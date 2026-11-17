#include "common.h"

// story u3
#include "mallocblock.h"
/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry), as mstory1's. */
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

/* a story-scene actor: its object and the action its process runs every frame */
typedef struct Story3Actor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08; /* set to 1 by the actor when its action is done */
    /* 0x0C */ s32 unk0C; /* 1: play the step sound unk10 on frame 0 of the walk */
    /* 0x10 */ s32 unk10; /* step sound (read as an s16 at +0x12) */
} Story3Actor; /* size = 0x14 */

/* a model part looked up by name (func_8001D33C_main) */
typedef struct Story3HmfPart {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ Vec scale;
    /* 0x28 */ char unk28[0x18];
    /* 0x40 */ Vec scale2;
} Story3HmfPart;

typedef struct Story3Motions {
    s32 v[8][4];
} Story3Motions;

extern Story3Actor D_80115CB0_mstory3[11];
extern s16 D_80115D8C_mstory3; /* shadow model, linked by the actors */
extern s16 D_80115D8E_mstory3; /* actor 3's texture-animation slot */
extern s16 D_80115D90_mstory3[4]; /* actor 3's texture animations */
extern s16 D_80115D98_mstory3[5]; /* actor 0's texture animations */
extern s16 D_80115DA2_mstory3; /* actor 0's texture-animation slot */
extern s16 D_80115DA4_mstory3[5]; /* actor 2's texture animations */
extern s16 D_80115DAE_mstory3; /* actor 2's texture-animation slot */
extern s16 D_80115DB0_mstory3; /* the player's character */
extern Vec D_80115740_mstory3;
extern Vec D_8011574C_mstory3;
extern Vec D_80115758_mstory3;
extern Vec D_80115764_mstory3;
extern Vec D_80115770_mstory3;
extern Vec D_8011577C_mstory3;
extern Vec D_80115788_mstory3;
extern Vec D_80115794_mstory3;
extern Vec D_801157A0_mstory3;
extern Vec D_801157AC_mstory3;
extern Vec D_801157B8_mstory3;
extern Vec D_801157C4_mstory3;
extern Vec D_801157D0_mstory3;
extern Vec D_801157DC_mstory3;
extern Vec D_801157E8_mstory3;
extern Vec D_801157F4_mstory3;
extern Story3Motions D_80115800_mstory3;
extern Vec D_801153B0_mstory3;
extern Vec D_801153BC_mstory3;
extern Vec D_801153C8_mstory3;
extern Vec D_801153D4_mstory3;
extern char *D_801153E0_mstory3[]; /* per character: its texture-animation name */
extern char D_8011588C_mstory3[]; /* "c300l_0_DEF" */
extern const Vec D_801158E0_mstory3;
extern const Vec D_80115908_mstory3;
extern const Vec D_80115914_mstory3;
extern const Vec D_80115920_mstory3;
extern const Vec D_8011592C_mstory3;
extern const Vec D_80115938_mstory3;
extern const Vec D_80115944_mstory3;
extern const Vec D_80115950_mstory3;
extern const Vec D_8011595C_mstory3;
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
void func_80032FC0_main(s16, s32, s32);
s16 func_800329B4_main(void *);
void func_8000CFA4_main(s16, f32, f32, f32);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void *func_8001D33C_main(s16, const char *);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);

void func_80105E8C_mstory3(void);
void func_80105F54_mstory3(void);
void func_8010603C_mstory3(void);
void func_8010606C_mstory3(void);
void func_80106090_mstory3(s32 mess);
void func_801060E4_mstory3(s32 mess);
void func_801061C4_mstory3(void);
void func_80106220_mstory3(void);
void func_80106284_mstory3(void);
void func_80106400_mstory3(s32 arg0);
s32 func_80106CDC_mstory3(void);
void func_80106CF0_mstory3(s16 model, s16 anim, s16 frame);
void func_80106DC4_mstory3(omObjData *obj, Vec *to, s32 frames);
void func_80106DE0_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80107070_mstory3(omObjData *obj, Vec *to, s32 frames);
void func_80107218_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107244_mstory3(s16 model);
void func_8010733C_mstory3(omObjData *obj, f32 speed, s16 frames);
void func_801074D8_mstory3(omObjData *obj, f32 speed, s16 frames);
void func_80107674_mstory3(omObjData *a, omObjData *b);
void func_80107A18_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn);

