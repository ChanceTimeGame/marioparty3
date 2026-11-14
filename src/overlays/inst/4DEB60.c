#include "common.h"

void func_80105D9C_inst(omObjData *);  /* extern */
void func_801061EC_inst(void);         /* extern */
void func_80106310_inst(omObjData *);  /* extern */
void func_80106388_inst(void);         /* extern */
void func_801063F4_inst(void);
s32 func_80106418_inst(Vec *posA, Vec *posB, Vec *atA, Vec *atB, s32 frames);
void func_80107BE4_inst(void);
s32 func_80107E20_inst(void);
void func_80107E98_inst(void);
void func_8010B0FC_inst(void);
s8 func_8010B118_inst(void);
u16 func_8010CA74_inst(s32, s16);
void func_8010CFF4_inst(void);
void func_8010674C_inst(omObjData *);  /* extern */
void func_801067CC_inst(void);         /* extern */
void func_80106850_inst(Vec *, Vec *); /* extern */
void func_80106898_inst(void);         /* extern */
void func_80106EB4_inst(void);         /* extern */
void func_80107308_inst(void);         /* extern */
void func_80107470_inst(void);         /* extern */
void func_80108350_inst(void);         /* extern */
void func_801094B0_inst(void);         /* extern */
void func_80109A90_inst(void);         /* extern */
void func_8010A1D0_inst(void);         /* extern */
void func_8010B990_inst(void);         /* extern */

extern s8 D_8010D400_inst[7];
extern s8 D_8010D407_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D40A_inst;
extern s8 D_8010D40B_inst;
extern s8 D_8010D411_inst;
extern s8 D_8010D404_inst;
extern s8 D_8010D405_inst;
extern s8 D_8010D406_inst;
extern s8 D_8010D409_inst;
extern u32 D_8010D43C_inst;
extern s32 D_8010D440_inst;
extern Vec D_8010D444_inst[4]; /* camera positions */
extern Vec D_8010D474_inst[4]; /* camera targets */
extern s32 D_8010DC00_inst;
extern s16 D_8010DC02_inst; /* low half of D_8010DC00_inst */
extern s8 D_8010D5B1_inst;
extern s8 D_8010D4A8_inst;
extern u32 D_8010D4AC_inst;
extern u8 D_8010D40C_inst[5]; /* item minigame: the items on offer */
extern u8 D_8010D4B0_inst[8];
extern u8 D_8010D4B8_inst[8];
extern u16 D_800A11D0_main[6];
extern s16 D_800A11DC_main[5];
extern const u8 D_8010D6B0_inst[8][5];
extern const s8 D_8010D6D8_inst[4][3];
extern const u8 D_8010D6E4_inst[8][5];
extern const s8 D_8010D70C_inst[4][3];
extern const u8 D_8010D718_inst[10];
extern const s8 D_8010D724_inst[8];
s32 BoardGetTurnTier(s32 turn);
s32 BoardPlayerRankCalc(s32 player);
extern f32 D_8010D414_inst;
extern Vec D_8010D418_inst;
extern Vec D_8010D424_inst;
extern Vec D_8010D430_inst;

/* The word before each MinigameTable entry (D_800A6D44_main), read with the table's 0x14 stride. */
typedef struct InstMgTableHead {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ char unk4[0x10];
} InstMgTableHead;
extern InstMgTableHead D_800A6D40_main[];
extern f32 D_800CB890_main;
extern f32 D_800CE17C_main[];
extern f32 D_800D5210_main;
extern const s32 D_8010D658_inst[];
void func_8000BC48_main(u16, s32);
void func_80037258_main(void);
void func_8005F524_main(void);

