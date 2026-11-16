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

// board p2
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

// board p2: declarations for func_8010B734_w03..func_80110EE0_w03
typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ Object *model;
    /* 0x1C */ u16 unk1C;
} ModelFadeWork;

typedef struct WarpBlockSwapWork {
    /* 0x00 */ s16 startX;
    /* 0x02 */ s16 startY;
    /* 0x04 */ s16 endX;
    /* 0x06 */ s16 endY;
    /* 0x08 */ s16 duration;
    /* 0x0A */ s16 spriteGroup;
} WarpBlockSwapWork;

void func_8001ED54_main(s16 arg0);
void func_800D9F5C_shared_board(Object *arg0, Vec *arg1, s32 arg2);
void func_8010F2BC_w03(omObjData *arg0);
void func_80106C2C_w03(Object *arg);
void func_80106CA0_w03(void);
void func_80106D28_w03(void);
s32 func_80106EB4_w03(u8 *arg0);
s32 func_80107148_w03(void);
s32 func_801078F4_w03(u8 *arg0);
s32 func_80107914_w03(u8 *arg0);
void func_801087E4_w03(s32 arg);
void func_8010B55C_w03(void);
void func_801128B0_w03(void);
omObjData *func_8010F160_w03(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5);
Process *func_8010FC2C_w03(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration);
void func_8010FF2C_w03(void);
extern s16 D_8011C140_w03[];
extern s32 D_8011C160_w03;
extern u8 D_8011CF80_w03[2][3][4];
extern s8 D_8011CF98_w03[][5][7];
extern u8 D_8011CFE0_w03[2][3][4];
extern s8 D_8011CFF8_w03[2][5][10];
extern u8 D_8011D05C_w03[2][10];
extern s32 D_8011D070_w03[5][2];
extern s32 D_8011D098_w03[2];
extern s32 D_8011D0A0_w03[2];
extern s32 D_8011D0A8_w03[2];
extern s32 D_8011D0B0_w03[2];
extern s32 D_8011D0B8_w03[2];
extern u32 D_8011D0C0_w03[];
extern u32 D_8011D0C8_w03[];
extern s32 D_8011D0D0_w03;
extern Vec2f D_8011D0E4_w03[];
extern Vec2f D_8011D104_w03[];
extern u8 D_8011D124_w03[6][3];
extern u8 D_8011D138_w03[14][3];
extern u8 D_8011D164_w03[];
extern s32 D_8011D16C_w03[];
extern s32 D_8011D178_w03[];
extern Vec2f D_8011D24C_w03[];
extern Vec2f D_8011D26C_w03[];
extern s32 D_8011D338_w03[];
extern Object *D_8011EB54_w03;
extern Object *D_8011EB58_w03[1];
extern s32 D_8011EB94_w03;
extern s32 D_8011EB98_w03;
extern u8 *D_8011EB9C_w03;
extern Object *D_8011EBA0_w03;
extern s32 D_8011EBA4_w03;

