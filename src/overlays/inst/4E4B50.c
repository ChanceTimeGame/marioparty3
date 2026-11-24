#include "common.h"

/* An entry of the main minigame table (D_800A6D40_main, stride 0x14; D_800A6D44_main is its +4). */
typedef struct InstMgEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 type;
    /* 0x05 */ char unk5[3];
    /* 0x08 */ s16 mes[6]; /* pages: first, second, three optional (< 0: none), last */
} InstMgEntry; /* size = 0x14 */

void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
TextWindow *func_8005BA28_main(s16 arg0);
void func_80060DEC_main(s32 winId);

void func_8010BE28_inst(omObjData *obj);
void func_8010BE78_inst(omObjData *obj);
void func_8010C124_inst(omObjData *obj);
void func_8010BE70_inst(omObjData *obj);
s32 func_8010C55C_inst(void);
void func_8010C5C4_inst(omObjData *obj);
void func_8010C8B4_inst(void);
s32 func_8010C8E0_inst(u16 btn);
void func_8010CBB8_inst(s32 page);
void func_8010CC14_inst(void);
void func_8010CDE4_inst(s32 mesId, s16 x, s16 y);
void func_8010CED0_inst(s16 x, s16 y);
void func_8010CF14_inst(void);
void func_8010CFF4_inst(void);
void func_8010D044_inst(void);
void func_8010D1D4_inst(void);

extern InstMgEntry D_800A6D40_main[];
extern u16 D_800CC698_main;

extern s8 D_8010D406_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D409_inst;
extern s8 D_8010D40A_inst;
extern s8 D_8010D40B_inst;
extern s8 D_8010D411_inst;
extern s32 D_8010D440_inst;
extern s8 D_8010D5B0_inst;
extern s32 D_8010D5B4_inst;
extern s32 D_8010D5B8_inst;
extern omObjData *D_8010DCA0_inst;
extern void (*D_8010DCA4_inst)(omObjData *);
extern s16 D_8010DCA8_inst[7];
extern s16 D_8010DCC0_inst[2];
extern s16 D_8010DCC4_inst[3];
extern s32 D_8010DCCC_inst;
extern InstMgEntry *D_8010DCD0_inst;
extern s8 D_8010DCD4_inst;

const s32 D_8010DAF8_inst[] = { 95, 105, 115 };

void func_8010B990_inst(void) {
    s32 digits[3];
    omObjData *obj;
    s32 n;
    s32 sprite;
    s16 mes;
    s32 i;

    obj = omAddObj(0x14, 5, 0, -1, NULL);
    D_8010DCA0_inst = obj;
    D_8010DCD0_inst = &D_800A6D40_main[D_8010D40B_inst];
    D_8010DCC0_inst[0] = InitEspriteSlot(func_8000B838_main(0x170008), 0, 1);
    func_8000BC48_main(D_8010DCC0_inst[0], 0x1000);
    func_8000BBFC_main(D_8010DCC0_inst[0], 0xFF);
    func_8000BBD4_main(D_8010DCC0_inst[0], 160, -100);
    func_8010CDE4_inst(D_8010D40B_inst + 0x4700, 160, -100);
    func_8010CF14_inst();
    func_8010CFF4_inst();
    if (D_8010D40A_inst == 3) {
        D_8010DCC0_inst[1] = InitEspriteSlot(func_8000B838_main(0x17000E), 0, 1);
        func_8000BC48_main(D_8010DCC0_inst[1], 0x1000);
        func_8000BBFC_main(D_8010DCC0_inst[1], 0xFF);
        func_8000BBD4_main(D_8010DCC0_inst[1], 160, -78);
        n = D_800CC698_main;
        sprite = func_8000B838_main(0x1300CF);
        if (n >= 1000) {
            n = 999;
        } else if (n < 0) {
            n = 0;
        }
        digits[0] = n / 100 % 10;
        digits[1] = n / 10 - n / 100 * 10;
        digits[2] = n % 10;
        for (i = 0; i < 3; i++) {
            D_8010DCC4_inst[i] = InitEspriteSlot(sprite, 0, 0);
            func_8000BBD4_main(D_8010DCC4_inst[i], D_8010DAF8_inst[i], -78);
            func_8000BD94_main(D_8010DCC4_inst[i], (u16)digits[i], 0);
        }
    }
    D_8010DCA8_inst[0] = func_80060880_main(72, 188, 7);
    func_8005C060_main(D_8010DCA8_inst[0], 2, 0, 0xFF, 0xFF);
    func_8005C060_main(D_8010DCA8_inst[0], 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(D_8010DCA8_inst[0], 6, 0xFF, 0xFF, 0x40);
    func_8005BA28_main(D_8010DCA8_inst[0])->unk_29 = 1;
    func_8010CC14_inst();
    D_8010DCA8_inst[1] = func_8005B7B8_main(D_8010DCA8_inst[0], 0x17000B, 60, -33, 0);
    D_8010DCA8_inst[2] = func_8005B7B8_main(D_8010DCA8_inst[0], 0x170009, 148, -33, 0);
    D_8010DCA8_inst[3] = func_8005B7B8_main(D_8010DCA8_inst[0], 0x17000A, 200, -33, 0);
    D_8010DCA8_inst[4] = func_8005B7B8_main(D_8010DCA8_inst[0], 0x17000D, 60, -33, 0);
    D_8010DCA8_inst[5] = func_8005B7B8_main(D_8010DCA8_inst[0], 0x17000F, 200, -33, 0);
    D_8010DCA8_inst[6] = func_8005B7B8_main(D_8010DCA8_inst[0], 0x17000C, 38, -33, 0);
    D_8010DCD4_inst = 0;
    mes = D_8010DCD0_inst->mes[0];
    D_8010DCCC_inst = mes;
    if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
        D_8010DCCC_inst = mes + 1;
    }
    func_8005B43C_main(D_8010DCA8_inst[0], D_8010DCCC_inst, -1, -1);
    omPrcSetDestructor(0, func_8010C8B4_inst);
    D_8010DCA4_inst = func_8010BE28_inst;
    while (TRUE) {
        D_8010DCA4_inst(obj);
        HuPrcVSleep();
    }
}

