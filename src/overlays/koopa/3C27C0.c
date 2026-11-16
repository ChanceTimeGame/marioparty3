#include "common.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/113520.h"

typedef struct UnkBowser {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} UnkBowser; // sizeof 0x8

typedef struct UnkBowser2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
} UnkBowser2; // sizeof 0x24

void func_8005A6B0_main(void);
void func_80108D2C_koopa(void);
void func_80109220_koopa(omObjData *);
void func_8010926C_koopa(void);
// event e4
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/106640.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/F2910.h"
void func_80105AD8_koopa(omObjData *obj);
s32 func_80107658_koopa(s32 arg0, s32 arg1);
s32 func_801076CC_koopa(s32 playerIndex);
void func_80107190_koopa(void);
void func_80107648_koopa(void);
void func_801087F0_koopa(void);
void func_80108360_koopa(s32 file);
void func_801091C4_koopa(omObjData *obj);
void func_801092A0_koopa(void);
void func_80109320_koopa(void);
void func_800E4A94_shared_board(void);
void func_800E4B18_shared_board(void);
void func_800EE700_shared_board(void);
void func_800EE740_shared_board(void);
void func_800F2A20_shared_board(void);
void func_800F2A34_shared_board(void);
void func_800F5828_shared_board(s32 arg0);
void func_800F591C_shared_board(s32 arg0);
void func_801092D4_koopa(void);
void func_80107724_koopa(void);
s32 func_80107A9C_koopa(void);
s32 func_80107DDC_koopa(void);
s32 func_801085E4_koopa(void);
s32 func_80108664_koopa(void);
s32 func_801086E4_koopa(void);
s32 func_80108A2C_koopa(void);
s32 func_80108BB0_koopa(void);
s32 func_8010778C_koopa(void);
s32 func_801078CC_koopa(void);

extern s16 D_801094F6_koopa;
extern Object *D_801094F8_koopa;
extern char D_80109508_koopa[];

extern u8 D_801094F0_koopa;
extern s32 D_801094F4_koopa;
extern u32 D_800D2094_main;
extern s32 D_8010956C_koopa;
extern omObjData *D_80109550_koopa;
extern s16 D_80109518_koopa[5][5];
extern s16 D_80109554_koopa[2];
extern s16 D_80109558_koopa;
extern s16 D_8010955A_koopa;
extern s16 D_8010955C_koopa;
extern s16 D_8010955E_koopa;
extern s16 D_80109560_koopa;
extern s16 D_80109562_koopa;
extern s16 D_80109564_koopa;
extern s32 D_80109568_koopa;
extern s32 D_80109500_koopa;
extern s32 D_80109504_koopa;

//.data
Unk3 *D_80109350_koopa = NULL;

s32 D_80109354_koopa[] = {
    0x00004200,
    0x00004201,
    0x00004202,
    0x00004203,
    0x00004204,
    0x00004205,
    0x00004206,
    0x00004207,
    0x00004208,
    0x00004209,
};

UnkBowser D_8010937C_koopa[] = {
    { 64, -206, 200, 20 },
    { 64, -186, 200, 20 },
    { 64, -166, 200, 20 },
    { 64, -146, 200, 20 },
    { 64, -126, 200, 20 }
};

u8 D_801093A4_koopa = 94;
u8 D_801093A8_koopa[][2] = {
    { 1, 0 },
    { 9, 15 },
    { 11, 8 },
    { 13, 0 }
};
Vec D_801093B0_koopa = { 0.0f, 0.0f, 2250.0f };
Vec D_801093BC_koopa = { 0.0f, 0.0f, -1000.0f };

UnkBowser2 D_801093C8_koopa = {
    0x00000008, 0x000A0035, 0x000A0032, 0x000A0038,
    0x000A0040, 0x000A0043, 0x000A0041, 0x000A0042, 0x000A0044
};

void *D_801093EC_koopa[] = {
    func_8010778C_koopa,
    func_801078CC_koopa,
    func_80107A9C_koopa,
    func_80107DDC_koopa,
    func_801085E4_koopa,
    func_80108664_koopa,
    func_801086E4_koopa,
    func_80108A2C_koopa,
    func_80108BB0_koopa,
    func_80108BB0_koopa
};

u32 D_80109414_koopa = 0;
s16 D_80109418_koopa[] = { 90, 89, 87, 71, 70, 84, 85, 86, 62, 61, 58, 59, 60, -1 };
// Coin amounts by kind (0: the visitor pays, 1: everyone pays, 2: Bowser gives a visitor with no coins), turn tier, rank.
// The third table was split off by splat as D_80109464 (func_801076CC reads index 2).
u16 D_80109434_koopa[3][3][4] = {
    { { 20, 20, 10, 10 },
      { 20, 20, 15, 15 },
      { 30, 30, 20, 20 } },
    { { 10, 10, 10, 10 },
      { 20, 20, 20, 20 },
      { 30, 30, 30, 30 } },
    { { 20, 20, 30, 30 },
      { 30, 30, 40, 40 },
      { 30, 40, 50, 50 } }
};

//.text
void func_801059A0_koopa(void) {
    s32 i;

    D_801094F0_koopa = GwSystem.current_board_index;
    D_801094F4_koopa = GwSystem.playerIndexVisitingBowser;
    omInitObjMan(0x32, 0x32);
    func_801092D4_koopa();
    func_8010926C_koopa();
    func_800D95C4_shared_board(1000.0f);
    func_8005A6B0_main();
    func_800F453C_shared_board();
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBStatusPosSet(i, 0x1E, -0x32);
    }
    omAddPrcObj(func_80108D2C_koopa, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80109220_koopa);
    func_800EA60C_shared_board();
    MBMasuCreate(0x13, 0x23A);
    func_8004A208_main();
}

