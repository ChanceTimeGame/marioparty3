#include "common.h"
// m4 hs: Hide and Sneak (1 vs 3: the solo player hides, the team searches)
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

/* One slot of the overlay's object table (D_8010C7A0_hide_and_sneak, 50 x 0x84). */
typedef struct HsEnt {
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
} HsEnt; // Size 0x84

extern HsEnt D_8010C7A0_hide_and_sneak[50];
#define HS_ENT(base, i) (&(D_8010C7A0_hide_and_sneak + (base))[i])

/* The computer solo player's wander state (func_80106ABC_hide_and_sneak). */
typedef struct HsAuto {
    /* 0x00 */ s8 active;
    /* 0x01 */ s8 state;
    /* 0x02 */ s8 stick;
    /* 0x03 */ s8 count;
    /* 0x04 */ s8 limit;
    /* 0x05 */ s8 turns;
    /* 0x06 */ s8 maxTurns;
    /* 0x07 */ s8 slot;
} HsAuto;

/* .data */
extern s16 D_8010C370_hide_and_sneak[5][4];
extern s32 D_8010C398_hide_and_sneak[8];
/* .bss */
extern s8 D_8010C782_hide_and_sneak;
extern HsAuto D_8010E168_hide_and_sneak;

void func_80105B3C_hide_and_sneak(s32 player);
s32 func_801064F4_hide_and_sneak(s32 max);
void func_801065B0_hide_and_sneak(omObjData *obj, u16 motion, s16 start, s16 end, s16 attr);

void func_8000BC48_main(u16, s32);
omObjData *func_80045ED0_main(u32 arg0);
s32 func_8000B710_main(s32 arg0);
extern u16 D_800D530C_main;
void func_8001C624_main(s16, s16, s16, s16, s16);
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];

f32 func_801059BC_hide_and_sneak(f32 angle, f32 add);
void func_80106730_hide_and_sneak(omObjData *obj);
void func_80106738_hide_and_sneak(omObjData *obj);
void func_8010BCB0_hide_and_sneak(omObjData *obj);
void func_8010BCE8_hide_and_sneak(omObjData *obj);
void func_8010BFE8_hide_and_sneak(omObjData *obj);
void func_8010C0AC_hide_and_sneak(void);
void func_8010C220_hide_and_sneak(void);
void func_80105A74_hide_and_sneak(void);

void func_801059A0_hide_and_sneak(void) {
    func_8010C220_hide_and_sneak();
}

