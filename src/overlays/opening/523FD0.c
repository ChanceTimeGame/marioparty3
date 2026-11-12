#include "common.h"
#include "../ovl_80_shared_board/FA250.h"
#include "opening.h"

void func_801059A0_opening(void) {
    ovlEventCall(D_80114B50_opening, omovlevtno);
}

OP_FILE_END()

void opObjectInit(void) {
    Vec pos;
    Vec target;
    Vec up;

    omInitObjMan(0x20, 8);
    func_800142A0_main(8);
    func_8004A208_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    pos = D_80114C40_opening;
    target = D_80114C4C_opening;
    up = D_80114C58_opening;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 41.0f, 80.0f, 8000.0f);
    Hu3DCamSetPositionOrientation(0, &pos, &target, &up);
    func_80030030_main(1.0f);
    func_8004A950_main();
    pfInit();
    func_8005A6B0_main();
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x80, 0x80, 0x80);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightDirSet(1, 0.0f, 64.0f, 192.0f);
    D_800D2132_main = 0;
}

void opTitleObjectSetup(void) {
    opObjectInit();
    opTitleCreate();
}

void func_80105C2C_opening(void) {
    opObjectInit();
    opDemoCreate();
}

void opDemoObjectSetup(void) {
    opObjectInit();
    opDemoCreate();
}

OP_FILE_END()

void opEventInit(void) {
    opDemoEndReset();
}

void opTitleCreate(void) {
    opEventInit();
    D_80114EA0_opening = omAddPrcObj(opTitleMain, 0x5000, 0x800, 0);
}

void opDemoCreate(void) {
    opEventInit();
    D_80114EA0_opening = omAddPrcObj(opDemoMain, 0x5000, 0x800, 0);
}

Process *opDemoEventCreate(void) {
    Process *parent = HuPrcCurrentGet();
    Process *child = omAddPrcObj(opDemoEvent, 0x5000, 0x2000, 0);

    HuPrcChildLink(parent, child);
    return child;
}

