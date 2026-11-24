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
void func_8000BC48_main(u16, s32);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);

extern s32 D_80111AC4_mstory4; /* 1: a board background is open and is closed on exit */
extern Vec D_80111AD0_mstory4; /* camera position */
extern Vec D_80111ADC_mstory4; /* camera target */

extern void (*const D_80111C10_mstory4[2])(void);

void func_801074AC_mstory4(s16 model);
void func_80106B3C_mstory4(s16 model, s16 anim, s16 frame);
void func_8010B9FC_mstory4(void);
void func_80106C10_mstory4(void);
void func_8010724C_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn);
void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_80032FC0_main(s16, s32, s32);
s16 func_800329B4_main(void *);
void func_80106C78_mstory4(void);
void func_80106CA8_mstory4(void);
void func_80106CCC_mstory4(s32 mess);
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
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);
void *func_8001D33C_main(s16, const char *);
void func_801060E8_mstory4(void);
void func_8000BBFC_main(u16 spriteId, s16 alpha);
void func_8000BEAC_main(u16 spriteId, s32 r, s32 g, s32 b);
void func_8000BD94_main(u16, s32, s32);
void func_8000BDDC_main(u16, s32);
void func_80106000_mstory4(void);
void func_80106034_mstory4(void);

// story v2

void func_800138EC_main(s16 model, u16 mask, u16 flags);

/* scene 2: three actors */
extern StoryActor D_801122A0_mstory4[];
extern Vec D_80112300_mstory4[]; /* [3] actor positions */
extern s16 D_80112324_mstory4; /* shadow model */
extern s16 D_80112326_mstory4; /* effect model */
extern s32 D_80111B80_mstory4; /* 1 once actor 2 exists: actor 2 bobs */
extern s16 D_80112328_mstory4[5]; /* actor 0's texture animations */
extern s32 D_80111B84_mstory4; /* 1: actor 2 stops bobbing */
extern s32 D_80112338_mstory4[4]; /* actor 1's texture animations */
extern s16 D_80112348_mstory4;
extern const Vec D_80111F80_mstory4;

extern s32 D_80111B88_mstory4; /* 1 once actor 1 exists: its model 6 bobs */
extern s32 D_80111B8C_mstory4; /* 1: it holds still */
void func_801118F8_mstory4(s32 actor, s32 fx);
void func_8011196C_mstory4(s32 actor);
void func_8010D1A0_mstory4(omObjData *obj);

extern const char *D_80111B94_mstory4[4]; /* aura part names */
extern const char D_80111FF8_mstory4[]; /* "c221_000-body" */
void func_80017358_main(s16 arg0, char *arg1, s16 arg2, char *arg3);
void func_80107220_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_8010E5C4_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn);
void func_8010EC38_mstory4(void);
void func_8010EDA0_mstory4(void);
void func_8010EE3C_mstory4(void);
void func_8010F0E0_mstory4(void);
void func_8010F12C_mstory4(void);
void func_8010F178_mstory4(void);
void func_8010F588_mstory4(void);
void func_8010F660_mstory4(void);
void func_8010F910_mstory4(void);
void func_8010FC98_mstory4(void);
void func_80110BB4_mstory4(omObjData *obj);
void func_80110D5C_mstory4(omObjData *obj);
extern const Vec D_80111F10_mstory4[]; /* [3] actor start positions */
extern const s32 D_80111F34_mstory4[8]; /* per character: actor 0 motions */
extern const s32 D_80111F54_mstory4[8];
void func_8010BAF0_mstory4(omObjData *obj);
void func_8010BAF8_mstory4(void);
void func_8010BF3C_mstory4(void);
void func_8010C0BC_mstory4(void);
void func_8010C54C_mstory4(void);
void func_8010C8D0_mstory4(void);
void func_8010CAE8_mstory4(void);
void func_8010CD40_mstory4(void);
void func_8010CE90_mstory4(void);
void func_8010D128_mstory4(void);
void func_801119C0_mstory4(void);

