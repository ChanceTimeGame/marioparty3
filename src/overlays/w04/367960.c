#include "common.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/FA250.h"

void func_801183D4_w04(void);
void func_801191B8_w04(void);
void func_8011A4E0_w04(s32);

// board q1
#include "WaluigisIsland.h" /* BranchLink */
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/EB2F0.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/F9DE0.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "gcc/memory.h"
#include "mallocblock.h"

extern Process *D_8011E038_w04;
extern s32 D_8011B790_w04[];
extern s32 D_8011B7AC_w04[];
extern Object *D_8011DFF8_w04[];
extern s32 D_8011B7C8_w04;
extern Unk3 *D_8011E040_w04;
extern Unk3 *D_8011E044_w04;
extern Unk3 *D_8011E048_w04;
extern Unk3 *D_8011E04C_w04;
extern Unk3 *D_8011E050_w04;

typedef struct {
    u8 b[4];
} W04Bytes4_q1;
extern W04Bytes4_q1 D_8011DDD0_w04;
s32 func_8011B350_w04(void);
s32 func_8011B6B4_w04(void);
extern s32 D_8011E054_w04;
extern s32 D_8011E058_w04;
void func_8010DA1C_w04(void);
void func_8010EE9C_w04(void);
void func_8010F264_w04(void);
void func_8010F2D0_w04(void);
void func_80117800_w04(void);
void func_801104DC_w04(void);
void func_80110768_w04(void);
void func_8010F7C4_w04(void);
void func_8010FD34_w04(void);
void func_80110080_w04(void);
void func_80116AFC_w04(void);
void func_8011737C_w04(void);
void func_80110BB8_w04(void);
void func_80110E78_w04(void);
void func_80111218_w04(void);
void func_80111C14_w04(void);
void func_8011276C_w04(void);
void func_80113484_w04(void);
void func_80114720_w04(void);
void func_80115720_w04(void);
void func_8011694C_w04(void);
void func_80117244_w04(void);
s32 func_8011AD48_w04(void);
void func_80116640_w04(void);
void func_80107D70_w04(void);
void func_80107F3C_w04(void);
void func_80108200_w04(void);
void func_801083D4_w04(void);
void func_80108644_w04(void);
void func_801086C4_w04(void);
void func_8010886C_w04(void);
void func_80107828_w04(void);
extern Object *D_8011DFF0_w04;
extern Process *D_8011E018_w04[];
extern s16 D_8011B7E4_w04[][2];
extern s16 D_8011B82C_w04[];
extern s16 D_8011B83C_w04[];
extern Object *D_8011E05C_w04;
extern Object *D_8011E060_w04[];
extern Object *D_8011E064_w04;
extern Object *D_8011E068_w04[];
extern s16 D_8011B804_w04[][2];
extern s16 D_8011B84C_w04[];
extern s16 D_8011B850_w04[];
extern Vec D_8011B854_w04[];
extern Vec D_8011B890_w04[];
extern Object *D_8011E090_w04;
extern Object *D_8011E094_w04[];
extern s16 D_8011B8CC_w04[];
extern s16 D_8011B8D0_w04[];
extern u32 *D_8011B90C_w04[];
extern s16 D_8011B824_w04[][2];
extern s16 D_8011B81C_w04[][2];
extern s32 D_8011B924_w04[];
extern s32 D_8011B948_w04[];
extern s32 D_8011B96C_w04[];
extern s32 D_8011B990_w04[];
extern s16 D_8011B9B4_w04[];
extern s16 D_8011B80C_w04[][2];
extern s16 D_8011B814_w04[][2];
extern s16 D_8011B9B8_w04[];
extern s16 D_8011B9BC_w04[];
extern s16 D_8011B9C4_w04[];
extern Object *D_8011E09C_w04[];
extern s16 D_8011B7CC_w04[];
extern s16 D_8011B7D0_w04[];
extern event_table_entry D_8011C77C_w04[];
extern event_table_entry D_8011C7F4_w04[];
extern event_table_entry D_8011C988_w04[];
extern event_table_entry D_8011C9C0_w04[];
void func_8011A858_w04(void);
extern Object *D_8011E03C_w04;

