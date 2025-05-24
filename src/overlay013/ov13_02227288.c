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

static void DrawBagMenuScreen(BattleBagTask *param0);
static void DrawBagSubMenuScreen(BattleBagTask *param0);
static void DrawUseBagItemScreen(BattleBagTask *param0);

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

void ov13_02227288(BattleBagTask *param0)
{
    Window_AddFromTemplate(param0->background, &param0->messageBoxWindow, &bagScreenMessageBoxWindowTemplate);
    InitializeInBattleBagScreen(param0, param0->currentScreen);
}

void InitializeInBattleBagScreen(BattleBagTask *param0, enum InBattlePartyScreenIndex screenIndex)
{
    const WindowTemplate *windowTemplates;
    u8 i;

    switch (screenIndex) {
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_MENU:
        windowTemplates = bagMenuScreenWindowTemplates;
        param0->numWindows = BAG_MENU_SCREEN_WINDOW_NUM;
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_SUB_MENU:
        windowTemplates = bagSubMenuScreenWindowTemplates;
        param0->numWindows = BAG_SUB_MENU_SCREEN_WINDOW_NUM;
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_USE_BAG_ITEM:
        windowTemplates = useBagItemScreenWindowTemplates;
        param0->numWindows = USE_BAG_ITEM_SCREEN_WINDOW_NUM;
        break;
    }

    param0->windows = Window_New(param0->battleInfo->heapID, param0->numWindows);

    for (i = 0; i < param0->numWindows; i++) {
        Window_AddFromTemplate(param0->background, &param0->windows[i], &windowTemplates[i]);
    }
}

void ClearInBattleBagScreen(BattleBagTask *param0)
{
    Windows_Delete(param0->windows, param0->numWindows);
}

void ClearBattleBagWindows(BattleBagTask *BATTLE_BAG_TASK_STATE_EXIT)
{
    Windows_Delete(BATTLE_BAG_TASK_STATE_EXIT->windows, BATTLE_BAG_TASK_STATE_EXIT->numWindows);
    Window_Remove(&BATTLE_BAG_TASK_STATE_EXIT->messageBoxWindow);
}

void DrawInBattleBagScreen(BattleBagTask *param0, enum InBattlePartyScreenIndex screenIndex)
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

