#include "common.h"
// m3 es: Eye Sore (four players dodge the eye beams of the Mr. I's on the stage)
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
#include "game/util.h"
#include "game/wipe.h"
#include "math.h"

/* One slot of the overlay's object table (D_8010AF70_eye_sore, 50 x 0x84):
 * [0] the background, [5..8] the players, [10..13] the player rings, [15..22] the eyes. */
typedef struct EsEnt {
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
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ Vec unk44;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} EsEnt; // Size 0x84

#define ES_ENT_BG 0
#define ES_ENT_PLAYER 5
#define ES_ENT_RING 10
#define ES_ENT_EYE 15

/* A player's state (D_8010CA60_eye_sore, 4 x 0x54). */
typedef struct EsPlayer {
    /* 0x00 */ s8 cpu;
    /* 0x01 */ s8 dif;
    /* 0x02 */ s8 state;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ s8 unk0C;
    /* 0x0D */ s8 unk0D;
    /* 0x0E */ s8 unk0E;
    /* 0x0F */ u8 timer;
    /* 0x10 */ s8 unk10;
    /* 0x11 */ s8 unk11;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ s8 rank;
    /* 0x14 */ s8 lap[16];
    /* 0x24 */ f32 dist;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 rot;
    /* 0x4C */ s8 eye;
    /* 0x50 */ omObjData *obj;
} EsPlayer; // Size 0x54

/* An eye (D_8010C938_eye_sore, 0x18 each). */
typedef struct EsEye {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ s8 unk10;
    /* 0x11 */ s8 unk11;
    /* 0x14 */ omObjData *obj;
} EsEye; // Size 0x18

/* A player's ring (D_8010CBC0_eye_sore, 4 x 0x14). */
typedef struct EsRing {
    /* 0x00 */ s8 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ s8 unk0C;
    /* 0x0D */ s8 unk0D;
    /* 0x10 */ omObjData *obj;
} EsRing; // Size 0x14

/* A camera (D_8010ACF4_eye_sore). */
typedef struct EsCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} EsCamera; // Size 0x2C

extern s32 D_800A178C_main[][6];
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u16 D_800D530C_main;

void func_8000B5F0_main(u8 arg0);
s32 func_8000B710_main(s32 arg0);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8004AB0C_main(s32);
void func_80033354_main(s16);
void func_8003F578_main(s16);
void func_8003F5C0_main(void);
void func_80045010_main(const s16 *, s32);
void func_80088800_main(HuMtx4F mf, f32 x, f32 y, f32 z);

/* .data */
extern s32 D_8010AC10_eye_sore[8];
extern s16 D_8010AC30_eye_sore[4];
extern s8 D_8010AC38_eye_sore[24];
extern u8 D_8010AC50_eye_sore[4];
extern u8 D_8010AC54_eye_sore[4];
extern u16 D_8010AC58_eye_sore[8][2];
extern u8 D_8010AC98_eye_sore[8];
extern f32 D_8010ACA0_eye_sore[20];
extern s8 D_8010ACF0_eye_sore[4];
extern char *D_8010AC78_eye_sore[8];
extern s32 D_8010ACF4_eye_sore;
extern EsCamera D_8010ACF8_eye_sore[4];

/* .bss */
extern s8 D_8010AF20_eye_sore;
extern s16 D_8010AF22_eye_sore[4];
extern f32 D_8010AF30_eye_sore[15];
extern u8 D_8010AF6C_eye_sore;
extern EsEnt D_8010AF70_eye_sore[50];
extern EsEye D_8010C938_eye_sore[12];
extern s16 D_8010CA58_eye_sore;
extern s8 D_8010CA5A_eye_sore;
extern EsPlayer D_8010CA60_eye_sore[4];
extern s16 D_8010CBB0_eye_sore;
extern u16 D_8010CBB2_eye_sore;
extern s16 D_8010CBB4_eye_sore;
extern s16 D_8010CBB6_eye_sore;
extern u16 D_8010CBB8_eye_sore;
extern EsRing D_8010CBC0_eye_sore[4];
extern s8 D_8010CC10_eye_sore;
extern s8 D_8010CC11_eye_sore;
extern void *D_8010CC18_eye_sore[4][2];
extern const s16 D_8010AF0C_eye_sore[];

f32 func_801059BC_eye_sore(f32 angle, f32 add);
u8 func_80105A3C_eye_sore(s32 max);
void func_80105A74_eye_sore(void);
void func_80105B3C_eye_sore(s32 player);
void func_80105BB4_eye_sore(f32 x0, f32 z0, f32 x1, f32 z1);
s32 func_80105CE4_eye_sore(s32 max);
void func_80105D38_eye_sore(omObjData *obj, u16 motion, s16 attr);
void func_80105DA0_eye_sore(omObjData *obj, u16 motion, s16 start, s16 end, s16 attr);
void func_80105E0C_eye_sore(f32 x0, f32 z0, f32 x1, f32 z1, f32 *dx, f32 *dz, f32 *rot, f32 max);
s8 func_80105F40_eye_sore(omObjData *obj, f32 rot);
void func_80106054_eye_sore(omObjData *obj);
void func_8010605C_eye_sore(omObjData *obj);
void func_80106210_eye_sore(void);
void func_80106250_eye_sore(omObjData *obj, u8 anim);
void func_80106328_eye_sore(omObjData *obj, s8 sfx);
void func_801063E8_eye_sore(omObjData *obj, s8 motion);
void func_80106510_eye_sore(omObjData *obj);
void func_80106718_eye_sore(omObjData *obj);
void func_8010683C_eye_sore(omObjData *obj);
void func_801070CC_eye_sore(omObjData *obj);
void func_8010725C_eye_sore(omObjData *obj);
void func_80107804_eye_sore(omObjData *obj);
void func_80107CBC_eye_sore(omObjData *obj);
void func_80108330_eye_sore(omObjData *obj);
void func_80108AAC_eye_sore(void);
void func_80108BBC_eye_sore(void);
void func_80108D3C_eye_sore(void);
void func_80108E8C_eye_sore(omObjData *obj);
void func_80109478_eye_sore(omObjData *obj);
void func_80109854_eye_sore(void);
void func_801098F8_eye_sore(omObjData *obj);
void func_8010A0CC_eye_sore(omObjData *obj);
void func_8010A3C0_eye_sore(void);
void func_8010A464_eye_sore(void);
void func_8010A528_eye_sore(omObjData *obj);
void func_8010A54C_eye_sore(omObjData *obj);
void func_8010A62C_eye_sore(omObjData *obj);
void func_8010A684_eye_sore(omObjData *obj);
void func_8010A8EC_eye_sore(omObjData *obj);
void func_8010A97C_eye_sore(omObjData *obj);
void func_8010A984_eye_sore(void);
void func_8010AAF8_eye_sore(void);

