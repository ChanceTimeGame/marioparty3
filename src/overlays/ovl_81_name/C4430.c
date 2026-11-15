#include "common.h"
#include "ovl_81.h"

void func_8004A9DC_main(s8);

// duel n2: fade the music volume up from 0x60 to 0x7F
void func_800DC660_name_81(void) {
    f32 vol = 96.0f;
    f32 step;
    f32 max;

    func_8004A9DC_main(0x60);
    step = 1.9375f;
    max = 127.0f;
    do {
        HuPrcVSleep();
        vol += step;
        if (vol >= max) {
            vol = max;
        }
        func_8004A9DC_main(vol);
    } while (vol < max);
    omDelPrcObj(NULL);
}

// duel n2: fade the music volume down from 0x7F to 0x60
void func_800DC700_name_81(void) {
    f32 vol = 127.0f;
    f32 step;
    f32 min;

    func_8004A9DC_main(0x7F);
    step = 1.9375f;
    min = 96.0f;
    do {
        HuPrcVSleep();
        vol -= step;
        if (vol <= min) {
            vol = min;
        }
        func_8004A9DC_main(vol);
    } while (min < vol);
    omDelPrcObj(NULL);
}

void func_800DC7A0_name_81(void) {
    omAddPrcObj(func_800DC700_name_81, 0xEFFF, 0, 0);
}

void func_800DC7CC_name_81(void) {
    omAddPrcObj(func_800DC660_name_81, 0xEFFF, 0, 0);
}
