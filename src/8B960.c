#include "common.h"
#include "math.h"

/* func_8008ABA0_main's scale-rotate-translate matrix built straight into the fixed-point Mtx: the
   twelve s15.16 elements of the upper 4x3 are computed first, then packed into integer and
   fraction halves (as guMtxF2L). */
// scheduling: masked 95 at the right count (227); logic checked against the asm.
#ifdef NON_MATCHING
void func_8008AD60_main(Mtx* m, Vec* rpy, Vec* scale, Vec* pos) {
    f32 sr, cr, sp, cp, sh, ch;
    f32 srsp, crsp;
    f32 sx, sy, sz;
    s32 e[12];

    sincosdf(rpy->x, &sr, &cr);
    sincosdf(rpy->y, &sp, &cp);
    sincosdf(rpy->z, &sh, &ch);
    srsp = sr * sp;
    crsp = cr * sp;
    sx = scale->x;
    sy = scale->y;
    sz = scale->z;
    e[0] = sx * (cp * ch) * 65536.0f;
    e[1] = sy * (cp * sh) * 65536.0f;
    e[2] = sz * -sp * 65536.0f;
    e[3] = sx * ((srsp * ch) - (cr * sh)) * 65536.0f;
    e[4] = sy * ((srsp * sh) + (cr * ch)) * 65536.0f;
    e[5] = sz * (sr * cp) * 65536.0f;
    e[6] = sx * ((crsp * ch) + (sr * sh)) * 65536.0f;
    e[7] = sy * ((crsp * sh) - (sr * ch)) * 65536.0f;
    e[8] = sz * (cr * cp) * 65536.0f;
    e[9] = pos->x * 65536.0f;
    e[10] = pos->y * 65536.0f;
    e[11] = pos->z * 65536.0f;
    m->m[0][0] = (e[0] & 0xFFFF0000) | ((e[1] >> 16) & 0xFFFF);
    m->m[0][1] = e[2] & 0xFFFF0000;
    m->m[0][2] = (e[3] & 0xFFFF0000) | ((e[4] >> 16) & 0xFFFF);
    m->m[0][3] = e[5] & 0xFFFF0000;
    m->m[1][0] = (e[6] & 0xFFFF0000) | ((e[7] >> 16) & 0xFFFF);
    m->m[1][1] = e[8] & 0xFFFF0000;
    m->m[1][2] = (e[9] & 0xFFFF0000) | ((e[10] >> 16) & 0xFFFF);
    m->m[1][3] = (e[11] & 0xFFFF0000) | 1;
    m->m[2][0] = ((e[0] << 16) & 0xFFFF0000) | (e[1] & 0xFFFF);
    m->m[2][1] = (e[2] << 16) & 0xFFFF0000;
    m->m[2][2] = ((e[3] << 16) & 0xFFFF0000) | (e[4] & 0xFFFF);
    m->m[2][3] = (e[5] << 16) & 0xFFFF0000;
    m->m[3][0] = ((e[6] << 16) & 0xFFFF0000) | (e[7] & 0xFFFF);
    m->m[3][1] = (e[8] << 16) & 0xFFFF0000;
    m->m[3][2] = ((e[9] << 16) & 0xFFFF0000) | (e[10] & 0xFFFF);
    m->m[3][3] = (e[11] << 16) & 0xFFFF0000;
}
#else
INCLUDE_ASM("asm/nonmatchings/8B960", func_8008AD60_main);
#endif

/* Rotation of angle degrees whose local z axis is turned onto the direction dir (normalised here);
   nothing is written when dir is zero. */
// scheduling: retail schedules the prologue into the body (as the libhmath units) and keeps 1.0f
// in s1; masked 79. Logic checked against the asm.
#ifdef NON_MATCHING
void func_8008B0E0_main(HuMtx4F m, f32 angle, Vec* dir) {
    f32 x, y, z;
    f32 len, inv;
    f32 xz;
    f32 sine, cosine;
    f32 nz, cy;

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
            m[0][0] = cosine;
            m[2][0] = 0.0f;
            m[1][0] = -sine;
            m[0][1] = 0.0f;
            m[1][1] = 0.0f;
            m[2][2] = 0.0f;
            m[2][1] = -y;
            m[0][2] = sine * y;
            m[1][2] = cosine * y;
        } else {
            inv = 1.0f / xz;
            nz = -z;
            m[0][0] = ((nz * cosine) - (sine * y * x)) * inv;
            cy = cosine * y;
            m[2][2] = nz;
            m[0][1] = sine * xz;
            m[1][1] = cosine * xz;
            m[2][1] = -y;
            m[1][0] = ((z * sine) - (cy * x)) * inv;
            m[2][0] = -x;
            m[1][2] = ((-sine * x) - (cy * z)) * inv;
            m[0][2] = ((cosine * x) - (sine * y * z)) * inv;
        }
        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
        m[2][3] = 0.0f;
        m[3][3] = 1.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/8B960", func_8008B0E0_main);
#endif
