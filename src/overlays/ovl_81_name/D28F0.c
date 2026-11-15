#include "common.h"
#include "ovl_81.h"
#include "game/board.h"

// duel n5: board message windows (party mode's FFB10.c)

extern s16 D_801011D2_name_81; // skip the player's input wait
extern s16 D_80105712_name_81; // message window id

void func_800EED84_name_81(s16, s32);
void func_800EF3D0_name_81(s16);

void func_800EAB20_name_81(s16 arg0) {
    if (D_801011D2_name_81 != 0) {
        func_800EF3B4_name_81(arg0);
        return;
    }
    func_800EED68_name_81(arg0, GwSystem.current_player_index);
}

void func_800EAB6C_name_81(s32 arg0, s32 arg1) {
    if ((GwSystem.current_player_index == 4) || (D_801011D2_name_81 != 0)) {
        func_800EF3D0_name_81(arg0);
        return;
    }
    func_800EED84_name_81(arg0, arg1);
}

s16 func_800EABBC_name_81(s16 arg0, s16* arg1, s16 arg2) {
    s32 result;

    if (arg2 == -1) {
        if (arg0 == arg2) {
            result = func_80061188_main(-1, 0, 0, arg1[0], arg1[1], 2);
        } else {
            result = func_80061188_main(arg0, 0, 0, arg1[0], arg1[1], 2);
        }
    } else {
        if (arg0 == -1) {
            result = func_80061188_main(-1, 0xA0 - arg1[0] / 2, arg2, arg1[0], arg1[1], 0);
        } else {
            result = func_80061188_main(arg0, 0xA0 - arg1[0] / 2, arg2, arg1[0], arg1[1], 0);
        }
    }
    if (D_800CB99C_main == 0) {
        func_8005B63C_main(result, 0x40, 0x40);
    }
    return result;
}

void func_800EAD08_name_81(s32 arg0) {
    s16 sp18[2];
    s16 temp_v0;

    func_80060394_main(1, sp18, arg0);
    temp_v0 = func_80061188_main(-1, 0, 0, sp18[0], sp18[1], 2);
    D_80105712_name_81 = temp_v0;
    if (D_800CB99C_main == 0) {
        func_8005B63C_main(temp_v0, 0x40, 0x40);
    }
    func_8005B43C_main(temp_v0, arg0, -1, -1);
    func_80061388_main(temp_v0);
}

void func_800EADBC_name_81(s32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5) {
    s16 sp18[2];
    s16 temp_v0;

    if (arg1 != 0) {
        func_8006022C_main(arg1, 0);
    }
    if (arg2 != 0) {
        func_8006022C_main(arg2, 1);
    }
    if (arg3 != 0) {
        func_8006022C_main(arg3, 2);
    }
    if (arg4 != 0) {
        func_8006022C_main(arg4, 3);
    }
    if (arg5 != 0) {
        func_8006022C_main(arg5, 4);
    }
    func_80060394_main(1, sp18, arg0);
    temp_v0 = func_80061188_main(-1, 0, 0, sp18[0], sp18[1], 2);
    D_80105712_name_81 = temp_v0;
    if (D_800CB99C_main == 0) {
        func_8005B63C_main(temp_v0, 0x40, 0x40);
    }
    if (arg1 != 0) {
        func_8005B6BC_main(temp_v0, arg1, 0);
    }
    if (arg2 != 0) {
        func_8005B6BC_main(temp_v0, arg2, 1);
    }
    if (arg3 != 0) {
        func_8005B6BC_main(temp_v0, arg3, 2);
    }
    if (arg4 != 0) {
        func_8005B6BC_main(temp_v0, arg4, 3);
    }
    if (arg5 != 0) {
        func_8005B6BC_main(temp_v0, arg5, 4);
    }
    func_8005B43C_main(temp_v0, arg0, -1, -1);
    func_80061388_main(temp_v0);
}

void func_800EAF70_name_81(s32 arg0) {
    func_800EAB6C_name_81(D_80105712_name_81, arg0);
}

void func_800EAF94_name_81(void) {
    func_80061A5C_main(D_80105712_name_81, 0);
    func_8005F364_main(D_80105712_name_81);
}

void func_800EAFC4_name_81(s32 arg0) {
    s16 sp18[2];
    s16 temp_v0;

    func_80060394_main(1, sp18, arg0);
    temp_v0 = func_80061188_main(-1, 0, 0, sp18[0], sp18[1], 2);
    D_8010555C_name_81 = temp_v0;
    if (D_800CB99C_main == 0) {
        func_8005B63C_main(temp_v0, 0x40, 0x40);
    }
    func_8005B43C_main(temp_v0, arg0, -1, -1);
    func_80061388_main(temp_v0);
    func_800EAB20_name_81(temp_v0);
    func_80061A5C_main(temp_v0, 0);
    func_8005F364_main(temp_v0);
}

