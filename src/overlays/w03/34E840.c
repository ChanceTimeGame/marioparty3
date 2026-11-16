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

// board p3: declarations for func_801110F0_w03..func_80116830_w03 (twins of w06's item and branch code)
#include "gcc/memory.h"
#include "mallocblock.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/EB2F0.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/F9DE0.h"
#include "../ovl_80_shared_board/FFB10.h"

typedef struct p3BranchLink {
    /* 0x00 */ s16 link;
    /* 0x02 */ s16 idx;
    /* 0x04 */ s16 rev;
} p3BranchLink; // size 0x6

typedef struct {
    /* 0x00 */ u16 multiplier;
    /* 0x02 */ u16 threshold;
} p3GameGuyReward;

typedef struct {
    /* 0x00 */ Object *obj1;
    /* 0x04 */ Object *obj2;
    /* 0x08 */ s32 state;
    /* 0x0C */ s32 flag;
} p3ModelAnimWork;

typedef struct {
    u8 unk[4];
} p3Unk4Bytes;

typedef struct {
    Vec v[8];
} p3VecTable8;

// The velocity table func_8010F3D4_w03 emits first (GCC shares the constant); extern while that function is asm.
extern const Vec D_8011E998_w03[8];

typedef s16 p3SpaceTriple[3];
typedef p3BranchLink p3BranchPair[2];

extern s16 D_8011C140_w03[];
extern Vec2f D_8011D0E4_w03[];
extern Vec2f D_8011D104_w03[];
extern Vec2f D_8011D24C_w03[];
extern DecisionTreeNonLeafNode D_8011D2CC_w03[];
extern DecisionTreeNonLeafNode D_8011D34C_w03[];
extern Vec2f D_8011D358_w03[];
extern s32 D_8011D388_w03;
extern u8 D_8011D38C_w03[];
extern u8 D_8011D390_w03[];
extern p3GameGuyReward D_8011D394_w03[];
extern RGB D_8011D3B0_w03[];
extern const u8 D_8011E910_w03[];
extern const char D_8011E98C_w03[];
extern Process *D_8011EAE8_w03[8];
extern s32 D_8011EBA4_w03;
extern s32 D_8011EBA8_w03;
extern s32 D_8011EBAC_w03;
extern Object *D_8011EBB0_w03;
extern Object *D_8011EBB4_w03;
extern s32 D_8011EBB8_w03;
extern s32 D_8011EBBC_w03;
extern Object *D_8011EBC0_w03;
extern s32 D_8011EBC8_w03[4];
extern Object *D_8011EBD8_w03;
extern Object *D_8011EBE0_w03[4];
extern omObjData *D_8011EBF0_w03[4];

void func_80106D28_w03(void);
void func_80106D84_w03(void);
void func_80106E54_w03(void);
void func_80108174_w03(void);
s32 func_80109F44_w03(s32 arg0, s32 arg1);
void func_8010A1C8_w03(s16 arg0, s32 arg1, s16 arg2, s32 arg3);
void func_8010A284_w03(void);
void func_8010B734_w03(void);
omObjData *func_8010F160_w03(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5);
Process *func_8010FC2C_w03(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration);
void func_8010FF2C_w03(void);
void func_801105B8_w03(void);
void func_8011077C_w03(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode);
void func_80110EE0_w03(void);
void func_801110F0_w03(void);
void func_801113B0_w03(void);
void func_80111750_w03(void);
void func_8011214C_w03(void);
void func_80112694_w03(void);
void func_801128B0_w03(void);
void func_80112CA4_w03(void);
void func_80112D60_w03(void);
void func_80112EF0_w03(void);
void func_80113080_w03(void);
s32 func_8011343C_w03(u8 *arg0, s32 arg1);
void func_801139BC_w03(void);
void func_80114728_w03(void);
void func_80114C58_w03(void);
void func_80115C58_w03(void);
void func_8011655C_w03(s16 (*masu)[3], p3BranchLink (*links)[2], DecisionTreeNonLeafNode **trees);
void func_80116830_w03(omObjData *arg0);

void func_801110F0_w03(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011EBA4_w03 = func_80055810_main(data);
    DataClose(data);
    func_801105B8_w03();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = func_80109F44_w03((s32)D_8011D2CC_w03, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(func_8010A284_w03, 0, 0, 0);
                omPrcSetStatBit(process, 0x80);
                func_80106D28_w03();
                one = 1;
                D_800CB99C_main = one;
                func_80049FB8_main();
                omDelPrcObj(process);
                func_800FC8A4_shared_board();
                continue;
            }
            GwSystem.forceShopHost = choice + 1;
            break;
        }

        process = omAddPrcObj(func_8010A284_w03, 0, 0, 0);
        omPrcSetStatBit(process, 0x80);
        func_80106D28_w03();
        one = 1;
        D_800CB99C_main = one;
        func_80049FB8_main();
        omDelPrcObj(process);
        func_800FC8A4_shared_board();
        continue;
    }

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110EE0_w03, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110EE0_w03, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);
    }

    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprKill(D_8011EBA4_w03);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (choice != 0) {
        HuAudFXPlay(0x2A0);
    } else if (GwPlayer[loc->current_player_index].coin < 5 ||
               loc->current_turn == loc->total_turns) {
        HuAudFXPlay(0x29A);
    } else {
        HuAudFXPlay(0x298);
    }
    func_8010B734_w03();
    GwSystem.forceShopHost = 0;
}

void func_801113B0_w03(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011EBA4_w03 = func_80055810_main(data);
    DataClose(data);
    func_801105B8_w03();

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110EE0_w03, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110EE0_w03, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);
    }

    HuAudFXPlay(0x29F);
retry:
    MBDlgWinInsertCreate(4, 0x3A0A,
                         mbCharNameMesTbl[GwPlayer[0].chr],
                         mbCharNameMesTbl[GwPlayer[1].chr],
                         mbCharNameMesTbl[GwPlayer[2].chr],
                         mbCharNameMesTbl[GwPlayer[3].chr], 0);
    if (GwPlayer[loc->current_player_index].coin != 0) {
        choice = func_80109F44_w03(1, 0);
    } else {
        choice = func_80109F44_w03(2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = func_800EF0D8_shared_board(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(func_8010A284_w03, 0, 0, 0);
            omPrcSetStatBit(process, 0x80);
            func_80106D28_w03();
            one = 1;
            D_800CB99C_main = one;
            func_80049FB8_main();
            omDelPrcObj(process);
            func_800FC8A4_shared_board();
            goto retry;
        default:
            MBDlgWinInsertCreate(4, 0x3A0B,
                                 mbCharNameMesTbl[GwPlayer[choice].chr],
                                 0, 0, 0, 0);
            break;
    }
    MBDlgWinClose();
    MBDlgWinKill();

    HuAudFXPlay(0x29C);
    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprKill(D_8011EBA4_w03);

    if (func_800DEB2C_shared_board(loc->current_player_index) == 3) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }
    GwSystem.playerIndexVisitingBowser = choice;
    func_800FCA4C_shared_board();
    func_800FF794_shared_board(0x50, 0, 3, 1);
    func_800FC8A4_shared_board();
    func_800FF7F0_shared_board(2);
    func_8004A0E0_main();
    HuPrcSleep(-1);
}

