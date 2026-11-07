#include "guint.h"

extern float D_800A3F80_main; /* dtor */
extern float sinf(float x);
extern float cosf(float x);

void func_8007E0C0_main(float mf[4][4], float a, float x, float y, float z) { /* guRotateF */
    float sine;
    float cosine;
    float ab, bc, ca, t;
    float xxsine;
    float yxsine;
    float zxsine;

    guNormalize(&x, &y, &z);

    a *= D_800A3F80_main;

    sine = sinf(a);
    cosine = cosf(a);

    t = (1 - cosine);
    ab = x * y * t;
    bc = y * z * t;
    ca = z * x * t;

    guMtxIdentF(mf);

    xxsine = x * sine;
    yxsine = y * sine;
    zxsine = z * sine;

    t = x * x;
    mf[0][0] = t + cosine * (1 - t);
    mf[2][1] = bc - xxsine;
    mf[1][2] = bc + xxsine;

    t = y * y;
    mf[1][1] = t + cosine * (1 - t);
    mf[2][0] = ca + yxsine;
    mf[0][2] = ca - yxsine;

    t = z * z;
    mf[2][2] = t + cosine * (1 - t);
    mf[1][0] = ab - zxsine;
    mf[0][1] = ab + zxsine;
}

void func_8007E220_main(Mtx *m, float a, float x, float y, float z) { /* guRotate */
    Matrix mf;

    func_8007E0C0_main(mf, a, x, y, z);
    guMtxF2L(mf, m);
}
