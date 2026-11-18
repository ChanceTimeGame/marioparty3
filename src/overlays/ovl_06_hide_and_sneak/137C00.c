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
#define ABS(x) ((x) < 0 ? -(x) : (x))

#define HS_ENT_TITLE 0
#define HS_ENT_SOLO 1
#define HS_ENT_SEEKER 2 /* 3 */
#define HS_ENT_BOX 5    /* 4 */
#define HS_ENT_MARK 9   /* 4 */
#define HS_ENT_FADE 13
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

/* A seeker's search state (D_8010C788_hide_and_sneak, 4 x 6). */
typedef struct HsSeeker {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 step;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
} HsSeeker;

/* A camera (D_8010C4C0_hide_and_sneak). */
typedef struct HsCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} HsCamera; // Size 0x2C

/* Who searched a box, in order (D_8010E188_hide_and_sneak). */
typedef struct HsBoxLog {
    /* 0x00 */ u8 count;
    /* 0x01 */ s8 seeker[3];
} HsBoxLog;

/* A box number sprite (D_8010C760_hide_and_sneak, 4 x 8). */
typedef struct HsNumSpr {
    /* 0x00 */ s16 grp;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 unk06;
} HsNumSpr;

/* .data */
extern s16 D_8010C370_hide_and_sneak[5][4];
extern s32 D_8010C398_hide_and_sneak[8];
extern f32 D_8010C3E4_hide_and_sneak[4];
extern f32 D_8010C3F4_hide_and_sneak[4];
extern s16 D_8010C474_hide_and_sneak[4];
extern char *D_8010C47C_hide_and_sneak[4];
extern char *D_8010C48C_hide_and_sneak[4];
extern s16 D_8010C49C_hide_and_sneak[4];
extern s16 D_8010C4A4_hide_and_sneak[4][2];
extern s16 D_8010C4B4_hide_and_sneak[4];
extern s32 D_8010C4BC_hide_and_sneak;
extern HsCamera D_8010C4C0_hide_and_sneak[2];
/* .rodata */
extern const s16 D_8010C754_hide_and_sneak[];
/* .bss */
extern HsNumSpr D_8010C760_hide_and_sneak[4];
extern s8 D_8010C780_hide_and_sneak;
extern s8 D_8010C782_hide_and_sneak;
extern HsSeeker D_8010C788_hide_and_sneak[4];
extern HsAuto D_8010E168_hide_and_sneak;
extern s8 D_8010E169_hide_and_sneak; /* view: D_8010E168_hide_and_sneak.state */
extern s8 D_8010E182_hide_and_sneak[4];
extern u8 D_8010E186_hide_and_sneak;
extern u8 D_8010E1A8_hide_and_sneak;
extern u8 D_8010E1A9_hide_and_sneak[3]; /* D_8010E1A8_hide_and_sneak[1..3]? */
extern s16 D_8010CE58_hide_and_sneak; /* view: D_8010C7A0_hide_and_sneak[HS_ENT_FADE].unk04 */
extern u8 D_8010CE59_hide_and_sneak; /* view: the low byte of D_8010CE58_hide_and_sneak */
extern s8 D_8010E170_hide_and_sneak;
extern s8 D_8010E174_hide_and_sneak;
extern s16 D_8010E17A_hide_and_sneak;
extern s8 D_8010E17C_hide_and_sneak;
extern s8 D_8010E180_hide_and_sneak;
extern HsBoxLog D_8010E188_hide_and_sneak[4];
extern HuSprite_Unk84_Struct *D_8010E198_hide_and_sneak[4];
extern u8 D_8010E17D_hide_and_sneak[3];
extern u8 D_8010E1AE_hide_and_sneak[3];
extern s8 D_8010E1AC_hide_and_sneak;
extern s8 D_8010E1AD_hide_and_sneak;
extern s8 D_8010E1B2_hide_and_sneak;
extern s8 D_8010E1B3_hide_and_sneak;

void func_80105B3C_hide_and_sneak(s32 player);
s32 func_801064F4_hide_and_sneak(s32 max);
void func_801065B0_hide_and_sneak(omObjData *obj, u16 motion, s16 start, s16 end, s16 attr);

