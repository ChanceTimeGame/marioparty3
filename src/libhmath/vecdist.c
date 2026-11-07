#include "common.h"
#include "math.h"

// scheduling: retail moves the prologue after the subtractions and multiplies, which KMC GCC
// 2.7.2 never does (its prologue is emitted as text, not scheduled RTL); logic checked (masked 4)
#ifdef NON_MATCHING
f32 HuVecDistance(Vec *a, Vec *b) {
    f32 x;
    f32 y;
    f32 z;

    x = a->x - b->x;
    y = a->y - b->y;
    z = a->z - b->z;
    return HuSqrtf((x * x) + (y * y) + (z * z));
}
#else
INCLUDE_ASM("asm/nonmatchings/libhmath/vecdist", HuVecDistance);
#endif
