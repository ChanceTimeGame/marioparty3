#include "common.h"
#include "overlays/ovl_36.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "include_asm.h"

#define PLAYERS_TOTAL 2

// C1F0
void func_8000B5F0_main(u8 arg0);
s32 func_8000B710_main(s32 arg0);

// 14EA0
s32 func_80017BB8_main(s16, s16);
s16 func_80017790_main(s16 model, s32 arg1, s16 arg2, s32 arg3);
void func_800142A0_main(s32);

// 20A20
void Hu3DAnimInit(s32);

// unknown
extern u16 D_800D530C_main;

enum {
    FGRP_CAMERA
};

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 unk04[3][7];
    /* 0x2E */ s16 unk2E[3];
    /* 0x34 */ s16 unk34[3][3];
    /* 0x46 */ s16 unk46[3];
    /* 0x4C */ s16 unk4C[10];
    /* 0x60 */ s16 unk60[10];
    /* 0x74 */ s16 unk74[10];
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ omObjData *unk8C;
    /* 0x90 */ s16 unk90[15];
    /* 0xAE */ s16 unkAE;
    /* 0xB0 */ s16 unkB0[5];
    /* 0xBA */ s16 unkBA[5];
    /* 0xC4 */ s8 unkC4[4];
    /* 0xC8 */ s8 unkC8[4];
    /* 0xCC */ char unkCC[8];
    /* 0xD4 */ s16 unkD4;
    /* 0xD6 */ char unkD6[0x1E];
} PlayerView; // Size 0xF4

typedef struct {
    /* 0x000 */ PlayerView *views;
    /* 0x004 */ char unk04[4];
    /* 0x008 */ f32 unk08;
    /* 0x00C */ char unk0C[2];
    /* 0x00E */ s16 unk0E;
    /* 0x010 */ f32 unk10; /* time left, frames */
    /* 0x014 */ s16 unk14[100]; /* item path position */
    /* 0x0DC */ s16 unkDC[100]; /* item lane */
    /* 0x1A4 */ s8 unk1A4[0x10]; /* setup counters; [8] per-view timers at [idx * 4 + i] */
    /* 0x1B4 */ s16 unk1B4[2];
    /* 0x1B8 */ char unk1B8[0xC];
    /* 0x1C4 */ f32 unk1C4;
    /* 0x1C8 */ char unk1C8[0xC];
} MinigameData;                  // Size 0x1D4

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ char unk15;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E[5];
    /* 0x28 */ s16 unk28[5];
    /* 0x32 */ s8 unk32;
    /* 0x33 */ char unk33;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char unk36[0x12];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ char unk4E[0xA];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ Vec unk68;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ u16 unk78;
    /* 0x7A */ char unk7A[2];
    /* 0x7C */ Vec unk7C;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
} D_801137C8_motor_rooter_Struct; // Size 0x8C

void m254_InitEnvironment(void);
void m254_CreateMinigame(void);
void m254_CheckExitRequest(omObjData *object);
void m254_WaitExitWipeOut(omObjData *object);
void m254_ExitOverlay(omObjData *object);
void func_80105F04_motor_rooter(void);
void func_80106044_motor_rooter(omObjData *object);
void func_80106298_motor_rooter(omObjData *object);
void func_801062BC_motor_rooter(omObjData *object);
void func_80106508_motor_rooter(omObjData *object);
void func_80106998_motor_rooter(omObjData *object);
void func_80106BAC_motor_rooter(omObjData *object);
void func_80107210_motor_rooter(omObjData *object);
void func_801079E8_motor_rooter(omObjData *object);
void m254_InitCamera(FuncContext *ctx);
void func_801082E0_motor_rooter(FuncContext *ctx);
void func_80108BF0_motor_rooter(FuncContext *ctx);
void func_80106968_motor_rooter(omObjData *object);
void func_80106B7C_motor_rooter(omObjData *object);
void func_801070CC_motor_rooter(omObjData *object);
void func_801076AC_motor_rooter(omObjData *object);
void func_80107D50_motor_rooter(omObjData *object);
void func_80108514_motor_rooter(FuncContext *ctx);
void func_801087C0_motor_rooter(FuncContext *ctx);
void func_801089B8_motor_rooter(FuncContext *ctx);
void func_80108E6C_motor_rooter(FuncContext *ctx);
void func_80108FDC_motor_rooter(FuncContext *ctx);
void func_80109134_motor_rooter(FuncContext *ctx);
void func_80109C94_motor_rooter(PlayerView *view, s16 row);
void func_80109EFC_motor_rooter(FuncContext *ctx);
void func_80017D24_main(f32 *mtx, f32 x, f32 y, f32 z);
extern s16 D_8011345A_motor_rooter[];
void func_801091A0_motor_rooter(FuncContext *ctx);
void func_8010961C_motor_rooter(FuncContext *ctx);
void func_8010972C_motor_rooter(FuncContext *ctx);
void func_8010A174_motor_rooter(FuncContext *ctx);
void func_8010A440_motor_rooter(FuncContext *ctx);
void func_8010AF0C_motor_rooter(FuncContext *ctx);
void func_8010B394_motor_rooter(FuncContext *ctx);
void func_8010ABC4_motor_rooter(FuncContext *ctx);
void func_8010BB78_motor_rooter(FuncContext *ctx);
void func_8010BCD0_motor_rooter(FuncContext *ctx);
void func_8010BDF0_motor_rooter(FuncContext *ctx);
void func_8010C084_motor_rooter(FuncContext *ctx);
void func_8010C44C_motor_rooter(FuncContext *ctx);
void func_8010C824_motor_rooter(FuncContext *ctx);
void func_8010CB2C_motor_rooter(omObjData *object, s16 arg1, s16 arg2);
void func_8010BDE4_motor_rooter(D_801137C8_motor_rooter_Struct *arg0, s16 arg1, s8 arg2);
void func_801107FC_motor_rooter(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2);
void func_801108CC_motor_rooter(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3);
extern RGBA D_80113470_motor_rooter[];
void func_8010CD84_motor_rooter(void *, s32);
s16 func_8010D03C_motor_rooter(f32);
void func_8010D0AC_motor_rooter(f32 *, s16, f32);
void func_8010D2E4_motor_rooter(s32);
s16 func_8010EFF8_motor_rooter(HuSprite_Unk84_Struct *arg0, f32 arg1);
s16 func_8010FC10_motor_rooter(HuSprite_Unk84_Struct *arg0, RGBA *arg1);

extern s16 D_80113458_motor_rooter; /* control scheme */
#define CPU_BTN ((u16 *)D_800CDA7C_main) /* input.h has s16; retail reads it as u16 */
void func_8010B970_motor_rooter(FuncContext *ctx);

extern s32 D_800A178C_main[][6];
extern D_800CCF58_main_Struct *D_800CCF58_main;
omObjData *func_80045F1C_main(u32, s16, s16);

// BSS
extern f32 *D_801137C0_motor_rooter;
extern MinigameData *m254_minigame; // D_801137C4_motor_rooter
extern D_801137C8_motor_rooter_Struct *D_801137C8_motor_rooter;
extern s16 D_801137CC_motor_rooter;
extern s16 D_801137CE_motor_rooter;
extern s16 D_801137D0_motor_rooter;
extern s16 D_801137D2_motor_rooter;
extern s16 D_801137D8_motor_rooter;
extern s16 m254_playerId[]; // D_801137D4_motor_rooter

extern s32 D_80111550_motor_rooter;
extern s32 D_8011245C_motor_rooter;

extern s16 D_801135E0_motor_rooter[];
extern s16 D_801135EC_motor_rooter[];
extern s16 D_801135FC_motor_rooter[];

void m254_OverlayMain(void) {
    m254_InitEnvironment();
}

void m254_InitEnvironment(void) {
    omObjData *temp_v0;

    Hu3DAnimInit(50);
    func_800142A0_main(0x30);
    omInitObjMan(50, 0);
    func_8004A208_main();
    temp_v0 = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    temp_v0->work[0] = 2;
    omSetStatBit(temp_v0, 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 152.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 60.0f, 40.0f, 4000.0f);
    ScissorSet(1, 168.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(1, 60.0f, 40.0f, 4000.0f);
    func_8001F38C_main(0xFF, 0xFF, 0xFF);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    m254_CreateSystem();
    m254_CreateMinigame();
    omAddObj(100, 0, 0, -1, func_80106044_motor_rooter);
    omAddObj(1000, 0, 0, -1, m254_CheckExitRequest);
    func_80045010_main(D_801135E0_motor_rooter, 1);
    func_80045010_main(D_801135EC_motor_rooter, 1);
    func_80045010_main(D_801135FC_motor_rooter, 1);
}

void m254_CreateMinigame(void) {
    s16 player1Set = FALSE;
    s16 player2Set = FALSE;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            if (!player1Set) {
                m254_playerId[0] = i;
                player1Set = TRUE;
            }
        } else if (GwPlayer[i].group == 1) {
            if (!player2Set) {
                m254_playerId[1] = i;
                player2Set = TRUE;
            }
        }
    }
    m254_minigame = HuMemAllocTag(sizeof(MinigameData), 31000);
    memset(m254_minigame, 0, sizeof(MinigameData));
    m254_minigame->views = HuMemAllocTag(PLAYERS_TOTAL * sizeof(PlayerView), 31000);
    memset(m254_minigame->views, 0, PLAYERS_TOTAL * sizeof(PlayerView));
    D_801137CE_motor_rooter = (rand16() % 201) / 100;
    switch (D_801137CE_motor_rooter) {
        case 0:
            D_801137CC_motor_rooter = 280;
            func_8010CD84_motor_rooter(&D_80111550_motor_rooter, 321);
            break;
        case 1:
            D_801137CC_motor_rooter = 300;
            func_8010CD84_motor_rooter(&D_8011245C_motor_rooter, 341);
            break;
        default:
            D_801137CC_motor_rooter = 280;
            func_8010CD84_motor_rooter(&D_80111550_motor_rooter, 321);
            D_801137CE_motor_rooter = 0;
            break;
    }
    func_8010D2E4_motor_rooter(0);
    D_801137C8_motor_rooter = HuMemAllocTag(2 * sizeof(D_801137C8_motor_rooter_Struct), 31000); // PLAYERS_TOTAL?
    memset(D_801137C8_motor_rooter, 0, 2 * sizeof(D_801137C8_motor_rooter_Struct));
}

