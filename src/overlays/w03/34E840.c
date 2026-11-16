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

// board p1: declarations for func_801059D0_w03..func_8010B55C_w03 (twins of w02/w06)
#include "WaluigisIsland.h" /* BranchLink */
#include "game/board.h"
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

typedef struct {
    u8 unk[4];
} g1Unk4Bytes;
typedef struct {
    u8 unk[4];
} g2Unk4Bytes;
typedef BranchLink g1BranchLink;
typedef s16 SpaceTriple[3];
typedef BranchLink BranchPair[2];
extern s16 D_8011CB20_w03[]; /* D_8011C288_w06 */
extern s16 D_8011CC40_w03[]; /* D_8011C288_w06 */
extern s16 D_8011CCD0_w03[]; /* D_8011C3F0_w06 */
extern s16 D_8011CD18_w03[]; /* D_8011C3F0_w06 */
extern s16 D_8011CD60_w03[]; /* D_8011C3F0_w06 */
extern s16 D_8011CDA8_w03[]; /* D_8011C3F0_w06 */
extern u8 D_8011E910_w03[]; /* D_8011EA70_w02 */
void func_80106D84_w03(void);
void func_80106E54_w03(void);
s32 func_80106EB4_w03(u8 *arg0);
s32 func_80107148_w03(void);
s32 func_80107628_w03(u8 *arg0, s32 arg1, s32 arg2);
void func_80108AB8_w03(void);
s32 func_801098C8_w03(s32 arg0);
s32 func_80109F44_w03(s32 arg0, s32 arg1);
void func_8010A930_w03(void);
void func_80113080_w03(void);
void func_8011655C_w03(SpaceTriple *masu, BranchPair *links, DecisionTreeNonLeafNode **trees);
s32 func_8011BD24_w03(void);
s32 func_8011C088_w03(void);

