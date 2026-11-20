#include "common.h"
#include "malloc.h"
#include "mallocblock.h"
#include "game/esprite.h"
#include "game/hmfman.h"
#include "game/process.h"
#include "game/object.h"
#include "game/util.h"
#include "math.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04; // gid?
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA; // x center
    /* 0x0C */ s16 unkC; // y center
    /* 0x0E */ s16 unkE;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
} D_800CD1DC_main_Struct; // Size 0x24

extern D_800CD1DC_main_Struct* D_800CD1DC_main;
extern s16 D_8011B650_mgmode;
extern s16 D_8011B652_mgmode;
extern u16* D_8011B654_mgmode[3];
extern void* D_8011B660_mgmode;
extern s16 D_8011A3E0_mgmode;

s16 func_80116B20_mgmode(void) {
    s16 sprGrp;
    s16 i;

    D_8011A3E0_mgmode = func_8000B838_main(0x12000E);
    sprGrp = InitEspriteSlot(D_8011A3E0_mgmode, 0, 1);
    D_8011B650_mgmode = sprGrp;
    for (i = 0; i < ARRAY_COUNT(D_8011B654_mgmode); i++) {
        D_8011B654_mgmode[i] = HuMemAllocTag(0x6000, 0x7918);
    }
    D_8011B660_mgmode = HuSprGet(D_800CD1DC_main[sprGrp].unk04, 0)->unk_84->unk00->unk00;
    D_8011B652_mgmode = 0;
    func_8000BB94_main(sprGrp);
    return sprGrp;
}

void func_80116C18_mgmode(s16 arg0) {
    HvqImageHeader *imageData;
    HvqFileHeader *decodeData;
    u8 *workBuffer;

    imageData = DataRead(arg0 | 0x170000);
    decodeData = DataRead((arg0 + 1) | 0x170000);
    hvqMpsInit1(0xFF);
    hvqMpsDecodeStart1(decodeData);
    workBuffer = HuMemMemoryAllocPerm(0xC00);
    hvqMpsDecode1(imageData, D_8011B654_mgmode[D_8011B652_mgmode], 0x80, workBuffer);
    HuMemMemoryFreePerm(workBuffer);
    DataClose(imageData);
    DataClose(decodeData);
    HuSprGet(D_800CD1DC_main[D_8011B650_mgmode].unk04, 0)->unk_84->unk00->unk00 =
        D_8011B654_mgmode[D_8011B652_mgmode];
    D_8011B652_mgmode++;
    if (D_8011B652_mgmode >= ARRAY_COUNT(D_8011B654_mgmode)) {
        D_8011B652_mgmode = 0;
    }
    func_8000BB54_main(D_8011B650_mgmode);
}

void func_80116D4C_mgmode(void) {
    s16 i;

    if (D_8011A3E0_mgmode != -1) {
        HuSprGet(D_800CD1DC_main[D_8011B650_mgmode].unk04, 0)->unk_84->unk00->unk00 =
            D_8011B660_mgmode;
        func_8000C184_main(D_8011B650_mgmode);
        HuSprKill(D_8011A3E0_mgmode);
        for (i = 0; i < ARRAY_COUNT(D_8011B654_mgmode); i++) {
            HuMemFree(D_8011B654_mgmode[i]);
        }
        D_8011A3E0_mgmode = -1;
    }
}

typedef struct CamData {
    Vec rot;
    Vec center;
    f32 zoom;
    f32 unk_1C;
} CamData;

extern f32 D_8011B6A4_mgmode;
extern Vec D_8011B898_mgmode;
extern CamData* D_8011B954_mgmode;
extern s8 D_8011B958_mgmode;

void func_80116E24_mgmode(s16 arg0) {
    CRot = D_8011B954_mgmode[arg0].rot;
    D_8011B898_mgmode = CRot;
    
    Center = D_8011B954_mgmode[arg0].center;
    CZoom = D_8011B954_mgmode[arg0].zoom;
    
    D_8011B6A4_mgmode = D_8011B954_mgmode[arg0].unk_1C;
    D_8011B958_mgmode = arg0;
}

/* out = b..a turn difference d (degrees, as a double) folded into -180..180. */
#define MG_WRAP180(out, d, a, b)              \
    if (((d) < 0.0 ? -(d) : (d)) > 180.0) {    \
        if ((a) < (b)) {                       \
            (out) = (d) + 360.0;               \
        } else {                               \
            (out) = (d) - 360.0;               \
        }                                      \
    } else {                                   \
        (out) = (d);                           \
    }

