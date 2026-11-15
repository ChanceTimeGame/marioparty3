#include "common.h"
#include "duel01.h"

void func_801059D0_duel01(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), 0x80);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel01(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_80119470_duel01 = func_800E1824_name_81(0, 0xA0, 1);
    D_80119474_duel01 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_80119478_duel01 = func_800E1824_name_81(1, 0xBC, 1);
    D_8011947C_duel01 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel01(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_80119470_duel01);
    func_800E1854_name_81(D_80119474_duel01);
    func_800E1854_name_81(D_80119478_duel01);
    func_800E1854_name_81(D_8011947C_duel01);
}

void func_80105B64_duel01(void) {
    GwSystem.current_board_index = 0;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x5A, 0, 0x4190);
}

void func_80105B9C_duel01(void) {
    s8 sp10;
    s8 sp11;

    omInitObjMan(0xA, 0);
    func_800E94D0_name_81();
    func_800E9B10_name_81(0x13, 0x241);
    func_800E9F4C_name_81(0x1C, &sp10, &sp11);
    func_800ECD0C_name_81(0, sp10, sp11);
    func_800E9F4C_name_81(0x1B, &sp10, &sp11);
    func_800ECD0C_name_81(1, sp10, sp11);
    GwPlayer[0].nnlink = -1;
    GwPlayer[0].nnidx = -1;
    GwPlayer[1].nnlink = -1;
    GwPlayer[1].nnidx = -1;
    func_800E9D9C_name_81();
    func_800E9564_name_81();
    GwSystem.bank_coins = 5;
    GwSystem.playerIndexVisitingBowser = 0;
    func_800EA760_name_81();
    omOvlReturnEx(1);
}

void func_80105C64_duel01(s32 arg0, s32 arg1, unkStruct01 *arg2) {
    f32 temp_f20;

    func_800EB708_name_81(arg0, arg1, arg2);
    temp_f20 = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->unk_00 = sindf(temp_f20);
    arg2->unk_08 = cosdf(temp_f20);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80105CC0_duel01);

void *func_80105EB0_duel01(unkStruct04 *arg0) {
    Process *process;
    unkStruct02 *temp_v0_2;

    process = omAddPrcObj(&func_80105CC0_duel01, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct02));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00.x = arg0->unk_0C.x;
    temp_v0_2->unk_00.y = arg0->unk_0C.y;
    temp_v0_2->unk_00.z = arg0->unk_0C.z;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80105F20_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801060D0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010615C_duel01);

void func_80106240_duel01(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

// TODO: arg0 is a pointer
void func_80106260_duel01(s32 arg0, unkStruct05 *arg1, s32 arg2, f32 arg3) {
    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        func_800EC1E4_name_81(&D_80105540_name_81, arg0 + 0xC, &D_80105540_name_81, arg3);
    } else {
        func_800EC1E4_name_81(&D_80105540_name_81, arg1->unk_24 + 0xC, &D_80105540_name_81, arg3);
    }
}

