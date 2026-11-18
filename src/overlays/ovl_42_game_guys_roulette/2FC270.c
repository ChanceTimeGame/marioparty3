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

/* The CPU's key presses in the window, by CPU level */
typedef struct GgrCpuKey {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 delay;
} GgrCpuKey;

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
void func_80060C14_main(s32 winId, s32 sound);
void func_8005D294_main(s16);
void func_8005B43C_main(s16, s32, s32, s32);
void func_8005F904_main(void);
s16 func_8005E0C0_main(s16);
void func_8005F698_main(s16, s16, s16, s16, u8);
void func_8005F744_main(s16, s16, s16, s16);
void func_8005FE54_main(s16, s16);
s32 func_8005E1D8_main(s16, s16, s32);
void func_8005F524_main(void);
extern u8 D_800D6A58_main;
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[4];
extern s8 D_800D20A1_main[];
void func_8005B6BC_main(s16 win_id, u32 arg1, s8 arg2);

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

extern GgrCpuKey D_8010A640_game_guys_roulette[3]; /* by CPU level */
extern u8 D_8010A646_game_guys_roulette;
extern u8 D_8010A647_game_guys_roulette; /* cursor direction: 1 up */
extern u8 D_8010A648_game_guys_roulette; /* cursor step */
extern f32 D_8010A64C_game_guys_roulette; /* chosen prize's pulse scale */
extern f32 D_8010A650_game_guys_roulette; /* its speed */
extern u8 D_8010A654_game_guys_roulette; /* cursor move frames */
extern u8 D_8010A655_game_guys_roulette; /* CPU key timer */
extern u8 D_8010A656_game_guys_roulette; /* bet timer frames */
extern u8 D_8010A657_game_guys_roulette; /* bet timer seconds */
extern f32 D_8010A658_game_guys_roulette; /* face scale */
extern s16 D_8010A65C_game_guys_roulette;
extern s16 D_8010A678_game_guys_roulette; /* result timer */
extern u8 D_8010A67A_game_guys_roulette; /* result message wait */
extern u8 D_8010A67B_game_guys_roulette; /* result step */
extern s16 D_8010A67C_game_guys_roulette;
extern char* D_8010A680_game_guys_roulette[8]; /* character names */
extern u8 D_8010A6A0_game_guys_roulette; /* banner blink timer */
extern u8 D_8010A6A1_game_guys_roulette; /* banner blink step */
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
extern f32 D_8010AAE4_game_guys_roulette; /* wheel speed */
extern f32 D_8010AAE8_game_guys_roulette; /* wheel deceleration */
extern f32 D_8010AAEC_game_guys_roulette;
extern u16 D_8010AAF0_game_guys_roulette[21]; /* pocket angles */
extern f32 D_8010AB20_game_guys_roulette[6];
extern f32 D_8010AB38_game_guys_roulette[6];
extern u8 D_8010AB50_game_guys_roulette; /* director step */
extern u8 D_8010AB51_game_guys_roulette;
extern s16 D_8010AB52_game_guys_roulette; /* the CPU's guess */
extern s16 D_8010AB54_game_guys_roulette;
extern u8 D_8010AB56_game_guys_roulette; /* the winning pocket */
extern u8 D_8010AB57_game_guys_roulette; /* its prize */
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

















/* Draw the winning pocket and its prize; for a CPU, its guess; then the pockets' angles and the spin that ends on
   the winning one (decelerating over 450 frames after seven full turns). */
