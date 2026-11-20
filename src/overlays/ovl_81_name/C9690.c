#include "common.h"
#include "ovl_81.h"

/* Duel warp: two players swap spaces, or one player warps to a given space or position. */

extern s16 D_800CE1D0_main;
extern s16 D_80102BF0_name_81; /* warping player (swap: first) */
extern s16 D_80102BF2_name_81; /* swap: second player */
extern s16 D_80102BF4_name_81; /* target link */
extern s16 D_80102BF6_name_81; /* target space index */
extern s16 D_80102BF8_name_81; /* back link, or -1 */
extern s16 D_80102BFA_name_81; /* back space index, or -1 */
extern Vec D_80102C00_name_81; /* player target position */
extern Vec D_80102C0C_name_81; /* front partner target position */
extern Vec D_80102C18_name_81; /* back partner target position */

void func_800E890C_name_81(Vec* arg0, s32 arg1);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
void func_800EB6C4_name_81(s16, s16);
void func_800EB7BC_name_81(Vec*);
void func_800EB8B0_name_81(s16, s16);
void func_800EDD50_name_81(Vec*);
void func_800EDDBC_name_81(void);
void func_800EDF48_name_81(void);
void func_800EDF78_name_81(void);
void func_800EE0F4_name_81(s32);
void func_800EE74C_name_81(s32);
void func_800F3B94_name_81(s16, Vec*);

void func_800E18C0_name_81(void) {
    D_80102BF0_name_81 = -1;
    D_80102BF2_name_81 = -1;
}

s32 func_800E18D8_name_81(s32 arg0, s32 arg1) {
    return ((arg1 ^ arg0) << 0x10) != 0;
}

void func_800E18E8_name_81(s16 arg0, s16 arg1) {
    if (arg1 == MBDGetCurrentPlayerIndex()) {
        D_80102BF0_name_81 = arg1;
        D_80102BF2_name_81 = arg0;
        return;
    }
    D_80102BF0_name_81 = arg0;
    D_80102BF2_name_81 = arg1;
}

// decomp-permuter
s32 func_800E1960_name_81(void)
{
  s16 players[2];
  GW_PLAYER *cur;
  s32 i;
  s32 new_var;
  s32 target;
  cur = MBDGetPlayerStruct(-1);
  for (i = 0; i < 2; i++)
  {
    players[i] = i;
  }

  for (i = 0; i < 2; i++)
  {
    target = players[i];
    new_var = cur->turn != target;
    if (new_var && (func_800E18D8_name_81(cur->turn, target) != 0))
    {
      break;
    }
  }

  if (i == 2)
  {
    return 0;
  }
  func_800E18E8_name_81(cur->turn, new_var = target);
  return 1;
}

