#include "common.h"
// m3 cc: Coconut Conk (1 vs 3: the solo player catches coconuts the others drop)
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

/* One slot of the overlay's object table (D_8010B1F0_coconut_conk, 50 x 0x84). */
typedef struct CcEnt {
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
} CcEnt; // Size 0x84

#define CC_ENT_GROUND 0
#define CC_ENT_SKY 1
#define CC_ENT_SEA 3
#define CC_ENT_WATER 4
#define CC_ENT_CLOUD 5
#define CC_ENT_TREE 6     /* 6 */
#define CC_ENT_NUT 12     /* 9 */
#define CC_ENT_SOLO 21
#define CC_ENT_PLAYER 22  /* 3 */

/* The ground object's data (func_80105C60_coconut_conk). */
typedef struct CcGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ char unk08[0xAC];
} CcGround; // Size 0xB4

/* A texture's size (func_800335BC_main). */
typedef struct CcTexSize {
    /* 0x00 */ s16 w;
    /* 0x02 */ s16 h;
} CcTexSize;

void func_8000BC48_main(u16, s32);
omObjData *func_80045ED0_main(u32 arg0);
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_800335BC_main(char *arg0, void *arg1);
void func_8004AE00_main(s16 handle, s16 pan);
s32 func_8000B710_main(s32 arg0);
void func_800E6F0C_minigame(s8 arg0);
void func_800DDD94_minigame(omObjData *obj);
void func_800E149C_minigame(omObjData *obj, u8 idx, u8 val);
void func_800E5978_minigame(omObjData *obj, u16 idx, s32 file, u16 flags, u16 speed);
void func_80105B04_coconut_conk(s32 player);
void func_80105B7C_coconut_conk(s8 arg0);
void func_8003F578_main(s16);
void func_8003F5C0_main(void);
extern s32 D_800EBE24_minigame;
void osViBlack(u8 active);
extern u16 D_800D530C_main;
f32 fabsf(f32);
f64 fabs(f64);
void func_8001C624_main(s16, s16, s16, s16, s16);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
s16 func_8004AC98_main(s16, s16);
void func_800E1304_minigame(omObjData *obj, f32 arg1);
void func_800E1310_minigame(omObjData *obj, f32 arg1);
void func_800E131C_minigame(omObjData *obj, f32 arg1);
void func_800E139C_minigame(omObjData *obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E4C88_minigame(omObjData *obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
extern s32 D_800A178C_main[][6];
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u8 D_800D6A90_main;
extern f32 D_800EB73C_minigame;
extern D_800CCF58_main_Struct *D_800CCF58_main;

/* A camera (D_8010B018_coconut_conk). */
typedef struct CcCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} CcCamera; // Size 0x2C

/* The minigame control block (minigame B8A20.c MgCtrl; the header's D_80111B50_vine_with_me_Struct). */
typedef struct CcCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
} CcCtrl; // Size 0x28

/* .data */
extern char D_8010B070_coconut_conk[];
extern char D_8010B07C_coconut_conk[];
extern char D_8010B088_coconut_conk[];
extern char D_8010B094_coconut_conk[];
extern char D_8010B0A0_coconut_conk[];
extern char D_8010B0AC_coconut_conk[];
extern char D_8010B0B8_coconut_conk[];
extern char D_8010B0C4_coconut_conk[];

