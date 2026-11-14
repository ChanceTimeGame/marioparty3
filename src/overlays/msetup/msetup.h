#ifndef _MSETUP_H_
#define _MSETUP_H_

#include "common.h"

/* Overlay 0x78 `msetup`: the party setup screen (players and COM, characters, board, rules) that
   modesel's Star Lifts load. Two units, 501C00.c and 506F20.c. Struct layouts come from how the
   functions use them; a fork that learns more corrects them in a block at the end of this file. */

/* Model definition table entry (func_80106030_msetup walks it with a 0x28 stride). */
typedef struct MsModelDef {
    /* 0x00 */ s32 unk0; /* func_8000B108_main arg0 */
    /* 0x04 */ s32 unk4; /* func_8000B108_main arg1 */
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA; /* func_8001C814_main arg2 */
    /* 0x0C */ s32 unkC; /* 0: none, 1: pos/rot, 2: pos*5 / rot */
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
} MsModelDef; /* size = 0x28 */

/* Filled by func_80106030_msetup, one per MsModelDef. */
typedef struct MsModelSlot {
    /* 0x00 */ s16 model;
    /* 0x02 */ s16 unk2; /* HmfModelData[model].unk02 */
} MsModelSlot; /* size = 0x4 */

/* Camera key: func_80106260_msetup sets CRot/Center/CZoom and the perspective from one;
   func_801068F4_msetup steps through a table of them (0x24 stride; D_80119580_msetup is one 0x20 key). */
typedef struct MsCamKey {
    /* 0x00 */ Vec rot;    /* CRot */
    /* 0x0C */ Vec center; /* Center */
    /* 0x18 */ f32 zoom;   /* CZoom */
    /* 0x1C */ f32 fov;
    /* 0x20 */ f32 unk20;
} MsCamKey; /* size = 0x24 */

/* Called by func_801068F4_msetup each frame (func_80107F88_msetup). */
typedef void (*MsCamFunc)(s16, s16, s16);

/* One Star Lift (the 3D lift models); func_8010E32C_msetup fills an array of them on the stack. */
typedef struct MsLift {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    /* 0x18 */ s16 model;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
} MsLift; /* size = 0x24 */

/* user_data of the func_80117820_msetup process (D_8011A882_msetup, memset 6 by its creators):
   state indexes the D_80119FF0_msetup table of state functions, each returning the next state. */
typedef struct MsSetupWork {
    /* 0x00 */ s16 state;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4; /* also labelled D_8011A886_msetup */
} MsSetupWork; /* size = 0x6 */

/* main functions without a shared prototype (as the units declared them) */
void func_8000BBFC_main(u16, s16);
void func_8000BC48_main(u16, s32);
void func_8000BE5C_main(u16, f32, f32);

/* .data/.bss with a known type */
extern Process *D_80119420_msetup;   /* func_8010F2BC_msetup's process (user_data D_8011A8B0_msetup) */
extern omObjData *D_80119430_msetup; /* func_80107428_msetup */
extern omObjData *D_80119AF0_msetup; /* func_8010E21C_msetup */
extern u8 D_80119419_msetup;         /* .data 0x3 (padding); lbu,sb: 80105C4C */
extern s16 D_801198C0_msetup;        /* .data 0x4 (padding); lh,sh: 801059A0 8010BEF8 */
extern s32 D_80119E94_msetup[];      /* party mode board backgrounds */
extern s32 D_80119EAC_msetup[];      /* duel mode board backgrounds */
extern s32 D_80119EC4_msetup[];      /* party mode board descriptions */
extern s32 D_80119EE0_msetup[];      /* duel mode board descriptions */
extern MsSetupWork D_8011A882_msetup;
extern s16 D_8011A886_msetup[5];     /* .bss 0xA; begins at D_8011A882_msetup.unk4 (one object, two labels); indexed in 80109F7C */
extern s16 D_8011A8E0_msetup[4][4];  /* 80117820 stores [i][0..3]; splat also labels D_8011A8E2/E4/E6 */
extern s16 D_8011A948_msetup;        /* .bss split 0x1 + D_8011A949_msetup 0x7: lh reads both bytes */
extern s16 D_8011A990_msetup[2];
extern Vec D_8011A994_msetup;        /* splat also labels .y/.z as D_8011A998/D_8011A99C_msetup */
extern f32 D_8011A93C_msetup;        /* far plane (func_80106260_msetup perspective) */
extern f32 D_8011A940_msetup;        /* near plane */
extern u8 D_8011AA30_msetup[4];      /* per player; splat also labels D_8011AA31_msetup */
extern u8 D_8011AA34_msetup[4];      /* per player; splat also labels D_8011AA35_msetup */
extern u8 D_8011AA38_msetup[4];      /* per player */
extern u8 D_8011AA3C_msetup[4];      /* per player */
extern u8 D_8011AA45_msetup;         /* board index chosen */

