#include "global.h"
#include "main.h"
#include "battle_main.h"
#include "bg.h"
#include "data.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "gym_challenge.h"
#include "international_string_util.h"
#include "item.h"
#include "list_menu.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "money.h"
#include "move.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "tm_machine.h"
#include "window.h"
#include "constants/party_menu.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "data/tm_unlock_groups.h"

// The TM Machine: lists every unlocked TM (see IsTMMoveUnlocked), shows the
// move's data and Gym Point cost, and teaches via the party menu's tutor
// flow (no bag item involved). Layout and flow are modeled on the Move
// Relearner (src/move_relearner.c), but TM-first: pick the move, then the
// Pokémon.

enum
{
    WIN_INFO,
    WIN_LIST,
    WIN_MSG,
    WIN_YESNO_DUMMY,
};

#define TAG_LIST_ARROWS 5425

static EWRAM_DATA struct TMMachine
{
    struct ListMenuItem menuItems[NUM_TECHNICAL_MACHINES + 1];
    u8 mainTask;
    u8 listMenuTask;
    u8 scrollArrowTask;
    u16 numMenuItems;
    u16 numToShowAtOnce;
} *sTMMachine = NULL;

static EWRAM_DATA struct
{
    u16 listOffset;
    u16 listRow;
} sTMMachineScroll = {0};

// The move handed to the party menu; consulted again on return to deduct
// points once the teach is confirmed successful.
static EWRAM_DATA u16 sPendingTeachMove = MOVE_NONE;

static void CB2_InitTMMachine(void);
static void CB2_TMMachineMain(void);
static void CB2_ChooseMonForTeach(void);
static void CB2_ReturnToTMMachine(void);
static void Task_TMMachine_HandleInput(u8 taskId);
static void Task_TMMachine_WaitConfirmText(u8 taskId);
static void Task_TMMachine_HandleConfirmInput(u8 taskId);
static void Task_TMMachine_WaitMessageThenResume(u8 taskId);
static void Task_TMMachine_FadeToPartyMenu(u8 taskId);
static void Task_TMMachine_Quit(u8 taskId);
static void PrintTMInfo(s32 move);
static void ShowSelectPrompt(void);
static void AddListScrollArrows(void);
static void RemoveListScrollArrows(void);

