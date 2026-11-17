#include "common.h"

typedef struct UnkPuddlePaddle {
    /* 0x00 */ char pad00[8];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ char pad09[1];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} UnkPuddlePaddle; // size >= 0x10

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801059A0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801059BC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105B94_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105C3C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105C84_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105CBC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105CE0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105DBC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106028_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106064_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106958_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106988_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801069FC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106B6C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106CE4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801073AC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801073E4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107588_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801075B8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107638_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010788C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801079D4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107B2C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107DB0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107E1C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108178_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108368_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801087DC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108D10_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108E2C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010910C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801091F8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801094C4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109718_puddle_paddle);

#include "gcc/memory.h"
#include "mallocblock.h"
#include "math.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/util.h"


// m1 pp2: object system shared with ovl_0C baby_bowser_broadside 169540 and ovl_39 tick_tock_hop system.c (m257_*):
// Puddle Paddle pools: 20 sprites, 8 function groups, 16 animated models (0x28 each), 16 billboards.
#define PP_FUNC_GRP_MAX 8
#define PP_SPRITES_MAX 20
#define PP_ANIMMDL_MAX 16
#define PP_BILLS_MAX 16

typedef struct {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 a;
} PpRGBA;

typedef struct {
    /* 0x00 */ s8 s8[16];
    /* 0x10 */ s16 s16[8];
    /* 0x20 */ f32 f32[4];
} PpWork; // Size 0x30

typedef struct {
    /* 0x00 */ omObjData *object;
    /* 0x04 */ s16 *modelIds;
    /* 0x08 */ s16 maxModels;
} PpFuncGroupContext; // Size 0xC

typedef struct pp_func_context {
    /* 0x00 */ s8 set;
    /* 0x02 */ s16 id;
    /* 0x04 */ s8 state;
    /* 0x05 */ s8 tag;
    /* 0x08 */ s32 prio;
    /* 0x0C */ PpWork work;
    /* 0x3C */ void *data;
    /* 0x40 */ void (*func)(PpFuncGroupContext *, struct pp_func_context *);
} PpFuncContext; // Size 0x44

typedef struct {
    /* 0x00 */ u32 prio;
    /* 0x04 */ s16 next;
    /* 0x06 */ s16 prev;
    /* 0x08 */ s16 id;
} PpFuncOrder; // Size 0xC

typedef struct {
    /* 0x00 */ PpFuncGroupContext *groupCtx;
    /* 0x04 */ PpFuncContext *funcCtx;
    /* 0x08 */ s16 maxFuncs;
    /* 0x0C */ PpFuncOrder *order;
    /* 0x10 */ s8 sort;
} PpFuncGroup; // Size 0x14

typedef struct {
    /* 0x00 */ s8 state; // 0 unused, 1 hidden, 2 shown
    /* 0x01 */ u8 groupId;
    /* 0x02 */ u8 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ s16 unk06;
} PpSpriteData; // Size 8

typedef struct {
    /* 0x00 */ s8 set;
    /* 0x04 */ s32 attr;
    /* 0x08 */ s8 state; // -1 hidden, 0 waiting, 1 animating
    /* 0x0A */ s16 tag;
    /* 0x0C */ s16 modelId;
    /* 0x10 */ f32 freq;
    /* 0x14 */ f32 animTimer;
    /* 0x18 */ f32 animStart;
    /* 0x1C */ f32 rotX; // applied by func_8010C664 each frame
    /* 0x20 */ f32 rotY;
    /* 0x24 */ f32 rotZ;
} PpAnimModelData; // Size 0x28

typedef struct {
    /* 0x00 */ s8 set;
    /* 0x04 */ s32 attr; // 1 animated sprite model, 2 animate, 4 loop, 8 hidden, 0x10 position by reference
    /* 0x08 */ s16 tag;
    /* 0x0A */ u8 spriteId;
    /* 0x0C */ s16 modelId;
    /* 0x0E */ s16 duration;
    /* 0x10 */ s16 timer;
    /* 0x12 */ s16 frameTimer; // frames on the current animation frame
    /* 0x14 */ s16 frameDelay; // frames per animation frame - 1
    /* 0x18 */ f32 *posX;
    /* 0x1C */ f32 *posY;
    /* 0x20 */ f32 *posZ;
} PpBillboardData; // Size 0x24

void func_80017D24_main(f32 *, f32, f32, f32);

extern Gfx D_80111330_puddle_paddle[];
extern PpAnimModelData *D_80111660_puddle_paddle;
extern PpSpriteData *D_80111664_puddle_paddle;
extern PpBillboardData *D_80111668_puddle_paddle;
extern PpFuncGroup *D_8011166C_puddle_paddle;

void func_8010BD18_puddle_paddle(PpFuncGroup *group);
void func_8010C11C_puddle_paddle(s16 spriteId);
s16 func_8010CE74_puddle_paddle(HuSprite_Unk84_Struct *arg0, f32 arg1);
s16 func_8010D5E4_puddle_paddle(HuSprite_Unk84_Struct *arg0, f32 arg1);
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z); // guRotateRPYF
void func_8010EDE8_puddle_paddle(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2);

// m1 pp2: Puddle Paddle game types (pp1's PpTeam/PpPlayer/PpCoin/PpState, with the fields pp2's functions use)
#include "game/gamework_data.h"
#include "overlays/minigame.h"
#include "game/audio.h"

/* A team (D_80111650_puddle_paddle[2]) */
typedef struct PpTeam {
    /* 0x00 */ f32 velX; /* drift, decays by dragX each frame */
    /* 0x04 */ char unk04[4];
    /* 0x08 */ f32 velZ;
    /* 0x0C */ f32 dragX;
    /* 0x10 */ char unk10[4];
    /* 0x14 */ f32 dragZ;
    /* 0x18 */ f32 unk18; /* raft heading, degrees */
    /* 0x1C */ f32 speed; /* sum of the members' paddle power */
    /* 0x20 */ u8 count;
    /* 0x22 */ s16 member[2]; /* player indices */
    /* 0x26 */ s16 digit[2]; /* score digit sprites */
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ s16 leader; /* the member who steers: a human, or the stronger CPU when both are CPUs */
    /* 0x2E */ char unk2E[0x22];
    /* 0x50 */ f32 baseX; /* raft position the stun shake is around */
    /* 0x54 */ f32 baseZ;
    /* 0x58 */ char unk58[8];
    /* 0x60 */ s16 reactTimer; /* CPU partner: frames since it last copied the leader */
    /* 0x62 */ s16 reactDelay;
} PpTeam; /* size 0x64 */

/* A player (D_80111654_puddle_paddle[4]) */
typedef struct PpPlayer {
    /* 0x00 */ s16 no;
    /* 0x02 */ s16 chr;
    /* 0x04 */ s32 unk04; /* 2 turn left, 4 turn right (CPU steering), 0x10 */
    /* 0x08 */ s8 pending; /* motion change requested */
    /* 0x0A */ s16 motion;
    /* 0x0C */ s16 nextMotion;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s8 slot; /* place in the team; also the blink phase while stunned (func_8010A224) */
    /* 0x11 */ s8 stunTimer;
    /* 0x12 */ char unk12[0x36];
    /* 0x48 */ f32 unk48; /* seat angle on the raft */
    /* 0x4C */ f32 power; /* paddle power this frame */
    /* 0x50 */ s16 team;
    /* 0x52 */ s16 cpuReactChance; /* CPU: 1 in (n + 1) frames re-rolls the reaction delay */
    /* 0x54 */ s16 cpuReactMax; /* CPU: reaction delay 5..n */
    /* 0x56 */ s16 unk56;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ char unk5A[2];
} PpPlayer; /* size 0x5C */

/* A coin (PpState::coins[16]) */
typedef struct PpCoin {
    /* 0x00 */ s16 kind;
    /* 0x02 */ s16 model;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0x1B];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x10];
} PpCoin; /* size 0x34 */

/* The game state (D_80111658_puddle_paddle) */
typedef struct PpState {
    /* 0x00 */ s32 flags;
    /* 0x04 */ char unk04[0x34];
    /* 0x38 */ PpCoin *coins;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ char unk3E[6];
} PpState; /* size 0x44 */

extern PpTeam *D_80111650_puddle_paddle;
extern PpPlayer *D_80111654_puddle_paddle;
extern PpState *D_80111658_puddle_paddle;

void func_801091F8_puddle_paddle(PpFuncGroupContext *groupCtx, PpFuncContext *ctx);
void func_8010981C_puddle_paddle(PpFuncGroupContext *groupCtx, PpFuncContext *ctx);
s16 func_8010BA04_puddle_paddle(s8 groupId, s32 prio, void *data, void (*func)(PpFuncGroupContext *, PpFuncContext *), s8 tag);
void func_80110BBC_puddle_paddle(f32 *a, f32 *b);
s16 func_8010C42C_puddle_paddle(s16 tag);
s32 func_8010C4D0_puddle_paddle(s16 animModelId, f32 posX, f32 posY, f32 posZ, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 animStart);

void func_80109804_puddle_paddle(PpPlayer *player, s16 motion, s8 pending) {
    player->pending = pending;
    player->nextMotion = motion;
    player->motion = motion;
}
s16 func_8010EFEC_puddle_paddle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);


void func_80109814_puddle_paddle(UnkPuddlePaddle *arg0, s16 arg1) {
    arg0->unk_0E = arg1;
}

