#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

/* guRotateXF (Hudson), from MP2 src/B4470.c (MP1 src/A4770.c) */
void func_8008A120_main(Matrix4f m, f32 angle) {
    sincosdf(angle, &m[1][2], &m[1][1]);
    m[2][1] = -m[1][2];
    m[2][2] = m[1][1];
    m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][3] = m[2][0] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[0][0] = m[3][3] = 1.0f;
}
