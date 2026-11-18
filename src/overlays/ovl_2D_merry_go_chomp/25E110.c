#include "common.h"
// m4 mc: Merry-Go-Chomp
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

/* One slot of the overlay's object table (D_8010B1F0_merry_go_chomp, 50 x 0x84). */
typedef struct McEnt {
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
} McEnt; // Size 0x84

#define MC_ENT_GROUND 0
#define MC_ENT_PLAYER 5
#define MC_ENT(base, i) (&(D_8010C500_merry_go_chomp + (base))[i])

/* The ground object's data (func_80105C60_merry_go_chomp). */
typedef struct McGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ char unk08[0xAC];
} McGround; // Size 0xB4

/* A texture's size (func_800335BC_main). */
typedef struct McTexSize {
    /* 0x00 */ s16 w;
    /* 0x02 */ s16 h;
} McTexSize;

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
void func_80105B04_merry_go_chomp(s32 player);
void func_80105B7C_merry_go_chomp(s8 arg0);
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

/* A camera (D_8010B018_merry_go_chomp). */
typedef struct McCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} McCamera; // Size 0x2C

/* The minigame control block (minigame B8A20.c MgCtrl; the header's D_80111B50_vine_with_me_Struct). */
typedef struct McCtrl {
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
} McCtrl; // Size 0x28

/* A player's movement state (D_8010C420_merry_go_chomp, 4 x 0x24). */
typedef struct McPl {
    /* 0x00 */ f32 dx;
    /* 0x04 */ f32 dz;
    /* 0x08 */ f32 rot;
    /* 0x0C */ f32 angle;
    /* 0x10 */ f32 speed;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 z;
    /* 0x1C */ s8 state;
    /* 0x1D */ s8 timer;
    /* 0x1E */ s8 wait;
    /* 0x1F */ s8 jump;
    /* 0x20 */ s8 slot;
} McPl; // Size 0x24

/* .bss */
extern McPl D_8010C420_merry_go_chomp[4];
extern HuSprite_Unk84_Struct *D_8010C414_merry_go_chomp;
extern s8 D_8010C4B0_merry_go_chomp;
extern s16 D_8010C4B2_merry_go_chomp;
extern s8 D_8010C4BD_merry_go_chomp;
extern s8 D_8010C4BE_merry_go_chomp[5];
extern omObjData *D_8010C4C8_merry_go_chomp;
extern s8 D_8010C4CE_merry_go_chomp;
/* The object table: [0] the background, [5..8] the players, [10], [15], [25], [30] the stage objects. */
extern McEnt D_8010C500_merry_go_chomp[50];
extern f32 D_8010CD04_merry_go_chomp; /* = D_8010C500_merry_go_chomp[15].pos.y */
extern f32 D_8010CD08_merry_go_chomp; /* = D_8010C500_merry_go_chomp[15].pos.z */
extern u8 D_8010DECC_merry_go_chomp[5];
extern f32 D_8010DED4_merry_go_chomp;
extern u8 D_8010DEDC_merry_go_chomp;
extern s8 D_8010DEDD_merry_go_chomp;

/* .data */
extern s32 D_8010C140_merry_go_chomp[8];
extern s8 D_8010C160_merry_go_chomp[17];
extern f32 D_8010C174_merry_go_chomp[17];
extern f32 D_8010C1B8_merry_go_chomp[4];
extern f32 D_8010C1C8_merry_go_chomp[4];
extern f32 D_8010C1D8_merry_go_chomp[3][5];
extern s32 D_8010C254_merry_go_chomp;
extern McCamera D_8010C258_merry_go_chomp[2];

/* .rodata */
extern const s16 D_8010C400_merry_go_chomp[];

void func_801059A0_merry_go_chomp(void);
f32 func_801059BC_merry_go_chomp(f32 angle, f32 add);
void func_80106054_merry_go_chomp(Gfx **gfx, s32 arg1, s32 arg2);
void func_8010637C_merry_go_chomp(omObjData *obj);
void func_80106384_merry_go_chomp(omObjData *obj);
void func_801064E0_merry_go_chomp(omObjData *obj);
void func_801064E8_merry_go_chomp(omObjData *obj);
void func_80106668_merry_go_chomp(omObjData *obj);
void func_80106920_merry_go_chomp(omObjData *obj);
s8 func_80106CC4_merry_go_chomp(omObjData *obj);
void func_80107664_merry_go_chomp(omObjData *obj);
void func_801077D0_merry_go_chomp(omObjData *obj);
void func_80107818_merry_go_chomp(omObjData *obj, f32 *x, f32 *z, f32 scale);
s8 func_80107980_merry_go_chomp(void);
void func_80107E34_merry_go_chomp(omObjData *obj);
void func_801084C8_merry_go_chomp(void);
void func_80108A88_merry_go_chomp(omObjData *obj);
void func_8010A9D0_merry_go_chomp(omObjData *obj);
void func_8010AE24_merry_go_chomp(omObjData *obj);
void func_8010AE2C_merry_go_chomp(omObjData *obj);
void func_8010BB7C_merry_go_chomp(omObjData *obj);
void func_8010BBA0_merry_go_chomp(omObjData *obj);
void func_8010BBD8_merry_go_chomp(omObjData *obj);
void func_8010BDE8_merry_go_chomp(omObjData *obj);
void func_8010BEB4_merry_go_chomp(omObjData *obj);
void func_8010BEBC_merry_go_chomp(void);
void func_8010C030_merry_go_chomp(void);


