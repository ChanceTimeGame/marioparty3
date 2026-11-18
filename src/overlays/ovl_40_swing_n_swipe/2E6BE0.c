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

#include "overlays/minigame.h"

// sn A: Swing 'n' Swipe (one player nets the Koopa thieves running off with the coins)

// main
s32 func_80017BB8_main(s16, s16);
extern u16 D_800D530C_main;
void func_8001C92C_main(s16 model, f32 arg1);
omObjData* func_80045ED0_main(u32 arg0);
extern u16 D_800D5558_main[4];
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8000B5F0_main(u8 arg0);
s16 func_8000B638_main(void);
void GMesMaxTimeGet(s16 mesId, s16 time);
f32 sindf(f32);
f32 cosdf(f32);
void func_8001EF6C_main(s16 arg0, s16 arg1, char* arg2);
extern s32 D_800A178C_main[][6];
extern u16 D_800A11D0_main[6];
extern s16 D_800A11DC_main[5];

// LOCAL
void func_801059BC_swing_n_swipe(void);
void func_80105C08_swing_n_swipe(omObjData* obj);
void func_80105CDC_swing_n_swipe(void);
void func_80105EE0_swing_n_swipe(omObjData* obj);
void func_80106154_swing_n_swipe(omObjData* obj);
void func_80106290_swing_n_swipe(omObjData* obj);
void func_801064A4_swing_n_swipe(omObjData* obj);
void func_801066BC_swing_n_swipe(omObjData* obj);
void func_80106704_swing_n_swipe(omObjData* obj);
void func_8010673C_swing_n_swipe(omObjData* obj);
void func_80106764_swing_n_swipe(omObjData* obj);
void func_801069CC_swing_n_swipe(omObjData* obj);
void func_80106AD0_swing_n_swipe(void);
void func_801072D0_swing_n_swipe(void);
void func_80107CEC_swing_n_swipe(omObjData* obj);
void func_80107F00_swing_n_swipe(omObjData* obj);
void func_80108158_swing_n_swipe(void);
void func_8010897C_swing_n_swipe(void);
void func_801092B4_swing_n_swipe(void);
void func_801099E8_swing_n_swipe(void);
void func_8010A0E4_swing_n_swipe(omObjData* obj);
void func_8010A3FC_swing_n_swipe(void);
void func_8010A780_swing_n_swipe(void);
void func_8010A994_swing_n_swipe(void);
void func_8010AA3C_swing_n_swipe(void);
void func_8010B01C_swing_n_swipe(omObjData* obj);
void func_8010B100_swing_n_swipe(omObjData* obj);
void func_8010B23C_swing_n_swipe(omObjData* obj);
s16 func_8010B840_swing_n_swipe(s32 file, u16 attr, u16 prio, s16 x, s16 y);
s16 func_8010B8EC_swing_n_swipe(s32 arg0);
s16 func_8010B920_swing_n_swipe(void);
s16 func_8010BA40_swing_n_swipe(s16 i);
s16 func_8010BB88_swing_n_swipe(s16 i);

