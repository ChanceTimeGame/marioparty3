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
#include "input.h"
#include "variables.h"
#include "game/hmflight.h"


typedef func_800E1BA8_minigame_ObjData MgWork;
typedef f32 Matrix4f[4][4];
typedef struct FpPlayer FpPlayer;





/* A textured quad strip drawn with its own display list (D_8010F32C_fowl_play[D_8010F350_fowl_play]). */
typedef struct PgBoard {
    /* 0x00 */ Gfx* gfx;
    /* 0x04 */ Vtx* vtx; /* 2 per strip row */
    /* 0x08 */ HuSprite_Unk84_Struct* spr; /* NULL = free */
    /* 0x0C */ struct PgBoard* prev; /* depth-sorted draw list */
    /* 0x10 */ struct PgBoard* next;
    /* 0x14 */ void (*func)(struct PgBoard*); /* per-frame hook */
    /* 0x18 */ u8 rows; /* vertex pairs */
    /* 0x19 */ u8 rowH; /* texels per row */
    /* 0x1A */ u8 unk1A; /* facing: 1 X, 2 Y, 7 camera, 4 none */
    /* 0x1B */ u8 unk1B; /* S mask */
    /* 0x1C */ u8 unk1C; /* T mask */
    /* 0x1D */ u8 r;
    /* 0x1E */ u8 g;
    /* 0x1F */ u8 b;
    /* 0x20 */ u16 a;
    /* 0x22 */ u16 cmds; /* display list length */
    /* 0x24 */ s16 frame;
    /* 0x26 */ char unk26[2];
    /* 0x28 */ u32 flags;
    /* 0x2C */ f32 timer;
    /* 0x30 */ f32 speed;
    /* 0x34 */ Vec ofs;
    /* 0x40 */ Vec pos;
    /* 0x4C */ Vec scale;
    /* 0x58 */ Vec rot;
    /* 0x64 */ f32 depth; /* view z */
} PgBoard; /* size 0x68 */

/* MgWork::unk158 of a player. */