void opDemoMain(void) {
    Process *self;
    Process *event;

    func_8001F38C_main(0, 0, 0);
    opDemoEventSetup();
    self = HuPrcCurrentGet();
    event = opDemoEventCreate();
    WipeCreateIn(0xB, 0x10);
    HuPrcSleep(0x10);
    while (TRUE) {
        HuPrcVSleep();
        if (omovlevtno == 1) {
            if (opBtnStartCheck() != 0 && _CheckFlag(0x32) != 0) {
                WipeColorSet(0xFF, 0xFF, 0xFF);
                WipeCreateOut(0xB, 0x14);
                HuAudSeqFadeOut(0x14);
                break;
            }
        } else if (opBtnStartCheck() != 0) {
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(0xB, 0x14);
            HuAudSeqFadeOut(0x14);
            break;
        }
        if (HuPrcChildGet(self) == 0 || opDemoEndGet() != 0) {
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(0xB, 0x14);
            HuAudSeqFadeOut(0x32);
            break;
        }
    }
    do {
        HuPrcVSleep();
    } while (WipeStatGet() != 0);
    if (HuPrcChildGet(self) != 0) {
        omDelPrcObj(event);
    }
    opDemoEventKill();
    func_8005F524_main();
    omOvlKill();
    if (omovlevtno == 0) {
        omOvlGotoEx(0x7A, 0, 0x82);
    } else if (omovlevtno == 1) {
        if (_CheckFlag(0x32) == 0) {
            _SetFlag(0x32);
            func_80050064_main(1);
        }
        omOvlReturnEx(1);
    } else {
        omOvlGotoEx(0x7A, 0, 0x82);
    }
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

Process *func_80105F68_opening(void) {
    Process *parent = HuPrcCurrentGet();
    Process *child = omAddPrcObj(opTitleSprMain, 0x5000, 0x2000, 0);

    HuPrcChildLink(parent, child);
    return child;
}

#ifdef NON_MATCHING
void opTitleMain(void) {
    Process *self;
    Process *spr;
    s32 time;

    func_8001F38C_main(0, 0x40, 0x40);
    time = 0;
    opTitleSetup();
    self = HuPrcCurrentGet();
    spr = func_80105F68_opening();
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(0xB, 0x10);
    HuPrcSleep(0x10);
    HuPrcSleep(0x3C);
    do {
        HuPrcVSleep();
        if (opBtnStartCheck() != 0) {
            WipeCreateOut(0xB, 0x14);
            HuAudSeqFadeOut(0x14);
            do {
                HuPrcVSleep();
            } while (WipeStatGet() != 0);
            if (HuPrcChildGet(self) != 0) {
                omDelPrcObj(spr);
            }
            opTitleKill();
            func_8005F524_main();
            omOvlKill();
            omOvlGotoEx(0x79, 0, 0x91);
            omDelPrcObj(NULL);
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        if (HuPrcChildGet(self) == 0 || opDemoEndGet() != 0) {
            break;
        }
    } while (time++ < 0x1519);
    WipeCreateOut(0xB, 0x14);
    HuAudSeqFadeOut(0x14);
    do {
        HuPrcVSleep();
    } while (WipeStatGet() != 0);
    if (HuPrcChildGet(self) != 0) {
        omDelPrcObj(spr);
    }
    opTitleKill();
    func_8005F524_main();
    omOvlKill();
    omOvlGotoEx(0x58, 1, 0x90);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opTitleMain);
#endif

s32 opBtnStartCheck(void) {
    if (GWContErrorGet() == 1) {
        return (D_800D5558_main[0] >> 12) & 1;
    }
    return 0;
}

void opDemoEndReset(void) {
    D_80114EA4_opening = 0;
}

void opDemoEndSet(s32 flag) {
    D_80114EA4_opening = flag;
}

s32 opDemoEndGet(void) {
    return D_80114EA4_opening;
}

OP_FILE_END()

void func_801061F0_opening(void) {
    func_8010621C_opening();
    func_801067D4_opening();
    func_80107A4C_opening();
}

#ifdef NON_MATCHING
void func_8010621C_opening(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_801155B0_opening[i] = -1;
        D_80114EB0_opening[i].espId = -1;
        D_80114EB0_opening[i].x = D_80114EB0_opening[i].y = 0;
        D_80114EB0_opening[i].scaleX = D_80114EB0_opening[i].scaleY = 0.0f;
        D_80114EB0_opening[i].unk14 = 0.0f;
        D_80114EB0_opening[i].unk18 = 0xFF;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_8010621C_opening);
#endif

s16 opAnimIdGet(s32 no) {
    return D_801155B0_opening[no];
}

s16 opEspIdGet(s32 no) {
    return D_80114EB0_opening[no].espId;
}

void opAnimCreate(s32 no, s32 dataNum) {
    D_801155B0_opening[no] = func_8000B838_main(dataNum);
}

void opAnimKill(s32 no) {
    if (D_801155B0_opening[no] != -1) {
        HuSprKill(D_801155B0_opening[no]);
    }
    D_801155B0_opening[no] = -1;
}

void opEspCreate(s32 no, s16 animNo) {
    D_80114EB0_opening[no].espId = InitEspriteSlot(D_801155B0_opening[animNo], 0, 0);
    opSprPosSet(no, 160, 120);
}

void opEspKill(s32 no) {
    if (D_80114EB0_opening[no].espId != -1) {
        func_8000C184_main(D_80114EB0_opening[no].espId);
    }
    D_80114EB0_opening[no].espId = -1;
}

void opSprCreate(s32 no, s32 dataNum) {
    opAnimCreate(no, dataNum);
    opEspCreate(no, no);
}

void opSprBGCreate(s32 no, s32 dataNum) {
    opSprCreate(no, dataNum);
    func_8000BC48_main(D_80114EB0_opening[no].espId, 0x4000);
}

void opSprKill(s32 no) {
    opEspKill(no);
    opAnimKill(no);
}

void opSprKillAll(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        opSprKill(i);
    }
}

void opSprDispOn(s32 no) {
    func_8000BB54_main(D_80114EB0_opening[no].espId);
}

void opSprDispOff(s32 no) {
    func_8000BB94_main(D_80114EB0_opening[no].espId);
}

void opSprBGDispOn(s32 no) {
    opSprDispOn(no);
}

void opSprBGDispOff(s32 no) {
    opSprDispOff(no);
}

void opSprPosSet(s32 no, s32 x, s32 y) {
    D_80114EB0_opening[no].x = x;
    D_80114EB0_opening[no].y = y;
    func_8000BBD4_main(D_80114EB0_opening[no].espId, x, y);
}

void opSprPosGet(s32 no, s32 *x, s32 *y) {
    *x = D_80114EB0_opening[no].x;
    *y = D_80114EB0_opening[no].y;
}

void opSprScaleSet(s32 no, f32 x, f32 y) {
    D_80114EB0_opening[no].scaleX = x;
    D_80114EB0_opening[no].scaleY = y;
    func_8000BE5C_main(D_80114EB0_opening[no].espId, x, y);
}

void opSprAlphaSet(s32 no, s16 alpha) {
    func_8000BBFC_main(D_80114EB0_opening[no].espId, alpha);
}

void opSprAttrSet(s32 no, u16 attr) {
    func_8000BC48_main(D_80114EB0_opening[no].espId, attr);
}

void opSprAttrReset(s32 no, u16 attr) {
    func_8000BC88_main(D_80114EB0_opening[no].espId, attr);
}

void func_80106734_opening(s32 no, u16 arg1) {
    func_8000BCC8_main(D_80114EB0_opening[no].espId, arg1);
}

void func_80106768_opening(s32 no, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_80114EB0_opening[no].espId, 1);
    func_8000BD94_main(D_80114EB0_opening[no].espId, arg1, arg2);
}