extern s32 D_8011C160_w03; /* D_8011C6E8_w02 */
extern s16 D_8011C1A0_w03[][2]; /* D_8011C724_w02 */
extern s16 D_8011C1A8_w03[][2]; /* D_8011C72C_w02 */
extern s16 D_8011C1B0_w03[][2]; /* D_8011C734_w02 */
extern s16 D_8011C1B8_w03[][2]; /* D_8011C73C_w02 */
extern s16 D_8011C1C0_w03[][2]; /* D_8011C744_w02 */
extern s16 D_8011C1E8_w03[]; /* D_8011C76C_w02 */
extern s16 D_8011C1EC_w03[]; /* D_8011C770_w02 */
extern Vec D_8011C1F0_w03[]; /* D_8011C774_w02 */
extern Vec D_8011C22C_w03[]; /* D_8011C7B0_w02 */
extern s16 D_8011C268_w03[]; /* D_8011C7EC_w02 */
extern s16 D_8011C26C_w03[]; /* D_8011C7F0_w02 */
extern u32 *D_8011C2A8_w03[]; /* D_8011C82C_w02 */
extern s32 D_8011C2C0_w03[]; /* D_8011C844_w02 */
extern s32 D_8011C2E4_w03[]; /* D_8011C868_w02 */
extern s32 D_8011C308_w03[]; /* D_8011C88C_w02 */
extern s32 D_8011C32C_w03[]; /* D_8011C8B0_w02 */
extern s16 D_8011C350_w03[]; /* D_8011C8D4_w02 */
extern s16 D_8011C354_w03[]; /* D_8011C8D8_w02 */
extern DecisionTreeNonLeafNode *D_8011C528_w03[]; /* D_8011C994_w02 */
extern DecisionTreeNonLeafNode *D_8011C5F4_w03[]; /* D_8011C994_w02 */
extern DecisionTreeNonLeafNode *D_8011C6D8_w03[]; /* D_8011C994_w02 */
extern DecisionTreeNonLeafNode *D_8011C804_w03[]; /* D_8011C994_w02 */
extern s16 D_8011CB68_w03[][3]; /* D_8011D070_w02 */
extern g1BranchLink D_8011CB7C_w03[][2]; /* D_8011D084_w02 */
extern s16 D_8011CBB0_w03[][3]; /* D_8011D070_w02 */
extern g1BranchLink D_8011CBC4_w03[][2]; /* D_8011D084_w02 */
extern s16 D_8011CBF8_w03[][3]; /* D_8011D070_w02 */
extern g1BranchLink D_8011CC0C_w03[][2]; /* D_8011D084_w02 */
extern s16 D_8011CC88_w03[][3]; /* D_8011D070_w02 */
extern g1BranchLink D_8011CC9C_w03[][2]; /* D_8011D084_w02 */
extern DecisionTreeNonLeafNode D_8011CF50_w03[]; /* D_8011D414_w02 */
extern u32 D_8011CF68_w03[]; /* D_8011D42C_w02 */
extern s8 D_8011CF98_w03[][5][7]; /* D_8011D45C_w02 */
extern char D_8011E98C_w03[]; /* D_8011EA74_w02 */
extern Process *D_8011EAE8_w03[]; /* D_8011EBF8_w02 */
extern Unk3 *D_8011EB10_w03; /* D_8011EC20_w02 */
extern Unk3 *D_8011EB14_w03; /* D_8011EC24_w02 */
extern Unk3 *D_8011EB18_w03; /* D_8011EC28_w02 */
extern Unk3 *D_8011EB1C_w03; /* D_8011EC2C_w02 */
extern Unk3 *D_8011EB20_w03; /* D_8011EC30_w02 */
extern s32 D_8011EB24_w03; /* D_8011EC34_w02 */
extern s32 D_8011EB28_w03; /* D_8011EC38_w02 */
extern Object *D_8011EB54_w03; /* D_8011EC3C_w02 */
extern Object *D_8011EB58_w03[]; /* D_8011EC40_w02 */
extern Object *D_8011EB5C_w03; /* D_8011EC44_w02 */
extern Object *D_8011EB60_w03[]; /* D_8011EC48_w02 */
extern Object *D_8011EB88_w03; /* D_8011EC70_w02 */
extern Object *D_8011EB8C_w03[]; /* D_8011EC74_w02 */
extern s32 D_8011EB94_w03; /* D_8011EC90_w02 */
extern s32 D_8011EB98_w03; /* D_8011EC94_w02 */
extern u8 *D_8011EB9C_w03; /* D_8011EC98_w02 */
extern DecisionTreeNonLeafNode *D_8011C4C8_w03[]; /* D_8011BBA0_w06 */
extern DecisionTreeNonLeafNode *D_8011C774_w03[]; /* D_8011BBA0_w06 */
extern DecisionTreeNonLeafNode *D_8011C864_w03[]; /* D_8011BD98_w06 */
extern DecisionTreeNonLeafNode *D_8011C8D0_w03[]; /* D_8011BD98_w06 */
extern DecisionTreeNonLeafNode *D_8011C924_w03[]; /* D_8011BD98_w06 */
extern s32 D_8011CB34_w03[]; /* D_8011C29C_w06 */
extern s32 D_8011CC54_w03[]; /* D_8011C29C_w06 */
extern s32 D_8011CCE4_w03[]; /* D_8011C404_w06 */
extern s32 D_8011CD2C_w03[]; /* D_8011C404_w06 */
extern s32 D_8011CD74_w03[]; /* D_8011C404_w06 */
extern s32 D_8011CDBC_w03[]; /* D_8011C404_w06 */
extern s16 D_8011C110_w03[]; /* star-space order */
extern s16 D_8011C120_w03[]; /* order constraints */
void func_801059F8_w03(void);
extern s16 D_8011C130_w03[]; /* star board flags */
extern s16 D_8011C140_w03[]; /* star spaces */
void func_8010DF54_w03(void);
void func_8010F3D4_w03(void);
void func_8010F79C_w03(void);
void func_8010F808_w03(void);
void func_80117D38_w03(void);
void func_80110A14_w03(void);
void func_80110CA0_w03(void);
void func_8010FCFC_w03(void);
void func_8011026C_w03(void);
void func_801105B8_w03(void);
void func_80117034_w03(void);
void func_801178B4_w03(void);
void func_801110F0_w03(void);
void func_801113B0_w03(void);
void func_80111750_w03(void);
void func_8011214C_w03(void);
void func_80112CA4_w03(void);
void func_801139BC_w03(void);
void func_80114C58_w03(void);
void func_80115C58_w03(void);
void func_80116E84_w03(void);
void func_8011777C_w03(void);
void func_80105B44_w03(void);
void func_80105C50_w03(void);
void func_80107F30_w03(void);
void func_80116B78_w03(void);
void func_8011908C_w03(void);
s32 func_8011B71C_w03(void);
extern s16 D_8011C164_w03[]; /* blocked-space extension table */
extern s16 D_8011C16C_w03[]; /* blocked spaces */
void func_80108118_w03(void);
void func_801083DC_w03(void);
void func_801085B0_w03(void);
void func_80108820_w03(void);
void func_801088A0_w03(void);
extern s16 D_8011C180_w03[][2]; /* star guide offsets (asm also labels +2 as D_8011C182_w03) */
extern s16 D_8011C1C8_w03[]; /* star guide spaces */
extern Object *D_8011EAC0_w03;
void func_80107D54_w03(s16 arg0);
extern s16 D_8011C1D8_w03[]; /* star guide board flags */
void func_80107ECC_w03(void);
extern s16 D_8011C358_w03[]; /* board flag per star space */
extern s16 D_8011C368_w03[8];
extern s16 D_8011C378_w03[8];
extern s16 D_8011C388_w03[8];
extern s16 D_8011C398_w03[8];
extern s16 D_8011C3A8_w03[8];
extern s16 D_8011C3B8_w03[8];
extern s16 D_8011C3C8_w03[8];
extern DecisionTreeNonLeafNode *D_8011CABC_w03[];
extern s16 D_8011CAD8_w03[];
extern s32 D_8011CAEC_w03[];
extern s16 D_8011CDF0_w03[];
extern s16 D_8011CDF8_w03[];
extern s16 D_8011CE00_w03[];
extern s16 D_8011CE08_w03[];
// board p1: end of declarations

