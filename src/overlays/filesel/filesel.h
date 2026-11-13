#ifndef _FILESEL_H_
#define _FILESEL_H_

#include "common.h"

/* Overlay 0x79 `filesel`: the save-file select screen. Its sprite, model and window helpers
   (func_80105CB0..func_801078F4) are the same library as opening's (523FD0.c, opSpr* / opModel*),
   with 64 model slots instead of 160. */

#define FS_FILE_USED 0x91 /* UnkFileSelect.unk_00 of a file that holds a save */

/* Sprite slot: D_80112ED0_filesel[64]. */
typedef struct FsSpr {
    /* 0x00 */ s16 espId; /* esprite slot, -1 when free */
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ f32 scaleX;
    /* 0x10 */ f32 scaleY;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18; /* 0xFF at init */
} FsSpr; /* size = 0x1C */

/* Model slot: D_80113650_filesel[64]. */
typedef struct FsModel {
    /* 0x00 */ s16 model;  /* -1 when free */
    /* 0x02 */ s16 motion; /* -1 when free */
    /* 0x04 */ s32 pos[3]; /* retail keeps the position truncated to integers */
    /* 0x10 */ Vec scale;
    /* 0x1C */ Vec rot;
    /* 0x28 */ s32 unk28;
} FsModel; /* size = 0x2C */

/* Window slot: D_80114158_filesel[32]. */
typedef struct UnkFileSelect2 {
    /* 0x00 */ s16 unk_00; /* window id, -1 when free */
    /* 0x04 */ u32 unk_04; /* heap copy of the message (address above 0x80000000), or 0 */
    /* 0x08 */ s32 unk_08; /* window type (3 = choice window) */
} UnkFileSelect2; /* size = 0xC */

/* Save file summary: D_801142DC_filesel[3]. */
typedef struct UnkFileSelect {
    /* 0x00 */ u8 unk_00; /* FS_FILE_USED when the file holds a save */
    /* 0x01 */ u8 unk_01[0xB]; /* name */
    /* 0x0C */ char unk_0C[0x78];
} UnkFileSelect; /* size = 0x84 */

/* .bss */
extern FsSpr D_80112ED0_filesel[64];
extern s16 D_801135D0_filesel[64]; /* sprite animations */
extern FsModel D_80113650_filesel[64];
extern s16 D_80114150_filesel; /* background animation */
extern s16 D_80114152_filesel; /* background esprite */
extern UnkFileSelect2 D_80114158_filesel[32];
extern UnkFileSelect D_801142DC_filesel[3];

/* main functions without a shared prototype */
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BCC8_main(u16 spriteId, s32 arg1);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
s32 func_800452A0_main(void *arg0, void *arg1);
void func_800601BC_main(s16 win, s32 arg1, s8 arg2);

