#include "common.h"

void func_8004F83C_main(s32);

extern u8 gEncodedSaveBuffer[220];
extern s32 D_800BBAA0_main;
extern s32 D_800BBAA4_main;
// extern char D_800A7B40_main[];
extern u8 D_800A1D70_main[]; /* GW_COMMON encoding scheme (0xA4 bytes decoded) */
extern u8 D_800A1D9C_main[]; /* 0x62-byte record encoding scheme */
extern u8 D_800A1DC8_main[]; /* 0x62-byte record encoding scheme */
extern u8 D_800A1DF8_main[]; /* GW_PLAYER encoding scheme (0x38 bytes decoded) */
extern u8 D_800A1E58_main[]; /* GW_STORY encoding scheme (0x74 bytes decoded) */
extern u16 D_800D04B0_main;
extern u16 D_800CBB64_main;
extern u16 D_800C9944_main;
extern u16 D_800CCF54_main;
extern u16 D_800CD6A4_main;
extern u16 D_800CE2C0_main;

s32 SaveFileEncode(u8 *sourceData, u8 *encodingScheme);
void func_8004FA4C_main(u8 *src, u8 *dst, u8 *decodingScheme);
s32 func_8004FC84_main(void);

void func_8004F290_main(void) {
    s16 bits;
    u8 *p;
    s32 size;

    bits = 0;
    for (p = D_800A1D70_main; *p != 0; p += 3) {
        bits += p[0] * p[1];
    }
    size = bits / 8;
    if (bits & 7) {
        D_800D04B0_main = size + 1;
    } else {
        D_800D04B0_main = size;
    }
    bits = 0;
    for (p = D_800A1D9C_main; *p != 0; p += 3) {
        bits += p[0] * p[1];
    }
    size = bits / 8;
    if (bits & 7) {
        D_800CBB64_main = size + 1;
    } else {
        D_800CBB64_main = size;
    }
    bits = 0;
    for (p = D_800A1DC8_main; *p != 0; p += 3) {
        bits += p[0] * p[1];
    }
    size = bits / 8;
    if (bits & 7) {
        D_800C9944_main = size + 1;
    } else {
        D_800C9944_main = size;
    }
    bits = 0;
    for (p = D_800A1DF8_main; *p != 0; p += 3) {
        bits += p[0] * p[1];
    }
    size = bits / 8;
    if (bits & 7) {
        D_800CCF54_main = size + 1;
    } else {
        D_800CCF54_main = size;
    }
    bits = 0;
    for (p = D_800A1E58_main; *p != 0; p += 3) {
        bits += p[0] * p[1];
    }
    size = bits / 8;
    if (bits & 7) {
        D_800CD6A4_main = size + 1;
    } else {
        D_800CD6A4_main = size;
    }
    D_800CE2C0_main = D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) +
                      (D_800C9944_main + D_800CCF54_main * 2) +
                      (D_800CD6A4_main + D_800C9944_main + D_800CCF54_main * 4);
}

s32 func_8004F504_main(u8 *src) {
    return SaveFileEncode(src, D_800A1D9C_main);
}

s32 func_8004F524_main(u8 *src) {
    return SaveFileEncode(src, D_800A1DC8_main);
}

s32 SavePlayerStruct(u8 *src) {
    return SaveFileEncode(src, D_800A1DF8_main);
}

s32 func_8004F564_main(u8 *src) {
    return SaveFileEncode(src, D_800A1D70_main);
}

s32 func_8004F584_main(u8 *src) {
    return SaveFileEncode(src, D_800A1E58_main);
}

