#include "common.h"

#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

typedef func_800E1BA8_minigame_ObjData MgWork;

/* One slot of the overlay's object table (D_80111700_messy_memory, 136 x 0x84; Coconut Conk's layout). */
typedef struct MmEnt {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 grp;
    /* 0x42 */ s16 spr;
    /* 0x44 */ Vec pos;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} MmEnt; // Size 0x84

/* A camera (D_80111340_messy_memory). */
typedef struct MmCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} MmCamera; // Size 0x2C

void func_800142A0_main(s32);
void func_8004A208_main(void);
s32 func_8000B710_main(s32 arg0);
void func_8004AB0C_main(s32);
void osViBlack(u8 active);
extern u16 D_800D530C_main;
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];

/* A board point in screen units (D_80110FE0 board origins, D_80111044 slot offsets). */
typedef struct MmPt {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} MmPt; // Size 4

/* .data */
extern MmPt D_80110FE0_messy_memory[5];
extern MmPt D_80111044_messy_memory[20];
extern s16 D_80111338_messy_memory;
extern s16 D_8011133A_messy_memory;
extern MmCamera D_80111340_messy_memory[2];

/* .bss */
extern MmEnt D_80111700_messy_memory[136];
extern MmEnt D_801134E8_messy_memory[]; /* = D_80111700_messy_memory[58] */
extern MmEnt D_80113884_messy_memory[]; /* = D_80111700_messy_memory[65] */
extern MmEnt D_80113A94_messy_memory[]; /* = D_80111700_messy_memory[69] */
extern s32 D_80111640_messy_memory[4];
extern u8 D_80111670_messy_memory[4];
extern u8 D_80111678_messy_memory[4][10];
extern u8 D_801116A4_messy_memory[10];
extern u8 D_801116B0_messy_memory[4][10];
extern u8 D_80115D72_messy_memory[];
extern u8 D_80115D80_messy_memory[4];
extern s8 D_80115D8C_messy_memory;
extern s16 D_80115D8E_messy_memory;

/* .rodata */
const s16 D_801115F4_messy_memory[];

#define MM_SLOTX(p, i) ((f32)(D_80111044_messy_memory[i].x + D_80110FE0_messy_memory[p].x))
#define MM_SLOTY(p, i) ((f32)(D_80111044_messy_memory[i].y + D_80110FE0_messy_memory[p].y))
#define MM_ITEM(p, i) (&D_80111700_messy_memory[(p) * 10 + 8 + (i)])
#define MM_NEAR(a, b, d) ((a) - (d) <= (b) && (b) <= (a) + (d))
#define MM_NEAR2(a, b, lo, hi) ((a) - (lo) <= (b) && (b) <= (a) + (hi))
#define MM_STEER(e)                                                                                                    \
    e->unk24 = 0.0f;                                                                                                   \
    e->unk28 = 0.0f;                                                                                                   \
    if (e->unk1C + 5.0f < e->pos.x) {                                                                                  \
        e->unk24 = 1.0f;                                                                                               \
    }                                                                                                                  \
    if (e->pos.x < e->unk1C - 5.0f) {                                                                                  \
        e->unk24 = 2.0f;                                                                                               \
    }                                                                                                                  \
    if (e->unk20 + 5.0f < e->pos.y) {                                                                                  \
        e->unk28 = 1.0f;                                                                                               \
    }                                                                                                                  \
    if (e->pos.y < e->unk20 - 5.0f) {                                                                                  \
        e->unk28 = 2.0f;                                                                                               \
    }
/* Picks up item k of player p's board (the held flag, the grab sound). */
#define MM_PICKUP(obj, p, k)                                                                                           \
    D_801116B0_messy_memory[p][k] = 1;                                                                                 \
    D_80111640_messy_memory[obj->work[0]] = 1;                                                                         \
    func_8004AC98_main(D_80111338_messy_memory, (s16)obj->work[0]);                                                    \
    D_80111670_messy_memory[p] = 1;
#define MM_DROP(obj, p, k)                                                                                             \
    D_801116B0_messy_memory[p][k] = 0;                                                                                 \
    D_80111640_messy_memory[obj->work[0]] = 0;                                                                         \
    func_8004AC98_main(D_8011133A_messy_memory, (s16)obj->work[0]);                                                    \
    D_80111670_messy_memory[p] = 0;

