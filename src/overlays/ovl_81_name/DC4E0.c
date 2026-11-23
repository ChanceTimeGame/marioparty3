#include "common.h"
#include "ovl_81.h"
#include "game/sprite.h"
#include "game/data.h"
#include "game/audio.h"
#include "math.h"

// duel n7: Duel Mode player status panels (two players; cf. ovl_80 106A50.c)

typedef struct DuelStatus {
    /* 0x00 */ u8 flags; // bit 0: hidden
    /* 0x01 */ s8 prevStars;
    /* 0x02 */ s16 prevCoins;
    /* 0x04 */ s16 grp;
    /* 0x06 */ char unk_06[2];
    /* 0x08 */ s16 timer;
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ f32 xPos;
    /* 0x10 */ f32 yPos;
    /* 0x14 */ f32 targetX;
    /* 0x18 */ f32 targetY;
    /* 0x1C */ f32 velX;
    /* 0x20 */ f32 velY;
    /* 0x24 */ f32 accX;
    /* 0x28 */ f32 accY;
    /* 0x2C */ omObjData *unk_2C;
    /* 0x30 */ char unk_30[4];
    /* 0x34 */ s16 numSpr;
    /* 0x36 */ char unk_36[4];
    /* 0x3A */ s16 frontSpr[11];
    /* 0x50 */ s16 backSpr[11];
    /* 0x66 */ char unk_66[4];
    /* 0x6A */ s8 frontCost;
    /* 0x6B */ s8 backCost;
} DuelStatus; // sizeof 0x6C

typedef struct DuelCoinDigits {
    /* 0x00 */ u8 digits[3];
} DuelCoinDigits;

extern s32 D_801014E0_name_81;
extern s32 D_801014E4_name_81;
extern s16 D_801014E8_name_81[][2];
extern s16 D_801015A4_name_81[3][2];
extern s16 D_801015B0_name_81[3][2];
extern s16 (*D_801015BC_name_81[])[2];
extern u8 D_801015C4_name_81[];
extern s32 D_801015E0_name_81[];
extern s32 D_80101620_name_81[];
extern s16 (*D_80101650_name_81[])[2];
extern s8 D_80101660_name_81[][3];

extern Process *D_80105410_name_81;
extern s16 D_80105414_name_81[];
extern s16 D_80105420_name_81;
extern s16 D_80105422_name_81;
extern f32 D_80105424_name_81;
extern Vec2f D_80105428_name_81;
extern Vec2f D_80105430_name_81;
extern Vec2f D_80105438_name_81;
extern s16 D_80105440_name_81;
extern omObjData *D_80105444_name_81[];
extern DuelStatus D_80105630_name_81[];

void func_800F37E0_name_81(s32, s32);
void func_800F4710_name_81(s32 playerNo);
void func_800F5834_name_81(s32 playerNo, s32 partnerId, s16 *sprIds, s16 base);
void func_800F6550_name_81(s32 playerNo, s16 x, s16 y);
void func_800F6F84_name_81(void);
void func_800F7458_name_81(s32 playerNo, f32 x, f32 y);

