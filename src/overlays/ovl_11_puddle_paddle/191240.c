#include "common.h"

typedef struct UnkPuddlePaddle {
    /* 0x00 */ char pad00[8];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ char pad09[1];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} UnkPuddlePaddle; // size >= 0x10

#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/sprite.h"

// m1 pp1
/* Puddle Paddle: two teams of two paddle a raft to collect the coins falling on the pond. Shares its frame (and
   the object system at func_8010B820_puddle_paddle) with Baby Bowser Broadside (ovl_0C). */

/* omObjData::work of a player object and of the setup object: work[0] the player index (its low half read
   as a s16), work[1] the task group (its low byte read as a s8). Big-endian views of two words. */
typedef union PpObjWork {
    struct {
        /* 0x00 */ s32 player;
        /* 0x04 */ s32 group;
    } w;
    struct {
        /* 0x00 */ s16 hi;
        /* 0x02 */ s16 player;
        /* 0x04 */ s8 pad[3];
        /* 0x07 */ s8 group;
    } b;
} PpObjWork;
#define PP_WORK(obj) ((PpObjWork*)(obj)->work)

/* The object system's types (Broadside 169540's Bb* layouts) */
typedef struct PpCtx {
    /* 0x00 */ omObjData* obj;
    /* 0x04 */ s16* models;
    /* 0x08 */ s16 count;
} PpCtx; /* size 0xC */

struct PpTask;
typedef void (*PpTaskFunc)(PpCtx*, struct PpTask*);

typedef struct PpTask {
    /* 0x00 */ s8 set;
    /* 0x02 */ s16 id;
    /* 0x04 */ s8 state;
    /* 0x05 */ s8 tag;
    /* 0x08 */ s32 prio;
    /* 0x0C */ s8 s8[16];
    /* 0x1C */ s16 s16[8];
    /* 0x2C */ f32 f32[4];
    /* 0x3C */ void* data;
    /* 0x40 */ PpTaskFunc func;
} PpTask; /* size 0x44 */

typedef struct PpGroup {
    /* 0x00 */ PpCtx* ctx;
    /* 0x04 */ PpTask* tasks;
    /* 0x08 */ s16 count;
    /* 0x0C */ void* order;
    /* 0x10 */ s8 sort;
} PpGroup; /* size 0x14 */

typedef struct PpSprite {
    /* 0x00 */ s8 state;
    /* 0x01 */ u8 group;
    /* 0x02 */ u8 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ s16 unk06;
} PpSprite; /* size 8 */

typedef struct PpBill {
    /* 0x00 */ s8 set;
    /* 0x04 */ s32 attr;
    /* 0x08 */ s16 tag;
    /* 0x0A */ u8 spriteId;
    /* 0x0C */ s16 model;
    /* 0x0E */ char unk0E[0x16];
} PpBill; /* size 0x24 */

/* A team (D_80111650_puddle_paddle[2]) */
typedef struct PpTeam {
    /* 0x00 */ char unk00[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ char unk1C[4];
    /* 0x20 */ u8 count;
    /* 0x22 */ s16 member[2]; /* player indices */
    /* 0x26 */ s16 digit[2]; /* score digit sprites */
    /* 0x2A */ char unk2A[0x3A];
} PpTeam; /* size 0x64 */

/* A player (D_80111654_puddle_paddle[4]) */
typedef struct PpPlayer {
    /* 0x00 */ s16 no;
    /* 0x02 */ s16 chr;
    /* 0x04 */ s32 unk04;
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
    /* 0x04 */ char unk04[0x1C];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x10];
} PpCoin; /* size 0x34 */

/* The game state (D_80111658_puddle_paddle) */
typedef struct PpState {
    /* 0x00 */ s32 flags;
    /* 0x04 */ char unk04[0x34];
    /* 0x38 */ PpCoin* coins;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ char unk3E[6];
} PpState; /* size 0x44 */

