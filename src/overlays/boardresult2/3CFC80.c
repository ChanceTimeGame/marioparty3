#include "common.h"
#include "../ovl_81_name/ovl_81.h"

// event e9: board results, page 2 (the star/coin ranking and the board-record scroll)

/* Texture-animation slot (MP2 TexAnimSlot; 14EA0.c). */
typedef struct BR2TexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} BR2TexAnimSlot; // sizeof 0xC

extern BR2TexAnimSlot* D_800D1714_main;
extern u16 D_800D530C_main;
void func_80032FC0_main(s16, u8, u8);
void func_80033910_main(HmfData*);
void func_80033970_main(HmfData*);
s16 func_800329B4_main(void*);
void func_800D7EB8_name_81(void);
void func_800F3F4C_name_81(void);
void func_800F4300_name_81(void);
void func_800D7F0C_name_81(void);
void func_800F4030_name_81(void);
void func_800F4314_name_81(void);

void func_80108E1C_boardresult2(void);
void func_801096AC_boardresult2(omObjData* obj);
void func_801096F0_boardresult2(omObjData* obj);
void func_80109714_boardresult2(void);
void func_80109740_boardresult2(void);
void func_8010976C_boardresult2(void);
void func_8010979C_boardresult2(void);

extern UnkBoard4* D_801099A0_boardresult2;
extern UnkBoard4* D_801099A4_boardresult2;
extern UnkBoard4* D_801099A8_boardresult2;
extern UnkBoard4* D_801099B0_boardresult2[4];
extern UnkBoard4* D_801099C0_boardresult2;
extern UnkBoard4* D_801099C4_boardresult2;
extern UnkMBGuideData* D_801099C8_boardresult2; /* the record guide: its model and window */
extern UnkBoard4* D_801099CC_boardresult2;
extern UnkBoard4* D_801099D0_boardresult2;
extern UnkBoard4* D_801099D4_boardresult2;
extern UnkBoard4* D_801099D8_boardresult2[4];
extern UnkBoard4* D_801099E8_boardresult2;
extern UnkBoard4* D_801099EC_boardresult2;
extern UnkBoard4* D_801099F0_boardresult2;
extern UnkBoard4* D_801099F4_boardresult2;
extern s32 D_801099F8_boardresult2[16];
extern s16 D_80109A38_boardresult2[10];
extern s16 D_80109A4C_boardresult2;
extern s16 D_80109A4E_boardresult2;
typedef struct BR2Words4 { s32 v[4]; } BR2Words4;
typedef struct BR2Words8 { s32 v[8]; } BR2Words8;
typedef struct BR2Files4x3 { s32 v[4][3]; } BR2Files4x3;
extern s16 kakusiMasuItemHis[]; /* here: the ranking, player index per place */
extern BR2Words4 D_801097C0_boardresult2;   /* place badges' x */
extern BR2Files4x3 D_801097D0_boardresult2; /* per place: the three badge file ids */
extern BR2Words8 D_80109800_boardresult2;   /* per character: portrait file id */
extern BR2Words4 D_80109820_boardresult2;   /* badge parts' x */
extern s32 D_801097B0_boardresult2; /* record scroll: page */
extern s32 D_801097B4_boardresult2; /* record scroll: row */
void func_800D8F0C_name_81(Object*);
void func_800D8E88_name_81(Object*);
void func_800E4E64_name_81(UnkMBGuideData* arg0);
void func_8005FE90_main(s16);
void func_8005FFA8_main(s16);
void func_8005D294_main(s16);
void func_8005B43C_main(s16, s32, s32, s32);
void func_80105B98_boardresult2(s16 model, s16 frame);
void func_801074B4_boardresult2(void);
int sprintf(char* s, const char* fmt, ...);
s32 func_80106B94_boardresult2(s32 row);

void func_801059A0_boardresult2(void) {
    u32 i;
    s32 r;

    omInitObjMan(0x50, 0x50);
    func_8010976C_boardresult2();
    func_80109714_boardresult2();
    func_8005A6B0_main();
    omAddPrcObj(func_80108E1C_boardresult2, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801096F0_boardresult2);
    for (i = 0; i < 16; i++) {
        do {
            r = func_800EFE20_name_81(7.0f);
            D_801099F8_boardresult2[i] = r;
        } while (i != 0 && D_801099F8_boardresult2[i - 1] == r);
    }
}

