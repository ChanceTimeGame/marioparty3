#include "common.h"

// story v1
/* a story-scene actor: its object and the action its process runs every frame */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C; /* 1 while its looping sound effect plays */
    /* 0x10 */ s32 unk10; /* looping sound effect (the actor's voice) */
    /* 0x14 */ s32 unk14; /* its handle (actor 0's playing voice; HuAudFXStop takes its low half) */
} StoryActor; /* size = 0x18 */

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

#include "mallocblock.h"

extern TexAnimSlot *D_800D1714_main;
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);

extern StoryActor D_801121C0_mstory4[];
extern s32 D_80112238_mstory4[4]; /* texture animations */
extern s16 D_80112248_mstory4;

extern void (*const D_80111C10_mstory4[2])(void);
extern const Vec D_80111DB8_mstory4;
extern const Vec D_80111DC4_mstory4;
extern const Vec D_80111E78_mstory4;
extern const Vec D_80111E84_mstory4;

void func_80106DBC_mstory4(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106DA0_mstory4(omObjData *obj, Vec *to, s32 frames);
void func_801072D8_mstory4(omObjData *obj, Vec *to, s32 frames);
void func_801074AC_mstory4(s16 model);
void func_80106B3C_mstory4(s16 model, s16 anim, s16 frame);
void func_8010818C_mstory4(void);
void func_80108280_mstory4(omObjData *obj);
void func_80106C10_mstory4(void);
void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80108288_mstory4(void);
void func_801094DC_mstory4(void);
void func_80109B5C_mstory4(omObjData *obj);
void func_80109EA4_mstory4(void);
void func_8010A1C4_mstory4(void);
void func_8010A480_mstory4(void);
void func_8010A5AC_mstory4(void);
void func_8010ACF4_mstory4(void);
extern s16 D_8011228C_mstory4; /* shadow model, linked by every actor */
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_801086EC_mstory4(void);
extern Vec D_80112250_mstory4[]; /* actor positions */
extern s16 D_80112290_mstory4[4];
extern const Vec D_80111C70_mstory4[]; /* actor start positions */
extern const s32 D_80111CAC_mstory4[8];
extern const s32 D_80111CCC_mstory4[8];
extern const s32 D_80111CEC_mstory4[8];
extern const s32 D_80111D0C_mstory4[8];
void func_80109838_mstory4(void);
void func_80032FC0_main(s16, s32, s32);
s16 func_800329B4_main(void *);
void func_801093B0_mstory4(omObjData *obj);
void func_801086F4_mstory4(omObjData *obj);
void func_8010A44C_mstory4(omObjData *obj);
void func_8010A76C_mstory4(omObjData *obj);
void func_80106C78_mstory4(void);
void func_80106CA8_mstory4(void);
void func_80106CCC_mstory4(s32 mess);
extern const Vec D_80111DDC_mstory4;
extern const Vec D_80111DF4_mstory4;
extern const Vec D_80111E0C_mstory4;
extern const Vec D_80111E18_mstory4;
extern const Vec D_80111E24_mstory4;
extern const Vec D_80111E30_mstory4;
extern const Vec D_80111E3C_mstory4;
extern const Vec D_80111E48_mstory4;
extern const Vec D_80111E54_mstory4;
extern const Vec D_80111E60_mstory4;
void func_8010A05C_mstory4(void);
void func_8010A064_mstory4(omObjData *obj);
void func_80109840_mstory4(omObjData *obj);
void func_8010ABD0_mstory4(s32 actor, s32 fx);
void func_8010AC84_mstory4(s32 actor);
/* a joint of a model, as func_8001D33C_main finds it by name */
typedef struct MsPart {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ f32 unk10; /* turned with unk34 */
    /* 0x14 */ f32 rotY;
    /* 0x18 */ char unk18[4];
    /* 0x1C */ Vec scale;
    /* 0x28 */ char unk28[0xC];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ char unk38[4];
    /* 0x3C */ f32 unk3C; /* set with rotY */
    /* 0x40 */ Vec scale2;
} MsPart;
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);
void *func_8001D33C_main(s16, const char *);
void func_801060E8_mstory4(void);
void func_801060F8_mstory4(s32 arg0);
s32 func_80106B20_mstory4(void);
void func_80109CCC_mstory4(omObjData *obj);
void func_80109E3C_mstory4(omObjData *obj);
void func_80109E68_mstory4(omObjData *obj);
extern s16 D_8011228E_mstory4;

// story v2