void func_80105A8C_koopa(void) {
    if (D_800D2094_main >= (D_80109414_koopa + 4)) {
        HuAudFXPlay(0x104);
        D_80109414_koopa = D_800D2094_main;
    }
}

// event e4
extern u8 D_8010954A_koopa[];
void func_80106A54_koopa(void);
void func_80106AB8_koopa(void);
void func_80106FC8_koopa(void);

// NON_MATCHING: masked 30 of 1083: block placement around the CPU/A-button check and the
// second wrap of the stop slot, and the hoisted D_801093A8 base in the last loop; logic checked
#ifdef NON_MATCHING
void func_80105AD8_koopa(omObjData *obj) {
    s32 i;
    s32 idx = 0;
    s16 *win;
    s32 r;
    f32 ofs;

    switch (obj->work[0]) {
    case 3:
        break;
    case 0:
        obj->trans.y += 16.0f;
        for (i = 0; i < 5; i++) {
            win = D_80109518_koopa[i];
            func_8005BA90_main(win[0], win[1] + win[3] / 2, win[2] + win[4] / 2 + (s32)obj->trans.y);
        }
        if (D_8010955E_koopa != -1) {
            func_80054904_main(D_8010955E_koopa, 0, D_80109518_koopa[0][1] + 100, (s32)obj->trans.y + D_80109518_koopa[0][2] + 50);
        }
        if (D_8010955A_koopa != -1) {
            func_80054904_main(D_8010955A_koopa, 0, D_80109518_koopa[0][1] + 100, (s32)obj->trans.y + D_80109518_koopa[0][2] - 30);
        }
        for (i = 0; i < 2; i++) {
            if (D_80109554_koopa[i] != -1) {
                func_80054904_main(D_80109554_koopa[i], 0, D_80109518_koopa[0][1] + i * 200, (s32)obj->trans.y + D_80109518_koopa[0][2] - 40);
            }
        }
        if (obj->trans.y >= 288.0f) {
            func_80105A8C_koopa();
            D_80109350_koopa = func_800E210C_shared_board(0x17, 200, 1);
            obj->work[0] = 1;
            obj->scale.x = 0.5f;
            obj->scale.z = -1.0f;
            obj->scale.y = 0.0f;
            obj->work[1] = 0;
            obj->work[3] = 0;
            obj->trans.z = 0.0f;
            obj->rot.y = D_80109500_koopa;
            if (D_80109504_koopa != 0) {
                for (i = 0; i < 5; i++) {
                    if (D_8010954A_koopa[i] >= 8) {
                        idx = i - (s32)obj->rot.y;
                        break;
                    }
                }
                if (idx < 0) {
                    idx += 5;
                } else {
                    idx %= 5;
                }
                obj->work[2] = idx;
            } else {
                obj->work[2] = 0;
            }
            r = MBRand(100.0f);
            if (r < 60) {
                obj->mdlcnt = 20;
            } else if (r < 90) {
                obj->mdlcnt = 14;
            } else {
                obj->mdlcnt = 8;
            }
            obj->mtncnt = 0;
            func_80106FC8_koopa();
        }
        break;
    case 1:
        if (obj->trans.z == 0.0f) {
            if (GwPlayer[D_801094F4_koopa].stat & 1) {
                obj->trans.z = 1.0f;
            } else if (D_800C9520_main[GwPlayer[D_801094F4_koopa].pad] & 0x8000) {
                obj->trans.z = 1.0f;
            }
            if (obj->trans.z == 1.0f && D_80109350_koopa != NULL) {
                MBHelpWinKill(D_80109350_koopa);
                D_80109350_koopa = NULL;
            }
            if (D_80109504_koopa == 0) {
                for (i = 0; ; i++) {
                    idx = i + obj->work[1];
                    if (idx < 0) {
                        idx += 5;
                    } else {
                        idx %= 5;
                    }
                    if (D_8010954A_koopa[idx] < 8) {
                        break;
                    }
                }
                idx -= (s32)obj->rot.y;
                if (idx >= 0) {
                    idx %= 5;
                } else {
                    idx += 5;
                }
                obj->work[2] = idx;
            }
        }
        if (obj->mtncnt != 0) {
            obj->scale.x = obj->mdlcnt / 100.0f;
        }
        obj->scale.z += obj->scale.x;
        if (obj->scale.z >= 1.0f) {
            if (obj->work[3] != 0 && obj->scale.x <= 0.08f) {
                obj->work[3]--;
            }
            obj->scale.z -= 1.0f;
            if (obj->scale.y == 0.0f) {
                obj->work[1] = (obj->work[1] + 1) % 5;
            } else if (--obj->work[1] >= 128) {
                obj->work[1] = 4;
            }
            func_80105A8C_koopa();
        }
        for (i = 0; i < 5; i++) {
            win = D_80109518_koopa[i];
            if (i == obj->work[1]) {
                func_8005FBF8_main(win[0], 0, 200, 0);
                func_8005BEE0_main(win[0], 0x100);
                func_8005BE30_main(win[0], 9000);
            } else {
                func_8005FBF8_main(win[0], 64, 64, 128);
                func_8005BEE0_main(win[0], 0);
                func_8005BE30_main(win[0], 10000);
            }
        }
        if (obj->trans.z != 0.0f) {
            if (obj->work[1] == obj->work[2] || obj->scale.x < 1.0f) {
                if (obj->mtncnt == 0) {
                    obj->scale.x -= 0.01f;
                }
            }
        }
        if (obj->scale.x <= 0.08f || obj->mtncnt != 0) {
            if (obj->mtncnt == 0) {
                obj->scale.x = 0.08f;
            }
            if (obj->work[1] == obj->work[2] && obj->work[3] == 0 && obj->scale.z + obj->scale.x >= 1.0f) {
                ofs = obj->rot.y;
                if (((ofs > 0.0f) ? ofs : 0.0f - ofs) <= 0.5f) {
                    HuAudFXPlay(0x105);
                    switch (D_8010954A_koopa[obj->work[2]]) {
                    case 0:
                    case 2:
                    case 3:
                    case 8:
                    case 9:
                        MBPlayerVibrate(D_801094F6_koopa, 2);
                        break;
                    case 1:
                        MBPlayerVibrate(0, 2);
                        MBPlayerVibrate(1, 2);
                        MBPlayerVibrate(2, 2);
                        MBPlayerVibrate(3, 2);
                        break;
                    case 4:
                    case 5:
                        MBPlayerVibrate(0, 3);
                        MBPlayerVibrate(1, 3);
                        MBPlayerVibrate(2, 3);
                        MBPlayerVibrate(3, 3);
                        break;
                    case 6:
                        MBPlayerVibrate(0, 4);
                        MBPlayerVibrate(1, 4);
                        MBPlayerVibrate(2, 4);
                        MBPlayerVibrate(3, 4);
                        break;
                    case 7:
                        MBPlayerVibrate(0, 5);
                        MBPlayerVibrate(1, 5);
                        MBPlayerVibrate(2, 5);
                        MBPlayerVibrate(3, 5);
                        break;
                    }
                    obj->work[0] = 2;
                    obj->work[3] = 60;
                    func_8005D294_main(D_80109518_koopa[obj->work[1]][0]);
                    if (D_8010954A_koopa[obj->work[1]] == 0) {
                        func_8005B6BC_main(D_80109518_koopa[obj->work[1]][0], (u32)D_80109508_koopa, 0);
                        func_8006022C_main((u32)D_80109508_koopa, 0);
                    }
                    func_8005B43C_main(D_80109518_koopa[obj->work[1]][0], D_80109354_koopa[D_8010954A_koopa[obj->work[1]]], -2, 4);
                    func_8005C02C_main(D_80109518_koopa[obj->work[1]][0], 1);
                    func_8005C154_main(D_80109518_koopa[obj->work[1]][0], 160, 160, 160);
                    func_8005FBF8_main(D_80109518_koopa[obj->work[1]][0], 254, 255, 208);
                    func_8005BDFC_main(D_80109518_koopa[obj->work[1]][0], 0);
                } else {
                    obj->mtncnt = 1;
                    if (obj->rot.y >= 0.5f) {
                        obj->rot.y -= 1.0f;
                        obj->work[2] = (obj->work[2] + 1) % 5;
                    } else {
                        obj->rot.y += 1.0f;
                        obj->scale.y = 1.0f;
                        if (--obj->work[2] >= 128) {
                            obj->work[2] = 4;
                        }
                    }
                }
            }
        }
        break;
    case 2:
        if (obj->work[3] == 0) {
            obj->work[0] = 4;
            func_80106A54_koopa();
        } else {
            obj->work[3]--;
            obj->rot.z += 1.0f;
            if (obj->rot.z >= 13.0f) {
                obj->rot.z -= 13.0f;
            }
        }
        break;
    case 4:
        obj->trans.y -= 32.0f;
        for (i = 0; i < 5; i++) {
            win = D_80109518_koopa[i];
            func_8005BA90_main(win[0], win[1] + win[3] / 2, win[2] + win[4] / 2 + (s32)obj->trans.y);
        }
        if (D_8010955E_koopa != -1) {
            func_80054904_main(D_8010955E_koopa, 0, D_80109518_koopa[0][1] + 100, (s32)obj->trans.y + D_80109518_koopa[0][2] + 50);
        }
        if (D_8010955A_koopa != -1) {
            func_80054904_main(D_8010955A_koopa, 0, D_80109518_koopa[0][1] + 100, (s32)obj->trans.y + D_80109518_koopa[0][2] - 30);
        }
        for (i = 0; i < 2; i++) {
            if (D_80109554_koopa[i] != -1) {
                func_80054904_main(D_80109554_koopa[i], 0, D_80109518_koopa[0][1] + i * 200, (s32)obj->trans.y + D_80109518_koopa[0][2] - 40);
            }
        }
        if (obj->trans.y <= 0.0f) {
            D_80109568_koopa = D_8010954A_koopa[obj->work[2]];
            func_80106AB8_koopa();
        }
        break;
    }
    if (D_80109562_koopa != -1) {
        for (i = 0; !(obj->rot.z < (s8)D_801093A8_koopa[i][0]); i++) {
        }
        func_80054904_main(D_80109562_koopa, 0, (s8)D_801093A8_koopa[i][1] + 50, D_801093A4_koopa + obj->work[1] * 20);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/koopa/3C27C0", func_80105AD8_koopa);
#endif

s32 func_80106968_koopa(void) {
    return D_80109568_koopa;
}

s32 func_80106974_koopa(void) {
    return D_8010956C_koopa;
}

s32 func_80106980_koopa(void) {
    if (D_80109550_koopa == NULL) {
        return -1;
    }
    return D_80109550_koopa->work[0];
}

void func_8010699C_koopa(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80109518_koopa); i++) {
        D_80109518_koopa[i][0] = -1;
    }

    D_80109550_koopa = NULL;

    for (i = 0; i < ARRAY_COUNT(D_80109554_koopa); i++) {
        D_80109554_koopa[i] = -1;
    }

    D_80109558_koopa = -1;
    D_8010955C_koopa = -1;
    D_8010955A_koopa = -1;
    D_80109560_koopa = -1;
    D_8010955E_koopa = -1;
    D_80109564_koopa = -1;
    D_80109562_koopa = -1;
    D_80109568_koopa = -1;
    D_80109350_koopa = 0;
}

