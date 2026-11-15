#include "common.h"
#include "ovl_81.h"

// this file is a duplicate of 10C230.c in ovl_80_shared_board
typedef struct UnkE3CD0 {
    char unk_00[0xC];
    Vec unk_0C;
    char unk_18[0x18];
    f32 unk_30;
} UnkE3CD0;

void func_8004A950_main(void);
extern s32 D_80101AF8_name_81;
extern s32 D_80101AFC_name_81;
extern s32 D_80101B00_name_81;
extern s32 D_80101B04_name_81;
extern UnkE3CD0 *D_801054B0_name_81;
extern Vec *D_801054AC_name_81;
extern Vec D_801054A0_name_81;
extern s16 D_8010549E_name_81;
extern s16 D_800A12C8_main;
extern f32 D_800C9938_main;
extern s16 D_800CE1D0_main;
extern s16 D_800CE206;
extern s16 D_800D124C_main;
extern s16 D_80101A50_name_81;
extern s32 D_80101A98_name_81;
extern void (*D_80101A8C_name_81)(void);
extern s32 D_80101A70_name_81[];
extern s32 D_80101A54_name_81[];
extern s16 D_800CE204;
extern s16 D_800CE206;
extern s32 D_80105498_name_81;
extern s16 D_8010549C_name_81;
extern u8 D_80101AF4_name_81[];

void func_800FBF00_name_81(s32 id, s16 event, u16 stat) {
    omOvlHisData *overlay = &mbovlhis[mbovlhisidx++];

    if (id != -2) {
        if (id == -1) {
            id = omovlhis[omovlhisidx].overlayID;
            overlay->overlayID = id;
        } else {
            overlay->overlayID = id;
        }
    } else {
        id = D_80101A54_name_81[GwSystem.current_board_index];
        overlay->overlayID = id;
    }

    overlay->event = event;
    overlay->stat = stat;

    if (mbovlhisidx >= ARRAY_COUNT(mbovlhis)) {
        mbovlhisidx = ARRAY_COUNT(mbovlhis) - 1;
    }
}

void func_800FBFA4_name_81(void) {
    D_800CD2A0_main.unk_02 = 1;
    mbovlhisidx = 0;

    if (GWBoardFlagCheck(1) == 0) {
        func_800FBF00_name_81(-2, 1, 0x4190);
        func_800FBF00_name_81(D_80101A70_name_81[GwSystem.current_board_index], 0, 0x4190);
    }
    func_800FC5D8_name_81();
    func_800EBAD4_name_81(GwSystem.message_speed);
    _ClearFlag(0xC);
    D_800D6A48_main = 0;
}

void func_800FC030_name_81(void) {
    omOvlHisData *overlay;

    D_800D4190_main.stat = 1;
    if (mbovlhisidx != 0) {
        mbovlhisidx--;
        overlay = &mbovlhis[mbovlhisidx];
        omOvlCallEx(overlay->overlayID, overlay->event, overlay->stat);
        return;
    }
    if (D_800CD2A0_main.unk_02 != 0) {
        D_800D4190_main.stat = 0;
        omOvlCallEx(D_80101A54_name_81[GwSystem.current_board_index], 2, 0x4190);
        return;
    }
    if (D_800D6A48_main != 0) {
        _SetFlag(0xC);
    } else {
        _ClearFlag(0xC);
    }
    omOvlReturnEx(1);
}

void func_800FC108_name_81(void) {
    D_800CD2A0_main.unk_02 = 0;
}

s16 func_800FC114_name_81(void) {
    return D_800D4190_main.stat;
}

void func_800FC120_name_81(s16 arg0) {
    s16 temp_v0 = mbovlhisidx;

    mbovlhis[mbovlhisidx].event = arg0;
    mbovlhisidx = temp_v0 + 1;
    if (mbovlhisidx >= 5) {
        mbovlhisidx = 4;
    }
    func_800FBF00_name_81(-2, 3, 0x4190);
    omOvlReturnEx(1);
}

s32 func_800FC18C_name_81(void) {
    return mbGameMode;
}

void func_800FC198_name_81(omObjData *obj) {
    s32 *temp_s0 = HuPrcCurrentGet()->user_data;

    while (1) {
        if (
            (func_800F37B8_name_81(temp_s0[0]) == 0) &&
            (D_800A12D8_main == 0) &&
            ((GwSystem.current_player_index != temp_s0[0]) || (D_800A12D4_main == 0)) &&
            (D_800C9520_main[GwPlayer[temp_s0[0]].pad] & 0x20)) {
            func_8004ACE0_main(0x2BD, temp_s0[0]);
        }
        HuPrcVSleep();
    }
}

void func_800FC260_name_81(s32 arg0, s16 arg1) {
    Process *temp_v0_2;
    UnkOvl81_1 *temp_v0_3;
    s32 frontPartnerID;
    s32 backPartnerID;
    Object *playerObj;
    s32 i;

    func_800E8D10_name_81();
    func_800E4F50_name_81(hvq_data_ROM_START);

    if (arg0 >= 0) {
        MBDBackLoad(arg0);
    }

    func_800E94D0_name_81();

    if (arg1 >= 0) {
        func_800E9B10_name_81(0x13, arg1);
    }

    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800F3DFC_name_81(0);
    func_800F3DFC_name_81(1);

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        func_800D8944_name_81(MBDGetPlayerStruct(i)->player_obj);
        playerObj = MBDGetPlayerStruct(i)->player_obj;
        playerObj->flags |= 2;
        func_800D8E88_name_81(MBDGetPlayerStruct(i)->player_obj);
    }

    func_8001FDE8_main(MBDGetPlayerStruct(0)->player_obj->omObj1->model[0]);
    func_8001FDE8_main(MBDGetPlayerStruct(1)->player_obj->omObj1->model[0]);
    func_800F8C68_name_81(0);
    func_800F8C68_name_81(1);
    func_800F4300_name_81();
    func_800DF1B0_name_81();
    func_800E0CEC_name_81();
    func_800E2870_name_81();
    func_800F6390_name_81();

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        frontPartnerID = GwPlayer[i].stats.partners.frontID;
        backPartnerID = GwPlayer[i].stats.partners.backID;
        GwPlayer[i].stats.partners.frontID = PARTNER_KOOPA; //?
        GwPlayer[i].stats.partners.backID = PARTNER_KOOPA;  //?
        func_800F5BB4_name_81(i);
        func_800F5EB0_name_81(i);
        GwPlayer[i].stats.partners.frontID = frontPartnerID;
        GwPlayer[i].stats.partners.backID = backPartnerID;
        func_800F5BB4_name_81(i);
        func_800F5EB0_name_81(i);
    }

    func_800DAB1C_name_81();
    func_8005A6B0_main();
    func_800EB664_name_81();

    D_80105494_name_81 = -1;
    D_800D1360.unk_20 = 0;
    D_80105496_name_81 = 0;
    func_800F4080_name_81();
    D_80101A8C_name_81 = NULL;
    D_80101A90_name_81 = 0;
    D_80101A94_name_81 = 0;
    D_80101A98_name_81 = 0;
    for (i = 0; i < 2; i++) {
        temp_v0_2 = omAddPrcObj(func_800FC198_name_81, 0, 0, 0x40);
        temp_v0_3 = HuMemMemoryAlloc(temp_v0_2->heap, sizeof(UnkOvl81_1));
        temp_v0_2->user_data = temp_v0_3;
        temp_v0_3->unk_00 = i;
        omPrcSetStatBit(temp_v0_2, 0xA0);
    }
}

void func_800FC4E4_name_81(void) {
    func_800DBEB0_name_81();
    func_800F64FC_name_81();
    func_800E28B0_name_81();
    func_800E0E38_name_81();
    func_800DF210_name_81();
    func_800F4314_name_81();
    func_8005F524_main();
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    func_800E9D9C_name_81();
    func_800E9564_name_81();
    MBDBackKill();
    MBDBackClose();
    func_800E4FF4_name_81();
    func_800E90B4_name_81();

    if (D_80101A8C_name_81 != NULL) {
        D_80101A8C_name_81();
    }

    func_800FD55C_name_81();
}

// file split? many setters here
void func_800FC590_name_81(s32 arg0) {
    D_80101A98_name_81 = arg0;
}

