#include "common.h"
#include "ovl_81.h"

// duel n10: ovl_81_name's shared .data block (0x80100E10..0x80101B10), formerly
// asm/data/overlays/ovl_81_name/E8BE0.data.s. It is the .data of the units BFB40 through
// E3CD0, in unit order. Each unit's block began on a 16-byte boundary; KMC GCC cannot align
// an object past 8 bytes, so the zero padding between the blocks is spelled out (pad_*).
// Inner labels that asm still uses are aliases in undefined_syms.txt.

typedef struct ItemRect { // as in C5770.c
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} ItemRect;

struct UnkModelStruct; // CCD20.c

extern const char D_80102458_name_81[]; // CA640.c .rodata
extern const char D_80102468_name_81[];

void func_800FB148_name_81(void);
void func_800FB158_name_81(void);

/* BFB40 */
f32 D_80100E10_name_81 = 1.0f;
f32 D_80100E14_name_81 = 100.0f;

/* C1D60 */
u8 pad_80100E18_name_81[8] = { 0 }; // zero padding to a 16-byte (unit) boundary
u8 D_80100E20_name_81 = 0x00;
s32 D_80100E24_name_81[3] = { 0x130207, 0x130207, 0x130207 }; // dice model per mode
s32 D_80100E30_name_81[3] = { 0x1300FE, 0x1300FF, 0x130100 }; // dice motion per mode

/* C45D0 */
u8 pad_80100E3C_name_81[4] = { 0 }; // zero padding to a 16-byte (unit) boundary
s32 D_80100E40_name_81 = 1;

/* C5770 */
u8 pad_80100E44_name_81[12] = { 0 }; // zero padding to a 16-byte (unit) boundary
u8 D_80100E50_name_81[12] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x00, 0x00 }; // duel minigame pools (minigame ids)
u8 D_80100E5C_name_81[8] = { 0x31, 0x32, 0x33, 0x35, 0x37, 0x38, 0x39, 0x00 };
u8 D_80100E64_name_81[31] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x02,
    0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0B, 0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08, 0x09, 0x0B, 0x00,
};
u8 D_80100E84_name_81[4] = { 0x05, 0x03, 0x00, 0x00 }; // list length per category
u8 D_80100E88_name_81[4] = { 0x05, 0x01, 0x02, 0x01 }; // recent-minigame avoid count
ItemRect D_80100E8C_name_81[5] = { { 60, 328, 200, 20 }, { 60, 348, 200, 20 }, { 60, 368, 200, 20 }, { 60, 388, 200, 20 }, { 60, 408, 200, 20 } };
ItemRect D_80100EB4_name_81[3] = { { 95, 330, 130, 20 }, { 95, 354, 130, 20 }, { 95, 378, 130, 20 } };
u8 D_80100ECC_name_81[4] = { 0x32, 0x22, 0x00, 0x00 };
u8 D_80100ED0_name_81[4] = { 0x32, 0x50, 0x00, 0x00 };
u8 D_80100ED4_name_81[4] = { 0x14, 0x18, 0x00, 0x00 };
u8 D_80100ED8_name_81[4] = { 0x72, 0x74, 0x00, 0x00 };
s8 D_80100EDC_name_81[4][2] = { { 1, 0 }, { 9, 15 }, { 11, 8 }, { 13, 0 } }; // D_80100EDD = [0][1]
s32 D_80100EE4_name_81[2] = { 0x4700, 0x1F20 }; // first board-call file per category
u8 D_80100EEC_name_81[76] = {
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06,
    0x07, 0x07, 0x07, 0x00,
}; // per minigame id - 1 (D_80100EEB = this - 1)
u32 D_80100F38_name_81 = 0;
s32 D_80100F3C_name_81 = 0;
s32 D_80100F40_name_81 = 0;
Object *D_80100F44_name_81 = NULL;
u8 pad_80100F48_name_81[8] = { 0 }; // zero padding to a 16-byte (unit) boundary
f32 D_80100F50_name_81[2][2] = { { 70.0f, 64.0f }, { 250.0f, 160.0f } };