s16 func_80105A8C_boardresult2(s16 model, s32 file, char* name) {
    void* data;
    s32 slot;
    u16 ret;

    data = DataRead(file);
    slot = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_80109A4C_boardresult2 = slot;
    func_80032FC0_main(slot, 1, 1);
    DataClose(data);
    ret = D_800D1714_main[(s16)slot].unk_00;
    D_80109A4E_boardresult2 = func_80032694_main(HmfModelData[model].hmf, slot, 0, name);
    func_8001C448_main(model);
    return ret;
}

void func_80105B98_boardresult2(s16 model, s16 frame) {
    BR2TexAnimSlot* p;

    if (D_80109A4E_boardresult2 != 0xFF) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
            return;
        }
        func_80033970_main(HmfModelData[model].hmf);
        p = &D_800D1714_main[D_80109A4E_boardresult2];
        p->unk_00 = frame;
        p->unk_04 = 0;
        p->unk_0A = 0;
        p->unk_06 = 0;
        p->unk_02 = 0;
    }
}

s16 func_80105C68_boardresult2(s32 file) {
    void* data;
    s16 sprite;

    data = DataRead(file);
    sprite = func_800329B4_main(data);
    DataClose(data);
    return sprite;
}
/* Builds the ranking: place badges, the results banner, and per place its badges, portrait and
   star and coin digits (sprite group D_801099B0[place], members 1-9). */
// NON_MATCHING: masked 0; register allocation only (the member index j and the &D_801099B0[i]
// pointer take s5/s4 the other way round). Tried declaration orders.
#ifdef NON_MATCHING
void func_80105CB0_boardresult2(void) {
    BR2Words4 badgeX;
    BR2Files4x3 badgeFiles;
    BR2Words8 portraits;
    BR2Words4 partX;
    s32 i;
    s32 j;
    void* data;

    badgeX = D_801097C0_boardresult2;
    badgeFiles = D_801097D0_boardresult2;
    portraits = D_80109800_boardresult2;
    partX = D_80109820_boardresult2;
    D_801099A4_boardresult2 = func_800F4528_name_81(4, 0);
    data = DataRead(0x130030);
    *D_801099A4_boardresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    for (j = 0; j < 4; j++) {
        func_80055024_main(D_801099A4_boardresult2->unk_0A, j, *D_801099A4_boardresult2->unk_0C, 0);
        HuSprPriSet(D_801099A4_boardresult2->unk_0A, j, 0x63);
        HuSprAttrSet(D_801099A4_boardresult2->unk_0A, j, 0x4000);
        func_80054904_main(D_801099A4_boardresult2->unk_0A, j, badgeX.v[j], 0x68);
    }
    D_801099A8_boardresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x130031);
    *D_801099A8_boardresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_801099A8_boardresult2->unk_0A, 0, *D_801099A8_boardresult2->unk_0C, 0);
    HuSprPriSet(D_801099A8_boardresult2->unk_0A, 0, 0x63);
    HuSprAttrSet(D_801099A8_boardresult2->unk_0A, 0, 0x4000);
    func_80054904_main(D_801099A8_boardresult2->unk_0A, 0, 0x37, 0x81);
    for (i = 0; i < 4; i++) {
        D_801099B0_boardresult2[i] = func_800F4528_name_81(10, 2);
        for (j = 0; j < 3; j++) {
            data = DataRead(badgeFiles.v[i][j]);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
            DataClose(data);
            func_80055024_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1], 0);
            HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x62 - j);
            HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
            func_80054904_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, partX.v[j], 0);
        }
        data = DataRead(portraits.v[GwPlayer[kakusiMasuItemHis[i]].chr]);
        j = 4;
        D_801099B0_boardresult2[i]->unk_0C[4] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_801099B0_boardresult2[i]->unk_0A, 4, D_801099B0_boardresult2[i]->unk_0C[4], 0);
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, 4, 0x5F);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, 4, 0x4000);
        func_80054904_main(D_801099B0_boardresult2[i]->unk_0A, 4, partX.v[3], 1);
        if (GwPlayer[kakusiMasuItemHis[i]].star >= 10) {
            data = DataRead(0xC0086);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        } else {
            data = DataRead(0xC003C);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        }
        DataClose(data);
        func_80055024_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                           GwPlayer[kakusiMasuItemHis[i]].star / 10);
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x62 - j);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
        func_80054904_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x44, 4);
        j = 5;
        data = DataRead(0xC0086);
        D_801099B0_boardresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                           GwPlayer[kakusiMasuItemHis[i]].star % 10);
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x62 - j);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
        func_80054904_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x54, 4);
        j = 6;
        if (GwPlayer[kakusiMasuItemHis[i]].coin >= 100) {
            data = DataRead(0xC0086);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        } else {
            data = DataRead(0xC003C);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        }
        DataClose(data);
        func_80055024_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                           GwPlayer[kakusiMasuItemHis[i]].coin / 100);
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x62 - j);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
        func_80054904_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x8E, 4);
        j = 7;
        data = DataRead(0xC0086);
        D_801099B0_boardresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        DataClose(data);
        if (GwPlayer[kakusiMasuItemHis[i]].coin >= 10) {
            func_80055024_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                               GwPlayer[kakusiMasuItemHis[i]].coin / 10 % 10);
        } else {
            func_80055024_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                               GwPlayer[kakusiMasuItemHis[i]].coin);
        }
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x62 - j);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
        func_80054904_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x9E, 4);
        if (GwPlayer[kakusiMasuItemHis[i]].coin >= 10) {
            j = 8;
            data = DataRead(0xC0086);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
            DataClose(data);
            func_80055024_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                               GwPlayer[kakusiMasuItemHis[i]].coin % 10);
            HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x62 - j);
            HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
            func_80054904_main(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0xAE, 4);
        }
    }
    for (i = 0; i < 4; i++) {
        func_80054904_main(D_801099B0_boardresult2[i]->unk_0A, 0, 0x6F, i * 40 + 0x45);
    }
    D_801099C0_boardresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x130046);
    *D_801099C0_boardresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_801099C0_boardresult2->unk_0A, 0, *D_801099C0_boardresult2->unk_0C, 0);
    HuSprPriSet(D_801099C0_boardresult2->unk_0A, 0, 0x5A);
    HuSprAttrSet(D_801099C0_boardresult2->unk_0A, 0, 0x4000);
    func_80054904_main(D_801099C0_boardresult2->unk_0A, 0, 0xA0, 0x21);
    D_801099C4_boardresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x130062);
    *D_801099C4_boardresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_801099C4_boardresult2->unk_0A, 0, *D_801099C4_boardresult2->unk_0C, 0);
    HuSprPriSet(D_801099C4_boardresult2->unk_0A, 0, 0x59);
    HuSprAttrSet(D_801099C4_boardresult2->unk_0A, 0, 0x4000);
    func_80054904_main(D_801099C4_boardresult2->unk_0A, 0, 0x37, 0x29);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80105CB0_boardresult2);
