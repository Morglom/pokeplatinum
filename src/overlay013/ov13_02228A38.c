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

BattlePartyBagCursor *MakeBattlePartyBagCursor(u32 heapID)
{
    BattlePartyBagCursor *cursor = Heap_AllocFromHeap(heapID, sizeof(BattlePartyBagCursor));
    memset(cursor, 0, sizeof(BattlePartyBagCursor));
    return cursor;
}

void DeleteBattlePartyCursor(BattlePartyBagCursor *cursor)
{
    Heap_FreeToHeap(cursor);
}

UnkStruct_ov16_0226DC24 *GetBattlePartyBagCursorSprites(BattlePartyBagCursor *cursor)
{
    return cursor->unk_00;
}

u8 IsBattlePartyBagCursorVisible(BattlePartyBagCursor *cursor)
{
    return cursor->isVisible;
}

void SetBattlePartyBagCursorVisiblity(BattlePartyBagCursor *cursor, u8 isVisible)
{
    cursor->isVisible = isVisible;
}

void SetBattlePartyBagCursorSprites(BattlePartyBagCursor *cursor, UnkStruct_ov16_0226DC24 *sprites)
{
    cursor->unk_00 = sprites;
}

void SetBattlePartyBagCursorPosition(BattlePartyBagCursor *cursor, u8 positionIndex)
{
    cursor->positionIndex = positionIndex;

    if (cursor->isVisible == TRUE) {
        ov16_0226DD7C(cursor->unk_00, cursor->unk_04[cursor->positionIndex].flagA, cursor->unk_04[cursor->positionIndex].flagC, cursor->unk_04[cursor->positionIndex].flagB, cursor->unk_04[cursor->positionIndex].flagD);
    }
}

void ResetPartyBagCursorPosition(BattlePartyBagCursor *cursor)
{
    cursor->positionIndex = 0;
    cursor->unk_0A = 0xff;
}

void SetBattlePartyBagCursorPositions(BattlePartyBagCursor *param0, const ByteFlagSet *param1)
{
    ResetPartyBagCursorPosition(param0);

    param0->unk_04 = param1;
    param0->numPositions = 0xffffffff;

    if (param0->isVisible == TRUE) {
        ov16_0226DD7C(param0->unk_00, param0->unk_04[0].flagA, param0->unk_04[0].flagC, param0->unk_04[0].flagB, param0->unk_04[0].flagD);
    }
}

void ov13_02228AC8(BattlePartyBagCursor *param0, u32 param1)
{
    param0->numPositions = param1;
}

static u8 IsCursorVisible(BattlePartyBagCursor *cursor)
{
    if (cursor->isVisible == TRUE) {
        return TRUE;
    }

    if (gSystem.pressedKeys & (PAD_KEY | PAD_BUTTON_B | PAD_BUTTON_A)) {
        cursor->isVisible = TRUE;

        ov16_0226DD7C(cursor->unk_00, cursor->unk_04[cursor->positionIndex].flagA, cursor->unk_04[cursor->positionIndex].flagC, cursor->unk_04[cursor->positionIndex].flagB, cursor->unk_04[cursor->positionIndex].flagD);
        Sound_PlayEffect(SEQ_SE_CONFIRM);
    }

    return FALSE;
}

static BOOL CheckPositionHasNeightbour(const ByteFlagSet *position, u8 direction)
{
    switch (direction) {
    case BYTE_FLAG_SET_DIRECTION_UP:
        if (position->downIndex & 0x80) {
            return TRUE;
        }
        break;
    case BYTE_FLAG_SET_DIRECTION_DOWN:
        if (position->upIndex & 0x80) {
            return TRUE;
        }
        break;
    case BYTE_FLAG_SET_DIRECTION_LEFT:
        if (position->rightIndex & 0x80) {
            return TRUE;
        }
        break;
    case BYTE_FLAG_SET_DIRECTION_RIGHT:
        if (position->leftIndex & 0x80) {
            return TRUE;
        }
        break;
    }

    return FALSE;
}

u32 CheckBattlePartyBagCursorInputs(BattlePartyBagCursor *param0)
{
    u8 v0, v1, v2, v3;
    u8 nextIndex;
    u8 pressedDirection;

    if (IsCursorVisible(param0) == FALSE) {
        return 0xffffffff;
    }

    if (gSystem.pressedKeys & PAD_KEY_UP) {
        nextIndex = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, param0->positionIndex, BYTE_FLAG_SET_DIRECTION_UP);
        pressedDirection = BYTE_FLAG_SET_DIRECTION_UP;
    } else if (gSystem.pressedKeys & PAD_KEY_DOWN) {
        nextIndex = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, param0->positionIndex, BYTE_FLAG_SET_DIRECTION_DOWN);
        pressedDirection = BYTE_FLAG_SET_DIRECTION_DOWN;
    } else if (gSystem.pressedKeys & PAD_KEY_LEFT) {
        nextIndex = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, param0->positionIndex, BYTE_FLAG_SET_DIRECTION_LEFT);
        pressedDirection = BYTE_FLAG_SET_DIRECTION_LEFT;
    } else if (gSystem.pressedKeys & PAD_KEY_RIGHT) {
        nextIndex = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, param0->positionIndex, BYTE_FLAG_SET_DIRECTION_RIGHT);
        pressedDirection = BYTE_FLAG_SET_DIRECTION_RIGHT;
    } else {
        nextIndex = 0xff;
    }

    if (nextIndex != 0xff) {
        u8 v6 = 1;

        if (nextIndex & 0x80) {
            if (param0->unk_0A != 0xff) {
                nextIndex = param0->unk_0A;
            } else {
                nextIndex ^= 0x80;
            }
        }

        while (TRUE) {
            u8 v7;

            if (param0->numPositions & (1 << nextIndex)) {
                break;
            }

            v6 = 0;
            v7 = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, nextIndex, pressedDirection) & (0xff ^ 0x80);

            if ((v7 == nextIndex) || (v7 == param0->positionIndex)) {
                nextIndex = param0->positionIndex;
                break;
            }

            nextIndex = v7;
        }

        if (param0->positionIndex != nextIndex) {
            ReadABByteFlags(&param0->unk_04[nextIndex], &v0, &v1);
            ReadCDByteFlags(&param0->unk_04[nextIndex], &v2, &v3);

            if ((CheckPositionHasNeightbour(&param0->unk_04[nextIndex], pressedDirection) == TRUE) && (v6 != 0)) {
                param0->unk_0A = param0->positionIndex;
            } else {
                param0->unk_0A = 0xff;
            }

            param0->positionIndex = nextIndex;

            ov16_0226DD7C(param0->unk_00, v0, v2, v1, v3);
            Sound_PlayEffect(SEQ_SE_CONFIRM);
        }

        return 0xffffffff;
    }

    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        return param0->positionIndex;
    }

    if (gSystem.pressedKeys & PAD_BUTTON_B) {
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        return 0xfffffffe;
    }

    return 0xffffffff;
}
