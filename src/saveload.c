#include "common.h"
#include "gameman.h"

/* Save boxes: each EEPROM box (0x2A0 bytes, eeprom.c's box buffer D_800D0E50_main) holds the
   bit-packed records of saveEncode.c. Layout, by the encoded sizes func_8004F290_main computes:
   GW_COMMON | GW_SYSTEM + 4 GW_PLAYER (board) | GW_SYSTEM (second scheme) + 2 GW_PLAYER |
   GW_SYSTEM (second scheme) + GW_STORY + 4 GW_PLAYER (story), then a u16 checksum at
   D_800CE2C0_main (the total). */

/* eeprom.c's common record (0x18 bytes at EEPROM offset 8) */
typedef struct SaveCommonBuf {
    /* 0x00 */ u8 flags;
    /* 0x01 */ u8 unk01; /* box number, 0xFF none */
    /* 0x02 */ char unk02[0x14];
    /* 0x16 */ u16 checksum;
} SaveCommonBuf; /* size = 0x18 */

extern SaveCommonBuf D_800D09A8_main;
extern u8 D_800D0450_main[]; /* eeprom.c: the common record as read */
extern u8 D_800D0E50_main[]; /* eeprom.c: the box buffer */
extern u8 gEncodedSaveBuffer[];
extern u8 D_800BBAB0_main; /* EEPROM present */
extern u8 D_800D20EC_main; /* load result: bit per bad box, 8 common record reset, 0xFF no EEPROM */
extern s8 D_800A1E80_main;
extern s8 D_800A1E81_main; /* current box */
extern s16 D_800A1E82_main;
/* saveEncode.c: encoded record sizes */
extern u16 D_800D04B0_main; /* GW_COMMON */
extern u16 D_800CBB64_main; /* GW_SYSTEM */
extern u16 D_800C9944_main; /* GW_SYSTEM, second scheme */
extern u16 D_800CCF54_main; /* GW_PLAYER */
extern u16 D_800CD6A4_main; /* GW_STORY */
extern u16 D_800CE2C0_main; /* all records */

s32 InitEeprom(u8* isNew);
s32 WriteEepromBox(s8 boxNo);
s32 ReadEepromBox(s8 boxNo, u16 offset, u8* dst, u16 size);
void func_8000C6C0_main(s8 boxNo, u16 offset, u8* src, u16 size);
s32 WriteEepromCommonBuf(u8* src);
s32 ReadEepromCommonBuf(u8* dst);
s32 func_8000C9C8_main(s8 boxNo);
void ClearBoxBuf(s8 boxNo);
u16 CalcChecksumEeprom(u8* data, u16 startIndex, u16 size);
s32 func_8004F504_main(u8* src);
s32 func_8004F524_main(u8* src);
s32 SavePlayerStruct(u8* src);
s32 func_8004F564_main(u8* src);
s32 func_8004F584_main(u8* src);
void func_8004F8BC_main(u8* src, u8* dst);
void func_8004F90C_main(u8* src, u8* dst);
void func_8004F95C_main(u8* src, u8* dst);
void func_8004F9AC_main(u8* src, u8* dst);
void func_8004F9FC_main(u8* src, u8* dst);

void func_8004FCF0_main(void);
s32 func_80050064_main(s32 write);
void func_80050CFC_main(void);
void func_80050D38_main(void);
s32 func_80050D84_main(void);
s32 func_80050CDC_main(void);
void func_80050E84_main(void);

void func_8004FCF0_main(void) {
    GWInit();
    func_8000E978_main();
    GwCommon.languageIndex = 2;
    GwCommon.unkA1 = GwCommon.unkA0 = GwCommon.unk9E = GwCommon.unkA2 = GwCommon.unk9F = 3;
    D_800D09A8_main.flags &= ~1;
    D_800D09A8_main.unk01 = 0;
    if (D_800BBAB0_main != 0) {
        ClearBoxBuf(D_800A1E81_main);
        _SetFlag(0x2E);
        _SetFlag(0x2F);
        func_80050064_main(0);
        memset(&D_800D0E50_main[D_800D04B0_main], 0, 0x2A0 - D_800D04B0_main);
        func_80050D38_main();
        WriteEepromBox(D_800A1E81_main);
    }
}

