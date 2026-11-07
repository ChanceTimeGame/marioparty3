#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

/* guRotateRPYF scaled by s, then translated by (tx, ty, tz): rotation in degrees about x, y, z */
void func_80088CB0_main(Matrix4f m, f32 x, f32 y, f32 z, f32 s, f32 tx, f32 ty, f32 tz) {
    f32 sx;
    f32 cx;
    f32 sy;
    f32 cy;
    f32 sz;
    f32 cz;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    m[0][0] = s * (cy * cz);
    m[0][1] = s * (cy * sz);
    m[0][2] = s * -sy;
    m[1][0] = s * (sx * sy * cz - cx * sz);
    m[1][1] = s * (sx * sy * sz + cx * cz);
    m[1][2] = s * (sx * cy);
    m[2][0] = s * (cx * sy * cz + sx * sz);
    m[2][1] = s * (cx * sy * sz - sx * cz);
    m[2][2] = s * (cx * cy);
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][0] = tx;
    m[3][1] = ty;
    m[3][2] = tz;
    m[3][3] = 1.0f;
}

/* the same as func_80088CB0_main written straight into the fixed-point Mtx: the twelve elements are
   converted into e[] (rows 0-2, columns 0-2, then the translation), then packed into s16 halves */
void func_80088E50_main(Mtx* m, f32 x, f32 y, f32 z, f32 s, f32 tx, f32 ty, f32 tz) {
    f32 sx;
    f32 cx;
    f32 sy;
    f32 cy;
    f32 sz;
    f32 cz;
    s32 e[12];

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    e[0] = s * (cy * cz) * 65536.0f;
    e[1] = s * (cy * sz) * 65536.0f;
    e[2] = s * -sy * 65536.0f;
    e[3] = s * (sx * sy * cz - cx * sz) * 65536.0f;
    e[4] = s * (sx * sy * sz + cx * cz) * 65536.0f;
    e[5] = s * (sx * cy) * 65536.0f;
    e[6] = s * (cx * sy * cz + sx * sz) * 65536.0f;
    e[7] = s * (cx * sy * sz - sx * cz) * 65536.0f;
    e[8] = s * (cx * cy) * 65536.0f;
    e[9] = tx * 65536.0f;
    e[10] = ty * 65536.0f;
    e[11] = tz * 65536.0f;
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

/* a rotation matrix that turns the direction (x, y, z) onto -z (the row 2 is -dir), rolled by a degrees
   about it; a zero direction leaves mf untouched */
void func_80089190_main(Matrix4f mf, f32 a, f32 x, f32 y, f32 z) {
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
        mf[0][0] = (-z * cosine - sine * y * x) * ixz;
        mf[1][0] = (z * sine - cosine * y * x) * ixz;
        mf[2][0] = -x;
        mf[0][1] = sine * xz;
        mf[1][1] = cosine * xz;
        mf[2][1] = -y;
        mf[0][2] = (cosine * x - sine * y * z) * ixz;
        mf[1][2] = (-sine * x - cosine * y * z) * ixz;
        mf[2][2] = -z;
    } else {
        mf[0][0] = cosine;
        mf[1][0] = -sine;
        mf[2][0] = 0.0f;
        mf[0][1] = 0.0f;
        mf[1][1] = 0.0f;
        mf[2][1] = -y;
        mf[0][2] = sine * y;
        mf[1][2] = cosine * y;
        mf[2][2] = 0.0f;
    }
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][3] = 1.0f;
}