extern PpTeam* D_80111650_puddle_paddle;
extern PpPlayer* D_80111654_puddle_paddle;
extern PpState* D_80111658_puddle_paddle;
extern PpSprite* D_80111664_puddle_paddle;
extern PpBill* D_80111668_puddle_paddle;

extern f32 D_80111220_puddle_paddle;
extern f32 D_80111224_puddle_paddle;
extern f32 D_80111228_puddle_paddle;
extern s16 D_8011122C_puddle_paddle;
extern s16 D_8011122E_puddle_paddle;
extern s16 D_80111230_puddle_paddle;
extern s16 D_80111232_puddle_paddle;
extern const s16 D_80111370_puddle_paddle[];
extern const s16 D_8011137C_puddle_paddle[];
extern const s16 D_8011138C_puddle_paddle[];

// main
s32 func_8000B638_main(void);
void func_8001E65C_main(s16 mdl, f32 u, f32 v, s32 w, s32 h);
u8 rand8(void);
extern s8 D_800CBB6E_main[];
extern s16 D_800CDA7C_main[];
extern s8 D_800D20A1_main[];
extern u8 D_800D6A90_main;
extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
// the object system (this unit)
void func_8010B820_puddle_paddle(void);
PpGroup* func_8010B8B4_puddle_paddle(omObjData* obj, s8 group, s16 models, s16 tasks);
s16 func_8010BA04_puddle_paddle(s8 group, s32 mask, void* data, PpTaskFunc func, s8 tag);
void func_8010BAA8_puddle_paddle(s8 group, PpTask* task);
void func_8010BC14_puddle_paddle(s8 group);
s16 func_8010BEE8_puddle_paddle(u16 prio, s32 dir, s32 file, u16 arg3, s32 attr);
void func_8010C088_puddle_paddle(s16 sprite, s32 x, s32 y);
void func_8010C16C_puddle_paddle(void);
s16 func_8010C214_puddle_paddle(s32 dir, s32 file, f32 freq, s16 tag, s32 attr, s32 arg5);
void func_8010C664_puddle_paddle(void);
s16 func_8010C804_puddle_paddle(s32 dir, s32 file, s16 tag, s32 attr, s32 arg4);
void func_8010CCF0_puddle_paddle(void);
void func_80110714_puddle_paddle(omObjData* obj);
// this range
void func_801059BC_puddle_paddle(void);
void func_80105B94_puddle_paddle(void);
void func_80105C3C_puddle_paddle(omObjData* obj);
void func_80105C84_puddle_paddle(omObjData* obj);
void func_80105CBC_puddle_paddle(omObjData* obj);
void func_80105CE0_puddle_paddle(void);
void func_80105DBC_puddle_paddle(omObjData* obj);
void func_80106028_puddle_paddle(omObjData* obj);
void func_80106064_puddle_paddle(omObjData* obj);
void func_80106958_puddle_paddle(omObjData* obj);
void func_80106988_puddle_paddle(omObjData* obj);
void func_801069FC_puddle_paddle(omObjData* obj);
void func_80106B6C_puddle_paddle(s16 dst, s16 src, u16 part);
void func_80106CE4_puddle_paddle(omObjData* obj);
void func_801073AC_puddle_paddle(omObjData* obj);
void func_801073E4_puddle_paddle(omObjData* obj);
void func_80107588_puddle_paddle(omObjData* obj);
void func_801075B8_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_80107638_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_8010788C_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_801079D4_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_80107B2C_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_80107DB0_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_80107E1C_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_80108178_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_80108368_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_801087DC_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_801094C4_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_80109718_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_80109804_puddle_paddle(PpPlayer* player, s16 motion, s8 pending);

void func_801059A0_puddle_paddle(void) {
    func_801059BC_puddle_paddle();
}

