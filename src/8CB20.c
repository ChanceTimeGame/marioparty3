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

/* dst = src rotated by angle degrees about y (rows 0 and 2 mixed, row 1 kept, the translation row
   copied as is), all in fixed point. src and dst may be the same matrix: every element is read
   before any is written, except the copied row. */
// scheduling: retail schedules the prologue into the body (as the libhmath units) and keeps the
// unpacked elements in stack temporaries; logic checked against the asm.
#ifdef NON_MATCHING
void func_8008BF20_main(Mtx* src, f32 angle, Mtx* dst) {
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
        f32 b = f[2][col];

        f[0][col] = (a * cosine) - (b * sine);
        f[2][col] = (a * sine) + (b * cosine);
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
INCLUDE_ASM("asm/nonmatchings/8CB20", func_8008BF20_main);
#endif

/* dst = src rotated by angle degrees about z (rows 0 and 1 mixed, rows 2 and 3 copied), float
   matrices; src and dst may be the same. */
// scheduling: retail schedules the prologue into the body (as the libhmath units); logic checked
// against the asm.
#ifdef NON_MATCHING
void func_8008C450_main(HuMtx4F src, f32 angle, HuMtx4F dst) {
    f32 sine, cosine;
    f32 a0, a1, a2, a3;
    f32 b0, b1, b2, b3;

    sincosdf(angle, &sine, &cosine);
    a0 = src[0][0];
    a1 = src[0][1];
    a2 = src[0][2];
    a3 = src[0][3];
    b0 = src[1][0];
    b1 = src[1][1];
    b2 = src[1][2];
    b3 = src[1][3];
    dst[2][0] = src[2][0];
    dst[2][1] = src[2][1];
    dst[2][2] = src[2][2];
    dst[2][3] = src[2][3];
    dst[3][0] = src[3][0];
    dst[3][1] = src[3][1];
    dst[3][2] = src[3][2];
    dst[3][3] = src[3][3];
    dst[0][0] = (a0 * cosine) + (b0 * sine);
    dst[0][1] = (a1 * cosine) + (b1 * sine);
    dst[0][2] = (a2 * cosine) + (b2 * sine);
    dst[0][3] = (a3 * cosine) + (b3 * sine);
    dst[1][0] = (b0 * cosine) - (a0 * sine);
    dst[1][1] = (b1 * cosine) - (a1 * sine);
    dst[1][2] = (b2 * cosine) - (a2 * sine);
    dst[1][3] = (b3 * cosine) - (a3 * sine);
}
#else
INCLUDE_ASM("asm/nonmatchings/8CB20", func_8008C450_main);
#endif
