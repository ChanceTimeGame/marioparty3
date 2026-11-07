#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

typedef struct {
    Vec eye;
    Vec at;
    Vec up;
} LookAtCam;

typedef struct {
    Vec right;
    Vec up;
    Vec look;
} LookAtBasis;

void func_8008D450_main(Matrix4f m, LookAtCam* cam, LookAtBasis* basis);

/* fixed-point look-at matrix from cam */
void func_80089FF0_main(Mtx* m, LookAtCam* cam) {
    Matrix4f mf;
    LookAtBasis basis;

    func_8008D450_main(mf, cam, &basis);
    func_800898F0_main((Mtx*)mf, m);
}
