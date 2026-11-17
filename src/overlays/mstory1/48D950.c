#include "common.h"

extern const Vec D_80114E64_mstory1;
extern const Vec D_80114E7C_mstory1;
extern const Vec D_80114E94_mstory1;
extern const Vec D_80114EA0_mstory1;
extern const Vec D_80114EAC_mstory1;
extern const Vec D_80114EB8_mstory1;
extern const Vec D_80114EC4_mstory1;
extern const Vec D_80114ED0_mstory1;
extern const Vec D_80114EDC_mstory1;
extern const Vec D_80114EE8_mstory1;
void func_801085F8_mstory1(omObjData *obj);
void func_8010B6A4_mstory1(omObjData *obj);
void func_8010B384_mstory1(omObjData *obj);

extern Vec D_80114AC4_mstory1[]; /* paths: Vec lists ended by { 9999, 9999, 9999 } */
extern Vec D_80114AF4_mstory1[];

void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_80109478_mstory1(omObjData *obj);
void func_80109FD0_mstory1(void);
void func_8010A608_mstory1(void);
void func_8010B108_mstory1(void);
void func_8010B300_mstory1(void);
void func_8010B69C_mstory1(void);
void func_8010BB08_mstory1(u32 actor, s32 fx);
void func_8010BBEC_mstory1(u32 actor);
extern s32 D_80114AC0_mstory1; /* 1 once actor 6 exists: actor 6 bobs */
extern s16 D_80115A12_mstory1; /* effect model */
extern const s32 D_8011505C_mstory1[7];
extern const Vec D_80115038_mstory1;
extern const Vec D_80115050_mstory1;

/* a story-scene actor: its object and the action its process runs every frame */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10; /* looping sound effect */
    /* 0x14 */ s32 unk14; /* its handle */
} StoryActor; /* size = 0x18 */

extern StoryActor D_801158F0_mstory1[8];
extern Vec D_801159B0_mstory1[8]; /* actor positions */
extern s16 D_80115A10_mstory1; /* shadow model, linked by every actor */
extern s16 D_80115A14_mstory1[4];
extern s32 D_80115A1C_mstory1[3]; /* texture animations */
extern s16 D_80115A28_mstory1;
extern const Vec D_80114CB0_mstory1[8]; /* actor start positions */
extern const s32 D_80114D10_mstory1[8];
extern const s32 D_80114D30_mstory1[8];
extern const s32 D_80114D50_mstory1[8];
extern const s32 D_80114D70_mstory1[8];
extern const Vec D_80114E40_mstory1;
extern const Vec D_80114E4C_mstory1;
extern const Vec D_80114F00_mstory1;
extern const Vec D_80114F0C_mstory1;
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_80032FC0_main(s16, s32, s32);
s16 func_800329B4_main(void *);
void func_80106984_mstory1(void);
void func_801068B0_mstory1(s16 model, s16 anim, s16 frame);
void func_801069EC_mstory1(void);
void func_80106A1C_mstory1(void);
void func_80106A40_mstory1(s32 mess);
void func_80106A94_mstory1(s32 mess);
void func_80106AC0_mstory1(void);
s32 func_80106AFC_mstory1(s32 chr);
void func_80105EC0_mstory1(void);
void func_80105EF4_mstory1(void);
void func_80105FA8_mstory1(void);
void func_80105FB8_mstory1(s32 arg0);
s32 func_80106894_mstory1(void);
void func_80106F94_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80106FC0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn);
void func_80106FF0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_8010701C_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn);
void func_801071F4_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107220_mstory1(s16 model);
void func_80107318_mstory1(omObjData *obj, f32 speed, s16 frames);
void func_801081D8_mstory1(omObjData *obj);
void func_801081E0_mstory1(void);
void func_801085F0_mstory1(void);
void func_80109140_mstory1(void);
void func_80109470_mstory1(void);
void func_801099F8_mstory1(void);
void func_80109C20_mstory1(void);
void func_80109C28_mstory1(omObjData *obj);
void func_80109DC0_mstory1(void);
void func_8010A424_mstory1(void);
void func_8010AA98_mstory1(void);
void func_8010B110_mstory1(void);
void func_8010B3B8_mstory1(void);
void func_8010B4E4_mstory1(void);
void func_8010BC68_mstory1(void);
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

