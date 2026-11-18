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

// cv A: Crowd Cover

typedef func_800E1BA8_minigame_ObjData MgWork;
typedef f32 Matrix4f[4][4];

typedef struct PgPair {
    s16 unk0;
    s16 unk2;
} PgPair;

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

/* A textured quad strip drawn with its own display list (D_8010D8EC_crowd_cover[D_8010D904_crowd_cover]). */
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
    /* 0x2C */ u8 win;
    /* 0x2D */ u8 cpu;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 mot0; /* motions */
    /* 0x30 */ u8 mot1;
    /* 0x31 */ u8 mot2;
    /* 0x32 */ s16 pick; /* chosen picture + 1, 0 none yet */
    /* 0x34 */ s16 cpuWait; /* CPU: frames until its next input */
    /* 0x36 */ u16 cpuBtn; /* CPU: button pressed when cpuWait runs out */
    /* 0x38 */ char unk38[0x1C];
} PgPlayer; /* size 0x54 */

/* One member of the crowd (D_8010CFE0_crowd_cover). */
typedef struct CcActor {
    /* 0x00 */ s16 board; /* billboard */
    /* 0x02 */ s16 mdl; /* shadow model */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ u8 unk08;
    /* 0x09 */ u8 unk09;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ Vec unk28;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
} CcActor; /* size 0x44 */

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

void func_80105B58_crowd_cover(omObjData* obj);
void func_80105C54_crowd_cover(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out);
void func_80105CD4_crowd_cover(f32 (*src)[4], f32 (*dst)[4]);
void func_80105EC4_crowd_cover(Vec* pos, Vec* out);
void func_80105FD0_crowd_cover(f32 x, f32 y, f32 z, Vec* out);
void func_801060C4_crowd_cover(void);
void func_80107298_crowd_cover(omObjData* obj, u32 file0, s32 file1, s32 player, u16 attr);
void func_801090CC_crowd_cover(s16 model, char* name, s16 frame, Vec* out);
void func_80109354_crowd_cover(u16 n);
s16 func_8010980C_crowd_cover(PgBoard* b);
s16 func_8010A12C_crowd_cover(s16 tex, u32 flags);
s32 func_80108F1C_crowd_cover(void);
f32 func_80108FDC_crowd_cover(Vec* a, Vec* b);
void func_8010AD3C_crowd_cover(s16 id, s16 frame);
void func_8010AFB4_crowd_cover(s16 id, u32 flags);
void func_8010AFF8_crowd_cover(s16 id, u32 flags);
void func_8010B228_crowd_cover(s16 id);
void func_8010BB4C_crowd_cover(Gfx** gfx, s32 arg1, s32 arg2);
void func_8010C61C_crowd_cover(void);
void func_8010ADBC_crowd_cover(s16 id, f32 x, f32 y, f32 z);
void func_8010B080_crowd_cover(s16 id, s8 arg1);
void func_8010B1DC_crowd_cover(s16 id, s8 r, s8 g, s8 b, u16 a);
s16 func_80109244_crowd_cover(s16 tex, s16 n);
HuSprite_Unk84_Unk00_Struct* func_8010930C_crowd_cover(s16 tex, s16 frame);

extern s16 D_8010CFB8_crowd_cover[16]; /* sprite slots in use */
extern f32 D_8010D868_crowd_cover[4][4]; /* world to view (D_8010DD88 is its [3][2]) */
extern f32 D_8010D8A0_crowd_cover; /* D_8010DD50[3][2] */
extern f32 D_8010D8A8_crowd_cover[4][4]; /* view to world */
extern f32 D_8010D8E8_crowd_cover; /* tan(fov / 2) */
extern PgBoard* D_8010D8EC_crowd_cover;
extern s32 D_8010D904_crowd_cover; /* billboard count */
extern void* D_8010D8F0_crowd_cover[3]; /* per-frame buffers */
extern u8* D_8010D8FC_crowd_cover; /* this frame's buffer */
extern s32 D_8010D900_crowd_cover; /* its size */
extern s32 D_8010CA9C_crowd_cover; /* buffer index */
extern s32 D_8010C804_crowd_cover[4]; /* texel shift by size */
extern s16 D_8010C814_crowd_cover[]; /* LoadBlock row limits by line width */
extern s16 D_8010C94C_crowd_cover[];
extern s16 D_8010CA84_crowd_cover[4]; /* colour dither by flags >> 4 */
extern s16 D_8010CA8C_crowd_cover[4]; /* texture filter by flags >> 2 */
extern s16 D_8010CA94_crowd_cover[4]; /* alpha compare by flags >> 22 */
void func_8008A120_main(Matrix4f m, f32 a);
void func_80018544_main(Matrix4f src, Matrix4f dst);
void func_8010949C_crowd_cover(Gfx** gfx, HuSprite_Unk84_Unk00_Struct* cel, u8 fmt, u8 siz, u16 rows, u16 uls,
                                  u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt, s32 mode);
extern PgBoard D_8010D918_crowd_cover; /* opaque draw list head */
extern PgBoard D_8010D980_crowd_cover; /* translucent draw list head */
extern s8 HmfPauseF;
void func_80079480_main(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp,
                        f32 zUp); /* guLookAtF */
void func_80109044_crowd_cover(Vec* dir, f32* angles);
void func_8010B754_crowd_cover(void);
void func_8010C45C_crowd_cover(void);
Gfx* func_8010BD74_crowd_cover(Gfx* g, PgBoard* b, f32 (*view)[4], Vec* rot);
void func_8010B8A8_crowd_cover(HuCamera* cam, f32 (*view)[4]);
void func_800341D0_main(Gfx** gfx, s32 timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult,
                        s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                        s32 shiftt);