void func_80116ED4_mgmode(s16 presetIdx, s16 duration, s16 easeType, void (*callback)(s16*)) {
    Vec rotDelta;                       /* sp10 */
    Vec centerDelta;                    /* sp20 */
    Vec rotStart;                       /* sp30 */
    Vec centerStart;                    /* sp40 */
    Vec rot;                            /* sp50 */
    Vec center;                         /* sp60 */
    s16 cbArg[24];                      /* sp70..sp9F (0x30 bytes) */
    Vec eye;                            /* spA0 */
    void (*cb)(s16*);                   /* s8 */
    f32 zoom;                           /* f22 */
    f32 zoomDelta;                      /* f24 */
    f32 zoomStart;                      /* f22_2 */
    f32 unkDelta;                       /* f28 */
    f32 unkStart;                       /* f26 */
    f64 diff;
    s16 i;

    cb = callback;
    rot = D_8011B954_mgmode[presetIdx].rot;
    center = D_8011B954_mgmode[presetIdx].center;
    zoom = D_8011B954_mgmode[presetIdx].zoom;

    eye.x = sindf(rot.y) * cosdf(rot.x) * zoom + center.x;
    eye.y = -sindf(rot.x) * zoom + center.y;
    eye.z = cosdf(rot.y) * cosdf(rot.x) * zoom + center.z;
    diff = 100.0f / zoom;
    center.x = eye.x + (center.x - eye.x) * diff;
    center.y = eye.y + (center.y - eye.y) * diff;
    center.z = eye.z + (center.z - eye.z) * diff;
    zoom = 100.0f;

    diff = rot.x - CRot.x;
    MG_WRAP180(rotDelta.x, diff, rot.x, CRot.x);
    diff = rot.y - CRot.y;
    MG_WRAP180(rotDelta.y, diff, rot.y, CRot.y);
    diff = rot.z - CRot.z;
    MG_WRAP180(rotDelta.z, diff, rot.z, CRot.z);

    centerDelta.x = center.x - Center.x;
    centerDelta.y = center.y - Center.y;
    centerDelta.z = center.z - Center.z;
    zoomDelta = zoom - CZoom;
    unkDelta = D_8011B954_mgmode[presetIdx].unk_1C - D_8011B6A4_mgmode;
    cbArg[1] = duration;
    unkStart = D_8011B6A4_mgmode;
    centerStart = Center;
    rotStart = CRot;
    zoomStart = CZoom;

    if (easeType == 1 || easeType == 2) {
        for (i = 0; i < duration; i++) {
            if (easeType != 2) {
                diff = sindf(i * 90.0f / duration);
            } else if (i <= duration / 2) {
                diff = (1.0f - cosdf(i * 180.0f / duration)) * 0.5f;
            } else {
                diff = -cosdf(i * 180.0f / duration) * 0.5f + 0.5f;
            }
            D_8011B898_mgmode.x = CRot.x = diff * rotDelta.x + rotStart.x;
            D_8011B898_mgmode.y = CRot.y = diff * rotDelta.y + rotStart.y;
            D_8011B898_mgmode.z = CRot.z = diff * rotDelta.z + rotStart.z;
            Center.x = diff * centerDelta.x + centerStart.x;
            Center.y = diff * centerDelta.y + centerStart.y;
            Center.z = diff * centerDelta.z + centerStart.z;
            CZoom = diff * zoomDelta + zoomStart;
            D_8011B6A4_mgmode = diff * unkDelta + unkStart;
            if (callback != (void (*)(s16*))-1) {
                cbArg[0] = i;
                cb(cbArg);
            }
            HuPrcVSleep();
        }
    } else {
        for (i = 0; i <= duration; i++) {
            diff = (1.0f / duration) * i;
            D_8011B898_mgmode.x = CRot.x = diff * rotDelta.x + rotStart.x;
            D_8011B898_mgmode.y = CRot.y = diff * rotDelta.y + rotStart.y;
            D_8011B898_mgmode.z = CRot.z = diff * rotDelta.z + rotStart.z;
            Center.x = diff * centerDelta.x + centerStart.x;
            Center.y = diff * centerDelta.y + centerStart.y;
            Center.z = diff * centerDelta.z + centerStart.z;
            CZoom = diff * zoomDelta + zoomStart;
            if (callback != (void (*)(s16*))-1) {
                cbArg[0] = i;
                cb(cbArg);
            }
            HuPrcVSleep();
        }
    }
    func_80116E24_mgmode(presetIdx);
}

