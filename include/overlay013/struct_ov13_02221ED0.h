#ifndef POKEPLATINUM_STRUCT_OV13_02221ED0_H
#define POKEPLATINUM_STRUCT_OV13_02221ED0_H

#include "overlay013/struct_ov13_022236B8.h"

#include "pokemon.h"

typedef struct {
    Pokemon *pokemon;
    u16 species;
    u16 attack;
    u16 defence;
    u16 speed;
    u16 spAtk;
    u16 spDef;
    u16 currentHP;
    u16 maxHP;
    u8 type1;
    u8 type2;
    u8 level : 7;
    u8 displayGender : 1;
    u8 gender : 3;
    u8 status : 4;
    u8 isEgg : 1;
    u16 ability;
    u16 heldItem;
    u32 exp;
    u32 currentLevelBaseExp;
    u32 nextLevelExp;
    u8 cool;
    u8 beauty;
    u8 cute;
    u8 smart;
    u8 tough;
    u8 mail;
    u8 form;
    UnkStruct_ov13_022236B8 moves[4];
} UnkStruct_ov13_02221ED0;

#endif // POKEPLATINUM_STRUCT_OV13_02221ED0_H
