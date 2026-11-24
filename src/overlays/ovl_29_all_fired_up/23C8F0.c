#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"

// fired A: All Fired Up (4 players dodge Podoboo flames that wander, form patterns and jump on a hot plate)

typedef func_800E1BA8_minigame_ObjData MgWork;

#define AF_ABS(x) (((x) > 0.0f) ? (x) : 0.0f - (x))

/* omObjData::data of a flame */
typedef struct AfFlame {
    /* 0x00 */ s8 unk00; /* flame index */
    /* 0x01 */ char unk01[3];
    /* 0x04 */ f32 unk04; /* fall speed while dropping in */
    /* 0x08 */ f32 unk08; /* shadow scale */
    /* 0x0C */ f32 unk0C; /* heading */
    /* 0x10 */ f32 unk10; /* jump phase */
    /* 0x14 */ f32 unk14; /* orbit radius */
    /* 0x18 */ f32 unk18; /* wander speed */
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ char unk1E[2];
    /* 0x20 */ Vec unk20; /* position when the pattern changes */
    /* 0x2C */ Vec unk2C; /* pattern target */
    /* 0x38 */ u8 unk38;  /* landed */
    /* 0x39 */ char unk39[3];
} AfFlame; /* size 0x3C */

/* MgWork::unk158 of a player */
typedef struct AfPlayer {
    /* 0x00 */ f32 unk00; /* shadow scale while burnt */
    /* 0x04 */ f32 unk04; /* burnt jump angle */
    /* 0x08 */ u16 unk08; /* CPU heading timer */
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ f32 unk0C; /* CPU heading */
} AfPlayer; /* size 0x10 */

/* omObjData::data of the plate (the framework's ground object) */
typedef struct AfGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[3];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ char unk0C[0xA8];
} AfGround; /* size 0xB4 */

/* The minigame control block (as Ice Rink Risk's IrCtrl) */
typedef struct AfCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
} AfCtrl; /* size 0x28 */

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004AD70_main(void);
s16 HmfAnimRead(HmfData* arg0, s32 arg1, char* arg2);
f32 HuSqrtf(f32 x);

extern s32 D_800A178C_main[][6];
extern u16 D_800A1906_main; /* music state flags */
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;
extern Vec Center;
extern Vec CRot;
extern f32 CZoom;
extern s8 D_800CBB6E_main[];  /* CPU stick x */
extern s8 D_800D20A1_main[];  /* CPU stick y */
extern u16 D_800D5558_main[]; /* CPU buttons */

// minigame
void func_800DDD94_minigame(omObjData* obj);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1490_minigame(u16 arg0);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E1804_minigame(void);
void func_800E1840_minigame(void);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern f32 D_800EB76C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[];

// LOCAL

void func_80105C54_all_fired_up(AfCtrl* ctrl);
void func_80105CE8_all_fired_up(void);
void func_80105E1C_all_fired_up(omObjData* obj);
void func_80105F5C_all_fired_up(void);
void func_80106348_all_fired_up(omObjData* obj);
void func_80106584_all_fired_up(omObjData* obj);
void func_801067CC_all_fired_up(omObjData* obj);
void func_801068F8_all_fired_up(void);
void func_80106B7C_all_fired_up(void);
void func_80106C68_all_fired_up(void);
void func_80106CDC_all_fired_up(omObjData* obj);
void func_80106F04_all_fired_up(omObjData* obj);
void func_80106FAC_all_fired_up(void);
void func_80107440_all_fired_up(omObjData* obj);
void func_80107578_all_fired_up(omObjData* obj);
void func_80107BD4_all_fired_up(omObjData* obj);
void func_80107DA4_all_fired_up(omObjData* obj);
void func_801080C8_all_fired_up(omObjData* obj);
void func_801085A4_all_fired_up(omObjData* obj);
void func_80108710_all_fired_up(omObjData* obj);
void func_80108958_all_fired_up(omObjData* obj);
void func_80108AA0_all_fired_up(omObjData* obj);
void func_80109660_all_fired_up(omObjData* obj, f32 dist, s8 inner);
void func_801097B0_all_fired_up(omObjData* obj);

extern u8 D_80109930_all_fired_up[24][4]; /* start slot per player, one row per permutation */
extern Vec D_80109990_all_fired_up[4];     /* start positions */
extern u16 D_801099C0_all_fired_up[4];     /* frame each player was burnt */
extern s8 D_801099C8_all_fired_up;         /* pattern state */
extern s8 D_801099C9_all_fired_up;         /* flames in play */
extern f32 D_801099CC_all_fired_up;        /* circle radius */
extern s8 D_801099D0_all_fired_up;
extern u8 D_801099D4_all_fired_up[6][6];   /* formation order */
extern s32 D_801099F8_all_fired_up;
extern s8 D_801099FC_all_fired_up;
extern f32 D_80109A00_all_fired_up;
extern s8 D_80109A04_all_fired_up;
extern s8 D_80109A05_all_fired_up;
extern s8 D_80109A06_all_fired_up;
extern s32 D_80109A08_all_fired_up[4];
extern s32 D_80109A18_all_fired_up[4][4];
extern f32 D_80109A58_all_fired_up[4];

extern s32 D_80109AC0_all_fired_up;
extern s8 D_80109AC4_all_fired_up;
extern s8 D_80109AC5_all_fired_up;
extern AfCtrl D_80109AC8_all_fired_up;
extern u8 D_80109AF0_all_fired_up;
extern s16 D_80109AF2_all_fired_up[4];
extern omObjData* D_80109B00_all_fired_up[21];
extern Vec D_80109B58_all_fired_up[21];
extern s8 D_80109C54_all_fired_up;
extern s16 D_80109C56_all_fired_up;
extern s8 D_80109C58_all_fired_up;
extern s8 D_80109C59_all_fired_up;

void func_801059A0_all_fired_up(void) {
    omObjData* obj;
    s32 i;

    Hu3DAnimInit(0x20);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105CE8_all_fired_up();
    func_80105C54_all_fired_up(&D_80109AC8_all_fired_up);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_80109AC8_all_fired_up);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80105E1C_all_fired_up), 0xA0);
    func_800E1490_minigame(D_800EBE28_minigame);
    obj = omAddObj(0, 1, 0, -1, func_801097B0_all_fired_up);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
    omSetStatBit(obj, 0xA0);
    D_80109AF0_all_fired_up = (u32)(rand8() * 3) >> 5;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(1, 2, 60, -1, func_80107DA4_all_fired_up);
    }
    for (i = 0; i < 4; i++) {
        D_80109AF2_all_fired_up[i] = func_8000B108_main(0x4A0003, 0x819);
        func_8001C258_main(D_80109AF2_all_fired_up[i], 4, 4);
    }
    func_80105F5C_all_fired_up();
    D_80109C58_all_fired_up = (u32)(rand8() * 3) >> 7;
    for (i = 0; i < 21; i++) {
        D_80109B00_all_fired_up[i] = omAddObj(1, 2, 0, -1, func_80106348_all_fired_up);
    }
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    WipeCreateIn(0xFF, 16);
}

