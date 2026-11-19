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

/* A player (D_8010F9B8_snowball_summit, 4 x 0x9C). */
typedef struct SsPlayer {
    /* 0x00 */ s32 state; /* -1 absent */
    /* 0x04 */ s32 motion;
    /* 0x08 */ s32 cpu;
    /* 0x0C */ s32 level; /* CPU difficulty */
    /* 0x10 */ f32 speed;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 rot;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ Vec vel;
    /* 0x2C */ f32 gravity;
    /* 0x30 */ Vec next;
    /* 0x3C */ s32 hit; /* knocked into the air */
    /* 0x40 */ s32 holdTime;
    /* 0x44 */ s32 holdCount;
    /* 0x48 */ s32 rolling;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ char unk58[0x14];
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 ball; /* the snowball being rolled, -1 none */
    /* 0x74 */ s32 land;
    /* 0x78 */ omObjData *obj;
    /* 0x7C */ s32 holdRate; /* CPU */
    /* 0x80 */ s32 range; /* CPU: dodge distance */
    /* 0x84 */ s32 chase; /* CPU */
    /* 0x88 */ s32 dodge; /* CPU */
    /* 0x8C */ s32 hold; /* CPU: holding A */
    /* 0x90 */ s32 timer; /* CPU: wander time */
    /* 0x94 */ s16 stickX; /* CPU */
    /* 0x96 */ s16 stickZ;
    /* 0x98 */ f32 size;
} SsPlayer; // Size 0x9C

/* A snowball (D_8010FC30_snowball_summit, 16 x 0x40). */
typedef struct SsBall {
    /* 0x00 */ s32 state; /* -1 absent */
    /* 0x04 */ char unk04[8];
    /* 0x0C */ f32 size;
    /* 0x10 */ s32 owner; /* player rolling it, -1 none */
    /* 0x14 */ char unk14[0x28];
    /* 0x3C */ omObjData *obj;
} SsBall; // Size 0x40

/* A u8 random number below n. */
#define SS_RAND(n) ((u8)(rand8() % (n)))
/* An angle wrapped once into [0, 360) (its argument is evaluated again on each test). */
#define SS_WRAP(a) ((a) >= 360.0f ? (a) - 360.0f : (a) < 0.0f ? (a) + 360.0f : (a))
#define SS_ABS(x) ((x) < 0.0f ? -(x) : (x))
#define SS_IABS(x) ((x) < 0 ? -(x) : (x))

/* Small state slots (D_801101C8_snowball_summit 4 x 8, D_80110250_snowball_summit 4 x 0x10). */
typedef struct SsSlot8 {
    /* 0x00 */ s32 state;
    /* 0x04 */ omObjData *obj;
} SsSlot8;
typedef struct SsSlot16 {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ omObjData *obj;
} SsSlot16;

typedef s32 (*SsDrawHookAdd)(s32, void (*)(Gfx **, s32, s32), u8);

extern s32 fontcolor;
extern s32 D_800A178C_main[][6];
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
void func_80088800_main(f32 *mtx, f32 x, f32 y, f32 z);
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
void func_80107944_snowball_summit(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, Vec *out);
void func_80107A18_snowball_summit(omObjData *obj, Vec stick, f32 rate);
void func_80107B58_snowball_summit(omObjData *obj, Vec stick);
void func_80107CA4_snowball_summit(omObjData *obj, s32 motion);
void func_80107D30_snowball_summit(omObjData *obj, s32 motion, s16 arg2, s16 arg3);
s32 func_80107988_snowball_summit(f32 cur, f32 target, f32 tol);
void func_80107DD4_snowball_summit(SsPlayer *pl);
s32 func_80107F80_snowball_summit(SsPlayer *pl);
void func_8010811C_snowball_summit(omObjData *obj);
void func_8010A0B0_snowball_summit(omObjData *obj);
void func_8010A384_snowball_summit(omObjData *obj);
void func_8010A71C_snowball_summit(omObjData *obj);
void func_8010A940_snowball_summit(omObjData *obj);
void func_8010AA78_snowball_summit(omObjData *obj);
void func_8010AC94_snowball_summit(omObjData *obj);
void func_8010AE74_snowball_summit(omObjData *obj);
void func_8010B01C_snowball_summit(omObjData *obj);
void func_8010B158_snowball_summit(omObjData *obj);
s32 func_8010B994_snowball_summit(omObjData *obj);
void func_8010B8E4_snowball_summit(void);
void func_8010B34C_snowball_summit(omObjData *obj);
void func_8010BC7C_snowball_summit(omObjData *obj);
s32 func_8010C36C_snowball_summit(void);
void func_8010C3E4_snowball_summit(s32 player);
void func_8010C328_snowball_summit(omObjData *obj);
void func_8010BE8C_snowball_summit(void);
void func_8010C000_snowball_summit(omObjData *obj);
void func_8010C10C_snowball_summit(void);
void func_8010C168_snowball_summit(omObjData *obj);
void func_8010C170_snowball_summit(omObjData *obj);
void func_8010C288_snowball_summit(void);
void func_8010C2E4_snowball_summit(omObjData *obj);
void func_8010C2EC_snowball_summit(omObjData *obj);
void func_8010C4F4_snowball_summit(omObjData *obj);
void func_8010C5C0_snowball_summit(omObjData *obj);
void func_8010C6A8_snowball_summit(omObjData *obj);
void func_8010C7A4_snowball_summit(omObjData *obj);
void func_8010C7F0_snowball_summit(omObjData *obj);
void func_8010C850_snowball_summit(omObjData *obj);
void func_8010C890_snowball_summit(omObjData *obj);
void func_8010C9B4_snowball_summit(omObjData *obj);
void func_8010C9E0_snowball_summit(omObjData *obj);
void func_8010CA18_snowball_summit(omObjData *obj);
void func_8010CA70_snowball_summit(void);
void func_8010D86C_snowball_summit(void);
void func_8010EA68_snowball_summit(void);
void func_8010EBC0_snowball_summit(void);
void func_8010EEEC_snowball_summit(omObjData *obj);
void func_8010F1B8_snowball_summit(void);
void func_8010F234_snowball_summit(omObjData *obj);
void func_8010F2B8_snowball_summit(void);
void func_8010F42C_snowball_summit(void);

/* .rodata */
extern const s16 D_8010F870_snowball_summit[];
/* .data */
extern SsPath D_8010F550_snowball_summit[3];
extern SsStart D_8010F598_snowball_summit[4];
extern s32 D_8010F5C8_snowball_summit;
extern SsCamera D_8010F5CC_snowball_summit[2];
/* .bss */
extern s32 D_8010F880_snowball_summit; /* game phase */
extern s32 D_8010F884_snowball_summit; /* phase advance */
extern u16 D_8010F888_snowball_summit; /* camera set */
extern s32 D_8010F88C_snowball_summit; /* phase timer */
extern s16 D_8010F890_snowball_summit;
extern u8 D_8010F892_snowball_summit;
extern SsSky D_8010F8C0_snowball_summit;
/* Some functions address D_8010F8C0's fields as separate symbols (no shared base): views of it. */
extern s32 D_8010F8C8_snowball_summit; /* D_8010F8C0.hook */
extern s16 D_8010F8CA_snowball_summit; /* D_8010F8C0.hook, low half */
extern HuSprite_Unk84_Struct *D_8010F8CC_snowball_summit; /* D_8010F8C0.left */
extern HuSprite_Unk84_Struct *D_8010F8D4_snowball_summit; /* D_8010F8C0.right */
extern s32 D_8010F8A8_snowball_summit; /* start corner */
extern u16 D_8010F8AE_snowball_summit; /* 0x49000C, linked by players 1-3 */
extern u16 D_8010F8B0_snowball_summit; /* 0x49000B, linked by players 1-3 */
extern SsRing D_8010F8D8_snowball_summit[8];
extern SsPlayer D_8010F9B8_snowball_summit[4];
extern SsBall D_8010FC30_snowball_summit[16];
extern s16 D_80110030_snowball_summit[]; /* snowfall emitter model (0x14 bytes, only [0] used) */
extern s32 D_80110044_snowball_summit; /* the winners have been decided */
extern SsFlash D_80110048_snowball_summit[16];
extern SsSlot8 D_801101C8_snowball_summit[4];
extern s32 D_801101E8_snowball_summit;
extern s32 D_80110248_snowball_summit;
extern s32 D_8011024C_snowball_summit;
extern SsSlot16 D_80110250_snowball_summit[4];
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

