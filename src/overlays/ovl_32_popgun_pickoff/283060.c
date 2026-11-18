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

// pg A: Popgun Pick-Off

typedef func_800E1BA8_minigame_ObjData MgWork;
typedef f32 Matrix4f[4][4];

typedef struct PgPair {
    s16 unk0;
    s16 unk2;
} PgPair;

/* A pop-up target (D_8010CC28_popgun_pickoff[9]). */
typedef struct PgTarget {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rot; /* flip angle: -90 down, 0 up */
    /* 0x10 */ s16 sx; /* screen position */
    /* 0x12 */ s16 sy;
    /* 0x14 */ s16 grp; /* "-10" sprite group, -1 none */
    /* 0x16 */ u8 hits;
    /* 0x17 */ u8 board; /* billboard id */
    /* 0x18 */ char unk18[2];
    /* 0x1A */ u8 kind; /* 0 target, 1 bomb */
    /* 0x1B */ u8 state;
    /* 0x1C */ u8 timer;
    /* 0x1D */ char unk1D[3];
} PgTarget; /* size 0x20 */

/* A cork shot (D_8010CD50_popgun_pickoff[0x80]). */
typedef struct PgShot {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 vx;
    /* 0x10 */ f32 vy;
    /* 0x14 */ f32 vz;
    /* 0x18 */ u8 target;
    /* 0x19 */ u8 state; /* 0 free */
    /* 0x1A */ u8 slot; /* shooter */
    /* 0x1B */ u8 timer;
    /* 0x1C */ u8 board; /* billboard id */
    /* 0x1D */ char unk1D[3];
} PgShot; /* size 0x20 */

/* A textured quad strip drawn with its own display list (D_8010DDD8_popgun_pickoff[D_8010DDF0_popgun_pickoff]). */
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
typedef struct PgPlayer {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk0C[8];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ s32 file; /* character model file | 0x2F */
    /* 0x28 */ u8 player;
    /* 0x29 */ u8 chr;
    /* 0x2A */ u8 slot; /* 0 left, 1 right */
    /* 0x2B */ u8 difficulty;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ s8 cpu;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 grp; /* cursor sprite group */
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ s16 cpuDir; /* CPU: target hole */
    /* 0x36 */ char unk36[0x1E];
} PgPlayer; /* size 0x54 */

#define PG_PLAYER(i) ((PgPlayer*)((MgWork*)D_800EC598_minigame[i]->data)->unk158)

