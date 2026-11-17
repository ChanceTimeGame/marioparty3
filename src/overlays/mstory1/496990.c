#include "common.h"
#include "mallocblock.h"

/* mstory1 (story mode chapter 1): the chapter's opening cutscene. Eight actors, each run by a
   process that loops calling its current hook (MsActor.func) once a frame; the hooks are scene
   steps that hand the next step to other actors. */

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i runs from
   points[i] to points[i + 1] and covers [segs[i].start, segs[i].end] of the path's length
   (0..1). flags & 1: closed. (opboard's ObPath.) */
typedef struct MsPathSeg {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
} MsPathSeg; /* size = 0x8 */

typedef struct MsPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 flags;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ Vec *points;
    /* 0x0C */ MsPathSeg *segs;
} MsPath; /* size = 0x10 */

typedef struct MsActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *obj); /* the current scene step, called every frame */
    /* 0x08 */ s32 flags; /* scene progress bits other actors wait on */
    /* 0x0C */ s32 sfxOn; /* func_801147D0_mstory1 started a looping sound */
    /* 0x10 */ s32 sfxId;
    /* 0x14 */ s32 sfx; /* its handle (CharFXPlay's s16, sign-extended) */
} MsActor; /* size = 0x18 */

typedef struct MsTexAnim { /* D_800D1714_main[] */
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0xA];
} MsTexAnim; /* size = 0xC */

typedef struct MsPart { /* a model part (func_8001D33C_main) */
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ char unk28[0x18];
    /* 0x40 */ Vec unk40;
} MsPart;

/* 48C120.c */
void func_80105FA8_mstory1(void);
void func_80105FB8_mstory1(s32 arg0);
s32 func_80106894_mstory1(void);
void func_801068B0_mstory1(s16 model, s16 anim, s16 slot);
void func_80106984_mstory1(void);
void func_801069EC_mstory1(void);
void func_80106A1C_mstory1(void);
void func_80106A40_mstory1(s32 mess);
s32 func_80106AFC_mstory1(s32 chr);
void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames);
void func_80106B30_mstory1(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_8010704C_mstory1(omObjData *obj, const Vec *rot, s32 frames);
void func_801071F4_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107220_mstory1(s16 model);

/* main */
void func_8001C258_main(s16 arg0, s32 arg1, s32 arg2);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);
void *func_8001D33C_main(s16, const char *);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
extern s32 D_800A178C_main[][6];
extern MsTexAnim *D_800D1714_main;

void func_80111218_mstory1(omObjData *obj);
void func_8011162C_mstory1(void);
void func_80111220_mstory1(void);
void func_80111634_mstory1(omObjData *obj);
void func_801121E4_mstory1(omObjData *obj);
void func_801122A8_mstory1(omObjData *obj);
void func_801122DC_mstory1(omObjData *obj);
void func_80112310_mstory1(void);
void func_8011263C_mstory1(void);
void func_80112644_mstory1(omObjData *obj);
void func_80112984_mstory1(omObjData *obj);
void func_80112A68_mstory1(omObjData *obj);
void func_80112BD8_mstory1(void);
void func_80112E14_mstory1(void);
void func_80112E1C_mstory1(omObjData *obj);
void func_80112F4C_mstory1(void);
void func_80113144_mstory1(void);
void func_8011314C_mstory1(omObjData *obj);
void func_801134B4_mstory1(void);
void func_80113694_mstory1(void);
void func_8011369C_mstory1(omObjData *obj);
void func_80113908_mstory1(void);
void func_80113AAC_mstory1(omObjData *obj);
void func_80113D2C_mstory1(void);
void func_80113D34_mstory1(void);
void func_80113F20_mstory1(void);
void func_80113F28_mstory1(omObjData *obj);
void func_80114050_mstory1(omObjData *obj);
void func_80114084_mstory1(void);
void func_801141B0_mstory1(void);
void func_80114364_mstory1(void);
void func_8011436C_mstory1(omObjData *obj);
void func_801147D0_mstory1(s32 idx, s32 seId);
void func_801148B4_mstory1(s32 idx);
void func_80114930_mstory1(void);

extern s32 D_80114BC0_mstory1; /* .data (48BE30): the board-sway process runs */
extern Vec D_80114BC4_mstory1[]; /* .data: two paths */
extern Vec D_80114BF4_mstory1[];
extern MsActor D_80115B70_mstory1[8];
extern Vec D_80115C30_mstory1[8]; /* the actors' start positions */
extern s16 D_80115C90_mstory1; /* the shadow model every actor links */
extern s16 D_80115C92_mstory1;
extern s16 D_80115C94_mstory1[4];
extern s32 D_80115C9C_mstory1[3]; /* texture animation slots */
extern s16 D_80115CA8_mstory1;

