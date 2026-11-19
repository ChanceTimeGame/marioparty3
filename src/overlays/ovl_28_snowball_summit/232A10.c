#include "common.h"
// m7 su: Snowball Summit (4 players: roll snowballs down the mountain, dodge or catch the big ones)
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

/* A snowball-impact flash (D_80110048_snowball_summit, 16 x 0x18). */
typedef struct SsFlash {
    /* 0x00 */ s32 state; /* -1 absent, 0 idle, 1 start, 2 fading */
    /* 0x04 */ s32 alpha;
    /* 0x08 */ s32 speed;
    /* 0x0C */ f32 max;
    /* 0x10 */ f32 grow;
    /* 0x14 */ omObjData *obj;
} SsFlash; // Size 0x18

/* An expanding ring (D_8010F8D8_snowball_summit, 8 x 0x1C). */
typedef struct SsRing {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 alpha;
    /* 0x08 */ s32 speed;
    /* 0x0C */ f32 max;
    /* 0x10 */ f32 grow;
    /* 0x14 */ f32 scale;
    /* 0x18 */ omObjData *obj;
} SsRing; // Size 0x1C

/* A sliding background prop (D_80110200_snowball_summit, 3 x 0x18). */
typedef struct SsSlider {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 len;
    /* 0x0C */ f32 dx;
    /* 0x10 */ f32 dy;
    /* 0x14 */ f32 dz;
} SsSlider; // Size 0x18

/* A slider's path (D_8010F550_snowball_summit, 3 x 0x18). */
typedef struct SsPath {
    /* 0x00 */ Vec from;
    /* 0x0C */ Vec to;
} SsPath; // Size 0x18

/* A start corner (D_8010F598_snowball_summit, 4 x 0xC). */
typedef struct SsStart {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ f32 rot;
} SsStart; // Size 0xC

/* A camera (D_8010F5CC_snowball_summit). */
typedef struct SsCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} SsCamera; // Size 0x2C

/* The sky backdrop (D_8010F8C0_snowball_summit). */
typedef struct SsSky {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 hook; /* draw hook (s16 return kept as int) */
    /* 0x0C */ HuSprite_Unk84_Struct *left;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ HuSprite_Unk84_Struct *right;
} SsSky; // Size 0x18

typedef s32 (*SsDrawHookAdd)(s32, void (*)(Gfx **, s32, s32), u8);

extern s32 fontcolor;
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u16 D_800D530C_main;
void osViBlack(u8 active);
void func_8000BC48_main(u16, u16);
s32 func_8000B710_main(s32 arg0);
void func_8001F9E4_main(s16 model, u8 alpha);
void func_8001FA68_main(s16 model);
void func_8001C6A8_main(s32 model, f32 arg1);
void func_80032FC0_main(s16, u8, u8);
void func_800E6F0C_minigame(s8 arg0);

/* m7 su: prototypes */
void func_801059A0_snowball_summit(void);
Gfx **func_801059BC_snowball_summit(Gfx **gfx);
Gfx **func_80105AA0_snowball_summit(Gfx **gfx);
Gfx **func_80105B6C_snowball_summit(Gfx **gfx, u8 alpha);
void func_80105B9C_snowball_summit(s32 player);
f32 func_80105C14_snowball_summit(f32 x);
void func_80105D64_snowball_summit(Vec *from, Vec *to, Vec *out);
void func_801060E0_snowball_summit(u16 x, u16 y, char *str, u16 color);
f32 func_8010610C_snowball_summit(f32 x, f32 z);
void func_80106184_snowball_summit(omObjData *obj);
void func_801061DC_snowball_summit(omObjData *obj);
void func_801062AC_snowball_summit(void);
void func_801062E0_snowball_summit(Gfx **gfx, s32 arg1, s32 arg2);
void func_80106758_snowball_summit(omObjData *obj);
void func_80106760_snowball_summit(omObjData *obj);
void func_801067FC_snowball_summit(void);
void func_80106834_snowball_summit(omObjData *obj);
void func_8010683C_snowball_summit(omObjData *obj);
void func_801068B0_snowball_summit(void);
void func_801068E4_snowball_summit(omObjData *obj);
void func_801068EC_snowball_summit(omObjData *obj);
void func_80106968_snowball_summit(void);
void func_8010699C_snowball_summit(omObjData *obj);
void func_80106D58_snowball_summit(omObjData *obj);
void func_80107000_snowball_summit(void);
void func_8010705C_snowball_summit(omObjData *obj, s32 speed, f32 grow, f32 max, f32 dx, f32 dy, f32 dz);
void func_801070F4_snowball_summit(omObjData *obj);
void func_80107230_snowball_summit(omObjData *obj);
void func_80107330_snowball_summit(void);
void func_8010738C_snowball_summit(omObjData *obj, s32 speed, f32 grow, f32 scale, f32 max, f32 dx, f32 dy, f32 dz);
void func_8010742C_snowball_summit(omObjData *obj);
void func_801075E0_snowball_summit(omObjData *obj);
void func_80107700_snowball_summit(void);
void func_8010775C_snowball_summit(omObjData *obj);
void func_80107860_snowball_summit(omObjData *obj);
void func_801078D4_snowball_summit(void);
void func_80107908_snowball_summit(f32 x0, f32 z0, f32 x1, f32 z1, Vec *out);
void func_8010F42C_snowball_summit(void);

