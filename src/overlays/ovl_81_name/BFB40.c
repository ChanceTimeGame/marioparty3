#include "common.h"
#include "ovl_81.h"

// duel n1: Duel Mode's board models (ovl_80 ECA50's MBModel* / MBMotion* in an older, MP2-like form).

/* A Duel Mode board model. Its first 0x44 bytes are laid out as `Object`, which the header's
 * prototypes and the other units use; Duel Mode keeps a motion count before the two motion ids. */
typedef struct DuelModel {
    /* 0x00 */ struct DuelModel *prev;
    /* 0x04 */ struct DuelModel *next;
    /* 0x08 */ u8 id;
    /* 0x09 */ s8 unk9;
    /* 0x0A */ u16 flags;
    /* 0x0C */ Vec coords;
    /* 0x18 */ Vec rot;
    /* 0x24 */ Vec scale;
    /* 0x30 */ Vec velocity; /* x: jump height, y: jump speed, z: jump acceleration */
    /* 0x3C */ omObjData *omObj1;
    /* 0x40 */ omObjData *omObj2; /* shadow */
    /* 0x44 */ s16 mtncnt; /* -1: no motions */
    /* 0x46 */ s16 baseMot;
    /* 0x48 */ s16 curMot;
} DuelModel; // sizeof 0x4C

typedef struct DuelModelWork {
    /* 0x00 */ DuelModel *model;
    /* 0x04 */ f32 scale;
} DuelModelWork; // sizeof 0x08

typedef struct DuelModelFile {
    /* 0x00 */ s32 file;
    /* 0x04 */ s32 shadowFile;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 shadowScale;
} DuelModelFile; // sizeof 0x10

typedef struct DuelModelSpin {
    /* 0x00 */ DuelModel *model;
    /* 0x04 */ f32 angle;
    /* 0x08 */ f32 speed;
    /* 0x0C */ s32 frames;
} DuelModelSpin; // sizeof 0x10

typedef struct DuelModelKill {
    /* 0x00 */ DuelModel *model;
} DuelModelKill;

f32 MBDBackMdlScaleGet(void);
f32 func_800D76D0_name_81(Vec *arg0);
void func_800EB708_name_81(Vec *arg0, Vec *arg1, Vec *arg2);
void func_800D8E34_name_81(DuelModel *arg0);
void func_800D8EB8_name_81(DuelModel *arg0);
void func_800D85B4_name_81(omObjData *arg0);
void func_800D87E8_name_81(omObjData *arg0);

extern DuelModel *D_801029C0_name_81;
extern u16 D_801029C4_name_81;
extern s16 D_801029C8_name_81[128];
extern u16 D_80105624_name_81;
extern u8 D_800D6A90_main;
extern f32 D_80100E10_name_81;
extern f32 D_80100E14_name_81;