s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]); /* matrix copy */
void func_8007DFE0_main(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
void func_80016B00_main(s16 model, s16 frame, char* name, Matrix4f mtx);
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
void func_8001EF6C_main(s16, s16, char*);
s32 func_800E4A90_minigame(omObjData* obj);
void func_800E5798_minigame(omObjData* obj, s32 arg1);
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
extern s32 D_800EBEB0_minigame[];
extern HuSprite_Unk84_Struct* D_800C9530_main[];

void func_80105AFC_popgun_pickoff(omObjData* obj);
void func_80105BF8_popgun_pickoff(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out);
void func_80105C78_popgun_pickoff(f32 (*src)[4], f32 (*dst)[4]);
void func_80105E68_popgun_pickoff(Vec* pos, Vec* out);
void func_80105F74_popgun_pickoff(f32 x, f32 y, f32 z, Vec* out);
void func_80106068_popgun_pickoff(void);
void func_801060E8_popgun_pickoff(omObjData* obj);
void func_80107A54_popgun_pickoff(void);
void func_80107B20_popgun_pickoff(omObjData* obj);
void func_801080DC_popgun_pickoff(omObjData* obj, u32 file0, s32 file1, s32 player, u16 attr);
void func_80108398_popgun_pickoff(omObjData* obj);
u16 func_8010880C_popgun_pickoff(omObjData* obj);
u8 func_80108A78_popgun_pickoff(omObjData* obj, s32 dir);
void func_80108FE4_popgun_pickoff(s16 model, char* name, s16 frame, Vec* out);
void func_80109260_popgun_pickoff(u16 n);
s16 func_80109718_popgun_pickoff(PgBoard* b);
s16 func_8010A024_popgun_pickoff(s16 tex, u32 flags);
void func_80106A44_popgun_pickoff(omObjData* obj);
void func_8010704C_popgun_pickoff(omObjData* obj);
u8 func_801068D0_popgun_pickoff(s16 x, s16 y);
s32 func_80108E1C_popgun_pickoff(void);
f32 func_80108EF4_popgun_pickoff(Vec* a, Vec* b);
void func_8010AC34_popgun_pickoff(s16 id, s16 frame);
void func_8010AEAC_popgun_pickoff(s16 id, u32 flags);
void func_8010AEF0_popgun_pickoff(s16 id, u32 flags);
void func_8010B120_popgun_pickoff(s16 id);
void func_8010BA44_popgun_pickoff(Gfx** gfx, s32 arg1, s32 arg2);
void func_8010C4EC_popgun_pickoff(void);
void func_8010ACB4_popgun_pickoff(s16 id, f32 x, f32 y, f32 z);
void func_8010AD54_popgun_pickoff(s16 id, f32 x, f32 y, f32 z);
void func_8010AE0C_popgun_pickoff(s16 id, f32 x, f32 y, f32 z);
void func_8010AE5C_popgun_pickoff(s16 id, f32 x, f32 y, f32 z);
void func_8010AF78_popgun_pickoff(s16 id, s8 arg1);
void func_8010B0D4_popgun_pickoff(s16 id, s8 r, s8 g, s8 b, u16 a);
s16 func_80109108_popgun_pickoff(s32 id);
s16 func_80109150_popgun_pickoff(s16 tex, s16 n);
HuSprite_Unk84_Unk00_Struct* func_80109218_popgun_pickoff(s16 tex, s16 frame);

extern s16 D_8010CBD0_popgun_pickoff[16]; /* textures */
extern s16 D_8010CBF0_popgun_pickoff[8]; /* sprite groups */
extern s16 D_8010CC00_popgun_pickoff[16]; /* sprite slots in use */
extern s16 D_8010CC20_popgun_pickoff;
extern PgPair D_8010CC22_popgun_pickoff;
extern PgTarget D_8010CC28_popgun_pickoff[9];
extern PgShot D_8010CD50_popgun_pickoff[0x80];
extern f32 D_8010DD50_popgun_pickoff[4][4]; /* world to view (D_8010DD88 is its [3][2]) */
extern f32 D_8010DD88_popgun_pickoff; /* D_8010DD50[3][2] */
extern f32 D_8010DD90_popgun_pickoff[4][4]; /* view to world */
extern f32 D_8010DDD0_popgun_pickoff; /* tan(fov / 2) */
extern PgBoard* D_8010DDD8_popgun_pickoff;
extern s32 D_8010DDF0_popgun_pickoff; /* billboard count */
extern void* D_8010DDDC_popgun_pickoff[3]; /* per-frame buffers */
extern u8* D_8010DDE8_popgun_pickoff; /* this frame's buffer */
extern s32 D_8010DDEC_popgun_pickoff; /* its size */
extern s32 D_8010C890_popgun_pickoff; /* buffer index */
extern s32 D_8010C5F8_popgun_pickoff[4]; /* texel shift by size */
extern s16 D_8010C608_popgun_pickoff[]; /* LoadBlock row limits by line width */
extern s16 D_8010C740_popgun_pickoff[];
extern s16 D_8010C878_popgun_pickoff[4]; /* colour dither by flags >> 4 */
extern s16 D_8010C880_popgun_pickoff[4]; /* texture filter by flags >> 2 */
extern s16 D_8010C888_popgun_pickoff[4]; /* alpha compare by flags >> 22 */
void func_8008A120_main(Matrix4f m, f32 a);
void func_80018544_main(Matrix4f src, Matrix4f dst);
void func_801093A8_popgun_pickoff(Gfx** gfx, HuSprite_Unk84_Unk00_Struct* cel, u8 fmt, u8 siz, u16 rows, u16 uls,
                                  u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt, s32 mode);
extern PgBoard D_8010DE00_popgun_pickoff; /* opaque draw list head */
extern PgBoard D_8010DE68_popgun_pickoff; /* translucent draw list head */
extern s8 HmfPauseF;
void func_80079480_main(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp,
                        f32 zUp); /* guLookAtF */
void func_80108F5C_popgun_pickoff(Vec* dir, f32* angles);
void func_8010B64C_popgun_pickoff(void);
void func_8010C32C_popgun_pickoff(void);
Gfx* func_8010BC6C_popgun_pickoff(Gfx* g, PgBoard* b, f32 (*view)[4], Vec* rot);
void func_8010B7A0_popgun_pickoff(HuCamera* cam, f32 (*view)[4]);
void func_800341D0_main(Gfx** gfx, s32 timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult,
                        s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                        s32 shiftt);
void func_80034998_main(Gfx** gfx, s32 timg, s32 fmt, u32 width, s32 height, s32 uls, s32 ult, s32 lrs,
                        s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
extern u32 D_8010C5F4_popgun_pickoff; /* random seed */
extern s32 D_8010C590_popgun_pickoff; /* timer */
extern u16 D_8010C594_popgun_pickoff; /* game timer, frames */
extern s32 D_8010C598_popgun_pickoff; /* winner slot, -1 draw */
extern s32 D_8010C59C_popgun_pickoff; /* end camera timer */
extern s16 D_8010C5A0_popgun_pickoff; /* frames since the wipe */
extern s16 D_8010C5A2_popgun_pickoff; /* spawn timer */
extern s16 D_8010C5A4_popgun_pickoff; /* spawn waves */
extern u8 D_8010DDD4_popgun_pickoff;
extern u8 D_8010C5B0_popgun_pickoff; /* players set up */
extern s16 D_8010C5B8_popgun_pickoff[][3]; /* start positions */
extern f32 D_8010C5D0_popgun_pickoff[]; /* start headings */
extern s16 D_8010C5E0_popgun_pickoff[]; /* aim pitch by row */
extern s16 D_8010C5E8_popgun_pickoff[2][3]; /* aim heading by slot and column */

void func_801059A0_popgun_pickoff(void) {
    omObjData* obj;
    u8 cam;

    Hu3DAnimInit(1);
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
    func_80105AFC_popgun_pickoff(obj);
    func_80106068_popgun_pickoff();
    func_80109260_popgun_pickoff(0x80);
    func_80107A54_popgun_pickoff();
    func_8001F38C_main(0xB4, 0xB4, 0xB4);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105AFC_popgun_pickoff(omObjData* obj) {
    HuCamera* cam;
    f32 s;

    CZoom = 500.0f;
    CRot.x = 5.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 250.0f;
    Center.z = 0.0f;
    omOutView(obj);
    cam = gCameraList;
    s = sindf(cam->fov[0] / 2.0);
    D_8010DDD0_popgun_pickoff = s / cosdf(cam->fov[0] / 2.0);
    guMtxL2F(D_8010DD50_popgun_pickoff, &cam->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010DD90_popgun_pickoff, &cam->mtxs[0].lookAtMtx);
    func_80105C78_popgun_pickoff(D_8010DD90_popgun_pickoff, D_8010DD90_popgun_pickoff);
}

void func_80105BF8_popgun_pickoff(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out) {
    out[0] = x * m[0][0] + y * m[1][0] + z * m[2][0];
    out[1] = x * m[0][1] + y * m[1][1] + z * m[2][1];
    out[2] = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

void func_80105C78_popgun_pickoff(f32 (*src)[4], f32 (*dst)[4]) {
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
        func_80105BF8_popgun_pickoff(dst, -m[3][0], -m[3][1], -m[3][2], dst[3]);
    }
}

void func_80105E68_popgun_pickoff(Vec* pos, Vec* out) {
    f32 m[4][4];
    f32 t;
    f32 w;

    func_8007DFE0_main(m, pos->x, pos->y, pos->z);
    guMtxCatF(m, D_8010DD50_popgun_pickoff, m);
    t = m[3][2] * D_8010DDD0_popgun_pickoff;
    w = fabsf(t);
    if (w != 0.0) {
        out->x = m[3][0] * 160.0f / w / 1.3333333333333333;
        out->y = -m[3][1] * 120.0f / w;
    }
    out->x += 160.0;
    out->y += 120.0;
    out->z = w;
}





void func_80105F74_popgun_pickoff(f32 x, f32 y, f32 z, Vec* out) {
    f32 m[4][4];
    f32 d;
    f32 w;

    d = z + D_8010DD88_popgun_pickoff;
    w = fabsf(d * D_8010DDD0_popgun_pickoff);
    x -= 160.0;
    y -= 120.0;
    func_8007DFE0_main(m, 2.0f * x * w * 1.3333333333333333 / 320.0, -(2.0f * y * w / 240.0f), d);
    guMtxCatF(m, D_8010DD90_popgun_pickoff, m);
    out->x = m[3][0];
    out->y = m[3][1];
    out->z = m[3][2];
}





void func_80106068_popgun_pickoff(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 10, 0, -1, func_801060E8_popgun_pickoff);
    D_8010CC20_popgun_pickoff = 0;
    D_8010CC22_popgun_pickoff.unk0 = D_8010CC22_popgun_pickoff.unk2 = 0;
}





#ifdef NON_MATCHING
void func_801060E8_popgun_pickoff(omObjData* obj) {
    f32 pts[9][2] = {
        { 115.0f, 93.0f }, { 160.0f, 93.0f }, { 204.0f, 93.0f }, { 115.0f, 128.0f }, { 160.0f, 128.0f },
        { 204.5f, 128.0f }, { 114.0f, 163.0f }, { 159.5f, 163.0f }, { 205.0f, 163.0f },
    };
    u16 chrTex[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
    Vec pos;
    Vec scr;
    HuSprite_Unk84_Unk00_Struct* spr;
    PgTarget* t;
    s32 i;

    D_8010CBD0_popgun_pickoff[0] = func_80109108_popgun_pickoff(0x530000);
    D_8010CBF0_popgun_pickoff[0] = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[0], 1);
    func_80054904_main(D_8010CBF0_popgun_pickoff[0], 0, 160, 120);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[0], 0, 0x4000);
    D_8010CBD0_popgun_pickoff[1] = func_80109108_popgun_pickoff(0x530001);
    spr = func_80109218_popgun_pickoff(D_8010CBD0_popgun_pickoff[1], 0);
    D_8010CBF0_popgun_pickoff[1] = func_8010A024_popgun_pickoff(D_8010CBD0_popgun_pickoff[1], 0x1808);
    func_8010AD54_popgun_pickoff(D_8010CBF0_popgun_pickoff[1], 0.0f, -70.0f, -400.0f);
    func_8010AE0C_popgun_pickoff(D_8010CBF0_popgun_pickoff[1], 3.0f, 3.0f, 1.0f);
    func_8010ACB4_popgun_pickoff(D_8010CBF0_popgun_pickoff[1], spr->unk04 * 0.5, spr->unk06, 0.0f);
    func_8010AF78_popgun_pickoff(D_8010CBF0_popgun_pickoff[1], 0);
    D_8010CBD0_popgun_pickoff[4] = func_80109108_popgun_pickoff(0x530004);
    D_8010CBD0_popgun_pickoff[5] = func_80109108_popgun_pickoff(0x530005);
    for (i = 0; i < 9; i++) {
        t = &D_8010CC28_popgun_pickoff[i];
        pos.x = t->x = (pts[i][0] - spr->unk04 * 0.5) * 3.0;
        pos.y = t->y = (spr->unk06 - pts[i][1]) * 3.0 + -70.0;
        pos.z = t->z = -400.0f;
        func_80105E68_popgun_pickoff(&pos, &scr);
        t->sx = scr.x;
        t->sy = scr.y;
        t->rot = -90.0f;
        t->grp = -1;
        t->hits = 0;
        t->state = 0;
        t->board = func_8010A024_popgun_pickoff(D_8010CBD0_popgun_pickoff[4], 0x12009808);
        func_8010ACB4_popgun_pickoff(t->board, 16.0f, 32.0f, 0.0f);
        func_8010AD54_popgun_pickoff(t->board, t->x, t->y - 42.0, t->z - 10.0);
        func_8010AE0C_popgun_pickoff(t->board, 3.0f, 3.0f, 1.0f);
        func_8010AE5C_popgun_pickoff(t->board, 90.0f, 0.0f, 0.0f);
        func_8010AF78_popgun_pickoff(t->board, 0);
        func_8010B0D4_popgun_pickoff(t->board, 0, 0, 0, 0x100);
    }
    for (i = 0; i < 0x80; i++) {
        D_8010CD50_popgun_pickoff[i].state = 0;
    }
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x530009, 0x2D9);
            obj->trans.x = D_8010CC28_popgun_pickoff[i].x;
            obj->trans.y = D_8010CC28_popgun_pickoff[i].y;
            obj->trans.z = D_8010CC28_popgun_pickoff[i].z + 10.0;
            obj->scale.z = 0.66f;
            obj->scale.x = 0.66f;
            obj->scale.y = 0.63f;
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelPosSet(obj->model[i], D_8010CC28_popgun_pickoff[i].x, D_8010CC28_popgun_pickoff[i].y,
                            D_8010CC28_popgun_pickoff[i].z + 10.0);
        }
        Hu3DModelScaleSet(obj->model[i], obj->scale.x, obj->scale.y, obj->scale.z);
        func_8001C92C_main(obj->model[i], 0.0f);
    }
    D_8010CBD0_popgun_pickoff[6] = func_80109108_popgun_pickoff(0x530007);
    D_8010CBF0_popgun_pickoff[2] = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[6], 2);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[2], 0, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[2], 1, 0x1000);
    func_80055484_main(D_8010CBF0_popgun_pickoff[2], 0, 0, 0, 0, 0xC2);
    func_80055484_main(D_8010CBF0_popgun_pickoff[2], 1, 0, 0, 0, 0xC2);
    func_80054904_main(D_8010CBF0_popgun_pickoff[2], 0, 60, 48);
    func_80054904_main(D_8010CBF0_popgun_pickoff[2], 1, 260, 48);
    D_8010CBD0_popgun_pickoff[11] = func_80109108_popgun_pickoff(
        chrTex[((PgPlayer*)((MgWork*)D_800EC598_minigame[0]->data)->unk158)->chr] | 0x210000);
    D_8010CBD0_popgun_pickoff[12] = func_80109108_popgun_pickoff(
        chrTex[((PgPlayer*)((MgWork*)D_800EC598_minigame[1]->data)->unk158)->chr] | 0x210000);
    D_8010CBF0_popgun_pickoff[6] = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[11], 2);
    func_80055024_main(D_8010CBF0_popgun_pickoff[6], 1, D_8010CBD0_popgun_pickoff[12], 0);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[6], 0, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[6], 1, 0x1000);
    func_80054904_main(D_8010CBF0_popgun_pickoff[6], 0, 36, 48);
    func_80054904_main(D_8010CBF0_popgun_pickoff[6], 1, 236, 48);
    D_8010CBD0_popgun_pickoff[8] = func_80109108_popgun_pickoff(0x2D);
    D_8010CBD0_popgun_pickoff[9] = func_80109108_popgun_pickoff(0x2F);
    D_8010CBF0_popgun_pickoff[4] = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[8], 6);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 0, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 1, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 2, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 3, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 4, 0x1000);
    HuSprAttrSet(D_8010CBF0_popgun_pickoff[4], 5, 0x1000);
    func_80054904_main(D_8010CBF0_popgun_pickoff[4], 0, 80, 48);
    func_80054904_main(D_8010CBF0_popgun_pickoff[4], 1, 67, 48);
    func_80054904_main(D_8010CBF0_popgun_pickoff[4], 2, 53, 48);
    func_80054904_main(D_8010CBF0_popgun_pickoff[4], 3, 280, 48);
    func_80054904_main(D_8010CBF0_popgun_pickoff[4], 4, 267, 48);
    func_80054904_main(D_8010CBF0_popgun_pickoff[4], 5, 253, 48);
    obj->func = func_80106A44_popgun_pickoff;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010C8E0_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010C928_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_801060E8_popgun_pickoff);
