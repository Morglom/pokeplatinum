#include "overlay013/ov13_02228A38.h"

#include <nitro.h>
#include <string.h>

#include "battle/ov16_0226DB7C.h"
#include "battle/struct_ov16_0226DC24_decl.h"
#include "overlay013/ov13_02228A38.h"

#include "byte_flag_set.h"
#include "heap.h"
#include "sound_playback.h"
#include "system.h"

#define CURSOR_STARTING_INDEX              0
#define NULL_POSITION_INDEX                0xff
#define GO_TO_PREVIOUS_POSITION_INDEX_MASK 0x80
#define ALL_POSITIONS_ENABLED_MASK         0xffffffff

BattleSubMenuCursor *MakeBattleSubMenuCursor(u32 heapID)
{
    BattleSubMenuCursor *cursor = Heap_AllocFromHeap(heapID, sizeof(BattleSubMenuCursor));
    memset(cursor, 0, sizeof(BattleSubMenuCursor));
    return cursor;
}

void DeleteBattleSubMenuCursor(BattleSubMenuCursor *cursor)
{
    Heap_FreeToHeap(cursor);
}

UnkStruct_ov16_0226DC24 *GetBattleSubMenuCursorSprites(BattleSubMenuCursor *cursor)
{
    return cursor->sprites;
}

u8 IsBattleSubMenuCursorVisible(BattleSubMenuCursor *cursor)
{
    return cursor->isVisible;
}

void SetBattlePartyBagCursorVisiblity(BattleSubMenuCursor *cursor, u8 isVisible)
{
    cursor->isVisible = isVisible;
}

void SetBattleSubMenuCursorSprites(BattleSubMenuCursor *cursor, UnkStruct_ov16_0226DC24 *sprites)
{
    cursor->sprites = sprites;
}

void SetBattleSubMenuCursorPosition(BattleSubMenuCursor *cursor, u8 positionIndex)
{
    cursor->currentPositionIndex = positionIndex;

    if (cursor->isVisible == TRUE) {
        ov16_0226DD7C(cursor->sprites, cursor->positions[cursor->currentPositionIndex].flagA, cursor->positions[cursor->currentPositionIndex].flagC, cursor->positions[cursor->currentPositionIndex].flagB, cursor->positions[cursor->currentPositionIndex].flagD);
    }
}

void ResetBattleSubMenuCursorPosition(BattleSubMenuCursor *cursor)
{
    cursor->currentPositionIndex = CURSOR_STARTING_INDEX;
    cursor->previousPositionIndex = NULL_POSITION_INDEX;
}

void SetBattleSubMenuCursorPositions(BattleSubMenuCursor *cursor, const ByteFlagSet *positions)
{
    ResetBattleSubMenuCursorPosition(cursor);

    cursor->positions = positions;
    cursor->enabledPositionsMask = ALL_POSITIONS_ENABLED_MASK;

    if (cursor->isVisible == TRUE) {
        ov16_0226DD7C(cursor->sprites, cursor->positions[CURSOR_STARTING_INDEX].flagA, cursor->positions[CURSOR_STARTING_INDEX].flagC, cursor->positions[CURSOR_STARTING_INDEX].flagB, cursor->positions[CURSOR_STARTING_INDEX].flagD);
    }
}

void SetEnabledPositionsMask(BattleSubMenuCursor *cursor, u32 mask)
{
    cursor->enabledPositionsMask = mask;
}

static u8 IsCursorVisible(BattleSubMenuCursor *cursor)
{
    if (cursor->isVisible == TRUE) {
        return TRUE;
    }

    if (gSystem.pressedKeys & (PAD_KEY | PAD_BUTTON_B | PAD_BUTTON_A)) {
        cursor->isVisible = TRUE;

        ov16_0226DD7C(cursor->sprites, cursor->positions[cursor->currentPositionIndex].flagA, cursor->positions[cursor->currentPositionIndex].flagC, cursor->positions[cursor->currentPositionIndex].flagB, cursor->positions[cursor->currentPositionIndex].flagD);
        Sound_PlayEffect(SEQ_SE_CONFIRM);
    }

    return FALSE;
}

static BOOL CheckShouldStorePreviousPosition(const ByteFlagSet *newPosition, u8 incomingDirection)
{
    switch (incomingDirection) {
    case BYTE_FLAG_SET_DIRECTION_UP:
        if (newPosition->downIndex & GO_TO_PREVIOUS_POSITION_INDEX_MASK) {
            return TRUE;
        }
        break;
    case BYTE_FLAG_SET_DIRECTION_DOWN:
        if (newPosition->upIndex & GO_TO_PREVIOUS_POSITION_INDEX_MASK) {
            return TRUE;
        }
        break;
    case BYTE_FLAG_SET_DIRECTION_LEFT:
        if (newPosition->rightIndex & GO_TO_PREVIOUS_POSITION_INDEX_MASK) {
            return TRUE;
        }
        break;
    case BYTE_FLAG_SET_DIRECTION_RIGHT:
        if (newPosition->leftIndex & GO_TO_PREVIOUS_POSITION_INDEX_MASK) {
            return TRUE;
        }
        break;
    }

    return FALSE;
}