void func_80105C54_all_fired_up(AfCtrl* ctrl) {
    s32 i;

    D_800EB932_minigame = 15;
    ctrl->unk00 = 0;
    ctrl->unk01 = 5;
    ctrl->unk02 = 1;
    ctrl->unk03 = 2;
    ctrl->unk04 = 0;
    ctrl->unk05 = 0;
    ctrl->unk06 = 9;
    ctrl->unk1C = 90;
    ctrl->unk1E = 1800;
    ctrl->unk20 = -1;
    ctrl->unk22 = 75;
    ctrl->unk24 = 150;
    for (i = 0; i < 4; i++) {
        ctrl->unk08[i] = 0;
        ctrl->unk18[i] = 0xFF;
    }
}

void func_80105CE8_all_fired_up(void) {
    f32 zero;
    s32 cam;

    Center.x = 0.0f;
    Center.y = 820.0f;
    Center.z = 650.0f;
    CRot.x = -45.0f;
    zero = Center.x;
    CRot.z = zero;
    CRot.y = zero;
    CZoom = 2100.0f;
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, zero, zero, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(cam, 30.0f, 80.0f, 8000.0f);
}

void func_80105E1C_all_fired_up(omObjData* obj) {
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        if (D_801099FC_all_fired_up == 0 && D_800D530C_main == 1) {
            func_8004AD70_main();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                func_8004A950_main();
            }
            func_800E6F0C_minigame(5);
            D_801099FC_all_fired_up = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 0x35;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (D_801099F8_all_fired_up == 0) {
                    WipeCreateOut(0, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_801099F8_all_fired_up++;
                break;
        }
    }
}

/* Flame drop heights, and the circle (radius 80) and ring (radius 160) start spots. */
void func_80105F5C_all_fired_up(void) {
    s32 i;

    for (i = 0; i < 15; i++) {
        D_80109B58_all_fired_up[i].y = (rand8() % 200) * 3 + 1200.0f;
    }
    D_80109B58_all_fired_up[0].x = D_80109B58_all_fired_up[0].z = 0.0f;
    D_80109B58_all_fired_up[1].x = sindf(0.0f) * 80.0f;
    D_80109B58_all_fired_up[1].z = cosdf(0.0f) * 80.0f;
    D_80109B58_all_fired_up[2].x = sindf(60.0f) * 80.0f;
    D_80109B58_all_fired_up[2].z = cosdf(60.0f) * 80.0f;
    D_80109B58_all_fired_up[3].x = sindf(120.0f) * 80.0f;
    D_80109B58_all_fired_up[3].z = cosdf(120.0f) * 80.0f;
    D_80109B58_all_fired_up[4].x = sindf(180.0f) * 80.0f;
    D_80109B58_all_fired_up[4].z = cosdf(180.0f) * 80.0f;
    D_80109B58_all_fired_up[5].x = sindf(240.0f) * 80.0f;
    D_80109B58_all_fired_up[5].z = cosdf(240.0f) * 80.0f;
    D_80109B58_all_fired_up[6].x = sindf(300.0f) * 80.0f;
    D_80109B58_all_fired_up[6].z = cosdf(300.0f) * 80.0f;
    D_80109B58_all_fired_up[7].x = 2.0f * (sindf(0.0f) * 80.0f);
    D_80109B58_all_fired_up[7].z = 2.0f * (cosdf(0.0f) * 80.0f);
    D_80109B58_all_fired_up[8].x = 2.0f * (sindf(45.0f) * 80.0f);
    D_80109B58_all_fired_up[8].z = 2.0f * (cosdf(45.0f) * 80.0f);
    D_80109B58_all_fired_up[9].x = 2.0f * (sindf(90.0f) * 80.0f);
    D_80109B58_all_fired_up[9].z = 2.0f * (cosdf(90.0f) * 80.0f);
    D_80109B58_all_fired_up[10].x = 2.0f * (sindf(135.0f) * 80.0f);
    D_80109B58_all_fired_up[10].z = 2.0f * (cosdf(135.0f) * 80.0f);
    D_80109B58_all_fired_up[11].x = 2.0f * (sindf(180.0f) * 80.0f);
    D_80109B58_all_fired_up[11].z = 2.0f * (cosdf(180.0f) * 80.0f);
    D_80109B58_all_fired_up[12].x = 2.0f * (sindf(225.0f) * 80.0f);
    D_80109B58_all_fired_up[12].z = 2.0f * (cosdf(225.0f) * 80.0f);
    D_80109B58_all_fired_up[13].x = 2.0f * (sindf(270.0f) * 80.0f);
    D_80109B58_all_fired_up[13].z = 2.0f * (cosdf(270.0f) * 80.0f);
    D_80109B58_all_fired_up[14].x = 2.0f * (sindf(315.0f) * 80.0f);
    D_80109B58_all_fired_up[14].z = 2.0f * (cosdf(315.0f) * 80.0f);
    for (i = 15; i < 21; i++) {
        D_80109B58_all_fired_up[i].x = D_80109B58_all_fired_up[i].y = D_80109B58_all_fired_up[i].z = 0.0f;
    }
}