/* The slot `i` of the object table's group starting at `base` (ES_ENT_*). */
#define ES_ENT(base, i) (&(D_8010AF70_eye_sore + (base))[i])

void func_801059A0_eye_sore(void) {
    func_8010AAF8_eye_sore();
}

f32 func_801059BC_eye_sore(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

u8 func_80105A3C_eye_sore(s32 max) {
    return ((u32)(rand8() * max)) >> 8;
}

void func_80105A74_eye_sore(void) {
    u32 i;
    EsEnt *ent;

    for (i = 0, ent = D_8010AF70_eye_sore; i < 50; i++, ent++) {
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
        ent->unk40 = -1;
        ent->unk42 = -1;
        ent->unk44.x = ent->unk44.y = ent->unk44.z = 0.0f;
        ent->unk50.x = ent->unk50.y = ent->unk50.z = 0.0f;
        ent->unk5C.x = ent->unk5C.y = ent->unk5C.z = 0.0f;
        ent->unk68 = 0.0f;
        ent->unk6C = 0.0f;
        ent->unk70 = 0.0f;
        ent->unk74 = 0.0f;
        ent->unk78.x = ent->unk78.y = ent->unk78.z = 0.0f;
    }
}

void func_80105B3C_eye_sore(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105BB4_eye_sore(f32 x0, f32 z0, f32 x1, f32 z1) {
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
    rot = func_801059BC_eye_sore(atan2df(dx, dz), 0.0f);
    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

s32 func_80105CE4_eye_sore(s32 max) {
    return rand8() % max;
}

void func_80105D38_eye_sore(omObjData *obj, u16 motion, s16 attr) {
    func_8001C5B4_main(obj->model[0], obj->motion[motion]);
    func_8001C814_main(obj->model[0], attr, attr);
}

void func_80105DA0_eye_sore(omObjData *obj, u16 motion, s16 start, s16 end, s16 attr) {
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[motion]].unk02, start, end, attr);
}

void func_80105E0C_eye_sore(f32 x0, f32 z0, f32 x1, f32 z1, f32 *dx, f32 *dz, f32 *rot, f32 max) {
    f32 x = x0 - x1;
    f32 z = z0 - z1;
    f32 dist = sqrtf(x * x + z * z);
    f32 div;

    if (dist == 0.0f) {
        *dx = 0.0f;
        *dz = 0.0f;
        return;
    }
    if (dist <= max) {
        *dx = x;
        *dz = z;
    } else {
        div = dist / max;
        if (x != 0.0f) {
            *dx = x / div;
        } else {
            *dx = 0.0f;
        }
        if (z != 0.0f) {
            *dz = z / div;
        } else {
            *dz = 0.0f;
        }
    }
    *rot = atan2df(x, z);
}

s8 func_80105F40_eye_sore(omObjData *obj, f32 rot) {
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
            obj->rot.y = func_801059BC_eye_sore(obj->rot.y, -10.0f);
        } else {
            obj->rot.y = func_801059BC_eye_sore(obj->rot.y, 10.0f);
        }
        return 1;
    }
    if (rot < cur) {
        if (diff > 180.0f) {
            obj->rot.y = func_801059BC_eye_sore(obj->rot.y, 10.0f);
        } else {
            obj->rot.y = func_801059BC_eye_sore(obj->rot.y, -10.0f);
        }
        return 1;
    }
    return 0;
}

void func_80106054_eye_sore(omObjData *obj) {
}

void func_8010605C_eye_sore(omObjData *obj) {
    EsEnt *ent = &D_8010AF70_eye_sore[ES_ENT_BG];

    obj->model[0] = func_8000B108_main(0x510000, 0x2B9);
    obj->model[1] = func_8000B108_main(0x510001, 0x2B9);
    func_8001C814_main(obj->model[1], 2, 2);
    ent->unk44.x = 160.0f;
    ent->unk44.y = 120.0f;
    ent->unk40 = func_8000B838_main(0x510004);
    ent->unk42 = InitEspriteSlot(ent->unk40, 0, 0);
    func_8000BC48_main(ent->unk42, 0x1000);
    func_8000BBD4_main(ent->unk42, ent->unk44.x, ent->unk44.y);
    ent->unk44.x = 160.0f;
    ent->unk44.y = 120.0f;
    ent->unk40 = func_8000B838_main(0x510005);
    ent->unk42 = InitEspriteSlot(ent->unk40, 0, 0);
    func_8000BC48_main(ent->unk42, 0x1000);
    func_8000BBD4_main(ent->unk42, ent->unk44.x, ent->unk44.y);
    obj->func = func_80106054_eye_sore;
}

void func_80106210_eye_sore(void) {
    omObjData *obj = omAddObj(500, 3, 3, -1, func_8010605C_eye_sore);

    obj->work[0] = 0;
    D_8010AF70_eye_sore[ES_ENT_BG].obj = obj;
}

void func_80106250_eye_sore(omObjData *obj, u8 anim) {
    u8 player = obj->work[0];
    u8 chr = GwPlayer[player].chr;

    func_80033354_main(D_8010AF22_eye_sore[player]);
    D_8010AF22_eye_sore[player] = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010CC18_eye_sore[player][anim], 0,
                         D_8010AC78_eye_sore[chr]);
}

