#include "common.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/10C230.h"

void func_80105CA4_w02(void);
void func_80106094_w02(void*);
extern s32 D_8011C6B0_w02[];
extern s32 D_8011C6CC_w02[];
extern Object* D_8011EBD8_w02[];
extern Process* D_8011EC18_w02;
extern Object* D_8011EC1C_w02;
extern s16 D_8011C6A0_w02[]; //mb2ev_StarGuideMasu

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801059D0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801059F8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80105B00_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80105B8C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80105C30_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80105CA4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106094_w02);

#define GET_STAR_MODEL() D_8011EBD8_w02[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]
//MB3Ev_StarMapView
void func_80106120_w02(void) {
    UnkMBGuideData *guide;
    Process *proc;
    SpaceData *space;
    s32 face;
    s32 mesNum;
    GW_SYSTEM* system = &GwSystem;

    D_800A12D4_main = 0;
    guide = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(guide->obj, 2, 0xF, D_8011C6B0_w02[0]);
    func_800FFF44_shared_board();
    MBModelDispOff(GET_STAR_MODEL());
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    func_800E6FCC_shared_board();
    func_800E9730_shared_board(3.0f);
    func_80106094_w02(guide);

    if ((system->current_star_spawn == 0) && (GWBoardFlagCheck(4) == 0)) {
        if (system->current_board_index == 2) {
            mesNum = 0x5E09;
        } else {
            mesNum = 0x5E00;
        }
    } else {
        if (system->current_board_index == 2) {
            mesNum = 0x5E09;
        } else {
            mesNum = 0x5E01;
        }
    }
    func_8005B43C_main(guide->amount, mesNum, -1, -1);
    func_80060C14_main(guide->amount, 1);
    HuAudFXPlay(0x2A7);
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);
    func_8001FDE8_main(guide->obj->omObj1->model[0]);

    if ((system->current_board_index != SPINY_DESERT) || (rand8() & 1)) {
        space = MBMasuGet(D_8011C6A0_w02[system->star_spawn_indices[system->current_star_spawn]]);
    }
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    face = MBRand(7.0f);
    MBGuideFaceSet(guide->obj, D_8011C6B0_w02[face]);
    MBMotionSet(guide->obj, -1, 2);

    if (system->current_board_index != 2) {
        proc = omAddPrcObj(func_80105CA4_w02, 0x4800, 0, 0);
        D_8011EC18_w02 = proc;
        proc->user_data = space;
        HuPrcSleep(30);
    } else {
        D_8011EC18_w02 = NULL;
    }

    func_8005B43C_main(guide->amount, D_8011C6CC_w02[face], -1, -1);
    func_80060C14_main(guide->amount, 1);
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);

    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(2, 0x10);
    HuPrcSleep(0x11);
    D_800A12D4_main = 1;
    func_80100130_shared_board();
    func_80046558_main(D_8011EC1C_w02->omObj1->model[0]);
    MBModelKill(D_8011EC1C_w02);
    MBModelDispOn(GET_STAR_MODEL());
    MBGuideKill(guide);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}


INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801064DC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106A3C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106AB0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106B38_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106B94_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106C64_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106CC4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106F58_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107170_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801072A0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107438_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107704_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107724_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107744_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107780_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107830_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107B4C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107BD0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107BFC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107D24_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107D88_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107E34_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107F54_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107FB0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801080AC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108218_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108280_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801083EC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010844C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801084A8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108570_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108620_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010865C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801086DC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108754_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801087F8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108870_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801088EC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801089C0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108A20_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108A58_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108A8C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108AC4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108B6C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108BA4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108C4C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108C7C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108CC0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108CF0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108D34_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108D64_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108DA8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108DD8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108E1C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108E4C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108F8C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108FEC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010904C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801090AC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010910C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010916C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801091CC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010922C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010928C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801092EC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010934C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801093AC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010940C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010946C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801094CC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010952C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010958C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801095EC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010964C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010985C_w02);

void func_80109C80_w02(void) {
}

void func_80109C88_w02(void) {
}

void func_80109C90_w02(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80109C98_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80109F1C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80109FD8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010A018_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010A3C4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010AF00_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010AF88_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010AFF0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010B1C8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010C47C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010C51C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010C5BC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010CA04_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010CA28_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010D854_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010D9A8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010D9E4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010EBB8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010EBD4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010EBF0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010ED4C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010EE64_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F22C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F298_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F458_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F6BC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F78C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F9BC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010FB8C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010FCFC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110048_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011020C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801104A4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110730_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110970_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110B80_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110E40_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801111E0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80111BDC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112124_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112340_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112734_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801127F0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112944_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112980_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112B10_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112ECC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80113164_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80113270_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011344C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801140F8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801141B8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801146E8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80114FF4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011512C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011529C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80115464_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801156E8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80115FEC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801161E4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011625C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801162C0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011646C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011656C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80116608_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80116708_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80116914_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80116A74_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80116AC4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011703C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011720C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80117344_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801177C8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80117E70_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80118480_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119244_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119360_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801193C0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801193D0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801193DC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119408_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119438_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011946C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119680_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801199EC_w02);

// board g6
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/106A50.h"
#include "game/window.h"
#include "game/hmfman.h"
#include "input.h"

void func_801199EC_w02(void);
void func_80107830_w02(void);
void func_80119DB0_w02(void);
void func_80119244_w02(void);
void func_801193C0_w02(void);
void func_801193D0_w02(void);
void func_801193DC_w02(void);
void func_80119408_w02(s16 model, f32 arg1, f32 arg2);
void func_80007EC0_main(s32);
extern s16 D_8011ED00_w02;
extern Object *D_8011C8DC_w02;
extern s32 D_8011D95C_w02;
extern s32 D_8011D960_w02[3];
extern s32 D_8011D96C_w02[3];
extern s32 D_8011D978_w02[3];
extern f32 D_8011D984_w02[4][2];
void func_8011B038_w02(s16 masu);
s32 func_8011B988_w02(void);
s32 func_8011BA58_w02(void);
extern RectF D_8011DADC_w02;
extern s32 D_8011D594_w02;
extern s32 D_8011E914_w02;
extern DecisionTreeNonLeafNode D_8011E254_w02[];
extern DecisionTreeNonLeafNode *D_8011E338_w02[];
extern DecisionTreeNonLeafNode *D_8011E73C_w02[];
extern DecisionTreeNonLeafNode *D_8011E75C_w02[];
extern DecisionTreeNonLeafNode *D_8011EA68_w02[];
extern DecisionTreeNonLeafNode D_8011DD2C_w02[];
extern DecisionTreeNonLeafNode D_8011DD98_w02[];
extern DecisionTreeNonLeafNode D_8011DF3C_w02[];
extern DecisionTreeNonLeafNode D_8011E0A4_w02[];
extern DecisionTreeNonLeafNode D_8011E1C4_w02[];
extern DecisionTreeNonLeafNode D_8011E4E4_w02[];
extern DecisionTreeNonLeafNode D_8011E77C_w02[];
extern s32 D_8011ECB4_w02;
extern s32 D_8011ECB8_w02;
extern s32 D_8011ECF8_w02;
extern s32 D_8011ECFC_w02;
extern s16 D_8011D9A4_w02[20];

/* Sets a model's matrix to a rotation of `angle` degrees about z. */
#define W02_MODEL_ROTZ(obj, angle)                                                                   \
    {                                                                                              \
        HmfModel *mdl;                                                                             \
        sincosdf(angle, &HmfModelData[(obj)->omObj1->model[0]].mtx[1],                             \
                 &HmfModelData[(obj)->omObj1->model[0]].mtx[0]);                                   \
        HmfModelData[(obj)->omObj1->model[0]].mtx[4] = -HmfModelData[(obj)->omObj1->model[0]].mtx[1]; \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                              \
        mdl->mtx[5] = mdl->mtx[0];                                                                 \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                              \
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] =         \
            mdl->mtx[11] = mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;                      \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                              \
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;                                                        \
    }
extern u8 *D_8011E998_w02[8];
extern s8 *D_8011EA38_w02[8];
extern DecisionTreeNonLeafNode *D_8011EA58_w02[2];
extern DecisionTreeNonLeafNode *D_8011EA60_w02[2];
s32 func_8010AF00_w02(s32 item);
s32 func_8010AF88_w02(void);

// board g6
Process *func_80119D84_w02(void) {
    return omAddPrcObj(func_801199EC_w02, 0x1000, 0, 0);
}

#ifdef NON_MATCHING
/* Reads a player motion id from the resident motion table: the u16 low half of word `n` of D_80101734_shared_board[0]. */
#define W02_MOTION_ID(n, tmp, cnt)                                            \
    for ((tmp) = (u16 *)D_80101734_shared_board[0], (cnt) = (n); (cnt) != 0; \
         (cnt)--, (tmp) += 2) {                                               \
    }

/* Spaces 0x50..0x55: the board's wheel spins; the players on those spaces mash A against the pull and the
   ones who fail are thrown to the place the wheel picked (D_8011D960/D_8011D96C/D_8011D978_w02[pick]). */
