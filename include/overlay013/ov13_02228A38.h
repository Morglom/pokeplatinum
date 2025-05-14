#ifndef POKEPLATINUM_OV13_02228A38_H
#define POKEPLATINUM_OV13_02228A38_H

#include "battle/struct_ov16_0226DC24_decl.h"

#include "byte_flag_set.h"

#define BATTLE_SUB_MENU_CURSOR_BACK_INDEX        0xfffffffe
#define BATTLE_SUB_MENU_CURSOR_NO_MOVEMENT_INDEX 0xffffffff

typedef struct BattleSubMenuCursor {
    UnkStruct_ov16_0226DC24 *sprites;
    const ByteFlagSet *positions;
    u8 isVisible;
    u8 currentPositionIndex;
    u8 previousPositionIndex;
    u32 enabledPositionsMask;
} BattleSubMenuCursor;

BattleSubMenuCursor *MakeBattleSubMenuCursor(u32 heapID);
void DeleteBattleSubMenuCursor(BattleSubMenuCursor *cursor);
UnkStruct_ov16_0226DC24 *GetBattleSubMenuCursorSprites(BattleSubMenuCursor *cursor);
u8 IsBattleSubMenuCursorVisible(BattleSubMenuCursor *cursor);
void SetBattlePartyBagCursorVisiblity(BattleSubMenuCursor *cursor, u8 isVisible);
void SetBattleSubMenuCursorSprites(BattleSubMenuCursor *cursor, UnkStruct_ov16_0226DC24 *sprites);
void SetBattleSubMenuCursorPosition(BattleSubMenuCursor *cursor, u8 positionIndex);
void ResetBattleSubMenuCursorPosition(BattleSubMenuCursor *cursor);
void SetBattleSubMenuCursorPositions(BattleSubMenuCursor *param0, const ByteFlagSet *param1);
void SetEnabledPositionsMask(BattleSubMenuCursor *param0, u32 param1);
u32 CheckBattleSubMenuCursorInputs(BattleSubMenuCursor *param0);

#endif // POKEPLATINUM_OV13_02228A38_H
