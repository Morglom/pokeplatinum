#include "overlay013/ov13_0221FC20.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/battle_system.h"

#include "applications/pokemon_summary_screen/main.h"
#include "battle/battle_controller.h"
#include "battle/ov16_0223DF00.h"
#include "overlay013/ov13_02221A88.h"
#include "overlay013/ov13_02224500.h"
#include "overlay013/ov13_02225710.h"
#include "overlay013/ov13_02228A38.h"
#include "overlay013/struct_ov13_0221FC20.h"
#include "overlay013/struct_ov13_022213F0.h"
#include "overlay013/struct_ov13_02221ED0.h"
#include "overlay013/struct_ov13_022236B8.h"

#include "bag.h"
#include "bg_window.h"
#include "font.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "item.h"
#include "message.h"
#include "move_table.h"
#include "narc.h"
#include "palette.h"
#include "party.h"
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
#include "unk_0208C098.h"
#include "unk_02094EDC.h"

enum BattlePartyTaskState {
    BATTLE_PARTY_TASK_STATE_INITIALISE = 0,
    IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_SELECT = 2,
    IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_DETAILS,
    IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_LIST,
    IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_DETAIL,
    IN_BATTLE_PARTY_SCREEN_INDEX_PARTY_LIST,
    IN_BATTLE_PARTY_SCREEN_INDEX_SELECT_POKEMON,
    IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_SUMMARY,
    IN_BATTLE_PARTY_SCREEN_INDEX_CHECK_MOVES,
    IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_SUMMARY,
    IN_BATTLE_PARTY_SCREEN_INDEX_LEARN_MOVE = 12,
    IN_BATTLE_PARTY_SCREEN_INDEX_CHECK_WHICH_PP_ITEM = 13,
    IN_BATTLE_PARTY_SCREEN_INDEX_SUMMARY,
    IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_CANT_SHIFT,
    IN_BATTLE_PARTY_SCREEN_INDEX_ERROR_MESSAGE_BOX,
    BATTLE_PARTY_TASK_STATE_TEXT_FINISH,
    BATTLE_PARTY_TASK_STATE_AWAITING_INPUT,
    IN_BATTLE_PARTY_SCREEN_INDEX_LEARN_MOVE_SCREEN,
    IN_BATTLE_PARTY_SCREEN_INDEX_RESTORE_PP = 21,
    BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION,
    IN_BATTLE_PARTY_SCREEN_INDEX_RESTORE_PP_ALL = 24,
    BATTLE_PARTY_TASK_EXIT,
    BATTLE_PARTY_TASK_FINISH_TASK,
};

enum InBattleTextIndex {
    IN_BATTLE_TEXT_INDEX_POKEMON_ALREADY_IN_BATTLE = 76,
    IN_BATTLE_TEXT_INDEX_POKEMON_HAS_NO_HP_LEFT,
    IN_BATTLE_TEXT_INDEX_POKEMON_CANT_BE_SWITCHED_OUT,
    IN_BATTLE_TEXT_INDEX_POKEMON_EGG_CANT_BATTLE,
    IN_BATTLE_TEXT_INDEX_CANT_SWITCH_TO_PARTNERS_POKEMON,
};

#define EXP_BAR_MAX_PIXELS 64

static void BattlePartyTask_Tick(SysTask *task, void *taskParam);
static u8 BattlePartyTask_Initialize(BattlePartyTask *battlePartyTask);
static u8 ov13_0221FF60(BattlePartyTask *battlePartyTask);
static u8 SelectPokemonScreen(BattlePartyTask *battlePartyTask);
static u8 PokemonDetailsScreen(BattlePartyTask *battlePartyTask);
static u8 PokemonCantShift(BattlePartyTask *battlePartyTask);
static u8 BattlePartyTask_ClearErrorMessage(BattlePartyTask *battlePartyTask);
static u8 BattlePartyTask_TextFinish(BattlePartyTask *battlePartyTask);
static u8 BattlePartyTask_AwaitingInput(BattlePartyTask *battlePartyTask);
static u8 SummaryScreen(BattlePartyTask *battlePartyTask);
static u8 MoveDetailScreen(BattlePartyTask *battlePartyTask);
static u8 LearnMoveScreen(BattlePartyTask *battlePartyTask);
static u8 ov13_0222050C(BattlePartyTask *battlePartyTask);
static u8 UsePPRestoreItem(BattlePartyTask *battlePartyTask);
static u8 BattlePartyTask_ScreenTransition(BattlePartyTask *battlePartyTask);
static u8 PartyList(BattlePartyTask *battlePartyTask);
static u8 SelectPokemon(BattlePartyTask *battlePartyTask);
static u8 CheckMoves(BattlePartyTask *battlePartyTask);
static u8 PokemonSummaryDisplay(BattlePartyTask *battlePartyTask);
static u8 MoveSummary(BattlePartyTask *battlePartyTask);
static u8 ov13_02220768(BattlePartyTask *battlePartyTask);
static u8 LearnMove(BattlePartyTask *battlePartyTask);
static u8 CheckWhichPPItem(BattlePartyTask *battlePartyTask);
static u8 ov13_022208A4(BattlePartyTask *battlePartyTask);
static u8 UsePPAllRestoreItem(BattlePartyTask *battlePartyTask);
static u8 BattlePartyTask_Exit(BattlePartyTask *battlePartyTask);
static BOOL BattlePartyTask_FinishTask(SysTask *task, BattlePartyTask *battlePartyTask);
static u8 MoveListScreen(BattlePartyTask *battlePartyTask);
static u8 ov13_0221FFDC(BattlePartyTask *battlePartyTask);
static void InitializeBackground(BattlePartyTask *battlePartyTask);
static void CleanupBackground(BgConfig *background);
static void ov13_02220D4C(BattlePartyTask *battlePartyTask);
static void InitializeMessageLoader(BattlePartyTask *battlePartyTask);
static void CleanupMessageLoader(BattlePartyTask *battlePartyTask);
static void InitialisePartyPokemon(BattlePartyTask *battlePartyTask);
static u8 ov13_0222124C(BattlePartyTask *battlePartyTask);
static u8 ov13_022212C4(BattlePartyTask *battlePartyTask);
static u8 ov13_0222130C(BattlePartyTask *battlePartyTask);
static u8 ov13_0222139C(BattlePartyTask *battlePartyTask);
static u8 ov13_02221354(BattlePartyTask *battlePartyTask);
static int CheckTouchRectIsPressed(BattlePartyTask *battlePartyTask, const TouchScreenRect *rect);
static void ChangeBattlePartyScreen(BattlePartyTask *battlePartyTask, u8 screen);
static void ov13_02221738(BattlePartyTask *battlePartyTask, u8 param1);
static u8 CheckPokemonCanBeSwitchedTo(BattlePartyTask *battlePartyTask);
static u8 ov13_02221428(BattlePartyTask *battlePartyTask, s32 param1, s32 param2);
static void SetupEXPBar(BattlePartyTask *battlePartyTask, u8 param1);
static void ov13_02221560(BattlePartyTask *battlePartyTask, u16 param1, u16 param2, u16 param3);
static void SetupMoveContestInfo(BattlePartyTask *battlePartyTask, u8 param1);
static u8 CheckSelectedMoveIsHM(BattlePartyTask *battlePartyTask);
static void ov13_02221A04(BattlePartyTask *battlePartyTask);
static void ov13_02221A3C(BattlePartyTask *battlePartyTask);
static u8 CheckSelectedPokemonIsEgg(BattlePartyTask *battlePartyTask);
static void UseBagItem(BattleSystem *battleSys, u16 item, u16 category, u32 heapID);