s16 func_801059D0_w03(void) {
    return D_8011C150_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

#ifdef NON_MATCHING
// board p1: li s0,7 scheduled into the MBRand delay slot (retail: before the lui)
void func_801059F8_w03(void) {
    s32 var;
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < D_8011C120_w03[idx2]) {
                continue;
            }
            if (idx2 < D_8011C120_w03[idx1]) {
                continue;
            }
            {
                s32 temp = D_8011C110_w03[idx1];
                D_8011C110_w03[idx1] = D_8011C110_w03[idx2];
                D_8011C110_w03[idx2] = temp;
                temp = D_8011C120_w03[idx1];
                D_8011C120_w03[idx1] = D_8011C120_w03[idx2];
                D_8011C120_w03[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = D_8011C110_w03[i];
    }

    var = 7;
    GwSystem.boardData.halfWordBytes[0] = loc->star_spawn_indices[MBRand(6.0f) + 1];
    if (GwSystem.boardData.halfWordBytes[0] != var) {
        GWBoardFlagClear(0x12);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801059F8_w03);
#endif

void func_80105B44_w03(void) {
    s32 temp_s0;
    s32 temp_v1;
    GW_SYSTEM *system = &GwSystem;

    if (++system->current_star_spawn >= 8) {
        temp_s0 = system->star_spawn_indices[7];
        system->current_star_spawn = 0;
        GWBoardFlagSet(4);
        func_801059F8_w03();
        if (temp_s0 == system->star_spawn_indices[0]) {
            temp_s0 = system->star_spawn_indices[0];
            system->star_spawn_indices[0] = system->star_spawn_indices[7];
            system->star_spawn_indices[7] = temp_s0;
        }
    }
    if (system->current_star_spawn >= 7) {
        GwSystem.boardData.halfWordBytes[0] = system->star_spawn_indices[MBRand(6.0f)];
    } else {
        GwSystem.boardData.halfWordBytes[0] = system->star_spawn_indices[MBRand(7 - system->current_star_spawn) + system->current_star_spawn + 1];
    }
    GWBoardFlagClear(0x12);
}

void func_80105C50_w03(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(D_8011C130_w03[i]);
    }
    MBMasuTypeSet(D_8011C140_w03[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(D_8011C130_w03[loc->star_spawn_indices[loc->current_star_spawn]]);
    if (GwSystem.boardData.halfWordBytes[0] != -1) {
        MBMasuTypeSet(D_8011C140_w03[GwSystem.boardData.halfWordBytes[0]], 0xE);
    }
}

s32 func_80105D20_w03(s16 arg0) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        if (arg0 == D_8011C140_w03[i]) {
            if (i == loc->star_spawn_indices[loc->current_star_spawn]) {
                loc->unk_0E = D_8011C130_w03[i];
                return 1;
            }
            if (i == GwSystem.boardData.halfWordBytes[0]) {
                return 2;
            }
            break;
        }
    }
    return 0;
}

void func_80105DB0_w03(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    D_8011EB0C_w03 = MBModelCreate(0x3A, NULL);
    model = D_8011EB0C_w03;
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
    D_8011EB08_w03 = NULL;
    omDelPrcObj(NULL);
}

void func_801061A0_w03(UnkMBGuideData *arg) {
    omObjData *s0 = *(omObjData **)arg;

    s0->scale.y = 4.0f;
    s0->scale.z = -0.6f;
    HuPrcSleep(3);
    while (s0->scale.z != 0.0f) {
        HuPrcVSleep();
    }
}

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


void func_801066CC_w03(void) {
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
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x8E) {
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
    if (D_8011C160_w03 != 0) {
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
    if (D_8011C160_w03 != 0) {
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

void func_80106C2C_w03(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801066CC_w03, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

void func_80106CA0_w03(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80106D28_w03(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void func_80106D84_w03(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_8011EB10_w03 = func_800E210C_shared_board(0, 0x92, 1);
    D_8011EB14_w03 = func_800E210C_shared_board(1, 0xA0, 1);
    D_8011EB20_w03 = func_800E210C_shared_board(0xD, 0xAE, 1);
    D_8011EB18_w03 = func_800E210C_shared_board(3, 0xBC, 1);
    D_8011EB1C_w03 = func_800E210C_shared_board(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80106E54_w03(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011EB10_w03);
    MBHelpWinKill(D_8011EB14_w03);
    MBHelpWinKill(D_8011EB20_w03);
    MBHelpWinKill(D_8011EB18_w03);
    MBHelpWinKill(D_8011EB1C_w03);
}

s32 func_80106EB4_w03(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = func_8011BD24_w03();
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

s32 func_80107148_w03(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // dead store; matches func_800FA104_shared_board
                var_s2 = func_8011C088_w03();
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

void func_80107360_w03(void) {
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
                D_8011EB24_w03 = 1;
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
        D_8011EB24_w03 = 0;
    } else {
        D_8011EB24_w03 = 2;
    }
}

void func_80107490_w03(void) {
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
    func_80107360_w03();
    if (D_8011EB24_w03 == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                D_8011EB28_w03 = order[i];
                break;
            }
        }
    } else if (D_8011EB24_w03 == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                D_8011EB28_w03 = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        D_8011EB24_w03 = 2;
    }
}

s32 func_80107628_w03(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 == 0) {
                    func_80107490_w03();
                    var_s2 = D_8011EB24_w03 + 1;
                } else {
                    var_s2 = D_8011EB28_w03 + 1;
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

s32 func_801078F4_w03(u8 *arg0) {
    return func_80107628_w03(arg0, 0, 1);
}

s32 func_80107914_w03(u8 *arg0) {
    return func_80107628_w03(arg0, 1, 0);
}

// entrypoint 0
void func_80107934_w03(void) {
    GwSystem.current_board_index = 2;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

// entrypoint 1
void func_80107970_w03(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    func_801059F8_w03();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[2] = 0;
    omOvlReturnEx(1);
}

void func_80107A04_w03(void) {
    s32 i;

    omInitObjMan(0xA0, 0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(9, 0x23C, 0xB, 0);
    MBMasuBlockTblExtSet(D_8011C164_w03);
    MBMasuBlockTblSet(D_8011C16C_w03);
    MBItemHookSet(0, &func_8010DF54_w03);
    MBItemHookSet(1, &func_8010F3D4_w03);
    MBItemHookSet(9, &func_8010F79C_w03);
    MBItemHookSet(2, &func_8010F808_w03);
    MBItemHookSet(3, &func_80117D38_w03);
    MBItemHookSet(4, &func_80110A14_w03);
    MBItemHookSet(5, &func_80110CA0_w03);
    MBItemHookSet(6, &func_8010FCFC_w03);
    MBItemHookSet(7, &func_8011026C_w03);
    MBItemHookSet(8, &func_801105B8_w03);
    MBItemHookSet(0xA, &func_80117034_w03);
    MBItemHookSet(0xB, &func_801178B4_w03);
    MBItemHookSet(0xE, &func_801110F0_w03);
    MBItemHookSet(0xF, &func_801113B0_w03);
    MBItemHookSet(0x10, &func_80111750_w03);
    MBItemHookSet(0x11, &func_8011214C_w03);
    MBItemHookSet(0x12, &func_80112CA4_w03);
    MBItemHookSet(0x13, &func_801139BC_w03);
    MBItemHookSet(0x14, &func_80114C58_w03);
    MBItemHookSet(0x15, &func_80115C58_w03);
    MBItemHookSet(0xC, &func_80116E84_w03);
    MBItemHookSet(0xD, &func_8011777C_w03);
    MBComItemDecideHookSet(func_8011B71C_w03);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, D_8011C150_w03[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        func_80105B44_w03();
    }

    func_80105C50_w03();
    func_80107F30_w03();
    func_80108118_w03();
    func_801083DC_w03();
    func_801085B0_w03();
    func_80108820_w03();
    func_801088A0_w03();
    func_80116B78_w03();
    func_800EBDAC_shared_board();
    omAddPrcObj(func_8011908C_w03, 0x4800, 0, 0);
}

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
void func_80107D28_w03(void) {
    Hu3DCamInit(1);
    func_80107A04_w03();
    MBStart(1);
}

void func_80107D54_w03(s16 arg0) {
    Object *obj;

    if (D_8011EAC8_w03[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_8001FA68_main(obj->omObj1->model[0]);
    func_8001F9E4_main(obj->omObj1->model[0], 0xFF);
    func_8001FA68_main(obj->omObj2->model[0]);
    func_8001F9E4_main(obj->omObj2->model[0], 0xFF);
    func_800461B4_main(obj->omObj1->model[0]);
    if (D_8011EAC0_w03 == NULL) {
        D_8011EAC0_w03 = obj;
    }
    D_8011EAC8_w03[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_8011EAE8_w03[arg0] = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C1C8_w03[arg0])->coords);
    GwSystem.boardData.halfWordBytes[1] = func_800D771C_shared_board(0xB, obj, D_8011C180_w03[arg0][0], D_8011C180_w03[arg0][1]);
}

void func_80107ECC_w03(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        Process *prc = D_8011EAE8_w03[i];

        if (prc != NULL) {
            omDelPrcObj(prc);
            D_8011EAE8_w03[i] = NULL;
        }
    }
}

void func_80107F30_w03(void) {
    s32 i;

    D_8011EAC0_w03 = NULL;
    for (i = 0; i < 8; i++) {
        D_8011EAC8_w03[i] = NULL;
        D_8011EAE8_w03[i] = NULL;
        MBKinokoEffKillHookSet(func_80107ECC_w03);
        if (!GWBoardFlagCheck(D_8011C1D8_w03[i])) {
            func_80107D54_w03(i);
        }
    }
    if (GwSystem.boardData.halfWordBytes[0] != -1) {
        func_80107D54_w03(GwSystem.boardData.halfWordBytes[0]);
    }
}

void func_80107FF8_w03(s16 arg0) {
    Object *obj;

    if (D_8011EB58_w03[arg0] != NULL) {
        return;
    }
    if (D_8011EB54_w03 == NULL) {
        obj = MBModelCreate(0xA, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_8011EB54_w03 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EB54_w03);
    }
    MBModelDispOff(obj);
    D_8011EB58_w03[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C1E8_w03[arg0])->coords);
    func_800D771C_shared_board(0xA, obj, D_8011C1A0_w03[arg0][0], D_8011C1A0_w03[arg0][1]);
}

void func_80108118_w03(void) {
    s32 i;

    D_8011EB54_w03 = 0;
    for (i = 0; i <= 0; i++) {
        D_8011EB58_w03[i] = NULL;
        func_80107FF8_w03(i);
    }
}

void func_80108174_w03(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(D_8011EB60_w03[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(D_8011EB60_w03[i * 5 + j]);
        }
    }
}

void func_80108270_w03(s16 arg0) {
    Object *obj;

    if (D_8011EB60_w03[arg0] != NULL) {
        return;
    }
    if (D_8011EB5C_w03 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_8011EB5C_w03 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EB5C_w03);
    }
    D_8011EB60_w03[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C1EC_w03[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &D_8011C1F0_w03[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = D_8011C22C_w03[arg0 % 5].x;
    obj->omObj1->rot.z = D_8011C22C_w03[arg0 % 5].z;
    MBModelDispOff(obj);
}

void func_801083DC_w03(void) {
    s32 i;

    D_8011EB5C_w03 = 0;
    for (i = 0; i < 0xA; i++) {
        D_8011EB60_w03[i] = NULL;
        func_80108270_w03(i);
    }
    func_80108174_w03();
}

void func_80108444_w03(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (D_8011EB8C_w03[arg0] != NULL) {
        return;
    }
    if (D_8011EB88_w03 == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(D_8011C26C_w03[board], D_8011C2A8_w03[board]);
        MBModelTempAllocFree(obj);
        D_8011EB88_w03 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EB88_w03);
    }
    D_8011EB8C_w03[arg0] = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C268_w03[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(D_8011C1C0_w03[arg0][0]);
        SpaceData *masuB = MBMasuGet(D_8011C1C0_w03[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    func_800D771C_shared_board(0xC, obj, D_8011C1B8_w03[arg0][0], D_8011C1B8_w03[arg0][1]);
}

void func_801085B0_w03(void) {
    s32 i;

    D_8011EB88_w03 = 0;
    for (i = 0; i < 2; i++) {
        D_8011EB8C_w03[i] = NULL;
        func_80108444_w03(i);
    }
}

void func_80108610_w03(void) {
    HuPrcSleep(D_8011C308_w03[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011C2E4_w03[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void func_8010866C_w03(s32 arg0, s32 arg1) {
    MBMotionSet(D_8011EB8C_w03[arg0], arg1 - 1, 0);
    func_8001C814_main(D_8011EB8C_w03[arg0]->omObj1->model[0], 5, 0);
    if (D_8011C2C0_w03[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011C2C0_w03[GwSystem.current_board_index]);
    }

    if (D_8011C2E4_w03[GwSystem.current_board_index] != -1) {
        omAddPrcObj(func_80108610_w03, 0x1000, 0, 0);
    }
}

void func_80108734_w03(void) {
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
    func_8001C814_main(D_8011EB8C_w03[index]->omObj1->model[0], 1, 4);

    if (D_8011C32C_w03[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011C32C_w03[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void func_801087E4_w03(s32 arg) {
    Process *temp = omAddPrcObj(func_80108734_w03, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void func_80108820_w03(void) {
    s32 i;

    D_8011EB88_w03 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011C350_w03[i])->coords,
                                         D_8011C1A8_w03[i][0], D_8011C1A8_w03[i][1]);
    }
}

void func_801088A0_w03(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011C354_w03[i])->coords,
                                         D_8011C1B0_w03[i][0], D_8011C1B0_w03[i][1]);
    }
}

s32 func_80108918_w03(s16 *list) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    for (; i < 8; i++) {
        if (*list == GwSystem.boardData.halfWordBytes[0]) {
            found = 1;
            break;
        }
        if (!GWBoardFlagCheck(D_8011C358_w03[*list])) {
            break;
        }
        list++;
    }
    return found;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E910_w03);

s32 func_801089AC_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 *list;

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x79:
            list = D_8011C368_w03;
            break;
        case 0x84:
            list = D_8011C378_w03;
            break;
        case 0x89:
            list = D_8011C388_w03;
            break;
        case 0x8A:
            list = D_8011C398_w03;
            break;
        case 0x8B:
            list = D_8011C3A8_w03;
            break;
        case 0x6F:
            list = D_8011C3B8_w03;
            break;
        default:
            list = D_8011C3C8_w03;
            break;
    }
    if (func_80108918_w03(list) != 0) {
        GwSystem.boardData.halfWordBytes[2] |= 1 << GwSystem.current_player_index;
    } else {
        GwSystem.boardData.halfWordBytes[2] &= ~(1 << GwSystem.current_player_index);
    }
    return 0;
}

void func_80108AB8_w03(void) {
    MBMoveNextMasuSet(-1, 1, 7);
}

void func_80108ADC_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x6D) {
        if (player->rev & 0x80) {
            if (mbWalkNum != 0) {
                func_8011655C_w03((SpaceTriple *)D_8011CAD8_w03, (BranchPair *)D_8011CAEC_w03, D_8011CABC_w03);
                return;
            }
            MBMoveBackMasuSet(-1, 1, 8);
        } else {
            MBMoveBackMasuSet(-1, 1, 6);
        }
    }
}

void func_80108B98_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x41 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 2, 0);
        player->rev &= ~1;
    } else {
        func_8011655C_w03((SpaceTriple *)D_8011CB20_w03, (BranchPair *)D_8011CB34_w03, D_8011C4C8_w03);
    }
    omDelPrcObj(NULL);
}

void func_80108C48_w03(void) {
    func_8011655C_w03(D_8011CB68_w03, D_8011CB7C_w03, D_8011C528_w03);
    omDelPrcObj(NULL);
}

void func_80108C80_w03(void) {
    func_8011655C_w03(D_8011CBB0_w03, D_8011CBC4_w03, D_8011C5F4_w03);
    omDelPrcObj(NULL);
}

void func_80108CB8_w03(void) {
    func_8011655C_w03(D_8011CBF8_w03, D_8011CC0C_w03, D_8011C6D8_w03);
    omDelPrcObj(NULL);
}

void func_80108CF0_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x32 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 9, 0);
        player->rev &= ~1;
    } else {
        func_8011655C_w03((SpaceTriple *)D_8011CC40_w03, (BranchPair *)D_8011CC54_w03, D_8011C774_w03);
    }
    omDelPrcObj(NULL);
}

void func_80108DA0_w03(void) {
    func_8011655C_w03(D_8011CC88_w03, D_8011CC9C_w03, D_8011C804_w03);
    omDelPrcObj(NULL);
}

void func_80108DD8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03((SpaceTriple *)D_8011CCD0_w03, (BranchPair *)D_8011CCE4_w03, D_8011C864_w03);
    }
}

void func_80108E30_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03((SpaceTriple *)D_8011CD18_w03, (BranchPair *)D_8011CD2C_w03, D_8011C864_w03);
    }
}

void func_80108E88_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03((SpaceTriple *)D_8011CD60_w03, (BranchPair *)D_8011CD74_w03, D_8011C8D0_w03);
    }
}

