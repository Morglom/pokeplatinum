#include "overlay013/ov13_02227A4C.h"

#include <nitro.h>
#include <string.h>

#include "overlay013/struct_ov13_02227244.h"

#include "bag.h"
#include "item.h"

enum BattleBagItemPocket {
    BATTLE_BAG_ITEM_POCKET_HP_PP = 0,
    BATTLE_BAG_ITEM_POCKET_STATUS,
    BATTLE_BAG_ITEM_POCKET_POKEBALL,
    BATTLE_BAG_ITEM_POCKET_BATTLE,
};

#define BAG_SUB_MENU_MAX_ITEMS 36
#define BATTLE_BAG_POCKET_NUM  5

BOOL IsLastUsedItemUsable(UnkStruct_ov13_02227244 *param0)
{
    if (param0->unk_00->lastUsedItem == ITEM_NONE) {
        return FALSE;
    }

    if (Bag_CanRemoveItem(param0->unk_00->unk_08, param0->unk_00->lastUsedItem, 1, param0->unk_00->heapID) == FALSE) {
        param0->unk_00->lastUsedItem = ITEM_NONE;
        param0->unk_00->unk_1F = 0;
        return FALSE;
    }

    return TRUE;
}

void SetNavigationForLastUsedItem(UnkStruct_ov13_02227244 *param0)
{
    u32 i;

    for (i = 0; i < BAG_SUB_MENU_MAX_ITEMS; i++) {
        if (param0->unk_00->lastUsedItem == param0->unk_3C[param0->unk_114D][i].item) {
            param0->unk_00->unk_27[param0->unk_114D] = i % NUM_BAG_ITEMS_PER_PAGE;
            param0->unk_00->unk_2C[param0->unk_114D] = i / NUM_BAG_ITEMS_PER_PAGE;
            break;
        }
    }
}

static const u8 Unk_ov13_02229BB0[] = {
    0x2,
    0x3,
    0x0,
    0x1,
    0x0
};

void RefreshBagSubMenus(UnkStruct_ov13_02227244 *param0)
{
    BagItem *bagItem;
    u32 i, slotIndex, v3;
    s32 bagItemBattlePocketMask;

    for (i = 0; i < POCKET_MAX; i++) {
        slotIndex = 0;

        while (TRUE) {
            bagItem = Bag_GetItemSlot(param0->unk_00->unk_08, i, slotIndex);

            if (bagItem == NULL) {
                break;
            }

            if (!((bagItem->item == ITEM_NONE) || (bagItem->quantity == 0))) {
                bagItemBattlePocketMask = Item_LoadParam(bagItem->item, ITEM_PARAM_BATTLE_POCKET, param0->unk_00->heapID);

                for (v3 = 0; v3 < BATTLE_BAG_POCKET_NUM; v3++) {
                    if ((bagItemBattlePocketMask & (1 << v3)) == FALSE) {
                        continue;
                    }

                    param0->unk_3C[Unk_ov13_02229BB0[v3]][param0->unk_114F[Unk_ov13_02229BB0[v3]]] = *bagItem;
                    param0->unk_114F[Unk_ov13_02229BB0[v3]]++;
                }
            }

            slotIndex++;
        }
    }

    for (i = 0; i < BATTLE_BAG_POCKET_NUM; i++) {
        if (param0->unk_114F[i] == 0) {
            param0->unk_1154[i] = 0;
        } else {
            param0->unk_1154[i] = (param0->unk_114F[i] - 1) / NUM_BAG_ITEMS_PER_PAGE;
        }

        if (param0->unk_1154[i] < param0->unk_00->unk_2C[i]) {
            param0->unk_00->unk_2C[i] = param0->unk_1154[i];
        }
    }
}

u16 GetBagItemOnPage(UnkStruct_ov13_02227244 *param0, u32 indexOnPage)
{
    if ((param0->unk_3C[param0->unk_114D][param0->unk_00->unk_2C[param0->unk_114D] * NUM_BAG_ITEMS_PER_PAGE + indexOnPage].item != ITEM_NONE) && (param0->unk_3C[param0->unk_114D][param0->unk_00->unk_2C[param0->unk_114D] * NUM_BAG_ITEMS_PER_PAGE + indexOnPage].quantity != 0)) {
        return param0->unk_3C[param0->unk_114D][param0->unk_00->unk_2C[param0->unk_114D] * NUM_BAG_ITEMS_PER_PAGE + indexOnPage].item;
    }

    return ITEM_NONE;
}