// Matches (masked 0; split-label relocs only) with ~/repos/mp3-wt/2d-A.header.patch: it uses
// func_80050800_main's result, which include/functions.us.h declares void.
s32 func_8004FDC0_main(void) {
    u8 isNew;
    s32 i;
    s32 bad;

    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i) == 1) {
            break;
        }
    }
    if (i == 4) {
        D_800A1E80_main = 1;
    }
    if (D_800A1E82_main == 0) {
        D_800A1E82_main = 1;
        if (InitEeprom(&isNew) != 0) {
            D_800BBAB0_main = 0;
        } else {
            D_800BBAB0_main = 1;
        }
    }
    if (D_800BBAB0_main != 0) {
        if (isNew == 1) {
            D_800D20EC_main = 0x1F;
        } else {
            D_800D20EC_main = 0;
        }
        bad = func_80050CDC_main();
        if (D_800D09A8_main.checksum != CalcChecksumEeprom(D_800D0450_main, 0, 0x16)) {
            bad = 1;
        }
        if (bad != 0) {
            memset(&D_800D09A8_main, 0, sizeof(SaveCommonBuf));
            D_800D09A8_main.unk01 = 0xFF;
            D_800D09A8_main.flags &= ~1;
            func_80050CFC_main();
            D_800D20EC_main |= 8;
        }
        for (i = 0; i < 3; i++) {
            SLCurBoxNoSet(i);
            bad = func_80050800_main();
            if (bad == 0 && func_80050D84_main() == 0) {
                bad = 1;
            }
            if (GwCommon.unk_00 == 0) {
                if (D_800D09A8_main.unk01 == i) {
                    D_800D09A8_main.unk01 = 0xFF;
                    func_80050CFC_main();
                }
            }
            if (GwCommon.unk_00 != 0) {
                if ((GwCommon.unk_00 != 0x91) | (bad != 0)) {
                    func_8000C9C8_main(i);
                    D_800D20EC_main |= 1 << i;
                }
            }
        }
        if (D_800D09A8_main.flags & 1) {
            func_80000F30_main(1);
        } else {
            func_80000F30_main(0);
        }
    } else {
        func_8004FCF0_main();
        func_80000F30_main(0);
        D_800D20EC_main = 0xFF;
    }
    GwSystem.minigame_index = 0;
    return D_800D20EC_main;
}

void func_80050044_main(void) {
}

void func_8005004C_main(void) {
}

void func_80050054_main(void) {
}

void func_8005005C_main(void) {
}

s32 func_80050064_main(s32 write) {
    if (D_800BBAB0_main != 0) {
        func_8000C6C0_main(D_800A1E81_main, 0, gEncodedSaveBuffer, func_8004F564_main((u8*) &GwCommon));
        if (write == 0) {
            return 0;
        }
        func_80050D38_main();
        return WriteEepromBox(D_800A1E81_main);
    }
    return 0;
}

// Matches (raw 0) with ~/repos/mp3-wt/2d-A.header.patch: include/functions.us.h declares
// it void, but it returns a value its callers use.
s32 func_800500E0_main(s32 write) {
    s16 ofs;
    s16 i;

    if (D_800BBAB0_main != 0) {
        func_80050064_main(0);
        func_8000C6C0_main(D_800A1E81_main, D_800D04B0_main, gEncodedSaveBuffer, func_8004F504_main((u8*) &GwSystem));
        ofs = D_800D04B0_main + D_800CBB64_main;
        for (i = 0; i < 4; i++) {
            func_8000C6C0_main(D_800A1E81_main, ofs, gEncodedSaveBuffer, SavePlayerStruct((u8*) &GwPlayer[i]));
            ofs += D_800CCF54_main;
        }
        if (write == 0) {
            return 0;
        }
        func_80050D38_main();
        return WriteEepromBox(D_800A1E81_main);
    }
    return 0;
}

s32 func_80050200_main(s32 write) {
    s16 ofs;
    s16 i;

    if (D_800BBAB0_main != 0) {
        func_80050064_main(0);
        func_8000C6C0_main(D_800A1E81_main, D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4),
                           gEncodedSaveBuffer, func_8004F524_main((u8*) &GwSystem));
        ofs = D_800C9944_main + (D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4));
        for (i = 0; i < 2; i++) {
            func_8000C6C0_main(D_800A1E81_main, ofs, gEncodedSaveBuffer, SavePlayerStruct((u8*) &GwPlayer[i]));
            ofs += D_800CCF54_main;
        }
        if (write == 0) {
            return 0;
        }
        func_80050D38_main();
        return WriteEepromBox(D_800A1E81_main);
    }
    return 0;
}

