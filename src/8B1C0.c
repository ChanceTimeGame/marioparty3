#include "common.h"
#include "math.h"

/* guScaleF, guScale, guTranslateF and guTranslate taking a Vec (Hudson); the fixed-point versions
   build the Mtx directly as 89170.c does: integer halves in m[0..1], fractions in m[2..3] */

typedef f32 Matrix4f[4][4];

/* guScaleF by v */
void func_8008A5C0_main(Matrix4f mf, Vec* v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 z = v->z;

    mf[0][1] = mf[0][2] = mf[0][3] = mf[1][0] = mf[1][2] = mf[1][3] = mf[2][0] = mf[2][1] = mf[2][3] = mf[3][0] =
        mf[3][1] = mf[3][2] = 0.0f;
    mf[0][0] = x;
    mf[1][1] = y;
    mf[2][2] = z;
    mf[3][3] = 1.0f;
}

/* guScale by v */
void func_8008A620_main(Mtx* m, Vec* v) {
    s32 e1;
    s32 e2;
    s32 e3;

    e1 = v->x * 65536.0f;
    e2 = v->y * 65536.0f;
    e3 = v->z * 65536.0f;
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

/* guTranslateF by v */
void func_8008A6D0_main(Matrix4f mf, Vec* v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 z = v->z;

    mf[0][1] = mf[0][2] = mf[0][3] = mf[1][0] = mf[1][2] = mf[1][3] = mf[2][0] = mf[2][1] = mf[2][3] = 0.0f;
    mf[3][0] = x;
    mf[3][1] = y;
    mf[3][2] = z;
    mf[0][0] = mf[1][1] = mf[2][2] = mf[3][3] = 1.0f;
}

/* guTranslate by v */
// NON_MATCHING: scheduling only, retail emits lui 0x1 (m[0][0]) before the loads (raw 1)
#ifdef NON_MATCHING
void func_8008A730_main(Mtx* m, Vec* v) {
    s32 e1;
    s32 e2;
    s32 e3;

    e1 = v->x * 65536.0f;
    e2 = v->y * 65536.0f;
    e3 = v->z * 65536.0f;
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
#else
INCLUDE_ASM("asm/nonmatchings/8B1C0", func_8008A730_main);
#endif
