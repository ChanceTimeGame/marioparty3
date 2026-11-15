#include "common.h"
#include "ovl_81.h"

// duel n1: Duel Mode's CPU decision tree (ovl_80 EDDB0's MBComTreeExec with two-player conditions)

s16 func_800EB9D4_name_81(s8 arg0);
s16 func_800EBA1C_name_81(void);
s32 func_800EFB3C_name_81(s32 player);
s32 func_800F3850_name_81(s32 playerNo, s32 requiredCoins);
s32 func_800F8980_name_81(s32 playerIndex);

/* Walks a CPU decision tree from arg0 and returns the chosen leaf's answer (0 or 1). Players are
 * -1 (the current one) or MBDGetCurrentPlayerIndex() ^ 1 (the opponent). */
s16 func_800D97B0_name_81(DecisionTreeNonLeafNode *arg0) {
    char pad[32];
    DecisionTreeNonLeafNode *node = arg0;
    GW_PLAYER *player;
    s16 cmp;
    s16 clink;
    s16 cidxMin;
    s16 cidxMax;
    u32 idx;
    s32 turns;
    u32 limit;
    s32 pct;
    s16 p;

    for (;; node++) {
        switch (node->type) {
            case 1:
                if (func_800F3850_name_81(-1, node->node_data1.data) != 0) {
                    break;
                }
                continue;

            case 2:
                if ((1 << (mbWalkNum - 1)) & node->node_data1.data) {
                    break;
                }
                continue;

            case 3:
                idx = node->node_data1.data >> 0x14;
                cmp = node->node_data1.data_u16[1];
                idx &= 0xFF;
                switch ((node->node_data1.data >> 0x10) & 0xF) {
                    case 0:
                        if (GwSystem.boardData.halfWordBytes[idx] == cmp) {
                            break;
                        }
                        continue;
                    case 1:
                        if (GwSystem.boardData.halfWordBytes[idx] != cmp) {
                            break;
                        }
                        continue;
                    case 2:
                        if (GwSystem.boardData.halfWordBytes[idx] < cmp) {
                            break;
                        }
                        continue;
                    case 3:
                        if (GwSystem.boardData.halfWordBytes[idx] <= cmp) {
                            break;
                        }
                        continue;
                    case 4:
                        if (GwSystem.boardData.halfWordBytes[idx] > cmp) {
                            break;
                        }
                        continue;
                    case 5:
                        if (GwSystem.boardData.halfWordBytes[idx] >= cmp) {
                            break;
                        }
                        continue;
                }
                break;

            case 0:
                break;

            case 4:
                if ((1 << func_800EFB3C_name_81(MBDGetCurrentPlayerIndex())) & node->node_data1.data) {
                    break;
                }
                continue;

            case 5:
                if (node->node_data1.func() != 0) {
                    break;
                }
                continue;

            case 6:
                turns = func_800EBA1C_name_81();
                limit = node->node_data1.signed_data;
                if ((limit > turns) == 0) {
                    break;
                }
                continue;

            case 7:
                limit = node->node_data1.signed_data;
                turns = mbWalkNum;
                if ((limit > turns) == 0) {
                    break;
                }
                continue;

            case 8:
                clink = node->node_data1.data_u8[2];
                cidxMin = node->node_data1.data_u8[3];
                player = MBDGetPlayerStruct(-1);
                if (player->clink != clink) {
                    continue;
                }
                if (player->cidx == cidxMin) {
                    break;
                }
                continue;

            case 9:
                clink = node->node_data1.data_u8[2];
                cidxMin = node->node_data1.data_u8[3];
                player = MBDGetPlayerStruct(MBDGetCurrentPlayerIndex() ^ 1);
                if (player->clink != clink) {
                    continue;
                }
                if (player->cidx == cidxMin) {
                    break;
                }
                continue;

            case 10:
                clink = node->node_data1.data_u8[1];
                cidxMin = node->node_data1.data_u8[2];
                cidxMax = node->node_data1.data_u8[3];
                player = MBDGetPlayerStruct(-1);
                if (player->clink != clink) {
                    continue;
                }
                if (player->cidx >= cidxMin && player->cidx <= cidxMax) {
                    break;
                }
                continue;

            case 11:
                clink = node->node_data1.data_u8[1];
                cidxMin = node->node_data1.data_u8[2];
                cidxMax = node->node_data1.data_u8[3];
                player = MBDGetPlayerStruct(MBDGetCurrentPlayerIndex() ^ 1);
                if (player->clink != clink) {
                    continue;
                }
                if (player->cidx >= cidxMin && player->cidx <= cidxMax) {
                    break;
                }
                continue;

            case 12:
                if (func_800F3850_name_81(-1, node->node_data1.data) == 0) {
                    break;
                }
                continue;

            case 13:
                if ((GwPlayer[MBDGetCurrentPlayerIndex()].chr != node->node_data1.data) == 0) {
                    break;
                }
                continue;

            case 14:
                clink = node->node_data1.data_u8[1];
                cidxMin = node->node_data1.data_u8[2];
                cidxMax = node->node_data1.data_u8[3];
                player = MBDGetPlayerStruct(node->node_data1.data_u8[0]);
                if (player->clink != clink) {
                    continue;
                }
                if (player->cidx >= cidxMin && player->cidx <= cidxMax) {
                    break;
                }
                continue;

            case 15:
                p = MBDGetCurrentPlayerIndex();
                if (func_800F8980_name_81(p) == 0 || GwPlayer[p].coin / func_800F8980_name_81(p) >= node->node_data1.signed_data) {
                    break;
                }
                continue;

            case 16:
                p = MBDGetCurrentPlayerIndex() ^ 1;
                if (func_800F8980_name_81(p) == 0 || GwPlayer[p].coin / func_800F8980_name_81(p) >= node->node_data1.signed_data) {
                    break;
                }
                continue;

            case 17:
                if (MBDGetPlayerStruct(-1)->stats.prize.itemPrize >= node->node_data1.signed_data) {
                    break;
                }
                continue;

            case 18:
                if (MBDGetPlayerStruct((s16)(MBDGetCurrentPlayerIndex() ^ 1))->stats.prize.itemPrize >= node->node_data1.signed_data) {
                    break;
                }
                continue;

            case 19:
                if (GwPlayer[MBDGetCurrentPlayerIndex()].star >= node->node_data1.signed_data) {
                    break;
                }
                continue;

            case 20:
                if (GwPlayer[(s16)(MBDGetCurrentPlayerIndex() ^ 1)].star >= node->node_data1.signed_data) {
                    break;
                }
                continue;

            case 21:
                if (MBDGetCurrentPlayerIndex() == node->node_data1.data) {
                    break;
                }
                continue;

            case 22:
                if (MBDGetPlayerStruct(-1)->cpu_difficulty == node->node_data1.data) {
                    break;
                }
                continue;

            case 23:
                if ((1 << (MBDGetPlayerStruct(-1)->stats.prize.gamblePrize + 1)) & node->node_data1.data) {
                    break;
                }
                continue;

            case 24:
                if ((1 << (MBDGetPlayerStruct((s16)(MBDGetCurrentPlayerIndex() ^ 1))->stats.prize.gamblePrize + 1)) & node->node_data1.data) {
                    break;
                }
                continue;

            case 25:
                if ((1 << (MBDGetPlayerStruct(-1)->stats.prize.duelNo + 1)) & node->node_data1.data) {
                    break;
                }
                continue;

            case 26:
                if ((1 << (MBDGetPlayerStruct(-1)->stats.prize.duelNo + 1)) & node->node_data1.data) {
                    break;
                }
                continue;
        }

        if ((s32)node->node_data2.node_data < 0) {
            node = node->node_data2.node_data - 1;
            continue;
        }

        switch (MBDGetPlayerStruct(-1)->cpu_difficulty) {
            case 0:
                pct = node->node_data2.data_u8[3] & 0x7F;
                break;
            case 1:
                pct = (node->node_data2.data >> 7) & 0x7F;
                break;
            case 2:
                pct = (node->node_data2.data >> 0xE) & 0x7F;
                break;
            case 3:
                pct = (node->node_data2.data >> 0x15) & 0x7F;
                break;
            default:
                pct = 0;
                break;
        }

        if (func_800EB9D4_name_81(pct) != 0) {
            cmp = (node->node_data2.data >> 0x1C) & 1;
        } else {
            cmp = ((node->node_data2.data >> 0x1C) ^ 1) & 1;
        }
        return cmp;
    }
}
