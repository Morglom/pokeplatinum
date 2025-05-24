#ifndef POKEPLATINUM_OV13_02227288_H
#define POKEPLATINUM_OV13_02227288_H

#include "overlay013/struct_ov13_02227244.h"

void ov13_02227288(BattleBagTask *param0);
void InitializeInBattleBagScreen(BattleBagTask *param0, enum InBattlePartyScreenIndex screenIndex);
void ClearInBattleBagScreen(BattleBagTask *param0);
void ClearBattleBagWindows(BattleBagTask *param0);
void DrawInBattleBagScreen(BattleBagTask *param0, enum InBattlePartyScreenIndex screenIndex);
void DrawBagSubMenuPage(BattleBagTask *param0);
void DrawBagSubMenuPageInfo(BattleBagTask *param0);
void ov13_022279F4(BattleBagTask *param0);
void ov13_02227A1C(BattleBagTask *param0);

#endif // POKEPLATINUM_OV13_02227288_H
