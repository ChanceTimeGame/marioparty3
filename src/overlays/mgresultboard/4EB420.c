#include "common.h"
#include "game/hmfman.h"
#include "mgresultboard.h"

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4EB420", func_8010A000_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4EB420", func_8010A334_mgresultboard);

void func_8010A350_mgresultboard(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4EB420", func_8010A358_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4EB420", func_8010A3E4_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4EB420", func_8010A454_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4EB420", func_8010A4A0_mgresultboard);

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
