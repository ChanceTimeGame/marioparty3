#include "common.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/util.h"
#include "game/wipe.h"
#include "game/window.h"
#include "game/hmfman.h"
#include "game/esprite.h"

// batter A: Hey, Batter, Batter! (one player bats pitches into the stands)

typedef struct HbCam {
    /* 0x00 */ f32 zoom;
    /* 0x04 */ Vec rot;
    /* 0x10 */ Vec center;
} HbCam; /* size 0x1C */


// main
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8000B5F0_main(u8 arg0);
s16 func_8000B638_main(void);
void GMesMaxTimeGet(s16 mesId, s16 time);
f32 sindf(f32);
void GMesPosSet(s16 mesId, f32 x, f32 y);
void func_800557A0_main(void);
void func_8000BC48_main(u16 arg0, u16 arg1);
s16 func_8000B13C_main(s32 arg0);
extern u16 D_800A11D0_main[6];
extern s16 D_800A11DC_main[5];

// LOCAL
void func_801059BC_hey_batter_batter(void);
void func_80105A4C_hey_batter_batter(void);
void func_80105AB8_hey_batter_batter(void);
void func_80105C44_hey_batter_batter(void);
void func_80105CE8_hey_batter_batter(omObjData* obj);
void func_80105DE0_hey_batter_batter(void);
void func_80106048_hey_batter_batter(omObjData* obj);
void func_801062E0_hey_batter_batter(omObjData* obj);
void func_80106744_hey_batter_batter(omObjData* obj);
void func_80106928_hey_batter_batter(omObjData* obj);
void func_80106C24_hey_batter_batter(omObjData* obj);
void func_80106CBC_hey_batter_batter(omObjData* obj);
void func_80106C6C_hey_batter_batter(omObjData* obj);
void func_80106FA8_hey_batter_batter(omObjData* obj);
s16 func_80109A78_hey_batter_batter(s32 file, u16 attr, u16 prio, s16 x, s16 y);
s16 func_80109B24_hey_batter_batter(s32 arg0);
void func_80106CE4_hey_batter_batter(omObjData* obj);
void func_801070D8_hey_batter_batter(omObjData* obj);
void func_80107144_hey_batter_batter(omObjData* obj);
void func_801079D0_hey_batter_batter(omObjData* obj);
void func_80108B48_hey_batter_batter(omObjData* obj);
void func_8010951C_hey_batter_batter(omObjData* obj);
void func_801098DC_hey_batter_batter(f32 zoom0, Vec rot0, Vec center0, f32 zoom1, Vec rot1, Vec center1, f32 frames, f32 t);

extern HbCam D_80109EB4_hey_batter_batter;
extern s16 D_80109ED0_hey_batter_batter; /* the batting player */
extern s16 D_80109ED6_hey_batter_batter;
extern s16 D_80109EE0_hey_batter_batter;
extern s16 D_80109EE2_hey_batter_batter;
extern s16 D_80109EE4_hey_batter_batter;
extern omObjData* D_80109EF4_hey_batter_batter;
extern s16 D_80109EF0_hey_batter_batter;
extern s16 D_80109EFA_hey_batter_batter;
extern s16 D_80109B60_hey_batter_batter;
extern s16 D_80109C30_hey_batter_batter; /* director state */
extern s16 D_80109C32_hey_batter_batter; /* result message */
extern s16 D_80109C34_hey_batter_batter; /* director timer */
extern s16 D_80109C36_hey_batter_batter; /* intro camera step */
extern s16 D_80109C38_hey_batter_batter; /* intro timer */
extern f32 D_80109C3C_hey_batter_batter; /* intro camera move frame */
extern s16 D_80109ED2_hey_batter_batter;
extern s16 D_80109C40_hey_batter_batter; /* batting phase step */
extern s16 D_80109C42_hey_batter_batter; /* batting phase timer */
extern s16 D_80109C44_hey_batter_batter; /* "start" message */
extern s16 D_80109C46_hey_batter_batter; /* countdown frames */
extern s16 D_80109ED4_hey_batter_batter;
extern s16 D_80109ED8_hey_batter_batter;
extern s16 D_80109EDA_hey_batter_batter;
extern s16 D_80109EDE_hey_batter_batter;
extern s16 D_80109EEE_hey_batter_batter;
extern s16 D_80109EFC_hey_batter_batter;
extern s16 D_80109EFE_hey_batter_batter;
extern s16 D_80109C48_hey_batter_batter; /* result step */
extern s16 D_80109C4A_hey_batter_batter; /* result camera frame */
extern Vec D_80109C4C_hey_batter_batter[5]; /* flag positions */
extern s16 D_80109F00_hey_batter_batter[5]; /* flag models */
extern s16 D_80109F0C_hey_batter_batter[5]; /* flag sway phases */
extern Vec D_80109BC4_hey_batter_batter[2]; /* result camera rotations */
extern Vec D_80109BDC_hey_batter_batter[2]; /* result camera centres */
extern Vec D_80109B64_hey_batter_batter[4]; /* camera rotations */
extern Vec D_80109B94_hey_batter_batter[4]; /* camera centres */

