#include "common.h"
#include "ovl_81.h"
#include "game/hmfman.h"
#include "game/sprite.h"

// duel n2: the dice block (Duel Mode's copy of ovl_80 EE660: roll, number sprites, hit effects).

/* func_800DC0EC's work. */
typedef struct DuelDiceProc {
    /* 0x00 */ s32 playerNo;
    /* 0x04 */ s32 state;
    /* 0x08 */ char unk08[8];
} DuelDiceProc; /* size 0x10 */

extern f32 D_800A0A7C_main;
extern u8 D_80100E20_name_81;
extern s32 D_80100E24_name_81[3]; /* dice model per mode */
extern s32 D_80100E30_name_81[3]; /* dice motion per mode */
extern u8 D_80105554_name_81;     /* 1 several dice at once (high column), 2 a plain block */
extern u8 D_80105555_name_81;
extern u8 D_8010562C_name_81;
extern f32 D_80105708_name_81;    /* dice height above the player */
extern s8 D_80105710_name_81;

void func_800EF7C8_name_81(Object*, f32, f32);
void func_800F3880_name_81(s32, s16, s16);
void func_800F397C_name_81(s32, s16, s16, s16, u16);

void func_800DBD88_name_81(s32 arg0);
void func_800DC4E4_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_800D9F90_name_81(s32 arg0) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];

    if ((entry->unk28 == -1) && (entry->dice->work[0] == 1)) {
        if (entry->unk_0A == 1) {
            entry->unk28 = HuAudFXPlay(0x1D5);
        } else {
            entry->unk28 = HuAudFXPlay(0x100);
        }
    }
}

void func_800DA00C_name_81(omObjData* arg0) {
    UnkDiceRelated* entry;
    f32 base;
    f32 scale;
    f32 decay;
    s32 i;

    entry = &D_800CDBD0_main[arg0->work[3]];
    if (D_80105554_name_81 == 1) {
        base = 1.0f;
    } else {
        base = 0.1f;
    }

    switch (arg0->work[0]) {
        case 0:
            if (HmfPauseF != 0) {
                return;
            }
            arg0->trans.y = GwPlayer[arg0->work[3]].player_obj->coords.y + D_80105708_name_81;
            scale = (sindf(arg0->work[1] * 2) * entry->unk48 * base) + base;
            arg0->scale.x = arg0->scale.y = arg0->scale.z = scale;
            arg0->rot.y += 22.5f;
            arg0->work[1] = (arg0->work[1] + 25) % 180;
            decay = entry->unk48 - 0.05;
            entry->unk48 = decay;
            if (decay <= 0.0f) {
                entry->unk48 = 0.0f;
                arg0->scale.x = arg0->scale.y = arg0->scale.z = base;
                arg0->work[1] = 0;
                arg0->work[0] = 1;
                if (D_80105554_name_81 == 1) {
                    for (i = 0; i < 4; i++) {
                        if (D_800CDBD0_main[i].unk28 != -1) {
                            break;
                        }
                    }
                    if (i == 4) {
                        if (GwSystem.current_board_index == 8) {
                            entry->unk28 = HuAudFXPlay(0x10B);
                        } else {
                            entry->unk28 = HuAudFXPlay(0x100);
                        }
                        return;
                    }
                    entry->unk28 = D_800CDBD0_main[i].unk28;
                } else if ((entry->unk2A == 0) && (D_80105554_name_81 != 2) && (entry->unk_0A != 2) &&
                           (D_80105555_name_81 != 0)) {
                    if (entry->unk_0A == 1) {
                        entry->unk28 = HuAudFXPlay(0x1D5);
                    } else {
                        entry->unk28 = HuAudFXPlay(0x100);
                    }
                    return;
                }
            }
            break;

        case 1:
            if (HmfPauseF == 0) {
                arg0->trans.y = GwPlayer[arg0->work[3]].player_obj->coords.y + D_80105708_name_81 +
                                (sindf(arg0->work[1] * 2) * 10.0f * base);
                arg0->work[1] = (arg0->work[1] + 5) % 180;
                return;
            }
            break;

        case 2:
            D_800A0A7C_main = entry->unk48;
            func_8001C2FC_main(*arg0->model, 0x22000, 0x20000);
            func_8001D558_main(*arg0->model, entry->unk40, entry->unk44, 2);
            if (HmfPauseF == 0) {
                entry->unk48 += 39.0f;
                entry->unk40 += 0.05f;
                entry->unk44 = ((10.0f - entry->unk44) / 30.0f) + entry->unk44;
                if (entry->unk40 > 1.0f) {
                    func_800DBD88_name_81(arg0->work[3]);
                }
            }
            break;
    }
}