/* model files: { file, shadow file, scale, shadow scale } */
const DuelModelFile D_80101C48_name_81[] = {
    { 0x200A2, 9, 1.0f, 0.9f }, { 0x300A2, 9, 1.0f, 0.9f }, { 0x700A2, 9, 1.0f, 1.2f }, { 0x400A2, 9, 1.0f, 1.1f },
    { 0x500A2, 9, 1.0f, 1.1f }, { 0x600A2, 9, 0.9f, 1.0f }, { 0x800A2, 9, 1.0f, 0.9f }, { 0x90003, 9, 1.0f, 1.2f },
    { 0xA002E, 9, 0.7f, 1.4f }, { 0xA0000, 9, 0.9f, 0.9f }, { 0xA00C5, 9, 0.6f, 1.2f }, { 0xA00CE, 1245791, 0.4f, 0.0f },
    { 0xA00A5, 9, 1.2f, 1.0f }, { 0xA00E7, 1245791, 0.9f, 1.8f }, { 0x13014C, 9, 1.6666666f, 0.0f }, { 0x200A0, 9, 1.0f, 0.9f },
    { 0x300A0, 9, 1.0f, 0.9f }, { 0x700A0, 9, 1.0f, 1.2f }, { 0x400A0, 9, 1.0f, 1.1f }, { 0x500A0, 9, 1.0f, 1.1f },
    { 0x600A0, 9, 1.0f, 1.5f }, { 0x800A0, 9, 1.0f, 0.9f }, { 0x90000, 9, 1.0f, 1.2f }, { 0x130145, 9, 1.0f, 0.0f },
    { 0x130146, 9, 1.0f, 0.0f }, { 0x130147, 9, 1.0f, 0.0f }, { 0x1301CA, 9, 0.65f, 0.0f }, { 0xA0022, 9, 1.2f, 0.7f },
    { 0xB0028, 9, 1.0f, 0.0f }, { 0x1301CC, 9, 1.0f, 1.0f }, { 0xA0000, 9, 1.0f, 0.0f }, { 0xB000D, 9, 3.0f, 0.0f },
    { 0xA00FF, 9, 1.2f, 0.7f }, { 0xB0026, 9, 1.0f, 0.0f }, { 0xB0027, 9, 1.0f, 0.0f }, { 0xA005B, 9, 1.0f, 1.0f },
    { 0xA0136, 9, 1.0f, 0.8f }, { 0xA008E, 9, 1.0f, 1.0f }, { 0xA00C1, 9, 1.2f, 1.0f }, { 0xA00C3, 9, 1.2f, 1.0f },
    { 0xA00C2, 9, 1.2f, 1.0f }, { 0xA0101, 9, 0.8f, 1.0f }, { 0xA00D9, 9, 0.6f, 1.0f }, { 0xA013F, 9, 2.0f, 1.0f },
    { 0xA010D, 9, 0.6f, 1.0f }, { 0x130149, 9, 1.6666666f, 0.0f }, { 0x13014A, 9, 1.6666666f, 0.0f }, { 0x130150, 9, 1.6666666f, 0.0f },
    { 0x130151, 9, 1.6666666f, 0.0f }, { 0x130152, 9, 1.6666666f, 0.0f }, { 0x130141, 9, 1.6666666f, 0.0f }, { 0x130142, 9, 1.6666666f, 0.0f },
    { 0xA011B, 9, 1.6666666f, 3.3333333f }, { 0xB0006, 9, 1.6666666f, 0.0f }, { 0xB0007, 9, 1.6666666f, 0.0f }, { 0xB0008, 9, 1.6666666f, 0.0f },
    { 0xB0009, 9, 1.6666666f, 0.0f }, { 0xB000A, 9, 1.6666666f, 0.0f }, { 0xB000B, 9, 1.6666666f, 0.0f }, { 0xA0122, 9, 1.6666666f, 2.0f },
    { 0x130143, 9, 0.5f, 0.0f }, { 0xA0063, 9, 1.5f, 0.0f }, { 0xA0075, 9, 1.5f, 1.5f }, { 0x130144, 9, 1.0f, 0.0f },
    { 0x13014C, 9, 1.6666666f, 0.0f }, { 0x13014D, 9, 1.6666666f, 0.0f }, { 0x13014E, 9, 1.6666666f, 0.0f }, { 0x13014F, 9, 1.6666666f, 0.0f },
    { 0xB001D, 9, 1.6666666f, 0.0f }, { 0xB001E, 9, 1.6666666f, 0.0f }, { 0xB001F, 9, 1.6666666f, 0.0f }, { 0xB0020, 9, 1.6666666f, 0.0f },
    { 0xB0021, 9, 1.6666666f, 0.0f }, { 0xB0022, 9, 1.6666666f, 0.0f }, { 0xB0017, 9, 1.6666666f, 0.0f }, { 0xB0018, 9, 1.6666666f, 0.0f },
    { 0xB0019, 9, 1.6666666f, 0.0f }, { 0xB001A, 9, 1.6666666f, 0.0f }, { 0xB001B, 9, 1.6666666f, 0.0f }, { 0xB0010, 9, 1.6666666f, 0.0f },
    { 0xB0011, 9, 1.6666666f, 0.0f }, { 0xB0012, 9, 1.6666666f, 0.0f }, { 0xB0013, 9, 1.6666666f, 0.0f }, { 0xB001C, 9, 1.6666666f, 0.0f },
    { 0xB000E, 9, 1.6666666f, 0.0f }, { 0xB000F, 9, 1.6666666f, 0.0f }, { 0xB0016, 9, 1.6666666f, 0.0f }, { 0xB0015, 9, 1.0f, 0.5f },
    { 0xB0014, 9, 1.6666666f, 0.0f }, { 0xB0029, 9, 1.6666666f, 0.0f }, { 0x330008, 9, 3.3333333f, 0.0f }, { 0xB002A, 9, 1.6666666f, 0.0f },
};

