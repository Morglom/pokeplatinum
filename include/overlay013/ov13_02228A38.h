#ifndef POKEPLATINUM_OV13_02228A38_H
#define POKEPLATINUM_OV13_02228A38_H

#include "battle/struct_ov16_0226DC24_decl.h"

#include "byte_flag_set.h"

typedef struct UnkStruct_ov13_02228A50_t {
    UnkStruct_ov16_0226DC24 *unk_00; // Sprites
    const ByteFlagSet *unk_04; // Cursor buttons
    u8 enabled;
    u8 setIndex; // Set Index
    u8 unk_0A; // Some sort of index
    u32 size; // Size I think
} UnkStruct_ov13_02228A50_t;

UnkStruct_ov13_02228A50_t *InitialiseInBattleCursor(u32 heapID);
void ClearInBattleCursor(UnkStruct_ov13_02228A50_t *param0);
UnkStruct_ov16_0226DC24 *GetInBattleCursorSprites(UnkStruct_ov13_02228A50_t *param0);
u8 GetIsInBattleCursorEnabled(UnkStruct_ov13_02228A50_t *param0);
void SetIsInBattleCursorEnabled(UnkStruct_ov13_02228A50_t *param0, u8 param1);
void SetInBattleCursorSprites(UnkStruct_ov13_02228A50_t *param0, UnkStruct_ov16_0226DC24 *param1);
void ov13_02228A68(UnkStruct_ov13_02228A50_t *param0, u8 param1);
void ov13_02228A90(UnkStruct_ov13_02228A50_t *param0);
void ov13_02228A9C(UnkStruct_ov13_02228A50_t *param0, const ByteFlagSet *param1);
void ov13_02228AC8(UnkStruct_ov13_02228A50_t *param0, u32 param1);
u32 CheckInBattleCursorNavigation(UnkStruct_ov13_02228A50_t *param0);

#endif // POKEPLATINUM_OV13_02228A38_H