typedef s16 Q1SpaceTriple[3];
typedef BranchLink Q1BranchPair[2];
void func_80116024_w04(Q1SpaceTriple *masu, Q1BranchPair *links, DecisionTreeNonLeafNode **trees);
extern Q1SpaceTriple D_8011BFB8_w04[];
extern Q1BranchPair D_8011BFCC_w04[];
extern DecisionTreeNonLeafNode *D_8011BA08_w04[];
extern Q1SpaceTriple D_8011C000_w04[];
extern Q1BranchPair D_8011C014_w04[];
extern DecisionTreeNonLeafNode *D_8011BA68_w04[];
extern Q1SpaceTriple D_8011C048_w04[];
extern Q1BranchPair D_8011C05C_w04[];
extern DecisionTreeNonLeafNode *D_8011BAEC_w04[];
extern Q1SpaceTriple D_8011C090_w04[];
extern Q1BranchPair D_8011C0A4_w04[];
extern DecisionTreeNonLeafNode *D_8011BB40_w04[];
extern Q1SpaceTriple D_8011C0D8_w04[];
extern Q1BranchPair D_8011C0EC_w04[];
extern DecisionTreeNonLeafNode *D_8011BBAC_w04[];
extern Q1SpaceTriple D_8011C120_w04[];
extern Q1BranchPair D_8011C134_w04[];
extern DecisionTreeNonLeafNode *D_8011BC24_w04[];
extern Q1SpaceTriple D_8011C168_w04[];
extern Q1BranchPair D_8011C17C_w04[];
extern DecisionTreeNonLeafNode *D_8011BC84_w04[];
extern Q1SpaceTriple D_8011C1B0_w04[];
extern Q1BranchPair D_8011C1C4_w04[];
extern DecisionTreeNonLeafNode *D_8011BCF0_w04[];
extern Q1SpaceTriple D_8011C1F8_w04[];
extern Q1BranchPair D_8011C20C_w04[];
extern DecisionTreeNonLeafNode *D_8011BD38_w04[];
extern Q1SpaceTriple D_8011C240_w04[];
extern Q1BranchPair D_8011C254_w04[];
extern DecisionTreeNonLeafNode *D_8011BD68_w04[];
extern Q1SpaceTriple D_8011C288_w04[];
extern Q1BranchPair D_8011C29C_w04[];
extern DecisionTreeNonLeafNode *D_8011BDE0_w04[];
extern Q1SpaceTriple D_8011C2D0_w04[];
extern Q1BranchPair D_8011C2E4_w04[];
extern DecisionTreeNonLeafNode *D_8011BE28_w04[];
extern Q1SpaceTriple D_8011C318_w04[];
extern Q1BranchPair D_8011C32C_w04[];
extern DecisionTreeNonLeafNode *D_8011BE88_w04[];
extern Q1SpaceTriple D_8011C360_w04[];
extern Q1BranchPair D_8011C374_w04[];
extern DecisionTreeNonLeafNode *D_8011BF0C_w04[];
extern s16 D_8011B740_w04[];
extern s16 D_8011B750_w04[];
extern s16 D_8011B760_w04[];
extern s16 D_8011B770_w04[];
extern s16 D_8011B780_w04[];
extern s8 D_8011C550_w04[][5][7];
extern s32 D_8011E0A8_w04;
extern s32 D_8011E0AC_w04;
extern u8 *D_8011E0B0_w04;
// end board q1

