#include "common.h"
#include "game/hmfman.h"
#include "mgresultboard.h"

void func_80032FC0_main(s16, u8, u8);

typedef struct TexAnimSlot {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk_02[0xA];
} TexAnimSlot; // sizeof 0xC

extern TexAnimSlot *D_800D1714_main;
s16 func_800329B4_main(void *);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
s16 func_8000B0D4_main(s32, s32);

extern Vec D_8010AB40_mgresultboard[4];
extern Vec D_8010AB70_mgresultboard[8];
extern Vec D_8010ABD0_mgresultboard[12];
extern s32 D_8010ADD0_mgresultboard[40];
extern s32 D_8010AE70_mgresultboard[4];
extern omObjData *D_8010AEA0_mgresultboard;
extern void (*D_8010AEA4_mgresultboard)(omObjData *);
extern ResultSlot D_8010AEA8_mgresultboard[4][5];
extern const s16 D_8010AD58_mgresultboard[4][5];
extern const u8 D_8010AD28_mgresultboard[8][3];

const u8 D_8010AD28_mgresultboard[8][3] = {
    { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 9, 10, 11 }, { 12, 13, 14 }, { 15, 16, 17 }, { 18, 19, 20 }, { 21, 22, 23 },
};

void func_80107D00_mgresultboard(void) {
    omObjData *obj;
    void *data;
    void *anim;
    s32 motId;
    s32 i;

    motId = 0;
    obj = omAddObj(0x14, 0xC, 0, -1, NULL);
    D_8010AFA8_mgresultboard = obj;
    data = DataRead(0x180004);
    for (i = 0; i < 8; i++) {
        obj->model[i + 1] = Hu3DModelCreate(data, 0x2A0);
        func_8001C814_main(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 1], D_8010AB40_mgresultboard[i & 3].x, D_8010AB40_mgresultboard[i & 3].y,
                        D_8010AB40_mgresultboard[i & 3].z);
        func_8001C8A8_main(obj->model[i + 1], 2);
        if (i == 0) {
            anim = DataRead(0x180008);
            motId = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, anim, 0, "ys04_04_DEF");
            D_8010ADB0_mgresultboard[0] = motId;
            HuMemMemoryFreePerm(anim);
        } else {
            D_8010ADB0_mgresultboard[i] =
                func_80032694_main(HmfModelData[obj->model[i + 1]].hmf, motId, 0, "ys04_04_DEF");
        }
        func_8001C448_main(obj->model[i + 1]);
        func_8001C514_main(obj->model[i + 1]);
        func_80032FC0_main(D_8010ADB0_mgresultboard[i], 1, 1);
        func_80032FF8_main((s16)D_8010ADB0_mgresultboard[i], D_8010AD28_mgresultboard[i][0]);
        if (i < 4) {
            func_8001C6A8_main(obj->model[i + 1], 40.0f);
            func_80032FF8_main((s16)D_8010ADB0_mgresultboard[i],
                               D_8010AD28_mgresultboard[D_8010B048_mgresultboard[i].unk_02][D_8010B048_mgresultboard[i].unk_03]);
        } else {
            func_8001C6A8_main(obj->model[i + 1], 20.0f);
            func_80032FF8_main((s16)D_8010ADB0_mgresultboard[i],
                               D_8010AD28_mgresultboard[D_8010B048_mgresultboard[rand8() & 3].unk_02][rand8() % 3]);
        }
    }
    HuMemMemoryFreePerm(data);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    func_801080C4_mgresultboard();
    omPrcSetDestructor(0, func_801081E8_mgresultboard);
    while (D_8010AAF8_mgresultboard == 0) {
        HuPrcVSleep();
    }
    D_8010AFAC_mgresultboard = func_801081CC_mgresultboard;
    func_80108150_mgresultboard(obj);
    while (TRUE) {
        D_8010AFAC_mgresultboard(obj);
        HuPrcVSleep();
    }
}

