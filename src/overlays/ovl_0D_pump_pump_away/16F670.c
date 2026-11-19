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

/* The full-screen picture (D_80113530_pump_pump_away). */
typedef struct PpScreen {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 grp;
    /* 0x08 */ s32 draw;
    /* 0x0C */ HuSprite_Unk84_Struct *spr;
    /* 0x10 */ s32 alpha;
    /* 0x14 */ s32 timer;
} PpScreen;

/* A 2D overlay with up to eight values (D_80111758_pump_pump_away, D_8011178C_pump_pump_away). */
typedef struct PpHud {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 grp;
    /* 0x08 */ s32 draw;
    /* 0x0C */ HuSprite_Unk84_Struct *spr;
    /* 0x10 */ s32 val[8];
    /* 0x30 */ s32 alpha;
} PpHud; // Size 0x34

typedef struct PpPos16 {
    /* 0x00 */ u16 x;
    /* 0x02 */ u16 y;
} PpPos16;

/* A water splash slot (D_801117E0_pump_pump_away, 20 x 0x10). */
typedef struct PpSplash {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 alpha;
    /* 0x08 */ f32 vel;
    /* 0x0C */ omObjData *obj;
} PpSplash;

/* The water arc between a team's pump and its balloon (D_80113518_pump_pump_away). */
typedef struct PpArc {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 team;
    /* 0x08 */ f32 angle;
    /* 0x0C */ omObjData *obj;
} PpArc;

#define PP_WRAP(a) ((a) >= 360.0f ? (a) - 360.0f : (a) < 0.0f ? (a) + 360.0f : (a))

/* A player's pump state (D_80113570_pump_pump_away, 4 x 0x10). */
typedef struct PpPump {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 flag;
    /* 0x0C */ s32 player;
} PpPump;

/* A player (D_80113438_pump_pump_away, 4 x 0x38). */
typedef struct PpPlayer {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ omObjData *obj;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
} PpPlayer; // Size 0x38

/* A team's pump tank (D_801117C0_pump_pump_away, 2 x 0x10). */
typedef struct PpTank {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 level;
    /* 0x0C */ s32 count;
} PpTank;

/* A fading effect model's state (D_80113400_pump_pump_away, 3 x 8). */
typedef struct PpFx {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 alpha;
} PpFx;

typedef s32 (*PpDrawHookAdd)(s32, void (*)(Gfx **, s32, s32), u8);

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
extern s32 D_801116F4_pump_pump_away;
extern PpTeam D_80111978_pump_pump_away[2];
extern CcEnt D_80111A30_pump_pump_away[50];
extern PpScreen D_80113530_pump_pump_away;
extern PpArc D_80113518_pump_pump_away;
/* Fields of D_80113518_pump_pump_away under their own labels (retail addresses each directly). */
extern s32 D_8011351C_pump_pump_away; /* .team */
extern f32 D_80113520_pump_pump_away; /* .angle */
extern omObjData *D_80113524_pump_pump_away; /* .obj */
extern s16 D_80111108_pump_pump_away;
extern s16 D_8011110A_pump_pump_away;
extern PpFx D_80113400_pump_pump_away[3];
extern Vec D_80111004_pump_pump_away[];
/* Fields of D_80113530_pump_pump_away under their own labels (retail addresses each directly). */
extern s32 D_80113534_pump_pump_away; /* .grp */
extern s32 D_80113538_pump_pump_away; /* .draw */
extern HuSprite_Unk84_Struct *D_8011353C_pump_pump_away; /* .spr */
extern s32 D_80113540_pump_pump_away; /* .alpha */
extern s32 D_80113544_pump_pump_away; /* .timer */
extern PpSplash D_801117E0_pump_pump_away[20];
extern PpTank D_801117C0_pump_pump_away[2];
extern PpHud D_80111758_pump_pump_away[2];
/* Fields of D_80111758_pump_pump_away[0] and [1] under their own labels (retail addresses each directly). */
extern s32 D_8011175C_pump_pump_away; /* [0].grp */
extern s32 D_80111760_pump_pump_away; /* [0].draw */
extern HuSprite_Unk84_Struct *D_80111764_pump_pump_away; /* [0].spr */
extern s32 D_80111790_pump_pump_away; /* [1].grp */
extern s32 D_80111794_pump_pump_away; /* [1].draw */
extern HuSprite_Unk84_Struct *D_80111798_pump_pump_away; /* [1].spr */
extern s32 D_80111788_pump_pump_away; /* D_80111758_pump_pump_away.alpha */
extern s32 D_801117BC_pump_pump_away; /* D_8011178C_pump_pump_away.alpha */
extern Vec D_80110FC4_pump_pump_away[];
extern PpPos16 D_80110FDC_pump_pump_away[];
extern PpPos16 D_80110FE4_pump_pump_away[];
extern Vec D_80110F6C_pump_pump_away[];
extern f32 D_80110F9C_pump_pump_away[];
extern s32 D_80113528_pump_pump_away;
extern s32 D_8011352C_pump_pump_away;
extern PpPlayer D_80113438_pump_pump_away[4];
extern PpPump D_80113570_pump_pump_away[4];
extern PpTexSize D_80113548_pump_pump_away[];
extern s32 D_801135E4_pump_pump_away;

