#include "common.h"

// duel c1
void func_800FBFA4_name_81(void);
void func_800FC030_name_81(void);

// entry 0
void func_801059D0_duelcall(void) {
    if (_CheckFlag(0) != 0) {
        GWBoardFlagSet(1);
    } else {
        GWBoardFlagClear(1);
    }
    omInitObjMan(0xA, 0);
    func_800FBFA4_name_81();
    omOvlGotoEx(duelcall, 1, 0x4190);
    omOvlHisChg(0, duelcall, 1, 0x4190);
}

// entry 1
void func_80105A44_duelcall(void) {
    omInitObjMan(0xA, 0);
    func_800FC030_name_81();
}

void func_80105A6C_duelcall(void) {
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

// entry 2
void func_80105A98_duelcall(void) {
    omInitObjMan(0xA, 0xA);
    func_8004A208_main();
    omAddPrcObj(func_80105A6C_duelcall, 0x1005, 0, 0);
}
