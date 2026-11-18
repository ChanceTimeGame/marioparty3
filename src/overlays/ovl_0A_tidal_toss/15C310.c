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

// tt A: Tidal Toss

typedef func_800E1BA8_minigame_ObjData MgWork;
typedef struct TtPlayer TtPlayer;

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]); /* matrix copy */
void func_8007DFE0_main(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
f32 fabsf(f32);
f64 fabs(f64);
f32 sqrtf(f32);
u8 rand8(void);

// minigame
void func_800E1804_minigame(void);
void func_800E12EC_minigame(omObjData* obj, f32 arg1);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1334_minigame(omObjData* obj, f32 arg1);
void func_800E1340_minigame(omObjData* obj, f32 arg1);
s32 func_800E4A90_minigame(omObjData* obj);
extern s32 D_800EBEB0_minigame[];

// LOCAL
void func_80105B04_tidal_toss(omObjData* obj);
void func_80105C00_tidal_toss(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out);
void func_80105C80_tidal_toss(f32 (*src)[4], f32 (*dst)[4]);
void func_8010600C_tidal_toss(void);
void func_801085A4_tidal_toss(void);
void func_80108638_tidal_toss(omObjData* obj);
u32 func_8010A7F8_tidal_toss(void);
s16 func_8010A90C_tidal_toss(s32 id);
s16 func_8010A954_tidal_toss(s16 tex, s16 n);
HuSprite_Unk84_Unk00_Struct* func_8010AA1C_tidal_toss(s16 tex, s16 frame);

extern D_80111B50_vine_with_me_Struct D_8010AEB0_tidal_toss;
extern u32 D_8010AAFC_tidal_toss; /* random seed */
extern f32 D_8010B058_tidal_toss[4][4]; /* world to view (D_8010B090 is its [3][2]) */
extern f32 D_8010B090_tidal_toss; /* D_8010B058[3][2]: the view depth offset */
extern f32 D_8010B098_tidal_toss[4][4]; /* view to world */
extern f32 D_8010B0D8_tidal_toss; /* tan(fov / 2) */

void func_801059A0_tidal_toss(void) {
    omObjData* obj;
    u8 cam;

    Hu3DAnimInit(3);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    omInitObjMan(0x10, 0);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 45.0f, 80.0f, 8000.0f);
    func_800E1804_minigame();
    func_80105B04_tidal_toss(obj);
    func_8010600C_tidal_toss();
    memset(&D_8010AEB0_tidal_toss, 0, 0x28);
    D_8010AEB0_tidal_toss.unk01 = 4;
    func_800E5EA0_minigame(&D_8010AEB0_tidal_toss);
    func_801085A4_tidal_toss();
}

void func_80105B04_tidal_toss(omObjData* obj) {
    HuCamera* cam;
    f32 s;

    CZoom = 1600.0f;
    CRot.x = -30.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 0.0f;
    omOutView(obj);
    cam = gCameraList;
    s = sindf(cam->fov[0] / 2.0);
    D_8010B0D8_tidal_toss = s / cosdf(cam->fov[0] / 2.0);
    guMtxL2F(D_8010B058_tidal_toss, &cam->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010B098_tidal_toss, &cam->mtxs[0].lookAtMtx);
    func_80105C80_tidal_toss(D_8010B098_tidal_toss, D_8010B098_tidal_toss);
}

void func_80105C00_tidal_toss(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out) {
    out[0] = x * m[0][0] + y * m[1][0] + z * m[2][0];
    out[1] = x * m[0][1] + y * m[1][1] + z * m[2][1];
    out[2] = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

void func_80105C80_tidal_toss(f32 (*src)[4], f32 (*dst)[4]) {
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
        func_80105C00_tidal_toss(dst, -m[3][0], -m[3][1], -m[3][2], dst[3]);
    }
}

void func_80105E70_tidal_toss(Vec* pos, f32* out) {
    f32 m[4][4];
    f32 t;
    f32 w;

    func_8007DFE0_main(m, pos->x, pos->y, pos->z);
    guMtxCatF(m, D_8010B058_tidal_toss, m);
    t = m[3][2] * D_8010B0D8_tidal_toss;
    w = fabsf(t);
    if (w != 0.0) {
        out[0] = m[3][0] * 160.0f / w / 1.3333334f;
        out[1] = -m[3][1] * 120.0f / w;
    }
}

void func_80105F40_tidal_toss(f32 x, f32 y, f32 z, f32* out) {
    f32 m[4][4];
    f32 d;
    f32 w;

    d = z + D_8010B090_tidal_toss;
    w = fabsf(d * D_8010B0D8_tidal_toss);
    func_8007DFE0_main(m, 2.0f * x * w * 1.3333334f / 320.0f, -(2.0f * y * w / 240.0f), d);
    guMtxCatF(m, D_8010B098_tidal_toss, m);
    out[0] = m[3][0];
    out[1] = m[3][1];
    out[2] = m[3][2];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010600C_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80106104_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80106480_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80106514_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_801065AC_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80106D24_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80108460_tidal_toss);

void func_801085A4_tidal_toss(void) {
    s32 i;

    func_800E18D8_minigame();
    D_800EC280_minigame = 0;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 15, 50, -1, func_80108638_tidal_toss);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80108638_tidal_toss);

void func_80108F08_tidal_toss(omObjData* obj, u32 file0, s32 file1, s32 player, u16 arg4) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80109180_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80109584_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010961C_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010A11C_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010A490_tidal_toss);

void func_8010A7E4_tidal_toss(omObjData* obj, MgWork** work, TtPlayer** ep) {
    MgWork* w = obj->data;

    *work = w;
    *ep = w->unk158;
}

u32 func_8010A7F8_tidal_toss(void) {
    D_8010AAFC_tidal_toss = D_8010AAFC_tidal_toss * 0x41C64E6D + 0x3039;
    D_8010AAFC_tidal_toss += rand8();
    return D_8010AAFC_tidal_toss >> 16;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010A850_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010A8A4_tidal_toss);

s16 func_8010A90C_tidal_toss(s32 id) {
    void* file;
    s16 sprite;

    file = DataRead(id);
    sprite = func_80055810_main(file);
    DataClose(file);
    return sprite;
}

s16 func_8010A954_tidal_toss(s16 tex, s16 n) {
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

HuSprite_Unk84_Unk00_Struct* func_8010AA1C_tidal_toss(s16 tex, s16 frame) {
    return &func_80055194_main(tex)->unk00[frame];
}
