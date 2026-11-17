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
s32 func_800E1854_minigame(s32 id);

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
void func_8005FE90_main(s16);
void func_8005FFA8_main(s16);
void func_8005D294_main(s16);
void func_8005B43C_main(s16, s32, s32, s32);

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

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106A2C_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108CC8_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106F7C_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D08_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D28_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D48_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80107454_duelresult2);

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

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_8010809C_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108240_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801083FC_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801084F4_duelresult2);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D80_duelresult2);
