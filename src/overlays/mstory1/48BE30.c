#include "common.h"

void func_80105C90_mstory1(omObjData *);
void func_80105D80_mstory1(omObjData *);
void func_80105E00_mstory1(void);
void func_80105F28_mstory1(omObjData *);
void func_8010809C_mstory1(void);
void func_8010C99C_mstory1(void);
void func_801110DC_mstory1(void);

extern s32 D_80114A84_mstory1;
extern s32 D_801158B4_mstory1; /* the controller that drives the story messages */
extern s16 D_801158B6_mstory1; /* low half of D_801158B4_mstory1 */
extern s32 D_80115CB0_mstory1[4]; /* play order: player per slot */

/* the scene for each story step (GwPlayer[0].coin), and the flag set once it has been seen */
void (*const D_80114C40_mstory1[3])(void) = { func_8010809C_mstory1, func_8010C99C_mstory1, func_801110DC_mstory1 };
const s32 D_80114C4C_mstory1[3] = { 0x34, 0x36, 0x38 };

void func_801059A0_mstory1(void) {
    s16 n = 0;
    s16 i;
    s16 j;
    s16 step;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            D_80115CB0_mstory1[n] = j;
            n++;
            if (n >= 4) {
                break;
            }
        }
        if (n >= 4) {
            break;
        }
    }
    func_800142A0_main(0x3C);
    omInitObjMan(0x1E, 0x1E);
    func_8005A6B0_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 35.0f, 80.0f, 8000.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    {
        omObjData *obj = omAddObj(0x7FDA, 0, 0, -1, func_80105F28_mstory1);
        omSetStatBit(obj, 0xA0);
        func_80105F28_mstory1(obj);
    }
    omAddObj(0, 0, 0, -1, func_80105C90_mstory1);
    omAddObj(0, 0, 0, -1, func_80105D80_mstory1);
    func_80105E00_mstory1();
    for (D_801158B4_mstory1 = 0; D_801158B4_mstory1 < 4; D_801158B4_mstory1++) {
        if (CheckControllerRead(D_801158B6_mstory1) != 0) {
            break;
        }
    }
    if (D_801158B4_mstory1 >= 4) {
        D_801158B4_mstory1 = 0;
    }
    step = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 3) {
        step = 2;
    }
    D_80114C40_mstory1[step]();
    if (_CheckFlag(D_80114C4C_mstory1[step]) != 0) {
        D_80114A84_mstory1 = 1;
    } else {
        _SetFlag(D_80114C4C_mstory1[step]);
    }
    WipeCreateIn(2, 0x10);
}
