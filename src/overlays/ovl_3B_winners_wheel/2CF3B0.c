#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// winners_wheel: Winner's Wheel (1 player: stop the wheel to win its prize)

/* omObjData::data of the wheel host (D_8010A498) */
typedef struct WwHost {
    /* 0x00 */ s32 unk00; /* flags */
    /* 0x04 */ s32 unk04;
} WwHost; /* size 8 */

// main
void func_80021BE0_main(s32* arg0, s32 n);
void func_8004B760_main(s32 prio, s32 sprId, void* draw, f32 fov, Vec* eye, Vec* at);
void func_8004BCE4_main(void* work);
void func_8004AD70_main(void);

typedef struct WwEsprite {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[0x1E];
} WwEsprite; /* size 0x24 */

extern WwEsprite* D_800CD1DC_main;
extern D_800CCF58_main_Struct* D_800CCF58_main;
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[];

// minigame
u16 func_800E6E9C_minigame(void);
extern s32 D_800EBEB0_minigame[];
extern s32 D_800EBE24_minigame;

// this overlay
void func_801059A0_winners_wheel(void);
void func_80105AB0_winners_wheel(void);
void func_80105BA8_winners_wheel(void);
void func_80105C5C_winners_wheel(omObjData* obj);
void func_80105E78_winners_wheel(s32 arg0);
void func_80105F18_winners_wheel(void);
void func_80105F60_winners_wheel(void);
void func_80105F94_winners_wheel(void);
void func_80105FB0_winners_wheel(omObjData* obj);
void func_80105FE4_winners_wheel(omObjData* obj);
void func_801063B0_winners_wheel(void);
void func_80106514_winners_wheel(void);
void func_80106718_winners_wheel(void);
void func_80106734_winners_wheel(void);
void func_80106750_winners_wheel(void);
void func_8010677C_winners_wheel(void);
void func_80106910_winners_wheel(void);
void func_80106D2C_winners_wheel(void);
void func_80106EB0_winners_wheel(s32 arg0);
void func_80106F54_winners_wheel(void);
void func_8010701C_winners_wheel(void);
void func_801070CC_winners_wheel(void);
void func_801075D4_winners_wheel(void);
void func_801077F4_winners_wheel(void);
void func_80107820_winners_wheel(void);
void func_801078D8_winners_wheel(void);
void func_80107B0C_winners_wheel(void);
void func_80107BE0_winners_wheel(void);
void func_80107CB4_winners_wheel(void);
void func_80107D50_winners_wheel(void);
void func_80107F4C_winners_wheel(void);
void func_8010842C_winners_wheel(void);
void func_80108458_winners_wheel(void);
void func_801089C8_winners_wheel(void);
void func_801089F4_winners_wheel(void);
void func_80108E80_winners_wheel(void);
void func_80108F04_winners_wheel(s32 arg0);
void func_80109050_winners_wheel(void);
void func_8010907C_winners_wheel(void);
void func_80109104_winners_wheel(void);
void func_80109130_winners_wheel(void);
void func_80109388_winners_wheel(void);
void func_80109454_winners_wheel(void);
void func_801095E4_winners_wheel(void);
void func_8010985C_winners_wheel(void);
void func_80109A18_winners_wheel(void);
void func_80109B90_winners_wheel(void);
void func_80109BAC_winners_wheel(void);
void func_80109BF0_winners_wheel(void);
void func_80109C1C_winners_wheel(void);
void func_80109D44_winners_wheel(void);
void func_80109E90_winners_wheel(void);
void func_80109F80_winners_wheel(void);
void func_80109FAC_winners_wheel(void);
void func_8010A190_winners_wheel(void);

/* .bss (ovl_3B_bss) */
extern u8 D_8010A464_winners_wheel; /* state */
extern s16 D_8010A466_winners_wheel;
extern s32 D_8010A468_winners_wheel[6]; /* prize on each wheel slot (0x11: none) */
extern s32 D_8010A480_winners_wheel;    /* slot the wheel stopped on */
extern s32 D_8010A48C_winners_wheel;    /* the playing player */
extern s32 D_8010A490_winners_wheel;    /* CPU timer */
extern omObjData* D_8010A498_winners_wheel;

/* .data */
extern D_80111B50_vine_with_me_Struct D_8010A260_winners_wheel;


