# Spike: Gym Points Currency & Rank Progress Bar

**Status:** implemented (slices 1–3; see `gym-leader-mode.md` for the living
docs). Slice 4 (card back / stars) remains future work. **Decisions locked
in** (see §2).
**Depends on:** nothing hard — can land against the current rank-1 PoC. The
rank-up *challenge* itself depends on the rank system
(`gym-leader-mode.md` §7.1) and story content, but the currency, bar, and
card can ship first.

> **Scope note.** `game_docs/` holds documentation for *this game*; `docs/` is
> the upstream pokeemerald-expansion mdbook. This is a game-specific spike.

## 1. The questions

1. Can gym battles award a **gym points** currency, scaled like trainer prize
   money, even though the tower battle type suppresses normal rewards?
2. Where does the currency (and the per-rank earned total) **persist**?
3. Can the per-rank total drive a **Legends ZA-style progress bar** that
   unlocks (not triggers) the rank-up challenge?
4. Can the **player card** be repurposed to show gym points + gym rank?

Short answer to all four: **yes, cheaply, with existing machinery.**

## 2. Decisions (agreed 2026-07-19)

| Decision | Choice |
| --- | --- |
| Bar fill metric | **Points earned this rank** (not win count). Beating a stronger challenger fills the bar faster, like ZA. Threshold per rank ≈ 20 average wins' worth. |
| Player card | **Reskin `src/trainer_card.c` in place** — swap what it prints; no new screen. |
| Economy | **Gym points only** from gym battles; no ₽ payout. Points are *the* progression currency. |

## 3. Earning: mirror the prize-money formula

### 3a. How gold actually works

`GetTrainerMoneyToGive` (`src/battle_script_commands.c:5831`):

```c
moneyReward = 4 * lastMonLevel * gBattleStruct->moneyMultiplier * trainerMoney;
// trainerMoney = gTrainerClasses[class].money ?: 5   (per-class rate, 1..50)
```

Class rates (`gTrainerClasses`, `src/battle_main.c:302`): Youngster/Bug
Catcher 4, Camper 4, Hex Maniac 6, Black Belt 8, Cooltrainer 12, Beauty 20,
Leader/Elite Four 25, Rich Boy 50. So a typical early trainer with a level-15
last mon pays `4 × 15 × 4 = ₽240`.

### 3b. The gym points formula

Gym battles run with `BATTLE_TYPE_BATTLE_TOWER`, so `Cmd_getmoneyreward`
never fires — **we award points ourselves, after the battle, in gym code**.
That's a feature: the formula lives in one place we own and no battle-script
changes are needed.

Use the *same shape* as gold:

```c
// In gym_challenge.c — everything here is already known statically.
points = 4 * rankLevelCap * classRate;
// classRate = gTrainerClasses[gFacilityClassToTrainerClass[
//                 gFacilityTrainers[challenger].facilityClass]].money ?: 5;
```

- `gFacilityClassToTrainerClass` already maps facility classes (what
  challengers use) to trainer classes (where the money rate lives) — used the
  same way by `frontier_util.c:3092`.
- Generated parties are all at the rank's level cap, so `lastMonLevel` ≡
  `rankLevelCap`. No party inspection needed.
- Calibration falls out for free: rank 1 (cap 15, Youngster rate 4) → **240
  points/win**, exactly what the same trainer would pay in gold. As ranks
  raise the level cap and introduce richer classes, points/win climbs the
  same curve gold does across a normal playthrough.
- Later difficulty features slot in naturally: a "tough challenger" roll can
  simply use a higher-rate class (or a flat multiplier), and pays more points
  *and* more bar progress — that's the ZA feel we want.

## 4. Storage: SaveBlock3 struct + one game var

### 4a. Where there is room

- **`struct SaveBlock3`** (`include/global.h:256`) is the expansion's
  purpose-built extensible save block. With this repo's current config
  (fake RTC, NPC followers, dexnav levels, item flags all disabled) it holds
  ~4 bytes of a 1,624-byte budget (`SAVE_BLOCK_3_CHUNK_SIZE 116 × 14`
  sectors, asserted at `src/save.c:80`). **This is the place.**
- SaveBlock2 has only ~84 bytes of slack and SaveBlock1's tail is tighter —
  no need to touch either.

### 4b. Proposed struct (~12 bytes)

```c
// include/global.h, inside struct SaveBlock3
struct GymLeaderState
{
    u32 points;                // spendable currency (XOR-encrypted, see 4c)
    u32 pointsEarnedThisRank;  // plain; drives the bar; reset on rank-up
    // room to grow: lifetime stats, wins, days opened...
};
```

