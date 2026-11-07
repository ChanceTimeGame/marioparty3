#include "common.h"

typedef f32 Matrix4f[4][4];

/* guMtxL2F (Hudson's copy), from MP2 src/B3CD0.c (MP1 src/A1620.c) */
void func_80089980_main(Matrix4f mf, Mtx* m) {
    s32 i;
    s32 j;
    u16* ai;
    u16* af;

    ai = (u16*)m;
    af = (u16*)((u8*)m + 0x20);
    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++) {
            mf[i][j * 2] = (s32)((*ai << 16) | *af) * (1.0f / 65536.0f);
            *(&mf[i][j * 2] + 1) = (s32)((*(ai + 1) << 16) | *(af + 1)) * (1.0f / 65536.0f);
            ai += 2;
            af += 2;
        }
}
