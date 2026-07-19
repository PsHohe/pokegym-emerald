# Game Docs

Documentation for the "player as gym leader" game built on
pokeemerald-expansion. Keep game-specific docs here, separate from the repo's
upstream `docs/` mdbook (which is reserved for pokeemerald-expansion merges).

- [Gym Leader Mode](gym-leader-mode.md) — the gym challenge system: concept,
  proof-of-concept state, how it reuses the Battle Frontier, the engine hook
  points, trainer implementation reference, and how to continue.
- [Spike: Challenger Counter-Picking](spike-challenger-counterpick.md) — how a
  challenger could "team preview" against the leader's stored gym team and bring
  a countering subset; scoring primitives, the Battle Dome precedent, hook
  points, and a difficulty ladder.
- [Spike: Gym Points & Rank Progress Bar](spike-gym-points.md) — the gym points
  currency (earning formula mirroring prize money, SaveBlock3 storage, money.c
  reuse), the per-rank Legends ZA-style progress bar that unlocks rank-ups, and
  the trainer card reskin showing points + rank.
