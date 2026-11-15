#include "common.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/util.h"
#include "game/wipe.h"

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106744_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106928_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106C24_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106C6C_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106CBC_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106CE4_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106FA8_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_801070D8_hey_batter_batter);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80109A78_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80109B24_hey_batter_batter);
