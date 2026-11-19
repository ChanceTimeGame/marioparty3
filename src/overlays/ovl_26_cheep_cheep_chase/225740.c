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
    /* 0x01 */ s8 state; // initial value from SetFunc
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
s16 func_8010D6F4_cheep_cheep_chase(s8 groupId, s8 prio, s16 param, s8 state, void *data, CxFunc func, u8 sort, u8 execFunc);
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


typedef struct {
    /* 0x00 */ s16 model;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
} CxStageModel; // Size 0x10

typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ u8 unk4; // index into CxGame::unkC
    /* 0x05 */ u8 unk5;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC; // phase, degrees
} CxUnk4Entry; // Size 0x10

/* The minigame state (D_8010E360_cheep_cheep_chase) */
typedef struct {
    /* 0x00 */ CxStageModel *models; // [6]
    /* 0x04 */ CxUnk4Entry *unk4;    // [8]
    /* 0x08 */ u8 *unk8;             // [7]
    /* 0x0C */ u8 *unkC;             // [7]
    /* 0x10 */ omObjData *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
} CxGame; // Size 0x34

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x04 */ f32 unk04; // speed bonus
    /* 0x08 */ s8 unk08; // jump/dodge request
    /* 0x09 */ char unk09[7];
    /* 0x10 */ s8 updateMotion;
    /* 0x12 */ s16 motion;
    /* 0x14 */ f32 unk14; // swim speed
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ char unk1E[2];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[4];
} CxPlayer; // Size 0x28

typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ char unk02[6];
} CxUnk368; // Size 8

extern CxGame *D_8010E360_cheep_cheep_chase;
extern CxPlayer *D_8010E364_cheep_cheep_chase; // [4]
extern CxUnk368 *D_8010E368_cheep_cheep_chase;
extern f32 D_8010E370_cheep_cheep_chase[4];

extern u8 D_8010E010_cheep_cheep_chase;
extern f32 D_8010E014_cheep_cheep_chase;
extern f32 D_8010E018_cheep_cheep_chase;
extern s16 D_8010E01C_cheep_cheep_chase;
extern s16 D_8010E01E_cheep_cheep_chase;
extern s16 D_8010E020_cheep_cheep_chase;
extern s16 D_8010E022_cheep_cheep_chase;
extern s16 D_8010E024_cheep_cheep_chase;
extern s16 D_8010E026_cheep_cheep_chase;
extern s32 D_8010E028_cheep_cheep_chase[8];
extern s16 D_8010E380_cheep_cheep_chase;

extern u8 D_800D6A90_main;
extern s32 D_800A178C_main[][6];

extern const s16 D_8010E050_cheep_cheep_chase[];
extern const s16 D_8010E05C_cheep_cheep_chase[];
extern const s16 D_8010E06C_cheep_cheep_chase[];

#include "game/pause.h"

// C1F0
void func_8000B5F0_main(u8 arg0);
s32 func_8000B638_main(void);
// 14EA0
void func_800142A0_main(s32);
// 20A20
void Hu3DAnimInit(s32);
void func_8001E65C_main(s16 mdl, f32 u, f32 v, s32 w, s32 h);

void func_801059A0_cheep_cheep_chase(void);
void func_801059BC_cheep_cheep_chase(void);
void func_80105BBC_cheep_cheep_chase(void);
void func_80105DD0_cheep_cheep_chase(omObjData *object);
void func_80105E18_cheep_cheep_chase(omObjData *object);
void func_80105E50_cheep_cheep_chase(omObjData *object);
void func_80105E74_cheep_cheep_chase(void);
void func_80105F50_cheep_cheep_chase(omObjData *object);
void func_8010619C_cheep_cheep_chase(omObjData *object);
void func_801061C8_cheep_cheep_chase(omObjData *object);
void func_8010636C_cheep_cheep_chase(omObjData *object);
void func_80106388_cheep_cheep_chase(omObjData *object);
void func_80106484_cheep_cheep_chase(omObjData *object);
void func_8010665C_cheep_cheep_chase(omObjData *object);
void func_801067B0_cheep_cheep_chase(omObjData *object);
void func_80106978_cheep_cheep_chase(omObjData *object);
void func_80106AA0_cheep_cheep_chase(omObjData *object);
void func_80106E80_cheep_cheep_chase(omObjData *object);
void func_80107440_cheep_cheep_chase(omObjData *object);
void func_8010732C_cheep_cheep_chase(omObjData *object);
void func_80107698_cheep_cheep_chase(omObjData *object);
void func_801076B4_cheep_cheep_chase(CxFuncContext *ctx);
void func_80107E3C_cheep_cheep_chase(CxFuncContext *ctx);
void func_801080C8_cheep_cheep_chase(CxFuncContext *ctx);
void func_80108170_cheep_cheep_chase(CxFuncContext *ctx);
void func_801085FC_cheep_cheep_chase(CxFuncContext *ctx);
void func_801088F8_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010896C_cheep_cheep_chase(CxFuncContext *ctx);
void func_80108AF4_cheep_cheep_chase(CxFuncContext *ctx);
void func_80108C98_cheep_cheep_chase(CxFuncContext *ctx);
void func_80108F78_cheep_cheep_chase(CxFuncContext *ctx);
void func_801090E0_cheep_cheep_chase(CxFuncContext *ctx);
void func_801092B8_cheep_cheep_chase(CxFuncContext *ctx);
void func_80109750_cheep_cheep_chase(CxFuncContext *ctx);
void func_80109CAC_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010A08C_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010A57C_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010A938_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010ACD8_cheep_cheep_chase(u8 player);
void func_8010AD14_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010AF70_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010B148_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010B33C_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010B52C_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010B63C_cheep_cheep_chase(CxPlayer *player, s32 motion, s32 updateMotion);
void func_8010B648_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010BB9C_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010C440_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010C988_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010CAD4_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010CBBC_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010D02C_cheep_cheep_chase(CxFuncContext *ctx);
void func_801091FC_cheep_cheep_chase(u8 arg0);
void func_801093CC_cheep_cheep_chase(s16 model);
void func_80109444_cheep_cheep_chase(s16 model);
void func_801094C0_cheep_cheep_chase(omObjData *object, s16 arg1);


void func_801059A0_cheep_cheep_chase(void) {
    func_801059BC_cheep_cheep_chase();
}

void func_801059BC_cheep_cheep_chase(void) {
    u8 camIndex;

    Hu3DAnimInit(50);
    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 4000.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_8010D560_cheep_cheep_chase();
    func_80105BBC_cheep_cheep_chase();
    func_8010D6F4_cheep_cheep_chase(0, 0, -1, 0, NULL, func_801076B4_cheep_cheep_chase, FALSE, FALSE);
    omAddObj(100, 0, 0, -1, func_80105F50_cheep_cheep_chase);
    omAddObj(1000, 0, 0, -1, func_80105DD0_cheep_cheep_chase);
    func_80045010_main(D_8010E050_cheep_cheep_chase, 1);
    func_80045010_main(D_8010E05C_cheep_cheep_chase, 1);
    func_80045010_main(D_8010E06C_cheep_cheep_chase, 1);
}

void func_80105BBC_cheep_cheep_chase(void) {
    s16 i, j;

    D_8010E360_cheep_cheep_chase = HuMemAllocTag(sizeof(CxGame), 31000);
    memset(D_8010E360_cheep_cheep_chase, 0, sizeof(CxGame));
    D_8010E360_cheep_cheep_chase->models = HuMemAllocTag(6 * sizeof(CxStageModel), 31000);
    memset(D_8010E360_cheep_cheep_chase->models, 0, 6 * sizeof(CxStageModel));
    D_8010E360_cheep_cheep_chase->unk4 = HuMemAllocTag(8 * sizeof(CxUnk4Entry), 31000);
    memset(D_8010E360_cheep_cheep_chase->unk4, 0, 8 * sizeof(CxUnk4Entry));
    D_8010E360_cheep_cheep_chase->unk8 = HuMemAllocTag(7, 31000);
    memset(D_8010E360_cheep_cheep_chase->unk8, 0, 7);
    D_8010E360_cheep_cheep_chase->unkC = HuMemAllocTag(7, 31000);
    memset(D_8010E360_cheep_cheep_chase->unkC, 0, 7);
    D_8010E364_cheep_cheep_chase = HuMemAllocTag(4 * sizeof(CxPlayer), 31000);
    memset(D_8010E364_cheep_cheep_chase, 0, 4 * sizeof(CxPlayer));
    D_8010E368_cheep_cheep_chase = HuMemAllocTag(sizeof(CxUnk368), 31000);
    memset(D_8010E368_cheep_cheep_chase, 0, sizeof(CxUnk368));
    for (i = 0; i < 4; i++) {
        D_8010E370_cheep_cheep_chase[i] = rand16() % 4;
        for (j = 0; j < i; j++) {
            if (D_8010E370_cheep_cheep_chase[j] == D_8010E370_cheep_cheep_chase[i]) {
                i--;
                break;
            }
        }
    }
}

