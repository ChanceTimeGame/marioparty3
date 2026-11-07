#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

/* dst = guRotateXF(angle) * src: rows 1 and 2 of src rotated into each other (angle in degrees);
   dst may be src */
// NON_MATCHING: retail reads every element before the first store and moves some through integer
// registers (98 instructions here, 100 in retail; masked 69)
#ifdef NON_MATCHING
void func_8008B6B0_main(Matrix4f src, f32 angle, Matrix4f dst) {
    f32 sine;
    f32 cosine;
    f32 m10;
    f32 m11;
    f32 m12;
    f32 m13;
    f32 m20;
    f32 m21;
    f32 m22;
    f32 m23;

    sincosdf(angle, &sine, &cosine);
    m10 = src[1][0] * cosine + src[2][0] * sine;
    m11 = src[1][1] * cosine + src[2][1] * sine;
    m12 = src[1][2] * cosine + src[2][2] * sine;
    m13 = src[1][3] * cosine + src[2][3] * sine;
    m20 = src[2][0] * cosine - src[1][0] * sine;
    m21 = src[2][1] * cosine - src[1][1] * sine;
    m22 = src[2][2] * cosine - src[1][2] * sine;
    m23 = src[2][3] * cosine - src[1][3] * sine;
    dst[0][0] = src[0][0];
    dst[0][1] = src[0][1];
    dst[0][2] = src[0][2];
    dst[0][3] = src[0][3];
    dst[1][0] = m10;
    dst[1][1] = m11;
    dst[1][2] = m12;
    dst[1][3] = m13;
    dst[2][0] = m20;
    dst[2][1] = m21;
    dst[2][2] = m22;
    dst[2][3] = m23;
    dst[3][0] = src[3][0];
    dst[3][1] = src[3][1];
    dst[3][2] = src[3][2];
    dst[3][3] = src[3][3];
}
#else
INCLUDE_ASM("asm/nonmatchings/8C2B0", func_8008B6B0_main);
#endif
