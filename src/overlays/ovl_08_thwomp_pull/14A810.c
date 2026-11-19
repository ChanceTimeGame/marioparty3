#include "common.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/hmfman.h"
#include "game/object.h"

/* main */
void func_8001C258_main(s16 arg0, s32 arg1, s32 arg2);
void func_8001C5B4_main(s16, s16);
void func_8001C624_main(s16, s16, s16, s16, s16);
void func_8001C6A8_main(s32 model, f32 arg1);
void func_80016FB4_main(s16 model, void* motion, s16 frame);
void* func_8001D33C_main(s16 model, char* name);
void func_8001EF6C_main(s16 arg0, s16 arg1, char* arg2);
void func_8001F9E4_main(s16, u8);
void func_8004AAD0_main(s16, s8);
void omVibrate(s16 player, s16 duration, s16 off, s16 on);
u8 rand8(void);
f32 sindf(f32 angle);
f32 cosdf(f32 angle);
f32 atan2df(f32 y, f32 x);
f32 HuSqrtf(f32 x);

/* What func_8001D33C_main returns (a model's named object). */
typedef struct TpHmfObj {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ Vec pos;
    /* 0x10 */ char unk10[0xC];
    /* 0x1C */ Vec scale;
    /* 0x28 */ char unk28[0x24];
    /* 0x4C */ u8 unk4C;
} TpHmfObj;

/* One player of the minigame (D_8010F4B8_thwomp_pull[4]); slot 0 is the solo team. */
typedef struct TpPlayer {
    /* 0x00 */ s8 player; /* GwPlayer index */
    /* 0x01 */ u8 slot;
    /* 0x02 */ s8 pad;
    /* 0x03 */ s8 chr;
    /* 0x04 */ s8 cpu; /* cpu difficulty, -1 human */
    /* 0x05 */ char unk05[0xB];
} TpPlayer; // Size 0x10

/* .data */
extern u32 D_8010EE24_thwomp_pull;      /* frame counter */
extern f32 D_8010EE28_thwomp_pull[2];   /* team distance pulled (negative) */
extern u8 D_8010EE30_thwomp_pull[2];
extern u8 D_8010EE34_thwomp_pull[2][3]; /* inner labels D_8010EE35/36 */
extern u16 D_8010EE3C_thwomp_pull[2];
extern u8 D_8010EE40_thwomp_pull[2];
extern u8 D_8010EE44_thwomp_pull[2];
extern u8 D_8010EE48_thwomp_pull[2][3]; /* inner labels D_8010EE49/4A */
extern u8 D_8010EE50_thwomp_pull[2];
extern f32 D_8010EE54_thwomp_pull[2][2];
extern u8 D_8010EE64_thwomp_pull[2][2];
extern f32 D_8010EE68_thwomp_pull[2][4]; /* inner label D_8010EE74 */
extern f32 D_8010EE88_thwomp_pull[2][4]; /* inner label D_8010EE94 */
extern f32 D_8010EEA8_thwomp_pull[2][4]; /* inner label D_8010EEB4 */
extern f32 D_8010EEC8_thwomp_pull[2][4];
extern f32 D_8010EEE8_thwomp_pull[2][4];
extern f32 D_8010EF08_thwomp_pull[2][4];
extern u8 D_8010EF28_thwomp_pull[2];
extern f32 D_8010EF2C_thwomp_pull[2];
extern u8 D_8010EF34_thwomp_pull[2];
extern s8 D_8010EF38_thwomp_pull[4];
extern u8 D_8010EF3C_thwomp_pull[4];
extern u8 D_8010EF40_thwomp_pull[4];
extern u8 D_8010EF44_thwomp_pull[4];
extern u16 D_8010EF48_thwomp_pull[2];
extern u8 D_8010EF4C_thwomp_pull[2][3];
extern f32 D_8010EF54_thwomp_pull[2][3];
extern u8 D_8010EF6C_thwomp_pull[2];
extern f32 D_8010EF70_thwomp_pull[24];

/* .bss */
extern TpPlayer D_8010F4B8_thwomp_pull[4];
extern TpPlayer* D_8010F4F8_thwomp_pull[4]; /* by slot; inner labels D_8010F4FC/500/504 */
extern f32 D_8010F510_thwomp_pull[4];
extern f32 D_8010F520_thwomp_pull[2];
extern void* D_8010F528_thwomp_pull;
extern s16 D_8010F530_thwomp_pull;
extern f32 D_8010F540_thwomp_pull[4];
extern u8 D_8010F564_thwomp_pull[2];
extern s8 D_8010F566_thwomp_pull;
extern omObjData* D_8010F568_thwomp_pull[2]; /* inner label D_8010F56C */
extern f32 D_8010F578_thwomp_pull[4];
extern f32 D_8010F588_thwomp_pull;
extern s32 D_8010F5A4_thwomp_pull;
extern void* D_8010F5AC_thwomp_pull;
extern void* D_8010F5B0_thwomp_pull;

void func_801097AC_thwomp_pull(omObjData* object, s8 team);
void func_8010AF18_thwomp_pull(s16 model, s16 frame);
void func_8010AF88_thwomp_pull(omObjData* object);

#define TP_DEC(x) ((x) = ((x) != 0) ? (x) - 1 : 0)
#define TP_INC(x) ((x) = ((x) != 0) ? (x) + 1 : 0)

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_801059A0_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80105D3C_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010EFD0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F008_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F018_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F028_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80105F14_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80106D5C_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F080_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80106E78_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80107FF4_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_801089B4_thwomp_pull);

void func_8010974C_thwomp_pull(omObjData* object) {
    func_801097AC_thwomp_pull(object, 0);
    object->func = func_8010AF88_thwomp_pull;
}

