/* Not common.h: functions.us.h declares func_80017AD8_main returning u8, but it returns s16
   (src/14EA0.c); this unit declares the main-code functions it calls itself. */
#include "ultra64.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/process.h"
#include "game/util.h"
#include "include_asm.h"
#include "math.h"
#include "mallocblock.h"
void HuMemMemoryFreePerm(void *ptr);

/* Story mode chapter 1: the cutscene actors. Each actor is an object driven by its own process,
   which calls the actor's current script function every frame; scripts hand over by storing the
   next function (func_8010CAD8_mstory1 is the idle script). */

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i runs
   from points[i] to points[i + 1] and covers [segs[i].start, segs[i].end] of the path's
   length (0..1). flags & 1: closed (the last segment returns to points[0]). */
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

typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 flags; /* cues the scripts give each other */
    /* 0x0C */ s32 sfxOn; /* func_80110248_mstory1 */
    /* 0x10 */ s32 sfxId;
    /* 0x14 */ s32 sfxNo;
} StoryActor; /* size = 0x18 */

/* a model part looked up by name (func_8001D33C_main) */
typedef struct StoryHmfPart {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ Vec scale;
    /* 0x28 */ char unk28[0x18];
    /* 0x40 */ Vec scale2;
} StoryHmfPart;

typedef struct StoryTexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} StoryTexAnimSlot; /* size = 0xC */

typedef struct StoryMotData {
    /* 0x00 */ char unk00[2];
    /* 0x02 */ s16 unk02; /* frame count */
    /* 0x04 */ char unk04[0x14];
} StoryMotData; /* size = 0x18 (D_800CCF58_main_Struct) */

extern s32 D_800A178C_main[][6];
extern StoryMotData *D_800CCF58_main;
void func_8000CD00_main(s16, f32, f32, f32);
s16 func_8000CED8_main(s32, s32);
void func_8000CFA4_main(s16, f32, f32, f32);
void func_8000D018_main(s16, f32);
void func_800461B4_main(s16 arg0);
s32 HmfAnimCreate(HmfData *, void *, s32, char *);
s16 func_80017790_main(s16 model, s32 arg1, s16 arg2, s32 arg3);
void func_80017954_main(s16, s16, s16, s16);
s16 func_80017AD8_main(s32);
s32 func_80017BB8_main(s16, s16);
s16 func_80032694_main(HmfData *, u16, s32, char *);
void func_80032FF8_main(s32, u8);
extern StoryTexAnimSlot *D_800D1714_main;

f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void *func_8001D33C_main(s16, const char *);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
void func_800138EC_main(s16 model, u16 mask, u16 flags);

/* 48C120 */
void func_80105FA8_mstory1(void);
void func_80105FB8_mstory1(s32 arg0);
s32 func_80106894_mstory1(void);
void func_801068B0_mstory1(s16 model, s16 anim, s16 frame);
void func_80106984_mstory1(void);
void func_801069EC_mstory1(void);
void func_80106A1C_mstory1(void);
void func_80106A40_mstory1(s32 mes);
s32 func_80106AFC_mstory1(s32 chr);
void func_80106B14_mstory1(omObjData *obj, Vec *pos, s32 time);
void func_80106B30_mstory1(omObjData *obj, Vec *pos, s32 time, s32 arg3);
void func_8010704C_mstory1(omObjData *obj, Vec *rot, s32 time);
void func_801071F4_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 time);
void func_80107220_mstory1(s16 model);

s32 D_80114B40_mstory1 = 0;
/* paths: Vec lists ended by { 9999, 9999, 9999 } */
Vec D_80114B44_mstory1[4] = {
    { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f }
};
Vec D_80114B74_mstory1[6] = {
    { -100.0f, 300.0f, 300.0f }, { -200.0f, 200.0f, 100.0f }, { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f }, { -50.0f, 120.0f, 450.0f }, { 9999.0f, 9999.0f, 9999.0f }
};

extern StoryActor D_80115A30_mstory1[8];
extern Vec D_80115AF0_mstory1[8];
extern s16 D_80115B50_mstory1;
extern s16 D_80115B52_mstory1;
extern s16 D_80115B54_mstory1[4];
extern s32 D_80115B5C_mstory1[3];
extern s16 D_80115B68_mstory1;