s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]); /* matrix copy */
void func_8007DFE0_main(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
void func_80016B00_main(s16 model, s16 frame, const char* name, Matrix4f mtx);
void func_80088800_main(Matrix4f mf, f32 x, f32 y, f32 z); /* guTranslateF */
void func_80017CD0_main(Matrix4f, f32, f32, f32);
void func_80017D24_main(Matrix4f, f32, f32, f32);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
f32 fabsf(f32);
f32 sqrtf(f32);
u8 rand8(void);
extern s32 D_800A178C_main[][6];
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
void func_800E3584_minigame(s16 mdl);
void func_800E12EC_minigame(omObjData* obj, f32 arg1);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1334_minigame(omObjData* obj, f32 arg1);
void func_800E1340_minigame(omObjData* obj, f32 arg1);
void func_8001EF6C_main(s16, s16, const char*);
s32 func_800E4A90_minigame(omObjData* obj);
void func_800E5798_minigame(omObjData* obj, s32 arg1);
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
extern s32 D_800EBEB0_minigame[];
extern HuSprite_Unk84_Struct* D_800C9530_main[];

void func_801064A8_fowl_play(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out);
void func_80106528_fowl_play(f32 (*src)[4], f32 (*dst)[4]);
void func_80106718_fowl_play(Vec* pos, Vec* out);
void func_80106824_fowl_play(f32 x, f32 y, f32 z, f32* out);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
void func_801068F0_fowl_play(void);
void func_80108020_fowl_play(omObjData* obj, u32 file0, s32 file1, s32 player, u16 attr);
void func_8010B1A0_fowl_play(s16 model, const char* name, s16 frame, Vec* out);
void func_8010B41C_fowl_play(u16 n);
s16 func_8010B8D4_fowl_play(PgBoard* b);
s16 func_8010C1F4_fowl_play(s16 tex, u32 flags);
s32 func_8010A9A0_fowl_play(void);
f32 func_8010AA64_fowl_play(Vec* a, Vec* b);
void func_8010CE04_fowl_play(s16 id, s16 frame);
void func_8010D07C_fowl_play(s16 id, u32 flags);
void func_8010D0C0_fowl_play(s16 id, u32 flags);
void func_8010D2F0_fowl_play(s16 id);
void func_8010DC24_fowl_play(Gfx** gfx, s32 arg1, s32 arg2);
void func_8010E704_fowl_play(void);
void func_8010CE84_fowl_play(s16 id, f32 x, f32 y, f32 z);
void func_8010D148_fowl_play(s16 id, s8 arg1);
void func_8010D2A4_fowl_play(s16 id, s8 r, s8 g, s8 b, u16 a);
s16 func_8010B30C_fowl_play(s16 tex, s16 n);
HuSprite_Unk84_Unk00_Struct* func_8010B3D4_fowl_play(s16 tex, s16 frame);

extern f32 D_8010F2A8_fowl_play[4][4]; /* world to view (D_8010DD88 is its [3][2]) */
extern f32 D_8010F2E0_fowl_play; /* D_8010DD50[3][2] */
extern f32 D_8010F2E8_fowl_play[4][4]; /* view to world */
extern f32 D_8010F328_fowl_play; /* tan(fov / 2) */
extern PgBoard* D_8010F32C_fowl_play;
extern s32 D_8010F350_fowl_play; /* billboard count */
extern void* D_8010F330_fowl_play[6]; /* per-frame buffers */
extern u8* D_8010F348_fowl_play; /* this frame's buffer */
extern s32 D_8010F34C_fowl_play; /* its size */
extern s32 D_8010EB64_fowl_play; /* buffer index */
extern s32 D_8010E8CC_fowl_play[4]; /* texel shift by size */
extern s16 D_8010E8DC_fowl_play[]; /* LoadBlock row limits by line width */
extern s16 D_8010EA14_fowl_play[];
extern s16 D_8010EB4C_fowl_play[4]; /* colour dither by flags >> 4 */
extern s16 D_8010EB54_fowl_play[4]; /* texture filter by flags >> 2 */
extern s16 D_8010EB5C_fowl_play[4]; /* alpha compare by flags >> 22 */
void func_8008A120_main(Matrix4f m, f32 a);
void func_80018544_main(Matrix4f src, Matrix4f dst);
void func_8010B564_fowl_play(Gfx** gfx, HuSprite_Unk84_Unk00_Struct* cel, u8 fmt, u8 siz, u16 rows, u16 uls,
                                  u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt, s32 mode);
extern PgBoard D_8010F360_fowl_play; /* opaque draw list head */
extern PgBoard D_8010F3C8_fowl_play; /* translucent draw list head */
extern s8 HmfPauseF;
void func_80079480_main(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp,
                        f32 zUp); /* guLookAtF */
void func_8010AAB8_fowl_play(Vec* dir, f32* angles);
void func_8010D81C_fowl_play(void);
void func_8010E544_fowl_play(void);
Gfx* func_8010DE4C_fowl_play(Gfx* g, PgBoard* b, f32 (*view)[4], Vec* rot);
void func_8010D970_fowl_play(HuCamera* cam, f32 (*view)[4]);
void func_800341D0_main(Gfx** gfx, s32 timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult,
                        s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                        s32 shiftt);
void func_80034998_main(Gfx** gfx, s32 timg, s32 fmt, u32 width, s32 height, s32 uls, s32 ult, s32 lrs,
                        s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
extern u32 D_8010E8C8_fowl_play; /* random seed */

typedef struct FpCam {
    /* 0x00 */ u8 idx; /* camera */
    /* 0x01 */ u8 timer;
    /* 0x04 */ f32 zoom;
    /* 0x08 */ f32 speed; /* turn speed */
    /* 0x0C */ Vec center;
    /* 0x18 */ Vec rot;
    /* 0x24 */ omObjData* target; /* followed player */
} FpCam; /* size 0x28 */

struct FpPlayer {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec prev; /* position at the start of the frame */
    /* 0x18 */ s16 unk18; /* last func_800E4A90_minigame result */
    /* 0x1A */ char unk1A[2];
    /* 0x1C */ s32 file; /* character model file | 0x9A */
    /* 0x20 */ u8 player;
    /* 0x21 */ u8 idx; /* camera / side */
    /* 0x22 */ u8 chr;
    /* 0x23 */ u8 difficulty;
    /* 0x24 */ u8 unk24; /* won */
    /* 0x25 */ u8 cpu;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ char unk28[4];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ char unk38[4];
    /* 0x3C */ s16 unk3C; /* holding the chick */
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ char unk40[0xC];
}; /* size 0x4C */

/* One feather puff (FpChick::feathers). */
typedef struct FpFeather {
    /* 0x00 */ s8 board; /* billboard */
    /* 0x01 */ u8 unk01;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ Vec vel;
    /* 0x10 */ f32 unk10;
} FpFeather; /* size 0x14 */

/* MgWork::unk158 of the chick. */
typedef struct FpChick {
    /* 0x00 */ u8 state;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ char unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ char unk08[4];
    /* 0x0C */ f32 speed;
    /* 0x10 */ f32 angle;
    /* 0x14 */ f32 target; /* wanted angle */
    /* 0x18 */ char unk18[0xC];
    /* 0x24 */ Vec vel;
    /* 0x30 */ char unk30[4];
    union {
        /* 0x34 */ s8 boards[8]; /* billboards; retail writes 8, so [4] and [5] are feathers[0]'s board and unk01 */
        struct {
            /* 0x34 */ s8 unk34[4];
            /* 0x38 */ FpFeather feathers[32];
        } f;
    } u;
} FpChick; /* size 0x2B8 */

typedef struct FpU8x8 {
    u8 v[8];
} FpU8x8;

#define FP_PLAYER(i) ((FpPlayer*)((MgWork*)D_800EC598_minigame[i]->data)->unk158)

void func_80106BD0_fowl_play(omObjData* obj);
void func_80055588_main(s16 group, s16 member, f32 arg2, f32 arg3);
void func_800555B8_main(s16 group, s16 member, u16 arg2, u16 arg3);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E1404_minigame(omObjData* obj, f32 arg1, f32 arg2);
void func_800E6F0C_minigame(s8 arg0);
s16 func_8010B2C4_fowl_play(s32 id);
extern s16 D_8010F230_fowl_play[2]; /* sprite files */
extern s16 D_8010F240_fowl_play[2]; /* sprite groups */
extern s16 D_8010F200_fowl_play; /* ambience sound */
extern s16 D_8010F202_fowl_play; /* its fade timer */
extern s16 D_8010F29E_fowl_play; /* time left, frames */
f32 func_8010AB40_fowl_play(Vec* v);
f32 func_8010AC04_fowl_play(Vec* p, Vec* a, Vec* d);
f32 func_8010AC88_fowl_play(Vec* p, Vec* a, Vec* b, Vec* out);
f32 func_8010AE10_fowl_play(Vec* p1, Vec* d1, Vec* p2, Vec* d2);
f32 func_8010AA64_fowl_play(Vec* a, Vec* b);
extern s32 D_8010E7A4_fowl_play; /* step timer */
extern Vec D_8010E7B4_fowl_play[8][2]; /* pen walls: segment ends */
extern u8 D_8010E87C_fowl_play; /* next player slot */
extern Vec D_8010E884_fowl_play[]; /* start positions */
extern f32 D_8010E8B4_fowl_play[]; /* start facings */
void func_80108298_fowl_play(omObjData* obj);
void func_801094A4_fowl_play(omObjData* obj);
void func_80109844_fowl_play(omObjData* obj);
void func_8010CE44_fowl_play(s16 id, f32 speed);
void func_8010CEE4_fowl_play(s16 id, f32 z);
void func_8010CFDC_fowl_play(s16 id, f32 x, f32 y, f32 z);
void func_8010D02C_fowl_play(s16 id, f32 x, f32 y, f32 z);
extern s16 D_8010F234_fowl_play; /* feather sprite file */
extern s16 D_8010F238_fowl_play; /* shadow sprite file */
extern omObjData* D_8010F290_fowl_play[1]; /* the chick */
void func_80108B08_fowl_play(omObjData* obj);
u8 func_8010724C_fowl_play(Vec* pos, Vec* prev, f32 r);
u8 func_8010A738_fowl_play(omObjData* obj, u8 hit);
void func_8001EED8_main(s16 arg0, s16 arg1, s16 arg2); /* hmfman.c defines (s16, u8, s8) */
void func_800DDD94_minigame(omObjData* obj);
extern const FpU8x8 D_8010ED88_fowl_play; /* motion slots by character */
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
extern s32 D_8010E7AC_fowl_play; /* winner, -1 none */
extern s16 D_8010E7B2_fowl_play; /* frames since the wipe ended */

void func_80107A4C_fowl_play(omObjData* obj);
void func_80106960_fowl_play(omObjData* obj);
void func_80105BEC_fowl_play(omObjData* obj);
void func_80105E4C_fowl_play(omObjData* obj);
void func_801079B0_fowl_play(void);
f32 func_8010A9EC_fowl_play(f32 x, f32 z);
void func_80109424_fowl_play(void);
void func_80109410_fowl_play(omObjData* obj, MgWork** work, FpPlayer** ep);
s32 func_8000B710_main(s32 arg0);
f64 fabs(f64);
extern D_80111B50_vine_with_me_Struct D_8010F208_fowl_play;
extern s16 D_8010F2A0_fowl_play;
extern omObjData* D_8010F294_fowl_play[2];
extern s16 D_8010F29C_fowl_play;

void func_801059A0_fowl_play(void) {
    omObjData* obj;

    Hu3DAnimInit(1);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    omInitObjMan(0x14, 0);
    func_8004A208_main();
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, 0xA0);
    obj->work[0] = 2;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 45.0f, 80.0f, 8000.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(1, 45.0f, 80.0f, 8000.0f);
    func_800E1804_minigame();
    func_80105BEC_fowl_play(obj);
    func_8010B41C_fowl_play(0x80);
    func_801068F0_fowl_play();
    memset(&D_8010F208_fowl_play, 0, 0x28);
    D_8010F208_fowl_play.unk01 = 4;
    func_800E5EA0_minigame(&D_8010F208_fowl_play);
    func_801079B0_fowl_play();
    D_8010F2A0_fowl_play = 0;
    func_80109424_fowl_play();
    func_8001F38C_main(0, 0, 0);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105BEC_fowl_play(omObjData* obj) {
    HuCamera* cam;
    omObjData* o;
    FpCam* c;
    f32 s;
    s32 i;

    CZoom = 1000.0f;
    CRot.x = -15.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 160.0f;
    Center.z = 0.0f;
    omOutView(obj);
    cam = gCameraList;
    s = sindf(cam->fov[0] / 2.0);
    D_8010F328_fowl_play = s / cosdf(cam->fov[0] / 2.0);
    guMtxL2F(D_8010F2A8_fowl_play, &cam->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010F2E8_fowl_play, &cam->mtxs[0].lookAtMtx);
    func_80106528_fowl_play(D_8010F2E8_fowl_play, D_8010F2E8_fowl_play);
    for (i = 0; i < 2; i++) {
        o = omAddObj(6, 1, 0, -1, func_80105E4C_fowl_play);
        D_8010F294_fowl_play[i] = o;
        c = o->data = HuMemAllocTag(sizeof(FpCam), 0x7918);
        memset(c, 0, sizeof(FpCam));
        c->idx = i;
        c->speed = 0.0f;
        c->timer = 2;
        c->center.x = CenterM[i].x = Center.x;
        c->center.y = CenterM[i].y = Center.y;
        c->center.z = CenterM[i].z = Center.z;
        c->rot.x = CRotM[i].x = CRot.x;
        c->rot.y = CRotM[i].y = 90.0 - i * 180.0;
        c->rot.z = CRotM[i].z = CRot.z;
        CZoomM[i] = CZoom;
        c->zoom = CZoom;
    }
}

void func_80105E4C_fowl_play(omObjData* obj) {
    u8 unused[0x50];
    MgWork* work;
    FpPlayer* pl;
    FpCam* c;
    HuCamera* cam;
    f32 face;
    f32 d;
    u8 idx;

    if (D_8010F29C_fowl_play >= 8) {
        if (obj->data != NULL) {
            HuMemFree(obj->data);
            obj->data = NULL;
        }
        return;
    }
    c = obj->data;
    if (c->target == NULL) {
        return;
    }
    func_80109410_fowl_play(c->target, &work, &pl);
    face = work->unk3C;
    idx = c->idx;
    cam = &gCameraList[idx];
    if (pl->unk24 != 0) {
        c->speed = 0.25f;
        c->rot.y = face;
    } else if (work->unk40 >= 0.1) {
        if (c->speed < 20.0) {
            c->speed += 0.25;
        }
        c->rot.y = func_8010A9EC_fowl_play(cam->pos.x - c->target->trans.x, cam->pos.z - c->target->trans.z);
        c->timer = 5;
    } else if (--c->timer == 0) {
        c->speed = 0.25f;
        c->rot.y = face + 180.0;
    }
    while (c->rot.y < 0.0) {
        c->rot.y += 360.0;
    }
    while (c->rot.y > 360.0) {
        c->rot.y -= 360.0;
    }
    CZoomM[idx] = c->zoom;
    CRotM[idx].x = c->rot.x;
    d = CRotM[idx].y - c->rot.y;
    while (d < -180.0) {
        d += 360.0;
    }
    while (d > 180.0) {
        d -= 360.0;
    }
    if (pl->unk24 != 0) {
        if (fabs(d) < 5.0) {
            c->speed = 0.5f;
        } else {
            c->speed = fabs(d) * 0.1;
        }
    } else if (work->unk40 <= 0.1) {
        if (fabs(d) < 5.0) {
            c->speed = 0.25f;
        } else {
            c->speed = fabs(d) * 0.05;
        }
    }
    if (c->speed < d) {
        CRotM[idx].y -= c->speed;
    } else if (d < -c->speed) {
        CRotM[idx].y += c->speed;
    } else {
        CRotM[idx].y = c->rot.y;
    }
    while (CRotM[idx].y < 0.0) {
        CRotM[idx].y += 360.0;
    }
    while (CRotM[idx].y > 360.0) {
        CRotM[idx].y -= 360.0;
    }
    c->center.x = c->target->trans.x - sindf(CRotM[idx].y) * 200.0;
    c->center.z = c->target->trans.z - cosdf(CRotM[idx].y) * 200.0;
    CenterM[idx].x = c->center.x;
    CenterM[idx].z = c->center.z;
}

void func_801064A8_fowl_play(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out) {
    out[0] = x * m[0][0] + y * m[1][0] + z * m[2][0];
    out[1] = x * m[0][1] + y * m[1][1] + z * m[2][1];
    out[2] = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

void func_80106528_fowl_play(f32 (*src)[4], f32 (*dst)[4]) {
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
        func_801064A8_fowl_play(dst, -m[3][0], -m[3][1], -m[3][2], dst[3]);
    }
}

void func_80106718_fowl_play(Vec* pos, Vec* out) {
    f32 m[4][4];
    f32 t;
    f32 w;

    func_8007DFE0_main(m, pos->x, pos->y, pos->z);
    guMtxCatF(m, D_8010F2A8_fowl_play, m);
    t = m[3][2] * D_8010F328_fowl_play;
    w = fabsf(t);
    if (w != 0.0) {
        out->x = m[3][0] * 160.0f / w / 1.3333334f;
        out->y = -m[3][1] * 120.0f / w;
    }
    out->x += 160.0;
    out->y += 120.0;
    out->z = w;
}

void func_80106824_fowl_play(f32 x, f32 y, f32 z, f32* out) {
    f32 m[4][4];
    f32 d;
    f32 w;

    d = z + D_8010F2E0_fowl_play;
    w = fabsf(d * D_8010F328_fowl_play);
    func_8007DFE0_main(m, 2.0f * x * w * 1.3333334f / 320.0f, -(2.0f * y * w / 240.0f), d);
    guMtxCatF(m, D_8010F2E8_fowl_play, m);
    out[0] = m[3][0];
    out[1] = m[3][1];
    out[2] = m[3][2];
}

void func_801068F0_fowl_play(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106960_fowl_play);
    D_8010F29C_fowl_play = 0;
}

void func_80106960_fowl_play(omObjData* obj) {
    Vec spots[16] = {
        { -500.0f, 0.0f, -1550.0f }, { -1050.0f, 0.0f, -1450.0f }, { -300.0f, 0.0f, -2245.0f },
        { -1400.0f, 0.0f, -600.0f }, { -1700.0f, 0.0f, 400.0f },   { -1550.0f, 0.0f, 800.0f },
        { -400.0f, 0.0f, 2150.0f },  { -1300.0f, 0.0f, 1450.0f },  { 750.0f, 0.0f, 1650.0f },
        { 1450.0f, 0.0f, 1600.0f },  { 450.0f, 0.0f, 2150.0f },    { 1550.0f, 0.0f, 800.0f },
        { 2000.0f, 0.0f, 500.0f },   { 1550.0f, 0.0f, -800.0f },   { 400.0f, 0.0f, -2150.0f },
        { 1150.0f, 0.0f, -1200.0f },
    }; /* unused */
    MgWork* work;

    obj->data = HuMemAllocTag(0xB4, 0x7918);
    work = obj->data;
    memset(work, 0, 0xB4);
    work->unk00[3] = 1;
    work->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.5f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E1404_minigame(obj, 0.0f, 1200.0f);
    D_8010F230_fowl_play[0] = func_8010B2C4_fowl_play(0x5B0000);
    D_8010F240_fowl_play[0] = func_8010B30C_fowl_play(D_8010F230_fowl_play[0], 2);
    func_80054904_main(D_8010F240_fowl_play[0], 0, 0, 0);
    HuSprAttrSet(D_8010F240_fowl_play[0], 0, 0x44000);
    func_80055588_main(D_8010F240_fowl_play[0], 0, 2.0f, 1.0f);
    func_800555B8_main(D_8010F240_fowl_play[0], 0, 8, 7);
    func_800555E8_main(D_8010F240_fowl_play[0], 0, 0, 0, 0x9F, 0xF0);
    func_80054904_main(D_8010F240_fowl_play[0], 1, 0xA0, 0);
    HuSprAttrSet(D_8010F240_fowl_play[0], 1, 0x44000);
    func_80055588_main(D_8010F240_fowl_play[0], 1, 2.0f, 1.0f);
    func_800555B8_main(D_8010F240_fowl_play[0], 1, 8, 7);
    func_800555E8_main(D_8010F240_fowl_play[0], 1, 0xA1, 0, 0x140, 0xF0);
    D_8010F230_fowl_play[1] = func_8010B2C4_fowl_play(0x5B0004);
    D_8010F240_fowl_play[1] = func_8010B30C_fowl_play(D_8010F230_fowl_play[1], 1);
    func_80054904_main(D_8010F240_fowl_play[1], 0, 0xA0, 0x78);
    HuSprAttrSet(D_8010F240_fowl_play[1], 0, 0x1000);
    obj->model[0] = func_8000B108_main(0x5B0005, 0x2D9);
    func_8001C8A8_main(obj->model[0], 3);
    obj->func = func_80106BD0_fowl_play;
}


void func_80106BD0_fowl_play(omObjData* obj) {
    HuSprite* spr;
    f32 x;
    s32 i;

    switch (D_8010F29C_fowl_play) {
        case 0:
            func_8001C8A8_main(func_8001AC8C_main(0xC0, func_8010DC24_fowl_play, 2), 3);
            GMesCreate(6);
            D_8010F200_fowl_play = HuAudFXPlay(0x4BF);
            D_8010F29E_fowl_play = 1800;
            D_8010F29C_fowl_play++;
        case 1:
            if (WipeStatGet() == 0) {
                if (++D_8010E7B2_fowl_play == 1) {
                    HuAudSeqPlay(0x36);
                }
            }
            if (GMesStatGet() == 0) {
                func_800E6F0C_minigame(2);
                D_8010F29C_fowl_play++;
                GMesCreate(0x1A, (D_8010F29E_fowl_play + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                if (FP_PLAYER(i)->unk24 != 0) {
                    D_8010E7AC_fowl_play = i;
                    D_8010F29C_fowl_play = 3;
                }
            }
            D_8010F29E_fowl_play--;
            func_8003F578_main((D_8010F29E_fowl_play + 29) / 30);
            if (D_8010F29E_fowl_play == 0) {
                D_8010F29C_fowl_play = 3;
            }
            break;
        case 3:
            func_8003F5C0_main();
            GMesCreate(0x11);
            HuAudSeqFadeOut(0x78);
            D_8010F29C_fowl_play = 6;
            D_8010E7A4_fowl_play = 15;
            D_8010F202_fowl_play = 15;
            break;
        case 6:
            if (--D_8010F202_fowl_play == 0) {
                func_8004AEF0_main(D_8010F200_fowl_play, 15);
            }
            if (GMesStatGet() == 0) {
                if (--D_8010E7A4_fowl_play == 0) {
                    for (i = 0; i < 2; i++) {
                        if (FP_PLAYER(i)->unk24 != 0) {
                            D_8010E7AC_fowl_play = i;
                        }
                    }
                    if (D_8010E7AC_fowl_play != -1) {
                        GMesCreate(0x16, FP_PLAYER(D_8010E7AC_fowl_play)->chr);
                        HuAudSeqPlay(0x67);
                    } else {
                        GMesCreate(0x20);
                        HuAudSeqPlay(0x6C);
                    }
                    D_8010E7A4_fowl_play = 15;
                    D_8010F29C_fowl_play++;
                    func_800E6F0C_minigame(4);
                }
            }
            break;
        case 7:
            if (GMesStatGet() == 0) {
                if (--D_8010E7A4_fowl_play == 0) {
                    D_8010F29C_fowl_play++;
                }
            }
            break;
        case 8:
            if (D_8010E7A4_fowl_play != 0) {
                if (--D_8010E7A4_fowl_play == 0) {
                    D_8010F29C_fowl_play++;
                }
            } else {
                func_800E6F0C_minigame(5);
                D_8010E7A4_fowl_play = 16;
                /* retail reads the low half of the s32 D_8010E7A4 (big-endian) as the fade length */
                WipeCreateOut(0, ((s16*)&D_8010E7A4_fowl_play)[1]);
                HuAudSeqFadeOut(((s16*)&D_8010E7A4_fowl_play)[1]);
                func_8004AB0C_main(((s16*)&D_8010E7A4_fowl_play)[1]);
            }
            break;
        case 9:
            func_8010E704_fowl_play();
            func_8004A950_main();
            omOvlReturnEx(1);
            break;
    }
    for (i = 0; i < 2; i++) {
        spr = HuSprGet(D_8010F240_fowl_play[0], i);
        x = CRotM[i].y * 256.0 / 360.0 - 256.0 + i * 160;
        func_80054904_main(D_8010F240_fowl_play[0], i, x, 0);
        spr->unk_48 = x;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010F29C_fowl_play = 8;
    }
}

/* Keeps obj at least r + 20 from the pen walls (fading out above y 20). */
void func_801070FC_fowl_play(omObjData* obj, f32 r) {
    Vec p;
    Vec d;
    s32 i;

    if (obj->trans.y >= 30.0) {
        return;
    }
    r = r + 20.0;
    if (obj->trans.y > 20.0) {
        r *= (30.0 - obj->trans.y) / 10.0;
    }
    for (i = 0; i < 8; i++) {
        if (!(r <= func_8010AC88_fowl_play(&obj->trans, &D_8010E7B4_fowl_play[i][0], &D_8010E7B4_fowl_play[i][1], &p))) {
            d.x = obj->trans.x - p.x;
            d.y = 0.0f;
            d.z = obj->trans.z - p.z;
            func_8010AB40_fowl_play(&d);
            obj->trans.x = r * d.x + p.x;
            obj->trans.z = r * d.z + p.z;
        }
    }
}

#ifdef NON_MATCHING
/* masked 0; n and &seg swap saved registers (s5/s6) */
/* Stops a move from prev to pos at the first pen wall it crosses, r + 20 short of it. */
u8 func_8010724C_fowl_play(Vec* pos, Vec* prev, f32 r) {
    Vec hit;
    Vec unused;
    Vec out;
    Vec seg;
    Vec dir;
    f32 len;
    f32 best;
    f32 c;
    f32 t;
    f32 d;
    u8 n;
    s32 i;

    dir.x = prev->x - pos->x;
    dir.y = 0.0f;
    dir.z = prev->z - pos->z;
    n = 0;
    best = sqrtf(dir.x * dir.x + dir.z * dir.z);
    len = best;
    func_8010A9EC_fowl_play(dir.x, dir.z);
    r = r + 20.0;
    for (i = 0; i < 8; i++) {
        seg.x = D_8010E7B4_fowl_play[i][1].x - D_8010E7B4_fowl_play[i][0].x;
        seg.y = D_8010E7B4_fowl_play[i][1].y - D_8010E7B4_fowl_play[i][0].y;
        seg.z = D_8010E7B4_fowl_play[i][1].z - D_8010E7B4_fowl_play[i][0].z;
        c = seg.x * D_8010E7B4_fowl_play[i][0].z - seg.z * D_8010E7B4_fowl_play[i][0].x;
        if (!((-seg.z * pos->x + seg.x * pos->z - c) * (-seg.z * prev->x + seg.x * prev->z - c) > 0.0f)) {
            t = func_8010AE10_fowl_play(D_8010E7B4_fowl_play[i], &seg, pos, &dir);
            if (!(t > 1.0) && !(t < 0.0)) {
                hit.x = t * seg.x + D_8010E7B4_fowl_play[i][0].x;
                hit.y = 0.0f;
                hit.z = t * seg.z + D_8010E7B4_fowl_play[i][0].z;
                d = func_8010AA64_fowl_play(pos, &hit);
                if (!(len <= d) && !(best <= d)) {
                    best = d;
                    func_8010AC88_fowl_play(prev, D_8010E7B4_fowl_play[i], &D_8010E7B4_fowl_play[i][1], &hit);
                    seg.x = prev->x - hit.x;
                    seg.y = 0.0f;
                    seg.z = prev->z - hit.z;
                    func_8010AB40_fowl_play(&seg);
                    out.x = hit.x - r * seg.x;
                    out.z = hit.z - r * seg.z;
                    n++;
                }
            }
        }
    }
    if (n) {
        pos->x = out.x;
        pos->z = out.z;
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010724C_fowl_play);
#endif

#ifdef NON_MATCHING
/* two instructions long: retail moves dist to $f24 before angle to $f20 and has no nop after each sindf/cosdf call; the rest matches */
/* Bounces a move of dist along angle off the nearest pen wall; returns the new angle. */
f32 func_801075B0_fowl_play(Vec* pos, f32 dist, f32 angle) {
    Vec hit;
    Vec out;
    Vec seg;
    Vec dir;
    f32 best;
    f32 t;
    f32 d;
    f32 wall;
    f32 rel;
    s32 i;

    best = dist;
    dir.x = best * sindf(angle);
    dir.y = 0.0f;
    dir.z = best * cosdf(angle);
    for (i = 0; i < 8; i++) {
        seg.x = (D_8010E7B4_fowl_play[i][1].x - D_8010E7B4_fowl_play[i][0].x) * 1.2;
        seg.y = D_8010E7B4_fowl_play[i][1].y - D_8010E7B4_fowl_play[i][0].y;
        seg.z = (D_8010E7B4_fowl_play[i][1].z - D_8010E7B4_fowl_play[i][0].z) * 1.2;
        t = func_8010AE10_fowl_play(D_8010E7B4_fowl_play[i], &seg, pos, &dir);
        if (!(t > 1.0) && !(t < 0.0)) {
            hit.x = t * seg.x + D_8010E7B4_fowl_play[i][0].x;
            hit.y = 0.0f;
            hit.z = t * seg.z + D_8010E7B4_fowl_play[i][0].z;
            d = func_8010AA64_fowl_play(pos, &hit);
            if (!(dist < d) && !(best < d)) {
                best = d;
                wall = func_8010A9EC_fowl_play(seg.x, seg.z);
                rel = func_8010A9EC_fowl_play(pos->x - D_8010E7B4_fowl_play[i][0].x,
                                              pos->z - D_8010E7B4_fowl_play[i][0].z) - wall;
                while (rel < -180.0) {
                    rel += 360.0;
                }
                while (rel > 180.0) {
                    rel -= 360.0;
                }
                if (rel > 0.0) {
                    angle = wall + 60.0;
                } else {
                    angle = wall - 60.0;
                }
                out.x = pos->x + dir.x;
                out.y = 0.0f;
                out.z = pos->z + dir.z;
                func_8010AC88_fowl_play(&out, D_8010E7B4_fowl_play[i], &D_8010E7B4_fowl_play[i][1], &hit);
                seg.x = out.x - hit.x;
                seg.y = 0.0f;
                seg.z = out.z - hit.z;
                func_8010AB40_fowl_play(&seg);
                out.x = hit.x - seg.x * 40.0;
                out.z = hit.z - seg.z * 40.0;
            }
        }
    }
    pos->x = out.x;
    pos->z = out.z;
    return angle;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_801075B0_fowl_play);
#endif

void func_801079B0_fowl_play(void) {
    s32 i;

    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EC280_minigame = 0;
    for (i = 0; i < 2; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 15, 50, -1, func_80107A4C_fowl_play);
    }
}



const FpU8x8 D_8010ED88_fowl_play = { { 0, 1, 2, 3, 4, 5, 6, 7 } };

void func_80107A4C_fowl_play(omObjData* obj) {
    FpU8x8 motTbl = D_8010ED88_fowl_play; /* unused */
    s32 files[3][8] = {
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    }; /* unused */
    u8 player;
    s8 chr;
    u32 file0;
    s32 mot;
    s32 i;
    MgWork* work;
    FpPlayer* fp;

    for (i = 0; i < 4; i++) {
        if (D_8010E87C_fowl_play == GwPlayer[i].group) {
            break;
        }
    }
    player = i;
    chr = GwPlayer[player].chr;
    file0 = D_800A178C_main[chr][0];
    mot = D_800A178C_main[chr][1];
    func_800E1BA8_minigame(obj, file0, mot, player, 0x2D9, 0x2D9);
    work = obj->data;
    work->unk50 &= ~1;
    work->unkEC = NULL;
    obj->trans.x = D_8010E884_fowl_play[D_8010E87C_fowl_play].x;
    obj->trans.y = D_8010E884_fowl_play[D_8010E87C_fowl_play].y;
    obj->trans.z = D_8010E884_fowl_play[D_8010E87C_fowl_play].z;
    work->unk3C = D_8010E8B4_fowl_play[D_8010E87C_fowl_play];
    switch (file0 >> 16) {
        case 6:
            work->unk48 *= 1.25f;
            break;
        case 4:
            work->unk48 *= 1.1f;
            break;
        case 5:
            work->unk48 *= 1.2f;
            break;
    }
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->trans.x = D_8010E884_fowl_play[D_8010E87C_fowl_play].x;
    obj->trans.y = D_8010E884_fowl_play[D_8010E87C_fowl_play].y;
    obj->trans.z = D_8010E884_fowl_play[D_8010E87C_fowl_play].z;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    work->unk158 = HuMemAllocTag(sizeof(FpPlayer), 31000);
    memset(work->unk158, 0, sizeof(FpPlayer));
    fp = work->unk158;
    fp->player = player;
    fp->idx = D_8010E87C_fowl_play;
    fp->chr = chr;
    fp->cpu = GwPlayer[player].stat & 1;
    fp->difficulty = GwPlayer[player].cpu_difficulty;
    fp->file = file0 | 0x9A;
    fp->unk24 = 0;
    fp->pos.x = obj->trans.x;
    fp->pos.y = obj->trans.y;
    fp->pos.z = obj->trans.z;
    fp->unk26 = 0;
    ((FpCam*)D_8010F294_fowl_play[D_8010E87C_fowl_play]->data)->target = obj;
    func_800E149C_minigame(obj, 0, 2);
    work->unk50 |= 0x8200;
    obj->func = func_80108298_fowl_play;
    func_8001C8A8_main(obj->model[0], 3);
    func_8001C8A8_main(obj->model[1], 3);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 17, func_80017BB8_main(chr, 0xE), 0, 0);
    func_800E5A00_minigame(obj, 32, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(obj, 21, func_80017BB8_main(chr, 0x1F), 0, 19);
    func_800E5A00_minigame(obj, 5, func_80017BB8_main(chr, 0x99), 0, 0);
    func_800E5A00_minigame(obj, 39, func_80017BB8_main(chr, 0x96), 1, 0);
    func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, 0x9A), 1, 60);
    switch (file0 >> 16) {
        case 3:
        case 4:
        case 5:
            func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x39), 1, 60);
            break;
        case 2:
        case 6:
        case 7:
        case 8:
        case 9:
            func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 0x3A), 1, 60);
            break;
    }
    func_800E5690_minigame(obj, 0);
    D_8010E87C_fowl_play++;
}

