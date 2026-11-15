#include "common.h"
#include "ovl_81.h"
#include "game/board.h"
#include "input.h"

// duel n5: player and partner placement and movement on the board (party mode's 1006F0.c, plus partners)

typedef struct MBDRotWork {
    /* 0x00 */ Vec from;
    /* 0x0C */ Vec to;
    /* 0x18 */ Vec* out;
    /* 0x1C */ s32 frames;
    /* 0x20 */ s32 spin;
} MBDRotWork; // sizeof 0x24

typedef struct MBDMoveWork {
    /* 0x00 */ Vec from;
    /* 0x0C */ Vec to;
    /* 0x18 */ Vec* out;
    /* 0x1C */ s32 frames;
} MBDMoveWork; // sizeof 0x20

typedef struct MBDMoveSpeedWork {
    /* 0x00 */ Vec from;
    /* 0x0C */ Vec to;
    /* 0x18 */ Vec* out;
    /* 0x1C */ f32 speed;
} MBDMoveSpeedWork; // sizeof 0x20

// partner moves; allocated 0x10 bytes
typedef struct MBDPartnerSpeedWork {
    /* 0x00 */ f32 player;
    /* 0x04 */ f32 speed;
} MBDPartnerSpeedWork;

typedef struct MBDPartnerFrameWork {
    /* 0x00 */ s32 player;
    /* 0x04 */ s32 frames;
} MBDPartnerFrameWork;

extern s32 D_801011E0_name_81[];

SpaceData* MBDMasuGet(s16 spaceIdx);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
f32 func_800D76D0_name_81(Vec*);
f32 func_800D7CEC_name_81(Vec*, Vec*);
void func_800EED30_name_81(s32);
void func_800EF7C8_name_81(Object*, f32, f32);
void func_800EB680_name_81(s16 playerNo, s16 spaceIdx, Vec* out);
void func_800EC6F4_name_81(void);
void func_800EC99C_name_81(void);
void func_800ED31C_name_81(void);
void func_800ED520_name_81(void);
void func_800ED7EC_name_81(void);
void func_800EDA38_name_81(void);
void func_800EB708_name_81(Vec* arg0, Vec* arg1, Vec* arg2);
Process* func_800EBC60_name_81(Vec* arg0, Vec* arg1, Vec* arg2, s32 arg3);
Process* func_800EBF2C_name_81(Vec* arg0, Vec* arg1, Vec* arg2, s32 arg3);
Process* func_800EC36C_name_81(Vec* arg0, Vec* arg1, Vec* arg2, f32 arg3);
void func_800EC420_name_81(s16 playerNo, f32 speed);
void func_800EC548_name_81(s16 playerNo, Vec* cur, Vec* next, Vec* after, Vec* dir);
Process* func_800EC91C_name_81(s16 playerNo, f32 speed);
Process* func_800ECBB4_name_81(s16 playerNo, f32 speed);
Process* func_800ED4AC_name_81(s16 playerNo, s32 frames);
Process* func_800ED68C_name_81(s16 playerNo, f32 speed);
Process* func_800ED9C4_name_81(s16 playerNo, s32 frames);
Process* func_800EDBEC_name_81(s16 playerNo, f32 speed);

void func_800EB680_name_81(s16 playerNo, s16 spaceIdx, Vec* out) {
    SpaceData* space = MBDMasuGet(spaceIdx);

    out->x = space->coords.x;
    out->y = space->coords.y;
    out->z = space->coords.z;
}

void func_800EB6C4_name_81(s16 playerNo, s16 spaceIdx) {
    func_800EB680_name_81(playerNo, spaceIdx, &GwPlayer[playerNo].player_obj->coords);
}

void func_800EB708_name_81(Vec* arg0, Vec* arg1, Vec* arg2) {
    HuVecSubtract(arg2, arg1, arg0);
    func_800D7828_name_81(arg2);
}

void func_800EB740_name_81(s16 playerNo, Vec* arg1) {
    Object* playerObj = MBDGetPlayerStruct(playerNo)->player_obj;

    func_800EB708_name_81(&playerObj->coords, arg1, &playerObj->rot);
}

void func_800EB780_name_81(Object* arg0, s16 arg1) {
    func_800EB708_name_81(&arg0->coords, &MBDMasuGet(arg1)->coords, &arg0->rot);
}

