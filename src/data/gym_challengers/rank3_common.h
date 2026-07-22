// Rank 3 common challengers (level cap 29): seasoned trainers with
// mid-stage evolutions and real movesets, still at the low IV band.

enum
{
    GYM3_MON_MANECTRIC,
    GYM3_MON_SWELLOW,
    GYM3_MON_HARIYAMA,
    GYM3_MON_BRELOOM,
    GYM3_MON_PELIPPER,
    GYM3_MON_GRAVELER,
    GYM3_MON_KADABRA,
    GYM3_MON_MACHOKE,
    GYM3_MON_ROSELIA,
    GYM3_MON_MAWILE,
    GYM3_MON_SANDSLASH,
    GYM3_MON_GLOOM,
};

static const struct TrainerMon sRank3CommonMons[] =
{
    [GYM3_MON_MANECTRIC] = {
        .species = SPECIES_MANECTRIC,
        .moves = {MOVE_SPARK, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_BITE},
        .ball = BALL_POKE,
    },
    [GYM3_MON_SWELLOW] = {
        .species = SPECIES_SWELLOW,
        .moves = {MOVE_WING_ATTACK, MOVE_QUICK_ATTACK, MOVE_ENDEAVOR, MOVE_AGILITY},
        .ball = BALL_POKE,
    },
    [GYM3_MON_HARIYAMA] = {
        .species = SPECIES_HARIYAMA,
        .moves = {MOVE_ARM_THRUST, MOVE_VITAL_THROW, MOVE_FAKE_OUT, MOVE_BELLY_DRUM},
        .ball = BALL_POKE,
    },
    [GYM3_MON_BRELOOM] = {
        .species = SPECIES_BRELOOM,
        .moves = {MOVE_MACH_PUNCH, MOVE_MEGA_DRAIN, MOVE_STUN_SPORE, MOVE_LEECH_SEED},
        .ball = BALL_POKE,
    },
    [GYM3_MON_PELIPPER] = {
        .species = SPECIES_PELIPPER,
        .moves = {MOVE_WATER_PULSE, MOVE_WING_ATTACK, MOVE_MIST, MOVE_PROTECT},
        .ball = BALL_POKE,
    },
    [GYM3_MON_GRAVELER] = {
        .species = SPECIES_GRAVELER,
        .moves = {MOVE_ROCK_THROW, MOVE_MAGNITUDE, MOVE_SELF_DESTRUCT, MOVE_DEFENSE_CURL},
        .ball = BALL_POKE,
    },
    [GYM3_MON_KADABRA] = {
        .species = SPECIES_KADABRA,
        .moves = {MOVE_CONFUSION, MOVE_PSYBEAM, MOVE_REFLECT, MOVE_DISABLE},
        .ball = BALL_POKE,
    },
    [GYM3_MON_MACHOKE] = {
        .species = SPECIES_MACHOKE,
        .moves = {MOVE_KARATE_CHOP, MOVE_SEISMIC_TOSS, MOVE_REVENGE, MOVE_FORESIGHT},
        .ball = BALL_POKE,
    },
    [GYM3_MON_ROSELIA] = {
        .species = SPECIES_ROSELIA,
        .moves = {MOVE_MAGICAL_LEAF, MOVE_STUN_SPORE, MOVE_LEECH_SEED, MOVE_TOXIC},
        .ball = BALL_POKE,
    },
    [GYM3_MON_MAWILE] = {
        .species = SPECIES_MAWILE,
        .moves = {MOVE_BITE, MOVE_FAIRY_WIND, MOVE_IRON_DEFENSE, MOVE_FAKE_TEARS},
        .ball = BALL_POKE,
    },
    [GYM3_MON_SANDSLASH] = {
        .species = SPECIES_SANDSLASH,
        .moves = {MOVE_SLASH, MOVE_SAND_TOMB, MOVE_ROLLOUT, MOVE_SWIFT},
        .ball = BALL_POKE,
    },
    [GYM3_MON_GLOOM] = {
        .species = SPECIES_GLOOM,
        .moves = {MOVE_ACID, MOVE_MEGA_DRAIN, MOVE_SLEEP_POWDER, MOVE_MOONLIGHT},
        .ball = BALL_POKE,
    },
};

static const struct BattleFrontierTrainer sRank3CommonChallengers[] =
{
    {
        .facilityClass = FACILITY_CLASS_GENTLEMAN,
        .trainerName = _("WALT"),
        .monSet = (const u16[]) {
            GYM3_MON_MANECTRIC, GYM3_MON_PELIPPER, GYM3_MON_MAWILE, GYM3_MON_KADABRA,
            GYM3_MON_GLOOM,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_PICNICKER,
        .trainerName = _("DARA"),
        .monSet = (const u16[]) {
            GYM3_MON_SWELLOW, GYM3_MON_BRELOOM, GYM3_MON_ROSELIA, GYM3_MON_GLOOM,
            GYM3_MON_MANECTRIC,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_POKEMANIAC,
        .trainerName = _("SETH"),
        .monSet = (const u16[]) {
            GYM3_MON_GRAVELER, GYM3_MON_MACHOKE, GYM3_MON_SANDSLASH, GYM3_MON_MAWILE,
            GYM3_MON_HARIYAMA,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_COLLECTOR,
        .trainerName = _("REX"),
        .monSet = (const u16[]) {
            GYM3_MON_KADABRA, GYM3_MON_HARIYAMA, GYM3_MON_PELIPPER, GYM3_MON_SWELLOW,
            GYM3_MON_SANDSLASH,
            0xFFFF
        },
    },
};

static const struct GymChallengerSpeech sRank3CommonSpeech[] =
{
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: A gentleman always\ntests a rising GYM himself.\pDo entertain me,\nLEADER."),
        .beforeText = COMPOUND_STRING("En garde, LEADER!"),
        .playerLostText = COMPOUND_STRING("Splendid! A win worth\na toast tonight."),
        .playerWonText = COMPOUND_STRING("Marvelous battle!\nMy compliments, LEADER."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I hiked all the way\nhere just for this battle!\pMy team's full of energy.\nLet's go!"),
        .beforeText = COMPOUND_STRING("Nature gives us strength!"),
        .playerLostText = COMPOUND_STRING("Fresh air and hard work\nbeat anything!"),
        .playerWonText = COMPOUND_STRING("Whew! That was worth\nthe whole hike."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: My POKéMON are my\npride and joy!\pLet's see how they measure\nup to a GYM LEADER's!"),
        .beforeText = COMPOUND_STRING("Go, my darlings!"),
        .playerLostText = COMPOUND_STRING("My darlings did it!\nI'm so proud!"),
        .playerWonText = COMPOUND_STRING("My poor darlings…\nWe'll grow stronger yet!"),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: I've collected rare\nPOKéMON from everywhere.\pA badge from your GYM would\ncrown my collection!"),
        .beforeText = COMPOUND_STRING("For my collection!"),
        .playerLostText = COMPOUND_STRING("The crown jewel of my\ncollection! Yes!"),
        .playerWonText = COMPOUND_STRING("Hmph. Some treasures\ncan't be collected…"),
    },
};
