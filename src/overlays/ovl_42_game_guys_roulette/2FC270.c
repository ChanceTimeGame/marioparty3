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

// roulette A: Game Guy's Roulette (one player bets coins on a spinning wheel)

/* An overlay sprite: an esprite slot with its place on screen (functions 80108A14/80108A6C/80108A9C) */
typedef struct GgrSprite {
    /* 0x00 */ u8 id;
    /* 0x04 */ s32 prio;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
    /* 0x10 */ u32 w;
    /* 0x14 */ u32 h;
    /* 0x18 */ f32 sx;
    /* 0x1C */ f32 sy;
} GgrSprite; /* size 0x20 */

/* The player who plays (func_80105E10) */
typedef struct GgrPlayer {
    /* 0x00 */ u8 player;
    /* 0x01 */ u8 pad;
    /* 0x02 */ u8 chr;
    /* 0x03 */ u8 cpu;
    /* 0x04 */ u8 difficulty;
    /* 0x06 */ u16 coins;
} GgrPlayer; /* size 0x8 */

/* The result message's state (func_80108414, func_80108480) */
typedef struct GgrResult {
    /* 0x00 */ s16 timer;
    /* 0x02 */ u8 wait;
    /* 0x03 */ u8 step;
} GgrResult;

typedef struct GgrI6 {
    s32 v[6];
} GgrI6;
typedef struct GgrI8 {
    s32 v[8];
} GgrI8;

void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BD50_main(u16 spriteId, s16 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void GMesMaxTimeGet(s16 mesId, s16 time);
void func_800557A0_main(void);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
/* main (functions.us.h is left out: it declares func_80060EA8_main's window id s16, window.c defines it s32) */
void func_8000B5F0_main(u8 arg0);
s16 func_8000B638_main(void);
void func_8004A208_main(void);
void func_8005A6B0_main(void);
s32 func_80060880_main(s32 arg0, s32 arg1, s32 arg2);
void func_8005B63C_main(s16, s32, s32);
void func_80061100_main(s16, s32);
void func_80060EA8_main(s32 winId, s32 sound);

// LOCAL
void func_801059A0_game_guys_roulette(void);
s32 func_801059BC_game_guys_roulette(f32 arg0);
void func_80105A28_game_guys_roulette(void);
void func_80105A78_game_guys_roulette(void);
void func_80105BD8_game_guys_roulette(void);
void func_80105C40_game_guys_roulette(void);
void func_80105CD0_game_guys_roulette(omObjData* obj);
void func_80105E10_game_guys_roulette(GgrPlayer* p);
void func_80105F70_game_guys_roulette(void);
void func_80106428_game_guys_roulette(omObjData* obj);
void func_801068E8_game_guys_roulette(omObjData* obj);
void func_801069DC_game_guys_roulette(omObjData* obj);
void func_80106B74_game_guys_roulette(omObjData* obj);
void func_80106C58_game_guys_roulette(omObjData* obj);
void func_80106DD8_game_guys_roulette(omObjData* obj);
void func_80106EA4_game_guys_roulette(omObjData* obj);
void func_801070C4_game_guys_roulette(void);
void func_80107104_game_guys_roulette(void);
void func_8010726C_game_guys_roulette(s16 winId);
void func_801073AC_game_guys_roulette(void);
void func_80107A00_game_guys_roulette(void);
void func_80107AA8_game_guys_roulette(void);
void func_80107B20_game_guys_roulette(void);
void func_80108414_game_guys_roulette(void);
void func_80108480_game_guys_roulette(void);
void func_801085A4_game_guys_roulette(omObjData* obj);
void func_801088B0_game_guys_roulette(omObjData* obj);
void func_80108998_game_guys_roulette(omObjData* obj);
void func_801089EC_game_guys_roulette(omObjData* obj);
void func_80108A14_game_guys_roulette(GgrSprite* sp, s32 file, s32 attr);
void func_80108A6C_game_guys_roulette(GgrSprite* sp, s32 prio, s32 x, s32 y, s32 w, s32 h, f32 sx, f32 sy);
void func_80108A9C_game_guys_roulette(GgrSprite* sp, u8 show);
s16 func_80108B44_game_guys_roulette(s16 winId, s16 pad, s16 mode, s16 count);
// 2FF5F0
void func_80108D20_game_guys_roulette(s32 x, s32 y);
s16 func_80109078_game_guys_roulette(void);
void func_80109D14_game_guys_roulette(void);

extern u8 D_8010A640_game_guys_roulette[]; /* pairs by CPU level: the window's key delay at +1 */
extern s16 D_8010A646_game_guys_roulette;
extern GgrResult D_8010A678_game_guys_roulette;
extern s16 D_8010A67C_game_guys_roulette;
extern char* D_8010A680_game_guys_roulette[8]; /* character names */
extern u8 D_8010A6A0_game_guys_roulette[2];
extern u8 D_8010A6A4_game_guys_roulette[];
extern GgrI6 D_8010A6C0_game_guys_roulette;
extern GgrI8 D_8010A6D8_game_guys_roulette;
extern GgrI6 D_8010A6F8_game_guys_roulette;
extern GgrI8 D_8010A710_game_guys_roulette;
extern char D_8010A7D0_game_guys_roulette[];

extern char D_8010A810_game_guys_roulette[0x100];
extern omObjData* D_8010A910_game_guys_roulette;
extern omObjData* D_8010A914_game_guys_roulette;
extern omObjData* D_8010A918_game_guys_roulette;
extern omObjData* D_8010A91C_game_guys_roulette;
extern omObjData* D_8010A920_game_guys_roulette;
extern Process* D_8010A924_game_guys_roulette;
extern Process* D_8010A928_game_guys_roulette;
extern GgrSprite D_8010A930_game_guys_roulette;
extern GgrSprite D_8010A950_game_guys_roulette;
extern GgrSprite D_8010A970_game_guys_roulette;
extern GgrSprite D_8010A990_game_guys_roulette;
extern GgrSprite D_8010A9B0_game_guys_roulette[6];
extern GgrSprite D_8010AA70_game_guys_roulette;
extern GgrSprite D_8010AA90_game_guys_roulette;
extern GgrSprite D_8010AAB0_game_guys_roulette;
extern u16 D_8010AAD0_game_guys_roulette[3]; /* coin digit esprites: ones, tens, hundreds */
extern GgrPlayer D_8010AAD6_game_guys_roulette;
extern u16 D_8010AADE_game_guys_roulette; /* the window */
extern u16 D_8010AAE0_game_guys_roulette;
extern u16 D_8010AAE2_game_guys_roulette;
extern u8 D_8010AB50_game_guys_roulette; /* director step */
extern u8 D_8010AB51_game_guys_roulette;
extern s16 D_8010AB54_game_guys_roulette;
extern u8 D_8010AB58_game_guys_roulette; /* 1: won */
extern s16 D_8010AB5A_game_guys_roulette; /* CPU level 0-2 */

void func_801059A0_game_guys_roulette(void) {
    func_80105C40_game_guys_roulette();
}

s32 func_801059BC_game_guys_roulette(f32 arg0) {
    u8 hi = rand8();
    u8 lo = rand8();
    s32 shifted = (hi << 8);
    s32 r = ((lo | shifted) / 65536.0f) * arg0;

    return r;
}

void func_80105A28_game_guys_roulette(void) {
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 0.0f, 95.0f);
}

