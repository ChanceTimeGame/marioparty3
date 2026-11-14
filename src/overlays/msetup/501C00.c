#include "common.h"
#include "msetup.h"

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801059A0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80105C4C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80105DB4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80105E90_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80105F7C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106030_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010610C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801061E0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106208_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106260_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106320_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801068F4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106DF8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106FC0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801070FC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107428_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801077E0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107840_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107964_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107A58_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107B8C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107CF4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107D84_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107E48_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107ECC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107F88_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107FB4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108464_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801084C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801085D4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801086C8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801087F4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801088A8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108938_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801089FC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108AB8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108F74_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109218_msetup);

void func_80109868_msetup(void) {
    s16 sp10[2];
    Process *proc;
    s32 i;
    s32 loop;

    D_8011A880_msetup = 2;
    func_80108F74_msetup();
    D_8011AA30_msetup[0x15] = GwSystem.current_board_index;
    D_8011AA30_msetup[0x12] = GwSystem.total_turns;
    D_8011AA30_msetup[0x17] = _CheckFlag(0x29);
    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011AA34_msetup[i] = GwPlayer[i].chr;
        D_8011AA3C_msetup[i] = GwPlayer[i].star;
        D_8011AA30_msetup[i] = GwPlayer[i].pad;
        if (GwPlayer[i].stat & 1) {
            D_8011AA38_msetup[i] = GwPlayer[i].cpu_difficulty;
        } else {
            D_8011AA38_msetup[i] = 0xFF;
        }
    }
    D_8011AA30_msetup[0x10] = 1;
    D_8011AA30_msetup[0x11] = 1;
    Hu3DModelPosSet(func_8000B108_main(D_80119428_msetup, 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, 6);
    D_8011A886_msetup[0] = -1;
    proc->user_data = D_8011A886_msetup - 2;
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(sp10, 0, 4);
    proc->user_data = sp10;
    func_80106260_msetup(&D_80119580_msetup);
    func_8010BBF4_msetup(D_8011A880_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    sp10[0] = 1;
    HuAudFXPlay(0x2DB);
    D_8011A9F2_msetup[0][0] = 1;
    while (sp10[0] == 1) {
        HuPrcVSleep();
    }
    D_8011A990_msetup[0] = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    func_8010B968_msetup(D_8011AA30_msetup[4] + 0x1C00, 0);
    func_8010B82C_msetup(0x2900);
    func_8010B858_msetup();
    func_8010B82C_msetup(D_801194C0_msetup[D_8011AA30_msetup[0x15]]);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x2907);
    func_8010B858_msetup();
    D_8011A882_msetup.state = 0xC;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    func_8010B82C_msetup(0x2908);
    func_8010B858_msetup();
    HuAudFXPlay(0x2DB);
    for (i = 1; i < D_8011A880_msetup; i++) {
        D_8011A9F2_msetup[i][0] = 1;
    }
    for (i = 7; i != 0; i--) {
        HuPrcVSleep();
    }
    D_8011A9F2_msetup[0][0] = 0x11;
    while (D_8011A9F2_msetup[D_8011A880_msetup - 1][0] != 0) {
        HuPrcVSleep();
    }
    if (D_8011AA34_msetup[1] != 1) {
        func_8010B82C_msetup(D_801194D8_msetup[D_8011AA34_msetup[1]]);
    } else {
        func_8010B82C_msetup(D_801194F8_msetup[D_8011AA45_msetup]);
    }
    func_8010B858_msetup();
    func_8010B82C_msetup(0x2914);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x2915);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x2916);
    func_8010B858_msetup();
    func_8010B82C_msetup(D_8011AA47_msetup != 0 ? 0x291A : 0x2919);
    func_8010B858_msetup();
    loop = TRUE;
    do {
        func_8010B82C_msetup(0x2917);
        if (func_8010B858_msetup() == 0) {
            func_8010B82C_msetup(0x2918);
            func_8010B858_msetup();
            HuAudFXPlay(0x2A6);
            D_8011A990_msetup[0] = 0;
            for (i = 0; i < D_8011A880_msetup; i++) {
                D_8011A9F2_msetup[i][0] = 0x10;
            }
            HuAudSeqFadeOut(0x186);
            D_80119412_msetup = 1;
            HuAudFXPlay(0x2DF);
            func_801068F4_msetup(D_801197BC_msetup, 22.0f, NULL);
            _ClearFlag(0);
            _ClearFlag(0x28);
            if (D_8011AA47_msetup != 0) {
                _SetFlag(0x20);
            } else {
                _ClearFlag(0x20);
            }
            GwSystem.playMode = 6;
            D_8011A944_msetup = 3;
            D_8011AA4C_msetup[0] = 0x5A;
            D_8011A946_msetup = 0;
            omOvlHisChg(0, 0x7D, 0, 0x4090);
            omovlhisidx++;
            loop = FALSE;
        } else {
            func_8010B82C_msetup(0x1501);
            if (func_8010B858_msetup() == 0) {
                loop = FALSE;
                D_8011A990_msetup[0] = 0;
                D_80119410_msetup = 0x4B;
                HuAudFXPlay(0x2EC);
                func_801068F4_msetup(D_801196C0_msetup, 25.0f, NULL);
            }
        }
    } while (loop);
    D_80119410_msetup = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s16 func_80109EA0_msetup(s16 arg0) {
    s16 ret;

    if (D_8011A886_msetup[0] >= 0) {
        func_8010B82C_msetup(0x4900);
        func_8010B858_msetup();
        func_8010B82C_msetup(0x4902);
        func_8010B858_msetup();
        ret = arg0 + 1;
    } else {
        ret = arg0 - 1;
    }
    return ret;
}