void func_80106328_eye_sore(omObjData *obj, s8 sfx) {
    EsEnt *ent = ES_ENT(ES_ENT_PLAYER, obj->work[0]);

    if (obj->work[2] == 0) {
        if (ent->unk14 != 0) {
            HuAudFXStop(ent->unk14);
        }
        ent->unk14 = func_8004ACE0_main(D_8010AC30_eye_sore[sfx], (s16)obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 11;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADC8_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADD4_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADE0_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADEC_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADF8_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AE04_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AE10_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AE1C_eye_sore);

void func_801063E8_eye_sore(omObjData *obj, s8 motion) {
    s16 attr;
    s32 player = obj->work[0];
    s8 chr = GwPlayer[player].chr;
    EsEnt *ent = ES_ENT(ES_ENT_PLAYER, player);

    if (ent->unk06 != motion) {
        switch (motion) {
        case 4:
        case 7:
        case 8:
            attr = 0;
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        default:
            attr = 2;
            break;
        }
        func_8001C92C_main(obj->model[0], 1.0f);
        func_80105DA0_eye_sore(obj, motion, 0, 10, attr);
        ent->unk06 = motion;
        if (motion == 7) {
            func_80045ED0_main((D_8010AC10_eye_sore[chr] << 16) | 0x2F);
        }
    }
}

void func_80106510_eye_sore(omObjData *obj) {
    u8 pad = obj->work[3];
    s16 x = D_800CBB6E_main[pad];
    s16 y = -D_800D20A1_main[pad];
    f32 mag;
    f32 speed;
    f32 rot;

    if (x != 0 || y != 0) {
        mag = sqrtf(x * x + y * y);
        if (mag >= 70.0f) {
            speed = 25.0f;
        } else {
            speed = mag * 0.357;
        }
        rot = func_801059BC_eye_sore(atan2df(x, y), 0.0f);
        obj->rot.y = rot;
        obj->trans.x += sindf(rot) * speed;
        obj->trans.z += cosdf(obj->rot.y) * speed;
        if (mag > 40.0f) {
            func_801063E8_eye_sore(obj, 2);
            func_80106328_eye_sore(obj, 2);
        } else {
            func_801063E8_eye_sore(obj, 1);
            func_80106328_eye_sore(obj, 1);
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    } else {
        func_801063E8_eye_sore(obj, 0);
    }
}

void func_80106718_eye_sore(omObjData *obj) {
    s16 player = obj->work[0];
    EsPlayer *p = &D_8010CA60_eye_sore[player];
    EsEye *eye0 = &D_8010C938_eye_sore[(s16)(player * 2)];
    EsEye *eye1 = &D_8010C938_eye_sore[(s16)(player * 2) + 1];

    if (p->unk0D < 12) {
        switch (p->unk0E) {
        case 0:
            eye0->unk06 = 1;
            break;
        case 5:
            if (p->unk0D < 7) {
                eye1->unk06 = 1;
            }
            break;
        case 60:
            eye0->unk06 = 5;
            break;
        case 65:
            if (p->unk0D < 7) {
                eye1->unk06 = 5;
            }
            break;
        }
        p->unk0E = (p->unk0E + 1) % 90;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010683C_eye_sore);

void func_801070CC_eye_sore(omObjData *obj) {
    f32 dx;
    f32 dz;
    f32 rot;
    s8 pad = obj->work[3];
    EsPlayer *p = &D_8010CA60_eye_sore[obj->work[0]];

    func_80105E0C_eye_sore(p->unk28, p->unk2C, obj->trans.x, obj->trans.z, &dx, &dz, &rot, 40.0f);
    if (dx + dz == 0.0f) {
        if (p->timer < 40) {
            p->timer++;
        }
        if (p->timer == 15) {
            func_801063E8_eye_sore(obj, 4);
        }
        if (p->timer >= 31 && (D_8010AF20_eye_sore >= 3 || D_800CBB6E_main[pad] + D_800D20A1_main[pad] != 0 || p->cpu != 0)) {
            p->unk11 = 0;
            p->timer = 0;
            p->state = 0;
        }
    } else {
        obj->trans.x += dx;
        obj->trans.z += dz;
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    }
}

void func_8010725C_eye_sore(omObjData *obj) {
    s8 pad = obj->work[3];
    EsEnt *ent = ES_ENT(ES_ENT_PLAYER, (s8)obj->work[0]);
    EsPlayer *p = &D_8010CA60_eye_sore[obj->work[0]];

    if (p->timer < 46) {
        p->unk34 = obj->trans.y + 30.0f;
        if (p->timer == 0 || p->timer == 23) {
            func_8004AC98_main(0x48C, (s16)obj->work[0]);
        }
        if ((u8)(p->timer % 23) < 11) {
            if (p->unk38 < p->unk34 + 44.0f) {
                p->unk38 += 5.0f;
            }
            if (p->unk3C < p->unk38 + 46.0f) {
                p->unk3C += 5.0f;
            }
            if (p->unk40 < p->unk3C + 60.0f) {
                p->unk40 += 5.0f;
            }
        } else {
            if (p->unk34 + 44.0f < p->unk38) {
                p->unk38 -= 5.0f;
            }
            if (p->unk38 + 46.0f < p->unk3C) {
                p->unk3C -= 5.0f;
            }
            if (p->unk3C + 60.0f < p->unk40) {
                p->unk40 -= 5.0f;
            }
        }
        ent->unk18 = func_801059BC_eye_sore(ent->unk18, 30.0f);
        Hu3DModelPosSet(obj->model[2], p->unk30, p->unk34, p->unk44);
        Hu3DModelPosSet(obj->model[3], p->unk30, p->unk38, p->unk44);
        Hu3DModelPosSet(obj->model[4], p->unk30, p->unk3C, p->unk44);
        Hu3DModelPosSet(obj->model[5], p->unk30, p->unk40, p->unk44);
        Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, ent->unk18);
        Hu3DModelRotSet(obj->model[3], 0.0f, 0.0f, ent->unk18);
        Hu3DModelRotSet(obj->model[4], 0.0f, 0.0f, ent->unk18);
        Hu3DModelRotSet(obj->model[5], 0.0f, 0.0f, ent->unk18);
        func_8001C258_main(obj->model[2], 4, 0);
        func_8001C258_main(obj->model[3], 4, 0);
        func_8001C258_main(obj->model[4], 4, 0);
        func_8001C258_main(obj->model[5], 4, 0);
    }
    if (p->timer == 46) {
        func_8004AC98_main(0x48C, (s16)obj->work[0]);
    }
    if (p->timer >= 16 && p->timer < 51) {
        ent->unk16 -= 7;
        if (ent->unk16 < 0) {
            ent->unk16 = 0;
        }
        func_8001F9E4_main(obj->model[2], ent->unk16);
    }
    if (p->timer < 23) {
        obj->trans.y += D_8010AC38_eye_sore[p->timer];
    } else if (p->timer < 46) {
        obj->trans.y += D_8010AC38_eye_sore[p->timer - 23];
    } else if (p->timer == 50) {
        func_8001C258_main(obj->model[2], 4, 4);
        func_8001C258_main(obj->model[3], 4, 4);
        func_8001C258_main(obj->model[4], 4, 4);
        func_8001C258_main(obj->model[5], 4, 4);
        func_801063E8_eye_sore(obj, 4);
    } else if (p->timer >= 65) {
        if (D_8010AF20_eye_sore >= 3 || D_800CBB6E_main[pad] + D_800D20A1_main[pad] != 0 || p->cpu != 0) {
            p->unk11 = 0;
            p->timer = 0;
            p->state = 0;
            ent->unk16 = 0xFF;
            func_8001F9E4_main(obj->model[2], 0xFF);
            p->unk34 = obj->trans.y + 30.0f;
            p->unk38 = obj->trans.y + 74.0f;
            p->unk3C = obj->trans.y + 120.0f;
            p->unk40 = obj->trans.y + 180.0f;
            return;
        }
    }
    if (p->timer < 65) {
        p->timer++;
    }
}

void func_80107804_eye_sore(omObjData *obj) {
    s8 player = obj->work[0];
    s8 base = player * 2;
    s8 end;
    s8 i;
    EsPlayer *p = &D_8010CA60_eye_sore[player];
    EsRing *ring = &D_8010CBC0_eye_sore[player];
    EsEye *eye;
    omObjData *eyeObj;
    f32 dist;
    f32 lim;
    f32 dx;
    f32 dz;
    f32 r;
    f32 rot;
    f32 d2;

    dist = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
    p->dist = dist;
    lim = ring->unk04 + 60.0f;
    if (dist > 280.0f) {
        obj->trans.x = sindf(p->rot) * 279.0f;
        obj->trans.z = cosdf(p->rot) * 279.0f;
    }
    if (p->dist < lim) {
        p->unk28 = ring->obj->trans.x + sindf(p->rot) * (ring->unk04 + 115.0f + p->unk0D * 6);
        p->unk2C = ring->obj->trans.z + cosdf(p->rot) * (ring->unk04 + 115.0f + p->unk0D * 6);
        p->unk11 = 1;
        ring->unk00 = 1;
        p->timer = 0;
        func_801063E8_eye_sore(obj, 5);
        func_8001C92C_main(obj->model[0], 2.0f);
        if (!(GwPlayer[obj->work[0]].stat & 1)) {
            omVibrate((s16)obj->work[0], 20, 0, 20);
        }
        func_8004AC98_main(0x488, (s16)obj->work[0]);
        func_8001C258_main(obj->model[2], 4, 4);
        func_8001C258_main(obj->model[3], 4, 4);
        func_8001C258_main(obj->model[4], 4, 4);
        func_8001C258_main(obj->model[5], 4, 4);
    }
    end = base + 2;
    for (i = base; i < end; i++) {
        eye = &D_8010C938_eye_sore[i];
        if (eye->unk10 != 0) {
            eyeObj = eye->obj;
            if (eyeObj->trans.y < 120.0f) {
                dx = obj->trans.x - eyeObj->trans.x;
                dz = obj->trans.z - eyeObj->trans.z;
                d2 = dx * dx + dz * dz;
                r = eye->unk0C + 60.0f;
                lim = r * r;
                if (d2 < lim) {
                    p->unk11 = 2;
                    p->timer = 0;
                    eye->unk10 = 0;
                    eye->unk06 = 5;
                    func_801063E8_eye_sore(obj, 6);
                    obj->rot.y = atan2df(dx, dz);
                    if (!(GwPlayer[obj->work[0]].stat & 1)) {
                        omVibrate((s16)obj->work[0], 20, 0, 20);
                    }
                    func_8004AC98_main(0x48B, (s16)obj->work[0]);
                    func_8004ACE0_main(0x2AB, (s16)obj->work[0]);
                    rot = func_801059BC_eye_sore(obj->rot.y, 180.0f);
                    p->unk30 = sindf(rot) * D_8010AC98_eye_sore[GwPlayer[player].chr] + obj->trans.x;
                    p->unk44 = cosdf(rot) * D_8010AC98_eye_sore[GwPlayer[player].chr] + obj->trans.z;
                }
            }
        }
    }
}

void func_80107CBC_eye_sore(omObjData *obj) {
    s8 player = obj->work[0];
    EsEnt *ent = ES_ENT(ES_ENT_PLAYER, player);
    EsPlayer *p = &D_8010CA60_eye_sore[player];
    EsRing *ring = &D_8010CBC0_eye_sore[player];
    f32 rot;

    if (D_8010AF20_eye_sore != 2) {
        if (D_8010AF20_eye_sore >= 3) {
            switch (p->unk11) {
            case 0:
                if (func_80105F40_eye_sore(obj, 0.0f)) {
                    func_801063E8_eye_sore(obj, 1);
                } else if (ent->unk06 != 7 && ent->unk06 != 8) {
                    func_801063E8_eye_sore(obj, 0);
                }
                if (p->rank == 0) {
                    ent->unk20 = 18.0f;
                    ent->unk24 = 0.6f;
                    ent->unk28 = 2.6f;
                    ent->unk2C = (obj->trans.z + 85.0f) / 50.0f;
                    p->unk11 = 99;
                }
                break;
            case 1:
                func_801070CC_eye_sore(obj);
                break;
            case 2:
                func_8010725C_eye_sore(obj);
                break;
            case 99:
                if (func_80105F40_eye_sore(obj, 0.0f)) {
                    func_801063E8_eye_sore(obj, 1);
                } else if (ent->unk06 != 7 && ent->unk06 != 8) {
                    func_801063E8_eye_sore(obj, 0);
                }
                if (ent->unk0E < 50) {
                    ent->unk0E++;
                    CZoomM[player] -= ent->unk20;
                    CRotM[player].x = func_801059BC_eye_sore(CRotM[player].x, ent->unk24);
                    CRotM[player].y = 0.0f;
                    CRotM[player].z = 0.0f;
                    CenterM[player].x = 0.0f;
                    CenterM[player].y += ent->unk28;
                    CenterM[player].z += ent->unk2C;
                }
                break;
            }
        }
    } else {
        if (p->unk0D < 0) {
            if (p->timer < 60) {
                func_801063E8_eye_sore(obj, 3);
                p->timer++;
            } else if (func_80105F40_eye_sore(obj, 0.0f)) {
                func_801063E8_eye_sore(obj, 1);
            } else {
                func_801063E8_eye_sore(obj, 0);
            }
            return;
        }
        switch (p->unk11) {
        case 0:
            if (p->cpu == 0) {
                func_80106510_eye_sore(obj);
            } else {
                func_8010683C_eye_sore(obj);
            }
            break;
        case 1:
            func_801070CC_eye_sore(obj);
            break;
        case 2:
            func_8010725C_eye_sore(obj);
            break;
        }
        rot = func_801059BC_eye_sore(atan2df(obj->trans.x, obj->trans.z), 0.0f);
        if ((p->unk10 == 0) & (rot > 300.0f) && rot < 330.0f) {
            p->unk10 = 1;
        }
        if (p->unk10 != 0 && p->unk0C == 0) {
            if (rot > 330.0f && p->rot < 30.0f && p->lap[p->unk0D] == 0) {
                p->lap[p->unk0D] = 1;
                p->unk0D--;
                if (p->unk0D < 0) {
                    p->rank = D_8010AF6C_eye_sore;
                    D_8010CA5A_eye_sore++;
                    func_8004AC98_main(0x490, (s16)obj->work[0]);
                    return;
                }
                func_8004AC98_main(0x48F, (s16)obj->work[0]);
                ring->unk04 = D_8010AF30_eye_sore[p->unk0D] * 75.0f;
            }
        }
        if ((p->rot < rot && rot - p->rot < 300.0f) || (rot < 30.0f && p->rot > 330.0f)) {
            p->unk0C = 1;
        } else if ((rot <= ring->unk08 && ring->unk08 <= p->rot)
                   || (rot > 330.0f && ring->unk08 < 30.0f && p->rot < 30.0f)
                   || (rot > 330.0f && ring->unk08 > 330.0f && rot <= ring->unk08)) {
            p->unk0C = 0;
        }
        p->rot = rot;
        func_80106718_eye_sore(obj);
        func_80107804_eye_sore(obj);
    }
}

void func_80108330_eye_sore(omObjData *obj) {
    u16 idx = obj->work[0];
    EsPlayer *p = &D_8010CA60_eye_sore[idx];
    EsEnt *ent = ES_ENT(ES_ENT_PLAYER, idx);
    u16 chr = GwPlayer[idx].chr;
    s32 dir = D_800A178C_main[chr][0];
    u16 i;
    s16 *link;

    obj->model[0] = func_8000B108_main(dir | D_800A178C_main[chr][2], 0x2A9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 2));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x13));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x23));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x15));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x1A));
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x36));
    for (i = 0; i < 2; i++) {
        D_8010CC18_eye_sore[idx][i] = DataRead(dir | D_8010AC58_eye_sore[chr][i]);
    }
    D_8010AF22_eye_sore[idx] = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010CC18_eye_sore[idx][0], 0,
                                             D_8010AC78_eye_sore[chr]);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    if (idx == 0) {
        obj->model[1] = func_8000B0A0_main(0, 0xC9);
        func_8001C2FC_main(obj->model[1], 0x80000000, 0);
        func_8001C448_main(obj->model[1]);
        func_8001C514_main(obj->model[1]);
        func_80088800_main(*(HuMtx4F *)HmfModelData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        D_8010CBB4_eye_sore = obj->model[1];
    } else {
        obj->model[1] = Hu3DModelLink(D_8010CBB4_eye_sore);
    }
    obj->model[2] = func_8000B108_main(0x10014, 0x8C);
    func_8001FA68_main(obj->model[2]);
    func_8001F9E4_main(obj->model[2], 0xFF);
    link = &D_8010CBB6_eye_sore;
    *link = obj->model[2];
    obj->model[3] = Hu3DModelLink(*link);
    obj->model[4] = Hu3DModelLink(*link);
    obj->model[5] = Hu3DModelLink(*link);
    obj->trans.y = 5.0f;
    obj->trans.z = 200.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 5.0f, 200.0f);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, 5.0f, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, 5.0f, obj->trans.z);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, 5.0f, obj->trans.z);
    Hu3DModelPosSet(obj->model[5], obj->trans.x, 5.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelScaleSet(obj->model[3], 1.2f, 1.2f, 1.2f);
    Hu3DModelScaleSet(obj->model[4], 1.4f, 1.4f, 1.4f);
    Hu3DModelScaleSet(obj->model[5], 1.6f, 1.6f, 1.6f);
    func_80105D38_eye_sore(obj, 0, 2);
    ent->unk06 = 0;
    switch (idx) {
    case 0:
        for (i = 0; i < 6; i++) {
            func_8001C8A8_main(obj->model[i], 1);
        }
        break;
    case 1:
        for (i = 0; i < 6; i++) {
            func_8001C8A8_main(obj->model[i], 2);
        }
        break;
    case 2:
        for (i = 0; i < 6; i++) {
            func_8001C8A8_main(obj->model[i], 4);
        }
        break;
    case 3:
        for (i = 0; i < 6; i++) {
            func_8001C8A8_main(obj->model[i], 8);
        }
        break;
    }
    ent->unk16 = 0xFF;
    p->unk34 = obj->trans.y + 30.0f;
    p->unk38 = obj->trans.y + 74.0f;
    p->unk3C = obj->trans.y + 120.0f;
    p->unk40 = obj->trans.y + 180.0f;
    p->unk0C = 0;
    p->unk0D = 14;
    p->cpu = GwPlayer[idx].stat & 1;
    p->dif = GwPlayer[idx].cpu_difficulty;
    p->state = 0;
    p->rot = 0;
    p->unk0E = 0;
    p->unk11 = 0;
    p->timer = 0;
    p->unk12 = 0;
    p->rank = -1;
    p->unk10 = 0;
    p->unk04 = D_8010AC50_eye_sore[p->dif];
    p->obj = obj;
    for (i = 0; i < 15; i++) {
        p->lap[i] = 0;
    }
    obj->work[3] = GwPlayer[idx].pad;
    obj->func = func_80107CBC_eye_sore;
}

