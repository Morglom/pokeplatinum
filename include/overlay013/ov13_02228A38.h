#ifndef POKEPLATINUM_OV13_02228A38_H
#define POKEPLATINUM_OV13_02228A38_H

#include "battle/struct_ov16_0226DC24_decl.h"

#include "byte_flag_set.h"

typedef struct BattlePartyBagCursor {
    UnkStruct_ov16_0226DC24 *unk_00; // Sprites
    const ByteFlagSet *unk_04; // Cursor buttons
    u8 isVisible;
    u8 positionIndex;
    u8 unk_0A; // Some sort of index
    u32 numPositions; // Size I think
} BattlePartyBagCursor;

BattlePartyBagCursor *MakeBattlePartyBagCursor(u32 heapID);
void DeleteBattlePartyCursor(BattlePartyBagCursor *cursor);
UnkStruct_ov16_0226DC24 *GetBattlePartyBagCursorSprites(BattlePartyBagCursor *cursor);
u8 IsBattlePartyBagCursorVisible(BattlePartyBagCursor *cursor);
void SetBattlePartyBagCursorVisiblity(BattlePartyBagCursor *cursor, u8 isVisible);
void SetBattlePartyBagCursorSprites(BattlePartyBagCursor *cursor, UnkStruct_ov16_0226DC24 *sprites);
void SetBattlePartyBagCursorPosition(BattlePartyBagCursor *cursor, u8 positionIndex);
void ResetPartyBagCursorPosition(BattlePartyBagCursor *cursor);
void SetBattlePartyBagCursorPositions(BattlePartyBagCursor *param0, const ByteFlagSet *param1);
void ov13_02228AC8(BattlePartyBagCursor *param0, u32 param1);
u32 CheckBattlePartyBagCursorInputs(BattlePartyBagCursor *param0);

#endif // POKEPLATINUM_OV13_02228A38_H