void func_800FC59C_name_81(s32 arg0) {
    D_80101A94_name_81 = arg0;
}

void func_800FC5A8_name_81(process_func arg0) {
    D_80101A90_name_81 = arg0;
}

void func_800FC5B4_name_81(void (*arg0)(void)) {
    D_80101A8C_name_81 = arg0;
}

void func_800FC5C0_name_81(s32 arg0) {
    D_800CC0B8_main = arg0;
}

s16 func_800FC5CC_name_81(void) {
    return D_800CC0B8_main;
}

void func_800FC5D8_name_81(void) {
    GW_PLAYER *player;
    GW_SYSTEM *system = &GwSystem;
    GW_COMMON *common = &GwCommon;
    s32 i, j;

    mbGameMode = 0;
    mbWalkNum = 0;
    D_800CE1D0_main = 0;
    D_800D124C_main = 0;
    D_80101A50_name_81 = 0;
    D_800C9938_main = 1.4f;
    func_800DF154_name_81();
    func_800DAAB0_name_81();
    D_800A12C8_main = -1;
    D_800C9930_main = -1;
    D_800CE206 = 0;
    D_800A12D4_main = 1;
    D_800A12D8_main = 0;

    if (((common->unk9E == 3) | (common->unk9E == 1)) != 0) {
        common->unk9E = 2;
    }

    if (common->unk9F == 3) {
        common->unk9F = 0;
    }

    if (common->unkA0 == 3) {
        common->unkA0 = 1;
    }

    if (common->unkA1 == 3) {
        common->unkA1 = 1;
    }

    if (common->unkA2 == 3) {
        common->unkA2 = 0;
    }

    system->save_mode = common->unk9E;
    system->show_minigame_explanations = common->unk9F;
    system->message_speed = common->unkA0;
    system->walk_speed = common->unkA1;
    system->show_com_minigames = common->unkA2;

    if (GWBoardFlagCheck(1) == 0) {
        system->current_turn = 1;
        system->current_player_index = 0;
        system->minigame_index = 0;

        if (system->total_turns == -1U) { //?
            system->total_turns = 50;
        } else {
            system->total_turns = 20;
        }

        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            player = MBDGetPlayerStruct(i);
            player->coin = 0;
            player->gamePrize = 0;
            player->coinPrize = 0;
            player->stats.partners.frontID = -1;
            player->stats.partners.backID = -1;
            player->stats.partners.frontPoweredUp = 0;
            player->stats.partners.backPoweredUp = 0;
            player->stats.partners.frontHp = 0;
            player->stats.partners.backHp = 0;
            player->stats.partners.frontCost = 0;
            player->stats.partners.backCost = 0;
            player->stats.partners.frontPower = 0;
            player->stats.partners.backPower = 0;

            for (j = 0; j < ARRAY_COUNT(player->itemNo); j++) {
                player->itemNo[j] = -1;
            }

            player->itemTurn = 0;
            player->rev = 0;
        }

#ifdef BUG_FIX
        for (i = 0; i < ARRAY_COUNT(GwSystem.boardData.halfWordBytes); i++) {
            GwSystem.boardData.halfWordBytes[i] = 0;
        }
#else
        // potentially this used to be 16 in length, then was shortened?
        for (i = 0; i < 16; i++) {
            GwSystem.boardData.halfWordBytes[i] = 0;
        }
#endif

        GWBoardFlagClear(0x12);
        GWBoardFlagClear(0x13);
        GWBoardFlagClear(0x14);
        GWBoardFlagClear(0x15);
        GWBoardFlagClear(0x16);
        GWBoardFlagClear(0x17);
        GWBoardFlagClear(1);
        GWBoardFlagClear(0x11);

        if (GwSystem.playMode & 4) {
            if (_CheckFlag(0x28) != 0) {
                GWBoardFlagSet(0);
                return;
            }
            GWBoardFlagClear(0);
            return;
        }

        if (_CheckFlag(0x17) != 0) {
            GWBoardFlagSet(0);
            return;
        }

        GWBoardFlagClear(0);
    }
}

void func_800FC888_name_81(s32 arg0) {
    D_8010549E_name_81 = arg0;
}

s16 func_800FC894_name_81(void) {
    return D_8010549E_name_81;
}

void func_800FC8A0_name_81(Vec *arg0) {
    D_801054A0_name_81 = *arg0;
}

void func_800FC8C4_name_81(Vec *arg0) {
    D_801054AC_name_81 = arg0;
}

Vec *func_800FC8D0_name_81(void) {
    return D_801054AC_name_81;
}

void func_800FC8DC_name_81(UnkE3CD0 *arg0) {
    D_801054B0_name_81 = arg0;
}

void func_800FC8E8_name_81(void) {
    Vec2f sp10;
    Vec sp18;

    while (1) {
        switch (D_8010549E_name_81) {
            case 1:
                MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
                break;
            case 2:
                MBDCameraPos3DSet(&D_801054A0_name_81);
                break;
            case 4:
                MBDCameraPos3DSet(D_801054AC_name_81);
                break;
            case 5:
                HuVecCopy3F(&sp18, &D_801054B0_name_81->unk_0C);
                sp18.y += D_801054B0_name_81->unk_30;
                MBDCameraPos3DSet(&sp18);
                break;
            case 3:
                MBDCameraPos2DGet(&sp10);
                MBDCameraPos2DSet(&sp10);
                break;
        }
        HuPrcVSleep();
    }
}

void func_800FC9FC_name_81(void) {
    GW_SYSTEM *system = &GwSystem;

    system->current_player_index++;
    if ((system->current_player_index >= 2) && (system->current_player_index = 0, (mbTurnOnF == 0))) {
        system->current_turn++;
        if ((system->current_board_index == 4) && (system->total_turns == 50)) {
            if (system->current_turn > 20) {
                system->current_turn = 19;
            }
        } else if (system->current_turn >= 20) {
            system->current_turn = 20;
        }
    }
}

void func_800FCAB4_name_81(void) {
    do {
        HuPrcVSleep();
    } while (WipeStatGet() != 0);

    while (1) {
        HuPrcVSleep();
        if (D_800D530C_main == 0) {
            if (D_80105494_name_81 < 0) {
                continue;
            }
        }

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }

        if (D_80105496_name_81 != 0) {
            HuAudSeqFadeOut(0x5A);
            D_800C9930_main = D_800C9930_main;
            if (D_800C9930_main != -1) {
                func_800039A4_main(D_800C9930_main, 0x5A);
                D_800C9930_main = -1;
                func_8004A950_main();
            }
            if (D_800CE206 != 0) {
                func_8004A950_main();
                D_800CE206 = 0;
            }
        }

        WipeCreateOut((s32)D_800D1360.unk_20, 0x10);
        HuPrcSleep(0x11);
        func_800FC4E4_name_81();
        if (D_80105494_name_81 & 0x20) {
            D_800D6A48_main = 1;
            if (GwSystem.current_board_index == 5) {
                _CheckFlag(9);
            }
            func_800FBF00_name_81(0x62, 0, 0x4190);
            func_800FC108_name_81();
        }
        if (D_80105494_name_81 & 1) {
            func_800FC9FC_name_81();
        }
        if (D_80105494_name_81 & 2) {
            func_800FBF00_name_81(0x70, 0, 0x192);
        }
        if (D_80105494_name_81 & 8) {
            func_800FBF00_name_81(D_80105498_name_81, D_8010549C_name_81, 0x192);
        }
        omOvlReturnEx(1);
        omOvlKill();
        HuPrcVSleep();
    }
}

void func_800FCC84_name_81(s16 arg0) {
    arg0 -= 2;

    switch (arg0) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 6:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            HuAudFXPlay(0x101);
            break;
    }
}

void func_800FCCCC_name_81(s16 arg0) {
    arg0 -= 2;

    switch (arg0) {
        case 3:
            if (GwSystem.current_board_index == 5) {
                HuAudFXPlay(0x1D4);
            } else {
                HuAudFXPlay(0x1D3);
            }
            break;
        case 8:
            HuAudFXPlay(0x1D2);
            break;
        case 1:
            HuAudFXPlay(0x12E);
            break;
        case 0:
        case 4:
        case 6:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            HuAudFXPlay(0x108);
    }
}