void func_801059A0_hey_batter_batter(void) {
    func_801059BC_hey_batter_batter();
}

void func_801059BC_hey_batter_batter(void) {
    Hu3DAnimInit(0x20);
    func_800142A0_main(0x20);
    omInitObjMan(0x20, 0x20);
    func_8004A208_main();
    func_80105A4C_hey_batter_batter();
    func_80105AB8_hey_batter_batter();
    func_80105C44_hey_batter_batter();
    omAddObj(1000, 0, 0, -1, func_80105CE8_hey_batter_batter);
    omAddObj(2000, 0, 0, -1, func_80106CBC_hey_batter_batter);
}

void func_80105A4C_hey_batter_batter(void) {
    HmfLightMaxSet(3);
    HmfLightDirSet(1, -10.0f, -10.0f, 150.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, -82.0f, 255.0f, -60.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
}

void func_80105AB8_hey_batter_batter(void) {
    s16 cam;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(cam, 45.0f, 80.0f, 8000.0f);
    D_80109EB4_hey_batter_batter.zoom = CZoom = 1065.0f;
    CRot.x = -15.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    D_80109EB4_hey_batter_batter.rot = CRot;
    Center.x = 0.0f;
    Center.y = 175.0f;
    Center.z = -200.0f;
    D_80109EB4_hey_batter_batter.center = Center;
}

/* Find the player in group 0 (the batter). */
void func_80105C44_hey_batter_batter(void) {
    s16 i = 0;
    u16 order[4] = { 0, 1, 2, 3 };

    for (; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    D_80109ED0_hey_batter_batter = (i < 4) ? order[i] : order[0];
}

void func_80105CE8_hey_batter_batter(omObjData* obj) {
    func_80105DE0_hey_batter_batter();
    omAddObj(10, 10, 0, -1, func_80106CE4_hey_batter_batter);
    omAddObj(20, 10, 0, -1, func_801070D8_hey_batter_batter);
    D_80109EF4_hey_batter_batter = omAddObj(30, 10, 10, -1, func_80107144_hey_batter_batter);
    omAddObj(40, 10, 10, -1, func_801079D0_hey_batter_batter);
    omAddObj(50, 20, 5, -1, func_80108B48_hey_batter_batter);
    omAddObj(60, 10, 10, -1, func_8010951C_hey_batter_batter);
    obj->func = func_80106048_hey_batter_batter;
}

/* The pitch count: a weighted draw over D_800A11DC_main; CPU batters get a few more or fewer. */
// masked 2: retail schedules the stack-array address before the u8 draw's andi (scheduling only)
#ifdef NON_MATCHING
void func_80105DE0_hey_batter_batter(void) {
    u8 r;
    s16 sum[5];
    s16 i;

    D_80109EE0_hey_batter_batter = 1;
    D_80109EE2_hey_batter_batter = 0;
    D_80109EE4_hey_batter_batter = 0;
    if (GwPlayer[D_80109ED0_hey_batter_batter].stat & 1) {
        sum[0] = D_800A11DC_main[0];
        for (i = 1; i < 5; i++) {
            sum[i] = sum[i - 1] + D_800A11DC_main[i];
        }
        r = rand8() % 100;
        for (i = 0; i < 5; i++) {
            if (r < sum[i]) {
                break;
            }
        }
        D_80109ED6_hey_batter_batter = i + 20;
        if (GwPlayer[D_80109ED0_hey_batter_batter].cpu_difficulty == 0) {
            if (!(rand8() & 3)) {
                if (!(rand8() & 1)) {
                    D_80109ED6_hey_batter_batter = 19 - (u8)(rand8() % 3);
                } else {
                    D_80109ED6_hey_batter_batter = (u8)(rand8() % 3) + 25;
                }
            }
        } else if (GwPlayer[D_80109ED0_hey_batter_batter].cpu_difficulty == 1 && !(rand8() & 0xF)) {
            if (!(rand8() & 1)) {
                D_80109ED6_hey_batter_batter = 19 - (rand8() & 1);
            } else {
                D_80109ED6_hey_batter_batter = (rand8() & 1) + 25;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80105DE0_hey_batter_batter);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106048_hey_batter_batter);

/* Intro: the camera tours the field from the batter to the stands and back. */
void func_801062E0_hey_batter_batter(omObjData* obj) {
    switch (D_80109C36_hey_batter_batter) {
    case 0:
        if (WipeStatGet() != 1) {
            HuAudSeqPlay(0x44);
            HuAudFXPlay(0x4D5);
            D_80109C3C_hey_batter_batter = 0.0f;
            D_80109C38_hey_batter_batter = 0;
            D_80109C36_hey_batter_batter = 1;
        }
        break;
    case 1:
        if (D_80109C38_hey_batter_batter++ >= 5) {
            D_80109C36_hey_batter_batter++;
            D_80109C38_hey_batter_batter = 0;
        }
        break;
    case 2:
        func_801098DC_hey_batter_batter(D_80109EB4_hey_batter_batter.zoom, D_80109B64_hey_batter_batter[0],
                                        D_80109B94_hey_batter_batter[0], D_80109EB4_hey_batter_batter.zoom,
                                        D_80109B64_hey_batter_batter[1], D_80109B94_hey_batter_batter[1], 20.0f,
                                        D_80109C3C_hey_batter_batter);
        if (sindf(D_80109C3C_hey_batter_batter * 4.5f) >= 1.0f) {
            D_80109C36_hey_batter_batter++;
            D_80109C3C_hey_batter_batter = 0.0f;
            D_80109B60_hey_batter_batter = 2;
        } else {
            D_80109C3C_hey_batter_batter += 1.0f;
        }
        break;
    case 3:
        if (D_80109C38_hey_batter_batter++ >= 30) {
            D_80109C36_hey_batter_batter++;
            D_80109C38_hey_batter_batter = 0;
        }
        break;
    case 4:
        func_801098DC_hey_batter_batter(D_80109EB4_hey_batter_batter.zoom, D_80109B64_hey_batter_batter[1],
                                        D_80109B94_hey_batter_batter[1], D_80109EB4_hey_batter_batter.zoom,
                                        D_80109B64_hey_batter_batter[3], D_80109B94_hey_batter_batter[3], 20.0f,
                                        D_80109C3C_hey_batter_batter);
        if (sindf(D_80109C3C_hey_batter_batter * 4.5f) >= 1.0f) {
            D_80109C36_hey_batter_batter++;
            D_80109C3C_hey_batter_batter = 0.0f;
        } else {
            D_80109C3C_hey_batter_batter += 1.0f;
        }
        break;
    case 5:
        if (D_80109C38_hey_batter_batter++ >= 20) {
            D_80109C36_hey_batter_batter++;
            D_80109C38_hey_batter_batter = 0;
            D_80109ED2_hey_batter_batter = 6;
        }
        break;
    case 6:
        func_801098DC_hey_batter_batter(D_80109EB4_hey_batter_batter.zoom, D_80109B64_hey_batter_batter[3],
                                        D_80109B94_hey_batter_batter[3], D_80109EB4_hey_batter_batter.zoom,
                                        D_80109B64_hey_batter_batter[0], D_80109B94_hey_batter_batter[0], 30.0f,
                                        D_80109C3C_hey_batter_batter);
        if (sindf(D_80109C3C_hey_batter_batter * 3.0f) == 1.0f) {
            D_80109C36_hey_batter_batter++;
            D_80109C3C_hey_batter_batter = 0.0f;
        } else {
            D_80109C3C_hey_batter_batter += 1.0f;
        }
        break;
    case 8:
        break;
    case 7:
        D_80109C3C_hey_batter_batter = 0.0f;
        D_80109C38_hey_batter_batter = 0;
        D_80109C36_hey_batter_batter = 0;
        obj->func = func_80106048_hey_batter_batter;
        break;
    }
}

/* The batting phase: start message, the countdown, then wait for the last pitch to settle. */
void func_80106744_hey_batter_batter(omObjData* obj) {
    switch (D_80109C40_hey_batter_batter) {
    case 0:
        D_80109C42_hey_batter_batter = 0;
        D_80109C40_hey_batter_batter = 0;
        D_80109C44_hey_batter_batter = 0;
        D_80109C46_hey_batter_batter = 91;
        D_80109C40_hey_batter_batter = 1;
        break;
    case 1:
        if (D_80109C42_hey_batter_batter++ >= 30) {
            D_80109EDA_hey_batter_batter = 3;
            D_80109C40_hey_batter_batter++;
        }
        break;
    case 2:
        HuAudFXPlay(8);
        D_80109C44_hey_batter_batter = GMesCreate(0x1A, 3, 150, 160);
        GMesPosSet(D_80109C44_hey_batter_batter, 150.0f, 160.0f);
        D_80109C40_hey_batter_batter++;
        break;
    case 3:
        if (D_80109C46_hey_batter_batter-- >= 0) {
            func_8003F578_main((D_80109C46_hey_batter_batter + 29) / 30);
        } else {
            func_8003F5C0_main();
            D_80109EDA_hey_batter_batter = 4;
            D_80109C40_hey_batter_batter++;
        }
        break;
    case 4:
        D_80109ED8_hey_batter_batter = 1;
        D_80109C40_hey_batter_batter++;
        break;
    case 5:
        if (D_80109EDE_hey_batter_batter == 2) {
            if ((D_80109ED4_hey_batter_batter == 1 && D_80109C42_hey_batter_batter++ >= 30) ||
                D_80109ED4_hey_batter_batter == 2) {
                obj->func = func_80106048_hey_batter_batter;
            }
        }
        break;
    case 6:
        break;
    }
}

/* The result: decide win or loss, move the camera onto the batter and play the reaction. */
void func_80106928_hey_batter_batter(omObjData* obj) {
    switch (D_80109C48_hey_batter_batter) {
    case 0:
        switch (D_80109ED4_hey_batter_batter) {
        case 1:
            D_80109EE0_hey_batter_batter = 0;
            break;
        case 2:
            D_80109EE0_hey_batter_batter = 1;
            break;
        }
        D_80109C48_hey_batter_batter++;
        break;
    case 1:
        if (D_80109EE0_hey_batter_batter == 0) {
            D_80109EEE_hey_batter_batter = 3;
            func_801098DC_hey_batter_batter(D_80109EB4_hey_batter_batter.zoom, D_80109B64_hey_batter_batter[0],
                                            D_80109B94_hey_batter_batter[0], D_80109EB4_hey_batter_batter.zoom,
                                            D_80109BC4_hey_batter_batter[0], D_80109BDC_hey_batter_batter[0], 30.0f,
                                            D_80109C4A_hey_batter_batter);
            if (sindf(D_80109C4A_hey_batter_batter * 3.0f) >= 1.0f) {
                D_80109C48_hey_batter_batter++;
                D_80109C4A_hey_batter_batter = 0;
            } else {
                D_80109C4A_hey_batter_batter++;
            }
        } else if (D_80109EE0_hey_batter_batter == 1) {
            D_80109C48_hey_batter_batter++;
        }
        break;
    case 2:
        if (D_80109EE0_hey_batter_batter == 1) {
            func_80017954_main(D_80109EF4_hey_batter_batter->model[0], 1, GwPlayer[D_80109ED0_hey_batter_batter].chr,
                               D_80109EFE_hey_batter_batter);
            D_80109ED2_hey_batter_batter = 3;
            D_80109EDA_hey_batter_batter = 1;
            HuAudFXPlay(0x4D8);
        } else if (D_80109EE0_hey_batter_batter == 0) {
            func_80017954_main(D_80109EF4_hey_batter_batter->model[0], 1, GwPlayer[D_80109ED0_hey_batter_batter].chr,
                               D_80109EFC_hey_batter_batter);
            D_80109ED2_hey_batter_batter = 2;
            D_80109EDA_hey_batter_batter = 2;
        }
        D_80109C48_hey_batter_batter++;
        break;
    case 3:
        obj->func = func_80106048_hey_batter_batter;
        break;
    }
}

void func_80106C24_hey_batter_batter(omObjData* obj) {
    WipeCreateOut(0, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80106C6C_hey_batter_batter;
}

void func_80106C6C_hey_batter_batter(omObjData* obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        GMesClose();
        func_8005F524_main();
        func_800557A0_main();
        omOvlReturnEx(1);
    }
}

/* Leave when the pause menu quits the minigame. */
void func_80106CBC_hey_batter_batter(omObjData* obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80106C24_hey_batter_batter;
    }
}

/* Background sprite and the five sway flags around the stands. */
void func_80106CE4_hey_batter_batter(omObjData* obj) {
    s16 i;
    u16 mdl;

    func_80109A78_hey_batter_batter(0x5D0000, 0x4000, 1000, 160, 120);
    for (i = 0; i < 2; i++) {
        mdl = func_8000B108_main(0x5D0003, 0x2A9);
        D_80109F00_hey_batter_batter[i] = mdl;
        Hu3DModelPosSet(mdl, D_80109C4C_hey_batter_batter[i].x, D_80109C4C_hey_batter_batter[i].y,
                        D_80109C4C_hey_batter_batter[i].z);
        Hu3DModelScaleSet(mdl, 2.0f, 2.0f, 2.0f);
        HmfModelData[(s16)mdl].rot.x = 20.0f;
        D_80109F0C_hey_batter_batter[i] = rand8() % 90;
    }
    for (; i < 5; i++) {
        mdl = func_8000B108_main(0x5D0003, 0x2A9);
        D_80109F00_hey_batter_batter[i] = mdl;
        Hu3DModelPosSet(mdl, D_80109C4C_hey_batter_batter[i].x, D_80109C4C_hey_batter_batter[i].y,
                        D_80109C4C_hey_batter_batter[i].z);
        Hu3DModelScaleSet(mdl, 2.0f, 2.0f, 2.0f);
        HmfModelData[(s16)mdl].rot.x = 20.0f;
        HmfModelData[(s16)mdl].rot.y = 90.0f;
        D_80109F0C_hey_batter_batter[i] = rand8() % 90;
    }
    obj->func = func_80106FA8_hey_batter_batter;
}

void func_80106FA8_hey_batter_batter(omObjData* obj) {
    s16 i;
    u16 mdl;
    s16* phase;

    for (i = 0; i < 5; i++) {
        mdl = D_80109F00_hey_batter_batter[i];
        phase = &D_80109F0C_hey_batter_batter[i];
        HmfModelData[(s16)mdl].scale.x = HmfModelData[(s16)mdl].scale.y = HmfModelData[(s16)mdl].scale.z =
            sindf(2.0f * *phase) * 0.5f + 2.0f;
        if ((*phase)++ >= 180.0f) {
            *phase = 0;
        }
    }
}

/* The stadium: field model and stands. */
void func_801070D8_hey_batter_batter(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0x5D0001, 0x2A9);
    obj->model[1] = func_8000B108_main(0x5D0002, 0x2A9);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, -1000.0f);
    obj->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80107144_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80107464_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_801079D0_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80107C48_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80108B48_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80108D90_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_8010951C_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80109630_hey_batter_batter);

/* Ease the camera from (zoom0, rot0, center0) to (zoom1, rot1, center1) over frames, at frame t. */
void func_801098DC_hey_batter_batter(f32 zoom0, Vec rot0, Vec center0, f32 zoom1, Vec rot1, Vec center1, f32 frames, f32 t) {
    f32 a = (90.0f / frames) * t;

    CZoom = zoom0 - sindf(a) * (zoom0 - zoom1);
    CRot.x = rot0.x - sindf(a) * (rot0.x - rot1.x);
    CRot.y = rot0.y - sindf(a) * (rot0.y - rot1.y);
    CRot.z = rot0.z - sindf(a) * (rot0.z - rot1.z);
    Center.x = center0.x - sindf(a) * (center0.x - center1.x);
    Center.y = center0.y - sindf(a) * (center0.y - center1.y);
    Center.z = center0.z - sindf(a) * (center0.z - center1.z);
    D_80109EB4_hey_batter_batter.zoom = CZoom;
    D_80109EB4_hey_batter_batter.rot = CRot;
    D_80109EB4_hey_batter_batter.center = Center;
}

s16 func_80109A78_hey_batter_batter(s32 file, u16 attr, u16 prio, s16 x, s16 y) {
    s16 id = InitEspriteSlot(func_8000B838_main(file), 0, 0);

    func_8000BC48_main(id, attr);
    func_8000BCC8_main(id, prio);
    func_8000BBD4_main(id, x, y);
    return id;
}

s16 func_80109B24_hey_batter_batter(s32 arg0) {
    s16 ret = func_8000B13C_main(arg0);

    if (ret < 0) {
        ret = -1;
    }
    return ret;
}
