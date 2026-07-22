#ifndef GUARD_GYM_CHALLENGE_H
#define GUARD_GYM_CHALLENGE_H

#include "constants/gym_challenge.h"

bool32 GymChallenge_OverrideFacilityPtrs(u8 *level);
bool32 GymChallenge_CopyChallengerText(u8 whichText, u16 trainerId);

// Gym Points / rank state
u32 GymChallenge_GetPoints(void);
u32 GymChallenge_GetBarProgress(void);
u32 GymChallenge_GetBarThreshold(void);
u32 GymChallenge_GetRank(void);
u32 GymChallenge_GetGymType(void);
u32 GymChallenge_GetLevelCap(void);
u32 GymChallenge_GetBringCount(void);
u32 GymChallenge_GetOffTypeSlots(void);

// Script specials
void GymChallenge_Begin(void);
void GymChallenge_PickChallenger(void);
void GymChallenge_StartBattle(void);
void GymChallenge_End(void);
void GymChallenge_AwardVictoryPoints(void);
void GymChallenge_RecordLoss(void);
void GymChallenge_GetStreakTier(void);
void GymChallenge_BufferStreak(void);
void GymChallenge_IsRankUpUnlocked(void);
void GymChallenge_RankUp(void);
void GymChallenge_GiveGymStarters(void);
void GymChallenge_AssignSignatureTM(void);
void GymChallenge_BufferSignatureMove(void);
void GymChallenge_CanUpgradeSignatureTM(void);
void GymChallenge_BufferSignatureUpgradeChoices(void);
void GymChallenge_UpgradeSignatureTM(void);
void GymChallenge_BufferChallengerIntro(void);
void GymChallenge_BufferRankInfo(void);
void GymChallenge_BufferGymProgress(void);

// Saved gym teams (script specials; team index in gSpecialVar_0x8004)
void GymTeams_RegisterParty(void);
void GymTeams_BufferTeam(void);
void GymTeams_ClearTeam(void);
void GymTeams_LoadTeamIntoParty(void);
void GymChallenge_ChooseGymParty(void);

#endif // GUARD_GYM_CHALLENGE_H
