#include "common.h"

/* a story-scene actor: its object and the action its process runs every frame */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_80109478_mstory1);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_80109C28_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_80109DC0_mstory1);

void func_80109FD0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80114F30_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_80109FD8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010A424_mstory1);

void func_8010A608_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010A610_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010AA98_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010AC40_mstory1);

void func_8010B108_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010B110_mstory1);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010B308_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010B384_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010B3B8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010B4E4_mstory1);

void func_8010B69C_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010B6A4_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010B9C0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80115038_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_80115050_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48D950", D_8011505C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010BB08_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010BBEC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48D950", func_8010BC68_mstory1);
