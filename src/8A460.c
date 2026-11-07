#include "common.h"

extern f32 D_800A12A4_main;

/* |x| <= D_800A12A4_main */
s32 func_80089860_main(f32 x) {
    return (-D_800A12A4_main <= x) && (x <= D_800A12A4_main);
}
