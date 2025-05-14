#include "overlay013/ov13_02227BDC.h"

#include <nitro.h>
#include <string.h>

#include "battle/ov16_0223DF00.h"
#include "battle/ov16_0226DB7C.h"
#include "battle/ov16_0226DE44.h"
#include "battle/struct_ov16_0226DC24_decl.h"
#include "battle/struct_ov16_0226DEEC_decl.h"
#include "overlay013/ov13_02227A4C.h"
#include "overlay013/ov13_02228A38.h"
#include "overlay013/struct_ov13_02227244.h"

#include "byte_flag_set.h"
#include "gx_layers.h"
#include "item.h"
#include "narc.h"
#include "palette.h"
#include "sprite_system.h"

static void ov13_02227C08(UnkStruct_ov13_02227244 *param0);
static void ov13_02227C54(UnkStruct_ov13_02227244 *param0);
static void ov13_02227D10(UnkStruct_ov13_02227244 *param0, u16 item, u32 param2);
static void ov13_02227D48(UnkStruct_ov13_02227244 *param0, u16 item, u16 param2, u32 param3);
static void ov13_02227DE8(UnkStruct_ov13_02227244 *param0);
static void RenderLastUsedItemSprite(UnkStruct_ov13_02227244 *param0);
static void RenderSubMenuItemSprites(UnkStruct_ov13_02227244 *param0);
static void RenderSelectedItemSprite(UnkStruct_ov13_02227244 *param0);
static void ov13_02227F7C(UnkStruct_ov13_02227244 *param0);
static void ov13_02227FDC(UnkStruct_ov13_02227244 *param0);
static void ov13_02228070(UnkStruct_ov13_02227244 *param0);
static void ov13_022280C8(UnkStruct_ov13_02227244 *param0);

static const int Unk_ov13_02229BC0[2] = {
    0x18,
    0xB2
};

static const int Unk_ov13_02229C44[][2] = {
    { 0x2C, 0x2D },
    { 0xAC, 0x2D },
    { 0x2C, 0x5D },
    { 0xAC, 0x5D },
    { 0x2C, 0x8D },
    { 0xAC, 0x8D }
};

static const int Unk_ov13_02229BB8[2] = {
    0x28,
    0x2C
};

static const int Unk_ov13_02229CBC[][5] = {
    { 0xB4B7, 0xB4B7, 0xB4B7, 0xB4B7, 0x1 },
    { 0xB4B8, 0xB4B8, 0xB4B7, 0xB4B7, 0x1 },
    { 0xB4B9, 0xB4B9, 0xB4B7, 0xB4B7, 0x1 },
    { 0xB4BA, 0xB4BA, 0xB4B7, 0xB4B7, 0x1 },
    { 0xB4BB, 0xB4BB, 0xB4B7, 0xB4B7, 0x1 },
    { 0xB4BC, 0xB4BC, 0xB4B7, 0xB4B7, 0x1 }
};

void ov13_02227BDC(UnkStruct_ov13_02227244 *param0)
{
    ov13_02227C08(param0);
    ov13_02227C54(param0);
    ov13_02227DE8(param0);
    ov13_02227F7C(param0);
    ov13_02228070(param0);

    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void ov13_02227C08(UnkStruct_ov13_02227244 *param0)
{
    SpriteResourceCapacities v0 = { 8, 8, 3, 3, 0, 0 };
    SpriteSystem *v1 = ov16_0223E010(param0->unk_00->unk_00);

    param0->unk_30C = SpriteManager_New(v1);

    SpriteSystem_InitSprites(v1, param0->unk_30C, 6 + 5 + 1);
    SpriteSystem_InitManagerWithCapacities(v1, param0->unk_30C, &v0);
}

static void ov13_02227C54(UnkStruct_ov13_02227244 *param0)
{
    SpriteSystem *v0;
    u32 v1;
    NARC *v2 = NARC_ctor(NARC_INDEX_ITEMTOOL__ITEMDATA__ITEM_ICON, param0->unk_00->heapID);
    v0 = ov16_0223E010(param0->unk_00->unk_00);

    for (v1 = 0; v1 < NUM_BAG_ITEMS_PER_PAGE; v1++) {
        SpriteSystem_LoadCharResObjFromOpenNarc(v0, param0->unk_30C, v2, Item_FileID(1, 1), FALSE, NNS_G2D_VRAM_TYPE_2DSUB, 46263 + v1);
        SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->unk_08, PLTTBUF_SUB_OBJ, v0, param0->unk_30C, v2, Item_FileID(1, 2), FALSE, 1, NNS_G2D_VRAM_TYPE_2DSUB, 46263 + v1);
    }

    SpriteSystem_LoadCellResObjFromOpenNarc(v0, param0->unk_30C, v2, Item_IconNCERFile(), FALSE, 46263);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v0, param0->unk_30C, v2, Item_IconNANRFile(), FALSE, 46263);
    NARC_dtor(v2);
}