/* C9330 */
s32 D_80100F60_name_81[24] = {
    0x1D00, 0x1D01, 0x1D02, 0x1D03, 0x1D04, 0x1D05, 0x1D06, 0x1D07,
    0x1D08, 0x1D09, 0x1D0A, 0x1D0B, 0x1D0C, 0x1D0D, 0x1D0E, 0x1D0F,
    0x1D10, 0x1D11, 0x1D12, 0x1D13, 0x1D14, 0x1D15, 0x3018, 0x3019,
};

/* CA640 */
char *D_80100FC0_name_81[2] = { (char *)D_80102468_name_81, (char *)D_80102458_name_81 }; // minigame type telop strings
s8 D_80100FC8_name_81[4] = { 14, 14, 0, 0 }; // last sprite of each telop string
s8 D_80100FCC_name_81[8] = { -8, -8, -8, -8, -8, -8, 0, 0 }; // x offset of each telop string
s16 D_80100FD4_name_81[14] = {
    60, 93, 126, 159, 192, 225, 258, 0,
    0, 0, 0, 0, 0, 0,
}; // x of each letter

/* CCD20 */
s32 *D_80100FF0_name_81 = NULL;
u32 *D_80100FF4_name_81 = NULL;
struct UnkModelStruct *D_80100FF8_name_81 = NULL;
u8 D_80100FFC_name_81 = 0xFF;
f32 D_80101000_name_81 = 1.0f;
f32 D_80101004_name_81 = 0.0f;
f32 D_80101008_name_81 = 0.0f;
u32 D_8010100C_name_81 = 0;
Gfx D_80101010_name_81[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};
Process *D_80101058_name_81 = NULL;
s32 D_8010105C_name_81 = 1;

/* D1190 */
void *D_80101060_name_81 = NULL; // board space file
u8 (*D_80101064_name_81)[SPACES_MAX] = NULL; // space ids by type
s32 D_80101068_name_81[19] = {
    0, 0, 0x13022E, 0x13022C, 0, 0x13022F, 0x13022B, 0,
    0x13022D, 0, 0x130230, 0x130231, 0x130232, 0x130233, 0x130234, 0x130235,
    0x130236, 0x130237, 0x130238,
};
s32 D_801010B4_name_81[19] = {
    0, 0, 0x13022E, 0x13022C, 0, 0x130239, 0x13022B, 0,
    0x13022D, 0, 0x130230, 0x130231, 0x130232, 0x130233, 0x130234, 0x130235,
    0x130236, 0x130237, 0x130238,
};
Vtx D_80101100_name_81[4] = { // unreferenced: a quad facing +Z
    { { { 100, 0, -100 }, 0, { 1024, 992 }, { 0x00, 0x00, 0x7F, 0xFF } } },
    { { { -100, 0, -100 }, 0, { 0, 992 }, { 0x00, 0x00, 0x7F, 0xFF } } },
    { { { -100, 0, 100 }, 0, { 0, -32 }, { 0x00, 0x00, 0x7F, 0xFF } } },
    { { { 100, 0, 100 }, 0, { 1024, -32 }, { 0x00, 0x00, 0x7F, 0xFF } } },
};
Gfx D_80101140_name_81[] = {
    gsSPSegment(0, 0),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};

/* D28F0 */
s16 D_801011D0_name_81 = 0;
s16 D_801011D2_name_81 = 0; // skip the player's input wait

/* D3450 */
u8 pad_801011D4_name_81[12] = { 0 }; // zero padding to a 16-byte (unit) boundary
s32 D_801011E0_name_81[4] = { 5, 25, 60, 0 };

