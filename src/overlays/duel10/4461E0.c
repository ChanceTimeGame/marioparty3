#include "common.h"

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801059D0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105A58_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105B10_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105B64_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105BA0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105CD0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105D2C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105F1C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105F8C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010613C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801061C8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801062AC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801062CC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010632C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80106374_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801064C8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80106534_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801067AC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80106840_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80106894_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801071F4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80107A24_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80107F28_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80108510_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801085BC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80109470_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801098F4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010A27C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010AB1C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010ADB4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B020_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B19C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B4EC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B52C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B594_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B5A8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B5B8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010BD40_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010CED4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010D490_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010D9C8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DA60_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DAE8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DB24_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DB60_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DD5C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DDA4_duel10);

// board ec2: declarations for func_8010E0EC_duel10..func_8010FE0C_duel10
#include "process.h"
#include "common_structs.h"
#include "malloc.h"
#include "game/board.h"
#include "game/object.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "input.h"
#include "variables.h"

/* Part of a model looked up by name (func_8001D33C_main). */
typedef struct Ec2HmfPart {
    /* 0x00 */ char unk_00[0x14];
    /* 0x14 */ f32 unk_14;
} Ec2HmfPart;

/* A player's model object, read for its current motion. */
typedef struct Ec2PlayerModel {
    /* 0x00 */ char unk_00[0x48];
    /* 0x48 */ s16 curMot;
} Ec2PlayerModel;

/* main */
void *func_8001D33C_main(s16 model, char *name);
void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4);

/* ovl_81 */
void func_800D8944_name_81(Object *);
Object *func_800D8010_name_81(u8, s32 *);
void func_800D90D0_name_81(Object *, s16, u16);
void func_800D918C_name_81(Object *, s16, s16, s16, u16);
s32 func_800D9234_name_81(Object *);
void func_800DADA0_name_81(s32);
s32 func_800DB3E0_name_81(s32);
void func_800DB4DC_name_81(s32);
void func_800DC07C_name_81(s32, s16);
s32 func_800DC0B4_name_81(s32);
Process *func_800DC324_name_81(s32);
void func_800DC3AC_name_81(s32 playerIndex);
void func_800DC410_name_81(s32 playerIndex);
void func_800E14B0_name_81(s32 player, s32 coins);
void func_800E14D8_name_81(s32, s32);
Process *func_800E39AC_name_81(s32);
void func_800E4EAC_name_81(UnkMBGuideData *guide, s16 x, s16 arg2);
void func_800EA388_name_81(s16);
void func_800EA698_name_81(s16);
void func_800EA788_name_81(s16, s32);
void func_800EA7D4_name_81(void);
void func_800EA97C_name_81(void);
void func_800EAFC4_name_81(s32 mess);
void func_800EB708_name_81(Vec *, Vec *, Vec *);
void func_800EB7BC_name_81(Vec *out);
void func_800EB7D8_name_81(s16);
Process *func_800EBC60_name_81(Vec *arg0, Vec *arg1, Vec *arg2, s32 arg3);
Process *func_800EC1E4_name_81(Vec *, Vec *, Vec *, f32);
void func_800ECC34_name_81(s16, f32);
void func_800ECE38_name_81(s32);
void func_800EF754_name_81(s32 winId);
void func_800EF800_name_81(Object *);
void func_800EFABC_name_81(Object *);
void func_800F38DC_name_81(s32, s32, s32);
void func_800F3A04_name_81(s32, s16, s16, s16, u16);
void func_800F3AF4_name_81(s32, f32);
void func_800F7378_name_81(s32, s32);
void func_800F924C_name_81(s32);
void func_800FAD04_name_81(s32);
void func_800FADB4_name_81(void);
void func_800FAE18_name_81(Object *, s16, s16);
void func_800FC108_name_81(void);
void func_800FC4E4_name_81(void);
void func_800FC888_name_81(s32);
void func_800FC8C4_name_81(Vec *);
void func_800FCC84_name_81(s16);
void func_800FCCCC_name_81(s16);
void func_800FCF50_name_81(s32, s32);
s32 func_800FD498_name_81(void);
void func_800FFA28_name_81(Vec *);
s16 MBDGetCurrentPlayerIndex(void);
GW_PLAYER *MBDGetPlayerStruct(s32 playerIndex);
Object *MBDGetPlayerPartnerRef(s32 playerIndex, s32 frontOrBackIndex);
SpaceData *MBDMasuGet(s16);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
Process *MBDCameraZoomMotStart(f32);
void MBDCameraZoomSet(f32);
void MBDCameraPos2DGet(Vec2f *);
u16 MBDCameraPos2DSet(Vec2f *);
extern u8 D_80100E20_name_81;

