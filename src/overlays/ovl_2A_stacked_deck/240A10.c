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
void func_80106780_stacked_deck(omObjData *obj);
void func_801069A0_stacked_deck(omObjData *obj);
void func_801063F4_stacked_deck(f32 x0, f32 z0, f32 x1, f32 z1, f32 *vx, f32 *vz, f32 speed);
extern f32 D_800EB744_minigame;
void func_8010D98C_stacked_deck(omObjData *obj);
void func_8010DC2C_stacked_deck(omObjData *obj);
s32 HmfSprModelCreate(void *, s32, u8);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
void func_80014714_main(s16 index, u16 arg1);
void func_80014794_main(s16 index, u8 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);

/* An entry of D_800CBB60_main (minigame BD210.c's MgSprModel) */
typedef struct SkSprModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x22];
} SkSprModel; /* size 0x24 */
extern SkSprModel *D_800CBB60_main;
void func_8010655C_stacked_deck(omObjData *obj);
void func_8010669C_stacked_deck(omObjData *obj);
void func_80106694_stacked_deck(omObjData *obj);
void func_80106554_stacked_deck(omObjData *obj);
void func_8010C188_stacked_deck(omObjData *obj);
void func_8010D58C_stacked_deck(omObjData *obj);
void func_8010DAE4_stacked_deck(omObjData *obj);
void func_8010DDAC_stacked_deck(omObjData *obj);
void func_8010E368_stacked_deck(omObjData *obj);
void func_8010E650_stacked_deck(omObjData *obj);
void func_8010EFC4_stacked_deck(void);
void func_8010ED44_stacked_deck(omObjData *obj);
void func_8010E734_stacked_deck(omObjData *obj);
extern const s16 D_8010F6E8_stacked_deck[];

/* .rodata */
extern char D_8010F42C_stacked_deck[]; /* "card_k_DEF" */

/* .data */
/* The twelve card slots on the table (x, z). */
typedef struct SkSlot {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
} SkSlot; // Size 8
extern SkSlot D_8010F2B0_stacked_deck[12]; /* asm labels D_8010F2B4..D_8010F2E4 are its fields */
extern s32 D_8010F35C_stacked_deck;
extern s32 D_8010F290_stacked_deck[8]; /* per character */
extern CcCamera D_8010F360_stacked_deck[1]; /* asm labels D_8010F364..D_8010F388 are its fields */
extern u8 D_8010F334_stacked_deck[]; /* the minigame control block (CcCtrl-like, 0x28) */

/* .bss (still asm: ovl_2A_bss.bss.s) */
extern s16 D_8010F6F0_stacked_deck;
extern s16 D_8010F6F2_stacked_deck;
extern u8 D_8010F6F4_stacked_deck;
extern void *D_8010F708_stacked_deck[6];
extern s16 D_8010F720_stacked_deck;
extern CcEnt D_8010F730_stacked_deck[50];
extern CcEnt D_8010F7B4_stacked_deck;    /* = D_8010F730_stacked_deck[1] */
extern CcEnt D_8010F838_stacked_deck[4]; /* = D_8010F730_stacked_deck[2]: the four players */
extern CcEnt D_8010FA48_stacked_deck[12]; /* = D_8010F730_stacked_deck[6] */
extern CcEnt D_80110078_stacked_deck[3]; /* = D_8010F730_stacked_deck[18] */
extern CcEnt D_801100FC_stacked_deck;    /* = D_8010F730_stacked_deck[19] */
extern CcEnt D_80110180_stacked_deck;    /* = D_8010F730_stacked_deck[20] */
extern CcEnt D_8011030C_stacked_deck[3]; /* = D_8010F730_stacked_deck[23] */
extern s16 D_801110F8_stacked_deck;
extern s16 D_801110FA_stacked_deck;
extern s16 D_80111100_stacked_deck;
extern s16 D_8011110A_stacked_deck;
extern s16 D_8011110C_stacked_deck;
extern s16 D_80111120_stacked_deck;
extern s16 D_80111128_stacked_deck[12];
extern s16 D_80111140_stacked_deck;
extern s16 D_80111142_stacked_deck[4];
extern s16 D_8011114A_stacked_deck;
extern s16 D_8011114C_stacked_deck;
extern s16 D_8011114E_stacked_deck;
extern s16 D_80111150_stacked_deck[12];
extern s16 D_80110208_stacked_deck;
extern s16 D_8011028C_stacked_deck;
extern u8 D_80111169_stacked_deck;
extern s16 D_8011116A_stacked_deck;
extern s16 D_8011116C_stacked_deck;
extern s16 D_8011116E_stacked_deck;


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

void func_80106554_stacked_deck(omObjData *obj) {
}

