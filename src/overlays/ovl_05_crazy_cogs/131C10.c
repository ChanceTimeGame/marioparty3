#include "common.h"
// m4 cg: Crazy Cogs (4 players: turn the cogs to complete the picture)
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

#define CG_ABS(x) ((x) < 0.0f ? -(x) : (x))

/* One slot of the overlay's object table (D_8010B9F0_crazy_cogs, 70 x 0x84). */
typedef struct CgEnt {
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
} CgEnt; // Size 0x84

#define CG_ENT_GROUND 0
#define CG_ENT_COG0 1 /* 1..4: the cogs */
#define CG_ENT_8 8
#define CG_ENT_18 18
#define CG_ENT_23 23
#define CG_ENT_24 24
#define CG_ENT_PLAYER 29 /* 29..32 */

/* The ground object's data (func_80106270_crazy_cogs). */
typedef struct CgGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} CgGround; // Size 0xB4

/* A camera (D_8010B898_crazy_cogs). */
typedef struct CgCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} CgCamera; // Size 0x2C

void osSyncPrintf(const char *fmt, ...);
f32 sqrtf(f32);
void func_8000BC48_main(u16, s32);
s32 func_8000B710_main(s32 arg0);
void func_800E131C_minigame(omObjData *obj, f32 arg1);
void func_800E1304_minigame(omObjData *obj, f32 arg1);
void func_800E1310_minigame(omObjData *obj, f32 arg1);
void func_800E1404_minigame(omObjData *obj, f32 arg1, f32 arg2);
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];

/* .data */
extern s32 D_8010B810_crazy_cogs[8];
extern D_80111B50_vine_with_me_Struct D_8010B830_crazy_cogs;
extern s16 D_8010B858_crazy_cogs[4];
extern CgCamera D_8010B898_crazy_cogs[2];
/* .bss */
extern f32 D_8010B9A8_crazy_cogs;
extern s8 D_8010B9A6_crazy_cogs;
extern CgEnt D_8010B9F0_crazy_cogs[70];
extern s16 D_8010BA30_crazy_cogs; /* = D_8010B9F0_crazy_cogs[CG_ENT_GROUND].grp */
extern s16 D_8010BA32_crazy_cogs; /* = D_8010B9F0_crazy_cogs[CG_ENT_GROUND].spr */
extern f32 D_8010BA34_crazy_cogs; /* = D_8010B9F0_crazy_cogs[CG_ENT_GROUND].pos.x */
extern f32 D_8010BA38_crazy_cogs; /* = D_8010B9F0_crazy_cogs[CG_ENT_GROUND].pos.y */
extern f32 D_8010DE14_crazy_cogs;
extern s8 D_8010DE60_crazy_cogs;
extern s8 D_8010DE6A_crazy_cogs[4];
extern s8 D_8010DEB4_crazy_cogs;
/* .rodata */
extern const s16 D_8010B97C_crazy_cogs[];

void func_8010B6E0_crazy_cogs(void);
f32 func_801059BC_crazy_cogs(f32 angle, f32 add);
s32 func_80105B7C_crazy_cogs(s32 max);
void func_80106268_crazy_cogs(omObjData *obj);
void func_80106270_crazy_cogs(omObjData *obj);
void func_80106418_crazy_cogs(omObjData *obj);
void func_801064AC_crazy_cogs(omObjData *obj);
void func_801065F0_crazy_cogs(omObjData *obj);
void func_80106688_crazy_cogs(omObjData *obj);
void func_801067AC_crazy_cogs(omObjData *obj);
void func_8010683C_crazy_cogs(omObjData *obj);
void func_8010694C_crazy_cogs(omObjData *obj);
void func_801069DC_crazy_cogs(omObjData *obj);
void func_8010B064_crazy_cogs(omObjData *obj);
void func_8010B040_crazy_cogs(omObjData *obj);
void func_8010B09C_crazy_cogs(omObjData *obj);
void func_8010B46C_crazy_cogs(omObjData *obj);
void func_8010B570_crazy_cogs(void);
void func_80105A3C_crazy_cogs(void);

void func_801059A0_crazy_cogs(void) {
    func_8010B6E0_crazy_cogs();
}

