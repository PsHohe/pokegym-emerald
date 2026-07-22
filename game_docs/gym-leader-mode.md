# Gym Leader Mode

This document describes the "player as gym leader" game mode being built on top
of pokeemerald-expansion 1.16.2, the current state of the proof of concept, and
how to continue from here.

> **Scope note.** `game_docs/` holds documentation for *this game*. The repo's
> `docs/` folder is the upstream pokeemerald-expansion mdbook and should be left
> for upstream merges. Keep game-specific docs here.

## 1. The concept

The player is a gym leader rather than a challenger. Instead of travelling to
gyms, the player *runs* one:

- The player can **open their gym** at will to receive a wave of challengers.
- Each challenger walks in, battles the player, and leaves; win/lose is handled
  without a whiteout so the loop continues.
- Outside of gym duty the player may keep any party, but to open the gym the
  active team must satisfy the **gym rules** (team size, level cap, and a single
  type). These rules tighten as the gym grows in **rank** (rank system planned,
  not yet built).
- Players will register/store battle teams so they can swap quickly between a
  free-roam party and a rules-compliant gym team (planned, see §6).

## 2. What the proof of concept implements

The PoC is a single self-contained slice that proves the end-to-end loop:

- Gym type is **fixed to Normal** and gym rank is **fixed to rank 1**
  (≤ 2 Pokémon, all level ≤ 15, all Normal type).
