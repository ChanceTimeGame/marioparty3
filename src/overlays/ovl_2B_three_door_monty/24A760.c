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

void func_801059A0_three_door_monty(void);
f32 func_801059BC_three_door_monty(f32 angle, f32 add);
u8 func_80105A3C_three_door_monty(s32 max);
void func_80105A74_three_door_monty(void);
void func_80105B3C_three_door_monty(s32 player);
void func_80105BB4_three_door_monty(f32 x0, f32 z0, f32 x1, f32 z1);
void func_80105CBC_three_door_monty(s32 conNo);
void func_801062E8_three_door_monty(s8 arg0);
void func_801062F4_three_door_monty(omObjData *obj, s16 mot, s16 arg2, s16 arg3, s16 arg4, s16 *cur);
void func_80106390_three_door_monty(omObjData *obj, s16 mot, s16 arg2, s16 arg3, s16 *cur);
void func_8010642C_three_door_monty(f32 x0, f32 z0, f32 x1, f32 z1, f32 *vx, f32 *vz, f32 speed);
void func_8010658C_three_door_monty(omObjData *obj, f32 *x, f32 *z, f32 scale);
f32 func_801066F4_three_door_monty(f32 cur, f32 target, f32 step);
f32 func_801067C4_three_door_monty(f32 pos, f32 *vel, f32 accel);
void func_801067E0_three_door_monty(omObjData *obj, u8 frame);
void func_80106868_three_door_monty(Gfx **gfx, s32 arg1, s32 arg2);
void func_80106B98_three_door_monty(omObjData *obj);
void func_80106EDC_three_door_monty(omObjData *obj);
void func_801071F4_three_door_monty(void);
void func_801071FC_three_door_monty(omObjData *obj);
void func_80107344_three_door_monty(void);
void func_80107384_three_door_monty(omObjData *obj);
void func_8010742C_three_door_monty(omObjData *obj);
void func_801074B4_three_door_monty(void);
void func_80107500_three_door_monty(omObjData *obj);
void func_80108034_three_door_monty(omObjData *obj);
void func_80108C28_three_door_monty(omObjData *obj);
void func_801090C8_three_door_monty(void);
void func_8010916C_three_door_monty(omObjData *obj);
void func_80109594_three_door_monty(omObjData *obj);
void func_801096FC_three_door_monty(void);
void func_8010973C_three_door_monty(omObjData *obj);
void func_80109890_three_door_monty(omObjData *obj);
void func_801099EC_three_door_monty(void);
void func_80109A90_three_door_monty(omObjData *obj);
void func_80109C84_three_door_monty(omObjData *obj);
void func_80109F0C_three_door_monty(omObjData *obj);
void func_8010A27C_three_door_monty(omObjData *obj);
void func_8010A678_three_door_monty(omObjData *obj);
void func_8010B138_three_door_monty(omObjData *obj);
void func_8010B5A8_three_door_monty(void);
void func_8010B7B8_three_door_monty(omObjData *obj);
void func_8010BC08_three_door_monty(omObjData *obj);
void func_8010BD88_three_door_monty(omObjData *obj);
void func_8010BE64_three_door_monty(omObjData *obj);
void func_8010C1B4_three_door_monty(omObjData *obj);
void func_8010C2DC_three_door_monty(omObjData *obj);
void func_8010C358_three_door_monty(omObjData *obj);
void func_8010C390_three_door_monty(omObjData *obj);
void func_8010C3E8_three_door_monty(omObjData *obj);
void func_8010C8C0_three_door_monty(omObjData *obj);
void func_8010CA40_three_door_monty(void);
void func_8010CA48_three_door_monty(void);
void func_8010CBBC_three_door_monty(void);

