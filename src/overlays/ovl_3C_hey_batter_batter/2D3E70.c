#include "ultra64.h"
#include "include_asm.h"
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
#include "game/data.h"

// batter A: Hey, Batter, Batter! (one player bats pitches into the stands)

typedef struct HbCam {
    /* 0x00 */ f32 zoom;
    /* 0x04 */ Vec rot;
    /* 0x10 */ Vec center;
} HbCam; /* size 0x1C */

typedef struct HbStand {
    /* 0x00 */ s16 target; /* target board */
    /* 0x02 */ s16 base;   /* its base */
} HbStand;


// main (functions.us.h is left out: its func_80017AD8_main returns u8, the function returns s16)
void func_80017954_main(s16, s16, s16, s16);
s16 func_80017790_main(s16 model, s32 arg1, s16 arg2, s32 arg3);
s32 func_80017BB8_main(s16, s16);
s16 func_80017AD8_main(s32);
extern u16 D_800D530C_main;
void func_8001C92C_main(s16 model, f32 arg1);
omObjData* func_80045ED0_main(u32 arg0);
s32 HmfAnimCreate(HmfData*, void*, s32, char*);
void func_80032FF8_main(s32, u8);
void func_80032FC0_main(s16, u8, u8);

/* D_800CCF58_main's records (common_structs.h D_800CCF58_main_Struct): motion length at 0x02 */
typedef struct HbMotInfo {
    /* 0x00 */ char unk00[2];
    /* 0x02 */ s16 unk02;
    /* 0x04 */ char unk04[0x14];
} HbMotInfo; /* size 0x18 */
extern HbMotInfo* D_800CCF58_main;
extern u16 D_800D5558_main[4];
s16 func_8000CED8_main(s32, s32);
u16 SprModelRead(s32 arg0, s32 arg1, s32 arg2);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_8000CD00_main(s16, f32, f32, f32);
void func_8000CFA4_main(s16, f32, f32, f32);
void func_8000D018_main(s16, f32);
void func_8001473C_main(s16 index, u16 arg1); /* src/14EA0.c defines arg1 as s16; retail calls it with a u16 here */

/* An entry of D_800CBB60_main (0x24 bytes; minigame BD210.c MgSprModel): its model at 0x00 */
typedef struct HbSprModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x1E];
    /* 0x20 */ u8* unk20; /* src/14EA0.c unk_800ECDE0: key-frame list */
} HbSprModel;
extern HbSprModel* D_800CBB60_main;
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
void func_8001EF6C_main(s16 arg0, s16 arg1, char* arg2);
extern s32 D_800A178C_main[][6];
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
void func_80107464_hey_batter_batter(omObjData* obj);
void func_80107C48_hey_batter_batter(omObjData* obj);
void func_80108D90_hey_batter_batter(omObjData* obj);
void func_80109630_hey_batter_batter(omObjData* obj);
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
extern s16 D_80109EF8_hey_batter_batter[4]; /* batter motions */
extern s16 D_80109C88_hey_batter_batter; /* batter motion shown */
extern s16 D_80109C8A_hey_batter_batter; /* batter cue step */
extern s16 D_80109C8C_hey_batter_batter; /* batter cue timer */
extern s16 D_80109C8E_hey_batter_batter; /* pitcher motion shown */
extern f32 D_80109C90_hey_batter_batter; /* ball frame */
extern s16 D_80109C94_hey_batter_batter; /* ball step */
extern s16 D_80109C96_hey_batter_batter; /* frames since the swing */
extern f32 D_80109C98_hey_batter_batter; /* ball flight frames */
extern f32 D_80109C9C_hey_batter_batter; /* pitch distance */
extern f32 D_80109CA0_hey_batter_batter; /* pitch arc height */
extern s16 D_80109CA4_hey_batter_batter; /* 1: the swing connects */
extern Vec D_80109CA8_hey_batter_batter[7]; /* hit targets by zone */
extern s16 D_80109CFC_hey_batter_batter; /* hit zone: 1-5 into a stand, 0 and 6 foul */
extern f32 D_80109D00_hey_batter_batter; /* foul ball vertical speed */
extern s16 D_80109EA0_hey_batter_batter; /* contact x */
extern s16 D_80109EA2_hey_batter_batter; /* contact y */
extern s16 D_80109EA4_hey_batter_batter; /* contact z */
extern s16 D_80109EA6_hey_batter_batter; /* hit speed x */
extern s16 D_80109EA8_hey_batter_batter; /* hit speed y */
extern s16 D_80109EAA_hey_batter_batter; /* hit speed z */
extern s16 D_80109EAC_hey_batter_batter; /* foul ball frame */
extern s16 D_80109EAE_hey_batter_batter; /* 1: swung */
extern Vec D_80109D04_hey_batter_batter[5]; /* stand target positions */
extern HbStand D_80109F18_hey_batter_batter[5];
extern s16 D_80109F2C_hey_batter_batter[5]; /* coin-count sprite models */
extern Vec D_80109BF4_hey_batter_batter[5]; /* coin-count positions over the stands */
extern s32 D_80109D40_hey_batter_batter[20]; /* coin-count sprite files by count */
extern u16 D_80109D90_hey_batter_batter; /* stand hit */
extern u16 D_80109D92_hey_batter_batter; /* its coin-count model */
extern s16 D_80109D94_hey_batter_batter; /* prize bob frame */
extern s16 D_80109D96_hey_batter_batter; /* prize step */
extern s16 D_80109D98_hey_batter_batter; /* prize sprite */
extern s16 D_80109EEA_hey_batter_batter[2]; /* 1: show the stand fireworks, the batter's burst */
extern s16 D_80109EDC_hey_batter_batter;
extern s16 D_80109EE6_hey_batter_batter[2]; /* fireworks burst and spark motions */
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