MsPath *func_80110500_mstory1(Vec *points, s16 flags);
void func_80110804_mstory1(MsPath *path, f32 t, Vec *out);
void func_801110AC_mstory1(MsPath *path);

/* the actors' start positions */
const Vec D_801154D0_mstory1 = { -120.0f, 0.0f, 480.0f };
const Vec D_801154DC_mstory1 = { 38.0f, 100.0f, 214.0f };
const Vec D_801154E8_mstory1 = { 150.0f, 0.0f, 384.0f };
const Vec D_801154F4_mstory1 = { -800.0f, 0.0f, 480.0f };
const Vec D_80115500_mstory1 = { -700.0f, 0.0f, 300.0f };
const Vec D_8011550C_mstory1 = { -800.0f, 0.0f, 300.0f };
const Vec D_80115518_mstory1 = { 0.0f, 200.0f, 150.0f };
const Vec D_80115524_mstory1 = { 0.0f, 200.0f, 100.0f };
/* actor 0's motions 5, 6, 7 and 9 by character */
const s32 D_80115530_mstory1[8] = { 0x1D003E, 0x1D0048, 0x1D0052, 0x1D005B, 0x1D0065, 0x1D006E, 0x1D003E, 0x1D003E };
const s32 D_80115550_mstory1[8] = { 0x1D0040, 0x1D004B, 0x1D0054, 0x1D005D, 0x1D0067, 0x1D0070, 0x1D0040, 0x1D0040 };
const s32 D_80115570_mstory1[8] = { 0x1D0041, 0x1D004C, 0x1D0055, 0x1D005E, 0x1D0068, 0x1D0071, 0x1D0041, 0x1D0041 };
const s32 D_80115590_mstory1[8] = { 0x1D0043, 0x1D004E, 0x1D0057, 0x1D0060, 0x1D006A, 0x1D0073, 0x1D0043, 0x1D0043 };
const Vec D_801155B0_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_801155BC_mstory1 = { 0.0f, 180.0f, 0.0f };
const Vec D_801155C8_mstory1 = { 0.0f, 90.0f, 0.0f };
const Vec D_801155D4_mstory1 = { 0.0f, -90.0f, 0.0f };
const Vec D_801155E0_mstory1 = { 146.66666f, 0.0f, 480.0f };
const Vec D_801155EC_mstory1 = { 730.0f, 0.0f, 480.0f };
const Vec D_801155F8_mstory1 = { 196.66666f, 0.0f, 480.0f };
const Vec D_80115604_mstory1 = { -100.0f, 0.0f, 350.0f };
const Vec D_80115610_mstory1 = { -100.0f, 0.0f, 150.0f };
const Vec D_8011561C_mstory1 = { 0.0f, 20.0f, 0.0f };
const Vec D_80115628_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_80115634_mstory1 = { 0.0f, -26.565f, 0.0f };

