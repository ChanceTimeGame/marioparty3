#include "common.h"
#include "game/object.h"

// sw A: Swinging with Sharks (1-player: swing on the rope and let go over a shark's back)

/* A model to load (as mgmode's MgModeModelDef); the table ends with dir == -1 */
typedef struct SwModelDef {
    /* 0x00 */ s32 dir;
    /* 0x04 */ s32 file;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 motion;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
} SwModelDef; /* size 0x24 */

/* A point of a Cheep Cheep path (D_8010B488, D_8010B5D8); the path ends with a point at 0,0,0 */
typedef struct SwPathPt {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unk0C[3];
    /* 0x18 */ f32 time; /* frames from the first point */
} SwPathPt; /* size 0x1C */

/* A shark (D_8010B9F0) */
typedef struct SwShark {
    /* 0x00 */ s16 model;
    /* 0x02 */ s16 timer;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec pos;
    /* 0x14 */ Vec base;
    /* 0x20 */ f32 angle;
    /* 0x24 */ s16 ripple;
    /* 0x26 */ char unk26[0xA];
} SwShark; /* size 0x30 */

/* A model's motion group looked up by part name (func_8001D33C_main; an N64-offset view) */
typedef struct SwPart {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk18[0x1C];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ char unk3C[0x10];
    /* 0x4C */ HuMtx4F mtx;
} SwPart;

// main
void func_8001F38C_main(s32, s32, s32);
void func_800142A0_main(s32);
void func_8004A208_main(void);
extern void HmfLightStatSet(s16, s16, s16);
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
u16 func_80049F98_main(void);
extern u8 D_800D6A90_main;
void func_8004AAD0_main(s16, s8);
s32 func_80017BB8_main(s16, s16);
u16 func_8000B108_main(s32 arg0, s32 arg1);
s16 func_8000B13C_main(s32 file);
s32 Hu3DModelLink(s16 linkMdlId);
void func_8001C5B4_main(s16, s16);
void func_8001C6A8_main(s32 model, f32 arg1);
void func_8001C814_main(s16, s16, s16);
void func_8001F304_main(s16, s16);
void func_8001FA68_main(s16);
s32 func_8001C514_main(s16);
void func_8001C448_main(s16);
s16 HmfAnimRead(HmfData *hmf, s32 dataNum, char *name);
void func_80032FF8_main(s32, u8);
extern u16 D_800A11D0_main[6];
void func_80014850_main(s16 index);
s16 func_8000CED8_main(s32, s32);
void func_800138EC_main(s16, s32, s32);
void func_8000CD00_main(s16, f32, f32, f32);
void func_8000D018_main(s16, f32);
void func_8000CFA4_main(s16, f32, f32, f32);
void func_8003F578_main(s16);
void func_8003F5C0_main(void);
void func_8004AEF0_main(s16, s32);
void Hu3DModelPosGet(s16 idx, Vec *arg1);
void *func_8001D33C_main(s16, char *);
void func_8002367C_main(HuMtx4F, HuMtx4F);
f32 func_80018ACC_main(f32 *y, f32 *x, f32 t);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);
void func_80088800_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017CD0_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80018044_main(HuMtx4F a, HuMtx4F b, HuMtx4F out);
u16 SprModelRead(s32 arg0, s32 arg1, s32 arg2);
omObjData *func_80045ED0_main(u32 arg0);
void func_80045010_main(const s16 *, s32);
extern s8 D_800CBB6E_main[];
extern s16 D_800CDA7C_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u16 D_800D530C_main;
extern u8 D_800CD280_main;

typedef struct SwSprModel { /* an entry of D_800CBB60_main (parasol_plummet's PaSprModel) */
    /* 0x00 */ s16 model;
    /* 0x02 */ char unk02[0x1E];
    /* 0x20 */ u8 *unk20; /* key-frame list */
} SwSprModel; /* size 0x24 */
extern SwSprModel *D_800CBB60_main;

// this overlay
void func_80105FE4_swinging_with_sharks(omObjData *obj);
void func_80106334_swinging_with_sharks(void);
void func_80106398_swinging_with_sharks(omObjData *obj);
void func_80106870_swinging_with_sharks(omObjData *obj);
void func_80106D44_swinging_with_sharks(omObjData *obj);
void func_80107044_swinging_with_sharks(omObjData *obj);
void func_801071A8_swinging_with_sharks(omObjData *obj);
void func_80107384_swinging_with_sharks(void);
void func_801073F0_swinging_with_sharks(omObjData *obj);
void func_80107628_swinging_with_sharks(omObjData *obj);
void func_801076DC_swinging_with_sharks(omObjData *obj);
void func_801077C4_swinging_with_sharks(void);
void func_80107954_swinging_with_sharks(omObjData *obj);
void func_80108474_swinging_with_sharks(omObjData *obj);
void func_801085F4_swinging_with_sharks(omObjData *obj);
void func_801088F0_swinging_with_sharks(f32 rx, f32 ry, f32 rz, f32 cx, f32 cy, f32 cz, f32 zoom, u16 frames);
void func_801089A4_swinging_with_sharks(omObjData *obj);
void func_80108B24_swinging_with_sharks(void);
void func_80108B4C_swinging_with_sharks(omObjData *obj);
void func_80108C08_swinging_with_sharks(f32 angle);
void func_80108DB0_swinging_with_sharks(Vec *out);
void func_80108E00_swinging_with_sharks(Vec *out);
void func_80108E50_swinging_with_sharks(HuMtx4F mtx, f32 angle);
void func_80108F20_swinging_with_sharks(s16 model, Vec *out, HuMtx4F mtx);
void func_80109020_swinging_with_sharks(omObjData *obj);
void func_801096AC_swinging_with_sharks(void);
void func_80109730_swinging_with_sharks(SwModelDef *defs, s16 idx, s16 model);
void func_8010979C_swinging_with_sharks(SwModelDef *defs);
void func_801098C0_swinging_with_sharks(omObjData *obj);
void func_80109924_swinging_with_sharks(omObjData *obj);
void func_80109950_swinging_with_sharks(void);
f32 func_80109B04_swinging_with_sharks(SwPathPt *path, f32 speed);
void func_80109C90_swinging_with_sharks(SwPathPt *path, s16 model, f32 total);
void func_8010A0C0_swinging_with_sharks(void);
void func_8010A260_swinging_with_sharks(void);
void func_8010A41C_swinging_with_sharks(void);
void func_8010A4DC_swinging_with_sharks(void);
void func_8010AA68_swinging_with_sharks(void);
void func_8010AAA0_swinging_with_sharks(void);

/* .data */
extern u8 D_8010ACE0_swinging_with_sharks; /* show the debug camera text */
extern u8 D_8010ACE1_swinging_with_sharks; /* quit */
extern f32 D_8010ACE4_swinging_with_sharks; /* rope angle */
extern f32 D_8010ACE8_swinging_with_sharks; /* swing phase, degrees */
extern SwModelDef D_8010ACEC_swinging_with_sharks[51];
extern u16 D_8010B418_swinging_with_sharks[4]; /* per CPU difficulty: odds (of 256) of aiming at a shark */
extern u8 D_8010B420_swinging_with_sharks[8]; /* per character */
extern s16 D_8010B428_swinging_with_sharks; /* splash ripple */
extern s16 D_8010B42A_swinging_with_sharks; /* swing stage */
extern s16 D_8010B42C_swinging_with_sharks; /* rope sound */
extern s32 D_8010B430_swinging_with_sharks[20]; /* prize sprites, per item */
extern s16 D_8010B480_swinging_with_sharks; /* camera move frames left */
extern f32 D_8010B484_swinging_with_sharks; /* degrees to radians */
extern SwPathPt D_8010B488_swinging_with_sharks[12];
extern SwPathPt D_8010B5D8_swinging_with_sharks[14];
extern SwPathPt *D_8010B760_swinging_with_sharks[2];
extern s16 D_8010B768_swinging_with_sharks; /* Cheep Cheeps created */
extern s16 D_8010B76A_swinging_with_sharks; /* wake ripple */
extern s16 D_8010B76C_swinging_with_sharks;

/* .bss */
extern HuMtx4F D_8010B860_swinging_with_sharks; /* "rope" matrix at rest */
extern HuMtx4F D_8010B8A0_swinging_with_sharks; /* "step" matrix at rest */
/* models, in D_8010ACEC's order: 0 sea, 2 rope, 3-7 sharks, 8-17 parts of them, 18-22 their ripples,
   32 the player (its label D_8010B920) */