void func_800F4710_name_81(s32 playerNo) {
    DuelCoinDigits coinDigits;
    GW_PLAYER *player;
    DuelStatus *sp;
    s32 var_v1;
    s32 i;

    player = MBDGetPlayerStruct(playerNo);
    sp = &D_80105630_name_81[playerNo];
    if (D_801014E0_name_81 != 0) {
        if (sp->prevCoins != GwPlayer[playerNo].coin) {
            coinDigits.digits[0] = GwPlayer[playerNo].coin / 100;
            coinDigits.digits[1] = GwPlayer[playerNo].coin / 10 % 10;
            coinDigits.digits[2] = GwPlayer[playerNo].coin % 10;
            if (coinDigits.digits[0] != 0) {
                var_v1 = ((coinDigits.digits[0] != 0) ? 3 : 2);
            } else if (coinDigits.digits[1] != 0) {
                var_v1 = ((coinDigits.digits[0] != 0) ? 3 : 2);
            } else {
                var_v1 = 1;
            }

            if (var_v1 == 1) {
                HuSprAttrSet(sp->grp, 5, 0x8000);
                coinDigits.digits[1] = coinDigits.digits[2];
            } else {
                HuSprAttrReset(sp->grp, 5, 0x8000);
            }

            if (coinDigits.digits[0] == 0) {
                coinDigits.digits[0] = 10;
            }
            for (i = 0; i < 3; i++) {
                func_80055140_main(sp->grp, i + 3, coinDigits.digits[i], 0);
                func_800550F4_main(sp->grp, i + 3, 1);
            }
            sp->prevCoins = GwPlayer[playerNo].coin;
        }

        if (sp->prevStars != GwPlayer[playerNo].star) {
            if (GwPlayer[playerNo].star >= 5) {
                func_80055140_main(sp->grp, 2, 5, 0);
            } else {
                func_80055140_main(sp->grp, 2, GwPlayer[playerNo].star, 0);
            }
            func_800550F4_main(sp->grp, 2, 1);
            sp->prevStars = GwPlayer[playerNo].star;
        }

        if (player->stats.partners.frontID != -1) {
            func_80055140_main(sp->grp, 12, player->stats.partners.frontHp, 0);
            func_80055140_main(sp->grp, 13, player->stats.partners.frontPower, 0);
            func_80055140_main(sp->grp, 14, 12, 0);
            if (player->stats.partners.frontCost >= 10) {
                func_80055140_main(sp->grp, 15, player->stats.partners.frontCost / 10, 0);
                func_80055140_main(sp->grp, 16, player->stats.partners.frontCost % 10, 0);
                if (sp->frontCost != player->stats.partners.frontCost && D_801014E4_name_81 != 0) {
                    for (i = 0; i < 3; i++) {
                        func_80054904_main(sp->grp, i + 14, D_801015A4_name_81[i][0], -D_801015A4_name_81[i][1]);
                    }
                }
            } else {
                func_80055140_main(sp->grp, 15, player->stats.partners.frontCost, 0);
                HuSprAttrSet(sp->grp, 16, 0x8000);
                if (sp->frontCost != player->stats.partners.frontCost && D_801014E4_name_81 != 0) {
                    for (i = 0; i < 3; i++) {
                        func_80054904_main(sp->grp, i + 14, D_801015B0_name_81[i][0], -D_801015B0_name_81[i][1]);
                    }
                }
            }
            sp->frontCost = player->stats.partners.frontCost;
            for (i = 5; i < 10; i++) {
                func_800550F4_main(sp->grp, i + 7, 1);
            }
        }

        if (player->stats.partners.backID != -1) {
            func_80055140_main(sp->grp, 23, player->stats.partners.backHp, 0);
            func_80055140_main(sp->grp, 24, player->stats.partners.backPower, 0);
            func_80055140_main(sp->grp, 25, 12, 0);
            if (player->stats.partners.backCost >= 10) {
                func_80055140_main(sp->grp, 26, player->stats.partners.backCost / 10, 0);
                func_80055140_main(sp->grp, 27, player->stats.partners.backCost % 10, 0);
                if (sp->backCost != player->stats.partners.backCost && D_801014E4_name_81 != 0) {
                    for (i = 0; i < 3; i++) {
                        func_80054904_main(sp->grp, i + 25, D_801015A4_name_81[i][0], D_801015A4_name_81[i][1]);
                    }
                }
            } else {
                func_80055140_main(sp->grp, 26, player->stats.partners.backCost, 0);
                HuSprAttrSet(sp->grp, 27, 0x8000);
                if (sp->backCost != player->stats.partners.backCost && D_801014E4_name_81 != 0) {
                    for (i = 0; i < 3; i++) {
                        func_80054904_main(sp->grp, i + 25, D_801015B0_name_81[i][0], D_801015B0_name_81[i][1]);
                    }
                }
            }
            sp->backCost = player->stats.partners.backCost;
            for (i = 5; i < 10; i++) {
                func_800550F4_main(sp->grp, i + 18, 1);
            }
        }
    }

    if (player->stats.partners.frontPoweredUp == POWERUP_ACTIVE) {
        HuSprAttrReset(sp->grp, 17, 0x8000);
    } else {
        HuSprAttrSet(sp->grp, 17, 0x8000);
    }
    if (player->stats.partners.backPoweredUp == POWERUP_ACTIVE) {
        HuSprAttrReset(sp->grp, 28, 0x8000);
    } else {
        HuSprAttrSet(sp->grp, 28, 0x8000);
    }
}

void func_800F4E90_name_81(void) {
    s32 i, j;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        DuelStatus *sp = &D_80105630_name_81[i];
        for (j = 0; j < 29; j++) {
            HuSprAttrSet(sp->grp, j, 0x8000);
        }
    }
}

void func_800F4F20_name_81(void) {
    DuelStatus *sp;
    s32 i, j;

    while (1) {
        if (HmfPauseF == 0) {
            for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                sp = &D_80105630_name_81[i];
                if (sp->flags & 1) {
                    for (j = 0; j < 29; j++) {
                        HuSprAttrSet(sp->grp, j, 0x8000);
                    }
                    continue;
                }
                for (j = 0; j < 29; j++) {
                    if (j >= 7 && j < 18) {
                        if (GwPlayer[i].stats.partners.frontID != -1) {
                            goto show;
                        }
                    } else if (j >= 18 && j < 29) {
                        if (GwPlayer[i].stats.partners.backID != -1) {
                            goto show;
                        }
                    } else if (j != 5) {
                        if (j != 6 || (GwPlayer[i].stat & 1)) {
                            goto show;
                        }
                    } else if (GwPlayer[i].coin >= 10) {
                        goto show;
                    }
                    continue;
                show:
                    HuSprAttrReset(sp->grp, j, 0x8000);
                }
                func_800F4710_name_81(i);
                if (sp->timer > 0) {
                    sp->timer--;
                    sp->xPos += sp->velX;
                    sp->yPos += sp->velY;
                    sp->velX += sp->accX;
                    sp->velY += sp->accY;
                } else if (sp->timer == -1) {
                    sp->timer = -2;
                } else if (sp->timer != -2) {
                    sp->xPos = sp->targetX;
                    sp->yPos = sp->targetY;
                    sp->timer = -1;
                }
                func_80054904_main(sp->grp, 0, (s32)(sp->xPos + 0.5f) + 48, (s32)(sp->yPos + 0.5f) + 24);
            }

            if (D_80105420_name_81 != -1) {
                D_80105424_name_81 -= 1.0f;
                if (D_80105424_name_81 < 1.0f) {
                    D_80105424_name_81 = 1.0f;
                }
                HuSprScaleSet(D_80105420_name_81, 0, D_80105424_name_81, D_80105424_name_81);
                if (D_80105440_name_81 > 0) {
                    D_80105440_name_81--;
                    D_80105428_name_81.x += D_80105430_name_81.x;
                    D_80105428_name_81.y += D_80105430_name_81.y;
                    D_80105430_name_81.x += D_80105438_name_81.x;
                    D_80105430_name_81.y += D_80105438_name_81.y;
                    func_80054904_main(D_80105420_name_81, 0, D_80105428_name_81.x, D_80105428_name_81.y);
                }
            }
        }
        HuPrcVSleep();
    }
}

