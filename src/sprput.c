#include "common.h"
#include "mallocblock.h"

/* Sprite drawing (MP2 src/84FF0.c: SprDispCheck .. func_80086C08_87808; MP1 src/sprput.c). */

/* The sprite object as these functions read it. Same layout as HuSprite (include/game/sprite.h,
   0x210 bytes), with the field types the code uses: the screen position (0x04, 0x08) and rotation
   (0x20) are f32, the clip rectangle (0x3C, 0x3E) is s16, 0x104 is the palette pointer and 0x120 is
   an index into 0x128/0x134. */
typedef struct SprObj {
    /* 0x000 */ s16 unk_00;
    /* 0x002 */ s16 unk_02;
    /* 0x004 */ f32 unk_04;
    /* 0x008 */ f32 unk_08;
    /* 0x00C */ s16 unk_0C;
    /* 0x00E */ s16 unk_0E;
    /* 0x010 */ f32 unk_10;
    /* 0x014 */ u16 prio;
    /* 0x018 */ f32 unk_18;
    /* 0x01C */ f32 unk_1C;
    /* 0x020 */ f32 unk_20;
    /* 0x024 */ s32 unk_24;
    /* 0x028 */ u8 unk_28[4];
    /* 0x02C */ u16 unk_2C;
    /* 0x02E */ s16 unk_2E;
    /* 0x030 */ f32 unk_30;
    /* 0x034 */ f32 unk_34;
    /* 0x038 */ s16 unk_38;
    /* 0x03A */ s16 unk_3A;
    /* 0x03C */ s16 unk_3C;
    /* 0x03E */ s16 unk_3E;
    /* 0x040 */ u16 unk_40;
    /* 0x042 */ u16 unk_42;
    /* 0x044 */ s32 unk_44;
    /* 0x048 */ f32 unk_48;
    /* 0x04C */ f32 unk_4C;
    /* 0x050 */ f32 unk_50;
    /* 0x054 */ f32 unk_54;
    /* 0x058 */ f32 unk_58;
    /* 0x05C */ s32 unk_5C;
    /* 0x060 */ f32 unk_60;
    /* 0x064 */ f32 unk_64;
    /* 0x068 */ HuSprAnm unk_68;
    /* 0x084 */ HuSprite_Unk84_Struct* unk_84;
    /* 0x088 */ u8 unk_88;
    /* 0x08A */ s16 unk_8A;
    /* 0x08C */ f32 unk_8C;
    /* 0x090 */ s16 unk_90;
    /* 0x092 */ s8 unk_92;
    /* 0x093 */ u8 unk_93;
    /* 0x094 */ u8 unk_94;
    /* 0x098 */ HuSprAnmDesc* unk_98;
    /* 0x09C */ u16 unk_9C[0x10];
    /* 0x0BC */ s32 unk_BC[0x10];
    /* 0x0FC */ f32 unk_FC;
    /* 0x100 */ s16 unk_100;
    /* 0x104 */ u16* unk_104;
    /* 0x108 */ void* unk_108[3];
    /* 0x114 */ s16 unk_114;
    /* 0x116 */ s16 unk_116;
    /* 0x118 */ struct SprObj* unk_118;
    /* 0x11C */ struct SprObj* unk_11C;
    /* 0x120 */ s32 unk_120;
    /* 0x124 */ void* unk_124;
    /* 0x128 */ void* unk_128[3];
    /* 0x134 */ void* unk_134[3];
    /* 0x140 */ Mtx unk_140[3];
    /* 0x200 */ char unk_200[4];
    /* 0x204 */ u16 unk_204;
    /* 0x206 */ u16 unk_206;
    /* 0x208 */ u16 unk_208;
    /* 0x20A */ u16 unk_20A;
    /* 0x20C */ char unk_20C[4];
} SprObj; // size 0x210

typedef struct SprPoint {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} SprPoint; // size 0x8

