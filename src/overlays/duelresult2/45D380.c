#include "common.h"
#include "../ovl_81_name/ovl_81.h"

// duel k1
/* duelresult2 (0x63): Duel Mode's end-of-game records screen. */

/* Texture-animation slot (14EA0.c TexAnimSlot). */
typedef struct OtTexAnimSlot {
    /* 0x00 */ s16 frame;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ char unk08[2];
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B;
} OtTexAnimSlot; /* size = 0xC */

extern u16 D_800D530C_main;
extern OtTexAnimSlot *D_800D1714_main;
void func_80032FC0_main(s16, u8, u8);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
s16 func_800329B4_main(void *);

typedef struct DR2Words4 { s32 v[4]; } DR2Words4;
typedef struct DR2Words8 { s32 v[8]; } DR2Words8;
typedef struct DR2Files2x3 { s32 v[2][3]; } DR2Files2x3;

extern s16 kakusiMasuItemHis[]; /* Duel Mode: [0] the winner, [2] -1 unless the duel was decided (boardresult2: the ranking) */
extern u16 D_800C9520_main[];
extern s16 D_800D0590_main[];
void func_800D8F0C_name_81(Object *);
void func_800D8E88_name_81(Object *);
void func_800E4E64_name_81(UnkMBGuideData *arg0);
void func_800E4EAC_name_81(UnkMBGuideData *arg0, s16 arg1, s16 arg2);
UnkMBGuideData *func_800E4B64_name_81(s32 arg0, s32 arg1);
void *func_800E172C_name_81(s16 msgIdx, s16 x, s16 y, u16 hideOnFlag); /* DuelHelpWin* */
void func_800E1854_minigame(void *win);                                  /* ovl_81 func_800E1854 */
void func_8005FE90_main(s16);
void func_8005FFA8_main(s16);
void func_8005D294_main(s16);
void func_8005B43C_main(s16, s32, s32, s32);
int sprintf(char *s, const char *fmt, ...);

s16 func_80105A8C_duelresult2(s16 model, s32 file, char *name);
void func_80105B98_duelresult2(s16 model, s16 frame);
s16 func_80105C68_duelresult2(s32 file);
void func_80105CB0_duelresult2(void);
void func_80106848_duelresult2(void);
void func_801068BC_duelresult2(void);
void func_80106974_duelresult2(void);
s32 func_80106A2C_duelresult2(s32 row);
void func_80106F7C_duelresult2(void);
void func_80107454_duelresult2(void);
void func_80107FEC_duelresult2(void);
void func_8010809C_duelresult2(void);
void func_80108240_duelresult2(void);
void func_801083FC_duelresult2(void);
void func_801084F4_duelresult2(void);
void func_80108B38_duelresult2(omObjData *obj);
void func_80108B7C_duelresult2(omObjData *obj);
void func_80108BA0_duelresult2(void);
void func_80108BCC_duelresult2(void);
void func_80108BF8_duelresult2(void);
void func_80108C28_duelresult2(void);

extern UnkBoard4 *D_80108C30_duelresult2; /* the result banner, NULL on a draw */
extern s32 D_80108C34_duelresult2; /* record scroll: first row shown */
extern s32 D_80108C38_duelresult2; /* record scroll: cursor row on screen */
extern DR2Files2x3 D_80108C40_duelresult2; /* per player: the three badge file ids */
extern DR2Files2x3 D_80108C58_duelresult2; /* per player: the result file (won, lost, draw) */
extern DR2Words8 D_80108C70_duelresult2;   /* per character: portrait file id */
extern DR2Words4 D_80108C90_duelresult2;   /* badge parts' x */

extern UnkBoard4 *D_80108DB0_duelresult2;
extern UnkBoard4 *D_80108DB4_duelresult2[2];
extern UnkBoard4 *D_80108DBC_duelresult2;
extern UnkMBGuideData *D_80108DC0_duelresult2; /* the record guide: its model and window */
extern UnkBoard4 *D_80108DC4_duelresult2;
extern UnkBoard4 *D_80108DC8_duelresult2;
extern UnkBoard4 *D_80108DCC_duelresult2;
extern UnkBoard4 *D_80108DD0_duelresult2[2];
extern UnkBoard4 *D_80108DD8_duelresult2;
extern UnkBoard4 *D_80108DDC_duelresult2;
extern UnkBoard4 *D_80108DE0_duelresult2;
extern UnkBoard4 *D_80108DE4_duelresult2;
extern s32 D_80108DE8_duelresult2[16];
extern s16 D_80108E28_duelresult2[10];
extern s16 D_80108E3C_duelresult2;
extern s16 D_80108E3E_duelresult2; /* texture-animation slot, 0xFF none */

void func_801059A0_duelresult2(void) {
    u32 i;
    s32 r;

    omInitObjMan(0x50, 0x50);
    func_80108BF8_duelresult2();
    func_80108BA0_duelresult2();
    func_8005A6B0_main();
    omAddPrcObj(func_801084F4_duelresult2, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80108B7C_duelresult2);
    for (i = 0; i < 16; i++) {
        do {
            r = func_800EFE20_name_81(7.0f);
            D_80108DE8_duelresult2[i] = r;
        } while (i != 0 && D_80108DE8_duelresult2[i - 1] == r);
    }
}

