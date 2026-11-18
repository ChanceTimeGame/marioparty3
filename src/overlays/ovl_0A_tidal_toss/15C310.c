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
/* MgWork::unk158 of a player */
typedef struct TtPlayer {
    /* 0x00 */ char unk00[0x2C];
    /* 0x2C */ u8 unk2C; /* character */
    /* 0x2D */ char unk2D[2];
    /* 0x2F */ u8 unk2F; /* won */
} TtPlayer;

#define TT_PLAYER(i) ((TtPlayer*)((MgWork*)D_800EC598_minigame[i]->data)->unk158)

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
void func_800E1490_minigame(u16 arg0);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E1404_minigame(omObjData* obj, f32 arg1, f32 arg2);
extern s32 D_800EBEB0_minigame[];
void func_800E6F0C_minigame(s32 arg0);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);

// LOCAL
void func_80105B04_tidal_toss(omObjData* obj);
void func_80105C00_tidal_toss(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out);
void func_80105C80_tidal_toss(f32 (*src)[4], f32 (*dst)[4]);
void func_8010600C_tidal_toss(void);
void func_801085A4_tidal_toss(void);
void func_80108638_tidal_toss(omObjData* obj);
s32 func_8010A7F8_tidal_toss(void);
void func_80106104_tidal_toss(omObjData* obj);
void func_80106480_tidal_toss(omObjData* obj);
void func_80106514_tidal_toss(omObjData* obj);
void func_801065AC_tidal_toss(omObjData* obj);
void func_80106D24_tidal_toss(Gfx** gfx, s32 arg1, s32 arg2);
void func_80108460_tidal_toss(f32 d);
void func_80109584_tidal_toss(omObjData* obj, f32 x, f32 y, f32 z);
f32 func_8010A850_tidal_toss(Vec* a, Vec* b);
f32 func_8010A8A4_tidal_toss(f32 x, f32 z);
s16 func_8010A90C_tidal_toss(s32 id);
s16 func_8010A954_tidal_toss(s16 tex, s16 n);
HuSprite_Unk84_Unk00_Struct* func_8010AA1C_tidal_toss(s16 tex, s16 frame);

/* obj->data of the pool objects (the framework's ground block) */
typedef struct TtGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} TtGround; /* size 0xB4 */

typedef struct TtSplash {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ u8 unk10;
} TtSplash; /* size 0x14 */

typedef struct TtCloud {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ f32 fx;
    /* 0x08 */ f32 fy;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} TtCloud; /* size 0x24 */

extern D_80111B50_vine_with_me_Struct D_8010AEB0_tidal_toss;
extern s16 D_8010AA74_tidal_toss[3][2];
extern f32 D_8010AA80_tidal_toss[3];
extern s16 D_8010AED8_tidal_toss;
extern s16 D_8010AEDA_tidal_toss;
extern s16 D_8010AEE8_tidal_toss[];
extern s16 D_8010AEEC_tidal_toss[];
extern s16 D_8010AF38_tidal_toss;
extern s16 D_8010AF3A_tidal_toss;
extern s16 D_8010AF40_tidal_toss; /* game state */
extern u8 D_8010AA70_tidal_toss; /* the solo player */
extern s32 D_8010AA8C_tidal_toss; /* message / wipe timer */
extern s16 D_8010AA8E_tidal_toss[]; /* [0]: the low half of D_8010AA8C (big-endian), read as the wipe-out speed */
extern u16 D_8010AA90_tidal_toss; /* game timer, frames */
extern s32 D_8010AA94_tidal_toss; /* winner: the solo player, else -1 */
extern s16 D_8010ADE0_tidal_toss; /* frames to the music */
extern void* D_8010AF3C_tidal_toss;
extern TtSplash D_8010AF48_tidal_toss[8];
extern TtCloud D_8010AFE8_tidal_toss[3];
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

void func_8010600C_tidal_toss(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106104_tidal_toss);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106480_tidal_toss);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106514_tidal_toss);
    D_8010AF40_tidal_toss = 0;
}

