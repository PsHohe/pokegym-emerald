// Rank 4 common challengers (level cap 36): from this rank on gym battles
// are DOUBLES — rosters are pair-themed trainers, and movesets avoid
// ally-hitting spread moves (no Earthquake/Magnitude/Surf).

enum
{
    GYM4_MON_SWELLOW,
    GYM4_MON_HARIYAMA,
    GYM4_MON_MANECTRIC,
    GYM4_MON_SHARPEDO,
    GYM4_MON_CAMERUPT,
    GYM4_MON_GRUMPIG,
    GYM4_MON_CACTURNE,
    GYM4_MON_ALTARIA,
    GYM4_MON_CLAYDOL,
    GYM4_MON_ABSOL,
    GYM4_MON_SEVIPER,
    GYM4_MON_ZANGOOSE,
    GYM4_MON_DODRIO,
    GYM4_MON_MAGNETON,
};

static const struct TrainerMon sRank4CommonMons[] =
{
    [GYM4_MON_SWELLOW] = {
        .species = SPECIES_SWELLOW,
        .moves = {MOVE_AERIAL_ACE, MOVE_QUICK_ATTACK, MOVE_ENDEAVOR, MOVE_DOUBLE_TEAM},
        .ball = BALL_POKE,
    },
    [GYM4_MON_HARIYAMA] = {
        .species = SPECIES_HARIYAMA,
        .moves = {MOVE_ARM_THRUST, MOVE_FAKE_OUT, MOVE_KNOCK_OFF, MOVE_VITAL_THROW},
        .ball = BALL_POKE,
    },
    [GYM4_MON_MANECTRIC] = {
        .species = SPECIES_MANECTRIC,
        .moves = {MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_QUICK_ATTACK, MOVE_BITE},
        .ball = BALL_POKE,
    },
    [GYM4_MON_SHARPEDO] = {
        .species = SPECIES_SHARPEDO,
        .moves = {MOVE_WATER_PULSE, MOVE_CRUNCH, MOVE_SLASH, MOVE_FOCUS_ENERGY},
        .ball = BALL_POKE,
    },
    [GYM4_MON_CAMERUPT] = {
        .species = SPECIES_CAMERUPT,
        .moves = {MOVE_FLAME_WHEEL, MOVE_ROCK_TOMB, MOVE_AMNESIA, MOVE_PROTECT},
        .ball = BALL_POKE,
    },
    [GYM4_MON_GRUMPIG] = {
        .species = SPECIES_GRUMPIG,
        .moves = {MOVE_PSYBEAM, MOVE_CONFUSE_RAY, MOVE_BOUNCE, MOVE_PROTECT},
        .ball = BALL_POKE,
    },
    [GYM4_MON_CACTURNE] = {
        .species = SPECIES_CACTURNE,
        .moves = {MOVE_NEEDLE_ARM, MOVE_FEINT_ATTACK, MOVE_LEECH_SEED, MOVE_PROTECT},
        .ball = BALL_POKE,
    },
    [GYM4_MON_ALTARIA] = {
        .species = SPECIES_ALTARIA,
        .moves = {MOVE_DRAGON_BREATH, MOVE_AERIAL_ACE, MOVE_SING, MOVE_SAFEGUARD},
        .ball = BALL_POKE,
    },
    [GYM4_MON_CLAYDOL] = {
        .species = SPECIES_CLAYDOL,
        .moves = {MOVE_PSYBEAM, MOVE_ANCIENT_POWER, MOVE_COSMIC_POWER, MOVE_PROTECT},
        .ball = BALL_POKE,
    },
    [GYM4_MON_ABSOL] = {
        .species = SPECIES_ABSOL,
        .moves = {MOVE_SLASH, MOVE_BITE, MOVE_SWORDS_DANCE, MOVE_QUICK_ATTACK},
        .ball = BALL_POKE,
    },
    [GYM4_MON_SEVIPER] = {
        .species = SPECIES_SEVIPER,
        .moves = {MOVE_POISON_TAIL, MOVE_BITE, MOVE_GLARE, MOVE_SCREECH},
        .ball = BALL_POKE,
    },
    [GYM4_MON_ZANGOOSE] = {
        .species = SPECIES_ZANGOOSE,
        .moves = {MOVE_SLASH, MOVE_CRUSH_CLAW, MOVE_QUICK_ATTACK, MOVE_SWORDS_DANCE},
        .ball = BALL_POKE,
    },
    [GYM4_MON_DODRIO] = {
        .species = SPECIES_DODRIO,
        .moves = {MOVE_DRILL_PECK, MOVE_TRI_ATTACK, MOVE_FURY_ATTACK, MOVE_AGILITY},
        .ball = BALL_POKE,
    },
    [GYM4_MON_MAGNETON] = {
        .species = SPECIES_MAGNETON,
        .moves = {MOVE_SHOCK_WAVE, MOVE_TRI_ATTACK, MOVE_THUNDER_WAVE, MOVE_SONIC_BOOM},
        .ball = BALL_POKE,
    },
};