static const TouchScreenRect Unk_ov13_02228DEC[] = {
    { 0x0, 0x2F, 0x0, 0x7F },
    { 0x8, 0x37, 0x80, 0xFF },
    { 0x30, 0x5F, 0x0, 0x7F },
    { 0x38, 0x67, 0x80, 0xFF },
    { 0x60, 0x8F, 0x0, 0x7F },
    { 0x68, 0x97, 0x80, 0xFF },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect Unk_ov13_02228D24[] = {
    { 0x8, 0x8F, 0x8, 0xF7 },
    { 0x98, 0xBF, 0x0, 0x67 },
    { 0x98, 0xBF, 0x68, 0xCF },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect Unk_ov13_02228D38[] = {
    { 0x98, 0xBF, 0x0, 0x27 },
    { 0x98, 0xBF, 0x28, 0x4F },
    { 0x98, 0xBF, 0x60, 0xC7 },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect Unk_ov13_02228E2C[] = {
    { 0x30, 0x5F, 0x0, 0x7F },
    { 0x30, 0x5F, 0x80, 0xFF },
    { 0x60, 0x8F, 0x0, 0x7F },
    { 0x60, 0x8F, 0x80, 0xFF },
    { 0x98, 0xBF, 0x0, 0x27 },
    { 0x98, 0xBF, 0x28, 0x4F },
    { 0x98, 0xBF, 0x60, 0xC7 },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect Unk_ov13_02228D4C[] = {
    { 0x98, 0xA7, 0x58, 0x7F },
    { 0x98, 0xA7, 0x80, 0xA7 },
    { 0xA8, 0xB7, 0x58, 0x7F },
    { 0xA8, 0xB7, 0x80, 0xA7 },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect Unk_ov13_02228E0C[] = {
    { 0x30, 0x5F, 0x0, 0x7F },
    { 0x30, 0x5F, 0x80, 0xFF },
    { 0x60, 0x8F, 0x0, 0x7F },
    { 0x60, 0x8F, 0x80, 0xFF },
    { 0x90, 0xBF, 0x40, 0xBF },
    { 0x0, 0x27, 0xB8, 0xFF },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect Unk_ov13_02228D14[] = {
    { 0x98, 0xBF, 0x0, 0xCF },
    { 0x0, 0x27, 0xB8, 0xFF },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect Unk_ov13_02228D64[] = {
    { 0x30, 0x5F, 0x0, 0x7F },
    { 0x30, 0x5F, 0x80, 0xFF },
    { 0x60, 0x8F, 0x0, 0x7F },
    { 0x60, 0x8F, 0x80, 0xFF },
    { 0x98, 0xBF, 0xD8, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

void BattlePartyTask_Start(BattlePartyBattleInfo *battleInfo)
{
    BattlePartyTask *battlePartyTask;

    if (battleInfo->selectedPartySlot > 5) {
        battleInfo->selectedPartySlot = 0;
    }

    battlePartyTask = SysTask_GetParam(SysTask_StartAndAllocateParam(BattlePartyTask_Tick, sizeof(BattlePartyTask), 0, battleInfo->heapID));
    memset(battlePartyTask, 0, sizeof(BattlePartyTask));

    battlePartyTask->battleInfo = battleInfo;
    battlePartyTask->background = BattleSystem_BGL(battleInfo->battleSystem);
    battlePartyTask->palette = BattleSystem_PaletteSys(battleInfo->battleSystem);
    battlePartyTask->currentState = BATTLE_PARTY_TASK_STATE_INITIALISE;
    battlePartyTask->selectedPartySlot = battleInfo->selectedPartySlot;
    battlePartyTask->visitedContestHall = ov16_0223F1F8(battleInfo->battleSystem);
    battlePartyTask->battlerType = BattleSystem_BattlerSlot(battleInfo->battleSystem, battleInfo->unk_28);
}

static void BattlePartyTask_Tick(SysTask *task, void *taskParam)
{
    BattlePartyTask *battlePartyTask = (BattlePartyTask *)taskParam;

    switch (battlePartyTask->currentState) {
    case BATTLE_PARTY_TASK_STATE_INITIALISE:
        battlePartyTask->currentState = BattlePartyTask_Initialize(battlePartyTask);
        break;
    case 1:
        battlePartyTask->currentState = ov13_0221FF60(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_SELECT:
        battlePartyTask->currentState = SelectPokemonScreen(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_DETAILS:
        battlePartyTask->currentState = PokemonDetailsScreen(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_LIST:
        battlePartyTask->currentState = MoveListScreen(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_DETAIL:
        battlePartyTask->currentState = MoveDetailScreen(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_PARTY_LIST:
        battlePartyTask->currentState = PartyList(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_SELECT_POKEMON:
        battlePartyTask->currentState = SelectPokemon(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_SUMMARY:
        battlePartyTask->currentState = PokemonSummaryDisplay(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_CHECK_MOVES:
        battlePartyTask->currentState = CheckMoves(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_SUMMARY:
        battlePartyTask->currentState = MoveSummary(battlePartyTask);
        break;
    case 11:
        battlePartyTask->currentState = ov13_02220768(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_LEARN_MOVE:
        battlePartyTask->currentState = LearnMove(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_CHECK_WHICH_PP_ITEM:
        battlePartyTask->currentState = CheckWhichPPItem(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_SUMMARY:
        battlePartyTask->currentState = SummaryScreen(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_CANT_SHIFT:
        battlePartyTask->currentState = PokemonCantShift(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_ERROR_MESSAGE_BOX:
        battlePartyTask->currentState = BattlePartyTask_ClearErrorMessage(battlePartyTask);
        break;
    case BATTLE_PARTY_TASK_STATE_TEXT_FINISH:
        battlePartyTask->currentState = BattlePartyTask_TextFinish(battlePartyTask);
        break;
    case BATTLE_PARTY_TASK_STATE_AWAITING_INPUT:
        battlePartyTask->currentState = BattlePartyTask_AwaitingInput(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_LEARN_MOVE_SCREEN:
        battlePartyTask->currentState = LearnMoveScreen(battlePartyTask);
        break;
    case 20:
        battlePartyTask->currentState = ov13_0222050C(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_RESTORE_PP:
        battlePartyTask->currentState = UsePPRestoreItem(battlePartyTask);
        break;
    case BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION:
        battlePartyTask->currentState = BattlePartyTask_ScreenTransition(battlePartyTask);
        break;
    case 23:
        battlePartyTask->currentState = ov13_022208A4(battlePartyTask);
        break;
    case IN_BATTLE_PARTY_SCREEN_INDEX_RESTORE_PP_ALL:
        battlePartyTask->currentState = UsePPAllRestoreItem(battlePartyTask);
        break;
    case BATTLE_PARTY_TASK_EXIT:
        battlePartyTask->currentState = BattlePartyTask_Exit(battlePartyTask);
        break;

    case BATTLE_PARTY_TASK_FINISH_TASK:
        if (BattlePartyTask_FinishTask(task, battlePartyTask) == TRUE) {
            return;
        }
    }

    ov13_0222537C(battlePartyTask);
    SpriteSystem_DrawSprites(battlePartyTask->spriteManager);
    ov13_0222601C(battlePartyTask);
}

static u8 BattlePartyTask_Initialize(BattlePartyTask *battlePartyTask)
{
    u8 v0;

    G2S_BlendNone();

    if (battlePartyTask->battleInfo->unk_35 == 3) {
        battlePartyTask->currentScreen = IN_BATTLE_SCREEN_LEARN_MOVE_1;
        v0 = IN_BATTLE_PARTY_SCREEN_INDEX_LEARN_MOVE_SCREEN;
    } else {
        battlePartyTask->currentScreen = IN_BATTLE_SCREEN_INDEX_PARTY_LIST;
        v0 = 1;
    }

    battlePartyTask->cursor = MakeBattleSubMenuCursor(battlePartyTask->battleInfo->heapID);

    InitialisePartyPokemon(battlePartyTask);
    InitializeBackground(battlePartyTask);
    ov13_02220D4C(battlePartyTask);
    InitializeMessageLoader(battlePartyTask);

    Font_InitManager(FONT_SUBSCREEN, battlePartyTask->battleInfo->heapID);

    ov13_02221738(battlePartyTask, battlePartyTask->currentScreen);
    ov13_022260EC(battlePartyTask, battlePartyTask->currentScreen);
    ov13_02226444(battlePartyTask, battlePartyTask->currentScreen);
    ov13_02224500(battlePartyTask);
    ov13_02224B7C(battlePartyTask, battlePartyTask->currentScreen);
    ov13_02221A88(battlePartyTask);
    DrawInBattlePartyScreen(battlePartyTask, battlePartyTask->currentScreen);

    if (battlePartyTask->battleInfo->isCursorEnabled != 0) {
        SetBattlePartyBagCursorVisiblity(battlePartyTask->cursor, 1);
    }

    if ((battlePartyTask->currentScreen == 0) && (CheckIfSwitchingWithPartnersPokemon(battlePartyTask, 0) == TRUE)) {
        battlePartyTask->battleInfo->selectedPartySlot = 1;
    }

    ov13_0222563C(battlePartyTask, battlePartyTask->currentScreen);
    SetupEXPBar(battlePartyTask, battlePartyTask->currentScreen);

    PaletteData_StartFade(battlePartyTask->palette, (0x2 | 0x8), 0xffff, -8, 16, 0, 0);

    return v0;
}

static u8 ov13_0221FF60(BattlePartyTask *battlePartyTask)
{
    if (PaletteData_GetSelectedBuffersMask(battlePartyTask->palette) != 0) {
        return 1;
    }

    if (ov13_0222124C(battlePartyTask) == 1) {
        if (battlePartyTask->battleInfo->selectedPartySlot == 6) {
            if (battlePartyTask->battleInfo->unk_35 != 1) {
                Sound_PlayEffect(SEQ_SE_DP_DECIDE);
                ov13_02225FCC(battlePartyTask, 6);
                return BATTLE_PARTY_TASK_EXIT;
            }
        } else {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE);
            ov13_02225FCC(battlePartyTask, 0 + battlePartyTask->battleInfo->selectedPartySlot);

            if (battlePartyTask->battleInfo->unk_35 == 2) {
                return ov13_0221FFDC(battlePartyTask);
            } else {
                battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_SELECT_POKEMON;
            }

            return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
        }
    }

    return 1;
}

static u8 ov13_0221FFDC(BattlePartyTask *battlePartyTask)
{
    BattlePartyBattleInfo *battleInfo = battlePartyTask->battleInfo;

    if (((battleInfo->selectedPartySlot == 0) && (battleInfo->unk_18[0] != 0)) || ((battleInfo->selectedPartySlot == 1) && (battleInfo->unk_18[1] != 0))) {
        OnEmbargoBlockingItem(battlePartyTask);
        DisplayBattleMessageBox(battlePartyTask);
        battlePartyTask->battleInfo->selectedPartySlot = 6;
        battlePartyTask->queuedState = BATTLE_PARTY_TASK_EXIT;
        return BATTLE_PARTY_TASK_STATE_TEXT_FINISH;
    }

    if ((Item_LoadParam(battleInfo->unk_22, ITEM_PARAM_PP_RESTORE, battleInfo->heapID) != FALSE) && (Item_LoadParam(battleInfo->unk_22, ITEM_PARAM_PP_RESTORE_ALL, battleInfo->heapID) == FALSE) && (battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].isEgg == FALSE)) {
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_CHECK_WHICH_PP_ITEM;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    }

    if (BattleSystem_UseBagItem(battleInfo->battleSystem, battleInfo->unk_28, battleInfo->unk_2C[battleInfo->selectedPartySlot], 0, battleInfo->unk_22) == TRUE) {
        if (Item_LoadParam(battleInfo->unk_22, ITEM_PARAM_PP_RESTORE_ALL, battleInfo->heapID) != 0) {
            battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_CHECK_WHICH_PP_ITEM;
        } else {
            if ((ov13_022213F0(battlePartyTask, battleInfo->selectedPartySlot) == 1) && (Item_LoadParam(battleInfo->unk_22, ITEM_PARAM_REVIVE, battleInfo->heapID) == 0)) {
                UseBagItem(battleInfo->battleSystem, battleInfo->unk_22, battleInfo->unk_33, battleInfo->heapID);
                battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].pokemon = BattleSystem_PartyPokemon(battleInfo->battleSystem, battleInfo->unk_28, battleInfo->unk_2C[battleInfo->selectedPartySlot]);
                battleInfo->unk_20 = Pokemon_GetValue(battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].pokemon, MON_DATA_CURRENT_HP, NULL);
                battleInfo->unk_20 -= battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].currentHP;
                battlePartyTask->queuedState = 25;
            } else {
                battlePartyTask->queuedState = 23;
            }
        }

        battlePartyTask->unk_2078 = 0;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    } else {
        MessageLoader_GetStrbuf(battlePartyTask->messageLoader, 81, battlePartyTask->strbuf);
        DisplayBattleMessageBox(battlePartyTask);
        battlePartyTask->battleInfo->selectedPartySlot = 6;
        battlePartyTask->queuedState = BATTLE_PARTY_TASK_EXIT;
        return BATTLE_PARTY_TASK_STATE_TEXT_FINISH;
    }

    return BATTLE_PARTY_TASK_STATE_TEXT_FINISH;
}

static u8 SelectPokemonScreen(BattlePartyTask *battlePartyTask)
{
    u8 v0 = ov13_022212C4(battlePartyTask);

    switch (v0) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 7);

        if (CheckPokemonCanBeSwitchedTo(battlePartyTask) == TRUE) {
            return BATTLE_PARTY_TASK_EXIT;
        }

        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_CANT_SHIFT;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 1:
        if (CheckSelectedPokemonIsEgg(battlePartyTask) == TRUE) {
            break;
        }

        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 8);
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_SUMMARY;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 2:
        if (CheckSelectedPokemonIsEgg(battlePartyTask) == TRUE) {
            break;
        }

        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 10);
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_CHECK_MOVES;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 3:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 6);
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_PARTY_LIST;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    }

    return 2;
}

static u8 PokemonDetailsScreen(BattlePartyTask *battlePartyTask)
{
    u8 v0 = ov13_0222130C(battlePartyTask);

    switch (v0) {
    case 0: {
        u8 v1 = ov13_02221428(battlePartyTask, battlePartyTask->battleInfo->selectedPartySlot, -1);

        if (v1 == 0xff) {
            break;
        }

        battlePartyTask->battleInfo->selectedPartySlot = v1;
    }
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 12);
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_SUMMARY;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 1: {
        u8 v2 = ov13_02221428(battlePartyTask, battlePartyTask->battleInfo->selectedPartySlot, 1);

        if (v2 == 0xff) {
            break;
        }

        battlePartyTask->battleInfo->selectedPartySlot = v2;
    }
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 13);
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_SUMMARY;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 2:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 11);
        battlePartyTask->queuedState = 9;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 3:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 6);
        battlePartyTask->unk_2088 = 1;
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_SELECT_POKEMON;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    }

    return IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_DETAILS;
}

static u8 MoveListScreen(BattlePartyTask *battlePartyTask)
{
    u8 v0 = ov13_02221354(battlePartyTask);

    switch (v0) {
    case 0:
    case 1:
    case 2:
    case 3:
        if (battlePartyTask->partyPokemon[battlePartyTask->battleInfo->selectedPartySlot].moves[v0].move == MOVE_NONE) {
            break;
        }

        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 14 + v0);
        battlePartyTask->battleInfo->unk_34 = v0;
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_SUMMARY;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 4: {
        u8 v1 = ov13_02221428(battlePartyTask, battlePartyTask->battleInfo->selectedPartySlot, -1);

        if (v1 == 0xff) {
            break;
        }

        battlePartyTask->battleInfo->selectedPartySlot = v1;
    }
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 12);
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_SUMMARY;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;

    case 5: {
        u8 v2 = ov13_02221428(battlePartyTask, battlePartyTask->battleInfo->selectedPartySlot, 1);

        if (v2 == 0xff) {
            break;
        }

        battlePartyTask->battleInfo->selectedPartySlot = v2;
    }
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 13);
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_SUMMARY;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 6:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 9);
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_SUMMARY;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 7:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 6);
        battlePartyTask->unk_2088 = 2;
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_SELECT_POKEMON;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    }

    return IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_LIST;
}

static u8 MoveDetailScreen(BattlePartyTask *battlePartyTask)
{
    u8 v0 = ov13_0222139C(battlePartyTask);

    switch (v0) {
    case 0:
    case 1:
    case 2:
    case 3:
        if ((battlePartyTask->battleInfo->unk_34 != v0) && (battlePartyTask->partyPokemon[battlePartyTask->battleInfo->selectedPartySlot].moves[v0].move == MOVE_NONE)) {
            break;
        }

        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        battlePartyTask->battleInfo->unk_34 = v0;
        return IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_SUMMARY;
    case 4:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 6);
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_CHECK_MOVES;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    }

    return IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_DETAIL;
}

static u8 LearnMoveScreen(BattlePartyTask *battlePartyTask)
{
    int v0 = CheckTouchRectIsPressed(battlePartyTask, Unk_ov13_02228E0C);

    if (v0 == TOUCHSCREEN_INPUT_NONE) {
        v0 = CheckBattleSubMenuCursorInputs(battlePartyTask->cursor);

        if (v0 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            v0 = 6;
        }
    } else {
        SomeKindOfReset(battlePartyTask);
    }

    switch (v0) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        battlePartyTask->battleInfo->unk_34 = (u8)v0;
        battlePartyTask->unk_2089 = (u8)v0;
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 23 + v0);
        battlePartyTask->queuedState = 12;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 5:
        if (battlePartyTask->visitedContestHall == 0) {
            break;
        }

        battlePartyTask->inLearnMoveContestData ^= 1;
        battlePartyTask->unk_2089 = (u8)v0;
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 18);
        battlePartyTask->queuedState = 11;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 6:
        battlePartyTask->battleInfo->unk_34 = 4;
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 6);
        battlePartyTask->queuedState = BATTLE_PARTY_TASK_EXIT;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    }

    return IN_BATTLE_PARTY_SCREEN_INDEX_LEARN_MOVE_SCREEN;
}

static u8 ov13_0222050C(BattlePartyTask *battlePartyTask)
{
    int v0 = CheckTouchRectIsPressed(battlePartyTask, Unk_ov13_02228D14);

    if (v0 == TOUCHSCREEN_INPUT_NONE) {
        v0 = CheckBattleSubMenuCursorInputs(battlePartyTask->cursor);

        if (v0 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            v0 = 2;
        }
    } else {
        SomeKindOfReset(battlePartyTask);
    }

    switch (v0) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);

        if (battlePartyTask->inLearnMoveContestData == FALSE) {
            ov13_02225FCC(battlePartyTask, 28);
        } else {
            ov13_02225FCC(battlePartyTask, 29);
        }

        if (CheckSelectedMoveIsHM(battlePartyTask) == TRUE) {
            ov13_02223118(battlePartyTask);

            if (battlePartyTask->inLearnMoveContestData == FALSE) {
                ov13_02221A04(battlePartyTask);
            } else {
                ov13_02221A3C(battlePartyTask);
            }

            battlePartyTask->queuedState = 20;
        } else {
            battlePartyTask->queuedState = BATTLE_PARTY_TASK_EXIT;
        }

        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 1:
        if (battlePartyTask->visitedContestHall == 0) {
            break;
        }

        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 18);
        battlePartyTask->inLearnMoveContestData ^= 1;
        battlePartyTask->unk_208A = (u8)v0;
        battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_LEARN_MOVE;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    case 2:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 6);
        battlePartyTask->unk_208A = 0;
        battlePartyTask->queuedState = 11;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    }

    return 20;
}

