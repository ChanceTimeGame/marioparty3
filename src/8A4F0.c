#include "common.h"

typedef f32 Matrix4f[4][4];

/* guMtxF2L (Hudson's copy), from MP2 src/B3C40.c (MP1 src/A1620.c): declared Mtx* in functions.us.h; integer halves first,
   then the fractions. The halves are written as N64 big-endian s16 pairs. */
void func_800898F0_main(Mtx* src, Mtx* m) {
    f32 (*mf)[4] = (f32 (*)[4])src;
    s32 i;
    s32 j;
    s32 e1;
    s32 e2;
    s16* ai;
    u16* af;

    ai = (s16*)m;
    af = (u16*)((u8*)m + 0x20);
    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++) {
            e1 = mf[i][j * 2] * 65536.0f;
            e2 = *(&mf[i][j * 2] + 1) * 65536.0f;
            *ai = e1 >> 16;
            *(ai + 1) = e2 >> 16;
            ai += 2;
            *af = e1;
            *(af + 1) = e2;
            af += 2;
        }
}
