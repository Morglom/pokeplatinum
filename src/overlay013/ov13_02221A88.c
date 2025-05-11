#include "overlay013/ov13_02221A88.h"

#include <nitro.h>
#include <string.h>

#include "applications/pokemon_summary_screen/main.h"
#include "battle/ov16_0223DF00.h"
#include "overlay013/struct_ov13_0221FC20.h"
#include "overlay013/struct_ov13_022213F0.h"
#include "overlay013/struct_ov13_02221ED0.h"
#include "overlay013/struct_ov13_022236B8.h"

#include "bg_window.h"
#include "font.h"
#include "heap.h"
#include "item.h"
#include "message.h"
#include "move_table.h"
#include "party.h"
#include "pokemon.h"
#include "render_text.h"
#include "render_window.h"
#include "strbuf.h"
#include "string_template.h"
#include "text.h"
#include "unk_0200C440.h"
#include "unk_0208C098.h"
#include "unk_02094EDC.h"

enum InBattleTextIds {
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_1_NAME_TEXT = 0,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_2_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_3_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_4_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_5_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_6_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_CHOOSE_POKEMON,
    IN_BATTLE_TEXT_IDS_USE_ON_POKEMON,
    IN_BATTLE_TEXT_IDS_ABILITY_TEXT,
    IN_BATTLE_TEXT_IDS_HELD_ITEM_TEXT,
    IN_BATTLE_TEXT_IDS_PP = 14,
    IN_BATTLE_TEXT_IDS_SHIFT,
    IN_BATTLE_TEXT_IDS_MALE_CHARACTER,
    IN_BATTLE_TEXT_IDS_FEMALE_CHARACTER,
    IN_BATTLE_TEXT_IDS_SUMMARY,
    IN_BATTLE_TEXT_IDS_CHECK_MOVES,
    IN_BATTLE_TEXT_IDS_NO_HELD_ITEM,
    IN_BATTLE_TEXT_IDS_LVL = 23,
    IN_BATTLE_TEXT_IDS_LVL_TEXT,
    IN_BATTLE_TEXT_IDS_NEXT_LVL,
    IN_BATTLE_TEXT_IDS_NEXT_LVL_TEXT,
    IN_BATTLE_TEXT_IDS_HP = 28,
    IN_BATTLE_TEXT_IDS_HP_TEXT,
    IN_BATTLE_TEXT_IDS_MAX_HP_TEXT,
    IN_BATTLE_TEXT_IDS_HP_DIVIDER,
    IN_BATTLE_TEXT_IDS_ATTACK,
    IN_BATTLE_TEXT_IDS_ATTACK_TEXT,
    IN_BATTLE_TEXT_IDS_DEFENCE,
    IN_BATTLE_TEXT_IDS_DEFENCE_TEXT,
    IN_BATTLE_TEXT_IDS_SP_ATK,
    IN_BATTLE_TEXT_IDS_SP_ATK_TEXT,
    IN_BATTLE_TEXT_IDS_SP_DEF,
    IN_BATTLE_TEXT_IDS_SP_DEF_TEXT,
    IN_BATTLE_TEXT_IDS_SPEED,
    IN_BATTLE_TEXT_IDS_SPEED_TEXT,
    IN_BATTLE_TEXT_IDS_PP_OTHER = 43,
    IN_BATTLE_TEXT_IDS_CURRENT_PP_TEXT,
    IN_BATTLE_TEXT_IDS_MAX_PP_TEXT,
    IN_BATTLE_TEXT_IDS_PP_DIVIDER,
    IN_BATTLE_TEXT_IDS_POWER = 48,
    IN_BATTLE_TEXT_IDS_POWER_TEXT,
    IN_BATTLE_TEXT_IDS_NO_VALUE,
    IN_BATTLE_TEXT_IDS_ACCURACY,
    IN_BATTLE_TEXT_IDS_ACCURACY_TEXT,
    IN_BATTLE_TEXT_IDS_CATEGORY,
    IN_BATTLE_TEXT_IDS_PHYSICAL,
    IN_BATTLE_TEXT_IDS_STATUS,
    IN_BATTLE_TEXT_IDS_SPECIAL,
    IN_BATTLE_TEXT_IDS_APPEAL_PTS,
    IN_BATTLE_TEXT_IDS_FORGET,
    IN_BATTLE_TEXT_IDS_CANCEL,
    IN_BATTLE_TEXT_IDS_HM_CANT_BE_FORGOTTEN,
    IN_BATTLE_TEXT_IDS_HP_RESTORED_TEXT = 82,
    IN_BATTLE_TEXT_IDS_POISON_CURED_TEXT,
    IN_BATTLE_TEXT_IDS_PARALYSIS_CURED_TEXT,
    IN_BATTLE_TEXT_IDS_BURN_CURED_TEXT,
    IN_BATTLE_TEXT_IDS_FROZEN_CURED_TEXT,
    IN_BATTLE_TEXT_IDS_PP_RESTORED_TEXT,
    IN_BATTLE_TEXT_IDS_FAINTED_CURED_TEXT,
    IN_BATTLE_TEXT_IDS_MADE_HEALTHY_TEXT,
    IN_BATTLE_TEXT_IDS_CONFUSION_CURED_TEXT,
    IN_BATTLE_TEXT_IDS_INFATUATION_CURED_TEXT,
    IN_BATTLE_TEXT_IDS_SLEEP_CURED_TEXT,
    IN_BATTLE_TEXT_IDS_RESTORE_WHICH_MOVE = 94,
    IN_BATTLE_TEXT_IDS_ITEM_USE_PREVENTED_TEXT,
};

static void DrawPartyList(UnkStruct_ov13_022213F0 *param0);
static void DrawSelectPartyPokemonScreen(UnkStruct_ov13_022213F0 *param0);
static void DrawInBattlePokemonSummaryScreen(UnkStruct_ov13_022213F0 *param0);
static void DrawCheckMovesScreen(UnkStruct_ov13_022213F0 *param0);
static void DrawMoveSummaryScreen(UnkStruct_ov13_022213F0 *param0);
static void DrawRestorePPScreen(UnkStruct_ov13_022213F0 *param0);
static void DrawLearnMoveScreen(UnkStruct_ov13_022213F0 *param0);
static void DrawConfirmLearnMove(UnkStruct_ov13_022213F0 *param0);
static void DrawConfirmLearnMoveContest(UnkStruct_ov13_022213F0 *param0);
static void WriteNameGenderOther(UnkStruct_ov13_022213F0 *param0, u32 param1);

static const WindowTemplate Unk_ov13_02228EA0[] = {
    { 0x4, 0x2, 0x15, 0x16, 0x2, 0xF, 0x1F },
    { 0x4, 0x2, 0x13, 0x1B, 0x4, 0xF, 0x1F }
};

static const WindowTemplate Unk_ov13_02228F54[] = {
    { 0x5, 0x0, 0x0, 0xF, 0x5, 0x9, 0x85 },
    { 0x5, 0x10, 0x1, 0xF, 0x5, 0x9, 0xD0 },
    { 0x5, 0x0, 0x6, 0xF, 0x5, 0x9, 0x11B },
    { 0x5, 0x10, 0x7, 0xF, 0x5, 0x9, 0x166 },
    { 0x5, 0x0, 0xC, 0xF, 0x5, 0x9, 0x1B1 },
    { 0x5, 0x10, 0xD, 0xF, 0x5, 0x9, 0x1FC }
};

static const WindowTemplate Unk_ov13_02228EDC[] = {
    { 0x5, 0xA, 0x4, 0xC, 0x3, 0x9, 0x1 },
    { 0x5, 0xB, 0xC, 0xA, 0x3, 0x9, 0x25 },
    { 0x5, 0x1, 0x14, 0xB, 0x3, 0x9, 0x43 },
    { 0x5, 0xE, 0x14, 0xB, 0x3, 0x9, 0x64 }
};

static const WindowTemplate Unk_ov13_02228FBC[] = {
    { 0x5, 0x5, 0x1, 0x9, 0x2, 0xD, 0x125 },
    { 0x5, 0x1, 0x6, 0xE, 0x5, 0x9, 0x149 },
    { 0x5, 0x11, 0x6, 0xE, 0x5, 0x9, 0x18F },
    { 0x5, 0x1, 0xC, 0xE, 0x5, 0x9, 0x1D5 },
    { 0x5, 0x11, 0xC, 0xE, 0x5, 0x9, 0x21B },
    { 0x5, 0xD, 0x14, 0xB, 0x3, 0x9, 0x104 },
    { 0x5, 0x5, 0x1, 0x9, 0x2, 0xD, 0x137 },
    { 0x5, 0x1, 0x6, 0xE, 0x5, 0x9, 0x261 },
    { 0x5, 0x11, 0x6, 0xE, 0x5, 0x9, 0x2A7 },
    { 0x5, 0x1, 0xC, 0xE, 0x5, 0x9, 0x2ED },
    { 0x5, 0x11, 0xC, 0xE, 0x5, 0x9, 0x333 }
};

