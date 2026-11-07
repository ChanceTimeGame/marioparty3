#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

/* guRotateRPYF (as 89510.c's func_80088910_main) with the angles, in degrees, taken from a Vec */
// NON_MATCHING: prologue scheduling only, the first angle load sits among the register saves (raw 4)
#ifdef NON_MATCHING
void func_8008A7F0_main(Matrix4f m, Vec* angles) {
    f32 sx;
    f32 cx;
    f32 sy;
    f32 cy;
    f32 sz;
    f32 cz;

    sincosdf(angles->x, &sx, &cx);
    sincosdf(angles->y, &sy, &cy);
    sincosdf(angles->z, &sz, &cz);
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
#else
INCLUDE_ASM("asm/nonmatchings/8B3F0", func_8008A7F0_main);
#endif
