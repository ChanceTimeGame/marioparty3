#include "common.h"
#include "../ovl_81_name/ovl_81.h"

typedef struct UnkStaff {
    char unk_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} UnkStaff;

typedef struct UnkStaff_1 {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ char unk_20[8];
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ char unk_2A[2];
} UnkStaff_1;

typedef struct UnkStaff_2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} UnkStaff_2;

void func_8010C680_staff(s16 *, s32 *, f32 *, void *);
void func_8010C8F4_staff(UnkStaff_1 *);
void func_8010CD74_staff(UnkStaff_1 *);
void func_8010CFD4_staff(UnkStaff *);
extern f32 D_80110534_staff;
extern s8 D_80110538_staff;
extern Vec D_80111534_staff;
extern Vec D_80111540_staff;
extern f32 D_80111560_staff;
extern f32 D_80111564_staff;

// story j1
#include "mallocblock.h"

/* Model definition table entry (0x28 stride; storyresult's SrModelDef, msetup's MsModelDef). */
typedef struct SrModelDef {
    /* 0x00 */ s32 unk0; /* func_8000B108_main arg0 */
    /* 0x04 */ s32 unk4; /* func_8000B108_main arg1 */
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA; /* func_8001C814_main arg2 */
    /* 0x0C */ s32 unkC; /* 0: none, 1: pos/rot, 2: pos*5 / rot */
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
} SrModelDef; /* size = 0x28 */

typedef struct SrModelSlot {
    /* 0x00 */ s16 model;
    /* 0x02 */ s16 unk2; /* HmfModelData[model].unk02 */
} SrModelSlot; /* size = 0x4 */

/* Camera key (storyresult's SrCamKey). */
typedef struct SrCamKey {
    /* 0x00 */ Vec rot;    /* CRot */
    /* 0x0C */ Vec center; /* Center */
    /* 0x18 */ f32 zoom;   /* CZoom */
    /* 0x1C */ f32 fov;
    /* 0x20 */ f32 unk20;
} SrCamKey; /* size = 0x24 */

typedef void (*SrCamFunc)(s16, s16, s16);

/* Spline path (mstory1's ObPath). */
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

void func_80105DB8_staff(SrModelDef *def, s16 model);
void func_80105E6C_staff(SrModelDef *defs, SrModelSlot *slots, s32 count);
u32 func_80105F48_staff(u32 seed);
u32 func_8010601C_staff(void);
u32 func_80106044_staff(u32 max);
void func_8010609C_staff(SrCamKey *key);
void func_8010615C_staff(void);
void func_80106720_staff(void);
void func_8010674C_staff(SrCamKey *keys, f32 speed, SrCamFunc func);
ObPath *func_801085F0_staff(Vec *points, s16 flags);
void func_801088F4_staff(ObPath *path, f32 t, Vec *out);
void func_8010919C_staff(ObPath *path);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
extern f32 D_800CB890_main;
extern f32 D_800CE17C_main[];
extern f32 D_800D5210_main;
extern SrModelDef D_80110FF4_staff[];
extern u32 D_8011053C_staff; /* random seed */
extern Vec D_80111550_staff; /* CRot copy */

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801059A0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105BD4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105CB4_staff);

void func_80105DB8_staff(SrModelDef *def, s16 model) {
    switch ((u32)def->unkC) {
    case 1:
        Hu3DModelPosSet(model, def->pos.x, def->pos.y, def->pos.z);
        Hu3DModelRotSet(model, def->rot.x, def->rot.y, def->rot.z);
        break;
    case 0:
        break;
    case 2:
        Hu3DModelPosSet(model, def->pos.x * 5.0f, def->pos.y * 5.0f, def->pos.z * 5.0f);
        Hu3DModelRotSet(model, def->rot.x, def->rot.y, def->rot.z);
        break;
    }
}

void func_80105E6C_staff(SrModelDef *defs, SrModelSlot *slots, s32 count) {
    s16 i;
    u16 model;

    if (defs == NULL || slots == NULL) {
        return;
    }
    for (i = 0; i < count; defs++, i++, slots++) {
        model = func_8000B108_main(defs->unk0, defs->unk4);
        slots->model = model;
        func_80105DB8_staff(defs, model);
        slots->unk2 = HmfModelData[(s16)model].unk02;
        if (slots->unk2 >= 0) {
            func_8001C814_main(model, -1, defs->unkA);
        }
    }
}

u32 func_80105F48_staff(u32 seed) {
    s32 hi, lo;

    if (seed == 0) {
        seed = rand8();
        seed = seed ^ osGetCount();
        seed ^= 0xD826BC89;
    }
    hi = seed / 0x1F31D;
    lo = seed - (hi * 0x1F31D);
    seed = hi * 0xB14;
    seed = seed - lo * 0x41A7;
    return seed;
}

u32 func_8010601C_staff(void) {
    return D_8011053C_staff = func_80105F48_staff(D_8011053C_staff);
}

