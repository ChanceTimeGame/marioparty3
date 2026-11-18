#include "ultra64.h"
#include "include_asm.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/util.h"
#include "game/wipe.h"
#include "game/window.h"
#include "game/hmfman.h"
#include "game/esprite.h"
#include "game/sprite.h"
#include "game/data.h"
#include "mallocblock.h"
#include "variables.h"

// sweet surprise A: Game Guy's Sweet Surprise (one player guesses which of two characters wins a pie race to six
// slices; a right guess wins the coins shown for that side)

/* The player who plays (func_80105C34) */
typedef struct GgsPlayer {
    /* 0x00 */ s16 player;
    /* 0x02 */ s16 pad;
    /* 0x04 */ u16 chr;
    /* 0x06 */ s16 cpu;
    /* 0x08 */ s16 difficulty;
    /* 0x0A */ s16 coins; /* shown */
    /* 0x0C */ s16 coins2; /* written back */
} GgsPlayer; /* size 0xE */

/* The CPU's key presses in the window, by CPU level */
typedef struct GgsCpuKey {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 delay;
} GgsCpuKey;

/* A sprite's place on screen, by side */
typedef struct GgsPos {
    s32 x;
    s32 y;
} GgsPos;

/* The tables in the data-only object after 3151F0's .data */
typedef struct GgsOrder {
    s16 v[4];
} GgsOrder;
typedef struct GgsTable6 {
    s16 v[6];
} GgsTable6;

