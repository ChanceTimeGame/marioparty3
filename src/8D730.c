#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

/* dst = src * guScaleF(s): each row's x, y and z scaled by s (dst may be src) */
void func_8008CB30_main(Matrix4f src, Vec* s, Matrix4f dst) {
    s32 i = 0;
    f32 a;
    f32 b;
    f32 c;
    f32 w;
    f32 x = s->x;
    f32 y = s->y;
    f32 z = s->z;

    for (; i < 4; i++) {
        a = src[i][0] * x;
        b = src[i][1] * y;
        c = src[i][2] * z;
        w = src[i][3];
        dst[i][3] = w;
        dst[i][0] = a;
        dst[i][1] = b;
        dst[i][2] = c;
    }
}