void func_801080C4_mgresultboard(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010AFE8_mgresultboard[i].unk_00 = 0;
        D_8010AFE8_mgresultboard[i].unk_02 = 0;
        D_8010AFE8_mgresultboard[i].unk_04 = -1;
        D_8010AFE8_mgresultboard[i].unk_06 = i;
        D_8010AFE8_mgresultboard[i].unk_08 = i + 4;
        D_8010AFE8_mgresultboard[i].unk_0A = 0;
    }
}

void func_80108150_mgresultboard(omObjData *obj) {
    s8 i;

    for (i = 0; i < 4; i++) {
        func_801081F0_mgresultboard(obj, i, D_8010B048_mgresultboard[i].unk_02, D_8010B048_mgresultboard[i].unk_03);
    }
}

void func_801081CC_mgresultboard(omObjData *obj) {
    func_80108330_mgresultboard(obj);
}

void func_801081E8_mgresultboard(void) {
}

s32 func_801081F0_mgresultboard(omObjData *obj, s8 arg1, s8 arg2, s8 arg3) {
    D_8010AFE8_mgresultboard[arg1].unk_02 = arg2 * 3 + arg3;
    D_8010AFE8_mgresultboard[arg1].unk_04 = -1;
    D_8010AFE8_mgresultboard[arg1].unk_00 = 0;
    return 1;
}

s32 func_80108250_mgresultboard(omObjData *obj, s8 arg1, s8 arg2, s8 arg3) {
    if (D_8010AFE8_mgresultboard[arg1].unk_04 >= 0) {
        return 0;
    }

    D_8010AFE8_mgresultboard[arg1].unk_04 = arg2 * 3 + arg3;

    if (D_8010AFE8_mgresultboard[arg1].unk_08 >= 0) {
        func_8001C258_main(obj->model[D_8010AFE8_mgresultboard[arg1].unk_08 + 1], 4, 0);
    }

    D_8010AFE8_mgresultboard[arg1].unk_00 = 1;
    return 1;
}

void func_80108330_mgresultboard(omObjData *obj) {
    s16 model;
    f32 time;
    f32 end;
    s16 b;
    s16 a;
    s16 tmp;
    s8 i;

    for (i = 0; i < 4; i++) {
        b = D_8010AFE8_mgresultboard[i].unk_08;
        a = D_8010AFE8_mgresultboard[i].unk_06;
        model = obj->model[a + 1];
        time = HmfModelData[model].unk40;
        end = D_800CCF58_main[HmfModelData[model].unk02].unk02;
        switch (D_8010AFE8_mgresultboard[i].unk_00) {
            case 1:
                if (a >= 0) {
                    func_8001C814_main(model, 1, 0);
                    func_8001C258_main(obj->model[a + 1], 4, 0);
                    func_8001C92C_main(obj->model[a + 1], D_8010AAF4_mgresultboard);
                }
                if (b >= 0) {
                    func_8001C814_main(obj->model[b + 1], 1, 0);
                    func_8001C258_main(obj->model[b + 1], 4, 0);
                    func_8001C92C_main(obj->model[b + 1], D_8010AAF4_mgresultboard);
                }
                if (D_8010AFE8_mgresultboard[i].unk_04 >= 0) {
                    if (end <= time) {
                        func_80032FF8_main((s16)D_8010ADB0_mgresultboard[b], D_8010AFE8_mgresultboard[i].unk_04);
                        D_8010AFE8_mgresultboard[i].unk_02 = D_8010AFE8_mgresultboard[i].unk_04;
                        D_8010AFE8_mgresultboard[i].unk_04 = -1;
                        if (a >= 0) {
                            func_8001C6A8_main(obj->model[a + 1], 0.0f);
                        }
                        if (b >= 0) {
                            func_8001C6A8_main(obj->model[b + 1], 20.0f);
                        }
                        tmp = D_8010AFE8_mgresultboard[i].unk_06;
                        D_8010AFE8_mgresultboard[i].unk_06 = D_8010AFE8_mgresultboard[i].unk_08;
                        D_8010AFE8_mgresultboard[i].unk_08 = tmp;
                    }
                    break;
                }
                D_8010AFE8_mgresultboard[i].unk_00 = 0;
                /* fallthrough */
            case 0:
                if (end <= time) {
                    /* Retail tests each model index and then uses the other one. */
                    if (a >= 0) {
                        func_8001C6A8_main(obj->model[b + 1], 20.0f);
                        func_8001C814_main(obj->model[b + 1], 1, 1);
                        func_8001C258_main(obj->model[b + 1], 4, 4);
                        func_80032FF8_main((s16)D_8010ADB0_mgresultboard[b], D_8010AFE8_mgresultboard[i].unk_02);
                    }
                    if (b >= 0) {
                        func_8001C6A8_main(obj->model[a + 1], end);
                        func_8001C814_main(obj->model[a + 1], 1, 1);
                    }
                }
                break;
        }
    }
}

