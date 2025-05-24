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

BOOL IsLastUsedItemUsable(BattleBagTask *param0)
{
    if (param0->battleInfo->lastUsedItem == ITEM_NONE) {
        return FALSE;
    }

    if (Bag_CanRemoveItem(param0->battleInfo->bag, param0->battleInfo->lastUsedItem, 1, param0->battleInfo->heapID) == FALSE) {
        param0->battleInfo->lastUsedItem = ITEM_NONE;
        param0->battleInfo->lastUsedItemPocket = ITEM_BATTLE_CATEGORY_RECOVER_HP;
        return FALSE;
    }

    return TRUE;
}

void SetNavigationForLastUsedItem(BattleBagTask *param0)
{
    u32 i;

    for (i = 0; i < BATTLE_BAG_POCKET_SIZE; i++) {
        if (param0->battleInfo->lastUsedItem == param0->battleBagItems[param0->currentBattleBagPocket][i].item) {
            param0->battleInfo->pocketCurrentPagePositions[param0->currentBattleBagPocket] = i % BATTLE_BAG_ITEMS_PER_POCKET_PAGE;
            param0->battleInfo->pocketCurrentPages[param0->currentBattleBagPocket] = i / BATTLE_BAG_ITEMS_PER_POCKET_PAGE;
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

void RefreshBagSubMenus(BattleBagTask *param0)
{
    BagItem *bagItem;
    u32 i, l, currentSlot;
    s32 bagItemBattlePocketMask;

    for (i = 0; i < POCKET_MAX; i++) {
        currentSlot = 0;

        while (TRUE) {
            bagItem = Bag_GetItemSlot(param0->battleInfo->bag, i, currentSlot);

            if (bagItem == NULL) {
                break;
            }

            if (!((bagItem->item == ITEM_NONE) || (bagItem->quantity == 0))) {
                bagItemBattlePocketMask = Item_LoadParam(bagItem->item, ITEM_PARAM_BATTLE_POCKET, param0->battleInfo->heapID);

                for (l = 0; l < BATTLE_BAG_POCKET_NUM; l++) {
                    if ((bagItemBattlePocketMask & (1 << l)) == FALSE) {
                        continue;
                    }

                    param0->battleBagItems[battleBagPocketMasks[l]][param0->numBattleBagPocketItems[battleBagPocketMasks[l]]] = *bagItem;
                    param0->numBattleBagPocketItems[battleBagPocketMasks[l]]++;
                }
            }

            currentSlot++;
        }
    }

    for (i = 0; i < BATTLE_BAG_POCKET_NUM; i++) {
        if (param0->numBattleBagPocketItems[i] == 0) {
            param0->numBattleBagPocketPages[i] = 0;
        } else {
            param0->numBattleBagPocketPages[i] = (param0->numBattleBagPocketItems[i] - 1) / BATTLE_BAG_ITEMS_PER_POCKET_PAGE;
        }

        if (param0->numBattleBagPocketPages[i] < param0->battleInfo->pocketCurrentPages[i]) {
            param0->battleInfo->pocketCurrentPages[i] = param0->numBattleBagPocketPages[i];
        }
    }
}

u16 GetBagItemOnPage(BattleBagTask *param0, u32 positionOnPage)
{
    if ((param0->battleBagItems[param0->currentBattleBagPocket][param0->battleInfo->pocketCurrentPages[param0->currentBattleBagPocket] * BATTLE_BAG_ITEMS_PER_POCKET_PAGE + positionOnPage].item != ITEM_NONE) && (param0->battleBagItems[param0->currentBattleBagPocket][param0->battleInfo->pocketCurrentPages[param0->currentBattleBagPocket] * BATTLE_BAG_ITEMS_PER_POCKET_PAGE + positionOnPage].quantity != 0)) {
        return param0->battleBagItems[param0->currentBattleBagPocket][param0->battleInfo->pocketCurrentPages[param0->currentBattleBagPocket] * BATTLE_BAG_ITEMS_PER_POCKET_PAGE + positionOnPage].item;
    }

    return ITEM_NONE;
}