/* .data */
extern CcCamera D_8010CDD0_three_door_monty[3];
/* .rodata */
extern char D_8010CEFC_three_door_monty[];
/* .bss */
extern s16 D_8010D230_three_door_monty;
extern s16 D_8010D232_three_door_monty;
extern CcTexSize D_8010D234_three_door_monty;
extern void *D_8010D238_three_door_monty[3];
extern s16 D_8010D244_three_door_monty[4];
extern HuSprite_Unk84_Struct *D_8010D24C_three_door_monty;
extern s16 D_8010D250_three_door_monty;
extern u8 D_8010D251_three_door_monty;      /* the low byte of D_8010D250_three_door_monty */
extern s16 D_8010D252_three_door_monty;
extern s16 D_8010D254_three_door_monty;
extern s16 D_8010D256_three_door_monty;
extern s16 D_8010D258_three_door_monty[4];
extern CcEnt D_8010D260_three_door_monty[50];
extern CcEnt D_8010D2E4_three_door_monty[4]; /* = D_8010D260_three_door_monty[1]: the players */
extern CcEnt D_8010D4F4_three_door_monty[3]; /* = D_8010D260_three_door_monty[5] */
extern CcEnt D_8010D680_three_door_monty;    /* = D_8010D260_three_door_monty[8] */
extern CcEnt D_8010D704_three_door_monty[3]; /* = D_8010D260_three_door_monty[9] */
extern CcEnt D_8010D890_three_door_monty;    /* = D_8010D260_three_door_monty[12] */
extern f32 D_8010D8A8_three_door_monty;      /* = D_8010D260_three_door_monty[12].unk18 */
extern s16 D_8010EC28_three_door_monty[4];
extern u8 D_8010EC30_three_door_monty;
extern s16 D_8010EC32_three_door_monty;
extern HuSprite_Unk84_Struct *D_8010EC34_three_door_monty;
extern u16 D_8010EC38_three_door_monty;
extern s16 D_8010EC3A_three_door_monty;
extern s16 D_8010EC3C_three_door_monty;
extern s16 D_8010EC3E_three_door_monty;
extern s16 D_8010EC40_three_door_monty;
extern u8 D_8010EC42_three_door_monty;
extern s16 D_8010EC44_three_door_monty;
extern u16 D_8010EC46_three_door_monty;
extern u8 D_8010EC47_three_door_monty;      /* the low byte of D_8010EC46_three_door_monty */
extern s16 D_8010EC48_three_door_monty;
extern s16 D_8010EC4A_three_door_monty[3];
extern s16 D_8010EC50_three_door_monty[8];




void func_801059A0_three_door_monty(void) {
    func_8010CBBC_three_door_monty();
}