static const WindowTemplate Unk_ov13_022290FC[] = {
    { 0x5, 0x5, 0x1, 0x9, 0x2, 0xD, 0x125 },
    { 0x5, 0x1, 0x9, 0xB, 0x2, 0xD, 0x149 },
    { 0x5, 0x1, 0xB, 0x12, 0x4, 0xD, 0x15F },
    { 0x5, 0x4, 0x10, 0xC, 0x2, 0xD, 0x1A7 },
    { 0x5, 0x18, 0x4, 0x7, 0x2, 0xD, 0x1BF },
    { 0x5, 0x1C, 0x7, 0x3, 0x2, 0xD, 0x1CD },
    { 0x5, 0x1C, 0x9, 0x3, 0x2, 0xD, 0x1D3 },
    { 0x5, 0x1C, 0xF, 0x3, 0x2, 0xD, 0x1D9 },
    { 0x5, 0x1C, 0xB, 0x3, 0x2, 0xD, 0x1DF },
    { 0x5, 0x1C, 0xD, 0x3, 0x2, 0xD, 0x1E5 },
    { 0x5, 0x19, 0x6, 0x6, 0x1, 0x9, 0x1EB },
    { 0x5, 0x5, 0x4, 0x3, 0x2, 0xD, 0x1F1 },
    { 0x5, 0xD, 0x6, 0x6, 0x2, 0xD, 0x1F7 },
    { 0x5, 0x15, 0x4, 0x2, 0x2, 0xD, 0x85 },
    { 0x5, 0x15, 0x7, 0x6, 0x2, 0xD, 0x89 },
    { 0x5, 0x15, 0x9, 0x6, 0x2, 0xD, 0x95 },
    { 0x5, 0x15, 0xF, 0x6, 0x2, 0xD, 0xA1 },
    { 0x5, 0x15, 0xB, 0x6, 0x2, 0xD, 0xAD },
    { 0x5, 0x15, 0xD, 0x6, 0x2, 0xD, 0xB9 },
    { 0x5, 0x1, 0x4, 0x4, 0x2, 0xD, 0xC5 },
    { 0x5, 0x1, 0x6, 0xB, 0x2, 0xD, 0xCD },
    { 0x5, 0xD, 0x14, 0xB, 0x3, 0x9, 0xE3 },
    { 0x5, 0x5, 0x1, 0x9, 0x2, 0xD, 0x137 },
    { 0x5, 0x1, 0x9, 0xB, 0x2, 0xD, 0x261 },
    { 0x5, 0x1, 0xB, 0x12, 0x4, 0xD, 0x277 },
    { 0x5, 0x4, 0x10, 0xC, 0x2, 0xD, 0x2BF },
    { 0x5, 0x18, 0x4, 0x7, 0x2, 0xD, 0x2D7 },
    { 0x5, 0x1C, 0x7, 0x3, 0x2, 0xD, 0x2E5 },
    { 0x5, 0x1C, 0x9, 0x3, 0x2, 0xD, 0x2EB },
    { 0x5, 0x1C, 0xF, 0x3, 0x2, 0xD, 0x2F1 },
    { 0x5, 0x1C, 0xB, 0x3, 0x2, 0xD, 0x2F7 },
    { 0x5, 0x1C, 0xD, 0x3, 0x2, 0xD, 0x2FD },
    { 0x5, 0x19, 0x6, 0x6, 0x1, 0x9, 0x303 },
    { 0x5, 0x5, 0x4, 0x3, 0x2, 0xD, 0x309 },
    { 0x5, 0xD, 0x6, 0x6, 0x2, 0xD, 0x30F }
};

static const WindowTemplate Unk_ov13_02229074[] = {
    { 0x4, 0x4, 0x5, 0xB, 0x2, 0xD, 0x9D },
    { 0x4, 0x17, 0x5, 0x5, 0x2, 0xD, 0xB7 },
    { 0x4, 0xA, 0x10, 0x3, 0x2, 0xD, 0xE1 },
    { 0x4, 0xA, 0xD, 0x3, 0x2, 0xD, 0xE7 },
    { 0x4, 0x10, 0x8, 0xF, 0xA, 0xD, 0xED },
    { 0x4, 0x6, 0xA, 0x8, 0x2, 0xD, 0x19B },
    { 0x4, 0x5, 0x1, 0x9, 0x2, 0xD, 0x8B },
    { 0x4, 0x14, 0x5, 0x2, 0x2, 0xD, 0xB3 },
    { 0x4, 0x1, 0x10, 0x8, 0x2, 0xD, 0xC1 },
    { 0x4, 0x1, 0xD, 0x8, 0x2, 0xD, 0xD1 },
    { 0x4, 0x1, 0x8, 0xC, 0x2, 0xD, 0x183 },
    { 0x4, 0x4, 0x5, 0xB, 0x2, 0xD, 0x1AB },
    { 0x4, 0x17, 0x5, 0x5, 0x2, 0xD, 0x1C1 },
    { 0x4, 0xA, 0x10, 0x3, 0x2, 0xD, 0x1CB },
    { 0x4, 0xA, 0xD, 0x3, 0x2, 0xD, 0x1D1 },
    { 0x4, 0x10, 0x8, 0xF, 0xA, 0xD, 0x1D7 },
    { 0x4, 0x6, 0xA, 0x8, 0x2, 0xD, 0x26D }
};

static const WindowTemplate Unk_ov13_02228F24[] = {
    { 0x4, 0x5, 0x1, 0x9, 0x2, 0xD, 0x85 },
    { 0x4, 0x1, 0x6, 0xE, 0x5, 0x9, 0x97 },
    { 0x4, 0x11, 0x6, 0xE, 0x5, 0x9, 0xDD },
    { 0x4, 0x1, 0xC, 0xE, 0x5, 0x9, 0x123 },
    { 0x4, 0x11, 0xC, 0xE, 0x5, 0x9, 0x169 },
    { 0x4, 0x9, 0x12, 0xE, 0x5, 0x9, 0x1AF }
};

static const WindowTemplate Unk_ov13_02229014[] = {
    { 0x5, 0x5, 0x1, 0x9, 0x2, 0xD, 0x1 },
    { 0x5, 0x4, 0x5, 0xB, 0x2, 0xD, 0x13 },
    { 0x5, 0x14, 0x5, 0x2, 0x2, 0xD, 0x29 },
    { 0x5, 0x17, 0x5, 0x5, 0x2, 0xD, 0x2D },
    { 0x5, 0x1, 0x10, 0x8, 0x2, 0xD, 0x5B },
    { 0x5, 0x1, 0xD, 0x8, 0x2, 0xD, 0x6B },
    { 0x5, 0xA, 0x10, 0x3, 0x2, 0xD, 0x7B },
    { 0x5, 0xA, 0xD, 0x3, 0x2, 0xD, 0x81 },
    { 0x5, 0x10, 0x8, 0xF, 0xA, 0xD, 0x87 },
    { 0x5, 0x1, 0x8, 0xC, 0x2, 0xD, 0x11D },
    { 0x5, 0x6, 0xA, 0x8, 0x2, 0xD, 0x135 },
    { 0x5, 0x7, 0x14, 0xC, 0x3, 0x9, 0x37 }
};

static const WindowTemplate Unk_ov13_02228EFC[] = {
    { 0x4, 0x5, 0x1, 0x9, 0x2, 0xD, 0x8B },
    { 0x4, 0x1, 0x6, 0xE, 0x5, 0x9, 0x9D },
    { 0x4, 0x11, 0x6, 0xE, 0x5, 0x9, 0xE3 },
    { 0x4, 0x1, 0xC, 0xE, 0x5, 0x9, 0x129 },
    { 0x4, 0x11, 0xC, 0xE, 0x5, 0x9, 0x16F }
};

static const WindowTemplate Unk_ov13_02228F84[] = {
    { 0x5, 0x5, 0x1, 0x9, 0x2, 0xD, 0x1 },
    { 0x5, 0x4, 0x8, 0xB, 0x2, 0xD, 0x13 },
    { 0x5, 0x14, 0x8, 0x2, 0x2, 0xD, 0x29 },
    { 0x5, 0x17, 0x8, 0x5, 0x2, 0xD, 0x2D },
    { 0x5, 0x2, 0xB, 0xC, 0x2, 0xD, 0x145 },
    { 0x5, 0x10, 0xB, 0xF, 0x6, 0xD, 0x15D },
    { 0x5, 0x7, 0x14, 0xC, 0x3, 0x9, 0x37 }
};

