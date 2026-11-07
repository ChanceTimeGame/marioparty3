#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

void func_80089980_main(Matrix4f mf, Mtx* m);
void func_8008CBF0_main(Matrix4f src, Vec* v, Matrix4f dst);

/* the fixed-point form of func_8008CBF0_main: out = m post-multiplied by a translate by v */
void func_8008CC60_main(Mtx* m, Vec* v, Mtx* out) {
    Matrix4f mf;

    func_80089980_main(mf, m);
    func_8008CBF0_main(mf, v, mf);
    func_800898F0_main((Mtx*)mf, out);
}
