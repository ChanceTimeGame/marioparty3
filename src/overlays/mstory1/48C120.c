#include "common.h"
#include "mallocblock.h"

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i runs
   from points[i] to points[i + 1] and covers [segs[i].start, segs[i].end] of the path's
   length (0..1). flags & 1: closed (the last segment returns to points[0]). Same as opboard's. */
typedef struct ObPathSeg {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
} ObPathSeg; /* size = 0x8 */

typedef struct ObPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 flags;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ Vec *points;
    /* 0x0C */ ObPathSeg *segs;
} ObPath; /* size = 0x10 */

typedef struct TexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} TexAnimSlot; /* size = 0xC */

extern TexAnimSlot *D_800D1714_main;
extern f32 D_800CE17C_main[];
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, s32);
s32 func_80050064_main(s32 write);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);

void func_80105FF4_mstory1(void);
void func_80106B30_mstory1(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106D80_mstory1(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106B14_mstory1(omObjData *obj, Vec *to, s32 frames);
void func_80106D64_mstory1(omObjData *obj, Vec *to, s32 frames);
void func_8010704C_mstory1(omObjData *obj, Vec *to, s32 frames);
s32 func_8010726C_mstory1(s16 model);

extern u32 D_80114A80_mstory1; /* main object state */
extern s32 D_80114A84_mstory1; /* 1: the scene was seen before, A skips it */
extern s8 D_80114A88_mstory1;
extern Vec D_80114A8C_mstory1; /* camera position */
extern Vec D_80114A98_mstory1; /* camera target */
extern Vec D_80114AA4_mstory1; /* camera up */
extern s32 D_80114AB0_mstory1;
extern s16 D_801158B0_mstory1; /* message window */
extern s16 D_801158B2_mstory1; /* background model */
extern s32 D_801158B4_mstory1; /* the controller that drives the story messages */
extern s16 D_801158B8_mstory1; /* background sprite */
extern s32 D_801158E4_mstory1;


// the A-press test: retail andi/sltu, KMC folds it to srl/andi (masked 2)
#ifdef NON_MATCHING
void func_80105C90_mstory1(omObjData *obj) {
    u32 state = D_80114A80_mstory1;

    switch (state) {
    case 0:
        HuAudSeqPlay(0x26);
        state++;
        break;
    case 1:
        state += WipeStatGet() == 0;
        break;
    case 2:
        if (D_80114A84_mstory1 == 1) {
            state += (D_800D5558_main[D_801158B4_mstory1] & 0x1000) > 0;
        }
        break;
    case 3:
        WipeCreateOut(2, 0x14);
        HuAudSeqFadeOut(0x1E);
        state++;
        break;
    case 4:
        if (WipeStatGet() == 0) {
            func_8005F524_main();
            func_80050064_main(1);
            omOvlReturnEx(1);
        }
        break;
    }
    D_80114A80_mstory1 = state;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105C90_mstory1);
#endif

void func_80105D80_mstory1(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80114A88_mstory1 == 0) {
            WipeCreateOut(2, 0x14);
            HuAudSeqFadeOut(0x1E);
            D_80114A88_mstory1 = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            func_8005F524_main();
            func_80050064_main(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105E00_mstory1(void) {
    D_801158B8_mstory1 = InitEspriteSlot(func_8000B838_main(0x1D0012), 0, 0);
    func_8000BBD4_main(D_801158B8_mstory1, 0xA0, 0x78);
    func_8000BC48_main(D_801158B8_mstory1, 0x4000);
    D_801158B2_mstory1 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_801158B2_mstory1, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_801158B2_mstory1, 2, 0);
    func_8001C814_main(D_801158B2_mstory1, 1, 1);
}

void func_80105EC0_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, 4, 4);
    func_8000BB94_main(D_801158B8_mstory1);
}

void func_80105EF4_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, 4, 0);
    func_8000BB54_main(D_801158B8_mstory1);
}

void func_80105F28_mstory1(omObjData *obj) {
    D_800CE17C_main[0] = D_80114A8C_mstory1.x;
    D_800CE17C_main[1] = D_80114A8C_mstory1.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_80114A8C_mstory1, &D_80114A98_mstory1, &D_80114AA4_mstory1);
    Hu3DCamUpdateMtx(0);
}

void func_80105FA8_mstory1(void) {
    D_80114A80_mstory1 = 3;
}