/* A background prop: wait, then slide along its path and hide. */
void func_8010699C_snowball_summit(omObjData *obj) {
    SsSlider *s = &D_80110200_snowball_summit[obj->work[0]];
    s32 side;

    if (s->state == -1) {
        return;
    }
    switch (s->state) {
        case 0:
            if (s->timer > 0) {
                s->timer--;
            } else {
                s->state = 1;
            }
            break;
        case 1:
            side = rand8() & 1;
            func_8001C258_main(obj->model[side], 4, 0);
            func_8001C258_main(obj->model[side ^ 1], 4, 4);
            obj->trans.x = D_8010F550_snowball_summit[obj->work[0]].from.x;
            obj->trans.y = D_8010F550_snowball_summit[obj->work[0]].from.y;
            obj->trans.z = D_8010F550_snowball_summit[obj->work[0]].from.z;
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
            s->len = SS_RAND(15) + 30;
            s->timer++;
            s->state = 2;
            break;
        case 2:
            s->dx = (D_8010F550_snowball_summit[obj->work[0]].to.x - D_8010F550_snowball_summit[obj->work[0]].from.x)
                    / s->len * s->timer;
            s->dy = (D_8010F550_snowball_summit[obj->work[0]].to.y - D_8010F550_snowball_summit[obj->work[0]].from.y)
                    / s->len * s->timer;
            s->dz = (D_8010F550_snowball_summit[obj->work[0]].to.z - D_8010F550_snowball_summit[obj->work[0]].from.z)
                    / s->len * s->timer;
            obj->trans.x = D_8010F550_snowball_summit[obj->work[0]].from.x + s->dx;
            obj->trans.y = D_8010F550_snowball_summit[obj->work[0]].from.y + s->dy;
            obj->trans.z = D_8010F550_snowball_summit[obj->work[0]].from.z + s->dz;
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
            if (s->timer >= s->len) {
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 4);
                s->state = 0;
                s->timer = SS_RAND(60) + 150;
                s->dx = s->dy = s->dz = 0.0f;
            } else {
                s->timer++;
            }
            break;
    }
}

void func_80106D58_snowball_summit(omObjData *obj) {
    SsSlider *s;
    void *data;

    if (obj->work[0] == 0) {
        obj->model[0] = D_8010F890_snowball_summit = func_8000B108_main(0x490007, 0x2B9);
        obj->model[1] = func_8000B108_main(0x490007, 0x2A9);
        data = DataRead(0x490008);
        obj->work[1] = D_8010F892_snowball_summit = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "s240_002_DEF");
        HuMemMemoryFreePerm(data);
    } else {
        obj->model[0] = Hu3DModelLink(D_8010F890_snowball_summit);
        obj->model[1] = func_8000B108_main(0x490007, 0x2A9);
        obj->work[1] = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8010F892_snowball_summit, 0, "s240_002_DEF");
    }
    func_80032FC0_main((s16)obj->work[1], 1, 1);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = D_8010F550_snowball_summit[obj->work[0]].from.x;
    obj->trans.y = D_8010F550_snowball_summit[obj->work[0]].from.y;
    obj->trans.z = D_8010F550_snowball_summit[obj->work[0]].from.z;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    s = &D_80110200_snowball_summit[obj->work[0]];
    s->state = 0;
    s->timer = SS_RAND(60) + 150;
    s->dx = s->dy = s->dz = 0.0f;
    obj->func = func_8010699C_snowball_summit;
}

void func_80107000_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        omAddObj(180, 2, 0, -1, func_80106D58_snowball_summit)->work[0] = i;
    }
}

/* Starts a free impact flash at obj's position plus (dx, dy, dz). */
void func_8010705C_snowball_summit(omObjData *obj, s32 speed, f32 grow, f32 max, f32 dx, f32 dy, f32 dz) {
    SsFlash *fl;
    s32 i;

    for (i = 0; i < 16; i++) {
        fl = &D_80110048_snowball_summit[i];
        if (fl->state == 0) {
            fl->state = 1;
            fl->obj->trans.x = dx + obj->trans.x;
            fl->obj->trans.y = dy + obj->trans.y;
            fl->obj->trans.z = dz + obj->trans.z;
            fl->speed = speed;
            fl->grow = grow;
            fl->max = max;
            break;
        }
    }
}

void func_801070F4_snowball_summit(omObjData *obj) {
    SsFlash *fl = &D_80110048_snowball_summit[obj->work[0]];

    if (fl->state == -1) {
        return;
    }
    switch (fl->state) {
        case -1: /* unreachable; retail's case tree has it */
            break;
        case 1:
            func_8001C258_main(obj->model[0], 4, 0);
            fl->state = 2;
            break;
        case 2:
            fl->alpha -= fl->speed;
            if (fl->alpha > 0) {
                func_8001F9E4_main(obj->model[0], fl->alpha);
                obj->scale.x += fl->grow;
                obj->scale.y += fl->grow;
                obj->scale.z += fl->grow;
            } else {
                func_8001C258_main(obj->model[0], 4, 4);
                fl->state = 0;
                fl->alpha = 0xFF;
                fl->speed = 0;
                fl->grow = 0.0f;
                obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
                func_8001F9E4_main(obj->model[0], 0xFF);
            }
            break;
    }
}

void func_80107230_snowball_summit(omObjData *obj) {
    SsFlash *fl;

    obj->model[0] = func_8000B108_main(0x490009, 0x289);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xFF);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    func_8001C8A8_main(obj->model[0], 2);
    obj->func = func_801070F4_snowball_summit;
    fl = &D_80110048_snowball_summit[obj->work[0]];
    fl->state = 0;
    fl->alpha = 0xFF;
    fl->speed = 0;
    fl->max = 1.6f;
    fl->grow = 0.0f;
    fl->obj = obj;
}

void func_80107330_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(500, 1, 0, -1, func_80107230_snowball_summit)->work[0] = i;
    }
}

/* Starts a free ring at obj's position plus (dx, dy, dz). */
void func_8010738C_snowball_summit(omObjData *obj, s32 speed, f32 grow, f32 scale, f32 max, f32 dx, f32 dy, f32 dz) {
    SsRing *r;
    s32 i;

    for (i = 0; i < 8; i++) {
        r = &D_8010F8D8_snowball_summit[i];
        if (r->state == 0) {
            r->state = 1;
            r->obj->trans.x = dx + obj->trans.x;
            r->obj->trans.y = dy + obj->trans.y;
            r->obj->trans.z = dz + obj->trans.z;
            r->speed = speed;
            r->grow = grow;
            r->max = max;
            r->scale = scale;
            break;
        }
    }
}

