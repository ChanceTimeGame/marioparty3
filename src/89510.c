#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

/* guRotateRPYF (Hudson, MP2 src/B2C60.c, from MP1 src/9F750.c): rotations about x, y, z in degrees */
void func_80088910_main(Matrix4f m, f32 x, f32 y, f32 z) {
    f32 sx;
    f32 cx;
    f32 sy;
    f32 cy;
    f32 sz;
    f32 cz;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    m[0][0] = cy * cz;
    m[0][1] = cy * sz;
    m[0][2] = -sy;
    m[1][0] = sx * sy * cz - cx * sz;
    m[1][1] = sx * sy * sz + cx * cz;
    m[1][2] = sx * cy;
    m[2][0] = cx * sy * cz + sx * sz;
    m[2][1] = cx * sy * sz - sx * cz;
    m[2][2] = cx * cy;
    m[3][0] = m[0][3] = m[1][3] = m[2][3] = m[3][1] = m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

/* guRotateRPY: the same rotation written straight into the fixed-point Mtx; element i's integer
   half is the s16 at i, its fraction the u16 at 16 + i (big-endian s16 pairs, as guMtxF2L) */
// NON_MATCHING: scheduling, retail stores af[0] after the column zeros (masked 4)
#ifdef NON_MATCHING
void func_80088A70_main(Mtx* m, f32 x, f32 y, f32 z) {
    f32 sx;
    f32 cx;
    f32 sy;
    f32 cy;
    f32 sz;
    f32 cz;
    s32 e1;
    s32 e2;
    s16* ai;
    u16* af;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    ai = (s16*)m;
    af = (u16*)m + 16;
    e1 = cy * cz * 65536.0f;
    e2 = cy * sz * 65536.0f;
    ai[0] = e1 >> 16;
    ai[1] = e2 >> 16;
    af[0] = e1;
    af[1] = e2;
    e1 = -sy * 65536.0f;
    ai[2] = e1 >> 16;
    ai[3] = 0;
    af[2] = e1;
    af[3] = 0;
    e1 = (sx * sy * cz - cx * sz) * 65536.0f;
    e2 = (sx * sy * sz + cx * cz) * 65536.0f;
    ai[4] = e1 >> 16;
    ai[5] = e2 >> 16;
    af[4] = e1;
    af[5] = e2;
    e1 = sx * cy * 65536.0f;
    ai[6] = e1 >> 16;
    ai[7] = 0;
    af[6] = e1;
    af[7] = 0;
    e1 = (cx * sy * cz + sx * sz) * 65536.0f;
    e2 = (cx * sy * sz - sx * cz) * 65536.0f;
    ai[8] = e1 >> 16;
    ai[9] = e2 >> 16;
    af[8] = e1;
    af[9] = e2;
    e1 = cx * cy * 65536.0f;
    ai[10] = e1 >> 16;
    ai[11] = 0;
    af[10] = e1;
    af[11] = 0;
    ai[12] = 0;
    ai[13] = 0;
    af[12] = 0;
    af[13] = 0;
    ai[14] = 0;
    ai[15] = 1;
    af[14] = 0;
    af[15] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/89510", func_80088A70_main);
#endif