void func_80108700_mgresultboard(void) {
    omObjData *obj;
    void *data;
    s32 i;

    obj = omAddObj(0x14, 0x32, 0, -1, NULL);
    D_8010AEA0_mgresultboard = obj;
    obj->model[1] = func_8000B0D4_main(0x180000, 0x2A8);
    data = DataRead(0x180005);
    D_8010ADD0_mgresultboard[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "zero_DEF");
    HuMemMemoryFreePerm(data);
    D_8010AE70_mgresultboard[0] = D_800D1714_main[D_8010ADD0_mgresultboard[0]].unk_00;
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8010ADD0_mgresultboard[0], 1, 1);
    func_80032FF8_main((s16)D_8010ADD0_mgresultboard[0], 0);
    func_8001C8A8_main(obj->model[1], 2);
    data = DataRead(0x180006);
    D_8010AE70_mgresultboard[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0x180000);
    for (i = 1; i < 40; i++) {
        obj->model[i + 1] = Hu3DModelCreate(data, 0x2A0);
        func_8001C8A8_main(obj->model[i + 1], 2);
        D_8010ADD0_mgresultboard[i] =
            func_80032694_main(HmfModelData[obj->model[i + 1]].hmf, D_8010ADD0_mgresultboard[0], 0, "zero_DEF");
        func_8001C448_main(obj->model[i + 1]);
        func_8001C514_main(obj->model[i + 1]);
        func_80032FC0_main(D_8010ADD0_mgresultboard[i], 1, 1);
        func_80032FF8_main((s16)D_8010ADD0_mgresultboard[i], 0);
    }
    HuMemMemoryFreePerm(data);
    for (i = 0; i < 8; i++) {
        Hu3DModelPosSet(obj->model[i + 1], D_8010AB70_mgresultboard[i].x, D_8010AB70_mgresultboard[i].y,
                        D_8010AB70_mgresultboard[i].z);
        func_8001C6A8_main(obj->model[i + 1], 40.0f);
        func_8001C814_main(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 21], D_8010AB70_mgresultboard[i].x, D_8010AB70_mgresultboard[i].y,
                        D_8010AB70_mgresultboard[i].z);
        func_8001C6A8_main(obj->model[i + 21], 20.0f);
        func_8001C814_main(obj->model[i + 21], 2, 0);
    }
    for (i = 0; i < 12; i++) {
        Hu3DModelPosSet(obj->model[i + 9], D_8010ABD0_mgresultboard[i].x, D_8010ABD0_mgresultboard[i].y,
                        D_8010ABD0_mgresultboard[i].z);
        func_8001C6A8_main(obj->model[i + 9], 40.0f);
        func_8001C814_main(obj->model[i + 9], 2, 0);
        Hu3DModelPosSet(obj->model[i + 29], D_8010ABD0_mgresultboard[i].x, D_8010ABD0_mgresultboard[i].y,
                        D_8010ABD0_mgresultboard[i].z);
        func_8001C6A8_main(obj->model[i + 29], 20.0f);
        func_8001C814_main(obj->model[i + 29], 2, 0);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    func_80109144_mgresultboard();
    omPrcSetDestructor(0, func_8010913C_mgresultboard);
    while (D_8010AAF8_mgresultboard == 0) {
        HuPrcVSleep();
    }
    D_8010AEA4_mgresultboard = func_80108BBC_mgresultboard;
    func_80108BC4_mgresultboard(obj);
    while (TRUE) {
        D_8010AEA4_mgresultboard(obj);
        func_80108C60_mgresultboard(obj);
        HuPrcVSleep();
    }
}