void func_80108020_fowl_play(omObjData* obj, u32 file0, s32 file1, s32 player, u16 arg4) {
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
/* 8 instructions long, scheduling only: a nop after each of six sindf/cosdf calls, and pad * 2 for
   &D_800D5558_main[pad] is hoisted into the switch cases' delay slots */
void func_80108298_fowl_play(omObjData* obj) {
    FpU8x8 motTbl = D_8010ED88_fowl_play; /* unused */
    MgWork* work;
    FpPlayer* fp;
    MgWork* ow;
    FpPlayer* op;
    omObjData* o;
    Vec p;
    u16* btnp;
    f32 r;
    f32 a;
    f32 mag;
    f32 d;
    s32 btn;
    s32 i;
    u8 pad;
    u8 hit;

    work = obj->data;
    fp = work->unk158;
    pad = work->unk57;
    hit = 0;
    if (D_8010F29C_fowl_play != 2) {
        D_800D20A1_main[pad] = 0;
        D_800CBB6E_main[pad] = 0;
        D_800D5558_main[pad] = 0;
        D_800CDA7C_main[pad] = 0;
    }
    switch (D_8010F29C_fowl_play) {
        case 0:
            fp->unk2C = fp->unk2E = fp->unk30 = fp->unk32 = fp->unk34 = fp->unk3C = fp->unk3E = 0;
            fp->unk36 = 450;
            fp->unk26 = 0;
            fp->unk27 = 0;
            break;
        case 2:
            if (fp->cpu == 0) {
                a = func_8010A9EC_fowl_play(D_800CBB6E_main[pad], -D_800D20A1_main[pad]) + CRotM[fp->idx].y;
                mag = sqrtf(D_800CBB6E_main[pad] * D_800CBB6E_main[pad] + D_800D20A1_main[pad] * D_800D20A1_main[pad]);
                D_800CBB6E_main[pad] = mag * sindf(a);
                D_800D20A1_main[pad] = -mag * cosdf(a);
            } else {
                D_800D20A1_main[pad] = 0;
                D_800CBB6E_main[pad] = 0;
                D_800D5558_main[pad] = 0;
                D_800CDA7C_main[pad] = 0;
                func_80108B08_fowl_play(obj);
            }
            break;
        case 6:
            if (fp->unk24 != 0) {
                a = func_8010A9EC_fowl_play(-obj->trans.x, -obj->trans.z);
                D_800CBB6E_main[pad] = sindf(a) * 18.0;
                D_800D20A1_main[pad] = -cosdf(a) * 18.0;
                func_8001C92C_main(obj->model[0], 1.0f);
            }
            break;
        case 7:
            fp->unk3C = 0;
            if (fp->unk24 == 1) {
                GwPlayer[work->unk59].bonusCoin += 10;
                func_800E5690_minigame(obj, 13);
                func_80045F1C_main(fp->file, -1, fp->idx);
                fp->unk24++;
            } else if (fp->unk24 == 0) {
                func_800E5690_minigame(obj, 14);
                fp->unk24--;
            }
            break;
        case 8:
            if (work != NULL) {
                HuMemFree(work->unk158);
                obj->data = NULL;
                obj->func = NULL;
            }
            return;
        case 9:
            return;
    }
    btnp = &D_800D5558_main[pad];
    btn = func_800E4A90_minigame(obj);
    fp->prev.x = obj->trans.x;
    fp->prev.y = obj->trans.y;
    fp->prev.z = obj->trans.z;
    if (fp->unk3C != 0) {
        *btnp &= ~0x4000;
    } else {
        HmfModelData[obj->model[0]].unk06 = 0xFF;
    }
    func_800DDD94_minigame(obj);
    if (btn & 0x40) {
        if (HmfModelData[obj->model[0]].unk40 >= 16.0 && HmfModelData[obj->model[0]].unk40 <= 20.0) {
            hit = 1;
        }
    }
    if (func_8010A738_fowl_play(obj, hit)) {
        fp->unk3C = 1;
        fp->unk24 = 1;
        func_8004AC5C_main(0x4C0, 2);
        func_8004AC5C_main(0x4C2, 3);
        omVibrate(work->unk59, 10, 0, 10);
        func_8001EED8_main(obj->model[0], obj->motion[39], 0);
    }
    for (i = 0; i < 2; i++) {
        o = D_800EC598_minigame[i];
        if (obj == o) {
            continue;
        }
        ow = o->data;
        op = ow->unk158;
        if (fabs(obj->trans.y - o->trans.y) > 30.0) {
            continue;
        }
        d = func_8010AA64_fowl_play(&obj->trans, &o->trans);
        r = work->unk48 + ow->unk48;
        if (r < d) {
            continue;
        }
        if (work->unk40 <= ow->unk40) {
            a = func_8010A9EC_fowl_play(o->trans.x - obj->trans.x, o->trans.z - obj->trans.z);
            o->trans.x = r * sindf(a) + obj->trans.x;
            o->trans.z = r * cosdf(a) + obj->trans.z;
            if (o->trans.y < 30.0) {
                p.x = op->prev.x;
                p.y = 0.0f;
                p.z = op->prev.z;
                if (func_8010724C_fowl_play(&p, &o->trans, ow->unk48)) {
                    o->trans.x = p.x;
                    o->trans.z = p.z;
                }
            }
        } else {
            a = func_8010A9EC_fowl_play(obj->trans.x - o->trans.x, obj->trans.z - o->trans.z);
            obj->trans.x = r * sindf(a) + o->trans.x;
            obj->trans.z = r * cosdf(a) + o->trans.z;
            if (obj->trans.y < 30.0) {
                p.x = fp->prev.x;
                p.y = 0.0f;
                p.z = fp->prev.z;
                if (func_8010724C_fowl_play(&p, &obj->trans, work->unk48)) {
                    obj->trans.x = p.x;
                    obj->trans.z = p.z;
                }
            }
        }
    }
    d = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
    r = 1200.0 - work->unk48 - 10.0;
    if (r < d) {
        a = func_8010A9EC_fowl_play(obj->trans.x, obj->trans.z);
        obj->trans.x = r * sindf(a);
        obj->trans.z = r * cosdf(a);
    }
    func_801070FC_fowl_play(obj, work->unk48);
    fp->unk18 = btn;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80108298_fowl_play);
#endif

void func_80108A70_fowl_play(omObjData* obj, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (HmfModelData[obj->model[i]].unk18 & 4) {
            func_800E4C88_minigame(obj, i, x, y, z, 0.0f, 0.0f);
            return;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", D_8010EE68_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80108B08_fowl_play);

void func_80109410_fowl_play(omObjData* obj, MgWork** work, FpPlayer** ep) {
    MgWork* w = obj->data;

    *work = w;
    *ep = w->unk158;
}

void func_80109424_fowl_play(void) {
    s32 i;

    D_8010F234_fowl_play = func_8010B2C4_fowl_play(0x5B0003);
    for (i = 0; i < 1; i++) {
        D_8010F290_fowl_play[i] = omAddObj(3, 5, 5, -1, func_801094A4_fowl_play);
    }
}

#ifdef NON_MATCHING
/* one instruction long: retail sign-extends the billboard id before storing its low byte to boards[i] */
void func_801094A4_fowl_play(omObjData* obj) {
    MgWork* work;
    FpChick* ch;
    f32 a;
    s16 id;
    s32 i;

    obj->data = HuMemAllocTag(sizeof(MgWork), 0x7918);
    work = obj->data;
    memset(work, 0, sizeof(MgWork));
    work->unkE8 = HuMemAllocTag(obj->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), 0x7918);
    memset(work->unkE8, 0, obj->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData));
    work->unk52 = 0;
    work->unkD0 = 0xFFFF;
    ch = HuMemAllocTag(sizeof(FpChick), 0x7918);
    work->unk158 = ch;
    memset(ch, 0, sizeof(FpChick));
    ch->state = 0;
    ch->unk01 = 0;
    ch->vel.x = ch->vel.y = ch->vel.z = 0.0f;
    ch->angle = ch->target = (f32)(func_8010A9A0_fowl_play() - 0x8000) * (1.0 / 32768.0) * 180.0;
    ch->speed = 20.0f;
    ch->unk02 = ch->unk04 = ch->unk06 = 0;
    obj->model[0] = func_8000B108_main(0x5B0006, 0x2D9);
    obj->model[1] = func_8000B0D4_main(9, 0x2D9);
    D_8010F238_fowl_play = func_8010B2C4_fowl_play(0xB);
    for (i = 0; i < 8; i++) {
        id = func_8010C1F4_fowl_play(D_8010F238_fowl_play, 0x20009000);
        ch->u.boards[i] = (s16)id;
        func_8010D148_fowl_play(id, 2);
        func_8010D2A4_fowl_play(id, -1, -0x3A, 0x69, 0xE0);
        func_8010CFDC_fowl_play(id, 1.2f, 1.2f, 1.2f);
        func_8010CE44_fowl_play(id, 0.5f);
    }
    Hu3DModelScaleSet(obj->model[1], 0.75f, 0.75f, 0.75f);
    func_800E5A00_minigame(obj, 0, 0x5B0007, 1, 0);
    func_800E5A00_minigame(obj, 1, 0x5B0008, 1, 0);
    func_800E5A00_minigame(obj, 2, 0x5B0009, 1, 0);
    func_800E5690_minigame(obj, 0);
    obj->func = func_80109844_fowl_play;
    obj->trans.x = (f32)(func_8010A9A0_fowl_play() - 0x8000) * (1.0 / 32768.0) * 40.0;
    obj->trans.z = (f32)(func_8010A9A0_fowl_play() - 0x8000) * (1.0 / 32768.0) * 40.0;
    for (i = 0; i < 32; i++) {
        ch->u.f.feathers[i].board = func_8010C1F4_fowl_play(D_8010F234_fowl_play, 0x10009000);
        func_8010D148_fowl_play(ch->u.f.feathers[i].board, 0);
        func_8010CFDC_fowl_play(ch->u.f.feathers[i].board, 2.0f, 2.0f, 2.0f);
        ch->u.f.feathers[i].unk01 = 0;
        ch->u.f.feathers[i].vel.x = ch->u.f.feathers[i].vel.y = ch->u.f.feathers[i].vel.z = 0.0f;
        ch->u.f.feathers[i].unk10 = 0.0f;
    }
    D_8010F2A0_fowl_play++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_801094A4_fowl_play);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_80109844_fowl_play);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010A738_fowl_play);

