#include "common.h"
// m5 sc: Storm Chasers (4 players: stand under the storm cloud to fill your bucket)
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

/* A u8 random number below n. */
#define SC_RAND(n) ((u8)(rand8() % (n)))
/* An angle wrapped once into [0, 360) (its argument is evaluated again on each test). */
#define SC_WRAP(a) ((a) >= 360.0f ? (a) - 360.0f : (a) < 0.0f ? (a) + 360.0f : (a))
#define SC_ABS(x) ((x) < 0.0f ? -(x) : (x))

/* A player's state (D_8010CD80_storm_chasers, 4 x 0x58). */
typedef struct ScPlayer {
    /* 0x00 */ s32 state; /* -1 absent; the CPU's 20.. */
    /* 0x04 */ s32 isCpu;
    /* 0x08 */ s32 done;
    /* 0x0C */ s32 pos; /* start corner (D_8010C8D8_storm_chasers) */
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 score;
    /* 0x18 */ s32 voice; /* 1 winner voice pending, 2 played */
    /* 0x1C */ s32 rank;
    /* 0x20 */ s32 jump;
    /* 0x24 */ f32 y;
    /* 0x28 */ f32 vy;
    /* 0x2C */ f32 g;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s32 hit;
    /* 0x40 */ s32 timer;
    /* 0x44 */ omObjData *obj;
    /* 0x48 */ f32 radius; /* CPU: distance to the storm it tolerates */
    /* 0x4C */ s32 delay; /* CPU: base reaction delay */
    /* 0x50 */ s32 wait;
    /* 0x54 */ s16 stickX;
    /* 0x56 */ s16 stickZ;
} ScPlayer; // Size 0x58

/* A player's bucket (D_8010CCE0_storm_chasers, 4 x 0x28). */
typedef struct ScBucket {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 held;
    /* 0x08 */ s32 done;
    /* 0x0C */ f32 vy;
    /* 0x10 */ f32 g;
    /* 0x14 */ s32 t;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 z;
    /* 0x20 */ s16 sfx;
    /* 0x24 */ omObjData *obj;
} ScBucket; // Size 0x28

/* The storm cloud (D_8010CCC0_storm_chasers). */
typedef struct ScStorm {
    /* 0x00 */ s32 state;
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 angle;
    /* 0x0C */ s32 timer;
    /* 0x10 */ s32 mode;
    /* 0x14 */ f32 turn;
    /* 0x18 */ omObjData *obj;
    /* 0x1C */ s16 sfx[2];
} ScStorm; // Size 0x20

/* The rain (D_8010CF20_storm_chasers). */
typedef struct ScRain {
    /* 0x00 */ s32 state;
    /* 0x04 */ f32 scroll;
    /* 0x08 */ f32 alpha;
    /* 0x0C */ omObjData *obj;
} ScRain; // Size 0x10

/* A whirlwind (D_8010CEE0_storm_chasers, 2 x 0x14). */
typedef struct ScWind {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 step;
    /* 0x08 */ s32 wait;
    /* 0x0C */ s32 alpha;
    /* 0x10 */ omObjData *obj;
} ScWind; // Size 0x14

/* A player's hit flash (D_8010CF38_storm_chasers, 4 x 0xC). */
typedef struct ScFlash {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 alpha;
    /* 0x08 */ omObjData *obj;
} ScFlash; // Size 0xC


/* A start corner (D_8010C8D8_storm_chasers). */
typedef struct ScStart {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ f32 rot;
    /* 0x0C */ f32 bucketRot;
    /* 0x10 */ f32 turn;
} ScStart; // Size 0x14

/* A CPU's goal point (D_8010C928_storm_chasers). */
typedef struct ScGoal {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ f32 unk08;
} ScGoal; // Size 0xC

/* A bucket's landing point (D_8010CA8C_storm_chasers). */
typedef struct ScPoint {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
} ScPoint; // Size 8

/* One step of a whirlwind animation table (-1 ends it). */
/* A camera (D_8010CAB8_storm_chasers). */
typedef struct ScCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} ScCamera; // Size 0x2C

/* A texture's size (func_800335BC_main). */
typedef struct ScTexSize {
    /* 0x00 */ s16 w;
    /* 0x02 */ s16 h;
} ScTexSize;

/* The ground object's data. */
typedef struct ScGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} ScGround; // Size 0xB4

extern s32 fontcolor;
extern s32 D_800A178C_main[][6];
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u8 D_800D6A90_main;
extern u16 D_800D530C_main;
extern f32 D_800EB73C_minigame;
extern s32 D_800EBE24_minigame;
extern D_800CCF58_main_Struct *D_800CCF58_main;
void osViBlack(u8 active);
void func_8000BC48_main(u16, u16);
s32 func_8000B710_main(s32 arg0);
void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_8001EED8_main(s16 arg0, s16 arg1, s16 arg2);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_80032FC0_main(s16, u8, u8);
void func_80034048_main(s16, s16);
void func_800335BC_main(char *arg0, void *arg1);
void func_8004AE00_main(s16 handle, s16 pan);
void func_80088800_main(f32 *mtx, f32 x, f32 y, f32 z);
void func_800DDD94_minigame(omObjData *obj);
void func_800E1304_minigame(omObjData *obj, f32 arg1);
void func_800E1310_minigame(omObjData *obj, f32 arg1);
void func_800E131C_minigame(omObjData *obj, f32 arg1);
void func_800E1404_minigame(omObjData *obj, f32 arg1, f32 arg2);
void func_800E149C_minigame(omObjData *obj, u8 idx, u8 val);
void func_800E6F0C_minigame(s8 arg0);

/* m5 sc: prototypes */
void func_801059A0_storm_chasers(void);
Gfx **func_801059BC_storm_chasers(Gfx **gfx);
Gfx **func_80105AA0_storm_chasers(Gfx **gfx);
Gfx **func_80105B6C_storm_chasers(Gfx **gfx, u8 alpha);
void func_80105B9C_storm_chasers(s32 player);
f32 func_80105C14_storm_chasers(f32 x);
void func_80105D64_storm_chasers(Vec *from, Vec *to, Vec *out);
void func_801060E0_storm_chasers(u16 x, u16 y, char *str, u16 color);
f32 func_8010610C_storm_chasers(f32 x, f32 z);
void func_80106184_storm_chasers(f32 x0, f32 z0, f32 x1, f32 z1, Vec *out);
void func_801061C0_storm_chasers(omObjData *obj);
void func_80106218_storm_chasers(omObjData *obj);
void func_8010637C_storm_chasers(void);
void func_801063B0_storm_chasers(Gfx **gfx, s32 arg1, s32 arg2);
void func_80106624_storm_chasers(omObjData *obj);
void func_8010662C_storm_chasers(omObjData *obj);
void func_801066BC_storm_chasers(void);
void func_801066F4_storm_chasers(omObjData *obj);
void func_80106794_storm_chasers(omObjData *obj);
void func_801068C8_storm_chasers(omObjData *obj);
void func_801069EC_storm_chasers(void);
void func_80106A48_storm_chasers(omObjData *obj);
void func_80106F98_storm_chasers(omObjData *obj);
void func_801070A8_storm_chasers(omObjData *obj);
void func_8010746C_storm_chasers(omObjData *obj);
void func_801075C4_storm_chasers(void);
void func_801075F8_storm_chasers(omObjData *obj);
void func_801077A0_storm_chasers(omObjData *obj);
void func_801078A0_storm_chasers(void);
void func_801078E0_storm_chasers(omObjData *obj);
void func_80107EA4_storm_chasers(omObjData *obj);
void func_80107F70_storm_chasers(omObjData *obj);
void func_8010834C_storm_chasers(void);
void func_801083A8_storm_chasers(omObjData *obj);
void func_80108478_storm_chasers(omObjData *obj);
void func_801085E4_storm_chasers(omObjData *obj);
void func_801086C4_storm_chasers(omObjData *obj);
void func_80108738_storm_chasers(omObjData *obj);
void func_8010891C_storm_chasers(omObjData *obj);
void func_80108C64_storm_chasers(omObjData *obj);
void func_80108F88_storm_chasers(void);
void func_80108FF8_storm_chasers(omObjData *obj);
void func_801090A4_storm_chasers(omObjData *obj);
void func_80109170_storm_chasers(omObjData *obj);
void func_8010A070_storm_chasers(omObjData *obj);
void func_8010A260_storm_chasers(omObjData *obj);
void func_8010AC7C_storm_chasers(omObjData *obj);
void func_8010AD68_storm_chasers(omObjData *obj);
void func_8010AE4C_storm_chasers(omObjData *obj);
void func_8010AF20_storm_chasers(omObjData *obj);
void func_8010B1B0_storm_chasers(omObjData *obj);
void func_8010B738_storm_chasers(void);
void func_8010B838_storm_chasers(omObjData *obj);
void func_8010B840_storm_chasers(omObjData *obj);
void func_8010B87C_storm_chasers(omObjData *obj);
void func_8010B944_storm_chasers(omObjData *obj);
void func_8010B980_storm_chasers(omObjData *obj);
void func_8010BA00_storm_chasers(void);
void func_8010BD04_storm_chasers(void);
void func_8010BDF4_storm_chasers(omObjData *obj);
void func_8010BE8C_storm_chasers(omObjData *obj);
void func_8010BF3C_storm_chasers(omObjData *obj);
void func_8010BF84_storm_chasers(omObjData *obj);
void func_8010C014_storm_chasers(omObjData *obj);
void func_8010C060_storm_chasers(omObjData *obj);
void func_8010C0E0_storm_chasers(omObjData *obj);
void func_8010C120_storm_chasers(omObjData *obj);
void func_8010C240_storm_chasers(omObjData *obj);
void func_8010C264_storm_chasers(omObjData *obj);
void func_8010C29C_storm_chasers(omObjData *obj);
void func_8010C2F4_storm_chasers(void);
void func_8010C31C_storm_chasers(omObjData *obj);
void func_8010C3A8_storm_chasers(void);
void func_8010C3EC_storm_chasers(void);
void func_8010C428_storm_chasers(void);
void func_8010C438_storm_chasers(void);
void func_8010C448_storm_chasers(void);
void func_8010C484_storm_chasers(void);
void func_8010C4C0_storm_chasers(void);
void func_8010C520_storm_chasers(void);
void func_8010C57C_storm_chasers(omObjData *obj);
void func_8010C604_storm_chasers(void);
void func_8010C60C_storm_chasers(void);
void func_8010C780_storm_chasers(void);