void func_80108AAC_eye_sore(void) {
    omObjData *obj;
    EsEnt *ent;
    s32 unused[2];
    u32 kind = 0;
    s8 i;

    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            kind = 0;
            break;
        case 1:
            kind = 1;
            break;
        case 2:
            kind = 2;
            break;
        case 3:
            kind = 3;
            break;
        }
        ent = ES_ENT(ES_ENT_PLAYER, i);
        obj = omAddObj(600, 7, 12, -1, func_80108330_eye_sore);
        obj->work[0] = kind;
        ent->obj = obj;
    }
}

void func_80108BBC_eye_sore(void) {
    EsPlayer *p;
    s8 n = 0;
    s8 i;

    for (i = 0; i < 4; i++) {
        p = &D_8010CA60_eye_sore[i];
        if (p->rank < 0) {
            n++;
        }
    }
    if (n == 4) {
        D_8010CA60_eye_sore[0].rank = 3;
        D_8010CA60_eye_sore[1].rank = 3;
        D_8010CA60_eye_sore[2].rank = 3;
        D_8010CA60_eye_sore[3].rank = 3;
        D_8010CC10_eye_sore = 1;
    }
    for (i = 0; i < 4; i++) {
        p = &D_8010CA60_eye_sore[i];
        if (p->rank < 0) {
            p->rank = D_8010AF6C_eye_sore;
        }
        GwPlayer[p->obj->work[0]].bonusCoin = p->rank;
        if (p->rank == 0) {
            func_801063E8_eye_sore(p->obj, 7);
            func_80106250_eye_sore(p->obj, 1);
        } else {
            func_801063E8_eye_sore(p->obj, 8);
        }
    }
}