void func_80034998_main(Gfx** gfx, s32 timg, s32 fmt, u32 width, s32 height, s32 uls, s32 ult, s32 lrs,
                        s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
extern u32 D_8010C800_crowd_cover; /* random seed */
extern u8 D_800CE20A_main;
extern s16 D_8010D860_crowd_cover;
extern s16 D_8010CFD8_crowd_cover;
void func_80106144_crowd_cover(omObjData* obj);
void func_80106D4C_crowd_cover(omObjData* obj);
void func_80107E40_crowd_cover(omObjData* obj);
void func_80106580_crowd_cover(omObjData* obj);
void func_80107554_crowd_cover(omObjData* obj);
s16 func_801091FC_crowd_cover(s32 id);
void func_80106CB8_crowd_cover(void);
void func_80107E0C_crowd_cover(void);
u16 func_80107C5C_crowd_cover(omObjData* obj);



void func_801059A0_crowd_cover(void) {
    omObjData* obj;
    u8 cam;
    s32 i;

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
    func_80105B58_crowd_cover(obj);
    func_801060C4_crowd_cover();
    func_80109354_crowd_cover(0x80);
    func_80106CB8_crowd_cover();
    func_80107E0C_crowd_cover();
    /* warm up the generator by 0..15 steps */
    for (i = (s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 16.0) - 1; i != 0; i--) {
        func_80108F1C_crowd_cover();
    }
    func_8001F38C_main(0xB4, 0xB4, 0xB4);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105B58_crowd_cover(omObjData* obj) {
    HuCamera* cam;
    f32 s;

    CZoom = 400.0f;
    CRot.x = -45.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 0.0f;
    omOutView(obj);
    cam = gCameraList;
    s = sindf(cam->fov[0] / 2.0);
    D_8010D8E8_crowd_cover = s / cosdf(cam->fov[0] / 2.0);
    guMtxL2F(D_8010D868_crowd_cover, &cam->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010D8A8_crowd_cover, &cam->mtxs[0].lookAtMtx);
    func_80105CD4_crowd_cover(D_8010D8A8_crowd_cover, D_8010D8A8_crowd_cover);
}

void func_80105C54_crowd_cover(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out) {
    out[0] = x * m[0][0] + y * m[1][0] + z * m[2][0];
    out[1] = x * m[0][1] + y * m[1][1] + z * m[2][1];
    out[2] = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

void func_80105CD4_crowd_cover(f32 (*src)[4], f32 (*dst)[4]) {
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
        func_80105C54_crowd_cover(dst, -m[3][0], -m[3][1], -m[3][2], dst[3]);
    }
}

void func_80105EC4_crowd_cover(Vec* pos, Vec* out) {
    f32 m[4][4];
    f32 t;
    f32 w;

    func_8007DFE0_main(m, pos->x, pos->y, pos->z);
    guMtxCatF(m, D_8010D868_crowd_cover, m);
    t = m[3][2] * D_8010D8E8_crowd_cover;
    w = fabsf(t);
    if (w != 0.0) {
        out->x = m[3][0] * 160.0f / w / 1.3333333333333333;
        out->y = -m[3][1] * 120.0f / w;
    }
    out->x += 160.0;
    out->y += 120.0;
    out->z = w;
}

void func_80105FD0_crowd_cover(f32 x, f32 y, f32 z, Vec* out) {
    f32 m[4][4];
    f32 d;
    f32 w;

    d = z + D_8010D8A0_crowd_cover;
    w = fabsf(d * D_8010D8E8_crowd_cover);
    x -= 160.0;
    y -= 120.0;
    func_8007DFE0_main(m, 2.0f * x * w * 1.3333333333333333 / 320.0, -(2.0f * y * w / 240.0f), d);
    guMtxCatF(m, D_8010D8A8_crowd_cover, m);
    out->x = m[3][0];
    out->y = m[3][1];
    out->z = m[3][2];
}

void func_801060C4_crowd_cover(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_8010D860_crowd_cover = D_800CE20A_main;
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106144_crowd_cover);
    D_8010CFD8_crowd_cover = 0;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CAF0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CAF8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB00_crowd_cover);

typedef struct CcU16x3 {
    u16 v[3];
} CcU16x3;
typedef struct CcFrames {
    s16 v[6][3];
} CcFrames;
extern CcU16x3 D_8010CAF0_crowd_cover;
extern CcU16x3 D_8010CAF8_crowd_cover;
extern CcFrames D_8010CB00_crowd_cover;
extern s16 D_8010CF88_crowd_cover[16]; /* sprite files */
extern s16 D_8010CFA8_crowd_cover[16]; /* their sprite groups */
extern s16 D_8010C6C4_crowd_cover[3][2]; /* screen positions */
extern s16 D_8010D862_crowd_cover;

/* Game setup object: loads the sprites, picks the round's layout at random. */
void func_80106144_crowd_cover(omObjData* obj) {
    CcU16x3 files1 = D_8010CAF0_crowd_cover;
    CcU16x3 files0 = D_8010CAF8_crowd_cover;
    CcFrames frames = D_8010CB00_crowd_cover;
    s32 unused[8];
    s16 pick;
    s32 i;

    omSetStatBit(obj, 0xA0);
    D_8010CF88_crowd_cover[0] = func_801091FC_crowd_cover(0x590000);
    D_8010CFA8_crowd_cover[0] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[0], 1);
    func_80054904_main(D_8010CFA8_crowd_cover[0], 0, 0xA0, 0x78);
    HuSprAttrSet(D_8010CFA8_crowd_cover[0], 0, 0x4000);
    D_8010CF88_crowd_cover[3] = func_801091FC_crowd_cover(0x59000A);
    D_8010CFA8_crowd_cover[4] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[3], 1);
    func_80054904_main(D_8010CFA8_crowd_cover[4], 0, 0xA0, 0xC6);
    HuSprAttrSet(D_8010CFA8_crowd_cover[4], 0, 0x100C);
    D_8010CF88_crowd_cover[2] = func_801091FC_crowd_cover(files0.v[D_8010D860_crowd_cover] | 0x590000);
    D_8010CFA8_crowd_cover[2] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[2], 3);
    pick = (f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 6.0;
    for (i = 0; i < 3; i++) {
        func_80054904_main(D_8010CFA8_crowd_cover[2], i, D_8010C6C4_crowd_cover[i][0], D_8010C6C4_crowd_cover[i][1]);
        HuSprAttrSet(D_8010CFA8_crowd_cover[2], i, 0x1008);
        func_80054FF8_main(D_8010CFA8_crowd_cover[2], i, frames.v[pick][i]);
    }
    D_8010CF88_crowd_cover[1] = func_801091FC_crowd_cover(files1.v[D_8010D860_crowd_cover] | 0x590000);
    D_8010CFA8_crowd_cover[1] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[1], 1);
    func_80054904_main(D_8010CFA8_crowd_cover[1], 0, 0xA0, 0x6E);
    D_8010D862_crowd_cover = (f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 3.0;
    func_80054FF8_main(D_8010CFA8_crowd_cover[1], 0, frames.v[pick][D_8010D862_crowd_cover]);
    HuSprAttrSet(D_8010CFA8_crowd_cover[1], 0, 0x405808);
    D_8010CF88_crowd_cover[4] = func_801091FC_crowd_cover(0x59000B);
    D_8010CFA8_crowd_cover[5] = func_80109244_crowd_cover(D_8010CF88_crowd_cover[4], 1);
    func_80054904_main(D_8010CFA8_crowd_cover[5], 0, 0xA0, 0x6E);
    HuSprScaleSet(D_8010CFA8_crowd_cover[5], 0, 1.2f, 1.2f);
    HuSprAttrSet(D_8010CFA8_crowd_cover[5], 0, 0x940C);
    obj->func = func_80106580_crowd_cover;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB48_crowd_cover);

