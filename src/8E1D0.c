#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

/* guPerspectiveF parameters */
typedef struct {
    f32 fovy;
    f32 aspect;
    f32 near;
    f32 far;
    f32 scale;
} PerspParams;

/* guPerspectiveF with the scale folded into each element; fovy in degrees. perspNorm may be NULL. */
// NON_MATCHING: prologue scheduling only; retail interleaves the register saves with the fovy load
// (the same unmatched pattern as libhmath's HuVecDistance)
#ifdef NON_MATCHING
void func_8008D5D0_main(Matrix4f mf, u16* perspNorm, PerspParams* p) {
    f32 sine;
    f32 cosine;
    f32 cot;
    f32 near;
    f32 far;
    f32 scale;
    f32 inv;
    f32 sum;
    f32 x;
    f32 z;
    f32 w;

    sincosdf(p->fovy * 0.5f, &sine, &cosine);
    cot = cosine / sine;
    near = p->near;
    far = p->far;
    scale = p->scale;
    inv = scale / (near - far);
    sum = near + far;
    cot *= scale;
    x = cot / p->aspect;
    z = sum * inv;
    w = (near + near) * far * inv;
    mf[0][1] = mf[0][2] = mf[0][3] = mf[1][0] = mf[1][2] = mf[1][3] = mf[2][0] = mf[2][1] = mf[3][0] =
        mf[3][1] = mf[3][3] = 0.0f;
    mf[0][0] = x;
    mf[1][1] = cot;
    mf[2][2] = z;
    mf[2][3] = -scale;
    mf[3][2] = w;
    if (perspNorm != NULL) {
        if (sum <= 2.0f) {
            *perspNorm = 0xFFFF;
        } else {
            *perspNorm = 131072.0f / sum;
            if (*perspNorm == 0) {
                *perspNorm = 1;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/8E1D0", func_8008D5D0_main);
#endif