#endif

u8 func_801068D0_popgun_pickoff(s16 x, s16 y) {
    u8 grp = HuSprGrpCreate(3, 2);

    func_80055024_main(grp, 0, D_8010CBD0_popgun_pickoff[8], 0);
    func_80055024_main(grp, 1, D_8010CBD0_popgun_pickoff[8], 0);
    func_80055024_main(grp, 2, D_8010CBD0_popgun_pickoff[9], 0);
    HuSprAttrSet(grp, 0, 0x1000);
    HuSprAttrSet(grp, 1, 0x1000);
    HuSprAttrSet(grp, 2, 0x1000);
    func_800550F4_main(grp, 0, 0);
    func_800550F4_main(grp, 1, 0);
    func_800550F4_main(grp, 2, 0);
    func_80054904_main(grp, 0, x, y);
    func_80054904_main(grp, 1, 12, 0);
    func_80054904_main(grp, 2, -12, 0);
    func_80054FF8_main(grp, 0, 1);
    func_80054FF8_main(grp, 1, 0);
    func_80054FF8_main(grp, 2, 4);
    return grp;
}





void func_80106A44_popgun_pickoff(omObjData* obj) {
    s32 i;
    s16 m;

    switch (D_8010CC20_popgun_pickoff) {
    case 0:
        func_8001AC8C_main(0xC0, func_8010BA44_popgun_pickoff, 2);
        GMesCreate(6);
        D_8010C594_popgun_pickoff = 900;
        D_8010CC20_popgun_pickoff++;
    case 1:
        if (WipeStatGet() == 0) {
            if (++D_8010C5A0_popgun_pickoff == 1) {
                HuAudSeqPlay(0x36);
            }
        }
        if (GMesStatGet() == 0) {
            D_8010CC20_popgun_pickoff++;
            GMesCreate(0x1A, (D_8010C594_popgun_pickoff + 29) / 30, 160, 32);
            HuAudFXPlay(0xE);
        }
        break;
    case 2:
        D_8010C594_popgun_pickoff--;
        func_8003F578_main((D_8010C594_popgun_pickoff + 29) / 30);
        if (D_8010C594_popgun_pickoff == 0) {
            D_8010CC20_popgun_pickoff = 3;
            func_8003F5C0_main();
            GMesCreate(0x11);
            HuAudSeqFadeOut(120);
        }
        break;
    case 3:
        if (D_8010C59C_popgun_pickoff != 0) {
            D_8010C59C_popgun_pickoff--;
            Center.y -= 2.9;
            /* retail reads the low half of the s32 D_8010C59C (big-endian) */
            func_80054904_main(D_8010CBF0_popgun_pickoff[0], 0, 160, ((s16*)&D_8010C59C_popgun_pickoff)[1] + 95);
        } else if (D_8010DDD4_popgun_pickoff == 0) {
            if (D_8010CC22_popgun_pickoff.unk0 > D_8010CC22_popgun_pickoff.unk2) {
                D_8010C598_popgun_pickoff = 0;
                PG_PLAYER(0)->unk2C = 1;
                PG_PLAYER(1)->unk2C = 0;
            } else if (D_8010CC22_popgun_pickoff.unk0 < D_8010CC22_popgun_pickoff.unk2) {
                D_8010C598_popgun_pickoff = 1;
                PG_PLAYER(0)->unk2C = 0;
                PG_PLAYER(1)->unk2C = 1;
            } else {
                D_8010C598_popgun_pickoff = -1;
                PG_PLAYER(0)->unk2C = PG_PLAYER(1)->unk2C = 0;
            }
            D_8010C590_popgun_pickoff = 15;
            D_8010CC20_popgun_pickoff++;
        }
        break;
    case 4:
        if (GMesStatGet() == 0) {
            if (--D_8010C590_popgun_pickoff == 0) {
                if (D_8010C598_popgun_pickoff == -1) {
                    GMesCreate(0x20);
                    m = 0x6C;
                } else {
                    GMesCreate(0x16, PG_PLAYER(D_8010C598_popgun_pickoff)->chr);
                    m = 0x67;
                }
                HuAudSeqPlay(m);
                D_8010C590_popgun_pickoff = 15;
                D_8010CC20_popgun_pickoff++;
            }
        }
        break;
    case 5:
        if (GMesStatGet() == 0) {
            if (--D_8010C590_popgun_pickoff == 0) {
                D_8010CC20_popgun_pickoff++;
            }
        }
        break;
    case 6:
        if (D_8010C590_popgun_pickoff != 0) {
            if (--D_8010C590_popgun_pickoff == 0) {
                D_8010CC20_popgun_pickoff++;
            }
        } else {
            D_8010C590_popgun_pickoff = 16;
            /* retail reads the low half of the s32 D_8010C590 (big-endian) as the fade length */
            WipeCreateOut(0, ((s16*)&D_8010C590_popgun_pickoff)[1]);
            HuAudSeqFadeOut(((s16*)&D_8010C590_popgun_pickoff)[1]);
            func_8004AB0C_main(((s16*)&D_8010C590_popgun_pickoff)[1]);
        }
        break;
    case 7:
        func_8004A950_main();
        omOvlReturnEx(1);
        func_8010C4EC_popgun_pickoff();
        break;
    }
    func_8010704C_popgun_pickoff(obj);
    for (i = 0; i < 2; i++) {
        HuSprAttrReset(D_8010CBF0_popgun_pickoff[4], i * 3 + 1, 0x8000);
        HuSprAttrReset(D_8010CBF0_popgun_pickoff[4], i * 3 + 2, 0x8000);
        func_80054FF8_main(D_8010CBF0_popgun_pickoff[4], i * 3, (&D_8010CC22_popgun_pickoff.unk0)[i] % 10);
        func_80054FF8_main(D_8010CBF0_popgun_pickoff[4], i * 3 + 1, (&D_8010CC22_popgun_pickoff.unk0)[i] / 10 % 10);
        func_80054FF8_main(D_8010CBF0_popgun_pickoff[4], i * 3 + 2, (&D_8010CC22_popgun_pickoff.unk0)[i] / 100);
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010CC20_popgun_pickoff = 6;
    }
}