s16 func_801059D0_w04(void) {
    return D_8011B780_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void func_801059F8_w04(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < D_8011B750_w04[idx2]) {
                continue;
            }
            if (idx2 < D_8011B750_w04[idx1]) {
                continue;
            }
            {
                s32 temp = D_8011B740_w04[idx1];
                D_8011B740_w04[idx1] = D_8011B740_w04[idx2];
                D_8011B740_w04[idx2] = temp;
                temp = D_8011B750_w04[idx1];
                D_8011B750_w04[idx1] = D_8011B750_w04[idx2];
                D_8011B750_w04[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = D_8011B740_w04[i];
    }
}

void func_80105B00_w04(void) {
    GW_SYSTEM *loc;
    s32 last;
    s32 first;

    loc = &GwSystem;
    loc->current_star_spawn++;
    if (loc->current_star_spawn >= 8) {
        last = loc->star_spawn_indices[7];
        loc->current_star_spawn = 0;
        GWBoardFlagSet(4);
        func_801059F8_w04();
        first = loc->star_spawn_indices[0];
        if ((last ^ first) == 0) {
            loc->star_spawn_indices[0] = loc->star_spawn_indices[7];
            loc->star_spawn_indices[7] = first;
        }
    }
}

void func_80105B8C_w04(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(D_8011B760_w04[i]);
    }
    MBMasuTypeSet(D_8011B770_w04[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(D_8011B760_w04[loc->star_spawn_indices[loc->current_star_spawn]]);
}

s32 func_80105C30_w04(s16 arg0) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        if (arg0 == D_8011B770_w04[i]) {
            if (i == loc->star_spawn_indices[loc->current_star_spawn]) {
                loc->unk_0E = D_8011B760_w04[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

void func_80105CA4_w04(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    D_8011E03C_w04 = MBModelCreate(0x3A, NULL);
    model = D_8011E03C_w04;
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
    D_8011E038_w04 = NULL;
    omDelPrcObj(NULL);
}

void func_80106094_w04(omObjData **arg) {
    omObjData *s0 = *arg;

    s0->scale.y = 4.0f;
    s0->scale.z = -0.6f;
    HuPrcSleep(3);
    while (s0->scale.z != 0.0f) {
        HuPrcVSleep();
    }
}

void func_80106120_w04(void) {
    struct UnkMBGuideData *data;
    GW_SYSTEM *loc = &GwSystem;
    SpaceData *space;
    s32 idx;

    D_800A12D4_main = 0;
    data = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(data->obj, 2, 0xF, D_8011B790_w04[0]);
    func_800FFF44_shared_board();
    MBModelDispOff(D_8011DFF8_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_800E6FCC_shared_board();
    func_800E9730_shared_board(3.0f);
    func_80106094_w04((omObjData **)data);
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
        space = MBMasuGet(D_8011B780_w04[loc->star_spawn_indices[loc->current_star_spawn]]);
    }
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    idx = MBRand(7.0f);
    MBGuideFaceSet(data->obj, D_8011B790_w04[idx]);
    MBMotionSet(data->obj, -1, 2);
    if (loc->current_board_index != 2) {
        Process *prc = omAddPrcObj(func_80105CA4_w04, 0x4800, 0, 0);
        D_8011E038_w04 = prc;
        prc->user_data = space;
        HuPrcSleep(30);
    } else {
        D_8011E038_w04 = NULL;
    }
    func_8005B43C_main(data->amount, D_8011B7AC_w04[idx], -1, -1);
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
    func_80046558_main(D_8011E03C_w04->omObj1->model[0]);
    MBModelKill(D_8011E03C_w04);
    MBModelDispOn(D_8011DFF8_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBGuideKill(data);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void func_801064DC_w04(void) {
    Object *playerModel = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    Object *model;
    Vec camPos;
    f32 scale;
    f32 angle;
    s32 obj;
    s32 i;

    HuAudFXPlay(0x11B);
    model = MBModelCreate(0x1A, NULL);
    model->flags |= 4;
    func_800ECC54_shared_board(model);
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x8D) {
        HuVecCopyXYZ(&model->coords, playerModel->coords.x, playerModel->coords.y + 10.0f, playerModel->coords.z);
        HuVecCopyXYZ(&camPos, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        model->velocity.x = 15.0f;
    } else {
        HuVecCopyXYZ(&model->coords, playerModel->coords.x, playerModel->coords.y + 10.0f, playerModel->coords.z + 30.0f);
        HuVecCopyXYZ(&camPos, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        model->velocity.x = 35.0f;
    }

    obj = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(obj, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(obj, 15.0f);
    func_8001C8A8_main(obj, 1);
    func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);

    scale = 0.0f;
    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale += 0.5f;
        func_8000D018_main(obj, scale * 15.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale -= 0.4f;
        func_8000D018_main(obj, scale * 15.0f);
        HuPrcVSleep();
    }

    func_8000D018_main(obj, scale * 15.0f);
    HuPrcSleep(20);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    HuVecCopyXYZ(&camPos, player->player_obj->coords.x, player->player_obj->coords.y - 10.0f, player->player_obj->coords.z);
    MBPlayerPosMoveCreate(&model->coords, &camPos, &model->coords, 40);

    for (i = 0; i < 40; i++) {
        func_8008A2A0_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        scale -= 0.05f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8000D018_main(obj, scale * 15.0f);
        func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
        HuPrcVSleep();
    }

    MBModelKill(model);
    func_8000D044_main(obj);
    MBVecForwardSet(&player->player_obj->rot);
    MBPlayerVibrate(-1, 5);
    if (D_8011B7C8_w04 != 0) {
        func_8004A670_main(0xE);
    } else {
        HuAudSeqPlay(0x6F);
    }

    GwPlayer[GwSystem.current_player_index].star += 1;
    if (GwPlayer[GwSystem.current_player_index].star >= 100) {
        GwPlayer[GwSystem.current_player_index].star = 99;
    }

    MBPlayerMotionSet(-1, 6, 0);
    func_8004ACE0_main(0x262, GwSystem.current_player_index);
    if (D_8011B7C8_w04 != 0) {
        HuPrcSleep(16);
        func_80003A70_main(D_800CDBC8_main);
        func_8004A918_main(0x6F);
        func_8004A880_main(0);
        HuPrcSleep(110);
        func_80003B70_main(D_800CDBC8_main, 0);
        func_8004A72C_main(0xF);
    } else {
        HuPrcSleep(60);
    }
    omDelPrcObj(NULL);
}

void func_80106A3C_w04(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801064DC_w04, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

void func_80106AB0_w04(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80106B38_w04(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void func_80106B94_w04(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_8011E040_w04 = func_800E210C_shared_board(0, 0x92, 1);
    D_8011E044_w04 = func_800E210C_shared_board(1, 0xA0, 1);
    D_8011E050_w04 = func_800E210C_shared_board(0xD, 0xAE, 1);
    D_8011E048_w04 = func_800E210C_shared_board(3, 0xBC, 1);
    D_8011E04C_w04 = func_800E210C_shared_board(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80106C64_w04(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011E040_w04);
    MBHelpWinKill(D_8011E044_w04);
    MBHelpWinKill(D_8011E050_w04);
    MBHelpWinKill(D_8011E048_w04);
    MBHelpWinKill(D_8011E04C_w04);
}

s32 func_80106CC4_w04(u8 *enabled) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                comCount = func_8011B350_w04();
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
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
        if (enabled[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    while (TRUE) {
        i = func_8005E1D8_main(mbDlgWinId, i, 0);
        if (i == -1) {
            return -1;
        }
        if (enabled[i] != 0) {
            return i;
        }
    }
}

void func_80106F58_w04(void) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                comCount = func_8011B6B4_w04();
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
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

void func_80107170_w04(void) {
    s32 cur = GwSystem.current_player_index;
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i != cur && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i != MB_MAX_PLAYERS && GwPlayer[cur].coin >= 50 && MBRand(100.0f) < GwPlayer[cur].coin + 10) {
        D_8011E054_w04 = 1;
        if (GwPlayer[cur].star < 99) {
            return;
        }
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i != cur && GwPlayer[i].coin >= 5) {
            break;
        }
    }
    if (i != MB_MAX_PLAYERS) {
        D_8011E054_w04 = 0;
    } else {
        D_8011E054_w04 = 2;
    }
}

void func_801072A0_w04(void) {
    s32 order[MB_MAX_PLAYERS];
    s32 cur = GwSystem.current_player_index;
    s32 i;
    s32 rank;
    s32 player;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        order[i] = -1;
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        rank = MBPlayerStealRankGet(i);
        while (TRUE) {
            if (order[rank] == -1) {
                break;
            }
            rank++;
        }
        order[rank] = i;
    }
    func_80107170_w04();
    if (D_8011E054_w04 == 1) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            player = order[i];
            if (player != cur && GwPlayer[player].star != 0) {
                D_8011E058_w04 = player;
                break;
            }
        }
    } else if (D_8011E054_w04 == 0) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            player = order[i];
            if (player != cur && GwPlayer[player].coin >= 5) {
                D_8011E058_w04 = player;
                break;
            }
        }
    }
    if (i == MB_MAX_PLAYERS) {
        D_8011E054_w04 = 2;
    }
}

s32 func_80107438_w04(u8 *enabled, s32 targetSet, s32 canCancel) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (targetSet == 0) {
                    func_801072A0_w04();
                    comCount = D_8011E054_w04 + 1;
                } else {
                    comCount = D_8011E058_w04 + 1;
                }
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
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
        if (enabled[i] == 0) {
            func_8006010C_main(mbDlgWinId, i);
        }
    }

    i = 0;
    while (TRUE) {
        i = func_8005E1D8_main(mbDlgWinId, i, canCancel);
        if (canCancel == 0) {
            if (i == -1) {
                return -1;
            }
        }
        if (enabled[i] != 0) {
            return i;
        }
    }
}

s32 func_80107704_w04(u8 *enabled) {
    return func_80107438_w04(enabled, 0, 1);
}

s32 func_80107724_w04(u8 *enabled) {
    return func_80107438_w04(enabled, 1, 0);
}

void func_80107744_w04(void) {
    GwSystem.current_board_index = 3;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

void func_80107780_w04(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    func_801059F8_w04();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[0] = 1;
    GwSystem.boardData.halfWordBytes[1] = 1;
    GwSystem.boardData.halfWordBytes[2] = 1;
    GwSystem.boardData.halfWordBytes[3] = 0;
    GwSystem.boardData.halfWordBytes[4] = 0;
    omOvlReturnEx(1);
}

void func_80107828_w04(void) {
    Vec sp10;
    SpaceData *space;
    s32 i;

    omInitObjMan(0xA0, 0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(0xC, 0x23D, 0xE, 0);
    MBMasuBlockTblExtSet(D_8011B7CC_w04);
    MBMasuBlockTblSet(D_8011B7D0_w04);
    space = MBMasuGet(0x71);
    MBVecDirGet(&space->coords, &MBMasuGet(0x75)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    space = MBMasuGet(0x8C);
    MBVecDirGet(&space->coords, &MBMasuGet(0x76)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBItemHookSet(0, &func_8010DA1C_w04);
    MBItemHookSet(1, &func_8010EE9C_w04);
    MBItemHookSet(9, &func_8010F264_w04);
    MBItemHookSet(2, &func_8010F2D0_w04);
    MBItemHookSet(3, &func_80117800_w04);
    MBItemHookSet(4, &func_801104DC_w04);
    MBItemHookSet(5, &func_80110768_w04);
    MBItemHookSet(6, &func_8010F7C4_w04);
    MBItemHookSet(7, &func_8010FD34_w04);
    MBItemHookSet(8, &func_80110080_w04);
    MBItemHookSet(0xA, &func_80116AFC_w04);
    MBItemHookSet(0xB, &func_8011737C_w04);
    MBItemHookSet(0xE, &func_80110BB8_w04);
    MBItemHookSet(0xF, &func_80110E78_w04);
    MBItemHookSet(0x10, &func_80111218_w04);
    MBItemHookSet(0x11, &func_80111C14_w04);
    MBItemHookSet(0x12, &func_8011276C_w04);
    MBItemHookSet(0x13, &func_80113484_w04);
    MBItemHookSet(0x14, &func_80114720_w04);
    MBItemHookSet(0x15, &func_80115720_w04);
    MBItemHookSet(0xC, &func_8011694C_w04);
    MBItemHookSet(0xD, &func_80117244_w04);
    MBComItemDecideHookSet(func_8011AD48_w04);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, D_8011B780_w04[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        func_80105B00_w04();
    }

    func_80105B8C_w04();
    func_80107D70_w04();
    func_80107F3C_w04();
    func_80108200_w04();
    func_801083D4_w04();
    func_80108644_w04();
    func_801086C4_w04();
    func_8010886C_w04();
    func_80116640_w04();
    func_800EBDAC_shared_board();
}

void func_80107B34_w04(void) {
    HuAudSeqPlay(0x1B);
    D_800CE198_main = 0x1B;
    func_800F8D6C_shared_board(0x1B);
    Hu3DCamInit(2);
    func_80107828_w04();
    MBMasuEventTblAdd(D_8011C77C_w04);
    MBMasuEventTblAdd(D_8011C9C0_w04);
    MBHatenaFuncSet(&func_8011A858_w04);
    MBMasuEventTblAdd(D_8011C7F4_w04);
    MBMasuEventTblAdd(D_8011C988_w04);
    MBStart(0);
}

void func_80107BB8_w04(void) {
    Hu3DCamInit(1);
    func_80107828_w04();
    MBStart(1);
}

void func_80107BE4_w04(s16 arg0) {
    Object *obj;

    if (D_8011DFF8_w04[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_800461B4_main(obj->omObj1->model[0]);
    if (D_8011DFF0_w04 == NULL) {
        D_8011DFF0_w04 = obj;
    }
    D_8011DFF8_w04[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_8011E018_w04[arg0] = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B82C_w04[arg0])->coords);
    func_800D771C_shared_board(0xB, obj, D_8011B7E4_w04[arg0][0], D_8011B7E4_w04[arg0][1]);
}

void func_80107D0C_w04(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        Process *prc = D_8011E018_w04[i];

        if (prc != NULL) {
            omDelPrcObj(prc);
            D_8011E018_w04[i] = NULL;
        }
    }
}

void func_80107D70_w04(void) {
    s32 i;

    D_8011DFF0_w04 = 0;
    for (i = 0; i < 8; i++) {
        D_8011DFF8_w04[i] = 0;
        D_8011E018_w04[i] = NULL;
        MBKinokoEffKillHookSet(func_80107D0C_w04);
        if (!GWBoardFlagCheck(D_8011B83C_w04[i])) {
            func_80107BE4_w04(i);
        }
    }
}

void func_80107E1C_w04(s16 arg0) {
    Object *obj;

    if (D_8011E060_w04[arg0] != NULL) {
        return;
    }
    if (D_8011E05C_w04 == NULL) {
        obj = MBModelCreate(0xA, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_8011E05C_w04 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011E05C_w04);
    }
    MBModelDispOff(obj);
    D_8011E060_w04[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B84C_w04[arg0])->coords);
    func_800D771C_shared_board(0xA, obj, D_8011B804_w04[arg0][0], D_8011B804_w04[arg0][1]);
}

void func_80107F3C_w04(void) {
    s32 i;

    D_8011E05C_w04 = 0;
    for (i = 0; i <= 0; i++) {
        D_8011E060_w04[i] = NULL;
        func_80107E1C_w04(i);
    }
}

void func_80107F98_w04(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(D_8011E068_w04[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(D_8011E068_w04[i * 5 + j]);
        }
    }
}

void func_80108094_w04(s16 arg0) {
    Object *obj;

    if (D_8011E068_w04[arg0] != NULL) {
        return;
    }
    if (D_8011E064_w04 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_8011E064_w04 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011E064_w04);
    }
    D_8011E068_w04[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B850_w04[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &D_8011B854_w04[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = D_8011B890_w04[arg0 % 5].x;
    obj->omObj1->rot.z = D_8011B890_w04[arg0 % 5].z;
    MBModelDispOff(obj);
}

void func_80108200_w04(void) {
    s32 i;

    D_8011E064_w04 = 0;
    for (i = 0; i < 0xA; i++) {
        D_8011E068_w04[i] = NULL;
        func_80108094_w04(i);
    }
    func_80107F98_w04();
}

void func_80108268_w04(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (D_8011E094_w04[arg0] != NULL) {
        return;
    }
    if (D_8011E090_w04 == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(D_8011B8D0_w04[board], D_8011B90C_w04[board]);
        MBModelTempAllocFree(obj);
        D_8011E090_w04 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011E090_w04);
    }
    D_8011E094_w04[arg0] = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B8CC_w04[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(D_8011B824_w04[arg0][0]);
        SpaceData *masuB = MBMasuGet(D_8011B824_w04[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    func_800D771C_shared_board(0xC, obj, D_8011B81C_w04[arg0][0], D_8011B81C_w04[arg0][1]);
}

void func_801083D4_w04(void) {
    s32 i;

    D_8011E090_w04 = 0;
    for (i = 0; i < 2; i++) {
        D_8011E094_w04[i] = NULL;
        func_80108268_w04(i);
    }
}

void func_80108434_w04(void) {
    HuPrcSleep(D_8011B96C_w04[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011B948_w04[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void func_80108490_w04(s32 arg0, s32 arg1) {
    MBMotionSet(D_8011E094_w04[arg0], arg1 - 1, 0);
    func_8001C814_main(D_8011E094_w04[arg0]->omObj1->model[0], 5, 0);
    if (D_8011B924_w04[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011B924_w04[GwSystem.current_board_index]);
    }

    if (D_8011B948_w04[GwSystem.current_board_index] != -1) {
        omAddPrcObj(func_80108434_w04, 0x1000, 0, 0);
    }
}

void func_80108558_w04(void) {
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
    func_8001C814_main(D_8011E094_w04[index]->omObj1->model[0], 1, 4);

    if (D_8011B990_w04[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011B990_w04[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void func_80108608_w04(s32 arg) {
    Process *temp = omAddPrcObj(func_80108558_w04, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void func_80108644_w04(void) {
    s32 i;

    D_8011E090_w04 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011B9B4_w04[i])->coords,
                                         D_8011B80C_w04[i][0], D_8011B80C_w04[i][1]);
    }
}

void func_801086C4_w04(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011B9B8_w04[i])->coords,
                                         D_8011B814_w04[i][0], D_8011B814_w04[i][1]);
    }
}

void func_8010873C_w04(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (GwSystem.boardData.halfWordBytes[D_8011B9C4_w04[i]] == 0) {
            D_8011E09C_w04[i]->rot.x = 0.0f;
            D_8011E09C_w04[i]->rot.z = -1.0f;
        } else {
            D_8011E09C_w04[i]->rot.x = 0.0f;
            D_8011E09C_w04[i]->rot.z = 1.0f;
        }
    }
}

void func_801087CC_w04(s32 arg0) {
    Object *obj;

    if (D_8011E09C_w04[arg0] != NULL) {
        return;
    }
    obj = MBModelFileCreate(0x130177, 0, 3.0f, 0, 0);
    MBModelTempAllocFree(obj);
    D_8011E09C_w04[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B9BC_w04[arg0])->coords);
}

void func_8010886C_w04(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_8011E09C_w04[i] = NULL;
        func_801087CC_w04(i);
    }
    func_8010873C_w04();
}

void func_801088C8_w04(void) {
    MBMoveNextMasuSet(CUR_PLAYER, 1, 0x15);
    MBMoveBackMasuSet(CUR_PLAYER, 1, 0x15);
}

void func_801088FC_w04(void) {
    func_80116024_w04(D_8011BFB8_w04, D_8011BFCC_w04, D_8011BA08_w04);
    omDelPrcObj(NULL);
}

void func_80108934_w04(void) {
    if (MBPlayerGet(CUR_PLAYER)->rev & 0x80) {
        func_80116024_w04(D_8011C000_w04, D_8011C014_w04, D_8011BA68_w04);
    } else {
        if (GwSystem.boardData.halfWordBytes[0] == 0) {
            MBMoveNextMasuSet(CUR_PLAYER, 4, 0);
        } else {
            MBMoveNextMasuSet(CUR_PLAYER, 9, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_801089B0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5C && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(CUR_PLAYER, 6, 0);
        player->rev &= ~1;
    } else {
        func_80116024_w04(D_8011C048_w04, D_8011C05C_w04, D_8011BAEC_w04);
    }
}

void func_80108A58_w04(void) {
    if (MBPlayerGet(CUR_PLAYER)->rev & 0x80) {
        func_80116024_w04(D_8011C090_w04, D_8011C0A4_w04, D_8011BB40_w04);
    } else {
        if (GwSystem.boardData.halfWordBytes[1] == 0) {
            MBMoveNextMasuSet(CUR_PLAYER, 7, 0);
        } else {
            MBMoveNextMasuSet(CUR_PLAYER, 8, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_80108AD4_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (GwSystem.boardData.halfWordBytes[4] != 0) {
        MBMoveNextMasuSet(CUR_PLAYER, 9, 5);
        player->rev |= 1;
    } else {
        func_80116024_w04(D_8011C0D8_w04, D_8011C0EC_w04, D_8011BBAC_w04);
    }
    omDelPrcObj(NULL);
}

void func_80108B4C_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (GwSystem.boardData.halfWordBytes[4] != 0) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xB, 3);
        player->rev |= 1;
    } else if (player->rev & 0x80) {
        func_80116024_w04(D_8011C120_w04, D_8011C134_w04, D_8011BC24_w04);
    } else {
        if (GwSystem.boardData.halfWordBytes[2] == 0) {
            MBMoveNextMasuSet(CUR_PLAYER, 0xC, 0);
        } else {
            MBMoveNextMasuSet(CUR_PLAYER, 0xD, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_80108C00_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x39 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(CUR_PLAYER, 1, 0);
        player->rev &= ~1;
    } else {
        func_80116024_w04(D_8011C168_w04, D_8011C17C_w04, D_8011BC84_w04);
    }
}

void func_80108CA8_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C1B0_w04, D_8011C1C4_w04, D_8011BCF0_w04);
    }
}

void func_80108D00_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C1F8_w04, D_8011C20C_w04, D_8011BD38_w04);
    }
}

void func_80108D58_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C240_w04, D_8011C254_w04, D_8011BD68_w04);
    }
}

void func_80108DB0_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C288_w04, D_8011C29C_w04, D_8011BDE0_w04);
    }
}

void func_80108E08_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C2D0_w04, D_8011C2E4_w04, D_8011BE28_w04);
    }
}

void func_80108E60_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C318_w04, D_8011C32C_w04, D_8011BE88_w04);
    }
}