void func_80119DB0_w02(void) {
    Vec camPos;
    Vec camTarget;
    Vec startPos[4];
    Vec pull[4];
    Vec step[4];
    f32 power[4];
    s32 presses[4];
    UnkVibrateProcess *vib[4];
    SpaceData *center;
    SpaceData *space2;
    GW_PLAYER *curPlayer;
    Object *pullModel;
    Unk3 *helpWin;
    SpaceData *dest;
    GW_PLAYER *player;
    s16 win;
    u16 *mot;
    s32 cnt;
    s32 pick;
    s32 angle;
    s32 speed;
    s32 laps;
    s32 onMask;
    s32 thrownMask;
    s32 sfxPlayed;
    s32 frame;
    s32 i;
    f32 scale;

    center = MBMasuGet(0x78);
    space2 = MBMasuGet(0x52);
    curPlayer = MBPlayerGet(-1);
    MBStatusHideAll();
    HuVecAdd(&camTarget, &center->coords, &space2->coords);
    HuVecMulScalar(&camTarget, 0.5f, &camTarget);
    camTarget.z -= 40.0f;
    HuVecCopy3F(&camPos, &curPlayer->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&camPos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &camTarget, &camPos, 40));
    HuPrcChildWait();
    MBDlgWinExec(0x39, 0x400);
    pick = MBRand(7.0f);
    if (pick >= 1 && pick <= 3) {
        pick = 1;
    }
    if (pick >= 4 && pick <= 6) {
        pick = 2;
    }
    laps = 0;
    speed = 0;
    angle = -138;
    HuAudFXPlay(0x192);
    while (TRUE) {
        D_8011C8DC_w02->rot.x = sindf(angle);
        D_8011C8DC_w02->rot.z = cosdf(angle);
        if (laps >= 5) {
            if (pick == 0 && angle >= -180 && angle + speed < -179) {
                angle = -180;
                break;
            }
            if (pick == 1 && angle >= -90 && angle + speed < -89) {
                angle = -90;
                break;
            }
            if (pick == 2 && angle >= -135 && angle + speed < -134) {
                angle = -135;
                break;
            }
        }
        angle += speed;
        speed -= 2;
        if (angle < -360) {
            laps++;
            angle += 360;
        }
        if (speed < -50) {
            speed = -50;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(0x193);
    D_8011C8DC_w02->rot.x = sindf(angle);
    D_8011C8DC_w02->rot.z = cosdf(angle);
    angle = 0;
    for (i = 0; i < 30; i++) {
        angle = angle + 39.0f;
        if ((f32)angle > 360.0f) {
            angle = (f32)angle - 360.0f;
        }
        scale = cosdf(angle) * 0.3f + 1.0f;
        cosdf(angle);
        HuVecCopyXYZ(&D_8011C8DC_w02->scale, 1.0f, 1.0f, scale);
        HuPrcVSleep();
    }
    D_8011D95C_w02 = 1;
    onMask = 0;
    func_80119244_w02();
    HuVecCopy3F(&camTarget, &MBMasuGet(0x53)->coords);
    camTarget.z -= 20.0f;
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &camTarget, &camPos, 30));
    HuPrcChildWait();
    pullModel = MBModelFileCreate(0x130169, -1, 1.0f, 0.0f, NULL);
    func_8001C258_main(pullModel->omObj1->model[0], 0x80000, 0x80000);
    func_8001C448_main(pullModel->omObj1->model[0]);
    MBModelTempAllocFree(pullModel);
    for (i = 0; i < 4; i++) {
        s16 masu;

        player = MBPlayerGet(i);
        masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        if (masu < 0x56 && masu >= 0x50) {
            onMask |= 1 << i;
            vib[i] = MBPlayerVibrateObjCreate(i, 1, 5);
        }
    }
    D_800A12D8_main = 1;
    func_801193C0_w02();
    HuAudFXPlay(0x194);
    for (i = 0; i < 4; i++) {
        if (onMask & (1 << i)) {
            player = MBPlayerGet(i);
            MBPlayerMotionLoad(i, 5, 0x3D);
            MBPlayerMotionLoad(i, 6, 0x3B);
            MBMotionSet(player->player_obj, 5, 2);
            MBVecDirGet(&center->coords, &player->player_obj->coords, &player->player_obj->rot);
            HuVecCopy3F(&startPos[i], &player->player_obj->coords);
            HuVecSubtract(&pull[i], &center->coords, &player->player_obj->coords);
            HuVecMulScalar(&pull[i], 0.1f, &pull[i]);
            HuVecAdd(&pull[i], &pull[i], &player->player_obj->coords);
            pull[i].y += (i - 1) * 7.0f;
            HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &pull[i], &player->player_obj->coords, 20));
            player->player_obj->flags |= 1;
        }
    }
    HuPrcChildWait();
    HuPrcChildLink(HuPrcCurrentGet(), func_80119D84_w02());
    HuPrcSleep(30);
    win = func_8005A968_main(0x66, 0xB2, 0x74, 0x18, 0, 0);
    func_8005BEE0_main(win, 0x100);
    func_8005FBF8_main(win, 0x8C, 0xC8, 0x3C);
    helpWin = func_800E210C_shared_board(0x16, 0xB4, 1);
    HuPrcChildWait();
    for (i = 0; i < 4; i++) {
        if (onMask & (1 << i)) {
            MBMotionSet(MBPlayerGet(i)->player_obj, 6, 2);
        }
    }
    HuPrcSleep(10);
    for (i = 0; i < 4; i++) {
        presses[i] = 0;
        power[i] = 1.0f;
        HuVecSubtract(&pull[i], &center->coords, &MBPlayerGet(i)->player_obj->coords);
        HuVecMulScalar(&pull[i], 0.002f, &pull[i]);
    }
    for (frame = 0; frame < 120; frame++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (!(onMask & (1 << i))) {
                continue;
            }
            if (MBPlayerComCheck(i) != 0) {
                if (MBRand(5.0f) == 0 || GwSystem.star_spawn_indices[GwSystem.current_star_spawn] == 7) {
                    presses[i]++;
                    if (power[i] == 0.0f) {
                        power[i] = 1.0f;
                    } else {
                        power[i] += 0.3f;
                    }
                    if (power[i] > 3.0f) {
                        power[i] = 3.0f;
                    }
                }
            } else if (D_800C9520_main[GwPlayer[i].pad] & 0x8000) {
                presses[i]++;
                if (power[i] == 0.0f) {
                    power[i] = 1.0f;
                } else {
                    power[i] += 0.3f;
                }
                if (power[i] > 3.0f) {
                    power[i] = 3.0f;
                }
            }
            HuVecCopy3F(&step[i], &pull[i]);
            if (power[i] < 1.0f) {
                HuVecMulScalar(&step[i], 1.0f - power[i] / 2.0f, &step[i]);
            } else {
                HuVecMulScalar(&step[i], 0.3f, &step[i]);
            }
            HuVecAdd(&player->player_obj->coords, &step[i], &player->player_obj->coords);
            power[i] -= 0.1f;
            if (power[i] < 0.0f) {
                power[i] = 0.0f;
            }
            func_8001C92C_main(player->player_obj->omObj1->model[0], power[i]);
        }
        func_80119408_w02(D_8011ED00_w02, frame / 24.0f + 1.0f, 1000.0f);
        HuPrcVSleep();
    }
    sfxPlayed = 0;
    func_801193D0_w02();
    func_80007EC0_main(30);
    MBHelpWinKill(helpWin);
    func_8005F364_main(win);
    thrownMask = 0;
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        if (onMask & (1 << i)) {
            MBPlayerVibrateObjKill(vib[i]);
            if (presses[i] >= 25) {
                func_8001C92C_main(player->player_obj->omObj1->model[0], 2.0f);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &startPos[i], &player->player_obj->coords, 20));
            } else {
                func_8001C92C_main(player->player_obj->omObj1->model[0], 2.0f);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &center->coords, &player->player_obj->coords, 10));
                thrownMask |= 1 << i;
                if (sfxPlayed == 0) {
                    sfxPlayed = 1;
                    HuAudFXPlay(0x195);
                }
            }
        }
    }
    HuPrcSleep(20);
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        if (!(thrownMask & (1 << i))) {
            player->player_obj->flags &= ~1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (onMask & (1 << i)) {
            player = MBPlayerGet(i);
            MBMotionSet(player->player_obj, -1, 2);
            W02_MOTION_ID(6, mot, cnt);
            MBPlayerMotionLoad(i, 5, mot[1]);
            W02_MOTION_ID(7, mot, cnt);
            MBPlayerMotionLoad(i, 6, mot[1]);
            MBVecForwardSet(&player->player_obj->rot);
        }
    }
    if (thrownMask != 0) {
        D_8011D95C_w02 = 2;
        func_80119408_w02(D_8011ED00_w02, -40.0f, 1000.0f);
        func_801193C0_w02();
        HuAudFXPlay(0x196);
        HuPrcSleep(30);
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (thrownMask & (1 << i)) {
                MBPlayerMotionLoad(i, 5, 0x3C);
                MBPlayerMotionLoad(i, 6, 7);
                MBMotionSet(player->player_obj, 5, 0);
                HuPrcVSleep();
                func_8001C814_main(player->player_obj->omObj1->model[0], 2, 1);
                HuVecCopy3F(&player->player_obj->coords, &MBMasuGet(0x7A)->coords);
                HuVecSubtract(&pull[i], &MBMasuGet(D_8011D960_w02[pick])->coords, &player->player_obj->coords);
                HuVecMulScalar(&pull[i], 2.5f, &pull[i]);
                HuVecAdd(&pull[i], &pull[i], &player->player_obj->coords);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &pull[i], &player->player_obj->coords, 15));
                MBVecDirGet(&player->player_obj->coords, &pull[i], &player->player_obj->rot);
                HuAudFXPlay(0x197);
                HuPrcSleep(5);
            }
        }
        HuPrcSleep(5);
        WipeCreateOut(4, 16);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        HuPrcChildWait();
        func_801193DC_w02();
        MBModelKill(pullModel);
        center = MBMasuGet(D_8011D978_w02[pick]);
        dest = MBMasuGet(D_8011D96C_w02[pick]);
        MBCameraFocusVecSet(&dest->coords);
        func_800E9AF0_shared_board(&dest->coords, 0);
        HuPrcVSleep();
        MBCameraFocusModeSet(3);
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (thrownMask & (1 << i)) {
                func_800EB24C_shared_board(D_8011D96C_w02[pick], &player->clink, &player->cidx);
                player->blink = player->nlink = player->clink;
                player->nidx = player->cidx + 1;
                player->bidx = player->cidx - 1;
            }
        }
        for (i = 0; i < 4; i++) {
            if (!(thrownMask & (1 << i))) {
                MBPlayerPosFixSet(i, 1);
            }
        }
        WipeCreateIn(4, 16);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        laps = 0;
        for (i = 0; i < 4; i++) {
            if (thrownMask & (1 << i)) {
                s32 jumpTime[3] = { 20, 20, 30 };

                player = MBPlayerGet(i);
                HuPrcChildLink(HuPrcCurrentGet(), func_800ED5E0_shared_board(&player->player_obj->coords, &center->coords, &player->player_obj->coords, jumpTime[pick]));
                MBVecDirGet(&player->player_obj->coords, &center->coords, &player->player_obj->rot);
                HuPrcChildWait();
                HuAudFXPlay(GwPlayer[i].chr + 0x287);
                MBPlayerVibrate(i, 3);
                MBMotionSet(player->player_obj, 6, 0);
                player->player_obj->flags &= ~1;
                MBVecForwardSet(&player->player_obj->rot);
                HuVecCopy3F(&pull[i], &dest->coords);
                pull[i].x += D_8011D984_w02[laps][0];
                pull[i].z += D_8011D984_w02[laps][1];
                laps++;
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &pull[i], &player->player_obj->coords, 16));
                func_800EE688_shared_board(player->player_obj, 15.0f, -1.875f);
                HuPrcChildWait();
                func_800EE6C0_shared_board(player->player_obj);
                MBMotionSet(player->player_obj, 4, 2);
            }
        }
        HuPrcSleep(20);
        for (i = 0; i < 4; i++) {
            if (thrownMask & (1 << i)) {
                MBPlayerGet(i);
                W02_MOTION_ID(6, mot, cnt);
                MBPlayerMotionLoad(i, 5, mot[1]);
                W02_MOTION_ID(7, mot, cnt);
                MBPlayerMotionLoad(i, 6, mot[1]);
            }
        }
        MBStatusShowAll();
    } else {
        HuVecCopy3F(&camTarget, &curPlayer->player_obj->coords);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &camTarget, &camPos, 20));
        HuPrcChildWait();
        MBStatusShowAll();
        MBCameraFocusModeSet(3);
        func_801193DC_w02();
        MBModelKill(pullModel);
    }
    HuVecCopyXYZ(&D_8011C8DC_w02->scale, 1.0f, 1.0f, 1.0f);
    D_8011C8DC_w02->rot.x = sindf(-138.0f);
    D_8011C8DC_w02->rot.z = cosdf(-138.0f);
    D_800A12D8_main = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119DB0_w02);
