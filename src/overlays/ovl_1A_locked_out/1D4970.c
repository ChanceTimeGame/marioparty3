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

extern f32 D_8010A680_locked_out[4][4]; /* world to view (D_8010A6B8 is its [3][2]) */
extern f32 D_8010A6B8_locked_out; /* D_8010A680[3][2] */
extern f32 D_8010A6C0_locked_out[4][4]; /* view to world */
extern f32 D_8010A700_locked_out; /* tan(fov / 2) */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801059A0_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80105B38_locked_out);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106040_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106134_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106424_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801064E0_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106FBC_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_8010713C_locked_out);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A298_locked_out);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A2A0_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801071D8_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80107844_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80107ABC_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801089F8_locked_out);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109CDC_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109D70_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109DBC_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109E34_locked_out);

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
