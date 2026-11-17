#include "common.h"
#include "../ovl_81_name/ovl_81.h"

// duel k1
/* duelresult2 (0x63): Duel Mode's end-of-game records screen. */

/* Texture-animation slot (14EA0.c TexAnimSlot). */
typedef struct OtTexAnimSlot {
    /* 0x00 */ s16 frame;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ char unk08[2];
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B;
} OtTexAnimSlot; /* size = 0xC */

extern u16 D_800D530C_main;
extern OtTexAnimSlot *D_800D1714_main;
void func_80032FC0_main(s16, u8, u8);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
s16 func_800329B4_main(void *);
s32 func_800E1854_minigame(s32 id);

extern s16 D_80108E3C_duelresult2;
extern s16 D_80108E3E_duelresult2; /* texture-animation slot, 0xFF none */

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801059A0_duelresult2);

s16 func_80105A8C_duelresult2(s16 model, s32 file, char *name) {
    void *data;
    s32 slot;
    u16 ret;

    data = DataRead(file);
    slot = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_80108E3C_duelresult2 = slot;
    func_80032FC0_main(slot, 1, 1);
    DataClose(data);
    ret = D_800D1714_main[(s16)slot].frame;
    D_80108E3E_duelresult2 = func_80032694_main(HmfModelData[model].hmf, slot, 0, name);
    func_8001C448_main(model);
    return ret;
}

void func_80105B98_duelresult2(s16 model, s16 frame) {
    OtTexAnimSlot *p;

    if (D_80108E3E_duelresult2 != 0xFF) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
            return;
        }
        func_80033970_main(HmfModelData[model].hmf);
        p = &D_800D1714_main[D_80108E3E_duelresult2];
        p->frame = frame;
        p->unk04 = 0;
        p->unk0A = 0;
        p->unk06 = 0;
        p->unk02 = 0;
    }
}

s16 func_80105C68_duelresult2(s32 file) {
    void *data;
    s16 sprite;

    data = DataRead(file);
    sprite = func_800329B4_main(data);
    DataClose(data);
    return sprite;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80105CB0_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106848_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801068BC_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106974_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106A2C_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108CC8_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80106F7C_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D08_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D28_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D48_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80107454_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80107FEC_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_8010809C_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108240_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801083FC_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801084F4_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108B38_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108B7C_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108BA0_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108BCC_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80108BF8_duelresult2);

void func_80108C28_duelresult2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D80_duelresult2);