#ifdef NON_MATCHING
void func_80108D3C_eye_sore(void) {
    EsPlayer *p;
    EsPlayer *q;
    s8 i;
    s8 j;
    s8 add = 3;
    s32 again;

    do {
        again = 0;
        for (i = 0; i < 4; i++) {
            p = &D_8010CA60_eye_sore[i];
            for (j = 0; j < 4; j++) {
                if (i != j) {
                    q = &D_8010CA60_eye_sore[j];
                    if (p->rank != -1 && p->rank == q->rank) {
                        if (func_80105CE4_eye_sore(2) != 0) {
                            p->rank++;
                            p->unk12 = add;
                        } else {
                            q->rank++;
                            q->unk12 = add;
                        }
                        add += 3;
                        again = 1;
                    }
                }
            }
        }
    } while (again);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108D3C_eye_sore);
#endif

void func_80108E8C_eye_sore(omObjData *obj) {
    u8 player = obj->work[0];
    EsEnt *ent = ES_ENT(ES_ENT_RING, player);
    EsPlayer *p = &D_8010CA60_eye_sore[player];
    EsRing *ring = &D_8010CBC0_eye_sore[player];
    omObjData *pobj = p->obj;
    f32 rot;
    f32 scale;
    f32 flash;

    switch (ring->unk0C) {
    case 1:
        if (p->unk12 != 0 && ++ent->unk08 < p->unk12) {
            break;
        }
        ent->unk24 -= 2.0f;
        obj->rot.y = func_801059BC_eye_sore(obj->rot.y, ent->unk24);
        ent->unk28 -= 0.008;
        obj->scale.x = obj->scale.y = obj->scale.z = ent->unk28 * 0.7f;
        scale = ent->unk28 * 2.4f;
        Hu3DModelScaleSet(obj->model[1], scale, 1.0f, scale);
        if (ent->unk28 < 0.06f) {
            func_8001C258_main(obj->model[0], 4, 4);
            func_8001C258_main(obj->model[1], 4, 4);
            func_8001C258_main(obj->model[2], 4, 4);
            func_8001C258_main(obj->model[3], 4, 0);
            Hu3DModelPosSet(obj->model[3], 0.0f, 90.0f, 70.0f);
            ring->unk0C++;
        }
        break;
    case 2:
        flash = D_8010ACA0_eye_sore[ent->unk16];
        Hu3DModelScaleSet(obj->model[3], flash, flash, flash);
        if (ent->unk16 > 16) {
            ent->unk04 = 0;
            func_8001C258_main(obj->model[3], 4, 4);
            ring->unk0C++;
            break;
        }
        ent->unk04 -= 15;
        ent->unk16++;
        if (ring->unk0D == 0) {
            func_8004AC98_main(0x48A, (s16)pobj->work[0]);
            ring->unk0D = 1;
        }
        func_8001F9E4_main(obj->model[3], ent->unk04);
        break;
    case 3:
        break;
    case 0:
    default:
        if (p->unk0C == 0) {
            obj->rot.y = func_801059BC_eye_sore(atan2df(pobj->trans.x, pobj->trans.z), 0.0f);
        }
        ring->unk08 = obj->rot.y;
        switch (ring->unk00) {
        case 0:
            break;
        case 1:
            rot = func_801059BC_eye_sore(p->rot, 180.0f);
            obj->trans.x = sindf(rot) * 30.0f;
            obj->trans.z = cosdf(rot) * 30.0f;
            func_8001C258_main(obj->model[2], 4, 0);
            func_8001C92C_main(obj->model[2], 1.0f);
            func_8001C6A8_main(obj->model[2], 5.0f);
            Hu3DModelRotSet(obj->model[2], 0.0f, p->rot, 0.0f);
            Hu3DModelPosSet(obj->model[2], sindf(p->rot) * ring->unk04, obj->scale.y * 50.0f,
                            cosdf(p->rot) * ring->unk04);
            scale = D_8010AF30_eye_sore[p->unk0D] * 1.4f;
            Hu3DModelScaleSet(obj->model[2], scale, scale, scale);
            ent->unk06 = 1;
            ring->unk00++;
            break;
        case 2:
            func_80105E0C_eye_sore(0.0f, 0.0f, obj->trans.x, obj->trans.z, &ent->unk18, &ent->unk1C, &rot, 30.0f);
            obj->trans.x += ent->unk18;
            obj->trans.z += ent->unk1C;
            if (ent->unk18 + ent->unk1C == 0.0f) {
                ring->unk00 = 0;
            }
            break;
        }
        if (p->unk0D < 0) {
            ring->unk0C = 1;
            ent->unk28 = D_8010AF30_eye_sore[0];
        } else {
            scale = D_8010AF30_eye_sore[p->unk0D] * 0.7f;
            if (scale < obj->scale.z) {
                obj->scale.z -= 0.03;
            } else {
                obj->scale.z = scale;
            }
            obj->scale.x = obj->scale.y = obj->scale.z;
            scale = D_8010AF30_eye_sore[p->unk0D] * 2.4f;
            Hu3DModelScaleSet(obj->model[1], scale, 1.0f, scale);
        }
        if (ent->unk06 != 0) {
            if (++ent->unk06 >= 15) {
                ent->unk06 = 0;
                func_8001C258_main(obj->model[2], 4, 4);
            }
        }
        break;
    }
}