/* sound effects: the solo player's barrel, a coconut landing, a coconut caught, the barrel rolling */
s16 D_8010AF60_coconut_conk = 0xC1;
s16 D_8010AF62_coconut_conk = 0x310;
s16 D_8010AF64_coconut_conk = 0x312;
s16 D_8010AF66_coconut_conk = 0x311;
/* Per character: the solo player's three animation files (0 start, 1 jump out, 2 catch). */
u16 D_8010AF68_coconut_conk[8][3] = {
    { 0xA4, 0xA5, 0xA8 }, { 0xA4, 0xA5, 0xA9 }, { 0xA4, 0xA5, 0xA9 }, { 0xA4, 0xA5, 0xA8 },
    { 0xA4, 0xA5, 0xA8 }, { 0xA4, 0xA5, 0xA8 }, { 0xA4, 0xA5, 0xA9 }, { 0x1A, 0x1C, 0x25 },
};
/* Per character: the model's animation target name. */
char *D_8010AF98_coconut_conk[8] = {
    D_8010B0C4_coconut_conk, D_8010B0B8_coconut_conk, D_8010B0AC_coconut_conk, D_8010B0A0_coconut_conk,
    D_8010B094_coconut_conk, D_8010B088_coconut_conk, D_8010B07C_coconut_conk, D_8010B070_coconut_conk,
};
/* palm tree x positions */
f32 D_8010AFB8_coconut_conk[6] = { -425.0f, -255.0f, -85.0f, 85.0f, 255.0f, 425.0f };
/* voice sound bank per character (func_80045ED0_main) */
s32 D_8010AFD0_coconut_conk[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
CcCtrl D_8010AFF0_coconut_conk = {
    0, 0, 1, 2, 0, 0, 0, 0, { 90.0f, 900.0f, 0.0f, 30.0f }, { 0x96, 0, 0, 0 }, 0, 0, 0, 0, 0, 0,
};
CcCamera D_8010B018_coconut_conk[2] = {
    { { 0.0f, 0.0f, 320.0f, 240.0f }, { 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f }, 43.0f },
    { { 0.0f, 0.0f, 320.0f, 240.0f }, { 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f }, 43.0f },
};
char D_8010B070_coconut_conk[] = "c301l_0_DEF";
char D_8010B07C_coconut_conk[] = "c300l_0_DEF";
char D_8010B088_coconut_conk[] = "c005l_0_DEF";
char D_8010B094_coconut_conk[] = "c004l_0_DEF";
char D_8010B0A0_coconut_conk[] = "c003l_0_DEF";
char D_8010B0AC_coconut_conk[] = "c002l_0_DEF";
char D_8010B0B8_coconut_conk[] = "c001l_0_DEF";
char D_8010B0C4_coconut_conk[] = "c000l_0_DEF";
char D_8010B0D0_coconut_conk[] = "mp_202_edt-umi_1";
char D_8010B0E4_coconut_conk[] = "suimen_DEF";
/* .bss */
extern s16 D_8010B1C0_coconut_conk;
extern s16 D_8010B1C2_coconut_conk;
extern s8 D_8010B1C3_coconut_conk;     /* the low byte of D_8010B1C2_coconut_conk */
extern u8 D_8010B1C8_coconut_conk;
extern u8 D_8010B1C9_coconut_conk[3];
extern u8 D_8010B1CC_coconut_conk;
extern HuSprite_Unk84_Struct *D_8010B1C4_coconut_conk;
extern void *D_8010B1D0_coconut_conk[3];
extern s16 D_8010B1DC_coconut_conk;
extern u8 D_8010B1DE_coconut_conk;
extern s16 D_8010B1E0_coconut_conk;
extern CcTexSize D_8010B1E2_coconut_conk;
extern s16 D_8010B1E6_coconut_conk;
extern CcEnt D_8010B1F0_coconut_conk[50];
extern CcEnt D_8010B274_coconut_conk;    /* = D_8010B274_coconut_conk */
extern CcEnt D_8010B37C_coconut_conk;    /* = D_8010B37C_coconut_conk */
extern CcEnt D_8010B400_coconut_conk;    /* = D_8010B400_coconut_conk */
extern f32 D_8010B418_coconut_conk;     /* = D_8010B400_coconut_conk.unk18 */
extern CcEnt D_8010B484_coconut_conk;    /* = D_8010B484_coconut_conk */
extern f32 D_8010B4A0_coconut_conk;     /* = D_8010B484_coconut_conk.unk1C */
extern f32 D_8010B4A4_coconut_conk;     /* = D_8010B484_coconut_conk.unk20 */
extern CcEnt D_8010B508_coconut_conk[6]; /* = D_8010B1F0_coconut_conk[CC_ENT_TREE] */
extern CcEnt D_8010B820_coconut_conk[9]; /* = D_8010B1F0_coconut_conk[CC_ENT_NUT] */
/* = D_8010B1F0_coconut_conk[CC_ENT_SOLO]: [0] the solo player, [1..3] the team (D_8010BD48_coconut_conk) */
extern CcEnt D_8010BCC4_coconut_conk[4];
extern s16 D_8010BCC8_coconut_conk;     /* = D_8010BCC4_coconut_conk[0].unk04 */
extern s16 D_8010CBB8_coconut_conk;
extern u8 D_8010CBBA_coconut_conk;
extern u8 D_8010CBBB_coconut_conk;
extern s16 D_8010CBBC_coconut_conk;
extern u8 D_8010CBBE_coconut_conk;
extern s16 D_8010CBC0_coconut_conk;
/* .rodata */
extern const s16 D_8010B1B8_coconut_conk[];

f32 func_801059BC_coconut_conk(f32 angle, f32 add);
void func_80105C58_coconut_conk(omObjData *obj);
void func_80105C60_coconut_conk(omObjData *obj);
void func_80105D98_coconut_conk(Gfx **gfx, s32 arg1, s32 arg2);
void func_801060C0_coconut_conk(omObjData *obj);
void func_801060C8_coconut_conk(omObjData *obj);
void func_801061EC_coconut_conk(omObjData *obj);
void func_801061F4_coconut_conk(omObjData *obj);
void func_801062D4_coconut_conk(omObjData *obj);
void func_80106394_coconut_conk(omObjData *obj);
void func_80106468_coconut_conk(omObjData *obj);
void func_8010659C_coconut_conk(omObjData *obj);
void func_801066E4_coconut_conk(omObjData *obj);
void func_801067E0_coconut_conk(omObjData *obj);
void func_801069BC_coconut_conk(omObjData *obj);
void func_80106D40_coconut_conk(omObjData *obj);
void func_80106D5C_coconut_conk(omObjData *obj);
void func_80106F18_coconut_conk(omObjData *obj);
void func_80107674_coconut_conk(omObjData *obj);
void func_80107690_coconut_conk(omObjData *obj);
void func_801076EC_coconut_conk(omObjData *obj);
void func_801078BC_coconut_conk(omObjData *obj);
void func_80107B8C_coconut_conk(omObjData *obj);
void func_8010815C_coconut_conk(omObjData *obj);
void func_801090C4_coconut_conk(omObjData *obj);
void func_801095A4_coconut_conk(omObjData *obj);
void func_801095C0_coconut_conk(omObjData *obj);
void func_801095C8_coconut_conk(omObjData *obj);
void func_80109940_coconut_conk(omObjData *obj);
void func_80109DEC_coconut_conk(omObjData *obj);
void func_8010A55C_coconut_conk(omObjData *obj);
void func_8010A5D8_coconut_conk(omObjData *obj);
void func_8010A610_coconut_conk(omObjData *obj);
void func_8010A668_coconut_conk(omObjData *obj);
void func_8010AB4C_coconut_conk(omObjData *obj);
void func_8010AC88_coconut_conk(omObjData *obj);
void func_8010AE04_coconut_conk(void);
void func_80105D58_coconut_conk(void);
void func_801061AC_coconut_conk(void);
void func_80106294_coconut_conk(void);
void func_8010641C_coconut_conk(void);
void func_801066A4_coconut_conk(void);
void func_80106924_coconut_conk(void);
void func_80106E80_coconut_conk(void);
void func_80108FA0_coconut_conk(void);
void func_8010A344_coconut_conk(void);
void func_8010A4AC_coconut_conk(void);
void func_8010AB4C_coconut_conk(omObjData *obj);
void func_8010AC90_coconut_conk(void);

void func_801059A0_coconut_conk(void) {
    func_8010AE04_coconut_conk();
}

f32 func_801059BC_coconut_conk(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

void func_80105A3C_coconut_conk(void) {
    CcEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010B1F0_coconut_conk; i < 50; i++, ent++) {
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

/* Clears a player's pad input (the CPU writes its own). */
void func_80105B04_coconut_conk(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105B7C_coconut_conk(s8 arg0) {
    D_8010B1C8_coconut_conk = arg0;
}

f32 func_80105B88_coconut_conk(f32 pos, f32 *vel, f32 accel) {
    f32 v = *vel;

    *vel = v - accel;
    return pos + v;
}

void func_80105BA4_coconut_conk(omObjData *obj, u8 anim) {
    u8 chr = GwPlayer[obj->work[0]].chr;

    func_80033354_main(D_8010B1DC_coconut_conk);
    D_8010B1DC_coconut_conk = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010B1D0_coconut_conk[anim], 0, D_8010AF98_coconut_conk[chr]);
}

void func_80105C58_coconut_conk(omObjData *obj) {
}

void func_80105C60_coconut_conk(omObjData *obj) {
    CcGround *gw;

    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
    obj->data = gw = HuMemAllocTag(sizeof(CcGround), 31000);
    memset(gw, 0, sizeof(CcGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    gw->unk06 &= ~0x200;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E139C_minigame(D_800EC1C0_minigame[0], 512.0f, -1000.0f, -285.0f, 1000.0f, -165.0f);
    obj->func = func_80105C58_coconut_conk;
}

void func_80105D58_coconut_conk(void) {
    omObjData *obj = omAddObj(1000, 1, 10, -1, func_80105C60_coconut_conk);

    obj->work[0] = 0;
    D_8010B1F0_coconut_conk[CC_ENT_GROUND].obj = obj;
}

/* Draws the sky backdrop: a 320-wide CI8 image, four rows at a time. */
void func_80105D98_coconut_conk(Gfx **gfx, s32 arg1, s32 arg2) {
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
    gDPLoadTLUT_pal256(g++, D_8010B1C4_coconut_conk->unk0C);
    x = 0;
    for (i = 0, y = 128; i < 112; i += 4) {
        gDPSetTextureImage(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 320, D_8010B1C4_coconut_conk->unk08);
        gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 41, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
        gDPLoadSync(g++);
        gDPLoadTile(g++, G_TX_LOADTILE, 0, i * 4, 320 * 4, (i + 4) * 4);
        gDPPipeSync(g++);
        gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 41, 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0);
        gDPSetTileSize(g++, G_TX_RENDERTILE, 0, i * 4, 320 * 4, (i + 4) * 4);
        gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 320 * 4, 4 * 4);
        gSPTextureRectangle(g++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 4) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }
    *gfx = g;
}

void func_801060C0_coconut_conk(omObjData *obj) {
}

/* The sky sprite and the backdrop display list. */
void func_801060C8_coconut_conk(omObjData *obj) {
    CcEnt *ent = &D_8010B274_coconut_conk;

    ent->grp = func_8000B838_main(0x23000D);
    ent->spr = InitEspriteSlot(ent->grp, 0, 0);
    func_8000BC48_main(ent->spr, 0x4000);
    ent->pos.x = 160.0f;
    ent->pos.y = 67.0f;
    func_8000BBD4_main(ent->spr, 160, 67);
    D_8010B1C4_coconut_conk = func_80055194_main(func_8000B838_main(0x23000E));
    func_8001C8A8_main(func_8001AC8C_main(0, func_80105D98_coconut_conk, 2), 1);
    obj->func = func_801060C0_coconut_conk;
}

void func_801061AC_coconut_conk(void) {
    omObjData *obj = omAddObj(900, 1, 10, -1, func_801060C8_coconut_conk);

    obj->work[0] = 0;
    D_8010B274_coconut_conk.obj = obj;
}

void func_801061EC_coconut_conk(omObjData *obj) {
}

void func_801061F4_coconut_conk(omObjData *obj) {
    CcEnt *ent = &D_8010B37C_coconut_conk;

    ent->grp = func_8000B838_main(0x23000F);
    ent->spr = InitEspriteSlot(ent->grp, 0, 0);
    func_8000BC48_main(ent->spr, 0);
    ent->pos.x = 160.0f;
    ent->pos.y = 219.0f;
    func_8000BBD4_main(ent->spr, 160, 219);
    obj->func = func_801061EC_coconut_conk;
}

void func_80106294_coconut_conk(void) {
    omObjData *obj = omAddObj(950, 1, 10, -1, func_801061F4_coconut_conk);

    obj->work[0] = 0;
    D_8010B37C_coconut_conk.obj = obj;
}

/* Scrolls the water texture. */
void func_801062D4_coconut_conk(omObjData *obj) {
    CcEnt *ent = &D_8010B400_coconut_conk;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010B418_coconut_conk += 0.2f;
    }
    func_8001E888_main(obj->model[0], 0, ent->unk18, D_8010B1E2_coconut_conk.w,
                       D_8010B1E2_coconut_conk.h, D_8010B0D0_coconut_conk, 0);
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
}

void func_80106394_coconut_conk(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x230004, 0x289);
    func_8001C954_main(obj->model[0]);
    func_800335BC_main(D_8010B0E4_coconut_conk, &D_8010B1E2_coconut_conk);
    D_8010B418_coconut_conk = 0;
    obj->trans.x = 0;
    obj->trans.y = 0;
    obj->trans.z = 0;
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_801062D4_coconut_conk;
}

void func_8010641C_coconut_conk(void) {
    omObjData *obj = omAddObj(860, 1, 0, -1, func_80106394_coconut_conk);

    obj->work[0] = 0;
    D_8010B400_coconut_conk.obj = obj;
    omSetStatBit(obj, 0xA0);
}

/* Two clouds that pulse in size against each other. */
void func_80106468_coconut_conk(omObjData *obj) {
    CcEnt *ent = &D_8010B484_coconut_conk;

    switch (ent->unk04) {
        case 0:
            ent->unk1C += 0.005f;
            ent->unk20 -= 0.005f;
            if (ent->unk1C > 1.1f) {
                ent->unk04 = 1;
            }
            break;
        case 1:
            ent->unk1C -= 0.005f;
            ent->unk20 += 0.005f;
            if (ent->unk1C < 1.0f) {
                ent->unk04 = 0;
            }
            break;
    }
    obj->scale.x = obj->scale.y = obj->scale.z = ent->unk1C;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[1], ent->unk20, ent->unk20, ent->unk20);
}

