#include "overlay013/ov13_02227288.h"

#include <nitro.h>
#include <string.h>

#include "battle/ov16_0223DF00.h"
#include "overlay013/struct_ov13_02227244.h"

#include "bg_window.h"
#include "font.h"
#include "item.h"
#include "message.h"
#include "render_text.h"
#include "render_window.h"
#include "strbuf.h"
#include "string_template.h"
#include "text.h"

enum InBattleBagTextID {
    IN_BATTLE_BAG_TEXT_ID_HP_PP = 0,
    IN_BATTLE_BAG_TEXT_ID_RESTORE,
    IN_BATTLE_BAG_TEXT_ID_STATUS,
    IN_BATTLE_BAG_TEXT_ID_HEALERS,
    IN_BATTLE_BAG_TEXT_ID_BATTLE_ITEMS = 6,
    IN_BATTLE_BAG_TEXT_ID_POKE_BALLS,
    IN_BATTLE_BAG_TEXT_ID_LAST_USED_ITEM,
    IN_BATTLE_BAG_TEXT_ID_SUB_MENU_HP_PP = 22,
    IN_BATTLE_BAG_TEXT_ID_SUB_MENU_RESTORE,
    IN_BATTLE_BAG_TEXT_ID_SUB_MENU_STATUS,
    IN_BATTLE_BAG_TEXT_ID_SUB_MENU_HEALERS,
    IN_BATTLE_BAG_TEXT_ID_SUB_MENU_POKE_BALLS,
    IN_BATTLE_BAG_TEXT_ID_SUB_MENU_BATTLE_ITEMS,
    IN_BATTLE_BAG_TEXT_ID_PAGE_DIVIDER,
    IN_BATTLE_BAG_TEXT_ID_CURRENT_PAGE_TEXT,
    IN_BATTLE_BAG_TEXT_ID_MAX_PAGE_TEXT,
    IN_BATTLE_BAG_TEXT_ID_USE,
};

#define BAG_MENU_SCREEN_WINDOW_NUM     5
#define BAG_SUB_MENU_SCREEN_WINDOW_NUM 26
#define USE_BAG_ITEM_SCREEN_WINDOW_NUM 4

static void DrawBagMenuScreen(UnkStruct_ov13_02227244 *param0);
static void DrawBagSubMenuScreen(UnkStruct_ov13_02227244 *param0);
static void DrawUseBagItemScreen(UnkStruct_ov13_02227244 *param0);

static const WindowTemplate bagScreenMessageBoxWindowTemplate = {
    0x4,
    0x2,
    0x13,
    0x1B,
    0x4,
    0xF,
    0x376
};

static const WindowTemplate bagMenuScreenWindowTemplates[] = {
    { 0x4, 0x2, 0x4, 0xC, 0x5, 0x0, 0x2CE },
    { 0x4, 0x2, 0xD, 0xC, 0x5, 0x0, 0x30A },
    { 0x4, 0x12, 0x5, 0xC, 0x3, 0x0, 0x286 },
    { 0x4, 0x12, 0xE, 0xC, 0x3, 0x0, 0x2AA },
    { 0x4, 0x5, 0x14, 0x14, 0x3, 0x0, 0x24A }
};