void func_80109478_eye_sore(omObjData *obj) {
    u16 idx = obj->work[0];
    EsEnt *ent = ES_ENT(ES_ENT_RING, idx);
    EsRing *ring = &D_8010CBC0_eye_sore[idx];
    f32 step;
    u16 i;

    if (idx == 0) {
        obj->model[0] = func_8000B108_main(0xA015D, 0x2B9);
        D_8010CBB2_eye_sore = obj->model[0];
    } else {
        obj->model[0] = Hu3DModelLink(D_8010CBB2_eye_sore);
    }
    obj->model[1] = Hu3DModelLink(D_8010CBB4_eye_sore);
    obj->model[2] = func_8000B108_main(0x510002, 0x2B9);
    func_8001C92C_main(obj->model[2], 0.0f);
    func_8001C258_main(obj->model[2], 4, 4);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    obj->model[3] = func_8000B108_main(0x510003, 0x2A8);
    func_8001FA68_main(obj->model[3]);
    func_8001F9E4_main(obj->model[3], 0xFF);
    func_8001C258_main(obj->model[3], 4, 4);
    Hu3DModelPosSet(obj->model[3], 0.0f, 60.0f, 20.0f);
    Hu3DModelRotSet(obj->model[3], 318.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[3], 0.3f, 0.3f, 0.3f);
    obj->trans.y = 5.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.7f;
    Hu3DModelScaleSet(obj->model[1], 2.4f, 1.0f, 2.4f);
    Hu3DModelPosSet(obj->model[1], 0.0f, 5.0f, 0.0f);
    switch (idx) {
    case 0:
        for (i = 0; i < 4; i++) {
            func_8001C8A8_main(obj->model[i], 1);
        }
        break;
    case 1:
        for (i = 0; i < 4; i++) {
            func_8001C8A8_main(obj->model[i], 2);
        }
        break;
    case 2:
        for (i = 0; i < 4; i++) {
            func_8001C8A8_main(obj->model[i], 4);
        }
        break;
    case 3:
        for (i = 0; i < 4; i++) {
            func_8001C8A8_main(obj->model[i], 8);
        }
        break;
    }
    ring->unk04 = 75.0f;
    ring->unk08 = 0;
    ring->unk0D = 0;
    ring->obj = obj;
    ent->unk04 = 0xFF;
    ent->unk20 = 0.3f;
    step = 0.7f / 15;
    for (i = 0; i < 15; i++) {
        D_8010AF30_eye_sore[i] = step * (i + 1) + 0.3f;
    }
    obj->func = func_80108E8C_eye_sore;
}

