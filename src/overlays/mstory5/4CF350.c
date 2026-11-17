#include "common.h"

// story i1
/* a story-scene actor: its object and the action its process runs every frame (as mstory1's) */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
} StoryActor; /* size = 0x18 */

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i covers
   [segs[i].start, segs[i].end] of the path's length (0..1). flags & 1: closed. As mstory1's. */
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
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, s32);
s32 func_80050064_main(s32 write);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
void func_80032FC0_main(s16, s32, s32);
s16 func_800329B4_main(void *);

extern u32 D_80114730_mstory5; /* main object state */
extern s32 D_80114734_mstory5; /* 1: the scene was seen before, A skips it */
extern s8 D_80114738_mstory5;
extern Vec D_8011473C_mstory5; /* camera position */
extern Vec D_80114748_mstory5; /* camera target */
extern Vec D_80114754_mstory5; /* camera up */
extern s32 D_80114760_mstory5;
extern s16 D_801151B0_mstory5; /* message window */
extern s16 D_801151B2_mstory5; /* background model */
extern s32 D_801151B4_mstory5; /* the controller that drives the story messages */
extern s16 D_801151B8_mstory5; /* background sprite */
extern s32 D_801151E4_mstory5;
extern StoryActor D_801151F0_mstory5[];
extern s16 D_80115364_mstory5; /* shadow model, linked by every actor */
extern const Vec D_80114A88_mstory5;