/* The pool: its ground work, sprites and the water display list model. */
void func_80106104_tidal_toss(omObjData* obj) {
    TtGround* gw;
    s32 i;
    TtSplash* sp;
    TtCloud* cl;

    obj->data = gw = HuMemAllocTag(sizeof(TtGround), 0x7918);
    memset(gw, 0, sizeof(TtGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E1404_minigame(obj, 0.0f, 730.0f);
    D_8010AED8_tidal_toss = func_8010A90C_tidal_toss(0x2B0000);
    D_8010AEE8_tidal_toss[0] = func_8010A954_tidal_toss(D_8010AED8_tidal_toss, 1);
    func_80054904_main(D_8010AEE8_tidal_toss[0], 0, 160, 120);
    HuSprAttrSet(D_8010AEE8_tidal_toss[0], 0, 0x4000);
    D_8010AF38_tidal_toss = obj->model[0] = func_8000B108_main(0x2B0003, 0x4002CD);
    func_8001C954_main(obj->model[0]);
    obj->model[1] = func_8000B108_main(0x2B0004, 0x2D9);
    obj->model[2] = func_8001AC8C_main(0x80, func_80106D24_tidal_toss, 2);
    D_8010AF3A_tidal_toss = func_8010A90C_tidal_toss(0x2B0001);
    for (i = 0, sp = D_8010AF48_tidal_toss; i < 8; i++, sp++) {
        sp->unk10 = 0;
        sp->unk00 = sp->unk04 = sp->unk08 = sp->unk0C = 0.0f;
    }
    D_8010AEDA_tidal_toss = func_8010A90C_tidal_toss(0x2B0002);
    D_8010AEEC_tidal_toss[0] = func_8010A954_tidal_toss(D_8010AEDA_tidal_toss, 3);
    for (cl = D_8010AFE8_tidal_toss, i = 0; i < 3; i++, cl++) {
        cl->x = cl->fx = D_8010AA74_tidal_toss[i][0];
        cl->y = cl->fy = D_8010AA74_tidal_toss[i][1];
        cl->unk0C = cl->unk10 = D_8010AA80_tidal_toss[i];
        cl->unk14 = (f32)func_8010A7F8_tidal_toss() * (1.0 / 65536.0) * 360.0;
        cl->unk18 = (f32)func_8010A7F8_tidal_toss() * (1.0 / 65536.0) * 360.0;
        cl->unk1C = 2.0 * ((f32)func_8010A7F8_tidal_toss() * (1.0 / 65536.0)) + 2.0;
        cl->unk20 = (f32)func_8010A7F8_tidal_toss() * (1.0 / 65536.0) * 1.5 + 1.0;
        HuSprAttrSet(D_8010AEEC_tidal_toss[0], i, 0x20005808);
        func_80054904_main(D_8010AEEC_tidal_toss[0], i, cl->x, cl->y);
    }
    obj->func = func_801065AC_tidal_toss;
}

void func_80106480_tidal_toss(omObjData* obj) {
    TtGround* gw;

    obj->data = gw = HuMemAllocTag(sizeof(TtGround), 0x7918);
    memset(gw, 0, sizeof(TtGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 5.0f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E1404_minigame(obj, 20.0f, 345.0f);
    obj->func = NULL;
}

void func_80106514_tidal_toss(omObjData* obj) {
    TtGround* gw;

    obj->data = gw = HuMemAllocTag(sizeof(TtGround), 0x7918);
    memset(gw, 0, sizeof(TtGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.05f);
    func_800E1310_minigame(obj, 20.0f);
    func_800E1404_minigame(obj, -800.0f, 1380.0f);
    obj->func = NULL;
}

/* The game flow: start message, 30 s countdown, result, wipe out, return; then the splashes and clouds. */
void func_801065AC_tidal_toss(omObjData* obj) {
    s8 chr[4];
    s32 i;
    s32 n;
    s32 won;
    TtSplash* sp;
    TtCloud* cl;
    HuSprite* spr;
    f32 sx;

    switch (D_8010AF40_tidal_toss) {
        case 0:
            func_8001F38C_main(0, 0, 0);
            WipeCreateIn(0xFF, 0x10);
            GMesCreate(4);
            HuAudFXPlay(0x42E);
            D_8010AA8C_tidal_toss = 45;
            D_8010AA90_tidal_toss = 900;
            D_8010AF40_tidal_toss++;
            D_8010ADE0_tidal_toss = 60;
        case 1:
            if (--D_8010ADE0_tidal_toss == -1) {
                HuAudSeqPlay(0x2F);
            }
            if (--D_8010AA8C_tidal_toss == -1) {
                func_8004AB0C_main(45);
            }
            if (GMesStatGet() == 0) {
                func_800E6F0C_minigame(2);
                D_8010AF40_tidal_toss++;
                GMesCreate(0x1A, (D_8010AA90_tidal_toss + 29) / 30, 160, 32);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            for (won = 0, i = 0; i < 4; i++) {
                if (i != D_8010AA70_tidal_toss) {
                    won += TT_PLAYER(i)->unk2F;
                }
            }
            if (won == 0) {
                D_8010AA94_tidal_toss = D_8010AA70_tidal_toss;
                D_8010AF40_tidal_toss = 3;
            }
            D_8010AA90_tidal_toss--;
            func_8003F578_main((D_8010AA90_tidal_toss + 29) / 30);
            if (D_8010AA90_tidal_toss == 0) {
                D_8010AF40_tidal_toss = 3;
            }
            break;
        case 3:
            if (D_8010AA94_tidal_toss == D_8010AA70_tidal_toss) {
                TT_PLAYER(D_8010AA94_tidal_toss)->unk2F = 1;
            } else {
                for (i = 0; i < 4; i++) {
                    if (i != D_8010AA70_tidal_toss) {
                        TT_PLAYER(i)->unk2F = 1;
                    }
                }
            }
            func_8003F5C0_main();
            GMesCreate(0xF);
            HuAudSeqFadeOut(120);
            D_8010AF40_tidal_toss++;
            D_8010AA8C_tidal_toss = 15;
            break;
        case 4:
            if (GMesStatGet() == 0) {
                if (--D_8010AA8C_tidal_toss == 0) {
                    if (D_8010AA94_tidal_toss == D_8010AA70_tidal_toss) {
                        GMesCreate(0x16, TT_PLAYER(D_8010AA94_tidal_toss)->unk2C);
                        HuAudSeqPlay(0x65);
                    } else {
                        for (i = 0, n = 0; i < 4; i++) {
                            if (i != D_8010AA70_tidal_toss) {
                                chr[n++] = TT_PLAYER(i)->unk2C;
                            }
                        }
                        GMesCreate(0x22, chr[0], chr[1], chr[2]);
                        HuAudSeqPlay(0x66);
                    }
                    D_8010AA8C_tidal_toss = 15;
                    D_8010AF40_tidal_toss++;
                    func_800E6F0C_minigame(4);
                }
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                if (--D_8010AA8C_tidal_toss == 0) {
                    D_8010AF40_tidal_toss++;
                }
            }
            break;
        case 6:
            if (D_8010AA8C_tidal_toss != 0) {
                if (--D_8010AA8C_tidal_toss == 0) {
                    D_8010AF40_tidal_toss++;
                }
            } else {
                func_800E6F0C_minigame(5);
                D_8010AA8C_tidal_toss = 16;
                WipeCreateOut(0, D_8010AA8E_tidal_toss[0]);
                HuAudSeqFadeOut(D_8010AA8E_tidal_toss[0]);
                func_8004AB0C_main(D_8010AA8E_tidal_toss[0]);
            }
            break;
        case 7:
            HuMemFree(D_8010AF3C_tidal_toss);
            func_8004A950_main();
            omOvlReturnEx(1);
            break;
    }
    for (sp = D_8010AF48_tidal_toss, i = 0; i < 8; i++, sp++) {
        if (sp->unk10 != 0) {
            sp->unk00 += sp->unk08;
            if (sp->unk00 >= 900.0) {
                sp->unk10 = 0;
                sp->unk00 = 0.0f;
            }
            if (sp->unk00 >= 160.0) {
                sp->unk08 = (1.15 - sp->unk10 * 0.15) * 20.0;
            }
        }
    }
    for (cl = D_8010AFE8_tidal_toss, i = 0; i < 3; i++, cl++) {
        cl->fx = cl->x + sindf(cl->unk14) * 8.0;
        cl->fy = cl->y + sindf(cl->unk18) * 6.0;
        cl->unk14 += cl->unk0C;
        if (cl->unk14 >= 360.0) {
            cl->unk14 -= 360.0;
        }
        cl->unk18 += cl->unk10;
        if (cl->unk18 >= 360.0) {
            cl->unk18 -= 360.0;
        }
        spr = HuSprGet(D_8010AEEC_tidal_toss[0], i);
        spr->unk_48 = cl->fx;
        spr->unk_4C = cl->fy;
        sx = cl->unk0C + sindf(cl->unk14 * 6.0) * 0.1;
        HuSprScaleSet(D_8010AEEC_tidal_toss[0], i, sx, cl->unk10 - sindf(cl->unk14 * 6.0) * 0.1);
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010AF40_tidal_toss = 6;
        D_8010AA8C_tidal_toss = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80106D24_tidal_toss);

/* Start a splash in the first free slot: its size by the distance d. */
void func_80108460_tidal_toss(f32 d) {
    TtSplash* sp;
    s32 i;

    for (sp = D_8010AF48_tidal_toss, i = 0; i < 8; i++, sp++) {
        if (sp->unk10 == 0) {
            sp->unk00 = 0.0f;
            if (d <= 150.0) {
                HuAudFXPlay(0x343);
                sp->unk10 = 1;
                sp->unk08 = 20.0f;
                sp->unk04 = 60.0f;
                sp->unk0C = 16.0f;
            } else if (d <= 250.0) {
                HuAudFXPlay(0x346);
                sp->unk10 = 2;
                sp->unk08 = 20.0f;
                sp->unk04 = 120.0f;
                sp->unk0C = 20.0f;
            } else {
                HuAudFXPlay(0x345);
                sp->unk10 = 3;
                sp->unk08 = 26.0f;
                sp->unk04 = 240.0f;
                sp->unk0C = 30.0f;
            }
            return;
        }
    }
}

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

/* Effect at (x, y, z) on the first of the player's models 9..11 that is shown. */
void func_80109584_tidal_toss(omObjData* obj, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (HmfModelData[obj->model[i]].unk18 & 4) {
            func_800E4C88_minigame(obj, i, x, y, z, 0.0f, 0.0f);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010961C_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010A11C_tidal_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_8010A490_tidal_toss);

void func_8010A7E4_tidal_toss(omObjData* obj, MgWork** work, TtPlayer** ep) {
    MgWork* w = obj->data;

    *work = w;
    *ep = w->unk158;
}

s32 func_8010A7F8_tidal_toss(void) {
    D_8010AAFC_tidal_toss = D_8010AAFC_tidal_toss * 0x41C64E6D + 0x3039;
    D_8010AAFC_tidal_toss += rand8();
    return D_8010AAFC_tidal_toss >> 16;
}

/* XZ distance */
f32 func_8010A850_tidal_toss(Vec* a, Vec* b) {
    return sqrtf((a->x - b->x) * (a->x - b->x) + (a->z - b->z) * (a->z - b->z));
}

/* atan2df in 0..360 */
f32 func_8010A8A4_tidal_toss(f32 x, f32 z) {
    f32 full = 360.0f;
    f32 a = atan2df(x, z);

    if (a < 0.0f) {
        a += full;
    } else if (a >= full) {
        a -= full;
    }
    return a;
}

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