void func_80109854_eye_sore(void) {
    omObjData *obj;
    EsEnt *ent;
    s8 i;

    for (i = 0; i < 4; i++) {
        ent = ES_ENT(ES_ENT_RING, i);
        obj = omAddObj(700, 4, 1, -1, func_80109478_eye_sore);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

void func_801098F8_eye_sore(omObjData *obj) {
    u8 idx = obj->work[0];
    u8 odd = idx % 2;
    u8 lane = odd * 2 + 1;
    f32 dist = 0.0f;
    EsEnt *ent = ES_ENT(ES_ENT_EYE, idx);
    EsPlayer *p = &D_8010CA60_eye_sore[obj->work[1]];
    EsRing *ring = &D_8010CBC0_eye_sore[obj->work[1]];
    EsEye *eye = &D_8010C938_eye_sore[idx];
    s16 n;
    f32 scale;

    if (p->unk0D < 0 || D_8010AF20_eye_sore >= 3) {
        if (eye->unk06 == 0) {
            return;
        }
        eye->unk06 = 5;
    }
    switch (eye->unk06) {
    case 0:
        return;
    case 1:
        ent->unk18 = 0;
        ent->unk1C = 1.0f;
        eye->unk06++;
        eye->unk00 = lane * 60 + func_80105CE4_eye_sore(60);
        eye->unk00 = func_801059BC_eye_sore(p->rot, -eye->unk00);
        if (!odd) {
            n = func_80105CE4_eye_sore(2);
        } else {
            n = (D_8010C938_eye_sore[idx - 1].unk04 + 1) % 2;
        }
        if (n == 0) {
            dist = ring->unk04 + eye->unk0C
                   + func_80105CE4_eye_sore((s16)(180.0f - (ring->unk04 + eye->unk0C + eye->unk0C))) + 20.0f;
            eye->unk04 = 0;
        } else {
            n = 280.0f - (ring->unk04 + 200.0f + eye->unk0C);
            if (n == 0) {
                dist = 280.0f;
            }
            if (n > 0) {
                dist = 280 - func_80105CE4_eye_sore(n);
            }
            if (n < 0) {
                dist = 280 - func_80105CE4_eye_sore(-n);
            }
            eye->unk04 = 1;
        }
        obj->trans.x = sindf(eye->unk00) * dist;
        obj->trans.z = cosdf(eye->unk00) * dist;
        if (func_80105CE4_eye_sore(D_8010ACF0_eye_sore[p->dif]) == 0) {
            eye->unk05 = 1;
        } else {
            eye->unk05 = 0;
        }
        break;
    case 2:
        ent->unk18 += 2.0f;
        obj->trans.y -= ent->unk18;
        if (obj->trans.y < 5.0f) {
            obj->trans.y = 5.0f;
            eye->unk06++;
        }
        break;
    case 3:
        ent->unk18 -= 7.0f;
        obj->trans.y += ent->unk18;
        if (obj->trans.y < 5.0f) {
            obj->trans.y = 5.0f;
            eye->unk06++;
        }
        break;
    case 4:
        if (--ent->unk04 < 0) {
            ent->unk04 = func_80105CE4_eye_sore(25) + 20;
            ent->unk24 = func_80105A3C_eye_sore(360);
        }
        obj->trans.x += sindf(ent->unk24) * 1.5f;
        obj->trans.z += cosdf(ent->unk24) * 1.5f;
        break;
    case 5:
        ent->unk1C -= 0.05;
        if (ent->unk1C < 0.4) {
            eye->unk10 = 0;
            eye->unk11 = 0;
        }
        if (ent->unk1C < 0.05) {
            obj->trans.y = 600.0f;
            eye->unk06 = 0;
            eye->unk0C = 30.0f;
            obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
            Hu3DModelScaleSet(obj->model[1], 0.1f, 1.0f, 0.1f);
            func_8001C258_main(obj->model[1], 4, 4);
        } else {
            eye->unk0C = ent->unk1C * 30.0f;
            obj->scale.x = obj->scale.y = obj->scale.z = ent->unk1C;
            Hu3DModelScaleSet(obj->model[1], ent->unk1C, 1.0f, ent->unk1C);
        }
        break;
    }
    if (eye->unk06 != 5) {
        if (obj->trans.y == 5.0f) {
            Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
        } else if (obj->trans.y < 450.0f) {
            scale = 1.0f - (2.0f * obj->trans.y) / 1000.0f;
            Hu3DModelScaleSet(obj->model[1], scale, 1.0f, scale);
            eye->unk10 = 1;
        } else if (obj->trans.y < 580.0f) {
            func_8001C258_main(obj->model[1], 4, 0);
            if (eye->unk11 == 0) {
                HuAudFXPlay(0x489);
                eye->unk11 = 1;
            }
        }
    }
    eye->unk00 = func_801059BC_eye_sore(atan2df(obj->trans.x, obj->trans.z), 0.0f);
    if (obj->trans.x < -260.0f) {
        obj->trans.x = -260.0f;
    }
    if (obj->trans.x > 260.0f) {
        obj->trans.x = 260.0f;
    }
    if (obj->trans.z < -260.0f) {
        obj->trans.z = -260.0f;
    }
    if (obj->trans.z > 260.0f) {
        obj->trans.z = 260.0f;
    }
    eye->unk08 = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
    if (eye->unk08 < ring->unk04 + eye->unk0C) {
        obj->trans.x = sindf(eye->unk00) * (eye->unk08 + 1.0f);
        obj->trans.z = cosdf(eye->unk00) * (eye->unk08 + 1.0f);
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 5.0f, obj->trans.z);
}

void func_8010A0CC_eye_sore(omObjData *obj) {
    u16 idx = obj->work[0];
    s32 first = idx;
    EsEye *eye = &D_8010C938_eye_sore[obj->work[0]];
    void *data = DataRead(0xA008C);
    u16 i;

    obj->model[0] = func_8000B108_main(0xA008A, 0x2A9);
    HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "c201n_00_DEF");
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    DataClose(data);
    if (first == 0) {
        obj->model[1] = func_8000B108_main(0x510006, 0x2B9);
        D_8010CBB8_eye_sore = obj->model[1];
        obj->trans.x = 0.0f;
    } else {
        obj->model[1] = Hu3DModelLink(D_8010CBB8_eye_sore);
        obj->trans.x = 0.0f;
    }
    obj->trans.y = 600.0f;
    obj->trans.z = 250.0f;
    obj->rot.x = 340.0f;
    func_8001C258_main(obj->model[1], 4, 4);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], 0.1f, 1.0f, 0.1f);
    switch (idx) {
    case 0:
    case 1:
        for (i = 0; i < 2; i++) {
            func_8001C8A8_main(obj->model[i], 1);
        }
        obj->work[1] = 0;
        break;
    case 2:
    case 3:
        for (i = 0; i < 2; i++) {
            func_8001C8A8_main(obj->model[i], 2);
        }
        obj->work[1] = 1;
        break;
    case 4:
    case 5:
        for (i = 0; i < 2; i++) {
            func_8001C8A8_main(obj->model[i], 4);
        }
        obj->work[1] = 2;
        break;
    case 6:
    case 7:
        for (i = 0; i < 2; i++) {
            func_8001C8A8_main(obj->model[i], 8);
        }
        obj->work[1] = 3;
        break;
    }
    eye->unk00 = 0;
    eye->unk06 = 0;
    eye->unk05 = 0;
    eye->unk04 = 0;
    eye->unk10 = 0;
    eye->unk0C = 30.0f;
    eye->obj = obj;
    eye->unk11 = 0;
    obj->func = func_801098F8_eye_sore;
}

