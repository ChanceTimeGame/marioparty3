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
extern DecisionTreeNonLeafNode *D_8011D524_w05[];
extern DecisionTreeNonLeafNode *D_8011DA28_w05[];
extern event_table_entry D_8011EC2C_w05[];
extern event_table_entry D_8011ECA4_w05[];
extern event_table_entry D_8011EE38_w05[];
extern event_table_entry D_8011EFA8_w05[];
extern s16 D_8011E3A8_w05[];
extern s16 D_8011E558_w05[];
extern s16 D_8011E810_w05[][3];
extern BranchLink D_8011E824_w05[][2];
extern DecisionTreeNonLeafNode *D_8011DEC0_w05[];
extern s16 D_8011E438_w05[][3];
extern BranchLink D_8011E44C_w05[][2];
extern DecisionTreeNonLeafNode *D_8011D74C_w05[];
extern s16 D_8011E5A0_w05[][3];
extern BranchLink D_8011E5B4_w05[][2];
extern DecisionTreeNonLeafNode *D_8011DA88_w05[];
void func_80118464_w05(void);
void func_8011BB74_w05(void);
extern s32 D_8011E3BC_w05[];
extern s32 D_8011E56C_w05[];
void func_80107780_w05(void);
void func_80107B90_w05(void);
void func_801089A8_w05(void);
void func_80108A90_w05(void);
void func_80108BC0_w05(void);
void func_80108C70_w05(void);
void func_80108EB4_w05(void);
void func_80109078_w05(void);
void func_80118364_w05(void);
void func_801184C0_w05(void);
extern DecisionTreeNonLeafNode D_8011E9B8_w05[];
extern char D_80120624_w05[];
extern s32 D_8011D0C8_w05;
extern s32 D_8011EAD8_w05[5][2];
extern s32 D_8011EB00_w05[2];
extern s32 D_8011EB08_w05[2];
extern s32 D_8011EB10_w05[2];
extern s32 D_8011EB18_w05[2];
extern s32 D_8011EB20_w05[2];
extern s32 D_8011EB38_w05;
extern s8 D_8011EA60_w05[2][5][10];
extern u32 D_8011E9D0_w05[];
extern u32 D_8011EB28_w05[];
extern u32 D_8011EB30_w05[];
extern u8 D_8011E9E8_w05[2][3][4];
extern u8 D_8011EA48_w05[2][3][4];
extern u8 D_8011EAC4_w05[2][10];
void func_801064DC_w05(void);
void func_80109E08_w05(void);
void func_8010AC0C_w05(void);
void func_80112554_w05(void);
extern s16 D_8011D0D0_w05[]; /* blocked-space extension table */
extern s16 D_8011D0D4_w05[]; /* blocked spaces */
void func_8010D428_w05(void);
void func_8010E8A8_w05(void);
void func_8010EC70_w05(void);
void func_8010ECDC_w05(void);
void func_8011720C_w05(void);
void func_8010FEE8_w05(void);
void func_80110174_w05(void);
void func_8010F1D0_w05(void);
void func_8010F740_w05(void);
void func_8010FA8C_w05(void);
void func_80116508_w05(void);
void func_80116D88_w05(void);
void func_801105C4_w05(void);
void func_80110884_w05(void);
void func_80110C24_w05(void);
void func_80111620_w05(void);
void func_80112178_w05(void);
void func_80112E90_w05(void);
void func_8011412C_w05(void);
void func_8011512C_w05(void);
void func_80116358_w05(void);
void func_80116C50_w05(void);
void func_8011604C_w05(void);
void func_80118E2C_w05(void);
void func_801191C0_w05(void);
s32 func_8011C648_w05(void);
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

void func_801064DC_w05(void) {
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
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x4F) {
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
    if (D_8011D0C8_w05 != 0) {
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
    if (D_8011D0C8_w05 != 0) {
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

void func_80107744_w05(void) {
    GwSystem.current_board_index = 4;
    omInitObjMan(10, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

void func_80107780_w05(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    func_801059F8_w05();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[0] = 0;
    func_80118464_w05();
    GwSystem.boardData.halfWordBytes[3] = 0;
    GwSystem.boardData.halfWordBytes[4] = 1;
    omOvlReturnEx(1);
}

void func_8010782C_w05(void) {
    Vec sp10;
    SpaceData *space;
    s32 i;

    omInitObjMan(0xA0, 0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(0xF, 0x23E, 0x11, 0);
    MBMasuBlockTblExtSet(D_8011D0D0_w05);
    MBMasuBlockTblSet(D_8011D0D4_w05);
    MBMasuArrowAngleAdd(0.0f);
    space = MBMasuGet(0x93);
    MBVecDirGet(&space->coords, &MBMasuGet(0x94)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBMasuArrowAngleAdd(0.0f);
    MBMasuArrowAngleAdd(0.0f);
    space = MBMasuGet(0x76);
    MBVecDirGet(&space->coords, &MBMasuGet(0x77)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBMasuArrowAngleAdd(0.0f);
    MBItemHookSet(0, &func_8010D428_w05);
    MBItemHookSet(1, &func_8010E8A8_w05);
    MBItemHookSet(9, &func_8010EC70_w05);
    MBItemHookSet(2, &func_8010ECDC_w05);
    MBItemHookSet(3, &func_8011720C_w05);
    MBItemHookSet(4, &func_8010FEE8_w05);
    MBItemHookSet(5, &func_80110174_w05);
    MBItemHookSet(6, &func_8010F1D0_w05);
    MBItemHookSet(7, &func_8010F740_w05);
    MBItemHookSet(8, &func_8010FA8C_w05);
    MBItemHookSet(0xA, &func_80116508_w05);
    MBItemHookSet(0xB, &func_80116D88_w05);
    MBItemHookSet(0xE, &func_801105C4_w05);
    MBItemHookSet(0xF, &func_80110884_w05);
    MBItemHookSet(0x10, &func_80110C24_w05);
    MBItemHookSet(0x11, &func_80111620_w05);
    MBItemHookSet(0x12, &func_80112178_w05);
    MBItemHookSet(0x13, &func_80112E90_w05);
    MBItemHookSet(0x14, &func_8011412C_w05);
    MBItemHookSet(0x15, &func_8011512C_w05);
    MBItemHookSet(0xC, &func_80116358_w05);
    MBItemHookSet(0xD, &func_80116C50_w05);
    MBComItemDecideHookSet(func_8011C648_w05);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, D_8011D080_w05[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        func_80105B00_w05();
    }

    func_80105B8C_w05();
    func_80107DCC_w05();
    func_80107F98_w05();
    func_8010825C_w05();
    func_80108430_w05();
    func_801086A0_w05();
    func_80108720_w05();
    func_8011604C_w05();
    func_800EBDAC_shared_board();
    omAddPrcObj(func_80118E2C_w05, 0x4800, 0, 0);
    omAddPrcObj(func_801191C0_w05, 0x4800, 0, 0);
}

void func_80107B90_w05(void) {
    HuAudSeqPlay(0x1C);
    D_800CE198_main = 0x1C;
    func_800F8D6C_shared_board(0x1C);
    Hu3DCamInit(2);
    func_8010782C_w05();
    MBMasuEventTblAdd(D_8011EC2C_w05);
    MBMasuEventTblAdd(D_8011EFA8_w05);
    MBHatenaFuncSet(&func_80118364_w05);
    MBMasuEventTblAdd(D_8011ECA4_w05);
    MBMasuEventTblAdd(D_8011EE38_w05);
    MBStart(0);
}

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

s32 func_80108798_w05(void) {
    s32 result = 1;
    s32 i;
    s32 item;

    for (i = 0; i < 3; i++) {
        item = GwPlayer[GwSystem.current_player_index].itemNo[i];
        switch (GwSystem.boardData.halfWordBytes[2]) {
            case 0:
                result &= -((item ^ 1) != 0);
                break;
            case 1:
                result &= -(item != 0);
                break;
            case 2:
                result &= -((item ^ 2) != 0);
                break;
        }
    }
    return result;
}

void func_80108830_w05(s32 masuAbsIndex, s16 arg1, s16 arg2) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == masuAbsIndex) {
        MBMoveNextMasuSet(-1, arg1, arg2);
    }
}

void func_801088B8_w05(s16 (*masu)[3], g1BranchLink (*links)[2], DecisionTreeNonLeafNode **trees) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && mbWalkNum != 0) {
        func_80115A30_w05(masu, links, trees);
    }
}

void func_80108924_w05(void) {
    MBMoveNextMasuSet(-1, 1, 2);
}

void func_80108948_w05(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x6C) {
        MBMoveBackMasuSet(-1, 1, 2);
    }
}

void func_801089A8_w05(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2A && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 3, 0);
        player->rev &= ~1;
    } else {
        func_80115A30_w05((SpaceTriple *)D_8011E3A8_w05, (BranchPair *)D_8011E3BC_w05, D_8011D524_w05);
    }
    omDelPrcObj(NULL);
}

void func_80108A58_w05(void) {
    func_80115A30_w05((SpaceTriple *)D_8011E3F0_w05, (BranchPair *)D_8011E404_w05, D_8011D6BC_w05);
    omDelPrcObj(NULL);
}

void func_80108A90_w05(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x8D) {
        func_801184C0_w05();
    } else {
        func_80115A30_w05(D_8011E438_w05, D_8011E44C_w05, D_8011D74C_w05);
    }
    omDelPrcObj(NULL);
}

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

void func_80108BC0_w05(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x61 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 15, 0);
        player->rev &= ~1;
    } else {
        func_80115A30_w05((SpaceTriple *)D_8011E558_w05, (BranchPair *)D_8011E56C_w05, D_8011DA28_w05);
    }
    omDelPrcObj(NULL);
}

void func_80108C70_w05(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x8A) {
        func_801184C0_w05();
    } else {
        func_80115A30_w05(D_8011E5A0_w05, D_8011E5B4_w05, D_8011DA88_w05);
    }
    omDelPrcObj(NULL);
}

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

void func_80108E48_w05(void) {
    func_80108830_w05(0x1C, 4, 9);
}

void func_80108E6C_w05(void) {
    func_80108830_w05(0x96, 4, 9);
}

void func_80108E90_w05(void) {
    func_80108830_w05(0x1F, 3, 0);
}

void func_80108EB4_w05(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & 0x80) && mbWalkNum != 0) {
        func_80115A30_w05(D_8011E810_w05, D_8011E824_w05, D_8011DEC0_w05);
    } else {
        func_80108830_w05(0x58, 1, 9);
    }
}

void func_80108F20_w05(void) {
    func_80108830_w05(0x23, 3, 4);
}

void func_80108F44_w05(void) {
    func_80108830_w05(0x8C, 3, 4);
}

void func_80108F68_w05(void) {
    func_80108830_w05(0x70, 14, 16);
}

void func_80108F8C_w05(void) {
    func_80108830_w05(0x28, 14, 4);
}

void func_80108FB0_w05(void) {
    func_80108830_w05(0x12, 14, 16);
}

void func_80108FD4_w05(void) {
    func_80108830_w05(0x13, 4, 3);
}

void func_80108FF8_w05(void) {
    func_80108830_w05(0x73, 1, 9);
}

void func_8010901C_w05(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x8B) {
        func_801184C0_w05();
    }
}

void func_80109078_w05(void) {
    func_80108830_w05(0x54, 16, 17);
    func_8011BB74_w05();
}

void func_801090A4_w05(void) {
    func_80108830_w05(0x56, 16, 4);
}

void func_801090C8_w05(void) {
    func_80108830_w05(0x38, 16, 17);
}

void func_801090EC_w05(void) {
    func_80108830_w05(0x5E, 9, 12);
    func_8011BB74_w05();
}

void func_80109118_w05(void) {
    func_80108830_w05(0x5F, 15, 2);
}

void func_8010913C_w05(void) {
    func_80108830_w05(0x44, 9, 12);
}

void func_80109160_w05(void) {
    func_80108830_w05(0x4A, 11, 6);
}

void func_80109184_w05(void) {
    func_80108830_w05(0x8A, 16, 0);
}

void func_801091A8_w05(void) {
    func_80108830_w05(0x5A, 15, 4);
}

void func_801091CC_w05(void) {
    func_80108830_w05(0x5C, 9, 4);
}

void func_801091F0_w05(void) {
    func_80108830_w05(0x87, 11, 6);
}

void func_80109214_w05(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x8C) {
        func_801184C0_w05();
    }
}

void func_80109270_w05(void) {
    GW_PLAYER *player;
    GW_SYSTEM *loc;
    s32 flag;
    s32 choice;
    void *prc;
    s32 masuId;
    s32 gateA;
    s32 gateB;

    flag = 1;
    loc = &GwSystem;
    player = MBPlayerGet(-1);
    masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    switch (masuId) {
        case 0x74:
        case 0x88:
            switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
                case 0x75:
                    MBMoveNextMasuSet(-1, 0x10, 7);
                    goto end;
                case 0x89:
                    MBMoveNextMasuSet(-1, 0xE, 5);
                    goto end;
            }
            break;
        case 0x73:
        case 0x87:
            switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
                case 0x75:
                case 0x89:
                    goto end;
            }
            break;
    }

    MBPlayerMotionSet(-1, -1, 2);
    if (MBItemFind(loc->current_player_index, 1) != -1) {
        func_800DBEC0_shared_board(loc->current_player_index);
        switch (masuId) {
            case 0x73:
            case 0x74:
                func_800ED20C_shared_board(-1, 8, 0x75);
                break;
            default:
                func_800ED20C_shared_board(-1, 8, 0x89);
                break;
        }
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWait();
        MBPlayerVibrate(-1, 1);

        while (1) {
            MBDlgWinCreate(0x38, 0x4103);
            choice = func_801096DC_w05(2, 0);
            MBDlgWinClose();
            MBDlgWinKill();

            switch (choice) {
                case 0:
                    MBDlgWinExec(0x38, 0x4104);
                    GwPlayer[loc->current_player_index].itemNo[MBItemFind(loc->current_player_index, 1)] = -1;
                    MBItemRemoveEmpty(GwSystem.current_player_index);
                    MBStatusItemIconSprReinit(-1);
                    switch (masuId) {
                        case 0x73:
                            gateA = 0;
                            gateB = 0;
                            break;
                        case 0x74:
                            gateA = 0;
                            gateB = 1;
                            break;
                        case 0x87:
                            gateA = 1;
                            gateB = 0;
                            break;
                        default:
                            gateA = 1;
                            gateB = 1;
                            break;
                    }
                    func_801084EC_w05(gateA, gateB);
                    flag = 0;
                    prc = MBPlayerVibrateObjCreate(-1, 2, 5);
                    HuPrcSleep(0x14);
                    MBPlayerVibrateObjKill(prc);
                    break;
                case 1:
                    MBDlgWinExec(0x38, 0x4105);
                    break;
                case 2:
                    func_80106AB0_w05();
                    continue;
            }
            break;
        }

        func_800DB884_shared_board(loc->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWait();
    } else {
        MBDlgWinExec(-1, 0x4106);
    }

    if (flag != 0) {
        switch (masuId) {
            case 0x73:
                MBMoveNextMasuSet(-1, 7, 0);
                player->rev |= 1;
                break;
            case 0x74:
                MBMoveNextMasuSet(-1, 0x10, 7);
                player->rev &= ~1;
                break;
            case 0x87:
                MBMoveNextMasuSet(-1, 0xD, 0);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 0xE, 5);
                player->rev &= ~1;
                break;
        }
    }

end:
    omDelPrcObj(NULL);
}

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