void func_80105F70_game_guys_roulette(void) {
    f32 sector = 360.0f / 21;
    f32 half = 360.0f / 42;
    u8 i;
    u32 v;

    D_8010AB56_game_guys_roulette = func_801059BC_game_guys_roulette(21.0f);
    if (D_8010AB56_game_guys_roulette == 0) {
        D_8010AB57_game_guys_roulette = 5;
    } else if (D_8010AB56_game_guys_roulette < 5) {
        D_8010AB57_game_guys_roulette = 2;
    } else if (D_8010AB56_game_guys_roulette < 7) {
        D_8010AB57_game_guys_roulette = 4;
    } else if (D_8010AB56_game_guys_roulette < 13) {
        D_8010AB57_game_guys_roulette = 0;
    } else if (D_8010AB56_game_guys_roulette < 16) {
        D_8010AB57_game_guys_roulette = 3;
    } else if (D_8010AB56_game_guys_roulette < 21) {
        D_8010AB57_game_guys_roulette = 1;
    }
    if (D_8010AAD6_game_guys_roulette.cpu == 1) {
        D_8010AB52_game_guys_roulette = func_801059BC_game_guys_roulette(6.0f);
        if (D_8010AAD6_game_guys_roulette.difficulty != 0) {
            D_8010AB52_game_guys_roulette -= func_801059BC_game_guys_roulette(D_8010AAD6_game_guys_roulette.difficulty);
            if (D_8010AB52_game_guys_roulette <= 0) {
                D_8010AB52_game_guys_roulette = 0;
            }
        }
        if (D_8010AB57_game_guys_roulette == D_8010AB52_game_guys_roulette) {
            D_8010AB58_game_guys_roulette = 1;
        } else {
            D_8010AB58_game_guys_roulette = 0;
        }
    }
    D_8010AB51_game_guys_roulette = 0;
    for (i = 0; i < 21; i++) {
        v = (sector * i + 270.0f) * 100.0f;
        if (v % 100 >= 50) {
            D_8010AAF0_game_guys_roulette[i] = (v / 100 + 1) % 360;
        } else {
            D_8010AAF0_game_guys_roulette[i] = (v / 100) % 360;
        }
    }
    D_8010AAE4_game_guys_roulette = ((D_8010AAF0_game_guys_roulette[D_8010AB56_game_guys_roulette] + 2520.0f) * 2) / 450.0f;
    D_8010AAE8_game_guys_roulette = D_8010AAE4_game_guys_roulette / 450.0f;
    D_8010AAEC_game_guys_roulette = (D_8010AAE4_game_guys_roulette + D_8010AAE8_game_guys_roulette) *
                                        (D_8010AAE4_game_guys_roulette / D_8010AAE8_game_guys_roulette) / 2.0f -
                                    (D_8010AAF0_game_guys_roulette[D_8010AB56_game_guys_roulette] + 2520.0f);
    D_8010AAE4_game_guys_roulette =
        (((D_8010AAF0_game_guys_roulette[D_8010AB56_game_guys_roulette] + 2520.0f) - D_8010AAEC_game_guys_roulette) * 2) / 450.0f;
    D_8010AAE8_game_guys_roulette = D_8010AAE4_game_guys_roulette / 450.0f;
    D_8010AB20_game_guys_roulette[0] = 270.0f - half;
    D_8010AB20_game_guys_roulette[1] = sector + D_8010AB20_game_guys_roulette[0];
    D_8010AB20_game_guys_roulette[2] = sector * 4 + D_8010AB20_game_guys_roulette[1];
    D_8010AB20_game_guys_roulette[3] = (sector + sector + D_8010AB20_game_guys_roulette[2]) - 360.0f;
    D_8010AB20_game_guys_roulette[4] = sector * 6 + D_8010AB20_game_guys_roulette[3];
    D_8010AB20_game_guys_roulette[5] = sector * 3 + D_8010AB20_game_guys_roulette[4];
    D_8010AB38_game_guys_roulette[0] = D_8010AAF0_game_guys_roulette[9] + half;
    D_8010AB38_game_guys_roulette[1] = D_8010AAF0_game_guys_roulette[18];
    D_8010AB38_game_guys_roulette[2] = D_8010AAF0_game_guys_roulette[2] + half;
    D_8010AB38_game_guys_roulette[3] = D_8010AAF0_game_guys_roulette[14];
    D_8010AB38_game_guys_roulette[4] = D_8010AAF0_game_guys_roulette[5] + half;
    D_8010AB38_game_guys_roulette[5] = 270.0f;
    D_8010AB50_game_guys_roulette = 0;
}

/* The sprites: background, the two blinking banners, the bet panel, the six prize icons, the player's face,
   the coin icon and its "x", the coin count's three digits. */