void func_801059A0_merry_go_chomp(void) {
    func_8010C030_merry_go_chomp();
}

f32 func_801059BC_merry_go_chomp(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

u8 func_80105A3C_merry_go_chomp(s32 max) {
    return ((u32)(rand8() * max)) >> 8;
}

void func_80105A74_merry_go_chomp(void) {
    McEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010C500_merry_go_chomp; i < 50; i++, ent++) {
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

void func_80105B3C_merry_go_chomp(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105BB4_merry_go_chomp(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = (x0 - x1) * 5.0f;
    f32 dz = (z0 - z1) * 5.0f;
    f32 zoom;
    f32 rot;

    if (dx < 0.0f) {
        dx = 0.0f - dx;
    }
    if (dz < 0.0f) {
        dz = 0.0f - dz;
    }
    zoom = sqrtf(dx * dx + dz * dz);
    rot = func_801059BC_merry_go_chomp(atan2df(dx, dz), 0.0f);
    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

s32 func_80105CE4_merry_go_chomp(s32 max) {
    return rand8() % max;
}

void func_80105D38_merry_go_chomp(omObjData *obj, u16 motion, s16 attr) {
    func_8001C5B4_main(obj->model[0], obj->motion[motion]);
    func_8001C814_main(obj->model[0], attr, attr);
}

void func_80105DA0_merry_go_chomp(omObjData *obj, u16 motion, s16 start, s16 end, s16 attr) {
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[motion]].unk02, start, end, attr);
}

void func_80105E0C_merry_go_chomp(f32 x0, f32 z0, f32 x1, f32 z1, f32 *dx, f32 *dz, f32 *rot, f32 max) {
    f32 x = x0 - x1;
    f32 z = z0 - z1;
    f32 dist = sqrtf(x * x + z * z);
    f32 div;

    if (dist == 0.0f) {
        *dx = 0.0f;
        *dz = 0.0f;
        return;
    }
    if (dist <= max) {
        *dx = x;
        *dz = z;
    } else {
        div = dist / max;
        if (x != 0.0f) {
            *dx = x / div;
        } else {
            *dx = 0.0f;
        }
        if (z != 0.0f) {
            *dz = z / div;
        } else {
            *dz = 0.0f;
        }
    }
    *rot = atan2df(x, z);
}

s8 func_80105F40_merry_go_chomp(omObjData *obj, f32 rot) {
    f32 cur = obj->rot.y;
    f32 diff = rot - cur;

    if (diff < 0.0f) {
        diff = 0.0f - diff;
    }
    if (diff < 15.0f) {
        obj->rot.y = rot;
        return 0;
    }
    if (cur < rot) {
        if (diff > 180.0f) {
            obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, -15.0f);
        } else {
            obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, 15.0f);
        }
        return 1;
    }
    if (rot < cur) {
        if (diff > 180.0f) {
            obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, 15.0f);
        } else {
            obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, -15.0f);
        }
        return 1;
    }
    return 0;
}

void func_80106054_merry_go_chomp(Gfx **gfx, s32 arg1, s32 arg2) {
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
    gDPLoadTLUT_pal256(g++, D_8010C414_merry_go_chomp->unk0C);
    x = 0;
    for (i = 0, y = 180; i < 60; i += 4) {
        gDPSetTextureImage(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 320, D_8010C414_merry_go_chomp->unk08);
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

void func_8010637C_merry_go_chomp(omObjData *obj) {
}

void func_80106384_merry_go_chomp(omObjData *obj) {
    McEnt *ent = &D_8010C500_merry_go_chomp[MC_ENT_GROUND];

    ent->pos.x = 160.0f;
    ent->pos.y = 107.0f;
    ent->grp = func_8000B838_main(0x4E0000);
    ent->spr = InitEspriteSlot(ent->grp, 0, 0);
    func_8000BC48_main(ent->spr, 0x5000);
    func_8000BBD4_main(ent->spr, ent->pos.x, ent->pos.y);
    D_8010C414_merry_go_chomp = func_80055194_main(func_8000B838_main(0x4E0001));
    func_8001C8A8_main(func_8001AC8C_main(0, func_80106054_merry_go_chomp, 2), 1);
    obj->model[0] = -1;
    obj->func = func_8010637C_merry_go_chomp;
}

void func_801064A0_merry_go_chomp(void) {
    omObjData *obj = omAddObj(500, 1, 1, -1, func_80106384_merry_go_chomp);

    obj->work[0] = 0;
    D_8010C500_merry_go_chomp[MC_ENT_GROUND].obj = obj;
}

void func_801064E0_merry_go_chomp(omObjData *obj) {
}

#ifdef NON_MATCHING
void func_801064E8_merry_go_chomp(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x4E0004, 0x2B9);
    obj->model[1] = func_8000B108_main(0x4E0005, 0x2B9);
    obj->model[2] = func_8000B108_main(0x4E0002, 0x2B9);
    obj->trans.x = -500.0f;
    obj->trans.y = 0.0f;
    D_8010CD04_merry_go_chomp = 0.0f;
    obj->trans.z = -400.0f;
    D_8010CD08_merry_go_chomp = -225.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, D_8010CD04_merry_go_chomp, D_8010CD08_merry_go_chomp);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    func_8001C8A8_main(obj->model[2], 2);
    obj->func = func_801064E0_merry_go_chomp;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801064E8_merry_go_chomp);