/* .data */
extern SsPath D_8010F550_snowball_summit[3];
extern SsStart D_8010F598_snowball_summit[4];
extern s32 D_8010F5C8_snowball_summit;
extern SsCamera D_8010F5CC_snowball_summit[2];
/* .bss */
extern s32 D_8010F880_snowball_summit; /* game phase */
extern s32 D_8010F884_snowball_summit; /* phase advance */
extern s32 D_8010F888_snowball_summit;
extern s32 D_8010F88C_snowball_summit; /* phase timer */
extern s16 D_8010F890_snowball_summit;
extern s16 D_8010F892_snowball_summit;
extern SsSky D_8010F8C0_snowball_summit;
/* Some functions address D_8010F8C0's fields as separate symbols (no shared base): views of it. */
extern s32 D_8010F8C8_snowball_summit; /* D_8010F8C0.hook */
extern s16 D_8010F8CA_snowball_summit; /* D_8010F8C0.hook, low half */
extern HuSprite_Unk84_Struct *D_8010F8CC_snowball_summit; /* D_8010F8C0.left */
extern HuSprite_Unk84_Struct *D_8010F8D4_snowball_summit; /* D_8010F8C0.right */
extern SsRing D_8010F8D8_snowball_summit[8];
extern s16 D_80110030_snowball_summit;
extern SsFlash D_80110048_snowball_summit[16];
extern s16 D_801101F0_snowball_summit;
extern s16 D_801101F2_snowball_summit;
extern f32 D_801101F4_snowball_summit;
extern f32 D_801101F8_snowball_summit;
extern SsSlider D_80110200_snowball_summit[3];

void func_801059A0_snowball_summit(void) {
    func_8010F42C_snowball_summit();
}