void func_800EB7BC_name_81(Vec* out) {
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 1.0f;
}

void func_800EB7D8_name_81(s16 playerNo) {
    func_800EB7BC_name_81(&MBDGetPlayerStruct(playerNo)->player_obj->rot);
}

void func_800EB804_name_81(Object* obj) {
    Vec sp10;
    Vec sp20;

    HuVecSubtract(&sp10, &gCameraList->pos, &obj->coords);
    HuVecCopyXYZ(&sp20, sp10.x, 0.0f, sp10.z);
    obj->omObj1->rot.x = -func_800D7CEC_name_81(&sp10, &sp20);
    func_800EB708_name_81(&obj->coords, &gCameraList->pos, &sp10);
    obj->omObj1->rot.y = func_800D76D0_name_81(&sp10);
    obj->omObj1->rot.z = 0;
}

void func_800EB8B0_name_81(s16 playerNoOne, s16 playerNoTwo) {
    GW_PLAYER* playerOne = MBDGetPlayerStruct(playerNoOne);
    GW_PLAYER* playerTwo = MBDGetPlayerStruct(playerNoTwo);
    u8 prev_clink;
    u8 prev_cidx;
    u8 prev_nlink;
    u8 prev_nidx;
    u8 prev_blink;
    u8 prev_bidx;
    u8 prev_nnlink;
    u8 prev_nnidx;
    u8 prev_rev;

    prev_clink = playerOne->clink;
    playerOne->clink = playerTwo->clink;
    playerTwo->clink = prev_clink;
    prev_cidx = playerOne->cidx;
    playerOne->cidx = playerTwo->cidx;
    playerTwo->cidx = prev_cidx;
    prev_nlink = playerOne->nlink;
    playerOne->nlink = playerTwo->nlink;
    playerTwo->nlink = prev_nlink;
    prev_nidx = playerOne->nidx;
    playerOne->nidx = playerTwo->nidx;
    playerTwo->nidx = prev_nidx;
    prev_blink = playerOne->blink;
    playerOne->blink = playerTwo->blink;
    playerTwo->blink = prev_blink;
    prev_bidx = playerOne->bidx;
    playerOne->bidx = playerTwo->bidx;
    playerTwo->bidx = prev_bidx;
    prev_nnlink = playerOne->nnlink;
    playerOne->nnlink = playerTwo->nnlink;
    playerTwo->nnlink = prev_nnlink;
    prev_nnidx = playerOne->nnidx;
    playerOne->nnidx = playerTwo->nnidx;
    playerTwo->nnidx = prev_nnidx;
    prev_rev = playerOne->rev;
    prev_nnidx = playerTwo->rev; // the temp is reused here for the match
    playerOne->rev = prev_nnidx;
    playerTwo->rev = prev_rev;
}

s16 func_800EB984_name_81(void) {
    s32 starTotal = 0;
    s32 i;

    for (i = 0; i < 2; i++) {
        starTotal += MBDGetPlayerStruct(i)->star;
    }
    return starTotal;
}

s16 func_800EB9D4_name_81(s8 arg0) {
    u8 randByte = rand8();
    s32 chance = arg0;
    return (randByte * 99 >> 8) < chance;
}

s16 func_800EBA1C_name_81(void) {
    GW_SYSTEM* system = &GwSystem;

    return system->total_turns - system->current_turn + 1;
}

s32 func_800EBA50_name_81(s16 arg0, f32 arg1) {
    Vec sp10;
    s32 var_v0;

    sp10.x = D_800CBB6E_main[arg0];
    sp10.y = 0.0f;
    sp10.z = D_800D20A1_main[arg0];
    if (!(arg1 <= HuVecGetLength3F(&sp10))) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    return var_v0;
}

void func_800EBAD4_name_81(s32 arg0) {
    func_800EED30_name_81(D_801011E0_name_81[(s16)arg0]);
}

