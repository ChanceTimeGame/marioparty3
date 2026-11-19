#include "common.h"
// m7 sb: Stardust Battle
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

/* A pooled particle effect (Log Jam's SbEffect). */
typedef struct SbEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ RGBA color;
    /* 0x08 */ f32 frame;
    /* 0x0C */ f32 speed;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec vel;
    /* 0x28 */ Vec scale;
} SbEffect; // Size 0x34

typedef struct SbCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} SbCamera; // Size 0x24

typedef struct SbBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} SbBytes;

typedef union SbPack {
    void *p;
    SbBytes b;
} SbPack;

typedef struct SbB44 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04; /* mode */
    /* 0x06 */ s16 unk06; /* timer */
    /* 0x08 */ char unk08[0xC];
} SbB44; // Size 0x14

typedef f32 Matrix4f[4][4];

#define SB_WRAP(v)             \
    if ((v) >= 360.0) {        \
        (v) -= 360.0;          \
    } else if ((v) < 0.0) {    \
        (v) += 360.0;          \
    }

/* The game's player record (D_80114AC8_stardust_battle points at one). Grown as functions are written. */
typedef struct SbPlayer {
    /* 0x00 */ char unk00[0x20];
    /* 0x20 */ s16 unk20; /* GwPlayer index */
} SbPlayer;

/* D_80114B1C_stardust_battle */
typedef struct SbB1C {
    /* 0x00 */ char unk00[6];
    /* 0x06 */ s16 unk06; /* stars left */
} SbB1C;

/* A camera pose in .data (center, rotation, zoom). */
typedef struct SbCamPose {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} SbCamPose; // Size 0x1C

// end m7 sb types

