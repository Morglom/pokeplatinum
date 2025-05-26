#ifndef POKEPLATINUM_OV13_0221FC20_H
#define POKEPLATINUM_OV13_0221FC20_H

#include "overlay013/struct_ov13_0221FC20.h"
#include "overlay013/struct_ov13_022213F0.h"

void BattlePartyTask_Start(BattlePartyBattleInfo *battlePartyTask);
u8 ov13_022213F0(BattlePartyTask *battlePartyTask, s32 param1);
u8 ov13_0222196C(BattlePartyTask *battlePartyTask);
u8 ov13_0222198C(BattlePartyTask *battlePartyTask);
u8 CheckIfSwitchingWithPartnersPokemon(BattlePartyTask *battlePartyTask, u8 partySlot);

#endif // POKEPLATINUM_OV13_0221FC20_H
