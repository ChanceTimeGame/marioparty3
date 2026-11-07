#include "common.h"
#include "math.h"

/* func_80089190_main written straight into the fixed-point Mtx: the rotation that turns the direction
   (x, y, z) onto -z, rolled by a degrees; a zero direction leaves m untouched */
void func_800893B0_main(Mtx* m, f32 a, f32 x, f32 y, f32 z) {
    s32 e[9];
    f32 sine;
    f32 cosine;
    f32 len;
    f32 xz;
    f32 ixz;

    len = HuSqrtf(x * x + y * y + z * z);
    if (len == 0.0f) {
        return;
    }
    len = 1.0f / len;
    x *= len;
    y *= len;
    z *= len;
    xz = HuSqrtf(x * x + z * z);
    sincosdf(a, &sine, &cosine);
    if (xz != 0.0f) {
        ixz = 1.0f / xz;
        e[0] = (-z * cosine - sine * y * x) * ixz * 65536.0f;
        e[1] = sine * xz * 65536.0f;
        e[2] = (cosine * x - sine * y * z) * ixz * 65536.0f;
        e[3] = (z * sine - cosine * y * x) * ixz * 65536.0f;
        e[4] = cosine * xz * 65536.0f;
        e[5] = (-sine * x - cosine * y * z) * ixz * 65536.0f;
        e[6] = -x * 65536.0f;
        e[7] = -y * 65536.0f;
        e[8] = -z * 65536.0f;
    } else {
        e[0] = cosine * 65536.0f;
        e[1] = 0;
        e[2] = sine * y * 65536.0f;
        e[3] = -sine * 65536.0f;
        e[4] = 0;
        e[5] = cosine * y * 65536.0f;
        e[6] = 0;
        e[7] = -y * 65536.0f;
        e[8] = 0;
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