/* 516AE0.c */
void func_801059A0_filesel(void);
void func_801059D0_filesel(void); /* object/camera/viewport init (opObjectInit) */
void func_80105BC0_filesel(void);
void func_80105BF0_filesel(void);
void func_80105C1C_filesel(void);
s16 func_80105CB0_filesel(s32 arg0);
s16 func_80105CC4_filesel(s32 arg0);
void func_80105CE0_filesel(s32 no, s32 dataNum); /* sprite anim create */
void func_80105D18_filesel(s32 arg0);
void func_80105D70_filesel(s32 no, s32 animNo); /* esprite create */
void func_80105DD8_filesel(s32 arg0);
void func_80105E48_filesel(s32 no, s32 dataNum); /* sprite create */
void func_80105E7C_filesel(s32 no, s32 dataNum); /* BG sprite create */
void func_80105EC0_filesel(s32 arg0);
void func_80105EEC_filesel(void);
void func_80105F24_filesel(s32 arg0);
void func_80105F54_filesel(s32 arg0);
void func_80105F84_filesel(void);
void func_80105FA0_filesel(void);
void func_80105FBC_filesel(s32 no, s32 x, s32 y); /* sprite pos set */
void func_80106014_filesel(s32 no, s32 *x, s32 *y);
void func_80106044_filesel(s32 no, f32 x, f32 y); /* sprite scale set */
void func_80106094_filesel(s32 no, u16 alpha);
void func_801060CC_filesel(s32 no, u16 attr); /* sprite attr set */
void func_80106100_filesel(s32 no, u16 attr); /* sprite attr reset */
void func_80106134_filesel(s32 no, u16 arg1);
void func_80106168_filesel(s32 no, u16 arg1, u16 arg2);
void func_801061D4_filesel(void);
void func_80106220_filesel(s32 no, s32 arg1, s32 dataNum); /* model create */
void func_801062BC_filesel(s32 no, s32 dataNum, s32 arg2); /* motion create */
void func_80106344_filesel(s32 arg0);
void func_801063F4_filesel(void);
s16 func_8010642C_filesel(s32 arg0);
s16 func_80106450_filesel(s32 arg0);
void func_80106474_filesel(s32 no, f32 x, f32 y, f32 z); /* model rot set */
void func_801064DC_filesel(s32 no, f32 x, f32 y, f32 z); /* model pos set */
void func_80106550_filesel(s32 no, f32 x, f32 y, f32 z); /* model scale set */
void func_801065B8_filesel(s32 no, f32 *x, f32 *y, f32 *z); /* model pos get */
void func_8010660C_filesel(s32 no, f32 *x, f32 *y, f32 *z); /* model rot get */
void func_80106654_filesel(s32 no, f32 *x, f32 *y, f32 *z); /* model scale get */
void func_8010669C_filesel(s32 arg0);
void func_801066DC_filesel(s32 arg0);
void func_8010671C_filesel(s32 no, s16 flag);
void func_80106760_filesel(s32 no, s32 motNo, s16 arg2, s16 arg3, s16 arg4);
void func_801067D0_filesel(s32 no, s16 arg1);
void func_80106814_filesel(s32 no, f32 speed);
void func_8010684C_filesel(s32 no, u32 time);
void func_801068B0_filesel(s32 arg0);
s32 func_80106950_filesel(s32 arg0);
void func_801069D8_filesel(s32 no, s32 motNo, s16 flag);
void func_80106A48_filesel(s32 dataNum);
void func_80106AAC_filesel(void);
u32 func_80106AD8_filesel(u32 mes); /* heap copy of a message when mes is a pointer */
void func_80106B40_filesel(s32 no, u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type); /* window create */
s16 func_80106D8C_filesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_80106ED8_filesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_80107040_filesel(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_801071E8_filesel(u32 mes, s16 x, s16 y, s16 type);
s16 func_801072B4_filesel(u32 mes, s16 x, s16 y, s16 type);
s16 func_80107380_filesel(u32 mes, s16 x, s16 y, s16 type);
void func_8010744C_filesel(void);
void func_80107490_filesel(s32 no); /* window kill */
void func_80107574_filesel(void);
void func_801075D8_filesel(s32 no, f32 x, f32 y);
void func_80107608_filesel(s32 no, f32 x, f32 y);
void func_80107670_filesel(s32 arg0);
void func_801076A0_filesel(s32 arg0);
void func_8010779C_filesel(s32 no, s8 arg1, s32 arg2);
s32 func_801077D8_filesel(s32 no, s16 arg1, s32 arg2);
s16 func_80107810_filesel(s32 no); /* window id get */
void func_8010782C_filesel(s32 no); /* wait for window */
void func_80107880_filesel(s32 btn); /* wait for button */
void func_801078BC_filesel(s32 no, s16 arg1);
u16 func_801078F4_filesel(s32 val); /* debug value print */
void func_80107AA8_filesel(void);
void func_80107C50_filesel(void);
void func_80107C84_filesel(void);
void func_80107CF8_filesel(void);
void func_801083AC_filesel(void);
void func_80108440_filesel(void);
u32 func_8010846C_filesel(void);
void func_80108878_filesel(void);
void func_801088DC_filesel(void);
void func_80108A94_filesel(void);
void func_80108C34_filesel(void);
void func_80108D74_filesel(void);
u32 func_80108EB8_filesel(void);
u32 func_801099A8_filesel(u32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80109B2C_filesel(void);
void func_8010A028_filesel(void);
void func_8010A680_filesel(s32 no, f32 x, f32 y, f32 z);
void func_8010A7D8_filesel(s16 arg0);
void func_8010A978_filesel(s32 arg0);
void func_8010A9B4_filesel(s32 arg0, u32 arg1, s32 *arg2, s32 *arg3);
void func_8010AB1C_filesel(s32 arg0, u32 arg1);
void func_8010AB60_filesel(s32 arg0, u32 arg1);
s32 func_8010AC58_filesel(s32 arg0);
s32 func_8010B4D0_filesel(s32 arg0, s32 arg1);
s32 func_8010B4FC_filesel(s32 arg0, s32 arg1);
s32 func_8010B528_filesel(s32 arg0, s32 arg1);
void func_8010B554_filesel(void *arg0);
void func_8010B598_filesel(void *arg0);
s32 func_8010B5D4_filesel(s32 arg0, s32 arg1, s32 arg2, s16 *arg3, s16 *arg4);
void func_8010B684_filesel(s32 arg0);
void func_8010B6F4_filesel(s32 arg0);
void func_8010B80C_filesel(s32 arg0);
s32 func_8010B998_filesel(s32 arg0);
void func_8010BDC4_filesel(void);
void func_8010BE14_filesel(void);
s32 func_8010BE30_filesel(s32 arg0);
s32 func_8010C25C_filesel(s32 arg0);
s32 func_8010C688_filesel(s32 arg0);
s32 func_8010C9B4_filesel(u32 arg0);
s32 func_8010CCA8_filesel(void);
void func_8010D13C_filesel(s32 arg0);
void func_8010D660_filesel(s32 arg0);
void func_8010DD54_filesel(void);
void func_8010DDC0_filesel(s32 arg0);
void func_8010DEEC_filesel(void);
void func_8010DF58_filesel(void);
void func_8010DFF4_filesel(s32 arg0);
void func_8010E1B4_filesel(void);
void func_8010E250_filesel(void *arg0, void *arg1, f32 arg2, void *arg3, void *arg4, void *arg5);
void func_8010E740_filesel(s32 arg0);
void func_8010E864_filesel(void);
void func_8010F10C_filesel(void);
void func_8010F12C_filesel(void);
void func_8010F168_filesel(void);
void func_8010F5C8_filesel(void);
void func_8010F65C_filesel(void);
void func_8010F678_filesel(u32 arg0);
void func_8010F760_filesel(s32 arg0, s32 arg1);
void func_8010F844_filesel(s32 arg0);
void func_8010F874_filesel(s32 arg0);
void func_8010F8A4_filesel(omObjData *arg0);
omObjData *func_8010FBE0_filesel(u32 arg0, u32 arg1);
void func_8010FC58_filesel(omObjData *arg0);
void func_8010FF48_filesel(u32 arg0, u32 arg1);
void func_8010FFA0_filesel(omObjData *arg0);
void func_801102F0_filesel(s32 arg0);
void func_80110320_filesel(u32 arg0, s32 arg1);
void func_801103A0_filesel(omObjData *arg0);
void func_801106FC_filesel(s32 arg0);
void func_8011072C_filesel(u32 arg0, s32 arg1);
void func_801107AC_filesel(omObjData *arg0);
void func_80110B4C_filesel(s32 arg0);
omObjData *func_80110B7C_filesel(u32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4);
void func_80110C84_filesel(void);
void func_80110CC0_filesel(s32 arg0);
void func_80110D0C_filesel(omObjData *arg0);
void func_80110E70_filesel(u32 arg0, omObjFunc func);
void func_80110F04_filesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80110FB0_filesel(u32 arg0);
void func_80111004_filesel(omObjData *arg0);
void func_801110F0_filesel(u32 arg0);
void func_80111144_filesel(omObjData *arg0);
void func_8011132C_filesel(s32 arg0);
void func_8011139C_filesel(s32 arg0);
void func_801113E8_filesel(omObjData *arg0);
void func_80111660_filesel(s32 arg0, s32 arg1, s32 arg2);
void func_80111790_filesel(omObjData *arg0);
omObjData *func_80111944_filesel(u32 arg0);
void func_801119F4_filesel(void);
s32 func_80111A08_filesel(s32 arg0);
s32 func_80111B14_filesel(s32 arg0);
void func_80111C30_filesel(void);
void func_80111CBC_filesel(s32 arg0);
void func_80111E78_filesel(s32 arg0);
void func_80111FFC_filesel(s32 arg0);
void func_80112184_filesel(s32 arg0, s32 arg1, u8 *arg2, u8 *arg3);
void func_801122B0_filesel(s32 arg0);
s32 func_80112508_filesel(s32 arg0, s32 arg1);
void func_80112584_filesel(u32 arg0);
s32 func_801125E8_filesel(s32 arg0);
void func_80112630_filesel(void);
void func_80112684_filesel(void);
void func_801126C0_filesel(s32 arg0, u8 *arg1, u8 *arg2);
void func_80112758_filesel(void);
void func_801076D0_filesel(s32 no, u32 mes); /* window message set */
s32 func_80108834_filesel(void); /* count of used save files */
u32 func_80109570_filesel(s32 arg0);
s32 func_80109904_filesel(s32 arg0);
s32 func_80109968_filesel(s32 arg0);
void func_8010AB58_filesel(s32 arg0, u32 arg1);
s32 func_80112494_filesel(s32 arg0, u8 *arg1);


/* fork C */
/* Name-entry keyboard state: 0x80114478..0x801144D4 (splat split it into D_80114478..D_801144D0). */
typedef struct FsKbd {
    /* 0x00 */ s32 unk00;     /* D_80114478 */
    /* 0x04 */ s32 unk04;     /* D_8011447C */
    /* 0x08 */ s32 unk08;     /* D_80114480 */
    /* 0x0C */ s32 col;       /* D_80114484: 0..12 */
    /* 0x10 */ s32 row;       /* D_80114488: 0..4 */
    /* 0x14 */ s32 unk14;     /* D_8011448C */
    /* 0x18 */ u16 name[16];  /* D_80114490: the name being typed, 0-terminated */
    /* 0x38 */ u16 unk38[16]; /* D_801144B0 */
    /* 0x58 */ s32 len;       /* D_801144D0: characters typed, at most 5 */
} FsKbd; /* size = 0x5C */
extern FsKbd D_80114478_filesel;
extern s32 D_80114470_filesel; /* the name changed */

#endif
