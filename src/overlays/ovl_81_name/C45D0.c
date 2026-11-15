#include "common.h"
#include "ovl_81.h"
#include "game/hmfman.h"

// duel n2: object bursts and two model particle effects (13F90's per-face-group particles).

/* One particle (13F90's HmfFxPart, 0x30 bytes, one per face group). */
typedef struct DuelFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec orbit; /* x radius, y rise speed, z angle (func_800DD5CC) */
    /* 0x24 */ Vec dir;
} DuelFxPart; /* size 0x30 */

/* A model's particle work (HmfModel.unkBC; 13F90's HmfFxWork). */
typedef struct DuelFxWork {
    /* 0x00 */ s16 motion; /* -1 none */
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags; /* 4 finished */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 rise;
    /* 0x0C */ f32 speed;
    /* 0x10 */ char unk10[8];
    /* 0x18 */ void (*unk18)(s16);
    /* 0x1C */ char unk1C[0xC];
    /* 0x28 */ Vec verts[4];
    /* 0x58 */ DuelFxPart* parts;
} DuelFxWork;

/* hmfman.h's HmfModelData_Unk64_Unk60_Struct (0x68 bytes) with its face-group count. */
typedef struct DuelFxObj {
    /* 0x00 */ char unk00[0x2E];
    /* 0x2E */ s16 groupCount;
    /* 0x30 */ char unk30[0x20];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ void* unk54;
    /* 0x58 */ char unk58[0x10];
} DuelFxObj; /* size 0x68 */

/* HmfData as the effects read it (13F90's HmfFxData; pointer slots kept for the host). */
typedef struct DuelFxData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 count; /* face group count */
    /* 0x1C */ char unk1C[0x10];
    /* 0x2C */ void* unk2C[4];
    /* 0x3C */ void* unk3C;
    /* 0x40 */ Vtx* unk40;
    /* 0x44 */ Vtx* unk44[3];
    /* 0x50 */ void* unk50[4];
    /* 0x60 */ DuelFxObj* objs;
} DuelFxData;

#define FXWORK(model) ((DuelFxWork*) HmfModelData[model].unkBC)
#define FXDATA(model) ((DuelFxData*) HmfModelData[model].hmf)

/* func_800DC800's work: a ring of `count` objects around `pos`. */
typedef struct DuelBurstWork {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 count;
    /* 0x08 */ Vec* pos;
    /* 0x0C */ f32 dist;
    /* 0x10 */ s32 delay;
    /* 0x14 */ s32 keepMotion;
} DuelBurstWork;

/* func_800DCBA8's work: one object moving by `vel` until its motion ends. */
typedef struct DuelMoveWork {
    /* 0x00 */ s32 type;
    /* 0x04 */ Vec* pos;
    /* 0x08 */ Vec* vel;
    /* 0x0C */ f32 scale;
    /* 0x10 */ Object* obj;
    /* 0x14 */ s32 delay;
} DuelMoveWork;

void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_80013954_main(s16 model, s16 value);
s32 func_800D9234_name_81(Object*);

extern Object* D_80102AD0_name_81[32];
extern s16 D_80102B50_name_81;
extern omObjData* D_80102B54_name_81;
extern Vec D_80102B58_name_81;
extern s32 D_80100E40_name_81;

void func_800DD518_name_81(omObjData* obj);
void func_800DD59C_name_81(s16 model, f32 rise, f32 speed);
void func_800DD5CC_name_81(s16 model);
void func_800DD75C_name_81(s16 model);