void func_8010704C_popgun_pickoff(omObjData* obj) {
    PgShot* s;
    PgTarget* t;
    s16 b;
    f32 sc;
    s32 i;
    s32 n;
    s32 k;

    D_8010DDD4_popgun_pickoff = 0;
    for (i = 0; i < 0x80; i++) {
        s = &D_8010CD50_popgun_pickoff[i];
        switch (s->state) {
        case 0:
            continue;
        case 1:
            t = &D_8010CC28_popgun_pickoff[s->target];
            if (func_80108EF4_popgun_pickoff((Vec*)t, (Vec*)s) <= 48.0) {
                s->x = t->x;
                s->y = t->y;
                s->z = t->z + 40.0;
                s->vx = s->vx * 0.2 + (f32)(func_80108E1C_popgun_pickoff() - 0x8000) * 3.0517578125e-05 * (s->vx * 0.2);
                s->vy = (f32)func_80108E1C_popgun_pickoff() * 1.52587890625e-05 * 6.0 + 15.0;
                s->vz = -s->vz * 0.1 - (f32)func_80108E1C_popgun_pickoff() * 1.52587890625e-05 * (s->vz * 0.05);
                s->timer = 120;
                s->state++;
                if (t->state == 2) {
                    t->rot = -50.0f;
                    func_8010AC34_popgun_pickoff(t->board, t->kind * 2 + 1);
                    if (t->kind == 0) {
                        func_8010B0D4_popgun_pickoff(t->board, -1, -1, -1, 0x100);
                        if (t->hits != 0) {
                            t->hits--;
                        }
                        (&D_8010CC22_popgun_pickoff.unk0)[s->slot]++;
                        b = func_8010A024_popgun_pickoff(D_8010CBD0_popgun_pickoff[10], 0x60001808);
                        func_8010AD54_popgun_pickoff(b, t->x, t->y, t->z + 20.0f);
                        func_8010B0D4_popgun_pickoff(t->board, -1, -1, -1, 0xC6);
                        func_8010AE0C_popgun_pickoff(b, 2.0f, 2.0f, 1.0f);
                        HuAudFXPlay(0x497);
                    } else {
                        if ((&D_8010CC22_popgun_pickoff.unk0)[s->slot] > 10) {
                            (&D_8010CC22_popgun_pickoff.unk0)[s->slot] -= 10;
                        } else {
                            (&D_8010CC22_popgun_pickoff.unk0)[s->slot] = 0;
                        }
                        t->grp = func_801068D0_popgun_pickoff(t->sx, t->sy);
                        func_8010B0D4_popgun_pickoff(t->board, -1, 0, 0, 0x100);
                        HuAudFXPlay(0x498);
                        omVibrate(PG_PLAYER(s->slot)->player, 10, 0, 10);
                        t->hits = 0;
                        t->state++;
                    }
                }
            }
            D_8010DDD4_popgun_pickoff++;
            break;
        case 2:
            if (--s->timer == 0) {
                s->state++;
            }
            break;
        case 3:
            s->state = 0;
            func_8010B120_popgun_pickoff(s->board);
            s->board = 0xFF;
            continue;
        }
        s->vy += -2.0f;
        s->x += s->vx;
        s->y += s->vy;
        s->z += s->vz;
        func_8010AD54_popgun_pickoff(s->board, s->x, s->y, s->z);
        sc = 1.5 - s->z / -400.0f;
        func_8010AE0C_popgun_pickoff(s->board, sc, sc, 1.0f);
    }
    for (i = 0; i < 9; i++) {
        t = &D_8010CC28_popgun_pickoff[i];
        switch (t->state) {
        case 0:
            break;
        case 1:
            func_8010AEF0_popgun_pickoff(t->board, 0x8000);
            t->state++;
            break;
        case 2:
            t->rot += 15.0;
            if (t->rot > 0.0) {
                t->rot = 0.0f;
                func_8010AC34_popgun_pickoff(t->board, t->kind * 2);
            } else if (t->rot > -30.0) {
                func_8010B0D4_popgun_pickoff(t->board, 0, 0, 0, 0x100);
            }
            if ((--t->timer == 0) | (t->hits == 0)) {
                t->state++;
            }
            break;
        case 3:
            func_8010B0D4_popgun_pickoff(t->board, 0, 0, 0, 0x100);
            if (t->rot <= -90.0) {
                func_8010AEAC_popgun_pickoff(t->board, 0x8000);
            } else {
                t->rot -= 10.0;
            }
            if (t->timer-- != 0) {
                break;
            }
            func_8001C6A8_main(obj->model[i], 4.2f);
            func_8001C92C_main(obj->model[i], -0.2f);
            t->timer = 9;
            t->state++;
        case 4:
            if (t->rot <= -90.0) {
                func_8010AEAC_popgun_pickoff(t->board, 0x8000);
            } else {
                t->rot -= 10.0;
            }
            if (--t->timer == 0) {
                func_8001C92C_main(obj->model[i], 0.0f);
                func_8001C6A8_main(obj->model[i], 0.0f);
                t->state = 0;
            }
            break;
        }
        if (t->grp != -1) {
            if (t->rot > -90.0) {
                sc = 1.0 - t->rot * 0.005;
                HuSprScaleSet(t->grp, 0, sc, sc);
                HuSprScaleSet(t->grp, 1, sc, sc);
                HuSprScaleSet(t->grp, 2, sc, sc);
            } else if (t->rot > -180.0) {
                t->rot -= 15.0;
                sc = (t->rot + 180.0) * 0.005 + 1.0;
                HuSprScaleSet(t->grp, 0, sc, sc);
                HuSprScaleSet(t->grp, 1, sc, sc);
                HuSprScaleSet(t->grp, 2, sc, sc);
            } else {
                HuSprGrpKill(t->grp);
                t->rot = 0.0f;
                t->grp = -1;
            }
        }
        func_8010AE5C_popgun_pickoff(t->board, t->rot, 0.0f, 0.0f);
    }
    if (D_8010CC20_popgun_pickoff == 2) {
        if (--D_8010C5A2_popgun_pickoff == 0) {
            D_8010C5A2_popgun_pickoff = 120;
            D_8010C5A4_popgun_pickoff++;
            n = D_8010C5A4_popgun_pickoff / 2 + 2;
            if (n >= 9) {
                n = 9;
            }
            for (i = 0; i < n;) {
                k = (f32)func_80108E1C_popgun_pickoff() * 1.52587890625e-05 * 8.0;
                t = &D_8010CC28_popgun_pickoff[k];
                if (t->state == 0) {
                    t->timer = (s32)((f32)func_80108E1C_popgun_pickoff() * 1.52587890625e-05 * 20.0) + 60;
                    t->hits = 10;
                    t->state = 1;
                    t->rot = -90.0f;
                    t->grp = -1;
                    if (i != 0) {
                        t->kind = func_80108E1C_popgun_pickoff() & 1;
                    } else {
                        t->kind = 0;
                    }
                    func_8010AC34_popgun_pickoff(t->board, t->kind * 2);
                    i++;
                    func_8001C92C_main(obj->model[k], 1.0f);
                    HuAudFXPlay(0x499);
                }
            }
        }
    }
}

