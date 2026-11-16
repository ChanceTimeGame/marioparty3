#include "common.h"
#include "game/board.h"
#include "game/object.h"
#include "malloc.h"
#include "game/sprite.h"
#include "game/data.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "game/wipe.h"
#include "math.h"
#include "game/audio.h"
#include "game/hmfman.h"
#include "../ovl_80_shared_board/1063F0.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/FA250.h"

// board h1: locals for func_801059D0_w10..func_80107F0C_w10
extern s16 D_8010B7F0_w10[4];
extern Vec D_8010B818_w10[];
extern Vec D_8010B854_w10[];
extern Object *D_8010BA24_w10;
extern Process *D_8010BA28_w10;
extern Object *D_8010BA2C_w10;
extern Object *D_8010BA30_w10;
extern Object *D_8010BA38_w10[2];

extern s16 D_8010B890_w10[];
extern s16 D_8010B898_w10[];
extern s32 D_8010B8C0_w10[];
extern s32 D_8010B8E8_w10[];
extern s16 D_8010BA4C_w10;
extern s16 D_8010BA4E_w10;
extern s16 D_8010BA50_w10;
extern s16 D_8010BA52_w10;
extern s16 D_8010BA54_w10;
extern Vec D_8010BA58_w10;
extern s16 D_8010B8FC_w10;
extern Object *D_8010BA68_w10;
extern Object *D_8010BA6C_w10;
extern Object *D_8010BA70_w10;
extern Object *D_8010BA74_w10;
extern u32 D_8010B900_w10[];
extern u32 D_8010B908_w10[];
extern s32 D_8010B918_w10;

/* Three-sprite panel: frame, tinted backing, picture. */
typedef struct W10SprWork {
    /* 0x00 */ s16 group;
    /* 0x02 */ s16 spr[3];
} W10SprWork; // size 0x8

void func_800461B4_main(s16 model);
void func_80105DC4_w10(void);
void func_80105E08_w10(void);
void func_800DCD64_shared_board(s32 arg0, s32 arg1);
void func_800EE614_shared_board(s32 arg0);
void func_800F591C_shared_board(s32 arg0);
void func_80107350_w10(omObjData *obj);
void func_801073C8_w10(omObjData *obj);
void func_8001FA68_main(s16 model);

void func_801059D0_w10(void) {
    GwSystem.current_board_index = 6;
    omInitObjMan(10, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

void func_80105A0C_w10(void) {
    s32 i;

    omInitObjMan(10, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->chr = D_8010B7F0_w10[i];
    }
    omOvlReturnEx(1);
}

void func_80105AB8_w10(void) {
    Object *obj;

    if (D_8010BA24_w10 == NULL) {
        obj = MBModelCreate(0x3A, NULL);
        func_800461B4_main(obj->omObj1->model[0]);
        MBModelTempAllocFree(obj);
        D_8010BA24_w10 = obj;
        obj->flags |= 2;
        HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
        obj->velocity.x = 10.0f;
        D_8010BA28_w10 = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
        HuVecCopy3F(&obj->coords, &MBMasuGet(0x25)->coords);
    }
}

void func_80105B70_w10(void) {
    D_8010BA24_w10 = NULL;
    func_80105AB8_w10();
}

void func_80105B90_w10(void) {
    Object *obj;

    if (D_8010BA2C_w10 == NULL) {
        obj = MBModelCreate(10, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_8010BA2C_w10 = obj;
        obj->flags |= 2;
        obj->velocity.x = 15.0f;
        HuVecCopy3F(&obj->coords, &MBMasuGet(0x24)->coords);
        MBModelDispOff(obj);
    }
}

void func_80105C28_w10(void) {
    D_8010BA2C_w10 = NULL;
    func_80105B90_w10();
}

void func_80105C48_w10(s16 arg0) {
    Object *obj;

    if (D_8010BA38_w10[arg0] == NULL) {
        if (D_8010BA30_w10 == NULL) {
            obj = MBModelCreate(0x1E, NULL);
            MBModelTempAllocFree(obj);
            D_8010BA30_w10 = obj;
        } else {
            obj = MBModelLinkCreate(D_8010BA30_w10);
        }
        D_8010BA38_w10[arg0] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &MBMasuGet(0x2F)->coords);
        HuVecAdd(&obj->coords, &D_8010B818_w10[arg0], &obj->coords);
        obj->omObj1->rot.x = D_8010B854_w10[arg0].x;
        obj->omObj1->rot.z = D_8010B854_w10[arg0].z;
    }
}

void func_80105D6C_w10(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_8010BA38_w10[i] = NULL;
        func_80105C48_w10(i);
    }
}

void func_80105DC4_w10(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    HuPrcSleep(3);
}

void func_80105E08_w10(void) {
}

void func_80105E10_w10(void) {
    UnkEA790Struct *choice;
    s32 i;
    s32 count;
    s32 result;

    MBPlayerMotionSet(-1, -1, 2);
    func_80105DC4_w10();
    choice = func_800D76A0_shared_board(-1, D_8010B890_w10);
    func_800D742C_shared_board(choice, -1, 0);
    if (MBPlayerComCheck(-1) != 0) {
        count = D_8010B898_w10[GwSystem.boardData.halfWordBytes[0]++];
        for (i = 0; i < count; i++) {
            func_800D7250_shared_board(choice, -2);
        }
        func_800D7250_shared_board(choice, -4);
    }
    result = func_800D7518_shared_board(choice);
    func_800D6CA0_shared_board(choice);
    func_80105E08_w10();
    if (result == 0) {
        MBMoveNextMasuSet(-1, 1, 0);
    } else {
        MBMoveNextMasuSet(-1, 2, 0);
    }
    omDelPrcObj(NULL);
}

void func_80105F20_w10(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->stat |= 1;
    }
}