/* Camera angles and distance looking from eye at target. */
// decomp-permuter
void func_801177BC_mgmode(Vec *eye, Vec *target)
{
  f32 dz;
  float new_var;
  f32 dx;
  f32 dy;
  f32 yaw;
  f32 c;
  dx = eye->x - target->x;
  dy = eye->y - target->y;
  dz = eye->z - target->z;
  CZoom = HuSqrtf(((dx * dx) + (dy * dy)) + (dz * dz));
  yaw = atan2df(dz, dx);
  CRot.y = -(yaw - 90.0f);
  c = cosdf(-yaw);
  new_var = (dx * c) + (dz * (-sindf(-yaw)));
  CRot.x = -atan2df(dy, new_var);
  CRot.z = 0.0f;
  Center = *target;
}

typedef struct MgModePair {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
} MgModePair;

extern s16 D_8011B664_mgmode;
extern s16 D_8011B666_mgmode;
extern s16 D_8011B668_mgmode;
extern s16 D_8011B66A_mgmode;
extern u16 D_8011B66C_mgmode;
extern s16 D_8011B66E_mgmode;
extern MgModePair* D_8011B670_mgmode;
extern u8 D_8011B630_mgmode[];
extern s16 D_8011A3F8_mgmode[];

void func_8000BBFC_main(u16 spriteId, s16 arg1);
s32 func_80050064_main(s32 write);
void func_801180A4_mgmode(void);

/* Look-at vectors for a camera orbiting center at rot, zoom away: eye, target and the up vector
   turned rot->z degrees about the view direction (Rodrigues). */
#ifdef NON_MATCHING
/* Masked 1 (341 vs 342): retail copies the HuSqrtf result to $f2 before the three divides;
   register allocation otherwise. Logic checked against the asm. */
void func_801178E0_mgmode(Vec* center, Vec* rot, f32 zoom, Vec* eye, Vec* at, Vec* up) {
    f32 rx = rot->x;
    f32 ry = rot->y;
    f32 rz = rot->z;
    f32 ux;
    f32 uy;
    f32 uz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;

    eye->x = sindf(ry) * cosdf(rx) * zoom + center->x;
    eye->y = -sindf(rx) * zoom + center->y;
    eye->z = cosdf(ry) * cosdf(rx) * zoom + center->z;
    *at = *center;
    ux = sindf(ry) * sindf(rx);
    uy = cosdf(rx);
    uz = cosdf(ry) * sindf(rx);
    dx = at->x - eye->x;
    dy = at->y - eye->y;
    dz = at->z - eye->z;
    len = HuSqrtf(dx * dx + dy * dy + dz * dz);
    dx /= len;
    dy /= len;
    dz /= len;
    up->x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz)) +
            uy * (dx * dy * (1.0f - cosdf(rz)) - dz * sindf(rz)) +
            uz * (dx * dz * (1.0f - cosdf(rz)) + dy * sindf(rz));
    up->y = ux * (dx * dy * (1.0f - cosdf(rz)) + dz * sindf(rz)) +
            uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz)) +
            uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
    up->z = ux * (dx * dz * (1.0f - cosdf(rz)) - dy * sindf(rz)) +
            uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz)) +
            uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47DD90", func_801178E0_mgmode);
#endif

/* Process: the cursor sprite; while shown it glides to slot D_8011B66A of D_8011B670 over
   D_8011B668 frames whenever the slot changes. */
