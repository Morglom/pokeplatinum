#include "overlay013/ov13_022264F4.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/battle_system.h"
#include "struct_decls/pc_boxes_decl.h"

#include "battle/battle_lib.h"
#include "battle/ov16_0223DF00.h"
#include "battle/ov16_0226DE44.h"
#include "overlay013/ov13_02227288.h"
#include "overlay013/ov13_02227A4C.h"
#include "overlay013/ov13_02227BDC.h"
#include "overlay013/ov13_02228128.h"
#include "overlay013/ov13_02228A38.h"
#include "overlay013/struct_ov13_022264F4.h"
#include "overlay013/struct_ov13_02227244.h"

#include "bag.h"
#include "bg_window.h"
#include "font.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "item.h"
#include "message.h"
#include "narc.h"
#include "palette.h"
#include "party.h"
#include "pc_boxes.h"
#include "pokemon.h"
#include "render_window.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "strbuf.h"
#include "string_template.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "touch_screen.h"
#include "unk_0200679C.h"
#include "unk_0200C440.h"

enum BattleBagTaskState {
    BATTLE_BAG_TASK_STATE_INITIALIZE = 0,
    BATTLE_BAG_TASK_STATE_MENU_SCREEN,
    BATTLE_BAG_TASK_STATE_POCKET_MENU_SCREEN,
    BATTLE_BAG_TASK_STATE_USE_ITEM_SCREEN,
    BATTLE_BAG_TASK_STATE_SETUP_MENU_SCREEN,
    BATTLE_BAG_TASK_STATE_SETUP_POCKET_MENU_SCREEN,
    BATTLE_BAG_TASK_STATE_SETUP_USE_ITEM_SCREEN,
    BATTLE_BAG_TASK_STATE_CHANGE_POCKET_PAGE,
    BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE,
    BATTLE_BAG_TASK_AWAITING_TEXT_FINISH,
    BATTLE_BAG_TASK_STATE_AWAITING_INPUT,
    BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION,
    BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL,
    BATTLE_BAG_TASK_STATE_EXIT,
    BATTLE_BAG_TASK_STATE_FINISH_TASK,
};

enum BattleBagMenuScreenButton {
    BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_HP_POCKET = 0,
    BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_STATUS_POCKET,
    BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_POKE_BALLS_POCKET,
    BATTLE_BAG_MENU_SCREEN_BUTTON_BATTLE_ITEMS_POCKET,
    BATTLE_BAG_MENU_SCREEN_BUTTON_LAST_USED_ITEM,
    BATTLE_BAG_MENU_SCREEN_BUTTON_CANCEL,
};

enum BattleBagPocketMenuScreenButton {
    BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_1 = 0,
    BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_2,
    BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_3,
    BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_4,
    BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_5,
    BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_6,
    BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_PREV_PAGE,
    BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_NEXT_PAGE,
    BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_CANCEL,
};

enum BattleBagUseItemScreenButton {
    BATTLE_BAG_USE_ITEM_SCREEN_BUTTON_USE = 0,
    BATTLE_BAG_USE_ITEM_SCREEN_BUTTON_CANCEL,
};

enum BattleBagCatchTutorialState {
    BATTLE_BAG_CATCH_TUTORIAL_STATE_MENU_SCREEN = 0,
    BATTLE_BAG_CATCH_TUTORIAL_STATE_SETUP_POCKET_MENU_SCREEN,
    BATTLE_BAG_CATCH_TUTORIAL_STATE_POCKET_MENU_SCREEN,
    BATTLE_BAG_CATCH_TUTORIAL_STATE_SETUP_USE_ITEM_SCREEN,
    BATTLE_BAG_CATCH_TUTORIAL_STATE_USE_ITEM_SCREEN,
};

#define POCKET_NEXT_PAGE 1
#define POCKET_PREV_PAGE -1