void func_800DA460_name_81(omObjData* arg0) {
    UnkDiceRelated* entry;
    Vec pos;
    Vec2f pos2d;
    u32 roll;

    entry = &D_800CDBD0_main[arg0->work[3]];

    if ((arg0->work[0] == 0) && (HmfPauseF == 0)) {
        arg0->scale.x = (sindf(arg0->rot.x) * arg0->scale.z) + 1.0f;
        arg0->rot.x += 20.0f;
        arg0->scale.z -= 0.15;
        if (arg0->rot.x >= 360.0f) {
            arg0->rot.x -= 360.0f;
        }
        if (arg0->scale.z <= 0.0f) {
            arg0->scale.x = 1.0f;
            arg0->work[0] = 1;
        }
    }

    HuSprScaleSet(entry->sprites[arg0->work[1]], 0, arg0->scale.x / 2.0f, arg0->scale.x / 2.0f);
    HuSprScaleSet(entry->sprites[arg0->work[1]], 1, arg0->scale.x / 2.0f, arg0->scale.x / 2.0f);

    roll = arg0->work[1];
    func_80055140_main(entry->sprites[roll], 0, entry->rollValue[roll] % 10, 0);
    func_800550F4_main(entry->sprites[arg0->work[1]], 0, 1);

    roll = arg0->work[1];
    func_80055140_main(entry->sprites[roll], 1, entry->rollValue[roll] / 10, 0);
    func_800550F4_main(entry->sprites[arg0->work[1]], 1, 1);

    pos.x = GwPlayer[arg0->work[3]].player_obj->coords.x;
    pos.y = GwPlayer[arg0->work[3]].player_obj->coords.y + D_80105708_name_81 + arg0->trans.y;
    pos.z = GwPlayer[arg0->work[3]].player_obj->coords.z;
    MBDCamera3Dto2D(&pos, &pos2d);

    func_80054904_main(entry->sprites[arg0->work[1]], 0, pos2d.x, pos2d.y - 8.0f);

    if ((pos2d.x >= 0.0f) && (pos2d.x <= 320.0f) && (pos2d.y >= 0.0f) && (pos2d.y <= 240.0f)) {
        func_800DC4E4_name_81(arg0->work[3], arg0->work[1], 160, 120 - (s32) (MBDCameraZoomGet() * 24.0f));
    }
}