void func_8010659C_coconut_conk(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x230005, 0x289);
    obj->model[1] = func_8000B108_main(0x230005, 0x289);
    obj->trans.x = -400.0f;
    obj->trans.y = 700.0f;
    obj->trans.z = -1000.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], 450.0f, 750.0f, -1000.0f);
    D_8010B4A0_coconut_conk = 1.0f;
    D_8010B4A4_coconut_conk = 1.0f;
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    obj->func = func_80106468_coconut_conk;
}

void func_801066A4_coconut_conk(void) {
    omObjData *obj = omAddObj(870, 5, 10, -1, func_8010659C_coconut_conk);

    obj->work[0] = 0;
    D_8010B484_coconut_conk.obj = obj;
}

/* A palm tree: shakes (unk04 1) until its motion ends. */
void func_801066E4_coconut_conk(omObjData *obj) {
    CcEnt *ent = &D_8010B508_coconut_conk[obj->work[0]];

    switch (ent->unk04) {
        case 0:
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C92C_main(obj->model[0], 0.0f);
            break;
        case 1:
            func_8001C92C_main(obj->model[0], 1.0f);
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 == HmfModelData[obj->model[0]].unk40) {
                ent->unk04 = 0;
            }
            break;
    }
}

void func_801067E0_coconut_conk(omObjData *obj) {
    if (obj->work[0] == obj->work[0] / 3 * 3) {
        obj->model[0] = func_8000B108_main(0x230001, 0x299);
    }
    if (obj->work[0] / 3 * 3 == obj->work[0] - 1) {
        obj->model[0] = func_8000B108_main(0x230003, 0x299);
    }
    if (obj->work[0] / 3 * 3 == obj->work[0] - 2) {
        obj->model[0] = func_8000B108_main(0x23000C, 0x299);
    }
    obj->trans.x = D_8010AFB8_coconut_conk[obj->work[0]];
    obj->trans.y = 0.0f;
    obj->trans.z = -225.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 2);
    obj->func = func_801066E4_coconut_conk;
}

void func_80106924_coconut_conk(void) {
    omObjData *obj;
    CcEnt *ent;
    s32 i;

    for (i = 0; (u8)i < 6; i++) {
        ent = &D_8010B508_coconut_conk[(u8)i];
        obj = omAddObj(850, 1, 10, -1, func_801067E0_coconut_conk);
        obj->work[0] = (u8)i;
        ent->obj = obj;
    }
}

/* A coconut: 1 shakes loose, 2 falls, 3 lands, 4 is caught. */
void func_801069BC_coconut_conk(omObjData *obj) {
    CcEnt *ent = &D_8010B820_coconut_conk[obj->work[0]];
    s16 se;
    s16 pan;

    switch (ent->unk04) {
        case 0:
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C92C_main(obj->model[0], 0.0f);
            func_8001C258_main(obj->model[0], 4, 4);
            break;
        case 1:
            func_8001C258_main(obj->model[0], 4, 0);
            obj->trans.y = 422.0f - (f32)(++ent->unk06 & 1) * 10.0f;
            if (ent->unk06 > 0) {
                ent->unk04 = 2;
                ent->unk06 = 0;
                obj->trans.y = 422.0f;
            }
            break;
        case 2:
            obj->trans.y -= ent->unk18;
            ent->unk18 += 1.5f;
            obj->trans.z += 4.0f;
            if (obj->trans.y < 0.0f) {
                obj->trans.y = 0.0f;
                ent->unk04 = 3;
                ent->unk18 = 0.0f;
                func_800E4C88_minigame(obj, 1, obj->trans.x, obj->trans.y, obj->trans.z, 0.0f, 0.0f);
            }
            break;
        case 3:
            if (ent->unk06 == 0) {
                func_8001C92C_main(obj->model[0], 2.0f);
                se = HuAudFXPlay(D_8010AF62_coconut_conk);
                pan = (obj->trans.x + 390.0f) * 0.165f;
                if (pan < 0) {
                    pan = 0;
                } else if (pan >= 128) {
                    pan = 127;
                }
                func_8004AE00_main(se, pan);
            }
            if ((++ent->unk06 & 3) < 3) {
                func_8001C258_main(obj->model[0], 4, 0);
            } else {
                func_8001C258_main(obj->model[0], 4, 4);
            }
            if (ent->unk06 >= 16) {
                D_8010B1DE_coconut_conk--;
                ent->unk04 = 0;
                ent->unk06 = 0;
                obj->trans.z = -200.0f;
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C92C_main(obj->model[0], 0.0f);
            }
            break;
        case 4:
            if (ent->unk06 == 0) {
                func_8001C92C_main(obj->model[0], 2.0f);
                se = HuAudFXPlay(D_8010AF64_coconut_conk);
                pan = (obj->trans.x + 390.0f) * 0.165f;
                if (pan < 0) {
                    pan = 0;
                } else if (pan >= 128) {
                    pan = 127;
                }
            }
            if ((++ent->unk06 & 3) < 3) {
                func_8001C258_main(obj->model[0], 4, 0);
            } else {
                func_8001C258_main(obj->model[0], 4, 4);
            }
            if (ent->unk06 >= 16) {
                D_8010B1DE_coconut_conk--;
                ent->unk04 = 0;
                ent->unk06 = 0;
                obj->trans.z = -200.0f;
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C92C_main(obj->model[0], 0.0f);
            }
            break;
    }
}

void func_80106D40_coconut_conk(omObjData *obj) {
    func_801069BC_coconut_conk(obj);
}

void func_80106D5C_coconut_conk(omObjData *obj) {
    if (obj->work[0] < 3) {
        obj->model[0] = func_8000B108_main(0x23000B, 0x289);
    }
    if (obj->work[0] - 3 < 3) {
        obj->model[0] = func_8000B108_main(0x23000A, 0x289);
    }
    if (obj->work[0] >= 6) {
        obj->model[0] = func_8000B108_main(0x230002, 0x289);
    }
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -200.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->model[1] = func_8000B108_main(7, 0x2AD);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    obj->func = func_80106D40_coconut_conk;
}

void func_80106E80_coconut_conk(void) {
    omObjData *obj;
    CcEnt *ent;
    s32 i;

    for (i = 0; (u8)i < 9; i++) {
        ent = &D_8010B820_coconut_conk[(u8)i];
        obj = omAddObj(800, 5, 10, -1, func_80106D5C_coconut_conk);
        obj->work[0] = (u8)i;
        ent->obj = obj;
    }
}