void func_80105FB8_mstory1(s32 arg0) {
    D_801158E4_mstory1 = arg0;
    D_80114AB0_mstory1 = 0;
    omAddPrcObj(func_80105FF4_mstory1, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105FF4_mstory1);

s32 func_80106894_mstory1(void) {
    return D_80114AB0_mstory1;
}

void func_801068A0_mstory1(void) {
}

void func_801068A8_mstory1(void) {
}

void func_801068B0_mstory1(s16 model, s16 anim, s16 frame) {
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

void func_80106984_mstory1(void) {
    D_801158B0_mstory1 = func_80060880_main(0xA0, 0xC2, 0x14);
    func_8005FE54_main(D_801158B0_mstory1, 1 << D_801158B4_mstory1);
    func_8005B6BC_main(D_801158B0_mstory1, GwStory.unk1 + 0x1C00, 0);
}

void func_801069EC_mstory1(void) {
    func_8005D294_main(D_801158B0_mstory1);
    func_80060C14_main(D_801158B0_mstory1, 1);
}

void func_80106A1C_mstory1(void) {
    func_80060EA8_main(D_801158B0_mstory1, 1);
}

void func_80106A40_mstory1(s32 mess) {
    func_8005B43C_main(D_801158B0_mstory1, mess, -1, -1);
    while (func_8005E0C0_main(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

void func_80106A94_mstory1(s32 mess) {
    func_8005B43C_main(D_801158B0_mstory1, mess, -1, -1);
}

void func_80106AC0_mstory1(void) {
    while (func_8005E0C0_main(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106AFC_mstory1(s32 chr) {
    return (chr == GwStory.unk1) ? -1 : 0;
}

void func_80106B14_mstory1(omObjData *obj, Vec *to, s32 frames) {
    func_80106B30_mstory1(obj, to, frames, 1);
}

// register allocation; retail converts frames separately for the divide (masked 10)
#ifdef NON_MATCHING
/* walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning
   it to face the way first when `turn` is set */
void func_80106B30_mstory1(omObjData *obj, Vec *to, s32 frames, s32 turn) {
    Vec start;
    Vec delta;
    Vec step;
    Vec pos;
    s16 model;
    f32 t;

    model = obj->model[1];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    delta.x = to->x - start.x;
    delta.y = to->y - start.y;
    delta.z = to->z - start.z;
    if (turn) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(delta.z, delta.x) - 90.0f), 0.0f);
    }
    step.x = delta.x / frames;
    step.y = delta.y / frames;
    step.z = delta.z / frames;
    for (t = 0.0f; t < frames; t += 1.0f) {
        pos.x = t * step.x + start.x;
        pos.y = t * step.y + start.y;
        pos.z = t * step.z + start.z;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], pos.x, -5.0f, pos.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, to->x, to->y, to->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], to->x, -5.0f, to->z);
    }
    HuPrcVSleep();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106B30_mstory1);
#endif

void func_80106D64_mstory1(omObjData *obj, Vec *to, s32 frames) {
    func_80106D80_mstory1(obj, to, frames, 1);
}

// register allocation; retail converts frames separately for the divide (masked 9)
#ifdef NON_MATCHING
/* as func_80106B30_mstory1, but the second model follows in 3D */
void func_80106D80_mstory1(omObjData *obj, Vec *to, s32 frames, s32 turn) {
    Vec start;
    Vec delta;
    Vec step;
    Vec pos;
    s16 model;
    f32 t;

    model = obj->model[1];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    delta.x = to->x - start.x;
    delta.y = to->y - start.y;
    delta.z = to->z - start.z;
    if (turn) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(delta.z, delta.x) - 90.0f), 0.0f);
    }
    step.x = delta.x / frames;
    step.y = delta.y / frames;
    step.z = delta.z / frames;
    for (t = 0.0f; t < frames; t += 1.0f) {
        pos.x = t * step.x + start.x;
        pos.y = t * step.y + start.y;
        pos.z = t * step.z + start.z;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, to->x, to->y, to->z);
    HuPrcVSleep();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106D80_mstory1);
#endif

void func_80106F94_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106B14_mstory1(obj, &to, frames);
}

void func_80106FC0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106B30_mstory1(obj, &to, frames, turn);
}

void func_80106FF0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106D64_mstory1(obj, &to, frames);
}

void func_8010701C_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106D80_mstory1(obj, &to, frames, turn);
}

/* turns obj's model to the rotation `to` in `frames` frames, easing out */
void func_8010704C_mstory1(omObjData *obj, Vec *to, s32 frames) {
    Vec start;
    Vec delta;
    Vec rot;
    s16 model;
    f32 t;
    f32 a;

    model = obj->model[1];
    start.x = HmfModelData[model].rot.x;
    start.y = HmfModelData[model].rot.y;
    start.z = HmfModelData[model].rot.z;
    delta.x = to->x - start.x;
    delta.y = to->y - start.y;
    delta.z = to->z - start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        a = 90.0f / frames * t;
        rot.x = sindf(a) * delta.x + start.x;
        rot.y = sindf(a) * delta.y + start.y;
        rot.z = sindf(a) * delta.z + start.z;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, to->x, to->y, to->z);
    HuPrcVSleep();
}

