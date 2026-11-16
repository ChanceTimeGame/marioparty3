#include "SpinyDesert.h"
#include "common.h"
#include "game/object.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/10C230.h"

void func_80105DB0_w03(void);
void func_801061A0_w03(UnkMBGuideData*);
extern s16 D_8011C150_w03[];
extern Object* D_8011EAC8_w03[];
extern Process* D_8011EB08_w03;
extern Object* D_8011EB0C_w03;

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801059D0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801059F8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80105B44_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80105C50_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80105D20_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80105DB0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801061A0_w03);

// Star tour.
void func_8010622C_w03(void) {
    UnkMBGuideData *guide;
    Process *proc;
    SpaceData *first;
    SpaceData *second;
    SpaceData *temp;
    s32 mesNum;
    GW_SYSTEM* system = &GwSystem;

    D_800A12D4_main = 0;
    guide = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(guide->obj, 2, 0xF, 0xA007E);
    func_800FFF44_shared_board();
    MBModelDispOff(D_8011EAC8_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBModelDispOff(D_8011EAC8_w03[GwSystem.boardData.halfWordBytes[0]]);
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    func_800E6FCC_shared_board();
    func_800E9730_shared_board(3.0f);
    func_801061A0_w03(guide);

    first = MBMasuGet(D_8011C150_w03[system->star_spawn_indices[system->current_star_spawn]]);
    second = MBMasuGet(D_8011C150_w03[GwSystem.boardData.halfWordBytes[0]]);

    if (MBRandCheck100(50) != 0) {
        temp = first;
        first = second;
        second = temp;
    }
    
    if ((system->current_star_spawn == 0) && (GWBoardFlagCheck(4) == 0)) {
        mesNum = 0x5E09;
    } else {
        mesNum = 0x5E0A;
    }

    
    func_8005B43C_main(guide->amount, mesNum, -1, -1);
    func_80060C14_main(guide->amount, 1);
    HuAudFXPlay(0x2A7);
    temp = first;
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);
    func_8001FDE8_main(guide->obj->omObj1->model[0]);

    MBCameraPos3DSet(&temp->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    MBMotionSet(guide->obj, -1, 2);
    proc = omAddPrcObj(func_80105DB0_w03, 0x4800, 0, 0);
    D_8011EB08_w03 = proc;
    proc->user_data = temp;
    HuPrcSleep(30);
    D_800CC69C_main[guide->amount].unk20 = 1;
    HuPrcVSleep();
    func_80060C14_main(guide->amount, 1);
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);

    while (D_8011EB08_w03 != NULL) {
        HuPrcVSleep();
    }
    temp = second;
    MBCameraPos3DSet(&temp->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    proc = omAddPrcObj(func_80105DB0_w03, 0x4800, 0, 0);
    D_8011EB08_w03 = proc;
    proc->user_data = temp;
    HuPrcSleep(30);
    D_800CC69C_main[guide->amount].unk20 = 1;
    HuPrcVSleep();
    func_80060C14_main(guide->amount, 1);
    func_800EE2C0_shared_board(guide->amount);
    func_80060EA8_main(guide->amount, 1);

    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(2, 0x10);
    HuPrcSleep(0x11);
    D_800A12D4_main = 1;
    func_80100130_shared_board();
    func_80046558_main(D_8011EB0C_w03->omObj1->model[0]);
    MBModelKill(D_8011EB0C_w03);
    MBModelDispOn(D_8011EAC8_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBModelDispOn(D_8011EAC8_w03[GwSystem.boardData.halfWordBytes[0]]);
    MBGuideKill(guide);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}


INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801066CC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80106C2C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80106CA0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80106D28_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80106D84_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80106E54_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80106EB4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107148_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107360_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107490_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107628_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801078F4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107914_w03);

// entrypoint 0
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107934_w03);

// entrypoint 1
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107970_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107A04_w03);