extern s16 D_8010B8E0_swinging_with_sharks[50];
extern s16 D_8010B948_swinging_with_sharks[50]; /* their motions */
#define D_8010B8E6_swinging_with_sharks (&D_8010B8E0_swinging_with_sharks[3])
extern Vec D_8010B9AC_swinging_with_sharks; /* player velocity */
extern Vec D_8010B9B8_swinging_with_sharks; /* "step" position last frame */
extern Vec D_8010B9C4_swinging_with_sharks; /* player position in the air */
extern f32 D_8010B9D0_swinging_with_sharks; /* swing amplitude */
extern f32 D_8010B9D4_swinging_with_sharks;
extern s16 D_8010B9D8_swinging_with_sharks; /* player */
extern s16 D_8010B9DA_swinging_with_sharks; /* pad */
extern s16 D_8010B9DC_swinging_with_sharks; /* character */
extern s16 D_8010B9DE_swinging_with_sharks; /* the shark landed on, -1 none */
extern s16 D_8010B9E0_swinging_with_sharks; /* game state */
extern s16 D_8010B9E2_swinging_with_sharks; /* time left */
extern s16 D_8010B9E4_swinging_with_sharks;
extern s16 D_8010B9E6_swinging_with_sharks;
extern s16 D_8010B9E8_swinging_with_sharks; /* CPU difficulty + 1, 0 human */
extern s16 D_8010B9EA_swinging_with_sharks; /* CPU aims at a shark */
extern s16 D_8010B9EC_swinging_with_sharks; /* CPU delay */
extern s16 D_8010B9EE_swinging_with_sharks; /* CPU release angle */
extern SwShark D_8010B9F0_swinging_with_sharks[5];
extern s16 D_8010BAE0_swinging_with_sharks;
extern s16 D_8010BAE2_swinging_with_sharks;
extern s16 D_8010BAE4_swinging_with_sharks;
extern s16 D_8010BAE6_swinging_with_sharks;
extern f32 D_8010BAE8_swinging_with_sharks; /* sea scroll */
extern s16 D_8010BAEC_swinging_with_sharks;
extern s16 D_8010BAEE_swinging_with_sharks;
extern s16 D_8010BAF0_swinging_with_sharks[4]; /* Cheep Cheep models */
extern s16 D_8010BAF8_swinging_with_sharks[20]; /* ripple timers */
extern s16 D_8010BB20_swinging_with_sharks[20]; /* ripple models */
extern s16 D_8010BB48_swinging_with_sharks; /* boat angle */
extern s16 D_8010BB50_swinging_with_sharks; /* camera move frames */
extern Vec D_8010BB54_swinging_with_sharks; /* camera move: rotation to */
extern Vec D_8010BB60_swinging_with_sharks; /* centre to */
extern Vec D_8010BB6C_swinging_with_sharks; /* centre from */
extern Vec D_8010BB78_swinging_with_sharks; /* centre at reset */
extern Vec D_8010BB84_swinging_with_sharks; /* rotation from */
extern Vec D_8010BB90_swinging_with_sharks; /* debug camera rotation */
extern f32 D_8010BB9C_swinging_with_sharks; /* zoom at reset */
extern f32 D_8010BBA0_swinging_with_sharks; /* zoom from */
extern f32 D_8010BBA4_swinging_with_sharks; /* zoom to */
extern Vec D_8010BBA8_swinging_with_sharks; /* rotation at reset */
extern f32 D_8010BBB4_swinging_with_sharks; /* field of view */

#define MODELS D_8010B8E0_swinging_with_sharks
#define MOTS D_8010B948_swinging_with_sharks

const s16 D_8010B770_swinging_with_sharks[] = {
    0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000,
};

#ifdef NON_MATCHING
/* the CPU shark pick: retail computes (rand8() * 5) >> 8 into v0 and indexes through v1, not at */
void func_801059A0_swinging_with_sharks(void) {
    s32 i;

    omInitObjMan(0x14, 0xA);
    func_8004A208_main();
    func_800142A0_main(0x14);
    func_8001F38C_main(0, 0xFF, 0);
    D_800CD280_main = 1;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CRot.x = 334.0f;
    CRot.y = D_8010BBA8_swinging_with_sharks.z = 0.0f;
    CZoom = 2750.0f;
    Center.x = -698.0f;
    Center.y = 363.0f;
    Center.z = -112.9f;
    D_8010BBB4_swinging_with_sharks = 20.0f;
    D_8010BBA8_swinging_with_sharks = CRot;
    D_8010BB90_swinging_with_sharks = D_8010BBA8_swinging_with_sharks;
    D_8010BB9C_swinging_with_sharks = CZoom;
    D_8010BB78_swinging_with_sharks = Center;
    Hu3DCamSetPerspective(0, D_8010BBB4_swinging_with_sharks, 500.0f, 8000.0f);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x40, 0x40, 0x60);
    HmfLightDirSet(0, 92.0f, 79.0f, 22.0f);
    HmfLightStatSet(0, 1, 1);
    HmfLightColorSet(2, 0x64, 0xFF, 0xFF);
    HmfLightDirSet(2, -115.0f, 6.0f, -33.0f);
    HmfLightStatSet(2, 1, 1);
    omAddObj(0x2710, 0, 0, -1, func_801098C0_swinging_with_sharks);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    D_8010B9E0_swinging_with_sharks = 0;
    D_8010B9E2_swinging_with_sharks = 0;
    omAddObj(0x3E8, 0, 0, -1, func_80105FE4_swinging_with_sharks);
    omAddObj(0x3E8, 0, 0, -1, func_80106398_swinging_with_sharks);
    omAddObj(0x384, 0, 0, -1, func_801073F0_swinging_with_sharks);
    omAddObj(0x384, 0, 0, -1, func_80107954_swinging_with_sharks);
    omSetStatBit(omAddObj(0x384, 0, 0, -1, func_80108B4C_swinging_with_sharks), 0xA0);
    omAddObj(0x384, 0, 0, -1, func_801089A4_swinging_with_sharks);
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    D_8010B9D8_swinging_with_sharks = i;
    D_8010B9E8_swinging_with_sharks = GwPlayer[D_8010B9D8_swinging_with_sharks].stat & 1;
    GwPlayer[D_8010B9D8_swinging_with_sharks].bonusCoin = -1;
    D_8010B9DC_swinging_with_sharks = GwPlayer[i].chr;
    D_8010B9DA_swinging_with_sharks = GwPlayer[i].pad;
    func_8010979C_swinging_with_sharks(D_8010ACEC_swinging_with_sharks);
    if (D_8010B9E8_swinging_with_sharks != 0) {
        D_8010B9E8_swinging_with_sharks = GwPlayer[D_8010B9D8_swinging_with_sharks].cpu_difficulty + 1;
        D_8010B9EA_swinging_with_sharks = rand8() > D_8010B418_swinging_with_sharks[GwPlayer[D_8010B9D8_swinging_with_sharks].cpu_difficulty];
        D_8010B9EC_swinging_with_sharks = (rand8() & 0x1F) + 15;
        if (D_8010B9EA_swinging_with_sharks != 0) {
            D_8010B9EE_swinging_with_sharks =
                (HmfModelData[MODELS[3 + ((s32)((rand8() & 0xFF) * 5) >> 8)]].pos.x + 70.0f) / 1000.0f * 70.0f + 10.0f;
        }
    }
    func_80107384_swinging_with_sharks();
    func_801077C4_swinging_with_sharks();
    func_80108B24_swinging_with_sharks();
    func_8010AA68_swinging_with_sharks();
    func_80106334_swinging_with_sharks();
    D_8010ACE4_swinging_with_sharks = 0.0f;
    D_8010B9D0_swinging_with_sharks = 80.0f;
    D_8010B9DE_swinging_with_sharks = -1;
    func_80108C08_swinging_with_sharks(0.0f);
    func_80108DB0_swinging_with_sharks(&D_8010B9B8_swinging_with_sharks);
    D_8010B9E4_swinging_with_sharks = 0;
    func_8001FA68_main(MODELS[31]);
    func_8001C514_main(MODELS[31]);
    func_80045010_main(D_8010B770_swinging_with_sharks, 1);
    func_8010A41C_swinging_with_sharks();
    omAddPrcObj(func_80109950_swinging_with_sharks, 0x3F00, 0x2000, 0);
    omAddPrcObj(func_80109950_swinging_with_sharks, 0x3F00, 0x2000, 0);
    HuAudSeqPlay(0x44);
    WipeCreateIn(0xFF, 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801059A0_swinging_with_sharks);
#endif

void func_80105FE4_swinging_with_sharks(omObjData *obj) {
    switch (D_8010B9E0_swinging_with_sharks) {
    case 0:
        if (WipeStatGet() == 0) {
            if (D_8010B9E4_swinging_with_sharks == 0) {
                D_8010B9E6_swinging_with_sharks = HuAudFXPlay(0x4ED);
            }
            if (++D_8010B9E4_swinging_with_sharks == 120) {
                D_8010BAE0_swinging_with_sharks = GMesCreate(8);
                func_801088F0_swinging_with_sharks(334.0f, 0.0f, 0.0f, 54.0f, 435.0f, -148.0f, 4340.0f, 30);
            }
            if (D_8010B9E4_swinging_with_sharks > 120 && GMesStatGet() == 0) {
                GMesCreate(0x1A, 10, 160, 120);
                D_8010B9E2_swinging_with_sharks = 329;
                D_8010B9E4_swinging_with_sharks = 0;
                D_8010B9E0_swinging_with_sharks = 1;
            }
        }
        break;
    case 1:
        if (D_8010B9E2_swinging_with_sharks > 0) {
            D_8010B9E2_swinging_with_sharks--;
            func_8003F578_main(D_8010B9E2_swinging_with_sharks / 30);
            if (D_8010B9E2_swinging_with_sharks == 0) {
                func_8003F5C0_main();
                D_8010B9E4_swinging_with_sharks = 0;
            }
        }
        break;
    case 2:
    case 5:
        break;
    case 3:
        if (D_8010B9E4_swinging_with_sharks == 0) {
            GMesCreate(0x13);
            HuAudSeqFadeOut(120);
            D_8010B9E4_swinging_with_sharks++;
            D_8010BAE2_swinging_with_sharks = 0;
        }
        if (++D_8010BAE2_swinging_with_sharks == 30) {
            func_8004AEF0_main(D_8010B9E6_swinging_with_sharks, 30);
        }
        if (GMesStatGet() == 0) {
            D_8010B9E4_swinging_with_sharks++;
            if (D_8010B9DE_swinging_with_sharks == -1) {
                if (D_8010B9E4_swinging_with_sharks >= 16) {
                    GMesCreate(0x1D);
                    D_8010B9E4_swinging_with_sharks = 0;
                    D_8010B9E0_swinging_with_sharks = 4;
                    HuAudSeqPlay(0x6B);
                }
            } else if (D_8010B9E4_swinging_with_sharks >= 16) {
                GMesCreate(0x24);
                D_8010B9E4_swinging_with_sharks = 0;
                D_8010B9E0_swinging_with_sharks = 4;
                HuAudSeqPlay(0x68);
            }
        }
        break;
    case 4:
        if (++D_8010B9E4_swinging_with_sharks >= 136) {
            D_8010B9E4_swinging_with_sharks = 0;
            D_8010ACE1_swinging_with_sharks = 1;
            D_8010B9E0_swinging_with_sharks = 5;
        }
        break;
    }
    func_8010A0C0_swinging_with_sharks();
    func_8010A260_swinging_with_sharks();
    func_8010A4DC_swinging_with_sharks();
    func_8010AAA0_swinging_with_sharks();
}

