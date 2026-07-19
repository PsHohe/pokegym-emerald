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
- A gift NPC hands the player two rules-compliant Normal Pokémon.
- An attendant NPC validates the player's team, then opens the gym for
  **3 challengers**, chosen randomly from a pool of 4.
- Each challenger has a randomly generated party, a unique overworld sprite,
  overworld intro dialogue, and plain-text in-battle win/lose speech.
- Battles award **no EXP or prize money** and never white the player out.

Everything lives on the test map `TestingGrounds_Exterior1`.

### Files

| File | Purpose |
| --- | --- |
| `src/gym_challenge.c` | All gym logic: challenger tables, mon pools, party generation hooks, team validation, battle launch, in-battle speech. |
| `include/gym_challenge.h` | C-facing API (functions + facility-pointer/speech hooks). |
| `include/constants/gym_challenge.h` | Constants shared between C **and** event scripts (validation results, rank-1 rules). Included from `data/event_scripts.s`. |
| `data/maps/TestingGrounds_Exterior1/map.json` | Object events: gym attendant, gift NPC, and the variable-sprite challenger object. |
| `data/maps/TestingGrounds_Exterior1/scripts.inc` | The gym day loop, gift NPC, validation messages, movement, and all dialogue text. |
| `data/specials.inc` | Registers the four gym script specials (appended at end). |
| `src/frontier_util.c` | Two small hook points (see §4). |

### How to test

1. Build (`make -j`) and run `pokeemerald.gba`.
2. Warp to `TestingGrounds_Exterior1` (debug menu: hold **R + START** →
   warp). The map also has a walk-out warp to Littleroot Town.
3. Talk to the gift NPC (Expert, at 10,8) to receive Zigzagoon + Whismur.
4. Make those two your only party members (deposit anything else via PC or the
   debug menu).
5. Talk to the attendant (at 7,7) and open the gym. Try opening with an illegal
   team (3 mons / an over-levelled mon / a non-Normal mon) to see each
   validation message.

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

1. **Gym rank system.** Replace the hardcoded rank-1 constants in
   `include/constants/gym_challenge.h` with a value read from a new save field.
   Rank should drive: team size, level cap, number of challengers, challenger
   difficulty (IV band / mon pool tier), and possibly the chance of a
   higher-difficulty challenger appearing.
2. **Persistent gym state.** Move the session bookkeeping (currently EWRAM
   statics in `gym_challenge.c`) that needs to persist — rank, win/loss record,
   reputation, currency — into a save block struct. There is slack in the
   PokémonStorage save sectors (~1470 bytes) and further space freeable via
   `include/config/save.h` `FREE_*` switches; see the spike notes.
3. **Player-chosen gym type.** Replace `#define GYM_TYPE TYPE_NORMAL` with a
   saved value chosen at game start, and key the challenger mon pools off the
   gym type (e.g. counter-type challengers).
4. **Registered teams.** Store gym teams as `struct BoxPokemon[6]` and swap them
   in/out of the party, mirroring the frontier's
   `SavePlayerParty()` / `LoadPlayerParty()` pattern
   (`src/load_save.c`). Add a management UI (the frontier "choose team" party
   menu and `dynmultichoice` are good templates).
5. **Variable challenge waves.** Randomise the number of challengers and add a
   chance for a tougher challenger, instead of a fixed 3.
6. **Content scale-out.** As the challenger roster grows, move the tables out of
   `src/gym_challenge.c` into dedicated data files under, e.g.,
   `src/data/gym_challengers/`.

### Known PoC caveats

- No EXP/money from gym battles (a side effect of the tower battle type). If
  leader mons should grow from defending, introduce a custom battle-type bit
  instead of reusing `BATTLE_TYPE_BATTLE_TOWER`.
- Session state is not saved — fine because a gym day completes within one
  script run, but any cross-session record must move to the save block.
- The gift-given flag uses `FLAG_UNUSED_0x020`; pick a permanent flag when the
  real intro flow exists.
- Challengers use the easiest frontier IV band and no EVs/items, tuned to be
  fair for two level-14 mons.
