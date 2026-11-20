#include "common.h"
#include "game/board.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106640.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/1006F0.h"

// event e5: the last-5-turns event (a host picks a player for a +10 / -10 coin change)
void func_800EC5B4_shared_board(s16 arg0, s32 arg1);
void func_800EE700_shared_board(void);
void func_800EE740_shared_board(void);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_801073B0_last5(void);
void func_80107450_last5(void);
void func_80105CD4_last5(omObjData *obj);
void func_80105F9C_last5(void);
void func_801066E0_last5(omObjData *obj);
void func_80106100_last5(void);
void func_80106768_last5(void);
void func_80107178_last5(void);
void func_801072B0_last5(omObjData *obj);
void func_801072FC_last5(omObjData *obj);
void func_80107358_last5(void);
void func_80107384_last5(void);

extern Vec D_80107480_last5;
extern Vec D_8010748C_last5;
extern Vec D_80107498_last5[2];
extern Vec D_801074B0_last5;
extern u32 D_801074BC_last5[2];
extern u32 D_801074C4_last5[2];
extern u32 D_801074CC_last5[2];
extern u32 D_801074D4_last5[3];
extern u32 D_801074E0_last5[2];
extern u8 D_801074E8_last5[4];
extern u8 D_801074EC_last5[4];
extern s32 D_801074F0_last5[4];
extern s32 D_80107500_last5;
extern s32 D_80107504_last5;

extern u8 D_80107550_last5;
extern s32 D_80107558_last5[4]; /* rank of each player */
extern s32 D_80107568_last5[4]; /* player of each rank */
extern UnkBoard8 *D_80107578_last5;
extern Object *D_8010757C_last5;

void func_801059A0_last5(void) {
    s32 i;

    D_80107550_last5 = GwSystem.current_board_index;
    omInitObjMan(50, 50);
    func_801073B0_last5();
    func_80107358_last5();
    func_800D95C4_shared_board(1000.0f);
    func_8005A6B0_main();
    func_800F453C_shared_board();
    func_800F7108_shared_board();
    for (i = 0; i < 4; i++) {
        MBStatusPosSet(i, 30, -50);
    }
    omAddPrcObj(func_80107178_last5, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801072FC_last5);
}

s16 func_80105A68_last5(s16 *size, s16 x, s16 y) {
    return func_80061188_main(-1, x, y, size[0], size[1], 0);
}

void func_80105AAC_last5(s16 win) {
    D_800CC69C_main[win].unk20 = 1;
    HuPrcVSleep();
    func_800EE2C0_shared_board(win);
}

s16 func_80105B04_last5(s32 mess, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, s16 x, s16 y) {
    s16 size[2];
    s16 win;

    if (arg1 != 0) {
        func_8006022C_main(arg1, 0);
    }
    if (arg2 != 0) {
        func_8006022C_main(arg2, 1);
    }
    if (arg3 != 0) {
        func_8006022C_main(arg3, 2);
    }
    if (arg4 != 0) {
        func_8006022C_main(arg4, 3);
    }
    if (arg5 != 0) {
        func_8006022C_main(arg5, 4);
    }
    func_80060394_main(1, size, mess);
    win = func_80105A68_last5(size, x, y);
    if (arg1 != 0) {
        func_8005B6BC_main(win, arg1, 0);
    }
    if (arg2 != 0) {
        func_8005B6BC_main(win, arg2, 1);
    }
    if (arg3 != 0) {
        func_8005B6BC_main(win, arg3, 2);
    }
    if (arg4 != 0) {
        func_8005B6BC_main(win, arg4, 3);
    }
    if (arg5 != 0) {
        func_8005B6BC_main(win, arg5, 4);
    }
    func_8005B43C_main(win, mess, -1, -1);
    func_80061388_main(win);
    func_800EE2C0_shared_board(win);
    return win;
}

void func_80105C9C_last5(s16 win) {
    func_80061A5C_main(win, 0);
    func_8005F364_main(win);
}

void func_80105CD4_last5(omObjData *obj) {
    f32 scale;

    obj->work[0]++;
    obj->rot.x += 30.0f;
    scale = obj->scale.x = sindf(obj->rot.x) + 1.0f;
    HuSprScaleSet(D_80107578_last5->spriteGroup, 1, scale, scale);
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
    if (obj->work[0] > 20) {
        func_80055458_main(D_80107578_last5->spriteGroup, 0, (31 - obj->work[0]) * 25);
        func_80055458_main(D_80107578_last5->spriteGroup, 1, (31 - obj->work[0]) * 25);
    }
}