void func_801059BC_puddle_paddle(void) {
    u8 cam;

    Hu3DAnimInit(50);
    func_800142A0_main(48);
    omInitObjMan(50, 0);
    func_8004A208_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 5000.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_8010B820_puddle_paddle();
    func_80105B94_puddle_paddle();
    omAddObj(1000, 0, 0, -1, func_80105DBC_puddle_paddle);
    omAddObj(2000, 0, 0, -1, func_80105C3C_puddle_paddle);
    func_80045010_main(D_80111370_puddle_paddle, 1);
    func_80045010_main(D_8011137C_puddle_paddle, 1);
    func_80045010_main(D_8011138C_puddle_paddle, 1);
}

void func_80105B94_puddle_paddle(void) {
    D_80111658_puddle_paddle = HuMemAllocTag(sizeof(PpState), 31000);
    memset(D_80111658_puddle_paddle, 0, sizeof(PpState));
    D_80111658_puddle_paddle->coins = HuMemAllocTag(sizeof(PpCoin) * 16, 31000);
    memset(D_80111658_puddle_paddle->coins, 0, sizeof(PpCoin) * 16);
    D_80111654_puddle_paddle = HuMemAllocTag(sizeof(PpPlayer) * 4, 31000);
    memset(D_80111654_puddle_paddle, 0, sizeof(PpPlayer) * 4);
    D_80111650_puddle_paddle = HuMemAllocTag(sizeof(PpTeam) * 2, 31000);
    memset(D_80111650_puddle_paddle, 0, sizeof(PpTeam) * 2);
}

void func_80105C3C_puddle_paddle(omObjData* obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_80105C84_puddle_paddle;
    }
}

void func_80105C84_puddle_paddle(omObjData* obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_80105CBC_puddle_paddle;
    }
}

void func_80105CBC_puddle_paddle(omObjData* obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80105CE0_puddle_paddle(void) {
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
    func_8010BC14_puddle_paddle(0);
}

void func_80105DBC_puddle_paddle(omObjData* obj) {
    s16 i;
    PpTeam* team;
    s8 n;

    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    func_8010B8B4_puddle_paddle(NULL, 0, 0, 4);
    func_8010BA04_puddle_paddle(0, 0, NULL, func_801075B8_puddle_paddle, 0);
    PP_WORK(obj)->w.group = 1;
    func_8010B8B4_puddle_paddle(obj, PP_WORK(obj)->b.group, 0, 4);
    D_800EC1C0_minigame[0] = omAddObj(10, 1, 2, -1, func_80106064_puddle_paddle);
    D_800EC1C0_minigame[1] = omAddObj(10, 1, 0, -1, func_80106988_puddle_paddle);
    omSetStatBit(D_800EC1C0_minigame[1], 0xA0);
    for (i = 0; i < 4; i++) {
        team = &D_80111650_puddle_paddle[D_80111654_puddle_paddle[i].team = GwPlayer[i].group];
        D_80111654_puddle_paddle[i].slot = team->count;
        n = team->count++;
        team->member[n] = i;
    }
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(300, 11, 42, -1, func_80106CE4_puddle_paddle);
    }
    omAddObj(500, 2, 0, -1, func_801073E4_puddle_paddle);
    D_80111658_puddle_paddle->flags = 1;
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0xF, NULL, func_801079D4_puddle_paddle, 0);
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0x1F, NULL, func_80107638_puddle_paddle, 0);
    WipeCreateIn(0xFF, 20);
    obj->func = func_80106028_puddle_paddle;
}

void func_80106028_puddle_paddle(omObjData* obj) {
    func_8010BC14_puddle_paddle(PP_WORK(obj)->b.group);
    func_80105CE0_puddle_paddle();
    func_8010C16C_puddle_paddle();
    func_8010C664_puddle_paddle();
    func_8010CCF0_puddle_paddle();
}

/* D_800CBB60_main's 0x24-byte sprite models (14EA0.c unk_800ECDE0): only the model number is read here */
typedef struct PpSprModel {
    /* 0x00 */ u16 model;
    /* 0x02 */ char unk02[0x1E];
    /* 0x20 */ u8* unk20;
} PpSprModel;
extern PpSprModel* D_800CBB60_main;
u16 func_80014618_main(s16 index, u16 arg1);