void func_80111750_w03(void) {
    s32 i;
    s32 j;
    s32 wipeStarted;
    GW_SYSTEM *system = &GwSystem;
    Object *lamp;
    Object *starModel;
    Object *targetStar;
    Process *process;
    Process *dialogProcess;
    Vec direction;
    Vec pos;
    Vec destination;
    s32 angle;
    s32 alpha;
    f32 speed;
    f32 rotation;
    void *dialog;

    {
        GW_PLAYER *player;

        player = MBPlayerGet(-1);
        lamp = MBModelCreate(0x3C, NULL);
        MBMotionSet(lamp, -1, 1);
        Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        HuVecCopy3F(&lamp->coords, &player->player_obj->coords);
        lamp->velocity.x = 30.0f;
        lamp->flags |= 1;
        HuVecCopyXYZ(&lamp->scale, 0.0f, 0.0f, 0.0f);
        MBModelDispOff(lamp);
        func_8010FF2C_w03();

        {
            s32 itemSlot = MBItemFind(-1, 9);

            GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
        }
        MBItemRemoveEmpty(system->current_player_index);

        starModel = MBModelCreate(0x3D, NULL);
        func_8001FA68_main(starModel->omObj1->model[0]);
        func_8001F9E4_main(starModel->omObj1->model[0], 0xFF);
        Hu3DModelScaleSet(starModel->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        HuVecCopy3F(&starModel->coords, &player->player_obj->coords);
        starModel->coords.y = 100.0f;
        while (starModel->coords.y > 30.0f) {
            starModel->coords.y -= 1.0f;
            HuPrcVSleep();
        }
    }

    HuAudFXPlay(0x127);
    func_800039A4_main(D_800CDBC8_main, 0xB4);
    dialog = MBPlayerVibrateObjCreate(-1, 3, 5);

    for (angle = 180, i = 0; angle < 1080; angle += 20, i++) {
        p3VecTable8 velocities = *(p3VecTable8 *)D_8011E998_w03;

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010F160_w03(&pos, 0.1f, 2.0f, 1,
                                     &velocities.v[(i / 2) & 7], 1);
        }
        HuPrcVSleep();
    }

    alpha = 0xFF;
    speed = 0.0f;
    while (1) {
        p3VecTable8 velocities2 = *(p3VecTable8 *)D_8011E998_w03;

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010F160_w03(&pos, 0.1f, 2.0f, 1,
                                     &velocities2.v[(i / 2) & 7], 1);
        }

        if (alpha > 0) {
            func_8001F9E4_main(starModel->omObj1->model[0], alpha & 0xFF);
            alpha -= 12;
        } else {
            MBModelDispOff(starModel);
            func_800D9A40_shared_board(lamp);
            speed += 0.1f;
            lamp->scale.z = speed;
            lamp->scale.y = speed;
            lamp->scale.x = speed;
            if (speed > 1.0f) {
                HuAudSeqPlay(0x3D);
                break;
            }
        }
        i++;
        HuPrcVSleep();
    }

    lamp->scale.x = lamp->scale.y = lamp->scale.z = 1.0f;
    dialogProcess = func_800EDB98_shared_board(lamp, 3.0f, 2.0f);
    MBPlayerVibrateObjKill(dialog);
    HuPrcSleep(30);
    MBDlgWinExec(0x3C, 0x3A2F);
    omDelPrcObj(dialogProcess);

    i = 1;
    lamp->coords.y -= lamp->velocity.x;
    HuVecSubtract(&direction, &gCameraList->pos, &lamp->coords);
    MBVecNormalize(&direction);
    lamp->coords.y += lamp->velocity.x;

    while (lamp->velocity.x < 1800.0f) {
        lamp->coords.x += direction.x * 40.2f;
        lamp->velocity.x += direction.y * 40.0f;
        lamp->coords.z += direction.z * 40.2f;
        if ((lamp->velocity.x > 300.0f) && (i != 0)) {
            i = 0;
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(0xB, 0x32);
            HuAudFXPlay(0x128);
        }
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    {
        SpaceData *space;
        SpaceData *nextSpace;

        space = MBMasuGet(D_8011C140_w03[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(D_8011C150_w03[system->star_spawn_indices[system->current_star_spawn]]);
        HuVecCopy3F(&destination, &space->coords);
        MBCameraPos3DSet(&destination);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&destination);
        lamp->flags &= ~1;
        HuVecCopy3F(&lamp->coords, &space->coords);
        HuVecSubtract(&direction, &nextSpace->coords, &space->coords);
        MBVecNormalize(&direction);
        lamp->coords.x -= direction.x * 20.0f;
        lamp->coords.z -= direction.z * 20.0f;
    }

    HuAudFXPlay(0x129);
    WipeCreateIn(0xB, 0x32);
    lamp->velocity.x = 100.0f;
    while (lamp->velocity.x > 30.0f) {
        HuPrcVSleep();
        lamp->velocity.x -= 3.0f;
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_800ED128_shared_board(&lamp->rot,
                                                     &direction,
                                                     &lamp->rot, 0x10));
    i = 0;
    HuPrcChildWait();
    dialogProcess = func_800EDB98_shared_board(lamp, 3.0f, 2.0f);
    MBDlgWinExec(0x3C, 0x3A30);
    HuAudFXPlay(0x12C);
    MBMotionSet(lamp, -1, 0);
    HuPrcSleep(20);

    wipeStarted = 1;
    for (j = 0; j < 8; j++) {
        if (D_8011EAE8_w03[j] != NULL) {
            omDelPrcObj(D_8011EAE8_w03[j]);
            D_8011EAE8_w03[j] = NULL;
        }
    }

    targetStar = D_8011EAC8_w03[system->star_spawn_indices[system->current_star_spawn]];
    HuAudSeqFadeOut(0x5A);
    rotation = 0.0f;
    while (targetStar->velocity.x < 400.0f) {
        targetStar->velocity.x += 3.0f;
        targetStar->coords.x += direction.x * 3.0f;
        targetStar->coords.z += direction.z * 3.0f;
        targetStar->rot.x = -sindf(rotation);
        targetStar->rot.z = cosdf(rotation);
        rotation += 45.0f;
        if (rotation > 360.0f) {
            rotation -= 360.0f;
        }
        if ((targetStar->velocity.x > 50.0f) && (wipeStarted != 0)) {
            if (func_800DEB2C_shared_board(system->current_player_index) == 3) {
                GWBoardFlagSet(0x17);
            } else {
                GWBoardFlagClear(0x17);
            }
            wipeStarted = 0;
            WipeColorSet(0, 0, 0);
            omDelPrcObj(dialogProcess);
            func_800EDA58_shared_board();
            func_800FC8A4_shared_board();
            func_800FF7F0_shared_board(2);
            func_800FCA14_shared_board();
            func_8004A0E0_main();
        }
        HuPrcVSleep();
    }
    HuPrcSleep(-1);
}

void func_8011214C_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 player;
    Process *process;
    s32 group;
    void *sprite;
    s32 spriteCount;
    s32 i;
    f32 position[2];
    s32 result;

    player = GwSystem.current_player_index;
    group = HuSprGrpCreate(1, 0);
    sprite = DataRead(D_8010197C_shared_board[1]);
    spriteCount = func_80055810_main(sprite);
    DataClose(sprite);
    func_80055024_main(group, 0, spriteCount, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x9000);
    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010FC2C_w03(mbItemCursorGrpId, position[0], position[1],
                                            D_8011D24C_w03[system->current_player_index].x,
                                            D_8011D24C_w03[system->current_player_index].y, -1));
    HuPrcChildWait();
    HuPrcSleep(10);
    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - i * 25);
        HuPrcVSleep();
    }
    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
    GwPlayer[player].itemNo[MBItemSelNoGet()] = -1;
    MBStatusItemTPLvlSet(player, MBItemSelNoGet(), 0);
    func_800F6848_shared_board(player, MBItemSelNoGet(), &position[0], &position[1]);
    func_80054904_main(group, 0, position[0], position[1]);
    HuSprAttrReset(group, 0, 0x8000);
    MBItemRemoveEmpty(player);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
