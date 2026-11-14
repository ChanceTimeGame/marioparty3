#include "common.h"

/* GAMEMES (src/gamemes.c): a game message, drawn as sprite groups. */
typedef struct InstGMes {
    /* 0x00 */ u8 mesNo;
    /* 0x01 */ u8 stat;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 strGId[16];
    /* 0x40 */ s16 strSprId[16];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} InstGMes; /* size = 0x74 */

/* An entry of the main minigame table (D_800A6D40_main, stride 0x14); see 4E4B50.c. */
typedef struct InstMgEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 type;
    /* 0x05 */ char unk5[3];
    /* 0x08 */ s16 mes[6];
} InstMgEntry; /* size = 0x14 */

s16 func_8003A37C_main(InstGMes *gMes, char *str, u8 flag, s16 x, s16 arg4);

void func_8010CBB8_inst(u8 page);
void func_8010CFF4_inst(void);

extern s8 D_8010D400_inst[];
extern s8 D_8010D409_inst;
extern s8 D_8010D40A_inst;
extern s8 D_8010D411_inst;
extern s8 D_8010D5B1_inst;
extern s16 D_8010DCA8_inst[7];
extern s32 D_8010DCCC_inst;
extern InstMgEntry *D_8010DCD0_inst;
extern s8 D_8010DCD4_inst;
extern InstGMes D_8010DCD8_inst; /* inside D_8010DCD4_inst's bss space: alias in undefined_syms.txt */
extern InstGMes D_8010DD50_inst;

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

void func_8010CDE4_inst(s32 mesId, s16 x, s16 y) {
    char *str;

    str = func_800364DC_main((void *)mesId);
    D_8010DCD8_inst.unk08 = -1;
    D_8010DCD8_inst.unk08 = func_8003A37C_main(&D_8010DCD8_inst, str + 1, 0, -1, -1);
    D_8010DCD8_inst.unk60 = x;
    D_8010DCD8_inst.unk64 = y;
    func_80054904_main(D_8010DCD8_inst.strGId[D_8010DCD8_inst.unk08], 0, D_8010DCD8_inst.unk60,
                       D_8010DCD8_inst.unk64);
    func_800365E8_main(str);
}

void func_8010CED0_inst(s16 x, s16 y) {
    func_80054904_main(D_8010DCD8_inst.strGId[D_8010DCD8_inst.unk08], 0, x, y);
}

void func_8010CF14_inst(void) {
    D_8010DD50_inst.unk08 = func_8003A37C_main(&D_8010DD50_inst, "PRACTICE", 0, -1, -1);
    D_8010DD50_inst.unk60 = 216.0f;
    D_8010DD50_inst.unk64 = 90.0f;
    func_80054904_main(D_8010DD50_inst.strGId[D_8010DD50_inst.unk08], 0, 216, 90);
}

void func_8010CF98_inst(void) {
    D_8010DD50_inst.unk60 = 216.0f;
    D_8010DD50_inst.unk64 = 90.0f;
    func_80054904_main(D_8010DD50_inst.strGId[D_8010DD50_inst.unk08], 0, 216, 90);
}

void func_8010CFF4_inst(void) {
    D_8010DD50_inst.unk60 = 512.0f;
    D_8010DD50_inst.unk64 = 512.0f;
    func_80054904_main(D_8010DD50_inst.strGId[D_8010DD50_inst.unk08], 0, 512, 512);
}

void func_8010D044_inst(void) {
    TextWindow *win;
    s16 mes;
    s8 i;

    win = &D_800CC69C_main[D_8010DCA8_inst[0]];
    if (D_8010D409_inst == 1) {
        return;
    }
    func_8010CFF4_inst();
    HuSprAttrReset(win->unk_6C, D_8010DCA8_inst[6], 0x8000);
    for (i = 0; i < 3; i++) {
        if (i != 1) {
            HuSprAttrReset(win->unk_6C, D_8010DCA8_inst[1 + i], 0x8000);
        }
    }
    for (i = 0; i < 2; i++) {
        HuSprAttrSet(win->unk_6C, D_8010DCA8_inst[4 + i], 0x8000);
    }
    mes = D_8010DCD0_inst->mes[0];
    D_8010DCCC_inst = mes;
    if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
        D_8010DCCC_inst = mes + 1;
    }
    func_8005B43C_main(D_8010DCA8_inst[0], D_8010DCCC_inst, -1, -1);
    func_8010CBB8_inst(0);
    D_8010DCD4_inst = 0;
    D_8010D5B1_inst = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E5AA0", func_8010D1D4_inst);