static const WindowTemplate bagSubMenuScreenWindowTemplates[] = {
    { 0x5, 0x1, 0x1, 0xE, 0x3, 0x0, 0x1 },
    { 0x5, 0x8, 0x4, 0x4, 0x3, 0x4, 0x2B },
    { 0x5, 0x11, 0x1, 0xE, 0x3, 0x0, 0x37 },
    { 0x5, 0x18, 0x4, 0x4, 0x3, 0x4, 0x61 },
    { 0x5, 0x1, 0x7, 0xE, 0x3, 0x0, 0x6D },
    { 0x5, 0x8, 0xA, 0x4, 0x3, 0x4, 0x97 },
    { 0x5, 0x11, 0x7, 0xE, 0x3, 0x0, 0xA3 },
    { 0x5, 0x18, 0xA, 0x4, 0x3, 0x4, 0xCD },
    { 0x5, 0x1, 0xD, 0xE, 0x3, 0x0, 0xD9 },
    { 0x5, 0x8, 0x10, 0x4, 0x3, 0x4, 0x103 },
    { 0x5, 0x11, 0xD, 0xE, 0x3, 0x0, 0x10F },
    { 0x5, 0x18, 0x10, 0x4, 0x3, 0x4, 0x139 },
    { 0x5, 0x1, 0x1, 0xE, 0x3, 0x0, 0x145 },
    { 0x5, 0x8, 0x4, 0x4, 0x3, 0x4, 0x16F },
    { 0x5, 0x11, 0x1, 0xE, 0x3, 0x0, 0x17B },
    { 0x5, 0x18, 0x4, 0x4, 0x3, 0x4, 0x1A5 },
    { 0x5, 0x1, 0x7, 0xE, 0x3, 0x0, 0x1B1 },
    { 0x5, 0x8, 0xA, 0x4, 0x3, 0x4, 0x1DB },
    { 0x5, 0x11, 0x7, 0xE, 0x3, 0x0, 0x1E7 },
    { 0x5, 0x18, 0xA, 0x4, 0x3, 0x4, 0x211 },
    { 0x5, 0x1, 0xD, 0xE, 0x3, 0x0, 0x21D },
    { 0x5, 0x8, 0x10, 0x4, 0x3, 0x4, 0x247 },
    { 0x5, 0x11, 0xD, 0xE, 0x3, 0x0, 0x253 },
    { 0x5, 0x18, 0x10, 0x4, 0x3, 0x4, 0x27D },
    { 0x5, 0xB, 0x13, 0xA, 0x5, 0x4, 0x289 },
    { 0x5, 0x16, 0x14, 0x4, 0x3, 0x4, 0x2BB }
};

static const WindowTemplate useBagItemScreenWindowTemplates[] = {
    { 0x5, 0x7, 0x4, 0xC, 0x2, 0x4, 0x2C7 },
    { 0x5, 0x14, 0x4, 0x4, 0x2, 0x4, 0x2DF },
    { 0x5, 0x2, 0x9, 0x1C, 0x6, 0x4, 0x2E7 },
    { 0x5, 0xA, 0x14, 0x6, 0x3, 0x0, 0x38F }
};

void ov13_02227288(UnkStruct_ov13_02227244 *param0)
{
    Window_AddFromTemplate(param0->unk_04, &param0->unk_1C, &bagScreenMessageBoxWindowTemplate);
    InitializeInBattleBagScreen(param0, param0->unk_114C);
}

void InitializeInBattleBagScreen(UnkStruct_ov13_02227244 *param0, enum InBattlePartyScreenIndex screenIndex)
{
    const WindowTemplate *windowTemplates;
    u8 i;

    switch (screenIndex) {
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_MENU:
        windowTemplates = bagMenuScreenWindowTemplates;
        param0->unk_30 = BAG_MENU_SCREEN_WINDOW_NUM;
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_SUB_MENU:
        windowTemplates = bagSubMenuScreenWindowTemplates;
        param0->unk_30 = BAG_SUB_MENU_SCREEN_WINDOW_NUM;
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_USE_BAG_ITEM:
        windowTemplates = useBagItemScreenWindowTemplates;
        param0->unk_30 = USE_BAG_ITEM_SCREEN_WINDOW_NUM;
        break;
    }

    param0->unk_2C = Window_New(param0->unk_00->heapID, param0->unk_30);

    for (i = 0; i < param0->unk_30; i++) {
        Window_AddFromTemplate(param0->unk_04, &param0->unk_2C[i], &windowTemplates[i]);
    }
}

void ClearInBattleBagScreen(UnkStruct_ov13_02227244 *param0)
{
    Windows_Delete(param0->unk_2C, param0->unk_30);
}

void ov13_02227334(UnkStruct_ov13_02227244 *param0)
{
    u32 v0;

    Windows_Delete(param0->unk_2C, param0->unk_30);
    Window_Remove(&param0->unk_1C);
}