void func_801067D4_opening(void) {
    s32 i;

    for (i = 0; i < 160; i++) {
        D_80115630_opening[i].model = -1;
        D_80115630_opening[i].motion = -1;
    }
}

void opModelCreate(s32 no, s32 arg1, s32 dataNum) {
    s16 model = func_8000B108_main(arg1, dataNum);

    D_80115630_opening[no].model = model;
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
}

void opMotionCreate(s32 no, s32 dataNum, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(dataNum);
    D_80115630_opening[no].motion = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void opModelKill(s32 no) {
    if (D_80115630_opening[no].model != -1) {
        func_8001ACDC_main(D_80115630_opening[no].model);
        D_80115630_opening[no].model = -1;
    }
    if (D_80115630_opening[no].motion != -1) {
        func_8002D4B8_main(D_80115630_opening[no].motion);
        D_80115630_opening[no].motion = -1;
    }
}

void opModelKillAll(void) {
    s32 i;

    for (i = 0; i < 160; i++) {
        opModelKill(i);
    }
}

s16 opModelIdGet(s32 no) {
    return D_80115630_opening[no].model;
}

s16 opMotionIdGet(s32 no) {
    return D_80115630_opening[no].motion;
}

void opModelRotSet(s32 no, f32 x, f32 y, f32 z) {
    D_80115630_opening[no].rot.x = x;
    D_80115630_opening[no].rot.y = y;
    D_80115630_opening[no].rot.z = z;
    Hu3DModelRotSet(D_80115630_opening[no].model, x, y, z);
}

void opModelPosSet(s32 no, f32 x, f32 y, f32 z) {
    D_80115630_opening[no].pos[0] = x;
    D_80115630_opening[no].pos[1] = y;
    D_80115630_opening[no].pos[2] = z;
    Hu3DModelPosSet(D_80115630_opening[no].model, x, y, z);
}

void opModelScaleSet(s32 no, f32 x, f32 y, f32 z) {
    D_80115630_opening[no].scale.x = x;
    D_80115630_opening[no].scale.y = y;
    D_80115630_opening[no].scale.z = z;
    Hu3DModelScaleSet(D_80115630_opening[no].model, x, y, z);
}

void opModelPosGet(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80115630_opening[no].pos[0];
    *y = D_80115630_opening[no].pos[1];
    *z = D_80115630_opening[no].pos[2];
}

void opModelRotGet(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80115630_opening[no].rot.x;
    *y = D_80115630_opening[no].rot.y;
    *z = D_80115630_opening[no].rot.z;
}

void opModelScaleGet(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80115630_opening[no].scale.x;
    *y = D_80115630_opening[no].scale.y;
    *z = D_80115630_opening[no].scale.z;
}

void opModelDispOff(s32 no) {
    func_8001C258_main(D_80115630_opening[no].model, 4, 4);
}

void opModelDispOn(s32 no) {
    func_8001C258_main(D_80115630_opening[no].model, 4, 0);
}

void opMotionFlagSet(s32 no, s16 flag) {
    func_8001C814_main(D_80115630_opening[no].model, -1, flag);
}

void opMotionShiftSet(s32 no, s32 motNo, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(D_80115630_opening[no].model, D_80115630_opening[motNo].motion, arg2, arg3, arg4);
}

void func_80106DD0_opening(s32 no, s16 arg1) {
    func_8001C814_main(D_80115630_opening[no].model, arg1, 0);
}

void opMotionSpeedSet(s32 no, f32 speed) {
    func_8001C92C_main(D_80115630_opening[no].model, speed);
}

void opMotionTimeSet(s32 no, u32 time) {
    func_8001C6A8_main(D_80115630_opening[no].model, time);
}

void opMotionEndWait(s32 no) {
    while (HmfModelData[D_80115630_opening[no].model].unk40 !=
           D_800CCF58_main[HmfModelData[D_80115630_opening[no].model].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 opMotionEndCheck(s32 no) {
    return HmfModelData[D_80115630_opening[no].model].unk40 ==
           D_800CCF58_main[HmfModelData[D_80115630_opening[no].model].unk02].unk02;
}

void opMotionSet(s32 no, s32 motNo, s16 flag) {
    s16 model = opModelIdGet(no);
    s16 motion = opMotionIdGet(motNo);

    func_8001F304_main(model, motion);
    func_8001C814_main(model, -1, flag);
}

void func_80107048_opening(s32 dataNum) {
    D_801171B0_opening = func_8000B838_main(dataNum);
    D_801171B2_opening = InitEspriteSlot(D_801171B0_opening, 0, 0);
    func_8000BC48_main(D_801171B2_opening, 0x4000);
    func_8000BBD4_main(D_801171B2_opening, 160, 120);
}

void func_801070AC_opening(void) {
    func_8000C184_main(D_801171B2_opening);
    HuSprKill(D_801171B0_opening);
}

u32 func_801070D8_opening(u32 mes) {
    u8 buf[0x100];
    s32 size;
    void *copy;
    u32 ret;

    if (mes <= 0x80000000) {
        ret = mes;
    } else {
        size = func_800452A0_main(buf, (void *)mes);
        copy = HuMemAlloc(size);
        bcopy(buf, copy, size);
        ret = (u32)copy;
    }
    return ret;
}

#ifdef NON_MATCHING
void func_80107140_opening(s32 no, u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    u32 buf;
    s16 id;

    switch (type) {
        case 1:
            buf = func_801070D8_opening(mes);
            id = func_801074D8_opening(buf, x, y, w, h, type);
            break;
        case 2:
            buf = func_801070D8_opening(mes);
            id = func_80107640_opening(buf, x, y, w, h, type);
            break;
        case 3:
            buf = func_801070D8_opening(mes);
            id = func_801077E8_opening(buf, x, y, type);
            break;
        case 4:
            buf = func_801070D8_opening(mes);
            id = func_801078B4_opening(buf, x, y, type);
            break;
        case 5:
            buf = func_801070D8_opening(mes);
            id = func_80107980_opening(buf, x, y, type);
            break;
        case 0:
        default:
            buf = func_801070D8_opening(mes);
            id = func_8010738C_opening(buf, x, y, w, h, type);
            break;
    }
    if (buf > 0x80000000) {
        D_801171B8_opening[no].mesBuf = buf;
    }
    D_801171B8_opening[no].id = id;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107140_opening);
#endif

s16 func_8010738C_opening(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 8);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0xFF);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C154_main(win, 0xC0, 0xC0, 0xC0);
    func_8005FBF8_main(win, 0, 0x40, 0x40);
    func_8005C02C_main(win, 7);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_801074D8_opening(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 4);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0xFF);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0xC0, 0xC0, 0xC0);
    func_8005FBF8_main(win, 0xFF, 0xFF, 0xFF);
    func_8005C02C_main(win, 1);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80107640_opening(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 8);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 7, 0xFF, 0xFF, 0xFF);
    func_8005C060_main(win, 0, 0, 0, 0);
    func_8005C060_main(win, 3, 0, 0, 0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0xC0, 0xC0, 0);
    func_8005FBF8_main(win, 0xFF, 0xFF, 0xFF);
    func_8005C02C_main(win, 6);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_801077E8_opening(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_801078B4_opening(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x14);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 0);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80107980_opening(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005FE54_main(win, 1);
    func_80060C14_main(win, 0);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

void func_80107A4C_opening(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_801171B8_opening[i].id = -1;
        D_801171B8_opening[i].mesBuf = 0;
    }
}

