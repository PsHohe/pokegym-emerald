#ifndef GUARD_CONSTANTS_GYM_CHALLENGE_H
#define GUARD_CONSTANTS_GYM_CHALLENGE_H

// Team validation results returned by GymChallenge_Begin in VAR_RESULT.
#define GYM_TEAM_OK          0
#define GYM_TEAM_WRONG_SIZE  1
#define GYM_TEAM_OVERLEVELED 2
#define GYM_TEAM_WRONG_TYPE  3

// Rank 1 gym rules. These will later come from the gym rank system.
#define GYM_RANK1_PARTY_SIZE 2
#define GYM_RANK1_LEVEL_CAP  15
#define GYM_RANK1_NUM_CHALLENGES 3

// Gym Points earned this rank needed to fill the progress bar and unlock the
// rank-up exam. Tuned to ~20 average rank-1 wins (240 points each).
#define GYM_RANK1_BAR_THRESHOLD 4800

#endif // GUARD_CONSTANTS_GYM_CHALLENGE_H