void func_80105DEC_last5(void) {
    omObjData *obj;
    void *data;

    D_80107578_last5 = func_800F2C48_shared_board(2, 0);
    data = DataRead(0x1301DE);
    D_80107578_last5->model[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80107578_last5->spriteGroup, 0, D_80107578_last5->model[0], 0);
    HuSprPriSet(D_80107578_last5->spriteGroup, 0, 0x11);
    HuSprAttrSet(D_80107578_last5->spriteGroup, 0, 0x1000);
    func_80054904_main(D_80107578_last5->spriteGroup, 0, 160, 100);
    data = DataRead(0x1301DF);
    D_80107578_last5->model[1] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(D_80107578_last5->spriteGroup, 1, D_80107578_last5->model[1], 3);
    HuSprPriSet(D_80107578_last5->spriteGroup, 1, 0x10);
    HuSprAttrSet(D_80107578_last5->spriteGroup, 1, 0x1000);
    func_80054904_main(D_80107578_last5->spriteGroup, 1, 160, 100);
    obj = omAddObj(0x1000, 0, 0, -1, func_80105CD4_last5);
    HuPrcSleep(30);
    omDelObj(obj);
    func_800F2CA4_shared_board(D_80107578_last5);
    HuPrcSleep(10);
}

void func_80105F9C_last5(void) {
    s32 rank = *(s32 *)HuPrcCurrentGet()->user_data;
    s32 i;

    for (i = 0; i < 110; i += 5) {
        MBStatusPosSet(D_80107568_last5[rank], 30, sindf(i) * 250.0f - (0xF1 - D_801074F0_last5[rank]));
        HuPrcVSleep();
    }
    MBStatusPosSet(D_80107568_last5[rank], 30, D_801074F0_last5[rank]);
    omDelPrcObj(NULL);
}

Process *func_801060A4_last5(s32 rank) {
    Process *prc = omAddPrcObj(func_80105F9C_last5, 10, 0, 0x40);
    s32 *data = HuMemMemoryAlloc(prc->heap, 0x10);

    prc->user_data = data;
    *data = rank;
    return prc;
}