retry:
    MBDlgWinInsertCreate(0x38, 0x4100, 0, 0, 0, 0, 0);
    result = func_80109F44_w03((s32)&D_8011D34C_w03, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    switch (result) {
        case 0:
            MBDlgWinInsertCreate(0x38, 0x4101, 0, 0, 0, 0, 0);
            break;
        case 1:
            MBDlgWinInsertCreate(0x38, 0x4102, 0, 0, 0, 0, 0);
            HuSprAttrSet(group, 0, 0x8000);
            GwPlayer[player].itemNo[MBItemFindEmpty(player)] = 1;
            MBItemRemoveEmpty(player);
            GwSystem.cur_player_used_item &= ~1;
            break;
        default:
            HuSprAttrSet(group, 0, 0x8000);
            func_80106D28_w03();
            D_800CB99C_main = 1;
            func_80049FB8_main();
            HuSprAttrReset(group, 0, 0x8000);
            goto retry;
    }
    MBDlgWinClose();
    MBDlgWinKill();
    if (result == 0) {
        HuPrcSleep(10);
        for (i = 1; i < 0x40; i++) {
            func_80055458_main(group, 0, (u16)(255.0f - (f32)i * 3.984f));
            HuPrcVSleep();
        }
        func_80055458_main(group, 0, 0);
    }
    HuSprGrpKill(group);
    HuSprKill(spriteCount);
}

void func_80112694_w03(void) {
    s32 playerIndex;
    s32 group;
    s16 setupGroup;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    f32 scale;
    s32 alpha;

    playerIndex = (s32)HuPrcCurrentGet()->user_data;
    group = HuSprGrpCreate(1, 0);
    setupGroup = group;
    func_80055024_main(setupGroup, 0, D_8011EBAC_w03, 0);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, 0x1000);
    MBStatusItemPosGet(D_8011EBA8_w03, 0, &xPos, &yPos);

    xPos = (s32)((D_8011D104_w03[D_8011EBA8_w03].x * 16.0f) +
                 D_8011D0E4_w03[D_8011EBA8_w03].x);
    yPos = (s32)((D_8011D104_w03[D_8011EBA8_w03].y * 16.0f) +
                 D_8011D0E4_w03[D_8011EBA8_w03].y);
    func_80054904_main(
        setupGroup, 0, (f32)xPos + D_8011D358_w03[playerIndex].x,
        (f32)yPos + D_8011D358_w03[playerIndex].y);
    func_80055420_main(group, 0, 0xFF, 0xFF, 0xFF);
    func_80055458_main(group, 0, 0xFF);

    scale = 0.0f;
    alpha = 0xFF;
    while (alpha >= 0) {
        HuSprScaleSet(group, 0, scale, scale);
        func_80055458_main(group, 0, alpha);
        HuPrcVSleep();
        alpha -= 10;
        scale += 0.1f;
    }

    func_80055458_main(group, 0, 0);
    HuSprGrpKill(group);
    omDelPrcObj(NULL);
}

void func_801128B0_w03(void) {
    s32 playerIndex;
    void *data;
    s32 itemSpriteId;
    s32 auraSpriteId;
    s32 group;
    s16 setupGroup;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    s32 i;
    s32 j;
    Process *childProcess;
    s32 fxId;

    playerIndex = (s32)HuPrcCurrentGet()->user_data;
    data = DataRead(0x21002C);
    itemSpriteId = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1301BA);
    auraSpriteId = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1301B9);
    D_8011EBAC_w03 = func_80055810_main(data);
    DataClose(data);

    group = HuSprGrpCreate(2, 2);
    setupGroup = group;
    func_800550F4_main(setupGroup, 0, 1);
    func_80055024_main(setupGroup, 0, itemSpriteId, 0xC);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, 0x1000);
    func_800554C4_main(setupGroup, 0, -1);
    func_80055024_main(setupGroup, 1, auraSpriteId, 0);
    HuSprPriSet(setupGroup, 1, 9);
    HuSprAttrSet(setupGroup, 1, 0x9000);
    func_80055420_main(setupGroup, 1, 0xFF, 0xFF, 0xFF);
    func_80055458_main(setupGroup, 1, 0xFF);
    HuSprScaleSet(setupGroup, 1, 2.0f, 2.0f);
    func_800554C4_main(setupGroup, 1, 0);

    yPos = 0xC8;
    if (playerIndex & 1) {
        HuSprAttrSet(setupGroup, 0, 1);
        HuSprAttrSet(setupGroup, 1, 1);
        func_80054904_main(setupGroup, 1, 0x14, -5);
    } else {
        yPos = 0x78;
        func_80054904_main(group, 1, -0x14, -5);
    }

    xPos = (playerIndex < 2) ? -0x20 : 0x110;
    HuPrcSleep(0x14);
    GwPlayer[playerIndex].itemNo[MBItemFind(playerIndex, 0xC)] = -1;
    MBItemRemoveEmpty(playerIndex);
    MBStatusItemIconSprReinit(playerIndex);

    do {
        if (playerIndex < 2) {
            xPos += 5;
            if (xPos >= 0x33) {
                break;
            }
        } else {
            xPos -= 5;
            if (xPos < 0xD2) {
                break;
            }
        }
        func_80054904_main(group, 0, yPos, xPos);
        HuPrcVSleep();
    } while (1);

    HuPrcSleep(0xA);
    HuSprAttrReset(group, 1, 0x8000);
    fxId = HuAudFXPlay(0x14C);
    D_8011EBA8_w03 = playerIndex;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            childProcess = omAddPrcObj(func_80112694_w03, 0x4002, 0, 0);
            childProcess->user_data = (void *)i;
            HuPrcSleep(2);
        }
        HuPrcSleep(5);
    }

    HuPrcChildLink(HuPrcCurrentGet(), childProcess);
    HuPrcChildWait();
    HuAudFXStop(fxId);
    func_80055458_main(group, 1, 0);

    for (i = 0xFF; i >= 0; i -= 0x1E) {
        func_80055458_main(group, 0, i);
        HuPrcVSleep();
    }

    func_80055458_main(group, 0, 0);
    HuSprGrpKill(group);
    HuSprKill(D_8011EBAC_w03);
    HuSprKill(auraSpriteId);
    HuSprKill(itemSpriteId);
    omDelPrcObj(NULL);
}