void func_800D7D70_name_81(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_801029C8_name_81); i++) {
        D_801029C8_name_81[i] = 0;
    }
}

s16 func_800D7DA0_name_81(s16 arg0) {
    D_801029C8_name_81[arg0]++;
    return arg0;
}

s16 func_800D7DC8_name_81(s32 arg0) {
    s16 res = func_8001F1FC_main(DataRead(arg0), 8);
    D_801029C8_name_81[res]++;
    return res;
}

void func_800D7E14_name_81(s16 arg0) {
    if (D_801029C8_name_81[arg0] != 0) {
        if (--D_801029C8_name_81[arg0] == 0) {
            func_8002D4B8_main(arg0);
        }
    }
}

s16 func_800D7E68_name_81(s16 arg0) {
    if (D_801029C8_name_81[arg0] != 0) {
        D_801029C8_name_81[arg0]++;
        return arg0;
    }
    return -1;
}

void func_800D7EB8_name_81(void) {
    D_801029C0_name_81 = NULL;
    D_801029C4_name_81 = 0;
    D_80105624_name_81 = 1;
    func_800D7D70_name_81();
    func_800D87DC_name_81(100.0f);
    func_800D85A8_name_81(1.0f);
}

void func_800D7F0C_name_81(void) {
    while (D_801029C0_name_81 != NULL) {
        func_800D8F3C_name_81((Object *)D_801029C0_name_81);
    }
}

DuelModel *func_800D7F4C_name_81(void) {
    DuelModel *model;

    model = HuMemMemoryAllocTemp(sizeof(DuelModel));
    if (model != NULL) {
        D_801029C4_name_81++;
        model->prev = D_801029C0_name_81;
        model->next = NULL;
        if (D_801029C0_name_81 != NULL) {
            D_801029C0_name_81->next = model;
        }
        D_801029C0_name_81 = model;
        model->flags = 8;
        HuVecCopyXYZ(&model->coords, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&model->rot, 0.0f, 0.0f, 1.0f);
        HuVecCopyXYZ(&model->scale, 1.0f, 1.0f, 1.0f);
        model->velocity.x = 0.0f;
        model->velocity.y = 0.0f;
        model->velocity.z = 0.0f;
        model->baseMot = -1;
        model->curMot = -1;
    }
    return model;
}