void func_80105DD0_cheep_cheep_chase(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        object->func = func_80105E18_cheep_cheep_chase;
    }
}

void func_80105E18_cheep_cheep_chase(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_80105E50_cheep_cheep_chase;
    }
}

void func_80105E50_cheep_cheep_chase(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80105E74_cheep_cheep_chase(void) {
    if (CRot.x > 360.0f) {
        CRot.x -= 360.0f;
    } else if (CRot.x < 0.0f) {
        CRot.x += 360.0f;
    }
    if (CRot.y > 360.0f) {
        CRot.y -= 360.0f;
    } else if (CRot.y < 0.0f) {
        CRot.y += 360.0f;
    }
    func_8010D8FC_cheep_cheep_chase(0);
}

void func_80105F50_cheep_cheep_chase(omObjData *object) {
    s32 mdlAttr = 0x499;
    u8 i;

    omAddObj(10, 7, 0, -1, func_801061C8_cheep_cheep_chase);
    omSetStatBit(omAddObj(10, 4, 0, -1, func_80106388_cheep_cheep_chase), 0xA0);
    omAddObj(10, 3, 0, -1, func_8010665C_cheep_cheep_chase);
    omAddObj(10, 8, 0, -1, func_80106978_cheep_cheep_chase);
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(200, 10, 0x2C, -1, func_80106E80_cheep_cheep_chase);
    }
    omSetStatBit(omAddObj(300, 2, 2, -1, func_80107440_cheep_cheep_chase), 0xA0);
    for (i = 0; i < 18; i++) {
        func_8010DB8C_cheep_cheep_chase(0x47, 5, 1.0f, mdlAttr);
    }
    for (i = 0; i < 4; i++) {
        func_8010DB8C_cheep_cheep_chase(1, 0x13, 2.0f, mdlAttr);
    }
    for (i = 0; i < 8; i++) {
        func_8010DB8C_cheep_cheep_chase(0x47, 7, 1.0f, mdlAttr);
    }
    for (i = 0; i < 8; i++) {
        func_8010DB8C_cheep_cheep_chase(0x47, 6, 1.0f, mdlAttr);
    }
    func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_80108170_cheep_cheep_chase, TRUE, FALSE);
    WipeCreateIn(0xFF, 16);
    object->func = func_8010619C_cheep_cheep_chase;
}

void func_8010619C_cheep_cheep_chase(omObjData *object) {
    func_8010D8FC_cheep_cheep_chase(1);
    func_8010DDF4_cheep_cheep_chase();
    func_80105E74_cheep_cheep_chase();
}

void func_801061C8_cheep_cheep_chase(omObjData *object) {
    s16 i;

    object->model[0] = D_8010E360_cheep_cheep_chase->models[0].model = func_8000B108_main(0x470000, 0x9D);
    object->model[1] = D_8010E360_cheep_cheep_chase->models[1].model = func_8000B108_main(0x470002, 0x9D);
    object->model[2] = D_8010E360_cheep_cheep_chase->models[2].model = func_8000B108_main(0x470001, 0x9D);
    for (i = 0; i < 3; i++) {
        object->model[i + 3] = D_8010E360_cheep_cheep_chase->models[i + 3].model = Hu3DModelLink(object->model[2]);
    }
    object->model[6] = func_8000B108_main(0x470008, 0x9D);
    func_8010D6F4_cheep_cheep_chase(2, 0, object->model[6], 0, NULL, func_80108C98_cheep_cheep_chase, FALSE, TRUE);
    func_8010D6F4_cheep_cheep_chase(2, 1, -1, 0, NULL, func_80108F78_cheep_cheep_chase, FALSE, TRUE);
    func_8010D6F4_cheep_cheep_chase(2, 0, -1, 1, NULL, func_801090E0_cheep_cheep_chase, TRUE, FALSE);
    object->func = func_8010636C_cheep_cheep_chase;
}

void func_8010636C_cheep_cheep_chase(omObjData *object) {
    func_8010D8FC_cheep_cheep_chase(2);
}

void func_80106388_cheep_cheep_chase(omObjData *object) {
    u16 i;

    object->model[0] = func_8000B108_main(0x470003, 0x2009D);
    for (i = 1; i < 4; i++) {
        object->model[i] = Hu3DModelLink(object->model[0]);
    }
    func_8001C954_main(object->model[0]);
    object->trans.x = 0;
    object->trans.z = -250.0f;
    object->trans.y = 110.0f;
    D_8010E360_cheep_cheep_chase->unk14++;
    for (i = 1; i < 4; i++) {
        func_801093CC_cheep_cheep_chase(object->model[i]);
    }
    object->func = func_80106484_cheep_cheep_chase;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E050_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E05C_cheep_cheep_chase);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E06C_cheep_cheep_chase);

void func_80106484_cheep_cheep_chase(omObjData *object) {
    HmfModel *model;
    s16 i;

    func_8001E65C_main(object->model[0], 0, D_8010E014_cheep_cheep_chase, 0x40, 0x40);
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010E014_cheep_cheep_chase += D_8010E360_cheep_cheep_chase->unk18;
    }
    for (i = 0; i < 4; i++) {
        model = &HmfModelData[object->model[i]];
        if (Center.z - 900.0f <= model->pos.z) {
            func_8001C258_main(object->model[i], 4, 0);
        }
        if (Center.z + 1000.0f <= model->pos.z) {
            func_8001C258_main(object->model[i], 4, 4);
            if (i != 0) {
                func_801093CC_cheep_cheep_chase(object->model[i]);
            } else {
                object->trans.z = -250.0 - D_8010E360_cheep_cheep_chase->unk14 * 500.0;
                D_8010E360_cheep_cheep_chase->unk14++;
            }
        }
    }
}

void func_8010665C_cheep_cheep_chase(omObjData *object) {
    u16 i;

    object->model[0] = func_8000B108_main(0x470009, 0x9D);
    for (i = 1; i < 3; i++) {
        object->model[i] = Hu3DModelLink(object->model[0]);
    }
    object->trans.x = -325.0f;
    object->trans.y = 200.0f;
    object->trans.z = -800.0f;
    D_8010E360_cheep_cheep_chase->unk1E++;
    for (i = 1; i < 3; i++) {
        func_80109444_cheep_cheep_chase(object->model[i]);
    }
    D_8010E360_cheep_cheep_chase->unk20 = D_800CCF58_main[HmfModelData[object->model[0]].unk02].unk02;
    object->func = func_801067B0_cheep_cheep_chase;
}

void func_801067B0_cheep_cheep_chase(omObjData *object) {
    HmfModel *model;
    s16 i;

    for (i = 0; i < 3; i++) {
        model = &HmfModelData[object->model[i]];
        if (model->pos.z >= Center.z - 800.0) {
            func_8001C258_main(object->model[i], 4, 0);
        }
        if (model->pos.z >= Center.z + 700.0) {
            func_8001C258_main(object->model[i], 4, 4);
            if (i != 0) {
                func_80109444_cheep_cheep_chase(object->model[i]);
            } else {
                object->trans.z = 200.0 - D_8010E360_cheep_cheep_chase->unk1E * 1000.0;
                D_8010E360_cheep_cheep_chase->unk1E++;
            }
        }
        if (HmfModelData[object->model[i]].unk40 >= D_8010E360_cheep_cheep_chase->unk20) {
            HmfModelData[object->model[i]].unk40 = 0.0f;
        }
    }
}

void func_80106978_cheep_cheep_chase(omObjData *object) {
    u16 i;

    object->model[0] = D_8010E360_cheep_cheep_chase->unk4[0].model = func_8000B108_main(0x470004, 0x2008D);
    for (i = 1; i < 8; i++) {
        object->model[i] = D_8010E360_cheep_cheep_chase->unk4[i].model = Hu3DModelLink(object->model[0]);
    }
    for (i = 0; i < 8; i++) {
        Hu3DModelScaleSet(object->model[i], 0.9f, 0.9f, 0.9f);
    }
    func_801094C0_cheep_cheep_chase(object, 0);
    func_801094C0_cheep_cheep_chase(object, 4);
    D_8010E360_cheep_cheep_chase->unk10 = object;
    object->func = func_80106AA0_cheep_cheep_chase;
}