/* this unit, outside ec2's range */
s16 func_8010DDA4_duel10(s32 padNo);
s32 func_80114940_duel10(void);

/* ec2's range */
void func_8010E4B4_duel10(s32 steps, s32 walkNum);
void func_8010ECA0_duel10(UnkMBGuideData *guide, s32 mess);
void func_8010EF98_duel10(void);
void func_8010F070_duel10(void);
void func_8010F258_duel10(void);
void func_8010F620_duel10(void);
void func_8010F864_duel10(void);
void func_8010FC2C_duel10(void);

/* data (still in the asm .data/.bss) */
extern u8 D_800CC0BA_main;
extern s8 D_801149D3_duel10; /* message speed saved at board start */
extern s32 D_80114A30_duel10;
extern s32 D_80114A3C_duel10;
extern s16 D_80114A40_duel10; /* motion requested of the guide, -1 = none */
extern f32 D_80114A44_duel10;
extern s32 D_80114A48_duel10[];
extern s16 D_80114A58_duel10;
extern s16 D_80114A5A_duel10;
extern Process *D_80114A5C_duel10;
extern s16 D_80114A60_duel10;
extern s16 D_80114A62_duel10;
extern Process *D_80114A64_duel10;
extern s32 D_80114A68_duel10;
extern char D_80114BBC_duel10[]; /* "bell" */
extern UnkMBGuideData *D_80114CD0_duel10;
extern Object *D_80114CD4_duel10;
extern Process *D_80114CD8_duel10;
extern Object *D_80114CDC_duel10;
extern f32 D_80114CE0_duel10;
extern Object *D_80114CE4_duel10;
extern f32 D_80114CE8_duel10;
// board ec2: end

// board ec2: pause watcher: Start opens the pause menu; quitting leaves Duel Mode.
void func_8010E0EC_duel10(void) {
    Vec2f sp10;
    s32 curPlayerNo;
    s32 i;

    while (1) {
        HuPrcVSleep();
        if (WipeStatGet() != 0) {
            continue;
        }
        if (D_800CC0BA_main == 3) {
            continue;
        }
        curPlayerNo = MBDGetCurrentPlayerIndex();
        for (i = 0; i < 4; i++) {
            if (!(D_800C9520_main[i] & START_BUTTON)) {
                continue;
            }
            if (D_80114A30_duel10 == 0) {
                continue;
            }
            func_800DC3AC_name_81(curPlayerNo);
            MBDCameraPos2DGet(&sp10);
            MBDCameraPos2DSet(&sp10);
            D_800CB99C_main = 1;
            func_80049FB8_main();
            HmfPauseF = 1;
            if (func_8010DDA4_duel10(i) != 0) {
                GwSystem.message_speed = D_801149D3_duel10;
                HuAudSeqFadeOut(0x5A);
                WipeCreateOut(0, 0x10);
                HuPrcSleep(0x11);
                func_800FC4E4_name_81();
                func_800FC108_name_81();
                omOvlReturnEx(1);
                omOvlKill();
                HuPrcVSleep();
            }
            HmfPauseF = 0;
            func_8004A0E0_main();
            D_800CB99C_main = 0;
            func_800DC410_name_81(curPlayerNo);
            break;
        }
    }
}

void func_8010E258_duel10(void) {
}

void func_8010E260_duel10(void) {
}