#endif

void func_80106924_boardresult2(void) {
    s32 i;

    func_800F4584_name_81(D_801099A4_boardresult2);
    func_800F4584_name_81(D_801099A8_boardresult2);
    for (i = 0; i < 4; i++) {
        func_800F4584_name_81(D_801099B0_boardresult2[i]);
    }
    func_800F4584_name_81(D_801099C0_boardresult2);
    func_800F4584_name_81(D_801099C4_boardresult2);
}

void func_801069A4_boardresult2(void) {
    s32 j;
    s32 i;

    for (j = 0; j < 4; j++) {
        HuSprAttrSet(D_801099A4_boardresult2->unk_0A, j, 0x8000);
    }
    HuSprAttrSet(D_801099A8_boardresult2->unk_0A, 0, 0x8000);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j, 0x8000);
        }
    }
    HuSprAttrSet(D_801099C0_boardresult2->unk_0A, 0, 0x8000);
    HuSprAttrSet(D_801099C4_boardresult2->unk_0A, 0, 0x8000);
}

void func_80106A9C_boardresult2(void) {
    s32 j;
    s32 i;

    for (j = 0; j < 4; j++) {
        HuSprAttrReset(D_801099A4_boardresult2->unk_0A, j, 0x8000);
    }
    HuSprAttrReset(D_801099A8_boardresult2->unk_0A, 0, 0x8000);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprAttrReset(D_801099B0_boardresult2[i]->unk_0A, j, 0x8000);
        }
    }
    HuSprAttrReset(D_801099C0_boardresult2->unk_0A, 0, 0x8000);
    HuSprAttrReset(D_801099C4_boardresult2->unk_0A, 0, 0x8000);
}

