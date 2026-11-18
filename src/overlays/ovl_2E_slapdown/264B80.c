#include "common.h"
// m2 sd: Slap Down (four players)
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/util.h"
#include "game/wipe.h"
#include "math.h"

f64 fabs(f64);

// esprite
void func_8000BC48_main(u16, s32);
void func_8000BE5C_main(u16, f32, f32);
void func_8000BF00_main(u16, f32);


void func_8010A550_slapdown(void);

/* One slot of the overlay's object table (D_8010AAB0_slapdown, 50 x 0x84):
 * [0] background sprite, [1] the shuffling card object, [2..10] the nine cards,
 * [11..14] the players, [15..18] the player panels. */
typedef struct SdEnt {
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
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
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
} SdEnt; // Size 0x84

typedef struct {
    s16 unk0;
    s16 unk2;
} SdCpuRate;

#define SD_ENT_BG 0
#define SD_ENT_DECK 1
#define SD_ENT_CARD 2
#define SD_ENT_PLAYER 11
#define SD_ENT_PANEL 15

// bss
extern s16 D_8010AA10_slapdown;
extern s16 D_8010AA12_slapdown;
extern s16 D_8010AA14_slapdown;
extern s16 D_8010AA16_slapdown[4];
extern void *D_8010AA20_slapdown[4];
extern s16 D_8010AA30_slapdown;
extern s16 D_8010AA32_slapdown;
extern s16 D_8010AA38_slapdown[9];
extern f32 D_8010AA4C_slapdown;
extern u8 D_8010AA50_slapdown;
extern s16 D_8010AA52_slapdown;
extern void *D_8010AA58_slapdown[5];
extern u8 D_8010AA6E_slapdown;
extern s16 D_8010AA72_slapdown;
extern s16 D_8010AA74_slapdown;
extern s16 D_8010AA76_slapdown;
extern void *D_8010AA78_slapdown[6];
extern s16 D_8010AA90_slapdown[4];
extern s16 D_8010AA98_slapdown;
extern s16 D_8010AA9A_slapdown;
extern void *D_8010AA9C_slapdown;
extern s16 D_8010AAA0_slapdown;
extern SdEnt D_8010AAB0_slapdown[50];
extern SdEnt D_8010AB34_slapdown;     /* = D_8010AAB0_slapdown[SD_ENT_DECK] */
extern SdEnt D_8010ABB8_slapdown[9];  /* = D_8010AAB0_slapdown[SD_ENT_CARD] */
extern SdEnt D_8010B05C_slapdown[4];  /* = D_8010AAB0_slapdown[SD_ENT_PLAYER] */
extern SdEnt D_8010B26C_slapdown[4];  /* = D_8010AAB0_slapdown[SD_ENT_PANEL] */

// data
typedef struct {
    s32 file;
    s32 pad;
} SdFile;

typedef struct {
    f32 x;
    f32 y;
} SdVec2;

extern f32 D_8010A6C0_slapdown[4];
extern f32 D_8010A6D0_slapdown[4];
extern f32 D_8010A6E0_slapdown[4];
extern f32 D_8010A6F0_slapdown[4];
extern f32 D_8010A700_slapdown[4];
extern f32 D_8010A710_slapdown[4];
extern f32 D_8010A720_slapdown[4];
extern f32 D_8010A730_slapdown[5];
extern SdFile D_8010A744_slapdown[4];
extern SdCpuRate D_8010A760_slapdown[];
extern f32 D_8010A7F0_slapdown[9];
extern f32 D_8010A814_slapdown[9];
extern SdVec2 D_8010A838_slapdown[4];
extern SdVec2 D_8010A858_slapdown[4];
extern s32 D_8010A878_slapdown[4];
extern s32 D_8010A888_slapdown;

// unknown
extern s32 D_800A178C_main[][6];