void func_80107A54_popgun_pickoff(void) {
    s32 i;

    func_800E18D8_minigame();
    D_8010CBD0_popgun_pickoff[2] = func_80109108_popgun_pickoff(0x530002);
    D_8010CBD0_popgun_pickoff[3] = func_80109108_popgun_pickoff(0x530003);
    D_8010CBD0_popgun_pickoff[10] = func_80109108_popgun_pickoff(0x530006);
    D_800EC280_minigame = 0;
    for (i = 0; i < 2; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 11, 50, -1, func_80107B20_popgun_pickoff);
    }
}

void func_80107B20_popgun_pickoff(omObjData* obj) {
    s16 colors[8][3] = {
        { 0xFF, 0x00, 0x00 }, { 0x00, 0x40, 0xFF }, { 0xFF, 0x80, 0xFF }, { 0x00, 0xFF, 0x00 },
        { 0x80, 0x00, 0xFF }, { 0xFF, 0x80, 0x80 }, { 0x80, 0x80, 0x80 }, { 0xFF, 0xFF, 0x00 },
    };
    u8 attrs[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 mots[3][8] = {
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    u8 player;
    s8 chr;
    u32 file0;
    s32 file1;
    MgWork* work;
    PgPlayer* p;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8010C5B0_popgun_pickoff == GwPlayer[i].group) {
            break;
        }
    }
    player = i;
    chr = GwPlayer[player].chr;
    file0 = D_800A178C_main[chr][0];
    file1 = D_800A178C_main[chr][2];
    func_800E19F0_minigame(1);
    func_801080DC_popgun_pickoff(obj, file0, file1, player, 0x2C9);
    work = obj->data;
    obj->trans.x = D_8010C5B8_popgun_pickoff[D_8010C5B0_popgun_pickoff][0];
    obj->trans.y = D_8010C5B8_popgun_pickoff[D_8010C5B0_popgun_pickoff][1];
    obj->trans.z = D_8010C5B8_popgun_pickoff[D_8010C5B0_popgun_pickoff][2];
    obj->rot.y = D_8010C5D0_popgun_pickoff[D_8010C5B0_popgun_pickoff];
    work->unk3C = obj->rot.y + 180.0;
    obj->scale.x = obj->scale.y = obj->scale.z = work->unkAC;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 5.0, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    p = work->unk158;
    p->player = player;
    p->chr = chr;
    p->slot = D_8010C5B0_popgun_pickoff;
    p->unk18 = p->unk14 = work->unk3C;
    p->cpu = GwPlayer[player].stat & 1;
    p->unk2E = 0;
    p->difficulty = GwPlayer[player].cpu_difficulty;
    p->file = file0 | 0x2F;
    p->unk2C = 0;
    p->unk1C = 11.0f;
    p->pos.x = obj->trans.x;
    p->pos.y = obj->trans.y;
    p->pos.z = obj->trans.z;
    p->unk20 = 0;
    p->grp = func_80109150_popgun_pickoff(D_8010CBD0_popgun_pickoff[2], 1);
    HuSprAttrSet(p->grp, 0, 0x9008);
    func_80055484_main(p->grp, 0, colors[chr][0], colors[chr][1], colors[chr][2], 0x100);
    p->unk33 = func_80017790_main(obj->model[0], 2, attrs[chr], file0 | mots[2][chr]);
    p->unk31 = func_80017AD8_main(file0 | mots[0][chr]);
    p->unk32 = func_80017AD8_main(file0 | mots[1][chr]);
    func_8001C514_main(obj->model[0]);
    if (D_8010C5B0_popgun_pickoff == 0) {
        obj->model[2] = func_8000B108_main(0x530008, 0x2C9);
    } else {
        obj->model[2] = func_8000B108_main(0x530008, 0x2C9);
        func_800552DC_main(p->grp, 0, 45.0f);
    }
    func_8001EF6C_main(obj->model[2], obj->model[0], "item_hook");
    func_8001C258_main(obj->model[2], 0x4000, 0x4000);
    obj->func = func_80108398_popgun_pickoff;
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0x4B), 1, 0);
    func_800E5A00_minigame(obj, 0x26, func_80017BB8_main(chr, 0x4C), 2, 0);
    func_800E5A00_minigame(obj, 0x27, func_80017BB8_main(chr, 0x4D), 0, 0);
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, 0x2F), 2, 0x78);
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, 0x36), 2, 0x78);
    func_800E5690_minigame(obj, 0);
    D_8010C5B0_popgun_pickoff++;
}



void func_801080DC_popgun_pickoff(omObjData* obj, u32 file0, s32 file1, s32 player, u16 attr) {
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
    work->unk158 = HuMemAllocTag(sizeof(PgPlayer), 0x7918);
    memset(work->unk158, 0, sizeof(PgPlayer));
    obj->model[0] = func_8000B108_main(file0 | file1, attr);
    obj->model[1] = func_8000B0D4_main(9, attr);
    func_800E3584_minigame(obj->model[1]);
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
void func_80108398_popgun_pickoff(omObjData* obj) {
    u8 attrs[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    MgWork* work;
    PgPlayer* p;
    u8 pad;
    s8 sx;
    s8 sy;
    u16 btn;
    s16 dir;
    f32 rotX;
    f32 rotY;

    btn = 0;
    dir = 0;
    work = obj->data;
    p = work->unk158;
    pad = work->unk57;
    rotX = obj->rot.x;
    rotY = work->unk3C;
    func_800E4A90_minigame(obj);
    switch (D_8010CC20_popgun_pickoff) {
    case 0:
        func_800E5690_minigame(obj, 0x26);
        break;
    case 1:
        p->unk30 = 0xFF;
        break;
    case 2:
        if ((u8)p->cpu == 0) {
            sx = D_800CBB6E_main[(s8)pad];
            sy = D_800D20A1_main[(s8)pad];
            btn = D_800D5558_main[(s8)pad];
            if (sy >= 24) {
                dir = 1;
            } else if (sy < -23) {
                dir = 7;
            } else {
                dir = 4;
            }
            if (sx >= 24) {
                dir++;
            } else if (sx < -23) {
                dir--;
            }
        } else {
            btn = func_8010880C_popgun_pickoff(obj);
            dir = p->cpuDir;
        }
        HuSprAttrReset(p->grp, 0, 0x8000);
        func_80054904_main(p->grp, 0, D_8010CC28_popgun_pickoff[dir].sx, D_8010CC28_popgun_pickoff[dir].sy);
        rotX = D_8010C5E0_popgun_pickoff[dir / 3];
        rotY = D_8010C5E8_popgun_pickoff[p->slot][dir % 3];
        break;
    case 3:
        HuSprAttrSet(p->grp, 0, 0x8000);
        func_800E5690_minigame(obj, 0);
    case 4:
        func_800E5690_minigame(obj, 0);
        func_8001C258_main(obj->model[2], 4, 4);
        rotX = 0.0f;
        if (p->slot != 0) {
            if (rotY > -180.0) {
                rotY -= 20.0;
            } else {
                rotY = -180.0f;
            }
        } else {
            if (rotY < 180.0) {
                rotY += 20.0;
            } else {
                rotY = 180.0f;
            }
        }
        break;
    case 5:
        if (p->unk20 == 0) {
            rotY = 180.0f;
            if (p->unk2C != 0) {
                GwPlayer[work->unk59].bonusCoin += 10;
                func_800E5690_minigame(obj, 0xD);
                func_80045F1C_main(p->file, -1, p->slot);
                func_80017954_main(obj->model[0], 2, attrs[p->chr], p->unk31);
            } else {
                func_800E5690_minigame(obj, 0xE);
                func_80017954_main(obj->model[0], 2, attrs[p->chr], p->unk32);
            }
            p->unk20++;
        }
        break;
    case 6:
        if (work != NULL) {
            HuMemFree(work->unkE8);
            HuMemFree(work->unk158);
            HuMemFree(work);
            obj->data = NULL;
            obj->func = NULL;
        }
        return;
    case 7:
        break;
    }
    if ((btn & 0x8000) && func_80108A78_popgun_pickoff(obj, dir)) {
        func_8004AC5C_main(0x496, work->unk59);
        func_8001C6A8_main(obj->model[0], 0.0f);
        func_800E5798_minigame(obj, 0x27);
    }
    work->unk3C = rotY;
    obj->rot.y = rotY + 180.0;
    obj->rot.x = rotX;
    func_800E4E30_minigame(obj);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80108398_popgun_pickoff);
#endif

u16 func_8010880C_popgun_pickoff(omObjData* obj) {
    s16 open[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    u8 n;
    s32 i;
    PgPlayer* p;
    PgTarget* t;
    s32 btn;

    n = 0;
    p = ((MgWork*)obj->data)->unk158;
    btn = 0;
    switch (p->unk2E) {
    case 0:
        for (i = 0; i < 9; i++) {
            t = &D_8010CC28_popgun_pickoff[i];
            if (t->state != 0) {
                open[n] = i;
                n++;
            }
        }
        if (n != 0) {
            p->cpuDir = open[func_80108E1C_popgun_pickoff() % n];
            p->unk2E++;
        }
        break;
    case 1:
        t = &D_8010CC28_popgun_pickoff[p->cpuDir];
        if (t->kind == 0 || func_80108E1C_popgun_pickoff() % (p->difficulty + 2) == 0) {
            if (func_80108E1C_popgun_pickoff() % (8 - p->difficulty) == 0) {
                btn = 0x8000;
            }
            if (t->state == 2 || func_80108E1C_popgun_pickoff() % (p->difficulty + 2) == 0) {
                break;
            }
        }
        p->unk2E = 0;
        break;
    }
    return btn;
}





u8 func_80108A78_popgun_pickoff(omObjData* obj, s32 dir) {
    Vec pos;
    f32 unused[4][4];
    f64 d[3];
    f64 g;
    PgPlayer* p;
    PgTarget* t;
    PgShot* s;
    s16 m;
    s32 i;
    s32 n;

    g = 0.0;
    p = ((MgWork*)obj->data)->unk158;
    t = &D_8010CC28_popgun_pickoff[dir];
    for (i = 0; i < 0x80; i++) {
        if (D_8010CD50_popgun_pickoff[i].state == 0) {
            break;
        }
    }
    if (i == 0x80) {
        return 0;
    }
    s = &D_8010CD50_popgun_pickoff[i];
    m = obj->model[0];
    func_80108FE4_popgun_pickoff(m, "item_hook", HmfModelData[m].unk40, &pos);
    s->x = pos.x;
    s->y = pos.y;
    s->z = pos.z - 20.0f;
    d[0] = t->x - s->x;
    d[1] = t->y - s->y;
    d[2] = t->z - s->z;
    n = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]) / 60.0;
    for (i = 1; i <= n; i++) {
        g += i * -2.0f;
    }
    s->vx = d[0] / n;
    s->vy = (d[1] - g) / n;
    s->vz = d[2] / n;
    s->target = dir;
    s->slot = p->slot;
    s->state = 1;
    s->board = func_8010A024_popgun_pickoff(D_8010CBD0_popgun_pickoff[3], 0x10001808);
    func_8010AC34_popgun_pickoff(s->board, p->chr);
    func_8010AE0C_popgun_pickoff(s->board, 1.8f, 1.8f, 1.0f);
    return 1;
}

/* Retail reads the sprite group from an uninitialised register (s1): the caller's leftover. */
s16 func_80108CF0_popgun_pickoff(s16 tex, s16 x, s16 y, f32 rot) {
    s16 grp;
    s32 i;

    if (tex == -1) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (D_8010CC00_popgun_pickoff[i] == 0) {
            break;
        }
    }
    if (i >= 16) {
        return -1;
    }
    D_8010CC00_popgun_pickoff[i] = 1;
    func_80055024_main(grp, i, tex, 0);
    func_800550F4_main(grp, i, 2);
    func_80054904_main(grp, i, x, y);
    func_800552DC_main(grp, i, rot);
    HuSprAttrReset(grp, i, 0x8000);
    return i;
}