ObPath *func_8010AE20_mstory4(Vec *points, s16 flags) {
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
void func_8010B124_mstory4(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C8050", func_8010B124_mstory4);
#endif

void func_8010B9CC_mstory4(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* scene 2: starts its actors and processes */
void func_8010B9FC_mstory4(void) {
    func_80106C10_mstory4();
    D_80112324_mstory4 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010BAF8_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010C0BC_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010C8D0_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010CE90_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010CD40_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010D128_mstory4, 0x1002, 0x800, 0);
    omAddPrcObj(func_801119C0_mstory4, 0x1002, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80112324_mstory4, 4, 4);
}

void func_8010BAF0_mstory4(omObjData *obj) {
}

/* scene 2 actor 0: the player's character */
void func_8010BAF8_mstory4(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 6, 0x10, -1, NULL);
    D_801122A0_mstory4[0].obj = obj;
    D_801122A0_mstory4[0].unk08 = 0;
    D_801122A0_mstory4[0].unk0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80112324_mstory4);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x34));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x8F));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x32));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 7, D_80111F34_mstory4[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x9B));
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x7A));
    func_8000B460_main(obj, 10, D_80111F54_mstory4[chr]);
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 2));
    func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x72));
    func_8000B460_main(obj, 13, func_80017BB8_main(chr, 0x6C));
    D_80112328_mstory4[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80112328_mstory4[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80112328_mstory4[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80112328_mstory4[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    D_80112328_mstory4[4] = func_80017AD8_main(func_80017BB8_main(chr, 0xAB));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112328_mstory4[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80112300_mstory4[0] = D_80111F10_mstory4[0];
    Hu3DModelPosSet(obj->model[1], D_80112300_mstory4[0].x, D_80112300_mstory4[0].y, D_80112300_mstory4[0].z);
    Hu3DModelPosSet(obj->model[2], D_80112300_mstory4[0].x, -5.0f, D_80112300_mstory4[0].z);
    omPrcSetDestructor(0, func_8010BF3C_mstory4);
    D_801122A0_mstory4[0].func = func_8010BAF0_mstory4;
    while (TRUE) {
        D_801122A0_mstory4[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010BF3C_mstory4(void) {
}

/* actor 0 steps forward with its voice on */
void func_8010BF44_mstory4(omObjData *obj) {
    Vec pos;
    s16 model;

    model = obj->model[1];
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    HuPrcSleep(30);
    func_8001C624_main(model, HmfModelData[obj->motion[6]].unk02, 0, 10, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_8010724C_mstory4(obj, pos.x, pos.y, pos.z + 50.0f, 15, 0);
    func_8011196C_mstory4(0);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801122A0_mstory4[0].func = func_8010BAF0_mstory4;
}

void func_8010C080_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 180.0f, 0.0f, 40);
    D_801122A0_mstory4[0].func = func_8010BAF0_mstory4;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F10_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F1C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F28_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F34_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F54_mstory4);

/* scene 2 actor 1, with its texture animations */
void func_8010C0BC_mstory4(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 8, 8, -1, NULL);
    D_801122A0_mstory4[1].obj = obj;
    D_801122A0_mstory4[1].unk08 = 0;
    D_801122A0_mstory4[1].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80112324_mstory4);
    obj->model[3] = func_8000B108_main(0x1D002B, 0x2B9);
    obj->model[4] = func_8000B108_main(0x1D002C, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    obj->model[5] = func_8000B108_main(0x1D002D, 0x299);
    func_8001C258_main(obj->model[5], 4, 4);
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    func_8001C814_main(obj->model[5], 2, 2);
    func_8001C92C_main(obj->model[5], 0.5f);
    obj->model[6] = func_8000B108_main(0xA015F, 0x2A9);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8001C814_main(obj->model[6], 2, 2);
    D_80111B88_mstory4 = 1;
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D0083);
    func_8000B460_main(obj, 3, 0x1D0084);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 10.0f, 330.0f, 0.0f);
    D_80112300_mstory4[1] = D_80111F10_mstory4[1];
    Hu3DModelPosSet(obj->model[1], D_80112300_mstory4[1].x, D_80112300_mstory4[1].y, D_80112300_mstory4[1].z);
    Hu3DModelPosSet(obj->model[2], D_80112300_mstory4[1].x, -5.0f, D_80112300_mstory4[1].z);
    data = DataRead(0xA007E);
    D_80112338_mstory4[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main((s16)D_80112338_mstory4[0], 1, 0);
    func_80032FF8_main((s16)D_80112338_mstory4[0], 0);
    D_80112348_mstory4 = func_80032694_main(HmfModelData[obj->model[1]].hmf, (s16)D_80112338_mstory4[0], 0, "c204n_0_DEF");
    D_80112338_mstory4[0] = D_800D1714_main[D_80112338_mstory4[0]].unk_00;
    data = DataRead(0xA0080);
    D_80112338_mstory4[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80112338_mstory4[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0081);
    D_80112338_mstory4[3] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106B3C_mstory4(obj->model[1], D_80112348_mstory4, (s16)D_80112338_mstory4[0]);
    omPrcSetDestructor(0, func_8010C54C_mstory4);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
    while (TRUE) {
        D_801122A0_mstory4[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C54C_mstory4(void) {
}

void func_8010C554_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 230.0f, 0.0f, 30);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

/* actor 1 spins, sinks and pops model 5 above itself */
void func_8010C590_mstory4(omObjData *obj) {
    s32 i;
    Vec pos;
    f32 s;

    func_80107480_mstory4(obj, 0.0f, 360.0f, 0.0f, 10);
    HmfModelData[obj->model[1]].rot.y = 0.0f;
    pos.x = HmfModelData[obj->model[1]].pos.x;
    pos.y = HmfModelData[obj->model[1]].pos.y;
    pos.z = HmfModelData[obj->model[1]].pos.z;
    func_8010724C_mstory4(obj, pos.x, pos.y - 50.0f, pos.z, 20, 0);
    pos.x = HmfModelData[obj->model[1]].pos.x;
    pos.y = HmfModelData[obj->model[1]].pos.y + 80.0f;
    pos.z = HmfModelData[obj->model[1]].pos.z;
    func_8001C258_main(obj->model[5], 4, 0);
    Hu3DModelPosSet(obj->model[5], pos.x, pos.y, pos.z);
    Hu3DModelPosSet(obj->model[6], pos.x, pos.y, pos.z);
    HuAudFXPlay(0x222);
    for (i = 0; i < 10; i++) {
        Hu3DModelPosSet(obj->model[5], pos.x, pos.y, pos.z);
        Hu3DModelPosSet(obj->model[6], pos.x, pos.y, pos.z);
        s = 2.0f * sindf(i * 9.0f);
        Hu3DModelScaleSet(obj->model[5], s, s, 1.0f);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_8010C7F8_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 10.0f, -30.0f, 0.0f, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    HuPrcSleep(30);
    func_8010724C_mstory4(obj, D_80111F10_mstory4[1].x + 300.0f, D_80111F10_mstory4[1].y + 100.0f, D_80111F10_mstory4[1].z, 20, 0);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

/* scene 2 actor 2 */
void func_8010C8D0_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801122A0_mstory4[2].obj = obj;
    D_801122A0_mstory4[2].unk08 = 0;
    D_801122A0_mstory4[2].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0129);
    func_8000B460_main(obj, 3, 0xA0127);
    func_8000B460_main(obj, 4, 0xA012D);
    obj->model[2] = Hu3DModelLink(D_80112324_mstory4);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80112300_mstory4[2] = D_80111F10_mstory4[2];
    Hu3DModelPosSet(obj->model[1], D_80112300_mstory4[2].x, D_80112300_mstory4[2].y, D_80112300_mstory4[2].z);
    Hu3DModelPosSet(obj->model[2], D_80112300_mstory4[2].x, -5.0f, D_80112300_mstory4[2].z);
    omPrcSetDestructor(0, func_8010CAE8_mstory4);
    D_801122A0_mstory4[2].func = func_8010BAF0_mstory4;
    D_80111B80_mstory4 = 1;
    while (TRUE) {
        D_801122A0_mstory4[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010CAE8_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F80_mstory4);

/* actor 2 swings out along D_80111F80_mstory4 and back, then hides */
void func_8010CAF0_mstory4(omObjData *obj) {
    s16 models[2];
    Vec pos;
    Vec ofs;
    f32 rot;
    f32 scale;
    f32 t;
    f32 s;
    f32 c;
    s32 i;

    models[0] = obj->model[1];
    models[1] = obj->model[2];
    pos.x = HmfModelData[models[0]].pos.x;
    pos.y = HmfModelData[models[0]].pos.y;
    pos.z = HmfModelData[models[0]].pos.z;
    ofs.x = 0.0f;
    ofs.y = 0.0f;
    ofs.z = 0.0f;
    scale = rot = ofs.x;
    D_80111B84_mstory4 = 1;
    i = 0;
    do {
        t = i * 4.5f;
        s = sindf(t);
        ofs.x = s * D_80111F80_mstory4.x;
        ofs.y = s * D_80111F80_mstory4.y;
        ofs.z = s * D_80111F80_mstory4.z;
        Hu3DModelPosSet(models[0], pos.x + ofs.x, pos.y + ofs.y, pos.z + ofs.z);
        Hu3DModelPosSet(models[1], pos.x + ofs.x, 0.0f, pos.z + ofs.z);
        c = 2.0f * cosdf(t);
        Hu3DModelScaleSet(models[0], c, c, c);
        scale -= 0.2;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        i++;
        Hu3DModelScaleSet(models[1], scale, scale, scale);
        rot += 0.5f;
        Hu3DModelRotSet(models[0], 0.0f, 0.0f, rot);
        HuPrcVSleep();
    } while (i < 20);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801122A0_mstory4[2].func = func_8010BAF0_mstory4;
}

/* actor 2 bobs up and down until D_80111B84_mstory4 is 1 */
void func_8010CD40_mstory4(void) {
    Vec pos;
    s16 model;
    f32 t;
    f32 y;

    t = 0.0f;
    if (D_80111B80_mstory4 != 0) {
        model = D_801122A0_mstory4[2].obj->model[1];
        pos.y = HmfModelData[model].pos.y;
        while (TRUE) {
            pos.x = HmfModelData[model].pos.x;
            pos.z = HmfModelData[model].pos.z;
            y = sindf(t) * 25.0f + 25.0f;
            t += 2.0f;
            t = (t >= 360.0f) ? t - 360.0f : t;
            Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
            if (D_80111B84_mstory4 == 1) {
                break;
            }
            HuPrcVSleep();
        }
        while (TRUE) {
            HuPrcVSleep();
        }
    }
}

/* actor 1's model 6 bobs while D_80111B8C_mstory4 is 0 */
void func_8010CE90_mstory4(void) {
    Vec pos;
    s16 model;
    f32 t;
    f32 y;

    t = 0.0f;
    if (D_80111B88_mstory4 != 0) {
        model = D_801122A0_mstory4[1].obj->model[6];
        pos.y = HmfModelData[model].pos.y;
        while (TRUE) {
            if (D_80111B8C_mstory4 == 0) {
                pos.x = HmfModelData[model].pos.x;
                pos.z = HmfModelData[model].pos.z;
                y = sindf(t) * 40.0f;
                t += 2.0f;
                t = (t >= 360.0f) ? t - 360.0f : t;
                Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
            } else {
                pos.y = HmfModelData[model].pos.y;
                t = 0.0f;
            }
            HuPrcVSleep();
        }
    }
}

/* turns a's model to face b's */
void func_8010CFE0_mstory4(omObjData *a, omObjData *b) {
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

/* scene 2 actor 3: the camera/effects driver */
void func_8010D128_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_801122A0_mstory4[3].obj = obj;
    D_801122A0_mstory4[3].unk08 = 0;
    D_801122A0_mstory4[3].unk0C = 0;
    D_801122A0_mstory4[3].func = func_8010D1A0_mstory4;
    while (TRUE) {
        D_801122A0_mstory4[3].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F98_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111FA8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111FB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111FC8_mstory4);

/* NON_MATCHING: retail's frame is 72 bytes larger (unused stack after the spill of the actor 0 model),
   and register allocation / constant-load order differ in the lift loop, the motion wait and the final
   pad wait; the logic was checked against the asm block by block (count 1608 = 1608) */
#ifdef NON_MATCHING
/* scene 2's script (actor 3's action): the talk, actor 1's dice block lift, the aura parts and the exit */
void func_8010D1A0_mstory4(omObjData *obj) {
    Vec pos;
    MsPart *parts[4];
    Vec *v;
    u16 model;
    omObjData *actor0;
    omObjData *actor1;
    omObjData *actor2;
    s32 i;
    f32 rise;
    f32 frame;

    HuPrcVSleep();
    actor0 = D_801122A0_mstory4[0].obj;
    actor1 = D_801122A0_mstory4[1].obj;
    actor2 = D_801122A0_mstory4[2].obj;
    model = actor0->model[1];
    HuPrcSleep(10);
    CharFXPlay(0x262, GwStory.unk1);
    func_80017954_main(actor0->model[1], 2, GwStory.unk1, D_80112328_mstory4[2]);
    func_8001C624_main(model, HmfModelData[actor0->motion[1]].unk02, 0, 20, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(30);
    func_8001C624_main(model, HmfModelData[actor0->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(20);
    func_80017954_main(actor0->model[1], 2, GwStory.unk1, D_80112328_mstory4[0]);
    func_8001C624_main(model, HmfModelData[actor0->motion[10]].unk02, 0, 10, 2);
    func_80107480_mstory4(actor0, 0.0f, 180.0f, 0.0f, 20);
    HuPrcSleep(30);
    func_80107480_mstory4(actor1, 0.0f, 210.0f, 0.0f, 10);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A79);
    func_80106CA8_mstory4();
    HuPrcSleep(40);
    func_8010724C_mstory4(actor2, 0.0f, 200.0f, -150.0f, 40, 0);
    HuPrcSleep(50);
    HuAudFXPlay(0x15C);
    func_8001C624_main(model, HmfModelData[actor0->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(D_801122A0_mstory4[2].obj->model[1], HmfModelData[D_801122A0_mstory4[2].obj->motion[2]].unk02, 0, 10, 2);
    D_801122A0_mstory4[0].func = func_8010BF44_mstory4;
    func_80107480_mstory4(actor2, 0.0f, -10.0f, 0.0f, 10);
    func_8010724C_mstory4(actor2, -120.0f, 200.0f, 400.0f, 20, 0);
    func_80107480_mstory4(actor2, 0.0f, 0.0f, 0.0f, 10);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7A);
    func_80106CA8_mstory4();
    func_8001C624_main(D_801122A0_mstory4[2].obj->model[1], HmfModelData[D_801122A0_mstory4[2].obj->motion[2]].unk02, 0, 10, 0);
    HuPrcSleep(30);
    func_8010724C_mstory4(actor2, 0.0f, 200.0f, -150.0f, 5, 0);
    func_80107480_mstory4(actor2, 0.0f, 0.0f, 0.0f, 5);
    func_8001C624_main(model, HmfModelData[actor0->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_8001C624_main(D_801122A0_mstory4[2].obj->model[1], HmfModelData[D_801122A0_mstory4[2].obj->motion[4]].unk02, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7B);
    func_80106CA8_mstory4();
    D_801122A0_mstory4[2].func = func_8010CAF0_mstory4;
    HuAudFXPlay(0x224);
    HuAudSeqFadeOut(120);
    HuPrcSleep(10);
    D_801122A0_mstory4[1].func = func_80110BB4_mstory4;
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_8001C624_main(model, HmfModelData[actor0->motion[6]].unk02, 0, 10, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_80107220_mstory4(actor0, pos.x - 80.0f, pos.y, pos.z - 200.0f, 20);
    func_8011196C_mstory4(0);
    func_8001C624_main(model, HmfModelData[actor0->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(50);
    func_80107480_mstory4(actor0, 0.0f, 0.0f, 0.0f, 10);
    CharFXPlay(0x286, GwStory.unk1);
    func_8001C624_main(model, HmfModelData[actor0->motion[5]].unk02, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(40);
    D_801122A0_mstory4[1].func = func_8010C590_mstory4;
    HuPrcSleep(40);
    func_8001C624_main(model, HmfModelData[actor0->motion[0]].unk02, 0, 30, 0);
    HuPrcSleep(20);
    func_8001C624_main(model, HmfModelData[actor0->motion[9]].unk02, 0, 10, 0);
    func_80107480_mstory4(actor0, 0.0f, 110.0f, 0.0f, 20);
    func_801074AC_mstory4(model);
    HuPrcSleep(25);
    func_8001C624_main(model, HmfModelData[actor0->motion[6]].unk02, 0, 10, 2);
    func_8001C92C_main(model, 1.0f);
    func_801118F8_mstory4(0, 0x1F);
    func_80107220_mstory4(actor0, -100.0f, 0.0f, 300.0f, 35);
    func_8011196C_mstory4(0);
    func_8001C92C_main(model, 1.0f);
    func_8001C624_main(model, HmfModelData[actor0->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(20);
    func_80106000_mstory4();
    func_8010EC38_mstory4();
    D_80111ADC_mstory4.x = HmfModelData[actor1->model[1]].pos.x;
    D_80111ADC_mstory4.y = HmfModelData[actor1->model[1]].pos.y + 90.0f;
    D_80111ADC_mstory4.z = HmfModelData[actor1->model[1]].pos.z;
    D_80111AD0_mstory4.x = HmfModelData[actor1->model[1]].pos.x;
    D_80111AD0_mstory4.y = HmfModelData[actor1->model[1]].pos.y + 90.0f;
    D_80111AD0_mstory4.z = HmfModelData[actor1->model[1]].pos.z + 400.0f;
    func_8010F0E0_mstory4();
    pos.x = HmfModelData[actor1->model[1]].pos.x;
    pos.y = HmfModelData[actor1->model[1]].pos.y + 90.0f;
    pos.z = HmfModelData[actor1->model[1]].pos.z - 5.0f;
    Hu3DModelPosSet(actor1->model[6], pos.x, pos.y, pos.z);
    Hu3DModelPosSet(actor1->model[5], pos.x, pos.y, pos.z - 80.0f);
    func_8001C5B4_main(actor1->model[1], actor1->motion[2]);
    func_8001C814_main(actor1->model[1], 2, 0);
    func_8001C814_main(actor1->model[1], 1, 1);
    func_80017358_main(actor1->model[3], "saikoro", actor1->model[1], "saikoro");
    func_80017358_main(actor1->model[4], "c204nj1-futa", actor1->model[1], "futa");
    rise = 0.0f;
    for (i = 0; i < 4; i++) {
        func_8002FD8C_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111B94_mstory4[i], 0x1B, 0x45);
        func_8002FD8C_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111B94_mstory4[i], 0x1B, 0x46);
        func_8002FD8C_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111B94_mstory4[i], 0x1B, 0x47);
        parts[i] = func_8001D33C_main(actor1->model[6], D_80111B94_mstory4[i]);
        v = &parts[i]->scale;
        v->x = rise;
        v->y = rise;
        v->z = rise;
        v = &parts[i]->scale2;
        v->x = rise;
        v->y = rise;
        v->z = rise;
    }
    HuPrcVSleep();
    HuPrcSleep(10);
    func_8001C814_main(actor1->model[1], 1, 0);
    HuPrcSleep(30);
    func_8001C258_main(actor1->model[6], 4, 0);
    HuAudFXPlay(0x223);
    HuPrcSleep(60);
    for (i = 0, rise = 0.0f; i <= 60.0f; i++) {
        D_80111ADC_mstory4.y += 4.1666665f;
        D_80111AD0_mstory4.y += 4.1666665f;
        rise += 4.1666665f;
        HuPrcVSleep();
        Hu3DModelPosSet(actor1->model[6], pos.x, rise + pos.y, pos.z);
        Hu3DModelPosSet(actor1->model[5], pos.x, rise + pos.y, pos.z - 80.0f);
    }
    HuPrcSleep(50);
    D_80111ADC_mstory4.x = -25.0f;
    D_80111ADC_mstory4.y = 0.0f;
    D_80111ADC_mstory4.z = -650.0f;
    D_80111AD0_mstory4.x = 14.0f;
    D_80111AD0_mstory4.y = 193.0f;
    D_80111AD0_mstory4.z = 1400.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(actor1->model[6], D_80111F10_mstory4[1].x, D_80111F10_mstory4[1].y + 150.0f, D_80111F10_mstory4[1].z);
    func_8001C258_main(actor1->model[5], 4, 4);
    for (i = 0; i < 4; i++) {
        func_8002FDCC_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111B94_mstory4[i], 0x1B, 0x45);
        func_8002FDCC_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111B94_mstory4[i], 0x1B, 0x46);
        func_8002FDCC_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111B94_mstory4[i], 0x1B, 0x47);
    }
    func_8010EDA0_mstory4();
    func_80106034_mstory4();
    func_8010F12C_mstory4();
    Hu3DModelPosSet(actor0->model[1], 0.0f, 0.0f, 300.0f);
    Hu3DModelPosSet(actor0->model[2], 0.0f, 0.0f, 300.0f);
    HuPrcVSleep();
    D_80111B8C_mstory4 = 0;
    func_8001C5B4_main(actor1->model[1], actor1->motion[2]);
    func_8001C814_main(actor1->model[1], 2, 0);
    func_8001C814_main(actor1->model[1], 4, 4);
    func_8001C624_main(model, HmfModelData[actor0->motion[9]].unk02, 0, 10, 0);
    func_8001C6A8_main(actor1->model[1], D_800CCF58_main[HmfModelData[actor1->model[1]].unk02].unk02);
    do {
        frame = HmfModelData[actor1->model[1]].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C814_main(actor1->model[1], 4, 0);
    func_8001C5B4_main(actor1->model[1], actor1->motion[0]);
    func_8001C814_main(actor1->model[1], 2, 2);
    func_8001C624_main(model, HmfModelData[actor0->motion[8]].unk02, 0, 30, 2);
    D_80111B8C_mstory4 = 1;
    D_801122A0_mstory4[0].func = func_8010C080_mstory4;
    func_8010E5C4_mstory4(actor1, 0.0f, 300.0f, 300.0f, 40, 0);
    D_80111B8C_mstory4 = 0;
    pos.x = HmfModelData[actor1->model[1]].pos.x;
    pos.y = HmfModelData[actor1->model[1]].pos.y + 100.0f;
    pos.z = HmfModelData[actor1->model[1]].pos.z;
    func_8010724C_mstory4(actor1, pos.x, pos.y, pos.z, 15, 0);
    HuPrcSleep(20);
    HuAudSeqPlay(0x2A);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7C);
    func_80106CA8_mstory4();
    func_8002FD8C_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111FF8_mstory4, 0x4C, 0x45);
    func_8002FD8C_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111FF8_mstory4, 0x4C, 0x46);
    parts[0] = func_8001D33C_main(actor1->model[6], D_80111FF8_mstory4);
    rise = 0.0f;
    parts[0]->rotY = rise;
    parts[0]->unk3C = rise;
    for (i = 0; i < 10; i++) {
        parts[0]->rotY += 4.5f;
        parts[0]->unk3C += 4.5f;
        parts[0]->unk10 += 0.5f;
        parts[0]->unk34 += 0.5f;
        HuPrcVSleep();
    }
    func_80107480_mstory4(actor1, 0.0f, -45.0f, 0.0f, 10);
    func_8001C624_main(actor1->model[1], HmfModelData[actor1->motion[3]].unk02, 0, 10, 2);
    func_80106B3C_mstory4(actor1->model[1], D_80112348_mstory4, (s16)D_80112338_mstory4[3]);
    HuPrcSleep(40);
    func_8001C624_main(actor1->model[1], HmfModelData[actor1->motion[0]].unk02, 0, 10, 2);
    func_80107480_mstory4(actor1, 10.0f, -20.0f, 0.0f, 10);
    for (i = 0; i < 10; i++) {
        parts[0]->rotY -= 4.5f;
        parts[0]->unk3C -= 4.5f;
        parts[0]->unk10 -= 0.5f;
        parts[0]->unk34 -= 0.5f;
        HuPrcVSleep();
    }
    func_8002FDCC_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111FF8_mstory4, 0x4C, 0x45);
    func_8002FDCC_main(actor1->model[6], HmfModelData[actor1->model[6]].unk02, D_80111FF8_mstory4, 0x4C, 0x46);
    HuPrcSleep(40);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7D);
    func_80106CA8_mstory4();
    HuPrcSleep(30);
    D_80111B8C_mstory4 = 1;
    D_801122A0_mstory4[1].func = func_80110D5C_mstory4;
    func_8010E5C4_mstory4(actor1, 0.0f, 230.0f, 300.0f, 30, 0);
    HuAudFXPlay(0x225);
    func_8010E5C4_mstory4(actor1, 0.0f, 700.0f, 300.0f, 30, 0);
    HuPrcSleep(30);
    func_8010F0E0_mstory4();
    func_8010F178_mstory4();
    func_80046558_main(D_801122A0_mstory4[2].obj->model[1]);
    func_8001ACDC_main(D_801122A0_mstory4[2].obj->model[1]);
    func_80106000_mstory4();
    func_8010EE3C_mstory4();
    D_80111B8C_mstory4 = 1;
    func_8010F588_mstory4();
    func_8010F660_mstory4();
    func_8010F910_mstory4();
    func_8010FC98_mstory4();
    HuPrcSleep(150);
    if (D_800D5558_main[0] == 0) {
        do {
            HuPrcVSleep();
        } while (D_800D5558_main[0] == 0);
    }
    func_801060E8_mstory4();
    D_801122A0_mstory4[3].func = func_8010BAF0_mstory4;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C8050", func_8010D1A0_mstory4);
#endif

// story h3
extern f32 D_80111B90_mstory4; /* the body spin */
extern s16 D_8011234A_mstory4[2][2];
extern s16 D_80112352_mstory4;
extern s16 D_80112358_mstory4[8]; /* sprite files */
extern s16 D_80112368_mstory4[8]; /* sprites */
extern const s32 D_80112008_mstory4[8];
void func_8010EF00_mstory4(s32 i);
void func_8010E7C0_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn);

/* hmfman's per-model particle work (HmfModel.unkBC, 13F90.c's HmfFxWork) as the smoke effect
   uses it: one StFxPart per face group */
typedef struct StFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 life; /* > 0 while live */
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ Vec unk24;
} StFxPart; /* size 0x30 */

typedef struct StFxWork {
    /* 0x00 */ s16 motion;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags; /* 1 emitting, 4 stopping */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 life;
    /* 0x0C */ f32 decay;
    /* 0x10 */ f32 spread;
    /* 0x14 */ f32 timer; /* < 0: none */
    /* 0x18 */ void (*hook)(s16);
    /* 0x1C */ Vec center;
    /* 0x28 */ Vec verts[4];
    /* 0x58 */ StFxPart *parts;
} StFxWork; /* size 0x5C */

typedef struct StFxHmf {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 groupCount;
} StFxHmf;

/* a sparkle group: `count` screen points */
typedef struct StSparkGroup {
    /* 0x00 */ s16 count;
    /* 0x04 */ s16 (*pos)[2];
} StSparkGroup; /* size 0x8 */

/* func_80110E3C_mstory4's work */
typedef struct StSparkWork {
    /* 0x00 */ s16 time;
    /* 0x02 */ s16 delay;
    /* 0x04 */ Vec pos;
} StSparkWork; /* size 0x10 */

extern const StSparkGroup D_80112088_mstory4[6];
extern s16 D_80111BA4_mstory4[4][2];
extern s16 D_80111BB4_mstory4[5][2];
extern s16 D_80111BC8_mstory4[4][2];
extern s16 D_80111BD8_mstory4[3][2];
extern s16 D_80111BE4_mstory4[3][2];
extern s16 D_80111BF0_mstory4[3][2];
extern const char D_80111F98_mstory4[];
extern const char D_80111FA8_mstory4[];
extern const char D_80111FB8_mstory4[];
extern const char D_80111FC8_mstory4[];
extern const s32 D_801120B8_mstory4[7]; /* fade-in frames of pictures 1..6 */
extern const s32 D_801120D4_mstory4[8]; /* name plate file per character */
extern const s16 D_801120F4_mstory4[8][2];
extern const s16 D_80112114_mstory4[2];
extern u8 D_80111BFC_mstory4[4];
extern u8 D_80111C04_mstory4[4][3]; /* burst colours */
extern s16 D_80111C00_mstory4;
extern s16 D_80112378_mstory4[22]; /* sparkle sprites */
extern s16 D_801123A4_mstory4;
extern s16 D_801123A6_mstory4[2]; /* name plate sprites */
s16 func_80055810_main(void *);
void *HuMemAllocTag(s32 size, s16 tag);
void func_80013390_main(s16 model, s16 type, char *name, void (*hook)(s16));
void func_8010EF28_mstory4(s32 i);
void func_8010EF50_mstory4(s32 i, s16 arg1);
void func_8010F010_mstory4(void);
s16 func_80110394_mstory4(s32 file, s32 prio);
void func_801104D4_mstory4(s16 model, f32 spread);
void func_80110528_mstory4(omObjData *obj);
s32 func_80110724_mstory4(s16 model, f32 x, f32 y, f32 z);
void func_80110888_mstory4(s16 model, f32 life, f32 decay, f32 rise);
s16 func_801108FC_mstory4(s32 file, s32 prio);
void func_801109EC_mstory4(s16 model);
s16 func_80110B4C_mstory4(s32 file, s32 prio);
void func_80110E3C_mstory4(void);
void func_80111430_mstory4(s16 model, f32 x, f32 y, f32 z, s16 count, s32 mode);
void func_80111740_mstory4(s16 model);
void func_80013954_main(s16 model, s32 arg1);

/* the firework burst's particles (the same hmfman work as StFxWork) */
typedef struct StBurstPart {
    /* 0x00 */ u8 rgb[3];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale; /* > 0 while live */
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec dir;
    /* 0x24 */ f32 color; /* D_80111C04_mstory4 index */
    /* 0x28 */ f32 time;
    /* 0x2C */ char unk2C[4];
} StBurstPart; /* size 0x30 */

typedef struct StBurstWork {
    /* 0x00 */ s16 motion;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags;
    /* 0x06 */ char unk06[0x52];
    /* 0x58 */ StBurstPart *parts;
} StBurstWork; /* size 0x5C */

/* HmfData.unk60's objects as the burst reads them */
typedef struct StBurstObj {
    /* 0x00 */ char unk00[0x22];
    /* 0x22 */ s16 faceCount;
    /* 0x24 */ char unk24[0xA];
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ char unk30[0x24];
    /* 0x54 */ HmfModelData_Unk64_Unk60_Unk54_Struct *faces;
    /* 0x58 */ char unk58[0x10];
} StBurstObj; /* size 0x68 */

/* walks obj's model 6 to (x, y, z) in `frames` frames, turning it to face the way first when
   `turn` is set */
void func_8010E5C4_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec start;
    Vec delta;
    Vec step;
    Vec pos;
    s16 model;
    f32 t;

    model = obj->model[6];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    delta.x = x - start.x;
    delta.y = y - start.y;
    delta.z = z - start.z;
    if (turn) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(delta.z, delta.x) - 90.0f), 0.0f);
    }
    t = frames;
    step.x = delta.x / t;
    step.y = delta.y / t;
    step.z = delta.z / t;
    for (t = 0.0f; t < frames; t += 1.0f) {
        pos.x = t * step.x + start.x;
        pos.y = t * step.y + start.y;
        pos.z = t * step.z + start.z;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    HuPrcVSleep();
}

/* as func_8010E5C4_mstory4, but the height eases out on a sine and the model grows from 1 to 5
   (the scale set each frame is the previous frame's) */
void func_8010E7C0_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec start;
    Vec delta;
    Vec step;
    Vec pos;
    s16 model;
    f32 t;
    f32 scale;
    f32 a;

    model = obj->model[6];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    delta.x = x - start.x;
    delta.y = y - start.y;
    delta.z = z - start.z;
    if (turn) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(delta.z, delta.x) - 90.0f), 0.0f);
    }
    t = frames;
    step.x = delta.x / t;
    step.y = delta.y / t;
    step.z = delta.z / t;
    scale = 1.0f;
    for (t = 0.0f; t < frames; t += 1.0f) {
        pos.x = t * step.x + start.x;
        a = t / frames * 90.0f;
        pos.y = sindf(a) * delta.y + start.y;
        pos.z = t * step.z + start.z;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        Hu3DModelScaleSet(model, scale, scale, scale);
        scale = sindf(a) * 5.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    HuPrcVSleep();
}

/* as func_8010E5C4_mstory4, clearing D_80111B90_mstory4 first and without the last frame's
   sleep */
f32 func_8010EA34_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec start;
    Vec delta;
    Vec step;
    Vec pos;
    s16 model;
    f32 t;

    model = obj->model[6];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    delta.x = x - start.x;
    delta.y = y - start.y;
    delta.z = z - start.z;
    if (turn) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(delta.z, delta.x) - 90.0f), 0.0f);
    }
    t = frames;
    step.x = delta.x / t;
    step.y = delta.y / t;
    step.z = delta.z / t;
    D_80111B90_mstory4 = 0.0f;
    for (t = 0.0f; t < frames; t += 1.0f) {
        pos.x = t * step.x + start.x;
        pos.y = t * step.y + start.y;
        pos.z = t * step.z + start.z;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    return 20.0f;
}

/* the four screen-quarter sprites */
void func_8010EC38_mstory4(void) {
    s32 i;
    s32 j;

    D_80112352_mstory4 = func_8000B838_main(0x1D0028);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            D_8011234A_mstory4[i][j] = InitEspriteSlot(D_80112352_mstory4, 0, 0);
            func_8000BBD4_main(D_8011234A_mstory4[i][j], j * 160 + 80, i * 120 + 60);
            func_8000BC48_main(D_8011234A_mstory4[i][j], 0x4000);
        }
    }
    func_8000BC48_main(D_8011234A_mstory4[0][1], 1);
    func_8000BC48_main(D_8011234A_mstory4[1][0], 2);
    func_8000BC48_main(D_8011234A_mstory4[1][1], 3);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            func_8000BB54_main(D_8011234A_mstory4[i][j]);
        }
    }
}