void func_800F52B8_name_81(s32 playerNo) {
    s16 grp = D_80105630_name_81[playerNo].grp;

    func_80055024_main(grp, 1, D_80105414_name_81[playerNo + 1], 0);
    func_800550F4_main(grp, 1, 0);
    HuSprPriSet(grp, 1, (playerNo * 5) + 0x4790);
    HuSprAttrSet(grp, 1, 0);
    func_80054904_main(grp, 1, D_801015BC_name_81[playerNo][1][0], D_801015BC_name_81[playerNo][1][1]);
    if (playerNo != 0 && GwPlayer[playerNo].chr != 1 && GwPlayer[playerNo].chr != 6) {
        HuSprAttrSet(grp, 1, 1);
    }
}

void func_800F53C4_name_81(s32 playerNo) {
    s16 grp = D_80105630_name_81[playerNo].grp;

    func_80055024_main(grp, 2, D_80105414_name_81[3], 0);
    HuSprPriSet(grp, 2, (playerNo * 5) + 0x4790);
    HuSprAttrSet(grp, 2, 0);
    func_800552DC_main(grp, 2, 0.0f);
    func_80054904_main(grp, 2, D_801015BC_name_81[playerNo][2][0], D_801015BC_name_81[playerNo][2][1]);
    func_800550B4_main(grp, 2, 0.0f);
    func_80055458_main(grp, 2, 0x100);
}

void func_800F54A4_name_81(s32 playerNo) {
    DuelStatus *sp = &D_80105630_name_81[playerNo];
    s16 grp;
    void *data;
    s32 i;

    sp->prevCoins = -1;
    sp->prevStars = -1;
    data = DataRead(0x1300CF);
    sp->numSpr = func_80055810_main(data);
    grp = sp->grp;
    for (i = 0; i < 3; i++) {
        func_80055024_main(grp, i + 3, sp->numSpr, 0);
        func_800550F4_main(grp, i + 3, 1);
        func_80055140_main(grp, i + 3, 10, 0);
        HuSprPriSet(grp, i + 3, (playerNo * 5) + 0x4790);
        HuSprAttrSet(grp, i + 3, 0);
        func_80054904_main(grp, i + 3, D_801015BC_name_81[playerNo][i + 3][0], D_801015BC_name_81[playerNo][i + 3][1]);
    }
    DataClose(data);
}

void func_800F55FC_name_81(s32 playerNo) {
    DuelStatus *sp = &D_80105630_name_81[playerNo];
    s16 grp = HuSprGrpCreate(29, 2);

    sp->grp = grp;
    func_80055024_main(grp, 0, D_80105414_name_81[0], 0);
    HuSprPriSet(grp, 0, (playerNo * 5) + 0x4790);
    HuSprAttrSet(grp, 0, 0);
    func_80054904_main(grp, 0, 0, 0);
}

void func_800F56C0_name_81(s32 playerNo) {
    s16 grp = D_80105630_name_81[playerNo].grp;

    func_80055024_main(grp, 6, D_80105414_name_81[5], 0);
    func_800550F4_main(grp, 6, 0);
    HuSprPriSet(grp, 6, (playerNo * 5) + 0x478E);
    HuSprAttrSet(grp, 6, 0);
    func_80054904_main(grp, 6, D_801015BC_name_81[playerNo][6][0], D_801015BC_name_81[playerNo][6][1]);
    if (!(GwPlayer[playerNo].stat & 1)) {
        HuSprAttrSet(grp, 6, 0x8000);
    }
}

void func_800F57B0_name_81(s32 playerNo) {
    DuelStatus *sp;
    s32 i;

    if (MBDGetPlayerStruct(playerNo)->stats.partners.frontID == -1) {
        sp = &D_80105630_name_81[playerNo];
        for (i = 0; i < 11; i++) {
            HuSprAttrSet(sp->grp, i + 7, 0x8000);
        }
    }
}