/* The minigame's director: wipe in, the intro, the batting phase, the result and the exit. */
void func_80106048_hey_batter_batter(omObjData* obj) {
    switch (D_80109C30_hey_batter_batter) {
    case 0:
        WipeCreateIn(0xFF, 16);
        D_80109C30_hey_batter_batter++;
        break;
    case 1:
        obj->func = func_801062E0_hey_batter_batter;
        D_80109C30_hey_batter_batter++;
        break;
    case 2:
        if (++D_80109C34_hey_batter_batter == 1) {
            GMesCreate(8);
        } else if (GMesStatGet() == 0) {
            D_80109C34_hey_batter_batter = 0;
            D_80109C30_hey_batter_batter++;
        }
        break;
    case 3:
        obj->func = func_80106744_hey_batter_batter;
        D_80109C30_hey_batter_batter++;
        break;
    case 4:
        if (++D_80109C34_hey_batter_batter == 1) {
            func_80017954_main(D_80109EF4_hey_batter_batter->model[0], 1, GwPlayer[D_80109ED0_hey_batter_batter].chr,
                               D_80109EF8_hey_batter_batter[1]);
            D_80109B60_hey_batter_batter = 1;
            GMesCreate(0x13);
            HuAudSeqFadeOut(120);
        } else if (GMesStatGet() == 0) {
            D_80109C34_hey_batter_batter = 0;
            D_80109C30_hey_batter_batter++;
        }
        break;
    case 5:
        obj->func = func_80106928_hey_batter_batter;
        D_80109C30_hey_batter_batter++;
        break;
    case 6:
        if (++D_80109C34_hey_batter_batter == 1) {
            switch (D_80109EE0_hey_batter_batter) {
            case 0:
                HuAudSeqPlay(0x68);
                D_80109C32_hey_batter_batter = GMesCreate(0x24);
                GwPlayer[D_80109ED0_hey_batter_batter].bonusCoin = D_800A11D0_main[D_80109EF0_hey_batter_batter];
                break;
            case 1:
                HuAudSeqPlay(0x6B);
                D_80109C32_hey_batter_batter = GMesCreate(0x1D);
                GwPlayer[D_80109ED0_hey_batter_batter].bonusCoin = -1;
                break;
            }
            GMesMaxTimeGet(D_80109C32_hey_batter_batter, 120);
        } else if (D_80109C34_hey_batter_batter >= 135) {
            D_80109C34_hey_batter_batter = 0;
            D_80109C30_hey_batter_batter++;
        }
        break;
    case 7:
        obj->func = func_80106C24_hey_batter_batter;
        break;
    case 8:
        break;
    }
}

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
                               D_80109EF8_hey_batter_batter[3]);
            D_80109ED2_hey_batter_batter = 3;
            D_80109EDA_hey_batter_batter = 1;
            HuAudFXPlay(0x4D8);
        } else if (D_80109EE0_hey_batter_batter == 0) {
            func_80017954_main(D_80109EF4_hey_batter_batter->model[0], 1, GwPlayer[D_80109ED0_hey_batter_batter].chr,
                               D_80109EF8_hey_batter_batter[2]);
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

/* The batter: character model, bat and shadow, motions. */
void func_80107144_hey_batter_batter(omObjData* obj) {
    s32 chr = GwPlayer[D_80109ED0_hey_batter_batter].chr;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x6A8);
    obj->model[1] = func_8000B108_main(0x5D0005, 0x6A9);
    obj->model[2] = func_8000B108_main(9, 0x2A9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x82));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x35));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x38));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x83));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 1));
    if (chr == 5) {
        func_8000B460_main(obj, 6, 0x5D000A);
    }
    func_8001C258_main(obj->model[1], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[1], obj->model[0], "item_hook");
    omSetTra(obj, -150.0f, 15.0f, 0.0f);
    omSetRot(obj, 0.0f, 180.0f, 0.0f);
    Hu3DModelPosSet(obj->model[2], -150.0f, 15.0f, 0.0f);
    GwPlayer[D_80109ED0_hey_batter_batter].bonusCoin = -1;
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[1]].unk02, 0, 2, 2);
    D_80109ED2_hey_batter_batter = 1;
    D_80109EF8_hey_batter_batter[0] = func_80017790_main(obj->model[0], 1, chr, func_80017BB8_main(chr, 0xAA));
    D_80109EF8_hey_batter_batter[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xA4));
    D_80109EF8_hey_batter_batter[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80109EF8_hey_batter_batter[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA6));
    func_8001C514_main(obj->model[0]);
    func_80017954_main(obj->model[0], 1, GwPlayer[D_80109ED0_hey_batter_batter].chr, D_80109EF8_hey_batter_batter[0]);
    obj->func = func_80107464_hey_batter_batter;
}

