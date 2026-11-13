#include "common.h"
#include "game/vibrator.h"

#include "filesel.h"
#include "mallocblock.h"

/* model effect slot: D_80114598_filesel[3] */
typedef struct FsEffect {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ Vec start;
    /* 0x10 */ Vec end;
    /* 0x1C */ char unk1C[0x34];
    /* 0x50 */ s32 time; /* also the wobble angle of func_80111004 */
    /* 0x54 */ s32 angle;
    /* 0x58 */ s32 total;
} FsEffect; /* size = 0x5C */

extern FsEffect D_80114598_filesel[3];


/* model move slot: D_80114508_filesel[4] */
typedef struct FsMove {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 time;
    /* 0x08 */ s32 total;
    /* 0x0C */ Vec start;
    /* 0x18 */ Vec end;
} FsMove; /* size = 0x24 */

extern Vec D_80112910_filesel[][2];
extern Vec D_80112958_filesel[];
extern Vec D_8011297C_filesel[];
extern FsMove D_80114508_filesel[4];


extern Vec D_801128A4_filesel[];
extern Vec D_801128C8_filesel[][2];


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

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80108D74_filesel);

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

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_801099A8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_80109B2C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AE8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A028_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A680_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A7D8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A978_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112AF0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010A9B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010AB1C_filesel);

void func_8010AB58_filesel(s32 arg0, u32 arg1) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010AB60_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010AC58_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B4D0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B4FC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B528_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B554_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B598_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B5D4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B684_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B6F4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B80C_filesel);

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

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010B998_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010BDC4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010BE14_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010BE30_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010C25C_filesel);

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

void func_8010F5C8_filesel(void) {
    func_80106344_filesel(0);
    func_80106344_filesel(1);
    func_80106344_filesel(2);
    func_80106344_filesel(3);
    func_80106344_filesel(4);
    func_80106344_filesel(5);
    func_80107490_filesel(1);
    func_80107490_filesel(2);
    func_80107490_filesel(3);
    func_80105EC0_filesel(0xD);
    func_80105EC0_filesel(0xE);
    func_80105EC0_filesel(0xF);
    func_80105EC0_filesel(0x12);
    func_80107490_filesel(0);
    func_8010F65C_filesel();
    func_80107490_filesel(4);
}

void func_8010F65C_filesel(void) {
    func_80105EC0_filesel(0xC);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112DF8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516AE0", D_80112E08_filesel);

void func_8010F678_filesel(u32 arg0) {
    s32 dataNum;
    s32 x;
    s32 y;

    switch (arg0) {
    case 0:
        dataNum = 0x1F001C;
        x = 0x5B;
        y = 0x21;
        break;
    case 1:
        dataNum = 0x1F001D;
        x = 0x5E;
        y = 0x21;
        break;
    case 2:
        dataNum = 0x1F001E;
        x = 0x36;
        y = 0x21;
        break;
    case 3:
        dataNum = 0x1F001F;
        x = 0x3F;
        y = 0x21;
        break;
    case 4:
        dataNum = 0x1F0022;
        x = 0x79;
        y = 0x1E;
        break;
    default:
        dataNum = 0;
        y = 0;
        x = 0;
        break;
    }
    func_80105E7C_filesel(0xC, dataNum);
    func_80106044_filesel(0xC, 1.0f, 1.0f);
    func_80106094_filesel(0xC, 0x100);
    func_80105FBC_filesel(0xC, x, y);
}

void func_8010F760_filesel(s32 arg0, s32 arg1) {
    Vec pos;
    Vec2f screen;
    s32 x;
    s32 dataNum;

    dataNum = (arg1 != 0) ? 0x1F0020 : 0x1F0021;
    pos.x = D_801128A4_filesel[arg0].x;
    pos.y = D_801128A4_filesel[arg0].y;
    pos.z = D_801128A4_filesel[arg0].z;
    Hu3DCam3DToScreen(0, &pos, &screen);
    x = screen.x;
    arg0 += 0xD;
    func_80105E48_filesel(arg0, dataNum);
    func_80106044_filesel(arg0, 1.0f, 1.0f);
    func_80106094_filesel(arg0, 0x100);
    func_80105FBC_filesel(arg0, x, 0xB1);
}

void func_8010F844_filesel(s32 arg0) {
    func_80105F84_filesel(arg0 + 0xD);
    func_80107670_filesel(arg0 + 1);
}

void func_8010F874_filesel(s32 arg0) {
    func_80105FA0_filesel(arg0 + 0xD);
    func_801076A0_filesel(arg0 + 1);
}

// work[0] is loaded into a0 and copied to s1 after the time conversions (masked 6)
#ifdef NON_MATCHING
void func_8010F8A4_filesel(omObjData *obj) {
    s32 no;
    Vec pos;
    Vec rot;
    f32 total;
    f32 time;
    Vec *start;
    Vec *end;
    f32 t;
    f32 s;
    f32 scale;

    no = obj->work[0];
    total = obj->work[1];
    time = obj->work[2];
    start = &D_801128C8_filesel[no][0];
    end = &D_801128C8_filesel[no][1];
    t = time / total;
    if (t > 1.0f) {
        t = 1.0f;
    }
    s = t * 0.9f + 0.1f;
    scale = s * 0.8f;
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    pos.x = (end->x - start->x) * s + start->x;
    pos.y = (end->y - start->y) * s + start->y;
    pos.z = (end->z - start->z) * s + start->z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    func_80106474_filesel(no + 3, rot.x, rot.y, rot.z);
    if (total <= time) {
        func_801064DC_filesel(no, end->x, end->y, end->z);
        func_801064DC_filesel(no + 3, end->x, end->y, end->z);
        func_80106550_filesel(no, 0.8f, 0.8f, 0.8f);
        func_80106550_filesel(no + 3, 0.8f, 0.8f, 0.8f);
        omDelObj(obj);
        return;
    }
    time += 1.0f;
    obj->work[2] = time;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010F8A4_filesel);
#endif

omObjData *func_8010FBE0_filesel(u32 arg0, u32 arg1) {
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_8010F8A4_filesel);
    obj->work[0] = arg0;
    obj->work[1] = arg1;
    obj->work[2] = 0;
    func_801066DC_filesel(arg0);
    func_801066DC_filesel(arg0 + 3);
    return obj;
}