f32 fabsf(f32);
void func_80106600_slapdown(omObjData *obj);
void func_80106900_slapdown(omObjData *obj);
void func_80107858_slapdown(omObjData *obj);
void func_801080FC_slapdown(omObjData *obj);
void func_8010820C_slapdown(omObjData *obj);
void func_801084BC_slapdown(omObjData *obj);
void func_80108BAC_slapdown(omObjData *obj);
void func_80108FE4_slapdown(omObjData *obj);
void func_8010924C_slapdown(omObjData *obj);
void func_80109E14_slapdown(omObjData *obj);
void func_80109E58_slapdown(omObjData *obj);
void func_80106608_slapdown(omObjData *obj);

void func_801059A0_slapdown(void) {
    func_8010A550_slapdown();
}

f32 func_801059BC_slapdown(f32 angle, f32 add) {
    angle += add;
    while (angle >= 360.0f) {
        angle -= 360.0f;
    }
    while (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

u8 func_80105A3C_slapdown(s32 max) {
    return (u32)(rand8() * max) >> 8;
}

void func_80105A74_slapdown(void) {
    u32 i;
    SdEnt *ent;

    for (i = 0, ent = D_8010AAB0_slapdown; i < 50; i++, ent++) {
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

void func_80105B3C_slapdown(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105BB4_slapdown(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = fabs(x0 - x1) * 5.0;
    f32 dz = fabs(z0 - z1) * 5.0;
    f32 zoom = sqrtf(dx * dx + dz * dz);
    f32 rot = func_801059BC_slapdown(atan2df(dx, dz), 0.0f);

    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

#ifdef NON_MATCHING
void func_80105CBC_slapdown(s16 conNo) {
    s16 i;

    if ((u16)conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if (D_800CDA7C_main[conNo] & 0x400) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_slapdown(CRotM[i].x, 1.0f);
        }
    }
    if (D_800CDA7C_main[conNo] & 0x800) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_slapdown(CRotM[i].x, -1.0f);
        }
    }
    if (D_800CDA7C_main[conNo] & 0x200) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_slapdown(CRotM[i].y, 1.0f);
        }
    }
    if (D_800CDA7C_main[conNo] & 0x100) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_slapdown(CRotM[i].y, -1.0f);
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80105CBC_slapdown);
#endif

void func_80106290_slapdown(s8 phase) {
    D_8010AA6E_slapdown = phase;
}

void func_8010629C_slapdown(omObjData *obj, s16 mot, s16 arg2, s16 arg3, s16 arg4, s16 *cur) {
    if (*cur != mot) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[mot]].unk02, arg2, arg3, arg4);
        *cur = mot;
    }
}

void func_80106338_slapdown(omObjData *obj, s16 mot, s16 arg2, s16 arg3, s16 *cur) {
    if (*cur != mot) {
        func_8001C5B4_main(obj->model[0], obj->motion[mot]);
        func_8001C814_main(obj->model[0], arg2, arg3);
        *cur = mot;
    }
}

/* Moves (x0, z0) toward (x1, z1): the longer axis at full speed, the other in proportion. */
#ifdef NON_MATCHING
void func_801063D4_slapdown(f32 x0, f32 z0, f32 x1, f32 z1, f32 *vx, f32 *vz, f32 speed) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801063D4_slapdown);
#endif

#ifdef NON_MATCHING
f32 func_80106534_slapdown(f32 cur, f32 target, f32 step) {
    f32 diff = target - cur;
    f32 add;

    if (diff < 0.0f) {
        diff = -diff;
    }
    if (diff < step) {
        return target;
    }
    if (cur < target) {
        add = step;
        if (diff > 180.0f) {
            add = -step;
        }
        cur = func_801059BC_slapdown(cur, add);
    } else if (target < cur) {
        if (diff > 180.0f) {
            add = step;
        } else {
            add = -step;
        }
        cur = func_801059BC_slapdown(cur, add);
    }
    return cur;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106534_slapdown);
#endif

void func_80106600_slapdown(omObjData *obj) {
}

void func_80106608_slapdown(omObjData *obj) {
    SdEnt *ent = &D_8010AAB0_slapdown[SD_ENT_BG];

    ent->unk40 = func_8000B838_main(0x4F0000);
    ent->unk42 = InitEspriteSlot(ent->unk40, 0, 0);
    func_8000BC48_main(ent->unk42, 0x4000);
    ent->unk44.x = 160.0f;
    ent->unk44.y = 120.0f;
    func_8000BBD4_main(ent->unk42, 160, 120);
    obj->func = func_80106600_slapdown;
}

