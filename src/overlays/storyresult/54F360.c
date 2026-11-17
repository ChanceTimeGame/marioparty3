#include "common.h"
#include "../ovl_81_name/ovl_81.h"

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
extern Vec D_8010AC0C_storyresult; /* CRot copy; splat also labels .y/.z */
extern f32 D_8010AC10_storyresult;
extern f32 D_8010AC14_storyresult;
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
extern u8 D_8010A924_storyresult[]; /* per GwStory.unk0: 0/1 hidden-block chapter, 2 duel, other always */
extern s16 kakusiMasuItemHis[];
extern u8 D_800CE20A_main;
extern s16 D_800EBAF0_minigame;
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

/*<func_80106FF0_storyresult>*/
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
/*</func_80106FF0_storyresult>*/

/*<func_80107030_storyresult>*/
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
/*</func_80107030_storyresult>*/

/*<func_801070D8_storyresult>*/
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
/*</func_801070D8_storyresult>*/

/*<func_80107140_storyresult>*/
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
/*</func_80107140_storyresult>*/

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80107204_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80107920_storyresult);

/*<func_8010818C_storyresult>*/
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
/*</func_8010818C_storyresult>*/

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

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010832C_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_801083A4_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_801085E8_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_801086E4_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108884_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108AC0_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108CB8_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108D04_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108D34_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108F0C_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A370_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A4A4_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A558_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A5C4_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A738_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A7B0_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A7EC_storyresult);