void func_8010655C_stacked_deck(omObjData *obj) {
    CcGround *gw;

    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
    obj->data = gw = HuMemAllocTag(sizeof(CcGround), 31000);
    memset(gw, 0, sizeof(CcGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E139C_minigame(D_800EC1C0_minigame[0], 1.0f, -5060.0f, -5000.0f, 5060.0f, 5000.0f);
    obj->func = func_80106554_stacked_deck;
}

void func_80106654_stacked_deck(void) {
    omObjData *obj = omAddObj(998, 1, 1, -1, func_8010655C_stacked_deck);

    obj->work[0] = 0;
    D_8010F730_stacked_deck[0].obj = obj;
}

void func_80106694_stacked_deck(omObjData *obj) {
}

void func_8010669C_stacked_deck(omObjData *obj) {
    CcEnt *ent = &D_8010F7B4_stacked_deck;

    ent->grp = func_8000B838_main(0x4B0000);
    ent->spr = InitEspriteSlot(ent->grp, 0, 0);
    func_8000BC48_main(ent->spr, 0x4000);
    ent->pos.x = 160.0f;
    ent->pos.y = 120.0f;
    func_8000BBD4_main(ent->spr, 160, 120);
    obj->func = func_80106694_stacked_deck;
}

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

#ifdef NON_MATCHING
void func_80106BC8_stacked_deck(omObjData *obj) {
    CcEnt *pl;
    MgWork *gw;
    CcEnt *e;
    CcEnt *p;
    omObjData *o;
    HmfModel *m;
    s16 i;
    s16 r;
    s32 busy;
    f32 tx;
    f32 vx;
    f32 vz;

    pl = &D_8010F838_stacked_deck[obj->work[0]];
    gw = obj->data;
    if (D_8010F6F4_stacked_deck != 6) {
        func_80105B3C_stacked_deck(obj->work[0]);
    }
    switch (D_8010F6F4_stacked_deck) {
    case 1:
    case 2:
    case 3:
        obj->rot.y = 0.0f;
        gw->unk3C = 180.0f;
        break;
    case 4:
        if (obj->work[1] == 0) {
            if (obj->trans.x > 0.0f) {
                D_800CBB6E_main[obj->work[3]] = -60;
            } else if (obj->trans.z > 800.0f) {
                D_800D20A1_main[obj->work[3]] = 60;
            }
            if (obj->trans.z <= 800.0f) {
                D_80111169_stacked_deck = 4;
            }
        } else if (D_8011116E_stacked_deck >= obj->work[1]) {
            if ((obj->work[1] - 1) * 140.0f < obj->trans.x) {
                D_800CBB6E_main[obj->work[3]] = -60;
            } else {
                obj->trans.x = (obj->work[1] - 1) * 140.0f;
                gw->unk3C = 180.0f;
            }
        }
        break;
    case 5:
        if (obj->work[1] != 0 && D_8011116E_stacked_deck >= obj->work[1]) {
            if ((obj->work[1] - 1) * 140.0f < obj->trans.x) {
                D_800CBB6E_main[obj->work[3]] = -60;
            } else {
                obj->trans.x = (obj->work[1] - 1) * 140.0f;
                gw->unk3C = 180.0f;
            }
        }
        break;
    case 13:
        if (obj->work[1] == 0) {
            if (obj->trans.x > 0.0f) {
                D_800CBB6E_main[obj->work[3]] = -60;
            } else if (obj->trans.z > 800.0f) {
                D_800D20A1_main[obj->work[3]] = 60;
            }
            if (obj->trans.z <= 800.0f) {
                D_80111169_stacked_deck = 13;
            }
        } else if (D_8011116E_stacked_deck >= obj->work[1]) {
            if ((obj->work[1] - 1) * 140.0f < obj->trans.x) {
                D_800CBB6E_main[obj->work[3]] = -60;
            } else {
                obj->trans.x = (obj->work[1] - 1) * 140.0f;
                gw->unk3C = 180.0f;
            }
        }
        break;
    case 6:
        if (D_8010F720_stacked_deck >= 286) {
            func_80105B3C_stacked_deck(obj->work[0]);
        } else {
            if (obj->work[1] == 0) {
                if (GwPlayer[obj->work[0]].stat & 1) {
                    func_80105B3C_stacked_deck(obj->work[0]);
                    func_80106780_stacked_deck(obj);
                }
                func_801069A0_stacked_deck(obj);
                D_8011114A_stacked_deck = 0;
            } else if (D_8011116E_stacked_deck >= obj->work[1]) {
                func_80105B3C_stacked_deck(obj->work[0]);
                if ((obj->work[1] - 1) * 140.0f < obj->trans.x) {
                    D_800CBB6E_main[obj->work[3]] = -60;
                } else {
                    obj->trans.x = (obj->work[1] - 1) * 140.0f;
                    gw->unk3C = 180.0f;
                }
            }
            D_80111140_stacked_deck = 0;
        }
        break;
    case 7:
        if (obj->work[1] == 0) {
            for (i = 0; i < 12; i++) {
                e = &D_8010FA48_stacked_deck[i];
                o = e->obj;
                if (e->unk04 == 1) {
                    break;
                }
            }
            if (gw->unk50 == 0x80
                || (o->trans.x - 90.0f < obj->trans.x && obj->trans.x < o->trans.x + 90.0f
                    && o->trans.z - 135.0f < obj->trans.z && obj->trans.z < o->trans.z + 135.0f && e->unk04 == 1
                    && D_8011114A_stacked_deck == 0)) {
                func_800E5690_minigame(obj, 0);
                D_800D5558_main[obj->work[3]] |= 0x8000;
                D_8011114A_stacked_deck = 1;
            }
        }
        if (obj->work[1] == 0) {
            if (D_80111140_stacked_deck == 3) {
                D_80111140_stacked_deck = 4;
                func_8004AC98_main(0x445, obj->work[0]);
                gw->unk3C = 0.0f;
            } else {
                if (D_80111140_stacked_deck < 3) {
                    D_80111140_stacked_deck++;
                }
                gw->unk3C = 0.0f;
            }
            if (obj->trans.x >= -175.0f && obj->trans.x <= 175.0f) {
                if (obj->trans.x < -20.0f) {
                    D_800CBB6E_main[obj->work[3]] = 60;
                } else if (obj->trans.x > 20.0f) {
                    D_800CBB6E_main[obj->work[3]] = -60;
                }
            }
            if (obj->trans.x < -175.0f) {
                if (obj->trans.x < -370.0f) {
                    D_800CBB6E_main[obj->work[3]] = 60;
                } else if (obj->trans.x > -330.0f) {
                    D_800CBB6E_main[obj->work[3]] = -60;
                }
            }
            if (obj->trans.x > 175.0f) {
                if (obj->trans.x < 330.0f) {
                    D_800CBB6E_main[obj->work[3]] = 60;
                } else if (obj->trans.x > 370.0f) {
                    D_800CBB6E_main[obj->work[3]] = -60;
                }
            }
        } else if (D_8011116E_stacked_deck >= obj->work[1]) {
            if ((obj->work[1] - 1) * 140.0f < obj->trans.x) {
                D_800CBB6E_main[obj->work[3]] = -60;
            } else {
                obj->trans.x = (obj->work[1] - 1) * 140.0f;
                gw->unk3C = 180.0f;
            }
        }
        D_8010F6F2_stacked_deck = 0;
        break;
    case 8:
        if (obj->work[1] == 0) {
            switch (pl->unk08) {
            case 0:
                if (D_80110078_stacked_deck[0].unk04 == 2 && pl->unk06 != 39) {
                    func_800E5690_minigame(obj, 39);
                    pl->unk06 = 39;
                }
                if (pl->unk06 == 39) {
                    m = &HmfModelData[obj->model[0]];
                    if (D_800CCF58_main[m->unk02].unk02 <= m->unk40) {
                        pl->unk08 = 1;
                        pl->unk06 = 0;
                    }
                }
                break;
            case 1:
                if (D_8011116E_stacked_deck >= 2) {
                    func_801063F4_stacked_deck((D_8011116E_stacked_deck - 1) * 140.0f, 800.0f, obj->trans.x,
                                               obj->trans.z, &vx, &vz, 60.0f);
                    D_800CBB6E_main[obj->work[3]] = vx;
                    D_800D20A1_main[obj->work[3]] = -vz;
                    tx = (D_8011116E_stacked_deck - 1) * 140.0f;
                } else {
                    func_801063F4_stacked_deck(D_8011116E_stacked_deck * 140.0f, 800.0f, obj->trans.x, obj->trans.z,
                                               &vx, &vz, 60.0f);
                    D_800CBB6E_main[obj->work[3]] = vx;
                    D_800D20A1_main[obj->work[3]] = -vz;
                    tx = D_8011116E_stacked_deck * 140.0f;
                }
                if (tx - 10.0f < obj->trans.x && obj->trans.x < tx + 10.0f) {
                    pl->unk08 = 2;
                    gw->unk40 = 0.0f;
                    obj->trans.x = tx;
                }
                break;
            case 2:
                if (obj->trans.z < 1100.0f) {
                    D_800D20A1_main[obj->work[3]] = -60;
                } else {
                    obj->trans.z = 1100.0f;
                    if ((D_8011116E_stacked_deck - 1) * 140.0f < obj->trans.x) {
                        D_800CBB6E_main[obj->work[3]] = -60;
                    } else {
                        gw->unk40 = 0.0f;
                        obj->trans.x = (D_8011116E_stacked_deck - 1) * 140.0f;
                        if (gw->unk3C <= 200.0f && gw->unk3C >= 160.0f) {
                            if (pl->unk06 != 0) {
                                func_800E5690_minigame(obj, 2);
                                obj->motion[0] = obj->motion[43];
                                func_800E5690_minigame(obj, 0);
                                pl->unk06 = 0;
                            }
                            gw->unk3C = 180.0f;
                            if (D_80110078_stacked_deck[0].unk04 == 5) {
                                pl->unk08 = 0;
                                D_80111169_stacked_deck = 8;
                                D_80110078_stacked_deck[0].unk04 = 0;
                            }
                        } else {
                            gw->unk3C = func_801059BC_stacked_deck(gw->unk3C, -15.0f);
                            if (pl->unk06 != 2) {
                                func_800E5690_minigame(obj, 2);
                                obj->motion[43] = obj->motion[0];
                                obj->motion[0] = obj->motion[2];
                                pl->unk06 = 2;
                            }
                        }
                    }
                }
                break;
            }
        } else {
            i = 0;
            if (D_8011116E_stacked_deck >= obj->work[1]) {
                for (i = 0; i < 4; i++) {
                    o = D_8010F838_stacked_deck[i].obj;
                    if (o->work[1] == 0) {
                        break;
                    }
                }
                if (o->trans.x > 60.0f) {
                    if (obj->work[1] == 1) {
                        if (obj->trans.z > 800.0f) {
                            D_800D20A1_main[obj->work[3]] = 60;
                        }
                    } else if ((obj->work[1] - 2) * 140.0f < obj->trans.x) {
                        D_800CBB6E_main[obj->work[3]] = -60;
                    } else {
                        obj->trans.x = (obj->work[1] - 2) * 140.0f;
                        gw->unk3C = 180.0f;
                    }
                }
            }
        }
        if (obj->work[0] == 3 && D_80111169_stacked_deck == 8) {
            for (i = 0; i < 4; i++) {
                o = D_8010F838_stacked_deck[i].obj;
                if (o->work[1] == 0) {
                    o->work[1] = D_8011116E_stacked_deck;
                } else if (D_8011116E_stacked_deck >= o->work[1]) {
                    o->work[1]--;
                }
            }
        }
        break;
    case 9:
        if (obj->work[1] == 0) {
            switch (pl->unk08) {
            case 0:
                gw->unk3C = 0.0f;
                if (D_801100FC_stacked_deck.unk04 == 2 && pl->unk06 != 40) {
                    func_800E5690_minigame(obj, 40);
                    pl->unk06 = 40;
                }
                if (pl->unk06 == 40) {
                    m = &HmfModelData[obj->model[0]];
                    if (D_800CCF58_main[m->unk02].unk02 <= m->unk40) {
                        pl->unk08 = 1;
                        pl->unk06 = 0;
                        obj->motion[43] = obj->motion[2];
                        obj->motion[2] = obj->motion[42];
                        func_8004ACE0_main(0x286, obj->work[0]);
                    }
                }
                break;
            case 1:
                if (obj->trans.z < 800.0f) {
                    func_801063F4_stacked_deck(150.0f, 800.0f, obj->trans.x, obj->trans.z, &vx, &vz, 60.0f);
                } else {
                    func_801063F4_stacked_deck(150.0f, 1600.0f, obj->trans.x, obj->trans.z, &vx, &vz, 60.0f);
                }
                D_800CBB6E_main[obj->work[3]] = vx;
                D_800D20A1_main[obj->work[3]] = -vz;
                if (obj->trans.z > 1500.0f) {
                    obj->trans.z = 3000.0f;
                    obj->motion[2] = obj->motion[43];
                    pl->unk08 = 2;
                }
                break;
            case 2:
                pl->unk08 = 3;
                break;
            }
        } else if (D_8011116E_stacked_deck >= obj->work[1]) {
            switch (pl->unk08) {
            case 0:
                if (D_801100FC_stacked_deck.unk04 == 2 && pl->unk06 != 40) {
                    gw->unk3C = 180.0f;
                    func_800E5690_minigame(obj, 40);
                    pl->unk06 = 40;
                }
                if (pl->unk06 == 40) {
                    m = &HmfModelData[obj->model[0]];
                    if (D_800CCF58_main[m->unk02].unk02 <= m->unk40) {
                        pl->unk08 = 1;
                        pl->unk06 = 0;
                        obj->motion[43] = obj->motion[2];
                        obj->motion[2] = obj->motion[42];
                    }
                }
                break;
            case 1:
                for (i = 0; i < 4; i++) {
                    p = &D_8010F838_stacked_deck[i];
                    o = p->obj;
                    if (o->work[1] == 0) {
                        break;
                    }
                }
                if (p->unk08 == 1 && o->trans.z > 800.0f && o->trans.x > -150.0f && o->trans.x < 450.0f) {
                    r = (u8)(rand8() % 100);
                    switch (obj->work[1]) {
                    case 1:
                        pl->unk18 = -60.0f;
                        pl->unk1C = -r;
                        break;
                    case 2:
                        pl->unk18 = !(rand8() & 1) ? r : -r;
                        pl->unk1C = -60.0f;
                        break;
                    case 3:
                        pl->unk18 = 60.0f;
                        pl->unk1C = -r;
                        break;
                    }
                    pl->unk08 = 2;
                    func_8004ACE0_main(0x286, obj->work[0]);
                }
                break;
            case 2:
                D_800CBB6E_main[obj->work[3]] = pl->unk18;
                D_800D20A1_main[obj->work[3]] = pl->unk1C;
                if (obj->trans.z > 1500.0f || obj->trans.x < -1000.0f || obj->trans.x > 1000.0f) {
                    obj->trans.z = 3000.0f;
                    obj->motion[2] = obj->motion[43];
                    pl->unk08 = 3;
                }
                break;
            }
        }
        busy = 0;
        if (obj->work[0] == 3) {
            for (i = 0; i < 4; i++) {
                p = &D_8010F838_stacked_deck[i];
                if (p->unk08 != 3 && D_8011116E_stacked_deck >= p->obj->work[1]) {
                    busy = 1;
                }
            }
            if (busy == 0 && D_801100FC_stacked_deck.unk04 == 5) {
                for (i = 0; i < 4; i++) {
                    p = &D_8010F838_stacked_deck[i];
                    p->unk08 = 0;
                }
                D_80111169_stacked_deck = 9;
                D_801100FC_stacked_deck.unk04 = 0;
            }
        }
        break;
    case 10:
        if (D_8011116E_stacked_deck >= obj->work[1]) {
            switch (pl->unk08) {
            case 0:
                r = rand8() % (D_8011116E_stacked_deck + 1);
                for (;;) {
                    if (D_80111142_stacked_deck[r] == 0) {
                        break;
                    }
                    r = (r + 1 <= D_8011116E_stacked_deck) ? r + 1 : 0;
                }
                obj->work[1] = r;
                obj->trans.x = r * 140.0f;
                obj->trans.z = 1500.0f;
                pl->unk08 = 1;
                gw->unk40 = 0.0f;
                D_80111142_stacked_deck[r] = 1;
                break;
            case 1:
                if (obj->trans.z > 1100.0f) {
                    D_800D20A1_main[obj->work[3]] = 60;
                } else {
                    gw->unk40 = 0.0f;
                    obj->trans.z = 1100.0f;
                    pl->unk08 = 2;
                }
                break;
            }
        }
        busy = 0;
        if (obj->work[0] == 3) {
            for (i = 0; i < 4; i++) {
                p = &D_8010F838_stacked_deck[i];
                if (p->unk08 != 2 && D_8011116E_stacked_deck >= p->obj->work[1]) {
                    busy = 1;
                }
            }
            if (busy == 0) {
                for (i = 0; i < 4; i++) {
                    D_8010F838_stacked_deck[i].unk08 = 0;
                    D_80111142_stacked_deck[i] = 0;
                }
                D_80111169_stacked_deck = 10;
            }
        }
        break;
    case 11:
        if (obj->work[1] == 0) {
            o = D_80110180_stacked_deck.obj;
            switch (pl->unk08) {
            case 0:
                gw->unk40 = 0.0f;
                gw->unk3C = 0.0f;
                if (D_80110180_stacked_deck.unk04 == 2 && pl->unk06 != 41) {
                    func_800E5690_minigame(obj, 41);
                    pl->unk06 = 41;
                    pl->unk12 = D_8011116E_stacked_deck;
                }
                if (obj->trans.x < o->trans.x) {
                    pl->unk10 = 1;
                } else {
                    pl->unk10 = 2;
                }
                if (D_80110180_stacked_deck.unk04 >= 5) {
                    pl->unk08 = 1;
                    func_800E5690_minigame(obj, 18);
                    pl->unk06 = 18;
                    func_8001C6A8_main(obj->model[0], 0.0f);
                    func_8001C92C_main(obj->model[0], 0.0f);
                    pl->unk20 = 50.0f;
                    D_80111120_stacked_deck = 1;
                }
                break;
            case 1:
                if (D_8010F6F2_stacked_deck == 0) {
                    D_8010F6F2_stacked_deck = 1;
                    func_8004ACE0_main(0x286, obj->work[0]);
                    HuAudFXPlay(0x44A);
                }
                obj->trans.y = pl->unk24 = func_80106338_stacked_deck(pl->unk24, &pl->unk20, 0.05f);
                if (pl->unk10 == 1) {
                    obj->trans.x -= 20.0f;
                } else {
                    obj->trans.x += 20.0f;
                }
                obj->trans.z += 20.0f;
                obj->rot.y = func_801059BC_stacked_deck(obj->rot.y, 66.0f);
                obj->rot.x = func_801059BC_stacked_deck(obj->rot.x, 66.0f);
                if (obj->trans.y > 3000.0f) {
                    obj->trans.x = 3000.0f;
                    pl->unk08 = 2;
                    obj->trans.y = 0.0f;
                }
                break;
            case 2:
                if (D_80110180_stacked_deck.unk04 == 7) {
                    pl->unk08 = 0;
                    D_80111169_stacked_deck = 11;
                    D_80110180_stacked_deck.unk04 = 0;
                    pl->unk06 = 0;
                }
                break;
            }
        } else {
            i = 0;
            if (D_8011116E_stacked_deck >= obj->work[1]) {
                for (i = 0; i < 4; i++) {
                    p = &D_8010F838_stacked_deck[i];
                    o = p->obj;
                    if (o->work[1] == 0) {
                        break;
                    }
                }
                if (p->unk08 > 0) {
                    if (obj->work[1] == 1) {
                        if (obj->trans.z > 800.0f) {
                            D_800D20A1_main[obj->work[3]] = 60;
                        }
                    } else if ((obj->work[1] - 2) * 140.0f < obj->trans.x) {
                        D_800CBB6E_main[obj->work[3]] = -60;
                    } else {
                        obj->trans.x = (obj->work[1] - 2) * 140.0f;
                        gw->unk3C = 180.0f;
                    }
                }
            }
        }
        if (obj->work[0] == 3 && D_80111169_stacked_deck == 11) {
            for (i = 0; i < 4; i++) {
                o = D_8010F838_stacked_deck[i].obj;
                if (o->work[1] == 0) {
                    o->work[1] = 99;
                } else if (D_8011116E_stacked_deck >= o->work[1]) {
                    o->work[1]--;
                }
            }
            D_8011116E_stacked_deck--;
        }
        break;
    case 14:
    case 15:
        if (obj->work[1] == 0) {
            o = D_80110180_stacked_deck.obj;
            switch (pl->unk08) {
            case 0:
                gw->unk40 = 0.0f;
                gw->unk3C = 0.0f;
                if (D_80110180_stacked_deck.unk04 == 2 && pl->unk06 != 41) {
                    func_800E5690_minigame(obj, 41);
                    pl->unk06 = 41;
                    pl->unk12 = D_8011116E_stacked_deck;
                }
                if (obj->trans.x < o->trans.x) {
                    pl->unk10 = 1;
                } else {
                    pl->unk10 = 2;
                }
                if (D_80110180_stacked_deck.unk04 >= 5) {
                    pl->unk08 = 1;
                    func_800E5690_minigame(obj, 18);
                    pl->unk06 = 18;
                    func_8001C6A8_main(obj->model[0], 0.0f);
                    func_8001C92C_main(obj->model[0], 0.0f);
                    pl->unk20 = 50.0f;
                    D_80111120_stacked_deck = 1;
                    D_8011110A_stacked_deck = 1;
                }
                break;
            case 1:
                if (D_8010F6F2_stacked_deck == 0) {
                    D_8010F6F2_stacked_deck = 1;
                    func_8004ACE0_main(0x286, obj->work[0]);
                    HuAudFXPlay(0x44A);
                }
                obj->trans.y = pl->unk24 = func_80106338_stacked_deck(pl->unk24, &pl->unk20, 0.05f);
                if (pl->unk10 == 1) {
                    obj->trans.x -= 20.0f;
                } else {
                    obj->trans.x += 20.0f;
                }
                obj->trans.z += 20.0f;
                obj->rot.y = func_801059BC_stacked_deck(obj->rot.y, 66.0f);
                obj->rot.x = func_801059BC_stacked_deck(obj->rot.x, 66.0f);
                if (obj->trans.y > 3000.0f) {
                    obj->trans.x = 3000.0f;
                    pl->unk08 = 2;
                }
                break;
            }
        } else if (D_8011116E_stacked_deck >= obj->work[1]) {
            if (D_8010F6F4_stacked_deck == 15) {
                if (gw->unk3C <= 20.0f || gw->unk3C >= 340.0f) {
                    gw->unk3C = 0.0f;
                    func_800E5690_minigame(obj, 2);
                    obj->motion[0] = obj->motion[43];
                    func_800E5690_minigame(obj, 0);
                    pl->unk06 = 0;
                } else {
                    gw->unk3C = func_801059BC_stacked_deck(gw->unk3C, 15.0f);
                    if (pl->unk06 != 2) {
                        func_800E5690_minigame(obj, 2);
                        obj->motion[43] = obj->motion[0];
                        obj->motion[0] = obj->motion[2];
                        pl->unk06 = 2;
                    }
                }
            }
        }
        break;
    case 16:
    case 17:
        if (obj->work[1] == 0) {
            o = D_80110180_stacked_deck.obj;
            switch (pl->unk08) {
            case 0:
                gw->unk40 = 0.0f;
                gw->unk3C = 0.0f;
                if (D_80110180_stacked_deck.unk04 == 2 && pl->unk06 != 41) {
                    func_800E5690_minigame(obj, 41);
                    pl->unk06 = 41;
                    pl->unk12 = D_8011116E_stacked_deck;
                }
                if (obj->trans.x < o->trans.x) {
                    pl->unk10 = 1;
                } else {
                    pl->unk10 = 2;
                }
                if (D_80110180_stacked_deck.unk04 >= 5) {
                    pl->unk08 = 1;
                    func_800E5690_minigame(obj, 18);
                    pl->unk06 = 18;
                    func_8001C6A8_main(obj->model[0], 0.0f);
                    func_8001C92C_main(obj->model[0], 0.0f);
                    pl->unk20 = 50.0f;
                    D_80111120_stacked_deck = 1;
                    D_8011110A_stacked_deck = 1;
                }
                break;
            case 1:
                if (D_8010F6F2_stacked_deck == 0) {
                    D_8010F6F2_stacked_deck = 1;
                    func_8004ACE0_main(0x286, obj->work[0]);
                    HuAudFXPlay(0x44A);
                }
                obj->trans.y = pl->unk24 = func_80106338_stacked_deck(pl->unk24, &pl->unk20, 0.05f);
                if (pl->unk10 == 1) {
                    obj->trans.x -= 20.0f;
                } else {
                    obj->trans.x += 20.0f;
                }
                obj->trans.z += 20.0f;
                obj->rot.y = func_801059BC_stacked_deck(obj->rot.y, 66.0f);
                obj->rot.x = func_801059BC_stacked_deck(obj->rot.x, 66.0f);
                if (obj->trans.y > 3000.0f) {
                    obj->trans.x = 3000.0f;
                    pl->unk08 = 2;
                }
                break;
            case 2:
                if (D_80110180_stacked_deck.unk04 == 7) {
                    pl->unk08 = 0;
                    D_80111169_stacked_deck = 11;
                    D_80110180_stacked_deck.unk04 = 0;
                    pl->unk06 = 0;
                }
                break;
            }
        } else if (D_8011116E_stacked_deck >= obj->work[1]) {
            if (gw->unk3C <= 20.0f || gw->unk3C >= 340.0f) {
                gw->unk3C = 0.0f;
                if (pl->unk06 != 13 && D_8010F720_stacked_deck >= 0) {
                    obj->motion[0] = obj->motion[43];
                    func_800E5690_minigame(obj, 13);
                    pl->unk06 = 13;
                    pl->unk12 = 0;
                    func_80045ED0_main((D_8010F290_stacked_deck[GwPlayer[obj->work[0]].chr] << 16) | 0x30);
                }
            } else {
                gw->unk3C = func_801059BC_stacked_deck(gw->unk3C, 15.0f);
                if (pl->unk06 != 2) {
                    func_800E5690_minigame(obj, 2);
                    obj->motion[43] = obj->motion[0];
                    obj->motion[0] = obj->motion[2];
                    pl->unk06 = 2;
                }
            }
        }
        break;
    }
    if (D_8010F6F4_stacked_deck == 7) {
        D_800EB744_minigame = 1.7f;
    } else {
        D_800EB744_minigame = 1.3f;
    }
    if (D_8011116E_stacked_deck < obj->work[1]) {
        func_80105B3C_stacked_deck(obj->work[0]);
        gw->unk40 = 0.0f;
    }
    func_800DDD94_minigame(obj);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 1.0f, obj->trans.z);
    if (obj->trans.x >= 3000.0f) {
        obj->trans.y = obj->work[0] * 500.0f + 100.0f;
    }
    if (obj->trans.z < -500.0f) {
        obj->trans.z = -499.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106BC8_stacked_deck);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80108E48_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010969C_stacked_deck);

#define SK_LEFT(n) ((n) == 0 || (n) == 1 || (n) == 4 || (n) == 5 || (n) == 8 || (n) == 9)
#define SK_RIGHT(n) ((n) == 2 || (n) == 3 || (n) == 6 || (n) == 7 || (n) == 10 || (n) == 11)

#define SK_LEFT(n) ((n) == 0 || (n) == 1 || (n) == 4 || (n) == 5 || (n) == 8 || (n) == 9)
#define SK_RIGHT(n) ((n) == 2 || (n) == 3 || (n) == 6 || (n) == 7 || (n) == 10 || (n) == 11)

#define SK_LEFT(n) ((n) == 0 || (n) == 1 || (n) == 4 || (n) == 5 || (n) == 8 || (n) == 9)
#define SK_RIGHT(n) ((n) == 2 || (n) == 3 || (n) == 6 || (n) == 7 || (n) == 10 || (n) == 11)

#define SK_LEFT(n) ((n) == 0 || (n) == 1 || (n) == 4 || (n) == 5 || (n) == 8 || (n) == 9)
#define SK_RIGHT(n) ((n) == 2 || (n) == 3 || (n) == 6 || (n) == 7 || (n) == 10 || (n) == 11)

#define SK_LEFT(n) ((n) == 0 || (n) == 1 || (n) == 4 || (n) == 5 || (n) == 8 || (n) == 9)
#define SK_RIGHT(n) ((n) == 2 || (n) == 3 || (n) == 6 || (n) == 7 || (n) == 10 || (n) == 11)

#define SK_LEFT(n) ((n) == 0 || (n) == 1 || (n) == 4 || (n) == 5 || (n) == 8 || (n) == 9)
#define SK_RIGHT(n) ((n) == 2 || (n) == 3 || (n) == 6 || (n) == 7 || (n) == 10 || (n) == 11)

#ifdef NON_MATCHING
#define SK_LEFT(n) ((n) == 0 || (n) == 1 || (n) == 4 || (n) == 5 || (n) == 8 || (n) == 9)
#define SK_RIGHT(n) ((n) == 2 || (n) == 3 || (n) == 6 || (n) == 7 || (n) == 10 || (n) == 11)

void func_801097D4_stacked_deck(omObjData *obj) {
    CcEnt *ent;
    CcEnt *e;
    s16 i;
    s16 r;
    u8 busy;
    omObjData *o;
    f32 tz;

    ent = &D_8010FA48_stacked_deck[obj->work[0]];
    switch (D_8010F6F4_stacked_deck) {
    case 1:
        switch (ent->unk06) {
        case 0:
            for (i = 0; i < 12; i++) {
                if (D_80111128_stacked_deck[i] == 0) {
                    if (SK_LEFT(i)) {
                        obj->trans.x = -1200.0f;
                    } else {
                        obj->trans.x = 1200.0f;
                    }
                    obj->trans.y = (obj->work[0] + 1) * 2;
                    obj->trans.z = D_8010F2B0_stacked_deck[i].z;
                    ent->unk0A = i;
                    D_80111128_stacked_deck[i] = 1;
                    break;
                }
            }
            switch (D_8011116C_stacked_deck) {
            case 0:
                if (D_8011114E_stacked_deck < 6) {
                    func_80106354_stacked_deck(obj, 0);
                    obj->work[1] = 1;
                    D_8011116A_stacked_deck++;
                }
                if (D_8011114E_stacked_deck >= 6 && D_8011114E_stacked_deck < 8) {
                    func_80106354_stacked_deck(obj, 1);
                    obj->work[1] = 2;
                    D_80111100_stacked_deck++;
                }
                if (D_8011114E_stacked_deck >= 8) {
                    func_80106354_stacked_deck(obj, 2);
                    obj->work[1] = 3;
                    D_801110FA_stacked_deck++;
                }
                break;
            case 1:
                if (D_8011114E_stacked_deck < 4) {
                    func_80106354_stacked_deck(obj, 0);
                    obj->work[1] = 1;
                    D_8011116A_stacked_deck++;
                }
                if (D_8011114E_stacked_deck >= 4 && D_8011114E_stacked_deck < 7) {
                    func_80106354_stacked_deck(obj, 2);
                    obj->work[1] = 3;
                    D_801110FA_stacked_deck++;
                }
                if (D_8011114E_stacked_deck >= 7) {
                    func_80106354_stacked_deck(obj, 1);
                    obj->work[1] = 2;
                    D_80111100_stacked_deck++;
                }
                break;
            case 2:
                if (D_8011114E_stacked_deck < 3) {
                    func_80106354_stacked_deck(obj, 0);
                    obj->work[1] = 1;
                    D_8011116A_stacked_deck++;
                }
                if (D_8011114E_stacked_deck >= 3) {
                    func_80106354_stacked_deck(obj, 2);
                    obj->work[1] = 3;
                    D_801110FA_stacked_deck++;
                }
                break;
            case 3:
                if (D_8011114E_stacked_deck < 2) {
                    func_80106354_stacked_deck(obj, 0);
                    obj->work[1] = 1;
                    D_8011116A_stacked_deck++;
                }
                if (D_8011114E_stacked_deck >= 2) {
                    func_80106354_stacked_deck(obj, 2);
                    obj->work[1] = 3;
                    D_801110FA_stacked_deck++;
                }
                break;
            case 4:
                if (D_8011114E_stacked_deck < 1) {
                    func_80106354_stacked_deck(obj, 0);
                    obj->work[1] = 1;
                    D_8011116A_stacked_deck++;
                }
                if (D_8011114E_stacked_deck >= 1) {
                    func_80106354_stacked_deck(obj, 2);
                    obj->work[1] = 3;
                    D_801110FA_stacked_deck++;
                }
                break;
            }
            D_8011114E_stacked_deck++;
            func_8001C258_main(obj->model[0], 4, 0);
            func_8001C258_main(obj->model[1], 4, 0);
            func_8001C258_main(obj->model[2], 4, 0);
            ent->unk06 = 1;
            ent->unk08 = 1;
            break;
        case 1:
            if (SK_LEFT(ent->unk0A)) {
                if (obj->trans.x < D_8010F2B0_stacked_deck[ent->unk0A].x) {
                    obj->trans.x += 50.0f;
                } else {
                    obj->trans.x = D_8010F2B0_stacked_deck[ent->unk0A].x;
                    if (obj->trans.y > 0.0f) {
                        obj->trans.y -= 5.0f;
                    }
                    if (obj->trans.y < 0.0f) {
                        obj->trans.y = 0.0f;
                    }
                }
            } else {
                if (obj->trans.x > D_8010F2B0_stacked_deck[ent->unk0A].x) {
                    obj->trans.x -= 50.0f;
                } else {
                    obj->trans.x = D_8010F2B0_stacked_deck[ent->unk0A].x;
                    if (obj->trans.y > 0.0f) {
                        obj->trans.y -= 5.0f;
                    }
                    if (obj->trans.y < 0.0f) {
                        obj->trans.y = 0.0f;
                    }
                }
            }
            if (obj->work[0] == 11) {
                if (D_8011110C_stacked_deck == 0) {
                    HuAudFXPlay(0x447);
                    D_8011110C_stacked_deck = 1;
                }
                busy = 0;
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (o->trans.x != D_8010F2B0_stacked_deck[e->unk0A].x || o->trans.y != 0.0f) {
                        busy = 1;
                    }
                }
                if (!busy) {
                    D_80111169_stacked_deck = 1;
                    D_8011114E_stacked_deck = 0;
                    D_8011110C_stacked_deck = 0;
                }
            }
            break;
        }
        break;
    case 2:
        switch (ent->unk0C) {
        case 0:
            if (ent->unk08 == 1) {
                if (D_8011110C_stacked_deck == 0) {
                    HuAudFXPlay(0x44F);
                    D_8011110C_stacked_deck = 1;
                }
                if (ent->unk18 > 0.0f) {
                    ent->unk28 -= 0.02;
                } else if (ent->unk18 < 0.0f) {
                    ent->unk28 += 0.02;
                }
                ent->unk1C += 8.0f;
                obj->trans.y = func_80106338_stacked_deck(obj->trans.y, &ent->unk18, 1.0f);
                if (ent->unk1C > 180.0f) {
                    ent->unk1C = 180.0f;
                }
                if (obj->trans.y <= 0.0f) {
                    obj->trans.y = 0.0f;
                    ent->unk28 = 1.0f;
                    if (ent->unk10 < 255) {
                        if (D_8011110C_stacked_deck == 1) {
                            HuAudFXPlay(0x450);
                            D_8011110C_stacked_deck = 2;
                        }
                        ent->unk10 += 7;
                    } else {
                        ent->unk18 = 15.0f;
                        ent->unk0C = 1;
                    }
                }
                if (ent->unk1C < 90.0f) {
                    ent->unk24 -= 0.05f;
                    ent->unk0E -= 3;
                } else if (ent->unk1C > 90.0f) {
                    ent->unk24 += 0.05f;
                    ent->unk0E += 3;
                }
            } else {
                ent->unk0C = 1;
            }
            break;
        case 1:
            if (ent->unk08 == 1) {
                if (D_8011110C_stacked_deck == 2) {
                    HuAudFXPlay(0x44F);
                    D_8011110C_stacked_deck = 0;
                }
                if (ent->unk18 > 0.0f) {
                    ent->unk28 -= 0.02;
                } else if (ent->unk18 < 0.0f) {
                    ent->unk28 += 0.02;
                }
                ent->unk1C -= 8.0f;
                obj->trans.y = func_80106338_stacked_deck(obj->trans.y, &ent->unk18, 1.0f);
                if (ent->unk1C < 0.0f) {
                    ent->unk1C = 0.0f;
                }
                if (obj->trans.y <= 0.0f) {
                    obj->trans.y = 0.0f;
                    ent->unk28 = 1.0f;
                    ent->unk18 = 15.0f;
                }
                if (ent->unk1C > 90.0f) {
                    ent->unk24 -= 0.05f;
                    ent->unk0E -= 3;
                } else if (ent->unk1C < 90.0f) {
                    ent->unk24 += 0.05f;
                    ent->unk0E += 3;
                }
            }
            busy = 0;
            if (obj->work[0] == 11) {
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (e->unk0C != 1 || o->trans.y != 0.0f || e->unk1C != 0.0f) {
                        busy = 1;
                    }
                }
                if (!busy) {
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        e->unk0C = 2;
                        e->unk08 = 0;
                        e->unk0A = 0;
                        D_80111128_stacked_deck[i] = 0;
                    }
                }
            }
            break;
        case 2:
            if (obj->work[0] == 11 && D_8011110C_stacked_deck == 0) {
                D_8011110C_stacked_deck = 1;
                HuAudFXPlay(0x447);
            }
            if (obj->trans.y < (f32)((obj->work[0] + 1) * 2)) {
                obj->trans.y += 1.0f;
            } else {
                obj->trans.y = (obj->work[0] + 1) * 2;
                obj->trans.x = (D_8010F2B0_stacked_deck[0].x < obj->trans.x) ? obj->trans.x - 50.0f : D_8010F2B0_stacked_deck[0].x;
                if (D_8010F2B0_stacked_deck[0].z < obj->trans.z) {
                    obj->trans.z -= 50.0f;
                } else {
                    obj->trans.z = D_8010F2B0_stacked_deck[0].z;
                }
            }
            busy = 0;
            if (obj->work[0] == 11) {
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (e->unk0C != 2 || o->trans.x != D_8010F2B0_stacked_deck[0].x
                        || o->trans.z != D_8010F2B0_stacked_deck[0].z) {
                        busy = 1;
                    }
                }
                if (!busy) {
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        e->unk0C = 3;
                        D_8011110C_stacked_deck = 0;
                    }
                }
            }
            break;
        case 3:
            if (obj->work[0] == 11 && D_8011110C_stacked_deck == 0) {
                D_8011110C_stacked_deck = 1;
                HuAudFXPlay(0x448);
            }
            if (obj->trans.y == 2.0f) {
                D_8011114C_stacked_deck = (s16)obj->work[0];
                obj->trans.x = (D_8010F2B0_stacked_deck[1].x > obj->trans.x) ? obj->trans.x + 50.0f : D_8010F2B0_stacked_deck[1].x;
                if (D_8010F2B0_stacked_deck[1].z > obj->trans.z) {
                    obj->trans.z += 50.0f;
                } else {
                    obj->trans.z = D_8010F2B0_stacked_deck[1].z;
                }
                if (obj->trans.x == D_8010F2B0_stacked_deck[1].x && obj->trans.z == D_8010F2B0_stacked_deck[1].z) {
                    D_801110F8_stacked_deck++;
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        e->unk0C = 4;
                    }
                }
            }
            break;
        case 4:
            if (obj->work[0] != D_8011114C_stacked_deck) {
                obj->trans.y -= 2.0f;
                ent->unk0C = 5;
            } else if (obj->trans.y < 26.0f) {
                obj->trans.y += 5.0f;
            } else {
                obj->trans.y = 26.0f;
                obj->trans.x = (D_8010F2B0_stacked_deck[0].x < obj->trans.x) ? obj->trans.x - 50.0f : D_8010F2B0_stacked_deck[0].x;
                if (D_8010F2B0_stacked_deck[0].z < obj->trans.z) {
                    obj->trans.z -= 50.0f;
                } else {
                    obj->trans.z = D_8010F2B0_stacked_deck[0].z;
                }
                if (obj->trans.x == D_8010F2B0_stacked_deck[0].x && obj->trans.z == D_8010F2B0_stacked_deck[0].z) {
                    ent->unk0C = 5;
                }
            }
            break;
        case 5:
            busy = 0;
            if (obj->work[0] == 11) {
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (e->unk0C != 5 || o->trans.x != D_8010F2B0_stacked_deck[0].x
                        || o->trans.z != D_8010F2B0_stacked_deck[0].z) {
                        busy = 1;
                    }
                }
                if (!busy) {
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        if (D_801110F8_stacked_deck > 0) {
                            e->unk0C = 6;
                            if (i == 11) {
                                D_801110F8_stacked_deck = 0;
                            }
                            D_8011110C_stacked_deck = 0;
                        } else {
                            e->unk0C = 3;
                        }
                    }
                }
            }
            break;
        case 6:
            r = (u8)(rand8() % 12);
            for (;;) {
                if (D_80111128_stacked_deck[r] == 0) {
                    ent->unk0A = r;
                    D_80111128_stacked_deck[r] = 1;
                    ent->unk0C = 7;
                    break;
                }
                r++;
                if (r >= 12) {
                    r = 0;
                }
            }
            break;
        case 7:
            if (obj->work[0] == 11 && D_8011110C_stacked_deck == 0) {
                D_8011110C_stacked_deck = 1;
                HuAudFXPlay(0x449);
            }
            obj->trans.x = (D_8010F2B0_stacked_deck[ent->unk0A].x > obj->trans.x) ? obj->trans.x + 50.0f : D_8010F2B0_stacked_deck[ent->unk0A].x;
            obj->trans.z = (D_8010F2B0_stacked_deck[ent->unk0A].z > obj->trans.z) ? obj->trans.z + 50.0f : D_8010F2B0_stacked_deck[ent->unk0A].z;
            if (obj->trans.x == D_8010F2B0_stacked_deck[ent->unk0A].x
                && obj->trans.z == D_8010F2B0_stacked_deck[ent->unk0A].z) {
                if (obj->trans.y > 0.0f) {
                    obj->trans.y -= 5.0f;
                }
                if (obj->trans.y < 0.0f) {
                    obj->trans.y = 0.0f;
                }
            }
            busy = 0;
            if (obj->work[0] == 11) {
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (e->unk0C != 7 || o->trans.x != D_8010F2B0_stacked_deck[e->unk0A].x
                        || o->trans.z != D_8010F2B0_stacked_deck[e->unk0A].z || o->trans.y != 0.0f) {
                        busy = 1;
                    }
                }
                if (!busy) {
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        e->unk0C = 0;
                    }
                    D_80111169_stacked_deck = 2;
                }
            }
            break;
        }
        break;
    case 3:
        switch (ent->unk0C) {
        case 0:
            if (ent->unk08 == 1) {
                if (D_8011110C_stacked_deck == 0) {
                    HuAudFXPlay(0x44F);
                    D_8011110C_stacked_deck = 1;
                }
                if (ent->unk18 > 0.0f) {
                    ent->unk28 -= 0.02;
                } else if (ent->unk18 < 0.0f) {
                    ent->unk28 += 0.02;
                }
                ent->unk1C += 8.0f;
                obj->trans.y = func_80106338_stacked_deck(obj->trans.y, &ent->unk18, 1.0f);
                if (ent->unk1C > 180.0f) {
                    ent->unk1C = 180.0f;
                }
                if (obj->trans.y <= 0.0f) {
                    obj->trans.y = 0.0f;
                    ent->unk28 = 1.0f;
                    if (ent->unk10 < 255) {
                        if (D_8011110C_stacked_deck == 1) {
                            HuAudFXPlay(0x450);
                            D_8011110C_stacked_deck = 2;
                        }
                        ent->unk10 += 7;
                    } else {
                        ent->unk18 = 15.0f;
                        ent->unk0C = 1;
                    }
                }
                if (ent->unk1C < 90.0f) {
                    ent->unk24 -= 0.05f;
                    ent->unk0E -= 3;
                } else if (ent->unk1C > 90.0f) {
                    ent->unk24 += 0.05f;
                    ent->unk0E += 3;
                }
            } else {
                ent->unk0C = 1;
            }
            break;
        case 1:
            if (ent->unk08 == 1) {
                if (D_8011110C_stacked_deck == 2) {
                    HuAudFXPlay(0x44F);
                    D_8011110C_stacked_deck = 0;
                }
                if (ent->unk18 > 0.0f) {
                    ent->unk28 -= 0.02;
                } else if (ent->unk18 < 0.0f) {
                    ent->unk28 += 0.02;
                }
                ent->unk1C -= 8.0f;
                obj->trans.y = func_80106338_stacked_deck(obj->trans.y, &ent->unk18, 1.0f);
                if (ent->unk1C < 0.0f) {
                    ent->unk1C = 0.0f;
                }
                if (obj->trans.y <= 0.0f) {
                    obj->trans.y = 0.0f;
                    ent->unk28 = 1.0f;
                    ent->unk18 = 15.0f;
                }
                if (ent->unk1C > 90.0f) {
                    ent->unk24 -= 0.05f;
                    ent->unk0E -= 3;
                } else if (ent->unk1C < 90.0f) {
                    ent->unk24 += 0.05f;
                    ent->unk0E += 3;
                }
            }
            busy = 0;
            if (obj->work[0] == 11) {
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (e->unk0C != 1 || o->trans.y != 0.0f || e->unk1C != 0.0f) {
                        busy = 1;
                    }
                }
                if (!busy) {
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        e->unk0C = 2;
                        e->unk08 = 0;
                        D_80111128_stacked_deck[i] = 0;
                    }
                }
            }
            break;
        case 2:
            if (obj->work[0] == 11 && D_8011110C_stacked_deck == 0) {
                D_8011110C_stacked_deck = 1;
                HuAudFXPlay(0x447);
            }
            if (obj->trans.y < (f32)((obj->work[0] + 1) * 2)) {
                obj->trans.y += 1.0f;
            } else {
                obj->trans.y = (obj->work[0] + 1) * 2;
                if (SK_LEFT(ent->unk0A)) {
                    obj->trans.x = (D_8010F2B0_stacked_deck[5].x > obj->trans.x) ? obj->trans.x + 40.0f : D_8010F2B0_stacked_deck[5].x;
                    if (D_8010F2B0_stacked_deck[5].z < obj->trans.z) {
                        obj->trans.z -= 40.0f;
                    } else if (D_8010F2B0_stacked_deck[5].z > obj->trans.z) {
                        obj->trans.z += 40.0f;
                    }
                    tz = D_8010F2B0_stacked_deck[5].z;
                } else {
                    obj->trans.x = (D_8010F2B0_stacked_deck[6].x < obj->trans.x) ? obj->trans.x - 40.0f : D_8010F2B0_stacked_deck[6].x;
                    if (D_8010F2B0_stacked_deck[6].z < obj->trans.z) {
                        obj->trans.z -= 40.0f;
                    } else if (D_8010F2B0_stacked_deck[6].z > obj->trans.z) {
                        obj->trans.z += 40.0f;
                    }
                    tz = D_8010F2B0_stacked_deck[6].z;
                }
                if (tz - 30.0f < obj->trans.z && obj->trans.z < tz + 30.0f) {
                    obj->trans.z = tz;
                }
            }
            busy = 0;
            if (obj->work[0] == 11) {
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (SK_LEFT(e->unk0A)) {
                        if (e->unk0C != 2 || o->trans.x != D_8010F2B0_stacked_deck[5].x
                            || o->trans.z != D_8010F2B0_stacked_deck[5].z) {
                            busy = 1;
                        }
                    } else {
                        if (e->unk0C != 2 || o->trans.x != D_8010F2B0_stacked_deck[6].x
                            || o->trans.z != D_8010F2B0_stacked_deck[6].z) {
                            busy = 1;
                        }
                    }
                }
                if (!busy) {
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        e->unk0C = 3;
                        D_8011110C_stacked_deck = 0;
                        if (SK_LEFT(e->unk0A)) {
                            e->unk0A = 5;
                        } else {
                            e->unk0A = 6;
                        }
                    }
                }
            }
            break;
        case 3:
            if (obj->work[0] == 11 && D_8011110C_stacked_deck == 0) {
                D_8011110C_stacked_deck = 1;
                HuAudFXPlay(0x448);
            }
            if (ent->unk0A == 5) {
                obj->trans.x = (D_8010F2B0_stacked_deck[6].x > obj->trans.x) ? obj->trans.x + 40.0f : D_8010F2B0_stacked_deck[6].x;
            }
            busy = 0;
            if (obj->work[0] == 11) {
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (e->unk0C != 3 || o->trans.x != D_8010F2B0_stacked_deck[6].x) {
                        busy = 1;
                    }
                }
                if (!busy) {
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        e->unk0C = 4;
                    }
                }
            }
            break;
        case 4:
            if (ent->unk0A == 6) {
                obj->trans.x = (D_8010F2B0_stacked_deck[5].x < obj->trans.x) ? obj->trans.x - 40.0f : D_8010F2B0_stacked_deck[5].x;
            }
            busy = 0;
            if (obj->work[0] == 11) {
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (e->unk0A == 6 && (e->unk0C != 4 || o->trans.x != D_8010F2B0_stacked_deck[5].x)) {
                        busy = 1;
                    }
                }
                if (!busy) {
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        e->unk0C = 7;
                        D_8011110C_stacked_deck = 0;
                    }
                }
            }
            break;
        case 7:
            r = (u8)(rand8() % 12);
            if (ent->unk0A == 5) {
                for (;;) {
                    if (SK_LEFT(r) && D_80111128_stacked_deck[r] == 0) {
                        break;
                    }
                    r++;
                    if (r >= 12) {
                        r = 0;
                    }
                }
                ent->unk0A = r;
            } else {
                for (;;) {
                    if (SK_RIGHT(r) && D_80111128_stacked_deck[r] == 0) {
                        break;
                    }
                    r++;
                    if (r >= 12) {
                        r = 0;
                    }
                }
                ent->unk0A = r;
            }
            D_80111128_stacked_deck[r] = 1;
            ent->unk0C = 8;
            break;
        case 8:
            if (obj->work[0] == 11 && D_8011110C_stacked_deck == 0) {
                D_8011110C_stacked_deck = 1;
                HuAudFXPlay(0x449);
            }
            if (D_8010F2B0_stacked_deck[ent->unk0A].x < obj->trans.x) {
                obj->trans.x -= 40.0f;
            } else if (D_8010F2B0_stacked_deck[ent->unk0A].x > obj->trans.x) {
                obj->trans.x += 40.0f;
            }
            if (D_8010F2B0_stacked_deck[ent->unk0A].x - 30.0f < obj->trans.x
                && obj->trans.x < D_8010F2B0_stacked_deck[ent->unk0A].x + 30.0f) {
                obj->trans.x = D_8010F2B0_stacked_deck[ent->unk0A].x;
            }
            if (D_8010F2B0_stacked_deck[ent->unk0A].z < obj->trans.z) {
                obj->trans.z -= 40.0f;
            } else if (D_8010F2B0_stacked_deck[ent->unk0A].z > obj->trans.z) {
                obj->trans.z += 40.0f;
            }
            if (D_8010F2B0_stacked_deck[ent->unk0A].z - 30.0f < obj->trans.z
                && obj->trans.z < D_8010F2B0_stacked_deck[ent->unk0A].z + 30.0f) {
                obj->trans.z = D_8010F2B0_stacked_deck[ent->unk0A].z;
            }
            if (obj->trans.x == D_8010F2B0_stacked_deck[ent->unk0A].x
                && obj->trans.z == D_8010F2B0_stacked_deck[ent->unk0A].z) {
                if (obj->trans.y > 0.0f) {
                    obj->trans.y -= 5.0f;
                }
                if (obj->trans.y < 0.0f) {
                    obj->trans.y = 0.0f;
                }
            }
            busy = 0;
            if (obj->work[0] == 11) {
                for (i = 0; i < 12; i++) {
                    e = &D_8010FA48_stacked_deck[i];
                    o = e->obj;
                    if (e->unk0C != 8 || o->trans.x != D_8010F2B0_stacked_deck[e->unk0A].x
                        || o->trans.z != D_8010F2B0_stacked_deck[e->unk0A].z || o->trans.y != 0.0f) {
                        busy = 1;
                    }
                }
                if (!busy) {
                    for (i = 0; i < 12; i++) {
                        e = &D_8010FA48_stacked_deck[i];
                        e->unk0C = 0;
                    }
                    D_80111169_stacked_deck = 3;
                }
            }
            break;
        }
        break;
    case 7:
        if (D_8010F6F0_stacked_deck == 4 && ent->unk06 == 1) {
            if (ent->unk04 == 0 && obj->work[1] == 3) {
                ent->unk04 = 1;
                D_8010F6F0_stacked_deck = 3;
            }
        } else if (*(s32 *)&ent->unk04 == 0x10001) {
            if (ent->unk18 > 0.0f) {
                ent->unk28 -= 0.02;
            } else if (ent->unk18 < 0.0f) {
                ent->unk28 += 0.02;
            }
            obj->trans.y = func_80106338_stacked_deck(obj->trans.y, &ent->unk18, 1.0f);
            ent->unk1C += 45.0f;
            if (ent->unk1C > 900.0f) {
                ent->unk1C = 900.0f;
            }
            if (ent->unk18 > 0.0f) {
                ent->unk24 -= 0.05f;
                ent->unk0E -= 3;
            } else if (ent->unk18 < 0.0f) {
                ent->unk24 += 0.05f;
                ent->unk0E += 3;
            }
            if (obj->trans.y <= 0.0f) {
                obj->trans.y = 0.0f;
                func_8001C258_main(obj->model[1], 4, 4);
                ent->unk28 = 1.0f;
                switch (obj->work[1]) {
                case 1:
                    func_80106354_stacked_deck(obj, 3);
                    break;
                case 2:
                    func_80106354_stacked_deck(obj, 4);
                    break;
                case 3:
                    func_80106354_stacked_deck(obj, 5);
                    break;
                }
                if (++ent->unk12 >= 7) {
                    ent->unk12 = 0;
                    D_80111169_stacked_deck = 7;
                }
            }
        }
        break;
    case 8:
    case 9:
    case 11:
    case 12:
    case 14:
    case 15:
    case 16:
    case 17:
        if (ent->unk04 == 1) {
            ent->unk20 -= 0.02f;
            ent->unk24 -= 0.02f;
            ent->unk28 -= 0.02f;
            ent->unk10 -= 15;
            if (ent->unk20 < 0.1f) {
                ent->unk20 = 0.1f;
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[2], 4, 4);
                ent->unk04 = 0;
                ent->unk06 = 0;
                D_80111128_stacked_deck[ent->unk0A] = 0;
                ent->unk0A = 0;
                ent->unk18 = 15.0f;
                ent->unk1C = 0.0f;
                ent->unk0E = 150;
                ent->unk10 = 0;
                ent->unk20 = 1.0f;
                ent->unk24 = 1.0f;
                ent->unk28 = 1.0f;
            }
        }
        break;
    }
    if (ent->unk0E < 0) {
        ent->unk0E = 0;
    }
    if (ent->unk0E > 150) {
        ent->unk0E = 150;
    }
    func_8001F9E4_main(obj->model[1], ent->unk0E);
    if (ent->unk10 < 0) {
        ent->unk10 = 0;
    }
    if (ent->unk10 > 255) {
        ent->unk10 = 255;
    }
    func_8001F9E4_main(obj->model[2], ent->unk10);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = func_801059BC_stacked_deck(ent->unk1C, 0.0f);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[2], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->scale.x = ent->unk20;
    obj->scale.y = ent->unk20;
    obj->scale.z = ent->unk20;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    if (ent->unk24 < 0.1f) {
        ent->unk24 = 0.1f;
    }
    if (ent->unk24 > 1.0f) {
        ent->unk24 = 1.0f;
    }
    Hu3DModelScaleSet(obj->model[1], ent->unk24, obj->scale.y, ent->unk28);
    Hu3DModelScaleSet(obj->model[2], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    ent->unk2C = 10.0f;
    if (obj->trans.z < -100.0f) {
        ent->unk30 = 40.0f;
    } else if (obj->trans.z < 400.0f) {
        ent->unk30 = 35.0f;
    } else {
        ent->unk30 = 30.0f;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x + ent->unk2C, -4.0f, obj->trans.z + ent->unk30);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801097D4_stacked_deck);