static void WriteTitleText(BattleBagTask *param0, u32 param1, u32 param2, u32 param3, u32 param4, TextColor param5)
{
    Window *v0;
    Strbuf *v1;
    u32 v2;
    u32 v3;

    v0 = &param0->windows[param1];
    v1 = MessageLoader_GetNewStrbuf(param0->messageLoader, param2);
    v2 = Font_CalcStrbufWidth(param3, v1, 0);
    v3 = (Window_GetWidth(v0) * 8 - v2) / 2;

    Text_AddPrinterWithParamsAndColor(v0, param3, v1, v3, param4, TEXT_SPEED_NO_TRANSFER, param5, NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void DrawBagMenuScreen(BattleBagTask *param0)
{
    u32 v0;

    for (v0 = 0; v0 < 5; v0++) {
        Window_FillTilemap(&param0->windows[v0], 0);
    }

    WriteTitleText(param0, 0, IN_BATTLE_BAG_TEXT_ID_HP_PP, FONT_SUBSCREEN, 8, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 0, IN_BATTLE_BAG_TEXT_ID_RESTORE, FONT_SUBSCREEN, 24, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 1, IN_BATTLE_BAG_TEXT_ID_STATUS, FONT_SUBSCREEN, 8, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 1, IN_BATTLE_BAG_TEXT_ID_HEALERS, FONT_SUBSCREEN, 24, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 2, IN_BATTLE_BAG_TEXT_ID_POKE_BALLS, FONT_SUBSCREEN, 8, TEXT_COLOR(3, 2, 1));
    WriteTitleText(param0, 3, IN_BATTLE_BAG_TEXT_ID_BATTLE_ITEMS, FONT_SUBSCREEN, 8, TEXT_COLOR(3, 2, 1));

    if (param0->battleInfo->lastUsedItem != ITEM_NONE) {
        Strbuf *v1 = MessageLoader_GetNewStrbuf(param0->messageLoader, IN_BATTLE_BAG_TEXT_ID_LAST_USED_ITEM);

        Text_AddPrinterWithParamsAndColor(&param0->windows[4], FONT_SUBSCREEN, v1, 0, 6, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 2, 1), NULL);
        Strbuf_Free(v1);
        Window_ScheduleCopyToVRAM(&param0->windows[4]);
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

static void WriteBagItemName(BattleBagTask *param0, u32 param1, u32 param2, u32 param3, u32 param4, TextColor param5)
{
    Window *v0;
    Strbuf *v1;
    u32 v2;
    u32 v3;

    v0 = &param0->windows[param3];

    Window_FillTilemap(v0, 0);

    if (param0->battleBagItems[param0->currentBattleBagPocket][param1].item != ITEM_NONE) {
        v1 = MessageLoader_GetNewStrbuf(param0->messageLoader, Unk_ov13_02229AB0[param2][0]);

        StringTemplate_SetItemName(param0->stringTemplate, 0, param0->battleBagItems[param0->currentBattleBagPocket][param1].item);
        StringTemplate_Format(param0->stringTemplate, param0->strbuf, v1);

        v2 = Font_CalcStrbufWidth(param4, param0->strbuf, 0);
        v3 = (Window_GetWidth(v0) * 8 - v2) / 2;

        Text_AddPrinterWithParamsAndColor(v0, param4, param0->strbuf, v3, 8, TEXT_SPEED_NO_TRANSFER, param5, NULL);
        Strbuf_Free(v1);
    }

    Window_ScheduleCopyToVRAM(v0);
}

static void WriteBagItemQuantity(BattleBagTask *param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, TextColor param6)
{
    Strbuf *v0;
    Window *v1 = &param0->windows[param3];

    Window_FillTilemap(v1, 0);

    if (param0->battleBagItems[param0->currentBattleBagPocket][param1].quantity != 0) {
        v0 = MessageLoader_GetNewStrbuf(param0->messageLoader, Unk_ov13_02229AB0[param2][1]);

        StringTemplate_SetNumber(param0->stringTemplate, 0, param0->battleBagItems[param0->currentBattleBagPocket][param1].quantity, 3, 0, 1);
        StringTemplate_Format(param0->stringTemplate, param0->strbuf, v0);
        Text_AddPrinterWithParamsAndColor(v1, param4, param0->strbuf, 0, param5, TEXT_SPEED_NO_TRANSFER, param6, NULL);
        Strbuf_Free(v0);
    }

    Window_ScheduleCopyToVRAM(v1);
}

static void DrawBagSubMenuItem(BattleBagTask *param0, u32 param1)
{
    u32 v0;
    u32 v1 = param0->battleInfo->pocketCurrentPages[param0->currentBattleBagPocket] * 6 + param1;

    if (param0->unk_31 == 0) {
        v0 = 0;
    } else {
        v0 = 12;
    }

    WriteBagItemName(param0, v1, param1, v0 + param1 * 2, FONT_SUBSCREEN, TEXT_COLOR(3, 2, 1));
    WriteBagItemQuantity(param0, v1, param1, v0 + 1 + param1 * 2, FONT_SYSTEM, 4, TEXT_COLOR(1, 2, 0));
}

void DrawBagSubMenuPage(BattleBagTask *param0)
{
    u16 v0;

    Bg_FillTilemapRect(param0->background, 5, 0, 0, 0, 32, 19, 17);

    for (v0 = 0; v0 < 6; v0++) {
        DrawBagSubMenuItem(param0, v0);
    }

    param0->unk_31 ^= 1;
}

void DrawBagSubMenuPageInfo(BattleBagTask *param0)
{
    Window *v0;
    Strbuf *v1;
    u32 v2;
    u32 v3;

    Window_FillTilemap(&param0->windows[25], 0);

    v0 = &param0->windows[25];
    v1 = MessageLoader_GetNewStrbuf(param0->messageLoader, IN_BATTLE_BAG_TEXT_ID_PAGE_DIVIDER);
    v2 = Font_CalcStrbufWidth(FONT_SYSTEM, v1, 0);
    v3 = (Window_GetWidth(v0) * 8 - v2) / 2;

    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, v3, 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->messageLoader, IN_BATTLE_BAG_TEXT_ID_CURRENT_PAGE_TEXT);
    StringTemplate_SetNumber(param0->stringTemplate, 0, param0->numBattleBagPocketPages[param0->currentBattleBagPocket] + 1, 2, 0, 1);
    StringTemplate_Format(param0->stringTemplate, param0->strbuf, v1);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, param0->strbuf, v3 + v2, 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);

    v1 = MessageLoader_GetNewStrbuf(param0->messageLoader, IN_BATTLE_BAG_TEXT_ID_MAX_PAGE_TEXT);
    StringTemplate_SetNumber(param0->stringTemplate, 0, param0->battleInfo->pocketCurrentPages[param0->currentBattleBagPocket] + 1, 2, 0, 1);
    StringTemplate_Format(param0->stringTemplate, param0->strbuf, v1);

    v2 = Font_CalcStrbufWidth(FONT_SYSTEM, param0->strbuf, 0);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, param0->strbuf, v3 - v2, 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void DrawBagSubMenuTitle(BattleBagTask *param0)
{
    Window_FillTilemap(&param0->windows[24], 0);

    switch (param0->currentBattleBagPocket) {
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

static void DrawBagSubMenuScreen(BattleBagTask *param0)
{
    DrawBagSubMenuPage(param0);
    DrawBagSubMenuTitle(param0);
    DrawBagSubMenuPageInfo(param0);
}

static void WriteUseBagItemName(BattleBagTask *param0, u32 param1)
{
    Window *v0;
    Strbuf *v1;

    v0 = &param0->windows[0];
    v1 = MessageLoader_GetNewStrbuf(param0->messageLoader, Unk_ov13_02229AB0[0][0]);

    StringTemplate_SetItemName(param0->stringTemplate, 0, param0->battleBagItems[param0->currentBattleBagPocket][param1].item);
    StringTemplate_Format(param0->stringTemplate, param0->strbuf, v1);
    Window_FillTilemap(v0, 0);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, param0->strbuf, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void WriteBagItemDescription(BattleBagTask *param0, u32 param1)
{
    Window *v0;
    Strbuf *v1;

    v0 = &param0->windows[2];
    v1 = Strbuf_Init(130, param0->battleInfo->heapID);

    Item_LoadDescription(v1, param0->battleBagItems[param0->currentBattleBagPocket][param1].item, param0->battleInfo->heapID);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, 4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Strbuf_Free(v1);
    Window_ScheduleCopyToVRAM(v0);
}

static void DrawUseBagItemScreen(BattleBagTask *param0)
{
    u32 v0;
    u32 v1;

    for (v0 = 0; v0 < 4; v0++) {
        Window_FillTilemap(&param0->windows[v0], 0);
    }

    v1 = param0->battleInfo->pocketCurrentPages[param0->currentBattleBagPocket] * 6 + param0->battleInfo->pocketCurrentPagePositions[param0->currentBattleBagPocket];

    WriteUseBagItemName(param0, v1);
    WriteBagItemQuantity(param0, v1, 0, 1, FONT_SYSTEM, 0, TEXT_COLOR(1, 2, 0));
    WriteBagItemDescription(param0, v1);
    WriteTitleText(param0, 3, IN_BATTLE_BAG_TEXT_ID_USE, FONT_SUBSCREEN, 6, TEXT_COLOR(3, 2, 1));
}

void DisplayMessageBox(BattleBagTask *battleBagTask)
{
    Window_DrawMessageBoxWithScrollCursor(&battleBagTask->messageBoxWindow, TRUE, 1024 - (18 + 12), 14);
    Window_FillTilemap(&battleBagTask->messageBoxWindow, 15);
    PrintTextToMessageBox(battleBagTask);
}

void PrintTextToMessageBox(BattleBagTask *battleBagTask)
{
    RenderControlFlags_SetCanABSpeedUpPrint(TRUE);
    battleBagTask->textPrinter = Text_AddPrinterWithParams(&battleBagTask->messageBoxWindow, FONT_MESSAGE, battleBagTask->strbuf, 0, 0, BattleSystem_TextSpeed(battleBagTask->battleInfo->battleSystem), NULL);
}