/* A flame: model 0 the Podoboo, model 1 its shadow. */
void func_80106348_all_fired_up(omObjData* obj) {
    AfFlame* w;
    s16 mdl;

    obj->func = func_80106584_all_fired_up;
    w = obj->data = HuMemAllocTag(sizeof(AfFlame), 0x7918);
    memset(w, 0, sizeof(AfFlame));
    w->unk00 = D_80109AC0_all_fired_up;
    w->unk04 = 0.0f;
    w->unk08 = 0.0f;
    w->unk1C = 0;
    w->unk0C = 0.0f;
    w->unk14 = 0.0f;
    w->unk10 = 0.0f;
    w->unk18 = 1.0f;
    w->unk38 = 0;
    obj->trans.x = D_80109B58_all_fired_up[w->unk00].x;
    obj->trans.y = D_80109B58_all_fired_up[w->unk00].y;
    obj->trans.z = D_80109B58_all_fired_up[w->unk00].z;
    obj->scale.z = 1.2f;
    obj->scale.y = 1.2f;
    obj->scale.x = 1.2f;
    mdl = obj->model[0] = func_8000B108_main(0xA008A, 0xAA9);
    if (w->unk00 == 0) {
        HmfAnimRead(HmfModelData[mdl].hmf, 0xA008C, "c201n_00_DEF");
    } else {
        func_80032694_main(HmfModelData[mdl].hmf, 0, 0, "c201n_00_DEF");
    }
    func_8001C448_main(mdl);
    func_8001C514_main(mdl);
    obj->model[1] = func_8000B108_main(0x4A0004, 0x2D9);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    if (w->unk00 >= 15) {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    D_80109AC0_all_fired_up++;
}

void func_80106584_all_fired_up(omObjData* obj) {
    AfFlame* w;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        w = obj->data;
        switch (func_800E6E8C_minigame()) {
            case 0:
                func_801067CC_all_fired_up(obj);
                break;
            case 2:
                if (D_801099C9_all_fired_up - 1 >= w->unk00) {
                    func_80107BD4_all_fired_up(obj);
                }
                if (w->unk00 == 0) {
                    func_801068F8_all_fired_up();
                }
                switch (D_801099C8_all_fired_up) {
                    case 0:
                        func_80106CDC_all_fired_up(obj);
                        break;
                    case 1:
                        func_80106F04_all_fired_up(obj);
                        break;
                    case 2:
                        func_80107440_all_fired_up(obj);
                        break;
                    case 3:
                        func_80107578_all_fired_up(obj);
                        break;
                }
                break;
            case 3:
                obj->scale.x -= 0.05f;
                if (obj->scale.x < 0.0f) {
                    obj->scale.x = 0.0f;
                }
                obj->scale.y -= 0.05f;
                if (obj->scale.y < 0.0f) {
                    obj->scale.y = 0.0f;
                }
                obj->scale.z -= 0.05f;
                if (obj->scale.z < 0.0f) {
                    obj->scale.z = 0.0f;
                }
                w->unk08 -= 0.05f;
                if (w->unk08 < 0.0f) {
                    w->unk08 = 0.0f;
                }
                Hu3DModelScaleSet(obj->model[1], w->unk08, w->unk08, w->unk08);
                break;
        }
    }
}

/* Intro: the first 15 flames drop in. */
void func_801067CC_all_fired_up(omObjData* obj) {
    AfFlame* w = obj->data;

    if (w->unk00 < 15) {
        if (func_800E6E9C_minigame() >= 16) {
            obj->trans.y -= w->unk04 + 15.0f;
            w->unk04 += 3.0f;
            if (obj->trans.y < 0.0f) {
                obj->trans.y = 0.0f;
                if (w->unk38 == 0) {
                    if (!(w->unk00 & 1)) {
                        HuAudFXPlay(0x441);
                    }
                    w->unk38 = 1;
                }
            }
            w->unk08 += 0.05f;
            if (w->unk08 > 1.0f) {
                w->unk08 = 1.0f;
            }
        }
        Hu3DModelScaleSet(obj->model[1], w->unk08, w->unk08, w->unk08);
    }
}

// NON_MATCHING (H1): masked 15, 234/235. Per-case `t + 1` stores now cross-jump into case 3's copy as
// in retail. Left: retail copies t into $a0 (move a0,v1 in each bne slot) and has a 0x38 frame (0x20
// unused locals). Tried an s16 t and `if ((t = D_80109C56_all_fired_up) == N)`.
#ifdef NON_MATCHING
/* Pattern timer: wander (adding a flame), gather, the next formation, run it. */
void func_801068F8_all_fired_up(void) {
    s32 i;
    s32 t;

    switch (D_801099C8_all_fired_up) {
        case 0:
            if (D_80109C56_all_fired_up == 0 && D_80109AC4_all_fired_up > 0 && D_801099C9_all_fired_up < 21) {
                func_80106B7C_all_fired_up();
                for (i = 0; i < 21; i++) {
                    ((AfFlame*)D_80109B00_all_fired_up[i]->data)->unk18 += 0.1f;
                }
            }
            if (D_80109C56_all_fired_up == 0) {
                HuAudFXPlay(0x444);
            }
            t = D_80109C56_all_fired_up;
            if (t == 90) {
                D_801099C8_all_fired_up = 1;
                D_80109C56_all_fired_up = 0;
                func_80106C68_all_fired_up();
            } else {
                D_80109C56_all_fired_up = t + 1;
            }
            break;
        case 1:
            if (D_80109C56_all_fired_up == 0) {
                HuAudFXPlay(0x443);
            }
            t = D_80109C56_all_fired_up;
            if (t == 30) {
                D_801099C8_all_fired_up = 2;
                D_80109C56_all_fired_up = 0;
                func_80106C68_all_fired_up();
            } else {
                D_80109C56_all_fired_up = t + 1;
            }
            break;
        case 2:
            if (D_80109C56_all_fired_up == 0) {
                D_80109C54_all_fired_up = D_801099D4_all_fired_up[D_80109C58_all_fired_up][D_80109AC4_all_fired_up++];
                if (D_80109AC4_all_fired_up >= 7) {
                    D_80109AC4_all_fired_up = 0;
                }
                func_80106FAC_all_fired_up();
                HuAudFXPlay(0x442);
            }
            t = D_80109C56_all_fired_up;
            if (t == 30) {
                D_801099C8_all_fired_up = 3;
                D_80109C56_all_fired_up = 0;
                D_801099CC_all_fired_up = 400.0f;
                D_801099D0_all_fired_up = 0;
            } else {
                D_80109C56_all_fired_up = t + 1;
            }
            break;
        case 3:
            if (D_80109C56_all_fired_up == 0) {
                HuAudFXPlay(0x442);
                D_80109C56_all_fired_up++;
                return;
            }
            t = D_80109C56_all_fired_up;
            if (t != 150) {
                D_80109C56_all_fired_up = t + 1;
            } else {
                D_801099C8_all_fired_up = 0;
                D_80109C56_all_fired_up = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801068F8_all_fired_up);
#endif

/* A new flame appears on the first one. */
void func_80106B7C_all_fired_up(void) {
    omObjData* first;
    omObjData* obj;
    AfFlame* src;
    AfFlame* w;

    D_801099C9_all_fired_up++;
    first = D_80109B00_all_fired_up[0];
    obj = D_80109B00_all_fired_up[D_801099C9_all_fired_up - 1];
    src = first->data;
    w = obj->data;
    obj->trans.x = first->trans.x;
    obj->trans.y = first->trans.y;
    obj->trans.z = first->trans.z;
    w->unk08 = src->unk08;
    w->unk0C = src->unk0C;
    w->unk14 = src->unk14;
    w->unk10 = src->unk10;
    func_8001C258_main(obj->model[0], 4, 0);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], w->unk08, w->unk08, w->unk08);
    func_8001C258_main(obj->model[1], 4, 0);
}

