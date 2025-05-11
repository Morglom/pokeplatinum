#include "overlay013/ov13_02227A4C.h"

#include <nitro.h>
#include <string.h>

#include "overlay013/struct_ov13_02227244.h"

#include "bag.h"
#include "item.h"

#define BAG_POCKETS_NUM 8

BOOL ov13_02227A4C(UnkStruct_ov13_02227244 *param0)
{
    if (param0->unk_00->unk_20 == ITEM_NONE) {
        return FALSE;
    }

    if (Bag_CanRemoveItem(param0->unk_00->unk_08, param0->unk_00->unk_20, 1, param0->unk_00->heapID) == FALSE) {
        param0->unk_00->unk_20 = ITEM_NONE;
        param0->unk_00->unk_1F = 0;
        return FALSE;
    }

    return TRUE;
}

void ov13_02227A7C(UnkStruct_ov13_02227244 *param0)
{
    u32 v0;

    for (v0 = 0; v0 < 36; v0++) {
        if (param0->unk_00->unk_20 == param0->unk_3C[param0->unk_114D][v0].item) {
            param0->unk_00->unk_27[param0->unk_114D] = v0 % 6;
            param0->unk_00->unk_2C[param0->unk_114D] = v0 / 6;
            break;
        }
    }
}

static const u8 Unk_ov13_02229BB0[] = {
    0x2,
    0x3,
    0x0,
    0x1,
    0x0
};

void ov13_02227AC8(UnkStruct_ov13_02227244 *param0)
{
    BagItem *v0;
    u32 i, slotIndex, v3;
    s32 v4;

    for (i = 0; i < BAG_POCKETS_NUM; i++) {
        slotIndex = 0;

        while (TRUE) {
            v0 = Bag_GetItemSlot(param0->unk_00->unk_08, i, slotIndex);

            if (v0 == NULL) {
                break;
            }

            if (!((v0->item == ITEM_NONE) || (v0->quantity == 0))) {
                v4 = Item_LoadParam(v0->item, ITEM_PARAM_BATTLE_POCKET, param0->unk_00->heapID);

                for (v3 = 0; v3 < 5; v3++) {
                    if ((v4 & (1 << v3)) == FALSE) {
                        continue;
                    }

                    param0->unk_3C[Unk_ov13_02229BB0[v3]][param0->unk_114F[Unk_ov13_02229BB0[v3]]] = *v0;
                    param0->unk_114F[Unk_ov13_02229BB0[v3]]++;
                }
            }

            slotIndex++;
        }
    }

    for (i = 0; i < 5; i++) {
        if (param0->unk_114F[i] == 0) {
            param0->unk_1154[i] = 0;
        } else {
            param0->unk_1154[i] = (param0->unk_114F[i] - 1) / 6;
        }

        if (param0->unk_1154[i] < param0->unk_00->unk_2C[i]) {
            param0->unk_00->unk_2C[i] = param0->unk_1154[i];
        }
    }
}

// Get item
u16 ov13_02227BA8(UnkStruct_ov13_02227244 *param0, u32 param1)
{
    if ((param0->unk_3C[param0->unk_114D][param0->unk_00->unk_2C[param0->unk_114D] * 6 + param1].item != 0) && (param0->unk_3C[param0->unk_114D][param0->unk_00->unk_2C[param0->unk_114D] * 6 + param1].quantity != 0)) {
        return param0->unk_3C[param0->unk_114D][param0->unk_00->unk_2C[param0->unk_114D] * 6 + param1].item;
    }

    return 0;
}