void func_801059A0_winners_wheel(void) {
    omInitObjMan(30, 10);
    Hu3DAnimInit(16);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    func_8010A190_winners_wheel();
    func_8004A208_main();
    func_8001F38C_main(0, 0, 0);
    func_800E5EA0_minigame(&D_8010A260_winners_wheel);
    WipeCreateIn(0xFF, 16);
    func_80105AB0_winners_wheel();
    func_80105BA8_winners_wheel();
    func_801063B0_winners_wheel();
    func_80106910_winners_wheel();
    func_801070CC_winners_wheel();
    func_801078D8_winners_wheel();
    func_80107D50_winners_wheel();
    func_80109454_winners_wheel();
    func_80109D44_winners_wheel();
    D_8010A466_winners_wheel = 0;
    CZoom = 1800.0f;
    D_800EBE24_minigame = 0;
    D_8010A464_winners_wheel = 0;
    omAddObj(0x50, 0, 0, -1, func_80105FE4_winners_wheel);
    HuAudSeqPlay(0x44);
}

/* The background sprite. */
void func_80105AB0_winners_wheel(void) {
    Vec eye;
    Vec at;
    s16 sprId;

    sprId = InitEspriteSlot(func_8000B838_main(0x5C0006), 0, 1);
    func_8000BB94_main(sprId);
    eye.x = 0.0f;
    eye.y = 200.0f;
    eye.z = 2625.0f;
    at.x = -0.9f;
    at.y = -21.9f;
    at.z = -253.6f;
    func_8004B760_main(100, D_800CD1DC_main[sprId].unk04, func_8004BCE4_main, 11.1f, &eye, &at);
}

/* The wheel host. */
void func_80105BA8_winners_wheel(void) {
    omObjData* obj;
    WwHost* work;

    obj = omAddObj(10, 1, 0, -1, func_80105C5C_winners_wheel);
    D_8010A498_winners_wheel = obj;
    obj->data = work = HuMemAllocTag(sizeof(WwHost), 31000);
    obj->model[0] = func_8000B108_main(0x5C0000, 0x699);
    func_8001C814_main(obj->model[0], 1, 1);
    omSetTra(obj, -175.0f, -400.0f, 400.0f);
    obj->func = func_80105C5C_winners_wheel;
    work->unk00 = 0;
    work->unk04 = 0;
}

void func_80105C5C_winners_wheel(omObjData* obj) {
    WwHost* work = obj->data;

    if (work->unk00 & 1) {
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
            work->unk00 &= ~1;
            func_80105F18_winners_wheel();
        }
    }
    if ((work->unk00 & 2) && HmfModelData[obj->model[0]].unk40 <= 0.0f) {
        work->unk00 &= ~2;
        if (work->unk04 != 0) {
            func_80105F60_winners_wheel();
        }
    }
    if (work->unk00 & 4) {
        obj->trans.y -= 2.0f;
        if (obj->trans.y <= -400.0f) {
            work->unk00 &= ~4;
            func_8001C258_main(obj->model[0], 4, 4);
        }
    }
    if (work->unk00 & 8) {
        obj->trans.y += 4.0f;
        if (obj->trans.y >= -350.0f && obj->trans.y < -346.0f) {
            HuAudFXPlay(0x4CA);
        }
        if (obj->trans.y >= -200.0f) {
            obj->trans.y = -200.0f;
            work->unk00 &= ~8;
        }
    }
}

void func_80105E78_winners_wheel(s32 arg0) {
    WwHost* work = D_8010A498_winners_wheel->data;

    func_8001C814_main(D_8010A498_winners_wheel->model[0], 4, 0);
    func_8001C814_main(D_8010A498_winners_wheel->model[0], 1, 0);
    work->unk00 |= 1;
    work->unk04 = arg0;
    if (arg0 == 0) {
        func_80106718_winners_wheel();
        func_80108E80_winners_wheel();
    } else {
        func_80106734_winners_wheel();
        func_80108F04_winners_wheel(arg0);
    }
}

void func_80105F18_winners_wheel(void) {
    WwHost* work = D_8010A498_winners_wheel->data;

    func_8001C814_main(D_8010A498_winners_wheel->model[0], 4, 4);
    work->unk00 |= 2;
}