void m254_CheckExitRequest(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        object->func = m254_WaitExitWipeOut;
    }
}

void m254_WaitExitWipeOut(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m254_ExitOverlay;
    }
}

void m254_ExitOverlay(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

/* <func_80105F04_motor_rooter> */
void func_80105F04_motor_rooter(void) {
    s16 i;

    for (i = 0; i < PLAYERS_TOTAL; i++) {
        if (CRotM[i].x > 360.0f) {
            CRotM[i].x -= 360.0f;
        } else if (CRotM[i].x < 0.0f) {
            CRotM[i].x += 360.0f;
        }
        if (CRotM[i].y > 360.0f) {
            CRotM[i].y -= 360.0f;
        } else if (CRotM[i].y < 0.0f) {
            CRotM[i].y += 360.0f;
        }
    }
    m254_UpdateFuncGroup(FGRP_CAMERA);
}
/* </func_80105F04_motor_rooter> */

void func_80106044_motor_rooter(omObjData *object) {
    s16 i;

    func_8001EF24_main(0x3CA, 1000, 0xFF, 0xFF, 0xFF);
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    for (i = 0; i < 2; i++) {
        D_800EC1C0_minigame[i] = omAddObj(10, 2, 0, -1, func_801062BC_motor_rooter);
        m254_minigame->views[i].unk00 = omAddObj(100, 21, 0, -1, func_80106508_motor_rooter);
        m254_minigame->views[i].unk8C = omAddObj(200, 15, 0, -1, func_80106998_motor_rooter);
        omAddObj(500, 1, 0, -1, func_80107210_motor_rooter);
        omAddObj(800, 5, 0, -1, func_801079E8_motor_rooter);
        D_800EC598_minigame[i] = D_801137C8_motor_rooter[i].unk00 = omAddObj(300, 11, 40, -1, func_80106BAC_motor_rooter);
    }
    memset(m254_minigame->unk1A4, 0, 0x30); // unk1A4 through unk1C8 (0x30 bytes)
    m254_SetFunc(FGRP_CAMERA, 0, -1, NULL, m254_InitCamera, 0, FALSE);
    m254_SetFunc(1, 0, -1, NULL, func_80108BF0_motor_rooter, 0, FALSE);
    WipeCreateIn(0xFF, 0x10);
    object->func = func_80106298_motor_rooter;
}

/* <func_80106298_motor_rooter> */
void func_80106298_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(1);
    func_80105F04_motor_rooter();
}
/* </func_80106298_motor_rooter> */

/* <func_801062BC_motor_rooter> */
typedef struct {
    s32 f[2][2];
} MrFileTbl;
extern MrFileTbl D_80113608_motor_rooter;
void func_801064EC_motor_rooter(omObjData *object);

void func_801062BC_motor_rooter(omObjData *object) {
    s32 attr = 0x99;
    MrFileTbl files = D_80113608_motor_rooter;
    s16 counts[2] = { 2, 2 };
    s16 var_a1;
    s16 i;

    object->work[0] = m254_minigame->unk1A4[0];
    for (i = 0; i < counts[D_801137CE_motor_rooter]; i++) {
        if (object->work[0] == 0) {
            object->model[i] = func_8000B108_main(files.f[D_801137CE_motor_rooter][i] | 0x570000, attr);
        } else {
            object->model[i] = Hu3DModelLink(D_800EC1C0_minigame[0]->model[i]);
        }
        Hu3DModelPosSet(object->model[i], 0.0f, 0.0f, 0.0f);
    }
    m254_SyncWithModel(object);
    var_a1 = 2;
    if (object->work[0] == 0) {
        var_a1 = 1;
    }
    for (i = 0; i < counts[D_801137CE_motor_rooter]; i++) {
        func_8001C8A8_main(object->model[i], var_a1);
    }
    m254_minigame->unk1A4[0]++;
    object->func = func_801064EC_motor_rooter;
}
/* </func_801062BC_motor_rooter> */

/* <func_801064EC_motor_rooter> */
void func_801064EC_motor_rooter(omObjData *object) {
    m254_SyncWithModel(object);
}
/* </func_801064EC_motor_rooter> */

/* <func_80106508_motor_rooter> */
#ifdef NON_MATCHING
typedef struct {
    s32 f[7];
} MrFileTbl7;
extern MrFileTbl7 D_80113618_motor_rooter;
void func_80106968_motor_rooter(omObjData *object);
void func_801091A0_motor_rooter(FuncContext *ctx);
void func_8010961C_motor_rooter(FuncContext *ctx);
void func_8010972C_motor_rooter(FuncContext *ctx);
void func_80109C94_motor_rooter(PlayerView *view, s16 row);

void func_80106508_motor_rooter(omObjData *object) {
    s32 files[7];
    PlayerView *view;
    FuncContext *ctx;
    s16 id;
    s16 var_a1;
    s16 i;
    s16 j;
    s32 dir = 0x570000;

    *(MrFileTbl7 *)files = D_80113618_motor_rooter;

    view = &m254_minigame->views[object->work[0] = m254_minigame->unk1A4[1]];
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 7; i++) {
            id = func_8000B838_main(files[i] | dir);
            m254_minigame->views[object->work[0]].unk04[j][i] = id;
            object->model[j * 7 + i] = func_8010EFF8_motor_rooter(func_80055194_main(id), 1.0f);
            Hu3DModelScaleSet(object->model[j * 7 + i], 2.0f, 2.0f, 2.0f);
        }
        view->unk2E[j] = view->unk88++;
        if (view->unk88 > D_801137D2_motor_rooter) {
            for (i = j * 7; i < j * 7 + 7; i++) {
                func_8001C258_main(object->model[i], 4, 4);
            }
            view->unk2E[j] = -1;
        } else {
            func_80109C94_motor_rooter(view, j);
        }
        view->unk46[j] = rand16() % 3;
    }
    var_a1 = 2;
    if (object->work[0] == 0) {
        var_a1 = 1;
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 7; i++) {
            func_8001C8A8_main(object->model[j * 7 + i], var_a1);
        }
    }
    m254_minigame->unk1A4[1]++;
    m254_SetFunc(2, 6, -1, &m254_minigame->views[object->work[0]], func_8010961C_motor_rooter, (s8)object->work[0], FALSE);
    ctx = m254_SetFunc(2, 7, -1, &m254_minigame->views[object->work[0]], func_8010972C_motor_rooter, (s8)object->work[0], FALSE);
    for (i = 0; i < 3; i++) {
        ctx->work.s16[0] = i;
        func_801091A0_motor_rooter(ctx);
    }
    m254_SyncWithModel(object);
    object->func = func_80106968_motor_rooter;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80106508_motor_rooter);
#endif
/* </func_80106508_motor_rooter> */

/* <func_80106968_motor_rooter> */
void func_80106968_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(2);
    m254_SyncWithModel(object);
}
/* </func_80106968_motor_rooter> */

/* <func_80106998_motor_rooter> */
void func_80106B7C_motor_rooter(omObjData *object);
void func_8010A174_motor_rooter(FuncContext *ctx);

void func_80106998_motor_rooter(omObjData *object) {
    PlayerView *view;
    s16 var_a1;
    s16 i;
    s32 attr = 0x99;

    view = &m254_minigame->views[object->work[0] = m254_minigame->unk1A4[3]];
    for (i = 0; i < 15; i++) {
        if (object->work[0] == 0) {
            object->model[i] = func_8000B108_main(0x570002, attr);
        } else {
            object->model[i] = Hu3DModelLink(m254_minigame->views[0].unk8C->model[i]);
        }
        view->unk90[i] = view->unkAE++;
        Hu3DModelScaleSet(object->model[i], 0.7f, 0.7f, 0.7f);
    }
    m254_SyncWithModel(object);
    var_a1 = 2;
    if (object->work[0] == 0) {
        var_a1 = 1;
    }
    for (i = 0; i < 15; i++) {
        func_8001C8A8_main(object->model[i], var_a1);
    }
    m254_minigame->unk1A4[3]++;
    m254_SetFunc(3, 5, -1, object, func_8010A174_motor_rooter, 0, FALSE);
    object->func = func_80106B7C_motor_rooter;
}
/* </func_80106998_motor_rooter> */

/* <func_80106B7C_motor_rooter> */
void func_80106B7C_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(3);
    m254_SyncWithModel(object);
}
/* </func_80106B7C_motor_rooter> */

/* <func_80106BAC_motor_rooter> */
#ifdef NON_MATCHING
void func_801070CC_motor_rooter(omObjData *object);
void func_8010ABC4_motor_rooter(FuncContext *ctx);
void func_8010BB78_motor_rooter(FuncContext *ctx);
void func_8010BCD0_motor_rooter(FuncContext *ctx);
void func_8010BDE4_motor_rooter(D_801137C8_motor_rooter_Struct *arg0, s16 arg1, s8 arg2);