s32 func_80108E1C_popgun_pickoff(void) {
    D_8010C5F4_popgun_pickoff = D_8010C5F4_popgun_pickoff * 0x41C64E6D + 0x3039;
    D_8010C5F4_popgun_pickoff += rand8();
    return D_8010C5F4_popgun_pickoff >> 16;
}

f32 func_80108E74_popgun_pickoff(f32 x, f32 z) {
    f32 full = 360.0f;
    f32 a = atan2df(z, x) * 57.29577951308232;

    if (a < 0.0f) {
        a += full;
    } else if (a >= full) {
        a -= full;
    }
    return a;
}

f32 func_80108EF4_popgun_pickoff(Vec* a, Vec* b) {
    return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) + (a->z - b->z) * (a->z - b->z));
}

void func_80108F5C_popgun_pickoff(Vec* dir, f32* angles) {
    f32 h = sqrtf(dir->x * dir->x + dir->z * dir->z);

    *angles++ = func_80108E74_popgun_pickoff(h, -dir->y);
    *angles++ = func_80108E74_popgun_pickoff(dir->z, dir->x);
    *angles = 0.0f;
}

void func_80108FE4_popgun_pickoff(s16 model, char* name, s16 frame, Vec* out) {
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

s16 func_80109108_popgun_pickoff(s32 id) {
    void* file;
    s16 sprite;

    file = DataRead(id);
    sprite = func_80055810_main(file);
    DataClose(file);
    return sprite;
}

s16 func_80109150_popgun_pickoff(s16 tex, s16 n) {
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

HuSprite_Unk84_Unk00_Struct* func_80109218_popgun_pickoff(s16 tex, s16 frame) {
    return &func_80055194_main(tex)->unk00[frame];
}

void func_80109260_popgun_pickoff(u16 n) {
    PgBoard* b;
    s16 i;

    D_8010DDF0_popgun_pickoff = n;
    D_8010DDD8_popgun_pickoff = HuMemAlloc(n * sizeof(PgBoard));
    for (i = 0; i < 3; i++) {
        D_8010DDDC_popgun_pickoff[i] = 0;
    }
    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        b = &D_8010DDD8_popgun_pickoff[i];
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


void func_801093A8_popgun_pickoff(Gfx** gfx, HuSprite_Unk84_Unk00_Struct* cel, u8 fmt, u8 siz, u16 rows, u16 uls,
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
s16 func_80109718_popgun_pickoff(PgBoard* b) {
    HuSprite_Unk84_Unk00_Struct* cel;
    HuSprite_Unk84_Unk00_Struct tex;
    Gfx* g;
    Gfx* buf;
    Gfx* start;
    s32 fmt;
    s32 siz;
    s32 mode;
    s32 w;
    u16 rowH;
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
        case 0x20:
            siz = 3;
            fmt = 0;
            gDPSetTextureLUT(g++, G_TT_NONE);
            mode = 2;
            break;
        case 0x8008:
            siz = 1;
            fmt = 4;
            gDPSetTextureLUT(g++, G_TT_NONE);
            mode = 2;
            break;
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
        case 0x10:
            siz = 2;
            fmt = (b->spr->unk1A == 1) ? 3 : 0;
            gDPSetTextureLUT(g++, G_TT_NONE);
            mode = 2;
            break;
        case 0x8004:
            siz = 0;
            fmt = 4;
            gDPSetTextureLUT(g++, G_TT_NONE);
            mode = 0;
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
            if (rowH * w > 0x1000) {
                rowH = 0x1000 / w;
            }
            break;
        default:
            if ((0x2000 >> siz) >= cel->unk06 * w) {
                rowH = cel->unk06;
            } else {
                rowH = (0x2000 >> siz) / w;
            }
            break;
    }
    strips = cel->unk06 / rowH;
    rem = cel->unk06 % rowH;
    /* a whole strip fits one LoadBlock: use the block loaders */
    if (cel->unk04 % (16 >> siz) == 0 && (u32)((rowH * cel->unk04) << siz) <= 0x1000) {
        idx = cel->unk04 >> D_8010C5F8_popgun_pickoff[siz];
        if ((u32)D_8010C608_popgun_pickoff[idx] >= rowH || rowH == D_8010C740_popgun_pickoff[idx]) {
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
        func_801093A8_popgun_pickoff(&g, &tex, fmt, siz, rowH, 0, 0, cel->unk04 - 1, cel->unk06 - 1, cms, cmt, masks,
                                     maskt, mode);
        gSPVertex(g++, 0x0E000000, 5, 0);
        gSP2Triangles(g++, 0, 2, 4, 0, 2, 3, 4, 0);
        gSP2Triangles(g++, 0, 4, 1, 0, 4, 3, 1, 0);
    } else {
        for (i = 0; i < strips; i++) {
            func_801093A8_popgun_pickoff(&g, &tex, fmt, siz, rowH, 0, i * rowH, cel->unk04 - 1, (i + 1) * rowH - 1,
                                         cms, cmt, masks, maskt, mode);
            gSPVertex(g++, 0x0E000000 + i * 2 * sizeof(Vtx), 4, 0);
            gSP2Triangles(g++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
        if (rem != 0) {
            func_801093A8_popgun_pickoff(&g, &tex, fmt, siz, rem, 0, i * rowH, cel->unk04 - 1, cel->unk06 - 1, cms,
                                         cmt, masks, maskt, mode);
            gSPVertex(g++, 0x0E000000 + i * 2 * sizeof(Vtx), 4, 0);
            gSP2Triangles(g++, 0, 2, 3, 0, 0, 3, 1, 0);
        }
    }
    gSPEndDisplayList(g++);
    b->cmds = g - start;
    b->gfx = HuMemAlloc(b->cmds * sizeof(Gfx));
    memcpy(b->gfx, start, b->cmds * sizeof(Gfx));
    HuMemFree(buf);
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80109718_popgun_pickoff);
#endif

#ifdef NON_MATCHING
/* Creates a billboard from sprite tex: a strip of quads sized to fit TMEM, then its display list. */
s16 func_8010A024_popgun_pickoff(s16 tex, u32 flags) {
    PgBoard* b;
    HuSprite_Unk84_Unk00_Struct* cel;
    s32 siz;
    s32 mode;
    s32 w;
    u16 rowH;
    u32 strips;
    s32 rem;
    s32 i;
    s32 j;
    s32 id;

    for (id = 0; id < D_8010DDF0_popgun_pickoff; id++) {
        if (D_8010DDD8_popgun_pickoff[id].spr == NULL) {
            break;
        }
    }
    if (id == D_8010DDF0_popgun_pickoff) {
        return -1;
    }
    b = &D_8010DDD8_popgun_pickoff[id];
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
            if (rowH * w > 0x1000) {
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
    rem = cel->unk06 % rowH;
    b->rows = strips + 2;
    b->rowH = rowH;
    b->vtx = HuMemAlloc((s8)(strips + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < strips + 1; i++) {
        b->vtx[i * 2].v.ob[0] = 0;
        b->vtx[i * 2 + 1].v.ob[0] = cel->unk04;
        b->vtx[i * 2 + 1].v.ob[1] = b->vtx[i * 2].v.ob[1] = -i * rowH;
        b->vtx[i * 2].v.tc[0] = 0;
        b->vtx[i * 2 + 1].v.tc[0] = cel->unk04 << 6;
        b->vtx[i * 2].v.tc[1] = b->vtx[i * 2 + 1].v.tc[1] = (i * rowH) << 6;
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
    if (func_80109718_popgun_pickoff(b) == 0) {
        HuMemFree(b->vtx);
        return -1;
    }
    return id;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010A024_popgun_pickoff);
#endif

#ifdef NON_MATCHING
/* Gives billboard id sprite tex: rebuilds its strip and display list. */
void func_8010A62C_popgun_pickoff(s16 id, s16 tex) {
    PgBoard* b;
    HuSprite_Unk84_Unk00_Struct* cel;
    s32 siz;
    s32 mode;
    s32 w;
    u16 rowH;
    u32 strips;
    s32 rem;
    s32 i;
    s32 j;

    b = &D_8010DDD8_popgun_pickoff[id];
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
            if (rowH * w > 0x1000) {
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
    rem = cel->unk06 % rowH;
    b->rows = strips + 2;
    b->rowH = rowH;
    b->vtx = HuMemAlloc((s8)(strips + 2) * 2 * sizeof(Vtx));
    for (i = 0; i < strips + 1; i++) {
        b->vtx[i * 2].v.ob[0] = 0;
        b->vtx[i * 2 + 1].v.ob[0] = cel->unk04;
        b->vtx[i * 2 + 1].v.ob[1] = b->vtx[i * 2].v.ob[1] = -i * rowH;
        b->vtx[i * 2].v.tc[0] = 0;
        b->vtx[i * 2 + 1].v.tc[0] = cel->unk04 << 6;
        b->vtx[i * 2].v.tc[1] = b->vtx[i * 2 + 1].v.tc[1] = (i * rowH) << 6;
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
    func_80109718_popgun_pickoff(b);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010A62C_popgun_pickoff);
#endif

void func_8010ABB4_popgun_pickoff(s16 id, s16 tex) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->spr = D_800C9530_main[tex];
        b->b = 0xFF;
        b->g = 0xFF;
        b->r = 0xFF;
        b->a = 0xFF;
        b->timer = 0.0f;
        b->frame = 0;
        b->speed = 1.0f;
    }
}













void func_8010AC34_popgun_pickoff(s16 id, s16 frame) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->frame = frame;
        b->timer = 0.0f;
    }
}













void func_8010AC74_popgun_pickoff(s16 id, f32 speed) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->speed = speed;
    }
}


















void func_8010ACB4_popgun_pickoff(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->flags |= 0x04000000;
        b->ofs.x = x;
        b->ofs.y = y;
        b->ofs.z = z;
    }
}













void func_8010AD14_popgun_pickoff(s16 id, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->ofs.z = z;
    }
}


















void func_8010AD54_popgun_pickoff(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->pos.x = x;
        b->pos.y = y;
        b->pos.z = z;
    }
}













void func_8010ADA4_popgun_pickoff(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->pos.x += x;
        b->pos.y += y;
        b->pos.z += z;
    }
}













void func_8010AE0C_popgun_pickoff(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->scale.x = x;
        b->scale.y = y;
        b->scale.z = z;
    }
}