/* The batter: play the motion for D_80109ED2 when it changes, and the intro and swing cues. */
void func_80107464_hey_batter_batter(omObjData* obj) {
    if (D_80109C88_hey_batter_batter != D_80109ED2_hey_batter_batter) {
        switch (D_80109ED2_hey_batter_batter) {
        case 0:
        case 1:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_80109ED2_hey_batter_batter]].unk02, 0, 30, 2);
            break;
        case 2:
            func_8001C5B4_main(obj->model[0], obj->motion[2]);
            func_80045ED0_main(D_800A178C_main[GwPlayer[D_80109ED0_hey_batter_batter].chr][0] | 0x35);
            break;
        case 3:
            func_8001C5B4_main(obj->model[0], obj->motion[3]);
            func_80045ED0_main(D_800A178C_main[GwPlayer[D_80109ED0_hey_batter_batter].chr][0] | 0x38);
            break;
        case 4:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_80109ED2_hey_batter_batter]].unk02, 0, 15, 0);
            break;
        case 5:
            func_8001C5B4_main(obj->model[0], obj->motion[4]);
            func_8001C6A8_main(obj->model[0], D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02);
            func_8001C92C_main(obj->model[0], -0.9f);
            break;
        case 6:
            func_8001C92C_main(obj->model[0], 1.0f);
            break;
        case 7:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[5]].unk02, 0, 10, 2);
            break;
        case 8:
            func_8001C5B4_main(obj->model[0], obj->motion[6]);
            break;
        }
        D_80109C88_hey_batter_batter = D_80109ED2_hey_batter_batter;
    }
    if (D_80109B60_hey_batter_batter == 1) {
        switch (D_80109C8A_hey_batter_batter) {
        case 0:
            D_80109EEA_hey_batter_batter[1] = 1;
            if (GwPlayer[D_80109ED0_hey_batter_batter].chr == 5 && D_80109ED2_hey_batter_batter == 4) {
                D_80109ED2_hey_batter_batter = 8;
            } else {
                D_80109ED2_hey_batter_batter = 0;
            }
            func_8001C8A8_main(obj->model[1], 0);
            D_80109C8A_hey_batter_batter++;
            break;
        case 1:
            if (D_80109C8C_hey_batter_batter++ >= 45) {
                D_80109C8A_hey_batter_batter++;
            }
            break;
        case 2:
            if (obj->rot.y > 0.0f) {
                D_80109ED2_hey_batter_batter = 7;
                obj->rot.y -= 10.0f;
            } else {
                D_80109ED2_hey_batter_batter = 0;
                D_80109C8A_hey_batter_batter++;
            }
            break;
        }
    }
    if (D_80109B60_hey_batter_batter == 2) {
        switch (D_80109C8A_hey_batter_batter) {
        case 0:
            HuAudFXPlay(0x4D0);
            D_80109ED2_hey_batter_batter = 4;
            D_80109C8A_hey_batter_batter++;
            break;
        case 1:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 == HmfModelData[obj->model[0]].unk40) {
                D_80109ED2_hey_batter_batter = 5;
                D_80109C8A_hey_batter_batter++;
            }
            break;
        case 2:
            if (HmfModelData[obj->model[0]].unk40 <= 3.0f) {
                D_80109ED2_hey_batter_batter = 1;
                func_8001C92C_main(obj->model[0], 0.0f);
                func_8001C6A8_main(obj->model[0], 0.0f);
                D_80109C8A_hey_batter_batter = 0;
                D_80109B60_hey_batter_batter = 0;
            }
            break;
        }
    }
}

/* The pitcher: model with its glove and ball, shadows, and its motions. */
void func_801079D0_hey_batter_batter(omObjData* obj) {
    void* data;
    s16 anim;

    obj->model[0] = func_8000B108_main(0xA00EE, 0x2A9);
    obj->model[1] = func_8000B108_main(0x5D0009, 0x2A9);
    obj->model[2] = func_8000B108_main(9, 0x6A9);
    obj->model[3] = func_8000B108_main(0x5D0004, 0x2A9);
    obj->model[4] = func_8000B108_main(9, 0x6A9);
    data = DataRead(0xA0100);
    anim = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "c162n_0_DEF");
    DataClose(data);
    func_8001C448_main(obj->model[0]);
    func_80032FF8_main(anim, 0);
    func_80032FC0_main(anim, 1, 0);
    func_8000B460_main(obj, 0, 0xA00F7);
    func_8000B460_main(obj, 1, 0xA00F6);
    func_8000B460_main(obj, 2, 0xA00F2);
    func_8000B460_main(obj, 3, 0xA00F8);
    func_8000B460_main(obj, 4, 0xA00F9);
    func_8000B460_main(obj, 5, 0xA00FA);
    func_8001C258_main(obj->model[1], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[1], obj->model[0], "c162_000-te2");
    func_8001C8A8_main(obj->model[1], 1);
    omSetTra(obj, 0.0f, 5.5f, -1000.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 4.0f, -1000.0f);
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 2, 2);
    D_80109EDA_hey_batter_batter = 0;
    func_8001C8A8_main(obj->model[3], 0);
    func_8001C8A8_main(obj->model[4], 0);
    obj->func = func_80107C48_hey_batter_batter;
}

