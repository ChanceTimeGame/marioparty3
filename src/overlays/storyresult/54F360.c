#include "common.h"
#include "../ovl_81_name/ovl_81.h"
#include "mallocblock.h"

/* Overlay 0x7D `storyresult`: the story mode results screen. Same framework as msetup (501C00.c). */

/* Model definition table entry (0x28 stride; msetup's MsModelDef). */
typedef struct SrModelDef {
    /* 0x00 */ s32 unk0; /* func_8000B108_main arg0 */
    /* 0x04 */ s32 unk4; /* func_8000B108_main arg1 */
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA; /* func_8001C814_main arg2 */
    /* 0x0C */ s32 unkC; /* 0: none, 1: pos/rot, 2: pos*5 / rot */
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
} SrModelDef; /* size = 0x28 */

typedef struct SrModelSlot {
    /* 0x00 */ s16 model;
    /* 0x02 */ s16 unk2; /* HmfModelData[model].unk02 */
} SrModelSlot; /* size = 0x4 */

/* Camera key (msetup's MsCamKey). */
typedef struct SrCamKey {
    /* 0x00 */ Vec rot;    /* CRot */
    /* 0x0C */ Vec center; /* Center */
    /* 0x18 */ f32 zoom;   /* CZoom */
    /* 0x1C */ f32 fov;
    /* 0x20 */ f32 unk20;
} SrCamKey; /* size = 0x24 */

typedef void (*SrCamFunc)(s16, s16, s16);

void func_80105C30_storyresult(omObjData *obj);
void func_80105CF8_storyresult(omObjData *obj);
void func_80105DEC_storyresult(SrModelDef *def, s16 model);
void func_80105EA0_storyresult(SrModelDef *defs, SrModelSlot *slots, s32 count);
u32 func_80105F7C_storyresult(u32 seed);
u32 func_80106050_storyresult(void);
u32 func_80106078_storyresult(u32 max);
void func_80106190_storyresult(void);
void func_80106754_storyresult(void);
void func_80106780_storyresult(SrCamKey *keys, f32 speed, SrCamFunc func);
void func_80106C84_storyresult(void);
s16 func_80106E48_storyresult(void);
void func_80107204_storyresult(void);
void func_8010822C_storyresult(void);
void func_801083A4_storyresult(void);
void func_800E989C_minigame(void);
f32 func_80018ACC_main(f32 *y, f32 *x, f32 t);

extern u16 omovlstat;
extern f32 D_800CB890_main;
extern f32 D_800CE17C_main[];
extern f32 D_800D5210_main;
extern f32 D_8010A918_storyresult; /* current fov */
extern s8 D_8010A91C_storyresult;  /* fixed camera */
extern u32 D_8010A920_storyresult; /* random seed */
extern s16 D_8010ABE2_storyresult; /* exit mode */
extern Vec D_8010AC00_storyresult; /* fixed camera target */
extern Vec D_8010AC0C_storyresult; /* CRot copy (splat also labels .y/.z as D_8010AC10/D_8010AC14) */
extern Vec D_8010AC18_storyresult; /* fixed camera eye */
extern f32 D_8010AC24_storyresult; /* near plane */
extern f32 D_8010AC2C_storyresult; /* far plane */
extern s16 D_8010AC30_storyresult; /* next overlay event */
extern s16 D_8010ABE0_storyresult; /* first controller (D_8010ABE8_storyresult.pad[0]) */

/* .bss 0x8010ABE8 (0x18): controller order; splat also labels D_8010ABEC/F0/F4/FA. */
typedef struct SrPadWork {
    /* 0x00 */ u8 pad[4];  /* connected controllers first, 0xFF-filled by the free ports */
    /* 0x04 */ u8 unk4[4];
    /* 0x08 */ u8 unk8[4];
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;   /* connected controller count */
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
} SrPadWork; /* size = 0x18 */
extern SrPadWork D_8010ABE8_storyresult;
extern u8 D_8010A924_storyresult[]; /* per GwStory.unk0 (chapter): 0 party board, 1 duel board, 2 two-player game, other none */
extern s16 kakusiMasuItemHis[];
extern u8 D_800CE20A_main;
s32 func_80050614_main(s32 write);
s16 func_80106FF0_storyresult(void);
void func_80107030_storyresult(void);
s16 func_801070D8_storyresult(void);
void func_80107140_storyresult(void);
void func_80107920_storyresult(void);
Process *func_8010818C_storyresult(s16 *res, s16 slot);
s16 func_8010A370_storyresult(s16 slot);
extern s16 D_8010AC32_storyresult; /* next overlay */

void func_801060D0_storyresult(SrCamKey *key);
extern u16 D_8010A910_storyresult; /* exit delay */
extern s16 D_8010A912_storyresult;
extern s16 D_8010A914_storyresult;
extern SrCamKey D_8010AB9C_storyresult[];
extern s16 D_8010AC28_storyresult;
extern s16 D_8010AC2A_storyresult;

/* Story record board (as minigame BA4B0's MgRec*: one more part, a second record source). */
typedef struct SrPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} SrPos;

