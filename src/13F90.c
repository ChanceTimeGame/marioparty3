#include "common.h"

/* A model's vertex-scatter effect (HmfModel.unkBC; hmfman.h's HmfModelData_UnkBC_Struct). */
typedef struct HmfFxWork {
    /* 0x00 */ s16 unk00; /* motion, -1 none */
    /* 0x02 */ s16 unk02;
    /* 0x04 */ u16 unk04; /* flags */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ char unk10[8];
    /* 0x18 */ void (*unk18)(s16);
} HmfFxWork;

#define FXWORK(model) ((HmfFxWork*) HmfModelData[model].unkBC)

INCLUDE_ASM("asm/nonmatchings/13F90", func_80013390_main);

void func_800138EC_main(s16 model, u16 mask, u16 flags) {
    FXWORK(model)->unk04 = (FXWORK(model)->unk04 & ~mask) | flags;
}

s16 func_80013928_main(s16 model) {
    return FXWORK(model)->unk04;
}

void func_80013954_main(s16 model, s16 value) {
    FXWORK(model)->unk02 = value;
}

s16 func_80013980_main(s16 model) {
    return FXWORK(model)->unk02;
}

INCLUDE_ASM("asm/nonmatchings/13F90", func_800139AC_main);

void func_80013D44_main(void) {
}

INCLUDE_ASM("asm/nonmatchings/13F90", func_80013D4C_main);

INCLUDE_ASM("asm/nonmatchings/13F90", func_80013FB4_main);
