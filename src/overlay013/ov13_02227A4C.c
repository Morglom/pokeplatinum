#include "overlay013/ov13_02227A4C.h"

#include <nitro.h>
#include <string.h>

#include "overlay013/struct_ov13_02227244.h"

#include "bag.h"
#include "item.h"

enum BattleBagPocketMask {
    BATTLE_BAG_POCKET_MASK_POKE_BALLS = 0x0,
    BATTLE_BAG_POCKET_MASK_BATTLE_ITEMS,
    BATTLE_BAG_POCKET_MASK_RECOVER_HP,
    BATTLE_BAG_POCKET_MASK_RECOVER_STATUS,
    BATTLE_BAG_POCKET_MASK_UNUSUED = 0x0,
};

#define BATTLE_BAG_POCKET_SIZE 36
#define BATTLE_BAG_POCKET_NUM  5

BOOL IsLastUsedItemUsable(UnkStruct_ov13_02227244 *param0)
{
    if (param0->unk_00->lastUsedItem == ITEM_NONE) {
        return FALSE;
    }

    if (Bag_CanRemoveItem(param0->unk_00->bag, param0->unk_00->lastUsedItem, 1, param0->unk_00->heapID) == FALSE) {
        param0->unk_00->lastUsedItem = ITEM_NONE;
        param0->unk_00->lastUsedItemPocket = ITEM_BATTLE_CATEGORY_RECOVER_HP;
        return FALSE;
    }

    return TRUE;
}

void SetNavigationForLastUsedItem(UnkStruct_ov13_02227244 *param0)
{
    u32 i;

    for (i = 0; i < BATTLE_BAG_POCKET_SIZE; i++) {
        if (param0->unk_00->lastUsedItem == param0->unk_3C[param0->unk_114D][i].item) {
            param0->unk_00->unk_27[param0->unk_114D] = i % NUM_BAG_ITEMS_PER_PAGE;
            param0->unk_00->unk_2C[param0->unk_114D] = i / NUM_BAG_ITEMS_PER_PAGE;
            break;
        }
    }
}

static const u8 battleBagPocketMasks[] = {
    BATTLE_BAG_POCKET_MASK_RECOVER_HP,
    BATTLE_BAG_POCKET_MASK_RECOVER_STATUS,
    BATTLE_BAG_POCKET_MASK_POKE_BALLS,
    BATTLE_BAG_POCKET_MASK_BATTLE_ITEMS,
    BATTLE_BAG_POCKET_MASK_UNUSUED
};

void RefreshBagSubMenus(UnkStruct_ov13_02227244 *param0)
{
    BagItem *bagItem;
    u32 i, slotIndex, v3;
    s32 bagItemBattlePocketMask;

    for (i = 0; i < POCKET_MAX; i++) {
        slotIndex = 0;

        while (TRUE) {
            bagItem = Bag_GetItemSlot(param0->unk_00->bag, i, slotIndex);

            if (bagItem == NULL) {
                break;
            }

            if (!((bagItem->item == ITEM_NONE) || (bagItem->quantity == 0))) {
                bagItemBattlePocketMask = Item_LoadParam(bagItem->item, ITEM_PARAM_BATTLE_POCKET, param0->unk_00->heapID);

                for (v3 = 0; v3 < BATTLE_BAG_POCKET_NUM; v3++) {
                    if ((bagItemBattlePocketMask & (1 << v3)) == FALSE) {
                        continue;
                    }

                    param0->unk_3C[battleBagPocketMasks[v3]][param0->unk_114F[battleBagPocketMasks[v3]]] = *bagItem;
                    param0->unk_114F[battleBagPocketMasks[v3]]++;
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
