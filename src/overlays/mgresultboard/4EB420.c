#include "common.h"
#include "game/hmfman.h"
#include "mgresultboard.h"

void func_80032FC0_main(s16, u8, u8);

extern Vec D_8010AC60_mgresultboard[4];
extern s32 D_8010AE80_mgresultboard[8];
extern void (*D_8010AFE4_mgresultboard)(omObjData *);

void func_8010A000_mgresultboard(void) {
    omObjData *obj;
    void *data;
    void *anim;
    s32 motId;
    s32 i;

    motId = 0;
    obj = omAddObj(0x14, 0xC, 0, -1, NULL);
    D_8010AFE0_mgresultboard = obj;
    data = DataRead(0x180003);
    for (i = 0; i < 8; i++) {
        obj->model[i + 1] = Hu3DModelCreate(data, 0x2A0);
        func_8001C814_main(obj->model[i + 1], 2, 0);
        func_8001C814_main(obj->model[i + 1], 1, 0);
        func_8001C8A8_main(obj->model[i + 1], 2);
        Hu3DModelPosSet(obj->model[i + 1], D_8010AC60_mgresultboard[i & 3].x, D_8010AC60_mgresultboard[i & 3].y,
                        D_8010AC60_mgresultboard[i & 3].z);
        if (i == 0) {
            anim = DataRead(0x180007);
            motId = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, anim, 0, "y004_010_DEF");
            D_8010AE80_mgresultboard[0] = motId;
            HuMemMemoryFreePerm(anim);
        } else {
            D_8010AE80_mgresultboard[i] =
                func_80032694_main(HmfModelData[obj->model[i + 1]].hmf, motId, 0, "y004_010_DEF");
        }
        func_80032FC0_main(D_8010AE80_mgresultboard[i], 1, 1);
        func_8001C448_main(obj->model[i + 1]);
        func_8001C514_main(obj->model[i + 1]);
        if (i < 4) {
            func_8001C6A8_main(obj->model[i + 1], 40.0f);
            func_80032FF8_main((s16)D_8010AE80_mgresultboard[i], D_8010B048_mgresultboard[i].unk_01);
        } else {
            func_8001C6A8_main(obj->model[i + 1], 20.0f);
            func_80032FF8_main((s16)D_8010AE80_mgresultboard[i], rand8() & 3);
        }
    }
    HuMemMemoryFreePerm(data);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    func_8010A358_mgresultboard();
    omPrcSetDestructor(0, func_8010A350_mgresultboard);
    while (D_8010AAF8_mgresultboard == 0) {
        HuPrcVSleep();
    }
    func_8010A3E4_mgresultboard(obj);
    D_8010AFE4_mgresultboard = func_8010A334_mgresultboard;
    while (TRUE) {
        D_8010AFE4_mgresultboard(obj);
        HuPrcVSleep();
    }
}

void func_8010A334_mgresultboard(omObjData *obj) {
    func_8010A4A0_mgresultboard(obj);
}

void func_8010A350_mgresultboard(void) {
}

void func_8010A358_mgresultboard(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010AFB0_mgresultboard[i].unk_00 = 0;
        D_8010AFB0_mgresultboard[i].unk_02 = 0;
        D_8010AFB0_mgresultboard[i].unk_04 = -1;
        D_8010AFB0_mgresultboard[i].unk_06 = i;
        D_8010AFB0_mgresultboard[i].unk_08 = i + 4;
        D_8010AFB0_mgresultboard[i].unk_0A = 0;
    }
}

void func_8010A3E4_mgresultboard(omObjData *obj) {
    s8 i;

    for (i = 0; i < 4; i++) {
        func_8010A454_mgresultboard(obj, i, D_8010B048_mgresultboard[i].unk_01);
    }
}

s32 func_8010A454_mgresultboard(omObjData *obj, s8 arg1, s8 arg2) {
    D_8010AFB0_mgresultboard[arg1].unk_02 = arg2;
    D_8010AFB0_mgresultboard[arg1].unk_04 = -1;
    D_8010AFB0_mgresultboard[arg1].unk_00 = 0;
    return 1;
}

void func_8010A4A0_mgresultboard(omObjData *obj) {
    s16 model;
    f32 time;
    f32 end;
    s16 b;
    s16 a;
    s16 tmp;
    s8 i;

    for (i = 0; i < 4; i++) {
        b = D_8010AFB0_mgresultboard[i].unk_08;
        a = D_8010AFB0_mgresultboard[i].unk_06;
        model = obj->model[a + 1];
        time = HmfModelData[model].unk40;
        end = D_800CCF58_main[HmfModelData[model].unk02].unk02;
        switch (D_8010AFB0_mgresultboard[i].unk_00) {
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
                if (D_8010AFB0_mgresultboard[i].unk_04 >= 0) {
                    if (end <= time) {
                        func_80032FF8_main((s16)D_8010AE80_mgresultboard[b], D_8010AFB0_mgresultboard[i].unk_04);
                        D_8010AFB0_mgresultboard[i].unk_02 = D_8010AFB0_mgresultboard[i].unk_04;
                        D_8010AFB0_mgresultboard[i].unk_04 = -1;
                        if (a >= 0) {
                            func_8001C6A8_main(obj->model[a + 1], 0.0f);
                        }
                        if (b >= 0) {
                            func_8001C6A8_main(obj->model[b + 1], 20.0f);
                        }
                        tmp = D_8010AFB0_mgresultboard[i].unk_06;
                        D_8010AFB0_mgresultboard[i].unk_06 = D_8010AFB0_mgresultboard[i].unk_08;
                        D_8010AFB0_mgresultboard[i].unk_08 = tmp;
                    }
                    break;
                }
                D_8010AFB0_mgresultboard[i].unk_00 = 0;
                /* fallthrough */
            case 0:
                if (end <= time) {
                    if (b >= 0) {
                        func_8001C6A8_main(obj->model[b + 1], 20.0f);
                        func_8001C814_main(obj->model[b + 1], 1, 1);
                        func_8001C258_main(obj->model[b + 1], 4, 4);
                    }
                    if (a >= 0) {
                        func_80032FF8_main((s16)D_8010AE80_mgresultboard[a], D_8010AFB0_mgresultboard[i].unk_02);
                        func_8001C6A8_main(obj->model[a + 1], end);
                        func_8001C814_main(obj->model[a + 1], 1, 1);
                    }
                }
                break;
        }
    }
}

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
