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

/* A team (D_80111650_puddle_paddle[2]) */
typedef struct PpTeam {
    /* 0x00 */ char unk00[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ char unk1C[4];
    /* 0x20 */ u8 count;
    /* 0x22 */ s16 member[2]; /* player indices */
    /* 0x26 */ s16 digit[2]; /* score digit sprites */
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ s16 leader; /* the member who steers: a human, or the stronger CPU when both are CPUs */
    /* 0x2E */ char unk2E[0x36];
} PpTeam; /* size 0x64 */

/* A player (D_80111654_puddle_paddle[4]) */
typedef struct PpPlayer {
    /* 0x00 */ s16 no;
    /* 0x02 */ s16 chr;
    /* 0x04 */ s32 unk04; /* 2 turn left, 4 turn right (CPU steering), 0x10 */
    /* 0x08 */ char unk08[6];
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s8 slot; /* place in the team */
    /* 0x11 */ char unk11[0x37];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ s16 team;
    /* 0x52 */ char unk52[4];
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
s16 func_8010EFEC_puddle_paddle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109804_puddle_paddle);

void func_80109814_puddle_paddle(UnkPuddlePaddle *arg0, s16 arg1) {
    arg0->unk_0E = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010981C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109BD4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010A224_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010A398_puddle_paddle);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010D5E4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010E1FC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010EDE8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010EEB8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010EFEC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F410_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F42C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F43C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F44C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F4DC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F4E8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F580_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F80C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F9FC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010FBD4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010FEC0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801101E0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110284_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801104C8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110524_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8011059C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110608_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110714_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110888_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110A8C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110BBC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110D3C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110DC4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110E1C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110E84_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110EEC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110FA0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80111038_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801110F0_puddle_paddle);