/* Remember where every flame is. */
void func_80106C68_all_fired_up(void) {
    AfFlame* w;
    s32 i;

    for (i = 0; i < D_801099C9_all_fired_up; i++) {
        w = D_80109B00_all_fired_up[i]->data;
        w->unk20.x = D_80109B00_all_fired_up[i]->trans.x;
        w->unk20.y = D_80109B00_all_fired_up[i]->trans.y;
        w->unk20.z = D_80109B00_all_fired_up[i]->trans.z;
    }
}

/* State 0: wander. */
void func_80106CDC_all_fired_up(omObjData* obj) {
    AfFlame* w = obj->data;

    if (D_801099C9_all_fired_up >= w->unk00) {
        if (obj->trans.y > 0.0f) {
            obj->trans.y -= 10.0f;
            if (obj->trans.y < 0.0f) {
                obj->trans.y = 0.0f;
            }
            w->unk10 = 0.0f;
            w->unk08 += 0.1f;
            if (w->unk08 > 1.0f) {
                w->unk08 = 1.0f;
            }
            Hu3DModelScaleSet(obj->model[1], w->unk08, w->unk08, w->unk08);
        }
        if (func_800E6E9C_minigame() % 15 == 0) {
            w->unk0C = (rand8() % 180) * 2;
        }
        if (HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z) >= 700.0f) {
            w->unk0C = atan2df(-obj->trans.x, -obj->trans.z);
        }
        obj->trans.x += sindf(w->unk0C) * 5.0f * w->unk18;
        obj->trans.z += cosdf(w->unk0C) * 5.0f * w->unk18;
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    }
}

/* State 1: gather at the centre. */
void func_80106F04_all_fired_up(omObjData* obj) {
    AfFlame* w = obj->data;

    if (D_801099C9_all_fired_up >= w->unk00) {
        obj->trans.x += (0.0f - w->unk20.x) / 30.0f;
        obj->trans.y += (0.0f - w->unk20.y) / 30.0f;
        obj->trans.z += (0.0f - w->unk20.z) / 30.0f;
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    }
}

/* Formation targets: 0 a circle, 1 a cross, 2 a jumping line. */
void func_80106FAC_all_fired_up(void) {
    AfFlame* w;
    f32 step;
    s32 half;
    s32 i;

    switch (D_80109C54_all_fired_up) {
        case 0:
            step = 360.0f / D_801099C9_all_fired_up;
            for (i = 0; i < D_801099C9_all_fired_up; i++) {
                w = D_80109B00_all_fired_up[i]->data;
                w->unk0C = step * w->unk00;
                w->unk2C.x = sindf(w->unk0C) * 400.0f;
                w->unk2C.y = 0.0f;
                w->unk2C.z = cosdf(w->unk0C) * 400.0f;
            }
            break;
        case 1:
            half = D_801099C9_all_fired_up / 2;
            if (D_801099C9_all_fired_up % 2 != 0) {
                step = 1400.0f / half;
            } else {
                step = 1400.0f / (half - 1);
            }
            for (i = 0; i < half; i++) {
                w = D_80109B00_all_fired_up[i]->data;
                if (D_801099C9_all_fired_up & 1) {
                    w->unk2C.x = step * w->unk00 + -700.0f + step / 2.0f;
                } else {
                    w->unk2C.x = step * w->unk00 + -700.0f;
                }
                w->unk2C.y = 0.0f;
                w->unk2C.z = 0.0f;
                w->unk0C = atan2df(w->unk2C.x, w->unk2C.z);
                w->unk14 = (w->unk2C.x > 0.0f) ? w->unk2C.x : 0.0f - w->unk2C.x;
            }
            for (i = half; i < D_801099C9_all_fired_up; i++) {
                w = D_80109B00_all_fired_up[i]->data;
                w->unk2C.x = 0.0f;
                w->unk2C.y = 0.0f;
                w->unk2C.z = step * (w->unk00 - half) + -700.0f;
                w->unk0C = atan2df(w->unk2C.x, w->unk2C.z);
                w->unk14 = (w->unk2C.z > 0.0f) ? w->unk2C.z : 0.0f - w->unk2C.z;
            }
            break;
        case 2:
            step = 1400.0f / (D_801099C9_all_fired_up - 1);
            for (i = 0; i < D_801099C9_all_fired_up; i++) {
                w = D_80109B00_all_fired_up[i]->data;
                w->unk2C.x = step * w->unk00 + -700.0f;
                w->unk10 = (360.0f / (D_801099C9_all_fired_up - 1)) * w->unk00;
                if (w->unk10 >= 180.0f) {
                    w->unk10 -= 180.0f;
                }
                w->unk2C.y = sindf(w->unk10) * 350.0f + 0.0f;
                w->unk2C.z = 0.0f;
                w->unk0C = atan2df(w->unk2C.x, 0.0f);
                w->unk14 = (w->unk2C.x > 0.0f) ? w->unk2C.x : 0.0f - w->unk2C.x;
                w->unk08 = 1.0f - sindf(w->unk10) * 0.4f;
            }
            break;
    }
}