void func_801059A0_inst(void) {
    void (*procFunc)(void) = NULL;
    s16 var_a1 = 0;
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            D_8010D400_inst[var_a1] = j;
            var_a1++;

            if (var_a1 >= 4) {
                break;
            }
        }
        if (var_a1 >= 4) {
            break;
        }
    }
    D_8010D40B_inst = GwSystem.minigame_index - 1;
    D_8010D40A_inst = D_800A6D44_main[D_8010D40B_inst].minigameType;

    if (_CheckFlag(0xF) != 0) {
        D_8010D407_inst = 1;
        D_8010D408_inst = 1;
    } else {
        D_8010D407_inst = 0;
        if ((GWMgUnlockCheck(D_8010D40B_inst)) != 0) {
            D_8010D408_inst = 1;
        }
    }

    GWMgUnlockSet(-1);
    _ClearFlag(0xF);
    func_80106EB4_inst();
    func_80106898_inst();
    func_80107308_inst();

    if ((GwSystem.show_minigame_explanations == 1) || (D_8010D40A_inst == 6)) {
        func_801061EC_inst();
        return;
    }

    Hu3DAnimInit(1);
    omInitObjMan(0x1E, 0x1E);
    func_8005A6B0_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 15.0f, 500.0f, 8000.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, func_8010674C_inst), 0xA0U);
    func_800142A0_main(0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    omAddPrcObj(func_80107470_inst, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B990_inst, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010A1D0_inst, 0x1001, 0x1000, 0);

    switch (D_8010D40A_inst) {
        case 5:
            procFunc = func_801094B0_inst;
            D_8010D411_inst = 1;
            break;
        case 4:
            if (omovlhisidx <= 0) {
                break;
            }
            if (GwSystem.playMode & 2) {
                procFunc = func_80108350_inst;
                D_8010D411_inst = 0;
                break;
            }
        case 3:
            procFunc = func_80109A90_inst;
            D_8010D411_inst = 2;
            break;
        case 0:
        case 1:
        case 2:
        case 6:
        case 7:
        case 8:
        default:
            procFunc = func_80108350_inst;
            D_8010D411_inst = 0;
            break;
    }

    omAddPrcObj(procFunc, 0x1001, 0x800, 0);
    omAddObj(0, 0, 0, -1, func_80105D9C_inst);
    omAddObj(0, 0, 0, -1, func_80106310_inst);
    func_80106388_inst();
    func_80106850_inst(&D_8010D444_inst[2], &D_8010D474_inst[2]);
    func_801067CC_inst();
    WipeCreateIn(0xFF, 0x10);
}

/* Main state machine of the instruction screen: camera moves in, the pages are shown, and
   once a player confirms the camera moves out and the minigame starts. */