void func_8010EDA0_mstory4(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            func_8000BB94_main(D_8011234A_mstory4[i][j]);
            func_8000C184_main(D_8011234A_mstory4[i][j]);
        }
    }
    HuSprKill(D_80112352_mstory4);
}

/* the eight full-screen picture sprites, hidden */
void func_8010EE3C_mstory4(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_80112358_mstory4[i] = func_8000B838_main(D_80112008_mstory4[i]);
        D_80112368_mstory4[i] = InitEspriteSlot(D_80112358_mstory4[i], 0, 0);
        func_8000BBD4_main(D_80112368_mstory4[i], 160, 120);
        func_8000BC48_main(D_80112368_mstory4[i], 0x4000);
        func_8000BB94_main(D_80112368_mstory4[i]);
    }
}

void func_8010EF00_mstory4(s32 i) {
    func_8000BB54_main(D_80112368_mstory4[i]);
}

void func_8010EF28_mstory4(s32 i) {
    func_8000BB94_main(D_80112368_mstory4[i]);
}

void func_8010EF50_mstory4(s32 i, s16 arg1) {
    func_8000BBFC_main(D_80112368_mstory4[i], arg1);
}

void func_8010EF80_mstory4(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        func_8000BB94_main(D_80112368_mstory4[i]);
        func_8000C184_main(D_80112368_mstory4[i]);
        HuSprKill(D_80112358_mstory4[i]);
    }
    HuPrcSleep(3);
}

