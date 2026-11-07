#include "common.h"
#include "math.h"

typedef f32 Matrix4f[4][4];

void HuVecCross(Vec* out, Vec* a, Vec* b);
void HuVecNormalize3F(Vec* vec);

/* a look-at camera: eye, the point looked at, and the up vector */
typedef struct {
    Vec eye;
    Vec at;
    Vec up;
} LookAtCam;

/* the camera basis func_8008D450_main leaves in its work area */
typedef struct {
    Vec right;
    Vec up;
    Vec look;
} LookAtBasis;

/* guLookAtF from a LookAtCam: look = normalize(eye - at), right = normalize(up x look),
   up = normalize(look x right); basis is the caller's work area */
// NON_MATCHING: retail starts the dot products before the column copies but reloads the copied
// values, so it needs no callee-saved float registers (this builds 106 instructions, masked 37)
#ifdef NON_MATCHING
void func_8008D450_main(Matrix4f m, LookAtCam* cam, LookAtBasis* basis) {
    f32 ex;
    f32 ey;
    f32 ez;
    f32 dr;
    f32 du;
    f32 dl;

    HuVecSubtract(&basis->look, &cam->eye, &cam->at);
    HuVecNormalize3F(&basis->look);
    HuVecCross(&basis->right, &cam->up, &basis->look);
    HuVecNormalize3F(&basis->right);
    HuVecCross(&basis->up, &basis->look, &basis->right);
    HuVecNormalize3F(&basis->up);
    ex = cam->eye.x;
    ey = cam->eye.y;
    ez = cam->eye.z;
    dr = ex * basis->right.x + ey * basis->right.y + ez * basis->right.z;
    du = ex * basis->up.x + ey * basis->up.y + ez * basis->up.z;
    dl = ex * basis->look.x + ey * basis->look.y + ez * basis->look.z;
    m[0][0] = basis->right.x;
    m[1][0] = basis->right.y;
    m[2][0] = basis->right.z;
    m[3][0] = -dr;
    m[0][1] = basis->up.x;
    m[1][1] = basis->up.y;
    m[2][1] = basis->up.z;
    m[3][1] = -du;
    m[0][2] = basis->look.x;
    m[1][2] = basis->look.y;
    m[2][2] = basis->look.z;
    m[3][2] = -dl;
    m[2][3] = m[1][3] = m[0][3] = 0.0f;
    m[3][3] = 1.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/8E050", func_8008D450_main);
#endif
