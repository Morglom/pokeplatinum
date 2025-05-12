#ifndef POKEPLATINUM_OV13_02221A88_H
#define POKEPLATINUM_OV13_02221A88_H

#include "overlay013/struct_ov13_022213F0.h"

void ov13_02221A88(UnkStruct_ov13_022213F0 *param0);
void InitializeInBattlePartyScreen(UnkStruct_ov13_022213F0 *param0, enum InBattleScreenIndex screenIndex);
void ClearInBattlePartyScreen(UnkStruct_ov13_022213F0 *param0);
void ov13_02221BC8(UnkStruct_ov13_022213F0 *param0);
void DrawInBattlePartyScreen(UnkStruct_ov13_022213F0 *param0, enum InBattleScreenIndex screenIndex);
void ov13_02223118(UnkStruct_ov13_022213F0 *param0);
void DrawHealthDisplay(UnkStruct_ov13_022213F0 *param0, u8 param1);
void ov13_022234A8(UnkStruct_ov13_022213F0 *param0, u8 param1);
void ov13_02223F5C(UnkStruct_ov13_022213F0 *param0, u16 windowIndex, u16 moveIndex);
void DisplayBattleMessageBox(UnkStruct_ov13_022213F0 *param0);
void ov13_02224108(UnkStruct_ov13_022213F0 *param0);
void ov13_02224144(UnkStruct_ov13_022213F0 *param0);
void OnEmbargoBlockingItem(UnkStruct_ov13_022213F0 *param0);

#endif // POKEPLATINUM_OV13_02221A88_H