/* .data */
extern D_80111B50_vine_with_me_Struct D_8010C8B0_storm_chasers;
extern ScStart D_8010C8D8_storm_chasers[4];
extern ScGoal D_8010C928_storm_chasers[4];
extern s32 D_8010C958_storm_chasers;
extern s32 D_8010C95C_storm_chasers;
extern s32 D_8010C960_storm_chasers[]; /* animation frames per step, -1 ends; read as s16 */
extern s32 D_8010C9C4_storm_chasers[]; /* animation frames per step, -1 ends; read as s16 */
extern s32 D_8010CA28_storm_chasers[]; /* animation frames per step, -1 ends; read as s16 */
extern ScPoint D_8010CA8C_storm_chasers[4];
extern s32 D_8010CAAC_storm_chasers;
extern s32 D_8010CAB0_storm_chasers;
extern s16 D_8010CAB4_storm_chasers;
extern ScCamera D_8010CAB8_storm_chasers[2];
/* .rodata */
extern const s16 D_8010CC8C_storm_chasers[];
/* .bss */
extern s32 D_8010CCA0_storm_chasers; /* game phase */
extern s32 D_8010CCA4_storm_chasers; /* phase advance */
extern u16 D_8010CCA8_storm_chasers;
extern s32 D_8010CCAC_storm_chasers; /* phase timer */
extern u8 D_8010CCB0_storm_chasers; /* bucket motion */
extern ScStorm D_8010CCC0_storm_chasers;
/* Several functions address D_8010CCC0's fields as separate symbols (no shared base): views of it. */
extern f32 D_8010CCC4_storm_chasers; /* D_8010CCC0.speed */
extern f32 D_8010CCC8_storm_chasers; /* D_8010CCC0.angle */
extern s32 D_8010CCCC_storm_chasers; /* D_8010CCC0.timer */
extern omObjData *D_8010CCD8_storm_chasers; /* D_8010CCC0.obj */
extern s16 D_8010CCDC_storm_chasers; /* D_8010CCC0.sfx[0] */
extern s16 D_8010CCDE_storm_chasers; /* D_8010CCC0.sfx[1] */
extern ScBucket D_8010CCE0_storm_chasers[4];
extern ScPlayer D_8010CD80_storm_chasers[4];
extern ScWind D_8010CEE0_storm_chasers[2];
extern s16 D_8010CF08_storm_chasers;
extern s16 D_8010CF0A_storm_chasers;
extern f32 D_8010CF0C_storm_chasers;
extern f32 D_8010CF10_storm_chasers;
extern s32 D_8010CF18_storm_chasers;
extern ScTexSize D_8010CF1C_storm_chasers;
extern ScRain D_8010CF20_storm_chasers;
/* func_801077A0_storm_chasers stores D_8010CF20's fields as separate symbols (no shared base): views of it. */
extern f32 D_8010CF24_storm_chasers; /* D_8010CF20.scroll */
extern f32 D_8010CF28_storm_chasers; /* D_8010CF20.alpha */
extern omObjData *D_8010CF2C_storm_chasers; /* D_8010CF20.obj */
extern s32 D_8010CF30_storm_chasers; /* whirlwind motions: retail reads the low halves */
extern s32 D_8010CF34_storm_chasers;
extern ScFlash D_8010CF38_storm_chasers[4];
typedef s32 (*ScDrawHookAdd)(s32, void (*)(Gfx **, s32, s32), u8);

typedef struct ScScreen {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 grp;
    /* 0x08 */ s32 draw;
    /* 0x0C */ HuSprite_Unk84_Struct *spr;
} ScScreen;
/* The screen overlay. func_8010662C_storm_chasers addresses its fields as separate symbols (no shared base):
   D_8010CF6C/70/74 are views of D_8010CF68's grp/draw/spr. */
extern ScScreen D_8010CF68_storm_chasers;
extern s32 D_8010CF6C_storm_chasers; /* D_8010CF68.grp (retail reads the low half) */
extern s32 D_8010CF70_storm_chasers; /* D_8010CF68.draw (retail reads the low half) */
extern HuSprite_Unk84_Struct *D_8010CF74_storm_chasers; /* D_8010CF68.spr */

void func_8010C780_storm_chasers(void);
void func_80106624_storm_chasers(omObjData *obj);
void func_801066F4_storm_chasers(omObjData *obj);
void func_80106A48_storm_chasers(omObjData *obj);
void func_80106F98_storm_chasers(omObjData *obj);
void func_801090A4_storm_chasers(omObjData *obj);
void func_8010B838_storm_chasers(omObjData *obj);
void func_8010BA00_storm_chasers(void);
void func_8010C2F4_storm_chasers(void);

void func_801059A0_storm_chasers(void) {
    func_8010C780_storm_chasers();
}

