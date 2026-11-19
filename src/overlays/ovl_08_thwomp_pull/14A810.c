#include "common.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/hmflight.h"
#include "game/wipe.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/util.h"
#include "game/sprite.h"

/* main */
void func_8000B5F0_main(u8 arg0);
void func_8000B710_main(s32);
void func_800142A0_main(s32);
void func_8001EF24_main(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4);
void func_8001F38C_main(s32 arg0, s32 arg1, s32 arg2);
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
void func_80017320_main(void* motion);
extern s16 D_800EB934_minigame;
f32 sindf(f32 angle);
f32 cosdf(f32 angle);
f32 atan2df(f32 y, f32 x);
f32 HuSqrtf(f32 x);
s16 func_80017790_main(s16 model, s32 arg1, s16 arg2, s32 arg3);
s16 func_80017AD8_main(s32);
void func_80033910_main(HmfData*);
s32 func_8001C514_main(s16);
void func_8000B460_main(omObjData*, u16, s32);
s32 func_80017BB8_main(s16, s16);
void func_8001C8A8_main(s16, s16);
void func_8001C814_main(s16, s16, s16);
void func_8001C2FC_main(s16 arg0, s32 arg1, s32 arg2);
void func_8001FDE8_main(s16);
void* func_80016784_main(s16 model, s16 arg1);
void func_8001ACDC_main(s16);
s32 Hu3DModelLink(s16 linkMdlId);
void func_8001FB34_main(s16 arg0, u8 arg1);
void func_8001FBBC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_8001FBFC_main(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_8001FA68_main(s16);
void func_8001C8E4_main(s16, u32);

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
    /* 0x05 */ char unk05[1];
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ s32 unk0C; /* (directory << 16) | file */
} TpPlayer; // Size 0x10

typedef struct {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[0x1E];
} D_800CD1DC_main_Struct; // Size 0x24

extern D_800CD1DC_main_Struct* D_800CD1DC_main;
extern Gfx* gMainGfxPos;

/* .data */
extern Gfx D_8010ED90_thwomp_pull[]; /* render setup display list */
extern D_80111B50_vine_with_me_Struct D_8010ED60_thwomp_pull; /* minigame setup; inner labels D_8010ED61/66 */
extern u32 D_8010ED88_thwomp_pull;
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
extern f32 D_8010F470_thwomp_pull[3]; /* the winners' jump: x */
extern f32 D_8010F47C_thwomp_pull[3]; /* y */
extern f32 D_8010F488_thwomp_pull[3]; /* z */
extern f32 D_8010F494_thwomp_pull[3]; /* x speed */
extern f32 D_8010F4A0_thwomp_pull[3]; /* y speed */
extern f32 D_8010F4AC_thwomp_pull[3]; /* z speed */
extern TpPlayer D_8010F4B8_thwomp_pull[4];
extern TpPlayer* D_8010F4F8_thwomp_pull[4]; /* by slot; inner labels D_8010F4FC/500/504 */
extern f32 D_8010F510_thwomp_pull[4];
extern f32 D_8010F520_thwomp_pull[2]; /* func_80105D3C_thwomp_pull clears [0..3] */
extern void* D_8010F528_thwomp_pull;
extern s16 D_8010F530_thwomp_pull; /* game state */
extern f32 D_8010F534_thwomp_pull[2]; /* screen shake per team; inner label D_8010F538 */
extern s32 D_8010F53C_thwomp_pull;
extern f32 D_8010F540_thwomp_pull[4];
extern s16 D_8010F550_thwomp_pull[10]; /* sprite groups */
extern u8 D_8010F564_thwomp_pull[2];
extern s8 D_8010F566_thwomp_pull;
extern omObjData* D_8010F52C_thwomp_pull;
extern omObjData* D_8010F568_thwomp_pull[2]; /* inner label D_8010F56C */
extern u16 D_8010F570_thwomp_pull;
extern f32 D_8010F578_thwomp_pull[4];
extern f32 D_8010F588_thwomp_pull;
extern s16 D_8010F590_thwomp_pull[10]; /* esprites; inner labels D_8010F592/594 */
extern s32 D_8010F5A4_thwomp_pull;
extern u8 D_8010F5A8_thwomp_pull;
extern void* D_8010F5AC_thwomp_pull[2]; /* motions of the Thwomp's model; inner label D_8010F5B0 */
extern u8 D_8010F5B4_thwomp_pull[4]; /* slot by player */

extern const s16 D_8010EFD0_thwomp_pull[];

void func_80105D3C_thwomp_pull(omObjData* object);
void func_80106D5C_thwomp_pull(omObjData* object);
void func_8010974C_thwomp_pull(omObjData* object);
void func_80109780_thwomp_pull(omObjData* object);
void func_801097AC_thwomp_pull(omObjData* object, s8 team);
void func_80105F14_thwomp_pull(omObjData* object);
void func_80106E78_thwomp_pull(omObjData* object);
void func_80107FF4_thwomp_pull(s16* x1, s16* y1, s16* x2, s16* y2);
void func_801089B4_thwomp_pull(Gfx** gfx, s32 arg1, s32 arg2);
void func_8010AF18_thwomp_pull(s16 model, s16 frame);
void func_8010AF88_thwomp_pull(omObjData* object);

#define TP_DEC(x) ((x) = ((x) != 0) ? (x) - 1 : 0)
#define TP_INC(x) ((x) = ((x) != 0) ? (x) + 1 : 0)

const s16 D_8010EFD0_thwomp_pull[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D,
    0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279, 0x0000, 0x0000,
};

