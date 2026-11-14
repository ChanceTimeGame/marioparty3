#include "common.h"
#include "inst.h"

extern s32 D_8010D520_inst;
extern s32 D_8010D524_inst;
void func_80108808_inst(omObjData *);
void func_80108870_inst(omObjData *);
void func_80108954_inst(omObjData *);
void func_8010C848_inst(void);
extern InstBoard D_8010DDE8_inst; /* the second host */
extern s32 D_8010D530_inst;
extern s32 D_8010D534_inst;
void func_8010986C_inst(omObjData *);
void func_801098D8_inst(omObjData *);
void func_801099C0_inst(omObjData *);
void func_80109A84_inst(omObjData *);
void func_8010C8D0_inst(void);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);

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

/* Host handlers: below the screen, waits, jumps up (sound 0x2A7), lands and idles. */
void func_8010872C_inst(omObjData *obj) {
    obj->trans.x = -86.0f;
    obj->trans.y = -148.0f;
    obj->trans.z = 253.0f;
    obj->rot.x = -20.0f;
    obj->rot.y = 15.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C5B4_main(obj->model[0], obj->motion[1]);
    func_8001C814_main(obj->model[0], 2, 2);
    func_80108A18_inst(obj->model[0], D_8010DC28_inst, D_8010DC22_inst);
    D_8010DDE0_inst.func = func_80108808_inst;
}

void func_80108808_inst(omObjData *obj) {
    if (++D_8010D520_inst >= 100) {
        func_8001C258_main(obj->model[0], 4, 0);
        HuAudFXPlay(0x135);
        D_8010DDE0_inst.func = func_80108870_inst;
        D_8010D520_inst = 0;
        func_8010C8D0_inst();
    }
}

void func_80108870_inst(omObjData *obj) {
    D_8010D524_inst++;
    obj->trans.y = sindf(D_8010D524_inst * 5) * 200.0f + -148.0f;
    if (D_8010D524_inst >= 17) {
        obj->trans.y = 52.0f;
        D_8010D524_inst = 0;
        func_8001C5B4_main(obj->model[0], obj->motion[2]);
        func_8001C814_main(obj->model[0], 2, 0);
        HuPrcSleep(10);
        HuAudFXPlay(0x2A7);
        D_8010DDE0_inst.func = func_80108954_inst;
    }
}

void func_80108954_inst(omObjData *obj) {
    s16 m = obj->model[0];
    f32 frame = HmfModelData[m].unk40;

    if (D_800CCF58_main[HmfModelData[m].unk02].unk02 <= frame) {
        func_8001C5B4_main(m, obj->motion[3]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8010C848_inst();
        D_8010DDE0_inst.func = func_80108A10_inst;
    }
}

void func_80108A10_inst(omObjData *obj) {
}

/* Starts texture animation anim of model at frame (frame -1: plays it as it is). */
#ifdef NON_MATCHING
/* Instruction-identical, but retail has a nop after it (func_80108AF0_inst is 16-byte
   aligned in retail; no file split explains it, see the report). */
void func_80108A18_inst(s16 model, s16 anim, s16 frame) {
    TexAnimSlot *slot;

    if (anim >= 0) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            slot = &D_800D1714_main[anim];
            slot->unk_00 = frame;
            slot->unk_04 = 0;
            slot->unk_0A = 0;
            slot->unk_06 = 0;
            slot->unk_02 = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_80108A18_inst);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_80108AF0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_801094B0_inst);

/* Second host's handlers (the 2-player screen): waits, jumps up (sound 0x298), lands. */
void func_801097DC_inst(omObjData *obj) {
    obj->trans.x = -91.0f;
    obj->trans.y = -171.0f;
    obj->trans.z = 210.0f;
    obj->rot.x = -20.0f;
    obj->rot.y = 15.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    D_8010DDE8_inst.func = func_8010986C_inst;
}

void func_8010986C_inst(omObjData *obj) {
    if (++D_8010D530_inst >= 100) {
        D_8010DDE8_inst.func = func_801098D8_inst;
        D_8010D530_inst = 0;
        func_8001C258_main(obj->model[0], 4, 0);
        HuAudFXPlay(0x298);
        func_8010C8D0_inst();
    }
}

void func_801098D8_inst(omObjData *obj) {
    D_8010D534_inst++;
    obj->trans.y = sindf(D_8010D534_inst * 5) * 200.0f + -171.0f;
    if (D_8010D534_inst == 13) {
        func_8001C5B4_main(obj->model[0], obj->motion[4]);
        func_8001C814_main(obj->model[0], 2, 0);
    }
    if (D_8010D534_inst >= 17) {
        obj->trans.y = 29.0f;
        D_8010D534_inst = 0;
        D_8010DDE8_inst.func = func_801099C0_inst;
    }
}

/* Retail indexes HmfModelData with the motion id (obj->motion[3]) for the blend length. */
#ifdef NON_MATCHING
/* Masked 2: the HmfModelData load is scheduled before the model index. */
void func_801099C0_inst(omObjData *obj) {
    HmfModel *models;
    HmfModel *model;
    s16 m;

    m = obj->model[0];
    models = HmfModelData;
    model = &models[m];

    if (D_800CCF58_main[model->unk02].unk02 <= model->unk40) {
        func_8001C624_main(m, models[obj->motion[3]].unk02, 0, 30, 2);
        func_8010C848_inst();
        D_8010DDE8_inst.func = func_80109A84_inst;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E1510", func_801099C0_inst);
#endif

void func_80109A84_inst(omObjData *obj) {
}
