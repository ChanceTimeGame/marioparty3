#include "common.h"

/* sign of x: -1, 0 or 1 */
s32 func_80089750_main(f32 x) {
    if (x < 0.0f) {
        return -1;
    }
    if (0.0f < x) {
        return 1;
    }
    return 0;
}

/* sign of x with a dead zone of +-eps */
s32 func_80089790_main(f32 x, f32 eps) {
    if (x < -eps) {
        return -1;
    }
    if (eps < x) {
        return 1;
    }
    return 0;
}