/* The pitcher and the ball: pitch, the batter's swing window, the hit's flight and its zone. */
void func_80107C48_hey_batter_batter(omObjData* obj) {
    f32 scale;

    if (D_80109C8E_hey_batter_batter != D_80109EDA_hey_batter_batter) {
        switch (D_80109EDA_hey_batter_batter) {
        case 2:
        case 4:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_80109EDA_hey_batter_batter]].unk02, 0, 30, 0);
            break;
        case 0:
        case 1:
        case 3:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_80109EDA_hey_batter_batter]].unk02, 0, 30, 2);
            break;
        case 5:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_80109EDA_hey_batter_batter]].unk02, 0, 10, 0);
            func_8001C92C_main(obj->model[0], 0.0f);
            func_8001C6A8_main(obj->model[0], 0.0f);
            break;
        }
        D_80109C8E_hey_batter_batter = D_80109EDA_hey_batter_batter;
    }
    if (D_80109ED8_hey_batter_batter == 1 && HmfModelData[obj->model[0]].unk40 >= 26.0f) {
        HuAudFXPlay(0x4D1);
        func_8001C8A8_main(obj->model[1], 0);
        D_80109EDE_hey_batter_batter = 1;
        D_80109ED8_hey_batter_batter = 0;
        D_80109C98_hey_batter_batter = 30.0f;
        D_80109CA0_hey_batter_batter = (u8)(rand8() % 50) + 100.0f;
    }
    if (D_80109EDE_hey_batter_batter == 1) {
        switch (D_80109C94_hey_batter_batter) {
        case 0:
            Hu3DModelPosSet(obj->model[3], -30.0f, 70.0f, -1015.0f);
            func_8001C8A8_main(obj->model[3], 1);
            func_8001C8A8_main(obj->model[4], 1);
            D_80109C90_hey_batter_batter = 1.0f;
            D_80109C96_hey_batter_batter = 0;
            D_80109EAE_hey_batter_batter = 0;
            D_80109C94_hey_batter_batter++;
            break;
        case 1:
            HmfModelData[obj->model[3]].pos.z += D_80109C9C_hey_batter_batter / D_80109C98_hey_batter_batter;
            if (HmfModelData[obj->model[3]].pos.y > 50.0f) {
                HmfModelData[obj->model[3]].pos.y =
                    sindf((90.0f / (D_80109C98_hey_batter_batter / 2.0f)) * D_80109C90_hey_batter_batter) *
                        D_80109CA0_hey_batter_batter +
                    70.0f;
            } else {
                HmfModelData[obj->model[3]].pos.y = 50.0f;
            }
            HmfModelData[obj->model[3]].rot.x += 30.0f;
            if (D_80109EAE_hey_batter_batter == 0) {
                if (GwPlayer[D_80109ED0_hey_batter_batter].stat & 1) {
                    if (D_80109C90_hey_batter_batter == D_80109ED6_hey_batter_batter) {
                        D_80109EAE_hey_batter_batter = 1;
                        HuAudFXPlay(0x4D0);
                        D_80109ED2_hey_batter_batter = 4;
                        if (D_80109C98_hey_batter_batter - 11.0f <= D_80109C90_hey_batter_batter &&
                            D_80109C90_hey_batter_batter < D_80109C98_hey_batter_batter - 4.0f) {
                            D_80109CFC_hey_batter_batter =
                                (D_80109C98_hey_batter_batter - D_80109C90_hey_batter_batter) - 5.0f;
                            D_80109CA4_hey_batter_batter = 1;
                        } else {
                            D_80109CA4_hey_batter_batter = 0;
                        }
                    }
                } else if (D_800D5558_main[GwPlayer[D_80109ED0_hey_batter_batter].pad] & 0x8000) {
                    D_80109EAE_hey_batter_batter = 1;
                    HuAudFXPlay(0x4D0);
                    D_80109ED2_hey_batter_batter = 4;
                    if (D_80109C98_hey_batter_batter - 11.0f <= D_80109C90_hey_batter_batter &&
                        D_80109C90_hey_batter_batter < D_80109C98_hey_batter_batter - 4.0f) {
                        omVibrate(D_80109ED0_hey_batter_batter, 2, 2, 20);
                        D_80109CFC_hey_batter_batter =
                            (D_80109C98_hey_batter_batter - D_80109C90_hey_batter_batter) - 5.0f;
                        D_80109CA4_hey_batter_batter = 1;
                    } else {
                        D_80109CA4_hey_batter_batter = 0;
                    }
                }
            }
            if (D_80109CA4_hey_batter_batter == 1 && ++D_80109C96_hey_batter_batter == 8) {
                D_80109C94_hey_batter_batter++;
                break;
            }
            if (HmfModelData[obj->model[3]].pos.z >= 500.0f) {
                func_8001C8A8_main(obj->model[3], 0);
                D_80109C94_hey_batter_batter++;
            }
            D_80109C90_hey_batter_batter += 1.0f;
            break;
        case 2:
            if (D_80109CA4_hey_batter_batter == 1) {
                HuAudFXPlay((D_80109CFC_hey_batter_batter == 0 || D_80109CFC_hey_batter_batter == 6) ? 0x4D9 : 0x4D2);
                HuAudFXPlay(0x4D6);
                D_80109C94_hey_batter_batter++;
            } else if (D_80109CA4_hey_batter_batter == 0) {
                D_80109EDE_hey_batter_batter = 2;
                D_80109ED4_hey_batter_batter = 2;
                break;
            }
        case 3:
            D_80109EA0_hey_batter_batter = HmfModelData[obj->model[3]].pos.x;
            D_80109EA2_hey_batter_batter = HmfModelData[obj->model[3]].pos.y;
            D_80109EA4_hey_batter_batter = HmfModelData[obj->model[3]].pos.z;
            Hu3DModelPosSet(obj->model[3], D_80109EA0_hey_batter_batter, D_80109EA2_hey_batter_batter,
                            D_80109EA4_hey_batter_batter);
            D_80109EA6_hey_batter_batter =
                (D_80109CA8_hey_batter_batter[D_80109CFC_hey_batter_batter].x + (u8)(rand8() % 50) -
                 D_80109EA0_hey_batter_batter) /
                10.0f;
            D_80109EA8_hey_batter_batter =
                (D_80109CA8_hey_batter_batter[D_80109CFC_hey_batter_batter].y + (u8)(rand8() % 50) -
                 D_80109EA2_hey_batter_batter) /
                10.0f;
            D_80109EAA_hey_batter_batter =
                (D_80109CA8_hey_batter_batter[D_80109CFC_hey_batter_batter].z - D_80109EA4_hey_batter_batter) / 10.0f;
            D_80109C98_hey_batter_batter = 10.0f;
            D_80109C90_hey_batter_batter = 0.0f;
            D_80109CA0_hey_batter_batter = (u8)(rand8() % 200);
            D_80109C94_hey_batter_batter++;
            D_80109D00_hey_batter_batter = -2.0f;
            D_80109EAC_hey_batter_batter = 0;
        case 4:
        case 6:
            if (D_80109CFC_hey_batter_batter >= 1 && D_80109CFC_hey_batter_batter <= 5) {
                HmfModelData[obj->model[3]].pos.x += D_80109EA6_hey_batter_batter;
                HmfModelData[obj->model[3]].pos.y += D_80109EA8_hey_batter_batter;
                HmfModelData[obj->model[3]].pos.z += D_80109EAA_hey_batter_batter;
                HmfModelData[obj->model[3]].rot.x -= 50.0f;
                if (D_80109C98_hey_batter_batter == D_80109C90_hey_batter_batter) {
                    HuAudFXPlay(0x4D3);
                    D_80109C94_hey_batter_batter++;
                    break;
                }
                D_80109C90_hey_batter_batter += 1.0f;
                break;
            }
            if (D_80109EAC_hey_batter_batter == 10) {
                D_80109EDA_hey_batter_batter = 5;
            }
            if (D_80109CFC_hey_batter_batter == 0) {
                HmfModelData[obj->model[3]].pos.z =
                    D_80109EA4_hey_batter_batter +
                    sindf(D_80109EAC_hey_batter_batter * 0.75f) * (D_80109EA4_hey_batter_batter + -1300.0f);
            } else {
                HmfModelData[obj->model[3]].pos.z =
                    D_80109EA4_hey_batter_batter +
                    sindf(D_80109EAC_hey_batter_batter * 0.75f) * (D_80109EA4_hey_batter_batter + -860.0f);
            }
            if (HmfModelData[obj->model[3]].pos.y >= 0.0f) {
                HmfModelData[obj->model[3]].pos.y += D_80109D00_hey_batter_batter * D_80109D00_hey_batter_batter *
                                                     (D_80109D00_hey_batter_batter >= 0.0f ? -35.0f : 35.0f);
                if (D_80109D00_hey_batter_batter >= 1.4f) {
                    D_80109D00_hey_batter_batter = 1.4f;
                } else {
                    D_80109D00_hey_batter_batter += 0.055f;
                }
            }
            if (D_80109EAC_hey_batter_batter == 75) {
                func_8001C92C_main(obj->model[0], 1.0f);
            }
            if (D_80109EAC_hey_batter_batter == 80) {
                HuAudFXPlay(0x4D4);
                func_8001C8A8_main(obj->model[1], 1);
                func_8001C8A8_main(obj->model[4], 0);
                func_8001C8A8_main(obj->model[3], 0);
            }
            if (D_80109EAC_hey_batter_batter++ >= 85) {
                D_80109C94_hey_batter_batter = 5;
                func_8001C8A8_main(obj->model[1], 1);
            }
            break;
        case 5:
            if (D_80109CFC_hey_batter_batter >= 1 && D_80109CFC_hey_batter_batter <= 5) {
                func_8001C8A8_main(obj->model[3], 0);
                func_8001C8A8_main(obj->model[4], 0);
                D_80109ED4_hey_batter_batter = 1;
                D_80109EF0_hey_batter_batter = D_80109CFC_hey_batter_batter - 1;
                D_80109EEE_hey_batter_batter = 1;
            } else {
                D_80109ED4_hey_batter_batter = 2;
            }
            D_80109EDE_hey_batter_batter = 2;
            D_80109C94_hey_batter_batter = 0;
            D_80109C90_hey_batter_batter = 0.0f;
            break;
        }
    }
    scale = 1.0f - HmfModelData[obj->model[3]].pos.y * 0.0005f;
    Hu3DModelPosSet(obj->model[4], HmfModelData[obj->model[3]].pos.x, 10.0f, HmfModelData[obj->model[3]].pos.z);
    Hu3DModelScaleSet(obj->model[4], scale, scale, scale);
}