static u8 UsePPRestoreItem(BattlePartyTask *battlePartyTask)
{
    BattlePartyBattleInfo *v0;
    int v1; // Move Index

    v0 = battlePartyTask->battleInfo;
    v1 = CheckTouchRectIsPressed(battlePartyTask, Unk_ov13_02228D64);

    if (v1 == TOUCHSCREEN_INPUT_NONE) {
        v1 = CheckBattleSubMenuCursorInputs(battlePartyTask->cursor);

        if (v1 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            v1 = 4;
        }
    } else {
        SomeKindOfReset(battlePartyTask);
    }

    switch (v1) {
    case 0:
    case 1:
    case 2:
    case 3:
        if (battlePartyTask->partyPokemon[v0->selectedPartySlot].moves[v1].move == 0) {
            break;
        }

        battlePartyTask->battleInfo->unk_34 = (u8)v1;
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 19 + v1);

        if (BattleSystem_UseBagItem(v0->battleSystem, v0->unk_28, v0->unk_2C[v0->selectedPartySlot], v1, v0->unk_22) == TRUE) {
            battlePartyTask->unk_2078 = 0;
            battlePartyTask->queuedState = 23;
            return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
        } else {
            MessageLoader_GetStrbuf(battlePartyTask->messageLoader, 81, battlePartyTask->strbuf);
            DisplayBattleMessageBox(battlePartyTask);
            battlePartyTask->battleInfo->selectedPartySlot = 6;
            battlePartyTask->queuedState = BATTLE_PARTY_TASK_EXIT;
            return BATTLE_PARTY_TASK_STATE_TEXT_FINISH;
        }
        break;
    case 4:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        ov13_02225FCC(battlePartyTask, 6);
        battlePartyTask->queuedState = 6;
        return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
    }

    return 21;
}