void func_8010742C_snowball_summit(omObjData *obj) {
    SsRing *r = &D_8010F8D8_snowball_summit[obj->work[0]];

    if (r->state == -1) {
        return;
    }
    switch (r->state) {
        case -1: /* unreachable; retail's case tree has it */
            break;
        case 1:
            func_8001C258_main(obj->model[0], 4, 0);
            func_8001C814_main(obj->model[0], 1, 0);
            obj->scale.x = obj->scale.y = obj->scale.z = r->scale;
            r->state = 2;
            break;
        case 2:
            r->alpha -= r->speed;
            if (r->alpha > 0) {
                if (r->alpha < 0xFF) {
                    func_8001F9E4_main(obj->model[0], r->alpha);
                } else {
                    func_8001F9E4_main(obj->model[0], 0xFF);
                }
                if (obj->scale.x < r->max) {
                    obj->scale.x += r->grow;
                    obj->scale.y += r->grow;
                    obj->scale.z += r->grow;
                }
            } else {
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C814_main(obj->model[0], 1, 1);
                r->state = 0;
                r->alpha = 450;
                r->speed = 0;
                r->grow = 0.0f;
                obj->scale.x = obj->scale.y = obj->scale.z = 0.5f;
                func_8001F9E4_main(obj->model[0], 0xFF);
            }
            break;
    }
}

void func_801075E0_snowball_summit(omObjData *obj) {
    SsRing *r;

    obj->model[0] = func_8000B108_main(0x49000A, 0x1689);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xFF);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C6A8_main(obj->model[0], 0.0f);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.7f;
    func_8001C8A8_main(obj->model[0], 2);
    obj->func = func_8010742C_snowball_summit;
    r = &D_8010F8D8_snowball_summit[obj->work[0]];
    r->state = 0;
    r->alpha = 450;
    r->speed = 0;
    r->max = 0.7f;
    r->grow = 0.0f;
    r->obj = obj;
}

void func_80107700_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        omAddObj(600, 1, 1, -1, func_801075E0_snowball_summit)->work[0] = i;
    }
}

/* Snowflakes: four emitters at random x inside a radius of 10000. */
void func_8010775C_snowball_summit(omObjData *obj) {
    s16 *snow = D_80110030_snowball_summit;
    f32 x;
    f32 z;
    s32 i;

    for (i = 0; i < 4; i++) {
        do {
            x = (rand8() - 128) * 12;
            z = i * 720 - 700;
        } while (!(x * x + z * z < 1e8f));
        func_8000CD74_main(*snow, x, i * 180 + 1000, z);
    }
}

void func_80107860_snowball_summit(omObjData *obj) {
    s16 *snow = D_80110030_snowball_summit;

    *snow = func_8000CBA0_main(0x49000D, 0x2A9);
    func_8000CD00_main(*snow, 15.0f, 110.0f, 8.0f);
    func_8001C8A8_main(*snow, 2);
    obj->func = func_8010775C_snowball_summit;
}

void func_801078D4_snowball_summit(void) {
    omAddObj(990, 1, 0, -1, func_80107860_snowball_summit);
}

void func_80107908_snowball_summit(f32 x0, f32 z0, f32 x1, f32 z1, Vec *out) {
    Vec from;
    Vec to;

    to.x = x0;
    to.y = 0;
    to.z = z0;
    from.x = x1;
    from.y = 0;
    from.z = z1;
    func_80105D64_snowball_summit(&from, &to, out);
}

void func_80107944_snowball_summit(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, Vec *out) {
    Vec from;
    Vec to;

    to.x = x0;
    to.y = y0;
    to.z = z0;
    from.x = x1;
    from.y = y1;
    from.z = z1;
    func_80105D64_snowball_summit(&from, &to, out);
}

/* Which way to turn from cur to target: 0 within tol, else -1 or 1. */
s32 func_80107988_snowball_summit(f32 cur, f32 target, f32 tol) {
    f32 d = target - cur;

    if (d < 0.0f) {
        d += 360.0f;
    }
    if (d < tol || 360.0f - tol < d) {
        return 0;
    }
    if (d >= 180.0f) {
        return -1;
    }
    return 1;
}

/* Turns obj toward the stick heading (stick.z) by at most rate degrees (only in motions 0, 1, 3 and 4). */
// retail shares rate * dir + rot between the < 0 test and its store (GCC 2.7 here computes it twice); same logic
#ifdef NON_MATCHING
void func_80107A18_snowball_summit(omObjData *obj, Vec stick, f32 rate) {
    SsPlayer *pl;
    s32 dir;

    pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    dir = func_80107988_snowball_summit(obj->rot.y, stick.z, rate);

    switch (pl->motion) {
        case 0:
        case 1:
        case 3:
        case 4:
            if (dir != 0) {
                obj->rot.y = SS_WRAP(rate * dir + obj->rot.y);
            } else {
                obj->rot.y = stick.z;
            }
            break;
    }
    pl->rot = obj->rot.y;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107A18_snowball_summit);
#endif

/* Speed from the stick distance (stick.x; a snowball slows its roller by its size) and the next position. */
// scheduling of the 0.4/0.6 blend (retail multiplies by 0.6 first and keeps 0.4 in double); same ops
#ifdef NON_MATCHING
void func_80107B58_snowball_summit(omObjData *obj, Vec stick) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    f32 spd;

    if (stick.x > 70.0f) {
        spd = pl->speed = 7.0f;
    } else {
        spd = pl->speed = stick.x * 0.1;
    }
    if (pl->ball != -1) {
        pl->speed = spd * 0.4 + (f32)(spd * 0.6) * (1.0f / D_8010FC30_snowball_summit[pl->ball].size);
    }
    pl->vel.x = sindf(obj->rot.y) * pl->speed;
    pl->vel.z = cosdf(obj->rot.y) * pl->speed;
    pl->next.x = obj->trans.x + pl->vel.x;
    pl->next.z = obj->trans.z + pl->vel.z;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107B58_snowball_summit);
#endif

void func_80107CA4_snowball_summit(omObjData *obj, s32 motion) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];

    func_8001C5B4_main(obj->model[0], obj->motion[motion]);
    func_8001C814_main(obj->model[0], 2, 2);
    pl->motion = motion;
}

void func_80107D30_snowball_summit(omObjData *obj, s32 motion, s16 arg2, s16 arg3) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];

    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[motion]].unk02, arg2, arg3, 2);
    pl->motion = motion;
}

/* The CPU's wander time by difficulty. */
void func_80107DD4_snowball_summit(SsPlayer *pl) {
    switch (pl->level) {
        case 0:
            pl->timer = SS_RAND(31) + 60;
            break;
        case 1:
            pl->timer = SS_RAND(31) + 48.0;
            break;
        case 2:
            pl->timer = SS_RAND(31) + 36.0;
            break;
        default:
            pl->timer = SS_RAND(31) + 24.0;
            break;
    }
}

/* The CPU's edge-turn angle by difficulty. */
s32 func_80107F80_snowball_summit(SsPlayer *pl) {
    switch (pl->level) {
        case 0:
            return SS_RAND(31) + 60;
        case 1:
            return SS_RAND(31) + 48.0;
        case 2:
            return SS_RAND(31) + 36.0;
        default:
            return SS_RAND(31) + 24.0;
    }
}