void func_801059A0_thwomp_pull(void) {
    omObjData* obj;
    omObjData* obj2;
    s16 none;

    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 140.0f, 240.0f);
    ScissorSet(1, 180.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 65.0f, 500.0f, 3000.0f);
    Hu3DCamSetPerspective(1, 65.0f, 500.0f, 3000.0f);
    func_8001EF24_main(950, 1000, 0xFF, 0xFF, 0xFF);
    func_8001F38C_main(0xFF, 0xFF, 0xFF);
    HmfLightMaxSet(2);
    HmfLightDirSet(0, 0.0f, 0.0f, 90.0f);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(1, -39.0f, 45.0f, 104.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 115.0f;
    CenterM[0].z = -500.0f;
    CRotM[0].x = -16.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 1260.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 115.0f;
    CenterM[1].z = -500.0f;
    CRotM[1].x = -16.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 1260.0f;
    omAddObj(0, 0, 0, -1, func_80105D3C_thwomp_pull);
    obj = omAddObj(8, 1, 1, -1, func_80106D5C_thwomp_pull);
    D_8010F52C_thwomp_pull = obj;
    omSetStatBit(obj, 0xA0);
    D_8010F568_thwomp_pull[0] = omAddObj(3, 52, 21, -1, func_8010974C_thwomp_pull);
    D_8010F568_thwomp_pull[1] = omAddObj(3, 52, 21, -1, func_80109780_thwomp_pull);
    obj2 = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj2->work[0] = 2;
    omSetStatBit(obj2, 0xA0);
    func_80045010_main(D_8010EFD0_thwomp_pull, 1);
    WipeCreateIn(0xFF, 0x10);
    D_8010ED60_thwomp_pull.unk01 = 2;
    none = -1;
    D_8010ED60_thwomp_pull.unk1C = 75;
    D_8010ED60_thwomp_pull.unk1E = 1800;
    D_8010ED60_thwomp_pull.unk03 = 2;
    D_8010ED60_thwomp_pull.unk02 = 1;
    D_8010ED60_thwomp_pull.unk22 = 45;
    D_8010ED60_thwomp_pull.unk24 = 165;
    D_8010ED60_thwomp_pull.unk04 = 0;
    D_8010ED60_thwomp_pull.unk05 = 0;
    D_8010ED60_thwomp_pull.unk20 = none;
    func_800E5EA0_minigame(&D_8010ED60_thwomp_pull);
}