void func_8000BC48_main(u16, s32);
extern s32 D_800A178C_main[][6];
void func_80088800_main(f32 *mtx, f32 x, f32 y, f32 z);
void func_80106D10_hide_and_sneak(omObjData *obj);
void func_80106960_hide_and_sneak(void);
void func_801078E4_hide_and_sneak(void);
void func_8010A48C_hide_and_sneak(void);
void func_8010A6BC_hide_and_sneak(omObjData *obj);
void func_8010A1CC_hide_and_sneak(omObjData *obj);
Gfx **func_80105BB4_hide_and_sneak(Gfx **gfx);
Gfx **func_80105C98_hide_and_sneak(Gfx **gfx);
Gfx **func_80105D64_hide_and_sneak(Gfx **gfx, u8 alpha);
void func_80107B30_hide_and_sneak(omObjData *obj);
void func_80109D88_hide_and_sneak(omObjData *obj);
extern u8 D_800D6A90_main;
void func_8010ACC4_hide_and_sneak(Gfx **gfx, s32 arg1, s32 arg2);
void func_8010AF98_hide_and_sneak(omObjData *obj);
void func_8010B33C_hide_and_sneak(omObjData *obj);
void func_8010A88C_hide_and_sneak(omObjData *obj);
void func_8010AAC8_hide_and_sneak(omObjData *obj);
void func_8010ABC8_hide_and_sneak(void);
void func_8010AFA0_hide_and_sneak(omObjData *obj);
void func_8010B0D0_hide_and_sneak(void);
void func_8010B410_hide_and_sneak(omObjData *obj);
void func_8010B55C_hide_and_sneak(void);
void func_8010BBBC_hide_and_sneak(void);
void func_8010BC8C_hide_and_sneak(omObjData *obj);
void func_8010BD40_hide_and_sneak(omObjData *obj);
void func_8000B5F0_main(u8 arg0);
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void osViBlack(u8 active);
void func_8004AB0C_main(s32);
void func_80107638_hide_and_sneak(omObjData *obj);
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
Gfx **func_80105BB4_hide_and_sneak(Gfx **gfx) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105BB4_hide_and_sneak);
#endif

#ifdef NON_MATCHING
Gfx **func_80105C98_hide_and_sneak(Gfx **gfx) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105C98_hide_and_sneak);
#endif

Gfx **func_80105D64_hide_and_sneak(Gfx **gfx, u8 alpha) {
    Gfx *g;

    g = *gfx;
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, alpha);
    *gfx = g;
    return gfx;
}

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

void func_80107638_hide_and_sneak(omObjData *obj) {
    u16 chr = GwPlayer[obj->work[0]].chr;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2B9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x14));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x6C));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x3A));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x30));
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0x36));
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(HmfModelData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.y = 180.0f;
    func_80106548_hide_and_sneak(obj, 0, 2);
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    D_8010E168_hide_and_sneak.active = GwPlayer[obj->work[0]].stat & 1;
    D_8010E169_hide_and_sneak = 0;
    obj->work[3] = GwPlayer[obj->work[0]].pad;
    obj->func = func_80106D10_hide_and_sneak;
}

#ifdef NON_MATCHING
void func_801078E4_hide_and_sneak(void) {
    omObjData *obj;
    s16 i;
    s32 player;
    s32 unused[2];

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
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
        default:
            player = 0;
            break;
    }
    obj = omAddObj(700, 3, 10, -1, func_80107638_hide_and_sneak);
    obj->work[0] = player;
    HS_ENT(1, 0)->obj = obj;
    D_8010E1A8_hide_and_sneak = obj->work[0];
    D_8010E186_hide_and_sneak = GwPlayer[obj->work[0]].chr;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801078E4_hide_and_sneak);
#endif

void func_801079E8_hide_and_sneak(omObjData *obj) {
    s8 i;

    for (i = 0; i < 4; i++) {
        if (D_8010E182_hide_and_sneak[i] != 0) {
            if (D_8010C3E4_hide_and_sneak[i] - 150.0f < obj->trans.x && obj->trans.x < D_8010C3E4_hide_and_sneak[i] + 150.0f
                && D_8010C3F4_hide_and_sneak[i] - 20.0f < obj->trans.z && obj->trans.z < D_8010C3F4_hide_and_sneak[i] + 100.0f) {
                func_8001C258_main(obj->model[0], 4, 4);
                return;
            }
            func_8001C258_main(obj->model[0], 4, 0);
        }
    }
}

