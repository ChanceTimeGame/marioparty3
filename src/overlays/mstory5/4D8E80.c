#include "common.h"

#include "mallocblock.h"
/* a story-scene actor: its object and the action its process runs every frame (as mstory1's) */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 flags; /* cues the scripts give each other */
    /* 0x0C */ s32 sfxOn; /* a looping sound effect is playing */
    /* 0x10 */ s32 sfxId;
    /* 0x14 */ s32 sfxNo; /* its handle */
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
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);

void func_80106B64_mstory5(omObjData *obj, const Vec *to, s32 frames, s32 turn);
void func_80106B48_mstory5(omObjData *obj, const Vec *to, s32 frames);
void func_80107080_mstory5(omObjData *obj, const Vec *to, s32 frames);
void func_80107254_mstory5(s16 model);
void func_801068E4_mstory5(s16 model, s16 anim, s16 frame);
void func_801069B8_mstory5(void);
/* a model part looked up by name (func_8001D33C_main) */
typedef struct StoryHmfPart {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ Vec scale;
    /* 0x28 */ char unk28[0x18];
    /* 0x40 */ Vec scale2;
} StoryHmfPart;
void *func_8001D33C_main(s16, const char *);
void func_8001EF6C_main(s16 arg0, s16 arg1, const char *arg2);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);
void func_80105FDC_mstory5(void);
void func_80105FEC_mstory5(s32 arg0);
s32 func_801068C8_mstory5(void);
void func_80106A20_mstory5(void);
void func_80106A50_mstory5(void);
void func_80106A74_mstory5(s32 mess);
s32 func_80106B30_mstory5(s32 chr);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void *HuMemAllocTag(s32 size, s16 tag);
void HuMemFree(void *data);
void func_8010F7D4_mstory5(ObPath *path, f32 t, Vec *out);
/* the second scene's actors (func_801100AC_mstory5) */
extern StoryActor D_801153A0_mstory5[8];
extern StoryActor D_80115460_mstory5; /* the effect object (func_80112104_mstory5) */
extern Vec D_80115478_mstory5[8]; /* actor positions */
extern s16 D_801154D8_mstory5; /* shadow model, linked by every actor */
extern s16 D_801154DC_mstory5[4]; /* texture animations */
extern const Vec D_80114D20_mstory5[8]; /* actor start positions */
extern const s32 D_80114D80_mstory5[8];
extern const s32 D_80114DA0_mstory5[8];
extern const s32 D_80114DC0_mstory5[8];
extern const s32 D_80114DE0_mstory5[8];
void func_80110208_mstory5(void);
void func_80110618_mstory5(void);
void func_801114E8_mstory5(void);
void func_80111DB8_mstory5(void);
void func_80112104_mstory5(void);
void func_8011275C_mstory5(void);
void func_80112F38_mstory5(void);
void func_80113470_mstory5(void);
void func_80113974_mstory5(void);
void func_80113D2C_mstory5(void);
void func_80113E58_mstory5(void);
void func_801145DC_mstory5(void);
extern s16 D_801154DA_mstory5; /* the item effect model */
extern const Vec D_80114E00_mstory5;
extern const Vec D_80114E0C_mstory5;
extern const Vec D_80114E18_mstory5[2];
extern const Vec D_80114E30_mstory5;
extern const Vec D_80114E54_mstory5;
extern const Vec D_80114E60_mstory5;
extern const Vec D_80114E6C_mstory5;
extern const Vec D_80114E78_mstory5;
extern const Vec D_80114E84_mstory5;
extern const Vec D_80114E90_mstory5;
extern const char D_80114E9C_mstory5[]; /* "item_hook" */
extern const f64 D_80114EA8_mstory5; /* 0.8 */
extern const f64 D_80114EB0_mstory5; /* 1.0 */
void func_80111B60_mstory5(omObjData *obj);
void func_80111C48_mstory5(omObjData *obj);
void func_8011299C_mstory5(omObjData *obj);
void func_80113B6C_mstory5(omObjData *obj);
void func_8011447C_mstory5(u32 actor, s32 fx);
void func_80114560_mstory5(u32 actor);
void func_80017954_main(s16, s16, s16, s16);
extern s32 D_801154E4_mstory5[3]; /* texture animations */
extern s16 D_801154F0_mstory5;
/* a puff of the effect object (func_80112104_mstory5): time < 0 is idle; it grows and drifts for 40 frames */
typedef struct StoryPuff {
    /* 0x00 */ f32 time;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec vel;
} StoryPuff; /* size = 0x1C */
extern StoryPuff D_801154F8_mstory5[16];
/* a sprite-model slot (D_800CBB60_main entry; src/14EA0.c unk_800ECDE0) */
typedef struct StorySprModel {
    /* 0x00 */ s16 model;
    /* 0x02 */ char unk_02[0x22];
} StorySprModel; /* size = 0x24 */
extern StorySprModel *D_800CBB60_main;
u16 func_80014618_main(s16 index, u16 arg1);
void func_80014794_main(s16 index, u8 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);
void func_80032FF8_main(s32, u8);
s16 func_80032694_main(HmfData *, u16, s32, char *);
s32 HmfAnimCreate(HmfData *, void *, s32, char *);
void HuMemMemoryFreePerm(void *ptr);
void func_80111818_mstory5(void);
void func_80111FE0_mstory5(void);
void func_80111FE8_mstory5(omObjData *obj);
void func_80113CF8_mstory5(omObjData *obj);
void func_80114018_mstory5(omObjData *obj);
extern const Vec D_80114EB8_mstory5;
extern const Vec D_80114EC4_mstory5;
extern const Vec D_80114EDC_mstory5;
extern const Vec D_80114EF4_mstory5;
extern const Vec D_80114F0C_mstory5;
extern const Vec D_80114F18_mstory5;
extern const Vec D_80114F24_mstory5;
extern const Vec D_80114F30_mstory5;
extern const Vec D_80114F3C_mstory5;
extern const Vec D_80114F48_mstory5;
extern const Vec D_80114F60_mstory5;
extern const Vec D_80114F6C_mstory5;
extern const Vec D_80114F78_mstory5;
extern const Vec D_80114F84_mstory5;
extern const Vec D_80114F90_mstory5;
extern const Vec D_80114F9C_mstory5;
void func_80112514_mstory5(omObjData *obj);
void func_80113138_mstory5(omObjData *obj);
void func_80113618_mstory5(omObjData *obj);
void func_8011396C_mstory5(void);
void func_80112994_mstory5(void);
void func_80113130_mstory5(void);
void func_80113B64_mstory5(void);
void func_80114010_mstory5(void);
extern const s32 D_8011514C_mstory5[];
extern const Vec D_80115134_mstory5;
extern const Vec D_80114FC0_mstory5;
extern const Vec D_80114FD8_mstory5;
extern const Vec D_80114FE4_mstory5;
extern const Vec D_80114FF0_mstory5;
extern const Vec D_80115014_mstory5;
extern const Vec D_80115020_mstory5;
extern const Vec D_8011502C_mstory5;
extern const Vec D_80115038_mstory5;
extern const Vec D_80115050_mstory5;
extern const Vec D_80115068_mstory5;
extern const Vec D_80115074_mstory5;
extern const Vec D_80115080_mstory5;
extern const Vec D_80115098_mstory5;
extern const Vec D_801150B0_mstory5;
extern const Vec D_801150BC_mstory5;
extern const Vec D_801150E0_mstory5;
extern const Vec D_801150EC_mstory5;
extern const Vec D_801150F8_mstory5;
extern const Vec D_80115110_mstory5;
extern const Vec D_8011511C_mstory5;
extern const Vec D_80115128_mstory5;
void func_800461B4_main(s16 arg0);
void func_8000CD00_main(s16, f32, f32, f32);
s16 func_8000CED8_main(s32, s32);
void func_8000CFA4_main(s16, f32, f32, f32);
void func_8000D018_main(s16, f32);