#endif

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

void func_8010DAE4_stacked_deck(omObjData *obj) {
    void *data;
    s32 spr;

    data = DataRead(0xB);
    spr = HmfSprModelCreate(data, 0x2A0, 8);
    DataClose(data);
    obj->model[0] = D_800CBB60_main[(u16)spr].unk00;
    D_80110208_stacked_deck = spr;
    func_800146DC_main(spr, 1, 1);
    func_800147FC_main(D_80110208_stacked_deck, 200, 200, 200);
    func_80014794_main(D_80110208_stacked_deck, 255);
    func_80014714_main(D_80110208_stacked_deck, 14);
    obj->scale.x = obj->scale.y = obj->scale.z = 10.0f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    obj->func = func_8010D98C_stacked_deck;
}

void func_8010DBF4_stacked_deck(void) {
    omAddObj(580, 1, 0, -1, func_8010DAE4_stacked_deck)->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DC2C_stacked_deck);

void func_8010DDAC_stacked_deck(omObjData *obj) {
    void *data;
    s32 spr;

    data = DataRead(0x4B0001);
    spr = HmfSprModelCreate(data, 0x2A0, 8);
    DataClose(data);
    obj->model[0] = D_800CBB60_main[(u16)spr].unk00;
    D_8011028C_stacked_deck = spr;
    func_800146DC_main(spr, 2, 0);
    func_80014714_main(D_8011028C_stacked_deck, 0);
    func_8001C92C_main(obj->model[0], 3.0f);
    obj->scale.x = obj->scale.y = obj->scale.z = 5.0f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->func = func_8010DC2C_stacked_deck;
}

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