void func_80107B30_hide_and_sneak(omObjData *obj) {
    HsEnt *ent = HS_ENT(2, obj->work[1]);

    if (obj->work[2] == 0) {
        if (ent->unk14 != 0) {
            HuAudFXStop(ent->unk14);
        }
        ent->unk14 = func_8004ACE0_main(0x28, (s16)obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 11;
}

void func_80107BD8_hide_and_sneak(omObjData *obj, s8 motion) {
    HsEnt *ent = HS_ENT(2, obj->work[0]);
    s8 attr = 0;

    if (ent->unk06 != motion) {
        switch (motion) {
            case 0:
                attr = 2;
                break;
            case 1:
                attr = 2;
                break;
            case 2:
                attr = 2;
                break;
            case 3:
                attr = 0;
                break;
            case 4:
                attr = 0;
                break;
        }
        func_801065B0_hide_and_sneak(obj, motion, 0, 15, attr);
        func_8001C92C_main(obj->model[0], 1.0f);
        ent->unk06 = motion;
        if (motion == 4) {
            func_80045ED0_main((D_8010C398_hide_and_sneak[GwPlayer[obj->work[0]].chr] << 16) | 0x30);
        }
    }
}

s8 func_80107CF4_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];
    s8 list[4];
    s8 i;
    s8 n;

    for (i = 0, n = 0; i < 4; i++) {
        if (D_8010E182_hide_and_sneak[i] != 0 && s->unk04 != i) {
            list[n] = i;
            n++;
        }
    }
    return list[func_801064F4_hide_and_sneak(n)];
}