typedef struct CcS16x3 {
    s16 v[3];
} CcS16x3;
extern CcS16x3 D_8010CB48_crowd_cover;
extern s16 D_8010CF80_crowd_cover; /* picture alpha */
extern s16 D_8010CF82_crowd_cover; /* music delay */
extern s16 D_8010C6C0_crowd_cover; /* time left, frames */
extern s32 D_8010C6D0_crowd_cover; /* step timer */
extern s32 D_8010C6D4_crowd_cover; /* winner slot, -1 none */
extern s32 D_8010C6D8_crowd_cover; /* the loser's wrong pick + 1, 0 none */

/* Game flow: intro, countdown, picks, result, wipe out. */
void func_80106580_crowd_cover(omObjData* obj) {
    CcS16x3 voices = D_8010CB48_crowd_cover;

    if (HmfPauseF) {
        HuSprAttrSet(D_8010CFA8_crowd_cover[1], 0, 0x8000);
        return;
    }
    HuSprAttrReset(D_8010CFA8_crowd_cover[1], 0, 0x8000);
    switch (D_8010CFD8_crowd_cover) {
        case 0:
            func_8001AC8C_main(0xC0, func_8010BB4C_crowd_cover, 2);
            D_8010CF80_crowd_cover = 0;
            func_80055458_main(D_8010CFA8_crowd_cover[1], 0, 0);
            GMesCreate(6);
            D_8010C6C0_crowd_cover = 900;
            D_8010CFD8_crowd_cover++;
            HuAudFXPlay(voices.v[D_8010D860_crowd_cover]);
            D_8010CF82_crowd_cover = 45;
        case 1:
            if (--D_8010CF82_crowd_cover == 0) {
                HuAudSeqPlay(0x31);
            }
            if (GMesStatGet() == 0) {
                D_8010CFD8_crowd_cover++;
                GMesCreate(0x1A, (D_8010C6C0_crowd_cover + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            if (D_8010CF80_crowd_cover < 0x100) {
                D_8010CF80_crowd_cover += 8;
                func_80055458_main(D_8010CFA8_crowd_cover[1], 0, D_8010CF80_crowd_cover);
            } else {
                func_80055458_main(D_8010CFA8_crowd_cover[1], 0, 0x100);
            }
            D_8010C6C0_crowd_cover--;
            func_8003F578_main((D_8010C6C0_crowd_cover + 29) / 30);
            if (D_8010C6C0_crowd_cover == 0) {
                D_8010CFD8_crowd_cover = 3;
            }
            if (PG_PLAYER(0)->pick | PG_PLAYER(1)->pick) {
                D_8010CFD8_crowd_cover = 3;
                if (PG_PLAYER(0)->pick && PG_PLAYER(1)->pick) {
                    PG_PLAYER(func_80108F1C_crowd_cover() & 1)->pick = 0;
                }
            }
            break;
        case 3:
            if (PG_PLAYER(0)->pick) {
                if (PG_PLAYER(0)->pick == D_8010D862_crowd_cover + 1) {
                    D_8010C6D4_crowd_cover = 0;
                    PG_PLAYER(0)->win = 1;
                    PG_PLAYER(1)->win = 0;
                } else {
                    D_8010C6D4_crowd_cover = 1;
                    D_8010C6D8_crowd_cover = PG_PLAYER(0)->pick;
                    PG_PLAYER(0)->win = 0;
                    PG_PLAYER(1)->win = 1;
                }
                D_8010C6D0_crowd_cover = 36;
            } else if (PG_PLAYER(1)->pick) {
                if (PG_PLAYER(1)->pick == D_8010D862_crowd_cover + 1) {
                    D_8010C6D4_crowd_cover = 1;
                    PG_PLAYER(0)->win = 0;
                    PG_PLAYER(1)->win = 1;
                } else {
                    D_8010C6D4_crowd_cover = 0;
                    D_8010C6D8_crowd_cover = PG_PLAYER(1)->pick;
                    PG_PLAYER(0)->win = 1;
                    PG_PLAYER(1)->win = 0;
                }
            } else {
                D_8010C6D4_crowd_cover = -1;
            }
            D_8010C6D0_crowd_cover = 15;
            func_8003F5C0_main();
            GMesCreate(0x11);
            HuAudSeqFadeOut(0x78);
            D_8010CFD8_crowd_cover++;
            break;
        case 4:
            if (D_8010CF80_crowd_cover < 0x100) {
                D_8010CF80_crowd_cover += 8;
                func_80055458_main(D_8010CFA8_crowd_cover[1], 0, D_8010CF80_crowd_cover);
            } else {
                func_80055458_main(D_8010CFA8_crowd_cover[1], 0, 0x100);
            }
            D_8010C6C0_crowd_cover -= 10;
            if (D_8010C6C0_crowd_cover > 0) {
                break;
            }
            D_8010C6C0_crowd_cover = 0;
            if (GMesStatGet()) {
                break;
            }
            if (D_8010C6D0_crowd_cover == 15) {
                HuSprAttrReset(D_8010CFA8_crowd_cover[5], 0, 0x8000);
                if (D_8010C6D8_crowd_cover == 0) {
                    HuAudFXPlay(D_8010C6D4_crowd_cover == -1 ? 0x4B6 : 0x4B5);
                    func_80054904_main(D_8010CFA8_crowd_cover[5], 0, D_8010C6C4_crowd_cover[D_8010D862_crowd_cover][0],
                                       D_8010C6C4_crowd_cover[D_8010D862_crowd_cover][1]);
                } else {
                    HuAudFXPlay(0x4B6);
                    func_80054FF8_main(D_8010CFA8_crowd_cover[5], 0, 1);
                    func_80054904_main(D_8010CFA8_crowd_cover[5], 0, D_8010C6C4_crowd_cover[D_8010C6D8_crowd_cover - 1][0],
                                       D_8010C6C4_crowd_cover[D_8010C6D8_crowd_cover - 1][1]);
                }
            }
            if (--D_8010C6D0_crowd_cover == 0) {
                if (D_8010C6D4_crowd_cover == -1) {
                    GMesCreate(0x20);
                    HuAudSeqPlay(0x6C);
                } else {
                    GMesCreate(0x16, PG_PLAYER(D_8010C6D4_crowd_cover)->chr);
                    HuAudSeqPlay(0x67);
                }
                D_8010C6D0_crowd_cover = 15;
                D_8010CFD8_crowd_cover++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                if (--D_8010C6D0_crowd_cover == 0) {
                    D_8010CFD8_crowd_cover++;
                }
            }
            break;
        case 6:
            if (D_8010C6D0_crowd_cover) {
                if (--D_8010C6D0_crowd_cover == 0) {
                    D_8010CFD8_crowd_cover++;
                }
            } else {
                D_8010C6D0_crowd_cover = 16;
                /* retail reads the low half of the s32 D_8010C6D0 (big-endian) as the fade length */
                WipeCreateOut(0, ((s16*)&D_8010C6D0_crowd_cover)[1]);
                HuAudSeqFadeOut(((s16*)&D_8010C6D0_crowd_cover)[1]);
                func_8004AB0C_main(((s16*)&D_8010C6D0_crowd_cover)[1]);
            }
            break;
        case 7:
            func_8004A950_main();
            omOvlReturnEx(1);
            func_8010C61C_crowd_cover();
            break;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010C6D0_crowd_cover = 0;
        D_8010CFD8_crowd_cover = 6;
    }
}

void func_80106CB8_crowd_cover(void) {
    s32 i;

    func_800E18D8_minigame();
    D_800EC280_minigame = 0;
    for (i = 0; i < 2; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 11, 50, -1, func_80106D4C_crowd_cover);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB78_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBD8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBE0_crowd_cover);

typedef struct CcU8x8 {
    u8 v[8];
} CcU8x8;
typedef struct CcMots {
    s32 v[3][8];
} CcMots;
extern CcU8x8 D_8010CB70_crowd_cover;
extern CcMots D_8010CB78_crowd_cover;
extern CcS16x3 D_8010CBD8_crowd_cover;
extern char D_8010CBE0_crowd_cover[]; /* "item_hook" */
extern u8 D_8010C6E4_crowd_cover; /* next slot */
extern s16 D_8010C6EC_crowd_cover[][3]; /* start positions */
extern f32 D_8010C704_crowd_cover[]; /* facing */

/* Player object setup: model, motions, the three picture cards in hand. */
void func_80106D4C_crowd_cover(omObjData* obj) {
    CcU8x8 attrs = D_8010CB70_crowd_cover;
    CcMots mots = D_8010CB78_crowd_cover;
    CcS16x3 cards = D_8010CBD8_crowd_cover;
    s32 unused[4];
    u8 player;
    s8 chr;
    u32 file0;
    s32 file1;
    MgWork* work;
    PgPlayer* p;
    u16 attr;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8010C6E4_crowd_cover == GwPlayer[i].group) {
            break;
        }
    }
    player = i;
    chr = GwPlayer[player].chr;
    file0 = D_800A178C_main[chr][0];
    file1 = D_800A178C_main[chr][2];
    func_800E19F0_minigame(1);
    func_80107298_crowd_cover(obj, file0, file1, player, 0x2C9);
    work = obj->data;
    obj->trans.x = D_8010C6EC_crowd_cover[D_8010C6E4_crowd_cover][0];
    obj->trans.y = D_8010C6EC_crowd_cover[D_8010C6E4_crowd_cover][1];
    obj->trans.z = D_8010C6EC_crowd_cover[D_8010C6E4_crowd_cover][2];
    work->unk3C = D_8010C704_crowd_cover[D_8010C6E4_crowd_cover];
    obj->rot.y = obj->rot.x = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.65f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 4.0, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelRotSet(obj->model[1], -50.0f, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    p = work->unk158;
    p->player = i;
    p->chr = chr;
    p->slot = D_8010C6E4_crowd_cover;
    p->unk18 = p->unk14 = work->unk3C;
    p->cpu = GwPlayer[player].stat & 1;
    p->unk2E = 0;
    p->difficulty = GwPlayer[player].cpu_difficulty;
    p->file = file0 | 0x2F;
    p->win = 0;
    p->unk1C = 11.0f;
    p->pos.x = obj->trans.x;
    p->pos.y = obj->trans.y;
    p->pos.z = obj->trans.z;
    p->unk20 = 0;
    p->mot2 = func_80017790_main(obj->model[0], 2, attrs.v[chr], file0 | mots.v[2][chr]);
    p->mot0 = func_80017AD8_main(file0 | mots.v[0][chr]);
    p->mot1 = func_80017AD8_main(file0 | mots.v[1][chr]);
    func_8001C514_main(obj->model[0]);
    attr = 0x2BD;
    for (i = 0; i < 3; i++) {
        s32 m = i + 2;

        obj->model[m] = func_8000B108_main(cards.v[i] | 0x590000, attr);
        func_8001EF6C_main(obj->model[m], obj->model[0], D_8010CBE0_crowd_cover);
        func_8001C258_main(obj->model[m], 0x4000, 0x4000);
    }
    func_8001C258_main(obj->model[2], 4, 0);
    obj->model[9] = func_8000B0A0_main(7, 0x2DD);
    obj->func = func_80107554_crowd_cover;
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 0x26, func_80017BB8_main(chr, 0x66), 1, 0);
    func_800E5A00_minigame(obj, 0x27, func_80017BB8_main(chr, 0x67), 1, 0x3C);
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, 0x2F), 2, 0x78);
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, 0x36), 2, 0x78);
    func_800E5690_minigame(obj, 0x26);
    D_8010C6E4_crowd_cover++;
}