#ifdef NON_MATCHING
void func_800F5834_name_81(s32 playerNo, s32 partnerId, s16 *sprIds, s16 base) {
    s32 files[11] = {
        0x001300D5, 0x00000000, 0x001300D2, 0x001300D3, 0x001300D4, 0x001300CF,
        0x001300CF, 0x001300D0, 0x001300D0, 0x001300D0, 0x001300F6,
    };
    s16 grp = D_80105630_name_81[playerNo].grp;
    void *data;
    s32 i;

    for (i = 0; i < 11; i++) {
        if (i == 1) {
            if (playerNo != 0) {
                HuSprAttrSet(grp, base + i, 1);
            } else {
                HuSprAttrReset(grp, base + i, 1);
            }
            data = DataRead(D_80101620_name_81[partnerId]);
            if (sprIds[i] != -1) {
                HuSprKill(sprIds[i]);
            }
            sprIds[i] = func_80055810_main(data);
            DataClose(data);
        } else if (sprIds[i] == -1) {
            data = DataRead(files[i]);
            sprIds[i] = func_80055810_main(data);
            DataClose(data);
        }
        func_80055024_main(grp, base + i, sprIds[i], 0);
        func_800550F4_main(grp, base + i, 1);
        if (i == 0) {
            HuSprPriSet(grp, base, (playerNo * 5) + 0x4793);
        } else {
            HuSprPriSet(grp, base + i, (playerNo * 5) + 0x4792);
        }
        HuSprAttrReset(grp, base + i, 0x8000);
        func_80054904_main(grp, base + i, D_801015BC_name_81[playerNo][base + i][0], D_801015BC_name_81[playerNo][base + i][1]);
        if (i == 0) {
            HuSprAttrSet(grp, base, 0x1000);
            func_80055458_main(grp, base, 0xA4);
        } else if (i == 10) {
            HuSprAttrSet(grp, base + 10, 0x1000);
        } else {
            HuSprAttrSet(grp, base + i, 0);
        }
        if (i == 10) {
            HuSprAttrSet(grp, base + 10, 0x8000);
            func_80055420_main(grp, base + 10, 0, 0xFF, 0);
            func_80055458_main(grp, base + 10, 0xC0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F5834_name_81);
#endif

void func_800F5BB4_name_81(s32 playerIndex) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    s16 grp;
    s32 i;

    func_800F57B0_name_81(playerIndex);
    if (player->stats.partners.frontID != -1) {
        D_80105630_name_81[playerIndex].frontCost = -1;
        func_800F5834_name_81(playerIndex, player->stats.partners.frontID, D_80105630_name_81[playerIndex].frontSpr, 7);
        grp = D_80105630_name_81[playerIndex].grp;
        func_80055140_main(grp, 12, player->stats.partners.frontHp, 0);
        func_80055140_main(grp, 13, player->stats.partners.frontPower, 0);
        func_80055140_main(grp, 14, 12, 0);
        if (player->stats.partners.frontCost >= 10) {
            func_80055140_main(grp, 15, player->stats.partners.frontCost / 10, 0);
            func_80055140_main(grp, 16, player->stats.partners.frontCost % 10, 0);
            for (i = 0; i < 3; i++) {
                func_80054904_main(grp, i + 14, D_801015A4_name_81[i][0], -D_801015A4_name_81[i][1]);
            }
        } else {
            func_80055140_main(grp, 15, player->stats.partners.frontCost, 0);
            HuSprAttrSet(grp, 16, 0x8000);
            for (i = 0; i < 3; i++) {
                func_80054904_main(grp, i + 14, D_801015B0_name_81[i][0], -D_801015B0_name_81[i][1]);
            }
        }
    }
}

void func_800F5E2C_name_81(s32 playerNo) {
    DuelStatus *sp;
    s32 i;

    if (MBDGetPlayerStruct(playerNo)->stats.partners.backID == -1) {
        sp = &D_80105630_name_81[playerNo];
        for (i = 0; i < 11; i++) {
            HuSprAttrSet(sp->grp, i + 18, 0x8000);
        }
    }
}

void func_800F5EB0_name_81(s32 playerIndex) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    s16 grp;
    s32 i;

    func_800F5E2C_name_81(playerIndex);
    if (player->stats.partners.backID != -1) {
        D_80105630_name_81[playerIndex].backCost = -1;
        func_800F5834_name_81(playerIndex, player->stats.partners.backID, D_80105630_name_81[playerIndex].backSpr, 18);
        grp = D_80105630_name_81[playerIndex].grp;
        func_80055140_main(grp, 23, player->stats.partners.backHp, 0);
        func_80055140_main(grp, 24, player->stats.partners.backPower, 0);
        func_80055140_main(grp, 25, 12, 0);
        if (player->stats.partners.backCost >= 10) {
            func_80055140_main(grp, 26, player->stats.partners.backCost / 10, 0);
            func_80055140_main(grp, 27, player->stats.partners.backCost % 10, 0);
            for (i = 0; i < 3; i++) {
                func_80054904_main(grp, i + 25, D_801015A4_name_81[i][0], D_801015A4_name_81[i][1]);
            }
        } else {
            func_80055140_main(grp, 26, player->stats.partners.backCost, 0);
            HuSprAttrSet(grp, 27, 0x8000);
            for (i = 0; i < 3; i++) {
                func_80054904_main(grp, i + 25, D_801015B0_name_81[i][0], D_801015B0_name_81[i][1]);
            }
        }
    }
}

void func_800F6110_name_81(void) {
    s16 *spriteIDs = D_80105414_name_81;
    void *data;
    s32 i;

    data = DataRead(0x1300D6);
    spriteIDs[0] = func_80055810_main(data);
    DataClose(data);

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        data = DataRead(D_801015E0_name_81[i * 8 + GwPlayer[i].chr]);
        spriteIDs[i + 1] = func_80055810_main(data);
        DataClose(data);
    }

    data = DataRead(0x1300D7);
    spriteIDs[3] = func_80055810_main(data);
    DataClose(data);

    data = DataRead(0x1300D1);
    spriteIDs[5] = func_80055810_main(data);
    DataClose(data);
}