/* The solo player's CPU: picks a direction (D_8010BCC4_coconut_conk[0].unk04: 1 left, 2 right). */
#ifdef NON_MATCHING
/* Differs from retail only in register allocation and the sort loops' index initialisation. */
void func_80106F18_coconut_conk(omObjData *obj) {
    CcEnt *solo = &D_8010BCC4_coconut_conk[0];
    f32 gap[4];
    f32 pos[3];
    u16 player = obj->work[0];
    f32 target = 0.0f;
    u8 dir = rand8();
    u8 diff = GwPlayer[player].cpu_difficulty;
    u8 near = 0;
    u8 lo;
    u8 mid;
    u8 hi;
    u8 best;
    s16 j;
    s16 i;
    CcEnt *ent;
    omObjData *o;

    if (((diff == 0) & (dir < 50)) || ((diff == 1) & (dir < 150)) || ((diff == 2) & (dir < 180)) || ((diff == 3) & (dir < 255))) {
        for (i = 0; i < 3; i++) {
            ent = &D_8010BCC4_coconut_conk[i + 1];
            o = ent->obj;
            pos[i] = o->trans.x;
            if (o->trans.x + 39.0f > obj->trans.x - 40.0f && o->trans.x - 39.0f < obj->trans.x + 40.0f) {
                near = 1;
            }
        }
        for (i = 0; i < 3; i++) {
            ent = &D_8010B820_coconut_conk[i];
            o = ent->obj;
            if (ent->unk04 == 1 || ent->unk04 == 2) {
                if (o->trans.x + 29.0f > obj->trans.x - 40.0f && o->trans.x - 29.0f < obj->trans.x + 40.0f) {
                    near = 2;
                }
            }
        }
        if (near == 1) {
            lo = 0;
            mid = 0;
            hi = 0;
            for (j = 0; j < 2; j++) {
                for (i = 0; i < 3; i++) {
                    if (pos[i] < pos[lo]) {
                        lo = i;
                    }
                }
            }
            for (j = 0; j < 2; j++) {
                for (i = 0; i < 3; i++) {
                    if (pos[hi] < pos[i]) {
                        hi = i;
                    }
                }
            }
            for (i = 0; i < 3; i++) {
                if (i != lo && i != hi) {
                    mid = i;
                }
            }
            gap[0] = fabsf(-450.0f - pos[lo]);
            gap[1] = fabsf(pos[lo] - pos[mid]);
            gap[2] = fabsf(pos[mid] - pos[hi]);
            gap[3] = fabsf(pos[hi] - 450.0f);
            best = 0;
            for (i = 0; i < 3; i++) {
                if (gap[i] < gap[i + 1]) {
                    best = i + 1;
                }
            }
            switch (best) {
                case 0:
                    target = (pos[lo] + -450.0f) * 0.5f;
                    break;
                case 1:
                    target = (pos[lo] + pos[mid]) * 0.5f;
                    break;
                case 2:
                    target = (pos[mid] + pos[hi]) * 0.5f;
                    break;
                case 3:
                    target = (pos[hi] + 450.0f) * 0.5f;
                    break;
            }
            if (target + 60.0f < obj->trans.x) {
                dir = 1;
            } else if (obj->trans.x < target - 60.0f) {
                dir = 2;
            }
        }
        if (near == 2) {
            dir = 2;
            if (solo->unk18 <= 0.0f) {
                dir = 1;
            }
        }
        if (near == 0) {
            if (solo->unk18 > 0.0f) {
                dir = 1;
            } else if (solo->unk18 < 0.0f) {
                dir = 2;
            }
        }
    }
    if (--solo->unk06 <= 0) {
        solo->unk06 = 0;
    }
    if (dir == 0) {
        solo->unk04 = 0;
    }
    if ((u8)(dir % 5) == 1 && solo->unk06 == 0) {
        solo->unk04 = 1;
        switch (GwPlayer[player].cpu_difficulty) {
            case 0:
                solo->unk06 = 30;
                break;
            case 1:
                solo->unk06 = 10;
                break;
            case 2:
                solo->unk06 = 7;
                break;
            case 3:
                solo->unk06 = 1;
                break;
        }
    }
    if ((u8)(dir % 5) == 2 && solo->unk06 == 0) {
        solo->unk04 = 2;
        switch (GwPlayer[player].cpu_difficulty) {
            case 0:
                solo->unk06 = 30;
                break;
            case 1:
                solo->unk06 = 10;
                break;
            case 2:
                solo->unk06 = 7;
                break;
            case 3:
                solo->unk06 = 1;
                break;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106F18_coconut_conk);
#endif

void func_80107674_coconut_conk(omObjData *obj) {
    func_80106F18_coconut_conk(obj);
}

/* The solo player's stick. */
void func_80107690_coconut_conk(omObjData *obj) {
    CcEnt *solo = &D_8010BCC4_coconut_conk[0];

    D_8010BCC8_coconut_conk = 0;
    if (D_800CBB6E_main[obj->work[3]] < -29) {
        D_8010BCC8_coconut_conk = 1;
    }
    if (D_800CBB6E_main[obj->work[3]] >= 30) {
        solo->unk04 = 2;
    }
}

/* Rolls the solo player's barrel during the intro. */
void func_801076EC_coconut_conk(omObjData *obj) {
    CcEnt *solo = &D_8010BCC4_coconut_conk[0];
    switch (D_8010BCC8_coconut_conk) {
        case 0:
            if (solo->unk18 < 0.0f) {
                solo->unk18 += 0.05;
            }
            if (solo->unk18 > 0.0f) {
                solo->unk18 -= 0.05;
            }
            if ((s16)solo->unk18 == 0) {
                solo->unk18 = 0.0f;
                obj->trans.x = (s16)obj->trans.x;
            }
            break;
        case 1:
            if (solo->unk18 > -10.0f) {
                solo->unk18 -= 0.5f;
                if (solo->unk18 < -10.0f) {
                    solo->unk18 = -10.0f;
                }
            }
            break;
        case 2:
            if (solo->unk18 < 10.0f) {
                solo->unk18 += 0.5f;
                if (solo->unk18 > 10.0f) {
                    solo->unk18 = 10.0f;
                }
            }
            break;
    }
    obj->rot.z = func_801059BC_coconut_conk(obj->rot.z, -solo->unk18);
    obj->trans.x += solo->unk18;
}

/* Rolls the solo player's barrel; D_8010B1C0_coconut_conk counts frames spent nearly still. */
void func_801078BC_coconut_conk(omObjData *obj) {
    f32 x;
    CcEnt *solo = &D_8010BCC4_coconut_conk[0];

    switch (D_8010BCC8_coconut_conk) {
        case 0:
            if (solo->unk18 < 0.0f) {
                solo->unk18 += 0.05;
            }
            if (solo->unk18 > 0.0f) {
                solo->unk18 -= 0.05;
            }
            if ((s16)solo->unk18 == 0) {
                solo->unk18 = 0.0f;
                obj->trans.x = (s16)obj->trans.x;
            }
            break;
        case 1:
            if (solo->unk18 > -7.0f) {
                solo->unk18 -= 0.45f;
                if (solo->unk18 < -7.0f) {
                    solo->unk18 = -7.0f;
                }
            }
            break;
        case 2:
            if (solo->unk18 < 7.0f) {
                solo->unk18 += 0.45f;
                if (solo->unk18 > 7.0f) {
                    solo->unk18 = 7.0f;
                }
            }
            break;
    }
    if (solo->unk18 >= -3.0f && solo->unk18 <= 3.0f) {
        if (++D_8010B1C0_coconut_conk >= 501) {
            D_8010B1C0_coconut_conk = 500;
        }
    } else {
        D_8010B1C0_coconut_conk = 0;
    }
    x = obj->trans.x + solo->unk18;
    if ((x >= 450.0f) | (x <= -450.0f)) {
        solo->unk18 = -(solo->unk18 * 0.5f);
    }
    obj->rot.z = func_801059BC_coconut_conk(obj->rot.z, -solo->unk18);
    obj->trans.x += solo->unk18;
}

/* The solo player catches a falling coconut; animates the barrel lid (D_8010BCC4_coconut_conk[0].unk0A). */
void func_80107B8C_coconut_conk(omObjData *obj) {
    CcEnt *ent;
    omObjData *nut;
    s16 i;
    s16 se;
    CcEnt *solo = &D_8010BCC4_coconut_conk[0];

    for (i = 0; i < 9; i++) {
        ent = &D_8010B820_coconut_conk[i];
        nut = ent->obj;
        if (ent->unk04 == 2 && nut->trans.x + 29.0f >= obj->trans.x - 40.0f && nut->trans.x - 29.0f <= obj->trans.x + 40.0f &&
            nut->trans.y + 84.0f >= obj->trans.y - 50.0f && nut->trans.y <= obj->trans.y + 50.0f) {
            if (D_8010B1C8_coconut_conk == 2 && D_8010B1E0_coconut_conk > 0) {
                D_8010B1CC_coconut_conk = 1;
                func_80105BA4_coconut_conk(obj, 2);
                func_8001C92C_main(obj->model[6], 1.0f);
                func_8001C258_main(obj->model[6], 4, 0);
                Hu3DModelPosSet(obj->model[6], obj->trans.x, obj->trans.y + 50.0f, obj->trans.z);
                solo->unk0A = 1;
                if (!(GwPlayer[obj->work[0]].stat & 1)) {
                    omVibrate(obj->work[0], 20, 0, 20);
                }
            }
            ent->unk04 = 4;
        }
    }
    if (D_800CCF58_main[HmfModelData[obj->model[6]].unk02].unk02 <= HmfModelData[obj->model[6]].unk40) {
        func_8001C258_main(obj->model[6], 4, 4);
        func_8001C258_main(obj->model[7], 4, 0);
        Hu3DModelPosSet(obj->model[7], obj->trans.x, obj->trans.y + 50.0f, obj->trans.z + 40.0f);
        if (solo->unk0C == 0) {
            se = func_8004ACE0_main(D_8010AF60_coconut_conk, obj->work[0]);
            solo->unk0C++;
            HuAudFXPitchSet(se, 0);
            func_8004AAD0_main(se, 127);
        }
    }
    switch (solo->unk0A) {
        case 0:
            solo->unk24 = 1.0f;
            solo->unk28 = 1.0f;
            break;
        case 1:
            func_8001C258_main(obj->model[3], 0x4000, 0);
            solo->unk24 = 0.5f;
            solo->unk28 = 1.3f;
            solo->unk0A = 2;
            break;
        case 2:
            solo->unk24 += 0.1f;
            solo->unk28 -= 0.06f;
            if (solo->unk24 >= 1.5f) {
                solo->unk0A = 3;
            }
            break;
        case 3:
            solo->unk24 -= 0.1f;
            solo->unk28 += 0.06f;
            if (solo->unk24 <= 0.5f) {
                solo->unk0A = 4;
            }
            break;
        case 4:
            solo->unk24 += 0.1f;
            solo->unk28 -= 0.06f;
            if (solo->unk24 >= 1.5f) {
                solo->unk0A = 5;
            }
            break;
        case 5:
            solo->unk24 -= 0.1f;
            solo->unk28 += 0.06f;
            if (solo->unk24 <= 0.5f) {
                solo->unk0A = 6;
            }
            break;
        case 6:
            solo->unk24 += 0.1f;
            solo->unk28 -= 0.06f;
            if (solo->unk24 >= 1.0f) {
                solo->unk0A = 7;
            }
            break;
    }
    Hu3DModelPosSet(obj->model[3], obj->trans.x, 40.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[3], 90.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[3], solo->unk28, 1.0f, solo->unk24);
}

/* The solo player: intro roll (D_8010B1C8_coconut_conk 0), play (2), and the end (4: jump out of the barrel). */
void func_8010815C_coconut_conk(omObjData *obj) {
    CcEnt *solo = &D_8010BCC4_coconut_conk[0];
    u16 player = obj->work[0];
    s16 old;
    s16 pan;

    switch (D_8010B1C8_coconut_conk) {
        case 1:
        case 5:
            break;
        case 0:
            switch (solo->unk08) {
                case 0:
                    solo->unk04 = 1;
                    if (obj->trans.x < 30.0f) {
                        solo->unk08 = 1;
                    }
                    break;
                case 1:
                    solo->unk04 = 2;
                    if (solo->unk18 > 2.5f) {
                        solo->unk08 = 2;
                    }
                    break;
                case 2:
                    solo->unk04 = 0;
                    if ((s16)obj->rot.z >= 350.0f || (s16)obj->rot.z <= 5.0f) {
                        if (obj->trans.x >= -5.0f && obj->trans.x <= 5.0f) {
                            obj->rot.z = 0.0f;
                            solo->unk04 = 0;
                            solo->unk18 = 0.0f;
                            solo->unk08 = 3;
                        }
                    }
                    break;
                case 3:
                    D_8010CBBA_coconut_conk = 0;
                    solo->unk08 = 0;
                    break;
            }
            func_801076EC_coconut_conk(obj);
            break;
        case 2:
            if (D_8010B1E0_coconut_conk > 0 && D_8010B1CC_coconut_conk == 0) {
                if (GwPlayer[player].stat & 1) {
                    func_80107674_coconut_conk(obj);
                } else {
                    func_80107690_coconut_conk(obj);
                }
                func_801078BC_coconut_conk(obj);
            }
            func_80107B8C_coconut_conk(obj);
            break;
        case 3:
            func_80107B8C_coconut_conk(obj);
            solo->unk18 = 0.0f;
            break;
        case 4:
            func_80107B8C_coconut_conk(obj);
            if (D_8010B1CC_coconut_conk == 0) {
                switch (solo->unk08) {
                    case 0:
                        func_8001C258_main(obj->model[3], 4, 4);
                        func_8001C258_main(obj->model[3], 0x4000, 0);
                        func_8001C92C_main(obj->model[4], 1.0f);
                        func_8001C258_main(obj->model[4], 4, 0);
                        Hu3DModelPosSet(obj->model[4], obj->trans.x, obj->trans.y + 20.0f, obj->trans.z);
                        func_8001C92C_main(obj->model[5], 1.0f);
                        func_8001C258_main(obj->model[5], 4, 0);
                        Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y + 20.0f, obj->trans.z);
                        func_80105BA4_coconut_conk(obj, 1);
                        obj->rot.z = 0.0f;
                        func_8001C5B4_main(obj->model[0], obj->motion[1]);
                        solo->unk1C = 30.0f;
                        solo->unk08 = 1;
                        break;
                    case 1:
                        obj->trans.y = func_80105B88_coconut_conk(obj->trans.y, &solo->unk1C, 3.0f);
                        if (obj->trans.y <= 0.0f) {
                            obj->trans.y = 0.0f;
                            solo->unk08 = 2;
                            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 5, 0);
                            func_80045ED0_main((D_8010AFD0_coconut_conk[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                        }
                        solo->unk20 -= 9.0f;
                        if (solo->unk20 < 0.0f) {
                            solo->unk20 = 0.0f;
                        }
                        func_8001F9E4_main(obj->model[4], solo->unk20);
                        if (D_800CCF58_main[HmfModelData[obj->model[4]].unk02].unk02 <= HmfModelData[obj->model[4]].unk40) {
                            func_8001C258_main(obj->model[4], 4, 4);
                        }
                        if (D_800CCF58_main[HmfModelData[obj->model[5]].unk02].unk02 <= HmfModelData[obj->model[5]].unk40) {
                            func_8001C258_main(obj->model[5], 4, 4);
                        }
                        break;
                    case 2:
                        solo->unk20 -= 9.0f;
                        if (solo->unk20 < 0.0f) {
                            solo->unk20 = 0.0f;
                        }
                        func_8001F9E4_main(obj->model[4], solo->unk20);
                        if (D_800CCF58_main[HmfModelData[obj->model[4]].unk02].unk02 <= HmfModelData[obj->model[4]].unk40) {
                            func_8001C258_main(obj->model[4], 4, 4);
                        }
                        if (D_800CCF58_main[HmfModelData[obj->model[5]].unk02].unk02 <= HmfModelData[obj->model[5]].unk40) {
                            func_8001C258_main(obj->model[5], 4, 4);
                        }
                        break;
                }
            }
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    if (++D_8010CBB8_coconut_conk >= 100) {
        D_8010CBB8_coconut_conk = 0;
    }
    old = D_8010CBC0_coconut_conk;
    if (old == -1) {
        D_8010CBC0_coconut_conk = func_8004AC98_main(D_8010AF66_coconut_conk, obj->work[0]);
        if (D_8010CBC0_coconut_conk != old) {
            D_8010B1E6_coconut_conk = -400;
            HuAudFXPitchSet(D_8010CBC0_coconut_conk, -400);
            D_8010B1C2_coconut_conk = 0;
            func_8004AAD0_main(D_8010CBC0_coconut_conk, D_8010B1C3_coconut_conk);
        }
        if (D_8010CBC0_coconut_conk == old) {
            return;
        }
    }
    if (D_8010B1C8_coconut_conk < 3) {
        if (!(D_8010CBB8_coconut_conk & 1)) {
            D_8010B1E6_coconut_conk = fabs(solo->unk18 * 60.0f) + 0.0;
            if (D_8010B1E6_coconut_conk >= 401) {
                D_8010B1E6_coconut_conk = 400;
            } else if (D_8010B1E6_coconut_conk < 0) {
                D_8010B1E6_coconut_conk = 0;
            }
            HuAudFXPitchSet(D_8010CBC0_coconut_conk, D_8010B1E6_coconut_conk);
        } else {
            D_8010B1C2_coconut_conk = fabs(solo->unk18 * 20.0f) + 0.0;
            if (D_8010B1C2_coconut_conk >= 126) {
                D_8010B1C2_coconut_conk = 125;
            } else if (D_8010B1C2_coconut_conk < 0) {
                D_8010B1C2_coconut_conk = 0;
            }
            func_8004AAD0_main(D_8010CBC0_coconut_conk, D_8010B1C3_coconut_conk);
        }
        pan = (obj->trans.x + 450.0f) * 0.143f;
        if (pan < 0) {
            pan = 0;
        } else if (pan >= 128) {
            pan = 127;
        }
        func_8004AE00_main(D_8010CBC0_coconut_conk, pan);
    }
}




/* The solo player: character model, barrel, shadow, lid, splash and hook models. */
void func_801089DC_coconut_conk(omObjData *obj) {
    CcEnt *solo = &D_8010BCC4_coconut_conk[0];
    s8 chr = GwPlayer[obj->work[0]].chr;
    s32 dir = D_800A178C_main[chr][0];
    s16 i;

    obj->model[0] = func_8000B108_main(dir | D_800A178C_main[chr][2], 0x2A9);
    for (i = 0; i < 3; i++) {
        D_8010B1D0_coconut_conk[i] = DataRead(dir | D_8010AF68_coconut_conk[chr][i]);
    }
    D_8010B1DC_coconut_conk = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010B1D0_coconut_conk[0], 0, D_8010AF98_coconut_conk[chr]);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x62));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 4));
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C6A8_main(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 2, 2);
    obj->trans.x = 400.0f;
    obj->trans.y = 40.0f;
    obj->trans.z = -100.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    solo->unk18 = -10.0f;
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 325.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[1] = func_8000B0A0_main(0, 0x4A9);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    obj->model[2] = func_8000B108_main(8, 0x2BD);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    obj->model[3] = func_8000B108_main(0x230000, 0x299);
    Hu3DModelPosSet(obj->model[3], 0.0f, 0.0f, 0.0f);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], obj->model[0], "item_hook");
    obj->model[4] = func_8000B108_main(0x230006, 0x28D);
    Hu3DModelPosSet(obj->model[4], 0.0f, 0.0f, 0.0f);
    func_8001C6A8_main(obj->model[4], 0.0f);
    func_8001C92C_main(obj->model[4], 0.0f);
    func_8001FA68_main(obj->model[4]);
    solo->unk20 = 255.0f;
    func_8001F9E4_main(obj->model[4], 255);
    obj->model[5] = func_8000B108_main(0x230007, 0x29D);
    Hu3DModelPosSet(obj->model[5], 0.0f, 0.0f, 0.0f);
    func_8001C6A8_main(obj->model[5], 0.0f);
    func_8001C92C_main(obj->model[5], 0.0f);
    obj->model[6] = func_8000B108_main(0x230008, 0x29D);
    Hu3DModelPosSet(obj->model[6], 0.0f, 0.0f, 0.0f);
    func_8001C6A8_main(obj->model[6], 3.0f);
    func_8001C92C_main(obj->model[6], 0.0f);
    Hu3DModelScaleSet(obj->model[6], 1.5f, 1.5f, 1.5f);
    obj->model[7] = func_8000B108_main(0x230009, 0x29D);
    Hu3DModelPosSet(obj->model[7], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[7], 1.5f, 1.5f, 1.5f);
    func_8001C814_main(obj->model[7], 2, 2);
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    func_8001C8A8_main(obj->model[2], 2);
    func_8001C8A8_main(obj->model[3], 2);
    func_8001C8A8_main(obj->model[4], 2);
    func_8001C8A8_main(obj->model[5], 2);
    func_8001C8A8_main(obj->model[6], 2);
    func_8001C8A8_main(obj->model[7], 2);
    obj->func = func_8010815C_coconut_conk;
}