/* Typed from their loads and stores only (sizes from the split); [] = several elements or indexed. */
extern u16 D_80119410_msetup;                    /* .data 0x2; lhu,sh: 801059A0 80105C4C 80107FB4 80108AB8 80109218 80109868 8010A3 */
extern s16 D_80119412_msetup;                    /* .data 0x2; lh,sh: 80105C4C 80107FB4 80108AB8 80109218 80109868 8010A35C 8010A7 */
extern f32 D_80119414_msetup;                    /* .data 0x4; lwc1,swc1: 801059A0 80106260 801068F4 */
extern s8 D_80119418_msetup;                     /* .data 0x1; lb: 80106320 */
extern s32 D_8011941C_msetup;                    /* .data 0x4; lw,sw: 801061E0 80106208 */
extern s32 D_80119424_msetup;                    /* .data 0x4; lw: 8010A35C 8010A7EC */
extern s32 D_80119428_msetup;                    /* .data 0x4; lw: 80108AB8 80109868 */
extern s32 D_8011942C_msetup;                    /* .data 0x4; lw: 80107FB4 80109218 */
extern u8 D_80119478_msetup[];                   /* .data 0x10; lbu: 80108F74 */
extern u8 D_80119488_msetup[];                   /* .data 0x10; lbu: 80108F74 */
extern u8 D_80119498_msetup[];                   /* .data 0x10; lbu: 80108F74 */
extern s32 D_801194A8_msetup[];                  /* .data 0x18; lw: 80109218 */
extern s32 D_801194C0_msetup[];                  /* .data 0x18; lw: 80109868 */
extern s32 D_801194D8_msetup[];                  /* .data 0x20; lw: 80109868 */
extern s32 D_801194F8_msetup[];                  /* .data 0x18; lw: 80109868 */
extern s32 D_80119964_msetup[];                  /* .data 0x20; lw: 8010BEF8 */
extern u8 D_80119984_msetup[];                   /* .data 0x8; lbu: 8010BEF8 */
extern s32 D_8011998C_msetup[];                  /* .data 0x20; lw: 8010BEF8 */
extern s32 D_801199AC_msetup[];                  /* .data 0x40; lw: 8010BEF8 */
extern s32 D_801199EC_msetup[];                  /* .data 0x20; lw: 8010BEF8 */
extern u16 D_80119A6C_msetup[];                  /* .data 0x10; lhu: 8010BA6C */
extern s32 D_80119A7C_msetup[];                  /* .data 0x10; lw: 8010BEF8 */
extern s32 D_80119A8C_msetup[];                  /* .data 0x28; lw: 8010BEF8 */
extern s32 D_80119AB4_msetup[];                  /* .data 0x14; lw: 8010BEF8 */
extern u8 D_80119AC8_msetup[];                   /* .data 0x4; lbu: 8010BEF8 */
extern u16 D_80119ACC_msetup[];                  /* .data 0x4; lhu: 8010BEF8 */
extern s32 D_80119AD0_msetup[8];                 /* .data 0x20; addiu,lw: 80110954 80111650 */
extern s32 D_80119B34_msetup[];                  /* .data 0x10; lw: 8010F87C */
extern s16 D_80119B60_msetup;                    /* .data 0x2; lh: 8011035C */
extern s16 D_80119B62_msetup[];                  /* .data 0x2E; lh: 8011035C */
extern s16 D_80119B90_msetup;                    /* .data 0x2; lh: 8011035C */
extern s16 D_80119B92_msetup;                    /* .data 0x2; lh: 8011035C */
extern s16 D_80119B94_msetup;                    /* .data 0x2; lh: 8011035C */
extern s16 D_80119B96_msetup[];                  /* .data 0xA; lh: 8011035C */
extern s32 D_80119BD0_msetup[];                  /* .data 0x20; lw: 8011035C */
extern s32 D_80119BF0_msetup[];                  /* .data 0x20; lw: 8011035C */
extern u8 D_80119C68_msetup[];                   /* .data 0x8; lbu: 80111650 */
extern s16 D_80119CB0_msetup[];                  /* .data 0x10; lh: 80110954 */
extern s32 D_80119D88_msetup[];                  /* .data 0x20; lw: 80111650 */
extern u16 D_80119E50_msetup[];                  /* .data 0x4; lhu: 80112804 */
extern u16 D_80119E54_msetup[];                  /* .data 0x4; lhu: 80112804 */
extern s32 D_80119F3C_msetup[];                  /* .data 0x10; lw: 801152C4 */
extern f32 D_80119F4C_msetup[];                  /* .data 0x14; lwc1: 801152C4 */
extern f32 D_80119F60_msetup[];                  /* .data 0xD; lwc1: 80115A9C */
extern u8 D_80119F6D_msetup[];                   /* .data 0xB; lbu: 80115EE0 */
extern u8 D_80119F79_msetup[];                   /* .data 0x13; lbu: 80115EE0 */
extern s32 D_80119F8C_msetup[];                  /* .data 0x8; lw: 80115A9C */
extern s32 D_80119FD4_msetup[];                  /* .data 0x8; lw: 801167B8 */
extern f32 D_8011A0B8_msetup[6];                 /* .data 0x18; addiu,lwc1: 8010F87C 801167B8 */
extern s16 D_8011A0D0_msetup[];                  /* .data 0xC; lh: 80117A3C */
extern u8 D_8011A3B0_msetup[];                   /* .data 0x8; lbu: 80118D48 */
extern s32 D_8011A508_msetup[];                  /* .data 0xC; lw: 80117A3C */
extern u8 D_8011A550_msetup[];                   /* .data 0x4; lbu: 80117A3C */
extern s16 D_8011A880_msetup;                    /* .bss 0x2; lh,lhu,sh: 80107840 80107964 80107A58 80107B8C 80107ECC 80107FB4 801084 */
extern s16 D_8011A890_msetup;                    /* .bss 0x2; lh,lhu,sh: 8010B5D0 8010B82C 8010B858 8010B8E0 8010B968 8010B998 8010B9 */
extern u16 D_8011A892_msetup;                    /* .bss 0x2; addiu,lhu: 8010B5D0 */
extern u16 D_8011A894_msetup[];                  /* .bss 0x4; lhu: 8010B5D0 */
extern s32 D_8011A900_msetup;                    /* .bss 0x4; lw,sw: 80111650 */
extern s16 D_8011A904_msetup;                    /* .bss 0x2; addiu,sh: 80111650 */
extern s16 D_8011A906_msetup;                    /* .bss 0x2; addiu,sh: 80110954 80111650 */
extern s16 D_8011A910_msetup[];                  /* .bss 0x10; lh,sh: 80118D48 */
extern s16 D_8011A938_msetup;                    /* .bss 0x2; lh,sh: 801059A0 80105C4C 8010A35C 8010BA6C 8010BEF8 8010EB94 801109 */
extern s16 D_8011A93A_msetup;                    /* .bss 0x2; lh,sh: 801059A0 80105C4C */
extern s16 D_8011A944_msetup;                    /* .bss 0x2; lh,sh: 801059A0 80105C4C 80105DB4 80107FB4 80108AB8 80109218 801098 */
extern s16 D_8011A946_msetup;                    /* .bss 0x2; lh,sh: 80105DB4 80107FB4 80108AB8 80109218 80109868 8010A35C 8010A7 */
extern f32 D_8011A9EC_msetup;                    /* .bss 0x4; swc1: 8010BA6C */
extern s16 D_8011A9F0_msetup;                    /* .bss 0x2; sh: 8010BA6C */
extern s16 D_8011A9F2_msetup[];                  /* .bss 0x14; lh,lhu,sh: 80107840 80107964 80107A58 80107B8C 80107FB4 801084C4 801085 */
extern s16 D_8011AA06_msetup[];                  /* .bss 0x28; lh: 801084C4 */
extern s16 D_8011AA2E_msetup;                    /* .bss 0x2; lh: 80107840 */
extern u8 D_8011AA40_msetup;                     /* .bss 0x1; addiu,lbu: 80105C4C 80109218 80109868 8010A7A0 8010A7EC 8010F87C 801116 */
extern u8 D_8011AA41_msetup;                     /* .bss 0x1; lbu: 80107964 801085D4 8010A10C 801132C4 */
extern u8 D_8011AA42_msetup;                     /* .bss 0x1; addiu,lbu,sb: 80106DF8 80115EE0 */
extern u8 D_8011AA43_msetup;                     /* .bss 0x1; lbu,sb: 80107E48 80107FB4 */
extern u8 D_8011AA47_msetup;                     /* .bss 0x1; lbu,sb: 80107D84 80107FB4 80108938 80108AB8 80109218 80109868 */
extern s16 D_8011AA48_msetup;                    /* .bss 0x2; lh,sh: 801059A0 80105C4C 80107FB4 80108AB8 80109218 80109868 8010A3 */
extern s16 D_8011AA4A_msetup;                    /* .bss 0x2; lh,sh: 80106FC0 80107428 80107FB4 80108AB8 80109218 80109868 8010A3 */
extern s16 D_8011AA4C_msetup[];                  /* .bss 0x4; lh,sh: 80105DB4 80107FB4 80108AB8 80109218 80109868 8010A35C 8010A7 */