void func_80107A90_opening(s32 no) {
    if (D_801171B8_opening[no].type == 3) {
        func_80060EA8_main(D_801171B8_opening[no].id, 1);
        func_800610E0_main(D_801171B8_opening[no].id);
    } else {
        func_8005FE90_main(D_801171B8_opening[no].id);
        func_8005F364_main(D_801171B8_opening[no].id);
        D_801171B8_opening[no].id = -1;
    }
    if (D_801171B8_opening[no].mesBuf != 0) {
        func_80019C00_main((void *)D_801171B8_opening[no].mesBuf);
        D_801171B8_opening[no].mesBuf = 0;
    }
}

void func_80107B74_opening(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (D_801171B8_opening[i].id != -1) {
            func_80107A90_opening(i);
        }
    }
}

void func_80107BD8_opening(s32 no, f32 x, f32 y) {
    func_8005BB18_main(D_801171B8_opening[no].id, x, y);
}

void func_80107C08_opening(s32 no, f32 x, f32 y) {
    func_8005BA90_main(D_801171B8_opening[no].id, x, y);
}

void func_80107C70_opening(s32 no) {
    func_8005FFA8_main(D_801171B8_opening[no].id);
}

void func_80107CA0_opening(s32 no) {
    func_8005FE90_main(D_801171B8_opening[no].id);
}