f32 func_801059BC_hide_and_sneak(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

u8 func_80105A3C_hide_and_sneak(s32 max) {
    return ((u32)(rand8() * max)) >> 8;
}

void func_80105A74_hide_and_sneak(void) {
    HsEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010C7A0_hide_and_sneak; i < 50; i++, ent++) {
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

void func_80105B3C_hide_and_sneak(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

#ifdef NON_MATCHING
void func_80105BB4_hide_and_sneak(Gfx **gfx) {
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
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105BB4_hide_and_sneak);
#endif

#ifdef NON_MATCHING
void func_80105C98_hide_and_sneak(Gfx **gfx) {
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
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105C98_hide_and_sneak);
#endif

#ifdef NON_MATCHING
void func_80105D64_hide_and_sneak(Gfx **gfx, u8 alpha) {
    Gfx *g;

    g = *gfx;
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, alpha);
    *gfx = g;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105D64_hide_and_sneak);
#endif

void func_80105D94_hide_and_sneak(f32 x0, f32 z0, f32 x1, f32 z1) {
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
    rot = func_801059BC_hide_and_sneak(atan2df(dx, dz), 0.0f);
    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

#ifdef NON_MATCHING
void func_80105EC4_hide_and_sneak(s32 conNo) {
    s16 i;

    if ((u16)conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x400) {
        for (i = 0; i < 2; i++) {
            CRotM[i].x = func_801059BC_hide_and_sneak(CRotM[i].x, 1.0f);
        }
    }
    /* retail reads player 0's pad here, not conNo's */
    if (D_800CDA7C_main[GwPlayer[0].pad] & 0x800) {
        for (i = 0; i < 2; i++) {
            CRotM[i].x = func_801059BC_hide_and_sneak(CRotM[i].x, -1.0f);
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x200) {
        for (i = 0; i < 2; i++) {
            CRotM[i].y = func_801059BC_hide_and_sneak(CRotM[i].y, 1.0f);
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x100) {
        for (i = 0; i < 2; i++) {
            CRotM[i].y = func_801059BC_hide_and_sneak(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[(s16)conNo] & 0x8000) {
        for (i = 0; i < 2; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x4000) {
        for (i = 0; i < 2; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 2) {
        for (i = 0; i < 2; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 1) {
        for (i = 0; i < 2; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 8) {
        for (i = 0; i < 2; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 4) {
        for (i = 0; i < 2; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if (D_800D5558_main[(s16)conNo] & 0x2000) {
        osSyncPrintf("\n");
        for (i = 0; i < 2; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105EC4_hide_and_sneak);
#endif

s32 func_801064F4_hide_and_sneak(s32 max) {
    return rand8() % max;
}

void func_80106548_hide_and_sneak(omObjData *obj, u16 motion, s16 attr) {
    func_8001C5B4_main(obj->model[0], obj->motion[motion]);
    func_8001C814_main(obj->model[0], attr, attr);
}

void func_801065B0_hide_and_sneak(omObjData *obj, u16 motion, s16 start, s16 end, s16 attr) {
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[motion]].unk02, start, end, attr);
}

s8 func_8010661C_hide_and_sneak(omObjData *obj, f32 rot) {
    f32 cur = obj->rot.y;
    f32 diff = rot - cur;

    if (diff < 0.0f) {
        diff = 0.0f - diff;
    }
    if (diff < 10.0f) {
        obj->rot.y = rot;
        return 0;
    }
    if (cur < rot) {
        if (diff > 180.0f) {
            obj->rot.y = func_801059BC_hide_and_sneak(obj->rot.y, -10.0f);
        } else {
            obj->rot.y = func_801059BC_hide_and_sneak(obj->rot.y, 10.0f);
        }
        return 1;
    }
    if (rot < cur) {
        if (diff > 180.0f) {
            obj->rot.y = func_801059BC_hide_and_sneak(obj->rot.y, 10.0f);
        } else {
            obj->rot.y = func_801059BC_hide_and_sneak(obj->rot.y, -10.0f);
        }
        return 1;
    }
    return 0;
}

void func_80106730_hide_and_sneak(omObjData *obj) {
}

void func_80106738_hide_and_sneak(omObjData *obj) {
    HsEnt *ent = HS_ENT(0, 0);

    ent->pos.x = 160.0f;
    ent->pos.y = 120.0f;
    ent->grp = func_8000B838_main(0x270000);
    ent->spr = InitEspriteSlot(ent->grp, 0, 0);
    func_8000BC48_main(ent->spr, 0x5000);
    func_8000BBD4_main(ent->spr, ent->pos.x, ent->pos.y);
    ent->pos.x = 160.0f;
    ent->pos.y = 231.0f;
    ent->grp = func_8000B838_main(0x270001);
    ent->spr = InitEspriteSlot(ent->grp, 0, 0);
    func_8000BC48_main(ent->spr, 0x1000);
    func_8000BBD4_main(ent->spr, ent->pos.x, ent->pos.y);
    obj->model[0] = func_8000B108_main(0x270003, 0x299);
    obj->model[1] = func_8000B108_main(0x270002, 0x299);
    obj->model[2] = func_8000B108_main(0x27000C, 0x299);
    func_8001C92C_main(obj->model[0], 0.0f);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[2], 4.0f, 0.0f, 0.0f);
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    func_8001C8A8_main(obj->model[2], 1);
    obj->func = func_80106730_hide_and_sneak;
}

void func_80106960_hide_and_sneak(void) {
    D_8010C7A0_hide_and_sneak[0].obj = omAddObj(500, 4, 2, -1, func_80106738_hide_and_sneak);
}

void func_8010699C_hide_and_sneak(omObjData *obj, s8 motion) {
    HsEnt *ent = HS_ENT(1, 0);
    s16 attr = 0;

    if (ent->unk06 != motion) {
        switch (motion) {
            case 0:
            case 1:
            case 3:
                attr = 2;
                break;
            case 2:
            case 4:
            case 5:
            case 6:
            case 7:
                attr = 0;
                break;
        }
        func_8001C92C_main(obj->model[0], 1.0f);
        func_801065B0_hide_and_sneak(obj, motion, 0, 10, attr);
        if (motion == 6) {
            func_80045ED0_main((D_8010C398_hide_and_sneak[GwPlayer[obj->work[0]].chr] << 16) | 0x30);
        }
        ent->unk06 = motion;
    }
}

#ifdef NON_MATCHING
s32 func_80106ABC_hide_and_sneak(omObjData *obj) {
    HsAuto *a = &D_8010E168_hide_and_sneak;
    s8 stick;

    if (a->active != 0) {
        func_80105B3C_hide_and_sneak(obj->work[0]);
        switch (a->state) {
            case 0:
                a->turns = 0;
                a->maxTurns = func_801064F4_hide_and_sneak(9 - D_8010C782_hide_and_sneak);
                a->stick = func_801064F4_hide_and_sneak(2) * 40 - 20;
                a->count = 0;
                a->limit = (D_8010C782_hide_and_sneak - 1) * 9;
                a->slot = func_801064F4_hide_and_sneak(D_8010C782_hide_and_sneak);
                a->state++;
                break;
            case 1:
                D_800CBB6E_main[obj->work[3]] = a->stick;
                a->count++;
                if (a->count >= a->limit) {
                    a->turns++;
                    if (a->turns >= a->maxTurns) {
                        a->state = 2;
                    } else {
                        a->stick = -a->stick;
                        a->count = 0;
                        a->limit = (D_8010C782_hide_and_sneak - 1) * 18;
                    }
                }
                break;
            case 2:
                if (D_8010C370_hide_and_sneak[D_8010C782_hide_and_sneak][a->slot] < obj->trans.x) {
                    stick = -20;
                } else if (obj->trans.x < D_8010C370_hide_and_sneak[D_8010C782_hide_and_sneak][a->slot]) {
                    stick = 20;
                } else {
                    if (obj->trans.x == D_8010C370_hide_and_sneak[D_8010C782_hide_and_sneak][a->slot]) {
                        a->state = 0;
                        return 1;
                    }
                    break;
                }
                D_800CBB6E_main[obj->work[3]] = stick;
                break;
            default:
                return 0;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106ABC_hide_and_sneak);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106D10_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107638_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801078E4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801079E8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107B30_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107BD8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107CF4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107D98_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107EF0_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108040_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108130_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108278_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010841C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108588_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108670_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801087B4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801088A0_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108990_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108AF0_hide_and_sneak);

s32 func_80108BD8_hide_and_sneak(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108BE0_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109578_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801095DC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109688_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109870_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109BF4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109D88_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A1CC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A48C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A6BC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A7A4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A824_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A88C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010AAC8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010ABC8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010AC78_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010ACB8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010ACC4_hide_and_sneak);

void func_8010AF98_hide_and_sneak(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010AFA0_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B0D0_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B118_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B33C_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C670_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C680_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C694_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6A4_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6B8_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6C8_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6DC_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6EC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B410_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B55C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B600_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BBBC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BC8C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BCB0_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BCE8_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BD40_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BFE8_hide_and_sneak);

void func_8010C0A4_hide_and_sneak(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010C0AC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010C220_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C754_hide_and_sneak);
