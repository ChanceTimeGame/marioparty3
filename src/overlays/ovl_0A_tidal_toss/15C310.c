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
    /* 0x00 */ f32 unk00; /* position */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C; /* last position */
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18; /* team: speed kept while airborne */
    /* 0x1C */ f32 unk1C; /* radius */
    /* 0x20 */ f32 unk20; /* boat: rock height */
    /* 0x24 */ s32 unk24; /* win motion file */
    /* 0x28 */ u16 unk28; /* last func_800E4A90_minigame flags */
    /* 0x2A */ u8 unk2A; /* boat: splashed */
    /* 0x2B */ u8 unk2B; /* player */
    /* 0x2C */ u8 unk2C; /* character */
    /* 0x2D */ u8 unk2D; /* team: 0 the solo player, 1 the three */
    /* 0x2E */ u8 unk2E; /* CPU difficulty */
    /* 0x2F */ u8 unk2F; /* won */
    /* 0x30 */ u8 unk30; /* CPU */
    /* 0x31 */ char unk31[1];
    /* 0x32 */ u16 unk32; /* CPU state */
    /* 0x34 */ u16 unk34; /* CPU: height to dive at */
    /* 0x36 */ u16 unk36; /* CPU: jumps left */
    /* 0x38 */ s16 unk38;
    /* 0x3A */ char unk3A[0xA];
    /* 0x44 */ f32 unk44; /* boat: bob phase */
    /* 0x48 */ char unk48[4];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ char unk50[0x14];
} TtPlayer; /* size 0x64 */

