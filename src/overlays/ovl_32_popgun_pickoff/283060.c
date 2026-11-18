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

/* A target hole / pop-up target (D_8010CC28_popgun_pickoff[9]); D_8010CD50_popgun_pickoff uses the same size. */
typedef struct PgTarget {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rot;
    /* 0x10 */ s16 sx; /* screen position */
    /* 0x12 */ s16 sy;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 board; /* billboard id */
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ char unk1C[4];
} PgTarget; /* size 0x20 */

/* A textured quad strip drawn with its own display list (D_8010DDD8_popgun_pickoff[D_8010DDF0_popgun_pickoff]). */
typedef struct PgBoard {
    /* 0x00 */ Gfx* gfx;
    /* 0x04 */ Vtx* vtx; /* 2 per strip row */
    /* 0x08 */ HuSprite_Unk84_Struct* spr; /* NULL = free */
    /* 0x0C */ char unk0C[8];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 rows; /* vertex pairs */
    /* 0x19 */ u8 rowH; /* texels per row */
    /* 0x1A */ s8 unk1A;
    /* 0x1B */ s8 unk1B;
    /* 0x1C */ s8 unk1C;
    /* 0x1D */ u8 r;
    /* 0x1E */ u8 g;
    /* 0x1F */ u8 b;
    /* 0x20 */ u16 a;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
    /* 0x28 */ u32 flags;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ Vec ofs;
    /* 0x40 */ Vec pos;
    /* 0x4C */ Vec scale;
    /* 0x58 */ Vec rot;
    /* 0x64 */ char unk64[4];
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
} PgPlayer;

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
void func_80109260_popgun_pickoff(s32 arg0);
s32 func_80109718_popgun_pickoff(PgBoard* b);
s16 func_8010A024_popgun_pickoff(s16 tex, u32 flags);
void func_80106A44_popgun_pickoff(omObjData* obj);
void func_8010704C_popgun_pickoff(omObjData* obj);
void func_8010BA44_popgun_pickoff(Gfx** gfx, s32 arg1, s32 arg2);
void func_8010C4EC_popgun_pickoff(void);
void func_8010ACB4_popgun_pickoff(s16 id, f32 x, f32 y, f32 z);
void func_8010AD54_popgun_pickoff(s16 id, f32 x, f32 y, f32 z);
void func_8010AE0C_popgun_pickoff(s16 id, f32 x, f32 y, f32 z);
void func_8010AE5C_popgun_pickoff(s16 id, f32 x, f32 y, f32 z);
void func_8010AF78_popgun_pickoff(s16 id, s8 arg1);
void func_8010B0D4_popgun_pickoff(s16 id, u8 r, u8 g, u8 b, u16 a);
s16 func_80109108_popgun_pickoff(s32 id);
s16 func_80109150_popgun_pickoff(s16 tex, s16 n);
HuSprite_Unk84_Unk00_Struct* func_80109218_popgun_pickoff(s16 tex, s16 frame);

extern s16 D_8010CBD0_popgun_pickoff[16]; /* textures */
extern s16 D_8010CBF0_popgun_pickoff[8]; /* sprite groups */
extern s16 D_8010CC00_popgun_pickoff[16]; /* sprite slots in use */
extern s16 D_8010CC20_popgun_pickoff;
typedef struct PgPair {
    s16 unk0;
    s16 unk2;
} PgPair;
extern PgPair D_8010CC22_popgun_pickoff;
extern PgTarget D_8010CC28_popgun_pickoff[9];
extern PgTarget D_8010CD50_popgun_pickoff[0x80];
extern f32 D_8010DD50_popgun_pickoff[4][4]; /* world to view (D_8010DD88 is its [3][2]) */
extern f32 D_8010DD88_popgun_pickoff; /* D_8010DD50[3][2] */
extern f32 D_8010DD90_popgun_pickoff[4][4]; /* view to world */
extern f32 D_8010DDD0_popgun_pickoff; /* tan(fov / 2) */
extern PgBoard* D_8010DDD8_popgun_pickoff;
extern s32 D_8010DDF0_popgun_pickoff; /* billboard count */
extern u32 D_8010C5F4_popgun_pickoff; /* random seed */
extern s32 D_8010C590_popgun_pickoff; /* timer */
extern u16 D_8010C594_popgun_pickoff; /* game timer, frames */
extern s32 D_8010C598_popgun_pickoff; /* winner slot, -1 draw */
extern s32 D_8010C59C_popgun_pickoff; /* end camera timer */
extern s16 D_8010C5A0_popgun_pickoff;
extern u8 D_8010DDD4_popgun_pickoff;

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
        t->unk14 = -1;
        t->unk16 = 0;
        t->unk1B = 0;
        t->board = func_8010A024_popgun_pickoff(D_8010CBD0_popgun_pickoff[4], 0x12009808);
        func_8010ACB4_popgun_pickoff(t->board, 16.0f, 32.0f, 0.0f);
        func_8010AD54_popgun_pickoff(t->board, t->x, t->y - 42.0, t->z - 10.0);
        func_8010AE0C_popgun_pickoff(t->board, 3.0f, 3.0f, 1.0f);
        func_8010AE5C_popgun_pickoff(t->board, 90.0f, 0.0f, 0.0f);
        func_8010AF78_popgun_pickoff(t->board, 0);
        func_8010B0D4_popgun_pickoff(t->board, 0, 0, 0, 0x100);
    }
    for (i = 0; i < 0x80; i++) {
        D_8010CD50_popgun_pickoff[i].unk19 = 0;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010704C_popgun_pickoff);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CA78_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CAA8_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CAB0_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CB10_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80107B20_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_801080DC_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80108398_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010880C_popgun_pickoff);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", D_8010CB78_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80108A78_popgun_pickoff);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80109260_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_801093A8_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_80109718_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010A024_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010A62C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010ABB4_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AC34_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AC74_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010ACB4_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AD14_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AD54_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010ADA4_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AE0C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AE5C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AEAC_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AEF0_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AF38_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AF78_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AFB4_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010AFF4_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B038_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B0D4_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B120_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B200_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B300_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B3D0_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B508_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B544_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B5B4_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B64C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010B7A0_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010BA44_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010BC6C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010C32C_popgun_pickoff);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_32_popgun_pickoff/283060", func_8010C4EC_popgun_pickoff);
