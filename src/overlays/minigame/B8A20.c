#include "common.h"

#include "overlays/minigame.h"

/* The minigame's control block (the caller's D_80111B50_vine_with_me_Struct, whose
   header layout lacks the gauge values and the extra winner slots). */
typedef struct MgCtrl {
    /* 0x00 */ u8 unk00;    /* state: 0 opening, 1 start, 2 playing, 3 finish, 4 result, 5 done */
    /* 0x01 */ u8 unk01;    /* start/finish message set */
    /* 0x02 */ u8 unk02;    /* timer direction: 0 up, 1 down */
    /* 0x03 */ u8 unk03;    /* 1 timed record, 2 countdown */
    /* 0x04 */ u8 unk04;    /* 1 new record */
    /* 0x05 */ u8 unk05;    /* gauge layout (high nibble) and cell count (low nibble) */
    /* 0x06 */ u8 unk06;    /* result message */
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08[4]; /* gauge values */
    /* 0x18 */ u8 unk18[4];  /* winner player indices */
    /* 0x1C */ s16 unk1C;   /* opening wait */
    /* 0x1E */ u16 unk1E;   /* timer */
    /* 0x20 */ s16 unk20;   /* time limit */
    /* 0x22 */ s16 unk22;   /* finish wait */
    /* 0x24 */ s16 unk24;   /* result wait */
} MgCtrl; /* size 0x26 */

void func_8000B880_main(s16 sprite, f32 r, f32 g, f32 b);
u16 GWMgRecordGet(s16 arg0);

void func_800E9C20_minigame(s16 count, u16 len);
void func_800E9F40_minigame(s16 idx, s32 x, s32 y, s16 dir);
void func_800EA0FC_minigame(s16 idx, f32 min, f32 max);
void func_800EA178_minigame(s16 idx, f32 value);
void func_800EA2A8_minigame(s16 idx);
void func_800EA518_minigame(void);

void func_800E6268_minigame(void);
void func_800E62A8_minigame(void);
s16 func_800E6300_minigame(s32 x, s32 y);
s16 func_800E64B8_minigame(s32 x, s32 y);
void func_800E6670_minigame(s16 idx, s16 time);

extern u32 omovl;
extern u8 D_800CE20A_main;
extern u16 D_800EB910_minigame;
extern u16 D_800EB912_minigame;
extern u16 D_800EB914_minigame;
extern u16 D_800EB916_minigame;
extern u16 D_800EB918_minigame;
extern u16 D_800EB91A_minigame;
extern s32 D_800EB91C_minigame;
extern s32 D_800EB920_minigame;
extern s32 D_800EB924_minigame;
extern s16 D_800EB92A_minigame;
extern s32 D_800EB92C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s16 D_800EB934_minigame;
extern f32 D_800EB938_minigame;
extern s32 D_800EB93C_minigame;
extern s32 D_800EB940_minigame;
extern MgCtrl *D_800EBDE0_minigame;
extern s16 D_800EBDE4_minigame;
extern s16 D_800EBDE6_minigame;
extern s16 D_800EBDE8_minigame[2];