// Matches (raw 0) with ~/repos/mp3-wt/2d-A.header.patch: include/functions.us.h declares
// it void, but it returns a value its callers use.
s32 func_8005035C_main(s32 write) {
    s16 ofs;
    s16 i;

    if (D_800BBAB0_main != 0) {
        GwStory.unk_64[0] = GwStory.unk0;
        GwStory.unk_64[1] = GwStory.unk1;
        GwStory.unk_64[2] = GwStory.unk2;
        GwStory.unk_64[15] = GwStory.unkF;
        for (i = 0; i < 12; i++) {
            GwStory.unk_64[i + 3] = GwStory.unk3[i];
        }
        func_8000C6C0_main(D_800A1E81_main, D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2) + D_800C9944_main, gEncodedSaveBuffer, func_8004F584_main((u8*) &GwStory));
        func_80050064_main(0);
        func_8000C6C0_main(D_800A1E81_main, D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2), gEncodedSaveBuffer, func_8004F524_main((u8*) &GwSystem));
        func_8000C6C0_main(D_800A1E81_main, D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2) + D_800C9944_main, gEncodedSaveBuffer, func_8004F584_main((u8*) &GwStory));
        ofs = D_800CD6A4_main + (D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2) + D_800C9944_main);
        for (i = 0; i < 4; i++) {
            func_8000C6C0_main(D_800A1E81_main, ofs, gEncodedSaveBuffer, SavePlayerStruct((u8*) &GwPlayer[i]));
            ofs += D_800CCF54_main;
        }
        if (write == 0) {
            return 0;
        }
        func_80050D38_main();
        return WriteEepromBox(D_800A1E81_main);
    }
    return 0;
}

s32 func_80050614_main(s32 write) {
    s16 ofs;
    s16 i;

    if (D_800BBAB0_main != 0) {
        func_80050064_main(0);
        func_8000C6C0_main(D_800A1E81_main, D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2), gEncodedSaveBuffer, func_8004F524_main((u8*) &GwSystem));
        func_8000C6C0_main(D_800A1E81_main, D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2) + D_800C9944_main, gEncodedSaveBuffer, func_8004F584_main((u8*) &GwStory));
        ofs = D_800CD6A4_main + (D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2) + D_800C9944_main);
        for (i = 0; i < 4; i++) {
            func_8000C6C0_main(D_800A1E81_main, ofs, gEncodedSaveBuffer, SavePlayerStruct((u8*) &GwPlayer[i]));
            ofs += D_800CCF54_main;
        }
        if (write == 0) {
            return 0;
        }
        func_80050D38_main();
        return WriteEepromBox(D_800A1E81_main);
    }
    return 0;
}

// Matches (raw 0) with ~/repos/mp3-wt/2d-A.header.patch: include/functions.us.h declares
// it void, but it returns a value its callers use.
s32 func_80050800_main(void) {
    if (D_800BBAB0_main == 0) {
        return 0;
    }
    if (ReadEepromBox((u8) D_800A1E81_main | 0x80, 0, NULL, 0x2A0) != 0) {
        return 1;
    }
    func_8004F9AC_main(D_800D0E50_main, (u8*) &GwCommon);
    return 0;
}

s32 func_8005086C_main(void) {
    s16 ofs;
    s16 i;

    if (D_800BBAB0_main != 0) {
        if (ReadEepromBox((u8) D_800A1E81_main | 0x80, 0, NULL, 0x2A0) != 0) {
            return 1;
        }
        func_8004F8BC_main(&D_800D0E50_main[D_800D04B0_main], (u8*) &GwSystem);
        ofs = D_800D04B0_main + D_800CBB64_main;
        for (i = 0; i < 4; i++) {
            func_8004F95C_main(&D_800D0E50_main[ofs], (u8*) &GwPlayer[i]);
            ofs += D_800CCF54_main;
        }
    }
    return 0;
}

