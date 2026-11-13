#ifndef _MODESEL_H_
#define _MODESEL_H_

#include "common.h"

/* Overlay 0x77 `modesel`: the mode-select screen after a save file is chosen. Its sprite, model and
   window helpers (func_80105C7C..func_80107B08) are filesel's library (filesel.h, 516AE0.c) shifted
   by 0x60 bytes, with the same slot counts. */

/* The overlay was linked from several source files; each one starts 16-byte aligned. In the single
   unit here, MS_FILE_END() after the last function of a file reproduces that padding. */
#ifdef NON_MATCHING
#define MS_FILE_END()
#else
#define MS_FILE_END() __asm__(".section .text\n    .align 4\n");
/* fork B: corrected prototypes (the originals above were removed: C cannot redeclare them). The
   float arguments travel in a1-a3 because the first argument is an integer. */
void func_8010B75C_modesel(s32 no, f32 x, f32 y, f32 z, f32 unk14); /* bob part set + apply */
void func_8010B790_modesel(s32 no, f32 x, f32 y, f32 z, f32 unk14); /* bob part set */
void func_8010B804_modesel(s32 no, f32 rot); /* bob part rotation set */
void func_801094F0_modesel(Vec *a, Vec *b, f32 t, Vec *out);
/* D_80110C68/C6C/C70_modesel are one array of structs (MsBob in 4F7E90.c); their s32 externs were removed. */

#endif

/* Sprite slot: D_8010F710_modesel[64] (filesel FsSpr). */
typedef struct MsSpr {
    /* 0x00 */ s16 espId; /* esprite slot, -1 when free */
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ f32 scaleX;
    /* 0x10 */ f32 scaleY;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18; /* 0xFF at init */
} MsSpr; /* size = 0x1C */

/* Model slot: D_8010FE90_modesel[64] (filesel FsModel). */
typedef struct MsModel {
    /* 0x00 */ s16 model;  /* -1 when free */
    /* 0x02 */ s16 motion; /* -1 when free */
    /* 0x04 */ s32 pos[3]; /* retail keeps the position truncated to integers */
    /* 0x10 */ Vec scale;
    /* 0x1C */ Vec rot;
    /* 0x28 */ s32 unk28;
} MsModel; /* size = 0x2C */

/* Window slot: D_80110998_modesel[32] (filesel UnkFileSelect2). */
typedef struct MsWin {
    /* 0x00 */ s16 id;   /* window id, -1 when free */
    /* 0x04 */ u32 mes;  /* heap copy of the message (address above 0x80000000), or 0 */
    /* 0x08 */ s32 type; /* window type (3 = choice window) */
} MsWin; /* size = 0xC */

/* .data */
extern OvlEntrypoint D_8010F270_modesel[];
extern Vec D_8010F3B0_modesel; /* camera position */
extern Vec D_8010F3BC_modesel; /* camera target */
extern Vec D_8010F3C8_modesel; /* camera up */

/* .bss: the helper library */
extern MsSpr D_8010F710_modesel[64];
extern s16 D_8010FE10_modesel[64]; /* sprite animations */
extern MsModel D_8010FE90_modesel[64];
extern s16 D_80110990_modesel; /* background animation */
extern s16 D_80110992_modesel; /* background esprite */
extern MsWin D_80110998_modesel[32];

/* .bss: screen state */
extern s32 D_80110BD8_modesel;
extern s16 D_80110BDA_modesel; /* the low half of D_80110BD8_modesel (big-endian), read on its own */
extern Process *D_80110BDC_modesel; /* main process (func_80107CEC_modesel) */
extern Vec D_80110BE8_modesel[3]; /* camera eye, target, up (splat also names D_80110BF4/C00) */

/* Typed from their loads and stores only (sizes from the .bss split); a fork that learns more
   corrects them in a block at the end of this file. */
