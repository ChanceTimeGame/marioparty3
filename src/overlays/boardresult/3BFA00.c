#include "common.h"

#include "mallocblock.h"

// event e8: the board results' firework (a model's vertex-scatter effect, 13F90.c); the same code as duelresult/45A700.c.

/* One scattered polygon of the effect (13F90.c's HmfFxPart). */
typedef struct BrFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale; /* alpha/size; <= 0 is a free slot */
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec dir; /* x: delay in frames for the shape's particles */
    /* 0x24 */ Vec vel; /* shape particles: target offset; z > 0 marks them */
} BrFxPart; /* size 0x30 */

/* HmfModel.unkBC for a vertex-scatter model (13F90.c's HmfFxWork). */
typedef struct BrFxWork {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags; /* 2 done, 4 finished */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 dist;
    /* 0x0C */ char unk0C[0xC];
    /* 0x18 */ void (*hook)(s16);
    /* 0x1C */ char unk1C[0x3C];
    /* 0x58 */ BrFxPart* parts;
} BrFxWork;

/* HmfData as the effect reads it (13F90.c's HmfFxData). */
typedef struct BrFxData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 count; /* face group (particle) count */
} BrFxData;

#define BR_FXWORK(model) ((BrFxWork*) HmfModelData[model].unkBC)
#define BR_FXDATA(model) ((BrFxData*) HmfModelData[model].hmf)

// Work area allocated by func_8010ABE0 and stored at the process's user_data
// (see Process.user_data).
typedef struct BoardResultWork {
    /* 0x00 */ s32 unk_00; /* sprite data id of the shape the firework draws */
    /* 0x04 */ s16 unk_04; /* flags: 1 waiting, 2 stop */
    /* 0x06 */ s16 unk_06; /* shape scale (BrFxWork.dist) */
    /* 0x08 */ s16 unk_08; /* flight frames */
    /* 0x0A */ s16 unk_0A; /* flight frames, set by func_8010AC94 */
    /* 0x0C */ Vec unk_0C; /* flight start */
    /* 0x18 */ Vec unk_18; /* flight end */
    /* 0x24 */ Vec unk_24; /* current start */
    /* 0x30 */ Vec unk_30; /* current end */
    /* 0x3C */ Vec unk_3C; /* arc amplitude */
    /* 0x48 */ f32 unk_48; /* arc phase, 0 or 180 */
} BoardResultWork; // sizeof 0x4C

void func_8010BE14_boardresult(void);
void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
void func_800138EC_main(s16 model, u16 mask, u16 flags);
s16 func_80013928_main(s16 model);
void func_80013954_main(s16 model, s16 value);

