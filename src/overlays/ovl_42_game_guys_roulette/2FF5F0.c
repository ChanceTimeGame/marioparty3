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
void func_8010A1FC_game_guys_roulette(s16 active, s16 x, s16 y, s16 r, s16 color);
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
extern s16 D_8010AC34_game_guys_roulette; /* buffer drawn this frame */
extern GgrLayer D_8010AC38_game_guys_roulette; /* the mask layer */

/* Start the effect: the rings circle the centre on a random path and end at (x, y) */
void func_80108D20_game_guys_roulette(s16 x, s16 y) {
    s16 paths[3][2] = { { 10, 7 }, { 10, 8 }, { 10, 10 } };
    s16 i;
    s32 k;

    D_8010ABA8_game_guys_roulette = 160;
    D_8010ABAA_game_guys_roulette = 120;
    D_8010ABAC_game_guys_roulette = 95;
    D_8010ABAE_game_guys_roulette = x;
    D_8010ABB0_game_guys_roulette = y;
    i = 0;
    k = (u8)(rand8() % 3);
    for (; i < 3; i++) {
        D_8010AB60_game_guys_roulette[i].active = 0;
        D_8010AB60_game_guys_roulette[i].fx = paths[k][0];
        D_8010AB60_game_guys_roulette[i].fy = paths[k][1];
        D_8010AB60_game_guys_roulette[i].speed = 1.5f;
        if (k == 0) {
            D_8010AB60_game_guys_roulette[i].speed = 1.75f;
        }
        D_8010AB60_game_guys_roulette[i].angle = i * 120;
        D_8010AB60_game_guys_roulette[i].x =
            D_8010ABA8_game_guys_roulette +
            cosdf(D_8010AB60_game_guys_roulette[i].fx * D_8010AB60_game_guys_roulette[i].angle) * D_8010ABAC_game_guys_roulette;
        D_8010AB60_game_guys_roulette[i].y =
            D_8010ABAA_game_guys_roulette +
            sindf(D_8010AB60_game_guys_roulette[i].fy * D_8010AB60_game_guys_roulette[i].angle) * D_8010ABAC_game_guys_roulette;
        D_8010AB60_game_guys_roulette[i].r = 0;
    }
    D_8010AB60_game_guys_roulette[0].color = 1;
    D_8010AB60_game_guys_roulette[1].color = 2;
    D_8010AB60_game_guys_roulette[2].color = 4;
    D_8010AC38_game_guys_roulette.alpha = 0x80;
    D_8010AC20_game_guys_roulette.alpha = 0x100;
    func_80109E6C_game_guys_roulette();
    func_80109FD0_game_guys_roulette();
    D_8010AC34_game_guys_roulette = 0;
}

/* Reset the mask layer (unused here) */
void func_80108FEC_game_guys_roulette(void) {
    func_80109FD0_game_guys_roulette();
    D_8010AC34_game_guys_roulette = 0;
    D_8010AC38_game_guys_roulette.alpha = 0;
    func_80055458_main(D_8010AC38_game_guys_roulette.grp, 0, 0);
    HuSprAttrReset(D_8010AC38_game_guys_roulette.grp, 0, 0xFFFF);
    HuSprAttrSet(D_8010AC38_game_guys_roulette.grp, 0, 0x1000);
    D_8010AC38_game_guys_roulette.spr->unk_84->unk00->unk00 = D_8010AC38_game_guys_roulette.buf[D_8010AC34_game_guys_roulette];
}

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