int sprintf(char* s, const char* fmt, ...);
s32 HmfAnimCreate(HmfData*, void*, s32, char*);
void func_80017358_main(s16 arg0, char* arg1, s16 arg2, char* arg3);
void func_80032FC0_main(s32, s32, s32);
void func_80032FF8_main(s32, u8);
void func_8004AB0C_main(s32);
void func_800610E0_main(s16);
void osViBlack(u8);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BD50_main(u16 spriteId, s16 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void GMesMaxTimeGet(s16 mesId, s16 time);
void func_800557A0_main(void);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8000B5F0_main(u8 arg0);
s16 func_8000B638_main(void);
void func_8004A208_main(void);
void func_8005A6B0_main(void);
s32 func_80060880_main(s32 arg0, s32 arg1, s32 arg2);
void func_8005B63C_main(s16, s32, s32);
void func_80061100_main(s16, s32);
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
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[4];
extern u8 D_800D6A58_main;
extern s8 D_800D20A1_main[]; /* stick x by pad */

// LOCAL
void func_801059A0_game_guys_sweet_surprise(void);
s32 func_801059BC_game_guys_sweet_surprise(f32 range);
void func_80105A28_game_guys_sweet_surprise(void);
void func_80105AB8_game_guys_sweet_surprise(void);
void func_80105C18_game_guys_sweet_surprise(void);
void func_80105C34_game_guys_sweet_surprise(void);
void func_80105DCC_game_guys_sweet_surprise(omObjData* obj);
void func_80105F24_game_guys_sweet_surprise(void);
void func_8010612C_game_guys_sweet_surprise(omObjData* obj);
void func_801063F0_game_guys_sweet_surprise(omObjData* obj);
void func_80106594_game_guys_sweet_surprise(void);
void func_8010672C_game_guys_sweet_surprise(void);
void func_80106918_game_guys_sweet_surprise(omObjData* obj);
void func_80106C0C_game_guys_sweet_surprise(void);
void func_80106CB4_game_guys_sweet_surprise(omObjData* obj);
void func_80106D48_game_guys_sweet_surprise(omObjData* obj);
void func_80106EE4_game_guys_sweet_surprise(omObjData* obj);
void func_801071F8_game_guys_sweet_surprise(omObjData* obj);
void func_801072B4_game_guys_sweet_surprise(omObjData* obj);
void func_80107398_game_guys_sweet_surprise(omObjData* obj);
void func_801073F0_game_guys_sweet_surprise(omObjData* obj);
void func_80107418_game_guys_sweet_surprise(omObjData* obj);
void func_80107478_game_guys_sweet_surprise(void);
void func_80107514_game_guys_sweet_surprise(void);
void func_80107550_game_guys_sweet_surprise(void);
void func_80107750_game_guys_sweet_surprise(void);
void func_801077D4_game_guys_sweet_surprise(void);
void func_80107894_game_guys_sweet_surprise(void);
void func_80107A8C_game_guys_sweet_surprise(void);
void func_80107B50_game_guys_sweet_surprise(omObjData* obj);
void func_80107B8C_game_guys_sweet_surprise(void);
void func_80107CAC_game_guys_sweet_surprise(void);
void func_80107F74_game_guys_sweet_surprise(void);
void func_80108218_game_guys_sweet_surprise(void);
void func_80108538_game_guys_sweet_surprise(void);
void func_8010878C_game_guys_sweet_surprise(omObjData* obj);
void func_80108878_game_guys_sweet_surprise(omObjData* obj);
void func_80108AC4_game_guys_sweet_surprise(omObjData* obj);
void func_80108CB8_game_guys_sweet_surprise(omObjData* obj);
void func_80108FE0_game_guys_sweet_surprise(omObjData* obj);
void func_801092F0_game_guys_sweet_surprise(omObjData* obj);
void func_80109AA8_game_guys_sweet_surprise(omObjData* obj);
void func_80109DE4_game_guys_sweet_surprise(omObjData* obj);
void func_8010A604_game_guys_sweet_surprise(omObjData* obj);
void func_8010A784_game_guys_sweet_surprise(omObjData* obj);
void func_8010A820_game_guys_sweet_surprise(omObjData* obj);
void func_8010AA94_game_guys_sweet_surprise(omObjData* obj);
void func_8010AAD8_game_guys_sweet_surprise(omObjData* obj);
void func_8010AB3C_game_guys_sweet_surprise(omObjData* obj);
void func_8010ABD8_game_guys_sweet_surprise(omObjData* obj);
void func_8010AC74_game_guys_sweet_surprise(omObjData* obj);
void func_8010AD04_game_guys_sweet_surprise(omObjData* obj);
s16 func_8010AD94_game_guys_sweet_surprise(s32 file, u16 attr, u16 prio, s16 x, s16 y);
s16 func_8010AE44_game_guys_sweet_surprise(s16 x, s16 y, s16 mes);
void func_8010AEB8_game_guys_sweet_surprise(s16 winId, s16 pad, s16 cpu);
s16 func_8010B004_game_guys_sweet_surprise(s16 winId, s16 pad, s16 cpu, s16 count);
void func_8010B1B4_game_guys_sweet_surprise(s16 winId);
Vec2f func_8010B1F4_game_guys_sweet_surprise(f32 x, f32 y, f32 z);
// 3151F0
void func_8010B250_game_guys_sweet_surprise(s16 x, s16 y);
s16 func_8010B5A8_game_guys_sweet_surprise(void);
void func_8010C244_game_guys_sweet_surprise(void);

/* .data */
extern GgsCpuKey D_8010CB70_game_guys_sweet_surprise[3]; /* by CPU level */
extern s16 D_8010CB76_game_guys_sweet_surprise; /* main step */
extern s16 D_8010CB78_game_guys_sweet_surprise; /* main frames */
extern s16 D_8010CB7A_game_guys_sweet_surprise; /* result message */
extern char* D_8010CB7C_game_guys_sweet_surprise[8]; /* character names (SJIS) */
extern s16 D_8010CB9C_game_guys_sweet_surprise; /* opening step */
extern s16 D_8010CB9E_game_guys_sweet_surprise; /* choose step */
extern s16 D_8010CBA0_game_guys_sweet_surprise; /* key delay */
extern s16 D_8010CBA2_game_guys_sweet_surprise; /* choose timer seconds */
extern s16 D_8010CBA4_game_guys_sweet_surprise; /* choose frames */
extern s16 D_8010CBA6_game_guys_sweet_surprise; /* jump step */
extern s16 D_8010CBA8_game_guys_sweet_surprise; /* start step */
extern s16 D_8010CBAA_game_guys_sweet_surprise; /* start frames */
extern s16 D_8010CBAC_game_guys_sweet_surprise; /* start whistles */
extern s16 D_8010CBAE_game_guys_sweet_surprise; /* race frames */
extern s16 D_8010CBB0_game_guys_sweet_surprise; /* race step */
extern s16 D_8010CBB2_game_guys_sweet_surprise;
extern s16 D_8010CBB4_game_guys_sweet_surprise; /* title blink step */
extern s16 D_8010CBB6_game_guys_sweet_surprise; /* title blink frames */
extern f32 D_8010CBB8_game_guys_sweet_surprise; /* cursor scale */
extern s16 D_8010CBBC_game_guys_sweet_surprise; /* cursor step */
extern s16 D_8010CBBE_game_guys_sweet_surprise;
extern s16 D_8010CBC0_game_guys_sweet_surprise; /* choice shown */
extern f32 D_8010CBC4_game_guys_sweet_surprise; /* face scale */
extern s16 D_8010CBC8_game_guys_sweet_surprise; /* face step */
extern GgsPos D_8010CBCC_game_guys_sweet_surprise[2]; /* face place by choice */
extern s16 D_8010CBDC_game_guys_sweet_surprise; /* pie drop step */
extern f32 D_8010CBE0_game_guys_sweet_surprise; /* pie drop speed */
extern f32 D_8010CBE4_game_guys_sweet_surprise; /* pie drop height */
extern s16 D_8010CBE8_game_guys_sweet_surprise; /* jump step */
extern f32 D_8010CBEC_game_guys_sweet_surprise; /* jump speed */
extern Vec D_8010CBF0_game_guys_sweet_surprise[2]; /* jump target by choice */
extern s16 D_8010CC08_game_guys_sweet_surprise; /* Game Guy's motion shown */
extern s16 D_8010CC0A_game_guys_sweet_surprise; /* Game Guy's jump step */
extern s16 D_8010CC0C_game_guys_sweet_surprise; /* Game Guy's jump frames */
extern f32 D_8010CC10_game_guys_sweet_surprise; /* Game Guy's jump speed */
extern f32 D_8010CC14_game_guys_sweet_surprise; /* Game Guy's shadow scale */
extern s16 D_8010CC18_game_guys_sweet_surprise; /* left bob direction */
extern s16 D_8010CC1A_game_guys_sweet_surprise; /* left bob */
extern s16 D_8010CC1C_game_guys_sweet_surprise; /* left motion shown */
extern f32 D_8010CC20_game_guys_sweet_surprise; /* left shadow scale */
extern s16 D_8010CC24_game_guys_sweet_surprise; /* left step */
extern s16 D_8010CC26_game_guys_sweet_surprise; /* left frames */
extern f32 D_8010CC28_game_guys_sweet_surprise; /* left sway speed */
extern f32 D_8010CC2C_game_guys_sweet_surprise; /* left sway */
extern f32 D_8010CC30_game_guys_sweet_surprise; /* left start x */
extern s16 D_8010CC34_game_guys_sweet_surprise; /* right bob direction */
extern s16 D_8010CC36_game_guys_sweet_surprise; /* right bob */
extern f32 D_8010CC38_game_guys_sweet_surprise; /* right chain step */
extern f32 D_8010CC3C_game_guys_sweet_surprise; /* right chain height */
extern s16 D_8010CC40_game_guys_sweet_surprise; /* right motion shown */
extern f32 D_8010CC44_game_guys_sweet_surprise; /* right shadow scale */
extern s16 D_8010CC48_game_guys_sweet_surprise; /* right step */
extern s16 D_8010CC4A_game_guys_sweet_surprise; /* right frames */
extern f32 D_8010CC4C_game_guys_sweet_surprise; /* right sway speed */
extern f32 D_8010CC50_game_guys_sweet_surprise; /* right sway */
extern f32 D_8010CC54_game_guys_sweet_surprise; /* right start x */
extern s16 D_8010CC58_game_guys_sweet_surprise; /* pie step */
extern s16 D_8010CC5A_game_guys_sweet_surprise; /* pie blink frames */
extern f32 D_8010CC5C_game_guys_sweet_surprise; /* pie scale */
extern GgsOrder D_8010CC70_game_guys_sweet_surprise;
extern GgsTable6 D_8010CC78_game_guys_sweet_surprise; /* prizes */
extern GgsTable6 D_8010CC84_game_guys_sweet_surprise; /* odds of the left side in 10 */

/* .bss */
extern char D_8010CE50_game_guys_sweet_surprise[0x100]; /* result message */
extern Process* D_8010CF50_game_guys_sweet_surprise;
extern Process* D_8010CF54_game_guys_sweet_surprise;
extern GgsPlayer D_8010CF58_game_guys_sweet_surprise;
extern s16 D_8010CF66_game_guys_sweet_surprise; /* the guess was right */
extern s16 D_8010CF68_game_guys_sweet_surprise; /* the choice (0 left, 1 right) */
extern s16 D_8010CF6A_game_guys_sweet_surprise; /* the CPU's choice */
extern s16 D_8010CF6C_game_guys_sweet_surprise; /* the winner */
extern s16 D_8010CF6E_game_guys_sweet_surprise[2]; /* coins by side */
extern s16 D_8010CF72_game_guys_sweet_surprise[2]; /* names by side */
extern s16 D_8010CF78_game_guys_sweet_surprise[36]; /* esprites */
extern omObjData* D_8010CFC0_game_guys_sweet_surprise;
extern omObjData* D_8010CFC4_game_guys_sweet_surprise;
extern omObjData* D_8010CFC8_game_guys_sweet_surprise; /* Game Guy */
extern omObjData* D_8010CFCC_game_guys_sweet_surprise; /* left */
extern omObjData* D_8010CFD0_game_guys_sweet_surprise; /* right */
extern omObjData* D_8010CFD4_game_guys_sweet_surprise;
extern omObjData* D_8010CFD8_game_guys_sweet_surprise;
extern s16 D_8010CFDC_game_guys_sweet_surprise; /* window done */
extern s16 D_8010CFDE_game_guys_sweet_surprise;
extern s16 D_8010CFE0_game_guys_sweet_surprise; /* choosing */
extern s16 D_8010CFE2_game_guys_sweet_surprise; /* drop the pies */
extern s16 D_8010CFE4_game_guys_sweet_surprise[2]; /* slices eaten by side */
extern s16 D_8010CFE8_game_guys_sweet_surprise; /* right pie bounce */
extern s16 D_8010CFEA_game_guys_sweet_surprise; /* left pie bounce */
extern s16 D_8010CFEC_game_guys_sweet_surprise; /* player jumps */
extern s16 D_8010CFEE_game_guys_sweet_surprise; /* Game Guy's motion */
extern s16 D_8010CFF0_game_guys_sweet_surprise; /* Game Guy jumps */
extern s16 D_8010CFF2_game_guys_sweet_surprise; /* left motion */
extern s16 D_8010CFF4_game_guys_sweet_surprise; /* left action */
extern s16 D_8010CFF6_game_guys_sweet_surprise; /* right motion */
extern s16 D_8010CFF8_game_guys_sweet_surprise; /* right action */
extern s16 D_8010CFFA_game_guys_sweet_surprise; /* pie pulse */
extern s16 D_8010CFFC_game_guys_sweet_surprise;
extern s16 D_8010CFFE_game_guys_sweet_surprise; /* odds range */
extern s16 D_8010D000_game_guys_sweet_surprise; /* odds of the left side */
extern s16 D_8010D002_game_guys_sweet_surprise; /* CPU key level */
extern u16 D_8010D004_game_guys_sweet_surprise; /* the left character's model */

#define P D_8010CF58_game_guys_sweet_surprise
#define SPR D_8010CF78_game_guys_sweet_surprise

void func_801059A0_game_guys_sweet_surprise(void) {
    func_80105A28_game_guys_sweet_surprise();
}

s32 func_801059BC_game_guys_sweet_surprise(f32 range) {
    u8 hi = rand8();
    u8 lo = rand8();
    s32 shifted = (hi << 8);
    s32 r = ((lo | shifted) / 65536.0f) * range;

    return r;
}

void func_80105A28_game_guys_sweet_surprise(void) {
    Hu3DAnimInit(0x20);
    func_800142A0_main(0x20);
    omInitObjMan(0x20, 0x20);
    func_8004A208_main();
    func_80105AB8_game_guys_sweet_surprise();
    func_80105C18_game_guys_sweet_surprise();
    func_80105C34_game_guys_sweet_surprise();
    omAddObj(1000, 0, 0, -1, func_80105DCC_game_guys_sweet_surprise);
    omAddObj(2000, 0, 0, -1, func_801073F0_game_guys_sweet_surprise);
}

void func_80105AB8_game_guys_sweet_surprise(void) {
    s16 cam;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(cam, 12.37f, 2000.0f, 8000.0f);
    CZoom = 3275.61f;
    CRot.x = -8.7f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 187.6f;
    Center.z = -16.89f;
}

void func_80105C18_game_guys_sweet_surprise(void) {
    func_8005A6B0_main();
}

/* The player in group 0 plays */
void func_80105C34_game_guys_sweet_surprise(void) {
    s16 i = 0;
    GgsOrder order = D_8010CC70_game_guys_sweet_surprise;

    for (; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    if (i < 4) {
        P.player = order.v[i];
    } else {
        P.player = order.v[0];
    }
    P.pad = GwPlayer[P.player].pad;
    P.chr = GwPlayer[P.player].chr;
    if (GwPlayer[P.player].stat & 1) {
        P.cpu = 1;
        P.difficulty = GwPlayer[P.player].cpu_difficulty;
        D_8010D002_game_guys_sweet_surprise = GwCommon.unkA0;
        if (D_8010D002_game_guys_sweet_surprise <= 0) {
            D_8010D002_game_guys_sweet_surprise = 0;
        } else if (D_8010D002_game_guys_sweet_surprise >= 2) {
            D_8010D002_game_guys_sweet_surprise = 2;
        }
    } else {
        P.cpu = 0;
        P.difficulty = 0;
    }
    P.coins = P.coins2 = GwPlayer[P.player].gameCoin;
}

void func_80105DCC_game_guys_sweet_surprise(omObjData* obj) {
    func_8010B250_game_guys_sweet_surprise(160, 180);
    func_80105F24_game_guys_sweet_surprise();
    D_8010CFC0_game_guys_sweet_surprise = omAddObj(10, 10, 10, -1, func_80107418_game_guys_sweet_surprise);
    D_8010CFC4_game_guys_sweet_surprise = omAddObj(20, 10, 10, -1, func_8010878C_game_guys_sweet_surprise);
    D_8010CFC8_game_guys_sweet_surprise = omAddObj(30, 10, 20, -1, func_80108AC4_game_guys_sweet_surprise);
    D_8010CFCC_game_guys_sweet_surprise = omAddObj(40, 10, 20, -1, func_80108FE0_game_guys_sweet_surprise);
    D_8010CFD0_game_guys_sweet_surprise = omAddObj(50, 10, 20, -1, func_80109AA8_game_guys_sweet_surprise);
    D_8010CFD4_game_guys_sweet_surprise = omAddObj(60, 10, 10, -1, func_8010A604_game_guys_sweet_surprise);
    D_8010CFD8_game_guys_sweet_surprise = omAddObj(70, 10, 10, -1, func_8010AAD8_game_guys_sweet_surprise);
    obj->func = func_8010612C_game_guys_sweet_surprise;
}

/* The CPU's guess, the prize and the odds */
void func_80105F24_game_guys_sweet_surprise(void) {
    GgsTable6 prizes = D_8010CC78_game_guys_sweet_surprise;
    GgsTable6 odds = D_8010CC84_game_guys_sweet_surprise;
    s16 r;

    D_8010CF66_game_guys_sweet_surprise = 0;
    D_8010CF68_game_guys_sweet_surprise = 0;
    if (P.cpu == 1) {
        D_8010CF6A_game_guys_sweet_surprise = 0;
        if (P.difficulty == 0) {
            D_8010CF6A_game_guys_sweet_surprise = func_801059BC_game_guys_sweet_surprise(2.0f);
        } else if (P.difficulty == 1) {
            if (func_801059BC_game_guys_sweet_surprise(4.0f) == 0) {
                D_8010CF6A_game_guys_sweet_surprise = 1;
            }
        } else if (P.difficulty == 2) {
            if (func_801059BC_game_guys_sweet_surprise(8.0f) == 0) {
                D_8010CF6A_game_guys_sweet_surprise = 1;
            }
        } else if (P.difficulty == 3) {
            if (func_801059BC_game_guys_sweet_surprise(16.0f) == 0) {
                D_8010CF6A_game_guys_sweet_surprise = 1;
            }
        }
    }
    r = func_801059BC_game_guys_sweet_surprise(5.0f) + 1;
    D_8010CF6E_game_guys_sweet_surprise[0] = 2;
    D_8010CF6E_game_guys_sweet_surprise[1] = prizes.v[r];
    while (D_8010CF72_game_guys_sweet_surprise[0] == D_8010CF72_game_guys_sweet_surprise[1]) {
        D_8010CF72_game_guys_sweet_surprise[0] = func_801059BC_game_guys_sweet_surprise(10.0f);
        D_8010CF72_game_guys_sweet_surprise[1] = func_801059BC_game_guys_sweet_surprise(10.0f);
    }
    D_8010CFFE_game_guys_sweet_surprise = 10;
    D_8010D000_game_guys_sweet_surprise = odds.v[r];
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CC90_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CC9C_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCAC_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCB4_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCC0_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCCC_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCD8_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCE4_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCF0_game_guys_sweet_surprise);

extern char D_8010CCF0_game_guys_sweet_surprise[]; /* "%s LOST!" (SJIS) */

/* The main sequence */
void func_8010612C_game_guys_sweet_surprise(omObjData* obj) {
    switch (D_8010CB76_game_guys_sweet_surprise) {
    case 0:
        WipeCreateIn(0xFF, 16);
        D_8010CB76_game_guys_sweet_surprise++;
        break;
    case 1:
        obj->func = func_801063F0_game_guys_sweet_surprise;
        D_8010CB76_game_guys_sweet_surprise++;
        break;
    case 2:
        if (++D_8010CB78_game_guys_sweet_surprise == 1) {
            GMesCreate(9);
        } else if (D_8010CB78_game_guys_sweet_surprise == 70) {
            D_8010CFEE_game_guys_sweet_surprise = 3;
        } else if (D_8010CB78_game_guys_sweet_surprise == 80) {
            D_8010CFFA_game_guys_sweet_surprise = 1;
            HuAudFXPlay(0x538);
        } else if (GMesStatGet() == 0) {
            D_8010CFEE_game_guys_sweet_surprise = 2;
            D_8010CB76_game_guys_sweet_surprise++;
            D_8010CB78_game_guys_sweet_surprise = 0;
        }
        break;
    case 3:
        obj->func = func_80106D48_game_guys_sweet_surprise;
        D_8010CB76_game_guys_sweet_surprise++;
        break;
    case 4:
        if (++D_8010CB78_game_guys_sweet_surprise == 1) {
            D_8010CFF4_game_guys_sweet_surprise = 3;
            D_8010CFF8_game_guys_sweet_surprise = 3;
            GMesCreate(0x14);
            HuAudSeqFadeOut(120);
        } else if (GMesStatGet() == 0) {
            D_8010CB76_game_guys_sweet_surprise++;
            D_8010CB78_game_guys_sweet_surprise = 0;
        }
        break;
    case 5:
        obj->func = func_801071F8_game_guys_sweet_surprise;
        D_8010CB76_game_guys_sweet_surprise++;
        break;
    case 6:
        if (++D_8010CB78_game_guys_sweet_surprise == 1) {
            switch (D_8010CF66_game_guys_sweet_surprise) {
            case 1:
                HuAudFXPlay(0x517);
                HuAudSeqPlay(0x73);
                D_8010CB7A_game_guys_sweet_surprise = GMesCreate(0x16, P.chr);
                GMesMaxTimeGet(D_8010CB7A_game_guys_sweet_surprise, 120);
                break;
            case 0:
                HuAudFXPlay(0x518);
                HuAudSeqPlay(0x71);
                sprintf(D_8010CE50_game_guys_sweet_surprise, D_8010CCF0_game_guys_sweet_surprise,
                        D_8010CB7C_game_guys_sweet_surprise[P.chr]);
                D_8010CB7A_game_guys_sweet_surprise =
                    GMesCreate(0x19, D_8010CE50_game_guys_sweet_surprise, 160, 120, 1.0, 1.0, 1);
                GMesMaxTimeGet(D_8010CB7A_game_guys_sweet_surprise, 120);
                break;
            }
        } else if (D_8010CB78_game_guys_sweet_surprise >= 135) {
            D_8010CB76_game_guys_sweet_surprise++;
            D_8010CB78_game_guys_sweet_surprise = 0;
        }
        break;
    case 7:
        obj->func = func_801072B4_game_guys_sweet_surprise;
        break;
    }
}

/* The opening: the title effect, the rules window, the names window, the choice */
void func_801063F0_game_guys_sweet_surprise(omObjData* obj) {
    switch (D_8010CB9C_game_guys_sweet_surprise) {
    case 0:
        if (WipeStatGet() != 1) {
            D_8010CB9C_game_guys_sweet_surprise++;
        }
        break;
    case 1:
        D_8010CB9C_game_guys_sweet_surprise += func_8010B5A8_game_guys_sweet_surprise();
        break;
    case 2:
        D_8010CFDC_game_guys_sweet_surprise = 0;
        D_8010CF50_game_guys_sweet_surprise = omAddPrcObj(func_80106594_game_guys_sweet_surprise, 0x3F00, 0x800, 0);
        D_8010CB9C_game_guys_sweet_surprise++;
        break;
    case 3:
        if (D_8010CFDC_game_guys_sweet_surprise == 1) {
            HuPrcKill(D_8010CF50_game_guys_sweet_surprise);
            D_8010CFDC_game_guys_sweet_surprise = 0;
            D_8010CB9C_game_guys_sweet_surprise++;
        }
        break;
    case 4:
        D_8010CF54_game_guys_sweet_surprise = omAddPrcObj(func_8010672C_game_guys_sweet_surprise, 0x3F00, 0x800, 0);
        D_8010CB9C_game_guys_sweet_surprise++;
        break;
    case 5:
        obj->func = func_80106918_game_guys_sweet_surprise;
        D_8010CB9C_game_guys_sweet_surprise++;
        break;
    case 6:
        D_8010CFDC_game_guys_sweet_surprise = 0;
        D_8010CF50_game_guys_sweet_surprise = omAddPrcObj(func_80106C0C_game_guys_sweet_surprise, 0x3F00, 0x800, 0);
        D_8010CB9C_game_guys_sweet_surprise++;
        break;
    case 7:
        if (D_8010CFDC_game_guys_sweet_surprise == 1) {
            HuPrcKill(D_8010CF50_game_guys_sweet_surprise);
            D_8010CFDC_game_guys_sweet_surprise = 0;
            D_8010CB9C_game_guys_sweet_surprise++;
        }
        break;
    case 8:
        obj->func = func_80106CB4_game_guys_sweet_surprise;
        D_8010CB9C_game_guys_sweet_surprise++;
        break;
    case 9:
        HuPrcKill(D_8010CF54_game_guys_sweet_surprise);
        obj->func = func_8010612C_game_guys_sweet_surprise;
        break;
    }
}

/* The rules window */
void func_80106594_game_guys_sweet_surprise(void) {
    s16 r;
    s16 done = 0;
    s16 winId;

    D_8010CFDC_game_guys_sweet_surprise = 0;
    winId = func_8010AE44_game_guys_sweet_surprise(0x82, 0x96, 0xC);
    HuAudFXPlay(0x11D);
    func_80060C14_main(winId, 1);
    func_8005B43C_main(winId, 0x2E00, -1, -1);
    func_8010AEB8_game_guys_sweet_surprise(winId, P.pad, P.cpu);
    func_8005B43C_main(winId, 0x2E01, -1, -1);
    while (done == 0) {
        r = func_8010B004_game_guys_sweet_surprise(winId, P.pad, P.cpu, 1);
        switch (r) {
        case 0:
            func_8005B43C_main(winId, 0x2E02, -1, -1);
            func_8010AEB8_game_guys_sweet_surprise(winId, P.pad, P.cpu);
        case 1:
            done = 1;
            break;
        }
        HuPrcVSleep();
    }
    func_8005B43C_main(winId, 0x2E03, -1, -1);
    func_8010AEB8_game_guys_sweet_surprise(winId, P.pad, P.cpu);
    func_8010B1B4_game_guys_sweet_surprise(winId);
    D_8010CFDC_game_guys_sweet_surprise = 1;
    while (1) {
        HuPrcVSleep();
    }
}

/* The two name windows, the chosen one lit */
void func_8010672C_game_guys_sweet_surprise(void) {
    s16 left;
    s16 right;
    s16 done = 0;

    left = func_8005A968_main(37, 180, 106, 34, 0, 1);
    func_8005FBF8_main(left, 0, 0, 0xFF);
    func_8005BEE0_main(left, 150);
    func_8005B43C_main(left, D_8010CF72_game_guys_sweet_surprise[0] + 0x2E07, -1, -1);
    right = func_8005A968_main(177, 180, 106, 34, 0, 1);
    func_8005FBF8_main(right, 0xFF, 0, 0);
    func_8005BEE0_main(right, 150);
    func_8005B43C_main(right, D_8010CF72_game_guys_sweet_surprise[1] + 0x2E07, -1, -1);
    func_8005FE90_main(left);
    func_8005FE90_main(right);
    while (TRUE) {
        if (D_8010CFE0_game_guys_sweet_surprise == 1) {
            switch (D_8010CF68_game_guys_sweet_surprise) {
            case 0:
                func_8005FFA8_main(left);
                func_8005FE90_main(right);
                break;
            case 1:
                func_8005FE90_main(left);
                func_8005FFA8_main(right);
                break;
            }
        } else if (D_8010CFE0_game_guys_sweet_surprise == 0 && D_8010CFDE_game_guys_sweet_surprise == 1) {
            done = 1;
        }
        HuPrcVSleep();
        if (done != 0) {
            break;
        }
    }
    func_8005F364_main(left);
    func_8005F364_main(right);
    while (1) {
        HuPrcVSleep();
    }
}

/* The choice: left or right with the stick, A to choose; the CPU moves to its pick */
void func_80106918_game_guys_sweet_surprise(omObjData* obj) {
    s16 dir = 0;

    switch (D_8010CB9E_game_guys_sweet_surprise) {
    case 0:
        GMesCreate(0x1A, 10, 156, 56);
        D_8010CBA2_game_guys_sweet_surprise = 10;
        D_8010CBA4_game_guys_sweet_surprise = 0;
        D_800D6A58_main = 0;
        D_8010CFE0_game_guys_sweet_surprise = 1;
        D_8010CB9E_game_guys_sweet_surprise++;
        break;
    case 1:
        if (D_8010CBA0_game_guys_sweet_surprise <= 0) {
            switch (P.cpu) {
            case 0:
                if (D_800D20A1_main[P.pad] < -64 && D_8010CF68_game_guys_sweet_surprise != 1) {
                    dir = 1;
                    D_8010CBA0_game_guys_sweet_surprise = 5;
                }
                if (D_800D20A1_main[P.pad] > 64 && D_8010CF68_game_guys_sweet_surprise != 0) {
                    dir = -1;
                    D_8010CBA0_game_guys_sweet_surprise = 5;
                }
                if (D_800D5558_main[P.pad] & 0x8000) {
                    dir = 10;
                }
                break;
            case 1:
                dir = 1;
                if (D_8010CF6A_game_guys_sweet_surprise != D_8010CF68_game_guys_sweet_surprise) {
                    D_8010CBA0_game_guys_sweet_surprise = 30;
                } else {
                    dir = 10;
                }
                break;
            }
        } else {
            D_8010CBA0_game_guys_sweet_surprise--;
        }
        if (D_8010CBA4_game_guys_sweet_surprise++ >= 30) {
            D_8010CBA2_game_guys_sweet_surprise--;
            D_8010CBA4_game_guys_sweet_surprise = 0;
            func_8003F578_main(D_8010CBA2_game_guys_sweet_surprise);
            if (D_8010CBA2_game_guys_sweet_surprise == 0) {
                dir = 10;
            } else if (D_8010CBA2_game_guys_sweet_surprise < 6) {
                HuAudFXPlay(8);
            }
        }
        switch (dir) {
        case 1:
            HuAudFXPlay(1);
            D_8010CF68_game_guys_sweet_surprise = 1;
            break;
        case -1:
            HuAudFXPlay(1);
            D_8010CF68_game_guys_sweet_surprise = 0;
            break;
        case 10:
            HuAudFXPlay(3);
            omVibrate(P.player, 10, 0, 10);
            D_8010CFEC_game_guys_sweet_surprise = 1;
            D_8010CFE0_game_guys_sweet_surprise = 0;
            D_8010CB9E_game_guys_sweet_surprise++;
            break;
        }
        break;
    case 2:
        D_800D6A58_main = 1;
        func_8003F5C0_main();
        obj->func = func_801063F0_game_guys_sweet_surprise;
        break;
    }
}

/* "You chose ..." */
void func_80106C0C_game_guys_sweet_surprise(void) {
    s16 winId;

    winId = func_8010AE44_game_guys_sweet_surprise(0x82, 0x96, 0xC);
    func_80060C14_main(winId, 1);
    func_8005B43C_main(winId, 0x2E04, -1, -1);
    func_8005B6BC_main(winId, D_8010CF68_game_guys_sweet_surprise + 0x2E05, 0);
    func_8010AEB8_game_guys_sweet_surprise(winId, P.pad, P.cpu);
    func_8010B1B4_game_guys_sweet_surprise(winId);
    D_8010CFDC_game_guys_sweet_surprise = 1;
    while (1) {
        HuPrcVSleep();
    }
}

/* Game Guy jumps and the pies drop */
void func_80106CB4_game_guys_sweet_surprise(omObjData* obj) {
    switch (D_8010CBA6_game_guys_sweet_surprise) {
    case 0:
        D_8010CFF0_game_guys_sweet_surprise = 1;
        D_8010CFFC_game_guys_sweet_surprise = 1;
        D_8010CBA6_game_guys_sweet_surprise++;
        break;
    case 1:
        if (D_8010CFF0_game_guys_sweet_surprise == 0) {
            D_8010CFE2_game_guys_sweet_surprise = 1;
            D_8010CBA6_game_guys_sweet_surprise++;
        }
        break;
    case 2:
        obj->func = func_801063F0_game_guys_sweet_surprise;
        break;
    }
}

/* The start whistle, then the race until Game Guy's motion ends */
void func_80106D48_game_guys_sweet_surprise(omObjData* obj) {
    switch (D_8010CBA8_game_guys_sweet_surprise) {
    case 0:
        obj->func = func_80106EE4_game_guys_sweet_surprise;
        D_8010CBA8_game_guys_sweet_surprise++;
        break;
    case 1:
        if (D_8010CBAA_game_guys_sweet_surprise++ >= 8 && D_8010CBAA_game_guys_sweet_surprise % 5 == 0) {
            if (D_8010CBAC_game_guys_sweet_surprise == 0) {
                HuAudFXPlay(0x539);
            }
            if (D_8010CBAC_game_guys_sweet_surprise++ < 4) {
                D_8010CFFA_game_guys_sweet_surprise = 1;
            }
        }
        if (D_800CCF58_main[HmfModelData[D_8010CFC8_game_guys_sweet_surprise->model[0]].unk02].unk02 <=
            HmfModelData[D_8010CFC8_game_guys_sweet_surprise->model[0]].unk40) {
            D_8010CBA8_game_guys_sweet_surprise++;
        }
        break;
    case 2:
        D_8010CFEE_game_guys_sweet_surprise = 0;
        obj->func = func_8010612C_game_guys_sweet_surprise;
        break;
    }
}

/* The race: every 30 frames one side eats one or two slices, the left side by the odds; the first to six wins */
void func_80106EE4_game_guys_sweet_surprise(omObjData* obj) {
    s16 i;

    switch (D_8010CBB0_game_guys_sweet_surprise) {
    case 0:
        D_8010CFF2_game_guys_sweet_surprise = 2;
        D_8010CFF6_game_guys_sweet_surprise = 2;
        D_8010CBB0_game_guys_sweet_surprise++;
        break;
    case 1:
        if (D_8010CBAE_game_guys_sweet_surprise++ >= 30) {
            if (func_801059BC_game_guys_sweet_surprise(D_8010CFFE_game_guys_sweet_surprise) <
                D_8010D000_game_guys_sweet_surprise) {
                if (func_801059BC_game_guys_sweet_surprise(10.0f) < 6) {
                    D_8010CFE4_game_guys_sweet_surprise[0] += 1;
                } else {
                    D_8010CFE4_game_guys_sweet_surprise[0] += 2;
                }
                if (D_8010CF68_game_guys_sweet_surprise == 0) {
                    omVibrate(P.player, 10, 0, 10);
                }
                D_8010CFF2_game_guys_sweet_surprise = 3;
                D_8010CFF6_game_guys_sweet_surprise = 2;
            } else {
                if (func_801059BC_game_guys_sweet_surprise(10.0f) < 6) {
                    D_8010CFE4_game_guys_sweet_surprise[1] += 1;
                } else {
                    D_8010CFE4_game_guys_sweet_surprise[1] += 2;
                }
                if (D_8010CF68_game_guys_sweet_surprise == 1) {
                    omVibrate(P.player, 10, 0, 10);
                }
                D_8010CFE8_game_guys_sweet_surprise = 1;
                D_8010CFF2_game_guys_sweet_surprise = 2;
                D_8010CFF6_game_guys_sweet_surprise = 3;
            }
            D_8010CBAE_game_guys_sweet_surprise = 0;
        } else if (D_8010CBAE_game_guys_sweet_surprise % 7 == 0) {
            if (func_801059BC_game_guys_sweet_surprise(2.0f) == 0) {
                D_8010CFEA_game_guys_sweet_surprise = 1;
            } else {
                D_8010CFE8_game_guys_sweet_surprise = 1;
            }
        }
        break;
    }
    for (i = 0; i < 2; i++) {
        if (D_8010CFE4_game_guys_sweet_surprise[i] >= 6) {
            D_8010CFE4_game_guys_sweet_surprise[i] = 6;
        }
    }
    for (i = 0; i < 2; i++) {
        if (D_8010CFE4_game_guys_sweet_surprise[i] == 6) {
            D_8010CFF2_game_guys_sweet_surprise = 0;
            D_8010CFF6_game_guys_sweet_surprise = 0;
            D_8010CF6C_game_guys_sweet_surprise = i;
            D_8010CFEE_game_guys_sweet_surprise = 4;
            obj->func = func_80106D48_game_guys_sweet_surprise;
        }
    }
}

/* The winner celebrates */
void func_801071F8_game_guys_sweet_surprise(omObjData* obj) {
    if (D_8010CBB2_game_guys_sweet_surprise == 0) {
        if (D_8010CF6C_game_guys_sweet_surprise == 0) {
            D_8010CFF6_game_guys_sweet_surprise = 1;
            D_8010CFF4_game_guys_sweet_surprise = 1;
            D_8010CFF8_game_guys_sweet_surprise = 2;
        } else {
            D_8010CFF2_game_guys_sweet_surprise = 1;
            D_8010CFF4_game_guys_sweet_surprise = 2;
            D_8010CFF8_game_guys_sweet_surprise = 1;
        }
        if (D_8010CF68_game_guys_sweet_surprise == D_8010CF6C_game_guys_sweet_surprise) {
            D_8010CF66_game_guys_sweet_surprise = 1;
        } else {
            D_8010CF66_game_guys_sweet_surprise = 0;
        }
        HuAudSeqFadeOut(30);
        obj->func = func_8010612C_game_guys_sweet_surprise;
    }
}

/* The result to the board, then fade out */
void func_801072B4_game_guys_sweet_surprise(omObjData* obj) {
    GwPlayer[P.player].gameCoin = P.coins2;
    switch (D_8010CF66_game_guys_sweet_surprise) {
    case 1:
        GwPlayer[P.player].bonusCoin = D_8010CF6E_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise];
        break;
    case 0:
        GwPlayer[P.player].bonusCoin = 0;
        break;
    }
    WipeCreateOut(0, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80107398_game_guys_sweet_surprise;
}

void func_80107398_game_guys_sweet_surprise(omObjData* obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        func_8010C244_game_guys_sweet_surprise();
        GMesClose();
        func_8005F524_main();
        func_800557A0_main();
        omOvlReturnEx(1);
    }
}

void func_801073F0_game_guys_sweet_surprise(omObjData* obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_801072B4_game_guys_sweet_surprise;
    }
}