static const u32 partySlotEntryIDs[] = {
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_1_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_2_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_3_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_4_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_5_NAME_TEXT,
    IN_BATTLE_TEXT_IDS_PARTY_SLOT_6_NAME_TEXT
};

static const u32 moveSlotEntryIDs[] = {
    0x3D,
    0x40,
    0x43,
    0x46,
    0x49 // Move to learn
};

void ov13_02221A88(UnkStruct_ov13_022213F0 *param0)
{
    u32 i;

    for (i = 0; i < 2; i++) {
        Window_AddFromTemplate(param0->unk_1E0, &param0->unk_204C[i], &Unk_ov13_02228EA0[i]);
    }

    InitializeInBattleScreen(param0, param0->unk_2076);
}

void InitializeInBattleScreen(UnkStruct_ov13_022213F0 *param0, enum InBattleScreenIndex screenIndex)
{
    const WindowTemplate *v0;
    u8 i;

    switch (screenIndex) {
    case IN_BATTLE_SCREEN_INDEX_PARTY_LIST:
        v0 = Unk_ov13_02228F54;
        param0->unk_2070 = 6;
        break;
    case IN_BATTLE_SCREEN_INDEX_SELECT_POKEMON:
        v0 = Unk_ov13_02228EDC;
        param0->unk_2070 = 4;
        break;
    case IN_BATTLE_SCREEN_INDEX_POKEMON_SUMMARY:
        v0 = Unk_ov13_022290FC;
        param0->unk_2070 = 35;
        break;
    case IN_BATTLE_SCREEN_INDEX_CHECK_MOVES:
        v0 = Unk_ov13_02228FBC;
        param0->unk_2070 = 11;
        break;
    case IN_BATTLE_SCREEN_INDEX_MOVE_SUMMARY:
        v0 = Unk_ov13_02229074;
        param0->unk_2070 = 17;
        break;
    case IN_BATTLE_SCREEN_INDEX_RESTORE_PP:
        v0 = Unk_ov13_02228EFC;
        param0->unk_2070 = 5;
        break;
    case IN_BATTLE_SCREEN_LEARN_MOVE_1:
    case IN_BATTLE_SCREEN_LEARN_MOVE_2:
        v0 = Unk_ov13_02228F24;
        param0->unk_2070 = 6;
        break;
    case IN_BATTLE_SCREEN_LEARN_MOVE_CONFIRM:
        v0 = Unk_ov13_02229014;
        param0->unk_2070 = 12;
        break;
    case IN_BATTLE_SCREEN_LEARN_MOVE_CONTEST:
        v0 = Unk_ov13_02228F84;
        param0->unk_2070 = 7;
        break;
    }

    param0->unk_206C = Window_New(param0->unk_00->heapID, param0->unk_2070);

    for (i = 0; i < param0->unk_2070; i++) {
        Window_AddFromTemplate(param0->unk_1E0, &param0->unk_206C[i], &v0[i]);
    }
}

void ClearInBattleScreen(UnkStruct_ov13_022213F0 *param0)
{
    Windows_Delete(param0->unk_206C, param0->unk_2070);
}

void ov13_02221BC8(UnkStruct_ov13_022213F0 *param0)
{
    u32 i;

    Windows_Delete(param0->unk_206C, param0->unk_2070);

    for (i = 0; i < 2; i++) {
        Window_Remove(&param0->unk_204C[i]);
    }
}

void DrawInBattleScreen(UnkStruct_ov13_022213F0 *param0, enum InBattleScreenIndex screenIndex)
{
    switch (screenIndex) {
    case IN_BATTLE_SCREEN_INDEX_PARTY_LIST:
        DrawPartyList(param0);
        break;
    case IN_BATTLE_SCREEN_INDEX_SELECT_POKEMON:
        DrawSelectPartyPokemonScreen(param0);
        break;
    case IN_BATTLE_SCREEN_INDEX_POKEMON_SUMMARY:
        DrawInBattlePokemonSummaryScreen(param0);
        break;
    case IN_BATTLE_SCREEN_INDEX_CHECK_MOVES:
        DrawCheckMovesScreen(param0);
        break;
    case IN_BATTLE_SCREEN_INDEX_MOVE_SUMMARY:
        DrawMoveSummaryScreen(param0);
        break;
    case IN_BATTLE_SCREEN_INDEX_RESTORE_PP:
        DrawRestorePPScreen(param0);
        break;
    case IN_BATTLE_SCREEN_LEARN_MOVE_1:
    case IN_BATTLE_SCREEN_LEARN_MOVE_2:
        DrawLearnMoveScreen(param0);
        break;
    case IN_BATTLE_SCREEN_LEARN_MOVE_CONFIRM:
        DrawConfirmLearnMove(param0);
        break;
    case IN_BATTLE_SCREEN_LEARN_MOVE_CONTEST:
        DrawConfirmLearnMoveContest(param0);
        break;
    }
}

static void DrawSummaryScreenHeader(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, enum Font font, u16 partyIndex, u8 xOffset, u8 yOffset)
{
    Window *v0;
    PartyPokemonData *v1;
    Strbuf *v2;
    Strbuf *v3;
    u32 v4;

    v0 = &param0->unk_206C[windowIndex];
    v1 = &param0->unk_04[partyIndex];
    v2 = Strbuf_Init(12, param0->unk_00->heapID);
    v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, partySlotEntryIDs[partyIndex]);

    StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v1->pokemon));
    StringTemplate_Format(param0->unk_1FA8, v2, v3);

    if (font == FONT_SYSTEM) {
        Text_AddPrinterWithParamsAndColor(v0, font, v2, xOffset, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    } else {
        Text_AddPrinterWithParamsAndColor(v0, font, v2, xOffset, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(7, 8, 9), NULL);
    }

    Strbuf_Free(v3);
    Strbuf_Free(v2);

    if ((v1->displayGender == FALSE) && (v1->isEgg == FALSE)) {
        if (v1->gender == GENDER_MALE) {
            v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_MALE_CHARACTER);
            v4 = Window_GetWidth(v0) * 8 - Font_CalcStrbufWidth(FONT_SYSTEM, v3, 0);

            if (font == FONT_SYSTEM) {
                Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v3, v4, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(7, 8, 0), NULL);
            } else {
                Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v3, v4, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(10, 11, 0), NULL);
            }

            Strbuf_Free(v3);
        } else if (v1->gender == GENDER_FEMALE) {
            v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_FEMALE_CHARACTER);
            v4 = Window_GetWidth(v0) * 8 - Font_CalcStrbufWidth(FONT_SYSTEM, v3, 0);

            if (font == FONT_SYSTEM) {
                Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v3, v4, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 4, 0), NULL);
            } else {
                Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v3, v4, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(12, 13, 0), NULL);
            }

            Strbuf_Free(v3);
        }
    }

    Window_ScheduleCopyToVRAM(v0);
}

static void ov13_02221E08(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u16 partyIndex, u8 x, u8 y)
{
    PartyPokemonData *v0 = &param0->unk_04[partyIndex];

    sub_0200C648(param0->unk_1FA0, 1, v0->level, 3, 0, &param0->unk_206C[windowIndex], x + 8, y);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[windowIndex]);
}

static void ov13_02221E50(UnkStruct_ov13_022213F0 *param0, u32 param1, u16 param2, u8 param3, u8 param4)
{
    PartyPokemonData *v0 = &param0->unk_04[param2];

    sub_0200C5BC(param0->unk_1FA0, v0->currentHP, 3, 1, &param0->unk_206C[param1], param3, param4);
    sub_0200C578(param0->unk_1FA0, 0, &param0->unk_206C[param1], param3 + 8 * 3, param4);
    sub_0200C5BC(param0->unk_1FA0, v0->maxHP, 3, 0, &param0->unk_206C[param1], param3 + 8 * 3 + 8, param4);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[param1]);
}