s32 func_8010A9A0_fowl_play(void) {
    u32 r;

    r = (rand8() + D_8010E8C8_fowl_play) * 0x41C64E6D + 0x3039;
    D_8010E8C8_fowl_play = r;
    return r >> 16;
}

f32 func_8010A9EC_fowl_play(f32 x, f32 z) {
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

f32 func_8010AA64_fowl_play(Vec* a, Vec* b) {
    return sqrtf((a->x - b->x) * (a->x - b->x) + (a->z - b->z) * (a->z - b->z));
}

void func_8010AAB8_fowl_play(Vec* dir, f32* angles) {
    f32 h = sqrtf(dir->x * dir->x + dir->z * dir->z);

    *angles++ = func_8010A9EC_fowl_play(h, -dir->y);
    *angles++ = func_8010A9EC_fowl_play(dir->x, dir->z);
    *angles = 0.0f;
}

f32 func_8010AB40_fowl_play(Vec* v) {
    f32 len = v->x * v->x + v->y * v->y + v->z * v->z;
    f32 inv;

    len = sqrtf(len);
    if (len != 0.0f) {
        inv = 1.0f / len;
        v->x = inv * v->x;
        v->y = inv * v->y;
        v->z = inv * v->z;
    } else {
        v->x = v->y = v->z = 0.0f;
    }
    return len;
}

#ifdef NON_MATCHING
/* masked 0; register allocation of the first subtraction differs */
/* The parameter of the point on the line a + t * d closest to p. */
f32 func_8010AC04_fowl_play(Vec* p, Vec* a, Vec* d) {
    f32 t;
    f32 n;

    t = (a->x - p->x) * d->x + (a->y - p->y) * d->y + (a->z - p->z) * d->z;
    n = -(d->x * d->x + d->y * d->y + d->z * d->z);

    if (n != 0.0f) {
        t /= n;
    }
    return t;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010AC04_fowl_play);
#endif

/* Distance in XZ from p to the segment a-b; the closest point goes to out. */
f32 func_8010AC88_fowl_play(Vec* p, Vec* a, Vec* b, Vec* out) {
    Vec d;
    f32 t;

    if (func_8010AA64_fowl_play(a, b) == 0.0f) {
        out->x = a->x;
        out->y = a->y;
        out->z = a->z;
        return func_8010AA64_fowl_play(p, a);
    }
    d.x = b->x - a->x;
    d.y = b->y - a->y;
    d.z = b->z - a->z;
    t = func_8010AC04_fowl_play(p, a, &d);
    if (t <= 0.0) {
        out->x = a->x;
        out->y = a->y;
        out->z = a->z;
    } else if (t >= 1.0) {
        out->x = b->x;
        out->y = b->y;
        out->z = b->z;
    } else {
        out->x = t * d.x + a->x;
        out->y = t * d.y + a->y;
        out->z = t * d.z + a->z;
    }
    return func_8010AA64_fowl_play(p, out);
}

/* The parameter along d1 where the line p1 + t * d1 meets the line p2 + s * d2, or -1. */
#ifdef NON_MATCHING
/* masked 7, one instruction short: retail divides into $f4 and moves the result to $f0 */
f32 func_8010AE10_fowl_play(Vec* p1, Vec* d1, Vec* p2, Vec* d2) {
    f32 ax;
    f32 ay;
    f32 az;
    f32 den;
    f32 a;
    f32 b;
    f32 t;
    s32 axis;

    t = -1.0f;
    ax = d2->x;
    if (ax < 0.0f) {
        ax = -ax;
    }
    ay = d2->y;
    if (ay < 0.0f) {
        ay = -ay;
    }
    az = d2->z;
    if (az < 0.0f) {
        az = -az;
    }
    if (ay <= ax) {
        axis = 0x100;
        if (az <= ax) {
            axis = 1;
        }
    } else {
        axis = 0x100;
        if (az <= ay) {
            axis = 0x10;
        }
    }
    if (axis & 3) {
        if (d1->x != 0.0f || d1->z != 0.0f) {
            den = d2->x * d1->z - d2->z * d1->x;
            if (den == 0.0f) {
                return t;
            }
            a = (p1->x - p2->x) * d2->z;
            b = (p1->z - p2->z) * d2->x;
        } else {
            den = d2->y * d1->x - d2->x * d1->y;
            if (den == 0.0f) {
                return t;
            }
            a = (p1->y - p2->y) * d2->x;
            b = (p1->x - p2->x) * d2->y;
        }
    } else if (axis & 0x30) {
        if (d1->x != 0.0f || d1->y != 0.0f) {
            den = d2->y * d1->x - d2->x * d1->y;
            if (den == 0.0f) {
                return t;
            }
            a = (p1->y - p2->y) * d2->x;
            b = (p1->x - p2->x) * d2->y;
        } else {
            den = d2->z * d1->y - d2->y * d1->z;
            if (den == 0.0f) {
                return t;
            }
            a = (p1->z - p2->z) * d2->y;
            b = (p1->y - p2->y) * d2->z;
        }
    } else {
        if (d1->x != 0.0f || d1->z != 0.0f) {
            den = d2->x * d1->z - d2->z * d1->x;
            if (den == 0.0f) {
                return t;
            }
            a = (p1->x - p2->x) * d2->z;
            b = (p1->z - p2->z) * d2->x;
        } else {
            den = d2->z * d1->y - d2->y * d1->z;
            if (den == 0.0f) {
                return t;
            }
            a = (p1->z - p2->z) * d2->y;
            b = (p1->y - p2->y) * d2->z;
        }
    }
    t = (a - b) / den;
    return t;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010AE10_fowl_play);
#endif

void func_8010B1A0_fowl_play(s16 model, const char* name, s16 frame, Vec* out) {
    HuMtx4F mdl;
    HuMtx4F res;
    HuMtx4F obj;
    HmfModel* m;

    func_80016B00_main(model, frame, name, obj);
    m = &HmfModelData[model];
    func_80088800_main(mdl, m->pos.x, m->pos.y, m->pos.z);
    func_80017D24_main(mdl, m->rot.x, m->rot.y, m->rot.z);
    func_80017CD0_main(mdl, m->scale.x, m->scale.y, m->scale.z);
    func_80018044_main(obj, mdl, res);
    out->x = res[0][0] + res[1][0] + res[2][0] + res[3][0];
    out->y = res[0][1] + res[1][1] + res[2][1] + res[3][1];
    out->z = res[0][2] + res[1][2] + res[2][2] + res[3][2];
}

s16 func_8010B2C4_fowl_play(s32 id) {
    void* file;
    s16 sprite;

    file = DataRead(id);
    sprite = func_80055810_main(file);
    DataClose(file);
    return sprite;
}

s16 func_8010B30C_fowl_play(s16 tex, s16 n) {
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

HuSprite_Unk84_Unk00_Struct* func_8010B3D4_fowl_play(s16 tex, s16 frame) {
    return &func_80055194_main(tex)->unk00[frame];
}

void func_8010B41C_fowl_play(u16 n) {
    PgBoard* b;
    s16 i;

    D_8010F350_fowl_play = n;
    D_8010F32C_fowl_play = HuMemAlloc(n * sizeof(PgBoard));
    for (i = 0; i < 6; i++) {
        D_8010F330_fowl_play[i] = 0;
    }
    for (i = 0; i < D_8010F350_fowl_play; i++) {
        b = &D_8010F32C_fowl_play[i];
        b->spr = NULL;
        b->func = NULL;
        b->flags = 0;
        b->a = 0x100;
        b->b = 0xFF;
        b->g = 0xFF;
        b->r = 0xFF;
        b->timer = 0.0f;
        b->frame = 0;
        b->speed = 1.0f;
        b->unk1C = 0;
        b->unk1B = 0;
        b->ofs.x = b->ofs.y = b->ofs.z = 0.0f;
        b->pos.x = b->pos.y = b->pos.z = 0.0f;
        b->scale.x = b->scale.y = b->scale.z = 1.0f;
        b->rot.x = b->rot.y = b->rot.z = 0.0f;
    }
}

void func_8010B564_fowl_play(Gfx** gfx, HuSprite_Unk84_Unk00_Struct* cel, u8 fmt, u8 siz, u16 rows, u16 uls,
                                  u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt, s32 mode) {
    Gfx* g = *gfx;

    switch (mode) {
        case 0:
            gDPLoadTextureTile_4b(g++, 0x0C000000, fmt, cel->unk04, rows, uls, ult, lrs, lrt, 0, cms, cmt, masks,
                                  maskt, 0, 0);
            break;
        case 1:
            func_80034998_main(&g, 0x0C000000, fmt, cel->unk04, rows, uls, ult, lrs, lrt, 0, cms, cmt, masks, maskt,
                                0, 0);
            break;
        case 2:
            func_800341D0_main(&g, 0x0C000000, fmt, siz, cel->unk04, cel->unk06, uls, ult, lrs, lrt, 0, cms, cmt,
                                masks, maskt, 0, 0);
            break;
        case 3:
            func_8003465C_main(&g, (void*)0x0C000000, fmt, siz, cel->unk04, rows, uls, ult, lrs, lrt, 0, cms, cmt,
                                masks, maskt, 0, 0);
            break;
    }
    *gfx = g;
}

#ifdef NON_MATCHING
/* Builds a billboard's display list: palette, then one texture load and two triangles per strip. */
s16 func_8010B8D4_fowl_play(PgBoard* b) {
    HuSprite_Unk84_Unk00_Struct* cel;
    HuSprite_Unk84_Unk00_Struct tex;
    Gfx* g;
    Gfx* buf;
    Gfx* start;
    s32 fmt;
    s32 siz;
    s32 mode;
    s32 w;
    u32 rowH;
    u32 strips;
    s32 rem;
    s32 idx;
    s32 cms;
    s32 cmt;
    s32 masks;
    s32 maskt;
    s32 i;

    cel = b->spr->unk00;
    buf = HuMemAlloc(0x1000);
    g = buf;
    gSPSegment(g++, 0x0C, cel->unk00);
    gSPSegment(g++, 0x0E, b->vtx);
    start = g;
    gDPPipeSync(g++);
    switch (b->spr->unk18) {
        case 4:
            siz = 0;
            if (b->spr->unk1A == 1) {
                fmt = 3;
                gDPSetTextureLUT(g++, G_TT_NONE);
            } else {
                fmt = 2;
                gDPLoadTLUT_pal16(g++, 0, b->spr->unk0C);
                gDPSetTextureLUT(g++, G_TT_RGBA16);
            }
            mode = 0;
            break;
        case 8:
            siz = 1;
            if (b->spr->unk1A == 1) {
                fmt = 3;
                gDPSetTextureLUT(g++, G_TT_NONE);
            } else {
                fmt = 2;
                gDPLoadTLUT_pal256(g++, b->spr->unk0C);
                gDPSetTextureLUT(g++, G_TT_RGBA16);
            }
            mode = 2;
            break;
        case 0x10:
            siz = 2;
            fmt = (b->spr->unk1A == 1) ? 3 : 0;
            gDPSetTextureLUT(g++, G_TT_NONE);
            mode = 2;
            break;
        case 0x20:
            siz = 3;
            fmt = 0;
            gDPSetTextureLUT(g++, G_TT_NONE);
            mode = 2;
            break;
        case 0x8004:
            siz = 0;
            fmt = 4;
            gDPSetTextureLUT(g++, G_TT_NONE);
            mode = 0;
            break;
        case 0x8008:
            siz = 1;
            fmt = 4;
            gDPSetTextureLUT(g++, G_TT_NONE);
            mode = 2;
            break;
    }
    w = (((cel->unk04 << siz) >> 4) * 16) >> siz;
    if (w < cel->unk04) {
        w += 16 >> siz;
    }
    switch (fmt) {
        case 2:
            if ((0x1000 >> siz) < cel->unk06 * w) {
                rowH = (0x1000 >> siz) / w;
            } else {
                rowH = cel->unk06;
            }
            break;
        case 4:
            rowH = cel->unk06;
            if ((s32)(cel->unk06 * w) > 0x1000) {
                rowH = 0x1000 / w;
            }
            break;
        default:
            if ((0x2000 >> siz) < cel->unk06 * w) {
                rowH = (0x2000 >> siz) / w;
            } else {
                rowH = cel->unk06;
            }
            break;
    }
    strips = cel->unk06 / rowH;
    rem = cel->unk06 - strips * rowH;
    /* a whole strip fits one LoadBlock: use the block loaders */
    if (cel->unk04 % (16 >> siz) == 0 && (u32)((rowH * cel->unk04) << siz) <= 0x1000) {
        idx = cel->unk04 >> D_8010E8CC_fowl_play[siz];
        if ((u32)D_8010E8DC_fowl_play[idx] >= rowH || rowH == D_8010EA14_fowl_play[idx]) {
            mode++;
        }
    }
    if (b->flags & 0xC0000) {
        masks = b->unk1B;
        cms = ((s32)b->flags >> 18) - 1;
    } else {
        masks = 0;
        cms = 0;
    }
    if (b->flags & 0x300000) {
        maskt = b->unk1C;
        cmt = ((s32)b->flags >> 20) - 1;
    } else {
        maskt = 0;
        cmt = 0;
    }
    gDPPipeSync(g++);
    tex = *cel;
    tex.unk00 = (void*)0x0C000000;
    if (((s32)b->flags < 0) & (strips == 1) && rem == 0) {
        func_8010B564_fowl_play(&g, &tex, fmt, siz, rowH, 0, 0, cel->unk04 - 1, cel->unk06 - 1, cms, cmt, masks,
                                     maskt, mode);
        gSPVertex(g++, 0x0E000000, 5, 0);
        gSP2Triangles(g++, 0, 2, 4, 0, 2, 3, 4, 0);
        gSP2Triangles(g++, 0, 4, 1, 0, 4, 3, 1, 0);
    } else {
        for (i = 0; i < strips; i++) {
            func_8010B564_fowl_play(&g, &tex, fmt, siz, rowH, 0, i * rowH, cel->unk04 - 1, (i + 1) * rowH - 1,
                                         cms, cmt, masks, maskt, mode);
            gSPVertex(g++, 0x0E000000 + i * 2 * sizeof(Vtx), 4, 0);
            gSP2Triangles(g++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
        if (rem != 0) {
            func_8010B564_fowl_play(&g, &tex, fmt, siz, rem, 0, i * rowH, cel->unk04 - 1, cel->unk06 - 1, cms,
                                         cmt, masks, maskt, mode);
            gSPVertex(g++, 0x0E000000 + i * 2 * sizeof(Vtx), 4, 0);
            gSP2Triangles(g++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
    }
    gDPPipeSync(g++);
    gSPEndDisplayList(g++);
    b->cmds = g - start;
    b->gfx = HuMemAlloc(b->cmds * sizeof(Gfx));
    memcpy(b->gfx, start, b->cmds * sizeof(Gfx));
    HuMemFree(buf);
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010B8D4_fowl_play);
#endif

#ifdef NON_MATCHING
/* Creates a billboard from sprite tex: a strip of quads sized to fit TMEM, then its display list. */
s16 func_8010C1F4_fowl_play(s16 tex, u32 flags) {
    PgBoard* b;
    HuSprite_Unk84_Unk00_Struct* cel;
    s32 siz;
    s32 mode;
    s32 w;
    u32 rowH;
    u32 strips;
    s32 rem;
    s32 i;
    s32 j;
    s32 tc;
    s32 id;

    for (id = 0; id < D_8010F350_fowl_play; id++) {
        if (D_8010F32C_fowl_play[id].spr == NULL) {
            break;
        }
    }
    if (id == D_8010F350_fowl_play) {
        return -1;
    }
    b = &D_8010F32C_fowl_play[id];
    b->spr = D_800C9530_main[tex];
    b->flags = flags;
    b->unk1A = 7;
    cel = b->spr->unk00;
    switch (b->spr->unk18) {
        case 4:
            siz = 0;
            mode = (b->spr->unk1A == 1) ? 3 : 2;
            break;
        case 8:
            siz = 1;
            mode = (b->spr->unk1A == 1) ? 3 : 2;
            break;
        case 0x10:
            siz = 2;
            mode = (b->spr->unk1A == 1) ? 3 : 0;
            break;
        case 0x20:
            siz = 3;
            mode = 0;
            break;
        case 0x8004:
            siz = 0;
            mode = 4;
            break;
        case 0x8008:
            siz = 1;
            mode = 4;
            break;
    }
    w = (((cel->unk04 << siz) >> 4) * 16) >> siz;
    if (w < cel->unk04) {
        w += 16 >> siz;
    }
    switch (mode) {
        case 2:
            if ((0x1000 >> siz) < cel->unk06 * w) {
                rowH = (0x1000 >> siz) / w;
            } else {
                rowH = cel->unk06;
            }
            break;
        case 4:
            rowH = cel->unk06;
            if ((s32)(cel->unk06 * w) > 0x1000) {
                rowH = 0x1000 / w;
            }
            break;
        default:
            if ((0x2000 >> siz) < cel->unk06 * w) {
                rowH = (0x2000 >> siz) / w;
            } else {
                rowH = cel->unk06;
            }
            break;
    }
    strips = cel->unk06 / rowH;
    rem = cel->unk06 - strips * rowH;
    b->rows = strips + 2;
    b->rowH = rowH;
    b->vtx = HuMemAlloc((strips + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < strips + 1; i++) {
        b->vtx[i * 2].v.ob[0] = 0;
        b->vtx[i * 2 + 1].v.ob[0] = cel->unk04;
        b->vtx[i * 2].v.ob[1] = b->vtx[i * 2 + 1].v.ob[1] = -i * rowH;
        b->vtx[i * 2].v.tc[0] = 0;
        b->vtx[i * 2 + 1].v.tc[0] = cel->unk04 << 6;
        tc = (i * rowH) << 6;
        b->vtx[i * 2].v.tc[1] = tc;
        b->vtx[i * 2 + 1].v.tc[1] = tc;
        for (j = 0; j < 2; j++) {
            b->vtx[i * 2 + j].v.ob[2] = 0;
            b->vtx[i * 2 + j].v.cn[0] = 0xFF;
            b->vtx[i * 2 + j].v.cn[1] = 0xFF;
            b->vtx[i * 2 + j].v.cn[2] = 0xFF;
            b->vtx[i * 2 + j].v.cn[3] = 0xFF;
        }
    }
    if (rem != 0) {
        b->vtx[i * 2].v.ob[0] = 0;
        b->vtx[i * 2 + 1].v.ob[0] = cel->unk04;
        b->vtx[i * 2 + 1].v.ob[1] = b->vtx[i * 2].v.ob[1] = cel->unk06;
        b->vtx[i * 2].v.tc[0] = 0;
        b->vtx[i * 2 + 1].v.tc[0] = cel->unk04 << 6;
        b->vtx[i * 2].v.tc[1] = b->vtx[i * 2 + 1].v.tc[1] = cel->unk06 << 6;
        for (j = 0; j < 2; j++) {
            b->vtx[i * 2 + j].v.ob[2] = 0;
            b->vtx[i * 2 + j].v.cn[0] = 0xFF;
            b->vtx[i * 2 + j].v.cn[1] = 0xFF;
            b->vtx[i * 2 + j].v.cn[2] = 0xFF;
            b->vtx[i * 2 + j].v.cn[3] = 0xFF;
        }
    } else if (strips == 1) {
        b->vtx[4].v.ob[0] = cel->unk04 * 0.5;
        b->vtx[4].v.ob[1] = -(s32)cel->unk06 * 0.5;
        b->vtx[4].v.ob[2] = 0;
        b->vtx[4].v.tc[0] = cel->unk04 * 0.5 * 64.0;
        b->vtx[4].v.tc[1] = cel->unk06 * 0.5 * 64.0;
        b->vtx[4].v.cn[0] = 0xFF;
        b->vtx[4].v.cn[1] = 0xFF;
        b->vtx[4].v.cn[2] = 0xFF;
        b->vtx[4].v.cn[3] = 0xFF;
    }
    if (func_8010B8D4_fowl_play(b) == 0) {
        HuMemFree(b->vtx);
        id = -1;
    }
    return id;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010C1F4_fowl_play);
#endif

#ifdef NON_MATCHING
/* Gives billboard id sprite tex: rebuilds its strip and display list. */
void func_8010C7FC_fowl_play(s16 id, s16 tex) {
    PgBoard* b;
    HuSprite_Unk84_Unk00_Struct* cel;
    s32 siz;
    s32 mode;
    s32 w;
    u32 rowH;
    u32 strips;
    s32 rem;
    s32 i;
    s32 j;
    s32 tc;

    b = &D_8010F32C_fowl_play[id];
    b->spr = D_800C9530_main[tex];
    cel = b->spr->unk00;
    HuMemFree(b->vtx);
    HuMemFree(b->gfx);
    switch (b->spr->unk18) {
        case 4:
            siz = 0;
            mode = (b->spr->unk1A == 1) ? 3 : 2;
            break;
        case 8:
            siz = 1;
            mode = (b->spr->unk1A == 1) ? 3 : 2;
            break;
        case 0x10:
            siz = 2;
            mode = (b->spr->unk1A == 1) ? 3 : 0;
            break;
        case 0x20:
            siz = 3;
            mode = 0;
            break;
        case 0x8004:
            siz = 0;
            mode = 4;
            break;
        case 0x8008:
            siz = 1;
            mode = 4;
            break;
    }
    w = (((cel->unk04 << siz) >> 4) * 16) >> siz;
    if (w < cel->unk04) {
        w += 16 >> siz;
    }
    switch (mode) {
        case 2:
            if ((0x1000 >> siz) < cel->unk06 * w) {
                rowH = (0x1000 >> siz) / w;
            } else {
                rowH = cel->unk06;
            }
            break;
        case 4:
            rowH = cel->unk06;
            if ((s32)(cel->unk06 * w) > 0x1000) {
                rowH = 0x1000 / w;
            }
            break;
        default:
            if ((0x2000 >> siz) < cel->unk06 * w) {
                rowH = (0x2000 >> siz) / w;
            } else {
                rowH = cel->unk06;
            }
            break;
    }
    strips = cel->unk06 / rowH;
    rem = cel->unk06 - strips * rowH;
    b->rows = strips + 2;
    b->rowH = rowH;
    b->vtx = HuMemAlloc((strips + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < strips + 1; i++) {
        b->vtx[i * 2].v.ob[0] = 0;
        b->vtx[i * 2 + 1].v.ob[0] = cel->unk04;
        b->vtx[i * 2].v.ob[1] = b->vtx[i * 2 + 1].v.ob[1] = -i * rowH;
        b->vtx[i * 2].v.tc[0] = 0;
        b->vtx[i * 2 + 1].v.tc[0] = cel->unk04 << 6;
        tc = (i * rowH) << 6;
        b->vtx[i * 2].v.tc[1] = tc;
        b->vtx[i * 2 + 1].v.tc[1] = tc;
        for (j = 0; j < 2; j++) {
            b->vtx[i * 2 + j].v.ob[2] = 0;
            b->vtx[i * 2 + j].v.cn[0] = 0xFF;
            b->vtx[i * 2 + j].v.cn[1] = 0xFF;
            b->vtx[i * 2 + j].v.cn[2] = 0xFF;
            b->vtx[i * 2 + j].v.cn[3] = 0xFF;
        }
    }
    if (rem != 0) {
        b->vtx[i * 2].v.ob[0] = 0;
        b->vtx[i * 2 + 1].v.ob[0] = cel->unk04;
        b->vtx[i * 2 + 1].v.ob[1] = b->vtx[i * 2].v.ob[1] = cel->unk06;
        b->vtx[i * 2].v.tc[0] = 0;
        b->vtx[i * 2 + 1].v.tc[0] = cel->unk04 << 6;
        b->vtx[i * 2].v.tc[1] = b->vtx[i * 2 + 1].v.tc[1] = cel->unk06 << 6;
        for (j = 0; j < 2; j++) {
            b->vtx[i * 2 + j].v.ob[2] = 0;
            b->vtx[i * 2 + j].v.cn[0] = 0xFF;
            b->vtx[i * 2 + j].v.cn[1] = 0xFF;
            b->vtx[i * 2 + j].v.cn[2] = 0xFF;
            b->vtx[i * 2 + j].v.cn[3] = 0xFF;
        }
    } else if (strips == 1) {
        b->vtx[4].v.ob[0] = cel->unk04 * 0.5;
        b->vtx[4].v.ob[1] = -(s32)cel->unk06 * 0.5;
        b->vtx[4].v.ob[2] = 0;
        b->vtx[4].v.tc[0] = cel->unk04 * 0.5 * 64.0;
        b->vtx[4].v.tc[1] = cel->unk06 * 0.5 * 64.0;
        b->vtx[4].v.cn[0] = 0xFF;
        b->vtx[4].v.cn[1] = 0xFF;
        b->vtx[4].v.cn[2] = 0xFF;
        b->vtx[4].v.cn[3] = 0xFF;
    }
    func_8010B8D4_fowl_play(b);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010C7FC_fowl_play);
#endif

void func_8010CD84_fowl_play(s16 id, s16 tex) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->spr = D_800C9530_main[tex];
        b->a = 0x100;
        b->b = 0xFF;
        b->g = 0xFF;
        b->r = 0xFF;
        b->timer = 0.0f;
        b->frame = 0;
        b->speed = 1.0f;
    }
}

void func_8010CE04_fowl_play(s16 id, s16 frame) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->frame = frame;
        b->timer = 0.0f;
    }
}

void func_8010CE44_fowl_play(s16 id, f32 speed) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->speed = speed;
    }
}

void func_8010CE84_fowl_play(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->flags |= 0x04000000;
        b->ofs.x = x;
        b->ofs.y = y;
        b->ofs.z = z;
    }
}

void func_8010CEE4_fowl_play(s16 id, f32 speed) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->ofs.z = speed;
    }
}