void func_80106428_game_guys_roulette(omObjData* obj) {
    GgrI6 prizes = D_8010A6C0_game_guys_roulette;
    u8 chr = GwPlayer[D_8010AAD6_game_guys_roulette.player].chr;
    GgrI8 faces = D_8010A6D8_game_guys_roulette;
    u8 i;
    s16 file;

    func_80108A14_game_guys_roulette(&D_8010A930_game_guys_roulette, 0x630000, 0x4008);
    func_80108A6C_game_guys_roulette(&D_8010A930_game_guys_roulette, 1000, 0, 0, 320, 240, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010A930_game_guys_roulette, 1);
    func_80108A14_game_guys_roulette(&D_8010A950_game_guys_roulette, 0x630001, 0x4008);
    func_80108A6C_game_guys_roulette(&D_8010A950_game_guys_roulette, 900, 0, 0, 320, 128, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010A950_game_guys_roulette, 0);
    func_80108A14_game_guys_roulette(&D_8010A970_game_guys_roulette, 0x630002, 0x4008);
    func_80108A6C_game_guys_roulette(&D_8010A970_game_guys_roulette, 900, 0, 0, 320, 128, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010A970_game_guys_roulette, 0);
    func_80108A14_game_guys_roulette(&D_8010A990_game_guys_roulette, 0x630003, 8);
    func_80108A6C_game_guys_roulette(&D_8010A990_game_guys_roulette, 800, 242, 16, 54, 144, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010A990_game_guys_roulette, 1);
    for (i = 0; i < 6; i++) {
        func_80108A14_game_guys_roulette(&D_8010A9B0_game_guys_roulette[i], prizes.v[i] | 0x630000, 8);
        func_80108A6C_game_guys_roulette(&D_8010A9B0_game_guys_roulette[i], 700, 246, i * 22 + 22, 22, 22, 1.0f, 1.0f);
        func_80108A9C_game_guys_roulette(&D_8010A9B0_game_guys_roulette[i], 0);
    }
    func_80108A14_game_guys_roulette(&D_8010AA70_game_guys_roulette, faces.v[chr] | 0x210000, 8);
    func_80108A6C_game_guys_roulette(&D_8010AA70_game_guys_roulette, 600, 206, 1, 46, 46, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010AA70_game_guys_roulette, 0);
    func_80108A14_game_guys_roulette(&D_8010AA90_game_guys_roulette, 0x21001A, 8);
    func_80108A6C_game_guys_roulette(&D_8010AA90_game_guys_roulette, 500, 24, 16, 12, 12, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010AA90_game_guys_roulette, 1);
    func_80108A14_game_guys_roulette(&D_8010AAB0_game_guys_roulette, 0x21001B, 8);
    func_80108A6C_game_guys_roulette(&D_8010AAB0_game_guys_roulette, 500, 36, 16, 12, 12, 1.0f, 1.0f);
    func_80108A9C_game_guys_roulette(&D_8010AAB0_game_guys_roulette, 1);
    file = func_8000B838_main(0x31);
    D_8010AAD0_game_guys_roulette[0] = InitEspriteSlot(file, 0, 1);
    func_8000BBD4_main(D_8010AAD0_game_guys_roulette[0], 54, 22);
    func_8000BCC8_main(D_8010AAD0_game_guys_roulette[0], 500);
    D_8010AAD0_game_guys_roulette[1] = InitEspriteSlot(file, 0, 1);
    func_8000BBD4_main(D_8010AAD0_game_guys_roulette[1], 66, 22);
    func_8000BCC8_main(D_8010AAD0_game_guys_roulette[1], 500);
    D_8010AAD0_game_guys_roulette[2] = InitEspriteSlot(file, 0, 1);
    func_8000BBD4_main(D_8010AAD0_game_guys_roulette[2], 78, 22);
    func_8000BCC8_main(D_8010AAD0_game_guys_roulette[2], 500);
    obj->func = func_801085A4_game_guys_roulette;
}

/* Game Guy */
void func_801068E8_game_guys_roulette(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0xA0063, 0x2B9);
    omSetTra(obj, 0.0f, 193.0f, -117.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0xA0063);
    func_8000B460_main(obj, 1, 0xA0066);
    func_8000B460_main(obj, 2, 0xA0067);
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
    obj->func = NULL;
}