MsPath *func_80110500_mstory1(Vec *points, s16 flags) {
    MsPath *path;
    Vec *prev;
    Vec *cur;
    MsPathSeg *seg;
    f32 total;
    f32 pos;
    f32 len;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 n;
    s16 i;

    path = HuMemAllocTag(sizeof(MsPath), 0x7918);
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
    seg = HuMemAllocTag(n * sizeof(MsPathSeg), 0x7918);
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

// register allocation in the closed-path neighbour loads (masked 3)
#ifdef NON_MATCHING
/* the point at t (0..1) along a path: a spline through the four points around the segment t
   falls in */
void func_80110804_mstory1(MsPath *path, f32 t, Vec *out) {
    f32 p[4];
    f32 times[4];
    MsPathSeg *segs;
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/496990", func_80110804_mstory1);
#endif

void func_801110AC_mstory1(MsPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

void func_801110DC_mstory1(void) {
    func_80106984_mstory1();
    D_80115C90_mstory1 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80111220_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112310_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112BD8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112F4C_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_801134B4_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113908_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113D34_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80114084_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_801141B0_mstory1, 0x384, 0x800, 0);
    omAddPrcObj(func_80114930_mstory1, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115C90_mstory1, 4, 4);
}

/* the idle step: does nothing */
void func_80111218_mstory1(omObjData *obj) {
}

/* NON_MATCHING: masked 0 at the right count once functions.us.h declares func_80017AD8_main as
   returning s16, as 14EA0.c defines it (the header's u8 adds an andi before each store to
   D_80115C94_mstory1; ~/repos/mp3-wt/s3A.header.patch). */
#ifdef NON_MATCHING
/* actor 0: the player's character */
void func_80111220_mstory1(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 6, 0x10, -1, NULL);
    D_80115B70_mstory1[0].obj = obj;
    D_80115B70_mstory1[0].flags = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x9C));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 5, D_80115530_mstory1[chr]);
    func_8000B460_main(obj, 6, D_80115550_mstory1[chr]);
    func_8000B460_main(obj, 7, D_80115570_mstory1[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_80115590_mstory1[chr]);
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x9B));
    D_80115C94_mstory1[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80115C94_mstory1[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80115C94_mstory1[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80115C94_mstory1[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115C94_mstory1[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_80115C30_mstory1[0] = D_801154D0_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C30_mstory1[0].x, D_80115C30_mstory1[0].y, D_80115C30_mstory1[0].z);
    Hu3DModelPosSet(obj->model[2], D_80115C30_mstory1[0].x, -5.0f, D_80115C30_mstory1[0].z);
    Hu3DModelPosSet(obj->model[4], D_80115C30_mstory1[0].x, D_80115C30_mstory1[0].y, D_80115C30_mstory1[0].z);
    omPrcSetDestructor(0, func_8011162C_mstory1);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[0].func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/496990", func_80111220_mstory1);
#endif

void func_8011162C_mstory1(void) {
}


/* actor 0's main scene step */
void func_80111634_mstory1(omObjData *obj) {
    MsPart *part;
    s32 sfx;
    omObjData *other;
    s32 i;
    f32 scale;
    f32 frame;
    s16 model;

    HuPrcSleep(20);
    model = obj->model[1];
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801071F4_mstory1(obj, 0.0f, 110.0f, 0.0f, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], model, "item_hook");
    func_8001C258_main(obj->model[3], 4, 0);
    func_80107220_mstory1(model);
    func_8001C624_main(model, HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    while (!(D_80115B70_mstory1[7].flags & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_80115B70_mstory1[7].obj->model[1], 4, 4);
    func_8001C258_main(D_80115C92_mstory1, 4, 4);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x45);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x46);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x47);
    part = func_8001D33C_main(model, "item_hook");
    i = 0;
    do {
        scale = sindf(i * 18.0f) * 0.8 + 1.0;
        part->unk1C.x = scale;
        part->unk1C.y = scale;
        part->unk1C.z = scale;
        part->unk40.x = scale;
        part->unk40.y = scale;
        part->unk40.z = scale;
        HuPrcVSleep();
        i++;
    } while (i < 10);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x47);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x46);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x45);
    func_80105FB8_mstory1(2);
    while (func_80106894_mstory1() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A33 : 0x5B25);
    func_80106A1C_mstory1();
    func_8001C5B4_main(model, obj->motion[5]);
    func_8001C814_main(model, 4, 4);
    func_8001C92C_main(model, 2.0f);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C5B4_main(model, obj->motion[6]);
    func_8001C814_main(model, 4, 4);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C92C_main(model, 1.0f);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    HuAudSeqFadeOut(20);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_8010704C_mstory1(obj, &D_801155B0_mstory1, 10);
    HuAudSeqPlay(0x72);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115C94_mstory1[2]);
    func_80107220_mstory1(model);
    sfx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    other = D_80115B70_mstory1[6].obj;
    func_8010704C_mstory1(other, &D_80115634_mstory1, 3);
    func_80106B14_mstory1(other, &D_80115604_mstory1, 5);
    func_8010704C_mstory1(other, &D_8011561C_mstory1, 3);
    D_80115B70_mstory1[1].func = func_80112A68_mstory1;
    HuAudFXPlay(0x219);
    HuAudFXStop(sfx);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115C94_mstory1[3]);
    func_8010704C_mstory1(other, &D_80115628_mstory1, 3);
    func_80106B30_mstory1(other, &D_80115610_mstory1, 10, 0);
    func_80107220_mstory1(model);
    HuAudSeqPlay(0x26);
    func_8010704C_mstory1(obj, &D_801155BC_mstory1, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115C94_mstory1[0]);
    HuAudFXPlay(0x159);
    func_8001C624_main(D_80115B70_mstory1[6].obj->model[1], HmfModelData[D_80115B70_mstory1[6].obj->motion[1]].unk02, 0, 10, 2);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A34 : 0x5B26);
    func_80106A1C_mstory1();
    func_8001C624_main(D_80115B70_mstory1[6].obj->model[1], HmfModelData[D_80115B70_mstory1[6].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(model, HmfModelData[obj->motion[8]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    D_80115B70_mstory1[6].func = func_80113F28_mstory1;
    D_80115B70_mstory1[1].func = func_80112984_mstory1;
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    D_80115B70_mstory1[3].func = func_8011314C_mstory1;
    func_8010704C_mstory1(obj, &D_801155C8_mstory1, 20);
    func_801147D0_mstory1(0, 0x1F);
    func_80106B14_mstory1(obj, &D_801155E0_mstory1, 20);
    func_801148B4_mstory1(0);
    func_8010704C_mstory1(obj, &D_801155D4_mstory1, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (!(D_80115B70_mstory1[3].flags & 2)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    func_801147D0_mstory1(0, 0x1F);
    func_80106B30_mstory1(obj, &D_801155F8_mstory1, 10, 0);
    func_801148B4_mstory1(0);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (!(D_80115B70_mstory1[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801155C8_mstory1, 10);
    func_801147D0_mstory1(0, 0x1F);
    func_80106B14_mstory1(obj, &D_801155EC_mstory1, 30);
    func_801148B4_mstory1(0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
}

const Vec D_80115660_mstory1 = { 0.0f, 150.0f, 0.0f };
const Vec D_8011566C_mstory1 = { 0.0f, 162.4f, 0.0f };

void func_801121E4_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C624_main(model, HmfModelData[obj->motion[9]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    HuPrcSleep(80);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
}

void func_801122A8_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115660_mstory1, 10);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
}

void func_801122DC_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_8011566C_mstory1, 10);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
}

/* actor 1 */
void func_80112310_mstory1(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[1].obj = obj;
    D_80115B70_mstory1[1].flags = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80115C30_mstory1[1] = D_801154DC_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C30_mstory1[1].x, D_80115C30_mstory1[1].y, D_80115C30_mstory1[1].z);
    Hu3DModelPosSet(obj->model[2], D_80115C30_mstory1[1].x, -5.0f, D_80115C30_mstory1[1].z);
    data = DataRead(0xA007E);
    D_80115C9C_mstory1[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115C9C_mstory1[0], 1, 0);
    func_80032FF8_main((s16)D_80115C9C_mstory1[0], 0);
    D_80115CA8_mstory1 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115C9C_mstory1[0], 0, "c204n_0_DEF");
    D_80115C9C_mstory1[0] = D_800D1714_main[D_80115C9C_mstory1[0]].unk00;
    data = DataRead(0xA0080);
    D_80115C9C_mstory1[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80115C9C_mstory1[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068B0_mstory1(obj->model[1], D_80115CA8_mstory1, D_80115C9C_mstory1[0]);
    omPrcSetDestructor(0, func_8011263C_mstory1);
    D_80115B70_mstory1[1].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[1].func(obj);
        HuPrcVSleep();
    }
}

const Vec D_80115684_mstory1 = { -5.0f, 300.0f, 0.0f };
const Vec D_80115690_mstory1 = { 10.0f, 378.9f, 0.0f };
const Vec D_8011569C_mstory1[2] = { { 20.0f, 320.0f, 0.0f }, { 0.0f, 450.0f, 0.0f } };
const Vec D_801156B4_mstory1 = { 0.0f, 225.0f, 0.0f };
const Vec D_801156C0_mstory1 = { 0.0f, 134.2f, 0.0f };
const Vec D_801156CC_mstory1 = { 0.0f, 320.0f, 0.0f };
const Vec D_801156D8_mstory1 = { -30.0f, 260.0f, 0.0f };
const Vec D_801156E4_mstory1 = { 238.0f, 100.0f, 214.0f };
const Vec D_801156F0_mstory1 = { 88.0f, 100.0f, 360.0f };
const Vec D_801156FC_mstory1 = { 30.0f, -20.0f, 0.0f };
const Vec D_80115708_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_80115714_mstory1 = { 384.66666f, 100.0f, 214.0f };
const Vec D_80115720_mstory1 = { 918.0f, 100.0f, 214.0f };
const Vec D_8011572C_mstory1 = { 0.0f, 90.0f, 0.0f };
const Vec D_80115738_mstory1 = { 0.0f, 270.0f, 0.0f };
const Vec D_80115744_mstory1 = { 200.0f, 0.0f, 1200.0f };
const Vec D_80115750_mstory1 = { -150.0f, 0.0f, 480.0f };
const Vec D_8011575C_mstory1 = { 650.0f, 0.0f, 480.0f };
const Vec D_80115768_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_80115774_mstory1[2] = { { 0.0f, 90.0f, 0.0f }, { 0.0f, -90.0f, 0.0f } };
const Vec D_8011578C_mstory1 = { 100.0f, 0.0f, 300.0f };
const Vec D_80115798_mstory1 = { 900.0f, 0.0f, 300.0f };
const Vec D_801157A4_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_801157B0_mstory1 = { 0.0f, 90.0f, 0.0f };
const Vec D_801157BC_mstory1 = { 0.0f, -90.0f, 0.0f };
const Vec D_801157C8_mstory1 = { -100.0f, 0.0f, 300.0f };
const Vec D_801157D4_mstory1 = { 700.0f, 0.0f, 300.0f };
const Vec D_801157E0_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_801157EC_mstory1[2] = { { 0.0f, 90.0f, 0.0f }, { 0.0f, -90.0f, 0.0f } };
const Vec D_80115804_mstory1 = { 166.66666f, 0.0f, 150.0f };
const Vec D_80115810_mstory1 = { 700.0f, 0.0f, 150.0f };
const Vec D_8011581C_mstory1 = { 216.66666f, 0.0f, 150.0f };
const Vec D_80115828_mstory1 = { 0.0f, 90.0f, 0.0f };
const Vec D_80115834_mstory1 = { 0.0f, -90.0f, 0.0f };
const Vec D_80115840_mstory1 = { 0.0f, 10.0f, 0.0f };
/* actor 7's model by ...? (only [2] is used) */
const s32 D_8011584C_mstory1[7] = { 0x1D0003, 0x1D0004, 0x1D0005, 0x1D0006, 0x1D0007, 0x1D0008, 0x1D0009 };

void func_8011263C_mstory1(void) {
}

void func_80112644_mstory1(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    D_80115B70_mstory1[0].func = func_801121E4_mstory1;
    D_80115B70_mstory1[6].func = func_80114050_mstory1;
    func_8010704C_mstory1(obj, &D_80115690_mstory1, 30);
    func_80106B14_mstory1(obj, &D_801156F0_mstory1, 20);
    HuPrcSleep(30);
    func_8010704C_mstory1(obj, &D_801156C0_mstory1, 10);
    func_80106B14_mstory1(obj, &D_801156E4_mstory1, 15);
    D_80115B70_mstory1[0].func = func_801122A8_mstory1;
    func_8010704C_mstory1(obj, &D_8011569C_mstory1[0], 10);
    func_801068B0_mstory1(obj->model[1], D_80115CA8_mstory1, D_80115C9C_mstory1[1]);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A31 : 0x5B23);
    func_80106A1C_mstory1();
    func_801068B0_mstory1(obj->model[1], D_80115CA8_mstory1, D_80115C9C_mstory1[0]);
    func_801071F4_mstory1(D_80115B70_mstory1[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_8010704C_mstory1(D_80115B70_mstory1[6].obj, &D_801156FC_mstory1, 10);
    func_8010704C_mstory1(obj, &D_801156B4_mstory1, 20);
    func_8001C624_main(D_80115B70_mstory1[6].obj->model[1], HmfModelData[D_80115B70_mstory1[6].obj->motion[1]].unk02, 0, 10, 2);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A32 : 0x5B24);
    func_80106A1C_mstory1();
    func_8001C624_main(D_80115B70_mstory1[6].obj->model[1], HmfModelData[D_80115B70_mstory1[6].obj->motion[0]].unk02, 0, 10, 2);
    func_8010704C_mstory1(D_80115B70_mstory1[6].obj, &D_80115708_mstory1, 10);
    D_80115B70_mstory1[7].func = func_8011436C_mstory1;
    func_8010704C_mstory1(obj, &D_80115684_mstory1, 20);
    func_8001C624_main(D_80115B70_mstory1[0].obj->model[1], HmfModelData[D_80115B70_mstory1[0].obj->motion[10]].unk02, 0, 10, 2);
    while (!(D_80115B70_mstory1[7].flags & 2)) {
        HuPrcVSleep();
    }
    D_80115B70_mstory1[0].func = func_80111634_mstory1;
    HuPrcSleep(40);
    func_8010704C_mstory1(obj, &D_801156D8_mstory1, 50);
    func_8010704C_mstory1(obj, &D_801156CC_mstory1, 40);
    D_80115B70_mstory1[1].func = func_80111218_mstory1;
}

void func_80112984_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_8011572C_mstory1, 20);
    func_80106B14_mstory1(obj, &D_80115714_mstory1, 20);
    func_8010704C_mstory1(obj, &D_80115738_mstory1, 10);
    while (!(D_80115B70_mstory1[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_8010704C_mstory1(obj, &D_8011572C_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80115720_mstory1, 30);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80115B70_mstory1[1].func = func_80111218_mstory1;
}

void func_80112A68_mstory1(omObjData *obj) {
    Vec pos;
    Vec start;
    f32 ofs;
    s16 model;
    s32 i;

    model = obj->model[1];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    pos.y = HmfModelData[model].pos.y;
    i = 0;
    do {
        pos.x = HmfModelData[model].pos.x;
        pos.z = HmfModelData[model].pos.z;
        ofs = sindf(i * 15.0f) * 80.0f;
        Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
        i++;
        HuPrcVSleep();
    } while (i < 12);
    Hu3DModelPosSet(model, start.x, ofs + start.y, start.z);
    func_801068B0_mstory1(obj->model[1], D_80115CA8_mstory1, D_80115C9C_mstory1[2]);
    D_80115B70_mstory1[1].func = func_80111218_mstory1;
}

/* actor 2 */
void func_80112BD8_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[2].obj = obj;
    D_80115B70_mstory1[2].flags = 0;
    if (func_80106AFC_mstory1(5) == 0) {
        obj->model[1] = func_8000B108_main(0x600A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
        func_8000B460_main(obj, 0, 0x60000);
        func_8000B460_main(obj, 1, 0x1D006C);
        func_8000B460_main(obj, 2, 0x1D006D);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
        func_8000B460_main(obj, 0, 0x30000);
        func_8000B460_main(obj, 1, 0x1D0046);
        func_8000B460_main(obj, 2, 0x1D0047);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80115C30_mstory1[2] = D_801154E8_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C30_mstory1[2].x, D_80115C30_mstory1[2].y, D_80115C30_mstory1[2].z);
    Hu3DModelPosSet(obj->model[2], D_80115C30_mstory1[2].x, -5.0f, D_80115C30_mstory1[2].z);
    omPrcSetDestructor(0, func_80112E14_mstory1);
    D_80115B70_mstory1[2].func = func_80112E1C_mstory1;
    while (1) {
        D_80115B70_mstory1[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80112E14_mstory1(void) {
}

void func_80112E1C_mstory1(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106AFC_mstory1(5) == 0) {
        CharFXPlay(0x26B, 5);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_80115B70_mstory1[1].func = func_80112644_mstory1;
    HuPrcSleep(70);
    if (func_80106AFC_mstory1(5) == 0) {
        CharFXPlay(0x286, 5);
    } else {
        CharFXPlay(0x286, 1);
    }
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    func_801147D0_mstory1(2, 0x28);
    func_80106B14_mstory1(obj, &D_80115744_mstory1, 40);
    func_801148B4_mstory1(2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80115B70_mstory1[2].func = func_80111218_mstory1;
}

/* actor 3 */
void func_80112F4C_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[3].obj = obj;
    D_80115B70_mstory1[3].flags = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115C30_mstory1[3] = D_801154F4_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C30_mstory1[3].x, D_80115C30_mstory1[3].y, D_80115C30_mstory1[3].z);
    Hu3DModelPosSet(obj->model[2], D_80115C30_mstory1[3].x, -5.0f, D_80115C30_mstory1[3].z);
    omPrcSetDestructor(0, func_80113144_mstory1);
    D_80115B70_mstory1[3].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80113144_mstory1(void) {
}

void func_8011314C_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A35 : 0x5B27);
    func_80106A1C_mstory1();
    D_80115B70_mstory1[3].flags |= 2;
    func_80106B14_mstory1(obj, &D_80115750_mstory1, 60);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuAudFXPlay(0x29C);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A36 : 0x5B28);
    func_80106A1C_mstory1();
    func_8010704C_mstory1(obj, &D_80115768_mstory1, 20);
    D_80115B70_mstory1[3].flags |= 1;
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80115774_mstory1[0], 10);
    func_8010704C_mstory1(obj, &D_80115768_mstory1, 10);
    func_8010704C_mstory1(obj, &D_80115774_mstory1[0], 5);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuAudFXPlay(0x29D);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A37 : 0x5B29);
    func_80106A1C_mstory1();
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106B14_mstory1(obj, &D_8011575C_mstory1, 50);
    D_80115B70_mstory1[4].func = func_8011369C_mstory1;
    D_80115B70_mstory1[5].func = func_80113AAC_mstory1;
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80115B70_mstory1[3].func = func_80111218_mstory1;
}

/* actor 4 */
void func_801134B4_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[4].obj = obj;
    D_80115B70_mstory1[4].flags = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0xA00F0);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115C30_mstory1[4] = D_80115500_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C30_mstory1[4].x, D_80115C30_mstory1[4].y, D_80115C30_mstory1[4].z);
    Hu3DModelPosSet(obj->model[2], D_80115C30_mstory1[4].x, -5.0f, D_80115C30_mstory1[4].z);
    omPrcSetDestructor(0, func_80113694_mstory1);
    D_80115B70_mstory1[4].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[4].func(obj);
        HuPrcVSleep();
    }
}