Gfx **func_801059BC_storm_chasers(Gfx **gfx) {
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

Gfx **func_80105AA0_storm_chasers(Gfx **gfx) {
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

Gfx **func_80105B6C_storm_chasers(Gfx **gfx, u8 alpha) {
    Gfx *g;

    g = *gfx;
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, alpha);
    *gfx = g;
    return gfx;
}

/* Clears a player's pad input (the CPU writes its own). */
void func_80105B9C_storm_chasers(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

/* arctan by continued fraction (radians). */
f32 func_80105C14_storm_chasers(f32 x) {
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

/* Distance (out->x) and heading (out->z, degrees) from one point to another. */
void func_80105D64_storm_chasers(Vec *from, Vec *to, Vec *out) {
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
            yaw = func_80105C14_storm_chasers(delta.x / delta.z) * 57.29577951308232;
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
            pitch = func_80105C14_storm_chasers(delta.y / horizontal) * 57.29577951308232;
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

void func_801060E0_storm_chasers(u16 x, u16 y, char *str, u16 color) {
    fontcolor = color;
    print8(x, y, str);
}

/* Heading of (x, z) from the origin, in [0, 360). */
f32 func_8010610C_storm_chasers(f32 x, f32 z) {
    f32 a = atan2df(x, z);

    if (a > 360.0) {
        a -= 360.0;
    } else if (a < 0.0) {
        a += 360.0;
    }
    return a;
}

/* Distance and heading from (x1, z1) to (x0, z0) on the ground. */
void func_80106184_storm_chasers(f32 x0, f32 z0, f32 x1, f32 z1, Vec *out) {
    Vec from;
    Vec to;

    to.x = x0;
    to.y = 0;
    to.z = z0;
    from.x = x1;
    from.y = 0;
    from.z = z1;
    func_80105D64_storm_chasers(&from, &to, out);
}

void func_801061C0_storm_chasers(omObjData *obj) {
    func_8000BBD4_main(D_8010CF0A_storm_chasers, D_8010CF0C_storm_chasers, D_8010CF10_storm_chasers);
}

void func_80106218_storm_chasers(omObjData *obj) {
    ScGround *gw;
    s16 grp;

    D_8010CF0C_storm_chasers = 160.0f;
    D_8010CF10_storm_chasers = 120.0f;
    grp = func_8000B838_main(0x500000);
    D_8010CF08_storm_chasers = grp;
    D_8010CF0A_storm_chasers = InitEspriteSlot(grp, 0, 0);
    func_8000BC48_main(D_8010CF0A_storm_chasers, 0x5000);
    func_8000BBD4_main(D_8010CF0A_storm_chasers, D_8010CF0C_storm_chasers, D_8010CF10_storm_chasers);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
    obj->data = gw = HuMemAllocTag(sizeof(ScGround), 31000);
    memset(gw, 0, sizeof(ScGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E1404_minigame(D_800EC1C0_minigame[0], 0.0f, 500.0f);
    obj->func = func_801061C0_storm_chasers;
}

void func_8010637C_storm_chasers(void) {
    omAddObj(150, 1, 0, -1, func_80106218_storm_chasers);
}

/* Draws the bottom band of the screen (rows 134..240) from a CI8 sprite, two rows at a time. */
void func_801063B0_storm_chasers(Gfx **gfx, s32 arg1, s32 arg2) {
    ScScreen *scr = &D_8010CF68_storm_chasers;
    Gfx *g;
    s32 i;

    if (scr->state != -1) {
        gfx = func_801059BC_storm_chasers(gfx);
        g = *gfx;
        gDPSetTextureLUT(g++, G_TT_RGBA16);
        gDPLoadTLUT_pal256(g++, scr->spr->unk0C);
        for (i = 0; i < 106; i += 2) {
            gDPLoadTextureTile(g++, scr->spr->unk08, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, i, 320,
                               i + 2, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 320 << 2, 2 << 2);
            gSPTextureRectangle(g++, 0, (i + 134) << 2, 320 << 2, (i + 136) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                                1 << 10);
        }
        *gfx = g;
    }
}

void func_80106624_storm_chasers(omObjData *obj) {
}

void func_8010662C_storm_chasers(omObjData *obj) {
    ScDrawHookAdd hookAdd = (ScDrawHookAdd)(void (*)(void))func_8001AC8C_main;

    D_8010CF6C_storm_chasers = func_8000B838_main(0x500001);
    D_8010CF74_storm_chasers = func_80055194_main((s16)D_8010CF6C_storm_chasers);
    /* retail stores this s16 return unextended: it called func_8001AC8C_main as returning int */
    D_8010CF70_storm_chasers = hookAdd(0, func_801063B0_storm_chasers, 2);
    func_8001C8A8_main((s16)D_8010CF70_storm_chasers, 1);
    obj->func = func_80106624_storm_chasers;
    D_8010CF68_storm_chasers.state = 0;
}

void func_801066BC_storm_chasers(void) {
    omAddObj(160, 1, 0, -1, func_8010662C_storm_chasers)->work[0] = 0;
}

/* Starts a player's hit flash. */
void func_801066F4_storm_chasers(omObjData *obj) {
    ScFlash *fl = &D_8010CF38_storm_chasers[obj->work[0]];

    fl->state = 1;
    fl->obj->trans.x = obj->trans.x;
    fl->obj->trans.y = 100.0f;
    fl->obj->trans.z = obj->trans.z + 80.0f;
    if (D_8010C95C_storm_chasers == -1) {
        D_8010C95C_storm_chasers = HuAudFXPlay(0x487);
    }
}

void func_80106794_storm_chasers(omObjData *obj) {
    ScFlash *fl = &D_8010CF38_storm_chasers[obj->work[0]];

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
            fl->alpha -= 25;
            if (fl->alpha > 0) {
                func_8001F9E4_main(obj->model[0], fl->alpha);
                obj->scale.x += 0.1;
                obj->scale.y += 0.1;
                obj->scale.z += 0.1;
            } else {
                func_8001C258_main(obj->model[0], 4, 4);
                fl->alpha = 0xFF;
                fl->state = 0;
                obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
            }
            break;
    }
}

void func_801068C8_storm_chasers(omObjData *obj) {
    ScPlayer *pl;
    ScFlash *fl;

    obj->model[0] = func_8000B108_main(0x50000D, 0x289);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xFF);
    func_8001C258_main(obj->model[0], 4, 4);
    pl = &D_8010CD80_storm_chasers[obj->work[0]];
    obj->trans.x = pl->obj->trans.x;
    obj->trans.y = 100.0f;
    obj->trans.z = pl->obj->trans.z + 80.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_80106794_storm_chasers;
    fl = &D_8010CF38_storm_chasers[obj->work[0]];
    fl->state = 0;
    fl->alpha = 0xFF;
    fl->obj = obj;
}

void func_801069EC_storm_chasers(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(210, 1, 0, -1, func_801068C8_storm_chasers)->work[0] = i;
    }
}

/* The storm wanders: a new heading, speed and turn when its timer runs out; turned back at the edge. */
void func_80106A48_storm_chasers(omObjData *obj) {
    ScStorm *st = &D_8010CCC0_storm_chasers;
    f32 a;

    if (st->timer > 0) {
        st->timer--;
    } else {
        st->angle = rand16() % 360;
        st->speed = SC_RAND(7) + 6;
        st->timer = SC_RAND(30) + 45;
        st->mode = SC_RAND(3);
        if (st->mode == 0) {
            st->turn = SC_RAND(9) + 1;
            if (rand8() & 1) {
                st->turn = -st->turn;
            }
        } else {
            st->turn = 0.0f;
        }
    }
    if (obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z > 160000.0f) {
        a = func_8010610C_storm_chasers(obj->trans.x, obj->trans.z);
        st->angle = SC_WRAP(a + 135.0f + SC_RAND(90));
        st->speed = SC_RAND(7) + 6;
        st->timer = SC_RAND(30) + 20;
        st->turn = 0.0f;
    }
    st->angle = SC_WRAP(st->angle + st->turn);
    obj->trans.x += sindf(st->angle) * st->speed;
    obj->trans.z += cosdf(st->angle) * st->speed;
}

/* The storm rises away once the rain has faded. */
void func_80106F98_storm_chasers(omObjData *obj) {
    f32 s;

    D_8010CCC4_storm_chasers = 0;
    D_8010CCC8_storm_chasers = 0;
    D_8010CCCC_storm_chasers = 0;
    if (!(D_8010CF28_storm_chasers > 0.0f)) {
        obj->trans.y += 20.0f;
        if (obj->trans.y > 1000.0f) {
            obj->trans.y = 1000.0f;
            func_8001C258_main(obj->model[0], 4, 4);
            func_8001C258_main(obj->model[1], 4, 4);
            return;
        }
        s = (1000.0f - obj->trans.y) / 800.0f * 1.3;
        Hu3DModelScaleSet(obj->model[1], s, s, s);
    }
}

void func_801070A8_storm_chasers(omObjData *obj) {
    ScStorm *st = &D_8010CCC0_storm_chasers;
    f32 vol;
    s8 pan;

    if (st->state != -1) {
        if (D_8010CCA0_storm_chasers == 1
            && (D_8010CCDC_storm_chasers == -1 || D_8010CCDE_storm_chasers == -1)) {
            st->sfx[0] = HuAudFXPlay(0x481);
            st->sfx[1] = HuAudFXPlay(0x482);
            func_8004AAD0_main(st->sfx[0], 64);
            func_8004AAD0_main(st->sfx[1], 64);
            func_8004AE00_main(st->sfx[0], 64);
            func_8004AE00_main(st->sfx[1], 64);
        }
        switch (D_8010CCA0_storm_chasers) {
            case 0:
            case 1:
                st->angle = rand16() % 360;
                st->speed = SC_RAND(7) + 6;
                st->timer = SC_RAND(30) + 45;
                st->turn = 0;
                if (st->sfx[0] != -1 && st->sfx[1] != -1) {
                    vol = (obj->trans.z + 400.0f) / 800.0f;
                    func_8004AAD0_main(st->sfx[0], (s32)((1.0f - vol) * 64.0f) + 32);
                    func_8004AAD0_main(st->sfx[1], (s32)(vol * 64.0f) + 32);
                    vol = (obj->trans.x + 400.0f) / 800.0f;
                    pan = (1.0f - vol) * 64.0f;
                    func_8004AE00_main(st->sfx[0], pan + 32);
                    func_8004AE00_main(st->sfx[1], pan + 32);
                }
                break;
            case 2:
                func_80106A48_storm_chasers(obj);
                vol = (obj->trans.z + 400.0f) / 800.0f;
                func_8004AAD0_main(st->sfx[0], (s32)((1.0f - vol) * 64.0f) + 32);
                func_8004AAD0_main(st->sfx[1], (s32)(vol * 64.0f) + 32);
                vol = (obj->trans.x + 400.0f) / 800.0f;
                    pan = (1.0f - vol) * 64.0f;
                func_8004AE00_main(st->sfx[0], pan + 32);
                func_8004AE00_main(st->sfx[1], pan + 32);
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                func_80106F98_storm_chasers(obj);
                if (st->sfx[0] != -1) {
                    func_8004AEF0_main(st->sfx[0], 30);
                    st->sfx[0] = -1;
                }
                if (st->sfx[1] != -1) {
                    func_8004AEF0_main(st->sfx[1], 30);
                    st->sfx[1] = -1;
                }
                break;
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, -10.0f, obj->trans.z);
    }
}

void func_8010746C_storm_chasers(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x500006, 0x289);
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(HmfModelData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    obj->trans.x = 0.0f;
    obj->trans.y = 350.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, -10.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], 1.5f, 1.5f, 1.5f);
    func_8001C814_main(obj->model[0], 2, 2);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    obj->func = func_801070A8_storm_chasers;
    D_8010CCC0_storm_chasers.state = 0;
    D_8010CCDE_storm_chasers = -1;
    D_8010CCDC_storm_chasers = -1;
    D_8010CCD8_storm_chasers = obj;
}

void func_801075C4_storm_chasers(void) {
    omAddObj(170, 2, 1, -1, func_8010746C_storm_chasers);
}

/* The rain follows the storm, its texture scrolling; it fades out once the round is over. */
void func_801075F8_storm_chasers(omObjData *obj) {
    ScRain *rain = &D_8010CF20_storm_chasers;
    ScStorm *storm;

    if (rain->state == -1) {
        return;
    }
    storm = &D_8010CCC0_storm_chasers;
    if (storm->state != -1) {
        if (func_80049F98_main() + D_800D6A90_main == 0) {
            rain->scroll -= 4.0f;
        }
        func_8001E888_main(obj->model[0], 0, rain->scroll, D_8010CF1C_storm_chasers.w,
                           D_8010CF1C_storm_chasers.h, "247_1-ame", 0);
        obj->trans.x = storm->obj->trans.x;
        obj->trans.y = 0;
        obj->trans.z = storm->obj->trans.z;
        if (D_8010CCA0_storm_chasers >= 3) {
            rain->alpha -= 20.0f;
            if (rain->alpha < 0.0f) {
                rain->alpha = 0.0f;
                func_8001C258_main(obj->model[0], 4, 4);
                return;
            }
            func_8001F9E4_main(obj->model[0], rain->alpha);
        }
    }
}

void func_801077A0_storm_chasers(omObjData *obj) {
    if (D_8010CCC0_storm_chasers.state != -1) {
        obj->model[0] = func_8000B108_main(0x500007, 0x289);
        func_8001C954_main(obj->model[0]);
        func_8001FA68_main(obj->model[0]);
        func_8001F9E4_main(obj->model[0], 0xFF);
        func_8001C258_main(obj->model[0], 4, 0);
        func_800335BC_main("247_ame_IA44", &D_8010CF1C_storm_chasers);
        obj->trans.x = D_8010CCC0_storm_chasers.obj->trans.x;
        obj->trans.y = 0;
        obj->trans.z = D_8010CCC0_storm_chasers.obj->trans.z;
        func_8001C8A8_main(obj->model[0], 1);
        obj->func = func_801075F8_storm_chasers;
        D_8010CF20_storm_chasers.state = 0;
        D_8010CF24_storm_chasers = 0;
        D_8010CF28_storm_chasers = 255.0f;
        D_8010CF2C_storm_chasers = obj;
    }
}

void func_801078A0_storm_chasers(void) {
    omSetStatBit(omAddObj(180, 1, 0, -1, func_801077A0_storm_chasers), 0xA0);
}

/* A whirlwind: waits, appears at a random spot, plays its rise and fade, then waits again. */
void func_801078E0_storm_chasers(omObjData *obj) {
    ScWind *w = &D_8010CEE0_storm_chasers[obj->work[0]];
    f32 ang;
    f32 r;
    f32 a;

    if (w->wait > 0) {
        w->wait--;
        return;
    }
    switch (w->state) {
        case 0:
            if (D_8010CCAC_storm_chasers >= 91) {
                func_8001C258_main(obj->model[1], 4, 0);
                if (w->state == 0) {
                    ang = (SC_RAND(5) + 1) * 30;
                    r = ((rand8() & 3) + 1) * 80;
                    if (obj->work[0] != 0) {
                        ang = SC_WRAP(ang + 180.0f);
                    }
                    obj->trans.x = sindf(ang) * r;
                    obj->trans.y = 0.0f;
                    obj->trans.z = cosdf(ang) * r;
                    w->state = 1;
                }
                if (obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z > 122500.0f) {
                    a = func_8010610C_storm_chasers(obj->trans.x, obj->trans.z);
                    obj->trans.x = sindf(a) * (350 - SC_RAND(50));
                    obj->trans.z = cosdf(a) * (350 - SC_RAND(50));
                }
                func_80034048_main(obj->work[2], D_8010C9C4_storm_chasers[w->step]);
                w->step++;
            }
            break;
        case 1:
            if (D_8010C9C4_storm_chasers[w->step] == -1) {
                HuAudFXPlay(0x483);
                func_8001C258_main(obj->model[0], 4, 0);
                func_8001C258_main(obj->model[1], 4, 0);
                func_8001C258_main(obj->model[2], 4, 0);
                w->step = 0;
                w->state = 2;
                func_8001C814_main(obj->model[2], 1, 0);
                func_80034048_main(obj->work[1], D_8010C960_storm_chasers[w->step]);
                func_80034048_main(obj->work[2], D_8010CA28_storm_chasers[w->step]);
                w->step++;
                func_8001F9E4_main(obj->model[2], w->alpha);
            } else {
                func_80034048_main(obj->work[2], D_8010C9C4_storm_chasers[w->step]);
                w->step++;
            }
            break;
        case 2:
            if (D_8010C960_storm_chasers[w->step] == -1) {
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 4);
                func_8001C258_main(obj->model[2], 4, 4);
                func_8001C6A8_main(obj->model[2], 0.0f);
                func_8001C814_main(obj->model[2], 1, 1);
                w->alpha = 0xFF;
                w->step = 0;
                w->wait = SC_RAND(75) + 75;
                w->state = 0;
            } else {
                if (HmfModelData[obj->model[2]].unk40 > 30.0f) {
                    w->alpha -= 52;
                    if (w->alpha < 0) {
                        w->alpha = 0xFF;
                        func_8001C258_main(obj->model[2], 4, 4);
                    }
                }
                func_8001F9E4_main(obj->model[2], w->alpha);
                func_80034048_main(obj->work[1], D_8010C960_storm_chasers[w->step]);
                func_80034048_main(obj->work[2], D_8010CA28_storm_chasers[w->step]);
                w->step++;
            }
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
}

void func_80107EA4_storm_chasers(omObjData *obj) {
    ScWind *w = &D_8010CEE0_storm_chasers[obj->work[0]];

    if (w->state != -1) {
        switch (D_8010CCA0_storm_chasers) {
            case 2:
                func_801078E0_storm_chasers(obj);
                break;
            case 3:
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 4);
                func_8001C258_main(obj->model[2], 4, 4);
                w->state = 0;
                break;
            case 0:
            case 1:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                break;
        }
    }
}