**Gym rank lives in a game var, not the struct:** e.g. `VAR_GYM_RANK` at
`0x40FE` (currently `VAR_UNUSED_0x40FE`), right beside
`VAR_CHOSEN_GYM_TYPE` (`0x40FF`). Rationale: rank is the value map scripts
gate on constantly (`compare VAR_GYM_RANK, 2` for story beats, NPC dialogue,
map changes), and vars are the native script-side currency — same reasoning
that put the gym type in a var. Rank fits u16 trivially.

> ⚠️ Adding fields to SaveBlock3 shifts its layout — existing saves break.
> Fine at this stage of the project (no save-migration story yet), but land
> it before anyone has a long-lived save they care about.

### 4c. Reuse `money.c` wholesale — including the anti-cheat encryption

`GetMoney/SetMoney/AddMoney/RemoveMoney/IsEnoughMoney` (`src/money.c:69`)
all take a **pointer**, not a hardcoded field:

```c
AddMoney(&gSaveBlock3Ptr->gym.points, 240);        // cap + overflow handled
IsEnoughMoney(&gSaveBlock3Ptr->gym.points, cost);  // future spend systems
```

That buys, for free: the `MAX_MONEY` cap (999,999 — right order of magnitude
for a whole playthrough of 240+ point wins), overflow clamping, and the
XOR-with-`encryptionKey` obfuscation money uses. One extra line is required
in `ApplyNewEncryptionKeyToAllEncryptedData` (`src/load_save.c:300`) so key
rotation re-encrypts our field, mirroring the `gSaveBlock1Ptr->money` line at
`load_save.c:305`. (Frontier BP skips encryption; since these helpers make it
free, take it.)

`pointsEarnedThisRank` stays a plain u32 — it's not spendable, resets every
rank, and keeping it raw makes the bar code trivial.

## 5. The award hook and script flow

The gym day loop already reads the outcome in the map script
(`GetBattleOutcome`, see `gym-leader-mode.md` §5). Add **one special**,
called from the script on `B_OUTCOME_WON`:

```c
// Registered in data/specials.inc like the existing four gym specials.
void GymChallenge_AwardVictoryPoints(void)
{
    u32 points = CalcChallengerPoints(sCurrentChallenger);   // §3b formula
    AddMoney(&gSaveBlock3Ptr->gym.points, points);
    bool32 wasFull = BarIsFull();
    gSaveBlock3Ptr->gym.pointsEarnedThisRank += points;      // clamp at threshold*? no — keep raw
    ConvertIntToDecimalStringN(gStringVar1, points, ...);    // for the msgbox
    gSpecialVar_Result = (!wasFull && BarIsFull());          // "bar just filled!"
}
```

Script side, inside the existing win branch:

```
special GymChallenge_AwardVictoryPoints
msgbox gText_EarnedGymPoints   # "Earned {STR_VAR_1} Gym Points!"
compare VAR_RESULT, TRUE
if eq, call BarJustFilled_Fanfare   # jingle + "You can now take the rank-up exam!"
```

Doing it C-side keeps the formula/state private; doing the *messaging*
script-side keeps text and fanfare authorable per map. This is the same
split the PoC already uses for everything else.

## 6. Bar semantics and rank-up gating

- **Fill:** `pointsEarnedThisRank / barThreshold(rank)`. Threshold table per
  rank, first pass: `20 × expectedPointsPerWin(rank)` → rank 1 ≈ **4,800**
  (20 × 240). Tune later — it's one table.
- **Full ≠ rank-up.** A full bar only *unlocks* the rank-up challenge. Gate
  scripts with a tiny special (`GymChallenge_IsRankUpUnlocked` →
  `VAR_RESULT`) or a flag set by the award special; the attendant/story NPC
  then offers the exam battle whenever the player is ready.
- **On rank-up (story battle won):** `VAR_GYM_RANK++`,
  `pointsEarnedThisRank = 0`. `points` (the wallet) is untouched — the bar
  resets, the money doesn't. Overfill past the threshold is deliberately
  discarded (ZA behaviour; also removes any incentive to farm before ranking
  up).
- The rank-up battle itself is future story work — a natural use for the
  9 free **authored** trainer slots (`gym-leader-mode.md` §6), since it's a
  named, scripted, once-per-rank opponent, not a generated challenger.
- Derived state (`BarIsFull`) is computed, never stored — no
  double-bookkeeping to corrupt.

## 7. Player card reskin

### 7a. Why in-place is cheap