void func_80106A54_koopa(void) {
    if (D_80109562_koopa != -1) {
        HuSprGrpKill(D_80109562_koopa);
        D_80109562_koopa = -1;
    }
    if (D_80109564_koopa != -1) {
        HuSprKill(D_80109564_koopa);
        D_80109564_koopa = -1;
    }
}

void func_80106AB8_koopa(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80109518_koopa); i++) {
        s16 *temp = D_80109518_koopa[i];
        if (temp[0] != -1) {
            func_8005F364_main(temp[0]);
            temp[0] = -1;
        }
    }

    if (D_80109350_koopa != 0) {
        MBHelpWinKill(D_80109350_koopa);
        D_80109350_koopa = 0;
    }

    if (D_80109550_koopa != NULL) {
        omDelObj(D_80109550_koopa);
        D_80109550_koopa = NULL;
    }

    if (D_8010955E_koopa != -1) {
        HuSprGrpKill(D_8010955E_koopa);
        D_8010955E_koopa = -1;
    }

    if (D_80109560_koopa != -1) {
        HuSprKill(D_80109560_koopa);
        D_80109560_koopa = -1;
    }

    if (D_8010955A_koopa != -1) {
        HuSprGrpKill(D_8010955A_koopa);
        D_8010955A_koopa = -1;
    }

    if (D_8010955C_koopa != -1) {
        HuSprKill(D_8010955C_koopa);
        D_8010955C_koopa = -1;
    }

    for (i = 0; i < ARRAY_COUNT(D_80109554_koopa); i++) {
        if (D_80109554_koopa[i] != -1) {
            HuSprGrpKill(D_80109554_koopa[i]);
            D_80109554_koopa[i] = -1;
        }
    }

    if (D_80109558_koopa != -1) {
        HuSprKill(D_80109558_koopa);
        D_80109558_koopa = -1;
    }

    func_80106A54_koopa();
}

