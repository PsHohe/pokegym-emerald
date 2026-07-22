// Rank 4 strong challengers (level cap 36): elite battlers built for
// DOUBLES — Protect/Fake Out tools, no ally-hitting spread moves — with
// items, EVs and counter-picked parties.

enum
{
    GYM4_SMON_GARDEVOIR,
    GYM4_SMON_STARMIE,
    GYM4_SMON_HOUNDOOM,
    GYM4_SMON_MAGNETON,
    GYM4_SMON_MACHOKE,
    GYM4_SMON_CLAYDOL,
    GYM4_SMON_SEALEO,
    GYM4_SMON_NINETALES,
    GYM4_SMON_SKARMORY,
    GYM4_SMON_HERACROSS,
    GYM4_SMON_HAUNTER,
    GYM4_SMON_LANTURN,
    GYM4_SMON_BRELOOM,
    GYM4_SMON_DONPHAN,
};

static const struct TrainerMon sRank4StrongMons[] =
{
    [GYM4_SMON_GARDEVOIR] = {
        .species = SPECIES_GARDEVOIR,
        .moves = {MOVE_PSYCHIC, MOVE_CALM_MIND, MOVE_HYPNOSIS, MOVE_DOUBLE_TEAM},
        .heldItem = ITEM_TWISTED_SPOON,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_STARMIE] = {
        .species = SPECIES_STARMIE,
        .moves = {MOVE_WATER_PULSE, MOVE_PSYBEAM, MOVE_RECOVER, MOVE_SWIFT},
        .heldItem = ITEM_MYSTIC_WATER,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_HOUNDOOM] = {
        .species = SPECIES_HOUNDOOM,
        .moves = {MOVE_FLAMETHROWER, MOVE_CRUNCH, MOVE_WILL_O_WISP, MOVE_PROTECT},
        .heldItem = ITEM_CHARCOAL,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_MAGNETON] = {
        .species = SPECIES_MAGNETON,
        .moves = {MOVE_THUNDERBOLT, MOVE_TRI_ATTACK, MOVE_THUNDER_WAVE, MOVE_PROTECT},
        .heldItem = ITEM_MAGNET,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 0, 252, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_MACHOKE] = {
        .species = SPECIES_MACHOKE,
        .moves = {MOVE_KARATE_CHOP, MOVE_VITAL_THROW, MOVE_BULK_UP, MOVE_PROTECT},
        .heldItem = ITEM_BLACK_BELT,
        .ev = TRAINER_PARTY_EVS(128, 128, 0, 0, 0, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_CLAYDOL] = {
        .species = SPECIES_CLAYDOL,
        .moves = {MOVE_PSYBEAM, MOVE_ANCIENT_POWER, MOVE_COSMIC_POWER, MOVE_PROTECT},
        .heldItem = ITEM_SITRUS_BERRY,
        .ev = TRAINER_PARTY_EVS(128, 0, 128, 0, 0, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_SEALEO] = {
        .species = SPECIES_SEALEO,
        .moves = {MOVE_AURORA_BEAM, MOVE_BODY_SLAM, MOVE_ENCORE, MOVE_PROTECT},
        .heldItem = ITEM_NEVER_MELT_ICE,
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 0, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_NINETALES] = {
        .species = SPECIES_NINETALES,
        .moves = {MOVE_FLAMETHROWER, MOVE_CONFUSE_RAY, MOVE_WILL_O_WISP, MOVE_PROTECT},
        .heldItem = ITEM_CHARCOAL,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_SKARMORY] = {
        .species = SPECIES_SKARMORY,
        .moves = {MOVE_STEEL_WING, MOVE_DRILL_PECK, MOVE_SPIKES, MOVE_PROTECT},
        .heldItem = ITEM_METAL_COAT,
        .ev = TRAINER_PARTY_EVS(128, 0, 128, 0, 0, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_HERACROSS] = {
        .species = SPECIES_HERACROSS,
        .moves = {MOVE_MEGAHORN, MOVE_BRICK_BREAK, MOVE_ENDURE, MOVE_COUNTER},
        .heldItem = ITEM_SITRUS_BERRY,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_HAUNTER] = {
        .species = SPECIES_HAUNTER,
        .moves = {MOVE_SHADOW_BALL, MOVE_HYPNOSIS, MOVE_DREAM_EATER, MOVE_CONFUSE_RAY},
        .heldItem = ITEM_SPELL_TAG,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_LANTURN] = {
        .species = SPECIES_LANTURN,
        .moves = {MOVE_BUBBLE_BEAM, MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_CONFUSE_RAY},
        .heldItem = ITEM_SITRUS_BERRY,
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 0, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_BRELOOM] = {
        .species = SPECIES_BRELOOM,
        .moves = {MOVE_MACH_PUNCH, MOVE_SKY_UPPERCUT, MOVE_STUN_SPORE, MOVE_LEECH_SEED},
        .heldItem = ITEM_MIRACLE_SEED,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_ULTRA,
    },
    [GYM4_SMON_DONPHAN] = {
        .species = SPECIES_DONPHAN,
        .moves = {MOVE_ROLLOUT, MOVE_ROCK_TOMB, MOVE_FLAIL, MOVE_PROTECT},
        .heldItem = ITEM_HARD_STONE,
        .ev = TRAINER_PARTY_EVS(0, 128, 128, 0, 0, 0),
        .ball = BALL_ULTRA,
    },
};

static const struct BattleFrontierTrainer sRank4StrongChallengers[] =
{
    {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("ROSCO"),
        .monSet = (const u16[]) {
            GYM4_SMON_HOUNDOOM, GYM4_SMON_MACHOKE, GYM4_SMON_STARMIE, GYM4_SMON_DONPHAN,
            GYM4_SMON_MAGNETON, GYM4_SMON_SKARMORY, GYM4_SMON_SEALEO, GYM4_SMON_HERACROSS,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_F,
        .trainerName = _("VERA"),
        .monSet = (const u16[]) {
            GYM4_SMON_GARDEVOIR, GYM4_SMON_NINETALES, GYM4_SMON_LANTURN, GYM4_SMON_BRELOOM,
            GYM4_SMON_STARMIE, GYM4_SMON_CLAYDOL, GYM4_SMON_SEALEO, GYM4_SMON_SKARMORY,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_EXPERT_F,
        .trainerName = _("IRMA"),
        .monSet = (const u16[]) {
            GYM4_SMON_NINETALES, GYM4_SMON_CLAYDOL, GYM4_SMON_GARDEVOIR, GYM4_SMON_SEALEO,
            GYM4_SMON_LANTURN, GYM4_SMON_DONPHAN, GYM4_SMON_HAUNTER, GYM4_SMON_BRELOOM,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_PSYCHIC_M,
        .trainerName = _("NILS"),
        .monSet = (const u16[]) {
            GYM4_SMON_GARDEVOIR, GYM4_SMON_HAUNTER, GYM4_SMON_CLAYDOL, GYM4_SMON_STARMIE,
            GYM4_SMON_MAGNETON, GYM4_SMON_HERACROSS, GYM4_SMON_HOUNDOOM, GYM4_SMON_LANTURN,
            0xFFFF
        },
    },
};

static const struct GymChallengerSpeech sRank4StrongSpeech[] =
{
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: Doubles is chess with\nfists, LEADER.\pI've already planned six\nmoves ahead of you."),
        .beforeText = COMPOUND_STRING("Opening move: yours."),
        .playerLostText = COMPOUND_STRING("Checkmate. As\ncalculated."),
        .playerWonText = COMPOUND_STRING("You played a line I\nnever considered…"),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: My pair has never lost\na double battle.\pI intend to keep that\nrecord today."),
        .beforeText = COMPOUND_STRING("Perfect record, perfect\npair!"),
        .playerLostText = COMPOUND_STRING("The record stands.\nFlawless."),
        .playerWonText = COMPOUND_STRING("Our first loss…\nI'll cherish this one."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I've judged pair\ncontests for twenty years.\pLet's see if your teamwork\nis worth the hype."),
        .beforeText = COMPOUND_STRING("Show me true harmony!"),
        .playerLostText = COMPOUND_STRING("Style AND substance.\nTop marks for me."),
        .playerWonText = COMPOUND_STRING("Magnificent coordination!\nFull marks, LEADER."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: Two minds, four\nPOKéMON, one battlefield…\pI can read them all,\nLEADER."),
        .beforeText = COMPOUND_STRING("I see every outcome."),
        .playerLostText = COMPOUND_STRING("All paths led to my\nvictory."),
        .playerWonText = COMPOUND_STRING("Your pair moved in ways\nI couldn't foresee…"),
    },
};
