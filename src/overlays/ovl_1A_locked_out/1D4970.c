#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/data.h"
#include "game/gamemes.h"
#include "game/wipe.h"
#include "mallocblock.h"

// lo A: Locked Out

typedef func_800E1BA8_minigame_ObjData MgWork;

/* MgWork::unk158 of a player. */
typedef struct LoPlayer {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ u8 unk0C[0x2C];
} LoPlayer; /* size 0x38 */

s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]); /* matrix copy */
void func_8007DFE0_main(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
f32 fabsf(f32);
f64 fabs(f64);
f32 sqrtf(f32);
extern s32 D_800A178C_main[][6];
u8 rand8(void);
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
void func_800E12EC_minigame(omObjData* obj, f32 arg1);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1334_minigame(omObjData* obj, f32 arg1);
void func_800E1340_minigame(omObjData* obj, f32 arg1);
s32 func_800E2250_minigame(omObjData* obj, s16 x, s16 y); /* stick: x << 16 | y */
s32 func_800E4A90_minigame(omObjData* obj);
extern s32 D_800EBEB0_minigame[];

void func_80105C34_locked_out(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out);
void func_80105CB4_locked_out(f32 (*src)[4], f32 (*dst)[4]);
void func_801090FC_locked_out(omObjData* obj, MgWork** work, LoPlayer** lp);
s16 func_80109FF4_locked_out(s16 tex, s16 n);

/* The ground/camera object's data (func_80106134_locked_out); Slot Synch's SsGround. */
typedef struct LoGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} LoGround; // Size 0xB4

/* A door (D_8010A638_locked_out[3]). */
typedef struct LoDoor {
    /* 0x00 */ Vec pos;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 model; /* low byte of obj->model[2 + i] */
    /* 0x0E */ u8 unk0E; /* linked model */
    /* 0x0F */ u8 unk0F; /* model */
    /* 0x10 */ u8 unk10;
    /* 0x11 */ char unk11[3];
} LoDoor; // Size 0x14

void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);

void func_80105B38_locked_out(omObjData* obj);
void func_80106040_locked_out(void);
void func_80106134_locked_out(omObjData* obj);
void func_80106424_locked_out(omObjData* obj);
void func_801064E0_locked_out(omObjData* obj);
void func_8010713C_locked_out(void);
void func_80109110_locked_out(void);
s32 func_80109D70_locked_out(void);
void func_80106FBC_locked_out(omObjData* obj);
void func_801071D8_locked_out(omObjData* obj);
void func_80107844_locked_out(omObjData* obj, u32 file0, s32 file1, s32 player, u16 arg4);
void func_801089F8_locked_out(omObjData* obj, f32 x, f32 y, f32 z);
void func_80109CDC_locked_out(void);
f32 func_80109DBC_locked_out(f32 x, f32 z);
f32 func_80109E34_locked_out(Vec* a, Vec* b);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);

extern Vec D_8010A110_locked_out[7]; /* positions; the doors use [0], [3], [6] */
extern u32 D_8010A1E8_locked_out; /* random seed */
extern D_80111B50_vine_with_me_Struct D_8010A588_locked_out;
extern omObjData* D_8010A610_locked_out[10];
extern LoDoor D_8010A638_locked_out[3];
extern s16 D_8010A674_locked_out;
extern s16 D_8010A676_locked_out;
extern s16 D_8010A678_locked_out;
extern s16 D_8010A67A_locked_out;
extern f32 D_8010A680_locked_out[4][4]; /* world to view (D_8010A6B8 is its [3][2]) */
extern f32 D_8010A6B8_locked_out; /* D_8010A680[3][2] */
extern f32 D_8010A6C0_locked_out[4][4]; /* view to world */
extern f32 D_8010A700_locked_out; /* tan(fov / 2) */