#endif

// board g6
/* Warp space: a board model carries the player to the space paired with `masu` in D_8011D9A4_w02. */
#ifdef NON_MATCHING
// One instruction off: retail has no nop after the first sindf call of the second loop
// (GCC filled that delay slot itself here, so gas adds a nop).
void func_8011B038_w02(s16 masu) {
    f32 screen[2];
    Vec pos;
    Vec target;
    GW_PLAYER *player;
    SpaceData *space;
    SpaceData *dest;
    Object *obj;
    UnkVibrateProcess *vib;
    s32 offscreen;
    s32 destMasu;
    s32 i;

    player = MBPlayerGet(-1);
    space = MBMasuGet(0x72);
    destMasu = 0;
    for (i = 0; i < ARRAY_COUNTU(D_8011D9A4_w02); i += 2) {
        if (D_8011D9A4_w02[i] == masu) {
            destMasu = D_8011D9A4_w02[i + 1];
            break;
        }
    }
    dest = MBMasuGet(destMasu);
    MBCamera3Dto2D(&space->coords, screen);
    offscreen = 1;
    if (screen[0] >= 24.0f && screen[0] <= 296.0f && screen[1] >= 12.0f && screen[1] <= 228.0f) {
        offscreen = 0;
        HuVecCopy3F(&target, &space->coords);
        HuVecCopy3F(&pos, &player->player_obj->coords);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&pos);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &target, &pos, 20));
        HuPrcChildWait();
    } else {
        offscreen = 1;
        WipeCreateOut(4, 16);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        HuVecCopy3F(&pos, &space->coords);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&pos);
        func_800E9AF0_shared_board(&pos, 0);
        HuPrcVSleep();
        WipeCreateIn(4, 16);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
    }
    MBDlgWinExec(0x3A, 0x500);
    HuVecAdd(&target, &player->player_obj->coords, &dest->coords);
    HuVecMulScalar(&target, 0.5f, &target);
    if (offscreen == 0) {
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &target, &pos, 20));
        HuPrcChildWait();
    } else {
        WipeCreateOut(4, 16);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        HuVecCopy3F(&pos, &target);
        func_800E9AF0_shared_board(&pos, 0);
        HuPrcVSleep();
        WipeCreateIn(4, 16);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
    }
    obj = MBModelFileCreate(0x13016A, -1, 1.0f, 0.0f, NULL);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->velocity.x = 150.0f;
    for (i = 90; i <= 180; i += 3) {
        obj->velocity.x = sindf(i) * 150.0f;
        W02_MODEL_ROTZ(obj, 180 - i);
        HuPrcVSleep();
    }
    func_800EB24C_shared_board(destMasu, &player->clink, &player->cidx);
    MBMoveMasuSet(MBPlayerTurnGet(), player->clink, player->cidx);
    for (i = 0; i < 4; i++) {
        if (i != MBPlayerTurnGet()) {
            MBPlayerPosFixSet(i, 5);
        }
    }
    HuAudFXPlay(0x191);
    vib = MBPlayerVibrateObjCreate(-1, 2, 5);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &dest->coords, &player->player_obj->coords, 18));
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&obj->coords, &dest->coords, &obj->coords, 18));
    for (i = 0; i <= 180; i += 10) {
        obj->velocity.x = sindf(i) * 50.0f;
        W02_MODEL_ROTZ(obj, -sindf(i) * 30.0f);
        player->player_obj->velocity.x = sindf(i) * 50.0f;
        HuPrcVSleep();
    }
    MBPlayerVibrateObjKill(vib);
    player->player_obj->velocity.x = 0.0f;
    for (i = 0; i <= 90; i += 10) {
        obj->velocity.x = sindf(i) * 150.0f;
        W02_MODEL_ROTZ(obj, i);
        HuPrcVSleep();
    }
    MBModelKill(obj);
    MBCameraFocusModeSet(3);
    HuPrcSleep(5);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B038_w02);
#endif

// board g6
void func_8011B8A0_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);

    HuPrcSleep(8);
    if (masu < 0x56) {
        if (masu >= 0x50) {
            func_80119DB0_w02();
            goto end;
        }
    }
    func_8011B038_w02(masu);
end:
    omDelPrcObj(NULL);
}

// board g6
void func_8011B934_w02(void) {
    Hu3DCamInit(2);
    CameraScissorSet(1, &D_8011DADC_w02);
    func_80107830_w02();
    MBStart(2);
    omAddPrcObj(func_80106120_w02, 0x1005, 0x1000, 0);
}

// board g6
#ifdef NON_MATCHING
// Differs only in how &GwSystem is shared: retail keeps the loop's copy in s1 and reloads the others.
s32 func_8011B988_w02(void) {
    GW_SYSTEM *sys = &GwSystem;
    DecisionTreeNonLeafNode *tree = D_8011E338_w02[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
    s32 i;
    s32 unused[2];

    func_800DA778_shared_board(GwSystem.current_player_index);
    if (MBComTreeExec(D_8011E254_w02) == 0) {
        return GwSystem.current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index) {
            func_800DA778_shared_board(i);
            if (MBComTreeExec(tree) == 0) {
                return i;
            }
        }
    }
    return MBRand(4.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B988_w02);
#endif

// board g6
#ifdef NON_MATCHING
// Same register-sharing difference as func_8011B988_w02.
s32 func_8011BA58_w02(void) {
    GW_SYSTEM *sys = &GwSystem;
    DecisionTreeNonLeafNode *tree1 = D_8011E73C_w02[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
    DecisionTreeNonLeafNode *tree2 = D_8011E75C_w02[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
    s32 i;
    s32 unused[2];

    func_800DA778_shared_board(GwSystem.current_player_index);
    if (MBComTreeExec(tree1) == 0) {
        return GwSystem.current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index) {
            func_800DA778_shared_board(i);
            if (MBComTreeExec(tree2) == 0) {
                return i;
            }
        }
    }
    return MBRand(4.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011BA58_w02);
#endif

// board g6
s32 func_8011BB30_w02(void) {
    s32 turnsLeft;
    s32 slot;
    GW_SYSTEM *sys = &GwSystem;

    turnsLeft = sys->total_turns - sys->current_turn + 1;
    slot = MBItemFindEmpty(-1);
    if (slot == -1) {
        slot = 3;
    }
    return (slot < turnsLeft) ? 0 : 1;
}

// board g6
s32 func_8011BB84_w02(s32 base, s32 perLevel) {
    s32 ret;
    s32 i;
    s32 j;

    ret = 1;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i != GwSystem.current_player_index) {
            for (j = 0; j < ARRAY_COUNT(GwPlayer->itemNo); j++) {
                if ((GwPlayer[i].itemNo[j] == ITEM_PLUNDER_CHEST) ||
                    (GwPlayer[i].itemNo[j] == ITEM_BARTER_BOX)) {
                    break;
                }
            }
            if (j < 3) {
                break;
            }
        }
    }
    if ((i < MB_MAX_PLAYERS) && MBRandCheck100(base + (perLevel * GwPlayer[i].cpu_difficulty)) != 0) {
        ret = 0;
    }
    return ret;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/w02/335610", D_8011EB68_w02);

// board g6
s32 func_8011BC6C_w02(void) {
    s32 curPlayer = MBPlayerTurnGet();
    GW_SYSTEM *loc = &GwSystem;
    s32 results[3];
    s32 item;
    s32 i;
    s32 j;
    s32 count;
    s32 best;
    s32 slot;

    if (GwSystem.cur_player_used_item & 1) {
        return -1;
    }
    for (slot = 0; slot < 3; slot++) {
        results[slot] = -1;
        item = GwPlayer[curPlayer].itemNo[slot];
        switch (item) {
            case ITEM_NONE:
                continue;
            case ITEM_SKELETON_KEY:
            case ITEM_BOO_REPELLENT:
            case ITEM_KOOPA_KARD:
                for (i = 0, count = 0; i < 3; i++) {
                    if (GwPlayer[curPlayer].itemNo[i] == item) {
                        count++;
                    }
                }
                if (count < 2) {
                    continue;
                }
                break;
            case ITEM_WACKY_WATCH:
                if (loc->total_turns == loc->current_turn) {
                    if (MBPlayerStealRankGet(loc->current_player_index) != 0) {
                        break;
                    }
                }
                if (loc->total_turns - loc->current_turn < 6) {
                    continue;
                }
                if (MBPlayerStealRankGet(loc->current_player_index) == 0) {
                    break;
                }
                continue;
            case ITEM_MUSHROOM:
            case ITEM_LUCKY_CHARM:
                if (func_8011BB30_w02() != 0) {
                    break;
                }
                if (MBRandCheck100(80) == 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_PHONE:
                if (GwPlayer[curPlayer].coin == 0) {
                    break;
                }
                for (i = 0; i < 4; i++) {
                    if (i != curPlayer && GwPlayer[i].coin == 0) {
                        break;
                    }
                }
                if (i >= 4) {
                    break;
                }
                if (MBRandCheck100(70) != 0 && func_8011BB30_w02() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (func_8011BB30_w02() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011DD2C_w02) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (func_8011BB30_w02() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011DD98_w02) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(D_8011DF3C_w02) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(D_8011E1C4_w02) == 0) {
                    s32 target = func_8011B988_w02();

                    D_8011ECFC_w02 = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(D_8011E4E4_w02) == 0) {
                    s32 target = func_8011BA58_w02();

                    D_8011ECF8_w02 = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, D_8011ECB8_w02 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < D_80100FA8_shared_board[it]) {
                                    best = D_80100FA8_shared_board[it];
                                    D_8011ECB8_w02 = i;
                                }
                            }
                        }
                    }
                }
                if (D_8011ECB8_w02 == -1) {
                    continue;
                }
                if (best >= 4) {
                    break;
                }
                if (MBRandCheck100(5) == 0) {
                    continue;
                }
                break;
            case ITEM_BARTER_BOX:
                for (i = 0, best = 0; i < 3; i++) {
                    if (i != slot) {
                        s8 it = GwPlayer[loc->current_player_index].itemNo[i];

                        if (it != -1) {
                            best += D_80100FA8_shared_board[it];
                        }
                    }
                }
                for (i = 0, D_8011ECB4_w02 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += D_80100FA8_shared_board[it];
                            }
                        }
                        if (best < count) {
                            D_8011ECB4_w02 = i;
                            best = count;
                        }
                    }
                }
                if (D_8011ECB4_w02 == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (func_8011BB84_w02(0x32, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 5) {
                    continue;
                }
                break;
            case ITEM_CELLULAR_SHOPPER:
                if (loc->total_turns == loc->current_turn) {
                    continue;
                }
                if (GwPlayer[curPlayer].coin < 5) {
                    continue;
                }
                break;
            case ITEM_MAGIC_LAMP:
                if (func_8011BB84_w02(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(D_8011E0A4_w02) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && func_8011BB30_w02() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(D_8011E77C_w02) != 0) {
                    continue;
                }
                break;
        }
        results[slot] = GwPlayer[curPlayer].itemNo[slot];
    }
    slot = 0;
    i = 0;
    for (j = 0; j < 3; j++) {
        item = results[j];
        if (item == -1) {
            continue;
        }
        if (loc->total_turns == loc->current_turn) {
            if (item == ITEM_WACKY_WATCH) {
                return j;
            }
        }
        if (slot < D_80100FF4_shared_board[results[j]]) {
            i = j;
            slot = D_80100FF4_shared_board[results[j]];
        }
    }
    if (slot == 0) {
        return -1;
    }
    return i;
}