// float register allocation of the 0.9/0.1 constants (masked 4)
#ifdef NON_MATCHING
void func_8010FC58_filesel(omObjData *obj) {
    Vec pos;
    Vec rot;
    s32 no;
    Vec *start;
    Vec *end;
    f32 total;
    f32 time;
    f32 t;
    f32 scale;

    no = obj->work[0];
    start = &D_80112910_filesel[no][0];
    end = &D_80112910_filesel[no][1];
    total = obj->work[1];
    time = obj->work[2];
    t = time / total;
    t = 1.0f - t;
    if (t < 0.0f) {
        t = 0.0f;
    }
    scale = (t * 0.9f + 0.1f) * 0.8f;
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    pos.x = (end->x - start->x) * (t * 0.9f + 0.1f) + start->x;
    pos.y = (end->y - start->y) * (t * 0.9f + 0.1f) + start->y;
    pos.z = (end->z - start->z) * (t * 0.9f + 0.1f) + start->z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    if (time == total) {
        omDelObj(obj);
        func_8010669C_filesel(no);
        func_8010669C_filesel(no + 3);
        return;
    }
    time += 1.0f;
    obj->work[2] = time;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516AE0", func_8010FC58_filesel);
#endif

void func_8010FF48_filesel(u32 arg0, u32 arg1) {
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_8010FC58_filesel);
    obj->work[0] = arg0;
    obj->work[1] = arg1;
    obj->work[2] = 0;
}

void func_8010FFA0_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    Vec rot;
    s32 no;
    f32 total;
    f32 time;
    f32 lo;
    f32 t;
    f32 scale;
    f32 u;
    f32 f;

    lo = 0.48f;
    no = obj->work[0];
    total = D_80114508_filesel[no].total;
    time = D_80114508_filesel[no].time;
    HuVecCopy3F(&start, &D_80112958_filesel[no]);
    HuVecCopyXYZ(&end, -400.0f, 340.0f, 0.0f);
    t = time / total;
    if (t > 1.0f) {
        t = 1.0f;
    }
    scale = lo + (0.8f - lo) * (1.0f - t);
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    u = t - 0.8f;
    f = u * -1.6666666f * u + 1.0666666242811431;
    pos.x = (end.x - start.x) * t + start.x;
    pos.y = (end.y - start.y) * f + start.y;
    pos.z = (end.z - start.z) * t + start.z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    func_80106474_filesel(no + 3, rot.x, rot.y, rot.z);
    if (total <= time) {
        func_801064DC_filesel(no, end.x, end.y, end.z);
        func_801064DC_filesel(no + 3, end.x, end.y, end.z);
        func_80106550_filesel(no, lo, lo, lo);
        func_80106550_filesel(no + 3, lo, lo, lo);
        func_80106474_filesel(no, 0.0f, 0.0f, 0.0f);
        func_80106474_filesel(no + 3, 0.0f, 0.0f, 0.0f);
        omDelObj(obj);
    } else {
        time += 1.0f;
        D_80114508_filesel[no].time = time;
    }
}

