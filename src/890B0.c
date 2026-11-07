#include "common.h"

typedef f32 Matrix4f[4][4];

void guLookAtF(Matrix4f mf, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);

/* guLookAt (Hudson's copy): guLookAtF, then the float matrix to fixed point */
void func_800884B0_main(Mtx* m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp) {
    Matrix4f mf;

    guLookAtF(mf, xEye, yEye, zEye, xAt, yAt, zAt, xUp, yUp, zUp);
    func_800898F0_main((Mtx*)mf, m);
}
