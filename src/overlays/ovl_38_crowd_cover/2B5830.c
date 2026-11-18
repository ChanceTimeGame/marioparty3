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



INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_801059A0_crowd_cover);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_801060C4_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CAF0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CAF8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB00_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106144_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB48_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106580_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106CB8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CB78_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBD8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CBE0_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80106D4C_crowd_cover);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107554_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107C5C_crowd_cover);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107E0C_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CC84_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CDEC_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80107E40_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_80108238_crowd_cover);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_801090CC_crowd_cover);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", func_801091FC_crowd_cover);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE38_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE3C_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", jtbl_8010CE40_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE60_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE68_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE70_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE78_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE80_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE88_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE90_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CE98_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEA0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEA8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEB0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEB8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEC0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEC8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CED0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CED8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEE0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEE8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEF0_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CEF8_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF00_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF08_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF10_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF18_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF20_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF28_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF30_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF38_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF40_crowd_cover);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_38_crowd_cover/2B5830", D_8010CF48_crowd_cover);

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