/* The CPU's stick and buttons: dodge snowballs, roll at the players, wander. */
// scheduling: retail loads 348100.0f before the x*x + z*z sum (one nop more here), then register allocation
#ifdef NON_MATCHING
void func_8010811C_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    Vec out;
    f32 base;
    f32 turn;
    SsPlayer *other;
    SsBall *ball;
    omObjData *target;
    s32 i;

    func_80105B9C_snowball_summit(obj->work[0]);
    if (pl->ball != -1 && pl->hold == 1) {
        pl->hold = 0;
        pl->stickX = sindf(SS_WRAP((f32)(rand16() % 360))) * 70.0f;
        pl->stickZ = -(s32)(cosdf(SS_WRAP((f32)(rand16() % 360))) * 70.0f);
        D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
        func_80107DD4_snowball_summit(pl);
        return;
    }
    if (pl->hold != 0) {
        if (rand8() < pl->holdRate && rand8() < pl->holdRate) {
            D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x4000;
        }
    }
    if (pl->hold == 0 && 348100.0f < obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z) {
        func_80107DD4_snowball_summit(pl);
        base = func_8010610C_snowball_summit(obj->trans.x, obj->trans.z);
        turn = 180.0 - func_80107F80_snowball_summit(pl) * 0.5;
        pl->stickX = sindf(SS_WRAP(base + turn + func_80107F80_snowball_summit(pl))) * 70.0f;
        pl->stickZ = -(s32)(cosdf(SS_WRAP(base + turn + func_80107F80_snowball_summit(pl))) * 70.0f);
        D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
        return;
    }
    if (pl->ball == -1) {
        if (pl->timer < 30) {
            for (i = 0; i < 16; i++) {
                ball = &D_8010FC30_snowball_summit[i];
                if (ball->state > 0) {
                    target = ball->obj;
                    func_80107908_snowball_summit(obj->trans.x, obj->trans.z, target->trans.x, target->trans.z,
                                                  &out);
                    if (SS_ABS(out.x) < (f32)pl->range) {
                        if (rand8() % pl->dodge != 0) {
                            pl->stickX = sindf(SS_WRAP(out.z + 70.0f + SS_RAND(60))) * 70.0f;
                            pl->stickZ = -(s32)(cosdf(SS_WRAP(out.z + 70.0f + SS_RAND(60))) * 70.0f);
                            D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
                            D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
                            pl->hold = 0;
                            func_80107DD4_snowball_summit(pl);
                            return;
                        }
                    }
                }
            }
        }
        if (pl->hold == 0) {
            if (pl->ball == -1 && pl->timer == 0 && rand8() % pl->holdRate != 0) {
                pl->hold = 1;
                D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = D_800D20A1_main[GwPlayer[obj->work[0]].pad] = 0;
                pl->stickX = pl->stickZ = 0;
                D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x4000;
                return;
            }
            goto wander;
        }
    } else {
        if (pl->timer < 30) {
            for (i = 0; i < 16; i++) {
                ball = &D_8010FC30_snowball_summit[i];
                if (ball->state > 0 && i != pl->ball) {
                    target = ball->obj;
                    func_80107908_snowball_summit(obj->trans.x, obj->trans.z, target->trans.x, target->trans.z,
                                                  &out);
                    if (SS_ABS(out.x) < (f32)pl->range) {
                        if (rand8() % pl->dodge != 0) {
                            if (rand8() % pl->dodge != 0) {
                                pl->stickX = sindf(SS_WRAP(out.z + 180.0f)) * 70.0f;
                                pl->stickZ = -(s32)(cosdf(SS_WRAP(out.z + 180.0f)) * 70.0f);
                            } else {
                                pl->stickX = sindf(SS_WRAP(out.z + 70.0f + SS_RAND(60))) * 70.0f;
                                pl->stickZ = -(s32)(cosdf(SS_WRAP(out.z + 70.0f + SS_RAND(60))) * 70.0f);
                            }
                            D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
                            D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
                            func_80107DD4_snowball_summit(pl);
                            return;
                        }
                        pl->stickX = sindf(SS_WRAP(out.z + 180.0f)) * 70.0f;
                        pl->stickZ = -(s32)(cosdf(SS_WRAP(out.z + 180.0f)) * 70.0f);
                        D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
                        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
                        func_80107DD4_snowball_summit(pl);
                        if (func_80107988_snowball_summit(obj->rot.y, SS_WRAP(out.z + 180.0f), 20.0f) == 0) {
                            D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x8000;
                            if (rand8() % pl->dodge != 0) {
                                pl->hold = 1;
                                D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = D_800D20A1_main[GwPlayer[obj->work[0]].pad] = 0;
                                pl->stickX = pl->stickZ = 0;
                                D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x4000;
                                pl->timer = 0;
                                return;
                            }
                        }
                    }
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (i != obj->work[0]) {
                other = &D_8010F9B8_snowball_summit[i];
                if (other->state >= 0 && other->state < 90) {
                    target = other->obj;
                    func_80107908_snowball_summit(obj->trans.x, obj->trans.z, target->trans.x, target->trans.z, &out);
                    if (func_80107988_snowball_summit(obj->rot.y, SS_WRAP(out.z + 180.0f), 15.0f) == 0
                        && pl->size < D_8010FC30_snowball_summit[pl->ball].size && rand8() % pl->dodge != 0) {
                        D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x8000;
                        if (rand8() % pl->dodge != 0) {
                            pl->hold = 1;
                            D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = D_800D20A1_main[GwPlayer[obj->work[0]].pad] = 0;
                            pl->stickX = pl->stickZ = 0;
                            D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x4000;
                            pl->timer = 0;
                            return;
                        }
                    }
                }
            }
        }
        if (pl->timer < 30) {
            for (i = 0; i < 4; i++) {
                if (i != obj->work[0]) {
                    other = &D_8010F9B8_snowball_summit[i];
                    if (other->state >= 0 && other->state < 90 && other->cpu == 0) {
                        target = other->obj;
                        if (rand8() % pl->chase == 0) {
                            func_80107908_snowball_summit(obj->trans.x, obj->trans.z, target->trans.x, target->trans.z,
                                                          &out);
                            if (SS_ABS(out.x) < (f32)(pl->range * 2)) {
                                if (rand8() % pl->dodge == 0) {
                                    pl->stickX = sindf(SS_WRAP(out.z + 180.0f)) * 70.0f;
                                    pl->stickZ = -(s32)(cosdf(SS_WRAP(out.z + 180.0f)) * 70.0f);
                                    D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
                                    D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
                                    func_80107DD4_snowball_summit(pl);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                if (i != obj->work[0]) {
                    other = &D_8010F9B8_snowball_summit[i];
                    if (other->state >= 0 && other->state < 90) {
                        target = other->obj;
                        func_80107908_snowball_summit(obj->trans.x, obj->trans.z, target->trans.x, target->trans.z,
                                                      &out);
                        if (SS_ABS(out.x) < (f32)(pl->range * 2)) {
                            pl->stickX = sindf(SS_WRAP(out.z + 180.0f)) * 70.0f;
                            pl->stickZ = -(s32)(cosdf(SS_WRAP(out.z + 180.0f)) * 70.0f);
                            D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
                            D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
                            func_80107DD4_snowball_summit(pl);
                            return;
                        }
                    }
                }
            }
        }
    wander:
        if (pl->hold == 0) {
            if (pl->timer > 0) {
                pl->timer--;
                D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
                D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
                return;
            }
            pl->stickX = sindf(SS_WRAP((f32)(rand16() % 360))) * 70.0f;
            pl->stickZ = -(s32)(cosdf(SS_WRAP((f32)(rand16() % 360))) * 70.0f);
            D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
            D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
            func_80107DD4_snowball_summit(pl);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010811C_snowball_summit);
#endif

/* Walking: finish turn/roll motions, then steer by the stick. */
void func_8010A0B0_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    HmfModel *m;
    Vec stick;

    switch (pl->motion) {
        case 0:
        case 2:
            if (pl->ball != -1) {
                func_80107CA4_snowball_summit(obj, 3);
            } else {
                func_80107CA4_snowball_summit(obj, 1);
            }
            break;
        case 5:
        case 6:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_80107CA4_snowball_summit(obj, 1);
            } else {
                pl->speed = 0.0f;
                pl->vel.x = pl->vel.z = pl->speed;
            }
            break;
        case 3:
        case 4:
            if (pl->ball == -1) {
                func_80107D30_snowball_summit(obj, 1, 0, 10);
            } else {
                if (pl->motion == 3 && D_8010FC30_snowball_summit[pl->ball].size >= 1.7) {
                    func_80107D30_snowball_summit(obj, 4, 12, 6);
                }
                func_8001C814_main(obj->model[0], 2, 2);
                func_8001C814_main(obj->model[0], 1, 0);
            }
            break;
    }
    func_80107908_snowball_summit(D_800CBB6E_main[GwPlayer[obj->work[0]].pad], -D_800D20A1_main[GwPlayer[obj->work[0]].pad],
                                  0, 0, &stick);
    if (pl->ball == -1) {
        func_80107A18_snowball_summit(obj, stick, 30.0f);
    } else {
        func_80107A18_snowball_summit(obj, stick,
                                      1.0f / (D_8010FC30_snowball_summit[pl->ball].size * D_8010FC30_snowball_summit[pl->ball].size) * 30.0f);
    }
    if (pl->motion != 5 && pl->motion != 6) {
        func_80107B58_snowball_summit(obj, stick);
    }
    if (pl->rolling == 0) {
        pl->holdTime = 0;
        pl->holdCount = 0;
    }
}

/* Standing: settle the motion, stop, and turn toward the stick when it is pushed. */
// register allocation only (masked 0: obj/pl swap s0/s1)
#ifdef NON_MATCHING
void func_8010A384_snowball_summit(omObjData *obj) {
    Vec stick;
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];

    switch (pl->motion) {
        case 2:
            if (pl->holdTime > 0) {
                pl->speed = 0.0f;
                break;
            }
            if (pl->rolling != 0) {
                func_80107D30_snowball_summit(obj, 3, 12, 10);
                goto roll;
            }
            goto stand;
        case 3:
        case 4:
            if (pl->ball == -1) {
            stand:
                func_80107D30_snowball_summit(obj, 0, 0, 10);
                pl->speed = 0.0f;
                break;
            }
            if (pl->motion == 3 && D_8010FC30_snowball_summit[pl->ball].size >= 1.7) {
                func_80107D30_snowball_summit(obj, 4, 12, 3);
            }
        roll:
            func_8001C6A8_main(obj->model[0], 12.0f);
            func_8001C814_main(obj->model[0], 2, 0);
            func_8001C814_main(obj->model[0], 1, 1);
            pl->speed = 0.0f;
            break;
        case 5:
        case 6:
            if (!(D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40)) {
                pl->speed = 0.0f;
                break;
            }
        case 1:
            func_80107CA4_snowball_summit(obj, 0);
        default:
            pl->speed = 0.0f;
            break;
    }
    pl->vel.x = pl->vel.z = pl->speed;
    if (!(SS_IABS(D_800CBB6E_main[GwPlayer[obj->work[0]].pad]) < 11
          && SS_IABS(D_800D20A1_main[GwPlayer[obj->work[0]].pad]) < 11)) {
        func_80107908_snowball_summit(D_800CBB6E_main[GwPlayer[obj->work[0]].pad],
                                      -D_800D20A1_main[GwPlayer[obj->work[0]].pad], 0, 0, &stick);
        if (pl->ball == -1) {
            func_80107A18_snowball_summit(obj, stick, 30.0f);
        } else {
            func_80107A18_snowball_summit(obj, stick,
                                          1.0f / (D_8010FC30_snowball_summit[pl->ball].size * D_8010FC30_snowball_summit[pl->ball].size) * 30.0f);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A384_snowball_summit);
#endif

/* Stick at rest with B (A) held: start packing a snowball after ten frames. */
void func_8010A71C_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];

    if (!(SS_IABS(D_800CBB6E_main[GwPlayer[obj->work[0]].pad]) < 11
          && SS_IABS(D_800D20A1_main[GwPlayer[obj->work[0]].pad]) < 11)) {
        return;
    }
    if (pl->motion != 5 && pl->motion != 6) {
        if (pl->motion != 1 && pl->motion != 2) {
            func_80107CA4_snowball_summit(obj, 2);
            pl->speed = 0.0f;
            pl->vel.x = pl->vel.z = pl->speed;
        } else if (pl->motion != 2 && pl->speed == 0.0f) {
            func_80107CA4_snowball_summit(obj, 2);
            pl->speed = 0.0f;
            pl->vel.x = pl->vel.z = 0.0f;
        }
        pl->holdTime = 30;
        if (++pl->holdCount >= 10) {
            pl->ball = func_8010B994_snowball_summit(obj);
            pl->rolling = 1;
            pl->holdTime = 0;
            pl->holdCount = 0;
            func_80107CA4_snowball_summit(obj, 3);
            func_8001C6A8_main(obj->model[0], 12.0f);
            if (pl->cpu == 0) {
                omVibrate((s16)obj->work[0], 2, 3, 10);
            }
        } else {
            func_8004AC98_main(0x438, (s16)obj->work[0]);
        }
    }
}

/* Lets go of the snowball (motion 3 or 4) and pushes it out in front. */
// register allocation only (masked 0: the distance is built in f20, not f2)
#ifdef NON_MATCHING
void func_8010A940_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    SsBall *ball;
    f32 dist;

    switch (pl->motion) {
        case 3:
            func_80107CA4_snowball_summit(obj, 5);
            break;
        case 4:
            func_80107CA4_snowball_summit(obj, 6);
            break;
        default:
            return;
    }
    ball = &D_8010FC30_snowball_summit[pl->ball];
    dist = ball->size * 37.5 + pl->unk50;
    ball->obj->trans.x = sindf(pl->rot) * dist + obj->trans.x;
    ball->obj->trans.z = cosdf(pl->rot) * dist + obj->trans.z;
    if (ball->state != 20) {
        ball->state = 10;
    }
    ball->owner = -1;
    pl->speed = 0.0f;
    pl->vel.x = pl->vel.z = pl->speed;
    pl->rolling = 0;
    pl->ball = -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A940_snowball_summit);
#endif

/* A human's controls. */
// scheduling/CSE: retail reloads obj->work[0] for the first pad lookup and fills delay slots differently; same ops
#ifdef NON_MATCHING
void func_8010AA78_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];

    if (pl->motion != 5 && pl->motion != 6) {
        if ((D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x8000) && pl->rolling == 1) {
            func_8010A940_snowball_summit(obj);
        } else if (!(SS_IABS(D_800CBB6E_main[GwPlayer[obj->work[0]].pad]) < 31
                     && SS_IABS(D_800D20A1_main[GwPlayer[obj->work[0]].pad]) < 31)) {
            func_8010A0B0_snowball_summit(obj);
        } else {
            func_8010A384_snowball_summit(obj);
        }
    } else {
        func_8010A384_snowball_summit(obj);
    }
    if ((D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x4000) && pl->rolling == 0) {
        func_8010A71C_snowball_summit(obj);
    }
    if (pl->rolling == 0) {
        if (pl->holdTime > 0) {
            pl->holdTime--;
        } else {
            pl->holdCount = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010AA78_snowball_summit);
#endif

/* Knocked into the air: fly backwards and fall. */
void func_8010AC94_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];

    pl->vel.x = sindf(SS_WRAP(pl->rot + 180.0f)) * pl->speed;
    pl->vel.y -= pl->gravity;
    pl->vel.z = cosdf(SS_WRAP(pl->rot + 180.0f)) * pl->speed;
    pl->next.x = obj->trans.x + pl->vel.x;
    pl->next.y = obj->trans.y + pl->vel.y;
    pl->next.z = obj->trans.z + pl->vel.z;
    if (pl->next.y < 0.0f && pl->unk4C == 0) {
        pl->land = 2;
        pl->speed = pl->gravity = pl->vel.x = pl->vel.y = pl->vel.z = pl->next.y = 0.0f;
    }
}

/* Hit reactions: knocked down (land 1-3) or out (unk4C). */
void func_8010AE74_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];

    if (pl->unk4C != 0) {
        if (pl->motion != 8) {
            func_80107CA4_snowball_summit(obj, 8);
        }
    } else if (pl->land == 1) {
        if (pl->motion != 7) {
            func_80107CA4_snowball_summit(obj, 7);
            func_8001C814_main(obj->model[0], 2, 0);
            func_8001C814_main(obj->model[0], 1, 1);
        }
    } else if (pl->land == 2) {
        func_80107CA4_snowball_summit(obj, 7);
        func_8001C814_main(obj->model[0], 1, 0);
        pl->land = 3;
    } else if (pl->land == 3) {
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
            func_80107CA4_snowball_summit(obj, 0);
            pl->land = 0;
            pl->hit = 0;
        }
    }
    if (pl->land == 1 && pl->hit != 0) {
        func_8010AC94_snowball_summit(obj);
    }
}

