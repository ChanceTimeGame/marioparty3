#include "common.h"
#include "msetup.h"

/* fork B: main declarations without a shared prototype */
typedef struct MsTexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} MsTexAnimSlot; /* size = 0xC (MP2 TexAnimSlot) */
extern MsTexAnimSlot *D_800D1714_main;
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
s16 func_800329B4_main(void *);


/* Matches with 506F20.c in the Makefile's W2DC_BLANKSTRIP list (only residue: KMC as adds a nop
   before each mul.s after the sindf/cosdf calls). */
#ifdef NON_MATCHING
void func_8010ACC0_msetup(s16 model, s16 shadow, s32 arg2) {
    f32 angle;
    f32 dAngle;
    f32 t;
    f32 dt;
    f32 y;
    f32 dy;
    f32 x;
    f32 z;
    f32 f;
    s32 i;

    angle = 330.0f;
    dAngle = -4.0f;
    t = 0.0f;
    dt = 5.625f;
    y = 260.0f;
    dy = -18.571428f;
    x = -86.0f;
    z = 617.0f;
    for (i = 0; i < 15; i++) {
        Hu3DModelPosSet(model, x, y, z);
        Hu3DModelPosSet(shadow, x, 0.0f, z);
        f = y + 100.0f;
        func_8010E044_msetup(D_80119AF0_msetup, 0, 100, x, f, z);
        func_8010E044_msetup(D_80119AF0_msetup, 1, 100, x, f, z);
        f = (1.0 - y * 0.009) * 0.6;
        if (f < 0.0f) {
            f = 0.0f;
        }
        Hu3DModelScaleSet(shadow, f, 1.0f, f);
        angle += dAngle;
        y += dy;
        t += dt;
        f = 500.0f - sindf(t) * 500.0f;
        x = f * sindf(angle) + 194.0f;
        z = f * cosdf(angle) + 197.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, 194.0f, 0.0f, 197.0f);
    Hu3DModelPosSet(shadow, 194.0f, 0.0f, 197.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010ACC0_msetup);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010AF40_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B1F4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B388_msetup);

void func_8010B4B8_msetup(s16 model, s16 *slot, s16 frame) {
    MsTexAnimSlot *anim;

    if (*slot >= 0) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            anim = &D_800D1714_main[*slot];
            anim->unk_00 = frame;
            anim->unk_04 = 0;
            anim->unk_0A = 0;
            anim->unk_06 = 0;
            anim->unk_02 = 0;
        }
    }
}

s16 func_8010B588_msetup(s32 file) {
    void *data;
    s16 ret;

    data = DataRead(file);
    ret = func_800329B4_main(data);
    DataClose(data);
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B5D0_msetup);

void func_8010B82C_msetup(s32 mes) {
    func_8005B43C_main(D_8011A890_msetup, mes, -1, -1);
}