// entrypoint 2
void func_80107CA4_w03() {
    HuAudSeqPlay(0x1A);
    D_800CE198_main = 0x1A;
    func_800F8D6C_shared_board(0x1A);
    Hu3DCamInit(2);
    func_80107A04_w03();
    MBMasuEventTblAdd(D_8011D1C4_w03);
    MBMasuEventTblAdd(D_8011D478_w03);
    MBHatenaFuncSet(func_8011A704_w03);
    MBMasuEventTblAdd(D_8011D23C_w03);
    MBMasuEventTblAdd(D_8011D3D0_w03);
    MBStart(0);
}

// entrypoint 3
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107D28_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107D54_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107ECC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107F30_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107FF8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108118_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108174_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108270_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801083DC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108444_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801085B0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108610_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010866C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108734_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801087E4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108820_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801088A0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108918_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E910_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801089AC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108AB8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108ADC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108B98_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108C48_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108C80_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108CB8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108CF0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108DA0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108DD8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108E30_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108E88_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108EE0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108F38_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109268_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801092C8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109328_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109388_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801093E8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109448_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801094A8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109508_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109568_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801095C8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109628_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109688_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801096E8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109748_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801097A8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109808_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109868_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801098C8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109AD8_w03);

void func_80109E90_w03(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109E98_w03);

void func_80109F3C_w03(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109F44_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010A1C8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010A284_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010A2C4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010A930_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010B46C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010B4F4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010B55C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010B734_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010C9EC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010CA8C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010CB2C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010CF74_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010CF98_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E98C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010DDC4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010DF18_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010DF54_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F128_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F144_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F160_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F2BC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F3D4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F79C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F808_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F9C8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010FC2C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010FCFC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010FF2C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801100FC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011026C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801105B8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011077C_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E998_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E9F8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80110A14_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80110CA0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80110EE0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801110F0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801113B0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80111750_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011214C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112694_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801128B0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112CA4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112D60_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112EB4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112EF0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80113080_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011343C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801136D4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801137E0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801139BC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80114668_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80114728_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80114C58_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80115564_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011569C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011580C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801159D4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80115C58_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011655C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116754_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801167CC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116830_w03);

// board p4
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EB2F0.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F9DE0.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/106640.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "input.h"
#include "game/window.h"
#include "game/hmfman.h"
extern Object *D_8011EBE0_w03[4];
void func_80116830_w03(omObjData *obj);
extern omObjData *D_8011EBF0_w03[4];
void func_80116ADC_w03(s32 arg);
void func_801167CC_w03(void);
void func_801169DC_w03(s32 arg0, s32 arg1);
void func_80116754_w03(s32 arg0);
void func_80116FE4_w03(void);
extern s32 D_8011EC04_w03;
s32 func_80109F44_w03(s32 arg0, s32 arg1);
void func_801175AC_w03(void);
extern s32 D_8011EC00_w03;
extern Vec2f D_8011D28C_w03[]; /* splat labels D_8011D28C (x) / D_8011D290 (rest): one Vec2f[4] */
void func_8010FF2C_w03(void);
void func_801100FC_w03(void);
extern Vec2f D_8011D2AC_w03[]; /* D_8011D2AC / D_8011D2B0 likewise */
s32 func_8011343C_w03(u8 *arg0, s32 arg1);
Process *func_8010FC2C_w03(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration);
extern s32 D_8011EB40_w03[];
extern DecisionTreeNonLeafNode D_8011E0DC_w03[];
extern DecisionTreeNonLeafNode D_8011E64C_w03[];
extern DecisionTreeNonLeafNode D_8011E3A0_w03[];
extern DecisionTreeNonLeafNode D_8011DF68_w03[];
extern s32 D_8011EBB8_w03;
extern DecisionTreeNonLeafNode D_8011DB9C_w03[];
extern DecisionTreeNonLeafNode D_8011DDD0_w03[];
s32 func_8011B470_w03(void);
extern DecisionTreeNonLeafNode D_8011E568_w03[];
s32 func_8011B51C_w03(void);
extern DecisionTreeNonLeafNode D_8011DB30_w03[];
extern DecisionTreeNonLeafNode D_8011E6B8_w03[];
extern DecisionTreeNonLeafNode D_8011E184_w03[];
extern s32 D_8011EBBC_w03;
extern DecisionTreeNonLeafNode *D_8011E8EC_w03[2];
extern s32 D_8011D0D0_w03;
extern u8 *D_8011E82C_w03[8];
extern DecisionTreeNonLeafNode *D_8011E8F4_w03[2];
extern s32 D_8011E7A8_w03;
s32 func_8010B4F4_w03(void);
s32 func_8010B46C_w03(s32 item);
extern s8 *D_8011E8CC_w03[8];
extern DecisionTreeNonLeafNode *D_8011E8FC_w03[];
// end board p4

