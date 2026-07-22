// Rank 1 common challengers: rookie trainers with unevolved, itemless mons
// at the frontier's lowest IV band. Parties are rolled randomly from each
// challenger's monSet by the standard frontier fill.

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

// Levels come from the gym rank's level cap, IVs from the frontier fixed-IV
// band for low trainer ids.
static const struct TrainerMon sRank1CommonMons[] =
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

// Same struct as frontier trainers so all facility name/class/sprite lookups
// work unchanged. Speech words are unused; overworld dialogue comes from the
// map script and in-battle speech from the speech table below.
static const struct BattleFrontierTrainer sRank1CommonChallengers[] =
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

static const struct GymChallengerSpeech sRank1CommonSpeech[] =
{
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: So you're the new GYM\nLEADER?\pMy POOCHYENA and I are gonna take\nyour badge, mister!"),
        .beforeText = COMPOUND_STRING("Here goes nothing!"),
        .playerLostText = COMPOUND_STRING("I did it! I beat a real\nGYM LEADER!"),
        .playerWonText = COMPOUND_STRING("Aww! You're the real deal,\nGYM LEADER…"),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I found sooo many BUG\nPOKéMON in the woods!\pLet's see them squish your\nPOKéMON!"),
        .beforeText = COMPOUND_STRING("Go, my BUG POKéMON!"),
        .playerLostText = COMPOUND_STRING("BUG POKéMON are the\nstrongest after all!"),
        .playerWonText = COMPOUND_STRING("Squished… My BUGS did\ntheir best…"),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: My FIGHTING-type\nPOKéMON train every day!\pShow me what a real GYM LEADER\ncan do. Prepare yourself!"),
        .beforeText = COMPOUND_STRING("Show me your spirit!"),
        .playerLostText = COMPOUND_STRING("FIGHTING spirit wins\nbattles! Remember that!"),
        .playerWonText = COMPOUND_STRING("Even with all my training…\nYou're strong, LEADER."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I studied all about\ntype matchups in school!\pToday's lesson: beating a GYM\nLEADER!"),
        .beforeText = COMPOUND_STRING("Time for a pop quiz!"),
        .playerLostText = COMPOUND_STRING("Just like the textbook\nsaid it would go!"),
        .playerWonText = COMPOUND_STRING("Back to studying…\nI'll ace the rematch!"),
    },
};
