#include "common.h"
#include "game/object.h"
#include "game/hmfman.h"
#include "../ovl_81_name/ovl_81.h"

/* duel res A: the duel-minigame results screen (ovl 0x73). Two players walk in from the sides, the
   loser's coins fly to the winner, and the host lands and rings the bell. */

typedef struct UnkOmData {
    omObjData *unk_00;
    void (*objFunc)(omObjData *);
} UnkOmData;

/* Sprite-model slot (D_800CBB60_main entry; src/14EA0.c unk_800ECDE0). */
typedef struct DuelSprModel {
    /* 0x00 */ s16 model;
    /* 0x02 */ u16 bank;
    /* 0x04 */ s16 step;
    /* 0x06 */ s16 anim;
    /* 0x08 */ s16 time;
    /* 0x0A */ char unk_0A[0x16];
    /* 0x20 */ u8 *unk_20;
} DuelSprModel; // sizeof 0x24

/* Sprite bank animation (src/14EA0.c SprBankAnim) and bank (SprBank). */
typedef struct DuelSprAnim {
    /* 0x00 */ s16 stepCount;
    /* 0x02 */ s16 duration;
    /* 0x04 */ void *steps;
} DuelSprAnim; // sizeof 8

typedef struct DuelSprBank {
    /* 0x00 */ char unk_00[0x0C];
    /* 0x0C */ void *frames;
    /* 0x10 */ DuelSprAnim *anims;
    /* 0x14 */ u16 *palette;
} DuelSprBank; // sizeof 0x18

/* Texture animation slot (D_800D1714_main entry). */
typedef struct DuelTexAnim {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ char unk_0B;
} DuelTexAnim; // sizeof 0xC

/* One flying coin (or the sparkle where it lands). */
typedef struct DuelCoin {
    /* 0x00 */ u8 active;
    /* 0x02 */ u16 spr;
    /* 0x04 */ s32 time;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 z;
    /* 0x14 */ f32 unk_14;
} DuelCoin; // sizeof 0x18

/* Part of a model looked up by name (func_8001D33C_main). */
typedef struct DuelHmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 unk_14;
} DuelHmfPart;

extern DuelSprModel *D_800CBB60_main;
extern DuelSprBank *D_800D408C_main;
extern DuelTexAnim *D_800D1714_main;
extern s32 D_800A178C_main[][6];

void func_800F6550_name_81(s32, s16, s16);
void func_800F7458_name_81(s32, f32, f32);
void func_800F79E8_name_81(s32);
void func_800E1504_name_81(s32, s32, s32, s32);
void func_800F37E0_name_81(s16, s32);
void *func_8001D33C_main(s16, const char *);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
f32 func_80018ACC_main(f32 *, f32 *, f32);
u16 func_80014618_main(s16, u16);
void func_80014714_main(s16, u16);
void func_8004AE00_main(s16, s16);
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void DataClose(void *);

/* .data (defined at the end of the unit) */
extern s8 D_80108E70_mgresultduel;
extern s32 D_80108E74_mgresultduel;
extern s8 D_80108E78_mgresultduel;
extern s32 D_80108E80_mgresultduel;
extern s32 D_80108E84_mgresultduel;
extern s32 D_80108E88_mgresultduel;
extern s32 D_80108E8C_mgresultduel;
extern s32 D_80108E90_mgresultduel;
extern s32 D_80108E94_mgresultduel;
extern s32 D_80108E98_mgresultduel;
extern s8 D_80108E9C_mgresultduel;

/* .bss */
typedef struct DuelSprIds {
    /* 0x00 */ u16 coin;
    /* 0x02 */ u16 sparkle;
} DuelSprIds;
extern DuelSprIds D_80108F30_mgresultduel; /* sprite models of the coins and their sparkles */
extern DuelCoin D_80108F38_mgresultduel[20];
extern DuelCoin D_80109118_mgresultduel[20];
extern s8 D_801092F8_mgresultduel; /* coin direction: the result (-1 left, 1 right) */
extern s32 D_80109300_mgresultduel[3];
extern s16 D_8010930C_mgresultduel;
extern s8 D_80109310_mgresultduel[4]; /* players by group: [0] left, [1] right */
extern s32 D_80109314_mgresultduel;   /* coins won */
extern s8 D_80109318_mgresultduel;    /* -1: left wins, 1: right wins, 2: draw */
extern UnkOmData D_8010931C_mgresultduel; /* coins */
extern UnkOmData D_80109324_mgresultduel; /* host */
extern UnkOmData D_8010932C_mgresultduel; /* right player */
extern UnkOmData D_80109338_mgresultduel; /* bell */
extern UnkOmData D_80109340_mgresultduel; /* left player */

void func_80105E90_mgresultduel(omObjData *);
void func_80105FD4_mgresultduel(omObjData *);
void func_80106054_mgresultduel(void);
void func_80106080_mgresultduel(void);
void func_80106270_mgresultduel(omObjData *);
void func_80106278_mgresultduel(omObjData *);
void func_80106544_mgresultduel(omObjData *);
void func_8010654C_mgresultduel(void);
void func_80106560_mgresultduel(void);
void func_80106574_mgresultduel(omObjData *);
void func_80106730_mgresultduel(void);
void func_80106744_mgresultduel(omObjData *);
void func_80106850_mgresultduel(omObjData *, s32);
void func_80106930_mgresultduel(void);
void func_80106B68_mgresultduel(omObjData *);
void func_80106B70_mgresultduel(omObjData *);
void func_80106BD8_mgresultduel(omObjData *);
void func_80106C3C_mgresultduel(omObjData *);
void func_80106CA0_mgresultduel(omObjData *);
void func_80106D04_mgresultduel(omObjData *);
void func_80106D0C_mgresultduel(omObjData *);
void func_80106F38_mgresultduel(void);
void func_80107170_mgresultduel(omObjData *);
void func_80107178_mgresultduel(omObjData *);
void func_801071E0_mgresultduel(omObjData *);
void func_80107244_mgresultduel(omObjData *);
void func_801072A8_mgresultduel(omObjData *);
void func_801074B0_mgresultduel(omObjData *);
void func_801074B8_mgresultduel(void);
void func_801074DC_mgresultduel(s8);
void func_8010751C_mgresultduel(s8);
void func_80107618_mgresultduel(void);
void func_80107654_mgresultduel(omObjData *);
void func_80107710_mgresultduel(void);
void func_80107AF4_mgresultduel(omObjData *);
void func_80107AFC_mgresultduel(omObjData *);
void func_80107B04_mgresultduel(s32);
void func_80107C74_mgresultduel(s32, s8);
void func_80107CA4_mgresultduel(omObjData *);
void func_80108304_mgresultduel(void);
void func_80108318_mgresultduel(omObjData *);
void func_801084B0_mgresultduel(void);
void func_80108818_mgresultduel(omObjData *);
void func_80108820_mgresultduel(omObjData *);
void func_80108D28_mgresultduel(omObjData *);
void func_80108D30_mgresultduel(s16, s16, s16);
void func_80108E04_mgresultduel(void);
void func_80108E18_mgresultduel(void);
void func_80108E2C_mgresultduel(omObjData *);