#endif

void func_8010662C_merry_go_chomp(void) {
    D_8010C500_merry_go_chomp[15].obj = omAddObj(700, 4, 1, -1, func_801064E8_merry_go_chomp);
}

void func_80106668_merry_go_chomp(omObjData *obj) {
    McEnt *ent = &D_8010C500_merry_go_chomp[25];

    obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, -D_8010DED4_merry_go_chomp);
    switch (D_8010C4B0_merry_go_chomp) {
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
        break;
    case 0:
        D_8010DED4_merry_go_chomp = 3.0f;
        ent->unk06 = 0;
        ent->unk08 = 0;
        break;
    case 4:
        if (D_8010C4B2_merry_go_chomp < 50) {
            if (obj->trans.y > 0.0f) {
                obj->trans.y -= 10.0f;
            } else {
                obj->trans.y = 0.0f;
            }
        }
        break;
    case 9:
        if (D_8010C4B2_merry_go_chomp == 50) {
            if (ent->unk06 == 0) {
                if (ent->unk08 == 0) {
                    HuAudFXPlay(0x473);
                    ent->unk08++;
                }
                if (obj->trans.y > -650.0f) {
                    obj->trans.y -= 15.0f;
                } else {
                    func_8001C258_main(obj->model[ent->unk04], 4, 4);
                    ent->unk04++;
                    func_8001C258_main(obj->model[ent->unk04], 4, 0);
                    ent->unk06 = 1;
                    if (D_8010C4CE_merry_go_chomp == 0) {
                        obj->rot.y = 0.0f;
                    }
                    if (D_8010C4CE_merry_go_chomp == 1) {
                        obj->rot.y = 30.0f;
                    }
                }
            } else {
                if (ent->unk08 == 1) {
                    HuAudFXPlay(0x473);
                    ent->unk08++;
                }
                if (obj->trans.y < 500.0f) {
                    obj->trans.y += 15.0f;
                } else {
                    obj->trans.y = 500.0f;
                    D_8010DEDC_merry_go_chomp |= 8;
                    if (ent->unk08 == 2) {
                        HuAudFXPlay(0x478);
                        ent->unk08++;
                    }
                }
            }
        }
        break;
    }
    Hu3DModelPosSet(obj->model[ent->unk04], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[ent->unk04], obj->rot.x, obj->rot.y, obj->rot.z);
}

void func_80106920_merry_go_chomp(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x4E0006, 0x2B9);
    obj->model[1] = func_8000B108_main(0x4E0007, 0x2B9);
    obj->model[2] = func_8000B108_main(0x4E0008, 0x2B9);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->model[3] = func_8000B108_main(0x4E0009, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    D_8010C500_merry_go_chomp[25].unk04 = 1;
    obj->trans.x = 0.0f;
    obj->trans.y = 500.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    D_8010C4BE_merry_go_chomp[0] = 1;
    D_8010C4BE_merry_go_chomp[1] = 1;
    D_8010C4BE_merry_go_chomp[2] = 1;
    D_8010C4BE_merry_go_chomp[3] = 1;
    D_8010C4BE_merry_go_chomp[4] = 1;
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    func_8001C8A8_main(obj->model[2], 1);
    func_8001C8A8_main(obj->model[3], 1);
    obj->func = func_80106668_merry_go_chomp;
}

void func_80106AB8_merry_go_chomp(void) {
    D_8010C500_merry_go_chomp[25].obj = omAddObj(600, 5, 1, -1, func_80106920_merry_go_chomp);
}