ObPath *func_8010C9F0_mstory3(Vec *points, s16 flags);
void func_8010CCF4_mstory3(ObPath *path, f32 t, Vec *out);
void func_8010D59C_mstory3(ObPath *path);
void func_8010D774_mstory3(omObjData *obj);
void func_8010D77C_mstory3(void);
void func_8010D974_mstory3(void);
void func_8010D97C_mstory3(void);
void func_8010DA00_mstory3(omObjData *obj);
void func_8010E170_mstory3(omObjData *obj);
void func_8010EBE4_mstory3(omObjData *obj);
void func_8010F658_mstory3(void);
void func_8010F660_mstory3(void);
void func_8010FCA4_mstory3(omObjData *obj);
void func_8010FD64_mstory3(omObjData *obj);
void func_8010FDB0_mstory3(omObjData *obj);
void func_801103E8_mstory3(omObjData *obj);
void func_80110474_mstory3(omObjData *obj);
void func_80110558_mstory3(omObjData *obj);
void func_80110628_mstory3(omObjData *obj);
void func_8011065C_mstory3(omObjData *obj);
void func_8011067C_mstory3(omObjData *obj);
void func_80110774_mstory3(omObjData *obj);
void func_80110978_mstory3(omObjData *obj);
void func_80110998_mstory3(omObjData *obj);
void func_80110A84_mstory3(omObjData *obj);
void func_80110CAC_mstory3(void);
void func_80110CB4_mstory3(void);
void func_80110E30_mstory3(omObjData *obj);
void func_80110F04_mstory3(omObjData *obj);
void func_80110FE8_mstory3(omObjData *obj);
void func_80111064_mstory3(omObjData *obj);
void func_801110AC_mstory3(void);
void func_801110B4_mstory3(void);
/* the other ranges of this unit */
void func_80111500_mstory3(omObjData *obj);
void func_80111764_mstory3(void);
void func_80111A58_mstory3(omObjData *obj);
void func_80111B34_mstory3(omObjData *obj);
void func_80111C50_mstory3(omObjData *obj);
void func_80111DF8_mstory3(omObjData *obj);
void func_80111E2C_mstory3(omObjData *obj);
void func_80111FA4_mstory3(omObjData *obj);
void func_8011204C_mstory3(omObjData *obj);
void func_801122C4_mstory3(void);
void func_8011249C_mstory3(void);
void func_801125F8_mstory3(omObjData *obj);
void func_801126D8_mstory3(omObjData *obj);
void func_8011289C_mstory3(omObjData *obj);
void func_80112944_mstory3(omObjData *obj);
void func_80112B88_mstory3(void);
void func_80112DA0_mstory3(omObjData *obj);
void func_80112F7C_mstory3(omObjData *obj);
void func_80112FD0_mstory3(omObjData *obj);
void func_801134E0_mstory3(void);
void func_80113968_mstory3(void);
void func_80113BB0_mstory3(void);
void func_80113E68_mstory3(omObjData *obj);
void func_80114260_mstory3(omObjData *obj);
void func_801142C0_mstory3(omObjData *obj);
void func_80114474_mstory3(omObjData *obj);
void func_8011475C_mstory3(omObjData *obj);
void func_801149D0_mstory3(void);
void func_80114B00_mstory3(void);
void func_801115D8_mstory3(omObjData *obj);
void func_80111E4C_mstory3(omObjData *obj);
void func_80111F5C_mstory3(omObjData *obj);
void func_8011272C_mstory3(omObjData *obj);
void func_80112854_mstory3(omObjData *obj);
void func_801130A4_mstory3(omObjData *obj);
void func_8011315C_mstory3(omObjData *obj);
void func_80113668_mstory3(omObjData *obj);
void func_801136E8_mstory3(omObjData *obj);
void func_80113800_mstory3(omObjData *obj);
void func_80113AA8_mstory3(omObjData *obj);
void func_80113B3C_mstory3(omObjData *obj);
void func_80114CD8_mstory3(omObjData *obj);
void func_8011517C_mstory3(omObjData *obj);
// end story u3