void func_80106BAC_motor_rooter(omObjData *object) {
    s32 files[2] = { 0, 1 };
    s16 var_a1;
    s16 i;
    u8 chr;
    s16 player;

    object->work[0] = D_800EC280_minigame;
    player = object->work[1] = m254_playerId[D_800EC280_minigame];
    chr = GwPlayer[player].chr;
    func_800E1BA8_minigame(object, D_800A178C_main[GwPlayer[player].chr][0],
                           D_800A178C_main[GwPlayer[player].chr][2], object->work[1], 0x289, 0x299);
    func_8001C258_main(object->model[1], 4, 4);
    Hu3DModelScaleSet(object->model[1], 0.2f, 0.2f, 0.2f);
    object->model[9] = func_8000B108_main(files[object->work[0]] | 0x570000, 0x299);
    func_8001C258_main(object->model[9], 4, 0);
    object->model[10] = func_8000B108_main(9, 0x99);
    Hu3DModelScaleSet(object->model[10], 0.4f, 0.4f, 0.4f);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(object, 13, func_80017BB8_main(chr, 0x2F), 1, 999);
    func_800E5A00_minigame(object, 21, func_80017BB8_main(chr, 0x1F), 1, 999);
    func_800E5A00_minigame(object, 38, func_80017BB8_main(chr, 0x27), 1, 0);
    func_800E5A00_minigame(object, 39, func_80017BB8_main(chr, 0x28), 1, 99);
    object->trans.x = 0.0f;
    object->trans.y = -56.0f;
    object->trans.z = 100.0f;
    object->rot.y = 180.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.2f;
    Hu3DModelPosSet(object->model[9], 0.0f, 0.0f, 200.0f);
    Hu3DModelRotSet(object->model[9], 0.0f, 180.0f, 0.0f);
    func_8001C258_main(object->model[10], 4, 4);
    func_8010BDE4_motor_rooter(&D_801137C8_motor_rooter[object->work[0]], 0x26, 1);
    D_800EC280_minigame++;
    D_801137C8_motor_rooter[object->work[0]].unk08 = 1;
    D_801137C8_motor_rooter[object->work[0]].unk04 = ((func_800E1BA8_minigame_ObjData *)object->data)->unk57;
    D_801137C8_motor_rooter[object->work[0]].unk16 = 0;
    D_801137C8_motor_rooter[object->work[0]].unk14 = 1;
    var_a1 = 2;
    if (object->work[0] == 0) {
        var_a1 = 1;
    }
    for (i = 0; i < 11; i++) {
        func_8001C8A8_main(object->model[i], var_a1);
    }
    m254_SetFunc(object->work[0] + 4, 5, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010ABC4_motor_rooter, 0, FALSE);
    m254_SetFunc(object->work[0] + 4, 9, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010BCD0_motor_rooter, 0, FALSE);
    m254_SetFunc(object->work[0] + 4, 4, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010BB78_motor_rooter, 0, FALSE);
    object->func = func_801070CC_motor_rooter;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80106BAC_motor_rooter);
#endif
/* </func_80106BAC_motor_rooter> */

/* <func_801070CC_motor_rooter> */
void func_801070CC_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(object->work[0] + 4);
    func_800E4E30_minigame(object);
    if (object->rot.x >= 360.0f) {
        object->rot.x -= 360.0f;
    }
    if (object->rot.x < 0.0f) {
        object->rot.x += 360.0f;
    }
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (object->rot.y < 0.0f) {
        object->rot.y += 360.0f;
    }
    if (object->rot.z >= 360.0f) {
        object->rot.z -= 360.0f;
    }
    if (object->rot.z < 0.0f) {
        object->rot.z += 360.0f;
    }
}
/* </func_801070CC_motor_rooter> */

/* <func_80107210_motor_rooter> */
#ifdef NON_MATCHING
typedef struct {
    s32 f[8];
} MrFileTbl8;
extern MrFileTbl8 D_80113634_motor_rooter;
void func_801076AC_motor_rooter(omObjData *object);

void func_80107210_motor_rooter(omObjData *object) {
    MrFileTbl8 files = D_80113634_motor_rooter;
    f32 y;
    s16 sprId;
    s16 x;
    s16 i;

    object->work[0] = m254_minigame->unk1A4[2];
    object->work[1] = m254_playerId[object->work[0]];
    m254_SetSpriteDispOn(m254_SetSprite(0xFFFF, 0x57, 7, 0, 0), 160, 120);
    for (i = 0; i < 5; i++) {
        sprId = m254_SetSprite(0xFFFF, 0x21, 0x18, 0, 0);
        if (object->work[0] == 0) {
            x = i * 10 + 35;
        } else {
            x = 285 - i * 10;
        }
        m254_SetSpriteDispOn(sprId, x, 25);
    }
    for (i = 0; i < 5; i++) {
        sprId = m254_SetSprite(0xFFF, 0x21, 0x19, 0, 0x1000);
        D_801137C8_motor_rooter[object->work[0]].unk1E[i] = sprId;
        if (object->work[0] == 0) {
            x = i * 10 + 35;
        } else {
            x = 285 - (4 - i) * 10;
        }
        m254_SetSpriteDispOn(sprId, x, 25);
        if (i == 0) {
            m254_sprites[sprId].unk06 = 0xFF;
        } else {
            m254_sprites[sprId].unk06 = 0;
        }
        func_80055458_main(m254_sprites[sprId].groupId, 0, (u8)m254_sprites[sprId].unk06);
        D_801137C8_motor_rooter[object->work[0]].unk28[i] = 0;
    }
    sprId = m254_SetSprite(0xFFF, 0x21, files.f[GwPlayer[m254_playerId[object->work[0]]].chr], 0, 0);
    D_801137C8_motor_rooter[object->work[0]].unk4A = sprId;
    m254_SetSpriteDispOn(sprId, (s16)(object->work[0] * 16 + 152), 220);
    for (i = 0; i < D_801137D2_motor_rooter; i++) {
        y = 220 - (s16)(D_801137C0_motor_rooter[m254_minigame->views[object->work[0]].unk4C[i] * 9 + 8] /
                         m254_minigame->unk08 * 180.0f);
        m254_SetSpriteDispOn(m254_SetSprite(0xEFFF, 0x57, 0x11, 0, 0), (s16)(object->work[0] * 16 + 152), (s16)y);
    }
    m254_minigame->unk1A4[2]++;
    object->func = func_801076AC_motor_rooter;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80107210_motor_rooter);
#endif
/* </func_80107210_motor_rooter> */

/* <func_801076AC_motor_rooter> */
#ifdef NON_MATCHING
extern s8 D_80113468_motor_rooter[];
extern s8 D_8011346C_motor_rooter[];