s16 func_80105A8C_duelresult2(s16 model, s32 file, char *name) {
    void *data;
    s32 slot;
    u16 ret;

    data = DataRead(file);
    slot = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_80108E3C_duelresult2 = slot;
    func_80032FC0_main(slot, 1, 1);
    DataClose(data);
    ret = D_800D1714_main[(s16)slot].frame;
    D_80108E3E_duelresult2 = func_80032694_main(HmfModelData[model].hmf, slot, 0, name);
    func_8001C448_main(model);
    return ret;
}

void func_80105B98_duelresult2(s16 model, s16 frame) {
    OtTexAnimSlot *p;

    if (D_80108E3E_duelresult2 != 0xFF) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
            return;
        }
        func_80033970_main(HmfModelData[model].hmf);
        p = &D_800D1714_main[D_80108E3E_duelresult2];
        p->frame = frame;
        p->unk04 = 0;
        p->unk0A = 0;
        p->unk06 = 0;
        p->unk02 = 0;
    }
}

s16 func_80105C68_duelresult2(s32 file) {
    void *data;
    s16 sprite;

    data = DataRead(file);
    sprite = func_800329B4_main(data);
    DataClose(data);
    return sprite;
}

// NON_MATCHING: masked 0; register allocation only (the member index j and the &D_80108DB4[i]
// pointer take s5/s4 the other way round), as in boardresult2's twin.
#ifdef NON_MATCHING
/* Builds the results page: per player its badges, portrait and star and coin digits and its
   result (sprite group D_80108DB4[i], members 1-10), the title banner and, unless the duel was a
   draw, the result banner. */
void func_80105CB0_duelresult2(void) {
    DR2Files2x3 badgeFiles;
    DR2Files2x3 resultFiles;
    DR2Words8 portraits;
    DR2Words4 partX;
    s32 i;
    s32 j;
    void *data;

    badgeFiles = D_80108C40_duelresult2;
    resultFiles = D_80108C58_duelresult2;
    portraits = D_80108C70_duelresult2;
    partX = D_80108C90_duelresult2;
    for (i = 0; i < 2; i++) {
        D_80108DB4_duelresult2[i] = func_800F4528_name_81(11, 2);
        for (j = 0; j < 3; j++) {
            data = DataRead(badgeFiles.v[i][j]);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
            DataClose(data);
            func_80055024_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1], 0);
            HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x62 - j);
            HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
            func_80054904_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, partX.v[j], 0);
        }
        data = DataRead(portraits.v[GwPlayer[i].chr]);
        j = 4;
        D_80108DB4_duelresult2[i]->unk_0C[4] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80108DB4_duelresult2[i]->unk_0A, 4, D_80108DB4_duelresult2[i]->unk_0C[4], 0);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, 4, 0x5F);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, 4, 0x4000);
        func_80054904_main(D_80108DB4_duelresult2[i]->unk_0A, 4, partX.v[3], 1);
        if (GwPlayer[i].star >= 10) {
            data = DataRead(0xC0086);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        } else {
            data = DataRead(0xC003C);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        }
        DataClose(data);
        func_80055024_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                           GwPlayer[i].star / 10);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x62 - j);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
        func_80054904_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x44, 4);
        j = 5;
        data = DataRead(0xC0086);
        D_80108DB4_duelresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                           GwPlayer[i].star % 10);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x62 - j);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
        func_80054904_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x54, 4);
        j = 6;
        if (GwPlayer[i].coin >= 100) {
            data = DataRead(0xC0086);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        } else {
            data = DataRead(0xC003C);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        }
        DataClose(data);
        func_80055024_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                           GwPlayer[i].coin / 100);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x62 - j);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
        func_80054904_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x8E, 4);
        j = 7;
        data = DataRead(0xC0086);
        D_80108DB4_duelresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        DataClose(data);
        if (GwPlayer[i].coin >= 10) {
            func_80055024_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                               GwPlayer[i].coin / 10 % 10);
        } else {
            func_80055024_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                               GwPlayer[i].coin);
        }
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x62 - j);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
        func_80054904_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x9E, 4);
        if (GwPlayer[i].coin >= 10) {
            j = 8;
            data = DataRead(0xC0086);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
            DataClose(data);
            func_80055024_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                               GwPlayer[i].coin % 10);
            HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x62 - j);
            HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
            func_80054904_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0xAE, 4);
        }
        j = 9;
        if (kakusiMasuItemHis[2] == -1) {
            data = DataRead(resultFiles.v[i][2]);
        } else if (kakusiMasuItemHis[0] == i) {
            data = DataRead(resultFiles.v[i][0]);
        } else {
            data = DataRead(resultFiles.v[i][1]);
        }
        D_80108DB4_duelresult2[i]->unk_0C[j + 1] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1], 0);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x62 - j);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
        func_80054904_main(D_80108DB4_duelresult2[i]->unk_0A, j + 1, -0x38, 0);
    }
    for (i = 0; i < 2; i++) {
        func_80054904_main(D_80108DB4_duelresult2[i]->unk_0A, 0, 0x6F, i * 0x3E + 0x5B);
    }
    D_80108DBC_duelresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x130046);
    *D_80108DBC_duelresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80108DBC_duelresult2->unk_0A, 0, *D_80108DBC_duelresult2->unk_0C, 0);
    HuSprPriSet(D_80108DBC_duelresult2->unk_0A, 0, 0x5A);
    HuSprAttrSet(D_80108DBC_duelresult2->unk_0A, 0, 0x4000);
    func_80054904_main(D_80108DBC_duelresult2->unk_0A, 0, 0xA0, 0x21);
    if (kakusiMasuItemHis[2] != -1) {
        D_80108C30_duelresult2 = func_800F4528_name_81(1, 0);
        data = DataRead(0x130062);
        *D_80108C30_duelresult2->unk_0C = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80108C30_duelresult2->unk_0A, 0, *D_80108C30_duelresult2->unk_0C, 0);
        HuSprPriSet(D_80108C30_duelresult2->unk_0A, 0, 0x59);
        HuSprAttrSet(D_80108C30_duelresult2->unk_0A, 0, 0x4000);
        if (kakusiMasuItemHis[0] == 0) {
            func_80054904_main(D_80108C30_duelresult2->unk_0A, 0, 0x37, 0x40);
        } else {
            func_80054904_main(D_80108C30_duelresult2->unk_0A, 0, 0x37, 0x7E);
        }
        return;
    }
    D_80108C30_duelresult2 = NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80105CB0_duelresult2);