/* The wheel and its six prize sectors */
void func_801069DC_game_guys_roulette(omObjData* obj) {
    GgrI6 files = D_8010A6F8_game_guys_roulette;
    u8 i;

    obj->model[0] = func_8000B108_main(0x63000D, 0x2B9);
    omSetTra(obj, 0.0f, 100.0f, 0.0f);
    omSetRot(obj, 15.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for (i = 1; i < 7; i++) {
        obj->model[i] = func_8000B108_main(files.v[i - 1] | 0x630000, 0x2B9);
        Hu3DModelPosSet(obj->model[i], 0.0f, 100.0f, 0.0f);
        Hu3DModelRotSet(obj->model[i], 15.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[i], 1.0f, 1.0f, 1.0f);
    }
    obj->func = NULL;
}

/* The player's character */
void func_80106B74_game_guys_roulette(omObjData* obj) {
    GgrI8 files = D_8010A710_game_guys_roulette;

    obj->model[0] = func_8000B108_main(files.v[D_8010AAD6_game_guys_roulette.chr] | 0x210000, 0x2B9);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 15.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8001C8A8_main(obj->model[0], 0);
    obj->func = NULL;
}

/* The ball and its shadow, on the rim at 270 degrees of the wheel tilted 15 */
void func_80106C58_game_guys_roulette(omObjData* obj) {
    f32 x;
    f32 y;
    f32 z;

    obj->model[0] = func_8000B108_main(0x63000B, 0x2B9);
    obj->model[1] = func_8000B108_main(0x63000C, 0x2B9);
    x = cosdf(270.0f) * 85.0f;
    y = cosdf(15.0f) * 100.0f - sindf(270.0f) * 85.0f * sindf(15.0f);
    z = 100.0f * sindf(15.0f) + 85.0f * sindf(270.0f) * cosdf(15.0f);
    omSetTra(obj, x, y + 100.0f, z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->func = NULL;
}

void func_80106DD8_game_guys_roulette(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0x630014, 0x2B9);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0x630014);
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
    obj->func = NULL;
}

/* The director */
void func_80106EA4_game_guys_roulette(omObjData* obj) {
    switch (D_8010AB50_game_guys_roulette) {
    case 0:
        func_801070C4_game_guys_roulette();
        break;
    case 1:
        D_8010A924_game_guys_roulette = omAddPrcObj(func_80107104_game_guys_roulette, 0x3F00, 0x800, 0);
        D_8010AB50_game_guys_roulette = 2;
        break;
    case 2:
        if (D_8010AAE0_game_guys_roulette == 1) {
            D_8010AB50_game_guys_roulette = 5;
            D_8010AAE0_game_guys_roulette = 0;
            omDelPrcObj(D_8010A924_game_guys_roulette);
            D_800D6A58_main = 0;
            D_8010AB54_game_guys_roulette = GMesCreate(0x1A, 10, 156, 56);
        }
        break;
    case 5:
        func_801073AC_game_guys_roulette();
        break;
    case 6:
        D_8010A928_game_guys_roulette = omAddPrcObj(func_80107A00_game_guys_roulette, 0x3F00, 0x800, 0);
        D_8010AB50_game_guys_roulette = 7;
        break;
    case 7:
        if (D_8010AA70_game_guys_roulette.sx > 0.0f) {
            D_8010AA70_game_guys_roulette.sx = D_8010AA70_game_guys_roulette.sy -= 0.25f;
            func_80108A9C_game_guys_roulette(&D_8010AA70_game_guys_roulette, 1);
        } else {
            D_8010AA70_game_guys_roulette.sx = D_8010AA70_game_guys_roulette.sy = 0.0f;
            func_80108A9C_game_guys_roulette(&D_8010AA70_game_guys_roulette, 0);
        }
        if (D_8010AAE2_game_guys_roulette == 1 && D_8010AA70_game_guys_roulette.sx <= 0.0f) {
            D_8010AB50_game_guys_roulette = 8;
            D_8010AAE2_game_guys_roulette = 0;
            omDelPrcObj(D_8010A928_game_guys_roulette);
        }
        break;
    case 8:
        func_80107AA8_game_guys_roulette();
        break;
    case 9:
        func_80107B20_game_guys_roulette();
        break;
    case 10:
        func_80108414_game_guys_roulette();
        break;
    case 11:
        func_80108480_game_guys_roulette();
        break;
    case 12:
        obj->func = func_801088B0_game_guys_roulette;
        break;
    }
}

void func_801070C4_game_guys_roulette(void) {
    D_8010A646_game_guys_roulette = func_80109078_game_guys_roulette();
    if (D_8010A646_game_guys_roulette == 1) {
        D_8010AB50_game_guys_roulette = 1;
    }
}