void func_800E1A24_name_81(void) {
    GW_PLAYER* player1;
    GW_PLAYER* player2;
    GW_PLAYER* playerCopy;
    Object* playerObj;
    Object* playerObjSecond;
    Object* model;
    f32 temp_f0;
    f32 temp_f2;
    s32 i;

    func_800FC888_name_81(0);
    player1 = MBDGetPlayerStruct(D_80102BF0_name_81);
    player2 = MBDGetPlayerStruct(D_80102BF2_name_81);
    player1->stat |= 4;
    player2->stat |= 4;
    playerObj = player1->player_obj;
    playerObjSecond = player2->player_obj;

    HuAudFXPlay(0x1F5);
    model = func_800D8010_name_81(0x1F, NULL);
    func_800D90D0_name_81(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObj->coords);
    func_800FFAE0_name_81(D_80102BF0_name_81, 1);
    for (i = 0; i < 15; i++) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObj->scale.x = temp_f2;
        playerObj->scale.y = temp_f0;
        playerObj->scale.z = temp_f2;
        func_800F3B94_name_81(D_80102BF0_name_81, &playerObj->scale);
        HuPrcVSleep();
    }
    playerObj->scale.x = 0.0f;
    playerObj->scale.y = 0.0f;
    playerObj->scale.z = 0.0f;
    func_800F3B94_name_81(D_80102BF0_name_81, &playerObj->scale);
    HuPrcVSleep();
    playerObj->flags &= ~2;
    func_800D8F0C_name_81(playerObj);
    func_800D8F3C_name_81(model);

    HuAudFXPlay(0x1F5);
    model = func_800D8010_name_81(0x1F, NULL);
    func_800D90D0_name_81(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObjSecond->coords);
    func_800FFAE0_name_81(D_80102BF2_name_81, 1);
    for (i = 0; i < 15; i++) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObjSecond->scale.x = temp_f2;
        playerObjSecond->scale.y = temp_f0;
        playerObjSecond->scale.z = temp_f2;
        func_800F3B94_name_81(D_80102BF2_name_81, &playerObjSecond->scale);
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(model);

    playerCopy = player1;
    D_800CE1D0_main = 0;
    func_800EB8B0_name_81(D_80102BF0_name_81, D_80102BF2_name_81);
    func_800EB6C4_name_81(D_80102BF0_name_81, MBDMasuLinkMasuIdGet(playerCopy->clink, player1->cidx));
    func_800EB6C4_name_81(D_80102BF2_name_81, MBDMasuLinkMasuIdGet(player2->clink, player2->cidx));
    func_800ED214_name_81(D_80102BF0_name_81);
    func_800ED214_name_81(D_80102BF2_name_81);

    HuAudFXPlay(0x1F5);
    model = func_800D8010_name_81(0x1F, NULL);
    func_800D90D0_name_81(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObjSecond->coords);
    func_800FFAE0_name_81(D_80102BF2_name_81, 1);
    for (i = 14; i >= 0; i--) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObjSecond->scale.x = temp_f2;
        playerObjSecond->scale.y = temp_f0;
        playerObjSecond->scale.z = temp_f2;
        func_800F3B94_name_81(D_80102BF2_name_81, &playerObjSecond->scale);
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(model);

    WipeCreateOut(0, 0x10);
    HuPrcSleep(0x10);
    func_800E890C_name_81(&playerObj->coords, 1);
    func_800FCF50_name_81(0, 1);
    func_800FCF50_name_81(1, 1);
    WipeCreateIn(0, 0x10);
    HuPrcSleep(0x10);

    HuAudFXPlay(0x1F5);
    playerObj->flags |= 2;
    func_800D8E88_name_81(playerObj);
    model = func_800D8010_name_81(0x1F, NULL);
    func_800D90D0_name_81(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObj->coords);
    func_800FFAE0_name_81(D_80102BF0_name_81, 1);
    for (i = 14; i >= 0; i--) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObj->scale.x = temp_f2;
        playerObj->scale.y = temp_f0;
        playerObj->scale.z = temp_f2;
        func_800F3B94_name_81(D_80102BF0_name_81, &playerObj->scale);
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(model);
    playerCopy->stat &= ~4;
    player2->stat &= ~4;

    if (D_80102BF0_name_81 != MBDGetCurrentPlayerIndex()) {
        HuPrcSleep(15);
        WipeCreateOut(0, 0x10);
        HuPrcSleep(0x10);
        func_800E890C_name_81(&MBDGetPlayerStruct(-1)->player_obj->coords, 1);
        WipeCreateIn(0, 0x10);
        HuPrcSleep(0x10);
    }
    HuPrcSleep(15);
    func_800EAFC4_name_81(0x1F2E);
    func_800FC888_name_81(1);
    func_800E18C0_name_81();
    omDelPrcObj(NULL);
}

void func_800E1F38_name_81(void) {
    Process* proc;

    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, omAddPrcObj(func_800E1A24_name_81, 0x1003, 0, 0));
    HuPrcChildWait();
}

s16 func_800E1F88_name_81(void) {
    return D_80102BF0_name_81;
}

void func_800E1F94_name_81(void) {
    func_800EE74C_name_81(1);
    HuPrcSleep(-1);
}

