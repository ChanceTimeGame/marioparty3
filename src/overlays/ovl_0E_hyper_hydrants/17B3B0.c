#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"

// hh A: Hyper Hydrants (2 vs 2, split screen: each team pumps a hydrant to put out its fire)

typedef func_800E1BA8_minigame_ObjData MgWork;

/* The minigame control block (as All Fired Up's AfCtrl) */
typedef struct HhCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
} HhCtrl; /* size 0x28 */

/* MgWork::unk158 of a player */
typedef struct HhPlayer {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ char unk14[4];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
} HhPlayer; /* size 0x20 */

// main
s32 func_8000B638_main(void);
void func_8000B710_main(s32);
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004AD70_main(void);
f32 HuSqrtf(f32 x);

extern s32 D_800A178C_main[][6];
extern u16 D_800A1906_main; /* music state flags */
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;
extern s8 D_800CBB6E_main[];  /* CPU stick x */
extern s8 D_800D20A1_main[];  /* CPU stick y */
extern u16 D_800D5558_main[]; /* CPU buttons */

// minigame
void func_800DDD94_minigame(omObjData* obj);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1490_minigame(u16 arg0);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E1804_minigame(void);
void func_800E1840_minigame(void);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s16 D_800EB934_minigame;
extern s32 D_800EBEB0_minigame[];

// LOCAL

void func_801059A0_hyper_hydrants(void);
void func_80105CB4_hyper_hydrants(HhCtrl* ctrl);
void func_80105D44_hyper_hydrants(omObjData* obj);
void func_80105D68_hyper_hydrants(s8 cam);
void func_80105EB0_hyper_hydrants(s8 cam);
void func_80105FC8_hyper_hydrants(void);
void func_801060F8_hyper_hydrants(omObjData* obj);
void func_80106238_hyper_hydrants(omObjData* obj);
void func_80106A50_hyper_hydrants(omObjData* obj);
void func_80107238_hyper_hydrants(omObjData* obj);
void func_801078B8_hyper_hydrants(omObjData* obj);
void func_80107A90_hyper_hydrants(omObjData* obj);
void func_80108788_hyper_hydrants(omObjData* obj);
void func_80108F34_hyper_hydrants(omObjData* obj);
void func_801091B0_hyper_hydrants(omObjData* obj);
void func_80109484_hyper_hydrants(omObjData* obj);
void func_80109588_hyper_hydrants(omObjData* obj);
void func_801099A0_hyper_hydrants(omObjData* obj);
void func_80109B30_hyper_hydrants(omObjData* obj);
void func_80109E44_hyper_hydrants(omObjData* obj);
void func_8010A2D4_hyper_hydrants(omObjData* obj);
void func_8010A458_hyper_hydrants(omObjData* obj);
void func_8010A68C_hyper_hydrants(omObjData* obj);
void func_8010AB34_hyper_hydrants(omObjData* obj);
void func_8010AE08_hyper_hydrants(omObjData* obj);
void func_8010B2FC_hyper_hydrants(omObjData* obj);
void func_8010B38C_hyper_hydrants(void);
void func_8010B658_hyper_hydrants(omObjData* obj);
void func_8010B8B0_hyper_hydrants(omObjData* obj);

extern Vec D_8010BDE0_hyper_hydrants;
extern Vec D_8010BDEC_hyper_hydrants;
extern Vec D_8010BDF8_hyper_hydrants;
extern Vec D_8010BE04_hyper_hydrants;
extern f32 D_8010BE28_hyper_hydrants;
extern f32 D_8010BE2C_hyper_hydrants;
extern s8 D_8010BE24_hyper_hydrants;
extern s8 D_8010BE25_hyper_hydrants;
extern s8 D_8010BE34_hyper_hydrants;
extern s8 D_8010BE35_hyper_hydrants;
extern s32 D_8010BE30_hyper_hydrants;

extern s8 D_8010BF40_hyper_hydrants;
extern HhCtrl D_8010BF60_hyper_hydrants;
extern u8 D_8010BFA8_hyper_hydrants;
extern u8 D_8010BFA9_hyper_hydrants;
extern u8 D_8010BFAA_hyper_hydrants;
extern u8 D_8010BFAB_hyper_hydrants;
extern s8 D_8010BFAC_hyper_hydrants[2];
extern omObjData* D_8010BFE0_hyper_hydrants[2];
extern omObjData* D_8010BFE8_hyper_hydrants[2][5];
extern s8 D_8010C010_hyper_hydrants;
extern s16 D_8010C022_hyper_hydrants[2];