void func_80108BBC_mgresultboard(omObjData *obj) {
}

void func_80108BC4_mgresultboard(omObjData *obj) {
    s8 i;

    for (i = 0; i < 4; i++) {
        func_80109744_mgresultboard(obj, i, D_8010B048_mgresultboard[i].score);
        func_80109DAC_mgresultboard(obj, i, D_8010B048_mgresultboard[i].coin);
    }
}

void func_80108C60_mgresultboard(omObjData *obj) {
    s16 model;
    f32 time;
    f32 end;
    s16 b;
    s16 a;
    s16 tmp;
    s8 i;
    s8 j;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 5; i++) {
            b = D_8010AEA8_mgresultboard[j][i].unk_08;
            a = D_8010AEA8_mgresultboard[j][i].unk_06;
            model = obj->model[a + 1];
            time = HmfModelData[model].unk40;
            end = D_800CCF58_main[HmfModelData[model].unk02].unk02;
            switch (D_8010AEA8_mgresultboard[j][i].unk_00) {
                case 1:
                    if (a >= 0) {
                        func_8001C814_main(model, 1, 0);
                        func_8001C258_main(obj->model[a + 1], 4, 0);
                        func_8001C92C_main(obj->model[a + 1], D_8010AAF4_mgresultboard);
                    }
                    if (b >= 0) {
                        func_8001C814_main(obj->model[b + 1], 1, 0);
                        func_8001C258_main(obj->model[b + 1], 4, 0);
                        func_8001C92C_main(obj->model[b + 1], D_8010AAF4_mgresultboard);
                    }
                    if (D_8010AEA8_mgresultboard[j][i].unk_04 >= 0) {
                        if (end <= time) {
                            func_80032FF8_main((s16)D_8010ADD0_mgresultboard[b], D_8010AEA8_mgresultboard[j][i].unk_04);
                            D_8010AEA8_mgresultboard[j][i].unk_02 = D_8010AEA8_mgresultboard[j][i].unk_04;
                            D_8010AEA8_mgresultboard[j][i].unk_04 = -1;
                            if (a >= 0) {
                                func_8001C6A8_main(obj->model[a + 1], 0.0f);
                            }
                            if (b >= 0) {
                                func_8001C6A8_main(obj->model[b + 1], 20.0f);
                            }
                            tmp = D_8010AEA8_mgresultboard[j][i].unk_06;
                            D_8010AEA8_mgresultboard[j][i].unk_06 = D_8010AEA8_mgresultboard[j][i].unk_08;
                            D_8010AEA8_mgresultboard[j][i].unk_08 = tmp;
                            if (D_8010AEA8_mgresultboard[j][i].unk_0A == 0) {
                                func_80109F30_mgresultboard(obj->model[b + 1], D_8010ADD0_mgresultboard[b],
                                                            D_8010AE70_mgresultboard[0]);
                            } else {
                                func_80109F30_mgresultboard(obj->model[b + 1], D_8010ADD0_mgresultboard[b],
                                                            D_8010AE70_mgresultboard[1]);
                            }
                        }
                        break;
                    }
                    D_8010AEA8_mgresultboard[j][i].unk_00 = 0;
                    /* fallthrough */
                case 0:
                    if (end <= time) {
                        if (b >= 0) {
                            func_8001C6A8_main(obj->model[b + 1], 20.0f);
                            func_8001C814_main(obj->model[b + 1], 1, 1);
                            func_8001C258_main(obj->model[b + 1], 4, 4);
                        }
                        if (a >= 0) {
                            func_80032FF8_main((s16)D_8010ADD0_mgresultboard[a], D_8010AEA8_mgresultboard[j][i].unk_02);
                            func_8001C6A8_main(obj->model[a + 1], end);
                            func_8001C814_main(obj->model[a + 1], 1, 1);
                        }
                    }
                    break;
            }
        }
    }
}

void func_8010913C_mgresultboard(void) {
}