u32 func_80106044_staff(u32 max) {
    return ((D_8011053C_staff = func_80105F48_staff(D_8011053C_staff)) & 0x7FFFFFFF) % max;
}

void func_8010609C_staff(SrCamKey *key) {
    f32 fov;

    CRot = key->rot;
    D_80111550_staff = CRot;
    Center = key->center;
    CZoom = key->zoom;
    fov = key->fov;
    if (fov != D_80110534_staff) {
        D_80110534_staff = fov;
        Hu3DCamSetPerspective(0, fov, D_80111564_staff, D_80111560_staff);
    }
}

#ifdef NON_MATCHING
/* Residue (masked 11): retail schedules the &Center load before the first mul.s, and f2/f12 swap in the distance sum (as msetup func_801068F4_msetup). */
void func_8010615C_staff(void) {
    Vec pos;
    Vec at;
    Vec up;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 ux;
    f32 uy;
    f32 uz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;

    if (D_80110538_staff == 0) {
        rx = CRot.x;
        ry = CRot.y;
        rz = CRot.z;
        pos.x = sindf(ry) * cosdf(rx) * CZoom + Center.x;
        pos.y = -sindf(rx) * CZoom + Center.y;
        pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
        at.x = Center.x;
        at.y = Center.y;
        at.z = Center.z;
        ux = sindf(ry) * sindf(rx);
        uy = cosdf(rx);
        uz = cosdf(ry) * sindf(rx);
        dx = at.x - pos.x;
        dy = at.y - pos.y;
        dz = at.z - pos.z;
        len = HuSqrtf(dx * dx + dy * dy + dz * dz);
        dx /= len;
        dy /= len;
        dz /= len;
        up.x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz))
             + uy * (dx * dy * (1.0f - cosdf(rz)) - dz * sindf(rz))
             + uz * (dx * dz * (1.0f - cosdf(rz)) + dy * sindf(rz));
        up.y = ux * (dx * dy * (1.0f - cosdf(rz)) + dz * sindf(rz))
             + uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz))
             + uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
        up.z = ux * (dx * dz * (1.0f - cosdf(rz)) - dy * sindf(rz))
             + uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz))
             + uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
    } else {
        pos = D_80111540_staff;
        at = D_80111534_staff;
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
    }
    D_800CE17C_main[0] = pos.x;
    D_800CE17C_main[1] = pos.z;
    D_800CE17C_main[-1] = CRot.y;
    D_800CE17C_main[2] = gCameraList->fov[0];
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010615C_staff);
#endif