typedef struct SrRecInfo {
    /* 0x00 */ s16 mode;  /* 0/1 a slot's or the current story's record */
    /* 0x02 */ s16 slot;
    /* 0x04 */ s16 cmd;   /* 1 show, 2 hide, 3 next page, 4 previous page, 0xFF close */
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
} SrRecInfo; /* size 0xC */

typedef struct SrRecPart {
    /* 0x00 */ SrPos pos;
    /* 0x04 */ s16 spr;
    /* 0x06 */ s16 alpha; /* maximum alpha */
    /* 0x08 */ s16 fade;  /* 1 start, 2 fading */
    /* 0x0A */ s16 shown;
} SrRecPart; /* size 0xC */

typedef struct SrRecWork {
    /* 0x000 */ SrRecInfo *info;
    /* 0x004 */ SrRecPart part[24];
    /* 0x124 */ s16 slot;
    /* 0x126 */ s16 win[6];
    /* 0x132 */ s16 winFade[6];
    /* 0x13E */ s16 grp;
    /* 0x140 */ s16 gfx[4];
    /* 0x148 */ s16 grp2;
    /* 0x14A */ s16 gfx2;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ s16 unk14E;
} SrRecWork; /* size 0x150 */

extern s16 D_800EBAF0_minigame;
extern SrPos D_8010AB34_storyresult[]; /* record number positions */
extern u8 D_8010AB6C_storyresult[];    /* record index order, even pages */
extern u8 D_8010AB74_storyresult[];    /* record index order, odd pages */
extern u8 D_8010AB7C_storyresult[];    /* score per result */
extern u8 D_8010AB84_storyresult[];    /* score per last result */
extern u8 D_8010AB8C_storyresult[];    /* rank thresholds */
extern u8 D_8010AB90_storyresult[];    /* rank per duel coin count */
extern s32 D_8010AB50_storyresult[];   /* record page titles (messages) */
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8005BF70_main(s16 winId, s32 alpha);
extern u16 D_8010A9D8_storyresult[];
extern s32 D_8010A940_storyresult[]; /* per chapter: background */
extern s32 D_8010A974_storyresult[]; /* per chapter: name message */
extern s32 D_8010A9A8_storyresult[]; /* per rank: message */
extern u8 D_8010A9C8_storyresult[];  /* per chapter: D_800CE20A_main for overlay 0x75 */
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BEAC_main(u16 spriteId, s32 arg1, s32 arg2, s32 arg3); /* per character: the flag set when its record is saved */
s16 func_80108D34_storyresult(s16 page, SrRecWork *w);

s16 func_800E905C_minigame(s16 slot);
void func_800E9170_minigame(void);
Process *func_8010832C_storyresult(s16 *res, s16 slot);
void func_801085E8_storyresult(s16 grp, s16 idx, s16 gfx, u16 prio, s32 x, s32 y);
s16 func_801086E4_storyresult(u8 *rec, s16 odd, s16 start, s16 end, SrRecPart *mark, SrRecPart *num, SrRecWork *w);
s16 func_80108884_storyresult(SrRecWork *w);
s16 func_80108AC0_storyresult(SrRecWork *w, u8 last, u8 *rec);
s16 func_80108CB8_storyresult(SrRecWork *w);
s16 func_80108D04_storyresult(SrRecWork *w);
void func_80108F0C_storyresult(void);
Process *func_8010A4A4_storyresult(s16 mode, s16 slot);
s32 func_8010A558_storyresult(Process *prc);
s16 func_8010A5C4_storyresult(s16 player);
s16 func_8010A738_storyresult(s16 player);
s16 func_8010A7B0_storyresult(s16 player);
s16 func_8010A7EC_storyresult(void);

/* Number of results in the saved copy (GwStory.unk_64). */
s16 func_80106FF0_storyresult(void) {
    s16 n;
    s32 i;

    n = (u8)GwStory.unk_64[15] != 0;
    for (i = 0; i < 12; i++) {
        if ((u8)GwStory.unk_64[3 + i] != 0) {
            n++;
        }
    }
    return n;
}

void func_80107030_storyresult(void) {
    s32 i;

    GwStory.unk_64[0] = GwStory.unk0;
    GwStory.unk_64[1] = GwStory.unk1;
    GwStory.unk_64[2] = GwStory.unk2;
    GwStory.unk_64[15] = GwStory.unkF;
    for (i = 0; i < 12; i++) {
        GwStory.unk_64[3 + i] = GwStory.unk3[i];
    }
    _ClearFlag(0x28);
    _SetFlag(0x18);
    if (_CheckFlag(0x20)) {
        _SetFlag(0x29);
    } else {
        _ClearFlag(0x29);
    }
    func_80050614_main(1);
}