static u8 PartyList(BattlePartyTask *battlePartyTask)
{
    ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_INDEX_PARTY_LIST);
    return 1;
}

static u8 SelectPokemon(BattlePartyTask *battlePartyTask)
{
    ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_INDEX_SELECT_POKEMON);
    return 2;
}

static u8 PokemonSummaryDisplay(BattlePartyTask *battlePartyTask)
{
    ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_INDEX_POKEMON_SUMMARY);
    return 3;
}

static u8 CheckMoves(BattlePartyTask *battlePartyTask)
{
    ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_INDEX_CHECK_MOVES);
    return IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_LIST;
}

static u8 MoveSummary(BattlePartyTask *battlePartyTask)
{
    ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_INDEX_MOVE_SUMMARY);
    return IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_DETAIL;
}

static u8 ov13_02220768(BattlePartyTask *battlePartyTask)
{
    if (battlePartyTask->inLearnMoveContestData == FALSE) {
        ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_LEARN_MOVE_1);
    } else {
        ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_LEARN_MOVE_2);
    }

    return 19;
}

static u8 LearnMove(BattlePartyTask *battlePartyTask)
{
    ov13_022252E8(battlePartyTask);

    if (battlePartyTask->inLearnMoveContestData == FALSE) {
        ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_LEARN_MOVE_CONFIRM);
    } else {
        ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_LEARN_MOVE_CONTEST);
    }

    return 20;
}

static u8 CheckWhichPPItem(BattlePartyTask *battlePartyTask)
{
    ChangeBattlePartyScreen(battlePartyTask, IN_BATTLE_SCREEN_INDEX_RESTORE_PP);

    if (Item_LoadParam(battlePartyTask->battleInfo->unk_22, ITEM_PARAM_PP_RESTORE_ALL, battlePartyTask->battleInfo->heapID) != FALSE) {
        return IN_BATTLE_PARTY_SCREEN_INDEX_RESTORE_PP_ALL;
    }

    return IN_BATTLE_PARTY_SCREEN_INDEX_RESTORE_PP;
}

static u8 SummaryScreen(BattlePartyTask *battlePartyTask)
{
    ov13_02224B7C(battlePartyTask, battlePartyTask->currentScreen);
    DrawInBattlePartyScreen(battlePartyTask, battlePartyTask->currentScreen);
    ov13_022260EC(battlePartyTask, battlePartyTask->currentScreen);
    SetupEXPBar(battlePartyTask, battlePartyTask->currentScreen);

    if (battlePartyTask->currentScreen == IN_BATTLE_SCREEN_INDEX_POKEMON_SUMMARY) {
        return IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_DETAILS;
    }

    return IN_BATTLE_PARTY_SCREEN_INDEX_MOVE_LIST;
}

static u8 PokemonCantShift(BattlePartyTask *battlePartyTask)
{
    DisplayBattleMessageBox(battlePartyTask);
    battlePartyTask->queuedState = IN_BATTLE_PARTY_SCREEN_INDEX_ERROR_MESSAGE_BOX;
    return BATTLE_PARTY_TASK_STATE_TEXT_FINISH;
}

static u8 BattlePartyTask_ClearErrorMessage(BattlePartyTask *battlePartyTask)
{
    Window_EraseMessageBox(&battlePartyTask->messageBoxWindows[1], FALSE);
    return IN_BATTLE_PARTY_SCREEN_INDEX_POKEMON_SELECT;
}

static u8 BattlePartyTask_TextFinish(BattlePartyTask *battlePartyTask)
{
    if (Text_IsPrinterActive(battlePartyTask->textPrinter) == FALSE) {
        return BATTLE_PARTY_TASK_STATE_AWAITING_INPUT;
    }

    return BATTLE_PARTY_TASK_STATE_TEXT_FINISH;
}

static u8 BattlePartyTask_AwaitingInput(BattlePartyTask *battlePartyTask)
{
    if (JOY_NEW(PAD_BUTTON_A | PAD_BUTTON_B) || (TouchScreen_Tapped() == TRUE)) {
        return battlePartyTask->queuedState;
    }

    return BATTLE_PARTY_TASK_STATE_AWAITING_INPUT;
}

static u8 BattlePartyTask_ScreenTransition(BattlePartyTask *battlePartyTask)
{
    if (battlePartyTask->unk_1F9F_7 == 0) {
        return battlePartyTask->queuedState;
    }

    return BATTLE_PARTY_TASK_STATE_SCREEN_TRANSITION;
}

static u8 ov13_022208A4(BattlePartyTask *battlePartyTask)
{
    BattlePartyBattleInfo *battleInfo = battlePartyTask->battleInfo;

    switch (battlePartyTask->unk_2078) {
    case 0:
        battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].pokemon = BattleSystem_PartyPokemon(battleInfo->battleSystem, battleInfo->unk_28, battleInfo->unk_2C[battleInfo->selectedPartySlot]);
        ov13_02224144(battlePartyTask);

        if (battlePartyTask->currentScreen == 5) {
            battlePartyTask->unk_207C[0] = (u16)Pokemon_GetValue(battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].pokemon, MON_DATA_MOVE1_CUR_PP + battleInfo->unk_34, NULL);
            battlePartyTask->unk_2078 = 2;
        } else {
            battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].status = PokemonSummaryScreen_StatusIconAnimIdx(battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].pokemon);

            if (battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].status == 7) {
                ManagedSprite_SetDrawFlag(battlePartyTask->unk_1FB4[13 + battleInfo->selectedPartySlot], 0);
                ov13_022234A8(battlePartyTask, battleInfo->selectedPartySlot);
            }

            battlePartyTask->unk_207A = Pokemon_GetValue(battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].pokemon, MON_DATA_CURRENT_HP, NULL);
            battlePartyTask->unk_2078 = 4;
        }

        Sound_PlayEffect(SEQ_SE_DP_KAIFUKU);
        break;
    case 1:
        if (battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].currentHP != battlePartyTask->unk_207A) {
            battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].currentHP++;
            DrawHealthDisplay(battlePartyTask, battleInfo->selectedPartySlot);
            break;
        }

        battlePartyTask->unk_2078 = 3;
        break;
    case 2:
        if (battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].moves[battleInfo->unk_34].currentPP != battlePartyTask->unk_207C[0]) {
            battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].moves[battleInfo->unk_34].currentPP++;
            ov13_02223F5C(battlePartyTask, 1 + battleInfo->unk_34, battleInfo->unk_34);
            break;
        }

        battlePartyTask->unk_2078 = 3;
        break;
    case 3:
        UseBagItem(battleInfo->battleSystem, battleInfo->unk_22, battleInfo->unk_33, battleInfo->heapID);
        DisplayBattleMessageBox(battlePartyTask);
        battlePartyTask->queuedState = BATTLE_PARTY_TASK_EXIT;
        return BATTLE_PARTY_TASK_STATE_TEXT_FINISH;
    case 4:
        if (battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].currentHP != battlePartyTask->unk_207A) {
            battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].currentHP++;
            DrawHealthDisplay(battlePartyTask, battleInfo->selectedPartySlot);
            ov13_022264C4(battlePartyTask);
        }

        battlePartyTask->unk_2078 = 1;
        break;
    }

    return 23;
}