extern u16 D_8010F296_modesel;                   /* .data; lhu: 80107CEC 8010BA70 8010CD00 */
extern u8 D_8010F2A0_modesel[];                  /* .data; lbu: 8010F204 8010F214 8010F234 */
extern u8 D_8010F2B0_modesel[];                  /* .data; lbu: 8010F258 */
extern f32 D_8010F2BC_modesel;                   /* .data; lw: 801088AC */
extern f32 D_8010F2C0_modesel;                   /* .data; lw: 801088AC */
extern f32 D_8010F2C4_modesel;                   /* .data; lw: 801088AC */
extern s32 D_8010F2C8_modesel;                   /* .data; lw,sw: 80109A58 */
extern f32 D_8010F2CC_modesel;                   /* .data; lwc1,swc1: 8010A068 8010A1C4 8010A2E8 8010A420 */
extern f32 D_8010F2D0_modesel;                   /* .data; lwc1,swc1: 8010A068 8010A1C4 8010A2E8 8010A420 */
extern f32 D_8010F2D4_modesel[];                  /* .data; lwc1,swc1: 8010A068 8010A1C4 8010A2E8 8010A420 */
extern s32 D_8010F2F0_modesel[];                  /* .data; lw: 8010DC6C */
extern f32 D_8010F304_modesel;                   /* .data; lwc1: 8010E000 8010E138 */
extern f32 D_8010F308_modesel;                   /* .data; lwc1: 8010E000 8010E138 */
extern f32 D_8010F30C_modesel[];                  /* .data; lwc1: 8010E000 8010E138 */
extern s32 D_80110B1C_modesel;                   /* .bss 0x4 bytes; lw: 8010B824 */
extern s32 D_80110B20_modesel;                   /* .bss 0x4 bytes; lw,sw: 8010B790 8010B824 */
extern s32 D_80110B28_modesel;                   /* .bss 0x4 bytes; lw,sw: 8010B790 8010B824 */
extern f32 D_80110B2C_modesel;                   /* .bss 0x4 bytes; swc1: 8010B790 */
extern s32 D_80110BA8_modesel;                   /* .bss 0x4 bytes; sw: 8010E7B4 */
extern s32 D_80110BB0_modesel;                   /* .bss 0x4 bytes; sw: 8010E7B4 */
extern s32 D_80110BC4_modesel;                   /* .bss 0x4 bytes; sw: 8010E7B4 */
extern omObjData *D_80110BD0_modesel;                   /* .bss 0x4 bytes; lw,sw: 80107CEC 8010B6B0 8010BA70 */
extern s32 D_80110BD4_modesel;                   /* .bss 0x4 bytes; lw,sw: 8010AF90 8010BA70 8010E3A4 */
extern Process *D_80110BE0_modesel;                   /* .bss 0x8 bytes; lw,sw: 80107CEC 8010BA70 */

/* Not declared here (mixed or address-only accesses; the fork that decompiles their users types them):
   D_801109A4_modesel D_80110B18_modesel D_80110B24_modesel D_80110B30_modesel D_80110B70_modesel D_80110B88_modesel
   D_80110B98_modesel D_80110BAC_modesel D_80110BB4_modesel D_80110BBC_modesel D_80110BC8_modesel D_80110BCC_modesel
   D_80110C10_modesel D_80110C14_modesel D_80110C20_modesel D_80110C2C_modesel D_80110C38_modesel
   D_80110C3C_modesel D_80110C40_modesel D_80110C5C_modesel D_80110C74_modesel D_80110C78_modesel D_80110CB0_modesel
   D_80110CBC_modesel D_80110CD4_modesel D_80110CD8_modesel D_80110CE4_modesel D_80110CF0_modesel D_80110CF4_modesel D_80110CF8_modesel D_80110DEC_modesel */

/* main functions and data without a shared prototype (as filesel.h) */
extern u8 D_800D09A9_main;
extern s8 D_800D2132_main; /* pause.c */
void func_80030030_main(f32);
void func_800465DC_main(s8 arg0);
void func_800465F4_main(s8 arg0);
void func_80050CFC_main(void);
s32 func_800465D0_main(void);
s32 func_800465E8_main(void);
s32 func_8005086C_main(void);
void func_80013320_main(s16 modelIndex, s16 camIndex);
void func_80013350_main(s16 camIndex);
s16 func_800E905C_minigame(s16 slot);
void func_800E989C_minigame(void);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BCC8_main(u16 spriteId, s32 arg1);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
s32 func_800452A0_main(void *arg0, void *arg1);
void func_800601BC_main(s16 win, s32 arg1, s8 arg2);

/* 4F7E90.c: all 171 functions. Argument and return widths come from the asm (m2c and how each
   function reads a0-a3/f12/f14); the library ones follow filesel.h. */