static const struct BattleFrontierTrainer sRank4CommonChallengers[] =
{
    {
        .facilityClass = FACILITY_CLASS_TWINS,
        .trainerName = _("LIA&MIA"),
        .monSet = (const u16[]) {
            GYM4_MON_SWELLOW, GYM4_MON_MANECTRIC, GYM4_MON_GRUMPIG, GYM4_MON_ALTARIA,
            GYM4_MON_DODRIO, GYM4_MON_ZANGOOSE,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_YOUNG_COUPLE,
        .trainerName = _("KIM&KEL"),
        .monSet = (const u16[]) {
            GYM4_MON_MANECTRIC, GYM4_MON_SHARPEDO, GYM4_MON_ABSOL, GYM4_MON_SEVIPER,
            GYM4_MON_CACTURNE, GYM4_MON_GRUMPIG,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_SR_AND_JR,
        .trainerName = _("INA&LEO"),
        .monSet = (const u16[]) {
            GYM4_MON_HARIYAMA, GYM4_MON_CLAYDOL, GYM4_MON_CAMERUPT, GYM4_MON_MAGNETON,
            GYM4_MON_SWELLOW, GYM4_MON_ABSOL,
            0xFFFF
        },
    },
    {
        .facilityClass = FACILITY_CLASS_POKEFAN_F,
        .trainerName = _("HELGA"),
        .monSet = (const u16[]) {
            GYM4_MON_CAMERUPT, GYM4_MON_DODRIO, GYM4_MON_ZANGOOSE, GYM4_MON_SEVIPER,
            GYM4_MON_CLAYDOL, GYM4_MON_HARIYAMA,
            0xFFFF
        },
    },
};

static const struct GymChallengerSpeech sRank4CommonSpeech[] =
{
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: We practiced our pair\nmoves all summer!\pTwo hearts, one battle -\nlet's go!"),
        .beforeText = COMPOUND_STRING("Together now!"),
        .playerLostText = COMPOUND_STRING("Teamwork makes the\ndream work!"),
        .playerWonText = COMPOUND_STRING("Even our best combo\nwasn't enough…"),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: A double battle is the\nultimate couple's test!\pOur POKéMON are as close\nas we are!"),
        .beforeText = COMPOUND_STRING("For love and victory!"),
        .playerLostText = COMPOUND_STRING("Best date ever!"),
        .playerWonText = COMPOUND_STRING("We lost the battle,\nbut not each other!"),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: My grandkid picked our\nteam. I picked the tactics.\pSixty years of battles in\none corner!"),
        .beforeText = COMPOUND_STRING("Old tricks, young legs!"),
        .playerLostText = COMPOUND_STRING("Experience and youth -\nunbeatable together!"),
        .playerWonText = COMPOUND_STRING("What a battle to share\nwith the little one."),
    },
    {
        .introText = COMPOUND_STRING("{STR_VAR_1}: My darlings have been\ndying to battle side by side!\pShow us your best\npair, LEADER!"),
        .beforeText = COMPOUND_STRING("Shine, my darlings!"),
        .playerLostText = COMPOUND_STRING("My darlings were simply\ndazzling today!"),
        .playerWonText = COMPOUND_STRING("Oh my… What a\nperformance, LEADER!"),
    },
};