void func_80112CA4_w03(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void func_80112D60_w03(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011EBB0_w03);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += 1.5;
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void func_80112EB4_w03(Object *arg) {
    Process *temp = omAddPrcObj(func_80112D60_w03, 0x1000, 0, 0);

    temp->user_data = arg;
}

void func_80112EF0_w03(void) {
    s32 *flag = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *loc = &GwSystem;

    while (1) {
        D_8011EBB4_w03->rot.x = -sindf(angle);
        D_8011EBB4_w03->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (*flag != 0) {
            D_8011EBB4_w03->scale.z = scale;
            D_8011EBB4_w03->scale.y = scale;
            D_8011EBB4_w03->scale.x = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }
    D_8011EBB4_w03->scale.x = D_8011EBB4_w03->scale.y = D_8011EBB4_w03->scale.z = 0.0f;
    GwPlayer[loc->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemIconSprReinit(loc->current_player_index);
    MBModelKill(D_8011EBB4_w03);
    omDelPrcObj(0);
}

void func_80113080_w03(void) {
    s32 flag = 0;
    GW_SYSTEM *system = &GwSystem;
    void *data;
    UnkVibrateProcess *process;
    s32 positionX;
    s32 positionY;
    s32 bankCoins;
    s32 coinCount;
    s32 spriteId;
    f32 coinStep;
    f32 coinProgress;

    mbItemCursorGrpId = HuSprGrpCreate(1, 5);
    data = DataRead(D_80101040_shared_board[GwPlayer[system->current_player_index].chr]);
    spriteId = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(mbItemCursorGrpId, 0, spriteId, 0);
    HuSprPriSet(mbItemCursorGrpId, 0, 10);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
    MBStatusItemPosGet(-1, 0, &positionX, &positionY);
    func_80054904_main(mbItemCursorGrpId, 0, positionX, positionY);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);
    MBItemSelNoSet(MBItemFind(-1, 0xF));
    func_8010FF2C_w03();

    D_8011EBB4_w03 = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&D_8011EBB4_w03->coords, &MBPlayerGet(-1)->player_obj->coords);
    D_8011EBB4_w03->velocity.x = 100.0f;
    while (30.0f < D_8011EBB4_w03->velocity.x) {
        D_8011EBB4_w03->velocity.x -= 1.0f;
        HuPrcVSleep();
    }
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(func_80112EF0_w03, 0x4002, 0, 0)->user_data = &flag;
    process = MBPlayerVibrateObjCreate(-1, 4, 5);

    bankCoins = GwSystem.bank_coins;
    coinStep = (f32)bankCoins / 30.0f;
    coinProgress = 0.0f;
    D_8011EBB0_w03 = MBModelCreate(0x19, NULL);
    MBModelTempAllocFree(D_8011EBB0_w03);
    MBModelDispOff(D_8011EBB0_w03);
    if (bankCoins != 0) {
        while (bankCoins != 0) {
            coinProgress += coinStep;
            coinCount = 0;
            while (coinProgress >= 1.0f) {
                coinProgress -= 1.0f;
                coinCount++;
            }
            if (coinCount != 0) {
                func_80112EB4_w03(D_8011EBB4_w03);
                if (bankCoins - coinCount < 0) {
                    coinCount = bankCoins;
                }
                bankCoins -= coinCount;
                MBPlayerCoinAdd(system->current_player_index, coinCount);
                HuAudFXPlay(0x106);
                GwSystem.bank_coins -= coinCount;
                func_80108174_w03();
                HuPrcSleep(5);
            }
        }
    }

    MBPlayerVibrateObjKill(process);
    flag = 1;
    HuPrcSleep(20);
    MBModelKill(D_8011EBB0_w03);
    MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    func_8004ACE0_main(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 func_8011343C_w03(u8 *arg0, s32 arg1) {
    s32 delay = 0;
    s16 inputs[MB_MAX_PLAYERS];
    u8 buttons[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(p3Unk4Bytes *)buttons = *(p3Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                delay = 1; // Required for matching register allocation.
                if (arg1 != 0) {
                    delay = D_8011EBB8_w03 + 1;
                } else {
                    delay = D_8011EBBC_w03 + 1;
                }
                inputs[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, buttons[GwPlayer[i].pad]);
                inputs[GwPlayer[i].pad] = -1;
            }
        } else {
            inputs[GwPlayer[i].pad] = 0;
        }
    }

    if (delay != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; delay != 0; j++) {
            if (--delay == 0) {
                inputs[GwPlayer[GwSystem.current_player_index].pad] = 0x8000;
            }
            if (j == 0) {
                func_8005F698_main(inputs[0], inputs[1], inputs[2], inputs[3],
                                    func_800EDC40_shared_board());
            } else {
                func_8005F698_main(inputs[0], inputs[1], inputs[2], inputs[3], 5);
            }
        }
    } else {
        func_8005F744_main(inputs[0], inputs[1], inputs[2], inputs[3]);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (arg0[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    do {
        i = func_8005E1D8_main(mbDlgWinId, i, 1);
    } while (arg0[i] == 0);
    return i;
}

void func_801136D4_w03(void) {
    Process *prc = HuPrcCurrentGet();
    s32 playerIdx = (s32)prc->user_data;
    s32 j;
    s32 val;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    MBPlayerVibrate(((s16 *)&prc->user_data)[1], 4);

    for (val = 0x80; val > 0; val -= 0xA) {
        for (j = 0; j < 3; j++) {
            if (GwPlayer[playerIdx].itemNo[j] != -1) {
                MBStatusItemTPLvlSet(playerIdx, j, val);
            }
        }
        HuPrcVSleep();
    }

    for (j = 0; j < 3; j++) {
        if (GwPlayer[playerIdx].itemNo[j] != -1) {
            MBStatusItemTPLvlSet(playerIdx, j, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_801137E0_w03(void) {
    Process *process = HuPrcCurrentGet();
    s32 playerIndex = (s32)process->user_data;
    GW_SYSTEM *system = &GwSystem;
    s32 i;
    s32 alpha;
    s32 itemIndex;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;

    for (i = 0, itemIndex = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
            MBStatusItemScaleSet(system->current_player_index, i, 1.0f, 1.0f);
            MBStatusItemPosGet(playerIndex, itemIndex, &xPos, &yPos);
            MBStatusItemPosSet(system->current_player_index, i, xPos, yPos);
            itemIndex += (i != MBItemSelNoGet());
        }
    }

    for (alpha = 0; alpha < 0x80; alpha += 0x14) {
        for (i = 0; i < 3; i++) {
            if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
                if (i != MBItemSelNoGet()) {
                    MBStatusItemTPLvlSet(system->current_player_index, i, alpha);
                }
            }
        }
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
            if (i != MBItemSelNoGet()) {
                MBStatusItemTPLvlSet(system->current_player_index, i, 0x80);
            }
        }
    }
    omDelPrcObj(NULL);
}

void func_801139BC_w03(void) {
    char playerNames[4][16];
    u8 choices[16];
    Vec2f position;
    Vec2f target;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    u16 spriteId;
    Object *box;
    Process *process;
    GW_SYSTEM *system = &GwSystem;
    s32 targetPlayer;
    s32 noAnimation = 0;
    s32 itemCount;
    s32 itemSlot;
    s32 sleepTime;
    s32 i;
    s32 j;
    s32 item;
    f32 angle;
    f32 angleStep;
    f32 spinStep;
    f32 scale;
    f32 scaleY;
    f32 itemAngle;
    f32 scaleZ;
    f32 finalScale;

    func_8010FF2C_w03();
    box = MBModelCreate(0x20, NULL);
    func_8001C2FC_main(box->omObj1->model[0], 0x20000, 0x20000);
    func_8001C448_main(box->omObj1->model[0]);
    func_8001C954_main(box->omObj1->model[0]);
    func_8001C514_main(box->omObj1->model[0]);
    Hu3DModelScaleSet(box->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&box->coords, &MBPlayerGet(-1)->player_obj->coords);
    func_8001C814_main(box->omObj1->model[0], 2, 1);
    box->velocity.x = 100.0f;
    HuAudFXPlay(0x142);
    while (box->velocity.x > 30.0f) {
        box->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    for (itemSlot = 0; itemSlot < 4; itemSlot++) {
        if (GwSystem.current_player_index == itemSlot) {
            playerNames[itemSlot][0] = 1;
            choices[itemSlot] = 0;
        } else {
            playerNames[itemSlot][0] = 8;
            choices[itemSlot] = 1;
        }
        func_800E2260_shared_board(itemSlot, &playerNames[itemSlot][1]);
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(-1, 0x5C01, (s32)playerNames[0], (s32)playerNames[1], (s32)playerNames[2],
                         (s32)playerNames[3], 0);
    targetPlayer = func_8011343C_w03(choices, 1);
    MBDlgWinClose();
    MBDlgWinKill();
    if (targetPlayer == 4) {
        targetPlayer = func_800EF0D8_shared_board(1);
    }

    itemSlot = MBItemSelNoGet();
    if (GwPlayer[GwSystem.current_player_index].itemNo[itemSlot] == 0x10 &&
        MBItemFindEmpty(GwSystem.current_player_index) == 1 && MBItemFindEmpty(targetPlayer) == 0) {
        noAnimation = 1;
    }

    if (!noAnimation) {
        HuAudFXPlay(0x149);
        func_8001C814_main(box->omObj1->model[0], 1, 0);
        HuPrcSleep(20);
        position.x = 160.0f;
        position.y = 84.0f;
        for (itemSlot = 0; itemSlot < 3; itemSlot++) {
            for (j = 0; j < 3; j++) {
                spriteId = 0x4790;
                if (j == itemSlot) {
                    spriteId = 0x4786;
                }
                MBStatusItemPriSet(system->current_player_index, j, spriteId);
            }
            if (GwPlayer[system->current_player_index].itemNo[itemSlot] != -1) {
                if (itemSlot != MBItemSelNoGet()) {
                    func_8011077C_w03(system->current_player_index, itemSlot, 10, &position.x, 0);
                    HuPrcSleep(2);
                }
            }
        }
        func_8001C814_main(box->omObj1->model[0], 4, 4);
        while (HmfModelData[box->omObj1->model[0]].unk40 != 0.0f) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x150);
        HuPrcSleep(20);
        process = omAddPrcObj(func_801136D4_w03, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        HuAudFXPlay(0x151);

        angle = 0.0f;
        spinStep = 5.0f;
        i = 0;
        while (1) {
            box->rot.x = -sindf(angle);
            box->rot.z = cosdf(angle);
            angle += spinStep;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            spinStep += 2.0f;
            if (spinStep > 45.0f) {
                spinStep = 45.0f;
                if (i++ >= 31) {
                    break;
                }
            }
            HuPrcVSleep();
        }

        i = 0;
        while (1) {
            box->rot.x = -sindf(angle);
            box->rot.z = cosdf(angle);
            angle += spinStep;
            if (angle > 360.0f) {
                angle -= 360.0f;
                if (++i >= 2) {
                    break;
                }
            }
            spinStep -= 2.0f;
            if (spinStep < 5.0f) {
                spinStep = 5.0f;
            }
            HuPrcVSleep();
        }
        box->rot.x = 0.0f;
        box->rot.z = 1.0f;
        HuAudFXPlay(0x152);
        for (itemSlot = 0; itemSlot < 1441; itemSlot += 40) {
            scale = itemSlot;
            angleStep = sindf(scale) / 1.5f + 1.0f;
            scaleY = sindf(scale) / 1.5f + 1.0f;
            scaleZ = sindf(scale) / 1.5f + 1.0f;
            HuVecCopyXYZ(&box->scale, angleStep, scaleY, scaleZ);
            HuPrcVSleep();
        }

        HuAudFXPlay(0x149);
        func_8001C814_main(box->omObj1->model[0], 4, 0);
        HuPrcSleep(20);
        process = omAddPrcObj(func_801137E0_w03, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8011077C_w03(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8011077C_w03(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8011077C_w03(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_8011077C_w03(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8011077C_w03(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_8011077C_w03(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8011077C_w03(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_8011077C_w03(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                func_8011077C_w03(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8011077C_w03(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_8011077C_w03(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                func_8011077C_w03(targetPlayer, 2, 7, &target.x, 2);
                break;
        }
        HuPrcSleep(2);
    }

    itemSlot = MBItemSelNoGet();
    GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    for (itemSlot = 0; itemSlot < 3; itemSlot++) {
        item = GwPlayer[targetPlayer].itemNo[itemSlot];
        GwPlayer[targetPlayer].itemNo[itemSlot] = GwPlayer[system->current_player_index].itemNo[itemSlot];
        GwPlayer[system->current_player_index].itemNo[itemSlot] = item;
    }
    if (!noAnimation) {
        MBStatusItemSprKill(-1);
        MBStatusItemSprKill(targetPlayer);
        sleepTime = 10;
    } else {
        sleepTime = 20;
    }
    HuPrcSleep(sleepTime);
    HuAudFXPlay(0x15B);
    finalScale = 0.1f;
    for (i = 0; i < 20; i++) {
        finalScale += 0.044999998f;
        func_8001D558_main(box->omObj1->model[0], finalScale, finalScale * 10.0f, 1);
        HuPrcVSleep();
    }
    MBModelKill(box);

    if (noAnimation) {
        func_8004ACE0_main(0x286, system->current_player_index);
        MBPlayerMotionSet(-1, 3, 0);
        HuPrcSleep(70);
    } else {
        func_8004ACE0_main(0x274, system->current_player_index);
        MBPlayerMotionSet(-1, 5, 0);
        HuPrcSleep(50);
    }
    func_800F2388_shared_board(-1, -1, 0, 10, 2);
    MBDlgWinInsertCreate(-1, noAnimation ? 0x3A2E : 0x3A2D,
                         mbCharNameMesTbl[GwPlayer[system->current_player_index].chr],
                         mbCharNameMesTbl[GwPlayer[targetPlayer].chr], 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
}

void func_80114668_w03(void) {
    p3ModelAnimWork *data = HuPrcCurrentGet()->user_data;
    Object *obj1 = data->obj1;
    Object *obj2 = data->obj2;

    MBMotionSet(obj1, -1, data->state);
    HuVecCopy3F(&obj1->coords, &obj2->coords);
    obj1->coords.y += obj2->velocity.x - 10.0f;
    func_800D9A40_shared_board(obj1);
    while (MBMotionCheck(obj1) == 0 && data->flag == 0) {
        HuPrcVSleep();
    }
    MBModelKill(obj1);
    omDelPrcObj(0);
}

void func_80114728_w03(void) {
    s32 *processFlag = HuPrcCurrentGet()->user_data;
    Object *gameGuyModel = D_8011EBC0_w03;
    Object *model;
    Process *process;
    p3ModelAnimWork *work;
    s32 effect;
    f32 angle;
    f32 angleStep;
    f32 fallSpeed;
    f32 scale;
    s32 i;

    model = MBModelCreate(0x45, NULL);
    MBModelDispOff(model);
    effect = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(effect, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 10.0f);
    func_8001C8A8_main(effect, 1);
    HuAudFXPlay(0x24C);

    angle = 0.0f;
    angleStep = 2.0f;
    while (angleStep < 80.0f) {
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        angleStep += 1.0f;
        if (angleStep > 80.0f) {
            angleStep = 80.0f;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    HuAudFXPlay(0x14A);
    while (gameGuyModel->velocity.x < 110.0f) {
        gameGuyModel->velocity.x += 7.0f;
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    *processFlag = 0;
    while (*processFlag == 0) {
        if (D_8011D388_w03 != -1) {
            HuVecCopy3F(&gameGuyModel->coords,
                        &MBPlayerGet(D_8011D388_w03)->player_obj->coords);
            func_8000CFA4_main(effect, gameGuyModel->coords.x,
                               gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        }
        HuPrcVSleep();
    }

    HuAudFXPlay(0x14B);
    fallSpeed = 3.0f;
    while (gameGuyModel->velocity.x > 30.0f) {
        gameGuyModel->velocity.x -= fallSpeed;
        if (fallSpeed > 1.0f) {
            fallSpeed -= 0.2f;
        }
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    while (1) {
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (angleStep > 15.0f) {
            angleStep -= 3.0f;
        } else {
            angleStep -= 0.5f;
        }
        if (angleStep < 1.0f) {
            break;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    func_8000D044_main(effect);
    process = omAddPrcObj(func_80114668_w03, 0x4800, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, 0x20);
    process->user_data = work;
    work->obj1 = model;
    work->obj2 = gameGuyModel;
    work->state = 0;
    work->flag = 0;
    HuPrcSleep(3);
    *processFlag = 0;
    HuAudFXPlay(0x24D);

    i = 0;
    scale = 0.1f;
    for (; i < 20; i++) {
        scale += 0.044999998f;
        func_8001D558_main(gameGuyModel->omObj1->model[0], scale, scale * 10.0f, 1);
        HuPrcVSleep();
    }
    MBModelKill(gameGuyModel);
    omDelPrcObj(NULL);
}

void func_80114C58_w03(void) {
    Object *coinModel;
    Object *gameGuyModel;
    Object *playerObj;
    Process *process;
    GW_SYSTEM *system;
    s32 choice;
    s32 itemSlot;
    s32 rewardIndex;
    s32 randomValue;
    s32 rewardAmount;
    s32 i;
    struct {
        s32 processFlag;
        s32 pad;
        char rewardText[0x10];
    } locals;

    system = &GwSystem;
    func_8010FF2C_w03();
    itemSlot = MBItemFind(-1, 0x11);
    GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    coinModel = MBModelCreate(0x3E, 0);
    Hu3DModelScaleSet(coinModel->omObj1->model[0], 0, 0, 0);
    MBModelTempAllocFree(coinModel);
    coinModel->velocity.x = 30.0f;
    MBModelDispOff(coinModel);

    gameGuyModel = MBModelCreate(0x43, 0);
    D_8011EBC0_w03 = gameGuyModel;
    func_8001C2FC_main(gameGuyModel->omObj1->model[0], 0x20000, 0x20000);
    func_8001C448_main(gameGuyModel->omObj1->model[0]);
    func_8001C954_main(gameGuyModel->omObj1->model[0]);
    func_8001C514_main(gameGuyModel->omObj1->model[0]);
    HuVecCopy3F(&gameGuyModel->coords, &MBPlayerGet(-1)->player_obj->coords);
    func_8001C814_main(gameGuyModel->omObj1->model[0], 2, 1);
    gameGuyModel->velocity.x = 100.0f;
    HuAudFXPlay(0x14B);
    while (gameGuyModel->velocity.x > 30.0f) {
        gameGuyModel->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

selectPlayer:
    MBDlgWinInsertCreate(-1, 0x5C00, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = func_80109F44_w03(0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    if (choice >= 0) {
        if (choice < 4) {
            goto validChoice;
        }
        if (choice == 4) {
            choice = func_800EF0D8_shared_board(0);
            goto validChoice;
        }
    }
    func_80106D28_w03();
    D_800CB99C_main = 1;
    func_80049FB8_main();
    goto selectPlayer;

validChoice:
    locals.processFlag = 1;
    process = omAddPrcObj(func_80114728_w03, 0x4002, 0, 0);
    process->user_data = &locals.processFlag;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    if (choice != system->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        D_8011D388_w03 = choice;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(choice)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(choice)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(10);
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(30);
        D_8011D388_w03 = choice;
    }

    locals.processFlag = 1;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    playerObj = MBPlayerGet(choice)->player_obj;
    process = func_800EDB98_shared_board(coinModel, 5.0f, 2.0f);
    HuVecCopy3F(&coinModel->coords, &playerObj->coords);
    func_800D9A40_shared_board(coinModel);
    coinModel->scale.x = coinModel->scale.y = coinModel->scale.z = 0.0f;
    while (coinModel->scale.x < 1.0f) {
        coinModel->scale.x = coinModel->scale.y = coinModel->scale.z += 0.2f;
        HuPrcVSleep();
    }

    MBPlayerVibrate(choice, 4);
    HuAudFXPlay(0x2A1);
    if (GwPlayer[choice].coin != 0) {
        func_8010A1C8_w03(10, 0x2F00, -1, choice);
        GwPlayer[choice].gameCoin = GwPlayer[choice].coin;
        MBCoinChangeCreate(choice, -GwPlayer[choice].coin);
        MBCoinTakeCreate(choice, -GwPlayer[choice].coin);
        HuPrcSleep(30);
        func_8010A1C8_w03(10, 0x2F02, -1, choice);
        omDelPrcObj(process);
        while (coinModel->velocity.x >= 10.0f) {
            coinModel->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        HuPrcSleep(30);
        while (coinModel->velocity.x < 100.0f) {
            coinModel->velocity.x += 4.0f;
            playerObj->velocity.x += 4.0f;
            HuPrcVSleep();
        }
    } else {
        func_8010A1C8_w03(10, 0x2F01, -1, choice);
        omDelPrcObj(process);
        while (coinModel->velocity.x <= 100.0f) {
            coinModel->velocity.x += 4.0f;
            HuPrcVSleep();
        }
        MBModelKill(coinModel);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        return;
    }

    if (MBPlayerComCheck((s16)choice) != 0 && system->show_com_minigames != 0) {
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBModelKill(coinModel);
        func_800EE688_shared_board(playerObj, 0, 0);
        playerObj->velocity.x = 0.0f;
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        randomValue = MBRand(100.0f) + 1;
        for (rewardIndex = 0; rewardIndex < 7; rewardIndex++) {
            if (randomValue <= D_8011D394_w03[rewardIndex].threshold) {
                break;
            }
        }
        if (D_8011D394_w03[rewardIndex].multiplier != 0) {
            rewardAmount = GwPlayer[choice].gameCoin * D_8011D394_w03[rewardIndex].multiplier;
            if (rewardAmount >= 1000) {
                rewardAmount = 999;
            }
            sprintf(locals.rewardText, D_8011E98C_w03, rewardAmount);
            MBDlgWinInsertCreate(-1, 0x2F03, (s32)locals.rewardText, 0, 0, 0, 0);
            MBDlgWinClose();
            MBDlgWinKill();
            MBCoinChangeCreate(choice, rewardAmount);
            MBCoinTakeCreate(choice, rewardAmount);
            HuPrcSleep(20);
        } else {
            MBDlgWinExec(-1, 0x2F04);
        }
        HuPrcSleep(10);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        return;
    }

    if (func_800DEB2C_shared_board(system->current_player_index) == 3) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].group = 1;
    }
    MBPlayerGet(choice)->group = 0;
    randomValue = MBRand(100.0f);
    for (rewardIndex = 0; (u32)rewardIndex < 3; rewardIndex++) {
        if (randomValue < D_8011D390_w03[rewardIndex]) {
            break;
        }
    }
    if (rewardIndex == 3) {
        rewardIndex = 2;
    }
    system->minigame_index = D_8011D38C_w03[rewardIndex];
    GwSystem.playerIndexVisitingBowser = choice;
    func_800FC998_shared_board();
    func_8004A0E0_main();
    func_800FF7F0_shared_board(2);
    HuPrcSleep(-1);
}

void func_80115564_w03(s32 arg0, s32 arg1, f32 *arg2) {
    f32 curX;
    f32 curY;
    f32 stepX;
    f32 stepY;

    MBStatusSprPosGet((s16)arg0, 0, &curX, &curY);
    stepX = (arg2[0] - curX) / arg1;
    stepY = (arg2[1] - curY) / arg1;
    while (arg1 != 0) {
        curX += stepX;
        curY += stepY;
        func_80054904_main(arg0, 0, curX, curY);
        HuPrcVSleep();
        arg1--;
    }
    func_80054904_main(arg0, 0, arg2[0], arg2[1]);
}

void func_8011569C_w03(void) {
    s32 idx;
    s32 divisor;
    s32 i;

    idx = (s32)HuPrcCurrentGet()->user_data;
    divisor = 10;

    switch (idx) {
        case 0:
            func_80054904_main(D_8011EBC8_w03[idx], 0, 0xB1, 0x2C);
            break;
        case 1:
            func_80054904_main(D_8011EBC8_w03[idx], 0, 0x7A, 0x39);
            break;
        default:
            func_80054904_main(D_8011EBC8_w03[idx], 0, 0xA0, 0x98);
            divisor = 30;
            break;
    }

    HuSprAttrReset(D_8011EBC8_w03[idx], 0, 0x8000U);
    for (i = 0; i < 255; i += 255 / divisor) {
        func_80055458_main(D_8011EBC8_w03[idx], 0, i & 0xFFFF);
        HuPrcVSleep();
    }

    func_80055458_main(D_8011EBC8_w03[idx], 0, 0xFF);
    omDelPrcObj(0);
}

void func_8011580C_w03(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i;
    s32 j;

    for (i = 0; i <= 0; i++) {
        sp18.r = D_8011D3B0_w03[i].r;
        sp18.g = D_8011D3B0_w03[i].g;
        sp18.b = D_8011D3B0_w03[i].b;

        sp28.r = (D_8011D3B0_w03[i + 1].r - sp18.r) / 30;
        sp28.g = (D_8011D3B0_w03[i + 1].g - sp18.g) / 30;
        sp28.b = (D_8011D3B0_w03[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            func_80055420_main(D_8011EBC8_w03[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        func_80055420_main(D_8011EBC8_w03[3], 0, D_8011D3B0_w03[i + 1].r, D_8011D3B0_w03[i + 1].g, D_8011D3B0_w03[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

void func_801159D4_w03(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    Object *model;
    f32 scale;
    f32 angle;
    f32 wait_angle_step;

    HuAudFXPlay(0x143);
    model = D_8011EBD8_w03;
    func_800D9A40_shared_board(model);

    angle = 0.0f;
    for (scale = 1.0f; scale < 18.0f; scale = (f32)((f64)scale + 0.8)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (*state != 1) {
        wait_angle_step = 20.0f;
        while (*state != 1) {
            func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
            angle += wait_angle_step;
            HuPrcVSleep();
        }
    }

    for (; scale < 40.0f; scale = (f32)((f64)scale + 0.8)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (*state != 2) {
        scale = 20.0f;
        while (*state != 2) {
            func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
            angle += scale;
            HuPrcVSleep();
        }
    }

    MBModelKill(model);
    omDelPrcObj(0);
}

void func_80115C58_w03(void) {
    s32 sp18[4];
    f32 sp28[2];
    s32 sp30;
    s32 sp34;
    f32 sp38;
    f32 sp3C;
    s32 sp40;
    Process *temp_v0_4;
    f32 temp_f20;
    f32 var_f20;
    s32 temp_s0_3;
    s32 temp_s4;
    s32 temp_s7;
    void *temp_s1_2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    void *temp_v0;
    Object *temp_v0_3;
    s32 i;
    s32 j;
    GW_SYSTEM *system = &GwSystem;
    s32 temp;

    temp_s4 = HuSprGrpCreate(1, 0);
    temp_v0 = DataRead(D_8010197C_shared_board[18]);
    temp_s7 = func_80055810_main(temp_v0);
    DataClose(temp_v0);
    func_80055024_main(temp_s4, 0, temp_s7, 0);
    HuSprPriSet(temp_s4, 0, 0x4776U);
    HuSprAttrSet(temp_s4, 0, 0x1000U);
    for (i = 0; i < 4; i++) {
        D_8011EBC8_w03[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = func_80055810_main(temp_v0);
        DataClose(temp_v0);
        func_80055024_main(D_8011EBC8_w03[i], 0, sp18[i], 0);
        HuSprPriSet(D_8011EBC8_w03[i], 0, 0x4780U);
        HuSprAttrSet(D_8011EBC8_w03[i], 0, 0x980CU);
        func_80055458_main(D_8011EBC8_w03[i], 0, 0U);
        func_80055420_main(D_8011EBC8_w03[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    D_8011EBD8_w03 = temp_v0_3;
    func_8001C258_main(temp_v0_3->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(temp_v0_3->omObj1->model[0], 0x1800);
    func_8001C448_main(temp_v0_3->omObj1->model[0]);
    Hu3DModelScaleSet(temp_v0_3->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&temp_v0_3->coords, &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    MBModelTempAllocFree(temp_v0_3);
    MBModelDispOff(temp_v0_3);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000U);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    MBStatusItemPosGet(system->current_player_index, MBItemSelNoGet(), &sp30, &sp34);
    func_80054904_main(temp_s4, 0, sp30, sp34);
    sp28[0] = 160.0f;
    sp28[1] = 76.0f;
    HuAudFXPlay(0x145);
    func_80115564_w03(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    func_80115564_w03(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(func_8011569C_w03, 0x4002U, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    func_80115564_w03(temp_s4, 0xA, sp28);
    HuPrcChildWait();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(func_8011569C_w03, 0x4002U, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    func_80115564_w03(temp_s4, 0xA, sp28);
    HuPrcChildWait();
    HuPrcSleep(0xA);
    HuAudFXPlay(0x14E);
    MBStatusSprPosGet(temp_s4, 0, &sp38, &sp3C);
    for (var_f20 = 0.0f, var_s1 = 0; var_f20 < 90.0f; var_f20 += 3.6f) {
        func_80054904_main(temp_s4, 0, ((cosdf((2.0f * var_f20) + 270.0f) * 80.0f) + sp38), (((1.0f - cosdf(var_f20)) * 90.0f) + sp3C));
        if (!(var_f20 > 54.0f)) {
            var_v1 = 0;
        } else {
            var_v1 = 1;
        }
        temp = var_v1 != 0;
        if (temp && var_s1 == 0) {
            var_s1 = 1;
            temp_v0_4 = omAddPrcObj(func_8011569C_w03, 0x4002U, 0, 0);
            temp_v0_4->user_data = (void *)2;
            HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
        }
        HuPrcVSleep();
    }

    temp_s0_3 = (s16)(s32)((cosdf(450.0f) * 80.0f) + sp38);
    func_80054904_main(temp_s4, 0, temp_s0_3, (((1.0f - cosdf(90.0f)) * 90.0f) + sp3C));

    for (j = 255; j > 0; j -= 0x19, HuPrcVSleep()) {
        func_80055458_main(temp_s4, 0, j);
    }

    HuSprGrpKill(temp_s4);
    HuSprKill(temp_s7);
    HuPrcChildWait();

    for (i = 0; i < 3; i++) {
        HuSprAttrSet(D_8011EBC8_w03[i], 0, 0x8000);
    }

    HuSprAttrReset(D_8011EBC8_w03[3], 0, 0x8000U);
    func_80055458_main(D_8011EBC8_w03[3], 0, 0xFFU);
    func_80054904_main(D_8011EBC8_w03[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_8011580C_w03, 0x4002U, 0, 0));
    sp40 = 0;
    omAddPrcObj(func_801159D4_w03, 0x4002U, 0, 0)->user_data = &sp40;
    HuPrcChildWait();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(D_8011EBC8_w03[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
        if (i >= (2880 / 2 + 1)) {
            sp40 = 1;
        }
        HuPrcVSleep();
    }

    HuAudFXPlay(0x129);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateOut(0xB, 0x32);
    MBPlayerVibrateObjKill(temp_s1_2);

    for (var_f20 = 0.0f; WipeStatGet() != 0; var_f20 += 0.1f) {
        HuSprScaleSet(D_8011EBC8_w03[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(D_8011EBC8_w03[i]);
        HuSprKill(sp18[i]);
    }

    WipeCreateIn(0xB, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = 2;
}

void func_8011655C_w03(p3SpaceTriple *masu, p3BranchPair *links, DecisionTreeNonLeafNode **trees) {
    GW_PLAYER *player;
    UnkEA790Struct *win;
    p3BranchLink *link;
    s32 back;
    s32 sel;
    s32 count;
    s32 row;
    s32 col;
    s32 i;
    s16 *temp;
    DecisionTreeNonLeafNode **tree;

    link = links[0];
    tree = trees;
    MBPlayerMotionSet(-1, -1, 2);
    HuPrcVSleep();
    func_80106D84_w03();
    player = MBPlayerGet(GwSystem.current_player_index);
    back = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    for (row = 0; row < 3; row++) {
        for (col = 0; col < 2; col++) {
            if (masu[row][col] == back) {
                break;
            }
        }
        if (col == 2) {
            break;
        }
    }

    temp = masu[row];
    link += row * 2;
    win = func_800D76A0_shared_board(GwSystem.current_player_index, temp);
    func_800D742C_shared_board(win, GwSystem.current_player_index, 0);

    if (MBPlayerComCheck(-1)) {
        count = MBComTreeExec(tree[row]);
        for (i = 0; i < count; i++) {
            func_800D7250_shared_board(win, -2);
        }
        func_800D7250_shared_board(win, -4);
    }

    sel = func_800D7518_shared_board(win);
    func_800D6CA0_shared_board(win);
    func_80106E54_w03();

    if (sel) {
        link++;
    }

    MBMoveNextMasuSet(-1, link->link, link->idx);
    switch (link->rev) {
        case 0:
            player->rev &= ~1;
            break;
        case 1:
            player->rev |= 1;
            break;
    }
}

void func_80116754_w03(s32 arg0) {
    if (D_8011EBF0_w03[arg0] != NULL) {
        omDelObj(D_8011EBF0_w03[arg0]);
        D_8011EBF0_w03[arg0] = NULL;
    }
    if (D_8011EBE0_w03[arg0] != NULL) {
        MBModelKill(D_8011EBE0_w03[arg0]);
        D_8011EBE0_w03[arg0] = NULL;
    }
}

void func_801167CC_w03(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = D_8011EBF0_w03[i];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011EBF0_w03[i] = NULL;
        }
    }
}

void func_80116830_w03(omObjData *obj) {
    s32 playerIdx = obj->work[0];

    if (GwSystem.current_player_index == 4) {
        if (obj->work[2] == 0) {
            if (obj->work[1] != 0) {
                obj->work[1] -= 1;
                if (obj->work[1] != 0) {
                    return;
                }
                obj->work[2] = 1;
            } else {
                obj->work[1] = 40;
                return;
            }
        }
    }

    {
        GW_PLAYER *player = MBPlayerGet(playerIdx);
        Object *effectObj = D_8011EBE0_w03[playerIdx];

        HuVecCopy3F(&effectObj->coords, &player->player_obj->coords);
        effectObj->velocity.x = player->player_obj->velocity.x + 20.0f;
        HuVecCopy3F(&effectObj->rot, &player->player_obj->rot);
        effectObj->coords.x += sindf(obj->rot.x) * obj->trans.x;
        effectObj->coords.z += cosdf(obj->rot.x) * obj->trans.x;
        obj->rot.x += 5.0f;
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
        if (obj->trans.x <= 5.0f) {
            obj->trans.x += 0.25f;
        }
        if (player->player_obj->flags & 8) {
            func_800D9A40_shared_board(effectObj);
        } else {
            MBModelDispOff(effectObj);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801169DC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116ADC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116B78_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116C78_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116E84_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116FE4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80117034_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801175AC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011777C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801178B4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80117D38_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801183E0_w03);

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

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B470_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B51C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B5E0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B634_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B71C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011BD24_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011C088_w03);