#define TT_PLAYER(i) ((TtPlayer*)((MgWork*)D_800EC598_minigame[i]->data)->unk158)

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]); /* matrix copy */
void func_8007DFE0_main(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
f32 fabsf(f32);
f64 fabs(f64);
f32 sqrtf(f32);
s32 fmod(f64 x, f64 y); /* retail calls it unprototyped: the result is read as an int */
u8 rand8(void);

extern s32 D_800A178C_main[][6];
s32 func_80017BB8_main(s16, s16);

extern s8 D_800CBB6E_main[];
extern s16 D_800CDA7C_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[];

// minigame
void func_800DDD94_minigame(omObjData* obj);
void func_800E19FC_minigame(MgWork* work, s32 state);
s32 func_800E5798_minigame(omObjData* obj, u16 motion);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
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
void func_80109180_tidal_toss(omObjData* obj);
void func_8010961C_tidal_toss(omObjData* obj);
u16 func_8010A11C_tidal_toss(omObjData* obj);
u16 func_8010A490_tidal_toss(omObjData* obj, f32 dist);
void func_8010A7E4_tidal_toss(omObjData* obj, MgWork** work, TtPlayer** ep);
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
extern u8 D_8010AAB0_tidal_toss[4][2]; /* [n][1]: the n-th player to spawn */
extern u8 D_8010AAB8_tidal_toss; /* players spawned */
extern u8 D_8010AAB9_tidal_toss; /* team players spawned */
extern Vec D_8010AABC_tidal_toss[4]; /* start positions: [0] the solo player, [1 + n] the team */
extern f32 D_8010AAEC_tidal_toss[4]; /* start headings */
extern s32 D_8010AA8C_tidal_toss; /* message / wipe timer */
extern s16 D_8010AA8E_tidal_toss[]; /* [0]: the low half of D_8010AA8C (big-endian), read as the wipe-out speed */
extern u16 D_8010AA90_tidal_toss; /* game timer, frames */
extern s32 D_8010AA94_tidal_toss; /* winner: the solo player, else -1 */
extern s16 D_8010ADE0_tidal_toss; /* frames to the music */
extern Gfx* D_8010AF3C_tidal_toss;
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

/* Local views of the main model structs (src/22EB0.c HmfObj, HmfPart, HmfFaceRec, HmfTexRef, HmfTex, HmfMat),
   MP3 offsets and names, every pointer a pointer. A prefix of each is enough: these are only read. */
typedef struct TtColVtx {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
} TtColVtx; /* size 0x6 */

typedef struct TtHmfTex {
    /* 0x00 */ char unk00[0x24];
    /* 0x24 */ u16 unk24; /* width */
    /* 0x26 */ u16 unk26; /* height */
} TtHmfTex;

typedef struct TtHmfTexRef {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ TtHmfTex* unk0C;
} TtHmfTexRef; /* size 0x10 */

typedef struct TtHmfMat {
    /* 0x00 */ u8 unk00[5];
    /* 0x05 */ u8 unk05[3]; /* colour of unlit faces */
    /* 0x08 */ u8 unk08[3];
} TtHmfMat; /* size 0xB */

typedef struct TtHmfFace {
    /* 0x00 */ u8 unk00; /* vertex count, 0x80 unlit */
    /* 0x01 */ s8 unk01[3];
    /* 0x04 */ s16 unk04[4]; /* vertices */
    /* 0x0C */ f32 unk0C[4]; /* s */
    /* 0x1C */ f32 unk1C[4]; /* t */
    /* 0x2C */ u8 unk2C[4]; /* materials of unlit vertices */
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32; /* texture or -1 */
} TtHmfFace; /* size 0x34 */

typedef struct TtHmfPart {
    /* 0x00 */ char unk00[0x22];
    /* 0x22 */ s16 unk22; /* face count */
    /* 0x24 */ char unk24[0x30];
    /* 0x54 */ TtHmfFace* unk54;
} TtHmfPart;

typedef struct TtHmfObj {
    /* 0x00 */ u8 unk00[0xE];
    /* 0x0E */ s16 unk0E; /* allocation tag */
    /* 0x10 */ s16 unk10[4];
    /* 0x18 */ s16 unk18; /* vertex count */
    /* 0x1A */ s16 unk1A[3];
    /* 0x20 */ char unk20[2];
    /* 0x22 */ s16 unk22;
    /* 0x24 */ char unk24[2];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ u8* unk2C;
    /* 0x30 */ u8* unk30;
    /* 0x34 */ u8* unk34;
    /* 0x38 */ void* unk38;
    /* 0x3C */ void* unk3C;
    /* 0x40 */ Vtx_t* unk40; /* vertices */
    /* 0x44 */ Vtx_t* unk44[3]; /* per-frame vertex buffers */
    /* 0x50 */ TtColVtx* unk50; /* positions */
    /* 0x54 */ u8* unk54; /* normals (3 bytes each) */
    /* 0x58 */ void* unk58;
    /* 0x5C */ s16* unk5C; /* position -> vertex */
    /* 0x60 */ TtHmfPart* unk60;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ char unk66[2];
    /* 0x68 */ void* unk68;
    /* 0x6C */ char unk6C[0x14];
    /* 0x80 */ void* unk80;
    /* 0x84 */ TtHmfTexRef* unk84;
    /* 0x88 */ TtHmfMat* unk88;
} TtHmfObj; /* MP3 HmfData */

/* The water's faces sorted by their lowest z (a list with sentinels at both ends) */
typedef struct TtFaceNode {
    /* 0x00 */ TtHmfFace* face;
    /* 0x04 */ f32 key;
    /* 0x08 */ struct TtFaceNode* prev;
    /* 0x0C */ struct TtFaceNode* next;
} TtFaceNode; /* size 0x10 */

/* One face of a vertex batch */
typedef struct TtBatchFace {
    /* 0x00 */ s16 n;
    /* 0x02 */ s16 v[4];
    /* 0x0A */ char unk0A[0xA];
} TtBatchFace; /* size 0x14 */

extern u8 D_800D2008_main; /* frame buffer index */
extern Mtx D_8010ADE8_tidal_toss[3];
extern TtFaceNode* D_8010AEA8_tidal_toss;
extern Vtx_t* D_8010AEAC_tidal_toss;
extern u8 D_8010AA9C_tidal_toss[8];
extern s32 D_8010AAA4_tidal_toss;
extern s32 D_8010AAA8_tidal_toss;
extern f32 D_8010AAAC_tidal_toss;
extern s8 HmfPauseF;
void func_80017CD0_main(f32 (*)[4], f32, f32, f32);
void func_80017D24_main(f32 (*)[4], f32, f32, f32);
void func_80018044_main(f32*, f32 (*)[4], f32 (*)[4]);

/* Draw hook of the water model. The first three calls build it: the faces sorted front to back, their
   vertices merged into one buffer, then one display list of gSPVertex batches (segment 1) and triangles.
   Every later call draws it with a scrolling two-tile texture and the vertices pushed by the splashes. */
#ifdef NON_MATCHING
void func_80106D24_tidal_toss(Gfx** gfxP, s32 arg1, s32 arg2) {
    f32 mf2[4][4];
    f32 mf[4][4];
    Vtx_t save;
    TtBatchFace batch[64];
    HmfModel* model;
    TtHmfObj* obj;
    TtHmfPart* part;
    TtFaceNode* nodes;
    TtFaceNode* node;
    TtFaceNode* p;
    TtHmfFace* face;
    TtHmfTexRef* tex;
    TtColVtx* pos;
    TtBatchFace* b;
    TtSplash* sp;
    HuSprite_Unk84_Unk00_Struct* frame;
    HuSprite_Unk84_Struct* spr;
    Vtx_t* vtx;
    Vtx_t* src;
    Vtx_t* dst;
    u8* col;
    Gfx* gfx;
    Gfx* dl;
    f32 min;
    f64 d;
    f32 fd;
    f32 x;
    f32 z;
    s16 idx;
    f64 diff;
    f64 adiff;
    f64 f;
    f64 c;
    s32 limit;
    s32 i;
    s32 j;
    s32 k2;
    u8 n;
    s16 lighting;
    s16 base;
    s16 count;
    s16 k;
    s16 w;
    s16 h;
    s16 s;
    s16 t;
    s16 vi;
    s16 top;
    s16 nb;
    s16 len;
    s32 flush;

    model = &HmfModelData[D_8010AF38_tidal_toss];
    obj = (TtHmfObj*) model->hmf;
    part = obj->unk60;
    if (D_8010AAA4_tidal_toss == 0) {
        switch (D_8010AAA8_tidal_toss) {
            case 0:
                nodes = HuMemAlloc((part->unk22 + 2) * sizeof(TtFaceNode));
                D_8010AEA8_tidal_toss = nodes;
                D_8010AEAC_tidal_toss = HuMemAlloc(obj->unk18 * 2 * sizeof(Vtx_t));
                memset(D_8010AEAC_tidal_toss, 0, obj->unk18 * 2 * sizeof(Vtx_t));
                D_8010AEA8_tidal_toss->key = -19980.0f;
                D_8010AEA8_tidal_toss->prev = NULL;
                D_8010AEA8_tidal_toss->next = &D_8010AEA8_tidal_toss[part->unk22 + 1];
                D_8010AEA8_tidal_toss[part->unk22 + 1].key = 19980.0f;
                D_8010AEA8_tidal_toss[part->unk22 + 1].prev = D_8010AEA8_tidal_toss;
                D_8010AEA8_tidal_toss[part->unk22 + 1].next = NULL;
                nodes++;
                for (i = 0; i < part->unk22; i++, nodes++) {
                    face = &part->unk54[i];
                    nodes->face = face;
                    n = face->unk00 & 0x7F;
                    min = 19980.0f;
                    for (j = 0; j < n; j++) {
                        if (obj->unk50[face->unk04[j]].z < min) {
                            min = obj->unk50[face->unk04[j]].z;
                        }
                    }
                    nodes->key = min;
                    for (p = D_8010AEA8_tidal_toss->next; p->key < nodes->key; p = p->next) {
                    }
                    p->prev->next = nodes;
                    nodes->prev = p->prev;
                    nodes->next = p;
                    p->prev = nodes;
                }
                base = 0;
                count = 0;
                limit = D_8010AA9C_tidal_toss[((u32) model->unk18 & 0x1C00) >> 10];
                node = D_8010AEA8_tidal_toss;
                for (i = 0; i < part->unk22; i++) {
                    node = node->next;
                    face = node->face;
                    if (face == NULL) {
                        continue;
                    }
                    n = face->unk00 & 0x7F;
                    if (face->unk00 < 3) {
                        continue;
                    }
                    if (face->unk32 >= 0) {
                        tex = &obj->unk84[face->unk32];
                    } else {
                        tex = (TtHmfTexRef*) -1;
                    }
                    if (limit < count - base) {
                        base = count;
                    }
                    if (tex != (TtHmfTexRef*) -1) {
                        w = tex->unk0C->unk24 << 5;
                        h = tex->unk0C->unk26 << 5;
                    } else {
                        w = h = 0;
                    }
                    lighting = face->unk00 & 0x80;
                    for (j = 0; j < n; j++) {
                        pos = &obj->unk50[face->unk04[j]];
                        idx = face->unk04[j];
                        if (lighting) {
                            col = obj->unk88[face->unk2C[j]].unk05;
                        } else {
                            col = &obj->unk54[idx * 3];
                        }
                        s = w * face->unk0C[j];
                        t = h * face->unk1C[j];
                        vtx = &D_8010AEAC_tidal_toss[count - 1];
                        for (k = count - 1; k >= base; k--, vtx--) {
                            if (vtx->ob[0] == pos->x && vtx->ob[1] == pos->y && vtx->ob[2] == pos->z
                                && (s8) vtx->cn[0] == (s8) col[0] && (s8) vtx->cn[1] == (s8) col[1]
                                && (s8) vtx->cn[2] == (s8) col[2] && vtx->tc[0] == s && vtx->tc[1] == t) {
                                break;
                            }
                        }
                        if (k <= base) {
                            vtx = &D_8010AEAC_tidal_toss[count];
                            vtx->ob[0] = pos->x;
                            vtx->ob[1] = pos->y;
                            vtx->ob[2] = pos->z;
                            vtx->cn[0] = col[0];
                            vtx->cn[1] = col[1];
                            vtx->cn[2] = col[2];
                            vtx->tc[0] = s;
                            vtx->tc[1] = t;
                            vtx->cn[3] = 255;
                            obj->unk5C[idx] = count;
                            count++;
                        } else {
                            obj->unk5C[idx] = k;
                        }
                    }
                }
                obj->unk18 = count;
                break;
            case 1:
                HuMemFree(obj->unk40);
                for (i = 0; i < 3; i++) {
                    HuMemFree(obj->unk44[i]);
                }
                obj->unk40 = HuMemAllocTag(obj->unk18 * sizeof(Vtx_t), obj->unk0E);
                bcopy(D_8010AEAC_tidal_toss, obj->unk40, obj->unk18 * sizeof(Vtx_t));
                for (i = 0; i < 3; i++) {
                    obj->unk44[i] = HuMemAllocTag(obj->unk18 * sizeof(Vtx_t), obj->unk0E);
                    bcopy(D_8010AEAC_tidal_toss, obj->unk44[i], obj->unk18 * sizeof(Vtx_t));
                }
                HuMemFree(D_8010AEAC_tidal_toss);
                break;
            case 2:
                gfx = dl = HuMemAlloc(640 * sizeof(Gfx));
                base = 0;
                nb = 0;
                limit = D_8010AA9C_tidal_toss[((u32) model->unk18 & 0x1C00) >> 10];
                top = 0;
                flush = 0;
                node = D_8010AEA8_tidal_toss;
                for (i = 0; i < part->unk22; i++) {
                    node = node->next;
                    face = node->face;
                    if (face == NULL) {
                        continue;
                    }
                    n = face->unk00 & 0x7F;
                    b = &batch[nb];
                    b->n = n;
                    for (j = 0; j < n; j++) {
                        vi = obj->unk5C[face->unk04[j]];
                        if (top < vi + 1) {
                            top = vi + 1;
                        }
                        if (limit < top - base) {
                            flush = 1;
                        }
                        b->v[j] = vi - base;
                    }
                    nb++;
                    if (flush != 0 || i == part->unk22 - 1) {
                        len = top - base;
                        if (len > 32) {
                            gSPVertex(gfx++, (Vtx*) 0x01000000 + base, 32, 0);
                            gSPVertex(gfx++, (Vtx*) 0x01000000 + (base + 32), len - 32, 32);
                        } else {
                            gSPVertex(gfx++, (Vtx*) 0x01000000 + base, len, 0);
                        }
                        for (j = 0; j < nb; j++) {
                            b = &batch[j];
                            if (b->n == 3) {
                                if (j + 1 < nb && b[1].n == 3) {
                                    gSP2Triangles(gfx++, b->v[0], b->v[1], b->v[2], 0, b[1].v[0], b[1].v[1], b[1].v[2], 0);
                                    j++;
                                } else {
                                    gSP1Triangle(gfx++, b->v[0], b->v[1], b->v[2], 0);
                                }
                            } else {
                                gSP2Triangles(gfx++, b->v[0], b->v[1], b->v[3], 0, b->v[3], b->v[1], b->v[2], 0);
                            }
                        }
                        flush = 0;
                        base = top;
                        nb = 0;
                    }
                }
                gSPEndDisplayList(gfx++);
                len = gfx - dl;
                D_8010AF3C_tidal_toss = HuMemAlloc(len * sizeof(Gfx));
                bcopy(dl, D_8010AF3C_tidal_toss, len * sizeof(Gfx));
                HuMemFree(dl);
                HuMemFree(D_8010AEA8_tidal_toss);
                D_8010AAA4_tidal_toss++;
                break;
        }
        D_8010AAA8_tidal_toss++;
        return;
    }
    gfx = *gfxP;
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPPipeSync(gfx++);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gfx++, 0xFFFFFFFF);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetBlendColor(gfx++, 0, 0, 0, 0);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    guMtxL2F(mf, &((HuCamMtxs*) arg1)->lookAtMtx);
    func_80017C10_main((Mtx*) mf, model->pos.x, model->pos.y, model->pos.z);
    func_80017D24_main(mf, model->rot.x, model->rot.y, model->rot.z);
    func_80017CD0_main(mf, model->scale.x, model->scale.y, model->scale.z);
    func_80018044_main(model->mtx, mf, mf2);
    guMtxF2L(mf2, &D_8010ADE8_tidal_toss[D_800D2008_main]);
    gSPMatrix(gfx++, osVirtualToPhysical(&D_8010ADE8_tidal_toss[D_800D2008_main]), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    frame = func_8010AA1C_tidal_toss(D_8010AF3A_tidal_toss, 0);
    spr = func_80055194_main(D_8010AF3A_tidal_toss);
    gDPLoadTLUT_pal16(gfx++, 0, spr->unk0C);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTextureBlock_4b(gfx++, frame->unk00, G_IM_FMT_CI, frame->unk04, frame->unk06, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadMultiBlock_4b(gfx++, frame->unk00, 0, 1, G_IM_FMT_CI, frame->unk04, frame->unk06, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    if (HmfPauseF == 0) {
        D_8010AAAC_tidal_toss += 1.0;
    }
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, (s32) (D_8010AAAC_tidal_toss * 1.5 + 7.25) & 0x1FF,
                   (frame->unk04 - 1) << G_TEXTURE_IMAGE_FRAC, (frame->unk06 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetTileSize(gfx++, 1, 16, (s32) D_8010AAAC_tidal_toss & 0x1FF,
                   (frame->unk04 - 1) << G_TEXTURE_IMAGE_FRAC, (frame->unk06 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
    gDPSetCombineLERP(gfx++, TEXEL0, TEXEL1, PRIMITIVE, TEXEL1, 0, 0, 0, SHADE, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED);
    gDPSetPrimColor(gfx++, 0, 0, 128, 128, 128, 176);
    src = obj->unk40;
    dst = obj->unk44[D_800D2008_main];
    for (i = 0; i < obj->unk18; i++, src++, dst++) {
        d = sqrtf((f64) (src->ob[0] * src->ob[0] + src->ob[2] * src->ob[2]));
        *dst = *src;
        dst->cn[0] = (s32) ((f32) src->cn[0] * 0.5);
        dst->cn[1] = (s32) ((f32) src->cn[1] * 0.5);
        dst->cn[2] = (s32) ((f32) src->cn[2] * 0.5);
        dst->cn[3] = 0x90;
        if (d < 140.0) {
            continue;
        }
        if (d > 710.0) {
            continue;
        }
        for (sp = D_8010AF48_tidal_toss, k2 = 0; k2 < 8; k2++, sp++) {
            if (sp->unk10 == 0) {
                continue;
            }
            save = *dst;
            diff = sp->unk00 - d;
            adiff = fabs(diff);
            fd = d;
            if (adiff >= 100.0) {
                dst->ob[1] = src->ob[1];
            } else if ((((diff < 34.0) & (diff >= 0.0)) && dst->ob[2] > 0.0)
                       || (((diff > -34.0) & (diff <= 0.0)) && dst->ob[2] <= 0.0)) {
                x = src->ob[0] / fd;
                z = src->ob[2] / fd;
                dst->ob[0] = x * sp->unk00;
                dst->ob[1] = src->ob[1] + sp->unk04;
                dst->ob[2] = z * sp->unk00;
                dst->cn[0] = src->cn[0];
                dst->cn[1] = src->cn[1];
                dst->cn[2] = src->cn[2];
                dst->cn[3] = 0xFF;
            } else {
                f = 1.0 - adiff / 100.0;
                f *= f;
                dst->ob[1] = src->ob[1] + sp->unk04 * f;
                c = f * 0.5 + 0.5;
                dst->cn[0] = (s32) ((f32) src->cn[0] * c);
                dst->cn[1] = (s32) ((f32) src->cn[1] * c);
                dst->cn[2] = (s32) ((f32) src->cn[2] * c);
                dst->cn[3] = (u32) (f * 112.0 + 144.0);
            }
            if (dst->ob[1] < save.ob[1]) {
                *dst = save;
            }
        }
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 1, osVirtualToPhysical(obj->unk44[D_800D2008_main]));
    gSPDisplayList(gfx++, D_8010AF3C_tidal_toss);
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    *gfxP = gfx;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80106D24_tidal_toss);
#endif

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

/* Player setup: the solo player (spawned first) in the boat, the team of three on the shore. */
void func_80108638_tidal_toss(omObjData* obj) {
    u8 player;
    s8 chr;
    u32 file0;
    s32 file1;
    s32 i;
    u16 attr;
    MgWork* work;
    TtPlayer* tp;

    player = D_8010AAB0_tidal_toss[D_8010AAB8_tidal_toss][1];
    chr = GwPlayer[player].chr;
    file0 = D_800A178C_main[chr][0];
    file1 = D_800A178C_main[chr][1];
    attr = 0x2D9;
    func_800E1BA8_minigame(obj, file0, file1, player, attr, attr);
    work = obj->data;
    work->unk50 &= ~1;
    work->unkEC = NULL;
    obj->trans.x = D_8010AABC_tidal_toss[D_8010AAB8_tidal_toss].x;
    obj->trans.y = D_8010AABC_tidal_toss[D_8010AAB8_tidal_toss].y;
    obj->trans.z = D_8010AABC_tidal_toss[D_8010AAB8_tidal_toss].z;
    work->unk3C = D_8010AAEC_tidal_toss[D_8010AAB8_tidal_toss];
    obj->scale.x = obj->scale.y = obj->scale.z = work->unkAC;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    work->unk158 = HuMemAllocTag(sizeof(TtPlayer), 0x7918);
    memset(work->unk158, 0, sizeof(TtPlayer));
    tp = work->unk158;
    tp->unk2B = player;
    tp->unk2D = GwPlayer[D_8010AAB8_tidal_toss].group;
    tp->unk2C = chr;
    tp->unk30 = GwPlayer[player].stat & 1;
    tp->unk2E = GwPlayer[player].cpu_difficulty;
    tp->unk2F = 0;
    tp->unk1C = 11.0f;
    tp->unk00 = obj->trans.x;
    tp->unk04 = obj->trans.y;
    tp->unk08 = obj->trans.z;
    if (tp->unk2D != 0) {
        obj->trans.x = D_8010AABC_tidal_toss[D_8010AAB9_tidal_toss + 1].x;
        obj->trans.y = D_8010AABC_tidal_toss[D_8010AAB9_tidal_toss + 1].y;
        obj->trans.z = D_8010AABC_tidal_toss[D_8010AAB9_tidal_toss + 1].z;
        work->unk3C = D_8010AAEC_tidal_toss[D_8010AAB9_tidal_toss + 1];
        func_800E149C_minigame(obj, 0, 2);
        func_800E149C_minigame(obj, 1, 1);
        func_800E149C_minigame(obj, 2, 1);
        work->unk50 |= 0x8000;
        obj->func = func_8010961C_tidal_toss;
        D_8010AAB9_tidal_toss++;
    } else {
        obj->trans.x = D_8010AABC_tidal_toss[0].x;
        obj->trans.y = D_8010AABC_tidal_toss[0].y;
        obj->trans.z = D_8010AABC_tidal_toss[0].z;
        work->unk3C = D_8010AAEC_tidal_toss[0];
        func_800E149C_minigame(obj, 0, 1);
        func_800E149C_minigame(obj, 1, 2);
        func_800E149C_minigame(obj, 2, 1);
        obj->model[9] = func_8000B108_main(0x2B0005, attr);
        Hu3DModelPosSet(obj->model[9], obj->trans.x, obj->trans.y, obj->trans.z + 20.0);
        D_8010AA70_tidal_toss = work->unk59;
        obj->func = func_80109180_tidal_toss;
    }
    attr = 0x2DD;
    if (tp->unk2D != 0) {
        for (i = 9; i < 12; i++) {
            obj->model[i] = func_8000B108_main(0x320003, attr);
            func_8001C92C_main(obj->model[i], 0.5f);
            Hu3DModelScaleSet(obj->model[i], 1.0f, 1.0f, 1.0f);
        }
    }
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(obj, 21, func_80017BB8_main(chr, 0x1F), 0, 19);
    if (tp->unk2D != 0) {
        func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
        func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 1), 1, 0);
        func_800E5A00_minigame(obj, 17, func_80017BB8_main(chr, 0xE), 0, 0);
        func_800E5A00_minigame(obj, 32, func_80017BB8_main(chr, 0x22), 0, 0);
        func_800E5A00_minigame(obj, 9, func_80017BB8_main(chr, 7), 1, 39);
        func_800E5A00_minigame(obj, 10, func_80017BB8_main(chr, 0x11), 1, 39);
        func_800E5978_minigame(obj, 33, func_80017BB8_main(chr, 0x23), 2, 0);
        func_800E5A00_minigame(obj, 34, func_80017BB8_main(chr, 0x24), 2, 0);
        tp->unk24 = file0 | 0x2F;
        func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
        func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x36), 1, 120);
    } else {
        func_800E5A00_minigame(obj, 8, func_80017BB8_main(chr, 6), 1, 29);
        func_800E5A00_minigame(obj, 18, func_80017BB8_main(chr, 0xF), 2, 0);
        switch (file0 >> 16) {
            case 2:
                tp->unk24 = file0 | 0x30;
                func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x30), 1, 120);
                func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x38), 1, 100);
                break;
            case 3:
                tp->unk24 = file0 | 0x30;
                func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x30), 1, 120);
                func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x38), 1, 100);
                break;
            case 7:
                tp->unk24 = file0 | 0x30;
                func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x30), 1, 120);
                func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x36), 1, 120);
                break;
            case 5:
                tp->unk24 = file0 | 0x2F;
                func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
                func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x38), 1, 100);
                break;
            case 6:
                tp->unk24 = file0 | 0x2F;
                func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
                func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x38), 1, 100);
                break;
            case 9:
                tp->unk24 = file0 | 0x2F;
                func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
                func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x38), 1, 100);
                break;
            default:
                tp->unk24 = file0 | 0x2F;
                func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
                func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x36), 1, 120);
                break;
        }
    }
    func_800E5690_minigame(obj, 0);
    D_8010AAB8_tidal_toss++;
}

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