/* Game Guy's opening talk: the rules, then the bet */
void func_80107104_game_guys_roulette(void) {
    s16 done = 0;
    s16 r;

    func_8005D294_main(D_8010AADE_game_guys_roulette);
    HuAudFXPlay(0x11D);
    func_80060C14_main(D_8010AADE_game_guys_roulette, 1);
    func_8005B43C_main(D_8010AADE_game_guys_roulette, 0x2D00, -1, -1);
    func_8010726C_game_guys_roulette(D_8010AADE_game_guys_roulette);
    func_8005B43C_main(D_8010AADE_game_guys_roulette, 0x2D01, -1, -1);
    do {
        r = func_80108B44_game_guys_roulette(D_8010AADE_game_guys_roulette, D_8010AAD6_game_guys_roulette.pad,
                                             D_8010AAD6_game_guys_roulette.cpu, 1);
        if (r == 0) {
            func_8005B43C_main(D_8010AADE_game_guys_roulette, 0x2D02, -1, -1);
            done = 1;
            func_8010726C_game_guys_roulette(D_8010AADE_game_guys_roulette);
        } else if (r == 1) {
            done = 1;
        }
        HuPrcVSleep();
    } while (done == 0);
    func_8005B43C_main(D_8010AADE_game_guys_roulette, 0x2D03, -1, -1);
    func_8010726C_game_guys_roulette(D_8010AADE_game_guys_roulette);
    func_8005D294_main(D_8010AADE_game_guys_roulette);
    func_80060EA8_main(D_8010AADE_game_guys_roulette, 1);
    D_8010AAE0_game_guys_roulette = 1;
    while (1) {
        HuPrcVSleep();
    }
}

/* Wait for the window's message to end: a human presses A, the CPU's key is pressed for it */
void func_8010726C_game_guys_roulette(s16 winId) {
    s16 i;

    func_8005F904_main();
    while (func_8005E0C0_main(winId) != 0) {
        switch (D_8010AAD6_game_guys_roulette.cpu) {
        case 0:
            if (D_800D5558_main[D_8010AAD6_game_guys_roulette.pad] & 0x8000) {
                func_8005F744_main(-0x8000, -0x8000, -0x8000, -0x8000);
            }
            break;
        case 1:
            for (i = 0; i < 10; i++) {
                func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000, (&D_8010A640_game_guys_roulette[D_8010AB5A_game_guys_roulette])->delay);
            }
            while (func_8005E0C0_main(winId) != 0) {
                HuPrcVSleep();
            }
            break;
        }
        HuPrcVSleep();
    }
    func_8005F904_main();
}

/* The bet: move the cursor (the player's face) over the six prizes with the stick, A or the timer ends it; the CPU
   steps down to its guess. The chosen prize pulses. */
