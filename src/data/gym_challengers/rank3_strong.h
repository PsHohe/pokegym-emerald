// Rank 3 strong challengers (level cap 29): experienced battlers with
// mid-stage evolutions, items, EVs and counter-picked parties.

enum
{
    GYM3_SMON_HAUNTER,
    GYM3_SMON_MACHOKE,
    GYM3_SMON_GRAVELER,
    GYM3_SMON_PELIPPER,
    GYM3_SMON_BRELOOM,
    GYM3_SMON_FLAAFFY,
    GYM3_SMON_NINETALES,
    GYM3_SMON_SNEASEL,
    GYM3_SMON_KADABRA,
    GYM3_SMON_QUAGSIRE,
    GYM3_SMON_SKARMORY,
    GYM3_SMON_XATU,
    GYM3_SMON_MAWILE,
    GYM3_SMON_MIGHTYENA,
};

static const struct TrainerMon sRank3StrongMons[] =
{
    [GYM3_SMON_HAUNTER] = {
        .species = SPECIES_HAUNTER,
        .moves = {MOVE_SHADOW_PUNCH, MOVE_NIGHT_SHADE, MOVE_HYPNOSIS, MOVE_CONFUSE_RAY},
        .heldItem = ITEM_SPELL_TAG,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_MACHOKE] = {
        .species = SPECIES_MACHOKE,
        .moves = {MOVE_KARATE_CHOP, MOVE_SEISMIC_TOSS, MOVE_REVENGE, MOVE_BULK_UP},
        .heldItem = ITEM_BLACK_BELT,
        .ev = TRAINER_PARTY_EVS(128, 128, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_GRAVELER] = {
        .species = SPECIES_GRAVELER,
        .moves = {MOVE_ROCK_THROW, MOVE_MAGNITUDE, MOVE_ROLLOUT, MOVE_HARDEN},
        .heldItem = ITEM_HARD_STONE,
        .ev = TRAINER_PARTY_EVS(0, 128, 128, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_PELIPPER] = {
        .species = SPECIES_PELIPPER,
        .moves = {MOVE_WATER_PULSE, MOVE_WING_ATTACK, MOVE_PROTECT, MOVE_MIST},
        .heldItem = ITEM_MYSTIC_WATER,
        .ev = TRAINER_PARTY_EVS(128, 0, 0, 0, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_BRELOOM] = {
        .species = SPECIES_BRELOOM,
        .moves = {MOVE_MACH_PUNCH, MOVE_MEGA_DRAIN, MOVE_HEADBUTT, MOVE_LEECH_SEED},
        .heldItem = ITEM_MIRACLE_SEED,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_FLAAFFY] = {
        .species = SPECIES_FLAAFFY,
        .moves = {MOVE_SHOCK_WAVE, MOVE_THUNDER_WAVE, MOVE_COTTON_SPORE, MOVE_HEADBUTT},
        .heldItem = ITEM_MAGNET,
        .ev = TRAINER_PARTY_EVS(128, 0, 0, 0, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_NINETALES] = {
        .species = SPECIES_NINETALES,
        .moves = {MOVE_FLAME_WHEEL, MOVE_CONFUSE_RAY, MOVE_QUICK_ATTACK, MOVE_WILL_O_WISP},
        .heldItem = ITEM_CHARCOAL,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_SNEASEL] = {
        .species = SPECIES_SNEASEL,
        .moves = {MOVE_FEINT_ATTACK, MOVE_ICY_WIND, MOVE_SLASH, MOVE_AGILITY},
        .heldItem = ITEM_NEVER_MELT_ICE,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_KADABRA] = {
        .species = SPECIES_KADABRA,
        .moves = {MOVE_PSYBEAM, MOVE_REFLECT, MOVE_RECOVER, MOVE_DISABLE},
        .heldItem = ITEM_TWISTED_SPOON,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_QUAGSIRE] = {
        .species = SPECIES_QUAGSIRE,
        .moves = {MOVE_MUD_SHOT, MOVE_SLAM, MOVE_YAWN, MOVE_AMNESIA},
        .heldItem = ITEM_ORAN_BERRY,
        .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_SKARMORY] = {
        .species = SPECIES_SKARMORY,
        .moves = {MOVE_STEEL_WING, MOVE_AIR_CUTTER, MOVE_SPIKES, MOVE_AGILITY},
        .heldItem = ITEM_METAL_COAT,
        .ev = TRAINER_PARTY_EVS(128, 0, 128, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_XATU] = {
        .species = SPECIES_XATU,
        .moves = {MOVE_PSYBEAM, MOVE_PECK, MOVE_CONFUSE_RAY, MOVE_WISH},
        .heldItem = ITEM_SITRUS_BERRY,
        .ev = TRAINER_PARTY_EVS(0, 0, 0, 128, 128, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_MAWILE] = {
        .species = SPECIES_MAWILE,
        .moves = {MOVE_BITE, MOVE_FAIRY_WIND, MOVE_CRUNCH, MOVE_IRON_DEFENSE},
        .heldItem = ITEM_SITRUS_BERRY,
        .ev = TRAINER_PARTY_EVS(128, 128, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
    [GYM3_SMON_MIGHTYENA] = {
        .species = SPECIES_MIGHTYENA,
        .moves = {MOVE_BITE, MOVE_HOWL, MOVE_SWAGGER, MOVE_ROAR},
        .heldItem = ITEM_BLACK_GLASSES,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 0, 0),
        .ball = BALL_GREAT,
    },
};

static const struct BattleFrontierTrainer sRank3StrongChallengers[] =
{
    {
        .facilityClass = FACILITY_CLASS_EXPERT_M,
        .trainerName = _("OTTO"),
        .monSet = (const u16[]) {
            GYM3_SMON_MACHOKE, GYM3_SMON_GRAVELER, GYM3_SMON_NINETALES, GYM3_SMON_SKARMORY,
            GYM3_SMON_KADABRA, GYM3_SMON_QUAGSIRE, GYM3_SMON_MAWILE, GYM3_SMON_BRELOOM,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_BLACK_BELT,
        .trainerName = _("KANE"),
        .monSet = (const u16[]) {
            GYM3_SMON_MACHOKE, GYM3_SMON_BRELOOM, GYM3_SMON_GRAVELER, GYM3_SMON_SNEASEL,
            GYM3_SMON_MIGHTYENA, GYM3_SMON_FLAAFFY, GYM3_SMON_HAUNTER, GYM3_SMON_QUAGSIRE,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_PSYCHIC_F,
        .trainerName = _("SYLVIA"),
        .monSet = (const u16[]) {
            GYM3_SMON_KADABRA, GYM3_SMON_XATU, GYM3_SMON_HAUNTER, GYM3_SMON_FLAAFFY,
            GYM3_SMON_NINETALES, GYM3_SMON_MAWILE, GYM3_SMON_SNEASEL, GYM3_SMON_PELIPPER,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_BIRD_KEEPER,
        .trainerName = _("ROLAND"),
        .monSet = (const u16[]) {
            GYM3_SMON_PELIPPER, GYM3_SMON_XATU, GYM3_SMON_SKARMORY, GYM3_SMON_MIGHTYENA,
            GYM3_SMON_BRELOOM, GYM3_SMON_HAUNTER, GYM3_SMON_FLAAFFY, GYM3_SMON_QUAGSIRE,
            0xFFFF
        },
    },
};

static const struct GymChallengerSpeech sRank3StrongSpeech[] =
{
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: Thirty years of battling,\nand rising GYMS still thrill me.\pI've prepared something\nspecial for yours."),
        .beforeText = COMPOUND_STRING("Experience is the best\ncounter."),
        .playerLostText = COMPOUND_STRING("The old ways still\nwork just fine."),
        .playerWonText = COMPOUND_STRING("Ho ho… The new generation\nhas teeth after all."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: My dojo studies every\nGYM in the region.\pYours is next on the\nlist. Osu!"),
        .beforeText = COMPOUND_STRING("Osu! No holding back!"),
        .playerLostText = COMPOUND_STRING("The dojo will feast\ntonight!"),
        .playerWonText = COMPOUND_STRING("Osu… Your discipline\nexceeds mine. For now."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I dreamed of this battle\nlast night.\pIn the dream, I knew exactly\nwhat to bring. And I did."),
        .beforeText = COMPOUND_STRING("Just like in my dream…"),
        .playerLostText = COMPOUND_STRING("Exactly as I\ndreamed it."),
        .playerWonText = COMPOUND_STRING("The dream ended\ndifferently…"),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: My birds scouted your\nGYM from above for days!\pNothing about your team\nsurprises us now."),
        .beforeText = COMPOUND_STRING("Strike from the skies!"),
        .playerLostText = COMPOUND_STRING("A bird's-eye view wins\nevery time!"),
        .playerWonText = COMPOUND_STRING("Even my birds didn't\nsee that coming…"),
    },
};
