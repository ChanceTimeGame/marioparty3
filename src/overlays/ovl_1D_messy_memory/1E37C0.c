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
extern s32 D_80110FC0_messy_memory[8]; /* voice sound bank per character (func_80045ED0_main) */
extern MmPt D_80110FE0_messy_memory[5];
extern MmPt D_80110FF4_messy_memory[20]; /* the shown room's slots */
extern MmPt D_80111044_messy_memory[20];
extern MmPt D_80111094_messy_memory[4];
extern Vec2f D_801110A4_messy_memory[20];
extern s32 D_801111EC_messy_memory[][2]; /* hand sprite group per character */
extern Vec2f D_80111298_messy_memory[4]; /* per player: walk speed, stop x */
extern s16 D_80111338_messy_memory;
extern s16 D_8011133A_messy_memory;
extern s16 D_8011133C_messy_memory;
extern MmCamera D_80111340_messy_memory[2];
/* The intro movers' walks, per mover: z and x step, the z where it stops, the start heading. */
typedef struct MmWalk {
    /* 0x00 */ f32 dz;
    /* 0x04 */ f32 dx;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 roty;
} MmWalk; // Size 0x10
extern MmWalk D_80111228_messy_memory[7];
extern s32 D_80111148_messy_memory[10][2]; /* item image groups, the players' boards */
extern s32 D_80111198_messy_memory[10][2]; /* item image groups, the shown room */

/* .bss */
extern MmEnt D_80111700_messy_memory[136];
extern MmEnt D_80111910_messy_memory[]; /* = D_80111700_messy_memory[4] */
extern MmEnt D_801134E8_messy_memory[]; /* = D_80111700_messy_memory[58] */
extern MmEnt D_80113884_messy_memory[]; /* = D_80111700_messy_memory[65] */
extern MmEnt D_80113A94_messy_memory[]; /* = D_80111700_messy_memory[69] */
extern s32 D_80111640_messy_memory[4];
extern s32 D_8011163C_messy_memory; /* the intro mover model (s16 value; retail reads its low half, D_8011163E) */
extern s32 D_80111608_messy_memory[10]; /* item sprite groups (s16 values) */
extern s32 D_80111634_messy_memory; /* the shadow sprite group (s16 value; retail reads its low half, D_80111636) */
extern HuSprite_Unk84_Struct *D_80111654_messy_memory; /* the room backdrop image */
extern HuSprite_Unk84_Struct *D_801116D8_messy_memory; /* the divider image */
extern u8 D_80111658_messy_memory[4]; /* hand shown, per player */
extern HuSprite_Unk84_Struct *D_80111660_messy_memory[4]; /* hand images, per player */
extern u8 D_80111630_messy_memory[4]; /* the players by score, best first */
extern u8 D_80111638_messy_memory;
extern u8 D_80111639_messy_memory;
extern u8 D_8011163B_messy_memory;
extern u16 D_80111650_messy_memory;
extern u8 D_8011163A_messy_memory;
extern f32 D_8011165C_messy_memory;
extern u8 D_80111674_messy_memory;
extern f32 D_801116A0_messy_memory;
extern u8 D_801116E0_messy_memory[20];
extern MmEnt D_80112FC0_messy_memory[]; /* = D_80111700_messy_memory[48] */
extern MmEnt D_80113B18_messy_memory[]; /* = D_80111700_messy_memory[70] */
extern s16 D_80115D84_messy_memory[4];
extern Vec2f D_80115D20_messy_memory[10];
extern u8 D_80115D76_messy_memory[4];
extern f32 D_80115D7C_messy_memory;
extern u8 D_80115D90_messy_memory[10];
extern u8 D_80115D9A_messy_memory;
extern u8 D_80111675_messy_memory;
extern s16 D_80115D70_messy_memory;
extern u8 D_80111670_messy_memory[4];
extern u8 D_80111678_messy_memory[4][10];
extern u8 D_801116A4_messy_memory[10];
extern u8 D_801116B0_messy_memory[40]; /* [player * 10 + item]: held */
extern u8 D_80115D72_messy_memory[];
extern u8 D_80115D80_messy_memory[4];
extern u8 D_80115D8C_messy_memory;
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
    D_801116B0_messy_memory[(p) * 10 + (k)] = 1;                                                                                 \
    D_80111640_messy_memory[obj->work[0]] = 1;                                                                         \
    func_8004AC98_main(D_80111338_messy_memory, (s16)obj->work[0]);                                                    \
    D_80111670_messy_memory[p] = 1;
#define MM_DROP(obj, p, k)                                                                                             \
    D_801116B0_messy_memory[(p) * 10 + (k)] = 0;                                                                                 \
    D_80111640_messy_memory[obj->work[0]] = 0;                                                                         \
    func_8004AC98_main(D_8011133A_messy_memory, (s16)obj->work[0]);                                                    \
    D_80111670_messy_memory[p] = 0;

