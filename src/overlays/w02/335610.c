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

void func_80105CA4_w02(void);
void func_80106094_w02(void*);
extern s32 D_8011C6B0_w02[];
extern s32 D_8011C6CC_w02[];
extern Object* D_8011EBD8_w02[];
extern Process* D_8011EC18_w02;
extern Object* D_8011EC1C_w02;
extern s16 D_8011C6A0_w02[]; //mb2ev_StarGuideMasu

// board g1: declarations for func_801059D0_w02..func_8010985C_w02

typedef struct {
    u8 unk[4];
} g1Unk4Bytes;

extern s16 D_8011C660_w02[]; /* star-space order */
extern s16 D_8011C670_w02[]; /* order constraints */
extern s16 D_8011C680_w02[]; /* star board flags */
extern s16 D_8011C690_w02[]; /* star spaces */
extern s32 D_8011C6E8_w02;
extern u8 D_8011EA70_w02[];
extern char D_8011EA74_w02[];
extern Unk3 *D_8011EC20_w02;
extern Unk3 *D_8011EC24_w02;
extern Unk3 *D_8011EC28_w02;
extern Unk3 *D_8011EC2C_w02;
extern Unk3 *D_8011EC30_w02;
extern s32 D_8011EC34_w02;
extern s32 D_8011EC38_w02;
extern s16 D_8011C6EC_w02[]; /* blocked-space extension table */
extern s16 D_8011C6F0_w02[]; /* blocked spaces */
extern s16 D_8011C704_w02[][2]; /* star guide offsets (asm also labels +2 as D_8011C706_w02) */
extern s16 D_8011C724_w02[][2]; /* Boo offsets */
extern s16 D_8011C72C_w02[][2];
extern s16 D_8011C734_w02[][2];
extern s16 D_8011C73C_w02[][2];
extern s16 D_8011C744_w02[][2]; /* pairs of spaces giving a model's facing */
extern s16 D_8011C74C_w02[]; /* star guide spaces */
extern s16 D_8011C75C_w02[]; /* star guide board flags */
extern s16 D_8011C76C_w02[]; /* Boo spaces */
extern s16 D_8011C770_w02[]; /* bank spaces */
extern Vec D_8011C774_w02[]; /* bank coin offsets */
extern Vec D_8011C7B0_w02[]; /* bank coin rotations (asm also labels +8 as D_8011C7B8_w02) */
extern s16 D_8011C7EC_w02[];
extern s16 D_8011C7F0_w02[]; /* model per board */
extern u32 *D_8011C82C_w02[]; /* model resource lists per board */
extern s32 D_8011C844_w02[]; /* sound per board */
extern s32 D_8011C868_w02[]; /* delayed sound per board */
extern s32 D_8011C88C_w02[]; /* delay per board */
extern s32 D_8011C8B0_w02[];
extern s16 D_8011C8D4_w02[];
extern s16 D_8011C8D8_w02[];
extern event_table_entry D_8011D688_w02[];
extern event_table_entry D_8011D700_w02[];
extern event_table_entry D_8011D894_w02[];
extern event_table_entry D_8011D9CC_w02[];
extern Object *D_8011EBD0_w02;
extern Process *D_8011EBF8_w02[8];
extern Object *D_8011EC3C_w02;
extern Object *D_8011EC40_w02[1];
extern Object *D_8011EC44_w02;
extern Object *D_8011EC48_w02[10];
extern Object *D_8011EC70_w02;
extern Object *D_8011EC74_w02[2];

typedef BranchLink g1BranchLink;

extern Object *D_8011C8DC_w02;
extern Object *D_8011C8E0_w02;
extern s16 D_8011C8E4_w02[];
extern Object *D_8011EC80_w02[4];
/* branch tables: spaces, links, decision trees */
extern s16 D_8011D070_w02[][3];
extern g1BranchLink D_8011D084_w02[][2];
extern DecisionTreeNonLeafNode *D_8011C994_w02[];
extern s16 D_8011D0B8_w02[][3];
extern g1BranchLink D_8011D0CC_w02[][2];
extern DecisionTreeNonLeafNode *D_8011CA3C_w02[];
extern s16 D_8011D100_w02[][3];
extern g1BranchLink D_8011D114_w02[][2];
extern DecisionTreeNonLeafNode *D_8011CB8C_w02[];
extern s16 D_8011D148_w02[][3];
extern g1BranchLink D_8011D15C_w02[][2];
extern DecisionTreeNonLeafNode *D_8011CCA0_w02[];
extern s16 D_8011D190_w02[][3];
extern g1BranchLink D_8011D1A4_w02[][2];
extern DecisionTreeNonLeafNode *D_8011CDD8_w02[];
extern s16 D_8011D1D8_w02[][3];
extern g1BranchLink D_8011D1EC_w02[][2];
extern DecisionTreeNonLeafNode *D_8011CE68_w02[];
extern s16 D_8011D220_w02[][3];
extern g1BranchLink D_8011D234_w02[][2];
extern DecisionTreeNonLeafNode *D_8011CEEC_w02[];
extern s16 D_8011D268_w02[][3];
extern g1BranchLink D_8011D27C_w02[][2];
extern DecisionTreeNonLeafNode *D_8011CF58_w02[];
extern s16 D_8011D2B0_w02[][3];
extern g1BranchLink D_8011D2B8_w02[][2];
extern DecisionTreeNonLeafNode *D_8011CFA0_w02[];

void func_80115FEC_w02(s16 (*masu)[3], g1BranchLink (*links)[2], DecisionTreeNonLeafNode **trees);
void func_80108870_w02(void);
void func_801088EC_w02(s16 arg0);
void func_80108C4C_w02(void);
void func_80108CC0_w02(void);
void func_80108D34_w02(void);
void func_80108DA8_w02(void);
void func_80108E1C_w02(void);
void func_80105B00_w02(void);
void func_80105B8C_w02(void);
void func_80107830_w02(void);
void func_80107BFC_w02(s16 arg0);
void func_80107D24_w02(void);
void func_80107D88_w02(void);
void func_80107E34_w02(s16 arg0);
void func_80107F54_w02(void);
void func_80107FB0_w02(void);
void func_801080AC_w02(s16 arg0);
void func_80108218_w02(void);
void func_80108280_w02(s16 arg0);
void func_801083EC_w02(void);
void func_8010844C_w02(void);
void func_80108570_w02(void);
void func_8010865C_w02(void);
void func_801086DC_w02(void);
void func_80108754_w02(void);
void func_801087F8_w02(void);
void func_801089C0_w02(void);
void func_8010D9E4_w02(void);
void func_8010EE64_w02(void);
void func_8010F22C_w02(void);
void func_8010F298_w02(void);
void func_8010F78C_w02(void);
void func_8010FCFC_w02(void);
void func_80110048_w02(void);
void func_801104A4_w02(void);
void func_80110730_w02(void);
void func_80110B80_w02(void);
void func_80110E40_w02(void);
void func_801111E0_w02(void);
void func_80111BDC_w02(void);
void func_80112734_w02(void);
void func_8011344C_w02(void);
void func_801146E8_w02(void);
void func_801156E8_w02(void);
void func_80116608_w02(void);
void func_80116914_w02(void);
void func_80116AC4_w02(void);
void func_8011720C_w02(void);
void func_80117344_w02(void);
void func_801177C8_w02(void);
void func_8011B8A0_w02(void);
s32 func_8011BC6C_w02(void);

void func_801059F8_w02(void);
void func_801064DC_w02(void);
void func_80107170_w02(void);
void func_801072A0_w02(void);
s32 func_80107438_w02(u8 *arg0, s32 arg1, s32 arg2);
s32 func_8011C274_w02(void);
s32 func_8011C5D8_w02(void);