void func_800F6220_name_81(void) {
    s16 *spriteIDs = D_80105414_name_81;
    s32 i;

    HuSprKill(spriteIDs[0]);
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        HuSprKill(spriteIDs[i + 1]);
    }
    HuSprKill(spriteIDs[3]);
    HuSprKill(spriteIDs[5]);
}

void func_800F628C_name_81(s32 playerNo) {
    DuelStatus *sp = &D_80105630_name_81[playerNo];
    s32 i;

    sp->flags = 0;
    sp->prevCoins = -1;
    sp->prevStars = -1;
    func_800F55FC_name_81(playerNo);
    func_800F6550_name_81(playerNo, D_801014E8_name_81[playerNo][0], D_801014E8_name_81[playerNo][1]);
    func_800F52B8_name_81(playerNo);
    func_800F53C4_name_81(playerNo);
    func_800F54A4_name_81(playerNo);
    func_800F56C0_name_81(playerNo);
    for (i = 0; i < 11; i++) {
        sp->frontSpr[i] = -1;
        sp->backSpr[i] = -1;
    }
    sp->frontCost = -1;
    sp->backCost = -1;
    func_800F5BB4_name_81(playerNo);
    func_800F5EB0_name_81(playerNo);
    func_800F4710_name_81(playerNo);
    D_80105444_name_81[playerNo] = NULL;
    sp->unk_2C = NULL;
}

void func_800F6390_name_81(void) {
    s32 i;

    func_800F6110_name_81();
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        func_800F628C_name_81(i);
    }
    D_80105410_name_81 = omAddPrcObj(func_800F4F20_name_81, 0, 0x2000, 0);
    omPrcSetStatBit(D_80105410_name_81, 0x80);
    D_80105422_name_81 = -1;
    D_80105420_name_81 = -1;
}

void func_800F6408_name_81(s32 playerNo) {
    DuelStatus *sp = &D_80105630_name_81[playerNo];
    s32 i;

    HuSprKill(sp->numSpr);
    HuSprGrpKill(sp->grp);
    for (i = 0; i < 11; i++) {
        if (sp->frontSpr[i] != -1) {
            HuSprKill(sp->frontSpr[i]);
        }
        if (sp->backSpr[i] != -1) {
            HuSprKill(sp->backSpr[i]);
        }
    }
    if (sp->unk_2C != NULL) {
        omDelObj(sp->unk_2C);
        sp->unk_2C = NULL;
    }
    if (D_80105444_name_81[playerNo] != NULL) {
        omDelObj(D_80105444_name_81[playerNo]);
        D_80105444_name_81[playerNo] = NULL;
    }
}

void func_800F64FC_name_81(void) {
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        func_800F6408_name_81(i);
    }
    func_800F6220_name_81();
    HuPrcKill(D_80105410_name_81);
    func_800F6F84_name_81();
}

void func_800F6550_name_81(s32 playerNo, s16 x, s16 y) {
    DuelStatus *sp = &D_80105630_name_81[playerNo];

    sp->xPos = sp->targetX = x;
    sp->yPos = sp->targetY = y;
    sp->velX = sp->velY = 0.0f;
    sp->timer = -2;
    func_80054904_main(sp->grp, 0, x + 48, y + 24);
}

void func_800F6600_name_81(s32 playerNo, s16 *x, s16 *y) {
    DuelStatus *sp = &D_80105630_name_81[playerNo];

    *x = sp->xPos;
    *y = sp->yPos;
}

void func_800F664C_name_81(s32 playerNo, s32 side) {
    s32 index = (side * 2) + playerNo;

    func_800F6550_name_81(playerNo, D_801014E8_name_81[index][0], D_801014E8_name_81[index][1]);
}

void func_800F6688_name_81(s32 playerNo, s32 slot) {
    func_800F6550_name_81(playerNo, D_801014E8_name_81[slot][0], D_801014E8_name_81[slot][1]);
}