/* D5B20 */
Object *D_801011F0_name_81 = NULL;
Process *D_801011F4_name_81 = NULL;
s16 D_801011F8_name_81 = -1;
s32 D_801011FC_name_81 = 1;
s32 D_80101200_name_81[8] = { 0x1C00, 0x1C01, 0x1C02, 0x1C03, 0x1C04, 0x1C05, 0x1C06, 0x1C07 }; // unreferenced
s32 D_80101220_name_81 = 2;
u8 pad_80101224_name_81[12] = { 0 }; // zero padding to a 16-byte (unit) boundary
s32 D_80101230_name_81[6] = { 0x1300AB, 0x1300AC, 0x1300AD, 0x1300AE, 0x1300AF, 0x1300B0 };
s16 D_80101248_name_81 = 0;
s16 D_8010124A_name_81 = 0;
s32 D_8010124C_name_81 = 0;
s32 D_80101250_name_81 = 0;
u8 D_80101254_name_81[4][3] = { { 0xFE, 0xFF, 0xA4 }, { 0xFF, 0xA4, 0xAC }, { 0xCC, 0xFF, 0x83 }, { 0x00, 0x00, 0x00 } }; // D_80101255 = [0][1], D_80101256 = [0][2]
s32 D_80101260_name_81[3] = { 0x1D01, 0x1D0A, 0x1D04 };
s32 D_8010126C_name_81[8] = { 0x5102, 0x5105, 0x5127, 0x512C, 0x5121, 0x5108, 0x510C, 0x5110 };
s32 D_8010128C_name_81[8] = { 0x13008C, 0x13008D, 0x13008F, 0x130092, 0x130095, 0x130099, 0x13009B, 0x13009A };
s32 D_801012AC_name_81[2] = { 0x13008D, 0x13008E };
s32 D_801012B4_name_81[2] = { 0x13008F, 0x130090 };
s32 D_801012BC_name_81[3] = { 0x130091, 0x130092, 0x130093 };
s32 D_801012C8_name_81[3] = { 0x130094, 0x130095, 0x130096 };
s32 D_801012D4_name_81[3] = { 0x130097, 0x130098, 0x130099 };
s32 D_801012E0_name_81 = 0x1300B1;
s32 D_801012E4_name_81 = 0x1300B2;
s32 D_801012E8_name_81 = 0x13009D;
s32 D_801012EC_name_81[2] = { 0x511F, 0x5120 };
s32 D_801012F4_name_81[8] = { 0x1300D8, 0x1300D9, 0x1300DB, 0x1300DC, 0x1300DD, 0x1300DE, 0x1300DF, 0x1300E1 };
s32 D_80101314_name_81[9] = {
    0x13009E, 0x13009F, 0x1300A0, 0x1300A1, 0x1300A2, 0x1300A6, 0x1300A5, 0x1300A4,
    0x1300A3,
};
s8 D_80101338_name_81[8] = { 0, -1, 1, -1, 2, -1, 3, -1 };
s8 D_80101340_name_81[8] = { 4, 8, 4, 7, 4, 6, 4, 5 };
s16 D_80101348_name_81[2] = { 90, 230 };
s16 D_8010134C_name_81[2] = { 62, 122 };
s16 D_80101350_name_81[4][4] = { { 0, 1, 0, 1 }, { -1, 0, -1, 0 }, { 0, 1, 0, 1 }, { -1, 0, -1, 0 } };
u8 D_80101370_name_81[4] = { 0x00, 0x01, 0x02, 0x03 };
u32 D_80101374_name_81[9] = {
    8, 0x20001, 0x2002B, 0x20036, 0x20023, 0x20035, 0x20038, 0x20032,
    0x20003,
}; // count, then the ids
s32 D_80101398_name_81[9] = {
    8, 0x30001, 0x3002B, 0x30020, 0x30023, 0x30035, 0x30038, 0x30032,
    0x30003,
}; // count, then the ids
s32 D_801013BC_name_81[9] = {
    8, 0x70001, 0x7002B, 0x70020, 0x70023, 0x70035, 0x70038, 0x70032,
    0x70003,
}; // count, then the ids
s32 D_801013E0_name_81[9] = {
    8, 0x40001, 0x4002B, 0x40020, 0x40023, 0x40035, 0x40038, 0x40032,
    0x40003,
}; // count, then the ids
s32 D_80101404_name_81[9] = {
    8, 0x50001, 0x5002B, 0x50020, 0x50023, 0x50035, 0x50038, 0x50032,
    0x50003,
}; // count, then the ids
s32 D_80101428_name_81[9] = {
    8, 0x60001, 0x6002B, 0x60020, 0x60023, 0x60035, 0x60038, 0x60032,
    0x60003,
}; // count, then the ids
s32 D_8010144C_name_81[9] = {
    8, 0x80001, 0x3002B, 0x80020, 0x30023, 0x80035, 0x80038, 0x80032,
    0x80003,
}; // count, then the ids
s32 D_80101470_name_81[9] = {
    8, 0x70001, 0x7002B, 0x70020, 0x70023, 0x9000D, 0x90010, 0x9000A,
    0x70003,
}; // count, then the ids
s32 *D_80101494_name_81[8] = {
    (s32 *)D_80101374_name_81,
    D_80101398_name_81,
    D_801013BC_name_81,
    D_801013E0_name_81,
    D_80101404_name_81,
    D_80101428_name_81,
    D_8010144C_name_81,
    D_80101470_name_81,
};
u8 D_801014B4_name_81[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
u8 D_801014BC_name_81[20] = {
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/* DBE50 */
RectF D_801014D0_name_81 = { 16.0f, 12.0f, 304.0f, 228.0f };

/* DC4E0 */
s32 D_801014E0_name_81 = 1;
s32 D_801014E4_name_81 = 1;
s16 D_801014E8_name_81[14][2] = { { 24, 36 }, { 200, 155 }, { -192, 36 }, { 416, 155 }, { 48, 96 }, { 176, 96 }, { 112, 110 }, { 416, 155 }, { -192, 16 }, { 416, 155 }, { 512, 24 }, { 512, 174 }, { 200, 24 }, { 200, 174 } }; // D_801014EA = [0][1]
s16 D_80101520_name_81[2][2] = { { 30, 138 }, { 194, 138 } };
s16 D_80101528_name_81[2][2] = { { 30, 138 }, { 194, 138 } };
s16 D_80101530_name_81[29][2] = { { 0, 0 }, { 0, 0 }, { -30, 0 }, { 20, 0 }, { 30, 0 }, { 40, 0 }, { 0, 13 }, { 0, -31 }, { 0, -31 }, { -32, -25 }, { -32, -37 }, { 20, -31 }, { -20, -25 }, { -20, -37 }, { 30, -31 }, { 40, -31 }, { 40, -31 }, { 0, -31 }, { 0, 31 }, { 0, 31 }, { -32, 37 }, { -32, 25 }, { 20, 31 }, { -20, 37 }, { -20, 25 }, { 30, 31 }, { 40, 31 }, { 40, 31 }, { 0, 31 } };
s16 D_801015A4_name_81[3][2] = { { 20, 31 }, { 30, 31 }, { 40, 31 } }; // D_801015A6 = [0][1]
s16 D_801015B0_name_81[3][2] = { { 30, 31 }, { 40, 31 }, { 40, 31 } }; // D_801015B2 = [0][1]
s16 (*D_801015BC_name_81[2])[2] = { D_80101530_name_81, D_80101530_name_81 };
u8 D_801015C4_name_81[28] = {
    0x00, 0x02, 0x00, 0x00, 0x04, 0x00, 0x06, 0x08, 0x0A, 0x0C, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x00,
};
s32 D_801015E0_name_81[16] = {
    0x1300D8, 0x1300D9, 0x1300DB, 0x1300DC, 0x1300DD, 0x1300DE, 0x1300DF, 0x1300E1,
    0x1300D8, 0x1300DA, 0x1300DB, 0x1300DC, 0x1300DD, 0x1300DE, 0x1300E0, 0x1300E1,
};
s32 D_80101620_name_81[12] = {
    0x1300E2, 0x1300E3, 0x1300E4, 0x1300E5, 0x1300E6, 0x1300E7, 0x1300E8, 0x1300E9,
    0x1300EA, 0x1300EB, 0x1300EC, 0x1300ED,
};
s16 (*D_80101650_name_81[4])[2] = { D_80101528_name_81, D_80101528_name_81, D_80101528_name_81, D_80101520_name_81 };
s8 D_80101660_name_81[5][3] = { { 13, 24, -1 }, { 14, 15, 25 }, { 26, -1, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

/* DFD60 */
s32 D_80101670_name_81[5] = { 4, 0xA0090, 0xA009A, 0xA009B, 0xA009C }; // count, then the ids
s32 D_80101684_name_81[3] = { 2, 0xA0094, 0xA0096 }; // count, then the ids
s32 D_80101690_name_81[5] = { 4, 0xA00A7, 0xA00AB, 0xA00AC, 0xA00AD }; // count, then the ids
s32 D_801016A4_name_81[3] = { 2, 0xA00AE, 0xA00AF }; // count, then the ids
s32 D_801016B0_name_81[5] = { 4, 0xA0002, 0xA0012, 0xA0013, 0xA0014 }; // count, then the ids
s32 D_801016C4_name_81[3] = { 2, 0xA0015, 0xA0016 }; // count, then the ids
s32 D_801016D0_name_81[5] = { 4, 0xA00BD, 0xA00BE, 0xA00BF, 0xA00C0 }; // count, then the ids
s32 D_801016E4_name_81[2] = { 1, 0xA00BC }; // count, then the ids
s32 D_801016EC_name_81[5] = { 4, 0xA00C7, 0xA00C8, 0xA00C9, 0xA00CA }; // count, then the ids
s32 D_80101700_name_81[5] = { 4, 0xA00D0, 0xA00D1, 0xA00D2, 0xA00D3 }; // count, then the ids
s32 D_80101714_name_81[2] = { 1, 0xA00D4 }; // count, then the ids
s32 D_8010171C_name_81[5] = { 4, 0xA0138, 0xA0139, 0xA013A, 0xA013B }; // count, then the ids
s32 D_80101730_name_81[4] = { 3, 0xA013C, 0xA013D, 0xA013E }; // count, then the ids
s32 D_80101740_name_81[5] = { 4, 0xA00E9, 0xA00EA, 0xA00EB, 0xA00EC }; // count, then the ids
s32 D_80101754_name_81[5] = { 4, 0xA0103, 0xA0104, 0xA0105, 0xA0106 }; // count, then the ids
s32 D_80101768_name_81[3] = { 2, 0xA0107, 0xA0108 }; // count, then the ids
s32 D_80101774_name_81[5] = { 4, 0xA00DD, 0xA00DE, 0xA00DF, 0xA00E0 }; // count, then the ids
s32 D_80101788_name_81[2] = { 1, 0xA00E1 }; // count, then the ids
s32 D_80101790_name_81[5] = { 4, 0xA0141, 0xA0142, 0xA0143, 0xA0144 }; // count, then the ids
s32 D_801017A4_name_81[2] = { 1, 0xA0145 }; // count, then the ids
s32 D_801017AC_name_81[3] = { 2, 0xA010F, 0xA0110 }; // count, then the ids
s32 D_801017B8_name_81[5] = { 4, 0xA0113, 0xA0114, 0xA0115, 0xA0116 }; // count, then the ids
s32 D_801017CC_name_81[4] = { 3, 0xA0110, 0xA0111, 0xA0112 }; // count, then the ids
s32 *D_801017DC_name_81[12] = {
    D_80101670_name_81, D_80101690_name_81, D_801016B0_name_81, D_801016D0_name_81,
    D_801016EC_name_81, D_80101700_name_81, D_8010171C_name_81, D_801017AC_name_81,
    D_80101774_name_81, D_80101740_name_81, D_80101790_name_81, D_80101754_name_81,
};
s32 *D_8010180C_name_81[12] = {
    D_80101684_name_81, D_801016A4_name_81, D_801016C4_name_81, D_801016E4_name_81,
    NULL, D_80101714_name_81, D_80101730_name_81, D_801017B8_name_81,
    D_80101788_name_81, NULL, D_801017A4_name_81, D_80101768_name_81,
};
s32 *D_8010183C_name_81[12] = {
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, D_801017CC_name_81,
    NULL, NULL, NULL, NULL,
};
PartnerBaseAttributes PartnersBaseStats[12] = {
    { 0x25, 2, 1, 1, NULL, NULL, NULL, NULL },
    { 0x0C, 1, 2, 2, NULL, NULL, NULL, NULL },
    { 0x09, 1, 1, 1, NULL, NULL, NULL, NULL },
    { 0x26, 1, 1, 3, NULL, NULL, func_800FB148_name_81, NULL },
    { 0x0A, 1, 2, 3, NULL, NULL, NULL, func_800FB158_name_81 },
    { 0x0B, 4, 0, 3, NULL, NULL, NULL, NULL },
    { 0x24, 2, 2, 5, NULL, NULL, NULL, NULL },
    { 0x2C, 1, 3, 5, NULL, NULL, NULL, NULL },
    { 0x2A, 2, 1, 6, NULL, NULL, NULL, NULL },
    { 0x0D, 2, 0, 4, NULL, NULL, NULL, NULL },
    { 0x2B, 3, 1, 2, NULL, NULL, NULL, NULL },
    { 0x29, 1, 1, 3, NULL, NULL, NULL, NULL },
};
Process *D_8010195C_name_81 = NULL;
u8 D_80101960_name_81[8] = { 0x00, 0x01, 0x02, 0x04, 0x03, 0x05, 0x07, 0x06 }; // unreferenced
s8 *D_80101968_name_81 = NULL;
s8 *D_8010196C_name_81 = NULL;
s8 *D_80101970_name_81 = NULL;
s8 *D_80101974_name_81 = NULL;
s8 *D_80101978_name_81 = NULL;
s8 *D_8010197C_name_81 = NULL;
s32 D_80101980_name_81 = 0;
s32 D_80101984_name_81 = 0;
Object *D_80101988_name_81 = NULL;
void (*D_8010198C_name_81)(void) = NULL;
s16 D_80101990_name_81 = 0;
s16 D_80101992_name_81 = 0;
s16 D_80101994_name_81 = 0;
s32 D_80101998_name_81[12] = {
    0x4F00, 0x4F01, 0x4F02, 0x4F03, 0x4F04, 0x4F05, 0x4F06, 0x4F07,
    0x4F08, 0x4F09, 0x4F0A, 0x4F0B,
};
s16 D_801019C8_name_81[12] = {
    23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34,
};
s32 D_801019E0_name_81[5][2] = { { 4, 10 }, { 3, 8 }, { 5, 9 }, { 0, 2 }, { 6, 10 } };
s32 D_80101A08_name_81[5] = { 0x1F16, 0x1F17, 0x1F18, 0x1F19, 0x1F1A };
s32 D_80101A1C_name_81[13] = {
    0x1F0A, 0x1F0B, 0x1F0C, 0x1F0D, 0x1F0E, 0x1F0F, 0x1F10, 0x1F11,
    0x1F12, 0x1F13, 0x1F14, 0x1F15, 0,
};

/* E3CD0 */
s16 D_80101A50_name_81 = 0;
s32 D_80101A54_name_81[7] = { 91, 92, 93, 94, 95, 96, 97 };
s32 D_80101A70_name_81[7] = { 100, 100, 100, 100, 100, 100, 101 };
void (*D_80101A8C_name_81)(void) = NULL;
process_func D_80101A90_name_81 = NULL;
s32 D_80101A94_name_81 = 0;
s32 D_80101A98_name_81 = 0;
u8 D_80101A9C_name_81[4] = { 0x43, 0x44, 0x45, 0x46 };
u8 D_80101AA0_name_81[4] = { 0x05, 0x1E, 0x41, 0x64 };
f32 D_80101AA4_name_81[5][2] = { { 0.0f, 0.0f }, { 200.0f, 250.0f }, { 110.0f, 250.0f }, { 70.0f, 290.0f }, { 0.0f, 360.0f } }; // D_80101AA8 = [0][1]
f32 D_80101ACC_name_81[5][2] = { { 0.0f, 0.0f }, { 20.0f, 70.0f }, { -70.0f, 70.0f }, { 70.0f, 290.0f }, { 0.0f, 360.0f } }; // D_80101AD0 = [0][1]
u8 D_80101AF4_name_81[4] = { 0x03, 0x05, 0x08, 0x0A };
s32 D_80101AF8_name_81 = 0;
s32 D_80101AFC_name_81 = 0;
s32 D_80101B00_name_81 = 0;
s32 D_80101B04_name_81 = 0;
u8 pad_80101B08_name_81[8] = { 0 }; // zero padding to a 16-byte (unit) boundary