BoardResultWork* func_8010BD30_boardresult(s32 arg0) {
    Process* process;
    BoardResultWork* work;

    process = omAddPrcObj(func_8010BE14_boardresult, 0x3F00, 0x2000, 0);
    work = HuMemAllocTag(sizeof(BoardResultWork), 0x7918);
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

void func_8010BDBC_boardresult(BoardResultWork *arg0, s32 arg1) {
    arg0->unk_00 = arg1;
}

void func_8010BDC4_boardresult(BoardResultWork* arg0, f32 x, f32 y, f32 z) {
    arg0->unk_0C.x = x;
    arg0->unk_0C.y = y;
    arg0->unk_0C.z = z;
}

void func_8010BDD4_boardresult(BoardResultWork* arg0, f32 x, f32 y, f32 z) {
    arg0->unk_18.x = x;
    arg0->unk_18.y = y;
    arg0->unk_18.z = z;
}

void func_8010BDE4_boardresult(BoardResultWork *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

void func_8010BDEC_boardresult(BoardResultWork* arg0, s32 mask, s32 value) {
    arg0->unk_04 = value | (arg0->unk_04 & ~mask);
}

s16 func_8010BE04_boardresult(BoardResultWork *arg0) {
    return arg0->unk_04;
}

void func_8010BE0C_boardresult(BoardResultWork *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

void func_8010CEF4_boardresult(s16 model, s32 dataId);
BrFxPart* func_8010D28C_boardresult(s16 model, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, u8 r, u8 g, u8 b);
void func_8010D36C_boardresult(s16 model);
void func_8010D87C_boardresult(s16 model);

/* Rows of the matrix turning a vector by angle a about the unit axis (x, y, z), applied to
   (vx, vy, vz) (the camera roll in camera.c's func_80013220-style code). */
#define BR_ROT_X(x, y, z, a, vx, vy, vz)                                                         \
    ((vx) * ((x) * (x) + (1.0f - (x) * (x)) * cosdf(a)) +                                       \
     (vy) * ((x) * (y) * (1.0f - cosdf(a)) - (z) * sindf(a)) +                                  \
     (vz) * ((x) * (z) * (1.0f - cosdf(a)) + (y) * sindf(a)))
#define BR_ROT_Y(x, y, z, a, vx, vy, vz)                                                         \
    ((vx) * ((x) * (y) * (1.0f - cosdf(a)) + (z) * sindf(a)) +                                  \
     (vy) * ((y) * (y) + (1.0f - (y) * (y)) * cosdf(a)) +                                       \
     (vz) * ((y) * (z) * (1.0f - cosdf(a)) - (x) * sindf(a)))
#define BR_ROT_Z(x, y, z, a, vx, vy, vz)                                                         \
    ((vx) * ((x) * (z) * (1.0f - cosdf(a)) - (y) * sindf(a)) +                                  \
     (vy) * ((y) * (z) * (1.0f - cosdf(a)) + (x) * sindf(a)) +                                  \
     (vz) * ((z) * (z) + (1.0f - (z) * (z)) * cosdf(a)))

// event e8: NON_MATCHING, masked 341 (1227 vs 1172): retail computes the spark arguments in a
// different order and keeps work in s4 (spilled here). Call sequence and flow match; logic checked.
#ifdef NON_MATCHING
/* The firework: a rocket flies from work->unk_18 to work->unk_0C along a wobbling arc, trailing
   sparks, then bursts into the shape of sprite data work->unk_00; repeats while work->unk_04
   bit 1 is clear (bit 0 is set while it waits). Never returns. */
void func_8010BE14_boardresult(void) {
    Vec pos;
    Vec prev;
    s16 head;
    s16 t;
    s16 spin;
    BrFxWork* fx;
    s16 model;
    BoardResultWork* work;
    HmfData* hmf;
    HmfModelData_Unk64_Unk60_Struct* obj;
    HmfModelData_Unk64_Unk60_Unk54_Struct* face;
    s16 i;
    s16 j;
    s16 count;
    f32 roll;
    f32 r;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 sc;
    f32 ease;
    f32 wave;

    roll = 0.0f;
    work = HuPrcCurrentGet()->user_data;
    spin = 0;
    model = func_8000B108_main(0xB0034, 0x2A8);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    hmf = HmfModelData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        obj = &hmf->unk60[j];
        count = obj->unk22;
        face = obj->unk54;
        for (i = 0; i < count; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_8010D36C_boardresult);
    func_800138EC_main(model, 8, 8);
    fx = BR_FXWORK(model);
    func_8001C258_main(model, 4, 4);
    head = func_8000B108_main(0xB0035, 0x2B9);
    func_8001C258_main(head, 4, 4);
    Hu3DModelScaleSet(head, 2.0f, 2.0f, 2.0f);
    func_8001C92C_main(head, 2.0f);
    while (TRUE) {
        work->unk_04 &= ~1;
        work->unk_30 = work->unk_18;
        work->unk_24 = work->unk_0C;
        work->unk_08 = work->unk_0A;
        r = rand8() * 2 + 400;
        work->unk_3C.x = r - r / 2.0f;
        r = rand8() * 2 + 200;
        work->unk_3C.y = r - r / 2.0f;
        r = rand8() * 2 + 200;
        work->unk_3C.z = r - r / 2.0f;
        work->unk_48 = (rand8() & 1) ? 180.0f : 0.0f;
        fx->dist = work->unk_06;
        prev = pos = work->unk_30;
        HuAudFXPlay(0x16F);
        func_8001C258_main(model, 4, 0);
        func_80013954_main(model, 0);
        fx->hook = func_8010D87C_boardresult;
        func_800138EC_main(model, 2, 0);
        for (t = 0; t <= work->unk_08; t++) {
            HuPrcVSleep();
            prev = pos;
            dx = work->unk_24.x - work->unk_30.x;
            dy = work->unk_24.y - work->unk_30.y;
            dz = work->unk_24.z - work->unk_30.z;
            ease = sindf(90.0f / work->unk_08 * t);
            wave = sindf(180.0f / work->unk_08 * t + work->unk_48);
            pos.x = ease * dx + work->unk_30.x + wave * work->unk_3C.x;
            pos.y = ease * dy + work->unk_30.y + wave * work->unk_3C.y;
            pos.z = ease * dz + work->unk_30.z + wave * work->unk_3C.z;
            spin += 5;
            if (spin > 360) {
                spin -= 360;
            }
            roll += 20.0f;
            if (roll > 360.0f) {
                roll -= 360.0f;
            }
            dx = prev.x - pos.x;
            dy = prev.y - pos.y;
            dz = prev.z - pos.z;
            len = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (len != 0.0f) {
                dx /= len;
                dy /= len;
                dz /= len;
                for (i = 0; i < 2; i++) {
                    rx = dx * (((s32) (rand8() * 15) >> 7) * 0.01f + 1.0f);
                    ry = dy * (((s32) (rand8() * 15) >> 7) * 0.01f + 1.0f);
                    rz = dz * (((s32) (rand8() * 15) >> 7) * 0.01f + 1.0f);
                    sc = len * ((s32) ((u32) (rand8() * 25) >> 7) * 0.01f);
                    rx *= sc;
                    ry *= sc;
                    rz *= sc;
                    func_8010D28C_boardresult(model, rx + pos.x, ry + pos.y, rz + pos.z, rx, ry, rz, 0xFF, 0xFF, 0xC0);
                }
                func_8010D28C_boardresult(model, pos.x, pos.y, pos.z,
                                         (dx * 0.5f + BR_ROT_X(dx, dy, dz, roll, 0.0f, 1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         (dy * 0.5f + BR_ROT_Y(dx, dy, dz, roll, 0.0f, 1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         (dz * 0.5f + BR_ROT_Z(dx, dy, dz, roll, 0.0f, 1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         0xFF, 0x20, 0x20);
                func_8010D28C_boardresult(model, pos.x, pos.y, pos.z,
                                         (dx * 0.5f + BR_ROT_X(dx, dy, dz, roll, 0.0f, -1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         (dy * 0.5f + BR_ROT_Y(dx, dy, dz, roll, 0.0f, -1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         (dz * 0.5f + BR_ROT_Z(dx, dy, dz, roll, 0.0f, -1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         0xFF, 0x40, 0x00);
            }
        }
        HuPrcSleep(15);
        func_8001C258_main(model, 4, 4);
        func_8001C6A8_main(head, 0.0f);
        func_8001C258_main(head, 4, 0);
        Hu3DModelPosSet(head, pos.x, pos.y, pos.z);
        HuPrcVSleep();
        HuAudFXPlay(0x170);
        func_8010CEF4_boardresult(model, work->unk_00);
        fx->hook = func_8010D36C_boardresult;
        func_80013954_main(model, 0);
        func_8001C258_main(model, 4, 0);
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        func_800138EC_main(model, 2, 0);
        while (!(func_80013928_main(model) & 2)) {
            HuPrcVSleep();
        }
        func_8001C258_main(head, 4, 4);
        func_8001C258_main(model, 4, 4);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        work->unk_04 |= 1;
        if (work->unk_04 & 2) {
            HuPrcVSleep();
        } else {
            while (work->unk_04 & 1) {
                HuPrcVSleep();
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3BFA00", func_8010BE14_boardresult);
#endif

// event e8: masked 3: retail stores scale in rand8's delay slot with 3.0f still hoisted; only
// the source order that hoists it (scale before vel.z) fills the slot with vel.z. Logic checked.
#ifdef NON_MATCHING
/* Lays model's particles out on the white (0xFFFF) texels of sprite data dataId: each one's target
   offset (vel) is its texel's position from the centre, 12 units per texel; spare particles are
   cleared. */
void func_8010CEF4_boardresult(s16 model, s32 dataId) {
    s16 sprId;
    s16 grp;
    s16 total;
    BrFxWork* fx;
    HuSprite* spr;
    BrFxPart* part;
    u16* pix;
    s16 w;
    s16 h;
    s16 x;
    s16 y;
    s16 i;
    s16 n;
    s16 white;

    sprId = func_8000B838_main(dataId);
    grp = HuSprGrpCreate(1, 0);
    func_80055024_main(grp, 0, sprId, 0);
    spr = HuSprGet(grp, 0);
    pix = spr->unk_84->unk00->unk00;
    w = spr->unk_84->unk00->unk04;
    h = spr->unk_84->unk00->unk06;
    white = 0;
    for (i = 0; i < w * h; i++) {
        if (*pix++ == 0xFFFF) {
            white++;
        }
    }
    pix = spr->unk_84->unk00->unk00;
    fx = BR_FXWORK(model);
    total = BR_FXDATA(model)->count;
    part = fx->parts;
    y = 0;
    n = 0;
    for (; y < h; y++) {
        for (x = 0; x < w; x++) {
            if (*pix++ == 0xFFFF && n < total) {
                part = &fx->parts[n];
                part->dir.x = rand8() & 0xF;
                part->vel.x = (x - w / 2) * 12;
                part->vel.y = (h / 2 - y) * 12;
                part->scale = 3.0f;
                part->vel.z = 1.0f;
                part->speed = (s32) ((u32) (rand8() * 5) >> 7) * 0.1f + 3.0f;
                n++;
                part++;
            }
        }
    }
    for (i = 0; i < total - n; i++, part++) {
        part->scale = part->vel.z = part->pos.x = part->pos.y = part->pos.z = 0.0f;
    }
    HuSprGrpKill(grp);
    HuSprKill(sprId);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3BFA00", func_8010CEF4_boardresult);
#endif

/* Starts a particle at pos with velocity vel and colour (r, g, b) in the first free slot of model's
   effect; returns the slot (one past the last if none is free). */
BrFxPart* func_8010D28C_boardresult(s16 model, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, u8 r, u8 g, u8 b) {
    BrFxPart* part;
    s16 i;
    s16 count;

    count = BR_FXDATA(model)->count;
    part = BR_FXWORK(model)->parts;
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
void func_8010D36C_boardresult(s16 model) {
    BrFxData* data;
    BrFxWork* fx;
    BrFxPart* part;
    BrFxPart* src;
    BrFxPart* dst;
    s16 count;
    s16 i;
    s16 j;
    s16 n;
    f32 t;
    u8 r;
    u8 g;
    u8 b;

    data = BR_FXDATA(model);
    fx = BR_FXWORK(model);
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
void func_8010D87C_boardresult(s16 model) {
    BrFxData* data;
    BrFxWork* fx;
    BrFxPart* part;
    s16 count;
    s16 i;

    data = BR_FXDATA(model);
    fx = BR_FXWORK(model);
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

void func_8010DA30_boardresult(void);

BoardResultWork* func_8010D9D0_boardresult(void) {
    Process* process;
    BoardResultWork* work;

    process = omAddPrcObj(func_8010DA30_boardresult, 0x3F00, 0x2000, 0);
    work = HuMemAllocTag(sizeof(BoardResultWork), 0x7918);
    process->user_data = work;
    work->unk_18.x = 0.0f;
    work->unk_18.y = 100.0f;
    work->unk_18.z = 0.0f;
    return work;
}

/* Spark colours (r, g, b, pad); one table in the overlay's .data (splat splits it at +1 and +2). */
extern u8 D_8010E950_boardresult[4][4];

// event e8: NON_MATCHING, masked 17 (670 vs 669): four extra nops after calls, the colour index
// (retail re-masks it with 0xFF and addresses splat's split labels D_8010D6C1/D_8010D6C2; this
// indexes the one table). Logic checked.
#ifdef NON_MATCHING
/* Two sparklers circling work->unk_18 (150 units out, opposite each other), each leaving sparks
   behind it in a spiral around its direction of travel. Never returns. */
void func_8010DA30_boardresult(void) {
    s16 angle[2];
    Vec cur[2];
    Vec prev[2];
    f32 roll[2];
    f32 tilt[2];
    BoardResultWork* work;
    HmfData* hmf;
    HmfModelData_Unk64_Unk60_Struct* obj;
    HmfModelData_Unk64_Unk60_Unk54_Struct* face;
    BrFxWork* fx;
    s16 model;
    s16 i;
    s16 j;
    s16 count;
    f32 x;
    f32 y;
    f32 z;
    f32 a;
    f32 len;
    f32 ux;
    f32 uy;
    f32 uz;
    u8 k;

    work = HuPrcCurrentGet()->user_data;
    model = func_8000B108_main(0xB0034, 0x6A8);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    hmf = HmfModelData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        obj = &hmf->unk60[j];
        count = obj->unk22;
        face = obj->unk54;
        for (i = 0; i < count; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_8010D36C_boardresult);
    func_800138EC_main(model, 8, 8);
    fx = BR_FXWORK(model);
    func_8001C258_main(model, 4, 4);
    func_8001C258_main(model, 4, 0);
    func_80013954_main(model, 0);
    fx->hook = func_8010D87C_boardresult;
    func_800138EC_main(model, 2, 0);
    work->unk_30 = work->unk_18;
    cur[0].x = sindf(0.0f) * 150.0f + work->unk_30.x;
    cur[0].y = work->unk_30.y;
    cur[0].z = cosdf(0.0f) * 150.0f + work->unk_30.z;
    prev[0] = cur[0];
    tilt[0] = roll[0] = 0.0f;
    angle[0] = 0;
    cur[1].x = sindf(180.0f) * 150.0f + work->unk_30.x;
    cur[1].y = work->unk_30.y;
    cur[1].z = cosdf(180.0f) * 150.0f + work->unk_30.z;
    prev[1] = cur[1];
    tilt[1] = roll[1] = 180.0f;
    angle[1] = 180;
    while (TRUE) {
        HuPrcVSleep();
        for (i = 0; i < 2; i++) {
            prev[i] = cur[i];
            x = sindf(angle[i]) * 150.0f;
            z = cosdf(angle[i]) * 150.0f;
            a = sindf(tilt[i]) * 10.0f;
            cur[i].x = x * cosdf(a) + work->unk_30.x;
            cur[i].y = x * -sindf(a) + work->unk_30.y;
            cur[i].z = z + work->unk_30.z;
            angle[i] += 5;
            if (angle[i] > 360) {
                angle[i] -= 360;
            }
            roll[i] += 20.0f;
            if (roll[i] > 360.0f) {
                roll[i] -= 360.0f;
            }
            tilt[i] += 1.0f;
            if (tilt[i] > 360.0f) {
                tilt[i] -= 360.0f;
            }
            x = prev[i].x - cur[i].x;
            y = prev[i].y - cur[i].y;
            z = prev[i].z - cur[i].z;
            len = HuSqrtf(x * x + y * y + z * z);
            if (len != 0.0f) {
                x /= len;
                y /= len;
                z /= len;
                a = roll[i];
                /* (0, 1, 0) turned by a about the direction of travel */
                ux = x * y * (1.0f - cosdf(a)) - z * sindf(a);
                uy = y * y + (1.0f - y * y) * cosdf(a);
                uz = y * z * (1.0f - cosdf(a)) + x * sindf(a);
                ux = (x * 0.7f + ux * 0.3f) * len * 0.7f;
                uy = (y * 0.7f + uy * 0.3f) * len * 0.7f;
                uz = (z * 0.7f + uz * 0.3f) * len * 0.7f;
                k = rand8() & 3;
                func_8010D28C_boardresult(model, cur[i].x, cur[i].y, cur[i].z, ux, uy, uz,
                                         D_8010E950_boardresult[k][0], D_8010E950_boardresult[k][1],
                                         D_8010E950_boardresult[k][2])->scale = 1.0f;
                ux = -(x * y * (1.0f - cosdf(a)) - z * sindf(a));
                uy = -(y * y + (1.0f - y * y) * cosdf(a));
                uz = -(y * z * (1.0f - cosdf(a)) + x * sindf(a));
                ux = (x * 0.7f + ux * 0.3f) * len * 0.7f;
                uy = (y * 0.7f + uy * 0.3f) * len * 0.7f;
                uz = (z * 0.7f + uz * 0.3f) * len * 0.7f;
                k = rand8() & 3;
                func_8010D28C_boardresult(model, cur[i].x, cur[i].y, cur[i].z, ux, uy, uz,
                                         D_8010E950_boardresult[k][0], D_8010E950_boardresult[k][1],
                                         D_8010E950_boardresult[k][2])->scale = 1.0f;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3BFA00", func_8010DA30_boardresult);
#endif