/* State 2: move to the formation. */
void func_80107440_all_fired_up(omObjData* obj) {
    AfFlame* w = obj->data;

    if (D_801099C9_all_fired_up >= w->unk00) {
        switch (D_80109C54_all_fired_up) {
            case 0:
            case 1:
                obj->trans.x += (w->unk2C.x - 0.0f) / 30.0f;
                obj->trans.z += (w->unk2C.z - 0.0f) / 30.0f;
                break;
            case 2:
                obj->trans.x += (w->unk2C.x - 0.0f) / 30.0f;
                obj->trans.y += (w->unk2C.y - 0.0f) / 30.0f;
                obj->trans.z += (w->unk2C.z - 0.0f) / 30.0f;
                Hu3DModelScaleSet(obj->model[1], w->unk08, w->unk08, w->unk08);
                break;
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    }
}

/* State 3: run the formation (spin the circle in and out, turn the cross, roll the jumping line). */
void func_80107578_all_fired_up(omObjData* obj) {
    AfFlame* w = obj->data;
    MgWork* pw;
    s32 i;

    if (D_801099C9_all_fired_up >= w->unk00) {
        if (w->unk00 == 0) {
            switch (D_80109C54_all_fired_up) {
                case 0:
                    for (i = 0; i < 4; i++) {
                        pw = D_800EC598_minigame[i]->data;
                        if ((GwPlayer[pw->unk59].stat & 1) && pw->unk38 != 1000.0f) {
                            D_80109A04_all_fired_up = 1;
                            break;
                        }
                    }
                    if (D_801099CC_all_fired_up == 0.0f || D_801099CC_all_fired_up == 700.0f ||
                        (D_80109A04_all_fired_up != 0 && func_800E6E9C_minigame() % 15 == 0 && (rand8() >> 7) != 0)) {
                        D_80109C59_all_fired_up ^= 1;
                    }
                    break;
                case 2:
                    D_80109C59_all_fired_up = 0;
                    break;
                default:
                    if (func_800E6E9C_minigame() % 15 == 0 && (rand8() >> 7) != 0) {
                        D_80109C59_all_fired_up ^= 1;
                    }
                    break;
            }
        }
        switch (D_80109C54_all_fired_up) {
            case 0:
                if (D_80109C59_all_fired_up == 0) {
                    if (D_801099D0_all_fired_up == 0 && (rand8() & 1)) {
                        D_80109C59_all_fired_up = 1;
                    }
                }
                if (D_80109C59_all_fired_up != 0) {
                    D_801099CC_all_fired_up += 0.5f;
                    if (D_801099CC_all_fired_up > 700.0f) {
                        D_801099CC_all_fired_up = 700.0f;
                        D_801099D0_all_fired_up = 1;
                    }
                } else {
                    D_801099CC_all_fired_up -= 0.5f;
                    if (D_801099CC_all_fired_up < 0.0f) {
                        D_801099CC_all_fired_up = 0.0f;
                    }
                }
                w->unk0C += 1.5f;
                if (w->unk0C >= 360.0f) {
                    w->unk0C -= 360.0f;
                }
                obj->trans.x = sindf(w->unk0C) * D_801099CC_all_fired_up;
                obj->trans.z = cosdf(w->unk0C) * D_801099CC_all_fired_up;
                break;
            case 1:
                if (w->unk00 == 0 && func_800E6E9C_minigame() % 15 == 0) {
                    D_80109A00_all_fired_up = (f32)(rand8() % 15) / 10.0f + 1.0f;
                }
                if (D_80109C59_all_fired_up != 0) {
                    w->unk0C += D_80109A00_all_fired_up;
                    if (w->unk0C >= 360.0f) {
                        w->unk0C -= 360.0f;
                    }
                } else {
                    w->unk0C -= D_80109A00_all_fired_up;
                    if (w->unk0C < 0.0f) {
                        w->unk0C += 360.0f;
                    }
                }
                obj->trans.x = sindf(w->unk0C) * w->unk14;
                obj->trans.z = cosdf(w->unk0C) * w->unk14;
                break;
            case 2:
                if (w->unk00 == 0 && func_800E6E9C_minigame() % 5 == 0) {
                    D_80109A00_all_fired_up = (f32)(rand8() % 15) / 10.0f + 1.0f;
                }
                w->unk0C -= D_80109A00_all_fired_up;
                if (w->unk0C < 0.0f) {
                    w->unk0C += 360.0f;
                }
                obj->trans.x = sindf(w->unk0C) * w->unk14;
                obj->trans.z = cosdf(w->unk0C) * w->unk14;
                w->unk10 += 2.0f;
                if (w->unk10 >= 180.0f) {
                    w->unk10 -= 180.0f;
                }
                obj->trans.y = sindf(w->unk10) * 350.0f;
                w->unk08 = 1.0f - sindf(w->unk10) * 0.6f;
                Hu3DModelScaleSet(obj->model[1], w->unk08, w->unk08, w->unk08);
                break;
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    }
}

/* A flame touches a player still on the plate: burnt. */
void func_80107BD4_all_fired_up(omObjData* obj) {
    omObjData* player;
    MgWork* pw;
    f32 range = 66.0f;
    f32 dx;
    f32 dz;
    s32 i;

    for (i = 0; i < 4; i++) {
        player = D_800EC598_minigame[i];
        pw = player->data;
        if (player->work[0] == 0) {
            dx = AF_ABS(player->trans.x - obj->trans.x);
            dz = AF_ABS(player->trans.z - obj->trans.z);
            if ((dx < range) & (dz < range)) {
                if (player->trans.y < obj->trans.y + 36.0f && player->trans.y + 150.0f > obj->trans.y - 36.0f) {
                    player->work[0] = 1;
                    D_801099C0_all_fired_up[pw->unk59] = func_800E6E9C_minigame();
                    func_8004AC98_main(0x440, pw->unk59);
                    func_8004ACE0_main(0x286, pw->unk59);
                    omVibrate(pw->unk59, 2, 2, 20);
                }
            }
        }
    }
}

/* A player. */
void func_80107DA4_all_fired_up(omObjData* obj) {
    s8 chr;
    s32 dir;
    s32 file;
    MgWork* pw;
    AfPlayer* ex;
    f32 zero;
    s8 slot;

    chr = GwPlayer[D_80109A05_all_fired_up].chr;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][1];
    func_800E19F0_minigame(1);
    func_800E1BA8_minigame(obj, dir, file, D_80109A05_all_fired_up, 0x2C9, 0x2D9);
    pw = obj->data;
    pw->unk158 = HuMemAllocTag(sizeof(AfPlayer), 0x7918);
    memset(pw->unk158, 0, sizeof(AfPlayer));
    ex = pw->unk158;
    ex->unk04 = 0.0f;
    ex->unk00 = 1.0f;
    ex->unk08 = 0;
    ex->unk0C = 0.0f;
    zero = ex->unk0C;
    obj->rot.z = zero;
    obj->rot.y = zero;
    obj->rot.x = zero;
    obj->scale.z = 1.2f;
    obj->scale.y = 1.2f;
    obj->scale.x = 1.2f;
    obj->work[0] = 0;
    slot = D_80109AC5_all_fired_up = D_80109930_all_fired_up[D_80109AF0_all_fired_up][D_80109A05_all_fired_up];
    obj->trans.x = D_80109990_all_fired_up[slot].x;
    obj->trans.y = D_80109990_all_fired_up[slot].y;
    obj->trans.z = D_80109990_all_fired_up[slot].z;
    func_800E149C_minigame(obj, 0, 2);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, zero, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, 0x1A), 1, 0);
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    func_800E5690_minigame(obj, 0);
    func_800E1328_minigame(obj, 60.0f);
    obj->func = func_801080C8_all_fired_up;
    D_80109A05_all_fired_up++;
}