Object *func_800D8010_name_81(u8 id, s32 *motions) {
    DuelModel *model;
    omObjData *obj;
    DuelModelWork *work;
    s16 mdl;
    u16 mtncnt;
    s16 i;

    mtncnt = 0;
    model = func_800D7F4C_name_81();
    if (model != NULL) {
        model->id = id;
        if (motions != NULL) {
            mtncnt = *motions++;
            model->mtncnt = mtncnt;
        } else {
            model->mtncnt = -1;
        }
        obj = model->omObj1 = omAddObj(0x4000, 1, mtncnt, -1, func_800D85B4_name_81);
        mdl = func_8000B108_main(D_80101C48_name_81[model->id].file, 0x6A9);
        omSetStatBit(obj, 0x80);
        obj->model[0] = mdl;
        omSetRot(obj, 0.0f, 0.0f, 0.0f);
        func_8001C814_main(mdl, 2, 2);
        func_8001C8A8_main(mdl, 1);
        Hu3DModelScaleSet(mdl, 0.0f, 0.0f, 0.0f);
        if (HmfModelData[mdl].unk02 != 0xFF) {
            model->baseMot = func_800D7DA0_name_81(HmfModelData[mdl].unk02);
        }
        work = HuMemMemoryAllocTemp(sizeof(DuelModelWork));
        obj->data = work;
        work->model = model;
        work->scale = D_80101C48_name_81[model->id].scale * 0.6f;
        for (i = 0; i < (s16)mtncnt; i++) {
            obj->motion[i] = func_800D7DC8_name_81(*motions++);
        }
        if (D_80101C48_name_81[model->id].shadowScale > 0.0f) {
            obj = model->omObj2 = omAddObj(0x4000, 1, 0, -1, func_800D87E8_name_81);
            mdl = func_8000B108_main(D_80101C48_name_81[model->id].shadowFile, 0x229);
            omSetStatBit(obj, 0x80);
            obj->model[0] = mdl;
            omSetRot(obj, 0.0f, 0.0f, 0.0f);
            func_8001C8A8_main(mdl, 1);
            Hu3DModelScaleSet(mdl, 0.0f, 0.0f, 0.0f);
            work = HuMemMemoryAllocTemp(sizeof(DuelModelWork));
            obj->data = work;
            work->model = model;
            work->scale = D_80101C48_name_81[model->id].shadowScale * 0.6f;
        } else {
            model->omObj2 = NULL;
        }
    }
    return (Object *)model;
}

/* Retail never sets the new model's mtncnt here (HuMemMemoryAllocTemp does not clear it). */
Object *func_800D8314_name_81(s32 file, s32 shadowFile, f32 scale, f32 shadowScale, s32 *motions) {
    DuelModel *model;
    omObjData *obj;
    DuelModelWork *work;
    s16 mdl;
    u16 mtncnt;
    s16 i;

    mtncnt = 0;
    model = func_800D7F4C_name_81();
    if (model != NULL) {
        model->id = 0xFF;
        if (motions != NULL) {
            mtncnt = *motions++;
        }
        obj = model->omObj1 = omAddObj(0x4000, 1, mtncnt, -1, func_800D85B4_name_81);
        mdl = func_8000B108_main(file, 0x6A9);
        omSetStatBit(obj, 0x80);
        obj->model[0] = mdl;
        omSetRot(obj, 0.0f, 0.0f, 0.0f);
        func_8001C814_main(mdl, 2, 2);
        func_8001C8A8_main(mdl, 1);
        Hu3DModelScaleSet(mdl, 0.0f, 0.0f, 0.0f);
        if (HmfModelData[mdl].unk02 != 0xFF) {
            model->baseMot = func_800D7DA0_name_81(HmfModelData[mdl].unk02);
        }
        work = HuMemMemoryAllocTemp(sizeof(DuelModelWork));
        obj->data = work;
        work->model = model;
        work->scale = scale;
        for (i = 0; i < (s16)mtncnt; i++) {
            obj->motion[i] = func_800D7DC8_name_81(*motions++);
        }
        if ((shadowFile >= 0) && (shadowScale > 0.0f)) {
            obj = model->omObj2 = omAddObj(0x4000, 1, 0, -1, func_800D87E8_name_81);
            mdl = func_8000B108_main(shadowFile, 0x229);
            omSetStatBit(obj, 0x80);
            obj->model[0] = mdl;
            omSetRot(obj, 0.0f, 0.0f, 0.0f);
            func_8001C8A8_main(mdl, 1);
            Hu3DModelScaleSet(mdl, 0.0f, 0.0f, 0.0f);
            work = HuMemMemoryAllocTemp(sizeof(DuelModelWork));
            obj->data = work;
            work->model = model;
            work->scale = shadowScale;
        } else {
            model->omObj2 = NULL;
        }
    }
    return (Object *)model;
}

