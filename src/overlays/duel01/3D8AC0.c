#include "common.h"
#include "duel01.h"

void func_801059D0_duel01(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel01(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_80119470_duel01 = func_800E1824_name_81(0, 0xA0, 1);
    D_80119474_duel01 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_80119478_duel01 = func_800E1824_name_81(1, 0xBC, 1);
    D_8011947C_duel01 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel01(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_80119470_duel01);
    func_800E1854_name_81(D_80119474_duel01);
    func_800E1854_name_81(D_80119478_duel01);
    func_800E1854_name_81(D_8011947C_duel01);
}

void func_80105B64_duel01(void) {
    GwSystem.current_board_index = 0;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x5A, 0, 0x4190);
}

void func_80105B9C_duel01(void) {
    s8 sp10;
    s8 sp11;

    omInitObjMan(0xA, 0);
    func_800E94D0_name_81();
    func_800E9B10_name_81(0x13, 0x241);
    func_800E9F4C_name_81(0x1C, &sp10, &sp11);
    func_800ECD0C_name_81(0, sp10, sp11);
    func_800E9F4C_name_81(0x1B, &sp10, &sp11);
    func_800ECD0C_name_81(1, sp10, sp11);
    GwPlayer[0].nnlink = -1;
    GwPlayer[0].nnidx = -1;
    GwPlayer[1].nnlink = -1;
    GwPlayer[1].nnidx = -1;
    func_800E9D9C_name_81();
    func_800E9564_name_81();
    GwSystem.bank_coins = 5;
    GwSystem.playerIndexVisitingBowser = 0;
    func_800EA760_name_81();
    omOvlReturnEx(1);
}

void func_80105C64_duel01(s32 arg0, s32 arg1, unkStruct01 *arg2) {
    f32 temp_f20;

    func_800EB708_name_81(arg0, arg1, arg2);
    temp_f20 = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->unk_00 = sindf(temp_f20);
    arg2->unk_08 = cosdf(temp_f20);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80105CC0_duel01);

void *func_80105EB0_duel01(unkStruct04 *arg0) {
    Process *process;
    unkStruct02 *temp_v0_2;

    process = omAddPrcObj(&func_80105CC0_duel01, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct02));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00.x = arg0->unk_0C.x;
    temp_v0_2->unk_00.y = arg0->unk_0C.y;
    temp_v0_2->unk_00.z = arg0->unk_0C.z;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80105F20_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801060D0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010615C_duel01);

void func_80106240_duel01(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

// TODO: arg0 is a pointer
void func_80106260_duel01(s32 arg0, unkStruct05 *arg1, s32 arg2, f32 arg3) {
    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        func_800EC1E4_name_81(&D_80105540_name_81, arg0 + 0xC, &D_80105540_name_81, arg3);
    } else {
        func_800EC1E4_name_81(&D_80105540_name_81, arg1->unk_24 + 0xC, &D_80105540_name_81, arg3);
    }
}

// TODO: arg0 is a pointer
void func_801062C0_duel01(s32 arg0, unkStruct05 *arg1, s32 arg2, f32 arg3) {
    if (arg2 & 9) {
        func_800EBF2C_name_81(&D_80105540_name_81, arg0 + 0xC, &D_80105540_name_81);
    } else {
        func_800EBF2C_name_81(&D_80105540_name_81, arg1->unk_24 + 0xC, &D_80105540_name_81);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80106308_duel01);

Process *func_8010645C_duel01(s32 arg0, s32 arg1) {
    Process *process;
    unkStruct06 *temp_v0_2;

    process = omAddPrcObj(&func_80106308_duel01, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct06));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00 = arg0;
    temp_v0_2->unk_04 = arg1;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801064C8_duel01);

void *func_80106740_duel01(s32 arg0) {
    Object *obj;

    obj = func_800D8010_name_81(arg0 & 0xFF, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0x1800);
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    return obj;
}

void func_801067D4_duel01(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81();
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80106828_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80107188_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118E60_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801079B8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80107EBC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801084A4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80108550_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80109404_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80109888_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010A210_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010AAB0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010AD48_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010AFB4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B130_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B480_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B4C0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B528_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B53C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B54C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010BCD4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010CE68_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010D424_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010D95C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010D9F4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DA84_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DB00_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118E98_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118EA4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118EB0_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118EE0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DB2C_duel01);