ObPath *func_8010BDC0_mstory1(Vec *points, s16 flags);
void func_8010C0C4_mstory1(ObPath *path, f32 t, Vec *out);
void func_8010C96C_mstory1(ObPath *path);
void func_8010CAD8_mstory1(omObjData *obj);
void func_8010CAE0_mstory1(void);
void func_8010CEF0_mstory1(void);
void func_8010CEF8_mstory1(omObjData *obj);
void func_8010D90C_mstory1(omObjData *obj);
void func_8010D9D0_mstory1(omObjData *obj);
void func_8010DA04_mstory1(omObjData *obj);
void func_8010DA38_mstory1(void);
void func_8010DD68_mstory1(void);
void func_8010DD70_mstory1(omObjData *obj);
void func_8010E0B0_mstory1(omObjData *obj);
void func_8010E12C_mstory1(omObjData *obj);
void func_8010E29C_mstory1(void);
void func_8010E4C4_mstory1(void);
void func_8010E4CC_mstory1(omObjData *obj);
void func_8010E5FC_mstory1(void);
void func_8010E80C_mstory1(void);
void func_8010E814_mstory1(omObjData *obj);
void func_8010EC30_mstory1(void);
void func_8010EE14_mstory1(void);
void func_8010EE1C_mstory1(omObjData *obj);
void func_8010F244_mstory1(void);
void func_8010F3EC_mstory1(omObjData *obj);
void func_8010F848_mstory1(void);
void func_8010F850_mstory1(void);
void func_8010FA40_mstory1(void);
void func_8010FA48_mstory1(omObjData *obj);
void func_8010FAC4_mstory1(omObjData *obj);
void func_8010FAF8_mstory1(void);
void func_8010FC24_mstory1(void);
void func_8010FDDC_mstory1(void);
void func_8010FDE4_mstory1(omObjData *obj);
void func_80110100_mstory1(omObjData *obj, omObjData *target);
void func_80110248_mstory1(s32 actor, s32 se);
void func_8011032C_mstory1(s32 actor);
void func_801103A8_mstory1(void);

/* each actor's start position */
const Vec D_801150C0_mstory1[8] = {
    { -120.0f, 0.0f, 480.0f },
    { 38.0f, 100.0f, 214.0f },
    { 150.0f, 0.0f, 384.0f },
    { -800.0f, 0.0f, 480.0f },
    { -700.0f, 0.0f, 300.0f },
    { -800.0f, 0.0f, 300.0f },
    { 0.0f, 200.0f, 150.0f },
    { 0.0f, 200.0f, 100.0f },
};
/* the player character's motions, per character */
const s32 D_80115120_mstory1[8] = { 0x001D003E, 0x001D0048, 0x001D0052, 0x001D005B,
                                    0x001D0065, 0x001D006E, 0x001D003E, 0x001D003E };
const s32 D_80115140_mstory1[8] = { 0x001D0040, 0x001D004B, 0x001D0054, 0x001D005D,
                                    0x001D0067, 0x001D0070, 0x001D0040, 0x001D0040 };
const s32 D_80115160_mstory1[8] = { 0x001D0041, 0x001D004C, 0x001D0055, 0x001D005E,
                                    0x001D0068, 0x001D0071, 0x001D0041, 0x001D0041 };
const s32 D_80115180_mstory1[8] = { 0x001D0043, 0x001D004E, 0x001D0057, 0x001D0060,
                                    0x001D006A, 0x001D0073, 0x001D0043, 0x001D0043 };