static void ov13_02227D10(UnkStruct_ov13_02227244 *param0, u16 item, u32 param2)
{
    SpriteSystem *v0 = ov16_0223E010(param0->unk_00->unk_00);
    SpriteSystem_ReplaceCharResObj(v0, param0->unk_30C, NARC_INDEX_ITEMTOOL__ITEMDATA__ITEM_ICON, Item_FileID(item, ITEM_FILE_TYPE_ICON), FALSE, param2);
}

static void ov13_02227D48(UnkStruct_ov13_02227244 *param0, u16 item, u16 param2, u32 param3)
{
    PaletteData_LoadBufferFromFileStart(param0->unk_08, NARC_INDEX_ITEMTOOL__ITEMDATA__ITEM_ICON, Item_FileID(item, ITEM_FILE_TYPE_PALETTE), param0->unk_00->heapID, PLTTBUF_SUB_OBJ, 0x20, param2 * 16);
}

static ManagedSprite *ov13_02227D78(UnkStruct_ov13_02227244 *param0, u32 param1)
{
    SpriteTemplate template;
    SpriteSystem *spriteSystem = ov16_0223E010(param0->unk_00->unk_00);

    template.x = 0;
    template.y = 0;
    template.z = 0;
    template.animIdx = 0;
    template.priority = Unk_ov13_02229CBC[param1][4];
    template.plttIdx = 0;
    template.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    template.resources[0] = Unk_ov13_02229CBC[param1][0];
    template.resources[1] = Unk_ov13_02229CBC[param1][1];
    template.resources[2] = Unk_ov13_02229CBC[param1][2];
    template.resources[3] = Unk_ov13_02229CBC[param1][3];
    template.bgPriority = 1;
    template.vramTransfer = FALSE;

    return SpriteSystem_NewSprite(spriteSystem, param0->unk_30C, &template);
}

static void ov13_02227DE8(UnkStruct_ov13_02227244 *param0)
{
    u32 v0;

    for (v0 = 0; v0 < NUM_BAG_ITEMS_PER_PAGE; v0++) {
        param0->unk_310[v0] = ov13_02227D78(param0, v0);
    }
}

void ov13_02227E08(UnkStruct_ov13_02227244 *param0)
{
    SpriteSystem *v0;
    u32 v1;

    v0 = ov16_0223E010(param0->unk_00->unk_00);

    for (v1 = 0; v1 < NUM_BAG_ITEMS_PER_PAGE; v1++) {
        Sprite_DeleteAndFreeResources(param0->unk_310[v1]);
    }

    ov13_02227FDC(param0);
    ov13_022280C8(param0);
    SpriteSystem_FreeResourcesAndManager(v0, param0->unk_30C);
}

static void DrawManagedSprite(ManagedSprite *sprite, const int x, const int y)
{
    ManagedSprite_SetDrawFlag(sprite, TRUE);
    ManagedSprite_SetPositionXY(sprite, x, y);
}

void ov13_02227E68(UnkStruct_ov13_02227244 *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < NUM_BAG_ITEMS_PER_PAGE; v0++) {
        ManagedSprite_SetDrawFlag(param0->unk_310[v0], FALSE);
    }

    switch (param1) {
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_MENU:
        RenderLastUsedItemSprite(param0);
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_SUB_MENU:
        RenderSubMenuItemSprites(param0);
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_USE_BAG_ITEM:
        RenderSelectedItemSprite(param0);
        break;
    }
}

static void RenderLastUsedItemSprite(UnkStruct_ov13_02227244 *param0)
{
    u16 v0;

    if (param0->unk_00->unk_20 != ITEM_NONE) {
        ov13_02227D10(param0, param0->unk_00->unk_20, 46263);
        ov13_02227D48(param0, param0->unk_00->unk_20, 0, 46263);
        DrawManagedSprite(param0->unk_310[0], Unk_ov13_02229BC0[0], Unk_ov13_02229BC0[1]);
    }
}

static void RenderSubMenuItemSprites(UnkStruct_ov13_02227244 *param0)
{
    u32 v0;
    u16 item;

    for (v0 = 0; v0 < NUM_BAG_ITEMS_PER_PAGE; v0++) {
        item = GetBagItemOnPage(param0, v0);

        if (item == ITEM_NONE) {
            continue;
        }

        ov13_02227D10(param0, item, 46263 + v0);
        ov13_02227D48(param0, item, (u16)v0, 46263 + v0);
        DrawManagedSprite(param0->unk_310[v0], Unk_ov13_02229C44[v0][0], Unk_ov13_02229C44[v0][1]);
    }
}

static void RenderSelectedItemSprite(UnkStruct_ov13_02227244 *param0)
{
    u16 item = GetBagItemOnPage(param0, param0->unk_00->unk_27[param0->unk_114D]);

    ov13_02227D10(param0, item, 46263);
    ov13_02227D48(param0, item, 0, 46263);
    DrawManagedSprite(param0->unk_310[0], Unk_ov13_02229BB8[0], Unk_ov13_02229BB8[1]);
}

