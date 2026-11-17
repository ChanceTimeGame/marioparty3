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
#include "game/util.h"
#include "game/audio.h"

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
    /* 0x2A */ s16 score;
    /* 0x2C */ s16 leader; /* the player who sets the pace */
    /* 0x2E */ char unk2E[0x36];
} PpTeam; /* size 0x64 */

/* A player (D_80111654_puddle_paddle[4]) */
typedef struct PpPlayer {
    /* 0x00 */ s16 no; /* controller port */
    /* 0x02 */ s16 chr;
    /* 0x04 */ s32 flags; /* 1, 2 steer right, 4 steer left, 8 paddled, 0x10 */
    /* 0x08 */ s8 pending; /* motion pending */
    /* 0x0A */ s16 motion;
    /* 0x0C */ char unk0C[2];
    /* 0x0E */ s16 unk0E; /* next motion, -1 none */
    /* 0x10 */ s8 slot; /* place in the team */
    /* 0x11 */ char unk11[0x37];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 power;
    /* 0x50 */ s16 team;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56; /* won */
    /* 0x58 */ s16 unk58;
    /* 0x5A */ char unk5A[2];
} PpPlayer; /* size 0x5C */

/* A coin (PpState::coins[16]) */
typedef struct PpCoin {
    /* 0x00 */ s16 kind;
    /* 0x02 */ s16 model;
    /* 0x04 */ u8 state; /* 0 off, 1 falling, 2 splash, 3 floating, 4 sinking */
    /* 0x08 */ Vec vel;
    /* 0x14 */ f32 vy0;
    /* 0x18 */ s16 time;
    /* 0x1A */ s16 life; /* frames afloat */
    /* 0x1C */ s16 count;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 spin;
    /* 0x28 */ f32 spinSpeed;
    /* 0x2C */ char unk2C[8];
} PpCoin; /* size 0x34 */

/* The game state (D_80111658_puddle_paddle) */
typedef struct PpState {
    /* 0x00 */ s32 flags; /* 1 start, 2 play, 4 end */
    /* 0x04 */ f32 timer;
    /* 0x08 */ char unk08[0x30];
    /* 0x38 */ PpCoin* coins;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ char unk3E[2];
    /* 0x40 */ s16 unk40;
    /* 0x42 */ char unk42[2];
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
void func_8010C11C_puddle_paddle(s16 sprite);
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
    player->flags = 1;
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

void func_80109BD4_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_8010A224_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_8010A398_puddle_paddle(PpCtx* ctx, PpTask* task);
void func_8010ABCC_puddle_paddle(PpCtx* ctx, PpTask* task);

/* The two rafts */
void func_801073E4_puddle_paddle(omObjData* obj) {
    s32 attr = 0x99;
    PpTeamPos rafts = D_80111614_puddle_paddle;
    PpCtx* ctx;
    s16 i;

    PP_WORK(obj)->w.group = 7;
    ctx = func_8010B8B4_puddle_paddle(obj, PP_WORK(obj)->b.group, 2, 6)->ctx;
    for (i = 0; i < 2; i++) {
        ctx->models[i] = func_8000B108_main(0x320002, attr);
        Hu3DModelPosSet(ctx->models[i], rafts.pos[i].x, rafts.pos[i].y, rafts.pos[i].z);
    }
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0xFF, NULL, func_8010A398_puddle_paddle, 0);
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0xFFF, NULL, func_80109BD4_puddle_paddle, 0);
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0x1FFF, NULL, func_8010A224_puddle_paddle, 0);
    func_8010BA04_puddle_paddle(PP_WORK(obj)->b.group, 0xFFFF, NULL, func_8010ABCC_puddle_paddle, 0);
    obj->model[0] = ctx->models[0];
    func_80110714_puddle_paddle(obj);
    obj->func = func_80107588_puddle_paddle;
}

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

/* The score digits */
void func_80107638_puddle_paddle(PpCtx* ctx, PpTask* task) {
    s16 i;
    s16 ones;
    s16 tens;

    for (i = 0; i < 2; i++) {
        if (D_80111650_puddle_paddle[i].score < 100) {
            ones = D_80111650_puddle_paddle[i].score % 10;
            tens = D_80111650_puddle_paddle[i].score * 0.1f;
            if (tens != 0) {
                func_8010C088_puddle_paddle(D_80111650_puddle_paddle[i].digit[0], (s16)(i * 160 + 104), 32);
            } else {
                func_8010C11C_puddle_paddle(D_80111650_puddle_paddle[i].digit[0]);
            }
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].digit[0]].group, 0, tens);
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].digit[1]].group, 0, ones);
        } else {
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].digit[0]].group, 0, 9);
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].digit[1]].group, 0, 9);
        }
    }
}

