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

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80106734_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80106768_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801067D4_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opMotionCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelKillAll);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelIdGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opMotionIdGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelRotSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelPosSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelScaleSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelPosGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelRotGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelScaleGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelDispOff);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opModelDispOn);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opMotionFlagSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opMotionShiftSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80106DD0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opMotionSpeedSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opMotionTimeSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opMotionEndWait);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opMotionEndCheck);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opMotionSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107048_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801070AC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801070D8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107140_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_8010738C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801074D8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107640_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801077E8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801078B4_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107980_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107A4C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107A90_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107B74_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107BD8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107C08_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107C70_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107CA0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107CD0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107D9C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107DD8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107E10_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107E2C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107E80_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107EBC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80107EF4_opening);

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

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80108118_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114CE4_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114D84_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114D90_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114D9C_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/523FD0", D_80114DA8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoEvent);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoEventKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80110B90_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80110B9C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80110C04_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80110D8C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoCharCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoShadowCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoModelKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", opDemoSprKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80110F48_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80110FB0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111028_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_8011105C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111090_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801110AC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801110F0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111164_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_801111AC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_8011124C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111490_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/523FD0", func_80111580_opening);

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