#ifdef NON_MATCHING
/* Residue (masked 3): retail loads GwStory.unk1 once into a0 and copies it (move) for the unk58 index; this loads it into v1. */
s16 func_801070D8_storyresult(void) {
    s16 n;
    s32 i;
    s32 c;

    c = GwStory.unk1;
    n = GwStory.unk58[c] != 0;
    for (i = 0; i < 12; i++) {
        if (GwStory.unk10[c][i] != 0) {
            n++;
        }
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_801070D8_storyresult);
#endif

#ifdef NON_MATCHING
/* Residue (masked 5): retail keeps GwStory.unk1 in a2 for all three indexes with register copies. */
void func_80107140_storyresult(void) {
    s32 i;
    s32 c;

    c = GwStory.unk1;
    GwStory.unk58[c] = GwStory.unkF;
    for (i = 0; i < 12; i++) {
        GwStory.unk10[c][i] = GwStory.unk3[i];
    }
    GwStory.unk5E[c] = GwStory.unk2;
    _ClearFlag(0x28);
    if (_CheckFlag(0x20)) {
        _SetFlag(0x29);
    } else {
        _ClearFlag(0x29);
    }
    func_80050614_main(1);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80107140_storyresult);
#endif

#ifdef NON_MATCHING
/* Residue (masked ~10): retail keeps the 160/120 screen centre in saved registers and derives 204/48/187 from them (GCC constant CSE); otherwise identical. */
/* Event 0 process (after a story board or game): records the rank for the chapter, shows it on the
   record board and moves the story on to the next chapter (overlay 0x75), offering a save. */
void func_80107204_storyresult(void) {
    s16 rank;
    SrRecInfo *info;
    u16 spr;
    u16 back;
    u16 frame;
    s16 win;
    s16 a;
    s32 ok;

    rank = func_8010A7EC_storyresult();
    if (GwStory.unk0 < 12) {
        GwStory.unk3[GwStory.unk0] = rank;
    } else {
        GwStory.unkF = rank;
    }
    info = func_8010A4A4_storyresult(2, GwStory.unk1)->user_data;
    HuPrcVSleep();
    D_8010A912_storyresult = 1;
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(D_8010A940_storyresult[GwStory.unk0]);
    func_800E8180_name_81(1000.0f, 10000.0f);
    if (GwStory.unk0 == 12) {
        spr = InitEspriteSlot(func_8000B838_main(0x1D0012), 0, 0);
        func_8000BC48_main(spr, 0x4000);
        func_8000BCC8_main(spr, 0xF001);
        func_8000BBD4_main(spr, 160, 120);
    }
    back = InitEspriteSlot(func_8000B838_main(0x140064), 0, 1);
    func_8000BC48_main(back, 0x4000);
    func_8000BCC8_main(back, 0xF000);
    func_8000BE5C_main(back, 10.0f, 8.0f);
    func_8000BBD4_main(back, 160, 120);
    func_8000BEAC_main(back, 0, 0, 0);
    func_8000BBFC_main(back, 0x40);
    D_800CD280_main = 1;
    frame = InitEspriteSlot(func_8000B838_main(0x150001), 0, 1);
    func_8000BCC8_main(frame, 600);
    func_8000BBD4_main(frame, 160, 204);
    func_8000BBFC_main(frame, 0);
    func_8000BB94_main(frame);
    win = func_8005A968_main(48, 187, 224, 42, 0, 12);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0);
    func_8005BE30_main(win, 1);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0x40, 0x40, 0x40);
    func_8005FBF8_main(win, 0, 0, 0);
    func_8005C02C_main(win, 7);
    func_8005BF70_main(win, 0xFF);
    if (GwStory.unk0 >= 12) {
        HuAudSeqPlay(0x26);
        D_8010A914_storyresult = 0;
    }
    WipeCreateIn(D_8010AC2A_storyresult, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    info->cmd = 1;
    func_8000BB54_main(frame);
    for (a = 0; a < 0x101; a += 36) {
        func_8000BBFC_main(frame, a);
        HuPrcVSleep();
    }
    while (info->cmd != 0) {
        HuPrcVSleep();
    }
    func_8005B6BC_main(win, D_8010A974_storyresult[GwStory.unk0], 0);
    func_8005B6BC_main(win, D_8010A9A8_storyresult[rank], 1);
    func_8005B43C_main(win, 0x6126, -1, -1);
    while (func_8005E0C0_main(win)) {
        HuPrcVSleep();
    }
    if (GwStory.unk0 >= 12) {
        omOvlHisChg(0, 0x7D, 1, 0x4090);
        omovlhisidx++;
        D_8010ABE2_storyresult = 1;
        D_8010AC32_storyresult = 0x75;
        D_8010AC30_storyresult = 0;
        D_800CE20A_main = 0xE;
    } else {
        if (GwStory.unk0 == 11) {
            _SetFlag(0x2F);
            _SetFlag(0x31);
        } else if (GwStory.unk0 == 10) {
            _SetFlag(0x2E);
            _SetFlag(0x30);
        }
        GwStory.unk0++;
        if (GwStory.unk0 >= 13) {
            GwStory.unk0 = 12;
        }
        GwSystem.playMode = (D_8010A924_storyresult[GwStory.unk0] == 1) ? 6 : 5;
        D_8010ABE2_storyresult = 1;
        D_8010AC32_storyresult = 0x75;
        D_8010AC30_storyresult = 0;
        D_800CE20A_main = D_8010A9C8_storyresult[GwStory.unk0];
        while (TRUE) {
            info->cmd = 10;
            do {
                HuPrcVSleep();
            } while (info->cmd != 0);
            func_8005B43C_main(win, 0x6127, -1, -1);
            while (func_8005E0C0_main(win)) {
                HuPrcVSleep();
            }
            if (func_8005E1D8_main(win, 0, 0) == 0) {
                ok = 1;
                if (func_80106FF0_storyresult() != 0) {
                    info->cmd = 11;
                    do {
                        HuPrcVSleep();
                    } while (info->cmd != 0);
                    func_8005B43C_main(win, 0x6129, -1, -1);
                    while (func_8005E0C0_main(win)) {
                        HuPrcVSleep();
                    }
                    if (func_8005E1D8_main(win, 0, 0) != 0) {
                        ok = 0;
                    }
                }
                func_8005D294_main(win);
                if (ok) {
                    func_8005B43C_main(win, 0x612C, -1, -1);
                    HuPrcVSleep();
                    func_80107030_storyresult();
                    info->cmd = 10;
                    func_8005B43C_main(win, 0x612A, -1, -1);
                    while (func_8005E0C0_main(win)) {
                        HuPrcVSleep();
                    }
                    break;
                }
            } else {
                func_8005D294_main(win);
                break;
            }
        }
    }
    D_8010A910_storyresult = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80107204_storyresult);