static void DrawHealthBar(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u16 partyIndex, u8 x, u8 y)
{
    PartyPokemonData *pokemon;
    u8 v1 = 1;
    u8 healthBarFilledPixels;

    pokemon = &param0->unk_04[partyIndex];
    healthBarFilledPixels = App_PixelCount(pokemon->currentHP, pokemon->maxHP, 48);

    switch (HealthBar_Color(pokemon->currentHP, pokemon->maxHP, 48)) {
    case BARCOLOR_EMPTY:
        Window_ScheduleCopyToVRAM(&param0->unk_206C[windowIndex]);
        return;
    case BARCOLOR_MAX:
    case BARCOLOR_GREEN:
        v1 = 1;
        break;
    case BARCOLOR_YELLOW:
        v1 = 3;
        break;
    case BARCOLOR_RED:
        v1 = 5;
        break;
    }

    Window_FillRectWithColor(&param0->unk_206C[windowIndex], v1 + 1, x, y + 1, healthBarFilledPixels, 1);
    Window_FillRectWithColor(&param0->unk_206C[windowIndex], v1, x, y + 2, healthBarFilledPixels, 2);
    Window_FillRectWithColor(&param0->unk_206C[windowIndex], v1 + 1, x, y + 4, healthBarFilledPixels, 1);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[windowIndex]);
}

static void WriteAbilityText(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u32 partyIndex)
{
    PartyPokemonData *pokemonData;
    Strbuf *v1;
    Strbuf *v2;

    pokemonData = &param0->unk_04[partyIndex];
    v1 = Strbuf_Init(16, param0->unk_00->heapID);
    v2 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_ABILITY_TEXT);

    StringTemplate_SetAbilityName(param0->unk_1FA8, 0, pokemonData->ability);
    StringTemplate_Format(param0->unk_1FA8, v1, v2);
    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[windowIndex], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v2);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[windowIndex]);
}

static void WriteHeldItem(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u32 partyIndex)
{
    PartyPokemonData *v0;
    Strbuf *v1;
    Strbuf *v2;

    v0 = &param0->unk_04[partyIndex];

    if (v0->heldItem == ITEM_NONE) {
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_NO_HELD_ITEM);
    } else {
        v1 = Strbuf_Init(18, param0->unk_00->heapID);
        v2 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_HELD_ITEM_TEXT);

        StringTemplate_SetItemName(param0->unk_1FA8, 0, v0->heldItem);
        StringTemplate_Format(param0->unk_1FA8, v1, v2);
        Strbuf_Free(v2);
    }

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[windowIndex], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[windowIndex]);
}

static void WriteMoveName(UnkStruct_ov13_022213F0 *param0, u32 move, u32 windowIndex, u32 param3, u16 font, u16 yOffset, TextColor textColor)
{
    Window *v0;
    Strbuf *v1;
    Strbuf *v2;
    u32 xOffset;

    v0 = &param0->unk_206C[windowIndex];
    v1 = Strbuf_Init(16, param0->unk_00->heapID);
    v2 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, param3);

    StringTemplate_SetMoveName(param0->unk_1FA8, 0, move);
    StringTemplate_Format(param0->unk_1FA8, v1, v2);

    if (font == FONT_SUBSCREEN) {
        xOffset = (Window_GetWidth(v0) * 8 - Font_CalcStrbufWidth(font, v1, 0)) / 2;
    } else {
        xOffset = 0;
    }

    Text_AddPrinterWithParamsAndColor(v0, font, v1, xOffset, yOffset, TEXT_SPEED_NO_TRANSFER, textColor, NULL);
    Strbuf_Free(v2);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteSystemFontPP(UnkStruct_ov13_022213F0 *param0, u16 windowIndex, u8 xOffset, u8 yOffset)
{
    Strbuf *v0 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_PP);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[windowIndex], FONT_SYSTEM, v0, xOffset, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v0);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[windowIndex]);
}

static void DrawPartyListSubText(UnkStruct_ov13_022213F0 *param0, u32 param1)
{
    Strbuf *v0;

    Window_DrawMessageBoxWithScrollCursor(&param0->unk_204C[0], 1, 1, 14);
    Window_FillTilemap(&param0->unk_204C[0], 15);

    v0 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, param1);

    Text_AddPrinterWithParamsAndColor(&param0->unk_204C[0], FONT_MESSAGE, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v0);
    Window_ScheduleCopyToVRAM(&param0->unk_204C[0]);
}

static void ov13_0222222C(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u32 param2)
{
    Window *v0;
    Strbuf *v1;
    u32 xOffset;

    v0 = &param0->unk_206C[windowIndex];
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, param2);
    xOffset = Font_CalcStrbufWidth(FONT_SUBSCREEN, v1, 0);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SUBSCREEN, v1, (Window_GetWidth(v0) * 8 - xOffset) / 2, 6, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(7, 8, 9), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteLevel(UnkStruct_ov13_022213F0 *param0, u32 partyIndex)
{
    PartyPokemonData *pokemonData;
    Strbuf *v1;
    Strbuf *v2;
    u16 v3;
    u16 v4;

    pokemonData = &param0->unk_04[partyIndex];
    v4 = 22 * param0->unk_2071;
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_LVL);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[19], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_LVL_TEXT);
    v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, pokemonData->level, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);
    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[11 + v4], FONT_SYSTEM, v2, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_NEXT_LVL);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[20], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_NEXT_LVL_TEXT);
    v2 = Strbuf_Init((6 + 1) * 2, param0->unk_00->heapID);

    if (pokemonData->level < MAX_POKEMON_LEVEL) {
        StringTemplate_SetNumber(
            param0->unk_1FA8, 0, pokemonData->nextLevelExp - pokemonData->exp, 6, 1, 1);
    } else {
        StringTemplate_SetNumber(
            param0->unk_1FA8, 0, 0, 6, 1, 1);
    }

    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v3 = Window_GetWidth(&param0->unk_206C[12 + v4]) * 8 - Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[12 + v4], FONT_SYSTEM, v2, v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[19]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[11 + v4]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[20]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[12 + v4]);
}

static void WriteAttackStat(UnkStruct_ov13_022213F0 *param0, u32 partyIndex)
{
    PartyPokemonData *pokemonData;
    Strbuf *v1;
    Strbuf *v2;
    u16 v3;
    u8 v4;
    u8 v5;

    pokemonData = &param0->unk_04[partyIndex];
    v3 = 22 * param0->unk_2071;
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_ATTACK);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[14], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_ATTACK_TEXT);
    v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, pokemonData->attack, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v4 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);
    v5 = Window_GetWidth(&param0->unk_206C[5 + v3]) * 8 - v4;

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[5 + v3], FONT_SYSTEM, v2, v5, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[14]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[5 + v3]);
}

static void WriteDefenceStat(UnkStruct_ov13_022213F0 *param0, u32 partyIndex)
{
    PartyPokemonData *pokemonData;
    Strbuf *v1;
    Strbuf *v2;
    u16 v3;
    u8 v4;
    u8 v5;

    pokemonData = &param0->unk_04[partyIndex];
    v3 = 22 * param0->unk_2071;
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_DEFENCE);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[15], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_DEFENCE_TEXT);
    v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, pokemonData->defence, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v4 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);
    v5 = Window_GetWidth(&param0->unk_206C[6 + v3]) * 8 - v4;

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[6 + v3], FONT_SYSTEM, v2, v5, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[15]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[6 + v3]);
}

static void WriteSpeedStat(UnkStruct_ov13_022213F0 *param0, u32 partyIndex)
{
    PartyPokemonData *pokemonData;
    Strbuf *v1;
    Strbuf *v2;
    u16 v3;
    u8 v4;
    u8 v5;

    pokemonData = &param0->unk_04[partyIndex];
    v3 = 22 * param0->unk_2071;
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_SPEED);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[16], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_SPEED_TEXT);
    v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, pokemonData->speed, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v4 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);
    v5 = Window_GetWidth(&param0->unk_206C[7 + v3]) * 8 - v4;

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[7 + v3], FONT_SYSTEM, v2, v5, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);

    Window_ScheduleCopyToVRAM(&param0->unk_206C[16]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[7 + v3]);
}

static void WriteSpAtkStat(UnkStruct_ov13_022213F0 *param0, u32 partyIndex)
{
    PartyPokemonData *pokemonData;
    Strbuf *v1;
    Strbuf *v2;
    u16 v3;
    u8 v4;
    u8 v5;

    pokemonData = &param0->unk_04[partyIndex];
    v3 = 22 * param0->unk_2071;
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_SP_ATK);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[17], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_SP_ATK_TEXT);
    v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, pokemonData->spAtk, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v4 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);
    v5 = Window_GetWidth(&param0->unk_206C[8 + v3]) * 8 - v4;

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[8 + v3], FONT_SYSTEM, v2, v5, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[17]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[8 + v3]);
}