- A gift NPC hands the player three Pokémon of the chosen gym type (at the
  rank's level cap) and unlocks the party menu, standing in for the starter.
- An attendant NPC validates the player's team, then opens the gym for
  **3 challengers**, chosen randomly from a pool of 4.
- Each challenger has a randomly generated party, a unique overworld sprite,
  overworld intro dialogue, and plain-text in-battle win/lose speech.
- Battles award **no EXP or prize money** and never white the player out.
- Each win pays **Gym Points** (`4 × levelCap × classMoneyRate`, mirroring
  prize money — 240–360 at rank 1), announced with a fanfare. Points
  accumulate in a save-backed wallet and a per-rank total that fills the
  **rank-up bar** (rank 1 threshold: 4,800). Filling the bar unlocks the
  (future) rank-up exam; the attendant announces it. See
  `spike-gym-points.md` for the design.
- The **trainer card front** shows POINTS, RANK (from `VAR_GYM_RANK`), and a
  NEXT RANK progress bar in place of money and the Pokédex count.

Everything lives on the test map `TestingGrounds_Exterior1`.

### Files

| File | Purpose |
| --- | --- |
| `src/gym_challenge.c` | All gym logic: challenger tables, mon pools, party generation hooks, team validation, battle launch, in-battle speech, Gym Points award/accessors and rank-up bar gating. |
| `include/gym_challenge.h` | C-facing API (functions + facility-pointer/speech hooks). |
| `include/constants/gym_challenge.h` | Constants shared between C **and** event scripts (validation results, rank bounds, wave size, saved-team dimensions). Included from `data/event_scripts.s`, so preprocessor defines only. |
| `data/maps/TestingGrounds_Exterior1/map.json` | Object events: gym attendant, gift NPC, team keeper, rank examiner, and the variable-sprite challenger object. |
| `data/maps/TestingGrounds_Exterior1/scripts.pory` | The gym day loop, gift NPC, team keeper (saved teams), rank examiner, and all dialogue text. Compiles to `scripts.inc` (generated — don't edit). |
| `data/specials.inc` | Registers the six gym script specials (appended at end). |
| `src/frontier_util.c` | Two small hook points (see §4). |
| `include/global.h` | `struct GymLeaderState` (points wallet + per-rank bar total) in SaveBlock3. |
| `src/load_save.c` | Encryption-key rotation covers the points wallet. |
| `src/new_game.c` | Initializes `VAR_GYM_RANK` to 1. |
| `src/trainer_card.c` | Card front reskin: POINTS, RANK, and the NEXT RANK progress bar. |

### How to test

1. Build (`make -j`) and run `pokeemerald.gba`.
2. Warp to `TestingGrounds_Exterior1` (debug menu: hold **R + START** →
   warp). The map also has a walk-out warp to Littleroot Town.
3. Talk to the gift NPC (Expert ♂, at 10,8): receive **three Pokémon of your
   chosen gym type** at the current rank's level cap, plus the gym's
   **signature TM** (tier-1 move per type, `sGymSignatureMoves` in
   `src/gym_challenge.c`; sets `gym.signatureMove`). TMs are **not bag
   items**: the signature TM and the starter TM group
   (`FLAG_TM_GROUP_STARTER`) unlock in the **TM Machine** (see §7), which
   appears in the start menu from this moment. The party menu unlocks
   (`FLAG_SYS_POKEMON_GET`), as if you'd been given a starter. To test the
   off-type rule: rank up to 3+, teach the signature TM to an off-type mon,
   and it becomes selectable (one per team).
4. Talk to the **team keeper** (Scientist, at 4,7): register the current
   party as one of the 5 saved teams, view a team's members (stale
   references show as `???`), or clear a team.
5. Talk to the **rank examiner** (Expert ♀, at 12,7): see the current rank's
   rules (level cap, bring count, off-type slot from rank 3), the gym type
   and rank-up bar progress — and rank up on the spot (test-only shortcut,
   no exam).
6. Talk to the attendant (Teala, at 7,7) to open the gym: choose the
   defending team (current party or a saved team — saved-team members are
   fetched from the PC automatically), then pick exactly the rank's bring
   count in the selection menu. Ineligible mons (over the level cap,
   off-type without the signature move) are grayed out; backing out with B
   cancels the opening and restores your roaming party. The roaming party
   is also restored automatically when the gym closes after the wave or a
   loss.

The map scripts live in `scripts.pory` (Poryscript); `scripts.inc` is
generated output — edit only the `.pory`.

## 3. How it works: reusing the Battle Frontier

The core insight is that the Battle Frontier already implements "a stream of
opponents with procedurally generated parties walk in and battle you." The gym
mode **borrows the frontier's machinery** rather than reimplementing it.

The frontier stores opponents in two tables that it reaches through two global
pointers:

- `gFacilityTrainers` → an array of `struct BattleFrontierTrainer` (name, class,
  speech, and a `monSet`: a `0xFFFF`-terminated list of indices into the mon
  pool).
- `gFacilityTrainerMons` → an array of `struct TrainerMon` templates (species,
  moves, item, EVs, nature, etc.).

At battle time the frontier calls `FillTrainerParty` → `CreateFacilityMon`,
which rolls a party from the chosen trainer's `monSet`, rejecting duplicate
species/items, applying win-streak-scaled IVs and the level-mode level.

**Gym mode swaps those pointers.** While a gym session is active, our tables
stand in for the frontier's, so party generation, trainer names, classes,
overworld sprites, and battle UI all work unchanged.

### The battle type

`GymChallenge_StartBattle` launches the battle with:

```c
gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
```

`BATTLE_TYPE_BATTLE_TOWER` is what buys three things for free:

1. The pre-generated enemy party is **not** overwritten. `CreateNPCTrainerParty`
   only rebuilds parties when `BATTLE_TYPE_TRAINER` is set *and* no
   `BATTLE_TYPE_FRONTIER` bit is set — the tower bit is a frontier bit, so our
   rolled party survives.
2. **No EXP / prize money** (tower rules).
3. Losing returns control to the script instead of whiting out.

We set `gMain.savedCallback` to our own `HandleGymBattleEnd`, which just returns
to the field and continues the script — we deliberately skip the frontier's
streak/record bookkeeping in `HandleFacilityTrainerBattleEnd`.

## 4. The two engine hook points

Gym mode adds exactly **two** gates to the shared frontier code, both guarded by
a "is a gym session active" flag so normal frontier behaviour is untouched when
the gym is closed.

**(a) Facility pointer + level override** — top of `SetFacilityPtrsGetLevel()`
in `src/frontier_util.c`:

```c
if (GymChallenge_OverrideFacilityPtrs(&gymLevel))
    return gymLevel;
```

Because every frontier lookup funnels through this one function, this single
gate redirects party generation, names, classes, and sprites to the gym tables,
and forces the rank's level cap.

**(b) In-battle speech override** — top of `CopyFrontierTrainerText()` in
`src/frontier_util.c`:

```c
if (GymChallenge_CopyChallengerText(whichText, trainerId))
    return;
```

Facility trainers store battle speech as 6-word **easy-chat** arrays. Leaving
those zeroed renders as `??????????` (word ID 0 is a valid-but-blank word; the
real terminator is `0xFFFF`). Rather than author easy-chat word sequences, the
gym supplies **plain text** for the before/win/lose lines. This is also the
right long-term choice: challenger dialogue is free-form, not constrained to the
frontier's fixed vocabulary.

## 5. The script flow (`TestingGrounds_Exterior1/scripts.inc`)

The gym day loop, modelled on
`data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.inc`:

1. Attendant asks to open the gym → `special GymChallenge_Begin` validates the
   team and returns a `GYM_TEAM_*` result in `VAR_RESULT`. On failure, show the
   matching message and stop.
2. On success, loop `GYM_RANK1_NUM_CHALLENGES` times (counter in `VAR_TEMP_3`):
   - `special GymChallenge_PickChallenger` — picks an unused challenger, sets its
     overworld sprite (`VAR_OBJ_GFX_ID_0`), copies its name to `gStringVar1`, and
     returns its index in `VAR_RESULT`.
   - `addobject` + `applymovement` walk the challenger in.
   - `switch VAR_RESULT` selects that challenger's intro dialogue.
   - `HealPlayerParty`, then `GymChallenge_StartBattle`.
   - `specialvar VAR_RESULT, GetBattleOutcome` reads the result. `B_OUTCOME_WON`
     → challenger leaves, counter increments, next challenger (or day complete);
     anything else → the leader lost, gym closes for the day.
3. `GymChallenge_End` clears the session flag when the day ends (win or loss).

The challenger object (`LOCALID_TESTING_GYM_CHALLENGER`) uses graphics id
`OBJ_EVENT_GFX_VAR_0` and is hidden by `FLAG_TEMP_2` until spawned, exactly like
the Battle Tower opponent object.

## 6. How trainers are implemented (reference)

Useful context for extending challengers or adding authored trainers.

### Two kinds of trainer

- **Authored trainers** (`gTrainers`) — the normal, hand-written trainers used
  across the game's story. Defined in **`src/data/trainers.party`** using a
  Pokémon Showdown / competitive export syntax (per-mon species, level, ability,
  IVs, EVs, nature, item, moves), compiled by `tools/trainerproc` into
  `src/data/trainers.h`. Each authored trainer has a stable `TRAINER_*` id
  (`include/constants/opponents.h`) and consumes **one save "defeated" flag**.
- **Generated trainers** (frontier / gym) — no fixed party. A trainer entry owns
  a *pool* of mon templates, and the party is rolled at battle time. These
  consume **no defeated flag**, which is why gym challengers can be effectively
  unlimited.

### The hard limit on authored trainers

The binding constraint is **not** ROM or the id type (u16, ~65k) — it is the
save-file defeated-flag block:

- `MAX_TRAINERS_COUNT` = 864 reserved flag slots (`include/constants/opponents.h`).
- Currently 855 are used, leaving 9 free.
- Flags occupy `0x500`–`0x85F` (`include/constants/flags.h`), immediately below
  the system/badge/story flags at `0x860`.

To exceed 864 authored trainers you must renumber every flag above `0x860`
(cascading through `constants/flags.h`), which also grows the save flag array.
For a from-scratch gym game you'll instead be *deleting* most of the 855 Hoenn
story trainers, reclaiming the budget. **Prefer generated trainers for
challengers**; reserve authored slots for a small set of named/recurring
characters.

### The `struct TrainerMon` template

Shared by authored trainers *and* the frontier/gym generators
(`include/data.h`). Key fields: `species`, `moves[4]`, `heldItem`, `ability`,
`ev` (6-byte array), `iv` (packed; 0 = "use the caller's fixed IV"), `lvl`,
`nature`, `ball`, gender/shiny/tera/dynamax flags. Note: for **generated**
parties `lvl` in the template is ignored — the level comes from the gym rank /
frontier level mode, not the template.

### Difficulty system (available, not yet used by the gym)

The expansion ships a per-trainer difficulty axis: `gTrainers` is indexed
`[DIFFICULTY_COUNT][TRAINERS_COUNT]` (`DIFFICULTY_EASY/NORMAL/HARD`), authored
via a `Difficulty:` field in `trainers.party` and selectable at runtime through
`B_VAR_DIFFICULTY`. This does not consume extra ids/flags. It's a candidate lever
for scaling authored challengers later; the gym currently scales difficulty
through its own rank-based pools and IV bands instead.

## 7. Continuing from here

Recommended next steps, roughly in order:

1. **Gym rank system.** ✅ Done: `sGymRanks[GYM_RANK_COUNT]`
   (`src/gym_challenge.c`) drives level cap (15→65), bring count (2→4),
   off-type slots (1 from rank 3, gated on the mon knowing the gym's
   signature move, `gym.signatureMove`) and the rank-up bar threshold, all
   keyed on `VAR_GYM_RANK` (advance with `special GymChallenge_RankUp`,
   which also resets the bar and win streak). Still to come: per-rank
   challenger pools/difficulty and the strong-challenger chance.
2. **Persistent gym state.** Partially done: `SaveBlock3.gym`
   (`struct GymLeaderState`, `include/global.h`) holds the Gym Points
   wallet, per-rank bar total, `winStreak`, `signatureMove`, and the saved
   team references (`teams[GYM_NUM_SAVED_TEAMS]`, identity-based
   personality+OT id pairs); the rank lives in `VAR_GYM_RANK`. Win/loss
   records and other career stats still need fields when they exist.
   Note: growing this struct shifts the SaveBlock3 layout — old dev saves
   read garbage in the gym fields; start a new save after layout changes.
3. **Player-chosen gym type.** Partially done: team validation reads
   `VAR_CHOSEN_GYM_TYPE` (set by the intro) via `GymChallenge_GetGymType`.
   Still to come: key the challenger mon pools off the
   gym type (e.g. counter-type challengers).
4. **Registered teams.** ✅ Done (reference-based): teams are identity
   references (`GymSavedTeam` in SaveBlock3), registered from the current
   party at the team keeper and resolved against party + boxes at gym-open.
   The gym-open flow: pick a source (party or saved team) → the roaming
   party is backed up (`SavePlayerParty` special) and the team swapped in
   (`GymTeams_LoadTeamIntoParty`) → the frontier choose-half party menu
   runs under gym rules (`GymChallenge_ChooseGymParty` sets
   `VAR_FRONTIER_FACILITY = FACILITY_GYM`; see the gym cases in
   `src/party_menu.c` for level cap, type/signature-move eligibility, and
   the max-one-off-type confirm check) → `ReducePlayerPartyToSelectedMons`.
   `LoadPlayerParty` restores the roaming party on cancel, loss, or day
   end. Still to come: a graphical team editor (per-slot add/remove).
5. **Variable challenge waves.** ✅ Partially done — the streak system:
   `gym.winStreak` grows on every win, resets on a loss
   (`GymChallenge_RecordLoss`) or rank-up. Each incoming challenger rolls
   strong with chance `min(20 + 10 × streak, 80)`%
   (`GYM_STRONG_CHANCE_*` in `include/constants/gym_challenge.h`);
   `GymChallenge_PickChallenger` reports the tier in `VAR_0x8006`. Strong
   wins pay ×2 Gym Points. The attendant's opening phrase hints at the
   chance in four flavor tiers (`GymChallenge_GetStreakTier`), and a strong
   arrival gets an extra warning line.
6. **Challenger tiers & counter-picking.** ✅ Done: challenger rosters live
   in `src/data/gym_challengers/rank<N>_<tier>.h`, wired through
   `sChallengerSets[rank][tier]` (ranks without content fall back to the
   nearest lower authored rank, level-scaled). Common challengers use the
   frontier's random fill; **strong**
   challengers have wider, type-diverse pools with held items/EVs, a
   higher fixed-IV band (`GYM_STRONG_FIXED_IV`), their own intro/battle
   dialogue, and a **counter-picked party**: `FillStrongChallengerParty`
   scores every pool entry against the gym's type (best damaging move in,
   gym STAB back — `ScoreStrongCandidate`, Dome-style point table) and
   draws from the top of the ranking with a small skip chance for variety.
   See `spike-challenger-counterpick.md` for the original exploration.
