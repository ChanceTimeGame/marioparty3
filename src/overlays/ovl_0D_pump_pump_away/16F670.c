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
#include "game/pause.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

typedef func_800E1BA8_minigame_ObjData MgWork;

/* The vertex count of an HmfData (+0x18, inside its unk16 bytes). */
#define PP_HMF_VTXNUM(h) (*(s16 *)&(h)->unk16[2])

/* A colour as three words (sky gradient key colours, D_80110EB8_pump_pump_away). */
typedef struct PpRgb {
    /* 0x00 */ s32 r;
    /* 0x04 */ s32 g;
    /* 0x08 */ s32 b;
} PpRgb;

typedef struct PpTexSize {
    /* 0x00 */ u16 w;
    /* 0x02 */ u16 h;
} PpTexSize;

/* A team's state (D_80111978_pump_pump_away, 2 x 0x34). */
typedef struct PpTeam {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 dist;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 speed;
    /* 0x24 */ s32 state;
    /* 0x28 */ omObjData *obj;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
} PpTeam; // Size 0x34

/* An entity slot (D_80111A30_pump_pump_away, 50 x 0x84; the layout of Coconut Conk's). */
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

extern s32 fontcolor;
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u8 D_800D6A90_main;
extern u8 D_800D2008_main;

extern Vec D_80110EA0_pump_pump_away[];
extern PpRgb D_80110EB8_pump_pump_away[];

extern f32 D_801116E0_pump_pump_away;
extern f32 D_801116E4_pump_pump_away;
extern u32 D_801116F4_pump_pump_away;
extern PpTeam D_80111978_pump_pump_away[2];
extern CcEnt D_80111A30_pump_pump_away[50];
extern s32 D_80113530_pump_pump_away;
extern PpTexSize D_80113548_pump_pump_away[];
extern s32 D_801135E4_pump_pump_away;

void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_80088800_main(f32 *mtx, f32 x, f32 y, f32 z);