void func_80117DD0_mgmode(void) {
    s16 last = -1;
    s16 x0;
    s16 dx;
    s16 y0;
    s16 dy;
    s16 i;
    f32 t;

    D_8011B66E_mgmode = 0;
    D_8011B66C_mgmode = InitEspriteSlot(func_8000B838_main(0x11000E), 0, 1);
    func_8000BCC8_main(D_8011B66C_mgmode, 1);
    func_8000BBD4_main(D_8011B66C_mgmode, 160, 120);
    func_8000BB94_main(D_8011B66C_mgmode);
    D_8011B664_mgmode = 160;
    D_8011B666_mgmode = 120;
    D_8011B668_mgmode = 10;
    omAddPrcObj(func_801180A4_mgmode, 0x3F00, 0x800, 0);
    while (TRUE) {
        HuPrcVSleep();
        if (D_8011B66E_mgmode != 0) {
            if (last != D_8011B66A_mgmode && D_8011B66A_mgmode != -1) {
                if (D_8011B670_mgmode[D_8011B66A_mgmode].unk0 != D_8011B664_mgmode ||
                    D_8011B670_mgmode[D_8011B66A_mgmode].unk2 != D_8011B666_mgmode) {
                    x0 = D_8011B664_mgmode;
                    y0 = D_8011B666_mgmode;
                    dx = D_8011B670_mgmode[D_8011B66A_mgmode].unk0 - D_8011B664_mgmode;
                    dy = D_8011B670_mgmode[D_8011B66A_mgmode].unk2 - D_8011B666_mgmode;
                    for (i = 1; i <= D_8011B668_mgmode; i++) {
                        t = sindf(90.0f / D_8011B668_mgmode * i);
                        D_8011B664_mgmode = x0 + dx * t;
                        D_8011B666_mgmode = y0 + dy * t;
                        func_8000BBD4_main(D_8011B66C_mgmode, D_8011B664_mgmode, D_8011B666_mgmode);
                        HuPrcVSleep();
                    }
                }
                last = D_8011B66A_mgmode;
            }
        } else {
            last = D_8011B66A_mgmode;
        }
        func_8000BBD4_main(D_8011B66C_mgmode, D_8011B664_mgmode, D_8011B666_mgmode);
    }
}

/* Process: fades sprite D_8011B66C in or out whenever D_8011B66E changes. */
void func_801180A4_mgmode(void) {
    s16 shown = 0;
    s16 i;

    while (TRUE) {
        HuPrcVSleep();
        if (shown == D_8011B66E_mgmode) {
            continue;
        }
        if (D_8011B66E_mgmode != 0) {
            func_8000BB54_main(D_8011B66C_mgmode);
            for (i = 0; i < 5; i++) {
                func_8000BBFC_main(D_8011B66C_mgmode, i * 63.75f);
                HuPrcVSleep();
            }
        } else {
            for (i = 0; i < 5; i++) {
                func_8000BBFC_main(D_8011B66C_mgmode, 255.0f - i * 63.75f);
                HuPrcVSleep();
            }
            func_8000BB94_main(D_8011B66C_mgmode);
        }
        shown = D_8011B66E_mgmode;
    }
}

void func_801181F4_mgmode(s16 arg0) {
    D_8011B664_mgmode = D_8011B670_mgmode[arg0].unk0;
    D_8011B666_mgmode = D_8011B670_mgmode[arg0].unk2;
    D_8011B66A_mgmode = arg0;
}

void func_8011822C_mgmode(MgModePair* pairs) {
    s16 i;

    D_8011B670_mgmode = pairs;
    for (i = 0; pairs[i].unk0 != -1 || pairs[i].unk2 != -1; i++) {
        D_8011B630_mgmode[i] = 0;
    }
}

void func_8011829C_mgmode(s16 arg0) {
    D_8011B668_mgmode = arg0;
}

void func_801182A8_mgmode(s16 arg0) {
    D_8011B66A_mgmode = arg0;
}

void func_801182B4_mgmode(s16 arg0) {
    D_8011B66E_mgmode = arg0;
}

void func_801182C0_mgmode(s16 arg0) {
    D_8011B630_mgmode[arg0] = 1;
}

/* Returns the nearest enabled slot of D_8011B670 lying in direction (dx, dy) from slot
   D_8011B66A (within 0.5 of it as unit vectors), or -1. */