typedef struct PpFiles8 {
    s32 v[8];
} PpFiles8;
typedef struct PpFiles3 {
    s32 v[3];
} PpFiles3;
typedef struct PpShort3 {
    s16 v[3];
} PpShort3;
extern PpFiles8 D_80111398_puddle_paddle; /* character icon files */
extern PpFiles3 D_801113B8_puddle_paddle; /* coin sprite files */
extern PpShort3 D_801113C4_puddle_paddle; /* coins of each kind */
extern PpShort3 D_801113CC_puddle_paddle; /* the kinds */

/* The pond: the raft, coins, effects and score sprites. NON_MATCHING: masked 0, spr and first swap s5/s6. */
#ifdef NON_MATCHING
void func_80106064_puddle_paddle(omObjData* obj) {
    PpFiles8 icons = D_80111398_puddle_paddle;
    PpFiles3 files = D_801113B8_puddle_paddle;
    PpShort3 counts = D_801113C4_puddle_paddle;
    PpShort3 kinds = D_801113CC_puddle_paddle;
    PpCtx* ctx;
    s16 sprite;
    s16 i;
    s16 j;
    s16 model;
    s16 first;
    s32 spr;
    void* data;

    PP_WORK(obj)->w.group = 2;
    ctx = func_8010B8B4_puddle_paddle(obj, PP_WORK(obj)->b.group, 6, 6)->ctx;
    ctx->models[0] = func_8000B108_main(0xA0117, 0x2D9);
    ctx->models[1] = func_8000B108_main(0x320000, 0x2D9);
    ctx->models[2] = func_8000B108_main(9, 0x2D9);
    func_8000B460_main(obj, 0, 0xA0118);
    func_8000B460_main(obj, 1, 0xA0119);
    spr = 0;
    func_8001C5B4_main(ctx->models[0], obj->motion[0]);
    func_8001C814_main(ctx->models[0], 2, 2);
    Hu3DModelScaleSet(ctx->models[1], 0.8f, 0.8f, 0.8f);
    Hu3DModelScaleSet(ctx->models[0], 1.2f, 1.2f, 1.2f);
    Hu3DModelPosSet(ctx->models[0], 0.0f, 325.0f, 0.0f);
    Hu3DModelScaleSet(ctx->models[2], 1.2f, 1.2f, 1.2f);
    Hu3DModelPosSet(ctx->models[2], 0.0f, 320.0f, 0.0f);
    D_80111658_puddle_paddle->unk3C = func_8000D658_main(0x6A9, 4);
    first = 0;
    for (i = 0; i < 3; i++) {
        for (j = first; j < first + counts.v[i]; j++) {
            D_80111658_puddle_paddle->coins[j].kind = kinds.v[i];
            D_80111658_puddle_paddle->coins[j].unk20 = 50.0f;
            if (j == first) {
                data = DataRead(files.v[i]);
                spr = HmfSprModelCreate(data, 0x9D, 0);
                model = spr;
                DataClose(data);
            } else {
                model = func_80014618_main(spr, 0);
            }
            D_80111658_puddle_paddle->coins[j].model = D_800CBB60_main[model].model;
            Hu3DModelScaleSet(D_800CBB60_main[model].model, 3.0f, 3.0f, 1.0f);
        }
        first += counts.v[i];
    }
    for (i = 0; i < 14; i++) {
        func_8010C214_puddle_paddle(50, 3, 1.0f, 0, 0, 0x499);
    }
    for (i = 0; i < 2; i++) {
        func_8010C214_puddle_paddle(0, 8, 1.0f, 1, 0, 0x499);
    }
    for (i = 0; i < 16; i++) {
        Hu3DModelScaleSet(D_80111668_puddle_paddle[func_8010C804_puddle_paddle(50, 22, 0, 0, 11)].model, 1.5f, 1.5f, 1.5f);
    }
    sprite = func_8010BEE8_puddle_paddle(0xFFF, 50, 21, 0, 0x1000);
    func_80055458_main(D_80111664_puddle_paddle[sprite].group, 0, 200);
    func_8010C088_puddle_paddle(sprite, 76, 32);
    sprite = func_8010BEE8_puddle_paddle(0xFFF, 50, 21, 0, 0x1000);
    func_80055458_main(D_80111664_puddle_paddle[sprite].group, 0, 200);
    func_8010C088_puddle_paddle(sprite, 236, 32);
    func_8010C088_puddle_paddle(func_8010BEE8_puddle_paddle(0xFF, 33, 26, 0, 0), 76, 32);
    func_8010C088_puddle_paddle(func_8010BEE8_puddle_paddle(0xFF, 33, 26, 0, 0), 236, 32);
    func_8010C088_puddle_paddle(func_8010BEE8_puddle_paddle(0xFF, 33, 27, 0, 0), 92, 32);
    func_8010C088_puddle_paddle(func_8010BEE8_puddle_paddle(0xFF, 33, 27, 0, 0), 252, 32);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            func_8010C088_puddle_paddle(
                func_8010BEE8_puddle_paddle(0xEF, 33, icons.v[GwPlayer[D_80111650_puddle_paddle[i].member[j]].chr], 0, 0),
                (s16)(i * 160 + 40 + j * 18), 32);
        }
    }
    for (i = 0; i < 2; i++) {
        D_80111650_puddle_paddle[i].digit[0] = model = func_8010BEE8_puddle_paddle(0xEF, 0, 49, 0, 0);
        func_8010C088_puddle_paddle(model, (s16)(i * 160 + 104), 32);
        D_80111650_puddle_paddle[i].digit[1] = model = func_8010BEE8_puddle_paddle(0xEF, 0, 49, 0, 0);
        func_8010C088_puddle_paddle(model, (s16)(i * 160 + 116), 32);
    }
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0xF, NULL, func_80107E1C_puddle_paddle, 0);
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0xFF, NULL, func_80108178_puddle_paddle, 0);
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0x1FF, NULL, func_80108368_puddle_paddle, 0);
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0xFFF, NULL, func_801087DC_puddle_paddle, 0);
    obj->model[0] = ctx->models[0];
    func_80110714_puddle_paddle(obj);
    obj->func = func_80106958_puddle_paddle;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106064_puddle_paddle);
