#include "common.h"
#include "math.h"

/* guRotateX (degrees) straight into the fixed-point Mtx: the s15.16 cosine, sine and -sine are
   parked in m[1][1], m[0][3] and m[3][0] while the integer and fraction halves are assembled. */
// frame and scheduling: retail's frame is 8 bytes larger (locals take 16 bytes, sine and cosine at the bottom);
// no scalar layout found that reproduces it, and a local array changes the scheduling. Logic
// checked against the asm; retail also loads m[1][1] before the sine conversion.
#ifdef NON_MATCHING
void func_8008A1B0_main(Mtx* m, f32 angle) {
    f32 sine;
    f32 cosine;
    s32 s;

    sincosdf(angle, &sine, &cosine);
    m->m[1][1] = cosine * 65536.0f;
    s = sine * 65536.0f;
    m->m[0][3] = s;
    s = -s;
    m->m[3][0] = s;
    m->m[1][0] = (u32)s >> 16;
    m->m[2][3] = m->m[0][3] << 16;
    m->m[0][1] = m->m[2][0] = m->m[2][1] = m->m[1][2] = m->m[3][2] = m->m[3][3] = 0;
    m->m[0][0] = 0x10000;
    m->m[1][3] = 1;
    m->m[3][1] = m->m[1][1] << 16;
    m->m[0][2] = (m->m[1][1] >> 16) & 0xFFFF;
    m->m[2][2] = m->m[1][1] & 0xFFFF;
    m->m[1][1] = m->m[1][1] & 0xFFFF0000;
    m->m[3][0] = m->m[3][0] & 0xFFFF;
    m->m[0][3] = m->m[0][3] & 0xFFFF0000;
}
#else
INCLUDE_ASM("asm/nonmatchings/8ADB0", func_8008A1B0_main);
#endif
