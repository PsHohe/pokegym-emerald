// Rank 2 common challengers (level cap 22): hobbyists with early-route
// mons and first-stage evolutions, still itemless and at the low IV band.

enum
{
    GYM2_MON_MIGHTYENA,
    GYM2_MON_LINOONE,
    GYM2_MON_LOUDRED,
    GYM2_MON_LOMBRE,
    GYM2_MON_NUZLEAF,
    GYM2_MON_KIRLIA,
    GYM2_MON_DUSTOX,
    GYM2_MON_NINJASK,
    GYM2_MON_MAKUHITA,
    GYM2_MON_ELECTRIKE,
    GYM2_MON_ARON,
    GYM2_MON_VOLBEAT,
};

static const struct TrainerMon sRank2CommonMons[] =
{
    [GYM2_MON_MIGHTYENA] = {
        .species = SPECIES_MIGHTYENA,
        .moves = {MOVE_BITE, MOVE_SAND_ATTACK, MOVE_HOWL, MOVE_ROAR},
        .ball = BALL_POKE,
    },
    [GYM2_MON_LINOONE] = {
        .species = SPECIES_LINOONE,
        .moves = {MOVE_HEADBUTT, MOVE_SAND_ATTACK, MOVE_FURY_SWIPES, MOVE_ODOR_SLEUTH},
        .ball = BALL_POKE,
    },
    [GYM2_MON_LOUDRED] = {
        .species = SPECIES_LOUDRED,
        .moves = {MOVE_STOMP, MOVE_ASTONISH, MOVE_HOWL, MOVE_SUPERSONIC},
        .ball = BALL_POKE,
    },
    [GYM2_MON_LOMBRE] = {
        .species = SPECIES_LOMBRE,
        .moves = {MOVE_ABSORB, MOVE_BUBBLE, MOVE_FAKE_OUT, MOVE_RAIN_DANCE},
        .ball = BALL_POKE,
    },
    [GYM2_MON_NUZLEAF] = {
        .species = SPECIES_NUZLEAF,
        .moves = {MOVE_RAZOR_LEAF, MOVE_POUND, MOVE_FAKE_OUT, MOVE_GROWTH},
        .ball = BALL_POKE,
    },
    [GYM2_MON_KIRLIA] = {
        .species = SPECIES_KIRLIA,
        .moves = {MOVE_CONFUSION, MOVE_MAGICAL_LEAF, MOVE_DOUBLE_TEAM, MOVE_CALM_MIND},
        .ball = BALL_POKE,
    },
    [GYM2_MON_DUSTOX] = {
        .species = SPECIES_DUSTOX,
        .moves = {MOVE_GUST, MOVE_CONFUSION, MOVE_POISON_POWDER, MOVE_MOONLIGHT},
        .ball = BALL_POKE,
    },
    [GYM2_MON_NINJASK] = {
        .species = SPECIES_NINJASK,
        .moves = {MOVE_FURY_CUTTER, MOVE_SAND_ATTACK, MOVE_DOUBLE_TEAM, MOVE_SCREECH},
        .ball = BALL_POKE,
    },
    [GYM2_MON_MAKUHITA] = {
        .species = SPECIES_MAKUHITA,
        .moves = {MOVE_ARM_THRUST, MOVE_VITAL_THROW, MOVE_FAKE_OUT, MOVE_WHIRLWIND},
        .ball = BALL_POKE,
    },
    [GYM2_MON_ELECTRIKE] = {
        .species = SPECIES_ELECTRIKE,
        .moves = {MOVE_SPARK, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_HOWL},
        .ball = BALL_POKE,
    },
    [GYM2_MON_ARON] = {
        .species = SPECIES_ARON,
        .moves = {MOVE_METAL_CLAW, MOVE_HEADBUTT, MOVE_MUD_SLAP, MOVE_HARDEN},
        .ball = BALL_POKE,
    },
    [GYM2_MON_VOLBEAT] = {
        .species = SPECIES_VOLBEAT,
        .moves = {MOVE_QUICK_ATTACK, MOVE_CONFUSE_RAY, MOVE_MOONLIGHT, MOVE_SHOCK_WAVE},
        .ball = BALL_POKE,
    },
};

static const struct BattleFrontierTrainer sRank2CommonChallengers[] =
{
    {
        .facilityClass = FACILITY_CLASS_POKEFAN_M,
        .trainerName = _("ARNOLD"),
        .monSet = (const u16[]) {
            GYM2_MON_MIGHTYENA, GYM2_MON_LINOONE, GYM2_MON_LOUDRED, GYM2_MON_ARON,
            GYM2_MON_LOMBRE,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_LASS,
        .trainerName = _("MIMI"),
        .monSet = (const u16[]) {
            GYM2_MON_KIRLIA, GYM2_MON_VOLBEAT, GYM2_MON_DUSTOX, GYM2_MON_LOMBRE,
            GYM2_MON_ELECTRIKE,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_CAMPER,
        .trainerName = _("TED"),
        .monSet = (const u16[]) {
            GYM2_MON_NUZLEAF, GYM2_MON_NINJASK, GYM2_MON_MAKUHITA, GYM2_MON_ARON,
            GYM2_MON_LINOONE,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_F,
        .trainerName = _("JUNE"),
        .monSet = (const u16[]) {
            GYM2_MON_ELECTRIKE, GYM2_MON_KIRLIA, GYM2_MON_DUSTOX, GYM2_MON_LOUDRED,
            GYM2_MON_NINJASK,
            0xFFFF
        },
    },
};

static const struct GymChallengerSpeech sRank2CommonSpeech[] =
{
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: My kids dared me to\nchallenge you.\pCan't lose in front of the\nfamily, can I?"),
        .beforeText = COMPOUND_STRING("For the family album!"),
        .playerLostText = COMPOUND_STRING("The kids won't believe\nthis! I beat a LEADER!"),
        .playerWonText = COMPOUND_STRING("Well fought! The kids\nwill love this story."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: Your GYM is the talk\nof my class!\pIf I win, everyone will\ntalk about ME instead!"),
        .beforeText = COMPOUND_STRING("Time to get famous!"),
        .playerLostText = COMPOUND_STRING("Everyone's going to hear\nabout this! Everyone!"),
        .playerWonText = COMPOUND_STRING("You're way stronger than\nthe rumors said…"),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I trained in the wild\nall month for this!\pMy POKéMON are tougher\nthan they look!"),
        .beforeText = COMPOUND_STRING("Fresh from the wild!"),
        .playerLostText = COMPOUND_STRING("A month outdoors beats\na fancy GYM any day!"),
        .playerWonText = COMPOUND_STRING("Back to the tent…\nWe'll train even harder."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I've been keeping notes\non your battles!\pLet's see if you can beat\nmy research!"),
        .beforeText = COMPOUND_STRING("According to my notes…"),
        .playerLostText = COMPOUND_STRING("My notes were perfect!\nStraight A's for me!"),
        .playerWonText = COMPOUND_STRING("Hmm… I clearly need\nmore data on you."),
    },
};