void func_8010B734_w03(void) {
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
        case 0x6E:
            camMasu = 0x76;
            spaceA = MBMasuGet(0x76);
            spaceB = MBMasuGet(0x6E);
            D_8011D0D0_w03 = 0;
            break;
        case 0x71:
            camMasu = 0x77;
            spaceA = MBMasuGet(0x77);
            spaceB = MBMasuGet(0x71);
            D_8011D0D0_w03 = 1;
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
            effectModel = MBModelCreate(0x39, D_8011D0C8_w03);
        } else {
            effectModel = MBModelCreate(0x1B, D_8011D0C0_w03);
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
        MBDlgWinExec(dlgWin, D_8011D0B0_w03[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, D_8011D0A8_w03[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, D_8011D0A0_w03[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, D_8011D098_w03[shopIdx]);
    choice = func_80107148_w03();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = BoardGetTurnTier(-1);
            row = D_8011CF80_w03[shopIdx][i][BoardPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (D_8011CF98_w03[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_8011CF98_w03[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (D_8011CF98_w03[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_80100F94_shared_board[D_8011CF98_w03[shopIdx][row][j]] >
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

            MBDlgWinInsertCreate(dlgWin, D_8011D070_w03[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            func_800ECAA8_shared_board(0);
            D_8011EB94_w03 = slot;
            D_8011EB98_w03 = row;
            D_8011EB9C_w03 = enabled;
            sel = func_80106EB4_w03(enabled);
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
            shopTable = D_8011CF98_w03;
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
                    D_8011CF98_w03[shopIdx][row][sel];
                item = D_8011CF98_w03[shopIdx][row][sel];
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

            if (D_8011CF98_w03[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = D_8011CFE0_w03[shopIdx][BoardGetTurnTier(-1)]
                                                [BoardPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < D_8011CFF8_w03[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = D_8011D05C_w03[shopIdx][i];

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
                    prc = omAddPrcObj(func_8010B55C_w03, 0x4002, 0, 0);
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
            MBDlgWinExec(dlgWin, D_8011D0B8_w03[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                func_80106D28_w03();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106CA0_w03();
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

void func_8010C9EC_w03(Object *obj) {
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

void func_8010CA8C_w03(Object *obj) {
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

s32 func_8010CB2C_w03(s32 playerIndex) {
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
    func_80054904_main(grp, 0, D_8011D0E4_w03[playerIndex].x,
                        D_8011D0E4_w03[playerIndex].y);
    func_80055458_main(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        func_80054904_main(grp, 0,
                            (i * D_8011D104_w03[playerIndex].x) +
                                D_8011D0E4_w03[playerIndex].x,
                            (i * D_8011D104_w03[playerIndex].y) +
                                D_8011D0E4_w03[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    func_80055458_main(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(func_801128B0_w03, 0x4002, 0, 0);
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
                            (D_8011D104_w03[playerIndex].x * 16.0f) +
                                D_8011D0E4_w03[playerIndex].x,
                            (D_8011D104_w03[playerIndex].y * 16.0f) +
                                D_8011D0E4_w03[playerIndex].y +
                                (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        func_80054904_main(grp, 0,
                            (i * D_8011D104_w03[playerIndex].x) +
                                D_8011D0E4_w03[playerIndex].x,
                            (i * D_8011D104_w03[playerIndex].y) +
                                D_8011D0E4_w03[playerIndex].y);
        func_80055458_main(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprKill(spriteId);
    return !hasRareItem;
}

void func_8010CF74_w03(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

s32 func_8010CF98_w03(s32 playerIndex) {
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
    func_80054904_main(grp, 0, D_8011D0E4_w03[playerIndex].x,
                        D_8011D0E4_w03[playerIndex].y);
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
                            D_8011D0E4_w03[playerIndex].x -
                                (D_8011D104_w03[playerIndex].x * 16.0f) - 8.0f,
                            D_8011D0E4_w03[playerIndex].y +
                                (D_8011D104_w03[playerIndex].y * 16.0f));
        func_80055458_main(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            func_80054904_main(grp, 0,
                                (i * D_8011D104_w03[playerIndex].x) +
                                    D_8011D0E4_w03[playerIndex].x,
                                (i * D_8011D104_w03[playerIndex].y) +
                                    D_8011D0E4_w03[playerIndex].y);
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
            omAddPrcObj(func_8010CF74_w03, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(func_801128B0_w03, 0x4002, 0, 0);
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
                    (D_8011D104_w03[playerIndex].x * 16.0f) +
                        D_8011D0E4_w03[playerIndex].x,
                    (D_8011D104_w03[playerIndex].y * 16.0f) +
                        D_8011D0E4_w03[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                func_80054904_main(
                    grp, 0,
                    (D_8011D104_w03[playerIndex].x * 16.0f) +
                        D_8011D0E4_w03[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (D_8011D104_w03[playerIndex].y * 16.0f) +
                        D_8011D0E4_w03[playerIndex].y);
                func_80054904_main(
                    playerGrp, 0,
                    D_8011D0E4_w03[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (D_8011D104_w03[playerIndex].y * 16.0f) +
                        D_8011D0E4_w03[playerIndex].y);
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
                            playerGrp, 0, D_8011D0E4_w03[playerIndex].x - 8.0f,
                            (D_8011D104_w03[playerIndex].y * 16.0f) +
                                D_8011D0E4_w03[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                func_80055140_main(playerGrp, 0, 0, 0);
                func_800550F4_main(playerGrp, 0, 1);
                playerSpriteVisible = 0;
                func_80054904_main(
                    playerGrp, 0,
                    D_8011D0E4_w03[playerIndex].x -
                        (D_8011D104_w03[playerIndex].x * 16.0f) - 8.0f,
                    (D_8011D104_w03[playerIndex].y * 16.0f) +
                        D_8011D0E4_w03[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(func_8010CF74_w03, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011D104_w03[playerIndex].x) +
                                    D_8011D0E4_w03[playerIndex].x,
                                (i * D_8011D104_w03[playerIndex].y) +
                                    D_8011D0E4_w03[playerIndex].y);
            func_80055458_main(grp, 0, i << 4);
            func_80055458_main(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            func_80054904_main(grp, 0,
                                (i * D_8011D104_w03[playerIndex].x) +
                                    D_8011D0E4_w03[playerIndex].x,
                                (i * D_8011D104_w03[playerIndex].y) +
                                    D_8011D0E4_w03[playerIndex].y);
            func_80054904_main(playerGrp, 0,
                                ((i - 0x10) * D_8011D104_w03[playerIndex].x) +
                                    D_8011D0E4_w03[playerIndex].x - 8.0f,
                                (i * D_8011D104_w03[playerIndex].y) +
                                    D_8011D0E4_w03[playerIndex].y);
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
        for (i = 0; i < ARRAY_COUNTU(D_8011D124_w03); i++) {
            if ((GwSystem.current_turn >= D_8011D124_w03[i][0]) &&
                (GwSystem.current_turn <= D_8011D124_w03[i][1])) {
                break;
            }
        }
        playerSpriteVisible = D_8011D124_w03[i][2];
        for (i = 0; i < ARRAY_COUNTU(D_8011D138_w03); i++) {
            if ((attempts >= D_8011D138_w03[i][0]) &&
                (attempts <= D_8011D138_w03[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= D_8011D138_w03[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

const char D_8011E98C_w03[] = "%d";

void func_8010DDC4_w03(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011EBA0_w03);
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

void func_8010DF18_w03(Object *arg) {
    Process *temp = omAddPrcObj(func_8010DDC4_w03, 0x1000, 0, 0);

    temp->user_data = arg;
}

void func_8010DF54_w03(void) {
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
    if (spaceId != 0x8E) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(D_8011EB54_w03);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x6C;
        space = MBMasuGet(0x6C);
        boo = D_8011EB58_w03[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (D_8011D178_w03[sys->current_board_index] != 0) {
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
            if (D_8011D178_w03[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011D178_w03[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (D_8011D178_w03[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        func_8001C92C_main(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    func_8010C9EC_w03(boo);
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
    menuResult = func_801078F4_w03(choices);
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
    playerChoice = func_80107914_w03(choices);
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
                func_80106D28_w03();
                D_800CB99C_main = 1;
                func_80049FB8_main();
            } else {
                func_80106CA0_w03();
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
        if (rank < D_8011D16C_w03[i]) {
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
            if (GwSystem.current_turn >= D_8011D124_w03[i][0] &&
                GwSystem.current_turn <= D_8011D124_w03[i][1]) {
                break;
            }
        }
        estimatedAmount = D_8011D124_w03[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    func_8010CA8C_w03(boo);
    if (menu == 0) {
        resultAmount = func_8010CF98_w03(target);
        func_8010C9EC_w03(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], D_8011E98C_w03, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], D_8011E98C_w03, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= D_8011D164_w03[i]) {
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
            D_8011EBA0_w03 = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(D_8011EBA0_w03);
            MBModelDispOff(D_8011EBA0_w03);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    func_8010DF18_w03(boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(D_8011EBA0_w03);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            func_8004ACE0_main(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = func_8010CB2C_w03(target);
        func_8010C9EC_w03(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            D_8011C160_w03 = 1;
            func_80106C2C_w03(boo);
            D_8011C160_w03 = 0;
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
    func_8010CA8C_w03(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        func_80106D28_w03();
        D_800CB99C_main = 1;
        func_80049FB8_main();
    } else {
        func_80106CA0_w03();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        func_8010CA8C_w03(boo);
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
            if (D_8011D178_w03[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011D178_w03[sys->current_board_index] != 0) {
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
    func_80109F3C_w03();
}

void func_8010F128_w03(void) {
    func_801087E4_w03(0);
}

void func_8010F144_w03(void) {
    func_801087E4_w03(1);
}

omObjData *func_8010F160_w03(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5) {
    omObjData *obj;
    ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, func_8010F2BC_w03);
    data = obj->data = HuMemAllocTag(0x20, 0x7918);
    data->unk0C = 255.0f;
    data->unk10 = arg1;
    data->unk14 = arg2;
    HuVecCopy3F(&data->unk00, arg4);
    if (arg5 != 0) {
        model = MBModelFileCreate(0x1301F8, 0, 1.0f, 0, 0);
    } else {
        model = MBModelFileCreate(0x1301F7, 0, 1.0f, 0, 0);
    }
    Hu3DModelScaleSet(model->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    model->coords.x = arg0->x;
    model->coords.y = arg0->y;
    model->coords.z = arg0->z;
    func_8001FA68_main(model->omObj1->model[0]);
    func_8001F9E4_main(model->omObj1->model[0], 0xFF);
    data->model = model;
    data->unk1C = arg3;
    return obj;
}

void func_8010F2BC_w03(omObjData *arg0) {
    ModelFadeWork *data = arg0->data;
    Object *model = data->model;
    f32 scale;
    f32 alpha;

    HuVecAdd(&model->coords, &model->coords, &data->unk00);
    scale = model->scale.z + data->unk10;
    model->scale.z = scale;
    model->scale.y = scale;
    model->scale.x = scale;
    alpha = data->unk0C - data->unk14;
    data->unk0C = alpha;
    if (alpha < 0.0f) {
        data->unk0C = 0.0f;
        if (data->unk1C != 0) {
            MBModelKill(data->model);
            omDelObj(arg0);
            return;
        }
        omSetStatBit(arg0, 8);
    }
    func_8001F9E4_main(model->omObj1->model[0], (u8)data->unk0C);
}

void func_8010F3D4_w03(void) {
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
    func_8010FF2C_w03();
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
        Vec particleDir[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010F160_w03(&pos, 0.1f, 2.0f, 1, &particleDir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    func_800EB24C_shared_board(
        D_8011C140_w03[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
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
        Vec particleDir2[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010F160_w03(&pos, 0.1f, 2.0f, 1, &particleDir2[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            func_80003A70_main(0);
        }
    }
}

void func_8010F79C_w03(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011C140_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void func_8010F808_w03(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    func_8010FF2C_w03();
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

void func_8010F9C8_w03(void) {
    Process *process = HuPrcCurrentGet();
    WarpBlockSwapWork *work = process->user_data;
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

Process *func_8010FC2C_w03(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY,
                                  s16 duration) {
    Process *process;
    WarpBlockSwapWork *work;

    process = omAddPrcObj(func_8010F9C8_w03, 0x4002, 0, 0x40);
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

void func_8010FCFC_w03(void) {
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
    HuPrcChildLink(process, func_8010FC2C_w03(
                                mbItemCursorGrpId, position[0], position[1],
                                D_8011D24C_w03[system->current_player_index].x,
                                D_8011D24C_w03[system->current_player_index].y, -1));
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

void func_8010FF2C_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    func_80055140_main(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    func_8010FC2C_w03(
        mbItemCursorGrpId, position[0], position[1],
        D_8011D26C_w03[system->current_player_index].x,
        D_8011D26C_w03[system->current_player_index].y, -1);
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

void func_801100FC_w03(void) {
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
                   func_8010FC2C_w03(mbItemCursorGrpId, position[0], position[1],
                                            targetX, targetY, -1));
    HuPrcChildWait();

    for (i = 1; i < 10; i++) {
        func_80055458_main(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    func_80055458_main(mbItemCursorGrpId, 0, 0);
    HuSprAttrSet(mbItemCursorGrpId, 0, 0x8000);
}

void func_8011026C_w03(void) {
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
                   func_8010FC2C_w03(mbItemCursorGrpId, position[0], position[1],
                                            D_8011D24C_w03[system->current_player_index].x,
                                            D_8011D24C_w03[system->current_player_index].y, -1));
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

void func_801105B8_w03(void) {
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
                   func_8010FC2C_w03(mbItemCursorGrpId, position[0], position[1],
                                            D_8011D24C_w03[system->current_player_index].x,
                                            D_8011D24C_w03[system->current_player_index].y, -1));
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

void func_8011077C_w03(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
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
                                 (f32)((f64)scale + 0.3));
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

void func_80110A14_w03(void) {
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

void func_80110CA0_w03(void) {
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

void func_80110EE0_w03(void) {
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
    func_80055024_main(group, 0, (s16)D_8011EBA4_w03, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x1000);
    func_800F6848_shared_board(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    func_80054904_main(group, 0, x, y);
    func_80055420_main(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)D_8011D338_w03[index];
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