void func_80107298_crowd_cover(omObjData* obj, u32 file0, s32 file1, s32 player, u16 attr) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBF8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC00_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC08_crowd_cover);

typedef struct CcS16x4 {
    s16 v[4];
} CcS16x4;
extern CcS16x4 D_8010CBF8_crowd_cover;
extern CcS16x4 D_8010CC00_crowd_cover;
extern CcU16x3 D_8010CC08_crowd_cover;

#ifdef NON_MATCHING
/* Player object: CPU decision, picking a card (Z/B/A), the flip and the result motion. */
void func_80107554_crowd_cover(omObjData* obj) {
    CcU8x8 attrs = D_8010CB70_crowd_cover;
    CcS16x4 waits = D_8010CBF8_crowd_cover; /* CPU reaction time by difficulty */
    CcS16x4 unused = D_8010CC00_crowd_cover;
    CcU16x3 btns = D_8010CC08_crowd_cover; /* the button for each card */
    s32 unused2[4];
    Vec pos;
    MgWork* work;
    PgPlayer* p;
    u8 pad;
    f32 rot;
    u16 btn;
    s16 mdl;

    work = obj->data;
    p = work->unk158;
    pad = work->unk57;
    rot = work->unk3C;
    func_800E4A90_minigame(obj);
    switch (D_8010CFD8_crowd_cover) {
        case 0:
            if (p->cpu) {
                p->cpuWait = waits.v[p->difficulty] +
                             (s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * waits.v[p->difficulty]);
                if ((s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 100.0) < (p->difficulty + 1) * 20) {
                    p->cpuBtn = btns.v[D_8010D862_crowd_cover];
                } else {
                    p->cpuBtn = btns.v[(s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 3.0)];
                }
            }
            break;
        case 2:
            if (!p->cpu) {
                btn = D_800D5558_main[(s8)pad];
            } else {
                btn = func_80107C5C_crowd_cover(obj);
            }
            if (btn & 0xE000) {
                if (btn & 0x8000) {
                    p->pick = 3;
                } else if (btn & 0x4000) {
                    p->pick = 2;
                } else if (btn & 0x2000) {
                    p->pick = 1;
                }
            }
            break;
        case 3:
            if (p->pick) {
                HuAudFXPlay(0x4B4);
                func_8001C258_main(obj->model[2], 4, 4);
                func_8001C258_main(obj->model[p->pick + 1], 4, 0);
            } else {
                func_800E5690_minigame(obj, 0);
                mdl = obj->model[9];
                func_801090CC_crowd_cover(obj->model[0], D_8010CBE0_crowd_cover, HmfModelData[obj->model[0]].unk40, &pos);
                func_8001C258_main(mdl, 4, 0);
                Hu3DModelPosSet(mdl, pos.x, pos.y, pos.z + 10.0);
                Hu3DModelScaleSet(mdl, 0.4f, 0.4f, 0.4f);
                func_8001C6A8_main(mdl, 0.0f);
                func_8001C92C_main(mdl, 2.0f);
                func_8001C814_main(mdl, 1, 0);
                func_8001C258_main(obj->model[2], 4, 4);
            }
        case 4:
            if (rot > 0.0) {
                rot -= 30.0;
            } else {
                rot = 0.0f;
                if (p->pick) {
                    HmfModel* m;

                    func_800E5690_minigame(obj, 0x27);
                    m = &HmfModelData[obj->model[0]];
                    if (m->unk40 == D_800CCF58_main[m->unk02].unk02 - 2.0) {
                        omVibrate(work->unk59, 2, 3, 10);
                    }
                }
            }
            break;
        case 5:
            if (p->unk20 == 0) {
                if (p->pick) {
                    mdl = obj->model[9];
                    func_801090CC_crowd_cover(obj->model[0], D_8010CBE0_crowd_cover, HmfModelData[obj->model[0]].unk40,
                                              &pos);
                    func_8001C258_main(mdl, 4, 0);
                    Hu3DModelPosSet(mdl, pos.x, pos.y, pos.z + 10.0);
                    Hu3DModelScaleSet(mdl, 0.4f, 0.4f, 0.4f);
                    func_8001C6A8_main(mdl, 0.0f);
                    func_8001C92C_main(mdl, 2.0f);
                    func_8001C814_main(mdl, 1, 0);
                    func_8001C258_main(obj->model[p->pick + 1], 4, 4);
                }
                if (p->win) {
                    GwPlayer[work->unk59].bonusCoin += 10;
                    func_80017954_main(obj->model[0], 2, attrs.v[p->chr], p->mot0);
                    func_800E5690_minigame(obj, 0xD);
                    func_80045F1C_main(p->file, -1, p->slot);
                } else {
                    func_80017954_main(obj->model[0], 2, attrs.v[p->chr], p->mot1);
                    func_800E5690_minigame(obj, 0xE);
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
            return;
    }
    {
        f32 (*mtx)[4] = (f32 (*)[4])HmfModelData[obj->model[0]].mtx;

        guMtxIdentF(mtx);
        func_8008A120_main(mtx, -50.0f);
        func_80017D24_main(mtx, 0.0f, rot, 0.0f);
        work->unk3C = rot;
        func_800E4E30_minigame(obj);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107554_crowd_cover);
#endif

typedef struct CcTbl9 {
    s16 v[9];
} CcTbl9;
extern CcTbl9 D_8010CC70_crowd_cover;

#ifdef NON_MATCHING
/* CPU input: the button held in cpuBtn, released once cpuWait counts down to 0. */
u16 func_80107C5C_crowd_cover(omObjData* obj) {
    CcTbl9 tbl = D_8010CC70_crowd_cover; /* unused copy */
    MgWork* work = obj->data;
    PgPlayer* pl = work->unk158;
    u16 btn;

    btn = 0;
    if (--pl->cpuWait == 0) {
        btn = pl->cpuBtn;
    }
    return btn;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107C5C_crowd_cover);
#endif

s16 func_80107CE0_crowd_cover(s16 tex, s16 x, s16 y, f32 rot) {
    s16 grp;
    s32 i;

    if (tex == -1) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (D_8010CFB8_crowd_cover[i] == 0) {
            break;
        }
    }
    if (i >= 16) {
        return -1;
    }
    D_8010CFB8_crowd_cover[i] = 1;
    func_80055024_main(grp, i, tex, 0);
    func_800550F4_main(grp, i, 2);
    func_80054904_main(grp, i, x, y);
    func_800552DC_main(grp, i, rot);
    HuSprAttrReset(grp, i, 0x8000);
    return i;
}

void func_80107E0C_crowd_cover(void) {
    omAddObj(3, 11, 50, -1, func_80107E40_crowd_cover);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC84_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CDEC_crowd_cover);

typedef struct CcSpots {
    f32 v[30][3];
} CcSpots;
extern CcSpots D_8010CC84_crowd_cover;
extern CcU16x3 D_8010CDEC_crowd_cover;
extern s16 D_8010D864_crowd_cover; /* crowd sprite file */
extern s16 D_8010D866_crowd_cover; /* crowd size */
extern CcActor D_8010CFE0_crowd_cover[30];
void func_8001FA68_main(s16);
void func_8001F9E4_main(s16, u8);
void func_8010AE5C_crowd_cover(s16 id, f32 x, f32 y, f32 z);
void func_8010AF14_crowd_cover(s16 id, f32 x, f32 y, f32 z);
void func_80108238_crowd_cover(omObjData* obj);

/* Crowd setup: 30 members placed on the 30 spots in a random order. */
void func_80107E40_crowd_cover(omObjData* obj) {
    CcSpots spots = D_8010CC84_crowd_cover;
    s16 order[32];
    CcU16x3 files = D_8010CDEC_crowd_cover;
    CcActor* a;
    s32 i;
    u16 tmp;
    s16 j;

    D_8010D864_crowd_cover = func_801091FC_crowd_cover(files.v[D_8010D860_crowd_cover] | 0x590000);
    D_8010D866_crowd_cover = 30;
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.8f;
    for (i = 0; i < D_8010D866_crowd_cover; i++) {
        order[i] = i;
    }
    for (i = D_8010D866_crowd_cover; i > 0; i--) {
        j = (f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * i;
        tmp = order[i - 1];
        order[i - 1] = order[j];
        order[j] = tmp;
    }
    a = D_8010CFE0_crowd_cover;
    for (i = 0; i < D_8010D866_crowd_cover; i++, a++) {
        a->board = func_8010A12C_crowd_cover(D_8010D864_crowd_cover, 0x401808);
        a->mdl = func_8000B0D4_main(9, 0x2C9);
        func_8001FA68_main(a->mdl);
        func_8001F9E4_main(a->mdl, 0xFF);
        a->pos.x = spots.v[order[i]][0];
        a->pos.y = spots.v[order[i]][1];
        a->pos.z = spots.v[order[i]][2];
        a->unk08 = 1;
        a->unk04 = 0;
        a->unk09 = (s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 30.0) + 1;
        a->unk28.x = a->unk28.y = a->unk28.z = 0.0f;
        a->unk06 = a->unk07 = 0;
        a->unk0C = 0.0f;
        a->unk34 = (f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 360.0;
        a->unk38 = a->unk3C = a->unk40 = 0.0f;
        if (D_8010D860_crowd_cover == 1) {
            a->unk34 = func_8000B0A0_main(0x10013, 0x2DD); /* sic: a model id in a float */
        } else if (D_8010D860_crowd_cover == 2) {
            a->unk3C = a->unk04 * 4;
        }
        func_8010ADBC_crowd_cover(a->board, 16.0f, 32.0f, 0.0f);
        func_8010AE5C_crowd_cover(a->board, a->pos.x, a->pos.y, a->pos.z);
        func_8010AF14_crowd_cover(a->board, 2.5f, 2.5f, 1.0f);
        Hu3DModelScaleSet(a->mdl, 0.45f, 0.45f, 0.45f);
    }
    obj->func = func_80108238_crowd_cover;
}

extern s16 D_8010C714_crowd_cover[][13]; /* billboard frames by facing, -1 ends */
void func_8001ACDC_main(s16 model);
f32 func_80108F74_crowd_cover(f32 x, f32 z);

/* Crowd: wander, separate, leave as the timer runs down (fade, walk off or pop). */
void func_80108238_crowd_cover(omObjData* obj) {
    CcActor* a;
    CcActor* b;
    s32 i;
    s32 j;
    s32 frame;
    s16 mdl;
    f32 ang;
    f32 sc;

    a = D_8010CFE0_crowd_cover;
    for (i = 0; i < D_8010D866_crowd_cover; i++, a++) {
        a->unk09--;
        switch (a->unk08) {
            case 0:
                a->unk09 = (s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 10.0) + 15;
                a->unk08 = 1;
                a->unk28.x = a->unk28.z = 0.0f;
                if (func_80108F1C_crowd_cover() & 1) {
                    break;
                }
                a->unk04 = (f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 8.0;
                if (func_80108F1C_crowd_cover() & 1) {
                    break;
                }
            case 2:
                a->unk28.x = sindf(a->unk04 * 45.0) * 4.0;
                a->unk28.z = cosdf(a->unk04 * 45.0) * 4.0;
                a->unk09 = 20;
                a->unk08 = 3;
                break;
            case 1:
                /* low byte of the s16 direction (big-endian) */
                a->unk06 = ((u8*)&a->unk04)[1] & 7;
                if (a->unk09 == 0) {
                    a->unk08 = 0;
                }
                break;
            case 3:
                a->unk0C += 0.5;
                if (a->unk09 == 0) {
                    a->unk08 = 0;
                }
                break;
            case 4:
                switch (D_8010D860_crowd_cover) {
                    case 0:
                        if (a->pos.x >= 0.0) {
                            a->unk28.x = 8.0f;
                            a->unk04 = 2;
                            if (a->pos.x >= 500.0) {
                                a->unk08 = 6;
                            }
                        } else {
                            a->unk28.x = -8.0f;
                            a->unk04 = 6;
                            if (a->pos.x <= -500.0) {
                                a->unk08 = 6;
                            }
                        }
                        a->unk0C += 1.0;
                        break;
                    case 1:
                        a->unk04 = 8;
                        a->unk0C += 0.5;
                        a->unk07 = a->unk0C;
                        sc = a->unk0C * 0.1 + 2.5;
                        func_8010AF14_crowd_cover(a->board, sc, sc, 1.0f);
                        if (a->unk07 >= 8) {
                            func_8010AFB4_crowd_cover(a->board, 0x8000);
                            func_8001C258_main(a->mdl, 4, 4);
                            mdl = a->unk34; /* the pop effect model */
                            HuAudFXPlay(0x4B7);
                            func_8001C258_main(mdl, 4, 0);
                            Hu3DModelPosSet(mdl, a->pos.x, a->pos.y + 40.0, a->pos.z);
                            Hu3DModelScaleSet(mdl, obj->scale.x, obj->scale.y, obj->scale.z);
                            func_8001C6A8_main(mdl, 0.0f);
                            func_8001C92C_main(mdl, 1.5f);
                            func_8001C814_main(mdl, 1, 0);
                            a->unk08 = 5;
                        }
                        break;
                    case 2:
                        a->unk04 = 0;
                        a->pos.y += 8.0;
                        a->unk34 = 0.0f;
                        a->unk38 += 20.0;
                        if (a->unk38 >= 360.0) {
                            a->unk38 -= 360.0;
                        }
                        a->unk1C.x = sindf(a->unk38) * 6.0;
                        a->unk09 -= 9;
                        func_8010B1DC_crowd_cover(a->board, 0, 0, 0, a->unk09);
                        func_8001F9E4_main(a->mdl, a->unk09);
                        if (a->unk09 == 0) {
                            a->unk08 = 6;
                        }
                        break;
                }
                break;
            case 5:
                frame = a->unk34;
                if (D_800CCF58_main[HmfModelData[frame].unk02].unk02 <= HmfModelData[frame].unk40) {
                    func_8001ACDC_main(frame);
                    a->unk08 = 6;
                }
                continue;
            case 6:
                func_8010AFB4_crowd_cover(a->board, 0x8000);
                func_8001C258_main(a->mdl, 4, 4);
                continue;
        }
        a->pos.x += a->unk28.x;
        a->pos.z += a->unk28.z;
        if (a->unk08 < 4) {
            if (i >= (s16)(D_8010C6C0_crowd_cover / 30)) {
                a->unk28.x = a->unk28.z = 0.0f;
                a->unk08 = 4;
                a->unk0C = 0.0f;
                a->unk38 = 0.0f;
                a->unk09 = 250;
            }
            for (j = 0; j < D_8010D866_crowd_cover; j++) {
                if (i == j) {
                    continue;
                }
                b = &D_8010CFE0_crowd_cover[j];
                if (b->unk08 < 4 && !(func_80108FDC_crowd_cover(&a->pos, &b->pos) >= 40.0)) {
                    ang = func_80108F74_crowd_cover(b->pos.x - a->pos.x, b->pos.z - a->pos.z) + 180.0;
                    a->unk08 = 0;
                    if (ang >= 360.0) {
                        ang -= 360.0;
                    }
                    a->pos.x = b->pos.x + sindf(ang) * 42.0;
                    a->pos.z = b->pos.z + cosdf(ang) * 42.0;
                }
            }
            if (a->pos.x > 200.0) {
                a->unk08 = func_80108F1C_crowd_cover() & 1;
                a->unk04 = (s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 3.0) + 5;
                a->pos.x = 200.0f;
            } else if (a->pos.x < -200.0) {
                a->unk08 = func_80108F1C_crowd_cover() & 1;
                a->unk04 = (s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 3.0) + 1;
                a->pos.x = -200.0f;
            }
            if (a->pos.z > -60.0) {
                a->unk08 = func_80108F1C_crowd_cover() & 1;
                a->unk04 = (s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 3.0) + 3;
                a->pos.z = -60.0f;
            } else if (a->pos.z < -500.0) {
                a->unk08 = func_80108F1C_crowd_cover() & 1;
                a->unk04 = ((s32)((f32)func_80108F1C_crowd_cover() * (1.0 / 65536.0) * 3.0) + 7) & 7;
                a->pos.z = -500.0f;
            }
        }
        /* low byte of the s16 direction (big-endian) */
        a->unk06 = ((u8*)&a->unk04)[1];
        a->unk07 = a->unk0C;
        frame = D_8010C714_crowd_cover[a->unk06][a->unk07];
        if (frame == -1) {
            a->unk07 = 0;
            a->unk0C = 0.0f;
            frame = D_8010C714_crowd_cover[a->unk06][a->unk07];
        }
        if (D_8010D860_crowd_cover == 2) {
            a->unk34 += 10.0;
            if (a->unk34 >= 360.0) {
                a->unk34 -= 360.0;
            }
            a->unk1C.y = sindf(a->unk34) * 8.0 + 20.0;
            a->pos.x -= a->unk28.x * 0.5;
            a->pos.z -= a->unk28.z * 0.5;
            frame = a->unk04 * 4;
            if (frame != (s32)a->unk3C) {
                if ((s32)a->unk3C < frame) {
                    if (frame - (s32)a->unk3C < 16) {
                        a->unk3C += 1.0;
                    } else {
                        a->unk3C -= 1.0;
                    }
                } else if (frame < (s32)a->unk3C) {
                    if (frame - (s32)a->unk3C >= -15) {
                        a->unk3C -= 1.0;
                    } else {
                        a->unk3C += 1.0;
                    }
                }
                if (a->unk3C >= 30.0) {
                    a->unk3C -= 30.0;
                } else if (a->unk3C < 0.0) {
                    a->unk3C += 30.0;
                }
                frame = a->unk3C;
            }
        }
        func_8010AE5C_crowd_cover(a->board, a->pos.x + a->unk1C.x, a->pos.y + a->unk1C.y, a->pos.z);
        func_8010AD3C_crowd_cover(a->board, frame);
        Hu3DModelPosSet(a->mdl, a->pos.x, 0.0f, a->pos.z - 5.0);
    }
}

s32 func_80108F1C_crowd_cover(void) {
    D_8010C800_crowd_cover = D_8010C800_crowd_cover * 0x41C64E6D + 0x3039;
    D_8010C800_crowd_cover += rand8();
    return D_8010C800_crowd_cover >> 16;
}

f32 func_80108F74_crowd_cover(f32 x, f32 z) {
    f32 full = 360.0f;
    f32 a = atan2df(x, z);

    if (a < 0.0f) {
        a += full;
    } else if (a >= full) {
        a -= full;
    }
    return a;
}

f32 func_80108FDC_crowd_cover(Vec* a, Vec* b) {
    return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) + (a->z - b->z) * (a->z - b->z));
}

void func_80109044_crowd_cover(Vec* dir, f32* angles) {
    f32 h = sqrtf(dir->x * dir->x + dir->z * dir->z);

    *angles++ = func_80108F74_crowd_cover(h, -dir->y);
    *angles++ = func_80108F74_crowd_cover(dir->z, dir->x);
    *angles = 0.0f;
}

void func_801090CC_crowd_cover(s16 model, char* name, s16 frame, Vec* out) {
    HuMtx4F mdl;
    HuMtx4F res;
    HuMtx4F obj;
    HmfModel* m;

    func_80016B00_main(model, frame, name, obj);
    m = &HmfModelData[model];
    func_8002367C_main(mdl, (f32 (*)[4])m->mtx);
    func_80017C10_main((Mtx*)mdl, m->pos.x, m->pos.y, m->pos.z);
    func_80017D24_main(mdl, m->rot.x, m->rot.y, m->rot.z);
    func_80017CD0_main(mdl, m->scale.x, m->scale.y, m->scale.z);
    func_80018044_main(obj, mdl, res);
    out->x = res[0][0] + res[1][0] + res[2][0] + res[3][0];
    out->y = res[0][1] + res[1][1] + res[2][1] + res[3][1];
    out->z = res[0][2] + res[1][2] + res[2][2] + res[3][2];
}

s16 func_801091FC_crowd_cover(s32 id) {
    void* file;
    s16 sprite;

    file = DataRead(id);
    sprite = func_80055810_main(file);
    DataClose(file);
    return sprite;
}

s16 func_80109244_crowd_cover(s16 tex, s16 n) {
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

HuSprite_Unk84_Unk00_Struct* func_8010930C_crowd_cover(s16 tex, s16 frame) {
    return &func_80055194_main(tex)->unk00[frame];
}

void func_80109354_crowd_cover(u16 n) {
    PgBoard* b;
    s16 i;

    D_8010D904_crowd_cover = n;
    D_8010D8EC_crowd_cover = HuMemAlloc(n * sizeof(PgBoard));
    for (i = 0; i < 3; i++) {
        D_8010D8F0_crowd_cover[i] = 0;
    }
    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        b = &D_8010D8EC_crowd_cover[i];
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

void func_8010949C_crowd_cover(Gfx** gfx, HuSprite_Unk84_Unk00_Struct* cel, u8 fmt, u8 siz, u16 rows, u16 uls,
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010980C_crowd_cover);

#ifdef NON_MATCHING
/* Creates a billboard from sprite tex: a strip of quads sized to fit TMEM, then its display list. */
s16 func_8010A12C_crowd_cover(s16 tex, u32 flags) {
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

    for (id = 0; id < D_8010D904_crowd_cover; id++) {
        if (D_8010D8EC_crowd_cover[id].spr == NULL) {
            break;
        }
    }
    if (id == D_8010D904_crowd_cover) {
        return -1;
    }
    b = &D_8010D8EC_crowd_cover[id];
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
    if (func_8010980C_crowd_cover(b) == 0) {
        HuMemFree(b->vtx);
        return -1;
    }
    return id;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010A12C_crowd_cover);
#endif

#ifdef NON_MATCHING
/* Gives billboard id sprite tex: rebuilds its strip and display list. */
void func_8010A734_crowd_cover(s16 id, s16 tex) {
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

    b = &D_8010D8EC_crowd_cover[id];
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
    func_8010980C_crowd_cover(b);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010A734_crowd_cover);
#endif

void func_8010ACBC_crowd_cover(s16 id, s16 tex) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
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

void func_8010AD3C_crowd_cover(s16 id, s16 frame) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->frame = frame;
        b->timer = 0.0f;
    }
}

void func_8010AD7C_crowd_cover(s16 id, f32 speed) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->speed = speed;
    }
}

void func_8010ADBC_crowd_cover(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->flags |= 0x04000000;
        b->ofs.x = x;
        b->ofs.y = y;
        b->ofs.z = z;
    }
}

