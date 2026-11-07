#include "common.h"
#include "math.h"

f32 HuVecDistanceSqr(Vec *a, Vec *b) {
    f32 x;
    f32 y;
    f32 z;

    x = a->x - b->x;
    y = a->y - b->y;
    z = a->z - b->z;

    return (x * x) + (y * y) + (z * z);
}
