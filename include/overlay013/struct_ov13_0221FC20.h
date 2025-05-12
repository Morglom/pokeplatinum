#ifndef POKEPLATINUM_STRUCT_OV13_0221FC20_H
#define POKEPLATINUM_STRUCT_OV13_0221FC20_H

#include "struct_decls/battle_system.h"

#include "party.h"

typedef struct {
    Party *unk_00; // Party
    void *unk_04;
    BattleSystem *unk_08; // Battle system
    u32 heapID;
    u8 unk_10;
    u8 selectedPartyIndex;
    u8 unk_12;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u32 unk_18[2];
    u16 unk_20;
    u16 unk_22; // Item selected for use
    u16 unk_24; // Move to learn
    s32 unk_28; // Battler
    u8 unk_2C[6]; // Party slots
    u8 unk_32;
    u8 unk_33; // Item Category?
    u8 unk_34; // Index of selected move
    u8 unk_35; // Selection enum maybe
    u8 unk_36;
} UnkStruct_ov13_0221FC20;

#endif // POKEPLATINUM_STRUCT_OV13_0221FC20_H