void func_80106334_swinging_with_sharks(void) {
    func_8001F304_main(MODELS[32], MOTS[41]);
    func_8001C814_main(MODELS[32], 1, 1);
    func_8001C6A8_main(MODELS[32], 0.0f);
    func_8001FA68_main(MODELS[33]);
    func_8001C514_main(MODELS[33]);
}

#ifdef NON_MATCHING
/* float register allocation in the fall-time loop (0.0f and 4.0f swap f0/f6) */
void func_80106398_swinging_with_sharks(omObjData *obj) {
    Vec pos;
    f32 y;
    f32 vy;
    s16 n;
    s32 go;

    go = 0;
    func_80108DB0_swinging_with_sharks(&pos);
    Hu3DModelPosSet(MODELS[32], pos.x, pos.y, pos.z);
    Hu3DModelRotSet(MODELS[32], 0.0f, 90.0f, D_8010ACE4_swinging_with_sharks);
    if (D_8010ACE8_swinging_with_sharks < 180.0f) {
        func_8001C6A8_main(MODELS[32], D_8010ACE8_swinging_with_sharks / 12.0f);
    } else {
        func_8001C6A8_main(MODELS[32], (360.0f - D_8010ACE8_swinging_with_sharks) / 12.0f);
    }
    if (D_8010B9E0_swinging_with_sharks > 0) {
        if (D_8010B9E8_swinging_with_sharks != 0) {
            if (D_8010B9EC_swinging_with_sharks <= 0) {
                if (D_8010B9EA_swinging_with_sharks != 0) {
                    if (D_8010B9EE_swinging_with_sharks <= D_8010ACE4_swinging_with_sharks && D_8010ACE8_swinging_with_sharks < 90.0f) {
                        go = 1;
                    }
                } else if ((D_8010ACE8_swinging_with_sharks > 150.0f && D_8010ACE8_swinging_with_sharks < 180.0f) ||
                           D_8010ACE8_swinging_with_sharks > 345.0f) {
                    go = 1;
                }
            } else {
                D_8010B9EC_swinging_with_sharks--;
            }
        } else {
            go = D_800D5558_main[D_8010B9DA_swinging_with_sharks] & 0x8000;
        }
        if ((D_8010B9E2_swinging_with_sharks != 0 && go != 0) ||
            (D_8010B9E2_swinging_with_sharks == 0 &&
             ((D_8010ACE8_swinging_with_sharks > 150.0f && D_8010ACE8_swinging_with_sharks < 180.0f) ||
              D_8010ACE8_swinging_with_sharks > 345.0f))) {
            HuAudFXPlay(0x4E9);
            if (D_8010B9E2_swinging_with_sharks != 0) {
                func_8003F5C0_main();
            }
            vy = pos.y - D_8010B9B8_swinging_with_sharks.y + 10.0f;
            y = pos.y + vy;
            for (vy -= 4.0f, n = 0; !(y <= 0.0f); vy -= 4.0f) {
                n++;
                y += vy;
            }
            D_8010B9E0_swinging_with_sharks = 2;
            D_8010B9C4_swinging_with_sharks = pos;
            if (D_8010ACE4_swinging_with_sharks > 10.0f && D_8010ACE4_swinging_with_sharks <= 80.0f && D_8010ACE8_swinging_with_sharks <= 90.0f) {
                D_8010B9AC_swinging_with_sharks.x = ((D_8010ACE4_swinging_with_sharks - 10.0f) * 14.285714f - 170.0f - pos.x) / n;
            } else {
                D_8010B9AC_swinging_with_sharks.x = pos.x - D_8010B9B8_swinging_with_sharks.x;
            }
            D_8010B9AC_swinging_with_sharks.y = pos.y - D_8010B9B8_swinging_with_sharks.y;
            D_8010B9AC_swinging_with_sharks.z = 0.0f;
            D_8010B9AC_swinging_with_sharks.y += 10.0f;
            D_8010B9D0_swinging_with_sharks *= 1.1f;
            D_8010B9D4_swinging_with_sharks = D_8010ACE4_swinging_with_sharks;
            obj->work[0] = 0;
            func_8001C624_main(MODELS[32], MOTS[34], 0, 4, 0);
            obj->func = func_80106870_swinging_with_sharks;
        }
    }
    D_8010B9B8_swinging_with_sharks = pos;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80106398_swinging_with_sharks);
#endif

void func_80106870_swinging_with_sharks(omObjData *obj) {
    f32 x;
    s16 i;

    D_8010B9C4_swinging_with_sharks.x += D_8010B9AC_swinging_with_sharks.x;
    D_8010B9C4_swinging_with_sharks.y += D_8010B9AC_swinging_with_sharks.y;
    D_8010B9C4_swinging_with_sharks.z += D_8010B9AC_swinging_with_sharks.z;
    D_8010B9AC_swinging_with_sharks.y -= 4.0f;
    if (obj->work[0] < 6) {
        Hu3DModelRotSet(MODELS[32], 0.0f, 90.0f, cosdf(obj->work[0] * 18.0f) * D_8010B9D4_swinging_with_sharks);
        obj->work[0]++;
    }
    if (D_8010B9C4_swinging_with_sharks.y <= 0.0f) {
        CharFXPlay(0x70, D_8010B9DC_swinging_with_sharks);
        omVibrate(D_8010B9D8_swinging_with_sharks, 10, 0, 10);
        D_8010B9E0_swinging_with_sharks = 3;
        D_8010B9D4_swinging_with_sharks = 0.0f;
        func_8001C624_main(MODELS[32], MOTS[35], 0, 8, 2);
        func_8001C624_main(MODELS[47], MOTS[48], 0, 4, 2);
        Hu3DModelRotSet(MODELS[32], 0.0f, 90.0f, 0.0f);
        obj->work[0] = 0;
        func_8001C258_main(MODELS[29], 4, 0);
        Hu3DModelPosSet(MODELS[29], D_8010B9C4_swinging_with_sharks.x, 0.0f, D_8010B9C4_swinging_with_sharks.z);
        func_8001C92C_main(MODELS[29], 0.5f);
        Hu3DModelScaleSet(MODELS[29], 3.0f, 3.0f, 3.0f);
        func_8001C258_main(MODELS[30], 4, 0);
        Hu3DModelPosSet(MODELS[30], D_8010B9C4_swinging_with_sharks.x, -30.0f, D_8010B9C4_swinging_with_sharks.z + 50.0f);
        Hu3DModelScaleSet(MODELS[30], 2.0f, 2.0f, 2.0f);
        HuAudFXPlay(0x4EF);
        obj->func = func_80106D44_swinging_with_sharks;
    } else if (D_8010B9C4_swinging_with_sharks.y < 90.0f) {
        for (i = 0; i < 5; i++) {
            x = HmfModelData[MODELS[3 + i]].pos.x;
            if (x - 80.0f < D_8010B9C4_swinging_with_sharks.x && D_8010B9C4_swinging_with_sharks.x < x + 80.0f) {
                HuAudFXPlay(0x4EC);
                omVibrate(D_8010B9D8_swinging_with_sharks, 10, 0, 10);
                D_8010B9E0_swinging_with_sharks = 3;
                D_8010B9D4_swinging_with_sharks = 0.0f;
                if (D_8010B9C4_swinging_with_sharks.x < x - 40.0f) {
                    func_8001C624_main(MODELS[32], MOTS[36], 0, 8, 0);
                } else if (x + 40.0f < D_8010B9C4_swinging_with_sharks.x || D_8010B9AC_swinging_with_sharks.x > 35.0f) {
                    func_8001C624_main(MODELS[32], MOTS[37], 0, 4, 0);
                } else {
                    func_8001C814_main(MODELS[32], 4, 4);
                }
                Hu3DModelRotSet(MODELS[32], 0.0f, 100.0f, 0.0f);
                Hu3DModelPosSet(MODELS[32], D_8010B9C4_swinging_with_sharks.x, 50.0f, D_8010B9C4_swinging_with_sharks.z);
                D_8010B9DE_swinging_with_sharks = i;
                func_8001C258_main(MODELS[42], 4, 0);
                Hu3DModelPosSet(MODELS[42], D_8010B9C4_swinging_with_sharks.x, 50.0f, D_8010B9C4_swinging_with_sharks.z + 30.0f);
                HuAudFXPlay(0x4EF);
                obj->func = func_80107044_swinging_with_sharks;
                break;
            }
        }
    }
    Hu3DModelPosSet(MODELS[32], D_8010B9C4_swinging_with_sharks.x, D_8010B9C4_swinging_with_sharks.y, D_8010B9C4_swinging_with_sharks.z);
}

