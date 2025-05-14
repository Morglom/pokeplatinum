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

UnkStruct_ov13_02228A50_t *InitialiseInBattleCursor(u32 heapID)
{
    UnkStruct_ov13_02228A50_t *v0 = Heap_AllocFromHeap(heapID, sizeof(UnkStruct_ov13_02228A50_t));
    memset(v0, 0, sizeof(UnkStruct_ov13_02228A50_t));
    return v0;
}

void ClearInBattleCursor(UnkStruct_ov13_02228A50_t *param0)
{
    Heap_FreeToHeap(param0);
}

UnkStruct_ov16_0226DC24 *GetInBattleCursorSprites(UnkStruct_ov13_02228A50_t *param0)
{
    return param0->unk_00;
}

u8 GetIsInBattleCursorEnabled(UnkStruct_ov13_02228A50_t *param0)
{
    return param0->enabled;
}

void SetIsInBattleCursorEnabled(UnkStruct_ov13_02228A50_t *param0, u8 param1)
{
    param0->enabled = param1;
}

void SetInBattleCursorSprites(UnkStruct_ov13_02228A50_t *param0, UnkStruct_ov16_0226DC24 *param1)
{
    param0->unk_00 = param1;
}

void ov13_02228A68(UnkStruct_ov13_02228A50_t *param0, u8 param1)
{
    param0->setIndex = param1;

    if (param0->enabled == TRUE) {
        ov16_0226DD7C(param0->unk_00, param0->unk_04[param0->setIndex].flagA, param0->unk_04[param0->setIndex].flagC, param0->unk_04[param0->setIndex].flagB, param0->unk_04[param0->setIndex].flagD);
    }
}

void ov13_02228A90(UnkStruct_ov13_02228A50_t *param0)
{
    param0->setIndex = 0;
    param0->unk_0A = 0xff;
}

void ov13_02228A9C(UnkStruct_ov13_02228A50_t *param0, const ByteFlagSet *param1)
{
    ov13_02228A90(param0);

    param0->unk_04 = param1;
    param0->size = 0xffffffff;

    if (param0->enabled == TRUE) {
        ov16_0226DD7C(param0->unk_00, param0->unk_04[0].flagA, param0->unk_04[0].flagC, param0->unk_04[0].flagB, param0->unk_04[0].flagD);
    }
}

void ov13_02228AC8(UnkStruct_ov13_02228A50_t *param0, u32 param1)
{
    param0->size = param1;
}

static u8 CheckCursorIsEnabled(UnkStruct_ov13_02228A50_t *param0)
{
    if (param0->enabled == TRUE) {
        return TRUE;
    }

    if (gSystem.pressedKeys & (PAD_KEY | PAD_BUTTON_B | PAD_BUTTON_A)) {
        param0->enabled = TRUE;

        ov16_0226DD7C(param0->unk_00, param0->unk_04[param0->setIndex].flagA, param0->unk_04[param0->setIndex].flagC, param0->unk_04[param0->setIndex].flagB, param0->unk_04[param0->setIndex].flagD);
        Sound_PlayEffect(SEQ_SE_CONFIRM);
    }

    return FALSE;
}

static BOOL ov13_02228B18(const ByteFlagSet *byteFlagSet, u8 direction)
{
    switch (direction) {
    case BYTE_FLAG_SET_DIRECTION_UP:
        if (byteFlagSet->downIndex & 0x80) {
            return TRUE;
        }
        break;
    case BYTE_FLAG_SET_DIRECTION_DOWN:
        if (byteFlagSet->upIndex & 0x80) {
            return TRUE;
        }
        break;
    case BYTE_FLAG_SET_DIRECTION_LEFT:
        if (byteFlagSet->rightIndex & 0x80) {
            return TRUE;
        }
        break;
    case BYTE_FLAG_SET_DIRECTION_RIGHT:
        if (byteFlagSet->leftIndex & 0x80) {
            return TRUE;
        }
        break;
    }

    return FALSE;
}

u32 CheckInBattleCursorNavigation(UnkStruct_ov13_02228A50_t *param0)
{
    u8 v0, v1, v2, v3;
    u8 directionIndex;
    u8 v5;

    if (CheckCursorIsEnabled(param0) == FALSE) {
        return 0xffffffff;
    }

    if (gSystem.pressedKeys & PAD_KEY_UP) {
        directionIndex = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, param0->setIndex, BYTE_FLAG_SET_DIRECTION_UP);
        v5 = BYTE_FLAG_SET_DIRECTION_UP;
    } else if (gSystem.pressedKeys & PAD_KEY_DOWN) {
        directionIndex = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, param0->setIndex, BYTE_FLAG_SET_DIRECTION_DOWN);
        v5 = BYTE_FLAG_SET_DIRECTION_DOWN;
    } else if (gSystem.pressedKeys & PAD_KEY_LEFT) {
        directionIndex = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, param0->setIndex, BYTE_FLAG_SET_DIRECTION_LEFT);
        v5 = BYTE_FLAG_SET_DIRECTION_LEFT;
    } else if (gSystem.pressedKeys & PAD_KEY_RIGHT) {
        directionIndex = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, param0->setIndex, BYTE_FLAG_SET_DIRECTION_RIGHT);
        v5 = BYTE_FLAG_SET_DIRECTION_RIGHT;
    } else {
        directionIndex = 0xffffffff;
    }

    if (directionIndex != 0xff) {
        u8 v6 = 1;

        if (directionIndex & 0x80) {
            if (param0->unk_0A != 0xff) {
                directionIndex = param0->unk_0A;
            } else {
                directionIndex ^= 0x80;
            }
        }

        while (TRUE) {
            u8 v7;

            if (param0->size & (1 << directionIndex)) {
                break;
            }

            v6 = 0;
            v7 = ReadByteFlags(param0->unk_04, NULL, NULL, NULL, NULL, directionIndex, v5) & (0xff ^ 0x80);

            if ((v7 == directionIndex) || (v7 == param0->setIndex)) {
                directionIndex = param0->setIndex;
                break;
            }

            directionIndex = v7;
        }

        if (param0->setIndex != directionIndex) {
            ReadABByteFlags(&param0->unk_04[directionIndex], &v0, &v1);
            ReadCDByteFlags(&param0->unk_04[directionIndex], &v2, &v3);

            if ((ov13_02228B18(&param0->unk_04[directionIndex], v5) == TRUE) && (v6 != 0)) {
                param0->unk_0A = param0->setIndex;
            } else {
                param0->unk_0A = 0xff;
            }

            param0->setIndex = directionIndex;

            ov16_0226DD7C(param0->unk_00, v0, v2, v1, v3);
            Sound_PlayEffect(SEQ_SE_CONFIRM);
        }

        return 0xffffffff;
    }

    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        return param0->setIndex;
    }

    if (gSystem.pressedKeys & PAD_BUTTON_B) {
        Sound_PlayEffect(SEQ_SE_DP_DECIDE);
        return 0xfffffffe;
    }

    return 0xffffffff;
}
