#include "common.h"
#include "math.h"

extern f32 D_800A12A4_main;

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

/* a and b equal per component within eps */
s32 func_80089E90_main(Vec* a, Vec* b, f32 eps) {
    f32 d;

    return (-eps <= (d = a->x - b->x)) && (d <= eps) && (-eps <= (d = a->y - b->y)) && (d <= eps) &&
           (-eps <= (d = a->z - b->z)) && (d <= eps);
}

/* a and b equal per component within D_800A12A4_main */
s32 func_80089F30_main(Vec* a, Vec* b) {
    f32 d;

    return (-D_800A12A4_main <= (d = a->x - b->x)) && (d <= D_800A12A4_main) && (-D_800A12A4_main <= (d = a->y - b->y)) && (d <= D_800A12A4_main) &&
           (-D_800A12A4_main <= (d = a->z - b->z)) && (d <= D_800A12A4_main);
}

/* look-at matrix from cam, discarding the basis */
void func_80089FD0_main(Matrix4f m, LookAtCam* cam) {
    LookAtBasis basis;

    func_8008D450_main(m, cam, &basis);
}