void func_80107CD0_opening(s32 no, u32 mes) {
    u32 buf;

    func_8005D294_main(D_801171B8_opening[no].id);
    if (D_801171B8_opening[no].mesBuf != 0) {
        func_80019C00_main((void *)D_801171B8_opening[no].mesBuf);
        D_801171B8_opening[no].mesBuf = 0;
    }
    buf = func_801070D8_opening(mes);
    if (buf > 0x80000000) {
        D_801171B8_opening[no].mesBuf = buf;
    }
    func_8005B43C_main(D_801171B8_opening[no].id, buf, -1, -1);
}

void func_80107D9C_opening(s32 no, s8 arg1, s32 arg2) {
    func_800601BC_main(D_801171B8_opening[no].id, arg2, arg1);
}

void func_80107DD8_opening(s32 no, s16 arg1, s32 arg2) {
    func_8005E1D8_main(D_801171B8_opening[no].id, arg1, arg2);
}

s16 func_80107E10_opening(s32 no) {
    return D_801171B8_opening[no].id;
}

void func_80107E2C_opening(s32 no) {
    while (func_8005E0C0_main(D_801171B8_opening[no].id) != 0) {
        HuPrcVSleep();
    }
}

void func_80107E80_opening(s32 btn) {
    do {
        HuPrcVSleep();
    } while (!(btn & D_800D5558_main[0]));
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107EBC_opening);