#endif

#ifdef NON_MATCHING
/* Residue (masked ~20): scheduling only (the arrow sindf product, message ids loaded before the sign extension, delay slots). */
/* Event 1 process: shows the story record board (func_8010A4A4_storyresult mode 1) with page arrows;
   B closes it, then asks whether to save the record (to slot GwStory.unk1) and exits to overlay 0x7C. */
void func_80107920_storyresult(void) {
    s16 arrow[2];
    SrPos pos[2];
    s16 *res;
    s16 gfxFrame;
    u16 frame;
    s16 win;
    s16 gfxArrow;
    Process *prc;
    SrRecInfo *info;
    s16 i;
    s16 a;
    s16 side;
    s16 ang;
    s16 step;
    s16 n;
    s32 msg;
    s32 ok;

    res = HuPrcCurrentGet()->user_data;
    gfxFrame = func_8000B838_main(0x150001);
    frame = InitEspriteSlot(gfxFrame, 0, 1);
    func_8000BCC8_main(frame, 600);
    func_8000BBD4_main(frame, 160, 204);
    func_8000BBFC_main(frame, 0);
    func_8000BB94_main(frame);
    win = func_8005A968_main(48, 187, 224, 42, 0, 12);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0);
    func_8005BE30_main(win, 1);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0x40, 0x40, 0x40);
    func_8005FBF8_main(win, 0, 0, 0);
    func_8005C02C_main(win, 7);
    func_8005BF70_main(win, 0xFF);
    pos[0].x = 25;
    pos[1].x = 295;
    pos[1].y = 130;
    pos[0].y = 130;
    gfxArrow = func_8000B838_main(0x150003);
    for (i = 0; i < 2; i++) {
        arrow[i] = InitEspriteSlot(gfxArrow, 0, 1);
        func_8000BCC8_main(arrow[i], 100);
        func_8000BBD4_main(arrow[i], pos[i].x, pos[i].y);
        func_8000BBFC_main(arrow[i], 0);
        func_8000BB94_main(arrow[i]);
    }
    func_8000BC48_main(arrow[1], 1);
    prc = func_8010A4A4_storyresult(1, -1);
    if (prc == NULL) {
        *res = -3;
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    info = prc->user_data;
    HuPrcVSleep();
    info->cmd = 1;
    func_8000BB54_main(frame);
    func_8000BB54_main(arrow[0]);
    func_8000BB54_main(arrow[1]);
    for (a = 0; a < 0x101; a += 36) {
        func_8000BBFC_main(frame, a);
        func_8000BBFC_main(arrow[0], a);
        func_8000BBFC_main(arrow[1], a);
        HuPrcVSleep();
    }
    func_8005B43C_main(win, 0x6128, -1, -1);
    side = 0;
    HuPrcVSleep();
    ang = 0;
    step = 0;
    while (TRUE) {
        if (D_800D5558_main[D_8010ABE0_storyresult] & 0x8000) {
            HuAudFXPlay(2);
            break;
        }
        if (info->cmd == 0) {
            if ((D_800D5558_main[D_8010ABE0_storyresult] & 0x100) || D_800CBB6E_main[D_8010ABE0_storyresult] >= 31) {
                HuAudFXPlay(1);
                info->cmd = 3;
                ang = 180;
                step = -22;
                side = 1;
            } else if ((D_800D5558_main[D_8010ABE0_storyresult] & 0x200) || D_800CBB6E_main[D_8010ABE0_storyresult] < -30) {
                HuAudFXPlay(1);
                info->cmd = 4;
                ang = 180;
                step = 22;
                side = 0;
            }
        }
        if (step != 0) {
            if ((u16)(ang += step) >= 361) {
                step = 0;
                func_8000BBD4_main(arrow[0], pos[0].x, pos[0].y);
                func_8000BBD4_main(arrow[1], pos[1].x, pos[1].y);
            } else {
                func_8000BBD4_main(arrow[side], pos[side].x + sindf(ang) * 8.0f, pos[side].y);
            }
        }
        HuPrcVSleep();
    }
    func_8005D294_main(win);
    for (a = 0x100; a >= 0; a -= 36) {
        func_8000BBFC_main(arrow[0], a);
        func_8000BBFC_main(arrow[1], a);
        HuPrcVSleep();
    }
    func_8000BB94_main(arrow[0]);
    func_8000BB94_main(arrow[1]);
    if (GwStory.unk2 >= 2) {
        _SetFlag(0x2D);
    }
    _ClearFlag(0x28);
    _ClearFlag(0x18);
    while (TRUE) {
        info->cmd = 10;
        do {
            HuPrcVSleep();
        } while (info->cmd != 0);
        func_8005B43C_main(win, 0x6127, -1, -1);
        while (func_8005E0C0_main(win)) {
            HuPrcVSleep();
        }
        if (func_8005E1D8_main(win, 0, 0) != 0) {
            break;
        }
        ok = 1;
        n = func_801070D8_storyresult();
        if (n != 0) {
            if (n >= 13) {
                func_8005B43C_main(win, 0x612D, -1, -1);
                while (func_8005E0C0_main(win)) {
                    HuPrcVSleep();
                }
                info->cmd = 9;
                do {
                    HuPrcVSleep();
                } while (info->cmd != 0);
                msg = 0x612E;
            } else {
                info->cmd = 9;
                do {
                    HuPrcVSleep();
                } while (info->cmd != 0);
                msg = 0x6129;
            }
            func_8005B43C_main(win, msg, -1, -1);
            while (func_8005E0C0_main(win)) {
                HuPrcVSleep();
            }
            if (func_8005E1D8_main(win, 0, 0) != 0) {
                ok = 0;
            }
        }
        func_8005D294_main(win);
        if (ok) {
            func_8005B43C_main(win, 0x612C, -1, -1);
            HuPrcVSleep();
            if (GwStory.unk1 < 6) {
                _SetFlag(D_8010A9D8_storyresult[GwStory.unk1]);
            }
            func_80107140_storyresult();
            info->cmd = 10;
            func_8005B43C_main(win, 0x612A, -1, -1);
            while (func_8005E0C0_main(win)) {
                HuPrcVSleep();
            }
            break;
        }
    }
    func_8005D294_main(win);
    D_8010ABE2_storyresult = 3;
    D_8010AC32_storyresult = 0x7C;
    D_8010AC30_storyresult = 6;
    *res = -1;
    info->cmd = 2;
    for (a = 0x100; a >= 0; a -= 36) {
        func_8000BBFC_main(frame, a);
        HuPrcVSleep();
    }
    func_8000BB94_main(frame);
    while (info->cmd != 0) {
        HuPrcVSleep();
    }
    func_8010A558_storyresult(prc);
    func_8000C184_main(frame);
    func_8000C184_main(arrow[0]);
    func_8000C184_main(arrow[1]);
    HuSprKill(gfxFrame);
    HuSprKill(gfxArrow);
    func_8005F364_main(win);
    *res = -3;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80107920_storyresult);