/* Not declared here (address-only or mixed accesses; the fork that decompiles their users types
   them). "ptrs" = .data holding pointers (function tables: D_80119434/D_80119458/D_80119510/
   D_80119524 hold s16 (*)(s32) menu functions, D_80119FF0 the MsSetupWork state functions). */
/* 80119434(addiu ptrs,24) 80119458(addiu ptrs,20) 80119510(addiu ptrs,14) 80119524(addiu ptrs,10) 
80119534(addiu,14) 80119548(addiu,14) 8011955C(lw ptrs,24) 80119580(addiu,20) 801195A0(addiu,120) 
801196C0(addiu,fc) 801197BC(addiu,104) 801198C4(addiu,a0) 80119A0C(addiu,30) 80119A3C(addiu,18) 
80119A54(addiu,10) 80119A64(addiu,8) 80119B0C(addiu,14) 80119B20(addiu,c) 80119B2C(addiu,8) 
80119B44(addiu,1c) 80119BA0(addiu,30) 80119C10(addiu,18) 80119C28(addiu,20) 80119C48(addiu,20) 80119C70(lw 
ptrs,40) 80119CC0(addiu,20) 80119CE0(addiu,20) 80119D00(addiu,20) 80119D20(addiu,48) 80119D68(lw ptrs,20) 
80119DA8(addiu,10) 80119DB8(addiu,10) 80119DC8(addiu,20) 80119DFC(addiu,10) 80119E0C(addiu ptrs,c) 
80119E18(addiu,8) 80119E20(addiu ptrs,18) 80119E38(addiu,18) 80119E58(addiu,c) 80119E64(addiu,c) 
80119E70(addiu,c) 80119E7C(addiu,c) 80119E88(addiu,c) 80119E94(addiu,18) 80119EAC(addiu,18) 
80119EFC(addiu,18) 80119F14(addiu,28) 80119F78(addiu,1) 80119F94(addiu,20) 80119FB4(addiu,20) 
80119FDC(addiu,8) 80119FE4(addiu,c) 80119FF0(addiu ptrs,38) 8011A028(addiu,30) 8011A058(addiu,20) 
8011A078(addiu,20) 8011A098(addiu,10) 8011A0A8(addiu,10) 8011A16C(lw ptrs,c) 8011A178(addiu,a0) 
8011A218(addiu,a0) 8011A2B8(addiu,b0) 8011A368(addiu,24) 8011A38C(addiu,24) 8011A3B8(addiu,70) 
8011A428(addiu,50) 8011A478(addiu,50) 8011A4C8(addiu,40) 8011A514(addiu,18) 8011A544(lw ptrs,c) 
8011A554(addiu,2c) 8011A898(addiu,18) 8011A8B0(addiu,30) 8011A908(lwc1/sw/swc1,8) 8011A920(addiu,c) 
8011A92C(addiu,c) 8011A950(addiu,40) 8011A9A0(addiu,40) 
8011A9E0(addiu,c) 8011AA44(addiu,1) */