void func_80106C78_koopa(void) {
    s32 randVal;
    s32 var_v0_2;
    void *temp_v0;
    s32 i;

    if (D_8010955E_koopa == -1) {
        D_8010955E_koopa = HuSprGrpCreate(1, 5);
        temp_v0 = DataRead(0x1301EB);
        D_80109560_koopa = func_80055810_main(temp_v0);
        DataClose(temp_v0);
        func_80055024_main(D_8010955E_koopa, 0, D_80109560_koopa, 0);
        HuSprPriSet(D_8010955E_koopa, 0, 0x4770);
        HuSprAttrSet(D_8010955E_koopa, 0, 0x1000);
        func_80054904_main(D_8010955E_koopa, 0, D_80109518_koopa[0][1] + 0x64, D_80109518_koopa[0][2] + 0x32);
        func_80055420_main(D_8010955E_koopa, 0, 0, 0, 0);
        D_8010955A_koopa = HuSprGrpCreate(1, 5);
        temp_v0 = DataRead(0x1301E9);
        D_8010955C_koopa = func_80055810_main(temp_v0);
        DataClose(temp_v0);
        func_80055024_main(D_8010955A_koopa, 0, D_8010955C_koopa, 0);
        HuSprPriSet(D_8010955A_koopa, 0, 0x4770);
        HuSprAttrSet(D_8010955A_koopa, 0, 0x1000);
        func_80054904_main(D_8010955A_koopa, 0, D_80109518_koopa[0][1] + 0x64, D_80109518_koopa[0][2] - 0x1E);
        temp_v0 = DataRead(0x130260);
        D_80109558_koopa = func_80055810_main(temp_v0);
        DataClose(temp_v0);
        randVal = MBRand(5.0f);
        for (i = 0; i < ARRAY_COUNT(D_80109554_koopa); i++) {
            D_80109554_koopa[i] = HuSprGrpCreate(1, 5);
            func_80055024_main(D_80109554_koopa[i], 0, D_80109558_koopa, 1);
            HuSprPriSet(D_80109554_koopa[i], 0, 0x4770);
            HuSprAttrSet(D_80109554_koopa[i], 0, 0x1000);
            func_80054904_main(D_80109554_koopa[i], 0, D_80109518_koopa[0][1] + (i * 0xC8), (D_80109518_koopa[0][2] - 0x28));
            if ((randVal == 0) && (D_80109504_koopa == 0)) {
                var_v0_2 = D_80109500_koopa;
                if (var_v0_2 == 0) {
                    func_80055420_main(D_80109554_koopa[i], 0, 0, 0, 0xFF);
                } else {
                    if (var_v0_2 < 0) {
                        var_v0_2 = -var_v0_2;
                    }
                    if (var_v0_2 < 2) {
                        func_80055420_main(D_80109554_koopa[i], 0, 0xFF, 0xFF, 0);
                    } else {
                        func_80055420_main(D_80109554_koopa[i], 0, 0xFF, 0, 0);
                    }
                }
            } else {
                func_80055420_main(D_80109554_koopa[i], 0, 0xFF, 0, 0);
            }
        }
    }
}

void func_80106FC8_koopa(void) {
    void *temp_v0;

    if (D_80109562_koopa == -1) {
        D_80109562_koopa = HuSprGrpCreate(1, 5);
        temp_v0 = DataRead(0x1301EA);
        D_80109564_koopa = func_80055810_main(temp_v0);
        DataClose(temp_v0);
        func_80055024_main(D_80109562_koopa, 0, D_80109564_koopa, 0);
        HuSprPriSet(D_80109562_koopa, 0, 0x100);
        HuSprAttrSet(D_80109562_koopa, 0, 0x1000);
        func_80054904_main(D_80109562_koopa, 0, 0x32, D_801093A4_koopa);
    }
}