void func_80106AA0_cheep_cheep_chase(omObjData *object) {
    HmfModel *model;
    s16 i;

    for (i = 0; i < 8; i++) {
        model = &HmfModelData[object->model[i]];
        if (D_8010E360_cheep_cheep_chase->unk4[i].unk3 == 0) {
            if (D_8010E360_cheep_cheep_chase->unk4[i].unk2 == 0) {
                D_8010E018_cheep_cheep_chase += 0.25f;
                if (D_8010E018_cheep_cheep_chase > 180.0f) {
                    D_8010E018_cheep_cheep_chase = 0.0f;
                }
                if (i == 0) {
                    object->trans.y = 105.0 - sindf(D_8010E018_cheep_cheep_chase) * 20.0f * 5.0f * 0.1;
                } else {
                    model->pos.y = 105.0 - sindf(D_8010E018_cheep_cheep_chase) * 20.0f * 5.0f * 0.1;
                }
                D_8010E360_cheep_cheep_chase->unk4[i].unkC += 0.75f;
                if (D_8010E360_cheep_cheep_chase->unk4[i].unkC >= 360.0f) {
                    D_8010E360_cheep_cheep_chase->unk4[i].unkC -= 360.0f;
                }
                D_8010E360_cheep_cheep_chase->unk4[i].unk8 = sindf(D_8010E360_cheep_cheep_chase->unk4[i].unkC) * (D_8010E360_cheep_cheep_chase->unk4[i].unk4 * 15.0);
                if (i == 0) {
                    object->trans.z = -(D_8010E360_cheep_cheep_chase->unkC[D_8010E360_cheep_cheep_chase->unk4[0].unk4] * 100) + D_8010E360_cheep_cheep_chase->unk4[0].unk8;
                } else {
                    model->pos.z = -(D_8010E360_cheep_cheep_chase->unkC[D_8010E360_cheep_cheep_chase->unk4[i].unk4] * 100) + D_8010E360_cheep_cheep_chase->unk4[i].unk8;
                }
                if (Center.z - 1000.0f <= model->pos.z) {
                    func_8001C258_main(object->model[i], 4, 0);
                }
            } else {
                func_8001C258_main(object->model[i], 4, 4);
            }
        }
        if (Center.z + 700.0f <= model->pos.z) {
            func_8001C258_main(object->model[i], 4, 4);
            if ((i == 0) | (i == 4)) {
                func_801094C0_cheep_cheep_chase(object, i);
            }
        }
    }
}

void func_80106E80_cheep_cheep_chase(omObjData *object) {
    s32 mdlAttr = 0x2A9;
    f32 speedBonus[8] = { -0.2f, 0.1f, 0.0f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f };
    s32 chr;
    s32 dir;
    s32 file;
    func_800E1BA8_minigame_ObjData *data;

    object->work[0] = D_800EC280_minigame;
    chr = GwPlayer[D_800EC280_minigame].chr;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(object, dir, file, D_800EC280_minigame, mdlAttr, 0x2BD);
    object->model[9] = func_8000B108_main(0x47000A, 0x2B9);
    func_8001C258_main(object->model[9], 4, 4);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 0x26, func_80017BB8_main(chr, 0xD), 1, 0);
    func_800E5A00_minigame(object, 0x27, func_80017BB8_main(chr, 0x3B), 1, 0);
    func_800E5A00_minigame(object, 0x28, func_80017BB8_main(chr, 0x3C), 1, 0);
    func_800E5A00_minigame(object, 0x2A, func_80017BB8_main(chr, 0x59), 1, 0);
    func_800E5A00_minigame(object, 0x2B, func_80017BB8_main(chr, 0x5D), 1, 0);
    func_800E5A00_minigame(object, 0xD, func_80017BB8_main(chr, 0x2F), 1, 999);
    Hu3DModelScaleSet(object->model[0], 0.7f, 0.7f, 0.7f);
    object->trans.x = 300.0 - (D_8010E370_cheep_cheep_chase[D_800EC280_minigame] + 1.0f) * 120.0;
    object->trans.y = 1060.0f;
    object->trans.z = -600.0f;
    object->rot.y = 180.0f;
    func_800E5690_minigame(object, 0x2A);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
    func_8001C258_main(object->model[1], 4, 4);
    D_800EC280_minigame++;
    data = object->data;
    D_8010E364_cheep_cheep_chase[object->work[0]].unk00 = data->unk57;
    D_8010E364_cheep_cheep_chase[object->work[0]].unk01 = 0;
    D_8010E364_cheep_cheep_chase[object->work[0]].unk04 = speedBonus[GwPlayer[object->work[0]].chr] * 20.0f * 5.0f;
    D_8010E364_cheep_cheep_chase[object->work[0]].unk20 = D_800CCF58_main[HmfModelData[object->model[9]].unk02].unk02;
    func_8010D6F4_cheep_cheep_chase(object->work[0] + 4, 9, object->model[0], 0, NULL, func_8010B52C_cheep_cheep_chase, FALSE, FALSE);
    func_8010D6F4_cheep_cheep_chase(object->work[0] + 4, 8, object->model[0], 1, NULL, func_8010BB9C_cheep_cheep_chase, TRUE, FALSE);
    object->func = func_8010732C_cheep_cheep_chase;
}

void func_8010732C_cheep_cheep_chase(omObjData *object) {
    CxFuncGroup *group = &D_8010E398_cheep_cheep_chase[object->work[0] + 4];
    CxFuncContext *ctx = group->funcCtx;
    s8 i;

    if (group->sort) {
        func_8010D9E8_cheep_cheep_chase(group);
    }
    for (i = 0; i < CX_FUNC_PRIO_MAX; i++) {
        s8 funcId = group->order[i];

        while (funcId != -1) {
            group->funcCtx[funcId].work.s16[0] = object->work[0];
            group->funcCtx[funcId].func(&ctx[funcId]);
            funcId = group->funcCtx[funcId].next;
        }
    }
    func_800E4E30_minigame(object);
}

void func_80107440_cheep_cheep_chase(omObjData *object) {
    s16 id;

    object->model[1] = D_8010E368_cheep_cheep_chase->model = func_8000B108_main(0xA0086, 0x289);
    object->model[0] = func_8000B108_main(0xA0087, 0x28D);
    object->motion[0] = func_8000B108_main(0xA0088, 0x28D);
    func_8001C5B4_main(object->model[1], object->motion[0]);
    func_8001C814_main(object->motion[0], 2, 2);
    func_8001C954_main(object->model[1]);
    func_8001C2FC_main(object->model[1], 0x20000, 0x20000);
    func_8001C2FC_main(object->model[0], 0x20000, 0x20000);
    func_8001C448_main(object->model[1]);
    func_8001C448_main(object->model[0]);
    func_8001C514_main(object->model[1]);
    func_8001C514_main(object->model[0]);
    Hu3DModelScaleSet(object->model[1], 1.4f, 1.4f, 1.4f);
    Hu3DModelPosSet(object->model[1], 0.0f, 40.0f, 0.0f);
    Hu3DModelRotSet(object->model[1], 0.0f, 180.0f, 0.0f);
    id = func_8010D6F4_cheep_cheep_chase(3, 7, -1, 0, NULL, func_8010C988_cheep_cheep_chase, FALSE, FALSE);
    D_8010E398_cheep_cheep_chase[3].funcCtx[id].work.s16[0] = object->model[1];
    D_8010E398_cheep_cheep_chase[3].funcCtx[id].work.s16[1] = object->model[0];
    func_8010D6F4_cheep_cheep_chase(3, 8, object->model[1], 0, NULL, func_8010CAD4_cheep_cheep_chase, FALSE, TRUE);
    func_8010D6F4_cheep_cheep_chase(3, 9, object->model[1], 1, NULL, func_8010CBBC_cheep_cheep_chase, FALSE, FALSE);
    func_8010D6F4_cheep_cheep_chase(3, 1, object->model[1], 1, NULL, func_8010D02C_cheep_cheep_chase, TRUE, FALSE);
    object->func = func_80107698_cheep_cheep_chase;
}

void func_80107698_cheep_cheep_chase(omObjData *object) {
    func_8010D8FC_cheep_cheep_chase(3);
}

void func_801076B4_cheep_cheep_chase(CxFuncContext *ctx) {
    if (ctx->state == 0) {
        Center.x = -26.0f;
        Center.y = 327.0f;
        Center.z = -485.0f;
        CRot.x = 320.0f;
        CRot.y = 180.0f;
        CRot.z = 0.0f;
        CZoom = 1670.0f;
        func_8010D7F4_cheep_cheep_chase(0, ctx);
    }
}