static u8 UsePPAllRestoreItem(BattlePartyTask *battlePartyTask)
{
    BattlePartyBattleInfo *battleInfo = battlePartyTask->battleInfo;
    u32 v1, v2;

    switch (battlePartyTask->unk_2078) {
    case 0:
        battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].pokemon = BattleSystem_PartyPokemon(battleInfo->battleSystem, battleInfo->unk_28, battleInfo->unk_2C[battleInfo->selectedPartySlot]);

        for (v1 = 0; v1 < LEARNED_MOVES_MAX; v1++) {
            if (battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].moves[v1].move == MOVE_NONE) {
                continue;
            }

            battlePartyTask->unk_207C[v1] = (u16)Pokemon_GetValue(battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].pokemon, MON_DATA_MOVE1_CUR_PP + v1, NULL);
        }

        ov13_02224144(battlePartyTask);
        Sound_PlayEffect(SEQ_SE_DP_KAIFUKU);
        battlePartyTask->unk_2078 = 1;
        break;
    case 1:
        v2 = 0;

        for (v1 = 0; v1 < 4; v1++) {
            if (battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].moves[v1].move == MOVE_NONE) {
                v2++;
                continue;
            }

            if (battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].moves[v1].currentPP != battlePartyTask->unk_207C[v1]) {
                battlePartyTask->partyPokemon[battleInfo->selectedPartySlot].moves[v1].currentPP++;
                ov13_02223F5C(battlePartyTask, 1 + v1, v1);
            } else {
                v2++;
            }
        }

        if (v2 == 4) {
            battlePartyTask->unk_2078 = 2;
        }
        break;
    case 2:
        UseBagItem(battleInfo->battleSystem, battleInfo->unk_22, battleInfo->unk_33, battleInfo->heapID);
        DisplayBattleMessageBox(battlePartyTask);
        battlePartyTask->queuedState = BATTLE_PARTY_TASK_EXIT;
        return BATTLE_PARTY_TASK_STATE_TEXT_FINISH;
    }

    return IN_BATTLE_PARTY_SCREEN_INDEX_RESTORE_PP_ALL;
}

static u8 BattlePartyTask_Exit(BattlePartyTask *battlePartyTask)
{
    PaletteData_StartFade(battlePartyTask->palette, (0x2 | 0x8), 0xffff, -8, 0, 16, 0);
    return BATTLE_PARTY_TASK_FINISH_TASK;
}

static BOOL BattlePartyTask_FinishTask(SysTask *task, BattlePartyTask *battlePartyTask)
{
    if (PaletteData_GetSelectedBuffersMask(battlePartyTask->palette) != 0) {
        return FALSE;
    }

    CleanupMessageLoader(battlePartyTask);
    ov13_02224970(battlePartyTask);
    ov13_02221BC8(battlePartyTask);
    CleanupBackground(battlePartyTask->background);

    battlePartyTask->battleInfo->isCursorEnabled = IsBattleSubMenuCursorVisible(battlePartyTask->cursor);

    DeleteBattleSubMenuCursor(battlePartyTask->cursor);
    Font_Free(FONT_SUBSCREEN);

    battlePartyTask->battleInfo->unk_36 = 1;
    SysTask_FinishAndFreeParam(task);

    return TRUE;
}

static void InitializeBackground(BattlePartyTask *battlePartyTask)
{
    {
        GraphicsModes graphicsMode = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D,
        };

        SetScreenGraphicsModes(&graphicsMode, DS_SCREEN_SUB);
    }

    {
        BgTemplate backgroundTemplate = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x0000,
            GX_BG_CHARBASE_0x08000,
            GX_BG_EXTPLTT_23,
            3,
            0,
            0,
            FALSE
        };

        Bg_InitFromTemplate(battlePartyTask->background, BG_LAYER_SUB_3, &backgroundTemplate, BG_TYPE_STATIC);
    }

    {
        BgTemplate backgroundTemplate = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x0800,
            GX_BG_CHARBASE_0x08000,
            GX_BG_EXTPLTT_23,
            2,
            0,
            0,
            FALSE
        };

        Bg_InitFromTemplate(battlePartyTask->background, BG_LAYER_SUB_2, &backgroundTemplate, BG_TYPE_STATIC);
    }

    {
        BgTemplate backgroundTemplate = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x1000,
            GX_BG_CHARBASE_0x10000,
            GX_BG_EXTPLTT_01,
            1,
            0,
            0,
            FALSE
        };

        Bg_InitFromTemplate(battlePartyTask->background, BG_LAYER_SUB_1, &backgroundTemplate, BG_TYPE_STATIC);
        Bg_ClearTilemap(battlePartyTask->background, BG_LAYER_SUB_1);
    }

    {
        BgTemplate backgroundTemplate = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x1800,
            GX_BG_CHARBASE_0x18000,
            GX_BG_EXTPLTT_01,
            0,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(battlePartyTask->background, BG_LAYER_SUB_0, &backgroundTemplate, BG_TYPE_STATIC);
        Bg_ClearTilemap(battlePartyTask->background, BG_LAYER_SUB_0);
    }

    Bg_ClearTilesRange(BG_LAYER_SUB_1, 32, 0, battlePartyTask->battleInfo->heapID);
    Bg_ClearTilesRange(BG_LAYER_SUB_0, 32, 0, battlePartyTask->battleInfo->heapID);
    Bg_ScheduleTilemapTransfer(battlePartyTask->background, BG_LAYER_SUB_1);
    Bg_ScheduleTilemapTransfer(battlePartyTask->background, BG_LAYER_SUB_0);
}

