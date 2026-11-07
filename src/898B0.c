#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

/* guRotateRPYF scaled by s, then translated by (tx, ty, tz): rotation in degrees about x, y, z */
void func_80088CB0_main(Matrix4f m, f32 x, f32 y, f32 z, f32 s, f32 tx, f32 ty, f32 tz) {
    f32 sx;
    f32 cx;
    f32 sy;
    f32 cy;
    f32 sz;
    f32 cz;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    m[0][0] = s * (cy * cz);
    m[0][1] = s * (cy * sz);
    m[0][2] = s * -sy;
    m[1][0] = s * (sx * sy * cz - cx * sz);
    m[1][1] = s * (sx * sy * sz + cx * cz);
    m[1][2] = s * (sx * cy);
    m[2][0] = s * (cx * sy * cz + sx * sz);
    m[2][1] = s * (cx * sy * sz - sx * cz);
    m[2][2] = s * (cx * cy);
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][0] = tx;
    m[3][1] = ty;
    m[3][2] = tz;
    m[3][3] = 1.0f;
}

INCLUDE_ASM("asm/nonmatchings/898B0", func_80088E50_main);

INCLUDE_ASM("asm/nonmatchings/898B0", func_80089190_main);
