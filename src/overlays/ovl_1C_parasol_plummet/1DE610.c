#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"

// m2 pa: Parasol Plummet (4 players drift down on parasols and steer through the rings)

/* omObjData::data of a player (D_8010AB60_parasol_plummet, HuMemAllocTag 0x50) */
typedef struct PaPlayer {
    /* 0x00 */ f32 unk00; /* position */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ char unk11[3];
    /* 0x14 */ u32 unk14; /* flags: 1 frozen, 0x40 finished */
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24; /* player index */
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C; /* lane 0..3, then rank */
} PaPlayer; // Size 0x50

typedef struct PaS32x8 {
    s32 v[8];
} PaS32x8;

typedef struct PaS32x56 {
    s32 v[8][7];
} PaS32x56;

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004AD70_main(void);
void func_8001E500_main(s16, char*, char*);

extern u16 D_800D530C_main;
extern Vec Center;
extern Vec CRot;
extern f32 CZoom;

// minigame
u16 func_800E6E9C_minigame(void);

extern s32 D_800EBEB0_minigame[];

// LOCAL
void func_80105B94_parasol_plummet(omObjData* obj);
void func_80105E94_parasol_plummet(omObjData* obj);
void func_80105EC0_parasol_plummet(s32 arg0);
void func_80106418_parasol_plummet(omObjData* obj);
void func_8010687C_parasol_plummet(omObjData* obj);
void func_80107C30_parasol_plummet(void);
void func_80107D14_parasol_plummet(omObjData* obj);
void func_80107D30_parasol_plummet(void);
void func_80108178_parasol_plummet(omObjData* obj);
void func_8010856C_parasol_plummet(void);
void func_801089E0_parasol_plummet(omObjData* obj);
void func_80108F6C_parasol_plummet(void);
void func_80109604_parasol_plummet(void);
void func_8010A160_parasol_plummet(void);
void func_8010A75C_parasol_plummet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z);

extern s32 D_8010AB50_parasol_plummet; /* camera */
extern u8 D_8010AB54_parasol_plummet;
extern omObjData* D_8010AB60_parasol_plummet[4]; /* players */
extern u16 D_8010ABD0_parasol_plummet;
extern f32 D_8010AC50_parasol_plummet[4]; /* lanes taken */
extern s16 D_8010AC64_parasol_plummet;
extern u8 D_8010AC66_parasol_plummet; /* minigame state */

D_80111B50_vine_with_me_Struct D_8010A8A0_parasol_plummet = {
    0, 0, 1, 2, 0, 0, 9, { 0 }, 0, { 0 }, 0xB4, 0x384, -1, 0xD2, 0x3C,
};

s32 D_8010A8C8_parasol_plummet[] = { 2, 3, 7, 4, 5, 6, 8, 9, 0, 0 }; /* model directory by character */


INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801059A0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80105B94_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80105E94_parasol_plummet);

const PaS32x8 D_8010A908_parasol_plummet = { { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 } };
const PaS32x8 D_8010A928_parasol_plummet = { { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 } };
const PaS32x56 D_8010A948_parasol_plummet = { {
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
} };


INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80105EC0_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const f32 D_8010AA8C_parasol_plummet[] = { -450.0f, -150.0f, 150.0f, 450.0f };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106418_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106788_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010687C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010693C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801069E4_parasol_plummet);


INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106AB4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106CDC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106DB0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106E14_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const f32 D_8010AAB0_parasol_plummet[] = { -260.0f, -100.0f, 100.0f, 260.0f };
const f32 D_8010AAC0_parasol_plummet[] = { -210.0f, -70.0f, 70.0f, 210.0f };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801071B4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801074CC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801076D4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801079D8_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107A44_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107B5C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107B78_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107C30_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107C94_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107CD4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107D14_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107D30_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107E6C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010803C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108178_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801082CC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801083F8_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010856C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801086F0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108878_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const s32 D_8010AAE0_parasol_plummet[] = { 0, 1, 1 };
const s32 D_8010AAEC_parasol_plummet[] = { 360, 600, 840 };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801089E0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108C1C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108DD0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108F6C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108FFC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801090A8_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801092B0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801093D4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109604_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801096BC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010995C_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const f32 D_8010AAF8_parasol_plummet[] = { 3.0f, 3.0f, 3.0f };
const u8 D_8010AB04_parasol_plummet[] = { 1, 2, 3 };
const s16 D_8010AB08_parasol_plummet[] = { 0x21, 0x26, 0x21, 0x27, 0x3D, 4 };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109B38_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109D74_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109F7C_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const s16 D_8010AB14_parasol_plummet[] = { 0x20, 0xE0, 0x20, 0xE0 };
const s16 D_8010AB1C_parasol_plummet[] = { 0x18, 0x18, 0xD8, 0xD8 };
const s32 D_8010AB24_parasol_plummet[] = { 8, 9, 10, 11, 12, 13, 14, 15 };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A160_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const s16 D_8010AB44_parasol_plummet[] = { 0x20, 0xEC, 0x20, 0xEC };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A484_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A75C_parasol_plummet);