static void ov13_02227F7C(UnkStruct_ov13_02227244 *param0)
{
    SpriteSystem *v0;
    UnkStruct_ov16_0226DC24 *v1;

    v0 = ov16_0223E010(param0->unk_00->unk_00);
    ov16_0226DB7C(v0, param0->unk_30C, param0->unk_08, param0->unk_00->heapID, 46270, 46270, 46265, 46265);
    v1 = ov16_0226DC24(v0, param0->unk_30C, param0->unk_00->heapID, 46270, 46270, 46265, 46265, 0, 1);

    SetBattleSubMenuCursorSprites(param0->unk_34, v1);
}

static void ov13_02227FDC(UnkStruct_ov13_02227244 *param0)
{
    ov16_0226DCA8(GetBattleSubMenuCursorSprites(param0->unk_34));
    ov16_0226DBFC(param0->unk_30C, 46270, 46270, 46265, 46265);
}

static const ByteFlagSet Unk_ov13_02229C14[] = {
    { 0x8, 0x10, 0x78, 0x48, 0x0, 0x1, 0x0, 0x2 },
    { 0x8, 0x58, 0x78, 0x90, 0x0, 0x4, 0x1, 0x3 },
    { 0x88, 0x10, 0xF8, 0x48, 0x2, 0x3, 0x0, 0x2 },
    { 0x88, 0x58, 0xF8, 0x90, 0x2, 0x5, 0x1, 0x3 },
    { 0x8, 0xA0, 0xC8, 0xB8, 0x1, 0x4, 0x4, 0x5 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x83, 0x5, 0x4, 0x5 }
};

static const ByteFlagSet Unk_ov13_02229C74[] = {
    { 0x8, 0x10, 0x78, 0x30, 0x0, 0x2, 0x0, 0x1 },
    { 0x88, 0x10, 0xF8, 0x30, 0x1, 0x3, 0x0, 0x1 },
    { 0x8, 0x40, 0x78, 0x60, 0x0, 0x4, 0x2, 0x3 },
    { 0x88, 0x40, 0xF8, 0x60, 0x1, 0x5, 0x2, 0x3 },
    { 0x8, 0x70, 0x78, 0x90, 0x2, 0x86, 0x4, 0x5 },
    { 0x88, 0x70, 0xF8, 0x90, 0x3, 0x8, 0x4, 0x5 },
    { 0x8, 0xA0, 0x20, 0xB8, 0x4, 0x6, 0x6, 0x7 },
    { 0x30, 0xA0, 0x48, 0xB8, 0x4, 0x7, 0x6, 0x8 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x5, 0x8, 0x7, 0x8 }
};

static const ByteFlagSet Unk_ov13_02229BD4[] = {
    { 0x8, 0xA0, 0xC8, 0xB8, 0x0, 0x0, 0x0, 0x1 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x1, 0x1, 0x0, 0x1 }
};

static const ByteFlagSet *const Unk_ov13_02229BC8[] = {
    Unk_ov13_02229C14,
    Unk_ov13_02229C74,
    Unk_ov13_02229BD4
};

void ov13_02228008(UnkStruct_ov13_02227244 *param0, u8 param1)
{
    SetBattleSubMenuCursorPositions(param0->unk_34, Unk_ov13_02229BC8[param1]);

    switch (param1) {
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_MENU:
        SetBattleSubMenuCursorPosition(param0->unk_34, param0->unk_114D);
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_BAG_SUB_MENU:
        SetBattleSubMenuCursorPosition(param0->unk_34, param0->unk_00->unk_27[param0->unk_114D]);
        break;
    case IN_BATTLE_BAG_SCREEN_INDEX_USE_BAG_ITEM:
        break;
    }
}

void ov13_02228050(UnkStruct_ov13_02227244 *param0)
{
    SetBattlePartyBagCursorVisiblity(param0->unk_34, 0);
    ResetBattleSubMenuCursorPosition(param0->unk_34);
    ov16_0226DDE8(GetBattleSubMenuCursorSprites(param0->unk_34));
}

static void ov13_02228070(UnkStruct_ov13_02227244 *param0)
{
    SpriteSystem *v0;
    UnkStruct_ov16_0226DEEC *v1;

    v0 = ov16_0223E010(param0->unk_00->unk_00);

    ov16_0226DE44(v0, param0->unk_30C, param0->unk_00->heapID, param0->unk_08, 46269, 46269, 46264, 46264);
    param0->unk_38 = ov16_0226DEEC(v0, param0->unk_30C, param0->unk_00->heapID, 46269, 46269, 46264, 46264, 0, 0);
}

static void ov13_022280C8(UnkStruct_ov13_02227244 *param0)
{
    ov16_0226DF68(param0->unk_38);
    ov16_0226DEC4(param0->unk_30C, 46269, 46269, 46264, 46264);
}

static const int Unk_ov13_02229BFC[3][2] = {
    { 0xC0, 0x18 },
    { 0x40, 0x10 },
    { 0x68, 0x98 }
};

void ov13_022280F0(UnkStruct_ov13_02227244 *param0, u8 param1)
{
    if (param0->unk_00->unk_14 == 1) {
        ov16_0226DFB0(param0->unk_38, Unk_ov13_02229BFC[param1][0], Unk_ov13_02229BFC[param1][1]);
        ov16_0226DFD0(param0->unk_38, 60);
    } else {
        ov16_0226DFBC(param0->unk_38);
    }
}