void func_80105F64_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), func_800F292C_shared_board());
    HuPrcChildWait();
}

void func_80105FA0_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), func_800F29EC_shared_board());
    HuPrcChildWait();
}

W10SprWork *func_80105FDC_w10(s16 arg0, s16 x, s16 y) {
    W10SprWork *work;
    void *data;

    work = HuMemMemoryAllocTemp(sizeof(W10SprWork));
    work->group = HuSprGrpCreate(3, 0);
    data = DataRead(0x130000);
    work->spr[0] = func_80055810_main(data);
    func_80055024_main(work->group, 0, work->spr[0], 0);
    HuSprPriSet(work->group, 0, 11);
    HuSprAttrSet(work->group, 0, 0x1000);
    func_80054904_main(work->group, 0, x + 5, y);
    DataClose(data);
    data = DataRead(0x130001);
    work->spr[1] = func_80055810_main(data);
    func_80055024_main(work->group, 1, work->spr[1], 0);
    HuSprPriSet(work->group, 1, 12);
    HuSprAttrSet(work->group, 1, 0x1000);
    func_80054904_main(work->group, 1, x + 5, y);
    func_80055458_main(work->group, 1, 0xFF);
    func_80055420_main(work->group, 1, 0x1F, 0xB0, 0x3F);
    DataClose(data);
    data = DataRead(D_8010B8C0_w10[arg0]);
    work->spr[2] = func_80055810_main(data);
    func_80055024_main(work->group, 2, work->spr[2], 0);
    HuSprPriSet(work->group, 2, 10);
    HuSprAttrSet(work->group, 2, 0x1000);
    func_80054904_main(work->group, 2, x, y);
    DataClose(data);
    return work;
}

void func_801061E8_w10(W10SprWork *work) {
    HuSprKill(work->spr[0]);
    HuSprKill(work->spr[1]);
    HuSprKill(work->spr[2]);
    HuSprGrpKill(work->group);
    HuMemMemoryFreeTemp(work);
}

void func_80106230_w10(s16 arg0, s16 x, s16 y) {
    void *data;

    D_8010BA4C_w10 = HuSprGrpCreate(1, 0);
    data = DataRead(D_8010B8E8_w10[arg0]);
    D_8010BA4E_w10 = func_80055810_main(data);
    func_80055024_main(D_8010BA4C_w10, 0, D_8010BA4E_w10, 0);
    HuSprPriSet(D_8010BA4C_w10, 0, 11);
    HuSprAttrSet(D_8010BA4C_w10, 0, 0x1000);
    func_80054904_main(D_8010BA4C_w10, 0, x, y);
    DataClose(data);
}

void func_80106314_w10(s16 x, s16 y) {
    void *data;
    f32 scale;

    D_8010BA50_w10 = HuSprGrpCreate(1, 0);
    data = DataRead(0x130015);
    D_8010BA52_w10 = func_80055810_main(data);
    func_80055024_main(D_8010BA50_w10, 0, D_8010BA52_w10, 0);
    HuSprPriSet(D_8010BA50_w10, 0, 12);
    HuSprAttrSet(D_8010BA50_w10, 0, 0x1000);
    func_80055420_main(D_8010BA50_w10, 0, 0, 0xFF, 0);
    func_80054904_main(D_8010BA50_w10, 0, x, y);
    HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, 0.0f);
    DataClose(data);
    for (scale = 0.0f; scale < 1.0f; scale += 1.0f / 6) {
        HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, scale);
        HuPrcVSleep();
    }
    HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, 1.0f);
}

void func_8010649C_w10(void) {
    HuSprKill(D_8010BA4E_w10);
    HuSprGrpKill(D_8010BA4C_w10);
}

void func_801064C8_w10(void) {
    f32 scale;

    for (scale = 1.0f; scale > 0.0f; scale -= 1.0f / 6) {
        HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, scale);
        HuPrcVSleep();
    }
    HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, 0.0f);
    HuSprKill(D_8010BA52_w10);
    HuSprGrpKill(D_8010BA50_w10);
}

/* Camera follower process: a space (>= 0), the current player (-1) or D_8010BA58_w10 (-2). */
void func_80106574_w10(void) {
    Vec *pos;

    D_8010BA54_w10 = -1;
    MBPlayerPosFixSet(0, 1);
    MBPlayerPosFixSet(1, 1);
    MBPlayerPosFixSet(2, 1);
    MBPlayerPosFixSet(3, 1);
    WipeCreateIn(2, 0x10);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_800E6FCC_shared_board();
    while (1) {
        if (D_8010BA54_w10 < 0) {
            if (D_8010BA54_w10 == -2) {
                pos = &D_8010BA58_w10;
            } else {
                /* one variable for the object and its coords, as retail's a0 shows */
                pos = (Vec *)MBPlayerGet(-1)->player_obj;
                pos = &((Object *)pos)->coords;
            }
        } else {
            pos = &MBMasuGet(D_8010BA54_w10)->coords;
        }
        MBCameraPos3DSet(pos);
        HuPrcVSleep();
    }
}