Gfx **func_801059BC_snowball_summit(Gfx **gfx) {
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

Gfx **func_80105AA0_snowball_summit(Gfx **gfx) {
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

Gfx **func_80105B6C_snowball_summit(Gfx **gfx, u8 alpha) {
    Gfx *g;

    g = *gfx;
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, alpha);
    *gfx = g;
    return gfx;
}

void func_80105B9C_snowball_summit(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

f32 func_80105C14_snowball_summit(f32 x) {
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

void func_80105D64_snowball_summit(Vec *from, Vec *to, Vec *out) {
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
            yaw = func_80105C14_snowball_summit(delta.x / delta.z) * 57.29577951308232;
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
            pitch = func_80105C14_snowball_summit(delta.y / horizontal) * 57.29577951308232;
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

void func_801060E0_snowball_summit(u16 x, u16 y, char *str, u16 color) {
    fontcolor = color;
    print8(x, y, str);
}

f32 func_8010610C_snowball_summit(f32 x, f32 z) {
    f32 a = atan2df(x, z);

    if (a > 360.0) {
        a -= 360.0;
    } else if (a < 0.0) {
        a += 360.0;
    }
    return a;
}

void func_80106184_snowball_summit(omObjData *obj) {
    func_8000BBD4_main(D_801101F2_snowball_summit, D_801101F4_snowball_summit, D_801101F8_snowball_summit);
}

void func_801061DC_snowball_summit(omObjData *obj) {
    D_801101F4_snowball_summit = 160.0f;
    D_801101F8_snowball_summit = 33.0f;
    D_801101F0_snowball_summit = func_8000B838_main(0x490002);
    D_801101F2_snowball_summit = InitEspriteSlot(D_801101F0_snowball_summit, 0, 0);
    func_8000BC48_main(D_801101F2_snowball_summit, 0x5000);
    func_8000BBD4_main(D_801101F2_snowball_summit, D_801101F4_snowball_summit, D_801101F8_snowball_summit);
    obj->func = func_80106184_snowball_summit;
}

void func_801062AC_snowball_summit(void) {
    omAddObj(150, 1, 0, -1, func_801061DC_snowball_summit);
}

/* The sky: two 104-pixel-wide CI8 strips, rows 66..175, at x 0 and x 216. */
void func_801062E0_snowball_summit(Gfx **gfx, s32 arg1, s32 arg2) {
    SsSky *sky = &D_8010F8C0_snowball_summit;
    Gfx *g;
    s32 i;

    if (sky->state != -1) {
        gfx = func_801059BC_snowball_summit(gfx);
        g = *gfx;
        gDPSetTextureLUT(g++, G_TT_RGBA16);
        gDPLoadTLUT_pal256(g++, D_8010F8CC_snowball_summit->unk0C);
        for (i = 0; i < 110; i += 10) {
            gDPLoadTextureTile(g++, sky->left->unk08, G_IM_FMT_CI, G_IM_SIZ_8b, 104, 0, 0, i, 104,
                               i + 10, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 104 << 2, 10 << 2);
            gSPTextureRectangle(g++, 0, (i + 66) << 2, 104 << 2, (i + 76) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                                1 << 10);
        }
        gDPSetTextureLUT(g++, G_TT_RGBA16);
        gDPLoadTLUT_pal256(g++, sky->right->unk0C);
        for (i = 0; i < 110; i += 10) {
            gDPLoadTextureTile(g++, sky->right->unk08, G_IM_FMT_CI, G_IM_SIZ_8b, 104, 0, 0, i, 104,
                               i + 10, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 104 << 2, 10 << 2);
            gSPTextureRectangle(g++, 216 << 2, (i + 66) << 2, 320 << 2, (i + 76) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                                1 << 10);
        }
        *gfx = g;
    }
}

void func_80106758_snowball_summit(omObjData *obj) {
}

void func_80106760_snowball_summit(omObjData *obj) {
    SsDrawHookAdd hookAdd = (SsDrawHookAdd)(void (*)(void))func_8001AC8C_main;

    D_8010F8CC_snowball_summit = func_80055194_main(func_8000B838_main(0x490000));
    D_8010F8D4_snowball_summit = func_80055194_main(func_8000B838_main(0x490001));
    /* retail stores this s16 return unextended: it called func_8001AC8C_main as returning int */
    D_8010F8C8_snowball_summit = hookAdd(0, func_801062E0_snowball_summit, 2);
    func_8001C8A8_main(D_8010F8CA_snowball_summit, 1);
    D_8010F8C0_snowball_summit.state = 0;
    obj->func = func_80106758_snowball_summit;
}

void func_801067FC_snowball_summit(void) {
    omAddObj(160, 1, 0, -1, func_80106760_snowball_summit)->work[0] = 0;
}

void func_80106834_snowball_summit(omObjData *obj) {
}

void func_8010683C_snowball_summit(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x490003, 0x2B9);
    obj->trans.x = obj->trans.z = 0.0f;
    obj->trans.y = 20.0f;
    func_8001C8A8_main(obj->model[0], 2);
    obj->func = func_80106834_snowball_summit;
}

void func_801068B0_snowball_summit(void) {
    omAddObj(200, 1, 0, -1, func_8010683C_snowball_summit);
}

void func_801068E4_snowball_summit(omObjData *obj) {
}

void func_801068EC_snowball_summit(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x490006, 0x2B9);
    func_8001C814_main(obj->model[0], 2, 2);
    obj->trans.y = obj->trans.x = obj->trans.z = 0.0f;
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_801068E4_snowball_summit;
}

void func_80106968_snowball_summit(void) {
    omAddObj(170, 1, 1, -1, func_801068EC_snowball_summit);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010699C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80106D58_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107000_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010705C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801070F4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107230_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107330_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010738C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010742C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801075E0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107700_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010775C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107860_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801078D4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107908_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107944_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107988_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107A18_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107B58_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107CA4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107D30_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107DD4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107F80_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010811C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A0B0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A384_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A71C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A940_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010AA78_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010AC94_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010AE74_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B01C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B158_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B250_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B34C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B8E4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B994_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B9E4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010BC7C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010BE8C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010BEE8_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C000_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C10C_snowball_summit);

void func_8010C168_snowball_summit(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C170_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C288_snowball_summit);

void func_8010C2E4_snowball_summit(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C2EC_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C328_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C36C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C3E4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C46C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C4F4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C5C0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C600_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C648_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C6A8_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C7A4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C7F0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C850_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C890_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C9B4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C9E0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CA18_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CA70_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CA98_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CC00_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CD58_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D108_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D304_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D55C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D86C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010DB10_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010DD00_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010DFD0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010E2F4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010E52C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010E824_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EA68_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EBC0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EEEC_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EFA0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EFE4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F020_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F05C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F090_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F0CC_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F100_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F134_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F1B8_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F234_snowball_summit);

void func_8010F2B0_snowball_summit(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F2B8_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F42C_snowball_summit);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", D_8010F870_snowball_summit);