7. **Content scale-out.** ✅ Structure done: challenger tables live under
   `src/data/gym_challengers/` (authored: ranks 1–4, both tiers — 32
   trainers total; ranks 5–8 fall back to the rank 4 doubles rosters,
   level-scaled). Challenger overworld intro lines live in the roster data
   (`introText`, shown via `GymChallenge_BufferChallengerIntro` +
   `msgbox gStringVar4`), so new rosters need no script changes. Remaining
   content: dedicated rosters for ranks 5–8.
9. **Doubles from rank 4.** ✅ Done: `GymRankInfo.doubles` (TRUE for ranks
   4–8) makes `GymChallenge_StartBattle` OR in `BATTLE_TYPE_DOUBLE` — the
   same flag the frontier's doubles mode uses; everything else (fill,
   counter-picking, points, win/loss flow) is unchanged. The attendant
   reminds the leader before defender selection and the examiner mentions
   it (`GymChallenge_IsDoubles` special). Rank 4+ rosters are pair-themed
   (Twins, Young Couple, Sr & Jr) and avoid ally-hitting spread moves
   (no Earthquake/Magnitude/Surf), favoring Protect/Fake Out tools.
8. **Rank-5 signature TM upgrade.** ✅ Done: at rank 5+ the examiner offers
   a one-time choice between two tier-2 moves for the gym's type
   (`sGymSignatureUpgrades`), shown by name in a `dynmultichoice`. Only the
   new move counts afterwards (the dialogue warns that outsiders knowing
   only the old move stop qualifying). TM57–77 were added to `FOREACH_TM`
   to cover the upgrade moves (Close Combat, Stone Edge, Scald, Play
   Rough, etc.).

