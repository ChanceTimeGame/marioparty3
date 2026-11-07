#include "common.h"
#include "math.h"

/* guRotateZ (degrees) straight into the fixed-point Mtx: the s15.16 cosine and sine are parked in
   m[1][1] and m[1][3] while the integer and fraction halves are assembled. */
void func_8008A4C0_main(Mtx* m, f32 angle) {
    f32 sine;
    f32 cosine;

    sincosdf(angle, &sine, &cosine);
    m->m[1][1] = cosine * 65536.0f;
    m->m[1][3] = sine * 65536.0f;
    m->m[0][2] = (-m->m[1][3] & 0xFFFF0000) | ((m->m[1][1] >> 16) & 0xFFFF);
    m->m[2][2] = ((-m->m[1][3] << 16) & 0xFFFF0000) | (m->m[1][1] & 0xFFFF);
    m->m[0][0] = (m->m[1][1] & 0xFFFF0000) | ((m->m[1][3] >> 16) & 0xFFFF);
    m->m[2][0] = ((m->m[1][1] << 16) & 0xFFFF0000) | (m->m[1][3] & 0xFFFF);
    m->m[0][1] = m->m[0][3] = m->m[1][0] = m->m[1][2] = m->m[2][1] = m->m[2][3] = m->m[3][0] =
        m->m[3][1] = m->m[3][2] = m->m[3][3] = 0;
    m->m[1][1] = 0x10000;
    m->m[1][3] = 1;
}