/* The timer. NON_MATCHING only because of the data split: GCC folds timer / 30.0f to the double 30.0 and gas puts
   that li.d literal in this unit's .rodata, which is D_80111630_puddle_paddle (the yaml has it at the end of .data).
   The code is identical once the unit's .rodata starts at 0x19CED0 and D_80111630 is not also defined as data. */
#ifdef NON_MATCHING
void func_8010788C_puddle_paddle(PpCtx* ctx, PpTask* task) {
    if (task->state == 0) {
        D_80111658_puddle_paddle->timer = 900.0f;
        /* retail passes the seconds as a double where GMesCreate reads an int */
        GMesCreate(0x1A, D_80111658_puddle_paddle->timer / 30.0f, 160, 28);
        task->state = 1;
    }
    D_80111658_puddle_paddle->timer -= 1.0f;
    func_8003F578_main((D_80111658_puddle_paddle->timer + 29.0f) * 0.033333335f);
    if (D_80111658_puddle_paddle->timer < 0.0f) {
        D_80111658_puddle_paddle->flags = 4;
        HuAudSeqFadeOut(120);
        GMesCreate(0x10);
        func_8003F5C0_main();
        func_8010BA04_puddle_paddle(PP_WORK(ctx->obj)->b.group, 0, NULL, func_80107B2C_puddle_paddle, 0);
        func_8010BAA8_puddle_paddle(PP_WORK(ctx->obj)->b.group, task);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010788C_puddle_paddle);
#endif

void func_8010B574_puddle_paddle(void);

/* The start */
void func_801079D4_puddle_paddle(PpCtx* ctx, PpTask* task) {
    s32 stat;

    switch (++task->s16[0]) {
        case 5:
            HuAudFXPlay(0x374);
            break;
        case 30:
            GMesCreate(5);
            HuAudFXPlay(14);
            break;
        case 50:
            D_8011122E_puddle_paddle = 1;
            break;
        default:
            if (D_8011122E_puddle_paddle == 1 && (stat = GMesStatGet()) == 2) {
                func_8010B574_puddle_paddle();
                func_8010BA04_puddle_paddle(PP_WORK(ctx->obj)->b.group, 0xF, NULL, func_8010788C_puddle_paddle, 0);
                D_80111658_puddle_paddle->flags = stat;
                func_8010BAA8_puddle_paddle(PP_WORK(ctx->obj)->b.group, task);
            }
            break;
    }
    if (D_80111230_puddle_paddle == 0 && GMesStatGet() != 0) {
        HuAudSeqPlay(0x30);
        D_80111230_puddle_paddle = 1;
    }
}

/* The result: the winners cheer, then the wipe out */
void func_80107B2C_puddle_paddle(PpCtx* ctx, PpTask* task) {
    s16 won[2];
    s16 i;
    s16 j;

    if (GMesStatGet() == 0) {
        D_80111232_puddle_paddle = 1;
    }
    if (D_80111232_puddle_paddle != 0) {
        switch (++task->s16[0]) {
            case 15:
                won[1] = 0;
                won[0] = 0;
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 2; j++) {
                        if (D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].member[j]].unk56 != 0) {
                            func_80109804_puddle_paddle(&D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].member[j]], 13, 1);
                            func_8004AC98_main(GwPlayer[D_80111650_puddle_paddle[i].member[j]].chr + 0x290,
                                               D_80111650_puddle_paddle[i].member[j]);
                            D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].member[j]].unk58 = -1;
                            D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].member[j]].unk0E = -1;
                            won[i] = 1;
                        }
                    }
                }
                if (won[0] != 0 && won[1] != 0) {
                    HuAudSeqPlay(0x66);
                } else if (won[0] != 0 || won[1] != 0) {
                    HuAudSeqPlay(0x65);
                } else {
                    HuAudSeqPlay(0x6C);
                }
                break;
            case 140:
                func_8010BA04_puddle_paddle(PP_WORK(ctx->obj)->b.group, 0, NULL, func_80107DB0_puddle_paddle, 0);
                func_8010BAA8_puddle_paddle(PP_WORK(ctx->obj)->b.group, task);
                break;
        }
    }
}

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