void func_801076AC_motor_rooter(omObjData *object) {
    D_801137C8_motor_rooter_Struct *work = D_801137C8_motor_rooter;
    SpriteData *sprite;
    s16 busy;
    s16 i;
    s16 j;

    for (j = 0; j < 2; j++, work++) {
        busy = FALSE;
        for (i = 0; i < 5; i++) {
            if (work->unk28[i] != 0) {
                busy = TRUE;
            }
        }
        if (!busy && work->unk14 == 5) {
            if (D_80113468_motor_rooter[j] == 0) {
                for (i = 0; i < 5; i++) {
                    func_80055458_main(m254_sprites[work->unk1E[i]].groupId, 0, 0);
                }
                if (++D_8011346C_motor_rooter[j] >= 3) {
                    D_8011346C_motor_rooter[j] = 0;
                    D_80113468_motor_rooter[j] = 1;
                }
            } else {
                for (i = 0; i < 5; i++) {
                    func_80055458_main(m254_sprites[work->unk1E[i]].groupId, 0, 0xFF);
                }
                if (++D_8011346C_motor_rooter[j] >= 3) {
                    D_8011346C_motor_rooter[j] = 0;
                    D_80113468_motor_rooter[j] = 0;
                }
            }
        } else {
            for (i = 0; i < 5; i++) {
                sprite = &m254_sprites[work->unk1E[i]];
                if (work->unk28[i] != 0) {
                    if (work->unk28[i] == 1) {
                        sprite->unk06 += 10;
                        if (sprite->unk06 >= 0xFF) {
                            sprite->unk06 = 0xFF;
                            work->unk28[i] = 0;
                        }
                    } else {
                        sprite->unk06 -= 10;
                        if (sprite->unk06 <= 0) {
                            sprite->unk06 = 0;
                            work->unk28[i] = 0;
                        }
                    }
                }
                func_80055458_main(sprite->groupId, 0, (u8)sprite->unk06);
            }
        }
        if (!(work->unk08 & 0x40)) {
            m254_SetSpriteDispOn(work->unk4A, (s16)(j * 16 + 152),
                                 (s16)(220 - (s32)(work->unk0C / m254_minigame->unk08 * 180.0f)));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801076AC_motor_rooter);
#endif
/* </func_801076AC_motor_rooter> */

/* <func_801079E8_motor_rooter> */
#ifdef NON_MATCHING
void func_801079E8_motor_rooter(omObjData *object) {
    s16 var_a1;
    s16 i;

    object->work[0] = m254_minigame->unk1A4[6];
    for (i = 0; i < 4; i++) {
        object->model[i] = func_8010FC10_motor_rooter(
            func_80055194_main(m254_minigame->views[object->work[0]].unkB0[i] = func_8000B838_main(0x570010)),
            D_80113470_motor_rooter);
        Hu3DModelScaleSet(object->model[i], 2.0f, 2.0f, 1.0f);
        func_8001C258_main(object->model[i], 4, 4);
        m254_minigame->views[object->work[0]].unkBA[i] = 0;
        m254_minigame->views[object->work[0]].unkC4[i] = rand16() % 11;
        m254_minigame->views[object->work[0]].unkC8[i] = 0;
    }
    m254_minigame->views[object->work[0]].unkD4 = 0;
    object->model[i] = func_8010EFF8_motor_rooter(
        func_80055194_main(m254_minigame->views[object->work[0]].unkB0[i] = func_8000B838_main(0x57000F)), 1.0f);
    Hu3DModelScaleSet(object->model[i], 1.5f, 1.5f, 1.0f);
    func_8001C258_main(object->model[i], 4, 4);
    m254_minigame->views[object->work[0]].unkBA[i] = 0;
    m254_SyncWithModel(object);
    var_a1 = 2;
    if (object->work[0] == 0) {
        var_a1 = 1;
    }
    for (i = 0; i < 5; i++) {
        func_8001C8A8_main(object->model[i], var_a1);
    }
    m254_minigame->unk1A4[6]++;
    object->func = func_80107D50_motor_rooter;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801079E8_motor_rooter);
#endif
/* </func_801079E8_motor_rooter> */

/* <func_80107D50_motor_rooter> */
#ifdef NON_MATCHING
void func_80107D50_motor_rooter(omObjData *object) {
    PlayerView *view;
    D_801137C8_motor_rooter_Struct *work;
    s16 idx;
    s16 i;
    s16 j;

    idx = object->work[0];
    view = &m254_minigame->views[idx];
    work = &D_801137C8_motor_rooter[idx];
    i = 0;

    if (work->unk10 == 0.0f) {
        do {
            func_8001C258_main(object->model[i], 4, 4);
        } while (++i < 5);
        return;
    }
    if (work->unk78 & 4) {
        do {
            if (view->unkC4[i] != 99 && view->unkC4[i] < ++m254_minigame->unk1A4[idx * 4 + i]) {
                func_8001C258_main(object->model[i], 4, 0);
                func_8010CB2C_motor_rooter(object, 4, i);
                func_801108CC_motor_rooter(object->model[i], func_80055194_main(view->unkB0[i]), view->unkBA[i],
                                           D_80113470_motor_rooter);
                if (++view->unkBA[i] >= 15) {
                    if (view->unkC8[i] == 0) {
                        view->unkC8[i] = 1;
                        view->unkBA[i] = 0;
                    } else {
                        func_8001C258_main(object->model[i], 4, 4);
                        m254_minigame->unk1A4[idx * 4 + i] = 0;
                        view->unkC4[i] = 99;
                        view->unkBA[i] = 0;
                        if (++view->unkD4 >= 4) {
                            for (j = 0; j < 4; j++) {
                                view->unkC8[j] = 0;
                                view->unkC4[j] = rand16() % 11;
                            }
                            work->unk78 &= ~4;
                        }
                    }
                }
            }
        } while (++i < 4);
    } else if (work->unk78 & 1) {
        func_8001C258_main(object->model[0], 4, 0);
        func_8010CB2C_motor_rooter(object, 1, 0);
        func_801108CC_motor_rooter(object->model[0], func_80055194_main(view->unkB0[0]), view->unkBA[0],
                                   D_80113470_motor_rooter);
        if (++view->unkBA[0] >= 15) {
            func_8001C258_main(object->model[0], 4, 4);
            work->unk78 &= ~1;
            view->unkBA[0] = 0;
        }
    }
    if (work->unk78 & 2) {
        func_8001C258_main(object->model[4], 4, 0);
        func_8010CB2C_motor_rooter(object, 2, 4);
        func_801107FC_motor_rooter(object->model[4], func_80055194_main(view->unkB0[4]), view->unkBA[4]);
        if (++m254_minigame->unk1B4[object->work[0]] >= 2) {
            m254_minigame->unk1B4[object->work[0]] = 0;
            if (++view->unkBA[4] >= 5) {
                func_8001C258_main(object->model[4], 4, 4);
                work->unk78 &= ~2;
                view->unkBA[4] = 0;
            }
        }
    }
    m254_SyncWithModel(object);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80107D50_motor_rooter);
#endif
/* </func_80107D50_motor_rooter> */

void m254_InitCamera(FuncContext *ctx) {
    s16 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 100.0f;
        CenterM[i].x = D_801137C0_motor_rooter[0];
        CenterM[i].y = D_801137C0_motor_rooter[1];
        CenterM[i].z = D_801137C0_motor_rooter[2];
        CRotM[i].x = D_801137C0_motor_rooter[3] - 180.0f;
        CRotM[i].y = D_801137C0_motor_rooter[4];
        CRotM[i].z = D_801137C0_motor_rooter[5];
    }
    m254_ResetFunc(FGRP_CAMERA, ctx);
    m254_SetFunc(FGRP_CAMERA, 0, -1, NULL, func_801082E0_motor_rooter, 0, FALSE);
}

void func_801082E0_motor_rooter(FuncContext *ctx) {
    PlayerView *view;
    D_801137C8_motor_rooter_Struct *var_s1;
    f32 sp10[7];
    s16 temp_v0;
    s16 i;

    view = m254_minigame->views;
    var_s1 = D_801137C8_motor_rooter;
    for (i = 0; i < 2; i++, var_s1++, view++) {
        if (var_s1->unk08 & 0x80) {
            continue;
        }
        temp_v0 = func_8010D03C_motor_rooter(var_s1->unk0C);
        func_8010D0AC_motor_rooter(sp10, temp_v0, var_s1->unk0C);
        CenterM[i].x = sp10[1];
        CenterM[i].y = sp10[2];
        CenterM[i].z = sp10[3];
        CRotM[i].x = sp10[4] - 180.0f;
        CRotM[i].y = sp10[5];
        CRotM[i].z = sp10[6];
        if (CRotM[i].x > 360.0f) {
            CRotM[i].x -= 360.0f;
        } else if (CRotM[i].x < 0.0f) {
            CRotM[i].x += 360.0f;
        }
        if (CRotM[i].y > 360.0f) {
            CRotM[i].y -= 360.0f;
        } else if (CRotM[i].y < 0.0f) {
            CRotM[i].y += 360.0f;
        }
        var_s1->unk1C = temp_v0 + 1;
        view->unk8A = temp_v0;
    }
}

/* <func_80108514_motor_rooter> */
#ifdef NON_MATCHING
extern f64 D_80113658_motor_rooter; /* 90.0 */
extern f64 D_80113660_motor_rooter; /* 30.0 */
extern s32 D_80113474_motor_rooter[];
void func_80108E6C_motor_rooter(FuncContext *ctx);

void func_80108514_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;
    omObjData *object = work->unk00;
    s16 idx = object->work[0];
    f32 buf[7];
    f32 t;
    f64 off;

    if (ctx->state == 0) {
        off = D_80113658_motor_rooter;
        func_8010D0AC_motor_rooter(buf, func_8010D03C_motor_rooter(work->unk0C + off), work->unk0C + off);
        ctx->work.f32[0] = buf[1];
        ctx->work.f32[1] = buf[2] - D_80113660_motor_rooter;
        ctx->work.f32[2] = buf[3];
        work->unk58 = CenterM[idx].x;
        work->unk5C = CenterM[idx].y;
        work->unk60 = CenterM[idx].z;
        ctx->work.s8[0] = ctx->work.s8[1] = ctx->work.s8[2] = 0;
        ctx->state = 1;
    }
    t = sindf(ctx->work.s8[0] / 30.0f * 90.0f);
    if (t > 1.0f) {
        t = 1.0f;
    }
    CenterM[idx].x = (ctx->work.f32[0] - work->unk58) * t + work->unk58;
    CenterM[idx].y = (ctx->work.f32[1] - work->unk5C) * t + work->unk5C;
    CenterM[idx].z = (ctx->work.f32[2] - work->unk60) * t + work->unk60;
    if (++ctx->work.s8[0] > 30) {
        func_80017790_main(object->model[0], 2, GwPlayer[m254_playerId[object->work[0]]].chr,
                           D_80113474_motor_rooter[GwPlayer[m254_playerId[object->work[0]]].chr]);
        func_8010BDE4_motor_rooter(work, 13, 1);
        m254_ResetFunc(0, ctx);
        m254_SetFunc(1, 0, -1, work, func_80108E6C_motor_rooter, 0, FALSE);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80108514_motor_rooter);
#endif
/* </func_80108514_motor_rooter> */

/* <func_801087C0_motor_rooter> */
#ifdef NON_MATCHING
void func_801087C0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work;
    s16 hits[8];
    s16 count;
    s16 i;
    s16 winner;
    s16 loser;

    work = D_801137C8_motor_rooter;
    count = 0;
    hits[0] = -1;
    hits[1] = -1;
    for (i = 0; i < 2; i++, work++) {
        if (!(work->unk08 & 0x40) && work->unk1C == D_801137CC_motor_rooter) {
            hits[count] = i;
            count++;
        }
    }
    if (count != 0) {
        if (count == 2) {
            winner = rand16() & 1;
        } else {
            winner = hits[0];
        }
        D_801137C8_motor_rooter[winner].unk08 |= 0x50;
        loser = winner == 0;
        D_801137C8_motor_rooter[loser].unk08 |= 0x41;
        HuAudSeqFadeOut(120);
        GMesCreate(0x11);
        func_8003F5C0_main();
        m254_minigame->unk1C4 = 99.0f;
        m254_SetFunc(D_801137C8_motor_rooter[winner].unk00->work[0] + 4, 5, -1, &D_801137C8_motor_rooter[winner],
                     func_8010C084_motor_rooter, 0, FALSE);
        m254_SetFunc(D_801137C8_motor_rooter[loser].unk00->work[0] + 4, 5, -1, &D_801137C8_motor_rooter[loser],
                     func_8010C824_motor_rooter, 0, FALSE);
        m254_ResetFunc(1, ctx);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801087C0_motor_rooter);
#endif
/* </func_801087C0_motor_rooter> */

/* <func_801089B8_motor_rooter> */
#ifdef NON_MATCHING
extern f64 D_80113668_motor_rooter; /* 60.0 */
void func_80108FDC_motor_rooter(FuncContext *ctx);
void func_8010C824_motor_rooter(FuncContext *ctx);

void func_801089B8_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work;
    s16 i;

    switch (ctx->state) {
    case 0:
        m254_minigame->unk10 = 1800.0f;
        GMesCreate(0x1A, D_80113668_motor_rooter, 160, 28);
        func_8003F578_main((m254_minigame->unk10 + 29.0f) / 30.0f);
        ctx->state = 1;
        break;
    case 1:
        if (m254_minigame->unk1C4 == 99.0f) {
            break;
        }
        m254_minigame->unk10 -= 1.0f;
        func_8003F578_main((m254_minigame->unk10 + 29.0f) * 0.033333335f);
        if (m254_minigame->unk10 < 0.0f) {
            func_8003F5C0_main();
            m254_ResetFunc(1, ctx);
            m254_SetFunc(1, 0, -1, NULL, func_80108FDC_motor_rooter, 0, FALSE);
            for (i = 0; i < 2; i++) {
                work = &D_801137C8_motor_rooter[i];
                work->unk08 |= 0x41;
                m254_SetFunc(work->unk00->work[0] + 4, 5, -1, work, func_8010C824_motor_rooter, 0, FALSE);
            }
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801089B8_motor_rooter);
#endif
/* </func_801089B8_motor_rooter> */

/* <func_80108BF0_motor_rooter> */
extern s16 D_80113494_motor_rooter;
void func_8010A440_motor_rooter(FuncContext *ctx);
void func_8010AF0C_motor_rooter(FuncContext *ctx);
void func_8010B394_motor_rooter(FuncContext *ctx);
void func_8010BDF0_motor_rooter(FuncContext *ctx);

void func_80108BF0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = D_801137C8_motor_rooter;
    s16 i;

    if (ctx->state == 0) {
        ctx->work.s16[0] = 0;
        ctx->state = 1;
    }
    switch (++ctx->work.s16[0]) {
    case 10:
        for (i = 0; i < 2; i++, work++) {
            m254_SetFunc(i + 4, 0, -1, work, func_8010BDF0_motor_rooter, 0, FALSE);
        }
        break;
    case 110:
        GMesCreate(6);
        HuAudFXPlay(14);
        HuAudSeqPlay(55);
        break;
    case 130:
        D_80113494_motor_rooter = 1;
        break;
    default:
        if (D_80113494_motor_rooter != 0 && GMesStatGet() == 2) {
            m254_SetFunc(1, 0, -1, NULL, func_801089B8_motor_rooter, 0, FALSE);
            for (i = 0; i < 2; i++, work++) {
                work->unk08 = (work->unk08 & ~1) | 0x120;
                work->unk10 = 1.0f;
                work->unk4C = 0;
                if (GwPlayer[m254_playerId[i]].stat & 1) {
                    work->unk06 = 1;
                    m254_SetFunc(i + 4, 0, -1, work, func_8010A440_motor_rooter, 0, FALSE);
                } else {
                    work->unk06 = 0;
                }
            }
            m254_ResetFunc(1, ctx);
            m254_SetFunc(1, 1, -1, NULL, func_801087C0_motor_rooter, 0, FALSE);
        }
        break;
    }
}
/* </func_80108BF0_motor_rooter> */

/* <func_80108E6C_motor_rooter> */
extern s16 D_80113496_motor_rooter;

void func_80108E6C_motor_rooter(FuncContext *ctx) {
    omObjData *object = ((D_801137C8_motor_rooter_Struct *)ctx->data)->unk00;
    s16 t;

    if (D_80113496_motor_rooter >= 2) {
        if (GMesStatGet() == 0) {
            D_80113496_motor_rooter = 3;
        }
        if (D_80113496_motor_rooter == 3) {
            if (++ctx->work.s16[0] >= 15) {
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 0, -1, NULL, func_80109134_motor_rooter, 0, TRUE);
            }
        }
    } else {
        t = ctx->work.s16[0];
        ctx->work.s16[0] = t + 1;
        if (t == 0) {
            HuAudSeqPlay(0x67);
            GMesCreate(0x16, GwPlayer[m254_playerId[object->work[0]]].chr);
            GwPlayer[m254_playerId[object->work[0]]].bonusCoin += 10;
        }
        if (GMesStatGet() != 0) {
            ctx->work.s16[0] = 0;
            D_80113496_motor_rooter = 2;
        }
    }
}
/* </func_80108E6C_motor_rooter> */