void func_80105D9C_inst(omObjData *arg0) {
    s32 i;

    switch (D_8010D43C_inst) {
        case 0:
            HuAudSeqPlay(0x10);
            func_801067CC_inst();
            D_8010DC00_inst = 0;
            D_8010D405_inst = 0;
            if (D_8010D408_inst != 0) {
                D_8010D418_inst.x = D_8010D444_inst[2].x;
                D_8010D418_inst.y = D_8010D444_inst[2].y;
                D_8010D418_inst.z = D_8010D444_inst[2].z;
                D_8010D424_inst.x = D_8010D474_inst[2].x;
                D_8010D424_inst.y = D_8010D474_inst[2].y;
                D_8010D424_inst.z = D_8010D474_inst[2].z;
                D_8010D430_inst.x = 0.0f;
                D_8010D430_inst.y = 1.0f;
                D_8010D430_inst.z = -0.000001f;
                D_8010D43C_inst = 6;
                break;
            }
            D_8010D43C_inst++;
            break;
        case 1:
            if (++D_8010DC00_inst >= 21) {
                func_80107E98_inst();
                D_8010D43C_inst += 2;
            }
            break;
        case 2:
            if (func_80106418_inst(&D_8010D444_inst[0], &D_8010D444_inst[1], &D_8010D474_inst[0], &D_8010D474_inst[1], 5) != 0) {
                func_80107E98_inst();
                D_8010D43C_inst++;
            }
            break;
        case 3:
            if (func_80107E20_inst() != 0) {
                func_8010B0FC_inst();
                D_8010D43C_inst++;
            }
            break;
        case 4:
            if (func_8010B118_inst() != 0) {
                D_8010D43C_inst++;
            }
            break;
        case 5:
            if (func_80106418_inst(&D_8010D444_inst[1], &D_8010D444_inst[2], &D_8010D474_inst[1], &D_8010D474_inst[2], 7) != 0) {
                func_80107BE4_inst();
                D_8010D43C_inst++;
            }
            break;
        case 6:
            D_8010DC00_inst = 60;
            D_8010D43C_inst++;
            break;
        case 7:
            if (D_8010D440_inst == 1) {
                D_8010DC00_inst--;
                if (func_8010CA74_inst(0x1000, D_8010DC02_inst) != 0 || D_8010D406_inst == 1) {
                    D_8010DC00_inst = 0;
                    switch (D_8010D40A_inst) {
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                            if (!(GwPlayer[D_8010D400_inst[0]].stat & 1)) {
                                omVibrate(D_8010D400_inst[0], 10, 0, 10);
                            }
                            break;
                        case 4:
                            for (i = 0; i < 2; i++) {
                                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                                    omVibrate(D_8010D400_inst[i], 10, 0, 10);
                                }
                            }
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        default:
                            for (i = 0; i < 4; i++) {
                                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                                    omVibrate(D_8010D400_inst[i], 10, 0, 10);
                                }
                            }
                            break;
                    }
                    func_8010CFF4_inst();
                    D_8010D409_inst = 1;
                    D_8010D43C_inst++;
                }
            }
            break;
        case 8:
            if (++D_8010DC00_inst >= 15) {
                D_8010D404_inst = 1;
                D_8010D43C_inst++;
            }
            break;
        case 9:
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(30);
            HuAudFXPlay(0x154);
            D_8010D43C_inst++;
            break;
        case 10:
            if (func_80106418_inst(&D_8010D444_inst[2], &D_8010D444_inst[3], &D_8010D474_inst[2], &D_8010D474_inst[3], 25) != 0 && WipeStatGet() == 0) {
                func_801063F4_inst();
                func_801061EC_inst();
            }
            break;
    }
}

/* Leaves the instruction screen for the minigame (or, if it was skipped, back). */
void func_801061EC_inst(void) {
    s32 pad[6];

    omOvlCallEx(D_800A6D40_main[D_8010D40B_inst].unk0, 0, 0x14);
    if (D_8010D5B1_inst == 1) {
        _SetFlag(0xF);
        return;
    }
    if (_CheckFlag(0xD) != 0) {
        goto back;
    }
    switch (D_8010D40A_inst) {
        case 6:
            omOvlHisChg(1, 0x72, 0, 0x14);
            break;
        case 4:
            if (GwSystem.playMode & 2) {
                omOvlHisChg(1, 0x73, 0, 0x4010);
                break;
            }
            goto back;
        case 3:
            omOvlHisChg(1, 0x74, 0, 0x12);
            break;
        case 5:
        case 7:
        case 8:
        back:
            if (omovlhisidx > 0) {
                omovlhisidx--;
            }
            break;
        default:
            omOvlHisChg(1, 0x71, 0, 0x12);
            break;
    }
}

void func_80106310_inst(omObjData *arg0) {
    if (D_800D530C_main == 1) {
        if (D_8010D4A8_inst == 0) {
            WipeCreateOut(0, 0x14);
            D_8010D4A8_inst = 1;
        } else if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(0x1E);
            func_801063F4_inst();
            omOvlReturnEx(1);
        }
    }
}

void func_80106388_inst(void) {
    u16 id = InitEspriteSlot(func_8000B838_main(D_8010D658_inst[D_8010D40A_inst]), 0, 0);

    func_8000BBD4_main(id, 0xA0, 0x78);
    func_8000BC48_main(id, 0x4000);
}

void func_801063F4_inst(void) {
    func_80037258_main();
    func_8005F524_main();
}

