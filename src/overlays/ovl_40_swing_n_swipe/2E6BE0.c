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
extern s8 D_800CBB6E_main[]; /* stick x by pad */
extern s8 D_800D20A1_main[]; /* stick y by pad */
/* D_800CCF58_main records (common_structs.h D_800CCF58_main_Struct): motion length at 0x02 */
typedef struct SnMotInfo {
    /* 0x00 */ char unk00[2];
    /* 0x02 */ s16 unk02;
    /* 0x04 */ char unk04[0x14];
} SnMotInfo; /* size 0x18 */
extern SnMotInfo* D_800CCF58_main;
void Hu3DAnimInit(s32);
s16 func_8000CED8_main(s32, s32);
s16 SprModelRead(s32 arg0, s32 arg1, s32 arg2); /* retail sign-extends the result here */
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_8000CD00_main(s16, f32, f32, f32);
void func_8000CFA4_main(s16, f32, f32, f32);
void func_8000D018_main(s16, f32);
/* An entry of D_800CBB60_main (0x24 bytes; minigame BD210.c MgSprModel): its model at 0x00 */
typedef struct SnSprModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x1E];
    /* 0x20 */ u8* unk20;
} SnSprModel;
extern SnSprModel* D_800CBB60_main;
void func_8000BC48_main(u16 arg0, u16 arg1);
s16 func_8000B13C_main(s32 arg0);
void func_8001EED8_main(s16 arg0, s16 arg1, s16 arg2); /* hmfman.c defines (s16, u8, s8) */
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
extern Vec D_8010C0C0_swing_n_swipe[5]; /* fleeing thieves' start */
extern Vec D_8010C100_swing_n_swipe[5]; /* lining-up thieves' start */
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
extern s16 D_8010C190_swing_n_swipe[5][4]; /* coin bag, its coin count, its shadow */
extern s16 D_8010C1B8_swing_n_swipe[4]; /* the prize's dust particles, its shadow */
extern s16 D_8010C1C0_swing_n_swipe[5]; /* puffs over the thieves */
extern s16 D_8010C1CC_swing_n_swipe[2]; /* result mark over the player, the net's swish */
extern s16 D_8010C1D0_swing_n_swipe[3]; /* their motions */

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

/* The minigame's director: wipe in, the intro, the play, the result and the exit. */
void func_80105EE0_swing_n_swipe(omObjData* obj) {
    switch (D_8010BD40_swing_n_swipe) {
    case 0:
        WipeCreateIn(0xFF, 16);
        D_8010BD40_swing_n_swipe++;
        break;
    case 1:
        obj->func = func_80106154_swing_n_swipe;
        D_8010BD40_swing_n_swipe++;
        break;
    case 2:
        if (++D_8010BD42_swing_n_swipe == 1) {
            GMesCreate(8);
        } else if (GMesStatGet() == 0) {
            D_8010BD42_swing_n_swipe = 0;
            D_8010BD40_swing_n_swipe++;
        }
        break;
    case 3:
        obj->func = func_80106290_swing_n_swipe;
        D_8010BD40_swing_n_swipe++;
        break;
    case 4:
        if (++D_8010BD42_swing_n_swipe == 1) {
            GMesCreate(0x13);
            HuAudSeqFadeOut(120);
        } else if (GMesStatGet() == 0) {
            D_8010BD42_swing_n_swipe = 0;
            D_8010BD40_swing_n_swipe++;
        }
        break;
    case 5:
        obj->func = func_801064A4_swing_n_swipe;
        D_8010BD40_swing_n_swipe++;
        break;
    case 6:
        if (++D_8010BD42_swing_n_swipe == 1) {
            switch (D_8010C13C_swing_n_swipe) {
            case 0:
                HuAudSeqPlay(0x68);
                GMesMaxTimeGet(GMesCreate(0x24), 120);
                GwPlayer[D_8010C144_swing_n_swipe].bonusCoin = D_800A11D0_main[D_8010C15E_swing_n_swipe];
                break;
            case 1:
                HuAudSeqPlay(0x6B);
                GMesMaxTimeGet(GMesCreate(0x1D), 120);
                GwPlayer[D_8010C144_swing_n_swipe].bonusCoin = -1;
                break;
            }
        } else if (D_8010BD42_swing_n_swipe >= 135) {
            D_8010BD42_swing_n_swipe = 0;
            D_8010BD40_swing_n_swipe++;
        }
        break;
    case 7:
        obj->func = func_801066BC_swing_n_swipe;
        break;
    }
    func_801092B4_swing_n_swipe();
    func_801099E8_swing_n_swipe();
    func_8010A994_swing_n_swipe();
    func_8010AA3C_swing_n_swipe();
}

/* Intro: the player walks on, the thieves come out. */
void func_80106154_swing_n_swipe(omObjData* obj) {
    switch (D_8010BD44_swing_n_swipe) {
    case 0:
        if (WipeStatGet() == 1) {
            return;
        }
        HuAudSeqPlay(0x44);
        D_8010BD44_swing_n_swipe++;
        break;
    case 1:
        D_8010C154_swing_n_swipe = 1;
        if (D_8010BD46_swing_n_swipe++ >= 30) {
            D_8010BD46_swing_n_swipe = 0;
            D_8010BD44_swing_n_swipe++;
        }
        break;
    case 2:
        D_8010C148_swing_n_swipe = 1;
        D_8010BD44_swing_n_swipe++;
        break;
    case 3:
        if (D_8010BD46_swing_n_swipe++ >= 60) {
            D_8010BD46_swing_n_swipe = 0;
            D_8010BD44_swing_n_swipe++;
        }
        break;
    case 4:
        D_8010C146_swing_n_swipe = 1;
        D_8010BD44_swing_n_swipe++;
        break;
    case 5:
        if (D_8010C146_swing_n_swipe == 0) {
            obj->func = func_80105EE0_swing_n_swipe;
        }
        break;
    }
    func_80106AD0_swing_n_swipe();
    func_80108158_swing_n_swipe();
    func_8010A3FC_swing_n_swipe();
}

/* Play: ten seconds to net a thief. */
void func_80106290_swing_n_swipe(omObjData* obj) {
    s16 i;

    if (--D_8010BD48_swing_n_swipe == 300) {
        D_8010C148_swing_n_swipe = 2;
        GMesCreate(0x1A, 10, 160, 56);
    } else if (D_8010BD48_swing_n_swipe >= 0) {
        func_8003F578_main((D_8010BD48_swing_n_swipe + 29) / 30);
        func_801072D0_swing_n_swipe();
        func_8010897C_swing_n_swipe();
    } else {
        D_8010C13C_swing_n_swipe = 1;
        func_8003F5C0_main();
        D_8010C156_swing_n_swipe = 1;
        D_8010C15A_swing_n_swipe = 1;
        D_8010C146_swing_n_swipe = 0;
        D_8010C148_swing_n_swipe = 0;
        HmfModelData[D_8010C140_swing_n_swipe->model[0]].unk06 = 0xFF;
        func_800E5690_minigame(D_8010C140_swing_n_swipe, 0);
        for (i = 0; i < 5; i++) {
            D_8010C14A_swing_n_swipe[i] = 0;
        }
        obj->func = func_80105EE0_swing_n_swipe;
    }
    if (D_8010C13C_swing_n_swipe == 0) {
        D_8010C13C_swing_n_swipe = 0;
        func_8003F5C0_main();
        D_8010C156_swing_n_swipe = 1;
        D_8010C146_swing_n_swipe = 0;
        D_8010C148_swing_n_swipe = 4;
        for (i = 0; i < 5; i++) {
            D_8010C14A_swing_n_swipe[i] = 0;
        }
        obj->func = func_80105EE0_swing_n_swipe;
    }
    func_801092B4_swing_n_swipe();
    func_801099E8_swing_n_swipe();
    func_8010A780_swing_n_swipe();
}

/* Result: the win or loss pose. */
void func_801064A4_swing_n_swipe(omObjData* obj) {
    s16 i;

    switch (D_8010BD4A_swing_n_swipe) {
    case 0:
        if (D_8010C13C_swing_n_swipe == 0) {
            D_8010C154_swing_n_swipe = 4;
        } else if (D_8010C13C_swing_n_swipe == 1) {
            D_8010C146_swing_n_swipe = 3;
            D_8010C148_swing_n_swipe = 3;
        }
        D_8010BD4A_swing_n_swipe++;
        break;
    case 1:
        if (D_8010BD4C_swing_n_swipe++ >= 90) {
            D_8010BD4A_swing_n_swipe++;
        }
        break;
    case 2:
        if (D_8010C13C_swing_n_swipe == 0) {
            func_800E5690_minigame(D_8010C140_swing_n_swipe, 6);
            func_80045ED0_main(D_800A178C_main[GwPlayer[D_8010C144_swing_n_swipe].chr][0] | 0x35);
        } else if (D_8010C13C_swing_n_swipe == 1) {
            HuAudFXPlay(0x4F6);
            func_800E5690_minigame(D_8010C140_swing_n_swipe, 7);
            func_80045ED0_main(D_800A178C_main[GwPlayer[D_8010C144_swing_n_swipe].chr][0] | 0x38);
            for (i = 0; i < 5; i++) {
                D_8010C14A_swing_n_swipe[i] = 4;
            }
        }
        obj->func = func_80105EE0_swing_n_swipe;
        break;
    }
    func_80106AD0_swing_n_swipe();
    func_801092B4_swing_n_swipe();
    func_801099E8_swing_n_swipe();
    func_8010AA3C_swing_n_swipe();
}

