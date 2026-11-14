#include "common.h"

void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_80032FC0_main(s16, u8, u8);

void func_80109E94_inst(omObjData *obj);
void func_8010A0E8_inst(omObjData *obj);

extern s8 D_8010D408_inst;
extern s8 D_8010D40A_inst;
extern s32 D_8010DC40_inst;
extern omObjData *D_8010DDD0_inst;
extern void (*D_8010DDD4_inst)(omObjData *);

/* NON_MATCHING: retail reads the low half of D_8010DC40_inst through its own label (D_8010DC42) at
 * each use; the endian-neutral (s16) read here makes GCC keep &D_8010DC40_inst+2 in s0. Logic matches. */
#ifdef NON_MATCHING
void func_80109A90_inst(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x19, 5, 8, -1, NULL);
    D_8010DDD0_inst = obj;
    obj->model[0] = func_8000B108_main(0xA00A5, 0x16A9);
    func_8000B460_main(obj, 0, 0xA00B4);
    func_8000B460_main(obj, 1, 0xA00B5);
    if (D_8010D40A_inst == 3) {
        obj->model[1] = func_8000B108_main(0x170047, 0x16B9);
        func_8001C258_main(obj->model[1], 0x4000, 0x4000);
        func_8001C814_main(obj->model[1], 2, 2);
        func_8001C258_main(obj->model[1], 4, 4);
        func_8001EF6C_main(obj->model[1], obj->model[0], "item_hook");
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    data = DataRead(0xA00B8);
    D_8010DC40_inst = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "c164m_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_80032FC0_main((s16)D_8010DC40_inst, 1, 0);
    func_80032FF8_main((s16)D_8010DC40_inst, 0);
    obj->trans.x = (D_8010D40A_inst == 3) ? -86.0f : -91.0f;
    obj->trans.y = (D_8010D40A_inst == 3) ? -150.0f : -164.0f;
    obj->trans.z = 210.0f;
    obj->rot.x = -20.0f;
    obj->rot.y = 15.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.5f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->scale.x = obj->scale.y = obj->scale.z = 0.4f;
    Hu3DModelScaleSet(obj->model[0], 0.4f, 0.4f, 0.4f);
    func_8001C258_main(obj->model[0], 4, 4);
    if (D_8010D408_inst == 1) {
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C258_main(obj->model[0], 4, 0);
        func_8001C258_main(obj->model[1], 4, 0);
        obj->trans.x = (D_8010D40A_inst == 3) ? -86.0f : -91.0f;
        obj->trans.y = (D_8010D40A_inst == 3) ? 50.0f : 36.0f;
        obj->trans.z = 210.0f;
        obj->rot.x = -20.0f;
        obj->rot.y = 15.0f;
        D_8010DDD4_inst = func_8010A0E8_inst;
    } else {
        D_8010DDD4_inst = func_80109E94_inst;
    }
    while (TRUE) {
        D_8010DDD4_inst(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_80109A90_inst);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_80109E94_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_80109F50_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010A000_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010A0E8_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010A1BC_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010A1D0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010A750_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010AC04_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010AC30_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010AD78_inst);

void func_8010B038_inst(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010D9C8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010D9E8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DA24_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DA34_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DA44_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DA54_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DA64_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DA74_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DA84_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DA94_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DAA4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DAB0_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DABC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DAC8_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010B040_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010B0FC_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010B10C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010B118_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010B124_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010B2A4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010B628_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010B990_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010BE28_inst);

void func_8010BE70_inst(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010BE78_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DAF8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DB04_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DB10_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DB1C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DB24_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E2C50", D_8010DB30_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010C124_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010C55C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010C5C4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010C848_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010C890_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010C8B4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010C8D0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010C8E0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010CA74_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010CBB8_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010CC14_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010CDE4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010CED0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010CF14_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010CF98_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010CFF4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010D044_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E2C50", func_8010D1D4_inst);
