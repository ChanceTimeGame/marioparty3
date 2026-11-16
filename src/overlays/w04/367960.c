#include "common.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/FA250.h"

void func_801183D4_w04(void);
void func_801191B8_w04(void);
void func_8011A4E0_w04(s32);

// board q1
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

extern s32 D_8011E038_w04;
extern Object *D_8011E03C_w04;

void func_80116024_w04(s16 *links, s16 *spaces, void **arrows);
extern s16 D_8011C1B0_w04[];
extern s16 D_8011C1C4_w04[];
extern void *D_8011BCF0_w04[];
extern s16 D_8011C1F8_w04[];
extern s16 D_8011C20C_w04[];
extern void *D_8011BD38_w04[];
extern s16 D_8011C240_w04[];
extern s16 D_8011C254_w04[];
extern void *D_8011BD68_w04[];
extern s16 D_8011C288_w04[];
extern s16 D_8011C29C_w04[];
extern void *D_8011BDE0_w04[];
extern s16 D_8011C2D0_w04[];
extern s16 D_8011C2E4_w04[];
extern void *D_8011BE28_w04[];
extern s16 D_8011C318_w04[];
extern s16 D_8011C32C_w04[];
extern void *D_8011BE88_w04[];
extern s16 D_8011C360_w04[];
extern s16 D_8011C374_w04[];
extern void *D_8011BF0C_w04[];
extern s16 D_8011B740_w04[];
extern s16 D_8011B750_w04[];
extern s16 D_8011B760_w04[];
extern s16 D_8011B770_w04[];
extern s16 D_8011B780_w04[];
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
    D_8011E038_w04 = 0;
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

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106120_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801064DC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106A3C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106AB0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106B38_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106B94_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106C64_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106CC4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106F58_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107170_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801072A0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107438_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107704_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107724_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107744_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107780_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107828_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107B34_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107BB8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107BE4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107D0C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107D70_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107E1C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107F3C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107F98_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108094_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108200_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108268_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801083D4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108434_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108490_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108558_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108608_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108644_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801086C4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010873C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801087CC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010886C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801088C8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801088FC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108934_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801089B0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108A58_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108AD4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108B4C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108C00_w04);

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

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80109690_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801098A0_w04);

void func_80109CBC_w04(void) {
}

void func_80109CC4_w04(void) {
}

void func_80109CCC_w04(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80109CD4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80109F58_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010A014_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010A054_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010A400_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010AF34_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010AFBC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010B024_w04);

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