void func_801102F0_filesel(s32 arg0) {
    omDelObj(D_80114508_filesel[arg0].obj);
}

void func_80110320_filesel(u32 arg0, s32 arg1) {
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_8010FFA0_filesel);
    obj->work[0] = arg0;
    D_80114508_filesel[arg0].obj = obj;
    D_80114508_filesel[arg0].total = arg1;
    D_80114508_filesel[arg0].time = 0;
}

void func_801103A0_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    Vec rot;
    s32 no;
    f32 total;
    f32 time;
    f32 lo;
    f32 t;
    f32 scale;
    f32 u;
    f32 f;

    lo = 0.48f;
    no = obj->work[0];
    total = D_80114508_filesel[no].total;
    time = D_80114508_filesel[no].time;
    HuVecCopy3F(&start, &D_8011297C_filesel[no]);
    HuVecCopyXYZ(&end, -400.0f, 340.0f, 0.0f);
    t = 1.0f - time / total;
    if (t < 0.0f) {
        t = 0.0f;
    }
    scale = lo + (0.8f - lo) * (1.0f - t);
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    u = t - 0.8f;
    f = u * -1.6666666f * u + 1.0666666242811431;
    pos.x = (end.x - start.x) * t + start.x;
    pos.y = (end.y - start.y) * f + start.y;
    pos.z = (end.z - start.z) * t + start.z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    func_80106474_filesel(no + 3, rot.x, rot.y, rot.z);
    if (total <= time) {
        func_801064DC_filesel(no, start.x, start.y, start.z);
        func_801064DC_filesel(no + 3, start.x, start.y, start.z);
        func_80106550_filesel(no, 0.8f, 0.8f, 0.8f);
        func_80106550_filesel(no + 3, 0.8f, 0.8f, 0.8f);
        func_80106474_filesel(no, 0.0f, 0.0f, 0.0f);
        func_80106474_filesel(no + 3, 0.0f, 0.0f, 0.0f);
        omDelObj(obj);
    } else {
        time += 1.0f;
        D_80114508_filesel[no].time = time;
    }
}

void func_801106FC_filesel(s32 arg0) {
    omDelObj(D_80114508_filesel[arg0].obj);
}

void func_8011072C_filesel(u32 arg0, s32 arg1) {
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_801103A0_filesel);
    obj->work[0] = arg0;
    D_80114508_filesel[arg0].obj = obj;
    D_80114508_filesel[arg0].time = 0;
    D_80114508_filesel[arg0].total = arg1;
}

void func_801107AC_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    Vec rot;
    s32 no;
    f32 total;
    f32 time;
    f32 t;
    f32 scale;
    f32 f;

    no = obj->work[0];
    total = D_80114508_filesel[no].total;
    time = D_80114508_filesel[no].time;
    HuVecCopy3F(&start, &D_80114508_filesel[no].start);
    HuVecCopy3F(&end, &D_80114508_filesel[no].end);
    t = time / total;
    if (t > 1.0f) {
        t = 1.0f;
    }
    if (end.y - start.y < 0.0f) {
        scale = t * (0.8f - 0.48) + 0.48;
        func_80106550_filesel(no, scale, scale, scale);
        func_80106550_filesel(no + 3, scale, scale, scale);
    }
    if (end.y - start.y < 0.0f) {
        f = -((0.2f - t) * -1.6666666f * (0.2f - t) + 1.0666666f) + 1.0f;
    } else {
        f = (t - 0.8f) * -1.6666666f * (t - 0.8f) + 1.0666666f;
    }
    pos.x = (end.x - start.x) * t + start.x;
    pos.y = (end.y - start.y) * f + start.y;
    pos.z = (end.z - start.z) * t + start.z;
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    rot.x = rot.y = rot.z = 0.0f;
    rot.y = (t * 3.0f - (s32)(t * 3.0f)) * 360.0f;
    func_80106474_filesel(no, rot.x, rot.y, rot.z);
    func_80106474_filesel(no + 3, rot.x, rot.y, rot.z);
    if (total <= time) {
        func_801064DC_filesel(no, end.x, end.y, end.z);
        func_801064DC_filesel(no + 3, end.x, end.y, end.z);
        func_80106474_filesel(no, 0.0f, 0.0f, 0.0f);
        func_80106474_filesel(no + 3, 0.0f, 0.0f, 0.0f);
        omDelObj(obj);
    } else {
        time += 1.0f;
        D_80114508_filesel[no].time = time;
    }
}

