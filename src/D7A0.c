#include "common.h"
#include "mallocblock.h"

// d7: particle effects built on 13F90's per-face-group particle system (a model's HmfModel.unkBC
// work, set up by func_80013390_main with type -1 and one of the hooks below).

/* One particle (13F90's HmfFxPart: 0x30 bytes, one per face group of the model). */
typedef struct FxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 life; /* > 0 while alive; the burst uses it as its speed */
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ Vec unk24;
} FxPart; /* size 0x30 */

/* The model's effect work (13F90's HmfFxWork) as these hooks use it. */
typedef struct FxWork {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags; /* 1 emitting, 4 finished (13F90's func_800138EC_main) */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 size;   /* particle start size */
    /* 0x0C */ f32 frames; /* particle lifetime in frames */
    /* 0x10 */ f32 spread; /* emitter's x/z spread */
    /* 0x14 */ f32 timer;  /* frames left to emit; < 0 forever */
    /* 0x18 */ void (*unk18)(s16);
    /* 0x1C */ Vec origin; /* emitter position */
    /* 0x28 */ Vec verts[4];
    /* 0x58 */ FxPart* parts;
} FxWork; /* size 0x5C */

/* 13F90's HmfFxData: only the face group (particle) count is read here. */
typedef struct FxData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 count;
} FxData;

/* A pool of burst models (func_8000D3E0_main): one 0x10-byte entry per model. */
typedef struct FxPoolEntry {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 model;
    /* 0x04 */ Vec unk04;
} FxPoolEntry; /* size 0x10 */

typedef struct FxPool {
    /* 0x00 */ s16 count;
    /* 0x04 */ FxPoolEntry* entries;
} FxPool;

#define FXWORK(model) ((FxWork*) HmfModelData[model].unkBC)
#define FXDATA(model) ((FxData*) HmfModelData[model].hmf)

void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
void func_800138EC_main(s16 model, u16 mask, u16 flags);
s16 func_80013928_main(s16 model);
void func_80013954_main(s16 model, s16 value);

extern u8 D_80097720_main[4]; /* flicker: 0, 1, 2, 1 */
extern FxPool* D_800D6A00_main[8];

/* Creates a flame model (flags arg1 without 0x60) whose particles rise and flicker. */
s16 func_8000CBA0_main(s32 arg0, s32 arg1) {
    FxData* hmf;
    FxWork* work;
    FxPart* part;
    s16 model;
    s16 i;

    model = func_8000CC98_main(arg0, arg1 & ~0x60);
    func_80013390_main(model, -1, NULL, func_8000D268_main);
    hmf = FXDATA(model);
    work = FXWORK(model);
    part = work->parts;
    work->size = 5.0f;
    work->frames = 20.0f;
    for (i = 0; i < hmf->count; i++, part++) {
        part->pos.x = part->pos.y = part->pos.z = 0.0f;
        part->vel.x = part->vel.z = 0.0f;
        part->vel.y = -10.0f;
        part->life = part->scale = 0.0f;
    }
    return model;
}

/* Creates a model from data arg0 with flags arg1 at the origin. */
s16 func_8000CC98_main(s32 arg0, s32 arg1) {
    s16 model;

    model = func_8000B108_main(arg0, arg1);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    return model;
}

/* Sets a flame's particle size, lifetime and rise speed. */
void func_8000CD00_main(s16 model, f32 size, f32 frames, f32 speed) {
    FxData* hmf;
    FxWork* work;
    FxPart* part;
    s16 i;

    hmf = FXDATA(model);
    work = FXWORK(model);
    part = work->parts;
    work->size = size;
    work->frames = frames;
    for (i = 0; i < hmf->count; i++, part++) {
        part->vel.y = -speed;
    }
}

/* Emits one particle at (x, y, z) if one is free; returns 1 if it did. */
s32 func_8000CD74_main(s16 model, f32 x, f32 y, f32 z) {
    FxData* hmf;
    FxWork* work;
    FxPart* part;
    s16 i;

    hmf = FXDATA(model);
    work = FXWORK(model);
    part = work->parts;
    for (i = 0; i < hmf->count; i++, part++) {
        if (part->life <= 0.0f) {
            part->pos.x = x;
            part->pos.y = y;
            part->pos.z = z;
            part->life = part->scale =
                work->size * 0.7f + work->size * 0.3f * ((rand8() % 10 + 1) * 0.1f);
            return 1;
        }
    }
    return 0;
}

/* Creates a flame with an emitter object that keeps it burning at its origin. */
s16 func_8000CED8_main(s32 arg0, s32 arg1) {
    omObjData* obj;
    FxWork* work;
    s16 model;

    obj = omAddObj(1000, 0, 0, -1, func_8000D06C_main);
    model = func_8000CBA0_main(arg0, arg1);
    obj->work[0] = model;
    work = FXWORK(model);
    work->origin.x = work->origin.y = work->origin.z = 0.0f;
    work->flags |= 1;
    work->spread = 100.0f;
    work->timer = -1.0f;
    return model;
}

void func_8000CFA4_main(s16 model, f32 x, f32 y, f32 z) {
    FxWork* work = FXWORK(model);

    work->origin.x = x;
    work->origin.y = y;
    work->origin.z = z;
}

void func_8000CFD8_main(s16 model, s16 frames) {
    FXWORK(model)->timer = frames;
}

void func_8000D018_main(s16 model, f32 spread) {
    FXWORK(model)->spread = spread;
}

/* Stops a flame: it is deleted once its last particle dies. */
void func_8000D044_main(s16 model) {
    func_800138EC_main(model, 5, 4);
}