void func_80107760_cheep_cheep_chase(CxFuncContext *ctx) {
    u16 btn;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 1;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (ctx->work.s8[1] != 0) {
                if (ctx->work.s8[1] == 1) {
                sprintf(D_800D5218_main, "C: TRANSLATE ADD: %d", ctx->work.s8[0]);
                } else {
                sprintf(D_800D5218_main, "C: ROTATE");
                }
                print8(16, 56, D_800D5218_main);
                sprintf(D_800D5218_main, "CZOOMM %.2f", CZoom);
                print8(16, 64, D_800D5218_main);
                sprintf(D_800D5218_main, "CCENTER_X %.2f Y %.2f Z %.2f", Center.x, Center.y, Center.z);
                print8(16, 72, D_800D5218_main);
                sprintf(D_800D5218_main, "CROTATE_X %.2f Y %.2f Z %.2f", CRot.x, CRot.y, CRot.z);
                print8(16, 80, D_800D5218_main);
            }
            btn = D_800CDA7C_main[0];
            if (D_800D5558_main[0] & Z_TRIG) {
                ctx->work.s8[1]++;
            }
            if (ctx->work.s8[1] >= 3) {
                ctx->work.s8[1] = 0;
            }
            if (ctx->work.s8[1] == 1) {
                if (btn & D_JPAD) {
                    Center.z += ctx->work.s8[0];
                }
                if (btn & L_JPAD) {
                    Center.x += ctx->work.s8[0];
                }
                if (btn & U_JPAD) {
                    Center.z -= ctx->work.s8[0];
                }
                if (btn & R_JPAD) {
                    Center.x -= ctx->work.s8[0];
                }
                if (btn & U_CBUTTONS) {
                    Center.y += ctx->work.s8[0];
                }
                if (btn & D_CBUTTONS) {
                    Center.y -= ctx->work.s8[0];
                }
                if (ctx->work.s8[2] == 15) {
                    ctx->work.s8[2] = 0;
                    if (btn & A_BUTTON) {
                        ctx->work.s8[0]++;
                    }
                    if (btn & B_BUTTON) {
                        ctx->work.s8[0]--;
                    }
                    if (ctx->work.s8[0] >= 125) {
                        ctx->work.s8[0] = 0;
                    }
                } else {
                    ctx->work.s8[2]++;
                }
            } else if (ctx->work.s8[1] == 2) {
                if (btn & D_JPAD) {
                    CRot.x += 1.0f;
                }
                if (btn & U_JPAD) {
                    CRot.x -= 1.0f;
                }
                if (btn & L_JPAD) {
                    CRot.y -= 1.0f;
                }
                if (btn & R_JPAD) {
                    CRot.y += 1.0f;
                }
                if (btn & U_CBUTTONS) {
                    CZoom += 10.0f;
                }
                if (btn & D_CBUTTONS) {
                    CZoom -= 10.0f;
                }
            }
            break;
    }
}

void func_80107BDC_cheep_cheep_chase(CxFuncContext *ctx) {
    f32 t;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            t = ctx->work.s8[0] * 0.025f * 90.0f;
            t = sindf(t);
            CZoom = t * 230.0f + 1670.0f;
            Center.x = t * -244.0f + -26.0f;
            Center.y = t * -343.0f + 327.0f;
            Center.z = t * 30.0f + -485.0f;
            CRot.x = t * -5.0f + 320.0f;
            CRot.y = t * -90.0f + 180.0f;
            if (++ctx->work.s8[0] > 40.0f) {
                CZoom = 1900.0f;
                Center.x = -270.0f;
                Center.y = -16.0f;
                Center.z = -455.0f;
                CRot.x = 315.0f;
                CRot.y = 90.0f;
                func_8010D7F4_cheep_cheep_chase(0, ctx);
                func_8010D6F4_cheep_cheep_chase(0, 2, -1, 0, NULL, func_801080C8_cheep_cheep_chase, FALSE, FALSE);
            }
            break;
    }
}

void func_80107E3C_cheep_cheep_chase(CxFuncContext *ctx) {
    // Retail steps through D_800EC598_minigame[0] as an array: it assumes the four player objects are adjacent.
    omObjData *object = D_800EC598_minigame[0];
    CxPlayer *player = D_8010E364_cheep_cheep_chase;
    f32 t;
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            for (i = 0; i < 4; i++, object++, player++) {
                if (player->unk01 == 6) {
                    ctx->work.f32[0] = object->trans.x - 450.0;
                    ctx->work.f32[1] = object->trans.z - 80.0;
                }
            }
            ctx->state = 1;
            break;
        case 1:
            t = ctx->work.s8[0] * 0.025f * 90.0f;
            t = sindf(t);
            CZoom = t * -770.0f + 1900.0f;
            Center.x = (ctx->work.f32[0] - -270.0f) * t + -270.0f;
            Center.y = t * 101.0f + -16.0f;
            Center.z = (ctx->work.f32[1] - -455.0f) * t + -455.0f;
            CRot.x = t * 25.0f + 315.0f;
            CRot.y = t * 31.0f + 90.0f;
            if (++ctx->work.s8[0] > 40.0f) {
                CZoom = 1130.0f;
                Center.x = ctx->work.f32[0];
                Center.y = 85.0f;
                Center.z = ctx->work.f32[1];
                CRot.x = 340.0f;
                CRot.y = 121.0f;
                func_8010D7F4_cheep_cheep_chase(0, ctx);
            }
            break;
    }
}

void func_801080C8_cheep_cheep_chase(CxFuncContext *ctx) {
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.f32[0] = Center.z;
            ctx->state = 1;
            break;
        case 1:
            for (i = 0; i < 4; i++) {
                if (D_800EC598_minigame[i]->trans.z + 255.0f < ctx->work.f32[0]) {
                    ctx->work.f32[0] = D_800EC598_minigame[i]->trans.z + 255.0f;
                }
            }
            Center.z = ctx->work.f32[0];
            break;
        case 2:
            break;
    }
}

void func_80108170_cheep_cheep_chase(CxFuncContext *ctx) {
    // Retail steps through D_800EC598_minigame[0] as an array: it assumes the four player objects are adjacent.
    omObjData *object = D_800EC598_minigame[0];
    s16 i;

    if (D_8010E01C_cheep_cheep_chase >= 4) {
        HuAudSeqPlay(0x34);
    }
    switch (ctx->state) {
        case 0:
            D_8010E380_cheep_cheep_chase = HuAudFXPlay(0x433);
            ctx->work.s16[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s16[0]++) {
                case 10:
                    for (i = 0; i < 4; i++, object++) {
                        func_8010D6F4_cheep_cheep_chase(i + 4, 0, object->model[0], 0, NULL, func_80109750_cheep_cheep_chase, FALSE, FALSE);
                    }
                    break;
                case 80:
                    func_8010D6F4_cheep_cheep_chase(2, 0, D_8010E360_cheep_cheep_chase->unk24, 0, NULL, func_801092B8_cheep_cheep_chase, FALSE, FALSE);
                    break;
                case 90:
                    object = D_800EC598_minigame[0];
                    for (i = 0; i < 4; i++, object++) {
                        func_8010D6F4_cheep_cheep_chase(i + 4, 4, object->model[0], 0, NULL, func_80109CAC_cheep_cheep_chase, FALSE, FALSE);
                    }
                    break;
                case 70:
                    func_8010D6F4_cheep_cheep_chase(0, 0, -1, 0, NULL, func_80107BDC_cheep_cheep_chase, FALSE, FALSE);
                    break;
                case 110:
                    GMesCreate(3);
                    HuAudFXPlay(0xE);
                    D_8010E01E_cheep_cheep_chase = 1;
                    break;
                default:
                    if (D_8010E01E_cheep_cheep_chase == 1) {
                        if (++D_8010E022_cheep_cheep_chase >= 61) {
                            for (i = 0; i < 4; i++, object++) {
                                if (GwPlayer[object->work[0]].stat & 1) {
                                    if (D_8010E010_cheep_cheep_chase == 0) {
                                        func_8010D6F4_cheep_cheep_chase(i + 4, 0, object->model[0], 0, NULL, func_8010A57C_cheep_cheep_chase, FALSE, FALSE);
                                    } else {
                                        func_8010D6F4_cheep_cheep_chase(i + 4, 0, object->model[0], 0, NULL, func_8010A938_cheep_cheep_chase, FALSE, FALSE);
                                    }
                                }
                                if (D_8010E010_cheep_cheep_chase == 0) {
                                    func_8010D6F4_cheep_cheep_chase(i + 4, 1, object->model[0], 0, NULL, func_8010AD14_cheep_cheep_chase, FALSE, FALSE);
                                } else {
                                    func_8010D6F4_cheep_cheep_chase(i + 4, 1, object->model[0], 0, NULL, func_8010AF70_cheep_cheep_chase, FALSE, FALSE);
                                }
                                func_8010D6F4_cheep_cheep_chase(i + 4, 2, object->model[0], 0, NULL, func_8010B148_cheep_cheep_chase, FALSE, FALSE);
                                func_8010D6F4_cheep_cheep_chase(i + 4, 3, object->model[0], 0, NULL, func_8010B33C_cheep_cheep_chase, FALSE, FALSE);
                            }
                            D_8010E020_cheep_cheep_chase = ctx->work.s16[0] + 10;
                            D_8010E01E_cheep_cheep_chase = 2;
                        }
                    } else if (D_8010E01E_cheep_cheep_chase == 2) {
                        if (ctx->work.s16[0] >= D_8010E020_cheep_cheep_chase) {
                            func_8010D6F4_cheep_cheep_chase(3, 0, D_8010E368_cheep_cheep_chase->model, 0, NULL, func_8010C440_cheep_cheep_chase, FALSE, FALSE);
                            func_8010D7F4_cheep_cheep_chase(1, ctx);
                            func_8010D6F4_cheep_cheep_chase(1, 0, -1, 1, NULL, func_801085FC_cheep_cheep_chase, FALSE, FALSE);
                        }
                    }
                    break;
            }
            break;
    }
}