// board g6
s32 func_8011C274_w02(void) {
    s32 sp14;
    GW_PLAYER* temp_s3;
    s32 var_s1_2;
    s32 temp_v0;
    s32 var_s2;
    s32 var_s2_2;
    s32 temp_s0;
    u8 temp_s0_2;
    s32 i;
    GW_SYSTEM* system = &GwSystem;

    temp_s3 = MBPlayerGet(CUR_PLAYER);
    sp14 = 1;

    for (i = 0; i < 16; i++) {
        temp_s0 = D_8011E998_w02[temp_s3->chr][i];
        var_s2 = func_8010AF00_w02(temp_s0);
        if (var_s2 != -1 && D_80100F94_shared_board[temp_s0] + 20 <= GwPlayer[system->current_player_index].coin &&
            MBRandCheck100(D_8011EA38_w02[temp_s3->chr][i])) {
            break;
        }
    }
    if (i == 16) {
        var_s2 = -1;
    }

    if (var_s2 != -1) {
        if ((func_8010AF00_w02(0xE) != var_s2) &&
        ((func_8010AF00_w02(0xB) != var_s2) ||
        ((D_80100F94_shared_board[0xB] + 50) > (GwPlayer[system->current_player_index].coin)) != 0)) {
            if ((func_8010AF00_w02(4) == var_s2) &&
            (MBItemFind(system->current_player_index, 4) != -1)) {
                var_s2 = -1;
                sp14 = 0;
            }
        } else {
            return var_s2 + 1;
        }
    }
    if ((MBComTreeExec(D_8011EA58_w02[D_8011D594_w02]) == 0) && GwPlayer[system->current_player_index].coin >= D_80100F94_shared_board[1]) {
        temp_v0 = func_8010AF00_w02(1);
        if (temp_v0 != -1) {
            return temp_v0 + 1;
        }
    }
    if (var_s2 == -1) {
        i = MBComTreeExec(D_8011EA60_w02[D_8011D594_w02]);
        if (i == 0) {
            do {
                temp_s0_2 = D_8011E998_w02[temp_s3->chr][i];
                //this line below has to be written very specific
                if ((temp_s0_2 == 4 && sp14 == 0) == 0) {
                    var_s2_2 = func_8010AF00_w02(temp_s0_2);
                    if ((var_s2_2 != -1) && !(D_80100F94_shared_board[temp_s0_2] > (GwPlayer[system->current_player_index].coin))) {
                        if ((MBRandCheck100(D_8011EA38_w02[temp_s3->chr][i]))) {
                            return var_s2_2 + 1;
                        }
                    }
                }
            } while (++i < 16);
        }

        var_s2_2 = func_8010AF00_w02(0);
        if (var_s2_2 == -1) {
            D_8011E914_w02 = 1;
            return func_8010AF88_w02() + 2;
        }
        return var_s2_2 + 1;
    }
    return var_s2 + 1;
}

