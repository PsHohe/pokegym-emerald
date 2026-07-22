# Spike: Challenger Counter-Picking (Team Preview)

**Status:** IMPLEMENTED (simplified: strong challengers counter-pick against the gym TYPE, not the stored team — see FillStrongChallengerParty in src/gym_challenge.c). Kept for the ideal-version notes (§5 difficulty tiers, §6 scouting model). **Depends on:** registered gym teams
(`gym-leader-mode.md` §7.4) for the *ideal* version; a stubbed version can run
against the live party today.

> **Scope note.** `game_docs/` holds documentation for *this game*; `docs/` is
> the upstream pokeemerald-expansion mdbook. This is a game-specific spike.

## 1. The question

In competitive play, both players see each other's full team and then choose
which subset to *bring*. Can a gym challenger do the same — look at the player's
(gym leader's) stored team and bring the Pokémon that best counter it, instead
of a random party?

## 2. What the engine already gives us

### 2a. The live-battle AI is the wrong tool

`src/battle_ai_switch.c` has genuinely competitive matchup logic
(`GetBattlerTypeMatchup`, `GetSwitchinHitsToKO`, `CanBattlerWin1v1`,
`IsAceMon`…). **None of it is usable here.** Those functions read `gBattleMons[]`
and live damage-calc state — they only exist *during* a battle. Team preview
happens *before* one. So counter-picking cannot reuse them; it needs functions
that score **static species/move/ability data**.

### 2b. The right tool exists

`CalcPartyMonTypeEffectivenessMultiplier(move, speciesDef, abilityDef)`
(`src/battle_util.c:8252`, declared in `include/battle_util.h`) is a **pure
function** — no live battle required. Given one of a challenger mon's moves and a
gym mon's species + ability, it returns a `uq4_12_t` type multiplier and already
handles Levitate, Wonder Guard, and dual types.

Lower-level, `GetTypeModifier(atkType, defType)` (`battle_util.c:8322`) is the
raw type-chart lookup.

### 2c. There is a working precedent — the Battle Dome

The Battle Dome **already does pre-battle party-vs-party scoring** to seed its
tournament and resolve off-screen rounds. See `GetTypeEffectivenessPoints(move,
targetSpecies, mode)` (`src/battle_dome.c:2381`) and its callers around
`partyMovePoints` (`battle_dome.c:2273`+). It converts each move's effectiveness
into weighted points (`EFFECTIVENESS_MODE_GOOD`: x1→2, x2→4, x4→8;
`EFFECTIVENESS_MODE_BAD` is the mirror for resistances) and sums across a party.
**This is exactly the counter-pick score we want** — copy its point table rather
than inventing one.

## 3. Where it plugs into gym mode

Today challenger parties are rolled by the frontier's `FillTrainerParty` /
`FillTentTrainerParty_` (`src/battle_tower.c`). The selection is **random**:

```c
u16 monId = monSet[Random() % bfMonCount];   // battle_tower.c ~line 1992
// ...then reject duplicate species / held item, CreateFacilityMon, repeat.
```

`monSet` is the challenger's `0xFFFF`-terminated list of pool indices (defined
per challenger in `sRank1Challengers`, `src/gym_challenge.c:136`). Counter-picking
means **replacing that random draw with a scored selection** — bring the top-N
scoring pool entries instead of N random ones.

Two viable insertion points:

| Option | Mechanism | Notes |
| --- | --- | --- |
| **A. Reorder the monSet** | Before a gym battle, build a temp `monSet` sorted by counter-pick score and truncated to N; expose it via the facility pointer. | Minimal: the frontier's own fill loop then "randomly" draws from an already-optimal, exact-size list. Cheapest to land. |
| **B. Dedicated gym fill** | New `GymChallenge_FillChallengerParty()` that scores the pool and calls `CreateFacilityMon` for the top-N directly, bypassing the random loop. | More control (synergy pass, ace handling), but duplicates the dup-rejection logic. |

**Recommendation:** start with **A** — it reuses the frontier fill unchanged and
is a few dozen lines. Graduate to **B** only when the difficulty tiers (§5) need
the extra control.

**Prerequisite for a real counter:** a challenger's pool must be **larger than
the party size** (bring N of M). Rank-1 monSets are ~4 entries for a 2-mon party,
so this already works; keep pools comfortably larger than the bring count as
ranks grow.

## 4. The scoring core

For each candidate pool entry `C` (a `struct TrainerMon`) against the player's
stored gym team `{G₁…Gₖ}`:

```c
// Pure / pre-battle. gymTeam is the leader's registered team (see §6).
static s32 ScoreCandidateVsGymTeam(const struct TrainerMon *cand,
                                   const struct BoxPokemon *gymTeam, u32 gymCount)
{
    s32 offense = 0, defense = 0;
    enum Ability cAbility = cand->ability;

    for (u32 g = 0; g < gymCount; g++)
    {
        enum Species gSpecies = GetBoxMonData(&gymTeam[g], MON_DATA_SPECIES, NULL);
        enum Ability gAbility  = GetSpeciesAbility(gSpecies, 0);

        // OFFENSE: best of the candidate's moves vs this gym mon.
        uq4_12_t best = UQ_4_12(0.0);
        for (u32 m = 0; m < MAX_MON_MOVES; m++)
        {
            uq4_12_t eff = CalcPartyMonTypeEffectivenessMultiplier(cand->moves[m], gSpecies, gAbility);
            if (eff > best) best = eff;
        }
        offense += MatchupToPoints(best);        // x2 -> +4, x4 -> +8, x0.5 -> -2 ...

        // DEFENSE: how hard the gym mon's STAB hits the candidate back.
        // A mono-type gym makes this cheap: score vs the single gym type.
        uq4_12_t incoming = CalcPartyMonTypeEffectivenessMultiplier(
                                BestStabProxyMove(gSpecies), cand->species, cAbility);
        defense -= MatchupToPoints(incoming);    // punished for being weak to their STAB
    }
    return offense + defense;
}
```

- `MatchupToPoints` = the Dome's `EFFECTIVENESS_MODE_GOOD` switch, lifted verbatim.
- `BestStabProxyMove` can be approximated: since a gym is **mono-type**, defense
  can just score the candidate against that one gym type via a representative
  move of that type (or `GetTypeModifier` on the type directly). The mono-type
  constraint makes counter-picking unusually decisive — one good coverage type
  lights up against the whole gym.

**Pick step:** score every pool entry, sort descending, take the top N with two
guards:
1. Skip a candidate whose coverage fully duplicates one already picked (don't
   bring three mons that all only resist the gym type).
2. Guarantee ≥1 offensive "answer"; if none exists, keep the best raw attacker.

## 5. Difficulty knob

Perfect counter-picking every battle is oppressive. Scale it to challenger
strength — the same lever the frontier uses via `challengeNum`, and the gym via
its rank (`gym-leader-mode.md` §7.1):

| Tier | Behaviour |
| --- | --- |
| Easy | Ignore the gym team → random subset (**today's** `FillTrainerParty`, zero cost). |
| Mid  | Score, then pick from the **top half** with `Random()` — good, not optimal. |
| Hard | Greedy top-N — a real team-preview counter. |
| Ace  | Greedy **+** synergy pass so brought mons cover each other's weaknesses. |

Low tiers are free — they *are* the current code path. Rank should choose the
tier (and possibly a per-challenger roll for a rare tough one).

## 6. Open dependencies / decisions

1. **Team storage.** The scorer reads the leader's roster. Registered gym teams
   (`struct BoxPokemon[6]`, `gym-leader-mode.md` §7.4) don't exist yet. Until
   they do, stub `gymTeam` by reading the **live `gParties[B_TRAINER_PLAYER]`**
   at gym-open time — enough to prototype scoring standalone.
2. **Information model.** Real team preview is *mutual*. Perfect info (score vs
   all 6, as above) is simplest. A scouting/fog-of-war variant — challenger only
   "knows" mons the leader has used on previous days — is more RPG-like and would
   read from a persisted "seen" set in the save block.
3. **Roster width.** Keep challenger pools wider than the bring count as ranks
   scale, or counter-picking degenerates to "bring everything."

## 7. Effort estimate

- Option A + §4 scoring + Easy/Mid/Hard tiers, against a **stubbed live-party**
  gym team: small, self-contained, no save changes. Good first slice.
- Perfect→scouting info model and the Ace synergy pass: follow-ups, and the
  scouting variant needs a save-block field.

## 8. Key references

| Symbol | Location | Role |
| --- | --- | --- |
| `CalcPartyMonTypeEffectivenessMultiplier` | `src/battle_util.c:8252` | Pure move-vs-species matchup; the scoring primitive. |
| `GetTypeModifier` | `src/battle_util.c:8322` | Raw type-chart lookup. |
| `GetTypeEffectivenessPoints` | `src/battle_dome.c:2381` | Precedent: pre-battle party scoring + point table to copy. |
| `FillTrainerParty` / `FillTentTrainerParty_` | `src/battle_tower.c` | Random `monSet` roll — the hook point to replace. |
| `sRank1Challengers` / `sRank1ChallengerMons` | `src/gym_challenge.c:136` / `:54` | Challenger pools (`monSet` + `TrainerMon` templates). |
| `GymChallenge_OverrideFacilityPtrs` | `src/gym_challenge.c:239` | Where the gym swaps in its facility tables. |
