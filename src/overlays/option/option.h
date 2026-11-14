#ifndef _OPTION_H_
#define _OPTION_H_

#include "common.h"

/* Overlay 0x7B `option`: the options screen (sound, rumble, records, erase). Its sprite, model and
   window helpers (func_80110170..func_80111E74) are modesel's library (modesel.h, 4F7E90.c
   func_80105C50..func_80107954) shifted by 0xA520 bytes, with the same slot counts. */

/* The overlay was linked from several source files; each one starts 16-byte aligned. In the single
   unit here, OP_FILE_END() after the last function of a file reproduces that padding. Retail pads
   after func_801059A0, func_80107D64, func_80110018 and func_80113490. */
#ifdef NON_MATCHING
#define OP_FILE_END()
#else
#define OP_FILE_END() __asm__(".section .text\n    .align 4\n");
#endif

/* Sprite slot: D_801147F0_option[64] (modesel MsSpr). */
typedef struct OpSpr {
    /* 0x00 */ s16 espId; /* esprite slot, -1 when free */
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ f32 scaleX;
    /* 0x10 */ f32 scaleY;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18; /* 0xFF at init */
} OpSpr; /* size = 0x1C */

/* Model slot: D_80114F70_option[64] (modesel MsModel). */
typedef struct OpModel {
    /* 0x00 */ s16 model;  /* -1 when free */
    /* 0x02 */ s16 motion; /* -1 when free */
    /* 0x04 */ s32 pos[3]; /* retail keeps the position truncated to integers */
    /* 0x10 */ Vec scale;
    /* 0x1C */ Vec rot;
    /* 0x28 */ s32 unk28;
} OpModel; /* size = 0x2C */

/* Window slot: D_80115A78_option[32] (modesel MsWin). */
typedef struct OpWin {
    /* 0x00 */ s16 id;   /* window id, -1 when free */
    /* 0x04 */ u32 mes;  /* heap copy of the message (address above 0x80000000), or 0 */
    /* 0x08 */ s32 type; /* window type (3 = choice window) */
} OpWin; /* size = 0xC */

/* The view of a model camera that func_80105FF8_option reads (modesel MsHmfCamView). */
typedef struct OpHmfCamView {
    /* 0x00 */ char unk0[8];
    /* 0x08 */ Vec pos;
    /* 0x14 */ Vec at;
    /* 0x20 */ Vec up;
} OpHmfCamView;

/* Camera state: D_801146F0_option (splat names the fields D_801146F4 .. D_80114760). */
typedef struct OpCam {
    /* 0x00 */ Process *proc;      /* camera process (func_80105EB8_option / func_80105D74_option) */
    /* 0x04 */ Vec eye;
    /* 0x10 */ Vec at;
    /* 0x1C */ Vec up;
    /* 0x28 */ f32 fov;
    /* 0x2C */ f32 nearZ;
    /* 0x30 */ f32 farZ;
    /* 0x34 */ s32 view;           /* model camera followed (func_80013320_main), -1 for none */
    /* 0x38 */ omObjData *moveObj; /* camera move object (func_80106BAC_option and siblings) */
    /* 0x3C */ Vec fromEye;
    /* 0x48 */ Vec fromAt;
    /* 0x54 */ Vec toEye;
    /* 0x60 */ Vec toAt;
    /* 0x6C */ s32 t;
    /* 0x70 */ s32 len;
} OpCam; /* size = 0x74 */

/* .data */
extern OvlEntrypoint D_801134B0_option[];
extern Vec D_801139E0_option; /* initial camera eye */
extern Vec D_801139EC_option; /* initial camera target */
extern Vec D_801139F8_option; /* initial camera up */

/* .bss: camera (fork A) */
extern OpCam D_801146F0_option;
extern s32 D_80114764_option;     /* camera move: aim the up vector (func_8010744C_option/func_801077BC_option) */
extern Process *D_80114770_option; /* the screen process (func_80108A68_option and siblings) */

/* .bss: the helper library (modesel names in brackets) */
extern OpSpr D_801147F0_option[64];  /* D_8010F710_modesel */
extern s16 D_80114EF0_option[64];    /* D_8010FE10_modesel: sprite animations */
extern OpModel D_80114F70_option[64]; /* D_8010FE90_modesel */
extern s16 D_80115A70_option;        /* D_80110990_modesel: background animation */
extern s16 D_80115A72_option;        /* D_80110992_modesel: background esprite */
extern OpWin D_80115A78_option[32];  /* D_80110998_modesel */