#endif

void func_80106958_puddle_paddle(omObjData* obj) {
    func_8010BC14_puddle_paddle(2);
    func_80110714_puddle_paddle(obj);
}

void func_80106988_puddle_paddle(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0x320001, 0x20099);
    Hu3DModelPosSet(obj->model[0], 0.0f, 200.0f, 0.0f);
    func_8001C954_main(obj->model[0]);
    func_80110714_puddle_paddle(obj);
    obj->func = func_801069FC_puddle_paddle;
}

void func_801069FC_puddle_paddle(omObjData* obj) {
    func_8001E65C_main(obj->model[0], sindf(D_80111220_puddle_paddle) * 15.0f, -D_80111224_puddle_paddle, 64, 64);
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_80111220_puddle_paddle += 0.5f;
        if (D_80111220_puddle_paddle >= 360.0f) {
            D_80111220_puddle_paddle -= 360.0f;
        }
        D_80111224_puddle_paddle += 0.2f;
        if (D_80111224_puddle_paddle >= 64.0f) {
            D_80111224_puddle_paddle -= 64.0f;
        }
        D_80111228_puddle_paddle += 2.4f;
        if (D_80111228_puddle_paddle >= 360.0f) {
            D_80111228_puddle_paddle -= 360.0f;
        }
    }
    func_80110714_puddle_paddle(obj);
}

/* Hands a part of model src over to model dst: the part (by number) is removed from src's object list and its
   draw points at dst's HmfData. Reads HmfData fields the shared header does not name yet (N64 offsets). */