void func_80106D44_swinging_with_sharks(omObjData *obj) {
    f32 scale;
    s16 model;

    if (obj->work[0] == 8) {
        HuAudFXPlay(D_8010B9DC_swinging_with_sharks + 0x287);
    }
    if (obj->work[0] >= 9) {
        model = MODELS[31];
        func_8001C258_main(model, 4, 0);
        Hu3DModelPosSet(model, D_8010B9C4_swinging_with_sharks.x, 0.0f, D_8010B9C4_swinging_with_sharks.z);
        if (D_8010B428_swinging_with_sharks > 90) {
            if (HmfModelData[MODELS[32]].unk40 != 0.0f) {
                return;
            }
            D_8010B428_swinging_with_sharks = 0;
        }
        scale = sindf(D_8010B428_swinging_with_sharks % 90) + 0.5f;
        Hu3DModelScaleSet(model, scale, scale, scale);
        func_8001F9E4_main(model, (u32)(255.0f - D_8010B428_swinging_with_sharks * 2.8333333f));
        D_8010B428_swinging_with_sharks += 3;
    } else {
        D_8010B9C4_swinging_with_sharks.y = sindf(obj->work[0] * 18.0f) * D_8010B9AC_swinging_with_sharks.y;
        obj->work[0]++;
        Hu3DModelPosSet(MODELS[32], D_8010B9C4_swinging_with_sharks.x, D_8010B9C4_swinging_with_sharks.y, D_8010B9C4_swinging_with_sharks.z);
        HmfModelData[MODELS[32]].rot.y = 90.0f - obj->work[0] * 11.25f;
    }
}