void func_8010CF24_fowl_play(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->pos.x = x;
        b->pos.y = y;
        b->pos.z = z;
    }
}

void func_8010CF74_fowl_play(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->pos.x += x;
        b->pos.y += y;
        b->pos.z += z;
    }
}

void func_8010CFDC_fowl_play(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->scale.x = x;
        b->scale.y = y;
        b->scale.z = z;
    }
}

void func_8010D02C_fowl_play(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->rot.x = x;
        b->rot.y = y;
        b->rot.z = z;
    }
}

void func_8010D07C_fowl_play(s16 id, u32 flags) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->flags |= flags;
    }
}

void func_8010D0C0_fowl_play(s16 id, u32 flags) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->flags &= ~flags;
    }
}

#ifdef NON_MATCHING
s32 func_8010D108_fowl_play(s16 id) {
    s32 flags = -1;
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        flags = b->flags;
    }
    return flags;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D108_fowl_play);
#endif

void func_8010D148_fowl_play(s16 id, s8 arg1) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->unk1A = arg1;
    }
}

PgBoard* func_8010D184_fowl_play(s16 id) {
    if (id == -1) {
        return NULL;
    }
    return &D_8010F32C_fowl_play[id];
}

Vtx* func_8010D1C4_fowl_play(s16 id) {
    PgBoard* b;

    if (id == -1) {
        return NULL;
    }
    b = &D_8010F32C_fowl_play[id];
    return b->vtx;
}