/* The five stand targets with their coin prizes, the hit flash and the home-run effect. */
void func_80108B48_hey_batter_batter(omObjData* obj) {
    s16 i;
    s16 spr;
    u16 target;
    u16 base;
    u16 count;
    HbStand* stand;

    for (i = 0; i < 5; i++) {
        target = func_8000B108_main(0x5D0006, 0x6A9);
        stand = &D_80109F18_hey_batter_batter[i];
        stand->target = target;
        Hu3DModelPosSet(target, D_80109D04_hey_batter_batter[i].x, D_80109D04_hey_batter_batter[i].y + 1.0f,
                        D_80109D04_hey_batter_batter[i].z);
        base = func_8000B108_main(0x5D0007, 0x2A9);
        stand->base = base;
        Hu3DModelPosSet(base, D_80109D04_hey_batter_batter[i].x, D_80109D04_hey_batter_batter[i].y,
                        D_80109D04_hey_batter_batter[i].z);
        spr = SprModelRead(0x21002C, 0xA0, 0x10);
        count = D_800CBB60_main[spr].unk00;
        D_80109F2C_hey_batter_batter[i] = count;
        func_8001473C_main(spr, D_800A11D0_main[i]);
        Hu3DModelPosSet(count, D_80109D04_hey_batter_batter[i].x, D_80109D04_hey_batter_batter[i].y + 250.0f,
                        D_80109D04_hey_batter_batter[i].z + 2.0f);
        Hu3DModelScaleSet(count, 6.0f, 6.0f, 6.0f);
    }
    obj->model[2] = func_8000B108_main(9, 0x6A9);
    func_8001C8A8_main(obj->model[2], 0);
    obj->model[3] = func_8000CED8_main(0xB0004, 0x6A9);
    func_800138EC_main(obj->model[3], 1, 0);
    D_80109EEE_hey_batter_batter = 0;
    obj->func = func_80108D90_hey_batter_batter;
}