/* After the time is up: stand still, drop the snowball. */
// register allocation only (masked 0: obj/pl swap s0/s1)
#ifdef NON_MATCHING
void func_8010B01C_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    SsBall *ball;

    switch (pl->hit) {
        case 0:
            if (pl->motion != 0) {
                func_80107D30_snowball_summit(obj, 0, 0, 10);
                if (pl->ball != -1) {
                    ball = &D_8010FC30_snowball_summit[pl->ball];
                    ball->state = 20;
                    ball->owner = -1;
                    pl->rolling = 0;
                    pl->ball = -1;
                }
            }
            break;
        case 1:
            if (obj->trans.y == 0.0f && pl->motion != 0) {
                func_80107D30_snowball_summit(obj, 0, 0, 10);
                obj->rot.y = 0.0f;
                break;
            }
        case 2:
            func_8010AE74_snowball_summit(obj);
            break;
        case 3:
            func_8010AE74_snowball_summit(obj);
            break;
    }
    if (pl->motion == 0) {
        obj->rot.y = 0.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B01C_snowball_summit);
#endif

/* The result pose: win (motion 9 and the character's voice) or lose (10). */
void func_8010B158_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    s32 voice = D_800A178C_main[GwPlayer[obj->work[0]].chr][0];

    if (D_80110044_snowball_summit != 0) {
        if (pl->hit == 0 && pl->motion != 9) {
            func_80107CA4_snowball_summit(obj, 9);
            func_8001C814_main(obj->model[0], 2, 0);
            func_80045ED0_main(voice | 0x2F);
        }
    } else if (pl->motion != 10) {
        func_80107CA4_snowball_summit(obj, 10);
        func_8001C814_main(obj->model[0], 2, 0);
    }
}