typedef struct PpHmfObj {
    /* 0x00 */ s16 part;
    /* 0x02 */ char unk02[0x46];
    /* 0x48 */ HmfData* hmf;
    /* 0x4C */ char unk4C[0x40];
} PpHmfObj; /* size 0x8C */

typedef struct PpHmfGroup {
    /* 0x00 */ s16 count;
    /* 0x02 */ char unk02[0x4E];
    /* 0x50 */ s16* parts;
    /* 0x54 */ HmfData* hmf;
    /* 0x58 */ char unk58[0x40];
} PpHmfGroup; /* size 0x98 */

typedef struct PpHmfView {
    /* 0x00 */ char unk00[0x16];
    /* 0x16 */ s16 groupCount;
    /* 0x18 */ char unk18[0x4C];
    /* 0x64 */ s16 objCount;
    /* 0x68 */ PpHmfObj* objs;
    /* 0x6C */ char unk6C[0x14];
    /* 0x80 */ PpHmfGroup* groups;
} PpHmfView;

void func_80106B6C_puddle_paddle(s16 dst, s16 src, u16 part) {
    PpHmfView* from = (PpHmfView*)HmfModelData[src].hmf;
    HmfData* to = HmfModelData[dst].hmf;
    PpHmfGroup* group;
    PpHmfObj* obj;
    s16 i;
    s16 j;
    s16 none = 0;

    if (from->groups == (PpHmfGroup*)-1) {
        for (i = 0; i < from->objCount; i++) {
            obj = &from->objs[i];
            if (obj->part == part) {
                obj->hmf = to;
                obj->part = none;
            }
        }
    } else {
        for (i = 0; i < from->groupCount; i++) {
            group = &from->groups[i];
            for (j = 0; j < group->count; j++) {
                if (group->parts[j] == part) {
                    group->hmf = to;
                    group->parts[j] = none;
                    break;
                }
            }
        }
    }
}

typedef struct PpHandNames {
    char name[8][2][32]; /* per character: the left and right hand parts */
} PpHandNames;
typedef struct PpTeamPos {
    Vec pos[2];
} PpTeamPos;
extern PpFiles8 D_801113D4_puddle_paddle; /* paddle models per character */
extern PpFiles8 D_801113F4_puddle_paddle; /* second paddle models per character */
extern PpHandNames D_80111414_puddle_paddle;
extern PpTeamPos D_80111614_puddle_paddle; /* each team's raft */
s16 func_8002C834_main(HmfData* hmf, char* name);

/* A player object. NON_MATCHING: the two D_800A178C/D_800A1790 loads for func_800E1BA8_minigame are scheduled
   after the a3 and stack arguments instead of before (same as Broadside func_80107140). */