void func_8010AE1C_crowd_cover(s16 id, f32 speed) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->ofs.z = speed;
    }
}

void func_8010AE5C_crowd_cover(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->pos.x = x;
        b->pos.y = y;
        b->pos.z = z;
    }
}

void func_8010AEAC_crowd_cover(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->pos.x += x;
        b->pos.y += y;
        b->pos.z += z;
    }
}

void func_8010AF14_crowd_cover(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->scale.x = x;
        b->scale.y = y;
        b->scale.z = z;
    }
}

void func_8010AF64_crowd_cover(s16 id, f32 x, f32 y, f32 z) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->rot.x = x;
        b->rot.y = y;
        b->rot.z = z;
    }
}

void func_8010AFB4_crowd_cover(s16 id, u32 flags) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->flags |= flags;
    }
}

void func_8010AFF8_crowd_cover(s16 id, u32 flags) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->flags &= ~flags;
    }
}

#ifdef NON_MATCHING
s32 func_8010B040_crowd_cover(s16 id) {
    s32 flags = -1;
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        flags = b->flags;
    }
    return flags;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B040_crowd_cover);
#endif

void func_8010B080_crowd_cover(s16 id, s8 arg1) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->unk1A = arg1;
    }
}

PgBoard* func_8010B0BC_crowd_cover(s16 id) {
    if (id == -1) {
        return NULL;
    }
    return &D_8010D8EC_crowd_cover[id];
}