void func_80109144_mgresultboard(void) {
    s8 j;
    s8 i;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 2; i++) {
            D_8010AEA8_mgresultboard[j][i].unk_00 = 0;
            D_8010AEA8_mgresultboard[j][i].unk_02 = 0;
            D_8010AEA8_mgresultboard[j][i].unk_04 = -1;
            D_8010AEA8_mgresultboard[j][i].unk_06 = D_8010AD58_mgresultboard[j][i];
            D_8010AEA8_mgresultboard[j][i].unk_08 = D_8010AD58_mgresultboard[j][i] + 20;
            D_8010AEA8_mgresultboard[j][i].unk_0A = 0;
        }
        for (; i < 5; i++) {
            D_8010AEA8_mgresultboard[j][i].unk_00 = 0;
            D_8010AEA8_mgresultboard[j][i].unk_02 = 0;
            D_8010AEA8_mgresultboard[j][i].unk_04 = -1;
            D_8010AEA8_mgresultboard[j][i].unk_06 = D_8010AD58_mgresultboard[j][i];
            D_8010AEA8_mgresultboard[j][i].unk_08 = D_8010AD58_mgresultboard[j][i] + 20;
            D_8010AEA8_mgresultboard[j][i].unk_0A = 0;
        }
    }
}

s32 func_801092E0_mgresultboard(omObjData *obj, s8 player, s16 value) {
    s16 digit[2];
    s8 i;

    if (D_8010AEA8_mgresultboard[player][0].unk_04 >= 0) {
        return 0;
    }
    if (value >= 100) {
        value = 99;
    }
    if (value < 0) {
        value = 0;
    }
    digit[0] = (s16)(value / 10) % 10;
    digit[1] = value % 10;
    if (digit[0] == 0) {
        digit[0] = 11;
    }
    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[player][i].unk_04 = digit[i];
        if (D_8010AEA8_mgresultboard[player][i].unk_08 >= 0) {
            func_8001C258_main(obj->model[D_8010AEA8_mgresultboard[player][i].unk_08 + 1], 4, 0);
        }
        D_8010AEA8_mgresultboard[player][i].unk_00 = 1;
    }
    return 1;
}

s32 func_80109498_mgresultboard(omObjData *obj, s8 player, s16 value) {
    s16 digit[2];
    s8 i;

    if (D_8010AEA8_mgresultboard[player][0].unk_04 >= 0) {
        return 0;
    }
    if (value >= 100) {
        value = 99;
    }
    if (value < 0) {
        value = 0;
    }
    digit[0] = (s16)(value / 10) % 10;
    digit[1] = value % 10;
    if (digit[0] == 0) {
        digit[0] = 10;
    }
    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[player][i].unk_04 = digit[i];
        if (D_8010AEA8_mgresultboard[player][i].unk_08 >= 0) {
            func_8001C258_main(obj->model[D_8010AEA8_mgresultboard[player][i].unk_08 + 1], 4, 0);
        }
        D_8010AEA8_mgresultboard[player][i].unk_00 = 1;
    }
    return 1;
}

s32 func_80109650_mgresultboard(omObjData *obj, s8 player) {
    s8 i;

    if (D_8010AEA8_mgresultboard[player][0].unk_04 >= 0) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[player][i].unk_00 = 0;
    }
    return 1;
}

s32 func_801096E0_mgresultboard(omObjData *obj, s8 player) {
    s8 i;

    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[player][i].unk_00 = 1;
    }
    return 1;
}

s32 func_80109744_mgresultboard(omObjData *obj, s8 player, s16 value) {
    s16 digit[2];
    s8 i;

    if (value >= 100) {
        value = 99;
    }
    if (value < 0) {
        value = 0;
    }
    digit[0] = (s16)(value / 10) % 10;
    digit[1] = value % 10;
    if (digit[0] == 0) {
        digit[0] = 11;
    }
    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[player][i].unk_02 = digit[i];
        D_8010AEA8_mgresultboard[player][i].unk_04 = -1;
        D_8010AEA8_mgresultboard[player][i].unk_00 = 0;
    }
    return 1;
}

