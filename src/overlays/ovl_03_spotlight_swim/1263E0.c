#include "common.h"
// m5 sp: Spotlight Swim
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

/* One slot of the overlay's object table (D_8010D480_spotlight_swim, 50 x 0x84). */
typedef struct SsEnt {
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
} SsEnt; // Size 0x84

extern SsEnt D_8010D480_spotlight_swim[50];

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


/* A camera (D_8010D1D4_spotlight_swim). */
typedef struct SsCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} SsCamera; // Size 0x2C

extern SsCamera D_8010D1D4_spotlight_swim[1];
extern const s16 D_8010D2E0_spotlight_swim[];

extern s16 D_8010CCF4_spotlight_swim[];
extern s16 D_8010D3B0_spotlight_swim[];
/* Views of D_8010D480_spotlight_swim[1].unk04 / .unk06 (retail addresses them as their own symbols). */
extern s16 D_8010D508_spotlight_swim;
extern s16 D_8010D50A_spotlight_swim;
extern f32 D_8010D338_spotlight_swim[2];
extern s8 D_8010D343_spotlight_swim;
extern omObjData *D_8010D348_spotlight_swim;

/* This overlay's functions */
void func_80106148_spotlight_swim(omObjData *obj);
void func_801061DC_spotlight_swim(omObjData *obj);
void func_8010CB78_spotlight_swim(void);
void func_80106150_spotlight_swim(omObjData *obj);
void func_80106350_spotlight_swim(omObjData *obj);
void func_801065C4_spotlight_swim(omObjData *obj);
void func_8010B828_spotlight_swim(omObjData *obj);
void func_8010C25C_spotlight_swim(omObjData *obj);
void func_8010C900_spotlight_swim(omObjData *obj);

void func_801059A0_spotlight_swim(void) {
    func_8010CB78_spotlight_swim();
}

f32 func_801059BC_spotlight_swim(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

void func_80105A3C_spotlight_swim(void) {
    SsEnt *ent;
    u32 i;

    for (i = 0, ent = D_8010D480_spotlight_swim; i < 50; i++, ent++) {
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

void func_80105B04_spotlight_swim(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

void func_80105B7C_spotlight_swim(s16 se, s16 ch) {
    if (D_8010D3B0_spotlight_swim[ch] != -1) {
        HuAudFXStop(D_8010D3B0_spotlight_swim[ch]);
    }
    D_8010D3B0_spotlight_swim[ch] = func_8004AC98_main(D_8010CCF4_spotlight_swim[se], ch);
}

void func_80105C04_spotlight_swim(s16 se, s16 ch) {
    if (D_8010D3B0_spotlight_swim[ch] != -1) {
        HuAudFXStop(D_8010D3B0_spotlight_swim[ch]);
    }
    D_8010D3B0_spotlight_swim[ch] = func_8004ACE0_main(D_8010CCF4_spotlight_swim[se], ch);
}

s32 func_80105C8C_spotlight_swim(s32 max) {
    return rand8() % max;
}

void func_80105CE0_spotlight_swim(omObjData *obj, u16 motion, s16 arg2) {
    if (motion < 10) {
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        func_8001C814_main(obj->model[0], arg2, arg2);
    }
}

void func_80105D4C_spotlight_swim(omObjData *obj, u16 motion, s16 arg2, s16 arg3, s16 arg4) {
    if (motion < 10) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[motion]].unk02, arg2, arg3, arg4);
    }
}

s32 func_80105DC8_spotlight_swim(omObjData *obj) {
    s32 ret = 0;

    if (obj->rot.y != 0.0f) {
        if (obj->rot.y < 180.0f) {
            obj->rot.y = func_801059BC_spotlight_swim(obj->rot.y, -7.0f);
            if (obj->rot.y > 350.0f) {
                obj->rot.y = 0.0f;
            }
        } else {
            obj->rot.y = func_801059BC_spotlight_swim(obj->rot.y, 7.0f);
            if (obj->rot.y < 10.0f) {
                obj->rot.y = 0.0f;
            }
        }
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80105E9C_spotlight_swim);

void func_80106148_spotlight_swim(omObjData *obj) {
}

void func_80106150_spotlight_swim(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x240000, 0x299);
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_80106148_spotlight_swim;
}

void func_801061A0_spotlight_swim(void) {
    D_8010D480_spotlight_swim[0].obj = omAddObj(500, 1, 0, -1, func_80106150_spotlight_swim);
}

void func_801061DC_spotlight_swim(omObjData *obj) {
    SsEnt *ent = &D_8010D480_spotlight_swim[1];

    if (++D_8010D50A_spotlight_swim >= 30) {
        D_8010D508_spotlight_swim++;
        D_8010D50A_spotlight_swim = 0;
    }
    switch (ent->unk04 & 1) {
    case 0:
        obj->trans.y += 0.5f;
        obj->trans.z -= 0.5f;
        if (D_8010D343_spotlight_swim != 7) {
            D_8010D338_spotlight_swim[0] += 0.5f;
            D_8010D348_spotlight_swim->trans.z -= 0.5f;
        }
        break;
    case 1:
        obj->trans.y -= 0.5f;
        obj->trans.z += 0.5f;
        if (D_8010D343_spotlight_swim != 7) {
            D_8010D338_spotlight_swim[0] -= 0.5f;
            D_8010D348_spotlight_swim->trans.z += 0.5f;
        }
        break;
    }
    obj->trans.x -= 4.0f;
    if (obj->trans.x == -254.0f) {
        obj->trans.x = 250.0f;
    }
}

void func_80106350_spotlight_swim(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x240001, 0xA9);
    obj->trans.x = 250.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -50.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, -50.0f);
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_801061DC_spotlight_swim;
}

