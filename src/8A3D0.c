#include "common.h"

extern f32 D_800A12A4_main;

/* sign of x with the global dead zone D_800A12A4_main */
s32 func_800897D0_main(f32 x) {
    if (x < -D_800A12A4_main) {
        return -1;
    }
    if (D_800A12A4_main < x) {
        return 1;
    }
    return 0;
}
