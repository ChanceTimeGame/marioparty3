#include "common.h"
#include "siman.h"

#define SAVE_FILE_HEADER_SIZE 0x20
#define SAVE_FILE_SIZE 0x2A0

typedef struct EepData {
    /* 0x00 */ u16 eepFileOffset;
    /* 0x04 */ u8 *eepromBuffer;
    /* 0x08 */ u16 size;
} EepData; // sizeof 0x0C

typedef struct UnkEepStruct {
    char unk_00[0x10];
} UnkEepStruct;

typedef struct unkfunc_8001AFD8 {
    s16 unk0;
    struct unkfunc_8001AFD8 *unk4; // is this correct?
    s16 unk8;
} unkfunc_8001AFD8;

typedef struct unkfunc_8007EE0C {
    void *_InitEepromFunc;  // func pointer
    unkfunc_8001AFD8 *unk4; // is this correct?
    s32 unk8;
    OSMesgQueue *mesgQueue;
} unkfunc_8007EE0C;

extern u8 D_80097710_main[];
extern u8 D_800D0450_main[];
extern u8 D_800AC7F0_main;
extern u8 D_800AC7F1_main;
extern u8 D_800D0E50_main[];

void ClearCommonBuf(void);
s32 _WriteEeprom(EepData *arg0);
s32 func_8000C9C8_main(s8);
s32 WriteEeprom(OSMesgQueue *arg0, u8 arg1, u8 *arg2, s32 arg3);
s32 ReadEepromBox(s8 boxNo, u16 offset, u8 *dst, u16 size);
s32 _ReadEeprom(EepData *arg0);
extern u8 D_800A1E81_main;

s32 _InitEeprom(u8 **arg0) {
    s16 eepromProbeResult;
    s32 var_s1;
    s16 i;

    D_800AC7F0_main = 0;
    D_800AC7F1_main = 0xFF;
    var_s1 = 0;
    eepromProbeResult = osEepromProbe(&D_800CE1A0_main);
    if ((eepromProbeResult) == 0) {
        for (i = 0; i < 4; i++) {
            eepromProbeResult = osEepromProbe(&D_800CE1A0_main);
            if (eepromProbeResult != 0) {
                break;
            }
        }

        ASSERT(i != 4);
    }

    ASSERT(eepromProbeResult == EEPROM_TYPE_16K);

    if (osEepromLongRead(&D_800CE1A0_main, 0, D_800D0E50_main, EEPROM_BLOCK_SIZE) != 0) {
        return EEPROM_TYPE_16K;
    }

    i = 0;
    if (D_80097710_main[i] != 0) {
        while (1) {
            if (D_800D0E50_main[i] != D_80097710_main[i]) {
                var_s1 = 1;
                // Write "HUDSON\0\0" header
                for (i = 0; i < EEPROM_BLOCK_SIZE; i++) {
                    D_800D0E50_main[i] = D_80097710_main[i];
                }

                // Write it again just to be sure
                for (i = 0; i < EEPROM_BLOCK_SIZE; i++) {
                    D_800D0E50_main[i] = D_80097710_main[i];
                }

                ClearCommonBuf();
                WriteEeprom(&D_800CE1A0_main, 1, D_800D0450_main, 0x18);

                for (i = 0; i < 3; i++) {
                    if (func_8000C9C8_main(i)) {
                        return EEPROM_TYPE_16K;
                    }
                }

                for (i = 0; i < 8; i++) {
                    D_800D0E50_main[i] = D_80097710_main[i];
                }

                if (WriteEeprom(&D_800CE1A0_main, 0, D_800D0E50_main, 8) == 0) {
                    **arg0 = var_s1;
                    return 0;
                }
                return EEPROM_TYPE_16K;
            }
            i++;
            if (D_80097710_main[i] == 0) {
                break;
            }
        }
    }
    **arg0 = var_s1;
    return 0;
}

s32 InitEeprom(u8 *isNew) {
    unkMesg sp10;
    u8 *sp20 = isNew;

    return RequestSIFunction(&sp10, (void *)&_InitEeprom, &sp20, 1);
}

s32 _WriteEeprom(EepData *arg0) {
    u16 alignedOffset = (arg0->eepFileOffset >> 3);
    u16 alignedSize = (arg0->size + (arg0->eepFileOffset & 7) + 7) & ~7;
    u8 *alignedEepBuffer = (u8 *)((u32)arg0->eepromBuffer & ~7);

    return (WriteEeprom(&D_800CE1A0_main, alignedOffset, alignedEepBuffer, alignedSize) != 0) * 2;
}

s32 WriteEepromBox2(s8 boxNo, u16 offset, u8 *src, u16 size) {
    unkMesg sp10;
    EepData sp20;
    s32 ret;
    s16 i;

    D_800AC7F0_main = 0;
    if (offset < 8) {
        return 2;
    }
    for (i = 0; i < size; i++) {
        if (offset + i >= 0x800) {
            break;
        }
        D_800D0E50_main[offset + i] = src[i];
    }
    sp20.eepFileOffset = offset + (boxNo * SAVE_FILE_SIZE) + SAVE_FILE_HEADER_SIZE;
    sp20.eepromBuffer = &D_800D0E50_main[offset];
    sp20.size = size;
    ret = RequestSIFunction(&sp10, &_WriteEeprom, &sp20, 1);
    if (ret == 0) {
        D_800AC7F1_main = boxNo;
    }
    return ret;
}