/* Record row arg0 (0 star, 1 coin, 2 gamePrize, 3 coinPrize, 4-12 the PrizeStats counts): bit n
   set for each place n holding the highest value, or 0 when all four tie. */
s32 func_80106B94_boardresult2(s32 row) {
    s32 i;
    s32 max;
    s32 mask;

    mask = 0;
    switch (row) {
    case 0:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].star) {
                max = GwPlayer[kakusiMasuItemHis[i]].star;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].star == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 1:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].coin) {
                max = GwPlayer[kakusiMasuItemHis[i]].coin;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].coin == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 2:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].gamePrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].gamePrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].gamePrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 3:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].coinPrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].coinPrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].coinPrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 4:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.bluePrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.bluePrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.bluePrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 5:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.redPrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.redPrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.redPrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 6:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.hatenaPrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.hatenaPrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.hatenaPrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 7:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.eventPrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.eventPrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.eventPrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 8:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.kupaPrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.kupaPrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.kupaPrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 9:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.battlePrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.battlePrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.battlePrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 10:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.itemPrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.itemPrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.itemPrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 11:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.bankPrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.bankPrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.bankPrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 12:
        for (i = 0, max = -100000; i < 4; i++) {
            if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.gamblePrize) {
                max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.gamblePrize;
            }
        }
        for (i = 0; i < 4; i++) {
            if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.gamblePrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    }
    if (mask == 0xF) {
        return 0;
    }
    return mask;
}

// NON_MATCHING: loop-invariant placement and register allocation (retail hoists k * 16 and k * 11
// into stack slots, keeps the value in a2); the "" after "%4d" in retail .rodata is not emitted.
#ifdef NON_MATCHING
/* Draws the four visible record rows (D_801097B0 onwards): each place's value in four digit
   sprites of D_801099F0, the row leaders in the second digit set, then the row cursor. */
void func_801074B4_boardresult2(void) {
    u8 buf[8];
    s32 offs[5] = { 0, -30, -25, -20, -15 };
    GW_PLAYER* player;
    s32 lead;
    s32 digits;
    s32 value;
    s32 row;
    s32 k;
    s32 p;
    s32 c;
    s32 member;

    for (row = 0; row < 13; row++) {
        HuSprAttrSet(D_801099EC_boardresult2->unk_0A, row, 0x8000);
    }
    for (row = D_801097B0_boardresult2, k = 0; row < D_801097B0_boardresult2 + 4; row++, k++) {
        HuSprAttrReset(D_801099EC_boardresult2->unk_0A, row, 0x8000);
        func_80054904_main(D_801099EC_boardresult2->unk_0A, row, k * 44 + 0x91, 0x34);
    }
    for (row = 0; row < 64; row++) {
        HuSprAttrSet(D_801099F0_boardresult2->unk_0A, row, 0x8000);
    }
    for (row = D_801097B0_boardresult2, k = 0; row < D_801097B0_boardresult2 + 4; row++, k++) {
        for (p = 0; p < 4; p++) {
            player = MBDGetPlayerStruct(kakusiMasuItemHis[p]);
            digits = 1;
            value = 1;
            lead = func_80106B94_boardresult2(row);
            switch (row) {
        case 0:
            value = player->star;
            digits = 2;
            break;
        case 1:
            value = player->coin;
            digits = 3;
            break;
        case 2:
            value = player->gamePrize;
            if (value >= 1000) {
                value = 999;
            }
            digits = 3;
            break;
        case 3:
            value = player->coinPrize;
            digits = 3;
            break;
        case 4:
            value = player->stats.prize.bluePrize;
            digits = 2;
            break;
        case 5:
            value = player->stats.prize.redPrize;
            digits = 2;
            break;
        case 6:
            value = player->stats.prize.hatenaPrize;
            digits = 2;
            break;
        case 7:
            value = player->stats.prize.eventPrize;
            digits = 2;
            break;
        case 8:
            value = player->stats.prize.kupaPrize;
            digits = 2;
            break;
        case 9:
            value = player->stats.prize.battlePrize;
            digits = 2;
            break;
        case 10:
            value = player->stats.prize.itemPrize;
            digits = 2;
            break;
        case 11:
            value = player->stats.prize.bankPrize;
            digits = 2;
            break;
        case 12:
            value = player->stats.prize.gamblePrize;
            digits = 2;
            break;
            }
            sprintf((char*)buf, "%4d", value);
            member = k * 16 + p * 4;
            for (c = 0; c < 4; c++) {
                if (buf[c] == ' ') {
                    HuSprAttrSet(D_801099F0_boardresult2->unk_0A, member + c, 0x8000);
                    continue;
                }
                if (lead & (1 << p)) {
                    func_80055024_main(D_801099F0_boardresult2->unk_0A, member + c, D_801099F0_boardresult2->unk_0C[1], 0);
                } else {
                    func_80055024_main(D_801099F0_boardresult2->unk_0A, member + c, D_801099F0_boardresult2->unk_0C[0], 0);
                }
                HuSprAttrReset(D_801099F0_boardresult2->unk_0A, member + c, 0x8000);
                func_80054904_main(D_801099F0_boardresult2->unk_0A, member + c, c * 10 + 0x91 + k * 44 + offs[digits],
                                   p * 22 + 0x49);
                func_80055140_main(D_801099F0_boardresult2->unk_0A, member + c, buf[c] - '0', 0);
                func_800550F4_main(D_801099F0_boardresult2->unk_0A, member + c, 1);
            }
        }
    }
    func_80054904_main(D_801099F4_boardresult2->unk_0A, 0, D_801097B4_boardresult2 * 44 + 0x92, 0x60);
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_80109864_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_801074B4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_80109880_boardresult2);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098B4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098C4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098DC_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098FC_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010991C_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010992C_boardresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80107964_boardresult2);