void func_801169DC_w03(s32 arg0, s32 arg1) {
    GW_PLAYER *player = MBPlayerGet(arg0);
    Object *obj;
    u8 modelId;

    if (D_8011EBE0_w03[arg0] == NULL) {
        switch (arg1) {
            case 0:
                modelId = 0x3F;
                break;
            case 1:
                modelId = 0x40;
                break;
            case 2:
                modelId = 0x41;
                break;
            default:
                modelId = 0x42;
                break;
        }

        obj = MBModelCreate(modelId, NULL);
        MBModelTempAllocFree(obj);
        D_8011EBE0_w03[arg0] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        func_800D9A40_shared_board(D_8011EBE0_w03[arg0]);
    }
}


void func_80116ADC_w03(s32 arg) {
    D_8011EBF0_w03[arg] = omAddObj(0x3FFF, 0, 0, -1, func_80116830_w03);
    D_8011EBF0_w03[arg]->work[0] = arg;
    D_8011EBF0_w03[arg]->work[1] = 0;
    D_8011EBF0_w03[arg]->work[2] = 0;
    D_8011EBF0_w03[arg]->rot.x = (f32)MBRand(360.0f);
    D_8011EBF0_w03[arg]->trans.x = 0;
}


void func_80116B78_w03(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        D_8011EBF0_w03[i] = NULL;
        D_8011EBE0_w03[i] = NULL;
        idx = -!(MBPlayerGet(i)->rev & 0x2);
        if (MBPlayerGet(i)->rev & 0x4) {
            idx = 1;
        }
        if (MBPlayerGet(i)->rev & 0x20) {
            idx = 2;
        }
        if (MBPlayerGet(i)->rev & 0x40) {
            idx = 3;
        }
        if (idx != -1) {
            func_801169DC_w03(i, idx);
            func_80116ADC_w03(i);
        }
    }
    func_800F8D54_shared_board(func_801167CC_w03);
}


void func_80116C78_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    f32 scale;

    if ((((*slowDiceFlags >> loc->current_player_index) & 1))) {
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        if ((player->rev & 0x20) || ((player->rev & 8) && !(player->rev & 2))) {
            MBDlgWinExec(-1, 0x4219);
        } else {
            MBDlgWinExec(-1, 0x3A07);
        }

        if (player->rev & 2) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}


