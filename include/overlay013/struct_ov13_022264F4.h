#ifndef POKEPLATINUM_STRUCT_OV13_022264F4_H
#define POKEPLATINUM_STRUCT_OV13_022264F4_H

#include "struct_decls/battle_system.h"

#include "bag.h"
#include "trainer_info.h"

#define BATTLE_BAG_ITEMS_PER_POCKET_PAGE 6

typedef struct {
    BattleSystem *battleSystem;
    TrainerInfo *trainerInfo;
    Bag *bag;
    u32 heapID;
    s32 battler;
    BOOL isCatchTutorial;
    u32 embargoTurns;
    u16 selectedBattleBagItem; // Item of some kind
    u8 selectedBattleBagPocket; // Sub menu index
    u8 lastUsedItemPocket;
    u16 lastUsedItem;
    u8 twoOpponents;
    u8 opponentHidden; // Has used fly, bounce, dig, etc
    u8 opponentSubstituted;
    u8 isCursorEnabled;
    u8 battleBagExited;
    u8 pocketCurrentPagePositions[5];
    u8 pocketCurrentPages[5];
} BattleBagBattleInfo;

#endif // POKEPLATINUM_STRUCT_OV13_022264F4_H