#ifdef NON_MATCHING
// board ec2: the turn passes to the other player; both stand idle facing the camera.
// board ec2: masked 13: retail never keeps &GwSystem.current_player_index in a register (it reads it as if a scalar global); this C shares the address
void func_8010E268_duel10(void) {
    GW_PLAYER *player;
    s32 i;
    s8 cur;

    cur = GwSystem.current_player_index + 1;
    GwSystem.current_player_index = cur;
    if (cur >= 2) {
        GwSystem.current_player_index = 0;
    }
    for (i = 0; i < 2; i++) {
        player = MBDGetPlayerStruct(i);
        func_800EB7D8_name_81(i);
        func_800D90D0_name_81(player->player_obj, -1, 2);
        func_800FCF50_name_81(i, 1);
    }
    HuPrcVSleep();
    MBDCameraZoomSet(1.4f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E268_duel10);
#endif

void func_8010E31C_duel10(Vec *arg0) {
    func_800FFA28_name_81(arg0);
}

void func_8010E338_duel10(void) {
    Process *proc = HuPrcCurrentGet();

    HuPrcChildLink(proc, func_800E39AC_name_81(GwSystem.current_player_index));
    HuPrcChildWait();
}

#ifdef NON_MATCHING
// board ec2: roll the dice block (arg0 = block kind) and wait for the roll.
// board ec2: masked 8: GwSystem.current_player_index address shared in a register here, re-formed per use in retail (see func_8010E268_duel10)
void func_8010E37C_duel10(s16 arg0) {
    Process *diceProc;
    Process *proc;

    func_800DC07C_name_81(GwSystem.current_player_index, arg0);
    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, MBDCameraZoomMotStart(1.7f));
    diceProc = func_800DC324_name_81(GwSystem.current_player_index);
    HuPrcChildWait();
    HuPrcChildLink(proc, diceProc);
    HuPrcChildWait();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E37C_duel10);
#endif

#ifdef NON_MATCHING
// board ec2: as func_8010E37C_duel10 with the roll flag set; func_8010E494_duel10 waits for it.
// board ec2: masked 8: as func_8010E37C_duel10
void func_8010E408_duel10(s16 arg0) {
    Process *diceProc;
    Process *proc;

    func_800DC07C_name_81(GwSystem.current_player_index, arg0);
    D_80100E20_name_81 = 1;
    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, MBDCameraZoomMotStart(1.7f));
    diceProc = func_800DC324_name_81(GwSystem.current_player_index);
    HuPrcChildWait();
    HuPrcChildLink(proc, diceProc);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E408_duel10);
#endif

void func_8010E494_duel10(void) {
    D_80100E20_name_81 = 0;
    HuPrcChildWait();
}