// masked 0: the burnt-player counters get $a1 where retail has $v1 (registers only); logic checked
#ifdef NON_MATCHING
/* A player's states: intro walk, play (CPU, hit test, burnt jump), results (rank by burn time), the finish. */
void func_801080C8_all_fired_up(omObjData* obj) {
    MgWork* pw = obj->data;
    s32 n;
    s32 i;
    s32 rank;
    s32 voice;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        switch (func_800E6E8C_minigame()) {
            case 0:
                func_801085A4_all_fired_up(obj);
                break;
            case 2:
                if (GwPlayer[pw->unk59].stat & 1) {
                    func_80108AA0_all_fired_up(obj);
                }
                func_800DDD94_minigame(obj);
                if (obj->work[0] == 1) {
                    func_800E5690_minigame(obj, 0xE);
                    func_80108710_all_fired_up(obj);
                    obj->work[0] = 2;
                } else if (obj->work[0] == 2) {
                    func_80108710_all_fired_up(obj);
                }
                n = 0;
                if (pw->unk59 == 3) {
                    for (i = 0; i < 4; i++) {
                        n += D_800EC598_minigame[i]->work[0] != 0;
                    }
                    if (n >= 3) {
                        func_800E6F0C_minigame(3);
                    }
                }
                break;
            case 3:
                rank = 0;
                if (D_80109A08_all_fired_up[pw->unk59] == 0) {
                    for (i = 0; i < 4; i++) {
                        if (i != pw->unk59) {
                            rank += D_801099C0_all_fired_up[pw->unk59] < D_801099C0_all_fired_up[i];
                        }
                    }
                    GwPlayer[pw->unk59].bonusCoin = rank;
                    D_80109A08_all_fired_up[pw->unk59] = 1;
                }
                if (obj->work[0] == 0) {
                    pw->unk3C *= 0.9f;
                }
                func_800DDD94_minigame(obj);
                if (obj->work[0] == 2) {
                    func_80108710_all_fired_up(obj);
                }
                break;
            case 4:
                if (func_800E6E9C_minigame() == 0) {
                    if (obj->work[0] == 0) {
                        switch (GwPlayer[pw->unk59].chr) {
                            case 0:
                            default:
                                voice = 2;
                                break;
                            case 1:
                                voice = 3;
                                break;
                            case 2:
                                voice = 7;
                                break;
                            case 3:
                                voice = 4;
                                break;
                            case 4:
                                voice = 5;
                                break;
                            case 5:
                                voice = 6;
                                break;
                            case 6:
                                voice = 8;
                                break;
                            case 7:
                                voice = 9;
                                break;
                        }
                        func_80045ED0_main((voice << 16) | 0x2F);
                        func_800E5690_minigame(obj, 0xD);
                        D_80109A06_all_fired_up = 0;
                    }
                    if (pw->unk59 == 3 && D_80109A06_all_fired_up == -1) {
                        D_80109A06_all_fired_up = 1;
                    }
                    switch (D_80109A06_all_fired_up) {
                        case 0:
                            for (n = 0, i = 0; i < 4; i++) {
                                n += GwPlayer[i].bonusCoin == 0;
                            }
                            if (n == 1) {
                                HuAudSeqPlay(0x65);
                            } else {
                                HuAudSeqPlay(0x66);
                            }
                            break;
                        case 1:
                            for (i = 0; i < 3; i++) {
                                if (D_801099C0_all_fired_up[i] != D_801099C0_all_fired_up[i + 1]) {
                                    break;
                                }
                            }
                            if (i == 3) {
                                for (i = 0; i < 4; i++) {
                                    GwPlayer[i].bonusCoin = 3;
                                }
                            }
                            HuAudSeqPlay(0x6C);
                            D_80109A06_all_fired_up = 1;
                            break;
                    }
                } else if ((D_80109A06_all_fired_up == 0 && func_800E6E9C_minigame() >= 100) ||
                           (D_80109A06_all_fired_up == 1 && func_800E6E9C_minigame() >= 145)) {
                    func_800E6F0C_minigame(5);
                }
                func_800DDD94_minigame(obj);
                break;
            default:
                func_800DDD94_minigame(obj);
                if (obj->work[0] == 2) {
                    func_80108710_all_fired_up(obj);
                }
                break;
        }
        obj->scale.z = 1.2f;
        obj->scale.x = 1.2f;
        if (!(pw->unk50 & 6)) {
            obj->scale.y = 1.2f;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801080C8_all_fired_up);
#endif

/* Intro: walk in from the start spot. */
void func_801085A4_all_fired_up(omObjData* obj) {
    MgWork* pw = obj->data;

    if (func_800E6E9C_minigame() == 20) {
        pw->unk3C = atan2df(obj->trans.x, obj->trans.z);
    } else if (func_800E6E9C_minigame() >= 21) {
        if (HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z) < 500.0f) {
            obj->trans.x += sindf(pw->unk3C) * 10.0f;
            obj->trans.z += cosdf(pw->unk3C) * 10.0f;
            func_800E5690_minigame(obj, 2);
        } else {
            pw->unk3C = atan2df(-obj->trans.x, -obj->trans.z);
            func_800E5690_minigame(obj, 0);
        }
        func_800E4E30_minigame(obj);
    }
    func_80088910_main((f32 (*)[4])HmfModelData[obj->model[0]].mtx, 0.0f, pw->unk3C, 0.0f);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
}

/* Burnt: the player jumps off the plate. */
void func_80108710_all_fired_up(omObjData* obj) {
    AfPlayer* ex;

    func_80108958_all_fired_up(obj);
    if (obj->trans.x > 0.0f) {
        obj->trans.x += 28.0f;
    } else {
        obj->trans.x -= 28.0f;
    }
    if (obj->trans.z > 0.0f) {
        obj->trans.z -= 28.0f;
    } else {
        obj->trans.z += 28.0f;
    }
    if (((obj->trans.x > 0.0f) ? obj->trans.x : 0.0f - obj->trans.x) > 700.0f) {
        func_800E149C_minigame(obj, 0, 1);
        func_8001C258_main(obj->model[1], 4, 4);
        if (obj->trans.y < -2000.0f) {
            obj->work[0] = 3;
        }
    }
    ex = ((MgWork*)obj->data)->unk158;
    if (ex->unk04 < 270.0f) {
        obj->trans.y = sindf(ex->unk04) * 400.0f;
        ex->unk04 += 6.0f;
    } else {
        obj->trans.y -= 50.0f;
    }
    ex->unk00 = 1.0f - sindf(ex->unk04) * 0.8f;
    Hu3DModelScaleSet(obj->model[1], ex->unk00, ex->unk00, ex->unk00);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
}