static void CleanupBackground(BgConfig *background)
{
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, FALSE);
    Bg_FreeTilemapBuffer(background, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(background, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(background, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(background, BG_LAYER_SUB_3);
}

static void ov13_02220D4C(BattlePartyTask *battlePartyTask)
{
    NARC *narc = NARC_ctor(NARC_INDEX_BATTLE__GRAPHIC__PL_B_PLIST_GRA, battlePartyTask->battleInfo->heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(narc, 22, battlePartyTask->background, BG_LAYER_SUB_3, 0, 0, 0, battlePartyTask->battleInfo->heapID);

    {
        NNSG2dScreenData *screenData;
        void *buffer;

        buffer = NARC_AllocAndReadWholeMember(narc, 20, battlePartyTask->battleInfo->heapID);
        NNS_G2dGetUnpackedScreenData(buffer, &screenData);
        ov13_02225710(battlePartyTask, (u16 *)screenData->rawData);
        Heap_FreeToHeap(buffer);

        buffer = NARC_AllocAndReadWholeMember(narc, 21, battlePartyTask->battleInfo->heapID);
        NNS_G2dGetUnpackedScreenData(buffer, &screenData);

        ov13_02225A3C(battlePartyTask, (u16 *)screenData->rawData);
        Heap_FreeToHeap(buffer);
    }

    PaletteData_LoadBufferFromFileStart(battlePartyTask->palette, NARC_INDEX_BATTLE__GRAPHIC__PL_B_PLIST_GRA, 23, battlePartyTask->battleInfo->heapID, PLTTBUF_SUB_BG, 0x20 * 16, 0);
    NARC_dtor(narc);

    {
        u16 *v3 = PaletteData_GetUnfadedBuffer(battlePartyTask->palette, PLTTBUF_SUB_BG);
        memcpy(battlePartyTask->unk_1F5C, &v3[12 * 16], 0x20 * 2);
    }

    PaletteData_LoadBufferFromFileStart(battlePartyTask->palette, NARC_INDEX_GRAPHIC__PL_FONT, 6, battlePartyTask->battleInfo->heapID, PLTTBUF_SUB_BG, 0x20, 13 * 16);
    PaletteData_LoadBufferFromFileStart(battlePartyTask->palette, NARC_INDEX_GRAPHIC__PL_FONT, 7, battlePartyTask->battleInfo->heapID, PLTTBUF_SUB_BG, 0x20, 15 * 16);

    {
        int optionsFrame = ov16_0223EDE0(battlePartyTask->battleInfo->battleSystem);

        Graphics_LoadTilesToBgLayer(NARC_INDEX_GRAPHIC__PL_WINFRAME, GetMessageBoxTilesNARCMember(optionsFrame), battlePartyTask->background, BG_LAYER_SUB_0, 1, 0, 0, battlePartyTask->battleInfo->heapID);
        PaletteData_LoadBufferFromFileStart(battlePartyTask->palette, NARC_INDEX_GRAPHIC__PL_WINFRAME, GetMessageBoxPaletteNARCMember(optionsFrame), battlePartyTask->battleInfo->heapID, PLTTBUF_SUB_BG, 0x20, 14 * 16);
    }

    {
        u16 *v5 = PaletteData_GetUnfadedBuffer(battlePartyTask->palette, PLTTBUF_SUB_BG);
        u16 *v6 = Heap_AllocFromHeap(battlePartyTask->battleInfo->heapID, 0x20);

        memcpy(v6, &v5[13 * 16], 0x20);
        memcpy(&v6[7], &v5[9 * 16 + 10], 4);
        memcpy(&v6[3], &v5[9 * 16 + 12], 4);

        PaletteData_LoadBuffer(battlePartyTask->palette, v6, PLTTBUF_SUB_BG, 13 * 16, 0x20);
        Heap_FreeToHeap(v6);
    }
}

static void InitializeMessageLoader(BattlePartyTask *battlePartyTask)
{
    battlePartyTask->messageLoader = MessageLoader_Init(MESSAGE_LOADER_BANK_HANDLE, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0003, battlePartyTask->battleInfo->heapID);
    battlePartyTask->unk_1FA0 = sub_0200C440(15, 14, 0, battlePartyTask->battleInfo->heapID);
    battlePartyTask->stringTemplate = StringTemplate_Default(battlePartyTask->battleInfo->heapID);
    battlePartyTask->strbuf = Strbuf_Init(512, battlePartyTask->battleInfo->heapID);
}

static void CleanupMessageLoader(BattlePartyTask *battlePartyTask)
{
    MessageLoader_Free(battlePartyTask->messageLoader);
    sub_0200C560(battlePartyTask->unk_1FA0);
    StringTemplate_Free(battlePartyTask->stringTemplate);
    Strbuf_Free(battlePartyTask->strbuf);
}

static void InitialisePartyPokemon(BattlePartyTask *battlePartyTask)
{
    u16 i, l;

    for (i = 0; i < Party_GetCurrentCount(battlePartyTask->battleInfo->unk_00); i++) {
        battlePartyTask->partyPokemon[i].pokemon = Party_GetPokemonBySlotIndex(battlePartyTask->battleInfo->unk_00, i);
        battlePartyTask->partyPokemon[i].species = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_SPECIES, NULL);

        if (battlePartyTask->partyPokemon[i].species == SPECIES_NONE) {
            continue;
        }

        battlePartyTask->partyPokemon[i].attack = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_ATK, NULL);
        battlePartyTask->partyPokemon[i].defence = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_DEF, NULL);
        battlePartyTask->partyPokemon[i].speed = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_SPEED, NULL);
        battlePartyTask->partyPokemon[i].spAtk = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_SP_ATK, NULL);
        battlePartyTask->partyPokemon[i].spDef = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_SP_DEF, NULL);
        battlePartyTask->partyPokemon[i].currentHP = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_CURRENT_HP, NULL);
        battlePartyTask->partyPokemon[i].maxHP = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_MAX_HP, NULL);
        battlePartyTask->partyPokemon[i].type1 = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_TYPE_1, NULL);
        battlePartyTask->partyPokemon[i].type2 = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_TYPE_2, NULL);
        battlePartyTask->partyPokemon[i].level = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_LEVEL, NULL);

        if (Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_NIDORAN_HAS_NICKNAME, NULL) == TRUE) {
            battlePartyTask->partyPokemon[i].displayGender = FALSE;
        } else {
            battlePartyTask->partyPokemon[i].displayGender = TRUE;
        }

        battlePartyTask->partyPokemon[i].gender = Pokemon_GetGender(battlePartyTask->partyPokemon[i].pokemon);
        battlePartyTask->partyPokemon[i].status = PokemonSummaryScreen_StatusIconAnimIdx(battlePartyTask->partyPokemon[i].pokemon);
        battlePartyTask->partyPokemon[i].isEgg = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_IS_EGG, NULL);
        battlePartyTask->partyPokemon[i].ability = (u16)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_ABILITY, NULL);
        battlePartyTask->partyPokemon[i].heldItem = (u16)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_HELD_ITEM, NULL);
        battlePartyTask->partyPokemon[i].exp = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_EXP, NULL);
        battlePartyTask->partyPokemon[i].currentLevelBaseExp = Pokemon_GetSpeciesBaseExpAt(battlePartyTask->partyPokemon[i].species, battlePartyTask->partyPokemon[i].level);

        if (battlePartyTask->partyPokemon[i].level == MAX_POKEMON_LEVEL) {
            battlePartyTask->partyPokemon[i].nextLevelExp = battlePartyTask->partyPokemon[i].currentLevelBaseExp;
        } else {
            battlePartyTask->partyPokemon[i].nextLevelExp = Pokemon_GetSpeciesBaseExpAt(battlePartyTask->partyPokemon[i].species, battlePartyTask->partyPokemon[i].level + 1);
        }

        battlePartyTask->partyPokemon[i].cool = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_COOL, NULL);
        battlePartyTask->partyPokemon[i].beauty = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_BEAUTY, NULL);
        battlePartyTask->partyPokemon[i].cute = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_CUTE, NULL);
        battlePartyTask->partyPokemon[i].smart = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_SMART, NULL);
        battlePartyTask->partyPokemon[i].tough = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_TOUGH, NULL);
        battlePartyTask->partyPokemon[i].mail = (u16)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_MAIL_ID, NULL);
        battlePartyTask->partyPokemon[i].form = (u8)Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_FORM, NULL);

        for (l = 0; l < LEARNED_MOVES_MAX; l++) {
            PartyPokemonMoveData *moveData = &battlePartyTask->partyPokemon[i].moves[l];

            moveData->move = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_MOVE1 + l, NULL);

            if (moveData->move == MOVE_NONE) {
                continue;
            }

            moveData->currentPP = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_MOVE1_CUR_PP + l, NULL);
            moveData->maxPP = Pokemon_GetValue(battlePartyTask->partyPokemon[i].pokemon, MON_DATA_MOVE1_PP_UPS + l, NULL);
            moveData->maxPP = MoveTable_CalcMaxPP(moveData->move, moveData->maxPP);
            moveData->type = MoveTable_LoadParam(moveData->move, MOVEATTRIBUTE_TYPE);
            moveData->class = MoveTable_LoadParam(moveData->move, MOVEATTRIBUTE_CLASS);
            moveData->accuracy = MoveTable_LoadParam(moveData->move, MOVEATTRIBUTE_ACCURACY);
            moveData->power = MoveTable_LoadParam(moveData->move, MOVEATTRIBUTE_POWER);
        }
    }
}

static u8 ov13_0222124C(BattlePartyTask *battlePartyTask)
{
    int v0 = CheckTouchRectIsPressed(battlePartyTask, Unk_ov13_02228DEC);

    if (v0 == TOUCHSCREEN_INPUT_NONE) {
        v0 = CheckBattleSubMenuCursorInputs(battlePartyTask->cursor);

        if (v0 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            v0 = 6;
        } else if (v0 == BATTLE_SUB_MENU_CURSOR_NO_MOVEMENT_INDEX) {
            return 0;
        }

        if ((v0 == 6) || (ov13_022213F0(battlePartyTask, v0) != 0)) {
            battlePartyTask->battleInfo->selectedPartySlot = (u8)v0;
            return 1;
        }
    } else {
        if ((v0 == 6) || (ov13_022213F0(battlePartyTask, v0) != 0)) {
            battlePartyTask->battleInfo->selectedPartySlot = (u8)v0;

            SomeKindOfReset(battlePartyTask);
            return 1;
        }
    }

    return 0;
}

static u8 ov13_022212C4(BattlePartyTask *battlePartyTask)
{
    int buttonPressed = CheckTouchRectIsPressed(battlePartyTask, Unk_ov13_02228D24);

    if (buttonPressed == TOUCHSCREEN_INPUT_NONE) {
        buttonPressed = CheckBattleSubMenuCursorInputs(battlePartyTask->cursor);

        if (buttonPressed == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            buttonPressed = 3;
        } else if (buttonPressed == BATTLE_SUB_MENU_CURSOR_NO_MOVEMENT_INDEX) {
            return 0xff;
        }
    } else {
        SomeKindOfReset(battlePartyTask);
    }

    return (u8)buttonPressed;
}

