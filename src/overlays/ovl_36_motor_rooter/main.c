#include "overlays/ovl_36.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/camera.h"
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
    /* 0x34 */ char unk34[0x12];
    /* 0x46 */ s16 unk46[3];
    /* 0x4C */ s16 unk4C[30];
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
    /* 0x00C */ char unk0C[0x198];
    /* 0x1A4 */ s8 unk1A4[0x30]; // mtx?
} MinigameData;                  // Size 0x1D4

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ char unk10[4];
    /* 0x14 */ s8 unk14;
    /* 0x15 */ char unk15;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ char unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E[5];
    /* 0x28 */ s16 unk28[5];
    /* 0x32 */ s8 unk32;
    /* 0x33 */ char unk33;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char unk36[0x14];
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ char unk4C[0x40];
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
void func_8010CD84_motor_rooter(void *, s32);
s16 func_8010D03C_motor_rooter(f32);
void func_8010D0AC_motor_rooter(f32 *, s16, f32);
void func_8010D2E4_motor_rooter(s32);
s16 func_8010EFF8_motor_rooter(HuSprite_Unk84_Struct *arg0, f32 arg1);

// BSS
extern f32 *D_801137C0_motor_rooter;
extern MinigameData *m254_minigame; // D_801137C4_motor_rooter
extern D_801137C8_motor_rooter_Struct *D_801137C8_motor_rooter;
extern s16 D_801137CC_motor_rooter;
extern s16 D_801137CE_motor_rooter;
extern s16 D_801137D0_motor_rooter;
extern s16 D_801137D2_motor_rooter;
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
    memset(m254_minigame->unk1A4, 0, sizeof(m254_minigame->unk1A4));
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
extern s32 D_800A178C_main[][6];
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
extern RGBA D_80113470_motor_rooter[];
s16 func_8010FC10_motor_rooter(HuSprite_Unk84_Struct *arg0, RGBA *arg1);
void func_80107D50_motor_rooter(omObjData *object);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80107D50_motor_rooter);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80108514_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801087C0_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801089B8_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80108BF0_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80108E6C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80108FDC_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80109134_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801091A0_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010961C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010972C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80109C94_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80109EFC_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010A174_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010A440_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010ABC4_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010AF0C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010B394_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010B970_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010BB78_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010BCD0_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010BDE4_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010BDF0_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010C084_motor_rooter);

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
