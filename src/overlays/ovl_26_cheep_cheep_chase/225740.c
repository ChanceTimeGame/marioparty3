#include "common.h"

#include "overlays/minigame.h"
#include "mallocblock.h"

// m6 cx: Cheep Cheep Chase. The object system at func_8010D560_cheep_cheep_chase is Silly Screws' (ovl_37
// system.c, m255_*) with a 0x40-byte function context, eight groups, no sprites and m257-style animated models.
#define CX_FUNC_GRP_MAX 8
#define CX_FUNC_PRIO_MAX 10
#define CX_SPRITES_MAX 0
#define CX_ANIMMDL_MAX 40

typedef struct {
    /* 0x00 */ s8 s8[16];
    /* 0x10 */ s16 s16[8];
    /* 0x20 */ f32 f32[4];
} CxWork; // Size 0x30

typedef struct cx_func_context {
    /* 0x00 */ s8 set;
    /* 0x01 */ s8 tag;
    /* 0x04 */ void *data;
    /* 0x08 */ s16 param;
    /* 0x0A */ s8 prio;
    /* 0x0B */ s8 next;
    /* 0x0C */ CxWork work;
    /* 0x3C */ void (*func)(struct cx_func_context *);
} CxFuncContext; // Size 0x40

typedef struct {
    /* 0x00 */ CxFuncContext *funcCtx;
    /* 0x04 */ s8 maxFuncs;
    /* 0x05 */ u8 sort;
    /* 0x06 */ s8 order[CX_FUNC_PRIO_MAX];
} CxFuncGroup; // Size 0x10

typedef struct {
    /* 0x00 */ s8 state; // 0 unused, 1 hidden, 2 shown
    /* 0x01 */ u8 groupId;
    /* 0x02 */ u8 unk02;
    /* 0x04 */ u16 unk04;
} CxSpriteData; // Size 6

typedef struct {
    /* 0x00 */ s8 set;
    /* 0x04 */ s32 attr; // never written
    /* 0x08 */ s8 state; // -1 hidden, 0 waiting, 1 animating
    /* 0x0A */ s16 modelId;
    /* 0x0C */ f32 freq;
    /* 0x10 */ f32 animTimer;
    /* 0x14 */ f32 animStart;
} CxAnimModelData; // Size 0x18

typedef void (*CxFunc)(CxFuncContext *);

extern CxSpriteData *D_8010E390_cheep_cheep_chase;    // never allocated (no sprites)
extern CxAnimModelData *D_8010E394_cheep_cheep_chase; // [CX_ANIMMDL_MAX]
extern CxFuncGroup *D_8010E398_cheep_cheep_chase;     // [CX_FUNC_GRP_MAX]

void func_8010D560_cheep_cheep_chase(void);
void func_8010D62C_cheep_cheep_chase(CxFuncGroup *group, s16 maxFuncs);
s16 func_8010D6F4_cheep_cheep_chase(s8 groupId, s8 prio, s16 param, s8 tag, void *data, CxFunc func, u8 sort, u8 execFunc);
void func_8010D7F4_cheep_cheep_chase(s8 groupId, CxFuncContext *ctx);
void func_8010D85C_cheep_cheep_chase(s8 groupId);
void func_8010D8FC_cheep_cheep_chase(s8 groupId);
void func_8010D9E8_cheep_cheep_chase(CxFuncGroup *group);
s16 func_8010DA74_cheep_cheep_chase(s32 dir, s32 file, u16 arg2, s32 attr);
void func_8010DA84_cheep_cheep_chase(s16 spriteId, s32 posX, s32 posY);
void func_8010DB24_cheep_cheep_chase(s16 spriteId);
void func_8010DB80_cheep_cheep_chase(void);
s16 func_8010DB8C_cheep_cheep_chase(s32 dir, s32 file, f32 freq, s32 arg3);
s32 func_8010DC7C_cheep_cheep_chase(s16 animModelId, f32 posX, f32 posY, f32 posZ, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 animStart);
void func_8010DDF4_cheep_cheep_chase(void);
u8 func_8010DF48_cheep_cheep_chase(f32 *out, u8 *timer, f32 start, f32 end, f32 duration);
f32 func_8010DFC0_cheep_cheep_chase(f32 t, f32 p0, f32 p1, f32 p2);


INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801059A0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801059BC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105BBC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105DD0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105E18_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105E50_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105E74_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80105F50_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010619C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801061C8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010636C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106388_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E050_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E05C_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E06C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106484_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010665C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801067B0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106978_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106AA0_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E0C0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80106E80_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010732C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107440_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107698_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801076B4_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107760_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107BDC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80107E3C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801080C8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80108170_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E170_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801085FC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801088F8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010896C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80108AF4_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80108C98_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80108F78_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801090E0_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801091FC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801092B8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801093CC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80109444_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801094C0_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E1B8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80109750_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80109CAC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010A08C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010A57C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010A938_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010ACD8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010AD14_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010AF70_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B148_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B33C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B52C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B63C_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E258_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010B648_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010BB9C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010BEA4_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010C004_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010C440_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010C8EC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010C988_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010CAD4_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010CBBC_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D02C_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010D198_cheep_cheep_chase);