void func_8010F010_mstory4(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        func_8000BB94_main(D_80112368_mstory4[i]);
        func_8000C184_main(D_80112368_mstory4[i]);
        HuSprKill(D_80112358_mstory4[i]);
        HuPrcSleep(3);
    }
}

void func_8010F0A0_mstory4(void) {
    func_8000BB94_main(D_80112368_mstory4[7]);
    func_8000C184_main(D_80112368_mstory4[7]);
    HuSprKill(D_80112358_mstory4[7]);
}

void func_8010F0E0_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[0].obj;

    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
}

void func_8010F12C_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[0].obj;

    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
}

void func_8010F178_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;

    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001ACDC_main(obj->model[1]);
    func_8001ACDC_main(obj->model[3]);
    func_8001ACDC_main(obj->model[4]);
    func_8001ACDC_main(obj->model[5]);
}

const char D_80111FF8_mstory4[] = "c221_000-body";

/* the eight picture files */
const s32 D_80112008_mstory4[8] = { 0x1D0017, 0x1D0015, 0x1D0018, 0x1D0019, 0x1D001A, 0x1D001B, 0x1D001C, 0x1D0016 };

/* debug camera: the D-pad and C buttons move the camera position and target (Z held: x only),
   printed on screen; never returns */
void func_8010F1F4_mstory4(void) {
    while (TRUE) {
        if (D_800CDA7C_main[0] & 0x2000) {
            if (D_800CDA7C_main[0] & 0x100) {
                D_80111AD0_mstory4.x -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x200) {
                D_80111AD0_mstory4.x += 10.0f;
            }
        } else {
            if (D_800CDA7C_main[0] & 0x800) {
                D_80111AD0_mstory4.z -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x400) {
                D_80111AD0_mstory4.z += 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x100) {
                D_80111AD0_mstory4.y -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x200) {
                D_80111AD0_mstory4.y += 10.0f;
            }
        }
        if (D_800CDA7C_main[0] & 0x2000) {
            if (D_800CDA7C_main[0] & 1) {
                D_80111ADC_mstory4.x -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 2) {
                D_80111ADC_mstory4.x += 10.0f;
            }
        } else {
            if (D_800CDA7C_main[0] & 8) {
                D_80111ADC_mstory4.z -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 4) {
                D_80111ADC_mstory4.z += 10.0f;
            }
            if (D_800CDA7C_main[0] & 1) {
                D_80111ADC_mstory4.y -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 2) {
                D_80111ADC_mstory4.y += 10.0f;
            }
        }
        sprintf(D_800D5218_main, "POSX   :[%f]", D_80111AD0_mstory4.x);
        print8(24, 128, D_800D5218_main);
        sprintf(D_800D5218_main, "POSY   :[%f]", D_80111AD0_mstory4.y);
        print8(24, 136, D_800D5218_main);
        sprintf(D_800D5218_main, "POSZ   :[%f]", D_80111AD0_mstory4.z);
        print8(24, 144, D_800D5218_main);
        sprintf(D_800D5218_main, "INTERX :[%f]", D_80111ADC_mstory4.x);
        print8(24, 160, D_800D5218_main);
        sprintf(D_800D5218_main, "INTERY :[%f]", D_80111ADC_mstory4.y);
        print8(24, 168, D_800D5218_main);
        sprintf(D_800D5218_main, "INTERZ :[%f]", D_80111ADC_mstory4.z);
        print8(24, 176, D_800D5218_main);
        HuPrcVSleep();
    }
}

