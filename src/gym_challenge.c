#include "global.h"
#include "battle.h"
#include "battle_frontier.h"
#include "battle_main.h"
#include "battle_setup.h"
#include "battle_transition.h"
#include "event_data.h"
#include "frontier_util.h"
#include "data.h"
#include "gym_challenge.h"
#include "main.h"
#include "money.h"
#include "overworld.h"
#include "pokemon.h"
#include "random.h"
#include "string_util.h"
#include "task.h"
#include "constants/abilities.h"
#include "constants/battle_frontier.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/trainers.h"

// The gym challenge repurposes the Battle Frontier's facility trainer
// machinery: while a challenge is active, GymChallenge_OverrideFacilityPtrs
// points gFacilityTrainers/gFacilityTrainerMons at the tables below, so
// party generation, trainer names, classes, sprites and battle UI all read
// gym challengers instead of frontier trainers.

// For the proof of concept the gym type is fixed to Normal and the gym is
// rank 1. Both will become dynamic (player-chosen type, gym rank system).
#define GYM_TYPE TYPE_NORMAL

enum
{
    GYM_MON_POOCHYENA,
    GYM_MON_ZIGZAGOON,
    GYM_MON_TAILLOW,
    GYM_MON_WINGULL,
    GYM_MON_WURMPLE,
    GYM_MON_SILCOON,
    GYM_MON_NINCADA,
    GYM_MON_BEAUTIFLY,
    GYM_MON_MAKUHITA,
    GYM_MON_MACHOP,
    GYM_MON_MEDITITE,
    GYM_MON_RALTS,
    GYM_MON_SHROOMISH,
    GYM_MON_ELECTRIKE,
    GYM_MON_ARON,
};

// Rank 1 mon templates. Levels come from the gym rank (GYM_RANK1_LEVEL_CAP),
// IVs from the frontier fixed-IV band for low trainer ids.
static const struct TrainerMon sRank1ChallengerMons[] =
{
    [GYM_MON_POOCHYENA] = {
        .species = SPECIES_POOCHYENA,
        .moves = {MOVE_TACKLE, MOVE_HOWL, MOVE_SAND_ATTACK, MOVE_BITE},
        .ball = BALL_POKE,
    },
    [GYM_MON_ZIGZAGOON] = {
        .species = SPECIES_ZIGZAGOON,
        .moves = {MOVE_TACKLE, MOVE_GROWL, MOVE_HEADBUTT, MOVE_SAND_ATTACK},
        .ball = BALL_POKE,
    },
    [GYM_MON_TAILLOW] = {
        .species = SPECIES_TAILLOW,
        .moves = {MOVE_PECK, MOVE_GROWL, MOVE_FOCUS_ENERGY, MOVE_QUICK_ATTACK},
        .ball = BALL_POKE,
    },
    [GYM_MON_WINGULL] = {
        .species = SPECIES_WINGULL,
        .moves = {MOVE_WATER_GUN, MOVE_GROWL, MOVE_QUICK_ATTACK, MOVE_WING_ATTACK},
        .ball = BALL_POKE,
    },
    [GYM_MON_WURMPLE] = {
        .species = SPECIES_WURMPLE,
        .moves = {MOVE_TACKLE, MOVE_STRING_SHOT, MOVE_POISON_STING, MOVE_BUG_BITE},
        .ball = BALL_POKE,
    },
    [GYM_MON_SILCOON] = {
        .species = SPECIES_SILCOON,
        .moves = {MOVE_TACKLE, MOVE_HARDEN, MOVE_STRING_SHOT, MOVE_NONE},
        .ball = BALL_POKE,
    },
    [GYM_MON_NINCADA] = {
        .species = SPECIES_NINCADA,
        .moves = {MOVE_SCRATCH, MOVE_SAND_ATTACK, MOVE_FURY_SWIPES, MOVE_MUD_SLAP},
        .ball = BALL_POKE,
    },
    [GYM_MON_BEAUTIFLY] = {
        .species = SPECIES_BEAUTIFLY,
        .moves = {MOVE_ABSORB, MOVE_GUST, MOVE_STUN_SPORE, MOVE_NONE},
        .ball = BALL_POKE,
    },
    [GYM_MON_MAKUHITA] = {
        .species = SPECIES_MAKUHITA,
        .moves = {MOVE_TACKLE, MOVE_FOCUS_ENERGY, MOVE_ARM_THRUST, MOVE_SAND_ATTACK},
        .ball = BALL_POKE,
    },
    [GYM_MON_MACHOP] = {
        .species = SPECIES_MACHOP,
        .moves = {MOVE_KARATE_CHOP, MOVE_LOW_KICK, MOVE_LEER, MOVE_FOCUS_ENERGY},
        .ball = BALL_POKE,
    },
    [GYM_MON_MEDITITE] = {
        .species = SPECIES_MEDITITE,
        .moves = {MOVE_CONFUSION, MOVE_MEDITATE, MOVE_DETECT, MOVE_LOW_KICK},
        .ball = BALL_POKE,
    },
    [GYM_MON_RALTS] = {
        .species = SPECIES_RALTS,
        .moves = {MOVE_CONFUSION, MOVE_GROWL, MOVE_DOUBLE_TEAM, MOVE_NONE},
        .ball = BALL_POKE,
    },
    [GYM_MON_SHROOMISH] = {
        .species = SPECIES_SHROOMISH,
        .moves = {MOVE_ABSORB, MOVE_TACKLE, MOVE_STUN_SPORE, MOVE_LEECH_SEED},
        .ball = BALL_POKE,
    },
    [GYM_MON_ELECTRIKE] = {
        .species = SPECIES_ELECTRIKE,
        .moves = {MOVE_SPARK, MOVE_QUICK_ATTACK, MOVE_LEER, MOVE_HOWL},
        .ball = BALL_POKE,
    },
    [GYM_MON_ARON] = {
        .species = SPECIES_ARON,
        .moves = {MOVE_TACKLE, MOVE_HARDEN, MOVE_MUD_SLAP, MOVE_HEADBUTT},
        .ball = BALL_POKE,
    },
};