extern s32 D_800A1EB0_main;    /* TMEM address of the second texture */
extern s32 D_800A1EB4_main[4]; /* other-mode shifts */
/* D_800A1ED0_main follows this table: the code indexes [0..3] here, and index 3 reads D_800A1ED0_main[0] */
extern s32 D_800A1EC4_main[3];
extern s32 D_800A1ED0_main[4];
extern s16 D_800A1EE0_main[156];
extern s16 D_800A2018_main[156];
extern SprPoint D_800BD810_main[4]; /* corners of the sprite being checked */
/* sprite texture-load state, set by SprDisp for PutSprite and SprTexLoad */
extern s32 D_800BD830_main; /* texture format (G_IM_FMT_*) */
extern s32 D_800BD834_main; /* texel size (G_IM_SIZ_*) */
extern s32 D_800BD838_main;
extern s32 D_800BD83C_main;
extern s32 D_800BD840_main; /* texture-load strips */
extern s32 D_800BD844_main; /* rows per strip */
extern s32 D_800BD848_main; /* rows in the last strip */
extern s32 D_800BD84C_main; /* texture-load strips drawn */
extern s32 D_800BD850_main; /* drawn with a matrix */
extern Gfx* D_800CCF30_main; /* scratch display list for cached sprites */
extern u8 D_800D2008_main;
extern Vtx* D_800D59F4_main;

void func_8003521C_main(void* mtx, f64 x, f64 y, f64 rot);
void func_80017CD0_main(Mtx* mtx, f32 sx, f32 sy, f32 sz);
void func_800341D0_main(Gfx** gfx, s32 timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult,
                        s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                        s32 shiftt);