void func_8010F588_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;

    func_8010EF00_mstory4(1);
    D_80111AD0_mstory4.x = 1720.0f;
    D_80111AD0_mstory4.y = 4000.0f;
    D_80111AD0_mstory4.z = 4000.0f;
    D_80111ADC_mstory4.x = 140.0f;
    D_80111ADC_mstory4.y = 1000.0f;
    D_80111ADC_mstory4.z = 500.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj->model[6], 0.0f, 0.0f, 0.0f);
    HuAudFXPlay(0x225);
    func_8010E7C0_mstory4(obj, 0.0f, 3000.0f, 0.0f, 100, 0);
}

/* actor 1's model 6 rises and its body spins up, with the smoke effect */
void func_8010F660_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;
    s32 i;
    MsPart *part;
    f32 speed;

    D_80112326_mstory4 = func_80110394_mstory4(0xB0004, 0x689);
    func_80110888_mstory4(D_80112326_mstory4, 7.0f, 50.0f, 12.0f);
    func_801104D4_mstory4(D_80112326_mstory4, 120.0f);
    func_800138EC_main(D_80112326_mstory4, 1, 0);
    func_8001C258_main(D_80112326_mstory4, 4, 4);
    func_8010EF28_mstory4(1);
    func_8010EF00_mstory4(0);
    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 0.0f;
    D_80111AD0_mstory4.z = 500.0f;
    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = 0.0f;
    D_80111ADC_mstory4.z = 0.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj->model[6], 0.0f, -100.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[6], 1.0f, 1.0f, 1.0f);
    func_8002FD8C_main(obj->model[6], HmfModelData[obj->model[6]].unk02, D_80111FF8_mstory4, 0x4C, 0x46);
    func_8010EA34_mstory4(obj, 0.0f, 50.0f, 0.0f, 40, 0);
    speed = 0.0f;
    HuPrcSleep(20);
    part = func_8001D33C_main(obj->model[6], D_80111FF8_mstory4);
    part->rotY = D_80111B90_mstory4;
    part->unk3C = D_80111B90_mstory4;
    HuAudFXPlay(0x226);
    for (i = 0; i < 80; i++) {
        if (i == 30) {
            func_800138EC_main(D_80112326_mstory4, 1, 1);
            func_8001C258_main(D_80112326_mstory4, 4, 0);
        }
        D_80111B90_mstory4 += speed;
        speed += 1.0f;
        if (speed > 30.0f) {
            speed = 40.0f;
        }
        part->rotY = D_80111B90_mstory4;
        part->unk3C = D_80111B90_mstory4;
        HuPrcVSleep();
    }
    func_8002FDCC_main(obj->model[6], HmfModelData[obj->model[6]].unk02, D_80111FF8_mstory4, 0x4C, 0x46);
    D_80111B90_mstory4 = 0.0f;
}