void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_80105B88_messy_memory(Gfx **gfx, s32 arg1, s32 arg2);
Gfx **func_80106620_messy_memory(Gfx **gfx);
Gfx **func_80106704_messy_memory(Gfx **gfx);
Gfx **func_801067D0_messy_memory(Gfx **gfx, u8 alpha);
void func_801060E0_messy_memory(omObjData *obj);
void func_8010622C_messy_memory(omObjData *obj);
void func_801063FC_messy_memory(omObjData *obj);
void func_80107C88_messy_memory(omObjData *obj);
void func_80106C60_messy_memory(omObjData *obj);
void func_8010ACE4_messy_memory(omObjData *obj);
void func_8010AD40_messy_memory(omObjData *obj);
void func_8010B5C8_messy_memory(omObjData *obj);
void func_80106800_messy_memory(Gfx **gfx, s32 arg1, s32 arg2);
extern s32 D_800A178C_main[][6];
void func_80088800_main(f32 *mtx, f32 x, f32 y, f32 z);
omObjData *func_80045ED0_main(u32 arg0);
void func_8010B32C_messy_memory(omObjData *obj);
void func_8010C03C_messy_memory(omObjData *obj);
void func_8010D55C_messy_memory(omObjData *obj);
void func_8010E29C_messy_memory(omObjData *obj);
void func_8010E654_messy_memory(omObjData *obj);
void func_8010EF10_messy_memory(omObjData *obj);
void func_8010DA64_messy_memory(omObjData *obj);
void func_80106140_messy_memory(omObjData *obj);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_80110EC4_messy_memory(void);
f32 func_801059BC_messy_memory(f32 angle, f32 add);
/* A winner's cheer: the win motion and the character's voice. */
#define MM_WIN(obj)                                                                                                    \
    func_8001C5B4_main(obj->model[0], obj->motion[3]);                                                                 \
    func_80045ED0_main((D_80110FC0_messy_memory[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
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

/* Draws the room backdrop (D_80111654: a 320-wide CI4 image, six rows a strip) and the centre divider (D_801116D8). */
void func_80105B88_messy_memory(Gfx **gfx, s32 arg1, s32 arg2) {
    Gfx *g = *gfx;
    s32 i;
    s32 x;
    s32 y;

    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                                  G_SHADING_SMOOTH);
    gSPSetGeometryMode(g++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(g++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetPrimColor(g++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(g++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetTextureLUT(g++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(g++, 0, D_80111654_messy_memory->unk0C);
    x = 0;
    for (i = 0, y = 108; i < 24; i += 6) {
        gDPSetTextureImage(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 160, D_80111654_messy_memory->unk08);
        gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 20, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
        gDPLoadSync(g++);
        gDPLoadTile(g++, G_TX_LOADTILE, 0, i * 4, 160 * 4, (i + 6) * 4);
        gDPPipeSync(g++);
        gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_4b, 20, 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0);
        gDPSetTileSize(g++, G_TX_RENDERTILE, 0, i * 4, 320 * 4, (i + 6) * 4);
        gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 320 * 4, 6 * 4);
        gSPTextureRectangle(g++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 6) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);
    }
    gDPSetTextureLUT(g++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(g++, 0, D_801116D8_messy_memory->unk0C);
    x = 148;
    for (i = 0, y = 0; i < 240; i += 16) {
        gDPSetTextureImage(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 12, D_801116D8_messy_memory->unk08);
        gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 2, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
        gDPLoadSync(g++);
        gDPLoadTile(g++, G_TX_LOADTILE, 0, i * 4, 12 * 4, (i + 16) * 4);
        gDPPipeSync(g++);
        gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0);
        gDPSetTileSize(g++, G_TX_RENDERTILE, 0, i * 4, 24 * 4, (i + 16) * 4);
        gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 24 * 4, 16 * 4);
        gSPTextureRectangle(g++, x << 2, (y + i) << 2, (x + 24) << 2, (y + i + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }
    *gfx = g;
}

void func_801060E0_messy_memory(omObjData *obj) {
    switch (D_80115D8C_messy_memory) {
    case 8:
        func_8001C258_main(obj->model[0], 4, 0);
        break;
    case 12:
        func_8001C258_main(obj->model[0], 4, 4);
        break;
    }
}

void func_80106140_messy_memory(omObjData *obj) {
    obj->model[0] = func_8001AC8C_main(0, func_80105B88_messy_memory, 2);
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->func = func_801060E0_messy_memory;
}

void func_801061AC_messy_memory(void) {
    omObjData *obj;

    D_80111654_messy_memory = func_80055194_main(func_8000B838_main(0x3E0002));
    D_801116D8_messy_memory = func_80055194_main(func_8000B838_main(0x3E0004));
    obj = omAddObj(200, 1, 0, -1, func_80106140_messy_memory);
    obj->work[0] = 0;
    D_80111700_messy_memory[7].obj = obj;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_801113F0_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_801113FC_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_8011140C_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_8011141C_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_80111428_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_80111434_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_80111440_messy_memory);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", D_8011144C_messy_memory);

#ifdef NON_MATCHING
/* The title sign (D_80111700[4]): appears, shrinks away when the room is shown, grows back for scoring. */
void func_8010622C_messy_memory(omObjData *obj) {
    MmEnt *ent = &D_80111700_messy_memory[4];

    switch (D_80115D8C_messy_memory) {
    case 4:
        if (obj->work[0] == 0) {
            func_8000BC88_main(D_80111700_messy_memory[4].spr, 0x4000);
        }
        break;
    case 5:
        if (obj->work[0] == 0) {
            if (D_80111700_messy_memory[4].unk04 == 0) {
                HuAudFXPlay(1009);
                D_80111700_messy_memory[4].unk04 = 1;
            }
            ent->unk5C.x = ent->unk5C.y = D_8011165C_messy_memory;
            func_8000BE5C_main(ent->spr, ent->unk5C.x, ent->unk5C.y);
            if (ent->unk5C.x <= 0.01 || ent->unk5C.y <= 0.01) {
                D_80115D9A_messy_memory = 5;
                func_8000BB94_main(ent->spr);
            }
        }
        break;
    case 12:
        if (obj->work[0] == 0) {
            D_80111700_messy_memory[4].unk5C.x = D_80111700_messy_memory[4].unk5C.y = D_8011165C_messy_memory;
            func_8000BE5C_main(D_80111700_messy_memory[4].spr, D_8011165C_messy_memory, D_8011165C_messy_memory);
            func_8000BB54_main(D_80111700_messy_memory[4].spr);
            func_8000BC48_main(D_80111700_messy_memory[4].spr, 0x4000);
            if (D_80111700_messy_memory[4].unk5C.x >= 0.23f || D_80111700_messy_memory[4].unk5C.y >= 0.23f) {
                D_80115D9A_messy_memory = 12;
            }
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010622C_messy_memory);
#endif

/* The title sign's sprites (D_80111700[4 + work[0]]): 0 the sign, 1 its overlay. */
void func_801063FC_messy_memory(omObjData *obj) {
    MmEnt *ent = &D_80111910_messy_memory[obj->work[0]];

    if (obj->work[0] == 0) {
        ent->pos.x = 160.0f;
        ent->pos.y = 120.0f;
        ent->grp = func_8000B838_main(0x3E0000);
        ent->spr = InitEspriteSlot(ent->grp, 0, 0);
        func_8000BC48_main(ent->spr, 0x4000);
        func_8000BBD4_main(ent->spr, ent->pos.x, ent->pos.y);
        func_8000BCC8_main(ent->spr, 0x5555);
    }
    if (obj->work[0] == 1) {
        ent->pos.x = 160.0f;
        ent->pos.y = 120.0f;
        ent->grp = func_8000B838_main(0x3E0001);
        ent->spr = InitEspriteSlot(ent->grp, 0, 0);
        func_8000BC48_main(ent->spr, 0x4000);
        func_8000BBD4_main(ent->spr, ent->pos.x, ent->pos.y);
        func_8000BCC8_main(ent->spr, 0xFFFF);
    }
    obj->func = func_8010622C_messy_memory;
}

void func_80106588_messy_memory(void) {
    omObjData *obj;
    MmEnt *ent;
    u8 i;

    for (i = 0; i < 2; i++) {
        ent = &D_80111910_messy_memory[i];
        obj = omAddObj(950, 0, 0, -1, func_801063FC_messy_memory);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

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

/* Draws the players' hand cursors (D_80111700[0..3]): open or holding (D_80111640), dimmed while blocked (D_80115D72). */
#ifdef NON_MATCHING
void func_80106800_messy_memory(Gfx **gfx, s32 arg1, s32 arg2) {
    MmEnt *ent;
    omObjData *o;
    Gfx *g;
    s32 lift;
    s32 i;
    f32 f;

    for (i = 0; i < 4; i++) {
        ent = &D_80111700_messy_memory[i];
        o = ent->obj;
        lift = 0;
        if (o->work[0] < 2) {
            f = ent->pos.y - 98.0f;
            if (f > 0.0f) {
                lift = f;
            }
        }
        lift = lift * ent->unk18;
        if (D_80111658_messy_memory[o->work[0]] != 0) {
            if (D_80115D72_messy_memory[o->work[0]] < 255) {
                gfx = func_801067D0_messy_memory(func_80106704_messy_memory(gfx), D_80115D72_messy_memory[o->work[0]]);
            } else {
                gfx = func_80106620_messy_memory(gfx);
            }
            g = *gfx;
            gDPSetTextureLUT(g++, G_TT_RGBA16);
            gDPLoadTLUT_pal16(g++, 0, D_80111660_messy_memory[o->work[0]]->unk0C);
            gDPSetTextureImage(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 16,
                               D_80111660_messy_memory[o->work[0]]->unk00[D_80111640_messy_memory[o->work[0]]].unk00);
            gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 2, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(g++);
            gDPLoadTile(g++, G_TX_LOADTILE, 0, 0, 16 * 4, (32 - lift) * 4);
            gDPPipeSync(g++);
            gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 32 * 4, (32 - lift) * 4);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 32 * 4, (32 - lift) * 4);
            gSPTextureRectangle(g++, (s32)(ent->pos.x - 8.0f + 16.0f - ent->unk18 * 16.0f) << 2,
                                (s32)(ent->pos.y - 8.0f + 16.0f - ent->unk18 * 16.0f) << 2,
                                (s32)(ent->pos.x - 8.0f + 16.0f + ent->unk18 * 16.0f) << 2,
                                (s32)(ent->pos.y - 8.0f + 16.0f + ent->unk18 * 16.0f - lift) << 2, G_TX_RENDERTILE, 0,
                                0, (s32)(1024.0f / ent->unk18), (s32)(1024.0f / ent->unk18));
            *gfx = g;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106800_messy_memory);
#endif

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
                                    D_801116B0_messy_memory[j * 10 + i] = 1;
                                    goto pickup;
                                }
                            } else {
                                if (MM_NEAR(item->pos.x, e->pos.x, 7.0f) &&
                                    MM_NEAR2(item->pos.y, e->pos.y, 7.0f, 6.0f)) {
                                    D_801116B0_messy_memory[j * 10 + i] = 1;
                                pickup:
                                    /* retail marks the picking player's hand (p), not the item's board (j) */
                                    D_80111640_messy_memory[obj->work[0]] = 1;
                                    func_8004AC98_main(D_80111338_messy_memory, (s16)obj->work[0]);
                                    D_80111670_messy_memory[p] = 1;
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
                                    D_801116B0_messy_memory[obj->work[0] * 10 + i] = 0;
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
                                    D_801116B0_messy_memory[obj->work[0] * 10 + i] = 0;
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
                            D_801116B0_messy_memory[p * 10 + e->unk08] = 0;
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

#ifdef NON_MATCHING
/* A CPU player's brain runs only while the items are put back (phase 9). */
void func_8010ACE4_messy_memory(omObjData *obj) {
    s32 p = (u16)obj->work[0];
    s32 d;

    if (D_80115D8C_messy_memory == 9) {
        d = GwPlayer[p].cpu_difficulty;
        if (d < 4 && d >= 0) {
            func_80107C88_messy_memory(obj);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010ACE4_messy_memory);
#endif

/* A player's hand object: grows in, a CPU decides how many items it remembers, then runs the brain or the pad. */
#ifdef NON_MATCHING
void func_8010AD40_messy_memory(omObjData *obj) {
    MmEnt *e;
    u16 p;
    s8 r;
    s8 cnt;
    s8 i;
    s8 k;
    s8 j;
    s8 flag;

    p = (u16)obj->work[0];
    e = &D_80111700_messy_memory[p];
    switch (D_80115D8C_messy_memory) {
    case 8:
        D_80111658_messy_memory[obj->work[0]] = 1;
        e->unk18 += 0.05;
        if (e->unk18 > 1.0f) {
            e->unk18 = 1.0f;
        }
        if ((GwPlayer[p].stat & 1) && e->unk16 == 0) {
            e->unk16 = 1;
            cnt = 0;
            r = rand8() % 100;
            if (GwPlayer[p].cpu_difficulty == 0) {
                if (r >= 1 && r < 30) {
                    e->unk04 = 0;
                }
                if (r >= 30 && r < 80) {
                    e->unk04 = 1;
                }
                if (r >= 80 && r < 90) {
                    e->unk04 = 2;
                }
                if (r >= 90 && r < 95) {
                    e->unk04 = 3;
                }
                if (r >= 95 && r < 98) {
                    e->unk04 = 4;
                }
                if (r >= 98 && r < 100) {
                    e->unk04 = 5;
                }
            }
            if (GwPlayer[p].cpu_difficulty == 1) {
                if (r >= 1 && r < 10) {
                    e->unk04 = 0;
                }
                if (r >= 10 && r < 40) {
                    e->unk04 = 1;
                }
                if (r >= 40 && r < 65) {
                    e->unk04 = 2;
                }
                if (r >= 65 && r < 85) {
                    e->unk04 = 3;
                }
                if (r >= 85 && r < 95) {
                    e->unk04 = 4;
                }
                if (r >= 95 && r < 100) {
                    e->unk04 = 5;
                }
            }
            if (GwPlayer[p].cpu_difficulty == 2) {
                if (r >= 0 && r < 10) {
                    e->unk04 = 1;
                }
                if (r >= 10 && r < 30) {
                    e->unk04 = 2;
                }
                if (r >= 30 && r < 55) {
                    e->unk04 = 3;
                }
                if (r >= 55 && r < 80) {
                    e->unk04 = 4;
                }
                if (r >= 80 && r < 95) {
                    e->unk04 = 5;
                }
                if (r >= 95 && r < 100) {
                    e->unk04 = 7;
                }
            }
            if (GwPlayer[p].cpu_difficulty == 3) {
                if (r >= 1 && r < 5) {
                    e->unk04 = 2;
                }
                if (r >= 5 && r < 15) {
                    e->unk04 = 3;
                }
                if (r >= 15 && r < 30) {
                    e->unk04 = 4;
                }
                if (r >= 30 && r < 80) {
                    e->unk04 = 5;
                }
                if (r >= 80 && r < 100) {
                    e->unk04 = 7;
                }
            }
            /* every item shown in its own slot is known */
            for (j = 0; j < 10; j++) {
                for (i = 0; i < 10; i++) {
                    if (D_801116E0_messy_memory[i] == j) {
                        D_80111678_messy_memory[p][D_801116E0_messy_memory[i]] = 1;
                    }
                }
            }
            /* then up to unk04 more, from the last item down, that were not shown */
            for (k = 9; k >= 0; k--) {
                flag = 0;
                if (cnt >= e->unk04) {
                    break;
                }
                for (i = 0; i < 10; i++) {
                    if (D_801116E0_messy_memory[i] == k) {
                        flag = 1;
                    }
                }
                if (flag == 0 && D_80111678_messy_memory[p][k] != 1) {
                    D_80111678_messy_memory[p][k] = 1;
                    cnt++;
                }
            }
        }
        break;
    case 9:
        if (D_80115D8E_messy_memory > 0) {
            if (GwPlayer[p].stat & 1) {
                func_8010ACE4_messy_memory(obj);
            } else {
                func_80106C60_messy_memory(obj);
            }
        }
        break;
    case 11:
        e->unk18 -= 0.03;
        if (e->unk18 <= 0.05f) {
            e->unk18 = 0.05f;
            D_80111658_messy_memory[obj->work[0]] = 0;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010AD40_messy_memory);
#endif

/* A player's hand: its sprite group by character, placed on its board; player 3's also adds the hand drawer. */
#ifdef NON_MATCHING
void func_8010B32C_messy_memory(omObjData *obj) {
    MmEnt *e;
    u8 chr;
    s16 i;

    chr = GwPlayer[obj->work[0]].chr;
    e = &D_80111700_messy_memory[obj->work[0]];
    e->grp = func_8000B838_main(D_801111EC_messy_memory[chr][0]);
    D_80111660_messy_memory[obj->work[0]] = func_80055194_main(e->grp);
    for (i = 0; i < 4; i++) {
        if (obj->work[0] == i) {
            e->pos.x = (f32)D_80110FE0_messy_memory[obj->work[0]].x + 88.0f;
            e->pos.y = (f32)D_80110FE0_messy_memory[obj->work[0]].y + 63.0f;
        }
    }
    e->unk18 = 0.1f;
    e->unk5C.x = e->unk5C.y = 0.1f;
    D_80115D72_messy_memory[obj->work[0]] = 255;
    D_80111658_messy_memory[obj->work[0]] = 0;
    if (obj->work[0] == 3) {
        func_8001C8A8_main(func_8001AC8C_main(0, func_80106800_messy_memory, 2), 1);
    }
    obj->func = func_8010AD40_messy_memory;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010B32C_messy_memory);
#endif

#ifdef NON_MATCHING
void func_8010B4CC_messy_memory(void) {
    omObjData *obj;
    MmEnt *ent;
    s32 unused[2];
    u32 kind = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            kind = 0;
            break;
        case 1:
            kind = 1;
            break;
        case 2:
            kind = 2;
            break;
        case 3:
            kind = 3;
            break;
        }
        ent = &D_80111700_messy_memory[i];
        obj = omAddObj(150, 4, 1, -1, func_8010B32C_messy_memory);
        obj->work[0] = kind;
        ent->obj = obj;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010B4CC_messy_memory);
#endif

/* A player's model object (work[0] the player; D_80113B18[player] its state), per game phase. */
#ifdef NON_MATCHING
void func_8010B5C8_messy_memory(omObjData *obj) {
    MmEnt *ent;
    MmEnt *q;
    f32 f;
    u16 p;
    s16 i;
    s16 flag;
    s32 a;
    s32 b;

    p = (u16)obj->work[0];
    ent = &D_80113B18_messy_memory[obj->work[0]];
    switch (D_80115D8C_messy_memory) {
    case 5:
        func_8001C258_main(obj->model[0], 4, 0);
        func_8001C258_main(obj->model[1], 4, 0);
        break;
    case 6:
        func_8001C258_main(obj->model[0], 4, 0);
        switch (ent->unk04) {
        case 0:
            func_8001C5B4_main(obj->model[0], obj->motion[2]);
            ent->unk04 = 1;
            break;
        case 1:
            if (p == 0 || p == 2) {
                obj->rot.y = func_801059BC_messy_memory(obj->rot.y, 20.0f);
            } else {
                obj->rot.y = func_801059BC_messy_memory(obj->rot.y, -20.0f);
            }
            if ((s16)obj->rot.y == 180) {
                ent->unk04 = 2;
                obj->rot.y = 180.0f;
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
            }
            break;
        case 2:
            if (++ent->unk08 >= 5) {
                ent->unk04 = 3;
                func_8001C5B4_main(obj->model[0], obj->motion[5]);
                func_8004ACE0_main(0x286, (s16)obj->work[0]);
            }
            break;
        case 3:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
                ent->unk04 = 4;
                func_8001C5B4_main(obj->model[0], obj->motion[2]);
                func_8001C814_main(obj->model[0], 2, 2);
            }
            break;
        case 4:
            if (p == 0 || p == 2) {
                obj->rot.y = func_801059BC_messy_memory(obj->rot.y, 15.0f);
            } else {
                obj->rot.y = func_801059BC_messy_memory(obj->rot.y, -15.0f);
            }
            if ((s16)obj->rot.y == 90 || (s16)obj->rot.y == 270) {
                ent->unk04 = 5;
            }
            break;
        case 5:
            obj->trans.x -= D_80111298_messy_memory[p].x;
            if (obj->work[0] == 3) {
                flag = 0;
                for (i = 0; i < 4; i++) {
                    q = &D_80113B18_messy_memory[i];
                    a = q->obj->trans.x;
                    if (a < 0) {
                        a = -a;
                    }
                    if (a < 651) {
                        flag = 1;
                    }
                }
                if (flag == 0) {
                    D_80115D9A_messy_memory = 6;
                    for (i = 0; i < 4; i++) {
                        q = &D_80113B18_messy_memory[i];
                        func_8001C258_main(q->obj->model[0], 4, 4);
                    }
                }
            }
            break;
        }
        break;
    case 13:
        switch (p) {
        case 0:
            obj->trans.x = -650.0f;
            obj->trans.y = -180.0f;
            obj->trans.z = -1000.0f;
            obj->rot.y = 90.0f;
            break;
        case 1:
            obj->trans.x = 650.0f;
            obj->trans.y = -180.0f;
            obj->trans.z = -1000.0f;
            obj->rot.y = 270.0f;
            break;
        case 2:
            obj->trans.x = -650.0f;
            obj->trans.y = -435.0f;
            obj->trans.z = -610.0f;
            obj->rot.y = 90.0f;
            break;
        case 3:
            obj->trans.x = 650.0f;
            obj->trans.y = -435.0f;
            obj->trans.z = -610.0f;
            obj->rot.y = 270.0f;
            break;
        }
        obj->rot.x = 0.0f;
        obj->rot.z = 0.0f;
        Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
        ent->unk04 = 0;
        break;
    case 14:
        func_8001C258_main(obj->model[0], 4, 0);
        switch (ent->unk04) {
        case 0:
            obj->trans.x += D_80111298_messy_memory[p].x;
            if (ent->unk06 >= 8) {
                if (D_80115D84_messy_memory[obj->work[0]] != -1) {
                    HuAudFXStop(D_80115D84_messy_memory[obj->work[0]]);
                }
                D_80115D84_messy_memory[obj->work[0]] = func_8004ACE0_main(D_8011133C_messy_memory, (s16)obj->work[0]);
                ent->unk06 = 0;
            } else {
                ent->unk06++;
            }
            a = obj->trans.x;
            if (a < 0) {
                a = -a;
            }
            f = D_80111298_messy_memory[p].y;
            b = f;
            if (b < 0) {
                b = -b;
            }
            if (b >= a) {
                obj->trans.x = f;
                ent->unk04 = 1;
                func_8001C5B4_main(obj->model[0], obj->motion[1]);
            }
            break;
        case 1:
            if (obj->rot.y >= 270.0f) {
                obj->rot.y = func_801059BC_messy_memory(obj->rot.y, 15.0f);
            } else if (obj->rot.y <= 90.0f) {
                obj->rot.y = func_801059BC_messy_memory(obj->rot.y, -15.0f);
            }
            if ((s16)obj->rot.y == 0) {
                ent->unk04 = 2;
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                if (p == 3) {
                    D_80115D9A_messy_memory = 14;
                }
            }
            break;
        }
        break;
    case 16:
        if (D_80115D8E_messy_memory >= 0 && ent->unk04 == 2) {
            if (D_8011163B_messy_memory == 0) {
                if (p == D_80111630_messy_memory[0]) {
                    MM_WIN(obj);
                } else {
                    func_8001C5B4_main(obj->model[0], obj->motion[4]);
                }
            }
            if (D_8011163B_messy_memory == 1) {
                if (p == D_80111630_messy_memory[0] || p == D_80111630_messy_memory[1]) {
                    MM_WIN(obj);
                } else {
                    func_8001C5B4_main(obj->model[0], obj->motion[4]);
                }
            }
            if (D_8011163B_messy_memory == 2) {
                if (p == D_80111630_messy_memory[0] || p == D_80111630_messy_memory[1] || p == D_80111630_messy_memory[2]) {
                    MM_WIN(obj);
                } else {
                    func_8001C5B4_main(obj->model[0], obj->motion[4]);
                }
            }
            if (D_8011163B_messy_memory == 3) {
                MM_WIN(obj);
            }
            if (D_8011163B_messy_memory == 4) {
                func_8001C5B4_main(obj->model[0], obj->motion[4]);
            }
            ent->unk04 = 3;
        }
        break;
    }
    if (GwPlayer[obj->work[0]].chr != 5) {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 5.0f, obj->trans.z);
    } else {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 10.0f, obj->trans.z + 30.0f);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010B5C8_messy_memory);
#endif

/* A player's model: character model, shadow, motions, start position. */
#ifdef NON_MATCHING
void func_8010C03C_messy_memory(omObjData *obj) {
    s8 chr = GwPlayer[obj->work[0]].chr;
    u16 p = (u16)obj->work[0];

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][1], 0x2A9);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    obj->model[1] = func_8000B0A0_main(0, 0x14C9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(HmfModelData[obj->model[1]].mtx, 0.0f, 15.0f, 0.0f);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 2));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x7A));
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C6A8_main(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 2, 2);
    switch (p) {
    case 0:
    case 1:
        obj->trans.x = D_80111298_messy_memory[p].y;
        obj->trans.y = -180.0f;
        obj->trans.z = -1000.0f;
        break;
    case 2:
    case 3:
        obj->trans.x = D_80111298_messy_memory[p].y;
        obj->trans.y = -435.0f;
        obj->trans.z = -610.0f;
        break;
    }
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    obj->func = func_8010B5C8_messy_memory;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010C03C_messy_memory);
#endif

#ifdef NON_MATCHING
void func_8010C37C_messy_memory(void) {
    omObjData *obj;
    MmEnt *ent;
    s32 unused[2];
    u32 kind = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            kind = 0;
            break;
        case 1:
            kind = 1;
            break;
        case 2:
            kind = 2;
            break;
        case 3:
            kind = 3;
            break;
        }
        ent = &D_80113B18_messy_memory[i];
        obj = omAddObj(850, 9, 60, -1, func_8010C03C_messy_memory);
        obj->work[0] = kind;
        ent->obj = obj;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010C37C_messy_memory);
#endif

/* An item's object (work[0] the item, work[1] its board: 0-3 a player's, 4 the shown room), per game phase. */
#ifdef NON_MATCHING
void func_8010C478_messy_memory(omObjData *obj) {
    MmEnt *e;
    MmEnt *it;
    MmEnt *sh;
    omObjData *iobj;
    u8 i;
    u8 k;
    u8 hit;
    s32 a;
    s32 b;
    s32 x0;
    u32 idx;
    f32 px;

    e = MM_ITEM(obj->work[1], obj->work[0]);
    switch (D_80115D8C_messy_memory) {
    case 2:
        D_80111674_messy_memory = 7;
        break;
    case 3:
        if (obj->work[1] == 4 && D_80115D90_messy_memory[obj->work[0]] == 10) {
            if (D_80111638_messy_memory < D_80111674_messy_memory) {
                k = rand8() % 10;
                if (k != D_80115D90_messy_memory[0] && k != D_80115D90_messy_memory[1] &&
                    k != D_80115D90_messy_memory[2] && k != D_80115D90_messy_memory[3] &&
                    k != D_80115D90_messy_memory[4] && k != D_80115D90_messy_memory[5] &&
                    k != D_80115D90_messy_memory[6] && k != D_80115D90_messy_memory[7] &&
                    k != D_80115D90_messy_memory[8] && k != D_80115D90_messy_memory[9]) {
                    D_80115D90_messy_memory[obj->work[0]] = k;
                    D_80111638_messy_memory++;
                    for (i = 0; i < 10; i++) {
                        if (k == i) {
                            e->pos.x = D_80110FF4_messy_memory[k + 10].x;
                            e->pos.y = D_80110FF4_messy_memory[k + 10].y;
                        }
                    }
                }
            }
        }
        if (D_80111638_messy_memory >= D_80111674_messy_memory) {
            if (obj->work[1] == 4) {
                func_8000BCC8_main(e->spr, 0x1111);
                func_8000BBD4_main(e->spr, e->pos.x, e->pos.y);
            }
            for (i = 0; i < 10; i++) {
                it = &D_80112FC0_messy_memory[i];
                iobj = it->obj;
                for (k = 0; k < 20; k++) {
                    if (it->pos.x == D_80110FF4_messy_memory[k].x && it->pos.y == D_80110FF4_messy_memory[k].y) {
                        D_801116E0_messy_memory[k] = iobj->work[0];
                    }
                }
            }
        }
        break;
    case 4:
        if (obj->work[1] == 4) {
            func_8000BC88_main(e->spr, 0x4000);
        }
        if (obj->work[1] < 4) {
            for (i = 0; i < 20; i++) {
                if (D_801116E0_messy_memory[i] == obj->work[0]) {
                    e->pos.x = MM_SLOTX(obj->work[1], i);
                    e->pos.y = MM_SLOTY(obj->work[1], i);
                    func_8000BBD4_main(e->spr, e->pos.x, e->pos.y);
                    func_8000BE5C_main(e->spr, e->unk5C.x, e->unk5C.y);
                    if (i < 15) {
                        func_8000BCC8_main(e->spr, 0xDDDD);
                    } else {
                        func_8000BCC8_main(e->spr, 0xBBBB);
                    }
                }
            }
            if (obj->work[1] * 10 + obj->work[0] == 39) {
                D_80115D9A_messy_memory = 4;
            }
        }
        break;
    case 5:
        if (obj->work[1] == 4) {
            idx = obj->work[0] + 48;
            it = &D_80111700_messy_memory[idx];
            for (i = 0; i < 20; i++) {
                if (it->pos.x == D_80110FF4_messy_memory[i].x && it->pos.y == D_80110FF4_messy_memory[i].y) {
                    D_80115D20_messy_memory[obj->work[0]].x = 2.0f * D_801110A4_messy_memory[i].x;
                    D_80115D20_messy_memory[obj->work[0]].y = 2.0f * D_801110A4_messy_memory[i].y;
                }
            }
            it->pos.x += D_80115D20_messy_memory[obj->work[0]].x;
            it->pos.y += D_80115D20_messy_memory[obj->work[0]].y;
            func_8000BBD4_main(it->spr, it->pos.x, it->pos.y);
            it->unk5C.x = it->unk5C.y = D_8011165C_messy_memory;
            func_8000BE5C_main(it->spr, it->unk5C.x, it->unk5C.y);
            if (it->unk5C.x <= 0.01 || it->unk5C.y <= 0.01) {
                func_8000BB94_main(it->spr);
                for (i = 0; i < 10; i++) {
                    if (obj->work[0] == D_801116A4_messy_memory[i]) {
                        it->pos.x = D_80110FF4_messy_memory[i].x;
                        it->pos.y = D_80110FF4_messy_memory[i].y;
                    }
                }
                for (i = 0; i < 20; i++) {
                    if (it->pos.x == D_80110FF4_messy_memory[i].x && it->pos.y == D_80110FF4_messy_memory[i].y) {
                        D_80115D20_messy_memory[obj->work[0]].x = -D_801110A4_messy_memory[i].x;
                        D_80115D20_messy_memory[obj->work[0]].y = -D_801110A4_messy_memory[i].y;
                        it->pos.x = 160.0f;
                        it->pos.y = 120.0f;
                    }
                }
            }
        }
        break;
    case 9:
        if (obj->work[1] < 4) {
            switch (D_801116B0_messy_memory[obj->work[1] * 10 + obj->work[0]]) {
            case 0:
                func_8000BCC8_main(e->spr, 0xDDDD);
                /* retail reads slot 20, one past D_80111044 (the first point of D_80111094) */
                for (i = 15; i < 21; i++) {
                    if (e->pos.x == MM_SLOTX(obj->work[1], i) && e->pos.y == MM_SLOTY(obj->work[1], i)) {
                        func_8000BCC8_main(e->spr, 0xBBBB);
                    }
                }
                break;
            case 1:
                it = &D_80111700_messy_memory[obj->work[1]];
                e->pos.x = it->pos.x;
                e->pos.y = it->pos.y;
                func_8000BCC8_main(e->spr, 0xAAAA);
                break;
            }
            func_8000BBD4_main(e->spr, e->pos.x, e->pos.y);
            func_8000BE5C_main(e->spr, e->unk5C.x, e->unk5C.y);
        }
        break;
    case 10:
        if (obj->work[1] < 4) {
            hit = 0;
            if (D_801116B0_messy_memory[obj->work[1] * 10 + obj->work[0]] == 1) {
                sh = &D_80111700_messy_memory[obj->work[1] * 10 + 86 + obj->work[0]];
                if ((f32)D_80110FE0_messy_memory[obj->work[1]].y + 93.0f <= e->pos.y) {
                    for (k = 1; k < 4; k++) {
                        x0 = D_80110FE0_messy_memory[obj->work[1]].x;
                        px = e->pos.x;
                        a = (f32)(x0 + D_80111094_messy_memory[e->unk06].x) - px;
                        if (a < 0) {
                            a = -a;
                        }
                        b = (f32)(x0 + D_80111094_messy_memory[k].x) - px;
                        if (b < 0) {
                            b = -b;
                        }
                        if (b < a) {
                            e->unk06 = k;
                        }
                    }
                    e->pos.x = (f32)(D_80110FE0_messy_memory[obj->work[1]].x + D_80111094_messy_memory[e->unk06].x);
                    e->pos.y = (f32)(D_80110FE0_messy_memory[obj->work[1]].y + D_80111094_messy_memory[e->unk06].y);
                    func_8000BCC8_main(sh->spr, 0xABBB);
                }
                if (e->pos.y < (f32)D_80110FE0_messy_memory[obj->work[1]].y + 93.0f) {
                    if (e->pos.x <= (f32)D_80110FE0_messy_memory[obj->work[1]].x + 80.0f && e->unk08 == 0) {
                        e->unk18 = 2.0f;
                        e->unk08 = 1;
                    }
                    if ((f32)D_80110FE0_messy_memory[obj->work[1]].x + 80.0f < e->pos.x && e->unk08 == 0) {
                        e->unk18 = -2.0f;
                        e->unk08 = 1;
                    }
                    e->unk1C += 0.5f;
                    e->pos.x += e->unk18;
                    e->pos.y += e->unk1C;
                    func_8000BCC8_main(e->spr, 0xCDDD);
                    func_8000BCC8_main(sh->spr, 0xCDEE);
                }
                if ((f32)D_80110FE0_messy_memory[obj->work[1]].y + 93.0f <= e->pos.y) {
                    D_801116B0_messy_memory[obj->work[1] * 10 + obj->work[0]] = 0;
                    func_8000BB54_main(sh->spr);
                    func_8000BBD4_main(sh->spr, e->pos.x, e->pos.y + 1.0f);
                }
            }
            for (i = 0; i < 40; i++) {
                if (D_801116B0_messy_memory[i] == 1) {
                    hit = 1;
                }
            }
            if (!hit) {
                D_80115D9A_messy_memory = 10;
            }
            func_8000BBD4_main(e->spr, e->pos.x, e->pos.y);
        }
        break;
    case 11:
        if (obj->work[1] == 4) {
            e->pos.x = 160.0f;
            e->pos.y = 120.0f;
        }
        break;
    case 12:
        if (obj->work[1] == 4) {
            idx = obj->work[0] + 48;
            it = &D_80111700_messy_memory[idx];
            it->pos.x += D_80115D20_messy_memory[obj->work[0]].x;
            it->pos.y += D_80115D20_messy_memory[obj->work[0]].y;
            func_8000BBD4_main(it->spr, it->pos.x, it->pos.y);
            it->unk5C.x = it->unk5C.y = D_8011165C_messy_memory;
            func_8000BE5C_main(it->spr, it->unk5C.x, it->unk5C.y);
            func_8000BB54_main(it->spr);
        }
        break;
    case 13:
        if (obj->work[1] < 4) {
            if (e->pos.y < (f32)D_80110FE0_messy_memory[obj->work[1]].y + 80.0f) {
                func_8000BCC8_main(e->spr, 0xDDDD);
                if (D_801116A4_messy_memory[D_8011163A_messy_memory] == obj->work[0]) {
                    for (i = 0; i < 10; i++) {
                        if (e->pos.x == MM_SLOTX(obj->work[1], i) && e->pos.y == MM_SLOTY(obj->work[1], i)) {
                            D_801116E0_messy_memory[i] = obj->work[0];
                            if (D_801116A4_messy_memory[i] == D_801116E0_messy_memory[i]) {
                                func_8000BCC8_main(e->spr, 0x1111);
                                if (e->unk04 == 0) {
                                    D_80115D76_messy_memory[obj->work[1]]++;
                                    e->unk04 = 1;
                                }
                                e->unk5C.x = e->unk5C.y = D_801116A0_messy_memory;
                                func_8000BE5C_main(e->spr, e->unk5C.x, e->unk5C.y);
                            }
                        }
                    }
                }
            }
        }
        if (obj->work[1] == 4) {
            func_8000BCC8_main(e->spr, 0x3333);
            if (D_801116A4_messy_memory[D_8011163A_messy_memory] == obj->work[0]) {
                func_8000BCC8_main(e->spr, 0x1111);
                e->unk5C.x = e->unk5C.y = D_8011165C_messy_memory;
                func_8000BE5C_main(e->spr, e->unk5C.x, e->unk5C.y);
            }
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010C478_messy_memory);
#endif

#ifdef NON_MATCHING
/* Item k of a board (work[1] board, work[0] item): load its image, place it in its slot (the shuffled room: a free
   random slot), then run func_8010C478. */
void func_8010D55C_messy_memory(omObjData *obj) {
    MmEnt *e;
    s16 i;
    u8 v;
    u32 k;

    e = &D_80111700_messy_memory[obj->work[1] * 10 + 8 + obj->work[0]];
    if (obj->work[1] == 0) {
        for (i = 0; i < 10; i++) {
            k = obj->work[0];
            if (k == i) {
                D_80111608_messy_memory[k] = func_8000B838_main((&D_80111148_messy_memory[k][0])[1]);
            }
        }
    }
    if (obj->work[1] < 4) {
        for (i = 0; i < 11; i++) {
            if (i == obj->work[0]) {
                e->spr = InitEspriteSlot((s16)D_80111608_messy_memory[i], 0, 0);
            }
        }
    } else {
        for (i = 0; i < 10; i++) {
            k = obj->work[0];
            if (k == i) {
                e->grp = func_8000B838_main(D_80111198_messy_memory[k][1]);
                e->spr = InitEspriteSlot(e->grp, 0, 0);
            }
        }
    }
    if (obj->work[1] == 4) {
        v = rand8() % 10;
    retry:
        if (v != D_80115D90_messy_memory[0] && v != D_80115D90_messy_memory[1] && v != D_80115D90_messy_memory[2] &&
            v != D_80115D90_messy_memory[3] && v != D_80115D90_messy_memory[4] && v != D_80115D90_messy_memory[5] &&
            v != D_80115D90_messy_memory[6] && v != D_80115D90_messy_memory[7] && v != D_80115D90_messy_memory[8]) {
            D_80115D90_messy_memory[obj->work[0]] = v;
        } else {
            v++;
            if (v >= 10) {
                v = 0;
            }
            goto retry;
        }
        for (i = 0; i < 10; i++) {
            if (v == i) {
                e->pos.x = D_80110FF4_messy_memory[v].x;
                e->pos.y = D_80110FF4_messy_memory[v].y;
                D_801116A4_messy_memory[v] = obj->work[0];
            }
        }
    }
    e->unk5C.x = 1.0f;
    e->unk5C.y = 1.0f;
    func_8000BC48_main(e->spr, 0x5008);
    func_8000BBD4_main(e->spr, e->pos.x, e->pos.y);
    func_8000BE5C_main(e->spr, e->unk5C.x, e->unk5C.y);
    func_8000BCC8_main(e->spr, 0xDDDD);
    if (obj->work[1] == 4) {
        func_8000BCC8_main(e->spr, 0x3333);
    }
    obj->func = func_8010C478_messy_memory;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010D55C_messy_memory);
#endif

#ifdef NON_MATCHING
/* Creates the item objects: ten per board (four players and the shown room), work[0] item, work[1] board. */
void func_8010D910_messy_memory(void) {
    omObjData *o;
    MmEnt *e;
    s16 b;
    s16 j;
    s16 i;

    for (b = 0; b < 5; b++) {
        for (j = 0; j < 10; j++) {
            e = &D_80111700_messy_memory[j + (b * 10 + 8)];
            o = omAddObj(300, 0, 0, -1, func_8010D55C_messy_memory);
            for (i = 0; i < 10; i++) {
                if ((s16)(j % 10) == i) {
                    o->work[0] = j;
                }
            }
            e->obj = o;
            o->work[1] = b;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010D910_messy_memory);
#endif

/* Snaps the shadow to its item when the item sits on a slot (tbl/origin: the slot table and board origin). */
#define MM_SHADOW_SNAP(tbl, n, yoff, twice, a, b)                                                                      \
    for (i = 0; i < n; i++) {                                                                                          \
        if (it->pos.x == (f32)(tbl[i].x + D_80110FE0_messy_memory[obj->work[1]].x) &&                                  \
            it->pos.y == (f32)(tbl[i].y + D_80110FE0_messy_memory[obj->work[1]].y)) {                                  \
            sh->pos.x = it->pos.x;                                                                                     \
            sh->pos.y = it->pos.y;                                                                                     \
            func_8000BB54_main(sh->spr);                                                                               \
            func_8000BBD4_main(sh->spr, sh->pos.x, sh->pos.y + yoff);                                                  \
            if (twice) {                                                                                               \
                func_8000BB54_main(sh->spr);                                                                           \
            }                                                                                                          \
            if (i < 15) {                                                                                              \
                func_8000BCC8_main(sh->spr, a);                                                                        \
            } else {                                                                                                   \
                func_8000BCC8_main(sh->spr, b);                                                                        \
            }                                                                                                          \
        }                                                                                                              \
    }

#ifdef NON_MATCHING
/* An item's shadow object (work[0] the item, work[1] its board). Retail's slot loops read one past their table. */
void func_8010DA64_messy_memory(omObjData *obj) {
    MmEnt *sh;
    MmEnt *it;
    s16 i;
    u32 t;

    t = obj->work[1] * 10;
    sh = &D_80111700_messy_memory[t + 86 + obj->work[0]];
    it = &D_80111700_messy_memory[t + 8 + obj->work[0]];
    switch (D_80115D8C_messy_memory) {
    case 3:
        if (obj->work[1] == 4) {
            MM_SHADOW_SNAP(D_80110FF4_messy_memory, 21, 2.0f, 0, 0x4444, 0x2222);
        }
        break;
    case 4:
        if (obj->work[1] == 4) {
            func_8000BC88_main(sh->spr, 0x4000);
        }
        break;
    case 5:
        if (obj->work[1] == 4) {
            for (i = 0; i < 20; i++) {
                if (it->pos.x == D_80110FF4_messy_memory[i].x && it->pos.y == D_80110FF4_messy_memory[i].y) {
                    D_80115D20_messy_memory[obj->work[0]].x = 2.0f * D_801110A4_messy_memory[i].x;
                    D_80115D20_messy_memory[obj->work[0]].y = 2.0f * D_801110A4_messy_memory[i].y;
                }
            }
            sh->pos.x += D_80115D20_messy_memory[obj->work[0]].x;
            sh->pos.y += D_80115D20_messy_memory[obj->work[0]].y;
            func_8000BBD4_main(sh->spr, sh->pos.x, sh->pos.y + 2.0f);
            sh->unk5C.x = sh->unk5C.y = D_8011165C_messy_memory;
            func_8000BE5C_main(sh->spr, sh->unk5C.x, sh->unk5C.y);
            if (sh->unk5C.x <= 0.01 || sh->unk5C.y <= 0.01) {
                func_8000BB94_main(sh->spr);
            }
        }
        if (obj->work[1] < 4) {
            MM_SHADOW_SNAP(D_80111044_messy_memory, 21, 1.0f, 1, 0xEEEE, 0xCCCC);
        }
        break;
    case 8:
        if (obj->work[1] < 4) {
            MM_SHADOW_SNAP(D_80111044_messy_memory, 21, 1.0f, 1, 0xEEEE, 0xCCCC);
        }
        break;
    case 9:
    case 10:
    case 11:
        if (obj->work[1] < 4) {
            MM_SHADOW_SNAP(D_80111044_messy_memory, 21, 1.0f, 0, 0xEEEE, 0xCCCC);
            if (D_801116B0_messy_memory[obj->work[1] * 10 + obj->work[0]] == 1) {
                func_8000BB94_main(sh->spr);
            }
        }
        break;
    case 12:
        if (obj->work[1] < 4) {
            func_8000BCC8_main(sh->spr, 0xEEEE);
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010DA64_messy_memory);
#endif

/* An item's shadow (D_80111700[48 + board * 10 + item]): shown under items of the shown room that sit on a slot. */
#ifdef NON_MATCHING
/* An item's shadow (D_80111700[86 + board * 10 + item]): shown under items of the shown room that sit on a slot. */
void func_8010E29C_messy_memory(omObjData *obj) {
    MmEnt *sh;
    MmEnt *it;
    s16 i;

    sh = &D_80111700_messy_memory[obj->work[1] * 10 + 86 + obj->work[0]];
    it = &D_80111700_messy_memory[obj->work[1] * 10 + 8 + obj->work[0]];
    if (obj->work[0] == 0 && obj->work[1] == 0) {
        D_80111634_messy_memory = func_8000B838_main(0x3E0003);
    }
    sh->spr = InitEspriteSlot((s16)D_80111634_messy_memory, 0, 0);
    if (obj->work[1] == 4) {
        sh->unk5C.x = 1.0f;
        sh->unk5C.y = 1.0f;
    } else {
        sh->unk5C.x = 0.5f;
        sh->unk5C.y = 0.5f;
    }
    func_8000BB94_main(sh->spr);
    func_8000BCC8_main(sh->spr, 0xEEEE);
    if (obj->work[1] == 4) {
        /* i reaches 20: D_80110FF4[20] is D_80111044[0] */
        for (i = 0; i < 21; i++) {
            if (it->pos.x == (f32)(D_80110FF4_messy_memory[i].x + D_80110FE0_messy_memory[obj->work[1]].x) &&
                it->pos.y == (f32)(D_80110FF4_messy_memory[i].y + D_80110FE0_messy_memory[obj->work[1]].y)) {
                sh->pos.x = it->pos.x;
                sh->pos.y = it->pos.y;
                func_8000BCC8_main(sh->spr, 0x4444);
                func_8000BB54_main(sh->spr);
                func_8000BBD4_main(sh->spr, sh->pos.x, sh->pos.y + 2.0f);
            }
        }
    }
    func_8000BC48_main(sh->spr, 0x5000);
    func_8000BE5C_main(sh->spr, sh->unk5C.x, sh->unk5C.y);
    obj->func = func_8010DA64_messy_memory;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010E29C_messy_memory);
#endif

#ifdef NON_MATCHING
/* Creates the item shadow objects: ten per board, work[0] item, work[1] board. */
void func_8010E500_messy_memory(void) {
    omObjData *o;
    MmEnt *e;
    s16 b;
    s16 j;
    s16 i;

    for (b = 0; b < 5; b++) {
        for (j = 0; j < 10; j++) {
            e = &D_80111700_messy_memory[j + (b * 10 + 86)];
            o = omAddObj(400, 0, 0, -1, func_8010E29C_messy_memory);
            for (i = 0; i < 10; i++) {
                if ((s16)(j % 10) == i) {
                    o->work[0] = j;
                }
            }
            e->obj = o;
            o->work[1] = b;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010E500_messy_memory);
#endif

/* One of the seven intro movers (D_801134E8[work[0]]; models from the first one's motions): walks in along
   D_80111228, turns, walks back out. */
void func_8010E654_messy_memory(omObjData *obj) {
    MmEnt *e;
    omObjData *o0;

    e = &D_801134E8_messy_memory[obj->work[0]];
    o0 = D_801134E8_messy_memory[0].obj;
    switch (D_80115D8C_messy_memory) {
    case 1:
        if (obj->work[0] == 0) {
            if (e->unk06 == 48) {
                HuAudFXPlay(0x3F0);
                func_8004AAD0_main(HuAudFXPlay(0x298), 0x73);
                HuAudSeqPlay(0x4F);
            }
            if (e->unk06 < 50) {
                e->unk06++;
            }
        }
        break;
    case 2:
    case 3:
        switch (obj->work[1]) {
        case 0:
            obj->trans.z += D_80111228_messy_memory[obj->work[0]].dz;
            obj->trans.x += D_80111228_messy_memory[obj->work[0]].dx;
            if (obj->trans.z <= D_80111228_messy_memory[obj->work[0]].z) {
                obj->work[1] = 1;
                D_80111650_messy_memory = 1;
                if ((obj->work[0] == 4) | (obj->work[0] == 6)) {
                    func_8001C5B4_main(obj->model[0], o0->motion[3]);
                } else {
                    func_8001C5B4_main(obj->model[0], o0->motion[4]);
                    if (HmfModelData[obj->model[0]].unk40 == 0.0f) {
                        func_8004AAD0_main(HuAudFXPlay(0x3EE), 0x73);
                    }
                }
                func_8001C814_main(obj->model[0], 2, 2);
                func_8001C6A8_main(obj->model[0], 0.0f);
            }
            break;
        case 1:
            if ((obj->work[0] != 4) & (obj->work[0] != 6)) {
                if (HmfModelData[obj->model[0]].unk40 == 0.0f) {
                    func_8004AAD0_main(HuAudFXPlay(0x3EE), 0x73);
                }
            }
            e->unk04++;
            if (D_80115D8C_messy_memory == 2) {
                if (obj->work[0] == D_80115D8C_messy_memory && e->unk04 == 5) {
                    D_80111675_messy_memory = 1;
                }
                if (D_80115D8C_messy_memory == 2 && obj->work[0] == 6 && e->unk04 == 10) {
                    D_80115D9A_messy_memory = 2;
                }
            }
            if (obj->work[0] < 4) {
                if (e->unk04 >= 70) {
                    e->unk04 = 0;
                    obj->work[1] = 2;
                }
            }
            if (obj->work[0] >= 4) {
                if (e->unk04 >= 20) {
                    e->unk04 = 0;
                    obj->work[1] = 2;
                    if (obj->work[0] == 4) {
                        HuAudFXPlay(0x3F2);
                    }
                }
            }
            break;
        case 2:
            obj->rot.y = func_801059BC_messy_memory(obj->rot.y, 180.0f);
            func_8001C5B4_main(obj->model[0], o0->motion[2]);
            func_8001C814_main(obj->model[0], 2, 2);
            func_8001C6A8_main(obj->model[0], 0.0f);
            if (obj->work[0] == 2) {
                D_80111675_messy_memory = 2;
                func_8004AAD0_main(HuAudFXPlay(0x298), 0x73);
            }
            obj->work[1] = 3;
            break;
        case 3:
            obj->trans.z -= D_80111228_messy_memory[obj->work[0]].dz;
            obj->trans.x -= D_80111228_messy_memory[obj->work[0]].dx;
            if (obj->trans.z >= 170.0f) {
                obj->work[1] = 4;
                if (obj->work[0] == 3) {
                    D_80115D9A_messy_memory = 3;
                }
            }
            if (obj->work[0] == 3 && obj->trans.z == -50.0f) {
                func_8004AAD0_main(HuAudFXPlay(0x29B), 0x73);
            }
            break;
        case 4:
            func_8001C258_main(obj->model[0], 4, 4);
            break;
        }
        Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
        break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z + 0.0f);
}

#ifdef NON_MATCHING
/* Sets up intro mover work[0]: the first loads the model and its motions, the others link to it; a shadow model. */
void func_8010EBB0_messy_memory(omObjData *obj) {
    omObjData *o0;
    u8 i;

    o0 = D_801134E8_messy_memory[0].obj;
    if (obj->work[0] == 0) {
        obj->model[0] = func_8000B108_main(0xA0000, 0xB9);
        D_8011163C_messy_memory = obj->model[0];
        func_8000B460_main(obj, 0, 0xA0001);
        func_8000B460_main(obj, 1, 0xA0002);
        func_8000B460_main(obj, 2, 0xA0006);
        func_8000B460_main(obj, 3, 0xA0007);
        func_8000B460_main(obj, 4, 0xA0009);
    } else {
        obj->model[0] = Hu3DModelLink((s16)D_8011163C_messy_memory);
    }
    obj->model[1] = func_8000B0A0_main(0, 0xA9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(HmfModelData[obj->model[1]].mtx, 0.0f, 15.0f, 0.0f);
    func_8001C5B4_main(obj->model[0], o0->motion[2]);
    func_8001C814_main(obj->model[0], 2, 2);
    func_8001C6A8_main(obj->model[0], 0.0f);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    for (i = 0; i < 7; i++) {
        if (i == obj->work[0]) {
            obj->trans.z = i * 80 + 120.0f;
        }
    }
    obj->rot.x = 0.0f;
    obj->rot.y = D_80111228_messy_memory[obj->work[0]].roty;
    obj->rot.z = 0.0f;
    obj->scale.x = 0.8f;
    obj->scale.y = 0.8f;
    obj->scale.z = 0.8f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    obj->func = func_8010E654_messy_memory;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010EBB0_messy_memory);
#endif

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

/* The intro spotlight (D_80113A94[work[0]]): fades in while the movers walk in (D_80111675 1), out after (2). */
void func_8010EF10_messy_memory(omObjData *obj) {
    MmEnt *e;

    e = &D_80113A94_messy_memory[obj->work[0]];
    switch (D_80115D8C_messy_memory) {
    case 2:
    case 3:
        if (D_80111675_messy_memory == 1) {
            if (D_80115D70_messy_memory == 0) {
                HuAudFXPlay(0x3E9);
                D_80115D70_messy_memory = 1;
                HuAudFXPlay(0x127);
            }
            func_8001C258_main(obj->model[0], 4, 0);
            func_8001F9E4_main(obj->model[0], e->unk06);
            e->unk06 += 20;
            if (e->unk06 >= 255) {
                e->unk06 = 255;
            }
        }
        if (D_80111675_messy_memory == 2) {
            func_8001F9E4_main(obj->model[0], e->unk06);
            e->unk06 -= 10;
            if (e->unk06 <= 0) {
                e->unk06 = 0;
                func_8001C258_main(obj->model[0], 4, 4);
                D_80111650_messy_memory = 0;
            }
        }
        break;
    }
}

/* Sets up the intro spotlight model. */
void func_8010F04C_messy_memory(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x3E001C, 0xA9);
    func_8001C814_main(obj->model[0], 2, 2);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 100);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    obj->scale.x = 1.0f;
    obj->scale.y = 1.0f;
    obj->scale.z = 1.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    func_8001C8A8_main(obj->model[0], 2);
    obj->func = func_8010EF10_messy_memory;
}

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

/* The minigame's phase controller (D_80115D8C the phase, D_80115D8E its timer). */
#ifdef NON_MATCHING
void func_8010FDF0_messy_memory(omObjData *obj) {
    u8 chr[4];
    u8 i;
    u8 j;

    switch (D_80115D8C_messy_memory) {
    case 0:
        if (D_80115D8E_messy_memory > 0) {
            D_80115D8E_messy_memory--;
        }
        if (D_80115D8E_messy_memory < 91) {
            GMesCreate(26, D_80115D8E_messy_memory / 30, 160, 28);
            D_80115D8E_messy_memory = 91;
            func_80105B7C_messy_memory(1);
        }
        break;
    case 1:
        if (D_80115D8E_messy_memory > 0) {
            if (--D_80115D8E_messy_memory == 88) {
                HuAudFXPlay(8);
            }
            func_8003F578_main((D_80115D8E_messy_memory + 29) / 30);
        } else {
            func_8003F5C0_main();
            D_80115D8E_messy_memory = 0;
            func_80105B7C_messy_memory(2);
        }
        break;
    case 2:
        if (D_80115D9A_messy_memory == 2) {
            for (i = 0; i < 10; i++) {
                D_80115D90_messy_memory[i] = 10;
            }
            func_80105B7C_messy_memory(3);
        }
        break;
    case 3:
        if (D_80115D9A_messy_memory == 3) {
            func_80105B7C_messy_memory(4);
        }
        break;
    case 4:
        if (D_80115D9A_messy_memory == 4) {
            func_80105B7C_messy_memory(5);
        }
        break;
    case 5:
        D_8011165C_messy_memory -= 0.02f;
        if (D_80115D9A_messy_memory == 5) {
            func_80105B7C_messy_memory(6);
        }
        break;
    case 6:
        if (D_80115D9A_messy_memory == 6) {
            func_80105B7C_messy_memory(8);
            D_80115D8E_messy_memory = 0;
        }
        break;
    case 7:
        if (--D_80115D8E_messy_memory <= 0) {
            func_80105B7C_messy_memory(8);
            D_80115D8E_messy_memory = 0;
        }
        break;
    case 8:
        if (D_80115D8E_messy_memory == 0) {
            GMesCreate(3);
            D_80115D8E_messy_memory++;
        } else if (D_80115D8E_messy_memory >= 43) {
            HuAudSeqPlay(49);
        } else {
            D_80115D8E_messy_memory++;
        }
        if (GMesStatGet() == 0) {
            func_80105B7C_messy_memory(9);
            GMesCreate(26, 30, 160, 28);
            D_80115D8E_messy_memory = 901;
        }
        break;
    case 9:
        if (D_80115D8E_messy_memory > 0) {
            D_80115D8E_messy_memory--;
            func_8003F578_main((D_80115D8E_messy_memory + 29) / 30);
        } else {
            func_8003F5C0_main();
            func_80105B7C_messy_memory(10);
            D_8011165C_messy_memory = 0.01f;
            GMesCreate(14);
            HuAudSeqFadeOut(120);
        }
        break;
    case 10:
        if (D_80115D9A_messy_memory == 10 && GMesStatGet() == 0) {
            func_80105B7C_messy_memory(11);
        }
        break;
    case 11:
        if (D_80115D9A_messy_memory == 11) {
            func_80105B7C_messy_memory(12);
        }
        break;
    case 12:
        D_8011165C_messy_memory += 0.01f;
        if (D_80115D9A_messy_memory == 12) {
            func_80105B7C_messy_memory(13);
        }
        break;
    case 13:
        if (D_80111639_messy_memory == 0) {
            if (D_801116A0_messy_memory == 1.0f) {
                HuAudFXPlay(1007);
            }
            D_8011165C_messy_memory += 0.1f;
            if ((D_801116A0_messy_memory += 0.05f) >= 1.5f) {
                D_80111639_messy_memory = 1;
            }
        }
        if (D_80111639_messy_memory == 1) {
            D_8011165C_messy_memory -= 0.1f;
            if ((D_801116A0_messy_memory -= 0.05f) <= 1.0f) {
                D_801116A0_messy_memory = 1.0f;
                D_8011163A_messy_memory++;
                D_80111639_messy_memory = 0;
                if (D_8011163A_messy_memory >= 10) {
                    for (i = 0; i < 4; i++) {
                        D_80111630_messy_memory[i] = i;
                    }
                    for (i = 0; i < 4; i++) {
                        for (j = 0; j < 3; j++) {
                            if (D_80115D76_messy_memory[D_80111630_messy_memory[j]] <
                                D_80115D76_messy_memory[D_80111630_messy_memory[j + 1]]) {
                                D_80111630_messy_memory[j] ^= D_80111630_messy_memory[j + 1];
                                D_80111630_messy_memory[j + 1] ^= D_80111630_messy_memory[j];
                                D_80111630_messy_memory[j] ^= D_80111630_messy_memory[j + 1];
                            }
                        }
                    }
                    for (i = 0; i < 3; i++) {
                        if (D_80115D76_messy_memory[D_80111630_messy_memory[0]] ==
                            D_80115D76_messy_memory[D_80111630_messy_memory[i + 1]]) {
                            D_8011163B_messy_memory++;
                        }
                    }
                    if (D_80115D76_messy_memory[D_80111630_messy_memory[0]] < 4) {
                        D_8011163B_messy_memory = 4;
                    }
                    D_80115D8E_messy_memory = 30;
                    func_80105B7C_messy_memory(14);
                }
            }
        }
        break;
    case 14:
        if ((D_80115D7C_messy_memory += 0.05f) >= 1.0f) {
            D_80115D7C_messy_memory = 1.0f;
        }
        if (D_80115D9A_messy_memory == 14) {
            func_80105B7C_messy_memory(15);
        }
        break;
    case 15:
        if (--D_80115D8E_messy_memory < 0) {
            D_80115D7C_messy_memory -= 0.045f;
        }
        if (D_80115D9A_messy_memory == 15) {
            func_80105B7C_messy_memory(16);
            D_80115D8E_messy_memory = -15;
        }
        break;
    case 16:
        if (GMesStatGet() == 0 && D_80115D8E_messy_memory == 0) {
            D_80115D8E_messy_memory = 1;
            switch (D_8011163B_messy_memory) {
            case 0:
                chr[0] = GwPlayer[D_80111630_messy_memory[0]].chr;
                GwPlayer[D_80111630_messy_memory[0]].bonusCoin = 10;
                GMesCreate(22, chr[0]);
                HuAudSeqPlay(101);
                break;
            case 1:
                for (i = 0; i < 2; i++) {
                    chr[i] = GwPlayer[D_80111630_messy_memory[i]].chr;
                    GwPlayer[D_80111630_messy_memory[i]].bonusCoin = 10;
                }
                GMesCreate(30, chr[0], chr[1], 10);
                HuAudSeqPlay(102);
                break;
            case 2:
                for (i = 0; i < 3; i++) {
                    chr[i] = GwPlayer[D_80111630_messy_memory[i]].chr;
                    GwPlayer[D_80111630_messy_memory[i]].bonusCoin = 10;
                }
                GMesCreate(34, chr[0], chr[1], chr[2]);
                HuAudSeqPlay(102);
                break;
            case 3:
                for (i = 0; i < 4; i++) {
                    chr[i] = GwPlayer[D_80111630_messy_memory[i]].chr;
                    GwPlayer[D_80111630_messy_memory[i]].bonusCoin = 10;
                }
                GMesCreate(35, chr[0], chr[1], chr[2], chr[3]);
                HuAudSeqPlay(102);
                break;
            case 4:
                GMesCreate(32);
                HuAudSeqPlay(108);
                break;
            }
        }
        if (D_80115D8E_messy_memory > 0) {
            if (GMesStatGet() == 0) {
                func_80105B7C_messy_memory(17);
                D_80115D8E_messy_memory = 15;
            }
        } else if (D_80115D8E_messy_memory < 0) {
            D_80115D8E_messy_memory++;
        }
        break;
    case 17:
        if (D_80115D8E_messy_memory > 0) {
            D_80115D8E_messy_memory--;
        } else {
            WipeCreateOut(0, 20);
            obj->func = func_8010FD60_messy_memory;
        }
        break;
    }
    if ((s16)D_80111650_messy_memory > 0) {
        if ((s16)D_80111650_messy_memory % 5 == 1) {
            for (i = 0; i < 4; i++) {
                if (!(GwPlayer[i].stat & 1)) {
                    omVibrate(i, 2, 3, 10);
                }
            }
        }
        D_80111650_messy_memory++;
    }
    if ((s16)D_80111650_messy_memory >= 30001) {
        D_80111650_messy_memory = 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_8010FDF0_messy_memory);
#endif

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

