#ifndef GUARD_GYM_CHALLENGE_H
#define GUARD_GYM_CHALLENGE_H

#include "constants/gym_challenge.h"

bool32 GymChallenge_OverrideFacilityPtrs(u8 *level);
bool32 GymChallenge_CopyChallengerText(u8 whichText, u16 trainerId);

// Script specials
void GymChallenge_Begin(void);
void GymChallenge_PickChallenger(void);
void GymChallenge_StartBattle(void);
void GymChallenge_End(void);

#endif // GUARD_GYM_CHALLENGE_H