/* Title sprite per minigame type. */
const s32 D_8010D658_inst[] = {
    0x00170000, 0x00170001, 0x00170002, 0x00170003, 0x00170004,
    0x00170005, 0x00170005, 0x00170006, 0x00140067,
};

/* One step of an eased (sine) camera move from posA/atA to posB/atB over frames steps;
   returns 1 (and resets the step counter) once the move is complete. */
s32 func_80106418_inst(Vec *posA, Vec *posB, Vec *atA, Vec *atB, s32 frames) {
    s32 ret;

    D_8010D418_inst.x = (posB->x - posA->x) * sindf(D_8010D4AC_inst * (90.0f / frames)) + posA->x;
    D_8010D418_inst.y = (posB->y - posA->y) * sindf(D_8010D4AC_inst * (90.0f / frames)) + posA->y;
    D_8010D418_inst.z = (posB->z - posA->z) * sindf(D_8010D4AC_inst * (90.0f / frames)) + posA->z;
    D_8010D424_inst.x = (atB->x - atA->x) * sindf(D_8010D4AC_inst * (90.0f / frames)) + atA->x;
    D_8010D424_inst.y = (atB->y - atA->y) * sindf(D_8010D4AC_inst * (90.0f / frames)) + atA->y;
    D_8010D424_inst.z = (atB->z - atA->z) * sindf(D_8010D4AC_inst * (90.0f / frames)) + atA->z;
    D_8010D430_inst.x = 0.0f;
    D_8010D430_inst.y = 1.0f;
    D_8010D430_inst.z = -0.000001f;
    ret = 0;
    if (++D_8010D4AC_inst > frames) {
        D_8010D4AC_inst = 0;
        ret = 1;
    }
    return ret;
}

void func_8010674C_inst(omObjData *arg0) {
    D_800CE17C_main[0] = D_8010D418_inst.x;
    D_800CE17C_main[1] = D_8010D418_inst.z;
    D_800CE17C_main[-1] = 0;
    D_800CE17C_main[2] = gCameraList->fov[0];
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_8010D418_inst, &D_8010D424_inst, &D_8010D430_inst);
    Hu3DCamUpdateMtx(0);
}

void func_801067CC_inst(void) {
    D_8010D418_inst.x = D_8010D444_inst[1].x;
    D_8010D418_inst.y = D_8010D444_inst[1].y;
    D_8010D418_inst.z = D_8010D444_inst[1].z;
    D_8010D424_inst.x = D_8010D474_inst[1].x;
    D_8010D424_inst.y = D_8010D474_inst[1].y;
    D_8010D424_inst.z = D_8010D474_inst[1].z;
    D_8010D430_inst.x = 0.0f;
    D_8010D430_inst.y = 1.0f;
    D_8010D430_inst.z = -0.000001f;
}

void func_80106850_inst(Vec *pos, Vec *at) {
    D_8010D414_inst = 90.0f - atan2df(pos->y - at->y, pos->z - at->z);
}

/* Item minigames (type 5): picks the five items on offer (D_8010D40C_inst, copied to
   D_800A11D0_main) by weighted draw from the turn tier and the player's rank, and their
   prices (D_800A11DC_main: the player's character item gets the 40-coin price). */