// duel n8
SpaceData *MBDMasuGet(s16 spaceIdx);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
void func_800EB680_name_81(s16 playerIndex, s16 spaceIdx, Vec *out);
void func_800EB708_name_81(Vec *from, Vec *to, Vec *dir);
Process *func_800EBF2C_name_81(Vec *from, Vec *to, Vec *out, s32 frames);
f32 func_800D76D0_name_81(Vec *vec);
extern Vec D_801054B8_name_81[];
extern Vec D_801054D0_name_81[][2];
extern f32 D_80101AA4_name_81[][2];
extern f32 D_80101ACC_name_81[][2];

void func_800FCD44_name_81(s32 playerIndex, Vec *out) {
    Vec sp10;
    Vec sp20;
    Vec sp30;
    Vec sp40;
    Vec sp50;
    GW_PLAYER *player;
    f32 len;

    player = MBDGetPlayerStruct(playerIndex);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &sp10);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &sp20);
    func_800EB680_name_81(playerIndex, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &sp30);
    func_800EB708_name_81(&sp10, &sp20, &sp40);
    len = HuVecGetLength3F(&sp40);
    func_800EB708_name_81(&sp10, &sp30, &sp50);
    HuVecAdd(&sp40, &sp40, &sp50);
    if (HuVecGetLength3F(&sp40) <= len) {
        func_800EB708_name_81(&sp10, &sp20, &sp40);
        func_800D7934_name_81(&sp40, 90.0f);
        func_800D7828_name_81(&sp40);
        if (GwSystem.current_board_index == 4 && player->clink == 6 && player->cidx == 0) {
            HuVecMulScalar(&sp40, 24.0f, &sp40);
        } else {
            HuVecMulScalar(&sp40, 16.968f, &sp40);
        }
    } else {
        func_800D7828_name_81(&sp40);
        HuVecMulScalar(&sp40, 24.0f, &sp40);
    }
    HuVecCopy3F(out, &sp40);
}