s16 func_80109F04_msetup(s16 arg0) {
    s16 ret;

    if (D_8011A886_msetup[0] >= 0) {
        func_8010B968_msetup(D_8011AA34_msetup[0] + 0x1C00, 0);
        func_8010B82C_msetup(0x4A00);
        func_8010B858_msetup();
        func_8010B82C_msetup(0x4A02);
        func_8010B858_msetup();
        ret = arg0 + 1;
    } else {
        ret = arg0 - 1;
    }
    return ret;
}

s16 func_80109F7C_msetup(s16 arg0) {
    s32 i;

    D_8011A882_msetup.state = 2;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] != -1) {
        D_8011A990_msetup[0] = 0;
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        func_8010BA6C_msetup(1, D_8011A880_msetup);
        for (i = 4; i != 0; i--) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x2DB);
        for (i = 1; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i][0] = 1;
        }
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        D_8011A9F2_msetup[0][0] = 0x11;
        while (D_8011A9F2_msetup[D_8011A880_msetup - 1][0] != 0) {
            HuPrcVSleep();
        }
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_8010A10C_msetup(s16 arg0) {
    s16 ret;
    s32 i;

    if (D_8011AA41_msetup != 0) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i][0] = 7;
        }
        D_8011A882_msetup.state = 3;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
    } else {
        D_8011A990_msetup[0] = 1;
    }
    if (D_8011A886_msetup[0] == -1) {
        HuAudFXPlay(0x2E4);
        func_8010BC18_msetup(1, D_8011A880_msetup);
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_8010A204_msetup(s16 arg0) {
    D_8011A886_msetup[0] = 0;
    func_8010B82C_msetup(0x4919);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x491B);
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
        arg0 = -2;
    } else {
        func_8010B82C_msetup(0x491A);
        if (func_8010B858_msetup() == 0) {
            HuAudFXPlay(0x2E4);
            func_8010BE8C_msetup(D_8011A880_msetup);
            arg0 = 1;
        } else {
            D_8011A886_msetup[0] = -1;
            arg0--;
        }
    }
    return arg0;
}

s16 func_8010A2B0_msetup(s16 arg0) {
    D_8011A886_msetup[0] = 0;
    func_8010B82C_msetup(0x4919);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x491B);
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
        arg0 = -2;
    } else {
        func_8010B82C_msetup(0x491A);
        if (func_8010B858_msetup() == 0) {
            HuAudFXPlay(0x2E4);
            func_8010BC18_msetup(1, D_8011A880_msetup);
            arg0 = 1;
        } else {
            D_8011A886_msetup[0] = -1;
            arg0--;
        }
    }
    return arg0;
}