void func_800E1FB8_name_81(void) {
    GW_PLAYER* player;
    Object* obj;
    s16 effect;
    s32 i;

    player = MBDGetPlayerStruct(-1);
    effect = func_8000CED8_main(0x110012, 0x2A9);
    func_8001C8A8_main(effect, 1);
    func_8000CD00_main(effect, 1.0f, 30.0f, 1.0f);
    func_8000D018_main(effect, 10.0f);
    for (i = 0; i < 30; i++) {
        obj = player->player_obj;
        func_8000CFA4_main(effect, obj->coords.x, obj->coords.y + 30.0f, obj->coords.z);
        HuPrcVSleep();
    }
    func_8000D044_main(effect);
    omDelPrcObj(NULL);
}

void func_800E209C_name_81(void) {
    GW_PLAYER* player;
    Object* playerObj;
    Object* model;
    Process* proc;
    f32 temp_f0;
    f32 temp_f2;
    s32 i;
    s32 link;
    s32 idx;

    func_800FC888_name_81(0);
    player = MBDGetPlayerStruct(D_80102BF0_name_81);
    player->stat |= 4;
    playerObj = player->player_obj;
    func_800EDD50_name_81(&playerObj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    proc = omAddPrcObj(func_800E1F94_name_81, 0xA, 0, 0);
    HuPrcSleep(0xA);

    HuAudFXPlay(0x1F7);
    model = func_800D8010_name_81(0x1F, NULL);
    func_800D90D0_name_81(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObj->coords);
    func_800FFAE0_name_81(D_80102BF0_name_81, 1);
    for (i = 0; i < 15; i++) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObj->scale.x = temp_f2;
        playerObj->scale.y = temp_f0;
        playerObj->scale.z = temp_f2;
        func_800F3B94_name_81(D_80102BF0_name_81, &playerObj->scale);
        HuPrcVSleep();
    }
    playerObj->scale.x = 0.0f;
    playerObj->scale.y = 0.0f;
    playerObj->scale.z = 0.0f;
    func_800F3B94_name_81(D_80102BF0_name_81, &playerObj->scale);
    HuPrcVSleep();
    playerObj->flags &= ~2;
    func_800D8F0C_name_81(playerObj);
    func_800D8F3C_name_81(model);

    player->clink = player->nlink = player->blink = (s8)D_80102BF4_name_81;
    player->cidx = (s8)D_80102BF6_name_81;
    player->nidx = (s8)D_80102BF6_name_81 + 1;
    player->bidx = (s8)D_80102BF6_name_81 - 1;
    player->nnidx = player->nnlink = -1;
    if (D_80102BF8_name_81 != -1) {
        player->blink = (s8)D_80102BF8_name_81;
    }
    if (D_80102BFA_name_81 != -1) {
        player->bidx = (s8)D_80102BFA_name_81;
    }
    player->rev = 0;
    D_800CE1D0_main = 0;
    func_800EB6C4_name_81(D_80102BF0_name_81, MBDMasuLinkMasuIdGet(player->clink, player->cidx));
    if ((GwSystem.current_board_index == 5) && (GwSystem.boardData.halfWordBytes[0] != 0)) {
        player->rev = 1;
        link = player->nlink;
        idx = player->nidx;
        player->nlink = player->blink;
        player->nidx = player->bidx;
        player->blink = link;
        player->bidx = idx;
    }
    WipeCreateOut(0, 0x10);
    HuPrcSleep(0x10);
    omDelPrcObj(proc);
    func_800EDF78_name_81();
    func_800EDDBC_name_81();
    func_800E890C_name_81(&playerObj->coords, 1);
    func_800FCF50_name_81(0, 1);
    func_800FCF50_name_81(1, 1);
    WipeCreateIn(0, 0x10);
    HuPrcSleep(0x10);
    omAddPrcObj(func_800E1FB8_name_81, 0xA, 0, 0);
    HuPrcSleep(0xA);

    HuAudFXPlay(0x1F8);
    playerObj->flags |= 2;
    func_800D8E88_name_81(playerObj);
    model = func_800D8010_name_81(0x1F, NULL);
    func_800D90D0_name_81(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObj->coords);
    func_800FFAE0_name_81(D_80102BF0_name_81, 1);
    for (i = 14; i >= 0; i--) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObj->scale.x = temp_f2;
        playerObj->scale.y = temp_f0;
        playerObj->scale.z = temp_f2;
        func_800F3B94_name_81(D_80102BF0_name_81, &playerObj->scale);
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(model);
    player->stat &= ~4;
    HuPrcSleep(15);
    func_800FC888_name_81(1);
    func_800E18C0_name_81();
    omDelPrcObj(NULL);
}

