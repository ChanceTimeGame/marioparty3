#include "common.h"

extern s8 D_8010D400_inst[];
extern s8 D_8010D40A_inst;
extern s16 D_8010DCA8_inst[7];

s32 func_8010C8E0_inst(u16 btn) {
    u16 ret = 0;
    s8 i;

    switch (D_8010D40A_inst) {
        case 5:
        case 6:
        case 7:
        case 8:
            if (!(GwPlayer[D_8010D400_inst[0]].stat & 1)) {
                ret = btn & D_800D5558_main[GwPlayer[D_8010D400_inst[0]].pad];
            }
            break;
        case 4:
            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                    ret = btn & D_800D5558_main[GwPlayer[D_8010D400_inst[i]].pad];
                    if (ret) {
                        break;
                    }
                }
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        default:
            for (i = 0; i < 4; i++) {
                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                    ret = btn & D_800D5558_main[GwPlayer[D_8010D400_inst[i]].pad];
                    if (ret) {
                        break;
                    }
                }
            }
            break;
    }
    return ret;
}

u16 func_8010CA74_inst(s32 btn, s16 flag) {
    s32 cpu = 0;
    s32 ret = 0;
    s32 free;
    s8 i;

    switch (D_8010D40A_inst) {
        case 5:
        case 6:
        case 7:
        case 8:
            cpu = GwPlayer[D_8010D400_inst[0]].stat & 1;
            break;
        case 4:
            if ((GwPlayer[D_8010D400_inst[0]].stat & 1) && (GwPlayer[D_8010D400_inst[1]].stat & 1)) {
                cpu = 1;
            }
            break;
    }
    for (i = 0; i < 4; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }
    if ((free = (i < 4)) & (cpu ^ 1)) {
        ret = func_8010C8E0_inst(btn);
    } else if (flag == 0) {
        ret = 1;
    }
    return ret;
}

void func_8010CBB8_inst(u8 page) {
    TextWindow *win = &D_800CC69C_main[D_8010DCA8_inst[0]];

    func_80055024_main(win->unk_6C, D_8010DCA8_inst[6], win->unk_6E[D_8010DCA8_inst[6]], page);
}

void func_8010CC14_inst(void) {
    s32 mask;
    s8 i;

    for (i = 0; i < 4; i++) {
        func_8005B6BC_main(D_8010DCA8_inst[0], GwPlayer[D_8010D400_inst[i]].chr + 0x1C00, i);
    }
    mask = 0;
    switch (D_8010D40A_inst) {
        case 5:
        case 6:
        case 7:
        case 8:
            mask |= 1 << GwPlayer[D_8010D400_inst[0]].pad;
            break;
        case 4:
            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                    mask |= 1 << GwPlayer[D_8010D400_inst[i]].pad;
                }
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        default:
            for (i = 0; i < 4; i++) {
                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                    mask |= 1 << GwPlayer[D_8010D400_inst[i]].pad;
                }
            }
            break;
    }
    func_8005FE54_main(D_8010DCA8_inst[0], mask);
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E5AA0", func_8010CDE4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E5AA0", func_8010CED0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E5AA0", func_8010CF14_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E5AA0", func_8010CF98_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E5AA0", func_8010CFF4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E5AA0", func_8010D044_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E5AA0", func_8010D1D4_inst);
