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

#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/FFB10.h"
// board g2: func_80109C98_w02..func_8010D854_w02 (twins of w06 func_8010B4C4_w06..func_8010F07C_w06)
typedef struct {
    u8 unk[4];
} g2Unk4Bytes;

s16 func_801059D0_w02(void);
s32 func_80105C30_w02(s16 arg0);
void func_80106A3C_w02(Object *arg);
void func_80106AB0_w02(void);
void func_80106B38_w02(void);
s32 func_80106CC4_w02(u8 *arg0);
s32 func_80106F58_w02(void);
void func_80107FB0_w02(void);
void func_80112340_w02(void);
void func_80112B10_w02(void);
void func_80109C80_w02(void);
void func_80109C88_w02(void);
void func_80109C90_w02(void);

extern DecisionTreeNonLeafNode D_8011D414_w02[];
extern u32 D_8011D42C_w02[];
extern u8 D_8011D444_w02[2][3][4];
extern s8 D_8011D45C_w02[][5][7];
extern u8 D_8011D4A4_w02[2][3][4];
extern s8 D_8011D4BC_w02[2][5][10];
extern u8 D_8011D520_w02[2][10];
extern s32 D_8011D534_w02[5][2];
extern s32 D_8011D55C_w02[2];
extern s32 D_8011D564_w02[2];
extern s32 D_8011D56C_w02[2];
extern s32 D_8011D574_w02[2];
extern s32 D_8011D57C_w02[2];
extern u32 D_8011D584_w02[];
extern u32 D_8011D58C_w02[];
extern s32 D_8011D594_w02;
extern Vec2f D_8011D5A8_w02[4];
extern Vec2f D_8011D5C8_w02[4];
extern u8 D_8011D5E8_w02[6][3];
extern u8 D_8011D5FC_w02[14][3];
extern const u8 D_8011EA70_w02[];
extern const char D_8011EA74_w02[];
extern const f64 D_8011EA78_w02;
extern Object *D_8011EBD0_w02;
extern s32 D_8011EC90_w02;
extern s32 D_8011EC94_w02;
extern u8 *D_8011EC98_w02;
extern Object *D_8011EC9C_w02;

s32 func_80109C98_w02(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g2Unk4Bytes *)sp20 = *(g2Unk4Bytes *)D_8011EA70_w02;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                switch (arg0) {
                    case 0:
                        var_s2 = func_800EF0D8_shared_board(0) + 1;
                        break;
                    case 1:
                        var_s2 = func_800EF0D8_shared_board(1) + 1;
                        break;
                    case 2:
                        var_s2 = arg1 + 1;
                        break;
                    default:
                        var_s2 = MBComTreeExec((void *)arg0) + 1;
                        break;
                }
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return func_8005E1D8_main(mbDlgWinId, 0, 1);
}

void func_80109F1C_w02(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
    s16 sp10[2];
    s16 winId;

    func_80060394_main(1, sp10, arg1);
    winId = MBWinCreate(arg0, sp10, arg2);
    mbDlgWinId = winId;
    func_8005B43C_main(winId, arg1, -1, -1);
    func_80061388_main(winId);
    func_800EBF98_shared_board(winId, arg3);
    func_80061A5C_main(winId, 0);
    func_8005F364_main(winId);
}