const s16 D_80108EA0_mgresultduel[2][2] = { { 30, 40 }, { 194, 40 } };

#ifdef NON_MATCHING
// duelres A: Masked 21: retail loads the coin index with lbu + sign extension and schedules it before the result store.
void func_801059A0_mgresultduel(void) {
    s16 coins[2];
    s8 idx;
    s8 n;
    s8 i;
    s8 grp;

    n = 0;
    for (grp = 0; grp < 4; grp++) {
        for (i = 0; i < 4; i++) {
            if (grp == GwPlayer[i].group) {
                D_80109310_mgresultduel[n] = i;
                n++;
                if (n >= 4) {
                    break;
                }
            }
        }
        if (n >= 4) {
            break;
        }
    }
    omInitObjMan(0x32, 0x14);
    func_800142A0_main(0x78);
    func_800F6390_name_81();
    func_800F6550_name_81(0, D_80108EA0_mgresultduel[0][0], D_80108EA0_mgresultduel[0][1]);
    func_800F6550_name_81(1, D_80108EA0_mgresultduel[1][0], D_80108EA0_mgresultduel[1][1]);
    func_800F7458_name_81(0, 0.0f, 0.0f);
    func_800F7458_name_81(1, 0.0f, 0.0f);
    Hu3DCamInit(1);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0x17);
    func_800E8180_name_81(1000.0f, 10000.0f);
    coins[0] = GwPlayer[D_80109310_mgresultduel[0]].gameCoin + GwPlayer[D_80109310_mgresultduel[0]].bonusCoin;
    coins[1] = GwPlayer[D_80109310_mgresultduel[1]].gameCoin + GwPlayer[D_80109310_mgresultduel[1]].bonusCoin;
    if (coins[0] >= coins[1]) {
        if (coins[0] == coins[1]) {
            D_80109318_mgresultduel = 2;
            D_80109314_mgresultduel = 0;
        } else {
            D_80109318_mgresultduel = -1;
            idx = D_80109310_mgresultduel[0];
            D_80109314_mgresultduel = GwPlayer[D_80109310_mgresultduel[idx]].gameCoin + GwPlayer[idx].bonusCoin;
            if (GwSystem.bank_coins == 0) {
                if (GwSystem.current_turn < 11) {
                    D_80109314_mgresultduel = D_80109314_mgresultduel * 2;
                } else if (GwSystem.current_turn < 20) {
                    D_80109314_mgresultduel = D_80109314_mgresultduel * 3;
                } else {
                    D_80109314_mgresultduel = D_80109314_mgresultduel * 4;
                }
            }
        }
    } else {
        D_80109318_mgresultduel = 1;
        idx = D_80109310_mgresultduel[1];
        D_80109314_mgresultduel = GwPlayer[D_80109310_mgresultduel[idx]].gameCoin + GwPlayer[idx].bonusCoin;
        if (GwSystem.bank_coins == 0) {
            if (GwSystem.current_turn < 11) {
                D_80109314_mgresultduel = D_80109314_mgresultduel * 2;
            } else if (GwSystem.current_turn < 20) {
                D_80109314_mgresultduel = D_80109314_mgresultduel * 3;
            } else {
                D_80109314_mgresultduel = D_80109314_mgresultduel * 4;
            }
        }
    }
    if (coins[0] != coins[1]) {
        if (coins[0] < coins[1]) {
            GwPlayer[D_80109310_mgresultduel[1]].gamePrize += D_80109314_mgresultduel;
        } else {
            GwPlayer[D_80109310_mgresultduel[0]].gamePrize += D_80109314_mgresultduel;
        }
    }
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 50.0f, 100.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    omAddPrcObj(func_80106930_mgresultduel, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80106F38_mgresultduel, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80106080_mgresultduel, 0x1001, 0x2000, 0);
    omAddPrcObj(func_801084B0_mgresultduel, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80107710_mgresultduel, 0x1001, 0x2000, 0);
    omAddObj(0xA, 0, 0, -1, func_80105E90_mgresultduel);
    omAddObj(0xA, 0, 0, -1, func_80105FD4_mgresultduel);
    WipeCreateIn(0xFF, 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F01F0", func_801059A0_mgresultduel);
#endif

void func_80105E90_mgresultduel(omObjData *arg0) {
    s32 state;
    s16 loser;

    state = D_80108E70_mgresultduel;
    switch (state) {
        case 0:
            HuAudSeqPlay(0x16);
            D_80108E74_mgresultduel = 0;
            state++;
            break;
        case 1:
            D_80108E74_mgresultduel++;
            state += D_80108E74_mgresultduel >= 0x14;
            break;
        case 2:
            state++;
            func_801074B8_mgresultduel();
            break;
        case 4:
            if (D_80109318_mgresultduel != 2) {
                loser = (D_80109318_mgresultduel == -1) ? D_80109310_mgresultduel[0] : D_80109310_mgresultduel[1];
                GwPlayer[loser].gameCoin = 0;
                GwPlayer[loser].bonusCoin = 0;
            }
            WipeCreateOut(0, 0x14);
            HuAudSeqFadeOut(0x1E);
            func_8004AB0C_main(0x1E);
            state++;
            break;
        case 5:
            if (WipeStatGet() == 0) {
                func_80106054_mgresultduel();
                omOvlReturnEx(1);
            }
            break;
    }
    D_80108E70_mgresultduel = state;
}

void func_80105FD4_mgresultduel(omObjData *arg0) {
    if (D_800D530C_main == 1) {
        if (D_80108E78_mgresultduel == 0) {
            WipeCreateOut(0, 0x14);
            D_80108E78_mgresultduel = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            func_80106054_mgresultduel();
            omOvlReturnEx(1);
        }
    }
}

void func_80106054_mgresultduel(void) {
    MBDBackKill();
    MBDBackClose();
    func_800F64FC_name_81();
}

void func_80106080_mgresultduel(void) {
    omObjData *temp_v0;

    temp_v0 = omAddObj(0x14, 5, 8, -1, NULL);
    D_80109338_mgresultduel.unk_00 = temp_v0;
    temp_v0->model[1] = func_8000B108_main(0xA011B, 0x2B9);
    func_8001C814_main(temp_v0->model[1], 2, 2);
    Hu3DModelScaleSet(temp_v0->model[1], 0.9f, 0.9f, 0.9f);
    temp_v0->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelScaleSet(temp_v0->model[2], 2.0f, 1.0f, 2.0f);
    func_8000B460_main(temp_v0, 0, 0xA011C);
    func_8000B460_main(temp_v0, 1, 0xA011D);
    func_8000B460_main(temp_v0, 2, 0xA011E);
    func_8000B460_main(temp_v0, 3, 0xA011F);
    func_8000B460_main(temp_v0, 4, 0xA0120);
    func_8001C5B4_main(temp_v0->model[1], temp_v0->motion[4]);
    func_8001C814_main(temp_v0->model[1], 2, 2);
    func_80106850_mgresultduel(temp_v0, -1);
    temp_v0->trans.x = 0.0f;
    temp_v0->trans.y = 0.0f;
    temp_v0->trans.z = 0.0f;
    Hu3DModelPosSet(temp_v0->model[0], temp_v0->trans.x, temp_v0->trans.y, temp_v0->trans.z);
    Hu3DModelPosSet(temp_v0->model[1], 0.0f, 0.0f, 2300.0f);
    Hu3DModelPosSet(temp_v0->model[2], 0.0f, 0.0f, 2300.0f);
    omPrcSetDestructor(0, func_80106544_mgresultduel);
    D_80109338_mgresultduel.objFunc = func_80106270_mgresultduel;
    while (1) {
        D_80109338_mgresultduel.objFunc(temp_v0);
        HuPrcVSleep();
    }
}

void func_80106270_mgresultduel(omObjData *arg0) {
}

#ifdef NON_MATCHING
// duelres A: Masked 0, raw residue: arg0 and i swap s0/s1.
/* The bell is rung: squash and stretch, then the loser reacts and the coins fly. */
void func_80106278_mgresultduel(omObjData *arg0) {
    f32 scale;
    s8 i;

    i = 0;
    scale = 0.9f;
    Hu3DModelScaleSet(arg0->model[1], scale, scale, scale);
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[1]].unk02, 0, 0x1E, 2);
    func_80106850_mgresultduel(arg0, HmfModelData[arg0->motion[1]].unk02);
    HuAudFXPlay(0x20F);
    for (; i < 4; i++) {
        Hu3DModelScaleSet(arg0->model[1], 0.9f, 0.9f - sindf(i * 22.5f) * 0.24f, 0.9f);
        HuPrcVSleep();
    }
    HuPrcSleep(2);
    for (i = 0; i < 4; i++) {
        Hu3DModelScaleSet(arg0->model[1], 0.9f, 0.9f - cosdf(i * 22.5f) * 0.24f, 0.9f);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(arg0->model[1], 0.9f, 0.9f, 0.9f);
    HuAudFXPlay(0x20D);
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[3]].unk02, 0, 0x1E, 2);
    func_80106850_mgresultduel(arg0, HmfModelData[arg0->motion[3]].unk02);
    func_8001C92C_main(arg0->model[1], 2.0f);
    func_801074DC_mgresultduel(D_80109318_mgresultduel);
    func_80107C74_mgresultduel(D_80109314_mgresultduel, D_80109318_mgresultduel);
    D_80109338_mgresultduel.objFunc = func_80106270_mgresultduel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F01F0", func_80106278_mgresultduel);