void func_800D85A8_name_81(f32 arg0) {
    D_80100E10_name_81 = arg0;
}

void func_800D85B4_name_81(omObjData *obj) {
    Vec2f pos2d;
    DuelModelWork *work = obj->data;
    DuelModel *model = work->model;

    if ((D_800D6A90_main == 0) || (model->flags & 0x10)) {
        if (model->velocity.z != 0.0f) {
            model->velocity.y += model->velocity.z;
            if ((model->velocity.x += model->velocity.y) < 0.0f) {
                model->velocity.x = 0.0f;
                model->velocity.y = 0.0f;
                model->velocity.z = 0.0f;
            }
        }
    }
    if (!(D_80105624_name_81 & 1)) {
        func_800D8EB8_name_81(model);
        return;
    }
    if (!(model->flags & 8)) {
        func_800D8EB8_name_81(model);
        return;
    }
    if (model->flags & 2) {
        MBDCamera3Dto2D(&model->coords, &pos2d);
        if (pos2d.x > 370.0f || pos2d.x < -50.0f || pos2d.y > 290.0f || pos2d.y < -20.0f) {
            func_800D8EB8_name_81(model);
            return;
        }
    }
    func_800D8E34_name_81(model);
    if (!(model->flags & 4)) {
        obj->rot.y = func_800D76D0_name_81(&model->rot);
    }
    obj->trans.x = model->coords.x;
    obj->trans.y = model->coords.y + model->velocity.x;
    obj->trans.z = model->coords.z;
    obj->scale.x = model->scale.x * work->scale * MBDBackMdlScaleGet() * D_80100E10_name_81;
    obj->scale.y = model->scale.y * work->scale * MBDBackMdlScaleGet() * D_80100E10_name_81;
    obj->scale.z = model->scale.z * work->scale * MBDBackMdlScaleGet() * D_80100E10_name_81;
}

void func_800D87DC_name_81(f32 arg0) {
    D_80100E14_name_81 = arg0;
}

void func_800D87E8_name_81(omObjData *obj) {
    f32 f;
    DuelModel *model;
    DuelModelWork *work;

    work = obj->data;
    model = work->model;
    f = 1.0f;
    obj->rot.y = func_800D76D0_name_81(&model->rot);
    if (model->flags & 1) {
        f = 0.0f;
    } else {
        if (model->velocity.x != 0.0f) {
            f = 1.0f - (model->velocity.x / D_80100E14_name_81);
            if (f <= 0.0f) {
                f = 0.0f;
            }
            if (f >= 1.0f) {
                f = 1.0f;
            }
        }
    }
    obj->scale.x = f * model->scale.x * work->scale * MBDBackMdlScaleGet() * D_80100E10_name_81;
    obj->scale.y = MBDBackMdlScaleGet();
    obj->scale.z = f * model->scale.z * work->scale * MBDBackMdlScaleGet() * D_80100E10_name_81;
    obj->trans.x = model->coords.x;
    obj->trans.y = model->coords.y;
    obj->trans.z = model->coords.z;
}

void func_800D8944_name_81(Object *arg0) {
    func_8001C514_main(arg0->omObj1->model[0]);
    if (arg0->omObj2 != NULL) {
        func_8001C514_main(arg0->omObj2->model[0]);
    }
}