f32 func_801059BC_three_door_monty(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

u8 func_80105A3C_three_door_monty(s32 max) {
    return ((u32)(rand8() * max)) >> 8;
}

void func_80105A74_three_door_monty(void) {
    CcEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010D260_three_door_monty; i < 50; i++, ent++) {
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

void func_80105B3C_three_door_monty(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105BB4_three_door_monty(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = fabs(x0 - x1) * 5.0;
    f32 dz = fabs(z0 - z1) * 5.0;
    f32 zoom = sqrtf(dx * dx + dz * dz);
    f32 rot = func_801059BC_three_door_monty(atan2df(dx, dz), 0.0f);

    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

#ifdef NON_MATCHING
void func_80105CBC_three_door_monty(s32 conNo) {
    s16 i;

    if ((u16)conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x400) {
        for (i = 0; i < 3; i++) {
            CRotM[i].x = func_801059BC_three_door_monty(CRotM[i].x, 1.0f);
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x800) {
        for (i = 0; i < 3; i++) {
            CRotM[i].x = func_801059BC_three_door_monty(CRotM[i].x, -1.0f);
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x200) {
        for (i = 0; i < 3; i++) {
            CRotM[i].y = func_801059BC_three_door_monty(CRotM[i].y, 1.0f);
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x100) {
        for (i = 0; i < 3; i++) {
            CRotM[i].y = func_801059BC_three_door_monty(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[(s16)conNo] & 0x8000) {
        for (i = 0; i < 3; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x4000) {
        for (i = 0; i < 3; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 2) {
        for (i = 0; i < 3; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 1) {
        for (i = 0; i < 3; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 8) {
        for (i = 0; i < 3; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 4) {
        for (i = 0; i < 3; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if (D_800CDA7C_main[(s16)conNo] & 0x2000) {
        osSyncPrintf("\n");
        for (i = 0; i < 3; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80105CBC_three_door_monty);
#endif

void func_801062E8_three_door_monty(s8 arg0) {
    D_8010EC30_three_door_monty = arg0;
}

void func_801062F4_three_door_monty(omObjData *obj, s16 mot, s16 arg2, s16 arg3, s16 arg4, s16 *cur) {
    if (*cur != mot) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[mot]].unk02, arg2, arg3, arg4);
        *cur = mot;
    }
}

void func_80106390_three_door_monty(omObjData *obj, s16 mot, s16 arg2, s16 arg3, s16 *cur) {
    if (*cur != mot) {
        func_8001C5B4_main(obj->model[0], obj->motion[mot]);
        func_8001C814_main(obj->model[0], arg2, arg3);
        *cur = mot;
    }
}

#ifdef NON_MATCHING
void func_8010642C_three_door_monty(f32 x0, f32 z0, f32 x1, f32 z1, f32 *vx, f32 *vz, f32 speed) {
    f32 dx = x1 - x0;
    f32 dz = z1 - z0;
    f32 adx = fabsf(dx);
    f32 adz = fabsf(dz);
    f32 d;

    if (adz <= adx) {
        if (dx >= 0.0f) {
            *vx = -speed;
        } else {
            *vx = speed;
        }
        d = speed;
        if (d == 0.0f) {
            d = 1.0f;
        }
        d = adx / d;
        if (d == 0.0f) {
            d = 1.0f;
        }
        *vz = -(dz / d);
    } else {
        if (dz >= 0.0f) {
            *vz = -speed;
        } else {
            *vz = speed;
        }
        d = speed;
        if (d == 0.0f) {
            d = 1.0f;
        }
        d = adz / d;
        if (d == 0.0f) {
            d = 1.0f;
        }
        *vx = -(dx / d);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010642C_three_door_monty);
#endif

void func_8010658C_three_door_monty(omObjData *obj, f32 *x, f32 *z, f32 scale) {
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

#ifdef NON_MATCHING
f32 func_801066F4_three_door_monty(f32 cur, f32 target, f32 step) {
    f32 diff = target - cur;

    if (diff < 0.0f) {
        diff = -diff;
    }
    if (diff < step) {
        return target;
    }
    if (cur < target) {
        return cur = func_801059BC_three_door_monty(cur, (diff > 180.0f) ? -step : step);
    }
    if (target < cur) {
        return cur = func_801059BC_three_door_monty(cur, (diff > 180.0f) ? step : -step);
    }
    return 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801066F4_three_door_monty);
#endif

f32 func_801067C4_three_door_monty(f32 pos, f32 *vel, f32 accel) {
    f32 v = *vel;

    *vel = v - accel;
    return pos + v;
}

void func_801067E0_three_door_monty(omObjData *obj, u8 frame) {
    func_80033354_main(D_8010EC3E_three_door_monty);
    D_8010EC3E_three_door_monty = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010D238_three_door_monty[frame], 0, D_8010CEFC_three_door_monty);
}

#ifdef NON_MATCHING
void func_80106868_three_door_monty(Gfx **gfx, s32 arg1, s32 arg2) {
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
    gDPLoadTLUT_pal256(g++, D_8010D24C_three_door_monty->unk0C);
    for (i = 0, y = 49, x = 0; i < 191; i += 4) {
        i -= x;
        gDPSetTextureImage(g++, G_IM_FMT_CI, G_IM_SIZ_8b, 320, D_8010D24C_three_door_monty->unk08);
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80106868_three_door_monty);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80106B98_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80106EDC_three_door_monty);

void func_801071F4_three_door_monty(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_801071FC_three_door_monty);

void func_80107344_three_door_monty(void) {
    omObjData *obj = omAddObj(50, 5, 10, -1, func_801071FC_three_door_monty);

    obj->work[0] = 0;
    D_8010D260_three_door_monty[CC_ENT_GROUND].obj = obj;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", D_8010CEFC_three_door_monty);

void func_80107384_three_door_monty(omObjData *obj) {
    CcEnt *ent = &D_8010D890_three_door_monty;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010D8A8_three_door_monty += 0.05f;
    }
    func_8001E888_main(obj->model[0], ent->unk18, 0, D_8010D234_three_door_monty.w, D_8010D234_three_door_monty.h,
                       "dammy-castle_ground1_2", 0);
}

void func_8010742C_three_door_monty(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x4C000D, 681);
    func_8001C954_main(obj->model[0]);
    func_800335BC_main("243_water_DEF", &D_8010D234_three_door_monty);
    D_8010D8A8_three_door_monty = 0;
    obj->trans.x = 0;
    obj->trans.y = 0;
    obj->trans.z = 0;
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_80107384_three_door_monty;
}

void func_801074B4_three_door_monty(void) {
    omObjData *obj = omAddObj(270, 1, 0, -1, func_8010742C_three_door_monty);

    obj->work[0] = 0;
    D_8010D890_three_door_monty.obj = obj;
    omSetStatBit(obj, 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80107500_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80108034_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80108C28_three_door_monty);

void func_801090C8_three_door_monty(void) {
    omObjData *obj;
    CcEnt *ent;
    s16 i;

    for (i = 0; i < 3; i++) {
        ent = &D_8010D4F4_three_door_monty[i];
        obj = omAddObj(150, 5, 10, -1, func_80108C28_three_door_monty);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010916C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109594_three_door_monty);

void func_801096FC_three_door_monty(void) {
    omObjData *obj = omAddObj(200, 5, 10, -1, func_80109594_three_door_monty);

    obj->work[0] = 0;
    D_8010D680_three_door_monty.obj = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010973C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109890_three_door_monty);

void func_801099EC_three_door_monty(void) {
    omObjData *obj;
    CcEnt *ent;
    s16 i;

    for (i = 0; i < 3; i++) {
        ent = &D_8010D704_three_door_monty[i];
        obj = omAddObj(250, 5, 10, -1, func_80109890_three_door_monty);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109A90_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109C84_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_80109F0C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010A27C_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010A678_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010B138_three_door_monty);

void func_8010B5A8_three_door_monty(void) {
    s16 slots[4];
    omObjData *obj;
    CcEnt *ent;
    s16 i;
    s16 j;
    u16 player;

    for (i = 0; i < 4; i++) {
        slots[i] = i;
    }
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
        ent = &D_8010D2E4_three_door_monty[i];
        obj = omAddObj(100, 10, 60, -1, func_8010B138_three_door_monty);
        obj->work[0] = player;
        obj->work[3] = GwPlayer[player].pad;
        ent->obj = obj;
        j = rand8() % (4 - i);
        obj->work[1] = slots[j];
        slots[j] = -1;
        for (j = 1; j < 4 - i; j++) {
            if (slots[j - 1] == -1) {
                slots[j - 1] = slots[j];
                slots[j] = -1;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010B7B8_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010BC08_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010BD88_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010BE64_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010C1B4_three_door_monty);

void func_8010C2DC_three_door_monty(omObjData *obj) {
    s16 i;

    for (i = 0; i < 3; i++) {
        DataClose(D_8010D238_three_door_monty[i]);
    }
    func_80033354_main(D_8010EC3E_three_door_monty);
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010C358_three_door_monty(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010C2DC_three_door_monty;
    }
}

void func_8010C390_three_door_monty(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010C358_three_door_monty;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010C3E8_three_door_monty);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2B_three_door_monty/24A760", func_8010C8C0_three_door_monty);

void func_8010CA40_three_door_monty(void) {
}

void func_8010CA48_three_door_monty(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 3;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(3);
    func_8000B710_main(3);
    for (i = 0; i < 3; i++) {
        ScissorSet(i, D_8010CDD0_three_door_monty[i].scissor[0], D_8010CDD0_three_door_monty[i].scissor[1],
                   D_8010CDD0_three_door_monty[i].scissor[2], D_8010CDD0_three_door_monty[i].scissor[3]);
        ViewportSet(i, D_8010CDD0_three_door_monty[i].viewport[0], D_8010CDD0_three_door_monty[i].viewport[1],
                    D_8010CDD0_three_door_monty[i].viewport[2], D_8010CDD0_three_door_monty[i].viewport[3],
                    D_8010CDD0_three_door_monty[i].viewport[4], D_8010CDD0_three_door_monty[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010CDD0_three_door_monty[i].fov, 80.0f, 8000.0f);
    }
}

extern const s16 D_8010D228_three_door_monty[];

void func_8010CBBC_three_door_monty(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(60, 0);
    func_8004A208_main();
    func_8010CA48_three_door_monty();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010D228_three_door_monty, 0);
    func_80045010_main(D_8010D228_three_door_monty, 1);
    omAddObj(1000, 0, 0, -1, func_8010C8C0_three_door_monty);
    omAddObj(1000, 0, 0, -1, func_8010C390_three_door_monty);
    func_80105A74_three_door_monty();
}

const s16 D_8010D228_three_door_monty[] = { 0x8260, 0x8261, 0x8262, 0 };