static u8 ov13_0222130C(BattlePartyTask *battlePartyTask)
{
    int v0 = CheckTouchRectIsPressed(battlePartyTask, Unk_ov13_02228D38);

    if (v0 == TOUCHSCREEN_INPUT_NONE) {
        v0 = CheckBattleSubMenuCursorInputs(battlePartyTask->cursor);

        if (v0 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            v0 = 3;
        } else if (v0 == BATTLE_SUB_MENU_CURSOR_NO_MOVEMENT_INDEX) {
            return 0xff;
        }
    } else {
        SomeKindOfReset(battlePartyTask);
    }

    return (u8)v0;
}

static u8 ov13_02221354(BattlePartyTask *battlePartyTask)
{
    int v0 = CheckTouchRectIsPressed(battlePartyTask, Unk_ov13_02228E2C);

    if (v0 == TOUCHSCREEN_INPUT_NONE) {
        v0 = CheckBattleSubMenuCursorInputs(battlePartyTask->cursor);

        if (v0 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            v0 = 7;
        } else if (v0 == BATTLE_SUB_MENU_CURSOR_NO_MOVEMENT_INDEX) {
            return 0xff;
        }
    } else {
        SomeKindOfReset(battlePartyTask);
    }

    return (u8)v0;
}

static u8 ov13_0222139C(BattlePartyTask *battlePartyTask)
{
    int v0 = CheckTouchRectIsPressed(battlePartyTask, Unk_ov13_02228D4C);

    if (v0 == TOUCHSCREEN_INPUT_NONE) {
        v0 = CheckBattleSubMenuCursorInputs(battlePartyTask->cursor);

        if (v0 == BATTLE_SUB_MENU_CURSOR_BACK_INDEX) {
            v0 = 4;
        } else if (v0 == BATTLE_SUB_MENU_CURSOR_NO_MOVEMENT_INDEX) {
            return 0xff;
        }
    } else {
        SomeKindOfReset(battlePartyTask);
    }

    return (u8)v0;
}

static int CheckTouchRectIsPressed(BattlePartyTask *battlePartyTask, const TouchScreenRect *rect)
{
    int isPressed = TouchScreen_CheckRectanglePressed(rect);
    return isPressed;
}

u8 ov13_022213F0(BattlePartyTask *battlePartyTask, s32 param1)
{
    if (battlePartyTask->partyPokemon[param1].species == SPECIES_NONE) {
        return 0;
    }

    if ((param1 == 0) || ((ov13_0222196C(battlePartyTask) || ov13_0222198C(battlePartyTask)) && (param1 == 1))) {
        return 1;
    }

    return 2;
}

static u8 ov13_02221428(BattlePartyTask *battlePartyTask, s32 param1, s32 param2)
{
    s32 v0 = param1;

    if (ov13_0222198C(battlePartyTask) == 1) {
        u8 v1[] = { 0, 2, 4, 1, 3, 5 };

        for (param1 = 0; param1 < 6; param1++) {
            if (v0 == v1[param1]) {
                break;
            }
        }

        while (TRUE) {
            param1 += param2;

            if (param1 < 0) {
                param1 = 5;
            } else if (param1 >= 6) {
                param1 = 0;
            }

            if (v0 == v1[param1]) {
                break;
            }

            if (ov13_022213F0(battlePartyTask, v1[param1]) != 0) {
                if (battlePartyTask->partyPokemon[v1[param1]].isEgg == FALSE) {
                    return v1[param1];
                }
            }
        }
    } else {
        while (TRUE) {
            param1 += param2;

            if (param1 < 0) {
                param1 = 5;
            } else if (param1 >= 6) {
                param1 = 0;
            }

            if (v0 == param1) {
                break;
            }

            if (ov13_022213F0(battlePartyTask, param1) != 0) {
                if (battlePartyTask->partyPokemon[param1].isEgg == FALSE) {
                    return (u8)param1;
                }
            }
        }
    }

    return 0xff;
}

static void SetupEXPBar(BattlePartyTask *battlePartyTask, u8 screen)
{
    PartyPokemonData *pokemonData;
    u32 expFromCurrentToNextLevel;
    u32 expTowardsNextLevel;
    u16 v3;
    u16 v4, v5;
    u8 expBarFilledPixels;
    u8 v7;

    if (screen != IN_BATTLE_SCREEN_INDEX_POKEMON_SUMMARY) {
        return;
    }

    pokemonData = &battlePartyTask->partyPokemon[battlePartyTask->battleInfo->selectedPartySlot];

    if (pokemonData->level < MAX_POKEMON_LEVEL) {
        expFromCurrentToNextLevel = pokemonData->nextLevelExp - pokemonData->currentLevelBaseExp;
        expTowardsNextLevel = pokemonData->exp - pokemonData->currentLevelBaseExp;
    } else {
        expFromCurrentToNextLevel = 0;
        expTowardsNextLevel = 0;
    }

    expBarFilledPixels = App_PixelCount(expTowardsNextLevel, expFromCurrentToNextLevel, EXP_BAR_MAX_PIXELS);

    for (v7 = 0; v7 < 8; v7++) {
        if (expBarFilledPixels >= 8) {
            v3 = 0x16 + 8;
        } else {
            v3 = 0x16 + expBarFilledPixels;
        }

        ov13_02221560(battlePartyTask, v3, 10 + v7, 8);

        if (expBarFilledPixels < 8) {
            expBarFilledPixels = 0;
        } else {
            expBarFilledPixels -= 8;
        }
    }

    Bg_ScheduleTilemapTransfer(battlePartyTask->background, 7);
}

static void ov13_02221560(BattlePartyTask *battlePartyTask, u16 param1, u16 x, u16 y)
{
    Bg_FillTilemapRect(battlePartyTask->background, 7, param1, x, y, 1, 1, 16);
}

static void ov13_02221590(BattlePartyTask *battlePartyTask, u16 param1, u8 param2)
{
    Bg_FillTilemapRect(battlePartyTask->background, 7, param1, 2 + param2 * 2, 14, 1, 1, 16);
    Bg_FillTilemapRect(battlePartyTask->background, 7, param1 + 1, 2 + param2 * 2 + 1, 14, 1, 1, 16);
    Bg_FillTilemapRect(battlePartyTask->background, 7, param1 + 32, 2 + param2 * 2, 14 + 1, 1, 1, 16);
    Bg_FillTilemapRect(battlePartyTask->background, 7, param1 + 33, 2 + param2 * 2 + 1, 14 + 1, 1, 1, 16);
}

static void ov13_02221630(BattlePartyTask *battlePartyTask)
{
    u16 i;

    for (i = 0; i < MAX_PARTY_SIZE; i++) {
        ov13_02221590(battlePartyTask, 0x125, i);
    }
}

static void SetupMoveContestInfo(BattlePartyTask *battlePartyTask, u8 screen)
{
    u32 v0;
    u16 v1;
    u16 v2;
    s8 v3;

    if (screen != IN_BATTLE_SCREEN_LEARN_MOVE_CONTEST) {
        return;
    }

    ov13_02221630(battlePartyTask);

    if (battlePartyTask->battleInfo->unk_34 < 4) {
        PartyPokemonMoveData *v4 = &battlePartyTask->partyPokemon[battlePartyTask->battleInfo->selectedPartySlot].moves[battlePartyTask->battleInfo->unk_34];

        v2 = v4->move;
    } else {
        v2 = battlePartyTask->battleInfo->unk_24;
    }

    v0 = MoveTable_LoadParam(v2, MOVEATTRIBUTE_CONTEST_EFFECT);
    v3 = sub_02095734(v0) / 10;

    for (v1 = 0; v1 < v3; v1++) {
        ov13_02221590(battlePartyTask, 0x140, v1);
    }

    Bg_ScheduleTilemapTransfer(battlePartyTask->background, 7);
}

static void ChangeBattlePartyScreen(BattlePartyTask *battlePartyTask, u8 screen)
{
    ov13_02221738(battlePartyTask, screen);

    Bg_ScheduleFillTilemap(battlePartyTask->background, BG_LAYER_SUB_0, 0);
    Bg_ScheduleFillTilemap(battlePartyTask->background, BG_LAYER_SUB_1, 0);

    ov13_02224B7C(battlePartyTask, screen); // Sprite related
    ClearInBattlePartyScreen(battlePartyTask);
    InitializeInBattlePartyScreen(battlePartyTask, screen);
    DrawInBattlePartyScreen(battlePartyTask, screen);
    SetupEXPBar(battlePartyTask, screen);
    SetupMoveContestInfo(battlePartyTask, screen);
    ov13_0222563C(battlePartyTask, screen); // Some kind of setup
    ov13_022260EC(battlePartyTask, screen); // Another setup
    ov13_02226444(battlePartyTask, screen); // Setup pallete

    battlePartyTask->currentScreen = screen;
}

static const u32 Unk_ov13_02228E50[][2] = {
    { 0x1, 0x0 },
    { 0x13, 0x12 },
    { 0x5, 0x4 },
    { 0x3, 0x2 },
    { 0x7, 0x6 },
    { 0x9, 0x8 },
    { 0xB, 0xA },
    { 0xF, 0xE },
    { 0xD, 0xC },
    { 0x11, 0x10 }
};