void func_80109FD8_w02(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

void func_8010A018_w02(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = func_80105C30_w02(spaceIdx);
    if (spaceIdx == 1) {
        func_800DBEC0_shared_board(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, func_801059D0_w02());
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWait();
        HuAudFXPlay(0x159);

        if (GwPlayer[loc->current_player_index].itemTurn != 0) {
            MBDlgWinInsertCreate(0x16, 0x4805, GwPlayer[loc->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
            func_800EC9DC_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
        }

        if (GwPlayer[loc->current_player_index].star >= 99) {
            MBDlgWinExec(0x16, 0x4804);
        } else {
            if (GwPlayer[loc->current_player_index].coin >= 20) {
            purchaseMenu:
                MBDlgWinInsertCreate(0x16, 0x4800, GwPlayer[loc->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
                choice = func_80109C98_w02(2, 0);
                MBDlgWinClose();
                MBDlgWinKill();

                switch (choice) {
                    case 0:
                        MBCoinChangeCreate(loc->current_player_index, -20);
                        MBCoinTakeCreate(loc->current_player_index, -20);
                        HuPrcSleep(30);
                        MBDlgWinExec(0x16, 0x4802);
                        if (D_800A12D0_main != 0) {
                            func_8004A950_main();
                            func_800039A4_main(D_800C9930_main, 60);
                            D_800C9930_main = -1;
                        } else {
                            HuAudSeqFadeOut(0x5A);
                        }
                        func_80106A3C_w02(D_8011EBD0_w02);
                        HuPrcSleep(30);
                        func_800EDA58_shared_board();
                        func_800FF7F0_shared_board(2);
                        func_80109C88_w02();
                        return;
                    case 1:
                        if (D_800A12D0_main != 0) {
                            func_800039A4_main(D_800C9930_main, 60);
                            func_80003310_main(D_800CE198_main);
                            func_8004A670_main(0);
                            func_8004A72C_main(0x5A);
                            D_800C9930_main = -1;
                        }
                        MBDlgWinExec(0x16, 0x4803);
                        func_800DB884_shared_board(loc->current_player_index);
                        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
                        HuPrcChildWait();
                        func_80109C88_w02();
                        return;
                    case 2:
                        func_80106AB0_w02();
                        goto purchaseMenu;
                    default:
                        func_80109C88_w02();
                        return;
                }
            } else {
                MBDlgWinExec(0x16, 0x4801);
            }
        }

        if (D_800A12D0_main != 0) {
            func_800039A4_main(D_800C9930_main, 60);
            func_80003310_main(D_800CE198_main);
            func_8004A670_main(0);
            func_8004A72C_main(0x5A);
            D_800C9930_main = -1;
        }

        func_800DB884_shared_board(loc->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWait();
    }

    func_80109C88_w02();
}

void func_8010A3C4_w02(void) {
    Object *model;
    Object *effectModel;
    SpaceData *spaceA;
    SpaceData *spaceB;
    GW_SYSTEM *sys;
    Vec *vec;
    s16 mgId;
    s32 choice;
    s32 flag;
    f32 angle;
    f32 speed;
    f32 scaleK;
    f32 scaleBase;
    f32 scaleStep;
    f32 scaleLimit;
    f32 sp38;
    char sp20[0x10];
    char sp30[0x10];
    Vec sp40;

    flag = 0;
    mgId = MBMasuCurGet();
    sys = &GwSystem;
    spaceA = NULL;
    spaceB = NULL;
    if (func_800DCD9C_shared_board(sys->current_player_index) <= 0) {
        MBPlayerVibrate(-1, 3);
    }
    MBPlayerMotionSet(-1, -1, 2);

    switch (mgId) {
        case 0x21:
            func_800ED20C_shared_board(-1, 8, 0x6E);
            spaceA = MBMasuGet(0x6E);
            spaceB = MBMasuGet(0x21);
            break;
        case 0x4B:
            func_800ED20C_shared_board(-1, 8, 0x70);
            spaceA = MBMasuGet(0x70);
            spaceB = MBMasuGet(0x4B);
            break;
    }

    HuPrcSleep(8);
    if (func_800DCD9C_shared_board(sys->current_player_index) > 0) {
        func_800DBEC0_shared_board(sys->current_player_index);
    }
    HuAudFXPlay(0x114);

    model = MBModelCreate(0x32, NULL);
    MBModelTempAllocFree(model);
    vec = &sp40;
    HuVecSubtract(vec, &spaceB->coords, &spaceA->coords);
    MBVecNormalize(vec);
    HuVecCopy3F(&model->rot, vec);
    model->scale.y = 0.0f;
    HuVecCopy3F(&model->coords, &spaceA->coords);
    MBMotionSet(model, -1, 1);
    func_800D9A40_shared_board(model);

    effectModel = MBModelCreate(0x35, D_8011D42C_w02);
    MBModelTempAllocFree(effectModel);
    HuVecCopy3F(&effectModel->rot, vec);
    HuVecCopy3F(&effectModel->coords, &spaceA->coords);
    effectModel->scale.y = effectModel->scale.x = effectModel->scale.z = 1.2f;
    MBModelDispOff(effectModel);

    speed = 1.0f / sindf(50.0f);
    angle = 0.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 90.0f;
    for (; angle < scaleLimit; angle += scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    if (50.0f < angle) {
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        do {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
            angle -= scaleStep;
        } while (50.0f < angle);
    }

    model->scale.z = model->scale.x = model->scale.y = 1.0f;
    func_800D9A40_shared_board(effectModel);

    if (MBItemFind(-1, 0xF) != -1) {
    dialogLoop:
        MBDlgWinInsertCreate(-1, 0x3A1D, 0, 0, 0, 0, 0);
        choice = func_80109C98_w02((s32)D_8011D414_w02, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                func_80106AB0_w02();
                goto dialogLoop;
        }
    }

    MBMotionSet(model, -1, 0);
    func_8001C92C_main(model->omObj1->model[0], 1.2f);
    while (MBMotionCheck(model) == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x259);
    MBMotionSet(effectModel, 0, 0);
    while (MBMotionCheck(effectModel) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(effectModel, -1, 2);

    if (flag != 0) {
        sprintf(sp20, D_8011EA74_w02, GwSystem.bank_coins);
        if (GwSystem.bank_coins != 0) {
            MBDlgWinInsertCreate(2, 0x3A1E, (s32)sp20, 0, 0, 0, 0);
        } else {
            MBDlgWinInsertCreate(2, 0x3A1F, 0, 0, 0, 0, 0);
        }
        func_800EC9DC_shared_board();
        MBDlgWinClose();
        MBDlgWinKill();

        if (GwSystem.bank_coins != 0) {
            mbItemBtnF = 0;
            func_80112B10_w02();
            mbItemBtnF = 1;
        } else {
            MBDlgWinInsertCreate(2, 0x3A21, 0, 0, 0, 0, 0);
            func_800EC9DC_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
            GwPlayer[sys->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
            MBItemRemoveEmpty(sys->current_player_index);
            MBStatusItemIconSprReinit(sys->current_player_index);
        }

        if (func_800DCD9C_shared_board(sys->current_player_index) > 0) {
            func_800DB884_shared_board(sys->current_player_index);
        }
    } else {
        if (func_800DCD9C_shared_board(sys->current_player_index) > 0) {
            if ((GwPlayer[sys->current_player_index].coin != 0) && (GwPlayer[sys->current_player_index].coin < 5)) {
                sprintf(sp20, D_8011EA74_w02, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, D_8011EA74_w02, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                func_80107FB0_w02();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, D_8011EA74_w02, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, D_8011EA74_w02, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                func_80107FB0_w02();
                MBCoinChangeCreate(sys->current_player_index, -5);
                MBCoinTakeCreate(sys->current_player_index, -5);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            }
            func_800EC9DC_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
            func_800DB884_shared_board(sys->current_player_index);
            HuPrcSleep(10);
        } else {
            if (GwSystem.bank_coins != 0) {
                sprintf(sp20, D_8011EA74_w02, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                func_80107FB0_w02();
                MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
                MBPlayerMotionSet(-1, 5, 0);
                func_8004ACE0_main(0x274, sys->current_player_index);
                HuPrcSleep(30);
                MBPlayerMotionSet(-1, -1, 2);
                func_800EC6A8_shared_board();
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBDlgWinKill();
            } else {
                MBDlgWinExec(2, 0x1204);
            }
        }
    }

    HuAudFXPlay(0x115);
    MBMotionSet(model, -1, 4);
    func_8001C92C_main(model->omObj1->model[0], 1.2f);
    func_8001C6A8_main(
        model->omObj1->model[0], D_800CCF58_main[HmfModelData[model->omObj1->model[0]].unk02].unk02);
    while (func_800D9E80_shared_board(model) == 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(effectModel);

    speed = 1.0f / sindf(50.0f);
    angle = 50.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 90.0f;
    for (; angle < scaleLimit; angle += scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    angle = 90.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 0.0f;
    for (; scaleLimit < angle; angle -= scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    model->scale.y = 0;
    model->scale.x = 0;
    model->scale.z = 0;
    MBModelKill(model);
    MBModelKill(effectModel);
    func_80109C80_w02();
}

s32 func_8010AF00_w02(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011EC98_w02[i] != 0) {
            if (D_8011D45C_w02[D_8011EC90_w02][D_8011EC94_w02][i] == arg0) {
                return i;
            }
        }
    }
    return -1;
}

s32 func_8010AF88_w02(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011D45C_w02[D_8011EC90_w02][D_8011EC94_w02][i] == -1) {
            break;
        }
    }
    return i;
}

void func_8010AFF0_w02(void) {
    s32 grp = (s32)HuPrcCurrentGet()->user_data;
    f32 angle;
    f32 scaleX;

    MBPlayerGet(GwSystem.current_player_index);
    MBPlayerVibrate(-1, 2);
    HuAudFXPlay(0x15A);

    for (angle = 0.0f; angle < 180.0f; angle += 20.0f) {
        scaleX = sindf(angle) * 1.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.5f);
        HuPrcVSleep();
    }

    while (angle < 360.0f) {
        scaleX = sindf(angle) * 0.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.25f);
        HuPrcVSleep();
        angle += 20.0f;
    }

    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010B1C8_w02(void) {
    GW_SYSTEM *system = &GwSystem;
    SpaceData *spaceA;
    SpaceData *spaceB;
    Object *model;
    Object *playerObj;
    Unk3 *helpWin;
    void *data;
    Process *prc;
    u8 enabled[9];
    u8 itemFlags[6][4];
    Vec sp48;
    s32 dlgWin;
    s16 shopIdx;
    s32 flag2;
    s32 id;
    s32 slot;
    s32 row;
    s32 row2;
    s32 sel;
    s32 choice;
    s32 count;
    s32 item;
    s8 *itemPtr;
    s8(*shopTable)[5][7];
    s8(*shopItems)[7];
    s32 timer;
    s32 randVal;
    s32 i;
    s32 j;
    s32 grp;
    s32 grp2;
    s16 spriteId;
    s32 spriteId2;
    s16 sprY;
    s16 masuId;
    s16 camMasu;
    GW_PLAYER *player;
    Object *effectModel;
    f32 angle;
    f32 speed;
    f32 scaleK;
    f32 scaleBase;
    f32 scaleStep;
    f32 scaleLimit;
    f32 sp38;
    f32 scale;
    player = MBPlayerGet(-1);
    spaceA = NULL;
    spaceB = NULL;
    model = NULL;
    effectModel = NULL;
    MBPlayerMotionSet(-1, -1, 2);

    masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    switch (masuId) {
        case 0x73:
            camMasu = 0x6C;
            spaceA = MBMasuGet(0x6C);
            spaceB = MBMasuGet(0x73);
            D_8011D594_w02 = 0;
            break;
        case 0x69:
            camMasu = 0x6D;
            spaceA = MBMasuGet(0x6D);
            spaceB = MBMasuGet(0x69);
            D_8011D594_w02 = 1;
            break;
        default:
            camMasu = -1;
            break;
    }

    if (camMasu != -1) {
        func_800ED20C_shared_board(-1, 8, camMasu);
        HuPrcSleep(8);
    }
    func_800DBEC0_shared_board(system->current_player_index);

    switch (GwSystem.forceShopHost) {
        case 0:
            shopIdx = !MBRandCheck100(0x42);
            break;
        case 1:
            shopIdx = 0;
            break;
        default:
            shopIdx = 1;
            break;
    }

    dlgWin = 3;
    if (shopIdx != 0) {
        dlgWin = 5;
    }

    if (camMasu != -1) {
        flag2 = (shopIdx << 1) >> 1;
        id = (-shopIdx & 0x31) | 0x30;
        HuAudFXPlay(0x114);
        model = MBModelCreate(id, NULL);
        MBModelTempAllocFree(model);
        HuVecSubtract(&sp48, &spaceB->coords, &spaceA->coords);
        MBVecNormalize(&sp48);
        HuVecCopy3F(&model->rot, &sp48);
        model->scale.y = 0.0f;
        MBMotionSet(model, -1, 1);
        func_800D9A40_shared_board(model);
        HuVecCopy3F(&model->coords, &spaceA->coords);

        if (flag2 != 0) {
            effectModel = MBModelCreate(0x39, D_8011D58C_w02);
        } else {
            effectModel = MBModelCreate(0x1B, D_8011D584_w02);
        }
        MBModelTempAllocFree(effectModel);
        HuVecCopy3F(&effectModel->rot, &sp48);
        HuVecCopy3F(&effectModel->coords, &spaceA->coords);
        effectModel->scale.y = effectModel->scale.x = effectModel->scale.z = 1.2f;
        MBModelDispOff(effectModel);

        speed = 1.0f / sindf(50.0f);
        angle = 0.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 90.0f;
        for (; angle < scaleLimit; angle += scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        for (; 50.0f < angle; angle -= scaleStep) {
            scaleK = 0.2f;
            scaleBase = 0.8f;
            scaleStep = 11.25f;
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        model->scale.y = model->scale.x = model->scale.z = 1.0f;
        func_800D9A40_shared_board(effectModel);
        MBMotionSet(model, -1, 0);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(effectModel, 0, 0);

        if (shopIdx != 0) {
            HuAudFXPlay(0x2A0);
        } else {
            if (GwPlayer[system->current_player_index].coin < 5 || MBItemFindEmpty(system->current_player_index) == -1) {
                HuAudFXPlay(0x29A);
            } else if (system->current_turn != system->total_turns) {
                HuAudFXPlay(0x298);
            } else {
                HuAudFXPlay(0x29A);
            }
        }

        while (MBMotionCheck(effectModel) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(effectModel, -1, 2);
    }

    if (system->current_turn == system->total_turns) {
        MBDlgWinExec(dlgWin, D_8011D574_w02[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, D_8011D56C_w02[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, D_8011D564_w02[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, D_8011D55C_w02[shopIdx]);
    choice = func_80106F58_w02();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = BoardGetTurnTier(-1);
            row = D_8011D444_w02[shopIdx][i][BoardPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (D_8011D45C_w02[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_8011D45C_w02[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (D_8011D45C_w02[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_80100F94_shared_board[D_8011D45C_w02[shopIdx][row][j]] >
                    GwPlayer[system->current_player_index].coin) {
                    enabled[j] = 0;
                    itemFlags[i][0] = 1;
                }
                itemFlags[i][1] = 0;
                count++;
            }
            for (; j < 9; j++) {
                enabled[j] = 1;
            }

            MBDlgWinInsertCreate(dlgWin, D_8011D534_w02[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            func_800ECAA8_shared_board(0);
            D_8011EC90_w02 = slot;
            D_8011EC94_w02 = row;
            D_8011EC98_w02 = enabled;
            sel = func_80106CC4_w02(enabled);
            MBDlgWinClose();
            MBDlgWinKill();

            if (sel == count) {
                mbItemBtnF = 0;
                MBItemSelNoClear();
                MBItemDescExec(system->current_player_index);
                mbItemBtnF = 1;
                goto restart;
            }
            if (sel == count + 1 || sel == -1) {
                goto itemSelect;
            }

            playerObj = player->player_obj;
            i = shopIdx;
            shopTable = D_8011D45C_w02;
            shopItems = shopTable[i];
            itemPtr = (s8 *)(row * 7);
            itemPtr += (s32)shopItems;
            itemPtr += sel;
            MBCoinChangeCreate(system->current_player_index, -D_80100F94_shared_board[*itemPtr]);
            MBCoinTakeCreate(system->current_player_index, -D_80100F94_shared_board[*itemPtr]);
            HuPrcSleep(30);

            if (*itemPtr == 0x13) {
                item = i + 0x13;
            } else {
                GwPlayer[system->current_player_index].itemNo[MBItemFindEmpty(system->current_player_index)] =
                    D_8011D45C_w02[shopIdx][row][sel];
                item = D_8011D45C_w02[shopIdx][row][sel];
            }

            grp = HuSprGrpCreate(1, 5);
            i = 0;
            data = DataRead(D_8010197C_shared_board[item]);
            spriteId = func_80055810_main(data);
            DataClose(data);
            func_80055024_main(grp, 0, spriteId, 0);
            HuSprPriSet(grp, 0, 0xA);
            func_800550F4_main(grp, 0, 0);
            HuSprAttrSet(grp, 0, 0x180C);
            func_80054904_main(grp, 0, 0xA0, 0x5A);
            func_80055458_main(grp, 0, 0);
            MBVecForwardSet(&sp48);
            func_800ED128_shared_board(&player->player_obj->rot, &sp48, &player->player_obj->rot, 0xA);
            HuAudFXPlay(0x19);
            for (; i < 10; i++) {
                func_80055458_main(grp, 0, i * 25);
                HuPrcVSleep();
            }
            func_80055458_main(grp, 0, 0x100);

            if (D_8011D45C_w02[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = D_8011D4A4_w02[shopIdx][BoardGetTurnTier(-1)]
                                                [BoardPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < D_8011D4BC_w02[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = D_8011D520_w02[shopIdx][i];

                    if (camMasu != -1) {
                        helpWin = func_800E210C_shared_board(0x15, 0xA0, 1);
                    } else {
                        playerObj->flags |= 0x10;
                        helpWin = func_800E210C_shared_board(0x15, 0xA0, 0);
                    }
                    timer = 30;

                    if ((*(u16 *)((u8 *)D_800C9520_main + (GwPlayer[system->current_player_index].pad << 1)) & 0x8000) == 0) {
                        row = (s32)D_800C9520_main;
                        while (1) {
                            if (MBPlayerComCheck(-1) != 0) {
                                timer--;
                                if (timer == -1) {
                                    break;
                                }
                            }
                            HuPrcVSleep();
                            if (((u16 *)row)[GwPlayer[system->current_player_index].pad] & 0x8000) {
                                break;
                            }
                        }
                    }
                    MBHelpWinKill(helpWin);

                    MBPlayerMotionSet(system->current_player_index, 2, 0);
                    func_800EE688_shared_board(playerObj, 2.0f, -0.3f);
                    HuPrcSleep(5);
                    prc = omAddPrcObj(func_8010AFF0_w02, 0x4002, 0, 0);
                    prc->user_data = (void *)grp;
                    func_800EE6C0_shared_board(playerObj);
                    MBPlayerMotionSet(-1, -1, 2);

                    grp2 = HuSprGrpCreate(1, 5);
                    i = 0;
                    data = DataRead(D_8010197C_shared_board[item]);
                    spriteId2 = func_80055810_main(data);
                    DataClose(data);
                    func_80055024_main(grp2, 0, spriteId2, 0);
                    HuSprPriSet(grp2, 0, 0xB);
                    func_800550F4_main(grp2, 0, 0);
                    HuSprAttrSet(grp2, 0, 0x1000);
                    func_80054904_main(grp2, 0, 0xA0, 0x5A);
                    func_80055458_main(grp2, 0, 0);
                    MBVecForwardSet(&sp48);
                    func_800ED128_shared_board(&player->player_obj->rot, &sp48, &player->player_obj->rot, 0xA);

                    sprY = 0x5A;
                    scale = 0.0f;
                    do {
                        func_80054904_main(grp2, 0, 0xA0, sprY);
                        func_80055458_main(grp2, 0, i * 25);
                        HuSprScaleSet(grp2, 0, scale, scale);
                        i++;
                        HuPrcVSleep();
                        sprY -= 3;
                        scale += 0.1f;
                    } while (i < 10);
                    HuSprScaleSet(grp2, 0, 1.0f, 1.0f);
                    func_80055458_main(grp2, 0, 0x100);
                    HuPrcSleep(10);
                    GwPlayer[system->current_player_index].itemNo[MBItemFindEmpty(system->current_player_index)] = item;
                    HuSprGrpKill(grp2);
                    HuSprKill(spriteId2);
                }
                if (camMasu == -1) {
                    playerObj->flags &= ~0x10;
                }
            }

            HuPrcSleep(5);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            func_8004ACE0_main(0x274, system->current_player_index);
            HuPrcSleep(20);
            HuPrcVSleep();
            func_800F2388_shared_board(-1, -1, 0, 5, 2);
            HuPrcSleep(10);
            HuSprGrpKill(grp);
            HuSprKill(spriteId);
            break;
        case 1:
            MBDlgWinExec(dlgWin, D_8011D57C_w02[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                func_80106B38_w02();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106AB0_w02();
            }
            goto itemSelect;
    }

end:
    if (camMasu != -1) {
        HuAudFXPlay(0x115);
        MBMotionSet(model, -1, 4);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        func_8001C6A8_main(
            model->omObj1->model[0], D_800CCF58_main[HmfModelData[model->omObj1->model[0]].unk02].unk02);
        while (func_800D9E80_shared_board(model) == 0) {
            HuPrcVSleep();
        }
        MBModelDispOff(effectModel);

        speed = 1.0f / sindf(50.0f);
        angle = 50.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 90.0f;
        for (; angle < scaleLimit; angle += scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        angle = 90.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 0.0f;
        for (; scaleLimit < angle; angle -= scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        model->scale.y = 0;
        model->scale.x = 0;
        model->scale.z = 0;
        MBModelKill(model);
        MBModelKill(effectModel);
    }
    func_800DB884_shared_board(system->current_player_index);
    HuPrcSleep(10);
}

void func_8010C47C_w02(Object *obj) {
    s32 i;

    MBModelDispOn(obj);
    for (i = 0; i < 0x100; i += 0xC) {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    func_8001F9E4_main(obj->omObj1->model[0], 0xFF);
    func_8001F9E4_main(obj->omObj2->model[0], 0xFF);
}

void func_8010C51C_w02(Object *obj) {
    s32 i;

    for (i = 0xFF; i >= 0; i -= 0xC) {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    func_8001F9E4_main(obj->omObj1->model[0], 0);
    func_8001F9E4_main(obj->omObj2->model[0], 0);
    MBModelDispOff(obj);
}

s32 func_8010C5BC_w02(s32 playerIndex) {
    s32 hasRareItem = 0;
    s16 grp;
    void *data;
    s16 spriteId;
    s32 i;
    s32 duration;
    Process *process;

    grp = HuSprGrpCreate(1, 5);
    data = DataRead(0x13020E);
    spriteId = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp, 0, spriteId, 0);
    HuSprPriSet(grp, 0, 0xA);
    func_800550F4_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x1000);
    func_80054904_main(grp, 0, D_8011D5A8_w02[playerIndex].x,
                        D_8011D5A8_w02[playerIndex].y);
    func_80055458_main(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        func_80054904_main(grp, 0,
                            (i * D_8011D5C8_w02[playerIndex].x) +
                                D_8011D5A8_w02[playerIndex].x,
                            (i * D_8011D5C8_w02[playerIndex].y) +
                                D_8011D5A8_w02[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    func_80055458_main(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(func_80112340_w02, 0x4002, 0, 0);
        process->user_data = (void *)playerIndex;
    }

    if (!hasRareItem) {
        GwPlayer[playerIndex].star--;
    }
    MBPlayerVibrate(playerIndex, 5);
    HuAudFXPlay(0x257);

    duration = hasRareItem ? 0x78 : 0x1E;
    for (i = 0; i < duration; i++) {
        func_80054904_main(grp, 0,
                            (D_8011D5C8_w02[playerIndex].x * 16.0f) +
                                D_8011D5A8_w02[playerIndex].x,
                            (D_8011D5C8_w02[playerIndex].y * 16.0f) +
                                D_8011D5A8_w02[playerIndex].y +
                                (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        func_80054904_main(grp, 0,
                            (i * D_8011D5C8_w02[playerIndex].x) +
                                D_8011D5A8_w02[playerIndex].x,
                            (i * D_8011D5C8_w02[playerIndex].y) +
                                D_8011D5A8_w02[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprKill(spriteId);
    return !hasRareItem;
}

void func_8010CA04_w02(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

s32 func_8010CA28_w02(s32 playerIndex) {
    s32 hasRareItem;
    s16 grp;
    void *data;
    s16 spriteId;
    s16 playerGrp;
    s16 playerSpriteId;
    s32 i;
    s32 state;
    s32 playerSpriteVisible;
    s16 delay;
    s32 angle;
    s32 attempts;
    void *dialog;
    Process *process;

    hasRareItem = 0;
    grp = HuSprGrpCreate(1, 5);
    data = DataRead(0x13020E);
    spriteId = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp, 0, spriteId, 0);
    HuSprPriSet(grp, 0, 0xA);
    func_800550F4_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x1000);
    func_80054904_main(grp, 0, D_8011D5A8_w02[playerIndex].x,
                        D_8011D5A8_w02[playerIndex].y);
    func_80055458_main(grp, 0, 0);

    {
        playerGrp = HuSprGrpCreate(1, 5);
        playerSpriteVisible = 0;
        data = DataRead(D_80101040_shared_board[GwPlayer[playerIndex].chr]);
        playerSpriteId = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(playerGrp, 0, playerSpriteId, 0);
        HuSprPriSet(playerGrp, 0, 0xA);
        func_800550F4_main(playerGrp, 0, 1);
        if (playerIndex & 1) {
            HuSprAttrSet(playerGrp, 0, 0x1001);
        } else {
            HuSprAttrSet(playerGrp, 0, 0x1000);
        }
        if (MBItemFind(playerIndex, 0xC) != -1) {
            HuSprAttrSet(playerGrp, 0, 0x8000);
        }
        func_80054904_main(playerGrp, 0,
                            D_8011D5A8_w02[playerIndex].x -
                                (D_8011D5C8_w02[playerIndex].x * 16.0f) - 8.0f,
                            D_8011D5A8_w02[playerIndex].y +
                                (D_8011D5C8_w02[playerIndex].y * 16.0f));
        func_80055458_main(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            func_80054904_main(grp, 0,
                                (i * D_8011D5C8_w02[playerIndex].x) +
                                    D_8011D5A8_w02[playerIndex].x,
                                (i * D_8011D5C8_w02[playerIndex].y) +
                                    D_8011D5A8_w02[playerIndex].y);
            func_80055458_main(grp, 0, i << 4);
            func_80055458_main(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
        func_80055458_main(grp, 0, 0xFF);
        func_80055458_main(playerGrp, 0, 0xFF);

        MBWinInsertOpen(MBItemFind(playerIndex, 0xC) == -1 ? 0x620E : 0x620F,
                        (char *)mbCharNameMesTbl[GwPlayer[playerIndex].chr], 0, 0, 0, 0);
        MBPlayerVibrate(playerIndex, 2);
        func_800EC3C0_shared_board(playerIndex);
        if (MBItemFind(playerIndex, 0xC) != -1) {
            omAddPrcObj(func_8010CA04_w02, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(func_80112340_w02, 0x4002, 0, 0);
            process->user_data = (void *)playerIndex;
        }
        HuAudFXPlay(0x133);
        dialog = MBPlayerVibrateObjCreate(playerIndex, 3, 5);
        delay = MBRand(10.0f) + 1;
        i = 0;
        angle = 0;

        for (; i < 0x78; i++, delay--) {
            if (delay == 0) {
                HuAudFXPlay(0x257);
                delay = MBRand(15.0f) + 0x1E;
            }
            state -= !(state < 2);
            if (state == 0) {
                func_80054904_main(
                    grp, 0,
                    (D_8011D5C8_w02[playerIndex].x * 16.0f) +
                        D_8011D5A8_w02[playerIndex].x,
                    (D_8011D5C8_w02[playerIndex].y * 16.0f) +
                        D_8011D5A8_w02[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                func_80054904_main(
                    grp, 0,
                    (D_8011D5C8_w02[playerIndex].x * 16.0f) +
                        D_8011D5A8_w02[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (D_8011D5C8_w02[playerIndex].y * 16.0f) +
                        D_8011D5A8_w02[playerIndex].y);
                func_80054904_main(
                    playerGrp, 0,
                    D_8011D5A8_w02[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (D_8011D5C8_w02[playerIndex].y * 16.0f) +
                        D_8011D5A8_w02[playerIndex].y);
                angle++;
            }

            if (GwPlayer[playerIndex].stat & 1) {
                if (state == 0) {
                    goto tryInput;
                } else {
                    if (GwPlayer[playerIndex].cpu_difficulty == 0) {
                        if ((6 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if (GwPlayer[playerIndex].cpu_difficulty == 1) {
                        if ((7 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if (GwPlayer[playerIndex].cpu_difficulty == 2) {
                        if ((8 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if ((9 - MBRand(2.0f)) >= state) {
                        goto tryInput;
                    }
                }
            } else if (D_800C9520_main[GwPlayer[playerIndex].pad] & 0x8000) {
            tryInput:
                if (!hasRareItem) {
                    attempts++;
                    state = 10;
                    if (!playerSpriteVisible) {
                        func_80055140_main(playerGrp, 0, 1, 0);
                        func_800550F4_main(playerGrp, 0, 1);
                        playerSpriteVisible = 1;
                        func_80054904_main(
                            playerGrp, 0, D_8011D5A8_w02[playerIndex].x - 8.0f,
                            (D_8011D5C8_w02[playerIndex].y * 16.0f) +
                                D_8011D5A8_w02[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                func_80055140_main(playerGrp, 0, 0, 0);
                func_800550F4_main(playerGrp, 0, 1);
                playerSpriteVisible = 0;
                func_80054904_main(
                    playerGrp, 0,
                    D_8011D5A8_w02[playerIndex].x -
                        (D_8011D5C8_w02[playerIndex].x * 16.0f) - 8.0f,
                    (D_8011D5C8_w02[playerIndex].y * 16.0f) +
                        D_8011D5A8_w02[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(func_8010CA04_w02, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011D5C8_w02[playerIndex].x) +
                                    D_8011D5A8_w02[playerIndex].x,
                                (i * D_8011D5C8_w02[playerIndex].y) +
                                    D_8011D5A8_w02[playerIndex].y);
            func_80055458_main(grp, 0, i << 4);
            func_80055458_main(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011D5C8_w02[playerIndex].x) +
                                    D_8011D5A8_w02[playerIndex].x,
                                (i * D_8011D5C8_w02[playerIndex].y) +
                                    D_8011D5A8_w02[playerIndex].y);
            func_80054904_main(playerGrp, 0,
                                ((i - 0x10) * D_8011D5C8_w02[playerIndex].x) +
                                    D_8011D5A8_w02[playerIndex].x - 8.0f,
                                (i * D_8011D5C8_w02[playerIndex].y) +
                                    D_8011D5A8_w02[playerIndex].y);
            if (hasRareItem) {
                i -= 2;
            }
            HuPrcVSleep();
        }
        func_80055140_main(playerGrp, 0, 0, 0);
        func_800550F4_main(playerGrp, 0, 1);
        for (i = 0x10; i >= 0; i -= 2) {
            func_80055458_main(grp, 0, i << 4);
            HuPrcVSleep();
        }
    }

    HuSprGrpKill(grp);
    HuSprKill(spriteId);
    HuSprGrpKill(playerGrp);
    HuSprKill(playerSpriteId);

    playerSpriteVisible = -2;
    if (!hasRareItem) {
        for (i = 0; i < ARRAY_COUNTU(D_8011D5E8_w02); i++) {
            if ((GwSystem.current_turn >= D_8011D5E8_w02[i][0]) &&
                (GwSystem.current_turn <= D_8011D5E8_w02[i][1])) {
                break;
            }
        }
        playerSpriteVisible = D_8011D5E8_w02[i][2];
        for (i = 0; i < ARRAY_COUNTU(D_8011D5FC_w02); i++) {
            if ((attempts >= D_8011D5FC_w02[i][0]) &&
                (attempts <= D_8011D5FC_w02[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= D_8011D5FC_w02[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}






void func_8010D854_w02(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011EC9C_w02);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += D_8011EA78_w02; // 1.5 (the literal sits in the .data asm file)
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

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

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119D84_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119DB0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B038_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B8A0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B934_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B988_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011BA58_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011BB30_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011BB84_w02);

INCLUDE_RODATA("asm/nonmatchings/overlays/w02/335610", D_8011EB68_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011BC6C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011C274_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011C5D8_w02);
