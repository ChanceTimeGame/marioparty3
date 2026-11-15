#include "common.h"
#include "ovl_81.h"
#include "game/camera.h"

// duel n7: screen scissor wipes (Duel Mode copy of ovl_80 1063F0.c)

extern RectF D_801014D0_name_81;

void func_800F4080_name_81(void) {
    D_801014D0_name_81.x1 = 16.0f;
    D_801014D0_name_81.y1 = 12.0f;
    D_801014D0_name_81.x2 = 304.0f;
    D_801014D0_name_81.y2 = 228.0f;
    CameraScissorSet(0, &D_801014D0_name_81);
}

void func_800F40E4_name_81(void) {
    D_801014D0_name_81.x1 = 16.0f;
    D_801014D0_name_81.y1 = 12.0f;
    D_801014D0_name_81.x2 = 16.0f;
    D_801014D0_name_81.y2 = 228.0f;
    CameraScissorSet(0, &D_801014D0_name_81);
}

void func_800F413C_name_81(void) {
    s32 i;

    D_801014D0_name_81.x1 = 16.0f;
    D_801014D0_name_81.x2 = 304.0f;

    for (i = 0; i < 9; i++) {
        HuPrcVSleep();
        D_801014D0_name_81.x1 += 32.0f;
        CameraScissorSet(0, &D_801014D0_name_81);
    }
    omDelPrcObj(NULL);
}

void func_800F41DC_name_81(void) {
    omAddPrcObj(func_800F413C_name_81, 0x1002, 0, 0);
}

void func_800F4208_name_81(void) {
    s32 i;

    D_801014D0_name_81.x1 = 16.0f;
    D_801014D0_name_81.x2 = 16.0f;

    for (i = 0; i < 9; i++) {
        HuPrcVSleep();
        D_801014D0_name_81.x2 += 32.0f;
        CameraScissorSet(0, &D_801014D0_name_81);
    }
    omDelPrcObj(NULL);
}

void func_800F429C_name_81(void) {
    omAddPrcObj(func_800F4208_name_81, 0x1002, 0, 0);
}

s32 func_800F42C8_name_81(void) {
    if (D_801014D0_name_81.x2 == 304.0f) {
        return 1;
    }
    return 0;
}