void func_80108548_boardresult2(void) {
    s32 i;

    func_800F4584_name_81(D_801099CC_boardresult2);
    func_800F4584_name_81(D_801099D0_boardresult2);
    func_800F4584_name_81(D_801099D4_boardresult2);
    for (i = 0; i < 4; i++) {
        func_800F4584_name_81(D_801099D8_boardresult2[i]);
    }
    func_800F4584_name_81(D_801099E8_boardresult2);
    func_800F4584_name_81(D_801099EC_boardresult2);
    func_800F4584_name_81(D_801099F0_boardresult2);
    func_800F4584_name_81(D_801099F4_boardresult2);
    func_800E4E64_name_81(D_801099C8_boardresult2);
}

void func_801085F8_boardresult2(void) {
    s32 j;
    s32 i;

    HuSprAttrSet(D_801099CC_boardresult2->unk_0A, 0, 0x8000);
    HuSprAttrSet(D_801099D0_boardresult2->unk_0A, 0, 0x8000);
    HuSprAttrSet(D_801099D0_boardresult2->unk_0A, 1, 0x8000);
    HuSprAttrSet(D_801099D4_boardresult2->unk_0A, 0, 0x8000);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprAttrSet(D_801099D8_boardresult2[i]->unk_0A, j, 0x8000);
        }
    }
    for (j = 0; j < 2; j++) {
        HuSprAttrSet(D_801099E8_boardresult2->unk_0A, j, 0x8000);
    }
    for (j = 0; j < 13; j++) {
        HuSprAttrSet(D_801099EC_boardresult2->unk_0A, j, 0x8000);
    }
    for (j = 0; j < 64; j++) {
        HuSprAttrSet(D_801099F0_boardresult2->unk_0A, j, 0x8000);
    }
    HuSprAttrSet(D_801099F4_boardresult2->unk_0A, 0, 0x8000);
    func_800D8F0C_name_81(D_801099C8_boardresult2->obj);
    func_8005FE90_main(D_801099C8_boardresult2->amount);
}

void func_8010879C_boardresult2(void) {
    s32 j;
    s32 i;

    HuSprAttrReset(D_801099CC_boardresult2->unk_0A, 0, 0x8000);
    HuSprAttrReset(D_801099D0_boardresult2->unk_0A, 0, 0x8000);
    HuSprAttrReset(D_801099D0_boardresult2->unk_0A, 1, 0x8000);
    HuSprAttrReset(D_801099D4_boardresult2->unk_0A, 0, 0x8000);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprAttrReset(D_801099D8_boardresult2[i]->unk_0A, j, 0x8000);
        }
    }
    for (j = 0; j < 2; j++) {
        HuSprAttrReset(D_801099E8_boardresult2->unk_0A, j, 0x8000);
    }
    func_801074B4_boardresult2();
    HuSprAttrReset(D_801099F4_boardresult2->unk_0A, 0, 0x8000);
    func_800D8E88_name_81(D_801099C8_boardresult2->obj);
    func_8005FFA8_main(D_801099C8_boardresult2->amount);
    if (D_801097B0_boardresult2 == 0 && D_801097B4_boardresult2 == 0) {
        HuSprAttrSet(D_801099E8_boardresult2->unk_0A, 0, 0x8000);
    }
    if (D_801097B0_boardresult2 == 9 && D_801097B4_boardresult2 == 3) {
        HuSprAttrSet(D_801099E8_boardresult2->unk_0A, 1, 0x8000);
    }
}

