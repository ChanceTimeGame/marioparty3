#include "common.h"

void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_80032FC0_main(s16, u8, u8);

void func_80109E94_inst(omObjData *obj);
void func_80109F50_inst(omObjData *obj);
void func_8010A000_inst(omObjData *obj);
void func_8010A0E8_inst(omObjData *obj);
void func_8010A1BC_inst(omObjData *obj);
void func_8010C848_inst(void);
void func_8010C8D0_inst(void);

extern s8 D_8010D408_inst;
extern s8 D_8010D40A_inst;
extern s32 D_8010D540_inst;
extern s32 D_8010D544_inst;
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

void func_80109E94_inst(omObjData *obj) {
    obj->trans.x = (D_8010D40A_inst == 3) ? -86.0f : -91.0f;
    obj->trans.y = (D_8010D40A_inst == 3) ? -150.0f : -164.0f;
    obj->trans.z = 210.0f;
    obj->rot.x = -20.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    D_8010DDD4_inst = func_80109F50_inst;
}

void func_80109F50_inst(omObjData *obj) {
    if (++D_8010D540_inst >= 110) {
        func_8001C5B4_main(obj->model[0], obj->motion[1]);
        func_8001C814_main(obj->model[0], 2, 0);
        func_8001C258_main(obj->model[0], 4, 0);
        func_8001C258_main(obj->model[1], 4, 0);
        HuAudFXPlay(0x25B);
        D_8010DDD4_inst = func_8010A000_inst;
        D_8010D540_inst = 0;
        func_8010C8D0_inst();
    }
}

void func_8010A000_inst(omObjData *obj) {
    D_8010D544_inst++;
    obj->trans.y = sindf(D_8010D544_inst * 5) * 200.0f + ((D_8010D40A_inst == 3) ? -150.0f : -164.0f);
    if (D_8010D544_inst > 16) {
        obj->trans.y = (D_8010D40A_inst == 3) ? 50.0f : 36.0f;
        D_8010D544_inst = 0;
        D_8010DDD4_inst = func_8010A0E8_inst;
    }
}

void func_8010A0E8_inst(omObjData *obj) {
    s16 model = obj->model[0];

    if (D_800CCF58_main[HmfModelData[model].unk02].unk02 <= HmfModelData[model].unk40 + 15.0f) {
        func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
        func_8010C848_inst();
        D_8010DDD4_inst = func_8010A1BC_inst;
    }
}

void func_8010A1BC_inst(omObjData *obj) {
}