static void WriteSpDefStat(UnkStruct_ov13_022213F0 *param0, u32 partyIndex)
{
    PartyPokemonData *pokemonData;
    Strbuf *v1;
    Strbuf *v2;
    u16 v3;
    u8 v4;
    u8 v5;

    pokemonData = &param0->unk_04[partyIndex];
    v3 = 22 * param0->unk_2071;
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_SP_DEF);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[18], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_SP_DEF_TEXT);
    v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, pokemonData->spDef, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v4 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);
    v5 = Window_GetWidth(&param0->unk_206C[9 + v3]) * 8 - v4;

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[9 + v3], FONT_SYSTEM, v2, v5, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[18]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[9 + v3]);
}

static void WriteHPStat(UnkStruct_ov13_022213F0 *param0, u32 partyIndex)
{
    PartyPokemonData *pokemonData;
    Strbuf *v1;
    Strbuf *v2;
    u32 v3, v4;
    u16 v5;
    u16 v6;

    pokemonData = &param0->unk_04[partyIndex];
    v6 = 22 * param0->unk_2071;
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_HP);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[13], FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_HP_DIVIDER);
    v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v1, 0);
    v5 = (Window_GetWidth(&param0->unk_206C[4]) * 8 - v3) / 2;

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[4 + v6], FONT_SYSTEM, v1, v5, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_HP_TEXT);
    v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, pokemonData->currentHP, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v4 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[4 + v6], FONT_SYSTEM, v2, v5 - v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_MAX_HP_TEXT);
    v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, pokemonData->maxHP, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);
    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[4 + v6], FONT_SYSTEM, v2, v5 + v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[13]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[4 + v6]);
}

static void WriteAbilityStat(UnkStruct_ov13_022213F0 *param0, u32 partyIndex)
{
    PartyPokemonData *pokemonData;
    MessageLoader *v1;
    Strbuf *v2;
    u32 v3;

    pokemonData = &param0->unk_04[partyIndex];
    v3 = 22 * param0->unk_2071;
    v1 = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_ABILITY_DESCRIPTIONS, param0->unk_00->heapID);
    v2 = MessageLoader_GetNewStrbuf(v1, pokemonData->ability);

    Text_AddPrinterWithParamsAndColor(&param0->unk_206C[2 + v3], FONT_SYSTEM, v2, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v2);
    MessageLoader_Free(v1);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[2 + v3]);
}

static void WriteSystemFontAccuracy(UnkStruct_ov13_022213F0 *param0, u32 windowIndex)
{
    Window *v0;
    Strbuf *v1;

    v0 = &param0->unk_206C[windowIndex];
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_ACCURACY);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteMoveAccuracy(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u32 accuracy)
{
    Window *v0;
    Strbuf *v1;
    Strbuf *v2;
    u16 v3;
    u16 v4;

    v0 = &param0->unk_206C[windowIndex];

    if (accuracy == 0) {
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_NO_VALUE);
        v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v1, 0);
        v4 = Window_GetWidth(v0) * 8 - v3;

        Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        Strbuf_Free(v1);
    } else {
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_ACCURACY_TEXT);
        v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

        StringTemplate_SetNumber(param0->unk_1FA8, 0, accuracy, 3, 0, 1);
        StringTemplate_Format(param0->unk_1FA8, v2, v1);

        v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);
        v4 = Window_GetWidth(v0) * 8 - v3;

        Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        Strbuf_Free(v1);
        Strbuf_Free(v2);
    }

    Window_ScheduleCopyToVRAM(v0);
}

static void WriteSystemFontPower(UnkStruct_ov13_022213F0 *param0, u32 windowIndex)
{
    Window *v0;
    Strbuf *v1;

    v0 = &param0->unk_206C[windowIndex];
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_POWER);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteMovePower(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u32 power)
{
    Window *v0;
    Strbuf *v1;
    Strbuf *v2;
    u16 v3;
    u16 v4;

    v0 = &param0->unk_206C[windowIndex];

    if (power <= 1) {
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_NO_VALUE);
        v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v1, 0);
        v4 = Window_GetWidth(v0) * 8 - v3;

        Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        Strbuf_Free(v1);
    } else {
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_POWER_TEXT);
        v2 = Strbuf_Init((3 + 1) * 2, param0->unk_00->heapID);

        StringTemplate_SetNumber(param0->unk_1FA8, 0, power, 3, 0, 1);
        StringTemplate_Format(param0->unk_1FA8, v2, v1);

        v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);
        v4 = Window_GetWidth(v0) * 8 - v3;

        Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        Strbuf_Free(v1);
        Strbuf_Free(v2);
    }

    Window_ScheduleCopyToVRAM(v0);
}

static void WriteMoveDescription(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u32 move)
{
    MessageLoader *v0;
    Window *v1;
    Strbuf *v2;

    v1 = &param0->unk_206C[windowIndex];
    v0 = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_MOVE_DESCRIPTIONS, param0->unk_00->heapID);
    v2 = MessageLoader_GetNewStrbuf(v0, move);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v2);
    MessageLoader_Free(v0);
    Window_ScheduleCopyToVRAM(v1);
}

static void WriteMoveContestEffect(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u32 move)
{
    MessageLoader *v0;
    Window *v1;
    Strbuf *v2;
    u32 v3;
    u32 v4;

    v1 = &param0->unk_206C[windowIndex];
    v3 = MoveTable_LoadParam(move, MOVEATTRIBUTE_CONTEST_EFFECT);
    v4 = sub_0209577C(v3);
    v0 = MessageLoader_Init(MESSAGE_LOADER_BANK_HANDLE, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_CONTEST_EFFECTS, param0->unk_00->heapID);
    v2 = MessageLoader_GetNewStrbuf(v0, v4);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v2);

    MessageLoader_Free(v0);
    Window_ScheduleCopyToVRAM(v1);
}

static void WriteSystemFontCategory(UnkStruct_ov13_022213F0 *param0, u32 windowIndex)
{
    Window *v0;
    Strbuf *v1;
    u16 v2;
    u16 v3;

    v0 = &param0->unk_206C[windowIndex];
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_CATEGORY);
    v2 = Font_CalcStrbufWidth(FONT_SYSTEM, v1, 0);
    v3 = (Window_GetWidth(v0) * 8 - v2) / 2;

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteMoveCategory(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u32 moveClass)
{
    Window *v0;
    Strbuf *v1;

    v0 = &param0->unk_206C[windowIndex];

    switch (moveClass) {
    case CLASS_PHYSICAL:
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_PHYSICAL);
        break;
    case CLASS_SPECIAL:
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_SPECIAL);
        break;
    case CLASS_STATUS:
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_STATUS);
    }

    {
        u32 v2 = Font_CalcCenterAlignment(FONT_SYSTEM, v1, 0, 7 * 8);
        Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, v2, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }

    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteSystemFontMovePP(UnkStruct_ov13_022213F0 *param0, u32 windowIndex, u32 currentPP, u32 maxPP)
{
    Window *v0;
    Strbuf *v1;
    Strbuf *v2;
    u32 v3, v4;
    u32 v5;

    v0 = &param0->unk_206C[windowIndex];
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_PP_DIVIDER);
    v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v1, 0);
    v5 = (Window_GetWidth(v0) * 8 - v3) / 2;

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, v5, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_CURRENT_PP_TEXT);
    v2 = Strbuf_Init((2 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, currentPP, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v4 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v2, v5 - v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_MAX_PP_TEXT);
    v2 = Strbuf_Init((2 + 1) * 2, param0->unk_00->heapID);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, maxPP, 3, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v2, v5 + v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);
    Window_ScheduleCopyToVRAM(v0);
}

static void DrawCancelForgetButton(UnkStruct_ov13_022213F0 *param0, u32 windowIndex)
{
    Window *v0;
    Strbuf *v1;
    u32 v2;

    v0 = &param0->unk_206C[windowIndex];

    if (param0->unk_00->unk_34 == 4) {
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_CANCEL);
    } else {
        v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_FORGET);
    }

    v2 = Font_CalcStrbufWidth(FONT_SUBSCREEN, v1, 0);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SUBSCREEN, v1, (12 * 8 - v2) / 2, 6, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(7, 8, 9), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