s32 func_80107D98_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (-700.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = -700.0f;
                s->step++;
            }
            break;
        case 1:
            if (-1600.0f < obj->trans.z) {
                obj->trans.z -= 24.0f;
                obj->rot.y = 180.0f;
            } else {
                obj->trans.z = -1600.0f;
                s->step++;
            }
            break;
        case 2:
            if (obj->trans.x < -250.0f) {
                obj->trans.x += 24.0f;
                obj->rot.y = 90.0f;
            } else {
                obj->trans.x = -250.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80107EF0_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (-600.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = -600.0f;
                s->step++;
            }
            break;
        case 1:
            if (obj->trans.z < -850.0f) {
                obj->trans.z += 24.0f;
                obj->rot.y = 0.0f;
            } else {
                obj->trans.z = -850.0f;
                s->step++;
            }
            break;
        case 2:
            if (obj->trans.x < -400.0f) {
                obj->trans.x += 24.0f;
                obj->rot.y = 90.0f;
            } else {
                obj->trans.x = -400.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108040_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (obj->trans.x < 0.0f) {
                obj->trans.x += 24.0f;
                obj->rot.y = 90.0f;
            } else {
                obj->trans.x = 150.0f;
                s->step++;
            }
            break;
        case 1:
            if (obj->trans.z < -575.0f) {
                obj->trans.z += 24.0f;
                obj->rot.y = 0.0f;
            } else {
                obj->trans.z = -575.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108130_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (-50.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = -50.0f;
                s->step++;
            }
            break;
        case 1:
            if (-850.0f < obj->trans.z) {
                obj->trans.z -= 24.0f;
                obj->rot.y = 180.0f;
            } else {
                obj->trans.z = -850.0f;
                s->step++;
            }
            break;
        case 2:
            if (-400.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = -400.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108278_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (-1100.0f < obj->trans.z) {
                obj->trans.z -= 24.0f;
                obj->rot.y = 180.0f;
            } else {
                obj->trans.z = -1100.0f;
                s->step++;
            }
            break;
        case 1:
            if (obj->trans.x < 60.0f) {
                obj->trans.x += 24.0f;
                obj->rot.y = 90.0f;
            } else {
                obj->trans.x = 60.0f;
                s->step++;
            }
            break;
        case 2:
            if (-1350.0f < obj->trans.z) {
                obj->trans.z -= 24.0f;
                obj->rot.y = 180.0f;
            } else {
                obj->trans.z = -1350.0f;
                s->step++;
            }
            break;
        case 3:
            if (obj->trans.x < 475.0f) {
                obj->trans.x += 24.0f;
                obj->rot.y = 90.0f;
            } else {
                obj->trans.x = 475.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_8010841C_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (150.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = 150.0f;
                s->step++;
            }
            break;
        case 1:
            if (obj->trans.z < -1200.0f) {
                obj->trans.z += 24.0f;
                obj->rot.y = 0.0f;
            } else {
                obj->trans.z = -1200.0f;
                s->step++;
            }
            break;
        case 2:
            if (-400.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = -400.0f;
                s->step++;
            }
            break;
        case 3:
            if (obj->trans.z < -850.0f) {
                obj->trans.z += 24.0f;
                obj->rot.y = 0.0f;
            } else {
                obj->trans.z = -850.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108588_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (obj->trans.x < 150.0f) {
                obj->trans.x += 24.0f;
                obj->rot.y = 90.0f;
            } else {
                obj->trans.x = 150.0f;
                s->step++;
            }
            break;
        case 1:
            if (obj->trans.z < -575.0f) {
                obj->trans.z += 24.0f;
                obj->rot.y = 0.0f;
            } else {
                obj->trans.z = -575.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108670_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (60.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = 60.0f;
                s->step++;
            }
            break;
        case 1:
            if (-1600.0f < obj->trans.z) {
                obj->trans.z -= 24.0f;
                obj->rot.y = 180.0f;
            } else {
                obj->trans.z = -1600.0f;
                s->step++;
            }
            break;
        case 2:
            if (-250.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = -250.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_801087B4_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (obj->trans.x < 475.0f) {
                obj->trans.x += 24.0f;
                obj->rot.y = 90.0f;
            } else {
                obj->trans.x = 475.0f;
                s->step++;
            }
            break;
        case 1:
            if (obj->trans.z < -1350.0f) {
                obj->trans.z += 24.0f;
                obj->rot.y = 0.0f;
            } else {
                obj->trans.z = -1350.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_801088A0_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (-1600.0f < obj->trans.z) {
                obj->trans.z -= 24.0f;
                obj->rot.y = 180.0f;
            } else {
                obj->trans.z = -1600.0f;
                s->step++;
            }
            break;
        case 1:
            if (-250.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = -250.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108990_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (60.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = 60.0f;
                s->step++;
            }
            break;
        case 1:
            if (-1350.0f < obj->trans.z) {
                obj->trans.z -= 24.0f;
                obj->rot.y = 180.0f;
            } else {
                obj->trans.z = -1350.0f;
                s->step++;
            }
            break;
        case 2:
            if (obj->trans.x < 475.0f) {
                obj->trans.x += 24.0f;
                obj->rot.y = 90.0f;
            } else {
                obj->trans.x = 475.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108AF0_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];

    switch (s->step) {
        case 0:
            if (150.0f < obj->trans.x) {
                obj->trans.x -= 24.0f;
                obj->rot.y = 270.0f;
            } else {
                obj->trans.x = 150.0f;
                s->step++;
            }
            break;
        case 1:
            if (obj->trans.z < -575.0f) {
                obj->trans.z += 24.0f;
                obj->rot.y = 0.0f;
            } else {
                obj->trans.z = -575.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108BD8_hide_and_sneak(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108BE0_hide_and_sneak);

void func_80109578_hide_and_sneak(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010E188_hide_and_sneak[i].seeker[0] = -1;
        D_8010E188_hide_and_sneak[i].seeker[1] = -1;
        D_8010E188_hide_and_sneak[i].seeker[2] = -1;
        D_8010E188_hide_and_sneak[i].count = 0;
    }
}

void func_801095DC_hide_and_sneak(void) {
    HsEnt *ent;
    s8 i;
    s8 box;

    for (i = 0; i < 3; i++) {
        ent = HS_ENT(HS_ENT_SEEKER, i);
        if (ent->unk04 == 0 && ent->unk08 != -1) {
            /* the box number is the low byte of unk08 */
            box = ((s8 *)&ent->unk08)[1];
            D_8010E188_hide_and_sneak[box].seeker[i] = D_8010E188_hide_and_sneak[box].count;
            D_8010E188_hide_and_sneak[box].count++;
        }
    }
}

#ifdef NON_MATCHING
void func_80109688_hide_and_sneak(omObjData *obj) {
    HsEnt *ent = HS_ENT(HS_ENT_SEEKER, obj->work[1]);
    s8 port = obj->work[3];
    s8 list[4];
    s8 i;
    s8 n;
    u8 sx;
    u8 sy;
    s16 ax;
    s16 ay;

    if (GwPlayer[obj->work[0]].stat & 1) {
        if (ent->unk08 == -1) {
            for (i = 0, n = 0; i < 4; i++) {
                if (D_8010E182_hide_and_sneak[i] != 0) {
                    list[n] = i;
                    n++;
                }
            }
            ent->unk08 = list[func_801064F4_hide_and_sneak(n)];
        }
    } else {
        sx = D_800CBB6E_main[port];
        sy = D_800D20A1_main[port];
        if (ABS((s8)sx) >= 11 || ABS((s16)(s8)sy) >= 11) {
            ax = ABS((s16)(s8)sx);
            ay = ABS((s16)(s8)sy);
            if (ay < ax) {
                if ((s16)(s8)sx < 0 && D_8010E182_hide_and_sneak[0] != 0) {
                    ent->unk08 = 0;
                }
                if ((s16)(s8)sx > 0 && D_8010E182_hide_and_sneak[3] != 0) {
                    ent->unk08 = 3;
                }
            } else {
                if ((s16)(s8)sy > 0 && D_8010E182_hide_and_sneak[1] != 0) {
                    ent->unk08 = 1;
                }
                if ((s16)(s8)sy < 0 && D_8010E182_hide_and_sneak[2] != 0) {
                    ent->unk08 = 2;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109688_hide_and_sneak);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109870_hide_and_sneak);

#ifdef NON_MATCHING
s32 func_80109BF4_hide_and_sneak(omObjData *obj) {
    HsEnt *ent = HS_ENT(HS_ENT_SEEKER, obj->work[1]);
    s32 dist;

    if (ent->unk04 == 0) {
        return 0;
    }
    if (ent->unk04 == 2) {
        return 1;
    }
    func_80107B30_hide_and_sneak(obj);
    if (ent->unk0C != 0) {
        ent->unk0C--;
    } else {
        if (ent->unk16 == 0) {
            ent->unk16++;
            func_8004ACE0_main(0x286, (s16)obj->work[0]);
        }
        dist = obj->trans.x;
        if (dist < 0) {
            dist = -dist;
        }
        if (dist > 1000) {
            ent->unk04 = 2;
            func_8001C258_main(obj->model[0], 4, 4);
            func_8001C258_main(obj->model[1], 4, 4);
            D_8010E1A9_hide_and_sneak[obj->work[1]] = 0;
            return 1;
        }
        if (obj->trans.x < 0.0f) {
            obj->rot.y = 270.0f;
            obj->trans.x -= 24.0f;
        } else {
            obj->rot.y = 90.0f;
            obj->trans.x += 24.0f;
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109BF4_hide_and_sneak);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109D88_hide_and_sneak);

void func_8010A1CC_hide_and_sneak(omObjData *obj) {
    HsSeeker *s = &D_8010C788_hide_and_sneak[obj->work[1]];
    u16 chr = GwPlayer[obj->work[0]].chr;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2B9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 2));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x79));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x30));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x70));
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(HmfModelData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    switch (obj->work[1]) {
        case 0:
            obj->trans.x = -220.0f;
            break;
        case 1:
            obj->trans.x = 0.0f;
            break;
        case 2:
            obj->trans.x = 220.0f;
            break;
    }
    obj->trans.y = 125.0f;
    obj->trans.z = -300.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    func_80106548_hide_and_sneak(obj, 0, 2);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    s->unk00 = 0;
    s->step = 0;
    s->unk02 = func_801064F4_hide_and_sneak(2);
    s->unk03 = 0;
    s->unk04 = 0;
    s->unk05 = 0;
    obj->work[3] = GwPlayer[obj->work[0]].pad;
    obj->func = func_80109D88_hide_and_sneak;
}

#ifdef NON_MATCHING
void func_8010A48C_hide_and_sneak(void) {
    omObjData *obj;
    HsEnt *ent;
    s8 *slot;
    s8 order[3];
    s8 player;
    s8 n;
    s8 i;
    s8 j;

    player = 0;
    n = 0;
    for (i = 0; i < 3; i++) {
        order[i] = i;
    }
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
            ent = HS_ENT(HS_ENT_SEEKER, n);
            obj = omAddObj(600, 3, 6, -1, func_8010A1CC_hide_and_sneak);
            obj->work[0] = player;
            ent->obj = obj;
            D_8010E17D_hide_and_sneak[n] = obj->work[0];
            D_8010E1AE_hide_and_sneak[n] = GwPlayer[obj->work[0]].chr;
            slot = &order[func_801064F4_hide_and_sneak(3 - n)];
            obj->work[1] = *slot;
            *slot = -1;
            for (j = 1; j < 3 - n; j++) {
                if (order[j - 1] == -1) {
                    order[j - 1] = order[j];
                    order[j] = -1;
                }
            }
            n++;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A48C_hide_and_sneak);
#endif

void func_8010A6BC_hide_and_sneak(omObjData *obj) {
    HsEnt *ent = HS_ENT(HS_ENT_BOX, obj->work[0]);

    func_8001E888_main(obj->model[0], 0.0f, ent->unk04, 0x60, 0x40, D_8010C47C_hide_and_sneak[obj->work[0]], 0);
    func_8001E888_main(obj->model[0], 0.0f, ent->unk04, 0x60, 0x40, D_8010C48C_hide_and_sneak[obj->work[0]], 0);
}

s32 func_8010A7A4_hide_and_sneak(void) {
    s8 i;
    s8 open;
    s8 used;

    for (i = 0, open = 0, used = 0; i < 4; i++) {
        if (HS_ENT(HS_ENT_BOX, i)->unk04 == 0) {
            open++;
        }
        if (D_8010E182_hide_and_sneak[i] != 0) {
            used++;
        }
    }
    return open == used;
}

s32 func_8010A824_hide_and_sneak(void) {
    s8 i;
    s8 n;

    for (i = 0, n = 0; i < 4; i++) {
        if (HS_ENT(HS_ENT_BOX, i)->unk04 == -0x40) {
            n++;
        }
    }
    return n == 4;
}

#ifdef NON_MATCHING
void func_8010A88C_hide_and_sneak(omObjData *obj) {
    s8 i = obj->work[0];
    HsEnt *ent = HS_ENT(HS_ENT_BOX, i);

    switch (D_8010E1B3_hide_and_sneak) {
        case 1:
            if (i == D_8010E17C_hide_and_sneak) {
                if (ent->unk16 == 0) {
                    HuAudFXPlay(0x32C);
                    ent->unk16++;
                }
                if (ent->unk04 < -63) {
                    ent->unk04 = -64;
                    D_8010E182_hide_and_sneak[i] = 0;
                    D_8010C760_hide_and_sneak[i].unk06 = 1;
                    ent->unk08++;
                    if (ent->unk08 >= 21) {
                        D_8010E1B3_hide_and_sneak = 2;
                    }
                } else {
                    goto shrink;
                }
            }
            break;
        case 2:
            if (D_8010E1AC_hide_and_sneak == 0) {
                HuAudFXPlay(0x327);
                D_8010E1AC_hide_and_sneak = 1;
            }
            if (ent->unk04 < -63) {
                ent->unk04 = -64;
            } else {
            shrink:
                if (func_80049F98_main() + D_800D6A90_main == 0) {
                    ent->unk04 -= 4;
                }
            }
            break;
        case 3:
            if (D_8010E1AC_hide_and_sneak != 0) {
                HuAudFXPlay(0x327);
                D_8010E1AC_hide_and_sneak = 0;
            }
            if (D_8010E182_hide_and_sneak[i] != 0) {
                if (ent->unk04 >= 0) {
                    ent->unk04 = 0;
                } else if (func_80049F98_main() + D_800D6A90_main == 0) {
                    ent->unk04 += 4;
                }
            }
            break;
    }
    switch (D_8010C780_hide_and_sneak) {
        case 0:
        case 1:
        case 4:
        case 5:
        case 6:
        case 7:
            func_8010A6BC_hide_and_sneak(obj);
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A88C_hide_and_sneak);
#endif

void func_8010AAC8_hide_and_sneak(omObjData *obj) {
    s8 i = obj->work[0];
    HsEnt *ent = HS_ENT(HS_ENT_BOX, i);

    obj->model[0] = func_8000B108_main(D_8010C474_hide_and_sneak[i] | 0x270000, 0x1689);
    obj->trans.z = -10.0f;
    if (i == 1) {
        obj->trans.x = -10.0f;
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C954_main(obj->model[0]);
    ent->unk04 = -0x40;
    func_8010A6BC_hide_and_sneak(obj);
    D_8010E182_hide_and_sneak[i] = 1;
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_8010A88C_hide_and_sneak;
}

void func_8010ABC8_hide_and_sneak(void) {
    omObjData *obj;
    HsEnt *ent;
    s8 i;

    for (i = 0; i < 4; i++) {
        ent = HS_ENT(HS_ENT_BOX, i);
        obj = omAddObj(800, 2, 1, -1, func_8010AAC8_hide_and_sneak);
        obj->work[0] = i;
        ent->obj = obj;
        omSetStatBit(obj, 0xA0);
    }
}

void func_8010AC78_hide_and_sneak(void) {
    HsEnt *ent = HS_ENT(HS_ENT_FADE, 0);

    if (D_8010CE58_hide_and_sneak < 255) {
        D_8010CE58_hide_and_sneak += 26;
    } else {
        ent->unk04 = 255;
    }
}

void func_8010ACB8_hide_and_sneak(void) {
    D_8010CE58_hide_and_sneak = 0;
}

#ifdef NON_MATCHING
void func_8010ACC4_hide_and_sneak(Gfx **arg0, s32 arg1, s32 arg2) {
    Gfx **gfx;
    s8 i;
    Gfx *g;

    if (D_8010CE58_hide_and_sneak < 255) {
        gfx = func_80105D64_hide_and_sneak(func_80105C98_hide_and_sneak(arg0), D_8010CE59_hide_and_sneak);
        if (D_8010CE58_hide_and_sneak == 0) {
            return;
        }
    } else {
        gfx = func_80105BB4_hide_and_sneak(arg0);
    }
    g = *gfx;
    gDPSetTextureLUT(g++, G_TT_RGBA16);
    for (i = 0; i < 4; i++) {
        if (D_8010C760_hide_and_sneak[i].unk06 == 0) {
            gDPLoadTLUT_pal16(g++, 0, D_8010E198_hide_and_sneak[i]->unk0C);
            gDPSetTextureImage(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 16, D_8010E198_hide_and_sneak[i]->unk08);
            gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(g++);
            gDPLoadTile(g++, G_TX_LOADTILE, 0, 0, 0x40, 0x80);
            gDPPipeSync(g++);
            gDPSetTile(g++, G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 0x80, 0x80);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 0x80, 0x80);
            gSPTextureRectangle(g++, D_8010C760_hide_and_sneak[i].x * 4, D_8010C760_hide_and_sneak[i].y * 4,
                                (D_8010C760_hide_and_sneak[i].x + 32) * 4, (D_8010C760_hide_and_sneak[i].y + 32) * 4,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
    }
    *gfx = g;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010ACC4_hide_and_sneak);
#endif

void func_8010AF98_hide_and_sneak(omObjData *obj) {
}

void func_8010AFA0_hide_and_sneak(omObjData *obj) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010C760_hide_and_sneak[i].grp = func_8000B838_main(D_8010C49C_hide_and_sneak[i] | 0x270000);
        D_8010C760_hide_and_sneak[i].x = D_8010C4A4_hide_and_sneak[i][0];
        D_8010C760_hide_and_sneak[i].y = D_8010C4A4_hide_and_sneak[i][1];
        D_8010C760_hide_and_sneak[i].unk06 = 0;
        D_8010E198_hide_and_sneak[i] = func_80055194_main(D_8010C760_hide_and_sneak[i].grp);
    }
    func_8001C8A8_main(func_8001AC8C_main(0, func_8010ACC4_hide_and_sneak, 2), 1);
    obj->func = func_8010AF98_hide_and_sneak;
}

void func_8010B0D0_hide_and_sneak(void) {
    omObjData *obj = omAddObj(1000, 2, 1, -1, func_8010AFA0_hide_and_sneak);

    HS_ENT(HS_ENT_FADE, 0)->obj = obj;
    omSetStatBit(obj, 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B118_hide_and_sneak);

void func_8010B33C_hide_and_sneak(omObjData *obj) {
    if (D_8010E180_hide_and_sneak >= 3) {
        if (obj->trans.y > -160.0f) {
            obj->trans.y -= 4.0f;
        }
    } else {
        switch (D_8010C780_hide_and_sneak) {
            case 1:
                if (obj->trans.y > -160.0f) {
                    obj->trans.y -= 4.0f;
                }
                break;
            case 2:
                if (obj->trans.y < 0.0f) {
                    obj->trans.y += 4.0f;
                }
                break;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C670_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C680_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C694_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6A4_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6B8_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6C8_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6DC_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6EC_hide_and_sneak);

void func_8010B410_hide_and_sneak(omObjData *obj) {
    s32 i = (s8)obj->work[0];
    void *data;

    obj->model[0] = func_8000B108_main(0x27000D, 0x2A9);
    data = DataRead(D_8010C4B4_hide_and_sneak[i] | 0x270000);
    HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "s206_004_DEF");
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    DataClose(data);
    obj->trans.x = i * 130 - 195;
    obj->trans.y = -160.0f;
    obj->trans.z = 100.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C92C_main(obj->model[0], 0.0f);
    func_8001C8A8_main(obj->model[0], 2);
    obj->func = func_8010B33C_hide_and_sneak;
}

void func_8010B55C_hide_and_sneak(void) {
    omObjData *obj;
    HsEnt *ent;
    s8 i;

    for (i = 0; i < 4; i++) {
        ent = HS_ENT(HS_ENT_MARK, i);
        obj = omAddObj(900, 1, 1, -1, func_8010B410_hide_and_sneak);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B600_hide_and_sneak);

void func_8010BBBC_hide_and_sneak(void) {
    u32 i;

    if (D_8010C4BC_hide_and_sneak == 0) {
        D_8010C4BC_hide_and_sneak = 1;
        for (i = 0; i < 2; i++) {
            CZoomM[i] = 2695.0789f;
            CRotM[i].x = 340.1531f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = -0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = 385.0f;
            CenterM[i].z = -100.0f;
        }
    }
}

void func_8010BC8C_hide_and_sneak(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010BCB0_hide_and_sneak(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010BC8C_hide_and_sneak;
    }
}

void func_8010BCE8_hide_and_sneak(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010BCB0_hide_and_sneak;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BD40_hide_and_sneak);

void func_8010BFE8_hide_and_sneak(omObjData *obj) {
    D_8010E180_hide_and_sneak = 0;
    D_8010E170_hide_and_sneak = 0;
    D_8010E17A_hide_and_sneak = 0;
    D_8010E174_hide_and_sneak = 0;
    D_8010E1B3_hide_and_sneak = 3;
    D_8010E1AD_hide_and_sneak = 0;
    D_8010E1B2_hide_and_sneak = 0;
    D_8010C782_hide_and_sneak = 4;
    D_8010E1AC_hide_and_sneak = 0;
    func_8010BBBC_hide_and_sneak();
    func_80106960_hide_and_sneak();
    func_801078E4_hide_and_sneak();
    func_8010A48C_hide_and_sneak();
    func_8010ABC8_hide_and_sneak();
    func_8010B55C_hide_and_sneak();
    func_8010B0D0_hide_and_sneak();
    WipeCreateIn(0xFF, 16);
    obj->func = func_8010BD40_hide_and_sneak;
}

void func_8010C0A4_hide_and_sneak(void) {
}

void func_8010C0AC_hide_and_sneak(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_8010C4C0_hide_and_sneak[i].scissor[0], D_8010C4C0_hide_and_sneak[i].scissor[1],
                   D_8010C4C0_hide_and_sneak[i].scissor[2], D_8010C4C0_hide_and_sneak[i].scissor[3]);
        ViewportSet(i, D_8010C4C0_hide_and_sneak[i].viewport[0], D_8010C4C0_hide_and_sneak[i].viewport[1],
                    D_8010C4C0_hide_and_sneak[i].viewport[2], D_8010C4C0_hide_and_sneak[i].viewport[3],
                    D_8010C4C0_hide_and_sneak[i].viewport[4], D_8010C4C0_hide_and_sneak[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010C4C0_hide_and_sneak[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010C220_hide_and_sneak(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010C0AC_hide_and_sneak();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, 0.0f, 0.0f, 100.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 0.0f, 0.0f, 100.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010C754_hide_and_sneak, 0);
    func_80045010_main(D_8010C754_hide_and_sneak, 1);
    omAddObj(1500, 0, 0, -1, func_8010BFE8_hide_and_sneak);
    omAddObj(1500, 0, 0, -1, func_8010BCE8_hide_and_sneak);
    func_80105A74_hide_and_sneak();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C754_hide_and_sneak);
