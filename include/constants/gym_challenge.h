#ifndef GUARD_CONSTANTS_GYM_CHALLENGE_H
#define GUARD_CONSTANTS_GYM_CHALLENGE_H

// This header is included from data/event_scripts.s as well as C code:
// preprocessor definitions only, no C declarations.

// Team validation results returned by GymChallenge_Begin in VAR_RESULT.
#define GYM_TEAM_OK          0
#define GYM_TEAM_WRONG_SIZE  1
#define GYM_TEAM_OVERLEVELED 2
#define GYM_TEAM_WRONG_TYPE  3

#define GYM_RANK_MIN   1
#define GYM_RANK_MAX   8
#define GYM_RANK_COUNT 8

// Challengers per accepted wave, at every rank.
#define GYM_NUM_CHALLENGES_PER_WAVE 3

// The most Pokemon any rank lets the leader bring.
#define GYM_MAX_BRING_COUNT 4

// Saved gym teams (reference-based; see struct GymSavedTeam in global.h).
#define GYM_NUM_SAVED_TEAMS 5
#define GYM_TEAM_SIZE       6

// Challenger tiers. Each incoming challenger rolls strong with a chance that
// starts at the base, grows with the leader's win streak, and is capped.
// The streak resets on a loss or rank-up.
#define GYM_TIER_COMMON 0
#define GYM_TIER_STRONG 1

#define GYM_STRONG_CHANCE_BASE    20
#define GYM_STRONG_CHANCE_PER_WIN 10
#define GYM_STRONG_CHANCE_MAX     80

// Strong challengers pay out more Gym Points.
#define GYM_STRONG_POINTS_MULTIPLIER 2

// Teaching a TM from the TM Machine costs the TM item's price in Gym Points;
// zero-priced TMs fall back to this. The current signature TM is free.
#define GYM_TM_DEFAULT_COST 3000

#endif // GUARD_CONSTANTS_GYM_CHALLENGE_H
