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