#endif

void func_80106544_mgresultduel(omObjData *arg0) {
}

void func_8010654C_mgresultduel(void) {
    D_80109338_mgresultduel.objFunc = func_80106278_mgresultduel;
}

void func_80106560_mgresultduel(void) {
    D_80109338_mgresultduel.objFunc = func_80106574_mgresultduel;
}

void func_80106574_mgresultduel(omObjData *arg0) {
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[3]].unk02, 0, 0x1E, 0);
    func_8001C814_main(arg0->model[1], 2, 0);
    func_8001C814_main(arg0->model[1], 4, 4);
    func_80106850_mgresultduel(arg0, HmfModelData[arg0->motion[3]].unk02);
    func_8001C92C_main(arg0->model[1], 1.0f);
    while (HmfModelData[arg0->model[1]].unk40 > 0.0f) {
        HuPrcVSleep();
    }
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[4]].unk02, 0, 0x1E, 2);
    func_80106850_mgresultduel(arg0, HmfModelData[arg0->motion[4]].unk02);
    D_80109338_mgresultduel.objFunc = func_80106270_mgresultduel;
}

void func_80106730_mgresultduel(void) {
    D_80109338_mgresultduel.objFunc = func_80106744_mgresultduel;
}

const char D_80108EC0_mgresultduel[] = "bell"; /* the bell's counter part */