/* Clear a ring's square from this frame's buffers */
// masked 6: retail's strength-reduced row pointers come from C not found (this C writes them out; same bytes cleared)
#ifdef NON_MATCHING
void func_8010A060_game_guys_roulette(s16 active, s16 x, s16 y, s16 r) {
    s32 xx;
    s32 yy;
    u8* pa;
    u8* pb;

    if (active == 0 || r < 1) {
        return;
    }
    pa = D_8010AC38_game_guys_roulette.buf[D_8010AC34_game_guys_roulette] + (x + r) / 2 + (y - 1 - r) * 160 + 1;
    pb = D_8010AC20_game_guys_roulette.buf[D_8010AC34_game_guys_roulette] + (x + r) / 2 + (y - 1 - r) * 160 + 1;
    for (yy = y - r; yy < y + r; yy++) {
        pa += 159 - r;
        pb += 159 - r;
        for (xx = x - r; xx < x + 1 + r; xx += 2) {
            if (xx >= 0 && xx < 320 && yy >= 0 && yy < 240) {
                *pa = 0;
                *pb = 0;
            }
            pa++;
            pb++;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A060_game_guys_roulette);
#endif

void func_8010A1BC_game_guys_roulette(s16 active, s16 x, s16 y, s16 color) {
    func_8010A1FC_game_guys_roulette(active, x, y, 45, color);
}

/* Draw a filled ring of radius r in a colour (a 4-bit pixel pair per byte) into this frame's buffers, the mask
   layer gets the colour and the colour layer a 1 */
// masked 35: retail squares r before the early-out test and allocates differently; logic checked block by block
#ifdef NON_MATCHING
void func_8010A1FC_game_guys_roulette(s16 active, s16 x, s16 y, s16 r, s16 color) {
    s32 xx;
    s32 yy;
    u8* pa;
    u8* pb;

    if (active == 0 || r < 1) {
        return;
    }
    for (yy = y - r; yy < y + r; yy++) {
        pa = D_8010AC38_game_guys_roulette.buf[D_8010AC34_game_guys_roulette] + (x - r) / 2 + yy * 160;
        pb = D_8010AC20_game_guys_roulette.buf[D_8010AC34_game_guys_roulette] + (x - r) / 2 + yy * 160;
        for (xx = x - r; xx < x + r; xx++) {
            if (xx >= 0 && xx < 320 && yy >= 0 && yy < 240 &&
                (xx - x) * (xx - x) + (yy - y) * (yy - y) < r * r) {
                if (xx & 1) {
                    *pa |= (u16)color;
                    *pb |= 1;
                } else {
                    *pa |= (u16)color << 4;
                    *pb |= 0x10;
                }
            }
            if (xx & 1) {
                pa++;
                pb++;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A1FC_game_guys_roulette);
#endif

/* Draw a line in colour 7 into this frame's mask buffer (Bresenham, stepping in y) */
// masked 39: two y-stepping Bresenham loops, register allocation and loop layout differ; logic checked against the asm
#ifdef NON_MATCHING
void func_8010A3F4_game_guys_roulette(s16 x0, s16 y0, s16 x1, s16 y1) {
    s32 dx;
    s16 dy;
    s32 err;
    u8* p;

    if (x1 < x0) {
        dx = x0 - x1;
    } else {
        dx = x1 - x0;
    }
    if (y1 < y0) {
        dy = y0 - y1;
    } else {
        dy = y1 - y0;
    }
    err = dy / 2;
    if (x1 >= x0) {
        for (; y0 <= y1; y0++) {
            err -= dx;
            if (err & 0x8000) {
                err += dy;
                x0++;
            }
            if ((u16)x0 < 320 && y0 >= 0 && y0 < 240) {
                p = D_8010AC38_game_guys_roulette.buf[D_8010AC34_game_guys_roulette] + x0 / 2 + y0 * 160;
                if (x0 & 1) {
                    *p |= 7;
                } else {
                    *p |= 0x70;
                }
            }
        }
    } else {
        for (; y0 <= y1; y0++) {
            err -= dx;
            if (err & 0x8000) {
                err += dy;
                x0--;
            }
            if ((u16)x0 < 320 && y0 >= 0 && y0 < 240) {
                p = D_8010AC38_game_guys_roulette.buf[D_8010AC34_game_guys_roulette] + x0 / 2 + y0 * 160;
                if (x0 & 1) {
                    *p |= 7;
                } else {
                    *p |= 0x70;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_42_game_guys_roulette/2FF5F0", func_8010A3F4_game_guys_roulette);
#endif