void func_80113694_mstory1(void) {
}

void func_8011369C_mstory1(omObjData *obj) {
    s16 model;

    model = obj->model[1];
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    while (!(D_80115B70_mstory1[3].flags & 1)) {
        HuPrcVSleep();
    }
    func_80106B14_mstory1(obj, &D_8011578C_mstory1, 30);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157BC_mstory1, 5);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(20);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157A4_mstory1, 5);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(30);
    model = obj->model[1];
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157B0_mstory1, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106B14_mstory1(obj, &D_80115798_mstory1, 20);
    func_80105FA8_mstory1();
    D_80115B70_mstory1[4].func = func_80111218_mstory1;
}

/* actor 5: a copy of actor 4's model */
void func_80113908_mstory1(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[5].obj = obj;
    D_80115B70_mstory1[5].flags = 0;
    src = D_80115B70_mstory1[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115C30_mstory1[5] = D_8011550C_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C30_mstory1[5].x, D_80115C30_mstory1[5].y, D_80115C30_mstory1[5].z);
    Hu3DModelPosSet(obj->model[2], D_80115C30_mstory1[5].x, -5.0f, D_80115C30_mstory1[5].z);
    omPrcSetDestructor(0, func_80113D2C_mstory1);
    D_80115B70_mstory1[5].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[5].func(obj);
        HuPrcVSleep();
    }
}

