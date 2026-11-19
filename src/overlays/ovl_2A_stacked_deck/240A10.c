#include "common.h"
// m7 sk: Stacked Deck
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

/* One slot of the overlay's object table (D_8010F730_stacked_deck, 50 x 0x84). */
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

void func_8010F134_stacked_deck(void);
void func_8010655C_stacked_deck(omObjData *obj);
void func_8010669C_stacked_deck(omObjData *obj);
void func_8010C188_stacked_deck(omObjData *obj);
void func_8010D58C_stacked_deck(omObjData *obj);
void func_8010DAE4_stacked_deck(omObjData *obj);
void func_8010DDAC_stacked_deck(omObjData *obj);
void func_8010E368_stacked_deck(omObjData *obj);
void func_8010E650_stacked_deck(omObjData *obj);

/* .rodata */
extern char D_8010F42C_stacked_deck[]; /* "card_k_DEF" */

/* .data */
extern s32 D_8010F35C_stacked_deck;

/* .bss (still asm: ovl_2A_bss.bss.s) */
extern s8 D_8010F6F4_stacked_deck;
extern void *D_8010F708_stacked_deck[6];
extern CcEnt D_8010F730_stacked_deck[50];
extern CcEnt D_8010F7B4_stacked_deck;    /* = D_8010F730_stacked_deck[1] */
extern CcEnt D_8010FA48_stacked_deck[12]; /* = D_8010F730_stacked_deck[6] */
extern CcEnt D_80110078_stacked_deck[3]; /* = D_8010F730_stacked_deck[18] */
extern CcEnt D_8011030C_stacked_deck[3]; /* = D_8010F730_stacked_deck[23] */
extern s16 D_80111150_stacked_deck[];


void func_801059A0_stacked_deck(void) {
    func_8010F134_stacked_deck();
}

f32 func_801059BC_stacked_deck(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

u8 func_80105A3C_stacked_deck(s32 max) {
    return ((u32)(rand8() * max)) >> 8;
}

void func_80105A74_stacked_deck(void) {
    CcEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010F730_stacked_deck; i < 50; i++, ent++) {
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

void func_80105B3C_stacked_deck(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105BB4_stacked_deck(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = fabs(x0 - x1) * 5.0;
    f32 dz = fabs(z0 - z1) * 5.0;
    f32 zoom = sqrtf(dx * dx + dz * dz);
    f32 rot = func_801059BC_stacked_deck(atan2df(dx, dz), 0.0f);

    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

#ifdef NON_MATCHING
void func_80105CBC_stacked_deck(s16 conNo) {
    s16 i;

    if ((u16)conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if (D_800CDA7C_main[conNo] & 0x400) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_stacked_deck(CRotM[i].x, 1.0f);
        }
    }
    if (D_800CDA7C_main[conNo] & 0x800) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_stacked_deck(CRotM[i].x, -1.0f);
        }
    }
    if (D_800CDA7C_main[conNo] & 0x200) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_stacked_deck(CRotM[i].y, 1.0f);
        }
    }
    if (D_800CDA7C_main[conNo] & 0x100) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_stacked_deck(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & 0x8000) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if (D_800CDA7C_main[conNo] & 0x4000) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if (D_800CDA7C_main[conNo] & 2) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if (D_800CDA7C_main[conNo] & 1) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if (D_800CDA7C_main[conNo] & 8) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if (D_800CDA7C_main[conNo] & 4) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if (D_800CDA7C_main[conNo] & 0x2000) {
        osSyncPrintf("\n");
        for (i = 0; i < 1; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80105CBC_stacked_deck);
#endif

void func_80106290_stacked_deck(s8 arg0) {
    D_8010F6F4_stacked_deck = arg0;
}

void func_8010629C_stacked_deck(omObjData *obj, s16 mot, s16 arg2, s16 arg3, s16 arg4, s16 *cur) {
    if (*cur != mot) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[mot]].unk02, arg2, arg3, arg4);
        *cur = mot;
    }
}

f32 func_80106338_stacked_deck(f32 pos, f32 *vel, f32 accel) {
    f32 v = *vel;

    *vel = v - accel;
    return pos + v;
}

void func_80106354_stacked_deck(omObjData *obj, u8 face) {
    func_80033354_main(D_80111150_stacked_deck[obj->work[0]]);
    D_80111150_stacked_deck[obj->work[0]] =
        HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010F708_stacked_deck[face], 0, D_8010F42C_stacked_deck);
}

