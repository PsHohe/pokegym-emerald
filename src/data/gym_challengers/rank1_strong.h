// Rank 1 strong challengers: trained battlers with held items, EVs, a
// higher fixed-IV band and, crucially, counter-picked parties — the fill
// scores each pool entry against the gym's type and brings the best
// answers (see FillStrongChallengerParty in gym_challenge.c).
//
// Pools are deliberately wider and more type-diverse than the bring count
// so that counter-picking has real choices against any gym type.

enum
{
    GYM_SMON_HOUNDOUR,
    GYM_SMON_MAGNEMITE,
    GYM_SMON_MACHOP,
    GYM_SMON_STARYU,
    GYM_SMON_BALTOY,
    GYM_SMON_SNORUNT,
    GYM_SMON_GROWLITHE,
    GYM_SMON_SHROOMISH,
    GYM_SMON_SANDSHREW,
    GYM_SMON_CHINCHOU,
    GYM_SMON_NATU,
    GYM_SMON_CUBONE,
    GYM_SMON_GASTLY,
    GYM_SMON_MEDITITE,
};

static const struct TrainerMon sRank1StrongMons[] =
{
    [GYM_SMON_HOUNDOUR] = {
        .species = SPECIES_HOUNDOUR,
        .moves = {MOVE_EMBER, MOVE_BITE, MOVE_SMOG, MOVE_HOWL},
        .heldItem = ITEM_CHARCOAL,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_MAGNEMITE] = {
        .species = SPECIES_MAGNEMITE,
        .moves = {MOVE_THUNDER_SHOCK, MOVE_SONIC_BOOM, MOVE_THUNDER_WAVE, MOVE_SUPERSONIC},
        .heldItem = ITEM_MAGNET,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 0, 252, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_MACHOP] = {
        .species = SPECIES_MACHOP,
        .moves = {MOVE_KARATE_CHOP, MOVE_LOW_KICK, MOVE_BULK_UP, MOVE_LEER},
        .heldItem = ITEM_BLACK_BELT,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_STARYU] = {
        .species = SPECIES_STARYU,
        .moves = {MOVE_WATER_PULSE, MOVE_SWIFT, MOVE_RECOVER, MOVE_HARDEN},
        .heldItem = ITEM_MYSTIC_WATER,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_BALTOY] = {
        .species = SPECIES_BALTOY,
        .moves = {MOVE_CONFUSION, MOVE_ROCK_TOMB, MOVE_MUD_SLAP, MOVE_HARDEN},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(128, 0, 0, 0, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_SNORUNT] = {
        .species = SPECIES_SNORUNT,
        .moves = {MOVE_POWDER_SNOW, MOVE_ICY_WIND, MOVE_BITE, MOVE_LEER},
        .heldItem = ITEM_NEVER_MELT_ICE,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 0, 252, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_GROWLITHE] = {
        .species = SPECIES_GROWLITHE,
        .moves = {MOVE_FLAME_WHEEL, MOVE_BITE, MOVE_ROAR, MOVE_LEER},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_SHROOMISH] = {
        .species = SPECIES_SHROOMISH,
        .moves = {MOVE_MEGA_DRAIN, MOVE_STUN_SPORE, MOVE_LEECH_SEED, MOVE_TACKLE},
        .heldItem = ITEM_MIRACLE_SEED,
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_SANDSHREW] = {
        .species = SPECIES_SANDSHREW,
        .moves = {MOVE_SAND_TOMB, MOVE_ROLLOUT, MOVE_SCRATCH, MOVE_SAND_ATTACK},
        .heldItem = ITEM_SOFT_SAND,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_CHINCHOU] = {
        .species = SPECIES_CHINCHOU,
        .moves = {MOVE_WATER_GUN, MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_SUPERSONIC},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(128, 0, 0, 0, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_NATU] = {
        .species = SPECIES_NATU,
        .moves = {MOVE_PECK, MOVE_NIGHT_SHADE, MOVE_CONFUSE_RAY, MOVE_WISH},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(128, 0, 0, 128, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_CUBONE] = {
        .species = SPECIES_CUBONE,
        .moves = {MOVE_BONE_CLUB, MOVE_HEADBUTT, MOVE_ROCK_TOMB, MOVE_LEER},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_GASTLY] = {
        .species = SPECIES_GASTLY,
        .moves = {MOVE_LICK, MOVE_NIGHT_SHADE, MOVE_HYPNOSIS, MOVE_CURSE},
        .heldItem = ITEM_SPELL_TAG,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM_SMON_MEDITITE] = {
        .species = SPECIES_MEDITITE,
        .moves = {MOVE_CONFUSION, MOVE_LOW_KICK, MOVE_DETECT, MOVE_MEDITATE},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(0, 128, 0, 128, 0, 0),
        .ball = BALL_GREAT,
    },
};

static const struct BattleFrontierTrainer sRank1StrongChallengers[] =
{
    {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("VITO"),
        .monSet = (const u16[]) {
            GYM_SMON_HOUNDOUR, GYM_SMON_MACHOP, GYM_SMON_STARYU, GYM_SMON_BALTOY,
            GYM_SMON_GROWLITHE, GYM_SMON_CHINCHOU, GYM_SMON_CUBONE, GYM_SMON_GASTLY,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_F,
        .trainerName = _("NADIA"),
        .monSet = (const u16[]) {
            GYM_SMON_MAGNEMITE, GYM_SMON_SNORUNT, GYM_SMON_SHROOMISH, GYM_SMON_SANDSHREW,
            GYM_SMON_NATU, GYM_SMON_MEDITITE, GYM_SMON_STARYU, GYM_SMON_HOUNDOUR,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_PSYCHIC_M,
        .trainerName = _("IVAN"),
        .monSet = (const u16[]) {
            GYM_SMON_NATU, GYM_SMON_BALTOY, GYM_SMON_MEDITITE, GYM_SMON_GASTLY,
            GYM_SMON_MAGNEMITE, GYM_SMON_SNORUNT, GYM_SMON_MACHOP, GYM_SMON_CHINCHOU,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_HEX_MANIAC,
        .trainerName = _("MARA"),
        .monSet = (const u16[]) {
            GYM_SMON_GASTLY, GYM_SMON_NATU, GYM_SMON_SNORUNT, GYM_SMON_HOUNDOUR,
            GYM_SMON_SHROOMISH, GYM_SMON_BALTOY, GYM_SMON_CUBONE, GYM_SMON_MEDITITE,
            0xFFFF
        },
    },
};

static const struct GymChallengerSpeech sRank1StrongSpeech[] =
{
    {
        .beforeText = COMPOUND_STRING("I've studied your GYM.\nNo mercy!"),
        .playerLostText = COMPOUND_STRING("Preparation beats\nreputation. Every time."),
        .playerWonText = COMPOUND_STRING("I countered everything…\nand still lost?!"),
    },
    {
        .beforeText = COMPOUND_STRING("Your streak ends with me."),
        .playerLostText = COMPOUND_STRING("Told you. Streaks are\nmade to be broken."),
        .playerWonText = COMPOUND_STRING("Tch… You've earned that\nstreak, LEADER."),
    },
    {
        .beforeText = COMPOUND_STRING("I foresaw this battle.\nAnd your defeat."),
        .playerLostText = COMPOUND_STRING("The future never lies\nto me."),
        .playerWonText = COMPOUND_STRING("Impossible… I did not\nforesee this outcome."),
    },
    {
        .beforeText = COMPOUND_STRING("A little curse for you…\nGood luck, LEADER."),
        .playerLostText = COMPOUND_STRING("Hee hee… The curse\nalways works."),
        .playerWonText = COMPOUND_STRING("My curse… broken?\nHow fascinating…"),
    },
};