#endif

void func_80106848_duelresult2(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800F4584_name_81(D_80108DB4_duelresult2[i]);
    }
    func_800F4584_name_81(D_80108DBC_duelresult2);
    if (D_80108C30_duelresult2 != NULL) {
        func_800F4584_name_81(D_80108C30_duelresult2);
    }
}

void func_801068BC_duelresult2(void) {
    s32 j;
    s32 i;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 11; j++) {
            HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j, 0x8000);
        }
    }
    HuSprAttrSet(D_80108DBC_duelresult2->unk_0A, 0, 0x8000);
    if (D_80108C30_duelresult2 != NULL) {
        HuSprAttrSet(D_80108C30_duelresult2->unk_0A, 0, 0x8000);
    }
}

void func_80106974_duelresult2(void) {
    s32 j;
    s32 i;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 11; j++) {
            HuSprAttrReset(D_80108DB4_duelresult2[i]->unk_0A, j, 0x8000);
        }
    }
    HuSprAttrReset(D_80108DBC_duelresult2->unk_0A, 0, 0x8000);
    if (D_80108C30_duelresult2 != NULL) {
        HuSprAttrReset(D_80108C30_duelresult2->unk_0A, 0, 0x8000);
    }
}

/* Duel Mode keeps per-player s16[2] record counters in GwSystem (0x42-0x57, over boardData and the
   fields after it). */
#define DR2_DUELSTAT(off) ((s16 *)((u8 *)&GwSystem + (off)))

/* Record row (0 star, 1 coin, 2 gamePrize, 3 coinPrize, 4-9 the duel counters): bit n set for each
   player n holding the highest value, or 0 when both tie. */
s32 func_80106A2C_duelresult2(s32 row) {
    s32 i;
    s32 max;
    s32 mask;

    mask = 0;
    switch (row) {
    case 0:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < GwPlayer[i].star) {
                max = GwPlayer[i].star;
            }
        }
        for (i = 0; i < 2; i++) {
            if (GwPlayer[i].star == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 1:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < GwPlayer[i].coin) {
                max = GwPlayer[i].coin;
            }
        }
        for (i = 0; i < 2; i++) {
            if (GwPlayer[i].coin == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 2:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < GwPlayer[i].gamePrize) {
                max = GwPlayer[i].gamePrize;
            }
        }
        for (i = 0; i < 2; i++) {
            if (GwPlayer[i].gamePrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 3:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < GwPlayer[i].coinPrize) {
                max = GwPlayer[i].coinPrize;
            }
        }
        for (i = 0; i < 2; i++) {
            if (GwPlayer[i].coinPrize == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 4:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < DR2_DUELSTAT(0x56)[i]) {
                max = DR2_DUELSTAT(0x56)[i];
            }
        }
        for (i = 0; i < 2; i++) {
            if (DR2_DUELSTAT(0x56)[i] == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 5:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < DR2_DUELSTAT(0x42)[i]) {
                max = DR2_DUELSTAT(0x42)[i];
            }
        }
        for (i = 0; i < 2; i++) {
            if (DR2_DUELSTAT(0x42)[i] == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 6:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < DR2_DUELSTAT(0x4E)[i]) {
                max = DR2_DUELSTAT(0x4E)[i];
            }
        }
        for (i = 0; i < 2; i++) {
            if (DR2_DUELSTAT(0x4E)[i] == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 7:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < DR2_DUELSTAT(0x52)[i]) {
                max = DR2_DUELSTAT(0x52)[i];
            }
        }
        for (i = 0; i < 2; i++) {
            if (DR2_DUELSTAT(0x52)[i] == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 8:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < DR2_DUELSTAT(0x46)[i]) {
                max = DR2_DUELSTAT(0x46)[i];
            }
        }
        for (i = 0; i < 2; i++) {
            if (DR2_DUELSTAT(0x46)[i] == max) {
                mask |= 1 << i;
            }
        }
        break;
    case 9:
        for (i = 0, max = -100000; i < 2; i++) {
            if (max < DR2_DUELSTAT(0x4A)[i]) {
                max = DR2_DUELSTAT(0x4A)[i];
            }
        }
        for (i = 0; i < 2; i++) {
            if (DR2_DUELSTAT(0x4A)[i] == max) {
                mask |= 1 << i;
            }
        }
        break;
    }
    if (mask == 3) {
        return 0;
    }
    return mask;
}


