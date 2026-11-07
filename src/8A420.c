#include "common.h"

/* |x| <= eps */
s32 func_80089820_main(f32 x, f32 eps) {
    return (-eps <= x) & (x <= eps);
}