ObPath *func_8010BDC0_mstory1(Vec *points, s16 flags) {
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

// register allocation in the closed-path neighbour loads (as opboard's twin)
#ifdef NON_MATCHING
/* the point at t (0..1) along a path: a spline through the four points around the segment t
   falls in */
void func_8010C0C4_mstory1(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/492250", func_8010C0C4_mstory1);
#endif

void func_8010C96C_mstory1(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* chapter 1 scene setup: the actors' processes */
void func_8010C99C_mstory1(void) {
    func_80106984_mstory1();
    D_80115B50_mstory1 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010CAE0_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010DA38_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010E29C_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010E5FC_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010EC30_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010F244_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010F850_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010FAF8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010FC24_mstory1, 0x384, 0x800, 0);
    omAddPrcObj(func_801103A8_mstory1, 0x384, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115B50_mstory1, 4, 4);
}

void func_8010CAD8_mstory1(omObjData *obj) {
}

/* actor 0: the player character */
void func_8010CAE0_mstory1(void) {
    omObjData *obj;
    s16 chr;
    s32 c;

    obj = omAddObj(0x14, 6, 0x10, -1, NULL);
    D_80115A30_mstory1[0].obj = obj;
    D_80115A30_mstory1[0].flags = 0;
    D_80115A30_mstory1[0].sfxOn = 0;
    c = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[c][0] | D_800A178C_main[c][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[4], 4, 4);
    chr = c;
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x9C));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 5, D_80115120_mstory1[chr]);
    func_8000B460_main(obj, 6, D_80115140_mstory1[chr]);
    func_8000B460_main(obj, 7, D_80115160_mstory1[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_80115180_mstory1[chr]);
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x9B));
    D_80115B54_mstory1[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80115B54_mstory1[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80115B54_mstory1[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80115B54_mstory1[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115B54_mstory1[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_80115AF0_mstory1[0] = D_801150C0_mstory1[0];
    Hu3DModelPosSet(obj->model[1], D_80115AF0_mstory1[0].x, D_80115AF0_mstory1[0].y, D_80115AF0_mstory1[0].z);
    Hu3DModelPosSet(obj->model[2], D_80115AF0_mstory1[0].x, -5.0f, D_80115AF0_mstory1[0].z);
    Hu3DModelPosSet(obj->model[4], D_80115AF0_mstory1[0].x, D_80115AF0_mstory1[0].y, D_80115AF0_mstory1[0].z);
    omPrcSetDestructor(0, func_8010CEF0_mstory1);
    D_80115A30_mstory1[0].func = func_8010CAD8_mstory1;
    while (TRUE) {
        D_80115A30_mstory1[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010CEF0_mstory1(void) {
}

const Vec D_801151A0_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_801151AC_mstory1 = { 0.0f, 180.0f, 0.0f };
const Vec D_801151B8_mstory1[3] = { { 0.0f, 90.0f, 0.0f }, { 0.0f, -90.0f, 0.0f }, { 146.66666f, 0.0f, 480.0f } };
const Vec D_801151DC_mstory1[2] = { { 730.0f, 0.0f, 480.0f }, { 196.66666f, 0.0f, 480.0f } };
const Vec D_801151F4_mstory1 = { -100.0f, 0.0f, 350.0f };
const Vec D_80115200_mstory1 = { -100.0f, 0.0f, 150.0f };
const Vec D_8011520C_mstory1 = { 0.0f, 20.0f, 0.0f };
const Vec D_80115218_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_80115224_mstory1 = { 0.0f, -26.565f, 0.0f };

/* the player: a hook pulls the item out, then the item handover with actor 6 */
void func_8010CEF8_mstory1(omObjData *obj) {
    StoryHmfPart *part;
    omObjData *other;
    s16 model;
    s32 se;
    s32 i;
    f32 scale;
    f32 s;

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
    while (!(D_80115A30_mstory1[7].flags & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_80115A30_mstory1[7].obj->model[1], 4, 4);
    func_8001C258_main(D_80115B52_mstory1, 4, 4);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x45);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x46);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x47);
    part = func_8001D33C_main(model, "item_hook");
    for (i = 0; i < 10; i++) {
        scale = sindf(i * 18.0f) * 0.8 + 1.0;
        part->scale.x = scale;
        part->scale.y = scale;
        part->scale.z = scale;
        part->scale2.x = scale;
        part->scale2.y = scale;
        part->scale2.z = scale;
        HuPrcVSleep();
    }
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x47);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x46);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x45);
    func_80105FB8_mstory1(1);
    while (func_80106894_mstory1() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A25 : 0x5B16);
    func_80106A1C_mstory1();
    func_8001C5B4_main(model, obj->motion[5]);
    func_8001C814_main(model, 4, 4);
    func_8001C92C_main(model, 2.0f);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        s = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (s > 0.0f);
    func_8001C5B4_main(model, obj->motion[6]);
    func_8001C814_main(model, 4, 4);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        s = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (s > 0.0f);
    func_8001C92C_main(model, 1.0f);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    HuAudSeqFadeOut(20);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_8010704C_mstory1(obj, (Vec *)&D_801151A0_mstory1, 10);
    HuAudSeqPlay(0x72);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115B54_mstory1[2]);
    func_80107220_mstory1(model);
    se = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    other = D_80115A30_mstory1[6].obj;
    func_8010704C_mstory1(other, (Vec *)&D_80115224_mstory1, 3);
    func_80106B14_mstory1(other, (Vec *)&D_801151F4_mstory1, 5);
    func_8010704C_mstory1(other, (Vec *)&D_8011520C_mstory1, 3);
    D_80115A30_mstory1[1].func = func_8010E12C_mstory1;
    HuAudFXPlay(0x219);
    HuAudFXStop(se);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115B54_mstory1[3]);
    func_8010704C_mstory1(other, (Vec *)&D_80115218_mstory1, 3);
    func_80106B30_mstory1(other, (Vec *)&D_80115200_mstory1, 10, 0);
    func_80107220_mstory1(model);
    HuAudSeqPlay(0x26);
    func_8010704C_mstory1(obj, (Vec *)&D_801151AC_mstory1, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115B54_mstory1[0]);
    HuAudFXPlay(0x159);
    func_8001C624_main(D_80115A30_mstory1[6].obj->model[1], HmfModelData[D_80115A30_mstory1[6].obj->motion[1]].unk02, 0, 10, 2);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A26 : 0x5B17);
    func_80106A1C_mstory1();
    func_8001C624_main(D_80115A30_mstory1[6].obj->model[1], HmfModelData[D_80115A30_mstory1[6].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(model, HmfModelData[obj->motion[8]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    D_80115A30_mstory1[6].func = func_8010FA48_mstory1;
    D_80115A30_mstory1[1].func = func_8010E0B0_mstory1;
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    D_80115A30_mstory1[3].func = func_8010E814_mstory1;
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    func_80110248_mstory1(0, 0x1F);
    func_8010704C_mstory1(obj, (Vec *)D_801151B8_mstory1, 10);
    func_80106B14_mstory1(obj, (Vec *)D_801151DC_mstory1, 50);
    func_8011032C_mstory1(0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80115A30_mstory1[0].func = func_8010CAD8_mstory1;
}

void func_8010D90C_mstory1(omObjData *obj) {
    s16 model;

    model = obj->model[1];
    func_8001C624_main(model, HmfModelData[obj->motion[9]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    HuPrcSleep(80);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_80115A30_mstory1[0].func = func_8010CAD8_mstory1;
}

const Vec D_80115250_mstory1 = { 0.0f, 150.0f, 0.0f };

void func_8010D9D0_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)&D_80115250_mstory1, 10);
    D_80115A30_mstory1[0].func = func_8010CAD8_mstory1;
}

const Vec D_8011525C_mstory1 = { 0.0f, 162.4f, 0.0f };

void func_8010DA04_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)&D_8011525C_mstory1, 10);
    D_80115A30_mstory1[0].func = func_8010CAD8_mstory1;
}