void func_80116E84_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        func_800DCA64_shared_board(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_80116754_w03(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}


void func_80116FE4_w03(void) {
    void *data;
    s32 i;

    i = 0x3C;
    data = HuPrcCurrentGet()->user_data;

    while (i != 0) {
        HuPrcVSleep();
        i--;
    }

    MBPlayerVibrateObjKill(data);
    omDelPrcObj(NULL);
}


void func_80117034_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player;
    s32 choice;
    s16 targetPlayer;
    UnkVibrateProcess *vib;
    s16 previousPlayer;
    f32 scale;
    f32 hudScale;

    MBDlgWinInsertCreate(-1, 0x5C01, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = func_80109F44_w03(2, D_8011EC04_w03);
    MBDlgWinClose();
    MBDlgWinKill();

    if (choice >= MB_MAX_PLAYERS) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else if (choice < 0) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else {
        targetPlayer = choice;
    }

    GwSystem.slow_dice_flags |= 1 << targetPlayer;
    player = MBPlayerGet(targetPlayer);

    for (scale = 1.0f, hudScale = 1.0f; scale > 0.0f;) {
        scale -= 0.1f;
        hudScale += 0.07f;
        MBStatusItemScaleSet(loc->current_player_index, MBItemSelNoGet(), scale, hudScale);
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&player->player_obj->coords);
        MBCameraPos3DSet(&player->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(0, 0x10);
        D_800A12D8_main = 1;
        HuPrcSleep(0x10);
    }

    func_80116754_w03(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    func_801169DC_w03(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    func_80116ADC_w03(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(func_80116FE4_w03, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    previousPlayer = loc->current_player_index;
    loc->current_player_index = targetPlayer;
    if (player->rev & 0x80) {
        MBDlgWinExec(-1, 0x3A09);
    }
    MBDlgWinExec(-1, 0x3A06);
    loc->current_player_index = previousPlayer;
    if (targetPlayer == (s8)previousPlayer) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, -1, 2);
        D_800A12D8_main = 0;
    }

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    }

    if (targetPlayer == loc->current_player_index) {
        GWBoardFlagSet(0x10);
        MBDlgWinExec(-1, 0x3A07);
        for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
            HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        func_80116754_w03(loc->current_player_index);
        func_800DCA64_shared_board(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}


void func_801175AC_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x80) {
        if ((player->rev & 0x40) || ((player->rev & 0x10) && !(player->rev & 4))) {
            MBDlgWinExec(-1, 0x421C);
        } else {
            MBDlgWinExec(-1, 0x3A03);
        }
        if (player->rev & 4) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}


void func_8011777C_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        func_800DCA64_shared_board(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_80116754_w03(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}


void func_801178B4_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player;
    s32 choice;
    s16 targetPlayer;
    s16 previousPlayer;
    f32 scale;
    f32 hudScale;
    UnkVibrateProcess *vib;

    MBDlgWinInsertCreate(-1, 0x5C01, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = func_80109F44_w03(2, D_8011EC00_w03);
    MBDlgWinClose();
    MBDlgWinKill();

    if (choice >= MB_MAX_PLAYERS) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else if (choice < 0) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else {
        targetPlayer = choice;
    }

    player = MBPlayerGet(targetPlayer);
    player->rev |= 0x80;

    for (scale = 1.0f, hudScale = 1.0f; scale > 0.0f;) {
        scale -= 0.1f;
        hudScale += 0.07f;
        MBStatusItemScaleSet(loc->current_player_index, MBItemSelNoGet(), scale, hudScale);
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&player->player_obj->coords);
        MBCameraPos3DSet(&player->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(0, 0x10);
        D_800A12D8_main = 1;
        HuPrcSleep(0x10);
    }

    func_80116754_w03(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    func_801169DC_w03(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011EBE0_w03[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    func_80116ADC_w03(targetPlayer);
    omAddPrcObj(func_80116FE4_w03, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    previousPlayer = loc->current_player_index;
    loc->current_player_index = targetPlayer;
    if (((previousPlayer == targetPlayer) && (func_800DEB2C_shared_board(previousPlayer) == 3)) ||
        ((GwSystem.slow_dice_flags >> targetPlayer) & 1)) {
        MBDlgWinExec(-1, 0x3A05);
    }
    MBDlgWinExec(-1, 0x3A02);
    loc->current_player_index = previousPlayer;
    if (targetPlayer == (s8)previousPlayer) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, -1, 2);
        D_800A12D8_main = 0;
    }

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    }

    if (targetPlayer == loc->current_player_index) {
        func_801175AC_w03();
    }
}


void func_80117D38_w03(void) {
    char playerNames[4][16];
    u8 choices[16];
    Object *chest;
    Process *process;
    GW_SYSTEM *system = &GwSystem;
    s32 targetPlayer = 0;
    s32 itemSlot;
    s32 i;
    f32 angle;
    u32 *motion;

    func_8010FF2C_w03();
    chest = MBModelCreate(0x21, NULL);
    Hu3DModelScaleSet(chest->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&chest->coords, &MBPlayerGet(-1)->player_obj->coords);
    func_8001C814_main(chest->omObj1->model[0], 2, 1);
    chest->velocity.x = 100.0f;
    HuAudFXPlay(0x142);
    while (chest->velocity.x > 30.0f) {
        chest->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    if (targetPlayer != 0) {
        for (i = 0; i < 1081; i += 30) {
            angle = sindf((f32)i) / 2.0f + 1.0f;
            HuVecCopyXYZ(&chest->scale, angle, sindf((f32)i) / 2.0f + 1.0f,
                         sindf((f32)i) / 2.0f + 1.0f);
            HuPrcVSleep();
        }
    }

    HuAudFXPlay(0x149);
    func_8001C814_main(chest->omObj1->model[0], 1, 0);
    HuPrcSleep(20);

    for (i = 0; i < 4; i++) {
        if (GwSystem.current_player_index == i) {
            playerNames[i][0] = 1;
            choices[i] = 0;
        } else {
            playerNames[i][0] = 8;
            choices[i] = 1;
        }
        func_800E2260_shared_board(i, &playerNames[i][1]);
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(-1, 0x5C01, (s32)playerNames[0], (s32)playerNames[1], (s32)playerNames[2],
                         (s32)playerNames[3], 0);
    targetPlayer = func_8011343C_w03(choices, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    if (targetPlayer == 4) {
        targetPlayer = func_800EF0D8_shared_board(1);
    }

    if (GwPlayer[targetPlayer].itemNo[0] == -1) {
        MBPlayerMotionSet(-1, 3, 0);
        func_8004ACE0_main(0x286, system->current_player_index);
        HuPrcSleep(60);
        func_800E2260_shared_board(targetPlayer, playerNames[0]);
        MBWinInsertOpen(0x3A0F, playerNames[0], 0, 0, 0, 0);
        func_800EC3C0_shared_board(system->current_player_index);
        func_800EC3E4_shared_board();
        func_800F2388_shared_board(-1, -1, 0, 10, 2);
        MBModelKill(chest);
        GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
        MBItemRemoveEmpty(system->current_player_index);
        return;
    }

    itemSlot = MBItemFindEmpty(targetPlayer);
    if (itemSlot == -1) {
        itemSlot = 3;
    }
    itemSlot = MBRand((f32)itemSlot);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] =
        GwPlayer[targetPlayer].itemNo[itemSlot];
    GwPlayer[targetPlayer].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(targetPlayer);
    MBPlayerVibrate((s16)targetPlayer, 3);
    if (MBItemSelNoGet() == itemSlot) {
        MBStatusItemTPLvlSet(targetPlayer, MBItemSelNoGet(), 0);
    }
    MBStatusItemSprKill(-1);
    MBStatusItemPosSet(system->current_player_index, MBItemSelNoGet(),
                       D_8011D2AC_w03[system->current_player_index].x,
                       D_8011D2AC_w03[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010FC2C_w03(-1,
                                            D_8011D2AC_w03[system->current_player_index].x,
                                            D_8011D2AC_w03[system->current_player_index].y,
                                            D_8011D28C_w03[system->current_player_index].x,
                                            D_8011D28C_w03[system->current_player_index].y, 5));
    HuPrcChildWait();
    func_8004ACE0_main(0x274, system->current_player_index);
    MBPlayerMotionLoad(system->current_player_index, 5, 0x31);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(50);
    func_800F2388_shared_board(system->current_player_index, -1, 0, 10, 2);
    HuPrcSleep(11);
    motion = D_80101734_shared_board[0];
    for (i = 6; i != 0; i--) {
        motion++;
    }
    MBPlayerMotionLoad(system->current_player_index, 5, ((u16 *)motion)[1]);
    MBModelKill(chest);
    MBDlgWinInsertCreate(-1, 0x3A0D, GwPlayer[targetPlayer].chr + 0x1C00,
                         GwPlayer[system->current_player_index].chr + 0x1C00, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    func_801100FC_w03();
}


void func_801183E0_w03(void) {
    s32 spr[3][4];
    s32 titleSpr;
    s32 frameSpr;
    s32 grp;
    Process *proc;
    Unk3 *win;
    void *data;
    s32 playerGrp;
    s32 alpha;
    s32 mask;
    s32 clamped;
    s32 fading;
    s32 wrapped;
    s32 count;
    s32 i;
    s32 j;
    f32 angle;
    f32 speed;

    i = 0;
    proc = HuPrcCurrentGet();
    data = DataRead(0x1300F7);
    titleSpr = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300F8);
    spr[0][0] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300FB);
    spr[0][1] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300F9);
    spr[0][2] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300FA);
    spr[0][3] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300FC);
    frameSpr = func_80055810_main(data);
    DataClose(data);
    for (; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 8) | 0x210000);
        spr[1][i] = func_80055810_main(data);
        DataClose(data);
    }
    grp = HuSprGrpCreate(1, 5);
    func_80055024_main(grp, 0, titleSpr, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x1008);
    HuSprPriSet(grp, 0, 0x1000);
    func_80054904_main(grp, 0, 0xA0, 0x5A);
    angle = 0.0f;
    speed = 30.0f;
    count = 0;
    wrapped = 0;
    while (1) {
        if ((angle >= 90.0f) & (wrapped == 0)) {
            wrapped = 1;
            count++;
        }
        if (angle >= 360.0f) {
            wrapped = 0;
            angle -= 360.0f;
        }
        if ((angle >= 180.0f) & (angle <= 360.0f)) {
            HuSprAttrSet(grp, 0, 2);
        } else {
            HuSprAttrReset(grp, 0, 2);
        }
        HuSprScaleSet(grp, 0, 1.0f, sindf(angle >= 180.0f ? angle - 180.0f : angle));
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }
    HuSprAttrReset(grp, 0, 2);
    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    win = func_800E210C_shared_board(0x14, 0xA0, 1);
    for (i = 0; i < 4; i++) {
        playerGrp = spr[2][i] = HuSprGrpCreate(6, 5);
        func_80055024_main(playerGrp, 0, frameSpr, 0);
        func_800550F4_main(playerGrp, 0, 0);
        HuSprAttrReset(playerGrp, 0, 0xFFFF);
        if (D_8011EB40_w03[i] != 0) {
            HuSprAttrSet(playerGrp, 0, 8);
        } else {
            HuSprAttrSet(playerGrp, 0, 0x8000);
        }
        HuSprPriSet(playerGrp, 0, 0x1000);
        func_800554C4_main(playerGrp, 0, -1);
        func_80055024_main(playerGrp, 1, spr[1][i], 0);
        func_800550F4_main(playerGrp, 1, 0);
        HuSprAttrReset(playerGrp, 1, 0xFFFF);
        if (D_8011EB40_w03[i] != 0) {
            HuSprAttrSet(playerGrp, 1, 8);
        } else {
            HuSprAttrSet(playerGrp, 1, 0x8000);
        }
        HuSprPriSet(playerGrp, 1, 0x1000);
        func_80054904_main(playerGrp, 1, 0, -9);
        func_800554C4_main(playerGrp, 1, 0);
        for (j = 0; j < 4; j++) {
            func_80055024_main(playerGrp, j + 2, spr[0][j], 0);
            func_800550F4_main(playerGrp, j + 2, 1);
            HuSprAttrReset(playerGrp, j + 2, 0xFFFF);
            if (D_8011EB40_w03[i] == j + 1) {
                HuSprAttrSet(playerGrp, j + 2, 8);
            } else {
                HuSprAttrSet(playerGrp, j + 2, 0x8000);
            }
            HuSprPriSet(playerGrp, j + 2, 0x1000);
            func_80054904_main(playerGrp, j + 2, 0, 9);
            func_800554C4_main(playerGrp, j + 2, 0);
        }
        func_80054904_main(playerGrp, 0, i * 70 + 55, 200);
    }
    HuPrcSleep(20);
    angle = 90.0f;
    count = 0;
    fading = 0;
    wrapped = 0;
    alpha = 255;
    while (1) {
        if ((angle >= 360.0f) & (wrapped == 0)) {
            wrapped = 1;
            count++;
        }
        if (angle >= 360.0f) {
            wrapped = 0;
            angle -= 360.0f;
        }
        if ((fading == 0) & (count != 0)) {
            if ((angle >= 90.0f) & (angle < 180.0f)) {
                fading = 1;
            }
        }
        if (fading != 0) {
            alpha -= 21;
            mask = -(alpha > 0);
            clamped = mask & alpha;
            alpha = clamped;
        }
        func_80055458_main(grp, 0, alpha);
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }
    HuSprScaleSet(grp, 0, 1.0f, 0.0f);
    HuSprGrpKill(grp);
    HuSprKill(titleSpr);
    proc->user_data = (void *)1;
    while (1) {
        for (i = 0; i < 4; i++) {
            switch (D_8011EB40_w03[i]) {
            case 0:
                for (j = 0; j < 6; j++) {
                    HuSprAttrSet(spr[2][i], j, 0x8000);
                }
                break;
            case 1:
                for (j = 0; j < 6; j++) {
                    HuSprAttrReset(spr[2][i], j, 0x8000);
                }
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(spr[2][i], j + 2, 0x8000);
                }
                HuSprAttrReset(spr[2][i], 2, 0x8000);
                break;
            case 2:
                for (j = 0; j < 6; j++) {
                    HuSprAttrReset(spr[2][i], j, 0x8000);
                }
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(spr[2][i], j + 2, 0x8000);
                }
                HuSprAttrReset(spr[2][i], 3, 0x8000);
                break;
            case 3:
                for (j = 0; j < 6; j++) {
                    HuSprAttrReset(spr[2][i], j, 0x8000);
                }
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(spr[2][i], j + 2, 0x8000);
                }
                HuSprAttrReset(spr[2][i], 4, 0x8000);
                break;
            case 4:
                for (j = 0; j < 6; j++) {
                    HuSprAttrReset(spr[2][i], j, 0x8000);
                }
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(spr[2][i], j + 2, 0x8000);
                }
                HuSprAttrReset(spr[2][i], 5, 0x8000);
                break;
            default:
                goto end;
            }
        }
        HuPrcVSleep();
    }