void func_800EB094_name_81(s16 arg0, s32 arg1, s32 arg2) {
    s16 sp10[2];
    s16 temp_v0;

    func_80060394_main(1, sp10, arg1);
    temp_v0 = func_800EABBC_name_81(arg0, sp10, arg2);
    D_8010555C_name_81 = temp_v0;
    func_8005B43C_main(temp_v0, arg1, -1, -1);
    func_80061388_main(temp_v0);
    func_800EAB20_name_81(temp_v0);
    func_80061A5C_main(temp_v0, 0);
    func_8005F364_main(temp_v0);
}

void func_800EB140_name_81(s32 arg0, s32 arg1) {
    func_800EB094_name_81(arg0, arg1, -1);
}

void func_800EB164_name_81(s16 arg0, s32 arg1) {
    D_801011D2_name_81 = 1;
    func_800EB094_name_81(arg0, arg1, -1);
    D_801011D2_name_81 = 0;
}

void func_800EB19C_name_81(s16 arg0, s32 arg1, s16 arg2) {
    D_801011D2_name_81 = 1;
    func_800EB094_name_81(arg0, arg1, arg2);
    D_801011D2_name_81 = 0;
}

void func_800EB1D8_name_81(s32 arg0, s32 arg1) {
    s16 sp10[2];
    s16 temp_v0;

    func_80060394_main(1, sp10, arg1);
    temp_v0 = func_800EABBC_name_81(arg0, sp10, -1);
    D_8010555C_name_81 = temp_v0;
    func_8005B43C_main(temp_v0, arg1, -1, -1);
    func_80061388_main(temp_v0);
}

void func_800EB258_name_81(void) {
    func_80061388_main(D_8010555C_name_81);
}

void func_800EB278_name_81(void) {
    func_80061A5C_main(D_8010555C_name_81, 0);
}

void func_800EB29C_name_81(void) {
    func_8005F364_main(D_8010555C_name_81);
}

void func_800EB2BC_name_81(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s16 arg7) {
    s16 sp10[2];
    s16 temp_v0;

    if (arg2 != 0) {
        func_8006022C_main(arg2, 0);
    }
    if (arg3 != 0) {
        func_8006022C_main(arg3, 1);
    }
    if (arg4 != 0) {
        func_8006022C_main(arg4, 2);
    }
    if (arg5 != 0) {
        func_8006022C_main(arg5, 3);
    }
    if (arg6 != 0) {
        func_8006022C_main(arg6, 4);
    }
    func_80060394_main(1, sp10, arg1);
    temp_v0 = func_800EABBC_name_81(arg0, sp10, arg7);
    D_8010555C_name_81 = temp_v0;
    if (arg2 != 0) {
        func_8005B6BC_main(temp_v0, arg2, 0);
    }
    if (arg3 != 0) {
        func_8005B6BC_main(temp_v0, arg3, 1);
    }
    if (arg4 != 0) {
        func_8005B6BC_main(temp_v0, arg4, 2);
    }
    if (arg5 != 0) {
        func_8005B6BC_main(temp_v0, arg5, 3);
    }
    if (arg6 != 0) {
        func_8005B6BC_main(temp_v0, arg6, 4);
    }
    if (D_801011D0_name_81 != 0) {
        func_8005E1A8_main(temp_v0, D_801011D0_name_81);
    }
    func_8005B43C_main(temp_v0, arg1, -1, -1);
    if (arg0 == -1) {
        func_80061388_main(temp_v0);
    } else {
        func_80061388_main(temp_v0);
    }

    func_800EAB6C_name_81(temp_v0, GwSystem.current_player_index);
}

void func_800EB49C_name_81(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_800EB2BC_name_81(arg0, arg1, arg2, arg3, arg4, arg5, arg6, -1);
}

void func_800EB4DC_name_81(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6) {
    D_801011D2_name_81 = 1;
    func_800EB2BC_name_81(arg0, arg1, arg2, arg3, arg4, arg5, arg6, -1);
    D_801011D2_name_81 = 0;
}

void func_800EB530_name_81(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s16 arg7) {
    D_801011D2_name_81 = 1;
    func_800EB2BC_name_81(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    D_801011D2_name_81 = 0;
}

void func_800EB58C_name_81(void) {
    D_800CC69C_main[D_8010555C_name_81].unk20 = 1;
    HuPrcVSleep();
    func_800EAB6C_name_81(D_8010555C_name_81, GwSystem.current_player_index);
}

void func_800EB5E8_name_81(void) {
    D_801011D2_name_81 = 1;
    D_800CC69C_main[D_8010555C_name_81].unk20 = 1;
    HuPrcVSleep();
    func_800EAB6C_name_81(D_8010555C_name_81, GwSystem.current_player_index);
    D_801011D2_name_81 = 0;
}

void func_800EB658_name_81(s16 arg0) {
    D_801011D0_name_81 = arg0;
}

void func_800EB664_name_81(void) {
    D_801011D0_name_81 = 0;
    D_801011D2_name_81 = 0;
}
