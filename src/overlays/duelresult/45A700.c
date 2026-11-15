#include "common.h"

#include "mallocblock.h"

// duel r2: the duel results' firework (a model's vertex-scatter effect, 13F90.c).

/* One scattered polygon of the effect (13F90.c's HmfFxPart). */
typedef struct DrFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale; /* alpha/size; <= 0 is a free slot */
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec dir; /* x: delay in frames for the shape's particles */
    /* 0x24 */ Vec vel; /* shape particles: target offset; z > 0 marks them */
} DrFxPart; /* size 0x30 */

/* HmfModel.unkBC for a vertex-scatter model (13F90.c's HmfFxWork). */
typedef struct DrFxWork {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags; /* 2 done, 4 finished */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 dist;
    /* 0x0C */ char unk0C[0xC];
    /* 0x18 */ void (*hook)(s16);
    /* 0x1C */ char unk1C[0x3C];
    /* 0x58 */ DrFxPart* parts;
} DrFxWork;

/* HmfData as the effect reads it (13F90.c's HmfFxData). */
typedef struct DrFxData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 count; /* face group (particle) count */
} DrFxData;

#define DR_FXWORK(model) ((DrFxWork*) HmfModelData[model].unkBC)
#define DR_FXDATA(model) ((DrFxData*) HmfModelData[model].hmf)

// Work area allocated by func_8010ABE0 and stored at the process's user_data
// (see Process.user_data).
typedef struct DuelResultWork {
    /* 0x00 */ s32 unk_00; /* sprite data id of the shape the firework draws */
    /* 0x04 */ s16 unk_04; /* flags: 1 waiting, 2 stop */
    /* 0x06 */ s16 unk_06; /* shape scale (DrFxWork.dist) */
    /* 0x08 */ s16 unk_08; /* flight frames */
    /* 0x0A */ s16 unk_0A; /* flight frames, set by func_8010AC94 */
    /* 0x0C */ Vec unk_0C; /* flight start */
    /* 0x18 */ Vec unk_18; /* flight end */
    /* 0x24 */ Vec unk_24; /* current start */
    /* 0x30 */ Vec unk_30; /* current end */
    /* 0x3C */ Vec unk_3C; /* arc amplitude */
    /* 0x48 */ f32 unk_48; /* arc phase, 0 or 180 */
} DuelResultWork; // sizeof 0x4C

void func_8010ACC4_duelresult(void);

DuelResultWork* func_8010ABE0_duelresult(s32 arg0) {
    Process* process;
    DuelResultWork* work;

    process = omAddPrcObj(func_8010ACC4_duelresult, 0x3F00, 0x2000, 0);
    work = HuMemAllocTag(sizeof(DuelResultWork), 0x7918);
    process->user_data = work;
    work->unk_06 = 60;
    work->unk_0A = 60;
    work->unk_0C.x = 0.0f;
    work->unk_0C.y = 500.0f;
    work->unk_0C.z = 0.0f;
    work->unk_18.x = 0.0f;
    work->unk_18.y = 0.0f;
    work->unk_18.z = 0.0f;
    work->unk_00 = arg0;
    work->unk_04 = 0;
    return work;
}

void func_8010AC6C_duelresult(DuelResultWork *arg0, s32 arg1) {
    arg0->unk_00 = arg1;
}

void func_8010AC74_duelresult(DuelResultWork* arg0, f32 x, f32 y, f32 z) {
    arg0->unk_0C.x = x;
    arg0->unk_0C.y = y;
    arg0->unk_0C.z = z;
}

void func_8010AC84_duelresult(DuelResultWork* arg0, f32 x, f32 y, f32 z) {
    arg0->unk_18.x = x;
    arg0->unk_18.y = y;
    arg0->unk_18.z = z;
}

void func_8010AC94_duelresult(DuelResultWork *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

void func_8010AC9C_duelresult(DuelResultWork* arg0, s32 mask, s32 value) {
    arg0->unk_04 = value | (arg0->unk_04 & ~mask);
}

s16 func_8010ACB4_duelresult(DuelResultWork *arg0) {
    return arg0->unk_04;
}

void func_8010ACBC_duelresult(DuelResultWork *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010ACC4_duelresult);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010BDA4_duelresult);

/* Starts a particle at pos with velocity vel and colour (r, g, b) in the first free slot of model's
   effect; returns the slot (one past the last if none is free). */
DrFxPart* func_8010C13C_duelresult(s16 model, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, u8 r, u8 g, u8 b) {
    DrFxPart* part;
    s16 i;
    s16 count;

    count = DR_FXDATA(model)->count;
    part = DR_FXWORK(model)->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->scale <= 0.0f) {
            part->pos.x = x;
            part->pos.y = y;
            part->pos.z = z;
            part->vel.x = vx;
            part->vel.y = vy;
            part->vel.z = vz;
            part->color[0] = r;
            part->color[1] = g;
            part->color[2] = b;
            part->scale = 2.0f;
            break;
        }
    }
    return part;
}