void func_80107F70_storm_chasers(omObjData *obj) {
    void *data;
    ScWind *w;
    s32 i;

    obj->model[0] = func_8000B108_main(0x500008, 0x2A9);
    obj->model[1] = func_8000B108_main(0x50000A, 0x2A9);
    obj->model[2] = func_8000B108_main(0x50000C, 0x2A9);
    if (obj->work[0] == 0) {
        data = DataRead(0x500009);
        obj->work[1] = D_8010CF30_storm_chasers =
            (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "247_tyropu1_DEF");
        HuMemMemoryFreePerm(data);
        data = DataRead(0x50000B);
        obj->work[2] = D_8010CF34_storm_chasers =
            (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "s247_004_DEF");
        HuMemMemoryFreePerm(data);
    } else {
        obj->work[1] =
            func_80032694_main(HmfModelData[obj->model[0]].hmf, D_8010CF30_storm_chasers, 0, "247_tyropu1_DEF");
        obj->work[2] =
            func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8010CF34_storm_chasers, 0, "s247_004_DEF");
    }
    for (i = 0; i < 2; i++) {
        func_80034048_main(obj->work[i + 1], 0);
        func_80032FC0_main(obj->work[i + 1], 1, 1);
        func_8001C448_main(obj->model[i]);
        func_8001C514_main(obj->model[i]);
        func_8001C258_main(obj->model[i], 4, 4);
    }
    func_8001FA68_main(obj->model[2]);
    func_8001F9E4_main(obj->model[2], 0xFF);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C6A8_main(obj->model[2], 0.0f);
    func_8001C814_main(obj->model[2], 1, 1);
    func_8001C814_main(obj->model[2], 2, 0);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = 1.3f;
    for (i = 1; i < 3; i++) {
        Hu3DModelPosSet(obj->model[i], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelScaleSet(obj->model[i], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    for (i = 0; i < 3; i++) {
        func_8001C8A8_main(obj->model[i], 1);
    }
    obj->func = func_80107EA4_storm_chasers;
    w = &D_8010CEE0_storm_chasers[obj->work[0]];
    w->state = 0;
    w->step = 0;
    w->wait = SC_RAND(75) + 75;
    w->alpha = 0xFF;
    w->obj = obj;
}

void func_8010834C_storm_chasers(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(400, 3, 1, -1, func_80107F70_storm_chasers)->work[0] = i;
    }
}

/* The bucket is thrown up from its player towards its landing point. */
void func_801083A8_storm_chasers(omObjData *obj) {
    ScBucket *b = &D_8010CCE0_storm_chasers[obj->work[0]];
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];

    obj->trans.x = pl->obj->trans.x;
    obj->trans.y = 100.0f;
    obj->trans.z = pl->obj->trans.z + 50.0f;
    obj->rot.y = D_8010C8D8_storm_chasers[pl->pos].bucketRot;
    b->vy = 14.0f;
    b->g = 2.0f;
    b->x = obj->trans.x;
    b->z = obj->trans.z;
    b->state = 2;
}