s32 func_80107090_koopa(void) {
    s32 var_s3;
    GW_PLAYER *temp_s1;
    s32 i, j;

    if (GwSystem.current_board_index == CHILLY_WATERS) {
        for (var_s3 = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
            temp_s1 = MBPlayerGet(i);
            for (j = 0; D_80109418_koopa[j] != -1; j++) {
                if (MBMasuLinkMasuIdGet(temp_s1->clink, temp_s1->cidx) == D_80109418_koopa[j]) {
                    var_s3++;
                    break;
                }
            }
        }
        if (var_s3 < 2) {
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}

const char D_801094C0_koopa[] = "%d";
const char D_801094C4_koopa[] = "";


void func_80107190_koopa(void) {
    u8 order[8];
    u8 kinds[8];
    s32 r;
    s32 i;
    s16 *win;
    UnkBowser *src = D_8010937C_koopa;
    omObjData *obj;

    i = MBRand(256.0f);
    if (i < 70) {
        D_80109500_koopa = 0;
    } else if (i < 115) {
        D_80109500_koopa = 1;
    } else if (i < 160) {
        D_80109500_koopa = 2;
    } else if (i < 185) {
        D_80109500_koopa = 3;
    } else if (i < 200) {
        D_80109500_koopa = 4;
    } else if (i < 225) {
        D_80109500_koopa = -1;
    } else if (i < 240) {
        D_80109500_koopa = -2;
    } else {
        D_80109500_koopa = -3;
    }
    if (MBRand(70.0f) == 0) {
        D_80109504_koopa = 1;
    } else {
        D_80109504_koopa = 0;
    }
    for (i = 0; i < 5; i++) {
        win = D_80109518_koopa[i];
        win[1] = src[i].unk_00;
        win[2] = src[i].unk_02;
        win[3] = src[i].unk_04;
        win[4] = src[i].unk_06;
        win[0] = func_8005A968_main(win[1] + win[3] / 2, win[2] + win[4] / 2, win[3], win[4], 0, 4);
        func_80060144_main(win[0]);
        func_8005BCA4_main(win[0], win[3] / 2, win[4] / 2);
        func_8005BEE0_main(win[0], 0);
        switch (i) {
        case 0:
        case 1:
            kinds[i] = 0;
            break;
        case 2:
            kinds[i] = MBRand(2.0f) + 8;
            break;
        case 3:
        case 4:
        retry:
            r = MBRand(100.0f);
            if (r < 20) {
                if (i == 4 && kinds[3] == 1) {
                    goto retry;
                }
                kinds[i] = 1;
            } else if (r < 60) {
                if (i == 4 && (kinds[3] == 2 || kinds[3] == 3)) {
                    goto retry;
                }
                kinds[i] = MBRand(2.0f) + 2;
            } else if (r < 90) {
                if (i == 4 && (kinds[3] == 4 || kinds[3] == 5)) {
                    goto retry;
                }
                kinds[i] = MBRand(2.0f) + 4;
            } else {
                if (i == 4 && (kinds[3] == 6 || kinds[3] == 7)) {
                    goto retry;
                }
                kinds[i] = MBRand(2.0f) + 6;
                if (kinds[i] == 6 && func_80107090_koopa() != 0) {
                    goto retry;
                }
            }
            break;
        }
    }
    MBArrayShuffle(order, 4);
    for (i = 0; i < 5; i++) {
        D_8010954A_koopa[i] = kinds[order[i]];
    }
    for (i = 0; i < 5; i++) {
        win = D_80109518_koopa[i];
        if (D_8010954A_koopa[i] == 0) {
            sprintf(D_80109508_koopa, D_801094C0_koopa, func_80107658_koopa(0, D_801094F4_koopa));
            func_8005B6BC_main(win[0], (u32)D_80109508_koopa, 0);
            func_8006022C_main((u32)D_80109508_koopa, 0);
        }
        func_8005B43C_main(win[0], D_80109354_koopa[D_8010954A_koopa[i]], -2, 4);
        func_8005BDFC_main(win[0], 0);
    }
    obj = omAddObj(0x8000, 0, 0, -1, func_80105AD8_koopa);
    D_80109550_koopa = obj;
    obj->work[0] = 3;
    obj->trans.y = 0.0f;
    obj->rot.z = 0.0f;
    func_80106C78_koopa();
}

void func_80107648_koopa(void) {
    D_80109550_koopa->work[0] = 0;
}

s32 func_80107658_koopa(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 playerRank;

    temp_s0 = BoardGetTurnTier(CUR_TURN);
    playerRank = BoardPlayerRankCalc(arg1);
    return D_80109434_koopa[arg0][temp_s0][playerRank];
}

s32 func_801076CC_koopa(s32 playerIndex) {
    s32 temp_s0;
    s32 playerRank;

    temp_s0 = BoardGetTurnTier(CUR_TURN);
    playerRank = BoardPlayerRankCalc(playerIndex);
    return D_80109434_koopa[2][temp_s0][playerRank];
}

void func_80107724_koopa(void) {
    func_800F5E24_shared_board(D_801094F4_koopa);
    MBStatusDispMoveSet(0x18);
    func_800F5E24_shared_board(-1);
    HuPrcSleep(20);
}

void func_8010775C_koopa(void) {
    func_800F5E24_shared_board(D_801094F4_koopa);
    MBStatusDispMoveSet(0x18);
    func_800F5E24_shared_board(-1);
}

s32 func_8010778C_koopa(void) {
    s32 temp_v0;

    temp_v0 = func_80107658_koopa(0, D_801094F4_koopa);
    sprintf(D_80109508_koopa, D_801094C0_koopa, temp_v0);
    if (GwPlayer[D_801094F4_koopa].coin >= temp_v0) {
        MBWinInsertOpen(0x420D, D_80109508_koopa, 0, 0, 0, 0);
    } else {
        MBWinInsertOpen(0x420E, D_80109508_koopa, 0, 0, 0, 0);
    }

    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_80107724_koopa();
    MBMotionShiftSet(D_801094F8_koopa, 2, 0, 5, 0);
    func_800EE884_shared_board(D_801094F8_koopa, -1, 2);
    HuPrcSleep(14);
    HuAudFXPlay(0x29F);
    MBCoinTakeCreate(D_801094F4_koopa, -temp_v0);
    MBPlayerVibrate(D_801094F6_koopa, 3);
    HuPrcSleep(30);
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}

s32 func_801078CC_koopa(void) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0_2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;
    s32 i;

    temp_v0 = func_80107658_koopa(1, D_801094F4_koopa);
    sprintf(D_80109508_koopa, D_801094C0_koopa, temp_v0);
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].coin < temp_v0) {
            break;
        }
    }

    if (i == 4) {
        MBWinInsertOpen(0x4210, D_80109508_koopa, 0, 0, 0, 0);
    } else {
        MBWinInsertOpen(0x4211, D_80109508_koopa, 0, 0, 0, 0);
    }

    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBStatusDispMoveSet(0);
    HuPrcSleep(20);
    MBMotionShiftSet(D_801094F8_koopa, 2, 0, 5, 0);
    func_800EE884_shared_board(D_801094F8_koopa, -1, 2);
    HuPrcSleep(14);
    HuAudFXPlay(0x29F);
    var_a0_2 = -10000;
    var_s1 = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_v1 = GwPlayer[i].coin - temp_v0;
        if (var_a0_2 < temp_v1) {
            var_a0_2 = temp_v1;
            var_s1 = i;
        }
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBCoinTakeCreateSound(i, -temp_v0, i == var_s1);
        MBPlayerVibrate(i, 3);
    }

    HuPrcSleep(30);
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}