#ifdef NON_MATCHING
/* masked 0, raw 1: retail tests flags & 0x20 on $v0 (the call result) instead of its copy in $s3. unk36 is u16 but retail converts with a signed trunc.w.d: the (s32) cast is needed */
/* The solo player in the boat: it bobs on the water and rocks when a ball lands. */
void func_80109180_tidal_toss(omObjData* obj) {
    MgWork* work;
    TtPlayer* tp;
    s32 flags;
    u8 pad;
    f32 y;

    work = obj->data;
    tp = work->unk158;
    pad = work->unk57;
    switch (D_8010AF40_tidal_toss) {
        case 0:
            tp->unk44 = 0.0f;
            tp->unk36 = (s32)((f32)func_8010A7F8_tidal_toss() * (1.0 / 65536.0) * 12.0);
            tp->unk38 = 0;
            break;
        case 2:
            if (tp->unk30 != 0) {
                D_800D20A1_main[pad] = 0;
                D_800CBB6E_main[pad] = 0;
                D_800D5558_main[pad] = 0;
                D_800CDA7C_main[pad] = 0;
                func_8010A11C_tidal_toss(obj);
            }
            break;
        case 3:
        case 4:
            D_800CBB6E_main[pad] = 0;
            D_800D20A1_main[pad] = -0x40;
            D_800D5558_main[pad] = 0;
            D_800CDA7C_main[pad] = 0;
            break;
        case 5:
            if (tp->unk2F == 1) {
                func_800E5690_minigame(obj, 0xD);
                func_80045ED0_main(tp->unk24);
                GwPlayer[work->unk59].bonusCoin += 10;
                tp->unk2F++;
            } else if (tp->unk2F == 0) {
                func_800E5690_minigame(obj, 0xE);
                tp->unk2F--;
            }
            break;
        case 6:
            if (work != NULL) {
                HuMemFree(work->unk158);
                obj->data = NULL;
                obj->func = NULL;
            }
            return;
        case 7:
            return;
    }
    flags = func_800E4A90_minigame(obj);
    tp->unk0C = obj->trans.x;
    tp->unk10 = obj->trans.y;
    tp->unk14 = obj->trans.z;
    if (flags & 0x20) {
        D_800D20A1_main[pad] = 0;
        D_800CBB6E_main[pad] = 0;
    }
    func_800DDD94_minigame(obj);
    func_8001C258_main(obj->model[1], 4, 4);
    if (flags & 0x200) {
        if ((work->unk50 & 0x80) && tp->unk2A == 0) {
            func_80108460_tidal_toss(tp->unk20);
            tp->unk2A++;
        }
        if (!(tp->unk28 & 0x200)) {
            tp->unk20 = obj->trans.y - 20.0;
            tp->unk2A = 0;
        }
    } else if ((tp->unk28 & 0x20) && !(flags & 0x20)) {
        func_80108460_tidal_toss(100.0f);
        tp->unk20 = 100.0f;
    }
    tp->unk44 += 4.0;
    if (tp->unk44 >= 360.0) {
        tp->unk44 -= 360.0;
    }
    if (tp->unk20 > 20.0 && tp->unk2A != 0) {
        y = 20.0 - tp->unk20 * 0.075;
        tp->unk20 *= 0.8;
    } else {
        y = 20.0 - sindf(tp->unk44) * 5.0;
    }
    Hu3DModelPosSet(obj->model[9], 0.0f, y, 0.0f);
    if (!(flags & 0x220)) {
        obj->trans.y = y;
    }
    obj->trans.x = obj->trans.z = 0.0f;
    tp->unk28 = flags;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0A_tidal_toss/15C310", func_80109180_tidal_toss);
#endif

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

/* A team player on the shore ring: dodge the waves, knocked into the pool by one. */
void func_8010961C_tidal_toss(omObjData* obj) {
    MgWork* work;
    TtPlayer* tp;
    u8 pad;
    s32 flags;
    f64 dist;
    f64 rad;
    s32 i;
    TtSplash* sp;
    f32 a;
    f32 h;
    omObjData* other;
    MgWork* ow;

    work = obj->data;
    tp = work->unk158;
    pad = work->unk57;
    flags = func_800E4A90_minigame(obj);
    tp->unk0C = obj->trans.x;
    tp->unk10 = obj->trans.y;
    tp->unk14 = obj->trans.z;
    dist = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
    switch (D_8010AF40_tidal_toss) {
        case 0:
            tp->unk2F = 1;
            tp->unk2A = 0;
            tp->unk44 = 0;
            tp->unk4C = (s32)((f32)func_8010A7F8_tidal_toss() * (1.0 / 65536.0) * 10.0);
            break;
        case 2:
            if (tp->unk30 != 0) {
                D_800D20A1_main[pad] = 0;
                D_800CBB6E_main[pad] = 0;
                D_800D5558_main[pad] = 0;
                D_800CDA7C_main[pad] = 0;
                func_8010A490_tidal_toss(obj, dist);
            }
            if (work->unkBE == 0) {
                for (sp = D_8010AF48_tidal_toss, i = 0; i < 8; i++, sp++) {
                    if (sp->unk10 != 0 && fabsf(sp->unk00 - dist) <= sp->unk08 * 0.75 && obj->trans.y < sp->unk04) {
                        a = func_8010A8A4_tidal_toss(obj->trans.x, obj->trans.z);
                        if (a > 180.0) {
                            a -= 360.0f;
                        }
                        h = work->unk3C;
                        if (h > 180.0) {
                            h -= 360.0f;
                        }
                        if (fabs(h - a) < 90.0) {
                            func_800E5690_minigame(obj, 0xA);
                            work->unk3C = a;
                            work->unk40 = sp->unk0C;
                            flags |= 0x800;
                        } else {
                            func_800E5690_minigame(obj, 9);
                            work->unk3C = a + 180.0;
                            work->unk40 = -sp->unk0C;
                            flags |= 0x400;
                        }
                        work->unk38 = -0.735f;
                        work->unkBE = 94;
                        func_800E19FC_minigame(work, 8);
                        switch (sp->unk10) {
                            case 1:
                                omVibrate(work->unk59, 2, 3, 10);
                                break;
                            case 2:
                                omVibrate(work->unk59, 10, 0, 10);
                                break;
                            case 3:
                                omVibrate(work->unk59, 2, 2, 20);
                                break;
                        }
                    }
                }
            }
            if (obj->trans.y <= 0.0) {
                obj->trans.x += obj->trans.x * 0.5 / dist;
                obj->trans.z += obj->trans.z * 0.5 / dist;
            }
            break;
        case 3:
            if (work->unkBE != 0) {
                work->unkBE = 1;
            }
        case 4:
            D_800CBB6E_main[pad] = 0;
            D_800D20A1_main[pad] = -0x30;
            D_800D5558_main[pad] = 0;
            D_800CDA7C_main[pad] = 0;
            break;
        case 5:
            D_800CBB6E_main[pad] = 0;
            D_800D20A1_main[pad] = -0x30;
            D_800D5558_main[pad] = 0;
            D_800CDA7C_main[pad] = 0;
            a = fmod(work->unk3C, 360.0);
            if ((a > 8.0 && a < 352.0) || (a < -8.0 && a > -352.0)) {
                break;
            }
            if (tp->unk2F == 1) {
                if (tp->unk2A == 0) {
                    func_800E5798_minigame(obj, 0xD);
                    func_80045ED0_main(tp->unk24);
                }
                GwPlayer[work->unk59].bonusCoin += 10;
                tp->unk2F++;
            } else if (tp->unk2F == 0) {
                tp->unk2F--;
            }
            break;
        case 6:
            if (work != NULL) {
                HuMemFree(work->unk158);
                obj->data = NULL;
                obj->func = NULL;
            }
            return;
        case 7:
            return;
    }
    D_800CBB6E_main[pad] = (f32)D_800CBB6E_main[pad] * 0.325;
    D_800D20A1_main[pad] = (f32)D_800D20A1_main[pad] * 0.325;
    func_800DDD94_minigame(obj);
    if (dist <= 190.0) {
        obj->trans.x = obj->trans.x / dist * 190.0;
        obj->trans.z = obj->trans.z / dist * 190.0;
    }
    if ((flags & 0xC00) && tp->unk2A == 0) {
        if (690.0 - work->unk48 <= dist && D_8010AF40_tidal_toss == 2) {
            if (flags & 0x400) {
                work->unk40 = -24.0f;
            } else {
                work->unk40 = 24.0f;
            }
            func_800E149C_minigame(obj, 0, 1);
            func_800E149C_minigame(obj, 2, 2);
            work->unk38 = -1.0289999f;
            tp->unk2A = 1;
            tp->unk2F = 0;
            func_8004AC5C_main(0x344, work->unk59);
            func_8004AC5C_main(tp->unk2C + 0x287, work->unk59);
        }
    } else {
        if (work->unk40 > 4.0) {
            work->unk40 = 4.0f;
        }
        if (flags & 0x20) {
            if (!(tp->unk28 & 0x20)) {
                tp->unk18 = work->unk40;
            }
            work->unk40 = tp->unk18;
        } else if (tp->unk28 & 0x20) {
            if (dist <= 590.0) {
                func_80109584_tidal_toss(obj, obj->trans.x, 60.0f, obj->trans.z + 50.0);
            }
        }
    }
    if (tp->unk2A != 0) {
        if (work->unk40 > 0.0f) {
            work->unk40 = 20.0f;
        } else {
            work->unk40 = -20.0f;
        }
    } else if (690.0 - work->unk48 <= dist) {
        obj->trans.x = (690.0 - work->unk48) * (obj->trans.x / dist);
        obj->trans.z = (690.0 - work->unk48) * (obj->trans.z / dist);
    }
    for (i = 0; i < 4; i++) {
        other = D_800EC598_minigame[i];
        if (obj == other) {
            continue;
        }
        ow = other->data;
        if (((TtPlayer*)ow->unk158)->unk2D == 0) {
            continue;
        }
        if (fabs(obj->trans.y - other->trans.y) > 30.0) {
            continue;
        }
        dist = func_8010A850_tidal_toss(&obj->trans, &other->trans);
        rad = work->unk48 + ow->unk48;
        if (rad < dist) {
            continue;
        }
        if (work->unk40 <= ow->unk40) {
            a = func_8010A8A4_tidal_toss(other->trans.x - obj->trans.x, other->trans.z - obj->trans.z);
            other->trans.x = obj->trans.x + rad * sindf(a);
            other->trans.z = obj->trans.z + rad * cosdf(a);
        } else {
            a = func_8010A8A4_tidal_toss(obj->trans.x - other->trans.x, obj->trans.z - other->trans.z);
            obj->trans.x = other->trans.x + rad * sindf(a);
            obj->trans.z = other->trans.z + rad * cosdf(a);
        }
    }
    tp->unk28 = flags;
    for (i = 9; i < 12; i++) {
        s16 m = obj->model[i];

        if (D_800CCF58_main[HmfModelData[m].unk02].unk02 <= HmfModelData[m].unk40) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
}

/* CPU of the solo player: jump (A) and dive (Z) on a timer. Returns an unset u16 (retail; the caller ignores it). */
u16 func_8010A11C_tidal_toss(omObjData* obj) {
    MgWork* work;
    TtPlayer* tp;
    s16 pad;
    s32 flags;
    u16 btn;

    func_8010A7E4_tidal_toss(obj, &work, &tp);
    pad = (s8)work->unk57;
    flags = func_800E4A90_minigame(obj);
    switch (tp->unk32) {
        case 1:
            if (tp->unk2E == 0) {
                D_800CDA7C_main[pad] |= 0x8000;
            }
            if (!(flags & 0x20)) {
                D_800D5558_main[pad] |= 0x8000;
            } else {
                tp->unk32++;
            }
            break;
        case 2:
            if (tp->unk2E == 0) {
                D_800CDA7C_main[pad] |= 0x8000;
            }
            if (!(flags & 0x20)) {
                tp->unk32 = 0;
            }
            break;
        case 3:
            if (flags & 2) {
                D_800D5558_main[pad] |= 0x8000;
                tp->unk32++;
            }
            break;
        case 4:
            D_800CDA7C_main[pad] |= 0x8000;
            if ((f32)tp->unk34 <= obj->trans.y - 20.0) {
                D_800D5558_main[pad] |= 0x2000;
                tp->unk32++;
            }
            break;
        case 5:
            if (flags & 2) {
                tp->unk32 = 0;
            }
            break;
    }
    if (tp->unk32 == 0) {
        if (func_8010A7F8_tidal_toss() % (6 - tp->unk2E) == 0) {
            tp->unk38 = 5;
            if (func_8010A7F8_tidal_toss() % (tp->unk2E + 3) == 0 || tp->unk36 == 0) {
                tp->unk32 = 3;
                tp->unk34 = (s32)((f32)func_8010A7F8_tidal_toss() * (1.0 / 65536.0) * 10.0) * 10 + 170;
                tp->unk36 = (s32)((f32)func_8010A7F8_tidal_toss() * (1.0 / 65536.0) * 8.0) + 8;
            } else {
                tp->unk32 = 1;
                tp->unk34 = 400;
                tp->unk36--;
            }
        }
    }
    return btn;
}

/* CPU of a team player: jump over a wave that is about to reach it, and stay near the shore. Returns an unset u16 (retail; the caller ignores it). */
u16 func_8010A490_tidal_toss(omObjData* obj, f32 dist) {
    MgWork* work;
    TtPlayer* tp;
    s16 pad;
    s32 flags;
    TtSplash* sp;
    s32 i;
    f64 d;
    u16 btn;

    func_8010A7E4_tidal_toss(obj, &work, &tp);
    pad = (s8)work->unk57;
    flags = func_800E4A90_minigame(obj);
    for (sp = D_8010AF48_tidal_toss, i = 0; i < 8; i++, sp++) {
        if (sp->unk10 == 0) {
            continue;
        }
        d = sp->unk00 - dist;
        if (!(fabsf(d) <= (f32)(sp->unk08 + ((7.25 - (f32)sp->unk10) + (f32)tp->unk2E * 0.25) * 20.0))) {
            continue;
        }
        if (!(d <= 0.0)) {
            continue;
        }
        if ((s32)((f32)func_8010A7F8_tidal_toss() * (1.0 / 65536.0) * 100.0) >= tp->unk2E * 10 + 45) {
            continue;
        }
        D_800D5558_main[pad] |= 0x8000;
        switch (tp->unk2E) {
            case 0:
            case 1:
                tp->unk32 = 10;
                break;
            case 2:
                if (sp->unk10 == 1) {
                    tp->unk32 = 0;
                } else {
                    tp->unk32 = 10;
                }
                break;
            case 3:
                if (sp->unk10 == 3) {
                    tp->unk32 = 10;
                } else {
                    tp->unk32 = 0;
                }
                break;
        }
        break;
    }
    if (tp->unk32 != 0) {
        tp->unk32--;
        D_800CDA7C_main[pad] |= 0x8000;
    }
    if (dist > 240.0 && !(flags & 0x20)) {
        D_800CBB6E_main[pad] = (tp->unk2E * 4.0 + 53.0) * -obj->trans.x / dist;
        D_800D20A1_main[pad] = (tp->unk2E * 4.0 + 53.0) * obj->trans.z / dist;
    }
    return btn;
}

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

u8 D_8010AA70_tidal_toss = 0;
s16 D_8010AA74_tidal_toss[3][2] = { { 55, 30 }, { 198, 38 }, { 294, 24 } }; /* cloud positions */
f32 D_8010AA80_tidal_toss[3] = { 1.0f, 0.8f, 1.2f }; /* cloud scales */
s32 D_8010AA8C_tidal_toss = 0; /* D_8010AA8E (undefined_syms.txt) is its low half */
u16 D_8010AA90_tidal_toss = 0;
s32 D_8010AA94_tidal_toss = -1;
s16 D_8010AA98_tidal_toss[2] = { 180, 0 }; /* unused */
u8 D_8010AA9C_tidal_toss[8] = { 0x1C, 0x1C, 0x3C, 0x3C, 0x1C, 0x1C, 0x1C, 0x3C }; /* func_80106D24 */
s32 D_8010AAA4_tidal_toss = 0; /* func_80106D24: mesh built */
s32 D_8010AAA8_tidal_toss = 0; /* func_80106D24: build step */
f32 D_8010AAAC_tidal_toss = 0.0f; /* func_80106D24 */
u8 D_8010AAB0_tidal_toss[4][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } }; /* [n][1]: the n-th player to spawn */
u8 D_8010AAB8_tidal_toss = 0;
u8 D_8010AAB9_tidal_toss = 0;
Vec D_8010AABC_tidal_toss[4] = {
    { 0.0f, 20.0f, -20.0f },
    { -240.0f, 0.0f, 0.0f },
    { 240.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 240.0f },
};
f32 D_8010AAEC_tidal_toss[4] = { 0.0f, 90.0f, -90.0f, 180.0f };
u32 D_8010AAFC_tidal_toss = 0x41C64E6D;