// TODO: arg0 is a pointer
void func_801062C0_duel01(s32 arg0, unkStruct05 *arg1, s32 arg2, f32 arg3) {
    if (arg2 & 9) {
        func_800EBF2C_name_81(&D_80105540_name_81, arg0 + 0xC, &D_80105540_name_81);
    } else {
        func_800EBF2C_name_81(&D_80105540_name_81, arg1->unk_24 + 0xC, &D_80105540_name_81);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80106308_duel01);

Process *func_8010645C_duel01(s32 arg0, s32 arg1) {
    Process *process;
    unkStruct06 *temp_v0_2;

    process = omAddPrcObj(&func_80106308_duel01, 0xA, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(unkStruct06));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_00 = arg0;
    temp_v0_2->unk_04 = arg1;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801064C8_duel01);

void *func_80106740_duel01(s32 arg0) {
    Object *obj;

    obj = func_800D8010_name_81(arg0 & 0xFF, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0x1800);
    func_8001C448_main(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    return obj;
}

void func_801067D4_duel01(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81();
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80106828_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80107188_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118E60_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801079B8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80107EBC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801084A4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80108550_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80109404_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80109888_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010A210_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010AAB0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010AD48_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010AFB4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B130_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B480_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B4C0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B528_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B53C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B54C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010BCD4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010CE68_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010D424_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010D95C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010D9F4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DA84_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DB00_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118E98_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118EA4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118EB0_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118EE0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DB2C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DC04_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DCA8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DD3C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DDEC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DF68_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E008_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F18_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E1B4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E2CC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E2F8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E348_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E3F8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E574_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E614_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E7C0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E8D8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E904_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E954_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EA74_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EAD4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EB44_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EB88_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EC78_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010ED20_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EDA0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EFBC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010F12C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010F99C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80110068_duel01);

void func_80110B7C_duel01(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110068_duel01(0);
    }
}

void func_80110BD8_duel01(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if ((MBDGetCurrentPlayerIndex() == 1) && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110068_duel01(1);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F30_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F48_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F60_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F6C_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F84_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FB4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE8_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FF0_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119010_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119014_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801190FC_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801191E4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801192CC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80110C3C_duel01);

#ifdef NON_MATCHING
// duel b4: logic checked; masked 8: the turn if-chain, where retail keeps buf's address out of s0 and leaves a j/nop pair (509 vs 512 instructions)
// duel b4: bell space: ring the bell; at zero coins the bell pays out and the board ends the turn
void func_80111DFC_duel01(void) {
    Vec pos;
    char buf[8];
    GW_PLAYER *player;
    SpaceData *space;
    DuelB4HmfPart *part;
    f32 ofs;
    s32 i;
    char *str;
    GW_SYSTEM *system = &GwSystem;
    DuelB4MoveFunc move = (DuelB4MoveFunc)(void (*)(void))func_800EC1E4_name_81;

    player = MBDGetPlayerStruct(-1);
    space = MBDMasuGet(0x1D);
    func_800DB3E0_name_81(system->current_player_index);
    func_800F38DC_name_81(-1, -1, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
    HuVecCopy3F(&pos, &player->player_obj->coords);
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), move(&pos, &space->coords, &pos, 4.0f));
    func_800D90D0_name_81(D_80119490_duel01, 2, 0);
    func_8002FD8C_main(D_80119490_duel01->omObj1->model[0],
                       HmfModelData[D_80119490_duel01->omObj1->model[0]].unk02, D_80118F18_duel01, 0x4C, 0x46);
    func_8002FD8C_main(D_80119490_duel01->omObj1->model[0], D_80119490_duel01->omObj1->motion[2],
                       D_80118F18_duel01, 0x4C, 0x46);
    i = 0;
    ((DuelB4HmfPart *)func_8001D33C_main(D_80119490_duel01->omObj1->model[0], D_80118F18_duel01))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
    while (!(func_800D9234_name_81(D_80119490_duel01) & 1)) {
        if (++i == 8) {
            HuAudFXPlay(0x1C5);
        }
        HuPrcVSleep();
    }
    func_8002FD8C_main(D_80119490_duel01->omObj1->model[0],
                       HmfModelData[D_80119490_duel01->omObj1->model[0]].unk02, D_80118F18_duel01, 0x4C, 0x46);
    part = func_8001D33C_main(D_80119490_duel01->omObj1->model[0], D_80118F18_duel01);
    part->unk_14 = (GwSystem.bank_coins - 5) * 60;
    HuAudFXPlay(0x1C7);
    for (ofs = 0.0f; ofs >= -60.0f; ofs -= 4.0f) {
        part->unk_14 = (GwSystem.bank_coins - 5) * 60 + ofs;
        HuPrcVSleep();
    }
    HuPrcChildWait();
    if (GwSystem.bank_coins != 0) {
        GwSystem.bank_coins--;
    }
    func_8010DC04_duel01();
    D_8011872C_duel01 = 12.0f;
    if (GwSystem.bank_coins != 0) {
        HuAudFXPlay(0x207);
        func_800D918C_name_81(D_80119490_duel01, 0, 0, 5, 2);
        func_8002FD8C_main(D_80119490_duel01->omObj1->model[0], D_80119490_duel01->omObj1->motion[0],
                           D_80118F18_duel01, 0x4C, 0x46);
        func_8001C92C_main(D_80119490_duel01->omObj1->model[0], (5.0f - GwSystem.bank_coins) / 4.0f + 1.0f);
        HuPrcSleep(0x18);
        func_800D90D0_name_81(D_80119490_duel01, -1, 2);
    } else {
        HuAudFXPlay(0x1C6);
        func_800D918C_name_81(D_80119490_duel01, 1, 0, 5, 2);
        func_8002FD8C_main(D_80119490_duel01->omObj1->model[0], D_80119490_duel01->omObj1->motion[1],
                           D_80118F18_duel01, 0x4C, 0x46);
        func_8001C92C_main(D_80119490_duel01->omObj1->model[0], 1.0f);
        func_8010DC04_duel01();
        func_800F74E4_name_81(-1);
        func_800EEC40_name_81(&pos);
        if (system->current_turn < 11) {
            str = "20";
        } else if (system->current_turn >= 20) {
            str = "40";
        } else {
            str = "30";
        }
        sprintf(buf, str);
        HuAudFXPlay(0x2A7);
        func_800EB49C_name_81(0x15, 0x1F30, (s32)buf, 0, 0, 0, 0);
        func_800EB58C_name_81();
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80118414_duel01();
        D_80100F44_name_81 = D_80119490_duel01;
        func_800FD620_name_81();
        HuPrcSleep(-1);
    }
    D_8011872C_duel01 = 3.0f;
    HuPrcChildLink(HuPrcCurrentGet(), move(&pos, &player->player_obj->coords, &pos, 4.0f));
    func_800DADA0_name_81(system->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(1.7f));
    HuPrcChildWait();
    func_800FC888_name_81(1);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80111DFC_duel01);
#endif

// duel b4: the current player's partner effect: restore the player's star field (duel HP) to 5
void func_801123E8_duel01(void) {
    GW_PLAYER *player;
    void *win;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1FF);
    win = func_800FFC2C_name_81(-1, 3, 5);
    func_800EE74C_name_81(3);
    func_800FFCCC_name_81(win);
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    func_800F3880_name_81(-1, 6, 0);
    func_8004ACE0_main(0x2BD, GwSystem.current_player_index);
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    GwPlayer[GwSystem.current_player_index].star = 5;
}

