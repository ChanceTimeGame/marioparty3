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

/* .data */
extern MmCamera D_80111340_messy_memory[2];

/* .bss */
extern MmEnt D_80111700_messy_memory[136];
extern MmEnt D_801134E8_messy_memory[]; /* = D_80111700_messy_memory[58] */
extern MmEnt D_80113884_messy_memory[]; /* = D_80111700_messy_memory[65] */
extern MmEnt D_80113A94_messy_memory[]; /* = D_80111700_messy_memory[69] */
extern s8 D_80115D8C_messy_memory;

/* .rodata */
const s16 D_801115F4_messy_memory[];

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80106C60_messy_memory);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1D_messy_memory/1E37C0", func_80107C88_messy_memory);

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