static const u8 sText_SelectPrompt[] = _("Choose a TM to teach.");
static const u8 sText_ConfirmTeach[] = _("Teach {STR_VAR_1} for\n{STR_VAR_2} GYM POINTS?");
static const u8 sText_ConfirmTeachFree[] = _("Teach {STR_VAR_1}?\nYour signature move is free!");
static const u8 sText_NotEnoughPoints[] = _("Not enough GYM POINTS!\n{STR_VAR_1} costs {STR_VAR_2}.");
static const u8 sText_CostFmt[] = _("COST: {STR_VAR_1}");
static const u8 sText_CostFree[] = _("COST: FREE");
static const u8 sText_PointsFmt[] = _("GP: {STR_VAR_2}");

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sWindowTemplates[] =
{
    [WIN_INFO] = {
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 16,
        .height = 12,
        .paletteNum = 15,
        .baseBlock = 0xA
    },
    [WIN_LIST] = {
        .bg = 1,
        .tilemapLeft = 19,
        .tilemapTop = 1,
        .width = 10,
        .height = 12,
        .paletteNum = 15,
        .baseBlock = 0xCA
    },
    [WIN_MSG] = {
        .bg = 1,
        .tilemapLeft = 4,
        .tilemapTop = 15,
        .width = 22,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x142
    },
    // Never drawn to directly; keeps a window alive on bg0 so RemoveWindow
    // never frees the shared bg0 tilemap buffer while the yes/no menu (the
    // only other bg0 window) comes and goes — freeing it corrupts the screen
    // once the heap block is reused (same trick as the Move Relearner's
    // "unused" RELEARNERWIN_YESNO).
    [WIN_YESNO_DUMMY] = {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 8,
        .width = 5,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x19A
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sYesNoWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 22,
    .tilemapTop = 8,
    .width = 5,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 0x19A
};

static const struct ScrollArrowsTemplate sListScrollArrowsTemplate =
{
    .firstArrowType = SCROLL_ARROW_UP,
    .firstX = 192,
    .firstY = 8,
    .secondArrowType = SCROLL_ARROW_DOWN,
    .secondX = 192,
    .secondY = 104,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 0,
    .tileTag = TAG_LIST_ARROWS,
    .palTag = TAG_LIST_ARROWS,
    .palNum = 0,
};

static void TMListCursorCallback(s32 itemIndex, bool8 onInit, struct ListMenu *list);

static const struct ListMenuTemplate sTMListMenuTemplate =
{
    .items = NULL,
    .moveCursorFunc = TMListCursorCallback,
    .itemPrintFunc = NULL,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = WIN_LIST,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NORMAL,
    .cursorKind = CURSOR_BLACK_ARROW,
    .textNarrowWidth = 68,
};

#define tMove data[2]

bool32 IsTMMoveUnlocked(u16 move)
{
    u32 i, j;

    for (i = 0; i < ARRAY_COUNT(sTmUnlockGroups); i++)
    {
        if (!FlagGet(sTmUnlockGroups[i].flag))
            continue;
        for (j = 0; sTmUnlockGroups[i].moves[j] != MOVE_UNAVAILABLE; j++)
        {
            if (sTmUnlockGroups[i].moves[j] == move)
                return TRUE;
        }
    }
    return GymChallenge_IsMoveUnlockedBySignature(move);
}

u32 GetTMTeachCost(u16 move)
{
    u32 price;

    if (move == GymChallenge_GetSignatureMove())
        return 0;
    price = GetItemPrice(GetTMHMItemIdFromMoveId(move));
    if (price == 0)
        price = GYM_TM_DEFAULT_COST;
    return price;
}

static void VBlankCB_TMMachine(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_OpenTMMachineFromStartMenu(void)
{
    sTMMachineScroll.listOffset = 0;
    sTMMachineScroll.listRow = 0;
    sPendingTeachMove = MOVE_NONE;
    CB2_InitTMMachine();
}

// Party menu exit callback: the tutor flow left gSpecialVar_Result TRUE only
// if the move was actually learned — that's when the points are spent.
static void CB2_ReturnToTMMachine(void)
{
    if (gSpecialVar_Result == TRUE && sPendingTeachMove != MOVE_NONE)
        GymChallenge_TrySpendPoints(GetTMTeachCost(sPendingTeachMove));
    sPendingTeachMove = MOVE_NONE;
    CB2_InitTMMachine();
}

static void BuildTMList(void)
{
    u32 i;

    sTMMachine->numMenuItems = 0;
    for (i = 1; i <= NUM_TECHNICAL_MACHINES; i++)
    {
        enum Move move = GetTMHMMoveId(i);

        if (move == MOVE_NONE || !IsTMMoveUnlocked(move))
            continue;
        sTMMachine->menuItems[sTMMachine->numMenuItems].name = GetMoveName(move);
        sTMMachine->menuItems[sTMMachine->numMenuItems].id = move;
        sTMMachine->numMenuItems++;
    }
    sTMMachine->menuItems[sTMMachine->numMenuItems].name = gText_Cancel;
    sTMMachine->menuItems[sTMMachine->numMenuItems].id = LIST_CANCEL;
    sTMMachine->numMenuItems++;

    gMultiuseListMenuTemplate = sTMListMenuTemplate;
    gMultiuseListMenuTemplate.totalItems = sTMMachine->numMenuItems;
    gMultiuseListMenuTemplate.items = sTMMachine->menuItems;
    gMultiuseListMenuTemplate.maxShowed = min(sTMMachine->numMenuItems, 6);
    sTMMachine->numToShowAtOnce = gMultiuseListMenuTemplate.maxShowed;

    if (sTMMachineScroll.listOffset + sTMMachineScroll.listRow >= sTMMachine->numMenuItems)
    {
        sTMMachineScroll.listOffset = 0;
        sTMMachineScroll.listRow = 0;
    }
}

static void InitTMMachineWindows(void)
{
    u32 i;

    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 1, BG_PLTT_ID(14));
    LoadPalette(gStandardMenuPalette, BG_PLTT_ID(15), PLTT_SIZE_4BPP);

    for (i = 0; i < ARRAY_COUNT(sWindowTemplates) - 1; i++)
        FillWindowPixelBuffer(i, PIXEL_FILL(1));

    PutWindowTilemap(WIN_INFO);
    PutWindowTilemap(WIN_LIST);
    PutWindowTilemap(WIN_MSG);
    DrawStdFrameWithCustomTileAndPalette(WIN_INFO, FALSE, 1, 0xE);
    DrawStdFrameWithCustomTileAndPalette(WIN_LIST, FALSE, 1, 0xE);
    DrawStdFrameWithCustomTileAndPalette(WIN_MSG, FALSE, 1, 0xE);
    ScheduleBgCopyTilemapToVram(1);
}

static void InitTMMachineBgs(void)
{
    ResetVramOamAndBgCntRegs();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
    ResetAllBgsCoordinates();
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 |
                                  DISPCNT_OBJ_1D_MAP |
                                  DISPCNT_OBJ_ON);
    ShowBg(0);
    ShowBg(1);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
}