/* The screen sprites */
void func_80107418_game_guys_sweet_surprise(omObjData* obj) {
    func_80107478_game_guys_sweet_surprise();
    func_80107514_game_guys_sweet_surprise();
    func_80107550_game_guys_sweet_surprise();
    func_80107750_game_guys_sweet_surprise();
    func_801077D4_game_guys_sweet_surprise();
    func_80107894_game_guys_sweet_surprise();
    func_80107A8C_game_guys_sweet_surprise();
    obj->func = func_80107B50_game_guys_sweet_surprise;
}

void func_80107478_game_guys_sweet_surprise(void) {
    SPR[0] = func_8010AD94_game_guys_sweet_surprise(0x660000, 0x4000, 1000, 160, 120);
    SPR[1] = func_8010AD94_game_guys_sweet_surprise(0x660001, 0x4000, 1000, 160, 120);
    SPR[2] = func_8010AD94_game_guys_sweet_surprise(0x660002, 0x4000, 1000, 160, 120);
    func_8000BB94_main(SPR[1]);
    func_8000BB94_main(SPR[2]);
}

void func_80107514_game_guys_sweet_surprise(void) {
    SPR[5] = func_8010AD94_game_guys_sweet_surprise(0x660003, 0, 900, 269, 44);
}

/* The prize sign of each side */
/* The prize coins shown by each side */
void func_80107550_game_guys_sweet_surprise(void) {
    s16 i = 0;
    s16 y = 33;
    s16 x = 280;
    s16 n = 10;

    for (; i < 2; i++) {
        switch (D_8010CF6E_game_guys_sweet_surprise[i]) {
        case 4:
            SPR[n + i] = func_8010AD94_game_guys_sweet_surprise(0x66000A, 0, 800, x, y + i * 22);
            break;
        case 8:
            SPR[n + i] = func_8010AD94_game_guys_sweet_surprise(0x660006, 0, 800, x, y + i * 22);
            break;
        case 16:
            SPR[n + i] = func_8010AD94_game_guys_sweet_surprise(0x660007, 0, 800, x, y + i * 22);
            break;
        case 32:
            SPR[n + i] = func_8010AD94_game_guys_sweet_surprise(0x660008, 0, 800, x, y + i * 22);
            break;
        case 64:
            SPR[n + i] = func_8010AD94_game_guys_sweet_surprise(0x660009, 0, 800, x, y + i * 22);
            break;
        }
    }
}