/* actor 5 uses actor 4's motions */
void func_80113AAC_mstory1(omObjData *obj) {
    omObjData *src;
    s16 model;

    src = D_80115B70_mstory1[4].obj;
    model = obj->model[1];
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    while (!(D_80115B70_mstory1[3].flags & 1)) {
        HuPrcVSleep();
    }
    func_80106B14_mstory1(obj, &D_801157C8_mstory1, 30);
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157EC_mstory1[0], 5);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(20);
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157E0_mstory1, 5);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(30);
    model = obj->model[1];
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157EC_mstory1[0], 10);
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_80106B14_mstory1(obj, &D_801157D4_mstory1, 20);
    D_80115B70_mstory1[5].func = func_80111218_mstory1;
}

void func_80113D2C_mstory1(void) {
}

/* actor 6: Toad? (the hovering one) */
void func_80113D34_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[6].obj = obj;
    D_80115B70_mstory1[6].flags = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_80115C30_mstory1[6] = D_80115518_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C30_mstory1[6].x, D_80115C30_mstory1[6].y, D_80115C30_mstory1[6].z);
    Hu3DModelPosSet(obj->model[2], D_80115C30_mstory1[6].x, -5.0f, D_80115C30_mstory1[6].z);
    omPrcSetDestructor(0, func_80113F20_mstory1);
    D_80115B70_mstory1[6].func = func_80111218_mstory1;
    D_80114BC0_mstory1 = 1;
    while (1) {
        D_80115B70_mstory1[6].func(obj);
        HuPrcVSleep();
    }
}