void func_80108478_storm_chasers(omObjData *obj) {
    ScBucket *b = &D_8010CCE0_storm_chasers[obj->work[0]];
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];

    if (obj->trans.y > 0.0f) {
        obj->trans.y += b->vy;
        b->vy -= b->g;
        b->t++;
        obj->trans.x = b->x - (b->x - D_8010CA8C_storm_chasers[pl->pos].x) * 0.05 * b->t;
        obj->trans.z = b->z - (b->z - D_8010CA8C_storm_chasers[pl->pos].z) * 0.05 * b->t;
    } else {
        obj->trans.y = 0.0f;
        obj->trans.x = D_8010CA8C_storm_chasers[pl->pos].x;
        obj->trans.z = D_8010CA8C_storm_chasers[pl->pos].z;
        b->done = 1;
    }
    if (D_8010CCA0_storm_chasers == 5) {
        b->state = 10;
    }
}

void func_801085E4_storm_chasers(omObjData *obj) {
    ScBucket *b = &D_8010CCE0_storm_chasers[obj->work[0]];
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];

    if (D_8010CAAC_storm_chasers == 1 && pl->rank == 0 && b->sfx == -1) {
        b->sfx = HuAudFXPlay(0x484);
    }
    if (pl->rank != 3) {
        func_8001C814_main(obj->model[0], 1, 0);
        b->state = 11;
    } else {
        b->state = 12;
        b->done = 2;
    }
}

void func_801086C4_storm_chasers(omObjData *obj) {
    ScBucket *b = &D_8010CCE0_storm_chasers[obj->work[0]];

    func_8001C5B4_main(obj->model[0], obj->motion[1]);
    func_8001C814_main(obj->model[0], 2, 2);
    b->state = 12;
}

/* The bucket's fill animation stops at the player's rank. */
void func_80108738_storm_chasers(omObjData *obj) {
    ScBucket *b = &D_8010CCE0_storm_chasers[obj->work[0]];
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];
    f32 end;

    if (pl->score != 0) {
        end = D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - pl->rank * 60;
    } else {
        end = D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 180;
    }
    if (HmfModelData[obj->model[0]].unk40 >= end - 2.0f) {
        if (pl->rank == 0 && b->sfx != -1) {
            HuAudFXStop(b->sfx);
            b->sfx = -1;
        }
        func_8001C6A8_main(obj->model[0], end);
        func_8001C814_main(obj->model[0], 1, 1);
        if (pl->rank == 0) {
            b->state = 13;
        } else {
            b->state = 12;
        }
        b->done = 2;
    }
}

void func_8010891C_storm_chasers(omObjData *obj) {
    ScBucket *b = &D_8010CCE0_storm_chasers[obj->work[0]];
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];
    Vec v;

    if (b->state == -1) {
        return;
    }
    switch (b->state) {
        case 0:
            if (b->held == 0) {
                b->state = 1;
                func_8001C258_main(obj->model[1], 4, 0);
            }
            obj->trans.x = pl->obj->trans.x;
            obj->trans.y = 100.0f;
            obj->trans.z = pl->obj->trans.z + 50.0f;
            break;
        case 1:
            func_801083A8_storm_chasers(obj);
            break;
        case 2:
            func_80108478_storm_chasers(obj);
            break;
        case 10:
            func_801085E4_storm_chasers(obj);
            break;
        case 11:
            func_80108738_storm_chasers(obj);
            break;
        case 13:
            func_801086C4_storm_chasers(obj);
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 1.0f, obj->trans.z + 10.0f);
    if (D_8010CCA0_storm_chasers == 2) {
        if (D_8010CCC0_storm_chasers.state == -1) {
            return;
        }
        pl = &D_8010CD80_storm_chasers[obj->work[0]];
        func_80106184_storm_chasers(D_8010CCD8_storm_chasers->trans.x, D_8010CCD8_storm_chasers->trans.z,
                                    pl->obj->trans.x + sindf(pl->obj->rot.y) * 50.0f,
                                    pl->obj->trans.z + sindf(pl->obj->rot.y) * 50.0f, &v);
        if (SC_ABS(v.x) < 85.0f) {
            /* filling: the gauge climbs to 2 and falls back, looping */
            pl->score++;
            if (obj->work[2] == 0) {
                if (obj->work[3] < 2) {
                    obj->work[3]++;
                } else {
                    obj->work[2] = 1;
                }
            } else if (obj->work[3] != 0) {
                obj->work[3]--;
            } else {
                obj->work[2] = 0;
            }
            func_80034048_main(obj->work[1], obj->work[3]);
        } else {
            if (obj->work[3] != 0) {
                obj->work[3]--;
            }
            func_80034048_main(obj->work[1], obj->work[3]);
        }
    } else {
        func_80034048_main(obj->work[1], 0);
    }
    if (D_8010CCA0_storm_chasers == 8 && b->sfx != -1) {
        func_8004AEF0_main(b->sfx, 30);
        b->sfx = -1;
    }
}

void func_80108C64_storm_chasers(omObjData *obj) {
    void *data;
    ScPlayer *pl;
    ScBucket *b;

    obj->model[0] = func_8000B108_main(0x500002, 0x289);
    func_8000B460_main(obj, 0, 0x500003);
    func_8000B460_main(obj, 1, 0x500004);
    if (obj->work[0] == 0) {
        data = DataRead(0x500005);
        obj->work[1] = D_8010CCB0_storm_chasers =
            HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "pakkun_optimized_00_DEF");
        HuMemMemoryFreePerm(data);
    } else {
        obj->work[1] = func_80032694_main(HmfModelData[obj->model[0]].hmf, D_8010CCB0_storm_chasers, 0,
                                          "pakkun_optimized_00_DEF");
    }
    func_80034048_main(obj->work[1], 0);
    func_80032FC0_main(obj->work[1], 1, 1);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(HmfModelData[obj->model[1]].mtx, 0.0f, 10.0f, 0.0f);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C6A8_main(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 2, 0);
    func_8001C814_main(obj->model[0], 1, 1);
    pl = &D_8010CD80_storm_chasers[obj->work[0]];
    obj->trans.x = pl->obj->trans.x;
    obj->trans.y = pl->obj->trans.y + 100.0f;
    obj->trans.z = pl->obj->trans.z + 50.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 1.0f, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    obj->func = func_8010891C_storm_chasers;
    b = &D_8010CCE0_storm_chasers[obj->work[0]];
    b->state = 0;
    b->held = 0;
    b->done = 0;
    b->t = 0;
    b->x = 0;
    b->z = 0;
    b->sfx = -1;
    b->obj = obj;
    func_801090A4_storm_chasers(obj);
}

void func_80108F88_storm_chasers(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        omAddObj(300, 2, 2, -1, func_80108C64_storm_chasers)->work[0] = i;
    }
}

/* The player takes the bucket back: it hangs from the player's hook again. */
void func_80108FF8_storm_chasers(omObjData *obj) {
    ScBucket *b = &D_8010CCE0_storm_chasers[obj->work[0]];

    if (b->state != -1) {
        func_8001C258_main(b->obj->model[0], 0x4000, 0x4000);
        func_8001EF6C_main(b->obj->model[0], obj->model[0], "item_hook");
        func_8001EED8_main(obj->model[0], obj->motion[22], 1);
        obj->work[1] = 1;
        b->held = 1;
    }
}

void func_801090A4_storm_chasers(omObjData *obj) {
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];
    ScBucket *b = &D_8010CCE0_storm_chasers[obj->work[0]];

    func_8001C258_main(obj->model[0], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[0], pl->obj->model[0], "item_hook");
    func_8001EED8_main(pl->obj->model[0], pl->obj->motion[22], 1);
    pl->obj->work[1] = 1;
    b->held = 1;
}

