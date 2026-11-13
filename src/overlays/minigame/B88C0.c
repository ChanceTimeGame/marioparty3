#include "common.h"
#include "PR/os_misc.h"

u8 rand8(void);

extern u32 D_800EB900_minigame;

/* Park-Miller style step (Schrage: 16807 = 0x41A7, q = 0x1F31D, r = 0xB14); seed 0 reseeds. */
u32 func_800E5D40_minigame(u32 param) {
    s32 rand2, rand3;

    if (param == 0) {
        param = rand8();
        param = param ^ osGetCount();
        param ^= 0xD826BC89;
    }

    rand2 = param / 0x1F31D;
    rand3 = param - (rand2 * 0x1F31D);
    param = rand2 * 0xB14;
    param = param - rand3 * 0x41A7;
    return param;
}

u32 func_800E5E14_minigame(void) {
    return D_800EB900_minigame = func_800E5D40_minigame(D_800EB900_minigame);
}

u32 func_800E5E3C_minigame(u32 arg0) {
    u32 val;

    val = func_800E5D40_minigame(D_800EB900_minigame);
    D_800EB900_minigame = val;
    return (val & 0x7FFFFFFF) % arg0;
}