end:
    MBHelpWinKill(win);
    HuSprKill(frameSpr);
    for (i = 0; i < 4; i++) {
        HuSprKill(spr[0][i]);
        HuSprKill(spr[1][i]);
        HuSprGrpKill(spr[2][i]);
    }
    omDelPrcObj(NULL);
}


INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80118E3C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80118F64_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011908C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80119120_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80119290_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011A2BC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011A338_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011A550_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011A704_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B1FC_w03);

// entrypoint 4
void func_8011B41C_w03() {
    Hu3DCamInit(2);
    CameraScissorSet(1, &D_8011D598_w03);
    func_80107A04_w03();
    MBStart(2);
    omAddPrcObj(func_8010622C_w03, 0x1005, 0x1000, 0);
}

s32 func_8011B470_w03(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    for (i = 0, bestRank = 99, best = MBPlayerTurnGet(); i < 4; i++) {
        if (i != MBPlayerTurnGet()) {
            func_800DA778_shared_board(i);
            if ((MBComTreeExec(D_8011E0DC_w03) == 0) &&
                (BoardPlayerRankCalc(i) < bestRank)) {
                bestRank = BoardPlayerRankCalc(i);
                best = i;
            }
        }
    }
    return best;
}


s32 func_8011B51C_w03(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    best = MBPlayerTurnGet();
    if (MBComTreeExec(D_8011E3A0_w03) != 0) {
        for (i = 0, bestRank = 99; i < 4; i++) {
            if (i != MBPlayerTurnGet()) {
                func_800DA778_shared_board(i);
                if ((MBComTreeExec(D_8011E64C_w03) == 0) &&
                    (BoardPlayerRankCalc(i) < bestRank)) {
                    bestRank = BoardPlayerRankCalc(i);
                    best = i;
                }
            }
        }
    }
    return best;
}