void func_801124D8_duel01(void) {
    func_800E18C0_name_81();
    func_800E1960_name_81();
    func_800E1F38_name_81();
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
}

// duel b4: lose up to 10 coins
void func_80112514_duel01(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 coins = GwPlayer[system->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    func_800E14D8_name_81(system->current_player_index, -coins);
    func_800F7378_name_81(system->current_player_index, -coins);
    HuPrcSleep(30);
}

// duel b4: gain 10 coins
void func_80112590_duel01(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E14D8_name_81(system->current_player_index, 10);
    func_800F7378_name_81(system->current_player_index, 10);
    HuPrcSleep(30);
}

// duel b4: warp the current player to their start space
void func_801125CC_duel01(void) {
    s8 link;
    s8 idx;
    s8 backLink = -1;
    s8 backIdx = -1;

    func_800E9F4C_name_81(MBDGetCurrentPlayerIndex() == 0 ? 0x1C : 0x1B, &link, &idx);
    func_80118320_duel01(&backLink, &backIdx);
    func_800E24AC_name_81(link, idx, backLink, backIdx);
    func_800ED214_name_81(GwSystem.current_player_index);
    func_80110068_duel01(MBDGetCurrentPlayerIndex());
}

// duel b4: swap space: a growing spin swaps the two players' places
void func_8011264C_duel01(void) {
    void *win[2];
    GW_PLAYER *player;
    Object *obj;
    f32 rot;
    f32 scale;
    s32 cur;
    s32 other;

    cur = MBDGetCurrentPlayerIndex();
    other = (cur + 1) & 1;
    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuPrcSleep(10);
    HuAudFXPlay(0x1F6);
    func_800EE74C_name_81(1);
    HuPrcSleep(15);
    obj = func_800D8010_name_81(0x21, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1F9);
    win[0] = func_800FFC2C_name_81(0, 3, 5);
    win[1] = func_800FFC2C_name_81(1, 3, 5);
    rot = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800EA898_name_81(other, cur);
    func_800EA7D4_name_81();
    func_800EA97C_name_81();
    for (; scale >= 1.0f; scale -= 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win[0]);
    func_800FFCCC_name_81(win[1]);
    func_800D8F3C_name_81(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    func_800EB49C_name_81(0x16, 0x1F2B, D_80101200_name_81[GwPlayer[GwSystem.current_player_index ^ 1].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    func_800F3880_name_81(-1, 6, 0);
    func_8004ACE0_main(0x2BD, GwSystem.current_player_index);
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
}

// duel b4: partner power-up space: each partner flashes and gains power
void func_801129C8_duel01(void) {
    Object *partner[2];
    GW_PLAYER *player;
    void *win;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1F6);
    win = func_800FFC2C_name_81(-1, 0, 5);
    func_800EE74C_name_81(0);
    func_800FFCCC_name_81(win);
    func_800EDF78_name_81();
    HuPrcChildLink(HuPrcCurrentGet(), func_800EE40C_name_81(2));
    partner[0] = NULL;
    partner[1] = NULL;
    if (player->stats.prize.gamblePrize != -1) {
        partner[0] = func_800D8010_name_81(0x38, 0);
        func_800D8944_name_81(partner[0]);
        HuVecCopy3F(&partner[0]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 0)->coords);
        func_8001C814_main(partner[0]->omObj1->model[0], 2, 0);
    }
    if (player->stats.prize.duelNo != -1) {
        partner[1] = func_800D8010_name_81(0x38, 0);
        func_800D8944_name_81(partner[1]);
        HuVecCopy3F(&partner[1]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 1)->coords);
        func_8001C814_main(partner[1]->omObj1->model[0], 2, 0);
    }
    HuAudFXPlay(0x1FA);
    if (partner[0] != NULL) {
        func_800EFABC_name_81(partner[0]);
        func_800D8F3C_name_81(partner[0]);
    }
    if (partner[1] != NULL) {
        func_800EFABC_name_81(partner[1]);
        func_800D8F3C_name_81(partner[1]);
    }
    Duel_PowerUpPartners(system->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), func_800E4A74_name_81(0));
    HuPrcChildWait();
    func_800EDDBC_name_81();
}