/* actor 1 */
void func_8010DA38_mstory1(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115A30_mstory1[1].obj = obj;
    D_80115A30_mstory1[1].flags = 0;
    D_80115A30_mstory1[1].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80115AF0_mstory1[1] = D_801150C0_mstory1[1];
    Hu3DModelPosSet(obj->model[1], D_80115AF0_mstory1[1].x, D_80115AF0_mstory1[1].y, D_80115AF0_mstory1[1].z);
    Hu3DModelPosSet(obj->model[2], D_80115AF0_mstory1[1].x, -5.0f, D_80115AF0_mstory1[1].z);
    data = DataRead(0xA007E);
    D_80115B5C_mstory1[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115B5C_mstory1[0], 1, 0);
    func_80032FF8_main((s16)D_80115B5C_mstory1[0], 0);
    D_80115B68_mstory1 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115B5C_mstory1[0], 0, "c204n_0_DEF");
    D_80115B5C_mstory1[0] = D_800D1714_main[D_80115B5C_mstory1[0]].unk_00;
    data = DataRead(0xA0080);
    D_80115B5C_mstory1[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80115B5C_mstory1[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068B0_mstory1(obj->model[1], D_80115B68_mstory1, D_80115B5C_mstory1[0]);
    omPrcSetDestructor(0, func_8010DD68_mstory1);
    D_80115A30_mstory1[1].func = func_8010CAD8_mstory1;
    while (TRUE) {
        D_80115A30_mstory1[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010DD68_mstory1(void) {
}

const Vec D_80115274_mstory1 = { -5.0f, 300.0f, 0.0f };
const Vec D_80115280_mstory1 = { 10.0f, 378.9f, 0.0f };
const Vec D_8011528C_mstory1[2] = { { 20.0f, 320.0f, 0.0f }, { 0.0f, 450.0f, 0.0f } };
const Vec D_801152A4_mstory1 = { 0.0f, 225.0f, 0.0f };
const Vec D_801152B0_mstory1 = { 0.0f, 134.2f, 0.0f };
const Vec D_801152BC_mstory1 = { 0.0f, 320.0f, 0.0f };
const Vec D_801152C8_mstory1 = { -30.0f, 260.0f, 0.0f };
const Vec D_801152D4_mstory1 = { 238.0f, 100.0f, 214.0f };
const Vec D_801152E0_mstory1 = { 88.0f, 100.0f, 360.0f };
const Vec D_801152EC_mstory1 = { 30.0f, -20.0f, 0.0f };
const Vec D_801152F8_mstory1[2] = { { 0.0f, 0.0f, 0.0f }, { 384.66666f, 100.0f, 214.0f } };

void func_8010DD70_mstory1(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    D_80115A30_mstory1[0].func = func_8010D90C_mstory1;
    D_80115A30_mstory1[6].func = func_8010FAC4_mstory1;
    func_8010704C_mstory1(obj, (Vec *)&D_80115280_mstory1, 30);
    func_80106B14_mstory1(obj, (Vec *)&D_801152E0_mstory1, 20);
    HuPrcSleep(30);
    func_8010704C_mstory1(obj, (Vec *)&D_801152B0_mstory1, 10);
    func_80106B14_mstory1(obj, (Vec *)&D_801152D4_mstory1, 15);
    D_80115A30_mstory1[0].func = func_8010D9D0_mstory1;
    func_8010704C_mstory1(obj, (Vec *)D_8011528C_mstory1, 10);
    func_801068B0_mstory1(obj->model[1], D_80115B68_mstory1, D_80115B5C_mstory1[1]);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A23 : 0x5B14);
    func_80106A1C_mstory1();
    func_801068B0_mstory1(obj->model[1], D_80115B68_mstory1, D_80115B5C_mstory1[0]);
    func_801071F4_mstory1(D_80115A30_mstory1[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_8010704C_mstory1(D_80115A30_mstory1[6].obj, (Vec *)&D_801152EC_mstory1, 10);
    func_8010704C_mstory1(obj, (Vec *)&D_801152A4_mstory1, 20);
    func_8001C624_main(D_80115A30_mstory1[6].obj->model[1], HmfModelData[D_80115A30_mstory1[6].obj->motion[1]].unk02, 0, 10, 2);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A24 : 0x5B15);
    func_80106A1C_mstory1();
    func_8001C624_main(D_80115A30_mstory1[6].obj->model[1], HmfModelData[D_80115A30_mstory1[6].obj->motion[0]].unk02, 0, 10, 2);
    func_8010704C_mstory1(D_80115A30_mstory1[6].obj, (Vec *)D_801152F8_mstory1, 10);
    D_80115A30_mstory1[7].func = func_8010FDE4_mstory1;
    func_8010704C_mstory1(obj, (Vec *)&D_80115274_mstory1, 20);
    func_8001C624_main(D_80115A30_mstory1[0].obj->model[1], HmfModelData[D_80115A30_mstory1[0].obj->motion[10]].unk02, 0, 10, 2);
    while (!(D_80115A30_mstory1[7].flags & 2)) {
        HuPrcVSleep();
    }
    D_80115A30_mstory1[0].func = func_8010CEF8_mstory1;
    HuPrcSleep(40);
    func_8010704C_mstory1(obj, (Vec *)&D_801152C8_mstory1, 50);
    func_8010704C_mstory1(obj, (Vec *)&D_801152BC_mstory1, 40);
    D_80115A30_mstory1[1].func = func_8010CAD8_mstory1;
}

const Vec D_80115310_mstory1 = { 918.0f, 100.0f, 214.0f };
const Vec D_8011531C_mstory1[2] = { { 0.0f, 90.0f, 0.0f }, { 0.0f, 270.0f, 0.0f } };

void func_8010E0B0_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)D_8011531C_mstory1, 10);
    func_80106B14_mstory1(obj, (Vec *)&D_80115310_mstory1, 50);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80115A30_mstory1[1].func = func_8010CAD8_mstory1;
}

/* actor 1 hops */
void func_8010E12C_mstory1(omObjData *obj) {
    Vec pos;
    Vec start;
    f32 y;
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
        y = sindf(i * 15.0f) * 80.0f;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        i++;
        HuPrcVSleep();
    } while (i < 12);
    Hu3DModelPosSet(model, start.x, y + start.y, start.z);
    func_801068B0_mstory1(obj->model[1], D_80115B68_mstory1, D_80115B5C_mstory1[2]);
    D_80115A30_mstory1[1].func = func_8010CAD8_mstory1;
}

