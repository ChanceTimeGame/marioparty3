#include "common.h"

#include "overlays/minigame.h"

void func_8000B880_main(s16 sprite, f32 r, f32 g, f32 b);
u16 GWMgRecordGet(s16 arg0);

void func_800E9C20_minigame(s16 count, u16 len);
void func_800E9F40_minigame(s16 idx, s32 x, s32 y, s16 dir);
void func_800EA0FC_minigame(s16 idx, f32 min, f32 max);
void func_800EA2A8_minigame(s16 idx);

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
extern s16 D_800EB91A_minigame;
extern s32 D_800EB91C_minigame;
extern s32 D_800EB920_minigame;
extern s32 D_800EB924_minigame;
extern s16 D_800EB92A_minigame;
extern s32 D_800EB92C_minigame;
extern s16 D_800EB934_minigame;
extern f32 D_800EB938_minigame;
extern D_80111B50_vine_with_me_Struct *D_800EBDE0_minigame;
extern s16 D_800EBDE4_minigame;
extern s16 D_800EBDE6_minigame;
extern s16 D_800EBDE8_minigame[2];


void func_800E5EA0_minigame(D_80111B50_vine_with_me_Struct *arg0) {
    arg0->unk00 = 0;
    D_800EBDE0_minigame = arg0;
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
    switch ((u8)D_800EBDE0_minigame->unk05 & 0xF0) {
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

    switch ((u8)D_800EBDE0_minigame->unk00) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBCF4_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBCFC_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBD04_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBD10_minigame);

INCLUDE_RODATA("asm/nonmatchings/overlays/minigame/B8A20", D_800EBD18_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B8A20", func_800E6F40_minigame);