void func_80109E08_w05(void) {
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
            func_800ED20C_shared_board(-1, 8, 0x6D);
            spaceA = MBMasuGet(0x6D);
            spaceB = MBMasuGet(0x21);
            break;
        case 0x45:
            func_800ED20C_shared_board(-1, 8, 0x79);
            spaceA = MBMasuGet(0x79);
            spaceB = MBMasuGet(0x45);
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

    effectModel = MBModelCreate(0x35, D_8011E9D0_w05);
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
        choice = func_801096DC_w05((s32)D_8011E9B8_w05, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                func_80106AB0_w05();
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
        sprintf(sp20, D_80120624_w05, GwSystem.bank_coins);
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
            func_80112554_w05();
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
                sprintf(sp20, D_80120624_w05, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, D_80120624_w05, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                func_80107FF4_w05();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, D_80120624_w05, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, D_80120624_w05, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                func_80107FF4_w05();
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
                sprintf(sp20, D_80120624_w05, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                func_80107FF4_w05();
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
    func_801096C4_w05();
}

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

void func_8010AC0C_w05(void) {
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
        case 0x93:
            camMasu = 0x94;
            spaceA = MBMasuGet(0x94);
            spaceB = MBMasuGet(0x93);
            D_8011EB38_w05 = 0;
            break;
        case 0x76:
            camMasu = 0x77;
            spaceA = MBMasuGet(0x77);
            spaceB = MBMasuGet(0x76);
            D_8011EB38_w05 = 1;
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
            effectModel = MBModelCreate(0x39, D_8011EB30_w05);
        } else {
            effectModel = MBModelCreate(0x1B, D_8011EB28_w05);
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
        MBDlgWinExec(dlgWin, D_8011EB18_w05[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, D_8011EB10_w05[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, D_8011EB08_w05[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, D_8011EB00_w05[shopIdx]);
    choice = func_80106F58_w05();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = BoardGetTurnTier(-1);
            row = D_8011E9E8_w05[shopIdx][i][BoardPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (D_8011EA00_w05[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_8011EA00_w05[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (D_8011EA00_w05[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_80100F94_shared_board[D_8011EA00_w05[shopIdx][row][j]] >
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

            MBDlgWinInsertCreate(dlgWin, D_8011EAD8_w05[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            func_800ECAA8_shared_board(0);
            D_80120824_w05 = slot;
            D_80120828_w05 = row;
            D_8012082C_w05 = enabled;
            sel = func_80106CC4_w05(enabled);
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
            shopTable = D_8011EA00_w05;
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
                    D_8011EA00_w05[shopIdx][row][sel];
                item = D_8011EA00_w05[shopIdx][row][sel];
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

            if (D_8011EA00_w05[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = D_8011EA48_w05[shopIdx][BoardGetTurnTier(-1)]
                                                [BoardPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < D_8011EA60_w05[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = D_8011EAC4_w05[shopIdx][i];

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
                    prc = omAddPrcObj(func_8010AA34_w05, 0x4002, 0, 0);
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
            MBDlgWinExec(dlgWin, D_8011EB20_w05[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                func_80106B38_w05();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106AB0_w05();
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

// board x2: declarations for func_8010BEC0_w05..func_80111B68_w05
#include "game/board.h"
#include "game/object.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/105D50.h"
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
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/FFB10.h"

typedef struct {
    /* 0x00 */ Vec dir[8];
} X2DirTable;

extern s16 D_8011D070_w05[]; /* star-space id per star spawn */
extern s16 D_8011D080_w05[]; /* space after each star space */
extern Object *D_80120748_w05[8]; /* bss: star models */
extern Process *D_80120768_w05[8]; /* bss: star processes */
extern X2DirTable D_80120630_w05; /* lamp particle directions */
extern const f64 D_80120690_w05; /* 0.3 */
extern const f64 D_80120628_w05; /* 1.5 */
extern Object *D_80120830_w05; /* bss: model linked by func_8010D298_w05 */
extern Vec2f D_8011EB4C_w05[]; /* per-player star sprite position */
extern Vec2f D_8011EB6C_w05[]; /* per-player star sprite step */
extern u8 D_8011EB8C_w05[6][3]; /* Boo: turn range -> base chance */
extern u8 D_8011EBA0_w05[14][3]; /* Boo: attempts range -> penalty */
extern s32 D_8011D0C8_w05;
extern u8 D_8011EBCC_w05[];
extern s32 D_8011EBD4_w05[];
extern s32 D_8011EBE0_w05[];
extern char D_80120624_w05[]; /* "%d" */
extern Object *D_801207E0_w05;
extern Vec2f D_8011ECB4_w05[]; /* item sprite targets */
extern Vec2f D_8011ECD4_w05[]; /* item sprite targets */
extern s32 D_8011EDA0_w05[]; /* sparkle angles */
extern s32 D_80120834_w05; /* bss: sparkle sprite id */
extern s32 D_80120838_w05; /* bss: player index for func_80111B68_w05 */
extern s32 D_8012083C_w05; /* bss: sprite id for func_80111B68_w05 */
extern Vec2f D_8011EDC0_w05[];
extern DecisionTreeNonLeafNode D_8011ED34_w05[];
extern DecisionTreeNonLeafNode D_8011EDB4_w05[];
extern Object *D_801207E4_w05[1];

typedef struct {
    /* 0x00 */ Vec vel;
    /* 0x0C */ f32 alpha;
    /* 0x10 */ f32 scaleStep;
    /* 0x14 */ f32 alphaStep;
    /* 0x18 */ Object *model;
    /* 0x1C */ u16 killOnFade;
} X2ModelFadeWork;

typedef struct {
    /* 0x00 */ s16 startX;
    /* 0x02 */ s16 startY;
    /* 0x04 */ s16 endX;
    /* 0x06 */ s16 endY;
    /* 0x08 */ s16 duration;
    /* 0x0A */ s16 spriteGroup;
} X2SpriteMoveWork;

void func_80108664_w05(s32 arg0);
void func_8010D298_w05(void);
void func_80106A3C_w05(Object *arg);
void func_80106AB0_w05(void);
void func_80106B38_w05(void);
void func_801096D4_w05(void);
s32 func_801096DC_w05(s32 arg0, s32 arg1);
void func_80109A1C_w05(void);
void func_8010AC0C_w05(void);
s32 func_80107704_w05(u8 *choices);
s32 func_80107724_w05(u8 *choices);
void func_800D9F5C_shared_board(Object *arg0, Vec *arg1, s32 arg2);
void func_8001ED54_main(s16 arg0);
void func_8010E790_w05(omObjData *arg0);
void func_8010EE9C_w05(void);
void func_8010F400_w05(void);
void func_80111D84_w05(void);

void func_8010BEC0_w05(Object *obj) {
    s32 i;

    MBModelDispOn(obj);
    i = 0;
    do {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        i += 0xC;
        HuPrcVSleep();
    } while (i < 0x100);
    func_8001F9E4_main(obj->omObj1->model[0], 0xFF);
    func_8001F9E4_main(obj->omObj2->model[0], 0xFF);
}

void func_8010BF60_w05(Object *obj) {
    s32 i;

    i = 0xFF;
    do {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        i -= 0xC;
        HuPrcVSleep();
    } while (i >= 0);
    func_8001F9E4_main(obj->omObj1->model[0], 0);
    func_8001F9E4_main(obj->omObj2->model[0], 0);
    MBModelDispOff(obj);
}

s32 func_8010C000_w05(s32 playerIndex) {
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
    func_80054904_main(grp, 0, D_8011EB4C_w05[playerIndex].x,
                        D_8011EB4C_w05[playerIndex].y);
    func_80055458_main(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        func_80054904_main(grp, 0,
                            (i * D_8011EB6C_w05[playerIndex].x) +
                                D_8011EB4C_w05[playerIndex].x,
                            (i * D_8011EB6C_w05[playerIndex].y) +
                                D_8011EB4C_w05[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    func_80055458_main(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(func_80111D84_w05, 0x4002, 0, 0);
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
                            (D_8011EB6C_w05[playerIndex].x * 16.0f) +
                                D_8011EB4C_w05[playerIndex].x,
                            (D_8011EB6C_w05[playerIndex].y * 16.0f) +
                                D_8011EB4C_w05[playerIndex].y +
                                (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        func_80054904_main(grp, 0,
                            (i * D_8011EB6C_w05[playerIndex].x) +
                                D_8011EB4C_w05[playerIndex].x,
                            (i * D_8011EB6C_w05[playerIndex].y) +
                                D_8011EB4C_w05[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprKill(spriteId);
    return !hasRareItem;
}

void func_8010C448_w05(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

s32 func_8010C46C_w05(s32 playerIndex) {
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
    func_80054904_main(grp, 0, D_8011EB4C_w05[playerIndex].x,
                        D_8011EB4C_w05[playerIndex].y);
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
                            D_8011EB4C_w05[playerIndex].x -
                                (D_8011EB6C_w05[playerIndex].x * 16.0f) - 8.0f,
                            D_8011EB4C_w05[playerIndex].y +
                                (D_8011EB6C_w05[playerIndex].y * 16.0f));
        func_80055458_main(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            func_80054904_main(grp, 0,
                                (i * D_8011EB6C_w05[playerIndex].x) +
                                    D_8011EB4C_w05[playerIndex].x,
                                (i * D_8011EB6C_w05[playerIndex].y) +
                                    D_8011EB4C_w05[playerIndex].y);
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
            omAddPrcObj(func_8010C448_w05, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(func_80111D84_w05, 0x4002, 0, 0);
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
                    (D_8011EB6C_w05[playerIndex].x * 16.0f) +
                        D_8011EB4C_w05[playerIndex].x,
                    (D_8011EB6C_w05[playerIndex].y * 16.0f) +
                        D_8011EB4C_w05[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                func_80054904_main(
                    grp, 0,
                    (D_8011EB6C_w05[playerIndex].x * 16.0f) +
                        D_8011EB4C_w05[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (D_8011EB6C_w05[playerIndex].y * 16.0f) +
                        D_8011EB4C_w05[playerIndex].y);
                func_80054904_main(
                    playerGrp, 0,
                    D_8011EB4C_w05[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (D_8011EB6C_w05[playerIndex].y * 16.0f) +
                        D_8011EB4C_w05[playerIndex].y);
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
                            playerGrp, 0, D_8011EB4C_w05[playerIndex].x - 8.0f,
                            (D_8011EB6C_w05[playerIndex].y * 16.0f) +
                                D_8011EB4C_w05[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                func_80055140_main(playerGrp, 0, 0, 0);
                func_800550F4_main(playerGrp, 0, 1);
                playerSpriteVisible = 0;
                func_80054904_main(
                    playerGrp, 0,
                    D_8011EB4C_w05[playerIndex].x -
                        (D_8011EB6C_w05[playerIndex].x * 16.0f) - 8.0f,
                    (D_8011EB6C_w05[playerIndex].y * 16.0f) +
                        D_8011EB4C_w05[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(func_8010C448_w05, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011EB6C_w05[playerIndex].x) +
                                    D_8011EB4C_w05[playerIndex].x,
                                (i * D_8011EB6C_w05[playerIndex].y) +
                                    D_8011EB4C_w05[playerIndex].y);
            func_80055458_main(grp, 0, i << 4);
            func_80055458_main(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011EB6C_w05[playerIndex].x) +
                                    D_8011EB4C_w05[playerIndex].x,
                                (i * D_8011EB6C_w05[playerIndex].y) +
                                    D_8011EB4C_w05[playerIndex].y);
            func_80054904_main(playerGrp, 0,
                                ((i - 0x10) * D_8011EB6C_w05[playerIndex].x) +
                                    D_8011EB4C_w05[playerIndex].x - 8.0f,
                                (i * D_8011EB6C_w05[playerIndex].y) +
                                    D_8011EB4C_w05[playerIndex].y);
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
        for (i = 0; i < ARRAY_COUNTU(D_8011EB8C_w05); i++) {
            if ((GwSystem.current_turn >= D_8011EB8C_w05[i][0]) &&
                (GwSystem.current_turn <= D_8011EB8C_w05[i][1])) {
                break;
            }
        }
        playerSpriteVisible = D_8011EB8C_w05[i][2];
        for (i = 0; i < ARRAY_COUNTU(D_8011EBA0_w05); i++) {
            if ((attempts >= D_8011EBA0_w05[i][0]) &&
                (attempts <= D_8011EBA0_w05[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= D_8011EBA0_w05[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

void func_8010D298_w05(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_80120830_w05);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += D_80120628_w05;
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void func_8010D3EC_w05(Object *obj) {
    omAddPrcObj(func_8010D298_w05, 0x1000, 0, 0)->user_data = obj;
}

void func_8010D428_w05(void) {
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
    if (spaceId != 79) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(D_801207E0_w05);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 99;
        space = MBMasuGet(99);
        boo = D_801207E4_w05[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (D_8011EBE0_w05[sys->current_board_index] != 0) {
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
            if (D_8011EBE0_w05[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011EBE0_w05[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (D_8011EBE0_w05[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    func_8010BEC0_w05(boo);
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
    menuResult = func_80107704_w05(choices);
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
    playerChoice = func_80107724_w05(choices);
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
                func_80106B38_w05();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106AB0_w05();
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
        if (rank < D_8011EBD4_w05[i]) {
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
            if (GwSystem.current_turn >= D_8011EB8C_w05[i][0] &&
                GwSystem.current_turn <= D_8011EB8C_w05[i][1]) {
                break;
            }
        }
        estimatedAmount = D_8011EB8C_w05[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    func_8010BF60_w05(boo);
    if (menu == 0) {
        resultAmount = func_8010C46C_w05(target);
        func_8010BEC0_w05(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], D_80120624_w05, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], D_80120624_w05, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= D_8011EBCC_w05[i]) {
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
            D_80120830_w05 = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(D_80120830_w05);
            MBModelDispOff(D_80120830_w05);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    func_8010D3EC_w05(boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(D_80120830_w05);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            func_8004ACE0_main(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = func_8010C000_w05(target);
        func_8010BEC0_w05(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            D_8011D0C8_w05 = 1;
            func_80106A3C_w05(boo);
            D_8011D0C8_w05 = 0;
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
    func_8010BF60_w05(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        func_80106B38_w05();
        D_800CB99C_main = 1;
        func_80049FB8_main();
    } else {
        func_80106AB0_w05();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        func_8010BF60_w05(boo);
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
            if (D_8011EBE0_w05[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011EBE0_w05[sys->current_board_index] != 0) {
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
    func_801096D4_w05();
}

void func_8010E5FC_w05(void) {
    func_80108664_w05(0);
}

void func_8010E618_w05(void) {
    func_80108664_w05(1);
}

omObjData *func_8010E634_w05(Vec *pos, f32 scaleStep, f32 alphaStep, s16 killOnFade, Vec *vel, s32 large) {
    omObjData *obj;
    X2ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, func_8010E790_w05);
    data = obj->data = HuMemAllocTag(sizeof(X2ModelFadeWork), 0x7918);
    data->alpha = 255.0f;
    data->scaleStep = scaleStep;
    data->alphaStep = alphaStep;
    HuVecCopy3F(&data->vel, vel);
    if (large != 0) {
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

void func_8010E790_w05(omObjData *obj) {
    X2ModelFadeWork *data = obj->data;
    Object *model = data->model;
    f32 scale;
    f32 alpha;

    HuVecAdd(&model->coords, &model->coords, &data->vel);
    scale = model->scale.z + data->scaleStep;
    model->scale.z = scale;
    model->scale.y = scale;
    model->scale.x = scale;
    alpha = data->alpha - data->alphaStep;
    data->alpha = alpha;
    if (alpha < 0.0f) {
        data->alpha = 0.0f;
        if (data->killOnFade != 0) {
            MBModelKill(data->model);
            omDelObj(obj);
            return;
        }
        omSetStatBit(obj, 8);
    }
    func_8001F9E4_main(model->omObj1->model[0], (u8)data->alpha);
}

void func_8010E8A8_w05(void) {
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
    func_8010F400_w05();
    lamp = MBModelCreate(0x24, NULL);
    Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&lamp->coords, &player->player_obj->coords);
    lamp->coords.y = 100.0f;
    do {
        lamp->coords.y -= 1.0f;
        HuPrcVSleep();
    } while (lamp->coords.y > 30.0f);

    HuAudFXPlay(0x127);
    func_8004A7C4_main(0xB4);
    vib = MBPlayerVibrateObjCreate(CUR_PLAYER, 4, 5);

    angle = 0xB4;
    i = 0;
    do {
        X2DirTable dirs = D_80120630_w05;

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010E634_w05(&pos, 0.1f, 2.0f, 1, &dirs.dir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    } while (angle < 0x438);

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    func_800EB24C_shared_board(D_8011D070_w05[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
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
        X2DirTable dirs2 = D_80120630_w05;

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010E634_w05(&pos, 0.1f, 2.0f, 1, &dirs2.dir[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            func_80003A70_main(0);
        }
    }
}

void func_8010EC70_w05(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011D070_w05[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void func_8010ECDC_w05(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    func_8010F400_w05();
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

void func_8010EE9C_w05(void) {
    X2SpriteMoveWork *work = HuPrcCurrentGet()->user_data;
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
            func_80054904_main(work->spriteGroup, 0, work->startX + (deltaX * i), work->startY + (deltaY * i));
        }
        MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(), spriteX + (deltaX * i), spriteY + (deltaY * i));
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

Process *func_8010F100_w05(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration) {
    Process *process;
    X2SpriteMoveWork *work;

    process = omAddPrcObj(func_8010EE9C_w05, 0x4002, 0, 0x40);
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

void func_8010F1D0_w05(void) {
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
    HuPrcChildLink(process, func_8010F100_w05(
                                mbItemCursorGrpId, position[0], position[1],
                                D_8011ECB4_w05[system->current_player_index].x,
                                D_8011ECB4_w05[system->current_player_index].y, -1));
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

void func_8010F400_w05(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    func_8010F100_w05(
        mbItemCursorGrpId, position[0], position[1],
        D_8011ECD4_w05[system->current_player_index].x,
        D_8011ECD4_w05[system->current_player_index].y, -1);
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

void func_8010F5D0_w05(void) {
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
                   func_8010F100_w05(mbItemCursorGrpId, position[0], position[1],
                                            targetX, targetY, -1));
    HuPrcChildWait();

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8010F740_w05(void) {
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
                   func_8010F100_w05(mbItemCursorGrpId, position[0], position[1],
                                            D_8011ECB4_w05[system->current_player_index].x,
                                            D_8011ECB4_w05[system->current_player_index].y, -1));
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

void func_8010FA8C_w05(void) {
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
                   func_8010F100_w05(mbItemCursorGrpId, position[0], position[1],
                                            D_8011ECB4_w05[system->current_player_index].x,
                                            D_8011ECB4_w05[system->current_player_index].y, -1));
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

void func_8010FC50_w05(s32 playerNo, s32 itemNo, s32 duration, f32 *target, s32 mode) {
    f32 position[2];
    f32 stepX;
    f32 stepY;
    f32 scale;
    s32 i;

    if (mode == 2) {
        HuAudFXPlay(0x145);
    }

    func_800F6848_shared_board(playerNo, itemNo, &position[0], &position[1]);
    stepX = (target[0] - position[0]) / duration;
    stepY = (target[1] - position[1]) / duration;

    for (i = 2; duration != 0; duration--, i++) {
        position[0] += stepX;
        position[1] += stepY;
        MBStatusItemPosSet(playerNo, itemNo, position[0], position[1]);

        if ((mode == 1) && (i < 11)) {
            MBStatusItemTPLvlSet(playerNo, itemNo, i * 25);
            scale = i * 0.07f;
            MBStatusItemScaleSet(playerNo, itemNo, scale + 0.3f, scale + D_80120690_w05);
        }
        HuPrcVSleep();
    }

    MBStatusItemPosSet(playerNo, itemNo, target[0], target[1]);

    if (mode == 0) {
        i = 1;
        do {
            MBStatusItemTPLvlSet(playerNo, itemNo, 255 - (i * 25));
            MBStatusItemScaleSet(playerNo, itemNo, 1.0f - (i * 0.1f), 1.0f - (i * 0.1f));
            i++;
            HuPrcVSleep();
        } while (i < 10);
        MBStatusItemTPLvlSet(playerNo, itemNo, 0);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/w05/37FFB0", D_80120690_w05);

void func_8010FEE8_w05(void) {
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

void func_80110174_w05(void) {
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

void func_801103B4_w05(void) {
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
    func_80055024_main(group, 0, D_80120834_w05, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x1000);
    func_800F6848_shared_board(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    func_80054904_main(group, 0, x, y);
    func_80055420_main(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)D_8011EDA0_w05[index];
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

void func_801105C4_w05(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_80120834_w05 = func_80055810_main(data);
    DataClose(data);
    func_8010FA8C_w05();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = func_801096DC_w05((s32)D_8011ED34_w05, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(func_80109A1C_w05, 0, 0, 0);
                omPrcSetStatBit(process, 0x80);
                func_80106B38_w05();
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

        process = omAddPrcObj(func_80109A1C_w05, 0, 0, 0);
        omPrcSetStatBit(process, 0x80);
        func_80106B38_w05();
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
            process = omAddPrcObj(func_801103B4_w05, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_801103B4_w05, 0x4002, 0, 0);
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
    HuSprKill(D_80120834_w05);
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
    func_8010AC0C_w05();
    GwSystem.forceShopHost = 0;
}

void func_80110884_w05(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_80120834_w05 = func_80055810_main(data);
    DataClose(data);
    func_8010FA8C_w05();

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_801103B4_w05, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWait();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_801103B4_w05, 0x4002, 0, 0);
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
        choice = func_801096DC_w05(1, 0);
    } else {
        choice = func_801096DC_w05(2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = func_800EF0D8_shared_board(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(func_80109A1C_w05, 0, 0, 0);
            omPrcSetStatBit(process, 0x80);
            func_80106B38_w05();
            one = 1;
            D_800CB99C_main = one;
            func_80049FB8_main();
            omDelPrcObj(process);
            func_800FC8A4_shared_board();
            goto retry;
        default:
            MBDlgWinInsertCreate(4, 0x3A0B,
                                 (s32)((char **)0x801014A0)[GwPlayer[choice].chr],
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
    HuSprKill(D_80120834_w05);

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

void func_80110C24_w05(void) {
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
        func_8010F400_w05();

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
        X2DirTable velocities = D_80120630_w05;

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010E634_w05(&pos, 0.1f, 2.0f, 1,
                                     &velocities.dir[(i / 2) & 7], 1);
        }
        HuPrcVSleep();
    }

    alpha = 0xFF;
    speed = 0.0f;
    while (1) {
        X2DirTable velocities2 = D_80120630_w05;

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010E634_w05(&pos, 0.1f, 2.0f, 1,
                                     &velocities2.dir[(i / 2) & 7], 1);
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

        space = MBMasuGet(D_8011D070_w05[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(D_8011D080_w05[system->star_spawn_indices[system->current_star_spawn]]);
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
        if (D_80120768_w05[j] != NULL) {
            omDelPrcObj(D_80120768_w05[j]);
            D_80120768_w05[j] = NULL;
        }
    }

    targetStar = D_80120748_w05[system->star_spawn_indices[system->current_star_spawn]];
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

void func_80111620_w05(void) {
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
                   func_8010F100_w05(mbItemCursorGrpId, position[0], position[1],
                                            D_8011ECB4_w05[system->current_player_index].x,
                                            D_8011ECB4_w05[system->current_player_index].y, -1));
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
    result = func_801096DC_w05((s32)&D_8011EDB4_w05, 0);
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
            func_80106B38_w05();
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

void func_80111B68_w05(void) {
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
    func_80055024_main(setupGroup, 0, D_8012083C_w05, 0);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, 0x1000);
    MBStatusItemPosGet(D_80120838_w05, 0, &xPos, &yPos);

    xPos = (s32)((D_8011EB6C_w05[D_80120838_w05].x * 16.0f) +
                 D_8011EB4C_w05[D_80120838_w05].x);
    yPos = (s32)((D_8011EB6C_w05[D_80120838_w05].y * 16.0f) +
                 D_8011EB4C_w05[D_80120838_w05].y);
    func_80054904_main(
        setupGroup, 0, (f32)xPos + D_8011EDC0_w05[playerIndex].x,
        (f32)yPos + D_8011EDC0_w05[playerIndex].y);
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

// board r3: item effects, last-5-turns and branch/mushroom events func_80111D84_w05..func_8011720C_w05 (twins of w02 func_80112340_w02..func_801177C8_w02 and ChillyWaters MB1Ev_*)
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
void func_80106B38_w05(void);
void func_80107FF4_w05(void);
s32 func_801096DC_w05(s32 arg0, s32 arg1);
Process *func_8010F100_w05(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration);
void func_8010F400_w05(void);
void func_80111B68_w05(void);
extern u8 D_80120620_w05[];
extern char D_80120624_w05[];
typedef struct R3ItemExchangeWork {
    Object* unk_00;
    Object* unk_04;
    s32 unk_08;
    s32 unk_0C;
    char unk_10[0x10];
} R3ItemExchangeWork; // board r3
typedef struct R3Bytes4 {
    u8 b[4];
} R3Bytes4; // board r3
extern s32 D_8011EDF0_w05;
extern u8 D_8011EDF4_w05[4];
extern u8 D_8011EDF8_w05[4];
extern u16 D_8011EDFC_w05[7][2];
extern RGB D_8011EE18_w05[2];
extern s32 D_80120838_w05;
extern s32 D_8012083C_w05;
extern Object* D_80120840_w05;
extern Object* D_80120844_w05;
extern s32 D_80120848_w05;
extern s32 D_8012084C_w05;
extern Object* D_80120850_w05;
extern s32 D_80120858_w05[4];
extern void* D_80120868_w05;
void func_80109960_w05(s16 arg0, s32 arg1, s16 arg2, s32 arg3);
void func_8010FC50_w05(s32 arg0, s32 arg1, s32 arg2, f32* arg3, s32 arg4);

typedef s16 R3SpaceTriple[3];
typedef BranchLink R3BranchPair[2];

void func_80106B94_w05(void);
void func_80106C64_w05(void);
void func_8010F5D0_w05(void);
s32 func_80112910_w05(u8 *arg0, s32 arg1);
void func_80115C28_w05(s32 arg0);
void func_80115CA0_w05(void);
void func_80115D04_w05(omObjData *obj);
void func_80115EB0_w05(s32 arg0, s32 arg1);
void func_80115FB0_w05(s32 arg);
void func_801164B8_w05(void);
void func_80116A80_w05(void);
extern Object *D_80120870_w05[4];
extern omObjData *D_80120880_w05[4];
extern s32 D_80120890_w05;
extern s32 D_80120894_w05;
extern Vec2f D_8011ECF4_w05[]; /* splat labels D_8011ECF4 (x) / D_8011ECF8 (rest): one Vec2f[4] */
extern Vec2f D_8011ED14_w05[]; /* D_8011ED14 / D_8011ED18 likewise */


void func_80111D84_w05(void) {
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
    D_8012083C_w05 = func_80055810_main(file);
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
    D_80120838_w05 = playerNo;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            proc = omAddPrcObj(func_80111B68_w05, 0x4002, 0, 0);
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
    HuSprKill(D_8012083C_w05);
    HuSprKill(charmSpr);
    HuSprKill(booSpr);
    omDelPrcObj(NULL);
}

// ChillyWaters MB1Ev_ItemNullUse
void func_80112178_w05(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void func_80112234_w05(void) {
    Object* modelObj;
    f32 angle;
    Object* obj;

    obj = HuPrcCurrentGet()->user_data;
    modelObj = MBModelLinkCreate(D_80120840_w05);
    HuVecCopy3F(&modelObj->coords, &obj->coords);
    HuVecCopyXYZ(&modelObj->scale, 2.0f, 2.0f, 2.0f);
    modelObj->velocity.x = obj->velocity.x + 10.0f;
    MBModelDispOn(modelObj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        modelObj->velocity.x += 1.5;
        if ((obj->velocity.x + 35.0f) <= modelObj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[modelObj->omObj1->model[0]].mtx, angle);
    }

    MBModelKill(modelObj);
    omDelPrcObj(NULL);
}


void func_80112388_w05(Object* arg0) {
    omAddPrcObj(func_80112234_w05, 0x1000, 0, 0)->user_data = arg0;
}

void func_801123C4_w05(void) {
    s32 *done = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *system = &GwSystem;

    while (1) {
        D_80120844_w05->rot.x = -sindf(angle);
        D_80120844_w05->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }

        if (*done != 0) {
            D_80120844_w05->scale.x =
            D_80120844_w05->scale.y =
            D_80120844_w05->scale.z = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }

    D_80120844_w05->scale.x =
    D_80120844_w05->scale.y =
    D_80120844_w05->scale.z = 0.0f;
    GwPlayer[system->current_player_index].itemNo[MBItemFind(CUR_PLAYER, ITEM_KOOPA_KARD)] = ITEM_NONE;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBModelKill(D_80120844_w05);
    omDelPrcObj(NULL);
}

void func_80112388_w05(Object *);

void func_80112554_w05(void) {
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
    func_8010F400_w05();

    D_80120844_w05 = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&D_80120844_w05->coords,
                &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    D_80120844_w05->velocity.x = 100.0f;
    while (D_80120844_w05->velocity.x > 30.0f) {
        D_80120844_w05->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(func_801123C4_w05, 0x4002, 0, 0)->user_data = &done;
    vib = MBPlayerVibrateObjCreate(-1, 4, 5);

    amount = GwSystem.bank_coins;
    step = (f32)amount / 30.0f;
    frac = 0.0f;
    coin = MBModelCreate(0x19, NULL);
    D_80120840_w05 = coin;
    MBModelTempAllocFree(coin);
    MBModelDispOff(D_80120840_w05);

    while (amount != 0) {
        frac += step;
        n = 0;
        while (frac >= 1.0f) {
            frac -= 1.0f;
            n++;
        }
        if (n != 0) {
            func_80112388_w05(D_80120844_w05);
            if ((amount - n) < 0) {
                n = amount;
            }
            amount -= n;
            MBPlayerCoinAdd(system->current_player_index, n);
            HuAudFXPlay(0x106);
            GwSystem.bank_coins -= n;
            func_80107FF4_w05();
            HuPrcSleep(5);
        }
    }

    MBPlayerVibrateObjKill(vib);
    done = 1;
    HuPrcSleep(0x14);
    MBModelKill(D_80120840_w05);
    MBVecForwardSet(&MBPlayerGet(CUR_PLAYER)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    func_8004ACE0_main(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 func_80112910_w05(u8 *arg0, s32 arg1) {
    s32 count = 0;
    s16 sp18[MB_MAX_PLAYERS];
    R3Bytes4 sp20 = *(R3Bytes4 *)D_80120620_w05;
    s32 i;
    s32 j;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 != 0) {
                    count = D_80120848_w05 + 1;
                } else {
                    count = D_8012084C_w05 + 1;
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

void func_80112BA8_w05(void) {
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

void func_80112CB4_w05(void) {
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
void func_80112E90_w05(void) {
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

    func_8010F400_w05();
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
    targetPlayer = func_80112910_w05(choices, 1);
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
                    func_8010FC50_w05(system->current_player_index, itemSlot, 10, &position.x, 0);
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
        process = omAddPrcObj(func_80112BA8_w05, 0x4800, 0, 0);
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
        process = omAddPrcObj(func_80112CB4_w05, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8010FC50_w05(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8010FC50_w05(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8010FC50_w05(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_8010FC50_w05(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8010FC50_w05(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_8010FC50_w05(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_8010FC50_w05(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_8010FC50_w05(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                func_8010FC50_w05(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_8010FC50_w05(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_8010FC50_w05(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                func_8010FC50_w05(targetPlayer, 2, 7, &target.x, 2);
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

void func_80113B3C_w05(void) {
    Object* temp_s1;
    Object* temp_s0;
    R3ItemExchangeWork* temp_s2;

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

void func_80113BFC_w05(void) {
    Object *coin;
    Object *obj;
    Process *proc;
    R3ItemExchangeWork *work;
    s32 *flag;
    s32 light;
    f32 angle;
    f32 speed;
    f32 decel;
    f32 scale;
    s32 i;

    flag = HuPrcCurrentGet()->user_data;
    coin = D_80120850_w05;
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
        if (D_8011EDF0_w05 != -1) {
            HuVecCopy3F(&coin->coords,
                        &MBPlayerGet(D_8011EDF0_w05)->player_obj->coords);
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
    proc = omAddPrcObj(func_80113B3C_w05, 0x4800, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, sizeof(R3ItemExchangeWork));
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
void func_8011412C_w05(void) {
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

    func_8010F400_w05();
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
    D_80120850_w05 = temp_v0_2;
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
    sel = func_801096DC_w05(NULL, 0);
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
            func_80106B38_w05();
            D_800CB99C_main = 1;
            func_80049FB8_main();
            goto loop;
    }

    sp20 = 1;
    omAddPrcObj(func_80113BFC_w05, 0x4002U, 0, 0)->user_data = &sp20;
    while(sp20) {
        HuPrcVSleep();
    }
    
    if (sel != system->current_player_index) {
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        D_8011EDF0_w05 = sel;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(sel)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(sel)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(0xA);
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(0x1E);
        D_8011EDF0_w05 = sel;
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
        func_80109960_w05(0xA, 0x2F00, -1, sel);
        GwPlayer[sel].gameCoin = GwPlayer[sel].coin;
        MBCoinChangeCreate(sel, -GwPlayer[sel].coin);
        MBCoinTakeCreate(sel, -GwPlayer[sel].coin);
        HuPrcSleep(0x1E);
        func_80109960_w05(0xA, 0x2F02, -1, sel);
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
        func_80109960_w05(0xA, 0x2F01, -1, sel);
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
            if (D_8011EDFC_w05[i][1] >= temp_a0) {
                break;
            }
        }
        if (D_8011EDFC_w05[i][0] != 0) {
            char sp28[16]; // required to be here or the codegen changes(?!)
            
            var_s1 = GwPlayer[sel].gameCoin * D_8011EDFC_w05[i][0];
            if (var_s1 >= 1000) {
                var_s1 = 999;
            }
            sprintf(sp28, D_80120624_w05, var_s1);
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
            if (temp_a0 < D_8011EDF8_w05[var_v1_3]) {
                break;
            }
        }
    
        if (var_v1_3 == 3) {
            var_v1_3 = 2;
        }
        system->minigame_index = D_8011EDF4_w05[var_v1_3];
        GwSystem.playerIndexVisitingBowser = sel;
        func_800FC998_shared_board();
        func_8004A0E0_main();
        func_800FF7F0_shared_board(2);
        HuPrcSleep(-1);
    }
}

// ChillyWaters MB1Ev_After5ItemMove
void func_80114A38_w05(s32 sprGrp, s32 frames, f32 *dest) {
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
void func_80114B70_w05(omObjData *obj) {
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
            func_80054904_main(D_80120858_w05[temp_s1], 0, 0xB1, 0x2C);
            break;
        case 1:
            func_80054904_main(D_80120858_w05[temp_s1], 0, 0x7A, 0x39);
            break;
        default:
            func_80054904_main(D_80120858_w05[temp_s1], 0, 0xA0, 0x98);
            var_s3 = 30;
            break;
    }

    HuSprAttrReset(D_80120858_w05[temp_s1], 0, 0x8000);
    for (i = 0; i < 255; i += 255 / var_s3) {
        func_80055458_main(D_80120858_w05[temp_s1], 0, i);
        HuPrcVSleep();
    }

    func_80055458_main(D_80120858_w05[temp_s1], 0, 0xFF);
    omDelPrcObj(0);
}

// ChillyWaters MB1Ev_After5NumFade
void func_80114CE0_w05(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i, j;

    for (i = 0; i <= 0; i++) {
        sp18.r = D_8011EE18_w05[i].r;
        sp18.g = D_8011EE18_w05[i].g;
        sp18.b = D_8011EE18_w05[i].b;

        sp28.r = (D_8011EE18_w05[i + 1].r - sp18.r) / 30;
        sp28.g = (D_8011EE18_w05[i + 1].g - sp18.g) / 30;
        sp28.b = (D_8011EE18_w05[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            func_80055420_main(D_80120858_w05[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        func_80055420_main(D_80120858_w05[3], 0, D_8011EE18_w05[i + 1].r, D_8011EE18_w05[i + 1].g, D_8011EE18_w05[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

// ChillyWaters MB1Ev_After5Effect
void func_80114EA8_w05(void) {
    Object *obj;
    s32 *state;
    f32 spin;
    f32 scale;

    state = HuPrcCurrentGet()->user_data;
    HuAudFXPlay(0x143);
    obj = D_80120868_w05;
    func_800D9A40_shared_board(obj);

    for (spin = 0.0f, scale = 1.0f; scale < 18.0f; scale += 0.8) {
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

    for (; scale < 40.0f; scale += 0.8) {
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
void func_8011512C_w05(void) {
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
        D_80120858_w05[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = func_80055810_main(temp_v0);
        DataClose(temp_v0);
        func_80055024_main(D_80120858_w05[i], 0, sp18[i], 0);
        HuSprPriSet(D_80120858_w05[i], 0, 0x4780U);
        HuSprAttrSet(D_80120858_w05[i], 0, 0x980CU);
        func_80055458_main(D_80120858_w05[i], 0, 0U);
        func_80055420_main(D_80120858_w05[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    D_80120868_w05 = temp_v0_3;
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
    func_80114A38_w05(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    func_80114A38_w05(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(func_80114B70_w05, 0x4002, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    func_80114A38_w05(temp_s4, 0xA, sp28);
    HuPrcChildWait();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(func_80114B70_w05, 0x4002, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    func_80114A38_w05(temp_s4, 0xA, sp28);
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
            temp_v0_4 = omAddPrcObj(func_80114B70_w05, 0x4002, 0, 0);
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
        HuSprAttrSet(D_80120858_w05[i], 0, 0x8000);
    }

    HuSprAttrReset(D_80120858_w05[3], 0, 0x8000U);
    func_80055458_main(D_80120858_w05[3], 0, 0xFFU);
    func_80054904_main(D_80120858_w05[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_80114CE0_w05, 0x4002, 0, 0));
    sp40 = 0;
    omAddPrcObj(func_80114EA8_w05, 0x4002, 0, 0)->user_data = &sp40;
    HuPrcChildWait();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(D_80120858_w05[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
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
        HuSprScaleSet(D_80120858_w05[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(D_80120858_w05[i]);
        HuSprKill(sp18[i]);
    }

    WipeCreateIn(0xB, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = WATCH_USED;
}


void func_80115A30_w05(R3SpaceTriple *masu, R3BranchPair *links, DecisionTreeNonLeafNode **trees) {
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
    func_80106B94_w05();
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
    func_80106C64_w05();

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

void func_80115C28_w05(s32 arg0) {
    if (D_80120880_w05[arg0] != NULL) {
        omDelObj(D_80120880_w05[arg0]);
        D_80120880_w05[arg0] = NULL;
    }
    if (D_80120870_w05[arg0] != NULL) {
        MBModelKill(D_80120870_w05[arg0]);
        D_80120870_w05[arg0] = NULL;
    }
}

void func_80115CA0_w05(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = D_80120880_w05[i];

        if (obj != NULL) {
            omDelObj(obj);
            D_80120880_w05[i] = NULL;
        }
    }
}

void func_80115D04_w05(omObjData *obj) {
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
        Object *effectObj = D_80120870_w05[playerIdx];

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

void func_80115EB0_w05(s32 arg0, s32 arg1) {
    GW_PLAYER *player = MBPlayerGet(arg0);
    Object *obj;
    u8 modelId;

    if (D_80120870_w05[arg0] == NULL) {
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
        D_80120870_w05[arg0] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        func_800D9A40_shared_board(D_80120870_w05[arg0]);
    }
}

void func_80115FB0_w05(s32 arg) {
    D_80120880_w05[arg] = omAddObj(0x3FFF, 0, 0, -1, func_80115D04_w05);
    D_80120880_w05[arg]->work[0] = arg;
    D_80120880_w05[arg]->work[1] = 0;
    D_80120880_w05[arg]->work[2] = 0;
    D_80120880_w05[arg]->rot.x = (f32)MBRand(360.0f);
    D_80120880_w05[arg]->trans.x = 0;
}

void func_8011604C_w05(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        D_80120880_w05[i] = NULL;
        D_80120870_w05[i] = NULL;
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
            func_80115EB0_w05(i, idx);
            func_80115FB0_w05(i);
        }
    }
    func_800F8D54_shared_board(func_80115CA0_w05);
}

void func_8011614C_w05(void) {
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
            if (D_80120870_w05[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_80120870_w05[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80115C28_w05(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (D_80120870_w05[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_80120870_w05[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80115C28_w05(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}

void func_80116358_w05(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        func_800DCA64_shared_board(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (D_80120870_w05[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_80120870_w05[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_80115C28_w05(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void func_801164B8_w05(void) {
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

void func_80116508_w05(void) {
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
    choice = func_801096DC_w05(2, D_80120894_w05);
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

    func_80115C28_w05(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    func_80115EB0_w05(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_80120870_w05[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_80120870_w05[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    func_80115FB0_w05(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(func_801164B8_w05, 0x4002, 0, 0)->user_data = vib;
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
            HuVecCopyXYZ(&D_80120870_w05[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&D_80120870_w05[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        func_80115C28_w05(loc->current_player_index);
        func_800DCA64_shared_board(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}

void func_80116A80_w05(void) {
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
            if (D_80120870_w05[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_80120870_w05[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80115C28_w05(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (D_80120870_w05[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_80120870_w05[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80115C28_w05(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}

void func_80116C50_w05(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        func_800DCA64_shared_board(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (D_80120870_w05[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_80120870_w05[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_80115C28_w05(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void func_80116D88_w05(void) {
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
    choice = func_801096DC_w05(2, D_80120890_w05);
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

    func_80115C28_w05(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    func_80115EB0_w05(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_80120870_w05[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_80120870_w05[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    func_80115FB0_w05(targetPlayer);
    omAddPrcObj(func_801164B8_w05, 0x4002, 0, 0)->user_data = vib;
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
        func_80116A80_w05();
    }
}

void func_8011720C_w05(void) {
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

    func_8010F400_w05();
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
    targetPlayer = func_80112910_w05(choices, 0);
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
                       D_8011ED14_w05[system->current_player_index].x,
                       D_8011ED14_w05[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F100_w05(-1,
                                            D_8011ED14_w05[system->current_player_index].x,
                                            D_8011ED14_w05[system->current_player_index].y,
                                            D_8011ECF4_w05[system->current_player_index].x,
                                            D_8011ECF4_w05[system->current_player_index].y, 5));
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
    func_8010F5D0_w05();
}


// board r3: copies a start/next/previous space record (six s16, low byte kept) into the player's chain/space fields
void func_801178B4_w05(GW_PLAYER *player, s32 idx, s16 (*tbl)[6]) {
    s16 *p = tbl[idx];

    player->clink = *p++;
    player->cidx = *p++;
    player->nlink = *p++;
    player->nidx = *p++;
    player->blink = p[0];
    player->bidx = p[1];
}

extern s32 D_801207B0_w05[4];

// board r3: w10 func_801084CC_w10's twin. The "who gets the item" panel: a flipping banner, then one card per
// player whose mark follows D_801207B0_w05[player] (0 hidden, 1..4 mark n-1) until a state above 4 closes it.
void func_80117908_w05(void) {
    s32 markSpr[4];
    s32 chrSpr[4];
    s32 cardGrp[4];
    s32 bannerSpr;
    s32 frameSpr;
    s32 bannerGrp;
    Process *curProc;
    Unk3 *helpWin;
    void *data;
    s32 i;
    s32 j;
    s32 flips;
    s32 flipped;
    s32 fading;
    s32 alpha;
    f32 angle;
    f32 t;
    f32 step;
    s32 grp;

    i = 0;
    curProc = HuPrcCurrentGet();
    data = DataRead(0x1300F7);
    bannerSpr = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300F8);
    markSpr[0] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300FB);
    markSpr[1] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300F9);
    markSpr[2] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300FA);
    markSpr[3] = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x1300FC);
    frameSpr = func_80055810_main(data);
    DataClose(data);
    for (; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 8) | 0x210000);
        chrSpr[i] = func_80055810_main(data);
        DataClose(data);
    }
    bannerGrp = HuSprGrpCreate(1, 5);
    func_80055024_main(bannerGrp, 0, bannerSpr, 0);
    HuSprAttrReset(bannerGrp, 0, 0xFFFF);
    HuSprAttrSet(bannerGrp, 0, 0x1008);
    HuSprPriSet(bannerGrp, 0, 0x1000);
    func_80054904_main(bannerGrp, 0, 160, 90);
    angle = 0.0f;
    step = 30.0f;
    flips = 0;
    flipped = 0;
    while (1) {
        if ((angle >= 90.0f) & (flipped == 0)) {
            flipped = 1;
            flips++;
        }
        if (angle >= 360.0f) {
            flipped = 0;
            angle -= 360.0f;
        }
        if ((angle >= 180.0f) & (angle <= 360.0f)) {
            HuSprAttrSet(bannerGrp, 0, 2);
        } else {
            HuSprAttrReset(bannerGrp, 0, 2);
        }
        t = angle;
        if (angle >= 180.0f) {
            t = angle - 180.0f;
        }
        HuSprScaleSet(bannerGrp, 0, 1.0f, sindf(t));
        if (flips >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += step;
    }
    HuSprAttrReset(bannerGrp, 0, 2);
    HuSprScaleSet(bannerGrp, 0, 1.0f, 1.0f);
    helpWin = func_800E210C_shared_board(20, 160, 1);
    for (i = 0; i < 4; i++) {
        grp = cardGrp[i] = HuSprGrpCreate(6, 5);
        func_80055024_main(grp, 0, frameSpr, 0);
        func_800550F4_main(grp, 0, 0);
        HuSprAttrReset(grp, 0, 0xFFFF);
        if (D_801207B0_w05[i] != 0) {
            HuSprAttrSet(grp, 0, 8);
        } else {
            HuSprAttrSet(grp, 0, 0x8000);
        }
        HuSprPriSet(grp, 0, 0x1000);
        func_800554C4_main(grp, 0, -1);
        func_80055024_main(grp, 1, chrSpr[i], 0);
        func_800550F4_main(grp, 1, 0);
        HuSprAttrReset(grp, 1, 0xFFFF);
        if (D_801207B0_w05[i] != 0) {
            HuSprAttrSet(grp, 1, 8);
        } else {
            HuSprAttrSet(grp, 1, 0x8000);
        }
        HuSprPriSet(grp, 1, 0x1000);
        func_80054904_main(grp, 1, 0, -9);
        func_800554C4_main(grp, 1, 0);
        for (j = 0; j < 4; j++) {
            func_80055024_main(grp, j + 2, markSpr[j], 0);
            func_800550F4_main(grp, j + 2, 1);
            HuSprAttrReset(grp, j + 2, 0xFFFF);
            if (D_801207B0_w05[i] == j + 1) {
                HuSprAttrSet(grp, j + 2, 8);
            } else {
                HuSprAttrSet(grp, j + 2, 0x8000);
            }
            HuSprPriSet(grp, j + 2, 0x1000);
            func_80054904_main(grp, j + 2, 0, 9);
            func_800554C4_main(grp, j + 2, 0);
        }
        func_80054904_main(grp, 0, i * 70 + 55, 200);
    }
    HuPrcSleep(20);
    angle = 90.0f;
    flips = 0;
    fading = 0;
    flipped = 0;
    alpha = 0xFF;
    while (1) {
        if ((angle >= 360.0f) & (flipped == 0)) {
            flipped = 1;
            flips++;
        }
        if (angle >= 360.0f) {
            flipped = 0;
            angle -= 360.0f;
        }
        if ((fading == 0) & (flips != 0)) {
            if ((angle >= 90.0f) & (angle < 180.0f)) {
                fading = 1;
            }
        }
        if (fading != 0) {
            alpha -= 0x15;
            if (alpha <= 0) {
                alpha = 0;
            }
        }
        func_80055458_main(bannerGrp, 0, alpha);
        if (flips >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += step;
    }
    HuSprScaleSet(bannerGrp, 0, 1.0f, 0.0f);
    HuSprGrpKill(bannerGrp);
    HuSprKill(bannerSpr);
    curProc->user_data = (void *)1;
    while (1) {
        for (i = 0; i < 4; i++) {
            switch (D_801207B0_w05[i]) {
                case 0:
                    for (j = 0; j < 6; j++) {
                        HuSprAttrSet(cardGrp[i], j, 0x8000);
                    }
                    break;
                case 1:
                    for (j = 0; j < 6; j++) {
                        HuSprAttrReset(cardGrp[i], j, 0x8000);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprAttrSet(cardGrp[i], j + 2, 0x8000);
                    }
                    HuSprAttrReset(cardGrp[i], 2, 0x8000);
                    break;
                case 2:
                    for (j = 0; j < 6; j++) {
                        HuSprAttrReset(cardGrp[i], j, 0x8000);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprAttrSet(cardGrp[i], j + 2, 0x8000);
                    }
                    HuSprAttrReset(cardGrp[i], 3, 0x8000);
                    break;
                case 3:
                    for (j = 0; j < 6; j++) {
                        HuSprAttrReset(cardGrp[i], j, 0x8000);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprAttrSet(cardGrp[i], j + 2, 0x8000);
                    }
                    HuSprAttrReset(cardGrp[i], 4, 0x8000);
                    break;
                case 4:
                    for (j = 0; j < 6; j++) {
                        HuSprAttrReset(cardGrp[i], j, 0x8000);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprAttrSet(cardGrp[i], j + 2, 0x8000);
                    }
                    HuSprAttrReset(cardGrp[i], 5, 0x8000);
                    break;
                default:
                    goto end;
            }
        }
        HuPrcVSleep();
    }
end:
    MBHelpWinKill(helpWin);
    HuSprKill(frameSpr);
    for (i = 0; i < 4; i++) {
        HuSprKill(markSpr[i]);
        HuSprKill(chrSpr[i]);
        HuSprGrpKill(cardGrp[i]);
    }
    omDelPrcObj(NULL);
}

// board r4: declarations for func_80118364_w05..func_8011CFB4_w05
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
#include "../ovl_80_shared_board/106640.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "input.h"
#include "game/window.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "WaluigisIsland.h" /* BranchLink */

void func_80106120_w05(void);
void func_8010782C_w05(void);
s32 func_8010A944_w05(s32);
s32 func_8010A9CC_w05(void);
s32 func_8011C50C_w05(void);
s32 func_8011C39C_w05(void);
s32 func_8011C448_w05(void);
s32 func_8011C560_w05(s32, s32);
void func_80118BBC_w05(void);
void func_8011AEA4_w05(void);
void func_8011BC40_w05(s32, SpaceData *);
void func_8011C2A8_w05(void);
void func_8011C2F8_w05(void);
extern s32 D_8011D0CC_w05;
extern Object *D_801207C4_w05;
extern Object *D_801207C8_w05;
extern RectF D_8011F128_w05;

#define R4_ABSF(x) (((x) < 0.0f) ? -(x) : (x))

typedef struct W05PlayerWork {
    /* 0x00 */ s32 playerNo;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 slot;
    /* 0x0C */ s32 dir;
    /* 0x10 */ s32 unk10[4];
} W05PlayerWork; // sizeof 0x20

Process *func_800ED75C_shared_board(Vec *arg0, Vec *arg1, Vec *arg2, f32 arg3);
void func_801178B4_w05(GW_PLAYER *player, s32 idx, s16 (*links)[6]);
void func_80119A4C_w05(void);
void func_801192AC_w05(void);
void func_80119610_w05(void);
extern s16 D_8011EE48_w05[][6];
extern f32 D_8011EF38_w05[][2];
extern f32 D_8011EF50_w05[];
extern f32 D_8011EF70_w05[];
extern Object *D_801207CC_w05;
void func_80119F04_w05(void);
extern DecisionTreeNonLeafNode D_8011E2A4_w05[];
extern s32 D_801207B0_w05[4];
extern s32 D_801207C0_w05;
void func_80117908_w05(void);
void func_80119BC4_w05(void);
void func_80119F7C_w05(void);
void func_8011A6E8_w05(void);
void func_8011A8D8_w05(void);
void func_8011ABEC_w05(s16 *masuList, s32 dir, s32 mode, s32 row);
s32 func_8011AD34_w05(s32 dir);
extern DecisionTreeNonLeafNode D_8011E0D0_w05[];
extern DecisionTreeNonLeafNode D_8011E124_w05[];
extern DecisionTreeNonLeafNode D_8011E1C0_w05[];
extern DecisionTreeNonLeafNode D_8011E274_w05[];
extern s16 *D_8011EF10_w05[4];
extern Process *D_801207D0_w05;
extern s16 *D_8011EF30_w05[2];
extern Vec D_801207D4_w05;
void func_8004AE00_main(s16 handle, s16 pan);
void func_80106B94_w05(void);
void func_80106C64_w05(void);
extern s16 D_8011EF78_w05[];
extern s16 D_8011EF80_w05[];
extern s16 D_8011EF88_w05[];
extern s16 D_8011EF90_w05[];
extern DecisionTreeNonLeafNode D_8011E2B0_w05[];
extern DecisionTreeNonLeafNode D_8011E31C_w05[];
extern DecisionTreeNonLeafNode D_8011E34C_w05[];
extern DecisionTreeNonLeafNode D_8011E370_w05[];
void func_80106AB0_w05(void);
s32 func_801096DC_w05(s32 arg0, s32 arg1);
void func_80115A30_w05(s16 (*masu)[3], BranchLink (*links)[2], DecisionTreeNonLeafNode **trees);
void func_80118464_w05(void);
extern DecisionTreeNonLeafNode D_8011DF38_w05[];
extern DecisionTreeNonLeafNode D_8011DF68_w05[];
extern DecisionTreeNonLeafNode D_8011E004_w05[];
extern DecisionTreeNonLeafNode D_8011E028_w05[];
extern s16 D_8011E438_w05[][3];
extern BranchLink D_8011E44C_w05[][2];
extern DecisionTreeNonLeafNode *D_8011D74C_w05[];
extern s16 D_8011E5A0_w05[][3];
extern BranchLink D_8011E5B4_w05[][2];
extern DecisionTreeNonLeafNode *D_8011DA88_w05[];
extern u32 D_8011EE78_w05[];
extern Vec D_8010125C_shared_board;
void func_80118CF8_w05(void);
extern s32 D_8011EB38_w05;
extern s32 D_801204B8_w05;
extern DecisionTreeNonLeafNode D_8011F5DC_w05[];
extern DecisionTreeNonLeafNode D_8011F648_w05[];
extern DecisionTreeNonLeafNode D_8011F924_w05[];
extern DecisionTreeNonLeafNode D_8011FB04_w05[];
extern DecisionTreeNonLeafNode D_8011FCC0_w05[];
extern DecisionTreeNonLeafNode D_8011FD50_w05[];
extern DecisionTreeNonLeafNode D_8011FFA8_w05[];
extern DecisionTreeNonLeafNode D_801201D0_w05[];
extern DecisionTreeNonLeafNode D_80120344_w05[];
extern DecisionTreeNonLeafNode D_801203B0_w05[];
extern u8 *D_8012053C_w05[8];
extern s8 *D_801205DC_w05[8];
extern DecisionTreeNonLeafNode *D_801205FC_w05[2];
extern DecisionTreeNonLeafNode *D_80120604_w05[2];
extern DecisionTreeNonLeafNode *D_8012060C_w05[];
extern s32 D_80120848_w05;
extern s32 D_8012084C_w05;
extern s32 D_80120890_w05;
extern s32 D_80120894_w05;

void func_80118364_w05(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x2:
        case 0x4C:
            func_80118BBC_w05();
            break;
        case 0x1A:
        case 0x1E:
        case 0x35:
        case 0x4D:
        case 0x51:
        case 0x57:
            func_8011C2A8_w05();
            break;
        default:
            func_8011C2F8_w05();
            break;
    }
    omDelPrcObj(NULL);
}

void func_80118464_w05(void) {
    s32 r = MBRand(10.0f);
    s16 v;

    if (r < 6) {
        v = 0;
    } else if (r < 8) {
        v = 1;
    } else {
        v = 2;
    }
    GwSystem.boardData.halfWordBytes[1] = v;
    GwSystem.boardData.halfWordBytes[2] = -1;
}

void func_801184C0_w05(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    DecisionTreeNonLeafNode *tree;
    s32 item;
    s32 choice;
    s32 grp;
    s32 spr;
    void *data;
    s32 alpha;

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x8E:
            if (GwSystem.boardData.halfWordBytes[0] != 0) {
                goto pass8E;
            }
            break;
        case 0x7C:
            if (GwSystem.boardData.halfWordBytes[0] == 0) {
                goto pass7C;
            }
            break;
        case 0x3:
            if (GwSystem.boardData.halfWordBytes[0] != 0) {
                return;
            }
            break;
        default:
            if (GwSystem.boardData.halfWordBytes[0] == 0) {
                goto passOther;
            }
            break;
    }
    func_800DBEC0_shared_board(sys->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x3:
        case 0x8E:
            func_800ED20C_shared_board(-1, 8, 0x8D);
            break;
        default:
            func_800ED20C_shared_board(-1, 8, 0x8B);
            break;
    }
    HuPrcSleep(8);
    switch (GwSystem.boardData.halfWordBytes[1]) {
        case 0:
            item = ITEM_SKELETON_KEY;
            break;
        case 1:
            item = ITEM_MUSHROOM;
            break;
        default:
            item = ITEM_POISON_MUSHROOM;
            break;
    }
    GwSystem.boardData.halfWordBytes[2] = GwSystem.boardData.halfWordBytes[1];
    HuAudFXPlay(0x1AC);
    if (MBItemFind(sys->current_player_index, item) != -1) {
        MBDlgWinExec(0xC, 0xC01);
    ask:
        MBDlgWinInsertCreate(0xC, 0xC02, GwSystem.boardData.halfWordBytes[1] + 0xC03, 0, 0, 0, 0);
        switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
            case 0x8E:
                tree = D_8011DF38_w05;
                break;
            case 0x3:
                tree = D_8011DF68_w05;
                break;
            case 0x7C:
                tree = D_8011E004_w05;
                break;
            default:
                tree = D_8011E028_w05;
                break;
        }
        choice = func_801096DC_w05((s32)tree, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                HuPrcSleep(20);
                grp = HuSprGrpCreate(1, 5);
                data = DataRead(D_8010197C_shared_board[item]);
                spr = func_80055810_main(data);
                DataClose(data);
                func_80055024_main(grp, 0, spr, 0);
                HuSprPriSet(grp, 0, 0xA);
                func_800550F4_main(grp, 0, 0);
                HuSprAttrSet(grp, 0, 0x180C);
                func_80054904_main(grp, 0, 0xA0, 0x5A);
                func_80055458_main(grp, 0, 0);
                GwPlayer[sys->current_player_index].itemNo[MBItemFind(sys->current_player_index, item)] = -1;
                MBItemRemoveEmpty(sys->current_player_index);
                MBStatusItemIconSprReinit(-1);
                HuAudFXPlay(0x145);
                for (alpha = 0; alpha < 0x100; alpha += 25) {
                    func_80055458_main(grp, 0, alpha);
                    HuPrcVSleep();
                }
                func_80055458_main(grp, 0, 0x100);
                HuPrcSleep(30);
                for (alpha = 0x100; alpha > 0; alpha -= 12) {
                    func_80055458_main(grp, 0, alpha);
                    HuPrcVSleep();
                }
                HuSprKill(spr);
                HuSprGrpKill(grp);
                MBDlgWinExec(0xC, 0xC06);
                D_8011D0CC_w05 = 1;
                do {
                    HuPrcVSleep();
                } while (D_8011D0CC_w05 != 0);
                func_80118464_w05();
                func_800DB884_shared_board(sys->current_player_index);
                HuPrcSleep(10);
                switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
                    case 0x8E:
                    pass8E:
                        func_80115A30_w05(D_8011E438_w05, D_8011E44C_w05, D_8011D74C_w05);
                        break;
                    case 0x7C:
                    pass7C:
                        func_80115A30_w05(D_8011E5A0_w05, D_8011E5B4_w05, D_8011DA88_w05);
                        break;
                    case 0x3:
                        break;
                    default:
                    passOther:
                        MBMoveNextMasuSet(-1, 0xF, 6);
                        player->rev |= 1;
                        break;
                }
                return;
            case 1:
                MBDlgWinExec(0xC, 0xC07);
                break;
            default:
                func_80106AB0_w05();
                goto ask;
        }
    } else {
        MBDlgWinInsertCreate(0xC, 0xC08, GwSystem.boardData.halfWordBytes[1] + 0xC03, 0, 0, 0, 0);
        func_800EC9DC_shared_board();
        MBDlgWinClose();
        MBDlgWinKill();
    }
    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x8E:
            if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 2) {
                MBMoveNextMasuSet(-1, 4, 0);
                player->rev &= ~1;
            } else {
                MBMoveNextMasuSet(-1, 3, 3);
                player->rev |= 1;
            }
            break;
        case 0x7C:
            if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4C) {
                MBMoveNextMasuSet(-1, 0xC, 0);
                player->rev &= ~1;
            } else {
                MBMoveNextMasuSet(-1, 0xF, 3);
                player->rev |= 1;
            }
            break;
        case 0x3:
            MBMoveNextMasuSet(-1, 0xE, 3);
            player->rev &= ~1;
            break;
        default:
            MBMoveNextMasuSet(-1, 0x10, 1);
            player->rev &= ~1;
            break;
    }
    func_800DB884_shared_board(sys->current_player_index);
    HuPrcSleep(10);
}


void func_80118BBC_w05(void) {
    Vec pos;
    GW_PLAYER *player;
    SpaceData *space;

    player = MBPlayerGet(-1);
    HuPrcSleep(20);
    func_800E6FCC_shared_board();
    space = MBMasuGet(0x62);
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &space->coords, &pos, 10));
    HuPrcChildWait();
    MBCameraFocusModeSet(2);
    MBCameraFocusStaticPosSet(&pos);
    D_8011D0CC_w05 = 1;
    do {
        HuPrcVSleep();
    } while (D_8011D0CC_w05 != 0);
    MBDlgResultWinExec(0xC00);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &player->player_obj->coords, &pos, 10));
    HuPrcChildWait();
    MBCameraFocusModeSet(1);
    func_800E6FBC_shared_board();
}

void func_80118CF8_w05(void) {
    s32 idx = (s32)HuPrcCurrentGet()->user_data;
    Object *obj;

    obj = MBModelCreate(0x4D, NULL);
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x62)->coords);
    obj->velocity.x = 150.0f;
    switch (idx) {
        case 0:
            obj->coords.z -= 30.0f;
            HuPrcSleep(2);
            break;
        case 1:
            obj->coords.x += 20.0f;
            obj->coords.z += 30.0f;
            break;
        default:
            obj->coords.x -= 15.0f;
            obj->coords.z += 40.0f;
            HuPrcSleep(5);
            break;
    }
    func_800EE688_shared_board(obj, 0.0f, -1.0f);
    func_800EE6C0_shared_board(obj);
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void func_80118E2C_w05(void) {
    Vec pos;
    GW_PLAYER *player;
    Object *obj;
    Process *prc;
    f32 angle;
    s32 focusMode;
    f32 z;
    s32 i;
    s32 jumped;

    obj = MBModelCreate(0xB, D_8011EE78_w05);
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x62)->coords);
    HuVecCopyXYZ(&obj->scale, 2.5f, 2.5f, 2.5f);
    HuVecCopyXYZ(&obj->rot, -1.0f, 0.0f, 0.0f);
    if (GwSystem.boardData.halfWordBytes[0] != 0) {
        MBMotionSet(obj, 1, 2);
    } else {
        MBMotionSet(obj, 2, 2);
    }
    while (TRUE) {
        if (D_8011D0CC_w05 != 0) {
            player = MBPlayerGet(-1);
            HuAudFXPlay(0x1AC);
            if (GwSystem.boardData.halfWordBytes[0] != 0) {
                MBMotionSet(obj, 0, 0);
                while (MBMotionCheck(obj) == 0) {
                    HuPrcVSleep();
                }
                GwSystem.boardData.halfWordBytes[0] = 0;
            } else {
                MBMotionSet(obj, 0, 4);
                func_8001C6A8_main(
                    obj->omObj1->model[0], D_800CCF58_main[HmfModelData[obj->omObj1->model[0]].unk02].unk02);
                while (func_800D9E80_shared_board(obj) == 0) {
                    HuPrcVSleep();
                }
                GwSystem.boardData.halfWordBytes[0] = 1;
            }
            HuAudFXPlay(0x1AD);
            for (i = 0; i < 3; i++) {
                prc = omAddPrcObj(func_80118CF8_w05, 0x4800, 0, 0);
                prc->user_data = (void *)i;
                HuPrcChildLink(HuPrcCurrentGet(), prc);
            }
            MBPlayerVibrate(-1, 3);
            HuVecCopyXYZ(&pos, D_8010125C_shared_board.x, D_8010125C_shared_board.y, D_8010125C_shared_board.z);
            jumped = 0;
            focusMode = MBCameraFocusModeGet();
            MBCameraFocusModeSet(4);
            MBCameraFocusVecSet(&pos);
            z = pos.z;
            for (angle = 0.0f; angle < 900.0f; angle += 90.0f) {
                HuVecCopyXYZ(&pos, pos.x, pos.y, z + sindf(angle) * 3.0f);
                if (!jumped & (angle > 450.0f)) {
                    jumped = 1;
                    func_800EE688_shared_board(player->player_obj, 5.0f, -1.0f);
                }
                HuPrcVSleep();
            }
            HuVecCopyXYZ(&pos, pos.x, pos.y, pos.z);
            MBCameraFocusModeSet(focusMode);
            func_800EE6C0_shared_board(player->player_obj);
            HuPrcChildWait();
            if (GwSystem.boardData.halfWordBytes[0] != 0) {
                MBMotionSet(obj, 1, 2);
            } else {
                MBMotionSet(obj, 2, 2);
            }
            D_8011D0CC_w05 = 0;
        }
        HuPrcVSleep();
    }
}

void func_801191C0_w05(void) {
    Object *obj;

    D_801207C4_w05 = obj = MBModelCreate(0xD, NULL);
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(GwSystem.boardData.halfWordBytes[3] != 0 ? 0x7F : 0x97)->coords);
    HuVecCopyXYZ(&obj->scale, 1.3f, 1.3f, 1.3f);
    D_801207C8_w05 = obj = MBModelCreate(0xD, NULL);
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(GwSystem.boardData.halfWordBytes[4] != 0 ? 0x85 : 0x71)->coords);
    HuVecCopyXYZ(&obj->scale, 1.3f, 1.3f, 1.3f);
    while (TRUE) {
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
void func_801192AC_w05(void) {
    Vec pos;
    UnkVibrateProcess *vib;
    W05PlayerWork *work;
    Object *gate;
    GW_PLAYER *player;
    Object *obj;
    s32 row;
    s32 slot;
    s32 dir;
    Process *curProc;
    SpaceData *first;
    SpaceData *second;
    s16 mes;
    s16 secondNo;
    f32 *ofs;
    Vec *vec;
    Vec *coords;

    work = HuPrcCurrentGet()->user_data;
    gate = D_801207CC_w05;
    player = MBPlayerGet(work->playerNo);
    obj = player->player_obj;
    row = work->unk4;
    slot = work->slot;
    dir = work->dir;
    curProc = HuPrcCurrentGet();
    switch (dir) {
        case 0:
            mes = 0x92;
            break;
        case 1:
            mes = 0x91;
            break;
        case 2:
            mes = 0x90;
            break;
        default:
            mes = 0x8F;
            break;
    }
    func_800ED20C_shared_board(work->playerNo, 8, mes);
    while (HuVecDistance(&obj->coords, &gate->coords) > slot * 20.0f + 30.0f) {
        HuPrcVSleep();
    }
    vib = MBPlayerVibrateObjCreate(work->playerNo, 0, 5);
    func_8004ACE0_main(0x286, work->playerNo);
    if (work->playerNo == GwSystem.current_player_index) {
        MBPlayerMotionSet(-1, 1, 2);
    } else {
        MBMotionSet(obj, 1, 2);
    }
    switch (dir) {
        case 0:
            first = MBMasuGet(0x35);
            secondNo = 0x36;
            break;
        case 1:
            first = MBMasuGet(0x1A);
            secondNo = 0x1B;
            break;
        case 2:
            first = MBMasuGet(0x82);
            secondNo = 0x43;
            break;
        default:
            first = MBMasuGet(0x6F);
            secondNo = 0x11;
            break;
    }
    second = MBMasuGet(secondNo);
    HuVecCopy3F(&pos, &first->coords);
    coords = &obj->coords;
    MBVecDirGet(coords, &pos, &obj->rot);
    HuPrcChildLink(curProc, func_800ED75C_shared_board(coords, &pos, coords, 2.0f));
    coords = &obj->coords;
    HuPrcChildWait();
    HuVecCopy3F(&pos, &second->coords);
    vec = &pos;
    ofs = D_8011EF38_w05[row + slot];
    vec->x += ofs[0];
    vec->z += ofs[1];
    MBVecDirGet(coords, &pos, &obj->rot);
    HuPrcChildLink(curProc, func_800ED5E0_shared_board(coords, &pos, coords, 2.0f));
    HuPrcChildWait();
    MBPlayerVibrateObjKill(vib);
    if (work->playerNo == GwSystem.current_player_index) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(obj, -1, 2);
    }
    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 1.0f);
    func_800ED128_shared_board(&player->player_obj->rot, &pos, &player->player_obj->rot, 5);
    func_801178B4_w05(player, dir, D_8011EE48_w05);
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801192AC_w05);
#endif

#ifdef NON_MATCHING
void func_80119610_w05(void) {
    Vec pos;
    SpaceData *second;
    SpaceData *first;
    Process *curProc;
    s32 dir;
    s32 slot;
    Object *obj;
    GW_PLAYER *player;
    Object *gate;
    W05PlayerWork *work;
    s16 mes;
    s16 secondNo;

    work = HuPrcCurrentGet()->user_data;
    gate = D_801207CC_w05;
    player = MBPlayerGet(work->playerNo);
    obj = player->player_obj;
    slot = work->slot;
    dir = work->dir;
    curProc = HuPrcCurrentGet();
    switch (dir) {
        case 0:
            mes = 0x92;
            break;
        case 1:
            mes = 0x91;
            break;
        case 2:
            mes = 0x90;
            break;
        default:
            mes = 0x8F;
            break;
    }
    func_800ED20C_shared_board(work->playerNo, 8, mes);
    while (HuVecDistance(&obj->coords, &gate->coords) > slot * 20.0f + 30.0f) {
        HuPrcVSleep();
    }
    func_8004ACE0_main(0x286, work->playerNo);
    if (work->playerNo == GwSystem.current_player_index) {
        MBPlayerMotionSet(-1, 1, 2);
    } else {
        MBMotionSet(obj, 1, 2);
    }
    switch (dir) {
        case 0:
            first = MBMasuGet(0x35);
            secondNo = 0x36;
            break;
        case 1:
            first = MBMasuGet(0x1A);
            secondNo = 0x1B;
            break;
        case 2:
            first = MBMasuGet(0x40);
            secondNo = 0x43;
            break;
        default:
            first = MBMasuGet(0x10);
            secondNo = 0x11;
            break;
    }
    second = MBMasuGet(secondNo);
    HuVecCopy3F(&pos, &first->coords);
    MBVecDirGet(&obj->coords, &pos, &obj->rot);
    HuPrcChildLink(curProc, func_800ED75C_shared_board(&obj->coords, &pos, &obj->coords, 2.0f));
    HuPrcChildWait();
    HuVecCopy3F(&pos, &first->coords);
    if (dir == 2) {
        pos.z += -30.0f;
    } else {
        pos.z += 30.0f;
    }
    MBVecDirGet(&obj->coords, &pos, &obj->rot);
    HuPrcChildLink(curProc, func_800ED5E0_shared_board(&obj->coords, &pos, &obj->coords, 2.0f));
    HuPrcChildWait();
    MBPlayerMotionSet(-1, -1, 2);
    if (dir == 2) {
        HuVecCopyXYZ(&pos, -1.0f, 0.0f, 0.5f);
    } else {
        HuVecCopyXYZ(&pos, 1.0f, 0.0f, -0.5f);
    }
    func_800ED128_shared_board(&player->player_obj->rot, &pos, &player->player_obj->rot, 5);
    HuPrcSleep(30);
    MBPlayerMotionSet(-1, 0, 2);
    HuVecCopy3F(&pos, &second->coords);
    if (dir == 2) {
        pos.x += D_8011EF50_w05[0];
        pos.z += D_8011EF50_w05[1];
    } else {
        pos.x += D_8011EF70_w05[0];
        pos.z += D_8011EF70_w05[1];
    }
    MBVecDirGet(&obj->coords, &pos, &obj->rot);
    HuPrcChildLink(curProc, func_800ED5E0_shared_board(&obj->coords, &pos, &obj->coords, 1.5f));
    HuPrcChildWait();
    if (work->playerNo == GwSystem.current_player_index) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(obj, -1, 2);
    }
    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 1.0f);
    func_800ED128_shared_board(&player->player_obj->rot, &pos, &player->player_obj->rot, 5);
    func_801178B4_w05(player, dir, D_8011EE48_w05);
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119610_w05);
#endif

void func_80119A4C_w05(void) {
    s32 idx = (s32)HuPrcCurrentGet()->user_data;
    Object *obj;
    SpaceData *space;
    f32 angle;

    switch (idx) {
        case 0:
            space = MBMasuGet(0x80);
            obj = D_801207C4_w05;
            break;
        case 1:
            space = MBMasuGet(0x6E);
            obj = D_801207C4_w05;
            break;
        case 2:
            space = MBMasuGet(0x86);
            obj = D_801207C8_w05;
            break;
        default:
            space = MBMasuGet(0x72);
            obj = D_801207C8_w05;
            break;
    }
    angle = 0.0f;
    while (TRUE) {
        obj->omObj1->rot.x = sindf(angle) * 5.0f;
        angle += 45.0f;
        if (angle < 360.0f) {
            angle -= 360.0f;
        }
        if (R4_ABSF(space->coords.x - obj->coords.x) <= 2.0f) {
            break;
        }
        HuPrcVSleep();
    }
    obj->omObj1->rot.x = 0.0f;
    omDelPrcObj(NULL);
}

#ifdef NON_MATCHING
void func_80119BC4_w05(void) {
    f32 d;
    Vec pos;
    s32 idx;
    Object *gate;
    Object *obj;
    SpaceData *space;
    s32 bounced;
    f32 speed;

    idx = (s32)HuPrcCurrentGet()->user_data;
    gate = D_801207CC_w05;
    switch (idx) {
        case 0:
        case 1:
            obj = D_801207C4_w05;
            break;
        default:
            obj = D_801207C8_w05;
            break;
    }
    HuVecCopy3F(&pos, &obj->coords);
    pos.z = gate->coords.z;
    while (TRUE) {
        switch (idx) {
            case 0:
            case 2:
                d = gate->coords.x - obj->coords.x;
                break;
            default:
                d = obj->coords.x - gate->coords.x;
                break;
        }
        if (d < -5.0f) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&obj->coords, &pos, &obj->coords, 10));
    for (bounced = 0, speed = 10.0f; TRUE; speed -= 2.0f) {
        obj->velocity.x += speed;
        if (bounced != 0 && obj->velocity.x <= 7.5f) {
            break;
        }
        if (obj->velocity.x > 7.5f) {
            bounced = 1;
        }
        HuPrcVSleep();
    }
    obj->velocity.x = 7.5f;
    HuAudFXPlay(0x1AE);
    HuAudFXPlay(0x1AF);
    switch (idx) {
        case 0:
            space = MBMasuGet(0x80);
            break;
        case 1:
            space = MBMasuGet(0x6E);
            break;
        case 2:
            space = MBMasuGet(0x86);
            break;
        default:
            space = MBMasuGet(0x72);
            break;
    }
    HuVecCopy3F(&pos, &space->coords);
    omAddPrcObj(func_80119A4C_w05, 0x4800, 0, 0)->user_data = (void *)idx;
    while (TRUE) {
        switch (idx) {
            case 0:
            case 2:
                obj->coords.x -= 2.0f;
                break;
            default:
                obj->coords.x += 2.0f;
                break;
        }
        if (R4_ABSF(space->coords.x - obj->coords.x) <= 2.0f) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&obj->coords, &pos, &obj->coords, 10));
    for (bounced = 0, speed = 8.0f; TRUE; speed -= 2.0f) {
        obj->velocity.x += speed;
        if (bounced != 0 && obj->velocity.x <= 0.0f) {
            break;
        }
        if (obj->velocity.x > 0.0f) {
            bounced = 1;
        }
        HuPrcVSleep();
    }
    obj->velocity.x = 0.0f;
    HuAudFXPlay(0x1AE);
    HuAudFXPlay(0x1AF);
    HuPrcChildWait();
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119BC4_w05);
#endif

void func_80119F04_w05(void) {
    s32 idx = (s32)HuPrcCurrentGet()->user_data;
    s16 mes;

    HuPrcSleep(10);
    switch (idx) {
        case 0:
            mes = 0x91;
            break;
        case 1:
            mes = 0x92;
            break;
        case 2:
            mes = 0x8F;
            break;
        default:
            mes = 0x90;
            break;
    }
    func_800ED20C_shared_board(-1, 8, mes);
    omDelPrcObj(NULL);
}

#ifdef NON_MATCHING
void func_80119F7C_w05(void) {
    GW_SYSTEM *sys;
    Vec pos;
    Vec dir;
    GW_PLAYER *player;
    Object *gate;
    SpaceData *space;
    s32 idx;
    s32 state;
    s32 pressed;
    s32 turned;
    s32 bounced;
    f32 speed;
    s16 masu;

    pressed = 0;
    idx = (s32)HuPrcCurrentGet()->user_data;
    sys = &GwSystem;
    player = MBPlayerGet(-1);
    gate = D_801207CC_w05;
    HuVecCopy3F(&pos, &player->player_obj->coords);
    pos.z = gate->coords.z;
    state = 0;
    while (TRUE) {
        switch (idx) {
            case 0:
            case 2:
                if (gate->coords.x - player->player_obj->coords.x < 46.0f && state != 2) {
                    D_801207B0_w05[sys->current_player_index] = 2;
                }
                if (gate->coords.x - player->player_obj->coords.x < 42.0f) {
                    if ((D_800C9520_main[GwPlayer[sys->current_player_index].pad] & 0x8000) && state == 0) {
                        state = 1;
                        pressed = 1;
                    }
                }
                if (gate->coords.x - player->player_obj->coords.x < 22.0f) {
                    goto done;
                }
                if (pressed != 0) {
                    pressed = 0;
                } else if ((D_800C9520_main[GwPlayer[sys->current_player_index].pad] & 0x8000) && state != 2) {
                    func_8004ACE0_main(0x286, sys->current_player_index);
                    state = 2;
                    D_801207B0_w05[sys->current_player_index] = 4;
                    MBPlayerMotionSet(-1, 4, 2);
                }
                break;
            default:
                if (player->player_obj->coords.x - gate->coords.x < 46.0f && state != 2) {
                    D_801207B0_w05[sys->current_player_index] = 2;
                }
                if (player->player_obj->coords.x - gate->coords.x < 42.0f) {
                    if ((D_800C9520_main[GwPlayer[sys->current_player_index].pad] & 0x8000) && state == 0) {
                        state = 1;
                        pressed = 1;
                    }
                }
                if (player->player_obj->coords.x - gate->coords.x < 22.0f) {
                    goto done;
                }
                if (pressed != 0) {
                    pressed = 0;
                } else if ((D_800C9520_main[GwPlayer[sys->current_player_index].pad] & 0x8000) && state != 2) {
                    func_8004ACE0_main(0x286, sys->current_player_index);
                    state = 2;
                    D_801207B0_w05[sys->current_player_index] = 4;
                    MBPlayerMotionSet(-1, 4, 2);
                }
                break;
        }
        HuPrcVSleep();
    }
done:
    if (MBPlayerComCheck(sys->current_player_index) != 0) {
        if (MBComTreeExec(D_8011E2A4_w05) == 0) {
            state = 1;
        }
    }
    if (state == 1) {
        func_8004ACE0_main(0x3A, sys->current_player_index);
        D_801207B0_w05[sys->current_player_index] = 3;
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&player->player_obj->coords, &pos, &player->player_obj->coords, 10));
        MBPlayerMotionSet(-1, 2, 0);
        for (bounced = 0, speed = 10.0f; TRUE; speed -= 2.0f) {
            player->player_obj->velocity.x += speed;
            if (bounced != 0 && player->player_obj->velocity.x <= 7.5f) {
                break;
            }
            if (player->player_obj->velocity.x > 7.5f) {
                bounced = 1;
            }
            HuPrcVSleep();
        }
        player->player_obj->velocity.x = 7.5f;
        func_8004ACE0_main(0x31, sys->current_player_index);
        func_8004ACE0_main(0x274, sys->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        omAddPrcObj(func_80119F04_w05, 0x4800, 0, 0)->user_data = (void *)idx;
        D_801207C0_w05 = 1;
        switch (idx) {
            case 0:
                masu = 0x7F;
                break;
            case 1:
                masu = 0x97;
                break;
            case 2:
                masu = 0x85;
                break;
            default:
                masu = 0x71;
                break;
        }
        turned = 0;
        space = MBMasuGet(masu);
        HuVecCopy3F(&pos, &space->coords);
        while (TRUE) {
            switch (idx) {
                case 0:
                case 2:
                    player->player_obj->coords.x -= 2.0f;
                    break;
                default:
                    player->player_obj->coords.x += 2.0f;
                    break;
            }
            if (R4_ABSF(player->player_obj->coords.x - space->coords.x) <= 2.0f) {
                break;
            }
            if (R4_ABSF(player->player_obj->coords.x - space->coords.x) <= 24.0f && turned == 0) {
                turned = 1;
                HuVecCopyXYZ(&dir, 0.0f, 0.0f, -1.0f);
                func_800ED128_shared_board(&player->player_obj->rot, &dir, &player->player_obj->rot, 5);
            }
            HuPrcVSleep();
        }
        func_8004ACE0_main(0x3A, sys->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&player->player_obj->coords, &pos, &player->player_obj->coords, 10));
        MBPlayerMotionSet(-1, 2, 0);
        for (bounced = 0, speed = 8.0f; TRUE; speed -= 2.0f) {
            player->player_obj->velocity.x += speed;
            if (bounced != 0 && player->player_obj->velocity.x <= 0.0f) {
                break;
            }
            if (player->player_obj->velocity.x > 0.0f) {
                bounced = 1;
            }
            HuPrcVSleep();
        }
        player->player_obj->velocity.x = 0.0f;
        func_8004ACE0_main(0x31, sys->current_player_index);
        func_8004ACE0_main(0x274, sys->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        HuVecCopyXYZ(&pos, 0.0f, 0.0f, 1.0f);
        func_800ED128_shared_board(&player->player_obj->rot, &pos, &player->player_obj->rot, 10);
    } else if (state == 0) {
        func_8004ACE0_main(0x286, sys->current_player_index);
        D_801207B0_w05[sys->current_player_index] = 4;
        MBPlayerMotionSet(-1, 4, 2);
    }
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119F7C_w05);
#endif

#ifdef NON_MATCHING
void func_8011A6E8_w05(void) {
    s32 idx;
    Object *gate;
    s16 se;
    SpaceData *from;
    SpaceData *to;
    SpaceData *stop;
    s16 toNo;

    idx = (s32)HuPrcCurrentGet()->user_data;
    gate = D_801207CC_w05;
    se = HuAudFXPlay(0x1B0);
    switch (idx) {
        case 0:
        case 1:
            from = MBMasuGet(0x91);
            toNo = 0x92;
            break;
        default:
            from = MBMasuGet(0x8F);
            toNo = 0x90;
            break;
    }
    to = MBMasuGet(toNo);
    switch (idx) {
        case 0:
            stop = MBMasuGet(0x91);
            break;
        case 1:
            stop = MBMasuGet(0x92);
            break;
        case 2:
            stop = MBMasuGet(0x8F);
            break;
        default:
            stop = MBMasuGet(0x90);
            break;
    }
    if (gate->coords.x != stop->coords.x) {
        do {
            func_8004AE00_main(se, R4_ABSF(from->coords.x - gate->coords.x) * 64.0f / R4_ABSF(from->coords.x - to->coords.x) + 32.0f);
            HuPrcVSleep();
        } while (gate->coords.x != stop->coords.x);
    }
    HuAudFXStop(se);
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011A6E8_w05);
#endif

void func_8011A8D8_w05(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    UnkEA790Struct *win;
    s16 *choices;
    DecisionTreeNonLeafNode *tree;
    s32 i;
    s32 count;
    s32 sel;

    func_80106B94_w05();
    player = MBPlayerGet(-1);
    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x7E:
            choices = D_8011EF78_w05;
            break;
        case 0x96:
            choices = D_8011EF80_w05;
            break;
        case 0x84:
            choices = D_8011EF88_w05;
            break;
        default:
            choices = D_8011EF90_w05;
            break;
    }
    win = func_800D76A0_shared_board(sys->current_player_index, choices);
    func_800D742C_shared_board(win, sys->current_player_index, 0);
    if (MBPlayerComCheck(-1) != 0) {
        switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
            case 0x7E:
                tree = D_8011E2B0_w05;
                break;
            case 0x96:
                tree = D_8011E31C_w05;
                break;
            case 0x84:
                tree = D_8011E34C_w05;
                break;
            default:
                tree = D_8011E370_w05;
                break;
        }
        count = MBComTreeExec(tree);
        for (i = 0; i < count; i++) {
            func_800D7250_shared_board(win, -2);
        }
        func_800D7250_shared_board(win, -4);
    }
    sel = func_800D7518_shared_board(win);
    func_800D6CA0_shared_board(win);
    func_80106C64_w05();
    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x7E:
            if (sel == 0) {
                MBMoveNextMasuSet(-1, 0x10, 0x11);
                player->rev |= 1;
            } else {
                MBMoveNextMasuSet(-1, 8, 1);
                player->rev &= ~1;
            }
            break;
        case 0x96:
            if (sel == 0) {
                MBMoveNextMasuSet(-1, 2, 0);
                player->rev |= 1;
            } else {
                MBMoveNextMasuSet(-1, 2, 2);
                player->rev &= ~1;
            }
            break;
        case 0x84:
            if (sel == 0) {
                MBMoveNextMasuSet(-1, 9, 0xC);
                player->rev |= 1;
            } else {
                MBMoveNextMasuSet(-1, 0xA, 1);
                player->rev &= ~1;
            }
            break;
        default:
            if (sel == 0) {
                MBMoveNextMasuSet(-1, 5, 0);
                player->rev |= 1;
            } else {
                MBMoveNextMasuSet(-1, 5, 2);
                player->rev &= ~1;
            }
            break;
    }
    omDelPrcObj(NULL);
}

#ifdef NON_MATCHING
void func_8011ABEC_w05(s16 *masuList, s32 dir, s32 mode, s32 row) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    Process *prc;
    W05PlayerWork *work;
    process_func func;
    s32 slot;
    s32 i;

    slot = 0;
    do {
        for (i = 0; i < 4; i++) {
            if (!(i == sys->current_player_index && mode == 0)) {
                player = MBPlayerGet(i);
                if (*masuList == MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
                    func = func_801192AC_w05;
                    if (mode == 2) {
                        func = func_80119610_w05;
                    }
                    prc = omAddPrcObj(func, 0x4800, 0, 0x40);
                    work = HuMemMemoryAlloc(prc->heap, sizeof(W05PlayerWork));
                    prc->user_data = work;
                    work->playerNo = i;
                    work->unk4 = row;
                    work->slot = slot;
                    work->dir = dir;
                    slot++;
                }
            }
        }
        masuList++;
    } while (*masuList != -1);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011ABEC_w05);
#endif

s32 func_8011AD34_w05(s32 dir) {
    Vec pos[4];
    GW_PLAYER *player;
    SpaceData *space;
    s32 masu;
    s32 i;
    s32 count;
    Vec *p;

    switch (dir) {
        case 0:
            masu = 0x36;
            space = MBMasuGet(0x36);
            break;
        case 1:
            masu = 0x1B;
            space = MBMasuGet(0x1B);
            break;
        case 2:
            masu = 0x43;
            space = MBMasuGet(0x43);
            break;
        default:
            masu = 0x11;
            space = MBMasuGet(0x11);
            break;
    }
    i = 0;
    count = 0;
    do {
        player = MBPlayerGet(i);
        if (masu == MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
            p = &pos[i];
            HuVecCopy3F(p, &space->coords);
            p->x += D_8011EF38_w05[count][0];
            p->z += D_8011EF38_w05[count][1];
            func_800ED5E0_shared_board(&player->player_obj->coords, p, &player->player_obj->coords, 2.0f);
            count++;
        }
        i++;
    } while (i < 4);
    return count;
}

void func_8011AEA4_w05(void) {
    Vec pos;
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    Object *statue;
    Object *gate;
    SpaceData *spaceB;
    SpaceData *spaceC;
    SpaceData *spaceD;
    SpaceData *spaceA;
    SpaceData *space;
    DecisionTreeNonLeafNode *tree;
    s32 dir;
    s32 choice;
    s32 i;

    player = MBPlayerGet(-1);
    D_801207C0_w05 = 0;
    func_800DBEC0_shared_board(sys->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x96:
            func_800ED20C_shared_board(-1, 8, 0x97);
            spaceA = MBMasuGet(0x6E);
            spaceB = MBMasuGet(0x97);
            statue = D_801207C4_w05;
            dir = 0;
            break;
        case 0x7E:
            func_800ED20C_shared_board(-1, 8, 0x7F);
            spaceA = MBMasuGet(0x80);
            spaceB = MBMasuGet(0x7F);
            statue = D_801207C4_w05;
            dir = 1;
            break;
        case 0x70:
            func_800ED20C_shared_board(-1, 8, 0x71);
            spaceA = MBMasuGet(0x72);
            spaceB = MBMasuGet(0x71);
            statue = D_801207C8_w05;
            dir = 2;
            break;
        default:
            func_800ED20C_shared_board(-1, 8, 0x85);
            spaceA = MBMasuGet(0x86);
            spaceB = MBMasuGet(0x85);
            statue = D_801207C8_w05;
            dir = 3;
            break;
    }
    HuPrcSleep(8);
    if (GwPlayer[sys->current_player_index].coin < 5) {
        MBDlgWinExec(8, 0xD01);
        func_800DB884_shared_board(sys->current_player_index);
        goto end;
    }
    HuAudFXPlay(0x1AE);
ask:
    MBDlgWinInsertCreate(8, 0xD00, 0, 0, 0, 0, 0);
    switch (dir) {
        case 0:
            tree = D_8011E0D0_w05;
            break;
        case 1:
            tree = D_8011E124_w05;
            break;
        case 2:
            tree = D_8011E1C0_w05;
            break;
        default:
            tree = D_8011E274_w05;
            break;
    }
    choice = func_801096DC_w05((s32)tree, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    switch (choice) {
        case 0:
            MBCoinChangeCreate(sys->current_player_index, -5);
            MBCoinTakeCreate(sys->current_player_index, -5);
            HuPrcSleep(30);
            MBDlgWinExec(8, 0xD03);
            break;
        case 1:
            MBDlgWinExec(8, 0xD02);
            func_800DB884_shared_board(sys->current_player_index);
            goto end;
        default:
            func_80106AB0_w05();
            goto ask;
    }
    mbItemBtnF = 0;
    D_800A12D8_main = 1;
    MBStatusHideAll();
    func_800E6FCC_shared_board();
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.2f));
    HuPrcChildWait();
    func_800EE688_shared_board(statue, 10.0f, -1.0f);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&statue->coords, &spaceA->coords, &statue->coords, 20));
    MBPlayerMotionSet(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBPlayerPosMoveCreate(&player->player_obj->coords, &spaceB->coords, &player->player_obj->coords, 20));
    HuPrcChildWait();
    func_800EE6C0_shared_board(statue);
    HuAudFXPlay(0x1AE);
    HuAudFXPlay(0x1AF);
    MBPlayerMotionSet(-1, -1, 2);
    func_800ED20C_shared_board(-1, 8, MBMasuLinkMasuIdGet(player->clink, player->cidx));
    HuPrcSleep(8);
    for (i = 0; i < 4; i++) {
        D_801207B0_w05[i] = 0;
    }
    D_801207D0_w05 = omAddPrcObj(func_80117908_w05, 0x4800, 0, 0);
    while (D_801207D0_w05->user_data == NULL) {
        HuPrcVSleep();
    }
    D_801207B0_w05[sys->current_player_index] = 1;
    switch (dir) {
        case 0:
            spaceA = MBMasuGet(0x92);
            spaceB = MBMasuGet(0x91);
            break;
        case 1:
            spaceA = MBMasuGet(0x91);
            spaceB = MBMasuGet(0x92);
            break;
        case 2:
            spaceA = MBMasuGet(0x90);
            spaceB = MBMasuGet(0x8F);
            break;
        default:
            spaceA = MBMasuGet(0x8F);
            spaceB = MBMasuGet(0x90);
            break;
    }
    func_8011ABEC_w05(D_8011EF10_w05[dir], dir, 0, func_8011AD34_w05(dir));
    D_801207CC_w05 = gate = MBModelCreate(0x4C, NULL);
    MBModelTempAllocFree(gate);
    HuVecCopy3F(&gate->coords, &spaceA->coords);
    switch (dir) {
        case 0:
            gate->coords.x += 0.8f;
            HuVecCopyXYZ(&gate->rot, -1.0f, 0.0f, 0.0f);
            break;
        case 1:
            HuVecCopyXYZ(&gate->rot, 1.0f, 0.0f, 0.0f);
            break;
        case 2:
            gate->coords.x += 1.5f;
            HuVecCopyXYZ(&gate->rot, -1.0f, 0.0f, 0.0f);
            break;
        default:
            gate->coords.x -= 1.5f;
            HuVecCopyXYZ(&gate->rot, 1.0f, 0.0f, 0.0f);
            break;
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED5E0_shared_board(&gate->coords, &spaceB->coords, &gate->coords, 2.0f));
    omAddPrcObj(func_8011A6E8_w05, 0x4800, 0, 0)->user_data = (void *)dir;
    omAddPrcObj(func_80119BC4_w05, 0x4800, 0, 0)->user_data = (void *)dir;
    omAddPrcObj(func_80119F7C_w05, 0x4800, 0, 0)->user_data = (void *)dir;
    space = MBMasuGet(MBMasuLinkMasuIdGet(player->clink, player->cidx));
    switch (dir) {
        case 0:
            while (gate->coords.x - space->coords.x > -10.0f) {
                HuPrcVSleep();
            }
            spaceC = MBMasuGet(0x7E);
            spaceD = MBMasuGet(0x7F);
            break;
        case 1:
            while (space->coords.x - gate->coords.x > -10.0f) {
                HuPrcVSleep();
            }
            spaceC = MBMasuGet(0x96);
            spaceD = MBMasuGet(0x97);
            break;
        case 2:
            while (gate->coords.x - space->coords.x > -10.0f) {
                HuPrcVSleep();
            }
            spaceC = MBMasuGet(0x84);
            spaceD = MBMasuGet(0x85);
            break;
        default:
            while (space->coords.x - gate->coords.x > -10.0f) {
                HuPrcVSleep();
            }
            spaceC = MBMasuGet(0x70);
            spaceD = MBMasuGet(0x71);
            break;
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED5E0_shared_board(&pos, &spaceC->coords, &pos, 2.0f));
    HuPrcChildWait();
    MBModelKill(gate);
    D_801207B0_w05[0] = -1;
    if (D_801207C0_w05 != 0) {
        MBPlayerMotionSet(-1, 0, 2);
        func_800EE688_shared_board(statue, 10.0f, -1.0f);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&statue->coords, &spaceD->coords, &statue->coords, 20));
        func_800DB884_shared_board(sys->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&player->player_obj->coords, &spaceC->coords, &player->player_obj->coords, 20));
        HuPrcChildWait();
        func_800DB884_shared_board(sys->current_player_index);
        HuAudFXPlay(0x1AE);
        HuAudFXPlay(0x1AF);
        MBPlayerMotionSet(-1, -1, 2);
        MBCameraFocusModeSet(1);
        func_800EE6C0_shared_board(statue);
        func_800E6FBC_shared_board();
        MBStatusShowAll();
        D_800A12D8_main = 0;
        mbItemBtnF = 1;
        switch (dir) {
            case 0:
                player->clink = 8;
                player->cidx = 0;
                player->nlink = 8;
                player->nidx = 1;
                player->blink = 0x10;
                player->bidx = 0x11;
                break;
            case 1:
                player->clink = 2;
                player->cidx = 1;
                player->nlink = 2;
                player->nidx = 2;
                player->blink = 2;
                player->bidx = 0;
                break;
            case 2:
                player->clink = 0xA;
                player->cidx = 0;
                player->nlink = 0xA;
                player->nidx = 1;
                player->blink = 9;
                player->bidx = 0xC;
                break;
            default:
                player->clink = 5;
                player->cidx = 1;
                player->nlink = 5;
                player->nidx = 2;
                player->blink = 5;
                player->bidx = 0;
                break;
        }
        if (player->rev & 0x80) {
            HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_8011A8D8_w05, 0x4800, 0, 0));
            HuPrcChildWait();
        }
    } else {
        WipeCreateOut(0xB, 0x10);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        func_800E6FBC_shared_board();
        HuVecCopy3F(&statue->coords, &spaceD->coords);
        HuVecCopy3F(&pos, &player->player_obj->coords);
        MBCameraFocusVecSet(&pos);
        HuPrcSleep(5);
        MBCameraFocusModeSet(1);
        WipeCreateIn(0xB, 0x10);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        MBPlayerMotionSet(-1, 0, 2);
        func_800DB884_shared_board(sys->current_player_index);
        switch (dir) {
            case 0:
                space = MBMasuGet(0x96);
                break;
            case 1:
                space = MBMasuGet(0x7E);
                break;
            case 2:
                space = MBMasuGet(0x70);
                break;
            default:
                space = MBMasuGet(0x84);
                break;
        }
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&player->player_obj->coords, &space->coords, &player->player_obj->coords, 20));
        HuPrcChildWait();
        MBStatusShowAll();
        D_800A12D8_main = 0;
        mbItemBtnF = 1;
    }
    switch (dir) {
        case 0:
        case 1:
            GwSystem.boardData.halfWordBytes[3] ^= 1;
            break;
        default:
            GwSystem.boardData.halfWordBytes[4] ^= 1;
            break;
    }
end:
    HuPrcSleep(10);
}

void func_8011BB74_w05(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x96:
            if (GwSystem.boardData.halfWordBytes[3] == 0) {
                func_8011AEA4_w05();
            }
            break;
        case 0x7E:
            if (GwSystem.boardData.halfWordBytes[3] != 0) {
                func_8011AEA4_w05();
            }
            break;
        case 0x70:
            if (GwSystem.boardData.halfWordBytes[4] == 0) {
                func_8011AEA4_w05();
            }
            break;
        default:
            if (GwSystem.boardData.halfWordBytes[4] != 0) {
                func_8011AEA4_w05();
            }
            break;
    }
}

void func_8011BC40_w05(s32 dir, SpaceData *target) {
    Vec pos;
    GW_PLAYER *player;
    Object *gate;
    Object *statue;
    SpaceData *spaceA;
    SpaceData *spaceB;
    SpaceData *spaceC;
    SpaceData *space;

    player = MBPlayerGet(-1);
    D_800A12D8_main = 1;
    WipeCreateOut(4, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuVecCopy3F(&D_801207D4_w05, &target->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&D_801207D4_w05);
    HuPrcSleep(5);
    func_800E6FCC_shared_board();
    func_8011ABEC_w05(D_8011EF10_w05[dir], dir, 1, func_8011AD34_w05(dir));
    if (dir == 2 || dir == 3) {
        func_8011ABEC_w05(D_8011EF30_w05[dir - 2], dir, 2, 0);
    }
    switch (dir) {
        case 0:
            spaceA = MBMasuGet(0x92);
            spaceB = MBMasuGet(0x91);
            statue = D_801207C4_w05;
            spaceC = MBMasuGet(0x7F);
            break;
        case 1:
            spaceA = MBMasuGet(0x91);
            spaceB = MBMasuGet(0x92);
            spaceC = MBMasuGet(0x97);
            statue = D_801207C4_w05;
            break;
        case 2:
            spaceA = MBMasuGet(0x90);
            spaceB = MBMasuGet(0x8F);
            spaceC = MBMasuGet(0x85);
            statue = D_801207C8_w05;
            break;
        default:
            spaceA = MBMasuGet(0x8F);
            spaceB = MBMasuGet(0x90);
            statue = D_801207C8_w05;
            spaceC = MBMasuGet(0x71);
            break;
    }
    D_801207CC_w05 = gate = MBModelCreate(0x4C, NULL);
    MBModelTempAllocFree(gate);
    HuVecCopy3F(&gate->coords, &spaceA->coords);
    switch (dir) {
        case 0:
            gate->coords.x += 0.8f;
            HuVecCopyXYZ(&gate->rot, -1.0f, 0.0f, 0.0f);
            break;
        case 1:
            HuVecCopyXYZ(&gate->rot, 1.0f, 0.0f, 0.0f);
            break;
        case 2:
            gate->coords.x += 1.5f;
            HuVecCopyXYZ(&gate->rot, -1.0f, 0.0f, 0.0f);
            break;
        default:
            gate->coords.x -= 2.0f;
            HuVecCopyXYZ(&gate->rot, 1.0f, 0.0f, 0.0f);
            break;
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED5E0_shared_board(&gate->coords, &spaceB->coords, &gate->coords, 2.0f));
    omAddPrcObj(func_8011A6E8_w05, 0x4800, 0, 0)->user_data = (void *)dir;
    omAddPrcObj(func_80119BC4_w05, 0x4800, 0, 0)->user_data = (void *)dir;
    WipeCreateIn(4, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuVecCopy3F(&pos, &target->coords);
    switch (dir) {
        case 0:
            while (gate->coords.x - pos.x > 20.0f) {
                HuPrcVSleep();
            }
            space = MBMasuGet(0x35);
            break;
        case 1:
            while (pos.x - gate->coords.x > 20.0f) {
                HuPrcVSleep();
            }
            space = MBMasuGet(0x1A);
            break;
        case 2:
            while (gate->coords.x - pos.x > 20.0f) {
                HuPrcVSleep();
            }
            space = MBMasuGet(0x40);
            break;
        default:
            while (pos.x - gate->coords.x > 20.0f) {
                HuPrcVSleep();
            }
            space = MBMasuGet(0x10);
            break;
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED5E0_shared_board(&D_801207D4_w05, &space->coords, &D_801207D4_w05, 2.0f));
    HuPrcChildWait();
    MBModelKill(gate);
    func_800EE688_shared_board(statue, 10.0f, -1.0f);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&statue->coords, &spaceC->coords, &statue->coords, 20));
    HuPrcChildWait();
    HuAudFXPlay(0x1AE);
    HuAudFXPlay(0x1AF);
    switch (dir) {
        case 0:
        case 1:
            GwSystem.boardData.halfWordBytes[3] ^= 1;
            break;
        default:
            GwSystem.boardData.halfWordBytes[4] ^= 1;
            break;
    }
    if (MBKettouPlayerBitGet(0) != 0) {
        HuPrcChildLink(HuPrcCurrentGet(),
                       func_800ED5E0_shared_board(&D_801207D4_w05, &player->player_obj->coords, &D_801207D4_w05, 2.0f));
        HuPrcChildWait();
    }
    func_800E6FBC_shared_board();
    D_800A12D8_main = 0;
}

void func_8011C2A8_w05(void) {
    s32 gate;
    s16 space;

    if (GwSystem.boardData.halfWordBytes[3] == 0) {
        gate = 0;
        space = 0x1A;
    } else {
        gate = 1;
        space = 0x35;
    }
    func_8011BC40_w05(gate, MBMasuGet(space));
}

void func_8011C2F8_w05(void) {
    s32 gate;
    s16 space;

    if (GwSystem.boardData.halfWordBytes[4] == 0) {
        gate = 2;
        space = 0x10;
    } else {
        gate = 3;
        space = 0x40;
    }
    func_8011BC40_w05(gate, MBMasuGet(space));
}

void func_8011C348_w05(void) {
    Hu3DCamInit(2);
    CameraScissorSet(1, &D_8011F128_w05);
    func_8010782C_w05();
    MBStart(2);
    omAddPrcObj(func_80106120_w05, 0x1005, 0x1000, 0);
}

s32 func_8011C39C_w05(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    for (i = 0, bestRank = 99, best = MBPlayerTurnGet(); i < 4; i++) {
        if (i != MBPlayerTurnGet()) {
            func_800DA778_shared_board(i);
            if ((MBComTreeExec(D_8011FCC0_w05) == 0) &&
                (BoardPlayerRankCalc(i) < bestRank)) {
                bestRank = BoardPlayerRankCalc(i);
                best = i;
            }
        }
    }
    return best;
}

s32 func_8011C448_w05(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    best = MBPlayerTurnGet();
    if (MBComTreeExec(D_8011FFA8_w05) != 0) {
        for (i = 0, bestRank = 99; i < 4; i++) {
            if (i != MBPlayerTurnGet()) {
                func_800DA778_shared_board(i);
                if ((MBComTreeExec(D_80120344_w05) == 0) &&
                    (BoardPlayerRankCalc(i) < bestRank)) {
                    bestRank = BoardPlayerRankCalc(i);
                    best = i;
                }
            }
        }
    }
    return best;
}

s32 func_8011C50C_w05(void) {
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

s32 func_8011C560_w05(s32 base, s32 perLevel) {
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

s32 func_8011C648_w05(void) {
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
                if (func_8011C50C_w05() != 0) {
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
                if (MBRandCheck100(70) != 0 && func_8011C50C_w05() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (func_8011C50C_w05() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011F5DC_w05) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (func_8011C50C_w05() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011F648_w05) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(D_8011F924_w05) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(D_8011FD50_w05) == 0) {
                    s32 target = func_8011C39C_w05();

                    D_80120894_w05 = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(D_801201D0_w05) == 0) {
                    s32 target = func_8011C448_w05();

                    D_80120890_w05 = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, D_8012084C_w05 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < D_80100FA8_shared_board[it]) {
                                    best = D_80100FA8_shared_board[it];
                                    D_8012084C_w05 = i;
                                }
                            }
                        }
                    }
                }
                if (D_8012084C_w05 == -1) {
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
                for (i = 0, D_80120848_w05 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += D_80100FA8_shared_board[it];
                            }
                        }
                        if (best < count) {
                            D_80120848_w05 = i;
                            best = count;
                        }
                    }
                }
                if (D_80120848_w05 == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (func_8011C560_w05(0x32, 0xA) == 0) {
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
                if (func_8011C560_w05(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(D_8011FB04_w05) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && func_8011C50C_w05() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(D_801203B0_w05) != 0) {
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

s32 func_8011CC50_w05(void) {
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
        temp_s0 = D_8012053C_w05[temp_s3->chr][i];
        var_s2 = func_8010A944_w05(temp_s0);
        if (var_s2 != -1 && D_80100F94_shared_board[temp_s0] + 20 <= GwPlayer[system->current_player_index].coin &&
            MBRandCheck100(D_801205DC_w05[temp_s3->chr][i])) {
            break;
        }
    }
    if (i == 16) {
        var_s2 = -1;
    }

    if (var_s2 != -1) {
        if ((func_8010A944_w05(0xE) != var_s2) &&
        ((func_8010A944_w05(0xB) != var_s2) ||
        ((D_80100F94_shared_board[0xB] + 50) > (GwPlayer[system->current_player_index].coin)) != 0)) {
            if ((func_8010A944_w05(4) == var_s2) &&
            (MBItemFind(system->current_player_index, 4) != -1)) {
                var_s2 = -1;
                sp14 = 0;
            }
        } else {
            return var_s2 + 1;
        }
    }
    if ((MBComTreeExec(D_801205FC_w05[D_8011EB38_w05]) == 0) && GwPlayer[system->current_player_index].coin >= D_80100F94_shared_board[1]) {
        temp_v0 = func_8010A944_w05(1);
        if (temp_v0 != -1) {
            return temp_v0 + 1;
        }
    }
    if (var_s2 == -1) {
        i = MBComTreeExec(D_80120604_w05[D_8011EB38_w05]);
        if (i == 0) {
            do {
                temp_s0_2 = D_8012053C_w05[temp_s3->chr][i];
                //this line below has to be written very specific
                if ((temp_s0_2 == 4 && sp14 == 0) == 0) {
                    var_s2_2 = func_8010A944_w05(temp_s0_2);
                    if ((var_s2_2 != -1) && !(D_80100F94_shared_board[temp_s0_2] > (GwPlayer[system->current_player_index].coin))) {
                        if ((MBRandCheck100(D_801205DC_w05[temp_s3->chr][i]))) {
                            return var_s2_2 + 1;
                        }
                    }
                }
            } while (++i < 16);
        }

        var_s2_2 = func_8010A944_w05(0);
        if (var_s2_2 == -1) {
            D_801204B8_w05 = 1;
            return func_8010A9CC_w05() + 2;
        }
        return var_s2_2 + 1;
    }
    return var_s2 + 1;
}

s32 func_8011CFB4_w05(void) {
    if (D_801204B8_w05 != 0) {
        D_801204B8_w05 = 0;
        return 2;
    }
    return MBComTreeExec(D_8012060C_w05[D_8011EB38_w05]) + 1;
}

// board r4: .data (0x8011D040, 0x3650 bytes): the overlay's initialised data, in address order.
// Inner labels the remaining asm uses are undefined_syms.txt aliases.
s32 func_80108798_w05();
void func_80108924_w05(void);
void func_80108948_w05(void);
void func_801089A8_w05(void);
void func_80108A58_w05(void);
void func_80108A90_w05(void);
void func_80108B18_w05(void);
void func_80108B50_w05(void);
void func_80108B88_w05(void);
void func_80108BC0_w05(void);
void func_80108C70_w05(void);
void func_80108CF8_w05(void);
void func_80108D28_w05(void);
void func_80108D58_w05(void);
void func_80108D88_w05(void);
void func_80108DB8_w05(void);
void func_80108DE8_w05(void);
void func_80108E18_w05(void);
void func_80108E48_w05(void);
void func_80108E6C_w05(void);
void func_80108E90_w05(void);
void func_80108EB4_w05(void);
void func_80108F20_w05(void);
void func_80108F44_w05(void);
void func_80108F68_w05(void);
void func_80108F8C_w05(void);
void func_80108FB0_w05(void);
void func_80108FD4_w05(void);
void func_80108FF8_w05(void);
void func_8010901C_w05(void);
void func_80109078_w05(void);
void func_801090A4_w05(void);
void func_801090C8_w05(void);
void func_801090EC_w05(void);
void func_80109118_w05(void);
void func_8010913C_w05(void);
void func_80109160_w05(void);
void func_80109184_w05(void);
void func_801091A8_w05(void);
void func_801091CC_w05(void);
void func_801091F0_w05(void);
void func_80109214_w05(void);
void func_80109270_w05(void);
void func_80109A5C_w05(void);
void func_80109E08_w05(void);
void func_8010AC0C_w05(void);
void func_8010D428_w05(void);
void func_8010E5FC_w05(void);
void func_8010E618_w05(void);
void func_8011614C_w05(void);
void func_80116A80_w05(void);
void func_8011BB74_w05(void);
s16 D_8011D040_w05[8] = { 0, 1, 2, 3, 6, 7, 4, 5 };
s16 D_8011D050_w05[8] = { 0, 0, 0, 0, 0, 0, 1, 1 };
s16 D_8011D060_w05[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011D070_w05[8] = { 11, 31, 40, 19, 72, 92, 86, 49 };
s16 D_8011D080_w05[8] = { 100, 101, 102, 103, 104, 105, 106, 107 };
s32 D_8011D090_w05[7] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083, 0xA0084 };
s32 D_8011D0AC_w05[7] = { 24066, 24067, 24068, 24069, 24070, 24071, 24072 };
s32 D_8011D0C8_w05 = 0;
s32 D_8011D0CC_w05 = 0;
s16 D_8011D0D0_w05 = -1;
s16 D_8011D0D4_w05[10] = {
    11, 31, 40, 19, 72, 92, 86, 49,
    -1, 0,
};
s16 D_8011D0E8_w05[8][2] = {
    { 1, -5 },
    { 3, -5 },
    { 2, -10 },
    { -5, 0 },
    { 1, -7 },
    { 9, 24 },
    { -7, 24 },
    { -1, -6 },
};
s16 D_8011D108_w05[2][2] = {
    { 2, 0 },
    { 2, 0 },
};
s16 D_8011D110_w05[2][2] = {
    { 1, -2 },
    { 0, -4 },
};
s16 D_8011D118_w05[2][2] = {
    { 1, -4 },
    { 3, -2 },
};
s16 D_8011D120_w05[2][2] = {
    { 0, 0 },
    { 0, -3 },
};
s16 D_8011D128_w05[2][2] = {
    { 115, 116 },
    { 135, 136 },
};
s16 D_8011D130_w05[8] = { 100, 101, 102, 103, 104, 105, 106, 107 };
s16 D_8011D140_w05[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 D_8011D150_w05[2] = { 99, 0 };
s16 D_8011D154_w05[2] = { 120, 122 };
Vec D_8011D158_w05[5] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f },
};
Vec D_8011D194_w05[5] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 2e+01f, 0.0f, -3e+01f },
    { 45.0f, 0.0f, 45.0f },
};
s16 D_8011D1D0_w05[2] = { 117, 137 };
u8 D_8011D1D4_w05[6][2] = {
    { 0, 38 },
    { 0, 39 },
    { 0, 40 },
    { 0, 41 },
    { 0, 42 },
    { 0, 43 },
};
u32 D_8011D1E0_w05[2] = { 1, 0x130163 };
u32 D_8011D1E8_w05[2] = { 1, 0x130168 };
u32 D_8011D1F0_w05[2] = { 1, 0x13016F };
u32 D_8011D1F8_w05[2] = { 1, 0x130176 };
u32 D_8011D200_w05[2] = { 1, 0x130180 };
u32 D_8011D208_w05[2] = { 1, 0x130184 };
u32 *D_8011D210_w05[6] = {
    D_8011D1E0_w05, D_8011D1E8_w05, D_8011D1F0_w05, D_8011D1F8_w05,
    D_8011D200_w05, D_8011D208_w05,
};
s32 D_8011D228_w05[9] = {
    328, 328, 328, 328, 328, 328, -1, -1,
    -1,
};
s32 D_8011D24C_w05[9] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1,
};
s32 D_8011D270_w05[9] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1,
};
s32 D_8011D294_w05[9] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1,
};
s16 D_8011D2B8_w05[2] = { 109, 121 };
s16 D_8011D2BC_w05[2] = { 148, 119 };
DecisionTreeNonLeafNode D_8011D2C0_w05[2] = {
    { 3, { .data = 0x00000008 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } },
};
DecisionTreeNonLeafNode D_8011D2D8_w05[2] = {
    { 3, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C96A33C } },
};
DecisionTreeNonLeafNode D_8011D2F0_w05[6] = {
    { 2, { .data = 0x000000F0 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000003 }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000001 }, { .node_data = D_8011D2C0_w05 } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00300000 }, { .node_data = D_8011D2D8_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C96A33C } },
};
DecisionTreeNonLeafNode D_8011D338_w05[2] = {
    { 3, { .data = 0x00000001 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } },
};
DecisionTreeNonLeafNode D_8011D350_w05[3] = {
    { 4, { .data = 0x00300000 }, { .node_data = D_8011D338_w05 } },
    { 3, { .data = 0x00000004 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } },
};
DecisionTreeNonLeafNode D_8011D374_w05[2] = {
    { 3, { .data = 0x00000001 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } },
};
DecisionTreeNonLeafNode D_8011D38C_w05[6] = {
    { 4, { .data = 0x00000001 }, { .node_data = D_8011D2C0_w05 } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00300000 }, { .node_data = D_8011D2D8_w05 } },
    { 3, { .data = 0x00000008 }, { .data = 0x0C96A33C } },
    { 3, { .data = 0x00000020 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } },
};
DecisionTreeNonLeafNode D_8011D3D4_w05[7] = {
    { 8, { .data = 0x00000001 }, { .node_data = D_8011D2F0_w05 } },
    { 2, { .data = 0x00000001 }, { .node_data = D_8011D350_w05 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011D374_w05 } },
    { 2, { .data = 0x0000000C }, { .node_data = D_8011D38C_w05 } },
    { 3, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000004 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011D428_w05[4] = {
    { 8, { .data = 0x00000001 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0BF6A83C } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A846 } },
};
DecisionTreeNonLeafNode D_8011D458_w05[4] = {
    { 2, { .data = 0x000000F0 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011D488_w05[5] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011D428_w05 } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A83C } },
    { 8, { .data = 0x00000001 }, { .node_data = D_8011D458_w05 } },
    { 3, { .data = 0x00000020 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011D4C4_w05[2] = {
    { 3, { .data = 0x00000001 }, { .data = 0x0C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C96A33C } },
};
DecisionTreeNonLeafNode D_8011D4DC_w05[3] = {
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A83C } },
    { 4, { .data = 0x00300000 }, { .node_data = D_8011D4C4_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C96A33C } },
};
DecisionTreeNonLeafNode D_8011D500_w05[3] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011D4DC_w05 } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode *D_8011D524_w05[3] = { D_8011D3D4_w05, D_8011D488_w05, D_8011D500_w05 };
DecisionTreeNonLeafNode D_8011D530_w05[2] = {
    { 3, { .data = 0x00000002 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011D548_w05[3] = {
    { 2, { .data = 0x00000002 }, { .node_data = D_8011D530_w05 } },
    { 2, { .data = 0x00000001 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D56C_w05[2] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D584_w05[5] = {
    { 3, { .data = 0x00000017 }, { .data = 0x0BF6A33C } },
    { 1, { .data = 0x00000014 }, { .data = 0x0BF6A83C } },
    { 4, { .data = 0x00300001 }, { .data = 0x1BF6A33C } },
    { 3, { .data = 0x00000012 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D5C0_w05[5] = {
    { 3, { .data = 0x00000002 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 1, { .data = 0x00000014 }, { .data = 0x1BF6A83C } },
    { 3, { .data = 0x0000002A }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D5FC_w05[2] = {
    { 3, { .data = 0x00000080 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D614_w05[3] = {
    { 4, { .data = 0x00000001 }, { .node_data = D_8011D5FC_w05 } },
    { 8, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D638_w05[3] = {
    { 4, { .data = 0x00300000 }, { .data = 0x1BF6A33C } },
    { 8, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D65C_w05[8] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011D584_w05 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011D5C0_w05 } },
    { 2, { .data = 0x0000000C }, { .node_data = D_8011D614_w05 } },
    { 2, { .data = 0x000000C0 }, { .node_data = D_8011D638_w05 } },
    { 8, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000020 }, { .data = 0x0BF6A33C } },
    { 2, { .data = 0x00000030 }, { .node_data = D_8011D638_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011D6BC_w05[3] = { D_8011D548_w05, D_8011D56C_w05, D_8011D65C_w05 };
DecisionTreeNonLeafNode D_8011D6C8_w05[2] = {
    { 2, { .data = 0x0000003C }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011D6E0_w05[4] = {
    { 2, { .data = 0x0000003C }, { .data = 0x1BF6A83C } },
    { 4, { .data = 0x00300001 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000008 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
};
DecisionTreeNonLeafNode D_8011D710_w05[2] = {
    { 9, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode D_8011D728_w05[3] = {
    { 2, { .data = 0x00000003 }, { .data = 0x1BF6A83C } },
    { 8, { .data = 0x00000001 }, { .node_data = D_8011D710_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } },
};
DecisionTreeNonLeafNode *D_8011D74C_w05[3] = { D_8011D6C8_w05, D_8011D6E0_w05, D_8011D728_w05 };
DecisionTreeNonLeafNode D_8011D758_w05[2] = {
    { 2, { .data = 0x00000034 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D770_w05[2] = {
    { 2, { .data = 0x00000034 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D788_w05[2] = {
    { 2, { .data = 0x00000034 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode *D_8011D7A0_w05[3] = { D_8011D758_w05, D_8011D770_w05, D_8011D788_w05 };
DecisionTreeNonLeafNode D_8011D7AC_w05[2] = {
    { 2, { .data = 0x000000C3 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D7C4_w05[2] = {
    { 2, { .data = 0x000000C3 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D7DC_w05[3] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode D_8011D800_w05[2] = {
    { 2, { .data = 0x00000080 }, { .node_data = D_8011D7DC_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } },
};
DecisionTreeNonLeafNode *D_8011D818_w05[3] = { D_8011D7AC_w05, D_8011D7C4_w05, D_8011D800_w05 };
DecisionTreeNonLeafNode D_8011D824_w05[2] = {
    { 3, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D83C_w05[4] = {
    { 4, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D86C_w05[4] = {
    { 2, { .data = 0x00000020 }, { .node_data = D_8011D824_w05 } },
    { 2, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x000000C0 }, { .node_data = D_8011D83C_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D89C_w05[3] = {
    { 3, { .data = 0x00000006 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D8C0_w05[2] = {
    { 2, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode *D_8011D8D8_w05[3] = { D_8011D86C_w05, D_8011D89C_w05, D_8011D8C0_w05 };
DecisionTreeNonLeafNode D_8011D8E4_w05[4] = {
    { 4, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D914_w05[3] = {
    { 2, { .data = 0x0000000F }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x000000C0 }, { .node_data = D_8011D8E4_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D938_w05[3] = {
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000030 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D95C_w05[3] = {
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000000 }, { .node_data = D_8011D938_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D980_w05[4] = {
    { 8, { .data = 0x00000001 }, { .node_data = D_8011D914_w05 } },
    { 2, { .data = 0x000000C0 }, { .node_data = D_8011D95C_w05 } },
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D9B0_w05[4] = {
    { 1, { .data = 0x00000014 }, { .data = 0x0BF6A83C } },
    { 3, { .data = 0x00000003 }, { .data = 0x1BF6A33C } },
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011D9E0_w05[3] = {
    { 2, { .data = 0x00000010 }, { .node_data = D_8011D9B0_w05 } },
    { 3, { .data = 0x00000020 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DA04_w05[3] = {
    { 2, { .data = 0x00000010 }, { .data = 0x0BF6A5BC } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode *D_8011DA28_w05[3] = { D_8011D980_w05, D_8011D9E0_w05, D_8011DA04_w05 };
DecisionTreeNonLeafNode D_8011DA34_w05[2] = {
    { 2, { .data = 0x0000003C }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DA4C_w05[3] = {
    { 2, { .data = 0x00000020 }, { .data = 0x1BF6A5BC } },
    { 9, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DA70_w05[2] = {
    { 2, { .data = 0x0000003C }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode *D_8011DA88_w05[3] = { D_8011DA34_w05, D_8011DA4C_w05, D_8011DA70_w05 };
DecisionTreeNonLeafNode D_8011DA94_w05[2] = {
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DAAC_w05[3] = {
    { 2, { .data = 0x00000008 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000034 }, { .node_data = D_8011DA94_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DAD0_w05[3] = {
    { 2, { .data = 0x00000008 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000034 }, { .node_data = D_8011DA94_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DAF4_w05[2] = {
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode *D_8011DB0C_w05[3] = { D_8011DAAC_w05, D_8011DAD0_w05, D_8011DAF4_w05 };
DecisionTreeNonLeafNode D_8011DB18_w05[2] = {
    { 9, { .data = 0x00000008 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DB30_w05[4] = {
    { 2, { .data = 0x00000004 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000030 }, { .node_data = D_8011DB18_w05 } },
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DB60_w05[7] = {
    { 2, { .data = 0x00000004 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000030 }, { .node_data = D_8011DB18_w05 } },
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DBB4_w05[5] = {
    { 2, { .data = 0x0000003C }, { .data = 0x1BF6A5BC } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode *D_8011DBF0_w05[3] = { D_8011DB30_w05, D_8011DB60_w05, D_8011DBB4_w05 };
DecisionTreeNonLeafNode D_8011DBFC_w05[2] = {
    { 2, { .data = 0x000000CF }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } },
};
DecisionTreeNonLeafNode D_8011DC14_w05[4] = {
    { 8, { .data = 0x00000001 }, { .node_data = D_8011DBFC_w05 } },
    { 3, { .data = 0x00000002 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } },
};
DecisionTreeNonLeafNode D_8011DC44_w05[2] = {
    { 8, { .data = 0x00000001 }, { .node_data = D_8011DBFC_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DC5C_w05[2] = {
    { 9, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DC74_w05[5] = {
    { 2, { .data = 0x00000004 }, { .node_data = D_8011DC5C_w05 } },
    { 2, { .data = 0x00000038 }, { .data = 0x1BF6A5BC } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode *D_8011DCB0_w05[3] = { D_8011DC14_w05, D_8011DC44_w05, D_8011DC74_w05 };
DecisionTreeNonLeafNode D_8011DCBC_w05[2] = {
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DCD4_w05[5] = {
    { 2, { .data = 0x00000040 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000040 }, { .data = 0x0BF6A5BC } },
    { 2, { .data = 0x00000003 }, { .node_data = D_8011DCBC_w05 } },
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DD10_w05[7] = {
    { 2, { .data = 0x00000043 }, { .data = 0x1BF6A5BC } },
    { 9, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000002 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 9, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DD64_w05[6] = {
    { 2, { .data = 0x000000C3 }, { .data = 0x1BF6A5BC } },
    { 9, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000002 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode *D_8011DDAC_w05[3] = { D_8011DCD4_w05, D_8011DD10_w05, D_8011DD64_w05 };
DecisionTreeNonLeafNode D_8011DDB8_w05[2] = {
    { 9, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DDD0_w05[2] = {
    { 2, { .data = 0x00000040 }, { .node_data = D_8011DDB8_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DDE8_w05[2] = {
    { 2, { .data = 0x00000003 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DE00_w05[3] = {
    { 8, { .data = 0x00000001 }, { .node_data = D_8011DDE8_w05 } },
    { 3, { .data = 0x00000002 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DE24_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011DE30_w05[3] = { D_8011DDD0_w05, D_8011DE00_w05, D_8011DE24_w05 };
DecisionTreeNonLeafNode D_8011DE3C_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011DE48_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011DE54_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011DE60_w05[3] = { D_8011DE3C_w05, D_8011DE48_w05, D_8011DE54_w05 };
DecisionTreeNonLeafNode D_8011DE6C_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011DE78_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011DE84_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011DE90_w05[3] = { D_8011DE6C_w05, D_8011DE78_w05, D_8011DE84_w05 };
DecisionTreeNonLeafNode D_8011DE9C_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011DEA8_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011DEB4_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode *D_8011DEC0_w05[3] = { D_8011DE9C_w05, D_8011DEA8_w05, D_8011DEB4_w05 };
DecisionTreeNonLeafNode D_8011DECC_w05[2] = {
    { 4, { .data = 0x00400000 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DEE4_w05[2] = {
    { 3, { .data = 0x00000002 }, { .node_data = D_8011DECC_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DEFC_w05[2] = {
    { 4, { .data = 0x00400001 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DF14_w05[3] = {
    { 3, { .data = 0x00000002 }, { .node_data = D_8011DEFC_w05 } },
    { 4, { .data = 0x00400000 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DF38_w05[4] = {
    { 2, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011DEE4_w05 } },
    { 2, { .data = 0x00000030 }, { .node_data = D_8011DF14_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DF68_w05[2] = {
    { 2, { .data = 0x000000C3 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DF80_w05[2] = {
    { 4, { .data = 0x00300001 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DF98_w05[2] = {
    { 3, { .data = 0x00000004 }, { .node_data = D_8011DF80_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DFB0_w05[2] = {
    { 1, { .data = 0x0000001E }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DFC8_w05[2] = {
    { 4, { .data = 0x00300000 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011DFE0_w05[3] = {
    { 3, { .data = 0x00000001 }, { .node_data = D_8011DFB0_w05 } },
    { 3, { .data = 0x00000004 }, { .node_data = D_8011DFC8_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E004_w05[3] = {
    { 2, { .data = 0x00000003 }, { .node_data = D_8011DF98_w05 } },
    { 2, { .data = 0x000000C0 }, { .node_data = D_8011DFE0_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E028_w05[2] = {
    { 2, { .data = 0x0000003C }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E040_w05[2] = {
    { 3, { .data = 0x00000040 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E058_w05[2] = {
    { 3, { .data = 0x00000040 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E070_w05[4] = {
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000000 }, { .node_data = D_8011E040_w05 } },
    { 4, { .data = 0x00000001 }, { .node_data = D_8011E058_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E0A0_w05[2] = {
    { 3, { .data = 0x00000019 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E0B8_w05[2] = {
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E0D0_w05[5] = {
    { 2, { .data = 0x0000000C }, { .node_data = D_8011E070_w05 } },
    { 2, { .data = 0x00000030 }, { .node_data = D_8011E0A0_w05 } },
    { 2, { .data = 0x00000040 }, { .data = 0x0BF6A5BC } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011E0B8_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E10C_w05[2] = {
    { 3, { .data = 0x00000018 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E124_w05[3] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011E10C_w05 } },
    { 2, { .data = 0x00000002 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E148_w05[2] = {
    { 3, { .data = 0x00000008 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E160_w05[2] = {
    { 3, { .data = 0x00000004 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E178_w05[2] = {
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E190_w05[4] = {
    { 6, { .func = func_80108798_w05 }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000000 }, { .node_data = D_8011E178_w05 } },
    { 3, { .data = 0x00000014 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E1C0_w05[5] = {
    { 2, { .data = 0x00000010 }, { .node_data = D_8011E148_w05 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011E160_w05 } },
    { 2, { .data = 0x000000C0 }, { .node_data = D_8011E190_w05 } },
    { 3, { .data = 0x0000000C }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E1FC_w05[2] = {
    { 3, { .data = 0x0000000C }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E214_w05[2] = {
    { 3, { .data = 0x00000010 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E22C_w05[2] = {
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E244_w05[4] = {
    { 6, { .func = func_80108798_w05 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000000 }, { .node_data = D_8011E214_w05 } },
    { 4, { .data = 0x00000001 }, { .node_data = D_8011E22C_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E274_w05[4] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0BF6A5BC } },
    { 2, { .data = 0x0000000B }, { .node_data = D_8011E1FC_w05 } },
    { 2, { .data = 0x000000C0 }, { .node_data = D_8011E244_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } },
};
DecisionTreeNonLeafNode D_8011E2A4_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C97E846 } },
};
DecisionTreeNonLeafNode D_8011E2B0_w05[4] = {
    { 2, { .data = 0x00000043 }, { .data = 0x1C97E846 } },
    { 2, { .data = 0x0000003C }, { .data = 0x0C97E846 } },
    { 9, { .data = 0x00000010 }, { .data = 0x0C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C97E846 } },
};
DecisionTreeNonLeafNode D_8011E2E0_w05[3] = {
    { 3, { .data = 0x00000001 }, { .data = 0x0C97E846 } },
    { 12, { .data = 0x00000014 }, { .data = 0x0C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C97E846 } },
};
DecisionTreeNonLeafNode D_8011E304_w05[2] = {
    { 3, { .data = 0x00000009 }, { .data = 0x1C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C97E846 } },
};
DecisionTreeNonLeafNode D_8011E31C_w05[4] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0C97E846 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011E2E0_w05 } },
    { 2, { .data = 0x000000F0 }, { .node_data = D_8011E304_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } },
};
DecisionTreeNonLeafNode D_8011E34C_w05[3] = {
    { 2, { .data = 0x00000010 }, { .data = 0x0C97E846 } },
    { 3, { .data = 0x00000004 }, { .data = 0x0C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1A119E32 } },
};
DecisionTreeNonLeafNode D_8011E370_w05[2] = {
    { 2, { .data = 0x00000034 }, { .data = 0x1C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C97E846 } },
};
event_list_entry D_8011E388_w05[2] = {
    { 8, 1, func_80108924_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E398_w05[2] = {
    { 1, 1, func_80108948_w05 },
    { 0, 0, NULL },
};
s16 D_8011E3A8_w05[3][3] = {
    { 77, 42, -1 },
    { 66, 42, -1 },
    { 66, 77, -1 },
};
BranchLink D_8011E3BC_w05[3][2] = {
    { { 3, 0, 0 }, { 7, 0, 0 } },
    { { 1, 8, 1 }, { 7, 0, 0 } },
    { { 1, 8, 1 }, { 3, 0, 0 } },
};
event_list_entry D_8011E3E0_w05[2] = {
    { 1, 2, func_801089A8_w05 },
    { 0, 0, NULL },
};
s16 D_8011E3F0_w05[3][3] = {
    { 29, 26, -1 },
    { 27, 26, -1 },
    { 27, 29, -1 },
};
BranchLink D_8011E404_w05[3][2] = {
    { { 2, 0, 0 }, { 4, 8, 1 } },
    { { 1, 0, 0 }, { 4, 8, 1 } },
    { { 1, 0, 0 }, { 2, 0, 0 } },
};
event_list_entry D_8011E428_w05[2] = {
    { 1, 2, func_80108A58_w05 },
    { 0, 0, NULL },
};
s16 D_8011E438_w05[3][3] = {
    { 34, 141, -1 },
    { 2, 141, -1 },
    { 2, 34, -1 },
};
BranchLink D_8011E44C_w05[3][2] = {
    { { 4, 0, 0 }, { 14, 0, 0 } },
    { { 3, 3, 1 }, { 14, 0, 0 } },
    { { 3, 3, 1 }, { 4, 0, 0 } },
};
event_list_entry D_8011E470_w05[2] = {
    { 1, 2, func_80108A90_w05 },
    { 0, 0, NULL },
};
s16 D_8011E480_w05[3][3] = {
    { 38, 17, -1 },
    { 37, 17, -1 },
    { 37, 38, -1 },
};
BranchLink D_8011E494_w05[3][2] = {
    { { 5, 0, 0 }, { 6, 0, 0 } },
    { { 14, 15, 1 }, { 6, 0, 0 } },
    { { 14, 15, 1 }, { 5, 0, 0 } },
};
event_list_entry D_8011E4B8_w05[2] = {
    { 1, 2, func_80108B18_w05 },
    { 0, 0, NULL },
};
s16 D_8011E4C8_w05[3][3] = {
    { 126, 54, -1 },
    { 53, 54, -1 },
    { 53, 126, -1 },
};
BranchLink D_8011E4DC_w05[3][2] = {
    { { 8, 0, 0 }, { 9, 0, 0 } },
    { { 16, 16, 1 }, { 9, 0, 0 } },
    { { 16, 16, 1 }, { 8, 0, 0 } },
};
event_list_entry D_8011E500_w05[2] = {
    { 1, 2, func_80108B50_w05 },
    { 0, 0, NULL },
};
s16 D_8011E510_w05[3][3] = {
    { 132, 67, -1 },
    { 65, 67, -1 },
    { 65, 132, -1 },
};
BranchLink D_8011E524_w05[3][2] = {
    { { 10, 0, 0 }, { 11, 0, 0 } },
    { { 9, 11, 1 }, { 11, 0, 0 } },
    { { 9, 11, 1 }, { 10, 0, 0 } },
};
event_list_entry D_8011E548_w05[2] = {
    { 1, 2, func_80108B88_w05 },
    { 0, 0, NULL },
};
s16 D_8011E558_w05[3][3] = {
    { 73, 97, -1 },
    { 72, 97, -1 },
    { 72, 73, -1 },
};
BranchLink D_8011E56C_w05[3][2] = {
    { { 15, 0, 0 }, { 13, 0, 0 } },
    { { 11, 5, 1 }, { 13, 0, 0 } },
    { { 11, 5, 1 }, { 15, 0, 0 } },
};
event_list_entry D_8011E590_w05[2] = {
    { 1, 2, func_80108BC0_w05 },
    { 0, 0, NULL },
};
s16 D_8011E5A0_w05[3][3] = {
    { 138, 89, -1 },
    { 76, 89, -1 },
    { 76, 138, -1 },
};
BranchLink D_8011E5B4_w05[3][2] = {
    { { 15, 5, 0 }, { 12, 0, 0 } },
    { { 15, 3, 1 }, { 12, 0, 0 } },
    { { 15, 3, 1 }, { 15, 5, 0 } },
};
event_list_entry D_8011E5D8_w05[2] = {
    { 1, 2, func_80108C70_w05 },
    { 0, 0, NULL },
};
s16 D_8011E5E8_w05[3][3] = {
    { 23, 20, -1 },
    { 36, 20, -1 },
    { 36, 23, -1 },
};
BranchLink D_8011E5FC_w05[3][2] = {
    { { 4, 4, 0 }, { 6, 3, 1 } },
    { { 4, 2, 1 }, { 6, 3, 1 } },
    { { 4, 2, 1 }, { 4, 4, 0 } },
};
event_list_entry D_8011E620_w05[2] = {
    { 1, 1, func_80108CF8_w05 },
    { 0, 0, NULL },
};
s16 D_8011E630_w05[3][3] = {
    { 6, 41, -1 },
    { 4, 41, -1 },
    { 4, 6, -1 },
};
BranchLink D_8011E644_w05[3][2] = {
    { { 14, 5, 0 }, { 5, 4, 1 } },
    { { 14, 3, 1 }, { 5, 4, 1 } },
    { { 14, 3, 1 }, { 14, 5, 0 } },
};
event_list_entry D_8011E668_w05[2] = {
    { 1, 1, func_80108D28_w05 },
    { 0, 0, NULL },
};
s16 D_8011E678_w05[3][3] = {
    { 7, 136, -1 },
    { 5, 136, -1 },
    { 5, 7, -1 },
};
BranchLink D_8011E68C_w05[3][2] = {
    { { 14, 6, 0 }, { 13, 3, 1 } },
    { { 14, 4, 1 }, { 13, 3, 1 } },
    { { 14, 4, 1 }, { 14, 6, 0 } },
};
event_list_entry D_8011E6B0_w05[2] = {
    { 1, 1, func_80108D58_w05 },
    { 0, 0, NULL },
};
s16 D_8011E6C0_w05[3][3] = {
    { 82, 87, -1 },
    { 80, 87, -1 },
    { 80, 82, -1 },
};
BranchLink D_8011E6D4_w05[3][2] = {
    { { 16, 5, 0 }, { 8, 4, 1 } },
    { { 16, 3, 1 }, { 8, 4, 1 } },
    { { 16, 3, 1 }, { 16, 5, 0 } },
};
event_list_entry D_8011E6F8_w05[2] = {
    { 1, 1, func_80108D88_w05 },
    { 0, 0, NULL },
};
s16 D_8011E708_w05[3][3] = {
    { 83, 45, -1 },
    { 116, 45, -1 },
    { 116, 83, -1 },
};
BranchLink D_8011E71C_w05[3][2] = {
    { { 16, 6, 1 }, { 16, 8, 0 } },
    { { 7, 3, 1 }, { 16, 8, 0 } },
    { { 7, 3, 1 }, { 16, 6, 1 } },
};
event_list_entry D_8011E740_w05[2] = {
    { 1, 1, func_80108DB8_w05 },
    { 0, 0, NULL },
};
s16 D_8011E750_w05[3][3] = {
    { 60, 93, -1 },
    { 58, 93, -1 },
    { 58, 60, -1 },
};
BranchLink D_8011E764_w05[3][2] = {
    { { 9, 5, 0 }, { 12, 4, 1 } },
    { { 9, 3, 1 }, { 12, 4, 1 } },
    { { 9, 3, 1 }, { 9, 5, 0 } },
};
event_list_entry D_8011E788_w05[2] = {
    { 1, 1, func_80108DE8_w05 },
    { 0, 0, NULL },
};
s16 D_8011E798_w05[3][3] = {
    { 74, 76, -1 },
    { 96, 76, -1 },
    { 96, 74, -1 },
};
BranchLink D_8011E7AC_w05[3][2] = {
    { { 15, 1, 1 }, { 15, 3, 0 } },
    { { 10, 3, 1 }, { 15, 3, 0 } },
    { { 10, 3, 1 }, { 15, 1, 1 } },
};
event_list_entry D_8011E7D0_w05[2] = {
    { 1, 1, func_80108E18_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E7E0_w05[2] = {
    { 1, 1, func_80108E48_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E7F0_w05[2] = {
    { 1, 1, func_80108E6C_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E800_w05[2] = {
    { 1, 1, func_80108E90_w05 },
    { 0, 0, NULL },
};
s16 D_8011E810_w05[3][3] = {
    { 32, 88, -1 },
    { 131, 88, -1 },
    { 131, 32, -1 },
};
BranchLink D_8011E824_w05[3][2] = {
    { { 2, 4, 1 }, { 3, 1, 0 } },
    { { 1, 9, 1 }, { 3, 1, 0 } },
    { { 1, 9, 1 }, { 2, 4, 1 } },
};
event_list_entry D_8011E848_w05[2] = {
    { 1, 1, func_80108EB4_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E858_w05[2] = {
    { 1, 1, func_80108F20_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E868_w05[2] = {
    { 1, 1, func_80108F44_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E878_w05[2] = {
    { 1, 1, func_80108F68_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E888_w05[2] = {
    { 1, 1, func_80108F8C_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E898_w05[2] = {
    { 1, 1, func_80108FB0_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E8A8_w05[2] = {
    { 1, 1, func_80108FD4_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E8B8_w05[2] = {
    { 1, 1, func_80108FF8_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E8C8_w05[2] = {
    { 1, 1, func_8010901C_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E8D8_w05[2] = {
    { 1, 1, func_80109078_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E8E8_w05[2] = {
    { 1, 1, func_801090A4_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E8F8_w05[2] = {
    { 1, 1, func_801090C8_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E908_w05[2] = {
    { 1, 1, func_801090EC_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E918_w05[2] = {
    { 1, 1, func_80109118_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E928_w05[2] = {
    { 1, 1, func_8010913C_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E938_w05[2] = {
    { 1, 1, func_80109160_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E948_w05[2] = {
    { 1, 1, func_80109184_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E958_w05[2] = {
    { 1, 1, func_801091A8_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E968_w05[2] = {
    { 1, 1, func_801091CC_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E978_w05[2] = {
    { 1, 1, func_801091F0_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E988_w05[2] = {
    { 1, 1, func_80109214_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E998_w05[2] = {
    { 1, 2, func_80109270_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011E9A8_w05[2] = {
    { 1, 1, func_80109A5C_w05 },
    { 0, 0, NULL },
};
DecisionTreeNonLeafNode D_8011E9B8_w05[2] = {
    { 4, { .data = 0x00F50014 }, { .data = 0x0B541E1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E1E } },
};
u32 D_8011E9D0_w05[2] = { 1, 0xA009D };
event_list_entry D_8011E9D8_w05[2] = {
    { 1, 1, func_80109E08_w05 },
    { 0, 0, NULL },
};
DecisionTreeNonLeafNode D_8011E9E8_w05[2] = {
    { 0, { .data = 0x01000000 }, { .data = 0x02030404 } },
    { 0, { .data = 0x01000000 }, { .data = 0x02030404 } },
};
s8 D_8011EA00_w05[2][5][7] = {
    { { 0, 1, 4, 5, 10, 14, 19 }, { 0, 1, 4, 5, 10, 12, 19 }, { 0, 1, 4, 5, 10, 19, -1 }, { 0, 1, 4, 8, 10, 12, 19 }, { 0, 1, 8, 10, 12, 14, 19 } },
    { { 1, 2, 3, 6, 13, 11, 19 }, { 1, 2, 3, 6, 9, 13, 19 }, { 1, 2, 3, 7, 13, 19, -1 }, { 1, 3, 6, 7, 9, 13, 19 }, { 1, 3, 6, 7, 9, 11, 19 } },
};
u8 D_8011EA48_w05[2][3][4] = {
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
};
s8 D_8011EA60_w05[2][5][10] = {
    { { 25, 55, 65, 76, 81, 86, 91, 96, 98, 100 }, { 30, 50, 60, 70, 75, 85, 90, 95, 97, 100 }, { 25, 45, 52, 62, 67, 82, 88, 95, 97, 100 }, { 20, 35, 40, 45, 55, 75, 85, 95, 97, 100 }, { 15, 25, 30, 40, 45, 70, 80, 92, 95, 100 } },
    { { 33, 53, 68, 73, 78, 83, 93, 98, 100, 0 }, { 25, 40, 55, 63, 73, 81, 91, 98, 100, 0 }, { 20, 38, 58, 68, 75, 82, 90, 98, 100, 0 }, { 15, 35, 55, 65, 72, 79, 85, 97, 100, 0 }, { 15, 25, 45, 55, 65, 75, 80, 95, 100, 0 } },
};
u8 D_8011EAC4_w05[2][10] = {
    { 0, 1, 4, 5, 8, 10, 12, 14, 15, 16 },
    { 1, 2, 3, 6, 7, 9, 13, 11, 17, 1 },
};
s32 D_8011EAD8_w05[5][2] = {
    { 15109, 15621 },
    { 15110, 15622 },
    { 15111, 15623 },
    { 15112, 15624 },
    { 15113, 15625 },
};
s32 D_8011EB00_w05[2] = { 15104, 15616 };
s32 D_8011EB08_w05[2] = { 15105, 15617 };
s32 D_8011EB10_w05[2] = { 15106, 15618 };
s32 D_8011EB18_w05[2] = { 15107, 15619 };
s32 D_8011EB20_w05[2] = { 15108, 15620 };
u32 D_8011EB28_w05[2] = { 1, 0xA0017 };
u32 D_8011EB30_w05[2] = { 1, 0xA00F0 };
s32 D_8011EB38_w05 = 0;
event_list_entry D_8011EB3C_w05[2] = {
    { 1, 1, func_8010AC0C_w05 },
    { 0, 0, NULL },
};
f32 D_8011EB4C_w05[4][2] = {
    { 76.0f, 52.0f },
    { 244.0f, 52.0f },
    { 76.0f, 192.0f },
    { 244.0f, 192.0f },
};
f32 D_8011EB6C_w05[4][2] = {
    { -1.0f, -1.0f },
    { 1.0f, -1.0f },
    { -1.0f, 1.0f },
    { 1.0f, 1.0f },
};
u8 D_8011EB8C_w05[6][3] = {
    { 1, 5, 15 },
    { 6, 15, 25 },
    { 16, 25, 27 },
    { 26, 35, 30 },
    { 36, 45, 32 },
    { 46, 50, 35 },
};
u8 D_8011EBA0_w05[14][3] = {
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
u8 D_8011EBCC_w05[8] = { 9, 7, 4, 1, 0, 0, 0, 0 };
s32 D_8011EBD4_w05[3] = { 50, 80, 100 };
s32 D_8011EBE0_w05[7] = { 1, 0, 1, 0, 0, 1, 0 };
event_list_entry D_8011EBFC_w05[2] = {
    { 1, 1, func_8010D428_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011EC0C_w05[2] = {
    { 1, 1, func_8010E5FC_w05 },
    { 0, 0, NULL },
};
event_list_entry D_8011EC1C_w05[2] = {
    { 1, 1, func_8010E618_w05 },
    { 0, 0, NULL },
};
event_table_entry D_8011EC2C_w05[15] = {
    { 11, D_8011E9A8_w05 },
    { 31, D_8011E9A8_w05 },
    { 40, D_8011E9A8_w05 },
    { 19, D_8011E9A8_w05 },
    { 72, D_8011E9A8_w05 },
    { 92, D_8011E9A8_w05 },
    { 86, D_8011E9A8_w05 },
    { 49, D_8011E9A8_w05 },
    { 33, D_8011E9D8_w05 },
    { 69, D_8011E9D8_w05 },
    { 147, D_8011EB3C_w05 },
    { 118, D_8011EB3C_w05 },
    { 117, D_8011EC0C_w05 },
    { 137, D_8011EC1C_w05 },
    { -1, NULL },
};
event_table_entry D_8011ECA4_w05[2] = {
    { 79, D_8011EBFC_w05 },
    { -1, NULL },
};
f32 D_8011ECB4_w05[4][2] = {
    { 164.0f, 76.0f },
    { 1.4e+02f, 76.0f },
    { 164.0f, 76.0f },
    { 1.4e+02f, 76.0f },
};
f32 D_8011ECD4_w05[4][2] = {
    { 132.0f, 62.0f },
    { 2.2e+02f, 62.0f },
    { 132.0f, 1.8e+02f },
    { 2.2e+02f, 1.8e+02f },
};
f32 D_8011ECF4_w05[4][2] = {
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
};
f32 D_8011ED14_w05[4][2] = {
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
};
DecisionTreeNonLeafNode D_8011ED34_w05[9] = {
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
s32 D_8011EDA0_w05[5] = { 20, 60, 30, 50, 70 };
DecisionTreeNonLeafNode D_8011EDB4_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C993264 } },
};
f32 D_8011EDC0_w05[6][2] = {
    { -1e+01f, 0.0f },
    { 1e+01f, -5.0f },
    { 1e+01f, 5.0f },
    { -5.0f, -5.0f },
    { 1e+01f, 0.0f },
    { -5.0f, 5.0f },
};
s32 D_8011EDF0_w05 = -1;
u8 D_8011EDF4_w05[4] = { 67, 68, 69, 0 };
u8 D_8011EDF8_w05[4] = { 20, 60, 100, 0 };
u16 D_8011EDFC_w05[7][2] = {
    { 0, 50 },
    { 2, 80 },
    { 4, 90 },
    { 8, 94 },
    { 16, 97 },
    { 32, 99 },
    { 64, 100 },
};
RGB D_8011EE18_w05[2] = {
    { 240, 222, 53 },
    { 247, 26, 66 },
};
event_list_entry D_8011EE20_w05[3] = {
    { 7, 1, func_8011614C_w05 },
    { 7, 1, func_80116A80_w05 },
    { 0, 0, NULL },
};
event_table_entry D_8011EE38_w05[2] = {
    { -5, D_8011EE20_w05 },
    { -1, NULL },
};
s16 D_8011EE48_w05[4][6] = {
    { 9, 0, 9, 1, 16, 17 },
    { 1, 0, 1, 1, 4, 9 },
    { 11, 0, 11, 1, 9, 12 },
    { 6, 0, 6, 1, 14, 16 },
};
u32 D_8011EE78_w05[4] = { 3, 0xA00D5, 0xA00D6, 0xA00D7 };
s16 D_8011EE88_w05[18] = {
    26, 149, 29, 150, 30, 31, 32, 77,
    81, 87, 86, 85, 84, 126, 125, 53,
    -1, 0,
};
s16 D_8011EEAC_w05[18] = {
    53, 125, 126, 84, 85, 86, 87, 81,
    77, 32, 31, 30, 150, 29, 149, 26,
    -1, 0,
};
s16 D_8011EED0_w05[16] = {
    16, 37, 111, 38, 112, 39, 40, 41,
    5, 75, 96, 95, 94, 132, 130, -1,
};
s16 D_8011EEF0_w05[16] = {
    64, 65, 130, 132, 94, 95, 96, 75,
    5, 41, 40, 39, 112, 38, 111, -1,
};
s16 *D_8011EF10_w05[4] = { D_8011EE88_w05, D_8011EEAC_w05, D_8011EED0_w05, D_8011EEF0_w05 };
s16 D_8011EF20_w05[3] = { 65, 64, -1 };
s16 D_8011EF28_w05[4] = { 37, 16, -1, 0 };
s16 *D_8011EF30_w05[2] = { D_8011EF20_w05, D_8011EF28_w05 };
f32 D_8011EF38_w05[3][2] = {
    { 0.0f, 0.0f },
    { -1e+01f, 0.0f },
    { 1e+01f, 0.0f },
};
f32 D_8011EF50_w05[8] = { 0.0f, -1e+01f, 0.0f, 0.0f, -1e+01f, 0.0f, 1e+01f, 0.0f };
f32 D_8011EF70_w05[2] = { 0.0f, 1e+01f };
s16 D_8011EF78_w05[4] = { 125, 84, -1, 0 };
s16 D_8011EF80_w05[4] = { 29, 30, -1, 0 };
s16 D_8011EF88_w05[4] = { 130, 94, -1, 0 };
s16 D_8011EF90_w05[4] = { 38, 39, -1, 0 };
event_list_entry D_8011EF98_w05[2] = {
    { 1, 1, func_8011BB74_w05 },
    { 0, 0, NULL },
};
event_table_entry D_8011EFA8_w05[48] = {
    { 108, D_8011E388_w05 },
    { 0, D_8011E398_w05 },
    { 131, D_8011E3E0_w05 },
    { 149, D_8011E428_w05 },
    { 142, D_8011E470_w05 },
    { 111, D_8011E4B8_w05 },
    { 125, D_8011E500_w05 },
    { 130, D_8011E548_w05 },
    { 123, D_8011E590_w05 },
    { 124, D_8011E5D8_w05 },
    { 21, D_8011E620_w05 },
    { 5, D_8011E668_w05 },
    { 6, D_8011E6B0_w05 },
    { 81, D_8011E6F8_w05 },
    { 43, D_8011E740_w05 },
    { 59, D_8011E788_w05 },
    { 75, D_8011E7D0_w05 },
    { 27, D_8011E7E0_w05 },
    { 29, D_8011E7F0_w05 },
    { 32, D_8011E800_w05 },
    { 77, D_8011E848_w05 },
    { 34, D_8011E858_w05 },
    { 141, D_8011E868_w05 },
    { 38, D_8011E878_w05 },
    { 41, D_8011E888_w05 },
    { 17, D_8011E898_w05 },
    { 20, D_8011E8A8_w05 },
    { 42, D_8011E8B8_w05 },
    { 129, D_8011E8C8_w05 },
    { 126, D_8011E8D8_w05 },
    { 87, D_8011E8E8_w05 },
    { 54, D_8011E8F8_w05 },
    { 132, D_8011E908_w05 },
    { 96, D_8011E918_w05 },
    { 67, D_8011E928_w05 },
    { 73, D_8011E938_w05 },
    { 139, D_8011E948_w05 },
    { 89, D_8011E958_w05 },
    { 93, D_8011E968_w05 },
    { 97, D_8011E978_w05 },
    { 3, D_8011E988_w05 },
    { 150, D_8011EF98_w05 },
    { 112, D_8011EF98_w05 },
    { 115, D_8011E998_w05 },
    { 135, D_8011E998_w05 },
    { 116, D_8011E998_w05 },
    { 136, D_8011E998_w05 },
    { -1, NULL },
};
RectF D_8011F128_w05 = { 0.0f, 0.0f, 3.2e+02f, 2.4e+02f };
DecisionTreeNonLeafNode D_8011F138_w05[8] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00010508 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020004 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000E080F }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060003 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F198_w05[2] = {
    { 4, { .data = 0x00300001 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F1B0_w05[4] = {
    { 4, { .data = 0x00300000 }, { .data = 0x00000000 } },
    { 6, { .func = func_80108798_w05 }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00000000 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F1E0_w05[14] = {
    { 12, { .data = 0x0000000F }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100101 }, { .node_data = D_8011F198_w05 } },
    { 10, { .data = 0x000F0003 }, { .node_data = D_8011F1B0_w05 } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00010508 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020304 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000E070F }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060003 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00010304 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0010030C }, { .node_data = D_8011F198_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F288_w05[3] = {
    { 6, { .func = func_80108798_w05 }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00000001 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F2AC_w05[13] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00030003 }, { .node_data = D_8011F288_w05 } },
    { 10, { .data = 0x000E030B }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00050304 }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00400000 }, { .data = 0x00000000 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090007 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0103 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0305 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0004 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F348_w05[5] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00030003 }, { .node_data = D_8011F288_w05 } },
    { 10, { .data = 0x000E030C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00050004 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F384_w05[6] = {
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100D10 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0009000B }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0004 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0103 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F3CC_w05[9] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x0009000B }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0103 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0205 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F438_w05[3] = {
    { 6, { .func = func_80108798_w05 }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00000000 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F45C_w05[15] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100101 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0103 }, { .node_data = D_8011F438_w05 } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x0010030D }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00300001 }, { .data = 0x00000000 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00010508 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020204 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000E060F }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070000 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F510_w05[17] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100101 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0003 }, { .node_data = D_8011F438_w05 } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100306 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00100C10 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080104 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0009070B }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0103 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0205 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00300001 }, { .data = 0x00000000 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00020000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040108 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060203 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F5DC_w05[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011F138_w05 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011F1E0_w05 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011F2AC_w05 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011F348_w05 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011F384_w05 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011F3CC_w05 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011F45C_w05 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011F510_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F648_w05[1] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A119E32 } },
};
DecisionTreeNonLeafNode D_8011F654_w05[6] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00010002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040708 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011F69C_w05[9] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040608 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00020002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00100D10 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011F708_w05[10] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000E0D0F }, { .data = 0x0000028A } },
    { 10, { .data = 0x00050002 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00050002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0009080B }, { .data = 0x0000028A } },
    { 11, { .data = 0x0009080B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011F780_w05[6] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000E0D0F }, { .data = 0x0000028A } },
    { 10, { .data = 0x00060001 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00060001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011F7C8_w05[7] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000B0204 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000B0204 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000B0001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011F81C_w05[6] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000F0203 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000C0002 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000F0203 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011F864_w05[12] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00100E10 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00080102 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00100E10 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080102 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020000 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040708 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011F8F4_w05[4] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0010070B }, { .data = 0x0000028A } },
    { 11, { .data = 0x0010070B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } },
};
DecisionTreeNonLeafNode D_8011F924_w05[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011F654_w05 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011F69C_w05 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011F708_w05 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011F780_w05 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011F7C8_w05 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011F81C_w05 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011F864_w05 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011F8F4_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011F990_w05[3] = {
    { 10, { .data = 0x00010002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040708 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011F9B4_w05[5] = {
    { 10, { .data = 0x00020002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040608 }, { .data = 0x0000028A } },
    { 4, { .data = 0x00300000 }, { .data = 0x0BF6A83C } },
    { 10, { .data = 0x00100D10 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011F9F0_w05[5] = {
    { 10, { .data = 0x000E0D0F }, { .data = 0x0000028A } },
    { 10, { .data = 0x00050002 }, { .data = 0x0000028A } },
    { 4, { .data = 0x00400000 }, { .data = 0x0BF6A83C } },
    { 10, { .data = 0x0009080B }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011FA2C_w05[3] = {
    { 10, { .data = 0x000E0D0F }, { .data = 0x0000028A } },
    { 10, { .data = 0x00060001 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011FA50_w05[4] = {
    { 10, { .data = 0x000B0204 }, { .data = 0x0000028A } },
    { 12, { .data = 0x00000019 }, { .data = 0x0BF6A83C } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011FA80_w05[3] = {
    { 10, { .data = 0x000F0203 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000C0002 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011FAA4_w05[6] = {
    { 10, { .data = 0x00100E10 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00080102 }, { .data = 0x0000028A } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020000 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040708 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011FAEC_w05[2] = {
    { 10, { .data = 0x0010070B }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } },
};
DecisionTreeNonLeafNode D_8011FB04_w05[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011F990_w05 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011F9B4_w05 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011F9F0_w05 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011FA2C_w05 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011FA50_w05 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011FA80_w05 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011FAA4_w05 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011FAEC_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FB70_w05[3] = {
    { 11, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FB94_w05[4] = {
    { 11, { .data = 0x00020002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FBC4_w05[5] = {
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00050002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x0009080B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FC00_w05[3] = {
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00060001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FC24_w05[2] = {
    { 11, { .data = 0x000B0204 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FC3C_w05[3] = {
    { 11, { .data = 0x000F0203 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FC60_w05[6] = {
    { 11, { .data = 0x00100E10 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080102 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FCA8_w05[2] = {
    { 11, { .data = 0x0010070B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FCC0_w05[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011FB70_w05 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011FB94_w05 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011FBC4_w05 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011FC00_w05 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011FC24_w05 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011FC3C_w05 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011FC60_w05 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011FCA8_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FD2C_w05[3] = {
    { 10, { .data = 0x00010204 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FD50_w05[3] = {
    { 0, { .data = 0x00000000 }, { .node_data = D_8011FCC0_w05 } },
    { 0, { .data = 0x00000000 }, { .node_data = D_8011FD2C_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FD74_w05[5] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00010405 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00010608 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FDB0_w05[9] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020404 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00030003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00070000 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028A1E } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00080103 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FE1C_w05[10] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000E0407 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050404 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028A1E } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000A0102 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x0000001E }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000B0303 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FE94_w05[4] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00040307 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060303 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FEC4_w05[2] = {
    { 10, { .data = 0x000E0608 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FEDC_w05[5] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000F0003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0B54233C } },
    { 8, { .data = 0x00000001 }, { .node_data = D_8011FEC4_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FF18_w05[4] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000C0404 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090508 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FF48_w05[3] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00100507 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FF6C_w05[5] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00080101 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8011FFA8_w05[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_8011FD74_w05 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_8011FDB0_w05 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_8011FE1C_w05 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_8011FE94_w05 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_8011FEDC_w05 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_8011FF18_w05 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_8011FF48_w05 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8011FF6C_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_80120014_w05[3] = {
    { 11, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_80120038_w05[4] = {
    { 11, { .data = 0x00020002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_80120068_w05[5] = {
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00050002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x0009080B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_801200A4_w05[3] = {
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00060001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_801200C8_w05[2] = {
    { 11, { .data = 0x000B0204 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_801200E0_w05[3] = {
    { 11, { .data = 0x000F0203 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_80120104_w05[6] = {
    { 11, { .data = 0x00100E10 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080102 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_8012014C_w05[2] = {
    { 11, { .data = 0x0010070B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } },
};
DecisionTreeNonLeafNode D_80120164_w05[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_80120014_w05 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_80120038_w05 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_80120068_w05 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_801200A4_w05 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_801200C8_w05 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_801200E0_w05 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_80120104_w05 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8012014C_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_801201D0_w05[3] = {
    { 0, { .data = 0x00000000 }, { .node_data = D_8011FFA8_w05 } },
    { 0, { .data = 0x00000000 }, { .node_data = D_80120164_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_801201F4_w05[3] = {
    { 15, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_80120218_w05[4] = {
    { 15, { .data = 0x00020002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028F1E } },
    { 15, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_80120248_w05[5] = {
    { 15, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00050002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028F1E } },
    { 15, { .data = 0x0009080B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_80120284_w05[3] = {
    { 15, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00060001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_801202A8_w05[2] = {
    { 15, { .data = 0x000B0204 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_801202C0_w05[3] = {
    { 15, { .data = 0x000F0203 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x000C0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_801202E4_w05[6] = {
    { 15, { .data = 0x00100E10 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00080102 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 15, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_8012032C_w05[2] = {
    { 15, { .data = 0x0010070B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } },
};
DecisionTreeNonLeafNode D_80120344_w05[9] = {
    { 2, { .data = 0x00000001 }, { .node_data = D_801201F4_w05 } },
    { 2, { .data = 0x00000002 }, { .node_data = D_80120218_w05 } },
    { 2, { .data = 0x00000004 }, { .node_data = D_80120248_w05 } },
    { 2, { .data = 0x00000008 }, { .node_data = D_80120284_w05 } },
    { 2, { .data = 0x00000010 }, { .node_data = D_801202A8_w05 } },
    { 2, { .data = 0x00000020 }, { .node_data = D_801202C0_w05 } },
    { 2, { .data = 0x00000040 }, { .node_data = D_801202E4_w05 } },
    { 2, { .data = 0x00000080 }, { .node_data = D_8012032C_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_801203B0_w05[2] = {
    { 0, { .data = 0x00000000 }, { .node_data = D_80120164_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_801203C8_w05[2] = {
    { 4, { .data = 0x00300000 }, { .data = 0x00028A1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_801203E0_w05[3] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x000000F0 }, { .node_data = D_801203C8_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_80120404_w05[2] = {
    { 4, { .data = 0x00400001 }, { .data = 0x00028A1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_8012041C_w05[3] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x0000000F }, { .node_data = D_80120404_w05 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_80120440_w05[2] = {
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_80120458_w05[2] = {
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } },
};
DecisionTreeNonLeafNode D_80120470_w05[3] = {
    { 2, { .data = 0x0000003C }, { .data = 0x0B54233C } },
    { 1, { .data = 0x00000019 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000F32 } },
};
DecisionTreeNonLeafNode D_80120494_w05[3] = {
    { 2, { .data = 0x000000CB }, { .data = 0x0B54233C } },
    { 1, { .data = 0x0000001E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000F32 } },
};
s32 D_801204B8_w05 = 0;
u8 D_801204BC_w05[16] = {
    14, 10, 0, 3, 2, 4, 19, 11,
    5, 6, 12, 13, 9, 7, 8, 1,
};
u8 D_801204CC_w05[16] = {
    14, 1, 11, 10, 19, 12, 0, 6,
    9, 3, 13, 4, 8, 7, 2, 5,
};
u8 D_801204DC_w05[16] = {
    14, 11, 6, 9, 12, 7, 3, 13,
    2, 4, 10, 19, 0, 8, 5, 1,
};
u8 D_801204EC_w05[16] = {
    14, 5, 9, 10, 11, 7, 19, 12,
    0, 6, 3, 13, 4, 8, 2, 1,
};
u8 D_801204FC_w05[16] = {
    14, 8, 13, 11, 10, 19, 6, 7,
    12, 0, 9, 3, 4, 2, 5, 1,
};
u8 D_8012050C_w05[16] = {
    14, 3, 11, 10, 19, 12, 0, 6,
    9, 13, 4, 8, 7, 2, 5, 1,
};
u8 D_8012051C_w05[16] = {
    14, 2, 9, 3, 6, 7, 8, 5,
    4, 19, 11, 13, 10, 12, 0, 1,
};
u8 D_8012052C_w05[16] = {
    14, 4, 19, 9, 11, 10, 3, 12,
    7, 0, 1, 6, 13, 8, 2, 5,
};
u8 *D_8012053C_w05[8] = {
    D_801204BC_w05, D_801204CC_w05, D_801204DC_w05, D_801204EC_w05,
    D_801204FC_w05, D_8012050C_w05, D_8012051C_w05, D_8012052C_w05,
};
s8 D_8012055C_w05[16] = {
    90, 70, 60, 30, 20, 20, 20, 20,
    10, 10, 10, 10, 10, 10, 10, 10,
};
s8 D_8012056C_w05[16] = {
    80, 50, 20, 20, 20, 10, 20, 10,
    10, 10, 20, 10, 10, 10, 10, 0,
};
s8 D_8012057C_w05[16] = {
    80, 30, 50, 30, 30, 20, 20, 20,
    20, 20, 30, 20, 30, 10, 10, 10,
};
s8 D_8012058C_w05[16] = {
    90, 50, 20, 30, 20, 10, 20, 10,
    30, 10, 10, 10, 10, 10, 10, 10,
};
s8 D_8012059C_w05[16] = {
    90, 50, 30, 30, 30, 20, 20, 20,
    10, 30, 10, 10, 10, 10, 10, 10,
};
s8 D_801205AC_w05[16] = {
    90, 50, 30, 60, 20, 20, 30, 20,
    10, 10, 10, 10, 10, 10, 10, 10,
};
s8 D_801205BC_w05[16] = {
    70, 40, 40, 40, 30, 20, 30, 30,
    20, 40, 40, 30, 40, 10, 40, 10,
};
s8 D_801205CC_w05[16] = {
    80, 50, 60, 20, 20, 30, 20, 30,
    10, 30, 20, 10, 10, 10, 10, 10,
};
s8 *D_801205DC_w05[8] = {
    D_8012055C_w05, D_8012056C_w05, D_8012057C_w05, D_8012058C_w05,
    D_8012059C_w05, D_801205AC_w05, D_801205BC_w05, D_801205CC_w05,
};
DecisionTreeNonLeafNode *D_801205FC_w05[2] = { D_801203E0_w05, D_8012041C_w05 };
DecisionTreeNonLeafNode *D_80120604_w05[2] = { D_80120440_w05, D_80120458_w05 };
DecisionTreeNonLeafNode *D_8012060C_w05[5] = {
    D_80120470_w05, D_80120494_w05, NULL, NULL,
    NULL,
};
u8 D_80120620_w05[4] = { 1, 2, 4, 8 };
char D_80120624_w05[4] = "%d";
f64 D_80120628_w05 = 1.5;
f32 D_80120630_w05[24] = {
    1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.0f, 2.0f,
    1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f, 2.0f, 1.0f, 1.0f, -1.0f, 1.0f,
};
