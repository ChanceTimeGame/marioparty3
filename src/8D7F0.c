#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

// NON_MATCHING: scheduling only, two add.s placed after the counter updates in retail (masked 8)
#ifdef NON_MATCHING
/* dst = src * guTranslateF(t): each row gains its w times t (dst may be src) */
void func_8008CBF0_main(Matrix4f src, Vec* t, Matrix4f dst) {
    s32 i = 0;
    f32 a;
    f32 b;
    f32 c;
    f32 w;
    f32 x = t->x;
    f32 y = t->y;
    f32 z = t->z;

    for (; i < 4; i++) {
        w = src[i][3];
        a = src[i][0] + w * x;
        b = src[i][1] + w * y;
        c = src[i][2] + w * z;
        dst[i][3] = w;
        dst[i][0] = a;
        dst[i][1] = b;
        dst[i][2] = c;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/8D7F0", func_8008CBF0_main);
#endif