/* Gives a board model another id: reloads its model and shadow and takes the new scales. */
void func_800D898C_name_81(DuelModel *model, u8 id) {
    s16 mdl;

    model->id = id;
    func_8001F304_main(model->omObj1->model[0], -1);
    func_8001ACDC_main(model->omObj1->model[0]);
    if (model->baseMot != -1) {
        func_800D7E14_name_81(model->baseMot);
    }
    mdl = func_8000B108_main(D_80101C48_name_81[model->id].file, 0x6A9);
    model->omObj1->model[0] = mdl;
    func_8001C814_main(mdl, 2, 2);
    func_8001C8A8_main(mdl, 1);
    ((DuelModelWork *)model->omObj1->data)->scale = D_80101C48_name_81[model->id].scale;
    if (HmfModelData[mdl].unk02 != 0xFF) {
        model->baseMot = func_800D7DA0_name_81(HmfModelData[mdl].unk02);
    } else {
        model->baseMot = -1;
    }
    if (model->omObj2 != NULL) {
        func_8001ACDC_main(model->omObj2->model[0]);
        mdl = func_8000B108_main(D_80101C48_name_81[model->id].shadowFile, 0x229);
        model->omObj2->model[0] = mdl;
        func_8001C8A8_main(mdl, 1);
        ((DuelModelWork *)model->omObj2->data)->scale = D_80101C48_name_81[model->id].shadowScale;
    }
}

/* Copies a board model (linked models). */
DuelModel *func_800D8B18_name_81(DuelModel *src) {
    DuelModel *model;
    omObjData *obj;
    DuelModelWork *work;
    s16 mdl;
    s16 i;

    model = func_800D7F4C_name_81();
    if (model != NULL) {
        model->id = src->id;
        obj = model->omObj1 = omAddObj(0x4000, 1, src->omObj1->mtncnt, -1, func_800D85B4_name_81);
        mdl = Hu3DModelLink(src->omObj1->model[0]);
        omSetStatBit(obj, 0x80);
        obj->model[0] = mdl;
        omSetRot(obj, 0.0f, 0.0f, 0.0f);
        func_8001C814_main(mdl, 2, 2);
        func_8001C8A8_main(mdl, 1);
        Hu3DModelScaleSet(mdl, 0.0f, 0.0f, 0.0f);
        if (HmfModelData[mdl].unk02 != 0xFF) {
            model->baseMot = func_800D7E68_name_81(HmfModelData[mdl].unk02);
        } else {
            model->baseMot = src->baseMot;
        }
        work = HuMemMemoryAllocTemp(sizeof(DuelModelWork));
        obj->data = work;
        work->model = model;
        if (model->id != 0xFF) {
            work->scale = D_80101C48_name_81[model->id].scale * 0.6f;
        } else {
            work->scale = 1.0f;
        }
        for (i = 0; i < src->omObj1->mtncnt; i++) {
            obj->motion[i] = func_800D7E68_name_81(src->omObj1->motion[i]);
        }
        model->mtncnt = src->mtncnt;
        if ((src->omObj2 != NULL) && (model->id != 0xFF) && (D_80101C48_name_81[model->id].shadowScale > 0.0f)) {
            obj = model->omObj2 = omAddObj(0x4000, 1, 0, -1, func_800D87E8_name_81);
            mdl = Hu3DModelLink(src->omObj2->model[0]);
            omSetStatBit(obj, 0x80);
            obj->model[0] = mdl;
            omSetRot(obj, 0.0f, 0.0f, 0.0f);
            func_8001C8A8_main(mdl, 1);
            Hu3DModelScaleSet(mdl, 0.0f, 0.0f, 0.0f);
            work = HuMemMemoryAllocTemp(sizeof(DuelModelWork));
            obj->data = work;
            work->model = model;
            work->scale = D_80101C48_name_81[model->id].shadowScale * 0.6f;
        } else {
            model->omObj2 = NULL;
        }
    }
    return model;
}

void func_800D8E34_name_81(DuelModel *arg0) {
    func_8001C258_main(arg0->omObj1->model[0], 4, 0);
    if (arg0->omObj2 != NULL) {
        func_8001C258_main(arg0->omObj2->model[0], 4, 0);
    }
}

void func_800D8E88_name_81(Object *arg0) {
    func_800D8E34_name_81((DuelModel *)arg0);
    arg0->flags |= 8;
}