void func_801066BC_swing_n_swipe(omObjData* obj) {
    WipeCreateOut(0, 16);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80106704_swing_n_swipe;
}

void func_80106704_swing_n_swipe(omObjData* obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        omOvlReturnEx(1);
    }
}

void func_8010673C_swing_n_swipe(omObjData* obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_801066BC_swing_n_swipe;
    }
}

/* The player: motions, start position, shadow and the net on its hand. */
void func_80106764_swing_n_swipe(omObjData* obj) {
    s32 chr;
    s32 dir;
    s32 file;

    func_800E18D8_minigame();
    chr = GwPlayer[D_8010C144_swing_n_swipe].chr;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][1];
    func_800E1BA8_minigame(obj, dir, file, D_8010C144_swing_n_swipe, 0x2B9, 0x2B9);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x18), 1, 0);
    func_800E5A00_minigame(obj, 3, func_80017BB8_main(chr, 4), 0, 0);
    func_800E5A00_minigame(obj, 5, func_80017BB8_main(chr, 0x91), 0, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 0x35), 0, 0);
    func_800E5A00_minigame(obj, 7, func_80017BB8_main(chr, 0x38), 0, 0);
    func_800E5690_minigame(obj, 4);
    omSetTra(obj, 0.0f, 0.0f, 1500.0f);
    obj->model[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], 1.5f, 1.0f, 1.5f);
    D_8010C166_swing_n_swipe = func_8000B108_main(0x610002, 0x2B9);
    func_8001C258_main(D_8010C166_swing_n_swipe, 0x4000, 0x4000);
    func_8001EF6C_main(D_8010C166_swing_n_swipe, obj->model[0], "item_hook");
    obj->func = func_801069CC_swing_n_swipe;
}

/* Per frame: the shadow shrinks as the player rises; footsteps. */
void func_801069CC_swing_n_swipe(omObjData* obj) {
    f32 scale = 1.5f - obj->trans.y * 0.003f;

    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], scale, 1.0f, scale);
    if (D_8010C168_swing_n_swipe == 1 && HmfModelData[obj->model[0]].unk40 == 0.0f) {
        CharFXPlay(0x1F, GwPlayer[D_8010C144_swing_n_swipe].chr);
    }
    func_800E4E30_minigame(obj);
}

/* The player's scripted moves: the walk-on (D_8010C146_swing_n_swipe 1) and, after a loss, the hop back to the
 * centre (3). */
void func_80106AD0_swing_n_swipe(void) {
    omObjData* obj = D_8010C140_swing_n_swipe;

    if (D_8010C146_swing_n_swipe == 0) {
        D_8010BD52_swing_n_swipe = 0;
        D_8010BD50_swing_n_swipe = 0;
        D_8010BD4E_swing_n_swipe = 0;
    }
    if (D_8010C146_swing_n_swipe == 1) {
        switch (D_8010BD4E_swing_n_swipe) {
        case 0:
            obj->trans.z = 1500.0f;
            obj->rot.y = 180.0f;
            func_8001EED8_main(obj->model[0], obj->motion[4], 0);
            func_800E5690_minigame(obj, 1);
            D_8010BD4E_swing_n_swipe++;
            break;
        case 1:
            D_8010C168_swing_n_swipe = 1;
            if ((obj->trans.z -= 13.5f) <= 550.0f) {
                obj->trans.z = 550.0f;
                D_8010BD4E_swing_n_swipe++;
            }
            break;
        case 2:
            if ((obj->rot.y -= 13.5f) <= 0.0f) {
                obj->rot.y = 0.0f;
                D_8010BD4E_swing_n_swipe++;
            }
            break;
        case 3:
            D_8010C168_swing_n_swipe = 0;
            func_8001EED8_main(obj->model[0], obj->motion[4], 0);
            func_800E5690_minigame(obj, 0);
            D_8010BD4E_swing_n_swipe++;
            break;
        case 4:
            if (D_8010BD50_swing_n_swipe++ >= 10) {
                D_8010BD50_swing_n_swipe = 0;
                D_8010BD4E_swing_n_swipe++;
            }
            break;
        case 5:
        case 8:
            HuAudFXPlay(0x4F8);
            func_8001EED8_main(obj->model[0], obj->motion[5], 0);
            func_800E5690_minigame(obj, 5);
            D_8010BD4E_swing_n_swipe++;
            break;
        case 6:
        case 9:
            if (D_8010BD50_swing_n_swipe++ >= 10) {
                D_8010BD50_swing_n_swipe = 0;
                D_8010BD4E_swing_n_swipe++;
            }
            break;
        case 7:
        case 10:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 == HmfModelData[obj->model[0]].unk40) {
                D_8010BD4E_swing_n_swipe++;
            }
            break;
        case 11:
            func_8001EED8_main(obj->model[0], obj->motion[4], 0);
            func_800E5690_minigame(obj, 0);
            D_8010BD50_swing_n_swipe = 0;
            D_8010BD4E_swing_n_swipe = 0;
            D_8010C146_swing_n_swipe = 0;
            break;
        }
    }
    if (D_8010C146_swing_n_swipe == 3) {
        switch (D_8010BD4E_swing_n_swipe) {
        case 0:
            D_8010C098_swing_n_swipe.x = obj->trans.x;
            D_8010C098_swing_n_swipe.z = obj->trans.z;
            D_8010BD52_swing_n_swipe = 1;
            D_8010BD58_swing_n_swipe = -1.47f;
            HmfModelData[obj->model[0]].unk06 = 0xFF;
            func_800E5690_minigame(obj, 1);
            D_8010BD4E_swing_n_swipe++;
            break;
        case 1:
            if (D_8010BD54_swing_n_swipe == 0) {
                D_8010C168_swing_n_swipe = 1;
                if (func_8010B920_swing_n_swipe() == 1) {
                    D_8010BD54_swing_n_swipe = 1;
                    func_800E5690_minigame(obj, 3);
                    CharFXPlay(0x3A, GwPlayer[D_8010C144_swing_n_swipe].chr);
                    D_8010C168_swing_n_swipe = 0;
                    return;
                }
            }
            if (D_8010BD54_swing_n_swipe == 1) {
                obj->trans.y += D_8010BD58_swing_n_swipe * D_8010BD58_swing_n_swipe
                                * (D_8010BD58_swing_n_swipe >= 0.0f ? -17.0f : 17.0f);
                if (D_8010BD58_swing_n_swipe >= 1.7f) {
                    D_8010BD58_swing_n_swipe = 1.7f;
                } else {
                    D_8010BD58_swing_n_swipe += 0.11f;
                }
                if (D_8010BD58_swing_n_swipe >= 0.0f && obj->trans.y < 0.0f) {
                    obj->trans.y = 0.0f;
                    D_8010BD58_swing_n_swipe = -1.47f;
                    D_8010C168_swing_n_swipe = 1;
                    D_8010BD54_swing_n_swipe = 0;
                    CharFXPlay(0x31, GwPlayer[D_8010C144_swing_n_swipe].chr);
                    func_800E5690_minigame(obj, 1);
                }
            }
            D_8010C090_swing_n_swipe = obj->trans.x;
            D_8010C094_swing_n_swipe = obj->trans.z;
            obj->trans.x = D_8010C098_swing_n_swipe.x - sindf(D_8010BD52_swing_n_swipe * 1.5f) * D_8010C098_swing_n_swipe.x;
            obj->trans.z = D_8010C098_swing_n_swipe.z
                           - sindf(D_8010BD52_swing_n_swipe * 1.5f) * (D_8010C098_swing_n_swipe.z - 400.0f);
            obj->rot.y = -atan2df(D_8010C094_swing_n_swipe - obj->trans.z, D_8010C090_swing_n_swipe - obj->trans.x)
                         + 270.0f;
            if (sindf(D_8010BD52_swing_n_swipe++ * 1.5f) == 1.0f
                || (obj->trans.x == 0.0f && obj->trans.z == 350.0f)) {
                D_8010BD4E_swing_n_swipe++;
            }
            break;
        case 2:
            if (obj->rot.y >= 360.0f) {
                obj->rot.y -= 360.0f;
            }
            if (obj->rot.y < 0.0f) {
                obj->rot.y += 360.0f;
            }
            if (obj->rot.y >= 180.0f) {
                if ((obj->rot.y += 15.0f) >= 360.0f) {
                    obj->rot.y = 0.0f;
                    D_8010BD4E_swing_n_swipe++;
                }
            } else if (obj->rot.y > 0.0f) {
                if ((obj->rot.y -= 15.0f) <= 0.0f) {
                    obj->rot.y = 0.0f;
                    D_8010BD4E_swing_n_swipe++;
                }
            } else if (obj->rot.y == 0.0f) {
                D_8010BD4E_swing_n_swipe++;
            }
            break;
        case 3:
            D_8010C168_swing_n_swipe = 0;
            func_800E5690_minigame(obj, 0);
            D_8010BD4E_swing_n_swipe++;
            break;
        }
    }
}

