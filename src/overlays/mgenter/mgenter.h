#ifndef MGENTER_H
#define MGENTER_H

#include "common.h"
#include "game/window.h"
#include "game/sprite.h"
#include "game/esprite.h"
#include "math.h"
#include "gcc/string.h"
#include "malloc.h"
#include "mallocblock.h"

/* Minigame entry screen (ovl_68): the title, the rules and the player/team setup before a minigame. */

/* The word before each MinigameTable entry (D_800A6D44_main), read with the table's 0x14 stride. */
typedef struct MgEntTableHead {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 type; /* D_800A6D44_main[].minigameType */
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u16 unk6; /* instruction message; 0x3800: variant count */
    /* 0x08 */ char unk8[0xC];
} MgEntTableHead;
extern MgEntTableHead D_800A6D40_main[];

/* gamemes.c's GAMEMES (a string drawn as one sprite per character) */
typedef struct MgEntMes {
    /* 0x00 */ u8 mesNo;
    /* 0x01 */ u8 stat;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 strGId[16];
    /* 0x40 */ s16 strSprId[16];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} MgEntMes; /* size 0x74 */

/* main */
extern s16 D_800A11E6_main;
extern struct {
    f32 unk00;
    s16 unk04;
} D_800CB890_main;
extern u8 D_800CE20A_main;
extern s16 D_800D1F36_main;
/* D_800D1FDC_main + 4 (that bss is 6 bytes; sprman.c declares its first word as a s32): entry screen run count */
extern s16 D_800D1FE0_main;
s16 func_800341C0_main(s8 mgIndex);
void func_800365E8_main(void *mes);
s32 func_80089750_main(f32 x);
s16 func_8002C834_main(HmfData *hmf, char *name);

/* .data */
extern f32 D_80109AA0_mgenter;
extern u16 D_80109AA4_mgenter; /* end request */
extern s16 D_80109AA6_mgenter; /* cancelled */
extern f32 D_80109AB0_mgenter; /* camera fov */

/* .bss */
extern s16 D_80109B20_mgenter;
extern s16 D_80109B22_mgenter; /* arrows shown (D_80109B23_mgenter: its low byte, as the compiler reads it) */
extern s16 D_80109B24_mgenter;
extern s16 D_80109B26_mgenter;
extern s16 D_80109B28_mgenter;
extern s16 D_80109B2A_mgenter; /* minigame index (0-based) */
extern s16 D_80109B2C_mgenter; /* chosen setting (D_80109B2D_mgenter: its low byte, as the compiler reads it) */
extern s16 D_80109B2E_mgenter;
extern s16 D_80109B30_mgenter; /* cursor step: -1, 0, 1 */
extern s16 D_80109B32_mgenter;
extern s16 D_80109B34_mgenter;
extern s16 D_80109B36_mgenter;
extern s16 D_80109B38_mgenter;
extern s16 D_80109B3A_mgenter;
extern f32 D_80109B64_mgenter; /* camera near */
extern s16 D_80109B74_mgenter; /* controlling pad */
extern s16 D_80109B76_mgenter;
extern f32 D_80109B78_mgenter; /* camera far */
extern s16 D_80109B7C_mgenter;
extern s16 D_80109B98_mgenter;

/* 468AC0 */
void func_801059D0_mgenter(void);
void func_80105C60_mgenter(void);
void func_80105CD8_mgenter(void);
void func_80106294_mgenter(void);
void func_80106568_mgenter(void);
void func_80106710_mgenter(u8 *str);
void func_8010677C_mgenter(void);
void func_80106BD0_mgenter(void);
void func_801079B4_mgenter(void);
void func_80107F0C_mgenter(void);
void func_80107E5C_mgenter(s16 win, s16 value, u8 *buf);
void func_80108560_mgenter(s16 x0, s16 y0, s16 x1, s16 y1);
void func_80108590_mgenter(void);
void func_801087C0_mgenter(void);
void func_80108934_mgenter(omObjData *obj);
void func_801089A0_mgenter(omObjData *obj);

/* 46BB50 */
void func_80108A60_mgenter(void);
void func_80109020_mgenter(void);
s32 func_801095F4_mgenter(void);
void func_801096EC_mgenter(s16 mes);
void func_80109820_mgenter(void);
void func_801098D8_mgenter(void);

#endif
