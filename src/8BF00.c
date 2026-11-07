#include "common.h"
#include "math.h"

/* func_8008B0E0_main built straight into the fixed-point Mtx: rotation of angle degrees whose local
   z axis is turned onto dir (normalised here); the nine s15.16 elements are computed first, then
   packed into integer and fraction halves. Nothing is written when dir is zero. */
// scheduling: retail schedules the prologue into the body (as the libhmath units); logic checked
// against the asm.
#ifdef NON_MATCHING
void func_8008B300_main(Mtx* m, f32 angle, Vec* dir) {
    f32 x, y, z;
    f32 len, inv;
    f32 xz;
    f32 sine, cosine;
    f32 nz, sy, cy;
    s32 e[9];

    x = dir->x;
    y = dir->y;
    z = dir->z;
    len = HuSqrtf((x * x) + (y * y) + (z * z));
    if (len != 0.0f) {
        inv = 1.0f / len;
        x *= inv;
        z *= inv;
        y *= inv;
        xz = HuSqrtf((x * x) + (z * z));
        sincosdf(angle, &sine, &cosine);
        if (xz == 0.0f) {
            e[0] = cosine * 65536.0f;
            e[1] = 0;
            e[2] = sine * y * 65536.0f;
            e[3] = -sine * 65536.0f;
            e[4] = 0;
            e[5] = cosine * y * 65536.0f;
            e[6] = 0;
            e[7] = -y * 65536.0f;
            e[8] = 0;
        } else {
            inv = 1.0f / xz;
            nz = -z;
            sy = sine * y;
            cy = cosine * y;
            e[0] = ((nz * cosine) - (sy * x)) * inv * 65536.0f;
            e[1] = sine * xz * 65536.0f;
            e[2] = ((cosine * x) - (sy * z)) * inv * 65536.0f;
            e[3] = ((z * sine) - (cy * x)) * inv * 65536.0f;
            e[4] = cosine * xz * 65536.0f;
            e[5] = ((-sine * x) - (cy * z)) * inv * 65536.0f;
            e[6] = -x * 65536.0f;
            e[7] = -y * 65536.0f;
            e[8] = nz * 65536.0f;
        }
        m->m[0][0] = (e[0] & 0xFFFF0000) | ((e[1] >> 16) & 0xFFFF);
        m->m[0][1] = e[2] & 0xFFFF0000;
        m->m[0][2] = (e[3] & 0xFFFF0000) | ((e[4] >> 16) & 0xFFFF);
        m->m[0][3] = e[5] & 0xFFFF0000;
        m->m[1][0] = (e[6] & 0xFFFF0000) | ((e[7] >> 16) & 0xFFFF);
        m->m[1][1] = e[8] & 0xFFFF0000;
        m->m[1][2] = 0;
        m->m[1][3] = 1;
        m->m[2][0] = ((e[0] << 16) & 0xFFFF0000) | (e[1] & 0xFFFF);
        m->m[2][1] = (e[2] << 16) & 0xFFFF0000;
        m->m[2][2] = ((e[3] << 16) & 0xFFFF0000) | (e[4] & 0xFFFF);
        m->m[2][3] = (e[5] << 16) & 0xFFFF0000;
        m->m[3][0] = ((e[6] << 16) & 0xFFFF0000) | (e[7] & 0xFFFF);
        m->m[3][1] = (e[8] << 16) & 0xFFFF0000;
        m->m[3][2] = 0;
        m->m[3][3] = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/8BF00", func_8008B300_main);
#endif