static void BattleBagTask_Tick(SysTask *param0, void *param1);
static enum BattleBagTaskState BattleBagTask_Initialize(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_MenuScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_PocketMenuScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_UseItemScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_SetupMenuScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_SetupPocketMenuScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_SetupUseItemScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_ChangePocketPage(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_ClearErrorMessage(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_AwaitingTextFinish(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_AwaitingInput(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_ScreenTransition(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_CatchTutorial(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_Exit(BattleBagTask *battleBagTask);
BOOL BattleBagTask_FinishTask(SysTask *task, BattleBagTask *battleBagTask);
static void InitializeBackground(BattleBagTask *battleBagTask);
static void CleanupBackground(BgConfig *param0);
static void ov13_02226FC4(BattleBagTask *battleBagTask);
static void InitializeMessageLoader(BattleBagTask *battleBagTask);
static void CleanupMessageLoader(BattleBagTask *battleBagTask);
static enum BattleBagTaskState ov13_02226A5C(BattleBagTask *battleBagTask);
static void ov13_02227118(BattleBagTask *battleBagTask, u8 screen);
static void ChangeBattleBagScreen(BattleBagTask *battleBagTask, u8 screen);
static int CheckTouchRectIsPressed(BattleBagTask *battleBagTask, const TouchScreenRect *rect);
static void UseBagItem(BattleSystem *battleSys, u16 item, u16 category, u32 heapID);

static const TouchScreenRect menuScreenTouchRects[] = {
    { 0x8, 0x4F, 0x0, 0x7F },
    { 0x50, 0x97, 0x0, 0x7F },
    { 0x8, 0x4F, 0x80, 0xFF },
    { 0x50, 0x97, 0x80, 0xFF },
    { 0x98, 0xBF, 0x0, 0xCF },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect pocketMenuScreenTouchRects[] = {
    { 0x8, 0x37, 0x0, 0x7F },
    { 0x8, 0x37, 0x80, 0xFF },
    { 0x38, 0x67, 0x0, 0x7F },
    { 0x38, 0x67, 0x80, 0xFF },
    { 0x68, 0x97, 0x0, 0x7F },
    { 0x68, 0x97, 0x80, 0xFF },
    { 0x98, 0xBF, 0x0, 0x27 },
    { 0x98, 0xBF, 0x28, 0x4F },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect useItemScreenTouchRects[] = {
    { 0x98, 0xBF, 0x0, 0xCF },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

void BattleBagTask_Start(UnkStruct_ov13_022264F4 *param0)
{
    BattleBagTask *battleBagTask = SysTask_GetParam(SysTask_StartAndAllocateParam(BattleBagTask_Tick, sizeof(BattleBagTask), 100, param0->heapID));
    memset(battleBagTask, 0, sizeof(BattleBagTask));

    battleBagTask->unk_00 = param0;
    battleBagTask->backGround = BattleSystem_BGL(param0->battleSystem);
    battleBagTask->palette = BattleSystem_PaletteSys(param0->battleSystem);
    battleBagTask->currentState = BATTLE_BAG_TASK_STATE_INITIALIZE;

    {
        BagCursor *bagCursor;
        u8 i;

        bagCursor = BattleSystem_BagCursor(param0->battleSystem);

        for (i = 0; i < BATTLE_BAG_POCKET_NUM; i++) {
            BagCursor_GetBattleCategoryPosition(bagCursor, i, &battleBagTask->unk_00->pocketCurrentPagePositions[i], &battleBagTask->unk_00->pocketCurrentPages[i]);
        }

        battleBagTask->unk_00->lastUsedItem = BagCursor_GetLastUsedBattleItem(bagCursor);
        battleBagTask->unk_00->lastUsedItemPocket = BagCursor_GetLastUsedBattleItemCategory(bagCursor);
    }

    IsLastUsedItemUsable(battleBagTask);

    if (BattleSystem_BattleType(battleBagTask->unk_00->battleSystem) & BATTLE_TYPE_CATCH_TUTORIAL) {
        battleBagTask->unk_00->isCatchTutorial = TRUE;
    }
}

static void BattleBagTask_Tick(SysTask *task, void *taskParam)
{
    BattleBagTask *battleBagTask = (BattleBagTask *)taskParam;

    switch (battleBagTask->currentState) {
    case BATTLE_BAG_TASK_STATE_INITIALIZE:
        battleBagTask->currentState = BattleBagTask_Initialize(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_MENU_SCREEN:
        battleBagTask->currentState = BattleBagTask_MenuScreen(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_POCKET_MENU_SCREEN:
        battleBagTask->currentState = BattleBagTask_PocketMenuScreen(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_USE_ITEM_SCREEN:
        battleBagTask->currentState = BattleBagTask_UseItemScreen(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_SETUP_MENU_SCREEN:
        battleBagTask->currentState = BattleBagTask_SetupMenuScreen(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_SETUP_POCKET_MENU_SCREEN:
        battleBagTask->currentState = BattleBagTask_SetupPocketMenuScreen(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_SETUP_USE_ITEM_SCREEN:
        battleBagTask->currentState = BattleBagTask_SetupUseItemScreen(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_CHANGE_POCKET_PAGE:
        battleBagTask->currentState = BattleBagTask_ChangePocketPage(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE:
        battleBagTask->currentState = BattleBagTask_ClearErrorMessage(battleBagTask);
        break;
    case BATTLE_BAG_TASK_AWAITING_TEXT_FINISH:
        battleBagTask->currentState = BattleBagTask_AwaitingTextFinish(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_AWAITING_INPUT:
        battleBagTask->currentState = BattleBagTask_AwaitingInput(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION:
        battleBagTask->currentState = BattleBagTask_ScreenTransition(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL:
        battleBagTask->currentState = BattleBagTask_CatchTutorial(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_EXIT:
        battleBagTask->currentState = BattleBagTask_Exit(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_FINISH_TASK:
        if (BattleBagTask_FinishTask(task, battleBagTask) == TRUE) {
            return;
        }
    }

    ov13_02228848(battleBagTask);
    SpriteSystem_DrawSprites(battleBagTask->unk_30C);
}

static enum BattleBagTaskState BattleBagTask_Initialize(BattleBagTask *battleBagTask)
{
    G2S_BlendNone();

    battleBagTask->cursor = MakeBattleSubMenuCursor(battleBagTask->unk_00->heapID);

    InitializeBackground(battleBagTask);
    ov13_02226FC4(battleBagTask);
    InitializeMessageLoader(battleBagTask);
    Font_InitManager(FONT_SUBSCREEN, battleBagTask->unk_00->heapID);

    battleBagTask->currentBattleBagPocket = (u8)BagCursor_GetBattleCurrentCategory(BattleSystem_BagCursor(battleBagTask->unk_00->battleSystem));

    RefreshBagSubMenus(battleBagTask);
    ov13_02228924(battleBagTask, battleBagTask->currentScreen);
    ov13_02227288(battleBagTask);
    DrawInBattleBagScreen(battleBagTask, battleBagTask->currentScreen);
    ov13_02227BDC(battleBagTask);
    RenderBattleBagScreenSprites(battleBagTask, battleBagTask->currentScreen);

    if (battleBagTask->unk_00->unk_25 != FALSE) {
        SetBattlePartyBagCursorVisiblity(battleBagTask->cursor, TRUE);
    }

    ov13_02228008(battleBagTask, battleBagTask->currentScreen);
    ov13_022280F0(battleBagTask, battleBagTask->currentScreen);
    PaletteData_StartFade(battleBagTask->palette, (0x2 | 0x8), 0xffff, -8, 16, 0, 0);

    if (battleBagTask->unk_00->isCatchTutorial == TRUE) {
        return BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL;
    }

    return BATTLE_BAG_TASK_STATE_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_MenuScreen(BattleBagTask *battleBagTask)
{
    if (PaletteData_GetSelectedBuffersMask(battleBagTask->palette) != 0) {
        return BATTLE_BAG_TASK_STATE_MENU_SCREEN;
    }

    enum BattleBagMenuScreenButton menuButtonPressed = CheckTouchRectIsPressed(battleBagTask, menuScreenTouchRects);

    if (menuButtonPressed == TOUCHSCREEN_INPUT_NONE) {
        menuButtonPressed = CheckBattleSubMenuCursorInputs(battleBagTask->cursor);

        if (menuButtonPressed == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            menuButtonPressed = BATTLE_BAG_MENU_SCREEN_BUTTON_CANCEL;
        }
    } else {
        DisableBattleBagCursor(battleBagTask);
    }

    switch (menuButtonPressed) {
    case BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_HP_POCKET:
    case BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_STATUS_POCKET:
    case BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_POKE_BALLS_POCKET:
    case BATTLE_BAG_MENU_SCREEN_BUTTON_BATTLE_ITEMS_POCKET:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        battleBagTask->currentBattleBagPocket = menuButtonPressed;
        battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_SETUP_POCKET_MENU_SCREEN;
        ov13_0222880C(battleBagTask, menuButtonPressed, 0);
        return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
    case BATTLE_BAG_MENU_SCREEN_BUTTON_LAST_USED_ITEM:
        if (battleBagTask->unk_00->lastUsedItem != ITEM_NONE) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->currentBattleBagPocket = battleBagTask->unk_00->lastUsedItemPocket;
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_SETUP_USE_ITEM_SCREEN;
            SetNavigationForLastUsedItem(battleBagTask);
            ov13_0222880C(battleBagTask, 4, 0);
            return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
        }
        break;
    case BATTLE_BAG_MENU_SCREEN_BUTTON_CANCEL:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        battleBagTask->unk_00->unk_1C = 0;
        battleBagTask->unk_00->unk_1E = 4;
        ov13_0222880C(battleBagTask, 5, 0);
        return BATTLE_BAG_TASK_STATE_EXIT;
    }

    return BATTLE_BAG_TASK_STATE_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_PocketMenuScreen(BattleBagTask *battleBagTask)
{
    enum BattleBagPocketMenuScreenButton pocketMenuScreenButtonPressed = CheckTouchRectIsPressed(battleBagTask, pocketMenuScreenTouchRects);

    if (pocketMenuScreenButtonPressed == TOUCHSCREEN_INPUT_NONE) {
        pocketMenuScreenButtonPressed = CheckBattleSubMenuCursorInputs(battleBagTask->cursor);

        if (pocketMenuScreenButtonPressed == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            pocketMenuScreenButtonPressed = BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_CANCEL;
        }
    } else {
        DisableBattleBagCursor(battleBagTask);
    }

    switch (pocketMenuScreenButtonPressed) {
    case BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_1:
    case BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_2:
    case BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_3:
    case BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_4:
    case BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_5:
    case BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_ITEM_6:
        if (GetBagItemOnPage(battleBagTask, pocketMenuScreenButtonPressed) != ITEM_NONE) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->unk_00->pocketCurrentPagePositions[battleBagTask->currentBattleBagPocket] = (u8)pocketMenuScreenButtonPressed;
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_SETUP_USE_ITEM_SCREEN;
            ov13_0222880C(battleBagTask, 6 + pocketMenuScreenButtonPressed, 0);
            return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
        }
        break;
    case BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_PREV_PAGE:
        if (battleBagTask->numBattleBagPocketPages[battleBagTask->currentBattleBagPocket] != 0) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CHANGE_POCKET_PAGE;
            battleBagTask->queuedPocketPageChange = POCKET_PREV_PAGE;
            ov13_0222880C(battleBagTask, 12, 0);
            return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
        }
        break;
    case BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_NEXT_PAGE:
        if (battleBagTask->numBattleBagPocketPages[battleBagTask->currentBattleBagPocket] != 0) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CHANGE_POCKET_PAGE;
            battleBagTask->queuedPocketPageChange = POCKET_NEXT_PAGE;
            ov13_0222880C(battleBagTask, 13, 0);
            return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
        }
        break;
    case BATTLE_BAG_POCKET_MENU_SCREEN_BUTTON_CANCEL:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_SETUP_MENU_SCREEN;
        ov13_0222880C(battleBagTask, 14, 0);
        return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
    }

    return BATTLE_BAG_TASK_STATE_POCKET_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_ChangePocketPage(BattleBagTask *battleBagTask)
{
    s8 currentPage = battleBagTask->unk_00->pocketCurrentPages[battleBagTask->currentBattleBagPocket];

    battleBagTask->unk_00->pocketCurrentPagePositions[battleBagTask->currentBattleBagPocket] = 0;
    currentPage += battleBagTask->queuedPocketPageChange;

    if (currentPage > battleBagTask->numBattleBagPocketPages[battleBagTask->currentBattleBagPocket]) {
        battleBagTask->unk_00->pocketCurrentPages[battleBagTask->currentBattleBagPocket] = 0;
    } else if (currentPage < 0) {
        battleBagTask->unk_00->pocketCurrentPages[battleBagTask->currentBattleBagPocket] = battleBagTask->numBattleBagPocketPages[battleBagTask->currentBattleBagPocket];
    } else {
        battleBagTask->unk_00->pocketCurrentPages[battleBagTask->currentBattleBagPocket] = currentPage;
    }

    DrawBagSubMenuPage(battleBagTask);
    DrawBagSubMenuPageInfo(battleBagTask);
    RenderBattleBagScreenSprites(battleBagTask, battleBagTask->currentScreen);
    ov13_02228924(battleBagTask, battleBagTask->currentScreen);

    return BATTLE_BAG_TASK_STATE_POCKET_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_UseItemScreen(BattleBagTask *battleBagTask)
{
    enum BattleBagUseItemScreenButton useItemScreenButtonPressed = CheckTouchRectIsPressed(battleBagTask, useItemScreenTouchRects);

    if (useItemScreenButtonPressed == TOUCHSCREEN_INPUT_NONE) {
        useItemScreenButtonPressed = CheckBattleSubMenuCursorInputs(battleBagTask->cursor);

        if (useItemScreenButtonPressed == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            useItemScreenButtonPressed = BATTLE_BAG_USE_ITEM_SCREEN_BUTTON_CANCEL;
        }
    } else {
        DisableBattleBagCursor(battleBagTask);
    }

    switch (useItemScreenButtonPressed) {
    case BATTLE_BAG_USE_ITEM_SCREEN_BUTTON_USE:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        battleBagTask->unk_00->unk_1C = GetBagItemOnPage(battleBagTask, battleBagTask->unk_00->pocketCurrentPagePositions[battleBagTask->currentBattleBagPocket]);
        battleBagTask->unk_00->unk_1E = battleBagTask->currentBattleBagPocket;
        ov13_0222880C(battleBagTask, 15, 0);
        return ov13_02226A5C(battleBagTask);
    case BATTLE_BAG_USE_ITEM_SCREEN_BUTTON_CANCEL:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_SETUP_POCKET_MENU_SCREEN;
        ov13_0222880C(battleBagTask, 16, 0);
        return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
    }

    return BATTLE_BAG_TASK_STATE_USE_ITEM_SCREEN;
}

static enum BattleBagTaskState ov13_02226A5C(BattleBagTask *battleBagTask)
{
    UnkStruct_ov13_022264F4 *v0 = battleBagTask->unk_00;

    if (battleBagTask->currentBattleBagPocket == ITEM_BATTLE_CATEGORY_BATTLE_ITEMS) {
        int v1 = GetSelectedPartySlot(battleBagTask);
        u32 v2 = Item_LoadParam(v0->unk_1C, ITEM_PARAM_BATTLE_USE_FUNC, v0->heapID);

        if ((v0->unk_18 != 0) && (v0->unk_1C != 55) && (v2 != 3)) {
            Pokemon *v3;
            Strbuf *v4;

            v3 = BattleSystem_PartyPokemon(v0->battleSystem, v0->battler, v1);
            v4 = MessageLoader_GetNewStrbuf(battleBagTask->messageLoader, 46);

            StringTemplate_SetNickname(battleBagTask->unk_14, 0, Pokemon_GetBoxPokemon(v3));
            StringTemplate_SetMoveName(battleBagTask->unk_14, 1, 373);
            StringTemplate_Format(battleBagTask->unk_14, battleBagTask->unk_18, v4);
            Strbuf_Free(v4);

            ov13_022279F4(battleBagTask);
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE;

            return BATTLE_BAG_TASK_AWAITING_TEXT_FINISH;
        }

        if (BattleSystem_UseBagItem(v0->battleSystem, v0->battler, v1, 0, v0->unk_1C) == TRUE) {
            UseBagItem(v0->battleSystem, v0->unk_1C, battleBagTask->currentBattleBagPocket, v0->heapID);
            return BATTLE_BAG_TASK_STATE_EXIT;
        } else if (v2 == 3) {
            if (!(BattleSystem_BattleType(v0->battleSystem) & BATTLE_TYPE_TRAINER)) {
                UseBagItem(v0->battleSystem, v0->unk_1C, battleBagTask->currentBattleBagPocket, v0->heapID);
                return BATTLE_BAG_TASK_STATE_EXIT;
            } else {
                MessageLoader *v5;
                Strbuf *v6;

                v5 = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_COMMON_STRINGS, v0->heapID);
                v6 = MessageLoader_GetNewStrbuf(v5, 36);
                StringTemplate_SetPlayerName(battleBagTask->unk_14, 0, v0->unk_04);
                StringTemplate_Format(battleBagTask->unk_14, battleBagTask->unk_18, v6);
                Strbuf_Free(v6);
                MessageLoader_Free(v5);
                ov13_022279F4(battleBagTask);
                battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE;
                return BATTLE_BAG_TASK_AWAITING_TEXT_FINISH;
            }
        } else {
            MessageLoader_GetStrbuf(battleBagTask->messageLoader, 34, battleBagTask->unk_18);
            ov13_022279F4(battleBagTask);
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE;
            return BATTLE_BAG_TASK_AWAITING_TEXT_FINISH;
        }
    } else if (battleBagTask->currentBattleBagPocket == ITEM_BATTLE_CATEGORY_POKE_BALLS) {
        if (v0->unk_22 == 1) {
            MessageLoader_GetStrbuf(battleBagTask->messageLoader, 44, battleBagTask->unk_18);
            ov13_022279F4(battleBagTask);
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE;
            return BATTLE_BAG_TASK_AWAITING_TEXT_FINISH;
        }

        if (v0->unk_23 == 1) {
            MessageLoader_GetStrbuf(battleBagTask->messageLoader, 47, battleBagTask->unk_18);
            ov13_022279F4(battleBagTask);
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE;
            return BATTLE_BAG_TASK_AWAITING_TEXT_FINISH;
        }

        if (v0->unk_24 == 1) {
            MessageLoader_GetStrbuf(battleBagTask->messageLoader, 48, battleBagTask->unk_18);
            ov13_022279F4(battleBagTask);
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE;
            return BATTLE_BAG_TASK_AWAITING_TEXT_FINISH;
        }

        {
            Party *v7 = BattleSystem_Party(v0->battleSystem, v0->battler);
            PCBoxes *v8 = ov16_0223E228(v0->battleSystem);

            if ((Party_GetCurrentCount(v7) == 6) && (PCBoxes_FirstEmptyBox(v8) == 18)) {
                MessageLoader_GetStrbuf(battleBagTask->messageLoader, 45, battleBagTask->unk_18);
                ov13_022279F4(battleBagTask);
                battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE;
                return BATTLE_BAG_TASK_AWAITING_TEXT_FINISH;
            }
        }
    }

    return BATTLE_BAG_TASK_STATE_EXIT;
}

static enum BattleBagTaskState BattleBagTask_SetupMenuScreen(BattleBagTask *battleBagTask)
{
    ChangeBattleBagScreen(battleBagTask, IN_BATTLE_BAG_SCREEN_INDEX_BAG_MENU);
    return BATTLE_BAG_TASK_STATE_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_SetupPocketMenuScreen(BattleBagTask *battleBagTask)
{
    ChangeBattleBagScreen(battleBagTask, IN_BATTLE_BAG_SCREEN_INDEX_BAG_SUB_MENU);
    return BATTLE_BAG_TASK_STATE_POCKET_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_SetupUseItemScreen(BattleBagTask *battleBagTask)
{
    ChangeBattleBagScreen(battleBagTask, IN_BATTLE_BAG_SCREEN_INDEX_USE_BAG_ITEM);
    return BATTLE_BAG_TASK_STATE_USE_ITEM_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_ClearErrorMessage(BattleBagTask *battleBagTask)
{
    Window_EraseMessageBox(&battleBagTask->messageBoxWindow, FALSE);
    return BATTLE_BAG_TASK_STATE_USE_ITEM_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_AwaitingTextFinish(BattleBagTask *battleBagTask)
{
    if (Text_IsPrinterActive(battleBagTask->textPrinter) == FALSE) {
        return BATTLE_BAG_TASK_STATE_AWAITING_INPUT;
    }

    return BATTLE_BAG_TASK_AWAITING_TEXT_FINISH;
}

static enum BattleBagTaskState BattleBagTask_AwaitingInput(BattleBagTask *battleBagTask)
{
    if (JOY_NEW(PAD_BUTTON_A | PAD_BUTTON_B) || TouchScreen_Tapped() == TRUE) {
        return battleBagTask->queuedState;
    }

    return BATTLE_BAG_TASK_STATE_AWAITING_INPUT;
}

static enum BattleBagTaskState BattleBagTask_ScreenTransition(BattleBagTask *battleBagTask)
{
    if (battleBagTask->unk_113E == 2) {
        return battleBagTask->queuedState;
    }

    return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
}

static enum BattleBagTaskState BattleBagTask_Exit(BattleBagTask *battleBagTask)
{
    PaletteData_StartFade(battleBagTask->palette, (0x2 | 0x8), 0xffff, -8, 0, 16, 0);
    return BATTLE_BAG_TASK_STATE_FINISH_TASK;
}

BOOL BattleBagTask_FinishTask(SysTask *task, BattleBagTask *battleBagTask)
{
    if (PaletteData_GetSelectedBuffersMask(battleBagTask->palette) != 0) {
        return FALSE;
    }

    ov13_02227E08(battleBagTask);
    ClearBattleBagWindows(battleBagTask);
    CleanupMessageLoader(battleBagTask);
    CleanupBackground(battleBagTask->backGround);

    battleBagTask->unk_00->unk_25 = IsBattleSubMenuCursorVisible(battleBagTask->cursor);

    DeleteBattleSubMenuCursor(battleBagTask->cursor);
    Font_Free(FONT_SUBSCREEN);

    if (battleBagTask->unk_00->unk_1C != ITEM_NONE) {
        BagCursor *bagCursor;
        u8 i;

        bagCursor = BattleSystem_BagCursor(battleBagTask->unk_00->battleSystem);

        for (i = 0; i < BATTLE_BAG_POCKET_NUM; i++) {
            BagCursor_SetBattleCategoryPosition(bagCursor, i, battleBagTask->unk_00->pocketCurrentPagePositions[i], battleBagTask->unk_00->pocketCurrentPages[i]);
        }

        BagCursor_SetBattleCurrentCategory(bagCursor, battleBagTask->currentBattleBagPocket);
    }

    battleBagTask->unk_00->unk_26 = 1;
    SysTask_FinishAndFreeParam(task);

    return TRUE;
}

static enum BattleBagTaskState BattleBagTask_CatchTutorial(BattleBagTask *battleBagTask)
{
    if (PaletteData_GetSelectedBuffersMask(battleBagTask->palette) != 0) {
        return BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL;
    }

    switch (battleBagTask->catchTutorialState) {
    case BATTLE_BAG_CATCH_TUTORIAL_STATE_MENU_SCREEN:
        if (ov16_0226DFD4(battleBagTask->unk_38) == 1) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->currentBattleBagPocket = ITEM_BATTLE_CATEGORY_POKE_BALLS;
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL;
            ov13_0222880C(battleBagTask, 2, 0);
            battleBagTask->unk_115A = 0;
            battleBagTask->catchTutorialState++;
            return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
        } else {
            battleBagTask->unk_115A++;
        }
        break;
    case BATTLE_BAG_CATCH_TUTORIAL_STATE_SETUP_POCKET_MENU_SCREEN:
        BattleBagTask_SetupPocketMenuScreen(battleBagTask);
        battleBagTask->catchTutorialState++;
        break;
    case BATTLE_BAG_CATCH_TUTORIAL_STATE_POCKET_MENU_SCREEN:
        if (ov16_0226DFD4(battleBagTask->unk_38) == 1) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->unk_00->pocketCurrentPagePositions[battleBagTask->currentBattleBagPocket] = IN_BATTLE_BAG_SUB_MENU_INDEX_HP_PP_RESTORE;
            battleBagTask->queuedState = BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL;
            ov13_0222880C(battleBagTask, 6, 0);
            battleBagTask->unk_115A = 0;
            battleBagTask->catchTutorialState++;
            return BATTLE_BAG_TASK_STATE_SCREEN_TRANSITION;
        } else {
            battleBagTask->unk_115A++;
        }
        break;
    case BATTLE_BAG_CATCH_TUTORIAL_STATE_SETUP_USE_ITEM_SCREEN:
        BattleBagTask_SetupUseItemScreen(battleBagTask);
        battleBagTask->catchTutorialState++;
        break;
    case BATTLE_BAG_CATCH_TUTORIAL_STATE_USE_ITEM_SCREEN:
        if (ov16_0226DFD4(battleBagTask->unk_38) == 1) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->unk_00->unk_1C = GetBagItemOnPage(battleBagTask, battleBagTask->unk_00->pocketCurrentPagePositions[battleBagTask->currentBattleBagPocket]);
            battleBagTask->unk_00->unk_1E = battleBagTask->currentBattleBagPocket;
            ov13_0222880C(battleBagTask, 15, 0);
            return ov13_02226A5C(battleBagTask);
        } else {
            battleBagTask->unk_115A++;
        }
        break;
    }

    return BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL;
}

static void InitializeBackground(BattleBagTask *battleBagTask)
{
    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D,
        };

        SetScreenGraphicsModes(&v0, DS_SCREEN_SUB);
    }

    {
        BgTemplate v1 = {
            0,
            0,
            0x2000,
            0,
            BG_SCREEN_SIZE_512x512,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xd000,
            GX_BG_CHARBASE_0x00000,
            GX_BG_EXTPLTT_23,
            3,
            0,
            0,
            FALSE
        };

        Bg_InitFromTemplate(battleBagTask->backGround, BG_LAYER_SUB_2, &v1, BG_TYPE_STATIC);
    }

    {
        BgTemplate v2 = {
            0,
            0,
            0x800,
            0,
            BG_SCREEN_SIZE_256x256,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xf800,
            GX_BG_CHARBASE_0x10000,
            GX_BG_EXTPLTT_01,
            1,
            0,
            0,
            FALSE
        };

        Bg_InitFromTemplate(battleBagTask->backGround, BG_LAYER_SUB_1, &v2, BG_TYPE_STATIC);
        Bg_ClearTilemap(battleBagTask->backGround, BG_LAYER_SUB_1);
    }

    {
        BgTemplate v3 = {
            0,
            0,
            0x800,
            0,
            BG_SCREEN_SIZE_256x256,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xf000,
            GX_BG_CHARBASE_0x00000,
            GX_BG_EXTPLTT_01,
            0,
            0,
            0,
            FALSE
        };

        Bg_InitFromTemplate(battleBagTask->backGround, BG_LAYER_SUB_0, &v3, BG_TYPE_STATIC);
        Bg_ClearTilemap(battleBagTask->backGround, BG_LAYER_SUB_0);
    }

    Bg_ClearTilesRange(BG_LAYER_SUB_1, 32, 0, battleBagTask->unk_00->heapID);
    Bg_ClearTilesRange(BG_LAYER_SUB_0, 32, 0, battleBagTask->unk_00->heapID);
    Bg_ScheduleTilemapTransfer(battleBagTask->backGround, BG_LAYER_SUB_1);
    Bg_ScheduleTilemapTransfer(battleBagTask->backGround, BG_LAYER_SUB_0);
}

static void CleanupBackground(BgConfig *background)
{
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ, FALSE);
    Bg_FreeTilemapBuffer(background, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(background, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(background, BG_LAYER_SUB_2);
}

static void ov13_02226FC4(BattleBagTask *battleBagTask)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_BATTLE__GRAPHIC__B_BAG_GRA, battleBagTask->unk_00->heapID);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 2, battleBagTask->backGround, 6, 0, 0, 0, battleBagTask->unk_00->heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 0, battleBagTask->backGround, 6, 0, 0, 0, battleBagTask->unk_00->heapID);

    {
        NNSG2dScreenData *v1;
        void *v2;
        u16 *v3;

        v2 = NARC_AllocAndReadWholeMember(v0, 1, battleBagTask->unk_00->heapID);
        NNS_G2dGetUnpackedScreenData(v2, &v1);
        v3 = (u16 *)v1->rawData;
        ov13_02228128(battleBagTask, v3);
        Heap_FreeToHeap(v2);
    }

    NARC_dtor(v0);
    PaletteData_LoadBufferFromFileStart(battleBagTask->palette, 77, 3, battleBagTask->unk_00->heapID, 1, 0x20 * 12, 0);
    PaletteData_LoadBufferFromFileStart(battleBagTask->palette, 14, 7, battleBagTask->unk_00->heapID, 1, 0x20, 15 * 16);

    {
        int v4 = ov16_0223EDE0(battleBagTask->unk_00->battleSystem);

        Graphics_LoadTilesToBgLayer(38, GetMessageBoxTilesNARCMember(v4), battleBagTask->backGround, 4, 1024 - (18 + 12), 0, 0, battleBagTask->unk_00->heapID);
        PaletteData_LoadBufferFromFileStart(battleBagTask->palette, 38, GetMessageBoxPaletteNARCMember(v4), battleBagTask->unk_00->heapID, 1, 0x20, 14 * 16);
    }
}

static void InitializeMessageLoader(BattleBagTask *battleBagTask)
{
    battleBagTask->messageLoader = MessageLoader_Init(MESSAGE_LOADER_BANK_HANDLE, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0002, battleBagTask->unk_00->heapID);
    battleBagTask->unk_0C = sub_0200C440(15, 14, 0, battleBagTask->unk_00->heapID);
    battleBagTask->unk_14 = StringTemplate_Default(battleBagTask->unk_00->heapID);
    battleBagTask->unk_18 = Strbuf_Init(512, battleBagTask->unk_00->heapID);
}

static void CleanupMessageLoader(BattleBagTask *battleBagTask)
{
    MessageLoader_Free(battleBagTask->messageLoader);
    sub_0200C560(battleBagTask->unk_0C);
    StringTemplate_Free(battleBagTask->unk_14);
    Strbuf_Free(battleBagTask->unk_18);
}

static void ov13_02227118(BattleBagTask *battleBagTask, u8 screen)
{
    switch (screen) {
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_MENU:
        Bg_ScheduleScroll(battleBagTask->backGround, 6, 0, 0);
        Bg_ScheduleScroll(battleBagTask->backGround, 6, 3, 0);
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_SUB_MENU:
        Bg_ScheduleScroll(battleBagTask->backGround, 6, 0, 256);
        Bg_ScheduleScroll(battleBagTask->backGround, 6, 3, 0);
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_USE_BAG_ITEM:
        Bg_ScheduleScroll(battleBagTask->backGround, 6, 0, 0);
        Bg_ScheduleScroll(battleBagTask->backGround, 6, 3, 256);
        break;
    }
}

static void ov13_0222717C(BattleBagTask *battleBagTask, u8 screen)
{
    if (screen != IN_BATTLE_BAG_SCREEN_INDEX_USE_BAG_ITEM) {
        return;
    }

    Bg_ChangeTilemapRectPalette(battleBagTask->backGround, 6, 2, 35, 28, 4, 8 + battleBagTask->currentBattleBagPocket);
    Bg_ChangeTilemapRectPalette(battleBagTask->backGround, 6, 2, 40, 28, 8, 8 + battleBagTask->currentBattleBagPocket);
}

static void ChangeBattleBagScreen(BattleBagTask *battleBagTask, u8 screen)
{
    ov13_0222717C(battleBagTask, screen);
    ov13_02227118(battleBagTask, screen);

    Bg_ScheduleFillTilemap(battleBagTask->backGround, 4, 0);
    Bg_ScheduleFillTilemap(battleBagTask->backGround, 5, 0);

    ClearInBattleBagScreen(battleBagTask);
    InitializeInBattleBagScreen(battleBagTask, screen);
    DrawInBattleBagScreen(battleBagTask, screen);
    ov13_02228924(battleBagTask, screen);
    ov13_02228008(battleBagTask, screen);
    ov13_022280F0(battleBagTask, screen);

    battleBagTask->currentScreen = screen;

    RenderBattleBagScreenSprites(battleBagTask, battleBagTask->currentScreen);
}

static int CheckTouchRectIsPressed(BattleBagTask *battleBagTask, const TouchScreenRect *rect)
{
    int isPressed = TouchScreen_CheckRectanglePressed(rect);
    return isPressed;
}

int GetSelectedPartySlot(BattleBagTask *battleBagTask)
{
    int slot = BattleContext_Get(battleBagTask->unk_00->battleSystem, BattleSystem_Context(battleBagTask->unk_00->battleSystem), BATTLECTX_SELECTED_PARTY_SLOT, battleBagTask->unk_00->battler);
    return slot;
}

static void UseBagItem(BattleSystem *battleSys, u16 item, u16 category, u32 heapID)
{
    Bag_TryRemoveItem(BattleSystem_Bag(battleSys), item, 1, heapID);
    Bag_SetLastBattleItemUsed(BattleSystem_BagCursor(battleSys), item, category);
}
