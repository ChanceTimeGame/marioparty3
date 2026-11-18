#include "ultra64.h"
#include "include_asm.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/util.h"
#include "game/wipe.h"
#include "game/sprite.h"
#include "mallocblock.h"

// sweet surprise B (a copy of roulette B and magic boxes B): the Game Guy title effect (three coloured rings circle the screen and close in, drawn into 4-bit
// sprite images of 320x240 that are cycled through three buffers so the rings leave trails)

/* A ring */
typedef struct GgrRing {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 color;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 r;
    /* 0x0A */ s16 fx; /* Lissajous factors of the circling path */
    /* 0x0C */ s16 fy;
    /* 0x10 */ f32 angle;
    /* 0x14 */ f32 speed;
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
s16 func_8000B838_main(s32 arg0);

// LOCAL
void func_8010B250_game_guys_sweet_surprise(s16 x, s16 y);
void func_8010B51C_game_guys_sweet_surprise(void);
s16 func_8010B5A8_game_guys_sweet_surprise(void);
s16 func_8010C090_game_guys_sweet_surprise(s32 x);
void func_8010C244_game_guys_sweet_surprise(void);
s16 func_8010C2C8_game_guys_sweet_surprise(s32 file, s32 attr, s32 prio, s32 alpha);
void func_8010C39C_game_guys_sweet_surprise(void);
void func_8010C500_game_guys_sweet_surprise(void);
void func_8010C590_game_guys_sweet_surprise(s16 active, s16 x, s16 y, s16 r);
void func_8010C6EC_game_guys_sweet_surprise(s16 active, s16 x, s16 y, s16 color);
void func_8010C72C_game_guys_sweet_surprise(s16 active, s16 x, s16 y, s16 r, s16 color);
void func_8010C924_game_guys_sweet_surprise(s16 x0, s16 y0, s16 x1, s16 y1);

/* .data */
extern s16 D_8010CC60_game_guys_sweet_surprise; /* frame */
extern s16 D_8010CC62_game_guys_sweet_surprise; /* the rings' start y */
extern s16 D_8010CC64_game_guys_sweet_surprise; /* func_8010C090's frame */

extern GgrRing D_8010D010_game_guys_sweet_surprise[3];
extern s16 D_8010D058_game_guys_sweet_surprise; /* centre x */
extern s16 D_8010D05A_game_guys_sweet_surprise; /* centre y */
extern s16 D_8010D05C_game_guys_sweet_surprise; /* circling radius */
extern s16 D_8010D05E_game_guys_sweet_surprise; /* end x */
extern s16 D_8010D060_game_guys_sweet_surprise; /* end y */
extern GgrTrail D_8010D068_game_guys_sweet_surprise[3];
extern GgrLayer D_8010D0D0_game_guys_sweet_surprise; /* the rings' colour layer */
extern s16 D_8010D0FC_game_guys_sweet_surprise; /* buffer drawn this frame */
extern GgrLayer D_8010D0E8_game_guys_sweet_surprise; /* the mask layer */

/* Start the effect: the rings circle the centre on a random path and end at (x, y) */
void func_8010B250_game_guys_sweet_surprise(s16 x, s16 y) {
    s16 paths[3][2] = { { 10, 7 }, { 10, 8 }, { 10, 10 } };
    s16 i;
    s32 k;

    D_8010D058_game_guys_sweet_surprise = 160;
    D_8010D05A_game_guys_sweet_surprise = 120;
    D_8010D05C_game_guys_sweet_surprise = 95;
    D_8010D05E_game_guys_sweet_surprise = x;
    D_8010D060_game_guys_sweet_surprise = y;
    i = 0;
    k = (u8)(rand8() % 3);
    for (; i < 3; i++) {
        D_8010D010_game_guys_sweet_surprise[i].active = 0;
        D_8010D010_game_guys_sweet_surprise[i].fx = paths[k][0];
        D_8010D010_game_guys_sweet_surprise[i].fy = paths[k][1];
        D_8010D010_game_guys_sweet_surprise[i].speed = 1.5f;
        if (k == 0) {
            D_8010D010_game_guys_sweet_surprise[i].speed = 1.75f;
        }
        D_8010D010_game_guys_sweet_surprise[i].angle = i * 120;
        D_8010D010_game_guys_sweet_surprise[i].x =
            D_8010D058_game_guys_sweet_surprise +
            cosdf(D_8010D010_game_guys_sweet_surprise[i].fx * D_8010D010_game_guys_sweet_surprise[i].angle) * D_8010D05C_game_guys_sweet_surprise;
        D_8010D010_game_guys_sweet_surprise[i].y =
            D_8010D05A_game_guys_sweet_surprise +
            sindf(D_8010D010_game_guys_sweet_surprise[i].fy * D_8010D010_game_guys_sweet_surprise[i].angle) * D_8010D05C_game_guys_sweet_surprise;
        D_8010D010_game_guys_sweet_surprise[i].r = 0;
    }
    D_8010D010_game_guys_sweet_surprise[0].color = 1;
    D_8010D010_game_guys_sweet_surprise[1].color = 2;
    D_8010D010_game_guys_sweet_surprise[2].color = 4;
    D_8010D0E8_game_guys_sweet_surprise.alpha = 0x80;
    D_8010D0D0_game_guys_sweet_surprise.alpha = 0x100;
    func_8010C39C_game_guys_sweet_surprise();
    func_8010C500_game_guys_sweet_surprise();
    D_8010D0FC_game_guys_sweet_surprise = 0;
}

/* Reset the mask layer (unused here) */
void func_8010B51C_game_guys_sweet_surprise(void) {
    func_8010C500_game_guys_sweet_surprise();
    D_8010D0FC_game_guys_sweet_surprise = 0;
    D_8010D0E8_game_guys_sweet_surprise.alpha = 0;
    func_80055458_main(D_8010D0E8_game_guys_sweet_surprise.grp, 0, 0);
    HuSprAttrReset(D_8010D0E8_game_guys_sweet_surprise.grp, 0, 0xFFFF);
    HuSprAttrSet(D_8010D0E8_game_guys_sweet_surprise.grp, 0, 0x1000);
    D_8010D0E8_game_guys_sweet_surprise.spr->unk_84->unk00->unk00 = D_8010D0E8_game_guys_sweet_surprise.buf[D_8010D0FC_game_guys_sweet_surprise];
}

/* One frame of the effect once the wipe is done: the rings grow in, circle, close in on the end point, merge into one
   that swells while the layers fade; returns 1 when it is over */
s16 func_8010B5A8_game_guys_sweet_surprise(void) {
    s16 i;

    if (WipeStatGet() == 1) {
        return 0;
    }
    if (D_8010CC60_game_guys_sweet_surprise >= 5) {
        if (D_8010CC60_game_guys_sweet_surprise < 15) {
            for (i = 0; i < 3; i++) {
                D_8010D010_game_guys_sweet_surprise[i].active = 1;
                D_8010D010_game_guys_sweet_surprise[i].r = sindf((D_8010CC60_game_guys_sweet_surprise - 5) * 9.0f) * 45.0f;
            }
        } else if (D_8010CC60_game_guys_sweet_surprise < 20) {
            for (i = 0; i < 3; i++) {
                D_8010D010_game_guys_sweet_surprise[i].r = 45;
            }
        } else if (D_8010CC60_game_guys_sweet_surprise < 47) {
            for (i = 0; i < 3; i++) {
                D_8010D010_game_guys_sweet_surprise[i].angle += D_8010D010_game_guys_sweet_surprise[i].speed;
                if (D_8010D010_game_guys_sweet_surprise[i].angle >= 360.0f) {
                    D_8010D010_game_guys_sweet_surprise[i].angle -= 360.0f;
                }
                if (D_8010D010_game_guys_sweet_surprise[i].angle < 0.0f) {
                    D_8010D010_game_guys_sweet_surprise[i].angle += 360.0f;
                }
                D_8010D010_game_guys_sweet_surprise[i].x =
                    D_8010D058_game_guys_sweet_surprise +
                    cosdf(D_8010D010_game_guys_sweet_surprise[i].fx * D_8010D010_game_guys_sweet_surprise[i].angle) * D_8010D05C_game_guys_sweet_surprise;
                D_8010D010_game_guys_sweet_surprise[i].y =
                    D_8010D05A_game_guys_sweet_surprise +
                    sindf(D_8010D010_game_guys_sweet_surprise[i].fy * D_8010D010_game_guys_sweet_surprise[i].angle) * D_8010D05C_game_guys_sweet_surprise;
            }
        } else if (D_8010CC60_game_guys_sweet_surprise < 80) {
            if (D_8010D05C_game_guys_sweet_surprise > 0) {
                D_8010D05C_game_guys_sweet_surprise -= 3;
                if (D_8010D05C_game_guys_sweet_surprise <= 0) {
                    D_8010D05C_game_guys_sweet_surprise = 0;
                }
            }
            D_8010D05A_game_guys_sweet_surprise =
                D_8010CC62_game_guys_sweet_surprise - sindf((D_8010CC60_game_guys_sweet_surprise - 47) * (90.0f / 33)) *
                                                   (D_8010CC62_game_guys_sweet_surprise - D_8010D060_game_guys_sweet_surprise);
            if (D_8010CC60_game_guys_sweet_surprise == 79) {
                D_8010D05A_game_guys_sweet_surprise = D_8010D060_game_guys_sweet_surprise;
            }
            for (i = 0; i < 3; i++) {
                D_8010D010_game_guys_sweet_surprise[i].angle += D_8010D010_game_guys_sweet_surprise[i].speed;
                if (D_8010D010_game_guys_sweet_surprise[i].angle >= 360.0f) {
                    D_8010D010_game_guys_sweet_surprise[i].angle -= 360.0f;
                }
                if (D_8010D010_game_guys_sweet_surprise[i].angle < 0.0f) {
                    D_8010D010_game_guys_sweet_surprise[i].angle += 360.0f;
                }
                D_8010D010_game_guys_sweet_surprise[i].x =
                    D_8010D058_game_guys_sweet_surprise +
                    cosdf(D_8010D010_game_guys_sweet_surprise[i].fx * D_8010D010_game_guys_sweet_surprise[i].angle) * D_8010D05C_game_guys_sweet_surprise;
                D_8010D010_game_guys_sweet_surprise[i].y =
                    D_8010D05A_game_guys_sweet_surprise +
                    sindf(D_8010D010_game_guys_sweet_surprise[i].fy * D_8010D010_game_guys_sweet_surprise[i].angle) * D_8010D05C_game_guys_sweet_surprise;
            }
        } else if (D_8010CC60_game_guys_sweet_surprise < 90) {
            for (i = 1; i < 3; i++) {
                D_8010D010_game_guys_sweet_surprise[i].active = 0;
            }
            D_8010D010_game_guys_sweet_surprise[0].color = 7;
        } else if (D_8010CC60_game_guys_sweet_surprise >= 120) {
            func_8010C244_game_guys_sweet_surprise();
            return 1;
        } else {
            D_8010D010_game_guys_sweet_surprise[0].r = sindf((D_8010CC60_game_guys_sweet_surprise - 90) * 3.0f) * 50.0f + 45.0f;
            D_8010D0E8_game_guys_sweet_surprise.alpha = 128.0f - sindf((D_8010CC60_game_guys_sweet_surprise - 90) * 3.0f) * 128.0f;
            D_8010D0D0_game_guys_sweet_surprise.alpha = 256.0f - sindf((D_8010CC60_game_guys_sweet_surprise - 90) * 3.0f) * 256.0f;
        }
    }
    if (D_8010CC60_game_guys_sweet_surprise == 15) {
        HuAudFXPlay(0x537);
    }
    if (D_8010CC60_game_guys_sweet_surprise == 90) {
        func_8004AB0C_main(30);
        HuAudSeqPlay(0x43);
    }
    if (D_8010CC60_game_guys_sweet_surprise == 115) {
        HuAudFXPlay(0x2A1);
    }
    if (D_8010D0E8_game_guys_sweet_surprise.alpha <= 0) {
        D_8010D0E8_game_guys_sweet_surprise.alpha = 0;
    }
    func_80055458_main(D_8010D0E8_game_guys_sweet_surprise.grp, 0, D_8010D0E8_game_guys_sweet_surprise.alpha);
    if (D_8010D0D0_game_guys_sweet_surprise.alpha <= 0) {
        D_8010D0D0_game_guys_sweet_surprise.alpha = 0;
    }
    func_80055458_main(D_8010D0D0_game_guys_sweet_surprise.grp, 0, D_8010D0D0_game_guys_sweet_surprise.alpha);
    if (D_8010CC60_game_guys_sweet_surprise < 90) {
        for (i = 0; i < 3; i++) {
            func_8010C590_game_guys_sweet_surprise(D_8010D068_game_guys_sweet_surprise[D_8010D0FC_game_guys_sweet_surprise].active[i],
                                             D_8010D068_game_guys_sweet_surprise[D_8010D0FC_game_guys_sweet_surprise].x[i],
                                             D_8010D068_game_guys_sweet_surprise[D_8010D0FC_game_guys_sweet_surprise].y[i],
                                             D_8010D068_game_guys_sweet_surprise[D_8010D0FC_game_guys_sweet_surprise].r[i]);
            D_8010D068_game_guys_sweet_surprise[D_8010D0FC_game_guys_sweet_surprise].active[i] = D_8010D010_game_guys_sweet_surprise[i].active;
            D_8010D068_game_guys_sweet_surprise[D_8010D0FC_game_guys_sweet_surprise].x[i] = D_8010D010_game_guys_sweet_surprise[i].x;
            D_8010D068_game_guys_sweet_surprise[D_8010D0FC_game_guys_sweet_surprise].y[i] = D_8010D010_game_guys_sweet_surprise[i].y;
            D_8010D068_game_guys_sweet_surprise[D_8010D0FC_game_guys_sweet_surprise].r[i] = D_8010D010_game_guys_sweet_surprise[i].r;
        }
    }
    if (D_8010CC60_game_guys_sweet_surprise < 20) {
        for (i = 0; i < 3; i++) {
            func_8010C72C_game_guys_sweet_surprise(D_8010D010_game_guys_sweet_surprise[i].active, D_8010D010_game_guys_sweet_surprise[i].x,
                                             D_8010D010_game_guys_sweet_surprise[i].y, D_8010D010_game_guys_sweet_surprise[i].r,
                                             D_8010D010_game_guys_sweet_surprise[i].color);
        }
    } else if (D_8010CC60_game_guys_sweet_surprise < 81) {
        for (i = 0; i < 3; i++) {
            func_8010C6EC_game_guys_sweet_surprise(D_8010D010_game_guys_sweet_surprise[i].active, D_8010D010_game_guys_sweet_surprise[i].x,
                                             D_8010D010_game_guys_sweet_surprise[i].y, D_8010D010_game_guys_sweet_surprise[i].color);
        }
    } else {
        func_8010C72C_game_guys_sweet_surprise(D_8010D010_game_guys_sweet_surprise[0].active, D_8010D010_game_guys_sweet_surprise[0].x,
                                         D_8010D010_game_guys_sweet_surprise[0].y, D_8010D010_game_guys_sweet_surprise[0].r,
                                         D_8010D010_game_guys_sweet_surprise[0].color);
    }
    D_8010D0E8_game_guys_sweet_surprise.spr->unk_84->unk00->unk00 = D_8010D0E8_game_guys_sweet_surprise.buf[D_8010D0FC_game_guys_sweet_surprise];
    D_8010D0D0_game_guys_sweet_surprise.spr->unk_84->unk00->unk00 = D_8010D0D0_game_guys_sweet_surprise.buf[D_8010D0FC_game_guys_sweet_surprise];
    D_8010D0FC_game_guys_sweet_surprise = (s16)(D_8010D0FC_game_guys_sweet_surprise + 1) % 3;
    D_8010CC60_game_guys_sweet_surprise++;
    return 0;
}

/* Another ending of the effect (not called in this overlay): fade the mask layer in, then draw lines falling from
   above x; returns 1 when done */
// masked 4: retail computes x - 40 and x + 40 before the loop's s16 copy of x (scheduling only)
#ifdef NON_MATCHING
s16 func_8010C090_game_guys_sweet_surprise(s32 x) {
    s16 i;
    s32 left;
    s32 right;

    D_8010D0E8_game_guys_sweet_surprise.spr->unk_84->unk00->unk00 = D_8010D0E8_game_guys_sweet_surprise.buf[0];
    if (D_8010CC64_game_guys_sweet_surprise++ < 10) {
        D_8010D0E8_game_guys_sweet_surprise.alpha = 0;
        return 0;
    }
    if (D_8010CC64_game_guys_sweet_surprise < 30) {
        D_8010D0E8_game_guys_sweet_surprise.alpha = sindf((D_8010CC64_game_guys_sweet_surprise - 10) * 4.5f) * 128.0f;
        func_80055458_main(D_8010D0E8_game_guys_sweet_surprise.grp, 0, D_8010D0E8_game_guys_sweet_surprise.alpha);
        return 0;
    }
    if (D_8010CC64_game_guys_sweet_surprise >= 40) {
        if (D_8010CC64_game_guys_sweet_surprise < 90) {
            i = 0;
            left = x - 40;
            right = x + 40;
            for (; i < 5; i++) {
                func_8010C924_game_guys_sweet_surprise(x, -100, i + (left + D_8010CC64_game_guys_sweet_surprise), 240);
                func_8010C924_game_guys_sweet_surprise(x, -100, (right - D_8010CC64_game_guys_sweet_surprise) - i, 240);
            }
            D_8010CC64_game_guys_sweet_surprise += 4;
            return 0;
        }
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C090_game_guys_sweet_surprise);
#endif

void func_8010C244_game_guys_sweet_surprise(void) {
    HuSprAttrSet(D_8010D0E8_game_guys_sweet_surprise.grp, 0, 0x8000);
    HuSprAttrSet(D_8010D0D0_game_guys_sweet_surprise.grp, 0, 0x8000);
    D_8010D0E8_game_guys_sweet_surprise.spr->unk_84->unk00->unk00 = D_8010D0E8_game_guys_sweet_surprise.buf[0];
    D_8010D0D0_game_guys_sweet_surprise.spr->unk_84->unk00->unk00 = D_8010D0D0_game_guys_sweet_surprise.buf[0];
}

s16 func_8010C2C8_game_guys_sweet_surprise(s32 file, s32 attr, s32 prio, s32 alpha) {
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
void func_8010C39C_game_guys_sweet_surprise(void) {
    s16* pal;

    D_8010D0E8_game_guys_sweet_surprise.grp = func_8010C2C8_game_guys_sweet_surprise(0x66000C, 0, 10, 0x80);
    D_8010D0E8_game_guys_sweet_surprise.spr = HuSprGet(D_8010D0E8_game_guys_sweet_surprise.grp, 0);
    D_8010D0E8_game_guys_sweet_surprise.buf[0] = D_8010D0E8_game_guys_sweet_surprise.spr->unk_84->unk00->unk00;
    pal = D_8010D0E8_game_guys_sweet_surprise.spr->unk_84->unk0C;
    D_8010D0E8_game_guys_sweet_surprise.buf[1] = HuMemAllocTag(0x9600, 0x7918);
    D_8010D0E8_game_guys_sweet_surprise.buf[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 1;
    pal[1] = 0x3F;
    pal[2] = 0x7C1;
    pal[3] = 0x7FF;
    pal[4] = -0x7FF;
    pal[5] = -0x7C1;
    pal[6] = -0x3F;
    pal[7] = -2;
    D_8010D0D0_game_guys_sweet_surprise.grp = func_8010C2C8_game_guys_sweet_surprise(0x66000C, 0, 10, 0x100);
    D_8010D0D0_game_guys_sweet_surprise.spr = HuSprGet(D_8010D0D0_game_guys_sweet_surprise.grp, 0);
    D_8010D0D0_game_guys_sweet_surprise.buf[0] = D_8010D0D0_game_guys_sweet_surprise.spr->unk_84->unk00->unk00;
    pal = D_8010D0D0_game_guys_sweet_surprise.spr->unk_84->unk0C;
    D_8010D0D0_game_guys_sweet_surprise.buf[1] = HuMemAllocTag(0x9600, 0x7918);
    D_8010D0D0_game_guys_sweet_surprise.buf[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 1;
    pal[1] = 0;
}

void func_8010C500_game_guys_sweet_surprise(void) {
    s32 i;
    s32 j;
    u8* p;

    for (i = 0; i < 3; i++) {
        p = D_8010D0E8_game_guys_sweet_surprise.buf[i];
        for (j = 0; j < 0x9600; j++) {
            *p++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        p = D_8010D0D0_game_guys_sweet_surprise.buf[i];
        for (j = 0; j < 0x9600; j++) {
            *p++ = 0;
        }
    }
}

/* Clear a ring's square from this frame's buffers */
// masked 6: retail's strength-reduced row pointers come from C not found (this C writes them out; same bytes cleared)
#ifdef NON_MATCHING
void func_8010C590_game_guys_sweet_surprise(s16 active, s16 x, s16 y, s16 r) {
    s32 xx;
    s32 yy;
    u8* pa;
    u8* pb;

    if (active == 0 || r < 1) {
        return;
    }
    pa = D_8010D0E8_game_guys_sweet_surprise.buf[D_8010D0FC_game_guys_sweet_surprise] + (x + r) / 2 + (y - 1 - r) * 160 + 1;
    pb = D_8010D0D0_game_guys_sweet_surprise.buf[D_8010D0FC_game_guys_sweet_surprise] + (x + r) / 2 + (y - 1 - r) * 160 + 1;
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C590_game_guys_sweet_surprise);
#endif

void func_8010C6EC_game_guys_sweet_surprise(s16 active, s16 x, s16 y, s16 color) {
    func_8010C72C_game_guys_sweet_surprise(active, x, y, 45, color);
}

/* Draw a filled ring of radius r in a colour (a 4-bit pixel pair per byte) into this frame's buffers, the mask
   layer gets the colour and the colour layer a 1 */
// masked 35: retail squares r before the early-out test and allocates differently; logic checked block by block
#ifdef NON_MATCHING
void func_8010C72C_game_guys_sweet_surprise(s16 active, s16 x, s16 y, s16 r, s16 color) {
    s32 xx;
    s32 yy;
    u8* pa;
    u8* pb;

    if (active == 0 || r < 1) {
        return;
    }
    for (yy = y - r; yy < y + r; yy++) {
        pa = D_8010D0E8_game_guys_sweet_surprise.buf[D_8010D0FC_game_guys_sweet_surprise] + (x - r) / 2 + yy * 160;
        pb = D_8010D0D0_game_guys_sweet_surprise.buf[D_8010D0FC_game_guys_sweet_surprise] + (x - r) / 2 + yy * 160;
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C72C_game_guys_sweet_surprise);
#endif

/* Draw a line in colour 7 into this frame's mask buffer (Bresenham, stepping in y) */
// masked 39: two y-stepping Bresenham loops, register allocation and loop layout differ; logic checked against the asm
#ifdef NON_MATCHING
void func_8010C924_game_guys_sweet_surprise(s16 x0, s16 y0, s16 x1, s16 y1) {
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
                p = D_8010D0E8_game_guys_sweet_surprise.buf[D_8010D0FC_game_guys_sweet_surprise] + x0 / 2 + y0 * 160;
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
                p = D_8010D0E8_game_guys_sweet_surprise.buf[D_8010D0FC_game_guys_sweet_surprise] + x0 / 2 + y0 * 160;
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/3151F0", func_8010C924_game_guys_sweet_surprise);
#endif