void DrawInBattleBagScreen(UnkStruct_ov13_02227244 *param0, enum InBattlePartyScreenIndex screenIndex)
{
    switch (screenIndex) {
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_MENU:
        DrawBagMenuScreen(param0);
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_SUB_MENU:
        DrawBagSubMenuScreen(param0);
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_USE_BAG_ITEM:
        DrawUseBagItemScreen(param0);
        break;
    }
}

static void WriteTitleText(UnkStruct_ov13_02227244 *param0, u32 param1, u32 param2, u32 param3, u32 param4, TextColor param5)
{
    Window *v0;
    Strbuf *v1;
    u32 v2;
    u32 v3;

    v0 = &param0->unk_2C[param1];
    v1 = MessageLoader_GetNewStrbuf(param0->unk_10, param2);
    v2 = Font_CalcStrbufWidth(param3, v1, 0);
    v3 = (Window_GetWidth(v0) * 8 - v2) / 2;

    Text_AddPrinterWithParamsAndColor(v0, param3, v1, v3, param4, TEXT_SPEED_NO_TRANSFER, param5, NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void DrawBagMenuScreen(UnkStruct_ov13_02227244 *param0)
{
    u32 v0;

    for (v0 = 0; v0 < 5; v0++) {
        Window_FillTilemap(&param0->unk_2C[v0], 0);
    }

    WriteTitleText(param0, 0, IN_BATTLE_BAG_TEXT_ID_HP_PP, FONT_SUBSCREEN, 8, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 0, IN_BATTLE_BAG_TEXT_ID_RESTORE, FONT_SUBSCREEN, 24, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 1, IN_BATTLE_BAG_TEXT_ID_STATUS, FONT_SUBSCREEN, 8, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 1, IN_BATTLE_BAG_TEXT_ID_HEALERS, FONT_SUBSCREEN, 24, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 2, IN_BATTLE_BAG_TEXT_ID_POKE_BALLS, FONT_SUBSCREEN, 8, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 3, IN_BATTLE_BAG_TEXT_ID_BATTLE_ITEMS, FONT_SUBSCREEN, 8, TEXT_COLOR(3, 2, 1));

    if (param0->unk_00->lastUsedItem != ITEM_NONE) {
        Strbuf *v1 = MessageLoader_GetNewStrbuf(param0->unk_10, IN_BATTLE_BAG_TEXT_ID_LAST_USED_ITEM);

        Text_AddPrinterWithParamsAndColor(&param0->unk_2C[4], FONT_SUBSCREEN, v1, 0, 6, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 2, 1), NULL);
        Strbuf_Free(v1);
        Window_ScheduleCopyToVRAM(&param0->unk_2C[4]);
    }
}

static const u32 Unk_ov13_02229AB0[][2] = {
    { 0x9, 0xA },
    { 0xB, 0xC },
    { 0xD, 0xE },
    { 0xF, 0x10 },
    { 0x11, 0x12 },
    { 0x13, 0x14 }
};

static void WriteBagItemName(UnkStruct_ov13_02227244 *param0, u32 param1, u32 param2, u32 param3, u32 param4, TextColor param5)
{
    Window *v0;
    Strbuf *v1;
    u32 v2;
    u32 v3;

    v0 = &param0->unk_2C[param3];

    Window_FillTilemap(v0, 0);

    if (param0->unk_3C[param0->unk_114D][param1].item != ITEM_NONE) {
        v1 = MessageLoader_GetNewStrbuf(param0->unk_10, Unk_ov13_02229AB0[param2][0]);

        StringTemplate_SetItemName(param0->unk_14, 0, param0->unk_3C[param0->unk_114D][param1].item);
        StringTemplate_Format(param0->unk_14, param0->unk_18, v1);

        v2 = Font_CalcStrbufWidth(param4, param0->unk_18, 0);
        v3 = (Window_GetWidth(v0) * 8 - v2) / 2;

        Text_AddPrinterWithParamsAndColor(v0, param4, param0->unk_18, v3, 8, TEXT_SPEED_NO_TRANSFER, param5, NULL);
        Strbuf_Free(v1);
    }

    Window_ScheduleCopyToVRAM(v0);
}

static void WriteBagItemQuantity(UnkStruct_ov13_02227244 *param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, TextColor param6)
{
    Strbuf *v0;
    Window *v1 = &param0->unk_2C[param3];

    Window_FillTilemap(v1, 0);

    if (param0->unk_3C[param0->unk_114D][param1].quantity != 0) {
        v0 = MessageLoader_GetNewStrbuf(param0->unk_10, Unk_ov13_02229AB0[param2][1]);

        StringTemplate_SetNumber(param0->unk_14, 0, param0->unk_3C[param0->unk_114D][param1].quantity, 3, 0, 1);
        StringTemplate_Format(param0->unk_14, param0->unk_18, v0);
        Text_AddPrinterWithParamsAndColor(v1, param4, param0->unk_18, 0, param5, TEXT_SPEED_NO_TRANSFER, param6, NULL);
        Strbuf_Free(v0);
    }

    Window_ScheduleCopyToVRAM(v1);
}

static void DrawBagSubMenuItem(UnkStruct_ov13_02227244 *param0, u32 param1)
{
    u32 v0;
    u32 v1 = param0->unk_00->unk_2C[param0->unk_114D] * 6 + param1;

    if (param0->unk_31 == 0) {
        v0 = 0;
    } else {
        v0 = 12;
    }

    WriteBagItemName(param0, v1, param1, v0 + param1 * 2, FONT_SUBSCREEN, TEXT_COLOR(3, 2, 1));
    WriteBagItemQuantity(param0, v1, param1, v0 + 1 + param1 * 2, FONT_SYSTEM, 4, TEXT_COLOR(1, 2, 0));
}

void DrawBagSubMenuPage(UnkStruct_ov13_02227244 *param0)
{
    u16 v0;

    Bg_FillTilemapRect(param0->unk_04, 5, 0, 0, 0, 32, 19, 17);

    for (v0 = 0; v0 < 6; v0++) {
        DrawBagSubMenuItem(param0, v0);
    }

    param0->unk_31 ^= 1;
}

void DrawBagSubMenuPageInfo(UnkStruct_ov13_02227244 *param0)
{
    Window *v0;
    Strbuf *v1;
    u32 v2;
    u32 v3;

    Window_FillTilemap(&param0->unk_2C[25], 0);

    v0 = &param0->unk_2C[25];
    v1 = MessageLoader_GetNewStrbuf(param0->unk_10, IN_BATTLE_BAG_TEXT_ID_PAGE_DIVIDER);
    v2 = Font_CalcStrbufWidth(FONT_SYSTEM, v1, 0);
    v3 = (Window_GetWidth(v0) * 8 - v2) / 2;

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, v3, 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_10, IN_BATTLE_BAG_TEXT_ID_CURRENT_PAGE_TEXT);
    StringTemplate_SetNumber(param0->unk_14, 0, param0->unk_1154[param0->unk_114D] + 1, 2, 0, 1);
    StringTemplate_Format(param0->unk_14, param0->unk_18, v1);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, param0->unk_18, v3 + v2, 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->unk_10, IN_BATTLE_BAG_TEXT_ID_MAX_PAGE_TEXT);
    StringTemplate_SetNumber(param0->unk_14, 0, param0->unk_00->unk_2C[param0->unk_114D] + 1, 2, 0, 1);
    StringTemplate_Format(param0->unk_14, param0->unk_18, v1);

    v2 = Font_CalcStrbufWidth(FONT_SYSTEM, param0->unk_18, 0);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, param0->unk_18, v3 - v2, 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void DrawBagSubMenuTitle(UnkStruct_ov13_02227244 *param0)
{
    Window_FillTilemap(&param0->unk_2C[24], 0);

    switch (param0->unk_114D) {
    case IN_BATTLE_BAG_SUB_MENU_INDEX_HP_PP_RESTORE:
        WriteTitleText(param0, 24, IN_BATTLE_BAG_TEXT_ID_SUB_MENU_HP_PP, FONT_SYSTEM, 4, TEXT_COLOR(1, 2, 0));
        WriteTitleText(param0, 24, IN_BATTLE_BAG_TEXT_ID_SUB_MENU_RESTORE, FONT_SYSTEM, (4 + 16), TEXT_COLOR(1, 2, 0));
        break;
    case IN_BATTLE_BAG_SUB_MENU_INDEX_STATUS_HEALERS:
        WriteTitleText(param0, 24, IN_BATTLE_BAG_TEXT_ID_SUB_MENU_STATUS, FONT_SYSTEM, 4, TEXT_COLOR(1, 2, 0));
        WriteTitleText(param0, 24, IN_BATTLE_BAG_TEXT_ID_SUB_MENU_HEALERS, FONT_SYSTEM, (4 + 16), TEXT_COLOR(1, 2, 0));
        break;
    case IN_BATTLE_BAG_SUB_MENU_INDEX_POKE_BALLS:
        WriteTitleText(param0, 24, IN_BATTLE_BAG_TEXT_ID_SUB_MENU_POKE_BALLS, FONT_SYSTEM, 12, TEXT_COLOR(1, 2, 0));
        break;
    case IN_BATTLE_BAG_SUB_MENU_INDEX_BATTLE_ITEMS:
        WriteTitleText(param0, 24, IN_BATTLE_BAG_TEXT_ID_SUB_MENU_BATTLE_ITEMS, FONT_SYSTEM, 12, TEXT_COLOR(1, 2, 0));
        break;
    }
}