`src/trainer_card.c` is fully self-contained and data-driven off one
snapshot struct: `TrainerCard_GenerateCardForPlayer` →
`SetPlayerCardData` (`trainer_card.c:696`) copies save data into
`sData->trainerCard`, then two print pipelines render it:
`PrintAllOnCardFront` (`:922` — name, ID, **money**, Pokédex, time, profile
phrase) and `PrintAllOnCardBack` (`:952` — HoF, **link battles, trades,
berry crush, Pokéblocks, union room, contests**, frontier). Every line is
its own small `Print*` function writing into `WIN_CARD_TEXT`.

Almost the entire back page is link-era content that is meaningless in this
game — that's our free real estate.

### 7b. The plan

1. **Extend `struct TrainerCard`** (`include/trainer_card.h`) with
   `gymPoints`, `gymRank`, `barProgress`, `barThreshold`. (The struct is only
   link-exchanged, which we don't support — extending is safe. FRLG-only
   fields could be cannibalised instead, but clarity beats 12 bytes.)
2. **Front page swaps** (labels live in `src/strings.c`):
   - `PrintMoneyOnCard` (`:1039`) → prints **gym points** (`"{STR_VAR_1} GP"`
     instead of the `gText_PokedollarVar1` template). ₽ money leaves the
     card — it's no longer the number that defines this player.
   - New print state: **rank line** (`"RANK 3"` — or the rank's title once
     ranks have names).
   - New draw step: the **progress bar** under the rank line.
3. **Progress bar rendering:** the card windows are plain pixel buffers —
   `FillWindowPixelRect(WIN_CARD_TEXT, color, x, y, w, h)` drawing a frame
   plus a fill of width `w × barProgress / barThreshold` is ~20 lines, no new
   graphics assets. (Battle HP/EXP bars are sprite-based and battle-bound —
   not worth borrowing.) A tiled art bar can replace it later if we restyle
   the card.
4. **Back page:** replace the link stats with gym career stats as they start
   existing (total wins, challengers per day record, hardest win…). Not part
   of the first slice; the front page is.
5. **Later polish option:** card **stars** (`CountPlayerTrainerStars`,
   `:664`) currently count HoF/dex/paintings/frontier and tint the card
   palette — an obvious candidate to repurpose as a rank-tier visual (card
   upgrades as your gym grows). Cosmetic, do when ranks have tiers.

The card is opened from `start_menu.c:754` via `ShowPlayerTrainerCard` —
unchanged; the reskin is invisible to its callers.

## 8. Suggested slices

| Slice | Content | Size |
| --- | --- | --- |
| 1. Currency core | SaveBlock3 struct, encryption-rotation line, `VAR_GYM_RANK`, award special + formula, script msg in the win branch. | Small, self-contained; testable in the PoC loop day one. |
| 2. Card front | Struct fields, GP + rank lines, pixel bar. | Small-medium; pure `trainer_card.c`. |
| 3. Bar gating | Threshold table, `IsRankUpUnlocked` special, attendant dialogue hook. | Small; the *exam battle* behind it is separate story work. |
| 4. Card back / stars | Career stats, rank-tier card palette. | Later, cosmetic. |

Slices 1 and 2 have no dependency on the rank system — they read
`VAR_GYM_RANK` (which just sits at 1) and the rank-1 constants.

## 9. Key references

| Symbol | Location | Role |
| --- | --- | --- |
| `GetTrainerMoneyToGive` | `src/battle_script_commands.c:5831` | The gold formula we mirror. |
| `gTrainerClasses[].money` | `src/battle_main.c:302` | Per-class payout rates (1–50). |
| `gFacilityClassToTrainerClass` | used at `src/frontier_util.c:3092` | Challenger facility class → money rate. |
| `GetMoney/AddMoney/IsEnoughMoney` | `src/money.c:69` | Pointer-based, reusable for gym points (cap + encryption). |
| `ApplyNewEncryptionKeyToAllEncryptedData` | `src/load_save.c:300` | Add one line so key rotation covers `gym.points`. |
| `struct SaveBlock3` | `include/global.h:256` | Persistence home; ~1,620 bytes free (assert `src/save.c:80`). |
| `VAR_UNUSED_0x40FE` | `include/constants/vars.h` | Candidate `VAR_GYM_RANK`, beside `VAR_CHOSEN_GYM_TYPE`. |
| `PrintAllOnCardFront` / `PrintMoneyOnCard` | `src/trainer_card.c:922` / `:1039` | Card front pipeline / the line GP replaces. |
| `SetPlayerCardData` | `src/trainer_card.c:696` | Save → card snapshot; add gym fields here. |
| `CountPlayerTrainerStars` | `src/trainer_card.c:664` | Star/tint system, future rank-tier visual. |