void func_801066A4_slapdown(void) {
    omObjData *obj = omAddObj(50, 1, 0, -1, func_80106608_slapdown);

    obj->work[0] = 0;
    D_8010AAB0_slapdown[SD_ENT_BG].obj = obj;
}

void func_801066E4_slapdown(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        DataClose(D_8010AA20_slapdown[i]);
    }
    for (i = 0; i < 4; i++) {
        func_80033354_main(D_8010AA90_slapdown[i]);
    }
}

void func_80106780_slapdown(omObjData *obj) {
    if (D_8010AA30_slapdown == 1 && D_8010AA74_slapdown < 50) {
        if ((rand8() + rand8()) % D_8010A760_slapdown[GwPlayer[obj->work[0]].cpu_difficulty].unk0 != 0 &&
            D_8010AA74_slapdown >= 2) {
            return;
        }
    } else if ((rand8() + rand8()) % D_8010A760_slapdown[GwPlayer[obj->work[0]].cpu_difficulty].unk2 != 0) {
        return;
    }
    D_800D5558_main[obj->work[3]] |= 0x8000;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106900_slapdown);

void func_80107858_slapdown(omObjData *obj) {
    SdEnt *ent = &D_8010B05C_slapdown[obj->work[0]];
    s8 chr = GwPlayer[obj->work[0]].chr;
    s32 mot;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2A9);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x14));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 8));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x30));
    if (chr != 3) {
        mot = func_80017BB8_main(chr, 0x38);
    } else {
        mot = func_80017BB8_main(chr, 0x3A);
    }
    func_8000B460_main(obj, 5, mot);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    ent->unk04 = 0;
    if (chr != 5) {
        obj->trans.x = D_8010A6C0_slapdown[obj->work[1]];
        obj->trans.y = 75.0f;
        obj->trans.z = D_8010A6D0_slapdown[obj->work[1]];
    } else {
        obj->trans.x = D_8010A6E0_slapdown[obj->work[1]];
        obj->trans.y = 75.0f;
        obj->trans.z = D_8010A6F0_slapdown[obj->work[1]];
    }
    obj->rot.x = 0.0f;
    obj->rot.y = D_8010A720_slapdown[obj->work[1]];
    obj->rot.z = 0.0f;
    obj->model[1] = func_8000B0A0_main(0, 0x14C9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    obj->model[2] = func_8000B108_main(0x4F0018, 0x2A9);
    D_8010AA20_slapdown[obj->work[1]] = DataRead(D_8010A744_slapdown[obj->work[1]].file);
    D_8010AA90_slapdown[obj->work[1]] =
        HmfAnimCreate(HmfModelData[obj->model[2]].hmf, D_8010AA20_slapdown[obj->work[1]], 0, "s246_07_DEF");
    func_8001C448_main(obj->model[2]);
    func_8001C514_main(obj->model[2]);
    func_8001C6A8_main(obj->model[2], 0.0f);
    func_8001C92C_main(obj->model[2], 0.0f);
    switch (obj->work[1]) {
        case 0:
            Hu3DModelPosSet(obj->model[2], -285.0f, 100.0f, -285.0f);
            break;
        case 1:
            Hu3DModelPosSet(obj->model[2], 285.0f, 100.0f, -285.0f);
            break;
        case 2:
            Hu3DModelPosSet(obj->model[2], 285.0f, 100.0f, 285.0f);
            break;
        case 3:
            Hu3DModelPosSet(obj->model[2], -285.0f, 100.0f, 285.0f);
            break;
    }
    Hu3DModelRotSet(obj->model[2], 0.0f, D_8010A730_slapdown[obj->work[1]], 0.0f);
    obj->model[3] = func_8000B108_main(0x4F0017, 0x2A9);
    Hu3DModelPosSet(obj->model[3], D_8010A700_slapdown[obj->work[1]], 0.0f, D_8010A710_slapdown[obj->work[1]]);
    Hu3DModelRotSet(obj->model[3], 0.0f, D_8010A720_slapdown[obj->work[1]], 0.0f);
    obj->model[4] = func_8000B108_main(0x4F001A, 0x2A9);
    Hu3DModelPosSet(obj->model[4], D_8010A700_slapdown[obj->work[1]], 0.0f, D_8010A710_slapdown[obj->work[1]]);
    Hu3DModelRotSet(obj->model[4], 0.0f, D_8010A720_slapdown[obj->work[1]], 0.0f);
    func_8001C6A8_main(obj->model[4], 0.0f);
    func_8001C92C_main(obj->model[4], 0.0f);
    ent->unk0A = -2;
    obj->func = func_80106900_slapdown;
}