void func_800E5EA0_minigame(D_80111B50_vine_with_me_Struct *arg0) {
    arg0->unk00 = 0;
    D_800EBDE0_minigame = (MgCtrl *)arg0;
    if ((u8)arg0->unk03 == 1) {
        func_800E62A8_minigame();
        func_800E6268_minigame();
        func_800E64B8_minigame(D_800EB91C_minigame, D_800EB920_minigame);
        func_800E6300_minigame(D_800EB91C_minigame, D_800EB920_minigame + 12);
        switch (omovl) {
        case 0x10:
            D_800EB92C_minigame = 1;
            D_800EB92A_minigame = GWMgRecordGet(D_800EB92C_minigame);
            break;
        case 0x23:
            D_800EB92C_minigame = 2;
            D_800EB92A_minigame = GWMgRecordGet(D_800EB92C_minigame);
            break;
        case 0x46:
            D_800EB92C_minigame = D_800CE20A_main + 5;
            D_800EB92A_minigame = GWMgRecordGet(D_800EB92C_minigame);
            break;
        }
        func_800E6670_minigame(1, D_800EB92A_minigame);
        func_800E6670_minigame(0, 0);
    }
    switch (D_800EBDE0_minigame->unk05 & 0xF0) {
    case 0x80:
        func_800E9C20_minigame(4, D_800EBDE0_minigame->unk05 & 0xF);
        func_800EA0FC_minigame(0, 0.0f, 100.0f);
        func_800E9F40_minigame(0, 24, 16, 0);
        func_800EA2A8_minigame(0);
        func_800EA0FC_minigame(1, 0.0f, 100.0f);
        func_800E9F40_minigame(1, 296 - (D_800EBDE0_minigame->unk05 & 0xF) * 10, 16, 0);
        func_800EA2A8_minigame(1);
        func_800EA0FC_minigame(2, 0.0f, 100.0f);
        func_800E9F40_minigame(2, 24, 200, 0);
        func_800EA2A8_minigame(2);
        func_800EA0FC_minigame(3, 0.0f, 100.0f);
        func_800E9F40_minigame(3, 296 - (D_800EBDE0_minigame->unk05 & 0xF) * 10, 200, 0);
        func_800EA2A8_minigame(3);
        break;
    case 0x40:
        func_800E9C20_minigame(2, D_800EBDE0_minigame->unk05 & 0xF);
        func_800EA0FC_minigame(0, 0.0f, 100.0f);
        func_800E9F40_minigame(0, 24, 16, 0);
        func_800EA2A8_minigame(0);
        func_800EA0FC_minigame(1, 0.0f, 100.0f);
        func_800E9F40_minigame(1, 296 - (D_800EBDE0_minigame->unk05 & 0xF) * 10, 16, 0);
        func_800EA2A8_minigame(1);
        break;
    case 0x20:
        func_800E9C20_minigame(2, D_800EBDE0_minigame->unk05 & 0xF);
        func_800EA0FC_minigame(0, 0.0f, 100.0f);
        func_800E9F40_minigame(0, 296 - (D_800EBDE0_minigame->unk05 & 0xF) * 10, 16, 0);
        func_800EA2A8_minigame(0);
        func_800EA0FC_minigame(1, 0.0f, 100.0f);
        func_800E9F40_minigame(1, 296 - (D_800EBDE0_minigame->unk05 & 0xF) * 10, 130, 0);
        func_800EA2A8_minigame(1);
        break;
    }
    D_800EB910_minigame = 0;
    D_800EB912_minigame = 0;
    D_800EB914_minigame = 0;
    D_800EB916_minigame = 0;
    D_800EB918_minigame = 0;
    D_800EB91A_minigame = 0;
    D_800EB934_minigame = 0;
}

void func_800E6248_minigame(s32 x, s32 y) {
    D_800EB91C_minigame = x;
    D_800EB920_minigame = y;
}

void func_800E625C_minigame(s32 arg0) {
    D_800EB924_minigame = arg0;
}

void func_800E6268_minigame(void) {
    void *data;

    data = DataRead(0x31);
    D_800EBDE4_minigame = func_80055810_main(data);
    DataClose(data);
}

void func_800E62A8_minigame(void) {
    void *data;

    data = DataRead(0x31);
    D_800EBDE6_minigame = func_80055810_main(data);
    DataClose(data);
    func_8000B880_main(D_800EBDE6_minigame, 0.0f, 1.0f, 0.0f);
}

s16 func_800E6300_minigame(s32 x, s32 y) {
    s16 i;
    s16 px;
    s16 grp;

    grp = D_800EBDE8_minigame[0] = HuSprGrpCreate(7, 5);
    func_80055024_main(grp, 0, D_800EBDE4_minigame, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x8000);
    func_80054904_main(grp, 0, x - 0x10, y);
    HuSprPriSet(grp, 0, (u16)D_800EB924_minigame);
    px = 4;
    for (i = 1; i < 7; i++) {
        HuSprPriSet(grp, i, (u16)D_800EB924_minigame);
        func_80055024_main(grp, i, D_800EBDE4_minigame, 0);
        func_80054904_main(grp, i, px, 0);
        HuSprAttrReset(grp, i, 0xFFFF);
        HuSprAttrSet(grp, i, 0x8000);
        if (i == 3) {
            px += 8;
        } else {
            px += 12;
        }
        func_800554C4_main(grp, i, 0);
    }
    HuSprAttrReset(grp, 2, 0x8000);
    return grp;
}

s16 func_800E64B8_minigame(s32 x, s32 y) {
    s16 i;
    s16 px;
    s16 grp;

    grp = D_800EBDE8_minigame[1] = HuSprGrpCreate(7, 5);
    func_80055024_main(grp, 0, D_800EBDE6_minigame, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x8000);
    func_80054904_main(grp, 0, x - 0x10, y);
    HuSprPriSet(grp, 0, (u16)D_800EB924_minigame);
    px = 4;
    for (i = 1; i < 7; i++) {
        HuSprPriSet(grp, i, (u16)D_800EB924_minigame);
        func_80055024_main(grp, i, D_800EBDE6_minigame, 0);
        func_80054904_main(grp, i, px, 0);
        HuSprAttrReset(grp, i, 0xFFFF);
        HuSprAttrSet(grp, i, 0x8000);
        if (i == 3) {
            px += 8;
        } else {
            px += 12;
        }
        func_800554C4_main(grp, i, 0);
    }
    HuSprAttrReset(grp, 2, 0x8000);
    return grp;
}