Vtx* func_8010B0FC_crowd_cover(s16 id) {
    PgBoard* b;

    if (id == -1) {
        return NULL;
    }
    b = &D_8010D8EC_crowd_cover[id];
    return b->vtx;
}

#ifdef NON_MATCHING
s32 func_8010B140_crowd_cover(s16 id, s16 w, s16 h) {
    PgBoard* b;
    Vtx* v;
    s32 x = w;
    s32 y = h;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B140_crowd_cover);
#endif

void func_8010B1DC_crowd_cover(s16 id, s8 r, s8 g, s8 b, u16 a) {
    PgBoard* p;

    if (id != -1) {
        p = &D_8010D8EC_crowd_cover[id];
        p->r = r;
        p->g = g;
        p->b = b;
        p->a = a;
    }
}

void func_8010B228_crowd_cover(s16 id) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
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

void func_8010B308_crowd_cover(s32 id, s32 on) {
    PgBoard* b = &D_8010D8EC_crowd_cover[id];
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

void func_8010B408_crowd_cover(s32 id, s32 flip) {
    PgBoard* b = &D_8010D8EC_crowd_cover[id];
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

void func_8010B4D8_crowd_cover(s32 id, s32 flip) {
    PgBoard* b = &D_8010D8EC_crowd_cover[id];
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

void func_8010B610_crowd_cover(s16 id, s32 arg1) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->func = (void (*)(PgBoard*))arg1;
    }
}

void func_8010B64C_crowd_cover(s16 id, s8 arg1, s8 arg2, u32 flags) {
    PgBoard* b;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
        b->unk1B = arg1;
        b->unk1C = arg2;
        b->flags |= flags;
        HuMemFree(b->gfx);
        func_8010980C_crowd_cover(b);
    }
}

