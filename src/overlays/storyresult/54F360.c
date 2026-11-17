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

/* Record board entry (minigame's MgPartDef). */
typedef struct SrPartDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ SrPos pos;
} SrPartDef; /* size 8 */

typedef struct SrRect {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
} SrRect; /* size 8 */

typedef struct SrRGB {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
} SrRGB; /* size 3 */

extern SrPartDef D_8010A9E4_storyresult[15]; /* board parts */
extern s32 D_8010AA5C_storyresult[];         /* rank mark files */
extern s32 D_8010AA78_storyresult[];         /* per character: portrait file */
extern s32 D_8010AA90_storyresult[];         /* per character: name message */
extern s32 D_8010AAA8_storyresult[];         /* per partner: message */
extern s32 D_8010AAB8_storyresult[];         /* per rank: message */
extern SrRGB D_8010AAD4_storyresult[];       /* rank 4 colour cycle (0,0,0 ends it) */
extern SrRGB D_8010AAE0_storyresult[];       /* rank 3 colour cycle */
extern SrRGB D_8010AAEC_storyresult[];       /* per rank: message colour */
extern SrRect D_8010AB04_storyresult[];      /* windows */
extern s16 D_800D6B62_main;

// NON_MATCHING: register allocation (retail keeps `color` in s8 and spills `info` and `page`, reloading
// them at every use; this C keeps `page` in s8), so the ROM differs in raw lines and reload counts (masked 331
// at 1466/1482 instructions, every block aligned with the asm). The cmd switch lists 0 and 0xFF so it builds
// a compare tree as retail does, not a jump table; the duplicated func_80055420_main call reproduces a mode-2
// compare retail keeps there.
#ifdef NON_MATCHING
/* The record board process (minigame's func_800E7F60_minigame, with a second record source: pages 4 and 6
   show the current story slot and the saved copy, part 23 the saved copy's portrait). */