/* <func_80108FDC_motor_rooter> */
extern s16 D_80113498_motor_rooter;

void func_80108FDC_motor_rooter(FuncContext *ctx) {
    s16 t;

    if (D_80113498_motor_rooter >= 2) {
        if (GMesStatGet() == 0) {
            D_80113498_motor_rooter = 3;
        }
        if (D_80113498_motor_rooter == 3) {
            if (++ctx->work.s16[0] >= 15) {
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 0, -1, NULL, func_80109134_motor_rooter, 0, TRUE);
            }
        }
    } else if (D_80113498_motor_rooter == 1) {
        t = ctx->work.s16[0]++;
        if (t == 15) {
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
        }
        if (GMesStatGet() != 0) {
            ctx->work.s16[0] = 0;
            D_80113498_motor_rooter = 2;
        }
    } else {
        t = ctx->work.s16[0];
        ctx->work.s16[0] = t + 1;
        if (t == 0) {
            HuAudSeqFadeOut(120);
            GMesCreate(0x11);
            return;
        }
        if (GMesStatGet() == 0) {
            ctx->work.s16[0] = 0;
            D_80113498_motor_rooter = 1;
        }
    }
}
/* </func_80108FDC_motor_rooter> */

/* <func_80109134_motor_rooter> */
void func_80109134_motor_rooter(FuncContext *ctx) {
    switch (ctx->state) {
    case 0:
        WipeCreateOut(0, 20);
        ctx->state = 1;
        break;
    case 1:
        if (WipeStatGet() == 0) {
            omOvlReturnEx(1);
        }
        break;
    }
}
/* </func_80109134_motor_rooter> */

/* <func_801091A0_motor_rooter> */
typedef struct {
    s16 v[7];
} MrS16x7;
extern MrS16x7 D_80113670_motor_rooter;
extern MrS16x7 D_80113680_motor_rooter;
extern MrS16x7 D_80113690_motor_rooter;
extern MrS16x7 D_801136A0_motor_rooter;

void func_801091A0_motor_rooter(FuncContext *ctx) {
    f32 rotX[16];
    f32 rotY[16];
    f32 mtx[16];
    Vec ofs;
    Vec out;
    MrS16x7 tbl0;
    MrS16x7 tbl2;
    MrS16x7 tbl3;
    MrS16x7 tbl1;
    PlayerView *view;
    omObjData *object;
    HmfModel *model;
    f32 *path;
    f32 angle;
    f32 pitch;
    s16 k;
    s16 pos;
    s16 i;

    view = ctx->data;
    object = view->unk00;
    pos = 0;
    tbl0 = D_80113670_motor_rooter;
    tbl2 = D_80113680_motor_rooter;
    tbl3 = D_80113690_motor_rooter;
    tbl1 = D_801136A0_motor_rooter;
    k = view->unk2E[ctx->work.s16[0]];
    for (i = 0; i < 7; i++) {
        model = &HmfModelData[object->model[ctx->work.s16[0] * 7 + i]];
        switch (view->unk74[k]) {
        case 0:
            pos = view->unk60[k] + tbl0.v[i];
            break;
        case 1:
            pos = view->unk60[k] + tbl1.v[i];
            break;
        case 2:
            pos = view->unk60[k] + tbl2.v[i];
            break;
        case 3:
            pos = view->unk60[k] + tbl3.v[i];
            break;
        }
        if (pos > 50) {
            Hu3DModelPosSet(object->model[ctx->work.s16[0] * 7 + i], 0.0f, 200.0f, 0.0f);
            func_8001C258_main(object->model[ctx->work.s16[0] * 7 + i], 4, 4);
            continue;
        }
        if (pos >= 8) {
            pos -= 8;
        }
        if (pos < 0) {
            pos += 8;
        }
        angle = pos * 45.0f;
        ofs.x = sindf(angle) * 55.9999990463256836;
        ofs.y = -cosdf(angle) * 55.9999990463256836;
        ofs.z = 0;
        path = &D_801137C0_motor_rooter[view->unk4C[k] * 9];
        pitch = path[3] - 180.0f;
        m254_MakeRotXMtx(rotX, pitch);
        m254_MakeRotYMtx(rotY, path[4]);
        m254_MultiplyMtx(rotX, rotY, mtx);
        func_801114B0_motor_rooter(mtx, &ofs, &out.x);
        model->pos.x = path[0] + out.x;
        model->pos.y = path[1] + out.y;
        model->pos.z = path[2] + out.z;
        model->rot.x = pitch;
        model->rot.y = path[4];
        m254_MakeIdentityMtx(model->mtx);
        func_80017D24_main(model->mtx, 0.0f, 0.0f, angle);
    }
}
/* </func_801091A0_motor_rooter> */

/* <func_8010961C_motor_rooter> */
void func_8010961C_motor_rooter(FuncContext *ctx) {
    PlayerView *view = ctx->data;
    omObjData *object = view->unk00;
    s16 i;
    s16 j;

    for (j = 0, i = 0; j < 3; j++, i = 0) {
        do {
            func_801107FC_motor_rooter(object->model[j * 7 + i], func_80055194_main(view->unk04[0][j * 7 + i]),
                                       view->unk46[j]);
        } while (++i < 7);
        view->unk46[j] = (view->unk46[j] + 1 >= 5) ? 0 : view->unk46[j] + 1;
    }
}
/* </func_8010961C_motor_rooter> */

/* <func_8010972C_motor_rooter> */
#ifdef NON_MATCHING
void func_8010972C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = &D_801137C8_motor_rooter[ctx->tag];
    PlayerView *view = ctx->data;
    omObjData *object = view->unk00;
    s16 nearest = 9999;
    s16 dist;
    s16 k;
    s16 i;
    s16 j;
    s16 n;

    for (j = 0; j < 3; j++) {
        k = view->unk2E[j];
        if (k == -1) {
            continue;
        }
        if (view->unk4C[k] - work->unk1C < m254_minigame->unk0E) {
            for (i = j * 7; i < j * 7 + 7; i++) {
                func_8001C258_main(object->model[i], 4, 0);
            }
        } else {
            for (i = j * 7; i < j * 7 + 7; i++) {
                func_8001C258_main(object->model[i], 4, 4);
            }
        }
        if (view->unk4C[k] - work->unk1C < nearest) {
            nearest = view->unk4C[k] - work->unk1C;
        }
        ctx->work.s16[0] = j;
        if (!(work->unk08 & 0x42) && work->unk1C == view->unk4C[k]) {
            if (work->unk16 != view->unk34[j][0] && work->unk16 != view->unk34[j][1] &&
                work->unk16 != view->unk34[j][2]) {
                for (n = 0; n < 3; n++) {
                    if (work->unk14 - 1 > 0) {
                        work->unk14--;
                        work->unk28[work->unk14] = 2;
                        work->unk10 -= 4.0f;
                    }
                }
                func_8004AC98_main(0x4B0, work->unk00->work[0]);
                HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[work->unk14]);
                work->unk08 |= 2;
                work->unk78 |= 2;
                func_8010BDE4_motor_rooter(work, 0x27, 1);
                if (work->unk06 == 0) {
                    omVibrate(m254_playerId[ctx->tag], 2, 2, 20);
                }
            }
        }
        if (view->unk4C[k] + 2 < view->unk8A) {
            view->unk2E[j] = view->unk88++;
            if (view->unk88 > D_801137D2_motor_rooter) {
                for (i = j * 7; i < j * 7 + 7; i++) {
                    func_8001C258_main(object->model[i], 4, 4);
                }
                view->unk2E[j] = -1;
            } else {
                for (i = j * 7; i < j * 7 + 7; i++) {
                    func_8001C258_main(object->model[i], 4, 4);
                }
                func_80109C94_motor_rooter(view, j);
                func_801091A0_motor_rooter(ctx);
            }
        }
    }
    dist = nearest + 3;
    if (work->unk88 == 0) {
        work->unk88 = 1;
        work->unk8A = func_8004AC5C_main(0x4B2, ctx->tag);
        func_8004AAD0_main(work->unk8A, 0);
    }
    func_8004AAD0_main(work->unk8A, dist < 26 ? 127 - (dist < 0 ? 0 : dist) * 3 : 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010972C_motor_rooter);
