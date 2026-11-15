#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/camera.h"
#include "game/hmfman.h"

// eatsa A: Eatsa Pizza (two teams of two eat a pizza from opposite halves of the screen)

typedef func_800E1BA8_minigame_ObjData MgWork;

/* MgWork::unk158 of a player: screen-space state (2D, origin at the screen centre). */
typedef struct EpPlayer {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 prevX;
    /* 0x10 */ f32 prevY;
    /* 0x14 */ f32 heading;
    /* 0x18 */ f32 cpuHeading; /* CPU: heading it steers to */
    /* 0x1C */ f32 radius;
    /* 0x20 */ s16 cellX; /* pizza slice cell under the player (32x32 px) */
    /* 0x22 */ s16 cellY;
    /* 0x24 */ s16 tgtX; /* CPU: target cell */
    /* 0x26 */ s16 tgtY;
    /* 0x28 */ u16 timer; /* CPU: frames to the next decision */
    /* 0x2A */ u16 pushed; /* frames pushed by another player */
    /* 0x2C */ s32 model; /* model file */
    /* 0x30 */ u8 player;
    /* 0x31 */ u8 difficulty;
    /* 0x32 */ u8 side; /* team: 0 left half, 1 right half */
    /* 0x33 */ u8 slot; /* index in the team */
    /* 0x34 */ u8 unk34;
    /* 0x35 */ s8 cpu;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
} EpPlayer; /* size 0x38 */

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]); /* matrix copy */
void func_8007DFE0_main(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
f32 fabsf(f32);

// minigame
void func_800E1804_minigame(void);

extern s32 D_800EBEB0_minigame[];

// LOCAL
void func_80105AF4_eatsa_pizza(omObjData* obj);
void func_80105BE4_eatsa_pizza(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out);
void func_80105C64_eatsa_pizza(f32 (*src)[4], f32 (*dst)[4]);
void func_80105FF0_eatsa_pizza(void);
void func_80106084_eatsa_pizza(omObjData* obj);
void func_801083BC_eatsa_pizza(void);

extern f32 D_80109358_eatsa_pizza[4][4]; /* world to view (D_80109390 is its [3][2]) */
extern f32 D_80109390_eatsa_pizza; /* D_80109358[3][2]: the view depth offset */
extern f32 D_80109398_eatsa_pizza[4][4]; /* view to world */
extern f32 D_801093D8_eatsa_pizza; /* tan(fov / 2) */

void func_801059A0_eatsa_pizza(void) {
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
    Hu3DCamSetPerspective(0, 5.0f, 80.0f, 4000.0f);
    func_800E1804_minigame();
    func_80105AF4_eatsa_pizza(obj);
    func_801083BC_eatsa_pizza();
    func_80105FF0_eatsa_pizza();
    func_8001F38C_main(0, 0, 0);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105AF4_eatsa_pizza(omObjData* obj) {
    HuCamera* cam;
    f32 s;

    CZoom = 2000.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = -100.0f;
    omOutView(obj);
    cam = gCameraList;
    s = sindf(cam->fov[0] / 2.0);
    D_801093D8_eatsa_pizza = s / cosdf(cam->fov[0] / 2.0);
    guMtxL2F(D_80109358_eatsa_pizza, &cam->mtxs[0].lookAtMtx);
    guMtxL2F(D_80109398_eatsa_pizza, &cam->mtxs[0].lookAtMtx);
    func_80105C64_eatsa_pizza(D_80109398_eatsa_pizza, D_80109398_eatsa_pizza);
}

/* out = (x, y, z) * the 3x3 part of m */
void func_80105BE4_eatsa_pizza(f32 (*m)[4], f32 x, f32 y, f32 z, f32* out) {
    out[0] = x * m[0][0] + y * m[1][0] + z * m[2][0];
    out[1] = x * m[0][1] + y * m[1][1] + z * m[2][1];
    out[2] = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

/* dst = inverse of the affine matrix src */
void func_80105C64_eatsa_pizza(f32 (*src)[4], f32 (*dst)[4]) {
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
        func_80105BE4_eatsa_pizza(dst, -m[3][0], -m[3][1], -m[3][2], dst[3]);
    }
}

/* world position -> screen position (origin at the centre) */
void func_80105E54_eatsa_pizza(Vec* pos, f32* out) {
    f32 m[4][4];
    f32 t;
    f32 w;

    func_8007DFE0_main(m, pos->x, pos->y, pos->z);
    guMtxCatF(m, D_80109358_eatsa_pizza, m);
    t = m[3][2] * D_801093D8_eatsa_pizza;
    w = fabsf(t);
    if (w != 0.0) {
        out[0] = m[3][0] * 160.0f / w / 1.3333334f;
        out[1] = -m[3][1] * 120.0f / w;
    }
}

/* screen position at depth z -> world position */
void func_80105F24_eatsa_pizza(f32 x, f32 y, f32 z, f32* out) {
    f32 m[4][4];
    f32 d;
    f32 w;

    d = z + D_80109390_eatsa_pizza;
    w = fabsf(d * D_801093D8_eatsa_pizza);
    func_8007DFE0_main(m, 2.0f * x * w * 1.3333334f / 320.0f, -(2.0f * y * w / 240.0f), d);
    guMtxCatF(m, D_80109398_eatsa_pizza, m);
    out[0] = m[3][0];
    out[1] = m[3][1];
    out[2] = m[3][2];
}

void func_80105FF0_eatsa_pizza(void) {
    s32 i;

    func_800E18D8_minigame();
    D_800EC280_minigame = 0;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 11, 50, -1, func_80106084_eatsa_pizza);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80106084_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80106504_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_8010679C_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_801070E8_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_801078C4_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80107A64_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80107E6C_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_801083A8_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_801083BC_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80108470_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_801084F8_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_801087DC_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80108C50_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80108D1C_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80108E48_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80108F4C_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80108FA4_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80108FEC_eatsa_pizza);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_801090B4_eatsa_pizza);