void func_8010BE28_inst(omObjData *obj) {
    if (D_8010D408_inst == 1) {
        D_8010D5B0_inst = 1;
    }
    if (D_8010D5B0_inst == 1) {
        D_8010DCA4_inst = func_8010BE78_inst;
    }
}

void func_8010BE70_inst(omObjData *obj) {
}

/* NON_MATCHING: retail loads the 1 stored to D_8010D440_inst into v1, this into v0; logic matches.
 * Retail reads the low half of D_8010D5B8_inst through its own label (D_8010D5BA). */
// decomp-permuter
void func_8010BE78_inst(omObjData *obj)
{
  int new_var;
  s32 i;
  if (D_8010D408_inst == 0)
  {
    func_8000BBD4_main(D_8010DCC0_inst[0], 160, (s16) D_8010D5B8_inst);
    func_8010CED0_inst(160, (s16) D_8010D5B8_inst);
    if (D_8010D40A_inst == 3)
    {
      func_8000BBD4_main(D_8010DCC0_inst[1], 160, ((s16) D_8010D5B8_inst) + 22);
      for (i = 0; i < 3; i++)
      {
        func_8000BBD4_main(D_8010DCC4_inst[i], D_8010DAF8_inst[i], ((s16) D_8010D5B8_inst) + 22);
      }

    }
    D_8010D5B4_inst++;
    D_8010D5B8_inst = (sindf(D_8010D5B4_inst * 6) * 96.0f) + (-64.0f);
    if (D_8010D5B4_inst < 15)
    {
      return;
    }
    D_8010D5B4_inst = 0;
    D_8010D5B8_inst = -64;
    func_8000BBD4_main(D_8010DCC0_inst[0], 160, 32);
    func_8010CED0_inst(160, 32);
    new_var = D_8010D40A_inst;
    if (new_var == 3)
    {
      func_8000BBD4_main(D_8010DCC0_inst[1], 160, 54);
      for (i = 0; i < 3; i++)
      {
        func_8000BBD4_main(D_8010DCC4_inst[i], D_8010DAF8_inst[i], 54);
      }

    }
  }
  else
  {
    func_8000BBD4_main(D_8010DCC0_inst[0], 160, 32);
    func_8010CED0_inst(160, 32);
    if (D_8010D40A_inst == 3)
    {
      func_8000BBD4_main(D_8010DCC0_inst[1], 160, 54);
      for (i = 0; i < 3; i++)
      {
        func_8000BBD4_main(D_8010DCC4_inst[i], D_8010DAF8_inst[i], 54);
      }

    }
    func_80060DEC_main(D_8010DCA8_inst[0]);
    new_var = 1;
    D_8010D440_inst = new_var;
  }
  func_8010D044_inst();
  D_8010DCA4_inst = func_8010C124_inst;
}