// duel b3: declarations for func_8010DC04_duel01..func_80110C3C_duel01
SpaceData *MBDMasuGet(s16 spaceIdx);
void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4);
void *func_8001D33C_main(s16 model, char *name);
void func_800EFABC_name_81(Object *arg0);
void func_8010DB2C_duel01(void);
void func_8010DC04_duel01(void);
void func_8010DDEC_duel01(void);
void func_8010E1B4_duel01(void);
void func_8010E3F8_duel01(void);
void func_8010E7C0_duel01(void);

/* The bell model part func_8001D33C_main returns: only its +0x14 float is used here. */
typedef struct Duel01Part {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 unk_14;
} Duel01Part;

extern char D_80118F18_duel01[]; /* "bell" (rodata; func_80111DFC_duel01 uses it too) */
extern s32 D_80118730_duel01[];
extern s16 D_80118740_duel01;
extern s16 D_80118742_duel01;
extern Process *D_80118744_duel01;
extern s16 D_80118748_duel01;
extern s16 D_8011874A_duel01;
extern Process *D_8011874C_duel01;
extern Object *D_80119490_duel01;
extern Process *D_80119494_duel01;
extern Object *D_80119498_duel01;
extern f32 D_8011949C_duel01;
extern Object *D_801194A0_duel01;
extern f32 D_801194A4_duel01;
extern s16 D_80118750_duel01[2];
extern s16 D_80118754_duel01[2][2]; /* each a pair of space ids (splat label D_80118756 is [0][1]) */
extern s32 D_8011875C_duel01;
extern Object *D_801194A8_duel01;
extern Object *D_801194AC_duel01[2];
Object *func_800D8B18_name_81(Object *arg0);
s32 func_800EFE20_name_81(f32 range);

/* A weighted choice: an entry is taken when a roll of 100 falls under its chance; value -1 ends a list. */
typedef struct Duel01Weight {
    /* 0x00 */ s8 value;
    /* 0x01 */ s8 chance;
} Duel01Weight;

extern s8 D_80118760_duel01[]; /* value, chance pairs as Duel01Weight (splat label D_80118761 is [1]) */
extern Duel01Weight *D_8011885C_duel01[]; /* per character */
extern s32 D_8011889C_duel01;

void func_8010DC04_duel01(void) {
    s16 model = D_80119490_duel01->omObj1->model[0];

    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80118F18_duel01, 0x4C, 0x46);
    ((Duel01Part *)func_8001D33C_main(D_80119490_duel01->omObj1->model[0], D_80118F18_duel01))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
}

void func_8010DCA8_duel01(void) {
    Object *obj;

    obj = func_800D8010_name_81(0x34, (s32)D_80118730_duel01);
    func_800D8944_name_81(obj);
    D_80119490_duel01 = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBDMasuGet(0x1D)->coords);
    func_8010DC04_duel01();
    D_80119494_duel01 = omAddPrcObj(func_8010DB2C_duel01, 0xA, 0, 0);
    omPrcSetStatBit(D_80119494_duel01, 0xA0);
}

void func_8010DD3C_duel01(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x32, 0);
    func_800D8944_name_81(obj);
    D_80119498_duel01 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80118740_duel01);
    to = MBDMasuGet(D_80118742_duel01);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81((s32)&from->coords, (s32)&to->coords, (unkStruct01 *)&obj->rot);
}