void func_80107DCC_slapdown(void) {
    s16 slots[4];
    omObjData *obj;
    SdEnt *ent;
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
        ent = &D_8010B05C_slapdown[i];
        obj = omAddObj(250, 10, 60, -1, func_80107858_slapdown);
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

void func_80107FDC_slapdown(omObjData *obj, s16 frame) {
    func_80033354_main(D_8010AA12_slapdown);
    D_8010AA12_slapdown = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010AA58_slapdown[frame], 0, "s246_01_DEF");
}

void func_80108064_slapdown(void) {
    s16 i;

    for (i = 0; i < 5; i++) {
        DataClose(D_8010AA58_slapdown[i]);
    }
    func_80033354_main(D_8010AA12_slapdown);
}

void func_801080D0_slapdown(void) {
    DataClose(D_8010AA9C_slapdown);
    func_80033354_main(D_8010AA52_slapdown);
}


void func_801080FC_slapdown(omObjData *obj) {
    SdEnt *deck = &D_8010AB34_slapdown;

    switch (D_8010AA6E_slapdown) {
        case 0:
            break;
        case 1:
            if (deck->unk04 < 60) {
                if (deck->unk06 == 0) {
                    HuAudFXPlay(0x479);
                    deck->unk06 = 1;
                }
                deck->unk04++;
                func_80107FDC_slapdown(obj, deck->unk04 % 5);
            } else {
                if (deck->unk06 == 1) {
                    HuAudFXPlay(0x47F);
                    deck->unk06 = 2;
                }
                func_80107FDC_slapdown(obj, D_8010AA72_slapdown);
                D_8010AA50_slapdown = 1;
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
    }
}

void func_8010820C_slapdown(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x4F0019, 0x2A9);
    D_8010AA58_slapdown[0] = DataRead(0x4F0011);
    D_8010AA58_slapdown[1] = DataRead(0x4F0012);
    D_8010AA58_slapdown[2] = DataRead(0x4F0013);
    D_8010AA58_slapdown[3] = DataRead(0x4F0014);
    D_8010AA58_slapdown[4] = DataRead(0x4F0015);
    D_8010AA12_slapdown = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010AA58_slapdown[0], 0, "s246_19_DEF");
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    D_8010AA72_slapdown = rand8() % 5;
    obj->func = func_801080FC_slapdown;
}

void func_80108340_slapdown(void) {
    omObjData *obj = omAddObj(150, 1, 0, -1, func_8010820C_slapdown);

    obj->work[0] = 0;
    D_8010AB34_slapdown.obj = obj;
}

void func_80108380_slapdown(omObjData *obj, s16 face) {
    func_80033354_main(D_8010AA38_slapdown[obj->work[0]]);
    D_8010AA38_slapdown[obj->work[0]] =
        HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010AA78_slapdown[face], 0, "s246_01_DEF");
}

