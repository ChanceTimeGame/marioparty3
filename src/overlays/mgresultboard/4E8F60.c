#include "common.h"
#include "game/audio.h"

void func_8001C6A8_main(s32, f32);
s16 func_8000B0D4_main(s32, s32);
void func_80107CEC_mgresultboard(omObjData *);
void func_80107CF4_mgresultboard(void);

extern s32 D_8010AAF8_mgresultboard;
extern omObjData *D_8010AF98_mgresultboard;
extern void (*D_8010AF9C_mgresultboard)(omObjData *);
extern Vec D_8010AB10_mgresultboard[4];

void func_80107B40_mgresultboard(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x14, 0xE, 0, -1, NULL);
    D_8010AF98_mgresultboard = obj;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            obj->model[1] = func_8000B0D4_main(0x180001, 0x2B9);
        } else {
            obj->model[i + 1] = Hu3DModelLink(obj->model[1]);
        }
        func_8001C814_main(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 1], D_8010AB10_mgresultboard[i].x, D_8010AB10_mgresultboard[i].y,
                        D_8010AB10_mgresultboard[i].z);
        func_8001C6A8_main(obj->model[i + 1], 0.0f);
        func_8001C8A8_main(obj->model[i + 1], 2);
        func_8001C258_main(obj->model[i + 1], 4, 0);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, func_80107CF4_mgresultboard);
    while (D_8010AAF8_mgresultboard == 0) {
        HuPrcVSleep();
    }
    D_8010AF9C_mgresultboard = func_80107CEC_mgresultboard;
    while (TRUE) {
        D_8010AF9C_mgresultboard(obj);
        HuPrcVSleep();
    }
}

void func_80107CEC_mgresultboard(omObjData *obj) {
}

void func_80107CF4_mgresultboard(void) {
}