/* Creates the solo player's object (the player in group 0). */
void func_80108FA0_coconut_conk(void) {
    omObjData *obj;
    u16 player = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            switch (i) {
                case 0:
                    player = 0;
                    break;
                case 1:
                    player = 1;
                    break;
                case 2:
                    player = 2;
                    break;
                case 3:
                    player = 3;
                    break;
            }
            obj = omAddObj(700, 9, 60, -1, func_801089DC_coconut_conk);
            obj->work[0] = player;
            obj->work[3] = GwPlayer[player].pad;
            D_8010BCC4_coconut_conk[0].obj = obj;
        }
    }
}



/* A team player's CPU: chases the solo player near the end and presses A/B; steers the stick through unk08. */
#ifdef NON_MATCHING
/* Differs from retail only in where the closest-player loop converts best to double (register/scheduling). */
void func_801090C4_coconut_conk(omObjData *obj) {
    CcEnt *ents[4];
    omObjData *objs[4];
    CcEnt *ent = &D_8010BCC4_coconut_conk[obj->work[1] + 1];
    u16 player = obj->work[0];
    u8 dir = rand8();
    omObjData *solo = D_8010BCC4_coconut_conk[0].obj;
    u8 diff;
    f64 d;
    f32 best;
    s16 i;
    s16 closest;

    if (D_8010B1C8_coconut_conk == 2) {
        diff = GwPlayer[player].cpu_difficulty;
        if (((diff == 0) & (dir < 50)) || ((diff == 1) & (dir < 80)) || ((diff == 2) & (dir < 100)) || ((diff == 3) & (dir < 130))) {
            dir = 2;
            if (solo->trans.x < obj->trans.x) {
                dir = 1;
            }
        }
    }
    if (D_8010CBBB_coconut_conk == 3) {
        closest = 0;
        if (D_8010B1C0_coconut_conk >= D_8010CBBC_coconut_conk) {
            best = 5000.0f;
            for (i = 0; i < 3; i++) {
                ents[i] = &D_8010BCC4_coconut_conk[i + 1];
                objs[i] = ents[i]->obj;
            }
            for (i = 0; i < 3; i++) {
                if (best >= (d = fabs(objs[i]->trans.x - solo->trans.x))) {
                    closest = i;
                    best = d;
                }
            }
            dir = 0;
            if (obj->work[1] == closest) {
                if (obj->trans.x > solo->trans.x) {
                    dir = 1;
                } else if (obj->trans.x < solo->trans.x) {
                    dir = 2;
                }
                if (obj->trans.x + 29.0f > solo->trans.x - 40.0f &&
                    obj->trans.x - 29.0f < solo->trans.x + 40.0f) {
                    D_800D5558_main[obj->work[3]] |= 0x8000;
                    D_800D5558_main[obj->work[3]] |= 0x2000;
                }
            } else {
                D_800D5558_main[obj->work[3]] |= 0x8000;
            }
        }
    }
    if (--ent->unk06 <= 0) {
        ent->unk06 = 0;
    }
    if (obj->trans.y > 512.0f) {
        dir = 0;
    }
    if (dir == 0 && ent->unk06 == 0) {
        ent->unk08 = 0;
    }
    if ((u8)(dir % 5) == 1 && ent->unk06 == 0) {
        ent->unk08 = -(rand8() & 0x1F) - 30;
        ent->unk06 = 15;
    }
    if ((u8)(dir % 5) == 2 && ent->unk06 == 0) {
        ent->unk08 = (rand8() & 0x1F) + 30;
        ent->unk06 = 15;
    }
    /* the low byte of the s16 unk08 (big-endian) */
    D_800CBB6E_main[obj->work[3]] = ((s8 *)&ent->unk08)[1];
    if ((u8)(rand8() % 70) == 0) {
        D_800D5558_main[obj->work[3]] |= 0x8000;
    }
    if ((u8)(rand8() % 5) == 0) {
        D_800D5558_main[obj->work[3]] |= 0x2000;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801090C4_coconut_conk);
#endif

void func_801095A4_coconut_conk(omObjData *obj) {
    func_801090C4_coconut_conk(obj);
}

void func_801095C0_coconut_conk(omObjData *obj) {
}









/* A team player hits a palm tree: the nearest tree shakes and drops one of its three coconuts. */
#ifdef NON_MATCHING
/* Differs from retail only in the scheduling of one instruction in the nearest-tree loop. */
void func_801095C8_coconut_conk(omObjData *obj) {
    CcEnt *ent = &D_8010BCC4_coconut_conk[obj->work[1] + 1];
    MgWork *gw = obj->data;
    CcEnt *tree;
    CcEnt *nut;
    omObjData *o;
    f32 best;
    f64 d;
    s16 closest;
    s16 i;

    if (D_800D20A1_main[obj->work[3]] >= 5) {
        D_800D20A1_main[obj->work[3]] = 0;
    }
    if (D_800D20A1_main[obj->work[3]] < -4) {
        D_800D20A1_main[obj->work[3]] = 0;
    }
    func_800DDD94_minigame(obj);
    if (HmfModelData[obj->model[7]].unk40 == 0.0f) {
        func_8001C258_main(obj->model[7], 4, 4);
    }
    if (gw->unk5C == 0x200) {
        if (gw->unk50 == 0x80 && ent->unk04 == 0) {
            ent->unk04 = 1;
            if (D_8010B1DE_coconut_conk < 3) {
                D_8010B1DE_coconut_conk++;
                func_800E4C88_minigame(obj, 7, obj->trans.x, obj->trans.y, obj->trans.z, 0.0f, 0.0f);
                best = 3000.0f;
                closest = 0;
                for (i = 0; i < 6; i++) {
                    if (best > (d = fabs(obj->trans.x - D_8010AFB8_coconut_conk[i]))) {
                        best = d;
                        closest = i;
                    }
                }
                tree = &D_8010B508_coconut_conk[closest];
                if (tree->unk04 == 0) {
                    tree->unk04 = 1;
                    ent->unk16 = 1;
                }
                switch (closest) {
                    case 0:
                    case 3:
                        for (i = 0; i < 3; i++) {
                            nut = &D_8010B820_coconut_conk[i];
                            o = nut->obj;
                            if (nut->unk04 == 0) {
                                nut->unk04 = 1;
                                o->trans.x = obj->trans.x;
                                break;
                            }
                        }
                        break;
                    case 1:
                    case 4:
                        for (i = 3; i < 6; i++) {
                            nut = &D_8010B820_coconut_conk[i];
                            o = nut->obj;
                            if (nut->unk04 == 0) {
                                nut->unk04 = 1;
                                o->trans.x = obj->trans.x;
                                break;
                            }
                        }
                        break;
                    case 2:
                    case 5:
                        for (i = 6; i < 9; i++) {
                            nut = &D_8010B820_coconut_conk[i];
                            o = nut->obj;
                            if (nut->unk04 == 0) {
                                nut->unk04 = 1;
                                o->trans.x = obj->trans.x;
                                break;
                            }
                        }
                        break;
                }
            }
        }
    }
    if (gw->unk5C != 0x200 && gw->unk50 != 0x80 && obj->trans.y <= 512.0f) {
        ent->unk04 = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801095C8_coconut_conk);
#endif

/* A team player: per frame. */
void func_80109940_coconut_conk(omObjData *obj) {
    MgWork *works[4];
    CcEnt *ents[4];
    omObjData *objs[4];
    CcEnt *ent = &D_8010BCC4_coconut_conk[obj->work[1] + 1];
    MgWork *gw = obj->data;
    s16 i;

    if (D_8010B1C8_coconut_conk != 2) {
        func_80105B04_coconut_conk(obj->work[0]);
    }
    ent->unk18 = obj->trans.x;
    switch (D_8010B1C8_coconut_conk) {
        case 0:
        case 1:
        case 5:
            break;
        case 2:
            if (D_8010B1E0_coconut_conk > 0 && D_8010B1CC_coconut_conk == 0) {
                if (!(GwPlayer[obj->work[0]].stat & 1)) {
                    func_801095C0_coconut_conk(obj);
                } else {
                    func_801095A4_coconut_conk(obj);
                }
            }
            func_801095C8_coconut_conk(obj);
            break;
        case 3:
            if (obj->trans.y > 512.0f) {
                if (++ent->unk0C >= 30001) {
                    ent->unk0C = 0;
                }
                if (ent->unk0C < 70) {
                    D_800CBB6E_main[obj->work[3]] = -40;
                } else if (ent->unk0C < 140) {
                    D_800CBB6E_main[obj->work[3]] = 40;
                }
                if (ent->unk0C >= 140) {
                    func_801095A4_coconut_conk(obj);
                }
                func_801095C8_coconut_conk(obj);
                break;
            }
            if (gw->unk3C != 0.0f) {
                D_800CBB6E_main[obj->work[3]] = 0;
                D_800D20A1_main[obj->work[3]] = -40;
            }
            for (i = 0; i < 3; i++) {
                ents[i] = &D_8010BCC4_coconut_conk[i + 1];
                objs[i] = ents[i]->obj;
                works[i] = objs[i]->data;
            }
            if (objs[0]->trans.y <= 512.0f && works[0]->unk3C == 0.0f && ((works[0]->unk50 == 0) | (works[0]->unk50 == 0x80)) &&
                works[0]->unk5C == 2 && objs[1]->trans.y <= 512.0f && works[1]->unk3C == 0.0f &&
                ((works[1]->unk50 == 0) | (works[1]->unk50 == 0x80)) && works[1]->unk5C == works[0]->unk5C &&
                objs[2]->trans.y <= 512.0f && works[2]->unk3C == 0.0f && ((works[2]->unk50 == 0) | (works[2]->unk50 == 0x80)) &&
                works[2]->unk5C == works[1]->unk5C) {
                D_8010CBBA_coconut_conk = 3;
            }
            func_800DDD94_minigame(obj);
            break;
        case 4:
            if (ent->unk0E == 0) {
                if (D_8010B1CC_coconut_conk == 0) {
                    func_800E5690_minigame(obj, 14);
                    ent->unk0E = 1;
                } else {
                    func_800E5690_minigame(obj, 13);
                    ent->unk0E = 1;
                    func_80045ED0_main((D_8010AFD0_coconut_conk[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                }
            }
            break;
    }
    if (D_8010B1C8_coconut_conk != 2 && D_8010B1C8_coconut_conk != 3) {
        func_800DDD94_minigame(obj);
    }
    if (obj->trans.x < -450.0f) {
        obj->trans.x = -450.0f;
    }
    if (obj->trans.x > 450.0f) {
        obj->trans.x = 450.0f;
    }
    if (gw->unk54 != -1) {
        obj->trans.x = ent->unk18;
    }
    func_8001C258_main(obj->model[1], 4, 4);
    if (ent->unk16 > 0) {
        ent->unk16++;
    }
    if (ent->unk16 >= 4) {
        func_8004AC98_main(0x313, obj->work[0]);
        ent->unk16 = 0;
    }
}

/* A team player: character model, motions and start position (a random free spot under the trees). */
void func_80109DEC_coconut_conk(omObjData *obj) {
    u16 chr = GwPlayer[obj->work[0]].chr;
    s32 dir;
    s32 file;
    u8 pos;

    if (GwPlayer[obj->work[0]].stat & 1) {
        D_8010CBBB_coconut_conk++;
        switch (GwPlayer[obj->work[0]].cpu_difficulty) {
            case 0:
                if (D_8010CBBC_coconut_conk >= 61) {
                    D_8010CBBC_coconut_conk = 60;
                }
                break;
            case 1:
                if (D_8010CBBC_coconut_conk >= 31) {
                    D_8010CBBC_coconut_conk = 30;
                }
                break;
            case 2:
                if (D_8010CBBC_coconut_conk >= 16) {
                    D_8010CBBC_coconut_conk = 15;
                }
                break;
            case 3:
                if (D_8010CBBC_coconut_conk >= 11) {
                    D_8010CBBC_coconut_conk = 10;
                }
                break;
        }
    }
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][1];
    func_800E18D8_minigame();
    func_800E1BA8_minigame(obj, dir, file, obj->work[0], 0x2B9, 0x2A9);
    ((MgWork *)obj->data)->unkEC = NULL;
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C258_main(obj->model[1], 0x60, 0x20);
    func_8001C258_main(obj->model[1], 0x180, 0x80);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    obj->model[7] = func_8000B108_main(8, 0x2BD);
    obj->model[6] = func_8000B108_main(5, 0x2BD);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 8, func_80017BB8_main(chr, 6), 1, 0x1B);
    func_800E5A00_minigame(obj, 0x12, func_80017BB8_main(chr, 0xF), 2, 0);
    func_800E5978_minigame(obj, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, 0x36), 1, 0x3E7);
    func_800E5690_minigame(obj, 0);
    D_800EBE24_minigame = 1;
    pos = rand8() % 3;
    for (;;) {
        if (pos != D_8010B1C9_coconut_conk[0] && pos != D_8010B1C9_coconut_conk[1]) {
            D_8010B1C9_coconut_conk[D_8010CBBE_coconut_conk] = pos;
            D_8010CBBE_coconut_conk++;
            switch (pos) {
                case 0:
                    obj->trans.x = -300.0f;
                    break;
                case 1:
                    obj->trans.x = 0.0f;
                    break;
                case 2:
                    obj->trans.x = 300.0f;
                    break;
            }
            break;
        }
        pos++;
        if (pos >= 3) {
            pos = 0;
        }
    }
    obj->trans.y = 512.0f;
    obj->trans.z = -225.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[7], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[6], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    func_8001C8A8_main(obj->model[7], 2);
    func_8001C8A8_main(obj->model[6], 2);
    func_800E149C_minigame(obj, 0, 2);
    func_80105B04_coconut_conk(obj->work[0]);
    obj->func = func_80109940_coconut_conk;
}

/* Creates the three team players' objects. */
void func_8010A344_coconut_conk(void) {
    omObjData *obj;
    CcEnt *ent;
    u16 player = 0;
    u32 n = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            switch (i) {
                case 0:
                    player = 0;
                    break;
                case 1:
                    player = 1;
                    break;
                case 2:
                    player = 2;
                    break;
                case 3:
                    player = 3;
                    break;
            }
            ent = &D_8010BCC4_coconut_conk[n + 1];
            obj = omAddObj(650, 9, 60, -1, func_80109DEC_coconut_conk);
            obj->work[0] = player;
            obj->work[3] = GwPlayer[player].pad;
            ent->obj = obj;
            obj->work[1] = n++;
            D_800EC598_minigame[D_800EC280_minigame] = obj;
            D_800EC280_minigame++;
        }
    }
}