void func_8010A35C_msetup(MsMenuFunc *menu) {
    s16 sp10[2];
    Process *proc;
    s16 state;
    s32 i;

    D_8011A880_msetup = 4;
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[0], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, 6);
    D_8011A886_msetup[0] = -1;
    proc->user_data = D_8011A886_msetup - 2;
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(sp10, 0, 4);
    proc->user_data = sp10;
    if (D_8011A938_msetup == 6) {
        func_8010BA6C_msetup(0, 1);
    }
    func_80106260_msetup(&D_80119580_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    D_8011A886_msetup[0] = 0;
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    if (D_8011A938_msetup == 6) {
        HuAudFXPlay(0x2DB);
        D_8011A9F2_msetup[0][0] = 1;
    }
    sp10[0] = 1;
    do {
        HuPrcVSleep();
    } while (sp10[0] == 1);
    D_8011A990_msetup[0] = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    state = 0;
    do {
        state = menu[state](state);
    } while (state >= 0);
    D_8011A990_msetup[0] = 0;
    if (state < -1) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i][0] = 0xC;
        }
        HuPrcVSleep();
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i][0] = 0x10;
        }
        HuAudSeqFadeOut(0x186);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(D_801197BC_msetup, 22.0f, NULL);
        for (i = 0; i < D_8011A880_msetup; i++) {
            GwPlayer[i].chr = D_8011AA34_msetup[i];
            GwPlayer[i].star = D_8011AA3C_msetup[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = D_8011AA30_msetup[i];
            if (D_8011AA38_msetup[i] < 4) {
                GwPlayer[i].cpu_difficulty = D_8011AA38_msetup[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        D_8011A944_msetup = 1;
        D_8011AA4C_msetup[0] = 0x69;
        D_8011A946_msetup = 0;
    } else {
        D_80119410_msetup = 0x4B;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(D_801196C0_msetup, 25.0f, NULL);
    }
    D_80119410_msetup = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010A780_msetup(void) {
    func_8010A35C_msetup(D_80119510_msetup);
}

void func_8010A7A0_msetup(void) {
    /* one .bss block from D_8011AA30_msetup: retail anchors at +0x10 (D_8011AA40_msetup) */
    D_8011AA30_msetup[0x10] = 1;
    D_8011AA30_msetup[0x11] = 3;
    D_8011AA30_msetup[4] = GwStory.unk1;
    D_8011AA30_msetup[8] = 0xFF;
    func_8010A35C_msetup(D_80119524_msetup);
}

void func_8010A7EC_msetup(s16 mode) {
    s16 sp10[2];
    Process *proc;
    s32 *mes;
    s32 i;
    s8 star;

    switch (mode) {
    case 0:
    default:
        D_8011A880_msetup = 4;
        D_8011AA30_msetup[0x10] = 1;
        D_8011AA30_msetup[0x11] = 3;
        D_8011AA30_msetup[4] = 3;
        D_8011AA30_msetup[5] = 2;
        D_8011AA30_msetup[6] = 0;
        D_8011AA30_msetup[7] = 4;
        mes = D_80119534_msetup;
        i = 2;
        break;
    case 1:
        D_8011A880_msetup = 2;
        D_8011AA30_msetup[0x10] = 1;
        D_8011AA30_msetup[0x11] = 1;
        D_8011AA30_msetup[4] = 0;
        D_8011AA30_msetup[5] = 1;
        mes = D_80119548_msetup;
        i = 1;
        break;
    }
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[i], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    func_8010E21C_msetup();
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(sp10, 0, 4);
    proc->user_data = sp10;
    func_80106260_msetup(&D_80119580_msetup);
    func_8010BBF4_msetup(D_8011A880_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    sp10[0] = 1;
    HuAudFXPlay(0x2DB);
    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011A9F2_msetup[i][0] = 1;
    }
    while (sp10[0] == 1) {
        HuPrcVSleep();
    }
    D_8011A990_msetup[0] = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    func_8010B998_msetup();
    for (i = 0; i < 4; i++) {
        func_8010B82C_msetup(mes[i]);
        func_8010B858_msetup();
        if (func_8010BA3C_msetup() & 0x4000) {
            func_8010B82C_msetup(mes[4]);
            if (func_8010B858_msetup() == 0) {
                break;
            }
        }
    }
    if (i < 4) {
        D_8011A990_msetup[0] = 0;
        D_80119410_msetup = 0x4B;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(D_801196C0_msetup, 25.0f, NULL);
    } else {
        HuAudFXPlay(0x2A6);
        D_8011A990_msetup[0] = 0;
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i][0] = 0x10;
        }
        HuAudSeqFadeOut(0x186);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(D_801197BC_msetup, 22.0f, NULL);
        _ClearFlag(0);
        GwSystem.current_board_index = 6;
        GwSystem.total_turns = 20;
        GwSystem.current_game_length = 0;
        switch (mode) {
        case 0:
        default:
            D_8011A944_msetup = 4;
            D_8011AA4C_msetup[0] = 0x47;
            D_8011A946_msetup = 0;
            star = 0;
            break;
        case 1:
            D_8011A944_msetup = 3;
            D_8011AA4C_msetup[0] = 0x5A;
            D_8011A946_msetup = 0;
            star = 5;
            break;
        }
        for (i = 0; i < D_8011A880_msetup; i++) {
            GwPlayer[i].chr = D_8011AA34_msetup[i];
            GwPlayer[i].star = star;
            GwPlayer[i].pad = D_8011A948_msetup;
            GwPlayer[i].cpu_difficulty = 1;
            GwPlayer[i].stat = 1;
            GwPlayer[i].coin = 0;
        }
    }
    D_80119410_msetup = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010AC78_msetup(void) {
    func_8010A7EC_msetup(0);
}

void func_8010AC94_msetup(void) {
    func_8010A7EC_msetup(1);
}

void func_8010ACB0_msetup(void) {
}