// decomp-permuter
void func_80106100_last5(void)
{
  s32 sel;
  Object *host;
  Object *obj;
  s32 i;
  s32 x;
  s32 dx;
  Vec dir;
  host = MBModelFileCreate(0xA002F, 9, 0.7f, 1.4f, D_801074D4_last5);
  HuVecCopy3F(&host->coords, &D_80107480_last5);
  MBVecDirGet(&host->coords, &D_8010748C_last5, &host->rot);
  HuVecCopyXYZ(&host->scale, 2.0f, 2.0f, 2.0f);
  obj = MBModelCreate(0x39, D_801074C4_last5);
  HuVecCopy3F(&obj->coords, &D_801074B0_last5);
  HuAudSeqPlay(0x13);
  WipeColorSet(255, 255, 255);
  WipeCreateIn(2, 16);
  while (WipeStatGet() != 0)
  {
    HuPrcVSleep();
  }

  func_80105DEC_last5();
  HuAudFXPlay(0x2A0);
  func_800EC5B4_shared_board(-1, 0x430A);
  for (x = 0; x < 4; x++)
  {
    HuPrcChildLink(HuPrcCurrentGet(), func_801060A4_last5(x));
    {
      s32 mes[4] = {0x430B, 0x430C, 0x430D, 0x430E};
      func_80105C9C_last5(func_80105B04_last5(mes[BoardPlayerRankCalc(D_80107568_last5[x])], mbCharNameMesTbl[GwPlayer[D_80107568_last5[x]].chr], 0, 0, 0, 0, 140, 110));
    }
    HuPrcChildWait();
  }

  func_800EC5B4_shared_board(-1, 0x430F);
  MBMotionSet(host, 0, 2);
  sel = 0;
  HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&host->coords, &D_8010748C_last5, &host->coords, 60));
  dx = 0;
  HuPrcChildWait();
  MBVecForwardSet(&dir);
  HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&host->rot, &dir, &host->rot, 10));
  HuPrcChildWait();
  MBMotionShiftSet(host, -1, 0, 5, 2);
  x = MBRand(100.0f);
  for (; dx < 4; dx++)
  {
    if (x < D_801074EC_last5[dx])
    {
      if (x)
      {
        sel = dx;
        break;
      }
      else
      {
        sel = dx;
        break;
      }
    }
  }

  HuAudFXPlay(0x29D);
  {
    s16 win = func_80105B04_last5(0x4310, mbCharNameMesTbl[GwPlayer[D_80107568_last5[sel]].chr], 0, 0, 0, 0, 160, 80);
    func_80105AAC_last5(win);
    func_80105C9C_last5(win);
  }
  x = 30;
  dx = 10;
  do
  {
    for (i = 0; i < 4; i++)
    {
      if (sel != i)
      {
        MBStatusPosSet(D_80107568_last5[i], x, D_801074F0_last5[i]);
      }
    }

    x -= dx;
    dx += 2;
    HuPrcVSleep();
  }
  while (x >= (-160));
  for (x = D_801074F0_last5[sel]; D_801074F0_last5[0] < x; x -= 10)
  {
    MBStatusPosSet(D_80107568_last5[sel], 30, x);
    HuPrcVSleep();
  }

  MBStatusPosSet(D_80107568_last5[sel], 30, D_801074F0_last5[0]);
  MBPlayerVibrate(D_80107568_last5[sel], 2);
  func_80105C9C_last5(func_80105B04_last5(0x4311, mbCharNameMesTbl[GwPlayer[D_80107568_last5[sel]].chr], 0, 0, 0, 0, 80, 100));
  MBCoinTakeCreate(D_80107568_last5[sel], -10);
  HuPrcSleep(30);
  MBMotionSet(host, 1, 2);
  MBVecDirGet(&host->coords, &D_80107480_last5, &host->rot);
  x = 30;
  HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&host->coords, &D_80107480_last5, &host->coords, 30));
  dx = 10;
  do
  {
    MBStatusPosSet(D_80107568_last5[sel], x, D_801074F0_last5[0]);
    x -= dx;
    dx += 2;
    HuPrcVSleep();
  }
  while (x >= (-160));
  HuPrcChildWait();
  func_800EC5B4_shared_board(-1, 0x4312);
  MBMotionShiftSet(obj, 0, 0, 5, 2);
  HuPrcSleep(20);
}