void func_800DC800_name_81(void) {
    Vec pos;
    DuelBurstWork* work = HuPrcCurrentGet()->user_data;
    s32 type = work->type;
    s32 count = work->count;
    Vec* src = work->pos;
    f32 dist = work->dist;
    s32 delay = work->delay;
    s32 keepMotion = work->keepMotion;
    Vec offsets[6] = {
        { 0.0f, 2.0f, 0.0f },   { 8.0f, 4.0f, 8.0f },   { -8.0f, -2.0f, -8.0f },
        { 8.0f, 6.0f, -8.0f },  { -8.0f, 0.0f, 8.0f },  { 0.0f, 10.0f, 0.0f },
    };
    s32 i;

    HuVecCopy3F(&pos, src);
    for (i = 0; i < count; i++) {
        D_80102AD0_name_81[i] = func_800D8010_name_81(type, NULL);
        if (keepMotion == 0) {
            func_8001C8E4_main(*D_80102AD0_name_81[i]->omObj1->model, 0x800);
            func_8001C258_main(*D_80102AD0_name_81[i]->omObj1->model, 0x180, 0);
            func_8001C448_main(*D_80102AD0_name_81[i]->omObj1->model);
        }
        func_800D8944_name_81(D_80102AD0_name_81[i]);
        func_8001C814_main(*D_80102AD0_name_81[i]->omObj1->model, 2, 0);
        HuVecCopy3F(&D_80102AD0_name_81[i]->coords, &pos);
        D_80102AD0_name_81[i]->coords.x += dist * offsets[i % 6].x;
        D_80102AD0_name_81[i]->coords.y += dist * offsets[i % 6].y;
        D_80102AD0_name_81[i]->coords.z += dist * offsets[i % 6].z;
        HuPrcSleep(delay);
    }
    func_800EFABC_name_81(D_80102AD0_name_81[i - 1]);
    for (i = 0; i < count; i++) {
        func_800D8F3C_name_81(D_80102AD0_name_81[i]);
    }
    omDelPrcObj(NULL);
}

Process* func_800DCA64_name_81(s32 type, s32 count, Vec* pos, f32 dist, s32 delay) {
    Process* process = omAddPrcObj(func_800DC800_name_81, 0, 0, 0x40);
    DuelBurstWork* work = HuMemMemoryAlloc(process->heap, 0x20);

    process->user_data = work;
    work->type = type;
    work->count = count;
    work->pos = pos;
    work->dist = dist;
    work->delay = delay;
    work->keepMotion = 0;
    return process;
}

Process* func_800DCB04_name_81(s32 type, s32 count, Vec* pos, f32 dist, s32 delay) {
    Process* process = omAddPrcObj(func_800DC800_name_81, 0, 0, 0x40);
    DuelBurstWork* work = HuMemMemoryAlloc(process->heap, 0x20);

    process->user_data = work;
    work->type = type;
    work->count = count;
    work->pos = pos;
    work->dist = dist;
    work->delay = delay;
    work->keepMotion = 1;
    return process;
}

void func_800DCBA8_name_81(void) {
    DuelMoveWork* work = HuPrcCurrentGet()->user_data;
    Vec* src = work->vel;
    Vec vel = { 0.0f, 0.0f, 0.0f };
    Object* obj = work->obj;
    s32 delay = work->delay;

    if (src != NULL) {
        HuVecCopy3F(&vel, src);
    }
    if (delay != 0) {
        HuPrcSleep(delay - 1);
        func_8001C814_main(*obj->omObj1->model, 1, 0);
        func_800D8E88_name_81(obj);
    }
    while (!(func_800D9234_name_81(obj) & 1)) {
        HuPrcVSleep();
        HuVecAdd(&obj->coords, &obj->coords, &vel);
    }
    func_800D8F3C_name_81(obj);
    omDelPrcObj(NULL);
}