void func_800EBB00_name_81(void) {
    MBDRotWork* work = HuPrcCurrentGet()->user_data;
    s32 frames = work->frames;
    f32 angle = func_800D76D0_name_81(&work->from);
    f32 step = func_800D76D0_name_81(&work->to) - angle;
    f32 framesF;

    if (step < -180.0f) {
        step += 360.0f;
    }
    if (step > 180.0f) {
        step -= 360.0f;
    }
    framesF = (f32)frames;
    step = step / framesF;
    if (work->spin != 0) {
        if (step >= 0.0f) {
            step += 720.0f / framesF;
        } else {
            step -= 720.0f / framesF;
        }
    }
    for (angle = 0.0f; work->frames != 0;) {
        HuVecCopy3F(work->out, &work->from);
        angle += step;
        func_800D7934_name_81(work->out, angle);
        work->frames--;
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

Process* func_800EBC60_name_81(Vec* arg0, Vec* arg1, Vec* arg2, s32 arg3) {
    Process* proc = omAddPrcObj(func_800EBB00_name_81, 0x4002, 0, 0x80);
    MBDRotWork* work = HuMemMemoryAlloc(proc->heap, sizeof(MBDRotWork));

    proc->user_data = work;
    HuVecCopyXYZ(&work->from, arg0->x, 0.0f, arg0->z);
    HuVecCopyXYZ(&work->to, arg1->x, 0.0f, arg1->z);
    work->out = arg2;
    work->frames = arg3;
    work->spin = 0;
    return proc;
}

Process* func_800EBD1C_name_81(Vec* arg0, Vec* arg1, Vec* arg2, s32 arg3) {
    Process* proc = omAddPrcObj(func_800EBB00_name_81, 0x4002, 0, 0x80);
    MBDRotWork* work = HuMemMemoryAlloc(proc->heap, sizeof(MBDRotWork));

    proc->user_data = work;
    HuVecCopyXYZ(&work->from, arg0->x, 0.0f, arg0->z);
    HuVecCopyXYZ(&work->to, arg1->x, 0.0f, arg1->z);
    work->out = arg2;
    work->frames = arg3;
    work->spin = 1;
    return proc;
}

void func_800EBDDC_name_81(s16 playerNo, s32 arg1, s16 spaceIdx) {
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    Vec sp10;

    HuVecSubtract(&sp10, &MBDMasuGet(spaceIdx)->coords, &player->player_obj->coords);
    func_800D7828_name_81(&sp10);
    func_800EBC60_name_81(&player->player_obj->rot, &sp10, &player->player_obj->rot, arg1);
}

void func_800EBE60_name_81(void) {
    MBDMoveWork* work = HuPrcCurrentGet()->user_data;
    s32 frames = work->frames;

    while (work->frames) {
        HuVecSubtract(work->out, &work->to, &work->from);
        HuVecMulScalar(work->out, 1.0f - ((1.0f / (f32)frames) * (f32)(work->frames - 1)), work->out);
        HuVecAdd(work->out, work->out, &work->from);
        work->frames--;
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

Process* func_800EBF2C_name_81(Vec* arg0, Vec* arg1, Vec* arg2, s32 arg3) {
    Process* proc = omAddPrcObj(func_800EBE60_name_81, 0x4002, 0, 0x50);
    MBDMoveWork* work = HuMemMemoryAlloc(proc->heap, sizeof(MBDMoveWork));

    proc->user_data = work;
    work->from = *arg0;
    work->to = *arg1;
    work->out = arg2;
    work->frames = arg3;
    return proc;
}

// walk the player to the next space in a number of frames
void func_800EBFE0_name_81(s16 playerNo, s32 frames) {
    Vec sp10;
    Vec sp20;
    Vec sp30;
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    Process* proc;

    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &sp10);
    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &sp20);
    if (!(player->rev & 4)) {
        func_800EB708_name_81(&sp10, &sp20, &sp30);
    } else {
        func_800EB708_name_81(&sp20, &sp10, &sp30);
    }
    func_800EBC60_name_81(&player->player_obj->rot, &sp30, &player->player_obj->rot, frames);
    proc = func_800EBF2C_name_81(&sp10, &sp20, &player->player_obj->coords, frames);
    HuPrcChildLink(HuPrcCurrentGet(), proc);
    HuPrcChildWait();
}

void func_800EC114_name_81(void) {
}

void func_800EC11C_name_81(void) {
    MBDMoveSpeedWork* work = HuPrcCurrentGet()->user_data;
    f32 speed = work->speed;
    Vec* to = &work->to;

    while (!(HuVecDistance(&work->from, to) < speed)) {
        HuVecSubtract(work->out, to, &work->from);
        func_800D7828_name_81(work->out);
        HuVecMulScalar(work->out, speed, work->out);
        HuVecAdd(work->out, work->out, &work->from);
        HuVecCopy3F(&work->from, work->out);
        HuPrcVSleep();
    }
    HuVecCopy3F(work->out, &work->to);
    omDelPrcObj(NULL);
}

Process* func_800EC1E4_name_81(Vec* arg0, Vec* arg1, Vec* arg2, f32 arg3) {
    Process* proc = omAddPrcObj(func_800EC11C_name_81, 0x4002, 0, 0x50);
    MBDMoveSpeedWork* work = HuMemMemoryAlloc(proc->heap, sizeof(MBDMoveSpeedWork));

    proc->user_data = work;
    work->from = *arg0;
    work->to = *arg1;
    work->out = arg2;
    work->speed = arg3;
    return proc;
}

void func_800EC298_name_81(void) {
    s32 done = 0;
    MBDMoveSpeedWork* work = HuPrcCurrentGet()->user_data;
    f32 speed = work->speed;
    Vec* to = &work->to;

    while (1) {
        HuVecSubtract(work->out, to, &work->from);
        func_800D7828_name_81(work->out);
        HuVecMulScalar(work->out, speed, work->out);
        HuVecAdd(work->out, work->out, &work->from);
        HuVecCopy3F(&work->from, work->out);
        if (HuVecDistance(&work->from, to) < speed) {
            done = 1;
        }
        if (done != 0) {
            break;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

Process* func_800EC36C_name_81(Vec* arg0, Vec* arg1, Vec* arg2, f32 arg3) {
    Process* proc = omAddPrcObj(func_800EC298_name_81, 0x4002, 0, 0x50);
    MBDMoveSpeedWork* work = HuMemMemoryAlloc(proc->heap, sizeof(MBDMoveSpeedWork));

    proc->user_data = work;
    work->from = *arg0;
    work->to = *arg1;
    work->out = arg2;
    work->speed = arg3;
    return proc;
}

// walk the player to the next space at a speed
void func_800EC420_name_81(s16 playerNo, f32 speed) {
    Vec sp10;
    Vec sp20;
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    Process* proc;

    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &sp10);
    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &sp20);
    if (!(player->rev & 4)) {
        func_800EB708_name_81(&sp10, &sp20, &player->player_obj->rot);
    } else {
        func_800EB708_name_81(&sp20, &sp10, &player->player_obj->rot);
    }
    proc = func_800EC1E4_name_81(&sp10, &sp20, &player->player_obj->coords, speed);
    HuPrcChildLink(HuPrcCurrentGet(), proc);
    HuPrcChildWait();
}

// positions of the current, next and following spaces, and the facing direction
void func_800EC548_name_81(s16 playerNo, Vec* cur, Vec* next, Vec* after, Vec* dir) {
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    s16 spaceIdx;

    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->clink, player->cidx), cur);
    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), next);
    if (player->nnlink >= 0 && player->nnidx >= 0) {
        func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->nnlink, player->nnidx), after);
    } else {
        if (!(player->rev & 1)) {
            spaceIdx = MBDMasuLinkMasuIdGet(player->nlink, player->nidx + 1);
        } else {
            spaceIdx = MBDMasuLinkMasuIdGet(player->nlink, player->nidx - 1);
        }
        func_800EB680_name_81(playerNo, spaceIdx, after);
    }
    if (!(player->rev & 4)) {
        func_800EB708_name_81(cur, next, dir);
    } else {
        func_800EB708_name_81(next, cur, dir);
    }
}