void func_80107750_game_guys_sweet_surprise(void) {
    s16 i = 15;

    SPR[i] = func_8010AD94_game_guys_sweet_surprise(0x660004, 0, 800, 257, 33);
    SPR[i + 1] = func_8010AD94_game_guys_sweet_surprise(0x660005, 0, 800, 257, 55);
    func_8000BB94_main(SPR[i]);
    func_8000BB94_main(SPR[i + 1]);
    D_8010CFDE_game_guys_sweet_surprise = 0;
}

/* The player's face */
void func_801077D4_game_guys_sweet_surprise(void) {
    s16 i = 20;
    s32 chr = GwPlayer[P.player].chr;
    s32 faces[8] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };

    SPR[i] = func_8010AD94_game_guys_sweet_surprise(faces[chr] | 0x210000, 0, 700, 0, 0);
    func_8000BB94_main(SPR[i]);
    D_8010CFE0_game_guys_sweet_surprise = 0;
}

/* The slice counters over the pies */
void func_80107894_game_guys_sweet_surprise(void) {
    Vec2f pos;
    s16 i = 0;
    s16 n = 25;

    for (; i < 2; i++) {
        void* data = DataRead(0x66000B);
        s16 spr = func_80055810_main(data);

        DataClose(data);
        SPR[n + i] = HuSprGrpCreate(1, 0);
        func_80055024_main(SPR[n + i], 0, spr, 0);
        HuSprPriSet(SPR[n + i], 0, 100);
        if (i == 0) {
            HuSprAttrReset(SPR[n + i], 0, 0xFFFF);
            HuSprAttrSet(SPR[n + i], 0, 0);
            pos = func_8010B1F4_game_guys_sweet_surprise(-80.0f, 600.0f, -400.0f);
            func_80054904_main(SPR[n + i], 0, pos.x, pos.y);
        } else if (i == 1) {
            HuSprAttrReset(SPR[n + i], 0, 0xFFFF);
            HuSprAttrSet(SPR[n + i], 0, 1);
            pos = func_8010B1F4_game_guys_sweet_surprise(80.0f, 600.0f, -400.0f);
            func_80054904_main(SPR[n + i], 0, pos.x, pos.y);
        }
        D_8010CFE4_game_guys_sweet_surprise[i] = 0;
    }
}