void func_800DA85C_name_81(omObjData* arg0) {
    UnkDiceRelated* entry;
    Vec pos;
    Vec2f pos2d;
    s8 roll;

    entry = &D_800CDBD0_main[arg0->work[3]];

    if ((arg0->work[0] == 0) && (HmfPauseF == 0)) {
        arg0->scale.x = (sindf(arg0->rot.x) * arg0->scale.z) + 1.0f;
        arg0->rot.x += 20.0f;
        if (arg0->rot.x >= 360.0f) {
            arg0->rot.x -= 360.0f;
        }
        arg0->scale.z -= 0.05;
        if (arg0->scale.z <= 0.0f) {
            arg0->scale.x = 1.0f;
            arg0->work[0] = 1;
        }
    }

    HuSprScaleSet(entry->sprites[entry->rollValueIdx], 0, arg0->scale.x, arg0->scale.x);

    roll = entry->rollValueIdx;
    func_80055140_main(entry->sprites[roll], 0, entry->rollValue[roll], 0);
    func_800550F4_main(entry->sprites[entry->rollValueIdx], 0, 1);

    pos.x = GwPlayer[arg0->work[3]].player_obj->coords.x;
    pos.y = GwPlayer[arg0->work[3]].player_obj->coords.y + D_80105708_name_81 + arg0->trans.y;
    pos.z = GwPlayer[arg0->work[3]].player_obj->coords.z;
    MBDCamera3Dto2D(&pos, &pos2d);

    func_80054904_main(entry->sprites[entry->rollValueIdx], 0, pos2d.x, pos2d.y);
}

void func_800DAAB0_name_81(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < DICE_TOTAL; j++) {
            D_800CDBD0_main[i].rollValue[j] = 0;
            D_800CDBD0_main[i].predecidedRollValue[j] = 0;
        }
    }
}

void func_800DAB1C_name_81(void) {
    UnkDiceRelated* entry;
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        entry = &D_800CDBD0_main[i];
        for (j = 0; j < DICE_TOTAL; j++) {
            entry->sprites[j] = -1;
            entry->predecidedRollValue[j] = 0;
        }
        entry->rollValueIdx = 0;
        entry->unk_16 = -1;
        entry->unk_18 = -1;
        entry->unk_30 = NULL;
        entry->unk_26 = -1;
        entry->unk_14 = -1;
        entry->unk_0C = 0;
        entry->dice = NULL;
        entry->unk_38 = NULL;
        entry->omObj = NULL;
        entry->unk_0B = 0;
        entry->unk28 = -1;
        entry->unk2A = 0;
        entry->unk_09 = -1;
    }
    D_80105554_name_81 = 0;
    D_80105710_name_81 = 1;
    D_80105708_name_81 = 25.0f;
    D_80105555_name_81 = 1;
}

void func_800DABE0_name_81(s32 arg0) {
    UnkDiceRelated* entry;
    void* data;
    s32 i;

    entry = &D_800CDBD0_main[arg0];

    if ((arg0 != 0) && (D_800CDBD0_main[0].unk_14 != -1)) {
        entry->unk_14 = D_800CDBD0_main[0].unk_14;
        D_800CDBD0_main[0].unk_0C++;
    } else {
        data = DataRead(0x13020D);
        entry->unk_14 = func_80055810_main(data);
        entry->unk_0C = 1;
        DataClose(data);
    }

    entry->sprites[entry->rollValueIdx] = HuSprGrpCreate(2, 5);

    for (i = 0; i < 2; i++) {
        func_80055024_main(entry->sprites[entry->rollValueIdx], i, entry->unk_14, 0);
        HuSprPriSet(entry->sprites[entry->rollValueIdx], i, 0x4000);
        HuSprAttrSet(entry->sprites[entry->rollValueIdx], i, 0x9000);
        func_800550B4_main(entry->sprites[entry->rollValueIdx], i, 0.0f);
        HuSprScaleSet(entry->sprites[entry->rollValueIdx], i, 0.0f, 0.0f);
        func_80055140_main(entry->sprites[entry->rollValueIdx], i, 0, 0);
        func_800550F4_main(entry->sprites[entry->rollValueIdx], i, 1);
    }

    entry->unk_0B = 1;
}

