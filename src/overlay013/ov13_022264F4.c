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
    BATTLE_BAG_TASK_STATE_SCROLL_POCKET_PAGE,
    BATTLE_BAG_TASK_STATE_CLEAR_ERROR_MESSAGE,
    BATTLE_BAG_TASK_AWAITING_TEXT_FINISH,
    BATTLE_BAG_TASK_STATE_AWAITING_INPUT,
    IN_BATTLE_BAG_TRANSITION_INDEX_SOME_TYPE_OF_QUEUE,
    BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL,
    BATTLE_BAG_TASK_STATE_EXIT_FADE_OUT,
    BATTLE_BAG_TASK_STATE_FINISH_TASK,
};

enum BattleBagCatchTutorialState {
    BATTLE_BAG_CATCH_TUTORIAL_STATE = 0,
};

enum BattleBagMenuScreenButton {
    BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_HP_POCKET = 0,
    BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_STATUS_POCKET,
    BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_POKE_BALLS_POCKET,
    BATTLE_BAG_MENU_SCREEN_BUTTON_BATTLE_ITEMS_POCKET,
    BATTLE_BAG_MENU_SCREEN_BUTTON_LAST_USED_ITEM,
    BATTLE_BAG_MENU_SCREEN_BUTTON_CANCEL,
};