/* The coin counter */
void func_80107A8C_game_guys_sweet_surprise(void) {
    s16 n = 30;

    SPR[n] = func_8010AD94_game_guys_sweet_surprise(0x21001A, 0, 600, 30, 22);
    SPR[n + 1] = func_8010AD94_game_guys_sweet_surprise(0x21001B, 0, 600, 42, 22);
    SPR[n + 2] = func_8010AD94_game_guys_sweet_surprise(0x31, 0, 600, 54, 22);
    SPR[n + 3] = func_8010AD94_game_guys_sweet_surprise(0x31, 0, 600, 66, 22);
    SPR[n + 4] = func_8010AD94_game_guys_sweet_surprise(0x31, 0, 600, 78, 22);
}

void func_80107B50_game_guys_sweet_surprise(omObjData* obj) {
    func_80107B8C_game_guys_sweet_surprise();
    func_80107CAC_game_guys_sweet_surprise();
    func_80107F74_game_guys_sweet_surprise();
    func_80108218_game_guys_sweet_surprise();
    func_80108538_game_guys_sweet_surprise();
}

/* The title's two lit frames blink */
void func_80107B8C_game_guys_sweet_surprise(void) {
    s16 i = 0;

    if (D_8010CBB6_game_guys_sweet_surprise++ >= 5) {
        D_8010CBB6_game_guys_sweet_surprise = 0;
        switch (D_8010CBB4_game_guys_sweet_surprise) {
        case 0:
            func_8000BB54_main(SPR[i + 1]);
            func_8000BB94_main(SPR[i + 2]);
            D_8010CBB4_game_guys_sweet_surprise++;
            break;
        case 1:
            func_8000BB94_main(SPR[i + 1]);
            func_8000BB54_main(SPR[i + 2]);
            D_8010CBB4_game_guys_sweet_surprise++;
            break;
        case 2:
            func_8000BB94_main(SPR[i + 1]);
            func_8000BB94_main(SPR[i + 2]);
            D_8010CBB4_game_guys_sweet_surprise = 0;
            break;
        }
    }
}

/* The cursor over the chosen side pulses */
void func_80107CAC_game_guys_sweet_surprise(void) {
    s16 n = 15;

    if (D_8010CFDE_game_guys_sweet_surprise == 1) {
        switch (D_8010CBBC_game_guys_sweet_surprise) {
        case 0:
            D_8010CBB8_game_guys_sweet_surprise = 1.0f;
            D_8010CBBE_game_guys_sweet_surprise = 0;
            D_8010CBBC_game_guys_sweet_surprise++;
            break;
        case 1:
            func_8000BE5C_main(SPR[n + D_8010CF68_game_guys_sweet_surprise], D_8010CBB8_game_guys_sweet_surprise,
                               D_8010CBB8_game_guys_sweet_surprise);
            if (D_8010CBB8_game_guys_sweet_surprise < 1.5f) {
                D_8010CBB8_game_guys_sweet_surprise += 0.1f;
            } else {
                D_8010CBBC_game_guys_sweet_surprise++;
            }
            break;
        case 2:
            func_8000BE5C_main(SPR[n + D_8010CF68_game_guys_sweet_surprise], D_8010CBB8_game_guys_sweet_surprise,
                               D_8010CBB8_game_guys_sweet_surprise);
            if (D_8010CBB8_game_guys_sweet_surprise > 1.1f) {
                D_8010CBB8_game_guys_sweet_surprise -= 0.1f;
            } else {
                D_8010CBBC_game_guys_sweet_surprise--;
            }
            break;
        }
        if (D_8010CFE0_game_guys_sweet_surprise == 0) {
            D_8010CBB8_game_guys_sweet_surprise = 1.5f;
            D_8010CBBC_game_guys_sweet_surprise += 2;
            func_8000BE5C_main(SPR[n + D_8010CF68_game_guys_sweet_surprise], 1.5f, 1.5f);
        }
        if (D_8010CBC0_game_guys_sweet_surprise != D_8010CF68_game_guys_sweet_surprise) {
            switch (D_8010CF68_game_guys_sweet_surprise) {
            case 0:
                func_8000BB54_main(SPR[n]);
                func_8000BB94_main(SPR[n + 1]);
                D_8010CBBC_game_guys_sweet_surprise = 0;
                break;
            case 1:
                func_8000BB94_main(SPR[n]);
                func_8000BB54_main(SPR[n + 1]);
                D_8010CBBC_game_guys_sweet_surprise = 0;
                break;
            }
            func_8000BE5C_main(SPR[n], 1.0f, 1.0f);
            func_8000BE5C_main(SPR[n + 1], 1.0f, 1.0f);
            D_8010CBC0_game_guys_sweet_surprise = D_8010CF68_game_guys_sweet_surprise;
        }
    }
}

/* The player's face grows in over the chosen side, and shrinks away after the choice */
void func_80107F74_game_guys_sweet_surprise(void) {
    s16 n = 20;

    if (D_8010CFE0_game_guys_sweet_surprise == 1) {
        switch (D_8010CBC8_game_guys_sweet_surprise) {
        case 0:
            func_8000BBD4_main(SPR[n], D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].x,
                               D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y);
            func_8000BE5C_main(SPR[n], 0.0f, 0.0f);
            func_8000BB54_main(SPR[n]);
            D_8010CFDE_game_guys_sweet_surprise = 1;
            D_8010CBC8_game_guys_sweet_surprise++;
            break;
        case 1:
            D_8010CBC4_game_guys_sweet_surprise += 0.25f;
            func_8000BE5C_main(SPR[n], D_8010CBC4_game_guys_sweet_surprise, D_8010CBC4_game_guys_sweet_surprise);
            if (D_8010CBC4_game_guys_sweet_surprise >= 1.0f) {
                D_8010CBC4_game_guys_sweet_surprise = 1.0f;
                D_8010CBC8_game_guys_sweet_surprise++;
            }
            break;
        case 2:
            func_8000BBD4_main(SPR[n], D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].x,
                               D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y);
            break;
        }
    } else if (D_8010CFE0_game_guys_sweet_surprise == 0) {
        switch (D_8010CBC8_game_guys_sweet_surprise) {
        case 2:
            func_8000BBD4_main(SPR[n], D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].x,
                               D_8010CBCC_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y);
            func_8000BE5C_main(SPR[n], 1.0f, 1.0f);
            D_8010CBC8_game_guys_sweet_surprise++;
            break;
        case 3:
            D_8010CBC4_game_guys_sweet_surprise -= 0.25f;
            func_8000BE5C_main(SPR[n], D_8010CBC4_game_guys_sweet_surprise, D_8010CBC4_game_guys_sweet_surprise);
            if (D_8010CBC4_game_guys_sweet_surprise <= 0.0f) {
                D_8010CBC4_game_guys_sweet_surprise = 0.0f;
                D_8010CBC8_game_guys_sweet_surprise++;
            }
            break;
        case 4:
            func_8000BB94_main(SPR[n]);
            D_8010CBC8_game_guys_sweet_surprise++;
            break;
        }
    }
}

/* The slice counters, and the pies dropping in */
void func_80108218_game_guys_sweet_surprise(void) {
    Vec2f pos;
    s16 i = 0;
    s16 n = 25;

    for (; i < 2; i++) {
        if (D_8010CFE4_game_guys_sweet_surprise[i] == 6) {
            HuSprAttrReset(SPR[n + i], 0, 0xFFFF);
            HuSprAttrSet(SPR[n + i], 0, 0x8000);
        } else {
            HuSprAttrReset(SPR[n + i], 0, 0x8000);
            func_80055140_main(SPR[n + i], 0, D_8010CFE4_game_guys_sweet_surprise[i], 0);
            func_800550F4_main(SPR[n + i], 0, 1);
        }
    }
    if (D_8010CFE2_game_guys_sweet_surprise == 1) {
        switch (D_8010CBDC_game_guys_sweet_surprise) {
        case 0:
            D_8010CBE4_game_guys_sweet_surprise = 600.0f;
            D_8010CBE0_game_guys_sweet_surprise = 0.0f;
            HuAudFXPlay(0x53C);
            D_8010CBDC_game_guys_sweet_surprise++;
            break;
        case 1:
            D_8010CBE4_game_guys_sweet_surprise +=
                D_8010CBE0_game_guys_sweet_surprise * D_8010CBE0_game_guys_sweet_surprise * -17.5f;
            if (D_8010CBE0_game_guys_sweet_surprise >= 1.47f) {
                D_8010CBE0_game_guys_sweet_surprise = 1.47f;
            } else {
                D_8010CBE0_game_guys_sweet_surprise += 0.22f;
            }
            if (D_8010CBE4_game_guys_sweet_surprise <= 0.0f) {
                D_8010CBDC_game_guys_sweet_surprise++;
                D_8010CBE4_game_guys_sweet_surprise = 0.0f;
            }
            break;
        case 2:
            D_8010CFE2_game_guys_sweet_surprise = 0;
            break;
        }
        pos = func_8010B1F4_game_guys_sweet_surprise(-80.0f, D_8010CBE4_game_guys_sweet_surprise, -400.0f);
        func_80054904_main(SPR[n], 0, pos.x, pos.y);
        pos = func_8010B1F4_game_guys_sweet_surprise(80.0f, D_8010CBE4_game_guys_sweet_surprise, -400.0f);
        func_80054904_main(SPR[n + 1], 0, pos.x, pos.y);
    }
}