// .data (defined at the end)
extern f32 D_8010BD30_swing_n_swipe;
extern f32 D_8010BD34_swing_n_swipe;
extern f32 D_8010BD38_swing_n_swipe;
extern f32 D_8010BD3C_swing_n_swipe;
extern s16 D_8010BD40_swing_n_swipe;
extern s16 D_8010BD42_swing_n_swipe;
extern s16 D_8010BD44_swing_n_swipe;
extern s16 D_8010BD46_swing_n_swipe;
extern s16 D_8010BD48_swing_n_swipe;
extern s16 D_8010BD4A_swing_n_swipe;
extern s16 D_8010BD4C_swing_n_swipe;
extern s16 D_8010BD4E_swing_n_swipe;
extern s16 D_8010BD50_swing_n_swipe;
extern s16 D_8010BD52_swing_n_swipe;
extern s16 D_8010BD54_swing_n_swipe;
extern f32 D_8010BD58_swing_n_swipe;
extern s16 D_8010BD5C_swing_n_swipe;
extern f32 D_8010BD60_swing_n_swipe;
extern s16 D_8010BD64_swing_n_swipe;
extern f32 D_8010BD68_swing_n_swipe[10][2];
extern s16 D_8010BDB8_swing_n_swipe;
extern s16 D_8010BDBA_swing_n_swipe;
extern s16 D_8010BDBC_swing_n_swipe[5];
extern s16 D_8010BDC8_swing_n_swipe[5];
extern s16 D_8010BDD4_swing_n_swipe[5];
extern s16 D_8010BDE0_swing_n_swipe[5];
extern f32 D_8010BDEC_swing_n_swipe[5][2];
extern s16 D_8010BE14_swing_n_swipe[5];
extern s16 D_8010BE20_swing_n_swipe[5];
extern f32 D_8010BE2C_swing_n_swipe;
extern f32 D_8010BE30_swing_n_swipe;
extern s16 D_8010BE34_swing_n_swipe[5];
extern s16 D_8010BE40_swing_n_swipe[5];
extern s16 D_8010BE4C_swing_n_swipe[6];
extern Vec D_8010BE58_swing_n_swipe[5];
extern s32 D_8010BE94_swing_n_swipe[20];
extern s16 D_8010BEE4_swing_n_swipe;
extern s16 D_8010BEE6_swing_n_swipe;
extern s16 D_8010BEE8_swing_n_swipe;
extern s16 D_8010BEEA_swing_n_swipe;
extern s16 D_8010BEEC_swing_n_swipe;
extern s16 D_8010BEEE_swing_n_swipe;

/* Tables copied whole onto the stack (retail keeps them in .data, after the variables) */
typedef struct SnOrder {
    u16 v[4];
} SnOrder;
typedef struct SnPeriod {
    s16 v[4];
} SnPeriod;
typedef struct SnSpeed {
    f32 v[4];
} SnSpeed;
extern SnOrder D_8010BEF0_swing_n_swipe;
extern SnPeriod D_8010BEF8_swing_n_swipe;
extern SnSpeed D_8010BF00_swing_n_swipe;

// .bss (asm)
extern f32 D_8010C090_swing_n_swipe;
extern f32 D_8010C094_swing_n_swipe;
extern Vec D_8010C098_swing_n_swipe;
extern f32 D_8010C0A4_swing_n_swipe;
extern f32 D_8010C0A8_swing_n_swipe;
extern f32 D_8010C0AC_swing_n_swipe;
extern f32 D_8010C0B0_swing_n_swipe;
extern f32 D_8010C0B4_swing_n_swipe;
extern f32 D_8010C0B8_swing_n_swipe;
extern f32 D_8010C0BC_swing_n_swipe;
extern Vec D_8010C0C0_swing_n_swipe[5];
extern s16 D_8010C13C_swing_n_swipe; /* 1: the round is lost (0: a thief netted) */
extern omObjData* D_8010C140_swing_n_swipe; /* the player */
extern s16 D_8010C144_swing_n_swipe; /* the player's index */
extern s16 D_8010C146_swing_n_swipe; /* player scripted move: 1 intro, 3 result */
extern s16 D_8010C148_swing_n_swipe; /* thieves' phase */
extern s16 D_8010C14A_swing_n_swipe[5]; /* thief motion wanted */
extern s16 D_8010C154_swing_n_swipe;
extern s16 D_8010C156_swing_n_swipe;
extern s16 D_8010C158_swing_n_swipe;
extern s16 D_8010C15A_swing_n_swipe;
extern s16 D_8010C15C_swing_n_swipe;
extern s16 D_8010C15E_swing_n_swipe; /* the thief netted */
extern s16 D_8010C160_swing_n_swipe; /* CPU: the thief it chases */
extern s16 D_8010C162_swing_n_swipe; /* CPU: retarget period */
extern s16 D_8010C164_swing_n_swipe; /* CPU: speed */
extern s16 D_8010C166_swing_n_swipe; /* net model */
extern s16 D_8010C168_swing_n_swipe; /* 1: footstep sounds */
extern s16 D_8010C170_swing_n_swipe[5][2]; /* thief model, its shadow */
extern s16 D_8010C184_swing_n_swipe[5]; /* thief motions */