void func_80106670_w10(s16 target) {
    D_8010BA54_w10 = target;
    MBCameraSpeedSet(4.0f);
}

void func_8010669C_w10(void) {
    HuPrcSleep(3);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    MBCameraSpeedSet(-1.0f);
}

void func_801066E8_w10(void) {
    s32 i;
    GW_PLAYER *player;

    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        player->color = 0;
        player->stat &= ~2;
    }
}

void func_80106730_w10(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        MBStatusColorSet(i, MBPlayerGet(i)->color);
    }
}

void func_80106774_w10(void) {
    GW_SYSTEM *sys = &GwSystem;
    s32 i;
    GW_PLAYER *player;

    sys->current_player_index++;
    if (sys->current_player_index >= 4) {
        sys->current_player_index = 0;
    }
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        MBPlayerForwardSet(i);
        MBMotionSet(player->player_obj, -1, 2);
        MBPlayerPosFixSet(i, 1);
    }
    MBCameraZoomSet(1.0f);
}

void func_8010681C_w10(Vec *arg0) {
    func_800FF840_shared_board(arg0);
}

void func_80106838_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBTelopCreate(GwSystem.current_player_index));
    HuPrcChildWait();
}

void func_8010687C_w10(s16 arg0) {
    GW_SYSTEM *sys = &GwSystem;
    Process *proc;
    Process *cur;

    func_800DCD64_shared_board(sys->current_player_index, arg0);
    cur = HuPrcCurrentGet();
    HuPrcChildLink(cur, MBCameraZoomMotStart(1.3f));
    proc = func_800DD6C4_shared_board(sys->current_player_index);
    HuPrcChildWait();
    HuPrcChildLink(cur, proc);
    HuPrcChildWait();
}

/* Walk the current player along the rolled number of spaces (the board's own copy of the
 * party walk loop: no reverse, no junction or pass events). */
void func_80106908_w10(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    s16 masu;
    s16 walkNum;
    s32 i;
    SpaceData *space;
    Vec dir;

    player = MBPlayerGet(CUR_PLAYER);
    masu = 0;
    walkNum = func_800DCD9C_shared_board(sys->current_player_index);
    MBPlayerMotionSet(-1, 0, 2);
    while (walkNum != 0) {
        s16 clink;
        s16 cidx;

        clink = player->clink;
        cidx = player->cidx;
        player->clink = player->nlink;
        player->cidx = player->nidx;
        for (i = 0; i < 4; i++) {
            MBPlayerPosFixSet(i, 10);
        }
        player->clink = clink;
        player->cidx = cidx;
        if ((MBMasuGet(MBMasuLinkMasuIdGet(player->nlink, player->nidx))->unk_02 & 0x8000)
            || func_800F9A68_shared_board(sys->current_player_index) != 0) {
            func_8004ACE0_main(0x3A, sys->current_player_index);
            MBPlayerMotionSet(-1, 2, 0);
            player->player_obj->velocity.y = 4.0f;
            player->player_obj->velocity.z = -0.5f;
            switch (sys->walk_speed) {
            case 0:
                player->player_obj->velocity.y = 8.0f;
                player->player_obj->velocity.z = -2.0f;
                MBPlayerPosMoveSet(sys->current_player_index, 7);
                break;
            case 1:
                player->player_obj->velocity.y = 4.0f;
                player->player_obj->velocity.z = -0.5f;
                MBPlayerPosMoveSet(sys->current_player_index, 15);
                break;
            case 2:
                player->player_obj->velocity.y = 2.0f;
                player->player_obj->velocity.z = -0.125f;
                MBPlayerPosMoveSet(sys->current_player_index, 30);
                break;
            }
        } else {
            if (player->player_obj->unk46 != 0) {
                MBPlayerMotionSet(-1, 0, 2);
            }
            switch (sys->walk_speed) {
            case 0:
                func_8001C92C_main(player->player_obj->omObj1->model[0], 2.0f);
                MBPlayerPosMoveSet(sys->current_player_index, 5);
                break;
            case 1:
                func_8001C92C_main(player->player_obj->omObj1->model[0], 1.0f);
                MBPlayerPosMoveSet(sys->current_player_index, 10);
                break;
            case 2:
                func_8001C92C_main(player->player_obj->omObj1->model[0], 0.75f);
                MBPlayerPosMoveSet(sys->current_player_index, 15);
                break;
            }
            func_8001C92C_main(player->player_obj->omObj1->model[0], 1.0f);
        }
        player->clink = player->nlink;
        player->cidx = player->nidx;
        player->nidx++;
        masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        space = MBMasuGet(masu);
        MBMasuCurSet(masu);
        switch (space->space_type) {
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 12:
        case 15:
            walkNum--;
            func_800DBFBC_shared_board(sys->current_player_index);
            func_800EB97C_shared_board(masu);
            break;
        }
        if (walkNum != 0) {
            switch (space->space_type) {
            case 1:
            case 2:
            case 4:
            case 5:
            case 6:
            case 7:
            case 9:
            case 12:
            case 15:
                HuAudFXPlay(0x101);
                break;
            case 14:
                HuAudFXPlay(0x123);
                break;
            }
        } else {
            switch (space->space_type) {
            case 4:
            case 6:
                HuAudFXPlay(0x108);
                break;
            case 1:
                HuAudFXPlay(0x121);
                break;
            case 2:
                HuAudFXPlay(0x122);
                break;
            case 12:
                HuAudFXPlay(0x124);
                break;
            case 5:
                HuAudFXPlay(0x12F);
                break;
            case 9:
            case 15:
                HuAudFXPlay(0x12E);
                break;
            case 7:
                HuAudFXPlay(0x130);
                break;
            case 14:
                HuAudFXPlay(0x123);
                break;
            }
        }
        MBMasuEventCall(masu, 1);
    }
    MBPlayerMotionSet(-1, -1, 2);
    MBMasuEventCall(masu, 3);
    MBVecForwardSet(&dir);
    func_800ED1E4_shared_board(&player->player_obj->rot, &dir, &player->player_obj->rot, 8);
    func_800F591C_shared_board(sys->current_player_index);
}