/* 501C00.c and 506F20.c: all 130 functions. Widths from m2c and how each function reads a0-a3/
   f12/f14 and its callers use v0/f0. */
void func_801059A0_msetup(void);
void func_80105C4C_msetup(omObjData *obj);
void func_80105DB4_msetup(omObjData *obj);
void func_80105E90_msetup(s32 *arg0);
void func_80105F7C_msetup(MsModelDef *def, s16 model);
void func_80106030_msetup(MsModelDef *defs, MsModelSlot *slots, s32 count);
u32 func_8010610C_msetup(u32 seed); /* random step (MP1 BoxMountainMayhem) */
u32 func_801061E0_msetup(void); /* D_8011941C_msetup = func_8010610C_msetup(it) */
u32 func_80106208_msetup(u32 arg0);
void func_80106260_msetup(MsCamKey *key); /* camera set */
void func_80106320_msetup(void); /* process */
void func_801068F4_msetup(MsCamKey *keys, f32 speed, MsCamFunc func);
void func_80106DF8_msetup(void);
f32 func_80106FC0_msetup(void *arg0, s32 arg1, f32 arg2);
void func_801070FC_msetup(omObjData *obj);
omObjData * func_80107428_msetup(void);
s16 func_801077E0_msetup(s32 arg0);
s16 func_80107840_msetup(s32 arg0);
s16 func_80107964_msetup(s32 arg0);
s32 func_80107A58_msetup(s32 arg0);
s16 func_80107B8C_msetup(s32 arg0);
s16 func_80107CF4_msetup(s32 arg0);
s16 func_80107D84_msetup(s32 arg0);
s16 func_80107E48_msetup(s32 arg0);
s32 func_80107ECC_msetup(s32 arg0);
void func_80107F88_msetup(s16 arg0, s16 arg1, s16 arg2); /* MsCamFunc */
void func_80107FB4_msetup(void);
s16 func_80108464_msetup(s32 arg0);
s16 func_801084C4_msetup(s32 arg0);
s16 func_801085D4_msetup(s32 arg0);
s32 func_801086C8_msetup(s32 arg0);
s16 func_801087F4_msetup(s32 arg0);
s16 func_801088A8_msetup(s32 arg0);
s16 func_80108938_msetup(s32 arg0);
s32 func_801089FC_msetup(s32 arg0);
void func_80108AB8_msetup(void);
void func_80108F74_msetup(void);
void func_80109218_msetup(void);
void func_80109868_msetup(void);
s16 func_80109EA0_msetup(s32 arg0);
s16 func_80109F04_msetup(s32 arg0);
s16 func_80109F7C_msetup(s32 arg0);
s16 func_8010A10C_msetup(s32 arg0);
s32 func_8010A204_msetup(s32 arg0);
s32 func_8010A2B0_msetup(s32 arg0);
void func_8010A35C_msetup(s32 arg0);
void func_8010A780_msetup(void);
void func_8010A7A0_msetup(void);
void func_8010A7EC_msetup(s16 arg0);
void func_8010AC78_msetup(void);
void func_8010AC94_msetup(void);
void func_8010ACB0_msetup(void);
void func_8010ACC0_msetup(s16 arg0, s16 arg1, s32 arg2); /* arg2: the caller sets a2 */
void func_8010AF40_msetup(void *arg0, s32 arg1, s16 *arg2);
void func_8010B1F4_msetup(void); /* process */
s16 func_8010B388_msetup(s16 arg0, void *arg1, s32 arg2, s8 *arg3);
void func_8010B4B8_msetup(s16 arg0, s16 *arg1, s16 arg2);
s16 func_8010B588_msetup(void);
void func_8010B5D0_msetup(void); /* process */
void func_8010B82C_msetup(s32 arg0);
void func_8010B858_msetup(void);
s32 func_8010B8E0_msetup(void);
void func_8010B968_msetup(u32 arg0, s8 arg1);
void func_8010B998_msetup(void);
void func_8010B9B8_msetup(s32 arg0, s32 arg1);
void func_8010BA10_msetup(s32 arg0, s32 arg1);
s16 func_8010BA3C_msetup(void);
void func_8010BA6C_msetup(s16 arg0, s16 arg1);
void func_8010BBF4_msetup(s16 arg0);
void func_8010BC18_msetup(s16 arg0, s16 arg1);
void func_8010BE8C_msetup(s16 arg0);
s16 func_8010BEB0_msetup(s16 arg0, s16 arg1);
void func_8010BEF8_msetup(void); /* process */
s16 func_8010CAF0_msetup(s32 arg0, s32 arg1);
void func_8010CC70_msetup(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 func_8010CD14_msetup(s16 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8010CE8C_msetup(s16 model); /* func_80013390_main hook */
void func_8010D060_msetup(void *arg0, s32 arg1);
void func_8010D094_msetup(void *arg0, s32 arg1);
s32 func_8010D0C8_msetup(s16 arg0, s32 arg1);
s16 func_8010D234_msetup(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5);
s16 func_8010D4DC_msetup(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s32 arg5); /* arg1 unused */
s16 func_8010D5EC_msetup(s16 arg0);
s32 func_8010D684_msetup(s16 arg0, s16 *arg1);
void func_8010D6D0_msetup(void); /* process */
void func_8010DAC4_msetup(omObjData *obj);
void func_8010DDD8_msetup(omObjData *obj);
omObjData * func_8010DE38_msetup(s32 arg0, s32 arg1, s32 arg2);
s16 func_8010E00C_msetup(omObjData *obj, s16 arg1);
void func_8010E044_msetup(omObjData *obj, s16 arg1, s16 arg2, f32 x, f32 y, f32 z);
void func_8010E09C_msetup(omObjData *obj);
omObjData * func_8010E21C_msetup(void);
void func_8010E32C_msetup(MsLift *lifts, s32 count, f32 rotY, s32 link);
void func_8010E4BC_msetup(MsLift *lifts, s32 count, f32 rotY);
void func_8010E4D8_msetup(MsLift *lifts, s32 count);
void func_8010E52C_msetup(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, f32 arg6, f32 arg7);
void func_8010E8C8_msetup(MsLift *lifts, s32 count, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7);
void func_8010EB94_msetup(void); /* process */
Process *func_8010F2BC_msetup(void); /* board-preview process, user_data D_8011A8B0_msetup */
s16 func_8010F2F4_msetup(Process *proc, s16 arg1);
void func_8010F320_msetup(Process *proc, s32 idx, s16 arg2, s16 arg3);
void func_8010F33C_msetup(s16 model, Vec *out, f32 (*mtx)[4]);
void func_8010F43C_msetup(s16 model, s32 arg1, Vec2f *out);
void func_8010F4E0_msetup(s32 arg0, s16 arg1, s32 arg2);
s32 func_8010F87C_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
void func_8011035C_msetup(void); /* process */
void func_80110954_msetup(void); /* process */
s32 func_80111650_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
void func_80112804_msetup(void); /* process */
s16 func_80112E08_msetup(s16 arg0, s16 *arg1, void *arg2);
s16 func_80112F5C_msetup(s16 *arg0, u16 arg1, s16 *arg2, void *arg3);
s32 func_801132C4_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s32 func_801138F8_msetup(void *arg0, s32 arg1, s32 *arg2, s16 arg3);
s16 func_80113DEC_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s16 func_80113E20_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s16 func_80113E54_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s16 func_80113E88_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s32 func_80113ED4_msetup(MsSetupWork *work); /* state 8: board select */
s32 func_801145D0_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s32 func_80114AA0_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s32 func_801150A0_msetup(s16 arg0);
s16 func_801152C4_msetup(s16 arg0, s32 arg1, void *arg2, s16 *arg3, u16 arg4); /* arg1 unused */
s32 func_801157B8_msetup(s16 arg0, s16 arg1, s16 *arg2, s16 arg3, void *arg4, void *arg5);
s16 func_80115A9C_msetup(s16 arg0, s32 arg1, void *arg2, s16 *arg3, s32 arg4); /* arg1 unused */
void func_80115E78_msetup(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 func_80115EE0_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s32 func_801167B8_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s32 func_80116FE0_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
s32 func_80117818_msetup(MsSetupWork *work); /* state (D_80119FF0_msetup) */
void func_80117820_msetup(void); /* process: MsSetupWork state machine (D_80119FF0_msetup) */
void func_80117910_msetup(s16 arg0, s16 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6); /* arg3 unused */
void func_80117A3C_msetup(void); /* process */
void func_80118D48_msetup(void);

/* fork C */
/* user_data of the func_8010D6D0_msetup sprite process (func_801132C4_msetup and
   func_80117A3C_msetup fill one per sprite). */
typedef struct MsSprWork {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 (*pos)[2]; /* positions, indexed by idx; may be NULL */
    /* 0x08 */ s32 file;      /* func_8000B838_main data id */
    /* 0x0C */ s16 idx;
    /* 0x0E */ s16 state;     /* 0 idle, 1 fade in, 2 fade out, -1 kill (then 100) */
    /* 0x10 */ s16 time;      /* frames per move (0: jump) */
    /* 0x12 */ s16 prio;
} MsSprWork; /* size = 0x14 */

/* omObjData::unk_5C of the func_8010DE38_msetup arrows object (HuMemAllocTag 0x10); model[0..1]
   esprite slots, model[2..3] their sprites; work[0] request, [1] rate/frames, [2] alpha or arrow
   index, [3] current state. */
typedef struct MsArrowWork {
    /* 0x00 */ f32 angle;
    /* 0x04 */ f32 speed;
    /* 0x08 */ s16 pos[2][2]; /* left arrow x,y; right arrow x,y */
} MsArrowWork; /* size = 0x10 */

/* omObjData::data of the func_8010E21C_msetup particle object (D_80119AF0_msetup; HuMemAllocTag
   0x3C): up to four emitters, each spawning at pos[i] +- range[i]/2 in x and z every frame. */
typedef struct MsEmitWork {
    /* 0x00 */ Vec pos[4];
    /* 0x30 */ s16 range[4];
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 count; /* func_8010E00C_msetup clamps it to 4 */
} MsEmitWork; /* size = 0x3C */

/* The fields of hmfman's particle work (HmfModelData[model].unkBC; 13F90.c's HmfFxWork, D7A0.c's
   FxWork) that func_8010E21C_msetup sets. */
typedef struct MsFxWork {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ f32 spread;
    /* 0x14 */ f32 timer;
    /* 0x18 */ void (*unk18)(s16);
    /* 0x1C */ Vec origin;
} MsFxWork; /* partial; size 0x5C */
#define MS_FX_WORK(model) ((MsFxWork *)HmfModelData[model].unkBC)

/* func_8000CD00_main arguments (f32 in a1-a3): the particle colour/scale set when work[1] changes */
extern f32 D_80119AF4_msetup;
extern f32 D_80119AF8_msetup;
extern f32 D_80119AFC_msetup[]; /* .data 0x10; only [0] read */

#endif