void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_80088800_main(f32 *mtx, f32 x, f32 y, f32 z);
void func_80034048_main(s16, s16);
void func_80032FC0_main(s16, u8, u8);
s16 func_80032694_main(HmfData *, u16, s32, char *);
void func_800335BC_main(char *arg0, void *arg1);
void func_8010749C_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2);
void func_8010775C_pump_pump_away(omObjData *obj);
void func_801078B4_pump_pump_away(void);
void func_80108560_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2);
void func_80108810_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2);
void func_80108B0C_pump_pump_away(omObjData *obj);
void func_8004AE00_main(s16 handle, s16 pan);

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
    PpTeam *t;
    PpTeam *t1;
    f32 scale;
    s32 i;

    switch (D_801116F4_pump_pump_away) {
        case 4:
            t = D_80111978_pump_pump_away;
            t1 = &t[1];
            if (t->dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y -= t->speed;
            } else {
                obj->trans.y -= t1->speed;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (D_80113530_pump_pump_away.state >= 2) {
        case 7:
                obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            break;
    }
    for (i = 0; i < 2; i++) {
        scale = D_80111978_pump_pump_away[i].obj->trans.y - obj->trans.y - 200.0f;
        if ((scale > 1000.0f) | (scale < -100.0f)) {
            func_8001C258_main(obj->model[i + 1], 4, 4);
        } else {
            func_8001C258_main(obj->model[i + 1], 4, 0);
            scale = 3.0 - scale * 0.003;
            if (scale >= 3.0) {
                scale = 3.0f;
            }
        }
        Hu3DModelPosSet(obj->model[i + 1], D_80110EA0_pump_pump_away[i].x, obj->trans.y + 1.0, D_80110EA0_pump_pump_away[i].z + 0.0f);
        Hu3DModelScaleSet(obj->model[i + 1], scale, scale, scale);
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

void func_80106724_pump_pump_away(omObjData *obj) {
    PpTeam *t;
    PpTeam *t1;

    switch (D_801116F4_pump_pump_away) {
        case 4:
            t = D_80111978_pump_pump_away;
            t1 = &t[1];
            if (t->dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y = obj->trans.y - t->speed * 0.9;
            } else {
                obj->trans.y = obj->trans.y - t1->speed * 0.9;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (D_80113530_pump_pump_away.state >= 2) {
        case 7:
                obj->trans.x = obj->trans.y = 0.0f;
                obj->trans.z = -1100.0f;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            break;
    }
}

void func_8010682C_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E0003, 0x289);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1100.0f;
    obj->func = func_80106724_pump_pump_away;
}

void func_80106894_pump_pump_away(void) {
    omAddObj(250, 1, 0, -1, func_8010682C_pump_pump_away);
}

void func_801068C8_pump_pump_away(omObjData *obj) {
    PpTeam *t;
    PpTeam *t1;

    switch (D_801116F4_pump_pump_away) {
        case 4:
            t = D_80111978_pump_pump_away;
            t1 = &t[1];
            if (t->dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y = obj->trans.y - t->speed * 0.8;
            } else {
                obj->trans.y = obj->trans.y - t1->speed * 0.8;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (D_80113530_pump_pump_away.state >= 2) {
        case 7:
                obj->trans.x = obj->trans.y = 0.0f;
                obj->trans.z = -1290.0f;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            break;
    }
}

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
            if (D_80113530_pump_pump_away.state >= 2) {
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

void func_80107338_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E0001, 0x289);
    obj->model[1] = func_8000B108_main(0x2E0002, 0x289);
    func_8001C2FC_main(obj->model[0], 0x20000, 0x20000);
    func_8001C448_main(obj->model[0]);
    func_8001C954_main(obj->model[0]);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C258_main(obj->model[1], 4, 0);
    func_800335BC_main("m213_back_DEF", D_80113548_pump_pump_away);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1300.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, -1300.0f);
    D_801116E0_pump_pump_away = 0.0f;
    D_801116E4_pump_pump_away = 0.0f;
    D_801135E4_pump_pump_away = 0;
    obj->func = func_80106A6C_pump_pump_away;
}

void func_8010745C_pump_pump_away(void) {
    omSetStatBit(omAddObj(100, 2, 0, -1, func_80107338_pump_pump_away), 0xA0);
}

#ifdef NON_MATCHING
void func_8010749C_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2) {
    PpScreen *s = &D_80113530_pump_pump_away;
    Gfx *g;
    s32 i;
    s32 j;

    if (s->state != -1) {
        if (D_80113540_pump_pump_away < 0xFF) {
            gfx = func_80105B6C_pump_pump_away(func_80105AA0_pump_pump_away(gfx), (u8)D_80113540_pump_pump_away);
        } else {
            gfx = func_801059BC_pump_pump_away(gfx);
        }
        g = *gfx;
        gDPSetTextureLUT(g++, G_TT_RGBA16);
        gDPLoadTLUT_pal16(g++, 0, s->spr->unk0C);
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                gDPLoadTextureTile_4b(g++, s->spr->unk08, G_IM_FMT_CI, 64, 48, 0, 0, 64, 48, 0,
                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                      G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 64 << 2, 48 << 2);
                gSPTextureRectangle(g++, (i * 64) << 2, (j * 48) << 2, ((i + 1) * 64) << 2, ((j + 1) * 48) << 2,
                                    G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            }
        }
        *gfx = g;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010749C_pump_pump_away);
#endif

void func_8010775C_pump_pump_away(omObjData *obj) {
    PpScreen *s = &D_80113530_pump_pump_away;

    if (s->state == -1) {
        return;
    }
    switch (s->state) {
        case 0:
            s->alpha = 0;
            break;
        case 1:
            s->alpha += 26;
            if (s->alpha >= 256) {
                s->alpha = 255;
                s->state = 2;
            }
            break;
        case 2:
            if (s->timer != 0) {
                s->timer--;
            } else {
                s->state = 3;
            }
            break;
        case 3:
            s->alpha -= 25;
            if (s->alpha < 30) {
                s->alpha = 0;
                s->state = 4;
            }
            break;
        case 4:
            s->alpha = 0;
            s->state = -1;
            break;
    }
}

void func_8010780C_pump_pump_away(omObjData *obj) {
    PpDrawHookAdd hookAdd = (PpDrawHookAdd)(void (*)(void))func_8001AC8C_main;

    D_80113534_pump_pump_away = func_8000B838_main(0x2E001E);
    D_8011353C_pump_pump_away = func_80055194_main((s16)D_80113534_pump_pump_away);
    D_80113538_pump_pump_away = hookAdd(0, func_8010749C_pump_pump_away, 6);
    func_8001C8A8_main((s16)D_80113538_pump_pump_away, 1);
    D_80113540_pump_pump_away = 0;
    D_80113530_pump_pump_away.state = -1;
    D_80113544_pump_pump_away = 30;
    obj->func = func_8010775C_pump_pump_away;
}

void func_801078B4_pump_pump_away(void) {
    omAddObj(950, 1, 0, -1, func_8010780C_pump_pump_away)->work[0] = 0;
}

void func_801078EC_pump_pump_away(omObjData *obj) {
    PpSplash *p;
    s32 i;

    for (i = 0; i < 20; i++) {
        p = &D_801117E0_pump_pump_away[i];
        if (p->state == 0) {
            p->state = 1;
            p->obj->trans.x = obj->trans.x;
            p->obj->trans.y = obj->trans.y + 50.0f;
            p->obj->trans.z = obj->trans.z + 50.0f;
            p->vel = 0;
            return;
        }
    }
}

void func_80107964_pump_pump_away(omObjData *obj) {
    PpPump *pump = &D_80113570_pump_pump_away[obj->work[0]];
    PpPlayer *pl = &D_80113438_pump_pump_away[pump->player];

    func_8001C6A8_main(obj->model[0], HmfModelData[pl->obj->model[0]].unk40);
    if (pl->unk18 != 0 && HmfModelData[obj->model[0]].unk40 <= 6.0f) {
        if (pump->timer != 0) {
            pump->timer--;
            return;
        }
        pump->flag ^= 1;
        pump->timer = 1;
        func_80034048_main((s16)obj->work[1], (s16)pump->flag);
    } else {
        pump->timer = 0;
        func_80034048_main((s16)obj->work[1], 0);
    }
}

void func_80107A8C_pump_pump_away(omObjData *obj) {
    PpPump *pump = &D_80113570_pump_pump_away[obj->work[0]];

    if (pump->state == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 2:
            func_80107964_pump_pump_away(obj);
            break;
        case 3:
            if (pump->state == 0) {
                func_801078EC_pump_pump_away(obj);
                pump->state = 1;
            }
            func_8001C258_main(obj->model[0], 4, 4);
            break;
        case 0:
        case 1:
        case 4:
            break;
    }
}

void func_80107B40_pump_pump_away(omObjData *obj) {
    void *data;
    PpPump *pump;
    s32 i;

    obj->model[0] = func_8000B108_main(0x2E0005, 0x2A9);
    func_8000B460_main(obj, 0, 0x2E0006);
    /* retail: players 0 and 1 fall through into the second team's animation set-up */
    switch (obj->work[0]) {
        case 0:
        case 1:
            if (obj->work[0] == 0) {
                data = DataRead(0x2E0007);
                obj->work[1] = D_8011352C_pump_pump_away = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "m213_p1_DEF");
                HuMemMemoryFreePerm(data);
            } else {
                obj->work[1] = func_80032694_main(HmfModelData[obj->model[0]].hmf, (u16)D_8011352C_pump_pump_away, 0, "m213_p1_DEF");
            }
        case 2:
        case 3:
            if (obj->work[0] == 2) {
                data = DataRead(0x2E0008);
                obj->work[1] = D_80113528_pump_pump_away = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "m213_p1_DEF");
                HuMemMemoryFreePerm(data);
            } else {
                obj->work[1] = func_80032694_main(HmfModelData[obj->model[0]].hmf, (u16)D_80113528_pump_pump_away, 0, "m213_p1_DEF");
            }
            break;
    }
    func_80034048_main((s16)obj->work[1], 0);
    func_80032FC0_main((s16)obj->work[1], 1, 1);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 1, 1);
    obj->trans.x = D_80110F6C_pump_pump_away[obj->work[0]].x;
    obj->trans.y = D_80110F6C_pump_pump_away[obj->work[0]].y;
    obj->trans.z = D_80110F6C_pump_pump_away[obj->work[0]].z;
    obj->func = func_80107A8C_pump_pump_away;
    pump = &D_80113570_pump_pump_away[obj->work[0]];
    pump->state = 0;
    pump->timer = 0;
    pump->flag = 0;
    for (i = 0; i < 4; i++) {
        if ((D_80113438_pump_pump_away + i)->obj->work[3] == obj->work[0]) {
            break;
        }
    }
    pump->player = i;
}