#ifdef NON_MATCHING
void func_8010B6BC_crowd_cover(s16 id, s32 on) {
    PgBoard* b;
    Vtx* v;
    s8 c;
    s8 a;
    s32 i;

    if (id != -1) {
        b = &D_8010D8EC_crowd_cover[id];
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B6BC_crowd_cover);
#endif

void func_8010B754_crowd_cover(void) {
    PgBoard* b;
    s32 i;

    if (++D_8010CA9C_crowd_cover >= 3) {
        D_8010CA9C_crowd_cover = 0;
    }
    D_8010D900_crowd_cover = 0;
    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        b = &D_8010D8EC_crowd_cover[i];
        if (b->spr != NULL) {
            D_8010D900_crowd_cover += (b->cmds * sizeof(Gfx) + b->rows * 2 * sizeof(Vtx)) + 0x40;
        }
    }
    if (D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover] != NULL) {
        HuMemFree(D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover]);
    }
    if (D_8010D900_crowd_cover != 0) {
        D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover] = HuMemAlloc(D_8010D900_crowd_cover);
    } else {
        D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover] = NULL;
    }
    D_8010D8FC_crowd_cover = D_8010D8F0_crowd_cover[D_8010CA9C_crowd_cover];
}

#ifdef NON_MATCHING
/* Sorts the visible billboards by view depth into the opaque (D_8010DE00) and translucent (D_8010DE68) lists. */
void func_8010B8A8_crowd_cover(HuCamera* cam, f32 (*view)[4]) {
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
    D_8010D918_crowd_cover.depth = 0.0f;
    D_8010D980_crowd_cover.depth = 99999.9f;
    tail0.depth = -99999.9f;
    tail1.depth = 0.0f;
    D_8010D980_crowd_cover.prev = NULL;
    D_8010D918_crowd_cover.prev = NULL;
    D_8010D918_crowd_cover.next = &tail0;
    D_8010D980_crowd_cover.next = &tail1;
    tail0.prev = &D_8010D918_crowd_cover;
    tail1.prev = &D_8010D980_crowd_cover;
    tail1.next = NULL;
    tail0.next = NULL;
    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        b = &D_8010D8EC_crowd_cover[i];
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
            list = &D_8010D980_crowd_cover;
            b->depth = -(f64)b->depth;
        } else {
            list = &D_8010D918_crowd_cover;
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
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010B8A8_crowd_cover);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010BB4C_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_8010BD74_crowd_cover);

void func_8010C45C_crowd_cover(void) {
    PgBoard* b;
    s32 n;
    s32 i;

    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        b = &D_8010D8EC_crowd_cover[i];
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
                            func_8010B228_crowd_cover(i);
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

void func_8010C61C_crowd_cover(void) {
    s32 i;

    for (i = 0; i < D_8010D904_crowd_cover; i++) {
        func_8010B228_crowd_cover(i);
    }
    for (i = 0; i < 3; i++) {
        if (D_8010D8F0_crowd_cover[i] != NULL) {
            HuMemFree(D_8010D8F0_crowd_cover[i]);
        }
    }
    HuMemFree(D_8010D8EC_crowd_cover);
}