s32 D_80114820_mstory5 = 3;
s32 D_80114824_mstory5 = 0;
Vec D_80114828_mstory5[] = {
    { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f },
};
Vec D_80114858_mstory5[] = {
    { -100.0f, 300.0f, 300.0f }, { -200.0f, 200.0f, 100.0f }, { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f },  { -50.0f, 120.0f, 450.0f },  { 9999.0f, 9999.0f, 9999.0f },
};

ObPath *func_8010F4D0_mstory5(Vec *points, s16 flags) {
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
void func_8010F7D4_mstory5(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4D8E80", func_8010F7D4_mstory5);
#endif

void func_8011007C_mstory5(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* chapter 5, second scene: the actors' processes */
void func_801100AC_mstory5(void) {
    func_801069B8_mstory5();
    D_801154D8_mstory5 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80110208_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_801114E8_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80111DB8_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_8011275C_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112F38_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113470_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113974_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113D2C_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113E58_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_80112104_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_801145DC_mstory5, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_801154D8_mstory5, 4, 4);
}

void func_80110200_mstory5(omObjData *obj) {
}

// masked 0 when func_80017AD8_main returns s16 (functions.us.h says u8), as mstory1's func_801081E0
#ifdef NON_MATCHING
/* actor 0: the player's character */
void func_80110208_mstory5(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 6, 0x10, -1, NULL);
    D_801153A0_mstory5[0].obj = obj;
    D_801153A0_mstory5[0].flags = 0;
    D_801153A0_mstory5[0].sfxOn = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
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
    func_8000B460_main(obj, 5, D_80114D80_mstory5[chr]);
    func_8000B460_main(obj, 6, D_80114DA0_mstory5[chr]);
    func_8000B460_main(obj, 7, D_80114DC0_mstory5[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_80114DE0_mstory5[chr]);
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x9B));
    D_801154DC_mstory5[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_801154DC_mstory5[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_801154DC_mstory5[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_801154DC_mstory5[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_80115478_mstory5[0] = D_80114D20_mstory5[0];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[0].x, D_80115478_mstory5[0].y, D_80115478_mstory5[0].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[0].x, -5.0f, D_80115478_mstory5[0].z);
    Hu3DModelPosSet(obj->model[4], D_80115478_mstory5[0].x, D_80115478_mstory5[0].y, D_80115478_mstory5[0].z);
    omPrcSetDestructor(0, func_80110618_mstory5);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[0].func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4D8E80", func_80110208_mstory5);
#endif

void func_80110618_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D20_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D2C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D38_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D44_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D50_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D5C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D68_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D74_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D80_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114DA0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114DC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114DE0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E00_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E30_mstory5);

const Vec D_80114E3C_mstory5 = { 230.0f, 0.0f, 480.0f };
const Vec D_80114E48_mstory5 = { 680.0f, 0.0f, 480.0f };

/* actor 0 (the player): uses its item on actor 7, then the scene with actors 1, 3 and 6 */
void func_80110620_mstory5(omObjData *obj) {
    StoryHmfPart *part;
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
    func_80107228_mstory5(obj, 0.0f, 110.0f, 0.0f, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], model, D_80114E9C_mstory5);
    func_8001C258_main(obj->model[3], 4, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    while (!(D_801153A0_mstory5[7].flags & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_801153A0_mstory5[7].obj->model[1], 4, 4);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x45);
    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x46);
    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x47);
    part = func_8001D33C_main(model, D_80114E9C_mstory5);
    i = 0;
    do {
        scale = sindf(i * 18.0f) * D_80114EA8_mstory5 + D_80114EB0_mstory5;
        part->scale.x = scale;
        part->scale.y = scale;
        part->scale.z = scale;
        part->scale2.x = scale;
        part->scale2.y = scale;
        part->scale2.z = scale;
        HuPrcVSleep();
        i++;
    } while (i < 10);
    func_8002FDCC_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x47);
    func_8002FDCC_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x46);
    func_8002FDCC_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x45);
    func_80105FEC_mstory5(3);
    while (func_801068C8_mstory5() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3E : 0x5B31);
    func_80106A50_mstory5();
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
    func_80107080_mstory5(obj, &D_80114E00_mstory5, 10);
    HuAudSeqPlay(0x72);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[2]);
    func_80107254_mstory5(model);
    sfx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    other = D_801153A0_mstory5[6].obj;
    func_80107080_mstory5(other, &D_80114E90_mstory5, 3);
    func_80106B48_mstory5(other, &D_80114E60_mstory5, 5);
    func_80107080_mstory5(other, &D_80114E78_mstory5, 3);
    D_801153A0_mstory5[1].func = func_80111C48_mstory5;
    HuAudFXPlay(0x219);
    HuAudFXStop(sfx);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[3]);
    func_80107080_mstory5(other, &D_80114E84_mstory5, 3);
    func_80106B64_mstory5(other, &D_80114E6C_mstory5, 10, 0);
    func_80107254_mstory5(model);
    HuAudSeqPlay(0x26);
    func_80107080_mstory5(obj, &D_80114E0C_mstory5, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[0]);
    HuAudFXPlay(0x159);
    func_8001C624_main(D_801153A0_mstory5[6].obj->model[1], HmfModelData[D_801153A0_mstory5[6].obj->motion[1]].unk02, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3F : 0x5B32);
    func_80106A50_mstory5();
    func_8001C624_main(D_801153A0_mstory5[6].obj->model[1], HmfModelData[D_801153A0_mstory5[6].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(model, HmfModelData[obj->motion[8]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    D_801153A0_mstory5[3].func = func_8011299C_mstory5;
    D_801153A0_mstory5[6].func = func_80113B6C_mstory5;
    D_801153A0_mstory5[1].func = func_80111B60_mstory5;
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    func_8011447C_mstory5(0, 0x1F);
    func_80107080_mstory5(obj, &D_80114E18_mstory5[0], 20);
    func_80106B48_mstory5(obj, &D_80114E3C_mstory5, 20);
    func_80114560_mstory5(0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].flags & 2)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    func_8011447C_mstory5(0, 0x1F);
    func_80106B64_mstory5(obj, &D_80114E54_mstory5, 30, 0);
    func_80114560_mstory5(0);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    for (i = 0; i < 2; i++) {
        func_8001C624_main(model, HmfModelData[obj->motion[9]].unk02, 0, 5, 0);
        func_8001C92C_main(model, 5.0f);
        func_80107254_mstory5(model);
        func_8001C5B4_main(model, obj->motion[9]);
        func_8001C814_main(model, 4, 4);
        func_8001C814_main(model, 2, 0);
        func_8001C92C_main(model, 5.0f);
        func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
        while (HmfModelData[model].unk40 > 0.0f) {
            HuPrcVSleep();
        }
        func_8001C814_main(model, 4, 0);
    }
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8001C92C_main(model, 1.0f);
    while (!(D_801153A0_mstory5[3].flags & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80114E30_mstory5, 40);
    while (!(D_801153A0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80114E18_mstory5[0], 15);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    func_8011447C_mstory5(0, 0x1F);
    func_80106B48_mstory5(obj, &D_80114E48_mstory5, 30);
    func_80114560_mstory5(0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

void func_801113BC_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C624_main(model, HmfModelData[obj->motion[9]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    HuPrcSleep(80);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

void func_80111480_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80114EB8_mstory5, 10);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

void func_801114B4_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80114EC4_mstory5, 10);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E54_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EA8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EB0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EB8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EC4_mstory5);

void func_801114E8_mstory5(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[1].obj = obj;
    D_801153A0_mstory5[1].flags = 0;
    D_801153A0_mstory5[1].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80115478_mstory5[1] = D_80114D20_mstory5[1];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[1].x, D_80115478_mstory5[1].y, D_80115478_mstory5[1].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[1].x, -5.0f, D_80115478_mstory5[1].z);
    data = DataRead(0xA007E);
    D_801154E4_mstory5[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main((s16)D_801154E4_mstory5[0], 1, 0);
    func_80032FF8_main((s16)D_801154E4_mstory5[0], 0);
    D_801154F0_mstory5 = func_80032694_main(HmfModelData[obj->model[1]].hmf, (s16)D_801154E4_mstory5[0], 0, "c204n_0_DEF");
    D_801154E4_mstory5[0] = D_800D1714_main[D_801154E4_mstory5[0]].unk_00;
    data = DataRead(0xA0080);
    D_801154E4_mstory5[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_801154E4_mstory5[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, (s16)D_801154E4_mstory5[0]);
    omPrcSetDestructor(0, func_80111818_mstory5);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80111818_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EDC_mstory5);

const Vec D_80114EE8_mstory5 = { 10.0f, 378.9f, 0.0f };

void func_80111820_mstory5(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    D_801153A0_mstory5[0].func = func_801113BC_mstory5;
    D_801153A0_mstory5[6].func = func_80113CF8_mstory5;
    func_80107080_mstory5(obj, (Vec *)&D_80114EE8_mstory5, 30);
    func_80106B48_mstory5(obj, (Vec *)&D_80114F48_mstory5, 20);
    HuPrcSleep(30);
    func_80107080_mstory5(obj, (Vec *)&D_80114F18_mstory5, 10);
    func_80106B48_mstory5(obj, (Vec *)&D_80114F3C_mstory5, 15);
    D_801153A0_mstory5[0].func = func_80111480_mstory5;
    func_80107080_mstory5(obj, (Vec *)&D_80114EF4_mstory5, 10);
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154E4_mstory5[1]);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3C : 0x5B2F);
    func_80106A50_mstory5();
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154E4_mstory5[0]);
    func_80107228_mstory5(D_801153A0_mstory5[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_80107080_mstory5(D_801153A0_mstory5[6].obj, (Vec *)&D_80114F60_mstory5, 10);
    func_80107080_mstory5(obj, (Vec *)&D_80114F0C_mstory5, 20);
    func_8001C624_main(D_801153A0_mstory5[6].obj->model[1], HmfModelData[D_801153A0_mstory5[6].obj->motion[1]].unk02, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3D : 0x5B30);
    func_80106A50_mstory5();
    func_8001C624_main(D_801153A0_mstory5[6].obj->model[1], HmfModelData[D_801153A0_mstory5[6].obj->motion[0]].unk02, 0, 10, 2);
    func_80107080_mstory5(D_801153A0_mstory5[6].obj, (Vec *)&D_80114F6C_mstory5, 10);
    D_801153A0_mstory5[7].func = func_80114018_mstory5;
    func_80107080_mstory5(obj, (Vec *)&D_80114EDC_mstory5, 20);
    func_8001C624_main(D_801153A0_mstory5[0].obj->model[1], HmfModelData[D_801153A0_mstory5[0].obj->motion[10]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[7].flags & 2)) {
        HuPrcVSleep();
    }
    D_801153A0_mstory5[0].func = func_80110620_mstory5;
    HuPrcSleep(40);
    func_80107080_mstory5(obj, (Vec *)&D_80114F30_mstory5, 50);
    func_80107080_mstory5(obj, (Vec *)&D_80114F24_mstory5, 40);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
}

void func_80111B60_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80114F9C_mstory5, 20);
    func_80106B48_mstory5(obj, (Vec *)&D_80114F78_mstory5, 20);
    while (!(D_801153A0_mstory5[3].flags & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(obj, (Vec *)&D_80114F90_mstory5, 30, 0);
    while (!(D_801153A0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    func_80106B48_mstory5(obj, (Vec *)&D_80114F84_mstory5, 30);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
}

void func_80111C48_mstory5(omObjData *obj) {
    Vec pos;
    Vec start;
    s16 model;
    s32 i;
    f32 y;

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
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, (s16)D_801154E4_mstory5[2]);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
}

void func_80111DB8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[2].obj = obj;
    D_801153A0_mstory5[2].flags = 0;
    D_801153A0_mstory5[2].sfxOn = 0;
    if (func_80106B30_mstory5(2) == 0) {
        obj->model[1] = func_8000B108_main(0x700A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
        func_8000B460_main(obj, 0, 0x70000);
        func_8000B460_main(obj, 1, 0x1D0050);
        func_8000B460_main(obj, 2, 0x1D0051);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
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
    D_80115478_mstory5[2] = D_80114D20_mstory5[2];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[2].x, D_80115478_mstory5[2].y, D_80115478_mstory5[2].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[2].x, -5.0f, D_80115478_mstory5[2].z);
    omPrcSetDestructor(0, func_80111FE0_mstory5);
    D_801153A0_mstory5[2].func = func_80111FE8_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80111FE0_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EF4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F24_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F30_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F3C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F48_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F9C_mstory5);

const Vec D_80114FB4_mstory5 = { 200.0f, 0.0f, 1200.0f };

void func_80111FE8_mstory5(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106B30_mstory5(2) == 0) {
        CharFXPlay(0x26B, 2);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_801153A0_mstory5[1].func = func_80111820_mstory5;
    HuPrcSleep(70);
    if (func_80106B30_mstory5(2) == 0) {
        CharFXPlay(0x286, 2);
    } else {
        CharFXPlay(0x286, 1);
    }
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    func_80106B48_mstory5(obj, (Vec *)&D_80114FB4_mstory5, 40);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[2].func = func_80110200_mstory5;
}

/* the effect object: 16 puffs (NON_MATCHING: registers s1/s2 swapped, and retail reloads
   time after the += before comparing it with 40) */
#ifdef NON_MATCHING
void func_80112104_mstory5(void) {
    omObjData *obj;
    void *data;
    s32 i;
    s32 base;
    s16 model;
    f32 scale;

    obj = omAddObj(0x14, 0x14, 1, -1, NULL);
    D_80115460_mstory5.obj = obj;
    for (i = 0; i < 16; i++) {
        if (i == 0) {
            data = DataRead(0x1D0036);
            model = base = HmfSprModelCreate(data, 0xA89, 8);
            DataClose(data);
        } else {
            model = func_80014618_main(base, 8);
        }
        func_800147FC_main(model, 0xF0, 0x40, 8);
        func_80014794_main(model, 0x80);
        model = D_800CBB60_main[model].model;
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x70000000, 0x70000000);
        func_8001C814_main(model, 2, 2);
        func_8001C258_main(model, 4, 4);
        obj->model[i + 1] = model;
        D_801154F8_mstory5[i].time = -10.0f;
        D_801154F8_mstory5[i].pos.x = 0.0f;
        D_801154F8_mstory5[i].pos.y = 0.0f;
        D_801154F8_mstory5[i].pos.z = 0.0f;
        D_801154F8_mstory5[i].vel.x = 0.0f;
        D_801154F8_mstory5[i].vel.y = 0.0f;
        D_801154F8_mstory5[i].vel.z = 0.0f;
    }
    D_80115460_mstory5.func = func_80110200_mstory5;
    while (TRUE) {
        D_80115460_mstory5.func(obj);
        for (i = 0; i < 16; i++) {
            if (!(D_801154F8_mstory5[i].time < 0.0f)) {
                func_8001C258_main(obj->model[i + 1], 4, 0);
                scale = D_801154F8_mstory5[i].time / 40.0f * 3.0f + 1.0f;
                Hu3DModelScaleSet(obj->model[i + 1], scale, scale, scale);
                Hu3DModelPosSet(obj->model[i + 1], D_801154F8_mstory5[i].pos.x, D_801154F8_mstory5[i].pos.y, D_801154F8_mstory5[i].pos.z);
                D_801154F8_mstory5[i].pos.x += D_801154F8_mstory5[i].vel.x;
                D_801154F8_mstory5[i].pos.y += D_801154F8_mstory5[i].vel.y;
                D_801154F8_mstory5[i].pos.z += D_801154F8_mstory5[i].vel.z;
                D_801154F8_mstory5[i].time = D_801154F8_mstory5[i].time + 1.0f;
                if (D_801154F8_mstory5[i].time >= 40.0f) {
                    func_8001C258_main(obj->model[i + 1], 4, 4);
                    D_801154F8_mstory5[i].time = -10.0f;
                }
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4D8E80", func_80112104_mstory5);
#endif

/* NON_MATCHING: only the HmfModelData load is scheduled differently */
#ifdef NON_MATCHING
/* the effect object's action: every third frame an idle puff starts 300 in front of actor 3
   and drifts away. Retail shows the puff's model from actor 3's object (obj is unused), not the
   effect object that owns the puffs; func_80112104_mstory5 shows the right one every frame anyway. */
void func_80112514_mstory5(omObjData *obj) {
    Vec pos;
    Vec rot;
    Vec off;
    omObjData *actor;
    HmfModel *model;
    s32 i;

    if (D_80114820_mstory5 >= 3) {
        D_80114820_mstory5 = 0;
        actor = D_801153A0_mstory5[3].obj;
        model = &HmfModelData[actor->model[1]];
        pos.x = model->pos.x;
        pos.y = model->pos.y;
        pos.z = model->pos.z;
        rot.x = model->rot.x;
        rot.y = model->rot.y;
        rot.z = model->rot.z;
        for (i = 0; i < 16; i++) {
            if (D_801154F8_mstory5[i].time < 0.0f) {
                off.x = 0.0f;
                off.y = 150.0f;
                off.z = 300.0f;
                D_801154F8_mstory5[i].pos.x = cosdf(rot.y) * off.x + pos.x - sindf(rot.y) * off.z;
                D_801154F8_mstory5[i].pos.y = pos.y + off.y;
                D_801154F8_mstory5[i].pos.z = sindf(rot.y) * off.x + pos.z + cosdf(rot.y) * off.z;
                D_801154F8_mstory5[i].vel.x = sindf(rot.y) * 5.0f;
                D_801154F8_mstory5[i].vel.y = cosdf(120.0f) * 5.0f;
                D_801154F8_mstory5[i].vel.z = cosdf(rot.y) * 5.0f;
                D_801154F8_mstory5[i].time = 0.0f;
                func_8001C258_main(actor->model[i + 1], 4, 0);
                break;
            }
        }
    }
    D_80114820_mstory5++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4D8E80", func_80112514_mstory5);
#endif

void func_8011275C_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x10, 8, -1, NULL);
    D_801153A0_mstory5[3].obj = obj;
    D_801153A0_mstory5[3].flags = 0;
    D_801153A0_mstory5[3].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0xA003A);
    func_8000B460_main(obj, 4, 0xA003B);
    func_8000B460_main(obj, 5, 0x1D0031);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115478_mstory5[3] = D_80114D20_mstory5[3];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[3].x, D_80115478_mstory5[3].y, D_80115478_mstory5[3].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[3].x, -5.0f, D_80115478_mstory5[3].z);
    omPrcSetDestructor(0, func_80112994_mstory5);
    D_801153A0_mstory5[3].func = func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80112994_mstory5(void) {
}

/* actor 3's script: it drives the scene, cueing actors 4-6 through its flags */
void func_8011299C_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A40 : 0x5B33);
    func_80106A50_mstory5();
    D_801153A0_mstory5[4].func = func_80113138_mstory5;
    D_801153A0_mstory5[5].func = func_80113618_mstory5;
    D_801153A0_mstory5[3].flags |= 2;
    func_80106B48_mstory5(obj, (Vec *)&D_80114FC0_mstory5, 40);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuAudFXPlay(0x29C);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A41 : 0x5B34);
    func_80106A50_mstory5();
    D_801153A0_mstory5[3].flags |= 8;
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80106B48_mstory5(D_801153A0_mstory5[1].obj, (Vec *)&D_8011502C_mstory5, 10);
    HuAudFXPlay(0x2A8);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A42 : 0x5B35);
    func_80106A50_mstory5();
    func_8001C624_main(model, HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801153A0_mstory5[3].flags |= 0x10;
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107080_mstory5(obj, (Vec *)&D_80114FF0_mstory5, 10);
    func_80106B64_mstory5(obj, (Vec *)&D_80114FD8_mstory5, 40, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801153A0_mstory5[3].flags |= 1;
    func_80107080_mstory5(obj, (Vec *)&D_80115020_mstory5, 90);
    HuPrcSleep(60);
    func_80107080_mstory5(obj, (Vec *)&D_80115014_mstory5, 20);
    D_801153A0_mstory5[3].flags |= 4;
    HuPrcSleep(20);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106B48_mstory5(obj, (Vec *)&D_80114FE4_mstory5, 30);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80107080_mstory5(obj, (Vec *)&D_80114FF0_mstory5, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    HuPrcSleep(30);
    HuAudFXPlay(0x21B);
    D_80115460_mstory5.func = func_80112514_mstory5;
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_80115460_mstory5.func = func_80110200_mstory5;
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(40);
    HuAudFXPlay(0x29E);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A44 : 0x5B37);
    func_80106A50_mstory5();
    D_801153A0_mstory5[3].flags |= 0x20;
    HuPrcSleep(50);
    func_80105FDC_mstory5();
    D_801153A0_mstory5[3].func = func_80110200_mstory5;
}

void func_80112F38_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[4].obj = obj;
    D_801153A0_mstory5[4].flags = 0;
    D_801153A0_mstory5[4].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0xA00F0);
    func_8000B460_main(obj, 3, 0x1D0037);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115478_mstory5[4] = D_80114D20_mstory5[4];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[4].x, D_80115478_mstory5[4].y, D_80115478_mstory5[4].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[4].x, -5.0f, D_80115478_mstory5[4].z);
    omPrcSetDestructor(0, func_80113130_mstory5);
    D_801153A0_mstory5[4].func = func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[4].func(obj);
        HuPrcVSleep();
    }
}

void func_80113130_mstory5(void) {
}

/* actor 4's script: cued by actor 3's flags (8, 0x10, 1, 4, 0x20), then loops motion 2 */
void func_80113138_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B48_mstory5(obj, (Vec *)&D_80115038_mstory5, 40);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].flags & 8)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].flags & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, (Vec *)&D_80115074_mstory5, 40);
    while (!(D_801153A0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_80107080_mstory5(obj, (Vec *)&D_80115068_mstory5, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106B48_mstory5(obj, (Vec *)&D_80115050_mstory5, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(40);
    func_80107080_mstory5(obj, (Vec *)&D_80115074_mstory5, 10);
    while (!(D_801153A0_mstory5[3].flags & 4)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, (Vec *)&D_80115068_mstory5, 30);
    while (!(D_801153A0_mstory5[3].flags & 0x20)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
        func_80107254_mstory5(model);
    }
}

void func_80113470_mstory5(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[5].obj = obj;
    D_801153A0_mstory5[5].flags = 0;
    D_801153A0_mstory5[5].sfxOn = 0;
    src = D_801153A0_mstory5[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115478_mstory5[5] = D_80114D20_mstory5[5];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[5].x, D_80115478_mstory5[5].y, D_80115478_mstory5[5].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[5].x, -5.0f, D_80115478_mstory5[5].z);
    omPrcSetDestructor(0, func_8011396C_mstory5);
    D_801153A0_mstory5[5].func = func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[5].func(obj);
        HuPrcVSleep();
    }
}

/* actor 5's script (a copy of actor 4: it plays actor 4's motions on its linked model) */
void func_80113618_mstory5(omObjData *obj) {
    omObjData *src = D_801153A0_mstory5[4].obj;
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B48_mstory5(obj, (Vec *)&D_80115080_mstory5, 40);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].flags & 8)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[src->motion[3]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].flags & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, (Vec *)&D_801150BC_mstory5, 40);
    while (!(D_801153A0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_80107080_mstory5(obj, (Vec *)&D_801150B0_mstory5, 10);
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_80106B48_mstory5(obj, (Vec *)&D_80115098_mstory5, 10);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(40);
    func_80107080_mstory5(obj, (Vec *)&D_801150BC_mstory5, 10);
    while (!(D_801153A0_mstory5[3].flags & 4)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, (Vec *)&D_801150B0_mstory5, 30);
    while (!(D_801153A0_mstory5[3].flags & 0x20)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        func_8001C624_main(model, HmfModelData[src->motion[2]].unk02, 0, 10, 0);
        func_80107254_mstory5(model);
    }
}

void func_8011396C_mstory5(void) {
}

void func_80113974_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[6].obj = obj;
    D_801153A0_mstory5[6].flags = 0;
    D_801153A0_mstory5[6].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_80115478_mstory5[6] = D_80114D20_mstory5[6];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[6].x, D_80115478_mstory5[6].y, D_80115478_mstory5[6].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[6].x, -5.0f, D_80115478_mstory5[6].z);
    omPrcSetDestructor(0, func_80113B64_mstory5);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
    D_80114824_mstory5 = 1;
    while (TRUE) {
        D_801153A0_mstory5[6].func(obj);
        HuPrcVSleep();
    }
}