s32 func_80109878_mgresultboard(omObjData *obj, s8 player, s16 value) {
    s16 digit[3];
    s8 i;

    if (D_8010AEA8_mgresultboard[player][2].unk_04 >= 0) {
        return 0;
    }
    if (value >= 1000) {
        value = 999;
    }
    if (value < 0) {
        value = 0;
    }
    digit[0] = (s16)(value / 100) % 10;
    digit[1] = (s16)(value / 10) % 10;
    digit[2] = value % 10;
    if (digit[0] == 0) {
        digit[0] = 11;
    }
    for (i = 0; i < 3; i++) {
        D_8010AEA8_mgresultboard[player][i + 2].unk_04 = digit[i];
        D_8010AEA8_mgresultboard[player][i + 2].unk_00 = 1;
        if (D_8010AEA8_mgresultboard[player][i + 2].unk_08 >= 0) {
            func_8001C258_main(obj->model[D_8010AEA8_mgresultboard[player][i + 2].unk_08 + 1], 4, 0);
        }
        D_8010AEA8_mgresultboard[player][i + 2].unk_0A = 0;
    }
    return 1;
}

s32 func_80109A90_mgresultboard(omObjData *obj, s8 player, s16 value) {
    s16 digit[3];
    s8 i;

    if (D_8010AEA8_mgresultboard[player][2].unk_04 >= 0) {
        return 0;
    }
    if (value >= 1000) {
        value = 999;
    }
    if (value < 0) {
        value = 0;
    }
    digit[0] = (s16)(value / 100) % 10;
    digit[1] = (s16)(value / 10) % 10;
    digit[2] = value % 10;
    if (digit[0] == 0) {
        digit[0] = 10;
    }
    for (i = 0; i < 3; i++) {
        D_8010AEA8_mgresultboard[player][i + 2].unk_04 = digit[i];
        D_8010AEA8_mgresultboard[player][i + 2].unk_00 = 1;
        if (D_8010AEA8_mgresultboard[player][i + 2].unk_08 >= 0) {
            func_8001C258_main(obj->model[D_8010AEA8_mgresultboard[player][i + 2].unk_08 + 1], 4, 0);
        }
        D_8010AEA8_mgresultboard[player][i + 2].unk_0A = 1;
    }
    return 1;
}

/* Retail runs i to 3: the last pass writes one slot past the player's three coin digits (for the
   last player, the first byte of D_8010AF98). */
s32 func_80109CB0_mgresultboard(omObjData *obj, s8 player) {
    s8 i;

    if (D_8010AEA8_mgresultboard[player][2].unk_04 >= 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        D_8010AEA8_mgresultboard[player][i + 2].unk_00 = 0;
    }
    return 1;
}

/* Same one-slot overrun as func_80109CB0_mgresultboard. */
s32 func_80109D44_mgresultboard(omObjData *obj, s8 player) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010AEA8_mgresultboard[player][i + 2].unk_00 = 1;
    }
    return 1;
}

s32 func_80109DAC_mgresultboard(omObjData *obj, s8 player, s16 value) {
    s16 digit[3];
    s8 i;

    if (value >= 1000) {
        value = 999;
    }
    if (value < 0) {
        value = 0;
    }
    digit[0] = (s16)(value / 100) % 10;
    digit[1] = (s16)(value / 10) % 10;
    digit[2] = value % 10;
    if (digit[0] == 0) {
        digit[0] = 11;
    }
    for (i = 0; i < 3; i++) {
        D_8010AEA8_mgresultboard[player][i + 2].unk_02 = digit[i];
        D_8010AEA8_mgresultboard[player][i + 2].unk_04 = -1;
        D_8010AEA8_mgresultboard[player][i + 2].unk_00 = 0;
    }
    return 1;
}

void func_80109F30_mgresultboard(s16 model, s16 slot, s16 frame) {
    TexAnimSlot *p;

    if (slot >= 0) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
            return;
        }
        func_80033970_main(HmfModelData[model].hmf);
        p = &D_800D1714_main[slot];
        p->unk_00 = frame;
    }
}

const s16 D_8010AD58_mgresultboard[4][5] = {
    { 0, 1, 8, 9, 10 }, { 2, 3, 11, 12, 13 }, { 4, 5, 14, 15, 16 }, { 6, 7, 17, 18, 19 },
};