void func_801059A0_hyper_hydrants(void) {
    omObjData* obj;
    s32 i;
    s32 j;

    Hu3DAnimInit(0x20);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105FC8_hyper_hydrants();
    func_80105CB4_hyper_hydrants(&D_8010BF60_hyper_hydrants);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010BF60_hyper_hydrants);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_80105D44_hyper_hydrants);
    omSetStatBit(obj, 0xA0);
    func_80105D44_hyper_hydrants(obj);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_801060F8_hyper_hydrants), 0xA0);
    for (i = 0; i < 2; i++) {
        D_8010BFE0_hyper_hydrants[i] = omAddObj(0, 2, 0, -1, func_80108F34_hyper_hydrants);
    }
    D_8010C010_hyper_hydrants = (rand8() * 3) >> 8;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 5; i++) {
            D_8010BFE8_hyper_hydrants[j][i] = omAddObj(0, 3, 0, -1, func_80109588_hyper_hydrants);
        }
    }
    for (i = 0; i < 2; i++) {
        omAddObj(1, 10, 0, -1, func_801078B8_hyper_hydrants);
    }
    omAddObj(1, 0, 0, -1, func_8010AE08_hyper_hydrants);
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 3, 5, -1, func_80106238_hyper_hydrants);
    }
    for (i = 0; i < 2; i++) {
        omAddObj(3, 6, 0, -1, func_8010A68C_hyper_hydrants);
    }
    omAddObj(3, 0, 0, -1, func_8010B658_hyper_hydrants);
    WipeCreateIn(0xFF, 16);
}

void func_80105CB4_hyper_hydrants(HhCtrl* ctrl) {
    s32 i;

    D_800EB932_minigame = 10;
    ctrl->unk00 = 0;
    ctrl->unk01 = 1;
    ctrl->unk02 = 1;
    ctrl->unk03 = 2;
    ctrl->unk04 = 0;
    ctrl->unk05 = 0;
    ctrl->unk06 = 9;
    ctrl->unk1C = 80;
    ctrl->unk1E = 900;
    ctrl->unk20 = -1;
    ctrl->unk22 = 75;
    ctrl->unk24 = 150;
    for (i = 0; i < 4; i++) {
        ctrl->unk08[i] = 0;
        ctrl->unk18[i] = 0xFF;
    }
}

void func_80105D44_hyper_hydrants(omObjData* obj) {
    func_80105EB0_hyper_hydrants(0);
    func_80105EB0_hyper_hydrants(1);
}

/* Camera `cam` (0 left team, 1 right team) during the intro: the target slides forward 2 units a frame. */
void func_80105D68_hyper_hydrants(s8 cam) {
    Vec pos;
    Vec at;
    Vec up;

    if (cam == 0) {
        pos.x = -850.0f;
    } else {
        pos.x = 850.0f;
    }
    pos.y = 1046.895f;
    pos.z = D_8010BE28_hyper_hydrants;
    if (cam == 0) {
        at.x = -850.0f;
    } else {
        at.x = 850.0f;
    }
    at.y = 0.0f;
    D_8010BE2C_hyper_hydrants += 2.0f;
    if (D_8010BE2C_hyper_hydrants > at.y) {
        D_8010BE2C_hyper_hydrants = at.y;
    }
    at.z = D_8010BE2C_hyper_hydrants;
    up.x = 0.0f;
    up.y = 1050.25f;
    up.z = 566.575f;
    Hu3DCamSetPositionOrientation(cam, &pos, &at, &up);
    Hu3DCamUpdateMtx(cam);
}

/* Camera `cam` at its start position. */
void func_80105EB0_hyper_hydrants(s8 cam) {
    Vec pos;
    Vec at;
    Vec up;

    if (cam == 0) {
        pos.x = -850.0f;
    } else {
        pos.x = 850.0f;
    }
    pos.y = 1046.895f;
    pos.z = 570.285f;
    if (cam == 0) {
        at.x = -850.0f;
    } else {
        at.x = 850.0f;
    }
    at.y = 0.0f;
    at.z = -375.0f;
    up.x = 0.0f;
    up.y = 1050.25f;
    up.z = 566.575f;
    Hu3DCamSetPositionOrientation(cam, &pos, &at, &up);
    Hu3DCamUpdateMtx(cam);
}

/* Two cameras, left and right halves of the screen. */
void func_80105FC8_hyper_hydrants(void) {
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 35.883f, 80.0f, 8000.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(1, 35.883f, 80.0f, 8000.0f);
}

void func_801060F8_hyper_hydrants(omObjData* obj) {
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        if (D_8010BE34_hyper_hydrants == 0 && D_800D530C_main == 1) {
            func_8004AD70_main();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                func_8004A950_main();
            }
            func_800E6F0C_minigame(5);
            D_8010BE34_hyper_hydrants = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 0x34;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (D_8010BE30_hyper_hydrants == 0) {
                    WipeCreateOut(0, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_8010BE30_hyper_hydrants++;
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80106238_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80106A50_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80107238_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801078B8_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80107A90_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801083A8_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80108788_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80108F34_hyper_hydrants);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", D_8010BEF0_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801091B0_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80109484_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80109588_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801099A0_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80109B30_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80109E44_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010A2D4_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010A458_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010A68C_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010AB34_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010AE08_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010B2FC_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010B38C_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010B658_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010B8B0_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010BC80_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010BD14_hyper_hydrants);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", D_8010BF30_hyper_hydrants);