Process* func_800DCC8C_name_81(s32 type, Vec* pos, Vec* vel, f32 scale, s32 delay, f32 speed) {
    Object* obj = func_800D8010_name_81(type, NULL);
    Process* process;
    DuelMoveWork* work;

    func_8001C8E4_main(*obj->omObj1->model, 0x800);
    func_8001C258_main(*obj->omObj1->model, 0x180, 0);
    func_8001C448_main(*obj->omObj1->model);
    func_8001C92C_main(*obj->omObj1->model, speed);
    func_800D8944_name_81(obj);
    if (delay != 0) {
        func_8001C814_main(*obj->omObj1->model, 2, 1);
        func_800D8F0C_name_81(obj);
    } else {
        func_8001C814_main(*obj->omObj1->model, 2, 0);
    }
    HuVecCopy3F(&obj->coords, pos);
    HuVecCopyXYZ(&obj->scale, scale, scale, scale);
    process = omAddPrcObj(func_800DCBA8_name_81, 0, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, 0x20);
    process->user_data = work;
    work->type = type;
    work->pos = pos;
    work->vel = vel;
    work->scale = scale;
    work->obj = obj;
    work->delay = delay;
    return process;
}

Process* func_800DCE10_name_81(s32 type, Vec* pos, Vec* vel, f32 scale, s32 delay) {
    return func_800DCC8C_name_81(type, pos, vel, scale, delay, 1.0f);
}

Process* func_800DCE40_name_81(s32 type, Vec* pos, Vec* vel, f32 scale) {
    return func_800DCC8C_name_81(type, pos, vel, scale, 0, 1.0f);
}

/* Particle hook: the particles fly out over a sphere, slow down and shrink; done after 100 frames. */
void func_800DCE6C_name_81(s16 model) {
    DuelFxData* hmf = FXDATA(model);
    DuelFxWork* work = FXWORK(model);
    DuelFxPart* part;
    s16 count;
    s16 i;
    s16 n;
    f32 yaw;
    f32 pitch;
    f32 sinYaw;

    if (work->motion == -1) {
        count = hmf->count;
    } else {
        count = hmf->objs[work->motion].groupCount;
    }
    if (work->frame == 0) {
        work->flags &= ~4;
        n = HuSqrtf(hmf->count);
        part = work->parts;
        for (i = 0; i < count; i++, part++) {
            part->pos.x = part->pos.y = part->pos.z = 0.0f;
            yaw = (360.0f / n) * (i % n);
            sinYaw = sindf(yaw);
            pitch = (180.0f / n) * (i / n);
            part->dir.x = sinYaw * sindf(pitch);
            part->dir.y = cosdf(pitch);
            part->dir.z = cosdf(yaw) * sindf(pitch);
            part->pos.x = part->dir.x * 50.0f;
            part->pos.y = part->dir.y * 50.0f;
            part->pos.z = part->dir.z * 50.0f;
            part->speed = (rand8() & 0xF) + 5;
            part->scale = 3.0f;
        }
    }
    part = work->parts;
    for (i = 0; i < count; i++, part++) {
        part->pos.x += part->dir.x * part->speed;
        part->pos.y += part->dir.y * part->speed;
        part->pos.z += part->dir.z * part->speed;
        part->speed *= 0.98f;
        part->scale *= 0.9f;
    }
    if (++work->frame > 100) {
        work->flags |= 4;
    }
}

s32 func_800DD1E0_name_81(s32 data, char* name) {
    s32 model = func_8000B108_main(data, 0xAA9) & 0xFFFF;

    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C258_main(model, 0x180, 0);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_8001C8A8_main(model, 1);
    func_8001C92C_main(model, 0.5f);
    Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
    func_80013390_main(model, -1, name, func_800DCE6C_name_81);
    return model;
}

void func_800DD2BC_name_81(s16 model) {
    func_8001ACDC_main(model);
}

void func_800DD2DC_name_81(s16 model, Vec* pos) {
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
}

void func_800DD30C_name_81(s32 model) {
    if (HmfModelData[model].unk40 >= D_800CCF58_main[HmfModelData[model].unk02].unk02) {
        func_8001C6A8_main((s16) model, 0.0f);
        func_800138EC_main(model, 4, 0);
        func_80013954_main(model, 0);
    }
}

s32 func_800DD3B4_name_81(s32 model) {
    return HmfModelData[model].unk40 >= D_800CCF58_main[HmfModelData[model].unk02].unk02;
}

