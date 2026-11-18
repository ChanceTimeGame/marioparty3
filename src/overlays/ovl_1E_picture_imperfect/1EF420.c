#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

// pi A: Picture Imperfect (4 players, split screen: assemble a picture from its pieces)

/* The minigame control block (as All Fired Up's AfCtrl) */
typedef struct PiCtrl {
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
} PiCtrl; /* size 0x28 */

// main
void func_8000B5F0_main(u8 arg0);
s32 func_8000B710_main(s32 arg0);
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004AD70_main(void);

extern u8 D_800CE20A_main;
extern u16 D_800A1906_main; /* music state flags */
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;

// minigame
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
void func_800E1840_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[];

// LOCAL
void func_80105BA8_picture_imperfect(void);
void func_80105E68_picture_imperfect(PiCtrl* ctrl);
void func_80105EF4_picture_imperfect(void);
void func_80106154_picture_imperfect(omObjData* obj);
void func_8010629C_picture_imperfect(omObjData* obj);
void func_80109608_picture_imperfect(omObjData* obj);

extern s32 D_8010A010_picture_imperfect;
extern s8 D_8010A014_picture_imperfect;

extern PiCtrl D_8010A128_picture_imperfect;
extern u8 D_8010A150_picture_imperfect; /* picture set: 2 - D_800CE20A_main */
extern s8 D_8010A151_picture_imperfect;
extern s16 D_8010A230_picture_imperfect;
extern s16 D_8010A232_picture_imperfect[5][5];
extern s16 D_8010A264_picture_imperfect;
extern s16 D_8010A266_picture_imperfect;
extern s16 D_8010A268_picture_imperfect;
extern s16 D_8010A26A_picture_imperfect;
extern s16 D_8010A26C_picture_imperfect;

void func_801059A0_picture_imperfect(void) {
    omObjData* obj;
    s32 i;

    Hu3DAnimInit(0x20);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105EF4_picture_imperfect();
    D_8010A150_picture_imperfect = 2 - D_800CE20A_main;
    func_80105BA8_picture_imperfect();
    func_80105E68_picture_imperfect(&D_8010A128_picture_imperfect);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010A128_picture_imperfect);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    D_8010A151_picture_imperfect = rand8() >> 6;
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80106154_picture_imperfect), 0xA0);
    func_800E1490_minigame(D_800EBE28_minigame);
    obj = omAddObj(0, 1, 0, -1, func_80109608_picture_imperfect);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
    for (i = 0; i < 4; i++) {
        omSetStatBit(D_800EC598_minigame[i] = omAddObj(1, 4, 60, -1, func_8010629C_picture_imperfect), 0xA0);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, 0xA0);
    obj->work[0] = 4;
    WipeCreateIn(0xFF, 16);
}

/* Load the picture pieces of the set, and the shared sprites. */
void func_80105BA8_picture_imperfect(void) {
    s32 i;

    switch (D_8010A150_picture_imperfect) {
        case 0:
            D_8010A230_picture_imperfect = func_8000B838_main(0x3F0005);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[0][i] = func_8000B838_main((i + 0x0E) | 0x3F0000);
                D_8010A232_picture_imperfect[1][i] = func_8000B838_main((i + 0x13) | 0x3F0000);
                D_8010A232_picture_imperfect[2][i] = func_8000B838_main((i + 0x18) | 0x3F0000);
                D_8010A232_picture_imperfect[3][i] = func_8000B838_main((i + 0x1D) | 0x3F0000);
                D_8010A232_picture_imperfect[4][i] = func_8000B838_main((i + 0x22) | 0x3F0000);
            }
            break;
        case 1:
            D_8010A230_picture_imperfect = func_8000B838_main(0x3F0006);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[0][i] = func_8000B838_main((i + 0x27) | 0x3F0000);
                D_8010A232_picture_imperfect[1][i] = func_8000B838_main((i + 0x2C) | 0x3F0000);
                D_8010A232_picture_imperfect[2][i] = func_8000B838_main((i + 0x31) | 0x3F0000);
                D_8010A232_picture_imperfect[3][i] = func_8000B838_main((i + 0x36) | 0x3F0000);
            }
            break;
        case 2:
        default:
            D_8010A230_picture_imperfect = func_8000B838_main(0x3F0007);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[0][i] = func_8000B838_main((i + 0x3B) | 0x3F0000);
                D_8010A232_picture_imperfect[1][i] = func_8000B838_main((i + 0x40) | 0x3F0000);
                D_8010A232_picture_imperfect[2][i] = func_8000B838_main((i + 0x45) | 0x3F0000);
            }
            break;
    }
    D_8010A264_picture_imperfect = func_8000B838_main(0x40001C);
    D_8010A266_picture_imperfect = func_8000B838_main(0x40001B);
    D_8010A268_picture_imperfect = func_8000B838_main(0x40001D);
    D_8010A26A_picture_imperfect = func_8000B838_main(0x2E);
    D_8010A26C_picture_imperfect = func_8000B838_main(0x3E0019);
}

void func_80105E68_picture_imperfect(PiCtrl* ctrl) {
    s32 i;

    D_800EB932_minigame = 10;
    ctrl->unk00 = 0;
    ctrl->unk01 = 0;
    ctrl->unk02 = 1;
    ctrl->unk03 = 2;
    ctrl->unk04 = 0;
    ctrl->unk05 = 0;
    ctrl->unk06 = 9;
    ctrl->unk1C = -1;
    ctrl->unk1E = 1800;
    ctrl->unk20 = -1;
    ctrl->unk22 = 360;
    ctrl->unk24 = 162;
    for (i = 0; i < 4; i++) {
        ctrl->unk08[i] = 0;
        ctrl->unk18[i] = 0xFF;
    }
}

/* Four cameras, one screen quarter each. */
void func_80105EF4_picture_imperfect(void) {
    s32 i;

    func_8000B710_main(4);
    func_8000B5F0_main(4);
    for (i = 0; i < 4; i++) {
        CenterM[i].x = -200.0f;
        CenterM[i].y = 100.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = CRotM[i].y = CRotM[i].z = 0.0f;
        CZoomM[i] = 2100.0f;
        Hu3DCamSetPerspective(i, 30.0f, 80.0f, 8000.0f);
    }
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 120.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 240.0f, 511.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 120.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 240.0f, 511.0f);
    ScissorSet(2, 0.0f, 120.0f, 160.0f, 240.0f);
    ViewportSet(2, 640.0f, 480.0f, 511.0f, 320.0f, 720.0f, 511.0f);
    ScissorSet(3, 160.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(3, 640.0f, 480.0f, 511.0f, 960.0f, 720.0f, 511.0f);
}

void func_80106154_picture_imperfect(omObjData* obj) {
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        if (D_8010A014_picture_imperfect == 0 && D_800D530C_main == 1) {
            func_8004AD70_main();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                func_8004A950_main();
            }
            func_800E6F0C_minigame(5);
            D_8010A014_picture_imperfect = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 0x31;
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
                if (D_8010A010_picture_imperfect == 0) {
                    WipeCreateOut(0, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    func_80037258_main();
                    omOvlReturnEx(1);
                }
                D_8010A010_picture_imperfect++;
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_8010629C_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80107820_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_801081E4_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_801083C0_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80108688_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80108A64_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80108C20_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80109284_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80109608_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80109AC4_picture_imperfect);
