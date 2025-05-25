#ifndef POKEPLATINUM_OV13_0221FC20_H
#define POKEPLATINUM_OV13_0221FC20_H

#include "overlay013/struct_ov13_0221FC20.h"
#include "overlay013/struct_ov13_022213F0.h"

void BattlePartyTask_Start(BattlePartyBattleInfo *param0);
u8 ov13_022213F0(BattlePartyTask *param0, s32 param1);
u8 ov13_0222196C(BattlePartyTask *param0);
u8 ov13_0222198C(BattlePartyTask *param0);
u8 CheckIfSwitchingWithPartnersPokemon(BattlePartyTask *param0, u8 partyIndex);

#endif // POKEPLATINUM_OV13_0221FC20_H