// NON_MATCHING: masked 28; retail keeps best in a stack slot (frame 0x78, s0-s4), ours gives it s5; logic checked against the asm
#ifdef NON_MATCHING
void func_8010981C_puddle_paddle(PpFuncGroupContext *groupCtx, PpFuncContext *ctx) {
    HmfModel *model[2]; /* the raft, a coin */
    Vec raftPos;
    Vec coinPos;
    Vec d;
    s16 best;
    PpCoin *coin;
    PpPlayer *player;
    f32 bestDist;
    f32 dist;
    f32 angle;
    s16 i;
    PpTeam *team = ctx->data;

    coin = D_80111658_puddle_paddle->coins;
    player = &D_80111654_puddle_paddle[team->leader];
    player->unk04 &= ~(2 | 4);
    if (!(player->unk04 & 0x10) && (D_80111658_puddle_paddle->flags & 2)) {
        model[0] = &HmfModelData[groupCtx->modelIds[ctx->tag]];
        raftPos.x = model[0]->pos.x;
        raftPos.y = model[0]->pos.y;
        raftPos.z = model[0]->pos.z;
        bestDist = 9999.0f;
        best = -1;
        for (i = 0; i < 16; i++, coin++) {
            if (coin->unk04 == 3 && coin->kind != 2) {
                model[1] = &HmfModelData[coin->model];
                coinPos.x = model[1]->pos.x;
                coinPos.y = model[1]->pos.y;
                coinPos.z = model[1]->pos.z;
                d.x = coinPos.x - raftPos.x;
                d.y = coinPos.y - raftPos.y;
                d.z = coinPos.z - raftPos.z;
                dist = d.x * d.x + d.z * d.z;
                if (dist != 0.0f) {
                    dist = HuSqrtf(dist);
                } else {
                    dist = 0.0f;
                }
                if (dist < bestDist) {
                    bestDist = dist;
                    best = i;
                }
            }
        }
        if (best != -1) {
            model[1] = &HmfModelData[D_80111658_puddle_paddle->coins[best].model];
            coinPos.x = model[1]->pos.x;
            coinPos.y = model[1]->pos.y;
            coinPos.z = model[1]->pos.z;
            d.x = coinPos.x - raftPos.x;
            d.z = coinPos.z - raftPos.z;
            angle = atan2df(-d.z, d.x) + 90.0f;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            d.x = model[0]->rot.y;
            d.y = angle;
            func_80110BBC_puddle_paddle(&d.x, &d.y);
            if (!(((d.x - d.y) > 0.0f ? (d.x - d.y) : -(d.x - d.y)) < 6.0f)) {
                if (d.x - d.y > 0.0f) {
                    player->unk04 |= 2;
                } else if (d.x - d.y < 0.0f) {
                    player->unk04 |= 4;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010981C_puddle_paddle);
#endif

// NON_MATCHING: masked 36 (count 434 vs 431): splash flag tests and the 2x offset differ in register use and scheduling; logic checked against the asm
#ifdef NON_MATCHING
void func_80109BD4_puddle_paddle(PpFuncGroupContext *groupCtx, PpFuncContext *ctx) {
    PpTeam *team;
    HmfModel *raft;
    HmfModel *playerModel;
    HmfModel *other;
    PpPlayer *player;
    func_800E1BA8_minigame_ObjData *objData;
    Vec d;
    f32 x;
    f32 z;
    s16 angle;
    s16 animModelId;
    s32 splashL;
    s32 splashR;
    s16 i;
    s16 j;

    team = D_80111650_puddle_paddle;
    for (i = 0; i < 2; i++, team++) {
        raft = &HmfModelData[groupCtx->modelIds[i]];
        for (j = 0; j < 2; j++) {
            player = &D_80111654_puddle_paddle[team->member[j]];
            playerModel = &HmfModelData[*D_800EC598_minigame[team->member[j]]->model];
            angle = player->unk48 + team->unk18;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            x = sindf(angle) * 20.0f * 5.0f * 0.7f + raft->pos.x;
            z = cosdf(angle) * 20.0f * 5.0f * 0.7f + raft->pos.z;
            Hu3DModelPosSet(*D_800EC598_minigame[team->member[j]]->model, x, raft->pos.y + 37.0f, z);
            Hu3DModelRotSet(*D_800EC598_minigame[team->member[j]]->model, 0.0f, raft->rot.y, 0.0f);
            Hu3DModelPosSet(D_800EC598_minigame[team->member[j]]->model[1], x, raft->pos.y + 34.0f, z);
            if (player->unk04 & 8) {
                if (player->unk04 & 2) {
                    func_80109804_puddle_paddle(player, 0x27, 0);
                } else if (player->unk04 & 4) {
                    func_80109804_puddle_paddle(player, 0x28, 0);
                } else {
                    func_80109804_puddle_paddle(player, 0x26, 0);
                }
            } else if (player->unk04 & 2) {
                func_80109804_puddle_paddle(player, 0x27, 0);
            } else if (player->unk04 & 4) {
                func_80109804_puddle_paddle(player, 0x28, 0);
            } else {
                func_80109804_puddle_paddle(player, 0, 0);
            }
            objData = D_800EC598_minigame[team->member[j]]->data;
            splashL = FALSE;
            splashR = FALSE;
            if (playerModel->unk40 == 20.0f) {
                if (objData->unkD8.motion == 0x26) {
                    splashL = TRUE;
                    splashR = TRUE;
                } else if (objData->unkD8.motion == 0x27) {
                    splashL = TRUE;
                } else if (objData->unkD8.motion == 0x28) {
                    splashR = TRUE;
                }
            }
            if (i == 0) {
                other = &HmfModelData[groupCtx->modelIds[1]];
            } else {
                other = &HmfModelData[groupCtx->modelIds[0]];
            }
            if (splashL) {
                animModelId = func_8010C42C_puddle_paddle(0);
                if (animModelId != -1) {
                    x = 2.0f * (sindf(team->unk18 + 70.0f) * 20.0f * 5.0f) + playerModel->pos.x;
                    z = 2.0f * (cosdf(team->unk18 + 70.0f) * 20.0f * 5.0f) + playerModel->pos.z;
                    d.x = x - other->pos.x;
                    d.z = z - other->pos.z;
                    d.y = HuSqrtf(d.x * d.x + d.z * d.z);
                    if (d.y > 200.0f) {
                        func_8010C4D0_puddle_paddle(animModelId, x, playerModel->pos.y, z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
                    }
                }
            }
            if (splashR) {
                animModelId = func_8010C42C_puddle_paddle(0);
                if (animModelId != -1) {
                    x = 2.0f * (sindf(team->unk18 + 290.0f) * 20.0f * 5.0f) + playerModel->pos.x;
                    z = 2.0f * (cosdf(team->unk18 + 290.0f) * 20.0f * 5.0f) + playerModel->pos.z;
                    d.x = x - other->pos.x;
                    d.z = z - other->pos.z;
                    d.y = HuSqrtf(d.x * d.x + d.z * d.z);
                    if (d.y > 200.0f) {
                        func_8010C4D0_puddle_paddle(animModelId, x, playerModel->pos.y, z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
                    }
                }
            }
            if (splashL | splashR) {
                func_8004AC5C_main(0x379, team->member[j]);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109BD4_puddle_paddle);
#endif

void func_8010A224_puddle_paddle(PpFuncGroupContext *groupCtx, PpFuncContext *ctx) {
    PpTeam *team;
    PpPlayer *player;
    omObjData *obj;
    s16 i;
    s16 j;

    team = D_80111650_puddle_paddle;
    for (i = 0; i < 2; i++, team++) {
        for (j = 0; j < 2; j++) {
            player = &D_80111654_puddle_paddle[team->member[j]];
            obj = D_800EC598_minigame[team->member[j]];
            if (player->unk04 & 0x10) {
                if (++player->slot < 3) {
                    func_8001C258_main(*obj->model, 4, 0);
                } else {
                    player->slot = 0;
                    func_8001C258_main(*obj->model, 4, 4);
                }
                if (++player->stunTimer >= 21) {
                    func_8001C258_main(*obj->model, 4, 0);
                    player->unk04 &= ~0x10;
                    player->stunTimer = 0;
                    player->slot = 0;
                }
            }
        }
    }
}

// NON_MATCHING: masked 24 (542 vs 543): the drift-decay blocks keep the drag in another register (a copy for the compare) and the stun shake allocates differently; logic checked against the asm
#ifdef NON_MATCHING
void func_8010A398_puddle_paddle(PpFuncGroupContext *groupCtx, PpFuncContext *ctx) {
    PpTeam *team;
    PpPlayer *player;
    HmfModel *raft;
    f32 dx;
    f32 dz;
    f32 bob;
    s16 i;
    s16 j;

    team = D_80111650_puddle_paddle;
    for (i = 0; i < 2; i++, team++) {
        raft = &HmfModelData[groupCtx->modelIds[i]];
        team->speed = 0.0f;
        for (j = 0; j < 2; j++) {
            player = &D_80111654_puddle_paddle[team->member[j]];
            if ((GwPlayer[team->member[j]].stat & 1) && team->member[j] != team->leader) {
                if (rand16() % (player->cpuReactChance + 1) == 0 && (GwPlayer[team->leader].stat & 1)) {
                    team->reactTimer = 0;
                    team->reactDelay = rand16() % (player->cpuReactMax - 4) + 5;
                }
                player->unk04 &= ~(2 | 4);
                if (++team->reactTimer > team->reactDelay) {
                    team->reactTimer = team->reactDelay;
                    if (D_80111654_puddle_paddle[team->leader].unk04 & 4) {
                        player->unk04 |= 4;
                    }
                    if (D_80111654_puddle_paddle[team->leader].unk04 & 2) {
                        player->unk04 |= 2;
                    }
                } else {
                    if (D_80111654_puddle_paddle[team->leader].unk04 & 4) {
                        player->unk04 |= 2;
                    }
                    if (D_80111654_puddle_paddle[team->leader].unk04 & 2) {
                        player->unk04 |= 4;
                    }
                }
            }
            if (player->unk04 & 2) {
                team->unk18 -= 2.0f;
            } else if (player->unk04 & 4) {
                team->unk18 += 2.0f;
            }
            if (!(player->power < 0.1f)) {
                team->speed += player->power;
            }
        }
        if (team->unk18 < 0.0f) {
            team->unk18 += 360.0f;
        }
        if (team->unk18 >= 360.0f) {
            team->unk18 -= 360.0f;
        }
        raft->rot.y = team->unk18;
        dx = team->dragX;
        if ((team->velX > 0.0f ? team->velX : -team->velX) > dx) {
            if (team->velX > 0.0f) {
                team->velX -= dx;
            } else {
                team->velX += dx;
            }
        } else {
            team->velX = 0.0f;
        }
        dz = team->dragZ;
        if ((team->velZ > 0.0f ? team->velZ : -team->velZ) > dz) {
            if (team->velZ > 0.0f) {
                team->velZ -= dz;
            } else {
                team->velZ += dz;
            }
        } else {
            team->velZ = 0.0f;
        }
        bob = ctx->work.s16[0] / 120.0f;
        if (bob > 1.0f) {
            bob = 1.0f;
        }
        if (++ctx->work.s16[0] >= 121) {
            ctx->work.s16[0] = 0;
        }
        /* retail reads the stun flag of the team's last member (the inner loop's pointer) */
        if (player->unk04 & 0x10) {
            dx = (rand16() % 7 - 3) * 0.2f * 100.0f * 0.2f;
            dz = (rand16() % 7 - 3) * 0.2f * 100.0f * 0.2f;
            raft->pos.x = dx + team->baseX;
            raft->pos.z = dz + team->baseZ;
        } else {
            dx = sindf(team->unk18) * 20.0f * 5.0f * team->speed * 0.08f;
            dz = cosdf(team->unk18) * 20.0f * 5.0f * team->speed * 0.08f;
            raft->pos.x += dx;
            raft->pos.z += dz;
        }
        raft->pos.y = sindf(bob * 180.0f) * 20.0f * 5.0f * 0.1f + 170.0f;
        if ((dx != 0.0f) & (dz != 0.0f)) {
            team->velX += dx * 0.005f;
            team->velZ += dz * 0.005f;
            team->dragX = dx * 0.001f;
            team->dragZ = dz * 0.001f;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010A398_puddle_paddle);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010ABCC_puddle_paddle);

void func_8010B574_puddle_paddle(void) {
    PpTeam *team;
    s16 cpu[2];
    s16 diff[2];
    s16 i;
    s16 j;
    u16 player;

    team = D_80111650_puddle_paddle;
    for (i = 0; i < 2; i++, team++) {
        cpu[0] = GwPlayer[D_80111650_puddle_paddle[i].member[0]].stat & 1;
        cpu[1] = GwPlayer[D_80111650_puddle_paddle[i].member[1]].stat & 1;
        if (cpu[0] && cpu[1]) {
            diff[0] = GwPlayer[team->member[0]].cpu_difficulty;
            diff[1] = GwPlayer[team->member[1]].cpu_difficulty;
            if (diff[0] > diff[1]) {
                team->leader = team->member[0];
            } else {
                team->leader = team->member[1];
            }
            for (j = 0; j < 2; j++) {
                player = team->member[j];
                func_8010BA04_puddle_paddle(player + 3, 0, &D_80111654_puddle_paddle[(s16)player], func_801091F8_puddle_paddle, 0);
            }
            func_8010BA04_puddle_paddle(7, 0, &D_80111650_puddle_paddle[i], func_8010981C_puddle_paddle, i);
        } else if (cpu[0] || cpu[1]) {
            if (cpu[0]) {
                team->leader = team->member[1];
            } else {
                team->leader = team->member[0];
            }
            for (j = 0; j < 2; j++) {
                player = team->member[j];
                if (team->member[j] != team->leader) {
                    func_8010BA04_puddle_paddle(player + 3, 0, &D_80111654_puddle_paddle[team->member[j]], func_801091F8_puddle_paddle, 0);
                }
            }
        }
    }
}

void func_8010B820_puddle_paddle(void) {
    D_80111664_puddle_paddle = HuMemAllocTag(PP_SPRITES_MAX * sizeof(PpSpriteData), 31000);
    memset(D_80111664_puddle_paddle, 0, PP_SPRITES_MAX * sizeof(PpSpriteData));
    D_80111660_puddle_paddle = HuMemAllocTag(PP_ANIMMDL_MAX * sizeof(PpAnimModelData), 31000);
    memset(D_80111660_puddle_paddle, 0, PP_ANIMMDL_MAX * sizeof(PpAnimModelData));
    D_80111668_puddle_paddle = HuMemAllocTag(PP_BILLS_MAX * sizeof(PpBillboardData), 31000);
    memset(D_80111668_puddle_paddle, 0, PP_BILLS_MAX * sizeof(PpBillboardData));
    D_8011166C_puddle_paddle = HuMemAllocTag(PP_FUNC_GRP_MAX * sizeof(PpFuncGroup), 31000);
}

PpFuncGroup *func_8010B8B4_puddle_paddle(omObjData *object, s8 groupId, s16 maxModels, s16 maxFuncs) {
    PpFuncGroup *group;

    if (groupId >= PP_FUNC_GRP_MAX) {
        return NULL;
    }
    group = &D_8011166C_puddle_paddle[groupId];
    if (maxFuncs != 0) {
        group->funcCtx = HuMemAllocTag(maxFuncs * sizeof(PpFuncContext), 31000);
        memset(group->funcCtx, 0, maxFuncs * sizeof(PpFuncContext));
        group->order = HuMemAllocTag((maxFuncs + 1) * sizeof(PpFuncOrder), 31000);
    }
    group->maxFuncs = maxFuncs;
    group->groupCtx = HuMemAllocTag(sizeof(PpFuncGroupContext), 31000);
    if (maxModels != 0) {
        group->groupCtx->modelIds = HuMemAllocTag(maxModels * sizeof(s16), 31000);
        memset(group->groupCtx->modelIds, 0, maxModels * sizeof(s16));
    }
    group->groupCtx->maxModels = maxModels;
    group->sort = TRUE;
    group->groupCtx->object = object;
    return group;
}

s16 func_8010BA04_puddle_paddle(s8 groupId, s32 prio, void *data, void (*func)(PpFuncGroupContext *, PpFuncContext *), s8 tag) {
    PpFuncGroup *group = &D_8011166C_puddle_paddle[groupId];
    PpFuncContext *ctx = group->funcCtx;
    s16 maxFuncs = group->maxFuncs;
    s16 i;

    for (i = 0; i < maxFuncs; i++, ctx++) {
        if (!ctx->set) {
            ctx->set = TRUE;
            ctx->prio = prio;
            ctx->id = i;
            ctx->tag = tag;
            ctx->state = 0;
            ctx->data = data;
            ctx->func = func;
            break;
        }
    }
    group->sort = TRUE;
    return i;
}

void func_8010BAA8_puddle_paddle(s8 groupId, PpFuncContext *ctx) {
    memset(ctx, 0, sizeof(PpFuncContext));
    D_8011166C_puddle_paddle[groupId].sort = TRUE;
}

void func_8010BB00_puddle_paddle(s8 groupId, s8 tag) {
    PpFuncGroup *group = &D_8011166C_puddle_paddle[groupId];
    PpFuncContext *ctx;
    s16 i;

    ctx = group->funcCtx;
    for (i = 0; i < group->maxFuncs; i++, ctx++) {
        if (ctx->tag == tag) {
            func_8010BAA8_puddle_paddle(groupId, ctx);
        }
    }
}

void func_8010BBB4_puddle_paddle(s8 groupId) {
    PpFuncGroup *group = &D_8011166C_puddle_paddle[groupId];

    memset(group->funcCtx, 0, group->maxFuncs * sizeof(PpFuncContext));
    group->sort = TRUE;
}

void func_8010BC14_puddle_paddle(s8 groupId) {
    PpFuncGroup *group = &D_8011166C_puddle_paddle[groupId];
    PpFuncContext *ctx;
    s8 orderId;

    if (group->sort) {
        func_8010BD18_puddle_paddle(group);
    }
    orderId = 0;
    while (group->order[orderId].next != -1) {
        orderId = group->order[orderId].next;
        ctx = &group->funcCtx[group->order[orderId].id];
        if (ctx->set) {
            ctx->func(group->groupCtx, ctx);
        }
    }
}

void func_8010BD18_puddle_paddle(PpFuncGroup *group) {
    PpFuncOrder *order = group->order;
    PpFuncContext *currCtx = group->funcCtx;
    s16 orderId;
    s16 i;
    s16 j;
    s16 tail;
    s16 pos;
    s16 found;

    order[0].next = -1;
    orderId = 1;
    tail = 0;
    for (i = 0; i < group->maxFuncs; i++, currCtx++) {
        pos = tail;
        if (!currCtx->set) {
            continue;
        }
        found = FALSE;
        j = 0;
        while (order[j].next != -1) {
            j = order[j].next;
            if (currCtx->prio < order[j].prio) {
                pos = j;
                found = TRUE;
                break;
            }
        }
        order[orderId].id = i;
        order[orderId].prio = currCtx->prio;
        if (found) {
            order[orderId].next = order[order[pos].prev].next;
            order[orderId].prev = order[pos].prev;
            order[order[pos].prev].next = orderId;
            order[order[orderId].next].prev = orderId;
        } else {
            order[orderId].next = order[pos].next;
            order[orderId].prev = pos;
            order[pos].next = orderId;
            tail = orderId;
        }
        orderId++;
    }
    group->sort = FALSE;
}

s16 func_8010BEE8_puddle_paddle(u16 prio, s32 dir, s32 file, u16 arg3, s32 attr) {
    PpSpriteData *sprite;
    HuSprite *temp_v0_2;
    s16 i;

    sprite = D_80111664_puddle_paddle;
    for (i = 0; i < PP_SPRITES_MAX; i++, sprite++) {
        if (sprite->state == 0) {
            sprite->unk02 = func_8000B838_main((dir << 16) | file);
            sprite->groupId = HuSprGrpCreate(1, 0);
            sprite->unk06 = 0xFF;
            HuSprAttrReset(sprite->groupId, 0, -1);
            func_80055024_main(sprite->groupId, 0, sprite->unk02, 0);
            HuSprAttrSet(sprite->groupId, 0, attr);
            func_800550F4_main(sprite->groupId, 0, arg3);
            HuSprPriSet(sprite->groupId, 0, prio);
            func_80054FF8_main(sprite->groupId, 0, 0);
            func_800550B4_main(sprite->groupId, 0, 1.0f);
            HuSprScaleSet(sprite->groupId, 0, 1.0f, 1.0f);
            func_80054904_main(sprite->groupId, 0, 100, 100);
            temp_v0_2 = HuSprGet(sprite->groupId, 0);
            if (arg3 == 0) {
                sprite->unk04 = 99;
            } else {
                sprite->unk04 = temp_v0_2->unk_84->unk10;
            }
            sprite->state = 2;
            func_8010C11C_puddle_paddle(i);
            break;
        }
    }
    return i;
}

void func_8010C088_puddle_paddle(s16 spriteId, s32 posX, s32 posY) {
    PpSpriteData *sprite = &D_80111664_puddle_paddle[spriteId];

    if (sprite->state != 0) {
        func_80054FF8_main(sprite->groupId, 0, 0);
        HuSprAttrReset(sprite->groupId, 0, 0x8000);
        func_80054904_main(sprite->groupId, 0, posX, posY);
        sprite->state = 2;
    }
}

void func_8010C11C_puddle_paddle(s16 spriteId) {
    PpSpriteData *sprite = &D_80111664_puddle_paddle[spriteId];

    if (sprite->state != 0) {
        HuSprAttrSet(sprite->groupId, 0, 0x8000);
        sprite->state = 1;
    }
}

void func_8010C16C_puddle_paddle(void) {
    PpSpriteData *sprite;
    s16 i;

    sprite = D_80111664_puddle_paddle;
    for (i = 0; i < PP_SPRITES_MAX; i++, sprite++) {
        switch (sprite->state) {
            case 2:
                if (HuSprGet(sprite->groupId, 0)->unk_90 + 1 >= sprite->unk04) {
                    HuSprAttrSet(sprite->groupId, 0, 0x8000);
                    func_80054FF8_main(sprite->groupId, 0, 0);
                }
                break;
        }
    }
}

s16 func_8010C214_puddle_paddle(s32 dir, s32 file, f32 freq, s16 tag, s32 attr, s32 arg5) {
    PpAnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_80111660_puddle_paddle;
    for (i = 0; i < PP_ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set) {
            animModel->modelId = func_8000B108_main((dir << 16) | file, arg5);
            func_8001C258_main(animModel->modelId, 4, 4);
            hmfModel = &HmfModelData[animModel->modelId];
            hmfModel->unk40 = 0.0f;
            hmfModel->unk44 = 0.0f;
            if (hmfModel->hmf->unk98 != NULL) {
                hmfModel->hmf->unk98->unk08 = 0;
            }
            animModel->tag = tag;
            animModel->attr = attr;
            animModel->freq = freq;
            animModel->state = -1;
            animModel->set = TRUE;
            break;
        }
    }
    return i;
}

s16 func_8010C324_puddle_paddle(s16 linkModelId, f32 freq, s16 tag, s32 attr) {
    PpAnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_80111660_puddle_paddle;
    for (i = 0; i < PP_ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set) {
            animModel->modelId = Hu3DModelLink(linkModelId);
            func_8001C258_main(animModel->modelId, 4, 4);
            hmfModel = &HmfModelData[animModel->modelId];
            hmfModel->unk40 = 0.0f;
            hmfModel->unk44 = 0.0f;
            if (hmfModel->hmf->unk98 != NULL) {
                hmfModel->hmf->unk98->unk08 = 0;
            }
            animModel->tag = tag;
            animModel->attr = attr;
            animModel->freq = freq;
            animModel->state = -1;
            animModel->set = TRUE;
            break;
        }
    }
    return i;
}

s16 func_8010C42C_puddle_paddle(s16 tag) {
    PpAnimModelData *animModel;
    s16 i;

    animModel = D_80111660_puddle_paddle;
    for (i = 0; i < PP_ANIMMDL_MAX; i++, animModel++) {
        if (animModel->set && animModel->tag == tag && (HmfModelData[animModel->modelId].unk18 & 4)
            && animModel->state == -1) {
            break;
        }
    }
    if (i == PP_ANIMMDL_MAX) {
        return -1;
    }
    return i;
}

s32 func_8010C4D0_puddle_paddle(s16 animModelId, f32 posX, f32 posY, f32 posZ, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 animStart) {
    PpAnimModelData *animModel;
    HmfModel *hmfModel;

    if (animModelId >= PP_ANIMMDL_MAX) {
        return FALSE;
    }
    if (!D_80111660_puddle_paddle[animModelId].set) {
        return FALSE;
    }
    animModel = &D_80111660_puddle_paddle[animModelId];
    hmfModel = &HmfModelData[animModel->modelId];
    if ((hmfModel->unk18 & 4) && animModel->state == -1) {
        Hu3DModelPosSet(animModel->modelId, posX, posY, posZ);
        Hu3DModelScaleSet(animModel->modelId, scale, scale, scale);
        animModel->rotX = rotX;
        animModel->rotY = rotY;
        animModel->rotZ = rotZ;
        if (animStart == 0.0f) {
            func_8001C258_main(animModel->modelId, 4, 0);
            animModel->state = 1;
            animModel->animStart = 0.0f;
            animModel->animTimer = 0.0f;
            hmfModel->unk44 = animModel->freq;
        } else {
            animModel->state = 0;
            animModel->animStart = animStart;
            animModel->animTimer = 0.0f;
        }
        return TRUE;
    }
    return FALSE;
}

void func_8010C664_puddle_paddle(void) {
    PpAnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_80111660_puddle_paddle;
    for (i = 0; i < PP_ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set || animModel->state == -1) {
            continue;
        }
        hmfModel = &HmfModelData[animModel->modelId];
        func_80088910_main((f32 (*)[4])hmfModel->mtx, animModel->rotX, animModel->rotY, animModel->rotZ);
        switch (animModel->state) {
            default:
                if (D_800CCF58_main[HmfModelData[animModel->modelId].unk02].unk02 <= hmfModel->unk40) {
                    hmfModel->unk40 = 0.0f;
                    if (hmfModel->hmf->unk98 != NULL) {
                        hmfModel->hmf->unk98->unk08 = 0;
                    }
                    if (!(animModel->attr & 1)) {
                        func_8001C258_main(animModel->modelId, 4, 4);
                        animModel->state = -1;
                        hmfModel->unk44 = 0.0f;
                    }
                }
                break;
            case 0:
                if (animModel->animStart <= animModel->animTimer++) {
                    func_8001C258_main(animModel->modelId, 4, 0);
                    animModel->state = 1;
                    hmfModel->unk44 = animModel->freq;
                }
                break;
        }
    }
}

s16 func_8010C804_puddle_paddle(s32 dir, s32 file, s16 frameDelay, s16 tag, s32 attr) {
    PpBillboardData *bill;
    s16 spriteId;
    s16 i;

    bill = D_80111668_puddle_paddle;
    for (i = 0; i < PP_BILLS_MAX; i++, bill++) {
        if (!bill->set) {
            bill->spriteId = spriteId = func_8000B838_main((dir << 16) | file);
            if (attr & 1) {
                bill->modelId = func_8010D5E4_puddle_paddle(func_80055194_main(spriteId), 1.0f);
            } else {
                bill->modelId = func_8010CE74_puddle_paddle(func_80055194_main(spriteId), 1.0f);
            }
            if (attr & 8) {
                func_8001C258_main(bill->modelId, 4, 4);
            }
            bill->posX = &HmfModelData[bill->modelId].pos.x;
            bill->posY = &HmfModelData[bill->modelId].pos.y;
            bill->posZ = &HmfModelData[bill->modelId].pos.z;
            bill->tag = tag;
            bill->attr = attr;
            bill->duration = func_80055194_main(spriteId)->unk10;
            bill->timer = 0;
            bill->frameTimer = 0;
            bill->frameDelay = frameDelay;
            bill->set = TRUE;
            break;
        }
    }
    return i;
}

s16 func_8010C98C_puddle_paddle(s16 tag) {
    PpBillboardData *bill;
    s16 i;

    bill = D_80111668_puddle_paddle;
    for (i = 0; i < PP_BILLS_MAX; i++, bill++) {
        if (bill->set && bill->tag == tag && (HmfModelData[bill->modelId].unk18 & 4) && (bill->attr & 8)) {
            break;
        }
    }
    if (i == PP_BILLS_MAX) {
        return -1;
    }
    return i;
}

void func_8010CA30_puddle_paddle(s16 billId, f32 posX, f32 posY, f32 posZ) {
    if (billId < PP_BILLS_MAX) {
        HmfModel *model = &HmfModelData[D_80111668_puddle_paddle[billId].modelId];

        model->pos.x = posX;
        model->pos.y = posY;
        model->pos.z = posZ;
        func_8001C258_main(D_80111668_puddle_paddle[billId].modelId, 4, 0);
        D_80111668_puddle_paddle[billId].attr &= ~(8 | 0x10);
    }
}

void func_8010CAD4_puddle_paddle(s16 billId, f32 *posX, f32 *posY, f32 *posZ) {
    if (billId < PP_BILLS_MAX) {
        HmfModel *model = &HmfModelData[D_80111668_puddle_paddle[billId].modelId];

        if (posX != NULL) {
            D_80111668_puddle_paddle[billId].posX = posX;
        } else {
            D_80111668_puddle_paddle[billId].posX = &model->pos.x;
        }
        if (posY != NULL) {
            D_80111668_puddle_paddle[billId].posY = posY;
        } else {
            D_80111668_puddle_paddle[billId].posY = &model->pos.y;
        }
        if (posZ != NULL) {
            D_80111668_puddle_paddle[billId].posZ = posZ;
        } else {
            D_80111668_puddle_paddle[billId].posZ = &model->pos.z;
        }
        func_8001C258_main(D_80111668_puddle_paddle[billId].modelId, 4, 0);
        D_80111668_puddle_paddle[billId].attr &= ~(8 | 0x10);
        D_80111668_puddle_paddle[billId].attr |= 0x10;
    }
}

PpBillboardData *func_8010CC64_puddle_paddle(s16 billId) {
    if (billId >= PP_BILLS_MAX) {
        return NULL;
    }
    return &D_80111668_puddle_paddle[billId];
}

HmfModel *func_8010CC9C_puddle_paddle(s16 billId) {
    if (billId >= PP_BILLS_MAX) {
        return NULL;
    }
    return &HmfModelData[D_80111668_puddle_paddle[billId].modelId];
}

void func_8010CCF0_puddle_paddle(void) {
    PpBillboardData *bill;
    HmfModel *model;
    s16 i;

    bill = D_80111668_puddle_paddle;
    for (i = 0; i < PP_BILLS_MAX; i++, bill++) {
        if (!bill->set || (bill->attr & 8)) {
            continue;
        }
        model = &HmfModelData[bill->modelId];
        if (bill->attr & 0x10) {
            model->pos.x = *bill->posX;
            model->pos.y = *bill->posY;
            model->pos.z = *bill->posZ;
        }
        model->rot.x = CRot.x;
        model->rot.y = CRot.y;
        if (bill->attr & 1) {
            if (bill->attr & 2) {
                if (++bill->frameTimer > bill->frameDelay) {
                    bill->frameTimer = 0;
                    func_8010EDE8_puddle_paddle(bill->modelId, func_80055194_main(bill->spriteId), bill->timer);
                    if (++bill->timer >= bill->duration) {
                        if (bill->attr & 4) {
                            bill->timer = 0;
                        } else {
                            bill->timer = 0;
                            bill->attr |= 8;
                            func_8001C258_main(bill->modelId, 4, 4);
                        }
                    }
                }
            }
        }
    }
}

s16 func_8010CE74_puddle_paddle(HuSprite_Unk84_Struct *arg0, f32 arg1) {
    HmfData *temp_s6;
    Gfx *temp_v0_0;
    Gfx *temp_v0;
    u32 temp_s5;
    s32 temp_s0;
    s32 var_s7;
    s16 temp_v0_2;
    s16 var_s4;

    temp_v0_0 = temp_v0 = HuMemAlloc(0x10000);
    temp_v0_2 = func_8001A894_main(0x4C1, temp_v0_0, 4);
    temp_s6 = HmfModelData[temp_v0_2].hmf;
    temp_s6->unk60->unk50 |= 0x01010000;
    temp_s5 = func_8010EFEC_puddle_paddle(arg0, temp_s6, 1.0f, 0, 0x64);
    gSPDisplayList(temp_v0++, osVirtualToPhysical(D_80111330_puddle_paddle));
    gDPPipeSync(temp_v0++);
    gDPSetCycleType(temp_v0++, G_CYC_1CYCLE);
    gDPPipeSync(temp_v0++);
    gSPClearGeometryMode(temp_v0++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(temp_v0++, G_ZBUFFER | G_SHADE | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetColorDither(temp_v0++, G_CD_NOISE);
    gDPSetTexturePersp(temp_v0++, G_TP_NONE);
    gDPSetTextureFilter(temp_v0++, G_TF_BILERP);
    gDPSetTextureConvert(temp_v0++, G_TC_FILT);
    gDPSetAlphaDither(temp_v0++, G_AD_PATTERN);
    gDPSetAlphaCompare(temp_v0++, G_AC_NONE);
    gDPSetBlendColor(temp_v0++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(temp_v0++);
    gDPSetRenderMode(temp_v0++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    gDPSetCombineLERP(temp_v0++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(temp_v0++, 0, 0, 0xFF, 0xFF, 0xFF, arg1 * 255.0f);
    gDPPipeSync(temp_v0++);
    gSPTexture(temp_v0++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(temp_v0++, G_TP_PERSP);
    if (arg0->unk1A >= 2) {
        gDPSetTextureLUT(temp_v0++, G_TT_RGBA16);
        var_s7 = 0x800;
        if (arg0->unk18 == 4) {
            gDPLoadTLUT_pal16(temp_v0++, 0, arg0->unk0C);
        } else {
            gDPLoadTLUT_pal256(temp_v0++, arg0->unk0C);
        }
    } else {
        gDPSetTextureLUT(temp_v0++, G_TT_NONE);
        var_s7 = 0x1000;
    }
    gDPPipeSync(temp_v0++);
    for (var_s4 = 0; var_s4 < temp_s5; var_s4++) {
        gSPSegment(temp_v0++, 0x02, osVirtualToPhysical(arg0->unk08 + var_s7 * var_s4));
        gDPLoadTextureBlock(temp_v0++, 0x02000000, G_IM_FMT_CI, G_IM_SIZ_8b,
                            arg0->unk00->unk04, arg0->unk00->unk06 / temp_s5, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(temp_v0++);
        gSPSegment(temp_v0++, 0x01, osVirtualToPhysical(&temp_s6->unk44[0][var_s4 * 4]));
        gSPVertex(temp_v0++, 0x01000000, 4, 0);
        gSP2Triangles(temp_v0++, 0, 1, 2, 0, 1, 3, 2, 0);
    }
    gSPClearGeometryMode(temp_v0++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(temp_v0++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(temp_v0++);
    gSPEndDisplayList(temp_v0++);
    temp_s0 = (u32)temp_v0 - (u32)temp_v0_0;
    temp_s6->unk3C->unk00[0] = HuMemAllocTag(temp_s0, temp_s6->unk0E);
    bcopy(temp_v0_0, temp_s6->unk3C->unk00[0], temp_s0);
    HuMemFree(temp_v0_0);
    return temp_v0_2;
}

// m1 pp3: sprite models and collider system, twins of Baby Bowser Broadside (169540.c, bb3 block)
#include "gcc/memory.h"
#include "mallocblock.h"
#include "math.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/util.h"

#define PP3_ABS(x) ((x) > 0 ? (x) : -(x))
#define PP3_M_ID(m, i, j) ((m)[(i) * 4 + (j)])
#define PP3_VECMagXZ(a) sqrtf(((a)->x * (a)->x) + ((a)->z * (a)->z))

typedef struct {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 a;
} PpRGBA;

typedef struct {
    /* 0x00 */ s8 s8[16];
    /* 0x10 */ s16 s16[8];
    /* 0x20 */ f32 f32[4];
} PpWork; // Size 0x30

typedef struct {
    /* 0x00 */ omObjData *object;
    /* 0x04 */ s16 *modelIds;
    /* 0x08 */ s16 maxModels;
} PpFuncGroupContext; // Size 0xC

typedef struct pp_func_context {
    /* 0x00 */ s8 set;
    /* 0x02 */ s16 id;
    /* 0x04 */ s8 state;
    /* 0x05 */ s8 tag;
    /* 0x08 */ s32 prio;
    /* 0x0C */ PpWork work;
    /* 0x3C */ void *data;
    /* 0x40 */ void (*func)(PpFuncGroupContext *, struct pp_func_context *);
} PpFuncContext; // Size 0x44

typedef struct {
    /* 0x00 */ Vec normal;
    /* 0x0C */ f32 dist;
    /* 0x10 */ s8 axis; // dominant normal axis: 0 x, 1 y, 2 z
} PpPlane; // Size 0x14

// Collider attr bits as Broadside's: 1 disabled, 2 no height test, 0x10 detect only, 0x20 two-sided,
// 0x80 sets the mover's attr bit 1, 0x100 plane, 0x200 sphere, 0x400 cylinder, none: vertical prism.
typedef struct {
    /* 0x00 */ s32 attr;
    /* 0x04 */ s8 set;
    /* 0x08 */ f32 *posX;
    /* 0x0C */ f32 *posY;
    /* 0x10 */ f32 *posZ;
    /* 0x14 */ f32 *rotX;
    /* 0x18 */ f32 *rotY;
    /* 0x1C */ f32 *rotZ;
    /* 0x20 */ f32 transMtx[16];
    /* 0x60 */ Vec base[4];
    /* 0x90 */ Vec cur[4];
    /* 0xC0 */ s16 vertexCount;
    /* 0xC4 */ f32 height;
    /* 0xC8 */ PpPlane plane;
    /* 0xDC */ f32 radius;
    /* 0xE0 */ s16 parent;
} PpCollider; // Size 0xE4

typedef struct {
    /* 0x00 */ s32 attr;
    /* 0x04 */ s16 *colliders;
    /* 0x08 */ s16 count;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ f32 radius;
    /* 0x28 */ s16 model;
    /* 0x2A */ s16 hitPlane;
    /* 0x2C */ s16 hitPrism;
    /* 0x2E */ s16 hitSphere;
    /* 0x30 */ s16 hitCylinder;
} PpMover;

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
extern Gfx D_80111330_puddle_paddle[];
extern PpCollider *D_80111670_puddle_paddle;

void func_8010BAA8_puddle_paddle(s8 groupId, PpFuncContext *ctx);
s16 func_8010EFEC_puddle_paddle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
s16 func_8010F80C_puddle_paddle(PpCollider *c, PpMover *m);
s16 func_8010F9FC_puddle_paddle(PpCollider *c, PpMover *m);
s16 func_8010FBD4_puddle_paddle(PpCollider *c, PpMover *m);
s16 func_8010FEC0_puddle_paddle(PpCollider *c, Vec *p);
f32 func_801101E0_puddle_paddle(PpCollider *c, Vec *p);
s16 func_80110284_puddle_paddle(PpCollider *c, PpMover *m);
f32 func_801104C8_puddle_paddle(PpMover *m, Vec *a, Vec *b);
void func_80110888_puddle_paddle(Vec *v, PpPlane *out);
void func_80110D3C_puddle_paddle(f32 *out);
void func_80110DC4_puddle_paddle(f32 *out, f32 x, f32 y, f32 z);
void func_80110E1C_puddle_paddle(f32 *out, f32 angle);
void func_80110E84_puddle_paddle(f32 *out, f32 angle);
void func_80110EEC_puddle_paddle(f32 *a, f32 *b, f32 *out);
// end m1 pp3 types

s16 func_8010D5E4_puddle_paddle(HuSprite_Unk84_Struct *arg0, f32 arg1) {
    HmfData *temp_s4;
    Gfx *temp_v0_0;
    Gfx *temp_v0;
    s32 temp_s0;
    s16 temp_v0_2;
    s16 var_a2;
    s16 var_s1;

    temp_v0_0 = temp_v0 = HuMemAlloc(0x10000);
    temp_v0_2 = func_8001A894_main(0x4C1, temp_v0_0, 4);
    temp_s4 = HmfModelData[temp_v0_2].hmf;
    temp_s4->unk60->unk50 |= 0x01010000;
    HuMemFree(temp_s4->unk3C);
    temp_s4->unk3C = HuMemAllocTag(0x14, D_800CDD6A_main);
    func_8010EFEC_puddle_paddle(arg0, temp_s4, 1.0f, 0, 0x1E);
    gSPDisplayList(temp_v0++, osVirtualToPhysical(D_80111330_puddle_paddle));
    gDPPipeSync(temp_v0++);
    gDPSetCycleType(temp_v0++, G_CYC_1CYCLE);
    gDPPipeSync(temp_v0++);
    gSPClearGeometryMode(temp_v0++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(temp_v0++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(temp_v0++, G_CD_NOISE);
    gDPSetTexturePersp(temp_v0++, G_TP_NONE);
    gDPSetTextureFilter(temp_v0++, G_TF_BILERP);
    gDPSetTextureConvert(temp_v0++, G_TC_FILT);
    gDPSetAlphaDither(temp_v0++, G_AD_PATTERN);
    gDPSetAlphaCompare(temp_v0++, G_AC_NONE);
    gDPSetBlendColor(temp_v0++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(temp_v0++);
    gDPSetRenderMode(temp_v0++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (arg0->unk1A >= 2) {
        gDPSetCombineLERP(temp_v0++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(temp_v0++, 0, 0, 0xFF, 0xFF, 0xFF, arg1 * 255.0f);
    } else {
        if (arg0->unk18 & 0x8000) {
            gDPSetCombineLERP(temp_v0++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
        } else {
            gDPSetCombineLERP(temp_v0++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        }
        gDPSetPrimColor(temp_v0++, 0, 0, 0xFF, 0xFF, 0xFF, arg1 * 255.0f);
    }
    gDPPipeSync(temp_v0++);
    gSPTexture(temp_v0++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(temp_v0++, G_TP_PERSP);
    if (arg0->unk1A >= 2) {
        gDPSetTextureLUT(temp_v0++, G_TT_RGBA16);
        if (arg0->unk18 == 4) {
            gDPLoadTLUT_pal16(temp_v0++, 0, arg0->unk0C);
        } else {
            gDPLoadTLUT_pal256(temp_v0++, arg0->unk0C);
        }
        gDPPipeSync(temp_v0++);
        var_a2 = 2;
    } else {
        gDPSetTextureLUT(temp_v0++, G_TT_NONE);
        gDPPipeSync(temp_v0++);
        var_a2 = (arg0->unk18 & 0x8000) ? 4 : 0;
    }
    switch (arg0->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(temp_v0++, 0x02000000, var_a2,
                                   arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(temp_v0++, 0x02000000, var_a2, G_IM_SIZ_8b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(temp_v0++, 0x02000000, var_a2, G_IM_SIZ_16b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(temp_v0++);
    gSPSegment(temp_v0++, 0x01, osVirtualToPhysical(temp_s4->unk44[0]));
    gSPVertex(temp_v0++, 0x01000000, 4, 0);
    gSP2Triangles(temp_v0++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(temp_v0++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(temp_v0++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(temp_v0++);
    gSPEndDisplayList(temp_v0++);
    temp_s0 = (u32)temp_v0 - (u32)temp_v0_0;
    temp_s4->unk3C->unk00[0] = temp_s4->unk3C->unk10 = HuMemAllocTag(temp_s0, temp_s4->unk0E);
    bcopy(temp_v0_0, temp_s4->unk3C->unk00[0], temp_s0);
    HuMemFree(temp_v0_0);
    for (var_s1 = 0; var_s1 < D_800D1FF0_main; var_s1++) {
        temp_v0 = *(temp_s4->unk3C->unk00 + (var_s1 + 1)) = HuMemAllocTag(0x100, temp_s4->unk0E);
        gDPPipeSync(temp_v0++);
        gSPSegment(temp_v0++, 0x02, osVirtualToPhysical(arg0->unk00->unk00));
        gSPDisplayList(temp_v0++, osVirtualToPhysical(temp_s4->unk3C->unk10));
        gSPEndDisplayList(temp_v0++);
    }
    temp_s4->unk3C->unk00[0] = temp_s4->unk3C->unk00[D_800D2008_main + 1];
    return temp_v0_2;
}

s16 func_8010E1FC_puddle_paddle(HuSprite_Unk84_Struct *arg0, PpRGBA *arg1) {
    HmfData *temp_s4;
    Gfx *temp_v0_0;
    Gfx *temp_v0_2;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_s1;

    temp_v0_0 = temp_v0_2 = HuMemAlloc(0x10000);
    temp_v0 = func_8001A894_main(0x8C1, temp_v0_0, 4);
    temp_s4 = HmfModelData[temp_v0].hmf;
    temp_s4->unk60->unk50 |= 0x01010000;
    HuMemFree(temp_s4->unk3C);
    temp_s4->unk3C = HuMemAllocTag(0x18, D_800CDD6A_main);
    func_8010EFEC_puddle_paddle(arg0, temp_s4, 1.0f, 0, 0);
    gSPDisplayList(temp_v0_2++, osVirtualToPhysical(D_80111330_puddle_paddle));
    gDPPipeSync(temp_v0_2++);
    gDPSetCycleType(temp_v0_2++, G_CYC_1CYCLE);
    gDPPipeSync(temp_v0_2++);
    gSPClearGeometryMode(temp_v0_2++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(temp_v0_2++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(temp_v0_2++, G_CD_NOISE);
    gDPSetTexturePersp(temp_v0_2++, G_TP_NONE);
    gDPSetTextureFilter(temp_v0_2++, G_TF_BILERP);
    gDPSetTextureConvert(temp_v0_2++, G_TC_FILT);
    gDPSetAlphaDither(temp_v0_2++, G_AD_PATTERN);
    gDPSetAlphaCompare(temp_v0_2++, G_AC_NONE);
    gDPSetBlendColor(temp_v0_2++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(temp_v0_2++);
    gDPSetRenderMode(temp_v0_2++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (arg0->unk18 & 0x8000) {
        gDPSetCombineLERP(temp_v0_2++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(temp_v0_2++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(temp_v0_2++);
    gSPEndDisplayList(temp_v0_2++);
    temp_s0 = (u32)temp_v0_2 - (u32)temp_v0_0;
    temp_s4->unk3C->unk10 = HuMemAllocTag(temp_s0, temp_s4->unk0E);
    bcopy(temp_v0_0, temp_s4->unk3C->unk10, temp_s0);
    HuMemFree(temp_v0_0);
    temp_v0_0 = temp_v0_2 = HuMemAlloc(0x10000);
    gSPTexture(temp_v0_2++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(temp_v0_2++, G_TP_PERSP);
    if (arg0->unk1A >= 2) {
        gDPSetTextureLUT(temp_v0_2++, G_TT_RGBA16);
        if (arg0->unk18 == 4) {
            gDPLoadTLUT_pal16(temp_v0_2++, 0, arg0->unk0C);
        } else {
            gDPLoadTLUT_pal256(temp_v0_2++, arg0->unk0C);
        }
        gDPPipeSync(temp_v0_2++);
        var_a2 = 2;
    } else {
        gDPSetTextureLUT(temp_v0_2++, G_TT_NONE);
        gDPPipeSync(temp_v0_2++);
        var_a2 = (arg0->unk18 & 0x8000) ? 4 : 0;
    }
    switch (arg0->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(temp_v0_2++, 0x02000000, var_a2,
                                   arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(temp_v0_2++, 0x02000000, var_a2, G_IM_SIZ_8b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(temp_v0_2++, 0x02000000, var_a2, G_IM_SIZ_16b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(temp_v0_2++);
    gSPSegment(temp_v0_2++, 0x01, osVirtualToPhysical(temp_s4->unk44[0]));
    gSPVertex(temp_v0_2++, 0x01000000, 4, 0);
    gSP2Triangles(temp_v0_2++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(temp_v0_2++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(temp_v0_2++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(temp_v0_2++);
    gSPEndDisplayList(temp_v0_2++);
    temp_s0 = (u32)temp_v0_2 - (u32)temp_v0_0;
    temp_s4->unk3C->unk14 = HuMemAllocTag(temp_s0, temp_s4->unk0E);
    bcopy(temp_v0_0, temp_s4->unk3C->unk14, temp_s0);
    HuMemFree(temp_v0_0);
    for (var_s1 = 0; var_s1 < D_800D1FF0_main; var_s1++) {
        temp_v0_2 = temp_s4->unk3C->unk00[var_s1 + 1] = HuMemAllocTag(0x100, temp_s4->unk0E);
        gDPPipeSync(temp_v0_2++);
        gSPSegment(temp_v0_2++, 0x02, osVirtualToPhysical(arg0->unk00->unk00));
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s4->unk3C->unk10));
        gDPSetPrimColor(temp_v0_2++, 0, 0, arg1->r, arg1->g, arg1->b, arg1->a);
        gDPPipeSync(temp_v0_2++);
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s4->unk3C->unk14));
        gDPPipeSync(temp_v0_2++);
        gSPEndDisplayList(temp_v0_2++);
    }
    temp_s4->unk3C->unk00[0] = temp_s4->unk3C->unk00[D_800D2008_main + 1];
    return temp_v0;
}

void func_8010EDE8_puddle_paddle(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2) {
    HmfModel *model = &HmfModelData[modelId];
    HmfData *temp_s2 = model->hmf;
    HmfModelData_Unk64_Unk3C_Struct *temp_v1 = temp_s2->unk3C;
    Gfx *temp_s0 = temp_v1->unk00[D_800D2008_main + 1];

    temp_v1->unk00[0] = temp_s0;
    gDPPipeSync(&temp_s0[0]);
    gSPSegment(&temp_s0[1], 0x02, osVirtualToPhysical(arg1->unk00[arg2].unk00));
    gSPDisplayList(&temp_s0[2], osVirtualToPhysical(temp_s2->unk3C->unk10));
    gDPPipeSync(&temp_s0[3]);
    gSPEndDisplayList(&temp_s0[4]);
}

void func_8010EEB8_puddle_paddle(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, PpRGBA *arg3) {
    HmfModel *model = &HmfModelData[modelId];
    HmfData *temp_s3 = model->hmf;
    HmfModelData_Unk64_Unk3C_Struct *temp_v1 = temp_s3->unk3C;
    Gfx *temp_s0 = temp_v1->unk00[D_800D2008_main + 1];

    temp_v1->unk00[0] = temp_s0;
    gDPPipeSync(&temp_s0[0]);
    gSPSegment(&temp_s0[1], 0x02, osVirtualToPhysical(arg1->unk00[arg2].unk00));
    gSPDisplayList(&temp_s0[2], osVirtualToPhysical(temp_s3->unk3C->unk10));
    gDPSetPrimColor(&temp_s0[3], 0, 0, arg3->r, arg3->g, arg3->b, arg3->a);
    gDPPipeSync(&temp_s0[4]);
    gSPDisplayList(&temp_s0[5], osVirtualToPhysical(temp_s3->unk3C->unk14));
    gDPPipeSync(&temp_s0[6]);
    gSPEndDisplayList(&temp_s0[7]);
}

const f64 D_80111640_puddle_paddle = 32.0;
const f64 D_80111648_puddle_paddle = 0.5;

s16 func_8010EFEC_puddle_paddle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
    Vtx *temp_s7;
    Vtx *var_s1;
    Vtx_t *var_t0;
    Vtx_t *var_a3;
    s32 var_a2;
    s32 temp_s4;
    s32 temp_a1;
    s32 sp24;
    s32 temp_f2;
    s32 var_s0;
    s32 var_s2;
    s32 sp2C;
    s32 temp_lo;
    s32 temp_s3;
    s32 var_s0_2;
    s32 var_a2_2;

    if (arg0->unk1A >= 2) {
        var_a2 = 0x800;
    } else {
        var_a2 = 0x1000;
    }
    temp_s4 = arg0->unk00->unk04;
    temp_a1 = arg0->unk00->unk06;
    sp24 = (f64)(temp_s4 * 0x64) * arg2 / D_80111640_puddle_paddle;
    temp_f2 = (f64)(temp_a1 * 0x64) * arg2 / D_80111640_puddle_paddle;
    if ((arg0->unk18 & 0xFFF) == 4) {
        var_s0 = ((temp_s4 + 1) & 0xFFFE) * temp_a1 * 4;
    } else {
        var_s0 = temp_s4 * temp_a1 * arg0->unk18;
    }
    var_s0 = (var_s0 < 0) ? (var_s0 + 7) : var_s0;
    var_s0 >>= 3;
    var_s2 = var_s0 / var_a2;
    if (var_s2 <= 0) {
        var_s2 = 1;
    }
    sp2C = temp_a1 / var_s2;
    temp_lo = temp_f2 / var_s2;
    temp_s3 = var_s2 * 4;
    temp_s7 = var_s1 = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
    memset(temp_s7, 0, temp_s3 * sizeof(Vtx));
    for (var_s0_2 = 0; var_s0_2 < var_s2; var_s0_2++, var_s1 += 4) {
        var_s1[0].v.ob[0] = (s32)(sp24 * D_80111648_puddle_paddle);
        var_s1[0].v.ob[1] = (s32)(temp_f2 * D_80111648_puddle_paddle - temp_lo * var_s0_2);
        var_s1[0].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[0].v.tc[1] = 0;
        var_s1[1].v.ob[0] = (s32)(sp24 * D_80111648_puddle_paddle);
        var_s1[1].v.ob[1] = (s32)(temp_f2 * D_80111648_puddle_paddle - temp_lo * (var_s0_2 + 1));
        var_s1[1].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[1].v.tc[1] = (sp2C - 1) * 64;
        var_s1[2].v.ob[0] = (s32) - (sp24 * D_80111648_puddle_paddle);
        var_s1[2].v.ob[1] = (s32)(temp_f2 * D_80111648_puddle_paddle - temp_lo * var_s0_2);
        var_s1[2].v.tc[0] = 0;
        var_s1[2].v.tc[1] = 0;
        var_s1[3].v.ob[0] = (s32) - (sp24 * D_80111648_puddle_paddle);
        var_s1[3].v.ob[1] = (s32)(temp_f2 * D_80111648_puddle_paddle - temp_lo * (var_s0_2 + 1));
        var_s1[3].v.tc[0] = 0;
        var_s1[3].v.tc[1] = (sp2C - 1) * 64;
        for (var_a2_2 = 0; var_a2_2 < 4; var_a2_2++) {
            var_s1[var_a2_2].v.ob[0] += arg3;
            var_s1[var_a2_2].v.ob[1] += arg4;
            var_s1[var_a2_2].v.ob[2] = 0;
            var_s1[var_a2_2].v.flag = 0;
            var_s1[var_a2_2].v.cn[3] = 0xFF;
            var_s1[var_a2_2].v.cn[0] = var_s1[var_a2_2].v.cn[1] = var_s1[var_a2_2].v.cn[2] = 0;
        }
    }
    var_s1 = temp_s7;
    for (var_s0_2 = 0; var_s0_2 < D_800D1FF0_main; var_s0_2++) {
        arg1->unk44[var_s0_2] = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
        var_t0 = &arg1->unk44[var_s0_2]->v;
        var_a3 = &var_s1->v;
        for (var_a2_2 = 0; var_a2_2 < temp_s3; var_a2_2++) {
            *(var_t0++) = *(var_a3++);
        }
    }
    HuMemFree(temp_s7);
    return var_s2;
}

void func_8010F410_puddle_paddle(PpFuncGroupContext *groupCtx, PpFuncContext *ctx) {
    func_8010BAA8_puddle_paddle(ctx->tag, ctx);
}

s32 func_8010F42C_puddle_paddle(void) {
    s32 unused[6];

    return 0;
}

s32 func_8010F43C_puddle_paddle(void) {
    s32 unused[6];

    return 0;
}

void func_8010F44C_puddle_paddle(s16 colliderId, Vec *base, f32 height) {
    if (colliderId < 0 && D_80111670_puddle_paddle[colliderId].set) {
        PpCollider *collider = &D_80111670_puddle_paddle[colliderId];

        memcpy(collider->base, base, collider->vertexCount * sizeof(Vec));
        collider->height = height;
        func_80110888_puddle_paddle(collider->base, &collider->plane);
    }
}

void func_8010F4DC_puddle_paddle(void) {
    s32 unused[8];
}

void func_8010F4E8_puddle_paddle(PpMover *mover, s16 maxColliders, f32 radius, s16 modelId) {
    if (mover != NULL) {
        mover->count = maxColliders + 1;
        mover->colliders = HuMemAllocTag(mover->count * sizeof(s16), 31000);
        memset(mover->colliders, -1, mover->count * sizeof(s16));
        mover->pos.x = mover->pos.y = mover->pos.z = 0.0f;
        mover->vel.x = mover->vel.y = mover->vel.z = 0.0f;
        mover->radius = radius;
        mover->model = modelId;
    }
}

void func_8010F580_puddle_paddle(PpMover *mover) {
    PpCollider *collider;
    s16 i;

    mover->hitCylinder = 0;
    mover->hitPlane = 0;
    mover->hitPrism = 0;
    mover->hitSphere = 0;
    mover->attr &= ~1;
    if (mover->model != -1) {
        mover->pos.x = HmfModelData[mover->model].pos.x;
        mover->pos.y = HmfModelData[mover->model].pos.y;
        mover->pos.z = HmfModelData[mover->model].pos.z;
    }
    for (i = 1; i < mover->count; i++) {
        if (mover->colliders[i] == -1) {
            continue;
        }
        collider = &D_80111670_puddle_paddle[mover->colliders[i]];
        if (collider->attr & 1) {
            continue;
        }
        if (collider->attr & 0x400) {
            if (func_8010F80C_puddle_paddle(collider, mover)) {
                if (!(collider->attr & 0x80)) {
                    mover->hitCylinder = i;
                } else {
                    mover->attr |= 1;
                }
            }
        } else if (collider->attr & 0x200) {
            if (func_8010F9FC_puddle_paddle(collider, mover)) {
                if (!(collider->attr & 0x80)) {
                    mover->hitSphere = i;
                } else {
                    mover->attr |= 1;
                }
            }
        } else if (collider->attr & 0x100) {
            if (func_8010FBD4_puddle_paddle(collider, mover)) {
                mover->hitPlane = i;
            }
        } else {
            if (func_80110284_puddle_paddle(collider, mover)) {
                if (collider->attr & 0x80) {
                    mover->attr |= 1;
                } else {
                    mover->hitPrism = i;
                }
            }
        }
    }
    mover->pos.x += mover->vel.x;
    mover->pos.y += mover->vel.y;
    mover->pos.z += mover->vel.z;
    if (mover->model != -1) {
        HmfModelData[mover->model].pos.x = mover->pos.x;
        HmfModelData[mover->model].pos.y = mover->pos.y;
        HmfModelData[mover->model].pos.z = mover->pos.z;
    }
}

s16 func_8010F80C_puddle_paddle(PpCollider *c, PpMover *m) {
    f32 range[2];
    Vec pos;
    Vec vel;
    Vec next;
    Vec d;
    f32 half;
    f32 dist;

    pos.x = m->pos.x;
    pos.y = m->pos.y;
    pos.z = m->pos.z;
    vel.x = m->vel.x;
    vel.y = m->vel.y;
    vel.z = m->vel.z;
    next.x = pos.x + vel.x;
    next.y = pos.y + vel.y;
    next.z = pos.z + vel.z;
    half = m->radius * 0.5f;
    range[0] = c->cur[0].y - half;
    range[1] = c->cur[0].y + c->height + half;
    if (!(next.y < range[0])) {
        if (range[1] < next.y) {
            return 0;
        }
        d.x = c->cur[0].x - next.x;
        d.z = c->cur[0].z - next.z;
        dist = HuSqrtf(d.x * d.x + d.z * d.z);
        if (!(dist <= m->radius + c->radius)) {
            return 0;
        }
        if (c->attr & 0x10) {
            return 1;
        }
        if (dist != 0.0f) {
            d.x /= dist;
            d.x *= m->radius + c->radius;
            d.z /= dist;
            d.z *= m->radius + c->radius;
        }
        next.x = c->cur[0].x - d.x;
        next.z = c->cur[0].z - d.z;
    } else {
        return 0;
    }
    vel.x = next.x - pos.x;
    vel.z = next.z - pos.z;
    m->vel.x = vel.x;
    m->vel.y = vel.y;
    m->vel.z = vel.z;
    return 1;
}

s16 func_8010F9FC_puddle_paddle(PpCollider *c, PpMover *m) {
    Vec pos;
    Vec vel;
    Vec next;
    Vec d;
    f32 dist;

    pos.x = m->pos.x;
    pos.y = m->pos.y;
    pos.z = m->pos.z;
    vel.x = m->vel.x;
    vel.y = m->vel.y;
    vel.z = m->vel.z;
    next.x = pos.x + vel.x;
    next.y = pos.y + vel.y;
    next.z = pos.z + vel.z;
    d.x = c->cur[0].x - next.x;
    d.y = c->cur[0].y - next.y;
    d.z = c->cur[0].z - next.z;
    dist = HuSqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
    if (!(dist <= m->radius + c->radius)) {
        return 0;
    }
    if (!(c->attr & 0x10)) {
        if (dist != 0.0f) {
            d.x /= dist;
            d.x *= m->radius + c->radius;
            d.y /= dist;
            d.y *= m->radius + c->radius;
            d.z /= dist;
            d.z *= m->radius + c->radius;
        }
        next.x = c->cur[0].x - d.x;
        next.y = c->cur[0].y - d.y;
        next.z = c->cur[0].z - d.z;
    } else {
        return 1;
    }
    vel.x = next.x - pos.x;
    vel.y = next.y - pos.y;
    vel.z = next.z - pos.z;
    m->vel.x = vel.x;
    m->vel.y = vel.y;
    m->vel.z = vel.z;
    return 1;
}

s16 func_8010FBD4_puddle_paddle(PpCollider *c, PpMover *m) {
    Vec n;
    Vec pos;
    Vec vel;
    Vec next;
    Vec proj;
    f32 d;
    f32 dist;
    f32 side;
    s16 hit;

    n.x = c->plane.normal.x;
    n.y = c->plane.normal.y;
    n.z = c->plane.normal.z;
    d = -c->plane.dist;
    pos.x = m->pos.x;
    pos.y = m->pos.y;
    pos.z = m->pos.z;
    vel.x = m->vel.x;
    vel.y = m->vel.y;
    vel.z = m->vel.z;
    if (!(c->attr & 0x20)) {
        side = n.x * pos.x + n.y * pos.y + n.z * pos.z + d;
        if (side < 0.0f) {
            return 0;
        }
    }
    next.x = pos.x + vel.x;
    next.y = pos.y + vel.y;
    next.z = pos.z + vel.z;
    if (!(c->attr & 0x20)) {
        side = n.x * next.x + n.y * next.y + n.z * next.z + d;
        dist = func_801101E0_puddle_paddle(c, &next);
        if (side > 0.0f) {
            if (m->radius <= PP3_ABS(dist)) {
                return 0;
            }
        }
    } else {
        dist = func_801101E0_puddle_paddle(c, &next);
        if (m->radius <= PP3_ABS(dist)) {
            return 0;
        }
    }
    proj.x = -n.x * dist + next.x;
    proj.y = -n.y * dist + next.y;
    proj.z = -n.z * dist + next.z;
    hit = func_8010FEC0_puddle_paddle(c, &proj);
    if (hit) {
        if (c->attr & 0x10) {
            return 1;
        }
        next.x = n.x * m->radius * 1.01f + proj.x;
        next.y = n.y * m->radius * 1.01f + proj.y;
        next.z = n.z * m->radius * 1.01f + proj.z;
        vel.x = next.x - pos.x;
        vel.y = next.y - pos.y;
        vel.z = next.z - pos.z;
        m->vel.x = vel.x;
        m->vel.y = vel.y;
        m->vel.z = vel.z;
    }
    return hit;
}

#ifdef NON_MATCHING
s16 func_8010FEC0_puddle_paddle(PpCollider *c, Vec *p) {
    Vec e;
    Vec q;
    s16 i;
    s16 j;

    switch (c->plane.axis) {
    case 0:
        for (i = 0; i < c->vertexCount; i++) {
            j = i + 1;
            if (j == c->vertexCount) {
                j = 0;
            }
            e.y = c->cur[j].y - c->cur[i].y;
            e.z = c->cur[j].z - c->cur[i].z;
            q.y = p->y - c->cur[i].y;
            q.z = p->z - c->cur[i].z;
            if ((e.y * q.z - e.z * q.y) * c->plane.normal.x < 0.0f) {
                return 0;
            }
        }
        break;
    case 1:
        for (i = 0; i < c->vertexCount; i++) {
            j = i + 1;
            if (j == c->vertexCount) {
                j = 0;
            }
            e.x = c->cur[j].x - c->cur[i].x;
            e.z = c->cur[j].z - c->cur[i].z;
            q.x = p->x - c->cur[i].x;
            q.z = p->z - c->cur[i].z;
            if ((e.z * q.x - e.x * q.z) * c->plane.normal.y < 0.0f) {
                return 0;
            }
        }
        // fallthrough (retail: missing break, the y-dominant case also runs the z test)
    case 2:
        for (i = 0; i < c->vertexCount; i++) {
            j = i + 1;
            if (j == c->vertexCount) {
                j = 0;
            }
            e.x = c->cur[j].x - c->cur[i].x;
            e.y = c->cur[j].y - c->cur[i].y;
            q.x = p->x - c->cur[i].x;
            q.y = p->y - c->cur[i].y;
            if ((e.x * q.y - e.y * q.x) * c->plane.normal.z < 0.0f) {
                return 0;
            }
        }
        break;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010FEC0_puddle_paddle);
#endif

f32 func_801101E0_puddle_paddle(PpCollider *c, Vec *p) {
    Vec n;
    f32 x = p->x;
    f32 y = p->y;
    f32 z = p->z;

    n.x = c->plane.normal.x;
    n.y = c->plane.normal.y;
    n.z = c->plane.normal.z;
    return (x * n.x + y * n.y + z * n.z - c->plane.dist) / HuSqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
}

s16 func_80110284_puddle_paddle(PpCollider *c, PpMover *m) {
    f32 side;
    f32 edge;
    s16 i;
    s16 j;

    if (!(c->attr & 2) && m->pos.y > c->height) {
        return 0;
    }
    side = func_801104C8_puddle_paddle(m, &c->cur[0], &c->cur[1]);
    if (side == 0.0f) {
        return 0;
    }
    if (side > 0.0f) {
        for (i = 1; i < c->vertexCount; i++) {
            j = i + 1;
            if (j == c->vertexCount) {
                j = 0;
            }
            edge = func_801104C8_puddle_paddle(m, &c->cur[i], &c->cur[j]);
            if (edge == 0.0f) {
                return 1;
            }
            if (edge < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < c->vertexCount; i++) {
            j = i + 1;
            if (j == c->vertexCount) {
                j = 0;
            }
            edge = func_801104C8_puddle_paddle(m, &c->cur[i], &c->cur[j]);
            if (edge == 0.0f) {
                return 1;
            }
            if (edge > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}

f32 func_801104C8_puddle_paddle(PpMover *m, Vec *a, Vec *b) {
    Vec modelPos;
    Vec ma;
    Vec mb;

    modelPos.x = m->pos.x;
    modelPos.z = m->pos.z;
    ma.x = a->x - modelPos.x;
    ma.z = a->z - modelPos.z;
    mb.x = b->x - modelPos.x;
    mb.z = b->z - modelPos.z;
    return ma.z * mb.x - ma.x * mb.z;
}

u8 func_80110524_puddle_paddle(f32 *out, u8 *timer, f32 start, f32 end, f32 duration) {
    f32 t = *timer / duration;

    *out = start + (end - start) * t;
    if (++(*timer) > duration) {
        *timer = 0;
        *out = end;
        return TRUE;
    }
    return FALSE;
}

f32 func_8011059C_puddle_paddle(f32 t, f32 p0, f32 p1, f32 p2) {
    if (t > 1.0f) {
        t = 1.0f;
    }
    return (1.0f - t) * (1.0f - t) * p0 + 2.0f * (1.0f - t) * t * p1 + t * t * p2;
}

void func_80110608_puddle_paddle(s16 *out, s16 n) {
    s16 temp;
    s16 i;

    for (i = 0; i < n; i++) {
        out[i] = i;
    }
    for (i = n - 1; i >= 0; i--) {
        s16 rand = rand16() % (i + 1);

        temp = out[i];
        out[i] = out[rand];
        out[rand] = temp;
    }
}

void func_80110714_puddle_paddle(omObjData *object) {
    HmfModel *model = &HmfModelData[object->model[0]];

    object->scale.x = model->scale.x;
    object->scale.y = model->scale.y;
    object->scale.z = model->scale.z;
    object->trans.x = model->pos.x;
    object->trans.y = model->pos.y;
    object->trans.z = model->pos.z;
    if (model->rot.x >= 360.0f) {
        model->rot.x -= 360.0f;
    }
    if (model->rot.x < 0.0f) {
        model->rot.x += 360.0f;
    }
    if (model->rot.y >= 360.0f) {
        model->rot.y -= 360.0f;
    }
    if (model->rot.y < 0.0f) {
        model->rot.y += 360.0f;
    }
    if (model->rot.z >= 360.0f) {
        model->rot.z -= 360.0f;
    }
    if (model->rot.z < 0.0f) {
        model->rot.z += 360.0f;
    }
    object->rot.x = model->rot.x;
    object->rot.y = model->rot.y;
    object->rot.z = model->rot.z;
}

void func_80110888_puddle_paddle(Vec *v, PpPlane *out) {
    f32 n[3];
    f32 e1x, e1y, e1z;
    f32 e2x, e2y, e2z;
    f32 len;
    s16 max;
    s16 i;

    e1x = v[1].x - v[0].x;
    e1y = v[1].y - v[0].y;
    e1z = v[1].z - v[0].z;
    e2x = v[2].x - v[0].x;
    e2y = v[2].y - v[0].y;
    e2z = v[2].z - v[0].z;
    n[0] = e1y * e2z - e1z * e2y;
    n[1] = e1z * e2x - e1x * e2z;
    n[2] = e1x * e2y - e1y * e2x;
    len = HuSqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
    if (len != 0.0f) {
        n[0] /= len;
        n[1] /= len;
        n[2] /= len;
    }
    out->dist = n[0] * v[0].x + n[1] * v[0].y + n[2] * v[0].z;
    max = 0;
    for (i = 1; i < 3; i++) {
        if (PP3_ABS(n[max]) < PP3_ABS(n[i])) {
            max = i;
        }
    }
    out->normal.x = n[0];
    out->normal.y = n[1];
    out->normal.z = n[2];
    out->axis = max;
}

void func_80110A8C_puddle_paddle(Vec from, Vec to, f32 *out) {
    Vec direction;
    f32 fullRot = 360.0f;
    f32 pitch;
    f32 yaw;

    direction.x = to.x - from.x;
    direction.y = to.y - from.y;
    direction.z = to.z - from.z;
    pitch = atan2df(direction.y, PP3_VECMagXZ(&direction));
    if (pitch < 0.0f) {
        pitch += fullRot;
    } else if (pitch >= fullRot) {
        pitch -= fullRot;
    }
    *(out++) = pitch;
    yaw = atan2df(direction.x, direction.z);
    if (yaw < 0.0f) {
        yaw += fullRot;
    } else if (yaw >= fullRot) {
        yaw -= fullRot;
    }
    *(out++) = yaw;
}

void func_80110BBC_puddle_paddle(f32 *a, f32 *b) {
    f32 diff;

    while (*b < 0.0f) {
        *b += 360.0f;
    }
    while (*b >= 360.0f) {
        *b -= 360.0f;
    }
    while (*a < 0.0f) {
        *a += 360.0f;
    }
    while (*a >= 360.0f) {
        *a -= 360.0f;
    }
    diff = PP3_ABS(*b - *a);
    if (diff > 180.0f) {
        if (*a < *b) {
            *b -= 360.0f;
        } else {
            *a -= 360.0f;
        }
    }
}

void func_80110D3C_puddle_paddle(f32 *out) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            PP3_M_ID(out, i, j) = 0.0f;
        }
        PP3_M_ID(out, i, i) = 1.0f;
    }
}

void func_80110DC4_puddle_paddle(f32 *out, f32 x, f32 y, f32 z) {
    func_80110D3C_puddle_paddle(out);
    PP3_M_ID(out, 3, 0) = x;
    PP3_M_ID(out, 3, 1) = y;
    PP3_M_ID(out, 3, 2) = z;
}

void func_80110E1C_puddle_paddle(f32 *out, f32 angle) {
    func_80110D3C_puddle_paddle(out);
    PP3_M_ID(out, 1, 1) = cosdf(angle);
    PP3_M_ID(out, 1, 2) = sindf(angle);
    PP3_M_ID(out, 2, 1) = -sindf(angle);
    PP3_M_ID(out, 2, 2) = cosdf(angle);
}

void func_80110E84_puddle_paddle(f32 *out, f32 angle) {
    func_80110D3C_puddle_paddle(out);
    PP3_M_ID(out, 0, 0) = cosdf(angle);
    PP3_M_ID(out, 0, 2) = -sindf(angle);
    PP3_M_ID(out, 2, 0) = sindf(angle);
    PP3_M_ID(out, 2, 2) = cosdf(angle);
}

void func_80110EEC_puddle_paddle(f32 *a, f32 *b, f32 *out) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            PP3_M_ID(out, i, j) = PP3_M_ID(a, i, 0) * PP3_M_ID(b, 0, j) + PP3_M_ID(a, i, 1) * PP3_M_ID(b, 1, j) +
                                  PP3_M_ID(a, i, 2) * PP3_M_ID(b, 2, j) + PP3_M_ID(a, i, 3) * PP3_M_ID(b, 3, j);
        }
    }
}

void func_80110FA0_puddle_paddle(f32 *arg0, f32 *out) {
    *(out++) = PP3_M_ID(arg0, 3, 0) * PP3_M_ID(arg0, 0, 0) + PP3_M_ID(arg0, 3, 1) * PP3_M_ID(arg0, 1, 0) + PP3_M_ID(arg0, 3, 2) * PP3_M_ID(arg0, 2, 0);
    *(out++) = PP3_M_ID(arg0, 3, 0) * PP3_M_ID(arg0, 0, 1) + PP3_M_ID(arg0, 3, 1) * PP3_M_ID(arg0, 1, 1) + PP3_M_ID(arg0, 3, 2) * PP3_M_ID(arg0, 2, 1);
    *(out++) = PP3_M_ID(arg0, 3, 0) * PP3_M_ID(arg0, 0, 2) + PP3_M_ID(arg0, 3, 1) * PP3_M_ID(arg0, 1, 2) + PP3_M_ID(arg0, 3, 2) * PP3_M_ID(arg0, 2, 2);
}

void func_80111038_puddle_paddle(f32 transX, f32 transY, f32 transZ, f32 rotX, f32 rotY, f32 rotZ, f32 *out) {
    f32 translationMtx[16];
    f32 rotXMtx[16];
    f32 rotYMtx[16];
    f32 rotMtx[16];

    func_80110DC4_puddle_paddle(translationMtx, transX, transY, transZ);
    func_80110E1C_puddle_paddle(rotXMtx, rotX);
    func_80110E84_puddle_paddle(rotYMtx, rotY);
    func_80110EEC_puddle_paddle(rotXMtx, rotYMtx, rotMtx);
    func_80110EEC_puddle_paddle(rotMtx, translationMtx, out);
}

void func_801110F0_puddle_paddle(Vec *in, s16 n, f32 *mtx, Vec *out) {
    s16 i;

    for (i = 0; i < n; i++) {
        out[i].x = (PP3_M_ID(mtx, 3, 0) + in[i].x) * PP3_M_ID(mtx, 0, 0) + (PP3_M_ID(mtx, 3, 1) + in[i].y) * PP3_M_ID(mtx, 1, 0) + (PP3_M_ID(mtx, 3, 2) + in[i].z) * PP3_M_ID(mtx, 2, 0);
        out[i].y = (PP3_M_ID(mtx, 3, 0) + in[i].x) * PP3_M_ID(mtx, 0, 1) + (PP3_M_ID(mtx, 3, 1) + in[i].y) * PP3_M_ID(mtx, 1, 1) + (PP3_M_ID(mtx, 3, 2) + in[i].z) * PP3_M_ID(mtx, 2, 1);
        out[i].z = (PP3_M_ID(mtx, 3, 0) + in[i].x) * PP3_M_ID(mtx, 0, 2) + (PP3_M_ID(mtx, 3, 1) + in[i].y) * PP3_M_ID(mtx, 1, 2) + (PP3_M_ID(mtx, 3, 2) + in[i].z) * PP3_M_ID(mtx, 2, 2);
    }
}

// m1 pp3: the unit's .data (0x80111220..0x80111638; the linker's ALIGN(0x10) pads to 0x80111640)
typedef struct {
    /* 0x00 */ s32 file[8];
} PpFileTable; // Size 0x20

typedef struct {
    /* 0x00 */ s16 v[6];
} PpS16x6; // Size 0xC

typedef struct {
    /* 0x00 */ s16 v[3];
} PpS16x3; // Size 6

typedef struct {
    /* 0x00 */ char name[16][32];
} PpNameTable; // Size 0x200

typedef struct {
    /* 0x00 */ Vec pos[2];
} PpVecPair; // Size 0x18

f32 D_80111220_puddle_paddle = 0.0f;
f32 D_80111224_puddle_paddle = 0.0f;
f32 D_80111228_puddle_paddle = 180.0f;
s16 D_8011122C_puddle_paddle = -1;
s16 D_8011122E_puddle_paddle = 0;
s16 D_80111230_puddle_paddle = 0;
s16 D_80111232_puddle_paddle = 0;
s16 D_80111234_puddle_paddle[6] = { 0 }; // only [0] is referenced

Gfx D_80111240_puddle_paddle[] = {
    gsSPSegment(0x00, 0x00000000),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPNoOp(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_801112F8_puddle_paddle[] = {
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx D_80111318_puddle_paddle[] = {
    gsSPDisplayList(D_801112F8_puddle_paddle),
    gsSPDisplayList(D_80111240_puddle_paddle),
    gsSPEndDisplayList(),
};

Gfx D_80111330_puddle_paddle[] = {
    gsDPPipeSync(),
    gsSPDisplayList(D_80111318_puddle_paddle),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

s16 D_80111370_puddle_paddle[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0 }; // "ＳＴＡＲＴ"
s16 D_8011137C_puddle_paddle[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0 }; // "ＦＩＮＩＳＨ"
s16 D_8011138C_puddle_paddle[] = { 0x8263, 0x8271, 0x8260, 0x8276, 0 }; // "ＤＲＡＷ"
PpFileTable D_80111398_puddle_paddle = { { 8, 9, 10, 11, 12, 13, 14, 15 } };
PpS16x6 D_801113B8_puddle_paddle = { { 0x21, 0x26, 0x21, 0x27, 0x32, 0x14 } };
PpS16x3 D_801113C4_puddle_paddle = { { 8, 4, 4 } };
PpS16x3 D_801113CC_puddle_paddle = { { 0, 1, 2 } };
PpFileTable D_801113D4_puddle_paddle = { { 12, 13, 14, 15, 16, 17, 18, 19 } };
PpFileTable D_801113F4_puddle_paddle = { { 4, 5, 6, 7, 8, 9, 10, 11 } };
PpNameTable D_80111414_puddle_paddle = { {
    "migi-te2_4",
    "migi-te3_2_1",
    "c001_000-migi-te2_2",
    "c001_000-migi-te2_3",
    "C002_000b-bmerge14",
    "C002_000b-bmerge16",
    "c003_000-bmerge1_13_1",
    "c003_000-bmerge1_8",
    "Luigi1-migi-te1_2",
    "Luigi1-migi-te1_1",
    "c005_000-bmerge4",
    "c005_000-bmerge6",
    "c001_000-migi-te2_2",
    "c001_000-migi-te2_3",
    "C002_000b-bmerge14",
    "C002_000b-bmerge16",
} };
PpVecPair D_80111614_puddle_paddle = { { { -300.0f, 200.0f, 0.0f }, { 300.0f, 200.0f, 0.0f } } };
f64 D_80111630_puddle_paddle = 30.0; // passed to GMesCreate's varargs (the asm reads it as two words)
// end m1 pp3 .data