void func_80106720_staff(void) {
    while (1) {
        func_8010615C_staff();
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
/* Residue: two hazard nops after cosdf() (W2DC_BLANKSTRIP) and f2/f12 swapped in the distance sum. */
void func_8010674C_staff(SrCamKey *keys, f32 speed, SrCamFunc func) {
    f32 out[10];
    f32 y[4];
    f32 x[4];
    SrCamFunc fn;
    SrCamKey *cur;
    f32 *p0;
    f32 *p1;
    f32 *p2;
    f32 *p3;
    f32 *o;
    f32 total;
    f32 d;
    f32 px, py, pz;
    f32 dz, dy, dx;
    f32 lx, ly, lz;
    s16 i;
    s16 seg;
    s16 j;

    fn = func;
    lz = 0.0f;
    ly = 0.0f;
    lx = 0.0f;
    total = 0.0f;
    cur = keys;
    for (i = 0; cur->zoom != 0.0f; cur = &keys[++i]) {
        if (speed != 0.0f) {
            px = sindf(cur->rot.y) * cosdf(cur->rot.x) * cur->zoom + cur->center.x;
            py = -sindf(cur->rot.x) * cur->zoom + cur->center.y;
            pz = cosdf(cur->rot.y) * cosdf(cur->rot.x) * cur->zoom + cur->center.z;
            if (i > 0) {
                dx = lx - px;
                dy = ly - py;
                dz = lz - pz;
                d = dx * dx + dy * dy + dz * dz;
            d = HuSqrtf(d);
                if (d == 0.0f) {
                    d = speed * 10.0f;
                }
                total += d / speed;
                cur->unk20 = total;
            }
            lx = px;
            ly = py;
            lz = pz;
        } else {
            total = cur->unk20;
        }
    }
    total -= 10.0f;
    for (i = 10, seg = 1; i < total; i++) {
        if (i > keys[seg + 1].unk20) {
            seg++;
        }
        x[0] = keys[seg - 1].unk20;
        x[1] = keys[seg].unk20;
        x[2] = keys[seg + 1].unk20;
        x[3] = keys[seg + 2].unk20;
        p0 = &keys[seg - 1].rot.x;
        p1 = &keys[seg].rot.x;
        p2 = &keys[seg + 1].rot.x;
        p3 = &keys[seg + 2].rot.x;
        o = out;
        for (j = 0; j < 8; j++) {
            y[0] = *p0++;
            y[1] = *p1++;
            y[2] = *p2++;
            y[3] = *p3++;
            *o++ = func_80018ACC_main(y, x, i);
        }
        Center.x = out[3];
        Center.y = out[4];
        Center.z = out[5];
        D_80111550_staff.x = CRot.x = out[0];
        D_80111550_staff.y = CRot.y = out[1];
        D_80111550_staff.z = CRot.z = out[2];
        CZoom = out[6];
        gCameraList->fov[0] = D_80110534_staff = out[7];
        if (func != NULL) {
            fn((s16)total, seg, i);
        }
        HuPrcVSleep();
    }
    i = seg + 1;
    D_80111550_staff.x = CRot.x = keys[i].rot.x;
    D_80111550_staff.y = CRot.y = keys[i].rot.y;
    D_80111550_staff.z = CRot.z = keys[i].rot.z;
    CZoom = keys[i].zoom;
    Center.x = keys[i].center.x;
    Center.y = keys[i].center.y;
    Center.z = keys[i].center.z;
    gCameraList->fov[0] = D_80110534_staff = keys[i].fov;
    D_800CB99C_main = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010674C_staff);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106C50_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106E20_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801073EC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107508_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107740_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107A9C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107B1C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107BA0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107DBC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107EB8_staff);

ObPath *func_801085F0_staff(Vec *points, s16 flags) {
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
void func_801088F4_staff(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801088F4_staff);
#endif

void func_8010919C_staff(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801091CC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109264_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801095E4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010992C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010998C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109D08_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109D74_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109F34_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010A848_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B1E0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B430_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B4B4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B514_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B794_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B8C0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B9BC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BA30_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BE20_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011133C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111348_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111354_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111360_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011136C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111378_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111384_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111390_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011139C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113A8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113B4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113C0_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113CC_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113D8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113E4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113F0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BF84_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C680_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C8F4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CD74_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CFD4_staff);

void func_8010D1E8_staff(void) {
    s16 sp10[3][2];
    UnkStaff sp20[8];
    UnkStaff_1 sp120[3];
    s16 sp1A8;
    s32 sp1AC;
    f32 sp1B0;
    s16 var_v0;
    s16 *temp_s2;
    s16 var_s0;
    s32 i;
    UnkStaff_1 *temp;
    UnkStaff *temp2;
    s16 *temp3;

    temp_s2 = HuPrcCurrentGet()->user_data;
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0x20);
    func_800E8180_name_81(1000.0f, 10000.0f);
    func_800E8110_name_81();
    D_80110538_staff = 1;
    D_80111540_staff.x = 350.0f;
    D_80111540_staff.y = 190.0f;
    D_80111540_staff.z = 3770.0f;
    D_80111534_staff.x = -1000.0f;
    D_80111534_staff.y = 130.0f;
    D_80111534_staff.z = 450.0f;
    D_80110534_staff = 40.0f;
    Hu3DCamSetPerspective(0, 40.0f, D_80111564_staff, D_80111560_staff);
    func_80105E6C_staff(D_80110FF4_staff, (SrModelSlot *)&sp10[0][0], 3);
    func_8010CFD4_staff(sp20);
    func_8010CD74_staff(sp120);
    *temp_s2 = 0;
    sp1A8 = 0;
    sp1B0 = 90.0f;
    sp1AC = 0;
    for (var_s0 = 0; var_s0 >= 0;) {
        if (var_s0 != *temp_s2) {
            if (*temp_s2 == -1) {
                var_s0 = -1;
            } else {
                var_s0 = *temp_s2;
                func_8010C8F4_staff(sp120);
                func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
                HuPrcVSleep();
            }
        } else {
            func_8010C8F4_staff(sp120);
            func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
            HuPrcVSleep();
        }
    }

    // TODO: fix typing of temp3 or sp10
    for (temp3 = sp10[0], i = 0; i < 3; i++, temp3 += 2) {
        func_8001ACDC_main(*temp3); //?
    }
    for (temp2 = sp20, i = 0; i < 8; i++, temp2++) {
        func_8001ACDC_main(temp2->unk_18);
        func_8001ACDC_main(temp2->unk_1A);
        func_80033354_main(temp2->unk_1C);
        if (temp2->unk_1E >= 0) {
            func_8001ACDC_main(temp2->unk_1E);
        }
    }

    for (temp = sp120, i = 0; i < 3; i++, temp++) {
        func_8001ACDC_main(temp->unk_28);
    }

    MBDBackKill();
    MBDBackClose();
    *temp_s2 = 0;
    while (1) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D450_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D580_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D998_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DE50_staff);

void func_8010DEDC_staff(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DEE4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DEF4_staff);

void func_8010DF04_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF0C_staff);

s16 func_8010DF24_staff(UnkStaff_2 *arg0) {
    return arg0->unk_04;
}

void func_8010DF2C_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF34_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F04C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F3E4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F4C4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F9D4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010FB28_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010FB88_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111430_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011143C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111448_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111454_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111460_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011146C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111478_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111484_staff);