/* The bell's "bell" part shows the counter at GwSystem 0x5C; at 0 it swings round and resets to 5. */
void func_80106744_mgresultduel(omObjData *arg0) {
    DuelHmfPart *part;
    f32 ofs;

    part = func_8001D33C_main(arg0->model[1], D_80108EC0_mgresultduel);
    part->unk_14 = (GwSystem.bank_coins - 5) * 60;
    if (GwSystem.bank_coins == 0) {
        for (ofs = 0.0f; ofs >= -60.0f; ofs -= 2.0f) {
            part->unk_14 = (GwSystem.bank_coins - 5) * 60 + ofs;
            HuPrcVSleep();
        }
        GwSystem.bank_coins = 5;
        HuPrcSleep(10);
    }
    D_80108E70_mgresultduel = 4;
    D_80109338_mgresultduel.objFunc = func_80106270_mgresultduel;
}

#ifdef NON_MATCHING
// duelres A: Instruction-identical, but retail pads it with two nops to 0x80106930: a TU boundary (the unit's .data also pads to 0x80108E80 there); asm keeps the pad.
void func_80106850_mgresultduel(omObjData *arg0, s32 arg1) {
    s16 model = arg0->model[1];

    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80108EC0_mgresultduel, 0x4C, 0x46);
    if ((s16)arg1 >= 0) {
        func_8002FD8C_main(arg0->model[1], (s16)arg1, D_80108EC0_mgresultduel, 0x4C, 0x46);
    }
    ((DuelHmfPart *)func_8001D33C_main(arg0->model[1], D_80108EC0_mgresultduel))->unk_14 = (GwSystem.bank_coins - 5) * 60;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F01F0", func_80106850_mgresultduel);
#endif

void func_80106930_mgresultduel(void) {
    omObjData *temp_v0;
    s16 chr;

    temp_v0 = omAddObj(0x14, 5, 8, -1, NULL);
    D_80109340_mgresultduel.unk_00 = temp_v0;
    chr = GwPlayer[D_80109310_mgresultduel[0]].chr;
    temp_v0->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2B9);
    func_8001C814_main(temp_v0->model[1], 2, 2);
    Hu3DModelPosSet(temp_v0->model[1], -460.0f, 0.0f, 2300.0f);
    temp_v0->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(temp_v0->model[2], -460.0f, -5.0f, 2300.0f);
    Hu3DModelScaleSet(temp_v0->model[2], 1.0f, 1.0f, 1.0f);
    func_8000B460_main(temp_v0, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(temp_v0, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(temp_v0, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(temp_v0, 3, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(temp_v0, 4, func_80017BB8_main(chr, 0x25));
    func_8001C5B4_main(temp_v0->model[1], temp_v0->motion[0]);
    func_8001C814_main(temp_v0->model[1], 2, 2);
    temp_v0->trans.x = 0.0f;
    temp_v0->trans.y = 0.0f;
    temp_v0->trans.z = 0.0f;
    Hu3DModelPosSet(temp_v0->model[0], temp_v0->trans.x, temp_v0->trans.y, temp_v0->trans.z);
    omPrcSetDestructor(0, func_80106D04_mgresultduel);
    D_80109340_mgresultduel.objFunc = func_80106B68_mgresultduel;
    while (1) {
        D_80109340_mgresultduel.objFunc(temp_v0);
        HuPrcVSleep();
    }
}

void func_80106B68_mgresultduel(omObjData *arg0) {
}

void func_80106B70_mgresultduel(omObjData *arg0) {
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[4]].unk02, 0, 0x1E, 2);
    D_80109340_mgresultduel.objFunc = func_80106B68_mgresultduel;
}

void func_80106BD8_mgresultduel(omObjData *arg0) {
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[2]].unk02, 0, 0x1E, 0);
    D_80109340_mgresultduel.objFunc = func_80107654_mgresultduel;
}

void func_80106C3C_mgresultduel(omObjData *arg0) {
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[3]].unk02, 0, 0x1E, 0);
    D_80109340_mgresultduel.objFunc = func_80106B68_mgresultduel;
}

void func_80106CA0_mgresultduel(omObjData *arg0) {
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[3]].unk02, 0, 0x1E, 0);
    D_80109340_mgresultduel.objFunc = func_80107654_mgresultduel;
}

void func_80106D04_mgresultduel(omObjData *arg0) {
}