void func_800E24AC_name_81(s16 link, s16 idx, s16 backLink, s16 backIdx) {
    Process* proc;

    D_80102BF0_name_81 = MBDGetCurrentPlayerIndex();
    D_80102BF4_name_81 = link;
    D_80102BF6_name_81 = idx;
    D_80102BF8_name_81 = backLink;
    D_80102BFA_name_81 = backIdx;
    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, omAddPrcObj(func_800E209C_name_81, 0x1003, 0, 0));
    HuPrcChildWait();
}

void func_800E2550_name_81(void) {
    GW_PLAYER* player;
    Object* playerObj;
    Object* model;
    Object* partner;
    f32 temp_f0;
    f32 temp_f2;
    s32 i;

    player = MBDGetPlayerStruct(D_80102BF0_name_81);
    player->stat |= 4;
    playerObj = player->player_obj;
    HuAudFXPlay(0x1F7);
    model = func_800D8010_name_81(0x1F, NULL);
    func_800D90D0_name_81(model, -1, 0);
    playerObj->flags &= ~2;
    HuVecCopy3F(&model->coords, &playerObj->coords);
    for (i = 0; i < 15; i++) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObj->scale.x = temp_f2;
        playerObj->scale.y = temp_f0;
        playerObj->scale.z = temp_f2;
        func_800F3B94_name_81(D_80102BF0_name_81, &playerObj->scale);
        HuPrcVSleep();
    }
    playerObj->scale.x = 0.0f;
    playerObj->scale.y = 0.0f;
    playerObj->scale.z = 0.0f;
    func_800F3B94_name_81(D_80102BF0_name_81, &playerObj->scale);
    HuPrcVSleep();
    func_800D8F0C_name_81(playerObj);
    func_800D8F3C_name_81(model);

    HuVecCopy3F(&playerObj->coords, &D_80102C00_name_81);
    func_800EB7BC_name_81(&playerObj->rot);
    partner = MBDGetPlayerPartnerRef(D_80102BF0_name_81, PARTNER_FRONT);
    if (partner != NULL) {
        HuVecCopy3F(&partner->coords, &D_80102C0C_name_81);
        func_800EB7BC_name_81(&partner->rot);
    }
    partner = MBDGetPlayerPartnerRef(D_80102BF0_name_81, PARTNER_BACK);
    if (partner != NULL) {
        HuVecCopy3F(&partner->coords, &D_80102C18_name_81);
        func_800EB7BC_name_81(&partner->rot);
    }
    HuPrcVSleep();

    HuAudFXPlay(0x1F8);
    playerObj->flags |= 2;
    func_800D8E88_name_81(playerObj);
    model = func_800D8010_name_81(0x1F, NULL);
    func_800D90D0_name_81(model, -1, 0);
    HuVecCopy3F(&model->coords, &playerObj->coords);
    for (i = 14; i >= 0; i--) {
        temp_f0 = (f32)i / 15.0f;
        temp_f2 = 1.0f - temp_f0;
        temp_f0 += 1.0f;
        playerObj->scale.x = temp_f2;
        playerObj->scale.y = temp_f0;
        playerObj->scale.z = temp_f2;
        func_800F3B94_name_81(D_80102BF0_name_81, &playerObj->scale);
        HuPrcVSleep();
    }
    func_800D8F3C_name_81(model);
    player->stat &= ~4;
    HuPrcSleep(15);
    func_800E18C0_name_81();
    omDelPrcObj(NULL);
}

void func_800E27D4_name_81(s16 playerIndex, Vec* pos, Vec* frontPos, Vec* backPos) {
    Process* proc;

    D_80102BF0_name_81 = playerIndex;
    HuVecCopy3F(&D_80102C00_name_81, pos);
    HuVecCopy3F(&D_80102C0C_name_81, frontPos);
    HuVecCopy3F(&D_80102C18_name_81, backPos);
    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, omAddPrcObj(func_800E2550_name_81, 0x1003, 0, 0));
    HuPrcChildWait();
}