ObPath *func_8010C9F0_mstory3(Vec *points, s16 flags) {
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
void func_8010CCF4_mstory3(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010CCF4_mstory3);
#endif

void func_8010D59C_mstory3(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* chapter 3, second scene: set up the actors and their processes */
void func_8010D5CC_mstory3(void) {
    D_80115DB0_mstory3 = GwStory.unk1;
    func_80105F54_mstory3();
    D_80115D8C_mstory3 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010F660_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80110CB4_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801110B4_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80111764_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801122C4_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112B88_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801134E0_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113968_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113BB0_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80114B00_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010D97C_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_8011249C_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801149D0_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010D77C_mstory3, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115D8C_mstory3, 4, 4);
}

void func_8010D774_mstory3(omObjData *obj) {
}

/* step sounds: actors 0, 2 and 1 play theirs on frame 0 of their walk */
void func_8010D77C_mstory3(void) {
    s16 se;
    s32 vol;
    f32 z;

    while (TRUE) {
        if (D_80115CB0_mstory3[0].unk0C == 1 && HmfModelData[D_80115CB0_mstory3[0].obj->model[1]].unk40 == 0.0f) {
            CharFXPlay(D_80115CB0_mstory3[0].unk10, (u8)D_80115DB0_mstory3);
        }
        if (D_80115CB0_mstory3[2].unk0C == 1 && HmfModelData[D_80115CB0_mstory3[2].obj->model[1]].unk40 == 0.0f) {
            se = CharFXPlay(D_80115CB0_mstory3[2].unk10, 6);
            z = HmfModelData[D_80115CB0_mstory3[2].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            func_8004AAD0_main(se, vol);
        }
        if (D_80115CB0_mstory3[1].unk0C == 1 && HmfModelData[D_80115CB0_mstory3[1].obj->model[1]].unk40 == 0.0f) {
            CharFXPlay(D_80115CB0_mstory3[1].unk10, 7);
        }
        HuPrcVSleep();
    }
}

void func_8010D974_mstory3(void) {
}

/* actor 10: the scene director */
void func_8010D97C_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(10, 0, 0, -1, NULL);
    D_80115CB0_mstory3[10].obj = obj;
    D_80115CB0_mstory3[10].unk08 = 0;
    D_80115CB0_mstory3[10].func = func_8010DA00_mstory3;
    omPrcSetDestructor(0, func_8010D974_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[10].func(obj);
        HuPrcVSleep();
    }
}

#define S3A D_80115CB0_mstory3
#define S3MODEL(i) S3A[i].obj->model[1]
#define S3MOT(i, m) HmfModelData[S3A[i].obj->motion[m]].unk02

/* the director, part 1 */
void func_8010DA00_mstory3(omObjData *obj) {
    s16 se;

    HuPrcSleep(30);
    CharFXPlay(0x26B, 7);
    S3A[3].func = func_80111A58_mstory3;
    HuPrcSleep(70);
    S3A[1].func = func_80110E30_mstory3;
    while (TRUE) {
        if (S3A[3].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[3].unk08 = 0;
    func_80106CF0_mstory3(S3MODEL(3), D_80115D8E_mstory3, D_80115D90_mstory3[1]);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5A);
    func_8010606C_mstory3();
    func_80106CF0_mstory3(S3MODEL(3), D_80115D8E_mstory3, D_80115D90_mstory3[0]);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[0].obj, &D_80115758_mstory3, 10);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 0), 0, 10, 0);
    func_80107070_mstory3(S3A[4].obj, &D_80115764_mstory3, 10);
    func_80107070_mstory3(S3A[3].obj, &D_80115770_mstory3, 10);
    HuAudFXPlay(0x159);
    func_8001C624_main(S3MODEL(4), S3MOT(4, 1), 0, 10, 2);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5B);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(4), S3MOT(4, 0), 0, 10, 2);
    func_80107070_mstory3(S3A[4].obj, &D_8011577C_mstory3, 10);
    S3A[8].func = func_80113E68_mstory3;
    func_80107070_mstory3(S3A[3].obj, &D_80115788_mstory3, 10);
    while (TRUE) {
        if (S3A[8].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[0].func = func_8010FDB0_mstory3;
    HuPrcSleep(40);
    func_80107070_mstory3(S3A[3].obj, &D_80115794_mstory3, 50);
    func_80107070_mstory3(S3A[3].obj, &D_801157A0_mstory3, 40);
    while (TRUE) {
        if (S3A[0].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[0].unk08 = 0;
    S3A[0].func = func_8010D774_mstory3;
    func_80107070_mstory3(S3A[0].obj, &D_801157AC_mstory3, 10);
    HuAudSeqPlay(0x72);
    func_80106CF0_mstory3(S3MODEL(0), D_80115DA2_mstory3, D_80115D98_mstory3[3]);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 7), 0, 10, 0);
    func_80107244_mstory3(S3MODEL(0));
    se = CharFXPlay(0x262, (u8)D_80115DB0_mstory3);
    HuPrcSleep(30);
    func_80107070_mstory3(S3A[4].obj, &D_801157B8_mstory3, 3);
    func_80106DC4_mstory3(S3A[4].obj, &D_80115740_mstory3, 5);
    HuAudFXPlay(0x219);
    HuAudFXStop(se);
    func_80106CF0_mstory3(S3MODEL(0), D_80115DA2_mstory3, D_80115D98_mstory3[1]);
    func_8001C258_main(S3A[0].obj->model[4], 4, 0);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 8), 0, 10, 0);
    func_80107070_mstory3(S3A[4].obj, &D_801157C4_mstory3, 3);
    S3A[4].unk08 = 0;
    S3A[3].func = func_80111B34_mstory3;
    func_80106DE0_mstory3(S3A[4].obj, &D_8011574C_mstory3, 10, 0);
    func_80107244_mstory3(S3MODEL(0));
    HuAudSeqPlay(0x26);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[0].obj, &D_801157D0_mstory3, 10);
    func_80106CF0_mstory3(S3MODEL(0), D_80115DA2_mstory3, D_80115D98_mstory3[0]);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 0), 0, 10, 2);
    S3A[8].func = func_801142C0_mstory3;
    func_8001C624_main(S3MODEL(4), S3MOT(4, 1), 0, 10, 2);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5D);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(4), S3MOT(4, 0), 0, 10, 2);
    while (TRUE) {
        if (S3A[8].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[8].unk08 = 0;
    func_8001C624_main(S3MODEL(0), S3MOT(0, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[0].obj, &D_8011577C_mstory3, 10);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 7), 0, 10, 0);
    func_80107244_mstory3(S3MODEL(0));
    S3A[10].func = func_8010E170_mstory3;
}