#ifdef NON_MATCHING
// block layout of the two rev & 4 tests and s-register allocation
// the front partner follows the player to the next space
void func_800EC6F4_name_81(void) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    Vec sp58;
    Vec sp68;
    MBDPartnerSpeedWork* work = HuPrcCurrentGet()->user_data;
    s16 playerNo = work->player;
    f32 speed = work->speed;
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    Process* proc;
    Object* partner;
    f32 angle;
    Vec* dir;

    func_800EC548_name_81(playerNo, &sp18, &sp28, &sp38, &sp68);
    proc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerNo, PARTNER_FRONT);
    if (!(player->rev & 4)) {
        HuVecCopy3F(&sp48, &partner->coords);
        HuVecCopy3F(&sp58, &sp28);
        HuVecCopy3F(&partner->rot, &sp68);
    } else {
        func_800EB708_name_81(&player->player_obj->coords, &partner->coords, &partner->rot);
        HuVecCopy3F(&sp48, &partner->coords);
        HuVecCopy3F(&sp58, &sp18);
    }
    HuPrcChildLink(proc, func_800EC36C_name_81(&sp48, &sp58, &partner->coords, speed));
    HuPrcChildWait();
    dir = &sp68;
    if (player->rev & 4) {
    } else {
        func_800EB708_name_81(&sp28, &sp38, dir);
    }
    angle = func_800D76D0_name_81(dir) + 0.0f;
    sp58.x = sindf(angle) * 12.0f + sp28.x;
    sp58.z = cosdf(angle) * 12.0f + sp28.z;
    sp58.y = sp28.y;
    HuVecCopy3F(&sp48, &partner->coords);
    HuVecCopy3F(&partner->rot, &sp68);
    HuPrcChildLink(proc, func_800EC1E4_name_81(&sp48, &sp58, &partner->coords, speed));
    HuPrcChildWait();
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC6F4_name_81);
#endif

