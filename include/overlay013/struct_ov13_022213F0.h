#ifndef POKEPLATINUM_STRUCT_OV13_022213F0_H
#define POKEPLATINUM_STRUCT_OV13_022213F0_H

#include "struct_decls/struct_0200C440_decl.h"

#include "overlay013/struct_ov13_0221FC20.h"
#include "overlay013/struct_ov13_02221ED0.h"
#include "overlay013/struct_ov13_02228A50_decl.h"

#include "bg_window.h"
#include "message.h"
#include "palette.h"
#include "sprite_system.h"
#include "strbuf.h"
#include "string_template.h"

enum InBattleScreenIndex {
    IN_BATTLE_SCREEN_INDEX_PARTY_LIST = 0,
    IN_BATTLE_SCREEN_INDEX_SELECT_POKEMON,
    IN_BATTLE_SCREEN_INDEX_POKEMON_SUMMARY,
    IN_BATTLE_SCREEN_INDEX_CHECK_MOVES,
    IN_BATTLE_SCREEN_INDEX_MOVE_SUMMARY,
    IN_BATTLE_SCREEN_INDEX_RESTORE_PP,
    IN_BATTLE_SCREEN_LEARN_MOVE_1,
    IN_BATTLE_SCREEN_LEARN_MOVE_CONFIRM,
    IN_BATTLE_SCREEN_LEARN_MOVE_2,
    IN_BATTLE_SCREEN_LEARN_MOVE_CONTEST,
};

typedef struct {
    UnkStruct_ov13_0221FC20 *unk_00;
    PartyPokemonData unk_04[6]; // Party Pokemon
    BgConfig *unk_1E0;
    PaletteData *unk_1E4;
    u16 unk_1E8[4][96];
    u16 unk_4E8[4][96];
    u16 unk_7E8[4][65];
    u16 unk_9F0[4][25];
    u16 unk_AB8[4][25];
    u16 unk_B80[4][25];
    u16 unk_C48[3][510];
    u16 unk_183C[4][96];
    u16 unk_1B3C[3][130];
    u16 unk_1E48[3][36];
    u16 unk_1F20[3][10];
    u16 unk_1F5C[32];
    u8 unk_1F9C;
    u8 unk_1F9D;
    u8 unk_1F9E;
    u8 unk_1F9F_0 : 4;
    u8 unk_1F9F_4 : 3;
    u8 unk_1F9F_7 : 1; // Some bool
    UnkStruct_0200C440 *unk_1FA0;
    MessageLoader *unk_1FA4;
    StringTemplate *unk_1FA8;
    Strbuf *unk_1FAC;
    SpriteManager *unk_1FB0;
    ManagedSprite *unk_1FB4[38];
    Window unk_204C[2]; // Message box windows
    Window *unk_206C; // Window array
    u8 unk_2070; // Window num
    u8 unk_2071;
    u8 unk_2072;
    u8 unk_2073_0 : 4; // Num windows
    u8 unk_2073_4 : 4; // Some sort of enum
    u8 unk_2074; // Another enum
    u8 unk_2075; // Screen queue
    u8 unk_2076; // Enum of some kind
    u8 unk_2077; // Printer id
    u8 unk_2078;
    u8 unk_2079;
    u16 unk_207A;
    u16 unk_207C[4]; // Moves
    UnkStruct_ov13_02228A50 *unk_2084; // Bag
    u8 unk_2088;
    u8 unk_2089;
    u8 unk_208A;
    u8 unk_208B;
} UnkStruct_ov13_022213F0;

#endif // POKEPLATINUM_STRUCT_OV13_022213F0_H