void func_80108EE0_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03((SpaceTriple *)D_8011CDA8_w03, (BranchPair *)D_8011CDBC_w03, D_8011C924_w03);
    }
}

void func_80108F38_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    UnkEA790Struct *win;
    s32 sel;
    s32 choice;
    s32 sel2;
    s32 i;

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MBPlayerMotionSet(-1, -1, 2);
        HuPrcVSleep();
        func_80106D84_w03();

        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
            case 0x62:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CDF0_w03);
                choice = MBRand(3.0f);
                break;
            case 0x46:
                choice = 2;
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CDF8_w03);
                break;
            case 0x45:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CE00_w03);
                choice = MBRand(3.0f);
                break;
            default:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CE08_w03);
                choice = MBRand(3.0f);
                break;
        }

        func_800D742C_shared_board(win, GwSystem.current_player_index, 0);

        if (MBPlayerComCheck(-1) != 0) {
            sel = choice;
            for (i = 0; i < sel; i++) {
                func_800D7250_shared_board(win, -2);
            }
            func_800D7250_shared_board(win, -4);
        }

        sel2 = func_800D7518_shared_board(win);
        func_800D6CA0_shared_board(win);
        func_80106E54_w03();

        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
            case 0x62:
                switch (sel2) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 0xA, 6);
                        player->rev |= 1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 0xC, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            case 0x46:
                switch (sel2) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 0xA, 6);
                        player->rev |= 1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 0xC, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            case 0x45:
                switch (sel2) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 0xC, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            default:
                switch (sel2) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 0xA, 6);
                        player->rev |= 1;
                        break;
                }
                break;
        }
    }
}