static void BattleBagTask_Tick(SysTask *param0, void *param1);
static enum BattleBagTaskState BattleBagTask_Initialize(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_MenuScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_PocketMenuScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_UseItemScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_SetupMenuScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_SetupPocketMenuScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_SetupUseItemScreen(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_ScrollPocketPage(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_ClearErrorMessage(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_AwaitingTextFinish(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_AwaitingInput(BattleBagTask *battleBagTask);
static enum BattleBagTaskState SomeTypeOfQueue(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_CatchTutorial(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_ExitFadeOut(BattleBagTask *battleBagTask);
static enum BattleBagTaskState BattleBagTask_FinishTask(SysTask *task, BattleBagTask *battleBagTask);
static void ov13_02226ED0(BattleBagTask *battleBagTask);
static void ov13_02226F9C(BgConfig *param0);
static void ov13_02226FC4(BattleBagTask *battleBagTask);
static void ov13_022270B8(BattleBagTask *battleBagTask);
static void ov13_022270F8(BattleBagTask *battleBagTask);
static enum BattleBagTaskState ov13_02226A5C(BattleBagTask *battleBagTask);
static void ov13_02227118(BattleBagTask *battleBagTask, u8 param1);
static void ChangeInBattleBagScreen(BattleBagTask *battleBagTask, u8 param1);
static int CheckTouchRectIsPressed(BattleBagTask *battleBagTask, const TouchScreenRect *rect);
static void ov13_02227260(BattleSystem *battleSys, u16 item, u16 category, u32 heapID);

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
    battleBagTask->unk_04 = BattleSystem_BGL(param0->unk_00);
    battleBagTask->unk_08 = BattleSystem_PaletteSys(param0->unk_00);
    battleBagTask->currentState = BATTLE_BAG_TASK_STATE_INITIALIZE;

    {
        BagCursor *bagCursor;
        u8 i;

        bagCursor = BattleSystem_BagCursor(param0->unk_00);

        for (i = 0; i < BATTLE_BAG_POCKET_NUM; i++) {
            BagCursor_GetBattleCategoryPosition(bagCursor, i, &battleBagTask->unk_00->pocketCurrentPagePositions[i], &battleBagTask->unk_00->pocketCurrentPages[i]);
        }

        battleBagTask->unk_00->lastUsedItem = BagCursor_GetLastUsedBattleItem(bagCursor);
        battleBagTask->unk_00->lastUsedItemPocket = BagCursor_GetLastUsedBattleItemCategory(bagCursor);
    }

    IsLastUsedItemUsable(battleBagTask);

    if (BattleSystem_BattleType(battleBagTask->unk_00->unk_00) & BATTLE_TYPE_CATCH_TUTORIAL) {
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
    case BATTLE_BAG_TASK_STATE_SCROLL_POCKET_PAGE:
        battleBagTask->currentState = BattleBagTask_ScrollPocketPage(battleBagTask);
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
    case IN_BATTLE_BAG_TRANSITION_INDEX_SOME_TYPE_OF_QUEUE:
        battleBagTask->currentState = SomeTypeOfQueue(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL:
        battleBagTask->currentState = BattleBagTask_CatchTutorial(battleBagTask);
        break;
    case BATTLE_BAG_TASK_STATE_EXIT_FADE_OUT:
        battleBagTask->currentState = BattleBagTask_ExitFadeOut(battleBagTask);
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

    battleBagTask->unk_34 = MakeBattleSubMenuCursor(battleBagTask->unk_00->heapID);

    ov13_02226ED0(battleBagTask);
    ov13_02226FC4(battleBagTask);
    ov13_022270B8(battleBagTask);
    Font_InitManager(FONT_SUBSCREEN, battleBagTask->unk_00->heapID);

    battleBagTask->currentBattleBagPocket = (u8)BagCursor_GetBattleCurrentCategory(BattleSystem_BagCursor(battleBagTask->unk_00->unk_00));

    RefreshBagSubMenus(battleBagTask);
    ov13_02228924(battleBagTask, battleBagTask->unk_114C);
    ov13_02227288(battleBagTask);
    DrawInBattleBagScreen(battleBagTask, battleBagTask->unk_114C);
    ov13_02227BDC(battleBagTask);
    ov13_02227E68(battleBagTask, battleBagTask->unk_114C);

    if (battleBagTask->unk_00->unk_25 != 0) {
        SetBattlePartyBagCursorVisiblity(battleBagTask->unk_34, 1);
    }

    ov13_02228008(battleBagTask, battleBagTask->unk_114C);
    ov13_022280F0(battleBagTask, battleBagTask->unk_114C);
    PaletteData_StartFade(battleBagTask->unk_08, (0x2 | 0x8), 0xffff, -8, 16, 0, 0);

    if (battleBagTask->unk_00->isCatchTutorial == TRUE) {
        return BATTLE_BAG_TASK_STATE_CATCH_TUTORIAL;
    }

    return BATTLE_BAG_TASK_STATE_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_MenuScreen(BattleBagTask *battleBagTask)
{
    if (PaletteData_GetSelectedBuffersMask(battleBagTask->unk_08) != 0) {
        return BATTLE_BAG_TASK_STATE_MENU_SCREEN;
    }

    {
        enum BattleBagMenuScreenButton v0 = CheckTouchRectIsPressed(battleBagTask, menuScreenTouchRects);

        if (v0 == TOUCHSCREEN_INPUT_NONE) {
            v0 = CheckBattleSubMenuCursorInputs(battleBagTask->unk_34);

            if (v0 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
                v0 = BATTLE_BAG_MENU_SCREEN_BUTTON_CANCEL;
            }
        } else {
            ov13_02228050(battleBagTask);
        }

        switch (v0) {
        case BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_HP_POCKET:
        case BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_STATUS_POCKET:
        case BATTLE_BAG_MENU_SCREEN_BUTTON_RECOVER_POKE_BALLS_POCKET:
        case BATTLE_BAG_MENU_SCREEN_BUTTON_BATTLE_ITEMS_POCKET:
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->currentBattleBagPocket = (enum ItemBattleCategory)v0;
            battleBagTask->unk_114B = BATTLE_BAG_TASK_STATE_SETUP_POCKET_MENU_SCREEN;
            ov13_0222880C(battleBagTask, v0, 0);
            return IN_BATTLE_BAG_TRANSITION_INDEX_SOME_TYPE_OF_QUEUE;
        case BATTLE_BAG_MENU_SCREEN_BUTTON_LAST_USED_ITEM:
            if (battleBagTask->unk_00->lastUsedItem != ITEM_NONE) {
                Sound_PlayEffect(SEQ_SE_DP_DECIDE);
                battleBagTask->currentBattleBagPocket = battleBagTask->unk_00->lastUsedItemPocket;
                battleBagTask->unk_114B = BATTLE_BAG_TASK_STATE_SETUP_USE_ITEM_SCREEN;
                SetNavigationForLastUsedItem(battleBagTask);
                ov13_0222880C(battleBagTask, 4, 0);
                return IN_BATTLE_BAG_TRANSITION_INDEX_SOME_TYPE_OF_QUEUE;
            }
            break;
        case BATTLE_BAG_MENU_SCREEN_BUTTON_CANCEL:
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->unk_00->unk_1C = 0;
            battleBagTask->unk_00->unk_1E = 4;
            ov13_0222880C(battleBagTask, 5, 0);
            return BATTLE_BAG_TASK_STATE_EXIT_FADE_OUT;
        }
    }

    return BATTLE_BAG_TASK_STATE_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_PocketMenuScreen(BattleBagTask *battleBagTask)
{
    {
        int v0 = CheckTouchRectIsPressed(battleBagTask, pocketMenuScreenTouchRects);

        if (v0 == TOUCHSCREEN_INPUT_NONE) {
            v0 = CheckBattleSubMenuCursorInputs(battleBagTask->unk_34);

            if (v0 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
                v0 = 8;
            }
        } else {
            ov13_02228050(battleBagTask);
        }

        switch (v0) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            if (GetBagItemOnPage(battleBagTask, v0) != ITEM_NONE) {
                Sound_PlayEffect(SEQ_SE_DP_DECIDE);
                battleBagTask->unk_00->pocketCurrentPagePositions[battleBagTask->currentBattleBagPocket] = (u8)v0;
                battleBagTask->unk_114B = 6;
                ov13_0222880C(battleBagTask, 6 + v0, 0);
                return 11;
            }
            break;
        case 6:
            if (battleBagTask->numBattleBagPocketPages[battleBagTask->currentBattleBagPocket] != 0) {
                Sound_PlayEffect(SEQ_SE_DP_DECIDE);
                battleBagTask->unk_114B = 7;
                battleBagTask->unk_114E = -1;
                ov13_0222880C(battleBagTask, 12, 0);
                return 11;
            }
            break;
        case 7:
            if (battleBagTask->numBattleBagPocketPages[battleBagTask->currentBattleBagPocket] != 0) {
                Sound_PlayEffect(SEQ_SE_DP_DECIDE);
                battleBagTask->unk_114B = 7;
                battleBagTask->unk_114E = 1;
                ov13_0222880C(battleBagTask, 13, 0);
                return 11;
            }
            break;
        case 8:
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->unk_114B = 4;
            ov13_0222880C(battleBagTask, 14, 0);
            return 11;
        }
    }

    return 2;
}

static enum BattleBagTaskState BattleBagTask_ScrollPocketPage(BattleBagTask *battleBagTask)
{
    s8 currentPage = battleBagTask->unk_00->pocketCurrentPages[battleBagTask->currentBattleBagPocket];

    battleBagTask->unk_00->pocketCurrentPagePositions[battleBagTask->currentBattleBagPocket] = 0;
    currentPage += battleBagTask->unk_114E;

    if (currentPage > battleBagTask->numBattleBagPocketPages[battleBagTask->currentBattleBagPocket]) {
        battleBagTask->unk_00->pocketCurrentPages[battleBagTask->currentBattleBagPocket] = 0;
    } else if (currentPage < 0) {
        battleBagTask->unk_00->pocketCurrentPages[battleBagTask->currentBattleBagPocket] = battleBagTask->numBattleBagPocketPages[battleBagTask->currentBattleBagPocket];
    } else {
        battleBagTask->unk_00->pocketCurrentPages[battleBagTask->currentBattleBagPocket] = currentPage;
    }

    DrawBagSubMenuPage(battleBagTask);
    DrawBagSubMenuPageInfo(battleBagTask);
    ov13_02227E68(battleBagTask, battleBagTask->unk_114C);
    ov13_02228924(battleBagTask, battleBagTask->unk_114C);

    return BATTLE_BAG_TASK_STATE_POCKET_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_UseItemScreen(BattleBagTask *battleBagTask)
{
    {
        int v0 = CheckTouchRectIsPressed(battleBagTask, useItemScreenTouchRects);

        if (v0 == TOUCHSCREEN_INPUT_NONE) {
            v0 = CheckBattleSubMenuCursorInputs(battleBagTask->unk_34);

            if (v0 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
                v0 = 1;
            }
        } else {
            ov13_02228050(battleBagTask);
        }

        switch (v0) {
        case 0:
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->unk_00->unk_1C = GetBagItemOnPage(battleBagTask, battleBagTask->unk_00->pocketCurrentPagePositions[battleBagTask->currentBattleBagPocket]);
            battleBagTask->unk_00->unk_1E = battleBagTask->currentBattleBagPocket;
            ov13_0222880C(battleBagTask, 15, 0);
            return ov13_02226A5C(battleBagTask);
        case 1:
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->unk_114B = 5;
            ov13_0222880C(battleBagTask, 16, 0);
            return 11;
        }
    }

    return 3;
}

static enum BattleBagTaskState ov13_02226A5C(BattleBagTask *battleBagTask)
{
    UnkStruct_ov13_022264F4 *v0 = battleBagTask->unk_00;

    if (battleBagTask->currentBattleBagPocket == ITEM_BATTLE_CATEGORY_BATTLE_ITEMS) {
        int v1 = ov13_02227244(battleBagTask);
        u32 v2 = Item_LoadParam(v0->unk_1C, 7, v0->heapID);

        if ((v0->unk_18 != 0) && (v0->unk_1C != 55) && (v2 != 3)) {
            Pokemon *v3;
            Strbuf *v4;

            v3 = BattleSystem_PartyPokemon(v0->unk_00, v0->unk_10, v1);
            v4 = MessageLoader_GetNewStrbuf(battleBagTask->unk_10, 46);

            StringTemplate_SetNickname(battleBagTask->unk_14, 0, Pokemon_GetBoxPokemon(v3));
            StringTemplate_SetMoveName(battleBagTask->unk_14, 1, 373);
            StringTemplate_Format(battleBagTask->unk_14, battleBagTask->unk_18, v4);
            Strbuf_Free(v4);

            ov13_022279F4(battleBagTask);
            battleBagTask->unk_114B = 8;

            return 9;
        }

        if (BattleSystem_UseBagItem(v0->unk_00, v0->unk_10, v1, 0, v0->unk_1C) == TRUE) {
            ov13_02227260(v0->unk_00, v0->unk_1C, battleBagTask->currentBattleBagPocket, v0->heapID);
            return 13;
        } else if (v2 == 3) {
            if (!(BattleSystem_BattleType(v0->unk_00) & BATTLE_TYPE_TRAINER)) {
                ov13_02227260(v0->unk_00, v0->unk_1C, battleBagTask->currentBattleBagPocket, v0->heapID);
                return 13;
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
                battleBagTask->unk_114B = 8;
                return 9;
            }
        } else {
            MessageLoader_GetStrbuf(battleBagTask->unk_10, 34, battleBagTask->unk_18);
            ov13_022279F4(battleBagTask);
            battleBagTask->unk_114B = 8;
            return 9;
        }
    } else if (battleBagTask->currentBattleBagPocket == ITEM_BATTLE_CATEGORY_POKE_BALLS) {
        if (v0->unk_22 == 1) {
            MessageLoader_GetStrbuf(battleBagTask->unk_10, 44, battleBagTask->unk_18);
            ov13_022279F4(battleBagTask);
            battleBagTask->unk_114B = 8;
            return 9;
        }

        if (v0->unk_23 == 1) {
            MessageLoader_GetStrbuf(battleBagTask->unk_10, 47, battleBagTask->unk_18);
            ov13_022279F4(battleBagTask);
            battleBagTask->unk_114B = 8;
            return 9;
        }

        if (v0->unk_24 == 1) {
            MessageLoader_GetStrbuf(battleBagTask->unk_10, 48, battleBagTask->unk_18);
            ov13_022279F4(battleBagTask);
            battleBagTask->unk_114B = 8;
            return 9;
        }

        {
            Party *v7 = BattleSystem_Party(v0->unk_00, v0->unk_10);
            PCBoxes *v8 = ov16_0223E228(v0->unk_00);

            if ((Party_GetCurrentCount(v7) == 6) && (PCBoxes_FirstEmptyBox(v8) == 18)) {
                MessageLoader_GetStrbuf(battleBagTask->unk_10, 45, battleBagTask->unk_18);
                ov13_022279F4(battleBagTask);
                battleBagTask->unk_114B = 8;
                return 9;
            }
        }
    }

    return 13;
}

static enum BattleBagTaskState BattleBagTask_SetupMenuScreen(BattleBagTask *battleBagTask)
{
    ChangeInBattleBagScreen(battleBagTask, IN_BATTLE_BAG_SCREEN_INDEX_BAG_MENU);
    return BATTLE_BAG_TASK_STATE_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_SetupPocketMenuScreen(BattleBagTask *battleBagTask)
{
    ChangeInBattleBagScreen(battleBagTask, IN_BATTLE_BAG_SCREEN_INDEX_BAG_SUB_MENU);
    return BATTLE_BAG_TASK_STATE_POCKET_MENU_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_SetupUseItemScreen(BattleBagTask *battleBagTask)
{
    ChangeInBattleBagScreen(battleBagTask, IN_BATTLE_BAG_SCREEN_INDEX_USE_BAG_ITEM);
    return BATTLE_BAG_TASK_STATE_USE_ITEM_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_ClearErrorMessage(BattleBagTask *battleBagTask)
{
    Window_EraseMessageBox(&battleBagTask->unk_1C, FALSE);
    return BATTLE_BAG_TASK_STATE_USE_ITEM_SCREEN;
}

static enum BattleBagTaskState BattleBagTask_AwaitingTextFinish(BattleBagTask *battleBagTask)
{
    if (Text_IsPrinterActive(battleBagTask->unk_32) == FALSE) {
        return BATTLE_BAG_TASK_STATE_AWAITING_INPUT;
    }

    return BATTLE_BAG_TASK_AWAITING_TEXT_FINISH;
}

static enum BattleBagTaskState BattleBagTask_AwaitingInput(BattleBagTask *battleBagTask)
{
    if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B) || TouchScreen_Tapped() == TRUE) {
        return battleBagTask->unk_114B;
    }

    return BATTLE_BAG_TASK_STATE_AWAITING_INPUT;
}

static enum BattleBagTaskState SomeTypeOfQueue(BattleBagTask *battleBagTask)
{
    if (battleBagTask->unk_113E == 2) {
        return battleBagTask->unk_114B;
    }

    return IN_BATTLE_BAG_TRANSITION_INDEX_SOME_TYPE_OF_QUEUE;
}

static enum BattleBagTaskState BattleBagTask_ExitFadeOut(BattleBagTask *battleBagTask)
{
    PaletteData_StartFade(battleBagTask->unk_08, (0x2 | 0x8), 0xffff, -8, 0, 16, 0);
    return BATTLE_BAG_TASK_STATE_FINISH_TASK;
}

static enum BattleBagTaskState BattleBagTask_FinishTask(SysTask *task, BattleBagTask *battleBagTask)
{
    if (PaletteData_GetSelectedBuffersMask(battleBagTask->unk_08) != 0) {
        return 0;
    }

    ov13_02227E08(battleBagTask);
    ov13_02227334(battleBagTask);
    ov13_022270F8(battleBagTask);
    ov13_02226F9C(battleBagTask->unk_04);

    battleBagTask->unk_00->unk_25 = IsBattleSubMenuCursorVisible(battleBagTask->unk_34);

    DeleteBattleSubMenuCursor(battleBagTask->unk_34);
    Font_Free(FONT_SUBSCREEN);

    if (battleBagTask->unk_00->unk_1C != 0) {
        BagCursor *v0;
        u8 v1;

        v0 = BattleSystem_BagCursor(battleBagTask->unk_00->unk_00);

        for (v1 = 0; v1 < 5; v1++) {
            BagCursor_SetBattleCategoryPosition(v0, v1, battleBagTask->unk_00->pocketCurrentPagePositions[v1], battleBagTask->unk_00->pocketCurrentPages[v1]);
        }

        BagCursor_SetBattleCurrentCategory(v0, battleBagTask->currentBattleBagPocket);
    }

    battleBagTask->unk_00->unk_26 = 1;
    SysTask_FinishAndFreeParam(task);

    return 1;
}

static enum BattleBagTaskState BattleBagTask_CatchTutorial(BattleBagTask *battleBagTask)
{
    if (PaletteData_GetSelectedBuffersMask(battleBagTask->unk_08) != 0) {
        return 12;
    }

    switch (battleBagTask->catchTutorialState) {
    case 0:

        if (ov16_0226DFD4(battleBagTask->unk_38) == 1) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->currentBattleBagPocket = ITEM_BATTLE_CATEGORY_POKE_BALLS;
            battleBagTask->unk_114B = 12;
            ov13_0222880C(battleBagTask, 2, 0);
            battleBagTask->unk_115A = 0;
            battleBagTask->catchTutorialState++;
            return IN_BATTLE_BAG_TRANSITION_INDEX_SOME_TYPE_OF_QUEUE;
        } else {
            battleBagTask->unk_115A++;
        }
        break;
    case 1:
        BattleBagTask_SetupPocketMenuScreen(battleBagTask);
        battleBagTask->catchTutorialState++;
        break;
    case 2:
        if (ov16_0226DFD4(battleBagTask->unk_38) == 1) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            battleBagTask->unk_00->pocketCurrentPagePositions[battleBagTask->currentBattleBagPocket] = 0;
            battleBagTask->unk_114B = 12;
            ov13_0222880C(battleBagTask, 6, 0);
            battleBagTask->unk_115A = 0;
            battleBagTask->catchTutorialState++;
            return IN_BATTLE_BAG_TRANSITION_INDEX_SOME_TYPE_OF_QUEUE;
        } else {
            battleBagTask->unk_115A++;
        }
        break;
    case 3:
        BattleBagTask_SetupUseItemScreen(battleBagTask);
        battleBagTask->catchTutorialState++;
        break;
    case 4:
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

    return 12;
}

static void ov13_02226ED0(BattleBagTask *battleBagTask)
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
            4,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xd000,
            GX_BG_CHARBASE_0x00000,
            GX_BG_EXTPLTT_23,
            3,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(battleBagTask->unk_04, 6, &v1, 0);
    }

    {
        BgTemplate v2 = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xf800,
            GX_BG_CHARBASE_0x10000,
            GX_BG_EXTPLTT_01,
            1,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(battleBagTask->unk_04, 5, &v2, 0);
        Bg_ClearTilemap(battleBagTask->unk_04, 5);
    }

    {
        BgTemplate v3 = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0xf000,
            GX_BG_CHARBASE_0x00000,
            GX_BG_EXTPLTT_01,
            0,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(battleBagTask->unk_04, 4, &v3, 0);
        Bg_ClearTilemap(battleBagTask->unk_04, 4);
    }

    Bg_ClearTilesRange(5, 32, 0, battleBagTask->unk_00->heapID);
    Bg_ClearTilesRange(4, 32, 0, battleBagTask->unk_00->heapID);
    Bg_ScheduleTilemapTransfer(battleBagTask->unk_04, 5);
    Bg_ScheduleTilemapTransfer(battleBagTask->unk_04, 4);
}

static void ov13_02226F9C(BgConfig *param0)
{
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ, 0);
    Bg_FreeTilemapBuffer(param0, 4);
    Bg_FreeTilemapBuffer(param0, 5);
    Bg_FreeTilemapBuffer(param0, 6);
}

static void ov13_02226FC4(BattleBagTask *battleBagTask)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_BATTLE__GRAPHIC__B_BAG_GRA, battleBagTask->unk_00->heapID);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 2, battleBagTask->unk_04, 6, 0, 0, 0, battleBagTask->unk_00->heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 0, battleBagTask->unk_04, 6, 0, 0, 0, battleBagTask->unk_00->heapID);

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
    PaletteData_LoadBufferFromFileStart(battleBagTask->unk_08, 77, 3, battleBagTask->unk_00->heapID, 1, 0x20 * 12, 0);
    PaletteData_LoadBufferFromFileStart(battleBagTask->unk_08, 14, 7, battleBagTask->unk_00->heapID, 1, 0x20, 15 * 16);

    {
        int v4 = ov16_0223EDE0(battleBagTask->unk_00->unk_00);

        Graphics_LoadTilesToBgLayer(38, GetMessageBoxTilesNARCMember(v4), battleBagTask->unk_04, 4, 1024 - (18 + 12), 0, 0, battleBagTask->unk_00->heapID);
        PaletteData_LoadBufferFromFileStart(battleBagTask->unk_08, 38, GetMessageBoxPaletteNARCMember(v4), battleBagTask->unk_00->heapID, 1, 0x20, 14 * 16);
    }
}

static void ov13_022270B8(BattleBagTask *battleBagTask)
{
    battleBagTask->unk_10 = MessageLoader_Init(MESSAGE_LOADER_BANK_HANDLE, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0002, battleBagTask->unk_00->heapID);
    battleBagTask->unk_0C = sub_0200C440(15, 14, 0, battleBagTask->unk_00->heapID);
    battleBagTask->unk_14 = StringTemplate_Default(battleBagTask->unk_00->heapID);
    battleBagTask->unk_18 = Strbuf_Init(512, battleBagTask->unk_00->heapID);
}

static void ov13_022270F8(BattleBagTask *battleBagTask)
{
    MessageLoader_Free(battleBagTask->unk_10);
    sub_0200C560(battleBagTask->unk_0C);
    StringTemplate_Free(battleBagTask->unk_14);
    Strbuf_Free(battleBagTask->unk_18);
}

static void ov13_02227118(BattleBagTask *battleBagTask, u8 param1)
{
    switch (param1) {
    case 0:
        Bg_ScheduleScroll(battleBagTask->unk_04, 6, 0, 0);
        Bg_ScheduleScroll(battleBagTask->unk_04, 6, 3, 0);
        break;
    case 1:
        Bg_ScheduleScroll(battleBagTask->unk_04, 6, 0, 256);
        Bg_ScheduleScroll(battleBagTask->unk_04, 6, 3, 0);
        break;
    case 2:
        Bg_ScheduleScroll(battleBagTask->unk_04, 6, 0, 0);
        Bg_ScheduleScroll(battleBagTask->unk_04, 6, 3, 256);
        break;
    }
}

static void ov13_0222717C(BattleBagTask *battleBagTask, u8 param1)
{
    if (param1 != 2) {
        return;
    }

    Bg_ChangeTilemapRectPalette(battleBagTask->unk_04, 6, 2, 35, 28, 4, 8 + battleBagTask->currentBattleBagPocket);
    Bg_ChangeTilemapRectPalette(battleBagTask->unk_04, 6, 2, 40, 28, 8, 8 + battleBagTask->currentBattleBagPocket);
}

static void ChangeInBattleBagScreen(BattleBagTask *battleBagTask, u8 param1)
{
    ov13_0222717C(battleBagTask, param1);
    ov13_02227118(battleBagTask, param1);

    Bg_ScheduleFillTilemap(battleBagTask->unk_04, 4, 0);
    Bg_ScheduleFillTilemap(battleBagTask->unk_04, 5, 0);

    ClearInBattleBagScreen(battleBagTask);
    InitializeInBattleBagScreen(battleBagTask, param1);
    DrawInBattleBagScreen(battleBagTask, param1);
    ov13_02228924(battleBagTask, param1);
    ov13_02228008(battleBagTask, param1);
    ov13_022280F0(battleBagTask, param1);

    battleBagTask->unk_114C = param1;

    ov13_02227E68(battleBagTask, battleBagTask->unk_114C);
}

static int CheckTouchRectIsPressed(BattleBagTask *battleBagTask, const TouchScreenRect *rect)
{
    int isPressed = TouchScreen_CheckRectanglePressed(rect);
    return isPressed;
}

int ov13_02227244(BattleBagTask *battleBagTask)
{
    int v0 = BattleContext_Get(battleBagTask->unk_00->unk_00, BattleSystem_Context(battleBagTask->unk_00->unk_00), 2, battleBagTask->unk_00->unk_10);
    return v0;
}

static void ov13_02227260(BattleSystem *battleSys, u16 item, u16 category, u32 heapID)
{
    Bag_TryRemoveItem(BattleSystem_Bag(battleSys), item, 1, heapID);
    Bag_SetLastBattleItemUsed(BattleSystem_BagCursor(battleSys), item, category);
}
