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