void func_80110BBC_puddle_paddle(f32* a, f32* b);

/* The pond turns: at random while playing, back to 0 at the end */
void func_80107E1C_puddle_paddle(PpCtx* ctx, PpTask* task) {
    HmfModel* model = &HmfModelData[ctx->models[0]];
    f32 from;
    f32 to;

    if (!(D_80111658_puddle_paddle->flags & 1) && D_80111658_puddle_paddle->unk40 == 0) {
        if (D_80111658_puddle_paddle->flags & 4) {
            if (task->s16[0] == 0) {
                from = model->rot.y;
                to = 0.0f;
                func_80110BBC_puddle_paddle(&from, &to);
                if (model->rot.y >= 360.0f) {
                    model->rot.y -= 360.0f;
                } else if (model->rot.y < 0.0f) {
                    model->rot.y += 360.0f;
                }
                if ((model->rot.y > 0.0f ? model->rot.y : -model->rot.y) <= 2.0f) {
                    task->s16[0] = 1;
                }
                if (from - to > 0.0f) {
                    model->rot.y -= 2.0f;
                } else if (from - to < 0.0f) {
                    model->rot.y += 2.0f;
                }
            }
        } else {
            if (task->s8[0] == 0) {
                task->s8[0] = 1;
                task->f32[0] = rand16() % 361;
            }
            from = model->rot.y;
            to = task->f32[0];
            func_80110BBC_puddle_paddle(&from, &to);
            if ((model->rot.y - task->f32[0] > 0.0f ? model->rot.y - task->f32[0] : -(model->rot.y - task->f32[0])) < 5.0f) {
                task->s8[0] = 0;
            }
            if (from - to > 0.0f) {
                model->rot.y -= 1.0f;
            } else if (from - to < 0.0f) {
                model->rot.y += 1.0f;
            }
        }
    }
}

/* The thrower's motion: every 40 to 100 frames of play it throws (motion 1), then idles (motion 0).
   NON_MATCHING: masked 2, the last test loads HmfModel::unk40 before the D_800CCF58_main index in retail. */