void func_801066E0_last5(omObjData *obj) {
    D_8010757C_last5->velocity.x = sindf(obj->rot.x) * 20.0f + obj->rot.y;
    obj->rot.x += 5.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void func_80106768_last5(void) {
    Object *host;
    Object *guide;
    s16 effect;
    s32 i;
    s32 r;
    s32 x;
    s32 dx;
    s32 sel;
    s32 hostWins;
    omObjData *bob;
    Vec dir;

    hostWins = 0;
    bob = NULL;
    host = MBModelCreate(0xB, D_801074CC_last5);
    HuVecCopy3F(&host->coords, &D_80107480_last5);
    MBVecDirGet(&host->coords, &D_8010748C_last5, &host->rot);
    HuVecCopyXYZ(&host->scale, 1.5f, 1.5f, 1.5f);
    D_8010757C_last5 = MBModelCreate(0x3A, D_801074E0_last5);
    func_800461B4_main(D_8010757C_last5->omObj1->model[0]);
    HuVecCopy3F(&D_8010757C_last5->coords, &D_80107498_last5[0]);
    D_8010757C_last5->velocity.x = 1000.0f;
    effect = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(effect, 10.0f, 20.0f, 10.0f);
    func_800138EC_main(effect, 1, 0);
    func_8000D018_main(effect, 300.0f);
    guide = MBModelCreate(9, D_801074BC_last5);
    HuVecCopy3F(&guide->coords, &D_801074B0_last5);
    MBGuideFaceCreate(guide, 2, 10, D_80107500_last5);
    HuAudSeqPlay(0x13);
    WipeColorSet(255, 255, 255);
    WipeCreateIn(2, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_80105DEC_last5();
    HuAudFXPlay(0x298);
    func_800EC5B4_shared_board(-1, 0x4300);
    for (r = 0; r < 4; r++) {
        HuPrcChildLink(HuPrcCurrentGet(), func_801060A4_last5(r));
        {
            s32 mes[4] = { 0x4301, 0x4302, 0x4303, 0x4304 };

            func_80105C9C_last5(func_80105B04_last5(mes[BoardPlayerRankCalc(D_80107568_last5[r])],
                                                    mbCharNameMesTbl[GwPlayer[D_80107568_last5[r]].chr], 0, 0, 0, 0, 140, 110));
        }
        HuPrcChildWait();
    }
    func_800EC5B4_shared_board(-1, 0x4305);
    sel = 3;
    for (r = 0; r < 4; r++) {
        if (GwPlayer[r].chr == 0) {
            sel = D_80107558_last5[r];
            break;
        }
    }
    if (r != 4 && MBRand(6.0f) == 0) {
        hostWins = 1;
    }
    if (hostWins == 1) {
        MBMotionSet(host, 0, 2);
        x = 30;
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&host->coords, &D_8010748C_last5, &host->coords, 30));
        dx = 10;
        HuPrcChildWait();
        MBVecForwardSet(&dir);
        HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&host->rot, &dir, &host->rot, 10));
        HuPrcChildWait();
        MBMotionSet(host, -1, 2);
        HuAudFXPlay(0x25D);
        {
            s16 win = func_80105B04_last5(0x4307, 0, 0, 0, 0, 0, 160, 80);

            func_80105AAC_last5(win);
            func_80105C9C_last5(win);
        }
    } else {
        func_800138EC_main(effect, 0, 1);
        HuAudFXPlay(0x157);
        while (D_8010757C_last5->velocity.x >= 400.0f) {
            D_8010757C_last5->velocity.x -= 20.0f;
            func_8000CFA4_main(effect, D_8010757C_last5->coords.x, D_8010757C_last5->velocity.x - 100.0f, D_8010757C_last5->coords.z);
            HuPrcVSleep();
        }
        bob = omAddObj(0x1000, 0, 0, -1, func_801066E0_last5);
        bob->rot.y = D_8010757C_last5->velocity.x;
        bob->rot.x = 180.0f;
        sel = 3;
        r = MBRand(100.0f);
        for (dx = 0; dx < 4; dx++) {
            if (r < D_801074E8_last5[dx]) {
                sel = dx;
                break;
            }
        }
        HuAudFXPlay(0x159);
        MBMotionShiftSet(D_8010757C_last5, 0, 0, 5, 2);
        {
            s16 win = func_80105B04_last5(0x4306, mbCharNameMesTbl[GwPlayer[D_80107568_last5[sel]].chr], 0, 0, 0, 0, 160, 80);

            func_80105AAC_last5(win);
            func_80105AAC_last5(win);
            func_80105C9C_last5(win);
        }
        MBMotionShiftSet(D_8010757C_last5, -1, 0, 5, 2);
        x = 30;
        dx = 10;
    }
    do {
        for (i = 0; i < 4; i++) {
            if (sel != i) {
                MBStatusPosSet(D_80107568_last5[i], x, D_801074F0_last5[i]);
            }
        }
        x -= dx;
        dx += 2;
        HuPrcVSleep();
    } while (x >= -160);
    for (r = D_801074F0_last5[sel]; D_801074F0_last5[0] < r; r -= 10) {
        MBStatusPosSet(D_80107568_last5[sel], 30, r);
        HuPrcVSleep();
    }
    MBStatusPosSet(D_80107568_last5[sel], 30, D_801074F0_last5[0]);
    MBPlayerVibrate(D_80107568_last5[sel], 2);
    func_80105C9C_last5(func_80105B04_last5(0x4308, mbCharNameMesTbl[GwPlayer[D_80107568_last5[sel]].chr], 0, 0, 0, 0, 80, 100));
    MBCoinTakeCreate(D_80107568_last5[sel], 10);
    HuPrcSleep(30);
    if (hostWins != 0) {
        MBMotionSet(host, 0, 2);
        MBVecDirGet(&host->coords, &D_80107480_last5, &host->rot);
        dx = 10;
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&host->coords, &D_80107480_last5, &host->coords, 30));
        x = 30;
        do {
            MBStatusPosSet(D_80107568_last5[sel], x, D_801074F0_last5[0]);
            x -= dx;
            dx += 2;
            HuPrcVSleep();
        } while (x >= -160);
        HuPrcChildWait();
    } else {
        x = 30;
        omDelObj(bob);
        dx = 10;
        do {
            MBStatusPosSet(D_80107568_last5[sel], x, D_801074F0_last5[0]);
            x -= dx;
            dx += 2;
            D_8010757C_last5->velocity.x += 20.0f;
            func_8000CFA4_main(effect, D_8010757C_last5->coords.x, D_8010757C_last5->velocity.x - 100.0f, D_8010757C_last5->coords.z);
            HuPrcVSleep();
        } while (x >= -160);
        while (D_8010757C_last5->velocity.x <= 1000.0f) {
            D_8010757C_last5->velocity.x += 20.0f;
            func_8000CFA4_main(effect, D_8010757C_last5->coords.x, D_8010757C_last5->velocity.x - 100.0f, D_8010757C_last5->coords.z);
            HuPrcVSleep();
        }
        func_800138EC_main(effect, 1, 0);
    }
    func_8000D044_main(effect);
    func_800EC5B4_shared_board(-1, 0x4309);
    MBGuideFaceSet(guide, D_80107504_last5);
    MBMotionShiftSet(guide, 0, 0, 5, 2);
    HuPrcSleep(20);
}

