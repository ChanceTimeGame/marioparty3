#include "common.h"
#include "math.h"

// https://decomp.me/scratch/6UMIQ
// scheduling: retail interleaves the prologue's register saves with the loads, which KMC GCC
// 2.7.2 never does (its prologue is emitted as text, not scheduled RTL); logic checked
#ifdef NON_MATCHING
void HuVecNormalize3F(Vec *vec) {
    f32 x;
    f32 y;
    f32 z;
    f32 invMag;

    x = vec->x;
    y = vec->y;
    z = vec->z;
    invMag = 1.0f / HuSqrtf((x * x) + (y * y) + (z * z));

    vec->x = invMag * x;
    vec->y = invMag * y;
    vec->z = invMag * z;
}
#else
INCLUDE_ASM("asm/nonmatchings/libhmath/vecnorm3f", HuVecNormalize3F);
#endif