void func_800DADA0_name_81(s32 arg0) {
    UnkDiceRelated* entry;
    omObjData* obj;
    Vec pos;
    Vec2f pos2d;
    s8 roll;

    entry = &D_800CDBD0_main[arg0];

    if (entry->rollValue[entry->rollValueIdx] != 0) {
        if ((entry->dice == NULL) || (entry->dice->work[0] == 2)) {
            pos.x = GwPlayer[arg0].player_obj->coords.x;
            pos.y = GwPlayer[arg0].player_obj->coords.y + D_80105708_name_81;
            pos.z = GwPlayer[arg0].player_obj->coords.z;
            MBDCamera3Dto2D(&pos, &pos2d);

            if (entry->sprites[entry->rollValueIdx] == -1) {
                func_800DABE0_name_81(arg0);
                entry->unk_0B = 0;
            } else {
                roll = entry->rollValueIdx;
                func_80055140_main(entry->sprites[roll], 0, entry->rollValue[roll], 0);
                HuSprPriSet(entry->sprites[entry->rollValueIdx], 0, 0x4000);
                func_800550F4_main(entry->sprites[entry->rollValueIdx], 0, 1);
            }

            if ((func_800FC114_name_81() == 0) && (D_80105554_name_81 == 0)) {
                func_800DC4E4_name_81(arg0, entry->rollValueIdx, pos2d.x, pos2d.y - 8.0f);
            } else {
                func_80054904_main(entry->sprites[entry->rollValueIdx], 0, pos2d.x, pos2d.y);
            }

            if ((pos2d.x >= 0.0f) && (pos2d.x <= 320.0f) && (pos2d.y >= 0.0f) && (pos2d.y <= 240.0f)) {
                func_80054904_main(entry->sprites[entry->rollValueIdx], 0, 160,
                                   120 - (s32) (MBDCameraZoomGet() * 24.0f));
            }

            HuSprAttrReset(entry->sprites[entry->rollValueIdx], 0, 0x8000);

            if (entry->omObj == NULL) {
                if ((func_800FC114_name_81() == 0) && (D_80105554_name_81 == 0)) {
                    obj = omAddObj(-0x8000, 0, 0, -1, func_800DA460_name_81);
                    entry->omObj = obj;
                    obj->scale.z = 3.0f;
                    obj->work[1] = entry->rollValueIdx;
                } else {
                    obj = omAddObj(-0x8000, 0, 0, -1, func_800DA85C_name_81);
                    entry->omObj = obj;
                    obj->scale.z = 1.0f;
                }
                obj->work[0] = 0;
                obj->work[3] = arg0;
                obj->scale.x = 0.0f;
                obj->rot.x = 270.0f;
                obj->trans.y = 0.0f;
            }
        }
    }
}

void func_800DB148_name_81(s32 arg0) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];
    s32 i;

    if (entry->unk_0B == 0) {
        if (entry->rollValueIdx == 0) {
            func_800DB3E0_name_81(arg0);
        }
    }

    entry->unk_0B = 0;

    if (D_80105554_name_81 == 1) {
        do {
            if (entry->predecidedRollValue[entry->rollValueIdx] != 0) {
                entry->rollValue[entry->rollValueIdx] = entry->predecidedRollValue[entry->rollValueIdx];
                entry->predecidedRollValue[entry->rollValueIdx] = 0;
            } else {
                entry->rollValue[entry->rollValueIdx] = (rand8() % 10) + 1;
            }

            for (i = 0; i < 5; i++) {
                if (i == arg0) {
                    continue;
                }
                if (D_800CDBD0_main[i].rollValue[D_800CDBD0_main[i].rollValueIdx] ==
                    entry->rollValue[entry->rollValueIdx]) {
                    break;
                }
            }
        } while (i != 5);
    } else {
        switch (entry->unk_0A) {
            case 0:
            case 1:
                if (entry->predecidedRollValue[entry->rollValueIdx] != 0) {
                    entry->rollValue[entry->rollValueIdx] = entry->predecidedRollValue[entry->rollValueIdx];
                    entry->predecidedRollValue[entry->rollValueIdx] = 0;
                } else {
                    entry->rollValue[entry->rollValueIdx] = (rand8() % 10) + 1;
                }
                break;

            case 2:
                if (entry->predecidedRollValue[entry->rollValueIdx] != 0) {
                    entry->rollValue[entry->rollValueIdx] = entry->predecidedRollValue[entry->rollValueIdx];
                    entry->predecidedRollValue[entry->rollValueIdx] = 0;
                } else {
                    entry->rollValue[entry->rollValueIdx] = (rand8() % 3) + 1;
                }
                break;
        }
    }

    func_800DADA0_name_81(arg0);
}