/* The coin counter's digits */
void func_80108538_game_guys_sweet_surprise(void) {
    s16 n = 30;
    s16 x = 54;
    s16 y = 22;
    s16 d;

    if (P.coins >= 999) {
        P.coins = 999;
    } else if (P.coins <= 0) {
        P.coins = 0;
    }
    d = P.coins / 100;
    if (d == 0) {
        func_8000BB94_main(SPR[n + 2]);
    } else {
        func_8000BD50_main(SPR[n + 2], d);
        func_8000BBD4_main(SPR[n + 2], x, y);
        x += 12;
        func_8000BB54_main(SPR[n + 2]);
    }
    d = (P.coins % 100) / 10;
    if (d == 0 && P.coins / 100 == 0) {
        func_8000BB94_main(SPR[n + 3]);
    } else {
        func_8000BD50_main(SPR[n + 3], d);
        func_8000BBD4_main(SPR[n + 3], x, y);
        x += 12;
        func_8000BB54_main(SPR[n + 3]);
    }
    func_8000BD50_main(SPR[n + 4], P.coins % 10);
    func_8000BBD4_main(SPR[n + 4], x, y);
    func_8000BB54_main(SPR[n + 4]);
}

/* The player's character */
void func_8010878C_game_guys_sweet_surprise(omObjData* obj) {
    s32 files[8] = { 0x21001C, 0x21001D, 0x21001E, 0x21001F, 0x210020, 0x210021, 0x210022, 0x210023 };

    obj->model[0] = func_8000B108_main(files[P.chr], 0x2A9);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 90.0f, 0.0f, 0.0f);
    omSetSca(obj, 2.0f, 2.0f, 2.0f);
    func_8001C8A8_main(obj->model[0], 0);
    D_8010CFEC_game_guys_sweet_surprise = 0;
    obj->func = func_80108878_game_guys_sweet_surprise;
}

/* The player's character jumps onto the chosen side and bounces */
void func_80108878_game_guys_sweet_surprise(omObjData* obj) {
    if (D_8010CFEC_game_guys_sweet_surprise == 1) {
        switch (D_8010CBE8_game_guys_sweet_surprise) {
        case 0:
            func_8001C8A8_main(obj->model[0], 1);
            obj->trans.x = D_8010CBF0_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].x;
            obj->trans.y = 600.0f;
            obj->trans.z = D_8010CBF0_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].z;
            obj->rot.y = 0.0f;
            D_8010CBEC_game_guys_sweet_surprise = 0.0f;
            D_8010CBE8_game_guys_sweet_surprise++;
            break;
        case 1:
        case 2:
        case 3:
            if (D_8010CBE8_game_guys_sweet_surprise == 1 || D_8010CBE8_game_guys_sweet_surprise == 2) {
                obj->trans.y += D_8010CBEC_game_guys_sweet_surprise * D_8010CBEC_game_guys_sweet_surprise *
                                ((D_8010CBEC_game_guys_sweet_surprise >= 0.0f) ? -17.5f : 17.5f);
            } else {
                obj->trans.y += D_8010CBEC_game_guys_sweet_surprise * D_8010CBEC_game_guys_sweet_surprise *
                                ((D_8010CBEC_game_guys_sweet_surprise >= 0.0f) ? -8.75f : 8.75f);
            }
            if (D_8010CBEC_game_guys_sweet_surprise < 1.7f) {
                D_8010CBEC_game_guys_sweet_surprise += 0.11f;
            } else {
                D_8010CBEC_game_guys_sweet_surprise = 1.7f;
            }
            if (obj->trans.y < D_8010CBF0_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y &&
                D_8010CBEC_game_guys_sweet_surprise >= 0.0f) {
                obj->trans.y = D_8010CBF0_game_guys_sweet_surprise[D_8010CF68_game_guys_sweet_surprise].y;
                if (D_8010CBE8_game_guys_sweet_surprise != 3) {
                    D_8010CBEC_game_guys_sweet_surprise = -1.47f;
                } else {
                    D_8010CBEC_game_guys_sweet_surprise = 0.0f;
                }
                D_8010CBE8_game_guys_sweet_surprise++;
            }
            break;
        }
        obj->rot.y += 10.0f;
    }
}

/* Game Guy */
void func_80108AC4_game_guys_sweet_surprise(omObjData* obj) {
    s16 i = 0;
    s32 attr = 0x2A9;
    s32 files[3] = { 0xA0063, 0xA0064, 9 };
    s32 motions[5] = { 0xA0065, 0xA006E, 0xA006C, 0xA006F, 0xA0071 };

    for (; i < 3; i++) {
        obj->model[i] = func_8000B108_main(files[i], attr);
    }
    omSetTra(obj, 0.0f, 0.0f, 200.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 5; i++) {
        func_8000B460_main(obj, i, motions[i]);
    }
    D_8010CFEE_game_guys_sweet_surprise = 0;
    func_8001C8A8_main(obj->model[1], 0);
    func_80017358_main(obj->model[1], "c203n30-r_hand", obj->model[0], "c203_000_new-r_hand");
    D_8010CFF0_game_guys_sweet_surprise = 0;
    obj->func = func_80108CB8_game_guys_sweet_surprise;
}

/* Game Guy's motions and his jump */
void func_80108CB8_game_guys_sweet_surprise(omObjData* obj) {
    if (D_8010CC08_game_guys_sweet_surprise != D_8010CFEE_game_guys_sweet_surprise) {
        switch (D_8010CFEE_game_guys_sweet_surprise) {
        case 0:
        case 2:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010CFEE_game_guys_sweet_surprise]].unk02, 0, 30, 2);
            break;
        case 1:
        case 3:
        case 4:
            func_8001C5B4_main(obj->model[0], obj->motion[D_8010CFEE_game_guys_sweet_surprise]);
            break;
        }
        D_8010CC08_game_guys_sweet_surprise = D_8010CFEE_game_guys_sweet_surprise;
    }
    if (D_8010CFF0_game_guys_sweet_surprise == 1) {
        switch (D_8010CC0A_game_guys_sweet_surprise) {
        case 0:
            D_8010CFEE_game_guys_sweet_surprise = 1;
            D_8010CC10_game_guys_sweet_surprise = -1.47f;
            D_8010CC0C_game_guys_sweet_surprise = 0;
            obj->trans.y = 0.0f;
            obj->trans.z = 200.0f;
            D_8010CC0A_game_guys_sweet_surprise++;
            break;
        case 1:
            if (D_8010CC0C_game_guys_sweet_surprise++ >= 25) {
                D_8010CC0A_game_guys_sweet_surprise++;
            }
            break;
        case 2:
            obj->trans.y += D_8010CC10_game_guys_sweet_surprise * D_8010CC10_game_guys_sweet_surprise *
                            ((D_8010CC10_game_guys_sweet_surprise >= 0.0f) ? -35.0f : 35.0f);
            if (obj->trans.y <= 0.0f && D_8010CC10_game_guys_sweet_surprise >= 0.0f) {
                D_8010CC0A_game_guys_sweet_surprise++;
                obj->trans.y = 0.0f;
            }
            if (D_8010CC10_game_guys_sweet_surprise >= 1.47f) {
                D_8010CC10_game_guys_sweet_surprise = 1.47f;
            } else {
                D_8010CC10_game_guys_sweet_surprise += 0.11f;
            }
            obj->trans.z -= 22.5f;
            break;
        case 3:
            D_8010CFEE_game_guys_sweet_surprise = 0;
            D_8010CFF0_game_guys_sweet_surprise = 0;
            break;
        }
    }
    D_8010CC14_game_guys_sweet_surprise = 1.0f - obj->trans.y * 0.001f;
    Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[2], D_8010CC14_game_guys_sweet_surprise, D_8010CC14_game_guys_sweet_surprise,
                      D_8010CC14_game_guys_sweet_surprise);
}

/* The left character, with its shadow and the chain of plates behind it */
void func_80108FE0_game_guys_sweet_surprise(omObjData* obj) {
    s16 i = 0;
    s32 attr = 0x2A9;
    s32 files[3] = { 0xA00D9, 9, 0xA00E4 };
    s32 motions[4] = { 0xA00DA, 0xA00DE, 0xA00E1, 0xA00E2 };
    void* data;
    s16 anim;

    D_8010D004_game_guys_sweet_surprise = obj->model[0] = func_8000B108_main(files[0], 0x2A9);
    obj->model[1] = func_8000B108_main(files[1], 0x2A9);
    omSetTra(obj, -210.0f, 0.0f, -50.0f);
    omSetRot(obj, 0.0f, 90.0f, 0.0f);
    omSetSca(obj, 0.6f, 0.6f, 0.6f);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 1.0f, 2.0f);
    for (; i < 4; i++) {
        func_8000B460_main(obj, i, motions[i]);
    }
    D_8010CFF2_game_guys_sweet_surprise = 0;
    data = DataRead(0xA00E5);
    anim = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "c165n_4_DEF");
    DataClose(data);
    func_8001C448_main(obj->model[0]);
    func_80032FF8_main(anim, 0);
    func_80032FC0_main(anim, 1, 0);
    for (i = 0; i < 4; i++) {
        obj->model[i + 2] = func_8000B108_main(files[2], attr);
        Hu3DModelRotSet(obj->model[i + 2], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[i + 2], 0.5f, 0.5f, 0.5f);
    }
    Hu3DModelPosSet(obj->model[2], -350.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(obj->model[3], -320.0f, 0.0f, -149.0f);
    Hu3DModelPosSet(obj->model[4], -290.0f, 0.0f, -148.0f);
    Hu3DModelPosSet(obj->model[5], -290.0f, 0.0f, -147.0f);
    obj->func = func_801092F0_game_guys_sweet_surprise;
}