/* Typed from their loads and stores only; a fork that learns more corrects them in a block at the
   end of this file. */
extern f32 D_80113770_option;                /* .data ; lwc1: 8010A3E8 */
extern s32 D_80113774_option;                /* .data ; lw: 8010A3E8 */
extern s32 D_801139D0_option;                /* .data ; lw,sw: 801130E8 */
extern s16 D_801147E6_option;                /* .bss 0x2 bytes; lh: 8010FE84 */

/* Not declared here (address-only or mixed accesses; the fork that decompiles their users types them):
   D_80113514_option D_80113580_option D_801135E0_option D_801135F8_option D_8011367C_option D_80113694_option
   D_801136AC_option D_801136B8_option D_801136F4_option D_80113700_option D_8011370C_option D_80113718_option
   D_80113724_option D_80113730_option D_8011373C_option D_80113748_option D_8011376C_option D_80113778_option
   D_80113784_option D_80113790_option D_8011379C_option D_801137B4_option D_801137CC_option D_801137E4_option
   D_801137FC_option D_80113808_option D_80113814_option D_80113820_option D_8011382C_option D_80113844_option
   D_8011385C_option D_80113874_option D_8011388C_option D_80113898_option D_801138A4_option D_801138B0_option
   D_801138BC_option D_801138C8_option D_8011394C_option D_80114778_option D_80114780_option D_80114784_option
   D_80114788_option D_80114794_option D_801147A0_option D_801147B0_option D_801147E0_option D_801147E4_option
   D_801147E8_option
   */

/* main functions and data without a shared prototype (as modesel.h) */
extern s8 D_800D2132_main; /* pause.c */
void func_80030030_main(f32);
void func_800465F4_main(s8 arg0);
s32 func_800465E8_main(void);
void func_80050CFC_main(void);
void func_80012E54_main(s16 camIndex);
void func_80013320_main(s16 modelIndex, s16 camIndex);
void func_80013350_main(s16 camIndex);
s16 func_800E905C_minigame(s16 slot);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
s32 func_800452A0_main(void *arg0, void *arg1);
void func_800601BC_main(s16 win, s32 arg1, s8 arg2);
void func_80017A84_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_80032FC0_main(s16 arg0, u8 arg1, u8 arg2);
void func_80033910_main(void *arg0); /* HmfTexData * (32160.c) */
void func_80033970_main(void *arg0); /* HmfTexData * (32160.c) */
s32 func_800078F8_main(s32 slot);
u16 GWMgRecordGet(s16 arg0);

/* 5334D0.c: all 193 functions. Argument and return widths come from the asm (m2c and how each
   function reads a0-a3/f12/f14); the library ones follow modesel.h. */
