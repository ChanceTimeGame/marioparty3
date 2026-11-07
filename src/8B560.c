#include "common.h"
#include "math.h"

/* guRotateRPY (degrees) straight into the fixed-point Mtx: each s15.16 element's integer half goes
   to the first 16 halfwords and its fraction half to the last 16. */
// scheduling: masked 71 at 150 vs 147 instructions (retail computes cp*sh before the first store
// and reuses fewer temporaries); logic checked against the asm.
#ifdef NON_MATCHING
void func_8008A960_main(Mtx* m, Vec* rpy) {
    f32 sr, cr, sp, cp, sh, ch;
    s16* h = (s16*)m;
    s32 e;
    f32 srsp, crsp;

    sincosdf(rpy->x, &sr, &cr);
    sincosdf(rpy->y, &sp, &cp);
    sincosdf(rpy->z, &sh, &ch);
    e = cp * ch * 65536.0f;
    h[0] = e >> 16;
    h[16] = e;
    h[3] = h[19] = h[7] = h[23] = h[11] = h[27] = 0;
    e = cp * sh * 65536.0f;
    h[1] = e >> 16;
    h[17] = e;
    e = -sp * 65536.0f;
    h[2] = e >> 16;
    h[18] = e;
    srsp = sr * sp;
    e = (srsp * ch - cr * sh) * 65536.0f;
    h[4] = e >> 16;
    h[20] = e;
    e = (srsp * sh + cr * ch) * 65536.0f;
    h[5] = e >> 16;
    h[21] = e;
    e = sr * cp * 65536.0f;
    h[6] = e >> 16;
    h[22] = e;
    crsp = cr * sp;
    e = (crsp * ch + sr * sh) * 65536.0f;
    h[8] = e >> 16;
    h[24] = e;
    e = (crsp * sh - sr * ch) * 65536.0f;
    h[9] = e >> 16;
    h[25] = e;
    e = cr * cp * 65536.0f;
    h[10] = e >> 16;
    h[26] = e;
    h[12] = h[13] = h[28] = h[29] = h[14] = 0;
    h[15] = 1;
    h[30] = h[31] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/8B560", func_8008A960_main);
#endif

/* Float matrix of guRotateRPYF (degrees) with each column scaled by scale and pos in the last
   row: scale, then rotate, then translate. */
// scheduling: masked 44 at 117 vs 113 instructions (retail loads scale->y/z after the first
// store); logic checked against the asm.
#ifdef NON_MATCHING
void func_8008ABA0_main(HuMtx4F m, Vec* rpy, Vec* scale, Vec* pos) {
    f32 sr, cr, sp, cp, sh, ch;
    f32 srsp, crsp;
    f32 sx, sy, sz;

    sincosdf(rpy->x, &sr, &cr);
    sincosdf(rpy->y, &sp, &cp);
    sincosdf(rpy->z, &sh, &ch);
    sx = scale->x;
    sy = scale->y;
    sz = scale->z;
    m[0][0] = sx * (cp * ch);
    srsp = sr * sp;
    crsp = cr * sp;
    m[0][1] = sy * (cp * sh);
    m[0][2] = sz * -sp;
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[1][0] = sx * ((srsp * ch) - (cr * sh));
    m[1][1] = sy * ((srsp * sh) + (cr * ch));
    m[1][2] = sz * (sr * cp);
    m[2][0] = sx * ((crsp * ch) + (sr * sh));
    m[2][1] = sy * ((crsp * sh) - (sr * ch));
    m[2][2] = sz * (cr * cp);
    m[3][0] = pos->x;
    m[3][1] = pos->y;
    m[3][2] = pos->z;
    m[3][3] = 1.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/8B560", func_8008ABA0_main);
#endif