void func_801059A0_locked_out(void) {
    omObjData* obj;
    u8 cam;

    Hu3DAnimInit(2);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 45.0f, 80.0f, 8000.0f);
    func_800E1804_minigame();
    func_80105B38_locked_out(obj);
    func_80106040_locked_out();
    memset(&D_8010A588_locked_out, 0, 0x28);
    D_8010A588_locked_out.unk01 = 4;
    func_800E5EA0_minigame(&D_8010A588_locked_out);
    func_8010713C_locked_out();
    D_8010A676_locked_out = 9;
    D_8010A678_locked_out = 0;
    func_80109110_locked_out();
    func_8001F38C_main(0, 0, 0);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105B38_locked_out(omObjData* obj) {
    HuCamera* cam;
    f32 s;

    CZoom = 1400.0f;
    CRot.x = -40.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 0.0f;
    omOutView(obj);
    cam = gCameraList;
    s = sindf(cam->fov[0] / 2.0);
    D_8010A700_locked_out = s / cosdf(cam->fov[0] / 2.0);
    guMtxL2F(D_8010A680_locked_out, &cam->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010A6C0_locked_out, &cam->mtxs[0].lookAtMtx);
    func_80105CB4_locked_out(D_8010A6C0_locked_out, D_8010A6C0_locked_out);
}

