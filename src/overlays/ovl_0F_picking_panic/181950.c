#include "ultra64.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "include_asm.h"
#include "math.h"

// EXTERN

void func_8000B5F0_main(u8 arg0);
void func_8000B710_main(s32);
void func_800142A0_main(s32);
void func_80017954_main(s16, s16, s16, s16);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_80045010_main(s16 *, s32);
void func_80045ED0_main(s32);
s32 _CheckFlag(s32);
f32 atan2df(f32, f32);
f32 cosdf(f32);
f32 sindf(f32);

extern u8 D_800CD280_main;
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[];
extern s16 D_800CDA7C_main[];
extern Gfx *gMainGfxPos;

typedef struct {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[0x1E];
} D_800CD1DC_main_Struct; // Size 0x24

extern D_800CD1DC_main_Struct *D_800CD1DC_main;

// LOCAL

typedef struct {
    /* 0x00 */ s8 unk00; /* player number */
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02; /* pad */
    /* 0x03 */ s8 unk03; /* character */
    /* 0x04 */ s8 unk04; /* CPU difficulty, -1 for a human */
    /* 0x05 */ char unk05[1];
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ s32 unk0C;
} PkPlayer; // Size 0x10

/* Per-team CPU state; the halves are split labels D_8010E704..D_8010E70A. */
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
} PkTeamAi; // Size 8

typedef struct {
    u8 unk00[8];
    u8 unk08[8];
    u8 unk10[8];
    u8 unk18[8];
} PkCpuTable;

void func_80107A48_picking_panic(void);
void func_8010B11C_picking_panic(s16 model, s16 frame);

/* data */
extern Gfx D_8010E5E0_picking_panic[];
extern D_80111B50_vine_with_me_Struct D_8010E5B0_picking_panic;
extern f32 D_8010E62C_picking_panic[3][16];
extern u32 D_8010E6EC_picking_panic;
extern s8 D_8010E6F0_picking_panic[2][4];
extern u8 D_8010E6F8_picking_panic[4];
extern u8 D_8010E6FC_picking_panic[4];
extern s8 D_8010E700_picking_panic[4];
extern PkTeamAi D_8010E704_picking_panic[2];
extern u8 D_8010E714_picking_panic[4];
extern u8 D_8010E718_picking_panic[8];

/* rodata */
extern PkCpuTable D_8010EA8C_picking_panic;

/* bss */
extern f32 D_8010EC20_picking_panic[3][16];
extern f32 D_8010ECE0_picking_panic[3][16];
extern u8 D_8010EDA0_picking_panic[2][4];
extern u8 D_8010EDA8_picking_panic[2][4];
extern f32 D_8010EDB0_picking_panic[2][4];
extern f32 D_8010EDD0_picking_panic[2][4];
extern f32 D_8010EDF0_picking_panic[2][4];
extern f32 D_8010EE10_picking_panic[2][4];
extern f32 D_8010EE30_picking_panic[2][4];
extern f32 D_8010EE50_picking_panic[2][4];
extern f32 D_8010EE70_picking_panic;
extern f32 D_8010EE74_picking_panic;
extern f32 D_8010EE78_picking_panic;
extern f32 D_8010EE7C_picking_panic;
extern f32 D_8010EE80_picking_panic;
extern f32 D_8010EE84_picking_panic;
extern f32 D_8010EE88_picking_panic;
extern f32 D_8010EE8C_picking_panic;
extern f32 D_8010EE90_picking_panic;
extern f32 D_8010EE94_picking_panic;
extern f32 D_8010EE98_picking_panic;
extern PkPlayer D_8010EEA0_picking_panic[4];
extern PkPlayer *D_8010EEE0_picking_panic[4];
extern u8 D_8010EEF0_picking_panic[4];
extern f32 D_8010EEF4_picking_panic[2];
extern omObjData *D_8010EEFC_picking_panic;
extern omObjData *D_8010EF00_picking_panic[4];
extern u16 D_8010EF10_picking_panic[2];
extern s8 D_8010EF14_picking_panic;
extern u8 D_8010EF15_picking_panic[2];
extern s16 *D_8010EF18_picking_panic[2][4][3];
extern f32 D_8010EF78_picking_panic;
extern s16 D_8010EF80_picking_panic;
extern f32 D_8010EF84_picking_panic[2];
extern f32 D_8010EF8C_picking_panic[2];
extern f32 D_8010EF94_picking_panic;
extern s8 D_8010EF98_picking_panic[2];
extern f32 D_8010EF9C_picking_panic[2];
extern u8 D_8010EFA4_picking_panic;
extern s32 D_8010EFA8_picking_panic;
extern f32 D_8010EFAC_picking_panic[2];
extern f32 D_8010EFC4_picking_panic[2];
extern s16 D_8010EFD0_picking_panic[4];
extern s16 D_8010EFD8_picking_panic;
extern f32 D_8010EFEC_picking_panic[2];


INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_801059A0_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80105D3C_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E720_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E758_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80106020_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E798_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E7C0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E7E8_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010664C_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80106E84_picking_panic);