ObPath *func_801074C0_mstory1(Vec *points, s16 flags);
void func_801077C4_mstory1(ObPath *path, f32 t, Vec *out);
void func_8010806C_mstory1(ObPath *path);

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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_801077C4_mstory1);
#endif

void func_8010806C_mstory1(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* chapter 1, first scene: the actors' processes */
void func_8010809C_mstory1(void) {
    func_80106984_mstory1();
    D_80115A10_mstory1 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_801081E0_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109140_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_801099F8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109DC0_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A424_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010AA98_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010B110_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010B3B8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010B4E4_mstory1, 0x384, 0x800, 0);
    omAddPrcObj(func_8010BC68_mstory1, 0x384, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115A10_mstory1, 4, 4);
}

void func_801081D8_mstory1(omObjData *obj) {
}

// masked 0 when func_80017AD8_main returns s16 (functions.us.h says u8: an andi 0xFF per call; s1A.header.patch)
#ifdef NON_MATCHING
/* actor 0: the player's character */
void func_801081E0_mstory1(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 6, 0x10, -1, NULL);
    D_801158F0_mstory1[0].obj = obj;
    D_801158F0_mstory1[0].unk08 = 0;
    D_801158F0_mstory1[0].unk0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
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
    func_8000B460_main(obj, 5, D_80114D10_mstory1[chr]);
    func_8000B460_main(obj, 6, D_80114D30_mstory1[chr]);
    func_8000B460_main(obj, 7, D_80114D50_mstory1[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_80114D70_mstory1[chr]);
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x9B));
    D_80115A14_mstory1[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80115A14_mstory1[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80115A14_mstory1[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80115A14_mstory1[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115A14_mstory1[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_801159B0_mstory1[0] = D_80114CB0_mstory1[0];
    Hu3DModelPosSet(obj->model[1], D_801159B0_mstory1[0].x, D_801159B0_mstory1[0].y, D_801159B0_mstory1[0].z);
    Hu3DModelPosSet(obj->model[2], D_801159B0_mstory1[0].x, -5.0f, D_801159B0_mstory1[0].z);
    Hu3DModelPosSet(obj->model[4], D_801159B0_mstory1[0].x, D_801159B0_mstory1[0].y, D_801159B0_mstory1[0].z);
    omPrcSetDestructor(0, func_801085F0_mstory1);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
    while (TRUE) {
        D_801158F0_mstory1[0].func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_801081E0_mstory1);
#endif

void func_801085F0_mstory1(void) {
}



INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114CB0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114CBC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114CC8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114CD4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114CE0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114CEC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114CF8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114D04_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114D10_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114D30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114D50_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114D70_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114D90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114D9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114DA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114DCC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_801085F8_mstory1);

void func_80109014_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C624_main(model, HmfModelData[obj->motion[9]].unk02, 0, 10, 0);
    func_80107220_mstory1(model);
    HuPrcSleep(80);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
}

void func_801090D8_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)&D_80114E40_mstory1, 10);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
}

void func_8010910C_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)&D_80114E4C_mstory1, 10);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114DFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E08_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E14_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E20_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E38_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E40_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E4C_mstory1);