/* the director, part 2 */
void func_8010E170_mstory3(omObjData *obj) {
    S3A[0].func = func_801103E8_mstory3;
    S3A[3].func = func_80111C50_mstory3;
    S3A[4].func = func_801125F8_mstory3;
    HuAudFXPlay(0x29C);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5E);
    func_8010606C_mstory3();
    S3A[8].func = func_80114260_mstory3;
    S3A[5].func = func_80112DA0_mstory3;
    while (TRUE) {
        if (S3A[5].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[5].unk08 = 0;
    func_8001C624_main(S3MODEL(4), S3MOT(4, 3), 0, 10, 2);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5F);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(4), S3MOT(4, 0), 0, 10, 2);
    HuAudFXPlay(0x29D);
    func_8001C624_main(S3MODEL(5), S3MOT(5, 2), 0, 10, 2);
    HuPrcSleep(5);
    S3A[8].func = func_80114474_mstory3;
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A60);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(0), S3MOT(0, 9), 0, 10, 2);
    func_8001C624_main(S3MODEL(5), S3MOT(5, 3), 0, 10, 2);
    HuPrcSleep(30);
    S3A[3].unk08 = 0;
    S3A[3].func = func_8011204C_mstory3;
    while (TRUE) {
        if (S3A[3].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[3].unk08 = 0;
    HuAudFXPlay(0x2AA);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A61);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(4), S3MOT(4, 3), 0, 10, 2);
    func_8010603C_mstory3();
    HuAudSeqFadeOut(30);
    func_80106090_mstory3(0x5A62);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(4), S3MOT(4, 0), 0, 10, 2);
    S3A[3].unk08 = 1;
    S3A[3].func = func_8011204C_mstory3;
    S3A[4].func = func_80112944_mstory3;
    func_8001C624_main(S3MODEL(0), S3MOT(0, 10), 0, 10, 0);
    func_80107070_mstory3(S3A[5].obj, &D_801157F4_mstory3, 10);
    func_8001C624_main(S3MODEL(5), S3MOT(5, 6), 0, 10, 0);
    func_80107244_mstory3(S3MODEL(5));
    func_8004AAD0_main(CharFXPlay(0x2BD, 6), 0x50);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A63);
    HuAudSeqPlay(0x28);
    func_8010606C_mstory3();
    HuPrcSleep(10);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 0), 0, 10, 2);
    func_8001C624_main(S3MODEL(5), S3MOT(5, 0), 0, 10, 2);
    func_8001C258_main(S3A[2].obj->model[1], 4, 0);
    func_8001C258_main(S3A[2].obj->model[2], 4, 0);
    func_8001C624_main(S3MODEL(2), S3MOT(2, 3), 0, 10, 0);
    HuPrcSleep(5);
    HuAudFXPlay(0x228);
    func_80106284_mstory3();
    S3A[0].func = func_80110628_mstory3;
    S3A[3].func = func_80111DF8_mstory3;
    S3A[4].func = func_801126D8_mstory3;
    S3A[5].func = func_80112F7C_mstory3;
    func_8001C624_main(S3MODEL(2), S3MOT(2, 0), 0, 10, 2);
    HuPrcSleep(10);
    S3A[8].func = func_8011475C_mstory3;
    HuPrcSleep(50);
    S3A[3].func = func_80111B34_mstory3;
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A64);
    func_8010606C_mstory3();
    HuPrcSleep(10);
    func_8001C624_main(S3MODEL(4), S3MOT(4, 1), 0, 10, 2);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A65);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(4), S3MOT(4, 0), 0, 10, 2);
    S3A[3].func = func_80111E2C_mstory3;
    func_8001C624_main(S3MODEL(2), S3MOT(2, 2), 0, 10, 2);
    S3A[1].func = func_80111064_mstory3;
    func_8001C92C_main(S3MODEL(0), 0.25f);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 13), 0, 10, 2);
    S3A[2].unk0C = 1;
    S3A[2].unk10 = 0x28;
    func_80107A18_mstory3(S3A[2].obj, &D_801157DC_mstory3, 180, 1);
    S3A[2].unk0C = 0;
    func_8001C92C_main(S3MODEL(0), 1.0f);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 0), 0, 10, 2);
    func_80106CF0_mstory3(S3MODEL(2), D_80115DAE_mstory3, D_80115DA4_mstory3[3]);
    func_8001C624_main(S3MODEL(2), S3MOT(2, 4), 0, 10, 0);
    func_80107244_mstory3(S3MODEL(2));
    func_80106CF0_mstory3(S3MODEL(2), D_80115DAE_mstory3, D_80115DA4_mstory3[0]);
    HuPrcSleep(30);
    func_8001C624_main(S3MODEL(2), S3MOT(2, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[2].obj, &D_801157E8_mstory3, 10);
    S3A[2].unk0C = 1;
    S3A[2].unk10 = 0x1F;
    func_8010733C_mstory3(S3A[2].obj, 17.0f, 10);
    S3A[2].unk0C = 0;
    func_8001C624_main(S3MODEL(2), S3MOT(2, 7), 0, 10, 0);
    func_80106CF0_mstory3(S3MODEL(0), D_80115DA2_mstory3, D_80115D98_mstory3[2]);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A66);
    func_8010606C_mstory3();
    S3A[0].func = func_8010D774_mstory3;
    S3A[3].func = func_8010D774_mstory3;
    S3A[4].func = func_8010D774_mstory3;
    S3A[5].func = func_80112FD0_mstory3;
    S3A[4].func = func_8011289C_mstory3;
    S3A[3].unk08 = 0;
    S3A[3].func = func_80111FA4_mstory3;
    S3A[0].func = func_8011067C_mstory3;
    S3A[2].func = func_80111500_mstory3;
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A67);
    func_8010606C_mstory3();
    while (TRUE) {
        if (S3A[5].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[5].unk08 = 0;
    S3A[10].func = func_8010EBE4_mstory3;
}

/* the director, part 3 */
void func_8010EBE4_mstory3(omObjData *obj) {
    S3A[4].func = func_8011289C_mstory3;
    S3A[3].func = func_80111FA4_mstory3;
    S3A[0].func = func_80110A84_mstory3;
    func_8001C624_main(S3MODEL(2), S3MOT(2, 7), 0, 10, 0);
    func_80106CF0_mstory3(S3MODEL(2), D_80115DAE_mstory3, D_80115DA4_mstory3[3]);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A69);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(2), S3MOT(2, 0), 0, 10, 2);
    S3A[4].func = func_8011289C_mstory3;
    S3A[3].func = func_80111FA4_mstory3;
    S3A[0].func = func_80110A84_mstory3;
    func_8001C624_main(S3MODEL(5), S3MOT(5, 7), 0, 10, 0);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A6A);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(5), S3MOT(5, 7), 0, 10, 0);
    func_8001C624_main(S3MODEL(2), S3MOT(2, 7), 0, 10, 0);
    HuPrcSleep(10);
    S3A[5].func = func_8011315C_mstory3;
    S3A[9].func = func_80114CD8_mstory3;
    S3A[2].func = func_8011517C_mstory3;
    HuPrcSleep(120);
    S3A[2].unk08 = 1;
    HuPrcSleep(10);
    while (TRUE) {
        if (S3A[9].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[9].unk08 = 0;
    HuPrcSleep(20);
    S3A[2].func = func_8010D774_mstory3;
    func_8001C624_main(S3MODEL(2), S3MOT(2, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[2].obj, &D_801153BC_mstory3, 5);
    func_8001C624_main(S3MODEL(2), S3MOT(2, 0), 0, 10, 2);
    HmfModelData[S3MODEL(2)].rot.y = 0.0f;
    func_8001C624_main(S3MODEL(2), S3MOT(2, 6), 0, 10, 2);
    S3A[0].unk08 = 1;
    S3A[4].unk08 = 1;
    S3A[3].unk08 = 1;
    HuAudFXPlay(0x2C4);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A6C);
    func_8010606C_mstory3();
    HuPrcSleep(5);
    S3A[0].func = func_80110774_mstory3;
    S3A[4].func = func_8011272C_mstory3;
    S3A[3].func = func_80111E4C_mstory3;
    HuAudFXPlay(0x29E);
    S3A[5].func = func_801130A4_mstory3;
    func_8010603C_mstory3();
    func_801060E4_mstory3(0x5A6D);
    func_8010606C_mstory3();
    HuPrcSleep(5);
    S3A[0].func = func_80110774_mstory3;
    S3A[4].func = func_8011272C_mstory3;
    S3A[3].func = func_80111E4C_mstory3;
    func_8001C624_main(S3MODEL(2), S3MOT(2, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[2].obj, &D_801153D4_mstory3, 10);
    func_8001C624_main(S3MODEL(2), S3MOT(2, 0), 0, 10, 2);
    func_8010603C_mstory3();
    func_801060E4_mstory3(0x5A6F);
    func_8010606C_mstory3();
    func_8001C624_main(S3MODEL(2), S3MOT(2, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[2].obj, &D_801153BC_mstory3, 10);
    func_8001C624_main(S3MODEL(2), S3MOT(2, 0), 0, 10, 2);
    func_8001C624_main(S3MODEL(2), S3MOT(2, 7), 0, 10, 0);
    func_80107244_mstory3(S3MODEL(2));
    func_8001C624_main(S3MODEL(2), S3MOT(2, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[2].obj, &D_801153B0_mstory3, 10);
    func_8001C624_main(S3MODEL(2), S3MOT(2, 0), 0, 10, 2);
    S3A[2].func = func_801115D8_mstory3;
    while (TRUE) {
        if (S3A[2].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[2].unk08 = 0;
    S3A[0].func = func_80110998_mstory3;
    S3A[4].func = func_80111F5C_mstory3;
    S3A[3].func = func_80112854_mstory3;
    HuPrcSleep(30);
    D_801153B0_mstory3.y = HmfModelData[S3MODEL(0)].rot.y;
    D_801153C8_mstory3.y = -62.78f;
    func_80106CF0_mstory3(S3MODEL(0), D_80115DA2_mstory3, D_80115D98_mstory3[0]);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[0].obj, &D_801153C8_mstory3, 10);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 0), 0, 10, 2);
    HuPrcSleep(40);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 1), 0, 10, 2);
    func_80107070_mstory3(S3A[0].obj, &D_801153BC_mstory3, 10);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 0), 0, 10, 2);
    HuPrcSleep(15);
    func_80106CF0_mstory3(S3MODEL(0), D_80115DA2_mstory3, D_80115D98_mstory3[2]);
    func_8001C624_main(S3MODEL(0), S3MOT(0, 11), 0, 10, 0);
    func_80107244_mstory3(S3MODEL(0));
    func_8001C624_main(S3MODEL(0), S3MOT(0, 2), 0, 10, 2);
    func_80107070_mstory3(S3A[0].obj, &D_801153B0_mstory3, 3);
    S3A[0].func = func_80110998_mstory3;
    HuPrcSleep(60);
    S3A[6].func = func_80113668_mstory3;
    S3A[7].func = func_80113AA8_mstory3;
    HuPrcSleep(15);
    HuAudFXPlay(0x2A0);
    func_8010603C_mstory3();
    func_801060E4_mstory3(0x5A6E);
    func_8010606C_mstory3();
    while (TRUE) {
        if (S3A[7].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[7].unk08 = 0;
    S3A[6].func = func_801136E8_mstory3;
    S3A[7].func = func_80113B3C_mstory3;
    while (TRUE) {
        if (S3A[6].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[6].unk08 = 0;
    S3A[6].func = func_80113800_mstory3;
    HuPrcSleep(60);
    func_80105E8C_mstory3();
    S3A[10].func = func_8010D774_mstory3;
}

void func_8010F658_mstory3(void) {
}

/* actor 0: the player's character */
void func_8010F660_mstory3(void) {
    Story3Motions motions = D_80115800_mstory3;
    omObjData *obj;
    s32 chr;
    void *data;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    S3A[0].obj = obj;
    S3A[0].unk08 = 0;
    S3A[0].func = func_8010D774_mstory3;
    S3A[0].unk0C = 0;
    S3A[0].unk10 = 0x1F;
    chr = D_80115DB0_mstory3;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 2));
    func_8000B460_main(obj, 3, motions.v[chr][1] | 0x1D0000);
    func_8000B460_main(obj, 4, motions.v[chr][0] | 0x1D0000);
    func_8000B460_main(obj, 5, motions.v[chr][2] | 0x1D0000);
    func_8000B460_main(obj, 6, motions.v[chr][3] | 0x1D0000);
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x72));
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x6C));
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x9B));
    func_8000B460_main(obj, 13, func_80017BB8_main(chr, 0x9C));
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    if (D_80115DB0_mstory3 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelPosSet(obj->model[4], -120.0f, 0.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    data = DataRead(func_80017BB8_main(chr, 0xA4));
    D_80115D98_mstory3[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_801153E0_mstory3[chr]);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115D98_mstory3[0], 1, 0);
    func_80032FF8_main(D_80115D98_mstory3[0], 0);
    D_80115DA2_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115D98_mstory3[0], 0, D_801153E0_mstory3[chr]);
    data = DataRead(func_80017BB8_main(chr, 0xA9));
    D_80115D98_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DA2_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115D98_mstory3[0], 0, D_801153E0_mstory3[chr]);
    data = DataRead(func_80017BB8_main(chr, 0xAA));
    D_80115D98_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DA2_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115D98_mstory3[0], 0, D_801153E0_mstory3[chr]);
    data = DataRead(func_80017BB8_main(chr, 0xA5));
    D_80115D98_mstory3[3] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DA2_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115D98_mstory3[0], 0, D_801153E0_mstory3[chr]);
    data = DataRead(func_80017BB8_main(chr, 0xA6));
    D_80115D98_mstory3[4] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106CF0_mstory3(obj->model[1], D_80115DA2_mstory3, D_80115D98_mstory3[0]);
    omPrcSetDestructor(0, func_8010F658_mstory3);
    while (TRUE) {
        S3A[0].func(obj);
        HuPrcVSleep();
    }
}