void func_80113B64_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114FC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114FD8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114FE4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114FF0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115014_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115020_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_8011502C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115038_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115050_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115068_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115074_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115080_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115098_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150B0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150BC_mstory5);

const Vec D_801150C8_mstory5 = { 250.0f, 0.0f, 150.0f };
const Vec D_801150D4_mstory5 = { 800.0f, 0.0f, 350.0f };

void func_80113B6C_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_801150F8_mstory5, 20);
    func_80106B48_mstory5(obj, (Vec *)&D_801150C8_mstory5, 20);
    while (!(D_801153A0_mstory5[3].flags & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(obj, (Vec *)&D_801150E0_mstory5, 30, 0);
    while (!(D_801153A0_mstory5[3].flags & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, (Vec *)&D_80115128_mstory5, 40);
    while (!(D_801153A0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, (Vec *)&D_801150F8_mstory5, 15);
    func_80106B64_mstory5(obj, (Vec *)&D_801150EC_mstory5, 5, 0);
    func_80107080_mstory5(obj, (Vec *)&D_80115110_mstory5, 10);
    func_80107080_mstory5(obj, (Vec *)&D_8011511C_mstory5, 10);
    func_80106B64_mstory5(obj, (Vec *)&D_801150D4_mstory5, 20, 0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
}

void func_80113CF8_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80115134_mstory5, 20);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
}

/* actor 6 bobs up and down */
/* actor 6 bobs up and down (NON_MATCHING, as mstory1's twin: one extra delay-slot nop) */
#ifdef NON_MATCHING
void func_80113D2C_mstory5(void) {
    Vec pos;
    s16 model;
    f32 t;
    f32 y;

    t = 0.0f;
    if (D_80114824_mstory5 != 0) {
        model = D_801153A0_mstory5[6].obj->model[1];
        pos.y = HmfModelData[model].pos.y;
        while (TRUE) {
            pos.x = HmfModelData[model].pos.x;
            pos.z = HmfModelData[model].pos.z;
            y = sindf(t) * 25.0f + 25.0f;
            t += 2.0f;
            t = (t >= 360.0f) ? t - 360.0f : t;
            Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
            HuPrcVSleep();
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4D8E80", func_80113D2C_mstory5);
#endif

void func_80113E58_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801153A0_mstory5[7].obj = obj;
    D_801153A0_mstory5[7].flags = 0;
    D_801153A0_mstory5[7].sfxOn = 0;
    obj->model[1] = func_8000B108_main(D_8011514C_mstory5[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115478_mstory5[7] = D_80114D20_mstory5[7];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[7].x, D_80115478_mstory5[7].y, D_80115478_mstory5[7].z);
    D_801154DA_mstory5 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_801154DA_mstory5, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_801154DA_mstory5, 60.0f);
    func_800138EC_main(D_801154DA_mstory5, 1, 0);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    omPrcSetDestructor(0, func_80114010_mstory5);
    D_801153A0_mstory5[7].func = func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[7].func(obj);
        HuPrcVSleep();
    }
}

void func_80114010_mstory5(void) {
}

void func_80114018_mstory5(omObjData *obj) {
    Vec pos;
    ObPath *path[2];
    omObjData *other;
    s32 i;
    f32 t;
    f32 rot;

    path[0] = func_8010F4D0_mstory5(D_80114828_mstory5, 0);
    path[1] = func_8010F4D0_mstory5(D_80114858_mstory5, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_801154DA_mstory5, 4, 0);
    func_800138EC_main(D_801154DA_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    i = 0;
    do {
        t = i * 0.02f;
        func_8010F7D4_mstory5(path[0], t * t, &pos);
        i++;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_801154DA_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 50);
    HuPrcSleep(40);
    other = D_801153A0_mstory5[6].obj;
    func_8001C624_main(other->model[1], HmfModelData[other->motion[2]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_801153A0_mstory5[7].flags |= 2;
    HuAudFXPlay(0x218);
    func_8001C624_main(other->model[1], HmfModelData[other->motion[0]].unk02, 0, 10, 2);
    rot = 0.0f;
    i = 0;
    do {
        t = i * (1.0f / 120.0f);
        func_8010F7D4_mstory5(path[1], t * t, &pos);
        rot -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        i++;
        Hu3DModelRotSet(obj->model[1], 0.0f, rot, 0.0f);
        func_8000CFA4_main(D_801154DA_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 120);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    HuAudFXPlay(0x21A);
    func_8011007C_mstory5(path[0]);
    func_8011007C_mstory5(path[1]);
    D_801153A0_mstory5[7].flags = 1;
    D_801153A0_mstory5[7].func = func_80110200_mstory5;
}

void func_80114334_mstory5(omObjData *a, omObjData *b) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150EC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150F8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115110_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_8011511C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115128_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115134_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_8011514C_mstory5);

void func_8011447C_mstory5(u32 actor, s32 fx) {

    if (D_801153A0_mstory5[actor].sfxOn == 0) {
        D_801153A0_mstory5[actor].sfxOn = 1;
        D_801153A0_mstory5[actor].sfxId = fx;
        switch (actor) {
        case 0:
            D_801153A0_mstory5[actor].sfxNo = CharFXPlay(fx, GwStory.unk1);
            break;
        case 2:
            if (func_80106B30_mstory5(2) == 0) {
                D_801153A0_mstory5[actor].sfxNo = CharFXPlay(fx, 2);
            } else {
                D_801153A0_mstory5[actor].sfxNo = CharFXPlay(fx, 1);
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

void func_80114560_mstory5(u32 actor) {
    if (D_801153A0_mstory5[actor].sfxOn == 1) {
        D_801153A0_mstory5[actor].sfxOn = 0;
        switch (actor) {
        case 0:
        case 2:
            HuAudFXStop((s16)D_801153A0_mstory5[actor].sfxNo);
            break;
        case 1:
        case 3:
        case 4:
        case 5:
            break;
        }
    }
}

void func_801145DC_mstory5(void) {
    s32 i;
    s32 fx;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (D_801153A0_mstory5[i].sfxOn == 1 && HmfModelData[D_801153A0_mstory5[i].obj->model[1]].unk40 == 0.0f) {
                fx = D_801153A0_mstory5[i].sfxId;
                switch ((u32)i) {
                case 0:
                    D_801153A0_mstory5[i].sfxNo = CharFXPlay(fx, GwStory.unk1);
                    break;
                case 2:
                    if (func_80106B30_mstory5(2) == 0) {
                        D_801153A0_mstory5[i].sfxNo = CharFXPlay(fx, 2);
                    } else {
                        D_801153A0_mstory5[i].sfxNo = CharFXPlay(fx, 1);
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

/* retail pads this file's .rodata to 16 bytes after func_801145DC_mstory5's jump table */
const s32 D_801151A8_mstory5[2] = { 0, 0 };