/* Instruction page message IDs, by minigame type (also read by func_8010D1D4_inst). */
const s16 D_8010DB04_inst[2][3] = { { 0x3900, 0x3901, 0x3902 }, { 0x3908, 0x3909, 0x390A } };
const s16 D_8010DB10_inst[2][3] = { { 0x3910, 0x3912, 0x3914 }, { 0x390C, 0x390D, 0x390E } };
const s16 D_8010DB1C_inst[3] = { 0x3904, 0x3905, 0x3906 };
const s16 D_8010DB24_inst[2][3] = { { 0x3803, 0x3804, 0x3805 }, { 0x380A, 0x380B, 0x380C } };
const s16 D_8010DB30_inst[3] = { 0x3811, 0x3812, 0x3813 };

void func_8010C124_inst(omObjData *obj) {
    s16 mes;

    if (D_8010D409_inst == 1) {
        return;
    }
    if ((u16)func_8010C8E0_inst(0x10)) {
        func_8010D1D4_inst();
        D_8010DCA4_inst = func_8010C5C4_inst;
        return;
    }
    switch (D_8010DCD4_inst) {
        case 0:
            if ((u16)func_8010C8E0_inst(1)) {
                D_8010DCCC_inst = D_8010DCD0_inst->mes[1];
                if (D_8010DCD0_inst->mes[2] < 0) {
                    func_8010CBB8_inst(1);
                    D_8010DCD4_inst = 1;
                } else {
                    func_8010CBB8_inst(3);
                    D_8010DCD4_inst = 3;
                }
                func_8005B43C_main(D_8010DCA8_inst[0], D_8010DCCC_inst, -1, -1);
            }
            break;
        case 1:
            if ((u16)func_8010C8E0_inst(1)) {
                mes = D_8010DCD0_inst->mes[5];
                D_8010DCCC_inst = mes;
                if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                    D_8010DCCC_inst = mes + 1;
                }
                func_8005B43C_main(D_8010DCA8_inst[0], D_8010DCCC_inst, -1, -1);
                func_8010CBB8_inst(2);
                D_8010DCD4_inst = 2;
            }
            break;
        case 3:
            if ((u16)func_8010C8E0_inst(1)) {
                if (D_8010DCD0_inst->mes[2] < 0) {
                    mes = D_8010DCD0_inst->mes[5];
                    D_8010DCCC_inst = mes;
                    if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                        D_8010DCCC_inst = mes + 1;
                    }
                    func_8010CBB8_inst(2);
                    D_8010DCD4_inst = 2;
                } else {
                    D_8010DCCC_inst = D_8010DCD0_inst->mes[2];
                    func_8010CBB8_inst(4);
                    D_8010DCD4_inst = 4;
                }
                func_8005B43C_main(D_8010DCA8_inst[0], D_8010DCCC_inst, -1, -1);
            }
            break;
        case 4:
            if ((u16)func_8010C8E0_inst(1)) {
                if (D_8010DCD0_inst->mes[3] < 0) {
                    mes = D_8010DCD0_inst->mes[5];
                    D_8010DCCC_inst = mes;
                    if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                        D_8010DCCC_inst = mes + 1;
                    }
                    func_8010CBB8_inst(2);
                    D_8010DCD4_inst = 2;
                } else {
                    D_8010DCCC_inst = D_8010DCD0_inst->mes[3];
                    func_8010CBB8_inst(6);
                    D_8010DCD4_inst = 6;
                }
                func_8005B43C_main(D_8010DCA8_inst[0], D_8010DCCC_inst, -1, -1);
            }
            break;
        case 6:
            if ((u16)func_8010C8E0_inst(1)) {
                if (D_8010DCD0_inst->mes[4] < 0) {
                    mes = D_8010DCD0_inst->mes[5];
                    D_8010DCCC_inst = mes;
                    if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                        D_8010DCCC_inst = mes + 1;
                    }
                    func_8010CBB8_inst(2);
                    D_8010DCD4_inst = 2;
                } else {
                    D_8010DCCC_inst = D_8010DCD0_inst->mes[4];
                    func_8010CBB8_inst(7);
                    D_8010DCD4_inst = 7;
                }
                func_8005B43C_main(D_8010DCA8_inst[0], D_8010DCCC_inst, -1, -1);
            }
            break;
        case 7:
            if ((u16)func_8010C8E0_inst(1)) {
                D_8010DCCC_inst = D_8010DCD0_inst->mes[5];
                func_8010CBB8_inst(2);
                D_8010DCD4_inst = 2;
                if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                    D_8010DCCC_inst++;
                }
                func_8005B43C_main(D_8010DCA8_inst[0], D_8010DCCC_inst, -1, -1);
            }
            break;
        case 2:
            if ((u16)func_8010C8E0_inst(1)) {
                mes = D_8010DCD0_inst->mes[0];
                D_8010DCCC_inst = mes;
                if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                    D_8010DCCC_inst = mes + 1;
                }
                func_8005B43C_main(D_8010DCA8_inst[0], D_8010DCCC_inst, -1, -1);
                func_8010CBB8_inst(0);
                D_8010DCD4_inst = 0;
            }
            break;
    }
}