/* Emitter object: one particle per frame within spread of the origin while emitting. */
void func_8000D06C_main(omObjData* obj) {
    FxData* hmf;
    FxWork* work;
    FxPart* part;
    s16 model;
    s16 i;
    f32 x;
    f32 z;

    model = obj->work[0];
    hmf = FXDATA(model);
    work = FXWORK(model);
    if (work->flags & 4) {
        part = work->parts;
        for (i = 0; i < hmf->count; i++, part++) {
            if (part->life > 0.0f) {
                break;
            }
        }
        if (i == hmf->count) {
            func_8001ACDC_main(model);
            omDelObj(obj);
            return;
        }
        work->flags &= ~1;
    }
    if (work->timer >= 0.0f) {
        work->timer -= 1.0f;
        if (work->timer <= 0.0f) {
            work->flags &= ~1;
        }
    }
    if (work->flags & 1) {
        x = rand8() * work->spread / 256.0f - work->spread / 2.0f;
        z = rand8() * work->spread / 256.0f - work->spread / 2.0f;
        func_8000CD74_main(model, x + work->origin.x, work->origin.y, z + work->origin.z);
    }
}

/* Flame hook: particles move, shrink over their lifetime and flicker. */
void func_8000D268_main(s16 model) {
    FxData* hmf;
    FxWork* work;
    FxPart* part;
    s16 count;
    s16 i;

    hmf = FXDATA(model);
    work = FXWORK(model);
    part = work->parts;
    count = hmf->count;
    for (i = 0; i < count; i++, part++) {
        if (part->life > 0.0f) {
            part->pos.x += part->vel.x;
            part->pos.y += part->vel.y;
            part->pos.z += part->vel.z;
            part->life -= work->size / work->frames;
            if (part->life <= 0.0f) {
                part->life = 0.0f;
            }
            part->scale = (D_80097720_main[(work->frame + i) & 3] * 0.15f + 1.0f) * part->life;
        }
    }
    work->frame++;
}

void func_8000D3AC_main(void) {
    FxPool** pool;
    s16 i;

    pool = D_800D6A00_main;
    for (i = 0; i < 8; i++, pool++) {
        *pool = NULL;
    }
}

/* Creates a pool of count stopped effect models (data arg0, flags arg1) driven by hook; returns
   the pool's slot, -1 if all 8 are used. */
s16 func_8000D3E0_main(s32 arg0, s32 arg1, s16 count, void (*hook)(s16)) {
    FxPool** pools;
    FxPool* pool;
    FxPoolEntry* entry;
    s16 model;
    s16 slot;
    s16 i;

    pools = D_800D6A00_main;
    for (slot = 0; slot < 8; slot++, pools++) {
        if (*pools == NULL) {
            break;
        }
    }
    if (slot == 8) {
        return -1;
    }
    pool = *pools = HuMemAllocTag(sizeof(FxPool), 0x7918);
    pool->count = count;
    entry = HuMemAllocTag(count * sizeof(FxPoolEntry), 0x7918);
    pool->entries = entry;
    for (i = 0; i < count; i++, entry++) {
        model = func_8000CC98_main(arg0, arg1 | 4);
        entry->model = model;
        func_80013390_main(model, -1, NULL, hook);
        func_800138EC_main(model, 6, 6);
        entry->unk04.x = entry->unk04.y = entry->unk04.z = 0.0f;
        entry->unk00 = 0;
    }
    return slot;
}

/* Starts a finished model of pool slot at (x, y, z); returns it, -1 if none is free. */
s16 func_8000D550_main(s16 slot, f32 x, f32 y, f32 z) {
    FxPool* pool;
    FxPoolEntry* entry;
    s16 model;
    s16 i;

    pool = D_800D6A00_main[slot];
    entry = pool->entries;
    for (i = 0; i < pool->count; i++, entry++) {
        if (func_80013928_main(entry->model) & 4) {
            break;
        }
    }
    if (i == pool->count) {
        return -1;
    }
    model = entry->model;
    Hu3DModelPosSet(model, x, y, z);
    func_80013954_main(model, 0);
    func_800138EC_main(model, 6, 0);
    func_8001C258_main(model, 4, 0);
    return model;
}

/* A pool of count bursts of data 0x85 with flags arg0. */
s16 func_8000D658_main(s32 arg0, s16 count) {
    return func_8000D3E0_main(0x85, arg0, count, func_8000D694_main);
}

// Masked 0, raw 5: the count and the constant 5 swap s6/s7. Logic checked against the asm.
#ifdef NON_MATCHING
/* Burst hook: on frame 0 spreads the particles in a ring; 8 frames out and falling, then hides. */
void func_8000D694_main(s16 model) {
    FxData* hmf;
    FxWork* work;
    FxPart* part;
    s16 count;
    s16 i;
    f32 angle;
    f32 scale;

    hmf = FXDATA(model);
    work = FXWORK(model);
    count = hmf->count;
    if (work->frame == 0) {
        work->flags &= ~4;
        part = work->parts;
        for (i = 0; i < count; i++, part++) {
            part->pos.x = part->pos.y = part->pos.z = 0.0f;
            angle = (360 / count) * i;
            part->vel.x = sindf(angle);
            part->vel.y = 5 - (rand8() & 0xF);
            part->vel.z = cosdf(angle);
            part->life = 15.0f;
        }
    }
    if (!(work->flags & 4)) {
        part = work->parts;
        scale = cosdf(work->frame * 11.25f) * 5.0f;
        for (i = 0; i < count; i++, part++) {
            part->pos.x += part->vel.x * part->life;
            part->pos.y += part->vel.y;
            part->pos.z += part->vel.z * part->life;
            part->scale = scale;
            part->vel.y -= 2.0f;
            part->life *= 0.7f;
        }
        if (++work->frame >= 8) {
            work->flags |= 4;
            func_8001C258_main(model, 4, 4);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/D7A0", func_8000D694_main);
#endif