void func_80109268_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x3B) {
        MBMoveNextMasuSet(-1, 11, 11);
    }
}

void func_801092C8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x43) {
        MBMoveNextMasuSet(-1, 1, 13);
    }
}

void func_80109328_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x8) {
        MBMoveNextMasuSet(-1, 2, 9);
    }
}

void func_80109388_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x9) {
        MBMoveNextMasuSet(-1, 2, 2);
    }
}

void func_801093E8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0xD) {
        MBMoveNextMasuSet(-1, 2, 9);
    }
}

void func_80109448_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0xF) {
        MBMoveNextMasuSet(-1, 4, 2);
    }
}

void func_801094A8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x54) {
        MBMoveNextMasuSet(-1, 4, 2);
    }
}

void func_80109508_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5B) {
        MBMoveNextMasuSet(-1, 5, 10);
    }
}

void func_80109568_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2A) {
        MBMoveNextMasuSet(-1, 5, 25);
    }
}

void func_801095C8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2F) {
        MBMoveNextMasuSet(-1, 5, 20);
    }
}

void func_80109628_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x8B) {
        MBMoveNextMasuSet(-1, 5, 25);
    }
}

void func_80109688_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5E) {
        MBMoveNextMasuSet(-1, 8, 1);
    }
}

void func_801096E8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x51) {
        MBMoveNextMasuSet(-1, 5, 18);
    }
}