s32 func_800F66BC_name_81(s32 arg0) {
    u8 slot[8];
    u8 group1[8];
    u8 group2[8];
    DuelStatus *sp;
    s32 i;
    u8 group1Count;
    u8 group2Count;
    u8 otherCount;

    group1Count = 0;
    group2Count = 0;

    if (arg0 == 2) {
        for (i = 0; i < 3; i++) {
            group1[i] = i;
        }
        group1Count = 3;
        group2Count = 0;
        otherCount = 0;
        for (i = 0; i < group1Count; i++) {
            slot[group1[i]] = otherCount++;
        }
    }

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        sp = &D_80105630_name_81[i];

        if ((arg0 >= 8) && (arg0 <= 9) && (i != arg0 - 8)) continue;
        if ((arg0 >= 10) && (arg0 <= 11) && (i != arg0 - 10)) continue;
        if ((arg0 >= 12) && (arg0 <= 13) && (i != arg0 - 12)) continue;

        switch (arg0) {
        case 0:
        case 8:
        case 9:
            func_800F6550_name_81(i, D_801014E8_name_81[i + 2][0], D_801014E8_name_81[i + 2][1]);
            break;
        }

        sp->timer = 19;
        switch (arg0) {
        case 14:
        case 15:
            sp->timer = 5;
            goto dummy;
        case 6:
        case 7:
            sp->timer = 15;
            goto dummy;
        case 0:
        case 1:
        case 3:
        case 4:
        case 8:
        case 9:
        dummy:
            sp->targetX = D_801014E8_name_81[D_801015C4_name_81[arg0] + i][0];
            sp->targetY = D_801014E8_name_81[D_801015C4_name_81[arg0] + i][1];
            break;
        case 2:
            sp->targetX = D_80101650_name_81[group1Count][slot[i]][0];
            sp->targetY = D_80101650_name_81[group1Count][slot[i]][1];
            sp->timer = 9;
            break;
        case 5:
            if (sp->xPos >= 160.0f) {
                sp->targetX = sp->xPos + 1920.0f;
            } else {
                sp->targetX = sp->xPos - 1920.0f;
            }
            sp->targetY = sp->yPos;
            sp->timer = 19;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
            sp->targetX = D_801014E8_name_81[D_801015C4_name_81[arg0] + i][0];
            sp->targetY = sp->yPos;
            break;
        }

        sp->velX = sp->accX = (2.0f * (sp->targetX - sp->xPos)) / (f32) ((sp->timer + 1) * (sp->timer + 1));
        sp->velY = sp->accY = (2.0f * (sp->targetY - sp->yPos)) / (f32) ((sp->timer + 1) * (sp->timer + 1));

        if (arg0 == 5) {
            D_80105430_name_81.x = D_80105438_name_81.x = 0.0f;
            D_80105430_name_81.y = D_80105438_name_81.y = 2.0f;
            D_80105440_name_81 = sp->timer;
        }
    }

    if ((arg0 == 2) && (group1Count != 5)) {
        if ((group1Count == 4) || (group1Count == 0)) {
            for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                GwPlayer[i].group = i;
            }
        } else if (group1Count == 3) {
            for (i = 0; i < group1Count; i++) {
                GwPlayer[group1[i]].group = 1;
            }
            for (i = 0; i < group2Count; i++) {
                GwPlayer[group2[i]].group = 0;
            }
        } else {
            for (i = 0; i < group1Count; i++) {
                GwPlayer[group1[i]].group = 0;
            }
            for (i = 0; i < group2Count; i++) {
                GwPlayer[group2[i]].group = 1;
            }
        }
    }

    if ((arg0 == 6) || (arg0 == 7)) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (i == arg0 - 6) {
                GwPlayer[i].group = 0;
            } else {
                GwPlayer[i].group = 1;
            }
        }
    }

    return 0;
}

s32 func_800F6CA0_name_81(void) {
    s32 var_a0 = FALSE;
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (D_80105630_name_81[i].timer != -2) {
            var_a0 = TRUE;
        }
    }
    return var_a0;
}

void func_800F6CEC_name_81(void) {
    void *data;

    if (D_80105420_name_81 == -1) {
        D_80105420_name_81 = HuSprGrpCreate(1, 0);
        data = DataRead(0x130115);
        D_80105428_name_81.y = 158.0f;
        D_80105422_name_81 = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80105420_name_81, 0, D_80105422_name_81, 0);
        HuSprPriSet(D_80105420_name_81, 0, 0x4780);
        HuSprAttrSet(D_80105420_name_81, 0, 0x1000);
        func_80054904_main(D_80105420_name_81, 0, 0xA0, D_80105428_name_81.y);
        HuSprScaleSet(D_80105420_name_81, 0, 0.0f, 0.0f);
        D_80105424_name_81 = 10.0f;
        D_80105428_name_81.x = 160.0f;
        D_80105430_name_81.x = D_80105430_name_81.y = 0.0f;
        D_80105440_name_81 = 0;
    }
}

