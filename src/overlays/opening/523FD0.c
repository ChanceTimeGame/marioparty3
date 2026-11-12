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

void opSprAlphaSet(s32 no, u16 alpha) {
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

void func_80107EBC_opening(s32 no, s16 arg1) {
    func_8005BE30_main(D_801171B8_opening[no].id, arg1);
}

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

#ifdef NON_MATCHING
void opDemoEvent(void) {
    f32 s1C0, s1C4, s1C8, s1CC, s1D0, s248, s24C, s250, s254, s258, s25C;
    f32 s368, s36C, s370, s374, s378, s37C, s4D0, s4D4;
    s32 flag;
    s32 j;
    f32 ang;
    f32 t60;
    HmfModel *temp_s1;
    OpHmfMotionObj *temp_v0_12;
    f32 temp_f0;
    f32 temp_f0_10;
    f32 temp_f0_11;
    f32 temp_f0_12;
    f32 temp_f0_13;
    f32 temp_f0_14;
    f32 temp_f0_15;
    f32 temp_f0_16;
    f32 temp_f0_17;
    f32 temp_f0_18;
    f32 temp_f0_19;
    f32 temp_f0_2;
    f32 temp_f0_20;
    f32 temp_f0_21;
    f32 temp_f0_22;
    f32 temp_f0_23;
    f32 temp_f0_24;
    f32 temp_f0_25;
    f32 temp_f0_26;
    f32 temp_f0_27;
    f32 temp_f0_28;
    f32 temp_f0_29;
    f32 temp_f0_3;
    f32 temp_f0_30;
    f32 temp_f0_31;
    f32 temp_f0_32;
    f32 temp_f0_33;
    f32 temp_f0_34;
    f32 temp_f0_35;
    f32 temp_f0_36;
    f32 temp_f0_37;
    f32 temp_f0_38;
    f32 temp_f0_39;
    f32 temp_f0_4;
    f32 temp_f0_40;
    f32 temp_f0_41;
    f32 temp_f0_42;
    f32 temp_f0_43;
    f32 temp_f0_44;
    f32 temp_f0_45;
    f32 temp_f0_46;
    f32 temp_f0_47;
    f32 temp_f0_48;
    f32 temp_f0_49;
    f32 temp_f0_5;
    f32 temp_f0_50;
    f32 temp_f0_51;
    f32 temp_f0_52;
    f32 temp_f0_53;
    f32 temp_f0_54;
    f32 temp_f0_55;
    f32 temp_f0_56;
    f32 temp_f0_57;
    f32 temp_f0_58;
    f32 temp_f0_59;
    f32 temp_f0_6;
    f32 temp_f0_60;
    f32 temp_f0_61;
    f32 temp_f0_62;
    f32 temp_f0_63;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f20;
    f32 temp_f20_10;
    f32 temp_f20_11;
    f32 temp_f20_12;
    f32 temp_f20_13;
    f32 temp_f20_14;
    f32 temp_f20_15;
    f32 temp_f20_16;
    f32 temp_f20_17;
    f32 temp_f20_18;
    f32 temp_f20_19;
    f32 temp_f20_2;
    f32 temp_f20_20;
    f32 temp_f20_21;
    f32 temp_f20_22;
    f32 temp_f20_23;
    f32 temp_f20_24;
    f32 temp_f20_25;
    f32 temp_f20_26;
    f32 temp_f20_27;
    f32 temp_f20_28;
    f32 temp_f20_29;
    f32 temp_f20_3;
    f32 temp_f20_30;
    f32 temp_f20_31;
    f32 temp_f20_32;
    f32 temp_f20_33;
    f32 temp_f20_34;
    f32 temp_f20_35;
    f32 temp_f20_36;
    f32 temp_f20_37;
    f32 temp_f20_38;
    f32 temp_f20_4;
    f32 temp_f20_5;
    f32 temp_f20_6;
    f32 temp_f20_7;
    f32 temp_f20_8;
    f32 temp_f20_9;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f22_3;
    f32 temp_f22_4;
    f32 temp_f22_5;
    f32 temp_f22_6;
    f32 temp_f22_7;
    f32 temp_f22_8;
    f32 temp_f22_9;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f24_3;
    f32 temp_f24_4;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f2_7;
    f32 temp_f2_8;
    f32 temp_f2_9;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f2;
    f32 var_f20;
    f32 var_f22;
    f32 var_f2_2;
    f32 var_f2_3;
    f32 var_f2_4;
    f32 var_f2_5;
    f32 var_f2_6;
    s16 temp_s1_2;
    s16 temp_s1_3;
    s16 temp_s1_4;
    s16 temp_v0_10;
    s16 temp_v0_11;
    s16 temp_v0_13;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v0_9;
    s32 var_s0_10;
    s32 var_s0_11;
    s32 var_s0_12;
    s32 var_s0_13;
    s32 var_s0_14;
    s32 var_s0_15;
    s32 var_s0_16;
    s32 var_s0_17;
    s32 var_s0_18;
    s32 var_s0_19;
    s32 var_s0_2;
    s32 var_s0_20;
    s32 var_s0_21;
    s32 var_s0_22;
    s32 var_s0_23;
    s32 var_s0_24;
    s32 var_s0_25;
    s32 var_s0_26;
    s32 var_s0_27;
    s32 var_s0_28;
    s32 var_s0_29;
    s32 var_s0_3;
    s32 var_s0_30;
    s32 var_s0_31;
    s32 var_s0_32;
    s32 var_s0_33;
    s32 var_s0_34;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_s0_7;
    s32 var_s0_8;
    s32 var_s0_9;
    s32 var_s1;
    s32 var_s3;
    s32 var_v0_2;

    D_800CD280_main = 1;
    if (omovlevtno == 0) {
        flag = 1;
    } else {
        flag = omovlevtno == 1;
    }
    opContErrorDispOn();
    if (flag != 0) {
        HuAudSeqPlay(0x39);
    }
    HuAudFXPlay(0x234);
    MBBackLoad(0x1F);
    func_800E9344_shared_board(10.0f, 10000.0f);
    opModelCreate(0xB, 0xF0007, 0x2A9);
    opModelPosSet(0xB, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(0xB, 1.0f, 1.0f, 1.0f);
    opMotionTimeSet(0xB, 0);
    opMotionFlagSet(0xB, 1);
    opModelDispOff(0xB);
    ({
    OpDemoStar stars[10] = {
        { 20, 20, 3, 0xFFFFFF00 }, { 50, 180, 8, 0xFFFFFF00 }, { 30, 120, 20, 0xFFFFFF00 }, { 75, 80, 75, 0xC0F08000 },
        { 90, 200, 120, 0xFFFFFF00 }, { 120, 45, 45, 0xC0C00000 }, { 160, 80, 24, 0xFFFFFF00 }, { 200, 160, 62, 0xC0C0FF00 },
        { 220, 120, 0, 0x8040FF00 }, { 240, 50, 80, 0xFFFFFF00 },
    };
    s32 i;
    func_80111C08_opening();
    for (i = 0; i < 10; i++) {
        if (i == 0) {
            opSprBGCreate(0, 0xF0009);
        } else if (i == 1) {
            opSprBGCreate(1, 0xF000A);
        } else {
            if (i & 1) {
                opEspCreate(i, 0);
            } else {
                opEspCreate(i, 1);
            }
            opSprAttrSet(i, 0x4000);
            func_80106768_opening(i, 0, func_80111C30_opening(6));
        }
        opSprPosSet(i, stars[i].x, stars[i].y);
        func_8000BEAC_main(opEspIdGet(i), 0xFF, 0xFF, 0xFF);
    }
    });
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    {
    Vec v20 = { 600.0f, 80.0f, 800.0f };
    Vec v30 = { 0.0f, 0.0f, -100.0f };
    func_800E92D4_shared_board();
    func_80110FB0_opening(&v20, &v30);
    }
    if (flag != 0) {
        func_80108118_opening(0, 0x5A00);
        func_80107CD0_opening(0, 0x4D01);
        func_80107E2C_opening(0);
    } else {
        func_80108118_opening(0, 0x5A00);
        func_80107CD0_opening(0, 0x4D00);
        opSleep(0x3C);
    }
    if (flag != 0) {
        HuAudFXPlay(0x235);
    }
    func_80111580_opening(0.0f, 0.0f, 0.0f, 0.0f);
    {
    Vec v40 = { 0.0f, 0.0f, 2000.0f };
    Vec v50 = { 0.0f, 0.0f, 0.0f };
    func_80110FB0_opening(&v40, &v50);
    }
    opModelDispOn(0xB);
    if (flag != 0) {
        HuAudFXPlay(0x236);
    }
    func_80106DD0_opening(0xB, 3);
    opMotionEndWait(0xB);
    if (flag != 0) {
        HuAudFXPlay(0x237);
    }
    opWipeWhiteOutCreate(0xF, 0x14);
    HuPrcSleep(0x32);
    opModelKill(0xB);
    opModelCreate(0xB, 0xA0122, 0x2A9);
    opModelPosSet(0xB, 0.0f, 0.0f, 0.0f);
    opModelRotSet(0xB, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(0xB, 1.0f, 1.0f, 1.0f);
    opMotionCreate(0x6C, 0xA0123, 0);
    opMotionCreate(0x6D, 0xA0124, 0);
    opMotionCreate(0x6E, 0xA012B, 0);
    opMotionSet(0xB, 0x6D, 1);
    opMotionFlagSet(0xB, 1);
    opMotionTimeSet(0xB, 1);
    func_80046030_main(opModelIdGet(0xB), -5);
    opDemoStarWaitCreate(0, 0xB, 0.0f, 0.0f, 0.0f, 50.0f, 0x2D);
    opWipeWhiteInCreate(0xF, 0x10);
    HuPrcSleep(0x10);
    HuPrcSleep(0x14);
    func_80107C70_opening(0);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D03);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D02);
        opSleep(0x78);
    }
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D05);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D04);
        opSleep(0x78);
    }
    func_80107CD0_opening(0, 0x4D06);
    opDemoObjKill(0);
    temp_s1 = &HmfModelData[opModelIdGet(0xB)];
    {
    Vec v60, v70, v80;
    f32 mtx[4][4];
    func_8002367C_main(mtx, (f32 (*)[4])temp_s1->mtx);
    var_f20 = 0.0f;
    opMotionShiftSet(0xB, 0x6E, 4, 4, 2);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D07);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D06);
        opSleep(0x78);
    }
    func_80107CA0_opening(0);
    opMotionFlagSet(0xB, 1);
    if (flag != 0) {
        HuAudFXPlay(0x238);
    }
    opModelPosGet(0xB, &v60.x, &v60.y, &v60.z);
    HuVecCopyXYZ(&v70, -1000.0f, -2000.0f, 0.0f);
    var_s0_2 = 0;
    do {
        temp_f4 = (f32) var_s0_2 * 0.033333335f;
        HuVecCopyXYZ(&v80, ((v70.x - v60.x) * temp_f4) + v60.x, ((v70.y - v60.y) * temp_f4 * temp_f4) + v60.y, ((v70.z - v60.z) * temp_f4) + v60.z);
        opModelPosSet(0xB, v80.x, v80.y, v80.z);
        var_f20 += 17.23f;
        if (var_f20 > 360.0f) {
            var_f20 -= 360.0f;
        }
        temp_s1->rot.z = var_f20;
        HuPrcVSleep();
        var_s0_2 += 1;
    } while (var_s0_2 < 0x1E);
    func_8002367C_main((f32 (*)[4])HmfModelData[opModelIdGet(0xB)].mtx, mtx);
    }
    HuPrcSleep(0x10);
    func_80107C70_opening(0);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D09);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D08);
        opSleep(0x3C);
    }
    opWipeOutCreate(0xF, 0x14);
    if (flag != 0) {
        HuAudSeqFadeOut(0x17);
    }
    func_8004AB0C_main(0x17);
    HuPrcSleep(0x17);
    func_80107CA0_opening(0);
    var_s0_3 = 0;
    do {
        opSprKill(var_s0_3);
        var_s0_3 += 1;
    } while (var_s0_3 < 0xA);
    opModelKill(0x6E);
    MBBackKill();
    MBBackLoad(0x20);
    func_800E92D4_shared_board();
    Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
    func_80110FB0_opening(&D_80114B70_opening[0], &D_80114B70_opening[1]);
    opModelDispOff(0xB);
    opDemoCharCreate(0, 0x200A0, 19.0f, 0.0f, 2700.0f);
    opModelRotSet(0, 0.0f, -30.0f, 0.0f);
    temp_v0_2 = opModelIdGet(0);
    func_80017790_main(temp_v0_2, 2, 0, 0x200A4);
    func_80017A84_main(temp_v0_2, 2, 0, 1, 0);
    opDemoShadowCreate(0x20, 19.0f, 0.0f, 2700.0f);
    opDemoCharCreate(1, 0x300A0, -250.0f, 0.0f, 2920.5f);
    temp_v0_3 = opModelIdGet(1);
    func_80017790_main(temp_v0_3, 2, 1, 0x300A4);
    func_80017A84_main(temp_v0_3, 2, 1, 7, 0);
    opDemoShadowCreate(0x21, -250.0f, 0.0f, 2920.5f);
    opModelDispOff(1);
    opDemoCharCreate(2, 0x700A0, 140.0f, 0.0f, 2680.0f);
    temp_v0_4 = opModelIdGet(2);
    func_80017790_main(temp_v0_4, 2, 2, 0x700A4);
    func_80017A84_main(temp_v0_4, 2, 2, 3, 0);
    opDemoShadowCreate(0x22, 140.0f, 0.0f, 2680.0f);
    opModelScaleSet(0x22, 1.5f, 1.0f, 1.5f);
    opModelDispOff(2);
    opDemoCharCreate(3, 0x400A0, 240.0f, 0.0f, 2680.0f);
    temp_v0_5 = opModelIdGet(3);
    func_80017790_main(temp_v0_5, 2, 3, 0x400A4);
    func_80017A84_main(temp_v0_5, 2, 3, 6, 0);
    opDemoShadowCreate(0x23, 240.0f, 0.0f, 2680.0f);
    opModelDispOff(3);
    opModelDispOff(0x23);
    opDemoCharCreate(4, 0x500A0, -240.0f, 0.0f, 2760.0f);
    temp_v0_6 = opModelIdGet(4);
    func_80017790_main(temp_v0_6, 2, 4, 0x500A4);
    func_80017A84_main(temp_v0_6, 2, 4, 9, 0);
    opDemoShadowCreate(0x24, 240.0f, 0.0f, 2680.0f);
    opModelDispOff(4);
    opModelDispOff(0x24);
    opDemoCharCreate(5, 0x600A0, -140.0f, 0.0f, 2710.0f);
    temp_v0_7 = opModelIdGet(5);
    func_80017790_main(temp_v0_7, 2, 5, 0x600A4);
    func_80017A84_main(temp_v0_7, 2, 5, 7, 0);
    opDemoShadowCreate(0x25, -140.0f, 0.0f, 2710.0f);
    opModelScaleSet(0x25, 1.5f, 1.0f, 1.5f);
    opModelDispOff(5);
    opModelDispOff(0x25);
    opModelCreate(6, 0xF0004, 0x6A9);
    opModelPosSet(6, -77.25f, 40.0f, 2632.5f);
    opModelScaleSet(6, 1.0f, 1.0f, 1.0f);
    opModelPosSet(0x21, -77.25f, 0.0f, 2632.5f);
    opModelCreate(7, 0xF0003, 0x6A9);
    opModelPosSet(7, 19.0f, 15.0f, 2700.0f);
    opModelRotSet(7, 0.0f, -30.0f, 0.0f);
    opModelScaleSet(7, 1.0f, 1.0f, 1.0f);
    opModelPosSet(0x22, 19.0f, 15.0f, 2700.0f);
    opModelCreate(8, 0xF0005, 0x6A9);
    opModelPosSet(8, -51.0f, 92.5f, 2651.25f);
    opModelScaleSet(8, 1.0f, 1.0f, 1.0f);
    opModelCreate(9, 0xF0002, 0x2A9);
    opModelPosSet(9, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(9, 1.0f, 1.0f, 1.0f);
    opModelCreate(0xA, 0xA015E, 0xAA9);
    opModelPosSet(0xA, -430.0f, 60.0f, 2605.0f);
    opModelScaleSet(0xA, 0.3f, 0.3f, 0.3f);
    opMotionFlagSet(0xA, 2);
    func_80114250_opening(0xC, 0xA, -340.0f, 60.0f, 2555.0f);
    opModelCreate(0x1A, 0xB0001, 0x6A9);
    opModelPosSet(0x1A, -400.0f, 25.0f, 2650.0f);
    opModelScaleSet(0x1A, 1.8f, 1.0f, 1.8f);
    opMotionTimeSet(0x1A, 0);
    opMotionFlagSet(0x1A, 1);
    opModelDispOff(0x1A);
    opModelCreate(0x1B, 0xA015E, 0xAA9);
    opModelPosSet(0x1B, 0.0f, 100.0f, 100.0f);
    opModelScaleSet(0x1B, 0.3f, 0.3f, 0.3f);
    opMotionFlagSet(0x1B, 2);
    func_80114250_opening(0xB, 0x1B, -340.0f, 80.0f, 3100.0f);
    opMotionCreate(0x28, 0x20000, 0);
    opMotionCreate(0x29, 0x20001, 0);
    opMotionCreate(0x2A, 0xF000B, 0);
    opMotionCreate(0x2B, 0xF000C, 0);
    opMotionCreate(0x2C, 0x2001B, 0);
    opMotionCreate(0x2D, 0x1D003B, 0);
    opMotionCreate(0x2E, 0xF000D, 0);
    opMotionCreate(0x2F, 0xF000E, 0);
    opMotionCreate(0x32, 0xF0010, 0);
    opMotionCreate(0x33, 0x2009C, 0);
    opMotionCreate(0x34, 0xF0011, 0);
    opMotionCreate(0x35, 0x2009B, 0);
    opMotionCreate(0x38, 0x30000, 0);
    opMotionCreate(0x39, 0x30001, 0);
    opMotionCreate(0x3A, 0xF0012, 0);
    opMotionCreate(0x3C, 0x3007A, 0);
    opMotionCreate(0x3D, 0x3009C, 0);
    opMotionCreate(0x3E, 0x3009B, 0);
    opMotionCreate(0x40, 0x70000, 0);
    opMotionCreate(0x41, 0x70001, 0);
    opMotionCreate(0x42, 0x1D0053, 0);
    opMotionCreate(0x43, 0xF0014, 0);
    opMotionCreate(0x46, 0x7009C, 0);
    opMotionCreate(0x47, 0x7009B, 0);
    opMotionCreate(0x48, 0x40000, 0);
    opMotionCreate(0x49, 0x40001, 0);
    opMotionCreate(0x4A, 0xF0015, 0);
    opMotionCreate(0x4D, 0x4009C, 0);
    opMotionCreate(0x4E, 0x40032, 0);
    opMotionCreate(0x4F, 0x4009B, 0);
    opMotionCreate(0x50, 0x50000, 0);
    opMotionCreate(0x51, 0x50001, 0);
    opMotionCreate(0x52, 0xF0016, 0);
    opMotionCreate(0x55, 0x5009C, 0);
    opMotionCreate(0x56, 0x50033, 0);
    opMotionCreate(0x57, 0x5009B, 0);
    opMotionCreate(0x58, 0x60000, 0);
    opMotionCreate(0x59, 0x60001, 0);
    opMotionCreate(0x5A, 0xF0018, 0);
    opMotionCreate(0x5B, 0xF0019, 0);
    opMotionCreate(0x5E, 0x6009C, 0);
    opMotionCreate(0x5F, 0xF001B, 0);
    opMotionCreate(0x60, 0x6009B, 0);
    opModelDispOn(0xB);
    opModelPosSet(0xB, 920.0f, 2060.0f, 2580.0f);
    opModelRotSet(0xB, 0.0f, 45.0f, 0.0f);
    opModelScaleSet(0xB, 2.5f, 2.5f, 2.5f);
    opMotionFlagSet(0xB, 1);
    opMotionSet(0xB, 0x6D, 1);
    opMotionFlagSet(0xB, 1);
    opMotionTimeSet(0xB, 1);
    opMotionSet(0, 0x2A, 2);
    opWipeInCreate(0xF, 0x10);
    HuPrcSleep(8);
    if (flag == 0) {
        HuAudSeqPlay(1);
    }
    HuPrcSleep(8);
    if (flag != 0) {
        HuAudSeqPlay(0x3A);
    }
    HuPrcSleep(0x1E);
    func_80107C70_opening(0);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D0B);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D0A);
        opSleep(0x3C);
    }
    opMotionShiftSet(0, 0x2B, 4, 4, 0);
    opMotionEndWait(0);
    opMotionShiftSet(0, 0x32, 4, 4, 2);
    HuPrcSleep(0x14);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D0D);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D0C);
        opSleep(0x1C);
    }
    func_80107CA0_opening(0);
    {
    Vec v90, vA0, vB0;
    opModelPosGet(0xB, &v90.x, &v90.y, &v90.z);
    HuVecCopyXYZ(&vA0, -580.0f, 60.0f, 2580.0f);
    var_s0_4 = 0;
    do {
        temp_f20 = (f32) var_s0_4 * 0.0625f;
        temp_f20_2 = temp_f20 * temp_f20;
        HuVecCopyXYZ(&vB0, ((vA0.x - v90.x) * temp_f20_2) + v90.x, ((vA0.y - v90.y) * temp_f20_2) + v90.y, ((vA0.z - v90.z) * temp_f20_2) + v90.z);
        opModelPosSet(0xB, vB0.x, vB0.y, vB0.z);
        HuPrcVSleep();
        if (var_s0_4 == 0xE) {
            opModelDispOn(0x1A);
            opMotionTimeSet(0x1A, 0);
            func_80106DD0_opening(0x1A, 1);
        }
        var_s0_4 += 1;
    } while (var_s0_4 < 0x11);
    if (flag != 0) {
        HuAudFXPlay(0x239);
    }
    func_80114150_opening(0xB, -1580.0f, 600.0f, 3430.0f, 0x28);
    func_80114150_opening(0xC, -780.0f, 590.0f, 3430.0f, 0x28);
    func_80110D8C_opening(0xC, 4.0f);
    opMotionShiftSet(0, 0x2C, 4, 4, 2);
    ({
    Vec rot[4];
    var_s0_5 = 0;
    if (flag != 0) {
        HuAudFXPlay(0x287);
        var_s0_5 = 0;
    }
    for (var_s0_5 = 0; var_s0_5 < 4; var_s0_5++) {
        rot[var_s0_5].x = rot[var_s0_5].y = rot[var_s0_5].z = 0.0f;
    }
    var_s0_6 = 0;
    do {
        temp_f20_3 = (f32) var_s0_6 * 0.05f;
        HuVecCopyXYZ(&v90, 19.0f, 0.0f, 2700.0f);
        HuVecCopyXYZ(&vA0, 1519.0f, 1500.0f, 2700.0f);
        HuVecCopyXYZ(&vB0, ((vA0.x - v90.x) * temp_f20_3) + v90.x, ((vA0.y - v90.y) * temp_f20_3) + v90.y, ((vA0.z - v90.z) * temp_f20_3) + v90.z);
        opModelPosSet(0, vB0.x, vB0.y, vB0.z);
        opModelPosSet(0x20, vB0.x, 0.0f, vB0.z);
        temp_f0 = 1.0f - (temp_f20_3 * 0.9f);
        opModelScaleSet(0x20, temp_f0, temp_f0, temp_f0);
        opModelIdGet(0);
        opModelRotSet(0, rot[0].x, rot[0].y, rot[0].z);
        var_f0 = rot[0].x + 33.0f;
        if (!(var_f0 < 360.0f)) {
            var_f0 -= 360.0f;
        }
        rot[0].x = var_f0;
        HuVecCopyXYZ(&v90, -77.25f, 40.0f, 2632.5f);
        HuVecCopyXYZ(&vA0, 922.75f, 1540.0f, 2632.5f);
        HuVecCopyXYZ(&vB0, ((vA0.x - v90.x) * temp_f20_3) + v90.x, ((vA0.y - v90.y) * temp_f20_3) + v90.y, ((vA0.z - v90.z) * temp_f20_3) + v90.z);
        opModelPosSet(6, vB0.x, vB0.y, vB0.z);
        opModelPosSet(0x21, vB0.x, 0.0f, vB0.z);
        temp_f0_2 = 1.0f - (temp_f20_3 * 0.9f);
        opModelScaleSet(0x21, temp_f0_2, temp_f0_2, temp_f0_2);
        opModelIdGet(6);
        opModelRotSet(6, rot[1].x, rot[1].y, rot[1].z);
        var_f2 = rot[1].x + 66.0f;
        if (!(var_f2 < 360.0f)) {
            var_f2 -= 360.0f;
        }
        rot[1].x = var_f2;
        var_f2_2 = rot[1].y + 12.0f;
        if (!(var_f2_2 < 360.0f)) {
            var_f2_2 -= 360.0f;
        }
        rot[1].y = var_f2_2;
        HuVecCopyXYZ(&v90, 19.0f, 15.0f, 2700.0f);
        HuVecCopyXYZ(&vA0, 1419.0f, 1515.0f, 2700.0f);
        HuVecCopyXYZ(&vB0, ((vA0.x - v90.x) * temp_f20_3) + v90.x, ((vA0.y - v90.y) * temp_f20_3) + v90.y, ((vA0.z - v90.z) * temp_f20_3) + v90.z);
        opModelPosSet(7, vB0.x, vB0.y, vB0.z);
        opModelPosSet(0x22, vB0.x, 0.0f, vB0.z);
        temp_f0_3 = 1.0f - (temp_f20_3 * 0.9f);
        opModelScaleSet(0x22, temp_f0_3, temp_f0_3, temp_f0_3);
        opModelIdGet(7);
        opModelRotSet(7, rot[2].x, rot[2].y, rot[2].z);
        var_f2_3 = rot[2].x + 13.0f;
        if (!(var_f2_3 < 360.0f)) {
            var_f2_3 -= 360.0f;
        }
        rot[2].x = var_f2_3;
        var_f2_4 = rot[2].y + 42.0f;
        if (!(var_f2_4 < 360.0f)) {
            var_f2_4 -= 360.0f;
        }
        rot[2].y = var_f2_4;
        HuVecCopyXYZ(&v90, -51.0f, 92.5f, 2651.25f);
        HuVecCopyXYZ(&vA0, 1549.0f, 1592.5f, 2651.25f);
        HuVecCopyXYZ(&vB0, ((vA0.x - v90.x) * temp_f20_3) + v90.x, ((vA0.y - v90.y) * temp_f20_3) + v90.y, ((vA0.z - v90.z) * temp_f20_3) + v90.z);
        opModelPosSet(8, vB0.x, vB0.y, vB0.z);
        opModelIdGet(8);
        opModelRotSet(8, rot[3].x, rot[3].y, rot[3].z);
        var_f2_5 = rot[3].x + 123.0f;
        if (!(var_f2_5 < 360.0f)) {
            var_f2_5 -= 360.0f;
        }
        rot[3].x = var_f2_5;
        var_f2_6 = rot[3].y + 45.0f;
        if (!(var_f2_6 < 360.0f)) {
            var_f2_6 -= 360.0f;
        }
        rot[3].y = var_f2_6;
        HuPrcVSleep();
        var_s0_6 += 1;
    } while (var_s0_6 < 0x15);
    });
    }
    HuPrcSleep(0x14);
    opModelKill(0x1A);
    HuPrcSleep(3);
    opMotionShiftSet(0, 0x34, 4, 4, 2);
    opMotionShiftSet(1, 0x39, 4, 4, 2);
    opMotionShiftSet(2, 0x41, 4, 4, 2);
    opMotionShiftSet(3, 0x49, 4, 4, 2);
    opMotionShiftSet(4, 0x51, 4, 4, 2);
    opMotionShiftSet(5, 0x59, 4, 4, 2);
    opMotionSpeedSet(1, 1.6f);
    opMotionSpeedSet(2, 1.6f);
    opMotionSpeedSet(3, 1.6f);
    opMotionSpeedSet(4, 1.6f);
    opMotionSpeedSet(5, 1.6f);
    opModelDispOn(1);
    opModelDispOn(2);
    opModelDispOn(3);
    opModelDispOn(4);
    opModelDispOn(5);
    opModelDispOn(0x20);
    opModelScaleSet(0x20, 1.0f, 1.0f, 1.0f);
    opModelDispOn(0x21);
    opModelScaleSet(0x21, 1.0f, 1.0f, 1.0f);
    opModelDispOn(0x22);
    opModelScaleSet(0x22, 1.0f, 1.0f, 1.0f);
    opModelDispOn(0x23);
    opModelDispOn(0x24);
    opModelDispOn(0x25);
    j = 0x37;
    {
    Vec v100, v110, v120, v130;
    do {
        temp_f20_4 = (f32) j * 0.008333334f;
        if (j == 0x64) {
            func_80107C70_opening(0);
            func_80107CD0_opening(0, 0x4D0E);
        }
        HuVecCopyXYZ(&v100, 1519.0f, 0.0f, 2700.0f);
        HuVecCopyXYZ(&v110, 62.5f, 0.0f, 2775.0f);
        HuVecCopyXYZ(&v130, ((v110.x - v100.x) * temp_f20_4) + v100.x, ((v110.y - v100.y) * temp_f20_4) + v100.y, ((v110.z - v100.z) * temp_f20_4) + v100.z);
        opModelPosSet(0, v130.x, v130.y, v130.z);
        opModelPosSet(0x20, v130.x, 0.0f, v130.z);
        HuVecCopyXYZ(&v110, -580.0f, 60.0f, 2580.0f);
        opModelRotSet(0, 0.0f, func_80111164_opening(v130.x, v130.z, v110.x, v110.z), 0.0f);
        HuVecCopyXYZ(&v100, -850.0f, 0.0f, 3920.5f);
        HuVecCopyXYZ(&v110, -300.0f, 0.0f, 2920.5f);
        HuVecCopyXYZ(&v130, ((v110.x - v100.x) * temp_f20_4) + v100.x, ((v110.y - v100.y) * temp_f20_4) + v100.y, ((v110.z - v100.z) * temp_f20_4) + v100.z);
        opModelPosSet(1, v130.x, v130.y, v130.z);
        opModelPosSet(0x21, v130.x, 0.0f, v130.z);
        opModelRotSet(1, 0.0f, func_80111164_opening(v130.x, v130.z, (v110.x - v100.x) + v130.x, (v110.z - v100.z) + v130.z), 0.0f);
        HuVecCopyXYZ(&v100, 1640.0f, 0.0f, 2680.0f);
        HuVecCopyXYZ(&v110, 120.0f, 0.0f, 2505.0f);
        HuVecCopyXYZ(&v130, ((v110.x - v100.x) * temp_f20_4) + v100.x, ((v110.y - v100.y) * temp_f20_4) + v100.y, ((v110.z - v100.z) * temp_f20_4) + v100.z);
        opModelPosSet(2, v130.x, v130.y, v130.z);
        opModelPosSet(0x22, v130.x, 0.0f, v130.z);
        HuVecCopyXYZ(&v110, -580.0f, 60.0f, 2580.0f);
        opModelRotSet(2, 0.0f, func_80111164_opening(v130.x, v130.z, v110.x, v110.z), 0.0f);
        HuVecCopyXYZ(&v100, 1740.0f, 0.0f, 2680.0f);
        HuVecCopyXYZ(&v110, 240.0f, 0.0f, 2680.0f);
        HuVecCopyXYZ(&v130, ((v110.x - v100.x) * temp_f20_4) + v100.x, ((v110.y - v100.y) * temp_f20_4) + v100.y, ((v110.z - v100.z) * temp_f20_4) + v100.z);
        opModelPosSet(3, v130.x, v130.y, v130.z);
        opModelPosSet(0x23, v130.x, 0.0f, v130.z);
        HuVecCopyXYZ(&v110, -580.0f, 60.0f, 2580.0f);
        opModelRotSet(3, 0.0f, func_80111164_opening(v130.x, v130.z, v110.x, v110.z), 0.0f);
        HuVecCopyXYZ(&v100, 960.0f, 0.0f, 3360.0f);
        HuVecCopyXYZ(&v110, -190.0f, 0.0f, 2775.0f);
        HuVecCopyXYZ(&v130, ((v110.x - v100.x) * temp_f20_4) + v100.x, ((v110.y - v100.y) * temp_f20_4) + v100.y, ((v110.z - v100.z) * temp_f20_4) + v100.z);
        opModelPosSet(4, v130.x, v130.y, v130.z);
        opModelPosSet(0x24, v130.x, 0.0f, v130.z);
        HuVecCopyXYZ(&v110, -580.0f, 60.0f, 2580.0f);
        opModelRotSet(4, 0.0f, func_80111164_opening(v130.x, v130.z, v110.x, v110.z), 0.0f);
        HuVecCopyXYZ(&v100, 1160.0f, 0.0f, 3310.0f);
        HuVecCopyXYZ(&v110, -140.0f, 0.0f, 2575.0f);
        HuVecCopyXYZ(&v130, ((v110.x - v100.x) * temp_f20_4) + v100.x, ((v110.y - v100.y) * temp_f20_4) + v100.y, ((v110.z - v100.z) * temp_f20_4) + v100.z);
        opModelPosSet(5, v130.x, v130.y, v130.z);
        opModelPosSet(0x25, v130.x, v130.y, v130.z);
        HuVecCopyXYZ(&v110, -580.0f, 60.0f, 2580.0f);
        opModelRotSet(5, 0.0f, func_80111164_opening(v130.x, v130.z, v110.x, v110.z), 0.0f);
        HuPrcVSleep();
        j++;
    } while (j < 0x79);
    opMotionSpeedSet(0, 1.0f);
    opMotionSpeedSet(1, 1.0f);
    opMotionSpeedSet(2, 1.0f);
    opMotionSpeedSet(3, 1.0f);
    opMotionSpeedSet(4, 1.0f);
    opMotionSpeedSet(5, 1.0f);
    opMotionShiftSet(0, 0x28, 4, 4, 2);
    opMotionShiftSet(2, 0x40, 4, 4, 2);
    opMotionShiftSet(3, 0x48, 4, 4, 2);
    opMotionShiftSet(4, 0x50, 4, 4, 2);
    opMotionShiftSet(5, 0x58, 4, 4, 2);
    HuVecCopyXYZ(&v100, -850.0f, 0.0f, 3920.5f);
    HuVecCopyXYZ(&v110, -300.0f, 0.0f, 2920.5f);
    opModelPosGet(1, &v130.x, &v130.y, &v130.z);
    HuVecCopyXYZ(&v110, (v110.x - v100.x) + v130.x, 0.0f, (v110.z - v100.z) + v130.z);
    opModelPosGet(1, &v100.x, &v100.y, &v100.z);
    opModelPosGet(0xB, &v120.x, &v120.y, &v120.z);
    opMotionShiftSet(1, 0x3D, 4, 4, 2);
    var_s0_7 = 0;
    do {
        temp_f20 = (f32) var_s0_7 * 0.125f;
        opModelRotSet(1, 0.0f, func_8011124C_opening(v110.x - v100.x, v110.z - v100.z, v120.x - v100.x, v120.z - v100.z, temp_f20), 0.0f);
        var_s0_7 += 1;
        HuPrcVSleep();
    } while (var_s0_7 < 9);
    opMotionShiftSet(1, 0x3A, 4, 4, 2);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D0F);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D0E);
        opSleep(0x5A);
    }
    func_80107CA0_opening(0);
    HuPrcSleep(0x14);
    opMotionShiftSet(0, 0x33, 4, 4, 2);
    opMotionShiftSet(2, 0x46, 4, 4, 2);
    opMotionShiftSet(3, 0x4D, 4, 4, 2);
    opMotionShiftSet(4, 0x55, 4, 4, 2);
    opMotionShiftSet(5, 0x5E, 4, 4, 2);
    j = 0;
    do {
        temp_f20_5 = (f32) j * 0.0625f;
        opModelPosGet(4, &v110.x, &v110.y, &v110.z);
        opModelPosGet(0, &v100.x, &v100.y, &v100.z);
        opModelRotGet(0, &v130.x, &v130.y, &v130.z);
        opModelRotSet(0, 0.0f, func_80111490_opening(v130.y, v110.x - v100.x, v110.z - v100.z, temp_f20_5), 0.0f);
        opModelPosGet(3, &v110.x, &v110.y, &v110.z);
        opModelPosGet(2, &v100.x, &v100.y, &v100.z);
        opModelRotGet(2, &v130.x, &v130.y, &v130.z);
        opModelRotSet(2, 0.0f, func_80111490_opening(v130.y, v110.x - v100.x, v110.z - v100.z, temp_f20_5), 0.0f);
        opModelPosGet(2, &v110.x, &v110.y, &v110.z);
        opModelPosGet(3, &v100.x, &v100.y, &v100.z);
        opModelRotGet(3, &v130.x, &v130.y, &v130.z);
        opModelRotSet(3, 0.0f, func_80111490_opening(v130.y, v110.x - v100.x, v110.z - v100.z, temp_f20_5), 0.0f);
        opModelPosGet(0, &v110.x, &v110.y, &v110.z);
        opModelPosGet(4, &v100.x, &v100.y, &v100.z);
        opModelRotGet(4, &v130.x, &v130.y, &v130.z);
        opModelRotSet(4, 0.0f, func_80111490_opening(v130.y, v110.x - v100.x, v110.z - v100.z, temp_f20_5), 0.0f);
        HuVecCopyXYZ(&v110, -60.0f, 0.0f, 2775.0f);
        opModelPosGet(5, &v100.x, &v100.y, &v100.z);
        opModelRotGet(5, &v130.x, &v130.y, &v130.z);
        opModelRotSet(5, 0.0f, func_80111490_opening(v130.y, v110.x - v100.x, v110.z - v100.z, temp_f20_5), 0.0f);
        HuPrcVSleep();
        j++;
    } while (j < 0x11);
    }
    opMotionShiftSet(0, 0x28, 4, 4, 2);
    opMotionShiftSet(2, 0x40, 4, 4, 2);
    opMotionShiftSet(3, 0x48, 4, 4, 2);
    opMotionShiftSet(4, 0x50, 4, 4, 2);
    opMotionShiftSet(5, 0x58, 4, 4, 2);
    HuPrcSleep(4);
    opMotionShiftSet(0, 0x2D, 8, 8, 2);
    HuPrcSleep(4);
    opMotionShiftSet(1, 0x3A, 8, 8, 2);
    HuPrcSleep(4);
    opMotionShiftSet(2, 0x42, 8, 8, 2);
    HuPrcSleep(4);
    opMotionShiftSet(3, 0x4A, 8, 8, 2);
    HuPrcSleep(4);
    opMotionShiftSet(4, 0x52, 8, 8, 2);
    HuPrcSleep(4);
    opMotionShiftSet(5, 0x5A, 8, 8, 2);
    HuPrcSleep(0x14);
    func_80107CA0_opening(0);
    HuPrcSleep(0x1E);
    func_80107C70_opening(0);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D11);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D10);
        opSleep(0x64);
    }
    HuPrcSleep(0xA);
    opDemoObjKill(0xB);
    opDemoObjKill(0xC);
    opModelKill(0xA);
    opModelKill(0x1B);
    opModelKill(6);
    opModelKill(7);
    opModelKill(8);
    opModelKill(0x2A);
    opModelKill(0x2B);
    opModelKill(0x2C);
    opModelKill(0x32);
    opModelKill(0x34);
    HuPrcSleep(3);
    func_80107CA0_opening(0);
    MBBackKill();
    MBBackLoad(0x21);
    func_800E92D4_shared_board();
    Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
    func_80110FB0_opening(&D_80114B88_opening[0], &D_80114B88_opening[1]);
    opModelCreate(0xC, 0xA0089, 0x6A9);
    opModelPosSet(0xC, 4340.0f, 4720.0f, 5925.0f);
    opModelScaleSet(0xC, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0xC, 2);
    opModelCreate(0xD, 0xF0001, 0x6A9);
    opModelPosSet(0xD, 4340.0f, 4720.0f, 5925.0f);
    opModelScaleSet(0xD, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0xD, 2);
    opModelCreate(0xE, 0xF0000, 0x6A9);
    opModelPosSet(0xE, 4340.0f, 4720.0f, 5925.0f);
    opModelScaleSet(0xE, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0xE, 1);
    temp_s1_2 = opModelIdGet(0xD);
    temp_v0_9 = opModelIdGet(0xE);
    func_8001C258_main(temp_v0_9, 0x4000, 0x4000);
    func_8001EF6C_main(temp_v0_9, temp_s1_2, "hook");
    var_s0_8 = 1;
    if (flag != 0) {
        HuAudFXPlay(0x23A);
        var_s0_8 = 1;
    }
    {
    Vec v140, v150, v160;
    do {
        temp_f20_6 = sindf((f32) var_s0_8 * 0.008333334f * 90.0f);
        if (var_s0_8 == 0x21) {
            func_80107C70_opening(0);
            func_80107CD0_opening(0, 0x4D12);
        }
        HuVecCopyXYZ(&v140, 4340.0f, 4420.0f, 5925.0f);
        HuVecCopyXYZ(&v150, D_80114B88_opening[0].x - 10.0f, D_80114B88_opening[0].y + 40.0f, D_80114B88_opening[0].z - 20.0f);
        v150.y += (temp_f20_6 - 0.5f) * 1600.0f * (temp_f20_6 - 0.5f);
        var_s0_8 += 1;
        func_80111164_opening(D_80114B88_opening[0].x, D_80114B88_opening[0].z, D_80114B88_opening[1].x, D_80114B88_opening[1].z);
        HuVecCopyXYZ(&v160, ((v150.x - v140.x) * temp_f20_6) + v140.x, ((v150.y - v140.y) * temp_f20_6) + v140.y, ((v150.z - v140.z) * temp_f20_6) + v140.z);
        temp_f0_4 = func_80111164_opening(D_80114B88_opening[0].x, D_80114B88_opening[0].z, v150.x, v150.z);
        opModelRotSet(0xC, 0.0f, temp_f0_4, 0.0f);
        opModelRotSet(0xD, 0.0f, temp_f0_4, 0.0f);
        opModelPosSet(0xC, v160.x, v160.y, v160.z);
        opModelPosSet(0xD, v160.x, v160.y, v160.z);
        HuPrcVSleep();
    } while (var_s0_8 < 0x74);
    }
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D13);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D12);
        opSleep(0x28);
    }
    func_80107CA0_opening(0);
    opModelDispOff(0xC);
    opModelDispOff(0xD);
    opModelDispOff(0xE);
    MBBackKill();
    MBBackLoad(0x20);
    func_800E92D4_shared_board();
    Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
    func_80110FB0_opening(&D_80114B70_opening[0], &D_80114B70_opening[1]);
    opModelCreate(6, 0xF0006, 0x6A9);
    {
    Vec v170;
    opModelPosGet(0xE, &v170.x, &v170.y, &v170.z);
    opModelPosSet(6, v170.x, v170.y, v170.z);
    opModelScaleSet(6, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(6, 1);
    opMotionTimeSet(6, 0);
    opModelDispOn(6);
    opModelCreate(0x2B, 0xF0006, 0x6A9);
    opModelPosGet(0xE, &v170.x, &v170.y, &v170.z);
    opModelPosSet(6, v170.x, 150.0f, v170.z);
    opModelScaleSet(0x2B, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0x2B, 1);
    opMotionTimeSet(0x2B, 0);
    opModelDispOff(0x2B);
    opModelCreate(0xF, 0xA0075, 0x6A9);
    opModelPosGet(0xE, &v170.x, &v170.y, &v170.z);
    opModelPosSet(0xF, v170.x, v170.y, v170.z);
    opModelScaleSet(0xF, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0xF, 1);
    opModelDispOff(0xF);
    opMotionCreate(0x68, 0xA0076, 0);
    opMotionCreate(0x69, 0xA0077, 0);
    opMotionCreate(0x6A, 0xA0078, 0);
    opMotionSet(0xF, 0x69, 1);
    opMotionTimeSet(0xF, 0);
    opModelPosGet(4, &v170.x, &v170.y, &v170.z);
    temp_f4_2 = v170.x - 50.0f;
    v170.x = temp_f4_2;
    temp_f2_2 = v170.z + 25.0f;
    v170.z = temp_f2_2;
    opModelPosSet(4, temp_f4_2, v170.y, temp_f2_2);
    opModelPosSet(0x24, v170.x, v170.y, v170.z);
    }
    opModelDispOn(0xC);
    opModelDispOn(0xD);
    opModelDispOn(0xE);
    opMotionTimeSet(0xD, 0);
    opMotionSet(0, 0x33, 2);
    opMotionSet(2, 0x46, 2);
    opMotionSet(3, 0x4D, 2);
    opMotionSet(4, 0x55, 2);
    opMotionSet(5, 0x5E, 2);
    {
    Vec v180, v190, v1A0, v1B0;
    v1A0.x = v1A0.y = v1A0.z = 0.0f;
    opDemoShadowCreate(0x1D, 0.0f, 0.0f, 0.0f);
    opDemoShadowCreate(0x1E, v1A0.x, v1A0.y, v1A0.z);
    opModelDispOff(0x1E);
    HuVecCopyXYZ(&v180, 800.0f, 400.0f, 2320.0f);
    HuVecCopyXYZ(&v190, -880.0f, 400.0f, 3231.5f);
    var_s0_9 = 0;
    temp_f0_5 = func_80111164_opening(v180.x, v180.z, v190.x, v190.z);
    s1D0 = temp_f0_5;
    opModelRotSet(0xC, 0.0f, temp_f0_5, 0.0f);
    opModelRotSet(0xD, 0.0f, s1D0, 0.0f);
    do {
        temp_f22 = (f32) var_s0_9 * 0.004166667f;
        HuVecCopyXYZ(&v180, 800.0f, 400.0f, 2320.0f);
        HuVecCopyXYZ(&v190, -880.0f, 400.0f, 3231.5f);
        HuVecCopyXYZ(&v1A0, ((v190.x - v180.x) * temp_f22) + v180.x, ((v190.y - v180.y) * temp_f22) + v180.y, ((v190.z - v180.z) * temp_f22) + v180.z);
        opModelPosSet(0xC, v1A0.x, v1A0.y, v1A0.z);
        opModelPosSet(0xD, v1A0.x, v1A0.y, v1A0.z);
        opModelPosSet(0x1D, v1A0.x, 0.0f, v1A0.z);
        opModelScaleSet(0x1D, 0.5f, 0.5f, 0.5f);
        opModelPosSet(0x1E, v1A0.x, 0.0f, v1A0.z);
        opModelScaleSet(0x1E, 0.5f, 0.5f, 0.5f);
        opModelPosGet(0, &v180.x, &v180.y, &v180.z);
        opModelRotGet(0, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        opModelRotSet(0, 0.0f, s1D0, 0.0f);
        opModelPosGet(2, &v180.x, &v180.y, &v180.z);
        opModelRotGet(2, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_8 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_8;
        opModelRotSet(2, 0.0f, temp_f0_8, 0.0f);
        opModelPosGet(3, &v180.x, &v180.y, &v180.z);
        opModelRotGet(3, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_10 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_10;
        opModelRotSet(3, 0.0f, temp_f0_10, 0.0f);
        opModelPosGet(4, &v180.x, &v180.y, &v180.z);
        opModelRotGet(4, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_12 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_12;
        opModelRotSet(4, 0.0f, temp_f0_12, 0.0f);
        opModelPosGet(5, &v180.x, &v180.y, &v180.z);
        opModelRotGet(5, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_14 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_14;
        opModelRotSet(5, 0.0f, temp_f0_14, 0.0f);
        HuPrcVSleep();
        if (var_s0_9 == 0x2C) {
            opMotionShiftSet(0, 0x35, 8, 0x10, 2);
            opMotionShiftSet(2, 0x47, 8, 0x10, 2);
            opMotionShiftSet(3, 0x4F, 8, 0x10, 2);
            opMotionShiftSet(4, 0x57, 8, 0x10, 2);
            opMotionShiftSet(5, 0x60, 8, 0x10, 2);
        }
        var_s0_9 += 2;
    } while (var_s0_9 < 0x68);
    func_8001C258_main(opModelIdGet(0xE), 0x4000, 0);
    opModelRotGet(0xD, &v1B0.x, &v1B0.y, &v1B0.z);
    opModelRotSet(0xE, v1B0.x, v1B0.y, v1B0.z);
    temp_f22_2 = v1B0.y;
    opModelPosGet(0xD, &v1B0.x, &v1B0.y, &v1B0.z);
    v1B0.x = (f32) ((f64) v1B0.x + ((f64) sindf(temp_f22_2) * 142.0));
    v1B0.y += -108.0f;
    temp_f2_3 = (f32) ((f64) v1B0.z + ((f64) cosdf(temp_f22_2) * 142.0));
    v1B0.z = temp_f2_3;
    opModelPosSet(0xE, v1B0.x, v1B0.y, temp_f2_3);
    opModelDispOff(0xD);
    opMotionShiftSet(0, 0x33, 8, 8, 2);
    opMotionShiftSet(2, 0x46, 8, 8, 2);
    opMotionShiftSet(3, 0x4D, 8, 8, 2);
    opMotionShiftSet(4, 0x55, 8, 8, 2);
    opMotionShiftSet(5, 0x5E, 8, 8, 2);
    opMotionSpeedSet(0, 0.3f);
    opMotionSpeedSet(2, 0.3f);
    opMotionSpeedSet(3, 0.3f);
    opMotionSpeedSet(4, 0.3f);
    opMotionSpeedSet(5, 0.3f);
    opModelDispOn(0x1E);
    opModelRotGet(0xE, &s1C4, &s1C8, &s1CC);
    var_s0_10 = 0x68;
    var_s1 = 0;
    do {
        if (var_s1 == 0x14) {
            func_80106DD0_opening(0xE, 1);
            if (flag != 0) {
                HuAudFXPlay(0x23B);
            }
        }
        var_f0_2 = (f32) var_s1 * 0.05f;
        var_f0_2 = (var_f0_2 > 1.0f) ? 1.0f : var_f0_2;
        HuVecCopyXYZ(&v1A0, v1B0.x, (var_f0_2 * var_f0_2 * (97.5f - v1B0.y)) + v1B0.y, v1B0.z);
        opModelPosSet(0xE, v1A0.x, v1A0.y, v1A0.z);
        temp_f0_15 = func_80111490_opening(s1C8, -(D_80114B70_opening[0].x - v1A0.x), -(D_80114B70_opening[0].z - v1A0.z), var_f0_2);
        s1C8 = temp_f0_15;
        opModelRotSet(0xE, 0.0f, temp_f0_15, 0.0f);
        opModelPosSet(0x1E, v1A0.x, 0.0f, v1A0.z);
        temp_f0_16 = (var_f0_2 * 0.5f) + 0.5f;
        opModelScaleSet(0x1E, temp_f0_16, temp_f0_16, temp_f0_16);
        temp_f22_4 = (f32) var_s0_10 * 0.004166667f;
        temp_f20_7 = (f32) (var_s0_10 - 0x68) * 0.007352941f;
        HuVecCopyXYZ(&v180, 800.0f, 400.0f, 2320.0f);
        HuVecCopyXYZ(&v190, -880.0f, 400.0f, 3231.5f);
        temp_f2_4 = (temp_f20_7 * 800.0f * temp_f20_7) + v190.y;
        v190.y = temp_f2_4;
        HuVecCopyXYZ(&v1A0, ((v190.x - v180.x) * temp_f22_4) + v180.x, ((temp_f2_4 - v180.y) * temp_f22_4) + v180.y, ((v190.z - v180.z) * temp_f22_4) + v180.z);
        opModelPosSet(0xC, v1A0.x, v1A0.y, v1A0.z);
        opModelPosSet(0xD, v1A0.x, v1A0.y, v1A0.z);
        opModelPosSet(0x1D, v1A0.x, 0.0f, v1A0.z);
        opModelScaleSet(0x1D, 0.5f, 0.5f, 0.5f);
        HuVecCopyXYZ(&v1A0, ((v190.x - v180.x) * 0.5f) + v180.x, ((v190.y - v180.y) * 0.5f) + v180.y, ((v190.z - v180.z) * 0.5f) + v180.z);
        opModelPosGet(0, &v180.x, &v180.y, &v180.z);
        opModelRotGet(0, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_18 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_18;
        opModelRotSet(0, 0.0f, temp_f0_18, 0.0f);
        opModelPosGet(2, &v180.x, &v180.y, &v180.z);
        opModelRotGet(2, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_20 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_20;
        opModelRotSet(2, 0.0f, temp_f0_20, 0.0f);
        opModelPosGet(3, &v180.x, &v180.y, &v180.z);
        opModelRotGet(3, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_22 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_22;
        opModelRotSet(3, 0.0f, temp_f0_22, 0.0f);
        opModelPosGet(4, &v180.x, &v180.y, &v180.z);
        opModelRotGet(4, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_24 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_24;
        opModelRotSet(4, 0.0f, temp_f0_24, 0.0f);
        opModelPosGet(5, &v180.x, &v180.y, &v180.z);
        opModelRotGet(5, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        var_s0_10 += 2;
        temp_f0_26 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_26;
        opModelRotSet(5, 0.0f, temp_f0_26, 0.0f);
        var_s1 += 1;
        HuPrcVSleep();
    } while (var_s0_10 < 0xA0);
    var_s0_11 = 0xA0;
    do {
        var_f22 = (f32) var_s1 * 0.05f;
        if (var_s1 == 0x14) {
            func_80106DD0_opening(0xE, 1);
            if (flag != 0) {
                HuAudFXPlay(0x23B);
            }
        }
        if (var_f22 > 1.0f) {
            var_f22 = 1.0f;
        }
        HuVecCopyXYZ(&v1A0, v1B0.x, (var_f22 * var_f22 * (97.5f - v1B0.y)) + v1B0.y, v1B0.z);
        opModelPosSet(0xE, v1A0.x, v1A0.y, v1A0.z);
        temp_f0_27 = func_80111490_opening(s1C8, -(D_80114B70_opening[0].x - v1A0.x), -(D_80114B70_opening[0].z - v1A0.z), var_f22);
        s1C8 = temp_f0_27;
        opModelRotSet(0xE, 0.0f, temp_f0_27, 0.0f);
        opModelPosSet(0x1E, v1A0.x, 0.0f, v1A0.z);
        temp_f0_28 = (var_f22 * 0.5f) + 0.5f;
        opModelScaleSet(0x1E, temp_f0_28, temp_f0_28, temp_f0_28);
        temp_f22_5 = (f32) var_s0_11 * 0.004166667f;
        temp_f20_8 = (f32) (var_s0_11 - 0x68) * 0.007352941f;
        HuVecCopyXYZ(&v180, 800.0f, 400.0f, 2320.0f);
        HuVecCopyXYZ(&v190, -880.0f, 400.0f, 3231.5f);
        temp_f2_5 = (temp_f20_8 * 800.0f * temp_f20_8) + v190.y;
        v190.y = temp_f2_5;
        HuVecCopyXYZ(&v1A0, ((v190.x - v180.x) * temp_f22_5) + v180.x, ((temp_f2_5 - v180.y) * temp_f22_5) + v180.y, ((v190.z - v180.z) * temp_f22_5) + v180.z);
        opModelPosSet(0xC, v1A0.x, v1A0.y, v1A0.z);
        opModelPosSet(0xD, v1A0.x, v1A0.y, v1A0.z);
        opModelPosGet(0, &v180.x, &v180.y, &v180.z);
        opModelRotGet(0, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_30 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_30;
        opModelRotSet(0, 0.0f, temp_f0_30, 0.0f);
        opModelPosGet(2, &v180.x, &v180.y, &v180.z);
        opModelRotGet(2, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_32 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_32;
        opModelRotSet(2, 0.0f, temp_f0_32, 0.0f);
        opModelPosGet(3, &v180.x, &v180.y, &v180.z);
        opModelRotGet(3, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_34 = func_801111AC_opening(s1C0, s1D0, 5.0f);
        s1D0 = temp_f0_34;
        opModelRotSet(3, 0.0f, temp_f0_34, 0.0f);
        opModelPosGet(4, &v180.x, &v180.y, &v180.z);
        opModelRotGet(4, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        temp_f0_36 = func_801111AC_opening(s1C0, s1D0, 9.0f);
        s1D0 = temp_f0_36;
        opModelRotSet(4, 0.0f, temp_f0_36, 0.0f);
        opModelPosGet(5, &v180.x, &v180.y, &v180.z);
        opModelRotGet(5, &v190.x, &s1C0, &v190.z);
        ang = func_80111164_opening(v180.x, v180.z, v1A0.x, v1A0.z);
        s1D0 = ang;
        if (ang < 0.0f) {
            s1D0 = ang + 360.0f;
        }
        var_s0_11 += 2;
        temp_f0_38 = func_801111AC_opening(s1C0, s1D0, 9.0f);
        s1D0 = temp_f0_38;
        opModelRotSet(5, 0.0f, temp_f0_38, 0.0f);
        var_s1 += 1;
        HuPrcVSleep();
    } while (var_s0_11 < 0xF1);
    opMotionShiftSet(0, 0x33, 4, 4, 2);
    opMotionSpeedSet(0, 1.0f);
    opMotionShiftSet(2, 0x46, 4, 4, 2);
    opMotionSpeedSet(2, 1.0f);
    opMotionShiftSet(3, 0x4D, 4, 4, 2);
    opMotionSpeedSet(3, 1.0f);
    opMotionShiftSet(4, 0x55, 4, 4, 2);
    opMotionSpeedSet(4, 1.0f);
    opMotionShiftSet(5, 0x5E, 4, 4, 2);
    opMotionSpeedSet(5, 1.0f);
    var_s0_12 = 0;
    do {
        temp_f22_6 = (f32) var_s0_12 * 0.0625f;
        HuVecCopyXYZ(&v180, 800.0f, 400.0f, 2320.0f);
        HuVecCopyXYZ(&v190, -880.0f, 400.0f, 3231.5f);
        HuVecCopyXYZ(&v1A0, ((v190.x - v180.x) * 0.5f) + v180.x, ((v190.y - v180.y) * 0.5f) + v180.y, ((v190.z - v180.z) * 0.5f) + v180.z);
        opModelPosSet(0x1E, v1A0.x, 0.0f, v1A0.z);
        opModelScaleSet(0x1E, 1.0f, 1.0f, 1.0f);
        opModelPosGet(0, &v180.x, &v180.y, &v180.z);
        opModelRotGet(0, &v190.x, &s1D0, &v190.z);
        temp_f0_39 = func_80111490_opening(s1D0, v1A0.x - v180.x, v1A0.z - v180.z, temp_f22_6);
        s1D0 = temp_f0_39;
        opModelRotSet(0, 0.0f, temp_f0_39, 0.0f);
        opModelPosGet(2, &v180.x, &v180.y, &v180.z);
        opModelRotGet(2, &v190.x, &s1D0, &v190.z);
        temp_f0_40 = func_80111490_opening(s1D0, v1A0.x - v180.x, v1A0.z - v180.z, temp_f22_6);
        s1D0 = temp_f0_40;
        opModelRotSet(2, 0.0f, temp_f0_40, 0.0f);
        opModelPosGet(3, &v180.x, &v180.y, &v180.z);
        opModelRotGet(3, &v190.x, &s1D0, &v190.z);
        temp_f0_41 = func_80111490_opening(s1D0, v1A0.x - v180.x, v1A0.z - v180.z, temp_f22_6);
        s1D0 = temp_f0_41;
        opModelRotSet(3, 0.0f, temp_f0_41, 0.0f);
        var_f0_3 = 1.0f;
        if (!((2.0f * temp_f22_6) > 1.0f)) {
            var_f0_3 = 2.0f * temp_f22_6;
        }
        opModelPosGet(4, &v180.x, &v180.y, &v180.z);
        opModelRotGet(4, &v190.x, &s1D0, &v190.z);
        temp_f0_42 = func_80111490_opening(s1D0, v1A0.x - v180.x, v1A0.z - v180.z, var_f0_3);
        s1D0 = temp_f0_42;
        opModelRotSet(4, 0.0f, temp_f0_42, 0.0f);
        opModelPosGet(5, &v180.x, &v180.y, &v180.z);
        opModelRotGet(5, &v190.x, &s1D0, &v190.z);
        temp_f0_43 = func_80111490_opening(s1D0, v1A0.x - v180.x, v1A0.z - v180.z, var_f0_3);
        s1D0 = temp_f0_43;
        opModelRotSet(5, 0.0f, temp_f0_43, 0.0f);
        var_s0_12 += 1;
        HuPrcVSleep();
    } while (var_s0_12 < 0x11);
    }
    opMotionShiftSet(2, 0x40, 4, 4, 2);
    opMotionShiftSet(3, 0x48, 4, 4, 2);
    opMotionShiftSet(4, 0x50, 4, 4, 2);
    opMotionShiftSet(5, 0x58, 4, 4, 2);
    opMotionShiftSet(0, 0x2E, 4, 4, 0);
    HuPrcSleep(0x10);
    opModelDispOn(6);
    temp_s1_3 = opModelIdGet(0);
    temp_v0_10 = opModelIdGet(6);
    func_8001C258_main(temp_v0_10, 0x4000, 0x4000);
    func_8001EF6C_main(temp_v0_10, temp_s1_3, "item_hook");
    {
    Vec v1D8, v1E8, v1F8, v208;
    opModelRotGet(0, &v208.x, &v208.y, &v208.z);
    opModelPosGet(0, &v1F8.x, &v1F8.y, &v1F8.z);
    var_s0_13 = 1;
    do {
        v208.y = func_80111490_opening(v208.y, D_80114B70_opening[0].x - v1F8.x, D_80114B70_opening[0].z - v1F8.z, (f32) var_s0_13 * 0.125f);
        HuPrcVSleep();
        var_s0_13 += 1;
    } while (var_s0_13 < 9);
    if (flag != 0) {
        HuAudFXPlay(0x275);
    }
    opMotionShiftSet(2, 0x43, 8, 8, 2);
    opMotionShiftSet(3, 0x4E, 8, 8, 2);
    opMotionShiftSet(4, 0x56, 8, 8, 0);
    opMotionEndWait(4);
    opMotionShiftSet(4, 0x50, 8, 8, 2);
    func_80107C70_opening(0);
    func_80107CD0_opening(0, 0x4D14);
    opMotionEndWait(0);
    opMotionShiftSet(0, 0x2F, 4, 4, 2);
    opMotionShiftSet(5, 0x59, 8, 8, 2);
    opModelPosGet(5, &v1D8.x, &v1D8.y, &v1D8.z);
    opModelPosGet(0xE, &v1E8.x, &v1E8.y, &v1E8.z);
    var_s0_14 = 0;
    temp_f0_44 = func_80111164_opening(D_80114B70_opening[0].x, D_80114B70_opening[0].z, v1E8.x, v1E8.z);
    temp_f20_9 = cosdf(temp_f0_44);
    v1E8.x = ((temp_f20_9 * 60.0f) + v1E8.x + (sindf(temp_f0_44) * 60.0f)) - 30.0f;
    temp_f20_10 = sindf(temp_f0_44);
    v1E8.z = (v1E8.z - (temp_f20_10 * 60.0f)) + (cosdf(temp_f0_44) * 60.0f);
    v1E8.y = v1D8.y;
    opModelRotGet(5, &v208.x, &v208.y, &v208.z);
    do {
        temp_f20_11 = (f32) var_s0_14;
        temp_f12 = temp_f20_11 * 0.125f;
        HuVecCopyXYZ(&v1F8, ((v1E8.x - v1D8.x) * temp_f12) + v1D8.x, ((v1E8.y - v1D8.y) * temp_f12) + v1D8.y, ((v1E8.z - v1D8.z) * temp_f12) + v1D8.z);
        opModelPosSet(5, v1F8.x, v1F8.y, v1F8.z);
        opModelPosSet(0x25, v1F8.x, v1F8.y, v1F8.z);
        if (var_s0_14 < 5) {
            opModelRotSet(5, 0.0f, func_80111490_opening(v208.y, v1E8.x - v1F8.x, (v1E8.z + 10.0f) - v1F8.z, temp_f20_11 * 0.25f), 0.0f);
        }
        var_s0_14 += 1;
        HuPrcVSleep();
    } while (var_s0_14 < 9);
    opModelPosGet(5, &v1D8.x, &v1D8.y, &v1D8.z);
    opModelPosGet(0xE, &v1E8.x, &v1E8.y, &v1E8.z);
    opModelRotGet(5, &v208.x, &v208.y, &v208.z);
    var_s0_15 = 0;
    do {
        opModelRotSet(5, 0.0f, func_80111490_opening(v208.y, v1E8.x - v1F8.x, (v1E8.z + 10.0f) - v1F8.z, (f32) var_s0_15 * 0.125f), 0.0f);
        var_s0_15 += 1;
        HuPrcVSleep();
    } while (var_s0_15 < 8);
    }
    opMotionShiftSet(5, 0x58, 4, 4, 2);
    HuPrcSleep(8);
    opMotionShiftSet(5, 0x5B, 4, 4, 0);
    HuPrcSleep(8);
    opModelDispOn(0xF);
    temp_s1_4 = opModelIdGet(5);
    temp_v0_11 = opModelIdGet(0xF);
    func_8001C258_main(temp_v0_11, 0x4000, 0x4000);
    func_8001EF6C_main(temp_v0_11, temp_s1_4, "item_hook");
    var_s0_16 = 1;
    do {
        var_s0_16 += 1;
        HuPrcVSleep();
    } while (var_s0_16 < 9);
    opMotionEndWait(5);
    if (flag != 0) {
        HuAudFXPlay(0x27A);
    }
    opMotionShiftSet(5, 0x5F, 4, 4, 2);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D15);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D14);
        opSleep(0x50);
    }
    func_80107CA0_opening(0);
    HuPrcSleep(0x32);
    func_80107C70_opening(0);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D17);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D16);
        opSleep(0x3C);
    }
    func_800E9344_shared_board(10.0f, 10000.0f);
    opModelCreate(0x1C, 0xF0007, 0x2A9);
    opModelPosSet(0x1C, -580.0f, 60.0f, 2580.0f);
    {
    Vec v218, v228, v238;
    opModelPosGet(0, &v238.x, &v238.y, &v238.z);
    opModelRotSet(0x1C, 0.0f, func_80111164_opening(v238.x, v238.z, D_80114B70_opening[0].x, D_80114B70_opening[0].z), 0.0f);
    opModelScaleSet(0x1C, 1.0f, 1.0f, 1.0f);
    opModelDispOff(0x1C);
    opMotionShiftSet(1, 0x3C, 4, 4, 0);
    HuPrcSleep(4);
    opModelDispOn(0x1C);
    func_80106DD0_opening(0x1C, 1);
    opMotionTimeSet(0x1C, 0);
    if (flag != 0) {
        HuAudFXPlay(0x236);
    }
    opMotionEndWait(1);
    opMotionShiftSet(1, 0x38, 4, 4, 2);
    opModelRotGet(0, &v228.x, &s248, &v228.z);
    opModelRotGet(1, &v228.x, &s24C, &v228.z);
    opModelRotGet(2, &v228.x, &s250, &v228.z);
    opModelRotGet(3, &v228.x, &s254, &v228.z);
    opModelRotGet(4, &v228.x, &s258, &v228.z);
    opModelRotGet(5, &v228.x, &s25C, &v228.z);
    opModelPosGet(0xB, &v228.x, &v228.y, &v228.z);
    opMotionShiftSet(2, 0x46, 4, 4, 2);
    opMotionShiftSet(3, 0x4D, 4, 4, 2);
    opMotionShiftSet(4, 0x55, 4, 4, 2);
    var_s3 = 0;
    do {
        temp_f20_12 = (f32) var_s3 * 0.125f;
        opModelPosGet(0, &v218.x, &v218.y, &v218.z);
        opModelRotSet(0, 0.0f, func_80111490_opening(s248, v228.x - v218.x, v228.z - v218.z, temp_f20_12), 0.0f);
        opModelPosGet(2, &v218.x, &v218.y, &v218.z);
        opModelRotSet(2, 0.0f, func_80111490_opening(s250, v228.x - v218.x, v228.z - v218.z, temp_f20_12), 0.0f);
        opModelPosGet(3, &v218.x, &v218.y, &v218.z);
        opModelRotSet(3, 0.0f, func_80111490_opening(s254, v228.x - v218.x, v228.z - v218.z, temp_f20_12), 0.0f);
        opModelPosGet(4, &v218.x, &v218.y, &v218.z);
        opModelRotSet(4, 0.0f, func_80111490_opening(s258, v228.x - v218.x, v228.z - v218.z, temp_f20_12), 0.0f);
        opModelPosGet(5, &v218.x, &v218.y, &v218.z);
        opModelRotSet(5, 0.0f, func_80111490_opening(s25C, v228.x - v218.x, v228.z - v218.z, temp_f20_12), 0.0f);
        opModelPosSet(5, v218.x - (temp_f20_12 * 7.5f), v218.y, v218.z);
        var_s3 += 1;
        HuPrcVSleep();
    } while (var_s3 < 9);
    }
    opMotionShiftSet(2, 0x40, 4, 4, 2);
    opMotionShiftSet(3, 0x48, 4, 4, 2);
    opMotionShiftSet(4, 0x50, 4, 4, 2);
    opMotionEndWait(0x1C);
    opModelKill(0x2D);
    opModelKill(0x39);
    opModelKill(0x41);
    opModelKill(0x42);
    opModelKill(0x43);
    opModelKill(0x49);
    opModelKill(0x4A);
    opModelKill(0x4E);
    opModelKill(0x52);
    opModelKill(0x56);
    opModelKill(0x5A);
    opModelKill(0x35);
    opModelKill(0x3D);
    opModelKill(0x46);
    opModelKill(0x4D);
    opModelKill(0x55);
    opModelKill(0x5E);
    HuPrcSleep(3);
    if (flag != 0) {
        HuAudFXPlay(0x23C);
    }
    opWipeWhiteOutCreate(0xF, 0x14);
    if (flag != 0) {
        HuAudSeqFadeOut(0x2E);
    }
    HuPrcSleep(0x14);
    HuPrcSleep(0x14);
    {
    Vec v268, v278, v288, v298, v2A8, v2B8, v2C8, v2D8, v2E8, v2F8;
    opModelPosGet(5, &v268.x, &v268.y, &v268.z);
    opModelPosSet(5, v268.x + 60.0f, v268.y, v268.z);
    opModelPosSet(0x25, v268.x + 60.0f, v268.y, v268.z);
    opMotionCreate(0x30, 0xF000F, 0);
    opMotionCreate(0x44, 0x70025, 0);
    HuPrcSleep(3);
    opMotionCreate(0x53, 0xF0017, 0);
    opMotionCreate(0x5C, 0xF001A, 0);
    HuPrcSleep(3);
    opModelKill(0x1C);
    opModelKill(0x1D);
    opModelKill(0x1E);
    MBBackKill();
    MBBackLoad(0x22);
    func_800E92D4_shared_board();
    Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
    func_80110FB0_opening(&D_80114B70_opening[0], &D_80114B70_opening[1]);
    opModelKill(0xC);
    opModelKill(0xD);
    opModelKill(0xE);
    opModelKill(9);
    opModelDispOff(0xB);
    HuPrcSleep(3);
    opMotionCreate(0x31, 0x2007A, 0);
    opMotionCreate(0x3B, 0xF0013, 0);
    opMotionCreate(0x45, 0x7007A, 0);
    opMotionCreate(0x4B, 0x40003, 0);
    opMotionCreate(0x4C, 0x4007A, 0);
    opMotionCreate(0x54, 0x5007A, 0);
    opMotionCreate(0x5D, 0x6007A, 0);
    opModelCreate(0x12, 0xF0008, 0x6A9);
    opModelPosSet(0x12, -130.99998f, 0.0f, 3250.0f);
    opModelRotSet(0x12, 0.0f, 25.0f, 0.0f);
    opModelScaleSet(0x12, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0x12, 1);
    temp_v0_12 = func_8001D33C_main(opModelIdGet(0x12), "tree_kage");
    func_80088700_main(temp_v0_12->unk58, 0.0f, 0.0f, 0.0f);
    temp_v0_12->unk1C.x = temp_v0_12->unk1C.y = temp_v0_12->unk1C.z = temp_v0_12->unk40.x = temp_v0_12->unk40.y = temp_v0_12->unk40.z = 0.0f;
    opModelPosGet(3, &v278.x, &v278.y, &v278.z);
    opModelRotGet(3, &v2A8.x, &v2A8.y, &v2A8.z);
    temp_f0_45 = func_80111164_opening(D_80114B70_opening[0].x, D_80114B70_opening[0].z, v278.x, v278.z);
    temp_f20_13 = sindf(temp_f0_45);
    v298.x = (temp_f20_13 * 100.0f) + (cosdf(temp_f0_45) * -160.0f) + v278.x;
    v298.y = 0.0f;
    temp_f20_14 = cosdf(temp_f0_45);
    temp_f20_15 = (temp_f20_14 * -100.0f) + (sindf(temp_f0_45) * -160.0f) + v278.z;
    v298.z = temp_f20_15;
    opModelPosSet(0x12, v298.x, v298.y, temp_f20_15);
    opModelPosGet(3, &v278.x, &v278.y, &v278.z);
    opModelPosGet(0x12, &v288.x, &v288.y, &v288.z);
    opModelRotSet(3, 0.0f, func_80111164_opening(v278.x, v278.z, v288.x, v288.z), 0.0f);
    func_80112BA0_opening(0, 3, 0x4B, 0x48, 0, 0x26);
    func_80112D30_opening(1, 0x12, 8, 0x33);
    opModelCreate(0x13, 0xF0008, 0x6A9);
    opModelPosSet(0x13, 344.0f, 0.0f, 2900.0f);
    opModelRotSet(0x13, 0.0f, 25.0f, 0.0f);
    opModelScaleSet(0x13, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0x13, 1);
    opModelPosGet(1, &v2B8.x, &v2B8.y, &v2B8.z);
    opModelRotGet(1, &v2E8.x, &v2E8.y, &v2E8.z);
    temp_f0_46 = func_80111164_opening(D_80114B70_opening[0].x, D_80114B70_opening[0].z, v2B8.x, v2B8.z);
    temp_f20_16 = sindf(temp_f0_46);
    v2D8.x = (temp_f20_16 * 125.0f) + (cosdf(temp_f0_46) * -100.0f) + v2B8.x;
    v2D8.y = 0.0f;
    temp_f20_17 = cosdf(temp_f0_46);
    temp_f20_18 = (temp_f20_17 * -125.0f) + (sindf(temp_f0_46) * -100.0f) + v2B8.z;
    v2D8.z = temp_f20_18;
    opModelPosSet(0x13, v2D8.x, v2D8.y, temp_f20_18);
    opModelPosGet(1, &v2B8.x, &v2B8.y, &v2B8.z);
    opModelPosGet(0x13, &v2C8.x, &v2C8.y, &v2C8.z);
    opModelRotSet(1, 0.0f, func_80111164_opening(v2B8.x, v2B8.z, v2C8.x, v2C8.z), 0.0f);
    func_80112BA0_opening(2, 1, 0x3B, 0x38, 0x2C, 0x28);
    func_80112D30_opening(3, 0x13, 0, 0x58);
    func_8001C258_main(opModelIdGet(0xF), 0x4000, 0);
    opModelDispOff(0xF);
    func_8001C258_main(opModelIdGet(6), 0x4000, 0);
    opModelKill(6);
    opModelPosGet(0xF, &v2F8.x, &v2F8.y, &v2F8.z);
    opDemoShadowCreate(0x27, v2F8.x, v2F8.y, v2F8.z);
    temp_f2_6 = (1200.0f - v2F8.y) * 0.00083333335f;
    }
    opModelScaleSet(0x27, temp_f2_6, 1.0f, temp_f2_6);
    opModelDispOff(0x27);
    opMotionCreate(0x6B, 0xF001C, 0);
    func_80107CA0_opening(0);
    opMotionSet(0, 0x30, 2);
    opMotionSet(2, 0x44, 2);
    opMotionSet(3, 0x48, 2);
    opMotionSet(4, 0x53, 2);
    opMotionSet(5, 0x5C, 2);
    opWipeWhiteInCreate(0xF, 0x14);
    HuPrcSleep(0x14);
    if (flag != 0) {
        HuAudSeqPlay(0x3B);
    }
    func_80107CD0_opening(0, 0x4D18);
    HuPrcSleep(0x28);
    func_80107C70_opening(0);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D19);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D18);
        opSleep(0x78);
    }
    func_80107CA0_opening(0);
    opModelDispOn(0xF);
    opModelDispOn(0x27);
    opMotionShiftSet(0xF, 0x69, 4, 4, 2);
    {
    Vec v308, v318, v328, v338, v348, v358;
    func_801110AC_opening(&v308.x, &v308.y, &v308.z, &v318.x, &v318.y, &v318.z);
    temp_f26 = func_80111164_opening(v318.x, v318.z, v308.x, v308.z);
    v328.y = 150.0f;
    v328.x = (sindf(temp_f26) * -600.0f) + v308.x;
    v328.z = (cosdf(temp_f26) * -600.0f) + v308.z;
    HuVecCopy3F(&v338, &v328);
    v328.y += 900.0f;
    opModelScaleSet(0xF, 1.0f, 1.0f, 1.0f);
    var_s0_17 = 0;
    if (flag != 0) {
        HuAudFXPlay(0x23D);
        var_s0_17 = 0;
    }
    do {
        temp_f0_47 = sindf((f32) var_s0_17 * 0.05f * 90.0f);
        HuVecCopyXYZ(&v358, (temp_f0_47 * (v338.x - v328.x)) + v328.x, (temp_f0_47 * (v338.y - v328.y)) + v328.y, (temp_f0_47 * (v338.z - v328.z)) + v328.z);
        opModelPosSet(0xF, v358.x, v358.y, v358.z);
        opModelPosSet(0x27, v358.x, 0.0f, v358.z);
        temp_f2_7 = (1200.0f - v358.y) * 0.00083333335f;
        opModelScaleSet(0x27, temp_f2_7, 1.0f, temp_f2_7);
        var_s0_17 += 1;
        opModelRotSet(0xF, 0.0f, func_80111164_opening(v358.x, v358.z, D_80114B70_opening[0].x, D_80114B70_opening[0].z), 0.0f);
        HuPrcVSleep();
    } while (var_s0_17 < 0x15);
    HuPrcSleep(8);
    opDemoGuideInEffCreate(4, 0xF);
    opDemoObjKill(0);
    opDemoObjKill(1);
    opDemoObjKill(2);
    opDemoObjKill(3);
    opModelPosGet(0xF, &v358.x, &v358.y, &v358.z);
    opModelRotGet(0, &v338.x, &s368, &v338.z);
    opModelRotGet(1, &v338.x, &s36C, &v338.z);
    opModelRotGet(2, &v338.x, &s370, &v338.z);
    opModelRotGet(3, &v338.x, &s374, &v338.z);
    opModelRotGet(4, &v338.x, &s378, &v338.z);
    opModelRotGet(5, &v338.x, &s37C, &v338.z);
    opMotionShiftSet(0, 0x33, 4, 4, 2);
    opMotionShiftSet(1, 0x3D, 4, 4, 2);
    opMotionShiftSet(2, 0x46, 4, 4, 2);
    opMotionShiftSet(3, 0x4D, 4, 4, 2);
    opMotionShiftSet(4, 0x55, 4, 4, 2);
    opMotionShiftSet(5, 0x5E, 4, 4, 2);
    var_s0_18 = 0;
    do {
        temp_f20_19 = (f32) var_s0_18 * 0.125f;
        opModelPosGet(0, &v328.x, &v328.y, &v328.z);
        opModelRotSet(0, 0.0f, func_80111490_opening(s368, v358.x - v328.x, v358.z - v328.z, temp_f20_19), 0.0f);
        opModelPosGet(1, &v328.x, &v328.y, &v328.z);
        opModelRotSet(1, 0.0f, func_80111490_opening(s36C, v358.x - v328.x, v358.z - v328.z, temp_f20_19), 0.0f);
        opModelPosGet(2, &v328.x, &v328.y, &v328.z);
        opModelRotSet(2, 0.0f, func_80111490_opening(s370, v358.x - v328.x, v358.z - v328.z, temp_f20_19), 0.0f);
        opModelPosGet(3, &v328.x, &v328.y, &v328.z);
        opModelRotSet(3, 0.0f, func_80111490_opening(s374, v358.x - v328.x, v358.z - v328.z, temp_f20_19), 0.0f);
        opModelPosGet(4, &v328.x, &v328.y, &v328.z);
        opModelRotSet(4, 0.0f, func_80111490_opening(s378, v358.x - v328.x, v358.z - v328.z, temp_f20_19), 0.0f);
        opModelPosGet(5, &v328.x, &v328.y, &v328.z);
        opModelRotSet(5, 0.0f, func_80111490_opening(s37C, v358.x - v328.x, v358.z - v328.z, temp_f20_19), 0.0f);
        var_s0_18 += 1;
        HuPrcVSleep();
    } while (var_s0_18 < 9);
    opMotionShiftSet(0, 0x28, 4, 4, 2);
    opMotionShiftSet(1, 0x38, 4, 4, 2);
    opMotionShiftSet(2, 0x40, 4, 4, 2);
    opMotionShiftSet(3, 0x48, 4, 4, 2);
    opMotionShiftSet(4, 0x50, 4, 4, 2);
    opMotionShiftSet(5, 0x58, 4, 4, 2);
    HuPrcSleep(0x10);
    opMotionShiftSet(0xF, 0x6A, 4, 4, 0);
    HuPrcSleep(0x11);
    if (flag != 0) {
        HuAudFXPlay(0x2A8);
    }
    HuPrcSleep(0x12);
    if (flag != 0) {
        func_8004AC5C_main(0x286, 0);
        func_8004AC5C_main(0x286, 1);
        func_8004AC5C_main(0x286, 2);
    }
    opMotionShiftSet(0, 0x31, 4, 4, 0);
    opMotionShiftSet(1, 0x3C, 4, 4, 0);
    opMotionShiftSet(2, 0x45, 4, 4, 0);
    HuPrcSleep(3);
    if (flag != 0) {
        func_8004AC5C_main(0x286, 3);
        func_8004AC5C_main(0x286, 4);
    }
    opMotionShiftSet(3, 0x4C, 4, 4, 0);
    opMotionShiftSet(4, 0x54, 4, 4, 0);
    HuPrcSleep(1);
    if (flag != 0) {
        func_8004AC5C_main(0x286, 5);
    }
    opMotionShiftSet(5, 0x5D, 4, 4, 0);
    opMotionEndWait(0xF);
    opMotionShiftSet(0xF, 0x68, 4, 4, 2);
    opMotionEndWait(0);
    opMotionShiftSet(0, 0x28, 4, 4, 2);
    opMotionShiftSet(1, 0x38, 4, 4, 2);
    opMotionShiftSet(2, 0x40, 4, 4, 2);
    opMotionEndWait(3);
    opMotionShiftSet(3, 0x48, 4, 4, 2);
    opMotionShiftSet(4, 0x50, 4, 4, 2);
    opMotionEndWait(5);
    opMotionShiftSet(5, 0x58, 4, 4, 2);
    HuPrcSleep(0x14);
    opDemoObjKill(4);
    opMotionShiftSet(0, 0x33, 4, 4, 2);
    opMotionSpeedSet(0, 0.6f);
    opMotionShiftSet(1, 0x3D, 4, 4, 2);
    opMotionSpeedSet(0, 0.6f);
    opMotionShiftSet(2, 0x46, 4, 4, 2);
    opMotionSpeedSet(0, 0.6f);
    opMotionShiftSet(3, 0x4D, 4, 4, 2);
    opMotionSpeedSet(0, 0.6f);
    opMotionShiftSet(4, 0x55, 4, 4, 2);
    opMotionSpeedSet(0, 0.6f);
    opMotionShiftSet(5, 0x5E, 4, 4, 2);
    opMotionSpeedSet(0, 0.6f);
    HuVecCopyXYZ(&v338, -325.0f, 160.0f, 2600.0f);
    opModelPosGet(0xF, &v328.x, &v328.y, &v328.z);
    opModelPosGet(3, &v338.x, &v338.y, &v338.z);
    v338.y = 160.0f;
    opMotionShiftSet(0xF, 0x6B, 8, 8, 2);
    func_80017790_main(opModelIdGet(0xF), 2, 0xF, 0xA0081);
    var_s0_19 = 0;
    do {
        t60 = (f32) var_s0_19 * 0.016666668f;
        if (var_s0_19 == 0x3C) {
        } else if (var_s0_19 == 0x36) {
            opDemoOutEffCreate(3, 3);
        } else if (var_s0_19 == 0x2D) {
            opDemoOutEffCreate(2, 2);
        } else if (var_s0_19 == 0x24) {
            opDemoOutEffCreate(0, 0);
        } else if (var_s0_19 == 0x1B) {
            opDemoOutEffCreate(5, 5);
        } else if (var_s0_19 == 0x12) {
            opDemoOutEffCreate(4, 4);
        } else if (var_s0_19 == 9) {
            if (flag != 0) {
                HuAudFXPlay(0x23E);
            }
            opDemoOutEffCreate(1, 1);
        }
        temp_f0_48 = sindf(t60 * 90.0f);
        HuVecCopyXYZ(&v348, (temp_f0_48 * (v338.x - v328.x)) + v328.x, (temp_f0_48 * (v338.y - v328.y)) + v328.y, (temp_f0_48 * (v338.z - v328.z)) + v328.z);
        var_s0_19 += 1;
        temp_f26_2 = func_80111164_opening(D_80114B70_opening[0].x, D_80114B70_opening[0].z, v328.x, v328.z);
        temp_f0_49 = sindf(temp_f0_48 * 90.0f) - 0.5f;
        temp_f24 = ((-temp_f0_49 * temp_f0_49) + 0.25f) * 4.0f;
        temp_f20_20 = sindf(temp_f26_2);
        temp_f0_49 = cosdf(temp_f26_2);
        temp_f22_7 = temp_f24 * 20.0f * 5.0f;
        v348.x = (temp_f24 * ((temp_f22_7 * temp_f20_20) + (temp_f0_49 * 300.0f))) + v348.x;
        v348.y = 150.0f;
        temp_f20_21 = cosdf(temp_f26_2);
        temp_f24_2 = (temp_f24 * ((-temp_f22_7 * temp_f20_21) + (sindf(temp_f26_2) * 300.0f))) + v348.z;
        v348.z = temp_f24_2;
        opModelPosSet(0xF, v348.x, v348.y, temp_f24_2);
        opModelPosSet(0x27, v348.x, 0.0f, v348.z);
        temp_f2_8 = (1200.0f - v348.y) * 0.00083333335f;
        opModelScaleSet(0x27, temp_f2_8, 1.0f, temp_f2_8);
        opModelRotSet(0xF, 0.0f, func_80111164_opening(v348.x, v348.z, D_80114B70_opening[0].x, D_80114B70_opening[0].z), 0.0f);
        opModelPosGet(0, &v358.x, &v358.y, &v358.z);
        opModelRotSet(0, 0.0f, func_80111164_opening(v358.x, v358.z, v348.x, v348.z), 0.0f);
        opModelPosGet(1, &v358.x, &v358.y, &v358.z);
        opModelRotSet(1, 0.0f, func_80111164_opening(v358.x, v358.z, v348.x, v348.z), 0.0f);
        opModelPosGet(2, &v358.x, &v358.y, &v358.z);
        opModelRotSet(2, 0.0f, func_80111164_opening(v358.x, v358.z, v348.x, v348.z), 0.0f);
        opModelPosGet(3, &v358.x, &v358.y, &v358.z);
        opModelRotSet(3, 0.0f, func_80111164_opening(v358.x, v358.z, v348.x, v348.z), 0.0f);
        opModelPosGet(4, &v358.x, &v358.y, &v358.z);
        opModelRotSet(4, 0.0f, func_80111164_opening(v358.x, v358.z, v348.x, v348.z), 0.0f);
        opModelPosGet(5, &v358.x, &v358.y, &v358.z);
        opModelRotSet(5, 0.0f, func_80111164_opening(v358.x, v358.z, v348.x, v348.z), 0.0f);
        HuPrcVSleep();
    } while (var_s0_19 < 0x3D);
    }
    opMotionShiftSet(0xF, 0x68, 8, 8, 2);
    HuPrcSleep(0x28);
    opDemoObjKill(0);
    opDemoObjKill(1);
    opDemoObjKill(2);
    opDemoObjKill(3);
    opDemoObjKill(4);
    opDemoObjKill(5);
    opModelKill(0);
    opModelKill(1);
    opModelKill(2);
    opModelKill(3);
    opModelKill(4);
    opModelKill(5);
    opModelKill(0x28);
    opModelKill(0x29);
    opModelKill(0x2E);
    opModelKill(0x2F);
    opModelKill(0x30);
    opModelKill(0x31);
    opModelKill(0x33);
    opModelKill(0x38);
    opModelKill(0x3A);
    opModelKill(0x3B);
    opModelKill(0x3C);
    opModelKill(0x3D);
    opModelKill(0x40);
    opModelKill(0x44);
    opModelKill(0x46);
    opModelKill(0x48);
    opModelKill(0x4B);
    opModelKill(0x4C);
    opModelKill(0x4D);
    opModelKill(0x50);
    opModelKill(0x51);
    opModelKill(0x53);
    opModelKill(0x54);
    opModelKill(0x55);
    opModelKill(0x58);
    opModelKill(0x59);
    opModelKill(0x5B);
    opModelKill(0x5C);
    opModelKill(0x5D);
    opModelKill(0x5F);
    opModelKill(0x5E);
    opModelKill(0x69);
    opModelKill(0x6A);
    opModelKill(0xC);
    opModelKill(0xD);
    opModelKill(0x21);
    opModelKill(0x22);
    opModelKill(0x23);
    opModelKill(0x24);
    opModelKill(0x25);
    HuPrcSleep(8);
    D_800CD280_main = 1;
    opWipeWhiteOutCreate(0xF, 0x14);
    HuPrcSleep(0x14);
    MBBackKill();
    {
    Vec v388, v398, v3A8, v3B8;
    HuVecCopy3F(&v3A8, &D_80114BA0_opening);
    HuVecCopy3F(&v3B8, &D_80114BAC_opening);
    HuVecCopyXYZ(&v398, v3A8.x - v3B8.x, v3A8.y - v3B8.y, v3A8.z - v3B8.z);
    temp_f20_22 = cosdf(315.0f);
    v388.x = (temp_f20_22 * v398.x) + v3B8.x + (sindf(315.0f) * v398.z);
    v388.y = v3B8.y + v398.y;
    temp_f20_23 = sindf(315.0f);
    v388.z = (v3B8.z - (temp_f20_23 * v398.x)) + (cosdf(315.0f) * v398.z);
    func_801110F0_opening(v388.x, v388.y, v388.z, v3B8.x, v3B8.y, v3B8.z);
    func_80110FB0_opening(&v388, &D_80114BAC_opening);
    }
    Hu3DCamSetPerspective(0, 40.0f, 80.0f, 8000.0f);
    opModelKill(0xF);
    opModelDispOff(0x27);
    opModelKill(0x68);
    HuPrcSleep(3);
    opSprCreate(0, 0xF001D);
    opSprPosSet(0, 0x78, 0x5C);
    opSprDispOff(0);
    HuPrcSleep(3);
    opModelCreate(0x10, 0x1D000A, 0x6A9);
    opModelPosSet(0x10, 0.0f, 0.0f, 0.0f);
    opModelRotSet(0x10, 270.0f, 180.0f, 0.0f);
    opModelScaleSet(0x10, 3.0f, 3.0f, 3.0f);
    opMotionTimeSet(0x10, 0);
    opMotionFlagSet(0x10, 1);
    opModelDispOff(0x10);
    opModelCreate(0x14, 0xD000A, 0x2002A9);
    opModelPosSet(0x14, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(0x14, 1.0f, 1.0f, 1.0f);
    opMotionTimeSet(0x14, 0);
    opMotionFlagSet(0x14, 1);
    opModelCreate(9, 0xD0000, 0x2002A9);
    opModelPosSet(9, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(9, 1.0f, 1.0f, 1.0f);
    opMotionTimeSet(9, 0);
    opMotionFlagSet(9, 1);
    opModelDispOff(9);
    opModelCreate(0x15, 0xD0001, 0x2A9);
    opModelPosSet(0x15, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(0x15, 1.0f, 1.0f, 1.0f);
    opMotionTimeSet(0x15, 0);
    opMotionFlagSet(0x15, 1);
    opModelCreate(0x16, 0xD0002, 0x2A9);
    opModelPosSet(0x16, 0.0f, 0.0f, -585.0f);
    opModelScaleSet(0x16, 1.0f, 1.0f, 1.0f);
    opMotionTimeSet(0x16, 0);
    opMotionFlagSet(0x16, 1);
    temp_v0_13 = opModelIdGet(0x16);
    func_80088800_main(((OpHmfMotionObj *)func_8001D33C_main(temp_v0_13, "mario"))->unk58, 0.0f, -4000.0f, 0.0f);
    func_80088800_main(((OpHmfMotionObj *)func_8001D33C_main(temp_v0_13, "luigi"))->unk58, 0.0f, -4000.0f, 0.0f);
    func_80088800_main(((OpHmfMotionObj *)func_8001D33C_main(temp_v0_13, "peach"))->unk58, 0.0f, -4000.0f, 0.0f);
    func_80088800_main(((OpHmfMotionObj *)func_8001D33C_main(temp_v0_13, "yoshi"))->unk58, 0.0f, -4000.0f, 0.0f);
    func_80088800_main(((OpHmfMotionObj *)func_8001D33C_main(temp_v0_13, "wario"))->unk58, 0.0f, -4000.0f, 0.0f);
    func_80088800_main(((OpHmfMotionObj *)func_8001D33C_main(temp_v0_13, "donkey"))->unk58, 0.0f, -4000.0f, 0.0f);
    {
    Vec v3C8;
    HuVecCopyXYZ(&v3C8, 0.0f, 0.0f, -200.0f);
    v3C8.z -= 8.0f;
    opModelCreate(0x17, 0xD0003, 0x2A9);
    opModelPosSet(0x17, v3C8.x, v3C8.y, v3C8.z);
    }
    opModelScaleSet(0x17, 1.0f, 1.0f, 1.0f);
    opMotionTimeSet(0x17, 0);
    opMotionFlagSet(0x17, 1);
    opModelCreate(0x18, 0xD0004, 0x2A9);
    opModelPosSet(0x18, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(0x18, 1.0f, 1.0f, 1.0f);
    opMotionTimeSet(0x18, 0);
    opMotionFlagSet(0x18, 1);
    opModelCreate(0x19, 0xD0005, 0x2A9);
    opModelPosSet(0x19, 325.0f, 9.5f, 45.0f);
    opModelScaleSet(0x19, 1.0f, 1.0f, 1.0f);
    opMotionTimeSet(0x19, 0);
    opMotionFlagSet(0x19, 1);
    opModelCreate(0x1D, 0xD0007, 0x6A9);
    opModelPosSet(0x1D, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(0x1D, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0x1D, 1);
    opModelIdGet(0x1D);
    opModelDispOff(0x1D);
    opModelCreate(0x1E, 0xD0008, 0x6A9);
    opModelPosSet(0x1E, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(0x1E, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0x1E, 1);
    opModelIdGet(0x1E);
    opModelDispOff(0x1E);
    opModelCreate(0x1F, 0xD0009, 0x6A9);
    opModelPosSet(0x1F, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(0x1F, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0x1F, 1);
    opModelIdGet(0x1F);
    opModelDispOff(0x1F);
    opModelCreate(0x1B, 0xB0001, 0x6A9);
    opModelPosSet(0x1B, 0.0f, -120.0f, 300.0f);
    opModelScaleSet(0x1B, 1.8f, 1.0f, 1.8f);
    opMotionTimeSet(0x1B, 0);
    opMotionFlagSet(0x1B, 1);
    opModelDispOff(0x1B);
    opMotionCreate(0x6E, 0xA0125, 0);
    opMotionCreate(0x6F, 0xA0129, 0);
    opWipeWhiteInCreate(0xF, 0x10);
    {
    Vec v3D8, v3E8, v3F8, v408, v418, v428;
    func_801110AC_opening(&v3D8.x, &v3D8.y, &v3D8.z, &v3E8.x, &v3E8.y, &v3E8.z);
    HuVecCopyXYZ(&v3F8, v3D8.x - v3E8.x, v3D8.y - v3E8.y, v3D8.z - v3E8.z);
    var_s0_20 = 0;
    do {
        temp_f0_50 = sindf((f32) var_s0_20 * 0.016393442f * 90.0f);
        temp_f24_3 = temp_f0_50 * 45.0f;
        temp_f20_24 = cosdf(temp_f24_3);
        temp_f22_8 = (temp_f0_50 * 0.4f) + 0.6f;
        v3D8.x = (temp_f22_8 * ((temp_f20_24 * v3F8.x) + (sindf(temp_f24_3) * v3F8.z))) + v3E8.x;
        v3D8.y = (temp_f22_8 * -150.0f) + v3E8.y + v3F8.y;
        temp_f20_25 = sindf(temp_f24_3);
        v3D8.z = (temp_f22_8 * ((-v3F8.x * temp_f20_25) + (cosdf(temp_f24_3) * v3F8.z))) + v3E8.z;
        var_s0_20 += 1;
        func_801110F0_opening(v3D8.x, v3D8.y, v3D8.z, v3E8.x, v3E8.y, v3E8.z);
        HuPrcVSleep();
    } while (var_s0_20 < 0x1F);
    opModelDispOn(0xB);
    opMotionSet(0xB, 0x6D, 2);
    opMotionFlagSet(0xB, 1);
    opMotionTimeSet(0xB, 0);
    HuVecCopyXYZ(&v418, 0.0f, 325.0f, 300.0f);
    HuVecCopy3F(&v408, &v418);
    temp_f2_9 = v408.y + 400.0f;
    v408.y = temp_f2_9;
    opModelPosSet(0xB, v408.x, temp_f2_9, v408.z);
    opModelRotSet(0xB, 0.0f, 0.0f, 0.0f);
    var_s0_21 = 0;
    do {
        temp_f0_51 = sindf((f32) var_s0_21 * 0.02f * 90.0f);
        HuVecCopyXYZ(&v428, (temp_f0_51 * (v418.x - v408.x)) + v408.x, (temp_f0_51 * (v418.y - v408.y)) + v408.y, (temp_f0_51 * (v418.z - v408.z)) + v408.z);
        opModelPosSet(0xB, v428.x, v428.y, v428.z);
        if (var_s0_21 < 0x1E) {
            temp_f0_52 = sindf((f32) (var_s0_21 + 0x1F) * 0.016393442f * 90.0f);
            temp_f24_4 = temp_f0_52 * 45.0f;
            temp_f20_26 = cosdf(temp_f24_4);
            temp_f22_9 = (temp_f0_52 * 0.4f) + 0.6f;
            v3D8.x = (temp_f22_9 * ((temp_f20_26 * v3F8.x) + (sindf(temp_f24_4) * v3F8.z))) + v3E8.x;
            v3D8.y = (temp_f22_9 * -150.0f) + v3E8.y + v3F8.y;
            temp_f20_27 = sindf(temp_f24_4);
            v3D8.z = (temp_f22_9 * ((-v3F8.x * temp_f20_27) + (cosdf(temp_f24_4) * v3F8.z))) + v3E8.z;
            func_801110F0_opening(v3D8.x, v3D8.y, v3D8.z, v3E8.x, v3E8.y, v3E8.z);
        }
        var_s0_21 += 1;
        HuPrcVSleep();
    } while (var_s0_21 < 0x33);
    HuPrcSleep(0x14);
    func_80106DD0_opening(0xB, 3);
    opMotionEndWait(0xB);
    if (flag != 0) {
        HuAudFXPlay(0x159);
    }
    opMotionSet(0xB, 0x6E, 2);
    opDemoStarWaitCreate(0, 0xB, v428.x, v428.y, v428.z, 50.0f, 0x1E);
    }
    HuPrcSleep(0x14);
    func_80107C70_opening(0);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D1B);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D1A);
        opSleep(0x3C);
    }
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D1D);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D1C);
        opSleep(0x78);
    }
    func_80107CA0_opening(0);
    {
    Vec v438, v448, v458, v468;
    Vec2f v478;
    Vec v480, v490;
    if (flag != 0) {
        opDemoObjKill(0);
        opModelPosGet(0xB, &v458.x, &v458.y, &v458.z);
        HuVecCopyXYZ(&v438, v458.x, v458.y, v458.z);
        HuVecCopyXYZ(&v448, v438.x + 240.0f, v438.y + 25.0f, v438.z - 150.0f);
        var_s0_22 = 0;
        do {
            temp_f20_28 = (f32) var_s0_22 * 0.033333335f;
            HuVecCopyXYZ(&v458, (temp_f20_28 * (v448.x - v438.x)) + v438.x, (temp_f20_28 * (v448.y - v438.y)) + v438.y, (temp_f20_28 * (v448.z - v438.z)) + v438.z);
            opModelPosSet(0xB, v458.x, v458.y, v458.z);
            var_s0_22 += 1;
            HuPrcVSleep();
        } while (var_s0_22 < 0x1F);
        opDemoStarWaitCreate(0, 0xB, v458.x, v458.y, v458.z, 50.0f, 0x1E);
        opModelDispOn(0x1B);
        opModelPosSet(0x1B, -215.0f, 168.0f, v458.z + 20.0f);
        opModelScaleSet(0x1B, 1.0f, 1.0f, 1.0f);
        opMotionTimeSet(0x1B, 0);
        func_80106DD0_opening(0x1B, 1);
        if (flag != 0) {
            HuAudFXPlay(0x241);
        }
        HuPrcSleep(8);
        opModelDispOn(0x10);
        opModelScaleSet(0x10, 3.0f, 3.0f, 3.0f);
        opModelPosSet(0x10, -190.0f, 268.0f, v458.z);
        opDemoStarWaitCreate(6, 0x10, -190.0f, 268.0f, v458.z, 25.0f, 0x32);
        opMotionEndWait(0x1B);
        opModelDispOff(0x1B);
        func_80107C70_opening(0);
        if (flag != 0) {
            func_80107CD0_opening(0, 0x4D1E);
            func_80107E2C_opening(0);
        }
        func_80107CA0_opening(0);
        opDemoObjKill(6);
        HuPrcSleep(1);
        opModelPosGet(0x10, &v468.x, &v468.y, &v468.z);
        Hu3DCam3DToScreen(0, &v468, &v478);
        v478.y -= 8.0f;
        opSprDispOn(0);
        opModelDispOff(0x10);
        var_s0_23 = 0;
        do {
            temp_f20_29 = (f32) var_s0_23 * 0.0625f;
            opSprPosSet(0, (s32) ((temp_f20_29 * (160.0f - v478.x)) + v478.x), (s32) ((temp_f20_29 * (120.0f - v478.y)) + v478.y));
            temp_f0_53 = (temp_f20_29 * 0.85f) + 0.15f;
            opSprScaleSet(0, temp_f0_53, temp_f0_53);
            var_s0_23 += 1;
            HuPrcVSleep();
        } while (var_s0_23 < 0x11);
        opSprScaleSet(0, 1.0f, 1.0f);
        HuPrcSleep(0x3C);
        var_s0_24 = 0;
        var_v0_2 = 0x10 - 0;
        do {
            temp_f20_30 = (f32) var_v0_2 * 0.0625f;
            opSprPosSet(0, (s32) ((temp_f20_30 * (160.0f - v478.x)) + v478.x), (s32) ((temp_f20_30 * (120.0f - v478.y)) + v478.y));
            temp_f0_54 = (temp_f20_30 * 0.85f) + 0.15f;
            opSprScaleSet(0, temp_f0_54, temp_f0_54);
            var_s0_24 += 1;
            HuPrcVSleep();
            var_v0_2 = 0x10 - var_s0_24;
        } while (var_s0_24 < 0x11);
        opSprDispOff(0);
        opModelDispOn(0x10);
        HuPrcSleep(1);
        opDemoStarWaitCreate(6, 0x10, v468.x, v468.y, v468.z, 25.0f, 0x32);
        func_80107C70_opening(0);
        if (flag != 0) {
            func_80107CD0_opening(0, 0x4D1F);
            func_80107E2C_opening(0);
        }
        func_80107CA0_opening(0);
        opDemoObjKill(6);
        HuPrcSleep(1);
        opModelPosGet(0x10, &v468.x, &v468.y, &v468.z);
        opModelPosSet(0x1B, v468.x, v468.y - 100.0f, v468.z);
        opModelDispOn(0x1B);
        opModelScaleSet(0x1B, 1.0f, 1.0f, 1.0f);
        opMotionTimeSet(0x1B, 4);
        func_80106DD0_opening(0x1B, 1);
        if (flag != 0) {
            HuAudFXPlay(0x242);
        }
        opModelDispOff(0x10);
        opModelKill(0x10);
        opMotionEndWait(0x1B);
        opModelDispOff(0x1B);
        opModelPosSet(0x1B, 0.0f, -120.0f, 300.0f);
        opModelScaleSet(0x1B, 8.0f, 1.0f, 8.0f);
        opMotionFlagSet(0x1B, 1);
    }
    HuPrcSleep(0x24);
    func_80107C70_opening(0);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D22);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D21);
        opSleep(0x3C);
    }
    opMotionShiftSet(0xB, 0x6F, 4, 4, 2);
    func_80107CA0_opening(0);
    opDemoObjKill(0);
    HuPrcSleep(1);
    opModelPosGet(0xB, &v438.x, &v438.y, &v438.z);
    HuVecCopyXYZ(&v448, 0.0f, v438.y - 20.0f, v438.z - 100.0f);
    var_s0_25 = 0;
    do {
        temp_f0_55 = sindf((f32) var_s0_25 * 0.016666668f * 90.0f);
        HuVecCopyXYZ(&v458, (temp_f0_55 * (v448.x - v438.x)) + v438.x, (temp_f0_55 * (v448.y - v438.y)) + v438.y, (temp_f0_55 * (v448.z - v438.z)) + v438.z);
        opModelPosSet(0xB, v458.x, v458.y, v458.z);
        temp_f0_56 = (((1.0f - temp_f0_55) * 0.1f) + 0.9f) * 2.5f;
        opModelScaleSet(0xB, temp_f0_56, temp_f0_56, temp_f0_56);
        var_s0_25 += 1;
        HuPrcVSleep();
    } while (var_s0_25 < 0x3D);
    HuPrcSleep(0xA);
    opModelPosGet(0xB, &v438.x, &v438.y, &v438.z);
    HuVecCopyXYZ(&v448, 0.0f, 1250.0f, v438.z);
    var_s0_26 = 0;
    do {
        temp_f20_31 = (f32) var_s0_26 * 0.033333335f;
        temp_f20_32 = temp_f20_31 * temp_f20_31;
        HuVecCopyXYZ(&v458, (temp_f20_32 * (v448.x - v438.x)) + v438.x, (temp_f20_32 * (v448.y - v438.y)) + v438.y, temp_f20_32 + (v448.z - v438.z) + v438.z);
        opModelPosSet(0xB, v458.x, v458.y, v458.z);
        var_s0_26 += 1;
        HuPrcVSleep();
    } while (var_s0_26 < 0x1F);
    opModelDispOn(0x27);
    opModelPosSet(0x27, 0.0f, 0.0f, 300.0f);
    opModelScaleSet(0x27, 0.01f, 1.0f, 0.01f);
    opModelScaleSet(0xB, 1.0f, 1.0f, 1.0f);
    HuVecCopyXYZ(&v438, 0.0f, v458.y, 300.0f);
    HuVecCopyXYZ(&v448, 0.0f, -90.0f, 300.0f);
    HuPrcSleep(0x1E);
    var_s0_27 = 0;
    do {
        temp_f20_33 = (f32) var_s0_27 * 0.028571429f;
        temp_f20_34 = temp_f20_33 * temp_f20_33;
        HuVecCopyXYZ(&v458, (temp_f20_34 * (v448.x - v438.x)) + v438.x, (temp_f20_34 * (v448.y - v438.y)) + v438.y, temp_f20_34 + (v448.z - v438.z) + v438.z);
        opModelPosSet(0xB, v458.x, v458.y, v458.z);
        temp_f0_57 = (1250.0f - v458.y) * 0.0008f;
        opModelScaleSet(0x27, temp_f0_57, 1.0f, temp_f0_57);
        var_s0_27 += 1;
        HuPrcVSleep();
    } while (var_s0_27 < 0x21);
    if (flag != 0) {
        HuAudFXPlay(0x23F);
    }
    opModelPosSet(0x1B, 0.0f, -120.0f, 300.0f);
    opModelScaleSet(0x1B, 1.8f, 1.0f, 1.8f);
    opModelDispOn(0x1B);
    opMotionTimeSet(0x1B, 0);
    func_80106DD0_opening(0x1B, 1);
    opModelDispOn(0x1D);
    opModelDispOn(0x1E);
    opModelDispOn(0x1F);
    HuVecCopyXYZ(&v480, 0.0f, 0.0f, 300.0f);
    HuVecCopyXYZ(&v490, 250.0f, 25.0f, 355.0f);
    func_801139B0_opening(8, 0x1D, &v480, &v490, "star_red", "red_kage");
    HuVecCopyXYZ(&v490, -250.0f, 25.0f, 355.0f);
    func_801139B0_opening(9, 0x1E, &v480, &v490, "star_blue", "blue_kage");
    HuVecCopyXYZ(&v490, 0.0f, 25.0f, 70.0f);
    func_801139B0_opening(0xA, 0x1F, &v480, &v490, "star_yellow", "yellow_kage");
    opModelDispOn(9);
    opModelDispOff(0x14);
    var_s0_28 = 0x21;
    do {
        temp_f20_35 = (f32) var_s0_28 * 0.028571429f;
        temp_f20_36 = temp_f20_35 * temp_f20_35;
        HuVecCopyXYZ(&v458, (temp_f20_36 * (v448.x - v438.x)) + v438.x, (temp_f20_36 * (v448.y - v438.y)) + v438.y, temp_f20_36 + (v448.z - v438.z) + v438.z);
        opModelPosSet(0xB, v458.x, v458.y, v458.z);
        temp_f0_58 = (1250.0f - v458.y) * 0.0008f;
        opModelScaleSet(0x27, temp_f0_58, 1.0f, temp_f0_58);
        var_s0_28 += 1;
        HuPrcVSleep();
    } while (var_s0_28 < 0x24);
    }
    opModelDispOff(0xB);
    HuPrcSleep(0x2D);
    opMotionEndWait(0x1B);
    opModelDispOff(0x1B);
    opModelKill(0x1B);
    opModelDispOff(0x27);
    opModelKill(0x27);
    HuPrcSleep(0x3C);
    if (flag == 0) {
        omDelPrcObj(NULL);
while (TRUE) {
            HuPrcVSleep();
        }
    }
    D_800CD280_main = 1;
    MBBackKill();
    MBBackLoad(0x22);
    func_800E92D4_shared_board();
    Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
    func_80110FB0_opening(&D_80114B70_opening[0], &D_80114B70_opening[1]);
    func_80046558_main(opModelIdGet(0xB));
    opDemoObjKill(8);
    opDemoObjKill(9);
    opDemoObjKill(0xA);
    opModelDispOff(0xB);
    opModelKill(0xB);
    opModelKill(0x6C);
    opModelKill(0x6D);
    opModelKill(0x6E);
    opModelKill(0x6F);
    opModelKill(0x14);
    opModelKill(0x15);
    opModelKill(0x16);
    opModelKill(0x17);
    opModelKill(0x18);
    opModelKill(0x19);
    opModelKill(0x1D);
    opModelKill(0x1E);
    opModelKill(0x1F);
    opModelKill(9);
    opMotionTimeSet(0x12, 0);
    opMotionFlagSet(0x12, 1);
    opMotionTimeSet(0x13, 0);
    opMotionFlagSet(0x13, 1);
    opModelDispOff(0x20);
    opModelCreate(0x11, 0xA00EE, 0x6A9);
    opModelPosSet(0x11, -40.0f, 0.0f, 2775.0f);
    opModelScaleSet(0x11, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(0x11, 2);
    opModelDispOn(0x20);
    opModelScaleSet(0x20, 1.0f, 1.0f, 1.0f);
    opModelPosSet(0x20, -40.0f, 0.0f, 2775.0f);
    {
    Vec v4A0, v4B0, v4C0;
    HuVecCopyXYZ(&v4A0, -880.0f, 0.0f, 2820.0f);
    HuVecCopyXYZ(&v4B0, -53.0f, 0.0f, 2807.0f);
    opMotionCreate(0x71, 0xA00F1, 0);
    HuVecCopyXYZ(&v4C0, ((v4B0.x - v4A0.x) * 0.6166667f) + v4A0.x, ((v4B0.y - v4A0.y) * 0.6166667f) + v4A0.y, ((v4B0.z - v4A0.z) * 0.6166667f) + v4A0.z);
    opModelPosSet(0x11, v4C0.x, v4C0.y, v4C0.z);
    opModelPosSet(0x20, v4C0.x, v4C0.y, v4C0.z);
    temp_f0_59 = func_80111164_opening(v4C0.x, v4C0.z, D_80114B70_opening[0].x, D_80114B70_opening[0].z);
    s4D4 = temp_f0_59;
    opModelRotSet(0x11, 0.0f, temp_f0_59, 0.0f);
    opMotionShiftSet(0x11, 0x71, 8, 8, 2);
    HuPrcSleep(0xA);
    if (flag != 0) {
        HuAudFXPlay(0x2A0);
    }
    func_80107C70_opening(0);
    func_80107CD0_opening(0, 0x4D25);
    HuPrcSleep(0x12);
    opMotionSpeedSet(0x11, 1.4f);
    var_s0_29 = 0;
    do {
        opModelPosGet(0x11, &v4C0.x, &v4C0.y, &v4C0.z);
        temp_f0_60 = func_80111490_opening(s4D4, v4B0.x - v4C0.x, v4B0.z - v4C0.z, (f32) var_s0_29 * 0.125f);
        s4D0 = temp_f0_60;
        opModelRotSet(0x11, 0.0f, temp_f0_60, 0.0f);
        var_s0_29 += 1;
        HuPrcVSleep();
    } while (var_s0_29 < 8);
    var_s0_30 = 0x25;
    temp_f0_61 = func_80111164_opening(v4A0.x, v4A0.z, v4B0.x, v4B0.z);
    s4D4 = temp_f0_61;
    s4D0 = temp_f0_61;
    opModelRotSet(0x11, 0.0f, temp_f0_61, 0.0f);
    do {
        temp_f20_37 = (f32) var_s0_30 * 0.016666668f;
        HuVecCopyXYZ(&v4C0, ((v4B0.x - v4A0.x) * temp_f20_37) + v4A0.x, ((v4B0.y - v4A0.y) * temp_f20_37) + v4A0.y, ((v4B0.z - v4A0.z) * temp_f20_37) + v4A0.z);
        opModelPosSet(0x11, v4C0.x, v4C0.y, v4C0.z);
        opModelPosSet(0x20, v4C0.x, v4C0.y, v4C0.z);
        var_s0_30 += 1;
        HuPrcVSleep();
    } while (var_s0_30 < 0x3D);
    opMotionSpeedSet(0x11, 1.0f);
    opModelRotGet(0x11, &s4D0, &s4D4, &s4D0);
    var_s0_31 = 0;
    do {
        opModelPosGet(0x11, &v4C0.x, &v4C0.y, &v4C0.z);
        temp_f0_62 = func_80111490_opening(s4D4, D_80114B70_opening[0].x - v4C0.x, D_80114B70_opening[0].z - v4C0.z, (f32) var_s0_31 * 0.0625f);
        s4D0 = temp_f0_62;
        opModelRotSet(0x11, 0.0f, temp_f0_62, 0.0f);
        var_s0_31 += 1;
        HuPrcVSleep();
    } while (var_s0_31 < 0x10);
    opModelPosGet(0x11, &v4C0.x, &v4C0.y, &v4C0.z);
    if (flag != 0) {
        func_80107CD0_opening(0, 0x4D26);
        func_80107E2C_opening(0);
    } else {
        func_80107CD0_opening(0, 0x4D25);
        HuPrcSleep(0x46);
    }
    func_80107CA0_opening(0);
    opModelPosGet(0x11, &v4A0.x, &v4A0.y, &v4A0.z);
    HuVecCopyXYZ(&v4B0, 800.0f, 0.0f, 3030.0f);
    opModelRotGet(0x11, &s4D0, &s4D4, &s4D0);
    var_s0_32 = 0;
    do {
        opModelPosGet(0x11, &v4C0.x, &v4C0.y, &v4C0.z);
        temp_f0_63 = func_80111490_opening(s4D4, v4B0.x - v4C0.x, v4B0.z - v4C0.z, (f32) var_s0_32 * 0.0625f);
        s4D0 = temp_f0_63;
        opModelRotSet(0x11, 0.0f, temp_f0_63, 0.0f);
        var_s0_32 += 1;
        HuPrcVSleep();
    } while (var_s0_32 < 0x10);
    opMotionSpeedSet(0x11, 1.4f);
    var_s0_33 = 0;
    do {
        temp_f20_38 = (f32) var_s0_33 * 0.016666668f;
        HuVecCopyXYZ(&v4C0, ((v4B0.x - v4A0.x) * temp_f20_38) + v4A0.x, ((v4B0.y - v4A0.y) * temp_f20_38) + v4A0.y, ((v4B0.z - v4A0.z) * temp_f20_38) + v4A0.z);
        opModelPosSet(0x11, v4C0.x, v4C0.y, v4C0.z);
        opModelPosSet(0x20, v4C0.x, v4C0.y, v4C0.z);
        HuPrcVSleep();
        if (var_s0_33 == 0xA) {
            opDemoEndSet(1);
        }
        var_s0_33 += 1;
    } while (var_s0_33 < 0x3D);
    }
    var_s0_34 = 0;
    do {
        var_s0_34 += 1;
        HuPrcVSleep();
    } while (var_s0_34 < 0x1E);
    omDelPrcObj(NULL);
while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114CE4_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114D84_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114D90_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114D9C_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114DA8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoEvent);
#endif

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
void func_80111580_opening(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
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

/* Starts the swirl effect on model (file dir/no): vertex-scatter with func_80111F58_opening as the
   update; every face group idle. */
s16 func_801117D4_opening(s32 arg0, s32 arg1) {
    HmfModel *m;
    OpFxHmf *hmf;
    OpFxWork *work;
    OpFxPart *part;
    s16 model;
    s16 i;
    f32 radius;
    f32 step;
    f32 speed;

    HuVecCopyXYZ(&D_80117378_opening, 0.0f, 0.0f, 0.0f);
    D_80117384_opening = 0;
    model = func_8000B108_main(arg0, arg1);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_80111F58_opening);
    hmf = (OpFxHmf *)HmfModelData[model].hmf;
    work = (OpFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->unk08 = 30.0f;
    work->unk0C = 720.0f;
    work->unk10 = 80.0f;
    work->unk14 = 5.0f;
    radius = work->unk10 / 10.0f;
    step = (work->unk10 - radius) / work->unk08;
    speed = work->unk0C / work->unk08;
    for (i = 0; i < hmf->groupCount; i++) {
        part->pos.x = part->pos.y = part->pos.z = 0.0f;
        part->angle = 0.0f;
        part->radius = radius;
        part->radiusStep = step;
        part->vel.x = speed;
        part->vel.y = 0.0f;
        part->vel.z = 0.0f;
        part->scale = 0.0f;
        part->phase = 180.0f;
        part++;
    }
    return model;
}

/* As func_801117D4_opening with func_80112120_opening (falling sparks) as the update. */
s16 func_80111984_opening(s32 arg0, s32 arg1) {
    HmfModel *m;
    OpFxHmf *hmf;
    OpFxWork *work;
    OpFxPart *part;
    s16 model;
    s16 i;
    f32 radius;
    f32 step;
    f32 speed;

    HuVecCopyXYZ(&D_80117378_opening, 0.0f, 0.0f, 0.0f);
    D_80117384_opening = 0;
    model = func_8000B108_main(arg0, arg1);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_80112120_opening);
    hmf = (OpFxHmf *)HmfModelData[model].hmf;
    work = (OpFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->unk08 = 30.0f;
    work->unk0C = 720.0f;
    work->unk10 = 80.0f;
    work->unk14 = 5.0f;
    radius = work->unk10 / 10.0f;
    step = (work->unk10 - radius) / work->unk08;
    speed = work->unk0C / work->unk08;
    for (i = 0; i < hmf->groupCount; i++) {
        part->pos.x = part->pos.y = part->pos.z = 0.0f;
        part->angle = 0.0f;
        part->radius = radius;
        part->radiusStep = step;
        part->vel.x = speed;
        part->vel.y = 0.0f;
        part->vel.z = 0.0f;
        part->scale = 0.0f;
        part->phase = 180.0f;
        part++;
    }
    return model;
}

/* Park-Miller minimal standard step (Schrage): seed 0 reseeds from rand8 and the count register. */
u32 func_80111B34_opening(u32 seed) {
    s32 hi, lo;

    if (seed == 0) {
        seed = rand8();
        seed = seed ^ osGetCount();
        seed ^= 0xD826BC89;
    }
    hi = seed / 0x1F31D;
    lo = seed - (hi * 0x1F31D);
    seed = hi * 0xB14;
    seed = seed - lo * 0x41A7;
    return seed;
}

void func_80111C08_opening(void) {
    D_80114BE0_opening = func_80111B34_opening(D_80114BE0_opening);
}

/* Random number in 0..max-1. */
u32 func_80111C30_opening(u32 max) {
    D_80114BE0_opening = func_80111B34_opening(D_80114BE0_opening);
    return (D_80114BE0_opening & 0x7FFFFFFF) % max;
}

/* Swirl: launches the first idle face group from (x, y, z); 1 if one was free. */
s32 func_80111C88_opening(s16 model, f32 x, f32 y, f32 z) {
    OpFxHmf *hmf;
    OpFxWork *work;
    OpFxPart *part;
    s16 i;
    f32 tilt;

    hmf = (OpFxHmf *)HmfModelData[model].hmf;
    work = (OpFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->center.x = x;
    work->center.y = y;
    work->center.z = z;
    for (i = 0; i < hmf->groupCount; i++, part++) {
        if (part->phase >= 180.0f) {
            part->angle = func_80111C30_opening(360);
            part->radius = work->unk10 / 10.0f;
            tilt = (f32)func_80111C30_opening(150) - 75.0f;
            part->vel.y = sindf(tilt);
            part->vel.z = cosdf(tilt);
            part->scale = 0.0f;
            part->phase = 0.0f;
            return 1;
        }
    }
    return 0;
}

/* Sparks: launches the first idle face group from (x, y, z) in a random direction at scale. */
s32 func_80111DDC_opening(s16 model, f32 x, f32 y, f32 z, f32 scale) {
    OpFxHmf *hmf;
    OpFxWork *work;
    OpFxPart *part;
    s16 i;

    hmf = (OpFxHmf *)HmfModelData[model].hmf;
    D_80117378_opening.x = x; /* retail stores x in all three */
    D_80117378_opening.y = x;
    D_80117378_opening.z = x;
    work = (OpFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    work->center.x = x;
    work->center.y = y;
    work->center.z = z;
    for (i = 0; i < hmf->groupCount; i++, part++) {
        if (part->phase >= 180.0f) {
            part->phase = 0.0f;
            part->vel.x = sindf(func_80111C30_opening(360));
            part->vel.y = sindf(func_80111C30_opening(360));
            part->vel.z = sindf(func_80111C30_opening(360));
            part->pos.x = work->center.x;
            part->pos.z = work->center.z;
            part->pos.y = work->center.y;
            part->scale = scale;
            return 1;
        }
    }
    return 0;
}

/* Swirl update: each live group circles the centre on a widening radius while it fades in. */
void func_80111F58_opening(s16 model) {
    OpFxHmf *hmf;
    OpFxWork *work;
    OpFxPart *part;
    s16 i;
    s16 count;
    f32 r;

    hmf = (OpFxHmf *)HmfModelData[model].hmf;
    work = (OpFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    count = hmf->groupCount;
    for (i = 0; i < count; i++, part++) {
        if (part->phase < 180.0f) {
            part->angle += part->vel.x;
            if (part->angle < 0.0f) {
                part->angle += 360.0f;
            } else if (part->angle >= 360.0f) {
                part->angle -= 360.0f;
            }
            part->radius += part->radiusStep;
            r = part->radius * part->vel.z;
            part->pos.x = r * sindf(part->angle) + work->center.x;
            part->pos.z = r * cosdf(part->angle) + work->center.z;
            part->pos.y = part->radius * part->vel.y + work->center.y;
            part->phase += work->unk14;
            if (part->phase > 180.0f) {
                part->phase = 180.0f;
            }
            part->scale = sindf(part->phase) * work->unk14;
        }
    }
    work->frame++;
}

/* Sparks update: each live group moves by 3 x its velocity and falls; it shrinks, idle at 0. */
void func_80112120_opening(s16 model) {
    OpFxHmf *hmf;
    OpFxWork *work;
    OpFxPart *part;
    s16 i;
    s16 count;

    hmf = (OpFxHmf *)HmfModelData[model].hmf;
    work = (OpFxWork *)HmfModelData[model].unkBC;
    part = work->parts;
    count = hmf->groupCount;
    for (i = 0; i < count; i++, part++) {
        if (part->phase < 180.0f) {
            part->pos.x = part->vel.x * 3.0f + part->pos.x;
            part->pos.y = part->vel.y * 3.0f + part->pos.y - 1.0f;
            part->pos.z = part->vel.z * 3.0f + part->pos.z;
            part->scale = (part->scale - 0.2f > 0.0f) ? part->scale - 0.4f : 0.0f;
            if (part->scale <= 0.0f) {
                part->scale = 0.0f;
                part->phase = 180.0f;
            }
        }
    }
    work->frame++;
}

/* Title screen: camera, the two background layers and the logo / press-start sprites. */
void opTitleSetup(void) {
    Vec pos;
    Vec at;
    u16 esp;

    func_801061F0_opening();
    func_80110F48_opening();
    opContErrorCreate();
    func_80112944_opening();
    pos = D_80114D84_opening;
    at = D_80114D90_opening;
    func_80110FB0_opening(&pos, &at);
    opSprBGCreate(0, 0x100000);
    opSprPosSet(0, 160, 120);
    func_8000BCC8_main(opEspIdGet(0), 9);
    opSprBGDispOn(0);
    opSprBGCreate(1, 0x100001);
    opSprPosSet(1, 160, 120);
    func_8000BCC8_main(opEspIdGet(1), 11);
    opSprBGDispOn(1);
    opSprBGCreate(2, 0x100002);
    opSprPosSet(2, 160, 71);
    opSprAttrSet(2, 8);
    opSprAlphaSet(2, 255);
    func_8000BCC8_main(opEspIdGet(2), 8);
    opSprBGCreate(3, 0x100005);
    opSprPosSet(3, 160, 71);
    opSprAttrSet(3, 8);
    opSprAlphaSet(3, 255);
    esp = opEspIdGet(3);
    func_8000BEAC_main(esp, 255, 255, 255);
    func_8000BCC8_main(esp, 9);
    opSprBGCreate(4, 0x100003);
    opSprPosSet(4, 158, 197);
    opSprAttrSet(4, 8);
    opSprAlphaSet(4, 255);
    func_8000BCC8_main(opEspIdGet(4), 8);
    opSprBGCreate(5, 0x100004);
    opSprPosSet(5, 158, 197);
    opSprAttrSet(5, 0x1008);
    opSprAlphaSet(5, 255);
    esp = opEspIdGet(5);
    func_8000BEAC_main(esp, 0, 6, 115);
    func_8000BCC8_main(esp, 9);
}

// Register allocation (masked 10): the first fade loop's clamp is copy-propagated and 1/60 is
// held in a GPR; the logo/press-start reads relocate against D_80114EB0+0x70 (retail: split label
// D_80114F20). Logic checked against the asm.
#ifdef NON_MATCHING
/* Title sequence: fade the first background out, bounce the logo in on a damped spring, fade the
   press-start sprites in, then show the controller check for 780 frames and end the process. */
void opTitleSprMain(void) {
    s32 i;
    f32 f;
    f32 t;
    f32 damp;
    f32 vel;
    f32 acc;
    f32 scale;
    u16 alpha;

    opSprBGDispOff(2);
    opSprBGDispOff(3);
    opSprBGDispOff(4);
    opSprBGDispOff(5);
    HuAudFXPlay(0x240);
    HuPrcSleep(16);
    for (i = 0; i < 40; i++) {
        HuPrcVSleep();
        f = 1.0f - i * (1.0f / 60.0f);
        t = f;
        if (f < 0.0f) {
            t = 0.0f;
        }
        opSprAlphaSet(0, (u8)(t * 255.0f));
    }
    opSprBGDispOn(2);
    opSprScaleSet(2, 0.0f, 0.0f);
    opSprScaleSet(3, 0.0f, 0.0f);
    vel = -2.0f;
    acc = 0.0f;
    HuAudSeqPlay(2);
    for (i = 40; i < 61; i++) {
        HuPrcVSleep();
        t = 1.0f - i * (1.0f / 60.0f);
        if (t < 0.0f) {
            t = 0.0f;
        }
        opSprAlphaSet(0, (u8)(t * 255.0f));
        damp = 1.0f - (i - 40) * 0.05f;
        if (damp < 0.0f) {
            damp = 0.0f;
        }
        acc += vel * -0.8f;
        vel += acc;
        vel *= 0.7f;
        scale = vel * damp + 1.0f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        opSprScaleSet(2, scale, scale);
        opSprScaleSet(3, scale, scale);
    }
    HuPrcVSleep();
    opSprScaleSet(2, 1.0f, 1.0f);
    opSprScaleSet(3, 1.0f, 1.0f);
    opSprAlphaSet(0, 0);
    opSprBGDispOn(4);
    opSprBGDispOn(5);
    func_80106768_opening(4, 0, 0);
    func_80106768_opening(5, 0, 0);
    opSprAlphaSet(4, 0);
    opSprAlphaSet(5, 0);
    func_8000BDDC_main(D_80114EB0_opening[4].espId, 0);
    func_8000BDDC_main(D_80114EB0_opening[5].espId, 0);
    for (i = 0; i < 9; i++) {
        HuPrcVSleep();
        alpha = i << 5;
        opSprAlphaSet(4, alpha);
        opSprAlphaSet(5, alpha);
    }
    opSprAlphaSet(4, 256);
    opSprAlphaSet(5, 256);
    func_8000BDDC_main(D_80114EB0_opening[4].espId, 1);
    func_8000BDDC_main(D_80114EB0_opening[5].espId, 1);
    opContErrorDispOn();
    HuPrcSleep(780);
    opContErrorDispOff();
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opTitleSprMain);
#endif

void opTitleKill(void) {
    opSprKill(5);
    opSprKill(4);
    opSprKill(3);
    opSprKill(2);
    opSprKill(1);
    opSprKill(0);
    opContErrorKill();
    opDemoObjKillAll();
    opDemoModelKill();
    opDemoSprKill();
}

void func_80112944_opening(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_80117388_opening[i].obj = NULL;
    }
}

void opDemoObjKillAll(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        opDemoObjKill(i);
    }
}

void opDemoObjKill(s32 no) {
    if (D_80117388_opening[no].obj != NULL) {
        omDelObj(D_80117388_opening[no].obj);
    }
    D_80117388_opening[no].obj = NULL;
}

void opDemoObjCreate(s32 no, omObjFunc func) {
    omObjData *obj;

    opDemoObjKill(no);
    obj = omAddObj(6, 0, 0, -1, func);
    D_80117388_opening[no].obj = obj;
    obj->work[0] = no;
}

/* Idle/action loop for a demo model: wait maxTime frames on motion w.i[1], play motion w.i[2]
   once, then back. time counts frames, -1 while the one-shot motion plays; w.i[0] is the model. */
void func_80112A74_opening(omObjData *obj) {
    s8 no = obj->work[0];
    s32 model = D_80117388_opening[no].w.i[0];

    if (D_80117388_opening[no].time < 0) {
        if (opMotionEndCheck(model) != 0) {
            opMotionShiftSet(model, D_80117388_opening[no].w.i[2], 4, 4, 2);
            D_80117388_opening[no].time = 0;
        }
    } else if (D_80117388_opening[no].time >= D_80117388_opening[no].maxTime) {
        opMotionShiftSet(model, D_80117388_opening[no].w.i[1], 4, 4, 0);
        D_80117388_opening[no].time = -1;
    } else {
        D_80117388_opening[no].time++;
    }
}

/* Starts func_80112A74_opening in slot no for model slot model: one-shot motion motA, loop motion
   motB, start frame time (< 0: start on the loop), loop length wait. */
void func_80112BA0_opening(s32 no, s32 model, s32 motA, s32 motB, s32 time, s32 wait) {
    opDemoObjCreate(no, func_80112A74_opening);
    D_80117388_opening[no].w.i[0] = model;
    D_80117388_opening[no].w.i[1] = motA;
    D_80117388_opening[no].w.i[2] = motB;
    D_80117388_opening[no].maxTime = wait;
    D_80117388_opening[no].time = time;
    if (time >= 0) {
        opMotionSet(model, motA, 0);
        opMotionTimeSet(model, time);
    } else {
        opMotionSet(model, motB, 2);
        opMotionTimeSet(model, 0);
    }
}

/* Restarts model slot w.i[0]'s motion from frame 0 every maxTime frames. */
void func_80112C8C_opening(omObjData *obj) {
    s8 no = obj->work[0];
    s32 model = D_80117388_opening[no].w.i[0];

    if (D_80117388_opening[no].time >= D_80117388_opening[no].maxTime) {
        opMotionTimeSet(model, 0);
        D_80117388_opening[no].time = 0;
    } else {
        D_80117388_opening[no].time++;
    }
}

void func_80112D30_opening(s32 no, s32 model, s32 time, s32 wait) {
    opDemoObjCreate(no, func_80112C8C_opening);
    D_80117388_opening[no].w.i[0] = model;
    D_80117388_opening[no].time = time;
    D_80117388_opening[no].maxTime = wait;
    func_80106DD0_opening(model, 3);
    if (time > 0) {
        opMotionTimeSet(model, time);
    } else {
        opMotionTimeSet(model, 0);
    }
}

/* A character leaving: its model and shadow shrink to nothing over 7 frames while the swirl
   effect spins up; hidden at frame 20, effect and object freed at frame 40. */
void opDemoOutEffMain(omObjData *obj) {
    s8 no = obj->work[0];
    s32 model = OP_FX_MODEL(no);
    s32 shadow = model + 32;
    s16 fx = OP_FX_FX(no);
    f32 scale = OP_FX_SCALE(no);
    f32 pos[3];

    HuVecCopy3F((Vec *)pos, OP_FX_POS(no));
    if (OP_FX_TIME(no) >= 40) {
        func_8001ACDC_main(fx);
        OP_FX_TIME(no) = 0;
        opDemoObjKill(no);
    } else if (OP_FX_TIME(no) >= 20) {
        opModelScaleSet(model, 1.0f, 1.0f, 1.0f);
        opModelScaleSet(shadow, 3.0f, 1.0f, 3.0f);
        opModelDispOff(model);
        opModelDispOff(shadow);
        OP_FX_TIME(no)++;
    } else {
        scale -= 1.0f / 7.0f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        func_80111C88_opening(fx, pos[0], pos[1], pos[2]);
        opModelScaleSet(model, scale, 1.0f, scale);
        opModelScaleSet(shadow, scale, 1.0f, scale);
        OP_FX_SCALE(no) = scale;
        OP_FX_TIME(no)++;
    }
}

void opDemoOutEffCreate(s32 no, s32 model) {
    f32 pos[3];
    s16 fx;

    opDemoObjCreate(no, opDemoOutEffMain);
    fx = func_801117D4_opening(0x110012, 0x689);
    OP_FX_MODEL(no) = model;
    OP_FX_FX(no) = fx;
    opModelPosGet(model, &pos[0], &pos[1], &pos[2]);
    pos[1] += 60.0f;
    HuVecCopy3F(OP_FX_POS(no), (Vec *)pos);
    OP_FX_SCALE(no) = 1.0f;
    OP_FX_TIME(no) = 0;
}

/* The guide arriving: the swirl effect runs 25 units above its position for 50 frames, then the
   effect and object are freed at frame 80. */
void opDemoGuideInEffMain(omObjData *obj) {
    s8 no = obj->work[0];
    s16 fx = OP_FX_FX(no);
    f32 scale = OP_FX_SCALE(no);
    f32 pos[3];

    HuVecCopy3F((Vec *)pos, OP_FX_POS(no));
    if (OP_FX_TIME(no) >= 80) {
        func_8001ACDC_main(fx);
        OP_FX_TIME(no) = 0;
        opDemoObjKill(no);
    } else if (OP_FX_TIME(no) >= 50) {
        OP_FX_TIME(no)++;
    } else {
        scale -= 1.0f / 7.0f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        func_80111C88_opening(fx, pos[0], pos[1] + 25.0f, pos[2]);
        OP_FX_SCALE(no) = scale;
        OP_FX_TIME(no)++;
    }
}

void opDemoGuideInEffCreate(s32 no, s32 model) {
    f32 pos[3];
    s16 fx;

    opDemoObjCreate(no, opDemoGuideInEffMain);
    fx = func_801117D4_opening(0x110012, 0x689);
    OP_FX_MODEL(no) = model;
    OP_FX_FX(no) = fx;
    opModelPosGet(model, &pos[0], &pos[1], &pos[2]);
    pos[1] += 60.0f;
    HuVecCopy3F(OP_FX_POS(no), (Vec *)pos);
    OP_FX_SCALE(no) = 1.0f;
    OP_FX_TIME(no) = 0;
}

/* A star bobbing in place: height sin(angle) * w.f[4], one turn every maxTime frames. */
void opDemoStarWaitMain(omObjData *obj) {
    s8 no = obj->work[0];
    s32 model = D_80117388_opening[no].w.i[0];
    f32 step;
    f32 angle;
    f32 dy;
    f32 pos[3];

    step = 1.0f / D_80117388_opening[no].maxTime;
    angle = step * 360.0f + D_80117388_opening[no].w.f[5];
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    D_80117388_opening[no].w.f[5] = angle;
    dy = sindf(angle) * D_80117388_opening[no].w.f[4];
    HuVecCopy3F((Vec *)pos, OP_STAR_POS(no));
    opModelPosSet(model, pos[0], dy + pos[1], pos[2]);
}

void opDemoStarWaitCreate(s32 no, s32 model, f32 x, f32 y, f32 z, f32 height, s32 period) {
    opDemoObjCreate(no, opDemoStarWaitMain);
    D_80117388_opening[no].w.i[0] = model;
    HuVecCopyXYZ(OP_STAR_POS(no), x, y, z);
    D_80117388_opening[no].w.f[4] = height;
    D_80117388_opening[no].w.f[5] = 0.0f;
    D_80117388_opening[no].time = 0;
    D_80117388_opening[no].maxTime = period;
}

/* Places the jump's two parts: part 0 at pos, part 1 (the shadow) 4 above shadow; both scaled
   (scale, 1, scale) and turned by rotY. */
void func_801134FC_opening(s32 no, Vec *pos, Vec *shadow, f32 scale, f32 rotY) {
    func_80088800_main(D_80117388_opening[no].w.jump.part[0]->mtx, pos->x, pos->y, pos->z);
    func_80017CD0_main(D_80117388_opening[no].w.jump.part[0]->mtx, scale, 1.0f, scale);
    func_800185A4_main((Mtx *)D_80117388_opening[no].w.jump.part[0]->mtx, rotY);
    func_80088800_main(D_80117388_opening[no].w.jump.part[1]->mtx, shadow->x, shadow->y + 4.0f, shadow->z);
    func_80017CD0_main(D_80117388_opening[no].w.jump.part[1]->mtx, scale, 1.0f, scale);
    func_800185A4_main((Mtx *)D_80117388_opening[no].w.jump.part[1]->mtx, rotY);
}

/* After landing: bob 12 units, one turn every maxTime frames. */
void func_8011361C_opening(omObjData *obj) {
    s8 no = obj->work[0];
    Vec pos;
    Vec shadow;
    f32 step;
    f32 angle;
    f32 dy;

    step = 1.0f / D_80117388_opening[no].maxTime;
    angle = step * 360.0f + D_80117388_opening[no].w.jump.angle;
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    D_80117388_opening[no].w.jump.angle = angle;
    dy = sindf(angle) * D_80117388_opening[no].w.jump.amp;
    HuVecCopy3F(&pos, &D_80117388_opening[no].w.jump.to);
    pos.y += dy;
    HuVecCopy3F(&shadow, &D_80117388_opening[no].w.jump.to);
    shadow.y = 0.0f;
    func_801134FC_opening(no, &pos, &shadow, 1.0f, 0.0f);
}

/* The jump: maxTime frames along a parabola (peak 100) from `from` to `to`, the model's two parts
   growing from 0.2 to full scale with the shadow on the ground; then func_8011361C_opening. */
void func_8011373C_opening(omObjData *obj) {
    s8 no = obj->work[0];
    s32 model = D_80117388_opening[no].w.jump.model;
    Vec from;
    Vec to;
    Vec cur;
    Vec pos;
    Vec shadow;
    f32 t;

    HuVecCopy3F(&from, &D_80117388_opening[no].w.jump.from);
    HuVecCopy3F(&to, &D_80117388_opening[no].w.jump.to);
    t = (1.0f / D_80117388_opening[no].maxTime) * D_80117388_opening[no].time;
    HuVecCopyXYZ(&cur, t * (to.x - from.x) + from.x,
                 t * (to.y - from.y) + from.y + (0.25 - (t - 0.5f) * (t - 0.5f)) * 4.0 * 5.0 * 20.0,
                 t * (to.z - from.z) + from.z);
    HuVecCopy3F(&from, &D_80117388_opening[no].w.jump.from);
    opModelPosSet(model, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&pos, cur.x, cur.y, cur.z);
    HuVecCopyXYZ(&shadow, cur.x, 0.0f, cur.z);
    func_801134FC_opening(no, &pos, &shadow, t * 0.8 + 0.2f, 0.0f);
    if (D_80117388_opening[no].time >= D_80117388_opening[no].maxTime) {
        D_80117388_opening[no].time = 0;
        obj->func = func_8011361C_opening;
    } else {
        D_80117388_opening[no].time++;
    }
}

/* Starts a jump in slot no for model slot model from *from to *to; partA / partB name the model
   parts placed by func_801134FC_opening (the body and its shadow). */
void func_801139B0_opening(s32 no, s32 model, Vec *from, Vec *to, char *partA, char *partB) {
    s16 id;

    opDemoObjCreate(no, func_8011373C_opening);
    D_80117388_opening[no].w.jump.model = model;
    HuVecCopy3F(&D_80117388_opening[no].w.jump.from, from);
    HuVecCopy3F(&D_80117388_opening[no].w.jump.to, to);
    D_80117388_opening[no].w.jump.amp = 12.0f;
    D_80117388_opening[no].w.jump.angle = 0.0f;
    D_80117388_opening[no].time = 0;
    D_80117388_opening[no].maxTime = 20;
    id = opModelIdGet(model);
    D_80117388_opening[no].w.jump.part[0] = func_8001D33C_main(id, partA);
    D_80117388_opening[no].w.jump.part[1] = func_8001D33C_main(id, partB);
    func_8011373C_opening(D_80117388_opening[no].obj);
}

/* Hover: the model drifts around fly.base on three phases (x sway 65, y bob 0..40, z sway 11),
   facing its direction of travel. */
void func_80113AE8_opening(omObjData *obj) {
    s8 no = obj->work[0];
    s32 model = D_80117388_opening[no].w.fly.model;
    s32 time = D_80117388_opening[no].time;
    f32 p0 = D_80117388_opening[no].w.fly.phase[0];
    f32 p1 = D_80117388_opening[no].w.fly.phase[1];
    f32 p2 = D_80117388_opening[no].w.fly.phase[2];
    Vec old;
    Vec cur;

    old.x = sindf(p0) * 65.0f + D_80117388_opening[no].w.fly.base.x;
    old.y = (sindf(p1) + 1.0f) * 20.0f + D_80117388_opening[no].w.fly.base.y;
    old.z = cosdf(p2) * 11.0f + D_80117388_opening[no].w.fly.base.z;
    p0 = (p0 + 1.45f < 360.0f) ? p0 + 1.45f : p0 - 360.0f + 1.45f;
    p1 = (p1 + 13.99f < 360.0f) ? p1 + 13.99f : p1 - 360.0f + 13.99f;
    p2 = (p2 + 0.8f < 360.0f) ? p2 + 0.8f : p2 - 360.0f + 0.8f;
    cur.x = D_80117388_opening[no].w.fly.base.x + sindf(p0) * 65.0f;
    cur.y = (sindf(p1) + 1.0f) * 20.0f + D_80117388_opening[no].w.fly.base.y;
    cur.z = cosdf(p2) * 11.0f + D_80117388_opening[no].w.fly.base.z;
    opModelPosSet(model, cur.x, cur.y, cur.z);
    opModelRotSet(model, 0.0f, func_80111164_opening(old.x, old.z, cur.x, cur.z), 0.0f);
    if (++time > 256) {
        time = 0;
    }
    D_80117388_opening[no].time = time;
    D_80117388_opening[no].w.fly.phase[0] = p0 + (rand8() & 7) * 0.3f;
    D_80117388_opening[no].w.fly.phase[1] = p1 + (rand8() & 3) * 0.3f;
    D_80117388_opening[no].w.fly.phase[2] = p2;
}

/* Flight: maxTime frames in a straight line from fly.base to fly.target with the hover bob,
   facing the target; then the object ends. */
void func_80113E8C_opening(omObjData *obj) {
    s8 no = obj->work[0];
    s32 model = D_80117388_opening[no].w.fly.model;
    s32 time = D_80117388_opening[no].time;
    f32 t = (1.0f / D_80117388_opening[no].maxTime) * D_80117388_opening[no].time;
    Vec from;
    Vec to;
    Vec cur;
    f32 p0;
    f32 p1;
    f32 p2;

    time++;
    if (t < 1.0f) {
        HuVecCopyXYZ(&from, D_80117388_opening[no].w.fly.base.x, D_80117388_opening[no].w.fly.base.y,
                     D_80117388_opening[no].w.fly.base.z);
        HuVecCopyXYZ(&to, D_80117388_opening[no].w.fly.target.x, D_80117388_opening[no].w.fly.target.y,
                     D_80117388_opening[no].w.fly.target.z);
        p0 = D_80117388_opening[no].w.fly.phase[0];
        p1 = D_80117388_opening[no].w.fly.phase[1];
        p2 = D_80117388_opening[no].w.fly.phase[2];
        cur.x = (to.x - from.x) * t + from.x;
        cur.y = (to.y - from.y) * t + from.y;
        cur.z = (to.z - from.z) * t + from.z;
        p1 = (p1 + 13.99f < 360.0f) ? p1 + 13.99f : p1 - 360.0f + 13.99f;
        cur.y = (sindf(p1) + 1.0f) * 20.0f + cur.y;
        opModelPosSet(model, cur.x, cur.y, cur.z);
        opModelRotSet(model, 0.0f, func_80111164_opening(cur.x, cur.z, to.x, to.z), 0.0f);
        D_80117388_opening[no].time = time;
        D_80117388_opening[no].w.fly.phase[0] = p0;
        D_80117388_opening[no].w.fly.phase[1] = p1;
        D_80117388_opening[no].w.fly.phase[2] = p2;
    } else {
        opDemoObjKill(no);
    }
    D_80117388_opening[no].time = time; /* retail stores it again, also after the kill */
}

/* Sends hover object no flying from its model's position to (x, y, z) over time frames. */
void func_80114150_opening(s32 no, f32 x, f32 y, f32 z, s32 time) {
    f32 pos[3];

    opModelPosGet(D_80117388_opening[no].w.fly.model, &pos[0], &pos[1], &pos[2]);
    HuVecCopy3F(&D_80117388_opening[no].w.fly.base, (Vec *)pos);
    HuVecCopyXYZ(&D_80117388_opening[no].w.fly.target, x, y, z);
    D_80117388_opening[no].w.fly.phase[0] = 0.0f;
    D_80117388_opening[no].w.fly.phase[1] = 0.0f;
    D_80117388_opening[no].w.fly.phase[2] = 0.0f;
    D_80117388_opening[no].obj->func = func_80113E8C_opening;
    D_80117388_opening[no].time = 0;
    D_80117388_opening[no].maxTime = time;
}

/* Starts hover object no for model slot model around (x, y, z) at random phases. */
void func_80114250_opening(s32 no, s32 model, f32 x, f32 y, f32 z) {
    opDemoObjCreate(no, func_80113AE8_opening);
    D_80117388_opening[no].time = 0;
    D_80117388_opening[no].maxTime = 20;
    D_80117388_opening[no].w.fly.model = model;
    D_80117388_opening[no].w.fly.phase[0] = D_80117388_opening[no].w.fly.phase[1] =
        D_80117388_opening[no].w.fly.phase[2] = 0.0f;
    D_80117388_opening[no].w.fly.phase[0] = rand8();
    D_80117388_opening[no].w.fly.phase[1] = rand8();
    D_80117388_opening[no].w.fly.base.x = x;
    D_80117388_opening[no].w.fly.base.y = y;
    D_80117388_opening[no].w.fly.base.z = z;
    func_80113AE8_opening(D_80117388_opening[no].obj);
}

/* Draw hook of every wipe: a full-screen rectangle in slot 15's colour while its alpha is not 0. */
void opWipeDraw(Gfx **gfx, s32 arg1, s32 arg2) {
    if (D_80117388_opening[15].w.wipe.a != 0) {
        gSPDisplayList((*gfx)++, D_80114BE8_opening);
        gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor((*gfx)++, 0, 0, D_80117388_opening[15].w.wipe.r, D_80117388_opening[15].w.wipe.g,
                        D_80117388_opening[15].w.wipe.b, D_80117388_opening[15].w.wipe.a);
        gDPFillRectangle((*gfx)++, 0, 0, 320, 240);
    }
}

void opWipeColorSet(s32 no, u8 r, u8 g, u8 b, u8 a) {
    D_80117388_opening[no].w.wipe.r = r;
    D_80117388_opening[no].w.wipe.b = b;
    D_80117388_opening[no].w.wipe.g = g;
    D_80117388_opening[no].w.wipe.a = a;
}

/* Fade in: alpha 255 -> 0 over maxTime frames, then the wipe is freed. Retail passes the stored
   b and g bytes as opWipeColorSet's g and b (the colours used are grey levels). */
void opWipeInMain(omObjData *obj) {
    s8 no = obj->work[0];
    s32 time = D_80117388_opening[no].time;
    s32 maxTime = D_80117388_opening[no].maxTime;
    u8 r = D_80117388_opening[no].w.wipe.r;
    u8 b = D_80117388_opening[no].w.wipe.b;
    u8 g = D_80117388_opening[no].w.wipe.g;
    f32 t;

    if (time >= maxTime) {
        t = 0.0f;
        opWipeKill(no);
    } else {
        t = (1.0f / maxTime) * (maxTime - time);
        D_80117388_opening[no].time++;
    }
    opWipeColorSet(no, r, b, g, t * 255.0f);
}

/* Fade out: alpha 0 -> 255 over maxTime frames, then held. */
void opWipeOutMain(omObjData *obj) {
    s8 no = obj->work[0];
    s32 time = D_80117388_opening[no].time;
    s32 maxTime = D_80117388_opening[no].maxTime;
    u8 r = D_80117388_opening[no].w.wipe.r;
    u8 b = D_80117388_opening[no].w.wipe.b;
    u8 g = D_80117388_opening[no].w.wipe.g;
    f32 t;

    if (time >= maxTime) {
        t = 1.0f;
    } else {
        t = (1.0f / maxTime) * time;
        D_80117388_opening[no].time++;
    }
    opWipeColorSet(no, r, b, g, t * 255.0f);
}

void opWipeKill(s32 no) {
    if (D_80117388_opening[no].obj != NULL) {
        func_8001ACDC_main(D_80117388_opening[no].w.wipe.gfx);
        opDemoObjKill(no);
    }
}

void opWipeInCreate(s32 no, s32 time) {
    opWipeKill(no);
    opDemoObjCreate(no, opWipeInMain);
    D_80117388_opening[no].w.wipe.gfx = func_8001AC8C_main(0, opWipeDraw, 6);
    opWipeColorSet(no, 0, 0, 0, 255);
    D_80117388_opening[no].time = 0;
    D_80117388_opening[no].maxTime = time;
}

void opWipeOutCreate(s32 no, s32 time) {
    opWipeKill(no);
    opDemoObjCreate(no, opWipeOutMain);
    D_80117388_opening[no].w.wipe.gfx = func_8001AC8C_main(0, opWipeDraw, 6);
    opWipeColorSet(no, 0, 0, 0, 255);
    D_80117388_opening[no].time = 0;
    D_80117388_opening[no].maxTime = time;
}

void opWipeWhiteInCreate(s32 no, s32 time) {
    opWipeInCreate(no, time);
    opWipeColorSet(no, 255, 255, 255, 255);
}

void opWipeWhiteOutCreate(s32 no, s32 time) {
    opWipeOutCreate(no, time);
    opWipeColorSet(no, 255, 255, 255, 255);
}

/* Frees texture animation 2 of character chr (14EA0.c's tables). */
void func_801149A4_opening(s32 chr) {
    if (D_800D20B8_main[chr][2] != 0xFF) {
        func_80033354_main(D_800D20B8_main[chr][2]);
        func_80033354_main(D_800D5570_main[chr][2]);
        D_800D20B8_main[chr][2] = 0xFF;
    }
}

void opSleep(s32 time) {
    HuPrcSleep(time);
}

/* The "check the controller" sprite, unless a controller error is already shown. */
void opContErrorCreate(void) {
    if (GWContErrorGet() == 0) {
        D_80117750_opening.anim = func_8000B838_main(0x100005);
        D_80117750_opening.esp = InitEspriteSlot(D_80117750_opening.anim, 0, 1);
        func_8000BBD4_main(D_80117750_opening.esp, 160, 168);
        func_8000BCC8_main(D_80117750_opening.esp, 0);
        func_8000BB94_main(D_80117750_opening.esp);
    }
}

void opContErrorDispOn(void) {
    if (GWContErrorGet() == 0) {
        func_8000BB54_main(D_80117750_opening.esp);
    }
}

void opContErrorDispOff(void) {
    if (GWContErrorGet() == 0) {
        func_8000BB94_main(D_80117750_opening.esp);
    }
}

void opContErrorKill(void) {
    if (GWContErrorGet() == 0) {
        func_8000C184_main(D_80117750_opening.esp);
        HuSprKill(D_80117750_opening.anim);
    }
}

OP_FILE_END()