void func_80109748_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x42) {
        MBMoveNextMasuSet(-1, 1, 13);
    }
}

void func_801097A8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x44) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void func_80109808_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x33) {
        MBMoveNextMasuSet(-1, 8, 1);
    }
}

void func_80109868_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2) {
        MBMoveNextMasuSet(-1, 11, 11);
    }
}

s32 func_801098C8_w03(s32 arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g1Unk4Bytes *)sp20 = *(g1Unk4Bytes *)D_8011E910_w03;

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
                func_8005F698_main(sp18[0], sp18[1], sp18[2], sp18[3], 0x5);
            }
        }
    } else {
        func_8005F744_main(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return func_8005E1D8_main(mbDlgWinId, 0, 1);
}

void func_80109AD8_w03(void) {
    GW_PLAYER *player;
    Process *proc;
    UnkVibrateProcess *vib;
    s32 masu;
    s32 ret;
    s32 blocked = 1;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(-1);
    masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);

    if ((((masu == 0x74) | (masu == 0x8C)) == 0 || !(player->rev & 1)) &&
        (((masu == 0x75) | (masu == 0x8D)) == 0 || (player->rev & 1))) {
        MBPlayerMotionSet(-1, -1, 2);

        if (MBItemFind(system->current_player_index, 1) != -1) {
            func_800DBEC0_shared_board(system->current_player_index);
            switch (masu) {
                case 0x74:
                case 0x75:
                    func_800ED20C_shared_board(-1, 8, 0x7D);
                    break;
                default:
                    func_800ED20C_shared_board(-1, 8, 0x7E);
            }

            proc = HuPrcCurrentGet();
            HuPrcChildLink(proc, MBCameraZoomMotStart(1.6f));
            HuPrcChildWait();
            MBPlayerVibrate(-1, 1);

            while (1) {
                MBDlgWinCreate(0x38, 0x4103);
                ret = func_801098C8_w03(0);
                MBDlgWinClose();
                MBDlgWinKill();
                switch (ret) {
                    case 0:
                        MBDlgWinExec(0x38, 0x4104);
                        GwPlayer[system->current_player_index].itemNo[MBItemFind(system->current_player_index, 1)] = -1;
                        MBItemRemoveEmpty(GwSystem.current_player_index);
                        MBStatusItemIconSprReinit(-1);
                        switch (masu) {
                            case 0x74:
                                func_8010866C_w03(0, 0);
                                break;
                            case 0x75:
                                func_8010866C_w03(0, 1);
                                break;
                            case 0x8C:
                                func_8010866C_w03(1, 0);
                                break;
                            default:
                                func_8010866C_w03(1, 1);
                                break;
                        }
                        blocked = 0;
                        vib = MBPlayerVibrateObjCreate(-1, 2, 5);
                        HuPrcSleep(0x14);
                        MBPlayerVibrateObjKill(vib);
                        break;
                    case 1:
                        MBDlgWinExec(0x38, 0x4105);
                        break;
                    case 2:
                        func_80106CA0_w03();
                        continue;
                }
                break;
            }
            func_800DB884_shared_board(system->current_player_index);
            proc = HuPrcCurrentGet();
            HuPrcChildLink(proc, MBCameraZoomMotStart(1.3f));
            HuPrcChildWait();
        } else {
            MBDlgWinExec(-1, 0x4106);
        }

        if (blocked != 0) {
            switch (masu) {
                case 0x74:
                    MBMoveNextMasuSet(-1, 0xA, 1);
                    player->rev |= 1;
                    break;
                case 0x75:
                    MBMoveNextMasuSet(-1, 0xA, 5);
                    player->rev &= ~1;
                    break;
                case 0x8C:
                    MBMoveNextMasuSet(-1, 0xB, 2);
                    player->rev |= 1;
                    break;
                default:
                    MBMoveNextMasuSet(-1, 0xB, 6);
                    player->rev &= ~1;
                    break;
            }
        }
    }
    omDelPrcObj(NULL);
}

