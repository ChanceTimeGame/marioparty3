#include "common.h"
#include "game/hmfman.h"
#include "mgresultboard.h"

void func_80032FC0_main(s16, u8, u8);

extern Vec D_8010AB40_mgresultboard[4];
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

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80108330_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80108700_mgresultboard);

void func_80108BBC_mgresultboard(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80108BC4_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80108C60_mgresultboard);

void func_8010913C_mgresultboard(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109144_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_801092E0_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109498_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109650_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_801096E0_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109744_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109878_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109A90_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109CB0_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109D44_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109DAC_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80109F30_mgresultboard);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultboard/4E9120", D_8010AD58_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_8010A000_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_8010A334_mgresultboard);

void func_8010A350_mgresultboard(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_8010A358_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_8010A3E4_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_8010A454_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_8010A4A0_mgresultboard);

s32 func_8010A864_mgresultboard(omObjData *arg0, s8 arg1, s8 arg2) {
    if (D_8010AFB0_mgresultboard[arg1].unk_04 >= 0) {
        return 0;
    }

    D_8010AFB0_mgresultboard[arg1].unk_04 = arg2;

    if (D_8010AFB0_mgresultboard[arg1].unk_08 >= 0) {
        func_8001C258_main(arg0->model[D_8010AFB0_mgresultboard[arg1].unk_08 + 1], 4, 0);
    }

    D_8010AFB0_mgresultboard[arg1].unk_00 = 1;
    return 1;
}