// Register allocation: GCC hoists func_8010A08C_cheep_cheep_chase out of the second loop (one more saved register).
#ifdef NON_MATCHING
void func_801085FC_cheep_cheep_chase(CxFuncContext *ctx) {
    // Retail steps through D_800EC598_minigame[0] as an array (the four player objects are assumed adjacent), and
    // the second loop passes the model of that pointer as the first loop left it: one past the last player.
    omObjData *object = D_800EC598_minigame[0];
    CxPlayer *player = D_8010E364_cheep_cheep_chase;
    s16 candidates[4] = { -1, -1, -1, -1 };
    s16 count = 0;
    s16 i;
    s16 *pick;
    u8 result;

    switch (ctx->state) {
        case 0:
            break;
        case 1:
            if (D_8010E360_cheep_cheep_chase->unk2E == 4) {
                func_8010D85C_cheep_cheep_chase(1);
                func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_80108AF4_cheep_cheep_chase, FALSE, TRUE);
            } else if (D_8010E360_cheep_cheep_chase->unk30 != 4) {
                if (D_8010E360_cheep_cheep_chase->unk28 != 0.0f) {
                    for (i = 0; i < 4; i++, object++) {
                        if (object->trans.z < D_8010E360_cheep_cheep_chase->unk28 - 350.0) {
                            candidates[count++] = i;
                        }
                    }
                }
                i = count;
                if (i != 0) {
                    pick = (s16)(rand16() % i) + candidates;
                    for (i = 0; i < 4; i++, player++) {
                        if (player->unk01 != 4) {
                            if (i != *pick) {
                                result = 7;
                            } else {
                                D_8010E360_cheep_cheep_chase->unk2C = i;
                                result = 6;
                            }
                            player->unk01 = result;
                            func_8010D85C_cheep_cheep_chase(i + 4);
                            func_8010D6F4_cheep_cheep_chase(i + 4, 0, object->model[0], 0, NULL, func_8010A08C_cheep_cheep_chase, FALSE, FALSE);
                        }
                    }
                    func_8010D7F4_cheep_cheep_chase(1, ctx);
                    HuAudSeqFadeOut(120);
                    GMesCreate(14);
                    func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_801088F8_cheep_cheep_chase, FALSE, TRUE);
                    D_8010E360_cheep_cheep_chase->unk18 = 0.4f;
                }
            }
            break;
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E170_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801085FC_cheep_cheep_chase);
#endif

void func_801088F8_cheep_cheep_chase(CxFuncContext *ctx) {
    if (ctx->state == 0) {
        ctx->work.s16[0] = 0;
        ctx->state = 1;
    }
    if (++ctx->work.s16[0] >= 16) {
        ctx->work.s16[0] = 15;
        func_8004AEF0_main(D_8010E380_cheep_cheep_chase, 15);
        func_8010D7F4_cheep_cheep_chase(1, ctx);
    }
}

void func_8010896C_cheep_cheep_chase(CxFuncContext *ctx) {
    s16 timer;

    switch (ctx->state) {
        case 0:
            ctx->work.s16[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (D_8010E024_cheep_cheep_chase >= 2) {
                if (GMesStatGet() == 0) {
                    D_8010E024_cheep_cheep_chase = 3;
                }
                if (D_8010E024_cheep_cheep_chase == 3) {
                    if (++ctx->work.s16[0] >= 15) {
                        WipeCreateOut(0, 20);
                        ctx->state = 2;
                    }
                }
            } else {
                timer = ctx->work.s16[0]++;
                if (timer == 0) {
                    GMesCreate(0x16, GwPlayer[D_8010E360_cheep_cheep_chase->unk2C].chr);
                    HuAudSeqPlay(0x65);
                    GwPlayer[D_8010E360_cheep_cheep_chase->unk2C].bonusCoin += 10;
                }
                if (GMesStatGet() != 0) {
                    ctx->work.s16[0] = 0;
                    D_8010E024_cheep_cheep_chase = 2;
                }
            }
            break;
        case 2:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

void func_80108AF4_cheep_cheep_chase(CxFuncContext *ctx) {
    if (D_8010E026_cheep_cheep_chase == 1 && GMesStatGet() == 0) {
        ctx->state = 99;
        ctx->work.s16[0] = 0;
        D_8010E026_cheep_cheep_chase = 2;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s16[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s16[0]++) {
                case 0:
                    HuAudSeqFadeOut(120);
                    GMesCreate(14);
                    func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_801088F8_cheep_cheep_chase, FALSE, TRUE);
                    ctx->state = 3;
                    break;
                case 15:
                    GMesCreate(0x20);
                    HuAudSeqPlay(0x6C);
                    D_8010E026_cheep_cheep_chase = 1;
                    break;
            }
            break;
        case 2:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                ctx->state = 1;
            }
            break;
        case 99:
            if (++ctx->work.s16[0] == 15) {
                WipeCreateOut(0, 20);
                ctx->state = 2;
            }
            break;
    }
}

void func_80108C98_cheep_cheep_chase(CxFuncContext *ctx) {
    s16 i = 0;

    if (ctx->state == 0) {
        D_8010E360_cheep_cheep_chase->models[0].x = 1200.0f;
        D_8010E360_cheep_cheep_chase->models[0].y = 600.0f;
        D_8010E360_cheep_cheep_chase->models[0].z = 1000.0f;
        D_8010E360_cheep_cheep_chase->models[1].x = 1200.0f;
        D_8010E360_cheep_cheep_chase->models[1].y = 600.0f;
        D_8010E360_cheep_cheep_chase->models[1].z = 1000.0f;
        for (i = 0; i < 4; i++) {
            D_8010E360_cheep_cheep_chase->models[i + 2].x = 1200.0f;
            D_8010E360_cheep_cheep_chase->models[i + 2].y = 600.0f;
            D_8010E360_cheep_cheep_chase->models[i + 2].z = 1000.0f;
        }
        D_8010E360_cheep_cheep_chase->unk14 = 0;
        D_8010E360_cheep_cheep_chase->unk1E = 0;
        D_8010E360_cheep_cheep_chase->unk1C = 0;
        D_8010E360_cheep_cheep_chase->unk28 = 0;
        D_8010E360_cheep_cheep_chase->unk18 = 0.4f;
        D_8010E360_cheep_cheep_chase->unk2C = -1;
        D_8010E360_cheep_cheep_chase->unk2E = 0;
        D_8010E360_cheep_cheep_chase->unk30 = 0;
        D_8010E360_cheep_cheep_chase->unk8[0] = 0;
        D_8010E360_cheep_cheep_chase->unk8[1] = 2;
        D_8010E360_cheep_cheep_chase->unk8[2] = 3;
        D_8010E360_cheep_cheep_chase->unk8[3] = 4;
        D_8010E360_cheep_cheep_chase->unk8[4] = 5;
        D_8010E360_cheep_cheep_chase->unk8[5] = 2;
        D_8010E360_cheep_cheep_chase->unk8[6] = 1;
        for (i = 0; i < 5; i++) {
            func_801091FC_cheep_cheep_chase(i);
        }
        func_801091FC_cheep_cheep_chase(6);
        D_8010E360_cheep_cheep_chase->unkC[0] = 10;
        D_8010E360_cheep_cheep_chase->unkC[1] = 18;
        D_8010E360_cheep_cheep_chase->unkC[2] = 28;
        D_8010E360_cheep_cheep_chase->unkC[3] = 32;
        D_8010E360_cheep_cheep_chase->unkC[4] = 40;
        D_8010E360_cheep_cheep_chase->unkC[5] = 47;
        D_8010E360_cheep_cheep_chase->unkC[6] = 56;
        D_8010E360_cheep_cheep_chase->unk24 = ctx->param;
        Hu3DModelScaleSet(ctx->param, 1.4f, 1.4f, 1.4f);
        Hu3DModelPosSet(ctx->param, 0.0f, -100.0f, 0.0f);
        func_8001C258_main(ctx->param, 4, 0);
        HmfModelData[ctx->param].unk44 = 0.0f;
        HmfModelData[ctx->param].unk40 = 0.0f;
        func_8010D7F4_cheep_cheep_chase(2, ctx);
    }
}

void func_80108F78_cheep_cheep_chase(CxFuncContext *ctx) {
    CxStageModel *stage = &D_8010E360_cheep_cheep_chase->models[1];
    HmfModel *model;
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 5;
            ctx->state = 1;
            break;
        case 1:
            for (i = 1; i < 6; i++, stage++) {
                model = &HmfModelData[stage->model];
                if (Center.z - 700.0f <= model->pos.z) {
                    func_8001C258_main(stage->model, 4, 0);
                }
                if (Center.z + 1700.0f <= model->pos.z) {
                    func_8001C258_main(stage->model, 4, 4);
                    if (i >= 2 && ctx->work.s8[0] < 7) {
                        func_801091FC_cheep_cheep_chase(ctx->work.s8[0]++);
                    }
                }
            }
            break;
        case 2:
            break;
    }
}