/* The left character eats and sways; its plates follow; it wins or loses */
#ifdef NON_MATCHING
void func_801092F0_game_guys_sweet_surprise(omObjData* obj) {
    f32 step;
    f32 a;

    if (D_8010CC1C_game_guys_sweet_surprise != D_8010CFF2_game_guys_sweet_surprise) {
        if (D_8010CFF2_game_guys_sweet_surprise < 4) {
            if (D_8010CFF2_game_guys_sweet_surprise >= 0) {
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010CFF2_game_guys_sweet_surprise]].unk02, 0, 30, 2);
            }
        }
        D_8010CC1C_game_guys_sweet_surprise = D_8010CFF2_game_guys_sweet_surprise;
    }
    if (D_8010CFF4_game_guys_sweet_surprise == 0) {
        if (D_8010CFF2_game_guys_sweet_surprise >= 2 && D_8010CFF2_game_guys_sweet_surprise < 4) {
            if (obj->trans.x < -190.0f) {
                obj->trans.x += 5.0f;
            } else {
                D_8010CC2C_game_guys_sweet_surprise += D_8010CC28_game_guys_sweet_surprise;
                if (D_8010CC2C_game_guys_sweet_surprise <= -20.0f || D_8010CC2C_game_guys_sweet_surprise >= 20.0f) {
                    D_8010CC28_game_guys_sweet_surprise = -D_8010CC28_game_guys_sweet_surprise;
                }
                obj->rot.y = D_8010CC2C_game_guys_sweet_surprise + 90.0f;
                if (D_8010CC2C_game_guys_sweet_surprise > 0.0f) {
                    obj->trans.x = D_8010CC2C_game_guys_sweet_surprise / 2.0f + -190.0f;
                } else {
                    obj->trans.x = -190.0f - D_8010CC2C_game_guys_sweet_surprise / 2.0f;
                }
            }
        }
        if (D_8010CFF2_game_guys_sweet_surprise == 2) {
            if (HmfModelData[obj->model[0]].unk40 == 4.0f) {
                HuAudFXPlay(0x53A);
            }
        } else if (D_8010CFF2_game_guys_sweet_surprise == 3) {
            if (HmfModelData[obj->model[0]].unk40 == 8.0f) {
                HuAudFXPlay(0x53A);
            }
        }
    }
    D_8010CC20_game_guys_sweet_surprise = 2.0f - obj->trans.y * 0.002f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], D_8010CC20_game_guys_sweet_surprise, D_8010CC20_game_guys_sweet_surprise,
                      D_8010CC20_game_guys_sweet_surprise);
    step = ((obj->trans.x - 90.0f) - HmfModelData[obj->model[2]].pos.x) / 3.0f;
    HmfModelData[obj->model[3]].pos.x = step + HmfModelData[obj->model[2]].pos.x;
    HmfModelData[obj->model[4]].pos.x = step + HmfModelData[obj->model[3]].pos.x;
    HmfModelData[obj->model[5]].pos.x = step + HmfModelData[obj->model[4]].pos.x;
    if (D_8010CC1A_game_guys_sweet_surprise >= 4) {
        D_8010CC18_game_guys_sweet_surprise = -1;
    } else if (D_8010CC1A_game_guys_sweet_surprise < -3) {
        D_8010CC18_game_guys_sweet_surprise = 1;
    }
    D_8010CC1A_game_guys_sweet_surprise += D_8010CC18_game_guys_sweet_surprise;
    a = step * 3.0f * 0.45f;
    HmfModelData[obj->model[3]].pos.y = 10.0f * sindf(sindf(a) * 30.0f) + D_8010CC1A_game_guys_sweet_surprise;
    HmfModelData[obj->model[4]].pos.y = sindf(sindf(a) * 60.0f) * 20.0f - D_8010CC1A_game_guys_sweet_surprise;
    HmfModelData[obj->model[5]].pos.y = sindf(sindf(a) * 90.0f) * 30.0f + D_8010CC1A_game_guys_sweet_surprise;
    if (D_8010CFF4_game_guys_sweet_surprise == 1) {
        switch (D_8010CC24_game_guys_sweet_surprise) {
        case 0:
            D_8010CC26_game_guys_sweet_surprise = 0;
            D_8010CC30_game_guys_sweet_surprise = obj->trans.x;
            D_8010CC24_game_guys_sweet_surprise++;
            break;
        case 1:
            obj->trans.x = sindf(D_8010CC26_game_guys_sweet_surprise++ * 4.5f) * 100.0f + D_8010CC30_game_guys_sweet_surprise;
            if (D_8010CC26_game_guys_sweet_surprise >= 21) {
                D_8010CC26_game_guys_sweet_surprise = 0;
                D_8010CC24_game_guys_sweet_surprise++;
            }
            break;
        case 2:
            obj->rot.y = 90.0f - sindf(D_8010CC26_game_guys_sweet_surprise++ * 9.0f) * 90.0f;
            if (obj->rot.y <= 0.0f || D_8010CC26_game_guys_sweet_surprise >= 11) {
                D_8010CC24_game_guys_sweet_surprise++;
            }
            break;
        case 3:
            HuAudFXPlay(0x53E);
            D_8010CFF2_game_guys_sweet_surprise = 2;
            D_8010CC24_game_guys_sweet_surprise++;
            break;
        }
    }
    if (D_8010CFF4_game_guys_sweet_surprise == 3) {
        if (obj->rot.y != 90.0f) {
            if (obj->rot.y > 90.0f) {
                obj->rot.y -= 1.0f;
                if (obj->rot.y <= 90.0f) {
                    obj->rot.y = 90.0f;
                    D_8010CFF4_game_guys_sweet_surprise = 0;
                }
            } else if (obj->rot.y < 90.0f) {
                obj->rot.y += 1.0f;
                if (obj->rot.y >= 90.0f) {
                    obj->rot.y = 90.0f;
                    D_8010CFF4_game_guys_sweet_surprise = 0;
                }
            }
        } else {
            D_8010CFF4_game_guys_sweet_surprise = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_801092F0_game_guys_sweet_surprise);
#endif

/* The right character (a link of the left one's model) */
void func_80109AA8_game_guys_sweet_surprise(omObjData* obj) {
    s16 i = 0;
    s32 attr = 0x2A9;
    s32 files[4] = { 0xA00D9, 9, 0xA00E4, 0 };
    s32 motions[4] = { 0xA00DA, 0xA00DE, 0xA00E1, 0xA00E2 };
    void* data;
    s16 anim;

    obj->model[0] = Hu3DModelLink(D_8010D004_game_guys_sweet_surprise);
    obj->model[1] = func_8000B108_main(files[1], 0x2A9);
    omSetTra(obj, 195.0f, 0.0f, -100.0f);
    omSetRot(obj, 0.0f, 270.0f, 0.0f);
    omSetSca(obj, 0.3f, 0.3f, 0.3f);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
    for (; i < 4; i++) {
        func_8000B460_main(obj, i, motions[i]);
    }
    D_8010CFF6_game_guys_sweet_surprise = 0;
    data = DataRead(0xA00E5);
    anim = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "c165n_4_DEF");
    DataClose(data);
    func_8001C448_main(obj->model[0]);
    func_80032FF8_main(anim, 0);
    func_80032FC0_main(anim, 1, 0);
    for (i = 0; i < 4; i++) {
        obj->model[i + 2] = func_8000B108_main(files[2], attr);
    }
    for (i = 0; i < 4; i++) {
        Hu3DModelRotSet(obj->model[i + 2], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[i + 2], 0.3f, 0.3f, 0.3f);
    }
    Hu3DModelPosSet(obj->model[2], 350.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(obj->model[3], 320.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(obj->model[4], 290.0f, 0.0f, -150.0f);
    Hu3DModelPosSet(obj->model[5], 280.0f, 70.0f, -150.0f);
    obj->func = func_80109DE4_game_guys_sweet_surprise;
}

/* The right character (as func_801092F0, mirrored) */
#ifdef NON_MATCHING
void func_80109DE4_game_guys_sweet_surprise(omObjData* obj) {
    if (D_8010CC40_game_guys_sweet_surprise != D_8010CFF6_game_guys_sweet_surprise) {
        if (D_8010CFF6_game_guys_sweet_surprise < 4) {
            if (D_8010CFF6_game_guys_sweet_surprise >= 0) {
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[D_8010CFF6_game_guys_sweet_surprise]].unk02, 0, 30,
                                   2);
            }
        }
        D_8010CC40_game_guys_sweet_surprise = D_8010CFF6_game_guys_sweet_surprise;
    }
    if (D_8010CFF8_game_guys_sweet_surprise == 0) {
        if (D_8010CFF6_game_guys_sweet_surprise >= 2 && D_8010CFF6_game_guys_sweet_surprise < 4) {
        if (obj->trans.x > 175.0f) {
            obj->trans.x -= 5.0f;
        } else {
            D_8010CC50_game_guys_sweet_surprise += D_8010CC4C_game_guys_sweet_surprise;
            if (D_8010CC50_game_guys_sweet_surprise <= -20.0f || D_8010CC50_game_guys_sweet_surprise >= 20.0f) {
                D_8010CC4C_game_guys_sweet_surprise = -D_8010CC4C_game_guys_sweet_surprise;
            }
            obj->rot.y = D_8010CC50_game_guys_sweet_surprise + 270.0f;
            if (D_8010CC50_game_guys_sweet_surprise > 0.0f) {
                obj->trans.x = 175.0f - D_8010CC50_game_guys_sweet_surprise / 2.0f;
            } else {
                obj->trans.x = D_8010CC50_game_guys_sweet_surprise / 2.0f + 175.0f;
            }
        }
        }
        if (D_8010CFF6_game_guys_sweet_surprise == 2) {
            if (HmfModelData[obj->model[0]].unk40 == 4.0f) {
                HuAudFXPlay(0x53B);
            }
        } else if (D_8010CFF6_game_guys_sweet_surprise == 3) {
            if (HmfModelData[obj->model[0]].unk40 == 8.0f) {
                HuAudFXPlay(0x53B);
            }
        }
    }
    D_8010CC44_game_guys_sweet_surprise = 1.0f - obj->trans.y * 0.001f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], D_8010CC44_game_guys_sweet_surprise, D_8010CC44_game_guys_sweet_surprise,
                      D_8010CC44_game_guys_sweet_surprise);
    D_8010CC38_game_guys_sweet_surprise = ((obj->trans.x + 60.0f) - HmfModelData[obj->model[2]].pos.x) / 3.0f;
    HmfModelData[obj->model[3]].pos.x = HmfModelData[obj->model[2]].pos.x + D_8010CC38_game_guys_sweet_surprise;
    HmfModelData[obj->model[4]].pos.x = HmfModelData[obj->model[3]].pos.x + D_8010CC38_game_guys_sweet_surprise;
    HmfModelData[obj->model[5]].pos.x = HmfModelData[obj->model[4]].pos.x + D_8010CC38_game_guys_sweet_surprise;
    if (D_8010CC36_game_guys_sweet_surprise >= 2) {
        D_8010CC34_game_guys_sweet_surprise = -1;
    } else if (D_8010CC36_game_guys_sweet_surprise < -1) {
        D_8010CC34_game_guys_sweet_surprise = 1;
    }
    D_8010CC36_game_guys_sweet_surprise += D_8010CC34_game_guys_sweet_surprise;
    D_8010CC3C_game_guys_sweet_surprise = 20.0f / 3.0f;
    HmfModelData[obj->model[3]].pos.y =
        sindf(sindf(D_8010CC38_game_guys_sweet_surprise * 3.0f * -0.225f) * 30.0f) * D_8010CC3C_game_guys_sweet_surprise +
        D_8010CC36_game_guys_sweet_surprise;
    HmfModelData[obj->model[4]].pos.y =
        2.0f * D_8010CC3C_game_guys_sweet_surprise *
            sindf(sindf(D_8010CC38_game_guys_sweet_surprise * 3.0f * -0.225f) * 60.0f) -
        D_8010CC36_game_guys_sweet_surprise;
    HmfModelData[obj->model[5]].pos.y =
        D_8010CC3C_game_guys_sweet_surprise * 3.0f *
            sindf(sindf(D_8010CC38_game_guys_sweet_surprise * 3.0f * -0.225f) * 90.0f) +
        D_8010CC36_game_guys_sweet_surprise;
    if (D_8010CFF8_game_guys_sweet_surprise == 1) {
        switch (D_8010CC48_game_guys_sweet_surprise) {
        case 0:
            D_8010CC4A_game_guys_sweet_surprise = 0;
            D_8010CC54_game_guys_sweet_surprise = obj->trans.x;
            D_8010CC48_game_guys_sweet_surprise++;
            break;
        case 1:
            obj->trans.x = D_8010CC54_game_guys_sweet_surprise - sindf(D_8010CC4A_game_guys_sweet_surprise++ * 4.5f) * 100.0f;
            if (D_8010CC4A_game_guys_sweet_surprise >= 21) {
                D_8010CC4A_game_guys_sweet_surprise = 0;
                D_8010CC48_game_guys_sweet_surprise++;
            }
            break;
        case 2:
            obj->rot.y = sindf(D_8010CC4A_game_guys_sweet_surprise++ * 9.0f) * 90.0f + 270.0f;
            if (obj->rot.y >= 360.0f || D_8010CC4A_game_guys_sweet_surprise >= 11) {
                D_8010CC48_game_guys_sweet_surprise++;
            }
            break;
        case 3:
            HuAudFXPlay(0x53F);
            D_8010CFF6_game_guys_sweet_surprise = 2;
            D_8010CC48_game_guys_sweet_surprise++;
            break;
        }
    }
    if (D_8010CFF8_game_guys_sweet_surprise == 3) {
        if (obj->rot.y != 270.0f) {
            if (obj->rot.y > 270.0f) {
                obj->rot.y -= 1.0f;
                if (obj->rot.y <= 270.0f) {
                    obj->rot.y = 270.0f;
                    D_8010CFF8_game_guys_sweet_surprise = 0;
                }
            } else if (obj->rot.y < 270.0f) {
                obj->rot.y += 1.0f;
                if (obj->rot.y >= 270.0f) {
                    obj->rot.y = 270.0f;
                    D_8010CFF8_game_guys_sweet_surprise = 0;
                }
            }
        } else {
            D_8010CFF8_game_guys_sweet_surprise = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80109DE4_game_guys_sweet_surprise);
#endif

/* The pie stand */
void func_8010A604_game_guys_sweet_surprise(omObjData* obj) {
    s16 i = 0;
    s32 attr = 0x2A9;
    s32 files[2] = { 0x66000D, 9 };

    for (; i < 2; i++) {
        obj->model[i] = func_8000B108_main(files[i], attr);
    }
    omSetTra(obj, 125.0f, 200.0f, -430.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
    omAddObj(100, 10, 10, -1, func_8010A784_game_guys_sweet_surprise);
    func_8001C8A8_main(obj->model[0], 0);
    func_8001C8A8_main(obj->model[1], 0);
    D_8010CFFA_game_guys_sweet_surprise = 0;
    obj->func = func_8010A820_game_guys_sweet_surprise;
}

void func_8010A784_game_guys_sweet_surprise(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0xB0006, 0x2A9);
    omSetTra(obj, 125.0f, 125.0f, -400.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 2.0f, 2.0f, 2.0f);
    func_8000B460_main(obj, 0, 0xB0006);
    obj->func = func_8010AA94_game_guys_sweet_surprise;
    D_8010CFFC_game_guys_sweet_surprise = 0;
}

void func_8010A820_game_guys_sweet_surprise(omObjData* obj) {
    f32 s;

    if (D_8010CFFA_game_guys_sweet_surprise == 1) {
        D_8010CC5C_game_guys_sweet_surprise = 1.5f;
        obj->scale.x = obj->scale.y = obj->scale.z = 1.5f;
        D_8010CC5A_game_guys_sweet_surprise = 0;
        D_8010CFFA_game_guys_sweet_surprise = 0;
    }
    if (D_8010CFF0_game_guys_sweet_surprise == 1) {
        switch (D_8010CC58_game_guys_sweet_surprise) {
        case 0:
            HuAudFXPlay(0x53D);
            obj->scale.x = obj->scale.y = obj->scale.z = 0.0f;
            func_8001C8A8_main(obj->model[0], 1);
            func_8001C8A8_main(obj->model[1], 1);
            D_8010CC58_game_guys_sweet_surprise++;
            break;
        case 1:
            if (obj->scale.x < 2.0f) {
                obj->scale.x = obj->scale.y = obj->scale.z = obj->scale.z + 1.0f;
            } else {
                D_8010CC58_game_guys_sweet_surprise++;
            }
            break;
        case 2:
            if (obj->scale.x > 1.0f) {
                obj->scale.x = obj->scale.y = obj->scale.z = obj->scale.z - 0.5f;
            } else {
                obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
                D_8010CC58_game_guys_sweet_surprise++;
            }
            break;
        }
    } else if (D_8010CC5C_game_guys_sweet_surprise > 1.0f) {
        if (!(D_8010CC5A_game_guys_sweet_surprise++ & 1)) {
            obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        } else {
            obj->scale.x = obj->scale.y = obj->scale.z = D_8010CC5C_game_guys_sweet_surprise =
                D_8010CC5C_game_guys_sweet_surprise - 0.05f;
        }
    } else {
        obj->scale.x = obj->scale.y = obj->scale.z = D_8010CC5C_game_guys_sweet_surprise = 1.0f;
    }
    s = 1.0f - obj->trans.y * 0.001f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], s, s, s);
}