#endif

#ifdef NON_MATCHING
/* Residue (masked 7): retail sign-extends the rank in v0 and puts the >= 4 slti in the bgezl delay slot; this copies it to v1 first. */
/* Starts the record board process (func_80107920_storyresult) for slot; *res = -1 when the slot has no result. */
Process *func_8010818C_storyresult(s16 *res, s16 slot) {
    s16 rank;
    Process *prc;

    rank = func_8010A370_storyresult(slot);
    if (rank < 0) {
        *res = -1;
        return NULL;
    }
    if (rank >= 4) {
        _SetFlag(0x1D);
    }
    _SetFlag(0x1E);
    *res = slot;
    D_800EBAF0_minigame = D_8010ABE0_storyresult;
    prc = omAddPrcObj(func_80107920_storyresult, 0x4000, 0x800, 0);
    prc->user_data = res;
    return prc;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010818C_storyresult);
#endif

void func_8010822C_storyresult(void) {
    s16 sp10;

    D_800CD280_main = 0;
    func_801060D0_storyresult(&D_8010AB9C_storyresult[0]);
    D_8010A912_storyresult = 1;
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0x20);
    func_800E8180_name_81(1000.0f, 10000.0f);
    D_8010AC2A_storyresult = 0xB;
    WipeCreateIn(0xB, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8010818C_storyresult(&sp10, -1);
    while (sp10 >= -1) {
        HuPrcVSleep();
    }
    D_8010AC2A_storyresult = 0xB;
    D_8010AC28_storyresult = 0x36;
    D_8010A914_storyresult = 2;
    D_8010A910_storyresult = 1;

    while (1) {
        HuPrcVSleep();
    }
}