s32 SaveFileEncode(u8 *sourceData, u8 *encodingScheme) {
    s32 phi_s0;
    s16 phi_v1_2;
    u8 *currentDataPtr;
    s16 fieldIndex, byteIndex, bitIndex, schemeIndex;

    for (schemeIndex = 0; schemeIndex < ARRAY_COUNT(gEncodedSaveBuffer); schemeIndex++) {
        gEncodedSaveBuffer[schemeIndex] = 0;
    }

    D_800BBAA4_main = 0;
    D_800BBAA0_main = 0;

    while (*encodingScheme != 0) {
        currentDataPtr = (sourceData + encodingScheme[2]);
        for (fieldIndex = 0; fieldIndex < encodingScheme[1]; fieldIndex++) {
            if (encodingScheme[0] > 16) {
                for (byteIndex = 0; byteIndex < (encodingScheme[0] >> 3); byteIndex++, currentDataPtr++) {
                    phi_s0 = *currentDataPtr;
                    for (bitIndex = 0; bitIndex < 8; bitIndex++, phi_s0 *= 2) {
                        func_8004F83C_main(phi_s0 & 0x80);
                    }
                }
                continue;
            } else {
                if (encodingScheme[0] > 8) {
                    phi_s0 = *currentDataPtr << (16 - encodingScheme[0]);
                    phi_v1_2 = encodingScheme[0] - 8;
                    for (bitIndex = 0; bitIndex < phi_v1_2; bitIndex++, phi_s0 *= 2) {
                        func_8004F83C_main(phi_s0 & 0x80);
                    }
                    currentDataPtr++;
                    phi_s0 = *currentDataPtr;
                    phi_v1_2 = 8;
                } else {
                    phi_s0 = *currentDataPtr << (8 - encodingScheme[0]);
                    phi_v1_2 = encodingScheme[0];
                }
                for (bitIndex = 0; bitIndex < phi_v1_2; bitIndex++, phi_s0 *= 2) {
                    func_8004F83C_main(phi_s0 & 0x80);
                }
            }
            currentDataPtr++;
        }
        encodingScheme += 3; // advance to next encoding tuplet
    }

    gEncodedSaveBuffer[D_800BBAA0_main] <<= 8 - D_800BBAA4_main;
    if (D_800BBAA4_main == 0) {
        D_800BBAA0_main--;
    }
    if (D_800BBAA0_main > ARRAY_COUNT(gEncodedSaveBuffer)) {
        osSyncPrintf("SaveCompBuffer Max Over!\n");
    }
    return D_800BBAA0_main + 1;
}

void func_8004F83C_main(s32 arg0) {
    gEncodedSaveBuffer[D_800BBAA0_main] *= 2;
    gEncodedSaveBuffer[D_800BBAA0_main] |= arg0 ? 1 : 0;

    if (++D_800BBAA4_main >= 8) {
        D_800BBAA0_main++;
        D_800BBAA4_main = 0;
    }
}

void func_8004F8BC_main(u8 *src, u8 *dst) {
    memset(dst, 0, 0x62);
    func_8004FA4C_main(src, dst, D_800A1D9C_main);
}

void func_8004F90C_main(u8 *src, u8 *dst) {
    memset(dst, 0, 0x62);
    func_8004FA4C_main(src, dst, D_800A1DC8_main);
}

void func_8004F95C_main(u8 *src, u8 *dst) {
    memset(dst, 0, 0x38);
    func_8004FA4C_main(src, dst, D_800A1DF8_main);
}

void func_8004F9AC_main(u8 *src, u8 *dst) {
    memset(dst, 0, 0xA4);
    func_8004FA4C_main(src, dst, D_800A1D70_main);
}

void func_8004F9FC_main(u8 *src, u8 *dst) {
    memset(dst, 0, 0x74);
    func_8004FA4C_main(src, dst, D_800A1E58_main);
}

void func_8004FA4C_main(u8 *src, u8 *dst, u8 *decodingScheme) {
    u8 *currentDataPtr;
    s16 fieldIndex, byteIndex, bitIndex, i;
    s16 count;
    u8 value;

    for (i = 0; i < ARRAY_COUNT(gEncodedSaveBuffer); i++) {
        gEncodedSaveBuffer[i] = *src;
        src++;
    }

    D_800BBAA4_main = 0;
    D_800BBAA0_main = 0;

    while (*decodingScheme != 0) {
        currentDataPtr = dst + decodingScheme[2];
        for (fieldIndex = 0; fieldIndex < decodingScheme[1]; fieldIndex++) {
            if (decodingScheme[0] > 16) {
                for (byteIndex = 0; byteIndex < (decodingScheme[0] >> 3); byteIndex++, currentDataPtr++) {
                    value = 0;
                    for (bitIndex = 0; bitIndex < 8; bitIndex++) {
                        value = (value << 1) | (func_8004FC84_main() ? 1 : 0);
                    }
                    *currentDataPtr = value;
                }
            } else {
                value = 0;
                if (decodingScheme[0] > 8) {
                    count = decodingScheme[0] - 8;
                    for (bitIndex = 0; bitIndex < count; bitIndex++) {
                        value = (value << 1) | (func_8004FC84_main() ? 1 : 0);
                    }
                    *currentDataPtr = value;
                    currentDataPtr++;
                    count = 8;
                } else {
                    count = decodingScheme[0];
                }
                value = 0;
                for (bitIndex = 0; bitIndex < count; bitIndex++) {
                    value = (value << 1) | (func_8004FC84_main() ? 1 : 0);
                }
                *currentDataPtr = value;
                currentDataPtr++;
            }
        }
        decodingScheme += 3;
    }
}

s32 func_8004FC84_main(void) {
    s32 bit = gEncodedSaveBuffer[D_800BBAA0_main] & 0x80;

    gEncodedSaveBuffer[D_800BBAA0_main] <<= 1;
    if (++D_800BBAA4_main >= 8) {
        D_800BBAA0_main++;
        D_800BBAA4_main = 0;
    }
    return bit;
}