#ifdef NON_MATCHING
void func_80106CE4_puddle_paddle(omObjData* obj) {
    s32 attr = 0x2B9;
    PpFiles8 paddles = D_801113D4_puddle_paddle;
    PpFiles8 paddles2 = D_801113F4_puddle_paddle;
    PpHandNames hands = D_80111414_puddle_paddle;
    f32 angles[2] = { 0.0f, 180.0f };
    PpTeamPos rafts = D_80111614_puddle_paddle;
    PpPlayer* player;
    s16 model;
    f32 angle;

    obj->work[0] = D_800EC280_minigame;
    obj->work[1] = D_800EC280_minigame + 3;
    player = &D_80111654_puddle_paddle[obj->work[0]];
    player->chr = GwPlayer[obj->work[0]].chr;
    func_800E1BA8_minigame(obj, D_800A178C_main[player->chr][0], D_800A1790_main[player->chr][0],
                           PP_WORK(obj)->b.player, attr, attr);
    obj->model[9] = model = func_8000B108_main(paddles.v[player->chr] | 0x320000, attr);
    D_8011122C_puddle_paddle = func_8002C834_main(HmfModelData[obj->model[0]].hmf, hands.name[player->chr][0]);
    func_80106B6C_puddle_paddle(model, obj->model[0], D_8011122C_puddle_paddle);
    obj->model[10] = model = func_8000B108_main(paddles2.v[player->chr] | 0x320000, attr);
    D_8011122C_puddle_paddle = func_8002C834_main(HmfModelData[obj->model[0]].hmf, hands.name[player->chr][1]);
    func_80106B6C_puddle_paddle(model, obj->model[0], D_8011122C_puddle_paddle);
    obj->trans.z = 200.0f;
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(player->chr, 0x98), 0, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(player->chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 13, func_80017BB8_main(player->chr, 0x9E), 1, 0);
    func_800E5A00_minigame(obj, 14, func_80017BB8_main(player->chr, 0x37), 1, 999);
    func_800E5A00_minigame(obj, 38, func_80017BB8_main(player->chr, 0x92), 0, 0);
    func_800E5A00_minigame(obj, 40, func_80017BB8_main(player->chr, 0x93), 0, 0);
    func_800E5A00_minigame(obj, 39, func_80017BB8_main(player->chr, 0x94), 0, 0);
    func_800E5A00_minigame(obj, 41, func_80017BB8_main(player->chr, 0x95), 0, 0);
    func_80109804_puddle_paddle(player, 0, 1);
    func_800E5690_minigame(obj, 0);
    player->unk0E = -1;
    player->unk48 = angles[player->slot];
    angle = player->unk48 + D_80111650_puddle_paddle[player->team].unk18;
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    Hu3DModelPosSet(obj->model[0], rafts.pos[player->team].x + sindf(angle) * 20.0f * 5.0f * 0.7f,
                    rafts.pos[player->team].y + 37.0f, rafts.pos[player->team].z + cosdf(angle) * 20.0f * 5.0f * 0.7f);
    player->no = ((func_800E1BA8_minigame_ObjData*)obj->data)->unk57;
    player->unk04 = 1;
    player->unk56 = 0;
    player->unk58 = 0;
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    obj->scale.z = 1.0f;
    obj->scale.y = 1.0f;
    obj->scale.x = 1.0f;
    D_800EC280_minigame++;
    func_8010B8B4_puddle_paddle(obj, PP_WORK(obj)->b.group, 0, 4);
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0xF, player, func_801094C4_puddle_paddle, 0);
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0xFFFF, player, func_80109718_puddle_paddle, 0);
    obj->func = func_801073AC_puddle_paddle;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106CE4_puddle_paddle);
#endif

void func_801073AC_puddle_paddle(omObjData* obj) {
    func_8010BC14_puddle_paddle(PP_WORK(obj)->b.group);
    func_800E4E30_minigame(obj);
    func_80110714_puddle_paddle(obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801073E4_puddle_paddle);

void func_80107588_puddle_paddle(omObjData* obj) {
    func_8010BC14_puddle_paddle(PP_WORK(obj)->b.group);
    func_80110714_puddle_paddle(obj);
}

void func_801075B8_puddle_paddle(PpCtx* ctx, PpTask* task) {
    Center.x = 0.0f;
    Center.y = 280.0f;
    Center.z = 102.0f;
    CRot.x = 321.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2970.0f;
    func_8010BAA8_puddle_paddle(0, task);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107638_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010788C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801079D4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107B2C_puddle_paddle);

void func_80107DB0_puddle_paddle(PpCtx* ctx, PpTask* task) {
    switch (task->state) {
        case 0:
            WipeCreateOut(0, 20);
            task->state = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109804_puddle_paddle);

void func_80109814_puddle_paddle(UnkPuddlePaddle *arg0, s16 arg1) {
    arg0->unk_0E = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010981C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109BD4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010A224_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010A398_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010ABCC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010B574_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010B820_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010B8B4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BA04_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BAA8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BB00_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BBB4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BC14_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BD18_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BEE8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C088_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C11C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C16C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C214_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C324_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C42C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C4D0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C664_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C804_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C98C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CA30_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CAD4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CC64_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CC9C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CCF0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CE74_puddle_paddle);

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