static void ov13_02221738(BattlePartyTask *battlePartyTask, u8 screen)
{
    NNSG2dScreenData *screenData;
    void *buffer;
    u32 i;

    for (i = 0; i < 2; i++) {
        buffer = NARC_AllocAndReadWholeMemberByIndexPair(NARC_INDEX_BATTLE__GRAPHIC__PL_B_PLIST_GRA, Unk_ov13_02228E50[screen][i], battlePartyTask->battleInfo->heapID);
        NNS_G2dGetUnpackedScreenData(buffer, &screenData);
        Bg_LoadToTilemapRect(battlePartyTask->background, BG_LAYER_SUB_2 + i, (u16 *)screenData->rawData, 0, 0, 32, 24);
        Bg_ScheduleTilemapTransfer(battlePartyTask->background, BG_LAYER_SUB_2 + i);
        Heap_FreeToHeap(buffer);
    }
}

static u8 CheckPokemonCanBeSwitchedTo(BattlePartyTask *battlePartyTask)
{
    PartyPokemonData *selectedPokemonData;
    Strbuf *strBuf;

    selectedPokemonData = &battlePartyTask->partyPokemon[battlePartyTask->battleInfo->selectedPartySlot];

    if (CheckIfSwitchingWithPartnersPokemon(battlePartyTask, battlePartyTask->battleInfo->selectedPartySlot) == TRUE) {
        strBuf = MessageLoader_GetNewStrbuf(battlePartyTask->messageLoader, IN_BATTLE_TEXT_INDEX_CANT_SWITCH_TO_PARTNERS_POKEMON);
        {
            int partnerID;

            partnerID = BattleSystem_Partner(battlePartyTask->battleInfo->battleSystem, battlePartyTask->battleInfo->unk_28);
            StringTemplate_SetTrainerNameBattle(battlePartyTask->stringTemplate, 0, BattleSystem_GetTrainer(battlePartyTask->battleInfo->battleSystem, partnerID));
        }
        StringTemplate_Format(battlePartyTask->stringTemplate, battlePartyTask->strbuf, strBuf);
        Strbuf_Free(strBuf);
        return FALSE;
    }

    if (selectedPokemonData->currentHP == 0) {
        strBuf = MessageLoader_GetNewStrbuf(battlePartyTask->messageLoader, IN_BATTLE_TEXT_INDEX_POKEMON_HAS_NO_HP_LEFT);
        StringTemplate_SetNickname(battlePartyTask->stringTemplate, 0, Pokemon_GetBoxPokemon(selectedPokemonData->pokemon));
        StringTemplate_Format(battlePartyTask->stringTemplate, battlePartyTask->strbuf, strBuf);
        Strbuf_Free(strBuf);
        return FALSE;
    }

    if ((battlePartyTask->battleInfo->unk_2C[battlePartyTask->battleInfo->selectedPartySlot] == battlePartyTask->battleInfo->unk_14) || (battlePartyTask->battleInfo->unk_2C[battlePartyTask->battleInfo->selectedPartySlot] == battlePartyTask->battleInfo->unk_15)) {
        strBuf = MessageLoader_GetNewStrbuf(battlePartyTask->messageLoader, IN_BATTLE_TEXT_INDEX_POKEMON_ALREADY_IN_BATTLE);
        StringTemplate_SetNickname(battlePartyTask->stringTemplate, 0, Pokemon_GetBoxPokemon(selectedPokemonData->pokemon));
        StringTemplate_Format(battlePartyTask->stringTemplate, battlePartyTask->strbuf, strBuf);
        Strbuf_Free(strBuf);
        return FALSE;
    }

    if (CheckSelectedPokemonIsEgg(battlePartyTask) == TRUE) {
        MessageLoader_GetStrbuf(battlePartyTask->messageLoader, IN_BATTLE_TEXT_INDEX_POKEMON_EGG_CANT_BATTLE, battlePartyTask->strbuf);
        return FALSE;
    }

    // Has already been selected
    if ((battlePartyTask->battleInfo->unk_12 != 6) && (battlePartyTask->battleInfo->unk_2C[battlePartyTask->battleInfo->selectedPartySlot] == battlePartyTask->battleInfo->unk_12)) {
        selectedPokemonData = &battlePartyTask->partyPokemon[battlePartyTask->battleInfo->selectedPartySlot];
        strBuf = MessageLoader_GetNewStrbuf(battlePartyTask->messageLoader, 93);

        StringTemplate_SetNickname(battlePartyTask->stringTemplate, 0, Pokemon_GetBoxPokemon(selectedPokemonData->pokemon));
        StringTemplate_Format(battlePartyTask->stringTemplate, battlePartyTask->strbuf, strBuf);
        Strbuf_Free(strBuf);
        return FALSE;
    }

    // Can't be switched out as needs to learn move
    if (battlePartyTask->battleInfo->unk_24 != MOVE_NONE) {
        selectedPokemonData = &battlePartyTask->partyPokemon[battlePartyTask->selectedPartySlot];
        strBuf = MessageLoader_GetNewStrbuf(battlePartyTask->messageLoader, 78);

        StringTemplate_SetNickname(battlePartyTask->stringTemplate, 0, Pokemon_GetBoxPokemon(selectedPokemonData->pokemon));
        StringTemplate_Format(battlePartyTask->stringTemplate, battlePartyTask->strbuf, strBuf);
        Strbuf_Free(strBuf);
        return FALSE;
    }

    return TRUE;
}

static u8 CheckSelectedPokemonIsEgg(BattlePartyTask *battlePartyTask)
{
    if (battlePartyTask->partyPokemon[battlePartyTask->battleInfo->selectedPartySlot].isEgg != FALSE) {
        return TRUE;
    }

    return FALSE;
}

u8 ov13_0222196C(BattlePartyTask *battlePartyTask)
{
    u32 battleType = BattleSystem_BattleType(battlePartyTask->battleInfo->battleSystem);

    if ((battleType != BATTLE_TYPE_AI_PARTNER)
        && (battleType != (BATTLE_TYPE_TRAINER_DOUBLES | BATTLE_TYPE_2vs2 | BATTLE_TYPE_AI))
        && (battleType & (BATTLE_TYPE_DOUBLES | BATTLE_TYPE_TAG))) {
        return TRUE;
    }

    return FALSE;
}

u8 ov13_0222198C(BattlePartyTask *battlePartyTask)
{
    u32 battleType = BattleSystem_BattleType(battlePartyTask->battleInfo->battleSystem);

    if ((battleType != BATTLE_TYPE_AI_PARTNER)
        && (battleType != (BATTLE_TYPE_TRAINER_DOUBLES | BATTLE_TYPE_2vs2 | BATTLE_TYPE_AI))
        && (battleType & BATTLE_TYPE_2vs2)) {
        return TRUE;
    }

    return FALSE;
}

u8 CheckIfSwitchingWithPartnersPokemon(BattlePartyTask *battlePartyTask, u8 partySlot)
{
    if (ov13_0222198C(battlePartyTask) == TRUE) {
        if (battlePartyTask->battlerType == 2) {
            if ((partySlot & 1) != 0) {
                return TRUE;
            }
        } else {
            if ((partySlot & 1) == 0) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

static u8 CheckSelectedMoveIsHM(BattlePartyTask *battlePartyTask)
{
    u16 move;

    if (battlePartyTask->battleInfo->unk_34 == 4) {
        move = battlePartyTask->battleInfo->unk_24;
    } else {
        move = battlePartyTask->partyPokemon[battlePartyTask->battleInfo->selectedPartySlot].moves[battlePartyTask->battleInfo->unk_34].move;
    }

    return Item_IsHMMove(move);
}

static void ov13_02221A04(BattlePartyTask *battlePartyTask)
{
    ManagedSprite_SetDrawFlag(battlePartyTask->unk_1FB4[26], FALSE);
    Window_ClearAndScheduleCopyToVRAM(&battlePartyTask->windows[10]);
    Window_ClearAndScheduleCopyToVRAM(&battlePartyTask->windows[6]);
    Window_ClearAndScheduleCopyToVRAM(&battlePartyTask->windows[7]);
}

static void ov13_02221A3C(BattlePartyTask *battlePartyTask)
{
    ov13_02221630(battlePartyTask);
    Bg_ScheduleTilemapTransfer(battlePartyTask->background, BG_LAYER_SUB_3);
}

static void UseBagItem(BattleSystem *battleSys, u16 item, u16 category, u32 heapID)
{
    if (item != ITEM_BLUE_FLUTE && item != ITEM_RED_FLUTE && item != ITEM_YELLOW_FLUTE) {
        Bag_TryRemoveItem(BattleSystem_Bag(battleSys), item, 1, heapID);
    }

    Bag_SetLastBattleItemUsed(BattleSystem_BagCursor(battleSys), item, category);
}