void func_800F6E3C_name_81(f32 x, f32 y) {
    void *data;

    if (D_80105420_name_81 == -1) {
        D_80105420_name_81 = HuSprGrpCreate(1, 5);
        data = DataRead(0x130261);
        D_80105428_name_81.y = y;
        D_80105422_name_81 = func_80055810_main(data);
        DataClose(data);
        func_80055024_main(D_80105420_name_81, 0, D_80105422_name_81, 0);
        HuSprPriSet(D_80105420_name_81, 0, 0x4780);
        HuSprAttrSet(D_80105420_name_81, 0, 0x1000);
        func_80054904_main(D_80105420_name_81, 0, 0xA0, D_80105428_name_81.y);
        HuSprScaleSet(D_80105420_name_81, 0, 0.0f, 0.0f);
        D_80105424_name_81 = 0.0f;
        D_80105428_name_81.x = x;
        D_80105430_name_81.x = D_80105430_name_81.y = 0.0f;
        D_80105440_name_81 = 0;
    }
}

void func_800F6F84_name_81(void) {
    if (D_80105420_name_81 != -1) {
        HuSprGrpKill(D_80105420_name_81);
        D_80105420_name_81 = -1;
    }
    if (D_80105422_name_81 != -1) {
        HuSprKill(D_80105422_name_81);
        D_80105422_name_81 = -1;
    }
}

void func_800F6FE8_name_81(omObjData *obj) {
    s32 var_s1 = 0;

    while (obj->scale.y <= 0.0f) {
        if (obj->trans.x > 0.0f) {
            func_800F37E0_name_81(obj->work[0], 1);
            if (((obj->work[3] != 0) & (var_s1 == 0)) && (obj->scale.z >= 3.0f)) {
                HuAudFXPlay(0x106);
                var_s1 = 1;
                obj->scale.z -= 3.0f;
            }
            obj->trans.x -= 1.0f;
        } else {
            func_800F37E0_name_81(obj->work[0], -1);
            obj->trans.x += 1.0f;
            if (obj->work[3] != 0) {
                if ((var_s1 == 0) && (obj->scale.z >= 3.0f)) {
                    HuAudFXPlay(0x109);
                    var_s1 = 1;
                    obj->scale.z -= 3.0f;
                }
                if ((obj->trans.x == 0.0f) || (GwPlayer[obj->work[0]].coin == 0)) {
                    HuAudFXPlay(0x10A);
                }
            }
        }

        if ((obj->trans.x == 0.0f) || (GwPlayer[obj->work[0]].coin == 0)) {
            D_80105444_name_81[obj->work[0]] = NULL;
            omDelObj(obj);
            return;
        }
        obj->scale.y += obj->scale.x;
    }

    obj->scale.y -= 1.0f;
    obj->scale.z += 2.0f;
}

void func_800F7228_name_81(s32 playerIndex, s32 coinAmount, s32 arg2) {
    if (coinAmount != 0) {
        if (D_80105444_name_81[playerIndex] != NULL) {
            func_800F37E0_name_81(playerIndex, coinAmount);
            return;
        }

        if ((GwPlayer[playerIndex].coin == 0) && (coinAmount < 0)) {
            return;
        }

        D_80105444_name_81[playerIndex] = omAddObj(-0x8000, 0, 0, -1, func_800F6FE8_name_81);
        D_80105444_name_81[playerIndex]->work[0] = playerIndex;
        D_80105444_name_81[playerIndex]->trans.x = coinAmount;

        D_80105444_name_81[playerIndex]->scale.x = coinAmount > 0.0f ? (30.0f / coinAmount) : (30.0f / (0.0f - coinAmount));

        (D_80105444_name_81[playerIndex])->scale.y = 0.0f;
        (D_80105444_name_81[playerIndex])->scale.z = 3.0f;
        (D_80105444_name_81[playerIndex])->work[3] = arg2;
    }
}

void func_800F7378_name_81(s32 playerIndex, s32 coinAmount) {
    func_800F7228_name_81(playerIndex, coinAmount, 1);
}

s32 func_800F7394_name_81(s32 playerIndex) {
    if (D_80105444_name_81[playerIndex]) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 func_800F73AC_name_81(void) {
    if (D_80105630_name_81->flags & 1) {
        return FALSE;
    } else {
        return TRUE;
    }
}

void func_800F73C0_name_81(void) {
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        D_80105630_name_81[i].flags |= 1;
    }
}

void func_800F740C_name_81(void) {
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        D_80105630_name_81[i].flags &= ~1;
    }
}

void func_800F7458_name_81(s32 playerNo, f32 x, f32 y) {
    DuelStatus *sp = &D_80105630_name_81[playerNo];
    s32 i;

    for (i = 0; i < 29; i++) {
        HuSprScaleSet(sp->grp, i, x, y);
    }
}

void func_800F74E4_name_81(s32 playerNo) {
    f32 angle;
    s32 i;

    for (angle = 0.0f; angle <= 90.0f; angle += 15.0f) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (playerNo == -1 || playerNo == i) {
                func_800F7458_name_81(i, cosdf(angle), 1.0f);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (playerNo == -1 || playerNo == i) {
            func_800F7458_name_81(i, 0.0f, 0.0f);
        }
    }
    HuPrcVSleep();
}

