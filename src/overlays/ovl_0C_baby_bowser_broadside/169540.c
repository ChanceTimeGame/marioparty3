#include "common.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// m1 bb2: object system shared with ovl_39 tick_tock_hop system.c (m257_*) and ovl_36 motor_rooter (m254_*),
// with larger pools, a tag per animated model and billboard, and a billboard colour.
#define BB_FUNC_GRP_MAX 7
#define BB_SPRITES_MAX 14
#define BB_ANIMMDL_MAX 16
#define BB_BILLS_MAX 8

typedef struct {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 a;
} BbRGBA;

typedef struct {
    /* 0x00 */ s8 s8[16];
    /* 0x10 */ s16 s16[8];
    /* 0x20 */ f32 f32[4];
} BbWork; // Size 0x30

typedef struct {
    /* 0x00 */ omObjData *object;
    /* 0x04 */ s16 *modelIds;
    /* 0x08 */ s16 maxModels;
} BbFuncGroupContext; // Size 0xC

typedef struct bb_func_context {
    /* 0x00 */ s8 set;
    /* 0x02 */ s16 id;
    /* 0x04 */ s8 state;
    /* 0x05 */ s8 tag;
    /* 0x08 */ s32 prio;
    /* 0x0C */ BbWork work;
    /* 0x3C */ void *data;
    /* 0x40 */ void (*func)(BbFuncGroupContext *, struct bb_func_context *);
} BbFuncContext; // Size 0x44

typedef struct {
    /* 0x00 */ u32 prio;
    /* 0x04 */ s16 next;
    /* 0x06 */ s16 prev;
    /* 0x08 */ s16 id;
} BbFuncOrder; // Size 0xC

typedef struct {
    /* 0x00 */ BbFuncGroupContext *groupCtx;
    /* 0x04 */ BbFuncContext *funcCtx;
    /* 0x08 */ s16 maxFuncs;
    /* 0x0C */ BbFuncOrder *order;
    /* 0x10 */ s8 sort;
} BbFuncGroup; // Size 0x14

typedef struct {
    /* 0x00 */ s8 state; // 0 unused, 1 hidden, 2 shown
    /* 0x01 */ u8 groupId;
    /* 0x02 */ u8 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ s16 unk06;
} BbSpriteData; // Size 8

typedef struct {
    /* 0x00 */ s8 set;
    /* 0x04 */ s32 attr;
    /* 0x08 */ s8 state; // -1 hidden, 0 waiting, 1 animating
    /* 0x0A */ s16 tag;
    /* 0x0C */ s16 modelId;
    /* 0x10 */ f32 freq;
    /* 0x14 */ f32 animTimer;
    /* 0x18 */ f32 animStart;
} BbAnimModelData; // Size 0x1C

typedef struct {
    /* 0x00 */ s8 set;
    /* 0x04 */ s32 attr; // 1 animated sprite model, 2 animate, 4 loop, 8 hidden, 0x10 position by reference
    /* 0x08 */ s16 tag;
    /* 0x0A */ u8 spriteId;
    /* 0x0C */ s16 modelId;
    /* 0x0E */ s16 duration;
    /* 0x10 */ s16 timer;
    /* 0x14 */ f32 *posX;
    /* 0x18 */ f32 *posY;
    /* 0x1C */ f32 *posZ;
    /* 0x20 */ BbRGBA color;
} BbBillboardData; // Size 0x24

void func_80017D24_main(f32 *, f32, f32, f32);
extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;

extern Gfx D_8010FE80_baby_bowser_broadside[];
extern BbRGBA D_8010FFE0_baby_bowser_broadside;
extern BbBillboardData *D_80110010_baby_bowser_broadside;
extern BbFuncGroup *D_80110014_baby_bowser_broadside;
extern BbSpriteData *D_80110018_baby_bowser_broadside;
extern BbAnimModelData *D_8011001C_baby_bowser_broadside;

