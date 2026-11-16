#include "common.h"
#include "game/board.h"
#include "game/object.h"
#include "malloc.h"
#include "game/sprite.h"
#include "game/data.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "game/wipe.h"
#include "../ovl_80_shared_board/1063F0.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/EE660.h"
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

/* Three-sprite panel: frame, tinted backing, picture. */
typedef struct W10SprWork {
    /* 0x00 */ s16 group;
    /* 0x02 */ s16 spr[3];
} W10SprWork; // size 0x8

void func_800461B4_main(s16 model);
void func_80105DC4_w10(void);
void func_80105E08_w10(void);
void func_800DCD64_shared_board(s32 arg0, s32 arg1);
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

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106908_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106DEC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106ED8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106F40_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106F7C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106FE0_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107028_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801070B8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010714C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107228_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107344_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107350_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801073C8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107444_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107780_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107ABC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107D64_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107F0C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801084CC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80108F28_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109050_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109444_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010AF68_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B12C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B434_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B5A4_w10);