void func_801059A0_option(void);
void func_801059D0_option(void); /* object/camera/viewport init */
void func_80105C14_option(void);
void func_80105C38_option(void);
void func_80105C5C_option(void);
void func_80105C80_option(void);
void func_80105CA4_option(void);
void func_80105CC8_option(void);
void func_80105CEC_option(void);
void func_80105D10_option(void); /* camera state init */
void func_80105D5C_option(f32 fov, f32 nearZ, f32 farZ); /* perspective set */
void func_80105D74_option(void);
void func_80105DA0_option(s16 view, f32 fov); /* camera follows a model camera */
void func_80105E40_option(void); /* camera process kill */
void func_80105EB8_option(void); /* camera process */
void func_80105F08_option(f32 fov); /* fixed camera */
s32 func_80105FF8_option(Vec *eye, Vec *at, Vec *up); /* current camera get (modesel func_80108AE0_modesel) */
void func_80106508_option(Vec *eye, Vec *at, Vec *up); /* camera set */
void func_80106998_option(omObjData *obj);
void func_80106B78_option(void); /* camera move kill */
omObjData *func_80106BAC_option(Vec *eye, Vec *at, s32 len); /* camera move (linear) */
void func_80106C7C_option(omObjData *obj);
omObjData *func_80106F88_option(Vec *eye, Vec *at, s32 len); /* camera move (arc) */
void func_80107058_option(omObjData *obj);
omObjData *func_8010737C_option(Vec *eye, Vec *at, s32 len);
void func_8010744C_option(omObjData *obj);
void func_80107758_option(Vec *eye, Vec *at, s32 len);
void func_8010778C_option(Vec *eye, Vec *at, s32 len);
void func_801077BC_option(omObjData *obj);
void func_80107AD4_option(Vec *eye, Vec *at, s32 len);
void func_80107B08_option(Vec *eye, Vec *at, s32 len);
f32 func_80107B38_option(f32 x0, f32 y0, f32 x1, f32 y1); /* modesel func_801094A8_modesel */
void func_80107B80_option(Vec *a, Vec *b, f32 t, Vec *out); /* modesel func_801094F0_modesel */
void func_80107D64_option(Vec *a, Vec *b, f32 t, Vec *out);
void func_80107F50_option(s32 arg0, s16 arg1, s16 arg2);
void func_80108A68_option(void);
void func_80108AAC_option(void);
void func_80108AF0_option(void);
void func_80108B34_option(void);
void func_80108B58_option(void); /* main process */
s32 func_80109504_option(void);
void func_801096B8_option(s32 arg0, s32 arg1, s32 arg2);
void func_801096E4_option(void);
void func_80109730_option(Vec *eye, Vec *at, Vec *up, f32 fov, Vec *pos, f32 *x, f32 *y); /* world to screen */
void func_80109908_option(f32 x, f32 y, f32 z, s32 *outX, s32 *outY); /* world to screen, current camera */
void func_8010998C_option(Vec *eye, Vec *at, Vec *up, f32 x, f32 y, f32 z, s32 *outX, s32 *outY);
void func_80109A0C_option(s32 arg0, void *arg1, void *arg2, s32 arg3);
void func_80109B7C_option(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_80109CB0_option(u32 arg0, s32 *arg1, s32 *arg2);
u32 func_80109D04_option(u32 arg0);
u32 func_80109EF4_option(u32 arg0, s32 arg1);
void func_8010A3E8_option(s32 arg0);
s32 func_8010A498_option(void);
void func_8010A66C_option(void); /* process */
void func_8010A8DC_option(u32 arg0, s32 *arg1, s32 *arg2);
u32 func_8010A940_option(u32 arg0, s32 arg1);
u32 func_8010AF54_option(u32 arg0);
void func_8010B654_option(void);
u32 func_8010B68C_option(u32 arg0, s32 arg1);
s32 func_8010BACC_option(u32 arg0);
void func_8010BFA4_option(s32 arg0);
s32 func_8010C04C_option(void);
void func_8010C224_option(void); /* process */
void func_8010C3E4_option(s32 arg0, s16 arg1, s16 arg2);
void func_8010D5B0_option(s32 arg0, s16 arg1, s16 arg2);
void func_8010E77C_option(s32 x, s32 y, s32 t);
void func_8010E7FC_option(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8010E8E0_option(void);
void func_8010F138_option(void);
f32 func_8010F914_option(f32 arg0, f32 arg1); /* modesel func_8010EC74_modesel */
void func_8010F94C_option(void);
void func_8010FA28_option(void);
void func_8010FB40_option(u32 arg0, s32 arg1);
u16 func_8010FC40_option(s32 arg0);
void func_8010FDF4_option(void);
s32 func_8010FE00_option(void);
void func_8010FE10_option(void);
void func_8010FE84_option(omObjData *arg0);
omObjData *func_8010FF0C_option(s32 arg0);
void func_8010FF88_option(void);
void func_8010FFDC_option(void);
s32 func_80110018_option(void);
void func_80110170_option(void);
void func_8011019C_option(void);
s16 func_80110230_option(s32 no);
s16 func_80110244_option(s32 no);
void func_80110260_option(s32 no, s32 dataNum); /* sprite anim create */
void func_80110298_option(s32 arg0);
void func_801102F0_option(s32 no, s16 animNo); /* esprite create */
void func_80110358_option(s32 arg0);
void func_801103C8_option(s32 no, s32 dataNum); /* sprite create */
void func_801103FC_option(s32 no, s32 dataNum); /* BG sprite create */
void func_80110440_option(s32 arg0);
void func_8011046C_option(void);
void func_801104A4_option(s32 arg0);
void func_801104D4_option(s32 arg0);
void func_80110504_option(s32 no); /* BG sprite disp on */
void func_80110520_option(s32 no); /* BG sprite disp off */
void func_8011053C_option(s32 no, s32 x, s32 y); /* sprite pos set */
void func_80110594_option(s32 no, s32 *x, s32 *y);
void func_801105C4_option(s32 no, f32 x, f32 y); /* sprite scale set */
void func_80110614_option(s32 no, u16 alpha);
void func_8011064C_option(s32 no, u16 attr); /* sprite attr set */
void func_80110680_option(s32 no, u16 attr); /* sprite attr reset */
void func_801106B4_option(s32 no, u16 arg1);
void func_801106E8_option(s32 no, u16 arg1, u16 arg2);
void func_80110754_option(void);
void func_801107A0_option(s32 no, s32 arg1, s32 dataNum); /* model create */
void func_8011083C_option(s32 no, s32 dataNum, s32 arg2); /* motion create */
void func_801108C4_option(s32 arg0);
void func_80110974_option(void);
s16 func_801109AC_option(s32 arg0);
s16 func_801109D0_option(s32 arg0);
void func_801109F4_option(s32 no, f32 x, f32 y, f32 z); /* model rot set */
void func_80110A5C_option(s32 no, f32 x, f32 y, f32 z); /* model pos set */
void func_80110AD0_option(s32 no, f32 x, f32 y, f32 z); /* model scale set */
void func_80110B38_option(s32 no, f32 *x, f32 *y, f32 *z); /* model pos get */
void func_80110B8C_option(s32 no, f32 *x, f32 *y, f32 *z); /* model rot get */
void func_80110BD4_option(s32 no, f32 *x, f32 *y, f32 *z); /* model scale get */
void func_80110C1C_option(s32 arg0);
void func_80110C5C_option(s32 arg0);
void func_80110C9C_option(s32 no, s16 flag);
void func_80110CE0_option(s32 no, s32 motNo, s16 arg2, s16 arg3, s16 arg4);
void func_80110D50_option(s32 no, s16 arg1);
void func_80110D94_option(s32 no, f32 speed);
void func_80110DCC_option(s32 no, u32 time);
void func_80110E30_option(s32 arg0);
s32 func_80110ED0_option(s32 arg0);
void func_80110F58_option(s32 no, s32 motNo, s16 flag);
void func_80110FC8_option(s32 dataNum);
void func_8011102C_option(void);
u32 func_80111058_option(u32 mes); /* heap copy of a message when mes is a pointer */
void func_801110C0_option(s32 no, u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type); /* window create */
s16 func_8011130C_option(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_80111458_option(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_801115C0_option(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_80111768_option(u32 mes, s16 x, s16 y, s16 type);
s16 func_80111834_option(u32 mes, s16 x, s16 y, s16 type);
s16 func_80111900_option(u32 mes, s16 x, s16 y, s16 type);
void func_801119CC_option(void);
void func_80111A10_option(s32 no); /* window kill */
void func_80111AF4_option(void);
void func_80111B58_option(s32 no, f32 x, f32 y);
void func_80111B88_option(s32 no, f32 x, f32 y);
void func_80111BF0_option(s32 arg0);
void func_80111C20_option(s32 arg0);
void func_80111C50_option(s32 no, u32 mes); /* window message set */
void func_80111D1C_option(s32 no, s8 arg1, s32 arg2);
s32 func_80111D58_option(s32 no, s16 arg1, s32 arg2);
s16 func_80111D90_option(s32 no); /* window id get */
void func_80111DAC_option(s32 no); /* wait for window */
void func_80111E00_option(s32 btn); /* wait for button */
void func_80111E3C_option(s32 no, s16 arg1);
u16 func_80111E74_option(s32 val); /* debug value print */
void func_80112028_option(s32 arg0, s32 arg1, s32 arg2);
void func_80112044_option(s32 arg0, s32 arg1);
void func_80112060_option(void);
void func_80112084_option(void);
void func_8011239C_option(void);
void func_801123D8_option(void);
void func_80112A44_option(void);
void func_80112B08_option(void);
void func_80112E14_option(void);
void func_80112EB8_option(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_80112F48_option(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_80112FD8_option(s32 arg0, s32 arg1, s32 arg2);
void func_80112FF4_option(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_80113088_option(void);
void func_801130CC_option(void);
s32 func_801130E8_option(s32 arg0);
s16 func_80113218_option(s32 arg0);
void func_8011323C_option(s32 arg0);
void func_80113258_option(s32 arg0);
void func_80113274_option(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void func_80113290_option(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_801132AC_option(s32 arg0, s16 arg1);
void func_801132C8_option(s32 arg0, s16 arg1);
void func_801132E4_option(s32 arg0, u32 arg1);
void func_80113300_option(s32 arg0);
void func_8011331C_option(s32 arg0, s32 arg1, s32 arg2);
void func_80113338_option(s32 arg0, s32 arg1, s16 arg2, s16 arg3, u16 arg4);
void func_80113368_option(s32 arg0, s32 *arg1, s32 *arg2);
void func_80113384_option(s32 arg0);
void func_801133A0_option(s32 arg0);
void func_801133BC_option(s32 arg0, u32 arg1);
void func_801133EC_option(s32 arg0);
void func_80113408_option(s32 arg0, u32 arg1);
void func_80113424_option(s32 arg0);
void func_80113440_option(s32 arg0);
void func_8011345C_option(s32 arg0);
void func_80113490_option(s32 arg0);

/* fork C */
/* Model facing the camera: D_80114788_option[2] (func_8010FB40_option starts one; splat names the
   fields D_80114794_option .. D_801147B0_option). */
typedef struct OpFace {
    /* 0x00 */ Vec unk0;
    /* 0x0C */ Vec unkC;
    /* 0x18 */ Vec pos;       /* model position when started */
    /* 0x24 */ s32 model;     /* model slot (func_80113274_option) */
    /* 0x28 */ omObjData *obj; /* func_8010FA7C_option */
} OpFace; /* size = 0x2C */
extern OpFace D_80114788_option[2];
void func_8010FA7C_option(omObjData *obj); /* turns a model to face the camera */
/* Sound and music test page (the local tables of func_8010E8E0_option and func_8010F138_option). */
typedef struct OpSndItem {
    /* 0x00 */ s32 mes; /* message id, -1 for none */
    /* 0x04 */ s16 fx;  /* sound effect (func_8010E8E0_option) or song (func_8010F138_option), -1 for none */
} OpSndItem; /* size = 0x8 */
typedef struct OpSndPage {
    /* 0x00 */ s32 title;
    /* 0x04 */ OpSndItem item[9];
} OpSndPage; /* size = 0x4C */
s32 func_80113204_option(s32 pad); /* pad buttons (lhu D_800D0590_main[pad]); callers use the whole register */
/* Records boards (func_8010C3E4_option, func_8010D5B0_option): window rectangles relative to the board. */
typedef struct OpRect {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 w;
    /* 0x0C */ f32 h;
} OpRect; /* size = 0x10 */
/* Records board sprites and windows (a local of func_8010C3E4_option and func_8010D5B0_option). Each
   records page is 9 bytes of GwCommon (from unk_1D + 2 and unk_1D + 0x38): a count, then a byte per
   character. */
typedef struct OpRecSpr {
    /* 0x00 */ s16 win[12]; /* [0..5] used */
    /* 0x18 */ s16 icon[8];
    /* 0x28 */ struct {
        s16 tens;
        s16 ones;
    } digit[8];
} OpRecSpr; /* size = 0x48 */
/* Records page `page` of the table at GwCommon.unk_1D[off]: the count, and the byte of character n. */
#define OP_RECCOUNT(off, page) (((u8 *)GwCommon.unk_1D)[(off) + (page) * 9])
#define OP_RECVAL(off, page) (((OpRecVals *)&GwCommon.unk_1D[(off) + 1])[page].val)
/* A records row seen from its first character byte: the next row's count follows. */
typedef struct OpRecVals {
    /* 0x00 */ u8 val[8];
    /* 0x08 */ u8 next;
} OpRecVals; /* size = 0x9 */
extern s32 D_801138C8_option[9];   /* character icon -> record column (also the icon frame) */
extern OpRect D_801138EC_option[6];
extern s32 D_8011394C_option[9];
extern OpRect D_80113970_option[6];
extern char D_80113A50_option[]; /* "%2d" (first used by func_80107F50_option): a literal once that is C */
extern char D_80113A4C_option[]; /* "%d" (also func_80107F50_option): a literal once both users are C */

#endif