void func_8010A3C8_baby_bowser_broadside(BbFuncGroup *group);
void func_8010A7CC_baby_bowser_broadside(s16 spriteId);
s16 func_8010B54C_baby_bowser_broadside(HuSprite_Unk84_Struct *arg0, f32 arg1);
s16 func_8010BCBC_baby_bowser_broadside(HuSprite_Unk84_Struct *arg0, f32 arg1);
s16 func_8010C8D4_baby_bowser_broadside(HuSprite_Unk84_Struct *arg0, BbRGBA *arg1);
void func_8010D590_baby_bowser_broadside(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, BbRGBA *arg3);
s16 func_8010D6C4_baby_bowser_broadside(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8010F878_baby_bowser_broadside(f32 *out);

void func_80109ED0_baby_bowser_broadside(void) {
    D_80110018_baby_bowser_broadside = HuMemAllocTag(BB_SPRITES_MAX * sizeof(BbSpriteData), 31000);
    memset(D_80110018_baby_bowser_broadside, 0, BB_SPRITES_MAX * sizeof(BbSpriteData));
    D_8011001C_baby_bowser_broadside = HuMemAllocTag(BB_ANIMMDL_MAX * sizeof(BbAnimModelData), 31000);
    memset(D_8011001C_baby_bowser_broadside, 0, BB_ANIMMDL_MAX * sizeof(BbAnimModelData));
    D_80110010_baby_bowser_broadside = HuMemAllocTag(BB_BILLS_MAX * sizeof(BbBillboardData), 31000);
    memset(D_80110010_baby_bowser_broadside, 0, BB_BILLS_MAX * sizeof(BbBillboardData));
    D_80110014_baby_bowser_broadside = HuMemAllocTag(BB_FUNC_GRP_MAX * sizeof(BbFuncGroup), 31000);
}

BbFuncGroup *func_80109F64_baby_bowser_broadside(omObjData *object, s8 groupId, s16 maxModels, s16 maxFuncs) {
    BbFuncGroup *group;

    if (groupId >= BB_FUNC_GRP_MAX) {
        return NULL;
    }
    group = &D_80110014_baby_bowser_broadside[groupId];
    if (maxFuncs != 0) {
        group->funcCtx = HuMemAllocTag(maxFuncs * sizeof(BbFuncContext), 31000);
        memset(group->funcCtx, 0, maxFuncs * sizeof(BbFuncContext));
        group->order = HuMemAllocTag((maxFuncs + 1) * sizeof(BbFuncOrder), 31000);
    }
    group->maxFuncs = maxFuncs;
    group->groupCtx = HuMemAllocTag(sizeof(BbFuncGroupContext), 31000);
    if (maxModels != 0) {
        group->groupCtx->modelIds = HuMemAllocTag(maxModels * sizeof(s16), 31000);
        memset(group->groupCtx->modelIds, 0, maxModels * sizeof(s16));
    }
    group->groupCtx->maxModels = maxModels;
    group->sort = TRUE;
    group->groupCtx->object = object;
    return group;
}

s16 func_8010A0B4_baby_bowser_broadside(s8 groupId, s32 prio, void *data, void (*func)(BbFuncGroupContext *, BbFuncContext *), s8 tag) {
    BbFuncGroup *group = &D_80110014_baby_bowser_broadside[groupId];
    BbFuncContext *ctx = group->funcCtx;
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

void func_8010A158_baby_bowser_broadside(s8 groupId, BbFuncContext *ctx) {
    memset(ctx, 0, sizeof(BbFuncContext));
    D_80110014_baby_bowser_broadside[groupId].sort = TRUE;
}

void func_8010A1B0_baby_bowser_broadside(s8 groupId, s8 tag) {
    BbFuncGroup *group = &D_80110014_baby_bowser_broadside[groupId];
    BbFuncContext *ctx;
    s16 i;

    ctx = group->funcCtx;
    for (i = 0; i < group->maxFuncs; i++, ctx++) {
        if (ctx->tag == tag) {
            func_8010A158_baby_bowser_broadside(groupId, ctx);
        }
    }
}

void func_8010A264_baby_bowser_broadside(s8 groupId) {
    BbFuncGroup *group = &D_80110014_baby_bowser_broadside[groupId];

    memset(group->funcCtx, 0, group->maxFuncs * sizeof(BbFuncContext));
    group->sort = TRUE;
}

void func_8010A2C4_baby_bowser_broadside(s8 groupId) {
    BbFuncGroup *group = &D_80110014_baby_bowser_broadside[groupId];
    BbFuncContext *ctx;
    s8 orderId;

    if (group->sort) {
        func_8010A3C8_baby_bowser_broadside(group);
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

void func_8010A3C8_baby_bowser_broadside(BbFuncGroup *group) {
    BbFuncOrder *order = group->order;
    BbFuncContext *currCtx = group->funcCtx;
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

s16 func_8010A598_baby_bowser_broadside(u16 prio, s32 dir, s32 file, u16 arg3, s32 attr) {
    BbSpriteData *sprite;
    HuSprite *temp_v0_2;
    s16 i;

    sprite = D_80110018_baby_bowser_broadside;
    for (i = 0; i < BB_SPRITES_MAX; i++, sprite++) {
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
            func_8010A7CC_baby_bowser_broadside(i);
            break;
        }
    }
    return i;
}

void func_8010A738_baby_bowser_broadside(s16 spriteId, s32 posX, s32 posY) {
    BbSpriteData *sprite = &D_80110018_baby_bowser_broadside[spriteId];

    if (sprite->state != 0) {
        func_80054FF8_main(sprite->groupId, 0, 0);
        HuSprAttrReset(sprite->groupId, 0, 0x8000);
        func_80054904_main(sprite->groupId, 0, posX, posY);
        sprite->state = 2;
    }
}

void func_8010A7CC_baby_bowser_broadside(s16 spriteId) {
    BbSpriteData *sprite = &D_80110018_baby_bowser_broadside[spriteId];

    if (sprite->state != 0) {
        HuSprAttrSet(sprite->groupId, 0, 0x8000);
        sprite->state = 1;
    }
}

void func_8010A81C_baby_bowser_broadside(void) {
    BbSpriteData *sprite;
    s16 i;

    sprite = D_80110018_baby_bowser_broadside;
    for (i = 0; i < BB_SPRITES_MAX; i++, sprite++) {
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

s16 func_8010A8C4_baby_bowser_broadside(s32 dir, s32 file, f32 freq, s16 tag, s32 attr, s32 arg5) {
    BbAnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_8011001C_baby_bowser_broadside;
    for (i = 0; i < BB_ANIMMDL_MAX; i++, animModel++) {
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

s16 func_8010A9D4_baby_bowser_broadside(s16 linkModelId, f32 freq, s16 tag, s32 attr) {
    BbAnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_8011001C_baby_bowser_broadside;
    for (i = 0; i < BB_ANIMMDL_MAX; i++, animModel++) {
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

s16 func_8010AADC_baby_bowser_broadside(s16 tag) {
    BbAnimModelData *animModel;
    s16 i;

    animModel = D_8011001C_baby_bowser_broadside;
    for (i = 0; i < BB_ANIMMDL_MAX; i++, animModel++) {
        if (animModel->set && animModel->tag == tag && (HmfModelData[animModel->modelId].unk18 & 4)
            && animModel->state == -1) {
            break;
        }
    }
    if (i == BB_ANIMMDL_MAX) {
        return -1;
    }
    return i;
}

s32 func_8010AB80_baby_bowser_broadside(s16 animModelId, f32 posX, f32 posY, f32 posZ, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 animStart) {
    BbAnimModelData *animModel;
    HmfModel *hmfModel;

    if (animModelId >= BB_ANIMMDL_MAX) {
        return FALSE;
    }
    if (!D_8011001C_baby_bowser_broadside[animModelId].set) {
        return FALSE;
    }
    animModel = &D_8011001C_baby_bowser_broadside[animModelId];
    hmfModel = &HmfModelData[animModel->modelId];
    if ((hmfModel->unk18 & 4) && animModel->state == -1) {
        Hu3DModelPosSet(animModel->modelId, posX, posY, posZ);
        Hu3DModelRotSet(animModel->modelId, rotX, rotY, rotZ);
        Hu3DModelScaleSet(animModel->modelId, scale, scale, scale);
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

void func_8010ACF8_baby_bowser_broadside(void) {
    BbAnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_8011001C_baby_bowser_broadside;
    for (i = 0; i < BB_ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set || animModel->state == -1) {
            continue;
        }
        hmfModel = &HmfModelData[animModel->modelId];
        switch (animModel->state) {
            default:
                if (D_800CCF58_main[hmfModel->unk02].unk02 <= hmfModel->unk40) {
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

s16 func_8010AE60_baby_bowser_broadside(s32 dir, s32 file, s16 tag, s32 attr) {
    BbBillboardData *bill;
    BbRGBA color;
    s16 spriteId;
    s16 i;

    bill = D_80110010_baby_bowser_broadside;
    color = D_8010FFE0_baby_bowser_broadside;
    for (i = 0; i < BB_BILLS_MAX; i++, bill++) {
        if (!bill->set) {
            bill->spriteId = spriteId = func_8000B838_main((dir << 16) | file);
            if (attr & 1) {
                bill->modelId = func_8010C8D4_baby_bowser_broadside(func_80055194_main(spriteId), &color);
            } else {
                bill->modelId = func_8010B54C_baby_bowser_broadside(func_80055194_main(spriteId), 1.0f);
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
            bill->set = TRUE;
            break;
        }
    }
    return i;
}

s16 func_8010AFF4_baby_bowser_broadside(s16 tag) {
    BbBillboardData *bill;
    s16 i;

    bill = D_80110010_baby_bowser_broadside;
    for (i = 0; i < BB_BILLS_MAX; i++, bill++) {
        if (bill->set && bill->tag == tag && (HmfModelData[bill->modelId].unk18 & 4) && (bill->attr & 8)) {
            break;
        }
    }
    if (i == BB_BILLS_MAX) {
        return -1;
    }
    return i;
}

void func_8010B098_baby_bowser_broadside(s16 billId, f32 posX, f32 posY, f32 posZ, BbRGBA *color) {
    if (billId < BB_BILLS_MAX) {
        HmfModel *model = &HmfModelData[D_80110010_baby_bowser_broadside[billId].modelId];

        model->pos.x = posX;
        model->pos.y = posY;
        model->pos.z = posZ;
        func_8001C258_main(D_80110010_baby_bowser_broadside[billId].modelId, 4, 0);
        D_80110010_baby_bowser_broadside[billId].color.r = color->r;
        D_80110010_baby_bowser_broadside[billId].color.g = color->g;
        D_80110010_baby_bowser_broadside[billId].color.b = color->b;
        D_80110010_baby_bowser_broadside[billId].color.a = color->a;
        D_80110010_baby_bowser_broadside[billId].attr &= ~(8 | 0x10);
    }
}

void func_8010B198_baby_bowser_broadside(s16 billId, f32 *posX, f32 *posY, f32 *posZ) {
    if (billId < BB_BILLS_MAX) {
        HmfModel *model = &HmfModelData[D_80110010_baby_bowser_broadside[billId].modelId];

        if (posX != NULL) {
            D_80110010_baby_bowser_broadside[billId].posX = posX;
        } else {
            D_80110010_baby_bowser_broadside[billId].posX = &model->pos.x;
        }
        if (posY != NULL) {
            D_80110010_baby_bowser_broadside[billId].posY = posY;
        } else {
            D_80110010_baby_bowser_broadside[billId].posY = &model->pos.y;
        }
        if (posZ != NULL) {
            D_80110010_baby_bowser_broadside[billId].posZ = posZ;
        } else {
            D_80110010_baby_bowser_broadside[billId].posZ = &model->pos.z;
        }
        func_8001C258_main(D_80110010_baby_bowser_broadside[billId].modelId, 4, 0);
        D_80110010_baby_bowser_broadside[billId].attr &= ~(8 | 0x10);
        D_80110010_baby_bowser_broadside[billId].attr |= 0x10;
    }
}

BbBillboardData *func_8010B328_baby_bowser_broadside(s16 billId) {
    if (billId >= BB_BILLS_MAX) {
        return NULL;
    }
    return &D_80110010_baby_bowser_broadside[billId];
}

HmfModel *func_8010B360_baby_bowser_broadside(s16 billId) {
    if (billId >= BB_BILLS_MAX) {
        return NULL;
    }
    return &HmfModelData[D_80110010_baby_bowser_broadside[billId].modelId];
}

void func_8010B3B4_baby_bowser_broadside(void) {
    BbBillboardData *bill;
    HmfModel *model;
    s16 i;

    bill = D_80110010_baby_bowser_broadside;
    for (i = 0; i < BB_BILLS_MAX; i++, bill++) {
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
        func_8010F878_baby_bowser_broadside(model->mtx);
        func_80017D24_main(model->mtx, 0.0f, 0.0f, CRot.z);
        if (bill->attr & 1) {
            if (bill->attr & 2) {
                func_8010D590_baby_bowser_broadside(bill->modelId, func_80055194_main(bill->spriteId), bill->timer, &bill->color);
                bill->timer++;
                if (bill->timer >= bill->duration) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B54C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010BCBC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010C8D4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010D4C0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010D590_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010D6C4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DAE8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DB38_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DC88_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DDDC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DE70_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E018_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E0B0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E348_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E538_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E710_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E9FC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010ED1C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010EDC0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F004_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F060_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F0D8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F144_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F250_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F3C4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F5C8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F6F8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F878_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F900_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F958_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F9C0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010FA28_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010FADC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010FB74_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010FC2C_baby_bowser_broadside);