static void CB2_InitTMMachine_Internal(void)
{
    switch (gMain.state)
    {
    case 0:
        ResetSpriteData();
        FreeAllSpritePalettes();
        ClearScheduledBgCopiesToVram();
        SetVBlankCallback(VBlankCB_TMMachine);
        gMain.state++;
        break;
    case 1:
        InitTMMachineBgs();
        InitTMMachineWindows();
        gMain.state++;
        break;
    case 2:
        BuildTMList();
        sTMMachine->listMenuTask = ListMenuInit(&gMultiuseListMenuTemplate, sTMMachineScroll.listOffset, sTMMachineScroll.listRow);
        gMain.state++;
        break;
    case 3:
        ShowSelectPrompt();
        SetBackdropFromColor(RGB_BLACK);
        BeginNormalPaletteFade(PALETTES_ALL, -2, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 4:
        UpdatePaletteFade();
        if (!gPaletteFade.active)
            gMain.state++;
        break;
    default:
        AddListScrollArrows();
        gTasks[sTMMachine->mainTask].func = Task_TMMachine_HandleInput;
        SetVBlankCallback(VBlankCB_TMMachine);
        SetMainCallback2(CB2_TMMachineMain);
        break;
    }
}

static void CB2_InitTMMachine(void)
{
    ResetTasks();
    sTMMachine = AllocZeroed(sizeof(*sTMMachine));
    sTMMachine->mainTask = CreateTask(TaskDummy, 1);
    sTMMachine->scrollArrowTask = TASK_NONE;
    gTasks[sTMMachine->mainTask].tMove = MOVE_NONE;
    SetMainCallback2(CB2_InitTMMachine_Internal);
}

static void CB2_TMMachineMain(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    RunTextPrinters();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void FreeTMMachineResources(void)
{
    RemoveListScrollArrows();
    DestroyListMenuTask(sTMMachine->listMenuTask, &sTMMachineScroll.listOffset, &sTMMachineScroll.listRow);
    FreeAllWindowBuffers();
    FREE_AND_SET_NULL(sTMMachine);
    ResetSpriteData();
    FreeAllSpritePalettes();
}

static void AddListScrollArrows(void)
{
    if (sTMMachine->scrollArrowTask == TASK_NONE)
    {
        gTempScrollArrowTemplate = sListScrollArrowsTemplate;
        gTempScrollArrowTemplate.fullyDownThreshold = sTMMachine->numMenuItems - sTMMachine->numToShowAtOnce;
        sTMMachine->scrollArrowTask = AddScrollIndicatorArrowPair(&gTempScrollArrowTemplate, &sTMMachineScroll.listOffset);
    }
}

static void RemoveListScrollArrows(void)
{
    if (sTMMachine->scrollArrowTask != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sTMMachine->scrollArrowTask);
        sTMMachine->scrollArrowTask = TASK_NONE;
    }
}

// Left panel: cost and wallet on the top row, then type/power/PP/accuracy
// and the description (layout mirrors the Move Relearner's battle panel).
static void PrintTMInfo(s32 move)
{
    s32 x;
    u8 buffer[32];
    const u8 *str;

    FillWindowPixelBuffer(WIN_INFO, PIXEL_FILL(1));

    ConvertIntToDecimalStringN(gStringVar2, GymChallenge_GetPoints(), STR_CONV_MODE_LEFT_ALIGN, MAX_MONEY_DIGITS);
    StringExpandPlaceholders(gStringVar4, sText_PointsFmt);
    x = GetStringRightAlignXOffset(FONT_SMALL, gStringVar4, 124);
    AddTextPrinterParameterized(WIN_INFO, FONT_SMALL, gStringVar4, x, 1, TEXT_SKIP_DRAW, NULL);

    if (move == LIST_CANCEL)
    {
        CopyWindowToVram(WIN_INFO, COPYWIN_GFX);
        return;
    }

    if (GetTMTeachCost(move) == 0)
    {
        StringExpandPlaceholders(gStringVar4, sText_CostFree);
    }
    else
    {
        ConvertIntToDecimalStringN(gStringVar1, GetTMTeachCost(move), STR_CONV_MODE_LEFT_ALIGN, MAX_MONEY_DIGITS);
        StringExpandPlaceholders(gStringVar4, sText_CostFmt);
    }
    AddTextPrinterParameterized(WIN_INFO, FONT_SMALL, gStringVar4, 4, 1, TEXT_SKIP_DRAW, NULL);

    str = gTypesInfo[GetMoveType(move)].name;
    AddTextPrinterParameterized(WIN_INFO, FONT_NORMAL, str, 4, 25, TEXT_SKIP_DRAW, NULL);

    str = gText_MoveRelearnerPower;
    x = GetStringRightAlignXOffset(FONT_NORMAL, str, 106);
    AddTextPrinterParameterized(WIN_INFO, FONT_NORMAL, str, x, 25, TEXT_SKIP_DRAW, NULL);

    if (GetMovePower(move) < 2)
    {
        str = gText_ThreeDashes;
    }
    else
    {
        ConvertIntToDecimalStringN(buffer, GetMovePower(move), STR_CONV_MODE_LEFT_ALIGN, 3);
        str = buffer;
    }
    AddTextPrinterParameterized(WIN_INFO, FONT_NORMAL, str, 106, 25, TEXT_SKIP_DRAW, NULL);

    str = gText_MoveRelearnerPP;
    AddTextPrinterParameterized(WIN_INFO, FONT_NORMAL, str, 4, 41, TEXT_SKIP_DRAW, NULL);
    x = 4 + GetStringWidth(FONT_NORMAL, gText_MoveRelearnerPP, 0);
    ConvertIntToDecimalStringN(buffer, GetMovePP(move), STR_CONV_MODE_LEFT_ALIGN, 2);
    AddTextPrinterParameterized(WIN_INFO, FONT_NORMAL, buffer, x, 41, TEXT_SKIP_DRAW, NULL);

    str = gText_MoveRelearnerAccuracy;
    x = GetStringRightAlignXOffset(FONT_NORMAL, str, 106);
    AddTextPrinterParameterized(WIN_INFO, FONT_NORMAL, str, x, 41, TEXT_SKIP_DRAW, NULL);

    if (GetMoveAccuracy(move) == 0)
    {
        str = gText_ThreeDashes;
    }
    else
    {
        ConvertIntToDecimalStringN(buffer, GetMoveAccuracy(move), STR_CONV_MODE_LEFT_ALIGN, 3);
        str = buffer;
    }
    AddTextPrinterParameterized(WIN_INFO, FONT_NORMAL, str, 106, 41, TEXT_SKIP_DRAW, NULL);

    AddTextPrinterParameterized(WIN_INFO, FONT_NARROW, GetMoveDescription(move), 0, 65, 0, NULL);
    CopyWindowToVram(WIN_INFO, COPYWIN_GFX);
}

static void TMListCursorCallback(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    if (onInit != TRUE)
        PlaySE(SE_SELECT);
    PrintTMInfo(itemIndex);
}

static void ShowSelectPrompt(void)
{
    FillWindowPixelBuffer(WIN_MSG, 0x11);
    AddTextPrinterParameterized(WIN_MSG, FONT_NORMAL, sText_SelectPrompt, 0, 1, 0, NULL);
}

static void PrintMessage(const u8 *message)
{
    StringExpandPlaceholders(gStringVar4, message);
    FillWindowPixelBuffer(WIN_MSG, PIXEL_FILL(1));
    gTextFlags.canABSpeedUpPrint = TRUE;
    AddTextPrinterParameterized2(WIN_MSG, FONT_NORMAL, gStringVar4, GetPlayerTextSpeedDelay(), NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, 3);
}

static void Task_TMMachine_HandleInput(u8 taskId)
{
    s32 itemId = ListMenu_ProcessInput(sTMMachine->listMenuTask);
    ListMenuGetScrollAndRow(sTMMachine->listMenuTask, &sTMMachineScroll.listOffset, &sTMMachineScroll.listRow);

    switch (itemId)
    {
    case LIST_NOTHING_CHOSEN:
        break;
    case LIST_CANCEL:
        PlaySE(SE_SELECT);
        RemoveListScrollArrows();
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_TMMachine_Quit;
        break;
    default:
        PlaySE(SE_SELECT);
        RemoveListScrollArrows();
        gTasks[taskId].tMove = itemId;
        StringCopy(gStringVar1, GetMoveName(itemId));
        u32 cost = GetTMTeachCost(itemId);
        ConvertIntToDecimalStringN(gStringVar2, cost, STR_CONV_MODE_LEFT_ALIGN, MAX_MONEY_DIGITS);
        if (cost > GymChallenge_GetPoints())
        {
            PrintMessage(sText_NotEnoughPoints);
            gTasks[taskId].func = Task_TMMachine_WaitMessageThenResume;
        }
        else
        {
            PrintMessage(cost == 0 ? sText_ConfirmTeachFree : sText_ConfirmTeach);
            gTasks[taskId].func = Task_TMMachine_WaitConfirmText;
        }
        break;
    }
}

static void Task_TMMachine_WaitConfirmText(u8 taskId)
{
    if (IsTextPrinterActiveOnWindow(WIN_MSG))
        return;
    CreateYesNoMenu(&sYesNoWindowTemplate, 1, 0xE, 0);
    gTasks[taskId].func = Task_TMMachine_HandleConfirmInput;
}

static void Task_TMMachine_HandleConfirmInput(u8 taskId)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0: // Yes
        sPendingTeachMove = gTasks[taskId].tMove;
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_TMMachine_FadeToPartyMenu;
        break;
    case 1: // No
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        ShowSelectPrompt();
        AddListScrollArrows();
        gTasks[taskId].func = Task_TMMachine_HandleInput;
        break;
    }
}

static void Task_TMMachine_WaitMessageThenResume(u8 taskId)
{
    if (IsTextPrinterActiveOnWindow(WIN_MSG))
        return;
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        ShowSelectPrompt();
        AddListScrollArrows();
        gTasks[taskId].func = Task_TMMachine_HandleInput;
    }
}

static void Task_TMMachine_FadeToPartyMenu(u8 taskId)
{
    if (gPaletteFade.active)
        return;
    gSpecialVar_0x8005 = sPendingTeachMove;
    FreeTMMachineResources();
    DestroyTask(taskId);
    SetMainCallback2(CB2_ChooseMonForTeach);
}

static void CB2_ChooseMonForTeach(void)
{
    ChooseMonForTMMachine(CB2_ReturnToTMMachine);
}

static void Task_TMMachine_Quit(u8 taskId)
{
    if (gPaletteFade.active)
        return;
    FreeTMMachineResources();
    DestroyTask(taskId);
    SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
}