/* Starts minigame's record viewer (func_800E9170_minigame) for slot; *res = -1 when the slot has no result. */
Process *func_8010832C_storyresult(s16 *res, s16 slot) {
    Process *prc;

    if (func_800E905C_minigame(slot) < 0) {
        *res = -1;
        return NULL;
    }
    *res = slot;
    D_800EBAF0_minigame = 0;
    prc = omAddPrcObj(func_800E9170_minigame, 0x4000, 0x800, 0);
    prc->user_data = res;
    return prc;
}

#ifdef NON_MATCHING
/* Residue (masked ~10): retail reloads D_800CDA7C_main for each button test and sets the first bit with andi/sltu (this: srl/andi on one load); loop counters swap registers. */
/* Event 3 (a test): fills every story record with top results, then shows minigame's record viewer
   for the slot picked by buttons C-down/C-right/C-up (D_800CDA7C_main[0] bits 2, 0, 3) and exits. */
void func_801083A4_storyresult(void) {
    s16 res;
    u16 spr;
    s16 slot;
    s16 n;
    s32 i;
    s32 j;
    s16 v;

    D_800CD280_main = 0;
    func_801060D0_storyresult(D_8010AB9C_storyresult);
    spr = InitEspriteSlot(func_8000B838_main(0x140067), 0, 0);
    func_8000BC48_main(spr, 0x4000);
    func_8000BBD4_main(spr, 160, 120);
    WipeCreateIn(D_8010AC2A_storyresult, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    for (i = 0, n = 4; i < 12; i++) {
        GwStory.unk3[i] = 4;
        if (++n >= 5) {
            n = 1;
        }
    }
    GwStory.unkF = 4;
    GwStory.unk2 = 3;
    GwStory.unk_64[2] = 1;
    GwStory.unk_64[15] = 0;
    GwStory.unk_64[1] = 4;
    GwStory.unk_64[0] = 4;
    for (i = 0, n = 4; i < 12; i++) {
        v = (i < (u8)GwStory.unk_64[0]) ? n : 0;
        GwStory.unk_64[3 + i] = v;
        n = v + 1;
        if (n >= 5) {
            n = 1;
        }
    }
    for (i = 0; i < 6; i++) {
        GwStory.unk5E[i] = i & 3;
        GwStory.unk58[i] = 4;
        for (j = 0; j < 12; j++) {
            GwStory.unk10[i][j] = 4;
        }
    }
    slot = (D_800CDA7C_main[0] & 4) != 0;
    if (D_800CDA7C_main[0] & 1) {
        slot |= 2;
    }
    if (D_800CDA7C_main[0] & 8) {
        slot |= 4;
    }
    func_8010832C_storyresult(&res, slot);
    while (res >= 0) {
        HuPrcVSleep();
    }
    D_8010A910_storyresult = 1;
    while (1) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_801083A4_storyresult);
#endif

void func_801085E8_storyresult(s16 grp, s16 idx, s16 gfx, u16 prio, s32 x, s32 y) {
    func_80055458_main(grp, idx, 0x100);
    HuSprAttrReset(grp, idx, 0xFFFF);
    HuSprAttrSet(grp, idx, 0x9000);
    HuSprScaleSet(grp, idx, 1.0f, 1.0f);
    func_800550F4_main(grp, idx, 0);
    func_80055024_main(grp, idx, gfx, 0);
    HuSprPriSet(grp, idx, prio);
    func_80054904_main(grp, idx, x, y);
}

s16 func_801086E4_storyresult(u8 *rec, s16 odd, s16 start, s16 end, SrRecPart *mark, SrRecPart *num, SrRecWork *w) {
    u8 *idx;
    u16 grp;
    s16 *gfx;
    u16 x;
    u16 y;
    s32 i;
    s16 ret;
    s16 v;
    s16 g;
    s16 px;
    s16 py;

    idx = odd ? D_8010AB74_storyresult : D_8010AB6C_storyresult;
    grp = w->grp;
    gfx = w->gfx;
    x = w->info->x;
    y = w->info->y;
    ret = -1;
    for (i = start; i < end; i++, idx++, num++, mark++) {
        v = rec[*idx] - 1;
        if (v < 0) {
            ret = i;
            break;
        }
        mark->fade = 1;
        mark->shown = 1;
        g = gfx[v];
        num->pos = D_8010AB34_storyresult[i];
        px = x + num->pos.x;
        py = y + num->pos.y;
        func_801085E8_storyresult(grp, i + 16, g, 1200, px, py);
        num->fade = 1;
        num->shown = 1;
    }
    return ret;
}

#ifdef NON_MATCHING
s16 func_80108884_storyresult(SrRecWork *w) {
    u8 count[4];
    u8 *rec;
    u8 last;
    s32 i;
    s16 r;
    s16 n;
    s16 grp;
    s16 y;
    u16 x0;
    u16 x;
    u8 c;
    s16 k;

    for (i = 0; i < 4; i++) {
        count[i] = 0;
    }
    if (w->slot < 0) {
        last = GwStory.unkF;
        rec = GwStory.unk3;
    } else {
        last = GwStory.unk58[w->slot];
        rec = GwStory.unk10[w->slot];
    }
    if (last != 0) {
        count[last - 1]++;
    }
    for (i = 0; i < 12; i++, rec++) {
        if (*rec != 0) {
            count[*rec - 1]++;
        }
    }
    y = w->info->y - 8;
    x0 = w->info->x - 54;
    n = 0;
    grp = w->grp2;
    for (r = 3; r >= 0; r--) {
        x = x0;
        c = count[r];
        for (i = 0; i < c; i++) {
            func_80054904_main(grp, n, x, y);
            func_80055458_main(grp, n, 0);
            HuSprAttrReset(grp, n, 0x8000);
            n++;
            x += 12;
        }
        y += 14;
    }
    for (k = n; k < 13; k++) {
        HuSprAttrSet(grp, k, 0x8000);
    }
    w->winFade[5] = 1;
    w->unk14C = 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108884_storyresult);
#endif

#ifdef NON_MATCHING
/* Residue (masked 2): the per-rank count local gets an andi and the saved registers rotate (as minigame func_800E7BCC_minigame). */
/* func_80108884_storyresult with the record passed in: per-rank marks for last and rec[12]. */
s16 func_80108AC0_storyresult(SrRecWork *w, u8 last, u8 *rec) {
    u8 count[4];
    s32 i;
    s16 r;
    s16 n;
    s16 grp;
    s16 y;
    u16 x0;
    u16 x;
    u8 c;
    s16 k;

    for (i = 0; i < 4; i++) {
        count[i] = 0;
    }
    if (last != 0) {
        count[last - 1]++;
    }
    for (i = 0; i < 12; i++, rec++) {
        if (*rec != 0) {
            count[*rec - 1]++;
        }
    }
    y = w->info->y - 8;
    x0 = w->info->x - 54;
    n = 0;
    grp = w->grp2;
    for (r = 3; r >= 0; r--) {
        x = x0;
        c = count[r];
        for (i = 0; i < c; i++) {
            func_80054904_main(grp, n, x, y);
            func_80055458_main(grp, n, 0);
            HuSprAttrReset(grp, n, 0x8000);
            n++;
            x += 12;
        }
        y += 14;
    }
    for (k = n; k < 13; k++) {
        HuSprAttrSet(grp, k, 0x8000);
    }
    w->winFade[5] = 1;
    w->unk14C = 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108AC0_storyresult);
#endif

s16 func_80108CB8_storyresult(SrRecWork *w) {
    return func_80108AC0_storyresult(w, GwStory.unk58[GwStory.unk1], GwStory.unk10[GwStory.unk1]);
}

s16 func_80108D04_storyresult(SrRecWork *w) {
    return func_80108AC0_storyresult(w, GwStory.unk_64[15], (u8 *)&GwStory.unk_64[3]);
}

#ifdef NON_MATCHING
/* Residue (masked 2): in the page 2 call retail computes &w->part[22] before storing mark to the stack (scheduling). */
/* Shows record page `page`: 0/1 the results, 2 the last one, 3/5 the rank marks of the record,
   4 those of the current story slot, 6 those of the saved copy. */
s16 func_80108D34_storyresult(s16 page, SrRecWork *w) {
    u8 *rec;
    s16 odd;
    SrRecPart *mark;
    SrRecPart *num;
    s16 ret;

    ret = -1;
    func_8005D294_main(w->win[4]);
    func_8005B43C_main(w->win[4], D_8010AB50_storyresult[page], -2, -1);
    w->winFade[4] = 1;
    if (page < 2) {
        odd = 0;
        mark = &w->part[2];
        if (page == 1) {
            odd = 1;
            mark = &w->part[8];
        }
        if (w->slot < 0) {
            rec = GwStory.unk3;
            num = &w->part[16];
        } else {
            rec = GwStory.unk10[w->slot];
            num = &w->part[16];
        }
        ret = func_801086E4_storyresult(rec, odd, 0, 6, mark, num, w);
    } else if (page == 2) {
        if (w->slot < 0) {
            rec = &GwStory.unkF;
        } else {
            rec = &GwStory.unk58[w->slot];
        }
        mark = &w->part[14];
        ret = func_801086E4_storyresult(rec, 0, 6, 7, mark, &w->part[22], w);
    } else if (page == 3) {
        ret = func_80108884_storyresult(w);
    } else if (page == 4) {
        ret = func_80108CB8_storyresult(w);
    } else if (page == 5) {
        ret = func_80108884_storyresult(w);
    } else if (page == 6) {
        ret = func_80108D04_storyresult(w);
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108D34_storyresult);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108F0C_storyresult);

#ifdef NON_MATCHING
/* Residue (masked 8): retail keeps a raw copy of slot and does not thread the slot >= 6 jump (as minigame func_800E905C_minigame). */
/* Rank (0-4) of a story record: slot 0-5 saved, -1 the current story, -2 the saved copy; -1 if incomplete. */
s16 func_8010A370_storyresult(s16 slot) {
    u8 *last;
    u8 *rec;
    s16 score;
    s32 i;
    s16 rank;

    if (slot < 6) {
        if (slot < 0) {
            if (slot == -2) {
                last = (u8 *)&GwStory.unk_64[15];
                rec = (u8 *)&GwStory.unk_64[3];
            } else {
                last = &GwStory.unkF;
                rec = GwStory.unk3;
            }
        } else {
            last = &GwStory.unk58[slot];
            rec = GwStory.unk10[slot];
        }
        if (*last != 0) {
            goto ok;
        }
    }
fail:
    return -1;
ok:
    if (*last >= 5) {
        *last = 4;
    }
    score = D_8010AB84_storyresult[*last];
    for (i = 0; i < 12; i++, rec++) {
        if (*rec == 0) {
            goto fail;
        }
        if (*rec >= 5) {
            *rec = 4;
        }
        score += D_8010AB7C_storyresult[*rec];
    }
    for (rank = 0; rank < 4; rank++) {
        if (score < D_8010AB8C_storyresult[rank]) {
            break;
        }
    }
    return rank;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A370_storyresult);
#endif

Process *func_8010A4A4_storyresult(s16 mode, s16 slot) {
    SrRecInfo *info;
    Process *prc;

    if ((mode == 0 || mode == 1) && func_8010A370_storyresult(slot) < 0) {
        return NULL;
    }
    info = HuMemAllocTag(sizeof(SrRecInfo), 0x7918);
    memset(info, 0, sizeof(SrRecInfo));
    info->x = 160;
    info->y = 120;
    info->mode = mode;
    info->slot = slot;
    prc = omAddPrcObj(func_80108F0C_storyresult, 0x4000, 0x1000, 0);
    prc->user_data = info;
    return prc;
}

s32 func_8010A558_storyresult(Process *prc) {
    SrRecInfo *info;
    s32 ret;

    if (prc == NULL) {
        return 0;
    }
    info = prc->user_data;
    info->cmd = 0xFF;
    do {
        HuPrcVSleep();
    } while (info->cmd != 0);
    ret = omDelPrcObj(prc);
    HuMemFree(info);
    return ret;
}

#ifdef NON_MATCHING
/* Register allocation only (masked 0): retail computes the star difference in a0 and the result in v1. */
/* Party rank of player: 4 two or more stars ahead, 3 one ahead, else 2 most coins among the star leaders, 1. */
s16 func_8010A5C4_storyresult(s16 player) {
    s16 stars;
    s16 best;
    s16 coin;
    s16 ret;
    s32 diff;
    s32 i;

    stars = GwPlayer[player].star;
    best = 0;
    for (i = 0; i < 4; i++) {
        if (i != player) {
            if (best < GwPlayer[i].star) {
                best = GwPlayer[i].star;
            }
        }
    }
    diff = stars - best;
    if (diff >= 2) {
        ret = 4;
    } else if (diff == 1) {
        ret = 3;
    } else {
        coin = GwPlayer[player].coin;
        best = 0;
        for (i = 0; i < 4; i++) {
            if (i != player && GwPlayer[i].star >= stars) {
                if (best < GwPlayer[i].coin) {
                    best = GwPlayer[i].coin;
                }
            }
        }
        ret = 1;
        if (best < coin) {
            ret = 2;
        }
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A5C4_storyresult);
#endif

#ifdef NON_MATCHING
/* Register allocation only (masked 0): retail computes the player's offset first. */
/* Duel rank of player from the star difference with the other player. */
s16 func_8010A738_storyresult(s16 player) {
    s32 diff;
    s32 other;
    s16 ret;

    other = player == 0;
    diff = GwPlayer[player].star - GwPlayer[other].star;
    if (diff >= 3) {
        ret = 4;
    } else if (diff == 2) {
        ret = 3;
    } else {
        ret = 1;
        if (diff == 1) {
            ret = 2;
        }
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A738_storyresult);
#endif

s16 func_8010A7B0_storyresult(s16 player) {
    s16 n;
    s16 rank;

    n = GwPlayer[player].bonusCoin;
    rank = 0;
    if (n >= 0) {
        rank = D_8010AB90_storyresult[n];
    }
    return rank;
}

#ifdef NON_MATCHING
/* Residue (masked 15): register allocation around the player search (retail copies GwStory.unk1 and keeps the chapter kind in t0). */
/* The story player's rank in the board just played (0 if not found). */
s16 func_8010A7EC_storyresult(void) {
    s32 kind;
    u8 chr;
    s16 n;
    s16 i;
    s16 ret;

    kind = D_8010A924_storyresult[GwStory.unk0];
    n = 4;
    if (kind != 0) {
        n = 2;
    }
    chr = GwStory.unk1;
    for (i = 0; i < n; i++) {
        if (GwPlayer[i].chr == chr) {
            break;
        }
    }
    if (i >= n) {
        return 0;
    }
    ret = 0;
    switch (kind) {
    case 0:
        ret = func_8010A5C4_storyresult(i);
        break;
    case 1:
        ret = func_8010A738_storyresult(i);
        break;
    case 2:
        ret = func_8010A7B0_storyresult(i);
        break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A7EC_storyresult);
#endif
