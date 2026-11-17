#include "common.h"
#include "game/esprite.h"

// m1 lf1
extern u8 D_800D20EC_main; /* save load result: bit per bad box, 8 common record, 0xF all */
extern s16 D_80105F40_slerror[4]; /* sprite file ids */
extern s16 D_80105F48_slerror[4]; /* esprite slots */
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BEAC_main(u16 spriteId, s32 arg1, s32 arg2, s32 arg3);

void func_801059D0_slerror(void) {
    u16 count;
    u16 i;
    u16 slot;
    s16 spr;

    if (D_800D20EC_main & 0x10) {
        omOvlGotoEx(0x58, 0, 0x81);
        omOvlKill();
        HuPrcVSleep();
    }
    func_8005A6B0_main();
    if (D_800D20EC_main == 0xF) {
        count = 1;
        D_80105F48_slerror[0] = slot = InitEspriteSlot(D_80105F40_slerror[0] = func_8000B838_main(0x200000), 0, 1);
        func_8000BBD4_main(slot, 0xA0, 0x78);
        func_8000BC88_main(slot, 0xFFFF);
        func_8000BC48_main(slot, 0x1000);
        func_8000BEAC_main(slot, 0xFF, 0xFF, 0xFF);
        func_8000BB94_main(slot);
    } else {
        count = 0;
        if (D_800D20EC_main & 8) {
            spr = func_8000B838_main(0x200004);
            D_80105F40_slerror[0] = spr;
            D_80105F48_slerror[0] = slot = InitEspriteSlot(spr, 0, 1);
            func_8000BBD4_main(slot, 0xA0, 0x78);
            func_8000BC88_main(slot, 0xFFFF);
            func_8000BC48_main(slot, 0x1000);
            func_8000BEAC_main(slot, 0xFF, 0xFF, 0xFF);
            func_8000BB94_main(slot);
            count = 1;
        }
        if (D_800D20EC_main & 1) {
            spr = func_8000B838_main(0x200001);
            D_80105F40_slerror[count] = spr;
            D_80105F48_slerror[count] = slot = InitEspriteSlot(spr, 0, 1);
            func_8000BBD4_main(slot, 0xA0, 0x78);
            func_8000BC88_main(slot, 0xFFFF);
            func_8000BC48_main(slot, 0x1000);
            func_8000BEAC_main(slot, 0xFF, 0xFF, 0xFF);
            func_8000BB94_main(slot);
            count++;
        }
        if (D_800D20EC_main & 2) {
            spr = func_8000B838_main(0x200002);
            D_80105F40_slerror[count] = spr;
            D_80105F48_slerror[count] = slot = InitEspriteSlot(spr, 0, 1);
            func_8000BBD4_main(slot, 0xA0, 0x78);
            func_8000BC88_main(slot, 0xFFFF);
            func_8000BC48_main(slot, 0x1000);
            func_8000BEAC_main(slot, 0xFF, 0xFF, 0xFF);
            func_8000BB94_main(slot);
            count++;
        }
        if (D_800D20EC_main & 4) {
            spr = func_8000B838_main(0x200003);
            D_80105F40_slerror[count] = spr;
            D_80105F48_slerror[count] = slot = InitEspriteSlot(spr, 0, 1);
            func_8000BBD4_main(slot, 0xA0, 0x78);
            func_8000BC88_main(slot, 0xFFFF);
            func_8000BC48_main(slot, 0x1000);
            func_8000BEAC_main(slot, 0xFF, 0xFF, 0xFF);
            func_8000BB94_main(slot);
            count++;
        }
    }
    for (i = 0; i < count; i++) {
        func_8000BB54_main(D_80105F48_slerror[i]);
        WipeCreateIn(0xB, 8);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        do {
            HuPrcVSleep();
        } while ((D_800D5558_main[0] | D_800D5558_main[1] | D_800D5558_main[2] | D_800D5558_main[3]) == 0);
        WipeCreateOut(0xB, 8);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        func_8000BB94_main(D_80105F48_slerror[i]);
    }
    for (i = 0; i < count; i++) {
        func_8000C184_main(D_80105F48_slerror[i]);
        HuSprKill(D_80105F40_slerror[i]);
    }
    func_8005F524_main();
    omOvlGotoEx(0x58, 0, 0x81);
    omOvlKill();
    HuPrcVSleep();
}

void func_80105E9C_slerror(void) {
    omInitObjMan(10, 10);
    func_8004A208_main();
    omAddPrcObj(func_801059D0_slerror, 0x1005, 0, 0);
}

void func_80105EDC_slerror(void) {
    omInitObjMan(10, 10);
    func_8004A208_main();
    omAddPrcObj(func_801059D0_slerror, 0x1005, 0, 0);
}
