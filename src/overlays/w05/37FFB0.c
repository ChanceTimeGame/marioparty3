#include "common.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/10C230.h"
#include "WaluigisIsland.h" /* BranchLink */
#include "game/board.h"
#include "../ovl_80_shared_board/1006F0.h"
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
#include "gcc/memory.h"
#include "mallocblock.h"
#include "../ovl_80_shared_board/106640.h"
#include "input.h"
#include "game/window.h"
#include "game/hmfman.h"

// board x1
typedef s16 SpaceTriple[3];
typedef s16 SpacePair[2];
typedef BranchLink BranchPair[2];

typedef struct {
    /* 0x00 */ Object *obj1;
    /* 0x04 */ Object *obj2;
    /* 0x08 */ s32 state;
    /* 0x0C */ s32 flag;
} ModelAnimWork;

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ Object *model;
    /* 0x1C */ u16 unk1C;
} ModelFadeWork;

typedef struct {
    u8 unk[4];
} Unk4Bytes;
typedef BranchLink g1BranchLink;

extern DecisionTreeNonLeafNode *D_8011D6BC_w05[];
extern DecisionTreeNonLeafNode *D_8011D7A0_w05[];
extern DecisionTreeNonLeafNode *D_8011D818_w05[];
extern DecisionTreeNonLeafNode *D_8011D8D8_w05[];
extern DecisionTreeNonLeafNode *D_8011DB0C_w05[];
extern DecisionTreeNonLeafNode *D_8011DBF0_w05[];
extern DecisionTreeNonLeafNode *D_8011DCB0_w05[];
extern DecisionTreeNonLeafNode *D_8011DDAC_w05[];
extern DecisionTreeNonLeafNode *D_8011DE30_w05[];
extern DecisionTreeNonLeafNode *D_8011DE60_w05[];
extern DecisionTreeNonLeafNode *D_8011DE90_w05[];
extern Object *D_80120740_w05;
extern Object *D_80120748_w05[8];
extern Object *D_8012078C_w05;
extern Object *D_801207E0_w05;
extern Object *D_801207E4_w05[1];
extern Object *D_801207E8_w05;
extern Object *D_801207F0_w05[10];
extern Object *D_80120818_w05;
extern Object *D_8012081C_w05[2];
extern Process *D_80120768_w05[8];
extern Unk3 *D_80120790_w05;
extern Unk3 *D_80120794_w05;
extern Unk3 *D_80120798_w05;
extern Unk3 *D_8012079C_w05;
extern Unk3 *D_801207A0_w05;
extern Vec D_8011D158_w05[];
extern Vec D_8011D194_w05[];
extern const u8 D_80120620_w05[];
extern g1BranchLink D_8011E5FC_w05[][2];
extern g1BranchLink D_8011E644_w05[][2];
extern g1BranchLink D_8011E68C_w05[][2];
extern g1BranchLink D_8011E6D4_w05[][2];
extern g1BranchLink D_8011E71C_w05[][2];
extern g1BranchLink D_8011E764_w05[][2];
extern g1BranchLink D_8011E7AC_w05[][2];
extern s16 D_8011D040_w05[];
extern s16 D_8011D050_w05[];
extern s16 D_8011D060_w05[];
extern s16 D_8011D070_w05[];
extern s16 D_8011D080_w05[];
extern s16 D_8011D0E8_w05[][2];
extern s16 D_8011D108_w05[][2];
extern s16 D_8011D110_w05[][2];
extern s16 D_8011D118_w05[][2];
extern s16 D_8011D120_w05[][2];
extern s16 D_8011D128_w05[][2];
extern s16 D_8011D130_w05[];
extern s16 D_8011D140_w05[];
extern s16 D_8011D150_w05[];
extern s16 D_8011D154_w05[];
extern s16 D_8011D1D0_w05[];
extern s16 D_8011D1D4_w05[];
extern s16 D_8011D2B8_w05[];
extern s16 D_8011D2BC_w05[];
extern s16 D_8011E3F0_w05[];
extern s16 D_8011E480_w05[];
extern s16 D_8011E4C8_w05[];
extern s16 D_8011E510_w05[];
extern s16 D_8011E5E8_w05[][3];
extern s16 D_8011E630_w05[][3];
extern s16 D_8011E678_w05[][3];
extern s16 D_8011E6C0_w05[][3];
extern s16 D_8011E708_w05[][3];
extern s16 D_8011E750_w05[][3];
extern s16 D_8011E798_w05[][3];
extern s32 D_8011D090_w05[];
extern s32 D_8011D0AC_w05[];
extern s32 D_8011D228_w05[];
extern s32 D_8011D24C_w05[];
extern s32 D_8011D270_w05[];
extern s32 D_8011D294_w05[];
extern s32 D_8011E404_w05[];
extern s32 D_8011E494_w05[];
extern s32 D_8011E4DC_w05[];
extern s32 D_8011E524_w05[];
extern s32 D_80120788_w05;
extern s32 D_801207A4_w05;
extern s32 D_801207A8_w05;
extern s32 D_80120824_w05;
extern s32 D_80120828_w05;
extern s8 D_8011EA00_w05[][5][7];
extern u32 *D_8011D210_w05[];
extern u8 *D_8012082C_w05;
s16 func_801059D0_w05(void);
s32 func_80105C30_w05(s16 arg0);
s32 func_80106CC4_w05(u8 *arg0);
s32 func_80106F58_w05(void);
s32 func_80107438_w05(u8 *arg0, s32 arg1, s32 arg2);
s32 func_801096DC_w05(s32 arg0, s32 arg1);
s32 func_8010A944_w05(s32 arg0);
s32 func_8010A9CC_w05(void);
s32 func_8011CC50_w05(void);
s32 func_8011CFB4_w05(void);
void func_801059F8_w05(void);
void func_80105B8C_w05(void);
void func_80105CA4_w05(void);
void func_80106120_w05(void);
void func_801064DC_w05(void);
void func_80106A3C_w05(Object *arg);
void func_80106B94_w05(void);
void func_80106C64_w05(void);
void func_80107170_w05(void);
void func_801072A0_w05(void);
void func_8010782C_w05(void);
void func_80107C14_w05(void);
void func_80107C40_w05(s16 arg0);
void func_80107D68_w05(void);
void func_80107DCC_w05(void);
void func_80107E78_w05(s16 arg0);
void func_80107F98_w05(void);
void func_80107FF4_w05(void);
void func_801080F0_w05(s16 arg0);
void func_8010825C_w05(void);
void func_801082C4_w05(s16 arg0);
void func_80108430_w05(void);
void func_80108490_w05(void);
void func_801084EC_w05(s32 arg0, s32 arg1);
void func_801085B4_w05(void);
void func_801086A0_w05(void);
void func_80108720_w05(void);
void func_801088B8_w05(s16 (*masu)[3], g1BranchLink (*links)[2], DecisionTreeNonLeafNode **trees);
void func_80108A58_w05(void);
void func_80108B18_w05(void);
void func_80108B50_w05(void);
void func_80108B88_w05(void);
void func_80108CF8_w05(void);
void func_80108D28_w05(void);
void func_80108D58_w05(void);
void func_80108D88_w05(void);
void func_80108DB8_w05(void);
void func_80108DE8_w05(void);
void func_80108E18_w05(void);
void func_80109A5C_w05(void);
void func_80115A30_w05(s16 (*masu)[3], BranchLink (*links)[2], DecisionTreeNonLeafNode **trees);
// board x1 end