void ov13_02223118(UnkStruct_ov13_022213F0 *param0)
{
    Window *v0;
    Strbuf *v1;

    if (param0->unk_2076 == IN_BATTLE_SCREEN_LEARN_MOVE_CONFIRM) {
        v0 = &param0->unk_206C[8];
    } else {
        v0 = &param0->unk_206C[5];
    }

    Window_FillTilemap(v0, 0);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_HM_CANT_BE_FORGOTTEN);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteMovePP(UnkStruct_ov13_022213F0 *param0, PartyPokemonMoveData *moveData, u32 windowIndex)
{
    Window *v0;
    Strbuf *v1;
    Strbuf *v2;
    u32 v3;

    v0 = &param0->unk_206C[windowIndex];
    v2 = Strbuf_Init((2 + 1) * 2, param0->unk_00->heapID);
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_PP_OTHER);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, 40, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_PP_DIVIDER);
    v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v1, 0);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, 80, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_MAX_PP_TEXT);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, moveData->maxPP, 2, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v2, 80 + v3, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_CURRENT_PP_TEXT);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, moveData->currentPP, 2, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v2, 80 - v3, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteMoveCurrentPP(UnkStruct_ov13_022213F0 *param0, PartyPokemonMoveData *moveData, u32 windowIndex)
{
    Window *v0;
    Strbuf *v1;
    Strbuf *v2;
    u32 v3;

    v0 = &param0->unk_206C[windowIndex];
    v2 = Strbuf_Init((2 + 1) * 2, param0->unk_00->heapID);
    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_PP_OTHER);
    v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v1, 0);

    Strbuf_Free(v1);
    Window_FillRectWithColor(v0, 0, 40 + v3, 24, 80 - (40 + v3), 16);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_CURRENT_PP_TEXT);

    StringTemplate_SetNumber(param0->unk_1FA8, 0, moveData->currentPP, 2, 0, 1);
    StringTemplate_Format(param0->unk_1FA8, v2, v1);

    v3 = Font_CalcStrbufWidth(FONT_SYSTEM, v2, 0);

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v2, 80 - v3, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    Strbuf_Free(v1);
    Strbuf_Free(v2);
    Window_ScheduleCopyToVRAM(v0);
}

static void DrawPartyList(UnkStruct_ov13_022213F0 *param0)
{
    s32 i;

    for (i = 0; i < Party_GetCurrentCount(param0->unk_00->unk_00); i++) {
        Window_FillTilemap(&param0->unk_206C[i], 0);

        if (param0->unk_04[i].species == SPECIES_NONE) {
            continue;
        }

        DrawSummaryScreenHeader(param0, i, FONT_SUBSCREEN, i, 32, 8);

        if (param0->unk_04[i].isEgg == FALSE) {
            DrawHealthDisplay(param0, i);
        }

        if (PokemonSummaryScreen_StatusIconAnimIdx(param0->unk_04[i].pokemon) != SUMMARY_CONDITION_NONE) {
            continue;
        }

        ov13_022234A8(param0, i);
    }

    if (param0->unk_00->unk_35 == 2) {
        DrawPartyListSubText(param0, IN_BATTLE_TEXT_IDS_USE_ON_POKEMON);
    } else {
        DrawPartyListSubText(param0, IN_BATTLE_TEXT_IDS_CHOOSE_POKEMON);
    }
}

void DrawHealthDisplay(UnkStruct_ov13_022213F0 *param0, u8 partyIndex)
{
    Window_FillRectWithColor(&param0->unk_206C[0 + partyIndex], 0, 56, 32, 24, 8);
    Window_FillRectWithColor(&param0->unk_206C[0 + partyIndex], 0, (48 + 16), 24, 64, 8);

    ov13_02221E50(param0, partyIndex, partyIndex, 56, 32);
    DrawHealthBar(param0, partyIndex, partyIndex, (48 + 16), 24);
}

void ov13_022234A8(UnkStruct_ov13_022213F0 *param0, u8 partyIndex)
{
    if (param0->unk_04[partyIndex].isEgg == FALSE) {
        ov13_02221E08(param0, partyIndex, partyIndex, 0, 32);
    }
}

static void DrawSelectPartyPokemonScreen(UnkStruct_ov13_022213F0 *param0)
{
    Window_FillTilemap(&param0->unk_206C[0], 0);
    Window_FillTilemap(&param0->unk_206C[1], 0);
    Window_FillTilemap(&param0->unk_206C[2], 0);
    Window_FillTilemap(&param0->unk_206C[3], 0);

    WriteNameGenderOther(param0, param0->unk_00->selectedPartyIndex);

    ov13_0222222C(param0, 1, IN_BATTLE_TEXT_IDS_SHIFT);

    if (param0->unk_04[param0->unk_00->selectedPartyIndex].isEgg == FALSE) {
        ov13_0222222C(param0, 2, IN_BATTLE_TEXT_IDS_SUMMARY);
        ov13_0222222C(param0, 3, IN_BATTLE_TEXT_IDS_CHECK_MOVES);
    } else {
        Window_ScheduleCopyToVRAM(&param0->unk_206C[2]);
        Window_ScheduleCopyToVRAM(&param0->unk_206C[3]);
    }
}

static void WriteNameGenderOther(UnkStruct_ov13_022213F0 *param0, u32 partyIndex)
{
    Window *v0;
    PartyPokemonData *pokemonData;
    Strbuf *v2;
    Strbuf *v3;
    u8 v4;
    u8 v5;
    u8 v6;
    u8 v7;

    v0 = &param0->unk_206C[0];
    pokemonData = &param0->unk_04[partyIndex];
    v2 = Strbuf_Init(12, param0->unk_00->heapID);
    v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, partySlotEntryIDs[partyIndex]);

    StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(pokemonData->pokemon));
    StringTemplate_Format(param0->unk_1FA8, v2, v3);
    Strbuf_Free(v3);

    v3 = NULL;

    if ((pokemonData->displayGender == FALSE) && (pokemonData->isEgg == FALSE)) {
        if (pokemonData->gender == GENDER_MALE) {
            v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_MALE_CHARACTER);
        } else if (pokemonData->gender == GENDER_FEMALE) {
            v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_FEMALE_CHARACTER);
        }
    }

    v4 = Font_CalcStrbufWidth(FONT_SUBSCREEN, v2, 0);

    if (v3 == NULL) {
        v5 = 0;
        v6 = 0;
    } else {
        v5 = Font_CalcStrbufWidth(FONT_SYSTEM, v3, 0);
        v6 = 8;
    }

    v7 = (Window_GetWidth(v0) * 8 - v4 - v5 - v6) / 2;

    Text_AddPrinterWithParamsAndColor(v0, FONT_SUBSCREEN, v2, v7, 8, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(7, 8, 9), NULL);
    Strbuf_Free(v2);

    if (v3 != NULL) {
        if (pokemonData->gender == GENDER_MALE) {
            Text_AddPrinterWithParamsAndColor(
                v0, FONT_SYSTEM, v3, v7 + v4 + v6, 8, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(10, 11, 0), NULL);
        } else {
            Text_AddPrinterWithParamsAndColor(
                v0, FONT_SYSTEM, v3, v7 + v4 + v6, 8, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(12, 13, 0), NULL);
        }

        Strbuf_Free(v3);
    }

    Window_ScheduleCopyToVRAM(v0);
}

static void DrawCheckMovesScreen(UnkStruct_ov13_022213F0 *param0)
{
    PartyPokemonMoveData *moveData;
    u16 v1, v2;

    v2 = 6 * param0->unk_2071;

    Window_FillTilemap(&param0->unk_206C[0 + v2], 0);
    Window_FillTilemap(&param0->unk_206C[1 + v2], 0);
    Window_FillTilemap(&param0->unk_206C[2 + v2], 0);
    Window_FillTilemap(&param0->unk_206C[3 + v2], 0);
    Window_FillTilemap(&param0->unk_206C[4 + v2], 0);
    Window_FillTilemap(&param0->unk_206C[5], 0);

    DrawSummaryScreenHeader(param0, 0 + v2, FONT_SYSTEM, param0->unk_00->selectedPartyIndex, 0, 0);

    for (v1 = 0; v1 < LEARNED_MOVES_MAX; v1++) {
        moveData = &param0->unk_04[param0->unk_00->selectedPartyIndex].moves[v1];

        if (moveData->move == MOVE_NONE) {
            continue;
        }

        WriteMoveName(param0, moveData->move, 1 + v2 + v1, moveSlotEntryIDs[v1], FONT_SUBSCREEN, 8, TEXT_COLOR(7, 8, 9));
        WriteMovePP(param0, moveData, 1 + v2 + v1);
    }

    ov13_0222222C(param0, 5, IN_BATTLE_TEXT_IDS_SUMMARY);

    Window_ScheduleCopyToVRAM(&param0->unk_206C[1 + v2]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[2 + v2]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[3 + v2]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[4 + v2]);

    param0->unk_2071 ^= 1;
}