void func_800DD41C_name_81(Vec* pos) {
    u16 model;

    D_80102B50_name_81 = model = func_8000B108_main(0xB0032, 0xAA9);
    Hu3DModelPosSet((s16) model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main((s16) model, 0x20000, 0x20000);
    func_8001C8A8_main((s16) model, 1);
    func_8001C448_main((s16) model);
    func_8001C954_main((s16) model);
    func_8001C514_main((s16) model);
    func_80013390_main((s16) model, -1, NULL, func_800DD75C_name_81);
    func_800DD59C_name_81((s16) model, 5.0f, 1.0f);
    D_80100E40_name_81 = 0;
    D_80102B54_name_81 = omAddObj(0x7D0, 10, 10, -1, func_800DD518_name_81);
    HuVecCopy3F(&D_80102B58_name_81, pos);
}

void func_800DD518_name_81(omObjData* obj) {
    if (D_80100E40_name_81 != 0) {
        func_800DD5CC_name_81(D_80102B50_name_81);
        func_800DD5CC_name_81(D_80102B50_name_81);
    }
}

void func_800DD554_name_81(void) {
    D_80100E40_name_81 = 1;
}

void func_800DD564_name_81(void) {
    D_80100E40_name_81 = 0;
}

void func_800DD570_name_81(void) {
    func_8001ACDC_main(D_80102B50_name_81);
    omDelObj(D_80102B54_name_81);
}

void func_800DD59C_name_81(s16 model, f32 rise, f32 speed) {
    DuelFxWork* work = FXWORK(model);

    work->rise = rise;
    work->speed = speed;
}

/* Starts one free particle on a random orbit around D_80102B58. */
void func_800DD5CC_name_81(s16 model) {
    DuelFxData* hmf = FXDATA(model);
    DuelFxWork* work = FXWORK(model);
    DuelFxPart* part = work->parts;
    s16 count = hmf->count;
    s16 i;

    for (i = 0; i < count; i++, part++) {
        if (part->scale <= 0.0f) {
            part->orbit.x = (((rand8() & 0xFF) * 75) >> 6) + 100;
            part->orbit.y = work->rise;
            part->orbit.z = ((rand8() & 0xFF) * 45) >> 5;
            part->pos.x = sindf(part->orbit.z) * part->orbit.x / 20.0f + D_80102B58_name_81.x + 142.0f;
            part->pos.y = D_80102B58_name_81.y;
            part->pos.z = cosdf(part->orbit.z) * part->orbit.x / 20.0f + D_80102B58_name_81.z;
            part->scale = 0.3f;
            return;
        }
    }
}

/* Particle hook: live particles circle D_80102B58 while rising and fading. */
void func_800DD75C_name_81(s16 model) {
    DuelFxData* hmf = FXDATA(model);
    DuelFxWork* work = FXWORK(model);
    s16 count = hmf->count;
    DuelFxPart* part;
    s16 i;

    if (work->frame == 0) {
        work->flags &= ~4;
        part = work->parts;
        for (i = 0; i < count; i++, part++) {
            part->pos.x = part->pos.y = part->pos.z = 0.0f;
            part->dir.x = part->dir.y = part->dir.z = 0.0f;
            part->scale = 0.0f;
            part->speed = 1.0f;
        }
        work->frame++;
    }
    part = work->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->scale > 0.0f) {
            part->pos.x = sindf(part->orbit.z) * part->orbit.x / 20.0f + D_80102B58_name_81.x + 142.0f;
            part->pos.y += part->orbit.y;
            part->pos.z = cosdf(part->orbit.z) * part->orbit.x / 20.0f + D_80102B58_name_81.z;
            part->orbit.z += (400.0f - part->orbit.x) / 20.0f * work->speed;
            if (part->orbit.z > 360.0f) {
                part->orbit.z -= 360.0f;
            }
            part->scale -= 0.015f;
        } else {
            part->scale = 0.0f;
        }
    }
}

/* The unit's .rodata is padded to 0x60 (to the next unit's 16-byte boundary). */
const u8 D_80102354_name_81[8] = { 0 };