// Matches (raw 0) with ~/repos/mp3-wt/2d-A.header.patch: include/functions.us.h declares
// it void, but it returns a value its callers use.
s32 func_80050974_main(void) {
    s16 ofs;
    s16 i;

    if (D_800BBAB0_main != 0) {
        if (ReadEepromBox((u8) D_800A1E81_main | 0x80, 0, NULL, 0x2A0) != 0) {
            return 1;
        }
        func_8004F90C_main(&D_800D0E50_main[D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4)], (u8*) &GwSystem);
        ofs = D_800C9944_main + (D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4));
        for (i = 0; i < 4; i++) {
            func_8004F95C_main(&D_800D0E50_main[ofs], (u8*) &GwPlayer[i]);
            ofs += D_800CCF54_main;
        }
        func_80050E84_main();
    }
    return 0;
}

// Matches (raw 0) with ~/repos/mp3-wt/2d-A.header.patch: include/functions.us.h declares
// it void, but it returns a value its callers use.
s32 func_80050ABC_main(void) {
    s16 ofs;
    s16 i;

    if (D_800BBAB0_main != 0) {
        if (ReadEepromBox((u8) D_800A1E81_main | 0x80, 0, NULL, 0x2A0) != 0) {
            return 1;
        }
        func_8004F90C_main(&D_800D0E50_main[D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2)], (u8*) &GwSystem);
        func_8004F9FC_main(&D_800D0E50_main[D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2) + D_800C9944_main], (u8*) &GwStory);
        GwStory.unk0 = GwStory.unk_64[0];
        GwStory.unk1 = GwStory.unk_64[1];
        GwStory.unk2 = GwStory.unk_64[2];
        GwStory.unkF = GwStory.unk_64[15];
        for (i = 0; i < 12; i++) {
            GwStory.unk3[i] = GwStory.unk_64[i + 3];
        }
        ofs = D_800CD6A4_main + (D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) + (D_800C9944_main + D_800CCF54_main * 2) + D_800C9944_main);
        for (i = 0; i < 4; i++) {
            func_8004F95C_main(&D_800D0E50_main[ofs], (u8*) &GwPlayer[i]);
            ofs += D_800CCF54_main;
        }
    }
    return 0;
}

s32 func_80050CDC_main(void) {
    return ReadEepromCommonBuf((u8*) &D_800D09A8_main);
}

void func_80050CFC_main(void) {
    D_800D09A8_main.checksum = CalcChecksumEeprom((u8*) &D_800D09A8_main, 0, 0x16);
    WriteEepromCommonBuf((u8*) &D_800D09A8_main);
}

void func_80050D38_main(void) {
    u16 checksum = CalcChecksumEeprom(D_800D0E50_main, 0, D_800CE2C0_main);

    func_8000C6C0_main(D_800A1E81_main, D_800CE2C0_main, (u8*) &checksum, sizeof(checksum));
}

s32 func_80050D84_main(void) {
    u16 checksum;

    ReadEepromBox(D_800A1E81_main, D_800CE2C0_main, (u8*) &checksum, sizeof(checksum));
    return checksum == CalcChecksumEeprom(D_800D0E50_main, 0, D_800CE2C0_main);
}

// register allocation (masked 0): s0/s1 swapped between curBox and dstBox
/* Copy box srcBox to dstBox; 1 on failure. Retail returns nothing on success (no return
   statement: the caller sees whatever v0 holds). */
#ifdef NON_MATCHING
s32 func_80050DDC_main(s16 srcBox, s16 dstBox) {
    s32 curBox = (u8) D_800A1E81_main;

    SLCurBoxNoSet(srcBox);
    if (ReadEepromBox((u8) D_800A1E81_main | 0x80, 0, NULL, 0x2A0) != 0 ||
        (SLCurBoxNoSet(dstBox), WriteEepromBox(D_800A1E81_main) != 0)) {
        SLCurBoxNoSet(curBox);
        return 1;
    }
    SLCurBoxNoSet(curBox);
}
#else
INCLUDE_ASM("asm/nonmatchings/saveload", func_80050DDC_main);
#endif

void SLCurBoxNoSet(u32 boxNo) {
    D_800A1E81_main = boxNo;
}

void func_80050E84_main(void) {
    s8 used[4];
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        used[i] = 0;
    }
    used[GwPlayer[0].pad] = -1;
    used[GwPlayer[1].pad] = -1;
    for (i = 0, j = 2; i < 4; i++) {
        if (used[i] == 0) {
            GwPlayer[j].pad = i;
            j++;
        }
    }
}