/* actor 0: shout, then stand */
void func_8010FCA4_mstory3(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    HuPrcSleep(80);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    S3A[0].func = func_8010D774_mstory3;
}

void func_8010FD64_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80107070_mstory3(obj, (Vec *)&D_801158E0_mstory3, 10);
    S3A[0].func = func_8010D774_mstory3;
}



INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115880_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011588C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115898_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158A4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158B0_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158BC_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158C8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158D4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158E0_mstory3);

/* actor 0: hold up the item and grow it, then the cheer */
void func_8010FDB0_mstory3(omObjData *obj) {
    Story3HmfPart *part;
    f32 scale;
    f32 s;
    s32 i;

    HuPrcSleep(70);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[13]].unk02, 0, 10, 2);
    func_80107218_mstory3(obj, 0.0f, 110.0f, 0.0f, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], obj->model[1], "item_hook");
    func_8001C258_main(obj->model[3], 4, 0);
    func_80107244_mstory3(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    while (TRUE) {
        if (S3A[8].unk08 == 2) {
            break;
        }
        HuPrcVSleep();
    }
    S3A[8].unk08 = 0;
    func_8001C258_main(S3A[8].obj->model[1], 4, 4);
    func_8001C258_main(S3A[8].obj->model[3], 4, 4);
    func_8002FD8C_main(obj->model[1], HmfModelData[obj->model[1]].unk02, "item_hook", 0x1B, 0x45);
    func_8002FD8C_main(obj->model[1], HmfModelData[obj->model[1]].unk02, "item_hook", 0x1B, 0x46);
    func_8002FD8C_main(obj->model[1], HmfModelData[obj->model[1]].unk02, "item_hook", 0x1B, 0x47);
    part = func_8001D33C_main(obj->model[1], "item_hook");
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
    func_8002FDCC_main(obj->model[1], HmfModelData[obj->model[1]].unk02, "item_hook", 0x1B, 0x47);
    func_8002FDCC_main(obj->model[1], HmfModelData[obj->model[1]].unk02, "item_hook", 0x1B, 0x46);
    func_8002FDCC_main(obj->model[1], HmfModelData[obj->model[1]].unk02, "item_hook", 0x1B, 0x45);
    func_80106400_mstory3(5);
    while (TRUE) {
        if (func_80106CDC_mstory3() == 1) {
            break;
        }
        HuPrcVSleep();
    }
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5C);
    func_8010606C_mstory3();
    func_8001C5B4_main(obj->model[1], obj->motion[4]);
    func_8001C814_main(obj->model[1], 4, 4);
    func_8001C92C_main(obj->model[1], 2.0f);
    func_8001C6A8_main(obj->model[1], D_800CCF58_main[HmfModelData[obj->model[1]].unk02].unk02);
    do {
        s = HmfModelData[obj->model[1]].unk40;
        HuPrcVSleep();
    } while (s > 0.0f);
    func_8001C5B4_main(obj->model[1], obj->motion[3]);
    func_8001C814_main(obj->model[1], 4, 4);
    func_8001C6A8_main(obj->model[1], D_800CCF58_main[HmfModelData[obj->model[1]].unk02].unk02);
    do {
        s = HmfModelData[obj->model[1]].unk40;
        HuPrcVSleep();
    } while (s > 0.0f);
    func_8001C92C_main(obj->model[1], 1.0f);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    HuAudSeqFadeOut(20);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    S3A[0].unk08 = 1;
    S3A[0].func = func_8010D774_mstory3;
}