// NON_MATCHING: one assembler nop after the first sindf call (masked 2); logic checked
#ifdef NON_MATCHING
s32 func_80107A9C_koopa(void) {
    UnkBoard8 *spr;
    void *data;
    s32 i;
    f32 t;
    f32 scale;

    MBWinOpen(0x4212);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    if (MBItemFindEmpty(D_801094F4_koopa) == -1) {
        func_80107724_koopa();
        MBWinOpen(0x4213);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        HuAudFXPlay(0x29E);
        MBMotionShiftSet(D_801094F8_koopa, 4, 0, 20, 0);
        MBModelMotionWait(D_801094F8_koopa);
        MBMotionShiftSet(D_801094F8_koopa, 7, 0, 5, 2);
        HuPrcSleep(10);
        return 1;
    }
    spr = func_800F2C48_shared_board(1, 0);
    data = DataRead(0x21003A);
    spr->model[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(spr->spriteGroup, 0, spr->model[0], 0);
    HuSprAttrReset(spr->spriteGroup, 0, 0xFFFF);
    HuSprAttrSet(spr->spriteGroup, 0, 0x1000);
    HuSprPriSet(spr->spriteGroup, 0, 0x1000);
    func_80054904_main(spr->spriteGroup, 0, 160, -32);
    func_8010775C_koopa();
    for (i = 0; i <= 120; i += 4) {
        func_80054904_main(spr->spriteGroup, 0, 160, i - 32);
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    for (i = 0; i < 70; i += 5) {
        t = i;
        func_80054904_main(spr->spriteGroup, 0, sindf(t) * 90.0f + 160.0f, sindf(i + 90) * 50.0f + 38.0f);
        func_80055458_main(spr->spriteGroup, 0, 256 - i * 2);
        scale = 1.0f - t / 140.0f;
        HuSprScaleSet(spr->spriteGroup, 0, scale, scale);
        HuPrcVSleep();
    }
    func_800F2CA4_shared_board(spr);
    HuAudFXPlay(0x10);
    GwPlayer[D_801094F4_koopa].itemNo[MBItemFindEmpty(D_801094F4_koopa)] = 13;
    MBStatusItemIconSprReinit(D_801094F4_koopa);
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/koopa/3C27C0", func_80107A9C_koopa);
#endif

// NON_MATCHING: an assembler nop after each sindf loop's first call (masked 2, as in func_80107A9C); logic checked
#ifdef NON_MATCHING
s32 func_80107DDC_koopa(void) {
    UnkBoard8 *spr;
    void *data;
    s32 i;
    f32 t;
    f32 scale;

    MBWinOpen(0x4214);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    if (MBItemFindEmpty(D_801094F4_koopa) == -1) {
        func_80107724_koopa();
        MBWinOpen(0x4215);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        HuAudFXPlay(0x29E);
        MBMotionShiftSet(D_801094F8_koopa, 4, 0, 20, 0);
        MBModelMotionWait(D_801094F8_koopa);
        MBMotionShiftSet(D_801094F8_koopa, 7, 0, 5, 2);
        HuPrcSleep(10);
        return 1;
    }
    spr = func_800F2C48_shared_board(1, 0);
    data = DataRead(0x210034);
    spr->model[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(spr->spriteGroup, 0, spr->model[0], 0);
    HuSprAttrReset(spr->spriteGroup, 0, 0xFFFF);
    HuSprAttrSet(spr->spriteGroup, 0, 0x1000);
    HuSprPriSet(spr->spriteGroup, 0, 0x1000);
    func_80054904_main(spr->spriteGroup, 0, 160, -32);
    func_8010775C_koopa();
    for (i = 0; i <= 120; i += 4) {
        func_80054904_main(spr->spriteGroup, 0, 160, i - 32);
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    for (i = 0; i < 70; i += 5) {
        t = i;
        func_80054904_main(spr->spriteGroup, 0, sindf(t) * 90.0f + 160.0f, sindf(i + 90) * 50.0f + 38.0f);
        func_80055458_main(spr->spriteGroup, 0, 256 - i * 2);
        t /= 140.0f;
        scale = 1.0f - t;
        HuSprScaleSet(spr->spriteGroup, 0, scale, scale);
        HuPrcVSleep();
    }
    HuSprAttrSet(spr->spriteGroup, 0, 0x8000);
    HuAudFXPlay(0x10);
    GwPlayer[D_801094F4_koopa].itemNo[MBItemFindEmpty(D_801094F4_koopa)] = 7;
    MBStatusItemIconSprReinit(D_801094F4_koopa);
    if (MBItemFindEmpty(D_801094F4_koopa) != -1 && MBRand(10.0f) == 0) {
        MBWinOpen(0x4216);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        HuSprAttrReset(spr->spriteGroup, 0, 0x8000);
        func_80055458_main(spr->spriteGroup, 0, 256);
        for (i = 0; i <= 10; i++) {
            func_80054904_main(spr->spriteGroup, 0, 160, 88);
            scale = i / 10.0f;
            HuSprScaleSet(spr->spriteGroup, 0, scale, scale);
            HuPrcVSleep();
        }
        HuPrcSleep(15);
        for (i = 0; i < 70; i += 5) {
            t = i;
            func_80054904_main(spr->spriteGroup, 0, sindf(t) * 90.0f + 160.0f, sindf(i + 90) * 50.0f + 38.0f);
            func_80055458_main(spr->spriteGroup, 0, 256 - i * 2);
            scale = 1.0f - t / 140.0f;
            HuSprScaleSet(spr->spriteGroup, 0, scale, scale);
            HuPrcVSleep();
        }
        HuSprAttrSet(spr->spriteGroup, 0, 0x8000);
        HuAudFXPlay(0x10);
        GwPlayer[D_801094F4_koopa].itemNo[MBItemFindEmpty(D_801094F4_koopa)] = 7;
        MBStatusItemIconSprReinit(D_801094F4_koopa);
    }
    func_800F2CA4_shared_board(spr);
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/koopa/3C27C0", func_80107DDC_koopa);
#endif

// event e4
void func_80108360_koopa(s32 file) {
    Object *obj;
    f32 rot;
    f32 scale;
    s32 i;

    MBMotionShiftSet(D_801094F8_koopa, 5, 0, 5, 0);
    obj = MBModelFileCreate(file, -1, 1.0f, 0.0f, NULL);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &D_801094F8_koopa->coords);
    obj->coords.y += 200.0f;
    rot = 0.0f;
    for (scale = 1.0f, i = 0; scale < 12.0f; scale += 0.25) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        if (i == 5) {
            HuAudFXPlay(0x12D);
        }
        i++;
        HuPrcVSleep();
    }
    for (i = 0; scale >= 1.0f; scale -= 0.25) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        if (i == 32) {
            HuAudFXPlay(0x13E);
        }
        i++;
        HuPrcVSleep();
    }
    MBModelKill(obj);
    MBModelMotionWait(D_801094F8_koopa);
    MBMotionShiftSet(D_801094F8_koopa, -1, 0, 5, 2);
}

s32 func_801085E4_koopa(void) {
    MBWinOpen(0x4217);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_80108360_koopa(0xB0036);
    MBWinOpen(0x4218);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_800E4A94_shared_board();
    return 0;
}

s32 func_80108664_koopa(void) {
    MBWinOpen(0x421A);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_80108360_koopa(0xB0037);
    MBWinOpen(0x421B);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_800E4B18_shared_board();
    return 0;
}

s32 func_801086E4_koopa(void) {
    s32 self;
    s32 other;
    s32 first;
    s32 second;
    s32 i;

    MBWinOpen(0x421D);
    self = 0;
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_80108360_koopa(0xB0038);
    other = MBRand(3.0f) + 1;
    MBPlayerMasuSwap(0, other);
    second = -1;
    first = -1;
    for (i = 0; i < 4; i++) {
        if ((i != self) & (i != other)) {
            if (first == -1) {
                first = i;
            } else {
                second = i;
            }
        }
    }
    MBPlayerMasuSwap(first, second);
    MBWinOpen(0x421E);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}

void func_801087F0_koopa(void) {
    s32 total;
    s32 maxGain;
    s32 maxPlayer;
    s32 i;

    for (total = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
        total += GwPlayer[i].coin;
    }
    HuAudFXPlay(0x152);
    total /= 4;
    maxGain = 0;
    maxPlayer = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        func_800F5828_shared_board(i);
        if (maxGain < total - GwPlayer[i].coin) {
            maxGain = total - GwPlayer[i].coin;
            maxPlayer = i;
        }
    }
    for (i = 0; i < 60; i++) {
        MBStatusColorSet(0, i % 5);
        MBStatusColorSet(1, i % 5);
        MBStatusColorSet(2, i % 5);
        MBStatusColorSet(3, i % 5);
        HuPrcVSleep();
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        s32 isMax = (i == maxPlayer);
        MBCoinTakeCreateSound(i, total - GwPlayer[i].coin, isMax);
    }
    for (i = 0; i < 30; i++) {
        MBStatusColorSet(0, i % 5);
        MBStatusColorSet(1, i % 5);
        MBStatusColorSet(2, i % 5);
        MBStatusColorSet(3, i % 5);
        HuPrcVSleep();
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBStatusColorSet(i, GwPlayer[i].color);
        func_800F591C_shared_board(i);
    }
    omDelPrcObj(NULL);
}

s32 func_80108A2C_koopa(void) {
    s32 total;
    s32 i;

    for (total = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
        total += GwPlayer[i].coin;
    }
    if (total < 4) {
        MBWinOpen(0x4220);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        HuAudFXPlay(0x29E);
        MBMotionShiftSet(D_801094F8_koopa, 4, 0, 20, 0);
        MBModelMotionWait(D_801094F8_koopa);
        MBMotionShiftSet(D_801094F8_koopa, 7, 0, 5, 2);
        HuPrcSleep(10);
        return 1;
    }
    MBWinOpen(0x421F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBStatusDispMoveSet(0);
    HuPrcSleep(20);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_801087F0_koopa, 0x300, 0x2000, 0));
    func_80108360_koopa(0xB0039);
    HuPrcChildWait();
    MBWinOpen(0x4221);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}

s32 func_80108BB0_koopa(void) {
    Vec dir;
    s32 i;

    HuPrcSleep(15);
    MBMotionSet(D_801094F8_koopa, 6, 2);
    func_8001C92C_main(D_801094F8_koopa->omObj1->model[0], 2.0f);
    MBVecDirGet(&D_801094F8_koopa->coords, &D_801093BC_koopa, &dir);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&D_801094F8_koopa->rot, &dir, &D_801094F8_koopa->rot, 10));
    HuPrcChildWait();
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&D_801094F8_koopa->coords, &D_801093BC_koopa, &D_801094F8_koopa->coords, 30));
    for (i = 0; i < 30; i++) {
        HuVecCopyXYZ(&D_801094F8_koopa->scale, 2.0f - i / 15.0f, 2.0f - i / 15.0f, 2.0f - i / 15.0f);
        HuPrcVSleep();
    }
    MBModelDispOff(D_801094F8_koopa);
    MBWinOpen(0x4222);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 1;
}