void func_8010B250_snowball_summit(omObjData *obj) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[obj->work[0]];

    if (pl->state != -1) {
        switch (D_8010F880_snowball_summit) {
            case 2:
                if (pl->cpu != 0) {
                    func_8010811C_snowball_summit(obj);
                }
                if (pl->hit == 0) {
                    func_8010AA78_snowball_summit(obj);
                } else {
                    func_8010AE74_snowball_summit(obj);
                }
                break;
            case 3:
                func_80105B9C_snowball_summit(obj->work[0]);
                func_8010B01C_snowball_summit(obj);
                break;
            case 4:
                func_80105B9C_snowball_summit(obj->work[0]);
                func_8010B158_snowball_summit(obj);
                break;
            case 0:
            case 1:
            case 5:
                func_80105B9C_snowball_summit(obj->work[0]);
                break;
        }
    }
}

/* A player's setup: model, motions, shadow, start corner and CPU tuning. */
void func_8010B34C_snowball_summit(omObjData *obj) {
    SsPlayer *pl;
    u16 chr;

    chr = GwPlayer[obj->work[0]].chr;
    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][1], 0x2B9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x89));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x85));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x86));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x87));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x88));
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0xF));
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x9F));
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x38));
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(HmfModelData[obj->model[1]].mtx, 0.0f, 10.0f, 0.0f);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    if (obj->work[0] == 0) {
        D_8010F8A8_snowball_summit = rand8() & 3;
        obj->trans.x = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].x;
        obj->trans.y = 0.0f;
        obj->trans.z = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].z;
        obj->rot.y = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].rot;
    } else {
        if (++D_8010F8A8_snowball_summit >= 4) {
            D_8010F8A8_snowball_summit = 0;
        }
        obj->trans.x = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].x;
        obj->trans.y = 0.0f;
        obj->trans.z = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].z;
        obj->rot.y = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].rot;
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y + 20.0f + 5.0f, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    obj->func = func_8010B250_snowball_summit;
    pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    pl->state = 0;
    pl->motion = 0;
    pl->cpu = GwPlayer[obj->work[0]].stat & 1;
    pl->level = GwPlayer[obj->work[0]].cpu_difficulty;
    pl->speed = 0.0f;
    pl->rot = 0.0f;
    pl->unk1C = 0.0f;
    pl->holdTime = 30;
    pl->holdCount = 0;
    pl->rolling = 0;
    pl->vel.x = 0.0f;
    pl->vel.y = 0.0f;
    pl->vel.z = 0.0f;
    pl->gravity = 0.0f;
    pl->next.x = obj->trans.x;
    pl->next.y = obj->trans.y;
    pl->next.z = obj->trans.z;
    pl->hit = 0;
    pl->unk4C = 0;
    pl->unk50 = 50.0f;
    pl->unk54 = 150.0f;
    pl->unk6C = 0;
    pl->ball = -1;
    pl->land = 0;
    pl->obj = obj;
    pl->hold = 0;
    switch (pl->level) {
        case 0:
            pl->holdRate = 90;
            pl->range = 200;
            pl->chase = 6;
            pl->dodge = 4;
            pl->timer = 0;
            pl->stickX = pl->stickZ = 0;
            pl->size = 1.7f;
            break;
        case 1:
            pl->holdRate = 100;
            pl->range = 250;
            pl->chase = 5;
            pl->dodge = 5;
            pl->timer = 0;
            pl->stickX = pl->stickZ = 0;
            pl->size = 2.0f;
            break;
        case 2:
            pl->holdRate = 120;
            pl->range = 300;
            pl->chase = 4;
            pl->dodge = 10;
            pl->timer = 0;
            pl->stickX = pl->stickZ = 0;
            pl->size = 1.7f;
            break;
        default:
            pl->holdRate = 140;
            pl->range = 400;
            pl->chase = 10;
            pl->dodge = 12;
            pl->timer = 0;
            pl->stickX = pl->stickZ = 0;
            pl->size = 2.0f;
            break;
    }
}