void func_800E6670_minigame(s16 idx, s16 time) {
    s16 g;
    s16 d;
    s16 sec;
    s16 cs;

    g = D_800EBDE8_minigame[idx];
    HuSprAttrReset(g, 0, 0x8000);
    d = time / 3600;
    func_80055140_main(g, 0, d, 0);
    func_800550F4_main(g, 0, 1);
    time -= d * 3600;
    HuSprAttrReset(g, 1, 0x8000);
    func_80055140_main(g, 1, 10, 0);
    func_800550F4_main(g, 1, 1);
    HuSprAttrReset(g, 2, 0x8000);
    d = time / 600;
    func_80055140_main(g, 2, d, 0);
    func_800550F4_main(g, 2, 1);
    time -= d * 600;
    sec = time / 60;
    HuSprAttrReset(g, 3, 0x8000);
    func_80055140_main(g, 3, sec, 0);
    func_800550F4_main(g, 3, 1);
    cs = time * 100 / 60 - sec * 100;
    HuSprAttrReset(g, 4, 0x8000);
    func_80055140_main(g, 4, 11, 0);
    func_800550F4_main(g, 4, 1);
    HuSprAttrReset(g, 5, 0x8000);
    func_80055140_main(g, 5, cs / 10, 0);
    func_800550F4_main(g, 5, 1);
    cs %= 10;
    HuSprAttrReset(g, 6, 0x8000);
    func_80055140_main(g, 6, cs, 0);
    func_800550F4_main(g, 6, 1);
}