void func_801103E8_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80107070_mstory3(obj, (Vec *)&D_80115908_mstory3, 5);
    S3A[0].func = func_8010D774_mstory3;
}

void func_80110474_mstory3(omObjData *obj) {
    S3A[0].unk0C = 1;
    S3A[0].unk10 = 0x1F;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801074D8_mstory3(obj, 1.5f, 60);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    S3A[0].unk0C = 0;
    S3A[0].func = func_8010D774_mstory3;
}

void func_80110558_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107070_mstory3(obj, (Vec *)&D_80115914_mstory3, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    S3A[0].func = func_8010D774_mstory3;
}

void func_80110628_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, (Vec *)&D_80115920_mstory3, 5);
    S3A[0].func = func_8011065C_mstory3;
}

/* actor 0 keeps facing actor 2 */
void func_8011065C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, S3A[2].obj);
}

void func_8011067C_mstory3(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107070_mstory3(obj, (Vec *)&D_8011592C_mstory3, 10);
    S3A[0].unk0C = 1;
    S3A[0].unk10 = 0x1F;
    func_801074D8_mstory3(obj, 6.0f, 30);
    S3A[0].unk0C = 0;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    S3A[0].func = func_80110A84_mstory3;
}

void func_80110774_mstory3(omObjData *obj) {
    if (S3A[0].unk08 == 1) {
        func_80106CF0_mstory3(obj->model[1], D_80115DA2_mstory3, D_80115D98_mstory3[4]);
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
        func_80107070_mstory3(obj, (Vec *)&D_80115944_mstory3, 10);
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
        S3A[0].unk08 = 2;
        S3A[0].func = func_8010D774_mstory3;
    } else if (S3A[0].unk08 == 2) {
        func_80106CF0_mstory3(obj->model[1], D_80115DA2_mstory3, D_80115D98_mstory3[2]);
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
        func_80107070_mstory3(obj, (Vec *)&D_80115938_mstory3, 10);
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
        S3A[0].unk08 = 3;
        S3A[0].func = func_80110978_mstory3;
    } else if (S3A[0].unk08 == 3) {
        func_80107070_mstory3(obj, (Vec *)&D_80115944_mstory3, 10);
        S3A[0].func = func_80110978_mstory3;
    }
}