void func_80110B4C_filesel(s32 arg0) {
    omDelObj(D_80114508_filesel[arg0].obj);
}

omObjData *func_80110B7C_filesel(u32 arg0, f32 x, f32 y, f32 z, s32 time) {
    f32 px;
    f32 py;
    f32 pz;
    omObjData *obj;

    obj = omAddObj(6, 0, 0, -1, func_801107AC_filesel);
    obj->work[0] = arg0;
    D_80114508_filesel[arg0].obj = obj;
    D_80114508_filesel[arg0].total = time;
    D_80114508_filesel[arg0].time = 0;
    func_801065B8_filesel(arg0, &px, &py, &pz);
    HuVecCopyXYZ(&D_80114508_filesel[arg0].start, px, py, pz);
    HuVecCopyXYZ(&D_80114508_filesel[arg0].end, x, y, z);
    return obj;
}

void func_80110C84_filesel(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80114598_filesel[i].obj = NULL;
    }
}

void func_80110CC0_filesel(s32 arg0) {
    omDelObj(D_80114598_filesel[arg0].obj);
    D_80114598_filesel[arg0].obj = NULL;
}

void func_80110D0C_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    u32 no;
    s32 mdl;
    f32 r;
    f32 t;

    no = obj->work[0];
    mdl = no;
    r = (f32)D_80114598_filesel[no].time / (f32)D_80114598_filesel[no].total;
    t = (r > 1.0f) ? 1.0f : r;
    HuVecCopy3F(&start, &D_80114598_filesel[no].start);
    HuVecCopy3F(&end, &D_80114598_filesel[no].end);
    HuVecCopyXYZ(&pos, (end.x - start.x) * t + start.x, (end.y - start.y) * t + start.y,
                 (end.z - start.z) * t + start.z);
    func_801064DC_filesel(mdl, pos.x, pos.y, pos.z);
    if (t > 1.0f) {
        func_80110CC0_filesel(no);
    }
}

void func_80110E70_filesel(u32 arg0, omObjFunc func) {
    omObjData *obj;

    if (D_80114598_filesel[arg0].obj != NULL) {
        omDelObj(D_80114598_filesel[arg0].obj);
    }
    obj = omAddObj(6, 0, 0, -1, func);
    obj->work[0] = arg0;
    D_80114598_filesel[arg0].obj = obj;
}

/* Retail copies the slot's start into a local and builds the target in another local: the
   slot's start, end, time and total are never set (see func_80110D0C_filesel). */
void func_80110F04_filesel(s32 arg0, f32 x, f32 y, f32 z) {
    Vec pos;
    Vec end;

    func_80110E70_filesel(arg0, func_80110D0C_filesel);
    func_8010642C_filesel(arg0);
    func_801065B8_filesel(arg0, &pos.x, &pos.y, &pos.z);
    HuVecCopy3F(&pos, &D_80114598_filesel[arg0].start);
    HuVecCopyXYZ(&end, x, y, z);
}

void func_80110FB0_filesel(u32 arg0) {
    func_80110CC0_filesel(arg0);
    func_80106550_filesel(arg0, 0.8f, 0.8f, 0.8f);
    func_80106550_filesel(arg0 + 3, 0.8f, 0.8f, 0.8f);
}