#ifdef NON_MATCHING
s32 func_8010D208_fowl_play(s16 id, s16 w, s16 h) {
    PgBoard* b;
    Vtx* v;
    s32 x = w;
    s32 y = h;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        if (b->rows == 3) {
            b->flags |= 0x80000000;
            v = b->vtx;
            v[4].v.ob[0] = x;
            v[4].v.ob[1] = -y;
            v[4].v.ob[2] = 0;
            v[4].v.tc[0] = x << 6;
            v[4].v.tc[1] = y << 6;
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D208_fowl_play);
#endif

void func_8010D2A4_fowl_play(s16 id, s8 r, s8 g, s8 b, u16 a) {
    PgBoard* p;

    if (id != -1) {
        p = &D_8010F32C_fowl_play[id];
        p->r = r;
        p->g = g;
        p->b = b;
        p->a = a;
    }
}

void func_8010D2F0_fowl_play(s16 id) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        if (b->spr != NULL) {
            HuMemFree(b->gfx);
            HuMemFree(b->vtx);
            b->spr = NULL;
            b->flags = 0;
            b->a = 0x100;
            b->b = 0xFF;
            b->g = 0xFF;
            b->r = 0xFF;
            b->timer = 0.0f;
            b->frame = 0;
            b->unk1C = 0;
            b->unk1B = 0;
            b->ofs.x = b->ofs.y = b->ofs.z = 0.0f;
            b->pos.x = b->pos.y = b->pos.z = 0.0f;
            b->scale.x = b->scale.y = b->scale.z = 1.0f;
            b->rot.x = b->rot.y = b->rot.z = 0.0f;
            b->speed = 1.0f;
        }
    }
}