/* actor 1 */
void func_80109140_mstory1(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[1].obj = obj;
    D_801158F0_mstory1[1].unk08 = 0;
    D_801158F0_mstory1[1].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_801159B0_mstory1[1] = D_80114CB0_mstory1[1];
    Hu3DModelPosSet(obj->model[1], D_801159B0_mstory1[1].x, D_801159B0_mstory1[1].y, D_801159B0_mstory1[1].z);
    Hu3DModelPosSet(obj->model[2], D_801159B0_mstory1[1].x, -5.0f, D_801159B0_mstory1[1].z);
    data = DataRead(0xA007E);
    D_80115A1C_mstory1[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main((s16)D_80115A1C_mstory1[0], 1, 0);
    func_80032FF8_main((s16)D_80115A1C_mstory1[0], 0);
    D_80115A28_mstory1 = func_80032694_main(HmfModelData[obj->model[1]].hmf, (s16)D_80115A1C_mstory1[0], 0, "c204n_0_DEF");
    D_80115A1C_mstory1[0] = D_800D1714_main[D_80115A1C_mstory1[0]].unk_00;
    data = DataRead(0xA0080);
    D_80115A1C_mstory1[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80115A1C_mstory1[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068B0_mstory1(obj->model[1], D_80115A28_mstory1, (s16)D_80115A1C_mstory1[0]);
    omPrcSetDestructor(0, func_80109470_mstory1);
    D_801158F0_mstory1[1].func = func_801081D8_mstory1;
    while (TRUE) {
        D_801158F0_mstory1[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80109470_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E64_mstory1);

const Vec D_80114E70_mstory1 = { 10.0f, 378.9f, 0.0f };

/* actor 1's scene: it meets actor 2 (or the player, when that is character 4) and actor 7
   takes off */
void func_80109478_mstory1(omObjData *obj) {
    D_801158F0_mstory1[0].func = func_80109014_mstory1;
    D_801158F0_mstory1[6].func = func_8010B384_mstory1;
    func_8010704C_mstory1(obj, (Vec *)&D_80114E70_mstory1, 30);
    func_80106B14_mstory1(obj, (Vec *)&D_80114ED0_mstory1, 20);
    HuPrcSleep(30);
    func_8010704C_mstory1(obj, (Vec *)&D_80114EA0_mstory1, 10);
    func_80106B14_mstory1(obj, (Vec *)&D_80114EC4_mstory1, 15);
    D_801158F0_mstory1[0].func = func_801090D8_mstory1;
    if (func_80106AFC_mstory1(4) == 0) {
        func_801071F4_mstory1(D_801158F0_mstory1[0].obj, 0.0f, 162.4744f, 0.0f, 10);
        func_8010704C_mstory1(obj, (Vec *)&D_80114E7C_mstory1, 15);
        HuPrcSleep(20);
        func_8010704C_mstory1(obj, (Vec *)&D_80114E94_mstory1, 10);
        func_8010704C_mstory1(D_801158F0_mstory1[6].obj, (Vec *)&D_80114EDC_mstory1, 10);
    } else {
        func_8010704C_mstory1(obj, (Vec *)&D_80114E7C_mstory1, 10);
        func_801068B0_mstory1(obj->model[1], D_80115A28_mstory1, (s16)D_80115A1C_mstory1[1]);
        func_801069EC_mstory1();
        func_80106A40_mstory1(0x5B04);
        func_80106A1C_mstory1();
        func_801068B0_mstory1(obj->model[1], D_80115A28_mstory1, (s16)D_80115A1C_mstory1[0]);
        func_801071F4_mstory1(D_801158F0_mstory1[0].obj, 0.0f, 162.4744f, 0.0f, 10);
        func_8010704C_mstory1(D_801158F0_mstory1[6].obj, (Vec *)&D_80114EDC_mstory1, 10);
        func_8010704C_mstory1(obj, (Vec *)&D_80114E94_mstory1, 20);
    }
    HuAudFXPlay(0x159);
    func_8001C624_main(D_801158F0_mstory1[6].obj->model[1], HmfModelData[D_801158F0_mstory1[6].obj->motion[1]].unk02, 0, 10, 2);
    func_801069EC_mstory1();
    func_80106A40_mstory1((func_80106AFC_mstory1(4) == 0) ? 0x5A15 : 0x5B05);
    func_80106A1C_mstory1();
    func_8001C624_main(D_801158F0_mstory1[6].obj->model[1], HmfModelData[D_801158F0_mstory1[6].obj->motion[0]].unk02, 0, 10, 2);
    func_8010704C_mstory1(D_801158F0_mstory1[6].obj, (Vec *)&D_80114EE8_mstory1, 10);
    D_801158F0_mstory1[7].func = func_8010B6A4_mstory1;
    func_8010704C_mstory1(obj, (Vec *)&D_80114E64_mstory1, 20);
    func_8001C624_main(D_801158F0_mstory1[0].obj->model[1], HmfModelData[D_801158F0_mstory1[0].obj->motion[10]].unk02, 0, 10, 2);
    while (!(D_801158F0_mstory1[7].unk08 & 2)) {
        HuPrcVSleep();
    }
    D_801158F0_mstory1[0].func = func_801085F8_mstory1;
    HuPrcSleep(40);
    func_8010704C_mstory1(obj, (Vec *)&D_80114EB8_mstory1, 50);
    func_8010704C_mstory1(obj, (Vec *)&D_80114EAC_mstory1, 40);
    D_801158F0_mstory1[1].func = func_801081D8_mstory1;
}

void func_8010980C_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)&D_80114F0C_mstory1, 10);
    func_80106B14_mstory1(obj, (Vec *)&D_80114F00_mstory1, 50);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801158F0_mstory1[1].func = func_801081D8_mstory1;
}

/* actor 1 hops */
void func_80109888_mstory1(omObjData *obj) {
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
    func_801068B0_mstory1(obj->model[1], D_80115A28_mstory1, (s16)D_80115A1C_mstory1[2]);
    D_801158F0_mstory1[1].func = func_801081D8_mstory1;
}

/* actor 2 */
void func_801099F8_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[2].obj = obj;
    D_801158F0_mstory1[2].unk08 = 0;
    D_801158F0_mstory1[2].unk0C = 0;
    if (func_80106AFC_mstory1(4) == 0) {
        obj->model[1] = func_8000B108_main(0x500A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
        func_8000B460_main(obj, 0, 0x50000);
        func_8000B460_main(obj, 1, 0x1D0063);
        func_8000B460_main(obj, 2, 0x1D0064);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
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
    D_801159B0_mstory1[2] = D_80114CB0_mstory1[2];
    Hu3DModelPosSet(obj->model[1], D_801159B0_mstory1[2].x, D_801159B0_mstory1[2].y, D_801159B0_mstory1[2].z);
    Hu3DModelPosSet(obj->model[2], D_801159B0_mstory1[2].x, -5.0f, D_801159B0_mstory1[2].z);
    omPrcSetDestructor(0, func_80109C20_mstory1);
    D_801158F0_mstory1[2].func = func_80109C28_mstory1;
    while (TRUE) {
        D_801158F0_mstory1[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80109C20_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E7C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114E94_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114EA0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114EAC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114EB8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114EC4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114ED0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114EDC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114EE8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F00_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F0C_mstory1);

const Vec D_80114F24_mstory1 = { 200.0f, 0.0f, 1200.0f };

/* actor 2's first action */
void func_80109C28_mstory1(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106AFC_mstory1(4) == 0) {
        CharFXPlay(0x26B, 4);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    if (func_80106AFC_mstory1(4) == 0) {
        func_801068B0_mstory1(D_801158F0_mstory1[1].obj->model[1], D_80115A28_mstory1, (s16)D_80115A1C_mstory1[1]);
        func_801069EC_mstory1();
        func_80106A40_mstory1(0x5A14);
        func_80106A1C_mstory1();
        func_801068B0_mstory1(D_801158F0_mstory1[1].obj->model[1], D_80115A28_mstory1, (s16)D_80115A1C_mstory1[0]);
    }
    D_801158F0_mstory1[1].func = func_80109478_mstory1;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    if (func_80106AFC_mstory1(4) == 0) {
        CharFXPlay(0x286, 4);
    } else {
        CharFXPlay(0x286, 1);
    }
    func_8010BB08_mstory1(2, 0x28);
    func_80106B14_mstory1(obj, (Vec *)&D_80114F24_mstory1, 0x28);
    func_8010BBEC_mstory1(2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801158F0_mstory1[2].func = func_801081D8_mstory1;
}

/* actor 3 */
void func_80109DC0_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[3].obj = obj;
    D_801158F0_mstory1[3].unk08 = 0;
    D_801158F0_mstory1[3].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
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
    D_801159B0_mstory1[3] = D_80114CB0_mstory1[3];
    Hu3DModelPosSet(obj->model[1], D_801159B0_mstory1[3].x, D_801159B0_mstory1[3].y, D_801159B0_mstory1[3].z);
    Hu3DModelPosSet(obj->model[2], D_801159B0_mstory1[3].x, -5.0f, D_801159B0_mstory1[3].z);
    omPrcSetDestructor(0, func_80109FD0_mstory1);
    D_801158F0_mstory1[3].func = func_801081D8_mstory1;
    while (TRUE) {
        D_801158F0_mstory1[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80109FD0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F30_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_80109FD8_mstory1);

/* actor 4 */
void func_8010A424_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[4].obj = obj;
    D_801158F0_mstory1[4].unk08 = 0;
    D_801158F0_mstory1[4].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
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
    D_801159B0_mstory1[4] = D_80114CB0_mstory1[4];
    Hu3DModelPosSet(obj->model[1], D_801159B0_mstory1[4].x, D_801159B0_mstory1[4].y, D_801159B0_mstory1[4].z);
    Hu3DModelPosSet(obj->model[2], D_801159B0_mstory1[4].x, -5.0f, D_801159B0_mstory1[4].z);
    omPrcSetDestructor(0, func_8010A608_mstory1);
    D_801158F0_mstory1[4].func = func_801081D8_mstory1;
    while (TRUE) {
        D_801158F0_mstory1[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A608_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010A610_mstory1);

/* actor 5: a copy of actor 4's model */
void func_8010AA98_mstory1(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[5].obj = obj;
    D_801158F0_mstory1[5].unk08 = 0;
    D_801158F0_mstory1[5].unk0C = 0;
    src = D_801158F0_mstory1[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801159B0_mstory1[5] = D_80114CB0_mstory1[5];
    Hu3DModelPosSet(obj->model[1], D_801159B0_mstory1[5].x, D_801159B0_mstory1[5].y, D_801159B0_mstory1[5].z);
    Hu3DModelPosSet(obj->model[2], D_801159B0_mstory1[5].x, -5.0f, D_801159B0_mstory1[5].z);
    omPrcSetDestructor(0, func_8010B108_mstory1);
    D_801158F0_mstory1[5].func = func_801081D8_mstory1;
    while (TRUE) {
        D_801158F0_mstory1[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010AC40_mstory1);

void func_8010B108_mstory1(void) {
}

/* actor 6 */
void func_8010B110_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[6].obj = obj;
    D_801158F0_mstory1[6].unk08 = 0;
    D_801158F0_mstory1[6].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_801159B0_mstory1[6] = D_80114CB0_mstory1[6];
    Hu3DModelPosSet(obj->model[1], D_801159B0_mstory1[6].x, D_801159B0_mstory1[6].y, D_801159B0_mstory1[6].z);
    Hu3DModelPosSet(obj->model[2], D_801159B0_mstory1[6].x, -5.0f, D_801159B0_mstory1[6].z);
    omPrcSetDestructor(0, func_8010B300_mstory1);
    D_801158F0_mstory1[6].func = func_801081D8_mstory1;
    D_80114AC0_mstory1 = 1;
    while (TRUE) {
        D_801158F0_mstory1[6].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B300_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F48_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F54_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F78_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F84_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114FA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114FB4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114FC0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114FCC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114FD8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114FE4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114FF0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114FFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80115008_mstory1);

const Vec D_80115020_mstory1[2] = { { 700.0f, 0.0f, 150.0f }, { 216.66666f, 0.0f, 150.0f } };

void func_8010B308_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)&D_80115038_mstory1, 10);
    func_80106B14_mstory1(obj, (Vec *)&D_80115020_mstory1[0], 50);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801158F0_mstory1[6].func = func_801081D8_mstory1;
}

void func_8010B384_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, (Vec *)&D_80115050_mstory1, 20);
    D_801158F0_mstory1[6].func = func_801081D8_mstory1;
}

// an extra nop after the sindf call (masked 3)
#ifdef NON_MATCHING
/* actor 6 bobs up and down */
void func_8010B3B8_mstory1(void) {
    Vec pos;
    s16 model;
    f32 t;
    f32 y;

    t = 0.0f;
    if (D_80114AC0_mstory1 != 0) {
        model = D_801158F0_mstory1[6].obj->model[1];
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010B3B8_mstory1);
#endif

/* actor 7 and the effect */
void func_8010B4E4_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801158F0_mstory1[7].obj = obj;
    D_801158F0_mstory1[7].unk08 = 0;
    D_801158F0_mstory1[7].unk0C = 0;
    obj->model[1] = func_8000B108_main(D_8011505C_mstory1[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_801159B0_mstory1[7] = D_80114CB0_mstory1[7];
    Hu3DModelPosSet(obj->model[1], D_801159B0_mstory1[7].x, D_801159B0_mstory1[7].y, D_801159B0_mstory1[7].z);
    D_80115A12_mstory1 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80115A12_mstory1, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_80115A12_mstory1, 60.0f);
    func_800138EC_main(D_80115A12_mstory1, 1, 0);
    func_8001C258_main(D_80115A12_mstory1, 4, 4);
    omPrcSetDestructor(0, func_8010B69C_mstory1);
    D_801158F0_mstory1[7].func = func_801081D8_mstory1;
    while (TRUE) {
        D_801158F0_mstory1[7].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B69C_mstory1(void) {
}

/* actor 7's flight: along the first path, then (after actor 6 reacts) spinning along the second */
void func_8010B6A4_mstory1(omObjData *obj) {
    Vec pos;
    ObPath *path[2];
    omObjData *other;
    s32 i;
    f32 t;
    f32 rot;

    path[0] = func_801074C0_mstory1(D_80114AC4_mstory1, 0);
    path[1] = func_801074C0_mstory1(D_80114AF4_mstory1, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_80115A12_mstory1, 4, 0);
    func_800138EC_main(D_80115A12_mstory1, 1, 1);
    HuAudFXPlay(0x215);
    i = 0;
    do {
        t = i * 0.02f;
        func_801077C4_mstory1(path[0], t * t, &pos);
        i++;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115A12_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 50);
    HuPrcSleep(40);
    other = D_801158F0_mstory1[6].obj;
    func_8001C624_main(other->model[1], HmfModelData[other->motion[2]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_801158F0_mstory1[7].unk08 |= 2;
    HuAudFXPlay(0x218);
    func_8001C624_main(other->model[1], HmfModelData[other->motion[0]].unk02, 0, 10, 2);
    rot = 0.0f;
    i = 0;
    do {
        t = i * (1.0f / 120.0f);
        func_801077C4_mstory1(path[1], t * t, &pos);
        rot -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        i++;
        Hu3DModelRotSet(obj->model[1], 0.0f, rot, 0.0f);
        func_8000CFA4_main(D_80115A12_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 120);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_80115A12_mstory1, 4, 4);
    HuAudFXPlay(0x21A);
    func_8010806C_mstory1(path[0]);
    func_8010806C_mstory1(path[1]);
    D_801158F0_mstory1[7].unk08 = 1;
    D_801158F0_mstory1[7].func = func_801081D8_mstory1;
}

/* turns a's model to face b's */
void func_8010B9C0_mstory1(omObjData *a, omObjData *b) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80115038_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80115050_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_8011505C_mstory1);

/* starts actor's looping sound effect (replayed by func_8010BC68_mstory1 each motion loop) */
void func_8010BB08_mstory1(u32 actor, s32 fx) {

    if (D_801158F0_mstory1[actor].unk0C == 0) {
        D_801158F0_mstory1[actor].unk0C = 1;
        D_801158F0_mstory1[actor].unk10 = fx;
        switch (actor) {
        case 0:
            D_801158F0_mstory1[actor].unk14 = CharFXPlay(fx, GwStory.unk1);
            break;
        case 2:
            if (func_80106AFC_mstory1(4) == 0) {
                D_801158F0_mstory1[actor].unk14 = CharFXPlay(fx, 4);
            } else {
                D_801158F0_mstory1[actor].unk14 = CharFXPlay(fx, 1);
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

void func_8010BBEC_mstory1(u32 actor) {
    if (D_801158F0_mstory1[actor].unk0C == 1) {
        D_801158F0_mstory1[actor].unk0C = 0;
        switch (actor) {
        case 0:
        case 2:
            HuAudFXStop((s16)D_801158F0_mstory1[actor].unk14);
            break;
        case 1:
        case 3:
        case 4:
        case 5:
            break;
        }
    }
}

/* replays each actor's looping sound effect when its motion starts over */
void func_8010BC68_mstory1(void) {
    s32 i;
    s32 fx;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (D_801158F0_mstory1[i].unk0C == 1 && HmfModelData[D_801158F0_mstory1[i].obj->model[1]].unk40 == 0.0f) {
                fx = D_801158F0_mstory1[i].unk10;
                switch ((u32)i) {
                case 0:
                    D_801158F0_mstory1[i].unk14 = CharFXPlay(fx, GwStory.unk1);
                    break;
                case 2:
                    if (func_80106AFC_mstory1(4) == 0) {
                        D_801158F0_mstory1[i].unk14 = CharFXPlay(fx, 4);
                    } else {
                        D_801158F0_mstory1[i].unk14 = CharFXPlay(fx, 1);
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