/* scene 1: five actors */
extern s32 D_80111B00_mstory4; /* 1 once actor 3 exists: actor 3 bobs */
extern Vec D_80111B04_mstory4[]; /* paths: Vec lists ended by { 9999, 9999, 9999 } */
extern Vec D_80111B34_mstory4[];
extern const Vec D_80111ECC_mstory4;
extern const Vec D_80111EE4_mstory4;
extern const s32 D_80111F08_mstory4[];
ObPath *func_801075B0_mstory4(Vec *points, s16 flags);
void func_801078B4_mstory4(ObPath *path, f32 t, Vec *out);
void func_8010815C_mstory4(ObPath *path);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_8010A3C8_mstory4(void);
void func_8010A764_mstory4(void);

ObPath *func_801075B0_mstory4(Vec *points, s16 flags) {
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
void func_801078B4_mstory4(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C47E0", func_801078B4_mstory4);
#endif

void func_8010815C_mstory4(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* story step 0 of chapter 4: the scene's actor processes */
void func_8010818C_mstory4(void) {
    func_80106C10_mstory4();
    D_8011228C_mstory4 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80108288_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_801094DC_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109EA4_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A1C4_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A480_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A5AC_mstory4, 0x384, 0x800, 0);
    omAddPrcObj(func_8010ACF4_mstory4, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_8011228C_mstory4, 4, 4);
}

void func_80108280_mstory4(omObjData *obj) {
}

void func_80108288_mstory4(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 6, 0x10, -1, NULL);
    D_801121C0_mstory4[0].obj = obj;
    D_801121C0_mstory4[0].unk08 = 0;
    D_801121C0_mstory4[0].unk0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
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
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x30));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 6, D_80111CAC_mstory4[chr]);
    func_8000B460_main(obj, 7, D_80111CCC_mstory4[chr]);
    func_8000B460_main(obj, 8, D_80111CEC_mstory4[chr]);
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 10, D_80111D0C_mstory4[chr]);
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 0x2C));
    func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x7A));
    func_8000B460_main(obj, 13, func_80017BB8_main(chr, 0x9B));
    D_80112290_mstory4[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80112290_mstory4[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80112290_mstory4[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80112290_mstory4[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_80112250_mstory4[0] = D_80111C70_mstory4[0];
    Hu3DModelPosSet(obj->model[1], D_80112250_mstory4[0].x, D_80112250_mstory4[0].y, D_80112250_mstory4[0].z);
    Hu3DModelPosSet(obj->model[2], D_80112250_mstory4[0].x, -5.0f, D_80112250_mstory4[0].z);
    Hu3DModelPosSet(obj->model[4], D_80112250_mstory4[0].x, D_80112250_mstory4[0].y, D_80112250_mstory4[0].z);
    omPrcSetDestructor(0, func_801086EC_mstory4);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[0].func(obj);
        HuPrcVSleep();
    }
}

void func_801086EC_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111C70_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111C7C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111C88_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111C94_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111CA0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111CAC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111CCC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111CEC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111D0C_mstory4);

const Vec D_80111D2C_mstory4 = { 0.0f, 0.0f, 0.0f };
const Vec D_80111D38_mstory4 = { 0.0f, 180.0f, 0.0f };
const Vec D_80111D44_mstory4 = { 0.0f, 90.0f, 0.0f }; /* unused */
const Vec D_80111D50_mstory4 = { 0.0f, -90.0f, 0.0f }; /* unused */
const Vec D_80111D5C_mstory4 = { -100.0f, 0.0f, 350.0f };
const Vec D_80111D68_mstory4 = { -100.0f, 0.0f, 150.0f };
const Vec D_80111D74_mstory4 = { 0.0f, 20.0f, 0.0f };
const Vec D_80111D80_mstory4 = { 0.0f, 0.0f, 0.0f };
const Vec D_80111D8C_mstory4 = { 0.0f, -26.565f, 0.0f };

/* actor 0's scene: the item hook, then the talk with actors 1 and 3 */
void func_801086F4_mstory4(omObjData *obj) {
    MsPart *part;
    omObjData *actor1;
    omObjData *actor3;
    s32 i;
    f32 scale;
    f32 frame;
    s16 model;

    HuPrcSleep(20);
    actor1 = D_801121C0_mstory4[1].obj;
    actor3 = D_801121C0_mstory4[3].obj;
    model = obj->model[1];
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107480_mstory4(obj, 0.0f, 110.0f, 0.0f, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[7]].unk02, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], model, "item_hook");
    func_8001C258_main(obj->model[3], 4, 0);
    func_801074AC_mstory4(model);
    func_8001C624_main(model, HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    func_801074AC_mstory4(model);
    while (!(D_801121C0_mstory4[4].unk08 & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_801121C0_mstory4[4].obj->model[1], 4, 4);
    func_8001C258_main(D_8011228E_mstory4, 4, 4);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x45);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x46);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x47);
    part = func_8001D33C_main(model, "item_hook");
    i = 0;
    do {
        scale = sindf(i * 18.0f) * 0.8 + 1.0;
        part->scale.x = scale;
        part->scale.y = scale;
        part->scale.z = scale;
        part->scale2.x = scale;
        part->scale2.y = scale;
        part->scale2.z = scale;
        HuPrcVSleep();
        i++;
    } while (i < 10);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x47);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x46);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x45);
    func_801060F8_mstory4(6);
    while (func_80106B20_mstory4() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A72);
    func_80106CA8_mstory4();
    func_80106B3C_mstory4(actor1->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[3]);
    D_801121C0_mstory4[1].func = func_80109CCC_mstory4;
    HuPrcSleep(12);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A73);
    func_80106CA8_mstory4();
    func_8001C5B4_main(model, obj->motion[6]);
    func_8001C814_main(model, 4, 4);
    func_8001C92C_main(model, 2.0f);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C5B4_main(model, obj->motion[7]);
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
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_801072D8_mstory4(obj, (Vec *)&D_80111D2C_mstory4, 10);
    HuAudSeqPlay(0x72);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[2]);
    func_801074AC_mstory4(model);
    CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    HuPrcSleep(60);
    func_801072D8_mstory4(actor3, (Vec *)&D_80111D8C_mstory4, 3);
    func_80106DA0_mstory4(actor3, (Vec *)&D_80111D5C_mstory4, 5);
    func_801072D8_mstory4(actor3, (Vec *)&D_80111D74_mstory4, 3);
    D_801121C0_mstory4[1].func = func_80109B5C_mstory4;
    HuAudFXPlay(0x219);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[3]);
    func_801072D8_mstory4(actor3, (Vec *)&D_80111D80_mstory4, 3);
    func_80106DBC_mstory4(actor3, (Vec *)&D_80111D68_mstory4, 10, 0);
    func_80107480_mstory4(actor1, 0.0f, 225.0f, 0.0f, 10);
    func_801074AC_mstory4(model);
    HuAudSeqPlay(0x26);
    func_801072D8_mstory4(obj, (Vec *)&D_80111D38_mstory4, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuAudFXPlay(0x159);
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[2]].unk02, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A74);
    func_80106CA8_mstory4();
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[obj->motion[11]].unk02, 0, 10, 2);
    func_80106B3C_mstory4(actor1->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[0]);
    func_80107480_mstory4(actor1, 0.0f, 225.0f, 0.0f, 10);
    HuPrcSleep(50);
    func_80107480_mstory4(actor3, 30.0f, -20.0f, 0.0f, 10);
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[1]].unk02, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A76);
    func_80106CA8_mstory4();
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[0]].unk02, 0, 10, 2);
    func_80107480_mstory4(actor3, 0.0f, 0.0f, 0.0f, 5);
    HuPrcSleep(50);
    HuAudSeqPlay(0x29);
    HuAudFXPlay(0x159);
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[3]].unk02, 0, 10, 0);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A77);
    func_80106CA8_mstory4();
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[0]].unk02, 0, 10, 2);
    D_801121C0_mstory4[1].func = func_80109E3C_mstory4;
    func_8001C624_main(model, HmfModelData[obj->motion[12]].unk02, 0, 10, 0);
    func_801074AC_mstory4(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[2]].unk02, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A78);
    func_80106CA8_mstory4();
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[3]].unk02, 0, 10, 0);
    func_80107480_mstory4(actor3, 0.0f, 0.0f, 0.0f, 10);
    func_80106B3C_mstory4(actor1->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[3]);
    D_801121C0_mstory4[1].func = func_80109E68_mstory4;
    func_80107480_mstory4(obj, 0.0f, 0.0f, 0.0f, 10);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[1]);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(30);
    func_801060E8_mstory4();
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_801093B0_mstory4(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C624_main(model, HmfModelData[obj->motion[10]].unk02, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(80);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_80109474_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, (Vec *)&D_80111DB8_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_801094A8_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, (Vec *)&D_80111DC4_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111DB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111DC4_mstory4);

/* actor 1 */
void func_801094DC_mstory4(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801121C0_mstory4[1].obj = obj;
    D_801121C0_mstory4[1].unk08 = 0;
    D_801121C0_mstory4[1].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80112250_mstory4[1] = D_80111C70_mstory4[1];
    Hu3DModelPosSet(obj->model[1], D_80112250_mstory4[1].x, D_80112250_mstory4[1].y, D_80112250_mstory4[1].z);
    Hu3DModelPosSet(obj->model[2], D_80112250_mstory4[1].x, -5.0f, D_80112250_mstory4[1].z);
    data = DataRead(0xA007E);
    D_80112238_mstory4[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main((s16)D_80112238_mstory4[0], 1, 0);
    func_80032FF8_main((s16)D_80112238_mstory4[0], 0);
    D_80112248_mstory4 = func_80032694_main(HmfModelData[obj->model[1]].hmf, (s16)D_80112238_mstory4[0], 0, "c204n_0_DEF");
    D_80112238_mstory4[0] = D_800D1714_main[D_80112238_mstory4[0]].unk_00;
    data = DataRead(0xA0080);
    D_80112238_mstory4[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80112238_mstory4[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0084);
    D_80112238_mstory4[3] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[0]);
    omPrcSetDestructor(0, func_80109838_mstory4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80109838_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111DDC_mstory4);

const Vec D_80111DE8_mstory4 = { 10.0f, 378.9f, 0.0f };

/* actor 1's scene: actor 3 talks, then actor 4 runs its action */
void func_80109840_mstory4(omObjData *obj) {
    D_801121C0_mstory4[0].func = func_801093B0_mstory4;
    D_801121C0_mstory4[3].func = func_8010A44C_mstory4;
    func_801072D8_mstory4(obj, (Vec *)&D_80111DE8_mstory4, 30);
    func_80106DA0_mstory4(obj, (Vec *)&D_80111E48_mstory4, 20);
    HuPrcSleep(30);
    func_801072D8_mstory4(obj, (Vec *)&D_80111E18_mstory4, 10);
    func_80106DA0_mstory4(obj, (Vec *)&D_80111E3C_mstory4, 15);
    func_80107480_mstory4(D_801121C0_mstory4[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_801072D8_mstory4(obj, (Vec *)&D_80111DF4_mstory4, 15);
    HuPrcSleep(20);
    func_801072D8_mstory4(obj, (Vec *)&D_80111E0C_mstory4, 10);
    func_801072D8_mstory4(D_801121C0_mstory4[3].obj, (Vec *)&D_80111E54_mstory4, 10);
    func_8001C624_main(D_801121C0_mstory4[3].obj->model[1], HmfModelData[D_801121C0_mstory4[3].obj->motion[1]].unk02, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A71);
    func_80106CA8_mstory4();
    func_8001C624_main(D_801121C0_mstory4[3].obj->model[1], HmfModelData[D_801121C0_mstory4[3].obj->motion[0]].unk02, 0, 10, 2);
    func_801072D8_mstory4(D_801121C0_mstory4[3].obj, (Vec *)&D_80111E60_mstory4, 10);
    D_801121C0_mstory4[4].func = func_8010A76C_mstory4;
    func_801072D8_mstory4(obj, (Vec *)&D_80111DDC_mstory4, 20);
    func_8001C624_main(D_801121C0_mstory4[0].obj->model[1], HmfModelData[D_801121C0_mstory4[0].obj->motion[13]].unk02, 0, 10, 2);
    while (!(D_801121C0_mstory4[4].unk08 & 2)) {
        HuPrcVSleep();
    }
    D_801121C0_mstory4[0].func = func_801086F4_mstory4;
    HuPrcSleep(40);
    func_801072D8_mstory4(obj, (Vec *)&D_80111E30_mstory4, 50);
    func_801072D8_mstory4(obj, (Vec *)&D_80111E24_mstory4, 40);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109AE0_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, (Vec *)&D_80111E84_mstory4, 10);
    func_80106DA0_mstory4(obj, (Vec *)&D_80111E78_mstory4, 50);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109B5C_mstory4(omObjData *obj) {
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
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[2]);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109CCC_mstory4(omObjData *obj) {
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
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[3]);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109E3C_mstory4(omObjData *obj) {
    HuPrcSleep(5);
    D_801121C0_mstory4[1].func = func_80109B5C_mstory4;
}

void func_80109E68_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 0.0f, 0.0f, 10);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

/* actor 2 */
void func_80109EA4_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801121C0_mstory4[2].obj = obj;
    D_801121C0_mstory4[2].unk08 = 0;
    D_801121C0_mstory4[2].unk0C = 0;
    obj->model[1] = func_8000B108_main(0x800A0, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    func_8000B460_main(obj, 0, 0x80000);
    func_8000B460_main(obj, 1, 0x1D0076);
    func_8000B460_main(obj, 2, 0x1D0077);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80112250_mstory4[2] = D_80111C70_mstory4[2];
    Hu3DModelPosSet(obj->model[1], D_80112250_mstory4[2].x, D_80112250_mstory4[2].y, D_80112250_mstory4[2].z);
    Hu3DModelPosSet(obj->model[2], D_80112250_mstory4[2].x, -5.0f, D_80112250_mstory4[2].z);
    omPrcSetDestructor(0, func_8010A05C_mstory4);
    D_801121C0_mstory4[2].func = func_8010A064_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A05C_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111DF4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E0C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E18_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E24_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E30_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E3C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E48_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E54_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E60_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E78_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E84_mstory4);

const Vec D_80111E9C_mstory4 = { 200.0f, 0.0f, 1200.0f };
const Vec D_80111EA8_mstory4 = { 166.66666f, 0.0f, 150.0f }; /* unused */

/* actor 2: actor 1 talks, then actor 2 walks off */
void func_8010A064_mstory4(omObjData *obj) {
    HuPrcSleep(10);
    CharFXPlay(0x26B, 6);
    HuPrcSleep(30);
    func_80106B3C_mstory4(D_801121C0_mstory4[1].obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[1]);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A70);
    func_80106CA8_mstory4();
    func_80106B3C_mstory4(D_801121C0_mstory4[1].obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[0]);
    D_801121C0_mstory4[1].func = func_80109840_mstory4;
    CharFXPlay(0x286, 6);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    func_8010ABD0_mstory4(2, 0x28);
    func_80106DA0_mstory4(obj, (Vec *)&D_80111E9C_mstory4, 0x28);
    func_8010AC84_mstory4(2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801121C0_mstory4[2].func = func_80108280_mstory4;
}

/* actor 3 */
void func_8010A1C4_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801121C0_mstory4[3].obj = obj;
    D_801121C0_mstory4[3].unk08 = 0;
    D_801121C0_mstory4[3].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0129);
    func_8000B460_main(obj, 3, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_80112250_mstory4[3] = D_80111C70_mstory4[3];
    Hu3DModelPosSet(obj->model[1], D_80112250_mstory4[3].x, D_80112250_mstory4[3].y, D_80112250_mstory4[3].z);
    Hu3DModelPosSet(obj->model[2], D_80112250_mstory4[3].x, -5.0f, D_80112250_mstory4[3].z);
    omPrcSetDestructor(0, func_8010A3C8_mstory4);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
    D_80111B00_mstory4 = 1;
    while (TRUE) {
        D_801121C0_mstory4[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A3C8_mstory4(void) {
}

const Vec D_80111EB4_mstory4[2] = { { 700.0f, 0.0f, 150.0f }, { 216.66666f, 0.0f, 150.0f } };

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111ECC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111EE4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111F08_mstory4);

void func_8010A3D0_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, (Vec *)&D_80111ECC_mstory4, 10);
    func_80106DA0_mstory4(obj, (Vec *)&D_80111EB4_mstory4[0], 50);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
}

void func_8010A44C_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, (Vec *)&D_80111EE4_mstory4, 20);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
}

/* matches only built blank-stripped (W2DC_BLANKSTRIP, wave 3u v2): otherwise a nop follows the sindf call */
/* actor 3 bobs up and down */
void func_8010A480_mstory4(void) {
    Vec pos;
    s16 model;
    f32 t;
    f32 y;

    t = 0.0f;
    if (D_80111B00_mstory4 != 0) {
        model = D_801121C0_mstory4[3].obj->model[1];
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

/* actor 4 */
void func_8010A5AC_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801121C0_mstory4[4].obj = obj;
    D_801121C0_mstory4[4].unk08 = 0;
    D_801121C0_mstory4[4].unk0C = 0;
    obj->model[1] = func_8000B108_main(D_80111F08_mstory4[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80112250_mstory4[4] = D_80111C70_mstory4[4];
    Hu3DModelPosSet(obj->model[1], D_80112250_mstory4[4].x, D_80112250_mstory4[4].y, D_80112250_mstory4[4].z);
    D_8011228E_mstory4 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_8011228E_mstory4, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_8011228E_mstory4, 60.0f);
    func_800138EC_main(D_8011228E_mstory4, 1, 0);
    func_8001C258_main(D_8011228E_mstory4, 4, 4);
    omPrcSetDestructor(0, func_8010A764_mstory4);
    D_801121C0_mstory4[4].func = func_80108280_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A764_mstory4(void) {
}

/* actor 4 flies along two paths while actor 3 reacts */
void func_8010A76C_mstory4(omObjData *obj) {
    Vec pos;
    ObPath *path[2];
    omObjData *other;
    s32 i;
    f32 t;
    f32 rot;

    path[0] = func_801075B0_mstory4(D_80111B04_mstory4, 0);
    path[1] = func_801075B0_mstory4(D_80111B34_mstory4, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_8011228E_mstory4, 4, 0);
    func_800138EC_main(D_8011228E_mstory4, 1, 1);
    HuAudFXPlay(0x215);
    i = 0;
    do {
        t = i * 0.02f;
        func_801078B4_mstory4(path[0], t * t, &pos);
        i++;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011228E_mstory4, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 50);
    HuPrcSleep(40);
    other = D_801121C0_mstory4[3].obj;
    func_8001C624_main(other->model[1], HmfModelData[other->motion[3]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_801121C0_mstory4[4].unk08 |= 2;
    HuAudFXPlay(0x218);
    func_8001C624_main(other->model[1], HmfModelData[other->motion[0]].unk02, 0, 10, 2);
    rot = 0.0f;
    i = 0;
    do {
        t = i * (1.0f / 120.0f);
        func_801078B4_mstory4(path[1], t * t, &pos);
        rot -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        i++;
        Hu3DModelRotSet(obj->model[1], 0.0f, rot, 0.0f);
        func_8000CFA4_main(D_8011228E_mstory4, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 120);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_8011228E_mstory4, 4, 4);
    HuAudFXPlay(0x21A);
    func_8010815C_mstory4(path[0]);
    func_8010815C_mstory4(path[1]);
    D_801121C0_mstory4[4].unk08 = 1;
    D_801121C0_mstory4[4].func = func_80108280_mstory4;
}

/* turns a's model to face b's */
void func_8010AA88_mstory4(omObjData *a, omObjData *b) {
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

/* starts actor's looping sound effect fx (actors 0 and 2 have one) */
void func_8010ABD0_mstory4(s32 actor, s32 fx) {
    if (D_801121C0_mstory4[actor].unk0C == 0) {
        D_801121C0_mstory4[actor].unk0C = 1;
        D_801121C0_mstory4[actor].unk10 = fx;
        switch (actor) {
        case 0:
            D_801121C0_mstory4[actor].unk14 = CharFXPlay(fx, GwStory.unk1);
            break;
        case 2:
            D_801121C0_mstory4[actor].unk14 = CharFXPlay(fx, 6);
            break;
        }
    }
}

/* stops it */
void func_8010AC84_mstory4(s32 actor) {
    if (D_801121C0_mstory4[actor].unk0C == 1) {
        D_801121C0_mstory4[actor].unk0C = 0;
        switch (actor) {
        case 0:
        case 2:
            HuAudFXStop((s16)D_801121C0_mstory4[actor].unk14);
            break;
        }
    }
}

/* replays each actor's looping sound effect when its motion starts over */
void func_8010ACF4_mstory4(void) {
    s32 i;
    s32 fx;

    while (TRUE) {
        for (i = 0; i < 5; i++) {
            if (D_801121C0_mstory4[i].unk0C == 1 && HmfModelData[D_801121C0_mstory4[i].obj->model[1]].unk40 == 0.0f) {
                fx = D_801121C0_mstory4[i].unk10;
                switch (i) {
                case 0:
                    D_801121C0_mstory4[i].unk14 = CharFXPlay(fx, GwStory.unk1);
                    break;
                case 2:
                    D_801121C0_mstory4[i].unk14 = CharFXPlay(fx, 6);
                    break;
                }
            }
        }
        HuPrcVSleep();
    }
}

/* .data */
s32 D_80111B00_mstory4 = 0;
Vec D_80111B04_mstory4[4] = {
    { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f },
};
Vec D_80111B34_mstory4[6] = {
    { -100.0f, 300.0f, 300.0f }, { -200.0f, 200.0f, 100.0f }, { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f }, { -50.0f, 120.0f, 450.0f }, { 9999.0f, 9999.0f, 9999.0f },
};