// duel b4: partner power-down space
void func_80112BB4_duel01(void) {
    Object *partner[2];
    GW_PLAYER *player;
    void *win;
    GW_SYSTEM *system = &GwSystem;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1FB);
    win = func_800FFC2C_name_81(-1, 0, 5);
    func_800EE74C_name_81(4);
    func_800FFCCC_name_81(win);
    func_800EDF78_name_81();
    HuPrcChildLink(HuPrcCurrentGet(), func_800EE40C_name_81(2));
    partner[0] = NULL;
    partner[1] = NULL;
    if (player->stats.prize.gamblePrize != -1) {
        partner[0] = func_800D8010_name_81(0x3A, 0);
        func_800D8944_name_81(partner[0]);
        HuVecCopy3F(&partner[0]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 0)->coords);
        func_8001C814_main(partner[0]->omObj1->model[0], 2, 0);
    }
    if (player->stats.prize.duelNo != -1) {
        partner[1] = func_800D8010_name_81(0x3A, 0);
        func_800D8944_name_81(partner[1]);
        HuVecCopy3F(&partner[1]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, 1)->coords);
        func_8001C814_main(partner[1]->omObj1->model[0], 2, 0);
    }
    if (partner[0] != NULL) {
        func_800EFABC_name_81(partner[0]);
        func_800D8F3C_name_81(partner[0]);
    }
    if (partner[1] != NULL) {
        func_800EFABC_name_81(partner[1]);
        func_800D8F3C_name_81(partner[1]);
    }
    Duel_PowerDownPartners(system->current_player_index);
    HuAudFXPlay(0x1FC);
    HuPrcChildLink(HuPrcCurrentGet(), func_800E4A74_name_81(1));
    HuPrcChildWait();
    func_800EDDBC_name_81();
}