void func_8010DDEC_duel01(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_8011949C_duel01;
        sincosdf(rot, &HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010DF68_duel01(Vec *pos) {
    Process *process;
    s32 *angle;

    D_8011949C_duel01 = 10.0f;
    process = omAddPrcObj(func_8010DDEC_duel01, 0xA, 0, 0x40);
    D_80118744_duel01 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_80119498_duel01->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E008_duel01(void) {
    HmfModel *mdl;

    if (D_80118744_duel01 != NULL) {
        while (D_8011949C_duel01 >= 0.0f) {
            D_8011949C_duel01 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80118744_duel01);
        sincosdf(0.0f, &HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80119498_duel01->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80119498_duel01->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}


INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F18_duel01);

void func_8010E1B4_duel01(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_80119498_duel01->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_80119498_duel01->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80119498_duel01);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_80119498_duel01->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_80119498_duel01->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E2CC_duel01(void) {
    omAddPrcObj(func_8010E1B4_duel01, 0xA, 0, 0);
}

void func_8010E2F8_duel01(void) {
    func_8001C814_main(D_80119498_duel01->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_80119498_duel01->omObj1->model[0], 1.0f);
}

void func_8010E348_duel01(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x33, 0);
    func_800D8944_name_81(obj);
    D_801194A0_duel01 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80118748_duel01);
    to = MBDMasuGet(D_8011874A_duel01);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81((s32)&from->coords, (s32)&to->coords, (unkStruct01 *)&obj->rot);
}

void func_8010E3F8_duel01(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_801194A4_duel01;
        sincosdf(rot, &HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010E574_duel01(Vec *pos) {
    Process *process;
    s32 *angle;

    D_801194A4_duel01 = 10.0f;
    process = omAddPrcObj(func_8010E3F8_duel01, 0xA, 0, 0x40);
    D_8011874C_duel01 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_801194A0_duel01->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010E614_duel01(void) {
    HmfModel *mdl;

    if (D_8011874C_duel01 != NULL) {
        while (D_801194A4_duel01 >= 0.0f) {
            D_801194A4_duel01 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_8011874C_duel01);
        sincosdf(0.0f, &HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[0]);
        HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_801194A0_duel01->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_801194A0_duel01->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

void func_8010E7C0_duel01(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_801194A0_duel01->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_801194A0_duel01->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_801194A0_duel01);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_801194A0_duel01->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_801194A0_duel01->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E8D8_duel01(void) {
    omAddPrcObj(func_8010E7C0_duel01, 0xA, 0, 0);
}

void func_8010E904_duel01(void) {
    func_8001C814_main(D_801194A0_duel01->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_801194A0_duel01->omObj1->model[0], 1.0f);
}

void func_8010E954_duel01(s16 no) {
    s32 pad[2]; /* retail's frame is 8 bytes larger */
    Object *obj;
    SpaceData *from;

    if (D_801194AC_duel01[no] == NULL) {
        if (D_801194A8_duel01 == NULL) {
            obj = func_800D8010_name_81(0x2D, 0);
            func_800D8944_name_81(obj);
            D_801194A8_duel01 = obj;
        } else {
            obj = func_800D8B18_name_81(D_801194A8_duel01);
        }
        D_801194AC_duel01[no] = obj;
        obj->flags |= 2;
        func_8001C814_main(obj->omObj1->model[0], 2, 1);
        HuVecCopy3F(&obj->coords, &MBDMasuGet(D_80118750_duel01[no])->coords);
        from = MBDMasuGet(D_80118754_duel01[no][0]);
        func_800EB708_name_81((s32)&from->coords, (s32)&MBDMasuGet(D_80118754_duel01[no][1])->coords,
                              (unkStruct01 *)&obj->rot);
    }
}

void func_8010EA74_duel01(void) {
    s32 i;

    D_801194A8_duel01 = NULL;
    for (i = 0; i < 2; i++) {
        D_801194AC_duel01[i] = NULL;
        func_8010E954_duel01(i);
    }
}

void func_8010EAD4_duel01(s32 no) {
    if (D_8011875C_duel01 == 0) {
        HuAudFXPlay(0x1C4);
    }
    D_8011875C_duel01 = 1;
    func_8001C814_main(D_801194AC_duel01[no]->omObj1->model[0], 5, 0);
    HuPrcSleep(10);
}

void func_8010EB44_duel01(s32 no) {
    func_8001C814_main(D_801194AC_duel01[no]->omObj1->model[0], 1, 4);
    D_8011875C_duel01 = 0;
}

// register allocation: GCC keeps &GwSystem.current_player_index in s0 across the call (masked 22)
#ifdef NON_MATCHING
s32 func_8010EB88_duel01(void) {
    GW_PLAYER *rival;
    s32 chance;
    s32 dist;

    rival = MBDGetPlayerStruct((s8)(GwSystem.current_player_index ^ 1));
    chance = (5 - GwPlayer[GwSystem.current_player_index].star) * 10;
    if (mbWalkNum < 4) {
        if (GwSystem.current_player_index == 0) {
            if (rival->clink == 0) {
                dist = rival->cidx - 8;
                if (dist == mbWalkNum) {
                    chance = 0;
                }
                if (dist < mbWalkNum) {
                    chance += 20;
                }
            }
        } else if (rival->clink == 1) {
            dist = rival->cidx - 8;
            if (dist == mbWalkNum) {
                chance = 0;
            }
            if (dist < mbWalkNum) {
                chance += 20;
            }
        }
    }
    return chance;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EB88_duel01);
#endif

s16 func_8010EC78_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 tbl[12] = { 40, 90, 30, 50, 90, 10, 80, 15, 60, 80, 70, 90 };
    s32 prize = player->stats.prize.gamblePrize;

    if (prize == -1) {
        return 0;
    }
    return tbl[prize];
}

s16 func_8010ED20_duel01(s32 no) {
    s16 tbl[12] = { 70, 10, 50, 20, 30, 90, 10, 10, 20, 80, 60, 30 };

    return tbl[no];
}

s32 func_8010EDA0_duel01(void) {
    GW_PLAYER *player;
    s32 result;
    s32 roll;
    s32 i;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    result = -1;
    roll = func_800EFE20_name_81(10.0f);
    switch (player->cpu_difficulty) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            /* Both prize bytes (gamblePrize, duelNo) unset, read as one big-endian word. */
            if ((*(u32 *)&player->stats.prize.gamblePrize & 0xFFFF0000) != 0xFFFF0000) {
                if (roll < 6) {
                    if (player->stats.prize.gamblePrize != -1) {
                        result = player->stats.prize.gamblePrize;
                    }
                    if (player->stats.prize.duelNo != -1) {
                        result = player->stats.prize.duelNo;
                    }
                    break;
                }
                if (roll < 8) {
                    for (i = 0; D_80118760_duel01[i * 2] != -1; i++) {
                        if (D_80118760_duel01[i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                            break;
                        }
                    }
                    result = D_80118760_duel01[i * 2];
                    break;
                }
            }
            for (i = 0; D_8011885C_duel01[player->chr][i].value != -1; i++) {
                if (D_8011885C_duel01[player->chr][i].chance > func_800EFE20_name_81(100.0f)) {
                    break;
                }
            }
            result = D_8011885C_duel01[player->chr][i].value;
            break;
    }
    if (result == -1) {
        result = func_800EFE20_name_81(12.0f);
    }
    if (result < 0 || result >= 12) {
        result = 0;
    }
    return result;
}

// float constants: retail keeps 64.0f and 3.0f out of registers (loop hoisting), frame 8 bytes larger (masked 24)
#ifdef NON_MATCHING
void func_8010EFBC_duel01(void) {
    s32 *data;
    f32 angle1;
    f32 angle2;
    s32 win;
    s16 r;
    s16 g;
    s16 b;

    r = 0x43;
    data = HuPrcCurrentGet()->user_data;
    angle2 = 0.0f;
    angle1 = 90.0f;
    win = data[0];
    /* The window id's low half (big-endian s16 at +2). */
    func_8005FBF8_main(((s16 *)data)[1], 0x43, 0x80, 1);
    while (TRUE) {
        if (D_8011889C_duel01 != 0) {
            g = sindf(angle1) * 128.0f;
            if (g < 0) {
                g = -g;
            }
            angle1 += 6.0f;
            if (angle1 > 360.0f) {
                angle1 -= 360.0f;
            }
            b = sindf(angle2) * 64.0f;
            if (b < 0) {
                b = -b;
            }
            angle2 += 3.0f;
            if (angle2 > 360.0f) {
                angle2 -= 360.0f;
            }
            func_8005FBF8_main(win, (u8)r, (u8)g, (u8)b);
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EFBC_duel01);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010F12C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010F99C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80110068_duel01);

void func_80110B7C_duel01(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110068_duel01(0);
    }
}

void func_80110BD8_duel01(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if ((MBDGetCurrentPlayerIndex() == 1) && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110068_duel01(1);
    }
}



INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F60_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F6C_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F84_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FB4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE8_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FF0_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119010_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119014_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801190FC_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801191E4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801192CC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80110C3C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80111DFC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801123E8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801124D8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80112514_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80112590_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801125CC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011264C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801129C8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80112BB4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80112DA0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801135D8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801138D0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011390C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80113CAC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801147FC_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801193E8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80115850_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801159F8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80116484_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119410_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117480_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117624_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801179AC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117D3C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117DDC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117E7C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117ED8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117FFC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118058_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118178_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801181C4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118210_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011825C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801182A8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801182E4_duel01);

void func_80118320_duel01(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118328_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118414_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118530_duel01);