/* actor 2 */
void func_8010E29C_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115A30_mstory1[2].obj = obj;
    D_80115A30_mstory1[2].flags = 0;
    D_80115A30_mstory1[2].sfxOn = 0;
    if (!func_80106AFC_mstory1(3)) {
        obj->model[1] = func_8000B108_main(0x400A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
        func_8000B460_main(obj, 0, 0x40000);
        func_8000B460_main(obj, 1, 0x1D0059);
        func_8000B460_main(obj, 2, 0x1D005A);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
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
    D_80115AF0_mstory1[2] = D_801150C0_mstory1[2];
    Hu3DModelPosSet(obj->model[1], D_80115AF0_mstory1[2].x, D_80115AF0_mstory1[2].y, D_80115AF0_mstory1[2].z);
    Hu3DModelPosSet(obj->model[2], D_80115AF0_mstory1[2].x, -5.0f, D_80115AF0_mstory1[2].z);
    omPrcSetDestructor(0, func_8010E4C4_mstory1);
    D_80115A30_mstory1[2].func = func_8010E4CC_mstory1;
    while (TRUE) {
        D_80115A30_mstory1[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010E4C4_mstory1(void) {
}

const Vec D_80115334_mstory1 = { 200.0f, 0.0f, 1200.0f };

void func_8010E4CC_mstory1(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106AFC_mstory1(3) == 0) {
        CharFXPlay(0x26B, 3);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_80115A30_mstory1[1].func = func_8010DD70_mstory1;
    HuPrcSleep(70);
    if (func_80106AFC_mstory1(3) == 0) {
        CharFXPlay(0x286, 3);
    } else {
        CharFXPlay(0x286, 1);
    }
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    func_80110248_mstory1(2, 0x28);
    func_80106B14_mstory1(obj, (Vec *)&D_80115334_mstory1, 40);
    func_8011032C_mstory1(2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80115A30_mstory1[2].func = func_8010CAD8_mstory1;
}

/* actor 3 */
void func_8010E5FC_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115A30_mstory1[3].obj = obj;
    D_80115A30_mstory1[3].flags = 0;
    D_80115A30_mstory1[3].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0x1D0035);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115AF0_mstory1[3] = D_801150C0_mstory1[3];
    Hu3DModelPosSet(obj->model[1], D_80115AF0_mstory1[3].x, D_80115AF0_mstory1[3].y, D_80115AF0_mstory1[3].z);
    Hu3DModelPosSet(obj->model[2], D_80115AF0_mstory1[3].x, -5.0f, D_80115AF0_mstory1[3].z);
    omPrcSetDestructor(0, func_8010E80C_mstory1);
    D_80115A30_mstory1[3].func = func_8010CAD8_mstory1;
    while (TRUE) {
        D_80115A30_mstory1[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010E80C_mstory1(void) {
}

const Vec D_80115340_mstory1[2] = { { 0.0f, 0.0f, 480.0f }, { 800.0f, 0.0f, 480.0f } };
const Vec D_80115358_mstory1[3] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 90.0f, 0.0f }, { 0.0f, -90.0f, 0.0f } };
const Vec D_8011537C_mstory1 = { 0.0f, -40.0f, 0.0f };
const Vec D_80115388_mstory1 = { 0.0f, 40.0f, 0.0f };

void func_8010E814_mstory1(omObjData *obj) {
    s16 model;

    HuPrcSleep(60);
    model = obj->model[1];
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A27 : 0x5B18);
    func_80106A1C_mstory1();
    D_80115A30_mstory1[4].func = func_8010EE1C_mstory1;
    D_80115A30_mstory1[5].func = func_8010F3EC_mstory1;
    func_80106B14_mstory1(obj, (Vec *)D_80115340_mstory1, 60);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, (Vec *)D_80115358_mstory1, 20);
    HuAudFXPlay(0x29C);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A28 : 0x5B19);
    func_80106A1C_mstory1();
    D_80115A30_mstory1[3].flags |= 1;
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    HuPrcSleep(30);
    while (!(D_80115A30_mstory1[4].flags & 1)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, (Vec *)&D_8011537C_mstory1, 10);
    D_80115A30_mstory1[3].flags |= 2;
    while (!(D_80115A30_mstory1[5].flags & 1)) {
        HuPrcVSleep();
    }
    func_8010704C_mstory1(obj, (Vec *)&D_80115388_mstory1, 10);
    HuPrcSleep(20);
    func_8010704C_mstory1(obj, (Vec *)D_80115358_mstory1, 5);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuAudFXPlay(0x29E);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A2B : 0x5B1C);
    func_80106A1C_mstory1();
    D_80115A30_mstory1[3].flags |= 4;
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    HuPrcSleep(40);
    D_80115A30_mstory1[3].flags |= 8;
    HuPrcSleep(20);
    HuAudFXPlay(0x2A0);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A2C : 0x5B1D);
    func_80106A1C_mstory1();
    HuPrcSleep(40);
    func_80105FA8_mstory1();
    D_80115A30_mstory1[3].func = func_8010CAD8_mstory1;
}