void func_80110EC4_messy_memory(void);
void func_80105A3C_messy_memory(void);
void func_80105B7C_messy_memory(s8 arg0);
void func_801109BC_messy_memory(omObjData *obj);
void func_8010FD98_messy_memory(omObjData *obj);
void func_8010FD3C_messy_memory(omObjData *object);
void func_8010FD60_messy_memory(omObjData *object);
void func_80110D50_messy_memory(void);
void func_8010EBB0_messy_memory(omObjData *obj);
void func_8010F04C_messy_memory(omObjData *obj);
void func_8010F3DC_messy_memory(omObjData *obj);

void func_801059A0_messy_memory(void) {
    func_80110EC4_messy_memory();
}

f32 func_801059BC_messy_memory(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

void func_80105A3C_messy_memory(void) {
    MmEnt *ent;
    u32 i;

    for (i = 0, ent = D_80111700_messy_memory; i < 136; i++, ent++) {
        ent->obj = NULL;
        ent->unk04 = 0;
        ent->unk06 = 0;
        ent->unk08 = 0;
        ent->unk0A = 0;
        ent->unk0C = 0;
        ent->unk0E = 0;
        ent->unk10 = 0;
        ent->unk12 = 0;
        ent->unk14 = 0;
        ent->unk16 = 0;
        ent->unk18 = 0;
        ent->unk1C = 0;
        ent->unk20 = 0;
        ent->unk24 = 0;
        ent->unk28 = 0;
        ent->unk2C = 0;
        ent->unk30 = 0;
        ent->unk34 = 0;
        ent->unk38 = 0;
        ent->unk3C = 0;
        ent->grp = -1;
        ent->spr = -1;
        ent->pos.x = ent->pos.y = ent->pos.z = 0.0f;
        ent->unk50.x = ent->unk50.y = ent->unk50.z = 0.0f;
        ent->unk5C.x = ent->unk5C.y = ent->unk5C.z = 0.0f;
        ent->unk68 = 0.0f;
        ent->unk6C = 0.0f;
        ent->unk70 = 0.0f;
        ent->unk74 = 0.0f;
        ent->unk78.x = ent->unk78.y = ent->unk78.z = 0.0f;
    }
}

void func_80105B04_messy_memory(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105B7C_messy_memory(s8 arg0) {
    D_80115D8C_messy_memory = arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80105B88_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_801060E0_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106140_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_801061AC_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_801113F0_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_801113FC_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_8011140C_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_8011141C_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_80111428_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_80111434_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_80111440_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_8011144C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010622C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_801063FC_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106588_messy_memory);

#ifdef NON_MATCHING
Gfx **func_80106620_messy_memory(Gfx **gfx) {
    Gfx *g = *gfx;

    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                  G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(g++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(g++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetPrimColor(g++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(g++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    *gfx = g;
    return gfx;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106620_messy_memory);
#endif

#ifdef NON_MATCHING
Gfx **func_80106704_messy_memory(Gfx **gfx) {
    Gfx *g = *gfx;

    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                  G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(g++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(g++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetRenderMode(g++, IM_RD | CVG_DST_FULL | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                     GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    *gfx = g;
    return gfx;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106704_messy_memory);
#endif

Gfx **func_801067D0_messy_memory(Gfx **gfx, u8 alpha) {
    Gfx *g;

    g = *gfx;
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, alpha);
    *gfx = g;
    return gfx;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106800_messy_memory);

/* A human player's hand in the putting-back phase: Z toggles the board, A picks up or puts down, the stick moves. */
#ifdef NON_MATCHING
void func_80106C60_messy_memory(omObjData *obj) {
    MmEnt *e;
    MmEnt *item;
    MmEnt *other;
    omObjData *iobj;
    omObjData *oobj;
    u16 p;
    u8 i;
    u8 j;
    u8 k;
    u8 hit;
    u8 free;
    f32 f;

    p = (u16)obj->work[0];
    e = &D_80111700_messy_memory[p];
    if (D_800D5558_main[GwPlayer[p].pad] & 0x2000) {
        switch (D_80115D80_messy_memory[p]) {
        case 0:
            D_80115D80_messy_memory[p] = 1;
            break;
        case 1:
            D_80115D80_messy_memory[p] = 2;
            break;
        }
    }
    free = 1;
    if (D_80115D80_messy_memory[p] != 0) {
        return;
    }
    hit = 0;
    D_80115D72_messy_memory[obj->work[0]] = 255;
    for (i = 0; i < 10; i++) {
        f = MM_SLOTX(p, i);
        if (MM_NEAR(f, e->pos.x, 7.0f)) {
            f = MM_SLOTY(p, i);
            if (f - 15.0f <= e->pos.y && e->pos.y <= f + 6.0f) {
                free = 0;
            }
        }
    }
    for (i = 10; i < 20; i++) {
        f = MM_SLOTX(p, i);
        if (MM_NEAR(f, e->pos.x, 7.0f)) {
            f = MM_SLOTY(p, i);
            if (f - 7.0f <= e->pos.y && e->pos.y <= f + 6.0f) {
                free = 0;
            }
        }
    }
    if (D_80111670_messy_memory[p] == 1) {
        for (i = 0; i < 10; i++) {
            item = MM_ITEM(p, i);
            iobj = item->obj;
            if (e->pos.x == item->pos.x && e->pos.y == item->pos.y) {
                for (j = 0; j < 10; j++) {
                    other = MM_ITEM(p, j);
                    oobj = other->obj;
                    if (iobj->work[1] * 10 + iobj->work[0] != oobj->work[1] * 10 + oobj->work[0]) {
                        for (k = 0; k < 20; k++) {
                            f = MM_SLOTX(p, k);
                            if (f <= other->pos.x && other->pos.x <= f) {
                                if (k < 10) {
                                    if (MM_NEAR(other->pos.x, e->pos.x, 7.0f) && other->pos.y - 15.0f <= e->pos.y &&
                                        e->pos.y <= other->pos.y + 6.0f) {
                                        hit = 1;
                                    }
                                } else {
                                    if (MM_NEAR(other->pos.x, e->pos.x, 7.0f) && other->pos.y - 7.0f <= e->pos.y &&
                                        e->pos.y <= other->pos.y + 6.0f) {
                                        hit = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (hit | free) {
        D_80115D72_messy_memory[obj->work[0]] = 150;
    }
    if (D_800D5558_main[GwPlayer[p].pad] & 0x8000) {
        switch (D_80111670_messy_memory[p]) {
        case 0:
            for (i = 0; i < 10; i++) {
                for (j = 0; j < 4; j++) {
                    item = MM_ITEM(j, i);
                    for (k = 0; k < 20; k++) {
                        f = MM_SLOTX(p, k);
                        if (f <= item->pos.x && item->pos.x <= f) {
                            if (k < 10) {
                                if (MM_NEAR(item->pos.x, e->pos.x, 7.0f) &&
                                    MM_NEAR2(item->pos.y, e->pos.y, 15.0f, 6.0f)) {
                                    MM_PICKUP(obj, j, i);
                                    omVibrate(p, 5, 0, 5);
                                }
                            } else {
                                if (MM_NEAR(item->pos.x, e->pos.x, 7.0f) &&
                                    MM_NEAR2(item->pos.y, e->pos.y, 7.0f, 6.0f)) {
                                    MM_PICKUP(obj, j, i);
                                    omVibrate(p, 5, 0, 5);
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 1:
            hit = 0;
            for (i = 0; i < 10; i++) {
                item = MM_ITEM(p, i);
                iobj = item->obj;
                if (e->pos.x == item->pos.x && e->pos.y == item->pos.y) {
                    for (j = 0; j < 10; j++) {
                        other = MM_ITEM(p, j);
                        oobj = other->obj;
                        if (iobj->work[1] * 10 + iobj->work[0] != oobj->work[1] * 10 + oobj->work[0]) {
                            for (k = 0; k < 20; k++) {
                                f = MM_SLOTX(p, k);
                                if (f <= other->pos.x && other->pos.x <= f) {
                                    if (k < 10) {
                                        if (MM_NEAR(other->pos.x, e->pos.x, 7.0f) &&
                                            other->pos.y - 15.0f <= e->pos.y && e->pos.y <= other->pos.y + 6.0f) {
                                            hit = 1;
                                        }
                                    } else {
                                        if (MM_NEAR(other->pos.x, e->pos.x, 7.0f) &&
                                            other->pos.y - 7.0f <= e->pos.y && e->pos.y <= other->pos.y + 6.0f) {
                                            hit = 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (!hit) {
                        for (k = 0; k < 10; k++) {
                            f = MM_SLOTX(p, k);
                            if (MM_NEAR(f, e->pos.x, 7.0f)) {
                                f = MM_SLOTY(p, k);
                                if (f - 15.0f <= e->pos.y && e->pos.y <= f + 6.0f) {
                                    D_801116B0_messy_memory[obj->work[0]][i] = 0;
                                    item->pos.x = MM_SLOTX(p, k);
                                    item->pos.y = MM_SLOTY(p, k);
                                    D_80111640_messy_memory[obj->work[0]] = 0;
                                    func_8004AC98_main(D_8011133A_messy_memory, (s16)obj->work[0]);
                                    D_80111670_messy_memory[p] = 0;
                                    omVibrate(p, 2, 3, 10);
                                }
                            }
                        }
                        for (k = 10; k < 20; k++) {
                            f = MM_SLOTX(p, k);
                            if (MM_NEAR(f, e->pos.x, 7.0f)) {
                                f = MM_SLOTY(p, k);
                                if (f - 7.0f <= e->pos.y && e->pos.y <= f + 6.0f) {
                                    D_801116B0_messy_memory[obj->work[0]][i] = 0;
                                    item->pos.x = MM_SLOTX(p, k);
                                    item->pos.y = MM_SLOTY(p, k);
                                    D_80111640_messy_memory[obj->work[0]] = 0;
                                    func_8004AC98_main(D_8011133A_messy_memory, (s16)obj->work[0]);
                                    D_80111670_messy_memory[p] = 0;
                                    omVibrate(p, 2, 3, 10);
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
    }
    if (D_800CBB6E_main[GwPlayer[p].pad] < -29) {
        e->pos.x -= 2.0f;
        if (e->pos.x < (f32)D_80110FE0_messy_memory[p].x + 30.0f) {
            e->pos.x = (f32)D_80110FE0_messy_memory[p].x + 30.0f;
        }
    }
    if (D_800CBB6E_main[GwPlayer[p].pad] >= 30) {
        e->pos.x += 2.0f;
        if ((f32)D_80110FE0_messy_memory[p].x + 140.0f < e->pos.x) {
            e->pos.x = (f32)D_80110FE0_messy_memory[p].x + 140.0f;
        }
    }
    if (D_800D20A1_main[GwPlayer[p].pad] >= 30) {
        e->pos.y -= 2.0f;
        if (e->pos.y < (f32)D_80110FE0_messy_memory[p].y + 20.0f) {
            e->pos.y = (f32)D_80110FE0_messy_memory[p].y + 20.0f;
        }
    }
    if (D_800D20A1_main[GwPlayer[p].pad] < -29) {
        e->pos.y += 2.0f;
        if ((f32)D_80110FE0_messy_memory[p].y + 108.0f < e->pos.y) {
            e->pos.y = (f32)D_80110FE0_messy_memory[p].y + 108.0f;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106C60_messy_memory);
#endif

/* A CPU player's brain in the putting-back phase: walks to items and slots on its board (D_80111700[p]). */
#ifdef NON_MATCHING
void func_80107C88_messy_memory(omObjData *obj) {
    MmEnt *e;
    MmEnt *item;
    MmEnt *other;
    omObjData *iobj;
    omObjData *oobj;
    u16 p;
    u8 i;
    u8 j;
    u8 k;
    u8 hit;
    u8 free;
    f32 f;

    p = (u16)obj->work[0];
    e = &D_80111700_messy_memory[p];
    if (e->unk14 >= 7) {
        if (e->unk12 == 0) {
            switch (GwPlayer[p].cpu_difficulty) {
            case 0:
                if (rand8() < 30) {
                    e->unk12 = 1;
                }
                break;
            case 1:
                if (rand8() < 20) {
                    e->unk12 = 1;
                }
                break;
            case 2:
                if (rand8() < 20) {
                    e->unk12 = 1;
                }
                break;
            case 3:
                if (rand8() < 30) {
                    e->unk12 = 1;
                }
                break;
            }
        }
        if (e->unk12 == 2) {
            if (D_80115D8E_messy_memory == 300 || D_80115D8E_messy_memory == 210) {
                switch (GwPlayer[p].cpu_difficulty) {
                case 0:
                    if (rand8() < 250) {
                        e->unk12 = 3;
                    }
                    break;
                case 1:
                    if (rand8() < 200) {
                        e->unk12 = 3;
                    }
                    break;
                case 2:
                    if (rand8() < 150) {
                        e->unk12 = 3;
                    }
                    break;
                case 3:
                    if (rand8() < 50) {
                        e->unk12 = 3;
                    }
                    break;
                }
            }
        }
        if (e->unk12 == 5) {
            switch (GwPlayer[p].cpu_difficulty) {
            case 0:
                if (rand8() < 250) {
                    e->unk12 = 6;
                }
                break;
            case 1:
                if (rand8() < 250) {
                    e->unk12 = 6;
                }
                break;
            case 2:
                if (rand8() < 250) {
                    e->unk12 = 6;
                }
                break;
            case 3:
                if (rand8() < 250) {
                    e->unk12 = 6;
                }
                break;
            }
        }
    }
    if (e->unk12 == 1 || e->unk12 == 3 || e->unk12 == 6) {
        switch (D_80115D80_messy_memory[p]) {
        case 0:
            D_80115D80_messy_memory[p] = 1;
            e->unk12++;
            e->unk06 = 0;
            break;
        case 1:
            D_80115D80_messy_memory[p] = 2;
            e->unk12++;
            e->unk06 = 0;
            break;
        }
    }
    if (D_80115D80_messy_memory[p] != 0) {
        return;
    }
    free = 1;
    hit = 0;
    D_80115D72_messy_memory[obj->work[0]] = 255;
    for (i = 0; i < 10; i++) {
        f = MM_SLOTX(p, i);
        if (MM_NEAR(f, e->pos.x, 7.0f)) {
            f = MM_SLOTY(p, i);
            if (f - 15.0f <= e->pos.y && e->pos.y <= f + 6.0f) {
                free = 0;
            }
        }
    }
    for (i = 10; i < 20; i++) {
        f = MM_SLOTX(p, i);
        if (MM_NEAR(f, e->pos.x, 7.0f)) {
            f = MM_SLOTY(p, i);
            if (f - 7.0f <= e->pos.y && e->pos.y <= f + 6.0f) {
                free = 0;
            }
        }
    }
    if (D_80111670_messy_memory[p] == 1) {
        for (i = 0; i < 10; i++) {
            item = MM_ITEM(p, i);
            iobj = item->obj;
            if (e->pos.x == item->pos.x && e->pos.y == item->pos.y) {
                for (j = 0; j < 10; j++) {
                    other = MM_ITEM(p, j);
                    oobj = other->obj;
                    if (iobj->work[1] * 10 + iobj->work[0] != oobj->work[1] * 10 + oobj->work[0]) {
                        for (k = 0; k < 20; k++) {
                            f = MM_SLOTX(p, k);
                            if (f <= other->pos.x && other->pos.x <= f) {
                                if (k < 10) {
                                    if (MM_NEAR(other->pos.x, e->pos.x, 7.0f) && other->pos.y - 15.0f <= e->pos.y &&
                                        e->pos.y <= other->pos.y + 6.0f) {
                                        hit = 1;
                                    }
                                } else {
                                    if (MM_NEAR(other->pos.x, e->pos.x, 7.0f) && other->pos.y - 7.0f <= e->pos.y &&
                                        e->pos.y <= other->pos.y + 6.0f) {
                                        hit = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (hit | free) {
        D_80115D72_messy_memory[obj->work[0]] = 150;
    }
    if (e->unk12 == 0) {
        switch (e->unk06) {
        case 0:
            k = rand8() % 10;
            item = MM_ITEM(p, k);
            if ((f32)D_80110FE0_messy_memory[p].y + 80.0f < item->pos.y) {
                e->unk08 = k;
                e->unk1C = item->pos.x;
                e->unk20 = item->pos.y;
                e->unk06 = 1;
            }
            if (e->unk06 != 1 && D_80111678_messy_memory[p][k] == 0 && D_80115D8E_messy_memory >= 451) {
                e->unk08 = k;
                e->unk1C = item->pos.x;
                e->unk20 = item->pos.y;
                e->unk06 = 10;
            }
            break;
        case 10:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(item->pos.x, e->pos.x, 5.0f) && MM_NEAR(item->pos.y, e->pos.y, 5.0f)) {
                e->unk06 = 0;
            }
            break;
        case 9:
            for (i = 0; i < 10; i++) {
                if (i != e->unk08) {
                    item = MM_ITEM(p, i);
                    if ((f32)D_80110FE0_messy_memory[p].y + 80.0f < item->pos.y) {
                        e->unk08 = i;
                        e->unk1C = item->pos.x;
                        e->unk20 = item->pos.y;
                        e->unk06 = 1;
                    }
                }
            }
            if (e->unk06 != 1) {
                e->unk06 = 0;
            }
            break;
        case 1:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(item->pos.x, e->pos.x, 5.0f) && MM_NEAR(item->pos.y, e->pos.y, 5.0f)) {
                MM_PICKUP(obj, p, e->unk08);
                if (D_80111678_messy_memory[p][e->unk08] == 1) {
                    e->unk06 = 2;
                } else {
                    e->unk06 = 3;
                }
            }
            break;
        case 2:
            for (i = 0; i < 10; i++) {
                if (D_801116A4_messy_memory[i] == D_80111700_messy_memory[p * 10 + 8 + e->unk08].obj->work[0]) {
                    e->unk1C = MM_SLOTX(p, i);
                    e->unk20 = MM_SLOTY(p, i);
                    e->unk0A = i;
                    e->unk06 = 4;
                }
            }
            break;
        case 3:
            item = MM_ITEM(p, e->unk08);
            iobj = item->obj;
            k = rand8() % 10;
            hit = 0;
            for (i = 0; i < 10; i++) {
                other = MM_ITEM(p, i);
                if (MM_SLOTX(p, k) == other->pos.x && MM_SLOTY(p, k) == other->pos.y) {
                    hit = 1;
                }
            }
            for (i = 0; i < 10; i++) {
                if (D_80111678_messy_memory[p][i] == 1 && D_801116A4_messy_memory[k] == i) {
                    hit = 1;
                }
            }
            if (!hit && D_801116A4_messy_memory[k] != iobj->work[0]) {
                e->unk1C = MM_SLOTX(p, k);
                e->unk20 = MM_SLOTY(p, k);
                e->unk0A = k;
                e->unk06 = 4;
                e->unk0E = 0;
            }
            if (!hit && D_801116A4_messy_memory[k] == iobj->work[0]) {
                if (e->unk14 >= 6) {
                    e->unk1C = MM_SLOTX(p, 10);
                    e->unk20 = MM_SLOTY(p, 10);
                    e->unk0A = k;
                    e->unk0C = 10;
                    e->unk06 = 5;
                    e->unk0E = 0;
                }
            }
            if (++e->unk0E >= 50) {
                e->unk0E = 0;
                e->unk06 = 9;
                for (i = 0; i < 20; i++) {
                    f = MM_SLOTX(p, i);
                    if (MM_NEAR(f, e->pos.x, 7.0f)) {
                        f = MM_SLOTY(p, i);
                        if (f - 7.0f <= e->pos.y && e->pos.y <= f + 6.0f) {
                            D_801116B0_messy_memory[p][e->unk08] = 0;
                            item->pos.x = MM_SLOTX(p, i);
                            item->pos.y = MM_SLOTY(p, i);
                            D_80111640_messy_memory[obj->work[0]] = 0;
                            func_8004AC98_main(D_8011133A_messy_memory, (s16)obj->work[0]);
                            D_80111670_messy_memory[p] = 0;
                        }
                    }
                }
            }
            break;
        case 4:
            MM_STEER(e);
            if (D_80115D8E_messy_memory >= 151) {
                switch (GwPlayer[p].cpu_difficulty) {
                case 0:
                    if (rand8() < 30) {
                        e->unk06 = 8;
                    }
                    break;
                case 1:
                    if (rand8() < 7) {
                        e->unk06 = 8;
                    }
                    break;
                case 2:
                    if (rand8() < 5) {
                        e->unk06 = 8;
                    }
                    break;
                case 3:
                    if (rand8() < 3) {
                        e->unk06 = 8;
                    }
                    break;
                }
            }
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(e->unk1C, e->pos.x, 5.0f) && MM_NEAR(e->unk20, e->pos.y, 5.0f)) {
                MM_DROP(obj, p, e->unk08);
                item->pos.x = MM_SLOTX(p, e->unk0A);
                item->pos.y = MM_SLOTY(p, e->unk0A);
                e->unk06 = 0;
                e->unk14++;
            }
            break;
        case 8:
            if (++e->unk10 % 10 == 0) {
                e->unk24 = 0.0f;
                e->unk28 = 0.0f;
                k = rand8();
                if (k % 2 == 0) {
                    e->unk24 = 1.0f;
                }
                if (k % 2 == 1) {
                    e->unk24 = 2.0f;
                }
                if ((u8)(k % 3) == 0) {
                    e->unk28 = 1.0f;
                }
                if ((u8)(k % 3) == 1) {
                    e->unk28 = 2.0f;
                }
            }
            if (e->unk10 >= 31) {
                e->unk10 = 0;
                e->unk06 = 4;
            }
            break;
        case 5:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(e->unk1C, e->pos.x, 5.0f) && MM_NEAR(e->unk20, e->pos.y, 5.0f)) {
                MM_DROP(obj, p, e->unk08);
                item->pos.x = MM_SLOTX(p, e->unk0C);
                item->pos.y = MM_SLOTY(p, e->unk0C);
                e->unk06 = 6;
            }
            break;
        case 6:
            k = rand8() % 10;
            item = MM_ITEM(p, k);
            if (item->pos.y < (f32)D_80110FE0_messy_memory[p].y + 80.0f && D_80111678_messy_memory[p][k] != 1) {
                e->unk08 = k;
                e->unk1C = item->pos.x;
                e->unk20 = item->pos.y;
                e->unk06 = 7;
            }
            break;
        case 7:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(item->pos.x, e->pos.x, 5.0f) && MM_NEAR(item->pos.y, e->pos.y, 5.0f)) {
                MM_PICKUP(obj, p, e->unk08);
                e->unk1C = MM_SLOTX(p, e->unk0A);
                e->unk20 = MM_SLOTY(p, e->unk0A);
                e->unk06 = 4;
                e->unk14--;
            }
            break;
        }
    }
    if (e->unk12 == 4) {
        switch (e->unk06) {
        case 0:
            k = rand8() % 10;
            item = MM_ITEM(p, k);
            if (item->pos.y < (f32)D_80110FE0_messy_memory[p].y + 80.0f) {
                e->unk08 = k;
                e->unk38 = e->unk1C = item->pos.x;
                e->unk3C = e->unk20 = item->pos.y;
                e->unk06 = 1;
            }
            break;
        case 1:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(item->pos.x, e->pos.x, 5.0f) && MM_NEAR(item->pos.y, e->pos.y, 5.0f)) {
                MM_PICKUP(obj, p, e->unk08);
                e->unk14--;
                e->unk06 = 2;
            }
            break;
        case 2:
            k = rand8() % 10;
            e->unk1C = MM_SLOTX(p, k + 10);
            e->unk20 = MM_SLOTY(p, k + 10);
            e->unk0A = k + 10;
            e->unk06 = 3;
            break;
        case 3:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(e->unk1C, e->pos.x, 5.0f) && MM_NEAR(e->unk20, e->pos.y, 5.0f)) {
                MM_DROP(obj, p, e->unk08);
                item->pos.x = MM_SLOTX(p, e->unk0A);
                item->pos.y = MM_SLOTY(p, e->unk0A);
                e->unk06 = 4;
            }
            break;
        case 4:
            k = rand8() % 10;
            item = MM_ITEM(p, k);
            if (item->pos.y < (f32)D_80110FE0_messy_memory[p].y + 80.0f) {
                e->unk08 = k;
                e->unk1C = item->pos.x;
                e->unk20 = item->pos.y;
                e->unk06 = 5;
            }
            break;
        case 5:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(item->pos.x, e->pos.x, 5.0f) && MM_NEAR(item->pos.y, e->pos.y, 5.0f)) {
                MM_PICKUP(obj, p, e->unk08);
                e->unk14--;
                e->unk06 = 6;
            }
            break;
        case 6:
            for (i = 0; i < 10; i++) {
                f = MM_SLOTX(p, i);
                if (e->unk38 == f && e->unk3C == MM_SLOTY(p, i)) {
                    e->unk1C = f;
                    e->unk20 = MM_SLOTY(p, i);
                    e->unk0A = i;
                    e->unk06 = 7;
                }
            }
            break;
        case 7:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(e->unk1C, e->pos.x, 5.0f) && MM_NEAR(e->unk20, e->pos.y, 5.0f)) {
                MM_DROP(obj, p, e->unk08);
                item->pos.x = MM_SLOTX(p, e->unk0A);
                item->pos.y = MM_SLOTY(p, e->unk0A);
                e->unk06 = 8;
                e->unk14++;
            }
            break;
        case 8:
            for (i = 0; i < 10; i++) {
                item = MM_ITEM(p, i);
                if ((f32)D_80110FE0_messy_memory[p].y + 80.0f < item->pos.y) {
                    e->unk08 = i;
                    e->unk1C = item->pos.x;
                    e->unk20 = item->pos.y;
                    e->unk06 = 9;
                }
            }
            break;
        case 9:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(item->pos.x, e->pos.x, 5.0f) && MM_NEAR(item->pos.y, e->pos.y, 5.0f)) {
                MM_PICKUP(obj, p, e->unk08);
                e->unk06 = 10;
            }
            break;
        case 10:
            hit = 0;
            for (i = 0; i < 10; i++) {
                for (j = 0; j < 10; j++) {
                    other = MM_ITEM(p, j);
                    if (MM_SLOTX(p, i) == other->pos.x && MM_SLOTY(p, i) == other->pos.y) {
                        hit = 1;
                    }
                }
                if (!hit) {
                    e->unk1C = MM_SLOTX(p, i);
                    e->unk20 = MM_SLOTY(p, i);
                    e->unk0A = i;
                    e->unk06 = 11;
                }
                hit = 0;
            }
            break;
        case 11:
            MM_STEER(e);
            item = MM_ITEM(p, e->unk08);
            if (MM_NEAR(e->unk1C, e->pos.x, 5.0f) && MM_NEAR(e->unk20, e->pos.y, 5.0f)) {
                MM_DROP(obj, p, e->unk08);
                item->pos.x = MM_SLOTX(p, e->unk0A);
                item->pos.y = MM_SLOTY(p, e->unk0A);
                e->unk06 = 12;
                e->unk14++;
                e->unk12 = 5;
            }
            break;
        }
    }
    if (e->unk24 == 1.0f) {
        e->pos.x -= 2.0f;
        if (e->pos.x < (f32)D_80110FE0_messy_memory[p].x + 30.0f) {
            e->pos.x = (f32)D_80110FE0_messy_memory[p].x + 30.0f;
        }
    }
    if (e->unk24 == 2.0f) {
        e->pos.x += 2.0f;
        if ((f32)D_80110FE0_messy_memory[p].x + 140.0f < e->pos.x) {
            e->pos.x = (f32)D_80110FE0_messy_memory[p].x + 140.0f;
        }
    }
    if (e->unk28 == 1.0f) {
        e->pos.y -= 2.0f;
        if (e->pos.y < (f32)D_80110FE0_messy_memory[p].y + 20.0f) {
            e->pos.y = (f32)D_80110FE0_messy_memory[p].y + 20.0f;
        }
    }
    if (e->unk28 == 2.0f) {
        e->pos.y += 2.0f;
        if ((f32)D_80110FE0_messy_memory[p].y + 108.0f < e->pos.y) {
            e->pos.y = (f32)D_80110FE0_messy_memory[p].y + 108.0f;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80107C88_messy_memory);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010ACE4_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010AD40_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010B32C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010B4CC_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010B5C8_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010C03C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010C37C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010C478_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010D55C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010D910_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010DA64_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010E29C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010E500_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010E654_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010EBB0_messy_memory);

void func_8010EE6C_messy_memory(void) {
    omObjData *obj;
    MmEnt *ent;
    s16 i;

    for (i = 0; i < 7; i++) {
        ent = &D_801134E8_messy_memory[i];
        obj = omAddObj(500, 1, 10, -1, func_8010EBB0_messy_memory);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010EF10_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010F04C_messy_memory);

void func_8010F15C_messy_memory(void) {
    omObjData *obj = omAddObj(250, 1, 10, -1, func_8010F04C_messy_memory);

    obj->work[0] = 0;
    D_80113A94_messy_memory[0].obj = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010F19C_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010F3DC_messy_memory);

void func_8010F644_messy_memory(void) {
    omObjData *obj;
    MmEnt *ent;
    s16 i;

    for (i = 0; i < 4; i++) {
        ent = &D_80113884_messy_memory[i];
        obj = omAddObj(470, 1, 3, -1, func_8010F3DC_messy_memory);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010F6E8_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FA38_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FBB0_messy_memory);

void func_8010FC90_messy_memory(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 495.050018f;
        CRotM[i].x = 335.14f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 204.0f;
        CenterM[i].z = -47.0f;
    }
}

void func_8010FD3C_messy_memory(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010FD60_messy_memory(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_8010FD3C_messy_memory;
    }
}

void func_8010FD98_messy_memory(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010FD60_messy_memory;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FDF0_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_801109BC_messy_memory);

void func_80110D48_messy_memory(void) {
}

void func_80110D50_messy_memory(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_80111340_messy_memory[i].scissor[0], D_80111340_messy_memory[i].scissor[1],
                   D_80111340_messy_memory[i].scissor[2], D_80111340_messy_memory[i].scissor[3]);
        ViewportSet(i, D_80111340_messy_memory[i].viewport[0], D_80111340_messy_memory[i].viewport[1],
                    D_80111340_messy_memory[i].viewport[2], D_80111340_messy_memory[i].viewport[3],
                    D_80111340_messy_memory[i].viewport[4], D_80111340_messy_memory[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_80111340_messy_memory[i].fov, 80.0f, 8000.0f);
    }
}

void func_80110EC4_messy_memory(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(32);
    omInitObjMan(150, 0);
    func_8004A208_main();
    HmfLightColorSet(0, 0x40, 0x40, 0x60);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 85.0f, 100.0f);
    func_80110D50_messy_memory();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_801115F4_messy_memory, 0);
    func_80045010_main(D_801115F4_messy_memory, 1);
    omAddObj(1000, 0, 0, -1, func_801109BC_messy_memory);
    omAddObj(1000, 0, 0, -1, func_8010FD98_messy_memory);
    func_80105A3C_messy_memory();
}

const s16 D_801115F4_messy_memory[] = { 0x8260, 0x8261, 0x8262, 0x0000 };