void func_80108F0C_storyresult(void) {
    s16 cur[3];
    s16 step[3];
    s32 msg[4];
    SrRecInfo *info;
    s16 *rankWin;
    SrRGB *colorStart;
    s16 grp;
    s16 lastCmd;
    s16 shown;
    s16 pending;
    s16 alphaStep;
    s16 winAlpha;
    s16 winStep;
    s16 hasRank;
    s16 colorFrames;
    s16 colorTimer;
    s16 colorCycle;
    s16 page;
    s16 shownPage;
    s16 changing;
    s16 rank;
    s16 rank2;
    s16 hasCopy;
    s16 swapPortrait;
    s32 grpShift;
    s32 rank32;
    s32 grpShift2;
    SrRecWork *w;
    SrRecPart *part;
    SrPartDef *def;
    s16 *win;
    s16 *fade;
    s16 *gfx;
    s16 alpha;
    s16 done;
    s16 n;
    s16 newPage;
    u16 x;
    u16 y;
    s32 prio;
    s16 spr;
    u16 grp2;
    s32 m;
    s32 i;
    SrRGB *color;

    info = HuPrcCurrentGet()->user_data;
    w = HuMemAllocTag(sizeof(SrRecWork), 0x7918);
    memset(w, 0, sizeof(SrRecWork));
    w->info = info;
    page = 0;
    shownPage = 0;
    hasCopy = 0;
    for (part = w->part, i = 0; i < 24; i++, part++) {
        part->spr = -1;
        part->alpha = 0x100;
        part->fade = 0;
        part->shown = 0;
    }
    w->gfx2 = -1;
    w->grp2 = -1;
    rank = -1;
    msg[3] = 0;
    switch (info->mode) {
    case 0:
    default:
        hasRank = 1;
        rank = func_8010A370_storyresult(info->slot);
        msg[0] = 0x6101;
        msg[2] = D_8010AAA8_storyresult[GwStory.unk5E[info->slot]];
        msg[3] = D_8010AAB8_storyresult[rank];
        w->slot = info->slot;
        break;
    case 1:
        info->slot = GwStory.unk1;
        hasRank = 1;
        rank = func_8010A370_storyresult(-1);
        msg[0] = 0x6101;
        msg[2] = D_8010AAA8_storyresult[GwStory.unk2];
        msg[3] = D_8010AAB8_storyresult[rank];
        w->slot = -1;
        break;
    case 2:
        if (func_80106FF0_storyresult()) {
            hasCopy = 1;
        }
        info->slot = GwStory.unk1;
        msg[0] = 0x6100;
        msg[2] = D_8010AAA8_storyresult[GwStory.unk2];
        w->slot = -1;
        hasRank = 1;
        if (GwStory.unk0 == 12) {
            rank = func_8010A370_storyresult(-1);
            page = 2;
            shownPage = 2;
        } else {
            page = D_8010A924_storyresult[GwStory.unk0];
            shownPage = page;
        }
        break;
    }
    msg[1] = D_8010AA90_storyresult[info->slot];
    grp = HuSprGrpCreate(24, 0);
    n = 0;
    def = D_8010A9E4_storyresult;
    part = w->part;
    grpShift = grp << 16;
    for (i = 0; i < ARRAY_COUNTU(D_8010A9E4_storyresult); i++, n++, def++, part++) {
        prio = 1200;
        spr = func_8000B838_main(def->file);
        part->spr = spr;
        part->pos = def->pos;
        x = part->pos.x + info->x;
        y = part->pos.y + info->y;
        if (i >= 2) {
            prio = 1199;
        }
        func_801085E8_storyresult(grpShift >> 16, n, spr, prio, (s16)x, (s16)y);
    }
    HuSprScaleSet(grp, 1, 1.0f, 1.02f);
    if (info->mode != 2) {
        func_80055420_main(grp, 1, 0, 0, 0);
    } else {
        func_80055420_main(grp, 1, 0, 0, 0);
    }
    func_80055458_main(grp, 1, 0xFF);
    w->part[1].alpha = 0xFF;
    w->grp = grp;
    w->part[15].spr = func_8000B838_main(D_8010AA78_storyresult[info->slot]);
    w->part[15].pos.x = -96;
    w->part[15].pos.y = -74;
    func_801085E8_storyresult(grp, 15, w->part[15].spr, 1200, (s16)(w->part[15].pos.x + info->x),
                              (s16)(info->y - 74));
    if (hasCopy) {
        w->part[23].spr = func_8000B838_main(D_8010AA78_storyresult[(u8)GwStory.unk_64[1]]);
        w->part[23].pos.x = -96;
        w->part[23].pos.y = -74;
        func_801085E8_storyresult(grp, 23, w->part[23].spr, 1200, (s16)(w->part[23].pos.x + info->x),
                                  (s16)(info->y - 74));
    }
    for (gfx = w->gfx, i = 0; i < 4; i++, gfx++) {
        *gfx = func_8000B838_main(D_8010AA5C_storyresult[i]);
    }
    w->grp2 = HuSprGrpCreate(13, 0);
    w->gfx2 = func_8000B838_main(0x15001D);
    y = info->y - 28;
    for (i = 0; i < 13; i++) {
        func_801085E8_storyresult(w->grp2, i, w->gfx2, 1200, (s16)(info->x + (i * 12 - 24)), (s16)y);
    }
    D_800D6B62_main = 400;
    win = w->win;
    fade = w->winFade;
    x = info->x;
    y = info->y;
    for (i = 0; i < ARRAY_COUNTU(w->win); i++, win++, fade++) {
        *win = func_8005A968_main(x + D_8010AB04_storyresult[i].x, y + D_8010AB04_storyresult[i].y,
                                  D_8010AB04_storyresult[i].w, D_8010AB04_storyresult[i].h, 0, 12);
        func_8005BDFC_main(*win, 0);
        func_8005BEE0_main(*win, 0);
        func_8005C060_main(*win, 2, 0xFF, 0x40, 0x40);
        func_8005C060_main(*win, 5, 0, 0xB0, 0xC0);
        func_8005C060_main(*win, 4, 0x60, 0xFF, 0x40);
        func_8005C060_main(*win, 6, 0xFF, 0xFF, 0x40);
        func_8005C154_main(*win, 0x40, 0x40, 0x40);
        func_8005FBF8_main(*win, 0, 0, 0);
        func_8005C02C_main(*win, 7);
        func_8005BF70_main(*win, 0);
        *fade = 0;
    }
    win = w->win;
    fade = w->winFade;
    func_8005B43C_main(w->win[0], msg[0], -1, -1);
    func_8005B43C_main(w->win[1], msg[1], -1, -1);
    func_8005B43C_main(w->win[2], msg[2], -1, -1);
    w->winFade[2] = 1;
    w->winFade[1] = 1;
    w->winFade[0] = 1;
    if (hasRank) {
        if (msg[3] != 0) {
            func_8005B43C_main(w->win[3], msg[3], -1, -1);
        }
        fade[3] = 1;
        /* Host: rank is -1 for a chapter other than 12 in mode 2 (reads the byte triple before the table). */
        func_8005C060_main(win[3], 7, D_8010AAEC_storyresult[rank].r, D_8010AAEC_storyresult[rank].g,
                           D_8010AAEC_storyresult[rank].b);
    }
    func_8005B43C_main(win[5], 0x6111, -1, -1);
    func_80108D34_storyresult(page, w);
    lastCmd = 0;
    w->unk14C = 0;
    shown = 0;
    pending = 0;
    changing = 0;
    alphaStep = 0;
    alpha = 0;
    winStep = 0;
    winAlpha = 0;
    colorCycle = 0;
    colorTimer = 0;
    colorFrames = 0;
    rankWin = &w->win[3];
    swapPortrait = 0;
    rank32 = rank;
    grpShift2 = grp << 16;
    do {
        if ((lastCmd == 1 || lastCmd == 2) && w->winFade[0] == 0) {
            info->cmd = 0;
        }
        if (pending && ((alphaStep == 0) & (winStep == 0))) {
            pending = 0;
            info->cmd = 0;
        }
        if (changing) {
            if ((alphaStep == 0) & (winStep == 0)) {
                changing = 0;
                func_80108D34_storyresult(page, w);
                alpha = 0;
                alphaStep = 51;
                winAlpha = 0;
                winStep = 51;
                pending = 1;
                if (page >= 4) {
                    if (swapPortrait) {
                        swapPortrait = 0;
                        if (page == 6) {
                            part = &w->part[23];
                        } else {
                            part = &w->part[15];
                        }
                        part->fade = 1;
                    }
                    m = 0;
                    if (page == 5) {
                        func_8005B43C_main(w->win[0], msg[0], -1, -1);
                        func_8005B43C_main(w->win[1], msg[1], -1, -1);
                        func_8005B43C_main(w->win[2], msg[2], -1, -1);
                        m = msg[3];
                        rank2 = rank;
                    } else if (page == 4) {
                        rank2 = func_8010A370_storyresult(GwStory.unk1);
                        func_8005B43C_main(w->win[2], D_8010AAA8_storyresult[GwStory.unk5E[GwStory.unk1]], -1, -1);
                        m = 0;
                        if (rank2 >= 0) {
                            func_8005B43C_main(w->win[0], 0x6101, -1, -1);
                            m = D_8010AAB8_storyresult[rank2];
                        } else {
                            func_8005B43C_main(w->win[0], 0x6100, -1, -1);
                        }
                    } else if (page == 6) {
                        rank2 = func_8010A370_storyresult(-2);
                        func_8005B43C_main(w->win[1], D_8010AA90_storyresult[(u8)GwStory.unk_64[1]], -1, -1);
                        func_8005B43C_main(w->win[2], D_8010AAA8_storyresult[(u8)GwStory.unk_64[2]], -1, -1);
                        m = 0;
                        if (rank2 >= 0) {
                            func_8005B43C_main(w->win[0], 0x6101, -1, -1);
                            m = D_8010AAB8_storyresult[rank2];
                        } else {
                            func_8005B43C_main(w->win[0], 0x6100, -1, -1);
                        }
                    }
                    if (m != 0) {
                        func_8005B43C_main(w->win[3], m, -1, -1);
                        func_8005C060_main(w->win[3], 7, D_8010AAEC_storyresult[rank2].r,
                                           D_8010AAEC_storyresult[rank2].g, D_8010AAEC_storyresult[rank2].b);
                        if (rank2 == 4) {
                            colorCycle = 1;
                            color = colorStart = D_8010AAD4_storyresult;
                            colorFrames = 6;
                        } else if (rank2 == 3) {
                            colorCycle = 1;
                            color = colorStart = D_8010AAE0_storyresult;
                            colorFrames = 8;
                        }
                    } else {
                        func_8005D294_main(w->win[3]);
                    }
                    for (i = 0; i < 4; i++) {
                        w->winFade[i] = 1;
                    }
                }
            }
        } else if (shownPage != page) {
            alpha = 0xFF;
            alphaStep = -51;
            winAlpha = 0xFF;
            winStep = -51;
            w->winFade[4] = 1;
            if (shownPage >= 3) {
                w->winFade[5] = 1;
                w->unk14C = 1;
            }
            for (part = w->part, i = 0; i < 24; i++, part++) {
                if (part->shown > 0) {
                    part->shown = 0;
                    part->fade = 1;
                }
            }
            if (page >= 4) {
                colorCycle = 0;
                for (i = 0; i < 4; i++) {
                    w->winFade[i] = 1;
                }
            }
            if ((page == 6) | (shownPage == 6)) {
                swapPortrait = 1;
                if (page == 6) {
                    part = &w->part[15];
                } else {
                    part = &w->part[23];
                }
                part->fade = 2;
            }
            shownPage = page;
            changing = 1;
        }
        if (lastCmd != info->cmd) {
            part = w->part;
            switch (info->cmd) {
            case 1:
                if (shown == 0) {
                    shown = 1;
                    alpha = 0;
                    alphaStep = 36;
                    winAlpha = 0;
                    winStep = 36;
                    part[0].fade = 1;
                    part[1].fade = 1;
                    part[15].fade = 1;
                    if (rank32 == 4) {
                        colorCycle = 1;
                        color = colorStart = D_8010AAD4_storyresult;
                        colorFrames = 6;
                    } else if (rank32 == 3) {
                        colorCycle = 1;
                        color = colorStart = D_8010AAE0_storyresult;
                        colorFrames = 8;
                    }
                }
                break;
            case 2:
                if (shown != 0) {
                    shown = 0;
                    alpha = 0xFF;
                    alphaStep = -36;
                    winAlpha = 0xFF;
                    winStep = -36;
                    part[0].fade = 1;
                    part[1].fade = 1;
                    part[15].fade = 1;
                    for (fade = w->winFade, i = 0; i < 5; i++, fade++) {
                        *fade = 1;
                    }
                    part = w->part;
                    if (shownPage >= 3) {
                        w->winFade[5] = 1;
                        w->unk14C = 1;
                    }
                    for (i = 0; i < 24; i++, part++) {
                        if (part->shown > 0) {
                            part->shown = 0;
                            part->fade = 1;
                        }
                    }
                }
                break;
            case 3:
                page++;
                if (page >= 4) {
                    page = 0;
                }
                break;
            case 4:
                page--;
                if (page < 0) {
                    page = 3;
                }
                break;
            case 5:
                newPage = 0;
                goto setPage;
            case 6:
                newPage = 1;
                goto setPage;
            case 7:
                newPage = 2;
                goto setPage;
            case 8:
                newPage = 3;
                goto setPage;
            case 9:
                newPage = 4;
                goto setPage;
            case 10:
                newPage = 5;
                if ((page != 4) & (page != 6)) {
                    info->cmd = 8;
                    newPage = 3;
                }
                goto setPage;
            case 11:
                newPage = 6;
            setPage:
                if (page == newPage) {
                    info->cmd = 0;
                }
                page = newPage;
                break;
            case 0:
            case 0xFF:
                break;
            }
            lastCmd = info->cmd;
        }
        if (colorCycle) {
            if (colorTimer != 0) {
                colorTimer--;
                cur[0] -= step[0];
                cur[1] -= step[1];
                cur[2] -= step[2];
                func_8005C060_main(*rankWin, 7, (u8)cur[0], (u8)cur[1], (u8)cur[2]);
            } else {
                cur[0] = color->r;
                cur[1] = color->g;
                cur[2] = color->b;
                func_8005C060_main(*rankWin, 7, (u8)cur[0], (u8)cur[1], (u8)cur[2]);
                color++;
                if (color->r == 0 && color->g == 0 && color->b == 0) {
                    color = colorStart;
                }
                step[0] = (cur[0] - color->r) / colorFrames;
                step[1] = (cur[1] - color->g) / colorFrames;
                step[2] = (cur[2] - color->b) / colorFrames;
                colorTimer = colorFrames - 1;
            }
        }
        if (alphaStep != 0) {
            done = 0;
            alpha += alphaStep;
            if (alpha >= 0xFF) {
                alphaStep = 0;
                alpha = 0xFF;
                done = 1;
            } else if (alpha <= 0) {
                alphaStep = 0;
                alpha = 0;
                done = 1;
            }
            for (part = w->part, i = 0; i < 24; i++, part++) {
                if (part->fade > 0) {
                    if (part->fade == 1) {
                        part->fade = 2;
                        HuSprAttrReset(grpShift2 >> 16, i, 0x8000);
                    }
                    if (done) {
                        part->fade = 0;
                    }
                    if (alpha == 0) {
                        HuSprAttrSet(grpShift2 >> 16, i, 0x8000);
                    }
                    if (alpha >= part->alpha) {
                        func_80055458_main(grpShift2 >> 16, i, part->alpha);
                    } else {
                        func_80055458_main(grpShift2 >> 16, i, alpha);
                    }
                }
            }
            if (w->unk14C != 0) {
                if (done) {
                    w->unk14C = 0;
                }
                grp2 = w->grp2;
                for (i = 0; i < 13; i++) {
                    if (alpha == 0) {
                        HuSprAttrSet(grp2, i, 0x8000);
                    }
                    func_80055458_main(grp2, i, alpha);
                }
            }
        }
        if (winStep != 0) {
            done = 0;
            winAlpha += winStep;
            if (winAlpha >= 0xFF) {
                winStep = 0;
                winAlpha = 0xFF;
                done = 1;
            } else if (winAlpha <= 0) {
                winStep = 0;
                winAlpha = 0;
                done = 1;
            }
            win = w->win;
            for (fade = w->winFade, i = 0; i < 6; i++, win++, fade++) {
                if (*fade > 0) {
                    if (done) {
                        *fade = 0;
                    }
                    func_8005BF70_main(*win, winAlpha);
                }
            }
        }
        HuPrcVSleep();
    } while (lastCmd != 0xFF);
    HuSprGrpKill(grp);
    /* Retail kills 23 of the 24 parts: part 23 (the saved copy's portrait) is never freed. */
    for (part = w->part, i = 0; i < ARRAY_COUNTU(w->part) - 1; i++, part++) {
        if (part->spr >= 0) {
            HuSprKill(part->spr);
        }
    }
    HuSprGrpKill(w->grp2);
    HuSprKill(w->gfx2);
    for (gfx = w->gfx, i = 0; i < 4; i++, gfx++) {
        if (*gfx >= 0) {
            HuSprKill(*gfx);
        }
    }
    for (win = w->win, i = 0; i < ARRAY_COUNTU(w->win); i++, win++) {
        func_8005F364_main(*win);
    }
    HuMemFree(w);
    info->cmd = 0;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108F0C_storyresult);
#endif

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