void func_8010D560_cheep_cheep_chase(void) {
    s8 maxFuncs[CX_FUNC_GRP_MAX] = { 4, 5, 4, 6, 12, 12, 12, 12 };
    s16 i;

    D_8010E394_cheep_cheep_chase = HuMemAllocTag(CX_ANIMMDL_MAX * sizeof(CxAnimModelData), 31000);
    memset(D_8010E394_cheep_cheep_chase, 0, CX_ANIMMDL_MAX * sizeof(CxAnimModelData));
    D_8010E398_cheep_cheep_chase = HuMemAllocTag(CX_FUNC_GRP_MAX * sizeof(CxFuncGroup), 31000);
    for (i = 0; i < CX_FUNC_GRP_MAX; i++) {
        func_8010D62C_cheep_cheep_chase(&D_8010E398_cheep_cheep_chase[i], maxFuncs[i]);
    }
}

void func_8010D62C_cheep_cheep_chase(CxFuncGroup *group, s16 maxFuncs) {
    s16 i;

    group->funcCtx = HuMemAllocTag(maxFuncs * sizeof(CxFuncContext), 31000);
    memset(group->funcCtx, 0, maxFuncs * sizeof(CxFuncContext));
    memset(group->order, -1, sizeof(group->order));
    for (i = 0; i < maxFuncs; i++) {
        group->funcCtx[i].next = -1;
    }
    group->sort = FALSE;
    group->maxFuncs = maxFuncs;
}

s16 func_8010D6F4_cheep_cheep_chase(s8 groupId, s8 prio, s16 param, s8 tag, void *data, CxFunc func, u8 sort, u8 execFunc) {
    CxFuncGroup *group = &D_8010E398_cheep_cheep_chase[groupId];
    CxFuncContext *ctx = group->funcCtx;
    s16 i = 0;
    s16 maxFuncs = group->maxFuncs;

    for (i = 0; i < maxFuncs; i++, ctx++) {
        if (!ctx->set) {
            ctx->set = TRUE;
            if (prio > CX_FUNC_PRIO_MAX - 1) {
                prio = CX_FUNC_PRIO_MAX - 1;
            }
            ctx->prio = prio;
            ctx->param = param;
            ctx->tag = tag;
            ctx->data = data;
            ctx->func = func;
            break;
        }
    }
    if (execFunc) {
        ctx->func(ctx);
    }
    if (sort) {
        func_8010D9E8_cheep_cheep_chase(group);
        group->sort = FALSE;
    } else {
        group->sort = TRUE;
    }
    return i;
}

void func_8010D7F4_cheep_cheep_chase(s8 groupId, CxFuncContext *ctx) {
    s8 next = ctx->next;

    memset(ctx, 0, sizeof(CxFuncContext));
    ctx->next = next;
    D_8010E398_cheep_cheep_chase[groupId].sort = TRUE;
}

void func_8010D85C_cheep_cheep_chase(s8 groupId) {
    CxFuncGroup *group = &D_8010E398_cheep_cheep_chase[groupId];
    s8 i = 0;

    memset(group->funcCtx, 0, group->maxFuncs * sizeof(CxFuncContext));
    memset(group->order, -1, sizeof(group->order));
    for (i = 0; i < group->maxFuncs; i++) {
        group->funcCtx[i].next = -1;
    }
}

void func_8010D8FC_cheep_cheep_chase(s8 groupId) {
    CxFuncGroup *group = &D_8010E398_cheep_cheep_chase[groupId];
    CxFuncContext *ctx = group->funcCtx;
    s8 i;

    if (group->sort) {
        func_8010D9E8_cheep_cheep_chase(group);
    }
    for (i = 0; i < CX_FUNC_PRIO_MAX; i++) {
        s8 funcId = group->order[i];

        while (funcId != -1) {
            group->funcCtx[funcId].func(&ctx[funcId]);
            funcId = group->funcCtx[funcId].next;
        }
    }
}

void func_8010D9E8_cheep_cheep_chase(CxFuncGroup *group) {
    CxFuncContext *currCtx = group->funcCtx;
    s8 prio;
    s8 i;

    for (i = 0; i < CX_FUNC_PRIO_MAX; i++) {
        group->order[i] = -1;
    }
    for (i = 0; i < group->maxFuncs; i++, currCtx++) {
        if (!currCtx->set) {
            continue;
        }
        prio = currCtx->prio;
        currCtx->next = group->order[prio];
        group->order[prio] = i;
    }
    group->sort = FALSE;
}