// masked 3: scheduling only (retail sets i = 0 between the row load and its address); logic checked
#ifdef NON_MATCHING
/* Burn smoke puffs (one model per player). */
void func_80108958_all_fired_up(omObjData* obj) {
    s32* timer;
    s32 i;
    f32 sc;

    for (i = 0, timer = D_80109A18_all_fired_up[((MgWork*)obj->data)->unk59]; i < 4; i++) {
        if (timer[i] >= 0) {
            if (timer[i] == 0) {
                Hu3DModelPosSet(D_80109AF2_all_fired_up[i], obj->trans.x, obj->trans.y, obj->trans.z);
                func_8001C258_main(D_80109AF2_all_fired_up[i], 4, 0);
            }
            if (timer[i] < 8) {
                sc = D_80109A58_all_fired_up[timer[i] / 2];
                Hu3DModelScaleSet(D_80109AF2_all_fired_up[i], sc, sc, 1.0f);
            }
            if (timer[i] >= 8) {
                timer[i] = -1;
            }
        }
        timer[i]++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80108958_all_fired_up);
#endif

// masked 234 of 836: retail keeps the nearest flame (a Vec at sp+0x14), the try count and the stick speed in the
// frame (0x98) and hoists the player position out of the nearest-flame loop; this C keeps more in registers. The
// logic is checked against the asm block by block (difficulty speeds, retry loop, ring and flame jumps, headings).
#ifdef NON_MATCHING
/* CPU: pick a heading away from the flames (and the ring's edge), set the stick and the jump button. */
void func_80108AA0_all_fired_up(omObjData* obj) {
    MgWork* pw;
    AfPlayer* ex;
    omObjData* fl;
    Vec near;
    f32 best;
    f32 dx;
    f32 dz;
    f32 d;
    f32 dist;
    f32 diag;
    f32 s;
    f32 c;
    f32 r;
    f32 stick;
    s32 i;
    s32 tries;
    s32 hit;
    s32 jump;
    u16 speed;

    near.z = 0.0f;
    near.x = near.z;
    hit = 0;
    jump = 0;
    if (obj->work[0] == 0) {
        pw = obj->data;
        ex = pw->unk158;
        switch (GwPlayer[pw->unk59].cpu_difficulty) {
            case 0:
                speed = 51;
                break;
            case 1:
                speed = 54;
                break;
            case 2:
                speed = 57;
                break;
            case 3:
                speed = 60;
                break;
            default:
                speed = 54;
                break;
        }
        if (ex->unk08 == 0) {
            ex->unk0C = (rand8() & 0xF) * 360 / 16;
            ex->unk08++;
        } else {
            ex->unk08++;
            if (ex->unk08 >= 15) {
                ex->unk08 = 0;
            }
        }
        best = 1960000.0f;
        for (i = 0; i < D_801099C9_all_fired_up; i++) {
            fl = D_80109B00_all_fired_up[i];
            dx = fl->trans.x - obj->trans.x;
            dz = fl->trans.z - obj->trans.z;
            d = dx * dx + dz * dz;
            if (d < best) {
                near.x = fl->trans.x;
                near.z = fl->trans.z;
                best = d;
            }
        }
        dist = HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
        tries = 0;
        do {
            if (ex->unk0C >= 360.0f) {
                ex->unk0C -= 360.0f;
            }
            s = sindf(ex->unk0C);
            c = cosdf(ex->unk0C);
            for (i = 0; i < D_801099C9_all_fired_up; i++) {
                fl = D_80109B00_all_fired_up[i];
                hit = 0;
                if (D_80109C54_all_fired_up == 0 && D_801099C8_all_fired_up == 3) {
                    if (D_80109C59_all_fired_up != 0) {
                        if (AF_ABS(D_801099CC_all_fired_up - dist) < 120.0f) {
                            jump = 1;
                        }
                    } else {
                        if (AF_ABS(D_801099CC_all_fired_up - dist) < 140.0f) {
                            jump = 1;
                        }
                    }
                } else {
                    if (D_801099C8_all_fired_up == 2) {
                        r = 250.0f;
                    } else if (D_801099C8_all_fired_up == 1) {
                        r = 200.0f;
                    } else if (D_801099C8_all_fired_up == 3) {
                        r = 150.0f;
                    } else {
                        r = 100.0f;
                    }
                    dx = fl->trans.x - obj->trans.x;
                    dz = fl->trans.z - obj->trans.z;
                    if (HuSqrtf(dx * dx + dz * dz) < r) {
                        if (jump == 1) {
                            if (fl->trans.y > 0.0f) {
                                jump = 0;
                            }
                        } else if (fl->trans.y == 0.0f) {
                            jump = 1;
                        }
                    }
                }
                if (D_801099C8_all_fired_up == 3 || D_801099C8_all_fired_up == 2) {
                    r = 400.0f;
                } else {
                    r = 200.0f;
                }
                dx = fl->trans.x - (s * r + obj->trans.x);
                dz = fl->trans.z - (c * r + obj->trans.z);
                if (HuSqrtf(dx * dx + dz * dz) < r) {
                    hit = 1;
                    break;
                }
            }
            if (hit == 0) {
                dx = s * 50.0f + obj->trans.x;
                dz = c * 50.0f + obj->trans.z;
                if (!(dx * dx + dz * dz > 490000.0f)) {
                    break;
                }
            }
            tries++;
            ex->unk0C += 0.022222222222222223;
        } while (tries < 8);
        diag = HuSqrtf(2.0f * (obj->trans.x * obj->trans.x));
        if (D_801099C8_all_fired_up == 1) {
            if (D_80109C56_all_fired_up < 21) {
                ex->unk0C = atan2df(obj->trans.x, obj->trans.z);
            } else {
                ex->unk0C = atan2df(obj->trans.x - near.x, obj->trans.z - near.z);
            }
        } else if (D_80109C54_all_fired_up == 0 && D_801099C8_all_fired_up == 3) {
            if (D_80109C59_all_fired_up != 0) {
                if (D_801099CC_all_fired_up > 350.0f) {
                    if (AF_ABS(obj->trans.x) < 150.0f && AF_ABS(obj->trans.z) < 150.0f) {
                        speed = 0;
                        pw->unk3C = atan2df(obj->trans.x, obj->trans.z);
                    } else {
                        ex->unk0C = pw->unk3C = atan2df(-obj->trans.x, -obj->trans.z);
                    }
                } else {
                    ex->unk0C = pw->unk3C = atan2df(obj->trans.x, obj->trans.z);
                }
            } else if (D_801099CC_all_fired_up < 350.0f) {
                ex->unk0C = pw->unk3C = atan2df(obj->trans.x, obj->trans.z);
            } else if (AF_ABS(obj->trans.x) < 150.0f && AF_ABS(obj->trans.z) < 150.0f) {
                speed = 0;
                pw->unk3C = atan2df(obj->trans.x, obj->trans.z);
            } else {
                ex->unk0C = pw->unk3C = atan2df(-obj->trans.x, -obj->trans.z);
            }
        } else if (D_801099C8_all_fired_up == 2) {
            if (D_80109C54_all_fired_up == 1 || D_80109C54_all_fired_up == 2) {
                if (AF_ABS(obj->trans.z) < 200.0f) {
                    if (obj->trans.z < 0.0f) {
                        ex->unk0C = 180.0f;
                    } else {
                        ex->unk0C = 0.0f;
                    }
                } else if (AF_ABS(obj->trans.x) < 200.0f) {
                    if (obj->trans.x < 0.0f) {
                        ex->unk0C = 270.0f;
                    } else {
                        ex->unk0C = 90.0f;
                    }
                } else {
                    ex->unk0C = atan2df(obj->trans.x - near.x, obj->trans.z - near.z);
                }
            }
        } else if (D_801099C8_all_fired_up != 3) {
            if (hit == 1) {
                ex->unk0C = atan2df(obj->trans.x - near.x, obj->trans.z - near.z);
            }
            speed *= 0.8f;
        } else if (D_80109C54_all_fired_up == 1 || D_80109C54_all_fired_up == 2) {
            func_80109660_all_fired_up(obj, diag, jump);
            if (D_800EB76C_minigame <= pw->unk40) {
                dx = sindf(pw->unk3C) * 200.0f + obj->trans.x - near.x;
                dz = cosdf(pw->unk3C) * 200.0f + obj->trans.z - near.z;
                if (dx * dx + dz * dz < 40000.0f) {
                    speed = 0;
                }
            }
        }
        stick = speed;
        D_800CBB6E_main[pw->unk57] = sindf(ex->unk0C) * stick;
        D_800D20A1_main[pw->unk57] = -cosdf(ex->unk0C) * stick;
        if (jump == 1) {
            D_800D5558_main[pw->unk57] |= 0x8000;
        } else {
            D_800D5558_main[pw->unk57] &= 0x7FFF;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80108AA0_all_fired_up);
#endif

/* CPU: the heading to dodge the circle (outward or inward, by the spin). */
void func_80109660_all_fired_up(omObjData* obj, f32 dist, s8 inner) {
    AfPlayer* ex = ((MgWork*)obj->data)->unk158;

    if (D_80109C59_all_fired_up != 0) {
        if (inner == 0) {
            if (dist > 600.0f) {
                ex->unk0C = atan2df(-obj->trans.x, -obj->trans.z) - 60.0f;
            } else {
                ex->unk0C = atan2df(-obj->trans.x, -obj->trans.z) - 90.0f;
            }
        } else {
            ex->unk0C = atan2df(-obj->trans.x, -obj->trans.z) + 90.0f;
        }
    } else if (inner != 0) {
        ex->unk0C = atan2df(-obj->trans.x, -obj->trans.z) - 90.0f;
    } else if (dist > 600.0f) {
        ex->unk0C = atan2df(-obj->trans.x, -obj->trans.z) + 60.0f;
    } else {
        ex->unk0C = atan2df(-obj->trans.x, -obj->trans.z) + 90.0f;
    }
}

/* The plate, and the title sprites. */
void func_801097B0_all_fired_up(omObjData* obj) {
    s16 file;
    s16 grp;
    s16 file2;
    s16 grp2;
    AfGround* g;

    obj->func = NULL;
    file = func_8000B838_main(0x4A0001);
    grp = HuSprGrpCreate(1, 0);
    func_80055024_main(grp, 0, file, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x5000);
    func_80054904_main(grp, 0, 160, 120);
    file2 = func_8000B838_main(0x4A0002);
    grp2 = HuSprGrpCreate(1, 0);
    func_80055024_main(grp2, 0, file2, 0);
    HuSprAttrReset(grp2, 0, 0xFFFF);
    HuSprAttrSet(grp2, 0, 0x1000);
    func_80054904_main(grp2, 0, 160, 180);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->model[0] = func_8000B0A0_main(0x4A0000, 0x29D);
    g = obj->data = HuMemAllocTag(sizeof(AfGround), 0x7918);
    memset(g, 0, sizeof(AfGround));
    g->unk03 = 1;
    g->unk04 = 0;
    g->unk08 = 0.5f;
}

/* Start slot of each player: one row per permutation of the four spots. */
u8 D_80109930_all_fired_up[24][4] = {
    { 0, 1, 2, 3 }, { 0, 1, 3, 2 }, { 0, 2, 1, 3 }, { 0, 2, 3, 1 }, { 0, 3, 1, 2 }, { 0, 3, 2, 1 },
    { 1, 0, 2, 3 }, { 1, 0, 3, 2 }, { 1, 2, 3, 0 }, { 1, 2, 0, 3 }, { 1, 3, 0, 2 }, { 1, 3, 2, 0 },
    { 2, 0, 1, 3 }, { 2, 0, 3, 1 }, { 2, 1, 0, 3 }, { 2, 1, 3, 0 }, { 2, 3, 0, 1 }, { 2, 3, 1, 0 },
    { 3, 0, 1, 2 }, { 3, 0, 2, 1 }, { 3, 1, 0, 2 }, { 3, 1, 2, 0 }, { 3, 2, 0, 1 }, { 3, 2, 1, 0 },
};
Vec D_80109990_all_fired_up[4] = {
    { 60.0f, 0.0f, -60.0f },
    { 60.0f, 0.0f, 60.0f },
    { -60.0f, 0.0f, 60.0f },
    { -60.0f, 0.0f, -60.0f },
};
u16 D_801099C0_all_fired_up[4] = { 1800, 1800, 1800, 1800 };
s8 D_801099C8_all_fired_up = 0;
s8 D_801099C9_all_fired_up = 15;
f32 D_801099CC_all_fired_up = 400.0f;
s8 D_801099D0_all_fired_up = 0;
/* Formation order (0 circle, 1 cross, 2 jumping line): one row per game. */
u8 D_801099D4_all_fired_up[6][6] = {
    { 0, 1, 2, 1, 0, 2 }, { 0, 2, 1, 0, 1, 2 }, { 0, 2, 0, 1, 2, 1 },
    { 2, 0, 2, 1, 2, 0 }, { 2, 0, 1, 0, 2, 1 }, { 2, 1, 0, 2, 0, 1 },
};
s32 D_801099F8_all_fired_up = 0;
s8 D_801099FC_all_fired_up = 0;
f32 D_80109A00_all_fired_up = 1.0f;
s8 D_80109A04_all_fired_up = 0;
s8 D_80109A05_all_fired_up = 0;
s8 D_80109A06_all_fired_up = -1;
s32 D_80109A08_all_fired_up[4] = { 0, 0, 0, 0 };
s32 D_80109A18_all_fired_up[4][4] = {
    { 0, -2, -4, -6 },
    { 0, -2, -4, -6 },
    { 0, -2, -4, -6 },
    { 0, -2, -4, -6 },
};
f32 D_80109A58_all_fired_up[4] = { 1.0f, 1.5f, 2.0f, 2.5f };