/* A home run: hide the other stands, raise the prize won over the hit stand, then fly it to the batter. */
void func_80108D90_hey_batter_batter(omObjData* obj) {
    s16 i = 0;
    f32 scale;

    if (D_80109EEE_hey_batter_batter == 1) {
        D_80109D90_hey_batter_batter = D_80109EF0_hey_batter_batter;
        D_80109D92_hey_batter_batter = D_80109F2C_hey_batter_batter[D_80109EF0_hey_batter_batter];
        D_80109EEA_hey_batter_batter[0] = 1;
        for (; i < 5; i++) {
            if (i != (s16)D_80109D90_hey_batter_batter) {
                func_8001C8A8_main(D_80109F18_hey_batter_batter[i].target, 0);
            }
            func_8001C8A8_main(D_80109F2C_hey_batter_batter[i], 0);
        }
        D_80109D98_hey_batter_batter =
            SprModelRead(D_80109D40_hey_batter_batter[D_800A11D0_main[(s16)D_80109D90_hey_batter_batter]], 0xA0, 0x10);
        obj->model[1] = D_800CBB60_main[D_80109D98_hey_batter_batter].unk00;
        Hu3DModelPosSet(obj->model[1], HmfModelData[(s16)D_80109D92_hey_batter_batter].pos.x,
                        HmfModelData[(s16)D_80109D92_hey_batter_batter].pos.y,
                        HmfModelData[(s16)D_80109D92_hey_batter_batter].pos.z + 1.0f);
        Hu3DModelScaleSet(obj->model[1], 6.0f, 6.0f, 6.0f);
        func_8001C8A8_main(obj->model[2], 1);
        Hu3DModelPosSet(obj->model[2], HmfModelData[obj->model[1]].pos.x, 10.0f, HmfModelData[obj->model[1]].pos.z);
        func_800138EC_main(obj->model[3], 1, 1);
        func_8000CD00_main(obj->model[3], 5.0f, 20.0f, 10.0f);
        func_8000D018_main(obj->model[3], 100.0f);
        func_8000CFA4_main(obj->model[3], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y,
                           HmfModelData[obj->model[1]].pos.z);
        omVibrate(D_80109ED0_hey_batter_batter, 2, 2, 20);
        D_80109EEE_hey_batter_batter = 2;
    }
    if (D_80109EEE_hey_batter_batter == 2) {
        HmfModelData[obj->model[1]].pos.y = sindf(D_80109D94_hey_batter_batter * 12.0f) * 10.0f + 250.0f;
        if (D_80109D94_hey_batter_batter++ >= 30) {
            D_80109D94_hey_batter_batter = 0;
        }
    }
    if (D_80109EEE_hey_batter_batter == 3) {
        switch (D_80109D96_hey_batter_batter) {
        case 0:
            HmfModelData[obj->model[1]].pos.y = sindf(D_80109D94_hey_batter_batter * 12.0f) * 10.0f + 250.0f;
            if (HmfModelData[obj->model[1]].pos.y == 250.0f) {
                D_80109D94_hey_batter_batter = 0;
                D_80109D96_hey_batter_batter++;
                HuAudFXPlay(0x4D7);
            }
            if (D_80109D94_hey_batter_batter++ >= 30) {
                D_80109D94_hey_batter_batter = 0;
            }
            break;
        case 1:
            HmfModelData[obj->model[1]].pos.x =
                D_80109BF4_hey_batter_batter[(s16)D_80109D90_hey_batter_batter].x -
                sindf(D_80109D94_hey_batter_batter * 3.0f) *
                    (D_80109BF4_hey_batter_batter[(s16)D_80109D90_hey_batter_batter].x + 150.0f);
            HmfModelData[obj->model[1]].pos.y =
                D_80109BF4_hey_batter_batter[(s16)D_80109D90_hey_batter_batter].y -
                sindf(D_80109D94_hey_batter_batter * 3.0f) *
                    (D_80109BF4_hey_batter_batter[(s16)D_80109D90_hey_batter_batter].y - 275.0f);
            HmfModelData[obj->model[1]].pos.z =
                D_80109BF4_hey_batter_batter[(s16)D_80109D90_hey_batter_batter].z -
                sindf(D_80109D94_hey_batter_batter * 3.0f) *
                    (D_80109BF4_hey_batter_batter[(s16)D_80109D90_hey_batter_batter].z - 0.0f);
            scale = 6.0f - sindf(D_80109D94_hey_batter_batter * 3.0f) * 4.0f;
            Hu3DModelScaleSet(obj->model[1], scale, scale, scale);
            if (sindf(D_80109D94_hey_batter_batter * 3.0f) == 1.0f) {
                D_80109D96_hey_batter_batter++;
            } else {
                D_80109D94_hey_batter_batter++;
            }
            break;
        case 2:
            HmfModelData[obj->model[1]].pos.y = sindf(D_80109D94_hey_batter_batter * 12.0f) * 10.0f + 275.0f;
            if (D_80109D94_hey_batter_batter++ >= 30) {
                D_80109D94_hey_batter_batter = 0;
            }
            break;
        }
        Hu3DModelPosSet(obj->model[2], HmfModelData[obj->model[1]].pos.x, 10.0f, HmfModelData[obj->model[1]].pos.z);
        func_8000CFA4_main(obj->model[3], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y,
                           HmfModelData[obj->model[1]].pos.z);
    }
}