void func_80105D3C_thwomp_pull(omObjData* object) {
    s32 i;
    s32 slot;

    D_8010F570_thwomp_pull = 0;
    D_8010F530_thwomp_pull = 0;
    D_8010F5A4_thwomp_pull = 0;
    D_8010F53C_thwomp_pull = 0;
    D_8010F566_thwomp_pull = 5;
    D_8010F5A8_thwomp_pull = 0;
    /* Clears four floats: [2] and [3] are D_8010F528_thwomp_pull and D_8010F52C_thwomp_pull. */
    D_8010F520_thwomp_pull[0] = D_8010F520_thwomp_pull[1] = D_8010F520_thwomp_pull[2] = D_8010F520_thwomp_pull[3] = 0.0f;
    D_8010F588_thwomp_pull = 0.0f;
    D_8010F564_thwomp_pull[0] = D_8010F564_thwomp_pull[1] = 0;
    for (i = 0; i < 4; i++) {
        D_8010F4F8_thwomp_pull[i] = &D_8010F4B8_thwomp_pull[i];
        bzero(D_8010F4F8_thwomp_pull[i], sizeof(TpPlayer));
    }
    for (i = 0; i < 4; i++) {
        slot = GwPlayer[i].group;
        slot = (slot == 3) ? 1 : (slot == 1) ? 3 : slot;
        D_8010F5B4_thwomp_pull[i] = slot;
        D_8010F4F8_thwomp_pull[slot]->player = i;
        D_8010F4F8_thwomp_pull[slot]->pad = GwPlayer[i].pad;
        D_8010F4F8_thwomp_pull[slot]->chr = GwPlayer[i].chr;
        D_8010F4F8_thwomp_pull[slot]->slot = slot;
        D_8010F4F8_thwomp_pull[slot]->cpu = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    func_8001AC8C_main(0, func_801089B4_thwomp_pull, 2);
    object->func = func_80105F14_thwomp_pull;
}

void func_80105F14_thwomp_pull(omObjData* object) {
    omObjData* obj;
    s32 i;
    u8 j;
    s32 k;

    D_8010F5A4_thwomp_pull++;
    D_8010F53C_thwomp_pull++;
    func_800E6F40_minigame();
    switch (D_8010F530_thwomp_pull) {
        case 0:
            if (D_8010F5A4_thwomp_pull == 1 && D_8010F570_thwomp_pull == 0 && D_800D530C_main == 0) {
                HuAudFXPlay(0x335);
            }
            if (func_800E6E8C_minigame() == 1) {
                D_8010F530_thwomp_pull = 1;
                D_8010F5A4_thwomp_pull = 0;
            }
            break;
        case 1:
            if (D_8010F5A4_thwomp_pull == 31 && D_8010F570_thwomp_pull == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(0x2E);
            }
            if (func_800E6E8C_minigame() == 2) {
                D_8010F530_thwomp_pull = 2;
                D_8010F5A4_thwomp_pull = 0;
            }
            break;
        case 2:
            if (D_8010F566_thwomp_pull != 5 || func_800E6E8C_minigame() == 3) {
                if (D_8010F566_thwomp_pull == 5) {
                    D_8010F530_thwomp_pull = 5;
                    D_8010F566_thwomp_pull = 4;
                } else {
                    D_8010F530_thwomp_pull = 3;
                }
                D_8010F5A4_thwomp_pull = 0;
            }
            if (D_8010F530_thwomp_pull != 3) {
                break;
            }
            /* fallthrough */
        case 3:
        case 4:
            if (D_8010F5A4_thwomp_pull == 0) {
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                if (D_8010F566_thwomp_pull == 0) {
                    D_8010ED60_thwomp_pull.unk06 = 0;
                    D_8010ED60_thwomp_pull.unk18 = D_8010F4F8_thwomp_pull[0]->player;
                    GwPlayer[D_8010F4F8_thwomp_pull[0]->player].bonusCoin = 10;
                } else {
                    D_8010ED60_thwomp_pull.unk06 = 2;
                    D_8010ED60_thwomp_pull.unk18 = D_8010F4F8_thwomp_pull[1]->player;
                    D_8010ED60_thwomp_pull.unk19[0] = D_8010F4F8_thwomp_pull[3]->player;
                    D_8010ED60_thwomp_pull.unk19[1] = D_8010F4F8_thwomp_pull[2]->player;
                    GwPlayer[D_8010F4F8_thwomp_pull[1]->player].bonusCoin = 10;
                    GwPlayer[D_8010F4F8_thwomp_pull[2]->player].bonusCoin = 10;
                    GwPlayer[D_8010F4F8_thwomp_pull[3]->player].bonusCoin = 10;
                }
            }
            if (D_8010F5A4_thwomp_pull == 2) {
                func_800E6F34_minigame(30);
            }
            if (D_8010F5A4_thwomp_pull >= 31 && D_8010F5A4_thwomp_pull <= 61) {
                D_8010F588_thwomp_pull = (D_8010F5A4_thwomp_pull - 31) / 30.0;
            }
            if (D_8010F5A4_thwomp_pull >= 32 && D_8010F5A4_thwomp_pull <= 79 && D_8010F566_thwomp_pull < 2) {
                obj = D_8010F568_thwomp_pull[D_8010F566_thwomp_pull];
                if (D_8010ED88_thwomp_pull == 0) {
                    for (i = 0; i < D_8010F566_thwomp_pull * 2 + 1; i++) {
                        D_8010F470_thwomp_pull[i] = D_8010F578_thwomp_pull[D_8010F566_thwomp_pull + i];
                        D_8010F47C_thwomp_pull[i] = D_8010F510_thwomp_pull[D_8010F566_thwomp_pull + i];
                        D_8010F488_thwomp_pull[i] = D_8010F540_thwomp_pull[D_8010F566_thwomp_pull + i];
                        D_8010F494_thwomp_pull[i] = (D_8010F566_thwomp_pull != 0) ? (1 - i) * 1.5 : 0.0f;
                        D_8010F4A0_thwomp_pull[i] = 38.0f;
                        D_8010F4AC_thwomp_pull[i] = 20.0f;
                        func_8001C258_main(obj->model[1 + i], 4, 4);
                        func_8001C258_main(obj->model[0x27 + i], 4, 0);
                        Hu3DModelPosSet(obj->model[0x27 + i], D_8010F470_thwomp_pull[i], D_8010F47C_thwomp_pull[i], D_8010F488_thwomp_pull[i]);
                        Hu3DModelRotSet(obj->model[0x27 + i], 0.0f, 0.0f, 0.0f);
                        func_8001C624_main(obj->model[0x27 + i], HmfModelData[obj->motion[0xF + i]].unk02, 8, 4, 1);
                    }
                } else if (D_8010ED88_thwomp_pull > 0 && D_8010ED88_thwomp_pull < 100) {
                    for (i = 0; i < D_8010F566_thwomp_pull * 2 + 1; i++) {
                        if (D_8010ED88_thwomp_pull < 5) {
                            f32 ofsY[4] = { -23.0f, -98.0f, -86.0f, -98.0f };
                            f32 ofsZ[4] = { -46.0f, -3.0f, -35.0f, -3.0f };

                            D_8010F510_thwomp_pull[D_8010F566_thwomp_pull + i] += ofsY[D_8010F566_thwomp_pull + i] / 4.0;
                            D_8010F540_thwomp_pull[D_8010F566_thwomp_pull + i] += ofsZ[D_8010F566_thwomp_pull + i] / 4.0;
                            if ((D_8010F566_thwomp_pull == 1) & (i == 0)) {
                                D_8010F540_thwomp_pull[D_8010F566_thwomp_pull + i] = ofsZ[D_8010F566_thwomp_pull + i];
                            }
                        }
                        D_8010F470_thwomp_pull[i] += D_8010F494_thwomp_pull[i];
                        D_8010F47C_thwomp_pull[i] += D_8010F4A0_thwomp_pull[i];
                        D_8010F488_thwomp_pull[i] += D_8010F4AC_thwomp_pull[i];
                        D_8010F4A0_thwomp_pull[i] -= 4.0f;
                        Hu3DModelPosSet(obj->model[0x27 + i], D_8010F470_thwomp_pull[i], D_8010F47C_thwomp_pull[i], D_8010F488_thwomp_pull[i]);
                        Hu3DModelPosSet(obj->model[0x2A + i], D_8010F470_thwomp_pull[i], (D_8010ED88_thwomp_pull == 1) ? 30.0f : 0.0f, D_8010F488_thwomp_pull[i]);
                        if (D_8010ED88_thwomp_pull == 2) {
                            func_8001C8E4_main(obj->model[0x2A + i], 0x400);
                        }
                        if (D_8010ED88_thwomp_pull == 1) {
                            func_8001C624_main(obj->model[0x27 + i], HmfModelData[obj->motion[0xC + i]].unk02, 14, 4, 0);
                        }
                    }
                    if (D_8010F47C_thwomp_pull[0] <= 0.0f) {
                        D_8010ED88_thwomp_pull = 100;
                        D_8010F47C_thwomp_pull[0] = 0.0f;
                        D_8010F47C_thwomp_pull[1] = 0.0f;
                        D_8010F47C_thwomp_pull[2] = 0.0f;
                        for (i = 0; i < D_8010F566_thwomp_pull * 2 + 1; i++) {
                            func_8001C624_main(obj->model[0x27 + i], HmfModelData[obj->motion[0xF + i]].unk02, 10, 4, 0);
                            Hu3DModelPosSet(obj->model[0x27 + i], D_8010F470_thwomp_pull[i], 0.0f, D_8010F488_thwomp_pull[i]);
                            Hu3DModelPosSet(obj->model[0x2A + i], D_8010F470_thwomp_pull[i], 0.0f, D_8010F488_thwomp_pull[i]);
                        }
                    }
                } else if (D_8010ED88_thwomp_pull == 102) {
                    for (i = 0; i < D_8010F566_thwomp_pull * 2 + 1; i++) {
                        func_8001C624_main(obj->model[0x27 + i], HmfModelData[obj->motion[i]].unk02, 0, 30, 2);
                    }
                }
                D_8010ED88_thwomp_pull += (D_8010ED88_thwomp_pull != 99);
            }
            if (D_800EB934_minigame != 0) {
                s32 chrs[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

                if (D_8010F566_thwomp_pull == 0) {
                    func_80017954_main(D_8010F568_thwomp_pull[0]->model[0x27], 1, chrs[D_8010F4F8_thwomp_pull[0]->chr], D_8010F4F8_thwomp_pull[0]->unk08);
                    func_8001C5B4_main(D_8010F568_thwomp_pull[0]->model[0x27], D_8010F568_thwomp_pull[0]->motion[9]);
                    func_8001C814_main(D_8010F568_thwomp_pull[0]->model[0x27], 3, 0);
                    func_80045ED0_main(D_8010F4F8_thwomp_pull[0]->unk0C);
                } else if (D_8010F566_thwomp_pull == 1) {
                    for (k = 0; k < 3; k++) {
                        func_80017954_main(D_8010F568_thwomp_pull[1]->model[0x27 + k], 1, chrs[D_8010F4F8_thwomp_pull[1 + k]->chr], D_8010F4F8_thwomp_pull[1 + k]->unk08);
                        func_8001C5B4_main(D_8010F568_thwomp_pull[1]->model[0x27 + k], D_8010F568_thwomp_pull[1]->motion[9 + k]);
                        func_8001C814_main(D_8010F568_thwomp_pull[1]->model[0x27 + k], 3, 0);
                        func_80045F1C_main(D_8010F4F8_thwomp_pull[1 + k]->unk0C, -1, D_8010F4F8_thwomp_pull[1 + k]->player);
                    }
                }
            }
            if (D_8010F530_thwomp_pull == 3 && func_800E6E8C_minigame() == 4) {
                D_8010F530_thwomp_pull = 4;
            }
            goto state6;
        case 5:
            if (D_8010F5A4_thwomp_pull == 1) {
                D_8010ED60_thwomp_pull.unk06 = 4;
                D_8010ED60_thwomp_pull.unk22 = 75;
                D_8010ED60_thwomp_pull.unk24 = 144;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010F530_thwomp_pull = 6;
                D_8010F5A4_thwomp_pull = 0;
            }
            break;
        case 6:
        state6:
            if (func_800E6E8C_minigame() == 5) {
                D_8010F530_thwomp_pull = 7;
                D_8010F5A4_thwomp_pull = 0;
            }
            break;
        case 7:
            if (D_8010F5A4_thwomp_pull == 1) {
                WipeCreateOut(0, 20);
            } else if (D_8010F5A4_thwomp_pull >= 32) {
                D_8010F570_thwomp_pull = 1;
            }
            break;
    }
    if (_CheckFlag(0xF) && D_800D530C_main == 0 && D_8010F5A8_thwomp_pull == 0 && D_8010F530_thwomp_pull == 2U) {
        for (j = 0; j < 2; j++) {
            if (D_8010F4F8_thwomp_pull[j]->cpu == -1 && (D_800D5558_main[D_8010F4F8_thwomp_pull[j]->pad] & 0x10)) {
                D_8010F5A8_thwomp_pull = 1;
            }
        }
    }
    if (D_8010F570_thwomp_pull == 0 && D_800D530C_main == 0 && D_8010F5A8_thwomp_pull == 0) {
        return;
    }
    if (D_800D530C_main != 0 && D_8010F5A8_thwomp_pull == 0) {
        D_8010F5A8_thwomp_pull = 1;
    }
    if (D_8010F5A8_thwomp_pull != 0) {
        if (D_8010F5A8_thwomp_pull == 1) {
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(20);
            func_8004AB0C_main(20);
        }
        D_8010F5A8_thwomp_pull++;
        if (D_8010F5A8_thwomp_pull < 25) {
            return;
        }
    }
    HuAudSeqFadeOut(30);
    func_80017320_main(D_8010F528_thwomp_pull);
    func_80017320_main(D_8010F5AC_thwomp_pull[0]);
    func_80017320_main(D_8010F5AC_thwomp_pull[1]);
    omOvlReturnEx(1);
}

void func_80106D5C_thwomp_pull(omObjData* object) {
    s32 files[10] = { 0x29001F, 0x290020, 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
    s16 i;

    for (i = 0; i < 10; i++) {
        D_8010F550_thwomp_pull[i] = func_8000B838_main(files[i]);
        D_8010F590_thwomp_pull[i] = InitEspriteSlot(D_8010F550_thwomp_pull[i], 0, 0);
        func_8000BB94_main(D_8010F590_thwomp_pull[i]);
    }
    object->func = func_80106E78_thwomp_pull;
}

#ifdef NON_MATCHING
void func_80106E78_thwomp_pull(omObjData* object) {
    s16 x1[2];
    s16 y1[2];
    s16 x2[2];
    s16 y2[2];
    f32 scX1[2];
    f32 scX2[2];
    f32 vpScale[2];
    f32 vpX[2];
    f32 vpY[2];
    omObjData* obj;
    s32 i;
    s32 other;
    f32 t;
    f32 x;
    f32 p;
    u8 c;
    u8* q;

    x1[0] = 0;
    x1[1] = 160;
    y1[0] = 0;
    y1[1] = 0;
    x2[0] = 160;
    x2[1] = 320;
    y2[0] = 240;
    y2[1] = 240;
    if (D_8010F53C_thwomp_pull == 100) {
        CenterM[0].x = CenterM[1].x = 0.0f;
        CenterM[0].y = CenterM[1].y = 115.0f;
        CenterM[0].z = CenterM[1].z = -500.0f;
        CRotM[0].x = CRotM[1].x = -16.0f;
        CRotM[0].y = CRotM[1].y = 0.0f;
        CRotM[0].z = CRotM[1].z = 0.0f;
        CZoomM[0] = CZoomM[1] = 1260.0f;
        Hu3DCamSetPerspective(0, 65.0f, 500.0f, 3000.0f);
        Hu3DCamSetPerspective(1, 65.0f, 500.0f, 3000.0f);
    }
    if (D_8010F588_thwomp_pull > 0.0f && D_8010F566_thwomp_pull < 2) {
        p = D_8010F588_thwomp_pull;
        t = 1.0f - p;
        scX1[0] = 0.0f;
        scX1[1] = 180.0f;
        scX2[0] = 140.0f;
        scX2[1] = 320.0f;
        vpScale[0] = 1.0f;
        vpScale[1] = 1.0f;
        vpX[0] = 320.0f;
        vpX[1] = 960.0f;
        vpY[0] = 480.0f;
        vpY[1] = 480.0f;
        CenterM[D_8010F566_thwomp_pull].y = t * 115.0f - p * 80.0f;
        CRotM[D_8010F566_thwomp_pull].x = t * -16.0f - p * 6.0f;
        CZoomM[D_8010F566_thwomp_pull] = t * 1260.0f + (f32)(D_8010F566_thwomp_pull * 150 + 1600) * p;
        vpScale[D_8010F566_thwomp_pull] = p + 1.0f;
        scX1[D_8010F566_thwomp_pull] = t * scX1[D_8010F566_thwomp_pull] + p * 0.0f;
        scX2[D_8010F566_thwomp_pull] = t * scX2[D_8010F566_thwomp_pull] + p * 320.0f;
        vpX[D_8010F566_thwomp_pull] = t * vpX[D_8010F566_thwomp_pull] + p * 640.0f;
        vpY[D_8010F566_thwomp_pull] = t * vpY[D_8010F566_thwomp_pull] + p * ((D_8010F566_thwomp_pull != 0) ? 780.0 : 720.0);
        x1[D_8010F566_thwomp_pull] = x1[D_8010F566_thwomp_pull] * t + p * 0.0f;
        x2[D_8010F566_thwomp_pull] = x2[D_8010F566_thwomp_pull] * t + p * 320.0f;
        y1[D_8010F566_thwomp_pull] = y1[D_8010F566_thwomp_pull] * t + p * ((D_8010F566_thwomp_pull != 0) ? -30.0f : -60.0f);
        y2[D_8010F566_thwomp_pull] = y2[D_8010F566_thwomp_pull] * t + p * ((D_8010F566_thwomp_pull != 0) ? 450.0f : 420.0f);
        if (D_8010F566_thwomp_pull == 0) {
            scX1[1] = t * scX1[1] + p * 318.0f;
            scX2[1] = t * scX2[1] + p * 320.0f;
            vpX[1] += p * 712.0f;
            i = p * 178.0f;
            x1[1] += i;
            x2[1] += i;
        } else {
            scX1[0] = t * scX1[0] + p * 0.0f;
            scX2[0] = t * scX2[0] + p * 2.0f;
            vpX[0] -= p * 712.0f;
            i = p * 178.0f;
            x1[0] -= i;
            x2[0] -= i;
        }
        ScissorSet(0, scX1[0], 0.0f, scX2[0], 240.0f);
        ScissorSet(1, scX1[1], 0.0f, scX2[1], 240.0f);
        ViewportSet(0, vpScale[0] * 640.0f, vpScale[0] * 480.0f, 511.0f, vpX[0], vpY[0], 511.0f);
        ViewportSet(1, vpScale[1] * 640.0f, vpScale[1] * 480.0f, 511.0f, vpX[1], vpY[1], 511.0f);
        func_80107FF4_thwomp_pull(x1, y1, x2, y2);
        if (D_8010F588_thwomp_pull == 1.0f) {
            other = 1 - D_8010F566_thwomp_pull;
            obj = D_8010F568_thwomp_pull[other];
            func_8001C258_main(obj->model[7], 4, 4);
            for (i = 0; i < other * 2 + 1; i++) {
                func_8001C258_main(obj->model[1 + i], 4, 4);
            }
            for (i = 0; i < 3; i++) {
                func_8001C258_main(obj->model[4 + i], 4, 4);
            }
            for (i = 0; i < 4; i++) {
                func_8001C258_main(obj->model[0xC + i], 4, 4);
                func_8001C258_main(obj->model[0x12 + i], 4, 4);
            }
        }
    } else if (D_8010F53C_thwomp_pull < 100) {
        t = (D_8010F53C_thwomp_pull < 80) ? D_8010F53C_thwomp_pull / 80.0 : 1.0f;
        x = 1.0f - t;
        CenterM[0].x = CenterM[1].x = t * 435.0f - x * 60.0f;
        CenterM[0].y = CenterM[1].y = 140.0f;
        CenterM[0].z = CenterM[1].z = -660.0f;
        CRotM[0].x = CRotM[1].x = -8.0f;
        CRotM[0].y = CRotM[1].y = -225.0f;
        CRotM[0].z = CRotM[1].z = 0.0f;
        CZoomM[0] = CZoomM[1] = 100.0f;
        CenterM[1].x = -CenterM[1].x;
        CRotM[1].y = -CRotM[1].y;
        Hu3DCamSetPerspective(0, 65.0f, 50.0f, 4000.0f);
        Hu3DCamSetPerspective(1, 65.0f, 50.0f, 4000.0f);
        y1[0] += D_8010F534_thwomp_pull[0];
        y2[0] += D_8010F534_thwomp_pull[0];
        y1[1] += D_8010F534_thwomp_pull[1];
        y2[1] += D_8010F534_thwomp_pull[1];
        func_80107FF4_thwomp_pull(x1, y1, x2, y2);
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, D_8010F534_thwomp_pull[0] * 4.0f + 480.0f, 511.0f);
        ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, D_8010F534_thwomp_pull[1] * 4.0f + 480.0f, 511.0f);
    } else {
        if (D_8010F53C_thwomp_pull < 150) {
            if (D_8010F53C_thwomp_pull >= 100) {
                t = (D_8010F53C_thwomp_pull < 115) ? (D_8010F53C_thwomp_pull - 100) / 15.0 : 1.0f;
            } else {
                t = 0.0f;
            }
            x = 1.0f - t;
            t = (x * x * x * 0.75 + x * 0.25) * 0.5 + 1.0;
            ViewportSet(0, t * 640.0f, t * 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
            ViewportSet(1, t * 640.0f, t * 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
            x1[0] = (x1[0] - 80) * t + 80.0f;
            y1[0] = (y1[0] - 120) * t + 120.0f;
            x2[0] = (x2[0] - 80) * t + 80.0f;
            y2[0] = (y2[0] - 120) * t + 120.0f;
            x1[1] = (x1[1] - 240) * t + 240.0f;
            y1[1] = (y1[1] - 120) * t + 120.0f;
            x2[1] = (x2[1] - 240) * t + 240.0f;
            y2[1] = (y2[1] - 120) * t + 120.0f;
            Hu3DCamSetPerspective(0, 65.0f, 500.0f, 3000.0f);
            Hu3DCamSetPerspective(1, 65.0f, 500.0f, 3000.0f);
        } else {
            if (D_8010F53C_thwomp_pull >= 90) {
                t = (D_8010F53C_thwomp_pull < 120) ? 2.5 - (D_8010F53C_thwomp_pull - 90) / 30.0 * 1.5 : 1.0f;
            } else {
                t = 2.5f;
            }
            ViewportSet(0, t * 640.0f, t * 480.0f, 511.0f, 320.0f, D_8010F534_thwomp_pull[0] * 4.0f + 480.0f, 511.0f);
            ViewportSet(1, t * 640.0f, t * 480.0f, 511.0f, 960.0f, D_8010F534_thwomp_pull[1] * 4.0f + 480.0f, 511.0f);
            x1[0] = (x1[0] - 80) * t + 80.0f;
            y1[0] = (y1[0] - 120) * t + 120.0f;
            x2[0] = (x2[0] - 80) * t + 80.0f;
            y2[0] = (y2[0] - 120) * t + 120.0f;
            x1[1] = (x1[1] - 240) * t + 240.0f;
            y1[1] = (y1[1] - 120) * t + 120.0f;
            x2[1] = (x2[1] - 240) * t + 240.0f;
            y2[1] = (y2[1] - 120) * t + 120.0f;
            y1[0] += D_8010F534_thwomp_pull[0];
            y2[0] += D_8010F534_thwomp_pull[0];
            y1[1] += D_8010F534_thwomp_pull[1];
            y2[1] += D_8010F534_thwomp_pull[1];
        }
        func_80107FF4_thwomp_pull(x1, y1, x2, y2);
    }
    if (func_80049F98_main() == 0) {
        other = D_8010F564_thwomp_pull[0];
        D_8010F534_thwomp_pull[0] = ((other & 1) ? -other : other) * 0.5;
        q = &D_8010F564_thwomp_pull[0];
        c = *q;
        if (c != 0) {
            c--;
        }
        *q = c;
        other = D_8010F564_thwomp_pull[1];
        D_8010F534_thwomp_pull[1] = ((other & 1) ? -other : other) * 0.5;
        q = &D_8010F564_thwomp_pull[1];
        c = *q;
        if (c != 0) {
            c--;
        }
        *q = c;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80106E78_thwomp_pull);
#endif

#ifdef NON_MATCHING
void func_80107FF4_thwomp_pull(s16* x1, s16* y1, s16* x2, s16* y2) {
    s32 scX1[2];
    s32 scX2[2];
    f32 sx[2];
    f32 ox[2];
    f32 sy[2];
    f32 oy[2];
    s32 dsdx[2];
    s32 dtdy[2];
    HuSprite* spr;
    HuSprite_Unk84_Unk00_Struct* frame;
    s32 i;
    s32 row;
    s32 col;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;
    f32 t;
    f32 tx0;
    f32 tx1;
    f32 ty0;
    f32 ty1;
    f32 p;

    for (i = 0; i < 2; i++) {
        sx[i] = (x2[i] - x1[i]) / 160.0;
        ox[i] = x1[i];
        dsdx[i] = (1.0 / sx[i]) * 1024.0;
        sy[i] = (y2[i] - y1[i]) / 240.0;
        oy[i] = y1[i];
        dtdy[i] = (1.0 / sy[i]) * 1024.0;
        scX1[i] = (i == 0) ? 0 : 180;
        scX2[i] = (i != 0) ? 320 : 140;
    }
    if (D_8010F588_thwomp_pull > 0.0f && D_8010F566_thwomp_pull < 2) {
        p = D_8010F588_thwomp_pull;
        t = 1.0f - p;
        scX1[D_8010F566_thwomp_pull] = scX1[D_8010F566_thwomp_pull] * t + p * 0.0f;
        scX2[D_8010F566_thwomp_pull] = scX2[D_8010F566_thwomp_pull] * t + p * 320.0f;
        if (D_8010F566_thwomp_pull == 0) {
            scX1[1] = scX1[1] * t + p * 318.0f;
            scX2[1] = scX2[1] * t + p * 320.0f;
        } else {
            scX1[0] = scX1[0] * t + p * 0.0f;
            scX2[0] = scX2[0] * t + p * 2.0f;
        }
    }
    gSPDisplayList(gMainGfxPos++, &D_8010ED90_thwomp_pull);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    spr = HuSprGet(D_800CD1DC_main[D_8010F590_thwomp_pull[0]].unk04, 0);
    frame = &spr->unk_84->unk00[spr->unk_90];
    gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
    for (row = 0; row < 3; row++) {
        ty0 = row * 40;
        ty1 = ty0 + 40.0f + ((row == 2) ? -0.75 : 1.0);
        for (col = 0; col < 4; col++) {
            tx0 = col * 40;
            tx1 = (col < 3) ? tx0 + 40.0f + 1.0f : tx0 + 40.0f + 0.0f;
            gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 160, 0, (s32)tx0, (s32)ty0,
                               (s32)tx1, (s32)ty1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            for (i = 0; i < 2; i++) {
                if (D_8010F588_thwomp_pull == 1.0f && i != D_8010F566_thwomp_pull) {
                    continue;
                }
                xl = (tx0 * sx[i] + ox[i]) * 4.0f;
                yl = ((ty0 - 1.0f) * sy[i] + oy[i]) * 4.0f;
                xh = (tx1 * sx[i] + ox[i]) * 4.0f;
                yh = ((ty1 - 1.0f) * sy[i] + oy[i]) * 4.0f;
                if (xl > 1280 || yl > 960 || xh < 0 || yh < 0) {
                    continue;
                }
                gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, scX1[i], 0, scX2[i], 240);
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, tx0 * 32.0f, ty0 * 32.0f,
                                        dsdx[i], dtdy[i]);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80107FF4_thwomp_pull);
#endif

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

#ifdef NON_MATCHING
void func_801097AC_thwomp_pull(omObjData* object, s8 team) {
    s32 dirTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 mdlTbl[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 mdl2Tbl[8] = { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 };
    s32 chrTbl[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 mtnTbl[2][8] = {
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
    };
    volatile s32 attr;
    u16 i;
    u16 chr;
    TpPlayer* pl;
    f32 f;
    s32 k;
    s32 n;

    attr = 0x8B9;
    for (i = 0; i < ((team != 0) ? 3 : 1); i++) {
        chr = (s8)D_8010F4F8_thwomp_pull[team + i]->chr;
        object->model[1 + i] = func_8000B108_main((dirTbl[chr] << 16) | mdlTbl[chr], attr);
        func_8001C8A8_main(object->model[1 + i], (team != 0) ? 2 : 1);
        object->model[0x27 + i] = func_8000B108_main((dirTbl[chr] << 16) | mdl2Tbl[chr], 0x8AD);
        func_8001C8A8_main(object->model[0x27 + i], (team != 0) ? 2 : 1);
        pl = D_8010F4F8_thwomp_pull[team + i];
        pl->unk06 = func_80017790_main(object->model[0x27 + i], 1, chrTbl[chr], (dirTbl[chr] << 16) | mtnTbl[0][chr]);
        pl->unk08 = func_80017AD8_main((dirTbl[chr] << 16) | mtnTbl[1][chr]);
        func_80033910_main(HmfModelData[object->model[0x27 + i]].hmf);
        func_8001C514_main(object->model[0x27 + i]);
        pl->unk0C = (rand8() & 1) ? 0x2F : 0x30;
        func_8000B460_main(object, i, func_80017BB8_main(chr, 0));
        func_8000B460_main(object, i + 3, func_80017BB8_main(chr, 0x84));
        func_8000B460_main(object, i + 6, func_80017BB8_main(chr, 0x21));
        func_8000B460_main(object, i + 12, func_80017BB8_main(chr, 4));
        func_8000B460_main(object, i + 15, func_80017BB8_main(chr, 0x1F));
        func_8000B460_main(object, i + 9, func_80017BB8_main(chr, D_8010F4F8_thwomp_pull[team + i]->unk0C));
        D_8010F4F8_thwomp_pull[team + i]->unk0C = (dirTbl[chr] << 16) | D_8010F4F8_thwomp_pull[team + i]->unk0C;
        if (team != 0) {
            D_8010F578_thwomp_pull[team + i] = (1 - i) * 125;
        } else {
            D_8010F578_thwomp_pull[team + i] = 0.0f;
        }
        D_8010F510_thwomp_pull[team + i] = 25.0f;
        if (team != 0) {
            D_8010F540_thwomp_pull[team + i] = -((i & 1) * 20);
        } else {
            D_8010F540_thwomp_pull[team + i] = 0.0f;
        }
        Hu3DModelPosSet(object->model[1 + i], D_8010F578_thwomp_pull[team + i], D_8010F510_thwomp_pull[team + i], D_8010F540_thwomp_pull[team + i]);
        Hu3DModelRotSet(object->model[1 + i], 0.0f, 180.0f, 0.0f);
        func_8001C5B4_main(object->model[1 + i], object->motion[3 + i]);
        func_8001C814_main(object->model[1 + i], 3, 1);
        func_8001C5B4_main(object->model[0x27 + i], object->motion[3 + i]);
        func_8001C2FC_main(object->model[1], 0x600, 0x400);
    }
    attr = 0x8B9;
    object->model[7] = func_8000B108_main((team != 0) ? 0x29000A : 0x290009, attr);
    func_8001C8A8_main(object->model[7], (team != 0) ? 2 : 1);
    Hu3DModelPosSet(object->model[7], 0.0f, 0.0f, (team != 0) ? -25.0f : 35.0f);
    Hu3DModelRotSet(object->model[7], 0.0f, 180.0f, 0.0f);
    attr = 0xAB9;
    for (i = 0; i < 3; i++) {
        object->model[8 + i] = func_8000B108_main(0x290007, attr);
        func_8001C8A8_main(object->model[8 + i], (team != 0) ? 2 : 1);
        func_8001C814_main(object->model[8 + i], 3, 1);
        func_8001FDE8_main(object->model[8 + i]);
    }
    if (team == 0) {
        func_8000B460_main(object, 20, 0x290008);
        func_8001C5B4_main(object->model[8], object->motion[20]);
        D_8010F528_thwomp_pull = func_80016784_main(object->model[8], 1);
        func_8001ACDC_main(object->motion[20]);
    }
    for (i = 0; i < 3; i++) {
        func_8001C5B4_main(object->model[8 + i], D_8010F568_thwomp_pull[0]->motion[20]);
    }
    attr = 0x8B9;
    for (i = 0; i < 3; i++) {
        if (team == 0 && i == 0) {
            object->model[4] = func_8000B108_main(0x290012, attr);
        } else {
            object->model[4 + i] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[4]);
        }
        Hu3DModelPosSet(object->model[4 + i], (1 - i) * (team * 60 + 200), 0.0f, -300.0f);
        Hu3DModelRotSet(object->model[4 + i], 0.0f, 180.0f, 0.0f);
        f = team * 0.5 + 1.0;
        Hu3DModelScaleSet(object->model[4 + i], f, f, f);
        func_8001C8A8_main(object->model[4 + i], (team != 0) ? 2 : 1);
        func_8001C2FC_main(object->model[4 + i], 0x600, 0);
    }
    attr = 0xABD;
    for (i = 0; i < 3; i++) {
        s32 hookTbl[2][3] = { { 0x13, 0x14, 0x15 }, { 0x16, 0x17, 0x18 } };

        object->model[0x2E + i] = func_8000B108_main(hookTbl[team][i] | 0x290000, attr);
        Hu3DModelPosSet(object->model[0x2E + i], (1 - i) * (team * 60 + 200), 0.0f, -300.0f);
        Hu3DModelRotSet(object->model[0x2E + i], -16.0f, 0.0f, 0.0f);
        f = team * 0.5 + 1.0;
        Hu3DModelScaleSet(object->model[0x2E + i], f, f, f);
        func_8001C8A8_main(object->model[0x2E + i], (team != 0) ? 2 : 1);
        func_8001C2FC_main(object->model[0x2E + i], 0x600, 0);
        func_8001C2FC_main(object->model[0x2E + i], 0x70000000, 0x70000000);
        func_8001FB34_main(object->model[0x2E + i], 1);
        func_8001FBBC_main(object->model[0x2E + i], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[0x2E + i], 0.0f, 0.0f, 127.0f);
    }
    attr = 0x8BD;
    for (i = 0; i < 3; i++) {
        if (team == 0) {
            object->model[0x1E + i] = func_8000B108_main((i == 0) ? 0x29000B : (i != 1) ? 0x29000D : 0x29000C, attr);
        } else {
            object->model[0x1E + i] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[0x1E + i]);
        }
        k = (i == 2);
        if (team == 0) {
            n = k * 10;
        } else {
            n = k * 60;
        }
        Hu3DModelPosSet(object->model[0x1E + i], ((1 - i) * 175 + 50) - n, 300.0f, -300.0f);
        Hu3DModelScaleSet(object->model[0x1E + i], 1.6820346f, 1.6820346f, 1.6820346f);
        func_8001C2FC_main(object->model[0x1E + i], 0x70000000, 0x70000000);
        func_8001C8A8_main(object->model[0x1E + i], (team != 0) ? 2 : 1);
    }
    if (team >= 0) {
        object->model[0x21] = func_8000B108_main(0x29001C, 0x4DD);
    } else {
        object->model[0x21] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[0x21]);
    }
    func_8001C8A8_main(object->model[0x21], (team != 0) ? 2 : 1);
    Hu3DModelScaleSet(object->model[0x21], 4.0f, 4.0f, 4.0f);
    Hu3DModelRotSet(object->model[0x21], 0.0f, 45.0f, 0.0f);
    func_8001FDE8_main(object->model[0x21]);
    if (team == 0) {
        func_8000B460_main(object, 18, 0x29001D);
        func_8001C5B4_main(object->model[0x21], object->motion[18]);
        D_8010F5AC_thwomp_pull[0] = func_80016784_main(object->model[0x21], 2);
        func_8001ACDC_main(object->motion[18]);
        func_8000B460_main(object, 19, 0x29001E);
        func_8001C5B4_main(object->model[0x21], object->motion[19]);
        D_8010F5AC_thwomp_pull[1] = func_80016784_main(object->model[0x21], 2);
        func_8001ACDC_main(object->motion[19]);
    }
    func_8001C5B4_main(object->model[0x21], D_8010F568_thwomp_pull[0]->motion[18]);
    func_80016FB4_main(object->model[0x21], D_8010F5AC_thwomp_pull[0], 0);
    object->model[0x22] = func_8000B108_main(0x29001A, 0x8DD);
    func_8001C8A8_main(object->model[0x22], (team != 0) ? 2 : 1);
    Hu3DModelScaleSet(object->model[0x22], 1.0f, 1.0f, 1.0f);
    func_8001C814_main(object->model[0x22], 3, 1);
    func_8001C2FC_main(object->model[0x22], 0x600, 0x400);
    object->model[0x24] = func_8000B108_main(0x29001B, 0x8CD);
    func_8001C8A8_main(object->model[0x24], (team != 0) ? 2 : 1);
    Hu3DModelScaleSet(object->model[0x24], 2.5f, 2.5f, 2.5f);
    func_8001C2FC_main(object->model[0x24], 0x600, 0x400);
    for (i = 0; i < 1; i++) {
        object->model[0x23] = func_8000B108_main(0x29001A, 0x8CD);
        func_8001FA68_main(object->model[0x23]);
        func_8001F9E4_main(object->model[0x23], 0xFF);
        func_8001C8A8_main(object->model[0x23 + i], (team != 0) ? 2 : 1);
        Hu3DModelScaleSet(object->model[0x23 + i], 0.25f, 0.25f, 0.25f);
        func_8001C814_main(object->model[0x23 + i], 3, 1);
        func_8001C2FC_main(object->model[0x23 + i], 0x600, 0x400);
    }
    object->model[0x26] = func_8000B108_main(9, 0x4CD);
    Hu3DModelScaleSet(object->model[0x26], 3.5f, 3.5f, 3.0f);
    func_8001C8A8_main(object->model[0x26], (team != 0) ? 2 : 1);
    func_8001FA68_main(object->model[0x26]);
    func_8001F9E4_main(object->model[0x26], 0x80);
    for (i = 0; i < team * 2 + 1; i++) {
        if (i == 0) {
            object->model[0x2A] = func_8000B108_main(9, 0x4C9);
            func_8001FA68_main(object->model[0x2A]);
            func_8001F9E4_main(object->model[0x2A], 0x80);
            func_8001C8E4_main(object->model[0x2A], 0x800);
        } else {
            object->model[0x2A + i] = Hu3DModelLink(object->model[0x2A]);
        }
        Hu3DModelPosSet(object->model[0x2A + i], D_8010F578_thwomp_pull[team + i], 28.0f, D_8010F540_thwomp_pull[team + i]);
        func_8001C8A8_main(object->model[0x2A + i], (team != 0) ? 2 : 1);
    }
    if (team == 0) {
        object->model[0x16] = func_8000B108_main(0x290003, 0x4BD);
    } else {
        object->model[0x16] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[0x16]);
    }
    func_8001C8A8_main(object->model[0x16], (team != 0) ? 2 : 1);
    func_8001FB34_main(object->model[0x16], 1);
    func_8001FBBC_main(object->model[0x16], 0xFF, 0xFF, 0xFF);
    func_8001FBFC_main(object->model[0x16], 0.0f, 0.0f, 127.0f);
    for (i = 0; i < 4; i++) {
        if (team == 0 && i == 0) {
            object->model[0x12] = func_8000B108_main(0x290004, 0x4BD);
        } else {
            object->model[0x12 + i] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[0x12]);
        }
        func_8001C8A8_main(object->model[0x12 + i], (team != 0) ? 2 : 1);
        func_8001C2FC_main(object->model[0x12 + i], 0x600, 0);
        func_8001FB34_main(object->model[0x12 + i], 1);
        func_8001FBBC_main(object->model[0x12 + i], 0xFF, 0xFF, 0xFF);
        func_8001FBFC_main(object->model[0x12 + i], 0.0f, 0.0f, 127.0f);
    }
    if (team == 0) {
        object->model[0x17] = func_8000B108_main(0x290005, 0x4DD);
    } else {
        object->model[0x17] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[0x17]);
    }
    func_8001C8A8_main(object->model[0x17], (team != 0) ? 2 : 1);
    func_8001FB34_main(object->model[0x17], 1);
    func_8001FBBC_main(object->model[0x17], 0xFF, 0xFF, 0xFF);
    func_8001FBFC_main(object->model[0x17], 0.0f, 0.0f, 127.0f);
    attr = 0x41D;
    for (i = 0; i < 2; i++) {
        object->model[0x18 + i] = func_8000B108_main((team != 0) ? 0x29000F : 0x29000E, attr);
        func_8001C8A8_main(object->model[0x18 + i], (team != 0) ? 2 : 1);
    }
    func_8001C258_main(object->model[0x18], 4, 0);
    Hu3DModelPosSet(object->model[0x18], 0.0f, 0.0f, -315.0f);
    object->model[0xB] = func_8000B108_main((team != 0) ? 0x290011 : 0x290010, 0x4D9);
    Hu3DModelPosSet(object->model[0xB], 0.0f, 10.0f, 0.0f);
    Hu3DModelScaleSet(object->model[0xB], 1.0f, 1.0f, 12.0f);
    func_8001C2FC_main(object->model[0xB], 0x600, 0);
    func_8001C8A8_main(object->model[0xB], (team != 0) ? 2 : 1);
    attr = 0x6CD;
    for (i = 0; i < 3; i++) {
        object->model[0x31 + i] = func_8000B108_main(0x290019, attr);
        func_8001C8A8_main(object->model[0x31 + i], (team != 0) ? 2 : 1);
        f = team * 0.5 + 1.75;
        Hu3DModelScaleSet(object->model[0x31 + i], f, f, f);
    }
    if (team == 0) {
        object->model[0x10] = func_8000B108_main(0x290000, 0x45D);
    } else {
        object->model[0x10] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[0x10]);
    }
    func_8001C8A8_main(object->model[0x10], (team != 0) ? 2 : 1);
    func_8001C2FC_main(object->model[0x10], 0x600, 0);
    for (i = 0; i < 4; i++) {
        if (team == 0 && i == 0) {
            object->model[0xC] = func_8000B108_main(0x290001, 0x41D);
        } else {
            object->model[0xC + i] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[0xC]);
        }
        func_8001C8A8_main(object->model[0xC + i], (team != 0) ? 2 : 1);
        func_8001C2FC_main(object->model[0xC + i], 0x600, 0);
        func_8001C2FC_main(object->model[0xC + i], 0x600, 0);
    }
    if (team == 0) {
        object->model[0x11] = func_8000B108_main(0x290002, 0x45D);
    } else {
        object->model[0x11] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[0x11]);
    }
    func_8001C8A8_main(object->model[0x11], (team != 0) ? 2 : 1);
    func_8001C2FC_main(object->model[0x11], 0x600, 0);
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F150_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F170_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F190_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F1B0_thwomp_pull);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F1F0_thwomp_pull);
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_801097AC_thwomp_pull);
#endif

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
                func_80016FB4_main(obj->model[0x21], D_8010F5AC_thwomp_pull[0], D_8010EF34_thwomp_pull[team] * 2 - 2);
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
                func_80016FB4_main(obj->model[0x21], D_8010F5AC_thwomp_pull[1], (D_8010EF34_thwomp_pull[team] - 16) * 2);
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
            s = HmfModelData[obj->model[4 + i]].pos.z;
            if (team != 0) {
                s = s + 118.54725;
            } else {
                s = s + 79.0315;
            }
            dx = (f32)px - x;
            dy = (f32)qy - py;
            dz = (f32)s - z;
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