static void DrawBagSubMenuScreen(UnkStruct_ov13_02227244 *param0)
{
    DrawBagSubMenuPage(param0);
    DrawBagSubMenuTitle(param0);
    DrawBagSubMenuPageInfo(param0);
}

static void WriteUseBagItemName(UnkStruct_ov13_02227244 *param0, u32 param1)
{
    Window *v0;
    Strbuf *v1;

    v0 = &param0->unk_2C[0];
    v1 = MessageLoader_GetNewStrbuf(param0->unk_10, Unk_ov13_02229AB0[0][0]);

    StringTemplate_SetItemName(param0->unk_14, 0, param0->unk_3C[param0->unk_114D][param1].item);
    StringTemplate_Format(param0->unk_14, param0->unk_18, v1);
    Window_FillTilemap(v0, 0);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, param0->unk_18, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteBagItemDescription(UnkStruct_ov13_02227244 *param0, u32 param1)
{
    Window *v0;
    Strbuf *v1;

    v0 = &param0->unk_2C[2];
    v1 = Strbuf_Init(130, param0->unk_00->heapID);

    Item_LoadDescription(v1, param0->unk_3C[param0->unk_114D][param1].item, param0->unk_00->heapID);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, 4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void DrawUseBagItemScreen(UnkStruct_ov13_02227244 *param0)
{
    u32 v0;
    u32 v1;

    for (v0 = 0; v0 < 4; v0++) {
        Window_FillTilemap(&param0->unk_2C[v0], 0);
    }

    v1 = param0->unk_00->unk_2C[param0->unk_114D] * 6 + param0->unk_00->unk_27[param0->unk_114D];

    WriteUseBagItemName(param0, v1);
    WriteBagItemQuantity(param0, v1, 0, 1, FONT_SYSTEM, 0, TEXT_COLOR(1, 2, 0));
    WriteBagItemDescription(param0, v1);
    WriteTitleText(param0, 3, IN_BATTLE_BAG_TEXT_ID_USE, FONT_SUBSCREEN, 6, TEXT_COLOR(3, 2, 1));
}

void ov13_022279F4(UnkStruct_ov13_02227244 *param0)
{
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_1C, 1, 1024 - (18 + 12), 14);
    Window_FillTilemap(&param0->unk_1C, 15);
    ov13_02227A1C(param0);
}

void ov13_02227A1C(UnkStruct_ov13_02227244 *param0)
{
    RenderControlFlags_SetCanABSpeedUpPrint(1);
    param0->unk_32 = Text_AddPrinterWithParams(&param0->unk_1C, FONT_MESSAGE, param0->unk_18, 0, 0, BattleSystem_TextSpeed(param0->unk_00->unk_00), NULL);
}