void func_8010A4AC_coconut_conk(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 1270.8f;
        CRotM[i].x = 350.94f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 415.0f;
        CenterM[i].z = -115.0f;
    }
}

void func_8010A55C_coconut_conk(omObjData *obj) {
    u8 i;

    for (i = 0; i < 3; i++) {
        DataClose(D_8010B1D0_coconut_conk[i]);
    }
    func_80033354_main(D_8010B1DC_coconut_conk);
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void func_8010A5D8_coconut_conk(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010A55C_coconut_conk;
    }
}

void func_8010A610_coconut_conk(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010A5D8_coconut_conk;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

/* The minigame's flow (D_8010B1C8_coconut_conk): 0 intro, 1 start message, 2 play (timer D_8010B1E0_coconut_conk),
 * 3 finish, 4 result, 5 exit. */
void func_8010A668_coconut_conk(omObjData *obj) {
    u8 chrs[8];
    CcEnt *ents[4];
    omObjData *objs[4];
    omObjData *solo = D_8010BCC4_coconut_conk[0].obj;
    s16 i;
    s16 n;

    for (i = 0; i < 3; i++) {
        ents[i] = &D_8010BCC4_coconut_conk[i + 1];
        objs[i] = ents[i]->obj;
    }
    switch (D_8010B1C8_coconut_conk) {
        case 0:
            if (D_8010B1E0_coconut_conk == 13) {
                HuAudFXPlay(0x314);
                D_8010B1E0_coconut_conk = 14;
            } else if (D_8010B1E0_coconut_conk < 13) {
                D_8010B1E0_coconut_conk++;
            }
            if (D_8010CBBA_coconut_conk == 0) {
                func_80105B7C_coconut_conk(1);
                D_8010B1E0_coconut_conk = 1;
                HuAudSeqPlay(0x30);
            }
            break;
        case 1:
            if (--D_8010B1E0_coconut_conk == 0) {
                GMesCreate(4);
            }
            if (GMesStatGet() == 0) {
                func_80105B7C_coconut_conk(2);
                GMesCreate(0x1A, 30, 160, 28);
                D_8010B1E0_coconut_conk = 901;
            }
            break;
        case 2:
            if (D_8010B1E0_coconut_conk > 0) {
                D_8010B1E0_coconut_conk--;
                func_8003F578_main((D_8010B1E0_coconut_conk + 29) / 30);
            } else if (D_8010B1CC_coconut_conk == 0) {
                func_8003F5C0_main();
                func_80105B7C_coconut_conk(3);
                GMesCreate(0xF);
                D_8010B1CC_coconut_conk = 0;
                D_8010B1E0_coconut_conk = -15;
                HuAudSeqFadeOut(120);
                HuAudFXStop(D_8010CBC0_coconut_conk);
            }
            if (D_8010B1CC_coconut_conk == 1) {
                func_8003F5C0_main();
                func_80105B7C_coconut_conk(3);
                GMesCreate(0xF);
                D_8010B1CC_coconut_conk = 1;
                D_8010B1E0_coconut_conk = -15;
                HuAudSeqFadeOut(120);
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                if (D_8010B1E0_coconut_conk >= 0 && D_8010CBBA_coconut_conk == 3) {
                    func_80105B7C_coconut_conk(4);
                    D_8010B1E0_coconut_conk = -1;
                } else if (D_8010B1E0_coconut_conk < 0) {
                    D_8010B1E0_coconut_conk++;
                }
            }
            break;
        case 4:
            if (D_8010B1E0_coconut_conk == -1) {
                D_8010B1E0_coconut_conk = 0;
                n = 0;
                if (D_8010B1CC_coconut_conk == 0) {
                    for (i = 0; i < 4; i++) {
                        if (GwPlayer[i].group == 0) {
                            chrs[0] = GwPlayer[i].chr;
                        }
                    }
                    GMesCreate(0x16, chrs[0]);
                    HuAudSeqPlay(0x65);
                    GwPlayer[solo->work[0]].bonusCoin = 10;
                } else {
                    for (i = 0; i < 4; i++) {
                        if (GwPlayer[i].group != 0) {
                            chrs[n] = GwPlayer[i].chr;
                            n++;
                        }
                    }
                    GMesCreate(0x22, chrs[0], chrs[1], chrs[2]);
                    HuAudSeqPlay(0x66);
                    for (i = 0; i < 3; i++) {
                        GwPlayer[objs[i]->work[0]].bonusCoin = 10;
                    }
                }
            }
            if (GMesStatGet() == 0) {
                if (D_8010B1E0_coconut_conk >= 15) {
                    func_80105B7C_coconut_conk(5);
                    D_8010B1E0_coconut_conk = -1;
                }
                D_8010B1E0_coconut_conk++;
            }
            break;
        case 5:
            if (D_8010B1E0_coconut_conk == 0) {
                WipeCreateOut(0, 20);
                obj->func = func_8010A5D8_coconut_conk;
                D_8010B1E0_coconut_conk++;
            }
            break;
    }
}





void func_8010AB4C_coconut_conk(omObjData *obj) {
    s16 i;

    func_800E6F0C_minigame(2);
    WipeCreateIn(255, 16);
    D_8010B1E0_coconut_conk = 0;
    D_8010B1C8_coconut_conk = 0;
    D_8010CBBA_coconut_conk = 100;
    for (i = 0; i < 3; i++) {
        D_8010B1C9_coconut_conk[i] = 5;
    }
    D_8010CBBE_coconut_conk = 0;
    D_8010B1C0_coconut_conk = 0;
    D_8010CBBB_coconut_conk = 0;
    D_8010CBBC_coconut_conk = 500;
    D_8010B1CC_coconut_conk = 0;
    D_8010B1DE_coconut_conk = 0;
    D_8010CBC0_coconut_conk = -1;
    D_8010B1E6_coconut_conk = -400;
    D_8010B1C2_coconut_conk = 0;
    D_8010CBB8_coconut_conk = 0;
    func_80105D58_coconut_conk();
    func_801061AC_coconut_conk();
    func_80106294_coconut_conk();
    func_8010641C_coconut_conk();
    func_801066A4_coconut_conk();
    func_80108FA0_coconut_conk();
    func_8010A344_coconut_conk();
    func_80106E80_coconut_conk();
    func_80106924_coconut_conk();
    func_8010A4AC_coconut_conk();
    obj->func = func_8010A668_coconut_conk;
}

void func_8010AC88_coconut_conk(omObjData *obj) {
}

void func_8010AC90_coconut_conk(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_8010B018_coconut_conk[i].scissor[0], D_8010B018_coconut_conk[i].scissor[1],
                   D_8010B018_coconut_conk[i].scissor[2], D_8010B018_coconut_conk[i].scissor[3]);
        ViewportSet(i, D_8010B018_coconut_conk[i].viewport[0], D_8010B018_coconut_conk[i].viewport[1],
                    D_8010B018_coconut_conk[i].viewport[2], D_8010B018_coconut_conk[i].viewport[3],
                    D_8010B018_coconut_conk[i].viewport[4], D_8010B018_coconut_conk[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010B018_coconut_conk[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010AE04_coconut_conk(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010AC90_coconut_conk();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(0, -84.0f, 49.0f, 69.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -84.0f, 49.0f, 69.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, -84.0f, 49.0f, 69.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010B1B8_coconut_conk, 0);
    func_80045010_main(D_8010B1B8_coconut_conk, 1);
    omAddObj(1500, 0, 0, -1, func_8010AB4C_coconut_conk);
    omAddObj(1500, 0, 0, -1, func_8010A610_coconut_conk);
    func_80105A3C_coconut_conk();
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct *)&D_8010AFF0_coconut_conk);
}

/* "ABC" in SJIS: the minigame's on-screen title */
const s16 D_8010B1B8_coconut_conk[] = { 0x8260, 0x8261, 0x8262, 0x0000 };
