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
extern DecisionTreeNonLeafNode D_8011C508_w04[];
extern u32 D_8011C520_w04[];
extern const char D_8011DDD4_w04[];
void func_80112B48_w04(void);
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

void func_8010A400_w04(void) {
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
        case 0x3D:
            func_800ED20C_shared_board(-1, 8, 0x77);
            spaceA = MBMasuGet(0x77);
            spaceB = MBMasuGet(0x3D);
            break;
        case 6:
            func_800ED20C_shared_board(-1, 8, 0x6D);
            spaceA = MBMasuGet(0x6D);
            spaceB = MBMasuGet(6);
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

    effectModel = MBModelCreate(0x35, D_8011C520_w04);
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
        choice = func_80109CD4_w04(D_8011C508_w04, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                func_80106AB0_w04();
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
        sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins);
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
            func_80112B48_w04();
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
                sprintf(sp20, D_8011DDD4_w04, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, D_8011DDD4_w04, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                func_80107F98_w04();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                func_80107F98_w04();
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
                sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                func_80107F98_w04();
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
    func_80109CBC_w04();
}

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

// board q2: func_8010B1FC_w04..func_80110768_w04 (twins of w02 func_8010B1C8_w02..func_80110730_w02)
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/10C230.h"
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

typedef struct G3ModelFadeWork {
    /* 0x00 */ Vec vel;
    /* 0x0C */ f32 alpha;
    /* 0x10 */ f32 scaleRate;
    /* 0x14 */ f32 fadeRate;
    /* 0x18 */ Object *model;
    /* 0x1C */ u16 killOnFade;
} G3ModelFadeWork; // size 0x20

typedef struct G3ItemMoveWork {
    /* 0x00 */ s16 startX;
    /* 0x02 */ s16 startY;
    /* 0x04 */ s16 endX;
    /* 0x06 */ s16 endY;
    /* 0x08 */ s16 duration;
    /* 0x0A */ s16 spriteGroup;
} G3ItemMoveWork; // size 0xC (allocated as 0x10)

/* Spark directions copied into a local array before each loop (an initialised local in the
   original; the table sits in this unit's data, which is still asm). */
typedef struct G3SparkDirs {
    Vec dir[8];
} G3SparkDirs;

void func_800D9F5C_shared_board(Object *arg0, Vec *arg1, s32 arg2);
void func_8001ED54_main(s16 arg0);
extern s16 D_8011B770_w04[]; /* star spaces */
extern s32 D_8011B7C8_w04;
extern u8 D_8011C538_w04[2][3][4];
extern s8 D_8011C550_w04[][5][7];
extern u8 D_8011C598_w04[2][3][4];
extern s8 D_8011C5B0_w04[2][5][10];
extern u8 D_8011C614_w04[2][10];
extern s32 D_8011C628_w04[5][2];
extern s32 D_8011C650_w04[2];
extern s32 D_8011C658_w04[2];
extern s32 D_8011C660_w04[2];
extern s32 D_8011C668_w04[2];
extern s32 D_8011C670_w04[2];
extern u32 D_8011C678_w04[];
extern u32 D_8011C680_w04[];
extern s32 D_8011C688_w04;
extern Vec2f D_8011C69C_w04[4];
extern Vec2f D_8011C6BC_w04[4];
extern u8 D_8011C6DC_w04[6][3];
extern u8 D_8011C6F0_w04[14][3];
extern u8 D_8011C71C_w04[];
extern s32 D_8011C724_w04[];
extern s32 D_8011C730_w04[];
extern Vec2f D_8011C804_w04[];
extern Vec2f D_8011C824_w04[];
extern char D_8011DDD4_w04[];
extern const f64 D_8011DDD8_w04;
extern const G3SparkDirs D_8011DDE0_w04;
extern const f64 D_8011DE40_w04;
extern Object *D_8011E05C_w04;
extern Object *D_8011E060_w04[1];
extern s32 D_8011E0A8_w04;
extern s32 D_8011E0AC_w04;
extern u8 *D_8011E0B0_w04;
extern Object *D_8011E0B4_w04;
void func_80106A3C_w04(Object *arg);
void func_80106AB0_w04(void);
void func_80106B38_w04(void);
s32 func_80106CC4_w04(u8 *arg0);
s32 func_80106F58_w04(void);
s32 func_80107704_w04(u8 *choices);
s32 func_80107724_w04(u8 *choices);
void func_80108608_w04(s32 arg);
void func_80109CCC_w04(void);
void func_8010B024_w04(void);
void func_8010B1FC_w04(void);
void func_8010C4B4_w04(Object *obj);
void func_8010C554_w04(Object *obj);
s32 func_8010C5F4_w04(s32 playerIndex);
void func_8010CA3C_w04(void);
s32 func_8010CA60_w04(s32 playerIndex);
void func_8010D88C_w04(void);
void func_8010D9E0_w04(s32 arg);
void func_8010DA1C_w04(void);
void func_8010EBF0_w04(void);
void func_8010EC0C_w04(void);
omObjData *func_8010EC28_w04(Vec *pos, f32 scaleRate, f32 fadeRate, s16 killOnFade, Vec *vel, s32 star);
void func_8010ED84_w04(omObjData *obj);
void func_8010EE9C_w04(void);
void func_8010F264_w04(void);
void func_8010F2D0_w04(void);
void func_8010F490_w04(void);
Process *func_8010F6F4_w04(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration);
void func_8010F7C4_w04(void);
void func_8010F9F4_w04(void);
void func_8010FBC4_w04(void);
void func_8010FD34_w04(void);
void func_80110080_w04(void);
void func_80110244_w04(s32 arg0, s32 arg1, s32 arg2, f32* arg3, s32 arg4);
void func_801104DC_w04(void);
void func_80110768_w04(void);
void func_80112378_w04(void);

void func_8010B1FC_w04(void) {
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
        case 0x71:
            camMasu = 0x75;
            spaceA = MBMasuGet(0x75);
            spaceB = MBMasuGet(0x71);
            D_8011C688_w04 = 0;
            break;
        case 0x8C:
            camMasu = 0x76;
            spaceA = MBMasuGet(0x76);
            spaceB = MBMasuGet(0x8C);
            D_8011C688_w04 = 1;
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
            effectModel = MBModelCreate(0x39, D_8011C680_w04);
        } else {
            effectModel = MBModelCreate(0x1B, D_8011C678_w04);
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
        MBDlgWinExec(dlgWin, D_8011C668_w04[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, D_8011C660_w04[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, D_8011C658_w04[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, D_8011C650_w04[shopIdx]);
    choice = func_80106F58_w04();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = BoardGetTurnTier(-1);
            row = D_8011C538_w04[shopIdx][i][BoardPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (D_8011C550_w04[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_8011C550_w04[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (D_8011C550_w04[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_80100F94_shared_board[D_8011C550_w04[shopIdx][row][j]] >
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

            MBDlgWinInsertCreate(dlgWin, D_8011C628_w04[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            func_800ECAA8_shared_board(0);
            D_8011E0A8_w04 = slot;
            D_8011E0AC_w04 = row;
            D_8011E0B0_w04 = enabled;
            sel = func_80106CC4_w04(enabled);
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
            shopTable = D_8011C550_w04;
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
                    D_8011C550_w04[shopIdx][row][sel];
                item = D_8011C550_w04[shopIdx][row][sel];
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

            if (D_8011C550_w04[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = D_8011C598_w04[shopIdx][BoardGetTurnTier(-1)]
                                                [BoardPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < D_8011C5B0_w04[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = D_8011C614_w04[shopIdx][i];

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
                    prc = omAddPrcObj(func_8010B024_w04, 0x4002, 0, 0);
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
            MBDlgWinExec(dlgWin, D_8011C670_w04[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                func_80106B38_w04();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106AB0_w04();
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

void func_8010C4B4_w04(Object *obj) {
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

void func_8010C554_w04(Object *obj) {
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

s32 func_8010C5F4_w04(s32 playerIndex) {
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
    func_80054904_main(grp, 0, D_8011C69C_w04[playerIndex].x,
                        D_8011C69C_w04[playerIndex].y);
    func_80055458_main(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        func_80054904_main(grp, 0,
                            (i * D_8011C6BC_w04[playerIndex].x) +
                                D_8011C69C_w04[playerIndex].x,
                            (i * D_8011C6BC_w04[playerIndex].y) +
                                D_8011C69C_w04[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    func_80055458_main(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(func_80112378_w04, 0x4002, 0, 0);
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
                            (D_8011C6BC_w04[playerIndex].x * 16.0f) +
                                D_8011C69C_w04[playerIndex].x,
                            (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                                D_8011C69C_w04[playerIndex].y +
                                (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        func_80054904_main(grp, 0,
                            (i * D_8011C6BC_w04[playerIndex].x) +
                                D_8011C69C_w04[playerIndex].x,
                            (i * D_8011C6BC_w04[playerIndex].y) +
                                D_8011C69C_w04[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprKill(spriteId);
    return !hasRareItem;
}

void func_8010CA3C_w04(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

s32 func_8010CA60_w04(s32 playerIndex) {
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
    func_80054904_main(grp, 0, D_8011C69C_w04[playerIndex].x,
                        D_8011C69C_w04[playerIndex].y);
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
                            D_8011C69C_w04[playerIndex].x -
                                (D_8011C6BC_w04[playerIndex].x * 16.0f) - 8.0f,
                            D_8011C69C_w04[playerIndex].y +
                                (D_8011C6BC_w04[playerIndex].y * 16.0f));
        func_80055458_main(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            func_80054904_main(grp, 0,
                                (i * D_8011C6BC_w04[playerIndex].x) +
                                    D_8011C69C_w04[playerIndex].x,
                                (i * D_8011C6BC_w04[playerIndex].y) +
                                    D_8011C69C_w04[playerIndex].y);
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
            omAddPrcObj(func_8010CA3C_w04, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(func_80112378_w04, 0x4002, 0, 0);
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
                    (D_8011C6BC_w04[playerIndex].x * 16.0f) +
                        D_8011C69C_w04[playerIndex].x,
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                func_80054904_main(
                    grp, 0,
                    (D_8011C6BC_w04[playerIndex].x * 16.0f) +
                        D_8011C69C_w04[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y);
                func_80054904_main(
                    playerGrp, 0,
                    D_8011C69C_w04[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y);
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
                            playerGrp, 0, D_8011C69C_w04[playerIndex].x - 8.0f,
                            (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                                D_8011C69C_w04[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                func_80055140_main(playerGrp, 0, 0, 0);
                func_800550F4_main(playerGrp, 0, 1);
                playerSpriteVisible = 0;
                func_80054904_main(
                    playerGrp, 0,
                    D_8011C69C_w04[playerIndex].x -
                        (D_8011C6BC_w04[playerIndex].x * 16.0f) - 8.0f,
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(func_8010CA3C_w04, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011C6BC_w04[playerIndex].x) +
                                    D_8011C69C_w04[playerIndex].x,
                                (i * D_8011C6BC_w04[playerIndex].y) +
                                    D_8011C69C_w04[playerIndex].y);
            func_80055458_main(grp, 0, i << 4);
            func_80055458_main(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011C6BC_w04[playerIndex].x) +
                                    D_8011C69C_w04[playerIndex].x,
                                (i * D_8011C6BC_w04[playerIndex].y) +
                                    D_8011C69C_w04[playerIndex].y);
            func_80054904_main(playerGrp, 0,
                                ((i - 0x10) * D_8011C6BC_w04[playerIndex].x) +
                                    D_8011C69C_w04[playerIndex].x - 8.0f,
                                (i * D_8011C6BC_w04[playerIndex].y) +
                                    D_8011C69C_w04[playerIndex].y);
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
        for (i = 0; i < ARRAY_COUNTU(D_8011C6DC_w04); i++) {
            if ((GwSystem.current_turn >= D_8011C6DC_w04[i][0]) &&
                (GwSystem.current_turn <= D_8011C6DC_w04[i][1])) {
                break;
            }
        }
        playerSpriteVisible = D_8011C6DC_w04[i][2];
        for (i = 0; i < ARRAY_COUNTU(D_8011C6F0_w04); i++) {
            if ((attempts >= D_8011C6F0_w04[i][0]) &&
                (attempts <= D_8011C6F0_w04[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= D_8011C6F0_w04[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

void func_8010D88C_w04(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011E0B4_w04);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += D_8011DDD8_w04; // 1.5 (the literal sits in the .data asm file)
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void func_8010D9E0_w04(s32 arg) {
    Process *temp = omAddPrcObj(func_8010D88C_w04, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void func_8010DA1C_w04(void) {
    char inserts[4][16];
    u8 choices[8];
    Vec direction;
    s32 rankedPlayers[3];
    Object *model = NULL;
    SpaceData *space;
    Vec *spaceCoords;
    GW_PLAYER *player;
    GW_SYSTEM *sys;
    Process *process;
    void *coinEffect;
    s32 resultAmount;
    s32 selectedByCpu;
    s16 target;
    s32 menuResult;
    s32 playerChoice;
    s32 rank;
    s32 count;
    s32 i;
    s32 j;
    s32 amountDifference;
    s16 spaceId;
    f32 angle;
    f32 scale;
    f32 rate;
    f32 booVelocity;
    Object *boo;
    s32 modelIsLinked;
    s32 estimatedAmount;
    s16 camMasu;
    s16 menu;
    s32 cameraSet;

    resultAmount = 0;
    estimatedAmount = resultAmount;
    MBMasuCurGet();
    sys = &GwSystem;
    player = MBPlayerGet(-1);
    cameraSet = func_800DBEC0_shared_board(sys->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    menu = 0;
    spaceId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    if (spaceId != 0x8D) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(D_8011E05C_w04);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x7D;
        space = MBMasuGet(0x7D);
        boo = D_8011E060_w04[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (D_8011C730_w04[sys->current_board_index] != 0) {
            func_8001ED54_main(model->omObj1->model[0]);
        }
        func_8001C448_main(model->omObj1->model[0]);
        MBModelTempAllocFree(model);
        spaceCoords = &space->coords;
        HuVecSubtract(&direction, &MBMasuGet(spaceId)->coords, spaceCoords);
        MBVecNormalize(&direction);
        HuVecCopy3F(&model->rot, &direction);
        model->scale.y = 0.0f;
        HuVecCopy3F(&model->coords, spaceCoords);
        MBMotionSet(model, -1, 1);
        MBModelDispOn(model);
        scale = 1.0f / sindf(50.0f);
        for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (D_8011C730_w04[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    func_8010C4B4_w04(boo);
    space = MBMasuGet(spaceId);
    spaceId = camMasu;
    if (spaceId != -1) {
        func_800D9F5C_shared_board(boo, &space->coords, 5);
        func_800ED20C_shared_board(-1, 5, spaceId);
        HuPrcSleep(5);
        process = HuPrcCurrentGet();
        HuPrcChildLink(process, MBCameraZoomMotStart(1.6f));
        HuPrcChildWait();
    }

    if (GwPlayer[sys->current_player_index].coin < 5) {
        MBDlgWinExec(7, 0x6201);
        goto finishMenu;
    }

restartMenu:
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index &&
            (GwPlayer[i].coin != 0 || GwPlayer[i].star != 0)) {
            break;
        }
    }
    if (i >= 4) {
        MBDlgWinExec(7, 0x6202);
        goto finishMenu;
    }
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index && GwPlayer[i].coin != 0) {
            break;
        }
    }
    if (i == 4) {
        inserts[0][0] = 1;
        choices[0] = 0;
    } else {
        inserts[0][0] = 8;
        choices[0] = 1;
    }
    inserts[0][1] = 0;
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i == 4) {
        goto starChoiceUnavailable;
    }
    if (GwPlayer[sys->current_player_index].coin < 50) {
        goto starChoiceUnavailable;
    }
    if (GwPlayer[sys->current_player_index].star < 99) {
        goto starChoiceAvailable;
    }

starChoiceUnavailable: {
    inserts[1][0] = 1;
    choices[1] = 0;
    goto starChoiceDone;
}

starChoiceAvailable: {
    inserts[1][0] = 8;
    choices[1] = 1;
}

starChoiceDone:
    inserts[1][1] = 0;
    choices[3] = 1;
    choices[2] = 1;
    MBDlgWinInsertCreate(7, 0x6200, (s32)inserts[0], (s32)inserts[1], 0, 0, 0);
    menuResult = func_80107704_w04(choices);
    menu = menuResult;
    MBDlgWinClose();
    MBDlgWinKill();
    switch ((s16)menuResult) {
        case 0:
        case 1:
            goto selectPlayer;
        case 2:
            goto menuResultTwo;
        case 3:
            goto menuResultThree;
        default:
            goto finishMenu;
    }

selectPlayer:
    i = 0;
    j = 0;
    while (i < 4) {
        if (i == sys->current_player_index) {
            choices[j] = 0;
            inserts[j][0] = 1;
        } else if (menu == 0) {
            if (GwPlayer[i].coin == 0) {
                choices[j] = 0;
                inserts[j][0] = 1;
            } else {
                choices[j] = 1;
                inserts[j][0] = 8;
            }
        } else {
            if (GwPlayer[i].star == 0) {
                choices[j] = 0;
                inserts[j][0] = 1;
            } else {
                choices[j] = 1;
                inserts[j][0] = 8;
            }
        }
        func_800E2260_shared_board(i, &inserts[j][1]);
        i++;
        j++;
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(7, 0x5C02, (s32)inserts[0], (s32)inserts[1], (s32)inserts[2], (s32)inserts[3], 0);
    playerChoice = func_80107724_w04(choices);
    target = playerChoice;
    MBDlgWinClose();
    selectedByCpu = 0;
    MBDlgWinKill();
    switch ((s16)playerChoice) {
        case -1:
            goto restartMenu;
        case 4:
            goto selectCpuPlayer;
        case 5:
            if (modelIsLinked == -1) {
                func_80106B38_w04();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106AB0_w04();
            }
            goto selectPlayer;
        default:
            goto playerSelected;
    }

selectCpuPlayer: {
    i = 0;
    count = 0;
    while (i < 4) {
        for (j = 0; j < 4; j++) {
            if (i == BoardPlayerRankCalc(j) && sys->current_player_index != j) {
                rankedPlayers[count++] = j;
            }
        }
        i++;
    }
    rank = MBRand(100.0f);
    for (i = 0; i < 3; i++) {
        if (rank < D_8011C724_w04[i]) {
            break;
        }
    }
    if (menu != 0) {
        while (GwPlayer[rankedPlayers[i]].star == 0 || rankedPlayers[i] == sys->current_player_index) {
            i--;
        }
    } else {
        while (i >= 0 &&
               (GwPlayer[rankedPlayers[i]].coin == 0 || rankedPlayers[i] == sys->current_player_index)) {
            i--;
        }
        i = 2;
        while (i >= 0 &&
               (GwPlayer[rankedPlayers[i]].coin == 0 || rankedPlayers[i] == sys->current_player_index)) {
            i--;
        }
    }
    target = rankedPlayers[i];
    selectedByCpu = 1;
}

playerSelected:
    if (menu == 0) {
        MBCoinChangeCreate(sys->current_player_index, -5);
        MBCoinTakeCreate(sys->current_player_index, -5);
    } else {
        MBCoinChangeCreate(sys->current_player_index, -50);
        MBCoinTakeCreate(sys->current_player_index, -50);
    }
    HuPrcSleep(30);
    if (menu == 1) {
        if (selectedByCpu != 0) {
            MBDlgWinExec(7, 0x6206);
        }
    } else {
        for (i = 0; (u32)i < 6; i++) {
            if (GwSystem.current_turn >= D_8011C6DC_w04[i][0] &&
                GwSystem.current_turn <= D_8011C6DC_w04[i][1]) {
                break;
            }
        }
        estimatedAmount = D_8011C6DC_w04[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    func_8010C554_w04(boo);
    if (menu == 0) {
        resultAmount = func_8010CA60_w04(target);
        func_8010C4B4_w04(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], D_8011DDD4_w04, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], D_8011DDD4_w04, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= D_8011C71C_w04[i]) {
                        break;
                    }
                }
                MBDlgWinInsertCreate(7, i + 0x6210, (s32)inserts[0], 0, 0, 0, 0);
            }
            MBDlgWinClose();
            MBDlgWinKill();
        }
        if (resultAmount != -2) {
            mbItemBtnF = 0;
            rate = (f32)resultAmount / 90.0f;
            angle = 0.0f;
            D_8011E0B4_w04 = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(D_8011E0B4_w04);
            MBModelDispOff(D_8011E0B4_w04);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    func_8010D9E0_w04((s32)boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(D_8011E0B4_w04);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            func_8004ACE0_main(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = func_8010C5F4_w04(target);
        func_8010C4B4_w04(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            D_8011B7C8_w04 = 1;
            func_80106A3C_w04(boo);
            D_8011B7C8_w04 = 0;
            goto outcomeDone;
        } else {
            resultAmount = -2;
        }
    }

outcomeDone:
    if (modelIsLinked == -1) {
        HuPrcSleep(20);
        MBPlayerMotionSet(-1, -1, 2);
    }
    if (resultAmount == -2) {
        HuPrcSleep(30);
        MBDlgWinExec(7, 0x6215);
    }
    goto finishMenu;

menuResultTwo:
    func_8010C554_w04(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        func_80106B38_w04();
        D_800CB99C_main = 1;
        func_80049FB8_main();
    } else {
        func_80106AB0_w04();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        func_8010C554_w04(boo);
    }
    MBVecForwardSet(&boo->rot);
    if (modelIsLinked == -1) {
        MBModelKill(boo);
    }
    if (camMasu != -1) {
        HuAudFXPlay(0x126);
        MBMotionSet(model, -1, 4);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        func_8001C6A8_main(
            model->omObj1->model[0], D_800CCF58_main[HmfModelData[model->omObj1->model[0]].unk02].unk02);
        while (func_800D9E80_shared_board(model) == 0) {
            HuPrcVSleep();
        }
        scale = 1.0f / sindf(50.0f);
        for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 0.0f;
        model->scale.x = 0.0f;
        model->scale.z = 0.0f;
        MBModelKill(model);
    }
    if (cameraSet != 0) {
        func_800DB884_shared_board(sys->current_player_index);
    }
    if (modelIsLinked != -1) {
        process = HuPrcCurrentGet();
        HuPrcChildLink(process, MBCameraZoomMotStart(1.3f));
        HuPrcChildWait();
    }
    func_80109CCC_w04();
}

void func_8010EBF0_w04(void) {
    func_80108608_w04(0);
}

void func_8010EC0C_w04(void) {
    func_80108608_w04(1);
}

omObjData *func_8010EC28_w04(Vec *pos, f32 scaleRate, f32 fadeRate, s16 killOnFade, Vec *vel, s32 star) {
    omObjData *obj;
    G3ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, func_8010ED84_w04);
    data = obj->data = HuMemAllocTag(sizeof(G3ModelFadeWork), 0x7918);
    data->alpha = 255.0f;
    data->scaleRate = scaleRate;
    data->fadeRate = fadeRate;
    HuVecCopy3F(&data->vel, vel);
    if (star != 0) {
        model = MBModelFileCreate(0x1301F8, 0, 1.0f, 0, 0);
    } else {
        model = MBModelFileCreate(0x1301F7, 0, 1.0f, 0, 0);
    }
    Hu3DModelScaleSet(model->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    model->coords.x = pos->x;
    model->coords.y = pos->y;
    model->coords.z = pos->z;
    func_8001FA68_main(model->omObj1->model[0]);
    func_8001F9E4_main(model->omObj1->model[0], 0xFF);
    data->model = model;
    data->killOnFade = killOnFade;
    return obj;
}

void func_8010ED84_w04(omObjData *arg0) {
    G3ModelFadeWork *data = arg0->data;
    Object *model = data->model;
    f32 scale;
    f32 alpha;

    HuVecAdd(&model->coords, &model->coords, &data->vel);
    scale = model->scale.z + data->scaleRate;
    model->scale.z = scale;
    model->scale.y = scale;
    model->scale.x = scale;
    alpha = data->alpha - data->fadeRate;
    data->alpha = alpha;
    if (alpha < 0.0f) {
        data->alpha = 0.0f;
        if (data->killOnFade != 0) {
            MBModelKill(data->model);
            omDelObj(arg0);
            return;
        }
        omSetStatBit(arg0, 8);
    }
    func_8001F9E4_main(model->omObj1->model[0], (u8)data->alpha);
}

void func_8010EE9C_w04(void) {
    Vec pos;
    s8 link;
    s8 index;
    GW_PLAYER *player;
    Object *lamp;
    UnkVibrateProcess *vib;
    s32 angle;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);
    func_8010F9F4_w04();
    lamp = MBModelCreate(0x24, NULL);
    Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&lamp->coords, &player->player_obj->coords);
    for (lamp->coords.y = 100.0f; lamp->coords.y > 30.0f;) {
        lamp->coords.y -= 1.0f;
        HuPrcVSleep();
    }

    HuAudFXPlay(0x127);
    func_8004A7C4_main(0xB4);
    vib = MBPlayerVibrateObjCreate(CUR_PLAYER, 4, 5);

    angle = 0xB4;
    i = 0;
    while (angle < 0x438) {
        G3SparkDirs particleDir = D_8011DDE0_w04;

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1, &particleDir.dir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    func_800EB24C_shared_board(
        D_8011B770_w04[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
    player->clink = link;
    player->cidx = index;
    player->nlink = link;
    player->nidx = index + 1;
    player->blink = link;
    player->bidx = index - 1;
    player->rev &= ~FLAG_REV;
    func_800FC9E0_shared_board();
    HuAudFXPlay(0x128);
    func_8004A0E0_main();

    while (1) {
        G3SparkDirs particleDir2 = D_8011DDE0_w04;

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1, &particleDir2.dir[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            func_80003A70_main(0);
        }
    }
}

void func_8010F264_w04(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011B770_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void func_8010F2D0_w04(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    func_8010F9F4_w04();
    func_800DCA64_shared_board(currentPlayerIndex);
    MBPlayerVibrate(CUR_PLAYER, 3);
    GWBoardFlagSet(0x11);
    func_800DC128_shared_board(currentPlayerIndex);
    playerIndex = func_800EF0D8_shared_board(1);
    func_8004A0E0_main();
    func_800FC8A4_shared_board();
    HuPrcSleep(5);
    HuPrcSleep(25);
    MBPlayerMotionSet(currentPlayerIndex, 2, 0);
    func_800EE688_shared_board(GwPlayer[currentPlayerIndex].player_obj, 2.0f, -0.3f);
    HuPrcSleep(5);
    func_800DCBCC_shared_board(currentPlayerIndex);
    func_800F2388_shared_board(currentPlayerIndex, CUR_PLAYER, 0, 10, 2);
    HuPrcSleep(20);
    MBItemWarpBlockSwapInit();
    MBItemWarpBlockSwapPlayerSet(playerIndex);
    MBItemWarpBlockSwapCreate();
    GWBoardFlagClear(0x11);
    fxId = func_800DC128_shared_board(currentPlayerIndex);
    HuAudFXStop(fxId);
    func_800DC06C_shared_board(currentPlayerIndex);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    func_800DCD2C_shared_board(currentPlayerIndex, CUR_PLAYER);
    spaceIndex = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    MBMasuCurSet(spaceIndex);
    MBMasuEventCall(spaceIndex, 1);
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(CUR_PLAYER);
    }
    func_800DAA40_shared_board(currentPlayerIndex);
}

void func_8010F490_w04(void) {
    Process *process = HuPrcCurrentGet();
    G3ItemMoveWork *work = process->user_data;
    f32 deltaX;
    f32 deltaY;
    f32 spriteX;
    f32 spriteY;
    s32 i;

    deltaX = (f32)(work->endX - work->startX) / (f32)work->duration;
    deltaY = (f32)(work->endY - work->startY) / (f32)work->duration;
    func_800F6848_shared_board(GwSystem.current_player_index, MBItemSelNoGet(), &spriteX, &spriteY);

    for (i = 1; i <= work->duration; i++) {
        if (work->spriteGroup != -1) {
            func_80054904_main(work->spriteGroup, 0,
                                work->startX + (deltaX * i), work->startY + (deltaY * i));
        }

        MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                           spriteX + (deltaX * i), spriteY + (deltaY * i));
        HuPrcVSleep();
    }

    if (work->spriteGroup != -1) {
        func_80054904_main(work->spriteGroup, 0, work->endX, work->endY);
    }

    MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                       work->endX + spriteX - work->startX,
                       work->endY + spriteY - work->startY);
    omDelPrcObj(NULL);
}

Process *func_8010F6F4_w04(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration) {
    Process *process;
    G3ItemMoveWork *work;

    process = omAddPrcObj(func_8010F490_w04, 0x4002, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = work;
    work->startX = startX;
    work->startY = startY;
    work->endX = endX;
    work->endY = endY;
    if (duration == -1) {
        duration = 25;
    }
    work->duration = duration;
    work->spriteGroup = spriteGroup;
    return process;
}

void func_8010F7C4_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    Process *process;
    f32 position[2];
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, func_8010F6F4_w04(
                                mbItemCursorGrpId, position[0], position[1],
                                D_8011C804_w04[system->current_player_index].x,
                                D_8011C804_w04[system->current_player_index].y, -1));
    HuPrcChildWait();
    HuPrcSleep(10);
    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 10; i++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (i * 25));
        MBStatusItemOfsApply(system->current_player_index,
                             MBItemSelNoGet(), 0, 2.0f);
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    MBPlayerMotionSet(-1, 5, 0);
    func_8004ACE0_main(0x274, system->current_player_index);
    HuPrcSleep(50);
    MBPlayerMotionSet(-1, -1, 2);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8010F9F4_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    func_8010F6F4_w04(
        mbItemCursorGrpId, position[0], position[1],
        D_8011C824_w04[system->current_player_index].x,
        D_8011C824_w04[system->current_player_index].y, -1);
    HuPrcSleep(20);

    for (i = 1; i < 10; i++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (i * 25));
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuPrcSleep(2);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8010FBC4_w04(void) {
    f32 position[2];
    s32 targetX;
    s32 targetY;
    Process *process;
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    func_800F6848_shared_board(GwSystem.current_player_index,
                                      MBItemSelNoGet(), &position[0], &position[1]);
    MBStatusItemPosGet(-1, MBItemSelNoGet(), &targetX, &targetY);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                            targetX, targetY, -1));
    HuPrcChildWait();

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8010FD34_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    Process *process;
    s32 i;
    s32 j;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                            D_8011C804_w04[system->current_player_index].x,
                                            D_8011C804_w04[system->current_player_index].y, -1));
    HuPrcChildWait();
    HuPrcSleep(10);
    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    if ((GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == 0xB) ||
        (GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == 8)) {
        HuAudFXPlay(0x141);
    }

    for (i = 0; i <= 1080; i += 30) {
        MBStatusItemRotSet(system->current_player_index,
                           MBItemSelNoGet(), sindf(i) * 30.0f);
        HuPrcVSleep();
    }

    for (j = 1; j < 10; j++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (j * 25));
        MBStatusItemRotSet(system->current_player_index,
                           MBItemSelNoGet(), sindf(i) * 30.0f);
        HuPrcVSleep();
        i += 30;
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_80110080_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    Process *process;
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                            D_8011C804_w04[system->current_player_index].x,
                                            D_8011C804_w04[system->current_player_index].y, -1));
    HuPrcChildWait();
    HuPrcSleep(10);
    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_80110244_w04(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
    f32 position[2];
    f32 stepX;
    f32 stepY;
    f32 scale;
    s32 i;

    if (mode == 2) {
        HuAudFXPlay(0x145);
    }

    func_800F6848_shared_board(arg0, arg1, &position[0], &position[1]);
    stepX = (target[0] - position[0]) / duration;
    stepY = (target[1] - position[1]) / duration;

    for (i = 2; duration != 0; duration--, i++) {
        position[0] += stepX;
        position[1] += stepY;
        MBStatusItemPosSet(arg0, arg1, position[0], position[1]);

        if ((mode == 1) && (i < 11)) {
            MBStatusItemTPLvlSet(arg0, arg1, i * 25);
            scale = i * 0.07f;
            MBStatusItemScaleSet(arg0, arg1, scale + 0.3f,
                                 (f32)((f64)scale + D_8011DE40_w04));
        }
        HuPrcVSleep();
    }

    MBStatusItemPosSet(arg0, arg1, target[0], target[1]);

    if (mode == 0) {
        for (i = 1; i < 10; i++) {
            MBStatusItemTPLvlSet(arg0, arg1, 255 - (i * 25));
            MBStatusItemScaleSet(arg0, arg1, 1.0f - (i * 0.1f), 1.0f - (i * 0.1f));
            HuPrcVSleep();
        }
        MBStatusItemTPLvlSet(arg0, arg1, 0);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/w04/367960", D_8011DE40_w04);

void func_801104DC_w04(void) {
    GW_PLAYER *player;
    Object *model;
    f32 scale;
    f32 angle;

    player = MBPlayerGet(-1);
    MBKSuitCreate();
    MBModelDispOff(D_801011FC_shared_board);
    D_801011FC_shared_board->omObj1->scale.x = 0.0f;
    D_801011FC_shared_board->omObj1->scale.y = 0.0f;
    D_801011FC_shared_board->omObj1->scale.z = 0.0f;
    MBPlayerVibrate(-1, 3);
    HuAudFXPlay(0x143);

    model = MBModelCreate(0x22, NULL);
    func_8001C258_main(model->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(model->omObj1->model[0], 0x1800);
    func_8001C448_main(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &player->player_obj->coords);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOff(player->player_obj);
    MBModelDispOn(D_801011FC_shared_board);

    for (; scale >= 1.0f; scale = (f32)((f64)scale - 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
    HuPrcSleep(20);
    func_8004ACE0_main(0x274, GwSystem.current_player_index);
    MBKSuitMotionSet(5, 2);
    HuPrcSleep(40);
    MBKSuitMotionSet(-1, 2);
    MBDlgResultWinExec(0x3A14);
}

void func_80110768_w04(void) {
    Vec direction;
    GW_PLAYER *player;
    Object *model;
    f32 scale;
    f32 angle;

    player = MBPlayerGet(-1);
    MBKSuitMotionSet(-1, 2);
    MBVecForwardSet(&direction);
    func_800ED128_shared_board(&player->player_obj->rot, &direction, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    HuAudFXPlay(0x143);

    model = MBModelCreate(0x22, NULL);
    func_8001C258_main(model->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(model->omObj1->model[0], 0x1800);
    func_8001C448_main(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &player->player_obj->coords);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOn(player->player_obj);
    MBKSuitKill();

    for (; scale >= 1.0f; scale = (f32)((f64)scale - 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
}

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