#ifdef NON_MATCHING
/* register allocation: retail keeps the player model in s2 until the Hu3DModelPosSet call (one more saved register) */
void func_80107044_swinging_with_sharks(omObjData *obj) {
    HmfModel *player;
    s16 model;

    model = MODELS[32];
    player = &HmfModelData[model];

    if (player->unk02 == MOTS[37] && D_800CCF58_main[player->unk02].unk02 <= player->unk40) {
        func_8001C624_main(MODELS[32], MOTS[32], 0, 0x10, 2);
    }
    Hu3DModelPosSet(model, D_8010B9C4_swinging_with_sharks.x, HmfModelData[MODELS[3 + D_8010B9DE_swinging_with_sharks]].pos.y + 80.0f,
                    D_8010B9C4_swinging_with_sharks.z);
    if (++obj->work[0] >= 21) {
        obj->work[0] = 0;
        func_8001C624_main(MODELS[47], MOTS[49], 0, 4, 0);
        obj->func = func_801071A8_swinging_with_sharks;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80107044_swinging_with_sharks);
#endif

void func_801071A8_swinging_with_sharks(omObjData *obj) {
    HmfModel *shark;
    u16 model;

    model = MODELS[32];
    shark = &HmfModelData[MODELS[3 + D_8010B9DE_swinging_with_sharks]];
    D_8010B9C4_swinging_with_sharks.x = (shark->pos.x - D_8010B9C4_swinging_with_sharks.x) / 2.0f + D_8010B9C4_swinging_with_sharks.x;
    Hu3DModelPosSet(model, D_8010B9C4_swinging_with_sharks.x, shark->pos.y + 80.0f, D_8010B9C4_swinging_with_sharks.z);
    if (obj->work[0] == 0) {
        func_8001C624_main(model, MOTS[38], 0, 4, 2);
    }
    obj->work[0]++;
    if (obj->work[0] == 75) {
        func_8001C624_main(model, MOTS[39], 0, 4, 0);
        func_80045ED0_main((D_8010B420_swinging_with_sharks[D_8010B9DC_swinging_with_sharks] << 16) | 0x35);
    }
    if (obj->work[0] < 9) {
        HmfModelData[(s16)model].rot.y = 90.0f - obj->work[0] * 11.25f;
        if (obj->work[0] == 8) {
            func_8001C624_main(model, MOTS[32], 0, 8, 2);
        }
    }
}

void func_80107384_swinging_with_sharks(void) {
    func_8002367C_main(D_8010B860_swinging_with_sharks, ((SwPart *)func_8001D33C_main(MODELS[2], "rope"))->mtx);
    func_8002367C_main(D_8010B8A0_swinging_with_sharks, ((SwPart *)func_8001D33C_main(MODELS[2], "step"))->mtx);
    D_8010ACE8_swinging_with_sharks = 0.0f;
}

void func_801073F0_swinging_with_sharks(omObjData *obj) {
    switch (D_8010B42A_swinging_with_sharks) {
    case 0:
        if (D_8010ACE8_swinging_with_sharks == 0.0f) {
            D_8010B42C_swinging_with_sharks = HuAudFXPlay(0x4EA);
        }
        D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
        D_8010ACE8_swinging_with_sharks += 5.0f;
        if (D_8010ACE8_swinging_with_sharks > 360.0f) {
            D_8010ACE8_swinging_with_sharks -= 360.0f;
            D_8010B42A_swinging_with_sharks++;
        }
        break;
    case 1:
        D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * 180.0f;
        D_8010ACE8_swinging_with_sharks += 5.0f;
        if (D_8010ACE8_swinging_with_sharks > 90.0f) {
            D_8010B42A_swinging_with_sharks++;
            D_8010B9D0_swinging_with_sharks = 180.0f;
        }
        break;
    case 2:
        D_8010ACE4_swinging_with_sharks = -sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
        D_8010ACE8_swinging_with_sharks += 5.0f;
        D_8010B9D0_swinging_with_sharks -= 6.0f;
        if (D_8010ACE8_swinging_with_sharks > 180.0f) {
            D_8010B9D0_swinging_with_sharks = 80.0f;
            D_8010ACE8_swinging_with_sharks += 180.0f;
            obj->func = func_80107628_swinging_with_sharks;
        }
        break;
    }
    func_80108C08_swinging_with_sharks(D_8010ACE4_swinging_with_sharks);
}

void func_80107628_swinging_with_sharks(omObjData *obj) {
    D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
    D_8010ACE8_swinging_with_sharks += 5.0f;
    if (D_8010ACE8_swinging_with_sharks > 360.0f) {
        D_8010ACE8_swinging_with_sharks -= 360.0f;
    }
    func_80108C08_swinging_with_sharks(D_8010ACE4_swinging_with_sharks);
    if (D_8010B9E0_swinging_with_sharks == 2) {
        obj->func = func_801076DC_swinging_with_sharks;
    }
}

void func_801076DC_swinging_with_sharks(omObjData *obj) {
    if (D_8010B9D0_swinging_with_sharks > 0.0f) {
        D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
        D_8010ACE8_swinging_with_sharks += 5.0f;
        if (D_8010ACE8_swinging_with_sharks > 360.0f) {
            D_8010ACE8_swinging_with_sharks -= 360.0f;
        }
        D_8010B9D0_swinging_with_sharks -= 0.5f;
        if (D_8010B9D0_swinging_with_sharks <= 0.0f) {
            D_8010B9D0_swinging_with_sharks = 0.0f;
        }
        func_80108C08_swinging_with_sharks(D_8010ACE4_swinging_with_sharks);
    }
}

void func_801077C4_swinging_with_sharks(void) {
    SwShark *shark;
    s16 i;

    for (i = 0; i < 5; i++) {
        shark = &D_8010B9F0_swinging_with_sharks[i];
        shark->model = MODELS[3 + i];
        Hu3DModelPosGet(shark->model, &shark->base);
        shark->angle = rand8() & 0xF8;
        shark->timer = 0;
        shark->unk04 = 30;
        func_80032FF8_main(HmfAnimRead(HmfModelData[MODELS[8 + i]].hmf, 0x21002C, "m259_30_000_DEF"), D_800A11D0_main[i]);
        func_8001C448_main(MODELS[8 + i]);
        func_8001C514_main(MODELS[8 + i]);
        shark->ripple = rand8() & 0x3F;
        func_8001FA68_main(MODELS[18 + i]);
        func_8001C514_main(MODELS[18 + i]);
    }
    D_8010BAE6_swinging_with_sharks = func_8000CED8_main(0xB0004, 0x2A9);
    func_800138EC_main(D_8010BAE6_swinging_with_sharks, 1, 0);
}

#ifdef NON_MATCHING
/* register allocation only (the landed-shark index, its HmfModel and &D_8010B8F0 permute s3/s4/s5) */
void func_80107954_swinging_with_sharks(omObjData *obj) {
    s16 cur;
    SwShark *shark;
    HmfModel *m;
    f32 dz;
    f32 scale;
    s16 i;
    u16 model;

    if (D_8010B9DE_swinging_with_sharks != -1) {
        cur = D_8010B9DE_swinging_with_sharks;
        shark = &D_8010B9F0_swinging_with_sharks[D_8010B9DE_swinging_with_sharks];
        m = &HmfModelData[shark->model];
        if (shark->timer < 50) {
            shark->pos.y = sindf(shark->timer * 30) * shark->unk04 + shark->base.y - 50.0f;
            Hu3DModelPosSet(shark->model, shark->pos.x, shark->pos.y, shark->pos.z);
            HmfModelData[shark->model].rot.z = 0.0f;
            Hu3DModelPosSet(MODELS[8 + cur], m->pos.x, m->pos.y, m->pos.z - ((cur & 1) * 10 + 80));
            HmfModelData[MODELS[8 + cur]].rot.z = 0.0f;
            Hu3DModelPosSet(MODELS[13 + cur], m->pos.x, m->pos.y, m->pos.z - ((cur & 1) * 10 + 80));
            HmfModelData[MODELS[13 + cur]].rot.z = 0.0f;
            shark->unk04--;
            if (++shark->timer == 50) {
                shark->angle = 500.0f;
                func_8001C258_main(MODELS[43], 4, 0);
                Hu3DModelRotSet(MODELS[43], CRot.x, CRot.y, CRot.z);
                Hu3DModelScaleSet(MODELS[43], 4.0f, 4.0f, 4.0f);
                Hu3DModelPosSet(MODELS[43], m->pos.x, m->pos.y + 300.0f, m->pos.z);
            }
        } else {
            shark->pos.y = sindf(shark->angle) * 5.0f + shark->base.y - 50.0f;
            shark->angle += 10.0f;
            if (shark->angle > 1440.0f) {
                shark->angle -= 1440.0f;
            }
            Hu3DModelPosSet(shark->model, shark->pos.x, shark->pos.y, shark->pos.z);
            if (shark->timer > 60) {
                func_8001C258_main(MODELS[8 + cur], 4, 4);
                func_8001C258_main(MODELS[13 + cur], 4, 4);
            } else {
                shark->timer++;
            }
            if (shark->timer == 60) {
                omAddObj(0x384, 0, 0, -1, func_80108474_swinging_with_sharks);
            }
            Hu3DModelPosSet(MODELS[8 + cur], m->pos.x, m->pos.y, m->pos.z - ((cur & 1) * 10 + 80));
            Hu3DModelPosSet(MODELS[13 + cur], m->pos.x, m->pos.y, m->pos.z - ((cur & 1) * 10 + 80));
        }
    }
    if (D_8010B9E0_swinging_with_sharks < 3) {
        for (i = 0; i < 5; i++) {
            if (i != D_8010B9DE_swinging_with_sharks) {
                shark = &D_8010B9F0_swinging_with_sharks[i];
                shark->pos.x = sindf(shark->angle / 4.0f) * 50.0f + shark->base.x;
                shark->pos.y = sindf(shark->angle) * 10.0f + shark->base.y;
                shark->pos.z = shark->base.z;
                shark->angle += 10.0f;
                if (shark->angle > 1440.0f) {
                    shark->angle -= 1440.0f;
                }
                Hu3DModelPosSet(shark->model, shark->pos.x, shark->pos.y, shark->pos.z);
                HmfModelData[shark->model].rot.z = sindf(shark->angle / 2.0f) * 5.0f;
                Hu3DModelPosSet(MODELS[8 + i], shark->pos.x, shark->pos.y, shark->pos.z - ((i & 1) * 10 + 80));
                HmfModelData[MODELS[8 + i]].rot.z = sindf(shark->angle / 2.0f) * 5.0f;
                Hu3DModelPosSet(MODELS[13 + i], shark->pos.x, shark->pos.y, shark->pos.z - ((i & 1) * 10 + 80));
                HmfModelData[MODELS[13 + i]].rot.z = sindf(shark->angle / 2.0f) * 5.0f;
            }
        }
    } else {
        for (i = 0; i < 5; i++) {
            shark = &D_8010B9F0_swinging_with_sharks[i];
            if (i != D_8010B9DE_swinging_with_sharks && !(shark->pos.y < -1500.0f)) {
                if (shark->pos.y > -80.0f) {
                    shark->pos.y -= 4.0f;
                    shark->angle = 0.0f;
                    shark->unk04 = (rand8() & 0xF) - 8;
                    HmfModelData[shark->model].rot.z = 0.0f;
                    scale = shark->pos.y * 0.0125f + 1.0f;
                    Hu3DModelScaleSet(MODELS[13 + i], scale, scale, scale);
                    Hu3DModelScaleSet(MODELS[8 + i], scale, scale, scale);
                    dz = (i & 1) * 10 + 80;
                    Hu3DModelPosSet(MODELS[13 + i], shark->pos.x, 0.0f, shark->pos.z - dz);
                    HmfModelData[MODELS[13 + i]].rot.z = 0.0f;
                    Hu3DModelPosSet(MODELS[8 + i], shark->pos.x, shark->pos.y, shark->pos.z - dz);
                    HmfModelData[MODELS[8 + i]].rot.z = 0.0f;
                    if (shark->pos.y <= -80.0f) {
                        func_8001C258_main(MODELS[23 + i], 4, 0);
                        Hu3DModelPosSet(MODELS[23 + i], shark->pos.x, 0.0f, shark->pos.z);
                        func_8001C92C_main(MODELS[23 + i], 1.0f);
                        Hu3DModelScaleSet(MODELS[23 + i], 1.0f, 1.0f, 1.0f);
                    }
                } else {
                    func_8001C258_main(MODELS[8 + i], 4, 4);
                    func_8001C258_main(MODELS[13 + i], 4, 4);
                    shark->pos.y -= 8.0f;
                    shark->angle = shark->unk04 / 10.0f + shark->angle;
                    HmfModelData[shark->model].rot.z = shark->angle;
                }
                Hu3DModelPosSet(shark->model, shark->pos.x, shark->pos.y, shark->pos.z);
            }
        }
    }
    for (i = 0; i < 5; i++) {
        shark = &D_8010B9F0_swinging_with_sharks[i];
        model = MODELS[18 + i];
        if (shark->ripple <= 90) {
            Hu3DModelPosSet(model, shark->pos.x, 0.0f, shark->pos.z);
            scale = sindf(shark->ripple % 90) + 0.8f;
            Hu3DModelScaleSet(model, scale, scale, scale);
            func_8001F9E4_main(model, (u32)(255.0f - shark->ripple * 2.8333333f));
            shark->ripple += 2;
            if (shark->ripple > 90) {
                if (shark->pos.y < -50.0f && D_8010B9DE_swinging_with_sharks != i) {
                    shark->ripple = 90;
                } else {
                    shark->ripple = 0;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80107954_swinging_with_sharks);
#endif

void func_80108474_swinging_with_sharks(omObjData *obj) {
    HmfModel *shark;
    s16 model;

    shark = &HmfModelData[MODELS[3 + D_8010B9DE_swinging_with_sharks]];
    D_8010BAE4_swinging_with_sharks = SprModelRead(D_8010B430_swinging_with_sharks[D_800A11D0_main[D_8010B9DE_swinging_with_sharks]], 0xA4, 0x10);
    model = D_800CBB60_main[D_8010BAE4_swinging_with_sharks].model;
    Hu3DModelScaleSet(model, 5.0f, 5.0f, 5.0f);
    Hu3DModelPosSet(model, shark->pos.x, 200.0f, shark->pos.z - 80.0f);
    func_80014850_main(D_8010BAE4_swinging_with_sharks);
    obj->work[0] = 0;
    obj->work[1] = 0;
    func_800138EC_main(D_8010BAE6_swinging_with_sharks, 1, 1);
    func_8000CD00_main(D_8010BAE6_swinging_with_sharks, 8.0f, 20.0f, 10.0f);
    func_8000D018_main(D_8010BAE6_swinging_with_sharks, 150.0f);
    func_8000CFA4_main(D_8010BAE6_swinging_with_sharks, shark->pos.x, 200.0f, shark->pos.z - 80.0f);
    HuAudFXPlay(0x4EE);
    obj->func = func_801085F4_swinging_with_sharks;
}

void func_801085F4_swinging_with_sharks(omObjData *obj) {
    HmfModel *shark;
    HmfModel *prize;
    s16 model;

    shark = &HmfModelData[MODELS[3 + D_8010B9DE_swinging_with_sharks]];
    model = D_800CBB60_main[D_8010BAE4_swinging_with_sharks].model;
    prize = &HmfModelData[model];
    switch (obj->work[0]) {
    case 0:
        Hu3DModelPosSet(model, shark->pos.x, sindf(obj->work[1] * 9.0f) * 200.0f + 200.0f,
                        shark->pos.z - (80.0f - sindf(obj->work[1] * 9.0f) * 80.0f));
        func_8000CFA4_main(D_8010BAE6_swinging_with_sharks, prize->pos.x, prize->pos.y - 50.0f, prize->pos.z);
        if (++obj->work[1] > 10) {
            GwPlayer[D_8010B9D8_swinging_with_sharks].bonusCoin = D_800A11D0_main[D_8010B9DE_swinging_with_sharks];
            obj->work[0] = 1;
            obj->work[1] = 0;
            func_801088F0_swinging_with_sharks(334.0f, 0.0f, 0.0f, shark->pos.x, 300.0f, shark->pos.z, 2500.0f, 20);
        }
        break;
    case 1:
        HmfModelData[model].pos.y = sindf(obj->work[1]) * 20.0f + 400.0f;
        func_8000CFA4_main(D_8010BAE6_swinging_with_sharks, prize->pos.x, prize->pos.y - 50.0f, prize->pos.z);
        obj->work[1] += 10;
        break;
    }
}

void func_801088F0_swinging_with_sharks(f32 rx, f32 ry, f32 rz, f32 cx, f32 cy, f32 cz, f32 zoom, u16 frames) {
    D_8010BB84_swinging_with_sharks = CRot;
    D_8010BB6C_swinging_with_sharks = Center;
    D_8010BBA0_swinging_with_sharks = CZoom;
    D_8010BB54_swinging_with_sharks.x = rx;
    D_8010BB54_swinging_with_sharks.y = ry;
    D_8010BB54_swinging_with_sharks.z = rz;
    D_8010BB60_swinging_with_sharks.x = cx;
    D_8010BB60_swinging_with_sharks.y = cy;
    D_8010BB60_swinging_with_sharks.z = cz;
    D_8010BBA4_swinging_with_sharks = zoom;
    D_8010BB50_swinging_with_sharks = frames;
    D_8010B480_swinging_with_sharks = frames;
}

void func_801089A4_swinging_with_sharks(omObjData *obj) {
    f32 t;

    if (D_8010B480_swinging_with_sharks != 0) {
        D_8010B480_swinging_with_sharks--;
        t = sindf((1.0f - (f32)D_8010B480_swinging_with_sharks / D_8010BB50_swinging_with_sharks) * 90.0f);
        CRot.x = (-D_8010BB84_swinging_with_sharks.x + D_8010BB54_swinging_with_sharks.x) * t + D_8010BB84_swinging_with_sharks.x;
        CRot.y = (-D_8010BB84_swinging_with_sharks.y + D_8010BB54_swinging_with_sharks.y) * t + D_8010BB84_swinging_with_sharks.y;
        CRot.z = (-D_8010BB84_swinging_with_sharks.z + D_8010BB54_swinging_with_sharks.z) * t + D_8010BB84_swinging_with_sharks.z;
        Center.x = (-D_8010BB6C_swinging_with_sharks.x + D_8010BB60_swinging_with_sharks.x) * t + D_8010BB6C_swinging_with_sharks.x;
        Center.y = (-D_8010BB6C_swinging_with_sharks.y + D_8010BB60_swinging_with_sharks.y) * t + D_8010BB6C_swinging_with_sharks.y;
        Center.z = (-D_8010BB6C_swinging_with_sharks.z + D_8010BB60_swinging_with_sharks.z) * t + D_8010BB6C_swinging_with_sharks.z;
        CZoom = (-D_8010BBA0_swinging_with_sharks + D_8010BBA4_swinging_with_sharks) * t + D_8010BBA0_swinging_with_sharks;
    }
}

void func_80108B24_swinging_with_sharks(void) {
    func_8001C954_main(MODELS[0]);
    D_8010BAE8_swinging_with_sharks = 0.0f;
}

void func_80108B4C_swinging_with_sharks(omObjData *obj) {
    func_8001E888_main(MODELS[0], 0.0f, -D_8010BAE8_swinging_with_sharks, 32, 32, "sea", 0);
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010BAE8_swinging_with_sharks += 0.3f;
        if (D_8010BAE8_swinging_with_sharks > 32.0f) {
            D_8010BAE8_swinging_with_sharks = 0.0f;
        }
    }
}

void func_80108C08_swinging_with_sharks(f32 angle) {
    SwPart *rope;
    SwPart *step;
    f32 a;
    s32 deg;

    if (D_8010B42C_swinging_with_sharks != -1) {
        deg = (s32)(angle + 360.0f) % 360;
        if (deg > 180) {
            deg = 360 - deg;
        }
        a = deg;
        HuAudFXPitchSet(D_8010B42C_swinging_with_sharks, (s16)(a * 6.6666665f));
        func_8004AAD0_main(D_8010B42C_swinging_with_sharks, 127.0f - a * 0.35f);
    }
    rope = func_8001D33C_main(MODELS[2], "rope");
    func_8002367C_main(rope->mtx, D_8010B860_swinging_with_sharks);
    func_80108E50_swinging_with_sharks(rope->mtx, angle);
    step = func_8001D33C_main(MODELS[2], "step");
    func_8002367C_main(step->mtx, rope->mtx);
    func_80017C10_main((Mtx *)step->mtx, step->unk08, step->unk0C, step->unk10);
}

void func_80108DB0_swinging_with_sharks(Vec *out) {
    func_80108F20_swinging_with_sharks(MODELS[2], out, ((SwPart *)func_8001D33C_main(MODELS[2], "step"))->mtx);
}

void func_80108E00_swinging_with_sharks(Vec *out) {
    func_80108F20_swinging_with_sharks(MODELS[2], out, ((SwPart *)func_8001D33C_main(MODELS[2], "rope"))->mtx);
}

void func_80108E50_swinging_with_sharks(HuMtx4F mtx, f32 angle) {
    s32 i;
    f32 s, c;
    f32 vec[4];

    vec[0] = angle * D_8010B484_swinging_with_sharks;
    s = sinf(vec[0]);
    c = cosf(vec[0]);

    for (i = 0; i < 3; i++) {
        vec[i] = mtx[0][i];
    }

    for (i = 0; i < 3; i++) {
        mtx[0][i] = (c * vec[i]) + (s * mtx[1][i]);
        mtx[1][i] = (-vec[i] * s) + (c * mtx[1][i]);
    }
}

void func_80108F20_swinging_with_sharks(s16 model, Vec *out, HuMtx4F mtx) {
    f32 local[4][4];
    f32 world[4][4];
    HmfModel *m;

    m = &HmfModelData[model];
    func_80088800_main(local, m->pos.x, m->pos.y, m->pos.z);
    func_80017D24_main(local, m->rot.x, m->rot.y, m->rot.z);
    func_80017CD0_main(local, m->scale.x, m->scale.y, m->scale.z);
    func_80018044_main(mtx, local, world);
    out->x = world[0][0] + world[1][0] + world[2][0] + world[3][0];
    out->y = world[0][1] + world[1][1] + world[2][1] + world[3][1];
    out->z = world[0][2] + world[1][2] + world[2][2] + world[3][2];
}

#ifdef NON_MATCHING
/* sldebug's func_80106254_sldebug plus field-of-view keys; the same residue as that twin: float register
   allocation (rx and speed swap f22/f24) and retail loads &Center into s0 inside the 0x800/0x400 branches */
void func_80109020_swinging_with_sharks(omObjData *obj) {
    char buf[256];
    f32 rx;
    f32 ry;
    f32 speed;
    f32 dx;
    f32 dz;
    f32 inv;

    if (D_800D5558_main[0] & 0x10) {
        D_8010ACE0_swinging_with_sharks ^= 1;
    }
    if (D_800CDA7C_main[0] & 0x1000) {
        func_801096AC_swinging_with_sharks();
    }
    if (D_800CDA7C_main[0] & 8) {
        CZoom = (D_800CDA7C_main[0] & 0x2000) ? CZoom + 30.0f : CZoom + 10.0f;
    }
    if ((D_800CDA7C_main[0] & 4) && CZoom - 10.0f != 0.0f) {
        CZoom = (D_800CDA7C_main[0] & 0x2000) ? CZoom - 30.0f : CZoom - 10.0f;
    }
    if (D_800CDA7C_main[0] & 2) {
        D_8010BBB4_swinging_with_sharks += 1.0f;
    }
    if (D_800CDA7C_main[0] & 1) {
        D_8010BBB4_swinging_with_sharks -= 1.0f;
    }
    Hu3DCamSetPerspective(0, D_8010BBB4_swinging_with_sharks, 500.0f, 8000.0f);
    rx = D_8010BB90_swinging_with_sharks.x;
    ry = D_8010BB90_swinging_with_sharks.y;
    if (D_800CDA7C_main[0] & 0x2000) {
        speed = 5.0f;
    } else {
        speed = 2.0f;
    }
    ry += (-D_800CBB6E_main[0] / 30) * speed;
    if (ry >= 360.0f) {
        ry -= 360.0f;
    } else if (ry < 0.0f) {
        ry += 360.0f;
    }
    D_8010BB90_swinging_with_sharks.y = ry;
    rx += (s8)(D_800D20A1_main[0] / 30) * speed;
    if (rx >= 360.0f) {
        rx -= 360.0f;
    } else if (rx < 0.0f) {
        rx += 360.0f;
    }
    D_8010BB90_swinging_with_sharks.x = rx;
    CRot.x = (s16)D_8010BB90_swinging_with_sharks.x;
    CRot.y = (s16)D_8010BB90_swinging_with_sharks.y;
    if (D_800CDA7C_main[0] & 0x2000) {
        speed = 10.0f;
    } else {
        speed = 2.0f;
    }
    if (D_800CDA7C_main[0] & 0x800) {
        dx = sindf(ry) * sindf(rx);
        speed = -speed;
        Center.x += dx * speed;
        Center.y += cosdf(rx) * speed;
        Center.z += cosdf(ry) * sindf(rx) * speed;
    } else if (D_800CDA7C_main[0] & 0x400) {
        dx = sindf(ry) * sindf(rx);
        Center.x += dx * speed;
        Center.y += cosdf(rx) * speed;
        Center.z += cosdf(ry) * sindf(rx) * speed;
    } else if (D_800CDA7C_main[0] & 0x200) {
        dx = gCameraList->pos.z - Center.z;
        dz = -(gCameraList->pos.x - Center.x);
        inv = 1.0f / HuSqrtf(dx * dx + dz * dz);
        Center.x += dx * inv * speed;
        Center.y += 0.0f;
        Center.z += dz * inv * speed;
    } else if (D_800CDA7C_main[0] & 0x100) {
        dx = -(gCameraList->pos.z - Center.z);
        dz = gCameraList->pos.x - Center.x;
        inv = 1.0f / HuSqrtf(dx * dx + dz * dz);
        Center.x += dx * inv * speed;
        Center.y += 0.0f;
        Center.z += dz * inv * speed;
    }
    if (D_8010ACE0_swinging_with_sharks != 0) {
        sprintf(buf, "CROT %4.1f,%4.1f,%4.1f", CRot.x, CRot.y, CRot.z);
        print8(32, 180, buf);
        sprintf(buf, "INT %4.1f,%4.1f,%4.1f", Center.x, Center.y, Center.z);
        print8(32, 190, buf);
        sprintf(buf, "CZOOM %4.1f  FOVY %4.1f", CZoom, D_8010BBB4_swinging_with_sharks);
        print8(32, 200, buf);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109020_swinging_with_sharks);
#endif

void func_801096AC_swinging_with_sharks(void) {
    CRot = D_8010BBA8_swinging_with_sharks;
    D_8010BB90_swinging_with_sharks = CRot;
    CZoom = D_8010BB9C_swinging_with_sharks;
    Center = D_8010BB78_swinging_with_sharks;
}

void func_80109730_swinging_with_sharks(SwModelDef *defs, s16 idx, s16 model) {
    SwModelDef *def = &defs[idx];

    Hu3DModelPosSet(model, def->pos.x, def->pos.y, def->pos.z);
    Hu3DModelRotSet(model, def->rot.x, def->rot.y, def->rot.z);
}

void func_8010979C_swinging_with_sharks(SwModelDef *defs) {
    SwModelDef *def = defs;
    s16 i;
    s16 model;

    for (i = 0; def->dir != -1; def++, i++) {
        if ((def->dir & 0xFFFF0000) == 0xFFFF0000) {
            def->dir = func_80017BB8_main(D_8010B9DC_swinging_with_sharks, def->dir);
        }
        MODELS[i] = model = func_8000B108_main(def->dir, def->file | 0x288);
        func_80109730_swinging_with_sharks(defs, i, model);
        if ((MOTS[i] = HmfModelData[model].unk02) != -1) {
            func_8001C814_main(model, -1, def->motion);
        }
    }
}

void func_801098C0_swinging_with_sharks(omObjData *obj) {
    if (D_8010ACE1_swinging_with_sharks != 0 || D_800D530C_main != 0) {
        WipeCreateOut(0, 20);
        obj->func = func_80109924_swinging_with_sharks;
        HuAudSeqFadeOut(0x3C);
        func_8004AB0C_main(30);
    }
}

void func_80109924_swinging_with_sharks(omObjData *obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80109950_swinging_with_sharks(void) {
    f32 total;
    s16 idx;
    s16 path;
    u16 model;

    if (D_8010B768_swinging_with_sharks == 0) {
        model = D_8010BAEC_swinging_with_sharks = func_8000B108_main(0xA0154, 0x299);
        D_8010BAEE_swinging_with_sharks = func_8000B13C_main(0xA0155);
    } else {
        model = Hu3DModelLink(D_8010BAEC_swinging_with_sharks);
    }
    func_8001C5B4_main(model, D_8010BAEE_swinging_with_sharks);
    idx = D_8010B768_swinging_with_sharks++;
    D_8010BAF0_swinging_with_sharks[idx] = model;
    path = idx % 2;
    func_8001C814_main(model, 2, 2);
    func_8001C6A8_main((s16)model, idx * 10);
    Hu3DModelPosSet(model, 0.0f, -100.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 90.0f, 0.0f);
    total = func_80109B04_swinging_with_sharks(D_8010B760_swinging_with_sharks[path], 20.0f);
    while (TRUE) {
        func_80109C90_swinging_with_sharks(D_8010B760_swinging_with_sharks[path], model, total);
        HuPrcVSleep();
    }
}

f32 func_80109B04_swinging_with_sharks(SwPathPt *path, f32 speed) {
    SwPathPt *prev;
    SwPathPt *p;
    f32 total;
    f32 dx, dy, dz;
    f32 d;
    s16 i;

    prev = NULL;
    total = 0.0f;
    p = path;
    for (i = 0; p->x != 0.0f || p->y != 0.0f || p->z != 0.0f; i++, p = &path[i]) {
        if (i > 0) {
            dx = prev->x - p->x;
            dy = prev->y - p->y;
            dz = prev->z - p->z;
            d = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (d == 0.0f) {
                d = speed * 10.0f;
            }
            total += d / speed;
            p->time = total;
        }
        prev = p;
    }
    return total;
}

#ifdef NON_MATCHING
/* scheduling: the 10.0f for end, path + i operand order, HmfModelData reloaded after the sindf products */
void func_80109C90_swinging_with_sharks(SwPathPt *path, s16 model, f32 total) {
    f32 x[4];
    f32 t[4];
    Vec pos;
    SwPathPt *p;
    f32 nx, ny, nz;
    f32 end;
    f32 a;
    s16 n;
    s16 frame;
    s16 i;

    n = 0;
    end = total - 10.0f;
    while (TRUE) {
        i = 1;
        for (frame = 10; frame < end; frame++) {
            if (frame > path[i + 1].time) {
                i++;
            }
            Hu3DModelPosGet(model, &pos);
            p = path + i;
            t[0] = p[-1].time;
            t[1] = p[0].time;
            t[2] = p[1].time;
            t[3] = p[2].time;
            x[0] = p[-1].x;
            x[1] = p[0].x;
            x[2] = p[1].x;
            x[3] = p[2].x;
            nx = func_80018ACC_main(x, t, frame);
            x[0] = p[-1].y;
            x[1] = p[0].y;
            x[2] = p[1].y;
            x[3] = p[2].y;
            ny = func_80018ACC_main(x, t, frame);
            x[0] = p[-1].z;
            x[1] = p[0].z;
            x[2] = p[1].z;
            x[3] = p[2].z;
            nz = func_80018ACC_main(x, t, frame);
            Hu3DModelPosSet(model, nx, ny, nz);
            nx -= pos.x;
            nz -= pos.z;
            if (nz != 0.0f || nx != 0.0f) {
                HmfModelData[model].rot.y = atan2df(nx, nz);
            }
            if (D_8010B9E0_swinging_with_sharks >= 3) {
                if (D_8010B9DE_swinging_with_sharks == -1) {
                    if (n < 20) {
                        n++;
                        ny = HmfModelData[model].pos.y;
                        a = n * 4.5f;
                        HmfModelData[model].pos.y = ny + sindf(a) * (-30.0f - ny);
                        HmfModelData[model].rot.x = sindf(a) * -30.0f;
                    } else {
                        HmfModelData[model].pos.y = -30.0f;
                        HmfModelData[model].rot.x = -30.0f;
                    }
                } else {
                    HmfModelData[model].pos.y -= n * 10;
                    n++;
                }
            }
            HuPrcVSleep();
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109C90_swinging_with_sharks);
#endif

#ifdef NON_MATCHING
/* retail frame is 8 bytes larger and keeps the head model in s2 re-sign-extended (sll/sra) after the branch */
void func_8010A0C0_swinging_with_sharks(void) {
    HmfModel *player;
    HmfModel *m;
    SwPart *part;
    f32 dy, dz;
    f32 ry;
    s32 model;

    model = MODELS[47];
    if (HmfModelData[model].unk02 != MOTS[47]) {
        func_8002FDCC_main(model, HmfModelData[model].unk02, "c162_000-atama", 0x4C, 0x46);
        return;
    }
    player = &HmfModelData[MODELS[32]];
    m = &HmfModelData[(s16)model];
    dy = player->pos.y - m->pos.y;
    dz = player->pos.z - m->pos.z;
    ry = atan2df(player->pos.x - m->pos.x, dz);
    func_8002FD8C_main((s16)model, HmfModelData[(s16)model].unk02, "c162_000-atama", 0x4C, 0x46);
    part = func_8001D33C_main((s16)model, "c162_000-atama");
    part->unk38 = part->unk14 = ry - m->rot.y;
    func_8002FD8C_main((s16)model, HmfModelData[(s16)model].unk02, "c162_000-atama", 0x4C, 0x45);
    part->unk34 = part->unk10 = -atan2df(dy, dz);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A0C0_swinging_with_sharks);
#endif

#ifdef NON_MATCHING
/* register allocation: model/m swap s1/s2, and the light products use f2/f6 instead of f6/f0 */
void func_8010A260_swinging_with_sharks(void) {
    HmfModel *m;
    f32 len;
    f32 lx, ly, lz;
    f32 k;
    s16 alpha;
    u16 model;

    model = MODELS[33];
    m = &HmfModelData[MODELS[32]];
    if (m->pos.y < 90.0f) {
        alpha = (m->pos.y - 40.0f) / 50.0f * 102.0f;
        if (alpha <= 0) {
            alpha = 0;
            func_8001C258_main(model, 4, 4);
        }
        func_8001F9E4_main(model, alpha);
    } else {
        func_8001C258_main(model, 4, 0);
        func_8001F9E4_main(model, 0x66);
    }
    /* the shadow falls along a light from (-1.3, -1, -1.3) */
    len = HuSqrtf(4.3799996f);
    lz = -1.3f / len;
    ly = -1.0f / len;
    lx = -1.3f / len;
    k = 1.0f / ly;
    if (k < 0.0f) {
        k = -k;
    }
    lz *= k;
    lx *= k;
    Hu3DModelPosSet(model, lx * m->pos.y + m->pos.x, 0.0f, lz * m->pos.y + m->pos.z);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A260_swinging_with_sharks);
#endif

void func_8010A41C_swinging_with_sharks(void) {
    s16 i;

    func_8001FA68_main(MODELS[46]);
    func_8001C514_main(MODELS[46]);
    for (i = 0; i < 20; i++) {
        D_8010BB20_swinging_with_sharks[i] = func_8000B108_main(0xB0031, 0xA8C);
        D_8010BAF8_swinging_with_sharks[i] = 90;
        func_8001FA68_main(D_8010BB20_swinging_with_sharks[i]);
        func_8001C514_main(D_8010BB20_swinging_with_sharks[i]);
    }
}

void func_8010A4DC_swinging_with_sharks(void) {
    HmfModel *m;
    f32 scale;
    s16 i;
    s16 j;
    u16 model;

    for (i = 0; i < 2; i++) {
        if (((D_8010B76A_swinging_with_sharks + i * 2) & 7) == 0) {
            m = &HmfModelData[D_8010BAF0_swinging_with_sharks[i]];
            if (!(m->pos.y < -100.0f)) {
                for (j = 0; j < 20; j++) {
                    if (D_8010BAF8_swinging_with_sharks[j] >= 90) {
                        D_8010BAF8_swinging_with_sharks[j] = 0;
                        Hu3DModelPosSet(D_8010BB20_swinging_with_sharks[j], m->pos.x, 0.0f, m->pos.z);
                        Hu3DModelRotSet(D_8010BB20_swinging_with_sharks[j], 0.0f, m->rot.y, 0.0f);
                        func_8001C258_main(D_8010BB20_swinging_with_sharks[j], 4, 0);
                        break;
                    }
                }
            }
        }
    }
    model = MODELS[46];
    scale = sindf(D_8010B76A_swinging_with_sharks % 90) * 1.5f + 0.5f;
    Hu3DModelScaleSet(model, scale, scale, scale);
    func_8001F9E4_main(model, (u32)(255.0f - D_8010B76A_swinging_with_sharks * 2.8333333f));
    D_8010B76A_swinging_with_sharks += 2;
    if (D_8010B9E0_swinging_with_sharks >= 3 && HmfModelData[MODELS[47]].unk02 == MOTS[49]) {
        if (D_8010B76A_swinging_with_sharks > 90) {
            func_8001C258_main(model, 4, 4);
        }
        if ((D_8010B76A_swinging_with_sharks & 0xF) == 0) {
            m = &HmfModelData[MODELS[44]];
            for (j = 0; j < 20; j++) {
                if (D_8010BAF8_swinging_with_sharks[j] >= 90) {
                    D_8010BAF8_swinging_with_sharks[j] = 0;
                    Hu3DModelPosSet(D_8010BB20_swinging_with_sharks[j], m->pos.x, 0.0f, m->pos.z);
                    Hu3DModelRotSet(D_8010BB20_swinging_with_sharks[j], 0.0f, m->rot.y, 0.0f);
                    func_8001C258_main(D_8010BB20_swinging_with_sharks[j], 4, 0);
                    break;
                }
            }
        }
    }
    if (D_8010B76A_swinging_with_sharks > 90) {
        D_8010B76A_swinging_with_sharks = 0;
    }
    for (i = 0; i < 20; i++) {
        if (D_8010BAF8_swinging_with_sharks[i] >= 90) {
            func_8001C258_main(D_8010BB20_swinging_with_sharks[i], 4, 4);
        } else {
            scale = sindf(D_8010BAF8_swinging_with_sharks[i] % 90) * 1.5f;
            Hu3DModelScaleSet(D_8010BB20_swinging_with_sharks[i], scale, scale, scale);
            func_8001F9E4_main(D_8010BB20_swinging_with_sharks[i], (u32)(128.0f - D_8010BAF8_swinging_with_sharks[i] * 1.4222223f));
            D_8010BAF8_swinging_with_sharks[i] += 2;
        }
    }
}

void func_8010AA68_swinging_with_sharks(void) {
    D_8010BB48_swinging_with_sharks = HmfModelData[MODELS[44]].rot.y;
}

void func_8010AAA0_swinging_with_sharks(void) {
    f32 x, y, z;
    u16 model;

    model = MODELS[44];
    if (D_8010B9E0_swinging_with_sharks >= 3 && HmfModelData[MODELS[47]].unk02 == MOTS[49]) {
        if (D_8010B76C_swinging_with_sharks == 0) {
            func_8001C624_main(MODELS[(s16)model], MOTS[45], 0, 4, 2); /* retail indexes the model table by a model id */
        }
        if (++D_8010B76C_swinging_with_sharks >= 30) {
            if (D_8010BB48_swinging_with_sharks < 90) {
                D_8010BB48_swinging_with_sharks = D_8010BB48_swinging_with_sharks + 1.5f;
            }
            x = HmfModelData[(s16)model].pos.x + sindf(D_8010BB48_swinging_with_sharks) * 10.0f;
            y = HmfModelData[(s16)model].pos.y;
            z = HmfModelData[(s16)model].pos.z + cosdf(D_8010BB48_swinging_with_sharks) * 10.0f;
            Hu3DModelPosSet(model, x, y, z);
            HmfModelData[(s16)model].rot.y = D_8010BB48_swinging_with_sharks;
            HmfModelData[MODELS[47]].pos.x = x;
            HmfModelData[MODELS[47]].pos.z = z;
            HmfModelData[MODELS[47]].rot.y = D_8010BB48_swinging_with_sharks;
        }
    }
}

/* .data */
u8 D_8010ACE0_swinging_with_sharks = 0;
u8 D_8010ACE1_swinging_with_sharks = 0;
f32 D_8010ACE4_swinging_with_sharks = 0.0f;
f32 D_8010ACE8_swinging_with_sharks = 0.0f;
SwModelDef D_8010ACEC_swinging_with_sharks[51] = {
    { 0x600001, 0x211, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600000, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600005, 0x231, 0, 0, { -700.0f, 600.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600002, 0x231, 0, 0, { -230.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600002, 0x231, 0, 0, { 0.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600002, 0x231, 0, 0, { 230.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600002, 0x231, 0, 0, { 460.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600002, 0x231, 0, 0, { 690.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600003, 0x229, 0, 0, { -300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600003, 0x229, 0, 0, { 0.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600003, 0x229, 0, 0, { 300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600003, 0x229, 0, 0, { 600.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600003, 0x229, 0, 0, { 900.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600004, 0xa51, 0, 0, { -300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600004, 0xa51, 0, 0, { 0.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600004, 0xa51, 0, 0, { 300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600004, 0xa51, 0, 0, { 600.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600004, 0xa51, 0, 0, { 900.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xb0030, 0xa01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xb0030, 0xa01, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xb0030, 0xa01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xb0030, 0xa01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xb0030, 0xa01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x220004, 0xa35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x220004, 0xa35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x220004, 0xa35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x220004, 0xa35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x220004, 0xa35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600006, 0xa51, 0, 0, { -700.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xb0049, 0xa35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x220004, 0xa35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xb0030, 0xa25, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { (s32)0xFFFF00A1, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x600008, 0xa20, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { (s32)0xFFFF0004, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { (s32)0xFFFF000D, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { (s32)0xFFFF0010, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { (s32)0xFFFF000E, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { (s32)0xFFFF0001, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { (s32)0xFFFF0035, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { (s32)0xFFFF0038, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { (s32)0xFFFF0071, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x7f, 0xa15, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xb0002, 0xa35, 0, 0, { 0.0f, 500.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xa0154, 0x231, 0, 2, { 110.0f, 0.0f, -1170.0f }, { -25.0f, -28.0f, 0.0f } },
    { 0xa0155, 0x231, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xb0030, 0xa20, 0, 0, { 110.0f, 0.0f, -1170.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xa00ee, 0x231, 0, 2, { 110.0f, 60.0f, -1170.0f }, { 0.0f, -28.0f, 0.0f } },
    { 0xa00f6, 0xa35, 0, 0, { 0.0f, 500.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xa00fc, 0xa35, 0, 0, { 0.0f, 500.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { -1, 0x0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
};
u16 D_8010B418_swinging_with_sharks[4] = { 76, 51, 25, 12 };
u8 D_8010B420_swinging_with_sharks[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s16 D_8010B428_swinging_with_sharks = 0;
s16 D_8010B42A_swinging_with_sharks = 0;
s16 D_8010B42C_swinging_with_sharks = -1;
s32 D_8010B430_swinging_with_sharks[20] = {
    0x0021002D, 0x0021002E, 0x0021002F, 0x00210030, 0x00210031,
    0x00210032, 0x00210033, 0x00210034, 0x00210035, 0x00210036,
    0x00210037, 0x00210038, 0x00210039, 0x0021003A, 0x0021003B,
    0x0021003C, 0x0021003D, 0x0021003E, 0x0021003F, 0x00210040,
};
s16 D_8010B480_swinging_with_sharks = 0;
f32 D_8010B484_swinging_with_sharks = 0.017453292f; /* M_PI / 180 */
SwPathPt D_8010B488_swinging_with_sharks[12] = {
    { 110.0f, -75.0f, -790.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 110.0f, -75.0f, -790.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -720.0f, -75.0f, -1230.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -1330.0f, -75.0f, -750.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -780.0f, -75.0f, 50.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 40.0f, -50.0f, 230.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 910.0f, -75.0f, 20.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 1240.0f, -75.0f, -420.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 670.0f, -75.0f, -880.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 110.0f, -75.0f, -790.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 110.0f, -75.0f, -790.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 0.0f, 0.0f, 0.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
};
SwPathPt D_8010B5D8_swinging_with_sharks[14] = {
    { -750.0f, -75.0f, 50.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -750.0f, -75.0f, 50.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -740.0f, -75.0f, 50.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 40.0f, -50.0f, 230.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 910.0f, -75.0f, 20.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 1240.0f, -75.0f, -420.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 670.0f, -75.0f, -880.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 110.0f, -75.0f, -790.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -720.0f, -75.0f, -1230.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -1330.0f, -75.0f, -750.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -790.0f, -75.0f, 50.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -780.0f, -75.0f, 50.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { -780.0f, -75.0f, 50.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { 0.0f, 0.0f, 0.0f, { 0.0f, 0.0f, 0.0f }, 0.0f },
};
SwPathPt *D_8010B760_swinging_with_sharks[2] = { D_8010B488_swinging_with_sharks, D_8010B5D8_swinging_with_sharks };
s16 D_8010B768_swinging_with_sharks = 0;
s16 D_8010B76A_swinging_with_sharks = 0;
s16 D_8010B76C_swinging_with_sharks = 0;