// Register allocation: retail reloads the model id for the first func_8001C258_main call.
#ifdef NON_MATCHING
void func_801090E0_cheep_cheep_chase(CxFuncContext *ctx) {
    s16 *stage = &D_8010E360_cheep_cheep_chase->models[0].model;
    HmfModel *model = &HmfModelData[*stage];

    if (ctx->state == 1) {
        if (Center.z - 700.0f <= model->pos.z) {
            func_8001C258_main(*stage, 4, 0);
        }
        if (model->pos.z >= Center.z + 1700.0f + 400.0) {
            func_8001C258_main(*stage, 4, 4);
            func_8010D7F4_cheep_cheep_chase(2, ctx);
            func_8001C258_main(D_8010E360_cheep_cheep_chase->unk24, 4, 4);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_801090E0_cheep_cheep_chase);
#endif

void func_801091FC_cheep_cheep_chase(u8 arg0) {
    f32 z = 0.0f;
    s16 i;
    u8 section;
    CxStageModel *stage;

    if (arg0 != 0) {
        for (i = 0; i < arg0; i++) {
            stage = &D_8010E360_cheep_cheep_chase->models[D_8010E360_cheep_cheep_chase->unk8[i]];
            z -= stage->z;
        }
    }
    section = D_8010E360_cheep_cheep_chase->unk8[arg0];
    stage = &D_8010E360_cheep_cheep_chase->models[section];
    if (section == 1) {
        D_8010E360_cheep_cheep_chase->unk28 = z;
    }
    Hu3DModelPosSet(stage->model, 0.0f, 0.0f, z);
}

void func_801092B8_cheep_cheep_chase(CxFuncContext *ctx) {
    HmfModel *model = &HmfModelData[ctx->param];

    switch (ctx->state) {
        case 0:
            HuAudFXPlay(0x435);
            ctx->work.f32[0] = D_800CCF58_main[HmfModelData[ctx->param].unk02].unk02 - 1.0f;
            model->unk44 = 1.0f;
            ctx->state = 1;
            break;
        case 1:
            if (HmfModelData[ctx->param].unk40 >= ctx->work.f32[0]) {
                func_8010D7F4_cheep_cheep_chase(2, ctx);
            }
            break;
    }
}

void func_801093CC_cheep_cheep_chase(s16 model) {
    Hu3DModelPosSet(model, 0.0f, 110.0f, -250.0 - D_8010E360_cheep_cheep_chase->unk14 * 500.0);
    D_8010E360_cheep_cheep_chase->unk14++;
}

void func_80109444_cheep_cheep_chase(s16 model) {
    Hu3DModelPosSet(model, -325.0f, 200.0f, 200.0 - D_8010E360_cheep_cheep_chase->unk1E * 1000.0);
    D_8010E360_cheep_cheep_chase->unk1E++;
}

void func_801094C0_cheep_cheep_chase(omObjData *object, s16 base) {
    s16 i;

    if (D_8010E360_cheep_cheep_chase->unk1C < 7) {
        for (i = 0; i < 4; i++) {
            if (base + i == 0) {
                object->trans.x = 300.0 - (i + 1) * 120.0;
                object->trans.y = 110.0f;
                object->trans.z = -(D_8010E360_cheep_cheep_chase->unkC[D_8010E360_cheep_cheep_chase->unk1C] * 100);
            } else {
                Hu3DModelPosSet(object->model[base + i], 300.0 - (i + 1) * 120.0, 110.0f,
                                -(D_8010E360_cheep_cheep_chase->unkC[D_8010E360_cheep_cheep_chase->unk1C] * 100));
            }
            D_8010E360_cheep_cheep_chase->unk4[base + i].unk4 = D_8010E360_cheep_cheep_chase->unk1C;
            D_8010E360_cheep_cheep_chase->unk4[base + i].unk2 = 0;
            D_8010E360_cheep_cheep_chase->unk4[base + i].unk3 = 0;
            D_8010E360_cheep_cheep_chase->unk4[base + i].unk5 = 0;
            D_8010E360_cheep_cheep_chase->unk4[base + i].unkC = rand16() % 361;
        }
        D_8010E360_cheep_cheep_chase->unk1C++;
    }
}

// Register allocation and scheduling (one more saved register; retail computes the inner loop bound in the loop).
#ifdef NON_MATCHING
void func_80109750_cheep_cheep_chase(CxFuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    f32 weight[8] = { 65.0f, 58.0f, 45.0f, 60.0f, 84.0f, 102.0f, 44.0f, 45.0f };
    f32 gravity;
    f32 dx;
    f32 dz;
    s16 i;
    s16 j;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.f32[1] = object->trans.y = 1060.0f;
            ctx->work.f32[2] = 0.0f;
            func_800E5690_minigame(object, 0x2A);
            CharFXPlay(0xB8, GwPlayer[object->work[0]].chr);
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s8[0]) {
                case 0:
                    ctx->work.f32[2] += 0.1;
                    gravity = weight[GwPlayer[object->work[0]].chr] * -9.8f;
                    if ((object->trans.y = gravity * 0.5 * ctx->work.f32[2] * ctx->work.f32[2] + ctx->work.f32[1]) <= 60.0) {
                        CharFXPlay(0x70, GwPlayer[object->work[0]].chr);
                        ctx->work.s8[0] = 1;
                        ctx->work.f32[2] = 0.0f;
                        for (i = 0; i < 2; i++) {
                            dx = (rand16() % 9 - 4) * 0.1;
                            dz = (rand16() % 9 - 4) * 0.1;
                            for (j = 30; j < 30 + 18; j++) {
                                if ((s16)func_8010DC7C_cheep_cheep_chase(j, dx * 100.0f + object->trans.x, 160.0f, dz * 100.0f + object->trans.z, 0.0f, 90.0f, 0.0f, 1.0f, i)) {
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case 1:
                    if (ctx->work.f32[2] >= 90.0f) {
                        ctx->work.f32[2] = 5.0f + ctx->work.f32[2];
                    } else {
                        ctx->work.f32[2] = ctx->work.f32[2] + 10.0f;
                    }
                    gravity = weight[GwPlayer[object->work[0]].chr] * -9.8f;
                    if (D_8010E364_cheep_cheep_chase[object->work[0]].unk04 + 60.0 <= (object->trans.y = sindf(ctx->work.f32[2]) * gravity * 0.15f)) {
                        ctx->work.s8[0] = 2;
                        ctx->work.f32[2] = 0.0f;
                        CharFXPlay(0x82, GwPlayer[object->work[0]].chr);
                        object->trans.y = D_8010E364_cheep_cheep_chase[object->work[0]].unk04 + 60.0;
                    }
                    break;
            }
            if (ctx->work.s8[0] == 2) {
                func_800E5690_minigame(object, 0x26);
                func_8010D7F4_cheep_cheep_chase(ctx->work.s16[0] + 4, ctx);
            }
            break;
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", D_8010E1B8_cheep_cheep_chase);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_80109750_cheep_cheep_chase);
#endif

void func_80109CAC_cheep_cheep_chase(CxFuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    f32 scale = 0.0f;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s8[0]) {
                case 0:
                    func_800E5690_minigame(object, 0x2B);
                    ctx->work.s8[0] = 1;
                    break;
                case 1:
                    if (++ctx->work.s8[1] > 7.0f) {
                        if (ctx->work.s16[4] == 0) {
                            omVibrate(ctx->work.s16[0], 10, 0, 10);
                            ctx->work.s16[4] = 1;
                        }
                        switch (ctx->work.s8[3]) {
                            case 0:
                                if (func_8010DF48_cheep_cheep_chase(&scale, (u8 *)&ctx->work.s8[2], 1.2f, 2.5f, 3.0f)) {
                                    ctx->work.s8[2] = 0;
                                    ctx->work.s8[3] = 1;
                                }
                                func_8001C258_main(object->model[9], 4, 0);
                                break;
                            case 1:
                                if (func_8010DF48_cheep_cheep_chase(&scale, (u8 *)&ctx->work.s8[2], 2.5f, 0.8f, 3.0f)) {
                                    HmfModelData[object->model[0]].unk44 = 0.75f;
                                    ctx->work.s8[2] = 0;
                                    ctx->work.s8[3] = 2;
                                    func_8001C258_main(object->model[9], 4, 4);
                                    D_8010E01C_cheep_cheep_chase++;
                                }
                                break;
                        }
                        Hu3DModelPosSet(object->model[9], object->trans.x - 10.0, object->trans.y + 200.0, object->trans.z - 30.0);
                        Hu3DModelScaleSet(object->model[9], scale, scale, scale);
                        HmfModelData[object->model[9]].rot.y = CRot.y - 90.0f;
                    }
                    break;
            }
            if (ctx->work.s8[1]++ > 40.0f) {
                ctx->work.s8[0] = 2;
            }
            if (ctx->work.s8[0] == 2) {
                func_8010B63C_cheep_cheep_chase(&D_8010E364_cheep_cheep_chase[object->work[0]], 0x26, 1);
                HmfModelData[object->model[0]].unk44 = 1.0f;
                HmfModelData[object->model[9]].rot.y = 0.0f;
                func_8010D7F4_cheep_cheep_chase(ctx->work.s16[0] + 4, ctx);
                func_8010D6F4_cheep_cheep_chase(object->work[0] + 4, 4, object->model[0], 0, NULL, func_8010B648_cheep_cheep_chase, FALSE, FALSE);
            }
            break;
    }
}

// Register allocation (ctx/object/player in other saved registers).
#ifdef NON_MATCHING
void func_8010A08C_cheep_cheep_chase(CxFuncContext *ctx) {
    CxPlayer *player;
    omObjData *object;
    GW_PLAYER *gw;

    object = D_800EC598_minigame[ctx->work.s16[0]];
    player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->work.s8[4] = 0;
            ctx->work.f32[0] = object->trans.z;
            ctx->work.f32[1] = object->trans.x;
            func_8001C258_main(object->model[9], 4, 4);
            ctx->state = 1;
            break;
        case 1:
            switch (player->unk01) {
                case 7:
                    func_800E5690_minigame(object, 0x2A);
                    object->trans.z += 5.0;
                    ctx->work.s8[0] = ctx->work.s8[0] + 0.5;
                    if (ctx->work.s8[0] >= 180.0f) {
                        ctx->work.s8[0] = ctx->work.s8[0] - 180.0f;
                    }
                    object->trans.y = sindf(ctx->work.s8[0]) * 20.0f * 5.0f * 0.05f + 80.0;
                    break;
                case 6:
                    if (++ctx->work.s8[3] >= 5) {
                        func_800E5690_minigame(object, 1);
                        if (HmfModelData[object->model[0]].unk40 == 0.0f) {
                            CharFXPlay(0x1F, GwPlayer[object->work[0]].chr);
                        }
                        if (ctx->work.s8[2] == 0 && func_8010DF48_cheep_cheep_chase(&object->trans.y, (u8 *)&ctx->work.s8[0], player->unk04 + 60.0, 210.0f, 20.0f)) {
                            ctx->work.s8[2] = 1;
                        }
                        if (func_8010DF48_cheep_cheep_chase(&object->trans.z, (u8 *)&ctx->work.s8[1], ctx->work.f32[0], D_8010E360_cheep_cheep_chase->unk28 - 700.0, 70.0f)) {
                            ctx->work.s8[1] = 70;
                        }
                        if (func_8010DF48_cheep_cheep_chase(&object->trans.x, (u8 *)&ctx->work.s8[4], ctx->work.f32[1], 0.0f, 70.0f)) {
                            func_800E5690_minigame(object, 0);
                            ctx->state = 2;
                            func_8010D6F4_cheep_cheep_chase(0, 0, -1, 0, NULL, func_80107E3C_cheep_cheep_chase, FALSE, FALSE);
                            ctx->work.s8[1] = 0;
                        }
                    }
                    func_8001C258_main(object->model[1], 4, 0);
                    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y - 5.0f, object->trans.z);
                    break;
            }
            break;
        case 2:
            if (func_8010DF48_cheep_cheep_chase(&object->rot.y, (u8 *)&ctx->work.s8[1], 180.0f, 121.0f, 40.0f)) {
                ctx->state = 3;
                ctx->work.s8[1] = 0;
            }
            break;
        case 3:
            if (++ctx->work.s8[1] >= 6) {
                gw = &GwPlayer[ctx->work.s16[0]];
                func_80017790_main(object->model[0], 2, gw->chr, D_8010E028_cheep_cheep_chase[gw->chr]);
                func_8010D7F4_cheep_cheep_chase(ctx->work.s16[0] + 4, ctx);
                func_800E5690_minigame(object, 0xD);
                func_80045ED0_main(D_800A178C_main[gw->chr][0] | 0x2F);
                func_8010D6F4_cheep_cheep_chase(1, 0, -1, 0, NULL, func_8010896C_cheep_cheep_chase, FALSE, FALSE);
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010A08C_cheep_cheep_chase);
#endif

// Register allocation: s0/s2/s3 rotated, f0/f2 swapped in the threshold sum (trans.z loaded before the add.d),
// and retail copies `hit` to v0 in the loop's delay slot where this has a nop.
#ifdef NON_MATCHING
void func_8010A57C_cheep_cheep_chase(CxFuncContext *ctx) {
    omObjData *object;
    CxPlayer *player;
    CxUnk4Entry *entry;
    f64 limit;
    s16 i;
    s32 hit;

    object = D_800EC598_minigame[ctx->work.s16[0]];
    player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];
    hit = 0;

    switch (ctx->state) {
        case 0:
            switch (GwPlayer[object->work[0]].cpu_difficulty) {
                case 0:
                    ctx->work.s8[0] = 2;
                    ctx->work.s8[2] = 3;
                    break;
                case 1:
                    ctx->work.s8[0] = 1;
                    ctx->work.s8[2] = 3;
                    break;
                case 2:
                    ctx->work.s8[0] = 0;
                    ctx->work.s8[2] = 3;
                    break;
                case 3:
                    ctx->work.s8[0] = 0;
                    ctx->work.s8[2] = 2;
                    break;
            }
            ctx->work.s8[1] = 0;
            ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
            ctx->state = 1;
            break;
        case 1:
            if (player->unk01 == 3) {
                break;
            }
            func_8010ACD8_cheep_cheep_chase(player->unk00);
            for (i = 0; i < 2; i++) {
                entry = &D_8010E360_cheep_cheep_chase->unk4[i * 4 + (s16)D_8010E370_cheep_cheep_chase[ctx->work.s16[0]]];
                if (entry->unk5 == 0 && !(HmfModelData[entry->model].unk18 & 4)) {
                    if (ctx->work.s8[0] == 0) {
                        limit = -(D_8010E360_cheep_cheep_chase->unkC[entry->unk4] * 100) + entry->unk8;
                    } else {
                        limit = -(D_8010E360_cheep_cheep_chase->unkC[entry->unk4] * 100);
                    }
                    if (object->trans.z < limit + 140.0) {
                        hit = 1;
                        entry->unk5 = 1;
                    }
                }
            }
            if (hit) {
                D_800CDA7C_main[(u8)player->unk00] = 0x4000;
            } else if (ctx->work.s8[1]++ > ctx->work.s8[0] + ctx->work.s8[3]) {
                ctx->work.s8[1] = 0;
                ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
                ((u16 *)D_800CDA7C_main)[(u8)player->unk00] = 0x8000;
            } else {
                D_800CDA7C_main[(u8)player->unk00] = 0;
            }
            break;
        case 2:
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010A57C_cheep_cheep_chase);
#endif

// Register allocation as func_8010A57C (object/player in s3/s2, f0/f2 swapped, nop for retail's `move v0,s0`).
#ifdef NON_MATCHING
void func_8010A938_cheep_cheep_chase(CxFuncContext *ctx) {
    CxPlayer *player;
    omObjData *object;
    CxUnk4Entry *entry;
    f32 limit;
    s16 i;
    s32 hit;

    object = D_800EC598_minigame[ctx->work.s16[0]];
    player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];
    hit = 0;

    switch (ctx->state) {
        case 0:
            switch (GwPlayer[object->work[0]].cpu_difficulty) {
                case 0:
                    ctx->work.s8[0] = 3;
                    ctx->work.s8[2] = 3;
                    break;
                case 1:
                    ctx->work.s8[0] = 2;
                    ctx->work.s8[2] = 3;
                    break;
                case 2:
                    ctx->work.s8[0] = 1;
                    ctx->work.s8[2] = 3;
                    break;
                case 3:
                    ctx->work.s8[0] = 0;
                    ctx->work.s8[2] = 3;
                    break;
            }
            ctx->work.s8[1] = 0;
            ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
            ctx->state = 1;
            break;
        case 1:
            if (player->unk01 == 3) {
                break;
            }
            func_8010ACD8_cheep_cheep_chase(player->unk00);
            for (i = 0; i < 2; i++) {
                entry = &D_8010E360_cheep_cheep_chase->unk4[i * 4 + (s16)D_8010E370_cheep_cheep_chase[ctx->work.s16[0]]];
                if (entry->unk5 == 0 && !(HmfModelData[entry->model].unk18 & 4)) {
                    if (ctx->work.s8[0] == 0) {
                        limit = -(D_8010E360_cheep_cheep_chase->unkC[entry->unk4] * 100) + entry->unk8 + 100.0f;
                    } else {
                        limit = -(D_8010E360_cheep_cheep_chase->unkC[entry->unk4] * 100) + 100;
                    }
                    if (object->trans.z < limit) {
                        hit = 1;
                        entry->unk5 = 1;
                    }
                }
            }
            if (hit) {
                D_800D5558_main[(u8)player->unk00] = 0x2000;
            } else if (ctx->work.s8[1]++ > ctx->work.s8[0] + ctx->work.s8[3]) {
                ctx->work.s8[1] = 0;
                ctx->work.s8[3] = rand16() % (ctx->work.s8[2] + 1);
                ((u16 *)D_800CDA7C_main)[(u8)player->unk00] = 0x8000;
            } else {
                D_800CDA7C_main[(u8)player->unk00] = 0x4000;
            }
            break;
        case 2:
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_26_cheep_cheep_chase/225740", func_8010A938_cheep_cheep_chase);
#endif

void func_8010ACD8_cheep_cheep_chase(u8 player) {
    D_800CBB6E_main[player] = 0;
    D_800D20A1_main[player] = 0;
    D_800CDA7C_main[player] = 0;
    D_800D5558_main[player] = 0;
}

void func_8010AD14_cheep_cheep_chase(CxFuncContext *ctx) {
    CxPlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    s32 count;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (player->unk01 == 3) {
                break;
            }
            if (ctx->work.s8[0] == 0) {
                if ((u16)D_800CDA7C_main[(u8)player->unk00] & 0x8000) {
                    if (player->unk01 == 0) {
                        player->unk14 = 7.0f;
                        player->unk01 = 1;
                    } else if (player->unk14 < 90.0f) {
                        player->unk14 += 4.0f;
                    } else {
                        player->unk1C++;
                        player->unk14 = 90.0f;
                        count = player->unk1C - 4;
                        if (count > 0) {
                            player->unk18 = count * 0.5f;
                            if (player->unk18 >= 4.0f) {
                                player->unk18 = 4.0f;
                            }
                        }
                    }
                    ctx->work.s8[0] = 1;
                }
            } else if (!((u16)D_800CDA7C_main[(u8)player->unk00] & 0x8000)) {
                ctx->work.s8[0] = 0;
            }
            if (player->unk01 == 1 && -(D_8010E360_cheep_cheep_chase->unkC[6] + 2) * 100 < object->trans.z) {
                if ((u16)D_800CDA7C_main[(u8)player->unk00] & 0x4000) {
                    player->unk08 = 1;
                }
                if ((u16)D_800CDA7C_main[(u8)player->unk00] & 0x2000) {
                    player->unk08 = 1;
                }
            }
            if (++ctx->work.s8[1] >= 30) {
                ctx->work.s8[1] = 0;
                player->unk1C = 0;
            }
            break;
        case 2:
            break;
    }
}

void func_8010AF70_cheep_cheep_chase(CxFuncContext *ctx) {
    CxPlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];
    s32 count;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (player->unk01 == 3) {
                break;
            }
            if (ctx->work.s8[0] == 0) {
                if ((u16)D_800CDA7C_main[(u8)player->unk00] & 0x8000) {
                    if (player->unk01 == 0) {
                        player->unk14 = 7.0f;
                        player->unk01 = 1;
                    } else if (player->unk14 < 90.0f) {
                        player->unk14 += 4.0f;
                    } else {
                        player->unk1C++;
                        player->unk14 = 90.0f;
                        count = player->unk1C - 1;
                        if (count > 0) {
                            player->unk18 = count * 0.5f;
                            if (player->unk18 >= 4.0f) {
                                player->unk18 = 4.0f;
                            }
                        }
                    }
                    ctx->work.s8[0] = 1;
                }
            } else if ((u16)D_800CDA7C_main[(u8)player->unk00] & 0x4000) {
                ctx->work.s8[0] = 0;
            }
            if (player->unk01 == 1 && (D_800D5558_main[(u8)player->unk00] & 0x2000)) {
                player->unk08 = 1;
            }
            if (++ctx->work.s8[1] >= 30) {
                ctx->work.s8[1] = 0;
                player->unk1C = 0;
            }
            break;
        case 2:
            break;
    }
}

void func_8010B148_cheep_cheep_chase(CxFuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CxPlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

    if (player->unk01 == 4) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (player->unk01 != 1) {
                break;
            }
            if (player->unk08 == 0) {
                ctx->work.s8[2] = 0;
                object->trans.z -= sindf(player->unk14) * (player->unk18 + 6.0f);
                if (HmfModelData[object->model[0]].unk40 == 0.0f) {
                    func_8004AC98_main(GwPlayer[object->work[0]].chr + 0x7A, object->work[0] + 4);
                }
            } else {
                object->trans.z -= sindf(player->unk14) * (player->unk18 + 6.0f) - 1.0f;
            }
            player->unk14 += 4.0f;
            if (player->unk14 >= 180.0f) {
                player->unk14 = 0.0f;
                player->unk01 = 0;
                func_8010B63C_cheep_cheep_chase(player, 0x26, 0);
            } else {
                player->unk01 = 1;
                func_8010B63C_cheep_cheep_chase(player, 0x27, 1);
            }
            break;
        case 2:
            break;
    }
}

void func_8010B33C_cheep_cheep_chase(CxFuncContext *ctx) {
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CxPlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.f32[0] = 0.0f;
            ctx->state = 1;
            break;
        case 1:
            if (player->unk08 == 0) {
                break;
            }
            ctx->work.f32[0] += 3.6f;
            if (ctx->work.f32[0] >= 180.0f) {
                ctx->work.s8[0] = 0;
                ctx->work.s8[1] = 0;
                ctx->work.f32[0] = 0.0f;
                player->unk08 = 0;
            }
            object->trans.y = player->unk04 + 60.0 - sindf(ctx->work.f32[0]) * 150.0;
            switch (ctx->work.s8[1]) {
                case 0:
                    if (func_8010DF48_cheep_cheep_chase(&object->rot.x, (u8 *)&ctx->work.s8[0], 0.0f, 45.0f, 8.0f)) {
                        ctx->work.s8[1] = 1;
                    }
                    break;
                case 1:
                    if (func_8010DF48_cheep_cheep_chase(&object->rot.x, (u8 *)&ctx->work.s8[0], 45.0f, -45.0f, 24.0f)) {
                        ctx->work.s8[1] = 2;
                    }
                    break;
                case 2:
                    if (func_8010DF48_cheep_cheep_chase(&object->rot.x, (u8 *)&ctx->work.s8[0], -45.0f, 0.0f, 17.0f)) {
                        ctx->work.s8[1] = 3;
                    }
                    break;
            }
            break;
        case 2:
            break;
    }
}

void func_8010B52C_cheep_cheep_chase(CxFuncContext *ctx) {
    HmfModel *model = &HmfModelData[ctx->param];
    omObjData *object = D_800EC598_minigame[ctx->work.s16[0]];
    CxPlayer *player = &D_8010E364_cheep_cheep_chase[ctx->work.s16[0]];

    switch (ctx->state) {
        case 0:
            player->updateMotion = 0;
            ctx->state = 1;
            break;
        case 1:
            if (D_800CCF58_main[HmfModelData[ctx->param].unk02].unk02 - 1 <= model->unk40) {
                player->updateMotion = 1;
            }
            if (player->updateMotion) {
                func_800E5690_minigame(object, player->motion);
                player->updateMotion = 0;
            }
            break;
        case 2:
            break;
    }
}

void func_8010B63C_cheep_cheep_chase(CxPlayer *player, s32 motion, s32 updateMotion) {
    player->updateMotion = updateMotion;
    player->motion = motion;
}

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

s16 func_8010D6F4_cheep_cheep_chase(s8 groupId, s8 prio, s16 param, s8 state, void *data, CxFunc func, u8 sort, u8 execFunc) {
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
            ctx->state = state;
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