void func_80107E5C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(500, 1, 1, -1, func_80107B40_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_80107EB8_pump_pump_away(omObjData *obj) {
    PpPlayer *pl[2];
    PpTank *tank = &D_801117C0_pump_pump_away[obj->work[0]];
    PpTeam *team;
    s32 level;
    s32 i;
    s32 n;

    for (i = 0, n = 0; (i < 4) & (n < 2); i++) {
        pl[n] = &D_80113438_pump_pump_away[i];
        n += GwPlayer[pl[n]->obj->work[0]].group == obj->work[0];
    }
    switch (tank->state) {
        case 0:
            if (tank->count < pl[0]->unk10 + pl[1]->unk10) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                level = (pl[0]->unk10 + pl[1]->unk10 - tank->count) / 3;
                tank->count = pl[0]->unk10 + pl[1]->unk10;
                if (level >= 10) {
                    level = 9;
                }
                tank->level = level;
                func_8001C92C_main(obj->model[0], D_80110F9C_pump_pump_away[level]);
                func_8001C814_main(obj->model[0], 1, 0);
                tank->state = 1;
            } else {
                func_8001C6A8_main(obj->model[0], 0.0f);
            }
            break;
        case 1:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                tank->state = 0;
                team = &D_80111978_pump_pump_away[obj->work[0]];
                team->unk0C = 1;
                team->unk10 = tank->level;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107EB8_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_8010811C_pump_pump_away(omObjData *obj) {
    PpTank *tank = &D_801117C0_pump_pump_away[obj->work[0]];

    switch (tank->state) {
        case 2:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C258_main(obj->model[0], 4, 4);
                tank->state = 3;
            }
            break;
        case 3:
            break;
        default:
            if (HmfModelData[obj->model[0]].unk40 == 0.0f ||
                D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C5B4_main(obj->model[0], obj->motion[1]);
                func_8001C814_main(obj->model[0], 2, 0);
                tank->state = 2;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010811C_pump_pump_away);
#endif

void func_801082AC_pump_pump_away(omObjData *obj) {
    if (D_801117C0_pump_pump_away[obj->work[0]].unk00 == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C814_main(obj->model[0], 1, 1);
            break;
        case 2:
            func_80107EB8_pump_pump_away(obj);
            break;
        case 3:
            func_8010811C_pump_pump_away(obj);
            break;
        case 4:
            break;
    }
}

void func_80108358_pump_pump_away(omObjData *obj) {
    void *data;
    PpTank *tank;

    obj->model[0] = func_8000B108_main(0x2E0009, 0x289);
    func_8000B460_main(obj, 0, 0x2E000A);
    func_8000B460_main(obj, 1, 0x2E000B);
    if (obj->work[0] != 0) {
        data = DataRead(0x2E000C);
        obj->work[1] = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "m213_hose_r_DEF");
        func_80032FC0_main((s16)obj->work[1], 1, 1);
        HuMemMemoryFreePerm(data);
        func_8001C448_main(obj->model[0]);
        func_8001C514_main(obj->model[0]);
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    obj->trans.x = D_80110FC4_pump_pump_away[obj->work[0]].x;
    obj->trans.y = D_80110FC4_pump_pump_away[obj->work[0]].y;
    obj->trans.z = D_80110FC4_pump_pump_away[obj->work[0]].z;
    obj->func = func_801082AC_pump_pump_away;
    tank = &D_801117C0_pump_pump_away[obj->work[0]];
    tank->unk00 = 0;
    tank->state = 0;
    tank->level = 0;
    tank->count = 0;
}

void func_80108504_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(600, 1, 2, -1, func_80108358_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_80108560_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2) {
    PpHud *h = &D_80111758_pump_pump_away[0];
    Gfx *g;
    s32 i;

    if (h->state != -1) {
        if (D_80111788_pump_pump_away < 0xFF) {
            gfx = func_80105B6C_pump_pump_away(func_80105AA0_pump_pump_away(gfx), (u8)D_80111788_pump_pump_away);
        } else {
            gfx = func_801059BC_pump_pump_away(gfx);
        }
        g = *gfx;
        gDPSetTextureLUT(g++, G_TT_RGBA16);
        gDPLoadTLUT_pal16(g++, 0, h->spr->unk0C);
        for (i = 0; i < 2; i++) {
            gDPLoadTextureTile_4b(g++, h->spr->unk08, G_IM_FMT_CI, 64, 16, 0, 0, 64, 16, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 64 << 2, 16 << 2);
            gSPTextureRectangle(g++, D_80110FDC_pump_pump_away[i].x << 2, D_80110FDC_pump_pump_away[i].y << 2, (D_80110FDC_pump_pump_away[i].x + 64) << 2,
                                (D_80110FDC_pump_pump_away[i].y + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
        *gfx = g;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108560_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_80108810_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2) {
    PpHud *h = &D_80111758_pump_pump_away[1];
    Gfx *g;
    s32 i;

    if (h->state != -1) {
        if (D_801117BC_pump_pump_away < 0xFF) {
            gfx = func_80105B6C_pump_pump_away(func_80105AA0_pump_pump_away(gfx), (u8)D_801117BC_pump_pump_away);
        } else {
            gfx = func_801059BC_pump_pump_away(gfx);
        }
        g = *gfx;
        gDPSetTextureLUT(g++, G_TT_RGBA16);
        gDPLoadTLUT_pal16(g++, 0, h->spr->unk0C);
        for (i = 0; i < 8; i++) {
            if (i != 0 && i != 4) {
                gDPLoadTextureTile_4b(g++, h->spr->unk08, G_IM_FMT_CI, 8, 100, 0, h->val[i], 8, h->val[i] + 10, 0,
                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                      G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 8 << 2, 10 << 2);
                gSPTextureRectangle(g++, D_80110FE4_pump_pump_away[i].x << 2, D_80110FE4_pump_pump_away[i].y << 2, (D_80110FE4_pump_pump_away[i].x + 8) << 2,
                                    (D_80110FE4_pump_pump_away[i].y + 10) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            }
        }
        *gfx = g;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108810_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_80108B0C_pump_pump_away(omObjData *obj) {
    s32 digit[4];
    PpHud *h = &D_80111758_pump_pump_away[1];
    s32 n;
    s32 cur;
    s32 t;
    s32 i;

    for (t = 0; t < 2; t++) {
        n = (D_80111978_pump_pump_away + t)->dist / 10.0f;
        digit[0] = n / 10000;
        n -= digit[0] * 10000;
        digit[1] = n / 1000;
        n -= digit[1] * 1000;
        digit[2] = n / 100;
        n -= digit[2] * 100;
        digit[3] = n / 10;
        n -= digit[3] * 10;
        for (i = 0; i < 4; i++) {
            h->val[t * 4 + i] = 100 - digit[i] * 10;
            if (i == 3) {
                h->val[t * 4 + i] -= n;
            }
        }
        for (i = 3; i > 0; i--) {
            cur = h->val[t * 4 + i];
            if (cur < 11) {
                h->val[t * 4 + i - 1] = h->val[t * 4 + i - 1] - (10 - cur);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108B0C_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_80108CFC_pump_pump_away(omObjData *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if ((D_80111758_pump_pump_away + i)->state == -1) {
            return;
        }
    }
    func_80108B0C_pump_pump_away(obj);
    switch (obj->work[0]) {
        case 0:
            if (D_801116F4_pump_pump_away < 4) {
                for (i = 0; i < 2; i++) {
                    (D_80111758_pump_pump_away + i)->alpha = 0;
                }
            } else {
                obj->work[0] = 1;
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                (D_80111758_pump_pump_away + i)->alpha += 25;
                if ((D_80111758_pump_pump_away + i)->alpha >= 255) {
                    (D_80111758_pump_pump_away + i)->alpha = 255;
                    obj->work[0] = 2;
                }
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                (D_80111758_pump_pump_away + i)->alpha = 255;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108CFC_pump_pump_away);
#endif

void func_80108E74_pump_pump_away(omObjData *obj) {
    PpHud *h = D_80111758_pump_pump_away;
    s32 i;

    D_8011175C_pump_pump_away = func_8000B838_main(0x2E0015);
    D_80111764_pump_pump_away = func_80055194_main((s16)D_8011175C_pump_pump_away);
    D_80111760_pump_pump_away = ((PpDrawHookAdd)(void (*)(void))func_8001AC8C_main)(0, func_80108560_pump_pump_away, 2);
    func_8001C8A8_main((s16)D_80111760_pump_pump_away, 1);
    D_80111788_pump_pump_away = 0;
    h->state = 0;
    h++;
    D_80111790_pump_pump_away = func_8000B838_main(0x2E0016);
    D_80111798_pump_pump_away = func_80055194_main((s16)D_80111790_pump_pump_away);
    D_80111794_pump_pump_away = ((PpDrawHookAdd)(void (*)(void))func_8001AC8C_main)(0, func_80108810_pump_pump_away, 2);
    func_8001C8A8_main((s16)D_80111794_pump_pump_away, 1);
    D_801117BC_pump_pump_away = 0;
    h->state = 0;
    obj->func = func_80108CFC_pump_pump_away;
    for (i = 0; i < 8; i++) {
        h->val[i] = 100;
    }
}

void func_80108FA8_pump_pump_away(void) {
    omAddObj(900, 2, 0, -1, func_80108E74_pump_pump_away)->work[0] = 0;
}

void func_80108FE0_pump_pump_away(omObjData *obj) {
    PpFx *fx = &D_80113400_pump_pump_away[obj->work[0]];
    PpTeam *t;
    PpTeam *t1;

    switch (fx->state) {
        case 0:
            break;
        case 1:
            func_8001C5B4_main(obj->model[0], obj->motion[0]);
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C258_main(obj->model[0], 4, 0);
            fx->state = 3;
            break;
        case 2:
            func_8001C5B4_main(obj->model[1], obj->motion[1]);
            func_8001C6A8_main(obj->model[1], 0.0f);
            func_8001C92C_main(obj->model[1], 0.5f);
            func_8001C814_main(obj->model[1], 1, 0);
            func_8001C258_main(obj->model[1], 4, 0);
            fx->state = 4;
            break;
        case 3:
            t = D_80111978_pump_pump_away;
            t1 = &t[1];
            if (t->dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y -= t->speed;
            } else {
                obj->trans.y -= t1->speed;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            fx->alpha -= 8;
            if (fx->alpha > 0) {
                func_8001F9E4_main(obj->model[0], (u8)fx->alpha);
            } else {
                func_8001C814_main(obj->model[0], 1, 1);
                func_8001C258_main(obj->model[0], 4, 4);
                fx->alpha = 255;
                fx->state = 0;
            }
            break;
        case 4:
            fx->alpha -= 5;
            if (fx->alpha > 0) {
                func_8001F9E4_main(obj->model[1], (u8)fx->alpha);
            } else {
                func_8001C814_main(obj->model[1], 1, 1);
                func_8001C258_main(obj->model[1], 4, 4);
                fx->alpha = 255;
                fx->state = 0;
            }
            break;
    }
}

void func_8010921C_pump_pump_away(omObjData *obj) {
    if (D_80113400_pump_pump_away[obj->work[0]].state == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
            break;
        case 4:
        case 7:
            func_80108FE0_pump_pump_away(obj);
            break;
    }
}

void func_80109280_pump_pump_away(omObjData *obj) {
    PpFx *fx;

    obj->model[0] = func_8000B108_main(0x2E0017, 0x289);
    obj->model[1] = func_8000B108_main(0x2E0019, 0x289);
    func_8000B460_main(obj, 0, 0x2E0018);
    func_8000B460_main(obj, 1, 0x2E001A);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xFF);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C6A8_main(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001FA68_main(obj->model[1]);
    func_8001F9E4_main(obj->model[1], 0xFF);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C6A8_main(obj->model[1], 0.0f);
    func_8001C814_main(obj->model[1], 1, 1);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = D_80111004_pump_pump_away[obj->work[0]].x;
    obj->trans.y = D_80111004_pump_pump_away[obj->work[0]].y;
    obj->trans.z = D_80111004_pump_pump_away[obj->work[0]].z;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->func = func_8010921C_pump_pump_away;
    fx = &D_80113400_pump_pump_away[obj->work[0]];
    fx->state = 0;
    fx->alpha = 255;
}

void func_80109470_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(750, 1, 2, -1, func_80109280_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_801094CC_pump_pump_away(omObjData *obj) {
    PpTeam *t;
    PpArc *a;
    s32 mdl;
    s32 mot;
    s16 se;

    a = &D_80113518_pump_pump_away;
    t = &D_80111978_pump_pump_away[D_8011351C_pump_pump_away];
    switch (a->state) {
        case 0:
            break;
        case 1:
            mdl = obj->model[0];
            mot = obj->motion[0];
            goto start;
        case 2:
            mdl = obj->model[0];
            mot = obj->motion[1];
        start:
            func_8001C5B4_main(mdl, mot);
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C258_main(obj->model[0], 4, 0);
            obj->trans.x = t->obj->trans.x;
            obj->trans.y = t->obj->trans.y + 200.0f;
            obj->trans.z = t->obj->trans.z;
            a->state = 3;
            break;
        case 3:
            if (HmfModelData[obj->model[0]].unk40 >= 16.0f && D_8011110A_pump_pump_away == 0) {
                se = HuAudFXPlay(0x363);
                if (t->obj->work[0] != 0) {
                    func_8004AE00_main(se, 0x60);
                } else {
                    func_8004AE00_main(se, 0x20);
                }
                D_8011110A_pump_pump_away = 1;
            }
            obj->trans.y = t->obj->trans.y + 200.0f;
            if (t->state == 2) {
                a->state = 4;
                break;
            }
            if (D_80111108_pump_pump_away != 0) {
                if (a->angle <= 175.0f) {
                    a->angle = 175.0f;
                    D_80111108_pump_pump_away ^= 1;
                } else {
                    a->angle = PP_WRAP(a->angle - 0.5);
                }
            } else {
                if (a->angle >= 185.0f) {
                    a->angle = 185.0f;
                    D_80111108_pump_pump_away ^= 1;
                } else {
                    a->angle = PP_WRAP(a->angle + 0.5);
                }
            }
            obj->rot.z = PP_WRAP(a->angle + 180.0f);
            t->obj->trans.x = obj->trans.x - sindf(a->angle) * 200.0f;
            t->obj->trans.y = cosdf(a->angle) * 200.0f + obj->trans.y;
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801094CC_pump_pump_away);
#endif

void func_801098E0_pump_pump_away(omObjData *obj) {
    PpArc *a = &D_80113518_pump_pump_away;
    PpTeam *t = &D_80111978_pump_pump_away[D_8011351C_pump_pump_away];

    if (a->state == 4) {
        func_8001C5B4_main(obj->model[0], obj->motion[1]);
        func_8001C6A8_main(obj->model[0], 0.0f);
        func_8001C814_main(obj->model[0], 1, 0);
        func_8001C258_main(obj->model[0], 4, 0);
        obj->trans.x = t->obj->trans.x;
        obj->trans.y = t->obj->trans.y + 200.0f;
        obj->trans.z = t->obj->trans.z;
        a->state = 5;
    }
}

void func_801099D4_pump_pump_away(omObjData *obj) {
    PpArc *a = &D_80113518_pump_pump_away;

    if (a->state == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            if (a->state < 4) {
                func_801094CC_pump_pump_away(obj);
                break;
            }
        case 8:
            func_801098E0_pump_pump_away(obj);
            break;
    }
}

void func_80109A50_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E001B, 0x1689);
    func_8000B460_main(obj, 0, 0x2E001C);
    func_8000B460_main(obj, 1, 0x2E001D);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C6A8_main(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->func = func_801099D4_pump_pump_away;
    D_80113518_pump_pump_away.state = 0;
    D_8011351C_pump_pump_away = -1;
    D_80113520_pump_pump_away = 180.0f;
    D_80113524_pump_pump_away = obj;
}

void func_80109B48_pump_pump_away(void) {
    omAddObj(740, 1, 2, -1, func_80109A50_pump_pump_away)->work[0] = 0;
}

void func_80109B80_pump_pump_away(omObjData *obj) {
    PpSplash *p;
    PpTeam *t;
    s32 i;

    for (i = 0; i < 20; i++) {
        p = &D_801117E0_pump_pump_away[i];
        if (p->state == 0) {
            t = D_80111978_pump_pump_away + obj->work[0];
            p->state = 1;
            p->obj->trans.x = obj->trans.x;
            p->obj->trans.y = obj->trans.y - 200.0f;
            p->obj->trans.z = obj->trans.z;
            p->vel = t->speed * 0.6;
            return;
        }
    }
}

void func_80109C30_pump_pump_away(omObjData *obj) {
    PpSplash *p = &D_801117E0_pump_pump_away[obj->work[0]];

    if (p->state == -1) {
        return;
    }
    switch (p->state) {
        case -1:
            break;
        case 1:
            func_8001C258_main(obj->model[0], 4, 0);
            p->state = 2;
            break;
        case 2:
            p->alpha -= 25;
            if (p->alpha > 0) {
                func_8001F9E4_main(obj->model[0], (u8)p->alpha);
                obj->trans.y -= p->vel * p->vel;
                obj->scale.x += 0.1;
                obj->scale.y += 0.1;
                obj->scale.z += 0.1;
            } else {
                func_8001C258_main(obj->model[0], 4, 4);
                p->alpha = 0xFF;
                p->vel = 0.0f;
                p->state = 0;
                obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
            }
            break;
    }
}

void func_80109D74_pump_pump_away(omObjData *obj) {
    PpSplash *p;

    obj->model[0] = func_8000B108_main(0x2E0013, 0x289);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xFF);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->func = func_80109C30_pump_pump_away;
    p = &D_801117E0_pump_pump_away[obj->work[0]];
    p->state = 0;
    p->alpha = 0xFF;
    p->vel = 0.0f;
    p->obj = obj;
}

void func_80109E3C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 14; i++) {
        omAddObj(760, 1, 0, -1, func_80109D74_pump_pump_away)->work[0] = i;
    }
}

void func_80109E98_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];
    s16 se;

    switch (t->unk0C) {
        case 0:
            func_8001C6A8_main(obj->model[0], 0.0f);
            break;
        case 1:
            func_8001C5B4_main(obj->model[0], obj->motion[0]);
            func_8001C92C_main(obj->model[0], D_80110F9C_pump_pump_away[t->unk10]);
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C814_main(obj->model[0], 4, 0);
            t->unk0C = 2;
            se = HuAudFXPlay(0x362);
            if (obj->work[0] != 0) {
                func_8004AE00_main(se, 0x60);
            } else {
                func_8004AE00_main(se, 0x20);
            }
            break;
        case 2:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2);
                func_8001C92C_main(obj->model[0], D_80110F9C_pump_pump_away[t->unk10]);
                func_8001C814_main(obj->model[0], 4, 4);
                t->unk0C = 3;
            }
            break;
        case 3:
            if (HmfModelData[obj->model[0]].unk40 <= 2.0f) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                t->unk0C = 0;
            }
            break;
    }
}

void func_8010A150_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];

    switch (t->unk0C) {
        case 2:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2);
                func_8001C92C_main(obj->model[0], D_80110F9C_pump_pump_away[t->unk10]);
                func_8001C814_main(obj->model[0], 4, 4);
                t->unk0C = 3;
            }
            break;
        case 3:
            if (HmfModelData[obj->model[0]].unk40 <= 2.0f) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C814_main(obj->model[0], 4, 0);
                func_8001C814_main(obj->model[0], 1, 1);
                t->unk0C = 0;
            }
            break;
        default:
            func_8001C5B4_main(obj->model[0], obj->motion[0]);
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C814_main(obj->model[0], 1, 1);
            t->unk0C = 3;
            break;
    }
}

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