void func_801059A0_swing_n_swipe(void) {
    func_801059BC_swing_n_swipe();
}

/* Find the player in group 0 (the netter). */
void func_801059BC_swing_n_swipe(void) {
    s16 cam;
    s16 i;
    SnOrder order = D_8010BEF0_swing_n_swipe;

    Hu3DAnimInit(0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x40, 0x40);
    func_8004A208_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(cam, 30.0f, 80.0f, 8000.0f);
    CZoom = 1800.0f;
    CRot.x = -15.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 174.5f;
    Center.z = 150.0f;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    D_8010C144_swing_n_swipe = (i < 4) ? order.v[i] : order.v[0];
    omAddObj(1000, 0, 0, -1, func_80105C08_swing_n_swipe);
    omAddObj(2000, 0, 0, -1, func_8010673C_swing_n_swipe);
}

void func_80105C08_swing_n_swipe(omObjData* obj) {
    func_80105CDC_swing_n_swipe();
    func_8010B840_swing_n_swipe(0x610000, 0x4000, 10, 160, 120);
    D_8010C140_swing_n_swipe = omAddObj(10, 20, 20, -1, func_80106764_swing_n_swipe);
    omAddObj(20, 20, 20, -1, func_80107CEC_swing_n_swipe);
    omAddObj(30, 20, 20, -1, func_8010A0E4_swing_n_swipe);
    omAddObj(40, 20, 20, -1, func_8010B100_swing_n_swipe);
    obj->func = func_80105EE0_swing_n_swipe;
}

// masked 2: retail schedules the stack-array address before the u8 draw's andi (as Hey, Batter, Batter!'s twin)
#ifdef NON_MATCHING
/* CPU setup: the thief it chases (a weighted draw over D_800A11DC_main) and, by difficulty, its retarget period
 * and speed. */
void func_80105CDC_swing_n_swipe(void) {
    s16 sum[5];
    SnPeriod period = D_8010BEF8_swing_n_swipe;
    SnSpeed speed = D_8010BF00_swing_n_swipe;
    s16 i;
    u8 r;

    D_8010C13C_swing_n_swipe = 1;
    GwPlayer[D_8010C144_swing_n_swipe].bonusCoin = -1;
    if (GwPlayer[D_8010C144_swing_n_swipe].stat & 1) {
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
        if (i <= 0) {
            i = 0;
        }
        if (i >= 4) {
            i = 4;
        }
        D_8010C160_swing_n_swipe = i;
        D_8010C162_swing_n_swipe = period.v[GwPlayer[D_8010C144_swing_n_swipe].cpu_difficulty];
        D_8010C164_swing_n_swipe = speed.v[GwPlayer[D_8010C144_swing_n_swipe].cpu_difficulty];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80105CDC_swing_n_swipe);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80105EE0_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80106154_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80106290_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801064A4_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801066BC_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80106704_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010673C_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80106764_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801069CC_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80106AD0_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801072D0_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80107CEC_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80107F00_swing_n_swipe);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", D_8010BF9C_swing_n_swipe);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", D_8010BFD8_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_80108158_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010897C_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801092B4_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801099E8_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010A0E4_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010A3FC_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010A780_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010A994_swing_n_swipe);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", D_8010C034_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010AA3C_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B01C_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B100_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B23C_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B840_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B8EC_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B920_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010BA40_swing_n_swipe);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010BB88_swing_n_swipe);