static void DrawInBattlePokemonSummaryScreen(UnkStruct_ov13_022213F0 *param0)
{
    u32 v0 = 22 * param0->unk_2071;

    Window_FillTilemap(&param0->unk_206C[19], 0);
    Window_FillTilemap(&param0->unk_206C[20], 0);
    Window_FillTilemap(&param0->unk_206C[14], 0);
    Window_FillTilemap(&param0->unk_206C[15], 0);
    Window_FillTilemap(&param0->unk_206C[16], 0);
    Window_FillTilemap(&param0->unk_206C[17], 0);
    Window_FillTilemap(&param0->unk_206C[18], 0);
    Window_FillTilemap(&param0->unk_206C[13], 0);
    Window_FillTilemap(&param0->unk_206C[21], 0);

    Window_FillTilemap(&param0->unk_206C[0 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[10 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[11 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[12 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[5 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[6 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[7 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[8 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[9 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[4 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[1 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[2 + v0], 0);
    Window_FillTilemap(&param0->unk_206C[3 + v0], 0);

    DrawSummaryScreenHeader(param0, 0 + v0, FONT_SYSTEM, param0->unk_00->selectedPartyIndex, 0, 0);
    WriteHPStat(param0, param0->unk_00->selectedPartyIndex);
    DrawHealthBar(param0, 10 + v0, param0->unk_00->selectedPartyIndex, 0, 0);
    WriteLevel(param0, param0->unk_00->selectedPartyIndex);
    WriteAttackStat(param0, param0->unk_00->selectedPartyIndex);
    WriteDefenceStat(param0, param0->unk_00->selectedPartyIndex);
    WriteSpeedStat(param0, param0->unk_00->selectedPartyIndex);
    WriteSpAtkStat(param0, param0->unk_00->selectedPartyIndex);
    WriteSpDefStat(param0, param0->unk_00->selectedPartyIndex);
    WriteAbilityText(param0, 1 + v0, param0->unk_00->selectedPartyIndex);
    WriteHeldItem(param0, 3 + v0, param0->unk_00->selectedPartyIndex);
    WriteAbilityStat(param0, param0->unk_00->selectedPartyIndex);
    ov13_0222222C(param0, 21, 19);

    param0->unk_2071 ^= 1;
}

static void DrawMoveSummaryScreen(UnkStruct_ov13_022213F0 *param0)
{
    PartyPokemonMoveData *v0;
    u32 v1 = 11 * param0->unk_2071;

    Window_FillTilemap(&param0->unk_206C[6], 0);
    Window_FillTilemap(&param0->unk_206C[7], 0);
    Window_FillTilemap(&param0->unk_206C[8], 0);
    Window_FillTilemap(&param0->unk_206C[9], 0);
    Window_FillTilemap(&param0->unk_206C[10], 0);
    Window_FillTilemap(&param0->unk_206C[1 + v1], 0);
    Window_FillTilemap(&param0->unk_206C[0 + v1], 0);
    Window_FillTilemap(&param0->unk_206C[2 + v1], 0);
    Window_FillTilemap(&param0->unk_206C[3 + v1], 0);
    Window_FillTilemap(&param0->unk_206C[5 + v1], 0);
    Window_FillTilemap(&param0->unk_206C[4 + v1], 0);

    v0 = &param0->unk_04[param0->unk_00->selectedPartyIndex].moves[param0->unk_00->unk_34];

    DrawSummaryScreenHeader(param0, 6, FONT_SYSTEM, param0->unk_00->selectedPartyIndex, 0, 0);
    WriteSystemFontPP(param0, 7, 0, 0);
    WriteMoveName(param0, v0->move, 0 + v1, moveSlotEntryIDs[param0->unk_00->unk_34], FONT_SYSTEM, 0, TEXT_COLOR(15, 14, 0));
    WriteSystemFontAccuracy(param0, 8);
    WriteMoveAccuracy(param0, 2 + v1, v0->accuracy);
    WriteSystemFontPower(param0, 9);
    WriteMovePower(param0, 3 + v1, v0->power);
    WriteMoveDescription(param0, 4 + v1, v0->move);
    WriteSystemFontCategory(param0, 10);
    WriteMoveCategory(param0, 5 + v1, v0->class);
    WriteSystemFontMovePP(param0, 1 + v1, v0->currentPP, v0->maxPP);

    param0->unk_2071 ^= 1;
}

static void DrawLearnMoveScreen(UnkStruct_ov13_022213F0 *param0)
{
    PartyPokemonMoveData *v0;
    u32 v1;

    Window_FillTilemap(&param0->unk_206C[0], 0);
    Window_FillTilemap(&param0->unk_206C[1], 0);
    Window_FillTilemap(&param0->unk_206C[2], 0);
    Window_FillTilemap(&param0->unk_206C[3], 0);
    Window_FillTilemap(&param0->unk_206C[4], 0);
    Window_FillTilemap(&param0->unk_206C[5], 0);

    DrawSummaryScreenHeader(param0, 0, FONT_SYSTEM, param0->unk_00->selectedPartyIndex, 0, 0);

    for (v1 = 0; v1 < LEARNED_MOVES_MAX; v1++) {
        v0 = &param0->unk_04[param0->unk_00->selectedPartyIndex].moves[v1];

        if (v0->move == MOVE_NONE) {
            continue;
        }

        WriteMoveName(param0, v0->move, 1 + v1, moveSlotEntryIDs[v1], FONT_SUBSCREEN, 8, TEXT_COLOR(7, 8, 9));
        WriteMovePP(param0, v0, 1 + v1);
    }

    WriteMoveName(param0, param0->unk_00->unk_24, 5, moveSlotEntryIDs[4], FONT_SUBSCREEN, 8, TEXT_COLOR(7, 8, 9));
    {
        PartyPokemonMoveData v2;

        v2.currentPP = MoveTable_LoadParam(param0->unk_00->unk_24, MOVEATTRIBUTE_PP);
        v2.maxPP = v2.currentPP;

        WriteMovePP(param0, &v2, 5);
    }

    Window_ScheduleCopyToVRAM(&param0->unk_206C[1]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[2]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[3]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[4]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[5]);
}

static void DrawConfirmLearnMove(UnkStruct_ov13_022213F0 *param0)
{
    Window_FillTilemap(&param0->unk_206C[0], 0);
    Window_FillTilemap(&param0->unk_206C[2], 0);
    Window_FillTilemap(&param0->unk_206C[3], 0);
    Window_FillTilemap(&param0->unk_206C[1], 0);
    Window_FillTilemap(&param0->unk_206C[4], 0);
    Window_FillTilemap(&param0->unk_206C[6], 0);
    Window_FillTilemap(&param0->unk_206C[5], 0);
    Window_FillTilemap(&param0->unk_206C[7], 0);
    Window_FillTilemap(&param0->unk_206C[9], 0);
    Window_FillTilemap(&param0->unk_206C[10], 0);
    Window_FillTilemap(&param0->unk_206C[8], 0);
    Window_FillTilemap(&param0->unk_206C[11], 0);

    DrawSummaryScreenHeader(param0, 0, FONT_SYSTEM, param0->unk_00->selectedPartyIndex, 0, 0);
    WriteSystemFontPP(param0, 2, 0, 0);
    WriteSystemFontAccuracy(param0, 4);
    WriteSystemFontPower(param0, 5);
    WriteSystemFontCategory(param0, 9);

    if (param0->unk_00->unk_34 < LEARNED_MOVES_MAX) {
        PartyPokemonMoveData *v0 = &param0->unk_04[param0->unk_00->selectedPartyIndex].moves[param0->unk_00->unk_34];

        WriteMoveName(param0, v0->move, 1, moveSlotEntryIDs[param0->unk_00->unk_34], FONT_SYSTEM, 0, TEXT_COLOR(15, 14, 0));
        WriteMoveAccuracy(param0, 6, v0->accuracy);
        WriteMovePower(param0, 7, v0->power);
        WriteMoveDescription(param0, 8, v0->move);
        WriteMoveCategory(param0, 10, v0->class);
        WriteSystemFontMovePP(param0, 3, v0->currentPP, v0->maxPP);
    } else {
        u32 v1 = MoveTable_LoadParam(param0->unk_00->unk_24, MOVEATTRIBUTE_PP);

        WriteMoveName(param0, param0->unk_00->unk_24, 1, moveSlotEntryIDs[4], FONT_SYSTEM, 0, TEXT_COLOR(15, 14, 0));
        WriteMoveDescription(param0, 8, param0->unk_00->unk_24);
        WriteMoveAccuracy(param0, 6, MoveTable_LoadParam(param0->unk_00->unk_24, MOVEATTRIBUTE_ACCURACY));
        WriteMovePower(param0, 7, MoveTable_LoadParam(param0->unk_00->unk_24, MOVEATTRIBUTE_POWER));
        WriteMoveCategory(param0, 10, MoveTable_LoadParam(param0->unk_00->unk_24, MOVEATTRIBUTE_CLASS));
        WriteSystemFontMovePP(param0, 3, v1, v1);
    }

    DrawCancelForgetButton(param0, 11);
}

static void DrawRestorePPScreen(UnkStruct_ov13_022213F0 *param0)
{
    PartyPokemonMoveData *v0;
    u32 v1;

    Window_FillTilemap(&param0->unk_206C[0], 0);
    Window_FillTilemap(&param0->unk_206C[1], 0);
    Window_FillTilemap(&param0->unk_206C[2], 0);
    Window_FillTilemap(&param0->unk_206C[3], 0);
    Window_FillTilemap(&param0->unk_206C[4], 0);

    DrawSummaryScreenHeader(param0, 0, FONT_SYSTEM, param0->unk_00->selectedPartyIndex, 0, 0);

    for (v1 = 0; v1 < LEARNED_MOVES_MAX; v1++) {
        v0 = &param0->unk_04[param0->unk_00->selectedPartyIndex].moves[v1];

        if (v0->move == 0) {
            continue;
        }

        WriteMoveName(param0, v0->move, 1 + v1, moveSlotEntryIDs[v1], FONT_SUBSCREEN, 8, TEXT_COLOR(7, 8, 9));
        WriteMovePP(param0, v0, 1 + v1);
    }

    if (Item_LoadParam(param0->unk_00->unk_22, ITEM_PARAM_PP_RESTORE_ALL, param0->unk_00->heapID) == FALSE) {
        DrawPartyListSubText(param0, IN_BATTLE_TEXT_IDS_RESTORE_WHICH_MOVE);
    }

    Window_ScheduleCopyToVRAM(&param0->unk_206C[1]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[2]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[3]);
    Window_ScheduleCopyToVRAM(&param0->unk_206C[4]);
}

void ov13_02223F5C(UnkStruct_ov13_022213F0 *param0, u16 windowIndex, u16 moveIndex)
{
    PartyPokemonMoveData *moveData = &param0->unk_04[param0->unk_00->selectedPartyIndex].moves[moveIndex];
    WriteMoveCurrentPP(param0, moveData, windowIndex);
}

static void DrawConfirmLearnMoveContest(UnkStruct_ov13_022213F0 *param0)
{
    Window_FillTilemap(&param0->unk_206C[0], 0);
    Window_FillTilemap(&param0->unk_206C[2], 0);
    Window_FillTilemap(&param0->unk_206C[3], 0);
    Window_FillTilemap(&param0->unk_206C[1], 0);
    Window_FillTilemap(&param0->unk_206C[4], 0);
    Window_FillTilemap(&param0->unk_206C[5], 0);
    Window_FillTilemap(&param0->unk_206C[6], 0);

    DrawSummaryScreenHeader(param0, 0, FONT_SYSTEM, param0->unk_00->selectedPartyIndex, 0, 0);
    WriteSystemFontPP(param0, 2, 0, 0);

    {
        Strbuf *v0;

        v0 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_APPEAL_PTS);

        {
            u32 v1 = Font_CalcCenterAlignment(FONT_SYSTEM, v0, 0, 12 * 8);
            Text_AddPrinterWithParamsAndColor(&param0->unk_206C[4], FONT_SYSTEM, v0, v1, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
        }

        Strbuf_Free(v0);
        Window_ScheduleCopyToVRAM(&param0->unk_206C[4]);
    }

    if (param0->unk_00->unk_34 < LEARNED_MOVES_MAX) {
        PartyPokemonMoveData *v2 = &param0->unk_04[param0->unk_00->selectedPartyIndex].moves[param0->unk_00->unk_34];

        WriteMoveName(param0, v2->move, 1, moveSlotEntryIDs[param0->unk_00->unk_34], FONT_SYSTEM, 0, TEXT_COLOR(15, 14, 0));
        WriteMoveContestEffect(param0, 5, v2->move);
        WriteSystemFontMovePP(param0, 3, v2->currentPP, v2->maxPP);
    } else {
        u32 v3 = MoveTable_LoadParam(param0->unk_00->unk_24, MOVEATTRIBUTE_PP);

        WriteMoveName(param0, param0->unk_00->unk_24, 1, moveSlotEntryIDs[4], FONT_SYSTEM, 0, TEXT_COLOR(15, 14, 0));
        WriteMoveContestEffect(param0, 5, param0->unk_00->unk_24);
        WriteSystemFontMovePP(param0, 3, v3, v3);
    }

    DrawCancelForgetButton(param0, 6);
}

void ov13_022240E0(UnkStruct_ov13_022213F0 *param0)
{
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_204C[1], 1, 1, 14);
    Window_FillTilemap(&param0->unk_204C[1], 15);
    ov13_02224108(param0);
}

void ov13_02224108(UnkStruct_ov13_022213F0 *param0)
{
    RenderControlFlags_SetCanABSpeedUpPrint(1);
    param0->unk_2077 = Text_AddPrinterWithParams(&param0->unk_204C[1], FONT_MESSAGE, param0->unk_1FAC, 0, 0, BattleSystem_TextSpeed(param0->unk_00->unk_08), NULL);
}

void ov13_02224144(UnkStruct_ov13_022213F0 *param0)
{
    Pokemon *v0;
    UnkStruct_ov13_0221FC20 *v1;
    void *v2;
    Strbuf *v3;
    u16 v4;
    u8 v5;
    u8 v6;

    v1 = param0->unk_00;
    v2 = Item_Load(v1->unk_22, 0, v1->heapID);
    v0 = BattleSystem_PartyPokemon(v1->unk_08, v1->unk_28, v1->unk_2C[v1->selectedPartyIndex]);
    v4 = Pokemon_GetValue(v0, MON_DATA_CURRENT_HP, NULL);
    v5 = 0;

    if (Item_Get(v2, 15) != 0) {
        v5 |= 0x1;
    }

    if (Item_Get(v2, 16) != 0) {
        v5 |= 0x2;
    }

    if (Item_Get(v2, 17) != 0) {
        v5 |= 0x4;
    }

    if (Item_Get(v2, 18) != 0) {
        v5 |= 0x8;
    }

    if (Item_Get(v2, 19) != 0) {
        v5 |= 0x10;
    }

    if (Item_Get(v2, 20) != 0) {
        v5 |= 0x20;
    }

    if (Item_Get(v2, 21) != 0) {
        v5 |= 0x40;
    }

    if ((param0->unk_04[v1->selectedPartyIndex].currentHP == 0) && (v4 != 0)) {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_FAINTED_CURED_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    } else if (param0->unk_04[v1->selectedPartyIndex].currentHP != v4) {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_HP_RESTORED_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_SetNumber(param0->unk_1FA8, 1, v4 - param0->unk_04[v1->selectedPartyIndex].currentHP, 3, 0, 1);
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    } else if ((Item_Get(v2, 36) != 0) || (Item_Get(v2, 37) != 0)) {
        MessageLoader_GetStrbuf(param0->unk_1FA4, 87, param0->unk_1FAC);
    } else if (v5 == 0x1) {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_SLEEP_CURED_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    } else if (v5 == 0x2) {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_POISON_CURED_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    } else if (v5 == 0x4) {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_BURN_CURED_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    } else if (v5 == 0x8) {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_FROZEN_CURED_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    } else if (v5 == 0x10) {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_PARALYSIS_CURED_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    } else if (v5 == 0x20) {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_CONFUSION_CURED_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    } else if (v5 == 0x40) {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_INFATUATION_CURED_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    } else {
        v3 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_MADE_HEALTHY_TEXT);
        StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(v0));
        StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v3);
        Strbuf_Free(v3);
    }

    Heap_FreeToHeap(v2);
}

void ov13_0222449C(UnkStruct_ov13_022213F0 *param0)
{
    Pokemon *pokemonData;
    UnkStruct_ov13_0221FC20 *v1;
    Strbuf *v2;

    v1 = param0->unk_00;
    pokemonData = BattleSystem_PartyPokemon(v1->unk_08, v1->unk_28, v1->unk_2C[v1->selectedPartyIndex]);
    v2 = MessageLoader_GetNewStrbuf(param0->unk_1FA4, IN_BATTLE_TEXT_IDS_ITEM_USE_PREVENTED_TEXT);

    StringTemplate_SetNickname(param0->unk_1FA8, 0, Pokemon_GetBoxPokemon(pokemonData));
    StringTemplate_SetMoveName(param0->unk_1FA8, 1, MOVE_EMBARGO);
    StringTemplate_Format(param0->unk_1FA8, param0->unk_1FAC, v2);
    Strbuf_Free(v2);
}