/* Left player walks in and turns to face the camera. */
void func_80106D0C_mgresultduel(omObjData *arg0) {
    f32 x;
    f32 rot;

    Hu3DModelRotSet(arg0->model[1], 0.0f, 90.0f, 0.0f);
    func_8001C5B4_main(arg0->model[1], arg0->motion[1]);
    func_8001C814_main(arg0->model[1], 2, 2);
    for (x = 0.0f; x < 240.0f; x += 16.0f) {
        Hu3DModelPosSet(arg0->model[1], x + -460.0f, 0.0f, 2300.0f);
        Hu3DModelPosSet(arg0->model[2], x + -460.0f, -5.0f, 2300.0f);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(arg0->model[1], rot = -220.0f, 0.0f, 2300.0f);
    Hu3DModelPosSet(arg0->model[2], rot, -5.0f, 2300.0f);
    for (rot = 90.0f; rot >= 0.0f; rot -= 8.0f) {
        Hu3DModelRotSet(arg0->model[1], 0.0f, rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[0]].unk02, 0, 0x1E, 2);
    D_80109340_mgresultduel.objFunc = func_80106B68_mgresultduel;
    if (D_80109318_mgresultduel != 2) {
        func_80108E04_mgresultduel();
    } else {
        func_80107618_mgresultduel();
    }
}

void func_80106F38_mgresultduel(void) {
    omObjData *temp_v0;
    s16 chr;

    temp_v0 = omAddObj(0x14, 5, 8, -1, NULL);
    D_8010932C_mgresultduel.unk_00 = temp_v0;
    chr = GwPlayer[D_80109310_mgresultduel[1]].chr;
    temp_v0->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2B9);
    func_8001C814_main(temp_v0->model[1], 2, 2);
    Hu3DModelPosSet(temp_v0->model[1], 460.0f, 0.0f, 2300.0f);
    temp_v0->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(temp_v0->model[2], 460.0f, -5.0f, 2300.0f);
    Hu3DModelScaleSet(temp_v0->model[2], 1.0f, 1.0f, 1.0f);
    func_8000B460_main(temp_v0, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(temp_v0, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(temp_v0, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(temp_v0, 3, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(temp_v0, 4, func_80017BB8_main(chr, 0x25));
    func_8001C5B4_main(temp_v0->model[1], temp_v0->motion[0]);
    func_8001C814_main(temp_v0->model[1], 2, 2);
    temp_v0->trans.x = 0.0f;
    temp_v0->trans.y = 0.0f;
    temp_v0->trans.z = 0.0f;
    Hu3DModelPosSet(temp_v0->model[0], temp_v0->trans.x, temp_v0->trans.y, temp_v0->trans.z);
    omPrcSetDestructor(0, func_801074B0_mgresultduel);
    D_8010932C_mgresultduel.objFunc = func_80107170_mgresultduel;
    while (1) {
        D_8010932C_mgresultduel.objFunc(temp_v0);
        HuPrcVSleep();
    }
}

void func_80107170_mgresultduel(omObjData *arg0) {
}

void func_80107178_mgresultduel(omObjData *arg0) {
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[4]].unk02, 0, 0x1E, 2);
    D_8010932C_mgresultduel.objFunc = func_80107170_mgresultduel;
}

void func_801071E0_mgresultduel(omObjData *arg0) {
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[2]].unk02, 0, 0x1E, 0);
    D_8010932C_mgresultduel.objFunc = func_80107654_mgresultduel;
}

void func_80107244_mgresultduel(omObjData *arg0) {
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[3]].unk02, 0, 0x1E, 0);
    D_8010932C_mgresultduel.objFunc = func_80107170_mgresultduel;
}