// Rank 1 challengers. Same struct as frontier trainers so all facility
// name/class/sprite lookups work unchanged. Speech words are unused; the
// map script provides the dialogue.
static const struct BattleFrontierTrainer sRank1Challengers[] =
{
    {
        .facilityClass = FACILITY_CLASS_YOUNGSTER,
        .trainerName = _("BENNY"),
        .monSet = (const u16[]) {
            GYM_MON_POOCHYENA, GYM_MON_ZIGZAGOON, GYM_MON_TAILLOW, GYM_MON_WINGULL,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_BUG_CATCHER,
        .trainerName = _("DINO"),
        .monSet = (const u16[]) {
            GYM_MON_WURMPLE, GYM_MON_SILCOON, GYM_MON_NINCADA, GYM_MON_BEAUTIFLY,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_BATTLE_GIRL,
        .trainerName = _("RIKA"),
        .monSet = (const u16[]) {
            GYM_MON_MAKUHITA, GYM_MON_MACHOP, GYM_MON_MEDITITE,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_M,
        .trainerName = _("TOMMY"),
        .monSet = (const u16[]) {
            GYM_MON_RALTS, GYM_MON_SHROOMISH, GYM_MON_ELECTRIKE, GYM_MON_ARON,
            0xFFFF
        },
    },
};

#define RANK1_CHALLENGER_COUNT ARRAY_COUNT(sRank1Challengers)

// In-battle dialogue. The frontier renders facility trainers' battle-end
// speech from 6-word easy chat arrays; gym challengers use plain text
// instead (see the gate in CopyFrontierTrainerText).
static const struct
{
    const u8 *beforeText;     // FRONTIER_BEFORE_TEXT
    const u8 *playerLostText; // FRONTIER_PLAYER_LOST_TEXT (challenger won)
    const u8 *playerWonText;  // FRONTIER_PLAYER_WON_TEXT (challenger lost)
} sRank1ChallengerSpeech[RANK1_CHALLENGER_COUNT] =
{
    {
        .beforeText = COMPOUND_STRING("Here goes nothing!"),
        .playerLostText = COMPOUND_STRING("I did it! I beat a real\nGYM LEADER!"),
        .playerWonText = COMPOUND_STRING("Aww! You're the real deal,\nGYM LEADER…"),
    },
    {
        .beforeText = COMPOUND_STRING("Go, my BUG POKéMON!"),
        .playerLostText = COMPOUND_STRING("BUG POKéMON are the\nstrongest after all!"),
        .playerWonText = COMPOUND_STRING("Squished… My BUGS did\ntheir best…"),
    },
    {
        .beforeText = COMPOUND_STRING("Show me your spirit!"),
        .playerLostText = COMPOUND_STRING("FIGHTING beats NORMAL!\nBasics win battles!"),
        .playerWonText = COMPOUND_STRING("Even with the type edge…\nYou're strong, LEADER."),
    },
    {
        .beforeText = COMPOUND_STRING("Time for a pop quiz!"),
        .playerLostText = COMPOUND_STRING("Just like the textbook\nsaid it would go!"),
        .playerWonText = COMPOUND_STRING("Back to studying…\nI'll ace the rematch!"),
    },
};

static EWRAM_DATA bool8 sChallengeActive = FALSE;
static EWRAM_DATA u8 sUsedChallengers = 0;
static EWRAM_DATA u8 sCurrentChallenger = 0;

static void Task_StartGymBattleAfterTransition(u8 taskId);
static void HandleGymBattleEnd(void);

// Called from CopyFrontierTrainerText. While a gym challenge is active the
// challenger's in-battle speech comes from plain text instead of the
// frontier's easy chat words.
bool32 GymChallenge_CopyChallengerText(u8 whichText, u16 trainerId)
{
    if (!sChallengeActive || trainerId >= RANK1_CHALLENGER_COUNT)
        return FALSE;

    switch (whichText)
    {
    case FRONTIER_BEFORE_TEXT:
        StringCopy(gStringVar4, sRank1ChallengerSpeech[trainerId].beforeText);
        return TRUE;
    case FRONTIER_PLAYER_LOST_TEXT:
        StringCopy(gStringVar4, sRank1ChallengerSpeech[trainerId].playerLostText);
        return TRUE;
    case FRONTIER_PLAYER_WON_TEXT:
        StringCopy(gStringVar4, sRank1ChallengerSpeech[trainerId].playerWonText);
        return TRUE;
    }

    return FALSE;
}

// Called from SetFacilityPtrsGetLevel. While a gym challenge is active all
// facility trainer lookups use the gym tables and the gym rank's level cap.
bool32 GymChallenge_OverrideFacilityPtrs(u8 *level)
{
    if (!sChallengeActive)
        return FALSE;

    gFacilityTrainers = sRank1Challengers;
    gFacilityTrainerMons = sRank1ChallengerMons;
    *level = GYM_RANK1_LEVEL_CAP;
    return TRUE;
}

static u16 ValidateTeam(void)
{
    u32 i;
    u32 count = CalculatePlayerPartyCount();

    if (count < 1 || count > GYM_RANK1_PARTY_SIZE)
        return GYM_TEAM_WRONG_SIZE;

    for (i = 0; i < count; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        u16 species = GetMonData(mon, MON_DATA_SPECIES);

        if (GetMonData(mon, MON_DATA_IS_EGG))
            return GYM_TEAM_WRONG_TYPE;
        if (GetMonData(mon, MON_DATA_LEVEL) > GYM_RANK1_LEVEL_CAP)
            return GYM_TEAM_OVERLEVELED;
        if (gSpeciesInfo[species].types[0] != GYM_TYPE
         && gSpeciesInfo[species].types[1] != GYM_TYPE)
            return GYM_TEAM_WRONG_TYPE;
    }

    return GYM_TEAM_OK;
}

// Validates the player's team against the gym rules. On success the gym
// opens for challenges. VAR_RESULT receives a GymTeamValidation value.
void GymChallenge_Begin(void)
{
    gSpecialVar_Result = ValidateTeam();
    if (gSpecialVar_Result == GYM_TEAM_OK)
    {
        sChallengeActive = TRUE;
        sUsedChallengers = 0;
    }
}

// Picks a random not-yet-fought challenger, prepares its overworld sprite
// (VAR_OBJ_GFX_ID_0) and copies its name to gStringVar1.
// VAR_RESULT receives the challenger index for dialogue selection.
void GymChallenge_PickChallenger(void)
{
    u32 id;

    do
    {
        id = Random() % RANK1_CHALLENGER_COUNT;
    } while (sUsedChallengers & (1u << id));

    sUsedChallengers |= 1u << id;
    sCurrentChallenger = id;
    SetBattleFacilityTrainerGfxId(id, 0);
    StringCopy(gStringVar1, sRank1Challengers[id].trainerName);
    gSpecialVar_Result = id;
}

// Starts the battle against the current challenger. Must be followed by
// waitstate. Uses the Battle Tower battle type so the pre-generated party
// is kept, no EXP/money is handed out and losing returns to the script
// instead of whiting out.
void GymChallenge_StartBattle(void)
{
    InitTrainerBattleParameter();
    TRAINER_BATTLE_PARAM.opponentA = sCurrentChallenger;
    gBattleScripting.specialTrainerBattleType = FACILITY_BATTLE_TOWER;
    gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
    FillFrontierTrainerParty(GYM_RANK1_PARTY_SIZE);
    CreateTask(Task_StartGymBattleAfterTransition, 1);
    PlayMapChosenOrBattleBGM(0);
    BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_TOWER));
}

void GymChallenge_End(void)
{
    sChallengeActive = FALSE;
}

// Gym Points wallet and rank-up bar. The wallet reuses the money helpers, so
// it shares money's cap and save encryption; the bar total is plain and only
// ever compared against the rank's threshold.

u32 GymChallenge_GetPoints(void)
{
    return GetMoney(&gSaveBlock3Ptr->gym.points);
}

u32 GymChallenge_GetBarProgress(void)
{
    return gSaveBlock3Ptr->gym.pointsEarnedThisRank;
}

// These two return rank-1 values until the gym rank system exists; they are
// the single lookup point to swap for per-rank tables later.
u32 GymChallenge_GetBarThreshold(void)
{
    return GYM_RANK1_BAR_THRESHOLD;
}

u32 GymChallenge_GetRank(void)
{
    return VarGet(VAR_GYM_RANK);
}

// Mirrors GetTrainerMoneyToGive's formula (4 * lastMonLevel * classRate).
// Generated parties are all at the rank's level cap, so the cap stands in
// for the last mon's level.
static u32 CalcChallengerPoints(u32 challengerId)
{
    u32 classRate = gTrainerClasses[gFacilityClassToTrainerClass[sRank1Challengers[challengerId].facilityClass]].money;

    if (classRate == 0)
        classRate = 5;
    return 4 * GYM_RANK1_LEVEL_CAP * classRate;
}

// Awards Gym Points for defeating the current challenger. Copies the amount
// to gStringVar1 for the reward message. VAR_RESULT receives TRUE if this
// win just filled the rank-up bar (for a one-time announcement).
void GymChallenge_AwardVictoryPoints(void)
{
    u32 points = CalcChallengerPoints(sCurrentChallenger);
    u32 threshold = GymChallenge_GetBarThreshold();
    bool32 wasFull = gSaveBlock3Ptr->gym.pointsEarnedThisRank >= threshold;

    AddMoney(&gSaveBlock3Ptr->gym.points, points);
    gSaveBlock3Ptr->gym.pointsEarnedThisRank += points;
    ConvertIntToDecimalStringN(gStringVar1, points, STR_CONV_MODE_LEFT_ALIGN, MAX_MONEY_DIGITS);
    gSpecialVar_Result = !wasFull && gSaveBlock3Ptr->gym.pointsEarnedThisRank >= threshold;
}

// VAR_RESULT receives whether the rank-up exam is unlocked. A full bar only
// unlocks the exam; ranking up is story-driven and resets the bar, not the
// wallet.
void GymChallenge_IsRankUpUnlocked(void)
{
    gSpecialVar_Result = gSaveBlock3Ptr->gym.pointsEarnedThisRank >= GymChallenge_GetBarThreshold();
}

static void Task_StartGymBattleAfterTransition(u8 taskId)
{
    if (IsBattleTransitionDone() == TRUE)
    {
        gMain.savedCallback = HandleGymBattleEnd;
        SetMainCallback2(CB2_InitBattle);
        DestroyTask(taskId);
    }
}

static void HandleGymBattleEnd(void)
{
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}