void func_8010B8E4_snowball_summit(void) {
    omObjData *obj;
    s32 player;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(300, 9, 60, -1, func_8010B34C_snowball_summit);
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
        obj->work[0] = player;
    }
}

/* Takes a free snowball for obj's player; -1 if none. */
s32 func_8010B994_snowball_summit(omObjData *obj) {
    SsBall *ball;
    s32 i;

    for (i = 0; i < 16; i++) {
        ball = &D_8010FC30_snowball_summit[i];
        if (ball->state == 0) {
            ball->state = 1;
            ball->owner = obj->work[0];
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B9E4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010BC7C_snowball_summit);

void func_8010BE8C_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(400, 2, 0, -1, func_8010BC7C_snowball_summit)->work[0] = i;
    }
}

/* The marker over a player: shown while it rolls (motion 2). */
void func_8010BEE8_snowball_summit(omObjData *obj) {
    SsSlot8 *sl = &D_801101C8_snowball_summit[obj->work[0]];
    SsPlayer *pl;

    if (sl->state != -1) {
        pl = &D_8010F9B8_snowball_summit[obj->work[0]];
        if (pl->state == -1) {
            sl->state = 0;
        }
        switch (sl->state) {
            case 0:
                func_8001C258_main(obj->model[0], 4, 4);
                if (pl->motion == 2) {
                    sl->state = 1;
                }
                break;
            case 1:
                func_8001C258_main(obj->model[0], 4, 0);
                if (pl->motion != 2) {
                    sl->state = 0;
                }
                break;
        }
        obj->trans.x = pl->next.x;
        obj->trans.y = pl->next.y + 50.0f;
        obj->trans.z = pl->next.z;
        obj->rot.y = pl->obj->rot.y;
    }
}

void func_8010C000_snowball_summit(omObjData *obj) {
    SsPlayer *pl;
    SsSlot8 *sl;

    if (obj->work[0] == 0) {
        obj->model[0] = D_8010F8AE_snowball_summit = func_8000B108_main(0x49000C, 0x1699);
    } else {
        obj->model[0] = Hu3DModelLink(D_8010F8AE_snowball_summit);
    }
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C814_main(obj->model[0], 2, 2);
    pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    obj->trans.x = pl->next.x;
    obj->trans.y = pl->next.y + 40.0f;
    obj->trans.z = pl->next.z;
    func_8001C8A8_main(obj->model[0], 2);
    obj->func = func_8010BEE8_snowball_summit;
    sl = &D_801101C8_snowball_summit[obj->work[0]];
    sl->state = 0;
    sl->obj = obj;
}

void func_8010C10C_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(510, 1, 1, -1, func_8010C000_snowball_summit)->work[0] = i;
    }
}

void func_8010C168_snowball_summit(omObjData *obj) {
}

void func_8010C170_snowball_summit(omObjData *obj) {
    SsPlayer *pl;
    SsSlot16 *sl;

    if (obj->work[0] == 0) {
        obj->model[0] = D_8010F8B0_snowball_summit = func_8000B108_main(0x49000B, 0x1699);
    } else {
        obj->model[0] = Hu3DModelLink(D_8010F8B0_snowball_summit);
    }
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C814_main(obj->model[0], 2, 2);
    pl = &D_8010F9B8_snowball_summit[obj->work[0]];
    obj->trans.x = pl->next.x;
    obj->trans.y = pl->next.y + 20.0f;
    obj->trans.z = pl->next.z;
    func_8001C8A8_main(obj->model[0], 2);
    obj->func = func_8010C168_snowball_summit;
    sl = &D_80110250_snowball_summit[obj->work[0]];
    sl->state = 0;
    sl->unk04 = 0;
    sl->unk08 = -1;
    sl->obj = obj;
}

void func_8010C288_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(520, 1, 1, -1, func_8010C170_snowball_summit)->work[0] = i;
    }
}

void func_8010C2E4_snowball_summit(omObjData *obj) {
}

void func_8010C2EC_snowball_summit(omObjData *obj) {
    if (D_8010F88C_snowball_summit > 0) {
        D_8010F88C_snowball_summit--;
        return;
    }
    D_8010F884_snowball_summit = 1;
    obj->func = func_8010C2E4_snowball_summit;
}

void func_8010C328_snowball_summit(omObjData *obj) {
    if (GMesStatGet() & 2) {
        D_8010F88C_snowball_summit = 20;
        obj->func = func_8010C2EC_snowball_summit;
    }
}

/* The last player standing, or -1. */
s32 func_8010C36C_snowball_summit(void) {
    SsPlayer *p;
    s32 i;
    s32 count;
    s32 last;

    i = 0;
    count = 0;
    last = -1;
    p = D_8010F9B8_snowball_summit;
    for (; i < 4; i++) {
        if (p[i].state >= 0 && p[i].state < 90) {
            count++;
            last = i;
        }
    }
    if (count == 1) {
        D_80110044_snowball_summit = 1;
        return last;
    }
    return -1;
}

void func_8010C3E4_snowball_summit(s32 player) {
    SsPlayer *pl = &D_8010F9B8_snowball_summit[player];

    GwPlayer[pl->obj->work[0]].bonusCoin = 10;
    GMesCreate(0x16, GwPlayer[pl->obj->work[0]].chr);
    HuAudSeqPlay(0x65);
}

void func_8010C46C_snowball_summit(omObjData *obj) {
    s32 winner;

    if (D_8010F88C_snowball_summit > 0) {
        D_8010F88C_snowball_summit--;
        return;
    }
    winner = func_8010C36C_snowball_summit();
    if (winner == -1) {
        GMesCreate(0x20);
        HuAudSeqPlay(0x6C);
        D_8010F88C_snowball_summit = 144;
    } else {
        func_8010C3E4_snowball_summit(winner);
    }
    obj->func = func_8010C328_snowball_summit;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C4F4_snowball_summit);

void func_8010C5C0_snowball_summit(omObjData *obj) {
    if (GMesStatGet() == 0) {
        D_8010F88C_snowball_summit = 15;
        obj->func = func_8010C4F4_snowball_summit;
    }
}

void func_8010C600_snowball_summit(omObjData *obj) {
    GMesCreate(14);
    HuAudSeqFadeOut(120);
    D_8010F88C_snowball_summit = 75;
    obj->func = func_8010C5C0_snowball_summit;
}