// duel b4: spin the partner's model about Y by ang * 10 degrees (the model matrix is rebuilt as a pure Y rotation)
#define B4_PARTNER_SPIN(obj, vel, ang)                                                                         \
    {                                                                                                          \
        HmfModel *mdl;                                                                                         \
        (obj)->velocity.x = (vel);                                                                             \
        sincosdf((ang) * 10.0f, &HmfModelData[(obj)->omObj1->model[0]].mtx[8],                                 \
                 &HmfModelData[(obj)->omObj1->model[0]].mtx[10]);                                              \
        HmfModelData[(obj)->omObj1->model[0]].mtx[2] = -HmfModelData[(obj)->omObj1->model[0]].mtx[8];         \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                          \
        mdl->mtx[0] = mdl->mtx[10];                                                                            \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                          \
        mdl->mtx[1] = mdl->mtx[3] = mdl->mtx[4] = mdl->mtx[6] = mdl->mtx[7] = mdl->mtx[9] = mdl->mtx[11] =     \
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;                                                 \
        mdl = &HmfModelData[(obj)->omObj1->model[0]];                                                          \
        mdl->mtx[5] = mdl->mtx[15] = 1.0f;                                                                     \
    }

// duel b4: partner swap space: both partners spin, swap front and back, and spin back
void func_80112DA0_duel01(void) {
    GW_PLAYER *player;
    Object *obj;
    void *win;
    f32 angle;
    s32 cur;

    player = MBDGetPlayerStruct(-1);
    cur = MBDGetCurrentPlayerIndex();
    func_800DD41C_name_81(&player->player_obj->coords);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1F6);
    func_800EE74C_name_81(1);
    HuAudFXPlay(0x1FD);
    func_800DD554_name_81();
    win = func_800FFC2C_name_81(-1, 1, 5);
    for (angle = 0.0f; angle < 120.0f; angle += 5.0f) {
        if (player->stats.prize.gamblePrize != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 0);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        if (player->stats.prize.duelNo != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 1);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        HuPrcVSleep();
    }
    Duel_SwapPartnerPositions(cur);
    func_800DD564_name_81();
    for (angle = 120.0f; angle > 0.0f; angle -= 5.0f) {
        if (player->stats.prize.gamblePrize != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 0);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        if (player->stats.prize.duelNo != -1) {
            obj = MBDGetPlayerPartnerRef(cur, 1);
            B4_PARTNER_SPIN(obj, angle, angle);
        }
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win);
    /* angle is 0 here: the loop steps from 120 by 5 */
    if (player->stats.prize.gamblePrize != -1) {
        obj = MBDGetPlayerPartnerRef(cur, 0);
        B4_PARTNER_SPIN(obj, 0.0f, angle);
    }
    if (player->stats.prize.duelNo != -1) {
        obj = MBDGetPlayerPartnerRef(cur, 1);
        B4_PARTNER_SPIN(obj, 0.0f, angle);
    }
    func_800DD570_name_81();
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F2C);
    func_800EDF78_name_81();
    func_800EE468_name_81(1);
    func_800EDDBC_name_81();
}