/* CPU: chase the storm (re-aimed with a random delay when it is further than the CPU's radius). */
#ifdef NON_MATCHING
void func_80109170_storm_chasers(omObjData *obj) {
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];
    ScStorm *storm = &D_8010CCC0_storm_chasers;
    Vec v;
    f32 a;

    if (obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z > 202500.0f) {
        a = func_8010610C_storm_chasers(obj->trans.x, obj->trans.z);
        D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = sindf(SC_WRAP(a + 180.0f + SC_RAND(3))) * 70.0f;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = -(s8)(cosdf(SC_WRAP(a + 180.0f + SC_RAND(3))) * 70.0f);
        pl->stickX = D_800CBB6E_main[GwPlayer[obj->work[0]].pad];
        pl->stickZ = D_800D20A1_main[GwPlayer[obj->work[0]].pad];
        pl->wait = SC_RAND(30) + pl->delay * 6;
    }
    if (pl->wait > 0) {
        pl->wait--;
        func_80106184_storm_chasers(storm->obj->trans.x, storm->obj->trans.z,
                                    obj->trans.x, obj->trans.z, &v);
        if (pl->radius < SC_ABS(v.x)) {
            D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = sindf(SC_WRAP(SC_RAND(3) + v.z)) * 70.0f;
            D_800D20A1_main[GwPlayer[obj->work[0]].pad] = -(s8)(cosdf(SC_WRAP(SC_RAND(3) + v.z)) * 70.0f);
            pl->stickX = D_800CBB6E_main[GwPlayer[obj->work[0]].pad];
            pl->stickZ = D_800D20A1_main[GwPlayer[obj->work[0]].pad];
            pl->wait = SC_RAND(30) + pl->delay * 6;
        }
        D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
        return;
    }
    func_80106184_storm_chasers(storm->obj->trans.x, storm->obj->trans.z,
                                obj->trans.x, obj->trans.z, &v);
    D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = sindf(SC_WRAP(SC_RAND(3) + v.z)) * 70.0f;
    D_800D20A1_main[GwPlayer[obj->work[0]].pad] = -(s8)(cosdf(SC_WRAP(SC_RAND(3) + v.z)) * 70.0f);
    pl->stickX = D_800CBB6E_main[GwPlayer[obj->work[0]].pad];
    pl->stickZ = D_800D20A1_main[GwPlayer[obj->work[0]].pad];
    pl->wait = SC_RAND(30) + pl->delay * 6;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80109170_storm_chasers);
#endif

/* A whirlwind that reaches a player throws them up and spins them. */
void func_8010A070_storm_chasers(omObjData *obj) {
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];
    MgWork *mw = obj->data;
    ScWind *w;
    Vec v;
    s32 i;

    for (i = 0; i < 2; i++) {
        w = &D_8010CEE0_storm_chasers[i];
        if (w->state >= 2) {
            func_80106184_storm_chasers(obj->trans.x, obj->trans.z, w->obj->trans.x, w->obj->trans.z, &v);
            if (SC_ABS(v.x) < 80.0f) {
                if (pl->hit == 0) {
                    func_800E5690_minigame(obj, 0x21);
                    pl->hit = 1;
                    if (pl->isCpu == 0) {
                        omVibrate(obj->work[0], 2, 2, 20);
                    }
                }
                pl->unk38 = mw->unk3C;
                pl->unk30 = mw->unk3C = v.z;
                mw->unk40 = 15.0f;
                pl->unk34 = 15.0f;
                pl->jump = 2;
                pl->vy = 12.0f;
                pl->g = 4.0f;
                pl->y = obj->trans.y;
            }
        }
    }
    if (pl->jump > 0) {
        func_80105B9C_storm_chasers(obj->work[0]);
        if (pl->y > 0.0f) {
            mw->unk40 = pl->unk34;
        }
        mw->unk3C = pl->unk30;
    }
}

/* CPU after the storm: walk to its goal point, sidestepping other players. */
#ifdef NON_MATCHING
void func_8010A260_storm_chasers(omObjData *obj) {
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];
    MgWork *mw = obj->data;
    ScPlayer *other;
    Vec v;
    s32 i;
    s32 near;

    if (pl->state < 20) {
        pl->state = 20;
    }
    if (D_8010C958_storm_chasers == 0) {
        mw->unk50 |= 0x400;
    }
    switch (pl->state) {
        case 20:
            if (pl->timer > 0) {
                pl->timer--;
                D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = pl->stickX;
                D_800D20A1_main[GwPlayer[obj->work[0]].pad] = pl->stickZ;
                break;
            }
            near = 0;
            for (i = 0; i < 4; i++) {
                if (i != obj->work[0]) {
                    other = &D_8010CD80_storm_chasers[i];
                    if (other->state != -1) {
                        func_80106184_storm_chasers(other->obj->trans.x, other->obj->trans.z, obj->trans.x,
                                                    obj->trans.z, &v);
                        if (SC_ABS(v.x) < 150.0f) {
                            near = 1;
                            break;
                        }
                    }
                }
            }
            if (near) {
                if (SC_RAND(10) != 0) {
                    pl->stickX = D_800CBB6E_main[GwPlayer[obj->work[0]].pad] =
                        sindf(SC_WRAP(v.z + 60.0f)) * 35.0f;
                    pl->stickZ = D_800D20A1_main[GwPlayer[obj->work[0]].pad] =
                        -(s8)(cosdf(SC_WRAP(v.z + 60.0f)) * 35.0f);
                } else {
                    pl->stickX = D_800CBB6E_main[GwPlayer[obj->work[0]].pad] =
                        sindf(SC_WRAP(v.z + 180.0f)) * 35.0f;
                    pl->stickZ = D_800D20A1_main[GwPlayer[obj->work[0]].pad] =
                        -(s8)(cosdf(SC_WRAP(v.z + 180.0f)) * 35.0f);
                }
                pl->timer = 20;
                break;
            }
            func_80106184_storm_chasers(D_8010C928_storm_chasers[pl->pos].x, D_8010C928_storm_chasers[pl->pos].z,
                                        obj->trans.x, obj->trans.z, &v);
            if (SC_ABS(v.x) < 30.0f) {
                pl->state = 21;
                obj->trans.x = D_8010C928_storm_chasers[pl->pos].x;
                obj->trans.z = D_8010C928_storm_chasers[pl->pos].z;
                break;
            }
            D_800CBB6E_main[GwPlayer[obj->work[0]].pad] = sindf(SC_WRAP(SC_RAND(6) + v.z)) * 35.0f;
            D_800D20A1_main[GwPlayer[obj->work[0]].pad] = -(s8)(cosdf(SC_WRAP(SC_RAND(6) + v.z)) * 35.0f);
            break;
        case 21:
            if (mw->unk40 <= 0.0f) {
                pl->done = 1;
                mw->unk3C = D_8010C8D8_storm_chasers[pl->pos].rot;
                pl->state = 22;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010A260_storm_chasers);
#endif

/* Puts the bucket down: the player's flash, and it faces its corner. */
void func_8010AC7C_storm_chasers(omObjData *obj) {
    s32 player = obj->work[0];
    ScPlayer *pl = &D_8010CD80_storm_chasers[player];
    MgWork *mw = obj->data;
    ScBucket *b = &D_8010CCE0_storm_chasers[player];

    if (b->held != 0) {
        HmfModelData[obj->model[0]].unk06 = 0xFF;
        func_8001C258_main(b->obj->model[0], 0x4000, 0);
        b->held = 0;
        func_801066F4_storm_chasers(obj);
    }
    mw->unk3C = D_8010C8D8_storm_chasers[pl->pos].rot;
}

void func_8010AD68_storm_chasers(omObjData *obj) {
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];
    MgWork *mw = obj->data;

    if (mw->unk3C != 0.0f) {
        mw->unk3C = SC_WRAP(mw->unk3C + D_8010C8D8_storm_chasers[pl->pos].turn);
    }
}

/* The result pose: the winner's voice. */
void func_8010AE4C_storm_chasers(omObjData *obj) {
    s32 player = obj->work[0];
    ScPlayer *pl = &D_8010CD80_storm_chasers[player];
    MgWork *mw = obj->data;
    s32 voice = D_800A178C_main[GwPlayer[player].chr][0];

    if (pl->voice == 1) {
        func_800E5690_minigame(obj, 13);
        func_80045ED0_main(voice | 0x2F);
        pl->voice = 2;
    } else if (pl->voice == 0) {
        func_800E5690_minigame(obj, 14);
        pl->voice = 2;
    }
    mw->unk3C = 0;
}


void func_8010AF20_storm_chasers(omObjData *obj) {
    ScPlayer *pl = &D_8010CD80_storm_chasers[obj->work[0]];
    MgWork *mw;

    if (pl->state != -1) {
        mw = obj->data;
        switch (D_8010CCA0_storm_chasers) {
            case 0:
            case 1:
                func_80105B9C_storm_chasers(obj->work[0]);
                if (obj->work[1] == 0) {
                    func_80108FF8_storm_chasers(obj);
                }
                obj->rot.y = 0;
                mw->unk3C = D_8010C8D8_storm_chasers[pl->pos].rot;
                break;
            case 2:
                if (pl->isCpu != 0) {
                    func_80105B9C_storm_chasers(obj->work[0]);
                    func_80109170_storm_chasers(obj);
                }
                func_8010A070_storm_chasers(obj);
                break;
            case 3:
                func_80105B9C_storm_chasers(obj->work[0]);
                func_8010A260_storm_chasers(obj);
                break;
            case 4:
            case 5:
                func_80105B9C_storm_chasers(obj->work[0]);
                func_8010AC7C_storm_chasers(obj);
                break;
            case 6:
                func_80105B9C_storm_chasers(obj->work[0]);
                func_8010AD68_storm_chasers(obj);
                break;
            case 7:
                func_80105B9C_storm_chasers(obj->work[0]);
                func_8010AE4C_storm_chasers(obj);
                break;
            case 8:
                func_80105B9C_storm_chasers(obj->work[0]);
                break;
        }
        if (pl->hit == 1 && HmfModelData[obj->model[0]].unk40 >= 10.0f) {
            func_8001C814_main(obj->model[0], 1, 1);
            pl->hit = 2;
        }
        if (pl->jump > 0) {
            if (pl->y <= 0.0f && pl->jump == 1) {
                obj->trans.y = 0.0f;
                pl->unk34 = 0.0f;
                mw->unk40 = 0.0f;
                func_8001C814_main(obj->model[0], 1, 0);
                if (mw->unk5C & 2) {
                    pl->jump = 0;
                    pl->hit = 0;
                }
            } else {
                mw->unk40 = pl->unk34;
                pl->y += pl->vy;
                pl->vy -= pl->g;
                obj->trans.y = pl->y;
                pl->jump = 1;
            }
        }
        func_800DDD94_minigame(obj);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 2.0f, obj->trans.z);
    }
}