void func_80106898_inst(void) {
    u8 weight[8];
    s8 used[8];
    u8 *items;
    s8 i;
    s8 n;
    s8 budget;
    s8 sum;
    s8 found;
    s8 tier;
    s8 rank;
    s8 col;
    s8 item;
    u8 target;
    u16 r;

    if (D_8010D40A_inst == 5) {
        if (_CheckFlag(0x1C) != 0) {
            r = rand8() & 3;
            if (rand8() & 1) {
                for (i = 0; i < 5; i++) {
                    D_8010D40C_inst[i] = D_8010D4B0_inst[i + r];
                }
            } else {
                for (i = 0; i < 5; i++) {
                    D_8010D40C_inst[i] = D_8010D4B8_inst[i + r];
                }
            }
            for (i = 0; i < 5; i++) {
                D_800A11D0_main[i] = (s8)D_8010D40C_inst[i];
            }
        } else if (D_8010D407_inst == 0) {
            for (i = 0; i < 8; i++) {
                used[i] = 0;
            }
            tier = BoardGetTurnTier(-1);
            rank = BoardPlayerRankCalc(D_8010D400_inst[0]);
            if ((u8)(rand8() % 3) == 0) {
                items = D_8010D4B0_inst;
                col = D_8010D6D8_inst[rank][tier];
                for (i = 0; i < 8; i++) {
                    weight[i] = D_8010D6B0_inst[i][col];
                }
            } else {
                items = D_8010D4B8_inst;
                col = D_8010D70C_inst[rank][tier];
                for (i = 0; i < 8; i++) {
                    weight[i] = D_8010D6E4_inst[i][col];
                }
            }
            budget = 100;
            for (n = 0; n < 5; n++) {
                target = rand8() % (budget + 1);
                sum = 0;
                for (i = 0; i < 8; i++) {
                    if (used[i] == 0) {
                        sum += weight[i];
                        if (sum >= target) {
                            used[i] = 1;
                            budget -= weight[i];
                            D_8010D40C_inst[n] = items[i];
                            break;
                        }
                    }
                }
            }
            for (i = 0; i < 5; i++) {
                D_800A11D0_main[i] = (s8)D_8010D40C_inst[i];
            }
            item = D_8010D724_inst[GwPlayer[D_8010D400_inst[0]].chr];
            found = -1;
            for (i = 0; i < 5; i++) {
                if (item == D_800A11D0_main[i]) {
                    found = i;
                    break;
                }
            }
            if (found >= 0) {
                for (i = 0, n = 0; i < 5; i++) {
                    if (i == found) {
                        D_800A11DC_main[i] = (s8)D_8010D718_inst[9];
                    } else {
                        D_800A11DC_main[i] = (s8)D_8010D718_inst[5 + n];
                        n++;
                    }
                }
            } else {
                for (i = 0; i < 5; i++) {
                    D_800A11DC_main[i] = (s8)D_8010D718_inst[i];
                }
            }
        } else {
            for (i = 0; i < 5; i++) {
                D_8010D40C_inst[i] = D_800A11D0_main[i];
            }
        }
    }
}

/* Item weights per item slot and column (picked by rank and turn tier). */
const u8 D_8010D6B0_inst[8][5] = {
    { 0x28, 0x28, 0x1E, 0x14, 0x14 }, { 0x14, 0x14, 0x0A, 0x0A, 0x0A }, { 0x0A, 0x0A, 0x0A, 0x05, 0x05 },
    { 0x0A, 0x0A, 0x0C, 0x0F, 0x05 }, { 0x02, 0x02, 0x05, 0x0A, 0x0A }, { 0x0A, 0x0A, 0x14, 0x14, 0x14 },
    { 0x03, 0x05, 0x0A, 0x0A, 0x0A }, { 0x05, 0x03, 0x03, 0x0A, 0x14 },
};
const s8 D_8010D6D8_inst[4][3] = { { 0, 1, 2 }, { 0, 0, 3 }, { 0, 0, 4 }, { 0, 0, 4 } };
const u8 D_8010D6E4_inst[8][5] = {
    { 0x1E, 0x1E, 0x1E, 0x14, 0x14 }, { 0x14, 0x14, 0x0A, 0x0A, 0x0A }, { 0x0A, 0x0A, 0x0F, 0x0A, 0x0F },
    { 0x0A, 0x0A, 0x05, 0x0F, 0x0F }, { 0x0A, 0x0A, 0x0A, 0x05, 0x05 }, { 0x07, 0x0A, 0x0F, 0x14, 0x14 },
    { 0x05, 0x05, 0x0C, 0x0A, 0x05 }, { 0x08, 0x05, 0x03, 0x0A, 0x14 },
};
const s8 D_8010D70C_inst[4][3] = { { 0, 1, 2 }, { 0, 0, 3 }, { 0, 0, 4 }, { 0, 0, 4 } };
/* Prices: [0..4] with no character item on offer, [5..8] the others and [9] the character
   item when it is. */