// NON_MATCHING: masked 71; retail hoists k * 16, k * 11 and the lead bit into stack slots (a 0x78
// frame) and differs in register allocation, as in boardresult2's twin func_801074B4. Logic checked
// against the asm: same loads (star s8, coin/gamePrize/coinPrize s16, the duel counters s16), the
// 999/99 clamps and the clamp of negatives to 0 before sprintf.
#ifdef NON_MATCHING
/* Draws the four visible record rows (D_80108C34 onwards): each player's value in four digit
   sprites of D_80108DE0, the row leaders in the second digit set, then the row cursor. */
void func_80106F7C_duelresult2(void) {
    u8 buf[8];
    s32 offs[5] = { 0, -30, -25, -20, -15 };
    GW_PLAYER *player;
    s32 lead;
    s32 digits;
    s32 value;
    s32 row;
    s32 k;
    s32 p;
    s32 c;
    s32 member;

    for (row = 0; row < 10; row++) {
        HuSprAttrSet(D_80108DDC_duelresult2->unk_0A, row, 0x8000);
    }
    for (row = D_80108C34_duelresult2, k = 0; row < D_80108C34_duelresult2 + 4; row++, k++) {
        HuSprAttrReset(D_80108DDC_duelresult2->unk_0A, row, 0x8000);
        func_80054904_main(D_80108DDC_duelresult2->unk_0A, row, k * 44 + 0x91, 0x49);
    }
    for (row = 0; row < 64; row++) {
        HuSprAttrSet(D_80108DE0_duelresult2->unk_0A, row, 0x8000);
    }
    for (row = D_80108C34_duelresult2, k = 0; row < D_80108C34_duelresult2 + 4; row++, k++) {
        for (p = 0; p < 2; p++) {
            player = MBDGetPlayerStruct(p);
            lead = func_80106A2C_duelresult2(row);
            digits = 1;
            value = 1;
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
                value = DR2_DUELSTAT(0x56)[p];
                if (value >= 100) {
                    value = 99;
                }
                digits = 2;
                break;
            case 5:
                value = DR2_DUELSTAT(0x42)[p];
                if (value >= 100) {
                    value = 99;
                }
                digits = 2;
                break;
            case 6:
                value = DR2_DUELSTAT(0x4E)[p];
                if (value >= 100) {
                    value = 99;
                }
                digits = 2;
                break;
            case 7:
                value = DR2_DUELSTAT(0x52)[p];
                if (value >= 100) {
                    value = 99;
                }
                digits = 2;
                break;
            case 8:
                value = DR2_DUELSTAT(0x46)[p];
                if (value >= 100) {
                    value = 99;
                }
                digits = 2;
                break;
            case 9:
                value = DR2_DUELSTAT(0x4A)[p];
                if (value >= 100) {
                    value = 99;
                }
                digits = 2;
                break;
            }
            if (value < 0) {
                value = 0;
            }
            sprintf((char *)buf, "%4d", value);
            member = k * 16 + p * 4;
            for (c = 0; c < 4; c++) {
                if (buf[c] == ' ') {
                    HuSprAttrSet(D_80108DE0_duelresult2->unk_0A, member + c, 0x8000);
                    continue;
                }
                if (lead & (1 << p)) {
                    func_80055024_main(D_80108DE0_duelresult2->unk_0A, member + c, D_80108DE0_duelresult2->unk_0C[1], 0);
                } else {
                    func_80055024_main(D_80108DE0_duelresult2->unk_0A, member + c, D_80108DE0_duelresult2->unk_0C[0], 0);
                }
                HuSprAttrReset(D_80108DE0_duelresult2->unk_0A, member + c, 0x8000);
                func_80054904_main(D_80108DE0_duelresult2->unk_0A, member + c, c * 10 + 0x91 + k * 44 + offs[digits],
                                   p * 26 + 0x63);
                func_80055140_main(D_80108DE0_duelresult2->unk_0A, member + c, buf[c] - '0', 0);
                func_800550F4_main(D_80108DE0_duelresult2->unk_0A, member + c, 1);
            }
        }
    }
    func_80054904_main(D_80108DE4_duelresult2->unk_0A, 0, D_80108C38_duelresult2 * 44 + 0x92, 0x64);
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108CC8_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106F7C_duelresult2);
#endif