void func_80113F20_mstory1(void) {
}

void func_80113F28_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115828_mstory1, 20);
    func_80106B14_mstory1(obj, &D_80115804_mstory1, 20);
    func_8010704C_mstory1(obj, &D_80115834_mstory1, 10);
    while (!(D_80115B70_mstory1[3].flags & 2)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_80106B30_mstory1(obj, &D_8011581C_mstory1, 10, 0);
    while (!(D_80115B70_mstory1[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_8010704C_mstory1(obj, &D_80115828_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80115810_mstory1, 30);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80115B70_mstory1[6].func = func_80111218_mstory1;
}

void func_80114050_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115840_mstory1, 20);
    D_80115B70_mstory1[6].func = func_80111218_mstory1;
}

/* bobs actor 6 up and down while D_80114BC0_mstory1 is set at start */
void func_80114084_mstory1(void) {
    Vec pos;
    f32 angle;
    f32 ofs;
    s16 model;

    angle = 0.0f;
    if (D_80114BC0_mstory1 != 0) {
        model = D_80115B70_mstory1[6].obj->model[1];
        pos.y = HmfModelData[model].pos.y;
        while (1) {
            pos.x = HmfModelData[model].pos.x;
            pos.z = HmfModelData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            HuPrcVSleep();
        }
    }
}

/* actor 7 */
void func_801141B0_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_80115B70_mstory1[7].obj = obj;
    D_80115B70_mstory1[7].flags = 0;
    obj->model[1] = func_8000B108_main(D_8011584C_mstory1[2], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115C30_mstory1[7] = D_80115524_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C30_mstory1[7].x, D_80115C30_mstory1[7].y, D_80115C30_mstory1[7].z);
    D_80115C92_mstory1 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80115C92_mstory1, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_80115C92_mstory1, 60.0f);
    func_800138EC_main(D_80115C92_mstory1, 1, 0);
    func_8001C258_main(D_80115C92_mstory1, 4, 4);
    omPrcSetDestructor(0, func_80114364_mstory1);
    D_80115B70_mstory1[7].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[7].func(obj);
        HuPrcVSleep();
    }
}

