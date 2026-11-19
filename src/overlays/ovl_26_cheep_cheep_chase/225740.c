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


typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ char unk02[0xE];
} CxStageModel; // Size 0x10

typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ u8 unk4; // index into CxGame::unkC
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
    /* 0x08 */ char unk08[0x18];
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

extern f32 D_8010E014_cheep_cheep_chase;
extern f32 D_8010E018_cheep_cheep_chase;

extern u8 D_800D6A90_main;
extern s32 D_800A178C_main[][6];

extern const s16 D_8010E050_cheep_cheep_chase[];
extern const s16 D_8010E05C_cheep_cheep_chase[];
extern const s16 D_8010E06C_cheep_cheep_chase[];

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
void func_80108170_cheep_cheep_chase(CxFuncContext *ctx);
void func_80108C98_cheep_cheep_chase(CxFuncContext *ctx);
void func_80108F78_cheep_cheep_chase(CxFuncContext *ctx);
void func_801090E0_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010B52C_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010BB9C_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010C988_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010CAD4_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010CBBC_cheep_cheep_chase(CxFuncContext *ctx);
void func_8010D02C_cheep_cheep_chase(CxFuncContext *ctx);
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