#ifdef NON_MATCHING
void func_80107A48_picking_panic(void) {
    f32 sp10[2];
    HuSprite_Unk84_Unk00_Struct *frame;
    HuSprite *spr;
    f32 lo;
    f32 hi;
    f32 scl;
    f32 cx;
    f32 cy;
    s32 i;
    s32 row;
    s32 col;
    s32 vp;
    s32 w;
    s32 h;
    s32 dx;
    f32 *p;

    lo = (D_8010EF78_picking_panic * 240.0f - 1.0f < 0.0f) ? 0.0f : D_8010EF78_picking_panic * 240.0f - 1.0f;
    hi = (D_8010EF78_picking_panic * 240.0f + 1.0f > 240.0f) ? 240.0f : D_8010EF78_picking_panic * 240.0f + 1.0f;
    gSPDisplayList(gMainGfxPos++, D_8010E5E0_picking_panic);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);

    /* Two 161x160 / 160x160 background halves, drawn in 40x40 tiles. */
    for (i = 0; i < 2; i++) {
        spr = HuSprGet(D_800CD1DC_main[*((i != 0) ? &D_8010EFD0_picking_panic[1] : &D_8010EFD0_picking_panic[0])].unk04, 0);
        frame = &spr->unk_84->unk00[spr->unk_90];
        gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
        for (col = 0; col < 4; col++) {
            for (row = 0; row < 3; row++) {
                w = ((i == 1) & (col == 3)) ? 40 : 41;
                h = (row != 2) ? 41 : 40;
                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, (i == 0) ? 161 : 160, 0,
                                   col * 40, row * 40, col * 40 + w, row * 40 + h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                for (vp = 0; vp < 2; vp++) {
                    if (vp == 0) {
                        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, lo);
                    } else {
                        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, hi, 320, 240);
                    }
                    gSPScisTextureRectangle(
                        gMainGfxPos++,
                        (s32)((col * 40 + i * 160) * 4 * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                        (s32)((vp * 120 + row * 40) * 4 * D_8010EFC4_picking_panic[vp] + D_8010EFAC_picking_panic[vp]),
                        (s32)((col * 40 + i * 160 + w) * 4 * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                        (s32)((vp * 120 + row * 40 + h) * 4 * D_8010EFC4_picking_panic[vp] + D_8010EFAC_picking_panic[vp]),
                        0, (col * 40) << 5, (row * 40) << 5, (s32)(D_8010EFEC_picking_panic[vp] * 1024.0f),
                        (s32)(D_8010EF8C_picking_panic[vp] * 1024.0f));
                }
            }
        }
    }
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0x00, 0x00, 0x00, 0xD0);

    /* Counter item rising: progress of each team's next item. */
    cx = 51.0f;
    cy = 64.0f;
    scl = 0.2875f;
    for (i = 0; i < 2; i++) {
        p = &sp10[i];
        if (D_8010EF10_picking_panic[i] >= 26) {
            if (D_8010EF10_picking_panic[i] < 30) {
                *p = (D_8010EF10_picking_panic[i] - 26) / 4.0;
            } else if (D_8010EF10_picking_panic[i] < 37) {
                *p = 1.0f;
            } else if (D_8010EF10_picking_panic[i] < 45) {
                *p = (D_8010EF10_picking_panic[i] - 37) / 7.0;
            } else {
                *p = 0.0f;
            }
        } else {
            *p = 0.0f;
        }
        if (D_8010EF10_picking_panic[i] - 37 < 8u) {
            sp10[i] = (1.0f - sp10[i] * sp10[i]) * 0.75 + (1.0f - sp10[i]) * 0.25;
        }
        if (D_8010EF10_picking_panic[i] == 26) {
            func_8001C258_main(D_8010EEFC_picking_panic->model[i + 10], 4, 0);
            func_8001C6A8_main(D_8010EEFC_picking_panic->model[i + 10], 0.0f);
            func_8001C814_main(D_8010EEFC_picking_panic->model[i + 10], 3, 0);
            func_8010B11C_picking_panic(D_8010EEFC_picking_panic->model[i + 10], 0);
        }
        if (D_8010EF10_picking_panic[i] == 27) {
            func_8001C258_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 4, 0);
            func_8001C6A8_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 0.0f);
            func_8001C814_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 1, 1);
        }
        if (D_8010EF10_picking_panic[i] - 26 < 5u) {
            Hu3DModelPosSet(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], -855.0f,
                            (1.0f - sp10[i]) * 175.0f + -25.0f, 0.0f);
        }
        if (D_8010EF10_picking_panic[i] == 30) {
            func_8001C6A8_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 0.0f);
            func_8001C814_main(*D_8010EF18_picking_panic[i][D_8010EEF0_picking_panic[i]][D_8010EF98_picking_panic[i]], 1, 0);
        }
        if (D_8010EF10_picking_panic[i] - 10 < 11u) {
            D_8010EF84_picking_panic[i] = sindf((D_8010EF10_picking_panic[i] - 10) / 15.0 * 1440.0) * 0.625;
        }
    }

    /* The counter's item panel, 64x97 in four loads, scaled by scl. */
    if (sp10[0] != 0.0f || sp10[1] != 0.0f) {
        spr = HuSprGet(D_800CD1DC_main[D_8010EFD8_picking_panic].unk04, 0);
        frame = &spr->unk_84->unk00[spr->unk_90];
        gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
        for (row = 0; row < 4; row++) {
            gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 0, 0, row * 24, 64,
                               (row < 3) ? row * 24 + 25 : row * 24 + 24, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            for (vp = 0; vp < 2; vp++) {
                if (sp10[vp] == 0.0f) {
                    continue;
                }
                if (vp == 0) {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, lo);
                } else {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, hi, 320, 240);
                }
                gSPScisTextureRectangle(
                    gMainGfxPos++,
                    (s32)((cx - scl * 32.0f) * 4.0 * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                    (s32)((cy + sp10[vp] * 21.0f - 48.0f + (row * 24) * scl + (vp * 120)) * 4.0 *
                              D_8010EFC4_picking_panic[vp] +
                          D_8010EFAC_picking_panic[vp]),
                    (s32)((cx + scl * 32.0f) * 4.0 * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                    (s32)((cy + sp10[vp] * 21.0f - 48.0f + ((row < 3) ? row * 24 + 25 : row * 24 + 23) * scl +
                           (vp * 120)) *
                              4.0 * D_8010EFC4_picking_panic[vp] +
                          D_8010EFAC_picking_panic[vp]),
                    0, 0, (row * 24) << 5, (s32)(1024.0f / scl * D_8010EFEC_picking_panic[vp]),
                    (s32)(1024.0f / scl * D_8010EF8C_picking_panic[vp]));
            }
        }
    }

    /* The two score boards (CI8 115x48 and RGBA16 108x48), the first shaking with D_8010EF84. */
    for (i = 0; i < 2; i++) {
        spr = HuSprGet(D_800CD1DC_main[*((i != 0) ? &D_8010EFD0_picking_panic[3] : &D_8010EFD0_picking_panic[2])].unk04, 0);
        frame = &spr->unk_84->unk00[spr->unk_90];
        if (i == 0) {
            gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
        }
        for (col = 0; col < 3; col++) {
            w = ((i == 1) & (col == 2)) ? 32 : 39;
            if (i == 0) {
                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, (i == 0) ? 115 : 108, 0,
                                   col * 38, 0, col * 38 + w, 48, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_RGBA, G_IM_SIZ_16b, (i == 0) ? 115 : 108,
                                   0, col * 38, 0, col * 38 + w, 48, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            }
            for (vp = 0; vp < 2; vp++) {
                dx = 0;
                if (i == 0) {
                    dx = D_8010EF84_picking_panic[vp] * 4.0;
                }
                if (vp == 0) {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, lo);
                } else {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, hi, 320, 240);
                }
                gSPScisTextureRectangle(
                    gMainGfxPos++,
                    (s32)(((col * 38 + i * 212) * 4 + dx) * D_8010EEF4_picking_panic[vp] + D_8010EF9C_picking_panic[vp]),
                    (s32)(vp * 120 * 4 * D_8010EFC4_picking_panic[vp] + D_8010EFAC_picking_panic[vp]),
                    (s32)(((col * 38 + i * 212 + w) * 4 + dx) * D_8010EEF4_picking_panic[vp] +
                          D_8010EF9C_picking_panic[vp]),
                    (s32)((vp * 120 + 48) * 4 * D_8010EFC4_picking_panic[vp] + D_8010EFAC_picking_panic[vp]), 0,
                    (col * 38) << 5, 0, (s32)(D_8010EFEC_picking_panic[vp] * 1024.0f),
                    (s32)(D_8010EF8C_picking_panic[vp] * 1024.0f));
            }
        }
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80107A48_picking_panic);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E990_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80109C00_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B11C_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B160_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B194_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B1C0_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B1F4_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B220_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B8D0_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B8EC_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E9E0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA00_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA20_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA40_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA80_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA8C_picking_panic);

