#include "common.h"

typedef f32 Matrix4f[4][4];

typedef struct {
    f32 fovy;
    f32 aspect;
    f32 near;
    f32 far;
    f32 scale;
} PerspParams;

void func_8008D5D0_main(Matrix4f mf, u16* perspNorm, PerspParams* p);

/* guPerspective: func_8008D5D0_main, then to fixed point */
void func_8008A030_main(Mtx* m, u16* perspNorm, PerspParams* p) {
    Matrix4f mf;

    func_8008D5D0_main(mf, perspNorm, p);
    func_800898F0_main((Mtx*)mf, m);
}