void func_80105F60_winners_wheel(void) {
    WwHost* work = D_8010A498_winners_wheel->data;

    work->unk00 |= 4;
    HuAudFXPlay(0x4CA);
}

void func_80105F94_winners_wheel(void) {
    WwHost* work = D_8010A498_winners_wheel->data;

    work->unk00 |= 8;
}

void func_80105FB0_winners_wheel(omObjData* obj) {
    if (WipeStatGet() == 0) {
        func_8005F524_main();
        omOvlReturnEx(1);
    }
}

void func_80105FE4_winners_wheel(omObjData* obj) {
    /* retail passes obj to the argument-less func_800E6F40_minigame */
    u8 (*getStat)(omObjData*) = (void*)func_800E6F40_minigame;

    if (D_800D530C_main != 0) {
        func_8004AD70_main();
        HuAudSeqFadeOut(30);
        WipeCreateOut(0, 20);
    }
    switch (getStat(obj)) {
        case 0:
            if (func_800E6E9C_minigame() == 15) {
                func_8010842C_winners_wheel();
            }
            break;
        case 2:
            if (func_800E6E9C_minigame() == 0) {
                omAddPrcObj(func_80109388_winners_wheel, 0x50, 0, 0);
                D_8010A464_winners_wheel = 1;
            }
            if (D_8010A464_winners_wheel == 1) {
                if (!(GwPlayer[D_8010A48C_winners_wheel].stat & 1)) {
                    if (D_800D5558_main[GwPlayer[D_8010A48C_winners_wheel].pad] == 0x8000) {
                        goto stop;
                    }
                } else if (--D_8010A490_winners_wheel == 0) {
                stop:
                    func_80106EB0_winners_wheel(1);
                    D_8010A464_winners_wheel = 3;
                }
            }
            if (D_8010A464_winners_wheel == 2) {
                func_80106EB0_winners_wheel(2);
                D_8010A464_winners_wheel = 0;
            }
            break;
        case 3:
            if (func_800E6E9C_minigame() == 1) {
                func_80109050_winners_wheel();
                func_801077F4_winners_wheel();
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                    func_8010985C_winners_wheel();
                }
            }
            if (D_8010A464_winners_wheel == 4) {
                func_80106750_winners_wheel();
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] == 0x11) {
                    func_80109F80_winners_wheel();
                } else {
                    func_80109BF0_winners_wheel();
                    func_80109BAC_winners_wheel();
                }
                D_8010A464_winners_wheel = 0;
            }
            if (D_8010A464_winners_wheel == 5) {
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                    func_801089C8_winners_wheel();
                }
                D_8010A464_winners_wheel = 0;
            }
            if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                D_8010A260_winners_wheel.unk06 = 5;
            } else {
                D_8010A260_winners_wheel.unk06 = 7;
            }
            break;
        case 4:
            if (func_800E6E9C_minigame() == 1) {
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                    func_80106F54_winners_wheel();
                    func_80107BE0_winners_wheel();
                } else {
                    func_8010701C_winners_wheel();
                    func_80107CB4_winners_wheel();
                    HuAudFXPlay(0x4CF);
                }
            }
            break;
        case 5:
            if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                GwPlayer[D_8010A48C_winners_wheel].bonusCoin = D_8010A468_winners_wheel[D_8010A480_winners_wheel];
            } else {
                GwPlayer[D_8010A48C_winners_wheel].bonusCoin = -1;
            }
            WipeCreateOut(0, 20);
            obj->func = func_80105FB0_winners_wheel;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801063B0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106514_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106718_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106734_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106750_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010677C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106910_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106D2C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106EB0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80106F54_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010701C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801070CC_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801075D4_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801077F4_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107820_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801078D8_winners_wheel);

void func_80107B04_winners_wheel(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107B0C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107BE0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107CB4_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107D50_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107F4C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010842C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80108458_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801089C8_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801089F4_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80108E80_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80108F04_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109050_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010907C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109104_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109130_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109388_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109454_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_801095E4_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010985C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109A18_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109B90_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109BAC_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109BF0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109C1C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109D44_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109E90_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109F80_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109FAC_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010A190_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A2E8_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A308_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A328_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A3A8_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A3C8_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A3E8_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A408_winners_wheel);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", D_8010A420_winners_wheel);
