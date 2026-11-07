#include "common.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "malloc.h"
#include "include_asm.h"

/* Screen fades and wipes (MP1 src/72D90.c, MP2 src/8FBB0.c) */

/* integer screen size (macros.h's SCREEN_WIDTH is a float) */
#define WIPE_W 320
#define WIPE_H 240

/* a pointer held as an integer so it can be aligned by masking (MP1's PB_PTR32) */
/* Frame-buffer addresses kept as integers (retail); a host build must widen this to intptr_t. */
typedef s32 WipePtr;

/* texture mask: log2 of a size rounded up (as in 14EA0.c) */
#define WIPE_TEX_MASK(x) ((x) < 3 ? 1 : (x) < 5 ? 2 : (x) < 9 ? 3 : (x) < 17 ? 4 : (x) < 33 ? 5 : (x) < 65 ? 6 : (x) < 129 ? 7 : (x) < 257 ? 8 : 9)

typedef struct WipeTex {
    /* 0x00 */ s16 w;
    /* 0x02 */ s16 h;
    /* 0x04 */ void* data;
} WipeTex; /* MP1 unk72D90Struct1 */

extern u8 D_800A26D0_main;       /* wipe type */
extern void* D_800A26D4_main;    /* captured frame buffer */
extern Gfx D_800A26D8_main[];
extern s32 D_800A2728_main[4];
extern Gfx D_800A2738_main[];

extern u8 D_800CCF84_main;       /* wipe status (MP1 fadeStatus) */
extern u8 D_800CC0BA_main;       /* wipe direction */
extern f32 D_800D0A3C_main;      /* wipe length */
extern f32 D_800D51F4_main;      /* wipe time */
extern u8 D_800CDA74_main;       /* wipe colour */
extern u8 D_800D0598_main;
extern u8 D_800D212E_main;
extern u8 D_800D5304_main;
extern WipePtr D_800D5550_main;  /* 64-byte aligned frame buffer */
extern WipeTex D_800D1F5C_main;
extern void* currFrameBuffer;

extern void* D_800BDA70_main;
extern WipePtr D_800BDA74_main;
extern u8 D_800BDA78_main;
extern Gfx* D_800BDA7C_main;
extern s16 D_800BDA80_main;
extern s16 D_800BDA82_main;

