#include "common.h"
#include "math.h"

/* Hudson's gu matrix builders: guRotateF about an axis, guScaleF, guScale, guTranslateF, guTranslate
   (MP2 src/B28C0.c; the float versions from MP1 src/9EC60.c and 9F4F0.c). guScale and guTranslate
   build the fixed-point Mtx directly: integer halves in m[0..1], fractions in m[2..3]. */

typedef f32 Matrix4f[4][4];

/* guRotateF without the degree conversion (sincosdf takes degrees); leaves mf[3][3] alone */
void func_80088570_main(Matrix4f mf, f32 a, f32 x, f32 y, f32 z) {
    f32 sine;
    f32 cosine;
    f32 xx;
    f32 yy;
    f32 zz;
    f32 ab;
    f32 bc;
    f32 ca;
    f32 t;

    t = 1.0f / HuSqrtf(x * x + y * y + z * z);
    x *= t;
    y *= t;
    z *= t;
    xx = x * x;
    yy = y * y;
    zz = z * z;
    sincosdf(a, &sine, &cosine);
    t = 1.0f - cosine;
    ab = x * y * t;
    bc = y * z * t;
    ca = z * x * t;
    x *= sine;
    y *= sine;
    z *= sine;
    mf[0][0] = xx + cosine * (1.0f - xx);
    mf[2][1] = bc - x;
    mf[1][2] = bc + x;
    mf[1][1] = yy + cosine * (1.0f - yy);
    mf[2][0] = ca + y;
    mf[0][2] = ca - y;
    mf[2][2] = zz + cosine * (1.0f - zz);
    mf[1][0] = ab - z;
    mf[0][1] = ab + z;
    mf[3][0] = mf[0][3] = mf[1][3] = mf[2][3] = mf[3][1] = mf[3][2] = 0.0f;
}

/* guScaleF */
void func_80088700_main(Matrix4f mf, f32 x, f32 y, f32 z) {
    mf[0][0] = x;
    mf[1][1] = y;
    mf[2][2] = z;
    mf[0][1] = mf[0][2] = mf[0][3] = mf[1][0] = mf[1][2] = mf[1][3] = mf[2][0] = mf[2][1] = mf[2][3] = mf[3][0] =
        mf[3][1] = mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;
}

/* guScale */
void func_80088750_main(Mtx* m, f32 x, f32 y, f32 z) {
    s32 e1;
    s32 e2;
    s32 e3;

    e1 = x * 65536.0f;
    e2 = y * 65536.0f;
    e3 = z * 65536.0f;
    m->m[0][0] = e1 & 0xFFFF0000;
    m->m[0][1] = 0;
    m->m[0][2] = (e2 >> 16) & 0xFFFF;
    m->m[0][3] = 0;
    m->m[1][0] = 0;
    m->m[1][1] = e3 & 0xFFFF0000;
    m->m[1][2] = 0;
    m->m[1][3] = 1;
    m->m[2][0] = (e1 << 16) & 0xFFFF0000;
    m->m[2][1] = 0;
    m->m[2][2] = e2 & 0xFFFF;
    m->m[2][3] = 0;
    m->m[3][0] = 0;
    m->m[3][1] = (e3 << 16) & 0xFFFF0000;
    m->m[3][2] = 0;
    m->m[3][3] = 0;
}

/* guTranslateF */
void func_80088800_main(Matrix4f mf, f32 x, f32 y, f32 z) {
    mf[3][0] = x;
    mf[3][1] = y;
    mf[3][2] = z;
    mf[0][0] = mf[1][1] = mf[2][2] = mf[3][3] = 1.0f;
    mf[0][1] = mf[0][2] = mf[0][3] = mf[1][0] = mf[1][2] = mf[1][3] = mf[2][0] = mf[2][1] = mf[2][3] = 0.0f;
}

/* guTranslate */
void func_80088850_main(Mtx* m, f32 x, f32 y, f32 z) {
    s32 e1;
    s32 e2;
    s32 e3;

    e1 = x * 65536.0f;
    e2 = y * 65536.0f;
    e3 = z * 65536.0f;
    m->m[0][0] = 0x10000;
    m->m[0][1] = 0;
    m->m[0][2] = 1;
    m->m[0][3] = 0;
    m->m[1][0] = 0;
    m->m[1][1] = 0x10000;
    m->m[1][2] = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
    m->m[1][3] = (e3 & 0xFFFF0000) | 1;
    m->m[2][0] = 0;
    m->m[2][1] = 0;
    m->m[2][2] = 0;
    m->m[2][3] = 0;
    m->m[3][0] = 0;
    m->m[3][1] = 0;
    m->m[3][2] = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
    m->m[3][3] = (e3 << 16) & 0xFFFF0000;
}