void func_80109E90_w03(void) {
}

void func_80109E98_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == 2 && MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x63) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void func_80109F3C_w03(void) {
}

s32 func_80109F44_w03(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(g2Unk4Bytes *)sp20 = *(g2Unk4Bytes *)D_8011E910_w03;

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

void func_8010A1C8_w03(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
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

void func_8010A284_w03(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010A2C4_w03);

void func_8010A930_w03(void) {
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
        case 0x1C:
            func_800ED20C_shared_board(-1, 8, 0x7B);
            spaceA = MBMasuGet(0x7B);
            spaceB = MBMasuGet(0x1C);
            break;
        case 0x5F:
            func_800ED20C_shared_board(-1, 8, 0x78);
            spaceA = MBMasuGet(0x78);
            spaceB = MBMasuGet(0x5F);
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

    effectModel = MBModelCreate(0x35, D_8011CF68_w03);
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
        choice = func_80109F44_w03((s32)D_8011CF50_w03, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                func_80106CA0_w03();
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
        sprintf(sp20, D_8011E98C_w03, GwSystem.bank_coins);
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
            func_80113080_w03();
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
                sprintf(sp20, D_8011E98C_w03, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, D_8011E98C_w03, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                func_80108174_w03();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, D_8011E98C_w03, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, D_8011E98C_w03, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                func_80108174_w03();
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
                sprintf(sp20, D_8011E98C_w03, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                func_80108174_w03();
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
    func_80109E90_w03();
}

s32 func_8010B46C_w03(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011EB9C_w03[i] != 0) {
            if (D_8011CF98_w03[D_8011EB94_w03][D_8011EB98_w03][i] == arg0) {
                return i;
            }
        }
    }
    return -1;
}

s32 func_8010B4F4_w03(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011CF98_w03[D_8011EB94_w03][D_8011EB98_w03][i] == -1) {
            break;
        }
    }
    return i;
}

void func_8010B55C_w03(void) {
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