void func_80109780_thwomp_pull(omObjData* object) {
    func_801097AC_thwomp_pull(object, 1);
    object->func = NULL;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F140_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F150_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F170_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F190_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F1B0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F1F0_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_801097AC_thwomp_pull);

/* Sets a model's animation frame (and its motion's current frame, an f32 in an s32 field). */
void func_8010AF18_thwomp_pull(s16 model, s16 frame) {
    HmfModel* m = &HmfModelData[model];
    f32 f = frame;

    func_8001C6A8_main(model, f);
    *(f32*)&m->hmf->unk98->unk08 = f;
}

#ifdef NON_MATCHING
void func_8010AF88_thwomp_pull(omObjData* object) {
    s32 hit[4][3];
    s32 btn[3] = { 0x8000, 0x4000, 0x2000 };
    s16 cpuTbl[5][4] = {
        { 17, 15, 13, 14 },
        { 5, 3, 2, 1 },
        { 1006, 1012, 1030, 1024 },
        { 12, 12, 8, 2 },
        { 5, 5, 6, 1 },
    };
    u8 shown[3];
    omObjData* obj;
    HmfModel* m;
    TpHmfObj* part;
    s32 team;
    s32 i;
    s32 p;
    s32 k;
    s32 kind;
    s32 isHit;
    s32 v;
    s32 n;
    s32* h;
    s16 se;
    f32 f;
    f32 t;
    f32 a;
    f32 b;
    f32 y;
    f32 rem;
    f64 r;

    if (D_8010EE24_thwomp_pull == 0) {
        for (i = 0; i < 2; i++) {
            D_8010EE48_thwomp_pull[i][0] = rand8() % 3;
            k = (D_8010EE48_thwomp_pull[i][0] + (rand8() & 1) + 1) % 3;
            D_8010EE48_thwomp_pull[i][1] = k;
            D_8010EE48_thwomp_pull[i][2] = 3 - (D_8010EE48_thwomp_pull[i][0] + k);
        }
        for (i = 0; i < 4; i++) {
            D_8010EF38_thwomp_pull[i] = cpuTbl[0][D_8010F4F8_thwomp_pull[i]->cpu] + rand8() % cpuTbl[1][D_8010F4F8_thwomp_pull[i]->cpu];
        }
    }
    D_800CD280_main = (D_8010F530_thwomp_pull < 2 || D_8010F588_thwomp_pull > 0.0f);

    for (team = 0; team < 2; team++) {
        obj = D_8010F568_thwomp_pull[team];
        for (i = 0; i < 3; i++) {
            for (p = team; p < team * 3 + 1; p++) {
                h = &hit[p][i];
                v = 0;
                if (D_8010EF40_thwomp_pull[p] == 0 && D_8010F530_thwomp_pull == 2) {
                    if (D_8010F4F8_thwomp_pull[p]->cpu == -1) {
                        if (D_800D5558_main[D_8010F4F8_thwomp_pull[p]->pad] & btn[i]) {
                            v = 1;
                        }
                    } else if (D_8010EF3C_thwomp_pull[p] != 0 && i == D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]] &&
                               D_8010EE40_thwomp_pull[team] == 1 && D_8010EE3C_thwomp_pull[team] == 18) {
                        v = 1;
                    }
                }
                *h = v;
            }
            shown[i] = ((u32)HmfModelData[obj->model[0x1E + D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]]]].unk18 >> 2) & 1;
            func_8001C258_main(obj->model[0x1E + i], 4, 4);
        }
        D_8010EE3C_thwomp_pull[team]++;
        if (D_8010EE40_thwomp_pull[team] == 1 && D_8010EE3C_thwomp_pull[team] >= 20) {
            D_8010EE40_thwomp_pull[team] = 0;
            D_8010EE3C_thwomp_pull[team] = 0;
        }
        if (D_8010EE40_thwomp_pull[team] == 0 &&
            D_8010EE34_thwomp_pull[team][0] + D_8010EE34_thwomp_pull[team][1] + D_8010EE34_thwomp_pull[team][2] == 0) {
            if (D_8010F530_thwomp_pull == 2) {
                if (*((team != 0) ? &D_8010EF40_thwomp_pull[1 + D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]]] : &D_8010EF40_thwomp_pull[0]) == 0) {
                    if (shown[D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]]] != 0) {
                        HuAudFXPlay((team != 0) ? 0x33F : 0x33E);
                    }
                    func_8001C258_main(obj->model[0x1E + D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]]], 4, 0);
                }
            }
            k = D_8010EE44_thwomp_pull[team];
            p = team + D_8010EE48_thwomp_pull[team][k] * team;
            if (D_8010F4F8_thwomp_pull[p]->cpu == 3) {
                if (k == 2) {
                    if (D_8010EF38_thwomp_pull[p] >= 3) {
                        D_8010EF38_thwomp_pull[p] = (rand8() & 1) + 1;
                    }
                }
            }
            D_8010EF38_thwomp_pull[p] -= (D_8010EF38_thwomp_pull[p] > 0 && D_8010EF40_thwomp_pull[p] == 0 && D_8010F530_thwomp_pull == 2);
            if ((D_8010F4F8_thwomp_pull[p]->cpu == -1) ? (hit[p][D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]]] != 0)
                                                      : (D_8010EF38_thwomp_pull[p] <= 0)) {
                hit[p][D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]]] = 0;
                D_8010EF38_thwomp_pull[p] = cpuTbl[0][D_8010F4F8_thwomp_pull[p]->cpu] + rand8() % cpuTbl[1][D_8010F4F8_thwomp_pull[p]->cpu];
                D_8010EF3C_thwomp_pull[p] = (rand8() % cpuTbl[2][D_8010F4F8_thwomp_pull[p]->cpu]) == 1;
                D_8010EE40_thwomp_pull[team] = 1;
                D_8010EE3C_thwomp_pull[team] = 0;
                D_8010EE30_thwomp_pull[team] = 1;
                D_8010EE50_thwomp_pull[team]++;
                D_8010EE50_thwomp_pull[team] &= 1;
                D_8010EF44_thwomp_pull[p] = 20;
                HuAudFXPlay((team != 0) ? 0x33B : 0x33A);
                D_8010EE44_thwomp_pull[team]++;
                D_8010EE44_thwomp_pull[team] %= 3;
                if (D_8010EE44_thwomp_pull[team] == 0) {
                    D_8010EE48_thwomp_pull[team][0] = rand8() % 3;
                    k = (D_8010EE48_thwomp_pull[team][0] + (rand8() & 1) + 1) % 3;
                    D_8010EE48_thwomp_pull[team][1] = k;
                    D_8010EE48_thwomp_pull[team][2] = 3 - (D_8010EE48_thwomp_pull[team][0] + k);
                }
            }
            if (D_8010EE40_thwomp_pull[team] == 0 && D_8010F530_thwomp_pull == 2) {
                if (*((team != 0) ? &D_8010EF40_thwomp_pull[1 + D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]]] : &D_8010EF40_thwomp_pull[0]) == 0) {
                    if (shown[D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]]] != 0) {
                        HuAudFXPlay((team != 0) ? 0x33F : 0x33E);
                    }
                    func_8001C258_main(obj->model[0x1E + D_8010EE48_thwomp_pull[team][D_8010EE44_thwomp_pull[team]]], 4, 0);
                }
            }
        }
        for (p = team; p < team * 3 + 1; p++) {
            TP_DEC(D_8010EF44_thwomp_pull[p]);
            if (D_8010EF44_thwomp_pull[p] == 19) {
                func_8001C624_main(obj->model[p - (team - 1)], HmfModelData[obj->motion[p - (team - 3)]].unk02, 2, 1, 0);
            }
        }
        if (D_8010EE34_thwomp_pull[team][0] + D_8010EE34_thwomp_pull[team][1] + D_8010EE34_thwomp_pull[team][2] == 0) {
            for (i = 0; i < 3; i++) {
                for (p = team; p < team * 3 + 1; p++) {
                    if (hit[p][i] != 0) {
                        if (team != 0) {
                            D_8010EE34_thwomp_pull[team][p - 1] = 15;
                        } else {
                            D_8010EE34_thwomp_pull[team][i] = 15;
                        }
                        HuAudFXPlay((team != 0) ? 0x339 : 0x338);
                        if (D_8010F4F8_thwomp_pull[p]->cpu != -1) {
                            D_8010EF3C_thwomp_pull[p] = 0;
                            D_8010EF38_thwomp_pull[p] = cpuTbl[3][D_8010F4F8_thwomp_pull[p]->cpu] + rand8() % cpuTbl[4][D_8010F4F8_thwomp_pull[p]->cpu];
                        }
                    }
                }
            }
        }
        f = -D_8010EE28_thwomp_pull[team];
        if (f <= 1500.0f || ((s32)f - 1000) % 3000 < 500) {
            k = ((s32)-D_8010EE28_thwomp_pull[team] - 1000) / 3000;
            if (k == 0) {
                v = 80;
            } else if (D_8010EE28_thwomp_pull[1 - team] < D_8010EE28_thwomp_pull[team]) {
                v = 80;
            } else if (k == 1) {
                v = 17;
            } else {
                v = 7;
            }
            D_8010EF48_thwomp_pull[team] = (v + D_8010EE24_thwomp_pull + (u8)(rand8() % 10) - 5) % 90;
        }
        if (D_8010EE24_thwomp_pull % 90 == D_8010EF48_thwomp_pull[team] && D_8010EF28_thwomp_pull[team] == 0 && D_8010F530_thwomp_pull == 2 &&
            !(HmfModelData[obj->model[0x21]].unk18 & 4)) {
            f = -D_8010EE28_thwomp_pull[team];
            if (f >= 1500.0f && ((s32)f - 1000) % 3000 >= 500 && ((s32)f - 1000) % 3000 <= 2900) {
                D_8010EF34_thwomp_pull[team] = 1;
                D_8010EF28_thwomp_pull[team] = 1;
                func_8001C5B4_main(obj->model[0x21], D_8010F568_thwomp_pull[0]->motion[0x12]);
                func_8001C258_main(obj->model[0x23], 4, 0);
                func_8001C258_main(obj->model[0x23], 0x4000, 0);
                func_8001F9E4_main(obj->model[0x23], 0xFF);
            }
        }
        if (D_8010EF34_thwomp_pull[team] != 0) {
            if (D_8010EF34_thwomp_pull[team] < 16) {
                func_80016FB4_main(obj->model[0x21], D_8010F5AC_thwomp_pull, D_8010EF34_thwomp_pull[team] * 2 - 2);
            }
            if (D_8010EF34_thwomp_pull[team] >= 8 && D_8010EF34_thwomp_pull[team] < 16) {
                t = (D_8010EF34_thwomp_pull[team] - 8) / 8.0;
                if (t > 1.0f) {
                    t = 1.0f;
                }
                a = 1.0f - t;
                a = a * a;
                b = 1.0f - a;
                D_8010EE68_thwomp_pull[team][0] = a * -35.0f - b * 176.0f;
                t = t * t;
                a = 1.0f - t;
                D_8010EE88_thwomp_pull[team][0] = a * 140.0f + t * 190.0f;
                D_8010EEA8_thwomp_pull[team][0] = a * -130.0f;
                f = b * 0.5 + 0.5;
                Hu3DModelScaleSet(obj->model[0x23], f, f, f);
                func_8001F9E4_main(obj->model[0x23], (s32)(b * 191.0f) + 64);
            } else if (D_8010EF34_thwomp_pull[team] < 16) {
                D_8010EE68_thwomp_pull[team][0] = D_8010EE88_thwomp_pull[team][0] = D_8010EEA8_thwomp_pull[team][0] = 0.0f;
                Hu3DModelScaleSet(obj->model[0x23], 0.0f, 0.0f, 0.0f);
                func_8001F9E4_main(obj->model[0x23], 16);
            }
            if (D_8010EF34_thwomp_pull[team] == 16) {
                func_8001C5B4_main(obj->model[0x21], D_8010F568_thwomp_pull[0]->motion[0x13]);
                func_8001C258_main(obj->model[0x23], 4, 0);
                func_8001EF6C_main(obj->model[0x23], obj->model[0x21], "srowman-item_fook");
                func_8001C258_main(obj->model[0x23], 0x4000, 0x4000);
                func_8001F9E4_main(obj->model[0x23], 0xFF);
            }
            if (D_8010EF34_thwomp_pull[team] >= 16 && D_8010EF34_thwomp_pull[team] < 46) {
                func_80016FB4_main(obj->model[0x21], D_8010F5B0_thwomp_pull, (D_8010EF34_thwomp_pull[team] - 16) * 2);
            }
            if (D_8010EF34_thwomp_pull[team] < 26) {
                part = func_8001D33C_main(obj->model[0x21], "srowman-item_fook");
                part->scale.x = 0.25f;
                part->scale.y = 0.25f;
                part->scale.z = 0.25f;
                part->pos.x = 300.0f;
                part->pos.y = 150.0f;
                part->pos.z = 150.0f;
                part->unk4C = 0;
            }
            if (D_8010EF34_thwomp_pull[team] == 26) {
                D_8010EF28_thwomp_pull[team] = 2;
                func_8001C258_main(obj->model[0x23], 0x4000, 0);
                func_8001C258_main(obj->model[0x23], 4, 4);
                func_8001C258_main(obj->model[0x22], 4, 0);
                func_8001C258_main(obj->model[0x26], 4, 0);
                D_8010EE68_thwomp_pull[team][0] = HmfModelData[obj->model[0x21]].pos.x + -105.0f;
                D_8010EE88_thwomp_pull[team][0] = HmfModelData[obj->model[0x21]].pos.y + 219.0f;
                D_8010EEA8_thwomp_pull[team][0] = HmfModelData[obj->model[0x21]].pos.z + -18.0f + D_8010EE28_thwomp_pull[team];
                D_8010EEC8_thwomp_pull[team][0] = 20.0f;
                D_8010EEE8_thwomp_pull[team][0] = 50.0f;
                D_8010EF08_thwomp_pull[team][0] = 0.0f;
            }
            if (D_8010EF34_thwomp_pull[team] >= 27 && D_8010EF34_thwomp_pull[team] < 76) {
                for (i = 0; i < ((D_8010EF28_thwomp_pull[team] == 3) ? 3 : 1); i++) {
                    if (D_8010EE88_thwomp_pull[team][i] > 0.0f) {
                        D_8010EE68_thwomp_pull[team][i] += D_8010EEC8_thwomp_pull[team][i];
                        D_8010EE88_thwomp_pull[team][i] += D_8010EEE8_thwomp_pull[team][i];
                        D_8010EEA8_thwomp_pull[team][i] += D_8010EF08_thwomp_pull[team][i];
                        D_8010EEE8_thwomp_pull[team][i] -= (D_8010EF28_thwomp_pull[team] == 3) ? 0.0f : 4.0f;
                    } else {
                        D_8010EE88_thwomp_pull[team][i] = 0.0f;
                    }
                }
                if (D_8010EF28_thwomp_pull[team] == 2) {
                    n = D_8010EEA8_thwomp_pull[team][0] - D_8010EE28_thwomp_pull[team];
                    if (n >= -549 && n <= -251) {
                        kind = 1;
                        isHit = D_8010EE88_thwomp_pull[team][0] <= HmfModelData[obj->model[5]].pos.y + 90.0f + (f32)(team * 55);
                    } else if (n >= -249 && n <= 99) {
                        kind = 2;
                        isHit = D_8010EE88_thwomp_pull[team][0] <= 100.0f;
                    } else {
                        kind = 0;
                        isHit = D_8010EE88_thwomp_pull[team][0] <= 0.0f;
                    }
                    if (isHit) {
                        D_8010EF28_thwomp_pull[team] = 3;
                        if (kind == 2) {
                            HuAudFXPlay((team != 0) ? 0x33D : 0x33C);
                        } else {
                            se = HuAudFXPlay((team != 0) ? 0x33D : 0x33C);
                            if (se != -1) {
                                f = (D_8010EEA8_thwomp_pull[team][0] - D_8010EE28_thwomp_pull[team]) - 200.0f;
                                f = (f > 0.0f) ? 0.0f : f / 2000.0 * 26.0;
                                func_8004AAD0_main(se, (s32)f + 127);
                            }
                        }
                        func_8001C258_main(obj->model[0x22], 4, 4);
                        func_8001C258_main(obj->model[0x26], 4, 4);
                        D_8010EE68_thwomp_pull[team][3] = D_8010EE68_thwomp_pull[team][0];
                        D_8010EE88_thwomp_pull[team][3] = D_8010EE88_thwomp_pull[team][0];
                        D_8010EEA8_thwomp_pull[team][3] = D_8010EEA8_thwomp_pull[team][0];
                        if (kind == 2) {
                            D_8010EEA8_thwomp_pull[team][0] = (D_8010EEA8_thwomp_pull[team][0] < D_8010EE28_thwomp_pull[team] + 35.0f)
                                                                  ? D_8010EE28_thwomp_pull[team] + 35.0f
                                                                  : D_8010EEA8_thwomp_pull[team][0];
                        }
                        if (kind == 2 && D_8010F530_thwomp_pull == 2) {
                            for (i = 0; i < team * 2 + 1; i++) {
                                D_8010EF40_thwomp_pull[team + i] = 31;
                                func_8001C624_main(obj->model[1 + i], HmfModelData[obj->motion[6 + i]].unk02, 0, 14, 0);
                                omVibrate(D_8010F4F8_thwomp_pull[team + i]->player, 20, 0, 20);
                            }
                        }
                        k = rand8() / 255.0 * 360.0;
                        for (i = 0; i < 1; i++) {
                            D_8010EF2C_thwomp_pull[team] = 0.0f;
                            f = k + i * 120 + ((u8)(rand8() / 3) - 42);
                            D_8010EEC8_thwomp_pull[team][i] = sindf(f) * 20.0f;
                            D_8010EF08_thwomp_pull[team][i] = cosdf(f) * 20.0f;
                            D_8010EEE8_thwomp_pull[team][i] = rand8() / 255.0 * 30.0 + 20.0;
                            D_8010EEC8_thwomp_pull[team][i] = D_8010EEE8_thwomp_pull[team][i] = D_8010EF08_thwomp_pull[team][i] = 0.0f;
                            D_8010EE68_thwomp_pull[team][i] = D_8010EE68_thwomp_pull[team][0] + 0.0f;
                            D_8010EE88_thwomp_pull[team][i] = 2.0f * D_8010EEE8_thwomp_pull[team][i] + D_8010EE88_thwomp_pull[team][0];
                            D_8010EEA8_thwomp_pull[team][i] = 2.0f * D_8010EF08_thwomp_pull[team][i] + D_8010EEA8_thwomp_pull[team][0];
                            func_8001C258_main(obj->model[0x22], 4, 4);
                            func_8001C258_main(obj->model[0x23], 4, 4);
                            func_8001C258_main(obj->model[0x24], 4, 0);
                            Hu3DModelPosSet(obj->model[0x24], D_8010EE68_thwomp_pull[team][0], D_8010EE88_thwomp_pull[team][0] + 100.0f,
                                            D_8010EEA8_thwomp_pull[team][0] - D_8010EE28_thwomp_pull[team]);
                            Hu3DModelRotSet(obj->model[0x24], 0.0f, rand8() / 256.0 * 360.0, 0.0f);
                            func_8010AF18_thwomp_pull(obj->model[0x24], 4);
                            D_8010EF6C_thwomp_pull[team] = 20;
                        }
                    }
                }
            }
            if (D_8010EF34_thwomp_pull[team] == 76) {
                D_8010EF34_thwomp_pull[team] = 0;
                D_8010EF28_thwomp_pull[team] = 0;
                func_8001C258_main(obj->model[0x22], 4, 4);
                func_8001C258_main(obj->model[0x23], 4, 4);
            }
            if (D_8010EF28_thwomp_pull[team] >= 2 && (D_8010EEA8_thwomp_pull[team][0] - D_8010EE28_thwomp_pull[team]) + 35.0f >= 378.0f) {
                D_8010EF34_thwomp_pull[team] = 0;
                D_8010EF28_thwomp_pull[team] = 0;
                func_8001C258_main(obj->model[0x22], 4, 4);
                func_8001C258_main(obj->model[0x23], 4, 4);
                func_8001C258_main(obj->model[0x26], 4, 4);
                func_8001C258_main(obj->model[0x24], 4, 4);
            }
            TP_INC(D_8010EF34_thwomp_pull[team]);
        }
        TP_INC(D_8010EF6C_thwomp_pull[team]);
        func_8001C258_main(obj->model[0x24], 4, (D_8010EF6C_thwomp_pull[team] == 0) * 4);
        TP_INC(D_8010EE30_thwomp_pull[team]);
        if (D_8010EE30_thwomp_pull[team] >= 21) {
            D_8010EE30_thwomp_pull[team] = 0;
            omVibrate(D_8010F4F8_thwomp_pull[team]->player, 10, 0, 10);
            if (team == 1) {
                omVibrate(D_8010F4F8_thwomp_pull[2]->player, 10, 0, 10);
                omVibrate(D_8010F4F8_thwomp_pull[3]->player, 10, 0, 10);
            }
        }
        v = 0;
        if (D_8010EE30_thwomp_pull[team] != 0) {
            v = D_8010EE34_thwomp_pull[team][0] + D_8010EE34_thwomp_pull[team][1] + D_8010EE34_thwomp_pull[team][2] == 0;
        }
        D_8010EE28_thwomp_pull[team] -= (v * 450) / 20.0;
        for (i = 0; i < 3; i++) {
            TP_DEC(D_8010EE34_thwomp_pull[team][i]);
            if (D_8010F530_thwomp_pull == 0) {
                if (team != 0) {
                    f = D_8010F5A4_thwomp_pull - i * 20;
                } else {
                    f = D_8010F5A4_thwomp_pull - (2 - i) * 20;
                }
                t = ((f >= 28.0f) & (f < 34.0f)) ? (f - 28.0f) / 6.0 : 0.0f;
                if (f < 0.0f) {
                    y = 0.0f;
                } else if (f < 20.0f) {
                    y = f / 20.0 * 120.0;
                } else if (f < 28.0f) {
                    y = 120.0f;
                } else if (f < 34.0f) {
                    y = (1.0f - t * t) * 120.0f;
                } else {
                    y = 0.0f;
                }
                if ((HmfModelData[obj->model[4 + i]].pos.y > 0.0f) & (y <= 0.0f)) {
                    D_8010F564_thwomp_pull[team] = 4;
                    HuAudFXPlay((team != 0) ? 0x337 : 0x336);
                    func_8001C258_main(obj->model[0x31 + i], 4, 0);
                    func_8010AF18_thwomp_pull(obj->model[0x31 + i], 6);
                    D_8010EF4C_thwomp_pull[team][i] = 27;
                    D_8010EF54_thwomp_pull[team][i] = D_8010EE28_thwomp_pull[team];
                }
                HmfModelData[obj->model[4 + i]].pos.y = y;
                D_8010EE54_thwomp_pull[team][0] = D_8010EE28_thwomp_pull[team] - 300.0f;
            } else {
                k = D_8010EE30_thwomp_pull[team];
                if (D_8010EF70_thwomp_pull[k] == 0.0f && (D_8010EE30_thwomp_pull[team] != 0) & (D_8010EE30_thwomp_pull[team] < 20)) {
                    D_8010EF70_thwomp_pull[D_8010EE30_thwomp_pull[team]] = sindf(k / 20.0 * 180.0);
                }
                HmfModelData[obj->model[4 + i]].pos.y = (D_8010EE30_thwomp_pull[team] != 0) ? D_8010EF70_thwomp_pull[D_8010EE30_thwomp_pull[team]] * 100.0f : 0.0f;
                if (D_8010EE30_thwomp_pull[team] == 20) {
                    if (i == 0) {
                        D_8010F564_thwomp_pull[team] = 2;
                        HuAudFXPlay((team != 0) ? 0x337 : 0x336);
                    }
                    func_8001C258_main(obj->model[0x31 + i], 4, 0);
                    func_8010AF18_thwomp_pull(obj->model[0x31 + i], 0);
                    D_8010EE54_thwomp_pull[team][D_8010EE50_thwomp_pull[team]] = D_8010EE28_thwomp_pull[team] - 300.0f;
                    D_8010EE64_thwomp_pull[team][D_8010EE50_thwomp_pull[team]] = 0;
                    D_8010EE64_thwomp_pull[team][(D_8010EE50_thwomp_pull[team] + 1) & 1] = 1;
                    func_8001C258_main(obj->model[0x18 + D_8010EE50_thwomp_pull[team]], 4, 0);
                    func_8010AF18_thwomp_pull(obj->model[0x18 + D_8010EE50_thwomp_pull[team]], 0);
                    D_8010EF4C_thwomp_pull[team][i] = 22;
                    D_8010EF54_thwomp_pull[team][i] = D_8010EE28_thwomp_pull[team];
                }
            }
            if (D_8010EE34_thwomp_pull[team][i] != 0) {
                if ((D_8010EE24_thwomp_pull & 1) == team % 2) {
                    t = 1.0f - (f32)(D_8010EE34_thwomp_pull[team][i] / 15.0);
                    t = (1.0f - t * t) * 0.5 + 0.5;
                    r = rand8() / 256.0 * 10.0 * t;
                    if ((D_8010EE24_thwomp_pull & 3) >= 2) {
                        r = -r;
                    }
                    HmfModelData[obj->model[4 + i]].rot.z = r;
                } else {
                    HmfModelData[obj->model[4 + i]].rot.z *= 0.5;
                }
            } else {
                HmfModelData[obj->model[4 + i]].rot.z = 0.0f;
            }
        }
        for (i = 0; i < 3; i++) {
            m = &HmfModelData[obj->model[4 + i]];
            Hu3DModelPosSet(obj->model[0x31 + i], m->pos.x, 0.0f, (m->pos.z + D_8010EF54_thwomp_pull[team][i]) - D_8010EE28_thwomp_pull[team]);
            if (D_8010EF4C_thwomp_pull[team][i] == 1) {
                func_8001C258_main(obj->model[0x31 + i], 4, 4);
            }
            TP_DEC(D_8010EF4C_thwomp_pull[team][i]);
        }
        for (i = 0; i < team * 2 + 1; i++) {
            if (D_8010EF40_thwomp_pull[team + i] == 11) {
                func_8001C624_main(obj->model[1 + i], HmfModelData[obj->motion[3 + i]].unk02, 0, 20, 1);
            }
            TP_DEC(D_8010EF40_thwomp_pull[team + i]);
            func_8001C258_main(obj->model[1 + i], 4,
                               ((D_8010EF40_thwomp_pull[team + i] & 1) || (D_8010F566_thwomp_pull == team && D_8010F588_thwomp_pull > 0.0f)) ? 4 : 0);
            func_8001C258_main(obj->model[0x2A + i], 4,
                               ((D_8010EF40_thwomp_pull[team + i] & 1) && (D_8010F566_thwomp_pull != team || D_8010F588_thwomp_pull == 0.0f)) ? 4 : 0);
        }
        if (team == 1) {
            k = rand8() & 1;
            if (D_8010EE28_thwomp_pull[k] <= -10210.0f) {
                v = k;
            } else {
                v = -1;
                if (D_8010EE28_thwomp_pull[1 - k] <= -10210.0f) {
                    v = 1 - k;
                }
            }
            if (v != -1 && D_8010F566_thwomp_pull == 5) {
                D_8010F566_thwomp_pull = v;
            }
        }
        D_8010EE28_thwomp_pull[team] = (D_8010EE28_thwomp_pull[team] < -10950.0f) ? -10950.0f : D_8010EE28_thwomp_pull[team];
        D_8010F520_thwomp_pull[team] = D_8010EE28_thwomp_pull[team] / 10280.0f + 1.0f;
        D_8010F520_thwomp_pull[team] = (D_8010F520_thwomp_pull[team] < 0.0f) ? 0.0f : D_8010F520_thwomp_pull[team];
        for (k = 0; k < 1; k++) {
            for (i = 0; i < 2; i++) {
                Hu3DModelPosSet(obj->model[0x18 + i], 0.0f, 0.0f, (D_8010EE54_thwomp_pull[team][i] - D_8010EE28_thwomp_pull[team]) - 0.0f);
                if (D_8010EE64_thwomp_pull[team][i] < 60 && D_8010EE64_thwomp_pull[team][i] + 1 >= 60) {
                    func_8001C258_main(obj->model[0x18 + i], 4, 4);
                    func_8001C6A8_main(obj->model[0x18 + i], 0.0f);
                }
                D_8010EE64_thwomp_pull[team][i] += ((D_8010EE64_thwomp_pull[team][i] != 0 && D_8010EE64_thwomp_pull[team][i] < 60) &&
                                                    (D_8010EE30_thwomp_pull[team] != 0 && D_8010EE30_thwomp_pull[team] < 20)) * 3;
                if (D_8010EE64_thwomp_pull[team][i] < 60) {
                    func_8001C6A8_main(obj->model[0x18 + i], D_8010EE64_thwomp_pull[team][i]);
                }
            }
        }
        for (i = 0; i < team * 2 + 1; i++) {
            f32 tblA[8] = { 23.0f, 56.0f, 0.0f, 35.0f, 7.0f, 19.0f, 23.0f, 0.0f };
            f32 tblB[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f };

            m = &HmfModelData[obj->model[1]];
            if (m->unk02 == HmfModelData[obj->motion[3]].unk02) {
                a = tblA[D_8010F4F8_thwomp_pull[team + i]->chr];
            } else if (m->unk02 == HmfModelData[obj->motion[6]].unk02) {
                a = tblB[D_8010F4F8_thwomp_pull[team + i]->chr];
            } else {
                a = 0.0f;
            }
            b = a;
            if (m->unk04 != 0xFF) {
                if (m->unk04 == HmfModelData[obj->motion[3]].unk02) {
                    b = tblA[D_8010F4F8_thwomp_pull[team + i]->chr];
                } else if (m->unk04 == HmfModelData[obj->motion[6]].unk02) {
                    b = tblB[D_8010F4F8_thwomp_pull[team + i]->chr];
                } else {
                    b = 0.0f;
                }
            }
            if (m->unk0E < m->unk0C && m->unk0C > 0) {
                t = (f32)m->unk0E / (f32)m->unk0C;
            } else {
                t = 1.0f;
            }
            Hu3DModelPosSet(obj->model[1 + i], D_8010F578_thwomp_pull[team + i], D_8010F510_thwomp_pull[team + i],
                            a * (1.0f - t) + b * t + D_8010F540_thwomp_pull[team + i]);
        }
        for (i = 0; i < 3; i++) {
            f32 x;
            f32 py;
            f32 z;
            f32 dx;
            f32 dy;
            f32 dz;
            f32 dist;
            f32 ay;
            f32 ax;
            f64 s;
            f64 px;
            f64 qy;

            x = D_8010F578_thwomp_pull[team + team * i];
            f = D_8010F510_thwomp_pull[team + team * i] + 75.0f;
            if (D_8010F566_thwomp_pull == 0) {
                py = f - D_8010F588_thwomp_pull * 105.0f;
            } else {
                py = f - 0.0f;
            }
            z = D_8010F540_thwomp_pull[team + team * i] - 50.0f;
            s = (HmfModelData[obj->model[4 + i]].rot.z != 0.0f) ? sindf(HmfModelData[obj->model[4 + i]].rot.z) * 20.6426 * 5.0 : 0.0;
            px = HmfModelData[obj->model[4 + i]].pos.x;
            if (team != 0) {
                px = px - s * 1.5;
            } else {
                px = px - s;
            }
            s = (HmfModelData[obj->model[4 + i]].rot.z != 0.0f) ? cosdf(HmfModelData[obj->model[4 + i]].rot.z) * 20.6426 * 5.0 : 103.213;
            qy = HmfModelData[obj->model[4 + i]].pos.y;
            if (team != 0) {
                qy = qy + s * 1.5;
            } else {
                qy = qy + s;
            }
            s = 79.0315;
            if (team != 0) {
                s = 118.54725;
            }
            dx = (f32)px - x;
            dy = (f32)qy - py;
            dz = (f32)(HmfModelData[obj->model[4 + i]].pos.z + s) - z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            dz = -dz;
            ay = atan2df(-dx, dz);
            ax = atan2df(dy, dz);
            f = (ay > 0.0f) ? ay / 90.0f : -ay / 90.0f;
            Hu3DModelPosSet(obj->model[8 + i], x, py, z);
            Hu3DModelRotSet(obj->model[8 + i], 360.0f - (ax * (1.0f - f / 2.0f) + 90.0f), ay + 180.0f, 0.0f);
            {
                f32 farTbl[2][3] = { { 282.0f, 199.0f, 282.0f }, { 268.0f, 187.0f, 268.0f } };
                f32 nearTbl[2][3] = { { 276.0f, 170.0f, 276.0f }, { 183.0f, 92.0f, 183.0f } };

                farTbl[team][i] = farTbl[team][i] * 0.625 + nearTbl[team][i] * 0.375;
                nearTbl[team][i] *= (i == 0) ? 0.625 : 0.5;
                if (dist < nearTbl[team][i]) {
                    f = 1.0f;
                } else if (farTbl[team][i] < dist) {
                    f = 0.0f;
                } else {
                    f = 1.0f - (dist - nearTbl[team][i]) / (farTbl[team][i] - nearTbl[team][i]);
                }
            }
            Hu3DModelScaleSet(obj->model[8 + i], 1.0f, dist / 500.0, 1.0f);
            func_80016FB4_main(obj->model[8 + i], D_8010F528_thwomp_pull, f * 60.0f);
        }
        func_8001C258_main(obj->model[0x10], 4, 4);
        func_8001C258_main(obj->model[0x16], 4, 4);
        func_8001C258_main(obj->model[0x11], 4, 4);
        func_8001C258_main(obj->model[0x17], 4, 4);
        func_8001C258_main(obj->model[0x21], 4, 4);
        for (i = 0; i < 4; i++) {
            f = D_8010EE28_thwomp_pull[team] - 3000.0f;
            t = f / 1000.0f;
            rem = f - (f32)((s32)t * 1000);
            n = (t + 3.0f) - (f32)i;
            if (n >= -11 && n <= 0) {
                if (n == -4 || n == -7 || n == -10) {
                    f = (f32)(500 - i * 1000) - rem;
                    if (f + 750.0f > -3000.0f) {
                        func_8001C258_main(obj->model[0x21], 4, 0);
                        Hu3DModelPosSet(obj->model[0x21], -515.0f, 85.0f, f - 250.0f);
                        switch (D_8010EF28_thwomp_pull[team]) {
                            case 1:
                                k = obj->model[0x23];
                                a = D_8010EE68_thwomp_pull[team][0] + -515.0f;
                                b = D_8010EE88_thwomp_pull[team][0] + 85.0f;
                                y = (((f32)(500 - i * 1000) - rem) - 250.0f) + D_8010EEA8_thwomp_pull[team][0];
                                goto setpos;
                            case 2:
                                Hu3DModelPosSet(obj->model[0x22], D_8010EE68_thwomp_pull[team][0], D_8010EE88_thwomp_pull[team][0],
                                                D_8010EEA8_thwomp_pull[team][0] - D_8010EE28_thwomp_pull[team]);
                                k = obj->model[0x26];
                                a = D_8010EE68_thwomp_pull[team][0];
                                b = 0.0f;
                                y = D_8010EEA8_thwomp_pull[team][0] - D_8010EE28_thwomp_pull[team];
                            setpos:
                                Hu3DModelPosSet(k, a, b, y);
                                break;
                            case 3:
                                Hu3DModelPosSet(obj->model[0x24], 0.0f, 0.0f, (D_8010EEA8_thwomp_pull[team][0] - D_8010EE28_thwomp_pull[team]) + 35.0f);
                                D_8010EF2C_thwomp_pull[team] += 1.0f;
                                break;
                        }
                    }
                }
                func_8001C258_main(obj->model[0xC + i], 4, 4);
                func_8001C258_main(obj->model[0x12 + i], 4, 4);
                if (n == 0) {
                    k = 0x10;
                } else if (n == -11) {
                    k = 0x11;
                } else {
                    k = i + 0xC;
                }
                if (D_8010F588_thwomp_pull < 1.0f || D_8010F566_thwomp_pull == team) {
                    func_8001C258_main(obj->model[k], 4, 0);
                }
                Hu3DModelPosSet(obj->model[k], 0.0f, 0.0f, (f32)(500 - i * 1000) - rem);
                k = (k == 0x2D) ? i + 0x12 : k + 6;
                if (D_8010F588_thwomp_pull < 1.0f || D_8010F566_thwomp_pull == team) {
                    func_8001C258_main(obj->model[k], 4, 0);
                }
                Hu3DModelPosSet(obj->model[k], 0.0f, 0.0f, (f32)(500 - i * 1000) - rem);
            }
        }
    }
    for (team = 0; team < 2; team++) {
        f32 ofsX[2][3] = { { 3.0f, 1.0f, -6.5f }, { 11.0f, -0.5f, -11.0f } };
        f32 ofsY[2][3] = { { 76.0f, 81.5f, 76.0f }, { 106.5f, 107.0f, 110.0f } };
        f32 sclX[2][3] = { { 0.813f, 0.781f, 0.828f }, { 0.008f, -0.188f, -0.117f } };
        f32 sclY[2][3] = { { 0.883f, 0.773f, 0.906f }, { -0.117f, -0.141f, -0.117f } };

        obj = D_8010F568_thwomp_pull[team];
        for (i = 0; i < 3; i++) {
            m = &HmfModelData[obj->model[4 + i]];
            Hu3DModelPosSet(obj->model[0x2E + i], m->pos.x + ofsX[team][i], m->pos.y + ofsY[team][i], m->pos.z);
            m = &HmfModelData[obj->model[4 + i]];
            Hu3DModelScaleSet(obj->model[0x2E + i], m->scale.x + sclX[team][i], m->scale.y + sclY[team][i], m->scale.z + sclX[team][i]);
            if (D_8010F588_thwomp_pull == 0.0f && CRotM[team].x == -16.0f && HmfModelData[obj->model[4 + i]].rot.z == 0.0f) {
                func_8001C258_main(obj->model[0x2E + i], 4, 0);
                func_8001C258_main(obj->model[4 + i], 4, 4);
            } else {
                func_8001C258_main(obj->model[4 + i], 4, 0);
                func_8001C258_main(obj->model[0x2E + i], 4, 4);
            }
        }
    }
    D_8010EE24_thwomp_pull++;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F238_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F244_thwomp_pull);
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_8010AF88_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F280_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2A0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2C0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2D8_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2F0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F308_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F320_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F338_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F350_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F358_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F360_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F368_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F370_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F378_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F380_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F388_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F390_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F398_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3A0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3A8_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3B0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3B8_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3C0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3C8_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3D0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3D8_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3E0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3E8_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3F0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3F8_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F400_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F408_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F410_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F418_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F420_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F428_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F430_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F438_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F440_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F448_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F450_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F458_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F460_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F468_thwomp_pull);
#endif