// duel b4: partner downgrade space (the mirror of the swap space's spin)
void func_801135D8_duel01(void) {
    void *win[2];
    GW_PLAYER *player;
    Object *obj;
    f32 rot;
    f32 scale;

    player = MBDGetPlayerStruct(-1);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuPrcSleep(10);
    HuAudFXPlay(0x1FB);
    func_800EE74C_name_81(4);
    HuPrcSleep(15);
    obj = func_800D8010_name_81(0x22, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    func_8001C8E4_main(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1FE);
    win[0] = func_800FFC2C_name_81(0, 2, 5);
    win[1] = func_800FFC2C_name_81(1, 2, 5);
    rot = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800EA8DC_name_81();
    func_800EA97C_name_81();
    for (; scale >= 1.0f; scale -= 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(&HmfModelData[obj->omObj1->model[0]].mtx, rot);
        rot += 20.0f;
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(win[0]);
    func_800FFCCC_name_81(win[1]);
    func_800D8F3C_name_81(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F2D);
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    CharFXPlay(0x286, GwPlayer[GwSystem.current_player_index].chr);
    func_800F3880_name_81(-1, 5, 0);
    func_800EFABC_name_81(player->player_obj);
}

// duel b4: gain 20 coins
void func_801138D0_duel01(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E14D8_name_81(system->current_player_index, 20);
    func_800F7378_name_81(system->current_player_index, 20);
    HuPrcSleep(30);
}

// duel b4: the event roulette's result: a banner drops in and bounces, then the chosen space event runs
void func_8011390C_duel01(void) {
    DuelB4SprGrp *grp;
    void *data;
    s32 i;
    s32 y;

    mbItemBtnF = 0;
    func_800F74E4_name_81(-1);
    HuAudFXPlay(0x204);
    grp = func_800F4528_name_81(2, 2);
    data = DataRead(0x130103);
    grp->sprite[0] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp->group, 0, grp->sprite[0], 0);
    HuSprPriSet(grp->group, 0, 1);
    HuSprAttrSet(grp->group, 0, 0x1000);
    func_80054904_main(grp->group, 0, 160, -32);
    func_800555E8_main(grp->group, 0, 16, 12, 304, 228);
    data = DataRead(0x130104);
    grp->sprite[1] = func_80055810_main(data);
    DataClose(data);
    func_80055024_main(grp->group, 1, grp->sprite[1], 0);
    HuSprPriSet(grp->group, 1, 2);
    HuSprAttrSet(grp->group, 1, 0x1000);
    func_80054904_main(grp->group, 1, 0, 0);
    func_800555E8_main(grp->group, 0, 16, 12, 304, 228);
    func_80055420_main(grp->group, 1, 251, 203, 0);
    for (i = 90; i < 180; i += 10) {
        func_80054904_main(grp->group, 0, 160, sindf(i) * -152.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 15) {
        func_80054904_main(grp->group, 0, 160, sindf(i) * -60.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 20) {
        func_80054904_main(grp->group, 0, 160, sindf(i) * -30.0f + 120.0f);
        HuPrcVSleep();
    }
    func_80054904_main(grp->group, 0, 160, 120);
    for (y = 0, i = 0; i < 9; i++) {
        y += i * 2;
        func_80054904_main(grp->group, 0, 160, 120 - y);
        HuPrcVSleep();
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800E0924_name_81());
    HuPrcChildWait();
    func_800F4584_name_81(grp);
    func_800F75EC_name_81(-1);
    D_801188E4_duel01[GwSystem.minigame_index]();
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

#ifdef NON_MATCHING
// duel b4: logic checked branch by branch against the asm; masked ~240: operand load order and register choice in the repeated power-vs-HP tests (759 vs 779 instructions)
// duel b4: COM decision for the current player against the opponent, from the opponent's position (clink, cidx)
// relative to the roll (mbWalkNum); compares partner power with HP. me/opp partner fields are PartnerStats.
s32 func_80113CAC_duel01(void) {
    DuelB4Dist dist;
    GW_PLAYER *me;
    GW_PLAYER *opp;
    s32 cur;
    s32 hp;
    s32 n;
    s32 m;
    s32 t;
    s32 other;
    s32 walk;

    cur = MBDGetCurrentPlayerIndex();
    other = (s16)(MBDGetCurrentPlayerIndex() ^ 1);
    me = MBDGetPlayerStruct(-1);
    opp = MBDGetPlayerStruct(other);
    walk = mbWalkNum;
    dist = D_801193E8_duel01;
    switch (opp->clink) {
        case 0:
            if (opp->cidx == walk - 6) {
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return TRUE;
                }
                if (opp->stats.partners.backID == 4 && !(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                    return FALSE;
                }
                if (func_800F8980_name_81(cur) == 0) {
                    n = 100;
                } else {
                    n = (GwPlayer[cur].coin - 5) / func_800F8980_name_81(cur);
                }
                if (n < 4) {
                    return FALSE;
                }
                return me->stats.partners.frontPower != 0;
            }
            if (opp->cidx < walk - 6) {
                hp = me->star;
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return TRUE;
                }
                if (opp->stats.partners.backID == 4) {
                    if (!(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                        return FALSE;
                    }
                    if (me->stats.partners.frontPower > me->stats.partners.frontHp) {
                        hp -= me->stats.partners.frontPower - me->stats.partners.frontHp;
                    }
                }
                if (walk == 10) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.frontHp + opp->star)) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID != 4) {
                        return TRUE;
                    }
                    return me->stats.partners.backPower < hp + me->stats.partners.backHp;
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID != 10) {
                        return FALSE;
                    }
                    return opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star;
                }
                return FALSE;
            }
            if (walk == 6) {
                if (func_800F8980_name_81(cur) == 0) {
                    n = 100;
                    m = 100;
                } else {
                    n = GwPlayer[cur].coin / func_800F8980_name_81(cur);
                    m = (GwPlayer[cur].coin - 5) / func_800F8980_name_81(cur);
                }
                if (n == 0) {
                    return FALSE;
                }
                if (m > 0) {
                    return TRUE;
                }
                if (func_800EFE20_name_81(100.0f) < 50) {
                    return TRUE;
                }
                return FALSE;
            }
            if (walk != 1) {
                return FALSE;
            }
            if (opp->cidx >= 6) {
                if (me->stats.partners.backID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.backID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.backID == 10) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.backHp + opp->star)) {
                        return FALSE;
                    }
                } else if (opp->stats.partners.frontHp + opp->star < me->stats.partners.backPower) {
                    return FALSE;
                }
                if (opp->stats.partners.frontID != 4) {
                    return FALSE;
                }
                return !(me->stats.partners.backPower < me->star + me->stats.partners.backHp);
            }
            if (opp->stats.partners.frontPower == 0) {
                return FALSE;
            }
            if (func_800F8980_name_81(cur) == 0) {
                n = 100;
            } else {
                n = (GwPlayer[cur].coin - 5) / func_800F8980_name_81(cur);
            }
            return n >= 4;
        case 1:
            if (opp->cidx == walk - 1) {
                if (me->stats.partners.frontID == 3) {
                    return FALSE;
                }
                if (opp->stats.partners.backID != 4) {
                    return FALSE;
                }
                if (me->stats.partners.frontPower < me->star + me->stats.partners.frontHp) {
                    return FALSE;
                }
                return me->stats.partners.frontPower < opp->stats.partners.backHp + opp->star;
            }
            if (opp->cidx < walk - 1) {
                hp = me->star;
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 10) {
                    t = opp->stats.partners.frontHp;
                } else {
                    t = opp->stats.partners.backHp;
                }
                if (t + opp->star <= me->stats.partners.frontPower) {
                    return FALSE;
                }
                if (opp->stats.partners.backID == 4) {
                    if (!(me->stats.partners.frontPower < me->star + me->stats.partners.frontHp)) {
                        return TRUE;
                    }
                    if (me->stats.partners.frontPower > me->stats.partners.frontHp) {
                        hp -= me->stats.partners.frontPower - me->stats.partners.frontHp;
                    }
                }
                if (walk == 7) {
                    if (!(me->stats.partners.backPower < opp->stats.partners.frontHp + opp->star)) {
                        return FALSE;
                    }
                    if (opp->stats.partners.frontID != 4) {
                        return FALSE;
                    }
                    return !(me->stats.partners.backPower < hp + me->stats.partners.backHp);
                }
                if (GwSystem.current_turn != GwSystem.total_turns || cur == 0) {
                    if (opp->stats.partners.frontID == 8 && me->star < 2) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                        return TRUE;
                    }
                    if (opp->stats.partners.frontID == 10) {
                        return !(opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star);
                    }
                    if (me->stats.partners.backHp + me->star < opp->stats.partners.frontPower) {
                        return TRUE;
                    }
                    return FALSE;
                }
                return FALSE;
            }
            if (walk == 1) {
                return FALSE;
            }
            if (opp->cidx < 8) {
                return FALSE;
            }
            if (opp->stats.partners.frontPower == 0) {
                return FALSE;
            }
            if (walk != 6) {
                return FALSE;
            }
            if (opp->stats.partners.frontID != 4) {
                return TRUE;
            }
            return me->stats.partners.backPower < me->stats.partners.backHp + me->star;
        case 2:
            if ((opp->rev & 1) || opp->nlink == 0) {
                if (dist.v[walk] < opp->cidx) {
                    return FALSE;
                }
                if (me->stats.partners.frontID == 8 && opp->star < 2) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 10) {
                    if (!(me->stats.partners.frontPower < opp->stats.partners.frontHp + opp->star)) {
                        return TRUE;
                    }
                } else if (!(me->stats.partners.frontPower < opp->star + opp->stats.partners.backHp)) {
                    return TRUE;
                }
                if (opp->stats.partners.frontID == 4) {
                    if (me->stats.partners.frontPower < me->star + me->stats.partners.frontHp) {
                        return TRUE;
                    }
                    return !(me->stats.partners.frontPower < opp->stats.partners.frontHp + opp->star);
                }
                if (me->stats.partners.frontPower != 0) {
                    return TRUE;
                }
                if (opp->stats.partners.frontPower != 0) {
                    return TRUE;
                }
                if (me->stats.partners.frontID == 3) {
                    return TRUE;
                }
                return FALSE;
            }
            if (dist.v[walk] < opp->cidx) {
                if (walk == 2 && me->stats.partners.frontPoweredUp != walk) {
                    if (func_800F8980_name_81(cur) == 0) {
                        n = 100;
                    } else {
                        n = (GwPlayer[cur].coin - 5) / (func_800F8980_name_81(cur) * 2);
                    }
                } else {
                    if (func_800F8980_name_81(cur) == 0) {
                        n = 100;
                    } else {
                        n = (GwPlayer[cur].coin - 5) / (func_800F8980_name_81(cur) * 2);
                    }
                }
                if (n < 4) {
                    return FALSE;
                }
                return me->stats.partners.frontPower != 0;
            }
            if (me->stats.partners.frontID == 8 && opp->star < 2) {
                return TRUE;
            }
            if (me->stats.partners.frontID == 3 && opp->star <= me->stats.partners.frontPoweredUp) {
                return TRUE;
            }
            if (me->stats.partners.frontID == 10) {
                if (!(me->stats.partners.frontPower < opp->stats.partners.frontHp + opp->star)) {
                    return TRUE;
                }
            } else if (!(me->stats.partners.frontPower < opp->star + opp->stats.partners.backHp)) {
                return TRUE;
            }
            if (opp->stats.partners.backID == 4) {
                return FALSE;
            }
            if (walk == 6) {
                return TRUE;
            }
            if (opp->cidx == dist.v[walk]) {
                return !(me->stats.partners.frontPower == 0 && walk == 1);
            }
            if (opp->stats.partners.frontID == 8 && me->star < 2) {
                return FALSE;
            }
            if (opp->stats.partners.frontID == 3 && me->star <= opp->stats.partners.frontPoweredUp) {
                return FALSE;
            }
            if (opp->stats.partners.frontID == 10) {
                if (opp->stats.partners.frontPower < me->stats.partners.frontHp + me->star) {
                    return FALSE;
                }
            } else if (opp->stats.partners.frontPower < me->star + me->stats.partners.backHp) {
                return FALSE;
            }
            return FALSE;
    }
    return FALSE;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80113CAC_duel01);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801147FC_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801193E8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80115850_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801159F8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80116484_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119410_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117480_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117624_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801179AC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117D3C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117DDC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117E7C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117ED8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117FFC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118058_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118178_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801181C4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118210_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011825C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801182A8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801182E4_duel01);

void func_80118320_duel01(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118328_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118414_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118530_duel01);