#ifdef NON_MATCHING
// masked 0: player and shareSpace swap s2/s3
void func_800FCF50_name_81(s32 playerIndex, s32 frames) {
    Vec sp10;
    Vec sp20;
    Vec sp30;
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *curPlayer;
    SpaceData *space;
    Object *partner;
    s32 shareSpace;
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(playerIndex);
    space = MBDMasuGet(MBDMasuLinkMasuIdGet(player->clink, player->cidx));
    if (system->current_player_index == playerIndex) {
        HuVecCopy3F(&player->player_obj->coords, &space->coords);
        func_800ED214_name_81(playerIndex);
        return;
    }
    shareSpace = 0;
    curPlayer = MBDGetPlayerStruct(system->current_player_index);
    if (player->clink == curPlayer->clink) {
        shareSpace = player->cidx == curPlayer->cidx;
    }
    HuVecCopy3F(&D_801054B8_name_81[playerIndex], &space->coords);
    if (shareSpace == 1) {
        func_800FCD44_name_81(playerIndex, &sp10);
        HuVecAdd(&D_801054B8_name_81[playerIndex], &D_801054B8_name_81[playerIndex], &sp10);
    }
    if (frames < 2) {
        HuVecCopy3F(&player->player_obj->coords, &D_801054B8_name_81[playerIndex]);
    } else {
        func_800EBF2C_name_81(&player->player_obj->coords, &D_801054B8_name_81[playerIndex], &player->player_obj->coords, frames);
    }
    func_800ECF1C_name_81(playerIndex, &sp20, &sp30);
    if (player->stats.partners.frontID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
        HuVecCopyXYZ(&D_801054D0_name_81[playerIndex][0], D_801054B8_name_81[playerIndex].x + sp20.x,
                     D_801054B8_name_81[playerIndex].y + sp20.y, D_801054B8_name_81[playerIndex].z + sp20.z);
        if (frames < 2) {
            HuVecCopy3F(&partner->coords, &D_801054D0_name_81[playerIndex][0]);
        } else {
            func_800EBF2C_name_81(&partner->coords, &D_801054D0_name_81[playerIndex][0], &partner->coords, frames);
        }
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
        HuVecCopyXYZ(&D_801054D0_name_81[playerIndex][1], D_801054B8_name_81[playerIndex].x + sp30.x,
                     D_801054B8_name_81[playerIndex].y + sp30.y, D_801054B8_name_81[playerIndex].z + sp30.z);
        if (frames < 2) {
            HuVecCopy3F(&partner->coords, &D_801054D0_name_81[playerIndex][1]);
        } else {
            func_800EBF2C_name_81(&partner->coords, &D_801054D0_name_81[playerIndex][1], &partner->coords, frames);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/E3CD0", func_800FCF50_name_81);
#endif

// if player should jump to next space
s32 func_800FD298_name_81(s32 playerIndex) {
    Vec sp10;
    GW_PLAYER *curPlayer;
    GW_PLAYER *player;
    f32 angle;
    SpaceData *space;
    s32 nextCount;
    s32 curCount;
    s32 i;

    curPlayer = MBDGetPlayerStruct(playerIndex);
    nextCount = 0;
    curCount = 0;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (i == playerIndex) {
            continue;
        }
        player = MBDGetPlayerStruct(i);
        if (curPlayer->clink == player->clink) {
            curCount += curPlayer->cidx == player->cidx;
        }
        if (curPlayer->nlink == player->clink) {
            nextCount += curPlayer->nidx == player->cidx;
        }
    }

    space = MBDMasuGet(MBDMasuLinkMasuIdGet(curPlayer->clink, curPlayer->cidx));
    HuVecSubtract(&sp10, &MBDMasuGet(MBDMasuLinkMasuIdGet(curPlayer->nlink, curPlayer->nidx))->coords, &space->coords);
    angle = func_800D76D0_name_81(&sp10);
    if ((curCount == 0) || (!(D_80101AA4_name_81[curCount][0] < angle)) || (!(angle <= D_80101AA4_name_81[curCount][1]))) {
        if (nextCount != 0) {
            if (D_80101ACC_name_81[nextCount][0] < 0.0f) {
                angle -= 360.0f;
            }
            if (!(D_80101ACC_name_81[nextCount][0] < angle) || (!(angle <= D_80101ACC_name_81[nextCount][1]))) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}

s32 func_800FD498_name_81(void) {
    s32 var_a0 = (GwSystem.current_turn - 1) / 5;

    if (var_a0 > 3) {
        var_a0 = 3;
    }
    return D_80101AF4_name_81[var_a0];
}

void func_800FD4DC_name_81(void) {
    if (D_80101AF8_name_81 == 0) {
        D_80101AF8_name_81 = func_800E1824_name_81(2, 0xAE, 1);
    }
    if (D_80101B00_name_81 == 0) {
        D_80101B00_name_81 = func_800E1824_name_81(3, 0xCA, 1);
    }
    if (D_80101B04_name_81 == 0) {
        D_80101B04_name_81 = func_800E1824_name_81(0xD, 0xBC, 1);
    }
}

void func_800FD55C_name_81(void) {
    if (D_80101AF8_name_81 != 0) {
        func_800E1854_name_81(D_80101AF8_name_81);
        D_80101AF8_name_81 = 0;
    }
    if (D_80101AFC_name_81 != 0) {
        func_800E1854_name_81(D_80101AFC_name_81);
        D_80101AFC_name_81 = 0;
    }
    if (D_80101B00_name_81 != 0) {
        func_800E1854_name_81(D_80101B00_name_81);
        D_80101B00_name_81 = 0;
    }
    if (D_80101B04_name_81 != 0) {
        func_800E1854_name_81(D_80101B04_name_81);
        D_80101B04_name_81 = 0;
    }
}

void func_800FD5F0_name_81(void) {
    mbGameMode = 7;
    D_800D1360.unk_20 = 8;
    func_800FD55C_name_81();
}

void func_800FD620_name_81(void) {
    Process *temp_s1;
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    temp_s1 = HuPrcCurrentGet();
    mbItemBtnF = 0;
    func_8001FDE8_main(temp_s0->player_obj->omObj1->model[0]);
    func_800F8C68_name_81(GwSystem.current_player_index);
    D_800A12D4_main = 0;
    HuPrcChildLink(temp_s1, func_800E0888_name_81());
    HuPrcChildWait();
    mbGameMode = 10;
    D_80105494_name_81 = 2;
    D_80105496_name_81 = 1;
    D_800D1360.unk_20 = 10;
    GwPlayer[0].group = 0;
    GwPlayer[1].group = 1;
    GwPlayer[2].group = 2;
    GwPlayer[3].group = 3;
}

// duel n9
extern s32 D_80105490_name_81;
extern u8 D_80101A9C_name_81[];
extern u8 D_80101AA0_name_81[];
extern s32 D_800A12CC_main;
void func_80050200_main(s32);
void func_80050E84_main(void);
void func_800D9F90_name_81(s32);
void func_800DB4DC_name_81(s32);
void func_800DB624_name_81(s32, s8);
s32 func_800DC0B4_name_81(s32);
Process *func_800DC324_name_81(s32);
void func_800E14B0_name_81(s32, s32);
void func_800E14D8_name_81(s32, s32);
Process *func_800E39AC_name_81(s32);
Process *func_800E4A74_name_81(s32);
void func_800EA388_name_81(s16);
s32 func_800EA4D4_name_81(s16, s16);
void func_800EA698_name_81(s16);
s16 func_800EA6A4_name_81(void);
void func_800EA788_name_81(s16, s32);
void func_800EA7D4_name_81(void);
s32 func_800EA848_name_81(s16);
s32 func_800EA940_name_81(s32);
void func_800EA97C_name_81(void);
void func_800EAD08_name_81(s32);
void func_800EADBC_name_81(s32, u32, u32, u32, u32, u32);
void func_800EAF70_name_81(s32);
void func_800EAF94_name_81(void);
void func_800EB140_name_81(s32, s32);
void func_800EB164_name_81(s16, s32);
void func_800EB7BC_name_81(Vec *);
void func_800EB7D8_name_81(s16);
Process *func_800EBC60_name_81(Vec *, Vec *, Vec *, s32);
Process *func_800EC1E4_name_81(Vec *, Vec *, Vec *, f32);
void func_800ECC34_name_81(s16, f32);
void func_800ECE38_name_81(s32);
void func_800EDD50_name_81(Vec *);
void func_800EDDBC_name_81(void);
Process *func_800EDEC4_name_81(Object *, f32, f32);
void func_800EDF48_name_81(void);
void func_800EDF78_name_81(void);
void func_800EE0F4_name_81(s32);
void func_800EE468_name_81(s32);
void func_800EE74C_name_81(s32);
void func_800EEC40_name_81(Vec *);
void func_800EF7C8_name_81(Object *, f32, f32);
void func_800F3880_name_81(s32, s16, s16);
void func_800F38DC_name_81(s32, s16, u16);
void func_800F397C_name_81(s32, s16, s16, s16, u16);
void func_800F3A04_name_81(s32, s16, s16, s16, u16);
void func_800F3AF4_name_81(s32, f32);
Process *func_800F41DC_name_81(void); /* DBE50.c */
Process *func_800F429C_name_81(void); /* DBE50.c */
s32 func_800F42C8_name_81(void);
void func_800F7378_name_81(s32, s32);
void func_800F924C_name_81(s32);
void func_800FADB4_name_81(void);
void func_800FAE18_name_81(Object *, s16, s16);
void *func_800FFC2C_name_81(s16, s16, s32);
void func_800FFCCC_name_81(void *);
void Duel_PowerUpPartners(s32);
void func_800FFA28_name_81(Vec *);

/* BFB40.c's Duel Mode board model: the player objects are these, and only curMot is read here. */
typedef struct DuelModel {
    /* 0x00 */ struct DuelModel *prev;
    /* 0x04 */ struct DuelModel *next;
    /* 0x08 */ u8 id;
    /* 0x09 */ s8 unk9;
    /* 0x0A */ u16 flags;
    /* 0x0C */ Vec coords;
    /* 0x18 */ Vec rot;
    /* 0x24 */ Vec scale;
    /* 0x30 */ Vec velocity;
    /* 0x3C */ omObjData *omObj1;
    /* 0x40 */ omObjData *omObj2;
    /* 0x44 */ s16 mtncnt;
    /* 0x46 */ s16 baseMot;
    /* 0x48 */ s16 curMot;
} DuelModel; // sizeof 0x4C

// Duel Mode's main turn loop (party mode: MBMain in ovl_80_shared_board/10C230.c)
void func_800FD6F4_name_81(void) {
    Vec sp18;
    /* Retail reuses these 0x24 bytes of the frame for unrelated locals; a union keeps that defined. */
    union {
        s16 winSize[2];           /* save prompt window size */
        Vec camPos;               /* coin space partner: camera target */
        struct {
            s32 unk00[2];
            Vec dir;              /* 0x30: direction to the player */
            s32 unk14;
            Vec rot;              /* 0x40: saved partner rotation */
        } partner;
        struct {
            s32 unk00[4];
            char buf[20];         /* 0x38: coin count text */
        } coin;
    } sp28;
    Process *diceProc;
    GW_SYSTEM *system = &GwSystem;
    Process *mainProc;
    GW_PLAYER *player;
    GW_PLAYER *rival;
    SpaceData *space;
    Object *partner;
    Object *coinPartner;
    Object *guy;
    Object *fxModels[2];
    Process *proc;
    s16 masuId;
    s16 winId;
    s32 seNo;
    s16 clink;
    s16 cidx;
    s8 tmp1;
    s8 tmp2;
    s32 ret;
    s32 amount;
    s32 rand;
    s32 roll;
    s32 coins;
    void *eff;
    u32 j;
    s32 i;

    diceProc = NULL;
    mainProc = HuPrcCurrentGet();

    while (1) {
        if ((mbGameMode == 0 || mbGameMode == 1) && system->current_player_index == 0) {
            if (!GWBoardFlagCheck(1) && system->current_turn >= 2) {
                switch (system->save_mode) {
                    case 1:
                        system->save_mode = 2;
                    case 0:
                        _SetFlag(0);
                        GWBoardFlagSet(0);
                        func_80060394_main(1, sp28.winSize, 0x5900);
                        winId = func_8005A968_main(0, 0, sp28.winSize[0], sp28.winSize[1], 0, 2);
                        func_8005BEE0_main(winId, 0);
                        func_8005B43C_main(winId, 0x5900, -1, -1);
                        func_8005BDFC_main(winId, 0);
                        while (func_8005E0C0_main(winId) != 0) {
                            HuPrcVSleep();
                        }
                        if (system->playMode & 4) {
                            _SetFlag(0x18);
                            _SetFlag(0x28);
                            func_8005035C_main(1);
                        } else {
                            _SetFlag(0x17);
                            func_80050200_main(1);
                        }
                        func_8005F364_main(winId);
                        func_80060394_main(1, sp28.winSize, 0x5901);
                        winId = func_8005A968_main(0, 0, sp28.winSize[0], sp28.winSize[1], 0, 2);
                        func_8005BEE0_main(winId, 0);
                        func_8005B43C_main(winId, 0x5901, -1, -1);
                        func_8005BDFC_main(winId, 0);
                        HuPrcSleep(0xF);
                        func_8005F364_main(winId);
                        break;
                }
            }
            GWBoardFlagClear(1);
            D_800A12D4_main = 0;
            D_80105490_name_81 = func_800EA4D4_name_81(-2, 7);
        }

        D_800A12D4_main = 1;
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            MBDGetPlayerStruct(i);
            func_800FCF50_name_81(i, 1);
        }
        player = MBDGetPlayerStruct(system->current_player_index);
        func_80050E84_main();
        GwPlayer[2].stat |= 1;
        GwPlayer[3].stat |= 1;
        masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
        MBDMasuGet(masuId);

        if (mbGameMode == 0 || mbGameMode == 1) {
            goto intro;
        }

        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }

        mbItemBtnF = 1;

        switch (mbGameMode) {
            intro:
                func_800EA4D4_name_81(-4, 7);
                func_8001FDE8_main(MBDGetPlayerStruct(0)->player_obj->omObj1->model[0]);
                func_8001FDE8_main(MBDGetPlayerStruct(1)->player_obj->omObj1->model[0]);
                func_800F8C68_name_81(0);
                func_800F8C68_name_81(1);
                func_800F38DC_name_81(-1, -1, 2);
                func_800FC888_name_81(1);
                if (D_800A12CC_main == 0) {
                    D_800C9938_main = 1.4f;
                    MBDCameraZoomSet(1.4f);
                    HuPrcChildLink(mainProc, func_800F429C_name_81());
                } else if (func_800F42C8_name_81() == 0) {
                    D_800C9938_main = 1.4f;
                    MBDCameraZoomSet(1.4f);
                    HuPrcChildLink(mainProc, func_800F429C_name_81());
                } else {
                    D_800C9938_main = 1.4f;
                    HuPrcChildLink(mainProc, MBDCameraZoomMotStart(1.4f));
                }
                HuPrcChildWait();
            default:
                HuPrcSleep(4);
                func_800FFAE0_name_81(-1, 3);
                HuPrcChildLink(mainProc, func_800E39AC_name_81(system->current_player_index));
                HuPrcChildWait();
                func_800EA4D4_name_81(-5, 7);
            case 7:
            diceRoll:
                func_800FD4DC_name_81();
                D_800C9938_main = 1.7f;
                HuPrcChildLink(mainProc, MBDCameraZoomMotStart(1.7f));
                if (D_800D124C_main == 0) {
                    diceProc = func_800DC324_name_81(system->current_player_index);
                }
                HuPrcChildWait();
                HuPrcSleep(1);
                mbCameraBtnF = 1;
                mbItemBtnF = 1;
                D_800D51F8_main = 1;
                if (D_800D124C_main != 0) {
                    GWBoardFlagClear(0x11);
                    func_800D9F90_name_81(system->current_player_index);
                }
                HuPrcChildLink(mainProc, diceProc);
                HuPrcChildWait();
                func_800FD55C_name_81();
                mbCameraBtnF = 0;
                D_800D51F8_main = 0;
                mbWalkNum = func_800DC0B4_name_81(system->current_player_index);
                func_800ECE38_name_81(system->current_player_index);
                if (!(player->rev & 2)) {
                    func_800F3A04_name_81(-1, 0, 0, 5, 2);
                } else {
                    func_800F3A04_name_81(-1, 0, 0, 5, 6);
                }

                while (mbWalkNum != 0) {
                    func_800EA4D4_name_81(masuId, 8);
                    if (D_80101A94_name_81 != 0) {
                        rival = MBDGetPlayerStruct((s8)(system->current_player_index ^ 1));
                        ret = ((s32 (*)(void))D_80101A94_name_81)();
                        if (ret != -1) {
                            func_800F38DC_name_81(-1, -1, 2);
                            func_800DB3E0_name_81(player->turn);
                            D_800A12D8_main = 1;
                            func_800F924C_name_81(ret);
                            D_800A12D8_main = 0;
                            if (mbTurnOnF != 0) {
                                player->star = 5;
                                rival->star = 5;
                            }
                            if (rival->star <= 0 || player->star <= 0) {
                                HuPrcChildLink(mainProc, MBDCameraZoomMotStart(1.7f));
                                HuPrcChildWait();
                                goto gameEnd;
                            }
                            func_800DADA0_name_81(player->turn);
                            HuPrcChildLink(mainProc, MBDCameraZoomMotStart(1.7f));
                            HuPrcChildWait();
                            if (!(player->rev & 2)) {
                    func_800F3A04_name_81(-1, 0, 0, 5, 2);
                } else {
                    func_800F3A04_name_81(-1, 0, 0, 5, 6);
                }
                        }
                    }

                    clink = player->clink;
                    cidx = player->cidx;
                    player->clink = player->nlink;
                    player->cidx = player->nidx;
                    func_800FCF50_name_81((s8)(system->current_player_index ^ 1), (system->walk_speed * 7) + 8);
                    player->clink = clink;
                    player->cidx = cidx;

                    space = MBDMasuGet(MBDMasuLinkMasuIdGet(player->nlink, player->nidx));
                    if (((DuelModel *)player->player_obj)->curMot != 0) {
                        if (!(player->rev & 2)) {
                    func_800F3A04_name_81(-1, 0, 0, 5, 2);
                } else {
                    func_800F3A04_name_81(-1, 0, 0, 5, 6);
                }
                    }
                    if (system->current_board_index == 4 && space->unk_02 == 2) {
                        seNo = HuAudFXPlay(0x1EC);
                        func_800F38DC_name_81(-1, -1, 2);
                        func_800F3AF4_name_81(-1, 1.0f);
                        eff = func_800FFC2C_name_81(-1, 1, 5);
                        func_800ECC34_name_81(system->current_player_index, 0.73f);
                        func_800FFCCC_name_81(eff);
                        HuAudFXStop(seNo);
                        HuPrcSleep(0xA);
                    } else {
                        switch (system->walk_speed) {
                            case 0:
                                func_800F3AF4_name_81(-1, 1.5f);
                                func_800ECC34_name_81(system->current_player_index, 5.0f);
                                break;
                            case 1:
                                func_800F3AF4_name_81(-1, 1.0f);
                                func_800ECC34_name_81(system->current_player_index, 4.0f);
                                break;
                            case 2:
                                func_800F3AF4_name_81(-1, 0.75f);
                                func_800ECC34_name_81(system->current_player_index, 3.0f);
                                break;
                        }
                        func_800F3AF4_name_81(-1, 1.0f);
                    }

                    player->blink = player->clink;
                    player->bidx = player->cidx;
                    player->clink = player->nlink;
                    player->cidx = player->nidx;
                    if (!(player->rev & 1)) {
                        player->nidx = player->nidx + 1;
                    } else {
                        player->nidx = player->nidx - 1;
                    }

                    masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
                    space = MBDMasuGet(masuId);
                    func_800EA698_name_81(masuId);
                    switch (space->space_type) {
                        case 2:
                        case 3:
                        case 5:
                        case 6:
                        case 8:
                        case 10:
                        case 11:
                        case 12:
                        case 13:
                        case 14:
                        case 15:
                        case 16:
                        case 17:
                        case 18:
                            func_800DB4DC_name_81(system->current_player_index);
                            mbWalkNum--;
                            func_800EA388_name_81(masuId);
                            break;
                    }
                    if (mbWalkNum != 0) {
                        func_800FCC84_name_81(space->space_type);
                    } else {
                        func_800FCCCC_name_81(space->space_type);
                    }
                    D_80105490_name_81 = func_800EA4D4_name_81(masuId, 1);
                    if (D_80105494_name_81 < 0) {
                        continue;
                    }
                    mbGameMode = 2;
                    HuPrcSleep(-1);
                    case 2:
                        if (D_80105490_name_81 & 1) {
                            masuId = func_800EA6A4_name_81();
                            D_80105490_name_81 = func_800EA4D4_name_81(masuId, 2);
                            if (D_80105494_name_81 >= 0) {
                                mbGameMode = 3;
                                HuPrcSleep(-1);
                            }
                        }
                    case 3:
                    walkStep:
                        if (D_80105490_name_81 & 2) {
                            mbWalkNum = 0;
                            continue;
                        }
                        func_800DADA0_name_81(system->current_player_index);
                        HuPrcSleep(0xA);
                }

                if (D_80101A50_name_81 == -1) {
                    D_80101A50_name_81 = 0;
                } else if ((player->stats.partners.frontID == 7 || player->stats.partners.backID == 7) &&
                           D_800D124C_main == 0 && D_800CE1D0_main == 0 &&
                           (func_800EFE20_name_81(100.0f) < 50 || D_80101A50_name_81 != 0)) {
                    D_80101A50_name_81 = 0;
                    func_800EB7BC_name_81(&sp18);
                    func_800EBC60_name_81(&player->player_obj->rot, &sp18, &player->player_obj->rot, 8);
                    func_800F38DC_name_81(-1, -1, 2);
                    func_800FAD04_name_81(7);
                    if (player->stats.partners.backID == 7) {
                        partner = MBDGetPlayerPartnerRef(system->current_player_index, PARTNER_BACK);
                    } else {
                        partner = MBDGetPlayerPartnerRef(system->current_player_index, PARTNER_FRONT);
                    }
                    func_800EB708_name_81(&partner->coords, &player->player_obj->coords, &sp28.partner.dir);
                    HuVecCopy3F(&sp28.partner.rot, &partner->rot);
                    func_800EBC60_name_81(&partner->rot, &sp28.partner.dir, &partner->rot, 2);
                    func_800FAE18_name_81(partner, 2, 0);
                    HuPrcSleep(5);
                    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
                    func_800DB624_name_81(system->current_player_index, 2);
                    diceProc = func_800DC324_name_81(system->current_player_index);
                    GWBoardFlagSet(0x11);
                    func_800EFABC_name_81(partner);
                    func_800FAE18_name_81(partner, 3, 2);
                    func_800EAD08_name_81(0x4F0D);
                    func_800EAF70_name_81(system->current_player_index);
                    func_800EAF94_name_81();
                    func_800D918C_name_81(partner, -1, 0, 5, 2);
                    func_800EBC60_name_81(&partner->rot, &sp28.partner.rot, &partner->rot, 6);
                    HuPrcSleep(6);
                    func_800FADB4_name_81();
                    func_800FC888_name_81(1);
                    D_800D124C_main = 1;
                    goto diceRoll;
                }

                D_800D124C_main = 0;
                if (D_800CE1D0_main != 0) {
                    tmp1 = player->nlink;
                    tmp2 = player->nidx;
                    player->nlink = player->blink;
                    player->nidx = player->bidx;
                    player->blink = tmp1;
                    player->bidx = tmp2;
                    player->rev = 0;
                    D_800CE1D0_main = 0;
                }
                func_800F38DC_name_81(-1, -1, 2);
                masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
                switch (MBDMasuGet(masuId)->space_type) {
                    case 2:
                        func_800FFAE0_name_81(-1, 2);
                        (&GwSystem.boardData.halfWordBytes[2])[player->turn]++;
                        break;
                    case 3:
                        func_800FFAE0_name_81(-1, 3);
                        (&GwSystem.boardData.halfWordBytes[4])[player->turn]++;
                        break;
                    case 5:
                        if (system->current_board_index != 5) {
                            func_800FFAE0_name_81(-1, 1);
                        } else {
                            func_800FFAE0_name_81(-1, 3);
                        }
                        (&GwSystem.boardData.halfWordBytes[6])[player->turn]++;
                        break;
                    case 8:
                        func_800FFAE0_name_81(-1, 0);
                        (&GwSystem.boardData.halfWordBytes[8])[player->turn]++;
                        break;
                    case 10:
                        func_800FFAE0_name_81(-1, 2);
                        (&GwSystem.wackyWatchUsedState)[player->turn]++;
                        break;
                    case 6:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                        (&GwSystem.slow_dice_flags)[player->turn]++;
                        break;
                }

                mbGameMode = 4;
                D_80105490_name_81 = func_800EA4D4_name_81(masuId, 3);
                if (D_80105494_name_81 < 0) {
                    goto landed;
                }
                HuPrcSleep(-1);
            case 4:
                if (D_80105490_name_81 & 1) {
                    D_80105490_name_81 = func_800EA4D4_name_81(func_800EA6A4_name_81(), 4);
                    if (D_80105494_name_81 >= 0) {
                        mbGameMode = 5;
                        HuPrcSleep(-1);
                    }
                }
            case 5:
                HuPrcSleep(0x1E);
            landed:
                func_800EB7BC_name_81(&sp18);
                func_800EBC60_name_81(&player->player_obj->rot, &sp18, &player->player_obj->rot, 8);
                masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
                space = MBDMasuGet(masuId);

                switch ((s32)space->space_type) {
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                        amount = func_800FD498_name_81();
                        if (space->space_type - 11 == GwPlayer[system->current_player_index].chr) {
                            func_800FFAE0_name_81(-1, 1);
                            func_800E14D8_name_81(system->current_player_index, amount);
                            func_800F7378_name_81(system->current_player_index, amount);
                        coinDone:
                            HuPrcSleep(0x1E);
                            goto spaceDone;
                        }
                        func_800FFAE0_name_81(-1, 2);
                        if (player->stats.partners.frontID == 2 || player->stats.partners.backID == 2) {
                            if (player->stats.partners.backID == 2) {
                                coinPartner = MBDGetPlayerPartnerRef(system->current_player_index, PARTNER_BACK);
                            } else {
                                coinPartner = MBDGetPlayerPartnerRef(system->current_player_index, PARTNER_FRONT);
                            }
                            HuPrcChildLink(mainProc, MBDCameraZoomMotStart(2.0f));
                            HuPrcChildWait();
                            HuVecCopy3F(&sp28.camPos, &player->player_obj->coords);
                            func_800FC888_name_81(4);
                            func_800FC8C4_name_81(&sp28.camPos);
                            HuPrcChildLink(mainProc, func_800EC1E4_name_81(&sp28.camPos, &coinPartner->coords, &sp28.camPos, 2.0f));
                            HuPrcChildWait();
                            func_800EB7BC_name_81(&sp18);
                            func_800EBC60_name_81(&coinPartner->rot, &sp18, &coinPartner->rot, 8);
                            HuPrcSleep(8);
                            func_800FAD04_name_81(2);
                            HuAudFXPlay(0x298);
                            func_800FAE18_name_81(coinPartner, 1, 0);
                            func_800EFABC_name_81(coinPartner);
                            func_800D90D0_name_81(coinPartner, -1, 2);
                            func_800FADB4_name_81();
                            func_800EAFC4_name_81(0x1F1C);
                            func_800FC888_name_81(3);
                            goto spaceDone;
                        }
                        if (GwPlayer[system->current_player_index].coin == 0) {
                            amount = 0;
                            func_800EAFC4_name_81(0x1F1B);
                        } else if (GwPlayer[system->current_player_index].coin < amount) {
                            amount = GwPlayer[system->current_player_index].coin;
                        }
                        if (amount == 0) {
                            goto spaceDone;
                        }
                        func_800E14D8_name_81(system->current_player_index, -amount);
                        func_800F7378_name_81(system->current_player_index, -amount);
                        HuPrcSleep(0x1E);
                        func_800E14B0_name_81(func_800EA848_name_81(masuId), amount);
                        func_800F7378_name_81(func_800EA848_name_81(masuId), amount);
                        goto coinDone;

                    case 6:
                        HuPrcSleep(8);
                        func_800EA788_name_81(masuId, system->current_player_index);
                        func_800EA7D4_name_81();
                        func_800EA97C_name_81();
                        HuAudFXPlay(0x201);
                        goto spaceDone;

                    case 2:
                        if (D_80101A90_name_81 == NULL) {
                            goto spaceDone;
                        }
                        HuPrcChildLink(mainProc, omAddPrcObj(D_80101A90_name_81, 0x4800, 0, 0));
                        HuPrcChildWait();
                        goto spaceDone;

                    case 3:
                        HuPrcSleep(8);
                        guy = func_800D8010_name_81(0x3D, NULL);
                        func_800D8944_name_81(guy);
                        HuVecCopy3F(&guy->coords, &player->player_obj->coords);
                        guy->velocity.x = 100.0f;
                        do {
                            guy->velocity.x -= 2.0f;
                            HuPrcVSleep();
                        } while (guy->velocity.x >= 30.0f);
                        proc = func_800EDEC4_name_81(guy, 5.0f, 2.0f);
                        if (GwPlayer[system->current_player_index].coin != 0) {
                            HuAudFXPlay(0x2A1);
                            func_800EB140_name_81(0xA, 0x2F00);
                            GwPlayer[system->current_player_index].gameCoin = GwPlayer[system->current_player_index].coin;
                            func_800E14D8_name_81(system->current_player_index, -GwPlayer[system->current_player_index].coin);
                            func_800F7378_name_81(system->current_player_index, -GwPlayer[system->current_player_index].coin);
                            HuPrcSleep(0x1E);
                            func_800EB140_name_81(0xA, 0x2F02);
                            omDelPrcObj(proc);
                            while (guy->velocity.x >= 10.0f) {
                                guy->velocity.x -= 2.0f;
                                HuPrcVSleep();
                            }
                            func_800EF7C8_name_81(guy, 2.0f, 0.0001f);
                            func_800EF7C8_name_81(player->player_obj, 2.0f, 0.0001f);
                            HuPrcSleep(0x1E);
                        } else {
                            HuAudFXPlay(0x2A1);
                            func_800EB140_name_81(0xA, 0x2F01);
                            omDelPrcObj(proc);
                            while (guy->velocity.x <= 100.0f) {
                                guy->velocity.x += 4.0f;
                                HuPrcVSleep();
                            }
                            func_800D8F3C_name_81(guy);
                            goto turnEnd;
                        }

                        if (func_800F37B8_name_81(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                            rand = func_800EFE20_name_81(1000.0f);
                            if (rand < 500) {
                                GwPlayer[system->current_player_index].gameCoin = 0;
                                GwPlayer[system->current_player_index].bonusCoin = 0;
                            } else if (rand < 870) {
                                GwPlayer[system->current_player_index].bonusCoin = 2;
                            } else if (rand < 950) {
                                GwPlayer[system->current_player_index].bonusCoin = 4;
                            } else if (rand < 985) {
                                GwPlayer[system->current_player_index].bonusCoin = 8;
                            } else if (rand < 995) {
                                GwPlayer[system->current_player_index].bonusCoin = 16;
                            } else if (rand < 999) {
                                GwPlayer[system->current_player_index].bonusCoin = 32;
                            } else {
                                GwPlayer[system->current_player_index].bonusCoin = 64;
                            }
                            WipeCreateOut(9, 0x10);
                            HuPrcSleep(0x11);
                            func_800D8F3C_name_81(guy);
                            func_800EF7C8_name_81(player->player_obj, 0.0f, 0.0f);
                            player->player_obj->velocity.x = 0.0f;
                            HuPrcSleep(5);
                            WipeCreateIn(9, 0x10);
                            HuPrcSleep(0x11);
                        } else {
                            mbGameMode = 8;
                            D_80105494_name_81 = 2;
                            D_80105496_name_81 = 1;
                            D_800D1360.unk_20 = 9;
                            GwPlayer[(s8)(system->current_player_index ^ 1)].group = 1;
                            GwPlayer[2].group = 1;
                            GwPlayer[3].group = 1;
                            player->group = 0;
                            roll = func_800EFE20_name_81(100.0f);
                            for (j = 0; j < 4; j++) {
                                if (roll < D_80101AA0_name_81[j]) {
                                    break;
                                }
                            }
                            if (j == 4) {
                                j = 3;
                            }
                            system->minigame_index = D_80101A9C_name_81[j];
                            HuPrcSleep(-1);
                        }
                    mode8: {
                        if (func_800F37B8_name_81(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                            coins = GwPlayer[system->current_player_index].gameCoin * GwPlayer[system->current_player_index].bonusCoin;
                            if (coins >= 999) {
                                coins = 999;
                            }
                            sprintf(sp28.coin.buf, "%d", coins);
                            if (coins != 0) {
                                func_800EADBC_name_81(0x2F03, (u32)sp28.coin.buf, 0, 0, 0, 0);
                                func_800EAF70_name_81(system->current_player_index);
                                func_800EAF94_name_81();
                            } else {
                                func_800EAFC4_name_81(0x2F04);
                                func_800F3880_name_81(-1, 2, 0);
                                func_8004ACE0_main(0x286, system->current_player_index);
                                func_800EFABC_name_81(player->player_obj);
                                HuPrcSleep(0x14);
                                func_800F397C_name_81(-1, -1, 0, 5, 2);
                            }
                        }
                        if (GwPlayer[system->current_player_index].gameCoin != 0 && GwPlayer[system->current_player_index].bonusCoin != 0) {
                            func_800E14D8_name_81(system->current_player_index, GwPlayer[system->current_player_index].gameCoin * GwPlayer[system->current_player_index].bonusCoin);
                            func_800F7378_name_81(system->current_player_index,
                                                  GwPlayer[system->current_player_index].gameCoin *
                                                      GwPlayer[system->current_player_index].bonusCoin);
                            if (func_800F37B8_name_81(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                                HuPrcSleep(0x14);
                                func_800F3880_name_81(-1, 6, 0);
                                func_8004ACE0_main(0x274, system->current_player_index);
                                func_800EFABC_name_81(player->player_obj);
                                func_800F397C_name_81(-1, -1, 0, 5, 2);
                            }
                        }
                        if (func_800F37B8_name_81(system->current_player_index) != 0 && system->show_com_minigames != 0) {
                            goto spaceDone;
                        }
                        goto sleepEnd;
                    }

                    case 8:
                        HuPrcSleep(8);
                        func_800F74E4_name_81(-1);
                        func_800EEC40_name_81(&player->player_obj->coords);
                        HuAudFXPlay(0x2A7);
                        func_800EB140_name_81(0x15, 0x1F2F);
                        func_800FD620_name_81();
                        mbGameMode = 9;
                        HuPrcSleep(-1);
                    sleepEnd:
                        HuPrcSleep(0x1E);
                        goto spaceDone;

                    case 10:
                        if ((*(s32 *)&player->stats.partners.frontID & 0xFFFF0000) == 0xFFFF0000) {
                            func_800EAFC4_name_81(0x1F1E);
                            goto spaceDone;
                        }
                        if ((player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 2) ||
                            (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 2)) {
                            func_800EAFC4_name_81(0x1F1F);
                            goto spaceDone;
                        }
                        func_800EDD50_name_81(&player->player_obj->coords);
                        func_800EE0F4_name_81(1);
                        func_800EDF48_name_81();
                        HuAudFXPlay(0x159);
                        func_800EB140_name_81(0x16, 0x1F1D);
                        HuAudFXPlay(0x1F6);
                        eff = func_800FFC2C_name_81(-1, 0, 5);
                        func_800EE74C_name_81(0);
                        func_800FFCCC_name_81(eff);
                        func_800EDF78_name_81();
                        func_800EE468_name_81(2);
                        func_800EDDBC_name_81();
                        fxModels[0] = NULL;
                        fxModels[1] = NULL;
                        if (player->stats.partners.frontID != -1) {
                            fxModels[0] = func_800D8010_name_81(0x38, NULL);
                            func_800D8944_name_81(fxModels[0]);
                            HuVecCopy3F(&fxModels[0]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, PARTNER_FRONT)->coords);
                            func_8001C814_main(fxModels[0]->omObj1->model[0], 2, 0);
                        }
                        if (player->stats.partners.backID != -1) {
                            fxModels[1] = func_800D8010_name_81(0x38, NULL);
                            func_800D8944_name_81(fxModels[1]);
                            HuVecCopy3F(&fxModels[1]->coords, &MBDGetPlayerPartnerRef(system->current_player_index, PARTNER_BACK)->coords);
                            func_8001C814_main(fxModels[1]->omObj1->model[0], 2, 0);
                        }
                        HuAudFXPlay(0x1FA);
                        if (fxModels[0] != NULL) {
                            func_800EFABC_name_81(fxModels[0]);
                            func_800D8F3C_name_81(fxModels[0]);
                        }
                        if (fxModels[1] != NULL) {
                            func_800EFABC_name_81(fxModels[1]);
                            func_800D8F3C_name_81(fxModels[1]);
                        }
                        Duel_PowerUpPartners(system->current_player_index);
                        HuPrcChildLink(mainProc, func_800E4A74_name_81(0));
                        HuPrcChildWait();
                        goto spaceDone;

                    case 5:
                        if (system->current_board_index == 5) {
                            goto spaceDone;
                        }
                        func_800DB624_name_81(system->current_player_index, 1);
                        if (D_800CE1D0_main == 0) {
                            tmp1 = player->nlink;
                            tmp2 = player->nidx;
                            player->nlink = player->blink;
                            player->nidx = player->bidx;
                            player->blink = tmp1;
                            player->bidx = tmp2;
                        }
                        player->rev = 7;
                        D_800CE1D0_main = 1;
                        goto diceRoll;

                    case -1:
                    modeWalkEnd:
                        func_800F38DC_name_81(-1, -1, 2);
                        HuPrcSleep(0x1E);
                        if (D_80101A98_name_81 != 0) {
                            ((void (*)(void))D_80101A98_name_81)();
                        }
                        D_80105490_name_81 = 0;
                        goto walkStep;

                    case 0:
                    case 1:
                    case 4:
                    case 7:
                    case 9:
                    default:
                        goto spaceDone;
                }
            case 8:
                goto mode8;
            case 9:
                goto sleepEnd;
            case 10:
                goto modeWalkEnd;
            spaceDone:
                mbGameMode = 6;
                D_80105490_name_81 = func_800EA4D4_name_81(masuId, 5);
                if (D_80105494_name_81 < 0) {
                    goto turnEnd;
                }
                HuPrcSleep(-1);
            case 6:
                HuPrcSleep(0x1E);
            turnEnd:
                mbItemBtnF = 0;
                if (system->current_player_index > 0 && system->total_turns >= 0 &&
                    system->current_turn >= system->total_turns) {
                gameEnd:
                    HuAudFXPlay(0x20C);
                    func_800EEC40_name_81(&player->player_obj->coords);
                    HuAudFXPlay(0x2A6);
                    func_800EB164_name_81(0x15, 0x2000);
                    GwSystem.boardData.halfWordBytes[0] = func_800EA940_name_81(0);
                    GwSystem.boardData.halfWordBytes[1] = func_800EA940_name_81(1);
                    D_80105494_name_81 = 0x20;
                    D_80105496_name_81 = 1;
                    D_800D1360.unk_20 = 2;
                    HuPrcSleep(-1);
                }
                HuPrcSleep(4);
                HuPrcChildLink(mainProc, func_800F41DC_name_81());
                HuPrcChildWait();
                func_800FC9FC_name_81();
                for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                    func_800EB7D8_name_81(i);
                    func_800D90D0_name_81(MBDGetPlayerStruct(i)->player_obj, -1, 2);
                }
                HuPrcVSleep();
                func_800FFA28_name_81(NULL);
                mbGameMode = 1;
        }
    }
}


void func_800FF420_name_81(void) {
    HuPrcVSleep();
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    func_800FC4E4_name_81();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

// duel n8
extern u8 D_800CC0BA_main;
void func_800DC3AC_name_81(s32 playerIndex);
void func_800DC410_name_81(s32 playerIndex);
void func_800F3500_name_81(s32 playerIndex);
void func_800FB524_name_81(void *arg0);

void func_800FF480_name_81(void) {
    Vec2f sp10;
    s32 curPlayerNo;
    s32 i;
    s32 playerPadNo;

    while (1) {
        HuPrcVSleep();
        if (WipeStatGet() != 0) {
            continue;
        }
        if (mbItemBtnF == 0) {
            continue;
        }
        if (D_800CC0BA_main == 3) {
            continue;
        }
        curPlayerNo = MBDGetCurrentPlayerIndex();
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (D_800C9520_main[i] & START_BUTTON) {
                func_800DC3AC_name_81(curPlayerNo);
                MBDCameraPos2DGet(&sp10);
                MBDCameraPos2DSet(&sp10);
                func_800F3500_name_81(i);
                func_800DC410_name_81(curPlayerNo);
                break;
            }
            if (i < MBD_MAX_PLAYERS && func_800F37B8_name_81(i) == 0) {
                playerPadNo = GwPlayer[i].pad;
                if (i == curPlayerNo) {
                    if (D_800D51F8_main != 0 && (D_800C9520_main[playerPadNo] & B_BUTTON)) {
                        func_800DC3AC_name_81(i);
                        D_800CB99C_main = 1;
                        func_80049FB8_main();
                        func_800FB524_name_81((void *)i);
                        func_8004A0E0_main();
                        D_800CB99C_main = 0;
                        func_800DC410_name_81(i);
                        break;
                    }
                    if (mbCameraBtnF != 0 && (D_800C9520_main[playerPadNo] & R_TRIG)) {
                        func_800DC3AC_name_81(curPlayerNo);
                        func_80100CEC_name_81(playerPadNo);
                        func_800DC410_name_81(curPlayerNo);
                        break;
                    }
                }
            }
        }
    }
}

// duel n8
void func_800EB6C4_name_81(s16 playerIndex, s16 spaceIdx);
void func_800F40E4_name_81(void);
void func_800DC7CC_name_81(void);
void func_800FC8E8_name_81(void);
void func_800FD6F4_name_81(void);
void func_800FCAB4_name_81(void);

void func_800FF640_name_81(u32 arg0) {
    GW_PLAYER *player;
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        s16 masuID;
        player = MBDGetPlayerStruct(i);
        masuID = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
        func_800EB6C4_name_81(i, masuID);
        func_800ED214_name_81(i);
    }

    func_800E5954_name_81();
    func_800E856C_name_81(1.0f);
    MBDCameraSpeedSet(-1.0f);
    D_800CD280_main = 1;
    switch (arg0) {
        case 0:
            switch (mbGameMode) {
                case 0:
                case 1:
                    WipeCreateIn(0, 0);
                    func_800F40E4_name_81();
                    break;
                default:
                    if (D_800A12C8_main != -1) {
                        if (D_800A12C8_main == 0) {
                            WipeColorSet(255, 255, 255);
                        } else {
                            WipeColorSet(0, 0, 0);
                        }
                        WipeCreateIn(D_800A12C8_main, 0x10);
                        D_800A12C8_main = -1;
                        func_800FFAE0_name_81(0, 0);
                        func_800FFAE0_name_81(1, 0);
                    } else {
                        WipeCreateIn(0xFF, 0x10);
                    }
                    MBDCameraZoomSet(D_800C9938_main);
                    func_800F4080_name_81();
                    break;
            }
            MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
            omAddPrcObj(func_800FD6F4_name_81, 0xEFFF, 0x4000, 0);
            omAddPrcObj(func_800FCAB4_name_81, 0x1005, 0, 0);
            omPrcSetStatBit(omAddPrcObj(func_800FF480_name_81, 0x1001, 0, 0), 0x80);
            mbCameraBtnF = 0;
            mbItemBtnF = 0;
            D_800D51F8_main = 0;
            omAddPrcObj(func_800FC8E8_name_81, 0x1005, 0, 0);
            func_800FC888_name_81(1);
            if (func_800037C4_main(D_800CDBC8_main) < 0x7F) {
                func_800DC7CC_name_81();
                return;
            }
            return;
        case 1:
            MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
            omAddPrcObj(func_800FCAB4_name_81, 0x1005, 0, 0);
            omPrcSetStatBit(omAddPrcObj(func_800FF420_name_81, 0x1005, 0, 0), 0x80);
            mbCameraBtnF = 1;
            return;
        case 2:
            func_800F73C0_name_81();
            func_800FC888_name_81(0);
            break;
    }
}

void func_800FF944_name_81(s16 arg0) {
    D_800CD2A0_main.unk_02 = 1;
    D_80105494_name_81 = 0x40;
    D_800D1360.unk_20 = arg0;
    D_80105496_name_81 = 0;
}

void func_800FF970_name_81(s32 arg0) {
    D_800A12C8_main = arg0;
}

void func_800FF97C_name_81(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    D_80105498_name_81 = arg0;
    D_8010549C_name_81 = arg1;
    D_80105494_name_81 = 8;
    D_800D1360.unk_20 = arg2;
    D_80105496_name_81 = arg3;
}

void func_800FF9AC_name_81(s32 arg0, s16 arg1, s16 arg2) {
    func_800FF97C_name_81(arg0, arg1, arg2, 0);
}

void func_800FF9D8_name_81(void) {
    D_800D530C_main = 1;
}

void func_800FF9E8_name_81(s16 arg0, s16 arg1) {
    D_80105494_name_81 = 0x10;
    D_800D1360.unk_20 = arg0;
    D_80105496_name_81 = arg1;
    func_800FC108_name_81();
}

s16 func_800FFA1C_name_81(void) {
    return D_80105494_name_81;
}

void func_800FFA28_name_81(Vec *arg0) {
    f32 temp_f20;
    f32 temp_f22;
    Vec *var_s0;

    var_s0 = arg0;
    func_800E5C20_name_81();
    func_800E5BE8_name_81();
    temp_f22 = MBDCameraSpeedGet();
    MBDCameraSpeedSet(-1.0f);
    temp_f20 = func_800E8578_name_81();
    func_800E856C_name_81(1.0f);
    func_800E5954_name_81();
    if (var_s0 == NULL) {
        var_s0 = &MBDGetPlayerStruct(CUR_PLAYER)->player_obj->coords;
    }
    MBDCameraPos3DSet(var_s0);
    HuPrcVSleep();
    func_800E856C_name_81(temp_f20);
    MBDCameraSpeedSet(temp_f22);
}
