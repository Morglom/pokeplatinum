#ifndef POKEPLATINUM_OV13_02227BDC_H
#define POKEPLATINUM_OV13_02227BDC_H

#include "overlay013/struct_ov13_02227244.h"

void ov13_02227BDC(BattleBagTask *battleBagTask);
void ClearPocketItemSprites(BattleBagTask *battleBagTask);
void RenderBattleBagScreenSprites(BattleBagTask *battleBagTask, u32 screen);
void SetupBattleBagCursor(BattleBagTask *battleBagTask, u8 screen);
void DisableBattleBagCursor(BattleBagTask *battleBagTask);
void ov13_022280F0(BattleBagTask *battleBagTask, u8 screen);

#endif // POKEPLATINUM_OV13_02227BDC_H