void func_80110978_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, S3A[2].obj);
}

void func_80110998_mstory3(omObjData *obj) {
    HuPrcSleep(5);
    S3A[0].unk0C = 1;
    S3A[0].unk10 = 0x28;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    func_8010733C_mstory3(obj, 20.0f, 15);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    S3A[0].unk0C = 0;
    S3A[0].func = func_8010D774_mstory3;
}

void func_80110A84_mstory3(omObjData *obj) {
    if (S3A[0].unk08 == 0) {
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
        func_80107070_mstory3(obj, (Vec *)&D_80115950_mstory3, 10);
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
        S3A[0].unk08 = 1;
        S3A[0].func = func_8010D774_mstory3;
    } else if (S3A[0].unk08 == 1) {
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
        func_80107070_mstory3(obj, (Vec *)&D_8011595C_mstory3, 10);
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
        S3A[0].unk08 = 2;
        S3A[0].func = func_8010D774_mstory3;
    } else if (S3A[0].unk08 == 2) {
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
        func_80107070_mstory3(obj, (Vec *)&D_80115950_mstory3, 10);
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
        S3A[0].unk08 = 0;
        S3A[0].func = func_8010D774_mstory3;
    }
}










void func_80110CAC_mstory3(void) {
}

/* actor 1 */
void func_80110CB4_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    S3A[1].obj = obj;
    S3A[1].unk08 = 0;
    S3A[1].func = func_8010D774_mstory3;
    S3A[1].unk0C = 0;
    S3A[1].unk10 = 0x1F;
    obj->model[1] = func_8000B108_main(0x90000, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0x90004);
    func_8000B460_main(obj, 1, 0x1D007A);
    func_8000B460_main(obj, 2, 0x1D0051);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 30, 2);
    Hu3DModelPosSet(obj->model[1], 150.0f, 0.0f, 384.0f);
    Hu3DModelPosSet(obj->model[2], 150.0f, -5.0f, 384.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    omPrcSetDestructor(0, func_80110CAC_mstory3);
    while (TRUE) {
        S3A[1].func(obj);
        HuPrcVSleep();
    }
}


INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115908_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115914_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115920_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011592C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115938_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115944_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115950_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011595C_mstory3);

const Vec D_80115974_mstory3 = { 200.0f, 0.0f, 1200.0f };

void func_80110E30_mstory3(omObjData *obj) {
    HuAudFXPlay(0x28E);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    S3A[1].unk0C = 1;
    S3A[1].unk10 = 0x28;
    func_80106DC4_mstory3(obj, (Vec *)&D_80115974_mstory3, 40);
    S3A[1].unk0C = 0;
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    S3A[1].func = func_8010D774_mstory3;
}

/* actor 8's model 2 drifts along x; its model 5 follows 40 below */
void func_80110F04_mstory3(omObjData *obj) {
    Vec pos;

    pos.x = HmfModelData[S3A[8].obj->model[2]].pos.x;
    pos.y = HmfModelData[S3A[8].obj->model[2]].pos.y;
    pos.z = HmfModelData[S3A[8].obj->model[2]].pos.z;
    pos.x += 0.5f;
    Hu3DModelPosSet(S3A[8].obj->model[2], pos.x, pos.y, pos.z);
    func_8000CFA4_main(S3A[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
}

void func_80110FE8_mstory3(omObjData *obj) {
    omObjData *a2 = S3A[2].obj;

    func_8001C258_main(a2->model[1], 4, 0);
    func_8001C258_main(a2->model[2], 4, 0);
    func_801061C4_mstory3();
    HuPrcSleep(3);
    func_80106220_mstory3();
    S3A[1].func = func_8010D774_mstory3;
}

const Vec D_80115980_mstory3 = { 138.0f, 100.0f, 214.0f };

void func_80111064_mstory3(omObjData *obj) {
    func_80106DE0_mstory3(S3A[3].obj, (Vec *)&D_80115980_mstory3, 180, 0);
    S3A[1].func = func_8010D774_mstory3;
}




void func_801110AC_mstory3(void) {
}

/* actor 2 */
void func_801110B4_mstory3(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    S3A[2].obj = obj;
    S3A[2].unk08 = 0;
    S3A[2].func = func_8010D774_mstory3;
    S3A[2].unk0C = 0;
    S3A[2].unk10 = 0x1F;
    obj->model[1] = func_8000B108_main(0x800A0, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8000B460_main(obj, 0, 0x80000);
    func_8000B460_main(obj, 1, 0x80001);
    func_8000B460_main(obj, 2, 0x80002);
    func_8000B460_main(obj, 3, 0x80005);
    func_8000B460_main(obj, 4, 0x8002F);
    func_8000B460_main(obj, 5, 0x80072);
    func_8000B460_main(obj, 6, 0x1D0075);
    func_8000B460_main(obj, 7, 0x80033);
    func_8000B460_main(obj, 8, 0x80003);
    func_8000B460_main(obj, 9, 0x80005);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 608.1f, -85.8f, -1390.3f);
    Hu3DModelPosSet(obj->model[2], 608.1f, -85.8f, -1390.3f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    data = DataRead(func_80017BB8_main(6, 0xA4));
    D_80115DA4_mstory3[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_8011588C_mstory3);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115DA4_mstory3[0], 1, 0);
    func_80032FF8_main(D_80115DA4_mstory3[0], 0);
    D_80115DAE_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115DA4_mstory3[0], 0, D_8011588C_mstory3);
    data = DataRead(func_80017BB8_main(6, 0xA9));
    D_80115DA4_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DAE_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115DA4_mstory3[0], 0, D_8011588C_mstory3);
    data = DataRead(func_80017BB8_main(6, 0xAA));
    D_80115DA4_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DAE_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115DA4_mstory3[0], 0, D_8011588C_mstory3);
    data = DataRead(func_80017BB8_main(6, 0xA5));
    D_80115DA4_mstory3[3] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106CF0_mstory3(obj->model[1], D_80115DAE_mstory3, D_80115DA4_mstory3[0]);
    omPrcSetDestructor(0, func_801110AC_mstory3);
    while (TRUE) {
        S3A[2].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111500_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801115D8_mstory3);

void func_8011175C_mstory3(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011598C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115998_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111764_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111A58_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159BC_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159C8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159D4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159E0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111B34_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111C50_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159F8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111CB8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111DF8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111E2C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111E4C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111F3C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111F5C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111FA4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011204C_mstory3);

void func_801122BC_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801122C4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011249C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801125C4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801125F8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112650_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011268C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801126D8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011270C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011272C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112834_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112854_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011289C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112944_mstory3);

void func_80112B80_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112B88_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A10_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A1C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A28_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A34_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A40_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A4C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A58_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A64_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A70_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A7C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A88_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A94_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115AA0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112DA0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112EF0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112F7C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112FB0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80112FD0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801130A4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011315C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011322C_mstory3);

void func_801134D8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801134E0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113668_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801136E8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113800_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113874_mstory3);

void func_80113960_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113968_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B24_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B30_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B3C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B48_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B54_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113AA8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113B3C_mstory3);

void func_80113BA8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113BB0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113E68_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114260_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801142C0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114474_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011475C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114920_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801149D0_mstory3);

void func_80114AF8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114B00_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114CD8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114EF8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114FA4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011517C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011522C_mstory3);