const u8 D_8010D718_inst[10] = { 20, 10, 20, 30, 20, 20, 10, 10, 20, 40 };
/* Each character's own item. */
const s8 D_8010D724_inst[8] = { 10, 1, 6, 5, 8, 3, 4, 2 };

/* Shuffles the play order (D_8010D400_inst) for the minigames that need it and gives each
   player their group from it; for 2-vs-2 pairs a lone human goes first in the pair. */
void func_80106EB4_inst(void) {
    s32 i;
    s32 n;
    s32 a;
    s32 b;
    s32 tmp;

    if (D_8010D407_inst != 1) {
        switch (D_8010D40B_inst) {
            case 18:
                if (rand8() & 1) {
                    tmp = D_8010D400_inst[0];
                    D_8010D400_inst[0] = D_8010D400_inst[1];
                    D_8010D400_inst[1] = tmp;
                }
                if (rand8() & 1) {
                    tmp = D_8010D400_inst[2];
                    D_8010D400_inst[2] = D_8010D400_inst[3];
                    D_8010D400_inst[3] = tmp;
                }
                for (i = 0; i < 4; i++) {
                    GwPlayer[D_8010D400_inst[i]].group = i;
                }
                break;
            case 14:
                if (rand8() & 1) {
                    tmp = D_8010D400_inst[0];
                    D_8010D400_inst[0] = D_8010D400_inst[1];
                    D_8010D400_inst[1] = tmp;
                }
                if (rand8() & 1) {
                    tmp = D_8010D400_inst[2];
                    D_8010D400_inst[2] = D_8010D400_inst[3];
                    D_8010D400_inst[3] = tmp;
                }
                for (i = 0; i < 4; i++) {
                    GwPlayer[D_8010D400_inst[i]].group = i;
                }
                break;
            case 13:
                for (i = 0, n = 0; i < 2; i++) {
                    if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                        n++;
                    }
                }
                if (n == 1) {
                    if (GwPlayer[D_8010D400_inst[0]].stat & 1) {
                        tmp = D_8010D400_inst[0];
                        D_8010D400_inst[0] = D_8010D400_inst[1];
                        D_8010D400_inst[1] = tmp;
                    }
                } else if (rand8() & 1) {
                    tmp = D_8010D400_inst[0];
                    D_8010D400_inst[0] = D_8010D400_inst[1];
                    D_8010D400_inst[1] = tmp;
                }
                for (i = 0, n = 0; i < 2; i++) {
                    if (!(GwPlayer[D_8010D400_inst[2 + i]].stat & 1)) {
                        n++;
                    }
                }
                if (n == 1) {
                    if (GwPlayer[D_8010D400_inst[2]].stat & 1) {
                        tmp = D_8010D400_inst[2];
                        D_8010D400_inst[2] = D_8010D400_inst[3];
                        D_8010D400_inst[3] = tmp;
                    }
                } else if (rand8() & 1) {
                    tmp = D_8010D400_inst[2];
                    D_8010D400_inst[2] = D_8010D400_inst[3];
                    D_8010D400_inst[3] = tmp;
                }
                for (i = 0; i < 4; i++) {
                    GwPlayer[D_8010D400_inst[i]].group = i;
                }
                break;
            case 6:
            case 7:
                for (i = 0; i < 5; i++) {
                    a = (u8)(rand8() % 3);
                    b = (u8)(rand8() % 3);
                    if (b == a) {
                        b++;
                        b %= 3;
                    }
                    tmp = D_8010D400_inst[1 + a];
                    D_8010D400_inst[1 + a] = D_8010D400_inst[1 + b];
                    D_8010D400_inst[1 + b] = tmp;
                }
                for (i = 0; i < 4; i++) {
                    GwPlayer[D_8010D400_inst[i]].group = i;
                }
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107308_inst);