void func_80108EB8_w04(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80116024_w04(D_8011C360_w04, D_8011C374_w04, D_8011BF0C_w04);
    }
}

void func_80108F10_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x28) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xD, 0xB);
    }
}

void func_80108F70_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x5B) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0x19);
    }
}

void func_80108FD0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x41) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0x19);
    }
}

void func_80109030_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x57) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0x12);
    }
}

void func_80109090_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x51) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x2, 0x7);
    }
}

void func_801090F0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x70) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x4, 0x4);
    }
}

void func_80109150_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xC) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x4, 0x4);
    }
}

void func_801091B0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x9) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x6, 0x2);
    }
}

void func_80109210_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x9) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0xE);
    }
}

void func_80109270_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xE) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x6, 0x2);
    }
}

void func_801092D0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x10) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xC, 0x7);
    }
}

void func_80109330_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4D) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x2, 0x7);
    }
}

void func_80109390_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x42) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x9, 0x6);
    }
}

void func_801093F0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x58) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x2, 0x4);
    }
}

void func_80109450_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3D) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x9, 0x6);
    }
}

void func_801094B0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x19) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xB, 0x4);
    }
}

void func_80109510_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x37) {
        MBMoveNextMasuSet(CUR_PLAYER, 0x1, 0x5);
    }
}