#ifdef NON_MATCHING
// board ec2: walk the current player: `steps` spaces at most (-1: no limit), `walkNum` counted spaces
// (0: the dice roll); func_80114940_duel10 may stop the walk for an event.
// board ec2: masked 30: the saved clink/cidx are sign-extended in retail, and the in-loop motion calls are not cross-jumped; logic checked against the asm block by block
void func_8010E4B4_duel10(s32 steps, s32 walkNum) {
    Vec sp18;
    Process *proc;
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    SpaceData *space;
    s32 ret;
    s32 speed;
    s16 masuId;
    s16 num;
    s8 clink;
    s8 cidx;

    player = MBDGetPlayerStruct(-1);
    speed = 1;
    proc = HuPrcCurrentGet();
    if (walkNum != 0) {
        num = walkNum;
    } else {
        num = func_800DC0B4_name_81(system->current_player_index);
    }
    func_800ECE38_name_81(system->current_player_index);
    if (!(player->rev & 2)) {
        func_800F3A04_name_81(-1, 0, 0, 5, 2);
    } else {
        func_800F3A04_name_81(-1, 0, 0, 5, 6);
    }
    while (num != 0 && steps != 0) {
        if (func_80114940_duel10() != 0) {
            ret = func_80114940_duel10();
            if (ret != -1) {
                func_800F38DC_name_81(-1, -1, 2);
                func_800DB3E0_name_81(player->turn);
                func_800F924C_name_81(ret);
                func_800DADA0_name_81(player->turn);
                HuPrcChildLink(proc, MBDCameraZoomMotStart(1.7f));
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
        func_800FCF50_name_81((s8)(system->current_player_index ^ 1), (speed * 7) + 8);
        player->clink = clink;
        player->cidx = cidx;
        space = MBDMasuGet(MBDMasuLinkMasuIdGet(player->nlink, player->nidx));
        if (((Ec2PlayerModel *)player->player_obj)->curMot != 0) {
            if (!(player->rev & 2)) {
                func_800F3A04_name_81(-1, 0, 0, 5, 2);
            } else {
                func_800F3A04_name_81(-1, 0, 0, 5, 6);
            }
        }
        switch (speed) {
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
                num--;
                steps--;
                func_800EA388_name_81(masuId);
                break;
        }
        if (walkNum == 0) {
            if (num != 0) {
                func_800FCC84_name_81(space->space_type);
            } else {
                func_800FCCCC_name_81(space->space_type);
            }
        }
    }
    func_800F38DC_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&sp18);
    func_800EBC60_name_81(&player->player_obj->rot, &sp18, &player->player_obj->rot, 8);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E4B4_duel10);
#endif

void func_8010E8D4_duel10(void) {
    func_8010E4B4_duel10(-1, 0);
}

#ifdef NON_MATCHING
// board ec2: the space the current player landed on: an event space, or a character space (11..18)
// that pays the owner, or with a coin partner prize takes coins from the rival.
// board ec2: masked 35: masuId kept unextended and the direct GwSystem.current_player_index reads not shared with `system` in retail; logic checked against the asm block by block
void func_8010E8F4_duel10(void) {
    Vec sp10;
    Vec sp20;
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    Process *proc;
    SpaceData *space;
    Object *partner;
    s32 masuId;
    s32 amount;

    player = MBDGetPlayerStruct(-1);
    proc = HuPrcCurrentGet();
    masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
    space = MBDMasuGet(masuId);
    switch (space->space_type) {
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            amount = func_800FD498_name_81();
            if (space->space_type - 11 == GwPlayer[GwSystem.current_player_index].chr) {
                func_800E14D8_name_81(GwSystem.current_player_index, amount);
                func_800F7378_name_81(GwSystem.current_player_index, amount);
                HuPrcSleep(30);
            } else if (player->stats.prize.gamblePrize == 2 || player->stats.prize.duelNo == 2) {
                partner = MBDGetPlayerPartnerRef(system->current_player_index,
                                                 (player->stats.prize.duelNo != 2) ? 0 : 1);
                HuPrcChildLink(proc, MBDCameraZoomMotStart(2.0f));
                HuPrcChildWait();
                HuVecCopy3F(&sp20, &player->player_obj->coords);
                func_800FC888_name_81(4);
                func_800FC8C4_name_81(&sp20);
                HuPrcChildLink(proc, func_800EC1E4_name_81(&sp20, &partner->coords, &sp20, 2.0f));
                HuPrcChildWait();
                func_800EB7BC_name_81(&sp10);
                func_800EBC60_name_81(&partner->rot, &sp10, &partner->rot, 8);
                HuPrcSleep(8);
                func_800FAD04_name_81(2);
                func_800FAE18_name_81(partner, 1, 0);
                func_800EFABC_name_81(partner);
                func_800D90D0_name_81(partner, -1, 2);
                func_800FADB4_name_81();
                func_800EAFC4_name_81(0x1F1C);
            } else {
                if (GwPlayer[system->current_player_index].coin == 0) {
                    amount = 0;
                    func_800EAFC4_name_81(0x1F1B);
                } else if (GwPlayer[system->current_player_index].coin < amount) {
                    amount = GwPlayer[system->current_player_index].coin;
                }
                if (amount != 0) {
                    func_800E14D8_name_81(system->current_player_index, -amount);
                    func_800F7378_name_81(system->current_player_index, -amount);
                    HuPrcSleep(30);
                    func_800E14B0_name_81((s8)(system->current_player_index ^ 1), amount);
                    func_800F7378_name_81((s8)(system->current_player_index ^ 1), amount);
                    HuPrcSleep(30);
                }
            }
            break;
        case 6:
            HuPrcSleep(8);
            func_800EA788_name_81(masuId, system->current_player_index);
            func_800EA7D4_name_81();
            func_800EA97C_name_81();
            HuAudFXPlay(0x201);
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E8F4_duel10);
#endif

// board ec2: turn the current player around (sets the reverse flags).
void func_8010EC1C_duel10(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);
    s8 nlink = player->nlink;
    s8 nidx = player->nidx;

    player->nlink = player->blink;
    player->nidx = player->bidx;
    player->blink = nlink;
    player->bidx = nidx;
    player->rev = 7;
}

// board ec2: turn the current player back (clears the reverse flags).
void func_8010EC60_duel10(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(-1);
    s8 nlink = player->nlink;
    s8 nidx = player->nidx;

    player->nlink = player->blink;
    player->nidx = player->bidx;
    player->blink = nlink;
    player->bidx = nidx;
    player->rev = 0;
}

// board ec2: the guide speaks message `mess` in its window and waits for it to close.
void func_8010ECA0_duel10(UnkMBGuideData *guide, s32 mess) {
    func_8005B43C_main(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
    func_800EF754_name_81(guide->amount);
    D_80114A3C_duel10 = 1;
    func_80060EA8_main(guide->amount, 1);
    func_8005D294_main(guide->amount);
    HuPrcVSleep();
}

void func_8010ED14_duel10(UnkMBGuideData *guide, s32 mess) {
    func_8005B43C_main(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
}

void func_8010ED50_duel10(UnkMBGuideData *guide) {
    func_800EF754_name_81(guide->amount);
    func_80060EA8_main(guide->amount, 1);
    func_8005D294_main(guide->amount);
    HuPrcVSleep();
}

void func_8010ED98_duel10(UnkMBGuideData *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    func_800EF800_name_81(guide->obj);
    func_800D90D0_name_81(guide->obj, -1, 2);
}

#ifdef NON_MATCHING
// board ec2: slide the guide from its x position to x over 14 frames, then idle.
// board ec2: masked 0; raw residue is the register allocation (guide s1, x - start in a1 in retail)
void func_8010EDF8_duel10(UnkMBGuideData *guide, s16 x) {
    s32 i;
    s32 step;
    s16 start = guide->spriteGroup;
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.5f;
    step = (x - start) / 14;
    for (i = 0; i < 14; i++) {
        func_800E4EAC_name_81(guide, guide->spriteGroup + step, 0);
        HuPrcVSleep();
    }
    func_800E4EAC_name_81(guide, x, 0);
    func_800D90D0_name_81(guide->obj, -1, 2);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010EDF8_duel10);
#endif

// board ec2: guide motion process: plays each motion D_80114A40_duel10 requests, then idles.
void func_8010EEE4_duel10(void) {
    Object **obj = HuPrcCurrentGet()->user_data;

    while (1) {
        do {
            HuPrcVSleep();
        } while (D_80114A40_duel10 == -1);
        func_800D918C_name_81(*obj, D_80114A40_duel10, 0, 10, 0);
        D_80114A40_duel10 = -1;
        while (!(u16)func_800D9234_name_81(*obj) && D_80114A40_duel10 == -1) {
            HuPrcVSleep();
        }
        func_800D90D0_name_81(*obj, -1, 2);
    }
}

// board ec2: from duel05 (func_8010DB3C_duel05..func_8010E308_duel05); two sets for the two swinging signs
void func_8010EF98_duel10(void) {
    Ec2HmfPart *part;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_80114CD4_duel10->omObj1->model[0], HmfModelData[D_80114CD4_duel10->omObj1->model[0]].unk02, "neji", 0x4C, 0x46);
        part = func_8001D33C_main(D_80114CD4_duel10->omObj1->model[0], "neji");
        angle += D_80114A44_duel10;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        part->unk_14 = angle;
        HuPrcVSleep();
    }
}

void func_8010F070_duel10(void) {
    s16 model = D_80114CD4_duel10->omObj1->model[0];

    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114BBC_duel10, 0x4C, 0x46);
    ((Ec2HmfPart *)func_8001D33C_main(D_80114CD4_duel10->omObj1->model[0], D_80114BBC_duel10))->unk_14 =
        (GwSystem.bank_coins - 5) * 60;
}