void func_800F75EC_name_81(s32 playerNo) {
    f32 angle;
    s32 i;

    for (angle = 90.0f; angle >= 0.0f; angle -= 15.0f) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (playerNo == -1 || playerNo == i) {
                func_800F7458_name_81(i, cosdf(angle), 1.0f);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (playerNo == -1 || playerNo == i) {
            func_800F7458_name_81(i, 1.0f, 1.0f);
        }
    }
    HuPrcVSleep();
}

#ifdef NON_MATCHING
void func_800F76F8_name_81(s32 playerNo, s32 x, s32 y, s32 back) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerNo);
    s32 base;
    s16 grp;
    s32 i;

    base = 18;
    if (back == 0) {
        base = 7;
    }
    grp = D_80105630_name_81[playerNo].grp;
    for (i = base; i < base + 11; i++) {
        func_80054904_main(grp, i, x + D_801015BC_name_81[playerNo][i][0], y + D_801015BC_name_81[playerNo][i][1]);
    }
    if (back == 0) {
        if (player->stats.partners.frontCost >= 10) {
            for (i = 0; i < 3; i++) {
                func_80054904_main(grp, base + (i + 7), x + D_801015A4_name_81[i][0], y - D_801015A4_name_81[i][1]);
            }
        } else {
            for (i = 0; i < 3; i++) {
                func_80054904_main(grp, base + (i + 7), x + D_801015B0_name_81[i][0], y - D_801015B0_name_81[i][1]);
            }
        }
    } else {
        if (player->stats.partners.backCost >= 10) {
            for (i = 0; i < 3; i++) {
                func_80054904_main(grp, base + (i + 7), x + D_801015A4_name_81[i][0], y + D_801015A4_name_81[i][1]);
            }
        } else {
            for (i = 0; i < 3; i++) {
                func_80054904_main(grp, base + (i + 7), x + D_801015B0_name_81[i][0], y + D_801015B0_name_81[i][1]);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/DC4E0", func_800F76F8_name_81);
#endif

void func_800F79D0_name_81(s32 arg0) {
    D_801014E0_name_81 = arg0;
}

void func_800F79DC_name_81(s32 arg0) {
    D_801014E4_name_81 = arg0;
}

void func_800F79E8_name_81(s32 playerNo) {
    f32 amp;
    f32 angle;
    s32 mask;
    s32 i;

    if (playerNo == -1) {
        mask = 3;
    } else {
        mask = 1 << playerNo;
    }
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (mask & (1 << i)) {
            func_800F7458_name_81(i, 0.0f, 0.0f);
        }
    }
    HuPrcVSleep();
    amp = 1.0f;
    for (angle = 0.0f; angle < 720.0f; angle += 60.0f) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (mask & (1 << i)) {
                func_800F7458_name_81(i, 1.0f - (cosdf(angle) * amp), 1.0f - (cosdf(angle) * amp));
            }
        }
        amp -= 1.0f / 12.0f;
        if (amp < 0.0f) {
            amp = 0.0f;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (mask & (1 << i)) {
            func_800F7458_name_81(i, 1.0f, 1.0f);
        }
    }
    HuPrcVSleep();
}

void func_800F7BB4_name_81(s32 playerNo, s32 set) {
    DuelStatus *sp;
    s8 *list;
    f32 scale;
    s32 mask;
    s32 step;
    s32 i;
    s32 j;

    if (playerNo == -1) {
        mask = 3;
    } else {
        mask = 1 << playerNo;
    }
    for (step = 10; step < 31; step += 10) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (mask & (1 << i)) {
                sp = &D_80105630_name_81[i];
                list = D_80101660_name_81[set];
                for (j = 0; j < 29; j++) {
                    if (j == *list) {
                        list++;
                        scale = step / 10.0f;
                        HuSprScaleSet(sp->grp, j, scale, scale);
                        func_80054904_main(sp->grp, j, D_801015BC_name_81[playerNo][j][0] / scale, D_801015BC_name_81[playerNo][j][1] / scale);
                        HuSprPriSet(sp->grp, j, 1);
                    }
                }
            }
        }
        HuPrcVSleep();
    }
}

void func_800F7D94_name_81(s32 playerNo, s32 set) {
    DuelStatus *sp;
    s8 *list;
    f32 scale;
    s32 mask;
    s32 step;
    s32 i;
    s32 j;

    if (playerNo == -1) {
        mask = 3;
    } else {
        mask = 1 << playerNo;
    }
    for (step = 30; step >= 10; step -= 2) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (mask & (1 << i)) {
                sp = &D_80105630_name_81[i];
                list = D_80101660_name_81[set];
                for (j = 0; j < 29; j++) {
                    if (j == *list) {
                        list++;
                        scale = step / 10.0f;
                        HuSprScaleSet(sp->grp, j, scale, scale);
                        func_80054904_main(sp->grp, j, D_801015BC_name_81[playerNo][j][0] / scale, D_801015BC_name_81[playerNo][j][1] / scale);
                        if (step == 10) {
                            HuSprPriSet(sp->grp, j, (i * 5) + 0x4792);
                        }
                    }
                }
            }
        }
        HuPrcVSleep();
    }
}