Process* func_800EC91C_name_81(s16 playerNo, f32 speed) {
    Process* proc = omAddPrcObj(func_800EC6F4_name_81, 0x4003, 0, 0x40);
    MBDPartnerSpeedWork* work = HuMemMemoryAlloc(proc->heap, 0x10);

    proc->user_data = work;
    work->player = playerNo;
    work->speed = speed;
    return proc;
}

#ifdef NON_MATCHING
// block layout of the two rev & 4 tests and s-register allocation
// the back partner follows the player to the next space
void func_800EC99C_name_81(void) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    Vec sp58;
    Vec sp68;
    MBDPartnerSpeedWork* work = HuPrcCurrentGet()->user_data;
    s16 playerNo = work->player;
    f32 speed = work->speed;
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    Process* proc;
    Object* partner;
    f32 angle;
    Vec* dir;

    func_800EC548_name_81(playerNo, &sp18, &sp28, &sp38, &sp68);
    proc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerNo, PARTNER_BACK);
    if (!(player->rev & 4)) {
        func_800EB708_name_81(&partner->coords, &player->player_obj->coords, &partner->rot);
        HuVecCopy3F(&sp48, &partner->coords);
        HuVecCopy3F(&sp58, &sp18);
    } else {
        HuVecCopy3F(&partner->rot, &sp68);
        HuVecCopy3F(&sp48, &partner->coords);
        HuVecCopy3F(&sp58, &sp28);
    }
    HuPrcChildLink(proc, func_800EC36C_name_81(&sp48, &sp58, &partner->coords, speed));
    HuPrcChildWait();
    dir = &sp68;
    if (!(player->rev & 4)) {
    } else {
        func_800EB708_name_81(&sp38, &sp28, dir);
    }
    angle = func_800D76D0_name_81(dir) + 180.0f;
    sp58.x = sindf(angle) * 12.0f + sp28.x;
    sp58.z = cosdf(angle) * 12.0f + sp28.z;
    sp58.y = sp28.y;
    HuVecCopy3F(&sp48, &partner->coords);
    HuVecCopy3F(&partner->rot, &sp68);
    HuPrcChildLink(proc, func_800EC1E4_name_81(&sp48, &sp58, &partner->coords, speed));
    HuPrcChildWait();
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC99C_name_81);
#endif

Process* func_800ECBB4_name_81(s16 playerNo, f32 speed) {
    Process* proc = omAddPrcObj(func_800EC99C_name_81, 0x4003, 0, 0x40);
    MBDPartnerSpeedWork* work = HuMemMemoryAlloc(proc->heap, 0x10);

    proc->user_data = work;
    work->player = playerNo;
    work->speed = speed;
    return proc;
}

// walk the player and partners to the next space
void func_800ECC34_name_81(s16 playerNo, f32 speed) {
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    Process* proc = HuPrcCurrentGet();

    if (player->stats.partners.frontID != PARTNER_NONE) {
        HuPrcChildLink(proc, func_800EC91C_name_81(playerNo, speed));
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        HuPrcChildLink(proc, func_800ECBB4_name_81(playerNo, speed));
    }
    func_800EC420_name_81(playerNo, speed);
    player->nnlink = -1;
    player->nnidx = -1;
}