void func_8010E650_stacked_deck(omObjData *obj) {
    s16 i;

    for (i = 0; i < 6; i++) {
        DataClose(D_8010F708_stacked_deck[i]);
    }
    for (i = 0; i < 12; i++) {
        func_80033354_main(D_80111150_stacked_deck[i]);
    }
    osViBlack(0);
    omOvlReturnEx(1);
}

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

void func_8010EFC4_stacked_deck(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010F360_stacked_deck[i].scissor[0], D_8010F360_stacked_deck[i].scissor[1],
                   D_8010F360_stacked_deck[i].scissor[2], D_8010F360_stacked_deck[i].scissor[3]);
        ViewportSet(i, D_8010F360_stacked_deck[i].viewport[0], D_8010F360_stacked_deck[i].viewport[1],
                    D_8010F360_stacked_deck[i].viewport[2], D_8010F360_stacked_deck[i].viewport[3],
                    D_8010F360_stacked_deck[i].viewport[4], D_8010F360_stacked_deck[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010F360_stacked_deck[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010F134_stacked_deck(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010EFC4_stacked_deck();
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
    func_80045010_main(D_8010F6E8_stacked_deck, 0);
    func_80045010_main(D_8010F6E8_stacked_deck, 1);
    omAddObj(1000, 0, 0, -1, func_8010ED44_stacked_deck);
    omAddObj(1000, 0, 0, -1, func_8010E734_stacked_deck);
    func_80105A74_stacked_deck();
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct *)&D_8010F334_stacked_deck);
}

const s16 D_8010F6E8_stacked_deck[] = { 0x8260, 0x8261, 0x8262, 0 };

