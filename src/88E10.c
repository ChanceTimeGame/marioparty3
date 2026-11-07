#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

/* guLookAtF: Hudson's copy, from MP2 src/B24A0.c func_800B1960_B2560 (MP1 src/9CE40.c HuGuLookAtF,
   NON_MATCHING in both). Retail inlines HuVecNormalize (src/libhmath/vecnorm.c) for the three
   normalisations, so the look, right and up vectors live in memory. */
// NON_MATCHING: retail loads xUp/yUp/zUp and interleaves the prologue differently
// (165 instructions; this builds 160).
#ifdef NON_MATCHING
static inline void guLookAtF_Normalize(f32 *x, f32 *y, f32 *z) {
    f32 oldX;
    f32 oldY;
    f32 oldZ;
    f32 invMag;

    oldX = *x;
    oldY = *y;
    oldZ = *z;
    invMag = 1.0f / HuSqrtf((oldX * oldX) + (oldY * oldY) + (oldZ * oldZ));

    *x *= invMag;
    *y *= invMag;
    *z *= invMag;
}

void guLookAtF(Matrix4f matrix, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp,
               f32 zUp) {
    f32 xLook;
    f32 yLook;
    f32 zLook;
    f32 xRight;
    f32 yRight;
    f32 zRight;

    xLook = xEye - xAt;
    yLook = yEye - yAt;
    zLook = zEye - zAt;
    guLookAtF_Normalize(&xLook, &yLook, &zLook);
    matrix[0][2] = xLook;
    matrix[1][2] = yLook;
    matrix[2][2] = zLook;
    matrix[3][2] = -(xEye * xLook + yEye * yLook + zEye * zLook);
    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    guLookAtF_Normalize(&xRight, &yRight, &zRight);
    matrix[0][0] = xRight;
    matrix[1][0] = yRight;
    matrix[2][0] = zRight;
    matrix[3][0] = -(xEye * xRight + yEye * yRight + zEye * zRight);
    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    guLookAtF_Normalize(&xUp, &yUp, &zUp);
    matrix[0][1] = xUp;
    matrix[1][1] = yUp;
    matrix[2][1] = zUp;
    matrix[3][1] = -(xEye * xUp + yEye * yUp + zEye * zUp);
    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/88E10", guLookAtF);
#endif