u32 CheckBattleSubMenuCursorInputs(BattleSubMenuCursor *cursor)
{
    u8 nextPositionIndex;
    u8 pressedDirection;

    if (IsCursorVisible(cursor) == FALSE) {
        return BATTLE_SUB_MENU_CURSOR_NO_MOVEMENT_INDEX;
    }

    if (gSystem.pressedKeys & PAD_KEY_UP) {
        nextPositionIndex = ReadByteFlags(cursor->positions, NULL, NULL, NULL, NULL, cursor->currentPositionIndex, BYTE_FLAG_SET_DIRECTION_UP);
        pressedDirection = BYTE_FLAG_SET_DIRECTION_UP;
    } else if (gSystem.pressedKeys & PAD_KEY_DOWN) {
        nextPositionIndex = ReadByteFlags(cursor->positions, NULL, NULL, NULL, NULL, cursor->currentPositionIndex, BYTE_FLAG_SET_DIRECTION_DOWN);
        pressedDirection = BYTE_FLAG_SET_DIRECTION_DOWN;
    } else if (gSystem.pressedKeys & PAD_KEY_LEFT) {
        nextPositionIndex = ReadByteFlags(cursor->positions, NULL, NULL, NULL, NULL, cursor->currentPositionIndex, BYTE_FLAG_SET_DIRECTION_LEFT);
        pressedDirection = BYTE_FLAG_SET_DIRECTION_LEFT;
    } else if (gSystem.pressedKeys & PAD_KEY_RIGHT) {
        nextPositionIndex = ReadByteFlags(cursor->positions, NULL, NULL, NULL, NULL, cursor->currentPositionIndex, BYTE_FLAG_SET_DIRECTION_RIGHT);
        pressedDirection = BYTE_FLAG_SET_DIRECTION_RIGHT;
    } else {
        nextPositionIndex = NULL_POSITION_INDEX;
    }

    if (nextPositionIndex != NULL_POSITION_INDEX) {
        u8 nextPositionIsEnabled = TRUE;

        if (nextPositionIndex & GO_TO_PREVIOUS_POSITION_INDEX_MASK) {
            if (cursor->previousPositionIndex != NULL_POSITION_INDEX) {
                nextPositionIndex = cursor->previousPositionIndex;
            } else {
                nextPositionIndex ^= GO_TO_PREVIOUS_POSITION_INDEX_MASK;
            }
        }

        while (TRUE) {
            u8 replacementPositionIndex;

            if (cursor->enabledPositionsMask & (1 << nextPositionIndex)) {
                break;
            }

            nextPositionIsEnabled = FALSE;
            replacementPositionIndex = ReadByteFlags(cursor->positions, NULL, NULL, NULL, NULL, nextPositionIndex, pressedDirection) & (NULL_POSITION_INDEX ^ GO_TO_PREVIOUS_POSITION_INDEX_MASK);

            if ((replacementPositionIndex == nextPositionIndex) || (replacementPositionIndex == cursor->currentPositionIndex)) {
                nextPositionIndex = cursor->currentPositionIndex;
                break;
            }

            nextPositionIndex = replacementPositionIndex;
        }

        if (cursor->currentPositionIndex != nextPositionIndex) {
            u8 x1, y1, x2, y2;

            ReadABByteFlags(&cursor->positions[nextPositionIndex], &x1, &y1);
            ReadCDByteFlags(&cursor->positions[nextPositionIndex], &x2, &y2);

            if ((CheckShouldStorePreviousPosition(&cursor->positions[nextPositionIndex], pressedDirection) == TRUE) && (nextPositionIsEnabled != FALSE)) {
                cursor->previousPositionIndex = cursor->currentPositionIndex;
            } else {
                cursor->previousPositionIndex = NULL_POSITION_INDEX;
            }

            cursor->currentPositionIndex = nextPositionIndex;

            ov16_0226DD7C(cursor->sprites, x1, x2, y1, y2);
            Sound_PlayEffect(SEQ_SE_CONFIRM);
        }

        return BATTLE_SUB_MENU_CURSOR_NO_MOVEMENT_INDEX;
    }

    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        return cursor->currentPositionIndex;
    }

    if (gSystem.pressedKeys & PAD_BUTTON_B) {
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        return BATTLE_SUB_MENU_CURSOR_BACK_INDEX;
    }

    return BATTLE_SUB_MENU_CURSOR_NO_MOVEMENT_INDEX;
}
