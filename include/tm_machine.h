#ifndef GUARD_TM_MACHINE_H
#define GUARD_TM_MACHINE_H

// The TM Machine: a Legends Z-A-style interface listing every unlocked TM.
// TMs are not bag items — they are unlocked by event flags or the gym
// signature system, and teaching one costs Gym Points (the current signature
// TM is free).

bool32 IsTMMoveUnlocked(u16 move);
u32 GetTMTeachCost(u16 move);
void CB2_OpenTMMachineFromStartMenu(void);

#endif // GUARD_TM_MACHINE_H