/* 1 when one player is left, -1 when none, else 0. */
s32 func_8010C648_snowball_summit(void) {
    SsPlayer *p;
    s32 i;
    s32 count;

    i = 0;
    count = 0;
    p = D_8010F9B8_snowball_summit;
    for (; i < 4; i++) {
        count += p[i].state >= 0 && p[i].state < 90;
    }
    if (count == 1) {
        return 1;
    }
    return -(count == 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C6A8_snowball_summit);

void func_8010C7A4_snowball_summit(omObjData *obj) {
    GMesCreate(0x1A, 60, 160, 28);
    D_8010F88C_snowball_summit = 1801;
    obj->func = func_8010C6A8_snowball_summit;
}

void func_8010C7F0_snowball_summit(omObjData *obj) {
    if (GMesStatGet() == 0 || (GMesStatGet() & 2)) {
        obj->func = func_8010C7A4_snowball_summit;
        D_8010F884_snowball_summit = 1;
        HuAudSeqPlay(0x30);
    }
}

void func_8010C850_snowball_summit(omObjData *obj) {
    GMesCreate(3);
    obj->func = func_8010C7F0_snowball_summit;
    D_8010F884_snowball_summit = 1;
}

/* The camera, once. */
void func_8010C890_snowball_summit(omObjData *obj) {
    Vec from;
    Vec to;
    Vec out;
    u32 i;

    if (D_8010F888_snowball_summit == 0) {
        D_8010F888_snowball_summit = 1;
        to.x = 1975.0f;
        to.y = 0;
        to.z = 2700.0f;
        from.x = -40.0f;
        from.y = 0;
        from.z = 45.0f;
        func_80105D64_snowball_summit(&from, &to, &out);
        for (i = 0; i < 2; i++) {
            CZoomM[i] = out.x;
            CRotM[i].x = 360.0f - out.z;
            CRotM[i].y = 0;
            CRotM[i].z = 0;
            CenterM[i].x = 0.0f;
            CenterM[i].y = from.x;
            CenterM[i].z = from.z;
        }
    }
}

void func_8010C9B4_snowball_summit(omObjData *obj) {
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void func_8010C9E0_snowball_summit(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010C9B4_snowball_summit;
    }
}

void func_8010CA18_snowball_summit(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010C9E0_snowball_summit;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8010CA70_snowball_summit(void) {
    D_8010F880_snowball_summit += D_8010F884_snowball_summit;
    D_8010F884_snowball_summit = 0;
}

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

void func_8010EEEC_snowball_summit(omObjData *obj) {
    func_8010CA70_snowball_summit();
    switch (D_8010F880_snowball_summit) {
        case 1:
            if (D_8010F5C8_snowball_summit == -1) {
                D_8010F5C8_snowball_summit = HuAudFXPlay(0x43D);
            }
            break;
        case 2:
        case 3:
            func_8010D86C_snowball_summit();
            func_8010EA68_snowball_summit();
            func_8010EBC0_snowball_summit();
            break;
        case 5:
            WipeCreateOut(0, 20);
            obj->func = func_8010C9E0_snowball_summit;
            break;
        case 0:
        case 4:
            break;
    }
}

void func_8010EFA0_snowball_summit(void) {
    SsPlayer *p;
    s32 i;

    i = 0;
    p = D_8010F9B8_snowball_summit;
    for (; i < 4; i++) {
        p[i].state = -1;
    }
}

void func_8010EFE4_snowball_summit(void) {
    SsSlider *p;
    s32 i;

    i = 0;
    p = D_80110200_snowball_summit;
    for (; i < 3; i++) {
        p[i].state = -1;
    }
}

void func_8010F020_snowball_summit(void) {
    SsFlash *p;
    s32 i;

    i = 0;
    p = D_80110048_snowball_summit;
    for (; i < 16; i++) {
        p[i].state = -1;
    }
}

void func_8010F05C_snowball_summit(void) {
    SsBall *p;
    s32 i;

    i = 0;
    p = D_8010FC30_snowball_summit;
    for (; i < 16; i++) {
        p[i].state = -1;
    }
}

void func_8010F090_snowball_summit(void) {
    SsRing *p;
    s32 i;

    i = 0;
    p = D_8010F8D8_snowball_summit;
    for (; i < 8; i++) {
        p[i].state = -1;
    }
}

void func_8010F0CC_snowball_summit(void) {
    SsSlot8 *p;
    s32 i;

    i = 0;
    p = D_801101C8_snowball_summit;
    for (; i < 4; i++) {
        p[i].state = -1;
    }
}

void func_8010F100_snowball_summit(void) {
    SsSlot16 *p;
    s32 i;

    i = 0;
    p = D_80110250_snowball_summit;
    for (; i < 4; i++) {
        p[i].state = -1;
    }
}

void func_8010F134_snowball_summit(void) {
    D_8010F880_snowball_summit = 0;
    D_8010F884_snowball_summit = 0;
    D_8010F888_snowball_summit = 0;
    D_80110044_snowball_summit = 0;
    D_80110248_snowball_summit = -1;
    D_801101E8_snowball_summit = 0;
    D_8011024C_snowball_summit = 0;
    func_8010EFA0_snowball_summit();
    func_8010EFE4_snowball_summit();
    func_8010F05C_snowball_summit();
    func_8010F020_snowball_summit();
    func_8010F0CC_snowball_summit();
    func_8010F100_snowball_summit();
    func_8010F090_snowball_summit();
}

void func_8010F1B8_snowball_summit(void) {
    func_8010F134_snowball_summit();
    func_801062AC_snowball_summit();
    func_801067FC_snowball_summit();
    func_80106968_snowball_summit();
    func_80107000_snowball_summit();
    func_801068B0_snowball_summit();
    func_8010B8E4_snowball_summit();
    func_8010BE8C_snowball_summit();
    func_80107330_snowball_summit();
    func_8010C10C_snowball_summit();
    func_8010C288_snowball_summit();
    func_80107700_snowball_summit();
    func_801078D4_snowball_summit();
}

void func_8010F234_snowball_summit(omObjData *obj) {
    func_8010F1B8_snowball_summit();
    WipeCreateIn(0xFF, 16);
    obj->func = func_8010EEEC_snowball_summit;
    omAddObj(100, 0, 0, -1, func_8010C890_snowball_summit);
    omAddObj(900, 0, 0, -1, func_8010C850_snowball_summit);
}

void func_8010F2B0_snowball_summit(omObjData *obj) {
}

void func_8010F2B8_snowball_summit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_8010F5CC_snowball_summit[i].scissor[0], D_8010F5CC_snowball_summit[i].scissor[1],
                   D_8010F5CC_snowball_summit[i].scissor[2], D_8010F5CC_snowball_summit[i].scissor[3]);
        ViewportSet(i, D_8010F5CC_snowball_summit[i].viewport[0], D_8010F5CC_snowball_summit[i].viewport[1],
                    D_8010F5CC_snowball_summit[i].viewport[2], D_8010F5CC_snowball_summit[i].viewport[3],
                    D_8010F5CC_snowball_summit[i].viewport[4], D_8010F5CC_snowball_summit[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010F5CC_snowball_summit[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010F42C_snowball_summit(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(100, 0);
    func_8004A208_main();
    func_8010F2B8_snowball_summit();
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, -215.0f, 295.0f, 470.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -215.0f, 295.0f, 470.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010F870_snowball_summit, 0);
    func_80045010_main(D_8010F870_snowball_summit, 1);
    omAddObj(1000, 0, 0, -1, func_8010F234_snowball_summit);
    omAddObj(1000, 0, 0, -1, func_8010CA18_snowball_summit);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", D_8010F870_snowball_summit);
