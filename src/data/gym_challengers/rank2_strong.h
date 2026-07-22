// Rank 2 strong challengers (level cap 22): trained battlers with items,
// EVs and counter-picked parties (see FillStrongChallengerParty).

enum
{
    GYM2_SMON_KADABRA,
    GYM2_SMON_HOUNDOUR,
    GYM2_SMON_SNEASEL,
    GYM2_SMON_WOOPER,
    GYM2_SMON_STARYU,
    GYM2_SMON_MANKEY,
    GYM2_SMON_GRIMER,
    GYM2_SMON_SKARMORY,
    GYM2_SMON_VULPIX,
    GYM2_SMON_LOMBRE,
    GYM2_SMON_ONIX,
    GYM2_SMON_ELEKID,
    GYM2_SMON_YANMA,
    GYM2_SMON_SPOINK,
};

static const struct TrainerMon sRank2StrongMons[] =
{
    [GYM2_SMON_KADABRA] = {
        .species = SPECIES_KADABRA,
        .moves = {MOVE_CONFUSION, MOVE_PSYBEAM, MOVE_DISABLE, MOVE_REFLECT},
        .heldItem = ITEM_TWISTED_SPOON,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_HOUNDOUR] = {
        .species = SPECIES_HOUNDOUR,
        .moves = {MOVE_EMBER, MOVE_BITE, MOVE_HOWL, MOVE_ROAR},
        .heldItem = ITEM_CHARCOAL,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_SNEASEL] = {
        .species = SPECIES_SNEASEL,
        .moves = {MOVE_FEINT_ATTACK, MOVE_ICY_WIND, MOVE_QUICK_ATTACK, MOVE_TAUNT},
        .heldItem = ITEM_NEVER_MELT_ICE,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_WOOPER] = {
        .species = SPECIES_WOOPER,
        .moves = {MOVE_MUD_SHOT, MOVE_WATER_GUN, MOVE_YAWN, MOVE_SLAM},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_STARYU] = {
        .species = SPECIES_STARYU,
        .moves = {MOVE_WATER_PULSE, MOVE_SWIFT, MOVE_RECOVER, MOVE_RAPID_SPIN},
        .heldItem = ITEM_MYSTIC_WATER,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_MANKEY] = {
        .species = SPECIES_MANKEY,
        .moves = {MOVE_KARATE_CHOP, MOVE_LOW_KICK, MOVE_FURY_SWIPES, MOVE_FOCUS_ENERGY},
        .heldItem = ITEM_BLACK_BELT,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_GRIMER] = {
        .species = SPECIES_GRIMER,
        .moves = {MOVE_SLUDGE, MOVE_MUD_SLAP, MOVE_DISABLE, MOVE_MINIMIZE},
        .heldItem = ITEM_POISON_BARB,
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_SKARMORY] = {
        .species = SPECIES_SKARMORY,
        .moves = {MOVE_PECK, MOVE_STEEL_WING, MOVE_SAND_ATTACK, MOVE_SWIFT},
        .heldItem = ITEM_METAL_COAT,
        .ev = TRAINER_PARTY_EVS(128, 0, 128, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_VULPIX] = {
        .species = SPECIES_VULPIX,
        .moves = {MOVE_EMBER, MOVE_CONFUSE_RAY, MOVE_QUICK_ATTACK, MOVE_WILL_O_WISP},
        .heldItem = ITEM_CHARCOAL,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 0, 252, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_LOMBRE] = {
        .species = SPECIES_LOMBRE,
        .moves = {MOVE_FAKE_OUT, MOVE_MEGA_DRAIN, MOVE_BUBBLE_BEAM, MOVE_NATURE_POWER},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(128, 0, 0, 0, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_ONIX] = {
        .species = SPECIES_ONIX,
        .moves = {MOVE_ROCK_THROW, MOVE_ROCK_TOMB, MOVE_BIND, MOVE_HARDEN},
        .heldItem = ITEM_HARD_STONE,
        .ev = TRAINER_PARTY_EVS(0, 128, 128, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_ELEKID] = {
        .species = SPECIES_ELEKID,
        .moves = {MOVE_SHOCK_WAVE, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_LEER},
        .heldItem = ITEM_MAGNET,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_YANMA] = {
        .species = SPECIES_YANMA,
        .moves = {MOVE_SONIC_BOOM, MOVE_WING_ATTACK, MOVE_DOUBLE_TEAM, MOVE_SUPERSONIC},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 252, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM2_SMON_SPOINK] = {
        .species = SPECIES_SPOINK,
        .moves = {MOVE_PSYBEAM, MOVE_CONFUSE_RAY, MOVE_BOUNCE, MOVE_GROWL},
        .heldItem = ITEM_LUM_BERRY,
        .ev = TRAINER_PARTY_EVS(128, 0, 0, 0, 128, 0),
        .ball = BALL_GREAT,
    },
};

static const struct BattleFrontierTrainer sRank2StrongChallengers[] =
{
    {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("DREW"),
        .monSet = (const u16[]) {
            GYM2_SMON_KADABRA, GYM2_SMON_HOUNDOUR, GYM2_SMON_STARYU, GYM2_SMON_MANKEY,
            GYM2_SMON_ONIX, GYM2_SMON_ELEKID, GYM2_SMON_SKARMORY, GYM2_SMON_LOMBRE,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_BATTLE_GIRL,
        .trainerName = _("KYLA"),
        .monSet = (const u16[]) {
            GYM2_SMON_MANKEY, GYM2_SMON_SNEASEL, GYM2_SMON_WOOPER, GYM2_SMON_VULPIX,
            GYM2_SMON_SPOINK, GYM2_SMON_ONIX, GYM2_SMON_ELEKID, GYM2_SMON_STARYU,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_HIKER,
        .trainerName = _("BORIS"),
        .monSet = (const u16[]) {
            GYM2_SMON_ONIX, GYM2_SMON_WOOPER, GYM2_SMON_GRIMER, GYM2_SMON_SKARMORY,
            GYM2_SMON_MANKEY, GYM2_SMON_HOUNDOUR, GYM2_SMON_LOMBRE, GYM2_SMON_YANMA,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_PSYCHIC_F,
        .trainerName = _("FAYE"),
        .monSet = (const u16[]) {
            GYM2_SMON_KADABRA, GYM2_SMON_SPOINK, GYM2_SMON_SNEASEL, GYM2_SMON_YANMA,
            GYM2_SMON_VULPIX, GYM2_SMON_GRIMER, GYM2_SMON_STARYU, GYM2_SMON_WOOPER,
            0xFFFF
        },
    },
};

static const struct GymChallengerSpeech sRank2StrongSpeech[] =
{
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I scouted your GYM for\na week before signing up.\pEvery pick in my lineup is\nan answer to yours!"),
        .beforeText = COMPOUND_STRING("Scouting complete.\nEngaging!"),
        .playerLostText = COMPOUND_STRING("Homework pays off.\nEvery single time."),
        .playerWonText = COMPOUND_STRING("I scouted everything…\nexcept your resolve."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: My master says a rising\nGYM makes the best training!\pI'm here to test my fists\nagainst your best!"),
        .beforeText = COMPOUND_STRING("Full power from the\nfirst bell!"),
        .playerLostText = COMPOUND_STRING("My training shows!\nMaster will be proud."),
        .playerWonText = COMPOUND_STRING("A worthy wall to train\nagainst. I'll return!"),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I carried this team\ndown from the mountains.\pRock-solid picks for\nbeating your type!"),
        .beforeText = COMPOUND_STRING("Steady as the mountain!"),
        .playerLostText = COMPOUND_STRING("Hah! The mountain\nalways wins!"),
        .playerWonText = COMPOUND_STRING("Solid as bedrock,\nyou are. Well fought."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: The cards showed me\nyour GYM's weakness…\pAnd I brought exactly\nwhat it fears."),
        .beforeText = COMPOUND_STRING("The cards never lie."),
        .playerLostText = COMPOUND_STRING("Just as the cards\nforetold."),
        .playerWonText = COMPOUND_STRING("The cards… misread\nyou entirely."),
    },
};