#ifdef NON_MATCHING
void func_80108178_puddle_paddle(PpCtx* ctx, PpTask* task) {
    omObjData* obj = ctx->obj;

    if (!(D_80111658_puddle_paddle->flags & 2)) {
        task->s16[0] = 0;
    }
    if (task->state == 0) {
        task->s16[0] = 0;
        task->s16[1] = 10;
        D_80111658_puddle_paddle->unk40 = 0;
        task->state = 1;
    }
    if (D_80111658_puddle_paddle->unk40 == 0) {
        if (++task->s16[0] > task->s16[1]) {
            func_8001C5B4_main(ctx->models[0], obj->motion[1]);
            func_8001C92C_main(ctx->models[0], 2.0f);
            func_8001C6A8_main(obj->model[0], 0.0f);
            D_80111658_puddle_paddle->unk40 = 1;
            task->s16[0] = 0;
            task->s16[1] = (f32)(rand16() % 61 + 40);
        }
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
            func_8001C5B4_main(ctx->models[0], obj->motion[0]);
            func_8001C92C_main(ctx->models[0], 1.0f);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108178_puddle_paddle);
#endif

extern s16 D_80111234_puddle_paddle; /* coins since the last kind-1 coin */
s16 func_8010910C_puddle_paddle(s16 kind);
void func_80108E2C_puddle_paddle(s16 coin, s16 kind, f32 angle, f32 speed, s16 model);

/* Throws 2 to 4 coins at angles at least 45 degrees apart when the throw motion reaches frame 30.
   NON_MATCHING: masked 0, chance and the angles pointer swap s3/s4. */
#ifdef NON_MATCHING
void func_80108368_puddle_paddle(PpCtx* ctx, PpTask* task) {
    omObjData* obj = ctx->obj;
    s16 chance;
    f32 angles[6];
    f32 time;
    f32 speed;
    f32 angle;
    f32 d;
    s16 count;
    s16 kind;
    s16 retry;
    s16 i;
    s16 j;

    if (D_80111658_puddle_paddle->unk40 != 0) {
        time = HmfModelData[obj->model[0]].unk40;
        if ((time >= 30.0f) & (time <= 35.0f)) {
            D_80111658_puddle_paddle->unk40 = 0;
            count = rand16() % 3 + 2;
            for (i = 0; i < count; i++) {
                chance = 65;
                if (D_80111234_puddle_paddle < 11) {
                    chance = rand16() % 101;
                }
                speed = rand16() % 41 + 30;
                do {
                    if (i == 0) {
                        angle = angles[0] = HmfModelData[ctx->models[0]].rot.y;
                    } else {
                        angle = angles[i] = rand16() % 360;
                    }
                    retry = 0;
                    for (j = 0; j < i; j++) {
                        if (i != j) {
                            d = angles[i] - angles[j];
                            if ((d > 0.0f ? d : -(angles[i] - angles[j])) < 45.0f) {
                                retry = 1;
                            }
                        }
                    }
                } while (retry != 0);
                kind = 0;
                if (chance < 61) {
                    D_80111234_puddle_paddle++;
                } else if (chance < 71) {
                    D_80111234_puddle_paddle = 0;
                    kind = 1;
                } else if (chance < 101) {
                    kind = 2;
                }
                func_80108E2C_puddle_paddle(func_8010910C_puddle_paddle(kind), kind, angle, speed, ctx->models[0]);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108368_puddle_paddle);
#endif

void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z);
s16 func_8010C42C_puddle_paddle(s16 tag);
void func_8010C4D0_puddle_paddle(s16 id, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, s32 arg8);
void func_80108D10_puddle_paddle(PpCtx* ctx, PpTask* task);

/* The coins: fall, splash, bob on the water, then sink blinking */
void func_801087DC_puddle_paddle(PpCtx* ctx, PpTask* task) {
    PpCoin* coin = D_80111658_puddle_paddle->coins;
    HmfModel* model;
    f32 t;
    s16 i;
    s16 id;

    for (i = 0; i < 16; i++, coin++) {
        if (coin->state == 0) {
            continue;
        }
        model = &HmfModelData[coin->model];
        model->rot.x = CRot.x;
        model->rot.y = CRot.y;
        if (coin->kind == 2) {
            coin->spin += coin->spinSpeed;
            if (coin->spin > 360.0f) {
                coin->spin -= 360.0f;
            }
            if (coin->spin < 0.0f) {
                coin->spin += 360.0f;
            }
            func_80088910_main((f32(*)[4])HmfModelData[coin->model].mtx, 0.0f, 0.0f, coin->spin);
        }
        if (D_80111658_puddle_paddle->flags & 4) {
            func_8010BA04_puddle_paddle(PP_WORK(ctx->obj)->b.group, 0xFFF, NULL, func_80108D10_puddle_paddle, 0);
            func_8010BAA8_puddle_paddle(PP_WORK(ctx->obj)->b.group, task);
            return;
        }
        switch (coin->state) {
            case 1:
                model->pos.x += coin->vel.x;
                model->pos.y += coin->vel.y;
                model->pos.z += coin->vel.z;
                coin->vel.y = coin->vy0 - ++coin->time * 2.45f;
                if (model->pos.y < 170.0f) {
                    id = func_8010C42C_puddle_paddle(0);
                    if (id != -1) {
                        func_8010C4D0_puddle_paddle(id, model->pos.x, 170.0f, model->pos.z, 0.0f, 0.0f, 0.0f, 1.0f, 0);
                    }
                    if (coin->kind != 2) {
                        coin->state = 2;
                        coin->time = 0;
                        coin->vel.y *= 0.25f;
                    } else {
                        coin->time = 0;
                        coin->count = 3;
                        coin->state = 4;
                        coin->vel.y = 2.45f;
                    }
                    switch (coin->kind) {
                        case 0:
                            HuAudFXPlay(0x376);
                            break;
                        case 1:
                            HuAudFXPlay(0x377);
                            break;
                        case 2:
                            HuAudFXPlay(0x37A);
                            break;
                    }
                }
                break;
            case 2:
                model->pos.y += coin->vel.y;
                coin->vel.y += 2.45f;
                if (model->pos.y >= 170.0f) {
                    coin->state = 3;
                    coin->vel.y = model->pos.y;
                }
                break;
            case 3:
                t = coin->time / 50.0f;
                if (t > 1.0f) {
                    t = 1.0f;
                }
                model->pos.y = sindf(t * 180.0f) * 20.0f * 5.0f * 0.4f + coin->vel.y;
                if (++coin->time >= 51) {
                    coin->time = 0;
                }
                if (++coin->count > coin->life) {
                    coin->time = 0;
                    coin->count = 3;
                    coin->state = 4;
                    coin->vel.y = 3.6750002f;
                }
                break;
            case 4:
                if (++coin->time < coin->count) {
                    func_8001C258_main(coin->model, 4, 4);
                } else {
                    coin->time = 0;
                    func_8001C258_main(coin->model, 4, 0);
                }
                model->pos.y -= coin->vel.y;
                if (model->pos.y < 0.0f) {
                    coin->state = 0;
                    func_8001C258_main(coin->model, 4, 4);
                }
                break;
        }
    }
}

s16 func_8010C98C_puddle_paddle(s16 tag);
void func_8010CA30_puddle_paddle(s16 id, f32 x, f32 y, f32 z);

/* At the end the coins left vanish in a puff */
void func_80108D10_puddle_paddle(PpCtx* ctx, PpTask* task) {
    PpCoin* coin = D_80111658_puddle_paddle->coins;
    HmfModel* model;
    s16 i;
    s16 id;

    for (i = 0; i < 16; i++, coin++) {
        if (coin->state == 0) {
            continue;
        }
        model = &HmfModelData[coin->model];
        if (coin->state == 5) {
            if (++coin->time >= 6) {
                func_8001C258_main(coin->model, 4, 4);
                coin->state = 0;
            }
        } else {
            coin->state = 5;
            coin->time = 0;
            id = func_8010C98C_puddle_paddle(0);
            if (id != -1) {
                func_8010CA30_puddle_paddle(id, model->pos.x, model->pos.y - 20.0f, model->pos.z);
            }
        }
    }
}

/* Launches a coin from the thrower: angle is the direction, speed the launch elevation in degrees.
   NON_MATCHING: the assembler puts a nop after the cosdf and the second sindf calls that retail lacks. */
#ifdef NON_MATCHING
void func_80108E2C_puddle_paddle(s16 index, s16 kind, f32 angle, f32 speed, s16 thrower) {
    PpCoin* coin;
    HmfModel* model;
    f32 scale;
    f32 x;
    f32 z;

    if (index != -1) {
        coin = &D_80111658_puddle_paddle->coins[index];
        scale = (rand16() % 6 + 20) * 0.01f;
        coin->vel.x = sindf(angle) * 20.0f * 5.0f * scale;
        coin->vel.z = cosdf(angle) * 20.0f * 5.0f * scale;
        coin->vy0 = coin->vel.y = sindf(speed) * 20.0f * 5.0f * 0.3f;
        coin->kind = kind;
        coin->state = 1;
        coin->time = 0;
        coin->count = 0;
        switch (kind) {
            case 0:
                coin->life = 250;
                break;
            case 1:
                coin->life = 150;
                break;
            case 2:
                if (angle < 180.0f) {
                    coin->spinSpeed = -20.0f;
                } else {
                    coin->spinSpeed = 20.0f;
                }
                break;
        }
        x = sindf(HmfModelData[thrower].rot.y) * 75.0f;
        z = cosdf(HmfModelData[thrower].rot.y) * 75.0f;
        func_8001C258_main(coin->model, 4, 0);
        model = &HmfModelData[thrower];
        Hu3DModelPosSet(coin->model, x + model->pos.x, model->pos.y + 50.0f, z + model->pos.z);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108E2C_puddle_paddle);
#endif

/* A free coin slot of a kind (0: 0-7, 1: 8-11, 2: 12-15), -1 if none */
s16 func_8010910C_puddle_paddle(s16 kind) {
    s16 end = 0;
    s16 start = 0;
    s16 i;

    switch (kind) {
        case 2:
            start += 4;
            end += 4;
        case 1:
            start += 8;
            end += 4;
        case 0:
            end += 8;
            break;
    }
    for (i = start; i < end; i++) {
        if (D_80111658_puddle_paddle->coins[i].state == 0) {
            break;
        }
    }
    if (i == end) {
        return -1;
    }
    return i;
}

/* A CPU player: paddles (button 0x8000) at a random interval set by its difficulty while its team's leader
   paddles */
void func_801091F8_puddle_paddle(PpCtx* ctx, PpTask* task) {
    omObjData* obj = ctx->obj;
    PpPlayer* p[2]; /* the player and its team's leader */

    if (D_80111658_puddle_paddle->flags & 2) {
        p[0] = task->data;
        p[1] = &D_80111654_puddle_paddle[D_80111650_puddle_paddle[p[0]->team].leader];
        if (task->state == 0) {
            switch (GwPlayer[obj->work[0]].cpu_difficulty) {
                case 0:
                    task->s8[0] = 4;
                    task->s8[1] = 8;
                    p[0]->unk52 = 20;
                    p[0]->unk54 = 15;
                    break;
                case 1:
                    task->s8[0] = 4;
                    task->s8[1] = 7;
                    p[0]->unk52 = 30;
                    p[0]->unk54 = 13;
                    break;
                case 2:
                    task->s8[0] = 3;
                    task->s8[1] = 6;
                    p[0]->unk52 = 40;
                    p[0]->unk54 = 11;
                    break;
                case 3:
                    task->s8[0] = 3;
                    task->s8[1] = 5;
                    p[0]->unk52 = 99;
                    p[0]->unk54 = 9;
                    break;
            }
            task->state = 1;
        }
        D_800CBB6E_main[p[0]->no] = 0;
        D_800D20A1_main[p[0]->no] = 0;
        D_800CDA7C_main[p[0]->no] = 0;
        if (obj->work[0] == D_80111650_puddle_paddle[p[0]->team].leader || (p[1]->flags & 8)) {
            if (++task->s16[0] > task->s16[1]) {
                task->s16[0] = 0;
                task->s16[1] = rand16() % (task->s8[1] - task->s8[0] + 1) + task->s8[0];
                ((u16*)D_800CDA7C_main)[p[0]->no] = 0x8000; /* the button bits are u16 */
            }
        }
    }
}

/* A player's paddling: each press adds power, which decays; the stick steers (flags 2 right, 4 left).
   NON_MATCHING: retail reads the stick with lbu and sign-extends it twice; this C gets one lb. */
#ifdef NON_MATCHING
void func_801094C4_puddle_paddle(PpCtx* ctx, PpTask* task) {
    PpPlayer* player = task->data;
    s32 flags = player->flags;
    u8 stick;

    player->flags = flags & ~6;
    if (!(flags & 0x10)) {
        if (D_80111658_puddle_paddle->flags & 2) {
            if (++task->s8[2] >= 7) {
                task->s8[2] = 6;
                player->flags &= ~8;
            }
            if ((u16)D_800CDA7C_main[player->no] & 0x8000) {
                if (task->s8[0] == 0) {
                    task->s8[0] = 1;
                    task->s8[2] = 0;
                    player->power += 0.05f;
                    player->flags |= 8;
                    if (player->power > 1.0f) {
                        player->power = 1.0f;
                    }
                }
            } else {
                task->s8[0] = 0;
            }
            if (task->s8[1] == 0) {
                task->s8[1] = 1;
                player->power -= sindf(player->power * 90.0f) * 0.025f;
                if (player->power < 0.0f) {
                    player->power = 0.0f;
                }
            } else {
                task->s8[1] = 0;
            }
            stick = (u8)D_800CBB6E_main[player->no];
            if (((s8)stick == 0) & (D_800D20A1_main[player->no] == 0)) {
                return;
            }
            if ((s8)stick < -7) {
                player->flags |= 4;
            } else if ((s8)stick >= 8) {
                player->flags |= 2;
            }
        } else {
            player->flags &= ~8;
            if (task->s8[1] == 0) {
                task->s8[1] = 1;
                player->power -= sindf(player->power * 90.0f) * 0.1f;
                if (player->power < 0.0f) {
                    player->power = 0.0f;
                }
            } else {
                task->s8[1] = 0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801094C4_puddle_paddle);
#endif

/* Plays the pending motion once the current one ends */
void func_80109718_puddle_paddle(PpCtx* ctx, PpTask* task) {
    PpPlayer* player = task->data;
    omObjData* obj = ctx->obj;
    HmfModel* model = &HmfModelData[obj->model[0]];

    if (player->unk58 != 1) {
        if (D_800CCF58_main[model->unk02].unk02 - 1 <= model->unk40) {
            player->pending = 1;
        }
        if (player->pending != 0) {
            func_800E5690_minigame(obj, player->motion);
            player->pending = 0;
            if (player->unk58 == -1) {
                player->unk58 = 1;
            }
            if (player->unk0E != -1) {
                player->motion = player->unk0E;
                player->unk0E = -1;
            }
        }
    }
}

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