f32 func_801059BC_crazy_cogs(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

void func_80105A3C_crazy_cogs(void) {
    CgEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010B9F0_crazy_cogs; i < 70; i++, ent++) {
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
void func_80105B04_crazy_cogs(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

s32 func_80105B7C_crazy_cogs(s32 max) {
    return rand8() % max;
}

/* The cog speed under an object: 55 on the big cog's rim, 28 inside it, 1 or 55 beyond it. */
f32 func_80105BD0_crazy_cogs(omObjData *obj) {
    f32 x;
    f32 z;
    f32 d;
    f32 ret;

    x = (s32)CG_ABS(obj->trans.x);
    z = (s32)CG_ABS(obj->trans.z);
    d = sqrtf(x * x + z * z);
    if (d > 480.0f) {
        ret = 1.0f;
        x = (s32)CG_ABS(obj->trans.x - 580.0f);
        z = (s32)CG_ABS(obj->trans.z + 450.0f);
        if (sqrtf(x * x + z * z) <= 380.0f) {
            ret = 55.0f;
        }
    } else if ((d <= 480.0f) & (d > 350.0f)) {
        ret = 55.0f;
    } else {
        ret = 28.0f;
    }
    return ret;
}

/* A rough angle (0-360, linear in each quadrant) of the direction (x, z). */
f32 func_80105E4C_crazy_cogs(f32 x, f32 z) {
    f32 ret = 0.0f;
    s32 q = 0;
    f32 ax;
    f32 az;

    if (x >= 0.0f) {
        q |= 1;
    } else {
        q |= 2;
    }
    if (z < 0.0f) {
        q |= 4;
    } else {
        q |= 8;
    }
    ax = CG_ABS(x);
    az = CG_ABS(z);
    switch (q) {
    case 5:
        if (x == 0.0f) {
            return 0.0f;
        }
        ret = (90.0f / (ax + az)) * ax;
        break;
    case 9:
        if (x == 0.0f) {
            return 180.0f;
        }
        if (z == 0.0f) {
            return 90.0f;
        }
        ret = (90.0f / (ax + az)) * az + 90.0f;
        break;
    case 10:
        if (x == 0.0f) {
            return 270.0f;
        }
        ret = (90.0f / (ax + az)) * ax + 180.0f;
        break;
    case 6:
        ret = (90.0f / (ax + az)) * az + 270.0f;
        break;
    }
    return ret;
}

void func_80106034_crazy_cogs(omObjData *obj, u16 motion, s16 arg2) {
    if (motion < 10) {
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        func_8001C814_main(obj->model[0], arg2, arg2);
    }
}

void func_801060A0_crazy_cogs(omObjData *obj, u16 motion, s16 arg2, s16 arg3, s16 arg4) {
    if (motion < 10) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[motion]].unk02, arg2, arg3, arg4);
    }
}

/* Steps an angle 6 degrees back towards 0 (none within 5 degrees of it). */
f32 func_8010611C_crazy_cogs(f32 angle) {
    if ((angle > 5.0f) & (angle < 355.0f)) {
        angle = func_801059BC_crazy_cogs(angle, (angle < 180.0f) ? -6.0f : 6.0f);
    } else {
        angle = 0.0f;
    }
    return angle;
}

/* Debug: prints a sound kind and a channel. */
void func_801061CC_crazy_cogs(s16 ch, s16 kind) {
    switch (kind) {
    case 0:
        osSyncPrintf("\x8E\x95\x8E\xD4\t");
        break;
    case 1:
        osSyncPrintf("\x83\x58\x83\x43\x83\x62\x83\x60\t");
        break;
    case 2:
        osSyncPrintf("\x91\xAB\x89\xB9\t");
        break;
    case 3:
        osSyncPrintf("\x83\x4C\x83\x89\x81\x5B\x97\x8E\x89\xBA\t");
        break;
    case 4:
        osSyncPrintf("\x94\x9A\x94\xAD\t");
        break;
    }
    osSyncPrintf("ch=%d\n", ch);
}

void func_80106268_crazy_cogs(omObjData *obj) {
}

void func_80106270_crazy_cogs(omObjData *obj) {
    CgGround *gw;
    s16 grp;

    /* retail names entity [0]'s fields by their own labels */
    D_8010BA34_crazy_cogs = 160.0f;
    D_8010BA38_crazy_cogs = 120.0f;
    grp = func_8000B838_main(0x260000);
    D_8010BA30_crazy_cogs = grp;
    D_8010BA32_crazy_cogs = InitEspriteSlot(grp, 0, 0);
    func_8000BC48_main(D_8010BA32_crazy_cogs, 0x5000);
    func_8000BBD4_main(D_8010BA32_crazy_cogs, D_8010BA34_crazy_cogs, D_8010BA38_crazy_cogs);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
    obj->data = gw = HuMemAllocTag(sizeof(CgGround), 31000);
    memset(gw, 0, sizeof(CgGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E1404_minigame(D_800EC1C0_minigame[0], 0.0f, 360.0f);
    obj->model[0] = -1;
    obj->func = func_80106268_crazy_cogs;
}

void func_801063DC_crazy_cogs(void) {
    D_8010B9F0_crazy_cogs[CG_ENT_GROUND].obj = omAddObj(500, 1, 0, -1, func_80106270_crazy_cogs);
}

/* A player's marker blinks for 20 frames when D_8010DE6A_crazy_cogs[player] is set. */
void func_80106418_crazy_cogs(omObjData *obj) {
    s8 i = obj->work[0];
    CgEnt *ent = &D_8010B9F0_crazy_cogs[CG_ENT_PLAYER + i];

    if (D_8010DE6A_crazy_cogs[i] != 0) {
        if (ent->unk04 & 1) {
            obj->trans.y = 10.0f;
        } else {
            obj->trans.y = 0.0f;
        }
        if (++ent->unk04 >= 20) {
            ent->unk04 = 0;
            D_8010DE6A_crazy_cogs[i] = 0;
        }
    }
}

void func_801064AC_crazy_cogs(omObjData *obj) {
    s8 i = obj->work[0];

    obj->model[0] = func_8000B108_main(D_8010B858_crazy_cogs[i] | 0x260000, 0xB9);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 1);
    D_8010DE6A_crazy_cogs[i] = 0;
    obj->func = func_80106418_crazy_cogs;
}

void func_8010654C_crazy_cogs(void) {
    omObjData *obj;
    CgEnt *ent;
    s8 i;

    for (i = 0; i < 4; i++) {
        ent = &D_8010B9F0_crazy_cogs[CG_ENT_PLAYER + i];
        obj = omAddObj(1700, 1, 0, -1, func_801064AC_crazy_cogs);
        ent->obj = obj;
        obj->work[0] = i;
    }
}

void func_801065F0_crazy_cogs(omObjData *obj) {
    switch (D_8010DE60_crazy_cogs) {
    case 0:
        break;
    case 1:
        obj->rot.y = func_801059BC_crazy_cogs(obj->rot.y, -3.3f);
        break;
    case 2:
        obj->rot.y = func_801059BC_crazy_cogs(obj->rot.y, 3.3f);
        break;
    }
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
}

void func_80106688_crazy_cogs(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x260002, 0xB9);
    obj->model[1] = func_8000B108_main(0x260005, 0xB9);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    obj->func = func_801065F0_crazy_cogs;
    D_8010B9A8_crazy_cogs = 4.4f;
    D_8010DE14_crazy_cogs = 6.6000004f;
}

