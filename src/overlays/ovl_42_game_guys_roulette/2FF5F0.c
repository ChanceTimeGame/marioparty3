#include "ultra64.h"
#include "include_asm.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/util.h"
#include "game/wipe.h"
#include "game/sprite.h"
#include "mallocblock.h"

// roulette B: the Game Guy title effect (three coloured rings circle the screen and close in, drawn into 4-bit
// sprite images of 320x240 that are cycled through three buffers so the rings leave trails)

/* A ring */
typedef struct GgrRing {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 color;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 r;
    /* 0x0C */ f32 angle;
    /* 0x10 */ f32 speed;
    /* 0x14 */ s16 fx; /* Lissajous factors of the circling path */
    /* 0x16 */ s16 fy;
} GgrRing; /* size 0x18 */

/* The rings as they were drawn into one buffer, to clear them again */
typedef struct GgrTrail {
    /* 0x00 */ s16 active[4];
    /* 0x08 */ s16 x[4];
    /* 0x10 */ s16 y[4];
    /* 0x18 */ s16 r[4];
} GgrTrail; /* size 0x20 */

/* A layer: a sprite whose 4-bit image is swapped between its own and two of ours */
typedef struct GgrLayer {
    /* 0x00 */ HuSprite* spr;
    /* 0x04 */ u8* buf[3];
    /* 0x10 */ s16 grp;
    /* 0x12 */ s16 alpha;
} GgrLayer; /* size 0x14 */

void func_80055458_main(s16, s16, u16);
void func_8004AB0C_main(s32);

// LOCAL
void func_80108D20_game_guys_roulette(s16 x, s16 y);
void func_80108FEC_game_guys_roulette(void);
s16 func_80109078_game_guys_roulette(void);
s16 func_80109B60_game_guys_roulette(s16 x);
void func_80109D14_game_guys_roulette(void);
s16 func_80109D98_game_guys_roulette(s32 file, s32 attr, s32 prio, s32 alpha);
void func_80109E6C_game_guys_roulette(void);
void func_80109FD0_game_guys_roulette(void);
void func_8010A060_game_guys_roulette(s16 active, s16 x, s16 y, s16 r);
void func_8010A1BC_game_guys_roulette(s16 active, s16 x, s16 y, s16 color);
void func_8010A1FC_game_guys_roulette(s16 active, s16 x, s16 y, s16 r, s32 color);
void func_8010A3F4_game_guys_roulette(s16 x0, s16 y0, s16 x1, s16 y1);

extern s16 D_8010A6B0_game_guys_roulette; /* frame */
extern s16 D_8010A6B2_game_guys_roulette; /* the rings' start y */
extern s16 D_8010A6B4_game_guys_roulette; /* func_80109B60's frame */

extern GgrRing D_8010AB60_game_guys_roulette[3];
extern s16 D_8010ABA8_game_guys_roulette; /* centre x */
extern s16 D_8010ABAA_game_guys_roulette; /* centre y */
extern s16 D_8010ABAC_game_guys_roulette; /* circling radius */
extern s16 D_8010ABAE_game_guys_roulette; /* end x */
extern s16 D_8010ABB0_game_guys_roulette; /* end y */
extern GgrTrail D_8010ABB8_game_guys_roulette[3];
extern GgrLayer D_8010AC20_game_guys_roulette; /* the rings' colour layer */
extern s32 D_8010AC34_game_guys_roulette; /* buffer drawn this frame */
extern GgrLayer D_8010AC38_game_guys_roulette; /* the mask layer */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80108D20_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80108FEC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80109078_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_80109B60_game_guys_roulette);

void func_80109D14_game_guys_roulette(void) {
    HuSprAttrSet(D_8010AC38_game_guys_roulette.grp, 0, 0x8000);
    HuSprAttrSet(D_8010AC20_game_guys_roulette.grp, 0, 0x8000);
    D_8010AC38_game_guys_roulette.spr->unk_84->unk00->unk00 = D_8010AC38_game_guys_roulette.buf[0];
    D_8010AC20_game_guys_roulette.spr->unk_84->unk00->unk00 = D_8010AC20_game_guys_roulette.buf[0];
}

s16 func_80109D98_game_guys_roulette(s32 file, s32 attr, s32 prio, s32 alpha) {
    s16 data = func_8000B838_main(file);
    s16 grp = HuSprGrpCreate(1, 0);

    func_80055024_main(grp, 0, data, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, attr | 0x1000);
    HuSprPriSet(grp, 0, prio);
    func_80054904_main(grp, 0, 160, 120);
    func_80055458_main(grp, 0, alpha);
    return grp;
}

/* The two layers, each with two image buffers of its own; the mask layer's palette */
void func_80109E6C_game_guys_roulette(void) {
    s16* pal;

    D_8010AC38_game_guys_roulette.grp = func_80109D98_game_guys_roulette(0x63000A, 0, 10, 0x80);
    D_8010AC38_game_guys_roulette.spr = HuSprGet(D_8010AC38_game_guys_roulette.grp, 0);
    D_8010AC38_game_guys_roulette.buf[0] = D_8010AC38_game_guys_roulette.spr->unk_84->unk00->unk00;
    pal = D_8010AC38_game_guys_roulette.spr->unk_84->unk0C;
    D_8010AC38_game_guys_roulette.buf[1] = HuMemAllocTag(0x9600, 0x7918);
    D_8010AC38_game_guys_roulette.buf[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 1;
    pal[1] = 0x3F;
    pal[2] = 0x7C1;
    pal[3] = 0x7FF;
    pal[4] = -0x7FF;
    pal[5] = -0x7C1;
    pal[6] = -0x3F;
    pal[7] = -2;
    D_8010AC20_game_guys_roulette.grp = func_80109D98_game_guys_roulette(0x63000A, 0, 10, 0x100);
    D_8010AC20_game_guys_roulette.spr = HuSprGet(D_8010AC20_game_guys_roulette.grp, 0);
    D_8010AC20_game_guys_roulette.buf[0] = D_8010AC20_game_guys_roulette.spr->unk_84->unk00->unk00;
    pal = D_8010AC20_game_guys_roulette.spr->unk_84->unk0C;
    D_8010AC20_game_guys_roulette.buf[1] = HuMemAllocTag(0x9600, 0x7918);
    D_8010AC20_game_guys_roulette.buf[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 1;
    pal[1] = 0;
}

void func_80109FD0_game_guys_roulette(void) {
    s32 i;
    s32 j;
    u8* p;

    for (i = 0; i < 3; i++) {
        p = D_8010AC38_game_guys_roulette.buf[i];
        for (j = 0; j < 0x9600; j++) {
            *p++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        p = D_8010AC20_game_guys_roulette.buf[i];
        for (j = 0; j < 0x9600; j++) {
            *p++ = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A060_game_guys_roulette);

void func_8010A1BC_game_guys_roulette(s16 active, s16 x, s16 y, s16 color) {
    func_8010A1FC_game_guys_roulette(active, x, y, 45, color);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A1FC_game_guys_roulette);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A3F4_game_guys_roulette);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", D_8010A800_game_guys_roulette);