s32 func_80110D28_pump_pump_away(void);
void func_801059A0_pump_pump_away(void);
Gfx **func_801059BC_pump_pump_away(Gfx **gfx);
Gfx **func_80105AA0_pump_pump_away(Gfx **gfx);
Gfx **func_80105B6C_pump_pump_away(Gfx **gfx, u8 alpha);
f32 func_80105B9C_pump_pump_away(f32 angle, f32 add);
u8 func_80105C1C_pump_pump_away(s32 max);
void func_80105C54_pump_pump_away(void);
void func_80105D1C_pump_pump_away(s32 player);
f32 func_80105D94_pump_pump_away(f32 x);
void func_80105EE4_pump_pump_away(Vec *from, Vec *to, Vec *out);
void func_80106260_pump_pump_away(u16 x, u16 y, char *str, u16 color);
void func_80106724_pump_pump_away(omObjData *obj);
void func_8010780C_pump_pump_away(omObjData *obj);
void func_8010682C_pump_pump_away(omObjData *obj);
void func_801078EC_pump_pump_away(omObjData *obj);
void func_801068C8_pump_pump_away(omObjData *obj);
void func_80107964_pump_pump_away(omObjData *obj);
void func_80107A8C_pump_pump_away(omObjData *obj);
void func_80108CFC_pump_pump_away(omObjData *obj);
void func_8010AD24_pump_pump_away(omObjData *obj);
void func_80109B80_pump_pump_away(omObjData *obj);
void func_8010A570_pump_pump_away(omObjData *obj);
void func_8010AE40_pump_pump_away(omObjData *obj);
void func_801069D0_pump_pump_away(omObjData *obj);
void func_80106A6C_pump_pump_away(omObjData *obj);
void func_8010ADA0_pump_pump_away(omObjData *obj);
void func_801082AC_pump_pump_away(omObjData *obj);
void func_8010BF14_pump_pump_away(omObjData *obj);
void func_8010BD80_pump_pump_away(omObjData *obj);
void func_8010C060_pump_pump_away(omObjData *obj);
void func_80107338_pump_pump_away(omObjData *obj);
void func_8010A390_pump_pump_away(omObjData *obj);
void func_8010D48C_pump_pump_away(omObjData *obj);
void func_8010C1C8_pump_pump_away(omObjData *obj);
void func_8010811C_pump_pump_away(omObjData *obj);
void func_8010D620_pump_pump_away(omObjData *obj);
void func_8010E6B8_pump_pump_away(omObjData *obj);
void func_8010E98C_pump_pump_away(omObjData *obj);
void func_8010654C_pump_pump_away(omObjData *obj);
void func_8010B630_pump_pump_away(omObjData *obj);
void func_80109D74_pump_pump_away(omObjData *obj);
void func_8010EBC4_pump_pump_away(omObjData *obj);
void func_80107EB8_pump_pump_away(omObjData *obj);
void func_8010A150_pump_pump_away(omObjData *obj);
void func_8010FCF8_pump_pump_away(omObjData *obj);
void func_8010FC64_pump_pump_away(omObjData *obj);
void func_80110034_pump_pump_away(omObjData *obj);
void func_8010921C_pump_pump_away(omObjData *obj);
void func_80110290_pump_pump_away(omObjData *obj);
void func_8010E0F4_pump_pump_away(omObjData *obj);
void func_80110260_pump_pump_away(omObjData *obj);
void func_8010C4D0_pump_pump_away(omObjData *obj);
void func_80110574_pump_pump_away(omObjData *obj);
void func_80109E98_pump_pump_away(omObjData *obj);
void func_801098E0_pump_pump_away(omObjData *obj);
void func_8010FEF8_pump_pump_away(omObjData *obj);
void func_8010D95C_pump_pump_away(omObjData *obj);
void func_8010B370_pump_pump_away(omObjData *obj);
void func_801104BC_pump_pump_away(omObjData *obj);
void func_8010BC14_pump_pump_away(omObjData *obj);
void func_8010FD94_pump_pump_away(omObjData *obj);
void func_8010FEB4_pump_pump_away(omObjData *obj);
void func_8010D1B8_pump_pump_away(omObjData *obj);
void func_8010F688_pump_pump_away(omObjData *obj);
void func_8011038C_pump_pump_away(omObjData *obj);
void func_8010FE6C_pump_pump_away(omObjData *obj);
void func_80108E74_pump_pump_away(omObjData *obj);
void func_80110458_pump_pump_away(omObjData *obj);
void func_80110B34_pump_pump_away(omObjData *obj);
void func_80109C30_pump_pump_away(omObjData *obj);
void func_8010AED4_pump_pump_away(omObjData *obj);
void func_8010C3E0_pump_pump_away(omObjData *obj);
void func_8010FA64_pump_pump_away(omObjData *obj);
void func_8010D6F4_pump_pump_away(omObjData *obj);
void func_8010FF70_pump_pump_away(omObjData *obj);
void func_8010F024_pump_pump_away(omObjData *obj);
void func_8010FD34_pump_pump_away(omObjData *obj);
void func_801102E4_pump_pump_away(omObjData *obj);
void func_80108FE0_pump_pump_away(omObjData *obj);
void func_8010628C_pump_pump_away(omObjData *obj);
void func_8010B274_pump_pump_away(omObjData *obj);
void func_8010A3F0_pump_pump_away(omObjData *obj);
void func_801094CC_pump_pump_away(omObjData *obj);
void func_8010B898_pump_pump_away(omObjData *obj);
void func_8010DC68_pump_pump_away(omObjData *obj);
void func_8010E45C_pump_pump_away(omObjData *obj);
void func_8010FF28_pump_pump_away(omObjData *obj);
void func_8010FA28_pump_pump_away(omObjData *obj);
void func_801103D8_pump_pump_away(omObjData *obj);
void func_8010FE2C_pump_pump_away(omObjData *obj);
void func_8010F268_pump_pump_away(omObjData *obj);
void func_801104F4_pump_pump_away(omObjData *obj);


void func_801059A0_pump_pump_away(void) {
    func_80110D28_pump_pump_away();
}