#ifdef NON_MATCHING
void func_8010B908_picking_panic(omObjData *arg0, s8 arg1) {
    PkCpuTable tbl;
    f32 sp38[11];
    PkPlayer *p0;
    PkPlayer *p1;
    omObjData *o0;
    omObjData *o1;
    u8 i0;
    u8 i1;
    f32 prevY;
    HmfModel *m;
    s32 i;
    s32 j;
    s32 k;
    s32 t;
    u32 ut;
    s32 se;
    s16 mdl;
    f32 dir;
    f32 baseX;
    f32 x;
    f32 y;
    f32 rot;
    f32 c;
    f32 s;
    f32 f;
    f32 g;
    f32 wall;
    f32 h;
    f32 h2;
    f32 ang;
    f32 spd;

    p0 = D_8010EEE0_picking_panic[arg1 * 2];
    p1 = D_8010EEE0_picking_panic[arg1 * 2 + 1];
    o0 = D_8010EF00_picking_panic[arg1 * 2];
    o1 = D_8010EF00_picking_panic[arg1 * 2 + 1];
    i0 = arg1 * 2;
    i1 = arg1 * 2 + 1;
    tbl = D_8010EA8C_picking_panic;

    if (arg1 == 0 && D_8010E6EC_picking_panic == 45) {
        for (i = 1; i < 6; i++) {
            D_8010E718_picking_panic[i] = rand8() / 110;
        }
    }
    if (arg1 == 0) {
        D_8010EF94_picking_panic -= (D_8010EF94_picking_panic > 0.0f) ? 1.0f : 0.0f;
    }
    if (arg1 == 0 && D_8010EF94_picking_panic == 0.0f && D_8010EF80_picking_panic == 2 &&
        D_8010E6EC_picking_panic % 60 == 46) {
        D_8010EF94_picking_panic = 60.0f;
    }
    if (arg1 == 0) {
        t = D_8010E6EC_picking_panic % 30;
        t = (t < 16) ? t : 30 - t;
        if (D_8010E62C_picking_panic[0][t] == 0.0f) {
            f32 sx = 0.0f;
            f32 sy = 0.0f;
            f64 amp = sindf(t * 90.0 / 15.0) * 80.0f;

            for (i = 0; i < 3; i++) {
                D_8010E62C_picking_panic[i][t] = amp * (i * 0.125 / 3.0 + 0.875) + 270.0;
                sx += cosdf(D_8010E62C_picking_panic[i][t]) * 110.0f;
                sy += sindf(D_8010E62C_picking_panic[i][t]) * 110.0f;
                D_8010EC20_picking_panic[i][t] = sx;
                D_8010ECE0_picking_panic[i][t] = sy;
            }
        }
        for (i = 0; i < 2; i++) {
            dir = (D_8010E6EC_picking_panic % 60 < 30) ? 1.0f : -1.0f;
            baseX = (i == 0) ? -500.0f : 500.0f;
            ut = D_8010E6EC_picking_panic % 30;
            t = (ut < 16) ? ut : 30 - ut;
            if (i != 0) {
                dir = -dir;
            }
            for (j = 0; j < 3; j++) {
                Hu3DModelPosSet(D_8010EEFC_picking_panic->model[(i == 0) ? j + 32 : j + 35],
                                baseX + dir * D_8010EC20_picking_panic[j][t],
                                D_8010ECE0_picking_panic[j][t] + 250.0f, 0.0f);
                Hu3DModelRotSet(D_8010EEFC_picking_panic->model[(i == 0) ? j + 32 : j + 35], 0.0f, 0.0f,
                                (D_8010E62C_picking_panic[j][t] - 270.0f) * dir);
            }
            x = baseX + dir * D_8010EC20_picking_panic[2][t];
            y = D_8010ECE0_picking_panic[2][t] + 250.0f;
            rot = (D_8010E62C_picking_panic[2][t] - 270.0f) * dir;
            Hu3DModelPosSet(D_8010EEFC_picking_panic->model[(i != 0) ? 9 : 8], x, y, 0.0f);
            Hu3DModelRotSet(D_8010EEFC_picking_panic->model[(i == 0) ? 8 : 9], 0.0f, 0.0f, rot);
            rot += (i == 0) ? 35.0f : -35.0f;
            if (D_8010EF80_picking_panic == 0 && D_8010EFA8_picking_panic < 45) {
                if (D_8010EFA8_picking_panic >= 30) {
                    f = 180.0 - (D_8010EFA8_picking_panic + 30) * 180.0 / 15.0;
                } else {
                    f = 180.0f;
                }
                if (i != 0) {
                    rot += f;
                } else {
                    rot -= f;
                }
            }
            c = cosdf(rot + 270.0f + ((i == 0) ? -14.0f : 14.0f));
            s = sindf(rot + 270.0f + ((i == 0) ? -14.0f : 14.0f));
            if (!(i & 1)) {
                D_8010EE80_picking_panic = -D_8010EE70_picking_panic;
                D_8010EE84_picking_panic = -D_8010EE74_picking_panic;
                D_8010EE70_picking_panic = x + c * 86.0f;
                D_8010EE74_picking_panic = y + s * 86.0f;
                D_8010EE80_picking_panic += D_8010EE70_picking_panic;
                D_8010EE84_picking_panic += D_8010EE74_picking_panic;
            } else {
                D_8010EE78_picking_panic = x + c * 86.0f;
                D_8010EE7C_picking_panic = y + s * 86.0f;
            }
            x -= c * 86.0f;
            y -= s * 86.0f;
            omSetTra(D_8010EF00_picking_panic[i], x, y, 0.0f);
            omSetRot(D_8010EF00_picking_panic[i], 0.0f, (i == 0) ? -90.0f : 90.0f, rot + 180.0f);
            omSetTra(D_8010EF00_picking_panic[i + 2], x, y, 0.0f);
            omSetRot(D_8010EF00_picking_panic[i + 2], 0.0f, (i == 0) ? -90.0f : 90.0f, rot + 180.0f);
            if (D_8010EF80_picking_panic >= 3 && D_8010EF14_picking_panic < 2) {
                s32 n = 16;
                s32 vx = 13;
                s32 vy = 36;
                s32 w = D_8010EF14_picking_panic * 2;

                if (i == 0 && D_8010EFA4_picking_panic > 30 && D_8010EFA4_picking_panic < 255) {
                    D_8010EE88_picking_panic += D_8010EE94_picking_panic;
                    D_8010EE8C_picking_panic += D_8010EE98_picking_panic;
                    D_8010EE98_picking_panic -= 6.25;
                }
                if (D_8010EFA4_picking_panic == 255 && D_8010E6EC_picking_panic % 60 == 7) {
                    D_8010EFA4_picking_panic = n + 30;
                    D_8010EE88_picking_panic = x;
                    D_8010EE94_picking_panic = vx;
                    D_8010EE8C_picking_panic = y;
                    D_8010EE98_picking_panic = vy;
                    D_8010EE90_picking_panic = rot;
                    for (j = 0; j < 2; j++) {
                        func_8001C258_main(D_8010EF00_picking_panic[w + j]->model[0], 4, 4);
                        func_8001C258_main(D_8010EF00_picking_panic[w + j]->model[1], 4, 0);
                        func_8001C624_main(D_8010EF00_picking_panic[w + j]->model[1],
                                           HmfModelData[D_8010EF00_picking_panic[w + j]->motion[2]].unk02, 50, n, 0);
                    }
                }
                if (D_8010EFA4_picking_panic > 30 && D_8010EFA4_picking_panic < 255) {
                    f = (f32)(D_8010EFA4_picking_panic - 30) / (f32)n;
                    g = f * f * 0.5 + f * 0.5;
                    Hu3DModelPosSet(D_8010EF00_picking_panic[w + i]->model[1],
                                    (i != 0) ? -D_8010EE88_picking_panic : D_8010EE88_picking_panic,
                                    D_8010EE8C_picking_panic, 50.0f);
                    Hu3DModelRotSet(D_8010EF00_picking_panic[w + i]->model[1], 0.0f,
                                    (i == 0) ? -(f * 45.0f + 45.0f) : f * 45.0f + 45.0f,
                                    (i != 0) ? -(g * D_8010EE90_picking_panic + (1.0f - g) * 180.0f) + 180.0f
                                             : g * D_8010EE90_picking_panic + (1.0f - g) * 180.0f + 180.0f);
                }
                if (D_8010EFA4_picking_panic < 31) {
                    f = (D_8010EFA4_picking_panic - 1) / 10.0;
                    if (f > 1.0f) {
                        f = 45.0f;
                    } else {
                        f = (f < 0.0f) ? 0.0f : f * 45.0f;
                    }
                    Hu3DModelPosSet(D_8010EF00_picking_panic[w + i]->model[1],
                                    (i != 0) ? -D_8010EE88_picking_panic : D_8010EE88_picking_panic,
                                    D_8010EE8C_picking_panic, 50.0f);
                    Hu3DModelRotSet(D_8010EF00_picking_panic[w + i]->model[1], 0.0f, (i == 0) ? -f : f,
                                    (i == 0) ? 360.0f : 0.0f);
                }
                if (D_8010EFA4_picking_panic == 30) {
                    func_8004AC98_main(D_8010EEE0_picking_panic[w + i]->unk03 + 50,
                                       D_8010EEE0_picking_panic[w + i]->unk00);
                    func_8001C5B4_main(D_8010EF00_picking_panic[w + i]->model[1],
                                       D_8010EF00_picking_panic[w + i]->motion[3]);
                    func_8001C6A8_main(D_8010EF00_picking_panic[w + i]->model[1], 2.0f);
                    func_8001C814_main(D_8010EF00_picking_panic[w + i]->model[1], 3, 0);
                }
                if (D_8010EFA4_picking_panic == 26) {
                    func_8001C624_main(D_8010EF00_picking_panic[w + i]->model[1],
                                       HmfModelData[D_8010EF00_picking_panic[w + i]->motion[0]].unk02, 0, 20, 2);
                }
                if (i == 1 && D_8010EFA4_picking_panic < 255) {
                    if (D_8010EFA4_picking_panic == i) {
                        for (j = 0; j < 3; j++) {
                            func_8001C258_main(D_8010EEFC_picking_panic->model[j + 32], 4, 4);
                            func_8001C258_main(D_8010EEFC_picking_panic->model[j + 35], 4, 4);
                        }
                        func_8001C258_main(D_8010EEFC_picking_panic->model[8], 4, 4);
                        func_8001C258_main(D_8010EEFC_picking_panic->model[9], 4, 4);
                    }
                    D_8010EFA4_picking_panic = (D_8010EFA4_picking_panic != 0) ? D_8010EFA4_picking_panic - 1 : 0;
                }
            }
        }
    }

    m = &HmfModelData[D_8010EEFC_picking_panic->model[arg1 + 10]];
    if (m->unk40 >= 60.0f) {
        m->unk40 = 0.0f;
        func_8001C258_main(D_8010EEFC_picking_panic->model[arg1 + 10], 4, 4);
    }
    D_8010EF10_picking_panic[arg1] =
        (D_8010EF10_picking_panic[arg1] < 46 && D_8010EF10_picking_panic[arg1] != 0) ? D_8010EF10_picking_panic[arg1] + 1 : 0;
    if (D_8010EF80_picking_panic == 0 || (D_8010EF80_picking_panic == 1 && D_8010EFA8_picking_panic < 45)) {
        D_8010EF10_picking_panic[arg1] = 1;
    }
    if (D_8010EF10_picking_panic[arg1] == 15) {
        if (D_8010E6F0_picking_panic[arg1][(D_8010EEF0_picking_panic[arg1] + 1) % 4] == 0) {
            D_8010EEF0_picking_panic[arg1] = (D_8010EEF0_picking_panic[arg1] + 1) % 4;
            D_8010E6F0_picking_panic[arg1][D_8010EEF0_picking_panic[arg1]] = 1;
            if (D_8010E714_picking_panic[arg1] < 6) {
                D_8010EF98_picking_panic[arg1] = D_8010E718_picking_panic[D_8010E714_picking_panic[arg1]];
            } else {
                t = rand8();
                D_8010EF98_picking_panic[arg1] =
                    (u32)(t % (((D_8010EF15_picking_panic[arg1] >= 4) &&
                                (D_8010EF15_picking_panic[arg1] - D_8010EF15_picking_panic[1 - arg1] >= 4)) + 5)) >> 1;
            }
            if (D_8010EF98_picking_panic[arg1] == 2 && D_8010EF15_picking_panic[arg1] == 0 &&
                D_8010E5B0_picking_panic.unk1E < 451) {
                D_8010EF98_picking_panic[arg1] = 0;
            }
            D_8010E714_picking_panic[arg1] = (D_8010E714_picking_panic[arg1] < 6) ? D_8010E714_picking_panic[arg1] + 1 : D_8010E714_picking_panic[arg1];
        } else {
            D_8010EF10_picking_panic[arg1]--;
        }
    }
    if (D_8010E6EC_picking_panic % 60 == 0) {
        D_8010E704_picking_panic[arg1].unk00 = (D_8010E704_picking_panic[arg1].unk00 > 0) ? D_8010E704_picking_panic[arg1].unk00 - 1 : D_8010E704_picking_panic[arg1].unk00;
    }
    if (D_8010E6EC_picking_panic % 60 == 0) {
        D_8010E704_picking_panic[arg1].unk06 = (D_8010E704_picking_panic[arg1].unk06 > 0) ? D_8010E704_picking_panic[arg1].unk06 - 1 : D_8010E704_picking_panic[arg1].unk06;
    }

    /* Front player: hook the next item at the counter. */
    if (D_8010EF80_picking_panic == 2 && D_8010E700_picking_panic[i0] == -1 &&
        D_8010E6F0_picking_panic[arg1][D_8010EEF0_picking_panic[arg1]] == 1 && D_8010EF98_picking_panic[arg1] != -1 &&
        ((D_8010EF10_picking_panic[arg1] == 0) | (D_8010EF10_picking_panic[arg1] >= 30)) &&
        ((p0->unk04 == -1) ? (D_800D5558_main[p0->unk02] & 0x8000) : (D_8010E704_picking_panic[arg1].unk00 == 0))) {
        f = D_8010EE70_picking_panic - -855.0f;
        g = D_8010EE74_picking_panic - -25.0f;
        if (f * f + g * g < 17929.21) {
            k = D_8010EEF0_picking_panic[arg1];
            D_8010E700_picking_panic[i0] = k;
            D_8010E6F0_picking_panic[arg1][k] = 2;
            D_8010EDA0_picking_panic[arg1][k] = D_8010EF98_picking_panic[arg1];
            D_8010EF98_picking_panic[arg1] = -1;
            D_8010EF10_picking_panic[arg1] = 1;
            D_8010E6F8_picking_panic[i0] = 6;
            D_8010E6FC_picking_panic[i0] = 23;
            func_8001EF6C_main(*D_8010EF18_picking_panic[arg1][k][D_8010EDA0_picking_panic[arg1][k]], o0->model[0], "item_hook");
            func_8001C258_main(*D_8010EF18_picking_panic[arg1][k][D_8010EDA0_picking_panic[arg1][k]], 0x4000, 0x4000);
            if (p0->unk04 != -1) {
                D_8010E704_picking_panic[arg1].unk00 = (rand8() < tbl.unk00[p0->unk04]) ? 2 : 1;
                D_8010E704_picking_panic[arg1].unk02 = rand8() % (tbl.unk08[p0->unk04] * 2) - tbl.unk08[p0->unk04];
            }
            if (p1->unk04 != -1) {
                D_8010E704_picking_panic[arg1].unk04 = tbl.unk10[p1->unk04];
            }
            t = D_8010EDA0_picking_panic[arg1][k];
            if (t == 0) {
                se = 0x36F;
            } else if (t == 1) {
                se = 0x36C;
            } else {
                se = 0x370;
            }
            func_8004AC98_main(se, arg1 * 2);
            omVibrate(p0->unk00, 2, 3, 10);
        }
    }
    /* Back player: hook a thrown item. */
    if (D_8010EF80_picking_panic == 2 && D_8010E700_picking_panic[i1] == -1 &&
        ((p1->unk04 == -1) ? (D_800D5558_main[p1->unk02] & 0x8000) : (rand8() < D_8010E704_picking_panic[arg1].unk04))) {
        for (j = 0; j < 4; j++) {
            if (D_8010E6F0_picking_panic[arg1][j] == 3) {
                f = D_8010EE78_picking_panic - D_8010EDB0_picking_panic[arg1][j];
                g = D_8010EE7C_picking_panic - D_8010EDD0_picking_panic[arg1][j];
                if (f * f + g * g < 16900.0) {
                    D_8010E700_picking_panic[i1] = j;
                    D_8010E6F0_picking_panic[arg1][j] = 4;
                    D_8010E6F8_picking_panic[i1] = 6;
                    D_8010E6FC_picking_panic[i1] = 23;
                    Hu3DModelPosSet(((j & 1) ? o1 : o0)->model[(j / 2 != 0) ? D_8010EDA0_picking_panic[arg1][j] + 5 : D_8010EDA0_picking_panic[arg1][j] + 2],
                                    0.0f, 0.0f, 0.0f);
                    func_8001EF6C_main(*D_8010EF18_picking_panic[arg1][j][D_8010EDA0_picking_panic[arg1][j]], o1->model[0], "item_hook");
                    func_8001C258_main(*D_8010EF18_picking_panic[arg1][j][D_8010EDA0_picking_panic[arg1][j]], 0x4000, 0x4000);
                    if (p1->unk04 != -1) {
                        D_8010E704_picking_panic[arg1].unk06 = rand8() < tbl.unk18[p1->unk04];
                    }
                    t = D_8010EDA0_picking_panic[arg1][j];
                    if (t == 0) {
                        se = 0x36F;
                    } else if (t == 1) {
                        se = 0x36C;
                    } else {
                        se = 0x370;
                    }
                    func_8004AC98_main(se, arg1 * 2 + 1);
                    omVibrate(p1->unk00, 2, 3, 10);
                    break;
                }
            }
        }
    }

    /* Front player: throw the hooked item. */
    if (D_8010EF80_picking_panic >= 2 && D_8010E700_picking_panic[i0] != -1 &&
        D_8010E6F0_picking_panic[arg1][D_8010E700_picking_panic[i0]] == 2 &&
        (D_8010EF80_picking_panic != 2 ||
         ((p0->unk04 == -1) ? !((u16)D_800CDA7C_main[p0->unk02] & 0x8000)
                            : (D_8010E6EC_picking_panic % 60 == (D_8010E704_picking_panic[arg1].unk02 + 68) % 60)))) {
        if (o0->rot.z > 210.0f) {
            f = 0.0f;
        } else if (o0->rot.z > 160.0f) {
            f = 1.0f;
        } else {
            f = (210.0f - o0->rot.z) / 50.0f;
        }
        k = D_8010E700_picking_panic[i0];
        D_8010E700_picking_panic[i0] = -1;
        D_8010E6F0_picking_panic[arg1][k] = 3;
        D_8010EDB0_picking_panic[arg1][k] = D_8010EE70_picking_panic;
        D_8010EDD0_picking_panic[arg1][k] = D_8010EE74_picking_panic;
        D_8010EDF0_picking_panic[arg1][k] = 0.0f;
        D_8010EE50_picking_panic[arg1][k] = 0.0f;
        if (D_8010EF80_picking_panic == 2) {
            D_8010EE10_picking_panic[arg1][k] =
                ((D_8010EE80_picking_panic * 0.875 - 5.0) * f + (1.0f - f) * 24.25) *
                (D_8010EDA0_picking_panic[arg1][k] * 0.15 + 0.85);
            D_8010EE30_picking_panic[arg1][k] =
                ((D_8010EE84_picking_panic * 0.875 + 10.0) * f + (1.0f - f) * 57.5) *
                (D_8010EDA0_picking_panic[arg1][k] * 0.15 + 0.85);
        } else {
            D_8010EE10_picking_panic[arg1][k] = D_8010EE30_picking_panic[arg1][k] = 0.0f;
        }
        func_8001C258_main(*D_8010EF18_picking_panic[arg1][k][D_8010EDA0_picking_panic[arg1][k]], 0x4000, 0);
        D_8010E6F8_picking_panic[i0] = 18;
        D_8010E6FC_picking_panic[i0] = 0;
        func_8004AC98_main(0x36D, arg1 * 2);
    }
    /* Back player: throw the hooked item into the basket. */
    if (D_8010EF80_picking_panic >= 2 && D_8010E700_picking_panic[i1] != -1 &&
        D_8010E6F0_picking_panic[arg1][D_8010E700_picking_panic[i1]] == 4 &&
        (D_8010EF80_picking_panic != 2 ||
         ((p1->unk04 == -1) ? !((u16)D_800CDA7C_main[p1->unk02] & 0x8000)
                            : (D_8010E704_picking_panic[arg1].unk06 == 0 &&
                               ((D_8010E6EC_picking_panic % 60 - 43 < 5u && (u8)(rand8() % 3) == 0) ||
                                D_8010E6EC_picking_panic % 60 == 48))))) {
        f32 sp38init[11] = { 30.0f, 30.0f, 26.0f, 25.0f, 24.0f, 26.0f, 23.0f, 23.0f, 25.5f, 26.0f, 30.0f };
        f64 d;

        t = (D_8010E6EC_picking_panic + 15) % 60;
        t = (t - 30 > 0) ? 60 - t : t;
        k = D_8010E700_picking_panic[i1];
        D_8010E700_picking_panic[i1] = -1;
        D_8010E6F0_picking_panic[arg1][k] = 5;
        D_8010EDB0_picking_panic[arg1][k] = D_8010EE78_picking_panic;
        D_8010EDD0_picking_panic[arg1][k] = D_8010EE7C_picking_panic;
        D_8010EDF0_picking_panic[arg1][k] = 0.0f;
        D_8010EDA8_picking_panic[arg1][k] = 0;
        D_8010EE50_picking_panic[arg1][k] = 0.0f;
        d = (t - 7 < 11u) ? sp38init[t - 7] : 23.0;
        D_8010EE10_picking_panic[arg1][k] = d * ((t >= 5 && t < 14) ? (t - 5) / 9.0 : (t >= 5 && t < 22) ? 1.0 - (t - 14) / 8.0 : 0.0);
        if (t >= 5 && t < 14) {
            D_8010EE30_picking_panic[arg1][k] = (t - 5) / 9.0 * 60.0;
        } else if (t >= 5 && t < 22) {
            D_8010EE30_picking_panic[arg1][k] = (1.0 - (t - 14) / 8.0) * 60.0;
        } else {
            D_8010EE30_picking_panic[arg1][k] = 0.0f;
        }
        func_8001C258_main(*D_8010EF18_picking_panic[arg1][k][D_8010EDA0_picking_panic[arg1][k]], 0x4000, 0);
        D_8010E6F8_picking_panic[i1] = 18;
        D_8010E6FC_picking_panic[i1] = 0;
        func_8004AC98_main(0x36D, arg1 * 2 + 1);
    }

    /* Ease the two arm motions towards their targets. */
    for (i = 0; i < 2; i++) {
        k = arg1 * 2 + i;
        if (D_8010E6F8_picking_panic[k] < D_8010E6FC_picking_panic[k]) {
            if (D_8010E6F8_picking_panic[k] + 2 <= D_8010E6FC_picking_panic[k]) {
                D_8010E6F8_picking_panic[k] = D_8010E6F8_picking_panic[k] + 2;
            } else {
                D_8010E6F8_picking_panic[k] = D_8010E6FC_picking_panic[k];
            }
        } else if (D_8010E6F8_picking_panic[k] > D_8010E6FC_picking_panic[k]) {
            if (D_8010E6F8_picking_panic[k] - 2 >= D_8010E6FC_picking_panic[k]) {
                D_8010E6F8_picking_panic[k] = D_8010E6F8_picking_panic[k] - 2;
            } else {
                D_8010E6F8_picking_panic[k] = D_8010E6FC_picking_panic[k];
            }
        }
        func_8001C6A8_main(D_8010EF00_picking_panic[k]->model[0], D_8010E6F8_picking_panic[k]);
    }

    /* Thrown items in flight. */
    for (j = 0; j < 4; j++) {
        prevY = D_8010EDD0_picking_panic[arg1][j];
        if (D_8010E6F0_picking_panic[arg1][j] == 3 || D_8010E6F0_picking_panic[arg1][j] == 5) {
            mdl = ((j & 1) ? o1 : o0)->model[(j / 2 != 0) ? D_8010EDA0_picking_panic[arg1][j] + 5 : D_8010EDA0_picking_panic[arg1][j] + 2];
            i = 2;
            D_8010EE30_picking_panic[arg1][j] -= 6.25;
            if (D_8010E6F0_picking_panic[arg1][j] == 5) {
                x = D_8010EDB0_picking_panic[arg1][j] + D_8010EE10_picking_panic[arg1][j];
                y = D_8010EDD0_picking_panic[arg1][j] + D_8010EE30_picking_panic[arg1][j];
                for (i = 0; i < 2; i++) {
                    wall = (i == 0) ? 827.0f : 953.0f;
                    if (y - 47.5 < -152.0 && -292.0 < y + 47.5 && x - 47.5 < wall && wall < x + 47.5) {
                        h2 = 2256.25 - (wall - x) * (wall - x);
                        h = (h2 <= 0.0f) ? 0.0f : HuSqrtf(h2);
                        if (y - h < -152.0f && y + h > -292.0f) {
                            h2 = 2256.25 - (wall - D_8010EDB0_picking_panic[arg1][j]) * (wall - D_8010EDB0_picking_panic[arg1][j]);
                            g = (h2 <= 0.0f) ? 0.0f : HuSqrtf(h2);
                            if (h2 > 0.0f && D_8010EDD0_picking_panic[arg1][j] - g < -152.0f &&
                                g + D_8010EDD0_picking_panic[arg1][j] > -292.0f) {
                                D_8010EDB0_picking_panic[arg1][j] = (i == 0) ? wall + 47.5 : wall - 47.5;
                                D_8010EE10_picking_panic[arg1][j] = 0.0f;
                            } else {
                                ang = atan2df(h, x - wall);
                                spd = HuSqrtf(D_8010EE10_picking_panic[arg1][j] * D_8010EE10_picking_panic[arg1][j] +
                                              D_8010EE30_picking_panic[arg1][j] * D_8010EE30_picking_panic[arg1][j]) * 0.25;
                                ang = ((ang < 0.0f) ? ang + 90.0f : ang + 0.0f) * 2.0f - 90.0f;
                                if ((D_8010EDA8_picking_panic[arg1][j] == 1) | (spd < 7.0f) ||
                                    (ang > 180.0f && ((i == 0) ? (x < wall) : (wall < x)))) {
                                    D_8010EDB0_picking_panic[arg1][j] = (i == 0) ? wall + 47.5 : wall - 47.5;
                                    D_8010EE10_picking_panic[arg1][j] = 0.0f;
                                } else {
                                    D_8010EDD0_picking_panic[arg1][j] = (D_8010EDD0_picking_panic[arg1][j] >= -222.0f) ? -104.5f : -339.5f;
                                    D_8010EE10_picking_panic[arg1][j] = cosdf(ang) * spd;
                                    D_8010EE30_picking_panic[arg1][j] = sindf(ang) * spd;
                                    D_8010EDB0_picking_panic[arg1][j] += D_8010EE10_picking_panic[arg1][j];
                                }
                            }
                            D_8010EDD0_picking_panic[arg1][j] += D_8010EE30_picking_panic[arg1][j];
                            break;
                        }
                    }
                }
            }
            if (i == 2) {
                D_8010EDB0_picking_panic[arg1][j] += D_8010EE10_picking_panic[arg1][j];
                D_8010EDD0_picking_panic[arg1][j] += D_8010EE30_picking_panic[arg1][j];
                D_8010EDA8_picking_panic[arg1][j] = 0;
            }
            D_8010EDF0_picking_panic[arg1][j] += D_8010EE50_picking_panic[arg1][j];
            if (D_8010E6F0_picking_panic[arg1][j] == 5 && 827.0 <= D_8010EDB0_picking_panic[arg1][j] - 47.5 &&
                D_8010EDB0_picking_panic[arg1][j] + 47.5 <= 953.0 && D_8010EDD0_picking_panic[arg1][j] - 47.5 <= -257.0 &&
                -257.0 < prevY - 47.5) {
                if (D_8010EF80_picking_panic < 3) {
                    D_8010EF15_picking_panic[arg1] += 3 - D_8010EDA0_picking_panic[arg1][j];
                    if (D_8010EF15_picking_panic[arg1] >= 100) {
                        D_8010EF15_picking_panic[arg1] = 99;
                    }
                    omVibrate(p0->unk00, 5, 0, 5);
                    omVibrate(p1->unk00, 5, 0, 5);
                }
                func_8001C258_main(mdl, 4, 4);
                func_8001C6A8_main(D_8010EEFC_picking_panic->model[arg1 + 2], 0.0f);
                func_8001C814_main(D_8010EEFC_picking_panic->model[arg1 + 2], 1, 0);
                func_8001C6A8_main(D_8010EEFC_picking_panic->model[arg1], 0.0f);
                func_8001C814_main(D_8010EEFC_picking_panic->model[arg1], 1, 0);
                func_8004AC98_main(0x36E, arg1);
                D_8010E6F0_picking_panic[arg1][j] = 0;
            } else if (D_8010EDD0_picking_panic[arg1][j] < -500.0f) {
                func_8001C258_main(mdl, 4, 4);
                D_8010E6F0_picking_panic[arg1][j] = 0;
            } else {
                Hu3DModelPosSet(*D_8010EF18_picking_panic[arg1][j][D_8010EDA0_picking_panic[arg1][j]],
                                D_8010EDB0_picking_panic[arg1][j], D_8010EDD0_picking_panic[arg1][j], 0.0f);
                Hu3DModelRotSet(*D_8010EF18_picking_panic[arg1][j][D_8010EDA0_picking_panic[arg1][j]], 0.0f, 0.0f,
                                D_8010EDF0_picking_panic[arg1][j]);
            }
        }
    }
    if (arg1 == 1 && (D_8010EF80_picking_panic != 0 || D_8010EFA8_picking_panic >= 7)) {
        D_8010E6EC_picking_panic++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B908_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAB8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAE8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAF0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAF8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAFC_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB00_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB04_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB08_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB10_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB18_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB20_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB28_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB30_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB38_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB40_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB48_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB50_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB58_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB60_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB68_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB70_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB78_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB80_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB88_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB90_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB98_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBA0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBA8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBB0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBB8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBC0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBC8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBD0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBD8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBE0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBE8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBF0_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBF8_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC00_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC08_picking_panic);
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC10_picking_panic);
#endif









