u16 func_80107EF4_opening(s32 val) {
    char buf[0x100];
    OpHmfCamView *view;

    HuPrcSleep(3);
    while (TRUE) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(buf, "\n%d\n", val);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            view = *(OpHmfCamView **)&HmfModelData[gCameraList->unk4].hmf->unkB8[4];
            sprintf(buf, "POS:%4.2f,%4.2f,%4.2f", view->pos.x, view->pos.y, view->pos.z);
            print8(16, 180, buf);
            sprintf(buf, "A T:%4.2f,%4.2f,%4.2f", view->at.x, view->at.y, view->at.z);
            print8(16, 190, buf);
            sprintf(buf, "U P:%4.2f,%4.2f,%4.2f", view->up.x, view->up.y, view->up.z);
            print8(16, 200, buf);
        } else {
            sprintf(buf, "%d", val);
            print8(16, 220, buf);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void opDemoEventSetup(void) {
    func_801061F0_opening();
    func_80110F48_opening();
    CameraViewportSet(0, &D_80114BB8_opening, &D_80114BC4_opening);
    CameraScissorSet(0, &D_80114BD0_opening);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    func_80112944_opening();
    func_80110B90_opening();
    opContErrorCreate();
}

void func_80108118_opening(s32 no, u32 mes) {
    func_80107140_opening(no, mes, 160, 194, 0, 0, 4);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114CE4_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114D84_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114D90_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114D9C_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114DA8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoEvent);

void opDemoEventKill(void) {
    func_80107B74_opening();
    opContErrorKill();
    func_80110B9C_opening();
    opWipeKill(15);
    opDemoObjKillAll();
    opDemoModelKill();
    opDemoSprKill();
    MBBackKill();
}

void func_80110B90_opening(void) {
    D_80117338_opening.obj = NULL;
}

void func_80110B9C_opening(void) {
    if (D_80117338_opening.obj != NULL) {
        CameraViewportSet(0, &D_80114BB8_opening, &D_80114BC4_opening);
        MBCameraOffsetSet(0, 0);
        omDelObj(D_80117338_opening.obj);
    }
    D_80117338_opening.obj = NULL;
}

#ifdef NON_MATCHING
void func_80110C04_opening(omObjData *obj) {
    Vec trans;
    f32 rnd;
    f32 ofs;

    if ((D_80117338_opening.sign = ~D_80117338_opening.sign)) {
        rnd = rand8() & 0xFF;
    } else {
        rnd = -(f32)(rand8() & 0xFF);
    }
    ofs = rnd * (1.0f / 255.0f) * ((1.0f - D_80117338_opening.time * 0.125f) * 0.8f + 0.2f) *
          D_80117338_opening.power;
    HuVecCopy3F(&trans, &D_80114BC4_opening);
    trans.y += ofs + ofs;
    CameraViewportSet(0, &D_80114BB8_opening, &trans);
    MBCameraOffsetSet(0, -ofs);
    if (++D_80117338_opening.time > D_80117338_opening.maxTime) {
        CameraViewportSet(0, &D_80114BB8_opening, &D_80114BC4_opening);
        MBCameraOffsetSet(0, 0);
        func_80110B9C_opening();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80110C04_opening);
#endif

void func_80110D8C_opening(s32 time, f32 power) {
    D_80117338_opening.time = 0;
    D_80117338_opening.maxTime = time;
    D_80117338_opening.power = power;
    D_80117338_opening.sign = 1;
    D_80117338_opening.obj = omAddObj(6, 0, 0, -1, func_80110C04_opening);
}

void opDemoCharCreate(s32 no, s32 dataNum, f32 x, f32 y, f32 z) {
    opModelCreate(no, dataNum, 0x6A9);
    opModelPosSet(no, x, y, z);
    opModelRotSet(no, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(no, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(no, 2);
}

void opDemoShadowCreate(s32 no, f32 x, f32 y, f32 z) {
    opModelCreate(no, 9, 0x229);
    opModelPosSet(no, x, y, z);
    opModelRotSet(no, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(no, 1.0f, 1.0f, 1.0f);
}

void opDemoModelKill(void) {
    opModelKillAll();
}

void opDemoSprKill(void) {
    opSprKillAll();
}

void func_80110F48_opening(void) {
    D_80117350_opening.obj = NULL;
    HuVecCopyXYZ(&D_80117350_opening.pos, 350.0f, 190.0f, 3770.0f);
    HuVecCopyXYZ(&D_80117350_opening.at, -1000.0f, 130.0f, 450.0f);
    HuVecCopyXYZ(&D_80117350_opening.up, 0.0f, 1.0f, 0.0f);
}

void func_80110FB0_opening(Vec *pos, Vec *at) {
    func_80111028_opening();
    HuVecCopy3F(&D_80117350_opening.pos, pos);
    HuVecCopy3F(&D_80117350_opening.at, at);
    D_80117350_opening.obj = omAddObj(6, 0, 0, -1, func_80111090_opening);
}

void func_80111028_opening(void) {
    if (D_80117350_opening.obj != NULL) {
        omDelObj(D_80117350_opening.obj);
    }
    D_80117350_opening.obj = NULL;
}

void func_8011105C_opening(void) {
    Hu3DCamSetPositionOrientation(0, &D_80117350_opening.pos, &D_80117350_opening.at, &D_80117350_opening.up);
    Hu3DCamUpdateMtx(0);
}

void func_80111090_opening(omObjData *obj) {
    func_8011105C_opening();
}

void func_801110AC_opening(f32 *posX, f32 *posY, f32 *posZ, f32 *atX, f32 *atY, f32 *atZ) {
    *posX = D_80117350_opening.pos.x;
    *posY = D_80117350_opening.pos.y;
    *posZ = D_80117350_opening.pos.z;
    *atX = D_80117350_opening.at.x;
    *atY = D_80117350_opening.at.y;
    *atZ = D_80117350_opening.at.z;
}

void func_801110F0_opening(f32 posX, f32 posY, f32 posZ, f32 atX, f32 atY, f32 atZ) {
    HuVecCopyXYZ(&D_80117350_opening.pos, posX, posY, posZ);
    HuVecCopyXYZ(&D_80117350_opening.at, atX, atY, atZ);
}

f32 func_80111164_opening(f32 x0, f32 z0, f32 x1, f32 z1) {
    return -(atan2df(z1 - z0, x1 - x0) - 90.0f);
}

f32 func_801111AC_opening(f32 from, f32 to, f32 step) {
    f32 diff = to - from;
    f32 abs;

    abs = diff;
    if (diff < 0.0f) {
        abs = diff + 360.0f;
    }
    diff = abs;
    if (diff > 180.0f) {
        if (360.0f - step < diff) {
            return to;
        }
        return from - step;
    }
    if (diff < step) {
        return to;
    }
    return from + step;
}

#ifdef NON_MATCHING
f32 func_8011124C_opening(f32 x0, f32 z0, f32 x1, f32 z1, f32 t) {
    f32 a0;
    f32 a1;
    f32 target;
    f32 ret;

    a0 = func_80111164_opening(0.0f, 0.0f, x0, z0);
    if (a0 < 0.0f) {
        a0 += 360.0f;
    }
    a1 = func_80111164_opening(0.0f, 0.0f, x1, z1);
    if (a1 < 0.0f) {
        a1 += 360.0f;
    }
    if ((a1 - a0 < 0.0f ? -(a1 - a0) : a1 - a0) < 5.0f) {
        return a1;
    }
    if (-z0 * x1 + x0 * z1 > 0.0f) {
        target = a1;
        if (!(a1 - a0 < 0.0f)) {
            target = a1 - 360.0f;
        }
        ret = (target - a0) * t + a0;
        if (ret < 0.0f) {
            ret += 360.0f;
        }
    } else {
        target = a1;
        if (!(a1 - a0 > 0.0f)) {
            target = a1 + 360.0f;
        }
        ret = (target - a0) * t + a0;
        if (ret > 360.0f) {
            ret -= 360.0f;
        }
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_8011124C_opening);
#endif

#ifdef NON_MATCHING
f32 func_80111490_opening(f32 angle, f32 x, f32 z, f32 t) {
    f32 diff = func_80111164_opening(0.0f, 0.0f, x, z);
    f32 ret;

    if (diff < 0.0f) {
        diff += 360.0f;
    }
    diff -= angle;
    if (diff < 0.0f) {
        diff += 360.0f;
    }
    if (!(diff > 180.0f)) {
        ret = diff * t;
    } else {
        ret = -(360.0f - diff) * t;
    }
    return ret + angle;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111490_opening);
#endif

#ifdef NON_MATCHING
void func_80111580_opening(void) {
    Vec pos;
    s16 model0;
    s16 model1;
    s32 i;
    f32 t;
    f32 angle;
    f32 scale;

    model0 = func_80111984_opening(0x110012, 0x689);
    model1 = func_80111984_opening(0x110012, 0x689);
    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
    for (i = 0; i < 120; i++) {
        if (i == 90) {
            func_80107CA0_opening(0);
        }
        t = i * (1.0f / 120.0f);
        HuSqrtf(t);
        angle = t * 360.0f;
        scale = (1.0f - t) * 8.0f;
        pos.x = (1.0f - t) * 100.0f * sindf(angle);
        pos.y = 40.0f - pos.x * 0.2f - (1.0f - t) * 120.0f * cosdf(angle);
        pos.z = (1.0f - t) * 800.0f * cosdf(angle) + -200.0f;
        func_80111DDC_opening(model0, pos.x, pos.y, pos.z, scale);
        func_80111DDC_opening(model0, pos.x, pos.y, pos.z, scale);
        func_80111DDC_opening(model1, pos.x, pos.y, pos.z, scale);
        func_80111DDC_opening(model1, pos.x, pos.y, pos.z, scale);
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    func_8001ACDC_main(model0);
    func_8001ACDC_main(model1);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111580_opening);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801117D4_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111984_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111B34_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111C08_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111C30_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111C88_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111DDC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111F58_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80112120_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opTitleSetup);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opTitleSprMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opTitleKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80112944_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoObjKillAll);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoObjKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoObjCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80112A74_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80112BA0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80112C8C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80112D30_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoOutEffMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoOutEffCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoGuideInEffMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoGuideInEffCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoStarWaitMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoStarWaitCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801134FC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_8011361C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_8011373C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801139B0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80113AE8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80113E8C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80114150_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80114250_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opWipeDraw);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opWipeColorSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opWipeInMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opWipeOutMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opWipeKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opWipeInCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opWipeOutCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opWipeWhiteInCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opWipeWhiteOutCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801149A4_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opSleep);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opContErrorCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opContErrorDispOn);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opContErrorDispOff);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opContErrorKill);
