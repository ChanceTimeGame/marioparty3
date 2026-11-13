#include "common.h"
#include "mallocblock.h"

/* A row of gauges drawn with two esprites per cell (frame and fill). */
typedef struct MgGauge {
    /* 0x00 */ u16 *frame;  /* esprite ids, D_800EBDFC_minigame entries */
    /* 0x04 */ u16 *fill;   /* esprite ids, D_800EBDFC_minigame entries */
    /* 0x08 */ f32 min;
    /* 0x0C */ f32 max;
    /* 0x10 */ f32 ratio;   /* fill level, 0.0 to 1.0 */
    /* 0x14 */ u16 flags;   /* 1 hidden, 2 full (blinking) */
    /* 0x16 */ u16 blink;
} MgGauge; /* size 0x18 */

void func_8000BBFC_main(u16 spriteId, s16 arg1);

void func_800E9F40_minigame(s16 idx, s32 x, s32 y, s16 dir);
void func_800EA0FC_minigame(s16 idx, f32 min, f32 max);
void func_800EA178_minigame(s16 idx, f32 value);
void func_800EA1E4_minigame(s16 idx, u16 attr);
void func_800EA2A8_minigame(s16 idx);
void func_800EA444_minigame(s16 idx);

extern s16 D_800EBDF0_minigame;
extern MgGauge *D_800EBDF4_minigame;
extern s16 D_800EBDF8_minigame;
extern s16 D_800EBDFA_minigame;
extern u16 D_800EBDFC_minigame;

void func_800E9C20_minigame(s16 count, u16 len) {
    s32 i;
    s32 j;

    D_800EBDF0_minigame = count;
    D_800EBDFC_minigame = len;
    D_800EBDF4_minigame = HuMemAllocTag(count * sizeof(MgGauge), 0x7918);
    D_800EBDF8_minigame = func_8000B838_main(0x210018);
    D_800EBDFA_minigame = func_8000B838_main(0x210019);
    for (i = 0; i < count; i++) {
        D_800EBDF4_minigame[i].frame = HuMemAllocTag(len * 2, 0x7918);
        D_800EBDF4_minigame[i].fill = HuMemAllocTag(len * 2, 0x7918);
        D_800EBDF4_minigame[i].blink = 0;
        D_800EBDF4_minigame[i].flags = 0;
        for (j = 0; j < len; j++) {
            D_800EBDF4_minigame[i].frame[j] = InitEspriteSlot(D_800EBDF8_minigame, 0, 0);
            D_800EBDF4_minigame[i].fill[j] = InitEspriteSlot(D_800EBDFA_minigame, 0, 0);
        }
        func_800E9F40_minigame(i, 24, 16, 0);
        func_800EA0FC_minigame(i, 0.0f, 100.0f);
        func_800EA178_minigame(i, 0.0f);
        func_800EA1E4_minigame(i, 0x8000);
        func_800EA444_minigame(i);
    }
}

void func_800E9E28_minigame(void) {
    s32 i;
    s32 j;

    for (i = 0; i < D_800EBDF0_minigame; i++) {
        for (j = 0; j < D_800EBDFC_minigame; j++) {
            func_8000C184_main(D_800EBDF4_minigame[i].frame[j]);
            func_8000C184_main(D_800EBDF4_minigame[i].fill[j]);
        }
        HuMemFree(D_800EBDF4_minigame[i].frame);
        HuMemFree(D_800EBDF4_minigame[i].fill);
    }
    HuSprKill(D_800EBDF8_minigame);
    HuSprKill(D_800EBDFA_minigame);
}

void func_800E9F40_minigame(s16 idx, s32 x, s32 y, s16 dir) {
    MgGauge *g = &D_800EBDF4_minigame[idx];
    s32 i;
    s32 n;

    switch (dir) {
    case 0:
        for (i = 0; i < D_800EBDFC_minigame; i++) {
            func_8000BBD4_main(g->frame[i], x + (s16)(i * 10 + 5), y + 5);
            func_8000BBD4_main(g->fill[i], x + (s16)(i * 10 + 5), y + 5);
        }
        break;
    case 1:
        for (i = D_800EBDFC_minigame - 1; i >= 0; i--) {
            func_8000BBD4_main(g->frame[i], x + (s16)((D_800EBDFC_minigame - (n = i + 1)) * 10 + 5), y + 5);
            func_8000BBD4_main(g->fill[i], x + (s16)((D_800EBDFC_minigame - n) * 10 + 5), y + 5);
        }
        break;
    }
}