#ifdef NON_MATCHING
void func_801063F4_stacked_deck(f32 x0, f32 z0, f32 x1, f32 z1, f32 *vx, f32 *vz, f32 speed) {
    f32 dx;
    f32 dz;
    f32 adx;
    f32 adz;
    f32 num;
    f32 den;
    f32 t;

    dx = x1 - x0;
    dz = z1 - z0;
    adx = fabsf(dx);
    adz = fabsf(dz);
    if (adz <= adx) {
        if (dx >= 0.0f) {
            *vx = -speed;
        } else {
            *vx = speed;
        }
        t = dz;
        den = speed;
        num = adx;
        if (den == 0.0f) {
            den = 1.0f;
        }
        den = num / den;
        if (den == 0.0f) {
            den = 1.0f;
        }
        *vz = -(t / den);
    } else {
        if (dz >= 0.0f) {
            *vz = -speed;
        } else {
            *vz = speed;
        }
        t = dx;
        den = speed;
        num = adz;
        if (den == 0.0f) {
            den = 1.0f;
        }
        den = num / den;
        if (den == 0.0f) {
            den = 1.0f;
        }
        *vx = -(t / den);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801063F4_stacked_deck);
#endif

void func_80106554_stacked_deck(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010655C_stacked_deck);

void func_80106654_stacked_deck(void) {
    omObjData *obj = omAddObj(998, 1, 1, -1, func_8010655C_stacked_deck);

    obj->work[0] = 0;
    D_8010F730_stacked_deck[0].obj = obj;
}

void func_80106694_stacked_deck(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010669C_stacked_deck);

void func_80106738_stacked_deck(void) {
    omObjData *obj = omAddObj(999, 1, 1, -1, func_8010669C_stacked_deck);

    obj->work[0] = 0;
    D_8010F7B4_stacked_deck.obj = obj;
}

void func_80106778_stacked_deck(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106780_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801069A0_stacked_deck);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", D_8010F42C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106BC8_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80108E48_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010969C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801097D4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010C188_stacked_deck);

void func_8010C524_stacked_deck(void) {
    omObjData *obj;
    CcEnt *ent;
    s16 i;

    for (i = 0; i < 12; i++) {
        ent = &D_8010FA48_stacked_deck[i];
        obj = omAddObj(550, 3, 3, -1, func_8010C188_stacked_deck);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010C5C8_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010D58C_stacked_deck);

void func_8010D8E8_stacked_deck(void) {
    omObjData *obj;
    CcEnt *ent;
    s16 i;

    for (i = 0; i < 3; i++) {
        ent = &D_80110078_stacked_deck[i];
        obj = omAddObj(570, 5, 5, -1, func_8010D58C_stacked_deck);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010D98C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DAE4_stacked_deck);

void func_8010DBF4_stacked_deck(void) {
    omAddObj(580, 1, 0, -1, func_8010DAE4_stacked_deck)->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DC2C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DDAC_stacked_deck);

void func_8010DEBC_stacked_deck(void) {
    omAddObj(590, 1, 0, -1, func_8010DDAC_stacked_deck)->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DEF4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E368_stacked_deck);

void func_8010E4EC_stacked_deck(void) {
    omObjData *obj;
    CcEnt *ent;
    s16 i;

    for (i = 0; i < 3; i++) {
        ent = &D_8011030C_stacked_deck[i];
        obj = omAddObj(600, 1, 1, -1, func_8010E368_stacked_deck);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

void func_8010E590_stacked_deck(void) {
    u32 i;

    if (D_8010F35C_stacked_deck == 0) {
        D_8010F35C_stacked_deck = 1;
        for (i = 0; i < 1; i++) {
            CZoomM[i] = 2522.7217f;
            CRotM[i].x = 332.3684f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = -200.0f;
            CenterM[i].z = 75.0f;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E650_stacked_deck);

void func_8010E6FC_stacked_deck(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_8010E650_stacked_deck;
    }
}

void func_8010E734_stacked_deck(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010E6FC_stacked_deck;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E78C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010ED44_stacked_deck);

void func_8010EFBC_stacked_deck(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010EFC4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010F134_stacked_deck);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", D_8010F6E8_stacked_deck);