void func_800ECD0C_name_81(s16 playerNo, s16 link, s16 idx) {
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);

    if (link > -1) {
        player->clink = link;
        player->nlink = link;
        player->blink = link;
    }
    if (idx > -1) {
        player->cidx = idx;
        player->nidx = idx + 1;
        player->bidx = idx - 1;
    }
}

void func_800ECD88_name_81(s16 playerNo, s16 link, s16 idx) {
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);

    if (link > -1) {
        player->nlink = link;
    }
    if (idx > -1) {
        player->nidx = idx;
    }
}

void func_800ECDE8_name_81(void) {
    MBDGetPlayerStruct(-1)->rev |= 1;
}

void func_800ECE10_name_81(void) {
    MBDGetPlayerStruct(-1)->rev &= ~1;
}

#ifdef NON_MATCHING
// the s16 playerNo conversion is scheduled after the first space id's
// face the next space
void func_800ECE38_name_81(s32 arg0) {
    Vec sp10;
    Vec sp20;
    GW_PLAYER* player = MBDGetPlayerStruct(arg0);
    s16 playerNo = arg0;

    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->clink, player->cidx), &sp10);
    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->nlink, player->nidx), &sp20);
    if (!(player->rev & 4)) {
        func_800EB708_name_81(&sp10, &sp20, &player->player_obj->rot);
    } else {
        func_800EB708_name_81(&sp20, &sp10, &player->player_obj->rot);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ECE38_name_81);
#endif

#ifdef NON_MATCHING
// f20/f22/f24 allocation (the 0.0f constant) and the shared tail call
// offsets of the front and back partners from the player
void func_800ECF1C_name_81(s32 playerNo, Vec* front, Vec* back) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    f32 angle;

    func_800EC548_name_81(playerNo, &sp18, &sp28, &sp38, &sp48);
    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &sp38);
    if (!(player->rev & 4)) {
        func_800EB708_name_81(&sp18, &sp28, &sp48);
        angle = func_800D76D0_name_81(&sp48) + 0.0f;
        front->x = sindf(angle) * 12.0f;
        front->z = cosdf(angle) * 12.0f;
        front->y = 0.0f;
        func_800EB708_name_81(&sp38, &sp18, &sp48);
    } else {
        func_800EB708_name_81(&sp18, &sp38, &sp48);
        angle = func_800D76D0_name_81(&sp48) + 0.0f;
        front->x = sindf(angle) * 12.0f;
        front->z = cosdf(angle) * 12.0f;
        front->y = 0.0f;
        func_800EB708_name_81(&sp28, &sp18, &sp48);
    }
    angle = func_800D76D0_name_81(&sp48) + 180.0f;
    back->x = sindf(angle) * 12.0f;
    back->z = cosdf(angle) * 12.0f;
    back->y = 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ECF1C_name_81);
#endif

// directions of the front and back partners
void func_800ED118_name_81(s32 playerNo, Vec* front, Vec* back) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);

    func_800EC548_name_81(playerNo, &sp18, &sp28, &sp38, &sp48);
    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &sp38);
    if (!(player->rev & 4)) {
        func_800EB708_name_81(&sp18, &sp28, front);
        func_800EB708_name_81(&sp38, &sp18, back);
    } else {
        func_800EB708_name_81(&sp18, &sp38, front);
        func_800EB708_name_81(&sp28, &sp18, back);
    }
}

void func_800ED214_name_81(s32 playerIndex) {
    Vec sp10;
    Vec sp20;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Object *partner;

    func_800ECF1C_name_81(playerIndex, &sp10, &sp20);
    if (player->stats.partners.frontID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
        HuVecCopy3F(&partner->coords, &player->player_obj->coords);
        HuVecAdd(&partner->coords, &partner->coords, &sp10);
        func_800D7828_name_81(&sp10);
        HuVecCopy3F(&partner->rot, &sp10);
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
        HuVecCopy3F(&partner->coords, &player->player_obj->coords);
        HuVecAdd(&partner->coords, &partner->coords, &sp20);
        func_800D7828_name_81(&sp20);
        func_800D7934_name_81(&sp20, 180.0f);
        HuVecCopy3F(&partner->rot, &sp20);
    }
}