/* A player (minigame framework): models, motions, start corner, CPU tuning by difficulty. */
void func_8010B1B0_storm_chasers(omObjData *obj) {
    s32 arg4 = 0x2B9;
    s32 arg5 = 0xC9;
    u16 chr = GwPlayer[obj->work[0]].chr;
    s32 dir = D_800A178C_main[chr][0];
    s32 file = D_800A178C_main[chr][2];
    MgWork *mw;
    ScPlayer *pl;

    func_800E18D8_minigame();
    func_800E1BA8_minigame(obj, dir, file, obj->work[0], arg4, arg5);
    mw = obj->data;
    mw->unkEC = NULL;
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C258_main(obj->model[1], 0x60, 0x20);
    func_8001C258_main(obj->model[1], 0x180, 0x80);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    obj->model[3] = func_8000B108_main(3, 0x2BD);
    obj->model[4] = func_8000B108_main(4, 0x2BD);
    obj->model[8] = func_8000B108_main(8, 0x2BD);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 0x11, func_80017BB8_main(chr, 0xE), 0, 0);
    func_800E5A00_minigame(obj, 3, func_80017BB8_main(chr, 0x1D), 1, 0);
    func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(obj, 0x20, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5A00_minigame(obj, 0x16, func_80017BB8_main(chr, 0x96), 1, 0);
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, 0x37), 1, 0x78);
    func_800E5A00_minigame(obj, 0x21, func_80017BB8_main(chr, 0x97), 2, 0);
    if (obj->work[0] == 0) {
        D_8010CF18_storm_chasers = rand8() & 3;
    } else if (++D_8010CF18_storm_chasers >= 4) {
        D_8010CF18_storm_chasers = 0;
    }
    obj->trans.x = D_8010C8D8_storm_chasers[D_8010CF18_storm_chasers].x;
    obj->trans.y = 0;
    obj->trans.z = D_8010C8D8_storm_chasers[D_8010CF18_storm_chasers].z;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 2.0f, obj->trans.z);
    obj->rot.y = D_8010C8D8_storm_chasers[D_8010CF18_storm_chasers].rot;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    func_800E5690_minigame(obj, 0);
    D_800EBE24_minigame = 1;
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    func_8001C8A8_main(obj->model[3], 1);
    func_8001C8A8_main(obj->model[4], 1);
    func_8001C8A8_main(obj->model[8], 1);
    func_800E149C_minigame(obj, 0, 2);
    func_80105B9C_storm_chasers(obj->work[0]);
    mw->unk40 = 0;
    obj->func = func_8010AF20_storm_chasers;
    pl = &D_8010CD80_storm_chasers[obj->work[0]];
    pl->state = 0;
    pl->isCpu = GwPlayer[obj->work[0]].stat & 1;
    pl->score = 0;
    pl->done = 0;
    pl->pos = -1;
    pl->unk10 = 0;
    pl->voice = 0;
    pl->pos = D_8010CF18_storm_chasers;
    pl->rank = 0;
    pl->jump = 0;
    pl->hit = 0;
    pl->obj = obj;
    pl->timer = 0;
    switch (GwPlayer[obj->work[0]].cpu_difficulty) {
        case 0:
            pl->radius = 300.0f;
            pl->delay = 5;
            pl->wait = 0;
            break;
        case 1:
            pl->radius = 200.0f;
            pl->delay = 4;
            pl->wait = 0;
            break;
        case 2:
            pl->radius = 100.0f;
            pl->delay = 3;
            pl->wait = 0;
            break;
        case 3:
            pl->radius = 70.0f;
            pl->delay = 2;
            pl->wait = 0;
            break;
    }
    pl->stickZ = 0;
    pl->stickX = 0;
}

void func_8010B738_storm_chasers(void) {
    s32 unused[2]; /* retail's frame carries 8 bytes no instruction uses */
    omObjData *obj;
    u32 player;
    s16 i;

    for (i = 0; i < 4; i++) {
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
        obj = omAddObj(200, 9, 60, -1, func_8010B1B0_storm_chasers);
        obj->work[0] = player;
        D_800EC598_minigame[D_800EC280_minigame] = obj;
        D_800EC280_minigame++;
    }
}

void func_8010B838_storm_chasers(omObjData *obj) {
}

void func_8010B840_storm_chasers(omObjData *obj) {
    if (D_8010CCAC_storm_chasers > 0) {
        D_8010CCAC_storm_chasers--;
        return;
    }
    D_8010CCA4_storm_chasers = 1;
    obj->func = func_8010B838_storm_chasers;
}

/* The result jingle: a winner's or the draw's. */
void func_8010B87C_storm_chasers(omObjData *obj) {
    ScPlayer *pl;
    s32 i;

    if (D_8010CCAC_storm_chasers > 0) {
        D_8010CCAC_storm_chasers--;
        return;
    }
    i = 0;
    pl = D_8010CD80_storm_chasers;
    for (; i < 4; i++) {
        if (pl[i].state != -1 && pl[i].rank == 0) {
            break;
        }
    }
    if (i < 4) {
        HuAudSeqPlay(0x65);
        D_8010CCAC_storm_chasers = 0x62;
    } else {
        HuAudSeqPlay(0x6C);
        D_8010CCAC_storm_chasers = 0x90;
    }
    obj->func = func_8010B840_storm_chasers;
}

void func_8010B944_storm_chasers(omObjData *obj) {
    if (D_8010CCAC_storm_chasers > 0) {
        D_8010CCAC_storm_chasers--;
        return;
    }
    D_8010CCA4_storm_chasers = 1;
    obj->func = func_8010B87C_storm_chasers;
}

void func_8010B980_storm_chasers(omObjData *obj) {
    ScBucket *b;
    s32 i;

    i = 0;
    b = D_8010CCE0_storm_chasers;
    for (; i < 4; i++) {
        if (b[i].state != -1 && b[i].done != 2) {
            break;
        }
    }
    if (i >= 4) {
        D_8010CCA4_storm_chasers = 1;
        D_8010CCAC_storm_chasers = 10;
        obj->func = func_8010B944_storm_chasers;
    }
}