/* Builds the record page: title, game-length badge, the two players' badge, portrait and name,
   the scroll arrows, the 10 row labels, the 64 digit sprites, the row cursor, and the guide
   (character model) with its texture-animation frames D_80108E28. */
void func_80107454_duelresult2(void) {
    s32 placeFiles[2] = { 0x13004A, 0x130047 };
    s32 portraitFiles[8] = { 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
    s32 nameFiles[8] = { 0x1301D5, 0x1301D6, 0x1301D7, 0x1301D8, 0x1301D9, 0x1301DA, 0x1301DB, 0x1301DC };
    s32 lengthFiles[2] = { 0x130072, 0x130074 };
    s32 rowFiles[11] = { 0x13005A, 0x13004E, 0x13004F, 0x130050, 0x13005B, 0x13005C,
                         0x13005D, 0x13005E, 0x13005F, 0x130060, 0x130061 }; /* [10]: row 9 on board 5 */
    void *data;
    s32 file;
    s32 i;

    D_80108DC4_duelresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x13006F);
    *D_80108DC4_duelresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80108DC4_duelresult2->unk_0A, 0, D_80108DC4_duelresult2->unk_0C[0], 0);
    HuSprPriSet(D_80108DC4_duelresult2->unk_0A, 0, 0x6E);
    HuSprAttrSet(D_80108DC4_duelresult2->unk_0A, 0, 0x4000);
    func_80054904_main(D_80108DC4_duelresult2->unk_0A, 0, 0x4A, 0x27);
    D_80108DC8_duelresult2 = func_800F4528_name_81(2, 0);
    data = DataRead(0x13004B);
    *D_80108DC8_duelresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80108DC8_duelresult2->unk_0A, 0, D_80108DC8_duelresult2->unk_0C[0], 0);
    HuSprPriSet(D_80108DC8_duelresult2->unk_0A, 0, 0x64);
    HuSprAttrSet(D_80108DC8_duelresult2->unk_0A, 0, 0x4000);
    func_80054904_main(D_80108DC8_duelresult2->unk_0A, 0, 0xD2, 0x24);
    if (GwSystem.playMode & 4) {
        file = 0x13007C;
    } else if (GwSystem.total_turns == 20) {
        file = lengthFiles[0];
    } else {
        file = lengthFiles[1];
    }
    data = DataRead(file);
    D_80108DC8_duelresult2->unk_0C[1] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80108DC8_duelresult2->unk_0A, 1, D_80108DC8_duelresult2->unk_0C[1], 0);
    HuSprPriSet(D_80108DC8_duelresult2->unk_0A, 1, 0x63);
    HuSprAttrSet(D_80108DC8_duelresult2->unk_0A, 1, 0x4000);
    func_80054904_main(D_80108DC8_duelresult2->unk_0A, 1, 0xD2, 0x24);
    D_80108DCC_duelresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x13004C);
    *D_80108DCC_duelresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80108DCC_duelresult2->unk_0A, 0, D_80108DCC_duelresult2->unk_0C[0], 0);
    HuSprPriSet(D_80108DCC_duelresult2->unk_0A, 0, 0x63);
    HuSprAttrSet(D_80108DCC_duelresult2->unk_0A, 0, 0x4000);
    func_80054904_main(D_80108DCC_duelresult2->unk_0A, 0, 0xDA, 0x49);
    for (i = 0; i < 2; i++) {
        D_80108DD0_duelresult2[i] = func_800F4528_name_81(10, 2);
        data = DataRead(placeFiles[i]);
        D_80108DD0_duelresult2[i]->unk_0C[1] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80108DD0_duelresult2[i]->unk_0A, 1, D_80108DD0_duelresult2[i]->unk_0C[1], 0);
        HuSprPriSet(D_80108DD0_duelresult2[i]->unk_0A, 1, 0x62);
        HuSprAttrSet(D_80108DD0_duelresult2[i]->unk_0A, 1, 0x4000);
        func_80054904_main(D_80108DD0_duelresult2[i]->unk_0A, 1, 0xAC, 0);
        data = DataRead(portraitFiles[GwPlayer[i].chr]);
        D_80108DD0_duelresult2[i]->unk_0C[2] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80108DD0_duelresult2[i]->unk_0A, 2, D_80108DD0_duelresult2[i]->unk_0C[2], 0);
        HuSprPriSet(D_80108DD0_duelresult2[i]->unk_0A, 2, 0x61);
        HuSprAttrSet(D_80108DD0_duelresult2[i]->unk_0A, 2, 0x4000);
        func_80054904_main(D_80108DD0_duelresult2[i]->unk_0A, 2, 0x24, 1);
        data = DataRead(nameFiles[GwPlayer[i].chr]);
        D_80108DD0_duelresult2[i]->unk_0C[3] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80108DD0_duelresult2[i]->unk_0A, 3, D_80108DD0_duelresult2[i]->unk_0C[3], 0);
        HuSprPriSet(D_80108DD0_duelresult2[i]->unk_0A, 3, 0x60);
        HuSprAttrSet(D_80108DD0_duelresult2[i]->unk_0A, 3, 0x4000);
        func_80054904_main(D_80108DD0_duelresult2[i]->unk_0A, 3, 0x4D, 1);
    }
    for (i = 0; i < 2; i++) {
        func_80054904_main(D_80108DD0_duelresult2[i]->unk_0A, 0, 0, i * 26 + 0x63);
    }
    D_80108DD8_duelresult2 = func_800F4528_name_81(2, 0);
    for (i = 0; i < 2; i++) {
        data = DataRead(0x13002E);
        D_80108DD8_duelresult2->unk_0C[i] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80108DD8_duelresult2->unk_0A, i, D_80108DD8_duelresult2->unk_0C[i], 0);
        HuSprPriSet(D_80108DD8_duelresult2->unk_0A, i, 0x5A);
        HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, i, 0x4000);
        func_80054904_main(D_80108DD8_duelresult2->unk_0A, i, i * 154 + 0x85, 0xA1);
    }
    HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, 0, 1);
    D_80108DDC_duelresult2 = func_800F4528_name_81(10, 0);
    for (i = 0; i < 10; i++) {
        if (i == 9 && GwSystem.current_board_index == 5) {
            data = DataRead(rowFiles[10]);
        } else {
            data = DataRead(rowFiles[i]);
        }
        D_80108DDC_duelresult2->unk_0C[i] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80108DDC_duelresult2->unk_0A, i, D_80108DDC_duelresult2->unk_0C[i], 0);
        HuSprPriSet(D_80108DDC_duelresult2->unk_0A, i, 0x50);
        HuSprAttrSet(D_80108DDC_duelresult2->unk_0A, i, 0xC000);
    }
    D_80108DE0_duelresult2 = func_800F4528_name_81(64, 0);
    data = DataRead(0x130077);
    *D_80108DE0_duelresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x130078);
    D_80108DE0_duelresult2->unk_0C[1] = func_80055810_main(data);
    DataClose(data);
    for (i = 0; i < 64; i++) {
        func_80055024_main(D_80108DE0_duelresult2->unk_0A, i, *D_80108DE0_duelresult2->unk_0C, 0);
        HuSprPriSet(D_80108DE0_duelresult2->unk_0A, i, 0x46);
        HuSprAttrSet(D_80108DE0_duelresult2->unk_0A, i, 0xC000);
    }
    D_80108DE4_duelresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x13007B);
    *D_80108DE4_duelresult2->unk_0C = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80108DE4_duelresult2->unk_0A, 0, D_80108DE4_duelresult2->unk_0C[0], 0);
    HuSprPriSet(D_80108DE4_duelresult2->unk_0A, 0, 0x3C);
    HuSprAttrSet(D_80108DE4_duelresult2->unk_0A, 0, 0x4000);
    D_80108DC0_duelresult2 = func_800E4B64_name_81(0, 8);
    func_800E4EAC_name_81(D_80108DC0_duelresult2, 0x69, 8);
    HuVecCopyXYZ(&D_80108DC0_duelresult2->obj->scale, 0.1f, 0.1f, 0.1f);
    func_8005BB18_main(D_80108DC0_duelresult2->amount, 1.0f, 1.0f);
    func_8005B63C_main(D_80108DC0_duelresult2->amount, 0x4000, 0x4000);
    func_8005C060_main(D_80108DC0_duelresult2->amount, 2, 0xFF, 0x60, 0x60);
    func_8005C060_main(D_80108DC0_duelresult2->amount, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(D_80108DC0_duelresult2->amount, 6, 0x40, 0xFF, 0xFF);
    func_800E4EAC_name_81(D_80108DC0_duelresult2, 0x71, 8);
    D_80108E28_duelresult2[0] = func_80105A8C_duelresult2(D_80108DC0_duelresult2->obj->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    D_80108E28_duelresult2[1] = func_80105C68_duelresult2(0xA007F);
    D_80108E28_duelresult2[2] = func_80105C68_duelresult2(0xA0080);
    D_80108E28_duelresult2[3] = func_80105C68_duelresult2(0xA0081);
    D_80108E28_duelresult2[4] = func_80105C68_duelresult2(0xA0082);
    D_80108E28_duelresult2[5] = func_80105C68_duelresult2(0xA0083);
    D_80108E28_duelresult2[6] = func_80105C68_duelresult2(0xA0084);
    func_80105B98_duelresult2(D_80108DC0_duelresult2->obj->omObj1->model[0], D_80108E28_duelresult2[0]);
}

void func_80107FEC_duelresult2(void) {
    s32 i;

    func_800F4584_name_81(D_80108DC4_duelresult2);
    func_800F4584_name_81(D_80108DC8_duelresult2);
    func_800F4584_name_81(D_80108DCC_duelresult2);
    for (i = 0; i < 2; i++) {
        func_800F4584_name_81(D_80108DD0_duelresult2[i]);
    }
    func_800F4584_name_81(D_80108DD8_duelresult2);
    func_800F4584_name_81(D_80108DDC_duelresult2);
    func_800F4584_name_81(D_80108DE0_duelresult2);
    func_800F4584_name_81(D_80108DE4_duelresult2);
    func_800E4E64_name_81(D_80108DC0_duelresult2);
}

/* hides the record page */
void func_8010809C_duelresult2(void) {
    s32 j;
    s32 i;

    HuSprAttrSet(D_80108DC4_duelresult2->unk_0A, 0, 0x8000);
    HuSprAttrSet(D_80108DC8_duelresult2->unk_0A, 0, 0x8000);
    HuSprAttrSet(D_80108DC8_duelresult2->unk_0A, 1, 0x8000);
    HuSprAttrSet(D_80108DCC_duelresult2->unk_0A, 0, 0x8000);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 10; j++) {
            HuSprAttrSet(D_80108DD0_duelresult2[i]->unk_0A, j, 0x8000);
        }
    }
    for (j = 0; j < 2; j++) {
        HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, j, 0x8000);
    }
    for (j = 0; j < 10; j++) {
        HuSprAttrSet(D_80108DDC_duelresult2->unk_0A, j, 0x8000);
    }
    for (j = 0; j < 64; j++) {
        HuSprAttrSet(D_80108DE0_duelresult2->unk_0A, j, 0x8000);
    }
    HuSprAttrSet(D_80108DE4_duelresult2->unk_0A, 0, 0x8000);
    func_800D8F0C_name_81(D_80108DC0_duelresult2->obj);
    func_8005FE90_main(D_80108DC0_duelresult2->amount);
}