s16 func_801059D0_w02(void) {
    return D_8011C6A0_w02[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void func_801059F8_w02(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < D_8011C670_w02[idx2]) {
                continue;
            }
            if (idx2 < D_8011C670_w02[idx1]) {
                continue;
            }
            {
                s32 temp = D_8011C660_w02[idx1];
                D_8011C660_w02[idx1] = D_8011C660_w02[idx2];
                D_8011C660_w02[idx2] = temp;
                temp = D_8011C670_w02[idx1];
                D_8011C670_w02[idx1] = D_8011C670_w02[idx2];
                D_8011C670_w02[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = D_8011C660_w02[i];
    }
}

void func_80105B00_w02(void) {
    GW_SYSTEM *loc;
    s32 sp7;
    s32 sp0;

    loc = &GwSystem;
    loc->current_star_spawn++;
    if (loc->current_star_spawn >= 8) {
        sp7 = loc->star_spawn_indices[7];
        loc->current_star_spawn = 0;
        GWBoardFlagSet(4);
        func_801059F8_w02();
        sp0 = loc->star_spawn_indices[0];
        if ((sp7 ^ sp0) == 0) {
            loc->star_spawn_indices[0] = loc->star_spawn_indices[7];
            loc->star_spawn_indices[7] = sp0;
        }
    }
}

void func_80105B8C_w02(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(D_8011C680_w02[i]);
    }
    MBMasuTypeSet(D_8011C690_w02[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(D_8011C680_w02[loc->star_spawn_indices[loc->current_star_spawn]]);
}

s32 func_80105C30_w02(s16 arg0) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        if (arg0 == D_8011C690_w02[i]) {
            if (i == loc->star_spawn_indices[loc->current_star_spawn]) {
                loc->unk_0E = D_8011C680_w02[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

void func_80105CA4_w02(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    D_8011EC1C_w02 = MBModelCreate(0x3A, NULL);
    model = D_8011EC1C_w02;
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
    D_8011EC18_w02 = NULL;
    omDelPrcObj(NULL);
}

void func_80106094_w02(void *arg) {
    omObjData *s0 = *(omObjData **)arg;

    s0->scale.y = 4.0f;
    s0->scale.z = -0.6f;
    HuPrcSleep(3);
    while (s0->scale.z != 0.0f) {
        HuPrcVSleep();
    }
}

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


void func_801064DC_w02(void) {
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
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x79) {
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
    if (D_8011C6E8_w02 != 0) {
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
    if (D_8011C6E8_w02 != 0) {
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

void func_80106A3C_w02(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801064DC_w02, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

void func_80106AB0_w02(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80106B38_w02(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void func_80106B94_w02(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_8011EC20_w02 = func_800E210C_shared_board(0, 0x92, 1);
    D_8011EC24_w02 = func_800E210C_shared_board(1, 0xA0, 1);
    D_8011EC30_w02 = func_800E210C_shared_board(0xD, 0xAE, 1);
    D_8011EC28_w02 = func_800E210C_shared_board(3, 0xBC, 1);
    D_8011EC2C_w02 = func_800E210C_shared_board(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80106C64_w02(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011EC20_w02);
    MBHelpWinKill(D_8011EC24_w02);
    MBHelpWinKill(D_8011EC30_w02);
    MBHelpWinKill(D_8011EC28_w02);
    MBHelpWinKill(D_8011EC2C_w02);
}

s32 func_80106CC4_w02(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011EA70_w02;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = func_8011C274_w02();
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

s32 func_80106F58_w02(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011EA70_w02;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // dead store; matches func_800FA104_shared_board
                var_s2 = func_8011C5D8_w02();
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

void func_80107170_w02(void) {
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
                D_8011EC34_w02 = 1;
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
        D_8011EC34_w02 = 0;
    } else {
        D_8011EC34_w02 = 2;
    }
}

void func_801072A0_w02(void) {
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
    func_80107170_w02();
    if (D_8011EC34_w02 == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                D_8011EC38_w02 = order[i];
                break;
            }
        }
    } else if (D_8011EC34_w02 == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                D_8011EC38_w02 = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        D_8011EC34_w02 = 2;
    }
}

s32 func_80107438_w02(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011EA70_w02;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 == 0) {
                    func_801072A0_w02();
                    var_s2 = D_8011EC34_w02 + 1;
                } else {
                    var_s2 = D_8011EC38_w02 + 1;
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

s32 func_80107704_w02(u8 *arg0) {
    return func_80107438_w02(arg0, 0, 1);
}

s32 func_80107724_w02(u8 *arg0) {
    return func_80107438_w02(arg0, 1, 0);
}

void func_80107744_w02(void) {
    GwSystem.current_board_index = 1;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

void func_80107780_w02(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0xB, 0);
    MBMoveMasuSet(1, 0xB, 0);
    MBMoveMasuSet(2, 0xB, 0);
    MBMoveMasuSet(3, 0xB, 0);
    GWBoardFlagSet(3);
    func_801059F8_w02();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[0] = 0;
    GwSystem.boardData.halfWordBytes[1] = MBRand(4.0f);
    omOvlReturnEx(1);
}

void func_80107830_w02(void) {
    Vec sp10;
    SpaceData *space;
    s32 i;

    omInitObjMan(0xA0, 0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(6, 0x23B, 8, 0);
    MBMasuBlockTblExtSet(D_8011C6EC_w02);
    MBMasuBlockTblSet(D_8011C6F0_w02);
    space = MBMasuGet(0x69);
    MBVecDirGet(&space->coords, &MBMasuGet(0x6D)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    space = MBMasuGet(0x73);
    MBVecDirGet(&space->coords, &MBMasuGet(0x6C)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBItemHookSet(0, &func_8010D9E4_w02);
    MBItemHookSet(1, &func_8010EE64_w02);
    MBItemHookSet(9, &func_8010F22C_w02);
    MBItemHookSet(2, &func_8010F298_w02);
    MBItemHookSet(3, &func_801177C8_w02);
    MBItemHookSet(4, &func_801104A4_w02);
    MBItemHookSet(5, &func_80110730_w02);
    MBItemHookSet(6, &func_8010F78C_w02);
    MBItemHookSet(7, &func_8010FCFC_w02);
    MBItemHookSet(8, &func_80110048_w02);
    MBItemHookSet(0xA, &func_80116AC4_w02);
    MBItemHookSet(0xB, &func_80117344_w02);
    MBItemHookSet(0xE, &func_80110B80_w02);
    MBItemHookSet(0xF, &func_80110E40_w02);
    MBItemHookSet(0x10, &func_801111E0_w02);
    MBItemHookSet(0x11, &func_80111BDC_w02);
    MBItemHookSet(0x12, &func_80112734_w02);
    MBItemHookSet(0x13, &func_8011344C_w02);
    MBItemHookSet(0x14, &func_801146E8_w02);
    MBItemHookSet(0x15, &func_801156E8_w02);
    MBItemHookSet(0xC, &func_80116914_w02);
    MBItemHookSet(0xD, &func_8011720C_w02);
    MBComItemDecideHookSet(func_8011BC6C_w02);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, D_8011C6A0_w02[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        func_80105B00_w02();
    }

    func_80105B8C_w02();
    func_80107D88_w02();
    func_80107F54_w02();
    func_80108218_w02();
    func_801083EC_w02();
    func_8010865C_w02();
    func_801086DC_w02();
    func_801087F8_w02();
    func_80108754_w02();
    func_801089C0_w02();
    func_80116608_w02();
    func_800EBDAC_shared_board();
}

void func_80107B4C_w02(void) {
    HuAudSeqPlay(0x19);
    D_800CE198_main = 0x19;
    func_800F8D6C_shared_board(0x19);
    Hu3DCamInit(2);
    func_80107830_w02();
    MBMasuEventTblAdd(D_8011D688_w02);
    MBMasuEventTblAdd(D_8011D9CC_w02);
    MBHatenaFuncSet(&func_8011B8A0_w02);
    MBMasuEventTblAdd(D_8011D700_w02);
    MBMasuEventTblAdd(D_8011D894_w02);
    MBStart(0);
}

void func_80107BD0_w02(void) {
    Hu3DCamInit(1);
    func_80107830_w02();
    MBStart(1);
}

void func_80107BFC_w02(s16 arg0) {
    Object *obj;

    if (D_8011EBD8_w02[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_800461B4_main(obj->omObj1->model[0]);
    if (D_8011EBD0_w02 == NULL) {
        D_8011EBD0_w02 = obj;
    }
    D_8011EBD8_w02[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_8011EBF8_w02[arg0] = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C74C_w02[arg0])->coords);
    func_800D771C_shared_board(0xB, obj, D_8011C704_w02[arg0][0], D_8011C704_w02[arg0][1]);
}

void func_80107D24_w02(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        Process *prc = D_8011EBF8_w02[i];

        if (prc != NULL) {
            omDelPrcObj(prc);
            D_8011EBF8_w02[i] = NULL;
        }
    }
}

void func_80107D88_w02(void) {
    s32 i;

    D_8011EBD0_w02 = 0;
    for (i = 0; i < 8; i++) {
        D_8011EBD8_w02[i] = 0;
        D_8011EBF8_w02[i] = NULL;
        MBKinokoEffKillHookSet(func_80107D24_w02);
        if (!GWBoardFlagCheck(D_8011C75C_w02[i])) {
            func_80107BFC_w02(i);
        }
    }
}

void func_80107E34_w02(s16 arg0) {
    Object *obj;

    if (D_8011EC40_w02[arg0] != NULL) {
        return;
    }
    if (D_8011EC3C_w02 == NULL) {
        obj = MBModelCreate(0xA, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_8011EC3C_w02 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EC3C_w02);
    }
    MBModelDispOff(obj);
    D_8011EC40_w02[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C76C_w02[arg0])->coords);
    func_800D771C_shared_board(0xA, obj, D_8011C724_w02[arg0][0], D_8011C724_w02[arg0][1]);
}

void func_80107F54_w02(void) {
    s32 i;

    D_8011EC3C_w02 = 0;
    for (i = 0; i <= 0; i++) {
        D_8011EC40_w02[i] = NULL;
        func_80107E34_w02(i);
    }
}

void func_80107FB0_w02(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(D_8011EC48_w02[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(D_8011EC48_w02[i * 5 + j]);
        }
    }
}

void func_801080AC_w02(s16 arg0) {
    Object *obj;

    if (D_8011EC48_w02[arg0] != NULL) {
        return;
    }
    if (D_8011EC44_w02 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_8011EC44_w02 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EC44_w02);
    }
    D_8011EC48_w02[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C770_w02[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &D_8011C774_w02[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = D_8011C7B0_w02[arg0 % 5].x;
    obj->omObj1->rot.z = D_8011C7B0_w02[arg0 % 5].z;
    MBModelDispOff(obj);
}

void func_80108218_w02(void) {
    s32 i;

    D_8011EC44_w02 = 0;
    for (i = 0; i < 0xA; i++) {
        D_8011EC48_w02[i] = NULL;
        func_801080AC_w02(i);
    }
    func_80107FB0_w02();
}

void func_80108280_w02(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (D_8011EC74_w02[arg0] != NULL) {
        return;
    }
    if (D_8011EC70_w02 == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(D_8011C7F0_w02[board], D_8011C82C_w02[board]);
        MBModelTempAllocFree(obj);
        D_8011EC70_w02 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EC70_w02);
    }
    D_8011EC74_w02[arg0] = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C7EC_w02[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(D_8011C744_w02[arg0][0]);
        SpaceData *masuB = MBMasuGet(D_8011C744_w02[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    func_800D771C_shared_board(0xC, obj, D_8011C73C_w02[arg0][0], D_8011C73C_w02[arg0][1]);
}

void func_801083EC_w02(void) {
    s32 i;

    D_8011EC70_w02 = 0;
    for (i = 0; i < 2; i++) {
        D_8011EC74_w02[i] = NULL;
        func_80108280_w02(i);
    }
}

void func_8010844C_w02(void) {
    HuPrcSleep(D_8011C88C_w02[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011C868_w02[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void func_801084A8_w02(s32 arg0, s32 arg1) {
    MBMotionSet(D_8011EC74_w02[arg0], arg1 - 1, 0);
    func_8001C814_main(D_8011EC74_w02[arg0]->omObj1->model[0], 5, 0);
    if (D_8011C844_w02[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011C844_w02[GwSystem.current_board_index]);
    }

    if (D_8011C868_w02[GwSystem.current_board_index] != -1) {
        omAddPrcObj(func_8010844C_w02, 0x1000, 0, 0);
    }
}

void func_80108570_w02(void) {
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
    func_8001C814_main(D_8011EC74_w02[index]->omObj1->model[0], 1, 4);

    if (D_8011C8B0_w02[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011C8B0_w02[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void func_80108620_w02(s32 arg) {
    Process *temp = omAddPrcObj(func_80108570_w02, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void func_8010865C_w02(void) {
    s32 i;

    D_8011EC70_w02 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011C8D4_w02[i])->coords,
                                         D_8011C72C_w02[i][0], D_8011C72C_w02[i][1]);
    }
}

void func_801086DC_w02(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011C8D8_w02[i])->coords,
                                         D_8011C734_w02[i][0], D_8011C734_w02[i][1]);
    }
}

void func_80108754_w02(void) {
    SpaceData *masu = MBMasuGet(0x81);
    Object *obj = MBModelFileCreate(0x13016D, -1, 0.8f, 0, 0);

    MBModelTempAllocFree(obj);
    D_8011C8DC_w02 = obj;
    obj->flags |= 2;
    obj->rot.x = sindf(-138.0f);
    obj->rot.z = cosdf(-138.0f);
    HuVecCopy3F(&obj->coords, &masu->coords);
}

void func_801087F8_w02(void) {
    SpaceData *masu = MBMasuGet(0x7B);
    Object *obj = MBModelFileCreate(0x13016B, -1, 1.0f, 0, 0);

    MBModelTempAllocFree(obj);
    D_8011C8E0_w02 = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &masu->coords);
}

void func_80108870_w02(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((GwSystem.boardData.halfWordBytes[0] >> i) & 1) {
            MBModelDispOn(D_8011EC80_w02[i]);
        } else {
            MBModelDispOff(D_8011EC80_w02[i]);
        }
    }
}

void func_801088EC_w02(s16 arg0) {
    Object *obj;

    if (D_8011EC80_w02[arg0] != NULL) {
        return;
    }
    obj = MBModelFileCreate(0x13016C, -1, 1.0f, 0, 0);
    MBModelTempAllocFree(obj);
    D_8011EC80_w02[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C8E4_w02[arg0])->coords);
    obj->coords.x -= 4.0f;
    obj->coords.z -= 2.0f;
}

void func_801089C0_w02(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8011EC80_w02[i] = NULL;
        func_801088EC_w02(i);
    }
    func_80108870_w02();
}

s32 func_80108A20_w02(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        count += (GwSystem.boardData.halfWordBytes[0] >> i) & 1;
    }
    return count >= 3;
}

void func_80108A58_w02(void) {
    MBMoveNextMasuSet(-1, 0, 0xF);
    MBMoveBackMasuSet(-1, 0, 0xF);
}

void func_80108A8C_w02(void) {
    func_80115FEC_w02(D_8011D070_w02, D_8011D084_w02, D_8011C994_w02);
    omDelPrcObj(NULL);
}

void func_80108AC4_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x26 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 0, 0);
        player->rev &= ~1;
    } else {
        func_80115FEC_w02(D_8011D0B8_w02, D_8011D0CC_w02, D_8011CA3C_w02);
    }
}

void func_80108B6C_w02(void) {
    func_80115FEC_w02(D_8011D100_w02, D_8011D114_w02, D_8011CB8C_w02);
    omDelPrcObj(NULL);
}

void func_80108BA4_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x59 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 0xA, 0);
        player->rev &= ~1;
    } else {
        func_80115FEC_w02(D_8011D148_w02, D_8011D15C_w02, D_8011CCA0_w02);
    }
}

void func_80108C4C_w02(void) {
    func_80115FEC_w02(D_8011D190_w02, D_8011D1A4_w02, D_8011CDD8_w02);
}

void func_80108C7C_w02(void) {
    if ((MBPlayerGet(-1)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80108C4C_w02();
    }
}

void func_80108CC0_w02(void) {
    func_80115FEC_w02(D_8011D1D8_w02, D_8011D1EC_w02, D_8011CE68_w02);
}

void func_80108CF0_w02(void) {
    if ((MBPlayerGet(-1)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80108CC0_w02();
    }
}

void func_80108D34_w02(void) {
    func_80115FEC_w02(D_8011D220_w02, D_8011D234_w02, D_8011CEEC_w02);
}

void func_80108D64_w02(void) {
    if ((MBPlayerGet(-1)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80108D34_w02();
    }
}

void func_80108DA8_w02(void) {
    func_80115FEC_w02(D_8011D268_w02, D_8011D27C_w02, D_8011CF58_w02);
}

void func_80108DD8_w02(void) {
    if ((MBPlayerGet(-1)->rev & 0x80) && (mbWalkNum != 0)) {
        func_80108DA8_w02();
    }
}

void func_80108E1C_w02(void) {
    func_80115FEC_w02(D_8011D2B0_w02, D_8011D2B8_w02, D_8011CFA0_w02);
}

void func_80108E4C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && (mbWalkNum != 0) && (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x67)) {
        func_80108E1C_w02();
    } else if ((player->rev & 0x80) && (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x67)) {
        MBMoveBackMasuSet(-1, 0, 0x10);
        MBMoveNextMasuSet(-1, 0, 0xE);
    } else if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x67) {
        MBMoveBackMasuSet(-1, 0, 0xE);
    }
}

void func_80108F8C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x12) {
        MBMoveNextMasuSet(-1, 4, 5);
    }
}

void func_80108FEC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x23) {
        MBMoveNextMasuSet(-1, 0, 0x14);
    }
}

void func_8010904C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x24) {
        MBMoveNextMasuSet(-1, 0, 5);
    }
}

void func_801090AC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x42) {
        MBMoveNextMasuSet(-1, 0, 0x14);
    }
}

void func_8010910C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 9) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_8010916C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x85) {
        MBMoveNextMasuSet(-1, 4, 5);
    }
}

void func_801091CC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x28) {
        MBMoveNextMasuSet(-1, 2, 7);
    }
}

void func_8010922C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0xD) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_8010928C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2B) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_801092EC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x38) {
        MBMoveNextMasuSet(-1, 6, 0xB);
    }
}

void func_8010934C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x69) {
        MBMoveNextMasuSet(-1, 6, 0xB);
    }
}

void func_801093AC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5C) {
        MBMoveNextMasuSet(-1, 7, 0x12);
    }
}

void func_8010940C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x87) {
        MBMoveNextMasuSet(-1, 7, 0x16);
    }
}

void func_8010946C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x88) {
        MBMoveNextMasuSet(-1, 6, 5);
    }
}

void func_801094CC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x50) {
        MBMoveNextMasuSet(-1, 7, 0x16);
    }
}

void func_8010952C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x56) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_8010958C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2A) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_801095EC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0xC) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

s32 func_8010964C_w02(s32 arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011EA70_w02;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1;
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
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 0x10);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return func_8005E1D8_main(mbDlgWinId, 0, 1);
}

void func_8010985C_w02(void) {
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

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x6A) {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x6B) {
            if (MBItemFind(GwSystem.current_player_index, 1) != -1) {
                func_800DBEC0_shared_board(GwSystem.current_player_index);
                MBPlayerMotionSet(-1, -1, 2);
                sp18 = MBMasuLinkMasuIdGet(player->clink, player->cidx);
                switch (sp18) {
                    case 0x85:
                    case 0x86:
                        func_800ED20C_shared_board(-1, 8, 0x6A);
                        break;
                    default:
                        func_800ED20C_shared_board(-1, 8, 0x6B);
                        break;
                }
                HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
                HuPrcChildWait();
                MBPlayerVibrate(-1, 1);

                while (1) {
                    MBDlgWinCreate(0x38, 0x4103);
                    choice = func_8010964C_w02(0);
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
                                case 0x85:
                                    func_801084A8_w02(0, 0);
                                    break;
                                case 0x86:
                                    func_801084A8_w02(0, 1);
                                    break;
                                case 0x87:
                                    func_801084A8_w02(1, 0);
                                    break;
                                default:
                                    func_801084A8_w02(1, 1);
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
                            func_80106AB0_w02();
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
            case 0x85:
                MBMoveNextMasuSet(-1, 3, 0);
                player->rev |= 1;
                break;
            case 0x86:
                MBMoveNextMasuSet(-1, 3, 4);
                player->rev &= ~1;
                break;
            case 0x87:
                MBMoveNextMasuSet(-1, 9, 0);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 9, 4);
                player->rev &= ~1;
                break;
        }
    }

    omDelPrcObj(NULL);
}

void func_80109C80_w02(void) {
}

void func_80109C88_w02(void) {
}

void func_80109C90_w02(void) {
}

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
extern const f64 D_8011EA78_w02;
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

// board g3: types, data and prototypes for func_8010D9A8_w02..func_801111E0_w02

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

void func_8010D854_w02(void);
void func_80108620_w02(s32 arg);
s32 func_80107704_w02(u8 *choices);
s32 func_80107724_w02(u8 *choices);
s32 func_80109C98_w02(s32 arg0, s32 arg1);
void func_80109FD8_w02(void);
void func_8010B1C8_w02(void);
void func_8010C47C_w02(Object *obj);
void func_8010C51C_w02(Object *obj);
s32 func_8010C5BC_w02(s32 playerIndex);
s32 func_8010CA28_w02(s32 playerIndex);
void func_8010D9A8_w02(s32 arg);
omObjData *func_8010EBF0_w02(Vec *pos, f32 scaleRate, f32 fadeRate, s16 killOnFade, Vec *vel, s32 star);
void func_8010ED4C_w02(omObjData *obj);
Process *func_8010F6BC_w02(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration);
void func_8010F9BC_w02(void);
void func_80110970_w02(void);
void func_800D9F5C_shared_board(Object *arg0, Vec *arg1, s32 arg2);
void func_8001ED54_main(s16 arg0);