void func_80114364_mstory1(void) {
}

/* actor 7 flies along two paths */
void func_8011436C_mstory1(omObjData *obj) {
    Vec pos;
    MsPath *path[2];
    omObjData *other;
    f32 t;
    f32 rot;
    s32 i;

    path[0] = func_80110500_mstory1(D_80114BC4_mstory1, 0);
    path[1] = func_80110500_mstory1(D_80114BF4_mstory1, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_80115C92_mstory1, 4, 0);
    func_800138EC_main(D_80115C92_mstory1, 1, 1);
    HuAudFXPlay(0x215);
    i = 0;
    do {
        t = i * 0.02f;
        func_80110804_mstory1(path[0], t * t, &pos);
        i++;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115C92_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 50);
    HuPrcSleep(40);
    other = D_80115B70_mstory1[6].obj;
    func_8001C624_main(other->model[1], HmfModelData[other->motion[2]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_80115B70_mstory1[7].flags |= 2;
    HuAudFXPlay(0x218);
    func_8001C624_main(other->model[1], HmfModelData[other->motion[0]].unk02, 0, 10, 2);
    rot = 0.0f;
    i = 0;
    do {
        t = i * (1.0f / 120.0f);
        func_80110804_mstory1(path[1], t * t, &pos);
        rot -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        i++;
        Hu3DModelRotSet(obj->model[1], 0.0f, rot, 0.0f);
        func_8000CFA4_main(D_80115C92_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 120);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_80115C92_mstory1, 4, 4);
    HuAudFXPlay(0x21A);
    func_801110AC_mstory1(path[0]);
    func_801110AC_mstory1(path[1]);
    D_80115B70_mstory1[7].flags = 1; /* clears the 2 set above (actor 0 waits on 1 only) */
    D_80115B70_mstory1[7].func = func_80111218_mstory1;
}

/* turns a's model to face b's */
void func_80114688_mstory1(omObjData *a, omObjData *b) {
    s16 models[2];
    Vec pos[2];
    Vec rot;
    Vec d;
    s32 i;

    models[0] = a->model[1];
    models[1] = b->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = HmfModelData[models[i]].pos.x;
        pos[i].y = HmfModelData[models[i]].pos.y;
        pos[i].z = HmfModelData[models[i]].pos.z;
    }
    rot.x = HmfModelData[models[0]].rot.x;
    rot.y = HmfModelData[models[0]].rot.y;
    rot.z = HmfModelData[models[0]].rot.z;
    d.x = pos[1].x - pos[0].x;
    d.y = pos[1].y - pos[0].y;
    d.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(d.z, d.x) - 90.0f);
    Hu3DModelRotSet(models[0], rot.x, rot.y, rot.z);
}