extern s32 D_801094FC_koopa;

void func_80108D2C_koopa(void) {
    s32 failed;

    failed = 0;
    func_8001EF24_main(0x3CA, 0x3E8, 0, 0, 0);
    D_801094F8_koopa = MBModelFileCreate(0xA002F, 9, 0.7f, 1.4f, (u32 *)&D_801093C8_koopa);
    HuVecCopy3F(&D_801094F8_koopa->coords, &D_801093B0_koopa);
    HuVecCopyXYZ(&D_801094F8_koopa->scale, 2.0f, 2.0f, 2.0f);
    if (MBRand(5.0f) == 0) {
        MBMotionSet(D_801094F8_koopa, 7, 2);
        D_801094FC_koopa = 1;
    } else {
        MBMotionSet(D_801094F8_koopa, 1, 2);
        D_801094FC_koopa = 0;
    }
    func_8010699C_koopa();
    func_80107190_koopa();
    HuAudSeqPlay(0x24);
    WipeCreateIn(3, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    if (D_801094FC_koopa == 0) {
        HuPrcSleep(20);
        MBMotionShiftSet(D_801094F8_koopa, -1, 0, 10, 2);
    } else {
        HuPrcSleep(20);
        MBMotionSet(D_801094F8_koopa, 4, 4);
        func_8001C6A8_main(D_801094F8_koopa->omObj1->model[0], 1024.0f);
        while (func_800D9E80_shared_board(D_801094F8_koopa) == 0) {
            HuPrcVSleep();
        }
        MBMotionShiftSet(D_801094F8_koopa, -1, 0, 10, 2);
        HuPrcSleep(10);
        MBMotionShiftSet(D_801094F8_koopa, 1, 0, 5, 2);
        HuPrcSleep(36);
        MBMotionShiftSet(D_801094F8_koopa, -1, 0, 10, 2);
    }
    HuPrcSleep(10);
    HuAudFXPlay(0x29D);
    if (GwPlayer[D_801094F4_koopa].coin == 0) {
        sprintf(D_80109508_koopa, D_801094C0_koopa, func_801076CC_koopa(D_801094F4_koopa));
        MBWinInsertOpen(0x420B, (char *)mbCharNameMesTbl[GwPlayer[D_801094F4_koopa].chr], (u32)D_80109508_koopa, 0, 0, 0);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        func_80107724_koopa();
        MBMotionShiftSet(D_801094F8_koopa, 2, 0, 5, 0);
        func_800EE884_shared_board(D_801094F8_koopa, -1, 2);
        HuPrcSleep(14);
        MBCoinTakeCreate(D_801094F4_koopa, func_801076CC_koopa(D_801094F4_koopa));
        HuPrcSleep(30);
        MBWinOpen(0x420C);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
    } else {
        MBWinInsertOpen(0x420A, (char *)mbCharNameMesTbl[GwPlayer[D_801094F4_koopa].chr], 0, 0, 0, 0);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        MBMotionShiftSet(D_801094F8_koopa, 2, 0, 5, 0);
        func_800EE884_shared_board(D_801094F8_koopa, -1, 2);
        HuPrcSleep(14);
        func_80107648_koopa();
        while (D_80109550_koopa != NULL) {
            HuPrcVSleep();
        }
        failed = ((s32 (*)(void))D_801093EC_koopa[D_80109568_koopa])();
    }
    if (failed == 0) {
        HuAudFXPlay(0x29C);
        MBMotionShiftSet(D_801094F8_koopa, 3, 0, 5, 2);
    }
    HuPrcSleep(20);
    D_800D530C_main = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_801091C4_koopa(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80109320_koopa();
        func_801092A0_koopa();
        func_800F4730_shared_board();
        func_8005F524_main();
        func_800EB09C_shared_board();
        func_800EA694_shared_board();
        omOvlReturnEx(1);
    }
}

void func_80109220_koopa(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(3, 20);
        HuAudSeqFadeOut(60);
        obj->func = func_801091C4_koopa;
    }
}

void func_8010926C_koopa(void) {
    MBModelInit();
    func_800F26E8_shared_board();
    func_800EE700_shared_board();
    func_800F2A20_shared_board();
}

void func_801092A0_koopa(void) {
    func_800F2A34_shared_board();
    func_800EE740_shared_board();
    func_800F27C4_shared_board();
    MBModelClose();
}

void func_801092D4_koopa(void) {
    Hu3DCamInit(1);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    MBBackLoad(2);
    func_800E9344_shared_board(100.0f, 10000.0f);
}

void func_80109320_koopa(void) {
    MBBackKill();
    MBBackClose();
}