#endif
/* </func_8010972C_motor_rooter> */

/* <func_80109C94_motor_rooter> */
void func_80109C94_motor_rooter(PlayerView *view, s16 row) {
    s16 i;

    switch (view->unk74[view->unk2E[row]]) {
    case 0:
        view->unk34[row][0] = view->unk34[row][1] = view->unk34[row][2] = view->unk60[view->unk2E[row]] + 4;
        break;
    case 1:
        view->unk34[row][0] = view->unk60[view->unk2E[row]] + 4;
        view->unk34[row][1] = view->unk60[view->unk2E[row]] + 5;
        view->unk34[row][2] = view->unk60[view->unk2E[row]] + 3;
        break;
    case 2:
        view->unk34[row][0] = view->unk60[view->unk2E[row]] + 4;
        view->unk34[row][1] = view->unk60[view->unk2E[row]] + 4;
        view->unk34[row][2] = view->unk60[view->unk2E[row]] + 3;
        break;
    case 3:
        view->unk34[row][0] = view->unk60[view->unk2E[row]] + 4;
        view->unk34[row][1] = view->unk60[view->unk2E[row]] + 4;
        view->unk34[row][2] = view->unk60[view->unk2E[row]] + 5;
        break;
    }
    for (i = 0; i < 3; i++) {
        if (view->unk34[row][i] >= 8) {
            view->unk34[row][i] -= 8;
        }
        if (view->unk34[row][i] < 0) {
            view->unk34[row][i] += 8;
        }
    }
}
/* </func_80109C94_motor_rooter> */

/* <func_80109EFC_motor_rooter> */
void func_80109EFC_motor_rooter(FuncContext *ctx) {
    f32 rotX[16];
    f32 rotY[16];
    f32 mtx[16];
    Vec ofs;
    Vec out;
    omObjData *object;
    HmfModel *model;
    PlayerView *view;
    s16 i;
    f32 *path;
    f32 angle;
    f32 pitch;

    object = ctx->data;
    i = ctx->work.s16[0];
    view = &m254_minigame->views[object->work[0]];
    model = &HmfModelData[object->model[i]];
    angle = m254_minigame->unkDC[view->unk90[i]] * 45.0f;
    ofs.x = sindf(angle) * 64.00000095367431640625;
    ofs.y = -cosdf(angle) * 64.00000095367431640625;
    ofs.z = -30.0f;
    path = &D_801137C0_motor_rooter[m254_minigame->unk14[view->unk90[i]] * 9];
    pitch = path[3] - 180.0f;
    m254_MakeRotXMtx(rotX, pitch);
    m254_MakeRotYMtx(rotY, path[4]);
    m254_MultiplyMtx(rotX, rotY, mtx);
    func_801114B0_motor_rooter(mtx, &ofs, &out.x);
    model->pos.x = D_801137C0_motor_rooter[m254_minigame->unk14[view->unk90[i]] * 9 + 0] + out.x;
    model->pos.y = D_801137C0_motor_rooter[m254_minigame->unk14[view->unk90[i]] * 9 + 1] + out.y;
    model->pos.z = D_801137C0_motor_rooter[m254_minigame->unk14[view->unk90[i]] * 9 + 2] + out.z;
    model->rot.x = pitch;
    model->rot.y = path[4];
    m254_MakeIdentityMtx(model->mtx);
    func_80017D24_main(model->mtx, 0.0f, 0.0f, angle);
}
/* </func_80109EFC_motor_rooter> */

/* <func_8010A174_motor_rooter> */
#ifdef NON_MATCHING
void func_8010A174_motor_rooter(FuncContext *ctx) {
    omObjData *object = ctx->data;
    PlayerView *view = &m254_minigame->views[object->work[0]];
    D_801137C8_motor_rooter_Struct *work = &D_801137C8_motor_rooter[object->work[0]];
    s32 half;
    s16 *ids;
    s16 i;

    if (ctx->work.s16[1] == work->unk1C) {
        return;
    }
    for (i = 0, half = 180, ids = m254_playerId; i < 15; i++) {
        if (view->unk90[i] >= D_801137D0_motor_rooter) {
            func_8001C258_main(object->model[i], 4, 4);
        } else {
            ctx->work.s16[0] = i;
            func_80109EFC_motor_rooter(ctx);
            if (work->unk1C == m254_minigame->unk14[view->unk90[i]] &&
                work->unk16 == m254_minigame->unkDC[view->unk90[i]]) {
                if (work->unk14 + 1 < 6) {
                    if (work->unk48 > 90) {
                        work->unk48 = half - work->unk48;
                    }
                    work->unk4C = 0;
                    work->unk28[work->unk14++] = 1;
                    work->unk10 += 4.0f;
                    work->unk08 |= 0x20;
                    work->unk78 |= 1;
                    ctx->work.s16[1] = work->unk1C;
                    HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[work->unk14]);
                } else {
                    if (work->unk48 > 90) {
                        work->unk48 = half - work->unk48;
                    }
                    work->unk08 |= 0x20;
                    work->unk78 |= 1;
                    ctx->work.s16[1] = work->unk1C;
                    work->unk4C = 0;
                }
                func_8004AC5C_main(0x4B1, work->unk00->work[0]);
                if (work->unk06 == 0) {
                    omVibrate(ids[object->work[0]], 10, 0, 10);
                }
            }
            if (view->unk8A > m254_minigame->unk14[view->unk90[i]]) {
                view->unk90[i] = view->unkAE++;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010A174_motor_rooter);
#endif
/* </func_8010A174_motor_rooter> */

/* <func_8010A440_motor_rooter> */

void func_8010A440_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;
    omObjData *object = work->unk00;
    PlayerView *view = &m254_minigame->views[object->work[0]];
    s16 best = 0;
    s16 min;
    s16 i;
    s16 d;
    s32 unused[24];

    if (ctx->state == 0) {
        switch (GwPlayer[m254_playerId[object->work[0]]].cpu_difficulty) {
        case 0:
            ctx->work.s8[2] = 8;
            ctx->work.s8[3] = 7;
            ctx->work.s8[4] = 5;
            ctx->work.s8[5] = 3;
            ctx->work.s8[6] = 1;
            ctx->work.s8[7] = 1;
            break;
        case 1:
            ctx->work.s8[2] = 6;
            ctx->work.s8[3] = 5;
            ctx->work.s8[4] = 4;
            ctx->work.s8[5] = 4;
            ctx->work.s8[6] = 3;
            ctx->work.s8[7] = 3;
            break;
        case 2:
            ctx->work.s8[2] = 4;
            ctx->work.s8[3] = 3;
            ctx->work.s8[4] = 3;
            ctx->work.s8[5] = 5;
            ctx->work.s8[6] = 6;
            ctx->work.s8[7] = 6;
            break;
        case 3:
            ctx->work.s8[2] = 2;
            ctx->work.s8[3] = 1;
            ctx->work.s8[4] = 2;
            ctx->work.s8[5] = 6;
            ctx->work.s8[6] = 8;
            ctx->work.s8[7] = 10;
            break;
        }
        ctx->work.s16[1] = 8;
        ctx->state = 1;
    }
    D_800CBB6E_main[work->unk04] = 0;
    D_800D20A1_main[work->unk04] = 0;
    CPU_BTN[work->unk04] = 0;
    min = 999;
    for (i = 0; i < 3; i++) {
        if (view->unk2E[i] != -1 && work->unk1C <= view->unk4C[view->unk2E[i]]) {
            if (view->unk4C[view->unk2E[i]] < min) {
                min = view->unk4C[view->unk2E[i]];
                best = i;
            }
        }
    }
    if (min != 999 && work->unk1C + ctx->work.s16[1] > view->unk4C[view->unk2E[best]]) {
        if (work->unk16 != view->unk34[best][0]) {
            d = view->unk34[best][0] - work->unk16;
            if (d < 0) {
                d += 7;
            }
            if (ctx->work.s8[0] > ctx->work.s8[2]) {
                ctx->work.s8[0] = 0;
                switch (D_80113458_motor_rooter) {
                case 0:
                case 1:
                    if (d < 3) {
                        D_800CBB6E_main[work->unk04] = 50;
                    } else {
                        if (d < 4) {
                            (void)rand16();
                        }
                        D_800CBB6E_main[work->unk04] = -50;
                    }
                    break;
                case 2:
                    if (d < 3) {
                        CPU_BTN[work->unk04] = 0x8000;
                    } else {
                        if (d < 4) {
                            (void)rand16();
                        }
                        CPU_BTN[work->unk04] = 0x4000;
                    }
                    break;
                }
            } else {
                ctx->work.s8[0]++;
            }
        } else {
            ctx->work.s16[1] = 8 - rand16() % (ctx->work.s8[3] + 1);
        }
    } else {
        ctx->work.s8[0] = 0;
        if (rand16() % (ctx->work.s8[7] + 1) != 0) {
            min = 999;
            for (i = 0; i < 15; i++) {
                if (work->unk1C < m254_minigame->unk14[view->unk90[i]]) {
                    if (m254_minigame->unk14[view->unk90[i]] < min) {
                        min = m254_minigame->unk14[view->unk90[i]];
                        best = view->unk90[i];
                    }
                }
            }
            if (min != 999 && work->unk1C + ctx->work.s8[5] > m254_minigame->unk14[best] &&
                work->unk16 != m254_minigame->unkDC[best]) {
                d = m254_minigame->unkDC[best] - work->unk16;
                if (d < 0) {
                    d += 7;
                }
                if (ctx->work.s8[1] > ctx->work.s8[4]) {
                    ctx->work.s8[1] = 0;
                    switch (D_80113458_motor_rooter) {
                    case 0:
                    case 1:
                        if (d < 3) {
                            D_800CBB6E_main[work->unk04] = 50;
                        } else {
                            if (d < 4) {
                                (void)rand16();
                            }
                            D_800CBB6E_main[work->unk04] = -50;
                        }
                        if (rand16() % (ctx->work.s8[6] + 1) == 0) {
                            D_800CBB6E_main[work->unk04] *= -1;
                        }
                        break;
                    case 2:
                        if (d < 3) {
                            CPU_BTN[work->unk04] = 0x8000;
                        } else {
                            if (d < 4) {
                                (void)rand16();
                            }
                            CPU_BTN[work->unk04] = 0x4000;
                        }
                        if (rand16() % (ctx->work.s8[6] + 1) == 0) {
                            CPU_BTN[work->unk04] = ~CPU_BTN[work->unk04];
                            CPU_BTN[work->unk04] &= 0xC000;
                        }
                        break;
                    }
                } else {
                    ctx->work.s8[1]++;
                }
            }
        }
    }
}
/* </func_8010A440_motor_rooter> */

/* <func_8010ABC4_motor_rooter> */
void func_8010ABC4_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;
    omObjData *object = work->unk00;

    if (work->unk08 & 0x13) {
        return;
    }
    switch (D_80113458_motor_rooter) {
    case 0:
    case 1:
        if (D_800CBB6E_main[work->unk04] > 10) {
            if (ctx->work.s8[0] == 0) {
                if (D_80113458_motor_rooter == 0) {
                    ctx->work.s8[0] = 1;
                }
                ctx->work.s8[1] = 0;
                if (!(work->unk08 & 0xC)) {
                    work->unk08 |= 4;
                    m254_SetFunc(object->work[0] + 4, 4, -1, work, func_8010B970_motor_rooter, 0, FALSE);
                } else {
                    ctx->work.s8[2] = 4;
                }
            }
        } else if (D_800CBB6E_main[work->unk04] < -10) {
            if (ctx->work.s8[1] == 0) {
                ctx->work.s8[0] = 0;
                if (D_80113458_motor_rooter == 0) {
                    ctx->work.s8[1] = 1;
                }
                if (!(work->unk08 & 0xC)) {
                    work->unk08 |= 8;
                    m254_SetFunc(object->work[0] + 4, 4, -1, work, func_8010B970_motor_rooter, 0, TRUE);
                } else {
                    ctx->work.s8[2] = 8;
                }
            }
        } else {
            ctx->work.s8[1] = 0;
            ctx->work.s8[0] = 0;
        }
        break;
    case 2:
        if (CPU_BTN[work->unk04] & 0x8000) {
            if (ctx->work.s8[0] == 0) {
                ctx->work.s8[0] = 1;
                ctx->work.s8[1] = 0;
                if (!(work->unk08 & 0xC)) {
                    work->unk08 |= 4;
                    m254_SetFunc(object->work[0] + 4, 4, -1, work, func_8010B970_motor_rooter, 0, FALSE);
                } else {
                    ctx->work.s8[2] = 4;
                }
            }
        } else if (CPU_BTN[work->unk04] & 0x4000) {
            if (ctx->work.s8[1] == 0) {
                ctx->work.s8[0] = 0;
                ctx->work.s8[1] = 1;
                if (!(work->unk08 & 0xC)) {
                    work->unk08 |= 8;
                    m254_SetFunc(object->work[0] + 4, 4, -1, work, func_8010B970_motor_rooter, 0, TRUE);
                } else {
                    ctx->work.s8[2] = 8;
                }
            }
        } else {
            ctx->work.s8[1] = 0;
            ctx->work.s8[0] = 0;
        }
        break;
    }
    if (D_80113458_motor_rooter != 1 && !(GwPlayer[m254_playerId[object->work[0]]].stat & 1) && !(work->unk08 & 0xC)) {
        switch (ctx->work.s8[2]) {
        case 4:
            work->unk08 |= 4;
            m254_SetFunc(object->work[0] + 4, 4, -1, work, func_8010B970_motor_rooter, 0, FALSE);
            break;
        case 8:
            work->unk08 |= 8;
            m254_SetFunc(object->work[0] + 4, 4, -1, work, func_8010B970_motor_rooter, 0, TRUE);
            break;
        }
        ctx->work.s8[2] = 0;
    }
}
/* </func_8010ABC4_motor_rooter> */