void func_8010A3C0_eye_sore(void) {
    omObjData *obj;
    EsEnt *ent;
    s8 i;

    for (i = 0; i < 8; i++) {
        ent = ES_ENT(ES_ENT_EYE, i);
        obj = omAddObj(800, 3, 2, -1, func_8010A0CC_eye_sore);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

void func_8010A464_eye_sore(void) {
    u32 i;

    if (D_8010ACF4_eye_sore == 0) {
        D_8010ACF4_eye_sore = 1;
        for (i = 0; i < 4; i++) {
            CZoomM[i] = 1627.4962f;
            CRotM[i].x = 317.99966f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = -45.0f;
            CenterM[i].z = -85.0f;
        }
    }
}

void func_8010A528_eye_sore(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010A54C_eye_sore(omObjData *obj) {
    s8 i;
    s8 j;

    if (WipeStatGet() == 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 2; j++) {
                DataClose(D_8010CC18_eye_sore[i][j]);
            }
            func_80033354_main(D_8010AF22_eye_sore[i]);
        }
        obj->func = func_8010A528_eye_sore;
    }
}

void func_8010A62C_eye_sore(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010A54C_eye_sore;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8010A684_eye_sore(omObjData *obj) {
    switch (D_8010AF20_eye_sore) {
    case 0:
        GMesCreate(7);
        D_8010AF20_eye_sore = 1;
        D_8010CA58_eye_sore = 0;
        break;
    case 1:
        if (GMesStatGet() == 0) {
            D_8010AF20_eye_sore = 2;
            GMesCreate(0x1A, 60, 160, 28);
        }
        if (++D_8010CA58_eye_sore == 43) {
            HuAudSeqPlay(0x35);
        }
        break;
    case 2:
        D_8010CBB0_eye_sore--;
        func_8003F578_main((D_8010CBB0_eye_sore + 29) / 30);
        if (D_8010CA5A_eye_sore != 0) {
            D_8010AF6C_eye_sore += D_8010CA5A_eye_sore;
            D_8010CC11_eye_sore += D_8010CA5A_eye_sore;
            D_8010CA5A_eye_sore = 0;
            func_80108D3C_eye_sore();
        }
        if (D_8010CBB0_eye_sore == 0 || D_8010CC11_eye_sore >= 3) {
            func_8003F5C0_main();
            GMesCreate(0x12);
            HuAudSeqFadeOut(120);
            D_8010CBB0_eye_sore = 0;
            D_8010AF20_eye_sore = 3;
        }
        break;
    case 3:
        if (GMesStatGet() == 0) {
            if (++D_8010CBB0_eye_sore >= 15) {
                func_80108BBC_eye_sore();
                if (D_8010CC10_eye_sore != 0) {
                    HuAudSeqPlay(0x6C);
                    D_8010CBB0_eye_sore = 144;
                } else {
                    HuAudSeqPlay(0x65);
                    D_8010CBB0_eye_sore = 98;
                }
                D_8010AF20_eye_sore = 4;
            }
        }
        break;
    case 4:
        if (--D_8010CBB0_eye_sore <= 0) {
            WipeCreateOut(0, 20);
            obj->func = func_8010A54C_eye_sore;
        }
        break;
    }
}

void func_8010A8EC_eye_sore(omObjData *obj) {
    D_8010AF20_eye_sore = 0;
    D_8010CBB0_eye_sore = 1800;
    D_8010CA5A_eye_sore = 0;
    D_8010CC11_eye_sore = 0;
    D_8010AF6C_eye_sore = 0;
    D_8010CC10_eye_sore = 0;
    func_8010A464_eye_sore();
    func_80106210_eye_sore();
    func_80108AAC_eye_sore();
    func_80109854_eye_sore();
    func_8010A3C0_eye_sore();
    WipeCreateIn(0xFF, 16);
    obj->func = func_8010A684_eye_sore;
}

void func_8010A97C_eye_sore(omObjData *obj) {
}

void func_8010A984_eye_sore(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 4;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(4);
    func_8000B710_main(4);
    for (i = 0; i < 4; i++) {
        ScissorSet(i, D_8010ACF8_eye_sore[i].scissor[0], D_8010ACF8_eye_sore[i].scissor[1],
                   D_8010ACF8_eye_sore[i].scissor[2], D_8010ACF8_eye_sore[i].scissor[3]);
        ViewportSet(i, D_8010ACF8_eye_sore[i].viewport[0], D_8010ACF8_eye_sore[i].viewport[1],
                    D_8010ACF8_eye_sore[i].viewport[2], D_8010ACF8_eye_sore[i].viewport[3],
                    D_8010ACF8_eye_sore[i].viewport[4], D_8010ACF8_eye_sore[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010ACF8_eye_sore[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010AAF8_eye_sore(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(60, 0);
    func_8004A208_main();
    func_8010A984_eye_sore();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightDirSet(0, -33.0f, 0.0f, 115.0f);
    HmfLightDirSet(1, -33.0f, 0.0f, 115.0f);
    HmfLightDirSet(2, -33.0f, 0.0f, 115.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010AF0C_eye_sore, 0);
    func_80045010_main(D_8010AF0C_eye_sore, 1);
    omAddObj(1000, 0, 0, -1, func_8010A8EC_eye_sore);
    omAddObj(1000, 0, 0, -1, func_8010A62C_eye_sore);
    func_80105A74_eye_sore();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AF0C_eye_sore);