s16 func_801059D0_w05(void) {
    return D_8011D080_w05[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void func_801059F8_w05(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < D_8011D050_w05[idx2]) {
                continue;
            }
            if (idx2 < D_8011D050_w05[idx1]) {
                continue;
            }
            {
                s32 temp = D_8011D040_w05[idx1];
                D_8011D040_w05[idx1] = D_8011D040_w05[idx2];
                D_8011D040_w05[idx2] = temp;
                temp = D_8011D050_w05[idx1];
                D_8011D050_w05[idx1] = D_8011D050_w05[idx2];
                D_8011D050_w05[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = D_8011D040_w05[i];
    }
}

void func_80105B00_w05(void) {
    GW_SYSTEM *loc;
    s32 sp7;
    s32 sp0;

    loc = &GwSystem;
    loc->current_star_spawn++;
    if (loc->current_star_spawn >= 8) {
        sp7 = loc->star_spawn_indices[7];
        loc->current_star_spawn = 0;
        GWBoardFlagSet(4);
        func_801059F8_w05();
        sp0 = loc->star_spawn_indices[0];
        if ((sp7 ^ sp0) == 0) {
            loc->star_spawn_indices[0] = loc->star_spawn_indices[7];
            loc->star_spawn_indices[7] = sp0;
        }
    }
}

void func_80105B8C_w05(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(D_8011D060_w05[i]);
    }
    MBMasuTypeSet(D_8011D070_w05[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(D_8011D060_w05[loc->star_spawn_indices[loc->current_star_spawn]]);
}

s32 func_80105C30_w05(s16 arg0) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        if (arg0 == D_8011D070_w05[i]) {
            if (i == loc->star_spawn_indices[loc->current_star_spawn]) {
                loc->unk_0E = D_8011D060_w05[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

void func_80105CA4_w05(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    D_8012078C_w05 = MBModelCreate(0x3A, NULL);
    model = D_8012078C_w05;
    func_800461B4_main(model->omObj1->model[0]);
    model->flags |= 4;
    func_800ECC54_shared_board(model);
    HuVecCopy3F(&model->coords, &space->coords);
    model->velocity.x = 50.0f;
    obj = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(obj, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(obj, 30.0f);
    func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
    func_8001C8A8_main(obj, 1);

    scale = 0.0f;
    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale += 0.5f;
        func_8000D018_main(obj, scale * 30.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale -= 0.4f;
        func_8000D018_main(obj, scale * 30.0f);
        HuPrcVSleep();
    }

    func_8000D018_main(obj, scale * 30.0f);
    HuPrcSleep(30);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    while (1) {
        func_8008A2A0_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (scale > 0.6f) {
            scale -= 0.04f;
        }
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        if (model->velocity.x > 10.0f) {
            model->velocity.x -= 1.2f;
        }
        func_8000D018_main(obj, scale * 30.0f);
        func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
        if ((model->velocity.x <= 10.0f) & (scale <= 0.6f)) {
            if (angle == 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }

    func_8008A2A0_main(HmfModelData[model->omObj1->model[0]].mtx, 0.0f);
    func_8000D044_main(obj);
    D_80120788_w05 = 0;
    omDelPrcObj(NULL);
}

void func_80106094_w05(omObjData **arg) {
    omObjData *s0 = *arg;

    s0->scale.y = 4.0f;
    s0->scale.z = -0.6f;
    HuPrcSleep(3);
    while (s0->scale.z != 0.0f) {
        HuPrcVSleep();
    }
}

void func_80106120_w05(void) {
    struct UnkMBGuideData *data;
    GW_SYSTEM *loc = &GwSystem;
    SpaceData *space;
    s32 idx;

    D_800A12D4_main = 0;
    data = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(data->obj, 2, 0xF, D_8011D090_w05[0]);
    func_800FFF44_shared_board();
    MBModelDispOff(D_80120748_w05[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_800E6FCC_shared_board();
    func_800E9730_shared_board(3.0f);
    func_80106094_w05((omObjData **)data);
    func_8005B43C_main(
        data->amount,
        (loc->current_star_spawn == 0 && GWBoardFlagCheck(4) == 0)
            ? (((loc->current_board_index == 2) ? 0x5E09 : 0) | 0x5E00)
            : (((loc->current_board_index == 2) ? 0x5E09 : 0) | 0x5E01),
        -1, -1);
    func_80060C14_main(data->amount, 1);
    HuAudFXPlay(0x2A7);
    func_800EE2C0_shared_board(data->amount);
    MBMotionShiftSet(data->obj, -1, 0, 6, 2);
    func_80060EA8_main(data->amount, 1);
    func_8001FDE8_main(data->obj->omObj1->model[0]);
    if (loc->current_board_index != 2 || (rand8() & 1)) {
        space = MBMasuGet(D_8011D080_w05[loc->star_spawn_indices[loc->current_star_spawn]]);
    }
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    idx = MBRand(7.0f);
    MBGuideFaceSet(data->obj, D_8011D090_w05[idx]);
    MBMotionSet(data->obj, -1, 2);
    if (loc->current_board_index != 2) {
        Process *prc = omAddPrcObj(func_80105CA4_w05, 0x4800, 0, 0);
        D_80120788_w05 = (s32)prc;
        prc->user_data = space;
        HuPrcSleep(30);
    } else {
        D_80120788_w05 = 0;
    }
    func_8005B43C_main(data->amount, D_8011D0AC_w05[idx], -1, -1);
    func_80060C14_main(data->amount, 1);
    func_800EE2C0_shared_board(data->amount);
    MBMotionShiftSet(data->obj, -1, 0, 6, 2);
    func_80060EA8_main(data->amount, 1);
    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(2, 0x10);
    HuPrcSleep(0x11);
    D_800A12D4_main = 1;
    func_80100130_shared_board();
    func_80046558_main(D_8012078C_w05->omObj1->model[0]);
    MBModelKill(D_8012078C_w05);
    MBModelDispOn(D_80120748_w05[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBGuideKill(data);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801064DC_w05);

void func_80106A3C_w05(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801064DC_w05, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

void func_80106AB0_w05(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80106B38_w05(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void func_80106B94_w05(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_80120790_w05 = func_800E210C_shared_board(0, 0x92, 1);
    D_80120794_w05 = func_800E210C_shared_board(1, 0xA0, 1);
    D_801207A0_w05 = func_800E210C_shared_board(0xD, 0xAE, 1);
    D_80120798_w05 = func_800E210C_shared_board(3, 0xBC, 1);
    D_8012079C_w05 = func_800E210C_shared_board(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80106C64_w05(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_80120790_w05);
    MBHelpWinKill(D_80120794_w05);
    MBHelpWinKill(D_801207A0_w05);
    MBHelpWinKill(D_80120798_w05);
    MBHelpWinKill(D_8012079C_w05);
}

s32 func_80106CC4_w05(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_80120620_w05;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = func_8011CC50_w05();
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
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

    for (i = 0; i < 9; i++) {
        if (arg0[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    do {
        i = func_8005E1D8_main(mbDlgWinId, i, 0);
        if (i == -1) {
            return -1;
        }
    } while (arg0[i] == 0);
    return i;
}

s32 func_80106F58_w05(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_80120620_w05;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // dead store; matches func_800FA104_shared_board
                var_s2 = func_8011CFB4_w05();
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

    func_8005E1D8_main(mbDlgWinId, 0, 1);
}

void func_80107170_w05(void) {
    s32 i;
    s32 cur = GwSystem.current_player_index;

    for (i = 0; i < 4; i++) {
        if (i != cur && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i != 4) {
        if (GwPlayer[cur].coin >= 50) {
            if (MBRand(100.0f) < GwPlayer[cur].coin + 10) {
                D_801207A4_w05 = 1;
                if (GwPlayer[cur].star < 99) {
                    return;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (i != cur && GwPlayer[i].coin >= 5) {
            break;
        }
    }
    if (i != 4) {
        D_801207A4_w05 = 0;
    } else {
        D_801207A4_w05 = 2;
    }
}

void func_801072A0_w05(void) {
    s32 order[4];
    s32 i;
    s32 j;
    s32 cur = GwSystem.current_player_index;

    for (i = 0; i < 4; i++) {
        order[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        j = MBPlayerStealRankGet(i);
        while (1) {
            if (order[j] == -1) {
                break;
            }
            j++;
        }
        order[j] = i;
    }
    func_80107170_w05();
    if (D_801207A4_w05 == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                D_801207A8_w05 = order[i];
                break;
            }
        }
    } else if (D_801207A4_w05 == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                D_801207A8_w05 = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        D_801207A4_w05 = 2;
    }
}

s32 func_80107438_w05(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_80120620_w05;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 == 0) {
                    func_801072A0_w05();
                    var_s2 = D_801207A4_w05 + 1;
                } else {
                    var_s2 = D_801207A8_w05 + 1;
                }
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
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

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (arg0[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    while (1) {
        i = func_8005E1D8_main(mbDlgWinId, i, arg2);
        if (arg2 == 0) {
            if (i == -1) {
                return -1;
            }
        }
        if (arg0[i] != 0) {
            return i;
        }
    }
}

s32 func_80107704_w05(u8 *arg0) {
    return func_80107438_w05(arg0, 0, 1);
}

s32 func_80107724_w05(u8 *arg0) {
    return func_80107438_w05(arg0, 1, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107744_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107780_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010782C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107B90_w05);

void func_80107C14_w05(void) {
    Hu3DCamInit(1);
    func_8010782C_w05();
    MBStart(1);
}

void func_80107C40_w05(s16 arg0) {
    Object *obj;

    if (D_80120748_w05[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_800461B4_main(obj->omObj1->model[0]);
    if (D_80120740_w05 == NULL) {
        D_80120740_w05 = obj;
    }
    D_80120748_w05[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_80120768_w05[arg0] = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011D130_w05[arg0])->coords);
    func_800D771C_shared_board(0xB, obj, D_8011D0E8_w05[arg0][0], D_8011D0E8_w05[arg0][1]);
}

void func_80107D68_w05(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        Process *prc = D_80120768_w05[i];

        if (prc != NULL) {
            omDelPrcObj(prc);
            D_80120768_w05[i] = NULL;
        }
    }
}

void func_80107DCC_w05(void) {
    s32 i;

    D_80120740_w05 = 0;
    for (i = 0; i < 8; i++) {
        D_80120748_w05[i] = 0;
        D_80120768_w05[i] = NULL;
        MBKinokoEffKillHookSet(func_80107D68_w05);
        if (!GWBoardFlagCheck(D_8011D140_w05[i])) {
            func_80107C40_w05(i);
        }
    }
}

void func_80107E78_w05(s16 arg0) {
    Object *obj;

    if (D_801207E4_w05[arg0] != NULL) {
        return;
    }
    if (D_801207E0_w05 == NULL) {
        obj = MBModelCreate(0xA, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_801207E0_w05 = obj;
    } else {
        obj = MBModelLinkCreate(D_801207E0_w05);
    }
    MBModelDispOff(obj);
    D_801207E4_w05[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011D150_w05[arg0])->coords);
    func_800D771C_shared_board(0xA, obj, D_8011D108_w05[arg0][0], D_8011D108_w05[arg0][1]);
}

void func_80107F98_w05(void) {
    s32 i;

    D_801207E0_w05 = 0;
    for (i = 0; i <= 0; i++) {
        D_801207E4_w05[i] = NULL;
        func_80107E78_w05(i);
    }
}

void func_80107FF4_w05(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(D_801207F0_w05[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(D_801207F0_w05[i * 5 + j]);
        }
    }
}

void func_801080F0_w05(s16 arg0) {
    Object *obj;

    if (D_801207F0_w05[arg0] != NULL) {
        return;
    }
    if (D_801207E8_w05 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_801207E8_w05 = obj;
    } else {
        obj = MBModelLinkCreate(D_801207E8_w05);
    }
    D_801207F0_w05[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011D154_w05[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &D_8011D158_w05[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = D_8011D194_w05[arg0 % 5].x;
    obj->omObj1->rot.z = D_8011D194_w05[arg0 % 5].z;
    MBModelDispOff(obj);
}

void func_8010825C_w05(void) {
    s32 i;

    D_801207E8_w05 = 0;
    for (i = 0; i < 0xA; i++) {
        D_801207F0_w05[i] = NULL;
        func_801080F0_w05(i);
    }
    func_80107FF4_w05();
}

void func_801082C4_w05(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (D_8012081C_w05[arg0] != NULL) {
        return;
    }
    if (D_80120818_w05 == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(D_8011D1D4_w05[board], D_8011D210_w05[board]);
        MBModelTempAllocFree(obj);
        D_80120818_w05 = obj;
    } else {
        obj = MBModelLinkCreate(D_80120818_w05);
    }
    D_8012081C_w05[arg0] = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011D1D0_w05[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(D_8011D128_w05[arg0][0]);
        SpaceData *masuB = MBMasuGet(D_8011D128_w05[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    func_800D771C_shared_board(0xC, obj, D_8011D120_w05[arg0][0], D_8011D120_w05[arg0][1]);
}

void func_80108430_w05(void) {
    s32 i;

    D_80120818_w05 = 0;
    for (i = 0; i < 2; i++) {
        D_8012081C_w05[i] = NULL;
        func_801082C4_w05(i);
    }
}

void func_80108490_w05(void) {
    HuPrcSleep(D_8011D270_w05[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011D24C_w05[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void func_801084EC_w05(s32 arg0, s32 arg1) {
    MBMotionSet(D_8012081C_w05[arg0], arg1 - 1, 0);
    func_8001C814_main(D_8012081C_w05[arg0]->omObj1->model[0], 5, 0);
    if (D_8011D228_w05[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011D228_w05[GwSystem.current_board_index]);
    }

    if (D_8011D24C_w05[GwSystem.current_board_index] != -1) {
        omAddPrcObj(func_80108490_w05, 0x1000, 0, 0);
    }
}

void func_801085B4_w05(void) {
    s32 index;
    s32 sleep;

    index = (s32)HuPrcCurrentGet()->user_data;

    switch (GwSystem.walk_speed) {
        case 0:
            sleep = 5;
            break;
        case 1:
            sleep = 10;
            break;
        default:
            sleep = 15;
            break;
    }

    HuPrcSleep(sleep);
    func_8001C814_main(D_8012081C_w05[index]->omObj1->model[0], 1, 4);

    if (D_8011D294_w05[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011D294_w05[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void func_80108664_w05(Object *arg) {
    Process *temp = omAddPrcObj(func_801085B4_w05, 0x1000, 0, 0);

    temp->user_data = arg;
}

void func_801086A0_w05(void) {
    s32 i;

    D_80120818_w05 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011D2B8_w05[i])->coords,
                                         D_8011D110_w05[i][0], D_8011D110_w05[i][1]);
    }
}

void func_80108720_w05(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011D2BC_w05[i])->coords,
                                         D_8011D118_w05[i][0], D_8011D118_w05[i][1]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108798_w05);

void func_80108830_w05(s32 masuAbsIndex, s16 arg1, s16 arg2) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == masuAbsIndex) {
        MBMoveNextMasuSet(-1, arg1, arg2);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801088B8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108924_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108948_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801089A8_w05);

void func_80108A58_w05(void) {
    func_80115A30_w05((SpaceTriple *)D_8011E3F0_w05, (BranchPair *)D_8011E404_w05, D_8011D6BC_w05);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108A90_w05);

void func_80108B18_w05(void) {
    func_80115A30_w05((SpaceTriple *)D_8011E480_w05, (BranchPair *)D_8011E494_w05, D_8011D7A0_w05);
    omDelPrcObj(NULL);
}

void func_80108B50_w05(void) {
    func_80115A30_w05((SpaceTriple *)D_8011E4C8_w05, (BranchPair *)D_8011E4DC_w05, D_8011D818_w05);
    omDelPrcObj(NULL);
}

void func_80108B88_w05(void) {
    func_80115A30_w05((SpaceTriple *)D_8011E510_w05, (BranchPair *)D_8011E524_w05, D_8011D8D8_w05);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108BC0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108C70_w05);

void func_80108CF8_w05(void) {
    func_801088B8_w05(D_8011E5E8_w05, D_8011E5FC_w05, D_8011DB0C_w05);
}

void func_80108D28_w05(void) {
    func_801088B8_w05(D_8011E630_w05, D_8011E644_w05, D_8011DBF0_w05);
}

void func_80108D58_w05(void) {
    func_801088B8_w05(D_8011E678_w05, D_8011E68C_w05, D_8011DCB0_w05);
}

void func_80108D88_w05(void) {
    func_801088B8_w05(D_8011E6C0_w05, D_8011E6D4_w05, D_8011DDAC_w05);
}

void func_80108DB8_w05(void) {
    func_801088B8_w05(D_8011E708_w05, D_8011E71C_w05, D_8011DE30_w05);
}

void func_80108DE8_w05(void) {
    func_801088B8_w05(D_8011E750_w05, D_8011E764_w05, D_8011DE60_w05);
}

void func_80108E18_w05(void) {
    func_801088B8_w05(D_8011E798_w05, D_8011E7AC_w05, D_8011DE90_w05);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108E48_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108E6C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108E90_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108EB4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108F20_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108F44_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108F68_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108F8C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108FB0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108FD4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108FF8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010901C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109078_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801090A4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801090C8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801090EC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109118_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010913C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109160_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109184_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801091A8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801091CC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801091F0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109214_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109270_w05);

void func_801096C4_w05(void) {
}

void func_801096CC_w05(void) {
}

void func_801096D4_w05(void) {
}

s32 func_801096DC_w05(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_80120620_w05;

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

void func_80109960_w05(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
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

void func_80109A1C_w05(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

void func_80109A5C_w05(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = func_80105C30_w05(spaceIdx);
    if (spaceIdx == 1) {
        func_800DBEC0_shared_board(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, func_801059D0_w05());
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
                choice = func_801096DC_w05(2, 0);
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
                        func_80106A3C_w05(D_80120740_w05);
                        HuPrcSleep(30);
                        func_800EDA58_shared_board();
                        func_800FF7F0_shared_board(2);
                        func_801096CC_w05();
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
                        func_801096CC_w05();
                        return;
                    case 2:
                        func_80106AB0_w05();
                        goto purchaseMenu;
                    default:
                        func_801096CC_w05();
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

    func_801096CC_w05();
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109E08_w05);

s32 func_8010A944_w05(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8012082C_w05[i] != 0) {
            if (D_8011EA00_w05[D_80120824_w05][D_80120828_w05][i] == arg0) {
                return i;
            }
        }
    }
    return -1;
}

s32 func_8010A9CC_w05(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011EA00_w05[D_80120824_w05][D_80120828_w05][i] == -1) {
            break;
        }
    }
    return i;
}

void func_8010AA34_w05(void) {
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

    for (; angle < 360.0f; angle += 20.0f) {
        scaleX = sindf(angle) * 0.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.25f);
        HuPrcVSleep();
    }

    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010AC0C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010BEC0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010BF60_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010C000_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010C448_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010C46C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010D298_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010D3EC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010D428_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E5FC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E618_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E634_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E790_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E8A8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010EC70_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010ECDC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010EE9C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F100_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F1D0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F400_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F5D0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F740_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010FA8C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010FC50_w05);

INCLUDE_RODATA("asm/nonmatchings/overlays/w05/37FFB0", D_80120690_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010FEE8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80110174_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801103B4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801105C4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80110884_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80110C24_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80111620_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80111B68_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80111D84_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112178_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112234_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112388_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801123C4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112554_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112910_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112BA8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112CB4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112E90_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80113B3C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80113BFC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011412C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80114A38_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80114B70_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80114CE0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80114EA8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011512C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115A30_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115C28_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115CA0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115D04_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115EB0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115FB0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011604C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011614C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116358_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801164B8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116508_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116A80_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116C50_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116D88_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011720C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801178B4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80117908_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80118364_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80118464_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801184C0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80118BBC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80118CF8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80118E2C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801191C0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801192AC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119610_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119A4C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119BC4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119F04_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119F7C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011A6E8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011A8D8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011ABEC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011AD34_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011AEA4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011BB74_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011BC40_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C2A8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C2F8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C348_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C39C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C448_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C50C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C560_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C648_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011CC50_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011CFB4_w05);
