#include "common.h"
#include "game/vibrator.h"

#include "filesel.h"
#include "mallocblock.h"

/* filesel B: name entry state, D_80114470_filesel..D_801144D4_filesel (offsets from D_80114470) */
extern s32 D_80114470_filesel; /* name changed */

typedef struct FsNameEntry {
    /* 0x08 */ s32 done;      /* D_80114478: leave the character grid */
    /* 0x0C */ s32 group;     /* D_8011447C: character grid 4, 5 or 6 */
    /* 0x10 */ s32 button;    /* D_80114480: focused button (7..11) */
    /* 0x14 */ s32 col;       /* D_80114484 */
    /* 0x18 */ s32 line;      /* D_80114488 */
    /* 0x1C */ s32 blink;     /* D_8011448C */
    /* 0x20 */ u16 name[16];  /* D_80114490: 16-bit characters, 0-terminated */
    /* 0x40 */ u16 saved[16]; /* D_801144B0 */
    /* 0x60 */ s32 len;       /* D_801144D0 */
} FsNameEntry; /* size = 0x5C */

extern FsNameEntry D_80114478_filesel;

extern s32 D_801127B0_filesel[3];
extern s32 D_801127BC_filesel[8][2]; /* cursor positions */
extern f32 D_800A0A7C_main;

extern u8 *D_801127FC_filesel[18];
extern u8 *D_80112844_filesel[18];
extern u8 *D_8011288C_filesel[5];


#define UNK_VALUE FS_FILE_USED

extern u16 D_800D1244_main;

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801059A0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801059D0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105BC0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105BF0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105C1C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105CB0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105CC4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105CE0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105D18_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105D70_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105DD8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105E48_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105E7C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105EC0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105EEC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105F24_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105F54_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105F84_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105FA0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80105FBC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106014_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106044_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106094_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801060CC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106100_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106134_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106168_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801061D4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106220_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801062BC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106344_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801063F4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010642C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106450_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106474_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801064DC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106550_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801065B8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010660C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106654_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010669C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801066DC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010671C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106760_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801067D0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106814_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010684C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801068B0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106950_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801069D8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106A48_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106AAC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106AD8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106B40_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106D8C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80106ED8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107040_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801071E8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801072B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107380_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010744C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107490_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107574_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801075D8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107608_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107670_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801076A0_filesel);