void func_801063E4_spotlight_swim(void) {
    D_8010D480_spotlight_swim[1].obj = omAddObj(600, 1, 0, -1, func_80106350_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106420_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801065C4_spotlight_swim);

void func_80106754_spotlight_swim(void) {
    D_8010D480_spotlight_swim[16].obj = omAddObj(1200, 5, 3, -1, func_801065C4_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106790_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106808_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801069BC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106BC8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106EB0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801072C4_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010755C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80107674_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80107710_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801077AC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801079FC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80107C10_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010846C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010881C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80108AD8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109088_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109194_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010932C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109468_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109558_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109690_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801098A8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109A94_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109C1C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109E08_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109F60_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A328_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A670_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A7AC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010AAB8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010ADF8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010AE9C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010B828_spotlight_swim);

void func_8010BA30_spotlight_swim(void) {
    D_8010D480_spotlight_swim[13].obj = omAddObj(1300, 5, 5, -1, func_8010B828_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BA6C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BD10_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BD5C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BDE0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BFD0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C094_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C25C_spotlight_swim);

void func_8010C444_spotlight_swim(void) {
    omObjData *obj = omAddObj(1100, 1, 0, -1, func_8010C25C_spotlight_swim);

    obj->work[0] = 0;
    D_8010D480_spotlight_swim[12].obj = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C484_spotlight_swim);

void func_8010C52C_spotlight_swim(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010C550_spotlight_swim(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010C52C_spotlight_swim;
    }
}

void func_8010C588_spotlight_swim(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010C550_spotlight_swim;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C5E0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C900_spotlight_swim);

void func_8010CA00_spotlight_swim(void) {
}

void func_8010CA08_spotlight_swim(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010D1D4_spotlight_swim[i].scissor[0], D_8010D1D4_spotlight_swim[i].scissor[1],
                   D_8010D1D4_spotlight_swim[i].scissor[2], D_8010D1D4_spotlight_swim[i].scissor[3]);
        ViewportSet(i, D_8010D1D4_spotlight_swim[i].viewport[0], D_8010D1D4_spotlight_swim[i].viewport[1],
                    D_8010D1D4_spotlight_swim[i].viewport[2], D_8010D1D4_spotlight_swim[i].viewport[3],
                    D_8010D1D4_spotlight_swim[i].viewport[4], D_8010D1D4_spotlight_swim[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010D1D4_spotlight_swim[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010CB78_spotlight_swim(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010CA08_spotlight_swim();
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
    func_80045010_main(D_8010D2E0_spotlight_swim, 0);
    func_80045010_main(D_8010D2E0_spotlight_swim, 1);
    omAddObj(1500, 0, 0, -1, func_8010C900_spotlight_swim);
    omAddObj(1500, 0, 0, -1, func_8010C588_spotlight_swim);
    func_80105A3C_spotlight_swim();
}

/* Shift-JIS fullwidth "ABC", passed to func_80045010_main. */
const s16 D_8010D2E0_spotlight_swim[] = { 0x8260, 0x8261, 0x8262, 0 };
