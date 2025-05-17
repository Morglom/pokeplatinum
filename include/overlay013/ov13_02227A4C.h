#ifndef POKEPLATINUM_OV13_02227A4C_H
#define POKEPLATINUM_OV13_02227A4C_H

#include "overlay013/struct_ov13_02227244.h"

#define BATTLE_BAG_POCKET_NUM 5

BOOL IsLastUsedItemUsable(BattleBagTask *param0);
void SetNavigationForLastUsedItem(BattleBagTask *param0);
void RefreshBagSubMenus(BattleBagTask *param0);
u16 GetBagItemOnPage(BattleBagTask *param0, u32 indexOnPage);

#endif // POKEPLATINUM_OV13_02227A4C_H