/* Fireworks over the stands for a home run. */
void func_8010951C_hey_batter_batter(omObjData* obj) {
    s16 i;

    obj->model[0] = func_8000B108_main(0xB0006, 0x6A9);
    func_8001C8A8_main(obj->model[0], 0);
    for (i = 1; i < 6; i++) {
        obj->model[i] = func_8000B108_main(0x5D0008, 0x6A9);
        func_8001C8A8_main(obj->model[i], 0);
    }
    obj->model[6] = func_8000B108_main(0xB0006, 0x6A9);
    func_8001C8A8_main(obj->model[6], 0);
    D_80109EE6_hey_batter_batter[0] = func_80109B24_hey_batter_batter(0xB0006);
    D_80109EE6_hey_batter_batter[1] = func_80109B24_hey_batter_batter(0x5D0008);
    D_80109EEA_hey_batter_batter[0] = 0;
    D_80109EEA_hey_batter_batter[1] = 0;
    obj->func = func_80109630_hey_batter_batter;
}

void func_80109630_hey_batter_batter(omObjData* obj) {
    s16 i = 0;
    u16 sel = D_80109EF0_hey_batter_batter;
    s16 m;

    if (D_80109EEA_hey_batter_batter[0] == 1) {
        for (; i < 5; i++) {
            if (i == (s16)sel) {
                omSetTra(obj, D_80109BF4_hey_batter_batter[i].x, D_80109BF4_hey_batter_batter[i].y,
                         D_80109BF4_hey_batter_batter[i].z);
                omSetSca(obj, 3.0f, 3.0f, 3.0f);
                func_8001C5B4_main(obj->model[0], D_80109EE6_hey_batter_batter[0]);
                func_8001C8A8_main(obj->model[0], 1);
            } else {
                Hu3DModelPosSet(obj->model[i + 1], D_80109BF4_hey_batter_batter[i].x, D_80109BF4_hey_batter_batter[i].y,
                                D_80109BF4_hey_batter_batter[i].z);
                Hu3DModelScaleSet(obj->model[i + 1], 3.0f, 3.0f, 3.0f);
                func_8001C5B4_main(obj->model[i + 1], D_80109EE6_hey_batter_batter[1]);
                func_8001C8A8_main(obj->model[i + 1], 1);
            }
        }
        D_80109EDC_hey_batter_batter = 1;
        D_80109EEA_hey_batter_batter[0] = 0;
        i = 0;
    }
    do {
        m = obj->model[i];
        if (D_800CCF58_main[HmfModelData[m].unk02].unk02 == HmfModelData[m].unk40) {
            func_8001C8A8_main(m, 0);
        }
        i++;
    } while (i < 7);
    if (D_80109EEA_hey_batter_batter[1] == 1) {
        Hu3DModelPosSet(obj->model[6], -170.0f, 100.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[6], 1.0f, 1.0f, 1.0f);
        func_8001C5B4_main(obj->model[6], D_80109EE6_hey_batter_batter[0]);
        func_8001C8A8_main(obj->model[6], 1);
        D_80109EEA_hey_batter_batter[1] = 0;
    }
}

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