s32 func_8010B858_msetup(void) {
    while (TRUE) {
        if (func_8005E0C0_main(D_8011A890_msetup) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    if (D_800CC69C_main[D_8011A890_msetup].unk_30 != 0) {
        return func_8005E1D8_main(D_8011A890_msetup, 0, 0);
    } else {
        return 0;
    }
}

s32 func_8010B8E0_msetup(void) {
    while (TRUE) {
        if (func_8005E0C0_main(D_8011A890_msetup) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    if (D_800CC69C_main[D_8011A890_msetup].unk_30 != 0) {
        return func_8005E1D8_main(D_8011A890_msetup, 1, 0);
    } else {
        return 0;
    }
}

void func_8010B968_msetup(u32 mes, s8 arg1) {
    func_8005B6BC_main(D_8011A890_msetup, mes, arg1);
}

void func_8010B998_msetup(void) {
    func_8005D294_main(D_8011A890_msetup);
}

void func_8010B9B8_msetup(s32 mask, s32 value) {
    while ((~func_8005B68C_main(D_8011A890_msetup) & mask) == value) {
        HuPrcVSleep();
    }
}

void func_8010BA10_msetup(s32 arg0, s32 arg1) {
    func_8005B63C_main(D_8011A890_msetup, arg0, arg1);
}

s16 func_8010BA3C_msetup(void) {
    /* TextWindow 0xA8 (inside window.h pad86) */
    return *(s16 *)&D_800CC69C_main[D_8011A890_msetup].pad86[0x22];
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BA6C_msetup);

void func_8010BBF4_msetup(s16 arg0) {
    func_8010BA6C_msetup(0, arg0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BC18_msetup);

void func_8010BE8C_msetup(s16 arg0) {
    func_8010BC18_msetup(0, arg0);
}

s16 func_8010BEB0_msetup(s16 player, s16 value) {
    s16 old = D_8011A9F2_msetup[player][0];

    if (value >= 0) {
        D_8011A9F2_msetup[player][0] = value;
    }
    return old;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BEF8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CAF0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CC70_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CD14_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CE8C_msetup);

void func_8010D060_msetup(HmfData *hmf, s16 idx) {
    if ((s8)hmf->unk84[idx].unk3 != -1) {
        hmf->unk84[idx].unk9 |= 0x80;
    }
}

void func_8010D094_msetup(HmfData *hmf, s16 idx) {
    if ((s8)hmf->unk84[idx].unk3 != -1) {
        hmf->unk84[idx].unk9 &= 0x7F;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D0C8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D234_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D4DC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D5EC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D684_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D6D0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010DAC4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010DDD8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010DE38_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E00C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E044_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E09C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E21C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E32C_msetup);


void func_8010E4BC_msetup(MsLift *lifts, s32 count, f32 rotY) {
    func_8010E32C_msetup(lifts, count, rotY, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E4D8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E52C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E8C8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010EB94_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F2BC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F2F4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F320_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F33C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F43C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F4E0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F87C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8011035C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80110954_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80111650_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6E4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6FC_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A708_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A714_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A720_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A72C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A738_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A744_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A74C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A754_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A75C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A764_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A76C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A774_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A77C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A784_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A78C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A794_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A79C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7A4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7AC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80112804_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80112E08_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80112F5C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801132C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801138F8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113DEC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113E20_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113E54_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113E88_msetup);

s32 func_80113ED4_msetup(MsSetupWork *arg0) {
#define MODE_PARTY 0
#define MODE_DUEL 1
#define FLAG_WALUIGIS_ISLAND 0x31
#define FLAG_BACKTRACK 0x30
    MsLift sp20[2];
    s16 unk_68;
    s32 *mainFSArray;
    s32 boardCountMaxCopy;
    f32 var_f20;
    void *temp_v0_4;
    omObjData *temp_s5;
    s16 prevBoardIndex;
    s16 backgroundEspriteSlot;
    s16 var_s6;
    s32 pad;
    s32 var_fp;
    s32 boardCountMax;
    s32 *boardDescriptionId;
    s16 curBoardIndex;
    s16 temp;
    s32 i;
    f32 tempFloat;

    boardDescriptionId = NULL;
    mainFSArray = NULL;
    curBoardIndex = D_8011AA45_msetup;
    arg0->unk4 = 0;
    backgroundEspriteSlot = -1;
    var_s6 = -1;
    boardCountMax = 6;
    var_fp = 70;
    tempFloat = 1.0f;

    switch (D_8011A938_msetup) { // current mode
        case MODE_PARTY:
            boardDescriptionId = D_80119EC4_msetup;
            mainFSArray = D_80119E94_msetup; // party mode board backgrounds
            tempFloat = 1.0f;
            var_fp = 74;
            boardCountMax = 5;
            if (_CheckFlag(FLAG_WALUIGIS_ISLAND) != 0) {
                boardCountMax = 6;
            }
            break;
        case MODE_DUEL:
            boardDescriptionId = D_80119EE0_msetup;
            mainFSArray = D_80119EAC_msetup; // duel mode board backgrounds
            var_fp = 74;
            boardCountMax = 5;
            if (_CheckFlag(FLAG_BACKTRACK) != 0) {
                boardCountMax = 6;
            }
            break;
    }

    func_8010B998_msetup();
    func_8010E4BC_msetup(sp20, 2, 0.0f);
    func_8010E4D8_msetup(sp20, 2);
    temp = sp20[0].model;
    temp_s5 = func_8010DE38_msetup(0x40, 0x100, 0x48);
    func_8010B82C_msetup(boardDescriptionId[6]);
    func_8010B858_msetup();
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(sp20, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    func_8001C258_main(sp20[1].model, 4, 4);

    for (var_f20 = 0.0f; var_f20 < 180.0f; var_f20 += (180.0f / 7.0f)) {
        Hu3DModelRotSet(temp, 0, var_f20, 0);
        HuPrcVSleep();
    }

    Hu3DModelRotSet(temp, 0, 180.0f, 0);
    temp_s5->work[0] = 1;
    temp_s5->work[1] = 36;

    for (var_f20 = 1.0f; var_f20 < 2.5f; var_f20 += (3.0f / 14.0f)) {
        Hu3DModelScaleSet(temp, var_f20, var_f20, var_f20);
        HuPrcVSleep();
    }

    Hu3DModelScaleSet(temp, 2.5f, 2.5f, 2.5f);
    prevBoardIndex = -1;
    pad = func_8010D684_msetup(D_8011A948_msetup, &unk_68);
    boardCountMaxCopy = boardCountMax;
    while (1) {
        pad = func_8010D684_msetup(D_8011A948_msetup, &unk_68);
        if (pad & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        if (pad & B_BUTTON) {
            HuAudFXPlay(4);
            curBoardIndex = -1;
            break;
        }
        if (pad & (U_JPAD | R_JPAD)) {
            curBoardIndex++;
            curBoardIndex = (boardCountMaxCopy <= curBoardIndex) ? 0 : curBoardIndex;
            HuAudFXPlay(1);
            temp_s5->work[0] = 4;
        } else {
            if (pad & (D_JPAD | L_JPAD)) {
                if (--curBoardIndex < 0) {
                    curBoardIndex = boardCountMax - 1;
                }
                HuAudFXPlay(1);
                temp_s5->work[0] = 3;
            }
        }
        // check if background image should update
        if (prevBoardIndex != curBoardIndex) {
            if (backgroundEspriteSlot >= 0) {
                for (i = 255; i > 0; i -= (255 / 5)) {
                    func_8000BBFC_main(backgroundEspriteSlot, i);
                    HuPrcVSleep();
                }
                func_8000C184_main(backgroundEspriteSlot);
                HuSprKill(var_s6);
            }
            temp_v0_4 = DataReadTemp(mainFSArray[curBoardIndex]);
            var_s6 = func_80055810_main(temp_v0_4);
            DataCloseTemp(temp_v0_4);
            backgroundEspriteSlot = InitEspriteSlot(var_s6, 0, 1);
            func_8000BC48_main(backgroundEspriteSlot, 0x1000);
            func_8000BCC8_main(backgroundEspriteSlot, 1);
            func_8000BBD4_main(backgroundEspriteSlot, 0xA0, var_fp);
            func_8000BE5C_main(backgroundEspriteSlot, tempFloat, tempFloat);
            for (i = 0; i < 255; i += (255 / 5)) {
                func_8000BBFC_main(backgroundEspriteSlot, i);
                HuPrcVSleep();
            }
            func_8000BBFC_main(backgroundEspriteSlot, 0xFF);
            prevBoardIndex = curBoardIndex;
            func_8010B82C_msetup(boardDescriptionId[curBoardIndex]);
        }
        HuPrcVSleep();
    }

    arg0->unk4 = curBoardIndex;
    if (curBoardIndex >= 0) {
        D_8011AA45_msetup = curBoardIndex;
    }

    temp_s5->work[0] = 2;
    temp_s5->work[1] = 17;

    for (i = 255; i > 0; i -= (255 / 5)) {
        func_8000BBFC_main(backgroundEspriteSlot, i);
        HuPrcVSleep();
    }

    func_8000BBFC_main(backgroundEspriteSlot, 0);

    for (var_f20 = 2.5f; var_f20 > 1.0f; var_f20 += -(3.0f / 14.0f)) {
        Hu3DModelScaleSet(temp, var_f20, var_f20, var_f20);
        HuPrcVSleep();
    }

    Hu3DModelScaleSet(temp, 1.0f, 1.0f, 1.0f);

    for (var_f20 = 180.0f; var_f20 < 360.0f; var_f20 += (180.0f / 7.0f)) {
        Hu3DModelRotSet(temp, 0, var_f20, 0);
        HuPrcVSleep();
    }

    Hu3DModelRotSet(temp, 0, 0.0f, 0);
    func_8001C258_main(sp20[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(sp20, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);

    if (curBoardIndex >= 0) {
        func_8010F320_msetup(D_80119420_msetup, 0, sp20[0].model, -1);
        func_8010F320_msetup(D_80119420_msetup, 2, backgroundEspriteSlot, var_s6);
        func_8001ACDC_main(sp20[1].model);
    } else {
        for (i = 0; i < 2; i++) {
            func_8001ACDC_main(sp20[i].model);
        }
        func_8000C184_main(backgroundEspriteSlot);
        HuSprKill(var_s6);
    }
    func_8010DDD8_msetup(temp_s5);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801145D0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80114AA0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801150A0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801152C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801157B8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115A9C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115E78_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7E0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7E8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7F8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A800_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115EE0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801167B8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80116FE0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117818_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117820_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117910_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117A3C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80118D48_msetup);
