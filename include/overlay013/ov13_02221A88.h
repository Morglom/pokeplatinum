#ifndef POKEPLATINUM_OV13_02221A88_H
#define POKEPLATINUM_OV13_02221A88_H

#include "overlay013/struct_ov13_022213F0.h"

void ov13_02221A88(BattlePartyTask *param0);
void InitializeInBattlePartyScreen(BattlePartyTask *param0, enum InBattleScreenIndex screenIndex);
void ClearInBattlePartyScreen(BattlePartyTask *param0);
void ov13_02221BC8(BattlePartyTask *param0);
void DrawInBattlePartyScreen(BattlePartyTask *param0, enum InBattleScreenIndex screenIndex);
void ov13_02223118(BattlePartyTask *param0);
void DrawHealthDisplay(BattlePartyTask *param0, u8 param1);
void ov13_022234A8(BattlePartyTask *param0, u8 param1);
void ov13_02223F5C(BattlePartyTask *param0, u16 windowIndex, u16 moveIndex);
void DisplayBattleMessageBox(BattlePartyTask *param0);
void ov13_02224108(BattlePartyTask *param0);
void ov13_02224144(BattlePartyTask *param0);
void OnEmbargoBlockingItem(BattlePartyTask *param0);

#endif // POKEPLATINUM_OV13_02221A88_H