/* .data (80109B60) */
s16 D_80109B60_hey_batter_batter = 0; /* batter cue: 1 intro, 2 swing */
Vec D_80109B64_hey_batter_batter[4] = {
    { -15.0f, 0.0f, 0.0f },
    { 5.0f, 90.0f, 0.0f },
    { 5.0f, -90.0f, 0.0f },
    { 10.0f, 0.0f, 0.0f },
};
Vec D_80109B94_hey_batter_batter[4] = {
    { 0.0f, 175.0f, -200.0f },
    { -800.0f, 170.0f, 0.0f },
    { 890.0f, 170.0f, -10.0f },
    { 0.0f, 225.0f, -1700.0f },
};
Vec D_80109BC4_hey_batter_batter[2] = { { 5.0f, 0.0f, 0.0f }, { 5.0f, 0.0f, 0.0f } };
Vec D_80109BDC_hey_batter_batter[2] = { { -110.0f, 200.0f, -575.0f }, { 110.0f, 200.0f, -575.0f } };
Vec D_80109BF4_hey_batter_batter[5] = {
    { 600.0f, 250.0f, -1000.0f }, { 400.0f, 250.0f, -1400.0f }, { 0.0f, 250.0f, -1600.0f },
    { -400.0f, 250.0f, -1400.0f }, { -600.0f, 250.0f, -1000.0f },
};
s16 D_80109C30_hey_batter_batter = 0;
s16 D_80109C32_hey_batter_batter = 0;
s16 D_80109C34_hey_batter_batter = 0;
s16 D_80109C36_hey_batter_batter = 0;
s16 D_80109C38_hey_batter_batter = 0;
f32 D_80109C3C_hey_batter_batter = 0.0f;
s16 D_80109C40_hey_batter_batter = 0;
s16 D_80109C42_hey_batter_batter = 0;
s16 D_80109C44_hey_batter_batter = 0;
s16 D_80109C46_hey_batter_batter = 4;
s16 D_80109C48_hey_batter_batter = 0;
s16 D_80109C4A_hey_batter_batter = 0;
Vec D_80109C4C_hey_batter_batter[5] = {
    { 600.0f, 500.0f, -2200.0f }, { -600.0f, 700.0f, -2200.0f }, { -2000.0f, 500.0f, -700.0f },
    { -2000.0f, 1000.0f, 0.0f }, { -2000.0f, 800.0f, 800.0f },
};
s16 D_80109C88_hey_batter_batter = 999;
s16 D_80109C8A_hey_batter_batter = 0;
s16 D_80109C8C_hey_batter_batter = 0;
s16 D_80109C8E_hey_batter_batter = 999;
f32 D_80109C90_hey_batter_batter = 0.0f;
s16 D_80109C94_hey_batter_batter = 0;
s16 D_80109C96_hey_batter_batter = 0;
f32 D_80109C98_hey_batter_batter = 30.0f;
f32 D_80109C9C_hey_batter_batter = 1000.0f;
f32 D_80109CA0_hey_batter_batter = 100.0f;
s16 D_80109CA4_hey_batter_batter = 0;
Vec D_80109CA8_hey_batter_batter[7] = {
    { 4.0f, 0.0f, 0.05f },        { 575.0f, 225.0f, -999.0f },  { 375.0f, 225.0f, -1399.0f },
    { 0.0f, 225.0f, -1599.0f },   { -375.0f, 225.0f, -1399.0f }, { -575.0f, 225.0f, -999.0f },
    { -3.0f, 0.0f, 2.0f },
};
s16 D_80109CFC_hey_batter_batter = 0;
f32 D_80109D00_hey_batter_batter = 1.47f;
Vec D_80109D04_hey_batter_batter[5] = {
    { 600.0f, 5.0f, -1000.0f }, { 400.0f, 5.0f, -1400.0f }, { 0.0f, 5.0f, -1600.0f },
    { -400.0f, 5.0f, -1400.0f }, { -600.0f, 5.0f, -1000.0f },
};
s32 D_80109D40_hey_batter_batter[20] = {
    0x21002D, 0x21002E, 0x21002F, 0x210030, 0x210031, 0x210032, 0x210033, 0x210034, 0x210035, 0x210036,
    0x210037, 0x210038, 0x210039, 0x21003A, 0x21003B, 0x21003C, 0x21003D, 0x21003E, 0x21003F, 0x210040,
};
u16 D_80109D90_hey_batter_batter = 0;
u16 D_80109D92_hey_batter_batter = 0;
s16 D_80109D94_hey_batter_batter = 0;
s16 D_80109D96_hey_batter_batter = 0;
s16 D_80109D98_hey_batter_batter = 0;
