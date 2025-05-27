#ifndef POKEPLATINUM_OV13_02227288_H
#define POKEPLATINUM_OV13_02227288_H

#include "overlay013/struct_ov13_02227244.h"

void InitializeWindows(BattleBagTask *battleBagTask);
void InitializeInBattleBagScreen(BattleBagTask *battleBagTask, enum BattleBagScreen screenIndex);
void ClearInBattleBagScreen(BattleBagTask *battleBagTask);
void ClearBattleBagWindows(BattleBagTask *battleBagTask);
void DrawInBattleBagScreen(BattleBagTask *battleBagTask, enum BattleBagScreen screenIndex);
void DrawBagSubMenuPage(BattleBagTask *battleBagTask);
void DrawBagSubMenuPageInfo(BattleBagTask *battleBagTask);
void DisplayMessageBox(BattleBagTask *battleBagTask);
void PrintTextToMessageBox(BattleBagTask *battleBagTask);

#endif // POKEPLATINUM_OV13_02227288_H