void func_800D8EB8_name_81(DuelModel *arg0) {
    func_8001C258_main(arg0->omObj1->model[0], 4, 4);
    if (arg0->omObj2 != NULL) {
        func_8001C258_main(arg0->omObj2->model[0], 4, 4);
    }
}

void func_800D8F0C_name_81(Object *arg0) {
    func_800D8EB8_name_81((DuelModel *)arg0);
    arg0->flags &= ~8;
}

void func_800D8F3C_name_81(Object *arg0) {
    DuelModel *model = (DuelModel *)arg0;
    s32 i;

    if (D_801029C0_name_81 != NULL) {
        if (model->prev != NULL) {
            model->prev->next = model->next;
        }
        if (model->next != NULL) {
            model->next->prev = model->prev;
        } else {
            D_801029C0_name_81 = model->prev;
        }
        func_8001F304_main(model->omObj1->model[0], -1);
        func_8001ACDC_main(model->omObj1->model[0]);
        if (model->omObj2 != NULL) {
            func_8001ACDC_main(model->omObj2->model[0]);
        }
        for (i = 0; i < model->omObj1->mtncnt; i++) {
            func_800D7E14_name_81(model->omObj1->motion[i]);
        }
        if (model->baseMot != -1) {
            func_800D7E14_name_81(model->baseMot);
        }
        HuMemMemoryFreeTemp(model->omObj1->data);
        model->omObj1->data = NULL;
        omDelObj(model->omObj1);
        if (model->omObj2 != NULL) {
            HuMemMemoryFreeTemp(model->omObj2->data);
            model->omObj2->data = NULL;
            omDelObj(model->omObj2);
        }
        HuMemMemoryFreeTemp(model);
        D_801029C4_name_81 -= 1;
    }
}

/* 1 if the model is still in the model list. */
s32 func_800D9098_name_81(DuelModel *arg0) {
    DuelModel *model;

    for (model = D_801029C0_name_81; model != NULL; model = model->prev) {
        if (model == arg0) {
            return 1;
        }
    }
    return 0;
}

// decomp-permuter
void func_800D90D0_name_81(Object *arg0, s16 arg1, u16 arg2)
{
  int new_var3;
  u16 new_var;
  s16 new_var2;
  DuelModel *model = (DuelModel *) arg0;
  u16 mot;
  new_var2 = arg1;
  new_var = arg2;
  if (model->mtncnt != (-1))
  {
    new_var3 = 1;
    if (new_var2 == (-1))
    {
      mot = model->baseMot;
      model->curMot = new_var2;
    }
    else
      if (new_var2 <= (model->mtncnt - new_var3))
    {
      mot = model->omObj1->motion[new_var2];
      model->curMot = new_var2;
    }
    else
    {
      return;
    }
    func_8001F304_main(model->omObj1->model[0], mot);
    func_8001C814_main(model->omObj1->model[0], -1, new_var);
  }
}

void func_800D918C_name_81(Object *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    DuelModel *model = (DuelModel *)arg0;
    u16 mot;

    if (model->mtncnt != -1) {
        if (arg1 == -1) {
            mot = model->baseMot;
            model->curMot = arg1;
        } else if (arg1 <= model->mtncnt - 1) {
            mot = model->omObj1->motion[arg1];
            model->curMot = arg1;
        } else {
            return;
        }
        func_8001C624_main(model->omObj1->model[0], mot, arg2, arg3, arg4);
    }
}

u16 func_800D9234_name_81(DuelModel *arg0) {
    u16 ret = 0;

    if (HmfModelData[arg0->omObj1->model[0]].unk40 == D_800CCF58_main[HmfModelData[arg0->omObj1->model[0]].unk02].unk02) {
        ret = 1;
    }
    return ret;
}

u16 func_800D92A8_name_81(DuelModel *arg0) {
    u16 ret;

    ret = 0;
    if (HmfModelData[arg0->omObj1->model[0]].unk40 == 0.0f) {
        ret = 1;
    }
    return ret;
}