/* .data */
f32 D_8010BD30_swing_n_swipe = -400.0f; /* field min x */
f32 D_8010BD34_swing_n_swipe = -275.0f; /* field min z */
f32 D_8010BD38_swing_n_swipe = 400.0f;  /* field max x */
f32 D_8010BD3C_swing_n_swipe = 600.0f;  /* field max z */
s16 D_8010BD40_swing_n_swipe = 0; /* director state */
s16 D_8010BD42_swing_n_swipe = 0; /* director timer */
s16 D_8010BD44_swing_n_swipe = 0; /* intro state */
s16 D_8010BD46_swing_n_swipe = 0; /* intro timer */
s16 D_8010BD48_swing_n_swipe = 301; /* play countdown frames */
s16 D_8010BD4A_swing_n_swipe = 0; /* result state */
s16 D_8010BD4C_swing_n_swipe = 0; /* result timer */
s16 D_8010BD4E_swing_n_swipe = 0; /* player scripted-move step */
s16 D_8010BD50_swing_n_swipe = 0; /* its timer */
s16 D_8010BD52_swing_n_swipe = 0; /* its frame */
s16 D_8010BD54_swing_n_swipe = 0; /* 1: jumping */
f32 D_8010BD58_swing_n_swipe = -1.47f; /* jump speed */
s16 D_8010BD5C_swing_n_swipe = 0; /* 1: swinging the net */
f32 D_8010BD60_swing_n_swipe = 99.0f; /* CPU retarget timer */
s16 D_8010BD64_swing_n_swipe = 0; /* swing frames */
f32 D_8010BD68_swing_n_swipe[10][2] = { 0 }; /* recent stick moves (x, z) */
s16 D_8010BDB8_swing_n_swipe = 0; /* their ring index */
s16 D_8010BDBA_swing_n_swipe = 0; /* 1: swing sound played */
s16 D_8010BDBC_swing_n_swipe[5] = { 999, 999, 999, 999, 999 }; /* thief motion shown */
s16 D_8010BDC8_swing_n_swipe[5] = { 0 };
s16 D_8010BDD4_swing_n_swipe[5] = { 0 };
s16 D_8010BDE0_swing_n_swipe[5] = { 0 };
f32 D_8010BDEC_swing_n_swipe[5][2] = { 0 };
s16 D_8010BE14_swing_n_swipe[5] = { 0 };
s16 D_8010BE20_swing_n_swipe[5] = { 1, 1, 1, 1, 1 };
f32 D_8010BE2C_swing_n_swipe = 0.0f;
f32 D_8010BE30_swing_n_swipe = 0.0f;
s16 D_8010BE34_swing_n_swipe[5] = { 0 };
s16 D_8010BE40_swing_n_swipe[5] = { 1, 1, 1, 1, 1 };
s16 D_8010BE4C_swing_n_swipe[6] = { 0 };
Vec D_8010BE58_swing_n_swipe[5] = {
    { 0.0f, 0.0f, -150.0f }, { -190.0f, 0.0f, 100.0f }, { -370.0f, 0.0f, 325.0f },
    { 190.0f, 0.0f, 100.0f }, { 370.0f, 0.0f, 325.0f },
};
s32 D_8010BE94_swing_n_swipe[20] = {
    0x21002D, 0x21002E, 0x21002F, 0x210030, 0x210031, 0x210032, 0x210033, 0x210034, 0x210035, 0x210036,
    0x210037, 0x210038, 0x210039, 0x21003A, 0x21003B, 0x21003C, 0x21003D, 0x21003E, 0x21003F, 0x210040,
};
s16 D_8010BEE4_swing_n_swipe = 0;
s16 D_8010BEE6_swing_n_swipe = 0;
s16 D_8010BEE8_swing_n_swipe = 0;
s16 D_8010BEEA_swing_n_swipe = 0;
s16 D_8010BEEC_swing_n_swipe = 0;
s16 D_8010BEEE_swing_n_swipe = 0;
SnOrder D_8010BEF0_swing_n_swipe = { { 0, 1, 2, 3 } };
SnPeriod D_8010BEF8_swing_n_swipe = { { 45, 30, 15, 5 } }; /* CPU retarget period by difficulty */
SnSpeed D_8010BF00_swing_n_swipe = { { 10.0f, 11.0f, 12.0f, 13.0f } }; /* CPU speed by difficulty */
