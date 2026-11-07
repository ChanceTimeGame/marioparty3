#include "common.h"

typedef f32 Matrix4f[4][4];

void func_8008D2C0_main(Matrix4f mf, u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);

/* guPerspective (Hudson's copy): func_8008D2C0_main, then to fixed point */
void func_80088520_main(Mtx* m, u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale) {
    Matrix4f mf;

    func_8008D2C0_main(mf, perspNorm, fovy, aspect, near, far, scale);
    func_800898F0_main((Mtx*)mf, m);
}