/* actor 4 */
void func_8010EC30_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115A30_mstory1[4].obj = obj;
    D_80115A30_mstory1[4].flags = 0;
    D_80115A30_mstory1[4].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
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
    D_80115AF0_mstory1[4] = D_801150C0_mstory1[4];
    Hu3DModelPosSet(obj->model[1], D_80115AF0_mstory1[4].x, D_80115AF0_mstory1[4].y, D_80115AF0_mstory1[4].z);
    Hu3DModelPosSet(obj->model[2], D_80115AF0_mstory1[4].x, -5.0f, D_80115AF0_mstory1[4].z);
    omPrcSetDestructor(0, func_8010EE14_mstory1);
    D_80115A30_mstory1[4].func = func_8010CAD8_mstory1;
    while (TRUE) {
        D_80115A30_mstory1[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010EE14_mstory1(void) {
}

const Vec D_80115394_mstory1[2] = { { -300.0f, 0.0f, 350.0f }, { 500.0f, 0.0f, 350.0f } };
const Vec D_801153AC_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_801153B8_mstory1 = { 0.0f, 90.0f, 0.0f };
const Vec D_801153C4_mstory1 = { 0.0f, -90.0f, 0.0f };
const Vec D_801153D0_mstory1 = { 0.0f, 30.0f, 0.0f };

void func_8010EE1C_mstory1(omObjData *obj) {
    s16 model;

    model = obj->model[1];
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B14_mstory1(obj, (Vec *)D_80115394_mstory1, 30);
    func_8010704C_mstory1(obj, (Vec *)&D_801153AC_mstory1, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (!(D_80115A30_mstory1[3].flags & 1)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, (Vec *)&D_801153C4_mstory1, 5);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, (Vec *)&D_801153B8_mstory1, 5);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, (Vec *)&D_801153AC_mstory1, 5);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, (Vec *)&D_801153D0_mstory1, 10);
    HuAudFXPlay(0x2A0);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A29 : 0x5B1A);
    func_80106A1C_mstory1();
    D_80115A30_mstory1[4].flags |= 1;
    while (!(D_80115A30_mstory1[3].flags & 8)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
        func_80107220_mstory1(model);
    }
}