s16 func_8010DA74_cheep_cheep_chase(s32 dir, s32 file, u16 arg2, s32 attr) {
    CxSpriteData *sprite;
    HuSprite *temp_v0_2;
    s16 i;

    sprite = D_8010E390_cheep_cheep_chase;
    for (i = 0; i < CX_SPRITES_MAX; i++, sprite++) {
        if (sprite->state == 0) {
            sprite->unk02 = func_8000B838_main((dir << 16) | file);
            sprite->groupId = HuSprGrpCreate(1, 0);
            HuSprAttrReset(sprite->groupId, 0, -1);
            func_80055024_main(sprite->groupId, 0, sprite->unk02, 0);
            HuSprAttrSet(sprite->groupId, 0, attr);
            func_800550F4_main(sprite->groupId, 0, arg2);
            HuSprPriSet(sprite->groupId, 0, 0xFFF0);
            func_80054FF8_main(sprite->groupId, 0, 0);
            func_800550B4_main(sprite->groupId, 0, 1.0f);
            HuSprScaleSet(sprite->groupId, 0, 1.0f, 1.0f);
            func_80054904_main(sprite->groupId, 0, 100, 100);
            temp_v0_2 = HuSprGet(sprite->groupId, 0);
            if (arg2 == 0) {
                sprite->unk04 = 99;
            } else {
                sprite->unk04 = temp_v0_2->unk_84->unk10;
            }
            sprite->state = 1;
            break;
        }
    }
    return i;
}

void func_8010DA84_cheep_cheep_chase(s16 spriteId, s32 posX, s32 posY) {
    CxSpriteData *sprite = &D_8010E390_cheep_cheep_chase[spriteId];

    if (sprite->state != 0) {
        func_80054FF8_main(sprite->groupId, 0, 0);
        HuSprAttrReset(sprite->groupId, 0, 0x8000);
        func_80054904_main(sprite->groupId, 0, posX, posY);
        sprite->state = 2;
    }
}

void func_8010DB24_cheep_cheep_chase(s16 spriteId) {
    CxSpriteData *sprite = &D_8010E390_cheep_cheep_chase[spriteId];

    if (sprite->state != 0) {
        HuSprAttrSet(sprite->groupId, 0, 0x8000);
        sprite->state = 1;
    }
}

void func_8010DB80_cheep_cheep_chase(void) {
    CxSpriteData *sprite;
    s16 i;

    sprite = D_8010E390_cheep_cheep_chase;
    for (i = 0; i < CX_SPRITES_MAX; i++, sprite++) {
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

s16 func_8010DB8C_cheep_cheep_chase(s32 dir, s32 file, f32 freq, s32 arg3) {
    CxAnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_8010E394_cheep_cheep_chase;
    for (i = 0; i < CX_ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set) {
            animModel->modelId = func_8000B108_main((dir << 16) | file, arg3);
            func_8001C258_main(animModel->modelId, 4, 4);
            hmfModel = &HmfModelData[animModel->modelId];
            hmfModel->unk40 = 0.0f;
            hmfModel->unk44 = 0.0f;
            if (hmfModel->hmf->unk98 != NULL) {
                hmfModel->hmf->unk98->unk08 = 0;
            }
            animModel->freq = freq;
            animModel->state = -1;
            animModel->set = TRUE;
            break;
        }
    }
    return i;
}

s32 func_8010DC7C_cheep_cheep_chase(s16 animModelId, f32 posX, f32 posY, f32 posZ, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 animStart) {
    CxAnimModelData *animModel;
    HmfModel *hmfModel;

    if (animModelId >= CX_ANIMMDL_MAX) {
        return FALSE;
    }
    if (!D_8010E394_cheep_cheep_chase[animModelId].set) {
        return FALSE;
    }
    animModel = &D_8010E394_cheep_cheep_chase[animModelId];
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

void func_8010DDF4_cheep_cheep_chase(void) {
    CxAnimModelData *animModel;
    HmfModel *hmfModel;
    s16 i;

    animModel = D_8010E394_cheep_cheep_chase;
    for (i = 0; i < CX_ANIMMDL_MAX; i++, animModel++) {
        if (!animModel->set || animModel->state == -1) {
            continue;
        }
        hmfModel = &HmfModelData[animModel->modelId];
        switch (animModel->state) {
            default:
                if (D_800CCF58_main[hmfModel->unk02].unk02 <= hmfModel->unk40) {
                    func_8001C258_main(animModel->modelId, 4, 4);
                    hmfModel->unk40 = 0.0f;
                    hmfModel->unk44 = 0.0f;
                    if (hmfModel->hmf->unk98 != NULL) {
                        hmfModel->hmf->unk98->unk08 = 0;
                    }
                    animModel->state = -1;
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

u8 func_8010DF48_cheep_cheep_chase(f32 *out, u8 *timer, f32 start, f32 end, f32 duration) {
    f32 t = *timer / duration;

    *out = start + (end - start) * t;
    if (++(*timer) > duration) {
        *timer = 0;
        *out = end;
        return TRUE;
    }
    return FALSE;
}

f32 func_8010DFC0_cheep_cheep_chase(f32 t, f32 p0, f32 p1, f32 p2) {
    f32 u = 1.0f - t;
    f32 ret;

    ret = u * u * p0;
    ret += 2.0f * u * t * p1;
    ret += u * u * p2;
    return ret;
}