void func_80106AF4_merry_go_chomp(omObjData *obj) {
    McEnt *ent = MC_ENT(MC_ENT_PLAYER, obj->work[0]);

    if (obj->work[2] == 0) {
        if (ent->unk14 != 0) {
            HuAudFXStop(ent->unk14);
        }
        ent->unk14 = func_8004ACE0_main(40, (s16)obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 11;
}

void func_80106B9C_merry_go_chomp(omObjData *obj, s8 motion) {
    s16 attr;
    s32 player = obj->work[0];
    s8 chr = GwPlayer[player].chr;
    McEnt *ent = MC_ENT(MC_ENT_PLAYER, player);

    if (ent->unk06 != motion) {
        switch (motion) {
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            attr = 0;
            break;
        case 0:
        case 1:
        case 2:
            attr = 2;
            break;
        case 3:
        case 4:
        case 5:
        default:
            attr = 2;
            break;
        }
        func_8001C92C_main(obj->model[0], 1.0f);
        func_80105DA0_merry_go_chomp(obj, motion, 0, 5, attr);
        ent->unk06 = motion;
        if (motion == 9) {
            func_80045ED0_main((D_8010C140_merry_go_chomp[chr] << 16) | 0x30);
        }
    }
}

#ifdef NON_MATCHING
/* masked 0: regalloc only (slot in v1/a0 in the CPU branch) */
s8 func_80106CC4_merry_go_chomp(omObjData *obj) {
    McEnt *ent = MC_ENT(MC_ENT_PLAYER, obj->work[0]);
    s8 slot = 99;
    s16 target;
    f32 rot = func_801059BC_merry_go_chomp(MC_ENT(MC_ENT_PLAYER, 20)->obj->rot.y, -120.0f);

    if (!(GwPlayer[obj->work[0]].stat & 1)) {
        switch (D_8010C4CE_merry_go_chomp) {
        case 0:
            if ((rot >= 324.0f) | (rot < 36.0f)) {
                slot = 0;
            }
            if ((rot >= 36.0f) & (rot < 108.0f)) {
                slot = 1;
            }
            if ((rot >= 108.0f) & (rot < 180.0f)) {
                slot = 2;
            }
            if ((rot >= 180.0f) & (rot < 252.0f)) {
                slot = 3;
            }
            if ((rot >= 252.0f) & (rot < 324.0f)) {
                slot = 4;
            }
            break;
        case 1:
            if ((rot >= 315.0f) | (rot < 45.0f)) {
                slot = 0;
            }
            if ((rot >= 45.0f) & (rot < 135.0f)) {
                slot = 1;
            }
            if ((rot >= 135.0f) & (rot < 225.0f)) {
                slot = 2;
            }
            if ((rot >= 225.0f) & (rot < 315.0f)) {
                slot = 3;
            }
            break;
        case 2:
            if ((rot >= 300.0f) | (rot < 60.0f)) {
                slot = 0;
            }
            if ((rot >= 60.0f) & (rot < 180.0f)) {
                slot = 1;
            }
            if ((rot >= 180.0f) & (rot < 300.0f)) {
                slot = 2;
            }
            break;
        }
    } else {
        switch (D_8010C4CE_merry_go_chomp) {
        case 0:
            if ((rot >= 324.0f) | (rot < 36.0f)) {
                slot = 0;
            }
            if ((rot >= 36.0f) & (rot < 108.0f)) {
                slot = 1;
            }
            if ((rot >= 108.0f) & (rot < 180.0f)) {
                slot = 2;
            }
            if ((rot >= 180.0f) & (rot < 252.0f)) {
                slot = 3;
            }
            if ((rot >= 252.0f) & (rot < 324.0f)) {
                slot = 4;
            }
            break;
        case 1:
            if (rot >= 315.0f) {
                slot = 0;
            }
            if ((rot >= 45.0f) & (rot < 90.0f)) {
                slot = 1;
            }
            if ((rot >= 135.0f) & (rot < 180.0f)) {
                slot = 2;
            }
            if ((rot >= 225.0f) & (rot < 270.0f)) {
                slot = 3;
            }
            break;
        case 2:
            if (rot >= 300.0f) {
                slot = 0;
            }
            if ((rot >= 60.0f) & (rot < 120.0f)) {
                slot = 1;
            }
            if ((rot >= 180.0f) & (rot < 240.0f)) {
                slot = 2;
            }
            break;
        }
        if (slot == 99) {
            return 0;
        }
    }
    if (!(GwPlayer[obj->work[0]].stat & 1) || D_8010C4B2_merry_go_chomp <= 0) {
        if (D_8010C4BE_merry_go_chomp[slot] != 0) {
            ent->unk0A = slot;
            D_8010DECC_merry_go_chomp[ent->unk0A] = obj->work[0];
            D_8010C4BE_merry_go_chomp[slot] = 0;
            return 1;
        }
    } else if ((target = ent->unk0C) == slot) {
        ent->unk0A = slot;
        D_8010DECC_merry_go_chomp[target] = obj->work[0];
        D_8010C4BE_merry_go_chomp[slot] = 0;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106CC4_merry_go_chomp);
#endif

#ifdef NON_MATCHING
/* masked 3: rot and 180.0f swap f20/f22 (one extra nop); work index in v0 not v1 */
void func_80107664_merry_go_chomp(omObjData *obj) {
    McEnt *ent = MC_ENT(MC_ENT_PLAYER, obj->work[0]);
    McPl *pl = &D_8010C420_merry_go_chomp[obj->work[0]];
    f32 rot;

    rot = func_801059BC_merry_go_chomp(MC_ENT(MC_ENT_PLAYER, 20)->obj->rot.y,
                                       -D_8010C1D8_merry_go_chomp[D_8010C4CE_merry_go_chomp][ent->unk0A]);
    rot = func_801059BC_merry_go_chomp(rot, -(D_8010DED4_merry_go_chomp * 15.0f));
    pl->dx = sindf(rot) * 180.0f;
    pl->dz = cosdf(rot) * 180.0f;
    pl->dx = (pl->dx - obj->trans.x) / 15.0f;
    pl->dz = (pl->dz - obj->trans.z) / 15.0f;
    pl->rot = atan2df(pl->dx, pl->dz);
    func_80105D38_merry_go_chomp(obj, 6, 0);
    func_8001C92C_main(obj->model[0], 1.5f);
    ent->unk06 = 6;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80107664_merry_go_chomp);
#endif

void func_801077D0_merry_go_chomp(omObjData *obj) {
    McPl *pl = &D_8010C420_merry_go_chomp[obj->work[0]];

    obj->trans.x += pl->dx;
    obj->trans.z += pl->dz;
    obj->rot.y = pl->rot;
}

void func_80107818_merry_go_chomp(omObjData *obj, f32 *x, f32 *z, f32 scale) {
    f32 rot = obj->rot.y;
    s16 quad = 0;

    if (rot >= 90.0f) {
        quad = 1;
    }
    if (rot >= 180.0f) {
        quad++;
    }
    if (rot >= 270.0f) {
        quad++;
    }
    switch (quad) {
    case 0:
        *x = rot * scale;
        *z = (90.0f - rot) * scale;
        break;
    case 1:
        rot -= 90.0f;
        *x = (90.0f - rot) * scale;
        *z = -(rot * scale);
        break;
    case 2:
        rot -= 180.0f;
        *x = -(rot * scale);
        *z = -(90.0f - rot) * scale;
        break;
    case 3:
        rot -= 270.0f;
        *x = -(90.0f - rot) * scale;
        *z = rot * scale;
        break;
    }
}

s8 func_80107980_merry_go_chomp(void) {
    s8 found = -1;
    s8 i;
    s8 slot;
    McEnt *ent;
    omObjData *obj;
    McPl *pl;
    f32 rot;

    for (i = 0; i < 4; i++) {
        ent = MC_ENT(MC_ENT_PLAYER, i);
        obj = ent->obj;
        if (ent->unk04 == 0) {
            pl = &D_8010C420_merry_go_chomp[i];
            slot = -1;
            rot = func_801059BC_merry_go_chomp(atan2df(obj->trans.x, obj->trans.z), 0.0f);
            switch (D_8010C4CE_merry_go_chomp) {
            case 0:
                if ((rot >= 306.0f) | (rot < 18.0f)) {
                    slot = 0;
                }
                if ((rot >= 18.0f) & (rot < 90.0f)) {
                    slot = 1;
                }
                if ((rot >= 90.0f) & (rot < 162.0f)) {
                    slot = 2;
                }
                if ((rot >= 162.0f) & (rot < 234.0f)) {
                    slot = 3;
                }
                if ((rot >= 234.0f) & (rot < 306.0f)) {
                    found = i;
                }
                break;
            case 1:
                if ((rot >= 315.0f) | (rot < 45.0f)) {
                    slot = 0;
                }
                if ((rot >= 45.0f) & (rot < 135.0f)) {
                    slot = 1;
                }
                if ((rot >= 135.0f) & (rot < 225.0f)) {
                    slot = 2;
                }
                if ((rot >= 225.0f) & (rot < 315.0f)) {
                    found = i;
                }
                break;
            case 2:
                if ((rot >= 330.0f) | (rot < 90.0f)) {
                    slot = 0;
                }
                if ((rot >= 90.0f) & (rot < 210.0f)) {
                    slot = 1;
                }
                if ((rot >= 210.0f) & (rot < 330.0f)) {
                    found = i;
                }
                break;
            }
            pl->slot = slot;
        }
    }
    return found;
}

void func_80107E34_merry_go_chomp(omObjData *obj) {
    s8 player = obj->work[0];
    McEnt *ent = MC_ENT(MC_ENT_PLAYER, player);
    McPl *pl = &D_8010C420_merry_go_chomp[player];

    if (ent->unk04 == 0) {
        switch (pl->state) {
        case 0:
            pl->timer = 0;
            pl->wait = 0;
            pl->x = obj->trans.x;
            pl->z = obj->trans.z;
            pl->speed = 18.0f;
            pl->angle = func_801059BC_merry_go_chomp(atan2df(obj->trans.x, obj->trans.z), 0.0f);
            func_80106B9C_merry_go_chomp(obj, 1);
            pl->state++;
            D_8010C4BD_merry_go_chomp = 0;
            break;
        case 1:
            pl->x += sindf(pl->angle) * pl->speed;
            pl->z += cosdf(pl->angle) * pl->speed;
            if (sqrtf(pl->x * pl->x + pl->z * pl->z) > 350.0f) {
                pl->state++;
            }
            break;
        case 2:
            if (pl->wait != 0) {
                func_80106B9C_merry_go_chomp(obj, 0);
                if (++pl->wait < 16) {
                    break;
                }
                func_80106B9C_merry_go_chomp(obj, 1);
                pl->wait = 0;
            }
            pl->angle = func_801059BC_merry_go_chomp(atan2df(410.0f - pl->x, 100.0f - pl->z), 0.0f);
            pl->x += sindf(pl->angle) * pl->speed;
            pl->z += cosdf(pl->angle) * pl->speed;
            if (pl->speed == 0.0f) {
                func_80106B9C_merry_go_chomp(obj, 0);
            } else {
                func_80106B9C_merry_go_chomp(obj, 1);
            }
            if (pl->x > 390.0f && pl->x < 430.0f && pl->z > 80.0f && pl->z < 120.0f) {
                pl->state++;
            }
            break;
        case 3:
            if (pl->wait != 0) {
                func_80106B9C_merry_go_chomp(obj, 0);
                if (++pl->wait < 16) {
                    break;
                }
                func_80106B9C_merry_go_chomp(obj, 1);
                pl->wait = 0;
            }
            pl->angle = func_801059BC_merry_go_chomp(atan2df(490.0f - pl->x, -20.0f - pl->z), 0.0f);
            pl->x += sindf(pl->angle) * pl->speed;
            pl->z += cosdf(pl->angle) * pl->speed;
            if (pl->speed == 0.0f) {
                func_80106B9C_merry_go_chomp(obj, 0);
            } else {
                func_80106B9C_merry_go_chomp(obj, 1);
            }
            if (pl->x > 470.0f && pl->x < 510.0f && pl->z > -40.0f && pl->z < 0.0f) {
                pl->state++;
                obj->work[1] = D_8010C4BD_merry_go_chomp;
                D_8010C4BD_merry_go_chomp++;
            }
            break;
        case 4:
            func_80106B9C_merry_go_chomp(obj, 2);
            func_8001C258_main(obj->model[1], 4, 4);
            obj->rot.y = 210.0f;
            if (obj->trans.y < 630.0f) {
                obj->trans.y += 10.0f;
            } else {
                obj->trans.y = 630.0f;
                func_80106B9C_merry_go_chomp(obj, 6);
                pl->dx = (D_8010C1B8_merry_go_chomp[obj->work[1]] - pl->x) / 17.0f;
                pl->dz = (D_8010C1C8_merry_go_chomp[obj->work[1]] - pl->z) / 17.0f;
                pl->rot = atan2df(pl->dx, pl->dz);
                pl->timer = 0;
                pl->state++;
            }
            break;
        case 5:
            if (pl->timer == 0) {
                func_8004ACE0_main(0x3A, (s16)obj->work[0]);
            }
            func_8001C258_main(obj->model[1], 4, 0);
            func_801077D0_merry_go_chomp(obj);
            pl->jump = 1;
            obj->trans.y += D_8010C160_merry_go_chomp[pl->timer];
            ent->unk24 = D_8010C174_merry_go_chomp[pl->timer];
            if (++pl->timer >= 17) {
                pl->jump = 0;
                func_80106B9C_merry_go_chomp(obj, 0);
                pl->state++;
                func_8004ACE0_main(0x31, (s16)obj->work[0]);
            }
            break;
        case 6:
            if (func_80105F40_merry_go_chomp(obj, 330.0f)) {
                func_80106B9C_merry_go_chomp(obj, 1);
            } else {
                func_80106B9C_merry_go_chomp(obj, 0);
                D_8010DEDC_merry_go_chomp |= 1 << obj->work[1];
                pl->state++;
            }
            break;
        case 7:
            break;
        }
        if (ent->unk06 == 1) {
            func_80106AF4_merry_go_chomp(obj);
        }
    }
}

#ifdef NON_MATCHING
/* masked 63: retail does not hoist the D_8010C420 base out of the first loop, and hoists the float constants instead */
void func_801084C8_merry_go_chomp(void) {
    s32 mode = 0;
    s32 hit;
    s8 i;
    s8 j;
    McPl *pl;
    McPl *pl2;
    McEnt *ent;
    McEnt *ent2;
    omObjData *obj;
    omObjData *obj2;
    f32 dx;
    f32 dz;
    f32 rot;

    for (i = 0; i < 4; i++) {
        pl = &D_8010C420_merry_go_chomp[i];
        if (pl->state >= 2 && MC_ENT(MC_ENT_PLAYER, i)->unk04 == 0) {
            if (sqrtf(pl->x * pl->x + pl->z * pl->z) < 350.0f) {
                rot = func_801059BC_merry_go_chomp(atan2df(pl->x, pl->z), 0.0f);
                pl->x = sindf(rot) * 350.0f;
                pl->z = cosdf(rot) * 350.0f;
            }
        }
    }
    do {
        hit = 0;
        for (i = 0; i < 4; i++) {
            pl = &D_8010C420_merry_go_chomp[i];
            ent = MC_ENT(MC_ENT_PLAYER, i);
            obj = ent->obj;
            if (ent->unk04 == 0 && !(obj->trans.y > 5.0f)) {
                for (j = 0; j < 4; j++) {
                    if (i == j) {
                        continue;
                    }
                    pl2 = &D_8010C420_merry_go_chomp[j];
                    ent2 = MC_ENT(MC_ENT_PLAYER, j);
                    obj2 = ent2->obj;
                    if (ent2->unk04 != 0) {
                        continue;
                    }
                    dx = pl->x - pl2->x;
                    dz = pl->z - pl2->z;
                    if (sqrtf(dx * dx + dz * dz) < 120.0f) {
                        dx = pl->x - 490.0f;
                        dz = pl->z + 20.0f;
                        rot = sqrtf(dx * dx + dz * dz);
                        dx = pl2->x - 490.0f;
                        dz = pl2->z + 20.0f;
                        if (rot < sqrtf(dx * dx + dz * dz)) {
                            mode = 2;
                        }
                        if (obj->trans.y > 5.0f && obj->trans.y < 160.0f) {
                            mode = 2;
                        }
                        if (obj2->trans.y > 5.0f && obj2->trans.y < 160.0f) {
                            mode = 1;
                        }
                        if (obj->trans.y > 160.0f) {
                            mode = 0;
                        }
                        if (obj2->trans.y > 160.0f) {
                            mode = 0;
                        }
                        switch (mode) {
                        case 1:
                            rot = func_801059BC_merry_go_chomp(atan2df(pl->x - pl2->x, pl->z - pl2->z), 0.0f);
                            pl->x = sindf(rot) * 121.0f + pl2->x;
                            pl->z = cosdf(rot) * 121.0f + pl2->z;
                            hit = 1;
                            pl->wait = 1;
                            break;
                        case 2:
                            rot = func_801059BC_merry_go_chomp(atan2df(pl2->x - pl->x, pl2->z - pl->z), 0.0f);
                            pl2->x = sindf(rot) * 121.0f + pl->x;
                            pl2->z = cosdf(rot) * 121.0f + pl->z;
                            hit = 1;
                            break;
                        }
                    }
                }
            }
        }
    } while (hit);
    for (i = 0; i < 4; i++) {
        pl = &D_8010C420_merry_go_chomp[i];
        ent = MC_ENT(MC_ENT_PLAYER, i);
        obj = ent->obj;
        if (ent->unk04 == 0 && pl->state < 5) {
            obj->trans.x = pl->x;
            obj->trans.z = pl->z;
            obj->rot.y = pl->angle;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801084C8_merry_go_chomp);
#endif

void func_80108A88_merry_go_chomp(omObjData *obj) {
    s8 player = obj->work[0];
    McEnt *ent = MC_ENT(MC_ENT_PLAYER, player);
    McPl *pl = &D_8010C420_merry_go_chomp[player];
    s8 open[5];
    s8 n;
    s8 k;

    switch (ent->unk04) {
    case 2:
        func_8001C92C_main(obj->model[0], 1.0f);
        ent->unk04 = 3;
        break;
    case 0:
        switch (D_8010C4B0_merry_go_chomp) {
        case 0:
            pl->state = 0;
            pl->timer = 0;
            ent->unk0C = -1;
            func_80106B9C_merry_go_chomp(obj, 0);
            break;
        case 1:
            if (D_8010C4B2_merry_go_chomp < 144 && obj->work[1] == D_8010DEDD_merry_go_chomp) {
                if (D_8010C4B2_merry_go_chomp > 0) {
                    if (GwPlayer[player].stat & 1) {
                        if (ent->unk0C < 0) {
                            for (k = 0, n = 0; k < 5 - D_8010C4CE_merry_go_chomp; k++) {
                                if (D_8010C4BE_merry_go_chomp[k] != 0) {
                                    open[n] = k;
                                    n++;
                                }
                            }
                            ent->unk0C = open[func_80105CE4_merry_go_chomp(n)];
                        }
                    } else if (!(D_800D5558_main[obj->work[3]] & 0x8000)) {
                        break;
                    }
                }
                if (func_80106CC4_merry_go_chomp(obj)) {
                    D_8010DEDC_merry_go_chomp = 1;
                    func_80107664_merry_go_chomp(obj);
                }
            }
            break;
        case 2:
            if (obj->work[1] == D_8010DEDD_merry_go_chomp) {
                if (D_8010C4B2_merry_go_chomp == 0) {
                    func_8004ACE0_main(0x3A, (s16)obj->work[0]);
                }
                if (D_8010C4B2_merry_go_chomp < 15) {
                    pl->jump = 1;
                    obj->trans.x += pl->dx;
                    obj->trans.z += pl->dz;
                    obj->trans.y += D_8010C160_merry_go_chomp[D_8010C4B2_merry_go_chomp];
                    obj->rot.y = pl->rot;
                    ent->unk24 = D_8010C174_merry_go_chomp[D_8010C4B2_merry_go_chomp];
                }
                if (D_8010C4B2_merry_go_chomp == 10) {
                    func_80106B9C_merry_go_chomp(obj, 0);
                }
                if (D_8010C4B2_merry_go_chomp == 15) {
                    func_8004ACE0_main(0x31, (s16)obj->work[0]);
                    pl->jump = 0;
                    ent->unk18 = func_801059BC_merry_go_chomp(atan2df(obj->trans.x, obj->trans.z), 0.0f);
                    ent->unk1C = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
                    ent->unk08++;
                }
            } else if (ent->unk08 == 0) {
                func_80106B9C_merry_go_chomp(obj, 1);
                func_80106AF4_merry_go_chomp(obj);
                obj->trans.x -= 7.0f;
                obj->trans.z += 4.0f;
            }
            break;
        case 3:
            func_80106B9C_merry_go_chomp(obj, 0);
            break;
        case 4:
            if (D_8010C4B2_merry_go_chomp < 50) {
                func_80106B9C_merry_go_chomp(obj, 5);
                if (obj->trans.y > 5.0f) {
                    obj->trans.y -= 10.0f;
                } else {
                    obj->trans.y = 5.0f;
                }
            }
            break;
        case 5:
            if (D_8010C4B2_merry_go_chomp < 30) {
                ent->unk08 = 0;
                if (pl->slot == -1) {
                    ent->unk0E = 3 - D_8010C4CE_merry_go_chomp;
                }
            } else if (pl->slot == -1) {
                if (!func_80105F40_merry_go_chomp(obj, 270.0f)) {
                    func_80106B9C_merry_go_chomp(obj, 7);
                    func_8004ACE0_main(0x286, (s16)obj->work[0]);
                    ent->unk04 = 1;
                }
            } else if (!func_80105F40_merry_go_chomp(obj, 0.0f)) {
                if (D_8010C4CE_merry_go_chomp == 2) {
                    D_8010C4C8_merry_go_chomp = obj;
                    func_80106B9C_merry_go_chomp(obj, 0);
                } else {
                    func_80106B9C_merry_go_chomp(obj, 8);
                }
            }
            break;
        case 9:
            func_80107E34_merry_go_chomp(obj);
            break;
        case 6:
            if (!func_80105F40_merry_go_chomp(obj, 0.0f)) {
                func_80106B9C_merry_go_chomp(obj, 8);
            }
            break;
        case 7:
            func_80106B9C_merry_go_chomp(obj, 5);
            break;
        }
        if (ent->unk08 != 0) {
            ent->unk18 = func_801059BC_merry_go_chomp(ent->unk18, -D_8010DED4_merry_go_chomp);
            obj->trans.x = sindf(ent->unk18) * ent->unk1C;
            obj->trans.z = cosdf(ent->unk18) * ent->unk1C;
            obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, -D_8010DED4_merry_go_chomp);
        }
        if (pl->jump == 0) {
            ent->unk20 = obj->trans.y;
        }
        if (obj->trans.y > 505.0f) {
            ent->unk20 = 505.0f;
        }
        if (obj->trans.y <= 5.0f) {
            ent->unk20 = 5.0f;
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, ent->unk20, obj->trans.z);
        Hu3DModelScaleSet(obj->model[1], ent->unk24, 1.0f, ent->unk24);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801090B0_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109420_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109604_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109670_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109A04_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010A9D0_merry_go_chomp);

void func_8010ADE8_merry_go_chomp(void) {
    D_8010C500_merry_go_chomp[10].obj = omAddObj(900, 15, 4, -1, func_8010A9D0_merry_go_chomp);
}

void func_8010AE24_merry_go_chomp(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010AE2C_merry_go_chomp);

void func_8010AECC_merry_go_chomp(void) {
    D_8010C500_merry_go_chomp[30].obj = omAddObj(1000, 1, 1, -1, func_8010AE2C_merry_go_chomp);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010AF08_merry_go_chomp);

void func_8010BAB8_merry_go_chomp(void) {
    u32 i;

    if (D_8010C254_merry_go_chomp == 0) {
        D_8010C254_merry_go_chomp = 1;
        for (i = 0; i < 2; i++) {
            CZoomM[i] = 2023.019f;
            CRotM[i].x = 330.45712f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = 500.0f;
            CenterM[i].z = 140.0f;
        }
    }
}

void func_8010BB7C_merry_go_chomp(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010BBA0_merry_go_chomp(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010BB7C_merry_go_chomp;
    }
}

void func_8010BBD8_merry_go_chomp(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010BBA0_merry_go_chomp;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BC30_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BDE8_merry_go_chomp);

void func_8010BEB4_merry_go_chomp(omObjData *obj) {
}

void func_8010BEBC_merry_go_chomp(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_8010C258_merry_go_chomp[i].scissor[0], D_8010C258_merry_go_chomp[i].scissor[1],
                   D_8010C258_merry_go_chomp[i].scissor[2], D_8010C258_merry_go_chomp[i].scissor[3]);
        ViewportSet(i, D_8010C258_merry_go_chomp[i].viewport[0], D_8010C258_merry_go_chomp[i].viewport[1],
                    D_8010C258_merry_go_chomp[i].viewport[2], D_8010C258_merry_go_chomp[i].viewport[3],
                    D_8010C258_merry_go_chomp[i].viewport[4], D_8010C258_merry_go_chomp[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010C258_merry_go_chomp[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010C030_merry_go_chomp(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(60, 0);
    func_8004A208_main();
    func_8010BEBC_merry_go_chomp();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightDirSet(0, -33.0f, 0.0f, 115.0f);
    HmfLightDirSet(1, -33.0f, 0.0f, 115.0f);
    HmfLightDirSet(2, -33.0f, 0.0f, 115.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010C400_merry_go_chomp, 0);
    func_80045010_main(D_8010C400_merry_go_chomp, 1);
    omAddObj(1500, 0, 0, -1, func_8010BDE8_merry_go_chomp);
    omAddObj(1500, 0, 0, -1, func_8010BBD8_merry_go_chomp);
    func_80105A74_merry_go_chomp();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", D_8010C400_merry_go_chomp);