/* actor 5: a copy of actor 4's model */
void func_8010F244_mstory1(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115A30_mstory1[5].obj = obj;
    D_80115A30_mstory1[5].flags = 0;
    D_80115A30_mstory1[5].sfxOn = 0;
    src = D_80115A30_mstory1[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115AF0_mstory1[5] = D_801150C0_mstory1[5];
    Hu3DModelPosSet(obj->model[1], D_80115AF0_mstory1[5].x, D_80115AF0_mstory1[5].y, D_80115AF0_mstory1[5].z);
    Hu3DModelPosSet(obj->model[2], D_80115AF0_mstory1[5].x, -5.0f, D_80115AF0_mstory1[5].z);
    omPrcSetDestructor(0, func_8010F848_mstory1);
    D_80115A30_mstory1[5].func = func_8010CAD8_mstory1;
    while (TRUE) {
        D_80115A30_mstory1[5].func(obj);
        HuPrcVSleep();
    }
}

const Vec D_801153DC_mstory1[2] = { { 300.0f, 0.0f, 350.0f }, { 1100.0f, 0.0f, 350.0f } };
const Vec D_801153F4_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_80115400_mstory1 = { 0.0f, 90.0f, 0.0f };
const Vec D_8011540C_mstory1 = { 0.0f, -90.0f, 0.0f };
const Vec D_80115418_mstory1[2] = { { 0.0f, -30.0f, 0.0f }, { 166.66666f, 0.0f, 150.0f } };

/* actor 5 uses actor 4's motions */
void func_8010F3EC_mstory1(omObjData *obj) {
    omObjData *src;
    s16 model;

    src = D_80115A30_mstory1[4].obj;
    model = obj->model[1];
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B14_mstory1(obj, (Vec *)D_801153DC_mstory1, 30);
    func_8010704C_mstory1(obj, (Vec *)&D_801153F4_mstory1, 10);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    while (!(D_80115A30_mstory1[3].flags & 1)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[src->motion[2]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    func_8001C624_main(model, HmfModelData[src->motion[2]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, (Vec *)&D_80115400_mstory1, 5);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, (Vec *)&D_8011540C_mstory1, 5);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_8010704C_mstory1(obj, (Vec *)&D_801153F4_mstory1, 5);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    while (!(D_80115A30_mstory1[3].flags & 2)) {
        HuPrcVSleep();
    }
    func_8010704C_mstory1(obj, (Vec *)D_80115418_mstory1, 10);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(3) == 0 ? 0x5A2A : 0x5B1B);
    func_80106A1C_mstory1();
    D_80115A30_mstory1[5].flags |= 1;
    while (!(D_80115A30_mstory1[3].flags & 8)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        func_8001C624_main(model, HmfModelData[src->motion[2]].unk02, 0, 10, 0);
        func_80107220_mstory1(model);
    }
}

void func_8010F848_mstory1(void) {
}

/* actor 6 */
void func_8010F850_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115A30_mstory1[6].obj = obj;
    D_80115A30_mstory1[6].flags = 0;
    D_80115A30_mstory1[6].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_80115B50_mstory1);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_80115AF0_mstory1[6] = D_801150C0_mstory1[6];
    Hu3DModelPosSet(obj->model[1], D_80115AF0_mstory1[6].x, D_80115AF0_mstory1[6].y, D_80115AF0_mstory1[6].z);
    Hu3DModelPosSet(obj->model[2], D_80115AF0_mstory1[6].x, -5.0f, D_80115AF0_mstory1[6].z);
    omPrcSetDestructor(0, func_8010FA40_mstory1);
    D_80115A30_mstory1[6].func = func_8010CAD8_mstory1;
    D_80114B40_mstory1 = 1;
    while (TRUE) {
        D_80115A30_mstory1[6].func(obj);
        HuPrcVSleep();
    }
}

void func_8010FA40_mstory1(void) {
}

const Vec D_80115430_mstory1[2] = { { 700.0f, 0.0f, 150.0f }, { 216.66666f, 0.0f, 150.0f } };
const Vec D_80115448_mstory1[2] = { { 0.0f, 90.0f, 0.0f }, { 0.0f, -90.0f, 0.0f } };

void func_8010FA48_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)D_80115448_mstory1, 10);
    func_80106B14_mstory1(obj, (Vec *)D_80115430_mstory1, 50);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80115A30_mstory1[6].func = func_8010CAD8_mstory1;
}

const Vec D_80115460_mstory1 = { 0.0f, 10.0f, 0.0f };

void func_8010FAC4_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)&D_80115460_mstory1, 20);
    D_80115A30_mstory1[6].func = func_8010CAD8_mstory1;
}

/* NON_MATCHING: masked 0 except one nop: the assembler pads after sindf's jal (the delay slot
   holds mov.s $f12) where retail does not; one instruction long. */
/* actor 6 bobs while D_80114B40_mstory1 is set */
void func_8010FAF8_mstory1(void) {
    Vec pos;
    f32 angle;
    f32 y;
    s16 model;

    angle = 0.0f;
    if (D_80114B40_mstory1 != 0) {
        model = D_80115A30_mstory1[6].obj->model[1];
        pos.y = HmfModelData[model].pos.y;
        while (TRUE) {
            pos.x = HmfModelData[model].pos.x;
            pos.z = HmfModelData[model].pos.z;
            y = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
            HuPrcVSleep();
        }
    }
}

/* the item model, per chapter */
const s32 D_8011546C_mstory1[7] = { 0x001D0003, 0x001D0004, 0x001D0005, 0x001D0006,
                                    0x001D0007, 0x001D0008, 0x001D0009 };

