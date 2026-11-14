#include "common.h"
#include "inst.h"

/* Process: the host character (model 0xA0075 with its motions and texture animation) beside
   the board; runs its handler (D_8010DDE0_inst.func) every frame. */
void func_80108350_inst(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x19, 5, 5, -1, NULL);
    D_8010DDE0_inst.obj = obj;
    obj->model[0] = func_8000B108_main(0xA0075, 0x16A9);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0xA0077);
    func_8000B460_main(obj, 2, 0xA0078);
    func_8000B460_main(obj, 3, 0xA0079);
    func_8001C5B4_main(obj->model[0], obj->motion[1]);
    func_8001C814_main(obj->model[0], 2, 2);
    data = DataRead(0xA007E);
    D_8010DC20_inst.anim = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_80032FC0_main(D_8010DC22_inst, 1, 0);
    func_80032FF8_main(D_8010DC22_inst, 0);
    D_8010DC28_inst = func_80032694_main(HmfModelData[obj->model[0]].hmf, D_8010DC22_inst, 0, "c204n_0_DEF");
    D_8010DC20_inst.anim = D_800D1714_main[D_8010DC20_inst.anim].unk_00;
    data = DataRead(0xA007F);
    D_8010DC20_inst.unk4 = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80108A18_inst(obj->model[0], D_8010DC28_inst, D_8010DC22_inst);
    obj->trans.x = -86.0f;
    obj->trans.y = -148.0f;
    obj->trans.z = 253.0f;
    obj->rot.x = -20.0f;
    obj->rot.y = 15.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.5f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->scale.x = obj->scale.y = obj->scale.z = 0.4f;
    Hu3DModelScaleSet(obj->model[0], 0.4f, 0.4f, 0.4f);
    func_8001C258_main(obj->model[0], 4, 4);
    if (D_8010D408_inst == 1) {
        func_8001C5B4_main(obj->model[0], obj->motion[3]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C258_main(obj->model[0], 4, 0);
        obj->trans.x = -86.0f;
        obj->trans.y = 52.0f;
        obj->trans.z = 253.0f;
        obj->rot.x = -20.0f;
        obj->rot.y = 15.0f;
        D_8010DDE0_inst.func = func_80108A10_inst;
    } else {
        D_8010DDE0_inst.func = func_8010872C_inst;
    }
    while (TRUE) {
        D_8010DDE0_inst.func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_8010872C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_80108808_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_80108870_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_80108954_inst);

void func_80108A10_inst(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_80108A18_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_80108AF0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_801094B0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_801097DC_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_8010986C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_801098D8_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_801099C0_inst);

void func_80109A84_inst(void) {
}