### Known PoC caveats

- No EXP/money from gym battles (a side effect of the tower battle type). If
  leader mons should grow from defending, introduce a custom battle-type bit
  instead of reusing `BATTLE_TYPE_BATTLE_TOWER`.
- Session state is not saved — fine because a gym day completes within one
  script run, but any cross-session record must move to the save block.
- The gift-given flag uses `FLAG_UNUSED_0x020`; pick a permanent flag when the
  real intro flow exists.
- Vanilla-world TM content (giveitem NPCs, marts, Game Corner prizes, hidden
  items) is untouched and effectively dead: the TM/HM pocket holds one dummy
  slot and is skipped in the bag UI, so those scripts silently fail. Convert
  the ones that survive into `setflag FLAG_TM_GROUP_*` unlocks as the real
  world is built out.

## 7. The TM Machine (Legends Z-A-style TMs)

TMs are not bag items. Each TM is either **unlocked** or not (no quantity),
and teaching one costs **Gym Points** — except the current signature move,
which is free. `BAG_TMHM_COUNT` was shrunk to 1 (reclaiming ~930 bytes of
SaveBlock1) and the TM/HM pocket is skipped when cycling bag pockets.

**Unlock model** (`IsTMMoveUnlocked` in `src/tm_machine.c`) — fully computed,
no new save state:

1. **Flag groups**: `src/data/tm_unlock_groups.h` maps event flags
   (`FLAG_TM_GROUP_STARTER`, `FLAG_TM_GROUP_2..8` in
   `include/constants/flags.h`) to lists of TM moves. Scripts unlock a whole
   group with a plain `setflag`; one event can unlock many TMs.
2. **Signature system** (`GymChallenge_IsMoveUnlockedBySignature`): the
   tier-1 move for the gym type unlocks once `gym.signatureMove` is
   assigned; after the rank-5 upgrade **both** tier-2 choices unlock — the
   chosen one is the free signature, the other costs its normal price.

**Cost** (`GetTMTeachCost`): 0 for the current signature move, otherwise the
TM item's `price` from `src/data/items.h` (fallback `GYM_TM_DEFAULT_COST`
in `include/constants/gym_challenge.h` for zero-priced TMs). Spending goes
through `GymChallenge_TrySpendPoints` (money.c helpers on the gym wallet).

**UI** (`src/tm_machine.c`, modeled on the Move Relearner): start-menu "TMs"
entry (shown once a signature move exists) → scrolling list of unlocked TMs
with move data, cost, and current points → confirm → party menu in tutor
mode (`ChooseMonForTMMachine` in `src/party_menu.c`, `PARTY_ACTION_MOVE_TUTOR`
— teaches without consuming anything). The tutor flow reports success in
`VAR_RESULT` (`learnMoveState == 2`), and points are deducted only then, on
return to the machine.
- Challengers use the easiest frontier IV band and no EVs/items, tuned to be
  fair for two level-14 mons.