void func_800DB38C_name_81(s32 arg0) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];

    if (entry->omObj != NULL) {
        omDelObj(entry->omObj);
        entry->omObj = NULL;
    }
}

s32 func_800DB3E0_name_81(s32 arg0) {
    s32 count = 0;
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];
    s32 i;

    for (i = 0; i < DICE_TOTAL; i++) {
        if (entry->sprites[i] != -1) {
            count++;
            HuSprGrpKill(entry->sprites[i]);
            entry->sprites[i] = -1;
        }
    }

    if (entry->unk_14 != -1) {
        if (entry->unk_0C != 0) {
            entry->unk_0C--;
            if (entry->unk_0C == 0) {
                HuSprKill(entry->unk_14);
                entry->unk_14 = -1;
            }
        }
        count++;
    }

    if (entry->omObj != NULL) {
        omDelObj(entry->omObj);
        entry->omObj = NULL;
        count++;
    }

    return count;
}

void func_800DB4DC_name_81(s32 arg0) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];

    entry->rollValue[entry->rollValueIdx]--;
    if (entry->rollValue[entry->rollValueIdx] <= 0) {
        func_800DB3E0_name_81(arg0);
    }
}

void func_800DB544_name_81(s32 arg0) {
    if (D_800CDBD0_main[arg0].unk_16 != -1) {
        func_8001C258_main(D_800CDBD0_main[arg0].unk_16, 4, 4);
    }
}

void func_800DB58C_name_81(s32 arg0) {
    D_80105555_name_81 = 0;
    func_800DB544_name_81(arg0);
}

void func_800DB5AC_name_81(s32 arg0) {
    if (D_80105555_name_81 != 0) {
        if (D_800CDBD0_main[arg0].unk_16 != -1) {
            func_8001C258_main(D_800CDBD0_main[arg0].unk_16, 4, 0);
        }
    }
}

void func_800DB600_name_81(s32 arg0) {
    D_80105555_name_81 = 1;
    func_800DB5AC_name_81(arg0);
}

void func_800DB624_name_81(s32 arg0, s8 arg1) {
    D_800CDBD0_main[arg0].unk_09 = arg1;
}