// protos begin
void func_801059A0_stardust_battle(void);
void func_80105D18_stardust_battle(omObjData *obj);
void func_80105DA0_stardust_battle(omObjData *obj);
void func_801065B4_stardust_battle(omObjData* obj);
void func_80108444_stardust_battle(void);
void func_8010844C_stardust_battle(void);
void func_801089B4_stardust_battle(void);
u16 func_8010EE38_stardust_battle(s32 dirAndFile);
void func_8010F580_stardust_battle(s16 idx);
void func_8010F5B0_stardust_battle(s16 idx);
void func_8010F5E0_stardust_battle(void);
void func_8010F73C_stardust_battle(omObjData *obj);
s32 func_8010F890_stardust_battle(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color);
void func_80110914_stardust_battle(void);
void func_801115F8_stardust_battle(s32 idx);
void func_801117E4_stardust_battle(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
void func_801119D4_stardust_battle(s32 idx);
f32 func_80111B28_stardust_battle(f32 a, f32 b);
f32 func_80111DF8_stardust_battle(f32 t, f32 a, f32 b);
f32 func_80111E10_stardust_battle(f32 t, f32 a, f32 b);
f32 func_80111EB8_stardust_battle(f32 x, f32 z);
void func_80111F38_stardust_battle(Vec* dir, f32* angles);
void func_80111FC0_stardust_battle(omObjData *obj, u32 value);
void *func_80111FEC_stardust_battle(omObjData *obj);
void func_80112040_stardust_battle(s16 mdl, const char *part, Matrix4f *out);
s32 func_80112980_stardust_battle(HuSprite_Unk84_Struct *arg0, RGBA *arg1);
s32 func_80113568_stardust_battle(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2);
void func_8011376C_stardust_battle(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3);
s32 func_801138A0_stardust_battle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
// protos end

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
f32 fabsf(f32);

/* still asm */
void func_80106690_stardust_battle(omObjData *obj);
void func_80106A3C_stardust_battle(omObjData *obj);
void func_80106B60_stardust_battle(omObjData *obj);
void func_80106C30_stardust_battle(omObjData *obj);
void func_801065D8_stardust_battle(omObjData *obj);
void func_80106D0C_stardust_battle(void);
void func_80107E84_stardust_battle(s32);
s16 func_80107FA4_stardust_battle(void);
s16 func_80107FE8_stardust_battle(void);
void func_80108074_stardust_battle(void);
void func_801080B0_stardust_battle(void);
void func_801080EC_stardust_battle(void);
void func_80108B34_stardust_battle(void);
void func_8010A74C_stardust_battle(void);
void func_8010BFE4_stardust_battle(f32, s32);
void func_8010C06C_stardust_battle(void);
void func_8010C0C8_stardust_battle(void);
void func_8010C1F8_stardust_battle(s32, s32, s32, s32);
void func_8010C2CC_stardust_battle(f32);
f32 func_8010C32C_stardust_battle(void);
void func_8010C38C_stardust_battle(f32);
f32 func_8010C3EC_stardust_battle(void);
s16 func_8010C508_stardust_battle(void);
void func_8010CB34_stardust_battle(void);
void func_8010ED7C_stardust_battle(void);
void func_8010EE7C_stardust_battle(void);
void func_8010F400_stardust_battle(s32, s32);
void func_8010FA60_stardust_battle(void);
void func_801107E4_stardust_battle(void);
f32 func_80111C2C_stardust_battle(f32 target, f32 cur, f32 step);
s32 func_801138A0_stardust_battle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8010F73C_stardust_battle(omObjData *obj);

extern RGBA D_80113CF4_stardust_battle;
u16 GWMgRecordGet(s16 arg0);
u8 func_8000B638_main(void);
void func_800E6F0C_minigame(s32);
void func_8003F5C0_main(void);
extern const s16 D_80114100_stardust_battle[];
extern const s16 D_8011410C_stardust_battle[];
extern SbCamPose D_80113CF8_stardust_battle;
extern SbCamPose D_80113D14_stardust_battle;
extern SbCamPose D_80113D30_stardust_battle;
extern SbCamPose D_80113D68_stardust_battle;
extern s16 D_80113DBC_stardust_battle[];
extern s16 D_80113DC4_stardust_battle[];
extern s16 D_80113DCC_stardust_battle[];
extern void (*D_80113DDC_stardust_battle)(omObjData *);
extern s16 D_80113DE0_stardust_battle; /* intro sound */
extern omObjData *D_80114A98_stardust_battle;
extern s32 D_80114A9C_stardust_battle;
extern s32 D_80114AA0_stardust_battle;
extern s32 D_80114AA4_stardust_battle; /* state timer */
extern s32 D_80114AA8_stardust_battle;
extern s32 D_80114AAC_stardust_battle;
extern s32 D_80114AB0_stardust_battle; /* game frames */
extern s32 D_80114AB4_stardust_battle; /* record */
extern s32 D_80114AB8_stardust_battle; /* game state */
extern s32 D_80114ABC_stardust_battle;
extern s32 D_80114AC0_stardust_battle; /* record mode */
extern s32 D_80114AC4_stardust_battle;
extern SbPlayer *D_80114AC8_stardust_battle;
extern s16 D_80114ACC_stardust_battle;
extern s16 D_80114ACE_stardust_battle;
extern Matrix4f D_80114AD0_stardust_battle;
extern s32 D_80114B10_stardust_battle;
extern s16 D_80114B14_stardust_battle;
extern s32 D_80114B18_stardust_battle;
extern SbB1C *D_80114B1C_stardust_battle;
extern s32 D_80114B24_stardust_battle;
extern s16 *D_80114B28_stardust_battle;
extern s32 D_80114B2C_stardust_battle;
extern s16 D_80114B54_stardust_battle;
extern s32 D_80114B58_stardust_battle;
extern s32 D_80114B5C_stardust_battle;
extern s32 D_80114BB0_stardust_battle;
extern s32 D_80114BB4_stardust_battle;
extern D_80111B50_vine_with_me_Struct D_80114BB8_stardust_battle;
extern s32 D_80113F08_stardust_battle; /* debug camera mode */
extern s32 D_80113F0C_stardust_battle; /* debug text x */
extern s32 D_80113F10_stardust_battle; /* debug text y */
extern SbB44 *D_80114B44_stardust_battle;
extern SbCamera D_80114B60_stardust_battle[2];
extern s32 D_80114BA8_stardust_battle;
extern s32 D_80114BAC_stardust_battle;
extern s32 fontcolor;
extern s8 HmfPauseF;
extern Matrix4f *D_800D1358_main;
extern s16 *D_800D04B4_main;
extern s16 D_800CD1B0_main;
extern s16 D_800D138A_main;
extern Matrix4f D_800D5A00_main[];
void func_8008A070_main(Matrix4f);
void func_80017CD0_main(Matrix4f, f32, f32, f32);
void func_80017D24_main(Matrix4f, f32, f32, f32);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
f64 fabs(f64);
void func_8002DFF8_main(HmfData *, f32, D_800CCF58_main_Struct *, s32);
void func_8002EAC0_main(HmfData *, f32, f32);
s16 func_8002C834_main(HmfData *, const char *);
void func_80016C2C_main(HmfData *arg0, s16 arg1, s16 arg2);
f64 fmod(f64, f64);
extern Gfx D_80114020_stardust_battle[];
extern s16 *D_80114B30_stardust_battle; /* s16[0x20] sprite/file ids */
extern omObjData *D_80114B48_stardust_battle;
extern SbEffect *D_80114B4C_stardust_battle;

void func_801059A0_stardust_battle(void) {
    u8 cam;
    s32 level;

    Hu3DAnimInit(50);
    omInitObjMan(50, 10);
    func_8004A208_main();
    func_800142A0_main(0x40);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 4000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_80114AB0_stardust_battle = 0;
    D_80114AA4_stardust_battle = 0;
    D_80114AA0_stardust_battle = 0;
    D_80114AA8_stardust_battle = 0;
    D_80114AAC_stardust_battle = 0;
    D_80114AB8_stardust_battle = -1;
    D_80114ABC_stardust_battle = 0;
    D_80114AC0_stardust_battle = 0;
    D_80114B14_stardust_battle = 1;
    D_80114B24_stardust_battle = 9;
    D_80114B28_stardust_battle = D_80113DBC_stardust_battle;
    D_80114AC4_stardust_battle = 1;
    D_80114AC0_stardust_battle = _CheckFlag(0x1C);
    if (D_80114AC0_stardust_battle != 0) {
        D_80114AC0_stardust_battle = 1;
        D_80114AB4_stardust_battle = GWMgRecordGet(9);
        if (D_80114AB4_stardust_battle == 0) {
            D_80114AB4_stardust_battle = 4500;
        }
    }
    if (!(GwSystem.playMode & 4) || _CheckFlag(0x1C) != 0) {
        level = 2;
    } else {
        level = GwStory.unk2;
    }
    switch (level) {
    case 0:
        D_80114B24_stardust_battle = 3;
        D_80114B28_stardust_battle = D_80113DCC_stardust_battle;
        break;
    case 1:
        D_80114B24_stardust_battle = 6;
        D_80114B28_stardust_battle = D_80113DC4_stardust_battle;
        break;
    default:
        D_80114B24_stardust_battle = 9;
        D_80114B28_stardust_battle = D_80113DBC_stardust_battle;
        break;
    }
    D_80114ACC_stardust_battle = -1;
    D_80114ACE_stardust_battle = 0;
    D_80114B30_stardust_battle = HuMemAllocTag(0x40, 31000);
    D_80114AC8_stardust_battle = NULL;
    D_80114B10_stardust_battle = 0;
    D_80114B18_stardust_battle = 0;
    D_80114B1C_stardust_battle = NULL;
    D_80114B2C_stardust_battle = 0;
    D_80114B58_stardust_battle = 0;
    D_80114B5C_stardust_battle = 0;
    guMtxIdentF(D_80114AD0_stardust_battle);
    D_80114A98_stardust_battle = omAddObj(0x20, 0, 0, -1, func_80105D18_stardust_battle);
    memset(&D_80114BB8_stardust_battle, 0, 0x28);
    D_80114BB8_stardust_battle.unk01 = 4;
    func_800E5EA0_minigame(&D_80114BB8_stardust_battle);
    func_80045010_main(D_80114100_stardust_battle, 1);
    func_80045010_main(D_8011410C_stardust_battle, 1);
}

void func_80105D18_stardust_battle(omObjData *obj) {
    obj->func = func_80105DA0_stardust_battle;
    func_80108B34_stardust_battle();
    func_8010F5E0_stardust_battle();
    func_8010FA60_stardust_battle();
    func_80106D0C_stardust_battle();
    func_8010A74C_stardust_battle();
    func_8010CB34_stardust_battle();
    func_801107E4_stardust_battle();
    func_8010EE7C_stardust_battle();
    D_80114B54_stardust_battle = func_8000D658_main(0x1CA9, 10);
    if (_CheckFlag(0xA) != 0) {
        D_80114A9C_stardust_battle = 1;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114100_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_8011410C_stardust_battle);

void func_80105DA0_stardust_battle(omObjData *obj) {
    SbB1C *b1c = D_80114B1C_stardust_battle;
    s32 left;

    switch (D_80114AB8_stardust_battle) {
    case -1:
        if (D_80114AA4_stardust_battle > 0) {
            D_80114BB4_stardust_battle = 0;
            func_801117E4_stardust_battle(D_80113CF8_stardust_battle.center.x, D_80113CF8_stardust_battle.center.y, D_80113CF8_stardust_battle.center.z, D_80113CF8_stardust_battle.rot.x, D_80113CF8_stardust_battle.rot.y, D_80113CF8_stardust_battle.rot.z, D_80113CF8_stardust_battle.zoom, 1);
            D_80113DE0_stardust_battle = HuAudFXPlay(0x50C);
            WipeCreateIn(0xFF, 0x10);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 0:
        if (WipeStatGet() == 0 && func_80107FA4_stardust_battle() != 0) {
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 1:
        if (func_80107FE8_stardust_battle() != 0) {
            D_80114BB4_stardust_battle = 0;
            func_801117E4_stardust_battle(D_80113D14_stardust_battle.center.x, D_80113D14_stardust_battle.center.y, D_80113D14_stardust_battle.center.z, D_80113D14_stardust_battle.rot.x, D_80113D14_stardust_battle.rot.y, D_80113D14_stardust_battle.rot.z, D_80113D14_stardust_battle.zoom, 37);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 2:
        if (D_80114BB0_stardust_battle == 0) {
            HuAudSeqPlay(0x41);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 3:
        if (D_80114AA4_stardust_battle >= 22.5) {
            D_80114BB4_stardust_battle = 3;
            func_801117E4_stardust_battle(D_80113D30_stardust_battle.center.x, D_80113D30_stardust_battle.center.y, D_80113D30_stardust_battle.center.z, D_80113D30_stardust_battle.rot.x, D_80113D30_stardust_battle.rot.y, D_80113D30_stardust_battle.rot.z, D_80113D30_stardust_battle.zoom, 15);
            func_80107E84_stardust_battle(0);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 4:
        if (D_80114BB0_stardust_battle == 0) {
            func_8010C1F8_stardust_battle(0, 0, 300, 0);
            HuAudFXPlay(0x511);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 5:
        if (func_8010C3EC_stardust_battle() >= 60.0f && func_8010C32C_stardust_battle() == 1.0f) {
            func_8010C38C_stardust_battle(60.0f);
            func_8010C2CC_stardust_battle(0.0f);
        }
        if (D_80114AA4_stardust_battle == 43.0f) {
            func_8010BFE4_stardust_battle(450.0f, 30);
        }
        if (D_80114AA4_stardust_battle > 45.0f) {
            func_8010C1F8_stardust_battle(0, 60, 0, 4);
            func_8010C2CC_stardust_battle(2.0f);
            D_80114BB4_stardust_battle = 2;
            func_801117E4_stardust_battle(D_80113D68_stardust_battle.center.x, D_80113D68_stardust_battle.center.y, D_80113D68_stardust_battle.center.z, D_80113D68_stardust_battle.rot.x, D_80113D68_stardust_battle.rot.y, D_80113D68_stardust_battle.rot.z, D_80113D68_stardust_battle.zoom, 22);
            if (D_80113DE0_stardust_battle != -1) {
                func_8004AEF0_main(D_80113DE0_stardust_battle, 22);
                D_80113DE0_stardust_battle = -1;
            }
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 6:
        if (D_80114BB0_stardust_battle == 0) {
            GMesCreate(9);
            HuAudFXPlay(0xE);
            func_80108074_stardust_battle();
            D_80114AB8_stardust_battle++;
        }
        break;
    case 7:
        if (GMesStatGet() == 0) {
            func_8010F400_stardust_battle(0, D_80114AB0_stardust_battle);
            func_800E6F0C_minigame(2);
            D_80114AB8_stardust_battle++;
        }
        break;
    case 8:
        func_8010F400_stardust_battle(0, ++D_80114AB0_stardust_battle);
        if (D_80114AB0_stardust_battle == 4470) {
            func_8010F5B0_stardust_battle(0);
            func_8010F5B0_stardust_battle(1);
        } else if (D_80114AB0_stardust_battle == 4499) {
            GMesCreate(0x1A, 31, 0x9C, 0x20);
        } else if (D_80114AB0_stardust_battle >= 4500) {
            left = 5429 - D_80114AB0_stardust_battle;
            func_8003F578_main(left / 30);
        }
        if (D_80114AB0_stardust_battle >= 5400 || D_80114ACE_stardust_battle != 0 || b1c->unk06 <= 0) {
            func_8003F5C0_main();
            GMesCreate(0x14);
            func_800E6F0C_minigame(3);
            func_8010C06C_stardust_battle();
            func_8010ED7C_stardust_battle();
            HuAudSeqFadeOut(120);
            func_801080EC_stardust_battle();
            if (b1c->unk06 <= 0) {
                D_80114ACC_stardust_battle = 0;
                left = (5429 - D_80114AB0_stardust_battle) / 30;
                if (left >= 60) {
                    GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = 3;
                } else if (left >= 40) {
                    GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = 2;
                } else if (left >= 20) {
                    GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = 1;
                } else {
                    GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = 0;
                }
            } else {
                GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = -1;
            }
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 9:
        if (GMesStatGet() == 0 && (func_8010C508_stardust_battle() == 12 || (D_80114AC0_stardust_battle != 0 && D_80114ACC_stardust_battle >= 0 && D_80114AB0_stardust_battle < D_80114AB4_stardust_battle))) {
            func_800E6F0C_minigame(4);
            func_801080B0_stardust_battle();
            D_80114ABC_stardust_battle = 0;
            if (D_80114AC0_stardust_battle == 0 || D_80114ACC_stardust_battle < 0 || D_80114AB0_stardust_battle >= D_80114AB4_stardust_battle) {
                func_8010C0C8_stardust_battle();
            }
            if (D_80114AC0_stardust_battle != 0) {
                if (D_80114ACC_stardust_battle >= 0) {
                    D_80113DDC_stardust_battle = func_80106690_stardust_battle;
                } else {
                    D_80113DDC_stardust_battle = func_80106A3C_stardust_battle;
                }
            } else if (D_80114ACC_stardust_battle >= 0) {
                D_80113DDC_stardust_battle = func_80106B60_stardust_battle;
            } else {
                D_80113DDC_stardust_battle = func_80106C30_stardust_battle;
            }
            D_80114AB8_stardust_battle++;
            D_80114AA4_stardust_battle = 0;
        }
        break;
    case 10:
        if (D_80113DDC_stardust_battle != NULL) {
            D_80113DDC_stardust_battle(obj);
        }
        break;
    case 32:
    case 64:
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreateOut(11, 0x10);
        HuAudSeqFadeOut(0x10);
        func_8004AB0C_main(0x10);
        HuAudFXPlay(0x509);
        D_80114AB8_stardust_battle = 99;
        D_80114AA4_stardust_battle = 0;
        break;
    case 99:
        if (WipeStatGet() == 0) {
            obj->func = func_801065B4_stardust_battle;
        }
        break;
    }
    func_801065D8_stardust_battle(obj);
    D_80114AA0_stardust_battle++;
    D_80114AA4_stardust_battle++;
}

void func_801065B4_stardust_battle(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801065D8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106690_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106A3C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106B60_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106C30_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106D0C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106EB0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801073F4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107760_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107DCC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107E84_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107F34_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107FA4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107FE8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108074_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801080B0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801080EC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108120_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801081FC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801082C4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108404_stardust_battle);

void func_80108444_stardust_battle(void) {
}

void func_8010844C_stardust_battle(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108454_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801084B0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801086E8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010882C_stardust_battle);

void func_801089B4_stardust_battle(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801089BC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108AC4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108B34_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108C14_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108D84_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108EC4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109128_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010929C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801092F0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801093CC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109424_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109B18_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109F94_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109FE4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A04C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A204_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A418_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A5A4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A5E0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A690_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A74C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010AAC4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010BFE4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C06C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C0C8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C1F8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C2CC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C32C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C38C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C3EC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C44C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C498_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C508_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C538_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C5A8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CA48_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CB34_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CE5C_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114528_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_8011452C_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114530_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", jtbl_80114538_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114550_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114558_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114560_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114568_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114570_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114578_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114580_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114588_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114590_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114598_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_801145A0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010DADC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010DE64_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010DF70_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E03C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E300_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E35C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E46C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E4C8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E524_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010EA04_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010ED7C_stardust_battle);

u16 func_8010EE38_stardust_battle(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010EE7C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F0E8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F400_stardust_battle);

void func_8010F580_stardust_battle(s16 idx) {
    D_80114B44_stardust_battle[idx].unk04 = 1;
    D_80114B44_stardust_battle[idx].unk06 = 0;
}

void func_8010F5B0_stardust_battle(s16 idx) {
    D_80114B44_stardust_battle[idx].unk04 = 2;
    D_80114B44_stardust_battle[idx].unk06 = 0;
}

void func_8010F5E0_stardust_battle(void) {
    HuSprite_Unk84_Struct *spr;
    SbEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_80114B30_stardust_battle[1] = func_8010EE38_stardust_battle(0xB));
    D_80114B48_stardust_battle = omAddObj(0x1E, 0, 0, -1, func_8010F73C_stardust_battle);
    D_80114B4C_stardust_battle = effect = HuMemAllocTag(sizeof(SbEffect) * 4, 0x7918);
    for (i = 0; i < 4; i++, effect++) {
        if (i == 0) {
            effect->model = func_80112980_stardust_battle(spr, &D_80113CF4_stardust_battle);
        } else {
            effect->model = func_80113568_stardust_battle(spr, D_80114B4C_stardust_battle->model, &D_80113CF4_stardust_battle);
        }
        effect->active = 0;
        *(u32 *)&effect->color = *(u32 *)&D_80113CF4_stardust_battle;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &HmfModelData[effect->model];
        model->unk40 = 0.0f;
    }
}

void func_8010F73C_stardust_battle(omObjData *obj) {
    HuSprite_Unk84_Struct *spr;
    SbEffect *effect;
    HmfModel *model;
    s32 i;

    i = 0;
    spr = func_80055194_main(D_80114B30_stardust_battle[1]);
    effect = D_80114B4C_stardust_battle;
    do {
        if (effect->active != 0) {
            model = &HmfModelData[effect->model];
            if (!(model->unk18 & 4)) {
                effect->pos.x += effect->vel.x;
                effect->pos.y += effect->vel.y;
                effect->pos.z += effect->vel.z;
                model->pos.x = effect->pos.x;
                model->pos.y = effect->pos.y;
                model->pos.z = effect->pos.z;
                model->scale.x = effect->scale.x;
                model->scale.y = effect->scale.y;
                model->scale.z = effect->scale.z;
                func_8011376C_stardust_battle(effect->model, spr, (s32)effect->frame, &effect->color);
                effect->frame += effect->speed;
                if ((s32)effect->frame >= (s32)spr->unk10) {
                    effect->active = 0;
                    effect->frame = 0.0f;
                    model->unk18 |= 4;
                }
            }
        }
        i++;
        effect++;
    } while (i < 4);
}

s32 func_8010F890_stardust_battle(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color) {
    HuSprite_Unk84_Struct *spr;
    SbEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_80114B30_stardust_battle[1]);
    for (i = 0, effect = D_80114B4C_stardust_battle; i < 4; i++, effect++) {
        if (effect->active == 0) {
            effect->active = 1;
            model = &HmfModelData[effect->model];
            if (pos != NULL) {
                effect->pos.x = pos->x;
                effect->pos.y = pos->y;
                effect->pos.z = pos->z;
            } else {
                effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
            }
            if (vel != NULL) {
                effect->vel.x = vel->x;
                effect->vel.y = vel->y;
                effect->vel.z = vel->z;
            } else {
                effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
            }
            if (scale != NULL) {
                effect->scale.x = scale->x;
                effect->scale.y = scale->y;
                effect->scale.z = scale->z;
            } else {
                effect->scale.x = effect->scale.y = effect->scale.z = 1.0f;
            }
            effect->color = *color;
            effect->speed = speed;
            effect->frame = 0.0f;
            func_8011376C_stardust_battle(effect->model, spr, 0, &effect->color);
            func_8001C258_main(effect->model, 4, 0);
            model->unk40 = 0.0f;
            model->pos.x = effect->pos.x;
            model->pos.y = effect->pos.y;
            model->pos.z = effect->pos.z;
            model->scale.x = effect->scale.x;
            model->scale.y = effect->scale.y;
            model->scale.z = effect->scale.z;
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FA60_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FBCC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FCBC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FE74_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80110364_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80110758_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80110780_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801107C4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801107E4_stardust_battle);

void func_80110914_stardust_battle(void) {
    SbCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_80113F08_stardust_battle) {
        case 1:
            if ((u16)D_800CDA7C_main[0] & 0x8000) {
                speed = 8.0f;
            }
            if (D_800CDA7C_main[0] & 0x4000) {
                speed = 0.5f;
            }
            if (D_800D5558_main[0] & 0x1000) {
                Center.x = 0.0f;
                Center.y = 191.2f;
                Center.z = 0.2f;
                CRot.x = -14.5f;
                CRot.y = 0.0f;
                CRot.z = 0.0f;
                CZoom = 1069.0f;
            } else {
                c.rot.x = (f32)D_800D20A1_main[0] * 0.125 * speed;
                c.rot.y = (f32)D_800CBB6E_main[0] * 0.125 * speed;
                if (D_800CDA7C_main[0] & 0x200) {
                    c.center.x = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 0x100) {
                    c.center.x = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x800) {
                    c.center.z = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x400) {
                    c.center.z = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 8) {
                    c.center.y = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 4) {
                    c.center.y = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 1) {
                    c.zoom = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 2) {
                    c.zoom = -(2.0 * speed);
                }
                c.center.x += Center.x;
                c.center.y += Center.y;
                c.center.z += Center.z;
                c.rot.x += CRot.x;
                c.rot.y += CRot.y;
                c.rot.z += CRot.z;
                c.zoom += CZoom;
                func_801117E4_stardust_battle(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 104, D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
                D_80113F0C_stardust_battle++;
            }
            if (D_800CDA7C_main[0] & 0x202) {
                D_80113F0C_stardust_battle--;
            }
            if (D_800CDA7C_main[0] & 0x404) {
                D_80113F10_stardust_battle++;
            }
            if (D_800CDA7C_main[0] & 0x808) {
                D_80113F10_stardust_battle--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 104, D_800D5218_main);
            break;
        case 3:
            D_80113F08_stardust_battle = 0;
            break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_80113F08_stardust_battle == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_80113F08_stardust_battle++ >= 4) {
            D_80113F08_stardust_battle = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111004_stardust_battle);

void func_801115F8_stardust_battle(s32 idx) {
    SB_WRAP(CRot.x);
    SB_WRAP(CRot.y);
    SB_WRAP(CRot.z);
    D_80114B60_stardust_battle[idx].center.x = Center.x;
    D_80114B60_stardust_battle[idx].center.y = Center.y;
    D_80114B60_stardust_battle[idx].center.z = Center.z;
    D_80114B60_stardust_battle[idx].rot.x = CRot.x;
    D_80114B60_stardust_battle[idx].rot.y = CRot.y;
    D_80114B60_stardust_battle[idx].rot.z = CRot.z;
    D_80114B60_stardust_battle[idx].zoom = CZoom;
    D_80114B60_stardust_battle[idx].unk1C = D_80114B60_stardust_battle[idx].unk20 = 0.0f;
}

void func_801117E4_stardust_battle(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_80114BA8_stardust_battle = frames - 1;
        D_80114BAC_stardust_battle = frames;
        if (cx != 65535.0f) {
            D_80114B60_stardust_battle[0].center.x = cx;
        } else {
            D_80114B60_stardust_battle[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_80114B60_stardust_battle[0].center.y = cy;
        } else {
            D_80114B60_stardust_battle[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_80114B60_stardust_battle[0].center.z = cz;
        } else {
            D_80114B60_stardust_battle[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_80114B60_stardust_battle[0].rot.x = rx;
        } else {
            D_80114B60_stardust_battle[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_80114B60_stardust_battle[0].rot.y = ry;
        } else {
            D_80114B60_stardust_battle[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_80114B60_stardust_battle[0].rot.z = rz;
        } else {
            D_80114B60_stardust_battle[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_80114B60_stardust_battle[0].zoom = zoom;
        } else {
            D_80114B60_stardust_battle[0].zoom = CZoom;
        }
        func_801115F8_stardust_battle(1);
    }
}

void func_801119D4_stardust_battle(s32 idx) {
    HuCamera *cam = &gCameraList[idx];
    f32 rx = CRot.x;
    f32 ry = CRot.y;

    cam->pos.x = Center.x + sindf(ry) * cosdf(rx) * CZoom;
    cam->pos.y = -sindf(rx) * CZoom + Center.y;
    cam->pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
    cam->at.x = Center.x;
    cam->at.y = Center.y;
    cam->at.z = Center.z;
    cam->up.x = sindf(ry) * sindf(rx);
    cam->up.y = cosdf(rx);
    cam->up.z = cosdf(ry) * sindf(rx);
}

f32 func_80111B28_stardust_battle(f32 a, f32 b) {
    f32 d;

    if (a >= 360.0f) {
        a -= 360.0f;
    } else if (a < 0.0f) {
        a += 360.0f;
    }
    if (b >= 360.0f) {
        b -= 360.0f;
    } else if (b < 0.0f) {
        b += 360.0f;
    }
    d = a - b;
    if (d <= -180.0f) {
        d += 360.0f;
    } else if (d >= 180.0f) {
        d -= 360.0f;
    }
    return d;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111C2C_stardust_battle);

f32 func_80111DF8_stardust_battle(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

f32 func_80111E10_stardust_battle(f32 t, f32 a, f32 b) {
    return func_80111C2C_stardust_battle(b, a, fabsf(func_80111B28_stardust_battle(b, a) * t));
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111E70_stardust_battle);

f32 func_80111EB8_stardust_battle(f32 x, f32 z) {
    f32 a = atan2df(z, x);

    if (a < 0.0) {
        a += 360.0;
    } else if (a >= 360.0) {
        a -= 360.0;
    }
    return a;
}

void func_80111F38_stardust_battle(Vec* dir, f32* angles) {
    f32 h = sqrtf(dir->x * dir->x + dir->z * dir->z);

    *angles++ = func_80111EB8_stardust_battle(h, -dir->y);
    *angles++ = func_80111EB8_stardust_battle(dir->z, dir->x);
    *angles = 0.0f;
}

void func_80111FC0_stardust_battle(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}

void *func_80111FEC_stardust_battle(omObjData *obj) {
    SbPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}

void func_80112040_stardust_battle(s16 mdl, const char *part, Matrix4f *out) {
    HmfModel *model = &HmfModelData[mdl];
    HmfData *hmf = model->hmf;
    s16 idx = func_8002C834_main(hmf, part);
    D_800CCF58_main_Struct *anim = &D_800CCF58_main[HmfModelData[mdl].unk02];
    s16 parts[4]; /* retail's frame leaves 8 bytes here, as in func_80016B00_main */

    D_800D1358_main = out;
    D_800D04B4_main = parts;
    D_800CD1B0_main = 0;
    if (model->unk06 != 0xFF) {
        hmf->unk94 = (HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->unk06];
        hmf->unkAC = model->unk58;
    } else {
        hmf->unk94 = NULL;
    }
    if (model->unk04 != 0xFF && model->unk0C != 0) {
        hmf->unk90 = (HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->unk04];
        hmf->unkA4 = model->unk4C;
        hmf->unkA8 = (f32)model->unk0E / (f32)model->unk0C;
    } else {
        hmf->unk90 = NULL;
    }
    guMtxIdentF(D_800D5A00_main[0]);
    func_8002DFF8_main(hmf, model->unk40, anim, 1);
    if (hmf->unk90 != NULL) {
        func_8002EAC0_main(hmf, hmf->unkA4, hmf->unkA8);
    }
    if (hmf->unk94 != NULL) {
        func_8002DFF8_main(hmf, hmf->unkAC, (D_800CCF58_main_Struct *)hmf->unk94, 0);
    }
    D_800D138A_main = 0;
    func_80016C2C_main(hmf, 0, idx);
    if (D_800CD1B0_main >= 2) {
        osSyncPrintf("Mtx Made Over\n");
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80112220_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801122D0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801127B8_stardust_battle);

s32 func_80112980_stardust_battle(HuSprite_Unk84_Struct *arg0, RGBA *arg1) {
    HmfData *temp_s4;
    Gfx *temp_v0_0;
    Gfx *temp_v0_2;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_s1;

    temp_v0_0 = temp_v0_2 = HuMemAlloc(0x10000);
    temp_v0 = func_8001A894_main(0x1CC1, temp_v0_0, 4);
    temp_s4 = HmfModelData[temp_v0].hmf;
    temp_s4->unk60->unk50 |= 0x01010000;
    HuMemFree(temp_s4->unk3C);
    temp_s4->unk3C = HuMemAllocTag(0x18, D_800CDD6A_main);
    func_801138A0_stardust_battle(arg0, temp_s4, 1.0f, 0, 0);
    gSPDisplayList(temp_v0_2++, osVirtualToPhysical(D_80114020_stardust_battle));
    gDPPipeSync(temp_v0_2++);
    gDPSetCycleType(temp_v0_2++, G_CYC_1CYCLE);
    gDPPipeSync(temp_v0_2++);
    gSPClearGeometryMode(temp_v0_2++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(temp_v0_2++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(temp_v0_2++, G_CD_NOISE);
    gDPSetTexturePersp(temp_v0_2++, G_TP_NONE);
    gDPSetTextureFilter(temp_v0_2++, G_TF_BILERP);
    gDPSetTextureConvert(temp_v0_2++, G_TC_FILT);
    gDPSetAlphaDither(temp_v0_2++, G_AD_PATTERN);
    gDPSetAlphaCompare(temp_v0_2++, G_AC_NONE);
    gDPSetBlendColor(temp_v0_2++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(temp_v0_2++);
    gDPSetRenderMode(temp_v0_2++, G_RM_ZB_CLD_SURF, G_RM_NOOP2);
    if (arg0->unk18 & 0x8000) {
        gDPSetCombineLERP(temp_v0_2++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(temp_v0_2++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(temp_v0_2++);
    gSPEndDisplayList(temp_v0_2++);
    temp_s0 = (u32)temp_v0_2 - (u32)temp_v0_0;
    temp_s4->unk3C->unk10 = HuMemAllocTag(temp_s0, temp_s4->unk0E);
    bcopy(temp_v0_0, temp_s4->unk3C->unk10, temp_s0);
    HuMemFree(temp_v0_0);
    temp_v0_0 = temp_v0_2 = HuMemAlloc(0x10000);
    gSPTexture(temp_v0_2++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(temp_v0_2++, G_TP_PERSP);
    if (arg0->unk1A >= 2) {
        gDPSetTextureLUT(temp_v0_2++, G_TT_RGBA16);
        if (arg0->unk18 == 4) {
            gDPLoadTLUT_pal16(temp_v0_2++, 0, arg0->unk0C);
        } else {
            gDPLoadTLUT_pal256(temp_v0_2++, arg0->unk0C);
        }
        gDPPipeSync(temp_v0_2++);
        var_a2 = 2;
    } else {
        gDPSetTextureLUT(temp_v0_2++, G_TT_NONE);
        gDPPipeSync(temp_v0_2++);
        var_a2 = (arg0->unk18 & 0x8000) ? 4 : 0;
    }
    switch (arg0->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(temp_v0_2++, 0x02000000, var_a2,
                                   arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(temp_v0_2++, 0x02000000, var_a2, G_IM_SIZ_8b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(temp_v0_2++, 0x02000000, var_a2, G_IM_SIZ_16b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(temp_v0_2++);
    gSPSegment(temp_v0_2++, 0x01, osVirtualToPhysical(temp_s4->unk44[0]));
    gSPVertex(temp_v0_2++, 0x01000000, 4, 0);
    gSP2Triangles(temp_v0_2++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(temp_v0_2++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(temp_v0_2++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(temp_v0_2++);
    gSPEndDisplayList(temp_v0_2++);
    temp_s0 = (u32)temp_v0_2 - (u32)temp_v0_0;
    temp_s4->unk3C->unk14 = HuMemAllocTag(temp_s0, temp_s4->unk0E);
    bcopy(temp_v0_0, temp_s4->unk3C->unk14, temp_s0);
    HuMemFree(temp_v0_0);
    for (var_s1 = 0; var_s1 < D_800D1FF0_main; var_s1++) {
        temp_v0_2 = temp_s4->unk3C->unk00[var_s1 + 1] = HuMemAllocTag(0x100, temp_s4->unk0E);
        gDPPipeSync(temp_v0_2++);
        gSPSegment(temp_v0_2++, 0x02, osVirtualToPhysical(arg0->unk00->unk00));
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s4->unk3C->unk10));
        gDPSetPrimColor(temp_v0_2++, 0, 0, arg1->r, arg1->g, arg1->b, arg1->a);
        gDPPipeSync(temp_v0_2++);
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s4->unk3C->unk14));
        gDPPipeSync(temp_v0_2++);
        gSPEndDisplayList(temp_v0_2++);
    }
    temp_s4->unk3C->unk00[0] = temp_s4->unk3C->unk00[D_800D2008_main + 1];
    return temp_v0;
}

s32 func_80113568_stardust_battle(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2) {
    HmfModel *model = &HmfModelData[arg1];
    HmfData *src = model->hmf;
    HmfData *temp_s1;
    Gfx *temp_v0_2;
    s32 temp_v0;
    s32 var_s2;

    temp_v0 = func_8001A894_main(model->unk18, NULL, 4);
    temp_s1 = HmfModelData[temp_v0].hmf;
    temp_s1->unk60->unk50 = src->unk60->unk50;
    HuMemFree(temp_s1->unk3C);
    temp_s1->unk3C = HuMemAllocTag(0x18, D_800CDD6A_main);
    temp_s1->unk3C->unk10 = src->unk3C->unk10;
    temp_s1->unk3C->unk14 = src->unk3C->unk14;
    for (var_s2 = 0; var_s2 < D_800D1FF0_main; var_s2++) {
        temp_v0_2 = temp_s1->unk3C->unk00[var_s2 + 1] = HuMemAllocTag(0x100, temp_s1->unk0E);
        gDPPipeSync(temp_v0_2++);
        gSPSegment(temp_v0_2++, 0x02, osVirtualToPhysical(arg0->unk00->unk00));
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s1->unk3C->unk10));
        gDPSetPrimColor(temp_v0_2++, 0, 0, arg2->r, arg2->g, arg2->b, arg2->a);
        gDPPipeSync(temp_v0_2++);
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s1->unk3C->unk14));
        gDPPipeSync(temp_v0_2++);
        gSPEndDisplayList(temp_v0_2++);
    }
    temp_s1->unk3C->unk00[0] = temp_s1->unk3C->unk00[D_800D2008_main + 1];
    return temp_v0;
}

void func_8011376C_stardust_battle(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3) {
    HmfModel *model = &HmfModelData[modelId];
    HmfData *temp_s3 = model->hmf;
    HmfModelData_Unk64_Unk3C_Struct *temp_v1 = temp_s3->unk3C;
    Gfx *temp_s0 = temp_v1->unk00[D_800D2008_main + 1];

    temp_v1->unk00[0] = temp_s0;
    gDPPipeSync(&temp_s0[0]);
    gSPSegment(&temp_s0[1], 0x02, osVirtualToPhysical(arg1->unk00[arg2].unk00));
    gSPDisplayList(&temp_s0[2], osVirtualToPhysical(temp_s3->unk3C->unk10));
    gDPSetPrimColor(&temp_s0[3], 0, 0, arg3->r, arg3->g, arg3->b, arg3->a);
    gDPPipeSync(&temp_s0[4]);
    gSPDisplayList(&temp_s0[5], osVirtualToPhysical(temp_s3->unk3C->unk14));
    gDPPipeSync(&temp_s0[6]);
    gSPEndDisplayList(&temp_s0[7]);
}

s32 func_801138A0_stardust_battle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
    Vtx *temp_s7;
    Vtx *var_s1;
    Vtx_t *var_t0;
    Vtx_t *var_a3;
    s32 var_a2;
    s32 temp_s4;
    s32 temp_a1;
    s32 sp24;
    s32 temp_f2;
    s32 var_s0;
    s32 var_s2;
    s32 sp2C;
    s32 temp_lo;
    s32 temp_s3;
    s32 var_s0_2;
    s32 var_a2_2;

    if (arg0->unk1A >= 2) {
        var_a2 = 0x800;
    } else {
        var_a2 = 0x1000;
    }
    temp_s4 = arg0->unk00->unk04;
    temp_a1 = arg0->unk00->unk06;
    sp24 = temp_s4 * 100.0 * arg2 / 32.0;
    temp_f2 = temp_a1 * 100.0 * arg2 / 32.0;
    if ((arg0->unk18 & 0xFFF) == 4) {
        var_s0 = ((temp_s4 + 1) & 0xFFFE) * temp_a1 * 4;
    } else {
        var_s0 = temp_s4 * temp_a1 * arg0->unk18;
    }
    var_s0 = (var_s0 < 0) ? (var_s0 + 7) : var_s0;
    var_s0 >>= 3;
    var_s2 = var_s0 / var_a2;
    if (var_s2 <= 0) {
        var_s2 = 1;
    }
    sp2C = temp_a1 / var_s2;
    temp_lo = temp_f2 / var_s2;
    temp_s3 = var_s2 * 4;
    temp_s7 = var_s1 = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
    memset(temp_s7, 0, temp_s3 * sizeof(Vtx));
    for (var_s0_2 = 0; var_s0_2 < var_s2; var_s0_2++, var_s1 += 4) {
        var_s1[0].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[0].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[0].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[0].v.tc[1] = 0;
        var_s1[1].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[1].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[1].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[1].v.tc[1] = (sp2C - 1) * 64;
        var_s1[2].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[2].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[2].v.tc[0] = 0;
        var_s1[2].v.tc[1] = 0;
        var_s1[3].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[3].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[3].v.tc[0] = 0;
        var_s1[3].v.tc[1] = (sp2C - 1) * 64;
        for (var_a2_2 = 0; var_a2_2 < 4; var_a2_2++) {
            var_s1[var_a2_2].v.ob[0] += arg3;
            var_s1[var_a2_2].v.ob[1] += arg4;
            var_s1[var_a2_2].v.ob[2] = 0;
            var_s1[var_a2_2].v.flag = 0;
            var_s1[var_a2_2].v.cn[3] = 0xFF;
            var_s1[var_a2_2].v.cn[0] = var_s1[var_a2_2].v.cn[1] = var_s1[var_a2_2].v.cn[2] = 0;
        }
    }
    var_s1 = temp_s7;
    for (var_s0_2 = 0; var_s0_2 < D_800D1FF0_main; var_s0_2++) {
        arg1->unk44[var_s0_2] = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
        var_t0 = &arg1->unk44[var_s0_2]->v;
        var_a3 = &var_s1->v;
        for (var_a2_2 = 0; var_a2_2 < temp_s3; var_a2_2++) {
            *(var_t0++) = *(var_a3++);
        }
    }
    HuMemFree(temp_s7);
    return var_s2;
}