Gfx **func_801059BC_pump_pump_away(Gfx **gfx) {
    u32 mode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *g = *gfx;

    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                  G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(g++, mode);
    gDPSetCombineMode(g++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetPrimColor(g++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(g++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    *gfx = g;
    return gfx;
}

Gfx **func_80105AA0_pump_pump_away(Gfx **gfx) {
    u32 mode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *g = *gfx;

    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                  G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(g++, mode);
    gDPSetCombineMode(g++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetRenderMode(g++, IM_RD | CVG_DST_FULL | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                     GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    *gfx = g;
    return gfx;
}

Gfx **func_80105B6C_pump_pump_away(Gfx **gfx, u8 alpha) {
    Gfx *g;

    g = *gfx;
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, alpha);
    *gfx = g;
    return gfx;
}

f32 func_80105B9C_pump_pump_away(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

u8 func_80105C1C_pump_pump_away(s32 max) {
    return ((u32)(rand8() * max)) >> 8;
}

void func_80105C54_pump_pump_away(void) {
    CcEnt *ent;
    u32 i;

    for (i = 0, ent = D_80111A30_pump_pump_away; i < 50; i++, ent++) {
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

void func_80105D1C_pump_pump_away(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

f32 func_80105D94_pump_pump_away(f32 x) {
    f32 a;
    f32 b;
    f32 sum;
    s32 sign;
    s32 i;

    sign = 1;
    if (x > 1.0f) {
        x = 1.0f / x;
    } else {
        sign = -1;
        if (x < -1.0f) {
            x = 1.0f / x;
        } else {
            sign = 0;
        }
    }
    sum = 0.0f;
    i = 6;
    do {
        a = (f32)(i * i) * x * x;
        b = (f32)(i * 2 + 1) + sum;
        i--;
        sum = a / b;
    } while (i > 0);
    if (sum != -1.0f) {
        if (sign > 0) {
            return 1.5707963267948966 - (x / (sum + 1.0f));
        }
        if (sign < 0) {
            return -1.5707963267948966 - (x / (sum + 1.0f));
        }
        return x / (sum + 1.0f);
    }
    return 0.0f;
}

void func_80105EE4_pump_pump_away(Vec *from, Vec *to, Vec *out) {
    Vec delta;
    Vec fromV;
    Vec toV;
    f32 horizontal;
    f32 pitch;
    f32 yaw;
    f32 y;
    f32 eps;
    s32 nearPositive;
    s32 nearNegative;

    fromV.x = from->x;
    fromV.y = from->y;
    fromV.z = from->z;
    toV.x = to->x;
    toV.y = to->y;
    toV.z = to->z;
    delta.x = toV.x - fromV.x;
    delta.y = toV.y - fromV.y;
    delta.z = toV.z - fromV.z;
    horizontal = HuSqrtf(delta.x * delta.x + delta.z * delta.z);
    nearPositive = horizontal <= 0.002f;
    nearNegative = horizontal >= -0.002f;
    if (nearPositive & nearNegative) {
        horizontal = 0.0f;
        y = delta.y;
        eps = 0.0001f;
        yaw = horizontal;
        if (!(y > eps) && y < eps) {
            pitch = horizontal;
        } else {
            pitch = 180.0f;
        }
    } else {
        if (delta.x != 0.0f && delta.z != 0.0f) {
            yaw = func_80105D94_pump_pump_away(delta.x / delta.z) * 57.29577951308232;
        } else if (delta.z == 0.0f) {
            if (delta.x >= 0.0f) {
                yaw = 90.0f;
            } else {
                yaw = 270.0f;
            }
        } else {
            yaw = 0.0f;
        }
        if (delta.z < 0.0f) {
            yaw -= 180.0f;
        }
        if (horizontal != 0.0f && delta.y != 0.0f) {
            pitch = func_80105D94_pump_pump_away(delta.y / horizontal) * 57.29577951308232;
        } else {
            pitch = 0.0f;
        }
        yaw = yaw >= 360.0f ? yaw - 360.0f : yaw < 0.0f ? yaw + 360.0f : yaw;
        pitch = pitch + 90.0f >= 360.0f ? pitch + 90.0f - 360.0f : pitch + 90.0f < 0.0f ? pitch + 90.0f + 360.0f : pitch + 90.0f;
    }
    nearPositive = pitch <= 0.002f;
    nearNegative = pitch >= -0.002f;
    if (nearPositive & nearNegative) {
        pitch = 0.0f;
    }
    horizontal = HuSqrtf(delta.y * delta.y + horizontal * horizontal);
    out->z = yaw;
    out->x = horizontal;
}

void func_80106260_pump_pump_away(u16 x, u16 y, char *str, u16 color) {
    fontcolor = color;
    print8(x, y, str);
}

#ifdef NON_MATCHING
void func_8010628C_pump_pump_away(omObjData *obj) {
    f32 scale;
    s32 i;

    switch (D_801116F4_pump_pump_away) {
        case 4:
            if (D_80111978_pump_pump_away[0].dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y -= D_80111978_pump_pump_away[0].speed;
            } else {
                obj->trans.y -= D_80111978_pump_pump_away[1].speed;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (D_80113530_pump_pump_away >= 2) {
        case 7:
                obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
            }
            break;
    }
    for (i = 1; i < 3; i++) {
        scale = D_80111978_pump_pump_away[i - 1].obj->trans.y - obj->trans.y - 200.0f;
        if ((scale > 1000.0f) | (scale < -100.0f)) {
            func_8001C258_main(obj->model[i], 4, 4);
        } else {
            func_8001C258_main(obj->model[i], 4, 0);
            scale = 3.0 - scale * 0.003;
            if (scale >= 3.0) {
                scale = 3.0f;
            }
        }
        Hu3DModelPosSet(obj->model[i], D_80110EA0_pump_pump_away[i - 1].x, obj->trans.y + 1.0, D_80110EA0_pump_pump_away[i - 1].z + 0.0f);
        Hu3DModelScaleSet(obj->model[i], scale, scale, scale);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010628C_pump_pump_away);
#endif

void func_8010654C_pump_pump_away(omObjData *obj) {
    s32 i;

    obj->model[0] = func_8000B108_main(0x2E0000, 0x289);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    for (i = 1; i < 3; i++) {
        obj->model[i] = func_8000B0A0_main(0, 0xC9);
        func_8001C2FC_main(obj->model[i], 0x80000000, 0);
        func_8001C448_main(obj->model[i]);
        func_8001C514_main(obj->model[i]);
        func_80088800_main(HmfModelData[obj->model[i]].mtx, 0.0f, 1.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[i], 3.0f, 3.0f, 3.0f);
        Hu3DModelPosSet(obj->model[i], D_80110EA0_pump_pump_away[i - 1].x, obj->trans.y + 1.0, D_80110EA0_pump_pump_away[i - 1].z + 0.0f);
    }
    obj->func = func_8010628C_pump_pump_away;
}

void func_801066F0_pump_pump_away(void) {
    omAddObj(200, 3, 0, -1, func_8010654C_pump_pump_away);
}

#ifdef NON_MATCHING
void func_80106724_pump_pump_away(omObjData *obj) {
    switch (D_801116F4_pump_pump_away) {
        case 4:
            if (D_80111978_pump_pump_away[0].dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y = obj->trans.y - D_80111978_pump_pump_away[0].speed * 0.9;
            } else {
                obj->trans.y = obj->trans.y - D_80111978_pump_pump_away[1].speed * 0.9;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (D_80113530_pump_pump_away >= 2) {
        case 7:
                obj->trans.x = obj->trans.y = 0.0f;
                obj->trans.z = -1100.0f;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80106724_pump_pump_away);
#endif

void func_8010682C_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E0003, 0x289);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1100.0f;
    obj->func = func_80106724_pump_pump_away;
}

void func_80106894_pump_pump_away(void) {
    omAddObj(250, 1, 0, -1, func_8010682C_pump_pump_away);
}

#ifdef NON_MATCHING
void func_801068C8_pump_pump_away(omObjData *obj) {
    switch (D_801116F4_pump_pump_away) {
        case 4:
            if (D_80111978_pump_pump_away[0].dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y = obj->trans.y - D_80111978_pump_pump_away[0].speed * 0.8;
            } else {
                obj->trans.y = obj->trans.y - D_80111978_pump_pump_away[1].speed * 0.8;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (D_80113530_pump_pump_away >= 2) {
        case 7:
                obj->trans.x = obj->trans.y = 0.0f;
                obj->trans.z = -1290.0f;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801068C8_pump_pump_away);
#endif

void func_801069D0_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E0004, 0x289);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1290.0f;
    obj->func = func_801068C8_pump_pump_away;
}

void func_80106A38_pump_pump_away(void) {
    omAddObj(260, 1, 0, -1, func_801069D0_pump_pump_away);
}

#ifdef NON_MATCHING
void func_80106A6C_pump_pump_away(omObjData *obj) {
    HmfData *hmf = HmfModelData[obj->model[0]].hmf;
    Vtx *v = hmf->unk44[D_800D2008_main];
    PpTeam *t1;
    f32 dist;
    s32 step;
    u32 i;

    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
        case 2:
        case 3:
            for (i = 0; i < PP_HMF_VTXNUM(hmf); i++, v++) {
                if (i == 1 || i == 2) {
                    v->v.cn[0] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].r;
                    v->v.cn[1] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].g;
                    v->v.cn[2] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].b;
                } else {
                    v->v.cn[0] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].r;
                    v->v.cn[1] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].g;
                    v->v.cn[2] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].b;
                }
            }
            break;
        case 4:
            func_8001C258_main(obj->model[0], 4, 0);
            func_8001C258_main(obj->model[1], 4, 4);
            t1 = &D_80111978_pump_pump_away[1];
            if (D_80111978_pump_pump_away[1].dist < D_80111978_pump_pump_away[0].dist) {
                dist = D_80111978_pump_pump_away[0].dist;
            } else {
                dist = t1->dist;
            }
            step = dist * 0.01;
            D_801135E4_pump_pump_away = step * 0.01;
            if (func_80049F98_main() + D_800D6A90_main == 0) {
                if (D_80111978_pump_pump_away[0].dist - t1->dist > 0.0f) {
                    D_801116E0_pump_pump_away = D_80111978_pump_pump_away[0].dist * 1.25e-05;
                    D_801116E4_pump_pump_away = D_801116E4_pump_pump_away - D_80111978_pump_pump_away[0].speed * 0.08;
                } else {
                    D_801116E0_pump_pump_away = t1->dist * 1.25e-05;
                    D_801116E4_pump_pump_away = D_801116E4_pump_pump_away - t1->speed * 0.08;
                }
            }
            for (i = 0; i < PP_HMF_VTXNUM(hmf); i++, v++) {
                if (i == 1 || i == 2) {
                    v->v.cn[0] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].r -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].r - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].r) *
                              ((f32)((D_801135E4_pump_pump_away + 1) * 100 - step) * 0.01));
                    v->v.cn[1] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].g -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].g - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].g) *
                              ((f32)((D_801135E4_pump_pump_away + 1) * 100 - step) * 0.01));
                    v->v.cn[2] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].b -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].b - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].b) *
                              ((f32)((D_801135E4_pump_pump_away + 1) * 100 - step) * 0.01));
                } else {
                    v->v.cn[0] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].r -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].r - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].r) *
                              ((f32)((D_801135E4_pump_pump_away + 2) * 100 - (dist + 10000.0f) * 0.01) * 0.01));
                    v->v.cn[1] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].g -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].g - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].g) *
                              ((f32)((D_801135E4_pump_pump_away + 2) * 100 - (dist + 10000.0f) * 0.01) * 0.01));
                    v->v.cn[2] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].b -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].b - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].b) *
                              ((f32)((D_801135E4_pump_pump_away + 2) * 100 - (dist + 10000.0f) * 0.01) * 0.01));
                }
            }
        case 5:
            func_8001E888_main(obj->model[0], D_801116E4_pump_pump_away, D_801116E4_pump_pump_away, D_80113548_pump_pump_away[0].w, D_80113548_pump_pump_away[0].h,
                               "dammy_0-sky_b_2", 0);
            break;
        case 6:
            if (D_80113530_pump_pump_away >= 2) {
        case 7:
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 0);
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80106A6C_pump_pump_away);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107338_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010745C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010749C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010775C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010780C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801078B4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801078EC_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107964_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107A8C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107B40_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107E5C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107EB8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010811C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801082AC_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108358_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108504_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108560_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108810_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108B0C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108CFC_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108E74_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108FA8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108FE0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010921C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109280_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109470_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801094CC_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801098E0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801099D4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109A50_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109B48_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109B80_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109C30_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109D74_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109E3C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109E98_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010A150_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010A390_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010A3F0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010A468_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010A570_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010AD24_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010ADA0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010AE40_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010AED4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010AF70_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010B274_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010B370_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010B5D4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010B630_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010B898_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010BC14_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010BD80_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010BF14_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010C060_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010C1C8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010C3E0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010C4D0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010C6E4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010CBF0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010CCBC_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010CDF4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010CEE8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D1B8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D458_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D48C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D620_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D6C0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D6F4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D95C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010DC68_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010DD24_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E098_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E0F4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E45C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E65C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E6B8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E98C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010EB68_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010EBC4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F024_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F20C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F268_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F688_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F8A4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F900_pump_pump_away);

void func_8010FA20_pump_pump_away(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FA28_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FA64_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FAA8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FB70_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FC64_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FCF8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FD34_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FD94_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FE2C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FE6C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FEB4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FEF8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FF28_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010FF70_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110034_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801100F0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110260_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110290_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801102E4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8011038C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801103D8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110458_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110498_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801104BC_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801104F4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8011054C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110574_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801105D8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110638_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8011066C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801106AC_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110718_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8011078C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801107C4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801107E4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110824_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110868_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110888_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801108D8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8011091C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8011096C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801109BC_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110A78_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110B34_pump_pump_away);

void func_80110BB0_pump_pump_away(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110BB8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80110D28_pump_pump_away);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", D_801116D8_pump_pump_away);
