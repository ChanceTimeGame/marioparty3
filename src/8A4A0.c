#include "common.h"

s32 func_80089820_main(f32 x, f32 eps);

/* |a - b| <= eps */
s32 func_800898A0_main(f32 a, f32 b, f32 eps) {
    return func_80089820_main(a - b, eps);
}