s32 WriteEepromBox(s8 saveFileIndex) {
    unkMesg sp10;
    EepData sp20;
    s32 ret;

    D_800AC7F0_main = 0;
    sp20.eepFileOffset = (saveFileIndex * SAVE_FILE_SIZE) + SAVE_FILE_HEADER_SIZE;
    sp20.eepromBuffer = D_800D0E50_main;
    sp20.size = SAVE_FILE_SIZE;
    ret = RequestSIFunction(&sp10, &_WriteEeprom, &sp20, 1);
    if (ret == 0) {
        D_800AC7F1_main = saveFileIndex;
    }
    return ret;
}

void func_8000C6C0_main(s8 boxNo, u16 offset, u8 *src, u16 size) {
    s16 i;

    if (boxNo != D_800AC7F1_main) {
        ReadEepromBox(D_800A1E81_main | 0x80, 0, NULL, SAVE_FILE_SIZE);
        D_800AC7F1_main = boxNo;
    }
    for (i = 0; i < size; i++) {
        if (offset + i >= 0x800) {
            break;
        }
        D_800D0E50_main[offset + i] = src[i];
    }
}

s32 _ReadEeprom(EepData *arg0) {
    u16 alignedOffset = (arg0->eepFileOffset >> 3);
    u16 alignedSize = (arg0->size + (arg0->eepFileOffset & 7) + 7) & ~7;

    return (osEepromLongRead(&D_800CE1A0_main, alignedOffset, arg0->eepromBuffer, alignedSize) != 0) * 2;
}

s32 ReadEepromBox(s8 boxNo, u16 offset, u8 *dst, u16 size) {
    unkMesg sp10;
    EepData sp20;
    s32 ret;

    if (boxNo != D_800AC7F1_main || D_800AC7F0_main == 0) {
        sp20.eepFileOffset = ((boxNo & 0x7F) * SAVE_FILE_SIZE) + SAVE_FILE_HEADER_SIZE;
        sp20.eepromBuffer = D_800D0E50_main;
        sp20.size = SAVE_FILE_SIZE;
        ret = RequestSIFunction(&sp10, &_ReadEeprom, &sp20, 1);
        if (ret != 0) {
            return ret;
        }
        D_800AC7F0_main = 1;
        D_800AC7F1_main = boxNo;
    }
    if (boxNo & 0x80) {
        return 0;
    }
    bcopy(&D_800D0E50_main[offset], dst, size);
    return 0;
}

s32 WriteEepromCommonBuf(u8 *src) {
    unkMesg sp10;
    EepData sp20;
    s32 ret;

    bcopy(src, D_800D0450_main, 0x18);
    sp20.eepFileOffset = 8;
    sp20.eepromBuffer = D_800D0450_main;
    sp20.size = 0x18;
    ret = RequestSIFunction(&sp10, &_WriteEeprom, &sp20, 1);
    if (ret != 0) {
        return ret;
    }
    return 0;
}

s32 ReadEepromCommonBuf(u8 *dst) {
    unkMesg sp10;
    EepData sp20;
    s32 ret;

    sp20.eepFileOffset = 8;
    sp20.eepromBuffer = D_800D0450_main;
    sp20.size = 0x18;
    ret = RequestSIFunction(&sp10, &_ReadEeprom, &sp20, 1);
    if (ret != 0) {
        return ret;
    }
    bcopy(D_800D0450_main, dst, 0x18);
    return 0;
}

s32 func_8000C9C8_main(s8 boxNo) {
    u8 buf[8];

    memset(buf, 0, sizeof(buf));
    return (WriteEeprom(&D_800CE1A0_main, ((boxNo * SAVE_FILE_SIZE) + SAVE_FILE_HEADER_SIZE) >> 3, buf, 8) != 0) * 2;
}

void ClearBoxBuf(s8 boxNo) {
    memset(D_800D0E50_main, 0, SAVE_FILE_SIZE);
}

void ClearCommonBuf(void) {
    memset(D_800D0450_main, 0, 0x18);
}

s32 _DestroyEeprom(void) {
    return (osEepromWrite(&D_800CE1A0_main, 0, &D_80097710_main[1]) != 0) * 2;
}

s32 DestroyEeprom(void) {
    unkMesg sp10;

    return RequestSIFunction(&sp10, &_DestroyEeprom, NULL, 1);
}

u16 CalcChecksumEeprom(u8 *data, u16 startIndex, u16 size) {
    u16 checksum = 0;

    while (size--) {
        checksum += data[startIndex];
        startIndex += 1;
    }

    return ~checksum;
}

s32 WriteEeprom(OSMesgQueue *arg0, u8 arg1, u8 *arg2, s32 arg3) {
    UnkEepStruct sp10;

    osEepromLongRead(arg0, (arg1 ^ 1), (u8 *)&sp10, 8);
    return osEepromLongWrite(arg0, arg1, arg2, arg3);
}