void func_80106770_crazy_cogs(void) {
    D_8010B9F0_crazy_cogs[1].obj = omAddObj(1000, 2, 0, -1, func_80106688_crazy_cogs);
}

void func_801067AC_crazy_cogs(omObjData *obj) {
    switch (D_8010DE60_crazy_cogs) {
    case 0:
        break;
    case 1:
        obj->rot.y = func_801059BC_crazy_cogs(obj->rot.y, D_8010B9A8_crazy_cogs);
        break;
    case 2:
        obj->rot.y = func_801059BC_crazy_cogs(obj->rot.y, -D_8010B9A8_crazy_cogs);
        break;
    }
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
}

void func_8010683C_crazy_cogs(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x260003, 0xB9);
    obj->model[1] = func_8000B108_main(0x260006, 0xB9);
    obj->trans.x = 580.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -450.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    obj->func = func_801067AC_crazy_cogs;
}

void func_80106910_crazy_cogs(void) {
    D_8010B9F0_crazy_cogs[2].obj = omAddObj(1100, 2, 0, -1, func_8010683C_crazy_cogs);
}

void func_8010694C_crazy_cogs(omObjData *obj) {
    switch (D_8010DE60_crazy_cogs) {
    case 0:
        break;
    case 1:
        obj->rot.y = func_801059BC_crazy_cogs(obj->rot.y, -D_8010DE14_crazy_cogs);
        break;
    case 2:
        obj->rot.y = func_801059BC_crazy_cogs(obj->rot.y, D_8010DE14_crazy_cogs);
        break;
    }
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
}

void func_801069DC_crazy_cogs(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x260004, 0xB9);
    obj->model[1] = func_8000B108_main(0x260007, 0xB9);
    obj->trans.x = 185.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -800.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    obj->func = func_8010694C_crazy_cogs;
}

void func_80106AB0_crazy_cogs(void) {
    D_8010B9F0_crazy_cogs[3].obj = omAddObj(1200, 2, 0, -1, func_801069DC_crazy_cogs);
}

/* Starts the cogs turning (1 or 2: the direction). */
void func_80106AEC_crazy_cogs(s8 dir) {
    D_8010DE60_crazy_cogs = dir;
    D_8010B9A6_crazy_cogs = 0;
    D_8010DEB4_crazy_cogs = func_80105B7C_crazy_cogs(5) + 10;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80106B24_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80106D54_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80106F54_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107078_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010728C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801074A0_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107778_crazy_cogs);

void func_8010787C_crazy_cogs(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107884_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107AB8_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107CA8_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107D58_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107E00_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80108190_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80108464_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801087B8_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80108B0C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80108EE8_crazy_cogs);

void func_80109084_crazy_cogs(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010908C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801091F4_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109298_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109388_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801097EC_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109A44_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109B88_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109D24_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109D44_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109F64_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010A4A4_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010A548_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010A67C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010AA10_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010AAA4_crazy_cogs);

void func_8010AAE0_crazy_cogs(void) {
}

void func_8010AAE8_crazy_cogs(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010AAF0_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010ABE0_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010AE08_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010AF58_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010AF94_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B040_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B064_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B09C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B0F4_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B46C_crazy_cogs);

void func_8010B568_crazy_cogs(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B570_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B6E0_crazy_cogs);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", D_8010B97C_crazy_cogs);