s16 func_800DB648_name_81(s32 arg0) {
    UnkDiceRelated* entry;
    omObjData* dice;
    s32 rot;
    s32 tile;
    s32 i;
    s16 ret;

    entry = &D_800CDBD0_main[arg0];

    if (entry->unk_16 != -1) {
        return -1;
    }

    if (entry->rollValueIdx == 0) {
        func_800DB3E0_name_81(arg0);
    }

    if (entry->unk_09 != -1) {
        entry->unk_0A = entry->unk_09;
        entry->unk_09 = -1;
    } else {
        entry->unk_0A = 0;
    }

    entry->unk_16 = Hu3DModelCreate(DataRead(D_80100E24_name_81[entry->unk_0A]), 0x6A9);
    func_8001C8A8_main(entry->unk_16, 1);
    Hu3DModelScaleSet(entry->unk_16, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(entry->unk_16, 0x20000, 0x20000);

    entry->unk_2C = DataRead(D_80100E30_name_81[entry->unk_0A]);
    entry->unk_1A[0] = HmfAnimCreate(HmfModelData[entry->unk_16].hmf, entry->unk_2C, 0, "tile01_DEF");
    entry->unk_1A[1] = func_80032694_main(HmfModelData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile02_DEF");
    entry->unk_1A[2] = func_80032694_main(HmfModelData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile03_DEF");
    entry->unk_1A[3] = func_80032694_main(HmfModelData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile04_DEF");
    entry->unk_1A[4] = func_80032694_main(HmfModelData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile06_DEF");
    entry->unk_1A[5] = func_80032694_main(HmfModelData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile10_DEF");

    tile = rand8() % 10;
    rot = rand8() & 3;
    for (i = 0; i < 6; i++) {
        if (entry->unk_0A < 2) {
            if (entry->unk_0A >= 0) {
                func_80032FF8_main(entry->unk_1A[i], rot);
            }
        }
        func_8003302C_main(entry->unk_1A[i], tile);
    }

    func_8001C448_main(entry->unk_16);
    func_8001C954_main(entry->unk_16);

    dice = omAddObj(-0x8000, 1, 1, -1, func_800DA00C_name_81);
    entry->dice = dice;
    *dice->model = entry->unk_16;
    omSetStatBit(dice, 0xA0);

    dice->trans.x = GwPlayer[arg0].player_obj->coords.x;
    dice->trans.y = GwPlayer[arg0].player_obj->coords.y + D_80105708_name_81;
    dice->trans.z = GwPlayer[arg0].player_obj->coords.z;
    dice->rot.y = -90.0f;
    dice->scale.z = dice->scale.y = dice->scale.x = dice->rot.x = dice->rot.z = 0.0f;
    dice->work[0] = 0;
    dice->work[1] = 0x87;
    dice->work[2] = 0;
    dice->work[3] = arg0;

    entry->unk48 = 1.0f;
    entry->unk40 = 0.0f;
    entry->unk44 = 1.0f;

    D_80105554_name_81 = 0;
    ret = -1;
    switch (entry->unk_0A) {
        case 0:
            if (D_80105554_name_81 != 2) {
                ret = HuAudFXPlay(0x102);
            } else {
                HuAudFXPlay(0x10E);
            }
            break;
        case 1:
            HuAudFXPlay(0x102);
            break;
        case 2:
            HuAudFXPlay(0x111);
            break;
        default:
            HuAudFXPlay(0x10E);
            break;
    }
    return ret;
}

void func_800DBAB0_name_81(s32 arg0, s32 arg1, s32 arg2, char* arg3[]) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];
    omObjData* dice;
    s32 i;

    if (entry->unk_16 == -1) {
        if (D_80105554_name_81 == 1) {
            D_80105708_name_81 = 250.0f;
        } else {
            D_80105708_name_81 = 25.0f;
        }

        func_800DB3E0_name_81(arg0);
        entry->unk_0A = 0;

        entry->unk_16 = Hu3DModelCreate(DataRead(arg1), 0x6A9);
        func_8001C8A8_main(entry->unk_16, 1);
        Hu3DModelScaleSet(entry->unk_16, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(entry->unk_16, 0x20000, 0x20000);

        if (arg2 != -1) {
            entry->unk_2C = DataRead(arg2);
        } else {
            entry->unk_2C = NULL;
        }

        for (i = 0; i < 6; i++) {
            if (arg3[i] != 0) {
                if (i == 0) {
                    entry->unk_1A[0] = HmfAnimCreate(HmfModelData[entry->unk_16].hmf, entry->unk_2C, 0, arg3[0]);
                } else {
                    entry->unk_1A[1] =
                        func_80032694_main(HmfModelData[entry->unk_16].hmf, entry->unk_1A[0], 0, arg3[i]);
                }
            } else {
                entry->unk_1A[i] = -1;
            }
        }

        func_8001C448_main(entry->unk_16);
        func_8001C954_main(entry->unk_16);

        dice = omAddObj(-0x8000, 1, 1, -1, func_800DA00C_name_81);
        entry->dice = dice;
        dice->model[0] = entry->unk_16;
        omSetStatBit(dice, 0xA0);
        dice->trans.x = GwPlayer[arg0].player_obj->coords.x;
        dice->trans.y = GwPlayer[arg0].player_obj->coords.y + D_80105708_name_81;
        dice->trans.z = GwPlayer[arg0].player_obj->coords.z;
        dice->rot.y = -90.0f;
        dice->scale.z = dice->scale.y = dice->scale.x = dice->rot.x = dice->rot.z = 0.0f;
        dice->work[0] = 0;
        dice->work[1] = 0x87;
        dice->work[2] = 0;
        dice->work[3] = arg0;

        entry->unk48 = 1.0f;
        entry->unk40 = 0.0f;
        entry->unk44 = 1.0f;

        HuAudFXPlay(0x10E);
    }
}

void func_800DBD88_name_81(s32 arg0) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];
    s32 i;

    if (entry->unk_16 != -1) {
        func_8001ACDC_main(entry->unk_16);
        for (i = 0; i < 6; i++) {
            if (entry->unk_1A[i] != -1) {
                func_80033430_main(entry->unk_1A[i]);
            }
        }
        if (entry->unk_2C != NULL) {
            DataClose(entry->unk_2C);
        }
        omDelObj(entry->dice);
        entry->dice = NULL;
        entry->unk_16 = -1;
    }

    if (entry->unk_18 != -1) {
        func_8001ACDC_main(entry->unk_18);
        entry->unk_18 = -1;
        if (entry->unk_38 != NULL) {
            omDelObj(entry->unk_38);
            entry->unk_38 = NULL;
        }
    }

    if (entry->unk_26 != -1) {
        func_80033430_main(entry->unk_26);
        entry->unk_26 = -1;
    }

    if (entry->unk_30 != NULL) {
        DataClose(entry->unk_30);
        entry->unk_30 = NULL;
    }
}

void func_800DBEB0_name_81(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        func_800DBD88_name_81(i);
        func_800DB3E0_name_81(i);
    }
}

void func_800DBEF0_name_81(s32 arg0) {
    UnkDiceRelated* entry;
    s32 count;
    s32 i;

    entry = &D_800CDBD0_main[arg0];

    if (entry->unk_16 != -1) {
        entry->dice->work[0] = 2;

        if (D_80105554_name_81 != 2) {
            func_800DB148_name_81(arg0);
        }

        if (D_80105554_name_81 == 1) {
            count = 0;
            for (i = 0; i < 4; i++) {
                if (D_800CDBD0_main[i].unk28 != -1) {
                    count++;
                }
            }
        } else {
            count = 1;
        }

        if (count == 1) {
            HuAudFXStop(entry->unk28);
        }
        entry->unk28 = -1;
        entry->unk2A = 0;

        if (D_80105554_name_81 == 2) {
            HuAudFXPlay(0x10D);
        } else {
            HuAudFXPlay(0x103);
        }
    }
}

void func_800DBFF8_name_81(void) {
    D_80105554_name_81 = 1;
    D_80105708_name_81 = 250.0f;
}

s32 func_800DC018_name_81(s32 arg0) {
    if (~D_800CDBD0_main[arg0].unk_16) {
        return 1;
    } else {
        return 0;
    }
}

void func_800DC044_name_81(s32 arg0, s8 arg1) {
    D_800CDBD0_main[arg0].rollValue[D_800CDBD0_main[arg0].rollValueIdx] = arg1;
}

void func_800DC07C_name_81(s32 arg0, s8 arg1) {
    D_800CDBD0_main[arg0].predecidedRollValue[D_800CDBD0_main[arg0].rollValueIdx] = arg1;
}

s32 func_800DC0B4_name_81(s32 arg0) {
    return D_800CDBD0_main[arg0].rollValue[D_800CDBD0_main[arg0].rollValueIdx];
}

void func_800DC0EC_name_81(void) {
    DuelDiceProc* work = HuPrcCurrentGet()->user_data;
    s32 timer = 0;

    while (1) {
        switch (work->state) {
            case 0:
                D_80105710_name_81 = 0;
                func_800DB648_name_81(work->playerNo);
                D_80105710_name_81 = 1;
                work->state++;
                HuPrcSleep(20);
                break;
            case 1:
                if (((GwPlayer[work->playerNo].stat & 1) || (D_800D5558_main[GwPlayer[work->playerNo].pad] & 0x8000)) &&
                    !(HmfModelData[D_800CDBD0_main[work->playerNo].unk_16].unk18 & 4) && (GWBoardFlagCheck(0x11) == 0) &&
                    (D_80100E20_name_81 == 0)) {
                    work->state++;
                    func_800F3880_name_81(work->playerNo, 1, 0);
                    func_800EF7C8_name_81(GwPlayer[work->playerNo].player_obj, 2.0f, -0.3f);
                    mbCameraBtnF = 0;
                    D_800D51F8_main = 0;
                }
                break;
            case 2:
                if (++timer >= 5) {
                    func_800DBEF0_name_81(work->playerNo);
                    func_800F397C_name_81(work->playerNo, -1, 0, 10, 2);
                    work->state++;
                }
                break;
            case 3:
                HuPrcSleep(20);
                omDelPrcObj(NULL);
                break;
        }
        HuPrcVSleep();
    }
}

Process* func_800DC324_name_81(s32 arg0) {
    Process* process = omAddPrcObj(func_800DC0EC_name_81, 0, 0, 0x40);
    DuelDiceProc* work = HuMemMemoryAlloc(process->heap, sizeof(DuelDiceProc));

    process->user_data = work;
    work->playerNo = arg0;
    work->state = 0;
    return process;
}

u8 func_800DC384_name_81(void) {
    return D_8010562C_name_81;
}

void func_800DC390_name_81(void) {
    D_8010562C_name_81 = 1;
}

void func_800DC3A0_name_81(void) {
    D_8010562C_name_81 = 0;
}

void func_800DC3AC_name_81(s32 arg0) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];

    if (entry->unk28 != -1) {
        HuAudFXStop(entry->unk28);
        entry->unk28 = -1;
    }
    entry->unk2A = 1;
}