extern u8 D_8011D628_w02[];
extern s32 D_8011D630_w02[];
extern s32 D_8011D63C_w02[];
extern Vec2f D_8011D710_w02[];
extern Vec2f D_8011D730_w02[];
extern DecisionTreeNonLeafNode D_8011D790_w02[];
extern s32 D_8011D7FC_w02[];
extern const G3SparkDirs D_8011EA80_w02;
extern const f64 D_8011EAE0_w02;
extern const f64 D_8011EAE8_w02;
extern const f64 D_8011EAF0_w02;
extern const f64 D_8011EAF8_w02;
extern const f64 D_8011EB00_w02;
extern s32 D_8011ECA0_w02;

void func_8010D9A8_w02(s32 arg) {
    Process *temp = omAddPrcObj(func_8010D854_w02, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void func_8010D9E4_w02(void) {
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
    if (spaceId != 0x79) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(D_8011EC3C_w02);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x66;
        space = MBMasuGet(0x66);
        boo = D_8011EC40_w02[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (D_8011D63C_w02[sys->current_board_index] != 0) {
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
            if (D_8011D63C_w02[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011D63C_w02[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (D_8011D63C_w02[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    func_8010C47C_w02(boo);
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
    menuResult = func_80107704_w02(choices);
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
    playerChoice = func_80107724_w02(choices);
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
                func_80106B38_w02();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106AB0_w02();
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
        if (rank < D_8011D630_w02[i]) {
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
            if (GwSystem.current_turn >= D_8011D5E8_w02[i][0] &&
                GwSystem.current_turn <= D_8011D5E8_w02[i][1]) {
                break;
            }
        }
        estimatedAmount = D_8011D5E8_w02[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    func_8010C51C_w02(boo);
    if (menu == 0) {
        resultAmount = func_8010CA28_w02(target);
        func_8010C47C_w02(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], D_8011EA74_w02, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], D_8011EA74_w02, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= D_8011D628_w02[i]) {
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
            D_8011EC9C_w02 = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(D_8011EC9C_w02);
            MBModelDispOff(D_8011EC9C_w02);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    func_8010D9A8_w02((s32)boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(D_8011EC9C_w02);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            func_8004ACE0_main(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = func_8010C5BC_w02(target);
        func_8010C47C_w02(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            D_8011C6E8_w02 = 1;
            func_80106A3C_w02(boo);
            D_8011C6E8_w02 = 0;
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
    func_8010C51C_w02(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        func_80106B38_w02();
        D_800CB99C_main = 1;
        func_80049FB8_main();
    } else {
        func_80106AB0_w02();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        func_8010C51C_w02(boo);
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
            if (D_8011D63C_w02[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011D63C_w02[sys->current_board_index] != 0) {
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
    func_80109C90_w02();
}

void func_8010EBB8_w02(void) {
    func_80108620_w02(0);
}

void func_8010EBD4_w02(void) {
    func_80108620_w02(1);
}

omObjData *func_8010EBF0_w02(Vec *pos, f32 scaleRate, f32 fadeRate, s16 killOnFade, Vec *vel, s32 star) {
    omObjData *obj;
    G3ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, func_8010ED4C_w02);
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

void func_8010ED4C_w02(omObjData *arg0) {
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

void func_8010EE64_w02(void) {
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
    func_8010F9BC_w02();
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
        G3SparkDirs particleDir = D_8011EA80_w02;

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EBF0_w02(&pos, 0.1f, 2.0f, 1, &particleDir.dir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    func_800EB24C_shared_board(
        D_8011C690_w02[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
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
        G3SparkDirs particleDir2 = D_8011EA80_w02;

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EBF0_w02(&pos, 0.1f, 2.0f, 1, &particleDir2.dir[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            func_80003A70_main(0);
        }
    }
}

void func_8010F22C_w02(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011C690_w02[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void func_8010F298_w02(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    func_8010F9BC_w02();
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

void func_8010F458_w02(void) {
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

Process *func_8010F6BC_w02(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration) {
    Process *process;
    G3ItemMoveWork *work;

    process = omAddPrcObj(func_8010F458_w02, 0x4002, 0, 0x40);
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

void func_8010F78C_w02(void) {
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
    HuPrcChildLink(process, func_8010F6BC_w02(
                                mbItemCursorGrpId, position[0], position[1],
                                D_8011D710_w02[system->current_player_index].x,
                                D_8011D710_w02[system->current_player_index].y, -1));
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

void func_8010F9BC_w02(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    func_8010F6BC_w02(
        mbItemCursorGrpId, position[0], position[1],
        D_8011D730_w02[system->current_player_index].x,
        D_8011D730_w02[system->current_player_index].y, -1);
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

void func_8010FB8C_w02(void) {
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
                   func_8010F6BC_w02(mbItemCursorGrpId, position[0], position[1],
                                            targetX, targetY, -1));
    HuPrcChildWait();

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8010FCFC_w02(void) {
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
                   func_8010F6BC_w02(mbItemCursorGrpId, position[0], position[1],
                                            D_8011D710_w02[system->current_player_index].x,
                                            D_8011D710_w02[system->current_player_index].y, -1));
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

void func_80110048_w02(void) {
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
                   func_8010F6BC_w02(mbItemCursorGrpId, position[0], position[1],
                                            D_8011D710_w02[system->current_player_index].x,
                                            D_8011D710_w02[system->current_player_index].y, -1));
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

void func_8011020C_w02(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
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
                                 (f32)((f64)scale + D_8011EAE0_w02));
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

void func_801104A4_w02(void) {
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
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + D_8011EAE8_w02)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOff(player->player_obj);
    MBModelDispOn(D_801011FC_shared_board);

    for (; scale >= 1.0f; scale = (f32)((f64)scale - D_8011EAF0_w02)) {
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

void func_80110730_w02(void) {
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
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + D_8011EAF8_w02)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOn(player->player_obj);
    MBKSuitKill();

    for (; scale >= 1.0f; scale = (f32)((f64)scale - D_8011EB00_w02)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
}

void func_80110970_w02(void) {
    s32 index;
    s32 group;
    s32 alpha;
    void *dialog;
    f32 x;
    f32 y;
    f32 angle;

    index = (s32)HuPrcCurrentGet()->user_data;
    dialog = MBPlayerVibrateObjCreate(-1, 1, 5);
    group = HuSprGrpCreate(1, 0);
    func_80055024_main(group, 0, D_8011ECA0_w02, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x1000);
    func_800F6848_shared_board(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    func_80054904_main(group, 0, x, y);
    func_80055420_main(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)D_8011D7FC_w02[index];
    for (; alpha >= 0; alpha -= 0x14) {
        x += cosdf(angle) * 5.0f;
        y -= sindf(angle) * 5.0f;
        func_80054904_main(group, 0, x, y);
        func_80055458_main(group, 0, alpha);
        HuPrcVSleep();
    }

    func_80055458_main(group, 0, 0);
    MBPlayerVibrateObjKill(dialog);
    HuSprGrpKill(group);
    omDelPrcObj(0);
}

void func_80110B80_w02(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011ECA0_w02 = func_80055810_main(data);
    DataClose(data);
    func_80110048_w02();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = func_80109C98_w02((s32)D_8011D790_w02, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(func_80109FD8_w02, 0, 0, 0);
                omPrcSetStatBit(process, 0x80);
                func_80106B38_w02();
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

        process = omAddPrcObj(func_80109FD8_w02, 0, 0, 0);
        omPrcSetStatBit(process, 0x80);
        func_80106B38_w02();
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
            process = omAddPrcObj(func_80110970_w02, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110970_w02, 0x4002, 0, 0);
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
    HuSprKill(D_8011ECA0_w02);
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
    func_8010B1C8_w02();
    GwSystem.forceShopHost = 0;
}

void func_80110E40_w02(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011ECA0_w02 = func_80055810_main(data);
    DataClose(data);
    func_80110048_w02();

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110970_w02, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_80110970_w02, 0x4002, 0, 0);
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
        choice = func_80109C98_w02(1, 0);
    } else {
        choice = func_80109C98_w02(2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = func_800EF0D8_shared_board(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(func_80109FD8_w02, 0, 0, 0);
            omPrcSetStatBit(process, 0x80);
            func_80106B38_w02();
            one = 1;
            D_800CB99C_main = one;
            func_80049FB8_main();
            omDelPrcObj(process);
            func_800FC8A4_shared_board();
            goto retry;
        default:
            MBDlgWinInsertCreate(4, 0x3A0B, mbCharNameMesTbl[GwPlayer[choice].chr], 0, 0, 0, 0);
            break;
    }
    MBDlgWinClose();
    MBDlgWinKill();

    HuAudFXPlay(0x29C);
    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprKill(D_8011ECA0_w02);

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

void func_801111E0_w02(void) {
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
        func_8010F9BC_w02();

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
        G3SparkDirs velocities = D_8011EA80_w02;

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EBF0_w02(&pos, 0.1f, 2.0f, 1, &velocities.dir[(i / 2) & 7], 1);
        }
        HuPrcVSleep();
    }

    alpha = 0xFF;
    speed = 0.0f;
    while (1) {
        G3SparkDirs velocities2 = D_8011EA80_w02;

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EBF0_w02(&pos, 0.1f, 2.0f, 1, &velocities2.dir[(i / 2) & 7], 1);
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

        space = MBMasuGet(D_8011C690_w02[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(D_8011C6A0_w02[system->star_spawn_indices[system->current_star_spawn]]);
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
        if (D_8011EBF8_w02[j] != NULL) {
            omDelPrcObj(D_8011EBF8_w02[j]);
            D_8011EBF8_w02[j] = NULL;
        }
    }

    targetStar = D_8011EBD8_w02[system->star_spawn_indices[system->current_star_spawn]];
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

// board g4: item effects (same code as ovl_48_ChillyWaters MB1Ev_ItemKeyManUse..MB1Ev_ItemAfter5)
typedef struct W02ItemExchangeWork {
    Object* unk_00;
    Object* unk_04;
    s32 unk_08;
    s32 unk_0C;
    char unk_10[0x10];
} W02ItemExchangeWork; // board g4
typedef struct W02Bytes4 {
    u8 b[4];
} W02Bytes4; // board g4
extern DecisionTreeNonLeafNode D_8011D810_w02[];
extern f32 D_8011D81C_w02[6][2];
extern s32 D_8011D84C_w02;
extern u8 D_8011D850_w02[4];
extern u8 D_8011D854_w02[4];
extern u16 D_8011D858_w02[7][2];
extern RGB D_8011D874_w02[2];
extern const f64 D_8011EB08_w02; // 1.5
extern const f64 D_8011EB10_w02; // 0.8
extern const f64 D_8011EB18_w02; // 0.8
extern s32 D_8011ECA4_w02;
extern s32 D_8011ECA8_w02;
extern Object* D_8011ECAC_w02;
extern Object* D_8011ECB0_w02;
extern s32 D_8011ECB4_w02;
extern s32 D_8011ECB8_w02;
extern Object* D_8011ECBC_w02;
extern s32 D_8011ECC0_w02[4];
extern void* D_8011ECD0_w02;
void func_80109F1C_w02(s16 arg0, s32 arg1, s16 arg2, s32 arg3);
void func_8011020C_w02(s32 arg0, s32 arg1, s32 arg2, f32* arg3, s32 arg4);

// ItemFunctions[IFUNC_KEYMAN] - throwing away a skeleton key
// ChillyWaters MB1Ev_ItemKeyManUse
void func_80111BDC_w02(void) {
    f32 sp20[2];
    Process *proc;
    void *file;
    s32 grpId;
    s32 sprId;
    s32 ret;
    s32 i;
    GW_SYSTEM* system = &GwSystem;
    s32 curPlayer = GwSystem.current_player_index;

    grpId = HuSprGrpCreate(1, 0);
    file = DataRead(D_8010197C_shared_board[1]);
    sprId = func_80055810_main(file);
    DataClose(file);
    func_80055024_main(grpId, 0, sprId, 0);
    HuSprPriSet(grpId, 0, 0x4780);
    HuSprAttrSet(grpId, 0, 0x9000);

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(0x14);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &sp20[0], &sp20[1]);

    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc,
        func_8010F6BC_w02(mbItemCursorGrpId, sp20[0], sp20[1],
                             D_8011D710_w02[system->current_player_index].x,
                             D_8011D710_w02[system->current_player_index].y,
                             -1));
    HuPrcChildWait();
    HuPrcSleep(0xA);

    func_80055140_main(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 0xA; i++, HuPrcVSleep()) {
        func_80055458_main(mbItemCursorGrpId, 0, (255 - (i * 25)));
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);

    GwPlayer[curPlayer].itemNo[MBItemSelNoGet()] = ITEM_NONE;
    MBStatusItemTPLvlSet(curPlayer, MBItemSelNoGet(), 0);
    func_800F6848_shared_board(curPlayer, MBItemSelNoGet(), &sp20[0], &sp20[1]);
    func_80054904_main(grpId, 0, sp20[0], sp20[1]);
    HuSprAttrReset(grpId, 0, 0x8000);
    MBItemRemoveEmpty(curPlayer);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

choiceLoop:
    MBDlgWinInsertCreate(0x38, 0x4100, 0, 0, 0, 0, 0);
    ret = func_80109C98_w02((s32)D_8011D810_w02, 0);
    MBDlgWinClose();
    MBDlgWinKill();

    switch (ret) {
    case 0:
        MBDlgWinInsertCreate(0x38, 0x4101, 0, 0, 0, 0, 0);
        break;
    case 1:
        MBDlgWinInsertCreate(0x38, 0x4102, 0, 0, 0, 0, 0);
        HuSprAttrSet(grpId, 0, 0x8000);
        GwPlayer[curPlayer].itemNo[MBItemFindEmpty(curPlayer)] = ITEM_SKELETON_KEY;
        MBItemRemoveEmpty(curPlayer);
        GwSystem.cur_player_used_item &= ~1;
        break;
    default:
        HuSprAttrSet(grpId, 0, 0x8000);
        func_80106B38_w02();
        D_800CB99C_main = 1;
        func_80049FB8_main();
        HuSprAttrReset(grpId, 0, 0x8000);
        goto choiceLoop;
    }

    MBDlgWinClose();
    MBDlgWinKill();

    if (ret == 0) {
        HuPrcSleep(0xA);
        for (i = 1; i < 0x40; i++, HuPrcVSleep()) {
            func_80055458_main(grpId, 0, 255.0f - (i * 3.984f));
        }
        func_80055458_main(grpId, 0, 0);
    }

    HuSprGrpKill(grpId);
    HuSprKill(sprId);
}

void func_80112124_w02(void) {
    s32 x;
    s32 y;
    s32 grpId;
    s32 idx;
    f32 scale;
    s32 alpha;

    idx = (s32)HuPrcCurrentGet()->user_data;

    grpId = HuSprGrpCreate(1, 0);
    func_80055024_main(grpId, 0, D_8011ECA8_w02, 0);
    HuSprPriSet(grpId, 0, 9);
    HuSprAttrSet(grpId, 0, 0x1000);

    MBStatusItemPosGet(D_8011ECA4_w02, 0, &x, &y);
    x = (D_8011D5C8_w02[D_8011ECA4_w02].x * 16.0f) +
         D_8011D5A8_w02[D_8011ECA4_w02].x;
    y = (D_8011D5C8_w02[D_8011ECA4_w02].y * 16.0f) +
         D_8011D5A8_w02[D_8011ECA4_w02].y;

    func_80054904_main(grpId, 0,
                        x + D_8011D81C_w02[idx][0],
                        y + D_8011D81C_w02[idx][1]);
    func_80055420_main(grpId, 0, 0xFF, 0xFF, 0xFF);
    func_80055458_main(grpId, 0, 0xFF);

    for (scale = 0.0f, alpha = 0xFF; alpha >= 0; alpha -= 0xA, scale += 0.1f) {
        HuSprScaleSet(grpId, 0, scale, scale);
        func_80055458_main(grpId, 0, alpha);
        HuPrcVSleep();
    }

    func_80055458_main(grpId, 0, 0);
    HuSprGrpKill(grpId);
    omDelPrcObj(NULL);
}

void func_80112340_w02(void) {
    Process *proc;
    void *file;
    s32 grpId;
    s32 charmSpr;
    s32 booSpr;
    s32 sfx;
    s32 x;
    s32 startX;
    s32 playerNo;
    s32 y;
    s32 i;
    s32 j;
    s32 alpha;

    playerNo = (s32)HuPrcCurrentGet()->user_data;

    file = DataRead(0x21002C);
    booSpr = func_80055810_main(file);
    DataClose(file);
    file = DataRead(0x1301BA);
    charmSpr = func_80055810_main(file);
    DataClose(file);
    file = DataRead(0x1301B9);
    D_8011ECA8_w02 = func_80055810_main(file);
    DataClose(file);

    grpId = HuSprGrpCreate(2, 2);
    func_800550F4_main(grpId, 0, 1);
    func_80055024_main(grpId, 0, booSpr, 0xC);
    HuSprPriSet(grpId, 0, 9);
    HuSprAttrSet(grpId, 0, 0x1000);
    func_800554C4_main(grpId, 0, -1);
    func_80055024_main(grpId, 1, charmSpr, 0);
    HuSprPriSet(grpId, 1, 9);
    HuSprAttrSet(grpId, 1, 0x9000);
    func_80055420_main(grpId, 1, 0xFF, 0xFF, 0xFF);
    func_80055458_main(grpId, 1, 0xFF);
    HuSprScaleSet(grpId, 1, 2.0f, 2.0f);
    func_800554C4_main(grpId, 1, 0);

    if (playerNo & 1) {
        x = 0xC8;
        HuSprAttrSet(grpId, 0, 1);
        HuSprAttrSet(grpId, 1, 1);
        func_80054904_main(grpId, 1, 0x14, -5);
    } else {
        x = 0x78;
        func_80054904_main(grpId, 1, -0x14, -5);
    }
    

    if (playerNo < 2) {
        y = -0x20;
    } else {
        y = 0x110;
    }

    HuPrcSleep(0x14);
    GwPlayer[playerNo].itemNo[MBItemFind(playerNo, ITEM_BOO_REPELLENT)] = ITEM_NONE;
    MBItemRemoveEmpty(playerNo);
    MBStatusItemIconSprReinit(playerNo);

    //TODO: this sure is some cod...
    while (1) {
        if (playerNo < 2) {
            y += 5;
            if (y > 50) {
                break;
            }
        } else {
            y -= 5;
            if (y < 210) {
                break;
            }
        }
        loop:
        func_80054904_main(grpId, 0, x, y);
        HuPrcVSleep();
    
        if (playerNo < 2) {
            y += 5;
            if (y < 51) {
                goto loop;
            }
            break;
        }
    }

    HuPrcSleep(0xA);
    HuSprAttrReset(grpId, 1, 0x8000);
    sfx = HuAudFXPlay(0x14C);
    D_8011ECA4_w02 = playerNo;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            proc = omAddPrcObj(func_80112124_w02, 0x4002, 0, 0);
            proc->user_data = (void *)i;
            HuPrcSleep(2);
        }
        HuPrcSleep(5);
    }

    HuPrcChildLink(HuPrcCurrentGet(), proc);
    HuPrcChildWait();
    HuAudFXStop(sfx);
    func_80055458_main(grpId, 1, 0);

    for (alpha = 0xFF; alpha >= 0; alpha -= 30) {
        func_80055458_main(grpId, 0, alpha);
        HuPrcVSleep();
    }

    func_80055458_main(grpId, 0, 0);
    HuSprGrpKill(grpId);
    HuSprKill(D_8011ECA8_w02);
    HuSprKill(charmSpr);
    HuSprKill(booSpr);
    omDelPrcObj(NULL);
}

// ChillyWaters MB1Ev_ItemNullUse
void func_80112734_w02(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void func_801127F0_w02(void) {
    Object* modelObj;
    f32 angle;
    Object* obj;

    obj = HuPrcCurrentGet()->user_data;
    modelObj = MBModelLinkCreate(D_8011ECAC_w02);
    HuVecCopy3F(&modelObj->coords, &obj->coords);
    HuVecCopyXYZ(&modelObj->scale, 2.0f, 2.0f, 2.0f);
    modelObj->velocity.x = obj->velocity.x + 10.0f;
    MBModelDispOn(modelObj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        modelObj->velocity.x += D_8011EB08_w02;
        if ((obj->velocity.x + 35.0f) <= modelObj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[modelObj->omObj1->model[0]].mtx, angle);
    }

    MBModelKill(modelObj);
    omDelPrcObj(NULL);
}


void func_80112944_w02(Object* arg0) {
    omAddPrcObj(func_801127F0_w02, 0x1000, 0, 0)->user_data = arg0;
}

void func_80112980_w02(void) {
    s32 *done = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *system = &GwSystem;

    while (1) {
        D_8011ECB0_w02->rot.x = -sindf(angle);
        D_8011ECB0_w02->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }

        if (*done != 0) {
            D_8011ECB0_w02->scale.x =
            D_8011ECB0_w02->scale.y =
            D_8011ECB0_w02->scale.z = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }

    D_8011ECB0_w02->scale.x =
    D_8011ECB0_w02->scale.y =
    D_8011ECB0_w02->scale.z = 0.0f;
    GwPlayer[system->current_player_index].itemNo[MBItemFind(CUR_PLAYER, ITEM_KOOPA_KARD)] = ITEM_NONE;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBModelKill(D_8011ECB0_w02);
    omDelPrcObj(NULL);
}

void func_80112944_w02(Object *);

void func_80112B10_w02(void) {
    s32 pos[2];
    UnkVibrateProcess *vib;
    Object *coin;
    void *file;
    s32 sprId;
    s32 amount;
    s32 n;
    f32 step;
    f32 frac;
    s32 done = 0;
    GW_SYSTEM *system = &GwSystem;

    mbItemCursorGrpId = HuSprGrpCreate(1, 5);
    file = DataRead(D_80101040_shared_board[GwPlayer[system->current_player_index].chr]);
    sprId = func_80055810_main(file);
    DataClose(file);
    func_80055024_main(mbItemCursorGrpId, 0, sprId, 0);
    HuSprPriSet(mbItemCursorGrpId, 0, 0xA);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
    MBStatusItemPosGet(-1, 0, &pos[0], &pos[1]);
    func_80054904_main(mbItemCursorGrpId, 0, pos[0], pos[1]);

    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);
    MBItemSelNoSet(MBItemFind(CUR_PLAYER, 0xF));
    func_8010F9BC_w02();

    D_8011ECB0_w02 = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&D_8011ECB0_w02->coords,
                &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    D_8011ECB0_w02->velocity.x = 100.0f;
    while (D_8011ECB0_w02->velocity.x > 30.0f) {
        D_8011ECB0_w02->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(func_80112980_w02, 0x4002, 0, 0)->user_data = &done;
    vib = MBPlayerVibrateObjCreate(-1, 4, 5);

    amount = GwSystem.bank_coins;
    step = (f32)amount / 30.0f;
    frac = 0.0f;
    coin = MBModelCreate(0x19, NULL);
    D_8011ECAC_w02 = coin;
    MBModelTempAllocFree(coin);
    MBModelDispOff(D_8011ECAC_w02);

    while (amount != 0) {
        frac += step;
        n = 0;
        while (frac >= 1.0f) {
            frac -= 1.0f;
            n++;
        }
        if (n != 0) {
            func_80112944_w02(D_8011ECB0_w02);
            if ((amount - n) < 0) {
                n = amount;
            }
            amount -= n;
            MBPlayerCoinAdd(system->current_player_index, n);
            HuAudFXPlay(0x106);
            GwSystem.bank_coins -= n;
            func_80107FB0_w02();
            HuPrcSleep(5);
        }
    }

    MBPlayerVibrateObjKill(vib);
    done = 1;
    HuPrcSleep(0x14);
    MBModelKill(D_8011ECAC_w02);
    MBVecForwardSet(&MBPlayerGet(CUR_PLAYER)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    func_8004ACE0_main(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 func_80112ECC_w02(u8 *arg0, s32 arg1) {
    s32 count = 0;
    s16 sp18[MB_MAX_PLAYERS];
    W02Bytes4 sp20 = *(W02Bytes4 *)D_8011EA70_w02;
    s32 i;
    s32 j;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 != 0) {
                    count = D_8011ECB4_w02 + 1;
                } else {
                    count = D_8011ECB8_w02 + 1;
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

    if (count != 0) {
        func_8005B63C_main(mbDlgWinId, 2, 2);
        for (j = 0; count != 0; j++) {
            if (--count == 0) {
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
    do {
        i = func_8005E1D8_main(mbDlgWinId, i, 1);
    } while (arg0[i] == 0);
    return i;
}

void func_80113164_w02(void) {
    Process *proc;
    s32 playerNo;
    s32 alpha;
    s32 i;

    proc = HuPrcCurrentGet();
    playerNo = (s32)proc->user_data;
    MBPlayerVibrate(playerNo, 4);

    for (alpha = 0x80; alpha > 0; alpha -= 0xA, HuPrcVSleep()) {
        for (i = 0; i < 3; i++) {
            if (GwPlayer[playerNo].itemNo[i] != ITEM_NONE) {
                MBStatusItemTPLvlSet(playerNo, i, alpha);
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if (GwPlayer[playerNo].itemNo[i] != ITEM_NONE) {
            MBStatusItemTPLvlSet(playerNo, i, 0);
        }
    }

    omDelPrcObj(NULL);
}

void func_80113270_w02(void) {
    s32 pos[2];
    s32 alpha;
    s32 i;
    s32 slot;
    s32 playerNo = (s32)HuPrcCurrentGet()->user_data;
    GW_SYSTEM* system = &GwSystem;

    for (i = 0, slot = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != ITEM_NONE) {
            MBStatusItemScaleSet(system->current_player_index, i, 1.0f, 1.0f);
            MBStatusItemPosGet(playerNo, slot, &pos[0], &pos[1]);
            MBStatusItemPosSet(system->current_player_index, i, pos[0], pos[1]);
            slot += i != MBItemSelNoGet();
        }
    }

    for (alpha = 0; alpha < 0x80; alpha += 0x14, HuPrcVSleep()) {
        for (i = 0; i < 3; i++) {
            if ((GwPlayer[system->current_player_index].itemNo[i] != ITEM_NONE) &&
                (i != MBItemSelNoGet())) {
                MBStatusItemTPLvlSet(system->current_player_index, i, alpha);
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if ((GwPlayer[system->current_player_index].itemNo[i] != ITEM_NONE) &&
            (i != MBItemSelNoGet())) {
            MBStatusItemTPLvlSet(system->current_player_index, i, 0x80);
        }
    }

    omDelPrcObj(NULL);
}

// ChillyWaters MB1Ev_ItemExchangeBox
void func_8011344C_w02(void) {
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

    func_8010F9BC_w02();
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
    targetPlayer = func_80112ECC_w02(choices, 1);
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
                    func_8011020C_w02(system->current_player_index, itemSlot, 10, &position.x, 0);
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
        process = omAddPrcObj(func_80113164_w02, 0x4800, 0, 0);
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
        process = omAddPrcObj(func_80113270_w02, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8011020C_w02(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8011020C_w02(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8011020C_w02(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_8011020C_w02(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8011020C_w02(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_8011020C_w02(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8011020C_w02(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_8011020C_w02(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                func_8011020C_w02(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8011020C_w02(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_8011020C_w02(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                func_8011020C_w02(targetPlayer, 2, 7, &target.x, 2);
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

void func_801140F8_w02(void) {
    Object* temp_s1;
    Object* temp_s0;
    W02ItemExchangeWork* temp_s2;

    temp_s2 = HuPrcCurrentGet()->user_data;
    temp_s1 = temp_s2->unk_00;
    temp_s0 = temp_s2->unk_04;
    MBMotionSet(temp_s1, -1, temp_s2->unk_08);
    HuVecCopy3F(&temp_s1->coords, &temp_s0->coords);
    temp_s1->coords.y += temp_s0->velocity.x - 10.0f;
    func_800D9A40_shared_board(temp_s1);
    while (!(MBMotionCheck(temp_s1)) && (temp_s2->unk_0C == 0)) {
        HuPrcVSleep();
    }
    MBModelKill(temp_s1);
    omDelPrcObj(NULL);
}

void func_801141B8_w02(void) {
    Object *coin;
    Object *obj;
    Process *proc;
    W02ItemExchangeWork *work;
    s32 *flag;
    s32 light;
    f32 angle;
    f32 speed;
    f32 decel;
    f32 scale;
    s32 i;

    flag = HuPrcCurrentGet()->user_data;
    coin = D_8011ECBC_w02;
    obj = MBModelCreate(0x45, NULL);
    MBModelDispOff(obj);

    light = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(light, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(light, 10.0f);
    func_8001C8A8_main(light, 1);
    HuAudFXPlay(0x24C);

    for (angle = 0.0f, speed = 2.0f; speed < 80.0f; HuPrcVSleep()) {
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        speed += 1.0f;
        if (speed > 80.0f) {
            speed = 80.0f;
        }
        func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);        
    }

    HuAudFXPlay(0x14A);
    
    while (coin->velocity.x < 110.0f) {
        coin->velocity.x += 7.0f;
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);
        HuPrcVSleep();
    }

    for (*flag = 0; *flag == 0; HuPrcVSleep()) {
        if (D_8011D84C_w02 != -1) {
            HuVecCopy3F(&coin->coords,
                        &MBPlayerGet(D_8011D84C_w02)->player_obj->coords);
            func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                               coin->coords.z);
        }        
    }

    HuAudFXPlay(0x14B);
    
    decel = 3.0f;
    while (coin->velocity.x > 30.0f) {
        coin->velocity.x -= decel;
        if (decel > 1.0f) {
            decel -= 0.2f;
        }
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);
        HuPrcVSleep();
    }

    while (1) {
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (speed > 15.0f) {
            speed -= 3.0f;
        } else {
            speed -= 0.5f;
        }
        if (speed < 1.0f) {
            break;
        }
        func_8000CFA4_main(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);
        HuPrcVSleep();
    }

    func_8000D044_main(light);
    proc = omAddPrcObj(func_801140F8_w02, 0x4800, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, sizeof(W02ItemExchangeWork));
    proc->user_data = work;
    work->unk_00 = obj;
    work->unk_04 = coin;
    work->unk_08 = 0;
    work->unk_0C = 0;
    HuPrcSleep(3);

    *flag = 0;
    HuAudFXPlay(0x24D);
    
    for (i = 0, scale = 0.1f; i < 0x14; i++) {
        scale += 0.044999998f;
        func_8001D558_main(coin->omObj1->model[0], scale, scale * 10.0f, 1);
        HuPrcVSleep();
    }

    MBModelKill(coin);
    omDelPrcObj(NULL);
}

// ChillyWaters MB1Ev_ItemGambleCoin
void func_801146E8_w02(void) {
    s32 sp20;
    GW_SYSTEM* system = &GwSystem;
    Object* temp_s3;
    Object* temp_v0;
    Object* temp_v0_2;
    Process* temp_s4;
    s32 temp_a0;
    s32 var_s1;
    s32 sel;
    s32 i;
    u32 var_v1_3;

    func_8010F9BC_w02();
    GwPlayer[system->current_player_index].itemNo[MBItemFind(-1, 0x11)] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    temp_v0 = MBModelCreate(0x3EU, NULL);
    Hu3DModelScaleSet(temp_v0->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    MBModelTempAllocFree(temp_v0);
    temp_v0->velocity.x = 30.0f;
    MBModelDispOff(temp_v0);
    temp_v0_2 = MBModelCreate(0x43U, NULL);
    D_8011ECBC_w02 = temp_v0_2;
    func_8001C2FC_main(temp_v0_2->omObj1->model[0], 0x20000, 0x20000);
    func_8001C448_main(temp_v0_2->omObj1->model[0]);
    func_8001C954_main(temp_v0_2->omObj1->model[0]);
    func_8001C514_main(temp_v0_2->omObj1->model[0]);
    HuVecCopy3F(&temp_v0_2->coords, &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    func_8001C814_main(temp_v0_2->omObj1->model[0], 2, 1);
    temp_v0_2->velocity.x = 100.0f;
    HuAudFXPlay(0x14B);
    while (temp_v0_2->velocity.x > 30.0f) {
        temp_v0_2->velocity.x -= 1.0f;
        HuPrcVSleep();
    } 
loop:
    MBDlgWinInsertCreate(-1, 0x5C00, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00, GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    sel = func_80109C98_w02(NULL, 0);
    MBDlgWinClose();
    MBDlgWinKill();

    switch(sel) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            sel = func_800EF0D8_shared_board(0);
            break;
        default:
            func_80106B38_w02();
            D_800CB99C_main = 1;
            func_80049FB8_main();
            goto loop;
    }

    sp20 = 1;
    omAddPrcObj(func_801141B8_w02, 0x4002U, 0, 0)->user_data = &sp20;
    while(sp20) {
        HuPrcVSleep();
    }
    
    if (sel != system->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        D_8011D84C_w02 = sel;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(sel)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(sel)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(0xA);
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(0x1E);
        D_8011D84C_w02 = sel;
    }
    sp20 = 1;
    while (sp20) {
        HuPrcVSleep();
    }
    
    temp_s3 = MBPlayerGet(sel)->player_obj;
    temp_s4 = func_800EDB98_shared_board(temp_v0, 5.0f, 2.0f);
    HuVecCopy3F(&temp_v0->coords, &temp_s3->coords);
    func_800D9A40_shared_board(temp_v0);
    temp_v0->scale.x = temp_v0->scale.y = temp_v0->scale.z = 0.0f;
    while (temp_v0->scale.x < 1.0f) {
        temp_v0->scale.x = temp_v0->scale.y = temp_v0->scale.z += 0.2f;
        HuPrcVSleep();
    }
    MBPlayerVibrate(sel, 4);
    HuAudFXPlay(0x2A1);
    if (GwPlayer[sel].coin != 0) {
        func_80109F1C_w02(0xA, 0x2F00, -1, sel);
        GwPlayer[sel].gameCoin = GwPlayer[sel].coin;
        MBCoinChangeCreate(sel, -GwPlayer[sel].coin);
        MBCoinTakeCreate(sel, -GwPlayer[sel].coin);
        HuPrcSleep(0x1E);
        func_80109F1C_w02(0xA, 0x2F02, -1, sel);
        omDelPrcObj(temp_s4);
        while(10.0f <= temp_v0->velocity.x) {
            temp_v0->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        HuPrcSleep(0x1E);
        while (temp_v0->velocity.x < 100.0f) {
            temp_v0->velocity.x += 4.0f;
            temp_s3->velocity.x += 4.0f;
            HuPrcVSleep();
        }
    } else {
        func_80109F1C_w02(0xA, 0x2F01, -1, sel);
        omDelPrcObj(temp_s4);
            while (temp_v0->velocity.x <= 100.0f) {
                temp_v0->velocity.x += 4.0f;
                HuPrcVSleep();
            } 
        MBModelKill(temp_v0);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(CUR_PLAYER)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        return;
    }
    
    if ((MBPlayerComCheck(sel) != 0) && (system->show_com_minigames != 0)) {
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBModelKill(temp_v0);
        func_800EE688_shared_board(temp_s3, 0.0f, 0.0f);
        temp_s3->velocity.x = 0.0f;
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        temp_a0 = MBRand(100.0f) + 1;
        for (i = 0; i < 7; i++) {
            if (D_8011D858_w02[i][1] >= temp_a0) {
                break;
            }
        }
        if (D_8011D858_w02[i][0] != 0) {
            char sp28[16]; // required to be here or the codegen changes(?!)
            
            var_s1 = GwPlayer[sel].gameCoin * D_8011D858_w02[i][0];
            if (var_s1 >= 1000) {
                var_s1 = 999;
            }
            sprintf(sp28, D_8011EA74_w02, var_s1);
            MBDlgWinInsertCreate(-1, 0x2F03, (s32)sp28, 0, 0, 0, 0);
            MBDlgWinClose();
            MBDlgWinKill();
            MBCoinChangeCreate(sel, var_s1);
            MBCoinTakeCreate(sel, var_s1);
            HuPrcSleep(0x14);
        } else {
            MBDlgWinExec(-1, 0x2F04);
        }
        HuPrcSleep(0xA);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(CUR_PLAYER)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
    } else {
        if (func_800DEB2C_shared_board(system->current_player_index) == 3) {
            GWBoardFlagSet(0x17);
        } else {
            GWBoardFlagClear(0x17);
        }
        for (i = 0; i < 4; i++) {
            GwPlayer[i].group = 1;
        }
        MBPlayerGet(sel)->group = 0;
        temp_a0 = MBRand(100.0f);
        for(var_v1_3 = 0; var_v1_3 < 3; var_v1_3++) {
            if (temp_a0 < D_8011D854_w02[var_v1_3]) {
                break;
            }
        }
    
        if (var_v1_3 == 3) {
            var_v1_3 = 2;
        }
        system->minigame_index = D_8011D850_w02[var_v1_3];
        GwSystem.playerIndexVisitingBowser = sel;
        func_800FC998_shared_board();
        func_8004A0E0_main();
        func_800FF7F0_shared_board(2);
        HuPrcSleep(-1);
    }
}

// ChillyWaters MB1Ev_After5ItemMove
void func_80114FF4_w02(s32 sprGrp, s32 frames, f32 *dest) {
    f32 x;
    f32 y;
    f32 stepX;
    f32 stepY;
    s32 i;

    MBStatusSprPosGet(sprGrp, 0, &x, &y);
    stepX = (dest[0] - x) / frames;
    stepY = (dest[1] - y) / frames;

    for (; frames != 0; frames--) {
        x += stepX;
        y += stepY;
        func_80054904_main(sprGrp, 0, x, y);
        HuPrcVSleep();
    }

    func_80054904_main(sprGrp, 0, dest[0], dest[1]);
}

// ChillyWaters MB1Ev_After5LineShow
void func_8011512C_w02(omObjData *obj) {
    s32 temp_s1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s3;
    s32 var_v0;
    s32 i;

    temp_s1 = (s32)HuPrcCurrentGet()->user_data;
    var_s3 = 10;

    switch (temp_s1) {
        case 0:
            func_80054904_main(D_8011ECC0_w02[temp_s1], 0, 0xB1, 0x2C);
            break;
        case 1:
            func_80054904_main(D_8011ECC0_w02[temp_s1], 0, 0x7A, 0x39);
            break;
        default:
            func_80054904_main(D_8011ECC0_w02[temp_s1], 0, 0xA0, 0x98);
            var_s3 = 30;
            break;
    }

    HuSprAttrReset(D_8011ECC0_w02[temp_s1], 0, 0x8000);
    for (i = 0; i < 255; i += 255 / var_s3) {
        func_80055458_main(D_8011ECC0_w02[temp_s1], 0, i);
        HuPrcVSleep();
    }

    func_80055458_main(D_8011ECC0_w02[temp_s1], 0, 0xFF);
    omDelPrcObj(0);
}

// ChillyWaters MB1Ev_After5NumFade
void func_8011529C_w02(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i, j;

    for (i = 0; i <= 0; i++) {
        sp18.r = D_8011D874_w02[i].r;
        sp18.g = D_8011D874_w02[i].g;
        sp18.b = D_8011D874_w02[i].b;

        sp28.r = (D_8011D874_w02[i + 1].r - sp18.r) / 30;
        sp28.g = (D_8011D874_w02[i + 1].g - sp18.g) / 30;
        sp28.b = (D_8011D874_w02[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            func_80055420_main(D_8011ECC0_w02[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        func_80055420_main(D_8011ECC0_w02[3], 0, D_8011D874_w02[i + 1].r, D_8011D874_w02[i + 1].g, D_8011D874_w02[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

// ChillyWaters MB1Ev_After5Effect
void func_80115464_w02(void) {
    Object *obj;
    s32 *state;
    f32 spin;
    f32 scale;

    state = HuPrcCurrentGet()->user_data;
    HuAudFXPlay(0x143);
    obj = D_8011ECD0_w02;
    func_800D9A40_shared_board(obj);

    for (spin = 0.0f, scale = 1.0f; scale < 18.0f; scale += D_8011EB10_w02) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    while (*state != 1) {
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    for (; scale < 40.0f; scale += D_8011EB18_w02) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    while (*state != 2) {
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(obj);
    omDelPrcObj(NULL);
}


// main function for using a wacky watch?
// ChillyWaters MB1Ev_ItemAfter5
void func_801156E8_w02(void) {
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
    s32 *temp_s0;
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
        D_8011ECC0_w02[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = func_80055810_main(temp_v0);
        DataClose(temp_v0);
        func_80055024_main(D_8011ECC0_w02[i], 0, sp18[i], 0);
        HuSprPriSet(D_8011ECC0_w02[i], 0, 0x4780U);
        HuSprAttrSet(D_8011ECC0_w02[i], 0, 0x980CU);
        func_80055458_main(D_8011ECC0_w02[i], 0, 0U);
        func_80055420_main(D_8011ECC0_w02[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    D_8011ECD0_w02 = temp_v0_3;
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
    func_80114FF4_w02(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    func_80114FF4_w02(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(func_8011512C_w02, 0x4002, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    func_80114FF4_w02(temp_s4, 0xA, sp28);
    HuPrcChildWait();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(func_8011512C_w02, 0x4002, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    func_80114FF4_w02(temp_s4, 0xA, sp28);
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
            temp_v0_4 = omAddPrcObj(func_8011512C_w02, 0x4002, 0, 0);
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
        HuSprAttrSet(D_8011ECC0_w02[i], 0, 0x8000);
    }

    HuSprAttrReset(D_8011ECC0_w02[3], 0, 0x8000U);
    func_80055458_main(D_8011ECC0_w02[3], 0, 0xFFU);
    func_80054904_main(D_8011ECC0_w02[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_8011529C_w02, 0x4002, 0, 0));
    sp40 = 0;
    omAddPrcObj(func_80115464_w02, 0x4002, 0, 0)->user_data = &sp40;
    HuPrcChildWait();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(D_8011ECC0_w02[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
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
        HuSprScaleSet(D_8011ECC0_w02[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(D_8011ECC0_w02[i]);
        HuSprKill(sp18[i]);
    }

    WipeCreateIn(0xB, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = WATCH_USED;
}


// board g5: functions func_80115FEC_w02..func_801199EC_w02 (Waluigi's Island w06 has the same code at +0x1828)

typedef s16 G5SpaceTriple[3];
typedef BranchLink G5BranchPair[2];

void func_80106B94_w02(void);
void func_80106C64_w02(void);
void func_8010FB8C_w02(void);
s32 func_80112ECC_w02(u8 *arg0, s32 arg1);
void func_801161E4_w02(s32 arg0);
void func_8011625C_w02(void);
void func_801162C0_w02(omObjData *obj);
void func_8011646C_w02(s32 arg0, s32 arg1);
void func_8011656C_w02(s32 arg);
void func_80116A74_w02(void);
void func_8011703C_w02(void);
extern Object *D_8011ECD8_w02[4];
extern omObjData *D_8011ECE8_w02[4];
extern s32 D_8011ECF8_w02;
extern s32 D_8011ECFC_w02;
extern Vec2f D_8011D750_w02[]; /* splat labels D_8011D750 (x) / D_8011D754 (rest): one Vec2f[4] */
extern Vec2f D_8011D770_w02[]; /* D_8011D770 / D_8011D774 likewise */

void func_80115FEC_w02(G5SpaceTriple *masu, G5BranchPair *links, DecisionTreeNonLeafNode **trees) {
    GW_PLAYER *player;
    UnkEA790Struct *win;
    BranchLink *link;
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
    func_80106B94_w02();
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
    func_80106C64_w02();

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

void func_801161E4_w02(s32 arg0) {
    if (D_8011ECE8_w02[arg0] != NULL) {
        omDelObj(D_8011ECE8_w02[arg0]);
        D_8011ECE8_w02[arg0] = NULL;
    }
    if (D_8011ECD8_w02[arg0] != NULL) {
        MBModelKill(D_8011ECD8_w02[arg0]);
        D_8011ECD8_w02[arg0] = NULL;
    }
}

void func_8011625C_w02(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = D_8011ECE8_w02[i];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011ECE8_w02[i] = NULL;
        }
    }
}

void func_801162C0_w02(omObjData *obj) {
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
        Object *effectObj = D_8011ECD8_w02[playerIdx];

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

void func_8011646C_w02(s32 arg0, s32 arg1) {
    GW_PLAYER *player = MBPlayerGet(arg0);
    Object *obj;
    u8 modelId;

    if (D_8011ECD8_w02[arg0] == NULL) {
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
        D_8011ECD8_w02[arg0] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        func_800D9A40_shared_board(D_8011ECD8_w02[arg0]);
    }
}

void func_8011656C_w02(s32 arg) {
    D_8011ECE8_w02[arg] = omAddObj(0x3FFF, 0, 0, -1, func_801162C0_w02);
    D_8011ECE8_w02[arg]->work[0] = arg;
    D_8011ECE8_w02[arg]->work[1] = 0;
    D_8011ECE8_w02[arg]->work[2] = 0;
    D_8011ECE8_w02[arg]->rot.x = (f32)MBRand(360.0f);
    D_8011ECE8_w02[arg]->trans.x = 0;
}

void func_80116608_w02(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        D_8011ECE8_w02[i] = NULL;
        D_8011ECD8_w02[i] = NULL;
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
            func_8011646C_w02(i, idx);
            func_8011656C_w02(i);
        }
    }
    func_800F8D54_shared_board(func_8011625C_w02);
}

void func_80116708_w02(void) {
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
            if (D_8011ECD8_w02[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011ECD8_w02[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_801161E4_w02(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (D_8011ECD8_w02[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011ECD8_w02[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_801161E4_w02(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}

void func_80116914_w02(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        func_800DCA64_shared_board(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (D_8011ECD8_w02[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011ECD8_w02[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_801161E4_w02(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void func_80116A74_w02(void) {
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

void func_80116AC4_w02(void) {
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
    choice = func_80109C98_w02(2, D_8011ECFC_w02);
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

    func_801161E4_w02(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    func_8011646C_w02(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011ECD8_w02[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011ECD8_w02[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    func_8011656C_w02(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(func_80116A74_w02, 0x4002, 0, 0)->user_data = vib;
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
            HuVecCopyXYZ(&D_8011ECD8_w02[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&D_8011ECD8_w02[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        func_801161E4_w02(loc->current_player_index);
        func_800DCA64_shared_board(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}

void func_8011703C_w02(void) {
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
            if (D_8011ECD8_w02[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011ECD8_w02[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_801161E4_w02(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (D_8011ECD8_w02[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011ECD8_w02[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_801161E4_w02(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}

void func_8011720C_w02(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        func_800DCA64_shared_board(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (D_8011ECD8_w02[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011ECD8_w02[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_801161E4_w02(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void func_80117344_w02(void) {
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
    choice = func_80109C98_w02(2, D_8011ECF8_w02);
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

    func_801161E4_w02(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    func_8011646C_w02(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011ECD8_w02[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011ECD8_w02[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    func_8011656C_w02(targetPlayer);
    omAddPrcObj(func_80116A74_w02, 0x4002, 0, 0)->user_data = vib;
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
        func_8011703C_w02();
    }
}

void func_801177C8_w02(void) {
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

    func_8010F9BC_w02();
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
    targetPlayer = func_80112ECC_w02(choices, 0);
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
                       D_8011D770_w02[system->current_player_index].x,
                       D_8011D770_w02[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6BC_w02(-1,
                                            D_8011D770_w02[system->current_player_index].x,
                                            D_8011D770_w02[system->current_player_index].y,
                                            D_8011D750_w02[system->current_player_index].x,
                                            D_8011D750_w02[system->current_player_index].y, 5));
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
    func_8010FB8C_w02();
}

/* board g5: D_8011EB20_w02 (five sprite files) and D_8011EB34_w02 (base position, then four
   offsets), copied whole onto the stack by func_80117E70_w02. */
typedef struct G5GateFiles {
    s32 file[5];
} G5GateFiles;
typedef struct G5GatePos {
    Vec2f pos[5];
} G5GatePos;
extern G5GateFiles D_8011EB20_w02;
extern G5GatePos D_8011EB34_w02;

/* The current player picks one of four gates not yet opened (bits of boardData.halfWordBytes[0])
   with left/right and A (a COM player: random moves, then the tenth frame); marks it open and
   returns its index. */
s32 func_80117E70_w02(void) {
    G5GateFiles files;
    G5GatePos pos;
    s32 turn;
    UnkBoard8 *gates;
    UnkBoard8 *cursor;
    Unk3 *help0;
    Unk3 *help1;
    void *data;
    s32 i;
    s32 sel;
    s32 prev;
    s32 timer;

    turn = MBPlayerTurnGet();
    files = D_8011EB20_w02;
    pos = D_8011EB34_w02;
    gates = func_800F2C48_shared_board(5, 2);
    for (i = 0; i < 5; i++) {
        data = DataRead(files.file[i]);
        gates->model[i] = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(gates->spriteGroup, i, gates->model[i], 0);
        HuSprAttrReset(gates->spriteGroup, i, 0xFFFF);
        HuSprAttrSet(gates->spriteGroup, i, 0);
        HuSprPriSet(gates->spriteGroup, i, 0x1000);
        func_80054904_main(gates->spriteGroup, i, pos.pos[i].x, pos.pos[i].y);
    }
    for (i = 1; i < 5; i++) {
        if ((GwSystem.boardData.halfWordBytes[0] >> (i - 1)) & 1) {
            HuSprAttrSet(gates->spriteGroup, i, 0x8000);
        }
    }
    cursor = func_800F2C48_shared_board(1, 2);
    data = DataRead(0x1301E6);
    cursor->model[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(cursor->spriteGroup, 0, cursor->model[0], 0);
    HuSprAttrReset(cursor->spriteGroup, 0, 0xFFFF);
    HuSprAttrSet(cursor->spriteGroup, 0, 0);
    HuSprPriSet(cursor->spriteGroup, 0, 0xFFF);
    for (i = 0; i < 4; i++) {
        if (!((GwSystem.boardData.halfWordBytes[0] >> i) & 1)) {
            break;
        }
    }
    sel = i;
    func_80054904_main(cursor->spriteGroup, 0, pos.pos[0].x + pos.pos[sel + 1].x,
                       pos.pos[0].y + pos.pos[sel + 1].y - 36.0f);
    help0 = func_800E210C_shared_board(0, 0xB4, 1);
    help1 = func_800E210C_shared_board(1, 0xC2, 1);
    timer = 10;
    while (TRUE) {
        prev = sel;
        HuPrcVSleep();
        if (MBPlayerComCheck(-1)) {
            if (--timer == 0) {
                HuAudFXPlay(0x18E);
                break;
            }
            if (timer % 3 != 0) {
                continue;
            }
            if (MBRand(5.0f) == 0) {
                goto left;
            }
            if (MBRand(5.0f) == 0) {
                goto right;
            }
            continue;
        }
        if (D_800C9520_main[GwPlayer[turn].pad] & 0x8000) {
            HuAudFXPlay(0x18E);
            break;
        }
        if (D_800C9520_main[GwPlayer[turn].pad] & 0x200) {
        left:
            do {
                if (--sel < 0) {
                    sel = 3;
                }
            } while ((GwSystem.boardData.halfWordBytes[0] >> sel) & 1);
        }
        if (D_800C9520_main[GwPlayer[turn].pad] & 0x100) {
        right:
            do {
                sel++;
                sel = (sel < 4) ? sel : 0;
            } while ((GwSystem.boardData.halfWordBytes[0] >> sel) & 1);
        }
        if (prev != sel) {
            func_80054904_main(cursor->spriteGroup, 0, pos.pos[0].x + pos.pos[sel + 1].x,
                               pos.pos[0].y + pos.pos[sel + 1].y - 36.0f);
        }
    }
    GwSystem.boardData.halfWordBytes[0] |= 1 << sel;
    func_80108870_w02();
    func_80054904_main(cursor->spriteGroup, 0, pos.pos[0].x + pos.pos[sel + 1].x,
                       pos.pos[0].y + pos.pos[sel + 1].y - 16.0f);
    HuSprAttrSet(gates->spriteGroup, sel + 1, 0x8000);
    HuPrcSleep(20);
    MBHelpWinKill(help0);
    MBHelpWinKill(help1);
    func_800F2CA4_shared_board(gates);
    func_800F2CA4_shared_board(cursor);
    return sel;
}

/* board g5: func_80118480_w02 data. D_8011D8B8_w02 is one motion list (count, then ids; splat
   labels its ids word D_8011D8BC_w02); D_8011D8F8_w02 points at one per character; the model
   number table after it (s32[8], low byte read) has no label of its own at 0x8011D918 (splat's
   D_8011D91B_w02 is its last byte): D_8011D918_w02 is an undefined_syms.txt alias. */
typedef struct G5MotList {
    /* 0x00 */ u32 count;
    /* 0x04 */ s32 ids[1]; /* [count] */
} G5MotList;
extern DecisionTreeNonLeafNode *D_8011CFE8_w02[];
extern DecisionTreeNonLeafNode D_8011CFF4_w02[];
extern DecisionTreeNonLeafNode D_8011D00C_w02[];
extern DecisionTreeNonLeafNode D_8011D030_w02[];
extern DecisionTreeNonLeafNode D_8011D048_w02[];
extern s16 D_8011D8A4_w02[][3];
extern BranchLink D_8011D8AC_w02[][2];
extern G5MotList D_8011D8B8_w02;
extern G5MotList *D_8011D8F8_w02[8];
extern s32 D_8011D918_w02[8];
extern s16 D_8011D938_w02[];
extern s16 D_8011D940_w02[];

// Masked 0, raw 74 (1110 instructions): register allocation only (model/from in s6/s4 swapped,
// the loop's float constants in other registers, win/i in s2/s0). Logic checked against the asm.
#ifdef NON_MATCHING
/* Junction event at the gates: from link 0x57/0xA the player picks a gate (func_80117E70_w02);
   the right one launches the player across to the far space (0x82/0x83) and resets the gates,
   a wrong one walks on. From 0x83/0xC or 0x2A/0x82: a two- or three-way path choice. */
void func_80118480_w02(void) {
    Vec target;
    Vec diff;
    s16 spaces[2];
    GW_PLAYER *player;
    Object *model;
    Object *fx;
    UnkEA790Struct *win;
    SpaceData *from;
    SpaceData *to;
    s32 dir;
    s16 link;
    s32 i;
    u32 j;
    s32 count;
    f32 scale;
    u32 *motion;
    GW_SYSTEM *system;

    player = MBPlayerGet(-1);
    link = MBMasuLinkMasuIdGet(player->blink, player->bidx);
    system = &GwSystem;
    spaces[0] = 0x82;
    spaces[1] = 0x83;
    switch (link) {
    case 0x57:
    case 0xA:
        func_80115FEC_w02(D_8011D8A4_w02, D_8011D8AC_w02, D_8011CFE8_w02);
        dir = MBMasuLinkMasuIdGet(player->nlink, player->nidx) != 0x2A;
        func_800DBEC0_shared_board(system->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 5, 0x77);
        MBDlgWinExec(0x3B, 0x600);
        if (func_80117E70_w02() == GwSystem.boardData.halfWordBytes[1]) {
            MBPlayerMotionLoad(system->current_player_index, 5, 0x1A);
            MBPlayerMotionLoad(system->current_player_index, 6, 0xF);
            if (GwPlayer[system->current_player_index].itemTurn == 0) {
                HuPrcVSleep();
                for (i = 1; i < 8; i++) {
                    for (j = 0; j < D_8011D8B8_w02.count; j++) {
                        D_8011D8F8_w02[i]->ids[j] = func_80017BB8_main(i, D_8011D8B8_w02.ids[j]);
                    }
                }
                model = MBModelCreate(D_8011D918_w02[GwPlayer[system->current_player_index].chr],
                                      (u32 *)D_8011D8F8_w02[GwPlayer[system->current_player_index].chr]);
                MBModelTempAllocFree(model);
                model->flags |= 1;
                MBMotionSet(model, 0, 2);
                func_8001C92C_main(model->omObj1->model[0], 0.5f);
                MBModelDispOff(model);
            } else {
                model = player->player_obj;
            }
            from = MBMasuGet(spaces[dir]);
            HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &from->coords,
                                                                    &player->player_obj->coords, 20));
            MBPlayerMotionSet(-1, 0, 2);
            func_8001C92C_main(player->player_obj->omObj1->model[0], 0.5f);
            MBVecDirGet(&player->player_obj->coords, &from->coords, &player->player_obj->rot);
            HuPrcChildWait();
            HuAudFXPlay(0x18F);
            HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&D_8011C8E0_w02->coords, &from->coords,
                                                                    &D_8011C8E0_w02->coords, 10));
            HuPrcSleep(2);
            MBVecDirGet(&player->player_obj->coords, &D_8011C8E0_w02->coords, &diff);
            func_800ED128_shared_board(&player->player_obj->rot, &diff, &player->player_obj->rot, 5);
            HuPrcSleep(6);
            MBModelDispOff(D_8011C8E0_w02);
            HuAudFXPlay(0x190);
            fx = MBModelFileCreate(0xB0013, -1, 10.0f, 0.0f, NULL);
            func_8001C8E4_main(fx->omObj1->model[0], 0);
            func_8001C258_main(fx->omObj1->model[0], 0x180, 0);
            func_8001C448_main(fx->omObj1->model[0]);
            func_8001C814_main(fx->omObj1->model[0], 2, 0);
            func_8001C92C_main(fx->omObj1->model[0], 0.5f);
            HuVecCopy3F(&fx->coords, &player->player_obj->coords);
            from = MBMasuGet(spaces[dir]);
            to = MBMasuGet(spaces[dir ^ 1]);
            HuVecCopy3F(&target, &player->player_obj->coords);
            MBCameraFocusModeSet(4);
            MBCameraFocusVecSet(&target);
            MBPlayerPosMoveCreate(&target, &to->coords, &target, 60);
            MBPlayerVibrate(-1, 4);
            MBVecForwardSet(&player->player_obj->rot);
            MBPlayerMotionSet(GwSystem.current_player_index, 5, 2);
            func_8001C92C_main(player->player_obj->omObj1->model[0], 0.5f);
            player->player_obj->flags |= 1;
            HuVecSubtract(&diff, &to->coords, &from->coords);
            player->stat |= 4;
            mbItemBtnF = 0;
            func_8004ACE0_main(0x286, system->current_player_index);
            if (GwPlayer[system->current_player_index].itemTurn == 0) {
                MBModelDispOff(player->player_obj);
                HuVecCopy3F(&model->coords, &player->player_obj->coords);
                HuVecCopy3F(&model->rot, &player->player_obj->rot);
                MBModelDispOn(model);
            } else {
                model = player->player_obj;
            }
            for (i = 0; i <= 180; i += 3) {
                player->player_obj->velocity.x = sindf(i) * 100.0f;
                model->velocity.x = sindf(i) * 100.0f;
                if (i < 90) {
                    player->player_obj->coords.z = sindf(i) * 100.0f + from->coords.z + i * diff.z / 90.0f;
                    player->player_obj->coords.x = sindf(i) * 10.0f + from->coords.x + i * diff.x / 90.0f;
                    model->coords.z = sindf(i) * 100.0f + from->coords.z + i * diff.z / 90.0f;
                    model->coords.x = sindf(i) * 10.0f + from->coords.x + i * diff.x / 90.0f;
                } else {
                    player->player_obj->coords.z = sindf(i) * 100.0f + to->coords.z;
                    player->player_obj->coords.x = sindf(i) * 10.0f + to->coords.x;
                    model->coords.z = sindf(i) * 100.0f + to->coords.z;
                    model->coords.x = sindf(i) * 10.0f + to->coords.x;
                }
                if (i < 90) {
                    scale = i / 40.0f;
                } else {
                    scale = (180 - i) / 40.0f;
                }
                scale += 1.0f;
                if (scale < 1.0f) {
                    scale = 1.0f;
                }
                HuVecCopyXYZ(&player->player_obj->scale, scale, scale, scale);
                HuVecCopyXYZ(&model->scale, scale, scale, scale);
                HuPrcVSleep();
            }
            if (GwPlayer[system->current_player_index].itemTurn == 0) {
                MBModelDispOn(player->player_obj);
                MBModelKill(model);
            }
            mbItemBtnF = 1;
            player->stat &= ~4;
            player->player_obj->flags &= ~1;
            HuVecCopy3F(&player->player_obj->coords, &to->coords);
            player->player_obj->velocity.x = 0.0f;
            MBCameraFocusModeSet(1);
            MBPlayerMotionSet(GwSystem.current_player_index, 4, 2);
            func_8001C92C_main(player->player_obj->omObj1->model[0], 1.0f);
            HuPrcSleep(20);
            HuVecCopy3F(&D_8011C8E0_w02->coords, &MBMasuGet(0x7B)->coords);
            MBModelDispOn(D_8011C8E0_w02);
            MBModelKill(fx);
            MBDlgResultWinExec(0x601);
            MBPlayerMotionSet(GwSystem.current_player_index, 6, 0);
            MBPlayerMotionWait(GwSystem.current_player_index);
            MBPlayerMotionSet(GwSystem.current_player_index, -1, 2);
            motion = D_80101734_shared_board[0];
            for (i = 6; i != 0; i--) {
                motion++;
            }
            MBPlayerMotionLoad(system->current_player_index, 5, ((u16 *)motion)[1]);
            motion = D_80101734_shared_board[0];
            for (i = 7; i != 0; i--) {
                motion++;
            }
            MBPlayerMotionLoad(system->current_player_index, 6, ((u16 *)motion)[1]);
            GwSystem.boardData.halfWordBytes[0] = 0;
            GwSystem.boardData.halfWordBytes[1] = MBRand(4.0f);
            func_80108870_w02();
            if (dir == 0) {
                MBMoveMasuSet(system->current_player_index, 0xD, 0);
                MBMoveNextMasuSet(system->current_player_index, 4, 0);
            } else {
                MBMoveMasuSet(system->current_player_index, 0xC, 0);
                MBMoveNextMasuSet(system->current_player_index, 6, 0);
            }
        } else {
            HuPrcSleep(2);
            from = MBMasuGet(spaces[dir]);
            HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &from->coords,
                                                                    &player->player_obj->coords, 20));
            MBPlayerMotionSet(-1, 0, 2);
            func_8001C92C_main(player->player_obj->omObj1->model[0], 0.5f);
            MBVecDirGet(&player->player_obj->coords, &from->coords, &player->player_obj->rot);
            HuPrcChildWait();
            if (dir == 0) {
                MBMoveMasuSet(system->current_player_index, 0xC, 0);
                MBMoveNextMasuSet(system->current_player_index, 6, 0);
            } else {
                MBMoveMasuSet(system->current_player_index, 0xD, 0);
                MBMoveNextMasuSet(system->current_player_index, 4, 0);
            }
            HuPrcSleep(5);
        }
        func_800DB884_shared_board(system->current_player_index);
        HuPrcSleep(10);
        break;
    case 0x83:
    case 0xC:
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, 0x77);
        HuPrcSleep(8);
        MBDlgResultWinExec(0x602);
        MBPlayerMotionSet(-1, -1, 2);
        HuPrcVSleep();
        func_80106B94_w02();
        win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011D938_w02);
        func_800D742C_shared_board(win, GwSystem.current_player_index, 0);
        if (MBPlayerComCheck(-1)) {
            if (MBComTreeExec(D_8011CFF4_w02) == 0) {
                count = 0;
            } else if (MBComTreeExec(D_8011D00C_w02) != 0) {
                count = 2;
            } else {
                count = 1;
            }
            for (i = 0; i < count; i++) {
                func_800D7250_shared_board(win, -2);
            }
            func_800D7250_shared_board(win, -4);
        }
        count = func_800D7518_shared_board(win);
        func_800D6CA0_shared_board(win);
        func_80106C64_w02();
        switch (count) {
        case 0:
            MBMoveNextMasuSet(-1, 2, 0xE);
            player->rev |= 1;
            break;
        case 1:
            MBMoveNextMasuSet(-1, 0xA, 8);
            player->rev |= 1;
            break;
        default:
            MBMoveNextMasuSet(-1, 6, 0);
            player->rev &= ~1;
            break;
        }
        break;
    case 0x2A:
    case 0x82:
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, 0x77);
        HuPrcSleep(8);
        MBDlgResultWinExec(0x602);
        MBPlayerMotionSet(-1, -1, 2);
        HuPrcVSleep();
        func_80106B94_w02();
        win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011D940_w02);
        func_800D742C_shared_board(win, GwSystem.current_player_index, 0);
        if (MBPlayerComCheck(-1)) {
            if (MBComTreeExec(D_8011D030_w02) == 0) {
                count = 0;
            } else if (MBComTreeExec(D_8011D048_w02) != 0) {
                count = 2;
            } else {
                count = 1;
            }
            for (i = 0; i < count; i++) {
                func_800D7250_shared_board(win, -2);
            }
            func_800D7250_shared_board(win, -4);
        }
        count = func_800D7518_shared_board(win);
        func_800D6CA0_shared_board(win);
        func_80106C64_w02();
        switch (count) {
        case 0:
            MBMoveNextMasuSet(-1, 4, 0);
            player->rev &= ~1;
            break;
        case 1:
            MBMoveNextMasuSet(-1, 2, 0xE);
            player->rev |= 1;
            break;
        default:
            MBMoveNextMasuSet(-1, 0xA, 8);
            player->rev |= 1;
            break;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80118480_w02);
#endif

/* board g5: the model effect func_80119244_w02 sets up (hmfman's vertex-scatter work, HmfModel.unkBC,
   13F90.c's HmfFxWork) with func_80119680_w02 as its update: one G5FxPart per face group. */
typedef struct G5FxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 scale; /* > 0 while live */
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ Vec unk24;
} G5FxPart; /* size 0x30 */

typedef struct G5FxWork {
    /* 0x00 */ s16 motion;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 dist;
    /* 0x0C */ f32 speed;
    /* 0x10 */ char unk10[8];
    /* 0x18 */ void (*hook)(s16);
    /* 0x1C */ Vec center;
    /* 0x28 */ Vec verts[4];
    /* 0x58 */ G5FxPart *parts;
} G5FxWork; /* size 0x5C */

typedef struct G5FxHmf {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 groupCount;
} G5FxHmf;

void func_80013390_main(s16 model, s16 type, char *name, void (*hook)(s16));
void func_80119360_w02(omObjData *obj);
void func_80119408_w02(s16 model, f32 speed, f32 dist);
void func_80119438_w02(s16 model, f32 x, f32 y, f32 z);
void func_8011946C_w02(s16 model);
void func_80119680_w02(s16 model);
extern s32 D_8011D958_w02; /* emitting on/off */
extern s32 D_8011D95C_w02; /* particles spawned per frame */
extern s16 D_8011ED00_w02;
extern omObjData *D_8011ED04_w02;

void func_80119244_w02(void) {
    SpaceData *space;
    s16 model;

    space = MBMasuGet(0x78);
    model = D_8011ED00_w02 = func_8000B108_main(0xB0033, 0xAA9);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C8A8_main(model, 1);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_80119680_w02);
    func_80119438_w02(model, space->coords.x + 142.0f, space->coords.y, space->coords.z);
    func_80119408_w02(model, 1.0f, 1000.0f);
    D_8011D958_w02 = 0;
    D_8011ED04_w02 = omAddObj(0x7D0, 0xA, 0xA, -1, func_80119360_w02);
}

void func_80119360_w02(omObjData *obj) {
    s32 i;

    if (D_8011D958_w02 != 0) {
        for (i = 0; i < D_8011D95C_w02; i++) {
            func_8011946C_w02(D_8011ED00_w02);
        }
    }
}

void func_801193C0_w02(void) {
    D_8011D958_w02 = 1;
}

void func_801193D0_w02(void) {
    D_8011D958_w02 = 0;
}

void func_801193DC_w02(void) {
    func_8001ACDC_main(D_8011ED00_w02);
    omDelObj(D_8011ED04_w02);
}

void func_80119408_w02(s16 model, f32 speed, f32 dist) {
    G5FxWork *work = (G5FxWork *)HmfModelData[model].unkBC;

    work->dist = dist;
    work->speed = speed;
}

void func_80119438_w02(s16 model, f32 x, f32 y, f32 z) {
    G5FxWork *work = (G5FxWork *)HmfModelData[model].unkBC;

    work->center.x = x;
    work->center.y = y;
    work->center.z = z;
}

/* Spawns one particle: on a ring of radius 300..325 around the centre, moving towards it. */
void func_8011946C_w02(s16 model) {
    G5FxHmf *hmf = (G5FxHmf *)HmfModelData[model].hmf;
    G5FxWork *work = (G5FxWork *)HmfModelData[model].unkBC;
    G5FxPart *part = work->parts;
    s16 count = hmf->groupCount;
    s16 i;
    f32 radius;
    f32 angle;
    f32 dx;
    f32 dy;
    f32 dz;

    for (i = 0; i < count; i++, part++) {
        if (part->scale <= 0.0f) {
            radius = (u8)(rand8() / 10) + 300;
            angle = (s32)((u32)(rand8() * 25) >> 7) + 15;
            part->pos.x = sindf(angle) * radius + work->center.x;
            part->pos.y = 0.0f;
            part->pos.z = cosdf(angle) * radius + work->center.z;
            if (work->speed > 0.0f) {
                part->vel.x = part->vel.y = part->vel.z = 0.0f;
            } else {
                dx = work->center.x - part->pos.x;
                dy = work->center.y - part->pos.y;
                dz = work->center.z - part->pos.z;
                radius = HuSqrtf(dx * dx + dy * dy + dz * dz);
                part->vel.x = dx / radius * work->speed;
                part->vel.y = dy / radius * work->speed;
                part->vel.z = dz / radius * work->speed;
                part->pos.x = work->center.x;
                part->pos.y = work->center.y;
                part->pos.z = work->center.z;
            }
            part->scale = 1.0f;
            return;
        }
    }
}

// Masked 9 (216 vs 215): the two "scale = 0" stores (not live, too close to the centre) are a
// shared `sw zero` in retail and len is kept in a second register; the else-if layout differs.
// Logic checked against the asm.
#ifdef NON_MATCHING
/* Effect update: on the first frame clears every particle, then moves the live ones. */
void func_80119680_w02(s16 model) {
    G5FxHmf *hmf = (G5FxHmf *)HmfModelData[model].hmf;
    G5FxWork *work = (G5FxWork *)HmfModelData[model].unkBC;
    s16 count = hmf->groupCount;
    G5FxPart *part;
    s16 i;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;
    f32 scale;
    f32 f;

    if (work->frame == 0) {
        work->flags &= ~4;
        part = work->parts;
        for (i = 0; i < count; i++, part++) {
            part->pos.x = part->pos.y = part->pos.z = 0.0f;
            part->unk24.x = part->unk24.y = part->unk24.z = 0.0f;
            part->scale = 0.0f;
            part->unk04 = 1.0f;
        }
        work->frame++;
    }
    part = work->parts;
    for (i = 0; i < count; i++, part++) {
        if (!(part->scale > 0.0f)) {
            part->scale = 0.0f;
        } else if (work->speed > 0.0f) {
            part->pos.x += part->vel.x;
            part->pos.y += part->vel.y;
            part->pos.z += part->vel.z;
            dx = work->center.x - part->pos.x;
            dy = work->center.y - part->pos.y;
            dz = work->center.z - part->pos.z;
            len = HuSqrtf(dx * dx + dy * dy + dz * dz);
            scale = len / 1000.0f * 3.0f;
            if ((len < 100.0f) | (scale < 0.1f)) {
                part->scale = 0.0f;
            } else {
                part->scale = scale;
                f = (work->dist - len) / len;
                if (f < 0.05f) {
                    f = 0.05f;
                }
                f *= work->speed;
                part->vel.x = dx / len * f;
                part->vel.y = dy / len * f;
                part->vel.z = dz / len * f;
            }
        } else {
            part->pos.x += part->vel.x;
            part->pos.y += part->vel.y;
            part->pos.z += part->vel.z;
            part->vel.x *= 0.98;
            part->vel.y *= 0.98f;
            part->vel.z *= 0.98f;
            part->scale -= 0.001f;
            if (part->scale < 0.0f) {
                part->scale = 0.0f;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119680_w02);
#endif

/* Process: a sprite (file 0x1300F7) at (160, 90) flips over twice (its y scale follows sin, the
   back half mirrored), holds, flips twice more while fading out from the second turn, then is
   freed. */
void func_801199EC_w02(void) {
    void *data;
    s32 sprite;
    s32 group;
    s32 turns;
    s32 counted;
    s32 fading;
    s32 alpha;
    f32 angle;
    f32 a;
    f32 step;

    data = DataRead(0x1300F7);
    sprite = func_80055810_main(data);
    DataClose(data);
    group = HuSprGrpCreate(1, 5);
    func_80055024_main(group, 0, sprite, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x1008);
    HuSprPriSet(group, 0, 0x1000);
    func_80054904_main(group, 0, 0xA0, 0x5A);
    angle = 0.0f;
    step = 30.0f;
    turns = 0;
    counted = 0;
    while (TRUE) {
        if ((angle >= 90.0f) & (counted == 0)) {
            counted = 1;
            turns++;
        }
        if (angle >= 360.0f) {
            counted = 0;
            angle -= 360.0f;
        }
        if ((angle >= 180.0f) & (angle <= 360.0f)) {
            HuSprAttrSet(group, 0, 2);
        } else {
            HuSprAttrReset(group, 0, 2);
        }
        a = angle;
        if (angle >= 180.0f) {
            a = angle - 180.0f;
        }
        HuSprScaleSet(group, 0, 1.0f, sindf(a));
        if (turns >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += step;
    }
    HuSprAttrReset(group, 0, 2);
    HuSprScaleSet(group, 0, 1.0f, 1.0f);
    HuPrcSleep(20);
    angle = 90.0f;
    turns = 0;
    fading = 0;
    counted = 0;
    alpha = 0xFF;
    while (TRUE) {
        if ((angle >= 360.0f) & (counted == 0)) {
            counted = 1;
            turns++;
        }
        if (angle >= 360.0f) {
            counted = 0;
            angle -= 360.0f;
        }
        if ((fading == 0) & (turns != 0)) {
            if ((angle >= 90.0f) & (angle < 180.0f)) {
                fading = 1;
            }
        }
        if (fading != 0) {
            alpha -= 21;
            if (alpha <= 0) {
                alpha = 0;
            }
        }
        func_80055458_main(group, 0, alpha);
        if (turns >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += step;
    }
    HuSprScaleSet(group, 0, 1.0f, 0.0f);
    HuSprGrpKill(group);
    HuSprKill(sprite);
    omDelPrcObj(NULL);
}

// board g6

void func_801199EC_w02(void);
void func_80119DB0_w02(void);
void func_80119244_w02(void);
void func_801193C0_w02(void);
void func_801193D0_w02(void);
void func_801193DC_w02(void);
void func_80007EC0_main(s32);
extern s32 D_8011D960_w02[3];
extern s32 D_8011D96C_w02[3];
extern s32 D_8011D978_w02[3];
extern f32 D_8011D984_w02[4][2];
void func_8011B038_w02(s16 masu);
s32 func_8011B988_w02(void);
s32 func_8011BA58_w02(void);
extern RectF D_8011DADC_w02;
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
// decomp-permuter
void func_8011B038_w02(s16 masu)
{
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
  for (i = 0; i < ((sizeof(D_8011D9A4_w02)) / (sizeof(D_8011D9A4_w02[0]))); i += 2)
  {
    if (D_8011D9A4_w02[i] == masu)
    {
      destMasu = D_8011D9A4_w02[i + 1];
      break;
    }
  }

  dest = MBMasuGet(destMasu);
  MBCamera3Dto2D(&space->coords, screen);
  offscreen = 1;
  if ((((screen[0] >= 24.0f) && (screen[0] <= 296.0f)) && (screen[1] >= 12.0f)) && (screen[1] <= 228.0f))
  {
    offscreen = 0;
    HuVecCopy3F(&target, &space->coords);
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &target, &pos, 20));
    HuPrcChildWait();
  }
  else
  {
    offscreen = 1;
    WipeCreateOut(4, 16);
    while (WipeStatGet() != 0)
    {
      HuPrcVSleep();
    }

    HuVecCopy3F(&pos, &space->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    func_800E9AF0_shared_board(&pos, 0);
    HuPrcVSleep();
    WipeCreateIn(4, 16);
    while (WipeStatGet() != 0)
    {
      HuPrcVSleep();
    }

  }
  MBDlgWinExec(0x3A, 0x500);
  HuVecAdd(&target, &player->player_obj->coords, &dest->coords);
  HuVecMulScalar(&target, 0.5f, &target);
  if (offscreen == 0)
  {
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &target, &pos, 20));
    HuPrcChildWait();
  }
  else
  {
    WipeCreateOut(4, 16);
    while (WipeStatGet() != 0)
    {
      HuPrcVSleep();
    }

    HuVecCopy3F(&pos, &target);
    func_800E9AF0_shared_board(&pos, 0);
    HuPrcVSleep();
    WipeCreateIn(4, 16);
    while (WipeStatGet() != 0)
    {
      HuPrcVSleep();
    }

  }
  obj = MBModelFileCreate(0x13016A, -1, 1.0f, 0.0f, 0);
  HuVecCopy3F(&obj->coords, &player->player_obj->coords);
  obj->velocity.x = 150.0f;
  for (i = 90; i <= 180; i += 3)
  {
    obj->velocity.x = sindf(i) * 150.0f;
    {
      HmfModel *mdl;
      sincosdf(180 - i, &HmfModelData[obj->omObj1->model[0]].mtx[1], &HmfModelData[obj->omObj1->model[0]].mtx[0]);
      HmfModelData[obj->omObj1->model[0]].mtx[4] = -HmfModelData[obj->omObj1->model[0]].mtx[1];
      mdl = &HmfModelData[obj->omObj1->model[0]];
      mdl->mtx[5] = mdl->mtx[0];
      mdl = &HmfModelData[obj->omObj1->model[0]];
      mdl->mtx[2] = (mdl->mtx[3] = (mdl->mtx[7] = (mdl->mtx[6] = (mdl->mtx[8] = (mdl->mtx[9] = (mdl->mtx[11] = (mdl->mtx[12] = (mdl->mtx[13] = (mdl->mtx[14] = 0.0f)))))))));
      mdl = &HmfModelData[obj->omObj1->model[0]];
      mdl->mtx[10] = (mdl->mtx[15] = 1.0f);
    }
    ;
    HuPrcVSleep();
  }

  func_800EB24C_shared_board(destMasu, &player->clink, &player->cidx);
  MBMoveMasuSet(MBPlayerTurnGet(), player->clink, player->cidx);
  for (i = 0; i < 4; i++)
  {
    if (MBPlayerTurnGet() != i)
    {
      MBPlayerPosFixSet(i, 5);
    }
  }

  HuAudFXPlay(0x191);
  vib = MBPlayerVibrateObjCreate(-1, 2, 5);
  HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &dest->coords, &player->player_obj->coords, 18));
  HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&obj->coords, &dest->coords, &obj->coords, 18));
  for (i = 0; i <= 180; i += 10)
  {
    obj->velocity.x = sindf(i) * 50.0f;
    {
      HmfModel *mdl;
      sincosdf((-sindf(i)) * 30.0f, &HmfModelData[obj->omObj1->model[0]].mtx[1], &HmfModelData[obj->omObj1->model[0]].mtx[0]);
      HmfModelData[obj->omObj1->model[0]].mtx[4] = -HmfModelData[obj->omObj1->model[0]].mtx[1];
      mdl = &HmfModelData[obj->omObj1->model[0]];
      mdl->mtx[5] = mdl->mtx[0];
      mdl = &HmfModelData[obj->omObj1->model[0]];
      mdl->mtx[2] = (mdl->mtx[3] = (mdl->mtx[7] = (mdl->mtx[6] = (mdl->mtx[8] = (mdl->mtx[9] = (mdl->mtx[11] = (mdl->mtx[12] = (mdl->mtx[13] = (mdl->mtx[14] = 0.0f)))))))));
      mdl = &HmfModelData[obj->omObj1->model[0]];
      mdl->mtx[10] = (mdl->mtx[15] = 1.0f);
    }
    ;
    player->player_obj->velocity.x = sindf(i) * 50.0f;
    HuPrcVSleep();
  }

  MBPlayerVibrateObjKill(vib);
  player->player_obj->velocity.x = 0.0f;
  for (i = 0; i <= 90; i += 10)
  {
    obj->velocity.x = sindf(i) * 150.0f;
    {
      HmfModel *mdl;
      sincosdf(i, &HmfModelData[obj->omObj1->model[0]].mtx[1], &HmfModelData[obj->omObj1->model[0]].mtx[0]);
      HmfModelData[obj->omObj1->model[0]].mtx[4] = -HmfModelData[obj->omObj1->model[0]].mtx[1];
      mdl = &HmfModelData[obj->omObj1->model[0]];
      mdl->mtx[5] = mdl->mtx[0];
      mdl = &HmfModelData[obj->omObj1->model[0]];
      mdl->mtx[2] = (mdl->mtx[3] = (mdl->mtx[7] = (mdl->mtx[6] = (mdl->mtx[8] = (mdl->mtx[9] = (mdl->mtx[11] = (mdl->mtx[12] = (mdl->mtx[13] = (mdl->mtx[14] = 0.0f)))))))));
      mdl = &HmfModelData[obj->omObj1->model[0]];
      mdl->mtx[10] = (mdl->mtx[15] = 1.0f);
    }
    ;
    HuPrcVSleep();
  }

  MBModelKill(obj);
  MBCameraFocusModeSet(3);
  HuPrcSleep(5);
}

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

s32 func_8011B988_w02(void) {
    s32 i;
    DecisionTreeNonLeafNode *tree;
    GW_SYSTEM *loc = &GwSystem;

    tree = D_8011E338_w02[loc->star_spawn_indices[loc->current_star_spawn]];
    func_800DA778_shared_board(loc->current_player_index);
    if (MBComTreeExec(D_8011E254_w02) == 0) {
        return loc->current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != loc->current_player_index) {
            func_800DA778_shared_board(i);
            if (MBComTreeExec(tree) == 0) {
                return i;
            }
        }
    }
    return MBRand(4.0f);
}

s32 func_8011BA58_w02(void) {
    s32 i;
    DecisionTreeNonLeafNode *tree1;
    DecisionTreeNonLeafNode *tree2;
    GW_SYSTEM *loc = &GwSystem;

    tree1 = D_8011E73C_w02[loc->star_spawn_indices[loc->current_star_spawn]];
    tree2 = D_8011E75C_w02[loc->star_spawn_indices[loc->current_star_spawn]];
    func_800DA778_shared_board(loc->current_player_index);
    if (MBComTreeExec(tree1) == 0) {
        return loc->current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != loc->current_player_index) {
            func_800DA778_shared_board(i);
            if (MBComTreeExec(tree2) == 0) {
                return i;
            }
        }
    }
    return MBRand(4.0f);
}

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
void func_8010EBB8_w02(void);
void func_8010EBD4_w02(void);
void func_80116708_w02(void);
void func_80118480_w02(void);
s16 D_8011C660_w02[8] = { 0, 1, 2, 3, 5, 4, 6, 7 };
s16 D_8011C670_w02[8] = { 0, 0, 0, 0, 0, 1, 1, 1 };
s16 D_8011C680_w02[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011C690_w02[8] = { 30, 40, 21, 7, 65, 92, 76, 86 };
s16 D_8011C6A0_w02[8] = { 94, 95, 96, 97, 98, 99, 100, 101 };
s32 D_8011C6B0_w02[7] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083, 0xA0084 };
s32 D_8011C6CC_w02[7] = { 24066, 24067, 24068, 24069, 24070, 24071, 24072 };
s32 D_8011C6E8_w02 = 0;
s16 D_8011C6EC_w02[1] = { -1 };
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
s16 D_8011C7F0_w02[6] = { 38, 39, 40, 41, 42, 43 };
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
s16 D_8011D2B0_w02[1][3] = { { 11, 32, -1 } };
BranchLink D_8011D2B8_w02[1][2] = {
    { { 0, 16, 0 }, { 0, 14, 1 } },
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
Vec2f D_8011D5A8_w02[4] = {
    { 76.0f, 52.0f },
    { 244.0f, 52.0f },
    { 76.0f, 192.0f },
    { 244.0f, 192.0f },
};
Vec2f D_8011D5C8_w02[4] = {
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
s16 D_8011D8A4_w02[1][3] = { { 42, 12, -1 } };
BranchLink D_8011D8AC_w02[1][2] = {
    { { 6, 0, 0 }, { 4, 0, 0 } },
};
G5MotList D_8011D8B8_w02 = { 1, { 0x2001A } };
G5MotList D_8011D8C0_w02 = { 1, { 0 } };
G5MotList D_8011D8C8_w02 = { 1, { 0 } };
G5MotList D_8011D8D0_w02 = { 1, { 0 } };
G5MotList D_8011D8D8_w02 = { 1, { 0 } };
G5MotList D_8011D8E0_w02 = { 1, { 0 } };
G5MotList D_8011D8E8_w02 = { 1, { 0 } };
G5MotList D_8011D8F0_w02 = { 1, { 0 } };
G5MotList *D_8011D8F8_w02[8] = {
    &D_8011D8B8_w02, &D_8011D8C0_w02, &D_8011D8C8_w02, &D_8011D8D0_w02,
    &D_8011D8D8_w02, &D_8011D8E0_w02, &D_8011D8E8_w02, &D_8011D8F0_w02,
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
const G3SparkDirs D_8011EA80_w02 __attribute__((section(".data"))) = { {
    { 1.0f, 1.0f, 1.0f }, { 1.0f, 2.0f, 1.0f }, { 0.0f, 2.0f, 1.0f }, { -1.0f, 1.0f, 1.0f },
    { -1.0f, -1.0f, 1.0f }, { 0.0f, -1.0f, 1.0f }, { -1.0f, 2.0f, 1.0f }, { 1.0f, -1.0f, 1.0f },
} };
const f64 D_8011EAE0_w02 __attribute__((section(".data"))) = 0.3;
const f64 D_8011EAE8_w02 __attribute__((section(".data"))) = 0.5;
const f64 D_8011EAF0_w02 __attribute__((section(".data"))) = 0.5;
const f64 D_8011EAF8_w02 __attribute__((section(".data"))) = 0.5;
const f64 D_8011EB00_w02 __attribute__((section(".data"))) = 0.5;
const f64 D_8011EB08_w02 __attribute__((section(".data"))) = 1.5;
const f64 D_8011EB10_w02 __attribute__((section(".data"))) = 0.8;
const f64 D_8011EB18_w02 __attribute__((section(".data"))) = 0.8;
G5GateFiles D_8011EB20_w02 = { { 0x1301E1, 0x1301E2, 0x1301E3, 0x1301E4, 0x1301E5 } };
G5GatePos D_8011EB34_w02 = { {
    { 160.0f, 120.0f },
    { -68.0f, -8.0f },
    { -23.0f, -8.0f },
    { 23.0f, -8.0f },
    { 68.0f, -8.0f },
} };
