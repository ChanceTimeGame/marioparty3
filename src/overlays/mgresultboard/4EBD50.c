#include "common.h"
#include "game/hmfman.h"
#include "mgresultboard.h"

s16 func_8000B0D4_main(s32, s32);
void func_8010AADC_mgresultboard(omObjData *);
void func_8010AAE4_mgresultboard(void);

extern void (*D_8010AFA4_mgresultboard)(omObjData *);
extern Vec D_8010AC90_mgresultboard[4];

void func_8010A930_mgresultboard(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x14, 0xC, 0, -1, NULL);
    D_8010AFA0_mgresultboard = obj;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            obj->model[1] = func_8000B0D4_main(0x180002, 0x2B9);
        } else {
            obj->model[i + 1] = Hu3DModelLink(obj->model[1]);
        }
        func_8001C814_main(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 1], D_8010AC90_mgresultboard[i].x, D_8010AC90_mgresultboard[i].y,
                        D_8010AC90_mgresultboard[i].z);
        func_8001C6A8_main(obj->model[i + 1], 0.0f);
        func_8001C8A8_main(obj->model[i + 1], 2);
        func_8001C258_main(obj->model[i + 1], 4, 0);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, func_8010AAE4_mgresultboard);
    while (D_8010AAF8_mgresultboard == 0) {
        HuPrcVSleep();
    }
    D_8010AFA4_mgresultboard = func_8010AADC_mgresultboard;
    while (TRUE) {
        D_8010AFA4_mgresultboard(obj);
        HuPrcVSleep();
    }
}

void func_8010AADC_mgresultboard(omObjData *obj) {
}

void func_8010AAE4_mgresultboard(void) {
}