/* Turns a board model over work[1] frames. */
void func_800D92F8_name_81(omObjData *obj) {
    DuelModel *model;

    model = obj->data;
    if (--obj->work[1] == 0) {
        model->rot.x = obj->rot.x;
        model->rot.y = obj->rot.y;
        model->rot.z = obj->rot.z;
        obj->data = NULL;
        omDelObj(obj);
        return;
    }
    obj->scale.y += obj->scale.x;
    model->rot.x = sindf(obj->scale.y);
    model->rot.y = 0.0f;
    model->rot.z = cosdf(obj->scale.y);
}

/* Starts turning a board model towards arg1 over arg2 frames. */
omObjData *func_800D9384_name_81(DuelModel *model, Vec *arg1, s32 arg2) {
    Vec dir;
    f32 from;
    f32 to;
    omObjData *obj;

    func_800EB708_name_81(&model->coords, arg1, &dir);
    obj = omAddObj(0x1000, 0, 0, -1, func_800D92F8_name_81);
    obj->work[1] = arg2;
    obj->rot.x = dir.x;
    obj->rot.y = dir.y;
    obj->rot.z = dir.z;
    from = func_800D76D0_name_81(&model->rot);
    to = func_800D76D0_name_81(&dir);
    if (to < from) {
        if ((from - to) >= 180.0f) {
            to += 360.0f;
        }
    } else if ((to - from) >= 180.0f) {
        from += 360.0f;
    }
    obj->scale.y = from;
    obj->scale.x = (to - from) / (f32)arg2;
    obj->data = model;
    return obj;
}

/* Spins a board model about its Y axis through its matrix (frames < 0: forever). */
void func_800D94C4_name_81(void) {
    DuelModelSpin *spin;
    DuelModel *model;
    HmfModel *mdl;
    f32 angle;
    f32 speed;
    s32 frames;

    spin = HuPrcCurrentGet()->user_data;
    model = spin->model;
    angle = spin->angle;
    speed = spin->speed;
    frames = spin->frames;
    while (frames != 0) {
        sincosdf(angle, &HmfModelData[model->omObj1->model[0]].mtx[8], &HmfModelData[model->omObj1->model[0]].mtx[10]);
        HmfModelData[model->omObj1->model[0]].mtx[2] = -HmfModelData[model->omObj1->model[0]].mtx[8];
        mdl = &HmfModelData[model->omObj1->model[0]];
        mdl->mtx[0] = mdl->mtx[10];
        mdl = &HmfModelData[model->omObj1->model[0]];
        mdl->mtx[1] = mdl->mtx[3] = mdl->mtx[4] = mdl->mtx[6] = mdl->mtx[7] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[model->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[15] = 1.0f;
        angle += speed;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (frames > 0) {
            frames--;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

Process *func_800D9668_name_81(DuelModel *model, f32 angle, f32 speed, s32 frames) {
    Process *proc;
    DuelModelSpin *spin;

    proc = omAddPrcObj(func_800D94C4_name_81, 0, 0, 0x40);
    spin = HuMemMemoryAlloc(proc->heap, sizeof(DuelModelSpin));
    proc->user_data = spin;
    spin->model = model;
    spin->angle = angle;
    spin->speed = speed;
    spin->frames = frames;
    return proc;
}

void func_800D96F4_name_81(void) {
    DuelModel *model;

    model = ((DuelModelKill *)HuPrcCurrentGet()->user_data)->model;
    func_8001C814_main(model->omObj1->model[0], 3, 0);
    func_800EFABC_name_81(model);
    func_800D8F3C_name_81((Object *)model);
    omDelPrcObj(NULL);
}

void func_800D974C_name_81(DuelModel *model) {
    Process *proc;
    DuelModelKill *work;

    proc = omAddPrcObj(func_800D96F4_name_81, 0, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = work;
    work->model = model;
}