void func_8010AA94_game_guys_sweet_surprise(omObjData* obj) {
    if (D_8010CFFC_game_guys_sweet_surprise == 1) {
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        D_8010CFFC_game_guys_sweet_surprise = 0;
    }
}

/* The two pies */
void func_8010AAD8_game_guys_sweet_surprise(omObjData* obj) {
    omAddObj(200, 10, 10, -1, func_8010AB3C_game_guys_sweet_surprise);
    omAddObj(300, 10, 10, -1, func_8010ABD8_game_guys_sweet_surprise);
    obj->func = NULL;
}

void func_8010AB3C_game_guys_sweet_surprise(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0x66000E, 0x2A9);
    omSetTra(obj, -80.0f, 0.0f, -400.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 2.0f, 2.0f, 2.0f);
    func_8000B460_main(obj, 0, 0x66000E);
    obj->func = func_8010AC74_game_guys_sweet_surprise;
    D_8010CFEA_game_guys_sweet_surprise = 0;
}

void func_8010ABD8_game_guys_sweet_surprise(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0x66000E, 0x2A9);
    omSetTra(obj, 80.0f, 0.0f, -400.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 2.0f, 2.0f, 2.0f);
    func_8000B460_main(obj, 0, 0x66000E);
    obj->func = func_8010AD04_game_guys_sweet_surprise;
    D_8010CFE8_game_guys_sweet_surprise = 0;
}

void func_8010AC74_game_guys_sweet_surprise(omObjData* obj) {
    if (D_8010CFEA_game_guys_sweet_surprise == 1) {
        if (func_801059BC_game_guys_sweet_surprise(3.0f) == 0) {
            obj->scale.x = obj->scale.y = obj->scale.z = 1.5f;
        } else {
            obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        }
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        D_8010CFEA_game_guys_sweet_surprise = 0;
    }
}

void func_8010AD04_game_guys_sweet_surprise(omObjData* obj) {
    if (D_8010CFE8_game_guys_sweet_surprise == 1) {
        if (func_801059BC_game_guys_sweet_surprise(3.0f) == 0) {
            obj->scale.x = obj->scale.y = obj->scale.z = 1.25f;
        } else {
            obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        }
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        D_8010CFE8_game_guys_sweet_surprise = 0;
    }
}

s16 func_8010AD94_game_guys_sweet_surprise(s32 file, u16 attr, u16 prio, s16 x, s16 y) {
    s16 id = InitEspriteSlot(func_8000B838_main(file), 0, 0);

    func_8000BC48_main(id, attr | 8);
    func_8000BCC8_main(id, prio);
    func_8000BBD4_main(id, x, y);
    return id;
}

s16 func_8010AE44_game_guys_sweet_surprise(s16 x, s16 y, s16 mes) {
    s16 winId = func_80060880_main(x, y, mes);

    func_8005B63C_main(winId, 2, 2);
    func_80061100_main(winId, 1);
    func_8005BDFC_main(winId, 0);
    func_8005D294_main(winId);
    return winId;
}

/* Wait for the window's message to end: a human presses A, the CPU's key is pressed for it */
void func_8010AEB8_game_guys_sweet_surprise(s16 winId, s16 pad, s16 cpu) {
    s16 i;

    func_8005F904_main();
    while (func_8005E0C0_main(winId) != 0) {
        switch (cpu) {
        case 0:
            if (D_800D5558_main[pad] & 0x8000) {
                func_8005F744_main(-0x8000, -0x8000, -0x8000, -0x8000);
            }
            break;
        case 1:
            for (i = 0; i < 10; i++) {
                func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000,
                                   (&D_8010CB70_game_guys_sweet_surprise[D_8010D002_game_guys_sweet_surprise])->delay);
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

/* A yes/no choice in the window: a human answers with the pad, the CPU moves down `count` times */
s16 func_8010B004_game_guys_sweet_surprise(s16 winId, s16 pad, s16 cpu, s16 count) {
    s16 keys[4] = { 0, 0, 0, 0 };
    s16 ports[4] = { 1, 2, 4, 8 };
    s16 i;

    switch (cpu) {
    case 0:
        keys[pad] = -1;
        func_8005B63C_main(winId, 2, 0);
        func_8005FE54_main(winId, ports[pad]);
        func_8005F744_main(keys[0], keys[1], keys[2], keys[3]);
        break;
    case 1:
        for (i = 0; i < count; i++) {
            func_8005F698_main(0x400, 0x400, 0x400, 0x400,
                               (&D_8010CB70_game_guys_sweet_surprise[D_8010D002_game_guys_sweet_surprise])->delay);
        }
        func_8005F698_main(-0x8000, -0x8000, -0x8000, -0x8000,
                           D_8010CB70_game_guys_sweet_surprise[D_8010D002_game_guys_sweet_surprise].delay);
        break;
    }
    return func_8005E1D8_main(winId, 0, 1);
}

void func_8010B1B4_game_guys_sweet_surprise(s16 winId) {
    func_8005D294_main(winId);
    func_80060EA8_main(winId, 1);
    func_800610E0_main(winId);
}

/* A point's place on screen */
Vec2f func_8010B1F4_game_guys_sweet_surprise(f32 x, f32 y, f32 z) {
    Vec v;
    Vec2f s;

    v.x = x;
    v.y = y;
    v.z = z;
    Hu3DCam3DToScreen(0, &v, &s);
    return s;
}