void func_8010F114_duel10(void) {
    Object *obj;

    obj = func_800D8010_name_81(0x34, D_80114A48_duel10);
    func_800D8944_name_81(obj);
    D_80114CD4_duel10 = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBDMasuGet(0x14)->coords);
    func_8010F070_duel10();
    D_80114CD8_duel10 = omAddPrcObj(func_8010EF98_duel10, 0xA, 0, 0);
    omPrcSetStatBit(D_80114CD8_duel10, 0xA0);
}

void func_8010F1A8_duel10(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x32, 0);
    func_800D8944_name_81(obj);
    D_80114CDC_duel10 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80114A58_duel10);
    to = MBDMasuGet(D_80114A5A_duel10);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010F258_duel10(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_80114CE0_duel10;
        sincosdf(rot, &HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010F3D4_duel10(Vec *pos) {
    Process *process;
    s32 *angle;

    D_80114CE0_duel10 = 10.0f;
    process = omAddPrcObj(func_8010F258_duel10, 0xA, 0, 0x40);
    D_80114A5C_duel10 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_80114CDC_duel10->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010F474_duel10(void) {
    HmfModel *mdl;

    if (D_80114A5C_duel10 != NULL) {
        while (D_80114CE0_duel10 >= 0.0f) {
            D_80114CE0_duel10 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80114A5C_duel10);
        sincosdf(0.0f, &HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80114CDC_duel10->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80114CDC_duel10->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114BBC_duel10);

void func_8010F620_duel10(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_80114CDC_duel10->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_80114CDC_duel10->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80114CDC_duel10);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_80114CDC_duel10->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_80114CDC_duel10->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010F738_duel10(void) {
    omAddPrcObj(func_8010F620_duel10, 0xA, 0, 0);
}

void func_8010F764_duel10(void) {
    func_8001C814_main(D_80114CDC_duel10->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_80114CDC_duel10->omObj1->model[0], 1.0f);
}

void func_8010F7B4_duel10(void) {
    Object *obj;
    SpaceData *from;
    SpaceData *to;

    obj = func_800D8010_name_81(0x33, 0);
    func_800D8944_name_81(obj);
    D_80114CE4_duel10 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    from = MBDMasuGet(D_80114A60_duel10);
    to = MBDMasuGet(D_80114A62_duel10);
    HuVecCopy3F(&obj->coords, &from->coords);
    func_800EB708_name_81(&from->coords, &to->coords, &obj->rot);
}

void func_8010F864_duel10(void) {
    HmfModel *mdl;
    s32 angle;

    angle = *(s32 *)HuPrcCurrentGet()->user_data;
    while (TRUE) {
        f32 rot = sindf(angle);

        angle += 45;
        rot *= D_80114CE8_duel10;
        sincosdf(rot, &HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010F9E0_duel10(Vec *pos) {
    Process *process;
    s32 *angle;

    D_80114CE8_duel10 = 10.0f;
    process = omAddPrcObj(func_8010F864_duel10, 0xA, 0, 0x40);
    D_80114A64_duel10 = process;
    angle = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = angle;
    if (pos->x <= D_80114CE4_duel10->coords.x) {
        *angle = 180;
    } else {
        *angle = 0;
    }
}

void func_8010FA80_duel10(void) {
    HmfModel *mdl;

    if (D_80114A64_duel10 != NULL) {
        while (D_80114CE8_duel10 >= 0.0f) {
            D_80114CE8_duel10 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80114A64_duel10);
        sincosdf(0.0f, &HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[1],
                 &HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[0]);
        HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[4] =
            -HmfModelData[D_80114CE4_duel10->omObj1->model[0]].mtx[1];
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[5] = mdl->mtx[0];
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[2] = mdl->mtx[3] = mdl->mtx[7] = mdl->mtx[6] = mdl->mtx[8] = mdl->mtx[9] = mdl->mtx[11] =
            mdl->mtx[12] = mdl->mtx[13] = mdl->mtx[14] = 0.0f;
        mdl = &HmfModelData[D_80114CE4_duel10->omObj1->model[0]];
        mdl->mtx[10] = mdl->mtx[15] = 1.0f;
    }
}

void func_8010FC2C_duel10(void) {
    f32 amp;
    f32 dy;
    s32 angle;

    func_8001C814_main(D_80114CE4_duel10->omObj1->model[0], 5, 0);
    angle = 0;
    func_8001C92C_main(D_80114CE4_duel10->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80114CE4_duel10);
    amp = 0.5f;
    do {
        dy = 1.0f - cosdf(angle) * amp;
        angle += 60;
        amp -= 0.013888888888888888;
        HuVecCopyXYZ(&D_80114CE4_duel10->scale, 1.0f, dy, 1.0f);
        HuPrcVSleep();
    } while (angle < 2160);
    HuVecCopyXYZ(&D_80114CE4_duel10->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010FD44_duel10(void) {
    omAddPrcObj(func_8010FC2C_duel10, 0xA, 0, 0);
}

void func_8010FD70_duel10(void) {
    func_8001C814_main(D_80114CE4_duel10->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_80114CE4_duel10->omObj1->model[0], 1.0f);
}

// board ec2: on the second call the guide gives message 0x2524.
void func_8010FDC0_duel10(void) {
    if (D_80114A68_duel10 == 1) {
        func_8010ECA0_duel10(D_80114CD0_duel10, 0x2524);
    }
    D_80114A68_duel10++;
}


INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010FE0C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80111D0C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80111DC4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80111E6C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80111FDC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801127A8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80112E74_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80113644_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801136B4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801136F0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80113840_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80113970_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80113AF4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80114140_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8011450C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801148D8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80114940_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114BD8_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114BF0_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114BFC_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C14_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C44_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C74_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C78_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C80_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114CA0_duel10);