/* Effect hook of the burst: the particles fly out to the shape (vel), twinkle, then fall. */
void func_8010C21C_duelresult(s16 model) {
    DrFxData* data;
    DrFxWork* fx;
    DrFxPart* part;
    DrFxPart* src;
    DrFxPart* dst;
    s16 count;
    s16 i;
    s16 j;
    s16 n;
    f32 t;
    u8 r;
    u8 g;
    u8 b;

    data = DR_FXDATA(model);
    fx = DR_FXWORK(model);
    count = data->count;
    if (fx->frame == 0) {
        fx->flags &= ~4;
        part = fx->parts;
        for (i = 0; i < count; i++, part++) {
            if (part->vel.z > 0.0f) {
                part->scale = 1.0f;
            }
        }
    }
    part = fx->parts;
    r = rand8() | 0x80;
    g = rand8() | 0x80;
    b = rand8() | 0x80;
    if (fx->frame <= fx->dist) {
        if (fx->frame > 20) {
            for (j = 0; j < 2; j++) {
                src = &fx->parts[(rand8() * count) >> 8];
                if (src->vel.z > 0.0f) {
                    dst = &fx->parts[(rand8() * count) >> 8];
                    if (dst->vel.z <= 0.0f) {
                        dst->pos.x = src->pos.x;
                        dst->pos.y = src->pos.y;
                        dst->pos.z = src->pos.z;
                        dst->scale = 1.0f;
                    }
                }
            }
        }
        for (i = 0; i < count; i++, part++) {
            if (part->scale > 0.0f) {
                part->color[0] = r;
                part->color[1] = g;
                part->color[2] = b;
                if (part->vel.z > 0.0f) {
                    t = fx->frame * part->speed;
                    if (t > 90.0f) {
                        t = 90.0f;
                    }
                    part->pos.x = sindf(t) * part->vel.x;
                    part->pos.y = sindf(t) * part->vel.y;
                    part->pos.z = 0.0f;
                    part->scale = ((fx->frame + i) & 1) * 0.5f + 1.0f;
                } else {
                    part->pos.y -= 10.0f;
                    part->scale -= 0.04f;
                }
            } else {
                part->scale = 0.0f;
            }
        }
    } else {
        for (i = 0, n = 0; i < count; i++, part++) {
            if (part->scale > 0.0f) {
                part->color[0] = r;
                part->color[1] = g;
                part->color[2] = b;
                if (part->vel.z > 0.0f) {
                    if (part->dir.x <= 0.0f) {
                        part->pos.y -= part->speed * 5.0f;
                        part->scale -= 0.02f;
                        if (part->scale < 0.0f) {
                            part->scale = 0.0f;
                        }
                    } else {
                        part->dir.x -= 1.0f;
                        part->scale = ((fx->frame + i) & 1) * 0.5f + 1.0f;
                    }
                } else {
                    part->pos.y -= 10.0f;
                    part->scale -= 0.04f;
                }
            } else {
                part->scale = 0.0f;
                n++;
            }
        }
        if (n >= i) {
            fx->flags |= 2;
            return;
        }
    }
    fx->frame++;
}

/* Effect hook of the rising rocket: the trail particles move, sink and fade. */
void func_8010C72C_duelresult(s16 model) {
    DrFxData* data;
    DrFxWork* fx;
    DrFxPart* part;
    s16 count;
    s16 i;

    data = DR_FXDATA(model);
    fx = DR_FXWORK(model);
    count = data->count;
    if (fx->frame == 0) {
        fx->flags &= ~4;
        part = fx->parts;
        for (i = 0; i < count; i++, part++) {
            part->scale = part->pos.x = part->pos.y = part->pos.z = 0.0f;
        }
        fx->frame++;
    }
    part = fx->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->scale > 0.0f) {
            part->pos.x += part->vel.x;
            part->pos.y += part->vel.y;
            part->pos.z += part->vel.z;
            part->pos.y -= 5.0f;
            part->scale -= 0.05f;
        } else {
            part->scale = 0.0f;
        }
    }
}

void func_8010C8E0_duelresult(void);

DuelResultWork* func_8010C880_duelresult(void) {
    Process* process;
    DuelResultWork* work;

    process = omAddPrcObj(func_8010C8E0_duelresult, 0x3F00, 0x2000, 0);
    work = HuMemAllocTag(sizeof(DuelResultWork), 0x7918);
    process->user_data = work;
    work->unk_18.x = 0.0f;
    work->unk_18.y = 100.0f;
    work->unk_18.z = 0.0f;
    return work;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010C8E0_duelresult);