// masked 0, raw 5: retail builds the sprite slot address in s0, KMC in a temp (tried: spr = base; spr += k,
// and a plain store then spr = &D[k]; both worse); for the permuter
#ifdef NON_MATCHING
/* the sparkle sprites (one per point of the six groups), the picture sequence 2..7 faded in,
   then the sparkles shown one by one */
void func_8010F910_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;
    s16 *spr;
    void *file;
    s32 k;
    s32 i;
    s32 j;

    file = DataRead(0x1D001D);
    k = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < D_80112088_mstory4[i].count; j++) {
            D_801123A4_mstory4 = func_80055810_main(file);
            *(spr = &D_80112378_mstory4[k]) = InitEspriteSlot(D_801123A4_mstory4, 0, 1);
            func_8000BBD4_main(*spr, D_80112088_mstory4[i].pos[j][0], D_80112088_mstory4[i].pos[j][1]);
            k++;
            func_8000BC48_main(*spr, 0x1000);
            func_8000BEAC_main(*spr, 0xFF, 0xFF, 0xDC);
            func_8000BC48_main(*spr, 8);
            func_8000BBFC_main(*spr, 0xFF);
            func_8000BB94_main(*spr);
        }
    }
    HuMemMemoryFreePerm(file);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8010EF28_mstory4(0);
    func_8010EF00_mstory4(1);
    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 40.0f;
    D_80111AD0_mstory4.z = 310.0f;
    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = -270.0f;
    D_80111ADC_mstory4.z = -180.0f;
    HuPrcVSleep();
    HuPrcSleep(90);
    func_800138EC_main(D_80112326_mstory4, 1, 0);
    HuPrcSleep(10);
    HuAudFXPlay(0x24E);
    for (j = 1; j < 7; j++) {
        func_8010EF00_mstory4(j + 1);
        func_8010EF50_mstory4(j + 1, 0);
        for (i = 0; i < D_801120B8_mstory4[j]; i++) {
            func_8010EF50_mstory4(j + 1, 256.0f / D_801120B8_mstory4[j] * i);
            HuPrcVSleep();
        }
        func_8010EF28_mstory4(j);
        func_8010EF50_mstory4(j + 1, 256);
    }
    HuAudFXPlay(0x227);
    k = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < D_80112088_mstory4[i].count; j++) {
            spr = &D_80112378_mstory4[k];
            func_8000BD94_main(*spr, 0, 0);
            func_8000BDDC_main(*spr, 1);
            k++;
            func_8000BB54_main(*spr);
            HuPrcSleep(1);
        }
    }
    func_8010F010_mstory4();
    HuPrcSleep(129);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C8050", func_8010F910_mstory4);
#endif

void func_8000BB94_main(u16);           /* extern */
void func_8000C184_main(u16);
void func_80017954_main(s16, s16, s16, s16);;
void Hu3DModelRotSet(s16, f32, f32, f32);                           /* extern */
void func_800E4F50_name_81(u8 *rom); /* extern */
void MBDBackCreate(s32, s32);                                       /* extern */
void func_8010F0A0_mstory4(void);                            /* extern */
void func_80110270_mstory4(void);                            /* extern */
void func_80110DB0_mstory4(f32, f32, f32, s16);              /* extern */

typedef struct UnkModel {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ char unk_04[0x14];
    /* 0x18 */ omObjData *obj2;
} UnkModel; // sizeof 0x14

extern s16 D_80112330_mstory4;

#ifdef NON_MATCHING
void func_8010FC98_mstory4(void) {
    omObjData *temp_s5;
    omObjData *temp_s7;
    s32 temp_s4;
    s32 var_a3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0;
    u16 temp_fp;
    u16 *temp_s0;
    s32 i, j;

    temp_s5 = D_801122A0_mstory4[0].obj;
    temp_s7 = D_801122A0_mstory4[1].obj;
    temp_fp = temp_s5->model[1];
    Hu3DCamSetPerspective(0, 40.0f, 80.0f, 8000.0f);

    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 190.0f;
    D_80111AD0_mstory4.z = 3770.0f;

    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = 130.0f;
    D_80111ADC_mstory4.z = 450.0f;

    D_80111AC4_mstory4 = 1;
    var_s3 = 0;
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackCreate(0x20, 0);
    func_8010EF28_mstory4(7);
    for (i = 0; i < 6; i++) {
        // if (D_80112088_mstory4[i].count > 0) {
        for (j = 0, temp_s4 = D_80112088_mstory4[i].count; j < temp_s4; var_s3++, j++) {
            func_8000BD94_main(D_80112378_mstory4[var_s3], 0, 0);
            func_8000BDDC_main(D_80112378_mstory4[var_s3], 1);
            func_8000BB94_main(D_80112378_mstory4[var_s3]);
            func_8000C184_main(D_80112378_mstory4[var_s3]);
        }
        // }
    }

    HuSprKill(D_801123A4_mstory4);
    func_8010F12C_mstory4();
    func_8001C5B4_main(temp_s5->model[1], temp_s5->motion[13]);
    func_8001C814_main(temp_s5->model[1], 2, 2);
    Hu3DModelPosSet(temp_s5->model[1], 0.0f, 0.0f, 2220.0f);
    Hu3DModelPosSet(temp_s5->model[2], 0.0f, -5.0f, 2220.0f);
    Hu3DModelRotSet(temp_s5->model[1], 0, 0, 0);
    Hu3DModelScaleSet(temp_s5->model[1], 1.5f, 1.5f, 1.5f);
    Hu3DModelScaleSet(temp_s5->model[2], 1.5f, 1.5f, 1.5f);
    HuPrcVSleep();
    func_8010F0A0_mstory4();
    HuPrcSleep(30);
    func_8001C258_main(temp_s7->model[6], 4, 0);
    Hu3DModelPosSet(temp_s7->model[6], 0.0f, 1000.0f, 2120.0f);
    Hu3DModelRotSet(temp_s7->model[6], 0, 0, 0);
    Hu3DModelScaleSet(temp_s7->model[6], 1.5f, 1.5f, 1.5f);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2120.0f, 0x3C, 0);
    D_80111B8C_mstory4 = 0;
    HuPrcSleep(20);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[0]].unk02, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 180.0f, 0.0f, 8);
    HuPrcSleep(20);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7E);
    func_80106CA8_mstory4();
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[4]].unk02, 0, 0xA, 0);
    func_801074AC_mstory4(temp_fp);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[0]].unk02, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 0.0f, 0.0f, 0xA);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[11]].unk02, 0, 0xA, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_8010724C_mstory4(temp_s5, 0.0f, 0.0f, 2930.0f, 0x28, 0);
    func_8011196C_mstory4(0);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[0]].unk02, 0, 0xA, 2);
    HuPrcSleep(20);
    CharFXPlay(0x2C6, GwStory.unk1);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[2]].unk02, 0, 0xA, 0);
    func_80017954_main(temp_fp, 2, GwStory.unk1, D_80112330_mstory4);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2500.0f, 0x14, 0);
    func_801074AC_mstory4(temp_fp);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[3]].unk02, 0, 0xA, 2);
    func_80110270_mstory4();
    HuPrcVSleep();
    for (i = 0; i < 4; i++) {
        func_80110DB0_mstory4(0.0f, 400.0f, 2500.0f, i << 3);
        HuPrcSleep(2);
    }
}

#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C8050", func_8010FC98_mstory4);
#endif

/* the character's name plate sprites */
void func_80110270_mstory4(void) {
    s8 chr = GwStory.unk1;
    s8 i;

    D_801123A6_mstory4[0] = InitEspriteSlot(func_8000B838_main(D_801120D4_mstory4[chr]), 0, 0);
    D_801123A6_mstory4[1] = InitEspriteSlot(func_8000B838_main(0x1D001E), 0, 0);
    for (i = 0; i < 2; i++) {
        func_8000BBD4_main(D_801123A6_mstory4[i], D_801120F4_mstory4[chr][i] + D_80112114_mstory4[i] / 2, 194);
    }
}

/* a smoke effect model (file, its draw priority) with its update object, emitting from the
   origin with a spread of 100 and no time limit */