void func_800DC410_name_81(s32 arg0) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];

    if ((entry->unk2A == 1) && (entry->unk_16 != -1)) {
        if ((entry->dice != NULL) && (entry->dice->work[0] != 2) && (D_80105554_name_81 != 2)) {
            if (entry->unk_0A == 1) {
                entry->unk28 = HuAudFXPlay(0x1D5);
            } else {
                entry->unk28 = HuAudFXPlay(0x100);
            }
        }
    }
    entry->unk2A = 0;
}

void func_800DC4B4_name_81(s32 arg0) {
    D_80105554_name_81 = arg0;
}

void func_800DC4C0_name_81(s32 arg0, s8 arg1) {
    D_800CDBD0_main[arg0].rollValueIdx = arg1;
}

void func_800DC4E4_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];

    if (entry->rollValue[arg1] >= 10) {
        HuSprAttrReset(entry->sprites[arg1], 1, 0x8000);
        func_80054904_main(entry->sprites[arg1], 0, arg2 + 10, arg3);
        func_80054904_main(entry->sprites[arg1], 1, -0x1C, 0);
    } else {
        HuSprAttrSet(entry->sprites[arg1], 1, 0x8000);
        func_80054904_main(entry->sprites[arg1], 0, arg2, arg3);
    }
}

void func_800DC5CC_name_81(s32 arg0) {
    UnkDiceRelated* entry = &D_800CDBD0_main[arg0];

    if (entry->dice != NULL) {
        entry->dice->trans.x = GwPlayer[arg0].player_obj->coords.x;
        entry->dice->trans.y = GwPlayer[arg0].player_obj->coords.y + D_80105708_name_81;
        entry->dice->trans.z = GwPlayer[arg0].player_obj->coords.z;
    }
}