void func_80109570_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x1C) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xB, 0x4);
    }
}

void func_801095D0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3A) {
        MBMoveNextMasuSet(CUR_PLAYER, 0xD, 0xB);
    }
}

void func_80109630_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x66) {
        MBMoveBackMasuSet(CUR_PLAYER, 0x1, 0x14);
    }
}

s32 func_80109690_w04(s32 arg0) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                comCount = 1;
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 0x10);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return func_8005E1D8_main(mbDlgWinId, 0, 1);
}

void func_801098A0_w04(void) {
    GW_SYSTEM *loc;
    GW_PLAYER *player;
    s32 flag;
    s32 choice;
    void *prc;
    s16 sp18;
    s16 masuId;

    loc = &GwSystem;
    player = MBPlayerGet(GwSystem.current_player_index);
    flag = 1;

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x6F) {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x6A) {
            if (MBItemFind(GwSystem.current_player_index, 1) != -1) {
                func_800DBEC0_shared_board(GwSystem.current_player_index);
                MBPlayerMotionSet(-1, -1, 2);
                sp18 = MBMasuLinkMasuIdGet(player->clink, player->cidx);
                switch (sp18) {
                    case 0x70:
                    case 0x88:
                        func_800ED20C_shared_board(-1, 8, 0x6F);
                        break;
                    default:
                        func_800ED20C_shared_board(-1, 8, 0x6A);
                        break;
                }
                HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
                HuPrcChildWait();
                MBPlayerVibrate(-1, 1);

                while (1) {
                    MBDlgWinCreate(0x38, 0x4103);
                    choice = func_80109690_w04(0);
                    MBDlgWinClose();
                    MBDlgWinKill();

                    switch (choice) {
                        case 0:
                            MBDlgWinExec(0x38, 0x4104);
                            GwPlayer[loc->current_player_index].itemNo[MBItemFind(loc->current_player_index, 1)] = -1;
                            MBItemRemoveEmpty(GwSystem.current_player_index);
                            MBStatusItemIconSprReinit(-1);
                            sp18 = MBMasuLinkMasuIdGet(player->clink, player->cidx);
                            switch (sp18) {
                                case 0x70:
                                    func_80108490_w04(0, 0);
                                    break;
                                case 0x88:
                                    func_80108490_w04(0, 1);
                                    break;
                                case 0x69:
                                    func_80108490_w04(1, 0);
                                    break;
                                default:
                                    func_80108490_w04(1, 1);
                                    break;
                            }
                            flag = 0;
                            prc = MBPlayerVibrateObjCreate(-1, 2, 5);
                            HuPrcSleep(0x14);
                            MBPlayerVibrateObjKill(prc);
                            break;
                        case 1:
                            MBDlgWinExec(0x38, 0x4105);
                            break;
                        case 2:
                            func_80106AB0_w04();
                            continue;
                        default:
                            break;
                    }
                    break;
                }

                func_800DB884_shared_board(loc->current_player_index);
                HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
                HuPrcChildWait();
            } else {
                MBDlgWinExec(-1, 0x4106);
            }
        }
    }

    if (flag != 0) {
        masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        switch (masuId) {
            case 0x70:
                MBMoveNextMasuSet(-1, 5, 0);
                player->rev |= 1;
                break;
            case 0x88:
                MBMoveNextMasuSet(-1, 3, 2);
                player->rev &= ~1;
                break;
            case 0x69:
                MBMoveNextMasuSet(-1, 0xE, 1);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 0xC, 2);
                player->rev &= ~1;
                break;
        }
    }

    omDelPrcObj(NULL);
}