void func_80108420_slapdown(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        DataClose(D_8010AA78_slapdown[i]);
    }
    for (i = 0; i < 9; i++) {
        func_80033354_main(D_8010AA38_slapdown[i]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801084BC_slapdown);

void func_80108BAC_slapdown(omObjData *obj) {
    SdEnt *ents[9];
    omObjData *objs[9];
    s16 i;
    s16 k;

    for (i = 0; i < 9; i++) {
        ents[i] = &D_8010ABB8_slapdown[i];
        objs[i] = ents[i]->obj;
    }
    obj->model[0] = func_8000B108_main(0x4F0016, 0x2A9);
    obj->trans.x = D_8010A7F0_slapdown[obj->work[1]];
    obj->trans.y = 35.7455f;
    obj->trans.z = D_8010A814_slapdown[obj->work[1]];
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    if (obj->work[0] == 8) {
        D_8010AA78_slapdown[0] = DataRead(0x4F0001);
        D_8010AA78_slapdown[1] = DataRead(0x4F0002);
        D_8010AA78_slapdown[2] = DataRead(0x4F0003);
        D_8010AA78_slapdown[3] = DataRead(0x4F0004);
        D_8010AA78_slapdown[4] = DataRead(0x4F0005);
        D_8010AA78_slapdown[5] = DataRead(0x4F0006);
        /* one odd face, then the other four as pairs */
        ents[0]->unk06 = D_8010AA72_slapdown;
        k = 1;
        for (i = 0; i < 5; i++) {
            if (i != D_8010AA72_slapdown) {
                ents[k]->unk06 = i;
                ents[k + 1]->unk06 = i;
                k += 2;
            }
        }
        for (i = 0; i < 9; i++) {
            D_8010AA38_slapdown[objs[i]->work[0]] =
                HmfAnimCreate(HmfModelData[objs[i]->model[0]].hmf, D_8010AA78_slapdown[5], 0, "s246_01_DEF");
            func_8001C448_main(objs[i]->model[0]);
            func_8001C514_main(objs[i]->model[0]);
        }
    }
    obj->func = func_801084BC_slapdown;
}

void func_80108E44_slapdown(void) {
    s16 slots[9];
    omObjData *obj;
    SdEnt *ent;
    s16 i;
    s16 j;

    for (i = 0; i < 9; i++) {
        slots[i] = i;
    }
    for (i = 0; i < 9; i++) {
        ent = &D_8010ABB8_slapdown[i];
        obj = omAddObj(200, 1, 0, -1, func_80108BAC_slapdown);
        obj->work[0] = i;
        ent->obj = obj;
        j = rand8() % (9 - i);
        obj->work[1] = slots[j];
        slots[j] = -1;
        for (j = 1; j < 9 - i; j++) {
            if (slots[j - 1] == -1) {
                slots[j - 1] = slots[j];
                slots[j] = -1;
            }
        }
    }
}

void func_80108FE4_slapdown(omObjData *obj) {
    SdEnt *panel = &D_8010B26C_slapdown[obj->work[0]];
    SdEnt *ents[4];
    omObjData *objs[4];
    s16 i;
    s32 phase;

    for (i = 0; i < 4; i++) {
        ents[i] = &D_8010B05C_slapdown[i];
        objs[i] = ents[i]->obj;
    }
    phase = D_8010AA6E_slapdown;
    if (phase < 10) {
        if (phase >= 7) {
            switch (panel->unk04) {
                case 2:
                    break;
                case 0:
                    for (i = 0; i < 4; i++) {
                        if (objs[i]->work[1] == obj->work[0] && (u16)(ents[i]->unk0A + 2) >= 2) {
                            func_8000BB54_main(panel->unk42);
                            switch (ents[i]->unk16) {
                                case 0:
                                    func_8000BB54_main(panel->unk06);
                                    break;
                                case 1:
                                    func_8000BB54_main(panel->unk08);
                                    break;
                                case 2:
                                    func_8000BB54_main(panel->unk0A);
                                    break;
                                case 3:
                                    func_8000BB54_main(panel->unk0C);
                                    break;
                            }
                            panel->unk04 = 1;
                        }
                    }
                    break;
                case 1:
                    if (panel->unk18 < 1.0f) {
                        panel->unk18 += 0.05f;
                    } else {
                        panel->unk04 = 2;
                    }
                    break;
            }
        }
    }
    func_8000BE5C_main(panel->unk42, panel->unk18, panel->unk18);
    func_8000BE5C_main(panel->unk06, panel->unk18, panel->unk18);
    func_8000BE5C_main(panel->unk08, panel->unk18, panel->unk18);
    func_8000BE5C_main(panel->unk0A, panel->unk18, panel->unk18);
    func_8000BE5C_main(panel->unk0C, panel->unk18, panel->unk18);
}

void func_8010924C_slapdown(omObjData *obj) {
    SdEnt *panel = &D_8010B26C_slapdown[obj->work[0]];
    s16 i;

    if (obj->work[0] == 0 || obj->work[0] == 3) {
        panel->unk40 = func_8000B838_main(0x4F000C);
        panel->unk42 = InitEspriteSlot(panel->unk40, 0, 0);
        if (obj->work[0] == 3) {
            func_8000BF00_main(panel->unk42, 180.0f);
        }
    } else {
        panel->unk40 = func_8000B838_main(0x4F000B);
        panel->unk42 = InitEspriteSlot(panel->unk40, 0, 0);
        if (obj->work[0] == 2) {
            func_8000BF00_main(panel->unk42, 180.0f);
        }
    }
    func_8000BC48_main(panel->unk42, 0);
    func_8000BBD4_main(panel->unk42, D_8010A838_slapdown[obj->work[0]].x, D_8010A838_slapdown[obj->work[0]].y);
    func_8000BB94_main(panel->unk42);
    func_8000BCC8_main(panel->unk42, 0xEEEE);
    for (i = 0; i < 4; i++) {
        panel->unk40 = func_8000B838_main(D_8010A878_slapdown[i]);
        switch (i) {
            case 0:
                panel->unk06 = InitEspriteSlot(panel->unk40, 0, 0);
                func_8000BC48_main(panel->unk06, 0);
                func_8000BBD4_main(panel->unk06, D_8010A858_slapdown[obj->work[0]].x, D_8010A858_slapdown[obj->work[0]].y);
                func_8000BB94_main(panel->unk06);
                func_8000BCC8_main(panel->unk06, 0xAAAA);
                break;
            case 1:
                panel->unk08 = InitEspriteSlot(panel->unk40, 0, 0);
                func_8000BC48_main(panel->unk08, 0);
                func_8000BBD4_main(panel->unk08, D_8010A858_slapdown[obj->work[0]].x, D_8010A858_slapdown[obj->work[0]].y);
                func_8000BB94_main(panel->unk08);
                func_8000BCC8_main(panel->unk08, 0xAAAA);
                break;
            case 2:
                panel->unk0A = InitEspriteSlot(panel->unk40, 0, 0);
                func_8000BC48_main(panel->unk0A, 0);
                func_8000BBD4_main(panel->unk0A, D_8010A858_slapdown[obj->work[0]].x, D_8010A858_slapdown[obj->work[0]].y);
                func_8000BB94_main(panel->unk0A);
                func_8000BCC8_main(panel->unk0A, 0xAAAA);
                break;
            case 3:
                panel->unk0C = InitEspriteSlot(panel->unk40, 0, 0);
                func_8000BC48_main(panel->unk0C, 0);
                func_8000BBD4_main(panel->unk0C, D_8010A858_slapdown[obj->work[0]].x, D_8010A858_slapdown[obj->work[0]].y);
                func_8000BB94_main(panel->unk0C);
                func_8000BCC8_main(panel->unk0C, 0xAAAA);
                break;
        }
    }
    panel->unk18 = 0.1f;
    obj->func = func_80108FE4_slapdown;
}

void func_80109640_slapdown(void) {
    omObjData *obj;
    SdEnt *ent;
    s16 i;

    for (i = 0; i < 4; i++) {
        ent = &D_8010B26C_slapdown[i];
        obj = omAddObj(300, 1, 0, -1, func_8010924C_slapdown);
        obj->work[0] = i;
        ent->obj = obj;
    }
}

/* Ranks the players by slap order (unk0A: frame of the slap, -1 slapped the wrong card, -2 never slapped). */
#ifdef NON_MATCHING
void func_801096E4_slapdown(void) {
    SdEnt *ents[4];
    omObjData *objs[4];
    s16 i;
    s16 j;
    s16 nHit = 0;
    s16 nNone = 0;
    s16 rank;
    s16 min;
    s16 flag;

    for (i = 0; i < 4; i++) {
        ents[i] = &D_8010B05C_slapdown[i];
        objs[i] = ents[i]->obj;
        ents[i]->unk16 = -1;
        if (ents[i]->unk0A == -2) {
            nNone++;
        }
        if (ents[i]->unk0A >= 0) {
            nHit++;
        }
    }
    (void)objs;
    if (nHit == 0) {
        if (nNone == 1) {
            for (i = 0; i < 4; i++) {
                if (ents[i]->unk0A == -1) {
                    ents[i]->unk16 = 1;
                } else {
                    ents[i]->unk16 = 0;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                ents[i]->unk16 = 3;
            }
        }
    } else {
        rank = 3;
        flag = 0;
        for (i = 0; i < 4; i++) {
            if (ents[i]->unk0A == -1) {
                ents[i]->unk16 = rank;
                flag = 1;
            }
        }
        min = 9999;
        for (i = 0; i < 4; i++) {
            if (ents[i]->unk0A == -2) {
                ents[i]->unk16 = rank;
                flag = 1;
            }
        }
        if (flag != 0) {
            rank--;
        }
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 4; i++) {
                if (ents[i]->unk16 == -1 && ents[i]->unk0A < min) {
                    min = ents[i]->unk0A;
                }
            }
            for (i = 0; i < 4; i++) {
                if (ents[i]->unk16 == -1 && ents[i]->unk0A == min) {
                    ents[i]->unk16 = rank;
                    rank--;
                }
            }
            min = 9999;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801096E4_slapdown);
#endif

/* Turns the ranks into places 0..3 (ties share a place) and writes them to the results. */
void func_801099C0_slapdown(void) {
    SdEnt *ents[4];
    omObjData *objs[4];
    s16 rank[4];
    s16 place[4];
    s16 i;
    s16 flag;

    for (i = 0; i < 4; i++) {
        rank[i] = 4;
        place[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        ents[i] = &D_8010B05C_slapdown[i];
        objs[i] = ents[i]->obj;
        if (rank[0] > ents[i]->unk16) {
            rank[0] = ents[i]->unk16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (rank[0] < ents[i]->unk16 && ents[i]->unk16 < rank[1]) {
            rank[1] = ents[i]->unk16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (rank[1] < ents[i]->unk16 && ents[i]->unk16 < rank[2]) {
            rank[2] = ents[i]->unk16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (rank[2] < ents[i]->unk16 && ents[i]->unk16 < rank[3]) {
            rank[3] = ents[i]->unk16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (rank[0] == ents[i]->unk16) {
            place[i] = 0;
        }
        if (rank[1] == ents[i]->unk16) {
            place[i] = 1;
        }
        if (rank[2] == ents[i]->unk16) {
            place[i] = 2;
        }
        if (rank[3] == ents[i]->unk16) {
            place[i] = 3;
        }
    }
    flag = 0;
    for (i = 0; i < 4; i++) {
        if (ents[i]->unk16 != 3) {
            flag = 1;
        }
    }
    if (flag == 0) {
        for (i = 0; i < 4; i++) {
            place[i] = 3;
        }
        D_8010AAA0_slapdown = 4;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[objs[i]->work[0]].bonusCoin = place[i];
        ents[i]->unk16 = place[i];
    }
}

void func_80109D54_slapdown(void) {
    u32 i;

    if (D_8010A888_slapdown == 0) {
        D_8010A888_slapdown = 1;
        for (i = 0; i < 1; i++) {
            CZoomM[i] = 2037.5552f;
            CRotM[i].x = 311.9663f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = -42.5f;
            CenterM[i].z = -160.0f;
        }
    }
}

void func_80109E14_slapdown(omObjData *obj) {
    func_80108064_slapdown();
    func_80108420_slapdown();
    func_801066E4_slapdown();
    HuAudFXStop(-1);
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80109E58_slapdown(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_80109E14_slapdown;
    }
}

void func_80109E90_slapdown(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_80109E58_slapdown;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109EE8_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010A2B8_slapdown);

void func_8010A3D8_slapdown(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010A3E0_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010A550_slapdown);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", D_8010AA08_slapdown);