void func_800E6968_minigame(s16 idx, s16 time) {
    s16 g;
    s16 d;
    s16 sec;
    s16 cs;

    g = D_800EBDE8_minigame[idx];
    if ((D_800EB938_minigame += 10.0f) > 180.0f) {
        D_800EB938_minigame = 180.0f;
    }
    HuSprScaleSet(g, 0, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(g, 1, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(g, 2, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(g, 3, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(g, 4, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(g, 5, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(g, 6, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprAttrReset(g, 0, 0x8000);
    d = time / 3600;
    func_80055140_main(g, 0, d, 0);
    func_800550F4_main(g, 0, 1);
    time -= d * 3600;
    HuSprAttrReset(g, 1, 0x8000);
    func_80055140_main(g, 1, 10, 0);
    func_800550F4_main(g, 1, 1);
    HuSprAttrReset(g, 2, 0x8000);
    d = time / 600;
    func_80055140_main(g, 2, d, 0);
    func_800550F4_main(g, 2, 1);
    time -= d * 600;
    sec = time / 60;
    HuSprAttrReset(g, 3, 0x8000);
    func_80055140_main(g, 3, sec, 0);
    func_800550F4_main(g, 3, 1);
    cs = time * 100 / 60 - sec * 100;
    HuSprAttrReset(g, 4, 0x8000);
    func_80055140_main(g, 4, 11, 0);
    func_800550F4_main(g, 4, 1);
    HuSprAttrReset(g, 5, 0x8000);
    func_80055140_main(g, 5, cs / 10, 0);
    func_800550F4_main(g, 5, 1);
    cs %= 10;
    HuSprAttrReset(g, 6, 0x8000);
    func_80055140_main(g, 6, cs, 0);
    func_800550F4_main(g, 6, 1);
}

void func_800E6E4C_minigame(s16 arg0) {
    D_800EBDE0_minigame->unk1C = arg0;
}

void func_800E6E5C_minigame(s16 arg0) {
    D_800EBDE0_minigame->unk1E = arg0;
}

void func_800E6E6C_minigame(s16 arg0) {
    D_800EBDE0_minigame->unk24 = arg0;
}

void func_800E6E7C_minigame(s8 arg0) {
    D_800EBDE0_minigame->unk01 = arg0;
}

u8 func_800E6E8C_minigame(void) {
    return D_800EBDE0_minigame->unk00;
}

u16 func_800E6E9C_minigame(void) {
    u16 v;

    switch (D_800EBDE0_minigame->unk00) {
    case 0:
        v = D_800EB910_minigame;
        break;
    case 1:
        v = D_800EB912_minigame;
        break;
    case 2:
        v = D_800EB914_minigame;
        break;
    case 3:
        v = D_800EB916_minigame;
        break;
    case 4:
    default:
        v = D_800EB918_minigame;
        break;
    }
    return v;
}

void func_800E6F0C_minigame(s8 arg0) {
    D_800EBDE0_minigame->unk00 = arg0;
}

void func_800E6F1C_minigame(void) {
    D_800EBDE0_minigame->unk00++;
}

void func_800E6F34_minigame(s32 arg0) {
    D_800EB91A_minigame = arg0;
}

// Matches once ~/repos/mp3-wt/mgD.header.patch is applied (and needs it to compile): the
// headers declare this function void (retail returns the state) and GWMgRecordSet's
// second parameter s16 (retail passes it as u16).
#ifdef NON_MATCHING
u8 func_800E6F40_minigame(void) {
    char *stateNames[4] = { "OPENING", "PLAYING", "DIRECTION", "ENDING" };
    s16 mes;

    if (D_800D530C_main == 1) {
        func_800E6F0C_minigame(5);
    }
    func_800EA518_minigame();
    switch (D_800EBDE0_minigame->unk00) {
    case 0:
        if (WipeStatGet() == 0) {
            if (D_800EBDE0_minigame->unk1C == 0) {
                func_800E6F0C_minigame(1);
            } else if (D_800EBDE0_minigame->unk1C != -1) {
                D_800EBDE0_minigame->unk1C--;
            }
            D_800EB910_minigame++;
        }
        break;
    case 1:
        if (D_800EB912_minigame == 0) {
            switch (D_800EBDE0_minigame->unk01) {
            case 0:
                mes = 3;
                break;
            case 1:
                mes = 5;
                break;
            case 2:
                mes = 4;
                break;
            case 3:
                mes = 8;
                break;
            case 4:
                mes = 6;
                break;
            case 6:
                mes = 9;
                break;
            case 5:
            case 7:
                mes = 7;
                break;
            }
            GMesCreate(mes);
        } else if (D_800EB912_minigame == 75.0) {
            func_800E6F0C_minigame(2);
        }
        if (D_800EB932_minigame == D_800EB912_minigame && D_800EB930_minigame != -1) {
            HuAudSeqPlay(D_800EB930_minigame);
        }
        D_800EB912_minigame++;
        break;
    case 2:
        if (D_800EB914_minigame == 0 && D_800EBDE0_minigame->unk03 == 2) {
            GMesCreate(0x1A, 30, 160, 24);
        }
        switch (D_800EBDE0_minigame->unk03) {
        case 0:
            break;
        case 1:
            func_800E6670_minigame(0, D_800EB914_minigame * 2);
            if (D_800EBDE0_minigame->unk20 == D_800EB914_minigame) {
                func_800E6F0C_minigame(3);
            }
            break;
        case 2:
            func_8003F578_main((s16)D_800EBDE0_minigame->unk1E / 30 + 1);
            break;
        }
        if (D_800EBDE0_minigame->unk20 != -1) {
            if (D_800EBDE0_minigame->unk20 - 900 == D_800EB914_minigame) {
                GMesCreate(0x1A, 30, 160, 24);
                D_800EB93C_minigame = 1;
            } else if (D_800EBDE0_minigame->unk20 - 900 < D_800EB914_minigame) {
                func_8003F578_main((D_800EBDE0_minigame->unk20 - D_800EB914_minigame) / 30 + 1);
            }
        }
        if ((s16)D_800EBDE0_minigame->unk1E != -1) {
            switch (D_800EBDE0_minigame->unk02) {
            case 0:
                if ((s16)D_800EBDE0_minigame->unk1E >= D_800EBDE0_minigame->unk20) {
                    func_800E6F0C_minigame(3);
                } else {
                    D_800EBDE0_minigame->unk1E++;
                }
                break;
            case 1:
                if ((s16)D_800EBDE0_minigame->unk1E == 0) {
                    func_800E6F0C_minigame(3);
                    func_8003F578_main(0);
                } else {
                    D_800EBDE0_minigame->unk1E--;
                }
                break;
            case 2:
                break;
            }
        }
        D_800EB914_minigame++;
        break;
    case 3:
        if (D_800EB916_minigame == 0) {
            D_800EB914_minigame--;
            if (D_800EB914_minigame * 2 < D_800EB92A_minigame) {
                D_800EBDE0_minigame->unk04 = 1;
                GWMgRecordSet(D_800EB92C_minigame, D_800EB914_minigame * 2);
                D_800EBDE0_minigame->unk24 = D_800EBDE0_minigame->unk24 + 75.0;
                D_800EB940_minigame = 1;
            }
            if (D_800EBDE0_minigame->unk03 == 2 || D_800EB93C_minigame != 0) {
                func_8003F5C0_main();
            }
            switch (D_800EBDE0_minigame->unk01) {
            case 0:
                mes = 0xE;
                break;
            case 1:
                mes = 0x10;
                break;
            case 2:
                mes = 0xF;
                break;
            case 3:
                mes = 0x13;
                break;
            case 4:
                mes = 0x11;
                break;
            case 6:
                mes = 0x14;
                break;
            case 5:
            case 7:
                mes = 0x12;
                break;
            }
            GMesCreate(mes);
            HuAudSeqFadeOut(120);
        }
        if (D_800EBDE0_minigame->unk22 == 0) {
            func_800E6F0C_minigame(4);
        } else if (D_800EBDE0_minigame->unk22 != -1) {
            D_800EBDE0_minigame->unk22--;
        }
        D_800EB916_minigame++;
        break;
    case 4:
        D_800EB934_minigame = 0;
        if (D_800EB918_minigame == 0 && D_800EBDE0_minigame->unk04 == 1) {
            D_800EB91A_minigame = 75;
            GMesCreate(0x1B);
        }
        if (D_800EB918_minigame == D_800EB91A_minigame) {
            switch (D_800EBDE0_minigame->unk06) {
            case 0:
                GMesCreate(0x16, GwPlayer[D_800EBDE0_minigame->unk18[0]].chr);
                if (D_800EBDE0_minigame->unk04 == 1) {
                    HuAudSeqPlay(0x6A);
                } else if (D_800EBDE0_minigame->unk01 == 4) {
                    HuAudSeqPlay(0x67);
                } else {
                    HuAudSeqPlay(0x65);
                }
                break;
            case 1:
                GMesCreate(0x1E, GwPlayer[D_800EBDE0_minigame->unk18[0]].chr,
                           GwPlayer[D_800EBDE0_minigame->unk18[1]].chr);
                if (D_800EBDE0_minigame->unk04 == 1) {
                    HuAudSeqPlay(0x6A);
                } else {
                    HuAudSeqPlay(0x66);
                }
                break;
            case 2:
                GMesCreate(0x22, GwPlayer[D_800EBDE0_minigame->unk18[0]].chr,
                           GwPlayer[D_800EBDE0_minigame->unk18[1]].chr,
                           GwPlayer[D_800EBDE0_minigame->unk18[2]].chr);
                HuAudSeqPlay(0x66);
                break;
            case 3:
                GMesCreate(0x23, GwPlayer[D_800EBDE0_minigame->unk18[0]].chr,
                           GwPlayer[D_800EBDE0_minigame->unk18[1]].chr,
                           GwPlayer[D_800EBDE0_minigame->unk18[2]].chr,
                           GwPlayer[D_800EBDE0_minigame->unk18[3]].chr);
                HuAudSeqPlay(0x66);
                break;
            case 4:
                GMesCreate(0x20);
                HuAudSeqPlay(0x6C);
                break;
            case 5:
                GMesCreate(0x24);
                HuAudSeqPlay(0x68);
                break;
            case 6:
                GMesCreate(0x25);
                HuAudSeqPlay(0x69);
                break;
            case 7:
                GMesCreate(0x1D);
                HuAudSeqPlay(0x6B);
                break;
            case 8:
                GMesCreate(0x17);
                break;
            case 9:
                break;
            }
            D_800EB934_minigame = 1;
        }
        if (D_800EBDE0_minigame->unk24 == 0) {
            func_800E6F0C_minigame(5);
        } else if (D_800EBDE0_minigame->unk24 != -1) {
            D_800EBDE0_minigame->unk24--;
        }
        if (D_800EB940_minigame != 0) {
            func_800E6968_minigame(1, D_800EB914_minigame * 2);
        }
        D_800EB918_minigame++;
        break;
    case 5:
        break;
    }
    switch (D_800EBDE0_minigame->unk05 & 0xF0) {
    case 0x80:
        func_800EA178_minigame(2, D_800EBDE0_minigame->unk08[2]);
        func_800EA178_minigame(3, D_800EBDE0_minigame->unk08[3]);
    case 0x40:
    case 0x20:
        func_800EA178_minigame(0, D_800EBDE0_minigame->unk08[0]);
        func_800EA178_minigame(1, D_800EBDE0_minigame->unk08[1]);
        break;
    }
    return D_800EBDE0_minigame->unk00;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBCF4_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBCFC_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBD04_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBD10_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBD18_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B8A20", func_800E6F40_minigame);
#endif