void func_80109CBC_w04(void) {
}

void func_80109CC4_w04(void) {
}

void func_80109CCC_w04(void) {
}

s32 func_80109CD4_w04(DecisionTreeNonLeafNode *tree, s32 count) {
    s32 comCount = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W04Bytes4_q1 sp20;
    s32 i;
    s32 j;

    sp20 = D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                switch ((s32)tree) {
                    case 0:
                        comCount = func_800EF0D8_shared_board(0) + 1;
                        break;
                    case 1:
                        comCount = func_800EF0D8_shared_board(1) + 1;
                        break;
                    case 2:
                        comCount = count + 1;
                        break;
                    default:
                        comCount = MBComTreeExec(tree) + 1;
                        break;
                }
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                func_8005FE54_main(mbDlgWinId, sp20.b[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (comCount != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; comCount != 0; j++) {
            if (--comCount == 0) {
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

void func_80109F58_w04(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
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

void func_8010A014_w04(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

void func_8010A054_w04(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = func_80105C30_w04(spaceIdx);
    if (spaceIdx == 1) {
        func_800DBEC0_shared_board(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, func_801059D0_w04());
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
                choice = func_80109CD4_w04((DecisionTreeNonLeafNode *)2, 0);
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
                        func_80106A3C_w04(D_8011DFF0_w04);
                        HuPrcSleep(30);
                        func_800EDA58_shared_board();
                        func_800FF7F0_shared_board(2);
                        func_80109CC4_w04();
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
                        func_80109CC4_w04();
                        return;
                    case 2:
                        func_80106AB0_w04();
                        goto purchaseMenu;
                    default:
                        func_80109CC4_w04();
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

    func_80109CC4_w04();
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010A400_w04);

s32 func_8010AF34_w04(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011E0B0_w04[i] != 0) {
            if (D_8011C550_w04[D_8011E0A8_w04][D_8011E0AC_w04][i] == arg0) {
                return i;
            }
        }
    }
    return -1;
}

s32 func_8010AFBC_w04(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011C550_w04[D_8011E0A8_w04][D_8011E0AC_w04][i] == -1) {
            break;
        }
    }
    return i;
}

void func_8010B024_w04(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010B1FC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010C4B4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010C554_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010C5F4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010CA3C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010CA60_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010D88C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010D9E0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010DA1C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010EBF0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010EC0C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010EC28_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010ED84_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010EE9C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F264_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F2D0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F490_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F6F4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F7C4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F9F4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010FBC4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010FD34_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110080_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110244_w04);

INCLUDE_RODATA("asm/nonmatchings/overlays/w04/367960", D_8011DE40_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801104DC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110768_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801109A8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110BB8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110E78_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80111218_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80111C14_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011215C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112378_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011276C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112828_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011297C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801129B8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112B48_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112F04_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011319C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801132A8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80113484_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80114130_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801141F0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80114720_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011502C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80115164_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801152D4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011549C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80115720_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116024_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011621C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116294_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801162F8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801164A4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801165A4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116640_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116740_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011694C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116AAC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116AFC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117074_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117244_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011737C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117800_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117EA8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80118240_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011826C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801183D4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801191B8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80119FCC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011A4E0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011A5DC_w04);

INCLUDE_RODATA("asm/nonmatchings/overlays/w04/367960", D_8011DE80_w04);

// main func for reroll event in woody woods
void func_8011A858_w04(void) {
    GW_PLAYER *curPlayer;
    s16 curPlayerSpace;

    curPlayer = MBPlayerGet(CUR_PLAYER);
    curPlayerSpace = MBMasuLinkMasuIdGet(curPlayer->clink, curPlayer->cidx);
    HuPrcSleep(8);
    switch (curPlayerSpace) {
        // space IDs for reroll event
        case 0x3F:
        case 0x49:
        case 0x4A:
            func_801183D4_w04();
            break;
        case 0x1F:
        case 0x21:
        case 0x22:
            func_801191B8_w04();
            break;
        case 0x4F:
            func_8011A4E0_w04(0);
            break;
        case 0xC:
            func_8011A4E0_w04(1);
            break;
        case 0x3B:
            func_8011A4E0_w04(2);
            break;
    }
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011A91C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AA10_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AA64_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AB34_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AC0C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AC60_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AD48_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011B350_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011B6B4_w04);