void func_80111004_filesel(omObjData *obj) {
    u32 no;
    s32 angle;
    f32 s;
    f32 sx;
    f32 sy;

    no = obj->work[0];
    angle = D_80114598_filesel[no].time;
    angle += 27;
    if (angle > 360) {
        angle -= 360;
    }
    D_80114598_filesel[no].time = angle;
    s = sindf(angle) * 0.1f;
    sx = 0.8f + s;
    sy = 0.8f - s;
    func_80106550_filesel(no, sx, sy, sx);
    func_80106550_filesel(no + 3, sx, sy, sx);
}

void func_801110F0_filesel(u32 arg0) {
    func_80110E70_filesel(arg0, func_80111004_filesel);
    D_80114598_filesel[arg0].time = 0;
    func_8010642C_filesel(arg0);
}

void func_80111144_filesel(omObjData *obj) {
    u32 no;
    s32 mdl;
    s32 angle;
    s32 time;
    s32 total;
    f32 r;
    f32 t;
    f32 a;
    f32 b;

    no = obj->work[0];
    mdl = no;
    angle = D_80114598_filesel[no].angle;
    time = D_80114598_filesel[no].time;
    total = D_80114598_filesel[no].total;
    r = 1.0f - time * 0.022222223f;
    t = (r < 0.0f) ? 0.0f : r;
    angle += 27;
    if (angle > 360.0f) {
        angle = angle - 360.0f;
    }
    a = 0.0f;
    b = 0.0f;
    if (time >= total) {
        func_80110FB0_filesel(mdl);
    } else {
        a = sindf(angle) * 0.3f * t;
        b = 1.0f / (a + 1.0f) - 1.0f;
    }
    D_80114598_filesel[no].angle = angle;
    D_80114598_filesel[no].time = time + 1;
    func_80106550_filesel(no, a + 0.8f, b + 0.8f, a + 0.8f);
    func_80106550_filesel(no + 3, a + 0.8f, b + 0.8f, a + 0.8f);
}

void func_8011132C_filesel(s32 arg0) {
    func_80110E70_filesel(arg0, func_80111144_filesel);
    D_80114598_filesel[arg0].total = 45;
    D_80114598_filesel[arg0].time = 0;
    D_80114598_filesel[arg0].angle = 0;
    func_8010642C_filesel(arg0);
}

void func_8011139C_filesel(s32 arg0) {
    omDelObj(D_80114598_filesel[arg0].obj);
    D_80114598_filesel[arg0].obj = NULL;
}

void func_801113E8_filesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    u32 no;
    s32 time;
    f32 r;
    f32 t;
    f32 h;
    f32 scale;

    no = obj->work[0];
    time = D_80114598_filesel[no].time;
    r = (f32)time / (f32)D_80114598_filesel[no].total;
    t = (r > 1.0f) ? 1.0f : r;
    h = (t - 0.2f) * -1.6666666f * (t - 0.2f) + 1.0666666f - (-t + 1.0f);
    HuVecCopy3F(&start, &D_80114598_filesel[no].start);
    HuVecCopy3F(&end, &D_80114598_filesel[no].end);
    HuVecCopyXYZ(&pos, (end.x - start.x) * t + start.x, (end.y - start.y) * t + h * 400.0f + start.y,
                 (end.z - start.z) * t + start.z);
    func_801064DC_filesel(no, pos.x, pos.y, pos.z);
    func_801064DC_filesel(no + 3, pos.x, pos.y, pos.z);
    scale = (t * 0.7f + 0.3f) * 0.8f;
    func_80106550_filesel(no, scale, scale, scale);
    func_80106550_filesel(no + 3, scale, scale, scale);
    time++;
    D_80114598_filesel[no].time = time;
    if (r > 1.0f) {
        func_8011139C_filesel(no);
    }
}

void func_80111660_filesel(s32 arg0, s32 arg1, s32 arg2) {
    Vec tbl[3] = { { -400.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 400.0f, 0.0f, 0.0f } };

    func_80110E70_filesel(arg1, func_801113E8_filesel);
    func_8010642C_filesel(arg1);
    HuVecCopy3F(&D_80114598_filesel[arg1].start, &tbl[arg0]);
    D_80114598_filesel[arg1].start.y += 100.0f;
    HuVecCopy3F(&D_80114598_filesel[arg1].end, &tbl[arg1]);
    D_80114598_filesel[arg1].time = 0;
    D_80114598_filesel[arg1].total = arg2;
}

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