s16 func_80110394_mstory4(s32 file, s32 prio) {
    omObjData *obj;
    s16 model;
    StFxWork *work;

    obj = omAddObj(1000, 0, 0, -1, func_80110528_mstory4);
    model = func_801108FC_mstory4(file, prio);
    obj->work[0] = model;
    work = (StFxWork *)HmfModelData[model].unkBC;
    work->center.x = work->center.y = work->center.z = 0.0f;
    work->flags |= 1;
    work->spread = 100.0f;
    work->timer = -1.0f;
    return model;
}

void func_80110460_mstory4(s16 model, f32 x, f32 y, f32 z) {
    StFxWork *work = (StFxWork *)HmfModelData[model].unkBC;

    work->center.x = x;
    work->center.y = y;
    work->center.z = z;
}

void func_80110494_mstory4(s16 model, s16 time) {
    ((StFxWork *)HmfModelData[model].unkBC)->timer = time;
}

void func_801104D4_mstory4(s16 model, f32 spread) {
    ((StFxWork *)HmfModelData[model].unkBC)->spread = spread;
}

void func_80110500_mstory4(s16 model) {
    func_800138EC_main(model, 5, 4);
}

/* the effect's object: once stopped (flag 4) it kills the model when no particle is left; the
   timer stops emitting; while emitting it spawns one particle a frame */
void func_80110528_mstory4(omObjData *obj) {
    s16 model = obj->work[0];
    StFxHmf *hmf = (StFxHmf *)HmfModelData[model].hmf;
    StFxWork *work = (StFxWork *)HmfModelData[model].unkBC;
    StFxPart *part;
    s16 i;
    f32 dx;
    f32 dz;

    if (work->flags & 4) {
        part = work->parts;
        for (i = 0; i < hmf->groupCount; i++, part++) {
            if (part->life > 0.0f) {
                break;
            }
        }
        if (i == hmf->groupCount) {
            func_8001ACDC_main(model);
            omDelObj(obj);
            return;
        }
        work->flags &= ~1;
    }
    if (work->timer >= 0.0f) {
        work->timer -= 1.0f;
        if (work->timer <= 0.0f) {
            work->flags &= ~1;
        }
    }
    if (work->flags & 1) {
        dx = rand8() * work->spread / 256.0f - work->spread / 2.0f;
        dz = rand8() * work->spread / 256.0f - work->spread / 2.0f;
        func_80110724_mstory4(model, dx + work->center.x, work->center.y, dz + work->center.z);
    }
}

/* starts a free particle at (x, y, z) with 70..100% of the effect's life; 0 if none is free */
s32 func_80110724_mstory4(s16 model, f32 x, f32 y, f32 z) {
    StFxHmf *hmf = (StFxHmf *)HmfModelData[model].hmf;
    StFxWork *work = (StFxWork *)HmfModelData[model].unkBC;
    StFxPart *part = work->parts;
    s16 i;

    for (i = 0; i < hmf->groupCount; i++, part++) {
        if (part->life <= 0.0f) {
            part->pos.x = x;
            part->pos.y = y;
            part->pos.z = z;
            part->life = part->scale = work->life * 0.7f + work->life * 0.3f * (((u8)(rand8() % 10) + 1) * 0.1f);
            return 1;
        }
    }
    return 0;
}

void func_80110888_mstory4(s16 model, f32 life, f32 decay, f32 rise) {
    StFxHmf *hmf = (StFxHmf *)HmfModelData[model].hmf;
    StFxWork *work = (StFxWork *)HmfModelData[model].unkBC;
    StFxPart *part = work->parts;
    s16 i;

    work->life = life;
    work->decay = decay;
    for (i = 0; i < hmf->groupCount; i++, part++) {
        part->vel.y = -rise;
    }
}

