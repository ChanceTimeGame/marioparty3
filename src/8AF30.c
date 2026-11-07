#include "common.h"
#include "math.h"

/* guRotateY (degrees) straight into the fixed-point Mtx: the s15.16 cosine, -sine and sine are
   parked in m[0][0], m[0][1] and m[1][0] while the integer and fraction halves are assembled. */
// frame: retail's frame is 8 bytes larger (locals take 16 bytes, sine and cosine at the bottom);
// no scalar layout found that reproduces it, and a local array changes the scheduling. Logic
// checked against the asm.
#ifdef NON_MATCHING
void func_8008A330_main(Mtx* m, f32 angle) {
    f32 sine;
    f32 cosine;

    sincosdf(angle, &sine, &cosine);
    m->m[0][0] = cosine * 65536.0f;
    m->m[1][0] = sine * 65536.0f;
    m->m[0][1] = -m->m[1][0];
    m->m[0][2] = m->m[1][3] = 1;
    m->m[2][0] = m->m[0][0] << 16;
    m->m[0][3] = m->m[2][2] = m->m[2][3] = m->m[1][2] = m->m[3][2] = m->m[3][3] = 0;
    m->m[2][1] = m->m[0][1] << 16;
    m->m[1][1] = m->m[0][0] & 0xFFFF0000;
    m->m[3][1] = (m->m[0][0] << 16) & 0xFFFF0000;
    m->m[0][0] &= 0xFFFF0000;
    m->m[0][1] &= 0xFFFF0000;
    m->m[3][0] = (m->m[1][0] << 16) & 0xFFFF0000;
    m->m[1][0] &= 0xFFFF0000;
}
#else
INCLUDE_ASM("asm/nonmatchings/8AF30", func_8008A330_main);
#endif