s32 func_8011B5E0_w03(void) {
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


s32 func_8011B634_w03(s32 base, s32 perLevel) {
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


s32 func_8011B71C_w03(void) {
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
                if (func_8011B5E0_w03() != 0) {
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
                if (MBRandCheck100(70) != 0 && func_8011B5E0_w03() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (func_8011B5E0_w03() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011DB30_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (func_8011B5E0_w03() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011DB9C_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(D_8011DDD0_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(D_8011E184_w03) == 0) {
                    s32 target = func_8011B470_w03();

                    D_8011EC04_w03 = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(D_8011E568_w03) == 0) {
                    s32 target = func_8011B51C_w03();

                    D_8011EC00_w03 = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, D_8011EBBC_w03 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < D_80100FA8_shared_board[it]) {
                                    best = D_80100FA8_shared_board[it];
                                    D_8011EBBC_w03 = i;
                                }
                            }
                        }
                    }
                }
                if (D_8011EBBC_w03 == -1) {
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
                for (i = 0, D_8011EBB8_w03 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += D_80100FA8_shared_board[it];
                            }
                        }
                        if (best < count) {
                            D_8011EBB8_w03 = i;
                            best = count;
                        }
                    }
                }
                if (D_8011EBB8_w03 == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (func_8011B634_w03(0x32, 0xA) == 0) {
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
                if (func_8011B634_w03(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(D_8011DF68_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && func_8011B5E0_w03() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(D_8011E6B8_w03) != 0) {
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


s32 func_8011BD24_w03(void) {
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
        temp_s0 = D_8011E82C_w03[temp_s3->chr][i];
        var_s2 = func_8010B46C_w03(temp_s0);
        if (var_s2 != -1 && D_80100F94_shared_board[temp_s0] + 20 <= GwPlayer[system->current_player_index].coin &&
            MBRandCheck100(D_8011E8CC_w03[temp_s3->chr][i])) {
            break;
        }
    }
    if (i == 16) {
        var_s2 = -1;
    }

    if (var_s2 != -1) {
        if ((func_8010B46C_w03(0xE) != var_s2) &&
        ((func_8010B46C_w03(0xB) != var_s2) ||
        ((D_80100F94_shared_board[0xB] + 50) > (GwPlayer[system->current_player_index].coin)) != 0)) {
            if ((func_8010B46C_w03(4) == var_s2) &&
            (MBItemFind(system->current_player_index, 4) != -1)) {
                var_s2 = -1;
                sp14 = 0;
            }
        } else {
            return var_s2 + 1;
        }
    }
    if ((MBComTreeExec(D_8011E8EC_w03[D_8011D0D0_w03]) == 0) && GwPlayer[system->current_player_index].coin >= D_80100F94_shared_board[1]) {
        temp_v0 = func_8010B46C_w03(1);
        if (temp_v0 != -1) {
            return temp_v0 + 1;
        }
    }
    if (var_s2 == -1) {
        i = MBComTreeExec(D_8011E8F4_w03[D_8011D0D0_w03]);
        if (i == 0) {
            do {
                temp_s0_2 = D_8011E82C_w03[temp_s3->chr][i];
                //this line below has to be written very specific
                if ((temp_s0_2 == 4 && sp14 == 0) == 0) {
                    var_s2_2 = func_8010B46C_w03(temp_s0_2);
                    if ((var_s2_2 != -1) && !(D_80100F94_shared_board[temp_s0_2] > (GwPlayer[system->current_player_index].coin))) {
                        if ((MBRandCheck100(D_8011E8CC_w03[temp_s3->chr][i]))) {
                            return var_s2_2 + 1;
                        }
                    }
                }
            } while (++i < 16);
        }

        var_s2_2 = func_8010B46C_w03(0);
        if (var_s2_2 == -1) {
            D_8011E7A8_w03 = 1;
            return func_8010B4F4_w03() + 2;
        }
        return var_s2_2 + 1;
    }
    return var_s2 + 1;
}


s32 func_8011C088_w03(void) {
    if (D_8011E7A8_w03 != 0) {
        D_8011E7A8_w03 = 0;
        return 2;
    }
    return MBComTreeExec(D_8011E8FC_w03[D_8011D0D0_w03]) + 1;
}