void func_8010AE5C_popgun_pickoff(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->rot.x = x;
        b->rot.y = y;
        b->rot.z = z;
    }
}













void func_8010AEAC_popgun_pickoff(s16 id, u32 flags) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->flags |= flags;
    }
}













void func_8010AEF0_popgun_pickoff(s16 id, u32 flags) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->flags &= ~flags;
    }
}













#ifdef NON_MATCHING
s32 func_8010AF38_popgun_pickoff(s16 id) {
    s32 flags = -1;
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        flags = b->flags;
    }
    return flags;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AF38_popgun_pickoff);
#endif


















void func_8010AF78_popgun_pickoff(s16 id, s8 arg1) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->unk1A = arg1;
    }
}


















PgBoard* func_8010AFB4_popgun_pickoff(s16 id) {
    if (id == -1) {
        return NULL;
    }
    return &D_8010DDD8_popgun_pickoff[id];
}













Vtx* func_8010AFF4_popgun_pickoff(s16 id) {
    PgBoard* b;

    if (id == -1) {
        return NULL;
    }
    b = &D_8010DDD8_popgun_pickoff[id];
    return b->vtx;
}


















#ifdef NON_MATCHING
s32 func_8010B038_popgun_pickoff(s16 id, s16 w, s16 h) {
    PgBoard* b;
    Vtx* v;
    s32 x = w;
    s32 y = h;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B038_popgun_pickoff);
#endif













void func_8010B0D4_popgun_pickoff(s16 id, s8 r, s8 g, s8 b, u16 a) {
    PgBoard* p;

    if (id != -1) {
        p = &D_8010DDD8_popgun_pickoff[id];
        p->r = r;
        p->g = g;
        p->b = b;
        p->a = a;
    }
}













void func_8010B120_popgun_pickoff(s16 id) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
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













void func_8010B200_popgun_pickoff(s32 id, s32 on) {
    PgBoard* b = &D_8010DDD8_popgun_pickoff[id];
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













void func_8010B300_popgun_pickoff(s32 id, s32 flip) {
    PgBoard* b = &D_8010DDD8_popgun_pickoff[id];
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













void func_8010B3D0_popgun_pickoff(s32 id, s32 flip) {
    PgBoard* b = &D_8010DDD8_popgun_pickoff[id];
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













void func_8010B508_popgun_pickoff(s16 id, s32 arg1) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->func = (void (*)(PgBoard*))arg1;
    }
}













void func_8010B544_popgun_pickoff(s16 id, s8 arg1, s8 arg2, u32 flags) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
        b->unk1B = arg1;
        b->unk1C = arg2;
        b->flags |= flags;
        HuMemFree(b->gfx);
        func_80109718_popgun_pickoff(b);
    }
}