void func_8010D3D0_fowl_play(s32 id, s32 on) {
    PgBoard* b = &D_8010F32C_fowl_play[id];
    s32 i;

    if (on) {
        b->flags |= 0x10000;
        for (i = 0; i < b->rows; i++) {
            b->vtx[i].v.cn[0] = 0;
            b->vtx[i].v.cn[1] = 0;
            b->vtx[i].v.cn[2] = 0x80;
        }
    } else {
        b->flags &= ~0x10000;
        for (i = 0; i < b->rows; i++) {
            b->vtx[i].v.cn[0] = 0xFF;
            b->vtx[i].v.cn[1] = 0xFF;
            b->vtx[i].v.cn[2] = 0xFF;
            b->vtx[i].v.cn[3] = 0xFF;
        }
    }
}

void func_8010D4D0_fowl_play(s32 id, s32 flip) {
    PgBoard* b = &D_8010F32C_fowl_play[id];
    s32 i;

    if (flip) {
        for (i = 0; i < b->rows; i++) {
            b->vtx[i * 2].v.tc[0] = b->spr->unk00->unk04 << 6;
            b->vtx[i * 2 + 1].v.tc[0] = 0;
        }
    } else {
        for (i = 0; i < b->rows; i++) {
            b->vtx[i * 2].v.tc[0] = 0;
            b->vtx[i * 2 + 1].v.tc[0] = b->spr->unk00->unk04 << 6;
        }
    }
}

void func_8010D5A0_fowl_play(s32 id, s32 flip) {
    PgBoard* b = &D_8010F32C_fowl_play[id];
    s32 rem = b->spr->unk00->unk06 - (b->rows - 2) * b->rowH;
    s32 i;

    if (flip) {
        for (i = 0; i < b->rows - 1; i++) {
            b->vtx[i * 2].v.tc[1] = b->vtx[i * 2 + 1].v.tc[1] = b->spr->unk00->unk06 - i * b->rowH;
        }
        if (rem != 0) {
            b->vtx[i * 2].v.tc[1] = b->vtx[i * 2 + 1].v.tc[1] = 0;
        }
    } else {
        for (i = 0; i < b->rows - 1; i++) {
            b->vtx[i * 2].v.ob[1] = b->vtx[i * 2 + 1].v.ob[1] = i * b->rowH;
        }
        if (rem != 0) {
            b->vtx[i * 2].v.ob[1] = b->vtx[i * 2 + 1].v.ob[1] = b->spr->unk00->unk06;
        }
    }
}

void func_8010D6D8_fowl_play(s16 id, s32 arg1) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->func = (void (*)(PgBoard*))arg1;
    }
}

void func_8010D714_fowl_play(s16 id, s8 arg1, s8 arg2, u32 flags) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        b->unk1B = arg1;
        b->unk1C = arg2;
        b->flags |= flags;
        HuMemFree(b->gfx);
        func_8010B8D4_fowl_play(b);
    }
}