/* <func_8010AF0C_motor_rooter> */
#ifdef NON_MATCHING
extern s8 D_8011349C_motor_rooter[];

void func_8010AF0C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;
    omObjData *object = work->unk00;
    f32 rot = 0.0f;
    s16 idx = object->work[0];
    f32 yaw;
    f32 mtxX[16];
    f32 mtxY[16];
    f32 mtx[16];
    Vec in;
    Vec out;

    if (work->unk08 & 0x80) {
        m254_ResetFunc(object->work[0] + 4, ctx);
        return;
    }
    if (work->unk08 == 0) {
        ctx->work.s16[1] = 1;
        ctx->state = 1;
    }
    work->unk0C += work->unk10;
    ctx->work.s16[0] = (ctx->work.s16[0] + 2 > 360) ? 0 : ctx->work.s16[0] + 2;
    ctx->work.f32[0] = sindf(ctx->work.s16[0]) * 20.0 * 0.05;
    if (work->unk08 & 2) {
        yaw = D_8011349C_motor_rooter[ctx->work.s8[0]] + work->unk18;
        if (++ctx->work.s8[0] >= 4) {
            func_8010BDE4_motor_rooter(work, 38, 0);
            ctx->work.s8[0] = 0;
            work->unk08 &= ~2;
        }
    } else {
        yaw = work->unk18;
    }
    if (work->unk08 & 0x20) {
        rot = sindf(work->unk48) * 30.0;
        if ((work->unk48 += 10) > 180) {
            work->unk48 = 0;
            work->unk08 &= ~0x20;
        }
    }
    work->unk68.x = ctx->work.f32[0];
    work->unk68.y = yaw;
    work->unk68.z = rot;
    work->unk7C.x = ctx->work.f32[0];
    work->unk7C.y = yaw;
    work->unk7C.z = rot;
    in.x = sindf(yaw) * (ctx->work.f32[0] + 55.999999046325684);
    in.y = -cosdf(yaw) * (ctx->work.f32[0] + 55.999999046325684);
    in.z = -120.0 - rot;
    m254_MakeRotXMtx(mtxX, CRotM[idx].x);
    m254_MakeRotYMtx(mtxY, CRotM[idx].y);
    m254_MultiplyMtx(mtxX, mtxY, mtx);
    func_801114B0_motor_rooter(mtx, &in, (f32 *)&out);
    object->trans.x = CenterM[idx].x + out.x;
    object->trans.y = CenterM[idx].y + out.y;
    object->trans.z = CenterM[idx].z + out.z;
    if (work->unk08 & 0x400) {
        object->rot.x = CRotM[idx].x;
        m254_MakeIdentityMtx(HmfModelData[object->model[0]].mtx);
        func_80017D24_main(HmfModelData[object->model[0]].mtx, 0.0f, work->unk74, 0.0f);
        object->rot.y = 0.0f;
        return;
    }
    object->rot.x = 360.0f - CRotM[idx].x;
    if (!(work->unk08 & 1)) {
        object->rot.y = CRotM[idx].y + 180.0f;
    }
    m254_MakeIdentityMtx(HmfModelData[object->model[0]].mtx);
    func_80017D24_main(HmfModelData[object->model[0]].mtx, 0.0f, 0.0f, 360.0f - yaw);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010AF0C_motor_rooter);
#endif
/* </func_8010AF0C_motor_rooter> */