void func_801071F4_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_8010704C_mstory1(obj, &to, frames);
}

void func_80107220_mstory1(s16 model) {
    HuPrcSleep(10);
    while (func_8010726C_mstory1(model) == 0) {
        HuPrcVSleep();
    }
}

/* -1 once the model's motion has played to its end */
s32 func_8010726C_mstory1(s16 model) {
    s32 done;
    f32 frame;

    frame = func_8001C7D0_main(model);
    done = 0;
    if (frame == -1.0f) {
        if (D_800CCF58_main[HmfModelData[model].unk02].unk02 <= HmfModelData[model].unk40) {
            done = -1;
        }
    }
    return done;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80107318_mstory1);

ObPath *func_801074C0_mstory1(Vec *points, s16 flags) {
    ObPath *path;
    Vec *prev;
    Vec *cur;
    ObPathSeg *seg;
    f32 total;
    f32 pos;
    f32 len;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 n;
    s16 i;

    path = HuMemAllocTag(sizeof(ObPath), 0x7918);
    path->flags = flags;
    path->points = points;
    prev = points;
    cur = prev + 1;
    total = 0.0f;
    n = 0;
    while (cur->x != 9999.0f || cur->y != 9999.0f || cur->z != 9999.0f) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
        n++;
        cur++;
        prev++;
    }
    if (flags & 1) {
        dx = points->x - prev->x;
        dy = points->y - prev->y;
        dz = points->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    n++;
    path->count = n;
    seg = HuMemAllocTag(n * sizeof(ObPathSeg), 0x7918);
    path->segs = seg;
    prev = points;
    cur = prev + 1;
    pos = 0.0f;
    for (i = 0; i < n; i++, prev++, cur++, seg++) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        if ((flags & 1) && i == n - 1) {
            dx = points->x - prev->x;
            dy = points->y - prev->y;
            dz = points->z - prev->z;
        }
        len = HuSqrtf(dx * dx + dy * dy + dz * dz);
        seg->start = pos / total;
        seg->end = (pos + len) / total;
        if (seg->end > 1.0f) {
            seg->end = 1.0001f;
        }
        pos += len;
    }
    return path;
}

#ifdef NON_MATCHING
/* the point at t (0..1) along a path: a spline through the four points around the segment t
   falls in */
void func_801077C4_mstory1(ObPath *path, f32 t, Vec *out) {
    f32 p[4];
    f32 times[4];
    ObPathSeg *segs;
    Vec *pts;
    s16 i;

    if (t >= 1.0f) {
        out->x = path->points[path->count - 1].x;
        out->y = path->points[path->count - 1].y;
        out->z = path->points[path->count - 1].z;
        return;
    }
    for (i = 0, segs = path->segs; i < path->count; i++, segs++) {
        if (t <= segs->start) {
            break;
        }
    }
    i--;
    i = (i < 0) ? 0 : i;
    if (i >= path->count - 1) {
        i--;
    }
    segs = path->segs;
    if (path->flags & 1) {
        times[0] = (i == 0) ? -(1.0f - segs[path->count - 1].start) : segs[i - 1].start;
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[path->count - 1].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[0].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[0].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[0].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].z : pts[i + 2].z;
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = segs[i - 1].start;
        }
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[0].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].z : pts[i + 2].z;
    }
    out->z = func_80018ACC_main(p, times, t);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801077C4_mstory1);
#endif

void func_8010806C_mstory1(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010809C_mstory1);

void func_801081D8_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801081E0_mstory1);

void func_801085F0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C88_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CB0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CBC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CC8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CD4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CE0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CEC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CF8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D04_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D10_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D50_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D70_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DCC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801085F8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109014_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801090D8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010910C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E08_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E14_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E20_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E38_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E40_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E4C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109140_mstory1);

void func_80109470_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E64_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109478_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010980C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109888_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801099F8_mstory1);

void func_80109C20_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E7C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E94_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EA0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EAC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EB8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EC4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114ED0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EDC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EE8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F00_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F0C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109C28_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109DC0_mstory1);

void func_80109FD0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F30_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109FD8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010A424_mstory1);

void func_8010A608_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010A610_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010AA98_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010AC40_mstory1);

void func_8010B108_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B110_mstory1);

void func_8010B300_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F48_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F54_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F78_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F84_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FB4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FC0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FCC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FD8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FE4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FF0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115008_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B308_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B384_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B3B8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B4E4_mstory1);

void func_8010B69C_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B6A4_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B9C0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115038_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115050_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_8011505C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010BB08_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010BBEC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010BC68_mstory1);