/* starts actor idx's looping sound seId (actors 0 and 2 only) */
void func_801147D0_mstory1(s32 idx, s32 seId) {
    if (D_80115B70_mstory1[idx].sfxOn == 0) {
        D_80115B70_mstory1[idx].sfxOn = 1;
        D_80115B70_mstory1[idx].sfxId = seId;
        switch (idx) {
        case 0:
            D_80115B70_mstory1[idx].sfx = CharFXPlay(seId, GwStory.unk1);
            break;
        case 2:
            if (func_80106AFC_mstory1(5) == 0) {
                D_80115B70_mstory1[idx].sfx = CharFXPlay(seId, 5);
            } else {
                D_80115B70_mstory1[idx].sfx = CharFXPlay(seId, 1);
            }
            break;
        case 1:
        case 3:
        case 4:
        case 5:
            break;
        }
    }
}

void func_801148B4_mstory1(s32 idx) {
    if (D_80115B70_mstory1[idx].sfxOn == 1) {
        D_80115B70_mstory1[idx].sfxOn = 0;
        switch (idx) {
        case 0:
        case 2:
            HuAudFXStop((s16)D_80115B70_mstory1[idx].sfx);
            break;
        case 1:
        case 3:
        case 4:
        case 5:
            break;
        }
    }
}

/* replays the looping sounds whenever their actor's motion restarts */
void func_80114930_mstory1(void) {
    s32 i;
    s32 seId;

    while (1) {
        for (i = 0; i < 8; i++) {
            if (D_80115B70_mstory1[i].sfxOn == 1 && HmfModelData[D_80115B70_mstory1[i].obj->model[1]].unk40 == 0.0f) {
                seId = D_80115B70_mstory1[i].sfxId;
                switch (i) {
                case 0:
                    D_80115B70_mstory1[i].sfx = CharFXPlay(seId, GwStory.unk1);
                    break;
                case 2:
                    if (func_80106AFC_mstory1(5) == 0) {
                        D_80115B70_mstory1[i].sfx = CharFXPlay(seId, 5);
                    } else {
                        D_80115B70_mstory1[i].sfx = CharFXPlay(seId, 1);
                    }
                    break;
                case 1:
                case 3:
                case 4:
                case 5:
                    break;
                }
            }
        }
        HuPrcVSleep();
    }
}