s16 func_801182DC_mgmode(s16 dx, s16 dy) {
    f32 dir[32][2];
    f32 dist[32];
    f32 x;
    f32 y;
    f32 len;
    f32 ux;
    f32 uy;
    f32 best;
    s16 found;
    s16 i;

    for (i = 0; D_8011B670_mgmode[i].unk0 != -1 || D_8011B670_mgmode[i].unk2 != -1; i++) {
        if (i == D_8011B66A_mgmode || D_8011B630_mgmode[i] != 0) {
            dist[i] = -1.0f;
        } else {
            x = D_8011B670_mgmode[D_8011B66A_mgmode].unk0 - D_8011B670_mgmode[i].unk0;
            y = D_8011B670_mgmode[D_8011B66A_mgmode].unk2 - D_8011B670_mgmode[i].unk2;
            len = dist[i] = HuSqrtf(x * x + y * y);
            dir[i][0] = x / len;
            dir[i][1] = y / len;
        }
    }
    len = HuSqrtf(dx * dx + dy * dy);
    ux = dx / len;
    uy = dy / len;
    for (i = 0; D_8011B670_mgmode[i].unk0 != -1 || D_8011B670_mgmode[i].unk2 != -1; i++) {
        if (!(dist[i] < 0.0f)) {
            x = ux - dir[i][0];
            y = uy - dir[i][1];
            if (HuSqrtf(x * x + y * y) > 0.5f) {
                dist[i] = -1.0f;
            }
        }
    }
    best = 100000.0f;
    found = -1;
    for (i = 0; D_8011B670_mgmode[i].unk0 != -1 || D_8011B670_mgmode[i].unk2 != -1; i++) {
        if (!(dist[i] < 0.0f) && dist[i] < best) {
            best = dist[i];
            found = i;
        }
    }
    return found;
}

void func_80118624_mgmode(s16 dst, s16 src) {
    HmfModelData[dst].pos.x = HmfModelData[src].pos.x;
    HmfModelData[dst].pos.y = HmfModelData[src].pos.y;
    HmfModelData[dst].pos.z = HmfModelData[src].pos.z;
}

/* hmfman's vertex-scatter effect (HmfModel.unkBC; 13F90.c's HmfFxWork) as this unit's hooks
   use it: one MgFxPart per face group. */
typedef struct MgFxPart {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 life;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ Vec unk24;
} MgFxPart; /* size 0x30 */

typedef struct MgFxWork {
    /* 0x00 */ s16 motion;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 spread;
    /* 0x0C */ char unk0C[0xC];
    /* 0x18 */ void (*hook)(s16);
    /* 0x1C */ Vec center;
    /* 0x28 */ Vec verts[4];
    /* 0x58 */ MgFxPart* parts;
} MgFxWork; /* size 0x5C */

typedef struct MgFxHmf {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 groupCount;
} MgFxHmf;

#define MG_FX_WORK(m) ((MgFxWork*)(m)->unkBC)
#define MG_FX_GROUPS(m) (((MgFxHmf*)(m)->hmf)->groupCount)

s16 HmfAnimRead(HmfData* hmf, s32 dataNum, char* name);
void func_8003302C_main(s32, u8);
void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
u8 rand8(void);
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];

extern s32 D_8011A3E4_mgmode[4];
extern s16 D_8011A3F4_mgmode;
extern s16 D_8011B678_mgmode[][4];
extern s16 D_8011B698_mgmode[];
extern s16 D_8011B808_mgmode;

void func_801188BC_mgmode(omObjData* obj);
void func_801189C4_mgmode(s16 model);
void func_80118B8C_mgmode(s16 model);

/* Creates the four smoke-puff models of effect set D_8011A3F4 around center (x, y, z) with the
   given spread, and the object that keeps emitting them; returns the set index. */
s16 func_80118678_mgmode(f32 x, f32 y, f32 z, f32 spread) {
    omObjData* obj;
    MgFxWork* work;
    s16 model;
    s16 anim;
    s16 i;

    for (i = 0; i < 4; i++) {
        D_8011B678_mgmode[D_8011A3F4_mgmode][i] = model = func_8000B108_main(D_8011A3E4_mgmode[i], 0x2A9);
        anim = HmfAnimRead(HmfModelData[model].hmf, 0xB0048, "e268p01_I8");
        func_8001C8A8_main(model, 2);
        func_8003302C_main(anim, i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x20000, 0x20000);
        func_8001C448_main(model);
        func_8001C954_main(model);
        func_8001C514_main(model);
        func_80013390_main(model, -1, NULL, func_80118B8C_mgmode);
        work = MG_FX_WORK(&HmfModelData[model]);
        work->center.x = x;
        work->center.y = y;
        work->center.z = z;
        work->spread = spread;
        func_8001C258_main(model, 4, 4);
    }
    obj = omAddObj(10, 10, 10, -1, func_801188BC_mgmode);
    obj->work[0] = D_8011A3F4_mgmode;
    D_8011A3F4_mgmode++;
    return (s16)obj->work[0];
}

void func_80118888_mgmode(s16 arg0) {
    D_8011A3F8_mgmode[arg0] = 1;
}