s32 func_8010C55C_inst(void) {
    s32 skip = 0;

    if ((u16)func_8010C8E0_inst(0x10) && D_8010D409_inst != 1) {
        skip = 1;
        func_8010D044_inst();
        D_8010DCA4_inst = func_8010C124_inst;
    }
    HuPrcVSleep();
    return skip;
}

void func_8010C5C4_inst(omObjData *obj) {
    s32 mes;
    s8 i;

    if (D_8010D409_inst == 1) {
        return;
    }
    for (i = 0; i < 3; i++) {
        switch (D_8010D40B_inst) {
            case 8:
            case 16:
            case 27:
                mes = D_8010DB1C_inst[i];
                break;
            default:
                switch (D_8010D40A_inst) {
                    case 5:
                        mes = D_8010DB04_inst[1][i];
                        break;
                    case 4:
                        mes = D_8010DB10_inst[0][i];
                        mes += (D_8010D411_inst != 2);
                        break;
                    case 3:
                        mes = D_8010DB10_inst[1][i];
                        break;
                    case 7:
                        if (D_8010D40B_inst == 70) {
                            mes = D_8010DB24_inst[1][i];
                        } else {
                            mes = D_8010DB30_inst[i];
                        }
                        break;
                    case 8:
                        mes = D_8010DB24_inst[0][i];
                        break;
                    case 0:
                    case 1:
                    case 2:
                    case 6:
                    default:
                        mes = D_8010DB04_inst[0][i];
                        break;
                }
                break;
        }
        func_8005B43C_main(D_8010DCA8_inst[0], mes, -1, -1);
    wait_page:
        if (func_8005E0C0_main(D_8010DCA8_inst[0])) {
            if (func_8010C55C_inst()) {
                return;
            }
            goto wait_page;
        }
    }
    mes = D_8010DCD0_inst->mes[5];
    if (D_8010D40A_inst == 4) {
        mes += (D_8010D411_inst != 2);
    }
    func_8005B43C_main(D_8010DCA8_inst[0], mes, -1, -1);
    while (func_8005E0C0_main(D_8010DCA8_inst[0])) {
        if (func_8010C55C_inst()) {
            return;
        }
    }
    while (!(u16)func_8010C8E0_inst(0x8000)) {
        if (func_8010C55C_inst()) {
            return;
        }
    }
    D_8010D406_inst = 1;
    D_8010DCA4_inst = func_8010BE70_inst;
}

void func_8010C848_inst(void) {
    if (D_8010D408_inst == 0) {
        HuAudFXPlay(0x11D);
        func_80060C14_main(D_8010DCA8_inst[0], 0);
        D_8010D440_inst = 1;
    }
}

void func_8010C890_inst(void) {
    func_80060EA8_main(D_8010DCA8_inst[0], 1);
}

void func_8010C8B4_inst(void) {
    GMesClose();
}

void func_8010C8D0_inst(void) {
    D_8010D5B0_inst = 1;
}

/* .data (8010D5B0) */
s8 D_8010D5B0_inst = 0;
s8 D_8010D5B1_inst = 0;
s32 D_8010D5B4_inst = 0;
s32 D_8010D5B8_inst = -64; /* the window's drop-in y */