/* actor 7: the item and its shadow */
void func_8010FC24_mstory1(void) {
    omObjData *obj;
    s16 shadow;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_80115A30_mstory1[7].obj = obj;
    D_80115A30_mstory1[7].flags = 0;
    D_80115A30_mstory1[7].sfxOn = 0;
    obj->model[1] = func_8000B108_main(D_8011546C_mstory1[1], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115AF0_mstory1[7] = D_801150C0_mstory1[7];
    Hu3DModelPosSet(obj->model[1], D_80115AF0_mstory1[7].x, D_80115AF0_mstory1[7].y, D_80115AF0_mstory1[7].z);
    shadow = func_8000CED8_main(0xB0004, 0x6A9);
    D_80115B52_mstory1 = shadow;
    func_8000CD00_main(shadow, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_80115B52_mstory1, 60.0f);
    func_800138EC_main(D_80115B52_mstory1, 1, 0);
    func_8001C258_main(D_80115B52_mstory1, 4, 4);
    omPrcSetDestructor(0, func_8010FDDC_mstory1);
    D_80115A30_mstory1[7].func = func_8010CAD8_mstory1;
    while (TRUE) {
        D_80115A30_mstory1[7].func(obj);
        HuPrcVSleep();
    }
}

void func_8010FDDC_mstory1(void) {
}

/* the item flies along two paths to the player */
void func_8010FDE4_mstory1(omObjData *obj) {
    Vec pos;
    ObPath *paths[2];
    omObjData *other;
    f32 rot;
    f32 t;
    s32 i;

    paths[0] = func_8010BDC0_mstory1(D_80114B44_mstory1, 0);
    paths[1] = func_8010BDC0_mstory1(D_80114B74_mstory1, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_80115B52_mstory1, 4, 0);
    func_800138EC_main(D_80115B52_mstory1, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        t = i * 0.02f;
        func_8010C0C4_mstory1(paths[0], t * t, &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115B52_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    other = D_80115A30_mstory1[6].obj;
    func_8001C624_main(other->model[1], HmfModelData[other->motion[2]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_80115A30_mstory1[7].flags |= 2;
    HuAudFXPlay(0x218);
    func_8001C624_main(other->model[1], HmfModelData[other->motion[0]].unk02, 0, 10, 2);
    rot = 0.0f;
    for (i = 0; i < 120; i++) {
        t = i * 0.008333334f;
        func_8010C0C4_mstory1(paths[1], t * t, &pos);
        rot -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rot, 0.0f);
        func_8000CFA4_main(D_80115B52_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_80115B52_mstory1, 4, 4);
    HuAudFXPlay(0x21A);
    func_8010C96C_mstory1(paths[0]);
    func_8010C96C_mstory1(paths[1]);
    D_80115A30_mstory1[7].flags = 1;
    D_80115A30_mstory1[7].func = func_8010CAD8_mstory1;
}

/* turns obj's model to face target's */
void func_80110100_mstory1(omObjData *obj, omObjData *target) {
    s16 models[2];
    Vec pos[2];
    Vec rot;
    Vec d;
    s32 i;

    models[0] = obj->model[1];
    models[1] = target->model[1];
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

/* starts actor's voice (or looping sound) se */
void func_80110248_mstory1(s32 actor, s32 se) {
    if (D_80115A30_mstory1[actor].sfxOn == 0) {
        D_80115A30_mstory1[actor].sfxOn = 1;
        D_80115A30_mstory1[actor].sfxId = se;
        switch (actor) {
        case 0:
            D_80115A30_mstory1[actor].sfxNo = CharFXPlay(se, GwStory.unk1);
            break;
        case 2:
            if (func_80106AFC_mstory1(3) == 0) {
                D_80115A30_mstory1[actor].sfxNo = CharFXPlay(se, 3);
            } else {
                D_80115A30_mstory1[actor].sfxNo = CharFXPlay(se, 1);
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

void func_8011032C_mstory1(s32 actor) {
    if (D_80115A30_mstory1[actor].sfxOn == 1) {
        D_80115A30_mstory1[actor].sfxOn = 0;
        switch (actor) {
        case 0:
        case 2:
            HuAudFXStop((s16)D_80115A30_mstory1[actor].sfxNo);
            break;
        case 1:
        case 3:
        case 4:
        case 5:
            break;
        }
    }
}

/* replays each actor's sound while its model's motion is stopped */
void func_801103A8_mstory1(void) {
    s32 se;
    s32 i;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (D_80115A30_mstory1[i].sfxOn == 1 && HmfModelData[D_80115A30_mstory1[i].obj->model[1]].unk40 == 0.0f) {
                se = D_80115A30_mstory1[i].sfxId;
                switch (i) {
                case 0:
                    D_80115A30_mstory1[i].sfxNo = CharFXPlay(se, GwStory.unk1);
                    break;
                case 2:
                    if (func_80106AFC_mstory1(3) == 0) {
                        D_80115A30_mstory1[i].sfxNo = CharFXPlay(se, 3);
                    } else {
                        D_80115A30_mstory1[i].sfxNo = CharFXPlay(se, 1);
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
