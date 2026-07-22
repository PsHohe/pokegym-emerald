// TM Machine unlock groups. Each group maps an event flag to the TM moves it
// unlocks; scripts unlock a whole group with a plain setflag. A move may
// appear in more than one group. Every move here should exist as a TM
// (FOREACH_TM in include/constants/tms_hms.h) or it will simply never show.
//
// Signature TMs are NOT listed here — they unlock through the gym state
// (see GymChallenge_IsMoveUnlockedBySignature).

struct TmUnlockGroup
{
    u16 flag;
    const u16 *moves; // MOVE_UNAVAILABLE-terminated
};

// Set by the intro gift NPC alongside the signature TM.
static const u16 sTmUnlockGroup_Starter[] =
{
    MOVE_TAKE_DOWN,
    MOVE_CHARM,
    MOVE_PROTECT,
    MOVE_THIEF,
    MOVE_REST,
    MOVE_SLEEP_TALK,
    MOVE_SUBSTITUTE,
    MOVE_UNAVAILABLE,
};

static const struct TmUnlockGroup sTmUnlockGroups[] =
{
    { FLAG_TM_GROUP_STARTER, sTmUnlockGroup_Starter },
};
