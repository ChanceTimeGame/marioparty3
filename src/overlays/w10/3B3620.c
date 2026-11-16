#include "common.h"
#include "game/board.h"
#include "game/object.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/FA250.h"

// board h1: locals for func_801059D0_w10..func_80107F0C_w10
extern s16 D_8010B7F0_w10[4];
extern Vec D_8010B818_w10[];
extern Vec D_8010B854_w10[];
extern Object *D_8010BA24_w10;
extern Process *D_8010BA28_w10;
extern Object *D_8010BA2C_w10;
extern Object *D_8010BA30_w10;
extern Object *D_8010BA38_w10[2];

void func_800461B4_main(s16 model);
void func_8001FA68_main(s16 model);

void func_801059D0_w10(void) {
    GwSystem.current_board_index = 6;
    omInitObjMan(10, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

void func_80105A0C_w10(void) {
    s32 i;

    omInitObjMan(10, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->chr = D_8010B7F0_w10[i];
    }
    omOvlReturnEx(1);
}

void func_80105AB8_w10(void) {
    Object *obj;

    if (D_8010BA24_w10 == NULL) {
        obj = MBModelCreate(0x3A, NULL);
        func_800461B4_main(obj->omObj1->model[0]);
        MBModelTempAllocFree(obj);
        D_8010BA24_w10 = obj;
        obj->flags |= 2;
        HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
        obj->velocity.x = 10.0f;
        D_8010BA28_w10 = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
        HuVecCopy3F(&obj->coords, &MBMasuGet(0x25)->coords);
    }
}

void func_80105B70_w10(void) {
    D_8010BA24_w10 = NULL;
    func_80105AB8_w10();
}

void func_80105B90_w10(void) {
    Object *obj;

    if (D_8010BA2C_w10 == NULL) {
        obj = MBModelCreate(10, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_8010BA2C_w10 = obj;
        obj->flags |= 2;
        obj->velocity.x = 15.0f;
        HuVecCopy3F(&obj->coords, &MBMasuGet(0x24)->coords);
        MBModelDispOff(obj);
    }
}

void func_80105C28_w10(void) {
    D_8010BA2C_w10 = NULL;
    func_80105B90_w10();
}

void func_80105C48_w10(s16 arg0) {
    Object *obj;

    if (D_8010BA38_w10[arg0] == NULL) {
        if (D_8010BA30_w10 == NULL) {
            obj = MBModelCreate(0x1E, NULL);
            MBModelTempAllocFree(obj);
            D_8010BA30_w10 = obj;
        } else {
            obj = MBModelLinkCreate(D_8010BA30_w10);
        }
        D_8010BA38_w10[arg0] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &MBMasuGet(0x2F)->coords);
        HuVecAdd(&obj->coords, &D_8010B818_w10[arg0], &obj->coords);
        obj->omObj1->rot.x = D_8010B854_w10[arg0].x;
        obj->omObj1->rot.z = D_8010B854_w10[arg0].z;
    }
}

void func_80105D6C_w10(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_8010BA38_w10[i] = NULL;
        func_80105C48_w10(i);
    }
}

void func_80105DC4_w10(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    HuPrcSleep(3);
}

void func_80105E08_w10(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105E10_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105F20_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105F64_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105FA0_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105FDC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801061E8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106230_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106314_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010649C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801064C8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106574_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106670_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010669C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801066E8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106730_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106774_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010681C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106838_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010687C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106908_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106DEC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106ED8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106F40_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106F7C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106FE0_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107028_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801070B8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010714C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107228_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107344_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107350_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801073C8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107444_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107780_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107ABC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107D64_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107F0C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801084CC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80108F28_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109050_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109444_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010AF68_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B12C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B434_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B5A4_w10);