#ifdef NON_MATCHING
// one assembler nop after cosdf
// the front partner hops to its place in front of the player
void func_800ED31C_name_81(void) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    Vec sp58;
    Vec sp68;
    MBDPartnerFrameWork* work = HuPrcCurrentGet()->user_data;
    s32 frames = work->frames;
    s16 playerNo = work->player;
    Process* proc;
    Object* partner;
    f32 angle;

    func_800EC548_name_81(playerNo, &sp18, &sp28, &sp38, &sp68);
    proc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerNo, PARTNER_FRONT);
    func_800EB708_name_81(&sp18, &sp28, &sp68);
    angle = func_800D76D0_name_81(&sp68) + 0.0f;
    sp58.x = sindf(angle) * 12.0f + sp18.x;
    sp58.z = cosdf(angle) * 12.0f + sp18.z;
    sp58.y = sp18.y;
    HuVecCopy3F(&sp48, &partner->coords);
    HuVecCopy3F(&partner->rot, &sp68);
    HuPrcChildLink(proc, func_800EBF2C_name_81(&sp48, &sp58, &partner->coords, frames));
    func_800EF7C8_name_81(partner, 5.0f, -5.0f / (f32)(frames / 2));
    HuPrcChildWait();
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ED31C_name_81);
#endif

Process* func_800ED4AC_name_81(s16 playerNo, s32 frames) {
    Process* proc = omAddPrcObj(func_800ED31C_name_81, 0x4003, 0, 0x40);
    MBDPartnerFrameWork* work = HuMemMemoryAlloc(proc->heap, 0x10);

    proc->user_data = work;
    work->player = playerNo;
    work->frames = frames;
    return proc;
}

#ifdef NON_MATCHING
// one assembler nop after cosdf
// the front partner walks to its place in front of the player
void func_800ED520_name_81(void) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    Vec sp58;
    Vec sp68;
    MBDPartnerSpeedWork* work = HuPrcCurrentGet()->user_data;
    s16 playerNo = work->player;
    f32 speed = work->speed;
    Process* proc;
    Object* partner;
    f32 angle;

    func_800EC548_name_81(playerNo, &sp18, &sp28, &sp38, &sp68);
    proc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerNo, PARTNER_FRONT);
    func_800EB708_name_81(&sp18, &sp28, &sp68);
    angle = func_800D76D0_name_81(&sp68) + 0.0f;
    sp58.x = sindf(angle) * 12.0f + sp18.x;
    sp58.z = cosdf(angle) * 12.0f + sp18.z;
    sp58.y = sp18.y;
    HuVecCopy3F(&sp48, &partner->coords);
    HuVecCopy3F(&partner->rot, &sp68);
    HuPrcChildLink(proc, func_800EC1E4_name_81(&sp48, &sp58, &partner->coords, speed));
    HuPrcChildWait();
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ED520_name_81);
#endif

Process* func_800ED68C_name_81(s16 playerNo, f32 speed) {
    Process* proc = omAddPrcObj(func_800ED520_name_81, 0x4003, 0, 0x40);
    MBDPartnerSpeedWork* work = HuMemMemoryAlloc(proc->heap, 0x10);

    proc->user_data = work;
    work->player = playerNo;
    work->speed = speed;
    return proc;
}

Process* func_800ED70C_name_81(s32 playerNo, s32 hop) {
    Process* proc = NULL;

    if (MBDGetPlayerStruct(playerNo)->stats.partners.frontID != PARTNER_NONE) {
        if (hop != 0) {
            proc = func_800ED4AC_name_81(playerNo, 15);
        } else {
            proc = func_800ED68C_name_81(playerNo, 3.0f);
        }
    }
    return proc;
}

void func_800ED788_name_81(s32 playerNo) {
    Process* proc;

    if (GwSystem.current_board_index == 3) {
        proc = func_800ED70C_name_81(playerNo, 1);
    } else {
        proc = func_800ED70C_name_81(playerNo, 0);
    }
    if (proc != NULL) {
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        HuPrcChildWait();
    }
}

