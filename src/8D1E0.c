#include "common.h"
#include "math.h"

/* s15.16 element (row, col) of a fixed-point Mtx: integer half in the first 16 halfwords, fraction
   half in the last 16 (the guMtxL2F layout). */
#define MTXL_GET(mtx, row, col)                                                                     \
    ((col) & 1 ? (((mtx)->m[(row) / 2][((row) & 1) * 2 + (col) / 2] << 16) & 0xFFFF0000) |           \
                     (mtx)->m[(row) / 2 + 2][((row) & 1) * 2 + (col) / 2] & 0xFFFF                   \
               : ((mtx)->m[(row) / 2][((row) & 1) * 2 + (col) / 2] & 0xFFFF0000) |                   \
                     (((mtx)->m[(row) / 2 + 2][((row) & 1) * 2 + (col) / 2] >> 16) & 0xFFFF))
#define MTXL_SET(mtx, row, col, e0, e1)                                                             \
    ((mtx)->m[(row) / 2][((row) & 1) * 2 + (col) / 2] = ((e0) & 0xFFFF0000) | (((e1) >> 16) & 0xFFFF), \
     (mtx)->m[(row) / 2 + 2][((row) & 1) * 2 + (col) / 2] = (((e0) << 16) & 0xFFFF0000) | ((e1) & 0xFFFF))

/* dst = src rotated by angle degrees about z (rows 0 and 1 mixed, row 2 kept, the translation row
   copied as is), all in fixed point. src and dst may be the same matrix: every element is read
   before any is written, except the copied row. */
// scheduling: retail schedules the prologue into the body (as the libhmath units) and keeps the
// unpacked elements in stack temporaries; logic checked against the asm.
#ifdef NON_MATCHING
void func_8008C5E0_main(Mtx* src, f32 angle, Mtx* dst) {
    f32 sine, cosine;
    HuMtx4F f;
    s32 row, col;
    s32 e0, e1;

    sincosdf(angle, &sine, &cosine);
    dst->m[1][2] = src->m[1][2];
    dst->m[1][3] = src->m[1][3];
    dst->m[3][2] = src->m[3][2];
    dst->m[3][3] = src->m[3][3];
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 4; col++) {
            f[row][col] = (f32)MTXL_GET(src, row, col) * (1.0f / 65536.0f);
        }
    }
    for (col = 0; col < 4; col++) {
        f32 a = f[0][col];
        f32 b = f[1][col];

        f[0][col] = (a * cosine) + (b * sine);
        f[1][col] = (b * cosine) - (a * sine);
    }
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 4; col += 2) {
            e0 = f[row][col] * 65536.0f;
            e1 = f[row][col + 1] * 65536.0f;
            MTXL_SET(dst, row, col, e0, e1);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/8D1E0", func_8008C5E0_main);
#endif