/* Blue/red space: colour the player and give or take three coins. */
void func_80106DEC_w10(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    SpaceData *space;

    player = MBPlayerGet(CUR_PLAYER);
    space = MBMasuGet(MBMasuLinkMasuIdGet(player->clink, player->cidx));
    MBPlayerMasuColorSet(CUR_PLAYER, space->space_type);
    MBStatusColorSet(sys->current_player_index, player->color);
    switch (space->space_type) {
    case 1:
        MBCoinChangeCreate(sys->current_player_index, 3);
        MBCoinTakeCreate(sys->current_player_index, 3);
        HuPrcSleep(30);
        break;
    case 2:
        MBCoinChangeCreate(sys->current_player_index, -3);
        MBCoinTakeCreate(sys->current_player_index, -3);
        HuPrcSleep(30);
        break;
    }
}

void func_80106ED8_w10(UnkMBGuideData *guide, s32 mess) {
    func_8005B43C_main(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
    func_800EE614_shared_board(guide->amount);
    func_80060EA8_main(guide->amount, 1);
    func_8005D294_main(guide->amount);
    HuPrcVSleep();
}

void func_80106F40_w10(UnkMBGuideData *guide, s32 mess) {
    func_8005B43C_main(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
}

void func_80106F7C_w10(UnkMBGuideData *guide, s32 mess) {
    func_8005B43C_main(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
    while (func_8005E0C0_main(guide->amount) != 0) {
        HuPrcVSleep();
    }
}

void func_80106FE0_w10(UnkMBGuideData *guide) {
    func_800EE614_shared_board(guide->amount);
    func_80060EA8_main(guide->amount, 1);
    func_8005D294_main(guide->amount);
    HuPrcVSleep();
}

void func_80107028_w10(UnkMBGuideData *guide, s32 mess) {
    func_8005FE54_main(guide->amount, 15);
    func_8005F744_main(-1, -1, -1, -1);
    func_8005B43C_main(guide->amount, mess, -1, -1);
    while (func_8005E0C0_main(guide->amount) != 0) {
        HuPrcVSleep();
    }
    func_8005F904_main();
}

void func_801070B8_w10(UnkMBGuideData *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    MBMotionSet(guide->obj, 0, 0);
    HuPrcSleep(3);
    while (MBMotionCheck(guide->obj) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(guide->obj, -1, 2);
}

#ifdef NON_MATCHING
// board h1: masked 0; raw residue is the register allocation (guide s1/step s2 in retail)
/* Slide the guide window from its x position to x over 14 frames. */
void func_8010714C_w10(UnkMBGuideData *guide, s16 x) {
    s32 i;
    s32 step;
    s16 start = guide->spriteGroup;
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.5f;
    step = (x - start) / 14;
    for (i = 0; i < 14; i++) {
        MBGuidePosSet(guide, guide->spriteGroup + step, 0);
        HuPrcVSleep();
    }
    MBGuidePosSet(guide, x, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010714C_w10);
#endif

/* Motion player: plays the motion requested through func_80107344_w10 (-2 = default). */
void func_80107228_w10(void) {
    Object **objp = HuPrcCurrentGet()->user_data;
    s16 req;

    while (1) {
        HuPrcVSleep();
        if (D_8010B8FC_w10 == -1) {
            continue;
        }
        if (D_8010B8FC_w10 == -2) {
            D_8010B8FC_w10 = -1;
            MBMotionShiftSet(*objp, -1, 0, 10, 0);
        } else {
            MBMotionShiftSet(*objp, D_8010B8FC_w10, 0, 10, 0);
        }
        req = D_8010B8FC_w10;
        D_8010B8FC_w10 = -1;
        while (MBMotionCheck(*objp) == 0 && D_8010B8FC_w10 == -1) {
            HuPrcVSleep();
        }
        switch (req) {
        case 1:
            MBMotionSet(*objp, 3, 2);
            break;
        case 2:
            MBMotionSet(*objp, 4, 2);
            break;
        default:
            MBMotionSet(*objp, -1, 2);
            break;
        }
    }
}

void func_80107344_w10(s16 req) {
    D_8010B8FC_w10 = req;
}

void func_80107350_w10(omObjData *obj) {
    D_8010BA68_w10->coords.y = -sindf(obj->rot.x) * 3.0f;
    D_8010BA6C_w10->coords.y = -sindf(obj->rot.x) * 3.0f;
    obj->rot.x += 3.0f;
}

void func_801073C8_w10(omObjData *obj) {
    D_8010BA70_w10->coords.y = sindf(obj->rot.x) * 3.0f;
    D_8010BA74_w10->coords.y = sindf(obj->rot.x) * 3.0f;
    obj->rot.x += 10.0f;
}

/* Lower two models onto the current player with an effect, bob them until told to stop
 * (*status != 1), then raise and delete them; *status = 3 when done. */
void func_80107444_w10(void) {
    s32 effect;
    omObjData *bob;
    GW_PLAYER *player;
    s32 *status;

    status = HuPrcCurrentGet()->user_data;
    player = MBPlayerGet(CUR_PLAYER);

    D_8010BA68_w10 = MBModelCreate(9, NULL);
    D_8010BA6C_w10 = MBModelFileCreate(0x1301C8, -1, 1.0f, 0.0f, NULL);
    effect = func_8000CED8_main(0xB0004, 0xAA9);
    HuAudFXPlay(0x119);
    func_8001C8A8_main(effect, 1);
    func_8000CD00_main(effect, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 15.0f);
    MBModelTempAllocFree(D_8010BA68_w10);
    D_8010BA68_w10->flags |= 1;
    MBModelTempAllocFree(D_8010BA6C_w10);
    HuVecCopy3F(&D_8010BA68_w10->coords, &player->player_obj->coords);
    HuVecCopy3F(&D_8010BA6C_w10->coords, &player->player_obj->coords);
    D_8010BA68_w10->velocity.x = 120.0f;
    D_8010BA6C_w10->velocity.x = 120.0f;
    while (D_8010BA68_w10->velocity.x > 50.0f) {
        func_8000CFA4_main(effect, D_8010BA68_w10->coords.x, D_8010BA68_w10->velocity.x - 10.0f,
                           D_8010BA68_w10->coords.z);
        HuPrcVSleep();
        D_8010BA68_w10->velocity.x -= 4.0f;
        D_8010BA6C_w10->velocity.x -= 4.0f;
    }
    bob = omAddObj(500, 0, 0, -1, func_80107350_w10);
    bob->rot.x = 180.0f;
    *status = 1;
    HuPrcVSleep();
    while (*status == 1) {
        HuPrcVSleep();
    }
    while (D_8010BA68_w10->velocity.x < 120.0f) {
        func_8000CFA4_main(effect, D_8010BA68_w10->coords.x, D_8010BA68_w10->velocity.x - 10.0f,
                           D_8010BA68_w10->coords.z);
        HuPrcVSleep();
        D_8010BA68_w10->velocity.x += 4.0f;
        D_8010BA6C_w10->velocity.x += 4.0f;
    }
    *status = 3;
    func_8000D044_main(effect);
    MBModelKill(D_8010BA68_w10);
    MBModelKill(D_8010BA6C_w10);
    omDelObj(bob);
    omDelPrcObj(NULL);
}

/* As func_80107444_w10 with the other model pair, effect and sound. */
void func_80107780_w10(void) {
    s32 effect;
    omObjData *bob;
    GW_PLAYER *player;
    s32 *status;

    status = HuPrcCurrentGet()->user_data;
    player = MBPlayerGet(CUR_PLAYER);

    D_8010BA68_w10 = MBModelCreate(0x39, NULL);
    D_8010BA6C_w10 = MBModelFileCreate(0x130203, -1, 1.0f, 0.0f, NULL);
    effect = func_8000CED8_main(0xB0005, 0xAA9);
    HuAudFXPlay(0x11A);
    func_8001C8A8_main(effect, 1);
    func_8000CD00_main(effect, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 15.0f);
    MBModelTempAllocFree(D_8010BA68_w10);
    D_8010BA68_w10->flags |= 1;
    MBModelTempAllocFree(D_8010BA6C_w10);
    HuVecCopy3F(&D_8010BA68_w10->coords, &player->player_obj->coords);
    HuVecCopy3F(&D_8010BA6C_w10->coords, &player->player_obj->coords);
    D_8010BA68_w10->velocity.x = 120.0f;
    D_8010BA6C_w10->velocity.x = 120.0f;
    while (D_8010BA68_w10->velocity.x > 50.0f) {
        func_8000CFA4_main(effect, D_8010BA68_w10->coords.x, D_8010BA68_w10->velocity.x - 10.0f,
                           D_8010BA68_w10->coords.z);
        HuPrcVSleep();
        D_8010BA68_w10->velocity.x -= 4.0f;
        D_8010BA6C_w10->velocity.x -= 4.0f;
    }
    bob = omAddObj(500, 0, 0, -1, func_80107350_w10);
    bob->rot.x = 180.0f;
    *status = 1;
    HuPrcVSleep();
    while (*status == 1) {
        HuPrcVSleep();
    }
    while (D_8010BA68_w10->velocity.x < 120.0f) {
        func_8000CFA4_main(effect, D_8010BA68_w10->coords.x, D_8010BA68_w10->velocity.x - 10.0f,
                           D_8010BA68_w10->coords.z);
        HuPrcVSleep();
        D_8010BA68_w10->velocity.x += 4.0f;
        D_8010BA6C_w10->velocity.x += 4.0f;
    }
    *status = 3;
    func_8000D044_main(effect);
    MBModelKill(D_8010BA68_w10);
    MBModelKill(D_8010BA6C_w10);
    omDelObj(bob);
    omDelPrcObj(NULL);
}

/* Grow two models in from above the current player, bob them until *status != 1, then
 * lift them away; *status = 3 when done. */
void func_80107ABC_w10(void) {
    s32 *status = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    omObjData *bob;

    D_8010BA70_w10 = MBModelCreate(12, NULL);
    Hu3DModelScaleSet(D_8010BA70_w10->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    func_8001FDE8_main(D_8010BA70_w10->omObj1->model[0]);
    D_8010BA70_w10->flags |= 1;
    D_8010BA74_w10 = MBModelCreate(0x1F, NULL);
    Hu3DModelScaleSet(D_8010BA74_w10->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&D_8010BA70_w10->coords, &player->player_obj->coords);
    HuVecCopy3F(&D_8010BA74_w10->coords, &player->player_obj->coords);
    D_8010BA70_w10->velocity.x = 120.0f;
    D_8010BA74_w10->velocity.x = 122.0f;
    while (D_8010BA70_w10->velocity.x > 30.0f) {
        HuPrcVSleep();
        D_8010BA70_w10->velocity.x -= 2.0f;
        D_8010BA74_w10->velocity.x -= 2.0f;
    }
    bob = omAddObj(500, 0, 0, -1, func_801073C8_w10);
    bob->rot.x = 180.0f;
    *status = 1;
    HuPrcVSleep();
    while (*status == 1) {
        HuPrcVSleep();
    }
    while (D_8010BA70_w10->velocity.x < 120.0f) {
        HuPrcVSleep();
        D_8010BA70_w10->velocity.x += 2.0f;
        D_8010BA74_w10->velocity.x += 2.0f;
    }
    *status = 3;
    MBModelKill(D_8010BA70_w10);
    MBModelKill(D_8010BA74_w10);
    omDelObj(bob);
    omDelPrcObj(NULL);
}

/* Lower one model onto the current player and orbit it until *status != 1, then lift it. */
void func_80107D64_w10(void) {
    s32 *status = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    Process *orbit;

    D_8010BA68_w10 = MBModelCreate(0x3E, NULL);
    MBModelTempAllocFree(D_8010BA68_w10);
    HuVecCopy3F(&D_8010BA68_w10->coords, &player->player_obj->coords);
    D_8010BA68_w10->velocity.x = 100.0f;
    do {
        D_8010BA68_w10->velocity.x -= 2.0f;
        HuPrcVSleep();
    } while (D_8010BA68_w10->velocity.x >= 30.0f);
    orbit = func_800EDB98_shared_board(D_8010BA68_w10, 5.0f, 2.0f);
    *status = 1;
    HuPrcVSleep();
    while (*status == 1) {
        HuPrcVSleep();
    }
    omDelPrcObj(orbit);
    while (D_8010BA68_w10->velocity.x < 100.0f) {
        D_8010BA68_w10->velocity.x += 2.0f;
        HuPrcVSleep();
    }
    *status = 3;
    MBModelKill(D_8010BA68_w10);
    omDelPrcObj(NULL);
}

/* Pop up a model (and its motion partner) at space 0x2B, run its motion, wait until
 * *status != 1, then play the closing motion and shrink both away; *status = 3. */
void func_80107F0C_w10(void) {
    s32 *status = HuPrcCurrentGet()->user_data;
    u8 model = (D_8010B918_w10 != 0) ? 0x31 : 0x30;
    Object *base;
    Object *top;
    f32 angle;
    f32 scale;

    HuAudFXPlay(0x114);
    base = MBModelCreate(model, NULL);
    MBModelTempAllocFree(base);
    HuVecCopyXYZ(&base->rot, 0.0f, 0.0f, 1.0f);
    base->scale.y = 0.0f;
    MBMotionSet(base, -1, 1);
    func_800D9A40_shared_board(base);
    HuVecCopy3F(&base->coords, &MBMasuGet(0x2B)->coords);
    if (D_8010B918_w10 != 0) {
        top = MBModelCreate(0x39, D_8010B908_w10);
    } else {
        top = MBModelCreate(0x1B, D_8010B900_w10);
    }
    MBModelTempAllocFree(top);
    HuVecCopy3F(&top->rot, &base->rot);
    HuVecCopy3F(&top->coords, &base->coords);
    top->scale.z = 1.2f;
    top->scale.x = 1.2f;
    top->scale.y = 1.2f;
    MBModelDispOff(top);

    scale = 1.0f / sindf(50.0f);
    for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
        base->scale.y = sindf(angle) * scale;
        base->scale.x = (sindf(angle) * scale * 0.2f) + 0.8f;
        base->scale.z = (sindf(angle) * scale * 0.2f) + 0.8f;
        HuPrcVSleep();
    }
    for (; 50.0f < angle; angle -= 11.25f) {
        base->scale.y = sindf(angle) * scale;
        base->scale.x = (sindf(angle) * scale * 0.2f) + 0.8f;
        base->scale.z = (sindf(angle) * scale * 0.2f) + 0.8f;
        HuPrcVSleep();
    }
    base->scale.z = 1.0f;
    base->scale.x = 1.0f;
    base->scale.y = 1.0f;
    func_800D9A40_shared_board(top);

    MBMotionSet(base, -1, 0);
    func_8001C92C_main(base->omObj1->model[0], 1.2f);
    while (MBMotionCheck(base) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(top, 0, 0);
    HuAudFXPlay((D_8010B918_w10 != 0) ? 0x2A0 : 0x298);
    while (MBMotionCheck(top) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(top, -1, 2);
    *status = 1;
    HuPrcVSleep();
    while (*status == 1) {
        HuPrcVSleep();
    }

    HuAudFXPlay(0x115);
    MBMotionSet(base, -1, 4);
    func_8001C92C_main(base->omObj1->model[0], 1.2f);
    func_8001C6A8_main(base->omObj1->model[0],
                       (f32)D_800CCF58_main[HmfModelData[base->omObj1->model[0]].unk02].unk02);
    while (func_800D9E80_shared_board(base) == 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(top);

    scale = 1.0f / sindf(50.0f);
    for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
        base->scale.y = sindf(angle) * scale;
        base->scale.x = (sindf(angle) * scale * 0.2f) + 0.8f;
        base->scale.z = (sindf(angle) * scale * 0.2f) + 0.8f;
        HuPrcVSleep();
    }
    for (angle = 90.0f; 0.0f < angle; angle -= 11.25f) {
        base->scale.y = sindf(angle) * scale;
        base->scale.x = (sindf(angle) * scale * 0.2f) + 0.8f;
        base->scale.z = (sindf(angle) * scale * 0.2f) + 0.8f;
        HuPrcVSleep();
    }
    base->scale.y = 0.0f;
    base->scale.x = 0.0f;
    base->scale.z = 0.0f;
    MBModelKill(base);
    MBModelKill(top);
    *status = 3;
    omDelPrcObj(NULL);
}

// board h2
#include "../ovl_80_shared_board/ovl_80.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/1063F0.h"
#include "../ovl_80_shared_board/106640.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/10AD50.h"
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
#include "../ovl_80_shared_board/F2910.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/F9DE0.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/FFB10.h"

void func_80105B70_w10(void);
void func_80105C28_w10(void);
void func_80105D6C_w10(void);
void func_80106574_w10(void);
void func_80109444_w10(void);
s16 func_8010B12C_w10(s32 padNo);
void func_8010B434_w10(void);
void func_80108F28_w10(void);
void func_80106ED8_w10(UnkMBGuideData *guide, s32 mesNo);
void func_80106F40_w10(UnkMBGuideData *guide, s32 mesNo);
void func_80106FE0_w10(UnkMBGuideData *guide);
extern event_table_entry D_8010B8B0_w10[];
extern u8 D_800CC0BA_main;
extern s32 D_8010BA20_w10;
extern Process *D_8010BA28_w10;
extern Object *D_8010BA90_w10;
extern s32 D_8010BA94_w10;

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801084CC_w10);

// Spins a model above space 0x2E while D_8010BA94_w10 is set.
void func_80108F28_w10(void) {
    Object *obj;

    D_8010BA94_w10 = 0;
    obj = MBModelCreate(0x4E, NULL);
    D_8010BA90_w10 = obj;
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x2E)->coords);
    HuVecCopyXYZ(&obj->rot, 0.0f, 0.0f, -1.0f);
    obj->velocity.x = 15.0f;
    while (D_8010BA94_w10 == 0) {
        HuPrcVSleep();
    }
    while (D_8010BA94_w10 != 0) {
        obj->omObj1->rot.z -= 15.0f;
        if (obj->omObj1->rot.z < 0.0f) {
            obj->omObj1->rot.z += 360.0f;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109050_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109444_w10);

// Tutorial: dice-roll explanation (zoom in, roll, hit the block, zoom out).
void func_8010AF68_w10(UnkMBGuideData *guide) {
    Process *curProc;
    Process *proc;
    GW_SYSTEM *system = &GwSystem;

    curProc = HuPrcCurrentGet();
    HuPrcChildLink(curProc, MBCameraZoomMotStart(1.6f));
    proc = func_800DDDD4_shared_board(system->current_player_index);
    func_800DE858_shared_board();
    HuPrcChildWait();
    func_80106F40_w10(guide, 0x1617);
    func_800DE868_shared_board();
    while (!func_800DE84C_shared_board()) {
        HuPrcVSleep();
    }
    func_80106FE0_w10(guide);
    func_800DE868_shared_board();
    HuPrcChildLink(curProc, proc);
    HuPrcChildWait();
    proc = func_800DE7E4_shared_board(system->current_player_index);
    func_800DE858_shared_board();
    func_800DE868_shared_board();
    while (!func_800DE84C_shared_board()) {
        HuPrcVSleep();
    }
    HuPrcChildLink(curProc, proc);
    HuPrcChildWait();
    func_80106ED8_w10(guide, 0x1618);
    proc = func_800DE414_shared_board(system->current_player_index, 0);
    func_800DE858_shared_board();
    func_800DE868_shared_board();
    while (!func_800DE84C_shared_board()) {
        HuPrcVSleep();
    }
    HuPrcChildLink(curProc, proc);
    HuPrcChildWait();
    func_80106ED8_w10(guide, 0x1619);
    HuPrcChildLink(curProc, MBCameraZoomMotStart(1.3f));
    HuPrcChildWait();
    HuPrcSleep(1);
}

// Tutorial pause menu: dims the screen, asks whether to quit; true when the player chose to quit.
s16 func_8010B12C_w10(s32 padNo) {
    s16 size[2];
    UnkBoard8 *dim;
    UnkBoard8 *frame;
    void *data;
    s16 winId;
    s16 choice;

    func_8004A9DC_main(0x60);
    dim = func_800F2C48_shared_board(1, 0);
    data = DataRead(0x13025D);
    dim->model[0] = func_80055810_main(data);
    func_80055024_main(dim->spriteGroup, 0, dim->model[0], 0);
    HuSprPriSet(dim->spriteGroup, 0, 9);
    HuSprAttrSet(dim->spriteGroup, 0, 0x1000);
    func_80054904_main(dim->spriteGroup, 0, 160, 120);
    HuSprScaleSet(dim->spriteGroup, 0, 40.0f, 30.0f);
    func_80055484_main(dim->spriteGroup, 0, 0, 0, 0, 0xC0);
    DataClose(data);
    frame = func_800F2C48_shared_board(2, 0);
    data = DataRead(0x130009);
    frame->model[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(frame->spriteGroup, 0, frame->model[0], 0);
    HuSprPriSet(frame->spriteGroup, 0, 8);
    HuSprAttrSet(frame->spriteGroup, 0, 0x1000);
    func_80054904_main(frame->spriteGroup, 0, 158, 120);
    func_80055420_main(frame->spriteGroup, 0, 0x89, 0xCA, 0xB2);
    func_80060394_main(1, size, 0x1633);
    winId = func_8005A968_main(0x49, 0x4B, size[0], size[1], 0, 2);
    func_8005BE30_main(winId, 5);
    func_8005BEE0_main(winId, 0);
    func_80060144_main(winId);
    func_8005C060_main(winId, 7, 0, 0, 0xE0);
    func_8005C060_main(winId, 0, 0x89, 0xCA, 0xB2);
    func_8005C060_main(winId, 4, 0, 0x80, 0);
    func_8005FBF8_main(winId, 0x89, 0xCA, 0xB2);
    func_8005B43C_main(winId, 0x1633, -1, -1);
    func_8005BDFC_main(winId, 0);
    while (func_8005E0C0_main(winId) != 0) {
        HuPrcVSleep();
    }
    func_8005FE54_main(winId, 1 << padNo);
    choice = func_8005E1D8_main(winId, 0, 0);
    func_8005F364_main(winId);
    func_8004A9DC_main(0x7F);
    func_800F2CA4_shared_board(dim);
    func_800F2CA4_shared_board(frame);
    return choice == 1;
}

// Pause watcher: Start opens the tutorial pause menu; quitting leaves the board.
void func_8010B434_w10(void) {
    Vec2f sp10;
    s32 curPlayerNo;
    s32 i;

    D_8010BA20_w10 = 0;
    while (1) {
        HuPrcVSleep();
        if (WipeStatGet() != 0) {
            continue;
        }
        if (D_800CC0BA_main == 3) {
            continue;
        }
        curPlayerNo = (s16)MBPlayerTurnGet();
        for (i = 0; i < 4; i++) {
            if (!(D_800C9520_main[i] & START_BUTTON)) {
                continue;
            }
            if (D_8010BA20_w10 != 0) {
                continue;
            }
            func_800DE874_shared_board(curPlayerNo);
            MBCameraPos2DGet(&sp10);
            MBCameraPos2DSet(&sp10);
            D_800CB99C_main = 1;
            func_80049FB8_main();
            HmfPauseF = 1;
            if (func_8010B12C_w10(i) != 0) {
                HuAudSeqFadeOut(0x5A);
                WipeCreateOut(0, 0x10);
                HuPrcSleep(0x11);
                omDelPrcObj(D_8010BA28_w10);
                MBExit();
                func_800F884C_shared_board();
                omOvlReturnEx(1);
                omOvlKill();
                HuPrcVSleep();
            }
            HmfPauseF = 0;
            func_8004A0E0_main();
            D_800CB99C_main = 0;
            func_800DE8D8_shared_board(curPlayerNo);
            break;
        }
    }
}

// Board setup: lights, board objects, ten coins each, event table, then the tutorial processes.
void func_8010B5A4_w10(void) {
    Vec sp10;
    SpaceData *space;
    GW_PLAYER *player;
    s32 i;

    Hu3DCamInit(2);
    omInitObjMan(0x50, 0x28);
    func_8004A208_main();
    HmfLightMaxSet(1);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -100.0f, 100.0f, 300.0f);
    MBObjectSetup(0x15, 0x240, 0, 0);
    space = MBMasuGet(0x2A);
    MBVecDirGet(&space->coords, &MBMasuGet(0x2B)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->coin = 10;
    }
    func_80105B70_w10();
    func_80105C28_w10();
    func_80105D6C_w10();
    MBMasuEventTblAdd(D_8010B8B0_w10);
    for (i = 0; i < 4; i++) {
        s16 masuID;
        player = MBPlayerGet(i);
        masuID = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        MBPlayerPosMasuSet(i, masuID);
        MBPlayerForwardSet(i);
    }
    func_800EBDAC_shared_board();
    func_800E6FBC_shared_board();
    func_800E9730_shared_board(1.0f);
    MBCameraSpeedSet(-1.0f);
    MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
    omAddPrcObj(func_80109444_w10, 0xEFFF, 0, 0);
    omAddPrcObj(func_80106574_w10, 0x1005, 0, 0);
    omPrcSetStatBit(omAddPrcObj(func_8010B434_w10, 0x1005, 0, 0), 0x80);
    omAddPrcObj(func_80108F28_w10, 0x4800, 0, 0);
}