void func_801188A4_mgmode(s16 arg0) {
    D_8011A3F8_mgmode[arg0] = 0;
}

/* Object: while set work[0] is on, restarts its four puff models in turn. */
void func_801188BC_mgmode(omObjData* obj) {
    s16 set = (s16)obj->work[0];
    s16 i;

    if (D_8011A3F8_mgmode[set] != 0) {
        for (i = 0; i < 4; i++) {
            func_8001C258_main(D_8011B678_mgmode[set][i], 4, 0);
            if (((D_8011B698_mgmode[set] + i) & 3) == 0) {
                func_801189C4_mgmode(D_8011B678_mgmode[set][i]);
            }
        }
        D_8011B698_mgmode[set]++;
    }
}

/* Relaunches the first landed particle of model's effect from a random point around its center. */
void func_801189C4_mgmode(s16 model) {
    MgFxHmf* hmf = (MgFxHmf*)HmfModelData[model].hmf;
    MgFxWork* work = MG_FX_WORK(&HmfModelData[model]);
    MgFxPart* part = work->parts;
    s16 spread = work->spread;
    s16 count = hmf->groupCount;
    s16 i;

    for (i = 0; i < count; i++, part++) {
        if (part->pos.y <= 0.0f) {
            part->pos.x = ((((rand8() & 0xFF) << 1) * spread) >> 8) + work->center.x - spread;
            part->pos.y = work->center.y;
            part->pos.z = ((((rand8() & 0xFF) << 1) * spread) >> 8) + work->center.z - spread;
            part->vel.x = ((s32)(((rand8() & 0xFF) * 5U) >> 7) - 5) / 2;
            part->vel.y = 0.0f;
            part->vel.z = ((s32)(((rand8() & 0xFF) * 5U) >> 7) - 5) / 2;
            part->life = 2.0f;
            return;
        }
    }
}

/* Effect hook: on the first frame parks every particle, then moves the airborne ones and lets them
   fall; landed ones go dark. */
void func_80118B8C_mgmode(s16 model) {
    MgFxHmf* hmf = (MgFxHmf*)HmfModelData[model].hmf;
    MgFxWork* work = MG_FX_WORK(&HmfModelData[model]);
    MgFxPart* part;
    s16 count = hmf->groupCount;
    s16 i;

    if (work->frame == 0) {
        work->flags &= ~4;
        part = work->parts;
        for (i = 0; i < count; i++, part++) {
            part->life = part->unk24.x = part->unk24.y = part->unk24.z = part->pos.x = part->pos.y =
                part->pos.z = 0.0f;
            part->unk04 = 1.0f;
        }
        work->frame++;
    }
    part = work->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->pos.y > 0.0f) {
            part->pos.x += part->vel.x;
            part->pos.y += part->vel.y - 8.0f;
            part->pos.z += part->vel.z;
        } else {
            part->life = 0.0f;
        }
    }
}

void func_80118CD8_mgmode(void) {
    _ClearFlag(0x1C);
    func_80050064_main(1);
    _ClearFlag(0xD);
    _SetFlag(0x1C);
}

/* Turns pad D_8011B808's D-pad into a stick deflection of 50. */
void func_80118D0C_mgmode(void) {
    f32 y = 0.0f;
    f32 x = 0.0f;
    f32 len;

    if (D_800CDA7C_main[D_8011B808_mgmode] & 0x200) {
        x = -1.0f;
    }
    if (D_800CDA7C_main[D_8011B808_mgmode] & 0x100) {
        x += 1.0f;
    }
    if (D_800CDA7C_main[D_8011B808_mgmode] & 0x800) {
        y += 1.0f;
    }
    if (D_800CDA7C_main[D_8011B808_mgmode] & 0x400) {
        y += -1.0f;
    }
    if ((x == 0.0f) & (y == 0.0f)) {
        return;
    }
    {
        len = HuSqrtf(x * x + y * y);
        D_800CBB6E_main[D_8011B808_mgmode] = x / len * 50.0f;
        D_800D20A1_main[D_8011B808_mgmode] = y / len * 50.0f;
    }
}

/* .data (0x8011A3E0) */
s16 D_8011A3E0_mgmode = -1;
s32 D_8011A3E4_mgmode[4] = { 0xB002B, 0xB002C, 0xB002D, 0xB002E };
s16 D_8011A3F4_mgmode = 0;
s16 D_8011A3F8_mgmode[4] = { 0, 0, 0, 0 };