#ifdef NON_MATCHING
void func_8010D784_fowl_play(s16 id, s32 on) {
    PgBoard* b;
    Vtx* v;
    s8 c;
    s8 a;
    s32 i;

    if (id != -1) {
        b = &D_8010F32C_fowl_play[id];
        if (on) {
            c = 0;
            a = 0x70;
        } else {
            c = -1;
            a = -1;
        }
        for (i = 0; i < b->rows; i++) {
            v = &b->vtx[i];
            v->v.cn[0] = v->v.cn[1] = v->v.cn[3] = c;
            b->vtx[i].v.cn[2] = a;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D784_fowl_play);
#endif

void func_8010D81C_fowl_play(void) {
    PgBoard* b;
    s32 i;

    if (++D_8010EB64_fowl_play >= 6) {
        D_8010EB64_fowl_play = 0;
    }
    D_8010F34C_fowl_play = 0;
    for (i = 0; i < D_8010F350_fowl_play; i++) {
        b = &D_8010F32C_fowl_play[i];
        if (b->spr != NULL) {
            D_8010F34C_fowl_play += (b->cmds * sizeof(Gfx) + b->rows * 2 * sizeof(Vtx)) + 0x40;
        }
    }
    if (D_8010F330_fowl_play[D_8010EB64_fowl_play] != NULL) {
        HuMemFree(D_8010F330_fowl_play[D_8010EB64_fowl_play]);
    }
    if (D_8010F34C_fowl_play != 0) {
        D_8010F330_fowl_play[D_8010EB64_fowl_play] = HuMemAlloc(D_8010F34C_fowl_play);
    } else {
        D_8010F330_fowl_play[D_8010EB64_fowl_play] = NULL;
    }
    D_8010F348_fowl_play = D_8010F330_fowl_play[D_8010EB64_fowl_play];
}

#ifdef NON_MATCHING
/* Sorts the visible billboards by view depth into the opaque (D_8010DE00) and translucent (D_8010DE68) lists. */
void func_8010D970_fowl_play(HuCamera* cam, f32 (*view)[4]) {
    PgBoard tail0;
    PgBoard tail1;
    PgBoard* unused[256];
    f32 m[4][4];
    f32 x0;
    f32 x1;
    f32 z0;
    f32 z1;
    PgBoard* b;
    PgBoard* list;
    PgBoard* n;
    s32 i;

    x0 = cam->at.x - 640.0;
    x1 = cam->at.x + 640.0;
    z0 = cam->at.z - 640.0;
    z1 = cam->at.z + 640.0;
    D_8010F360_fowl_play.depth = 0.0f;
    D_8010F3C8_fowl_play.depth = 99999.9f;
    tail0.depth = -99999.9f;
    tail1.depth = 0.0f;
    D_8010F3C8_fowl_play.prev = NULL;
    D_8010F360_fowl_play.prev = NULL;
    D_8010F360_fowl_play.next = &tail0;
    D_8010F3C8_fowl_play.next = &tail1;
    tail0.prev = &D_8010F360_fowl_play;
    tail1.prev = &D_8010F3C8_fowl_play;
    tail1.next = NULL;
    tail0.next = NULL;
    for (i = 0; i < D_8010F350_fowl_play; i++) {
        b = &D_8010F32C_fowl_play[i];
        if (b->spr == NULL) {
            continue;
        }
        if (b->pos.x < x0 || x1 < b->pos.x) {
            continue;
        }
        if (b->pos.z < z0 || z1 < b->pos.z) {
            continue;
        }
        func_8007DFE0_main(m, b->pos.x, b->pos.y, b->pos.z);
        guMtxCatF(m, view, m);
        b->depth = m[3][2];
        if (b->depth > 0.0) {
            continue;
        }
        if ((b->flags & 0x1000) && b->a < 0x100) {
            list = &D_8010F3C8_fowl_play;
            b->depth = -(f64)b->depth;
        } else {
            list = &D_8010F360_fowl_play;
        }
        n = list->next;
        while (b->depth < n->depth) {
            n = n->next;
        }
        n->prev->next = b;
        b->prev = n->prev;
        b->next = n;
        n->prev = b;
    }
    tail1.prev->next = NULL;
    tail0.prev->next = NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3A_fowl_play/2C5B50", func_8010D970_fowl_play);
#endif

void func_8010DC24_fowl_play(Gfx** gfx, s32 arg1, s32 arg2) {
    HuCamera* cam = (HuCamera*)arg2;
    f32 unused0[2][4][4];
    f32 view[4][4];
    u8 unused1[0x100];
    Vec rot;
    Vec dir;
    u8 unused2[0x840];
    Gfx* g;
    PgBoard* b;

    g = *gfx;
    func_80079480_main(view, cam->pos.x, cam->pos.y, cam->pos.z, cam->at.x, cam->at.y, cam->at.z, cam->up.x,
                       cam->up.y, cam->up.z);
    dir.x = cam->at.x - cam->pos.x;
    dir.y = cam->at.y - cam->pos.y;
    dir.z = cam->at.z - cam->pos.z;
    func_8010AAB8_fowl_play(&dir, (f32*)&rot);
    func_8010D81C_fowl_play();
    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_2CYCLE);
    gDPSetTexturePersp(g++, G_TP_PERSP);
    gSPTexture(g++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(g++, 0x060600);
    gSPSetGeometryMode(g++, 0x280004);
    gDPSetAlphaDither(g++, G_AD_PATTERN);
    func_8010D970_fowl_play(cam, view);
    for (b = D_8010F360_fowl_play.next; b != NULL; b = b->next) {
        g = func_8010DE4C_fowl_play(g, b, view, &rot);
    }
    for (b = D_8010F3C8_fowl_play.next; b != NULL; b = b->next) {
        g = func_8010DE4C_fowl_play(g, b, view, &rot);
    }
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    *gfx = g;
    if (HmfPauseF == 0) {
        func_8010E544_fowl_play();
    }
}

Gfx* func_8010DE4C_fowl_play(Gfx* g, PgBoard* b, f32 (*view)[4], Vec* rot) {
    f32 sc[4][4];
    f32 m[4][4];
    f32 ofs[4][4];
    f32 inv[4][4];
    HuSprite_Unk84_Unk00_Struct* cel;
    u8* vtx;
    Mtx* mtx;
    u8* dl;
    u32 rm1;
    u32 rm2;
    u16 fmt;

    cel = &b->spr->unk00[b->frame];
    gDPPipeSync(g++);
    gDPSetTextureFilter(g++, D_8010EB54_fowl_play[((s32)b->flags >> 2) & 3]);
    gDPSetColorDither(g++, D_8010EB4C_fowl_play[((s32)b->flags >> 4) & 3]);
    gDPSetAlphaCompare(g++, D_8010EB5C_fowl_play[((s32)b->flags >> 22) & 3]);
    if (b->flags & 0x10000) {
        gSPSetGeometryMode(g++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(g++, G_LIGHTING);
    }
    fmt = b->spr->unk18;
    rm2 = 0x110000;
    if (b->flags & 0x08000000) {
        rm2 = 0xC8004000;
    }
    if (b->flags & 0x1000) {
        rm1 = 0x4850;
        if (fmt & 0x8000) {
            rm2 = 0x100000;
            if (b->a == 0x100) {
                gDPSetCombine(g++, 0xFFFE04, 0xFFFDF3F8);
            } else {
                gDPSetCombine(g++, 0xFF9604, 0xFF11FFFF);
            }
        } else if (b->a == 0x100) {
            rm1 = 0x3038;
            if (b->flags & 0x02000000) {
                gDPSetCombine(g++, 0x60FE04, 0x3FFDF3F8);
            } else {
                gDPSetCombine(g++, 0x127E04, 0xFFFFF3F8);
            }
        } else {
            rm1 = 0x4850;
            rm2 = 0x100000;
            if (b->flags & 0x02000000) {
                gDPSetCombine(g++, 0x609604, 0x3F11FFFF);
            } else {
                gDPSetCombine(g++, 0x121604, 0xFF13FFFF);
            }
        }
    } else {
        rm1 = 0x2030;
        if (b->flags & 0x02000000) {
            gDPSetCombine(g++, 0x6097FF, 0x3FFDFE38);
        } else {
            gDPSetCombine(g++, 0x1217FF, 0xFFFFFE38);
        }
    }
    switch (((s32)b->flags >> 10) & 3) {
        case 0:
            rm1 |= 0x200;
            break;
        case 2:
            rm1 |= 0x40;
            if (b->flags & 0x1000) {
                rm1 |= 0x180;
            }
        case 1:
            rm1 |= 8;
            break;
    }
    if (b->flags & 0x2000) {
        rm1 |= 0xC00;
    }
    if (b->flags & 0x08000000) {
        gSPSetGeometryMode(g++, G_FOG);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, rm1 | rm2 | 0xC8000000);
    } else {
        gSPClearGeometryMode(g++, G_FOG);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, rm1 | rm2 | 0x0C080000);
    }
    gDPSetPrimColor(g++, 0, 0, b->r, b->g, b->b, b->a);
    vtx = D_8010F348_fowl_play;
    mtx = (Mtx*)(vtx + b->rows * 2 * sizeof(Vtx));
    dl = (u8*)mtx + sizeof(Mtx);
    D_8010F348_fowl_play = dl + b->cmds * sizeof(Gfx);
    guMtxIdentF(ofs);
    if (b->flags & 0x04000000) {
        ofs[3][0] = -b->ofs.x;
        ofs[3][1] = b->ofs.y;
    } else {
        ofs[3][0] = -(s32)(u16)cel->unk08;
        ofs[3][1] = (u16)cel->unk0A;
    }
    ofs[3][2] = b->ofs.z;
    func_8002367C_main(m, view);
    func_80017C10_main((Mtx*)m, b->pos.x, b->pos.y, b->pos.z);
    switch (b->unk1A) {
        case 0:
            func_80017D24_main(m, b->rot.x, b->rot.y, b->rot.z);
            func_80017CD0_main(m, b->scale.x, b->scale.y, b->scale.z);
            break;
        case 2:
            func_80017D24_main(m, b->rot.x, b->rot.y + rot->y, b->rot.z);
            func_80017CD0_main(m, b->scale.x, b->scale.y, b->scale.z);
            break;
        case 7:
            func_80017D24_main(m, b->rot.x, b->rot.y, b->rot.z);
            func_80017CD0_main(m, b->scale.x, b->scale.y, b->scale.z);
            sc[0][0] = b->scale.x;
            sc[1][1] = b->scale.y;
            sc[2][2] = b->scale.z;
            sc[3][3] = 1.0f;
            sc[0][1] = sc[0][2] = sc[0][3] = sc[1][0] = sc[1][2] = sc[1][3] = sc[2][0] = sc[2][1] = sc[2][3] =
                sc[3][0] = sc[3][1] = sc[3][2] = 0.0f;
            func_80018544_main(m, inv);
            func_80018044_main(sc, inv, m);
            break;
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
            break;
    }
    guMtxCatF(ofs, m, m);
    guMtxF2L(m, mtx);
    gDPPipeSync(g++);
    gSPMatrix(g++, osVirtualToPhysical(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(g++);
    gSPSegment(g++, 0x0C, cel->unk00);
    gSPSegment(g++, 0x0E, vtx);
    gDPPipeSync(g++);
    memcpy(vtx, b->vtx, b->rows * 2 * sizeof(Vtx));
    memcpy(dl, b->gfx, b->cmds * sizeof(Gfx));
    if (!(b->flags & 0x8000)) {
        gSPDisplayList(g++, dl);
    }
    return g;
}

void func_8010E544_fowl_play(void) {
    PgBoard* b;
    s32 n;
    s32 i;

    for (i = 0; i < D_8010F350_fowl_play; i++) {
        b = &D_8010F32C_fowl_play[i];
        if (b->func != NULL) {
            b->func(b);
        }
        if (b->spr == NULL) {
            continue;
        }
        if (b->flags & 0x8000) {
            continue;
        }
        if (b->flags & 0x10000000) {
            continue;
        }
        {
            n = b->spr->unk10;
            b->timer += b->speed;
            while (b->timer >= 1.0) {
                b->frame++;
                b->timer -= 1.0f;
                if (b->frame >= n) {
                    if (b->flags & 0x20000000) {
                        b->flags |= 0x8000;
                        b->frame--;
                        b->timer += 1.0f;
                        if (b->flags & 0x40000000) {
                            func_8010D2F0_fowl_play(i);
                        }
                        break;
                    } else if (!(b->flags & 0x40000000)) {
                        b->frame = 0;
                    } else {
                        b->frame--;
                        break;
                    }
                }
            }
        }
    }
}

void func_8010E704_fowl_play(void) {
    s32 i;

    for (i = 0; i < D_8010F350_fowl_play; i++) {
        func_8010D2F0_fowl_play(i);
    }
    for (i = 0; i < 6; i++) {
        if (D_8010F330_fowl_play[i] != NULL) {
            HuMemFree(D_8010F330_fowl_play[i]);
        }
    }
    HuMemFree(D_8010F32C_fowl_play);
}