/* <func_8010B394_motor_rooter> */
void func_8010B394_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;
    omObjData *object = work->unk00;
    HmfModel *model = &HmfModelData[object->model[9]];
    s16 idx = object->work[0];
    f32 yaw;
    f32 rot;
    f32 mtxX[16];
    f32 mtxY[16];
    f32 mtx[16];
    Vec in;
    Vec out;

    if (work->unk08 & 0x80) {
        m254_ResetFunc(object->work[0] + 4, ctx);
        return;
    }
    if (!(work->unk08 & 0x200)) {
        in.x = sindf(work->unk7C.y) * (work->unk7C.x + 55.999999046325684);
        in.y = -cosdf(work->unk7C.y) * (work->unk7C.x + 55.999999046325684);
        in.z = -120.0 - work->unk7C.z;
        m254_MakeRotXMtx(mtxX, CRotM[idx].x);
        m254_MakeRotYMtx(mtxY, CRotM[idx].y);
        m254_MultiplyMtx(mtxX, mtxY, mtx);
        func_801114B0_motor_rooter(mtx, &in, (f32 *)&out);
        HmfModelData[object->model[9]].pos.x = CenterM[idx].x + out.x;
        HmfModelData[object->model[9]].pos.y = CenterM[idx].y + out.y;
        HmfModelData[object->model[9]].pos.z = CenterM[idx].z + out.z;
    } else {
        Hu3DModelPosSet(object->model[9], object->trans.x, object->trans.y + 0.0, object->trans.z);
    }
    Hu3DModelRotSet(object->model[9], object->rot.x, object->rot.y, object->rot.z);
    if (work->unk08 & 0x400) {
        m254_MakeIdentityMtx(model->mtx);
        func_80017D24_main(model->mtx, 0.0f, work->unk74, 0.0f);
        model->rot.y = model->rot.z = 0.0f;
    } else {
        m254_MakeIdentityMtx(model->mtx);
        func_80017D24_main(model->mtx, 0.0f, 0.0f, 360.0f - work->unk18);
    }
    if (!(work->unk08 & 0x200)) {
        yaw = work->unk68.y;
        rot = work->unk68.z;
        in.x = sindf(yaw) * (work->unk68.x + 65.99999904632568);
        in.y = -cosdf(yaw) * (work->unk68.x + 65.99999904632568);
        in.z = -120.0 - rot;
        m254_MakeRotXMtx(mtxX, CRotM[idx].x);
        m254_MakeRotYMtx(mtxY, CRotM[idx].y);
        m254_MultiplyMtx(mtxX, mtxY, mtx);
        func_801114B0_motor_rooter(mtx, &in, (f32 *)&out);
        HmfModelData[object->model[10]].pos.x = CenterM[idx].x + out.x;
        HmfModelData[object->model[10]].pos.y = CenterM[idx].y + out.y;
        HmfModelData[object->model[10]].pos.z = CenterM[idx].z + out.z;
    } else {
        func_8001C258_main(object->model[10], 4, 0);
        Hu3DModelPosSet(object->model[10], object->trans.x, object->trans.y - 10.0 + 0.0, object->trans.z);
    }
    if (work->unk08 & 0x400) {
        Hu3DModelRotSet(object->model[10], object->rot.x, object->rot.y, 0.0f);
        m254_MakeIdentityMtx(HmfModelData[object->model[10]].mtx);
        func_80017D24_main(HmfModelData[object->model[10]].mtx, 0.0f, work->unk74, 0.0f);
    } else {
        Hu3DModelRotSet(object->model[10], object->rot.x, object->rot.y, object->rot.z);
        m254_MakeIdentityMtx(HmfModelData[object->model[10]].mtx);
        func_80017D24_main(HmfModelData[object->model[10]].mtx, 0.0f, 0.0f, 360.0f - work->unk18);
    }
}
/* </func_8010B394_motor_rooter> */

/* <func_8010B970_motor_rooter> */
void func_8010B970_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;
    omObjData *object = work->unk00;

    if (work->unk08 & 2) {
        return;
    }
    switch (ctx->state) {
    case 0:
        ctx->work.s8[0] = 0;
        if (work->unk08 & 4) {
            ctx->work.f32[0] = work->unk18;
            ctx->work.f32[1] = work->unk18 + 45.0f;
            work->unk16 = (work->unk16 + 1 >= 8) ? 0 : work->unk16 + 1;
        } else {
            work->unk16 = (work->unk16 - 1 < 0) ? 7 : work->unk16 - 1;
            ctx->work.f32[0] = work->unk18;
            ctx->work.f32[1] = work->unk18 - 45.0f;
        }
        ctx->state = 1;
        break;
    case 1:
        work->unk18 = (ctx->work.f32[1] - ctx->work.f32[0]) * sindf(ctx->work.s8[0] / 4.0f * 90.0f) + ctx->work.f32[0];
        if (work->unk18 > 360.0f) {
            work->unk18 -= 360.0f;
        }
        if (work->unk18 < 0.0f) {
            work->unk18 += 360.0f;
        }
        if (++ctx->work.s8[0] > 4.0f) {
            work->unk08 &= ~0xC;
            m254_ResetFunc(object->work[0] + 4, ctx);
        }
        break;
    }
}
/* </func_8010B970_motor_rooter> */

/* <func_8010BB78_motor_rooter> */
extern s16 D_8011349E_motor_rooter[];

void func_8010BB78_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;

    if (work->unk08 & 0x11) {
        return;
    }
    if (work->unk08 & 0x100) {
        if (work->unk10 < 20.0f) {
            work->unk10 = 2.0f * work->unk10;
            if (work->unk10 > 20.0f) {
                work->unk10 = 20.0f;
            }
        } else {
            HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[work->unk14]);
            work->unk08 &= ~0x100;
        }
    } else if (++work->unk4C > D_8011349E_motor_rooter[work->unk14]) {
        work->unk4C = 0;
        if (work->unk14 - 1 > 0) {
            work->unk14--;
            work->unk28[work->unk14] = 2;
            work->unk10 -= 4.0f;
        }
        func_8004AAD0_main(D_801137D8_motor_rooter, 64);
        HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[work->unk14]);
    }
}
/* </func_8010BB78_motor_rooter> */

/* <func_8010BCD0_motor_rooter> */
void func_8010BCD0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;
    omObjData *object = work->unk00;
    HmfModel *model = &HmfModelData[object->model[0]];

    if (D_800CCF58_main[model->unk02].unk02 - 1 <= model->unk40) {
        work->unk32 = 1;
    }
    if (work->unk32 != 0) {
        func_800E5690_minigame(object, work->unk34);
        work->unk32 = 0;
        if (work->unk34 == 13) {
            func_80045F1C_main(D_800A178C_main[GwPlayer[m254_playerId[object->work[0]]].chr][0] | 0x2F, -1, 0);
        }
    }
}
/* </func_8010BCD0_motor_rooter> */

/* <func_8010BDE4_motor_rooter> */
void func_8010BDE4_motor_rooter(D_801137C8_motor_rooter_Struct *arg0, s16 arg1, s8 arg2) {
    arg0->unk32 = arg2;
    arg0->unk34 = arg1;
}
/* </func_8010BDE4_motor_rooter> */

/* <func_8010BDF0_motor_rooter> */
#ifdef NON_MATCHING
void func_8010BDF0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;
    omObjData *object = work->unk00;
    f32 t;
    f32 s;
    s16 v;

    if (ctx->state == 0) {
        ctx->work.s8[0] = 0;
        ctx->work.s16[0] = 0;
        ctx->work.f32[0] = -120.0f;
        ctx->work.f32[1] = 40.0f;
        ctx->state = 1;
        work->unk08 |= 0x200;
        D_801137D8_motor_rooter = func_8004AC5C_main(0x4AF, work->unk00->work[0]);
        func_8004AAD0_main(D_801137D8_motor_rooter, 64);
        HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[work->unk14]);
        m254_SetFunc(object->work[0] + 4, 8, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010B394_motor_rooter, 0, FALSE);
    }
    /* retail takes the sine of s8[0] / 80 degrees, then scales it by 90 */
    s = sindf(ctx->work.s8[0] / 80.0f) * 90.0f;
    if (s > 1.0f) {
        t = 1.0f;
    } else {
        t = s;
    }
    if (ctx->work.s16[0] + 2 < 361) {
        v = ctx->work.s16[0] + 2;
    } else {
        v = 0;
    }
    ctx->work.s16[0] = v;
    ctx->work.f32[2] = sindf(v) * 20.0 * 0.05;
    object->trans.z = (ctx->work.f32[0] - ctx->work.f32[1]) * t + ctx->work.f32[1];
    object->trans.y = ctx->work.f32[2] + -55.999999046325684;
    if (++ctx->work.s8[0] > 80) {
        m254_ResetFunc(object->work[0] + 4, ctx);
        m254_SetFunc(object->work[0] + 4, 7, -1, work, func_8010AF0C_motor_rooter, 0, FALSE)->work.s16[0] = ctx->work.s16[0];
        work->unk08 &= ~0x200;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010BDF0_motor_rooter);
#endif
/* </func_8010BDF0_motor_rooter> */

/* <func_8010C084_motor_rooter> */
void func_8010C084_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *work = ctx->data;
    omObjData *object = work->unk00;
    s16 idx = object->work[0];
    s16 i;
    f32 t;

    if (work->unk08 & 0xC) {
        return;
    }
    switch (ctx->state) {
    case 0:
        ctx->work.s8[2] = 0;
        ctx->work.s16[0] = 1;
        ctx->work.f32[3] = object->rot.y;
        work->unk64 = CRotM[idx].y + 90.0f;
        if (ctx->work.f32[3] > 360.0f) {
            ctx->work.f32[3] -= 360.0f;
        }
        if (ctx->work.f32[3] < 0.0f) {
            ctx->work.f32[3] += 360.0f;
        }
        if (work->unk64 - ctx->work.f32[3] > 180.0f) {
            work->unk64 -= 360.0f;
        }
        ctx->work.f32[2] = work->unk18;
        if (work->unk18 > 180.0f) {
            ctx->work.f32[1] = 360.0f;
        } else {
            ctx->work.f32[1] = 0.0f;
        }
        ctx->work.f32[0] = work->unk10 / 40.0f;
        ctx->state = 1;
        work->unk08 |= 1;
        break;
    case 1:
        t = ctx->work.s8[2] / 15.0f;
        work->unk18 = (ctx->work.f32[1] - ctx->work.f32[2]) * t + ctx->work.f32[2];
        if (++ctx->work.s8[2] > 15) {
            func_8004AB0C_main(120);
            ctx->state = 2;
            work->unk78 |= 4;
            for (i = 0; i < 4; i++) {
                m254_minigame->unk1A4[idx * 4 + i] = 0;
            }
        }
        break;
    case 2:
        object->rot.y = (work->unk64 - ctx->work.f32[3]) * sindf(ctx->work.s16[0]) + ctx->work.f32[3];
        ctx->work.s16[0] = 2.0f * ctx->work.s16[0];
        if (ctx->work.s16[0] > 90) {
            ctx->work.s16[0] = 90;
        }
        work->unk10 -= ctx->work.f32[0];
        if (++ctx->work.s16[5] > 6) {
            ctx->work.s16[5] = 0;
            if (work->unk14 - 1 >= 0) {
                work->unk14--;
                work->unk28[work->unk14] = 2;
            }
        }
        if (work->unk10 < 0.0f) {
            work->unk10 = 0.0f;
            work->unk08 |= 0x80;
            m254_SetFunc(object->work[0] + 4, 5, -1, work, func_8010C44C_motor_rooter, 0, FALSE);
            m254_ResetFunc(object->work[0] + 4, ctx);
        }
        break;
    }
}
/* </func_8010C084_motor_rooter> */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010C44C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010C824_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010CB2C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010CD84_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010D03C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010D0AC_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010D1A8_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010D2E4_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010DC3C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010DD10_motor_rooter);