// board g6
s32 func_8011C5D8_w02(void) {
    if (D_8011E914_w02 != 0) {
        D_8011E914_w02 = 0;
        return 2;
    }
    return MBComTreeExec(D_8011EA68_w02[D_8011D594_w02]) + 1;
}
/* .data (0x8011C660, 0x2500 bytes): the overlay's initialised data, in address order. */
#include "WaluigisIsland.h" /* BranchLink */
s32 func_80108A20_w02();
void func_80108A58_w02(void);
void func_80108A8C_w02(void);
void func_80108AC4_w02(void);
void func_80108B6C_w02(void);
void func_80108BA4_w02(void);
void func_80108C7C_w02(void);
void func_80108CF0_w02(void);
void func_80108D64_w02(void);
void func_80108DD8_w02(void);
void func_80108E4C_w02(void);
void func_80108F8C_w02(void);
void func_80108FEC_w02(void);
void func_8010904C_w02(void);
void func_801090AC_w02(void);
void func_8010910C_w02(void);
void func_8010916C_w02(void);
void func_801091CC_w02(void);
void func_8010922C_w02(void);
void func_8010928C_w02(void);
void func_801092EC_w02(void);
void func_8010934C_w02(void);
void func_801093AC_w02(void);
void func_8010940C_w02(void);
void func_8010946C_w02(void);
void func_801094CC_w02(void);
void func_8010952C_w02(void);
void func_8010958C_w02(void);
void func_801095EC_w02(void);
void func_8010985C_w02(void);
void func_8010A018_w02(void);
void func_8010A3C4_w02(void);
void func_8010B1C8_w02(void);
void func_8010D9E4_w02(void);
void func_8010EBB8_w02(void);
void func_8010EBD4_w02(void);
void func_80116708_w02(void);
void func_8011703C_w02(void);
void func_80118480_w02(void);
s16 D_8011C660_w02[8] = { 0, 1, 2, 3, 5, 4, 6, 7 };
s16 D_8011C670_w02[8] = { 0, 0, 0, 0, 0, 1, 1, 1 };
s16 D_8011C680_w02[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011C690_w02[8] = { 30, 40, 21, 7, 65, 92, 76, 86 };
s16 D_8011C6A0_w02[8] = { 94, 95, 96, 97, 98, 99, 100, 101 };
s32 D_8011C6B0_w02[7] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083, 0xA0084 };
s32 D_8011C6CC_w02[7] = { 24066, 24067, 24068, 24069, 24070, 24071, 24072 };
s32 D_8011C6E8_w02 = 0;
s16 D_8011C6EC_w02 = -1;
s16 D_8011C6F0_w02[10] = {
    30, 40, 21, 7, 65, 92, 76, 86,
    -1, 0,
};
s16 D_8011C704_w02[8][2] = {
    { 4, 0 },
    { -2, -2 },
    { 0, -4 },
    { 4, 0 },
    { 4, -2 },
    { -2, 2 },
    { -4, -4 },
    { 0, 0 },
};
s16 D_8011C724_w02[2][2] = {
    { 0, -2 },
    { 0, 0 },
};
s16 D_8011C72C_w02[2][2] = {
    { 0, 0 },
    { 0, -4 },
};
s16 D_8011C734_w02[2][2] = {
    { 0, 0 },
    { 2, 0 },
};
s16 D_8011C73C_w02[2][2] = {
    { 0, 0 },
    { 0, 2 },
};
s16 D_8011C744_w02[2][2] = {
    { 133, 134 },
    { 135, 136 },
};
s16 D_8011C74C_w02[8] = { 94, 95, 96, 97, 98, 99, 100, 101 };
s16 D_8011C75C_w02[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011C76C_w02[2] = { 102, 0 };
s16 D_8011C770_w02[2] = { 111, 113 };
Vec D_8011C774_w02[5] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f },
};
Vec D_8011C7B0_w02[5] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 20.0f, 0.0f, -30.0f },
    { 45.0f, 0.0f, 45.0f },
};
s16 D_8011C7EC_w02[2] = { 106, 107 };
u8 D_8011C7F0_w02[6][2] = {
    { 0, 38 },
    { 0, 39 },
    { 0, 40 },
    { 0, 41 },
    { 0, 42 },
    { 0, 43 },
};
u32 D_8011C7FC_w02[2] = { 1, 0x130163 };
u32 D_8011C804_w02[2] = { 1, 0x130168 };
u32 D_8011C80C_w02[2] = { 1, 0x13016F };
u32 D_8011C814_w02[2] = { 1, 0x130176 };
u32 D_8011C81C_w02[2] = { 1, 0x130180 };
u32 D_8011C824_w02[2] = { 1, 0x130184 };
u32 *D_8011C82C_w02[6] = {
    D_8011C7FC_w02, D_8011C804_w02, D_8011C80C_w02, D_8011C814_w02,
    D_8011C81C_w02, D_8011C824_w02,
};
s32 D_8011C844_w02[9] = {
    328, 328, 328, 328, 328, 328, -1, -1,
    -1,
};
s32 D_8011C868_w02[9] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1,
};
s32 D_8011C88C_w02[9] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1,
};
s32 D_8011C8B0_w02[9] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1,
};
s16 D_8011C8D4_w02[2] = { 110, 112 };
s16 D_8011C8D8_w02[2] = { 108, 109 };
Object *D_8011C8DC_w02 = NULL;
Object *D_8011C8E0_w02 = NULL;
s16 D_8011C8E4_w02[4] = { 124, 126, 127, 128 };
DecisionTreeNonLeafNode D_8011C8EC_w02[2] = {
    { 3, { .data = 0x00000140 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011C904_w02[3] = {
    { 2, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000090 }, { .node_data = D_8011C8EC_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011C928_w02[4] = {
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x1B54233C } },
    { 9, { .data = 0x00000008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011C958_w02[3] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011C928_w02 } },
    { 2, { .data = 0x00000090 }, { .node_data = D_8011C8EC_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011C97C_w02[2] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011C928_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode *D_8011C994_w02[3] = { D_8011C904_w02, D_8011C958_w02, D_8011C97C_w02 };
DecisionTreeNonLeafNode D_8011C9A0_w02[2] = {
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011C9B8_w02[2] = {
    { 2, { .data = 0x0000000A }, { .node_data = D_8011C9A0_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011C9D0_w02[2] = {
    { 2, { .data = 0x0000000A }, { .node_data = D_8011C9A0_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011C9E8_w02[2] = {
    { 9, { .data = 0x00000009 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011CA00_w02[2] = {
    { 9, { .data = 0x00000007 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011CA18_w02[3] = {
    { 2, { .data = 0x00000008 }, { .node_data = D_8011C9E8_w02 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011CA00_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode *D_8011CA3C_w02[3] = { D_8011C9B8_w02, D_8011C9D0_w02, D_8011CA18_w02 };
DecisionTreeNonLeafNode D_8011CA48_w02[2] = {
    { 3, { .data = 0x00000050 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode D_8011CA60_w02[2] = {
    { 3, { .data = 0x00000050 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CA78_w02[3] = {
    { 3, { .data = 0x00000010 }, { .data = 0x1B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011CA9C_w02[4] = {
    { 3, { .data = 0x00000020 }, { .data = 0x1B54233C } },
    { 3, { .data = 0x00000050 }, { .data = 0x1B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011CACC_w02[5] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011CA48_w02 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011CA60_w02 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011CA78_w02 } },
    { 2, { .data = 0x000000C0 }, { .node_data = D_8011CA9C_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011CB08_w02[2] = {
    { 3, { .data = 0x00000046 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode D_8011CB20_w02[4] = {
    { 2, { .data = 0x00000007 }, { .node_data = D_8011CB08_w02 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011CA78_w02 } },
    { 2, { .data = 0x000000C0 }, { .node_data = D_8011CA9C_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011CB50_w02[2] = {
    { 3, { .data = 0x00000050 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011CB68_w02[3] = {
    { 2, { .data = 0x00000007 }, { .node_data = D_8011CB08_w02 } },
    { 2, { .data = 0x000000D0 }, { .node_data = D_8011CB50_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011CB8C_w02[3] = { D_8011CACC_w02, D_8011CB20_w02, D_8011CB68_w02 };
DecisionTreeNonLeafNode D_8011CB98_w02[2] = {
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CBB0_w02[3] = {
    { 2, { .data = 0x00000080 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000070 }, { .node_data = D_8011CB98_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CBD4_w02[3] = {
    { 3, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000004 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CBF8_w02[5] = {
    { 2, { .data = 0x00000040 }, { .node_data = D_8011CBD4_w02 } },
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000008 }, { .data = 0x1B54233C } },
    { 9, { .data = 0x00000007 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011CC34_w02[4] = {
    { 1, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 9, { .data = 0x00000007 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011CC64_w02[5] = {
    { 2, { .data = 0x00000080 }, { .node_data = D_8011CC34_w02 } },
    { 2, { .data = 0x00000040 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 9, { .data = 0x00000007 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011CCA0_w02[3] = { D_8011CBB0_w02, D_8011CBF8_w02, D_8011CC64_w02 };
DecisionTreeNonLeafNode D_8011CCAC_w02[3] = {
    { 3, { .data = 0x0000000A }, { .data = 0x1B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CCD0_w02[3] = {
    { 3, { .data = 0x0000000A }, { .data = 0x1B54233C } },
    { 9, { .data = 0x00000005 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CCF4_w02[5] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011CCAC_w02 } },
    { 2, { .data = 0x0000000E }, { .node_data = D_8011CCD0_w02 } },
    { 3, { .data = 0x00000020 }, { .data = 0x1B54233C } },
    { 3, { .data = 0x0000000A }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011CD30_w02[3] = {
    { 3, { .data = 0x00000058 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000020 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011CD54_w02[4] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x000000F0 }, { .node_data = D_8011CD30_w02 } },
    { 3, { .data = 0x00000020 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011CD84_w02[3] = {
    { 3, { .data = 0x0000000A }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011CDA8_w02[4] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011CD84_w02 } },
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x000000F0 }, { .node_data = D_8011CD30_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011CDD8_w02[3] = { D_8011CCF4_w02, D_8011CD54_w02, D_8011CDA8_w02 };
DecisionTreeNonLeafNode D_8011CDE4_w02[2] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CDFC_w02[3] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011CDE4_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CE20_w02[2] = {
    { 2, { .data = 0x0000000A }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CE38_w02[2] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011CE50_w02[2] = {
    { 2, { .data = 0x00000008 }, { .node_data = D_8011CE38_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode *D_8011CE68_w02[3] = { D_8011CDFC_w02, D_8011CE20_w02, D_8011CE50_w02 };
DecisionTreeNonLeafNode D_8011CE74_w02[2] = {
    { 3, { .data = 0x0000000C }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CE8C_w02[2] = {
    { 2, { .data = 0x000000F0 }, { .node_data = D_8011CE74_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011CEA4_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011CEB0_w02[3] = {
    { 3, { .data = 0x0000000C }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011CED4_w02[2] = {
    { 2, { .data = 0x000000F0 }, { .node_data = D_8011CEB0_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011CEEC_w02[3] = { D_8011CE8C_w02, D_8011CEA4_w02, D_8011CED4_w02 };
DecisionTreeNonLeafNode D_8011CEF8_w02[4] = {
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x000000C0 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011CF28_w02[2] = {
    { 9, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode D_8011CF40_w02[2] = {
    { 9, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode *D_8011CF58_w02[3] = { D_8011CEF8_w02, D_8011CF28_w02, D_8011CF40_w02 };
DecisionTreeNonLeafNode D_8011CF64_w02[5] = {
    { 2, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x0000000C }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x000000A0 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } },
};
DecisionTreeNonLeafNode *D_8011CFA0_w02[3] = { D_8011CF64_w02, D_8011CF64_w02, D_8011CF64_w02 };
DecisionTreeNonLeafNode D_8011CFAC_w02[2] = {
    { 6, { .func = func_80108A20_w02 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011CFC4_w02[3] = {
    { 2, { .data = 0x0000000F }, { .node_data = D_8011CFAC_w02 } },
    { 6, { .func = func_80108A20_w02 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode *D_8011CFE8_w02[3] = { D_8011CFC4_w02, D_8011CFC4_w02, D_8011CFC4_w02 };
DecisionTreeNonLeafNode D_8011CFF4_w02[2] = {
    { 2, { .data = 0x0000000F }, { .data = 0x0A142850 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
DecisionTreeNonLeafNode D_8011D00C_w02[3] = {
    { 2, { .data = 0x0000000F }, { .data = 0x0A142850 } },
    { 2, { .data = 0x00000080 }, { .data = 0x0B56AD5A } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
DecisionTreeNonLeafNode D_8011D030_w02[2] = {
    { 2, { .data = 0x00000007 }, { .data = 0x0A142850 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
DecisionTreeNonLeafNode D_8011D048_w02[2] = {
    { 2, { .data = 0x0000000F }, { .data = 0x0A142850 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C993264 } },
};
event_list_entry D_8011D060_w02[2] = {
    { 8, 1, func_80108A58_w02 },
    { 0, 0, NULL },
};
s16 D_8011D070_w02[3][3] = {
    { 55, 34, -1 },
    { 44, 34, -1 },
    { 44, 55, -1 },
};
BranchLink D_8011D084_w02[3][2] = {
    { { 2, 0, 0 }, { 1, 0, 0 } },
    { { 0, 19, 1 }, { 1, 0, 0 } },
    { { 0, 19, 1 }, { 2, 0, 0 } },
};
event_list_entry D_8011D0A8_w02[2] = {
    { 1, 2, func_80108A8C_w02 },
    { 0, 0, NULL },
};
s16 D_8011D0B8_w02[3][3] = {
    { 17, 38, -1 },
    { 16, 38, -1 },
    { 16, 17, -1 },
};
BranchLink D_8011D0CC_w02[3][2] = {
    { { 0, 0, 0 }, { 3, 0, 0 } },
    { { 4, 4, 1 }, { 3, 0, 0 } },
    { { 4, 4, 1 }, { 0, 0, 0 } },
};
event_list_entry D_8011D0F0_w02[2] = {
    { 1, 1, func_80108AC4_w02 },
    { 0, 0, NULL },
};
s16 D_8011D100_w02[3][3] = {
    { 54, 91, -1 },
    { 53, 91, -1 },
    { 53, 54, -1 },
};
BranchLink D_8011D114_w02[3][2] = {
    { { 7, 0, 0 }, { 8, 0, 0 } },
    { { 6, 10, 1 }, { 8, 0, 0 } },
    { { 6, 10, 1 }, { 7, 0, 0 } },
};
event_list_entry D_8011D138_w02[2] = {
    { 1, 2, func_80108B6C_w02 },
    { 0, 0, NULL },
};
s16 D_8011D148_w02[3][3] = {
    { 79, 89, -1 },
    { 76, 89, -1 },
    { 76, 79, -1 },
};
BranchLink D_8011D15C_w02[3][2] = {
    { { 10, 0, 0 }, { 9, 0, 0 } },
    { { 7, 21, 1 }, { 9, 0, 0 } },
    { { 7, 21, 1 }, { 10, 0, 0 } },
};
event_list_entry D_8011D180_w02[2] = {
    { 1, 1, func_80108BA4_w02 },
    { 0, 0, NULL },
};
s16 D_8011D190_w02[3][3] = {
    { 24, 37, -1 },
    { 21, 37, -1 },
    { 21, 24, -1 },
};
BranchLink D_8011D1A4_w02[3][2] = {
    { { 0, 6, 0 }, { 1, 3, 1 } },
    { { 0, 4, 1 }, { 1, 3, 1 } },
    { { 0, 4, 1 }, { 0, 6, 0 } },
};
event_list_entry D_8011D1C8_w02[2] = {
    { 1, 1, func_80108C7C_w02 },
    { 0, 0, NULL },
};
s16 D_8011D1D8_w02[3][3] = {
    { 4, 41, -1 },
    { 2, 41, -1 },
    { 2, 4, -1 },
};
BranchLink D_8011D1EC_w02[3][2] = {
    { { 2, 8, 0 }, { 3, 6, 1 } },
    { { 2, 6, 1 }, { 3, 6, 1 } },
    { { 2, 6, 1 }, { 2, 8, 0 } },
};
event_list_entry D_8011D210_w02[2] = {
    { 1, 1, func_80108CF0_w02 },
    { 0, 0, NULL },
};
s16 D_8011D220_w02[3][3] = {
    { 49, 90, -1 },
    { 47, 90, -1 },
    { 47, 49, -1 },
};
BranchLink D_8011D234_w02[3][2] = {
    { { 6, 6, 0 }, { 9, 4, 1 } },
    { { 6, 4, 1 }, { 9, 4, 1 } },
    { { 6, 4, 1 }, { 6, 6, 0 } },
};
event_list_entry D_8011D258_w02[2] = {
    { 1, 1, func_80108D64_w02 },
    { 0, 0, NULL },
};
s16 D_8011D268_w02[3][3] = {
    { 74, 93, -1 },
    { 72, 93, -1 },
    { 72, 74, -1 },
};
BranchLink D_8011D27C_w02[3][2] = {
    { { 7, 19, 0 }, { 8, 3, 1 } },
    { { 7, 17, 1 }, { 8, 3, 1 } },
    { { 7, 17, 1 }, { 7, 19, 0 } },
};
event_list_entry D_8011D2A0_w02[2] = {
    { 1, 1, func_80108DD8_w02 },
    { 0, 0, NULL },
};
s16 D_8011D2B0_w02[3] = { 11, 32, -1 };
BranchLink D_8011D2B8_w02[2] = {
    { 0, 16, 0 },
    { 0, 14, 1 },
};
event_list_entry D_8011D2C4_w02[2] = {
    { 1, 1, func_80108E4C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D2D4_w02[2] = {
    { 1, 1, func_80108F8C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D2E4_w02[2] = {
    { 1, 1, func_80108FEC_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D2F4_w02[2] = {
    { 1, 1, func_8010904C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D304_w02[2] = {
    { 1, 1, func_801090AC_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D314_w02[2] = {
    { 1, 1, func_8010910C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D324_w02[2] = {
    { 1, 1, func_8010916C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D334_w02[2] = {
    { 1, 1, func_801091CC_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D344_w02[2] = {
    { 1, 1, func_8010922C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D354_w02[2] = {
    { 1, 1, func_8010928C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D364_w02[2] = {
    { 1, 1, func_801092EC_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D374_w02[2] = {
    { 1, 1, func_8010934C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D384_w02[2] = {
    { 1, 1, func_801093AC_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D394_w02[2] = {
    { 1, 1, func_8010940C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D3A4_w02[2] = {
    { 1, 1, func_8010946C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D3B4_w02[2] = {
    { 1, 1, func_801094CC_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D3C4_w02[2] = {
    { 1, 1, func_8010952C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D3D4_w02[2] = {
    { 1, 1, func_8010958C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D3E4_w02[2] = {
    { 1, 1, func_801095EC_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D3F4_w02[2] = {
    { 1, 2, func_8010985C_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D404_w02[2] = {
    { 1, 1, func_8010A018_w02 },
    { 0, 0, NULL },
};
DecisionTreeNonLeafNode D_8011D414_w02[2] = {
    { 4, { .data = 0x00F50014 }, { .data = 0x0B541E1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E1E } },
};
u32 D_8011D42C_w02[2] = { 1, 0xA009D };
event_list_entry D_8011D434_w02[2] = {
    { 1, 1, func_8010A3C4_w02 },
    { 0, 0, NULL },
};
u8 D_8011D444_w02[2][3][4] = {
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } },
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } },
};
s8 D_8011D45C_w02[2][5][7] = {
    { { 0, 1, 4, 5, 10, 14, 19 }, { 0, 1, 4, 5, 10, 12, 19 }, { 0, 1, 4, 5, 10, 19, -1 }, { 0, 1, 4, 8, 10, 12, 19 }, { 0, 1, 8, 10, 12, 14, 19 } },
    { { 1, 2, 3, 6, 13, 11, 19 }, { 1, 2, 3, 6, 9, 13, 19 }, { 1, 2, 3, 7, 13, 19, -1 }, { 1, 3, 6, 7, 9, 13, 19 }, { 1, 3, 6, 7, 9, 11, 19 } },
};
u8 D_8011D4A4_w02[2][3][4] = {
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
};
s8 D_8011D4BC_w02[2][5][10] = {
    { { 25, 55, 65, 76, 81, 86, 91, 96, 98, 100 }, { 30, 50, 60, 70, 75, 85, 90, 95, 97, 100 }, { 25, 45, 52, 62, 67, 82, 88, 95, 97, 100 }, { 20, 35, 40, 45, 55, 75, 85, 95, 97, 100 }, { 15, 25, 30, 40, 45, 70, 80, 92, 95, 100 } },
    { { 33, 53, 68, 73, 78, 83, 93, 98, 100, 0 }, { 25, 40, 55, 63, 73, 81, 91, 98, 100, 0 }, { 20, 38, 58, 68, 75, 82, 90, 98, 100, 0 }, { 15, 35, 55, 65, 72, 79, 85, 97, 100, 0 }, { 15, 25, 45, 55, 65, 75, 80, 95, 100, 0 } },
};
u8 D_8011D520_w02[2][10] = {
    { 0, 1, 4, 5, 8, 10, 12, 14, 15, 16 },
    { 1, 2, 3, 6, 7, 9, 13, 11, 17, 1 },
};
s32 D_8011D534_w02[5][2] = {
    { 15109, 15621 },
    { 15110, 15622 },
    { 15111, 15623 },
    { 15112, 15624 },
    { 15113, 15625 },
};
s32 D_8011D55C_w02[2] = { 15104, 15616 };
s32 D_8011D564_w02[2] = { 15105, 15617 };
s32 D_8011D56C_w02[2] = { 15106, 15618 };
s32 D_8011D574_w02[2] = { 15107, 15619 };
s32 D_8011D57C_w02[2] = { 15108, 15620 };
u32 D_8011D584_w02[2] = { 1, 0xA0017 };
u32 D_8011D58C_w02[2] = { 1, 0xA00F0 };
s32 D_8011D594_w02 = 0;
event_list_entry D_8011D598_w02[2] = {
    { 1, 1, func_8010B1C8_w02 },
    { 0, 0, NULL },
};
f32 D_8011D5A8_w02[4][2] = {
    { 76.0f, 52.0f },
    { 244.0f, 52.0f },
    { 76.0f, 192.0f },
    { 244.0f, 192.0f },
};
f32 D_8011D5C8_w02[4][2] = {
    { -1.0f, -1.0f },
    { 1.0f, -1.0f },
    { -1.0f, 1.0f },
    { 1.0f, 1.0f },
};
u8 D_8011D5E8_w02[6][3] = {
    { 1, 5, 15 },
    { 6, 15, 25 },
    { 16, 25, 27 },
    { 26, 35, 30 },
    { 36, 45, 32 },
    { 46, 50, 35 },
};
u8 D_8011D5FC_w02[14][3] = {
    { 0, 0, 0 },
    { 1, 10, 1 },
    { 11, 11, 4 },
    { 12, 14, 2 },
    { 15, 15, 4 },
    { 16, 23, 3 },
    { 24, 33, 4 },
    { 34, 37, 5 },
    { 38, 39, 2 },
    { 40, 49, 6 },
    { 50, 54, 5 },
    { 55, 63, 7 },
    { 64, 64, 8 },
    { 65, 255, 9 },
};
u8 D_8011D628_w02[8] = { 9, 7, 4, 1, 0, 0, 0, 0 };
s32 D_8011D630_w02[3] = { 50, 80, 100 };
s32 D_8011D63C_w02[7] = { 1, 0, 1, 0, 0, 1, 0 };
event_list_entry D_8011D658_w02[2] = {
    { 1, 1, func_8010D9E4_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D668_w02[2] = {
    { 1, 1, func_8010EBB8_w02 },
    { 0, 0, NULL },
};
event_list_entry D_8011D678_w02[2] = {
    { 1, 1, func_8010EBD4_w02 },
    { 0, 0, NULL },
};
event_table_entry D_8011D688_w02[15] = {
    { 30, D_8011D404_w02 },
    { 40, D_8011D404_w02 },
    { 21, D_8011D404_w02 },
    { 7, D_8011D404_w02 },
    { 65, D_8011D404_w02 },
    { 92, D_8011D404_w02 },
    { 76, D_8011D404_w02 },
    { 86, D_8011D404_w02 },
    { 33, D_8011D434_w02 },
    { 75, D_8011D434_w02 },
    { 115, D_8011D598_w02 },
    { 105, D_8011D598_w02 },
    { 106, D_8011D668_w02 },
    { 107, D_8011D678_w02 },
    { -1, NULL },
};
event_table_entry D_8011D700_w02[2] = {
    { 121, D_8011D658_w02 },
    { -1, NULL },
};
Vec2f D_8011D710_w02[4] = {
    { 164.0f, 76.0f },
    { 140.0f, 76.0f },
    { 164.0f, 76.0f },
    { 140.0f, 76.0f },
};
Vec2f D_8011D730_w02[4] = {
    { 132.0f, 62.0f },
    { 220.0f, 62.0f },
    { 132.0f, 180.0f },
    { 220.0f, 180.0f },
};
Vec2f D_8011D750_w02[4] = {
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
};
Vec2f D_8011D770_w02[4] = {
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
};
DecisionTreeNonLeafNode D_8011D790_w02[9] = {
    { 13, { .data = 0x00000000 }, { .data = 0x0A142850 } },
    { 13, { .data = 0x00000001 }, { .data = 0x064C9932 } },
    { 13, { .data = 0x00000002 }, { .data = 0x03C78F1E } },
    { 13, { .data = 0x00000003 }, { .data = 0x08D1A346 } },
    { 13, { .data = 0x00000004 }, { .data = 0x078F1E3C } },
    { 13, { .data = 0x00000005 }, { .data = 0x064C9932 } },
    { 13, { .data = 0x00000006 }, { .data = 0x03C78F1E } },
    { 13, { .data = 0x00000007 }, { .data = 0x078F1E3C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
s32 D_8011D7FC_w02[5] = { 20, 60, 30, 50, 70 };
DecisionTreeNonLeafNode D_8011D810_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
f32 D_8011D81C_w02[6][2] = {
    { -10.0f, 0.0f },
    { 10.0f, -5.0f },
    { 10.0f, 5.0f },
    { -5.0f, -5.0f },
    { 10.0f, 0.0f },
    { -5.0f, 5.0f },
};
s32 D_8011D84C_w02 = -1;
u8 D_8011D850_w02[4] = { 67, 68, 69, 0 };
u8 D_8011D854_w02[4] = { 20, 60, 100, 0 };
u16 D_8011D858_w02[7][2] = {
    { 0, 50 },
    { 2, 80 },
    { 4, 90 },
    { 8, 94 },
    { 16, 97 },
    { 32, 99 },
    { 64, 100 },
};
RGB D_8011D874_w02[2] = {
    { 240, 222, 53 },
    { 247, 26, 66 },
};
event_list_entry D_8011D87C_w02[3] = {
    { 7, 1, func_80116708_w02 },
    { 7, 1, func_8011703C_w02 },
    { 0, 0, NULL },
};
event_table_entry D_8011D894_w02[2] = {
    { -5, D_8011D87C_w02 },
    { -1, NULL },
};
s16 D_8011D8A4_w02[3] = { 42, 12, -1 };
BranchLink D_8011D8AC_w02[2] = {
    { 6, 0, 0 },
    { 4, 0, 0 },
};
u32 D_8011D8B8_w02[2] = { 1, 0x2001A };
u32 D_8011D8C0_w02[2] = { 1, 0 };
u32 D_8011D8C8_w02[2] = { 1, 0 };
u32 D_8011D8D0_w02[2] = { 1, 0 };
u32 D_8011D8D8_w02[2] = { 1, 0 };
u32 D_8011D8E0_w02[2] = { 1, 0 };
u32 D_8011D8E8_w02[2] = { 1, 0 };
u32 D_8011D8F0_w02[2] = { 1, 0 };
u32 *D_8011D8F8_w02[8] = {
    D_8011D8B8_w02, D_8011D8C0_w02, D_8011D8C8_w02, D_8011D8D0_w02,
    D_8011D8D8_w02, D_8011D8E0_w02, D_8011D8E8_w02, D_8011D8F0_w02,
};
s32 D_8011D918_w02[8] = { 14, 15, 16, 17, 18, 19, 20, 21 };
s16 D_8011D938_w02[4] = { 10, 87, 42, -1 };
s16 D_8011D940_w02[4] = { 12, 10, 87, -1 };
event_list_entry D_8011D948_w02[2] = {
    { 1, 1, func_80118480_w02 },
    { 0, 0, NULL },
};
s32 D_8011D958_w02 = 1;
s32 D_8011D95C_w02 = 1;
s32 D_8011D960_w02[3] = { 85, 80, 82 };
s32 D_8011D96C_w02[3] = { 4, 68, 103 };
s32 D_8011D978_w02[3] = { 117, 118, 116 };
f32 D_8011D984_w02[4][2] = {
    { 0.0f, 0.0f },
    { 0.0f, 14.0f },
    { 7.0f, 7.0f },
    { -7.0f, 7.0f },
};
s16 D_8011D9A4_w02[20] = {
    15, 46, 47, 16, 17, 49, 18, 50,
    51, 19, 52, 20, 25, 58, 59, 26,
    27, 60, 61, 28,
};
event_table_entry D_8011D9CC_w02[34] = {
    { 103, D_8011D060_w02 },
    { 104, D_8011D0A8_w02 },
    { 132, D_8011D0F0_w02 },
    { 137, D_8011D138_w02 },
    { 78, D_8011D180_w02 },
    { 23, D_8011D1C8_w02 },
    { 3, D_8011D210_w02 },
    { 48, D_8011D258_w02 },
    { 73, D_8011D2A0_w02 },
    { 0, D_8011D2C4_w02 },
    { 17, D_8011D2D4_w02 },
    { 34, D_8011D2E4_w02 },
    { 37, D_8011D2F4_w02 },
    { 55, D_8011D304_w02 },
    { 10, D_8011D314_w02 },
    { 38, D_8011D324_w02 },
    { 41, D_8011D334_w02 },
    { 12, D_8011D344_w02 },
    { 42, D_8011D354_w02 },
    { 54, D_8011D364_w02 },
    { 91, D_8011D374_w02 },
    { 93, D_8011D384_w02 },
    { 89, D_8011D394_w02 },
    { 90, D_8011D3A4_w02 },
    { 79, D_8011D3B4_w02 },
    { 87, D_8011D3C4_w02 },
    { 130, D_8011D3D4_w02 },
    { 131, D_8011D3E4_w02 },
    { 133, D_8011D3F4_w02 },
    { 135, D_8011D3F4_w02 },
    { 134, D_8011D3F4_w02 },
    { 136, D_8011D3F4_w02 },
    { 125, D_8011D948_w02 },
    { -1, NULL },
};
RectF D_8011DADC_w02 = { 0.0f, 0.0f, 320.0f, 240.0f };
DecisionTreeNonLeafNode D_8011DAEC_w02[8] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00000006 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040005 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00001315 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00000E12 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DB4C_w02[3] = {
    { 10, { .data = 0x0002000E }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DB70_w02[3] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 8, { .data = 0x00000001 }, { .node_data = D_8011DB4C_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DB94_w02[5] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00040005 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002000E }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DBD0_w02[6] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00020006 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00001315 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00000C12 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DC18_w02[5] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x0006000B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00070005 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090104 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DC54_w02[5] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00060006 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0008 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002080E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DC90_w02[5] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00000000 } },
    { 10, { .data = 0x0007000E }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x0006000B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DCCC_w02[8] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00000000 } },
    { 10, { .data = 0x0007070E }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00071416 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00070F13 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00080003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DD2C_w02[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011DAEC_w02 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011DB70_w02 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011DB94_w02 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011DBD0_w02 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011DC18_w02 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011DC54_w02 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011DC90_w02 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011DCCC_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DD98_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A141932 } },
};
DecisionTreeNonLeafNode D_8011DDA4_w02[3] = {
    { 10, { .data = 0x0000050B }, { .data = 0x0001038A } },
    { 11, { .data = 0x0000050B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DDC8_w02[3] = {
    { 10, { .data = 0x00030104 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00030104 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DDEC_w02[7] = {
    { 10, { .data = 0x00000003 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00040305 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040305 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DE40_w02[5] = {
    { 10, { .data = 0x0002050A }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030406 }, { .data = 0x0001038A } },
    { 11, { .data = 0x0002050A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030406 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DE7C_w02[3] = {
    { 10, { .data = 0x00070409 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00070409 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DEA0_w02[5] = {
    { 10, { .data = 0x00080001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x0006060B }, { .data = 0x0001038A } },
    { 11, { .data = 0x00080001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x0006060B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DEDC_w02[5] = {
    { 10, { .data = 0x00070E14 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00080003 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00070E14 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DF18_w02[3] = {
    { 10, { .data = 0x000A0006 }, { .data = 0x0001038A } },
    { 11, { .data = 0x000A0006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } },
};
DecisionTreeNonLeafNode D_8011DF3C_w02[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011DDA4_w02 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011DDC8_w02 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011DDEC_w02 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011DE40_w02 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011DE7C_w02 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011DEA0_w02 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011DEDC_w02 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011DF18_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011DFA8_w02[2] = {
    { 10, { .data = 0x0000050B }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011DFC0_w02[2] = {
    { 10, { .data = 0x00030104 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011DFD8_w02[4] = {
    { 10, { .data = 0x00000003 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00040305 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011E008_w02[3] = {
    { 10, { .data = 0x0002050A }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030406 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011E02C_w02[2] = {
    { 10, { .data = 0x00070409 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011E044_w02[3] = {
    { 10, { .data = 0x00080001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x0006060B }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011E068_w02[3] = {
    { 10, { .data = 0x00070E14 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00080003 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011E08C_w02[2] = {
    { 10, { .data = 0x000A0006 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } },
};
DecisionTreeNonLeafNode D_8011E0A4_w02[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011DFA8_w02 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011DFC0_w02 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011DFD8_w02 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011E008_w02 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011E02C_w02 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011E044_w02 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011E068_w02 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011E08C_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E110_w02[2] = {
    { 11, { .data = 0x00000509 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E128_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E134_w02[4] = {
    { 11, { .data = 0x00000000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040205 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E164_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E170_w02[2] = {
    { 11, { .data = 0x00070105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E188_w02[2] = {
    { 11, { .data = 0x00060507 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E1A0_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E1AC_w02[2] = {
    { 11, { .data = 0x000A0004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E1C4_w02[12] = {
    { 10, { .data = 0x00000F11 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00080303 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071113 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000001 }, { .node_data = D_8011E110_w02 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011E128_w02 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011E134_w02 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011E164_w02 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011E170_w02 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011E188_w02 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011E1A0_w02 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011E1AC_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E254_w02[4] = {
    { 15, { .data = 0x00000F11 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00080303 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071113 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E284_w02[2] = {
    { 15, { .data = 0x00000509 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E29C_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E2A8_w02[4] = {
    { 15, { .data = 0x00000000 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00030000 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040205 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E2D8_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E2E4_w02[2] = {
    { 15, { .data = 0x00070105 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E2FC_w02[2] = {
    { 15, { .data = 0x00060507 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E314_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E320_w02[2] = {
    { 15, { .data = 0x000A0004 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode *D_8011E338_w02[8] = {
    D_8011E284_w02, D_8011E29C_w02, D_8011E2A8_w02, D_8011E2D8_w02,
    D_8011E2E4_w02, D_8011E2FC_w02, D_8011E314_w02, D_8011E320_w02,
};
DecisionTreeNonLeafNode D_8011E358_w02[4] = {
    { 10, { .data = 0x00000D12 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x0000050B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E388_w02[4] = {
    { 10, { .data = 0x00030606 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002080B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E3B8_w02[4] = {
    { 10, { .data = 0x0000050A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E3E8_w02[5] = {
    { 10, { .data = 0x00020C0E }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040002 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060002 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E424_w02[4] = {
    { 10, { .data = 0x00070B12 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00070904 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E454_w02[4] = {
    { 10, { .data = 0x00080303 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071316 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E484_w02[3] = {
    { 10, { .data = 0x00090000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E4A8_w02[5] = {
    { 10, { .data = 0x000A0808 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000A0006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E4E4_w02[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011E358_w02 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011E388_w02 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011E3B8_w02 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011E3E8_w02 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011E424_w02 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011E454_w02 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011E484_w02 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011E4A8_w02 } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } },
};
DecisionTreeNonLeafNode D_8011E550_w02[3] = {
    { 15, { .data = 0x00000D12 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E574_w02[4] = {
    { 15, { .data = 0x00030606 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x0002080B }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E5A4_w02[3] = {
    { 15, { .data = 0x0000050A }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E5C8_w02[5] = {
    { 15, { .data = 0x00020C0E }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040002 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00060002 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E604_w02[3] = {
    { 15, { .data = 0x00070B12 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E628_w02[4] = {
    { 15, { .data = 0x00080303 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071316 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E658_w02[3] = {
    { 15, { .data = 0x00090000 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000A0005 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E67C_w02[4] = {
    { 15, { .data = 0x000A0808 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040004 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00060004 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E6AC_w02[2] = {
    { 15, { .data = 0x0000050B }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E6C4_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E6D0_w02[2] = {
    { 15, { .data = 0x00000003 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E6E8_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E6F4_w02[2] = {
    { 15, { .data = 0x00070904 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E70C_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E718_w02[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E724_w02[2] = {
    { 15, { .data = 0x000A0006 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode *D_8011E73C_w02[8] = {
    D_8011E550_w02, D_8011E574_w02, D_8011E5A4_w02, D_8011E5C8_w02,
    D_8011E604_w02, D_8011E628_w02, D_8011E658_w02, D_8011E67C_w02,
};
DecisionTreeNonLeafNode *D_8011E75C_w02[8] = {
    D_8011E6AC_w02, D_8011E6C4_w02, D_8011E6D0_w02, D_8011E6E8_w02,
    D_8011E6F4_w02, D_8011E70C_w02, D_8011E718_w02, D_8011E724_w02,
};
DecisionTreeNonLeafNode D_8011E77C_w02[1] = {
    { 0, { .data = 0x00000000 }, { .node_data = D_8011DF3C_w02 } },
};
DecisionTreeNonLeafNode D_8011E788_w02[3] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E7AC_w02[3] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E7D0_w02[2] = {
    { 2, { .data = 0x000000F1 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E7E8_w02[2] = {
    { 2, { .data = 0x0000001F }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011E800_w02[2] = {
    { 1, { .data = 0x00000028 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E818_w02[5] = {
    { 9, { .data = 0x00000008 }, { .node_data = D_8011E800_w02 } },
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000028 }, { .data = 0x0A11A0BC } },
    { 1, { .data = 0x0000001E }, { .data = 0x064C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x02879432 } },
};
DecisionTreeNonLeafNode D_8011E854_w02[3] = {
    { 2, { .data = 0x00000008 }, { .node_data = D_8011E818_w02 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011E878_w02[2] = {
    { 1, { .data = 0x0000002D }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E890_w02[5] = {
    { 9, { .data = 0x00000006 }, { .node_data = D_8011E878_w02 } },
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000028 }, { .data = 0x0A11A0BC } },
    { 1, { .data = 0x0000001E }, { .data = 0x064C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x02879432 } },
};
DecisionTreeNonLeafNode D_8011E8CC_w02[2] = {
    { 1, { .data = 0x00000028 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8011E8E4_w02[4] = {
    { 2, { .data = 0x00000020 }, { .node_data = D_8011E8CC_w02 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011E890_w02 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
s32 D_8011E914_w02 = 0;
u8 D_8011E918_w02[16] = {
    14, 10, 0, 3, 2, 4, 19, 11,
    5, 6, 12, 13, 9, 7, 8, 1,
};
u8 D_8011E928_w02[16] = {
    14, 1, 11, 10, 19, 12, 0, 6,
    9, 3, 13, 4, 8, 7, 2, 5,
};
u8 D_8011E938_w02[16] = {
    14, 11, 6, 9, 12, 7, 3, 13,
    2, 4, 10, 19, 0, 8, 5, 1,
};
u8 D_8011E948_w02[16] = {
    14, 5, 9, 10, 11, 7, 19, 12,
    0, 6, 3, 13, 4, 8, 2, 1,
};
u8 D_8011E958_w02[16] = {
    14, 8, 13, 11, 10, 19, 6, 7,
    12, 0, 9, 3, 4, 2, 5, 1,
};
u8 D_8011E968_w02[16] = {
    14, 3, 11, 10, 19, 12, 0, 6,
    9, 13, 4, 8, 7, 2, 5, 1,
};
u8 D_8011E978_w02[16] = {
    14, 2, 9, 3, 6, 7, 8, 5,
    4, 19, 11, 13, 10, 12, 0, 1,
};
u8 D_8011E988_w02[16] = {
    14, 4, 19, 9, 11, 10, 3, 12,
    7, 0, 1, 6, 13, 8, 2, 5,
};
u8 *D_8011E998_w02[8] = {
    D_8011E918_w02, D_8011E928_w02, D_8011E938_w02, D_8011E948_w02,
    D_8011E958_w02, D_8011E968_w02, D_8011E978_w02, D_8011E988_w02,
};
s8 D_8011E9B8_w02[16] = {
    90, 70, 60, 30, 20, 20, 20, 20,
    10, 10, 10, 10, 10, 10, 10, 10,
};
s8 D_8011E9C8_w02[16] = {
    80, 50, 20, 20, 20, 10, 20, 10,
    10, 10, 20, 10, 10, 10, 10, 0,
};
s8 D_8011E9D8_w02[16] = {
    80, 30, 50, 30, 30, 20, 20, 20,
    20, 20, 30, 20, 30, 10, 10, 10,
};
s8 D_8011E9E8_w02[16] = {
    90, 50, 20, 30, 20, 10, 20, 10,
    30, 10, 10, 10, 10, 10, 10, 10,
};
s8 D_8011E9F8_w02[16] = {
    90, 50, 30, 30, 30, 20, 20, 20,
    10, 30, 10, 10, 10, 10, 10, 10,
};
s8 D_8011EA08_w02[16] = {
    90, 50, 30, 60, 20, 20, 30, 20,
    10, 10, 10, 10, 10, 10, 10, 10,
};
s8 D_8011EA18_w02[16] = {
    70, 40, 40, 40, 30, 20, 30, 30,
    20, 40, 40, 30, 40, 10, 40, 10,
};
s8 D_8011EA28_w02[16] = {
    80, 50, 60, 20, 20, 30, 20, 30,
    10, 30, 20, 10, 10, 10, 10, 10,
};
s8 *D_8011EA38_w02[8] = {
    D_8011E9B8_w02, D_8011E9C8_w02, D_8011E9D8_w02, D_8011E9E8_w02,
    D_8011E9F8_w02, D_8011EA08_w02, D_8011EA18_w02, D_8011EA28_w02,
};
DecisionTreeNonLeafNode *D_8011EA58_w02[2] = { D_8011E788_w02, D_8011E7AC_w02 };
DecisionTreeNonLeafNode *D_8011EA60_w02[2] = { D_8011E7D0_w02, D_8011E7E8_w02 };
DecisionTreeNonLeafNode *D_8011EA68_w02[2] = { D_8011E854_w02, D_8011E8E4_w02 };
u8 D_8011EA70_w02[4] = { 1, 2, 4, 8 };
char D_8011EA74_w02[4] = "%d";
const f64 D_8011EA78_w02 __attribute__((section(".data"))) = 1.5;
f32 D_8011EA80_w02[24] = {
    1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.0f, 2.0f,
    1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f, 2.0f, 1.0f, 1.0f, -1.0f, 1.0f,
};
const f64 D_8011EAE0_w02 __attribute__((section(".data"))) = 0.3;
const f64 D_8011EAE8_w02 __attribute__((section(".data"))) = 0.5;
const f64 D_8011EAF0_w02 __attribute__((section(".data"))) = 0.5;
const f64 D_8011EAF8_w02 __attribute__((section(".data"))) = 0.5;
const f64 D_8011EB00_w02 __attribute__((section(".data"))) = 0.5;
const f64 D_8011EB08_w02 __attribute__((section(".data"))) = 1.5;
const f64 D_8011EB10_w02 __attribute__((section(".data"))) = 0.8;
const f64 D_8011EB18_w02 __attribute__((section(".data"))) = 0.8;
s32 D_8011EB20_w02[5] = { 0x1301E1, 0x1301E2, 0x1301E3, 0x1301E4, 0x1301E5 };
f32 D_8011EB34_w02[5][2] = {
    { 160.0f, 120.0f },
    { -68.0f, -8.0f },
    { -23.0f, -8.0f },
    { 23.0f, -8.0f },
    { 68.0f, -8.0f },
};