void func_80106028_mstory5(void);
void func_801085D8_mstory5(omObjData *obj);
void func_80106B64_mstory5(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106DB4_mstory5(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106B48_mstory5(omObjData *obj, Vec *to, s32 frames);
void func_80106D98_mstory5(omObjData *obj, Vec *to, s32 frames);
void func_80107080_mstory5(omObjData *obj, Vec *to, s32 frames);
s32 func_801072A0_mstory5(s16 model);
void func_80107254_mstory5(s16 model);
void func_801068E4_mstory5(s16 model, s16 anim, s16 frame);
void func_8010E3F0_mstory5(omObjData *a, omObjData *b);
void func_80105BDC_mstory5(omObjData *obj);
void func_80105CCC_mstory5(omObjData *obj);
void func_80105E34_mstory5(void);
void func_80105F5C_mstory5(omObjData *obj);
void func_8010842C_mstory5(void);
void func_801100AC_mstory5(void);
extern s16 D_801151B6_mstory5; /* low half of D_801151B4_mstory5 */
extern s16 D_80115368_mstory5;
void func_801069B8_mstory5(void);
void func_801085E0_mstory5(void);
void func_801097B8_mstory5(void);
void func_8010ABE4_mstory5(void);
void func_8010AF44_mstory5(void);
void func_8010B77C_mstory5(void);
void func_8010C4B8_mstory5(void);
void func_8010C85C_mstory5(void);
void func_8010CBE8_mstory5(void);
void func_8010DB30_mstory5(void);
void func_8010DC78_mstory5(void);
void func_8010E558_mstory5(void);
void func_8010E5D0_mstory5(void);
void func_8010F2BC_mstory5(void);
// end story i1

/* the scene for each story step (GwPlayer[0].coin), and the flag set once it has been seen */
void (*const D_801148A0_mstory5[2])(void) = { func_801100AC_mstory5, func_8010842C_mstory5 };
const s32 D_801148A8_mstory5[2] = { 0x3A, 0x3C };

void func_801059A0_mstory5(void) {
    s16 step;

    func_800142A0_main(0x3C);
    omInitObjMan(0x1E, 0x1E);
    func_8005A6B0_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 35.0f, 80.0f, 8000.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    {
        omObjData *obj = omAddObj(0x7FDA, 0, 0, -1, func_80105F5C_mstory5);
        omSetStatBit(obj, 0xA0);
        func_80105F5C_mstory5(obj);
    }
    omAddObj(0, 0, 0, -1, func_80105BDC_mstory5);
    omAddObj(0, 0, 0, -1, func_80105CCC_mstory5);
    func_80105E34_mstory5();
    for (D_801151B4_mstory5 = 0; D_801151B4_mstory5 < 4; D_801151B4_mstory5++) {
        if (CheckControllerRead(D_801151B6_mstory5) != 0) {
            break;
        }
    }
    if (D_801151B4_mstory5 >= 4) {
        D_801151B4_mstory5 = 0;
    }
    step = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        step = 1;
    }
    D_801148A0_mstory5[step]();
    if (_CheckFlag(D_801148A8_mstory5[step]) != 0) {
        D_80114734_mstory5 = 1;
    } else {
        _SetFlag(D_801148A8_mstory5[step]);
    }
    WipeCreateIn(2, 0x10);
}

#ifdef NON_MATCHING
void func_80105BDC_mstory5(omObjData *obj) {
    u32 state = D_80114730_mstory5;

    switch (state) {
    case 0:
        HuAudSeqPlay(0x26);
        state++;
        break;
    case 1:
        state += WipeStatGet() == 0;
        break;
    case 2:
        if (D_80114734_mstory5 == 1) {
            state += (D_800D5558_main[D_801151B4_mstory5] & 0x1000) > 0;
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
    D_80114730_mstory5 = state;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80105BDC_mstory5);
#endif

void func_80105CCC_mstory5(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80114738_mstory5 == 0) {
            WipeCreateOut(2, 0x14);
            HuAudSeqFadeOut(0x1E);
            D_80114738_mstory5 = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            func_8005F524_main();
            func_80050064_main(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105D4C_mstory5(void) {
    func_8001C814_main(D_801151B2_mstory5, 4, 0);
    func_8001C814_main(D_801151B2_mstory5, 1, 0);
    func_8001C6A8_main(D_801151B2_mstory5, 0.0f);
    HuAudFXPlay(0x216);
}

void func_80105DA0_mstory5(void) {
    func_8001C814_main(D_801151B2_mstory5, 4, 4);
    func_8001C814_main(D_801151B2_mstory5, 1, 0);
    func_8001C6A8_main(D_801151B2_mstory5, D_800CCF58_main[HmfModelData[D_801151B2_mstory5].unk02].unk02);
}

void func_80105E34_mstory5(void) {
    D_801151B8_mstory5 = InitEspriteSlot(func_8000B838_main(0x1D0012), 0, 0);
    func_8000BBD4_main(D_801151B8_mstory5, 0xA0, 0x78);
    func_8000BC48_main(D_801151B8_mstory5, 0x4000);
    D_801151B2_mstory5 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_801151B2_mstory5, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_801151B2_mstory5, 2, 0);
    func_8001C814_main(D_801151B2_mstory5, 1, 1);
}

void func_80105EF4_mstory5(void) {
    func_8001C258_main(D_801151B2_mstory5, 4, 4);
    func_8000BB94_main(D_801151B8_mstory5);
}

void func_80105F28_mstory5(void) {
    func_8001C258_main(D_801151B2_mstory5, 4, 0);
    func_8000BB54_main(D_801151B8_mstory5);
}

void func_80105F5C_mstory5(omObjData *obj) {
    D_800CE17C_main[0] = D_8011473C_mstory5.x;
    D_800CE17C_main[1] = D_8011473C_mstory5.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_8011473C_mstory5, &D_80114748_mstory5, &D_80114754_mstory5);
    Hu3DCamUpdateMtx(0);
}

void func_80105FDC_mstory5(void) {
    D_80114730_mstory5 = 3;
}

void func_80105FEC_mstory5(s32 arg0) {
    D_801151E4_mstory5 = arg0;
    D_80114760_mstory5 = 0;
    omAddPrcObj(func_80106028_mstory5, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80106028_mstory5);

s32 func_801068C8_mstory5(void) {
    return D_80114760_mstory5;
}

void func_801068D4_mstory5(void) {
}

void func_801068DC_mstory5(void) {
}

void func_801068E4_mstory5(s16 model, s16 anim, s16 frame) {
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

void func_801069B8_mstory5(void) {
    D_801151B0_mstory5 = func_80060880_main(0xA0, 0xC2, 0x14);
    func_8005FE54_main(D_801151B0_mstory5, 1 << D_801151B4_mstory5);
    func_8005B6BC_main(D_801151B0_mstory5, GwStory.unk1 + 0x1C00, 0);
}

void func_80106A20_mstory5(void) {
    func_8005D294_main(D_801151B0_mstory5);
    func_80060C14_main(D_801151B0_mstory5, 1);
}

void func_80106A50_mstory5(void) {
    func_80060EA8_main(D_801151B0_mstory5, 1);
}

void func_80106A74_mstory5(s32 mess) {
    func_8005B43C_main(D_801151B0_mstory5, mess, -1, -1);
    while (func_8005E0C0_main(D_801151B0_mstory5) != 0) {
        HuPrcVSleep();
    }
}

void func_80106AC8_mstory5(s32 mess) {
    func_8005B43C_main(D_801151B0_mstory5, mess, -1, -1);
}

void func_80106AF4_mstory5(void) {
    while (func_8005E0C0_main(D_801151B0_mstory5) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106B30_mstory5(s32 chr) {
    return (chr == GwStory.unk1) ? -1 : 0;
}

void func_80106B48_mstory5(omObjData *obj, Vec *to, s32 frames) {
    func_80106B64_mstory5(obj, to, frames, 1);
}

#ifdef NON_MATCHING
/* walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning
   it to face the way first when `turn` is set */
void func_80106B64_mstory5(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80106B64_mstory5);
#endif

void func_80106D98_mstory5(omObjData *obj, Vec *to, s32 frames) {
    func_80106DB4_mstory5(obj, to, frames, 1);
}

#ifdef NON_MATCHING
/* as func_80106B64_mstory5, but the second model follows in 3D */
void func_80106DB4_mstory5(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80106DB4_mstory5);
#endif

void func_80106FC8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106B48_mstory5(obj, &to, frames);
}

void func_80106FF4_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106B64_mstory5(obj, &to, frames, turn);
}

void func_80107024_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106D98_mstory5(obj, &to, frames);
}

void func_80107050_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106DB4_mstory5(obj, &to, frames, turn);
}

void func_80107080_mstory5(omObjData *obj, Vec *to, s32 frames) {
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

void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80107080_mstory5(obj, &to, frames);
}

void func_80107254_mstory5(s16 model) {
    HuPrcSleep(10);
    while (func_801072A0_mstory5(model) == 0) {
        HuPrcVSleep();
    }
}

s32 func_801072A0_mstory5(s16 model) {
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

void func_8010734C_mstory5(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(HmfModelData[obj->model[1]].rot.y);
    dz = speed * cosdf(HmfModelData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        HmfModelData[obj->model[2]].pos.x = HmfModelData[obj->model[1]].pos.x += dx;
        HmfModelData[obj->model[2]].pos.z = HmfModelData[obj->model[1]].pos.z += dz;
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801074E8_mstory5);

ObPath *func_80107850_mstory5(Vec *points, s16 flags) {
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
void func_80107B54_mstory5(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80107B54_mstory5);
#endif

void func_801083FC_mstory5(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* story step 1's scene: shadow models, then every actor's and the script's processes */
void func_8010842C_mstory5(void) {
    func_801069B8_mstory5();
    D_80115364_mstory5 = func_8000B108_main(9, 0x2B9);
    D_80115368_mstory5 = func_8000B108_main(0x83, 0x2B9);
    omAddPrcObj(func_801085E0_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_801097B8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010ABE4_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010AF44_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010B77C_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010C4B8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010C85C_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010CBE8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010E558_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010E5D0_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010DC78_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_8010DB30_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010F2BC_mstory5, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115364_mstory5, 4, 4);
    func_8001C258_main(D_80115368_mstory5, 4, 4);
}

void func_801085D8_mstory5(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801085E0_mstory5);

void func_80108A20_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148C4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114900_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011490C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114918_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114924_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114930_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011493C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114948_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114954_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114960_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011496C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011498C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801149AC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801149CC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801149EC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A18_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80108A28_mstory5);

void func_80109698_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C624_main(model, HmfModelData[obj->motion[9]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    HuPrcSleep(80);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

void func_8010975C_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80114A88_mstory5, 10);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

void func_80109790_mstory5(void) {
    func_8010E3F0_mstory5(D_801151F0_mstory5[0].obj, D_801151F0_mstory5[3].obj);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A3C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A48_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A54_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A80_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A88_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801097B8_mstory5);

void func_80109B28_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AA0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109B30_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109E70_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109F48_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010A0A8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010ABC4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010ABE4_mstory5);

void func_8010AE0C_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AB8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AD0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114ADC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AE8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AF4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B00_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B24_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B54_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BA8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BB4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BCC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BD8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BE4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BF0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010AE14_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010AF44_mstory5);

void func_8010B318_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B320_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B5DC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B6F8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B77C_mstory5);

void func_8010B9CC_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B9D4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010C4B8_mstory5);

void func_8010C69C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010C6A4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010C85C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CA04_mstory5);

void func_8010CBE0_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CBE8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CFE4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D214_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D230_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D460_mstory5);

void func_8010D47C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D484_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D560_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D594_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D7D8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DADC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DB30_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DC78_mstory5);