/* shows the record page */
void func_80108240_duelresult2(void) {
    s32 j;
    s32 i;

    HuSprAttrReset(D_80108DC4_duelresult2->unk_0A, 0, 0x8000);
    HuSprAttrReset(D_80108DC8_duelresult2->unk_0A, 0, 0x8000);
    HuSprAttrReset(D_80108DC8_duelresult2->unk_0A, 1, 0x8000);
    HuSprAttrReset(D_80108DCC_duelresult2->unk_0A, 0, 0x8000);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 10; j++) {
            HuSprAttrReset(D_80108DD0_duelresult2[i]->unk_0A, j, 0x8000);
        }
    }
    for (j = 0; j < 2; j++) {
        HuSprAttrReset(D_80108DD8_duelresult2->unk_0A, j, 0x8000);
    }
    func_80106F7C_duelresult2();
    HuSprAttrReset(D_80108DE4_duelresult2->unk_0A, 0, 0x8000);
    func_800D8E88_name_81(D_80108DC0_duelresult2->obj);
    func_8005FFA8_main(D_80108DC0_duelresult2->amount);
    if (D_80108C34_duelresult2 == 0 && D_80108C38_duelresult2 == 0) {
        HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, 0, 0x8000);
    }
    if (D_80108C34_duelresult2 == 6 && D_80108C38_duelresult2 == 3) {
        HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, 1, 0x8000);
    }
}