void func_80105C34_locked_out(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out) {
    out[0] = x * m[0][0] + y * m[1][0] + z * m[2][0];
    out[1] = x * m[0][1] + y * m[1][1] + z * m[2][1];
    out[2] = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

void func_80105CB4_locked_out(f32 (*src)[4], f32 (*dst)[4]) {
    f32 m[4][4];
    f32 c0;
    f32 c1;
    f32 c2;
    f32 det;

    func_8002367C_main(m, src);
    c0 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    c1 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
    c2 = m[1][0] * m[2][1] - m[1][1] * m[2][0];
    det = c0 * m[0][0] + c1 * m[0][1] + c2 * m[0][2];
    if (det != 0.0f) {
        det = 1.0f / det;
        dst[0][0] = c0 * det;
        dst[1][0] = c1 * det;
        dst[2][0] = c2 * det;
        dst[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * det;
        dst[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * det;
        dst[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * det;
        dst[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * det;
        dst[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * det;
        dst[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * det;
        dst[0][3] = dst[1][3] = dst[2][3] = 0.0f;
        dst[3][3] = 1.0f;
        func_80105C34_locked_out(dst, -m[3][0], -m[3][1], -m[3][2], dst[3]);
    }
}

void func_80105EA4_locked_out(Vec* pos, f32* out) {
    f32 m[4][4];
    f32 t;
    f32 w;

    func_8007DFE0_main(m, pos->x, pos->y, pos->z);
    guMtxCatF(m, D_8010A680_locked_out, m);
    t = m[3][2] * D_8010A700_locked_out;
    w = fabsf(t);
    if (w != 0.0) {
        out[0] = m[3][0] * 160.0f / w / 1.3333334f;
        out[1] = -m[3][1] * 120.0f / w;
    }
}

void func_80105F74_locked_out(f32 x, f32 y, f32 z, f32* out) {
    f32 m[4][4];
    f32 d;
    f32 w;

    d = z + D_8010A6B8_locked_out;
    w = fabsf(d * D_8010A700_locked_out);
    func_8007DFE0_main(m, 2.0f * x * w * 1.3333334f / 320.0f, -(2.0f * y * w / 240.0f), d);
    guMtxCatF(m, D_8010A6C0_locked_out, m);
    out[0] = m[3][0];
    out[1] = m[3][1];
    out[2] = m[3][2];
}

void func_80106040_locked_out(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_8010A67A_locked_out = (f32)func_80109D70_locked_out() * (1.0 / 65536.0) * 3.0;
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 8, 0, -1, func_80106134_locked_out);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106424_locked_out);
    D_8010A674_locked_out = 0;
}

void func_80106134_locked_out(omObjData* obj) {
    LoGround* gw;
    s32 i;
    s32 attr;

    obj->data = gw = HuMemAllocTag(sizeof(LoGround), 31000);
    memset(gw, 0, sizeof(LoGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E139C_minigame(obj, 0.0f, -600.0f, -615.0f, 600.0f, 615.0f);
    attr = 0x2D9;
    obj->model[0] = func_8000B108_main(0x3B0000, 0x2D9);
    obj->model[1] = func_8000B108_main(0x3B0003, 0x2D9);
    obj->model[6] = func_8000B108_main(0x3B0010, 0x2DD);
    obj->model[7] = func_8000B108_main(0x3B0011, 0x2DD);
    for (i = 0; i < 3; i++) {
        D_8010A638_locked_out[i].pos.x = D_8010A110_locked_out[i * 3].x;
        D_8010A638_locked_out[i].pos.y = D_8010A110_locked_out[i * 3].y;
        D_8010A638_locked_out[i].pos.z = D_8010A110_locked_out[i * 3].z;
        D_8010A638_locked_out[i].unk0C = 0;
        D_8010A638_locked_out[i].unk10 = 1;
        D_8010A638_locked_out[i].model = obj->model[2 + i] = func_8000B108_main((D_8010A67A_locked_out + 4) | 0x3B0000, attr);
        Hu3DModelPosSet(obj->model[2 + i], D_8010A638_locked_out[i].pos.x, D_8010A638_locked_out[i].pos.y, D_8010A638_locked_out[i].pos.z);
        func_8001C92C_main(obj->model[2 + i], 0.0f);
        D_8010A638_locked_out[i].unk0F = func_8000B0A0_main(7, 0x2DD);
        func_8001C92C_main(D_8010A638_locked_out[i].unk0F, 0.0f);
        Hu3DModelRotSet(D_8010A638_locked_out[i].unk0F, 90.0f, 0.0f, 0.0f);
        D_8010A638_locked_out[i].unk0E = Hu3DModelLink(obj->model[6]);
        func_8001C258_main(D_8010A638_locked_out[i].unk0E, 4, 4);
        func_8001C92C_main(D_8010A638_locked_out[i].unk0E, 0.0f);
    }
    obj->model[5] = func_8000B108_main(0x3B000A, 0x2B9);
    obj->func = func_801064E0_locked_out;
}

void func_80106424_locked_out(omObjData* obj) {
    LoGround* gw;

    obj->data = gw = HuMemAllocTag(sizeof(LoGround), 31000);
    memset(gw, 0, sizeof(LoGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E139C_minigame(obj, 0.0f, -600.0f, -615.0f, 600.0f, 665.0f);
    obj->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801064E0_locked_out);

// register allocation and scheduling of the HmfModelData base load (masked 4)
#ifdef NON_MATCHING
/* Pushes the player out of the doors' swing circles. */
void func_80106FBC_locked_out(omObjData* obj) {
    HmfModel* m;
    Vec pos;
    f32 n;
    f32 r;
    f32 a;
    s32 i;
    LoDoor* d;

    for (i = 0; i < 3; i++) {
        d = &D_8010A638_locked_out[i];
        if (d->unk0C != 0) {
            m = &HmfModelData[d->unk0E];
            n = D_800CCF58_main[m->unk02].unk02;
            r = m->unk40 * 175.0 / n + 50.0;
            pos.x = d->pos.x - 86.5;
            pos.y = d->pos.y;
            pos.z = d->pos.z;
            if (!(r < func_80109E34_locked_out(&pos, &obj->trans))) {
                a = func_80109DBC_locked_out(pos.x - obj->trans.x, pos.z - obj->trans.z);
                obj->trans.x = pos.x - r * sindf(a);
                obj->trans.z = pos.z - r * cosdf(a);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106FBC_locked_out);
#endif

void func_8010713C_locked_out(void) {
    s32 i;

    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EC280_minigame = 0;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 15, 50, -1, func_801071D8_locked_out);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A298_locked_out);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A2A0_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801071D8_locked_out);

/* A player's actor work: the framework's func_800E1BA8_minigame cut down. */
void func_80107844_locked_out(omObjData* obj, u32 file0, s32 file1, s32 player, u16 arg4) {
    MgWork* work;
    s32 i;

    for (i = 0; i < obj->mdlcnt; i++) {
        obj->model[i] = 0;
    }
    obj->data = HuMemAllocTag(sizeof(MgWork), 0x7918);
    memset(obj->data, 0, sizeof(MgWork));
    work = obj->data;
    work->unkE8 = HuMemAllocTag(obj->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), 0x7918);
    memset(work->unkE8, 0, obj->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData));
    obj->model[0] = func_8000B108_main(file0 | file1, arg4);
    for (i = 0; i < obj->mtncnt; i++) {
        obj->motion[i] = -1;
    }
    for (i = 0; i < obj->mtncnt; i++) {
        func_800E1BA8_minigame_UnkE8_ObjData* mtn = work->unkE8;
        mtn[i].unk02 = 0;
        mtn[i].unk00 = 0;
    }
    work->unk57 = GwPlayer[(u16)player].pad;
    work->unk52 = 0;
    work->unkB4 = 1.0f;
    work->unkD0 = 0xFFFF;
    work->unk4C = 0.5f;
    work->unkCC = 1.0f;
    work->unkA0 = work->unk9C = work->unkA4 = 0.0f;
    work->unk59 = player;
    work->unk3C = atan2df(-obj->trans.x, -obj->trans.z);
    func_800E1328_minigame(obj, 60.0f);
    func_800E1334_minigame(obj, 150.0f);
    func_800E1340_minigame(obj, 20.0f);
    func_800E12EC_minigame(obj, 1000.0f);
    switch (file0 >> 16) {
        case 6:
            work->unkAC = 0.8f;
            break;
        case 5:
            work->unkAC = 0.9f;
            break;
        case 4:
        default:
            work->unkAC = 1.0f;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80107ABC_locked_out);

/* Spawns effect 9..11 (the first free one) at a point. */
void func_801089F8_locked_out(omObjData* obj, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (HmfModelData[obj->model[i]].unk18 & 4) {
            func_800E4C88_minigame(obj, i, x, y, z, 0.0f, 0.0f);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80108A90_locked_out);

void func_801090FC_locked_out(omObjData* obj, MgWork** work, LoPlayer** ep) {
    MgWork* w = obj->data;

    *work = w;
    *ep = w->unk158;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109110_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109264_locked_out);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A468_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109444_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109858_locked_out);

void func_80109CDC_locked_out(void) {
    omObjData* o;
    s32 i;

    for (i = 0; i < D_8010A676_locked_out; i++) {
        o = D_8010A610_locked_out[i];
        func_8001ACDC_main(o->model[0]);
        func_8001ACDC_main(o->model[1]);
        HuMemFree(o->data);
        o->data = NULL;
        omDelObj(o);
    }
}

s32 func_80109D70_locked_out(void) {
    u32 r;

    r = (rand8() + D_8010A1E8_locked_out) * 0x41C64E6D + 0x3039;
    D_8010A1E8_locked_out = r;
    return r >> 16;
}

/* atan2df(x, z) wrapped to -180..180. */
f32 func_80109DBC_locked_out(f32 x, f32 z) {
    f32 a;
    f32 full = 360.0f;

    a = atan2df(x, z);
    if (a < -180.0f) {
        a += full;
    } else if (a >= 180.0) {
        a -= full;
    }
    return a;
}

// register allocation (masked 0, raw 4)
#ifdef NON_MATCHING
/* Distance in XZ. */
f32 func_80109E34_locked_out(Vec* a, Vec* b) {
    f32 dx;
    f32 dz;

    dx = a->x - b->x;
    dx = dx * dx;
    dz = a->z - b->z;
    return sqrtf(dx + dz * dz);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109E34_locked_out);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109E88_locked_out);

s16 func_80109FAC_locked_out(s32 id) {
    void* file;
    s16 sprite;

    file = DataRead(id);
    sprite = func_80055810_main(file);
    DataClose(file);
    return sprite;
}

s16 func_80109FF4_locked_out(s16 tex, s16 n) {
    s16 grp;
    s32 i;

    if (tex == -1) {
        return -1;
    }
    grp = HuSprGrpCreate(n, 0);
    if (grp == -1) {
        return -1;
    }
    for (i = 0; i < n; i++) {
        func_80055024_main(grp, i, tex, 0);
    }
    return grp;
}

#ifdef NON_MATCHING
/* masked 2: retail scales the index before loading unk00 (scheduling only) */
void* func_8010A0BC_locked_out(s16 tex, s16 frame) {
    return func_80055194_main(tex)->unk00[frame].unk00;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_8010A0BC_locked_out);
#endif