void func_80105A78_game_guys_roulette(void) {
    s16 cam;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(cam, 19.03f, 80.0f, 8000.0f);
    CZoom = 1498.69f;
    CRot.x = 334.75f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 10.82f;
    Center.z = -505.55f;
}

void func_80105BD8_game_guys_roulette(void) {
    func_8005A6B0_main();
    D_8010AADE_game_guys_roulette = func_80060880_main(0x82, 0x6E, 9);
    func_8005B63C_main(D_8010AADE_game_guys_roulette, 2, 2);
    func_80061100_main(D_8010AADE_game_guys_roulette, 1);
    func_80060EA8_main(D_8010AADE_game_guys_roulette, 1);
}

void func_80105C40_game_guys_roulette(void) {
    Hu3DAnimInit(0x20);
    func_800142A0_main(0x20);
    omInitObjMan(0x20, 0x20);
    func_8004A208_main();
    func_80105A28_game_guys_roulette();
    func_80105A78_game_guys_roulette();
    func_80105BD8_game_guys_roulette();
    omAddObj(1000, 0, 0, -1, func_80105CD0_game_guys_roulette);
    omAddObj(2000, 0, 0, -1, func_801089EC_game_guys_roulette);
}

void func_80105CD0_game_guys_roulette(omObjData* obj) {
    func_80108D20_game_guys_roulette(0xA0, 0x56);
    func_80105E10_game_guys_roulette(&D_8010AAD6_game_guys_roulette);
    func_80105F70_game_guys_roulette();
    D_8010A910_game_guys_roulette = omAddObj(0, 10, 10, -1, func_80106428_game_guys_roulette);
    D_8010A918_game_guys_roulette = omAddObj(1, 10, 10, -1, func_801068E8_game_guys_roulette);
    D_8010A914_game_guys_roulette = omAddObj(2, 10, 10, -1, func_801069DC_game_guys_roulette);
    D_8010A91C_game_guys_roulette = omAddObj(3, 10, 10, -1, func_80106B74_game_guys_roulette);
    D_8010A920_game_guys_roulette = omAddObj(4, 10, 10, -1, func_80106C58_game_guys_roulette);
    omAddObj(5, 10, 10, -1, func_80106DD8_game_guys_roulette);
    WipeCreateIn(0xFF, 16);
    obj->func = func_80106EA4_game_guys_roulette;
}

/* The player in group 0 plays. */
void func_80105E10_game_guys_roulette(GgrPlayer* p) {
    u8 i;
    u8 n;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    switch (i) {
    case 0:
        n = 0;
        break;
    case 1:
        n = 1;
        break;
    case 2:
        n = 2;
        break;
    case 3:
        n = 3;
        break;
    default:
        n = 0;
        break;
    }
    p->player = n;
    p->pad = GwPlayer[n].pad;
    p->chr = GwPlayer[n].chr;
    if (GwPlayer[n].stat & 1) {
        p->cpu = 1;
        p->difficulty = GwPlayer[n].cpu_difficulty;
        D_8010AB5A_game_guys_roulette = GwCommon.unkA0;
        if (D_8010AB5A_game_guys_roulette <= 0) {
            D_8010AB5A_game_guys_roulette = 0;
        } else if (D_8010AB5A_game_guys_roulette >= 2) {
            D_8010AB5A_game_guys_roulette = 2;
        }
    } else {
        p->cpu = 0;
        p->difficulty = 0;
    }
    p->coins = GwPlayer[n].gameCoin;
}

















INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80105F70_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106428_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801068E8_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801069DC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106B74_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106C58_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106DD8_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80106EA4_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801070C4_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80107104_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_8010726C_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801073AC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80107A00_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80107AA8_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80107B20_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108414_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A770_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A77C_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A78C_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A794_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7A0_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7AC_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7B8_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7C4_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7D0_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108480_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801085A4_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801088B0_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108998_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801089EC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108A14_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108A6C_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108A9C_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108B44_game_guys_roulette);