// masked 8: retail loads HmfModelData before scaling the model index (both thief-distance tests); register choice
#ifdef NON_MATCHING
/* Play: the player's move (the stick averaged over ten frames, or the CPU chasing its thief) and the net swing; a
 * swing within 125 of a thief nets it. */
void func_801072D0_swing_n_swipe(void) {
    omObjData* obj = D_8010C140_swing_n_swipe;
    f32 sz = 0.0f;
    f32 sx = 0.0f;
    s16 i = 0;
    s16 pad;
    HmfModel* m;

    if (!(GwPlayer[D_8010C144_swing_n_swipe].stat & 1)) {
        pad = GwPlayer[D_8010C144_swing_n_swipe].pad;
        if ((D_800D5558_main[pad] & 0x8000) && D_8010BD5C_swing_n_swipe == 0) {
            D_8010BD5C_swing_n_swipe = 1;
            for (i = 0; i < 10; i++) {
                D_8010BD68_swing_n_swipe[i][0] = D_8010BD68_swing_n_swipe[i][1] = 0.0f;
            }
            func_8001EED8_main(obj->model[0], obj->motion[5], 0);
            func_800E5690_minigame(obj, 5);
        }
        if (D_8010BD5C_swing_n_swipe == 0) {
            D_8010BD68_swing_n_swipe[D_8010BDB8_swing_n_swipe][0] = D_800CBB6E_main[pad];
            D_8010BD68_swing_n_swipe[D_8010BDB8_swing_n_swipe++][1] = D_800D20A1_main[pad];
            for (i = 0; i < 10; i++) {
                sx += D_8010BD68_swing_n_swipe[i][0];
                sz += D_8010BD68_swing_n_swipe[i][1];
            }
            sx /= 100.0f;
            sz /= 100.0f;
        }
    } else {
        if (D_8010BD5C_swing_n_swipe == 0) {
            D_8010C0A4_swing_n_swipe = cosdf(obj->rot.y - 90.0f) * 100.0f + obj->trans.x;
            D_8010C0A8_swing_n_swipe = obj->trans.z - sindf(obj->rot.y - 90.0f) * 100.0f;
            m = &HmfModelData[D_8010C170_swing_n_swipe[D_8010C160_swing_n_swipe][0]];
            D_8010C0AC_swing_n_swipe = D_8010C0A4_swing_n_swipe - m->pos.x;
            D_8010C0B0_swing_n_swipe = D_8010C0A8_swing_n_swipe - m->pos.z;
            if (HuSqrtf(D_8010C0AC_swing_n_swipe * D_8010C0AC_swing_n_swipe
                        + D_8010C0B0_swing_n_swipe * D_8010C0B0_swing_n_swipe)
                <= 100.0f) {
                D_8010BD5C_swing_n_swipe = 1;
                for (i = 0; i < 10; i++) {
                    D_8010BD68_swing_n_swipe[i][0] = D_8010BD68_swing_n_swipe[i][1] = 0.0f;
                }
                func_8001EED8_main(obj->model[0], obj->motion[5], 0);
                func_800E5690_minigame(obj, 5);
            }
        }
        if (D_8010C162_swing_n_swipe <= D_8010BD60_swing_n_swipe++ && D_8010BD5C_swing_n_swipe == 0) {
            D_8010BD60_swing_n_swipe = 0.0f;
            D_8010C0B4_swing_n_swipe =
                obj->trans.x - HmfModelData[D_8010C170_swing_n_swipe[D_8010C160_swing_n_swipe][0]].pos.x;
            D_8010C0B8_swing_n_swipe =
                obj->trans.z - HmfModelData[D_8010C170_swing_n_swipe[D_8010C160_swing_n_swipe][0]].pos.z;
            D_8010C0BC_swing_n_swipe = -atan2df(D_8010C0B4_swing_n_swipe, -D_8010C0B8_swing_n_swipe) + 270.0f;
        }
        i = 0;
        D_8010BD68_swing_n_swipe[D_8010BDB8_swing_n_swipe][0] = (D_8010C164_swing_n_swipe / 2) * cosdf(D_8010C0BC_swing_n_swipe);
        D_8010BD68_swing_n_swipe[D_8010BDB8_swing_n_swipe++][1] = (D_8010C164_swing_n_swipe / 2) * sindf(D_8010C0BC_swing_n_swipe);
        for (i = 0; i < 10; i++) {
            sx += D_8010BD68_swing_n_swipe[i][0];
            sz += D_8010BD68_swing_n_swipe[i][1];
        }
        sx /= 10.0f;
        sz /= 10.0f;
    }
    if (D_8010BDB8_swing_n_swipe >= 10) {
        D_8010BDB8_swing_n_swipe = 0;
    }
    if (D_8010BD5C_swing_n_swipe == 1) {
        if (D_8010BDBA_swing_n_swipe == 0) {
            HuAudFXPlay(0x4F8);
            D_8010BDBA_swing_n_swipe = 1;
        }
        if (D_8010BD64_swing_n_swipe >= 7 && HmfModelData[obj->model[0]].unk40 == 16.0f) {
            D_8010BD64_swing_n_swipe = 0;
            D_8010C0A4_swing_n_swipe = cosdf(obj->rot.y - 90.0f) * 100.0f + obj->trans.x;
            D_8010C0A8_swing_n_swipe = obj->trans.z - sindf(obj->rot.y - 90.0f) * 100.0f;
            for (i = 0; i < 5; i++) {
                m = &HmfModelData[D_8010C170_swing_n_swipe[i][0]];
                D_8010C0AC_swing_n_swipe = D_8010C0A4_swing_n_swipe - m->pos.x;
                D_8010C0B0_swing_n_swipe = D_8010C0A8_swing_n_swipe - m->pos.z;
                if (HuSqrtf(D_8010C0AC_swing_n_swipe * D_8010C0AC_swing_n_swipe
                            + D_8010C0B0_swing_n_swipe * D_8010C0B0_swing_n_swipe)
                    <= 125.0f) {
                    D_8010C15E_swing_n_swipe = i;
                    D_8010C148_swing_n_swipe = 5;
                    D_8010C154_swing_n_swipe = 3;
                    D_8010C15C_swing_n_swipe = 1;
                    D_8010C13C_swing_n_swipe = 0;
                    omVibrate(D_8010C144_swing_n_swipe, 2, 2, 20);
                    HuAudFXPlay(0x4F4);
                    HuAudFXPlay(0x4F5);
                    break;
                }
            }
        } else {
            D_8010BD64_swing_n_swipe++;
        }
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 == HmfModelData[obj->model[0]].unk40
            && D_8010BD64_swing_n_swipe >= 7) {
            D_8010BD5C_swing_n_swipe = 0;
            D_8010BD64_swing_n_swipe = 0;
            D_8010BDBA_swing_n_swipe = 0;
        }
    } else if (D_8010BD5C_swing_n_swipe == 0) {
        obj->trans.x = sx + obj->trans.x;
        obj->trans.z = obj->trans.z - sz;
        if (func_8010B920_swing_n_swipe() == 1) {
            obj->trans.x = obj->trans.x - sx;
            obj->trans.z = sz + obj->trans.z;
        }
        if (obj->trans.z > D_8010BD3C_swing_n_swipe) {
            obj->trans.z = D_8010BD3C_swing_n_swipe;
        } else if (obj->trans.z < D_8010BD34_swing_n_swipe) {
            obj->trans.z = D_8010BD34_swing_n_swipe;
        }
        if (obj->trans.x > D_8010BD38_swing_n_swipe) {
            obj->trans.x = D_8010BD38_swing_n_swipe;
        } else if (obj->trans.x < D_8010BD30_swing_n_swipe) {
            obj->trans.x = D_8010BD30_swing_n_swipe;
        }
    }
    if ((sx != 0.0f) | (sz != 0.0f)) {
        if (D_8010BD5C_swing_n_swipe == 0) {
            if (HmfModelData[obj->model[0]].unk40 == 0.0f) {
                CharFXPlay(0x1F, GwPlayer[D_8010C144_swing_n_swipe].chr);
            }
            func_8001EED8_main(obj->model[0], obj->motion[4], 0);
            func_800E5690_minigame(obj, 1);
            obj->rot.y = -atan2df(-sx, -sz);
        }
    } else if (D_8010BD5C_swing_n_swipe == 0) {
        func_8001EED8_main(obj->model[0], obj->motion[4], 0);
        func_800E5690_minigame(obj, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_801072D0_swing_n_swipe);
#endif

/* The five thieves and their shadows. */
void func_80107CEC_swing_n_swipe(omObjData* obj) {
    s16 i;

    D_8010C170_swing_n_swipe[0][0] = func_8000B108_main(0xA0109, 0x2B9);
    D_8010C170_swing_n_swipe[0][1] = func_8000B108_main(9, 0x2B9);
    for (i = 1; i < 5; i++) {
        D_8010C170_swing_n_swipe[i][0] = Hu3DModelLink(D_8010C170_swing_n_swipe[0][0]);
        D_8010C170_swing_n_swipe[i][1] = Hu3DModelLink(D_8010C170_swing_n_swipe[0][1]);
    }
    for (i = 0; i < 5; i++) {
        func_8001C8A8_main(D_8010C170_swing_n_swipe[i][0], 0);
        Hu3DModelScaleSet(D_8010C170_swing_n_swipe[i][1], 1.5f, 1.0f, 1.5f);
        func_8001C8A8_main(D_8010C170_swing_n_swipe[i][1], 0);
    }
    D_8010C184_swing_n_swipe[0] = func_8010B8EC_swing_n_swipe(0xA0102);
    D_8010C184_swing_n_swipe[1] = func_8010B8EC_swing_n_swipe(0xA0103);
    D_8010C184_swing_n_swipe[2] = func_8010B8EC_swing_n_swipe(0xA010A);
    D_8010C184_swing_n_swipe[3] = func_8010B8EC_swing_n_swipe(0xA010B);
    D_8010C184_swing_n_swipe[4] = func_8010B8EC_swing_n_swipe(0xA010C);
    for (i = 0; i < 5; i++) {
        func_8001C624_main(D_8010C170_swing_n_swipe[i][0], HmfModelData[D_8010C184_swing_n_swipe[0]].unk02, 0, 30, 2);
    }
    D_8010C148_swing_n_swipe = 0;
    obj->func = func_80107F00_swing_n_swipe;
}

/* Per frame: each thief's motion follows D_8010C14A_swing_n_swipe; shadows follow and shrink with height. */
void func_80107F00_swing_n_swipe(omObjData* obj) {
    s16 i;
    s16* cur;
    s16 mot;
    f32 scale;

    for (i = 0; i < 5; i++) {
        cur = &D_8010BDBC_swing_n_swipe[i];
        mot = D_8010C14A_swing_n_swipe[i];
        if (*cur != mot) {
            *cur = mot;
            switch (mot) {
            case 0:
            case 1:
            case 3:
            case 4:
                func_8001C624_main(D_8010C170_swing_n_swipe[i][0],
                                   HmfModelData[D_8010C184_swing_n_swipe[D_8010BDBC_swing_n_swipe[i]]].unk02, 0, 30, 2);
                break;
            case 2:
                func_8001C5B4_main(D_8010C170_swing_n_swipe[i][0], D_8010C184_swing_n_swipe[D_8010BDBC_swing_n_swipe[i]]);
                break;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        scale = 1.5f - HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.y * 0.00375f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelPosSet(D_8010C170_swing_n_swipe[i][1], HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.x, 0.0f,
                        HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.z);
        Hu3DModelScaleSet(D_8010C170_swing_n_swipe[i][1], scale, 1.0f, scale);
    }
}

/* Intro: the thieves run in from their doors to their places and turn to face the player. */
void func_80108158_swing_n_swipe(void) {
    Vec from[5] = {
        { -575.0f, 0.0f, 600.0f }, { -625.0f, 0.0f, 800.0f }, { -675.0f, 0.0f, 1000.0f },
        { 625.0f, 0.0f, 800.0f }, { 675.0f, 0.0f, 1000.0f },
    };
    Vec to[5] = {
        { 0.0f, 0.0f, -250.0f }, { -190.0f, 0.0f, -50.0f }, { -370.0f, 0.0f, 200.0f },
        { 190.0f, 0.0f, -50.0f }, { 370.0f, 0.0f, 200.0f },
    };
    s16 i = 0;
    u16 mdl;
    u16 shadow;
    u16 bag;
    f32 ox;
    f32 oz;

    if (D_8010C148_swing_n_swipe == 1) {
        for (i = 0; i < 5; i++) {
            mdl = D_8010C170_swing_n_swipe[i][0];
            shadow = D_8010C170_swing_n_swipe[i][1];
            bag = D_8010C190_swing_n_swipe[i][0];
            switch (D_8010BDC8_swing_n_swipe[i]) {
            case 0:
                Hu3DModelPosSet(mdl, from[i].x, 0.0f, from[i].z);
                Hu3DModelPosSet(shadow, HmfModelData[(s16)mdl].pos.x, 0.0f, HmfModelData[(s16)mdl].pos.z);
                D_8010C14A_swing_n_swipe[i] = 1;
                func_8001C8A8_main(mdl, 1);
                func_8001C8A8_main(shadow, 1);
                D_8010BDC8_swing_n_swipe[i]++;
                break;
            case 1:
                ox = HmfModelData[(s16)mdl].pos.x;
                oz = HmfModelData[(s16)mdl].pos.z;
                if (i < 3) {
                    HmfModelData[(s16)mdl].pos.x = ox + 2.5f;
                } else {
                    HmfModelData[(s16)mdl].pos.x -= 2.5f;
                }
                HmfModelData[(s16)mdl].pos.z -= 10.0f;
                HmfModelData[(s16)mdl].rot.y =
                    -atan2df(oz - HmfModelData[(s16)mdl].pos.z, ox - HmfModelData[(s16)mdl].pos.x) + 270.0f;
                if (to[i].z >= HmfModelData[(s16)mdl].pos.z) {
                    HmfModelData[(s16)mdl].pos.z = to[i].z;
                    D_8010BDC8_swing_n_swipe[i]++;
                }
                break;
            case 2:
                if (i < 3) {
                    if ((HmfModelData[(s16)mdl].rot.y -= 6.75f) <= 90.0f) {
                        HmfModelData[(s16)mdl].rot.y = 90.0f;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                } else {
                    if ((HmfModelData[(s16)mdl].rot.y += 6.75f) >= 270.0f) {
                        HmfModelData[(s16)mdl].rot.y = 270.0f;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                }
                break;
            case 3:
                ox = HmfModelData[(s16)mdl].pos.x;
                oz = HmfModelData[(s16)mdl].pos.z;
                if (i < 3) {
                    HmfModelData[(s16)mdl].pos.x = ox + 10.0f;
                } else {
                    HmfModelData[(s16)mdl].pos.x -= 10.0f;
                }
                HmfModelData[(s16)mdl].rot.y =
                    -atan2df(oz - HmfModelData[(s16)mdl].pos.z, ox - HmfModelData[(s16)mdl].pos.x) + 270.0f;
                if (i < 3) {
                    if (to[i].x <= HmfModelData[(s16)mdl].pos.x) {
                        HmfModelData[(s16)mdl].pos.x = to[i].x;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                } else {
                    if (to[i].x >= HmfModelData[(s16)mdl].pos.x) {
                        HmfModelData[(s16)mdl].pos.x = to[i].x;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                }
                break;
            case 4:
                if (i < 3) {
                    if ((HmfModelData[(s16)mdl].rot.y -= 6.75f) <= 0.0f) {
                        HmfModelData[(s16)mdl].rot.y = 0.0f;
                        D_8010C14A_swing_n_swipe[i] = 2;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                } else {
                    if ((HmfModelData[(s16)mdl].rot.y += 6.75f) >= 360.0f) {
                        HmfModelData[(s16)mdl].rot.y = 0.0f;
                        D_8010C14A_swing_n_swipe[i] = 2;
                        D_8010BDC8_swing_n_swipe[i]++;
                    }
                }
                break;
            case 5:
                HmfModelData[(s16)bag].pos.y = (1.0f - cosdf(D_8010BDD4_swing_n_swipe[i] * 4.5f)) * 140.0f;
                if (D_8010BDD4_swing_n_swipe[i] > 10.0f) {
                    HmfModelData[(s16)bag].pos.z =
                        (to[i].z + 100.0f) - sindf((D_8010BDD4_swing_n_swipe[i] - 10.0f) * 9.0f) * 50.0f;
                }
                if (sindf(D_8010BDD4_swing_n_swipe[i]++ * 4.5f) == 1.0f) {
                    D_8010BDD4_swing_n_swipe[i] = 0;
                    D_8010BDC8_swing_n_swipe[i]++;
                }
                break;
            case 6:
                if (i == 0) {
                    D_8010C148_swing_n_swipe = 0;
                    D_8010C154_swing_n_swipe = 2;
                }
                break;
            }
        }
    }
}

// masked 46: register allocation only (retail keeps 360.0f in $f30 and 270.0f in $s7; here they swap)
#ifdef NON_MATCHING
/* Play: the thieves wander, turning at random and bouncing off each other and the field's edges. */
void func_8010897C_swing_n_swipe(void) {
    s16 st[5][5]; /* per thief: [0] heading, [1] turn direction; never initialised (retail reads stale stack) */
    s16 i = 0;
    u16 mdl;
    f32 ox;
    f32 oz;
    f32 dx;
    f32 dz;
    f32 v;

    if (D_8010C148_swing_n_swipe == 2) {
        for (i = 0; i < 5; i++) {
            mdl = D_8010C170_swing_n_swipe[i][0];
            switch (D_8010BDE0_swing_n_swipe[i]) {
            case 0:
                D_8010C14A_swing_n_swipe[i] = 3;
                st[i][0] = (s16)((u8)(rand8() % 180) + 90.0f) % 360;
                st[i][1] = rand8() & 1;
                D_8010BDE0_swing_n_swipe[i]++;
                break;
            case 1:
                if (st[i][1] == 0) {
                    HmfModelData[(s16)mdl].rot.y += 10.0f;
                    if (!(u8)(rand8() % 10)) {
                        if (HmfModelData[(s16)mdl].rot.y <= 360.0f) {
                            HmfModelData[(s16)mdl].rot.y -= 360.0f;
                        }
                        D_8010BDE0_swing_n_swipe[i]++;
                    }
                } else {
                    HmfModelData[(s16)mdl].rot.y -= 10.0f;
                    if (!(u8)(rand8() % 10)) {
                        if (HmfModelData[(s16)mdl].rot.y < 0.0f) {
                            HmfModelData[(s16)mdl].rot.y += 360.0f;
                        }
                        D_8010BDE0_swing_n_swipe[i]++;
                    }
                }
                D_8010BDEC_swing_n_swipe[i][0] = D_8010BDEC_swing_n_swipe[i][1] = 0.0f;
                break;
            case 2:
                ox = HmfModelData[(s16)mdl].pos.x;
                oz = HmfModelData[(s16)mdl].pos.z;
                dx = cosdf(HmfModelData[(s16)mdl].rot.y + 270.0f) * 10.0f;
                dz = sindf(HmfModelData[(s16)mdl].rot.y + 270.0f) * 10.0f;
                HmfModelData[(s16)mdl].pos.x += dx;
                HmfModelData[(s16)mdl].pos.z -= dz;
                HmfModelData[(s16)mdl].rot.y =
                    -atan2df(oz - HmfModelData[(s16)mdl].pos.z, ox - HmfModelData[(s16)mdl].pos.x) + 270.0f;
                if (func_8010BA40_swing_n_swipe(i) == 1 || func_8010BB88_swing_n_swipe(i) == 1) {
                    HmfModelData[(s16)mdl].pos.x -= dx;
                    HmfModelData[(s16)mdl].pos.z += dz;
                    D_8010BDE0_swing_n_swipe[i]++;
                    st[i][0] = (u8)(rand8() % 180) + 90.0f;
                } else if (HmfModelData[(s16)mdl].pos.x > D_8010BD38_swing_n_swipe) {
                    HmfModelData[(s16)mdl].pos.x = D_8010BD38_swing_n_swipe;
                    D_8010BDE0_swing_n_swipe[i]++;
                    st[i][0] = 270;
                } else if (HmfModelData[(s16)mdl].pos.x < D_8010BD30_swing_n_swipe) {
                    HmfModelData[(s16)mdl].pos.x = D_8010BD30_swing_n_swipe;
                    D_8010BDE0_swing_n_swipe[i]++;
                    st[i][0] = 90;
                } else if (HmfModelData[(s16)mdl].pos.z > D_8010BD3C_swing_n_swipe) {
                    HmfModelData[(s16)mdl].pos.z = D_8010BD3C_swing_n_swipe;
                    D_8010BDE0_swing_n_swipe[i]++;
                    st[i][0] = 0;
                } else if (HmfModelData[(s16)mdl].pos.z < D_8010BD34_swing_n_swipe) {
                    HmfModelData[(s16)mdl].pos.z = D_8010BD34_swing_n_swipe;
                    D_8010BDE0_swing_n_swipe[i]++;
                    st[i][0] = 180;
                }
                break;
            case 3:
                st[i][0] = st[i][0] % 360;
                st[i][1] = rand8() & 1;
                D_8010BDE0_swing_n_swipe[i] = 1;
                break;
            }
        }
        i = 0;
    }
    for (i = 0; i < 5; i++) {
        mdl = D_8010C170_swing_n_swipe[i][0];
        if (D_8010BDE0_swing_n_swipe[i] == 2) {
            if (D_8010BDEC_swing_n_swipe[i][1] < 0.0f) {
                HmfModelData[(s16)mdl].rot.y += 3.0f;
                v = D_8010BDEC_swing_n_swipe[i][1] + 1.0f;
            } else if (D_8010BDEC_swing_n_swipe[i][1] > 0.0f) {
                HmfModelData[(s16)mdl].rot.y -= 3.0f;
                v = D_8010BDEC_swing_n_swipe[i][1] - 1.0f;
            } else {
                v = (u8)(rand8() % 80) - 40;
            }
            D_8010BDEC_swing_n_swipe[i][1] = v;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010897C_swing_n_swipe);
#endif

/* After a catch (D_8010C148_swing_n_swipe 4, 5): the other thieves flee off the field and the netted one is
 * flung away. */
void func_801092B4_swing_n_swipe(void) {
    omObjData* obj = D_8010C140_swing_n_swipe;
    s16 i;
    u16 mdl;
    u16 shadow;
    f32 ox;
    f32 oz;

    if (D_8010C148_swing_n_swipe == 4) {
        for (i = 0; i < 5; i++) {
            if (i != D_8010C15E_swing_n_swipe) {
                mdl = D_8010C170_swing_n_swipe[i][0];
                shadow = D_8010C170_swing_n_swipe[i][1];
                switch (D_8010BE14_swing_n_swipe[i]) {
                case 0:
                    D_8010C0C0_swing_n_swipe[i].x = HmfModelData[(s16)mdl].pos.x;
                    D_8010C0C0_swing_n_swipe[i].y = HmfModelData[(s16)mdl].pos.y;
                    D_8010C14A_swing_n_swipe[i] = 1;
                    func_8001C92C_main(mdl, 2.0f);
                    D_8010BE20_swing_n_swipe[i] = 1;
                    D_8010BE14_swing_n_swipe[i]++;
                    break;
                case 1:
                    ox = HmfModelData[(s16)mdl].pos.x;
                    oz = HmfModelData[(s16)mdl].pos.z;
                    if (obj->trans.x <= ox) {
                        HmfModelData[(s16)mdl].pos.x = ox + 10.0f;
                    } else {
                        HmfModelData[(s16)mdl].pos.x = HmfModelData[(s16)mdl].pos.x - 10.0f;
                    }
                    HmfModelData[(s16)mdl].pos.z += 27.0f;
                    HmfModelData[(s16)mdl].rot.y =
                        -atan2df(oz - HmfModelData[(s16)mdl].pos.z, ox - HmfModelData[(s16)mdl].pos.x) + 270.0f;
                    if (HmfModelData[(s16)mdl].pos.x <= -1200.0f) {
                        D_8010BE14_swing_n_swipe[i]++;
                    }
                    break;
                case 2:
                    func_8001C8A8_main(mdl, 0);
                    func_8001C8A8_main(shadow, 0);
                    D_8010BE14_swing_n_swipe[i]++;
                    break;
                }
            }
        }
    }
    if (D_8010C148_swing_n_swipe == 4 || D_8010C148_swing_n_swipe == 5) {
        for (i = 0; i < 5; i++) {
            if (i == D_8010C15E_swing_n_swipe) {
                mdl = D_8010C170_swing_n_swipe[i][0];
                shadow = D_8010C170_swing_n_swipe[i][1];
                switch (D_8010BE14_swing_n_swipe[i]) {
                case 0:
                    D_8010BE30_swing_n_swipe = D_8010C140_swing_n_swipe->rot.y + 270.0f;
                    D_8010BE2C_swing_n_swipe = -2.0f;
                    HmfModelData[(s16)mdl].rot.y = D_8010BE30_swing_n_swipe;
                    D_8010C14A_swing_n_swipe[i] = 3;
                    D_8010BE14_swing_n_swipe[i]++;
                    break;
                case 1:
                    HmfModelData[(s16)mdl].pos.x -= cosdf(D_8010BE30_swing_n_swipe + 270.0f) * 100.0f;
                    HmfModelData[(s16)mdl].pos.z += sindf(D_8010BE30_swing_n_swipe + 270.0f) * 100.0f;
                    HmfModelData[(s16)mdl].pos.y += D_8010BE2C_swing_n_swipe * D_8010BE2C_swing_n_swipe
                                                    * (D_8010BE2C_swing_n_swipe <= 0.0f ? 17.5f : -17.5f);
                    if (HmfModelData[(s16)mdl].pos.z <= -4000.0f && HmfModelData[(s16)mdl].scale.x > 0.0f) {
                        HmfModelData[(s16)mdl].scale.x = HmfModelData[(s16)mdl].scale.y = HmfModelData[(s16)mdl].scale.z =
                            HmfModelData[(s16)mdl].scale.z - 0.025f;
                    }
                    if (D_8010BE2C_swing_n_swipe <= 0.0f) {
                        D_8010BE2C_swing_n_swipe += 0.11f;
                    } else {
                        D_8010BE2C_swing_n_swipe = 0.0f;
                    }
                    if (sindf(D_8010BE20_swing_n_swipe[i] * 3.0f) != 1.0f) {
                        HmfModelData[(s16)mdl].rot.x = 0.0f - sindf(D_8010BE20_swing_n_swipe[i]++ * 3.0f) * 90.0f;
                    } else {
                        HmfModelData[(s16)mdl].rot.x = -90.0f;
                    }
                    if (HmfModelData[(s16)mdl].pos.x >= 5000.0f || HmfModelData[(s16)mdl].pos.x <= -5000.0f
                        || HmfModelData[(s16)mdl].pos.z >= 5000.0f || HmfModelData[(s16)mdl].pos.z <= -6000.0f) {
                        D_8010BE14_swing_n_swipe[i]++;
                    }
                    break;
                case 2:
                    func_8001C8A8_main(mdl, 0);
                    func_8001C8A8_main(shadow, 0);
                    D_8010BE14_swing_n_swipe[i]++;
                    break;
                }
                break;
            }
        }
    }
}

/* After a loss (D_8010C148_swing_n_swipe 3): the thieves line up left to right, in the order they stand, and turn
 * to face the player. */
void func_801099E8_swing_n_swipe(void) {
    Vec line[5] = {
        { -370.0f, 0.0f, 325.0f }, { -190.0f, 0.0f, 100.0f }, { 0.0f, 0.0f, -150.0f },
        { 190.0f, 0.0f, 100.0f }, { 370.0f, 0.0f, 325.0f },
    };
    s16 rank = 0;
    s16 i;
    s16 j;
    u16 mdl;
    f32 ox;
    f32 oz;

    if (D_8010BE34_swing_n_swipe[0] == 0) {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (i != j && HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.x
                                  > HmfModelData[D_8010C170_swing_n_swipe[j][0]].pos.x) {
                    rank++;
                }
            }
            D_8010BE4C_swing_n_swipe[i] = rank;
            rank = 0;
        }
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (i != j && D_8010BE4C_swing_n_swipe[i] == D_8010BE4C_swing_n_swipe[j]) {
                    D_8010BE4C_swing_n_swipe[j]++;
                    i = 0;
                    break;
                }
            }
        }
    }
    i = 0;
    if (D_8010C148_swing_n_swipe == 3) {
        for (i = 0; i < 5; i++) {
            mdl = D_8010C170_swing_n_swipe[i][0];
            switch (D_8010BE34_swing_n_swipe[i]) {
            case 0:
                D_8010C100_swing_n_swipe[i].x = HmfModelData[(s16)mdl].pos.x;
                D_8010C100_swing_n_swipe[i].z = HmfModelData[(s16)mdl].pos.z;
                D_8010C14A_swing_n_swipe[i] = 1;
                D_8010BE34_swing_n_swipe[i]++;
                break;
            case 1:
                ox = HmfModelData[(s16)mdl].pos.x;
                oz = HmfModelData[(s16)mdl].pos.z;
                HmfModelData[(s16)mdl].pos.x =
                    D_8010C100_swing_n_swipe[i].x
                    - sindf(D_8010BE40_swing_n_swipe[i] * 1.5f)
                          * (D_8010C100_swing_n_swipe[i].x - line[D_8010BE4C_swing_n_swipe[i]].x);
                HmfModelData[(s16)mdl].pos.z =
                    D_8010C100_swing_n_swipe[i].z
                    - sindf(D_8010BE40_swing_n_swipe[i] * 1.5f)
                          * (D_8010C100_swing_n_swipe[i].z - line[D_8010BE4C_swing_n_swipe[i]].z);
                HmfModelData[(s16)mdl].rot.y =
                    -atan2df(oz - HmfModelData[(s16)mdl].pos.z, ox - HmfModelData[(s16)mdl].pos.x) + 270.0f;
                if (sindf(D_8010BE40_swing_n_swipe[i]++ * 1.5f) == 1.0f) {
                    HmfModelData[(s16)mdl].pos.x = line[D_8010BE4C_swing_n_swipe[i]].x;
                    HmfModelData[(s16)mdl].pos.z = line[D_8010BE4C_swing_n_swipe[i]].z;
                    D_8010BE40_swing_n_swipe[i] = 0;
                    D_8010BE34_swing_n_swipe[i]++;
                }
                break;
            case 2:
                if (HmfModelData[(s16)mdl].rot.y >= 360.0f) {
                    HmfModelData[(s16)mdl].rot.y -= 360.0f;
                }
                if (HmfModelData[(s16)mdl].rot.y < 0.0f) {
                    HmfModelData[(s16)mdl].rot.y += 360.0f;
                }
                if (HmfModelData[(s16)mdl].rot.y >= 180.0f) {
                    if ((HmfModelData[(s16)mdl].rot.y += 6.75f) >= 360.0f) {
                        HmfModelData[(s16)mdl].rot.y = 0.0f;
                        D_8010BE34_swing_n_swipe[i]++;
                    }
                } else if (HmfModelData[(s16)mdl].rot.y > 0.0f) {
                    if ((HmfModelData[(s16)mdl].rot.y -= 6.75f) <= 0.0f) {
                        HmfModelData[(s16)mdl].rot.y = 0.0f;
                        D_8010BE34_swing_n_swipe[i]++;
                    }
                } else if (HmfModelData[(s16)mdl].rot.y == 0.0f) {
                    HmfModelData[(s16)mdl].pos.y = 0.0f;
                    D_8010BE34_swing_n_swipe[i]++;
                }
                break;
            case 3:
                D_8010C14A_swing_n_swipe[i] = 0;
                D_8010BE34_swing_n_swipe[i]++;
                break;
            }
        }
    }
}

/* The coin bags (one in front of each thief's place), their coin counts and shadows, and the net's dust. */
void func_8010A0E4_swing_n_swipe(omObjData* obj) {
    s16 i;

    D_8010C190_swing_n_swipe[0][0] = func_8000B108_main(0x610001, 0x2B9);
    D_8010C190_swing_n_swipe[0][2] = func_8000B108_main(9, 0x2B9);
    for (i = 1; i < 5; i++) {
        D_8010C190_swing_n_swipe[i][0] = Hu3DModelLink(D_8010C190_swing_n_swipe[0][0]);
        D_8010C190_swing_n_swipe[i][2] = Hu3DModelLink(D_8010C190_swing_n_swipe[0][2]);
    }
    for (i = 0; i < 5; i++) {
        Hu3DModelPosSet(D_8010C190_swing_n_swipe[i][0], D_8010BE58_swing_n_swipe[i].x, D_8010BE58_swing_n_swipe[i].y,
                        D_8010BE58_swing_n_swipe[i].z);
        Hu3DModelScaleSet(D_8010C190_swing_n_swipe[i][0], 1.5f, 1.5f, 1.5f);
        func_8001C92C_main(D_8010C190_swing_n_swipe[i][0], 0.0f);
        D_8010C190_swing_n_swipe[i][1] =
            D_800CBB60_main[SprModelRead(D_8010BE94_swing_n_swipe[D_800A11D0_main[i]], 0xA0, 0x10)].unk00;
        Hu3DModelPosSet(D_8010C190_swing_n_swipe[i][1], HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.x, 1000.0f,
                        HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.z);
        Hu3DModelScaleSet(D_8010C190_swing_n_swipe[i][1], 3.0f, 3.0f, 3.0f);
        func_8001C8A8_main(D_8010C190_swing_n_swipe[i][1], 0);
        Hu3DModelPosSet(D_8010C190_swing_n_swipe[i][2], HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.x, 0.0f,
                        HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.z);
        Hu3DModelScaleSet(D_8010C190_swing_n_swipe[i][2], 1.5f, 1.0f, 1.5f);
    }
    D_8010C1B8_swing_n_swipe[0] = func_8000CED8_main(0xB0004, 0x2A9);
    func_800138EC_main(D_8010C1B8_swing_n_swipe[0], 1, 0);
    D_8010C1B8_swing_n_swipe[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelScaleSet(D_8010C1B8_swing_n_swipe[1], 1.0f, 1.0f, 1.0f);
    func_8001C8A8_main(D_8010C1B8_swing_n_swipe[1], 0);
    D_8010C154_swing_n_swipe = 0;
    obj->func = func_8010B01C_swing_n_swipe;
}

/* The coin bags' show (D_8010C154_swing_n_swipe 1): they open, the counts drop in, then close again. */
void func_8010A3FC_swing_n_swipe(void) {
    s16 i;

    if (D_8010C154_swing_n_swipe == 1) {
        switch (D_8010BEE4_swing_n_swipe) {
        case 0:
            for (i = 0; i < 5; i++) {
                func_8001C92C_main(D_8010C190_swing_n_swipe[i][0], 1.0f);
                func_8001C8A8_main(D_8010C190_swing_n_swipe[i][1], 1);
            }
            HuAudFXPlay(0x4F1);
            D_8010BEE4_swing_n_swipe++;
            break;
        case 1:
            for (i = 0; i < 5; i++) {
                HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.y = 1000.0f - sindf(D_8010BEE6_swing_n_swipe * 0.75f) * 960.0f;
                if (D_8010BEE6_swing_n_swipe >= 100 && HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.x > 2.0f) {
                    HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.x =
                        HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.y =
                            HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.z =
                                HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.z - 0.1f;
                }
            }
            if (sindf(D_8010BEE6_swing_n_swipe++ * 0.75f) == 1.0f) {
                D_8010BEE4_swing_n_swipe++;
                HuAudFXPlay(0x4F0);
            }
            break;
        case 2:
            for (i = 0; i < 5; i++) {
                func_8001C92C_main(D_8010C190_swing_n_swipe[i][0], -1.0f);
            }
            if (HmfModelData[D_8010C190_swing_n_swipe[0][0]].unk40 <= 0.0f) {
                for (i = 0; i < 5; i++) {
                    func_8001C92C_main(D_8010C190_swing_n_swipe[i][0], 0.0f);
                    func_8001C6A8_main(D_8010C190_swing_n_swipe[i][0], 0.0f);
                    func_8001C8A8_main(D_8010C190_swing_n_swipe[i][1], 0);
                }
                D_8010BEE4_swing_n_swipe++;
            }
            break;
        case 3:
            D_8010BEE6_swing_n_swipe = 0;
            D_8010BEE4_swing_n_swipe = 0;
            D_8010C154_swing_n_swipe = 0;
            break;
        }
    }
}

/* While carried (D_8010C154_swing_n_swipe 2): each bag rides on its thief's back. */
void func_8010A780_swing_n_swipe(void) {
    s16 i = 0;

    if (D_8010C154_swing_n_swipe == 2) {
        for (i = 0; i < 5; i++) {
            HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.x =
                HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.x
                + cosdf(HmfModelData[D_8010C170_swing_n_swipe[i][0]].rot.y + 270.0f) * 50.0f;
            HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.y = HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.y + 140.0f;
            HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.z =
                HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.z
                - sindf(HmfModelData[D_8010C170_swing_n_swipe[i][0]].rot.y + 270.0f) * 50.0f;
            HmfModelData[D_8010C190_swing_n_swipe[i][0]].rot.y = HmfModelData[D_8010C170_swing_n_swipe[i][0]].rot.y;
        }
    }
}

/* After a catch (D_8010C154_swing_n_swipe 3): the netted thief's bag drops to the ground. */
void func_8010A994_swing_n_swipe(void) {
    s16 i = D_8010C15E_swing_n_swipe;

    if (D_8010C154_swing_n_swipe == 3) {
        HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.y -= 10.0f;
        if (HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.y <= 0.0f) {
            HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.y = 0.0f;
            D_8010C154_swing_n_swipe = 0;
        }
    }
}

/* The prize (D_8010C154_swing_n_swipe 4): the netted bag opens, its coin count flies up to the player with a
 * burst of dust and bobs over the field. */
void func_8010AA3C_swing_n_swipe(void) {
    s16 i;

    if (D_8010C154_swing_n_swipe == 4) {
        i = D_8010C15E_swing_n_swipe;
        switch (D_8010BEE8_swing_n_swipe) {
        case 0:
            Hu3DModelPosSet(D_8010C190_swing_n_swipe[i][1], HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.x, 40.0f,
                            HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.z);
            func_8001C8A8_main(D_8010C190_swing_n_swipe[i][1], 1);
            func_8001C92C_main(D_8010C190_swing_n_swipe[i][0], 1.0f);
            HuAudFXPlay(0x4F7);
            D_8010BEE8_swing_n_swipe++;
            break;
        case 1:
            if (D_800CCF58_main[HmfModelData[D_8010C190_swing_n_swipe[i][0]].unk02].unk02
                == HmfModelData[D_8010C190_swing_n_swipe[i][0]].unk40) {
                HuAudFXPlay(0x4F3);
                func_800138EC_main(D_8010C1B8_swing_n_swipe[0], 1, 1);
                func_8000CD00_main(D_8010C1B8_swing_n_swipe[0], 5.0f, 20.0f, 10.0f);
                func_8000D018_main(D_8010C1B8_swing_n_swipe[0], 100.0f);
                func_8000CFA4_main(D_8010C1B8_swing_n_swipe[0], HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.x,
                                   HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.y,
                                   HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.z);
                func_8001C8A8_main(D_8010C1B8_swing_n_swipe[1], 1);
                Hu3DModelPosSet(D_8010C1B8_swing_n_swipe[1], HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.x, 0.0f,
                                HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.z);
                D_8010C158_swing_n_swipe = 1;
                D_8010BEE8_swing_n_swipe++;
            }
            break;
        case 2:
            HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.y =
                40.0f - sindf(D_8010BEEA_swing_n_swipe * 3.0f) * -310.0f;
            if (D_8010BEEA_swing_n_swipe >= 10 && HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.x < 3.0f) {
                HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.x =
                    HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.y =
                        HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.z =
                            HmfModelData[D_8010C190_swing_n_swipe[i][1]].scale.z + 0.1f;
            }
            if (sindf(D_8010BEEA_swing_n_swipe++ * 3.0f) == 1.0f) {
                D_8010BEEA_swing_n_swipe = 0;
                D_8010BEE8_swing_n_swipe++;
            }
            break;
        case 3:
            HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.x =
                HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.x
                - sindf(D_8010BEEA_swing_n_swipe * 3.0f) * HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.x;
            HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.z =
                HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.z
                - sindf(D_8010BEEA_swing_n_swipe * 3.0f) * (HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.z - 400.0f);
            if (sindf(D_8010BEEA_swing_n_swipe++ * 3.0f) == 1.0f) {
                D_8010BEEA_swing_n_swipe = 0;
                D_8010BEE8_swing_n_swipe++;
            }
            break;
        case 4:
            HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.y = sindf(D_8010BEEA_swing_n_swipe * 6.0f) * 10.0f + 350.0f;
            if (D_8010BEEA_swing_n_swipe++ >= 60) {
                D_8010BEEA_swing_n_swipe = 0;
            }
            break;
        }
        func_8000CFA4_main(D_8010C1B8_swing_n_swipe[0], HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.x,
                           HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.y,
                           HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.z);
        Hu3DModelPosSet(D_8010C1B8_swing_n_swipe[1], HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.x, 0.0f,
                        HmfModelData[D_8010C190_swing_n_swipe[i][1]].pos.z);
    }
}

/* Per frame: the bags' shadows follow and shrink with height. */
void func_8010B01C_swing_n_swipe(omObjData* obj) {
    s16 i;
    f32 scale;

    for (i = 0; i < 5; i++) {
        scale = 1.5f - HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.y * 0.010714286f;
        Hu3DModelPosSet(D_8010C190_swing_n_swipe[i][2], HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.x, 0.0f,
                        HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.z);
        Hu3DModelScaleSet(D_8010C190_swing_n_swipe[i][2], scale, 1.0f, scale);
    }
}

/* The effect models: a puff over each thief, the result mark over the player and the net's swish. */
void func_8010B100_swing_n_swipe(omObjData* obj) {
    s16 i;

    for (i = 0; i < 5; i++) {
        D_8010C1C0_swing_n_swipe[i] = func_8000B108_main(0x610005, 0x2B9);
        Hu3DModelScaleSet(D_8010C1C0_swing_n_swipe[i], 1.5f, 1.5f, 1.0f);
        func_8001C8A8_main(D_8010C1C0_swing_n_swipe[i], 0);
    }
    D_8010C1D0_swing_n_swipe[0] = func_8010B8EC_swing_n_swipe(0x610005);
    D_8010C1CC_swing_n_swipe[0] = func_8000B108_main(0xB0006, 0x2B9);
    D_8010C1D0_swing_n_swipe[1] = func_8010B8EC_swing_n_swipe(0xB0006);
    func_8001C8A8_main(D_8010C1CC_swing_n_swipe[0], 0);
    D_8010C1CC_swing_n_swipe[1] = func_8000B108_main(0x610004, 0x2B9);
    D_8010C1D0_swing_n_swipe[2] = func_8010B8EC_swing_n_swipe(0x610004);
    func_8001C8A8_main(D_8010C1CC_swing_n_swipe[1], 0);
    obj->func = func_8010B23C_swing_n_swipe;
}

// masked 16: register allocation (retail computes each puff's address late and numbers the loop registers
// differently)
#ifdef NON_MATCHING
/* Per frame: play each effect once when its flag is raised (1), hide it when its motion ends (2). */
void func_8010B23C_swing_n_swipe(omObjData* obj) {
    s16 skip;
    s16 i;

    if (D_8010C156_swing_n_swipe == 1) {
        skip = -1;
        if (D_8010C13C_swing_n_swipe == 0) {
            skip = D_8010C15E_swing_n_swipe;
        }
        for (i = 0; i < 5; i++) {
            if (i != skip) {
                Hu3DModelPosSet(D_8010C1C0_swing_n_swipe[i], HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.x,
                                HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.y + 125.0f,
                                HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.z + 50.0f);
                func_8001C8A8_main(D_8010C1C0_swing_n_swipe[i], 1);
                func_8001C5B4_main(D_8010C1C0_swing_n_swipe[i], D_8010C1D0_swing_n_swipe[0]);
                func_8001C8A8_main(D_8010C190_swing_n_swipe[i][0], 0);
                func_8001C8A8_main(D_8010C190_swing_n_swipe[i][1], 0);
                func_8001C8A8_main(D_8010C190_swing_n_swipe[i][2], 0);
            }
        }
        HuAudFXPlay(0x4F2);
        D_8010C156_swing_n_swipe = 2;
    }
    if (D_8010C156_swing_n_swipe == 2) {
        if (D_800CCF58_main[HmfModelData[D_8010C1C0_swing_n_swipe[0]].unk02].unk02
            == HmfModelData[D_8010C1C0_swing_n_swipe[0]].unk40) {
            for (i = 0; i < 5; i++) {
                if (i != D_8010C15E_swing_n_swipe) {
                    func_8001C8A8_main(D_8010C1C0_swing_n_swipe[i], 0);
                }
            }
        }
    }
    if (D_8010C158_swing_n_swipe == 1) {
        i = D_8010C15E_swing_n_swipe;
        Hu3DModelPosSet(D_8010C1C0_swing_n_swipe[i], HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.x, 10.0f,
                        HmfModelData[D_8010C190_swing_n_swipe[i][0]].pos.z + 50.0f);
        func_8001C8A8_main(D_8010C1C0_swing_n_swipe[i], 1);
        func_8001C5B4_main(D_8010C1C0_swing_n_swipe[i], D_8010C1D0_swing_n_swipe[0]);
        func_8001C8A8_main(D_8010C190_swing_n_swipe[i][0], 0);
        func_8001C8A8_main(D_8010C190_swing_n_swipe[i][2], 0);
        D_8010C146_swing_n_swipe = 3;
        D_8010C15A_swing_n_swipe = 1;
        D_8010C158_swing_n_swipe = 2;
    } else if (D_8010C158_swing_n_swipe == 2) {
        if (D_800CCF58_main[HmfModelData[D_8010C1C0_swing_n_swipe[D_8010C15E_swing_n_swipe]].unk02].unk02
            == HmfModelData[D_8010C1C0_swing_n_swipe[D_8010C15E_swing_n_swipe]].unk40) {
            func_8001C8A8_main(D_8010C1C0_swing_n_swipe[D_8010C15E_swing_n_swipe], 0);
        }
    }
    if (D_8010C15A_swing_n_swipe == 1) {
        Hu3DModelPosSet(D_8010C1CC_swing_n_swipe[0], D_8010C140_swing_n_swipe->trans.x, 100.0f,
                        D_8010C140_swing_n_swipe->trans.z + 150.0f);
        func_8001C8A8_main(D_8010C1CC_swing_n_swipe[0], 1);
        func_8001C5B4_main(D_8010C1CC_swing_n_swipe[0], D_8010C1D0_swing_n_swipe[1]);
        func_8001C8A8_main(D_8010C166_swing_n_swipe, 0);
        D_8010C15A_swing_n_swipe = 2;
    }
    if (D_8010C15A_swing_n_swipe == 2) {
        if (D_800CCF58_main[HmfModelData[D_8010C1CC_swing_n_swipe[0]].unk02].unk02 == HmfModelData[D_8010C1CC_swing_n_swipe[0]].unk40) {
            func_8001C8A8_main(D_8010C1CC_swing_n_swipe[0], 0);
        }
    }
    if (D_8010C15C_swing_n_swipe == 1) {
        Hu3DModelPosSet(D_8010C1CC_swing_n_swipe[1],
                        D_8010C140_swing_n_swipe->trans.x + cosdf(D_8010C140_swing_n_swipe->rot.y - 90.0f) * 100.0f, 50.0f,
                        D_8010C140_swing_n_swipe->trans.z + sindf(D_8010C140_swing_n_swipe->rot.y - 90.0f) * 100.0f);
        func_8001C8A8_main(D_8010C1CC_swing_n_swipe[1], 1);
        func_8001C5B4_main(D_8010C1CC_swing_n_swipe[1], D_8010C1D0_swing_n_swipe[2]);
        D_8010C15C_swing_n_swipe = 2;
    }
    if (D_8010C15C_swing_n_swipe == 2) {
        if (D_800CCF58_main[HmfModelData[D_8010C1CC_swing_n_swipe[1]].unk02].unk02 == HmfModelData[D_8010C1CC_swing_n_swipe[1]].unk40) {
            func_8001C8A8_main(D_8010C1CC_swing_n_swipe[1], 0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B23C_swing_n_swipe);
#endif

s16 func_8010B840_swing_n_swipe(s32 file, u16 attr, u16 prio, s16 x, s16 y) {
    s16 id = InitEspriteSlot(func_8000B838_main(file), 0, 0);

    func_8000BC48_main(id, attr);
    func_8000BCC8_main(id, prio);
    func_8000BBD4_main(id, x, y);
    return id;
}

s16 func_8010B8EC_swing_n_swipe(s32 arg0) {
    s16 ret = func_8000B13C_main(arg0);

    if (ret < 0) {
        ret = -1;
    }
    return ret;
}

// retail keeps an unused 3 in s1 across the loop (a dead local?) and so allocates the floats differently
// H0: loading pos.x/pos.z into locals before the subtractions gives retail's load order (masked 14) but not the 3
#ifdef NON_MATCHING
/* 1 if the point 50 in front of the player is within 100 of a thief. */
s16 func_8010B920_swing_n_swipe(void) {
    omObjData* obj = D_8010C140_swing_n_swipe;
    f32 x = obj->trans.x + cosdf(obj->rot.y - 90.0f) * 50.0f;
    f32 z = obj->trans.z - sindf(obj->rot.y - 90.0f) * 50.0f;
    f32 dx;
    f32 dz;
    s16 i;

    for (i = 0; i < 5; i++) {
        dx = x;
        dz = z;
        dx -= HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.x;
        dz -= HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.z;
        if (HuSqrtf(dx * dx + dz * dz) < 100.0f) {
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_40_swing_n_swipe/2E6BE0", func_8010B920_swing_n_swipe);
#endif

/* 1 if the point 50 in front of thief i is within 150 of the player. */
s16 func_8010BA40_swing_n_swipe(s16 i) {
    omObjData* obj = D_8010C140_swing_n_swipe;
    f32 x = HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.x
            + cosdf(HmfModelData[D_8010C170_swing_n_swipe[i][0]].rot.y - 90.0f) * 50.0f;
    f32 z = HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.z
            - sindf(HmfModelData[D_8010C170_swing_n_swipe[i][0]].rot.y - 90.0f) * 50.0f;
    f32 dx = obj->trans.x;
    f32 dz = obj->trans.z;

    dx -= x;
    dz -= z;
    if (HuSqrtf(dx * dx + dz * dz) < 150.0f) {
        return 1;
    }
    return 0;
}

/* 1 if the point 50 in front of thief i is within 150 of another thief. */
s16 func_8010BB88_swing_n_swipe(s16 i) {
    f32 x = HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.x
            + cosdf(HmfModelData[D_8010C170_swing_n_swipe[i][0]].rot.y - 90.0f) * 50.0f;
    f32 z = HmfModelData[D_8010C170_swing_n_swipe[i][0]].pos.z
            - sindf(HmfModelData[D_8010C170_swing_n_swipe[i][0]].rot.y - 90.0f) * 50.0f;
    f32 dx;
    f32 dz;
    s16 j;

    for (j = 0; j < 5; j++) {
        if (i != j) {
            dx = HmfModelData[D_8010C170_swing_n_swipe[j][0]].pos.x;
            dz = HmfModelData[D_8010C170_swing_n_swipe[j][0]].pos.z;
            dx -= x;
            dz -= z;
            if (HuSqrtf(dx * dx + dz * dz) < 150.0f) {
                return 1;
            }
        }
    }
    return 0;
}

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