/* 34DD0.c (its definition takes the image address as s32) */
void func_800341D0_main(Gfx** arg0, s32 timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void* WipeMalloc(s32);

s32 func_80062168_main(Gfx** arg0);
s32 func_80062244_main(Gfx** arg0);
void func_8006231C_main(Gfx** arg0, u8 arg1, s32* arg2);
void func_8006265C_main(Gfx** arg0, WipePtr arg1);
void func_80062884_main(Gfx** arg0, WipePtr arg1);
void* func_800635F4_main(s32 arg0);
void func_800636D8_main(Gfx** arg0, f32 arg1, f32 arg2);
void func_800641C8_main(Gfx** arg0, f32 arg1);
void func_8006619C_main(Gfx** arg0);
void func_800661D4_main(Gfx** arg0);
void func_80062844_main(Gfx** arg0);
s32 func_800623F0_main(Gfx** arg0);
s32 func_80062584_main(Gfx** arg0);
s32 func_80063454_main(Gfx** arg0);
s32 func_80063510_main(Gfx** arg0);
s32 func_800640EC_main(Gfx** arg0);
s32 func_80065094_main(Gfx** arg0);
s32 func_8006515C_main(Gfx** arg0);
void func_800651F0_main(Gfx** arg0, f32 arg1);
s32 func_80065C9C_main(Gfx** arg0, s32 arg1);
s32 func_80065D80_main(Gfx** arg0);
s32 func_80065E88_main(Gfx** arg0);
void func_8003661C_main(void); /* gamemes.c */
void GMesExec(Gfx** arg0);

extern void* D_800D1F80_main[8]; /* WipeMalloc blocks */

void WipeInit(void) {
    s16 i;

    D_800CCF84_main = 0;
    D_800CC0BA_main = 0;
    D_800D212E_main = 0;
    D_800D0598_main = 0;
    D_800CDA74_main = 0;
    D_800D5304_main = 0;

    for (i = 0; i < 8; i++) {
        D_800D1F80_main[i] = NULL;
    }

    func_8003661C_main();
}

void WipeExecAlways(Gfx** arg0) {
    s16 i;

    if (D_800CC0BA_main == 3) {
        switch (D_800A26D0_main) {
            case 254:
                func_80062844_main(arg0);
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                func_800651F0_main(arg0, 1.0f);
                break;
            default:
                func_8006231C_main(arg0, 255, D_800A2728_main);
                break;
        }
        return;
    }

    GMesExec(arg0);

    if (D_800CC0BA_main == 0) {
        return;
    }

    switch (D_800CC0BA_main) {
        case 1:
            switch (D_800A26D0_main) {
                case 11:
                    D_800CCF84_main = func_80062168_main(arg0);
                    break;
                case 254:
                    D_800CCF84_main = func_800623F0_main(arg0);
                    break;
                case 1:
                    D_800CCF84_main = func_80063454_main(arg0);
                    break;
                case 2:
                    D_800CCF84_main = func_800640EC_main(arg0);
                    break;
                case 12:
                    D_800CCF84_main = func_80065D80_main(arg0);
                    break;
                case 0:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    D_800CCF84_main = func_8006515C_main(arg0);
                    break;
            }
            D_800D51F4_main += 1.0f;
            if (D_800CCF84_main == 0) {
                WipeColorSet(0, 0, 0);
                if (D_800A26D4_main != NULL) {
                    if (D_800D5304_main == 0) {
                        HuMemMemoryFreePerm(D_800A26D4_main);
                    }
                    D_800A26D4_main = NULL;
                }
                for (i = 0; i < 8; i++) {
                    if (D_800D1F80_main[i] != NULL) {
                        HuMemMemoryFreePerm(D_800D1F80_main[i]);
                    }
                    D_800D1F80_main[i] = NULL;
                }
                D_800D1F5C_main.data = NULL;
                func_80019C68_main(28000);
            }
            break;
        case 2:
            switch (D_800A26D0_main) {
                case 0:
                    D_800CCF84_main = func_80065C9C_main(arg0, 0);
                    break;
                case 11:
                    D_800CCF84_main = func_80062244_main(arg0);
                    break;
                case 254:
                    D_800CCF84_main = func_80062584_main(arg0);
                    break;
                case 1:
                    D_800CCF84_main = func_80063510_main(arg0);
                    break;
                case 2:
                    D_800CCF84_main = func_80065094_main(arg0);
                    break;
                case 12:
                    D_800CCF84_main = func_80065E88_main(arg0);
                    break;
                case 3:
                    D_800CCF84_main = func_80065C9C_main(arg0, 18);
                    break;
                case 4:
                    D_800CCF84_main = func_80065C9C_main(arg0, 19);
                    break;
                case 5:
                    D_800CCF84_main = func_80065C9C_main(arg0, 20);
                    break;
                case 6:
                    D_800CCF84_main = func_80065C9C_main(arg0, 21);
                    break;
                case 7:
                    D_800CCF84_main = func_80065C9C_main(arg0, 22);
                    break;
                case 8:
                    D_800CCF84_main = func_80065C9C_main(arg0, 17);
                    break;
                case 9:
                    D_800CCF84_main = func_80065C9C_main(arg0, 16);
                    break;
                case 10:
                    D_800CCF84_main = func_80065C9C_main(arg0, 15);
                    break;
            }
            D_800D51F4_main += 1.0f;
            break;
    }

    if (D_800CCF84_main == 0) {
        if (D_800CC0BA_main == 2) {
            D_800CC0BA_main = 3;
        } else {
            D_800CC0BA_main = 0;
        }
        D_800D51F4_main = 0.0f;
    }
}

void WipeCreateIn(s32 arg0, s32 arg1) {
    s16 type = arg0;
    s16 len = arg1;

    if (D_800CCF84_main == 0) {
        D_800CC0BA_main = 1;
        D_800CCF84_main = 1;
        if (type != 255) {
            D_800A26D0_main = type;
        }
        D_800D0A3C_main = len;
        D_800D51F4_main = 0.0f;
    }
}

/* wipe.h declares an s32 result; retail returns nothing */
s32 WipeCreateOut(s32 arg0, s32 arg1) {
    s16 type = arg0;
    s16 len = arg1;

    if (D_800CCF84_main == 0) {
        D_800CC0BA_main = 2;
        D_800CCF84_main = 1;
        if (type != 255) {
            D_800A26D0_main = type;
        }
        D_800D0A3C_main = len;
        D_800D51F4_main = 0.0f;
    }
}

s32 WipeStatGet(void) {
    return D_800CCF84_main;
}

void WipeColorSet(u8 r, u8 g, u8 b) {
    D_800CDA74_main = r;
    D_800D0598_main = g;
    D_800D212E_main = b;
}

void* WipeMalloc(s32 size) {
    s16 i;

    for (i = 0; i < 8; i++) {
        if (D_800D1F80_main[i] == NULL) {
            break;
        }
    }

    if (i == 8) {
        return NULL;
    }

    return D_800D1F80_main[i] = HuMemMemoryAllocPerm(size);
}

s32 func_80062168_main(Gfx** arg0) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    func_8006231C_main(arg0, 255.0f - D_800D51F4_main / D_800D0A3C_main * 255.0f, D_800A2728_main);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

s32 func_80062244_main(Gfx** arg0) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    func_8006231C_main(arg0, D_800D51F4_main / D_800D0A3C_main * 255.0f, D_800A2728_main);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

void func_8006231C_main(Gfx** arg0, u8 arg1, s32* arg2) {
    gSPDisplayList((*arg0)++, D_800A26D8_main);
    gDPSetRenderMode((*arg0)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode((*arg0)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor((*arg0)++, 0, 0, D_800CDA74_main, D_800D0598_main, D_800D212E_main, arg1);
    gDPFillRectangle((*arg0)++, 0, 0, WIPE_W, WIPE_H);
}

// decomp-permuter (MP1 func_800729C8)
s32 func_800623F0_main(Gfx **arg0)
{
  f32 new_var;
  if (D_800A26D4_main == 0)
  {
    return 0;
  }
 do { if ((new_var = D_800D0A3C_main) != 0.0f) { u8 var_a1 = 255.0f - ((D_800D51F4_main / D_800D0A3C_main) * 255.0f); gSPDisplayList((*arg0)++, D_800A26D8_main); gDPSetCombineMode((*arg0)++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM); gDPSetRenderMode((*arg0)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2); gDPSetPrimColor((*arg0)++, 0, 0, 255, 255, 255, var_a1); func_80062884_main(arg0, D_800D5550_main); if (!(D_800D51F4_main >= D_800D0A3C_main)) { return 1; } } if (D_800D5304_main == 0) { HuMemMemoryFreePerm(D_800A26D4_main); } } while (0);
  D_800A26D4_main = 0;
  return 0;
}

s32 func_80062584_main(Gfx** arg0) {
    gSPDisplayList((*arg0)++, D_800A26D8_main);

    if (D_800D51F4_main == 0.0f) {
        D_800A26D4_main = HuMemMemoryAllocPerm(153664);
        D_800D5550_main = ((WipePtr)D_800A26D4_main + 63) & ~63;
        func_8006265C_main(arg0, D_800D5550_main);
        return 1;
    }

    func_80062884_main(arg0, D_800D5550_main);

    if (D_800D51F4_main > 1.0f) {
        return 0;
    }

    return 1;
}

void func_8006265C_main(Gfx** arg0, WipePtr arg1) {
    s16 i;
    s16 j;

    gDPSetColorImage((*arg0)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, arg1);

    for (i = 0; i < WIPE_H; i += 16) {
        for (j = 0; j < WIPE_W; j += 64) {
            func_800341D0_main(arg0, ((j + (i * WIPE_W)) * 2) + 0x02000000, 0, 2, WIPE_W, WIPE_H, 0, 0, 64, 16, 0, 2, 2, 0, 0, 0, 0);
            gSPTextureRectangle((*arg0)++, j * 4, i * 4, (j + 64) * 4, (i + 16) * 4, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
        }
    }

    gDPSetColorImage((*arg0)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, WIPE_W, 0x02000000);
}

void func_80062844_main(Gfx** arg0) {
    gSPDisplayList((*arg0)++, D_800A26D8_main);
    func_80062884_main(arg0, D_800D5550_main);
}

void func_80062884_main(Gfx** arg0, WipePtr arg1) {
    s16 i;
    s16 j;

    for (i = 0; i < WIPE_H; i += 16) {
        for (j = 0; j < WIPE_W; j += 64) {
            func_800341D0_main(arg0, arg1 + (j + i * WIPE_W) * 2, 0, 2, WIPE_W, WIPE_H, 0, 0, 64, 16, 0, 2, 2, 0, 0, 0, 0);
            gSPTextureRectangle((*arg0)++, j * 4, i * 4, (j + 64) * 4, (i + 16) * 4, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
        }
    }
}

/* MP2 func_80090460_91060: shrink the frame into the depth buffer and draw it back scaled */
s32 func_80062A30_main(Gfx** arg0) {
    f32 temp_f22;
    f32 temp_f24;
    u8* var_s8; /* a frame buffer address */
    s16 i;
    s16 j;

    if (D_800D0A3C_main - 1.0f <= D_800D51F4_main) {
        func_8006231C_main(arg0, 255, D_800A2728_main);
        return 0;
    }

    temp_f22 = 1.0f - D_800D51F4_main / D_800D0A3C_main;
    temp_f24 = 1.0f / temp_f22;

    gSPDisplayList((*arg0)++, D_800A26D8_main);
    gDPSetAlphaCompare((*arg0)++, G_AC_THRESHOLD);
    gDPSetBlendColor((*arg0)++, 0, 0, 0, 0);
    gDPSetTextureFilter((*arg0)++, G_TF_BILERP);
    gDPSetScissor((*arg0)++, G_SC_NON_INTERLACE, 0, 0, WIPE_W, WIPE_H);

    var_s8 = currFrameBuffer;

    gDPSetColorImage((*arg0)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, WIPE_W, 0x003D0800);
    gSPDisplayList((*arg0)++, D_800A2738_main);
    gDPSetCombineMode((*arg0)++, G_CC_DECALRGB, G_CC_DECALRGB);
    gDPSetRenderMode((*arg0)++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    for (i = 0; i < WIPE_H; i += 16) {
        for (j = 0; j < WIPE_W; j += 64) {
            func_800341D0_main(arg0, (s32)(var_s8 + (j + i * WIPE_W) * 2), 0, 2, WIPE_W, WIPE_H, 0, 0, 64, 16, 0, 2, 2, 0, 0, 0, 0);
            gSPTextureRectangle((*arg0)++, j * temp_f22 * 4.0f, i * temp_f22 * 4.0f,
                (j * temp_f22 + temp_f22 * 64.0f) * 4.0f, (i * temp_f22 + temp_f22 * 16.0f) * 4.0f,
                G_TX_RENDERTILE, 0, 0, temp_f24 * 1024.0f, temp_f24 * 1024.0f);
        }
    }

    gDPSetColorImage((*arg0)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, WIPE_W, 0x02000000);

    var_s8 = (u8*)0x803D0800;
    for (i = 0; i < temp_f22 * (f32)WIPE_H + 15.0f; i += 16) {
        for (j = 0; j < temp_f22 * (f32)WIPE_W + 31.0f; j += 32) {
            func_800341D0_main(arg0, (s32)(var_s8 + (j + i * WIPE_W) * 2), 0, 2, WIPE_W, WIPE_H, 0, 0, 32, 16, 0, 2, 2, 0, 0, 0, 0);
            gSPTextureRectangle((*arg0)++, j * temp_f24 * 4.0f, i * temp_f24 * 4.0f,
                (j + 32) * temp_f24 * 4.0f, (i + 16) * temp_f24 * 4.0f,
                G_TX_RENDERTILE, 0, 0, temp_f22 * 1024.0f, temp_f22 * 1024.0f);
        }
    }

    gDPPipeSync((*arg0)++);
    gDPSetCombineMode((*arg0)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode((*arg0)++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor((*arg0)++, 0, 0, 0, 0, 0, 8);
    gDPFillRectangle((*arg0)++, 0, 0, WIPE_W, WIPE_H);

    return 1;
}

s32 func_80063454_main(Gfx** arg0) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    if (D_800D51F4_main == 0.0f) {
        func_800635F4_main(0x0D);
    }

    func_800636D8_main(arg0, D_800D51F4_main / D_800D0A3C_main, 1.0f);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

s32 func_80063510_main(Gfx** arg0) {
    f32 var_a2;

    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    if (D_800D51F4_main == 0.0f) {
        func_800635F4_main(0x0D);
    }

    var_a2 = (1.0f - D_800D51F4_main / D_800D0A3C_main) * 1.1f;
    func_800636D8_main(arg0, var_a2, 1.0f);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

void* func_800635F4_main(s32 arg0) {
    u8* data;
    u8* p;

    data = DataRead(arg0);
    p = data + (data[2] << 8) + data[3];
    D_800D1F5C_main.w = (p[4] << 8) + p[5];
    D_800D1F5C_main.h = (p[6] << 8) + p[7];
    p = data + (p[2] << 8) + p[3];
    D_800D1F5C_main.data = WipeMalloc(D_800D1F5C_main.w * D_800D1F5C_main.h);
    bcopy(p, D_800D1F5C_main.data, D_800D1F5C_main.w * D_800D1F5C_main.h);
    DataClose(data);
    return data;
}

/* MP2 func_8009110C_91D0C. Same instructions, but the KMC assembler's VR4300 mul fix (on for
   this unit: func_80062A30_main needs it) adds a nop before the mult after the first bgezl. */
#ifdef NON_MATCHING
/* MP2 func_8009110C_91D0C: draw the wipe texture scaled by arg1 about the centre, fill the rest */
void func_800636D8_main(Gfx** arg0, f32 arg1, f32 arg2) {
    s16 var_t1;
    s16 var_t2;
    s16 var_t3;
    s16 var_t4;
    f32 temp_f4;

    if (arg1 == 0) {
        func_8006231C_main(arg0, 255, D_800A2728_main);
        return;
    }

    gSPDisplayList((*arg0)++, D_800A26D8_main);
    gDPSetAlphaCompare((*arg0)++, G_AC_THRESHOLD);
    gDPSetBlendColor((*arg0)++, 0, 0, 0, 1);
    gDPSetScissor((*arg0)++, G_SC_NON_INTERLACE, 0, 0, WIPE_W, WIPE_H);
    gDPSetTextureFilter((*arg0)++, G_TF_BILERP);
    gDPSetRenderMode((*arg0)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineLERP((*arg0)++, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0);
    gDPLoadTextureBlock((*arg0)++, D_800D1F5C_main.data, G_IM_FMT_I, G_IM_SIZ_8b, D_800D1F5C_main.w, D_800D1F5C_main.h, 0,
        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetPrimColor((*arg0)++, 0, 0, D_800CDA74_main, D_800D0598_main, D_800D212E_main, arg2 * 255.0f);

    var_t3 = 160.0f - arg1 * 160.0f;
    var_t1 = 120.0f - arg1 * 160.0f;
    var_t4 = 160.0f + arg1 * 160.0f;
    var_t2 = 120.0f + arg1 * 160.0f;
    temp_f4 = ((f32) var_t4 - var_t3) / D_800D1F5C_main.w;

    gSPScisTextureRectangle((*arg0)++, var_t3 * 4, var_t1 * 4, var_t4 * 4, var_t2 * 4, 0, 0, 0,
        (1.0f / temp_f4) * 1024.0f, (1.0f / temp_f4) * 1024.0f);
    gDPSetRenderMode((*arg0)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode((*arg0)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor((*arg0)++, 0, 0, D_800CDA74_main, D_800D0598_main, D_800D212E_main, arg2 * 255.0f);

    if (var_t1 > 0) {
        gDPScisFillRectangle((*arg0)++, 0, 0, WIPE_W, var_t1);
    } else {
        var_t1 = 0;
    }

    if (var_t2 < WIPE_H) {
        gDPScisFillRectangle((*arg0)++, 0, var_t2, WIPE_W, WIPE_H);
    } else {
        var_t2 = WIPE_H;
    }

    if (var_t3 > 0) {
        gDPScisFillRectangle((*arg0)++, 0, var_t1, var_t3, var_t2);
    }

    if (var_t4 < WIPE_W) {
        gDPScisFillRectangle((*arg0)++, var_t4, var_t1, WIPE_W, var_t2);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/wipe", func_800636D8_main);
#endif

s32 func_800640EC_main(Gfx** arg0) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    if (D_800D51F4_main == 0.0f && D_800D1F5C_main.data == NULL) {
        func_800635F4_main(0x17);
    }

    func_800641C8_main(arg0, 1.0f - 1.0f / D_800D0A3C_main * D_800D51F4_main);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

INCLUDE_ASM("asm/nonmatchings/wipe", func_800641C8_main);

s32 func_80065094_main(Gfx** arg0) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    if (D_800D51F4_main == 0.0f) {
        func_800635F4_main(0x17);
    }

    func_800641C8_main(arg0, 1.0f / D_800D0A3C_main * D_800D51F4_main);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

s32 func_8006515C_main(Gfx** arg0) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    func_800651F0_main(arg0, 1.0f - 1.0f / D_800D0A3C_main * D_800D51F4_main);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

/* ten horizontal bands of height arg1 * 24 about each band centre; bands over the wipe texture
   draw its rows (4-bit I) instead of a flat fill */
void func_800651F0_main(Gfx** arg0, f32 arg1) {
    f32 alpha;
    f32 half;
    s16 i;
    s16 y;
    s16 row;
    s32 top;

    if (arg1 == 0.0f) {
        return;
    }

    gSPDisplayList((*arg0)++, D_800A26D8_main);
    gDPSetAlphaCompare((*arg0)++, G_AC_THRESHOLD);
    gDPSetBlendColor((*arg0)++, 0, 0, 0, 1);

    alpha = (arg1 + 0.2f) * 255.0f;
    if (alpha > 255.0f) {
        alpha = 255.0f;
    }

    for (i = 0; i < 10; i++) {
        y = i * 24.0f + 12.0f;
        half = arg1 * 24.0f / 2.0f;
        gDPPipeSync((*arg0)++);
        if (alpha == 255.0f) {
            gDPSetRenderMode((*arg0)++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
        } else {
            gDPSetRenderMode((*arg0)++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        }
        gDPSetCombineMode((*arg0)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor((*arg0)++, 0, 0, 0, 0, 0, alpha);
        gDPFillRectangle((*arg0)++, 0, y - half, WIPE_W, y + half);

        if (D_800D1F5C_main.data != NULL) {
            top = (WIPE_H - D_800D1F5C_main.h) / 2;
            if (!(top > i * 24.0f) && !(D_800D1F5C_main.h + top <= i * 24.0f)) {
                row = i * 24.0f - top;
                gDPPipeSync((*arg0)++);
                gDPSetRenderMode((*arg0)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
                gDPSetCombineLERP((*arg0)++, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0);
                gDPSetPrimColor((*arg0)++, 0, 0, 255, 255, 255, alpha);
                gDPLoadTextureTile_4b((*arg0)++, (u8*)D_800D1F5C_main.data + (u32)(row * D_800D1F5C_main.w) / 2, G_IM_FMT_I,
                    D_800D1F5C_main.w, D_800D1F5C_main.h, 0, 0, D_800D1F5C_main.w, 24, 0,
                    G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                    WIPE_TEX_MASK(D_800D1F5C_main.w), WIPE_TEX_MASK(D_800D1F5C_main.h), G_TX_NOLOD, G_TX_NOLOD);
                gSPScisTextureRectangle((*arg0)++, (160 - D_800D1F5C_main.w / 2) * 4, (y - half) * 4.0f,
                    (160 + D_800D1F5C_main.w / 2) * 4, (y + half) * 4.0f, G_TX_RENDERTILE, 0, 0,
                    0x0400, 1.0f / arg1 * 1024.0f);
            }
        }
    }
}

/* wipe out through the texture in data file arg1 (none for 0) */
s32 func_80065C9C_main(Gfx** arg0, s32 arg1) {
    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    if (D_800D51F4_main == 0.0f) {
        if (arg1 != 0) {
            func_800635F4_main(arg1);
        } else {
            D_800D1F5C_main.data = NULL;
        }
    }

    func_800651F0_main(arg0, 1.0f / D_800D0A3C_main * D_800D51F4_main);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

s32 func_80065D80_main(Gfx** arg0) {
    f32 var_a2;
    f32 temp_f2;
    f32 var_f2;

    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    if (D_800D51F4_main == 0.0f) {
        func_800635F4_main(0x18);
    }

    var_a2 = D_800D51F4_main / D_800D0A3C_main * 2.0f;
    temp_f2 = D_800D0A3C_main * 0.5f;
    if (temp_f2 < D_800D51F4_main) {
        var_f2 = 1.0f - (D_800D51F4_main - temp_f2) / temp_f2;
    } else {
        var_f2 = 1.0f;
    }

    func_800636D8_main(arg0, var_a2, var_f2);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

s32 func_80065E88_main(Gfx** arg0) {
    f32 var_a2;
    f32 temp_f2;
    f32 var_f2;

    if (D_800D0A3C_main == 0.0f) {
        return 0;
    }

    if (D_800D51F4_main == 0.0f) {
        func_800635F4_main(0x18);
    }

    var_a2 = (1.0f - D_800D51F4_main / D_800D0A3C_main) * 2.0f;
    temp_f2 = D_800D0A3C_main * 0.5f;
    if (temp_f2 > D_800D51F4_main) {
        var_f2 = D_800D51F4_main / temp_f2;
    } else {
        var_f2 = 1.0f;
    }

    func_800636D8_main(arg0, var_a2, var_f2);

    if (D_800D51F4_main >= D_800D0A3C_main) {
        return 0;
    }

    return 1;
}

void func_80065F8C_main(void) {
    Gfx* sp10;

    D_800BDA70_main = HuMemAlloc(153664);
    sp10 = D_800BDA7C_main = HuMemAlloc(6400);

    D_800BDA74_main = ((WipePtr)D_800BDA70_main + 63) & ~63;
    D_800BDA80_main = func_8001AC8C_main(0, (void (*)(Gfx**, s32, s32))func_8006619C_main, 6);

    gSPDisplayList(sp10++, D_800A26D8_main);
    func_8006265C_main(&sp10, D_800BDA74_main);
    gSPEndDisplayList(sp10);

    D_800BDA78_main = 0;
}

s32 func_80066048_main(void) {
    if (D_800BDA78_main < 3) {
        return 0;
    }

    func_80019C00_main(D_800BDA7C_main);
    func_8001ACDC_main(D_800BDA80_main);

    return 1;
}

void func_8006608C_main(void) {
    Gfx* sp10;

    sp10 = D_800BDA7C_main = HuMemAlloc(6400);
    D_800BDA82_main = func_8001AC8C_main(0, (void (*)(Gfx**, s32, s32))func_800661D4_main, 0);

    gSPDisplayList(sp10++, D_800A26D8_main);
    gDPSetCombineMode(sp10++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetRenderMode(sp10++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetPrimColor(sp10++, 0, 0, 255, 255, 255, 128);

    func_80062884_main(&sp10, D_800BDA74_main);
    gSPEndDisplayList(sp10);
}

void func_80066164_main(void) {
    func_80019C00_main(D_800BDA7C_main);
    func_80019C00_main(D_800BDA70_main);
    func_8001ACDC_main(D_800BDA82_main);
}

void func_8006619C_main(Gfx** arg0) {
    gSPDisplayList((*arg0)++, D_800BDA7C_main);
    D_800BDA78_main++;
}

void func_800661D4_main(Gfx** arg0) {
    gSPDisplayList((*arg0)++, D_800BDA7C_main);
}

void func_800661F8_main(void) {
    D_800BDA70_main = D_800A26D4_main;
    D_800BDA74_main = D_800D5550_main;
    D_800D5304_main = 1;
}

void func_80066228_main(void) {
    func_80019C00_main(D_800BDA7C_main);
    HuMemMemoryFreePerm(D_800BDA70_main);
    func_8001ACDC_main(D_800BDA82_main);
    D_800D5304_main = 0;
}