/* Ranks the players by score (ties broken at random) into their bonus and rank. */
void func_8010BA00_storm_chasers(void) {
    s32 rank[4][3]; /* player, score, rank */
    ScPlayer *pl;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            rank[i][j] = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        pl = &D_8010CD80_storm_chasers[i];
        if (pl->state == -1) {
            continue;
        }
        if (i == 0) {
            rank[0][0] = 0;
            rank[0][1] = pl->score;
            rank[0][2] = 0;
            continue;
        }
        for (j = i - 1; j >= 0; j--) {
            if (pl->score > rank[j][1]) {
                /* beats rank j: push it down one place */
                rank[j + 1][0] = rank[j][0];
                rank[j + 1][1] = rank[j][1];
                rank[j + 1][2] = rank[j][2] + 1;
                rank[j][0] = i;
                rank[j][1] = pl->score;
            } else if (pl->score < rank[j][1]) {
                rank[j + 1][0] = i;
                rank[j + 1][1] = pl->score;
                rank[j + 1][2] = rank[j][2] + 1;
                break;
            } else if (rank[j][1] == 0) {
                /* tied at zero: same place */
                rank[j + 1][0] = i;
                rank[j + 1][1] = pl->score;
                rank[j + 1][2] = rank[j][2];
                break;
            } else if (rand8() & 1) {
                /* tied: a coin flip decides the order */
                rank[j + 1][0] = rank[j][0];
                rank[j + 1][1] = rank[j][1];
                rank[j + 1][2] = rank[j][2] + 1;
                rank[j][0] = i;
                rank[j][1] = pl->score;
            } else {
                rank[j + 1][0] = i;
                rank[j + 1][1] = pl->score;
                rank[j + 1][2] = rank[j][2] + 1;
                break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[rank[i][0]].bonusCoin = rank[i][2];
        pl = &D_8010CD80_storm_chasers[rank[i][0]];
        pl->rank = rank[i][2];
        if (rank[i][2] == 0) {
            pl->voice = 1;
        }
    }
}

// decomp-permuter
void func_8010BD04_storm_chasers(void)
{
  s32 i;
  int new_var;
  s32 zero;
  ScPlayer *pl;
  i = 0;
  new_var = 1;
  zero = 0;
  pl = D_8010CD80_storm_chasers;
  for (; i < 4; i++)
  {
 do { if (pl[i].state != (-new_var)) { zero += pl[i].score == 0; } } while (0);
  }

  if (zero >= 4)
  {
    i = 0;
    pl = D_8010CD80_storm_chasers;
    for (; i < 4; i++)
    {
      if (pl[i].state != (-1))
      {
        GwPlayer[i].bonusCoin = 3;
        pl[i].rank = 3;
        D_8010CAAC_storm_chasers = 0;
      }
    }

    return;
  }
  func_8010BA00_storm_chasers();
  D_8010CAAC_storm_chasers = 1;
}

void func_8010BDF4_storm_chasers(omObjData *obj) {
    ScBucket *b;
    s32 i;

    i = 0;
    b = D_8010CCE0_storm_chasers;
    for (; i < 4; i++) {
        if (b[i].state != -1 && b[i].done != 1) {
            break;
        }
    }
    if (i >= 4) {
        func_8010BD04_storm_chasers();
        D_8010CCA4_storm_chasers = 1;
        obj->func = func_8010B980_storm_chasers;
    }
}

void func_8010BE8C_storm_chasers(omObjData *obj) {
    ScPlayer *pl;
    s32 i;

    if (D_8010CCAC_storm_chasers > 0) {
        D_8010CCAC_storm_chasers--;
    } else {
        i = 0;
        pl = D_8010CD80_storm_chasers;
        for (; i < 4; i++) {
            if (pl[i].state != -1 && pl[i].done != 1) {
                break;
            }
        }
        if (i >= 4) {
            D_8010CCA4_storm_chasers = 1;
            obj->func = func_8010BDF4_storm_chasers;
        }
    }
    if (D_8010C958_storm_chasers > 0) {
        D_8010C958_storm_chasers--;
    }
}

void func_8010BF3C_storm_chasers(omObjData *obj) {
    GMesCreate(0x12);
    HuAudSeqFadeOut(120);
    D_8010CCAC_storm_chasers = 75;
    obj->func = func_8010BE8C_storm_chasers;
}

/* The round's countdown. */
void func_8010BF84_storm_chasers(omObjData *obj) {
    if (D_8010CCAC_storm_chasers != 0) {
        func_8003F578_main((D_8010CCAC_storm_chasers-- + 28) / 30);
        return;
    }
    func_8003F5C0_main();
    obj->func = func_8010BF3C_storm_chasers;
    D_8010CCA4_storm_chasers = 1;
}

void func_8010C014_storm_chasers(omObjData *obj) {
    GMesCreate(0x1A, 30, 160, 28);
    D_8010CCAC_storm_chasers = 901;
    obj->func = func_8010BF84_storm_chasers;
}

void func_8010C060_storm_chasers(omObjData *obj) {
    if (++D_8010CAB0_storm_chasers == 63) {
        HuAudSeqPlay(0x38);
    }
    if (GMesStatGet() == 0 || GMesStatGet() & 2) {
        obj->func = func_8010C014_storm_chasers;
        D_8010CCA4_storm_chasers = 1;
    }
}

void func_8010C0E0_storm_chasers(omObjData *obj) {
    GMesCreate(7);
    obj->func = func_8010C060_storm_chasers;
    D_8010CCA4_storm_chasers = 1;
}

void func_8010C120_storm_chasers(omObjData *obj) {
    Vec from;
    Vec to;
    Vec out;
    u32 i;

    if (D_8010CCA8_storm_chasers == 0) {
        D_8010CCA8_storm_chasers = 1;
        to.x = 1280.0f;
        to.y = 0;
        to.z = 1900.0f;
        from.x = 70.0f;
        from.y = 0;
        from.z = 20.0f;
        func_80105D64_storm_chasers(&from, &to, &out);
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

void func_8010C240_storm_chasers(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010C264_storm_chasers(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010C240_storm_chasers;
    }
}

void func_8010C29C_storm_chasers(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010C264_storm_chasers;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8010C2F4_storm_chasers(void) {
    D_8010CCA0_storm_chasers += D_8010CCA4_storm_chasers;
    D_8010CCA4_storm_chasers = 0;
}

void func_8010C31C_storm_chasers(omObjData *obj) {
    func_8010C2F4_storm_chasers();
    switch (D_8010CCA0_storm_chasers) {
        case 1:
            if (D_8010CAB4_storm_chasers == -1) {
                D_8010CAB4_storm_chasers = HuAudFXPlay(0x486);
            }
            break;
        case 8:
            WipeCreateOut(0, 20);
            obj->func = func_8010C264_storm_chasers;
            break;
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
    }
}

void func_8010C3A8_storm_chasers(void) {
    ScPlayer *pl;
    s32 i;

    i = 0;
    pl = D_8010CD80_storm_chasers;
    for (; i < 4; i++) {
        pl[i].state = -1;
    }
}

void func_8010C3EC_storm_chasers(void) {
    ScBucket *p;
    s32 i;

    i = 0;
    p = D_8010CCE0_storm_chasers;
    for (; i < 4; i++) {
        p[i].state = -1;
    }
}

void func_8010C428_storm_chasers(void) {
    D_8010CCC0_storm_chasers.state = -1;
}

void func_8010C438_storm_chasers(void) {
    D_8010CF20_storm_chasers.state = -1;
}

void func_8010C448_storm_chasers(void) {
    ScFlash *p;
    s32 i;

    i = 0;
    p = D_8010CF38_storm_chasers;
    for (; i < 4; i++) {
        p[i].state = -1;
    }
}

void func_8010C484_storm_chasers(void) {
    ScWind *p;
    s32 i;

    i = 0;
    p = D_8010CEE0_storm_chasers;
    for (; i < 2; i++) {
        p[i].state = -1;
    }
}

void func_8010C4C0_storm_chasers(void) {
    D_8010CCA0_storm_chasers = 0;
    D_8010CCA4_storm_chasers = 0;
    D_8010CCA8_storm_chasers = 0;
    D_8010CF18_storm_chasers = 0;
    func_8010C428_storm_chasers();
    func_8010C438_storm_chasers();
    func_8010C3A8_storm_chasers();
    func_8010C448_storm_chasers();
    func_8010C3EC_storm_chasers();
    func_8010C484_storm_chasers();
}

void func_8010C520_storm_chasers(void) {
    func_8010C4C0_storm_chasers();
    func_8010637C_storm_chasers();
    func_801066BC_storm_chasers();
    func_801075C4_storm_chasers();
    func_801078A0_storm_chasers();
    func_8010B738_storm_chasers();
    func_801069EC_storm_chasers();
    func_80108F88_storm_chasers();
    func_8010834C_storm_chasers();
}

void func_8010C57C_storm_chasers(omObjData *obj) {
    func_800E6F0C_minigame(2);
    func_8010C520_storm_chasers();
    WipeCreateIn(0xFF, 16);
    obj->func = func_8010C31C_storm_chasers;
    omAddObj(100, 0, 0, -1, func_8010C120_storm_chasers);
    omAddObj(900, 0, 0, -1, func_8010C0E0_storm_chasers);
}

void func_8010C604_storm_chasers(void) {
}

void func_8010C60C_storm_chasers(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_8010CAB8_storm_chasers[i].scissor[0], D_8010CAB8_storm_chasers[i].scissor[1],
                   D_8010CAB8_storm_chasers[i].scissor[2], D_8010CAB8_storm_chasers[i].scissor[3]);
        ViewportSet(i, D_8010CAB8_storm_chasers[i].viewport[0], D_8010CAB8_storm_chasers[i].viewport[1],
                    D_8010CAB8_storm_chasers[i].viewport[2], D_8010CAB8_storm_chasers[i].viewport[3],
                    D_8010CAB8_storm_chasers[i].viewport[4], D_8010CAB8_storm_chasers[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010CAB8_storm_chasers[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010C780_storm_chasers(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(60, 0);
    func_8004A208_main();
    func_8010C60C_storm_chasers();
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, -215.0f, 295.0f, 470.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -215.0f, 295.0f, 470.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010CC8C_storm_chasers, 0);
    func_80045010_main(D_8010CC8C_storm_chasers, 1);
    omAddObj(1000, 0, 0, -1, func_8010C57C_storm_chasers);
    omAddObj(1000, 0, 0, -1, func_8010C29C_storm_chasers);
    func_800E5EA0_minigame(&D_8010C8B0_storm_chasers);
}

const s16 D_8010CC8C_storm_chasers[] = { 0x8260, 0x8261, 0x8262, 0x0000 };