void func_8010DE7C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DE84_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E1A0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E3F0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E538_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E558_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E5D0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E648_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E6B4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E7B0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E870_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E8C0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010EA34_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010EBCC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010EDFC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F02C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F0B8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C44_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C50_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C5C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114CA8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F14C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F240_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F2BC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F41C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F4D0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F7D4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011007C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801100AC_mstory5);

void func_80110200_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80110208_mstory5);

void func_80110618_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D20_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D2C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D38_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D44_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D50_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D5C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D68_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D74_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D80_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114DA0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114DC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114DE0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E00_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E30_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80110620_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801113BC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111480_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801114B4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E54_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EA8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EB0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EB8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EC4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801114E8_mstory5);

void func_80111818_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EDC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111820_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111B60_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111C48_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111DB8_mstory5);

void func_80111FE0_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EF4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F24_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F30_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F3C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F48_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F9C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111FE8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112104_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112514_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011275C_mstory5);

void func_80112994_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011299C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112F38_mstory5);

void func_80113130_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113138_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113470_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113618_mstory5);

void func_8011396C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113974_mstory5);

void func_80113B64_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FD8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FE4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FF0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115014_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115020_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011502C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115038_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115050_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115068_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115074_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115080_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115098_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150B0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150BC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113B6C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113CF8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113D2C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113E58_mstory5);

void func_80114010_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80114018_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80114334_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150EC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150F8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115110_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011511C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115128_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115134_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011514C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011447C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80114560_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801145DC_mstory5);