s16 func_801108FC_mstory4(s32 file, s32 prio) {
    s16 model;
    StFxHmf *hmf;
    StFxWork *work;
    StFxPart *part;
    s16 i;

    model = func_80110B4C_mstory4(file, prio);
    func_80013390_main(model, -1, NULL, func_801109EC_mstory4);
    hmf = (StFxHmf *)HmfModelData[model].hmf;
    work = (StFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->life = 5.0f;
    work->decay = 20.0f;
    for (i = 0; i < hmf->groupCount; i++, part++) {
        part->vel.x = part->vel.z = part->pos.x = part->pos.y = part->pos.z = 0.0f;
        part->vel.y = -10.0f;
        part->life = part->scale = 0.0f;
    }
    return model;
}

/* the effect's per-frame particle update (hmfman hook) */
void func_801109EC_mstory4(s16 model) {
    StFxHmf *hmf = (StFxHmf *)HmfModelData[model].hmf;
    StFxWork *work = (StFxWork *)HmfModelData[model].unkBC;
    StFxPart *part = work->parts;
    s16 count = hmf->groupCount;
    s16 i;

    for (i = 0; i < count; i++, part++) {
        if (part->life > 0.0f) {
            part->pos.x = part->pos.x * 0.04f + part->vel.x + part->pos.x;
            part->pos.y = part->pos.y + part->vel.y;
            part->pos.z = part->pos.z * 0.04f + part->vel.z + part->pos.z;
            part->life -= work->life / work->decay;
            if (part->life <= 0.0f) {
                part->life = 0.0f;
            }
            part->scale = (D_80111BFC_mstory4[(work->frame + i) & 3] * 0.15f + 1.0f) * part->life;
        }
    }
    work->frame++;
}

s16 func_80110B4C_mstory4(s32 file, s32 prio) {
    s16 model = func_8000B108_main(file, prio);

    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    return model;
}

/* actor 1's action: model 1 hops three times while turning towards 230 degrees */
void func_80110BB4_mstory4(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec start;
    Vec rot;
    f32 h;
    f32 turn;
    s32 i;

    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    pos.y = HmfModelData[model].pos.y;
    rot.x = HmfModelData[model].rot.x;
    rot.y = HmfModelData[model].rot.y;
    rot.z = HmfModelData[model].rot.z;
    turn = (230.0f - rot.y) / 12.0f;
    for (i = 0; i < 12; i++) {
        pos.x = HmfModelData[model].pos.x;
        pos.z = HmfModelData[model].pos.z;
        h = sindf(i * 15.0f) * 80.0f;
        rot.y += turn;
        Hu3DModelPosSet(model, pos.x, h + pos.y, pos.z);
        Hu3DModelRotSet(model, rot.x, h + rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, start.x, start.y, start.z);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_80110D5C_mstory4(omObjData *obj) {
    HuPrcSleep(30);
    func_80107480_mstory4(obj, -30.0f, -45.0f, 0.0f, 30);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

/* starts func_80110E3C_mstory4 at (x, y, z) with the given delay */
void func_80110DB0_mstory4(f32 x, f32 y, f32 z, s16 delay) {
    Process *prc;
    StSparkWork *work;

    prc = omAddPrcObj(func_80110E3C_mstory4, 0x3F00, 0x2000, 0);
    work = HuMemAllocTag(sizeof(StSparkWork), 0x7918);
    prc->user_data = work;
    work->pos.x = x;
    work->pos.y = y;
    work->pos.z = z;
    work->delay = delay;
    work->time = 0;
}

// scheduling: retail reads the sindf results without a nop and keeps the face-table load earlier (raw 18, masked 13)
#ifdef NON_MATCHING
/* a firework process: after work->delay frames, launches a shell from work->pos on an arc to
   alternate sides every 25 frames and bursts it (3 in 4 times with a flash model), forever */
void func_80110E3C_mstory4(void) {
    StSparkWork *work;
    s16 models[3];
    s16 model;
    s16 n;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    HmfData *hmf;
    StBurstObj *obj;
    StBurstPart *part;
    s16 i;
    s16 j;
    s16 count;
    f32 dist;
    f32 height;
    f32 depth;
    f32 t;
    f32 a;
    f32 x;
    f32 y;
    f32 z;

    work = HuPrcCurrentGet()->user_data;
    models[0] = model = func_8000B108_main(0xB0034, 0x28C);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    hmf = HmfModelData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        obj = &((StBurstObj *)hmf->unk60)[j];
        n = obj->faceCount;
        face = obj->faces;
        for (i = 0; i < n; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    HuPrcVSleep();
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_80111740_mstory4);
    func_800138EC_main(model, 8, 8);
    func_80013954_main(model, 0);
    part = ((StBurstWork *)HmfModelData[model].unkBC)->parts;
    count = ((StFxHmf *)hmf)->groupCount;
    for (i = 0; i < count; i++, part++) {
        part->scale = part->pos.x = part->pos.y = part->pos.z = 0.0f;
    }
    HuPrcVSleep();
    models[1] = func_8000B108_main(0xB004B, 0x29D);
    func_8001C814_main(models[1], 2, 2);
    Hu3DModelScaleSet(models[1], 0.2f, 0.2f, 0.2f);
    models[2] = func_8000B108_main(0xB004C, 0x29D);
    Hu3DModelScaleSet(models[2], 0.4f, 0.4f, 0.4f);
    HuPrcSleep(work->delay);
    func_8001C258_main(model, 4, 0);
    while (TRUE) {
        HuPrcVSleep();
        dist = ((s32)((u32)(rand8() * 25) >> 7) + 100.0f) * D_80111C00_mstory4;
        height = ((rand8() * 75) >> 7) + 50;
        depth = (rand8() * 75) >> 7;
        dist = 2.0f * dist;
        height = 2.0f * height;
        depth = 2.0f * depth;
        D_80111C00_mstory4 = -D_80111C00_mstory4;
        func_8001C258_main(models[1], 4, 0);
        for (i = 0; i < 21; i++) {
            t = i / 20.0f;
            a = t * 90.0f;
            x = dist * sindf(a) + work->pos.x;
            y = height * sindf(t * 135.0f + 45.0f) - height * sindf(45.0f) + work->pos.y;
            z = depth * sindf(a) + work->pos.z;
            Hu3DModelPosSet(models[1], x, y, z);
            HuPrcVSleep();
        }
        func_8001C258_main(models[1], 4, 4);
        HuPrcSleep(5);
        if (rand8() & 3) {
            func_8001C258_main(models[2], 4, 0);
            func_8001C6A8_main(models[2], 0.0f);
            func_8001C92C_main(models[2], 3.0f);
            Hu3DModelPosSet(models[2], x, y, z);
            for (i = 0; i < 8; i++) {
                func_80111430_mstory4(model, x, y, z, count / 8, i & 3);
                HuPrcVSleep();
            }
            func_8001C258_main(models[2], 4, 4);
        } else {
            for (i = 0; i < 8; i++) {
                func_80111430_mstory4(model, x, y, z, count / 8, i & 3);
                HuPrcVSleep();
            }
        }
        HuPrcSleep(25);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C8050", func_80110E3C_mstory4);
#endif

// decomp-permuter
void func_80111430_mstory4(s16 model, f32 x, f32 y, f32 z, s16 count, s32 mode)
{
  f32 step = 360.0f / count;
  StFxHmf *hmf = (StFxHmf *) HmfModelData[model].hmf;
  StBurstPart *part = ((StBurstWork *) HmfModelData[model].unkBC)->parts;
  s16 total = hmf->groupCount;
  f32 ax;
  f32 ay;
  f32 az;
  f32 len;
  f32 a;
  short color;
  s16 n;
  s16 i;
  if (mode != 0)
  {
    while (1)
    {
      ax = rand8() - 128;
      ay = rand8() - 128;
      az = rand8() - 128;
      len = ((ax * ax) + (ay * ay)) + (az * az);
      if (len != 0.0f)
      {
        break;
      }
    }

  }
  else
  {
    ax = 0.0f;
    ay = 0.0f;
    az = 1.0f;
    len = 1.0f;
  }
  len = HuSqrtf(len);
  ax /= len;
  ay /= len;
  az /= len;
  color = (u8) (rand8() & 3);
  for (n = 0, i = 0; i < total; i++, part++)
  {
    if (part->scale <= 0.0f)
    {
      part->pos.x = x;
      part->pos.y = y;
      part->pos.z = z;
      a = step * n;
      part->dir.x = ((ax * ay) * (1.0f - cosdf(a))) - (az * sindf(a));
      part->dir.y = (ay * ay) + ((1.0f - (ay * ay)) * cosdf(a));
      part->dir.z = ((ay * az) * (1.0f - cosdf(a))) + (ax * sindf(a));
      part->color = color;
      part->time = 0.0f;
      part->scale = 1.0f;
      part->speed = 20.0f;
      n++;
      if (n >= count)
      {
        break;
      }
    }
  }

}

/* the burst's per-frame particle update (hmfman hook): colour, move, slow down, shrink */
void func_80111740_mstory4(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    StBurstWork *work = (StBurstWork *)HmfModelData[model].unkBC;
    StBurstPart *part;
    s16 count;
    s16 i;
    s16 color;
    f32 sx;
    f32 sy;
    f32 sz;

    if (work->motion == -1) {
        count = ((StFxHmf *)hmf)->groupCount;
    } else {
        count = ((StBurstObj *)hmf->unk60)[work->motion].unk2E;
    }
    part = work->parts;
    if (work->frame >= 50) {
        if (!(work->flags & 1)) {
            return;
        }
        work->frame = 0;
    }
    for (i = 0; i < count; i++, part++) {
        if (part->scale > 0.0f) {
            color = part->color;
            part->time += 1.0f;
            part->rgb[0] = (*(D_80111C04_mstory4 + color))[0];
            part->rgb[1] = (*(D_80111C04_mstory4 + color))[1];
            part->rgb[2] = (*(D_80111C04_mstory4 + color))[2];
            sx = part->dir.x * part->speed;
            sy = part->dir.y * part->speed;
            sz = part->dir.z * part->speed;
            part->pos.x = sx + part->pos.x;
            part->pos.y = sy + part->pos.y;
            part->pos.z = sz + part->pos.z;
            part->speed *= 0.9f;
            part->scale -= 0.05f;
        }
    }
}

/* starts actor i's voice `se` once (actor 0 plays it as the story character's) */
void func_801118F8_mstory4(s32 i, s32 se) {
    if (D_801122A0_mstory4[i].unk0C == 0) {
        D_801122A0_mstory4[i].unk0C = 1;
        D_801122A0_mstory4[i].unk10 = se;
        if (i == 0) {
            D_801122A0_mstory4[0].unk14 = CharFXPlay(se, GwStory.unk1);
        }
    }
}

void func_8011196C_mstory4(s32 i) {
    if (D_801122A0_mstory4[i].unk0C == 1) {
        D_801122A0_mstory4[i].unk0C = 0;
        if (i == 0) {
            HuAudFXStop((s16)D_801122A0_mstory4[0].unk14);
        }
    }
}

/* replays actor 0's voice each time its motion restarts, while it is on */
void func_801119C0_mstory4(void) {
    s32 i;
    s32 se;

    while (TRUE) {
        for (i = 0; i < 3; i++) {
            if (D_801122A0_mstory4[i].unk0C == 1 && HmfModelData[D_801122A0_mstory4[i].obj->model[1]].unk40 == 0.0f) {
                se = D_801122A0_mstory4[i].unk10;
                if (i == 0) {
                    D_801122A0_mstory4[0].unk14 = CharFXPlay(se, GwStory.unk1);
                }
            }
        }
        HuPrcVSleep();
    }
}

const StSparkGroup D_80112088_mstory4[6] = {
    { 4, D_80111BA4_mstory4 }, { 5, D_80111BB4_mstory4 }, { 4, D_80111BC8_mstory4 },
    { 3, D_80111BD8_mstory4 }, { 3, D_80111BE4_mstory4 }, { 3, D_80111BF0_mstory4 },
};
const s32 D_801120B8_mstory4[7] = { 8, 8, 8, 8, 8, 8, 24 };
const s32 D_801120D4_mstory4[8] = { 0x1D001F, 0x1D0020, 0x1D0021, 0x1D0022, 0x1D0023, 0x1D0024, 0x1D001F, 0x1D001F };
const s16 D_801120F4_mstory4[8][2] = { { 25, 98 }, { 25, 92 }, { 25, 100 }, { 25, 97 }, { 25, 98 }, { 25, 81 }, { 25, 98 }, { 25, 98 } };
const s16 D_80112114_mstory4[2] = { 78, 190 }; /* name plate widths */

/* .data */
s32 D_80111B80_mstory4 = 0;
s32 D_80111B84_mstory4 = 0;
s32 D_80111B88_mstory4 = 0;
s32 D_80111B8C_mstory4 = 1;
f32 D_80111B90_mstory4 = 0.0f; /* the body spin */
const char *D_80111B94_mstory4[4] = { D_80111FC8_mstory4, D_80111FB8_mstory4, D_80111FA8_mstory4, D_80111F98_mstory4 };
/* sparkle points (x, y) of the six groups */
s16 D_80111BA4_mstory4[4][2] = { { 147, 99 }, { 135, 111 }, { 126, 141 }, { 186, 39 } };
s16 D_80111BB4_mstory4[5][2] = { { 175, 64 }, { 174, 92 }, { 161, 113 }, { 154, 136 }, { 139, 155 } };
s16 D_80111BC8_mstory4[4][2] = { { 193, 78 }, { 189, 105 }, { 173, 127 }, { 167, 158 } };
s16 D_80111BD8_mstory4[3][2] = { { 215, 112 }, { 206, 130 }, { 188, 141 } };
s16 D_80111BE4_mstory4[3][2] = { { 229, 122 }, { 221, 146 }, { 202, 169 } };
s16 D_80111BF0_mstory4[3][2] = { { 246, 119 }, { 236, 156 }, { 225, 174 } };
u8 D_80111BFC_mstory4[4] = { 0, 1, 2, 1 }; /* particle size wobble */
s16 D_80111C00_mstory4 = 1; /* the firework's side, flipped each launch */
s16 D_80111C02_mstory4 = 0; /* unreferenced */
u8 D_80111C04_mstory4[4][3] = { { 0xFF, 0x20, 0x40 }, { 0xFF, 0xFF, 0x40 }, { 0x40, 0xC0, 0xC0 }, { 0xFF, 0xFF, 0xFF } };