void func_801059A0_modesel(void);
void func_801059D0_modesel(void); /* object/camera/viewport init */
void func_80105BD8_modesel(void);
void func_80105BFC_modesel(void);
void func_80105C20_modesel(void);
void func_80105C50_modesel(void);
void func_80105C7C_modesel(void);
s16 func_80105D10_modesel(s32 no);
s16 func_80105D24_modesel(s32 no);
void func_80105D40_modesel(s32 no, s32 dataNum); /* sprite anim create */
void func_80105D78_modesel(s32 arg0);
void func_80105DD0_modesel(s32 no, s16 animNo); /* esprite create */
void func_80105E38_modesel(s32 arg0);
void func_80105EA8_modesel(s32 no, s32 dataNum); /* sprite create */
void func_80105EDC_modesel(s32 no, s32 dataNum); /* BG sprite create */
void func_80105F20_modesel(s32 arg0);
void func_80105F4C_modesel(void);
void func_80105F84_modesel(s32 arg0);
void func_80105FB4_modesel(s32 arg0);
void func_80105FE4_modesel(s32 no); /* BG sprite disp on */
void func_80106000_modesel(s32 no); /* BG sprite disp off */
void func_8010601C_modesel(s32 no, s32 x, s32 y); /* sprite pos set */
void func_80106074_modesel(s32 no, s32 *x, s32 *y);
void func_801060A4_modesel(s32 no, f32 x, f32 y); /* sprite scale set */
void func_801060F4_modesel(s32 no, u16 alpha);
void func_8010612C_modesel(s32 no, u16 attr); /* sprite attr set */
void func_80106160_modesel(s32 no, u16 attr); /* sprite attr reset */
void func_80106194_modesel(s32 no, u16 arg1);
void func_801061C8_modesel(s32 no, u16 arg1, u16 arg2);
void func_80106234_modesel(void);
void func_80106280_modesel(s32 no, s32 arg1, s32 dataNum); /* model create */
void func_8010631C_modesel(s32 no, s32 dataNum, s32 arg2); /* motion create */
void func_801063A4_modesel(s32 arg0);
void func_80106454_modesel(void);
s16 func_8010648C_modesel(s32 arg0);
s16 func_801064B0_modesel(s32 arg0);
void func_801064D4_modesel(s32 no, f32 x, f32 y, f32 z); /* model rot set */
void func_8010653C_modesel(s32 no, f32 x, f32 y, f32 z); /* model pos set */
void func_801065B0_modesel(s32 no, f32 x, f32 y, f32 z); /* model scale set */
void func_80106618_modesel(s32 no, f32 *x, f32 *y, f32 *z); /* model pos get */
void func_8010666C_modesel(s32 no, f32 *x, f32 *y, f32 *z); /* model rot get */
void func_801066B4_modesel(s32 no, f32 *x, f32 *y, f32 *z); /* model scale get */
void func_801066FC_modesel(s32 arg0);
void func_8010673C_modesel(s32 arg0);
void func_8010677C_modesel(s32 no, s16 flag);
void func_801067C0_modesel(s32 no, s32 motNo, s16 arg2, s16 arg3, s16 arg4);
void func_80106830_modesel(s32 no, s16 arg1);
void func_80106874_modesel(s32 no, f32 speed);
void func_801068AC_modesel(s32 no, u32 time);
void func_80106910_modesel(s32 arg0);
s32 func_801069B0_modesel(s32 arg0);
void func_80106A38_modesel(s32 no, s32 motNo, s16 flag);
void func_80106AA8_modesel(s32 dataNum);
void func_80106B0C_modesel(void);
u32 func_80106B38_modesel(u32 mes); /* heap copy of a message when mes is a pointer */
void func_80106BA0_modesel(s32 no, u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type); /* window create */
s16 func_80106DEC_modesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_80106F38_modesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_801070A0_modesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_80107248_modesel(u32 mes, s16 x, s16 y, s16 type);
s16 func_80107314_modesel(u32 mes, s16 x, s16 y, s16 type);
s16 func_801073E0_modesel(u32 mes, s16 x, s16 y, s16 type);
void func_801074AC_modesel(void);
void func_801074F0_modesel(s32 no); /* window kill */
void func_801075D4_modesel(void);
void func_80107638_modesel(s32 no, f32 x, f32 y);
void func_80107668_modesel(s32 no, f32 x, f32 y);
void func_801076D0_modesel(s32 arg0);
void func_80107700_modesel(s32 arg0);
void func_80107730_modesel(s32 no, u32 mes); /* window message set */
void func_801077FC_modesel(s32 no, s8 arg1, s32 arg2);
s32 func_80107838_modesel(s32 no, s16 arg1, s32 arg2);
s16 func_80107870_modesel(s32 no); /* window id get */
void func_8010788C_modesel(s32 no); /* wait for window */
void func_801078E0_modesel(s32 btn); /* wait for button */
void func_8010791C_modesel(s32 no, s16 arg1);
u16 func_80107954_modesel(s32 val); /* debug value print */
void func_80107B08_modesel(void);
void func_80107CB0_modesel(void);
void func_80107CEC_modesel(void); /* main process */
void func_801088AC_modesel(void);
void func_801088F8_modesel(void);
void func_8010893C_modesel(Process *proc);
Process *func_8010899C_modesel(void);
void func_801089DC_modesel(Vec *eye, Vec *at, Vec *up); /* camera get */
void func_80108A34_modesel(Vec *eye, Vec *at, Vec *up); /* camera set */
void func_80108A94_modesel(s32 arg0); /* arg0 unused; the caller passes 0 */
s32 func_80108AE0_modesel(Vec *eye, Vec *at, Vec *up);
void func_80108F8C_modesel(Vec *eye, Vec *at, Vec *up);
void func_80108FC4_modesel(void);
void func_80108FD0_modesel(omObjData *arg0);
void func_80109154_modesel(void);
omObjData *func_80109188_modesel(s32 arg0, s32 arg1);
void func_80109290_modesel(omObjData *arg0);
void func_80109408_modesel(void);
void func_80109444_modesel(void);
f32 func_801094A8_modesel(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_801096D4_modesel(omObjData *arg0);
omObjData *func_80109968_modesel(s32 arg0, s32 arg1);
s32 func_80109A58_modesel(s32 arg0);
void func_80109B74_modesel(void);
void func_80109BC0_modesel(omObjData *arg0);
void func_80109C8C_modesel(s32 arg0);
omObjData *func_80109CEC_modesel(u32 arg0);
void func_80109DB8_modesel(omObjData *arg0);
void *func_80109E90_modesel(s32 arg0);
void func_80109FCC_modesel(omObjData *obj);
void func_8010A020_modesel(u32 arg0);
void func_8010A068_modesel(omObjData *arg0);
void func_8010A1C4_modesel(omObjData *arg0);
void func_8010A2E8_modesel(omObjData *arg0);
void func_8010A420_modesel(omObjData *arg0);
void func_8010A62C_modesel(u32 arg0);
void func_8010A674_modesel(omObjData *arg0);
void func_8010A84C_modesel(omObjData *arg0);
omObjData *func_8010A9B8_modesel(u32 arg0);
omObjData *func_8010AA48_modesel(u32 arg0);
void func_8010AAC0_modesel(omObjData *arg0);
omObjData *func_8010ABB4_modesel(u32 arg0);
void func_8010AC3C_modesel(void);
void func_8010ACA8_modesel(omObjData *arg0);
void func_8010AD74_modesel(omObjData *arg0);
void func_8010ADC8_modesel(omObjData *arg0);
omObjData *func_8010AF18_modesel(void);
void func_8010AF90_modesel(void);
void func_8010B6B0_modesel(void);
void func_8010B824_modesel(s32 arg0);
void func_8010B940_modesel(s32 arg0, f32 arg1);
Process *func_8010B9C4_modesel(void);
s32 func_8010BA70_modesel(void);
s32 func_8010C094_modesel(void);
void func_8010C874_modesel(void);
void func_8010CA30_modesel(void);
void func_8010CB34_modesel(void);
s32 func_8010CC38_modesel(void);
s32 func_8010CD00_modesel(u32 arg0);
u32 func_8010D8DC_modesel(u32 arg0, s32 arg1);
void func_8010DC6C_modesel(u32 arg0);
void func_8010DE88_modesel(u32 arg0);
void func_8010DF70_modesel(void);
void func_8010DFB4_modesel(void);
void func_8010DFD0_modesel(void);
void func_8010E000_modesel(u32 arg0, s32 *arg1, s32 *arg2);
void func_8010E138_modesel(u32 arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void func_8010E22C_modesel(s32 arg0, s32 arg1);
void func_8010E280_modesel(s32 no, u32 arg1);
void func_8010E3A4_modesel(s32 arg0, f32 arg1);
void func_8010E50C_modesel(void);
void func_8010E558_modesel(s32 arg0);
void func_8010E5B8_modesel(void);
void func_8010E5F0_modesel(omObjData *arg0);
void func_8010E6D8_modesel(s32 arg0);
void func_8010E790_modesel(Process *proc);
void func_8010E7B4_modesel(void);
void func_8010E984_modesel(void);
void func_8010EBC4_modesel(void);
void func_8010EBF8_modesel(void);
void func_8010EC40_modesel(void);
f32 func_8010EC74_modesel(f32 arg0, f32 arg1);
void func_8010ECAC_modesel(omObjData *obj);
void func_8010ED00_modesel(void);
void func_8010ED3C_modesel(void);
s32 func_8010F1FC_modesel(void);
s32 func_8010F204_modesel(s32 arg0); /* D_8010F2A0_modesel[arg0]; callers use v0 unmasked */
u8 func_8010F214_modesel(s32 arg0);
s32 func_8010F234_modesel(s32 arg0);
u8 func_8010F258_modesel(s32 arg0);

/* fork B: corrected prototypes (the originals above were removed: C cannot redeclare them). The
   float arguments travel in a1-a3 because the first argument is an integer. */
void func_8010B75C_modesel(s32 no, f32 x, f32 y, f32 z, f32 unk14); /* bob part set + apply */
void func_8010B790_modesel(s32 no, f32 x, f32 y, f32 z, f32 unk14); /* bob part set */
void func_8010B804_modesel(s32 no, f32 rot); /* bob part rotation set */
void func_801094F0_modesel(Vec *a, Vec *b, f32 t, Vec *out);
/* D_80110C68/C6C/C70_modesel are one array of structs (MsBob in 4F7E90.c); their s32 externs were removed. */

#endif