void func_80034998_main(Gfx** gfx, s32 timg, s32 fmt, u32 width, s32 height, s32 uls, s32 ult, s32 lrs,
                        s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void func_800343FC_main(Gfx** gfx, s32 timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult,
                        s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                        s32 shiftt, s32 rtile, s32 tmem);
void func_80034C08_main(Gfx** gfx, s32 timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult,
                        s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                        s32 shiftt, s32 rtile, s32 tmem);
void func_80034F70_main(Gfx** gfx, s32 timg, s32 fmt, u32 width, s32 height, s32 uls, s32 ult, s32 lrs,
                        s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt,
                        s32 rtile, s32 tmem);

s32 DispCheck(SprPoint* p);
Gfx* PutSprite(Gfx* gfx, SprObj* obj, Vtx* vtx, Mtx* mtx, void* cam);
void SprTexLoad(Gfx** gfx, SprObj* obj, u16 rows, u16 uls, u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt,
                u16 masks, u16 maskt);
void func_80059CDC_main(Gfx** gfx, SprObj* obj, u16 rows, u16 uls, u16 ult, u16 lrs, u16 lrt, u16 cms,
                        u16 cmt, u16 masks, u16 maskt);

s32 SprDispCheck(SprObj* obj) {
    HuSprite_Unk84_Unk00_Struct* cel;
    f32 s;
    f32 c;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;

    cel = &obj->unk_84->unk00[obj->unk_90];
    s = sindf(obj->unk_20);
    c = cosdf(obj->unk_20);
    if (!(obj->unk_24 & 0x10000)) {
        x0 = -(u16)cel->unk08 * obj->unk_18;
        y0 = -(u16)cel->unk0A * obj->unk_1C;
        x1 = (cel->unk04 - (u16)cel->unk08) * obj->unk_18;
        y1 = (cel->unk06 - (u16)cel->unk0A) * obj->unk_1C;
    } else {
        x0 = obj->unk_3C;
        y0 = obj->unk_3E;
        x1 = (s16)obj->unk_40;
        y1 = (s16)obj->unk_42;
    }
    D_800BD810_main[0].x = c * x0 + s * y0 + obj->unk_04;
    D_800BD810_main[0].y = -s * x0 + c * y0 + obj->unk_08;
    D_800BD810_main[1].x = c * x1 + s * y0 + obj->unk_04;
    D_800BD810_main[1].y = -s * x1 + c * y0 + obj->unk_08;
    D_800BD810_main[2].x = c * x1 + s * y1 + obj->unk_04;
    D_800BD810_main[2].y = -s * x1 + c * y1 + obj->unk_08;
    D_800BD810_main[3].x = c * x0 + s * y1 + obj->unk_04;
    D_800BD810_main[3].y = -s * x0 + c * y1 + obj->unk_08;
    return DispCheck(D_800BD810_main);
}

/* 1 if any part of the quad p[0..3] is on the 320x240 screen */
s32 DispCheck(SprPoint* p) {
    s32 i;
    s32 j;
    f32 dx;
    f32 dy;
    f32 t;
    f32 v;
    f32 cx;
    f32 cy;

    for (i = 0; i < 4; i++) {
        if (p[i].x >= 0.0f && p[i].x < 320.0f && p[i].y >= 0.0f && p[i].y < 240.0f) {
            return 1;
        }
    }
    for (i = 0; i < 4; i++) {
        j = i + 1;
        if (j >= 4) {
            j = 0;
        }
        dx = p[j].x - p[i].x;
        dy = p[j].y - p[i].y;
        if (dy != 0.0f) {
            t = (0.0f - p[i].y) / dy;
            if ((0.0f <= t) & (t < 1.0f)) {
                v = p[i].x + t * dx;
                if ((0.0f <= v) & (v < 320.0f)) {
                    return 1;
                }
            }
            t = (240.0f - p[i].y) / dy;
            if ((0.0f <= t) & (t < 1.0f)) {
                v = p[i].x + t * dx;
                if ((0.0f <= v) & (v < 320.0f)) {
                    return 1;
                }
            }
        }
        if (dx != 0.0f) {
            t = (0.0f - p[i].x) / dx;
            if ((0.0f <= t) & (t < 1.0f)) {
                v = p[i].y + t * dy;
                if ((0.0f <= v) & (v < 240.0f)) {
                    return 1;
                }
            }
            t = (320.0f - p[i].x) / dx;
            if ((0.0f <= t) & (t < 1.0f)) {
                v = p[i].y + t * dy;
                if ((0.0f <= v) & (v < 240.0f)) {
                    return 1;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        j = (i + 1 < 4) ? i + 1 : 0;
        dx = p[j].x - p[i].x;
        dy = p[j].y - p[i].y;
        cx = 160.0f - p[j].x;
        cy = 120.0f - p[j].y;
        if (dx * cy - dy * cx < 0.0f) {
            return 0;
        }
    }
    return 1;
}

void SprDisp(Gfx** gfx, SprObj* obj, void* cam) {
    f32 mf[4][4];
    Gfx* g;
    f32 sx;
    f32 sy;
    f32 ox;
    f32 oy;
    HuSprite_Unk84_Unk00_Struct* cel;
    s32 w;
    s32 idx;
    s32 rm;
    u32 intensity;
    Vtx* vtx;
    Gfx* end;
    s32 size;

    g = *gfx;
    sx = obj->unk_18;
    sy = obj->unk_1C;
    if (obj->unk_84 == NULL) {
        return;
    }
    cel = &obj->unk_84->unk00[obj->unk_90];
    if ((sx <= 0.0f) | (sy <= 0.0f)) {
        return;
    }
    if (SprDispCheck(obj) == 0) {
        return;
    }
    gDPSetScissor(g++, G_SC_NON_INTERLACE, obj->unk_204, obj->unk_206, obj->unk_208, obj->unk_20A);
    switch (obj->unk_84->unk18) {
        case 4:
            D_800BD834_main = G_IM_SIZ_4b;
            if (obj->unk_84->unk1A == 1) {
                D_800BD830_main = G_IM_FMT_IA;
                gDPSetTextureLUT(g++, G_TT_NONE);
            } else {
                D_800BD830_main = G_IM_FMT_CI;
                if (obj->unk_98 != NULL) {
                    gDPLoadTLUT_pal16(g++, 0, obj->unk_104);
                } else {
                    gDPLoadTLUT_pal16(g++, 0, obj->unk_84->unk0C);
                }
                gDPSetTextureLUT(g++, G_TT_RGBA16);
                D_800A1EB0_main = 0x80;
            }
            D_800BD838_main = 0;
            break;
        case 8:
            D_800BD834_main = G_IM_SIZ_8b;
            if (obj->unk_84->unk1A == 1) {
                D_800BD830_main = G_IM_FMT_IA;
                gDPSetTextureLUT(g++, G_TT_NONE);
            } else {
                D_800BD830_main = G_IM_FMT_CI;
                if (obj->unk_98 != NULL) {
                    gDPLoadTLUT_pal256(g++, obj->unk_104);
                } else {
                    gDPLoadTLUT_pal256(g++, obj->unk_84->unk0C);
                }
                gDPSetTextureLUT(g++, G_TT_RGBA16);
                D_800A1EB0_main = 0x80;
            }
            D_800BD838_main = 2;
            break;
        case 0x10:
            D_800BD834_main = G_IM_SIZ_16b;
            if (obj->unk_84->unk1A == 1) {
                D_800BD830_main = G_IM_FMT_IA;
            } else {
                D_800BD830_main = G_IM_FMT_RGBA;
            }
            gDPSetTextureLUT(g++, G_TT_NONE);
            D_800A1EB0_main = 0x100;
            D_800BD838_main = 2;
            break;
        case 0x20:
            D_800BD834_main = G_IM_SIZ_32b;
            D_800BD830_main = G_IM_FMT_RGBA;
            gDPSetTextureLUT(g++, G_TT_NONE);
            D_800A1EB0_main = 0x100;
            D_800BD838_main = 2;
            break;
        case 0x8004:
            D_800BD834_main = G_IM_SIZ_4b;
            D_800BD830_main = G_IM_FMT_I;
            gDPSetTextureLUT(g++, G_TT_NONE);
            D_800A1EB0_main = 0x100;
            D_800BD838_main = 0;
            break;
        case 0x8008:
            D_800BD834_main = G_IM_SIZ_8b;
            D_800BD830_main = G_IM_FMT_I;
            gDPSetTextureLUT(g++, G_TT_NONE);
            D_800A1EB0_main = 0x100;
            D_800BD838_main = 2;
            break;
    }
    w = (((cel->unk04 << D_800BD834_main) >> 4) << 4) >> D_800BD834_main;
    if (w < cel->unk04) {
        w += 16 >> D_800BD834_main;
    }
    switch (D_800BD830_main) {
        case G_IM_FMT_CI:
            if ((0x1000 >> D_800BD834_main) >= cel->unk06 * w) {
                D_800BD844_main = cel->unk06;
            } else {
                D_800BD844_main = (0x1000 >> D_800BD834_main) / w;
            }
            break;
        case G_IM_FMT_I:
            if (cel->unk06 * w <= 0x1000) {
                D_800BD844_main = cel->unk06;
            } else {
                D_800BD844_main = 0x1000 / w;
            }
            break;
        default:
            if ((0x2000 >> D_800BD834_main) >= cel->unk06 * w) {
                D_800BD844_main = cel->unk06;
            } else {
                D_800BD844_main = (0x2000 >> D_800BD834_main) / w;
            }
            break;
    }
    D_800BD840_main = cel->unk06 / D_800BD844_main;
    D_800BD848_main = cel->unk06 - D_800BD840_main * D_800BD844_main;
    if (cel->unk04 % (16 >> D_800BD834_main) == 0 && ((cel->unk04 * D_800BD844_main) << D_800BD834_main) <= 0x1000) {
        idx = cel->unk04 >> D_800A1ED0_main[D_800BD834_main];
        if (D_800A1EE0_main[idx] >= D_800BD844_main || D_800BD844_main == D_800A2018_main[idx]) {
            D_800BD838_main++;
        }
    }
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, D_800A1EB4_main[0], 2, (((u32)obj->unk_24 >> 2) & 3) << D_800A1EB4_main[0]);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, D_800A1EB4_main[1], 2, ((((u32)obj->unk_24 >> 4) ^ 3) & 3) << D_800A1EB4_main[1]);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, D_800A1EB4_main[2], 2, (((u32)obj->unk_24 >> 6) & 3) << D_800A1EB4_main[2]);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, D_800A1EB4_main[3], 2, D_800A1EC4_main[((u32)obj->unk_24 >> 22) & 3]);
    if (((u32)obj->unk_24 >> 6) & 2) {
        gDPSetRenderMode(g++, 0, 0);
        gDPSetCombine(g++, 0xFFFFFF, 0xFFFCF279);
        D_800BD83C_main = 4;
    } else {
        intensity = obj->unk_84->unk18 >> 15;
        rm = (((u32)obj->unk_24 >> 26) & 1) ? 0x30 : 0;
        switch (((u32)obj->unk_24 >> 10) & 3) {
            case 0:
                if (obj->unk_24 & 0x1000) {
                    if (obj->unk_2C == 0x100 && intensity == 0) {
                        rm |= 0x0C087008;
                    } else {
                        rm |= 0x404240;
                    }
                } else {
                    rm |= 0x0C084000;
                }
                break;
            case 1:
                if (obj->unk_24 & 0x1000) {
                    if (obj->unk_2C == 0x100 && intensity == 0) {
                        rm |= 0x443048;
                    } else {
                        rm |= 0x4041C8;
                    }
                } else {
                    rm |= 0x442008;
                }
                break;
            case 2:
                if (obj->unk_24 & 0x1000) {
                    if (obj->unk_2C == 0x100 && intensity == 0) {
                        rm |= 0x443048;
                    } else {
                        rm |= 0x4041C8;
                    }
                } else {
                    rm |= 0x442048;
                }
                break;
        }
        gDPSetRenderMode(g++, rm, 0);
        if (intensity) {
            if (obj->unk_2C == 0x100) {
                gDPSetCombine(g++, 0xFFFFFF, 0xFFFDF2F9);
            } else {
                gDPSetCombine(g++, 0xFF97FF, 0xFF2DFEFF);
            }
        } else if (obj->unk_2C == 0x100) {
            if (obj->unk_24 & 0x2000000) {
                gDPSetCombine(g++, 0x60FEC1, 0x33FDF2F9);
            } else {
                gDPSetCombine(g++, 0xFFFFFF, 0xFFFCF279);
            }
        } else if (obj->unk_24 & 0x2000000) {
            gDPSetCombine(g++, 0x6096C1, 0x332DFEFF);
        } else {
            gDPSetCombine(g++, 0xFF97FF, 0xFF2CFE7F);
        }
        gDPSetPrimColor(g++, 0, 0, obj->unk_28[0], obj->unk_28[1], obj->unk_28[2], obj->unk_2C);
        D_800BD83C_main = 1;
    }
    D_800BD850_main = ((u32)obj->unk_24 >> 30) & 1;
    gSPSegment(g++, 2, osVirtualToPhysical(cel->unk00));
    if (D_800BD850_main != 0) {
        if (obj->unk_24 & 0x10000) {
            ox = ((obj->unk_3C - (s16)obj->unk_40) * (u16)cel->unk08) / cel->unk04;
            oy = (((s16)obj->unk_42 - obj->unk_3E) * (u16)cel->unk0A) / cel->unk06;
            obj->unk_04 = obj->unk_3C + (((s16)obj->unk_40 - obj->unk_3C) * (u16)cel->unk08) / cel->unk04;
            obj->unk_08 = obj->unk_3E + (((s16)obj->unk_42 - obj->unk_3E) * (u16)cel->unk0A) / cel->unk06;
        } else {
            ox = -(u16)cel->unk08;
            oy = (u16)cel->unk0A;
        }
        mf[0][2] = mf[0][3] = mf[1][2] = mf[1][3] = mf[2][0] = mf[2][1] = mf[2][3] = mf[3][2] = 0.0f;
        mf[2][2] = mf[3][3] = 1.0f;
        func_8003521C_main(mf, obj->unk_04 - 160.0f, 120.0f - obj->unk_08, obj->unk_20);
        func_80017CD0_main((Mtx*)mf, sx, sy, 1.0f);
        func_80017C10_main((Mtx*)mf, ox, oy, 0.0f);
        func_800898F0_main((Mtx*)mf, &obj->unk_140[D_800D2008_main]);
        gSPMatrix(g++, osVirtualToPhysical(&obj->unk_140[D_800D2008_main]), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    }
    if (obj->unk_24 & 0x08000000) {
        if (obj->unk_24 & 0x10000000) {
            if (D_800BD850_main != 0) {
                end = PutSprite(D_800CCF30_main, obj, obj->unk_134[obj->unk_120], &obj->unk_140[D_800D2008_main], cam);
            } else {
                end = PutSprite(D_800CCF30_main, obj, NULL, NULL, cam);
            }
            gSPEndDisplayList(end++);
            size = (u8*)end - (u8*)D_800CCF30_main;
            obj->unk_128[obj->unk_120] = HuMemAlloc(size);
            bcopy(D_800CCF30_main, obj->unk_128[obj->unk_120], size);
            obj->unk_124 = obj->unk_128[obj->unk_120];
            if (++obj->unk_120 >= 3) {
                obj->unk_120 = 0;
            }
            obj->unk_24 &= ~0x10000000;
        }
        gSPDisplayList(g++, obj->unk_124);
    } else if (D_800BD850_main != 0) {
        vtx = D_800D59F4_main;
        g = PutSprite(g, obj, vtx, &obj->unk_140[D_800D2008_main], cam);
        if (!(obj->unk_24 & 0x2000)) {
            D_800D59F4_main = vtx + (D_800BD840_main + 2) * 2;
        } else {
            D_800D59F4_main = vtx + (D_800BD840_main + 2) * 4;
        }
    } else {
        g = PutSprite(g, obj, NULL, NULL, cam);
    }
    *gfx = g;
}


/* register allocation (as in MP2): tstep and sx swap f30/s8 and the zero for the initialisers is f30
   instead of f20; the code is otherwise retail's. */
#ifdef NON_MATCHING
Gfx* PutSprite(Gfx* gfx, SprObj* obj, Vtx* vtx, Mtx* mtx, void* cam) {
    f32 s0;
    s32 shiftS;
    s32 shiftT;
    s32 maskS;
    s32 maskT;
    Vtx* vtxbase;
    f32 ystep;
    HuSprite_Unk84_Unk00_Struct* cel;
    f32 sx;
    f32 sy;
    f32 y;
    f32 tstep;
    f32 x0;
    f32 x1;
    f32 y0;
    f32 step;
    f32 t;
    f32 d;
    s32 flipS;
    s32 flipT;
    s32 i;
    s32 j;
    s32 rows;
    s32 n;
    s32 dy;

    tstep = s0 = 0.0f;
    cel = &obj->unk_84->unk00[obj->unk_90];
    sx = obj->unk_18;
    sy = obj->unk_1C;
    ystep = y = 0.0f;
    vtxbase = NULL;
    if (obj->unk_24 & 0x2000) {
        gDPSetCycleType(gfx++, G_CYC_2CYCLE);
        gDPPipeSync(gfx++);
        gDPSetCombine(gfx++, 0x2527FF, 0x1FFC9238);
        gDPSetRenderMode(gfx++, 0x0C1841C8, 0);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, obj->unk_2C);
        D_800BD840_main *= 2;
        D_800BD844_main >>= 1;
    }
    if ((obj->unk_24 & 0x30000) == 0x30000) {
        obj->unk_30 = (f32)((s16)obj->unk_40 - obj->unk_3C) / (cel->unk04 * sx);
        obj->unk_34 = (f32)((s16)obj->unk_42 - obj->unk_3E) / (cel->unk06 * sy);
    }
    if (obj->unk_24 & 0x04000000) {
        gDPSetDepthSource(gfx++, G_ZS_PRIM);
        gDPSetPrimDepth(gfx++, obj->unk_44, 0);
    }
    if (D_800BD848_main != 0) {
        D_800BD84C_main = D_800BD840_main + 1;
    } else {
        D_800BD84C_main = D_800BD840_main;
    }
    if (D_800BD850_main != 0) {
        vtxbase = vtx;
        flipS = 0;
        if (obj->unk_24 & 1) {
            x1 = 0.0f;
            x0 = cel->unk04 * 63.999;
        } else {
            x0 = 0.0f;
            x1 = cel->unk04 * 63.999;
            flipS = 1;
        }
        if (obj->unk_24 & 2) {
            if (obj->unk_24 & 0x10000) {
                y0 = (f32)(obj->unk_3E - (s16)obj->unk_42) / obj->unk_34;
            } else {
                y0 = -cel->unk06;
            }
            flipT = -1;
        } else {
            y0 = 0.0f;
            flipT = 1;
        }
        t = 0.0f;
        rows = cel->unk06;
        for (i = 0; i < D_800BD840_main + 2; i++) {
            if (rows < D_800BD844_main) {
            n = rows;
        } else {
            n = D_800BD844_main;
        }
            rows -= D_800BD844_main;
            if (obj->unk_24 & 0x10000) {
                vtx[0].v.ob[0] = 0;
                vtx[1].v.ob[0] = (f32)((s16)obj->unk_40 - obj->unk_3C) / obj->unk_30;
            } else {
                vtx[0].v.ob[0] = -cel->unk04 * (obj->unk_30 - 1.0f) * (flipS ^ 1);
                vtx[1].v.ob[0] = cel->unk04;
            }
            vtx[0].v.ob[1] = vtx[1].v.ob[1] = y0;
            vtx[0].v.tc[0] = x0;
            vtx[1].v.tc[0] = x1;
            vtx[0].v.tc[1] = vtx[1].v.tc[1] = t * 128.0f;
            for (j = 0; j < 2; j++) {
                vtx[j].v.ob[2] = -1;
                vtx[j].v.cn[0] = 0;
                vtx[j].v.cn[1] = 0;
                vtx[j].v.cn[2] = 0;
                vtx[j].v.cn[3] = 0xFF;
            }
            if ((obj->unk_24 & 0xC0000) && (u16)obj->unk_38 != 0) {
                vtx[1].v.ob[0] = vtx[1].v.ob[0] * obj->unk_30;
                vtx[0].v.tc[0] = vtx[0].v.tc[0] * obj->unk_30;
                vtx[1].v.tc[0] = vtx[1].v.tc[0] * obj->unk_30;
            }
            if ((obj->unk_24 & 0x300000) && (u16)obj->unk_3A != 0) {
                vtx[0].v.ob[1] = vtx[0].v.ob[1] * obj->unk_34;
                vtx[1].v.ob[1] = vtx[1].v.ob[1] * obj->unk_34;
                vtx[0].v.tc[1] = vtx[0].v.tc[1] * obj->unk_34;
                vtx[1].v.tc[1] = vtx[1].v.tc[1] * obj->unk_34;
            }
            y0 += (obj->unk_24 & 0x10000)
                      ? ((flipT < 0) ? (f32)(((s16)obj->unk_42 - obj->unk_3E) * n / D_800BD844_main) / obj->unk_34
                                     : (f32)((obj->unk_3E - (s16)obj->unk_42) * n / D_800BD844_main) / obj->unk_34)
                      : -flipT * n;
            vtx += 2;
            t += n;
        }
    } else {
        if (obj->unk_24 & 0x10000) {
            x0 = obj->unk_3C;
            x1 = (s16)obj->unk_40;
            y0 = obj->unk_3E;
            sx = (f32)((s16)obj->unk_40 - obj->unk_3C) / cel->unk04;
            dy = (s16)obj->unk_42 - obj->unk_3E;
            step = dy / D_800BD840_main;
            sy = (f32)dy / cel->unk06;
        } else {
            x0 = obj->unk_04 - (u16)cel->unk08 * sx;
            x1 = x0 + cel->unk04 * sx;
            y0 = obj->unk_08 - (u16)cel->unk0A * sy;
            step = D_800BD844_main * sy;
        }
        flipS = -1;
        if (obj->unk_24 & 1) {
            s0 = cel->unk04;
        } else {
            s0 = 0.0f;
            flipS = 1;
        }
        flipT = -1;
        if (obj->unk_24 & 2) {
            y = y0 + step * (D_800BD840_main - 1) + D_800BD848_main * sy;
            ystep = -step;
            t = step / sy - 1.0f;
        } else {
            y = y0;
            ystep = step;
            flipT = 1;
            t = 0.0f;
        }
        tstep = step / sy;
    }
    if (obj->unk_24 & 0xC0000) {
        maskS = (u16)obj->unk_38;
        shiftS = (u32)obj->unk_24 >> 18;
        shiftS -= 1;
    } else {
        maskS = 0;
        shiftS = 0;
    }
    if (obj->unk_24 & 0x300000) {
        maskT = (u16)obj->unk_3A;
        shiftT = (u32)obj->unk_24 >> 20;
        shiftT -= 1;
    } else {
        maskT = 0;
        shiftT = 0;
    }
    rows = cel->unk06;
    for (i = 0; i < D_800BD84C_main; i++) {
        if (rows < D_800BD844_main) {
            n = rows;
        } else {
            n = D_800BD844_main;
        }
        rows -= D_800BD844_main;
        SprTexLoad(&gfx, obj, n, 0, i * D_800BD844_main, cel->unk04 - 1, i * D_800BD844_main + n - 1, shiftS,
                   shiftT, maskS, maskT);
        if (D_800BD850_main != 0) {
            gSPVertex(gfx++, vtxbase + i * 2, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        } else {
            gSPScisTextureRectangle(gfx++, (s32)x0 * 4, (s16)(s32)y << 2, (s32)x1 * 4, (s32)(y + n * sy) * 4,
                                    G_TX_RENDERTILE, (s16)(s32)s0 << 5, (s16)(s32)t << 5,
                                    (s32)(D_800BD83C_main / sx * 1024.0f * flipS),
                                    (s32)(1.0f / sy * 1024.0f * flipT));
            if (flipT < 0 && rows < D_800BD844_main) {
                ystep = -(f32)rows * sy;
                tstep = rows / sy;
            }
            t += tstep;
            y += ystep;
        }
    }
    gDPPipeSync(gfx++);
    return gfx;
}
#else
INCLUDE_ASM("asm/nonmatchings/sprput", PutSprite);
#endif


/* Loads one strip of the sprite's texture (segment 2) as SprDisp chose */
void SprTexLoad(Gfx** gfx, SprObj* obj, u16 rows, u16 uls, u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt,
                u16 masks, u16 maskt) {
    HuSprite_Unk84_Unk00_Struct* cel = &obj->unk_84->unk00[obj->unk_90];
    Gfx* g = *gfx;

    switch (D_800BD838_main) {
        case 0:
            gDPLoadTextureTile_4b(g++, 0x02000000, D_800BD830_main, cel->unk04, rows, uls, ult, lrs, lrt, 0, cms,
                                  cmt, masks, maskt, 0, 0);
            break;
        case 1:
            func_80034998_main(&g, 0x02000000, D_800BD830_main, cel->unk04, rows, uls, ult, lrs, lrt, 0, cms, cmt,
                                masks, maskt, 0, 0);
            break;
        case 2:
            func_800341D0_main(&g, 0x02000000, D_800BD830_main, D_800BD834_main, cel->unk04, cel->unk06, uls,
                                ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 3:
            func_8003465C_main(&g, (void*)0x02000000, D_800BD830_main, D_800BD834_main, cel->unk04, rows, uls, ult,
                                lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0);
            break;
    }
    if (obj->unk_24 & 0x2000) {
        func_80059CDC_main(&g, obj, rows, uls, ult, lrs, lrt, cms, cmt, masks, maskt);
    }
    *gfx = g;
}

/* SprTexLoad's second texture (two-cycle sprites): the same strip into tile 1 at TMEM D_800A1EB0_main */
void func_80059CDC_main(Gfx** gfx, SprObj* obj, u16 rows, u16 uls, u16 ult, u16 lrs, u16 lrt, u16 cms,
                         u16 cmt, u16 masks, u16 maskt) {
    HuSprite_Unk84_Unk00_Struct* cel = &obj->unk_84->unk00[obj->unk_90];
    Gfx* g = *gfx;

    switch (D_800BD838_main) {
        case 0:
            gDPLoadMultiTile_4b(g++, 0x02000000, D_800A1EB0_main, 1, D_800BD830_main, cel->unk04, rows, uls, ult,
                                lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0);
            break;
        case 1:
            func_80034F70_main(&g, 0x02000000, D_800BD830_main, cel->unk04, rows, uls, ult, lrs, lrt, 0, cms, cmt,
                                masks, maskt, 0, 0, 1, D_800A1EB0_main);
            break;
        case 2:
            func_800343FC_main(&g, 0x02000000, D_800BD830_main, D_800BD834_main, cel->unk04, cel->unk06, uls,
                                ult, lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0, 1, D_800A1EB0_main);
            break;
        case 3:
            func_80034C08_main(&g, 0x02000000, D_800BD830_main, D_800BD834_main, cel->unk04, rows, uls, ult,
                                lrs, lrt, 0, cms, cmt, masks, maskt, 0, 0, 1, D_800A1EB0_main);
            break;
    }
    *gfx = g;
}