#ifdef NON_MATCHING
void func_8010B5B4_popgun_pickoff(s16 id, s32 on) {
    PgBoard* b;
    Vtx* v;
    s8 c;
    s8 a;
    s32 i;

    if (id != -1) {
        b = &D_8010DDD8_popgun_pickoff[id];
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B5B4_popgun_pickoff);
#endif

void func_8010B64C_popgun_pickoff(void) {
    PgBoard* b;
    s32 i;

    if (++D_8010C890_popgun_pickoff >= 3) {
        D_8010C890_popgun_pickoff = 0;
    }
    D_8010DDEC_popgun_pickoff = 0;
    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        b = &D_8010DDD8_popgun_pickoff[i];
        if (b->spr != NULL) {
            D_8010DDEC_popgun_pickoff += (b->cmds * sizeof(Gfx) + b->rows * 2 * sizeof(Vtx)) + 0x40;
        }
    }
    if (D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff] != NULL) {
        HuMemFree(D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff]);
    }
    if (D_8010DDEC_popgun_pickoff != 0) {
        D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff] = HuMemAlloc(D_8010DDEC_popgun_pickoff);
    } else {
        D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff] = NULL;
    }
    D_8010DDE8_popgun_pickoff = D_8010DDDC_popgun_pickoff[D_8010C890_popgun_pickoff];
}










#ifdef NON_MATCHING
/* Sorts the visible billboards by view depth into the opaque (D_8010DE00) and translucent (D_8010DE68) lists. */
void func_8010B7A0_popgun_pickoff(HuCamera* cam, f32 (*view)[4]) {
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
    D_8010DE00_popgun_pickoff.depth = 0.0f;
    D_8010DE68_popgun_pickoff.depth = 99999.9f;
    tail0.depth = -99999.9f;
    tail1.depth = 0.0f;
    D_8010DE68_popgun_pickoff.prev = NULL;
    D_8010DE00_popgun_pickoff.prev = NULL;
    D_8010DE00_popgun_pickoff.next = &tail0;
    D_8010DE68_popgun_pickoff.next = &tail1;
    tail0.prev = &D_8010DE00_popgun_pickoff;
    tail1.prev = &D_8010DE68_popgun_pickoff;
    tail1.next = NULL;
    tail0.next = NULL;
    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        b = &D_8010DDD8_popgun_pickoff[i];
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
            list = &D_8010DE68_popgun_pickoff;
            b->depth = -(f64)b->depth;
        } else {
            list = &D_8010DE00_popgun_pickoff;
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B7A0_popgun_pickoff);
#endif



void func_8010BA44_popgun_pickoff(Gfx** gfx, s32 arg1, s32 arg2) {
    HuCamera* cam = (HuCamera*)arg2;
    f32 unused0[2][4][4];
    f32 view[4][4];
    u8 unused1[0x100];
    Vec rot;
    Vec dir;
    u8 unused2[0x800];
    Gfx* g;
    PgBoard* b;

    g = *gfx;
    func_80079480_main(view, cam->pos.x, cam->pos.y, cam->pos.z, cam->at.x, cam->at.y, cam->at.z, cam->up.x,
                       cam->up.y, cam->up.z);
    dir.x = cam->pos.x - cam->at.x;
    dir.y = cam->pos.y - cam->at.y;
    dir.z = cam->pos.z - cam->at.z;
    func_80108F5C_popgun_pickoff(&dir, (f32*)&rot);
    func_8010B64C_popgun_pickoff();
    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_2CYCLE);
    gDPSetTexturePersp(g++, G_TP_PERSP);
    gSPTexture(g++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(g++, 0x060600);
    gSPSetGeometryMode(g++, 0x280004);
    gDPSetAlphaDither(g++, G_AD_PATTERN);
    func_8010B7A0_popgun_pickoff(cam, view);
    for (b = D_8010DE00_popgun_pickoff.next; b != NULL; b = b->next) {
        g = func_8010BC6C_popgun_pickoff(g, b, view, &rot);
    }
    for (b = D_8010DE68_popgun_pickoff.next; b != NULL; b = b->next) {
        g = func_8010BC6C_popgun_pickoff(g, b, view, &rot);
    }
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    *gfx = g;
    if (HmfPauseF == 0) {
        func_8010C32C_popgun_pickoff();
    }
}

#ifdef NON_MATCHING
/* Draws one billboard: render state, its matrix, then a copy of its vertices and display list. */
Gfx* func_8010BC6C_popgun_pickoff(Gfx* g, PgBoard* b, f32 (*view)[4], Vec* rot) {
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

    cel = &b->spr->unk00[b->frame];
    gDPPipeSync(g++);
    gDPSetTextureFilter(g++, D_8010C880_popgun_pickoff[((s32)b->flags >> 2) & 3]);
    gDPSetColorDither(g++, D_8010C878_popgun_pickoff[((s32)b->flags >> 4) & 3]);
    gDPSetAlphaCompare(g++, D_8010C888_popgun_pickoff[((s32)b->flags >> 22) & 3]);
    if (b->flags & 0x10000) {
        gSPSetGeometryMode(g++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(g++, G_LIGHTING);
    }
    rm2 = 0x110000;
    if (b->flags & 0x08000000) {
        rm2 = 0xC8004000;
    }
    if (b->flags & 0x1000) {
        rm1 = 0x4850;
        if (b->spr->unk18 & 0x8000) {
            rm2 = 0x100000;
            if (b->a == 0x100) {
                gDPSetCombine(g++, 0xFFFE04, 0xFFFDF3F8);
            } else {
                gDPSetCombine(g++, 0xFF9604, 0xFF11FFFF);
            }
        } else if (b->a != 0x100) {
            rm1 = 0x4850;
            rm2 = 0x100000;
            if (b->flags & 0x02000000) {
                gDPSetCombine(g++, 0x609604, 0x3F11FFFF);
            } else {
                gDPSetCombine(g++, 0x121604, 0xFF13FFFF);
            }
        } else {
            rm1 = 0x3038;
            if (b->flags & 0x02000000) {
                gDPSetCombine(g++, 0x60FE04, 0x3FFDF3F8);
            } else {
                gDPSetCombine(g++, 0x127E04, 0xFFFFF3F8);
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
            if ((b->flags & 0x1000) && b->a != 0x100) {
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
    vtx = D_8010DDE8_popgun_pickoff;
    mtx = (Mtx*)(vtx + b->rows * 2 * sizeof(Vtx));
    dl = (u8*)mtx + sizeof(Mtx);
    D_8010DDE8_popgun_pickoff = dl + b->cmds * sizeof(Gfx);
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
    func_80017D24_main(m, b->rot.x, b->rot.y, b->rot.z);
    func_80017CD0_main(m, b->scale.x, b->scale.y, b->scale.z);
    switch (b->unk1A) {
        case 1:
            func_8008A120_main(m, rot->x);
            break;
        case 2:
            func_8008A2A0_main((f32*)m, rot->y);
            break;
        case 7:
            sc[0][0] = b->scale.x;
            sc[1][1] = b->scale.y;
            sc[2][2] = b->scale.z;
            sc[3][3] = 1.0f;
            sc[3][2] = 0.0f;
            sc[3][1] = 0.0f;
            sc[3][0] = 0.0f;
            sc[2][3] = 0.0f;
            sc[2][1] = 0.0f;
            sc[2][0] = 0.0f;
            sc[1][3] = 0.0f;
            sc[1][2] = 0.0f;
            sc[1][0] = 0.0f;
            sc[0][3] = 0.0f;
            sc[0][2] = 0.0f;
            sc[0][1] = 0.0f;
            func_80018544_main(m, inv);
            func_80018044_main(sc, inv, m);
        case 4:
            break;
    }
    guMtxCatF(ofs, m, m);
    guMtxF2L(m, mtx);
    gSPMatrix(g++, osVirtualToPhysical(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPSegment(g++, 0x0C, cel->unk00);
    gSPSegment(g++, 0x0E, vtx);
    memcpy(vtx, b->vtx, b->rows * 2 * sizeof(Vtx));
    memcpy(dl, b->gfx, b->cmds * sizeof(Gfx));
    if (!(b->flags & 0x8000)) {
        gSPDisplayList(g++, dl);
    }
    return g;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010BC6C_popgun_pickoff);
#endif

void func_8010C32C_popgun_pickoff(void) {
    PgBoard* b;
    s32 n;
    s32 i;

    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        b = &D_8010DDD8_popgun_pickoff[i];
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
                            func_8010B120_popgun_pickoff(i);
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










void func_8010C4EC_popgun_pickoff(void) {
    s32 i;

    for (i = 0; i < D_8010DDF0_popgun_pickoff; i++) {
        func_8010B120_popgun_pickoff(i);
    }
    for (i = 0; i < 3; i++) {
        if (D_8010DDDC_popgun_pickoff[i] != NULL) {
            HuMemFree(D_8010DDDC_popgun_pickoff[i]);
        }
    }
    HuMemFree(D_8010DDD8_popgun_pickoff);
}