#ifdef NON_MATCHING
// one assembler nop after cosdf
// the back partner hops to its place behind the player
void func_800ED7EC_name_81(void) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    Vec sp58;
    Vec sp68;
    MBDPartnerFrameWork* work = HuPrcCurrentGet()->user_data;
    s32 frames = work->frames;
    s16 playerNo = work->player;
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    Process* proc;
    Object* partner;
    f32 angle;

    func_800EC548_name_81(playerNo, &sp18, &sp28, &sp38, &sp68);
    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &sp38);
    proc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerNo, PARTNER_BACK);
    func_800EB708_name_81(&sp38, &sp18, &sp68);
    angle = func_800D76D0_name_81(&sp68) + 180.0f;
    sp58.x = sindf(angle) * 12.0f + sp18.x;
    sp58.z = cosdf(angle) * 12.0f + sp18.z;
    sp58.y = sp18.y;
    HuVecCopy3F(&sp48, &partner->coords);
    HuVecCopy3F(&partner->rot, &sp68);
    HuPrcChildLink(proc, func_800EBF2C_name_81(&sp48, &sp58, &partner->coords, frames));
    func_800EF7C8_name_81(partner, 5.0f, -5.0f / (f32)(frames / 2));
    HuPrcChildWait();
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ED7EC_name_81);
#endif

Process* func_800ED9C4_name_81(s16 playerNo, s32 frames) {
    Process* proc = omAddPrcObj(func_800ED7EC_name_81, 0x4003, 0, 0x40);
    MBDPartnerFrameWork* work = HuMemMemoryAlloc(proc->heap, 0x10);

    proc->user_data = work;
    work->player = playerNo;
    work->frames = frames;
    return proc;
}

#ifdef NON_MATCHING
// one assembler nop after cosdf
// the back partner walks to its place behind the player
void func_800EDA38_name_81(void) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    Vec sp58;
    Vec sp68;
    MBDPartnerSpeedWork* work = HuPrcCurrentGet()->user_data;
    s16 playerNo = work->player;
    f32 speed = work->speed;
    GW_PLAYER* player = MBDGetPlayerStruct(playerNo);
    Process* proc;
    Object* partner;
    f32 angle;

    func_800EC548_name_81(playerNo, &sp18, &sp28, &sp38, &sp68);
    func_800EB680_name_81(playerNo, MBDMasuLinkMasuIdGet(player->blink, player->bidx), &sp38);
    proc = HuPrcCurrentGet();
    partner = MBDGetPlayerPartnerRef(playerNo, PARTNER_BACK);
    func_800EB708_name_81(&sp38, &sp18, &sp68);
    angle = func_800D76D0_name_81(&sp68) + 180.0f;
    sp58.x = sindf(angle) * 12.0f + sp18.x;
    sp58.z = cosdf(angle) * 12.0f + sp18.z;
    sp58.y = sp18.y;
    HuVecCopy3F(&sp48, &partner->coords);
    HuVecCopy3F(&partner->rot, &sp68);
    HuPrcChildLink(proc, func_800EC1E4_name_81(&sp48, &sp58, &partner->coords, speed));
    HuPrcChildWait();
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EDA38_name_81);
#endif

Process* func_800EDBEC_name_81(s16 playerNo, f32 speed) {
    Process* proc = omAddPrcObj(func_800EDA38_name_81, 0x4003, 0, 0x40);
    MBDPartnerSpeedWork* work = HuMemMemoryAlloc(proc->heap, 0x10);

    proc->user_data = work;
    work->player = playerNo;
    work->speed = speed;
    return proc;
}

Process* func_800EDC6C_name_81(s32 playerNo, s32 hop) {
    Process* proc = NULL;

    if (MBDGetPlayerStruct(playerNo)->stats.partners.backID != PARTNER_NONE) {
        if (hop != 0) {
            proc = func_800ED9C4_name_81(playerNo, 15);
        } else {
            proc = func_800EDBEC_name_81(playerNo, 3.0f);
        }
    }
    return proc;
}

void func_800EDCE8_name_81(s32 playerNo) {
    Process* proc;

    if (GwSystem.current_board_index == 3) {
        proc = func_800EDC6C_name_81(playerNo, 1);
    } else {
        proc = func_800EDC6C_name_81(playerNo, 0);
    }
    if (proc != NULL) {
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        HuPrcChildWait();
    }
}