/* Right player walks in and turns to face the camera. */
void func_801072A8_mgresultduel(omObjData *arg0) {
    f32 x;
    f32 rot;

    Hu3DModelRotSet(arg0->model[1], 0.0f, -90.0f, 0.0f);
    func_8001C5B4_main(arg0->model[1], arg0->motion[1]);
    func_8001C814_main(arg0->model[1], 2, 2);
    for (x = 0.0f; x < 240.0f; x += 16.0f) {
        Hu3DModelPosSet(arg0->model[1], 460.0f - x, 0.0f, 2300.0f);
        Hu3DModelPosSet(arg0->model[2], 460.0f - x, -5.0f, 2300.0f);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(arg0->model[1], rot = 220.0f, 0.0f, 2300.0f);
    Hu3DModelPosSet(arg0->model[2], rot, -5.0f, 2300.0f);
    for (rot = 90.0f; rot >= 0.0f; rot -= 8.0f) {
        Hu3DModelRotSet(arg0->model[1], 0.0f, -rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    func_8001C624_main(arg0->model[1], HmfModelData[arg0->motion[0]].unk02, 0, 0x1E, 2);
    D_8010932C_mgresultduel.objFunc = func_80107170_mgresultduel;
}

void func_801074B0_mgresultduel(omObjData *arg0) {
}

void func_801074B8_mgresultduel(void) {
    D_80109340_mgresultduel.objFunc = func_80106D0C_mgresultduel;
    D_8010932C_mgresultduel.objFunc = func_801072A8_mgresultduel;
}

/* The loser reacts while the coins fly. */
void func_801074DC_mgresultduel(s8 arg0) {
    if (arg0 == -1) {
        D_80109340_mgresultduel.objFunc = func_80106B70_mgresultduel;
    } else {
        D_8010932C_mgresultduel.objFunc = func_80107178_mgresultduel;
    }
}

/* Win / lose voices and poses. */
void func_8010751C_mgresultduel(s8 arg0) {
    HuPrcSleep(2);
    if (arg0 == -1) {
        func_8004AE00_main(func_8004ACE0_main(0x28F, D_80109310_mgresultduel[0]), 0x20);
        func_8004AE00_main(func_8004ACE0_main(0x26B, D_80109310_mgresultduel[1]), 0x60);
        D_80109340_mgresultduel.objFunc = func_80106BD8_mgresultduel;
        D_8010932C_mgresultduel.objFunc = func_80107244_mgresultduel;
    } else {
        func_8004AE00_main(func_8004ACE0_main(0x26B, D_80109310_mgresultduel[0]), 0x20);
        func_8004AE00_main(func_8004ACE0_main(0x28F, D_80109310_mgresultduel[1]), 0x60);
        D_80109340_mgresultduel.objFunc = func_80106C3C_mgresultduel;
        D_8010932C_mgresultduel.objFunc = func_801071E0_mgresultduel;
    }
    func_80108E18_mgresultduel();
}

void func_80107618_mgresultduel(void) {
    HuPrcSleep(2);
    D_80109340_mgresultduel.objFunc = func_80106CA0_mgresultduel;
    D_8010932C_mgresultduel.objFunc = func_80107244_mgresultduel;
}

/* Wait for the win motion to end, then show the coins won. Retail reads the frame once: if the
   motion has already reached its end here this waits forever. */
void func_80107654_mgresultduel(omObjData *arg0) {
    f32 frame;
    f32 end;

    frame = HmfModelData[arg0->model[1]].unk40;
    end = D_800CCF58_main[HmfModelData[arg0->model[1]].unk02].unk02;
    while (end <= frame) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80108304_mgresultduel();
    while (1) {
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
// duelres A: Masked 18: retail rematerialises &D_80108F30_mgresultduel after each call; this keeps it in a saved register.
void func_80107710_mgresultduel(void) {
    omObjData *obj;
    void *data;
    s8 i;

    obj = omAddObj(0x14, 0x2A, 0, -1, NULL);
    D_8010931C_mgresultduel.unk_00 = obj;
    data = DataRead(0x210026);
    D_80108F30_mgresultduel.coin = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[D_80108F30_mgresultduel.coin].model, 0x70000000, 0x70000000);
    for (i = 0; i < 20; i++) {
        D_80108F38_mgresultduel[i].active = 0;
        D_80108F38_mgresultduel[i].spr = func_80014618_main(D_80108F30_mgresultduel.coin, 8);
        D_80108F38_mgresultduel[i].time = 0;
        obj->model[i + 1] = D_800CBB60_main[D_80108F38_mgresultduel[i].spr].model;
        Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        func_8001C8A8_main(obj->model[i + 1], 1);
        func_8001C92C_main(obj->model[i + 1], 2.0f);
        /* retail scales sprite slot i + 1's model, not this coin's */
        Hu3DModelScaleSet(D_800CBB60_main[i + 1].model, 1.5f, 1.5f, 1.5f);
    }
    data = DataRead(0xC);
    D_80108F30_mgresultduel.sparkle = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[D_80108F30_mgresultduel.sparkle].model, 0x70000000, 0x70000000);
    Hu3DModelScaleSet(D_800CBB60_main[D_80108F30_mgresultduel.sparkle].model, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 20; i++) {
        D_80109118_mgresultduel[i].active = 0;
        D_80109118_mgresultduel[i].spr = func_80014618_main(D_80108F30_mgresultduel.sparkle, 8);
        D_80109118_mgresultduel[i].time = 0;
        obj->model[i + 21] = D_800CBB60_main[D_80109118_mgresultduel[i].spr].model;
        Hu3DModelPosSet(obj->model[i + 21], 0.0f, 400.0f, 0.0f);
        func_8001C8A8_main(obj->model[i + 21], 1);
        func_8001C92C_main(obj->model[i + 21], 1.0f);
        Hu3DModelScaleSet(D_800CBB60_main[i + 21].model, 3.0f, 3.0f, 3.0f);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_80107AFC_mgresultduel);
    D_8010931C_mgresultduel.objFunc = func_80107AF4_mgresultduel;
    while (1) {
        D_8010931C_mgresultduel.objFunc(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F01F0", func_80107710_mgresultduel);
#endif

void func_80107AF4_mgresultduel(omObjData *arg0) {
}

void func_80107AFC_mgresultduel(omObjData *arg0) {
}

void func_80107B04_mgresultduel(s32 arg0) {
    omObjData *obj;
    DuelCoin *coin;
    s32 n;
    s8 i;

    obj = D_8010931C_mgresultduel.unk_00;
    if (arg0 > 0) {
        n = 50;
        if (arg0 < 51) {
            n = arg0;
        }
        arg0 = n;
        D_80108E84_mgresultduel = arg0;
        D_80108E88_mgresultduel = 0;
        D_80108E80_mgresultduel = 0;
        D_80108E8C_mgresultduel = 0;
        if (arg0 <= 100) {
            D_80108E90_mgresultduel = arg0;
        } else {
            D_80108E90_mgresultduel = 100;
        }
        D_80108E94_mgresultduel = 4;
        for (i = 0; i < 20; i++) {
            D_80108F38_mgresultduel[i].active = 0;
            D_80108F38_mgresultduel[i].time = 0;
            coin = &D_80108F38_mgresultduel[i];
            D_80108F38_mgresultduel[i].x = coin->y = coin->z = 0.0f;
            D_80108F38_mgresultduel[i].unk_14 = -10.0f;
            func_8001C258_main(obj->model[i + 1], 4, 4);
            Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        }
    }
}

void func_80107C74_mgresultduel(s32 coins, s8 result) {
    D_801092F8_mgresultduel = result;
    func_80107B04_mgresultduel(coins);
    D_8010931C_mgresultduel.objFunc = func_80107CA4_mgresultduel;
}

#ifdef NON_MATCHING
// duelres A: Masked 39: retail duplicates the coin index (sll s0) into both arms of the burst choice; register allocation follows.
/* Throw the coins from the loser to the winner, one or two every few frames. */
void func_80107CA4_mgresultduel(omObjData *arg0) {
    DuelSprModel *spr;
    DuelSprAnim *anim;
    f32 x;
    f32 y;
    f32 z;
    f32 t;
    s32 burst;
    s8 thrown;
    s8 i;
    s8 winner;

    if (D_80108E88_mgresultduel < D_80108E90_mgresultduel) {
        thrown = 0;
        for (i = 0; i < 20; i++) {
            if (D_80108F38_mgresultduel[i].active != 1 && D_80108E80_mgresultduel % D_80108E94_mgresultduel == 0) {
                spr = &D_800CBB60_main[D_80108F38_mgresultduel[i].spr];
                anim = &D_800D408C_main[spr->bank].anims[spr->anim];
                func_8001C258_main(arg0->model[i + 1], 4, 0);
                if (D_80108E84_mgresultduel < 20) {
                    burst = 1;
                } else {
                    burst = (rand8() & 1) + 1;
                }
                Hu3DModelPosSet(arg0->model[i + 1], 0.0f, 400.0f, 0.0f);
                D_80108F38_mgresultduel[i].x = (u8)(rand8() % 40) - 20;
                D_80108F38_mgresultduel[i].y = (u8)(rand8() % 40) - 20;
                D_80108F38_mgresultduel[i].z = (u8)(rand8() % 40) - 20;
                D_80108F38_mgresultduel[i].active = 1;
                D_80108F38_mgresultduel[i].time = 0;
                spr->step = rand8() % anim->stepCount;
                spr->time = 0;
                if (++D_80108E88_mgresultduel >= D_80108E90_mgresultduel) {
                    break;
                }
                if (++thrown >= burst) {
                    break;
                }
            }
        }
    } else if (D_80108E9C_mgresultduel == 0) {
        func_80106560_mgresultduel();
        D_80108E9C_mgresultduel = 1;
    }
    for (i = 0; i < 20; i++) {
        if (D_80108F38_mgresultduel[i].active) {
            t = D_80108F38_mgresultduel[i].time;
            x = t * 8.8f + D_80108F38_mgresultduel[i].x;
            y = sindf(t * 7.2f) * 170.0f + D_80108F38_mgresultduel[i].y + 170.0f;
            z = D_80108F38_mgresultduel[i].z + 2300.0f;
            Hu3DModelPosSet(arg0->model[i + 1], x * D_801092F8_mgresultduel, y, z);
            D_80108F38_mgresultduel[i].time++;
            if (D_80108F38_mgresultduel[i].time >= 25) {
                D_80108E8C_mgresultduel++;
                D_80108F38_mgresultduel[i].active = 0;
                func_8001C258_main(arg0->model[i + 1], 4, 4);
                func_8001C258_main(arg0->model[i + 21], 4, 0);
                Hu3DModelPosSet(arg0->model[i + 21], x * D_801092F8_mgresultduel, y, z);
                func_8001C6A8_main(arg0->model[i + 21], 0.0f);
                func_80014714_main(D_80109118_mgresultduel[i].spr, 0);
                HuAudFXPlay(9);
                if (D_80108E98_mgresultduel == 0) {
                    if (D_80109318_mgresultduel == -1) {
                        winner = D_80109310_mgresultduel[0];
                    } else {
                        winner = D_80109310_mgresultduel[1];
                    }
                    if (!(GwPlayer[winner].stat & 1)) {
                        omVibrate(winner, 5, 0, 5);
                    }
                    D_80108E98_mgresultduel = 1;
                }
            }
        }
    }
    D_80108E80_mgresultduel++;
    if (D_80108E8C_mgresultduel >= D_80108E84_mgresultduel) {
        D_80108E9C_mgresultduel = 0;
        func_8010751C_mgresultduel(D_80109318_mgresultduel);
        D_8010931C_mgresultduel.objFunc = func_80107AF4_mgresultduel;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F01F0", func_80107CA4_mgresultduel);
#endif

void func_80108304_mgresultduel(void) {
    D_8010931C_mgresultduel.objFunc = func_80108318_mgresultduel;
}

#ifdef NON_MATCHING
// duelres A (masked 6, 1 short): retail sign-extends the winner again for each call (s8 for the first, s16 for the second); tried winner s32/s16/u16/u8 and an s8 prototype (H1)
/* Show the coins won over the winner's head and add them. */
void func_80108318_mgresultduel(omObjData *arg0) {
    Vec pos;
    Vec2f screen;
    omObjData *winObj;
    s8 winner;

    func_800F79E8_name_81(-1);
    if (D_80109318_mgresultduel != 2) {
        if (D_80109318_mgresultduel == -1) {
            winObj = D_80109340_mgresultduel.unk_00;
        } else {
            winObj = D_8010932C_mgresultduel.unk_00;
        }
        pos.x = HmfModelData[winObj->model[1]].pos.x;
        pos.y = HmfModelData[winObj->model[1]].pos.y + 120.0f;
        pos.z = HmfModelData[winObj->model[1]].pos.z;
        Hu3DCam3DToScreen(0, &pos, &screen);
        func_800E0CEC_name_81();
        if (D_80109318_mgresultduel == -1) {
            winner = D_80109310_mgresultduel[0];
        } else {
            winner = D_80109310_mgresultduel[1];
        }
        func_800E1504_name_81(winner, D_80109314_mgresultduel, screen.x, screen.y);
        HuPrcSleep(0x14);
        func_800F37E0_name_81(winner, D_80109314_mgresultduel);
        HuPrcSleep(0x14);
        func_800E0E38_name_81();
    } else {
        HuPrcSleep(0x28);
    }
    func_80106730_mgresultduel();
    D_8010931C_mgresultduel.objFunc = func_80107AF4_mgresultduel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F01F0", func_80108318_mgresultduel);
#endif

void func_801084B0_mgresultduel(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 5, 6, -1, NULL);
    D_80109324_mgresultduel.unk_00 = obj;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    func_8001C814_main(obj->model[1], 2, 2);
    data = DataRead(0xA007E);
    D_80109300_mgresultduel[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80109300_mgresultduel[0], 1, 0);
    func_80032FF8_main((s16)D_80109300_mgresultduel[0], 0);
    D_8010930C_mgresultduel =
        func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80109300_mgresultduel[0], 0, "c204n_0_DEF");
    D_80109300_mgresultduel[0] = D_800D1714_main[D_80109300_mgresultduel[0]].unk_00;
    data = DataRead(0xA0081);
    D_80109300_mgresultduel[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0084);
    D_80109300_mgresultduel[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80108D30_mgresultduel(obj->model[1], D_8010930C_mgresultduel, D_80109300_mgresultduel[0]);
    obj->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], 0.0f, -5.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0xA0077);
    func_8000B460_main(obj, 2, 0xA0078);
    func_8000B460_main(obj, 3, 0xA007A);
    func_8000B460_main(obj, 4, 0xA007B);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], 700.0f, 300.0f, 1600.0f);
    Hu3DModelPosSet(obj->model[2], 700.0f, -5.0f, 1600.0f);
    omPrcSetDestructor(0, func_80108D28_mgresultduel);
    D_80109324_mgresultduel.objFunc = func_80108818_mgresultduel;
    while (1) {
        D_80109324_mgresultduel.objFunc(obj);
        HuPrcVSleep();
    }
}

void func_80108818_mgresultduel(omObjData *arg0) {
}

/* The host's flight path: control points and their knot times. */
const f32 D_80108ED4_mgresultduel[5][3] = {
    { 1000.0f, 2000.0f, 1500.0f }, { 600.0f, 600.0f, 1800.0f }, { 300.0f, 50.0f, 2000.0f },
    { 0.0f, 300.0f, 2300.0f },     { 0.0f, 800.0f, 2400.0f },
};
const f32 D_80108F10_mgresultduel[5] = { 0.0f, 5.0f, 15.0f, 40.0f, 80.0f };

#ifdef NON_MATCHING
// duelres A (masked 7, right count): retail loads pos.y after arg0->model[1] in the three hop calls (f0/f2 swapped); tried a product temporary (H1)
/* The host flies in along the path, lands, hops and rings the bell. */
void func_80108820_mgresultduel(omObjData *arg0) {
    f32 ctrl[4];
    Vec pos;
    omObjData *bell;
    f32 t;
    f32 x;
    f32 z;
    s32 rung;
    s32 seg;
    s8 j;
    s8 k;

    bell = D_80109338_mgresultduel.unk_00;
    rung = 0;
    x = 700.0f;
    z = 1600.0f;
    Hu3DModelPosSet(arg0->model[1], x, 300.0f, z);
    seg = 0;
    Hu3DModelPosSet(arg0->model[2], x, -0.5f, z);
    HuPrcVSleep();
    t = 0.0f;
    while (1) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 4; k++) {
                ctrl[k] = D_80108ED4_mgresultduel[k + seg][j];
            }
            ((f32 *)&pos)[j] = func_80018ACC_main(ctrl, (f32 *)&D_80108F10_mgresultduel[seg], t);
        }
        t += 1.0f;
        if (D_80108F10_mgresultduel[seg + 2] <= t) {
            seg++;
            if (seg + 3 >= 5) {
                break;
            }
        }
        Hu3DModelPosSet(arg0->model[1], pos.x, pos.y, pos.z);
        Hu3DModelPosSet(arg0->model[2], pos.x, -0.5f, pos.z);
        HuPrcVSleep();
    }
    x = pos.x;
    z = pos.z;
    Hu3DModelPosSet(arg0->model[1], x, pos.y, z);
    Hu3DModelPosSet(arg0->model[2], x, -0.5f, z);
    func_80108D30_mgresultduel(arg0->model[1], D_8010930C_mgresultduel, D_80109300_mgresultduel[1]);
    HuPrcSleep(12);
    func_8001C624_main(arg0->model[0], HmfModelData[arg0->motion[3]].unk02, 0, 10, 0);
    for (j = 0; j < 6; j++) {
        Hu3DModelPosSet(arg0->model[1], x, pos.y - sindf(j * 15.0f) * 120.0f, z);
        if ((j >= 2) & (rung != 1)) {
            rung = 1;
            func_8010654C_mgresultduel();
        }
        HuPrcVSleep();
    }
    HuPrcSleep(2);
    func_8001C624_main(arg0->model[0], HmfModelData[arg0->motion[0]].unk02, 0, 0x1E, 2);
    for (j = 0; j < 12; j++) {
        Hu3DModelPosSet(arg0->model[1], x, pos.y - cosdf(j * 7.5f) * 120.0f, z);
        HuPrcVSleep();
    }
    x = HmfModelData[bell->model[1]].pos.x;
    z = HmfModelData[bell->model[1]].pos.z;
    Hu3DModelPosSet(arg0->model[1], x, pos.y, z);
    Hu3DModelPosSet(arg0->model[2], x, -0.5f, z);
    HuPrcVSleep();
    for (j = 0; j < 10; j++) {
        Hu3DModelPosSet(arg0->model[1], x, sindf(j * 9.0f) * 50.0f + pos.y, z);
        HuPrcVSleep();
    }
    D_80109324_mgresultduel.objFunc = func_80108818_mgresultduel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F01F0", func_80108820_mgresultduel);
#endif

void func_80108D28_mgresultduel(omObjData *arg0) {
}

void func_80108D30_mgresultduel(s16 model, s16 anim, s16 tex) {
    DuelTexAnim *slot;

    if (anim >= 0) {
        if (tex == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            slot = &D_800D1714_main[anim];
            slot->unk_00 = tex;
            slot->unk_04 = 0;
            slot->unk_0A = 0;
            slot->unk_06 = 0;
            slot->unk_02 = 0;
        }
    }
}

void func_80108E04_mgresultduel(void) {
    D_80109324_mgresultduel.objFunc = func_80108820_mgresultduel;
}

void func_80108E18_mgresultduel(void) {
    D_80109324_mgresultduel.objFunc = func_80108E2C_mgresultduel;
}

void func_80108E2C_mgresultduel(omObjData *arg0) {
    func_80108D30_mgresultduel(arg0->model[1], D_8010930C_mgresultduel, D_80109300_mgresultduel[2]);
    D_80109324_mgresultduel.objFunc = func_80108818_mgresultduel;
}

/* .data (80108E70). Retail has 4 zero bytes after D_80108E78_mgresultduel: the .data side of the
   TU boundary that pads the text to 0x80106930 (see func_80106850_mgresultduel). */
s8 D_80108E70_mgresultduel = 0;  /* results state */
s32 D_80108E74_mgresultduel = 0; /* state timer */
s8 D_80108E78_mgresultduel = 0;  /* reset wipe started */
s32 D_80108E7C_mgresultduel = 0; /* unreferenced (file padding) */
s32 D_80108E80_mgresultduel = 0; /* coin burst frame */
s32 D_80108E84_mgresultduel = 0; /* coins to throw */
s32 D_80108E88_mgresultduel = 0; /* coins thrown */
s32 D_80108E8C_mgresultduel = 0; /* coins landed */
s32 D_80108E90_mgresultduel = 0; /* throw cap */
s32 D_80108E94_mgresultduel = 0; /* frames between throws */
s32 D_80108E98_mgresultduel = 0; /* winner rumbled */
s8 D_80108E9C_mgresultduel = 0;  /* last-coin cue given */