void func_80107178_last5(void) {
    s32 i;
    s32 rank;
    s32 count;

    for (i = 0; i < 4; i++) {
        D_80107558_last5[i] = BoardPlayerRankCalc(i);
    }
    for (rank = 0; rank < 4; rank++) {
        count = 0;
        for (i = 0; i < 4; i++) {
            if (D_80107558_last5[i] == rank) {
                count++;
                if (count >= 2) {
                    D_80107558_last5[i] = rank + count - 1;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        D_80107568_last5[D_80107558_last5[i]] = i;
    }
    if (MBRand(3.0f) == 0) {
        func_80106100_last5();
    } else {
        func_80106768_last5();
    }
    D_800D530C_main = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_801072B0_last5(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80107450_last5();
        func_80107384_last5();
        func_800F4730_shared_board();
        func_8005F524_main();
        omOvlReturnEx(1);
    }
}

void func_801072FC_last5(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeColorSet(255, 255, 255);
        WipeCreateOut(2, 20);
        HuAudSeqFadeOut(60);
        obj->func = func_801072B0_last5;
    }
}

void func_80107358_last5(void) {
    MBModelInit();
    func_800F26E8_shared_board();
    func_800EE700_shared_board();
}

void func_80107384_last5(void) {
    func_800EE740_shared_board();
    func_800F27C4_shared_board();
    MBModelClose();
}

void func_801073B0_last5(void) {
    s32 sp10[] = { 4, 7, 0xA, 0xD, 0x10, 0x13 };

    Hu3DCamInit(1);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    MBBackLoad(sp10[GwSystem.current_board_index]);
    func_800E9344_shared_board(1000.0f, 10000.0f);
}

void func_80107450_last5(void) {
    MBBackKill();
    MBBackClose();
}

/* event e5: .data */
Vec D_80107480_last5 = { 750.0f, 0.0f, 2250.0f }; /* the host's start (and exit) */
Vec D_8010748C_last5 = { 150.0f, 0.0f, 1750.0f }; /* where the host walks to */
Vec D_80107498_last5[2] = { { 150.0f, 0.0f, 2000.0f }, { 150.0f, 0.0f, 2000.0f } }; /* the lamp */
Vec D_801074B0_last5 = { 0.0f, 0.0f, 2250.0f };
u32 D_801074BC_last5[2] = { 1, 0xA0019 }; /* MBModelCreate file lists: count, then ids */
u32 D_801074C4_last5[2] = { 1, 0xA00FB };
u32 D_801074CC_last5[2] = { 1, 0xA00D0 };
u32 D_801074D4_last5[3] = { 2, 0xA0035, 0xA0042 };
u32 D_801074E0_last5[2] = { 1, 0xA0125 };
u8 D_801074E8_last5[4] = { 5, 15, 50, 100 }; /* cumulative odds of picking rank 1..4 (coin gift) */
u8 D_801074EC_last5[4] = { 50, 85, 95, 100 }; /* the same for the coin loss */
s32 D_801074F0_last5[4] = { 0x11, 0x49, 0x81, 0xB9 }; /* status box y of each rank */
s32 D_80107500_last5 = 0xA002A;
s32 D_80107504_last5 = 0xA002B;