void func_800EA0FC_minigame(s16 idx, f32 min, f32 max) {
    D_800EBDF4_minigame[idx].min = min;
    D_800EBDF4_minigame[idx].max = max;
}

void func_800EA128_minigame(s16 idx, f32 ratio) {
    D_800EBDF4_minigame[idx].ratio = ratio;
    if (!(D_800EBDF4_minigame[idx].flags & 1)) {
        func_800EA2A8_minigame(idx);
    }
}

void func_800EA178_minigame(s16 idx, f32 value) {
    f32 range = D_800EBDF4_minigame[idx].max - D_800EBDF4_minigame[idx].min;

    D_800EBDF4_minigame[idx].ratio = (value - D_800EBDF4_minigame[idx].min) / range;
    if (!(D_800EBDF4_minigame[idx].flags & 1)) {
        func_800EA2A8_minigame(idx);
    }
}

void func_800EA1E4_minigame(s16 idx, u16 attr) {
    s32 i;

    for (i = 0; i < D_800EBDFC_minigame; i++) {
        func_8000BCC8_main(D_800EBDF4_minigame[idx].frame[i], (u16)(attr + 1));
        func_8000BCC8_main(D_800EBDF4_minigame[idx].fill[i], attr);
    }
}

void func_800EA2A8_minigame(s16 idx) {
    MgGauge *g = &D_800EBDF4_minigame[idx];
    u16 flags;
    f32 len;
    f32 ratio;
    f32 step;
    f32 frac;
    s32 full;
    s32 i;

    flags = g->flags;
    g->flags = flags & ~1;
    if (!(flags & 2)) {
        len = D_800EBDFC_minigame;
        ratio = g->ratio;
        full = len * ratio;
        step = 1.0f / len;
        frac = (ratio - step * full) / step;
        for (i = 0; i < D_800EBDFC_minigame; i++) {
            func_8000BB54_main(g->frame[i]);
            if (i < full) {
                func_8000BB54_main(g->fill[i]);
                func_8000BBFC_main(g->fill[i], 0x100);
            } else if (i == full) {
                func_8000BB54_main(g->fill[i]);
                func_8000BBFC_main(g->fill[i], frac * 256.0f);
            } else {
                func_8000BB94_main(g->fill[i]);
            }
        }
    }
}

void func_800EA444_minigame(s16 idx) {
    s32 i;

    D_800EBDF4_minigame[idx].flags |= 1;
    for (i = 0; i < D_800EBDFC_minigame; i++) {
        func_8000BB94_main(D_800EBDF4_minigame[idx].frame[i]);
        func_8000BB94_main(D_800EBDF4_minigame[idx].fill[i]);
    }
}

void func_800EA518_minigame(void) {
    s32 i;
    s32 j;
    MgGauge *g;
    u16 flags;

    for (i = 0; i < D_800EBDF0_minigame; i++) {
        g = &D_800EBDF4_minigame[i];
        flags = g->flags;
        if (flags & 1) {
            continue;
        }
        if (g->ratio >= 1.0f) {
            if (!(flags & 2)) {
                g->flags = flags | 2;
                g->blink = 0;
            }
            if (g->blink < 2) {
                for (j = 0; j < D_800EBDFC_minigame; j++) {
                    func_8000BB94_main(g->fill[j]);
                }
            } else {
                for (j = 0; j < D_800EBDFC_minigame; j++) {
                    func_8000BB54_main(g->fill[j]);
                }
            }
            g->blink = (g->blink + 1) & 3;
        } else if (flags & 2) {
            g->flags = flags & ~2;
            func_800EA2A8_minigame(i);
        }
    }
}