// masked 4: retail loads 102.5f after the first cosdf call, this C before it (constant placement only)
#ifdef NON_MATCHING
void func_801073AC_game_guys_roulette(void) {
    u8 confirm = 0;
    u8 dir = 0;
    u8 i;
    f32 x;
    f32 r;
    f32 y;
    f32 h;

    if (D_8010AAD6_game_guys_roulette.cpu == 0) {
        confirm = D_800D5558_main[D_8010AAD6_game_guys_roulette.pad] >> 15;
        dir = D_800D20A1_main[D_8010AAD6_game_guys_roulette.pad] > 64;
        if (D_800D20A1_main[D_8010AAD6_game_guys_roulette.pad] < -64) {
            dir = 2;
        }
    } else if (D_8010AAD6_game_guys_roulette.cpu == 1) {
        if (D_8010A655_game_guys_roulette >= 16) {
            if (D_8010AB51_game_guys_roulette == D_8010AB52_game_guys_roulette) {
                confirm = 1;
            } else {
                dir = 2;
            }
            D_8010A655_game_guys_roulette = 0;
        } else {
            D_8010A655_game_guys_roulette++;
        }
    }
    if (D_8010A656_game_guys_roulette < 30) {
        D_8010A656_game_guys_roulette++;
    } else {
        D_8010A657_game_guys_roulette--;
        D_8010A656_game_guys_roulette = 0;
        if (D_8010A657_game_guys_roulette == 0) {
            confirm = 1;
        }
    }
    func_8003F578_main(D_8010A657_game_guys_roulette);
    if (D_8010A654_game_guys_roulette == 0) {
        if (dir == 1 && D_8010AB51_game_guys_roulette != 0) {
            D_8010AB51_game_guys_roulette--;
            D_8010A654_game_guys_roulette = 5;
            D_8010A64C_game_guys_roulette = 1.1f;
            D_8010A650_game_guys_roulette = 0.1f;
            D_8010A647_game_guys_roulette = 1;
            HuAudFXPlay(1);
        } else if (dir == 2 && D_8010AB51_game_guys_roulette < 5) {
            D_8010AB51_game_guys_roulette++;
            D_8010A654_game_guys_roulette = 5;
            D_8010A64C_game_guys_roulette = 1.1f;
            D_8010A650_game_guys_roulette = 0.1f;
            D_8010A647_game_guys_roulette = 0;
            HuAudFXPlay(1);
        }
    } else {
        if (D_8010A654_game_guys_roulette == 5 || D_8010A654_game_guys_roulette == 1) {
            D_8010A648_game_guys_roulette = 2;
        } else {
            D_8010A648_game_guys_roulette = 6;
        }
        if (D_8010A647_game_guys_roulette == 0) {
            D_8010AA70_game_guys_roulette.y += D_8010A648_game_guys_roulette;
        } else {
            D_8010AA70_game_guys_roulette.y -= D_8010A648_game_guys_roulette;
        }
        D_8010A654_game_guys_roulette--;
    }
    for (i = 0; i < 6; i++) {
        func_80108A9C_game_guys_roulette(&D_8010A9B0_game_guys_roulette[i], 0);
        func_8001C8A8_main(D_8010A914_game_guys_roulette->model[i + 1], 1);
    }
    D_8010A9B0_game_guys_roulette[D_8010AB51_game_guys_roulette].sx =
        D_8010A9B0_game_guys_roulette[D_8010AB51_game_guys_roulette].sy = D_8010A64C_game_guys_roulette;
    func_80108A9C_game_guys_roulette(&D_8010A9B0_game_guys_roulette[D_8010AB51_game_guys_roulette], 1);
    if (D_8010A658_game_guys_roulette < 1.0f) {
        D_8010A658_game_guys_roulette += 0.25f;
    }
    D_8010AA70_game_guys_roulette.sx = D_8010AA70_game_guys_roulette.sy = D_8010A658_game_guys_roulette;
    func_80108A9C_game_guys_roulette(&D_8010AA70_game_guys_roulette, 1);
    func_8001C8A8_main(D_8010A914_game_guys_roulette->model[D_8010AB51_game_guys_roulette + 1], 0);
    D_8010A64C_game_guys_roulette += D_8010A650_game_guys_roulette;
    if (D_8010A64C_game_guys_roulette >= 1.5f || D_8010A64C_game_guys_roulette <= 1.1f) {
        D_8010A650_game_guys_roulette = -D_8010A650_game_guys_roulette;
    }
    if (confirm == 1) {
        func_8003F5C0_main();
        D_800D6A58_main = 1;
        HuAudFXPlay(3);
        omVibrate(D_8010AAD6_game_guys_roulette.player, 10, 0, 10);
        D_8010A9B0_game_guys_roulette[D_8010AB51_game_guys_roulette].sx =
            D_8010A9B0_game_guys_roulette[D_8010AB51_game_guys_roulette].sy = 1.5f;
        func_80108A9C_game_guys_roulette(&D_8010A9B0_game_guys_roulette[D_8010AB51_game_guys_roulette], 1);
        func_8001C8A8_main(D_8010A914_game_guys_roulette->model[D_8010AB51_game_guys_roulette + 1], 1);
        h = 102.5f;
        x = cosdf(D_8010AB38_game_guys_roulette[D_8010AB51_game_guys_roulette]) * 40.0f;
        h = 102.5f;
        r = sindf(D_8010AB38_game_guys_roulette[D_8010AB51_game_guys_roulette]) * 40.0f;
        y = cosdf(15.0f) * h - r * sindf(15.0f);
        omSetTra(D_8010A91C_game_guys_roulette, x, y + 100.0f, sindf(15.0f) * h + r * cosdf(15.0f));
        func_8001C8A8_main(D_8010A91C_game_guys_roulette->model[0], 1);
        if (D_8010AB51_game_guys_roulette == D_8010AB57_game_guys_roulette) {
            D_8010AB58_game_guys_roulette = 1;
        } else {
            D_8010AB58_game_guys_roulette = 0;
        }
        D_8010AB50_game_guys_roulette = 6;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_801073AC_game_guys_roulette);
#endif

/* Game Guy's line for the chosen prize */
void func_80107A00_game_guys_roulette(void) {
    func_8005D294_main(D_8010AADE_game_guys_roulette);
    func_80060C14_main(D_8010AADE_game_guys_roulette, 1);
    func_8005B43C_main(D_8010AADE_game_guys_roulette, 0x2D04, -1, -1);
    func_8005B6BC_main(D_8010AADE_game_guys_roulette, D_8010AB51_game_guys_roulette + 0x2D05, 0);
    func_8010726C_game_guys_roulette(D_8010AADE_game_guys_roulette);
    func_8005D294_main(D_8010AADE_game_guys_roulette);
    func_80060EA8_main(D_8010AADE_game_guys_roulette, 1);
    D_8010AAE2_game_guys_roulette = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_80107AA8_game_guys_roulette(void) {
    if (++D_8010A65C_game_guys_roulette == 1) {
        GMesCreate(9);
    } else if (GMesStatGet() == 0) {
        HuAudSeqFadeOut(30);
        D_8010AB50_game_guys_roulette = 9;
        D_8010A65C_game_guys_roulette = 0;
    }
}


INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80107B20_game_guys_roulette);

void func_80108414_game_guys_roulette(void) {
    if (++D_8010A678_game_guys_roulette == 1) {
        GMesCreate(0x14);
        HuAudSeqFadeOut(120);
    } else if (GMesStatGet() == 0) {
        D_8010AB50_game_guys_roulette = 11;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A770_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A77C_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A78C_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A794_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7A0_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7AC_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7B8_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7C4_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", D_8010A7D0_game_guys_roulette);

/* The result: the win jingle and message, or "<name> LOST!" */
// raw 2: retail sign-extends the message id through v0 (sll v0 / sra a0), register choice only
#ifdef NON_MATCHING
void func_80108480_game_guys_roulette(void) {
    s16 mes;

    if (D_8010A67B_game_guys_roulette == 0) {
        func_8004AB0C_main(30);
        if (D_8010AB58_game_guys_roulette == 1) {
            HuAudSeqPlay(0x73);
            mes = GMesCreate(0x16, D_8010AAD6_game_guys_roulette.chr);
        } else {
            HuAudSeqPlay(0x71);
            sprintf(D_8010A810_game_guys_roulette, D_8010A7D0_game_guys_roulette,
                    D_8010A680_game_guys_roulette[D_8010AAD6_game_guys_roulette.chr]);
            mes = GMesCreate(0x19, D_8010A810_game_guys_roulette, 160, 120, 1.0, 1.0, 1);
        }
        GMesMaxTimeGet(D_8010A67C_game_guys_roulette = mes, 120);
        D_8010A67B_game_guys_roulette = 1;
    } else if (D_8010A67B_game_guys_roulette == 1) {
        if (D_8010A67A_game_guys_roulette++ >= 135) {
            D_8010AB50_game_guys_roulette = 12;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FC270", func_80108480_game_guys_roulette);
#endif

/* Blink the two banners in turn; show the coin count */
void func_801085A4_game_guys_roulette(omObjData* obj) {
    s32 x = 0;
    u16 digit;

    if (D_8010A6A0_game_guys_roulette >= 5) {
        if (D_8010A6A1_game_guys_roulette == 0) {
            func_80108A9C_game_guys_roulette(&D_8010A950_game_guys_roulette, 0);
            func_80108A9C_game_guys_roulette(&D_8010A970_game_guys_roulette, 0);
        } else if (D_8010A6A1_game_guys_roulette == 1) {
            func_80108A9C_game_guys_roulette(&D_8010A950_game_guys_roulette, 1);
            func_80108A9C_game_guys_roulette(&D_8010A970_game_guys_roulette, 0);
        } else if (D_8010A6A1_game_guys_roulette == 2) {
            func_80108A9C_game_guys_roulette(&D_8010A950_game_guys_roulette, 0);
            func_80108A9C_game_guys_roulette(&D_8010A970_game_guys_roulette, 1);
        }
        D_8010A6A1_game_guys_roulette++;
        if (D_8010A6A1_game_guys_roulette >= 3) {
            D_8010A6A1_game_guys_roulette = 0;
        }
        D_8010A6A0_game_guys_roulette = 0;
    }
    D_8010A6A0_game_guys_roulette++;
    if (D_8010AAD6_game_guys_roulette.coins >= 999) {
        D_8010AAD6_game_guys_roulette.coins = 999;
    }
    if (D_8010AAD6_game_guys_roulette.coins == 0) {
        D_8010AAD6_game_guys_roulette.coins = 0;
    }
    func_8000BB54_main(D_8010AAD0_game_guys_roulette[2]);
    if ((digit = D_8010AAD6_game_guys_roulette.coins / 100) == 0) {
        func_8000BB94_main(D_8010AAD0_game_guys_roulette[2]);
    }
    func_8000BD50_main(D_8010AAD0_game_guys_roulette[2], digit);
    func_8000BBD4_main(D_8010AAD0_game_guys_roulette[2], x + 54, 22);
    if (digit != 0) {
        x += 12;
    }
    func_8000BB54_main(D_8010AAD0_game_guys_roulette[1]);
    if ((digit = (u16)(D_8010AAD6_game_guys_roulette.coins % 100) / 10) == 0 && (u16)(D_8010AAD6_game_guys_roulette.coins / 100) == 0) {
        func_8000BB94_main(D_8010AAD0_game_guys_roulette[1]);
    }
    func_8000BD50_main(D_8010AAD0_game_guys_roulette[1], digit);
    func_8000BBD4_main(D_8010AAD0_game_guys_roulette[1], x + 54, 22);
    if (digit != 0 || (u16)(D_8010AAD6_game_guys_roulette.coins / 100) != 0) {
        x += 12;
    }
    func_8000BD50_main(D_8010AAD0_game_guys_roulette[0], D_8010AAD6_game_guys_roulette.coins % 10);
    func_8000BBD4_main(D_8010AAD0_game_guys_roulette[0], x + 54, 22);
}

/* Hand the coins back; a win gets the prize */
void func_801088B0_game_guys_roulette(omObjData* obj) {
    GwPlayer[D_8010AAD6_game_guys_roulette.player].gameCoin = D_8010AAD6_game_guys_roulette.coins;
    if (D_8010AB58_game_guys_roulette == 1) {
        GwPlayer[D_8010AAD6_game_guys_roulette.player].bonusCoin = D_8010A6A4_game_guys_roulette[D_8010AB51_game_guys_roulette];
    } else if (D_8010AB58_game_guys_roulette == 0) {
        GwPlayer[D_8010AAD6_game_guys_roulette.player].bonusCoin = 0;
    }
    WipeCreateOut(0, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80108998_game_guys_roulette;
}

void func_80108998_game_guys_roulette(omObjData* obj) {
    if (WipeStatGet() == 0) {
        osViBlack(0);
        func_80109D14_game_guys_roulette();
        GMesClose();
        func_8005F524_main();
        func_800557A0_main();
        omOvlReturnEx(1);
    }
}

void func_801089EC_game_guys_roulette(omObjData* obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_801088B0_game_guys_roulette;
    }
}

void func_80108A14_game_guys_roulette(GgrSprite* sp, s32 file, s32 attr) {
    sp->id = InitEspriteSlot(func_8000B838_main(file), 0, 1);
    func_8000BC48_main(sp->id, attr);
}

void func_80108A6C_game_guys_roulette(GgrSprite* sp, s32 prio, s32 x, s32 y, s32 w, s32 h, f32 sx, f32 sy) {
    sp->prio = prio;
    sp->x = x;
    sp->y = y;
    sp->w = w;
    sp->h = h;
    sp->sx = sx;
    sp->sy = sy;
}

void func_80108A9C_game_guys_roulette(GgrSprite* sp, u8 show) {
    func_8000BBD4_main(sp->id, sp->x + (sp->w >> 1), sp->y + (sp->h >> 1));
    func_8000BE5C_main(sp->id, sp->sx, sp->sy);
    func_8000BCC8_main(sp->id, (u16)sp->prio);
    if (show == 1) {
        func_8000BB54_main(sp->id);
    } else {
        func_8000BB94_main(sp->id);
    }
}

/* Run the window's choice: mode 0 picks the cursor's entry for the CPU's pad, mode 1 moves the cursor down count
   times first; returns the choice */
s16 func_80108B44_game_guys_roulette(s16 winId, s16 pad, s16 mode, s16 count) {
    s16 keys[4] = { 0, 0, 0, 0 };
    s16 ports[4] = { 1, 2, 4, 8 };
    s16 i;

    switch (mode) {
    case 0:
        keys[pad] = -1;
        func_8005B63C_main(winId, 2, 0);
        func_8005FE54_main(winId, ports[pad]);
        func_8005F744_main(keys[0], keys[1], keys[2], keys[3]);
        break;
    case 1:
        for (i = 0; i < count; i++) {
            keys[pad] = 0x400;
            func_8005F698_main(keys[0], keys[1], keys[2], keys[3],
                               (&D_8010A640_game_guys_roulette[D_8010AB5A_game_guys_roulette])->delay);
        }
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000,
                           D_8010A640_game_guys_roulette[D_8010AB5A_game_guys_roulette].delay);
        break;
    }
    return func_8005E1D8_main(winId, 0, 1);
}