void func_801076D0_filesel(s32 arg0, u32 arg1) {
    u32 temp_v0;

    func_8005D294_main(D_80114158_filesel[arg0].unk_00);
    if (D_80114158_filesel[arg0].unk_04 != 0) {
        func_80019C00_main((void *)D_80114158_filesel[arg0].unk_04);
        D_80114158_filesel[arg0].unk_04 = 0;
    }

    temp_v0 = func_80106AD8_filesel(arg1);
    // pointer check
    if (temp_v0 > 0x80000000U) {
        D_80114158_filesel[arg0].unk_04 = temp_v0;
    }
    func_8005B43C_main(D_80114158_filesel[arg0].unk_00, temp_v0, -1, -1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010779C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801077D8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107810_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010782C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107880_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801078BC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801078F4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107AA8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107C50_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107C84_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80107CF8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801083AC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80108440_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112A64_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112A68_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010846C_filesel);

s32 func_80108834_filesel(void) {
    s32 i;
    s32 total;

    for (i = 0, total = 0; i < ARRAY_COUNT(D_801142DC_filesel); i++) {
        if (D_801142DC_filesel[i].unk_00 == UNK_VALUE) {
            total++;
        }
    }

    return total;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80108878_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801088DC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80108A94_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80108C34_filesel);

void func_80108D74_filesel(void) {
    Vec from;
    Vec to;
    Vec cur;
    f32 t;
    s32 i;

    i = 0;
    do {
        t = 1.0f - i * 0.1f;
        if (t < 0.0f) {
            t = 0.0f;
        }
        HuVecCopyXYZ(&from, 160.0f, 288.0f, 0.0f);
        HuVecCopyXYZ(&to, 160.0f, 192.0f, 0.0f);
        cur.x = (to.x - from.x) * t + from.x;
        cur.y = (to.y - from.y) * t + from.y;
        func_80107608_filesel(4, 160.0f, (96.0f - t * 96.0f) + 208.0f);
        i++;
        HuPrcVSleep();
    } while (i < 11);
    func_801076A0_filesel(4);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80108EB8_filesel);

#define CLAMP_BELOW(val, limit) ((val) < (limit) ? (val) : 0)

enum OptionsFileSelect {
    OPTION_FILE0 = 0,
    OPTION_FILE1 = 1,
    OPTION_FILE2 = 2,
    OPTION_FILES_END,
    OPTION_COPY = 3,
    OPTION_ERASE = 4,
    OPTION_FILES_NAME_BEGIN,
    OPTION_FILE0_NAME = 5,
    OPTION_FILE1_NAME = 6,
    OPTION_FILE2_NAME = 7,
    OPTION_MAX = 7,
};

// TODO: can the gotos be removed?
// main function for handling input when an option hasn't been select yet
u32 func_80109570_filesel(s32 arg0) {
    s32 temp_v0;
    u32 temp_v1;
    s32 animTimerAdjusted;
    s32 animTimer;
    u16 pressedInput;
    s32 cursorIndex;
    u32 selectedOption;
    s32 unkValue;

    animTimer = 0;

    if (arg0 < 0) {
        arg0 = 0;
    }

    selectedOption = arg0;
    cursorIndex = selectedOption;
    unkValue = UNK_VALUE;

    while (1) {
        pressedInput = D_800D1244_main;
        temp_v0 = func_80111B14_filesel(0);
        if (temp_v0 != -1) {
            pressedInput |= temp_v0;
        }
        if (D_800D5558_main[0] & A_BUTTON) {
            switch (selectedOption) {
                case OPTION_FILE0:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_FILE1:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_FILE2:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_COPY:
                case OPTION_ERASE:
                case OPTION_FILE0_NAME:
                case OPTION_FILE1_NAME:
                case OPTION_FILE2_NAME:
                    break;
                default:
                    goto checkIfCursorIndexChanged;
            }
            return selectedOption;
        }
        if ((D_800D5558_main[0] & B_BUTTON)) {
            if (selectedOption > OPTION_MAX) {
                goto checkIfCursorIndexChanged;
            }
        }
        switch (selectedOption) {
            case OPTION_FILE0:
            case OPTION_FILE1:
            case OPTION_FILE2:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    func_801076D0_filesel(4, 0x2A00);
                    func_80110FB0_filesel(selectedOption);
                    cursorIndex = selectedOption + 1;
                    if (pressedInput & L_JPAD) {
                        cursorIndex = selectedOption - 1;
                        // if less than 0, wrap index back around to file index 2
                        if (cursorIndex < 0) {
                            cursorIndex = OPTION_FILE2;
                        }
                    } else {
                        cursorIndex = CLAMP_BELOW(cursorIndex, OPTION_FILES_END);
                    }
                } else if (pressedInput & (U_JPAD | D_JPAD)) {
                    if (pressedInput & U_JPAD) {
                        cursorIndex = OPTION_COPY;
                        if ((temp_v1 - 1) < (OPTION_FILES_END - 1)) {
                            func_801076D0_filesel(4, 0x2A01);
                        } else {
                            func_801076D0_filesel(4, 0x2A03);
                        }
                        func_80110FB0_filesel(selectedOption);
                    } else {
                        if (D_801142DC_filesel[cursorIndex].unk_00 == unkValue) {
                            cursorIndex = selectedOption + OPTION_FILES_NAME_BEGIN;
                            func_80110FB0_filesel(selectedOption);
                        }
                    }
                }
                break;
            case OPTION_COPY:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    if (temp_v1 == 0) {
                        func_801076D0_filesel(4, 0x2A13);
                    } else {
                        func_801076D0_filesel(4, 0x2A07);
                    }
                    cursorIndex = OPTION_ERASE;
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = OPTION_FILE1;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
            case OPTION_ERASE:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    cursorIndex = OPTION_FILES_END;
                    if ((temp_v1 - 1) < 2) {
                        func_801076D0_filesel(4, 0x2A01);
                    } else {
                        func_801076D0_filesel(4, 0x2A03);
                    }
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = 2;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
            case OPTION_FILE0_NAME:
            case OPTION_FILE1_NAME:
            case OPTION_FILE2_NAME:
                func_801076D0_filesel(4, 0x2A11);
                if (pressedInput & L_JPAD) {
                    cursorIndex = selectedOption;
                    do {
                        cursorIndex -= 1;
                        if (cursorIndex < OPTION_FILES_NAME_BEGIN) {
                            cursorIndex = 7;
                        }
                    } while (D_801142DC_filesel[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_00 != unkValue);
                } else {
                    if (pressedInput & R_JPAD) {
                        cursorIndex = selectedOption;
                        do {
                            // if cursor goes over max, wrap around back to file 0 name
                            if (++cursorIndex > OPTION_MAX) {
                                cursorIndex = OPTION_FILE0_NAME;
                            }
                        } while (D_801142DC_filesel[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_00 != unkValue);
                    }
                }
                if (pressedInput & U_JPAD) {
                    cursorIndex = selectedOption - OPTION_FILES_NAME_BEGIN;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
        }

    checkIfCursorIndexChanged:
        if (selectedOption != cursorIndex) {
            // animate cursor to new position
            func_8010AB60_filesel(18, cursorIndex);
            selectedOption = cursorIndex;

            if (selectedOption < OPTION_FILES_END) {
                func_801110F0_filesel(selectedOption);
            }
        }
        func_8010AB1C_filesel(18, selectedOption);

        animTimerAdjusted = (animTimer < 0) ? animTimer + 7 : animTimer;
        animTimerAdjusted = (animTimerAdjusted >> 3);
        func_8010AB58_filesel(18, -animTimerAdjusted);

        animTimer = (animTimer < 20) ? animTimer + 1 : 0;

        HuPrcVSleep();
    }
    return selectedOption;
}

s32 func_80109904_filesel(s32 arg0) {
    u8 buf[32]; // TODO: figure out correct type of this
    s32 temp_s0;

    bzero(&buf, sizeof(buf));
    func_80112494_filesel(arg0, buf);
    HuPrcSleep(3);
    func_801076D0_filesel(4, 0x2A11);
    temp_s0 = func_8010AC58_filesel(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

s32 func_80109968_filesel(s32 arg0) {
    s32 temp_s0;

    HuPrcSleep(3);
    temp_s0 = func_8010AC58_filesel(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

u32 func_801099A8_filesel(u32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 enabled[3];
    s32 cur;
    s32 timer;
    u16 btn;
    s32 temp;

    cur = arg0;
    timer = 0;
    enabled[0] = arg1;
    enabled[1] = arg2;
    enabled[2] = arg3;
    func_8010AB60_filesel(0x12, cur);
    while (1) {
        HuPrcVSleep();
        func_8010AB1C_filesel(0x12, cur);
        func_8010AB58_filesel(0x12, -(timer / 8));
        timer = (timer < 20) ? timer + 1 : 0;
        btn = D_800D1244_main;
        temp = func_80111B14_filesel(0);
        if (temp != -1) {
            btn |= temp;
        }
        if (D_800D5558_main[0] & B_BUTTON) {
            return -1;
        }
        if (D_800D5558_main[0] & A_BUTTON) {
            HuAudFXPlay(3);
            if (enabled[cur] == 1) {
                break;
            }
        } else if (btn & L_JPAD) {
            do {
                cur--;
                if (cur < 0) {
                    cur = 2;
                }
            } while (enabled[cur] != 1);
            func_8010AB60_filesel(0x12, cur);
        } else if (btn & R_JPAD) {
            do {
                cur++;
                cur = CLAMP_BELOW(cur, 3);
            } while (enabled[cur] != 1);
            func_8010AB60_filesel(0x12, cur);
        }
    }
    return cur;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80109B2C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A028_filesel);

void func_8010A680_filesel(s32 no, f32 x, f32 y, f32 z) {
    s32 no2;
    s32 i;

    i = no;
    no2 = no + 3;
    if (D_801142DC_filesel[no].unk_00 != FS_FILE_USED) {
        func_80106220_filesel(i, 0x1F0029, 0x6A9);
    } else {
        func_80106220_filesel(i, 0x1F002A, 0x6A9);
    }
    func_801064DC_filesel(i, x, y, z);
    func_80106550_filesel(i, 0.8f, 0.8f, 0.8f);
    func_8010684C_filesel(i, 0);
    func_8010671C_filesel(i, 1);
    func_8010669C_filesel(i);
    func_80106220_filesel(no2, D_801127B0_filesel[no], 0x6A9);
    func_801064DC_filesel(no2, x, y, z);
    func_80106550_filesel(no2, 0.8f, 0.8f, 0.8f);
    func_8010684C_filesel(no2, 0);
    func_8010671C_filesel(no2, 1);
    func_8010669C_filesel(no2);
}

void func_8010A7D8_filesel(s16 arg0) {
    f32 t;
    f32 angle;
    f32 scale;

    func_8001C2FC_main(arg0, 0x22000, 0x20000);
    func_8001C448_main(arg0);
    func_8001C954_main(arg0);
    HuPrcVSleep();
    t = 0.0f;
    angle = 0.0f;
    scale = 1.0f;
    while (1) {
        if (t > 1.0f) {
            break;
        }
        D_800A0A7C_main = angle;
        func_8001D558_main(arg0, t, scale, 2);
        angle += 46.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        t += 0.1f;
        scale += (10.0f - scale) / 67.0f * 4.0f;
        HuPrcVSleep();
    }
    func_8001C258_main(arg0, 4, 4);
    func_8001ACDC_main(arg0);
    HuPrcSleep(3);
}

void func_8010A978_filesel(s32 arg0) {
    if (arg0 >= 6) {
        arg0 = 5;
    }
    func_80105FBC_filesel(0x13, arg0 * 10 + 0x68, 0x3D);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AF0_filesel);

void func_8010A9B4_filesel(s32 arg0, u32 arg1, s32 *arg2, s32 *arg3) {
    Vec pos;
    Vec2f scr;
    s32 x;
    s32 y;

    x = D_801127BC_filesel[arg1][0];
    y = D_801127BC_filesel[arg1][1];
    switch (arg1) {
        case 0:
        case 1:
        case 2:
            func_801065B8_filesel(arg1, &pos.x, &pos.y, &pos.z);
            pos.x += 30.0f;
            pos.y += 300.0f;
            Hu3DCam3DToScreen(0, &pos, &scr);
            x = scr.x;
            y = scr.y;
            break;
        case 3:
        case 4:
            x = D_801127BC_filesel[arg1][0];
            y = D_801127BC_filesel[arg1][1];
            break;
        case 5:
            HuVecCopyXYZ(&pos, -400.0f, 0.0f, 0.0f);
            Hu3DCam3DToScreen(0, &pos, &scr);
            x = scr.x + 31.0f;
            y = 0xA8;
            break;
        case 6:
            HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
            Hu3DCam3DToScreen(0, &pos, &scr);
            x = scr.x + 31.0f;
            y = 0xA8;
            break;
        case 7:
            HuVecCopyXYZ(&pos, 400.0f, 0.0f, 0.0f);
            Hu3DCam3DToScreen(0, &pos, &scr);
            x = scr.x + 31.0f;
            y = 0xA8;
            break;
    }
    *arg2 = x;
    *arg3 = y;
}

void func_8010AB1C_filesel(s32 arg0, u32 arg1) {
    s32 x;
    s32 y;

    func_8010A9B4_filesel(arg0, arg1, &x, &y);
    func_80105FBC_filesel(arg0, x, y);
}

void func_8010AB58_filesel(s32 arg0, u32 arg1) {
}

void func_8010AB60_filesel(s32 arg0, u32 arg1) {
    s32 tx;
    s32 ty;
    s32 sx;
    s32 sy;
    s32 i;
    f32 t;

    func_8010A9B4_filesel(arg0, arg1, &tx, &ty);
    func_80106014_filesel(arg0, &sx, &sy);
    i = 0;
    do {
        t = i * 0.25f;
        func_80105FBC_filesel(arg0, sx + t * (tx - sx), sy + t * (ty - sy));
        i++;
        HuPrcVSleep();
    } while (i < 5);
    func_80105FBC_filesel(arg0, tx, ty);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010AC58_filesel);

s32 func_8010B4D0_filesel(s32 arg0, s32 arg1) {
    u8 *p = D_801127FC_filesel[arg0];
    s32 hi = p[arg1 * 2] << 8;

    return p[arg1 * 2 + 1] | hi;
}

s32 func_8010B4FC_filesel(s32 arg0, s32 arg1) {
    u8 *p = D_80112844_filesel[arg0];
    s32 hi = p[arg1 * 2] << 8;

    return p[arg1 * 2 + 1] | hi;
}

s32 func_8010B528_filesel(s32 arg0, s32 arg1) {
    u8 *p = D_8011288C_filesel[arg1];
    s32 hi = p[arg0 * 2] << 8;

    return p[arg0 * 2 + 1] | hi;
}

void func_8010B554_filesel(void *arg0) {
    bzero(D_80114478_filesel.name, sizeof(D_80114478_filesel.name));
    bcopy(arg0, D_80114478_filesel.name, sizeof(D_80114478_filesel.name));
}

void func_8010B598_filesel(void *arg0) {
    bzero(arg0, sizeof(D_80114478_filesel.name));
    bcopy(D_80114478_filesel.name, arg0, sizeof(D_80114478_filesel.name));
}

s32 func_8010B5D4_filesel(s32 arg0, s32 arg1, s32 arg2, s16 *arg3, s16 *arg4) {
    s32 x = 0x2F;
    s32 y = 0x67;

    switch (arg0) {
        case 4:
        case 5:
            x += 5;
            y += 12;
            if (arg1 >= 10) {
                x += 5;
            }
            if (arg1 >= 11) {
                if (arg1 < 15) {
                    x += (arg1 - 10) * 2;
                } else {
                    x += 10;
                }
            }
            x += arg1 * 12;
            y += arg2 * 13;
            break;
        case 6:
            x += 0x2A;
            y += 12;
            x += arg1 * 12;
            y += arg2 * 13;
            break;
        default:
            x = 0;
            y = 0;
            break;
    }
    *arg3 = x;
    *arg4 = y;
    return 0;
}

void func_8010B684_filesel(s32 arg0) {
    if (arg0 != -1) {
        func_80105F24_filesel(arg0);
    }
    if (arg0 != 4) {
        func_80105F54_filesel(4);
    }
    if (arg0 != 5) {
        func_80105F54_filesel(5);
    }
    if (arg0 != 6) {
        func_80105F54_filesel(6);
    }
}

void func_8010B6F4_filesel(s32 arg0) {
    if (arg0 != -1) {
        func_80105F24_filesel(arg0);
    }
    if (arg0 != 7) {
        func_80105F54_filesel(7);
        func_80105F54_filesel(0x30);
    } else {
        func_80105F24_filesel(0x30);
    }
    if (arg0 != 8) {
        func_80105F54_filesel(8);
        func_80105F54_filesel(0x31);
    } else {
        func_80105F24_filesel(0x31);
    }
    if (arg0 != 9) {
        func_80105F54_filesel(9);
        func_80105F54_filesel(0x32);
    } else {
        func_80105F24_filesel(0x32);
    }
    if (arg0 != 10) {
        func_80105F54_filesel(10);
        func_80105F54_filesel(0x33);
    } else {
        func_80105F24_filesel(0x33);
    }
    if (arg0 != 11) {
        func_80105F54_filesel(11);
        func_80105F54_filesel(0x34);
    } else {
        func_80105F24_filesel(0x34);
    }
    D_80114478_filesel.blink = 0;
}

void func_8010B80C_filesel(s32 arg0) {
    s32 cnt;
    s32 pos;
    s32 *p;
    f32 f;
    u8 alpha;

    cnt = D_80114478_filesel.blink;
    if (cnt < 0) {
        cnt = -cnt;
    }
    pos = D_80114478_filesel.blink >= 0;
    f = 1.0f;
    if (f > 1.0f) { /* dead clamp: retail does not fold f * 255 */
        f = 1.0f;
    }
    cnt++;
    if (pos) {
        alpha = f * 255.0f;
    } else {
        alpha = (1.0f - f) * 255.0f;
    }
    p = &D_80114478_filesel.blink;
    *p = cnt;
    if (pos < 0) {
        *p = -cnt;
    }
    if (arg0 != -1) {
        func_80106094_filesel(arg0, alpha);
    }
    if (arg0 != 7) {
        func_80106094_filesel(7, alpha);
    }
    if (arg0 != 8) {
        func_80106094_filesel(8, alpha);
    }
    if (arg0 != 9) {
        func_80106094_filesel(9, alpha);
    }
    if (arg0 != 10) {
        func_80106094_filesel(10, alpha);
    }
    if (arg0 != 11) {
        func_80106094_filesel(11, alpha);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B18_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B24_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B30_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B3C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B48_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B54_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B60_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B6C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B78_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B84_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B90_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112B9C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BA8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BB4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BC0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BCC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BD8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BF0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112BFC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C08_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C14_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C20_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C2C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C38_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C44_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C50_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C5C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C68_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C74_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C80_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C8C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112C98_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CA4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CB0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CBC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CC8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112CE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D00_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D1C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D38_filesel);

s32 func_8010B998_filesel(s32 btn) {
    s32 len;

    if (btn & START_BUTTON) {
        D_80114478_filesel.done = 1;
        D_80114478_filesel.button = 11;
        func_8010BE14_filesel();
        func_8010B6F4_filesel(D_80114478_filesel.button);
        return 0;
    }
    if (D_800D5558_main[0] & A_BUTTON) {
        switch (D_80114478_filesel.button) {
            case 7:
            case 8:
                HuAudFXPlay(1);
                D_80114478_filesel.group = 6;
                break;
            case 9:
                HuAudFXPlay(1);
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                break;
            case 10:
                D_80114478_filesel.name[D_80114478_filesel.len] = 0;
                if (D_80114478_filesel.len > 0) {
                    HuAudFXPlay(0x2EF);
                    D_80114478_filesel.len--;
                } else {
                    HuAudFXPlay(5);
                }
                D_80114478_filesel.name[D_80114478_filesel.len] = 0;
                func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
                func_8010A978_filesel(D_80114478_filesel.len + 1);
                break;
            case 11:
                HuAudFXPlay(2);
                if ((u16)((D_80114478_filesel.name[0] << 8) | D_80114478_filesel.name[1])) {
                    return 11;
                }
                bcopy(D_80114478_filesel.saved, D_80114478_filesel.name, sizeof(D_80114478_filesel.name));
                func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
                len = func_801125E8_filesel((s32)D_80114478_filesel.name);
                D_80114478_filesel.name[len] = 0;
                D_80114478_filesel.len = len;
                func_8010A978_filesel(len + 1);
                break;
        }
        func_8010B6F4_filesel(D_80114478_filesel.button);
        func_8010B684_filesel(D_80114478_filesel.group);
        return 0;
    }
    if (D_800D5558_main[0] & B_BUTTON) {
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        if (D_80114478_filesel.len > 0) {
            HuAudFXPlay(0x2EF);
            D_80114478_filesel.len--;
            D_80114478_filesel.name[D_80114478_filesel.len] = 0;
            func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
            func_8010A978_filesel(D_80114478_filesel.len + 1);
        } else {
            if (D_80114478_filesel.button == 11) {
                return -1;
            }
            HuAudFXPlay(1);
            D_80114478_filesel.button = 11;
            func_8010BE14_filesel();
            func_8010B6F4_filesel(D_80114478_filesel.button);
        }
        func_8010B684_filesel(D_80114478_filesel.group);
        return 0;
    }
    if (btn & U_JPAD) {
        D_80114478_filesel.done = 0;
        func_8010B6F4_filesel(-1);
        D_80114478_filesel.line = 4;
        func_8010BDC4_filesel();
    } else if (btn & D_JPAD) {
        D_80114478_filesel.done = 0;
        func_8010B6F4_filesel(-1);
        D_80114478_filesel.line = 0;
        func_8010BDC4_filesel();
    } else if (btn & L_JPAD) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.button) {
            case 10:
                D_80114478_filesel.button = 11;
                break;
            case 11:
                D_80114478_filesel.button = 10;
                break;
        }
        func_8010B6F4_filesel(D_80114478_filesel.button);
    } else if (btn & R_JPAD) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.button) {
            case 10:
                D_80114478_filesel.button = 11;
                break;
            case 11:
                D_80114478_filesel.button = 10;
                break;
        }
        func_8010B6F4_filesel(D_80114478_filesel.button);
    } else if (btn & Z_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 5:
                D_80114478_filesel.group = 6;
                break;
            case 4:
                D_80114478_filesel.group = 6;
                break;
            case 6:
                D_80114478_filesel.group = 6;
                break;
        }
        func_8010B684_filesel(D_80114478_filesel.group);
    } else if (btn & R_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 5:
                D_80114478_filesel.group = 6;
                break;
            case 4:
                D_80114478_filesel.group = 6;
                break;
            case 6:
                D_80114478_filesel.group = 6;
                break;
        }
        func_8010B684_filesel(D_80114478_filesel.group);
    }
    return 0;
}

void func_8010BDC4_filesel(void) {
    s16 x;
    s16 y;

    func_8010B5D4_filesel(D_80114478_filesel.group, D_80114478_filesel.col, D_80114478_filesel.line, &x, &y);
    func_80105FBC_filesel(0x11, x, y);
    func_80105F24_filesel(0x11);
}

void func_8010BE14_filesel(void) {
    func_80105F54_filesel(0x11);
}

s32 func_8010BE30_filesel(s32 btn) {
    if (btn & START_BUTTON) {
        D_80114478_filesel.done = 1;
        D_80114478_filesel.button = 11;
        func_8010BE14_filesel();
        func_8010B6F4_filesel(D_80114478_filesel.button);
    } else if (btn & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
        func_8010BDC4_filesel();
        if (btn & U_JPAD) {
            if (--D_80114478_filesel.line < 0) {
                D_80114478_filesel.line = 0;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 7;
                func_8010B6F4_filesel(7);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & D_JPAD) {
            if (++D_80114478_filesel.line >= 5) {
                D_80114478_filesel.line = 4;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 7;
                func_8010B6F4_filesel(7);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & L_JPAD) {
            if (--D_80114478_filesel.col < 0) {
                D_80114478_filesel.col = 17;
            }
            func_8010BDC4_filesel();
        } else if (btn & R_JPAD) {
            if (++D_80114478_filesel.col >= 18) {
                D_80114478_filesel.col = 0;
            }
            func_8010BDC4_filesel();
        }
    } else if (D_800D5558_main[0] & A_BUTTON) {
        if (D_80114478_filesel.len < 5) {
            HuAudFXPlay(0x2EE);
            D_80114478_filesel.name[D_80114478_filesel.len] =
                func_8010B4D0_filesel(D_80114478_filesel.col, D_80114478_filesel.line);
            D_80114478_filesel.len++;
            D_80114470_filesel = 1;
        }
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
        func_8010A978_filesel(D_80114478_filesel.len + 1);
        if (D_80114478_filesel.len >= 5) {
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (D_800D5558_main[0] & B_BUTTON) {
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        if (D_80114478_filesel.len > 0) {
            HuAudFXPlay(0x2EF);
            D_80114478_filesel.len--;
            D_80114478_filesel.name[D_80114478_filesel.len] = 0;
            func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
            func_8010A978_filesel(D_80114478_filesel.len + 1);
            D_80114470_filesel = 1;
        } else {
            HuAudFXPlay(1);
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (btn & Z_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 4:
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                func_8010BDC4_filesel();
                break;
            case 5:
                D_80114478_filesel.group = 4;
                break;
            case 6:
                D_80114478_filesel.group = 5;
                break;
        }
        func_8010B684_filesel(D_80114478_filesel.group);
    } else if (btn & R_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 4:
                D_80114478_filesel.group = 5;
                break;
            case 5:
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                func_8010BDC4_filesel();
                break;
            case 6:
                D_80114478_filesel.group = 4;
                break;
        }
        func_8010BDC4_filesel();
        func_8010B684_filesel(D_80114478_filesel.group);
    }
    return 0;
}

s32 func_8010C25C_filesel(s32 btn) {
    if (btn & START_BUTTON) {
        D_80114478_filesel.done = 1;
        D_80114478_filesel.button = 11;
        func_8010BE14_filesel();
        func_8010B6F4_filesel(D_80114478_filesel.button);
    } else if (btn & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
        func_8010BDC4_filesel();
        if (btn & U_JPAD) {
            if (--D_80114478_filesel.line < 0) {
                D_80114478_filesel.line = 0;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 8;
                func_8010B6F4_filesel(8);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & D_JPAD) {
            if (++D_80114478_filesel.line >= 5) {
                D_80114478_filesel.line = 4;
                D_80114478_filesel.done = 1;
                D_80114478_filesel.button = 8;
                func_8010B6F4_filesel(8);
                func_8010BE14_filesel();
            } else {
                func_8010BDC4_filesel();
            }
        } else if (btn & L_JPAD) {
            if (--D_80114478_filesel.col < 0) {
                D_80114478_filesel.col = 17;
            }
            func_8010BDC4_filesel();
        } else if (btn & R_JPAD) {
            if (++D_80114478_filesel.col >= 18) {
                D_80114478_filesel.col = 0;
            }
            func_8010BDC4_filesel();
        }
    } else if (D_800D5558_main[0] & A_BUTTON) {
        if (D_80114478_filesel.len < 5) {
            HuAudFXPlay(0x2EE);
            D_80114478_filesel.name[D_80114478_filesel.len] =
                func_8010B4FC_filesel(D_80114478_filesel.col, D_80114478_filesel.line);
            D_80114478_filesel.len++;
            D_80114470_filesel = 1;
        }
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
        func_8010A978_filesel(D_80114478_filesel.len + 1);
        if (D_80114478_filesel.len >= 5) {
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (D_800D5558_main[0] & B_BUTTON) {
        D_80114478_filesel.name[D_80114478_filesel.len] = 0;
        if (D_80114478_filesel.len > 0) {
            HuAudFXPlay(0x2EF);
            D_80114478_filesel.len--;
            D_80114478_filesel.name[D_80114478_filesel.len] = 0;
            func_801076D0_filesel(10, (u32)D_80114478_filesel.name);
            func_8010A978_filesel(D_80114478_filesel.len + 1);
            D_80114470_filesel = 1;
        } else {
            HuAudFXPlay(1);
            D_80114478_filesel.done = 1;
            D_80114478_filesel.button = 11;
            func_8010B6F4_filesel(11);
            func_8010B684_filesel(D_80114478_filesel.group);
            func_8010BE14_filesel();
        }
    } else if (btn & Z_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 4:
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                func_8010BDC4_filesel();
                break;
            case 5:
                D_80114478_filesel.group = 4;
                break;
            case 6:
                D_80114478_filesel.group = 5;
                break;
        }
        func_8010B684_filesel(D_80114478_filesel.group);
    } else if (btn & R_TRIG) {
        HuAudFXPlay(1);
        switch (D_80114478_filesel.group) {
            case 4:
                D_80114478_filesel.group = 5;
                break;
            case 5:
                D_80114478_filesel.group = 6;
                if (D_80114478_filesel.col >= 13) {
                    D_80114478_filesel.col = 12;
                }
                func_8010BDC4_filesel();
                break;
            case 6:
                D_80114478_filesel.group = 4;
                break;
        }
        func_8010BDC4_filesel();
        func_8010B684_filesel(D_80114478_filesel.group);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010C688_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D6C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D7C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D8C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112D9C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112DAC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112DBC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010C9B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010CCA8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010D13C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010D660_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DD54_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DDC0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DEEC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DF58_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010DFF4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010E1B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010E250_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010E740_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010E864_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F10C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F12C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F168_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F5C8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F65C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112DF8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112E08_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F678_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F760_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F844_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F874_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F8A4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FBE0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FC58_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FF48_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FFA0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801102F0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110320_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801103A0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801106FC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8011072C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801107AC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110B4C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110B7C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110C84_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110CC0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110D0C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110E70_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110F04_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80110FB0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111004_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801110F0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111144_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8011132C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8011139C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801113E8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111660_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111790_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111944_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801119F4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111A08_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111B14_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111C30_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111CBC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111E78_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80111FFC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112184_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801122B0_filesel);

s32 func_80112494_filesel(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_801142DC_filesel[arg0].unk_01[i] = arg1[i];
    }

    // terminate string
    D_801142DC_filesel[arg0].unk_01[i] = '\0';
    D_801142DC_filesel[arg0].unk_01[i + 1] = '\0';
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112508_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112584_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801125E8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112630_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112684_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801126C0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80112758_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112E68_filesel);