void func_80108958_boardresult2(void) {
    s32 msgs[13] = { 0x1900, 0x1901, 0x1902, 0x1903, 0x1904, 0x1905, 0x1906,
                     0x1907, 0x1908, 0x1909, 0x190A, 0x190B, 0x190C };

    func_8005D294_main(D_801099C8_boardresult2->amount);
    func_8005B43C_main(D_801099C8_boardresult2->amount, msgs[D_801097B0_boardresult2 + D_801097B4_boardresult2], -1, -1);
    func_80105B98_boardresult2(D_801099C8_boardresult2->obj->omObj1->model[0],
                               D_80109A38_boardresult2[D_801099F8_boardresult2[D_801097B0_boardresult2 + D_801097B4_boardresult2]]);
}

void func_80108A48_boardresult2(void) {
    s32 idx;
    f32 angle;
    f32 amp;

    idx = *(s32*)HuPrcCurrentGet()->user_data;
    for (angle = 90.0f; angle < 180.0f; angle += 10.0f) {
        func_80054904_main(D_801099B0_boardresult2[idx]->unk_0A, 0, 0x6F,
                           (idx * 40 + 0x45) + sindf(angle) * -(idx * 40 + 0x6D));
        HuPrcVSleep();
    }
    amp = -8.0f;
    HuAudFXPlay(0x178);
    for (angle = 0.0f; angle <= 1260.0f; angle += 50.0f) {
        func_80054904_main(D_801099B0_boardresult2[idx]->unk_0A, 0, 0x6F, (idx * 40 + 0x45) + sindf(angle) * amp);
        amp += 0.3174603f;
        if (amp > 0.0f) {
            amp = 0.0f;
        }
        HuPrcVSleep();
    }
    func_80054904_main(D_801099B0_boardresult2[idx]->unk_0A, 0, 0x6F, idx * 40 + 0x45);
    omDelPrcObj(NULL);
}

/* The title banner bounces in. NON_MATCHING: the KMC assembler puts a nop between the delay-slot
   mov.s of each sindf call and the mul.s after it (GCC fills that slot itself and emits a blank
   line; retail looks gas-filled). Tried do-while and for loops, operand orders. */
#ifdef NON_MATCHING
void func_80108C70_boardresult2(void) {
    f32 angle;
    f32 amp;

    angle = 90.0f;
    do {
        func_80054904_main(D_801099C0_boardresult2->unk_0A, 0, 0xA0, sindf(angle) * -73.0f + 33.0f);
        HuPrcVSleep();
        angle += 10.0f;
    } while (angle < 180.0f);
    amp = -4.0f;
    HuAudFXPlay(0x179);
    angle = 0.0f;
    do {
        func_80054904_main(D_801099C0_boardresult2->unk_0A, 0, 0xA0, sindf(angle) * amp + 33.0f);
        amp += 0.2777778f;
        if (amp > 0.0f) {
            amp = 0.0f;
        }
        HuPrcVSleep();
        angle += 50.0f;
    } while (angle <= 720.0f);
    func_80054904_main(D_801099C0_boardresult2->unk_0A, 0, 0xA0, 0x21);
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108C70_boardresult2);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108E1C_boardresult2);

void func_801096AC_boardresult2(omObjData* obj) {
    if (WipeStatGet() == 0) {
        func_8010979C_boardresult2();
        func_80109740_boardresult2();
        func_8005F524_main();
        omOvlReturnEx(1);
    }
}

void func_801096F0_boardresult2(omObjData* obj) {
    if (D_800D530C_main != 0) {
        obj->func = func_801096AC_boardresult2;
    }
}

void func_80109714_boardresult2(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800F4300_name_81();
}

void func_80109740_boardresult2(void) {
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    func_800F4314_name_81();
}

void func_8010976C_boardresult2(void) {
    Hu3DCamInit(2);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_8010979C_boardresult2(void) {
}