/* the guide explains the record row under the cursor */
void func_801083FC_duelresult2(void) {
    s32 msgs[10] = { 0x2800, 0x2801, 0x2802, 0x2803, 0x2804, 0x2805, 0x2806, 0x2807, 0x2808, 0x2809 };

    func_8005D294_main(D_80108DC0_duelresult2->amount);
    func_8005B43C_main(D_80108DC0_duelresult2->amount, msgs[D_80108C34_duelresult2 + D_80108C38_duelresult2], -1, -1);
    func_80105B98_duelresult2(D_80108DC0_duelresult2->obj->omObj1->model[0],
                              D_80108E28_duelresult2[D_80108DE8_duelresult2[D_80108C34_duelresult2 + D_80108C38_duelresult2]]);
}

/* The results page's main process: builds both pages, then lets either human player open the
   duel record (A), scroll it (D-pad), close it (A) or leave (Start); with only COM players it
   leaves after 60 frames. */
void func_801084F4_duelresult2(void) {
    void *winA;
    void *winB;
    s32 open;
    s32 allCom;
    s32 timer;
    s32 oldRow;
    s32 oldPage;
    s32 i;

    winA = NULL;
    winB = NULL;
    D_80108DB0_duelresult2 = func_800F4528_name_81(6, 0);
    {
        void *data = DataRead(0x13002F);
        *D_80108DB0_duelresult2->unk_0C = func_80055810_main(data);
        DataClose(data);
    }
    for (i = 0; i < 6; i++) {
        func_80055024_main(D_80108DB0_duelresult2->unk_0A, i, *D_80108DB0_duelresult2->unk_0C, 0);
        HuSprPriSet(D_80108DB0_duelresult2->unk_0A, i, 0xC8);
        HuSprAttrSet(D_80108DB0_duelresult2->unk_0A, i, 0x4000);
        func_80054904_main(D_80108DB0_duelresult2->unk_0A, i, i / 2 * 128 + 64, (i & 1) * 128 + 64);
    }
    open = 0;
    func_80105CB0_duelresult2();
    func_80107454_duelresult2();
    func_801083FC_duelresult2();
    func_8010809C_duelresult2();
    func_80106974_duelresult2();
    WipeCreateIn(2, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    allCom = 0;
    for (i = 0; i < 2; i++) {
        if (func_800F37B8_name_81(i) == 0) {
            break;
        }
    }
    if (i == 2) {
        allCom = 1;
    }
    timer = 60;
    while (1) {
        if (allCom) {
            if (--timer == 0) {
                break;
            }
            if (winA == NULL) {
                winA = func_800E172C_name_81(0x16, 0x3C, 0xCF, 1);
            }
            if (winB == NULL) {
                winB = func_800E172C_name_81(0x17, 0xC8, 0xCF, 1);
            }
        } else {
            for (i = 0; i < 2; i++) {
                if (func_800F37B8_name_81(i) != 0) {
                    continue;
                }
                if (!open) {
                    if (winA == NULL) {
                        winA = func_800E172C_name_81(0x16, 0x3C, 0xCF, 1);
                    }
                    if (winB == NULL) {
                        winB = func_800E172C_name_81(0x17, 0xC8, 0xCF, 1);
                    }
                    if (D_800C9520_main[GwPlayer[i].pad] & 0x1000) {
                        open = 1;
                        func_801068BC_duelresult2();
                        func_80108240_duelresult2();
                        if (winA != NULL) {
                            func_800E1854_minigame(winA);
                            winA = NULL;
                        }
                        if (winB != NULL) {
                            func_800E1854_minigame(winB);
                            winB = NULL;
                        }
                    } else if (D_800C9520_main[GwPlayer[i].pad] & 0x8000) {
                        goto exit;
                    }
                } else {
                    oldRow = D_80108C38_duelresult2;
                    oldPage = D_80108C34_duelresult2;
                    if (D_800C9520_main[GwPlayer[i].pad] & 0x1000) {
                        open = 0;
                        func_8010809C_duelresult2();
                        func_80106974_duelresult2();
                    } else if (D_800D0590_main[GwPlayer[i].pad] & 0x100) {
                        if (++D_80108C38_duelresult2 >= 4) {
                            D_80108C38_duelresult2 = 3;
                            if (++D_80108C34_duelresult2 >= 7) {
                                D_80108C34_duelresult2 = 6;
                            }
                        }
                    } else if (D_800D0590_main[GwPlayer[i].pad] & 0x200) {
                        if (--D_80108C38_duelresult2 < 0) {
                            D_80108C38_duelresult2 = 0;
                            if (--D_80108C34_duelresult2 < 0) {
                                D_80108C34_duelresult2 = 0;
                            }
                        }
                    }
                    if (D_80108C38_duelresult2 != oldRow || D_80108C34_duelresult2 != oldPage) {
                        func_801083FC_duelresult2();
                        func_80106F7C_duelresult2();
                    }
                }
            }
            if (open == 1) {
                if (D_80108C34_duelresult2 == 0 && D_80108C38_duelresult2 == 0) {
                    HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, 0, 0x8000);
                } else {
                    HuSprAttrReset(D_80108DD8_duelresult2->unk_0A, 0, 0x8000);
                }
                if (D_80108C34_duelresult2 == 6 && D_80108C38_duelresult2 == 3) {
                    HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, 1, 0x8000);
                } else {
                    HuSprAttrReset(D_80108DD8_duelresult2->unk_0A, 1, 0x8000);
                }
            }
        }
        HuPrcVSleep();
    }
exit:
    if (winA != NULL) {
        func_800E1854_minigame(winA);
    }
    if (winB != NULL) {
        func_800E1854_minigame(winB);
    }
    if (!(GwSystem.playMode & 4) || kakusiMasuItemHis[2] == -1 || (GwPlayer[kakusiMasuItemHis[0]].stat & 1)) {
        HuAudSeqFadeOut(60);
    }
    WipeCreateOut(0, 20);
    HuPrcSleep(20);
    func_80106848_duelresult2();
    func_80107FEC_duelresult2();
    func_800F4584_name_81(D_80108DB0_duelresult2);
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_80108B38_duelresult2(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80108C28_duelresult2();
        func_80108BCC_duelresult2();
        func_8005F524_main();
        omOvlReturnEx(1);
    }
}

void func_80108B7C_duelresult2(omObjData *obj) {
    if (D_800D530C_main != 0) {
        obj->func = func_80108B38_duelresult2;
    }
}

void func_80108BA0_duelresult2(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800F4300_name_81();
}

void func_80108BCC_duelresult2(void) {
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    func_800F4314_name_81();
}

void func_80108BF8_duelresult2(void) {
    Hu3DCamInit(2);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_80108C28_duelresult2(void) {
}

