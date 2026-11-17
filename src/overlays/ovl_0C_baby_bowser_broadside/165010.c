#include "common.h"

#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// m1 bb1
/* Baby Bowser Broadside: two teams of two on a rotating ship deck, firing cannonballs at each other. */

/* omObjData::work of a player object and of the setup object: work[0] the player index (its low half read
   as a s16), work[1] the task group (its low byte read as a s8). Big-endian views of two words. */
typedef union BbObjWork {
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
} BbObjWork;
#define BB_WORK(obj) ((BbObjWork*)(obj)->work)

/* A task group's context (169540 func_80109F64_baby_bowser_broadside) */
typedef struct BbCtx {
    /* 0x00 */ omObjData* obj;
    /* 0x04 */ s16* models;
    /* 0x08 */ s16 count;
} BbCtx; /* size 0xC */

struct BbTask;
typedef void (*BbTaskFunc)(BbCtx*, struct BbTask*);

/* A task (169540 func_8010A0B4_baby_bowser_broadside) */
typedef struct BbTask {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 index;
    /* 0x04 */ s8 state;
    /* 0x05 */ u8 unk05;
    /* 0x08 */ s32 mask;
    /* 0x0C */ s8 unk0C;
    /* 0x0D */ s8 unk0D;
    /* 0x0E */ s8 unk0E;
    /* 0x0F */ s8 unk0F;
    /* 0x10 */ s8 unk10;
    /* 0x11 */ s8 unk11;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ s8 unk13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ char unk15[7];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ char unk20[0xC];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ char unk34[8];
    /* 0x3C */ void* data;
    /* 0x40 */ BbTaskFunc func;
} BbTask; /* size 0x44 */

/* A task group (169540 D_80110014_baby_bowser_broadside[7]) */
typedef struct BbGroup {
    /* 0x00 */ BbCtx* ctx;
    /* 0x04 */ BbTask* tasks;
    /* 0x08 */ s16 count;
    /* 0x0C */ void* order;
    /* 0x10 */ u8 dirty;
} BbGroup; /* size 0x14 */

/* A team (D_80110000_baby_bowser_broadside[2]) */
typedef struct BbTeam {
    /* 0x00 */ u8 count;
    /* 0x02 */ s16 member[2]; /* player indices */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 angle[2]; /* deck angle of each member's cannon */
    /* 0x10 */ s16 score;
    /* 0x12 */ s16 digit[2]; /* score digit sprites (169540 D_80110018_baby_bowser_broadside index) */
    /* 0x16 */ char unk16[2];
} BbTeam; /* size 0x18 */

/* A sphere collider (169540 func_8010E018_baby_bowser_broadside) */
typedef struct BbColl {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s16* hits;
    /* 0x08 */ char unk08[4];
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ char unk24[6];
    /* 0x2A */ s16 unk2A; /* hit a wall */
    /* 0x2C */ char unk2C[4];
    /* 0x30 */ s16 unk30; /* hit a target */
    /* 0x32 */ char unk32[2];
} BbColl; /* size 0x34 */

/* A cannonball (BbPlayer::balls[3]) */
typedef struct BbBall {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ Vec vel0; /* launch velocity */
    /* 0x10 */ Vec vel;
    /* 0x1C */ f32 unk1C; /* start height */
    /* 0x20 */ f32 time;
    /* 0x24 */ f32 angle;
    /* 0x28 */ s16 team;
    /* 0x2C */ BbColl* coll;
} BbBall; /* size 0x30 */

/* A player (D_80110004_baby_bowser_broadside[4]) */
typedef struct BbPlayer {
    /* 0x00 */ s16 no; /* player index */
    /* 0x02 */ s16 chr;
    /* 0x04 */ union {
        s32 w;
        struct {
            s16 hi;
            u16 lo; /* 1 + the ball to fire */
        } h;
    } fire;
    /* 0x08 */ s8 unk08; /* motion pending */
    /* 0x0A */ s16 unk0A; /* motion */
    /* 0x0C */ s16 unk_0C; /* next motion, -1 none */
    /* 0x0E */ char unk0E[2];
    /* 0x10 */ s8 held; /* fire button held */
    /* 0x11 */ char unk11[0xF];
    /* 0x20 */ s16 sePlaying;
    /* 0x22 */ s16 seNo;
    /* 0x24 */ char unk24[0x24];
    /* 0x48 */ s16 model; /* cannon */
    /* 0x4A */ char unk4A[2];
    /* 0x4C */ f32 aim;
    /* 0x50 */ f32 angle;
    /* 0x54 */ BbBall* balls;
    /* 0x58 */ s16 cooldown;
    /* 0x5A */ s16 team;
    /* 0x5C */ BbColl* aimColl;
} BbPlayer; /* size 0x60 */

typedef BbPlayer unk_80109EBC;

/* The game state (D_80110008_baby_bowser_broadside) */
typedef struct BbState {
    /* 0x00 */ s32 flags; /* 1 start, 2 play, 4 end */
    /* 0x04 */ f32 timer;
    /* 0x08 */ char unk08[0x10];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char unk1A[0xE];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ char unk2C[0xC];
    /* 0x38 */ f32 speed; /* deck rotation per frame */
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E[4];
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s16 unk48[4];
    /* 0x50 */ s16 model; /* the target */
    /* 0x52 */ u8 unk52; /* rocking */
    /* 0x53 */ char unk53[5];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ s8 unk60; /* target position from */
    /* 0x61 */ s8 unk61; /* to */
    /* 0x62 */ char unk62[2];
} BbState; /* size 0x64 */

/* An 8-byte sprite slot (169540 D_80110018_baby_bowser_broadside[14]) */
typedef struct BbSprite {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 group;
    /* 0x02 */ char unk02[6];
} BbSprite;

/* A 0x24 effect slot (169540 D_80110010_baby_bowser_broadside[8]) */
typedef struct BbEffect {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ s16 model;
    /* 0x0E */ char unk0E[0x16];
} BbEffect;

extern BbTeam* D_80110000_baby_bowser_broadside;
extern BbPlayer* D_80110004_baby_bowser_broadside;
extern BbState* D_80110008_baby_bowser_broadside;
extern s16 D_8011000C_baby_bowser_broadside;
extern BbEffect* D_80110010_baby_bowser_broadside;
extern BbGroup* D_80110014_baby_bowser_broadside;
extern BbSprite* D_80110018_baby_bowser_broadside;

extern s16 D_8010FD60_baby_bowser_broadside; /* the result is out */
extern f32 D_8010FD64_baby_bowser_broadside;
extern f32 D_8010FD68_baby_bowser_broadside;
extern f32 D_8010FD6C_baby_bowser_broadside;
extern s16 D_8010FD70_baby_bowser_broadside;
extern s16 D_8010FD72_baby_bowser_broadside;
extern s16 D_8010FD74_baby_bowser_broadside;
extern s16 D_8010FD76_baby_bowser_broadside;
extern s16 D_8010FD78_baby_bowser_broadside[6];
extern s16 D_8010FD84_baby_bowser_broadside[6];
extern s16 D_8010FEC0_baby_bowser_broadside[];
extern s16 D_8010FECC_baby_bowser_broadside[];
extern s16 D_8010FEDC_baby_bowser_broadside[];
extern Vec D_8010FEE8_baby_bowser_broadside;
extern Vec D_8010FEF4_baby_bowser_broadside[4][4];
extern s32 D_8010FFB4_baby_bowser_broadside[8];

// main
s32 func_8000B638_main(void);
void func_8001E65C_main(s16 mdl, f32 u, f32 v, s32 w, s32 h);
void func_8001F6BC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void func_8001F6F8_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
u8 rand8(void);
omObjData* func_80045ED0_main(u32 arg0);
f32 atan2df(f32 y, f32 x);
extern u8 D_800CB8B1_main[];
extern s8 D_800CBB6E_main[];
extern s16 D_800CDA7C_main[];
extern s8 D_800D20A1_main[];
extern u8 D_800D6A90_main;
extern s32 D_800A178C_main[][6];

// 169540
void func_80109ED0_baby_bowser_broadside(void);
void func_8010A81C_baby_bowser_broadside(void);
void func_8010ACF8_baby_bowser_broadside(void);
void func_8010B3B4_baby_bowser_broadside(void);
BbGroup* func_80109F64_baby_bowser_broadside(omObjData* obj, s8 group, s16 models, s16 tasks);
s16 func_8010A0B4_baby_bowser_broadside(s8 group, s32 mask, void* data, BbTaskFunc func, u8 arg4);
void func_8010A158_baby_bowser_broadside(s8 group, BbTask* task);
void func_8010A2C4_baby_bowser_broadside(s8 group);
void func_8010F250_baby_bowser_broadside(omObjData* obj);
void func_8010F6F8_baby_bowser_broadside(f32* a, f32* b);
void func_8010E0B0_baby_bowser_broadside(BbColl* coll);
s16 func_8010AADC_baby_bowser_broadside(s16 arg0);
s16 func_8010AFF4_baby_bowser_broadside(s16 arg0);
void func_8010B098_baby_bowser_broadside(s16 arg0, f32 x, f32 y, f32 z, u8* color);
void func_8010AB80_baby_bowser_broadside(s16 arg0, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, s32 arg8);

// this unit
void func_801059BC_baby_bowser_broadside(void);
void func_80105B94_baby_bowser_broadside(void);
void func_80105DE4_baby_bowser_broadside(omObjData* obj);
void func_80105E2C_baby_bowser_broadside(omObjData* obj);
void func_80105E64_baby_bowser_broadside(omObjData* obj);
void func_80105F64_baby_bowser_broadside(omObjData* obj);
void func_80106288_baby_bowser_broadside(omObjData* obj);
void func_801062C4_baby_bowser_broadside(omObjData* obj);
void func_80106E40_baby_bowser_broadside(omObjData* obj);
void func_80106E70_baby_bowser_broadside(omObjData* obj);
void func_80106EC4_baby_bowser_broadside(omObjData* obj);
void func_80107140_baby_bowser_broadside(omObjData* obj);
void func_80107600_baby_bowser_broadside(omObjData* obj);
void func_80107630_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_801076AC_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80107854_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80107A00_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80107A80_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80107C64_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80107FE0_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_801081A4_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80108210_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80108350_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80108614_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_801087CC_baby_bowser_broadside(s16 model);
void func_80108804_baby_bowser_broadside(f32 angle);
void func_80108860_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
s16 func_80109058_baby_bowser_broadside(omObjData* obj, BbPlayer* player);
void func_8010913C_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80109434_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_801096E8_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_801098F8_baby_bowser_broadside(BbBall* ball);
s16 func_80109970_baby_bowser_broadside(BbPlayer* player);
void func_801099D4_baby_bowser_broadside(omObjData* obj, BbBall* ball, f32 angle, s16 team);
void func_80109BD8_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80109D2C_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80109D94_baby_bowser_broadside(BbCtx* ctx, BbTask* task);
void func_80109EB0_baby_bowser_broadside(BbPlayer* player, s16 motion, s8 pending);
void func_80109EBC_baby_bowser_broadside(unk_80109EBC* arg0, s16 arg1);

/* <func_801059A0_baby_bowser_broadside> */
void func_801059A0_baby_bowser_broadside(void) {
    func_801059BC_baby_bowser_broadside();
}
/* </func_801059A0_baby_bowser_broadside> */

/* <func_801059BC_baby_bowser_broadside> */
void func_801059BC_baby_bowser_broadside(void) {
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
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 6000.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80109ED0_baby_bowser_broadside();
    func_80105B94_baby_bowser_broadside();
    omAddObj(1000, 0, 0, -1, func_80105F64_baby_bowser_broadside);
    omAddObj(2000, 0, 0, -1, func_80105DE4_baby_bowser_broadside);
    func_80045010_main(D_8010FEC0_baby_bowser_broadside, 1);
    func_80045010_main(D_8010FECC_baby_bowser_broadside, 1);
    func_80045010_main(D_8010FEDC_baby_bowser_broadside, 1);
}
/* </func_801059BC_baby_bowser_broadside> */

/* <func_80105B94_baby_bowser_broadside> */
#ifdef NON_MATCHING
void func_80105B94_baby_bowser_broadside(void) {
    s8 i;
    s8 j;
    f32 angle;
    s8 r;

    D_80110008_baby_bowser_broadside = HuMemAllocTag(sizeof(BbState), 0x7918);
    memset(D_80110008_baby_bowser_broadside, 0, sizeof(BbState));
    D_80110004_baby_bowser_broadside = HuMemAllocTag(sizeof(BbPlayer) * 4, 0x7918);
    memset(D_80110004_baby_bowser_broadside, 0, sizeof(BbPlayer) * 4);
    for (i = 0; i < 4; i++) {
        D_80110004_baby_bowser_broadside[i].balls = HuMemAllocTag(sizeof(BbBall) * 3, 0x7918);
        memset(D_80110004_baby_bowser_broadside[i].balls, 0, sizeof(BbBall) * 3);
    }
    D_80110000_baby_bowser_broadside = HuMemAllocTag(sizeof(BbTeam) * 2, 0x7918);
    memset(D_80110000_baby_bowser_broadside, 0, sizeof(BbTeam) * 2);
    r = rand16() % 4;
    angle = r * 90.0f;
    D_80110000_baby_bowser_broadside[0].angle[0] = angle;
    D_80110000_baby_bowser_broadside[0].angle[1] = angle + 180.0f;
    D_80110000_baby_bowser_broadside[1].angle[0] = angle + 90.0f;
    D_80110000_baby_bowser_broadside[1].angle[1] = angle + 270.0f;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            while (D_80110000_baby_bowser_broadside[i].angle[j] >= 360.0f) {
                D_80110000_baby_bowser_broadside[i].angle[j] -= 360.0f;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80105B94_baby_bowser_broadside);
#endif
/* </func_80105B94_baby_bowser_broadside> */

/* <func_80105DE4_baby_bowser_broadside> */
void func_80105DE4_baby_bowser_broadside(omObjData* obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_80105E2C_baby_bowser_broadside;
    }
}
/* </func_80105DE4_baby_bowser_broadside> */

/* <func_80105E2C_baby_bowser_broadside> */
void func_80105E2C_baby_bowser_broadside(omObjData* obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_80105E64_baby_bowser_broadside;
    }
}
/* </func_80105E2C_baby_bowser_broadside> */

/* <func_80105E64_baby_bowser_broadside> */
void func_80105E64_baby_bowser_broadside(omObjData* obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}
/* </func_80105E64_baby_bowser_broadside> */

/* <func_80105E88_baby_bowser_broadside> */
void func_80105E88_baby_bowser_broadside(void) {
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
    func_8010A2C4_baby_bowser_broadside(0);
}
/* </func_80105E88_baby_bowser_broadside> */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80105F64_baby_bowser_broadside);

/* <func_80106288_baby_bowser_broadside> */
void func_80106288_baby_bowser_broadside(omObjData* obj) {
    func_8010A2C4_baby_bowser_broadside(BB_WORK(obj)->b.group);
    func_80105E88_baby_bowser_broadside();
    func_8010A81C_baby_bowser_broadside();
    func_8010ACF8_baby_bowser_broadside();
    func_8010B3B4_baby_bowser_broadside();
}
/* </func_80106288_baby_bowser_broadside> */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801062C4_baby_bowser_broadside);

/* <func_80106E40_baby_bowser_broadside> */
void func_80106E40_baby_bowser_broadside(omObjData* obj) {
    func_8010A2C4_baby_bowser_broadside(2);
    func_8010F250_baby_bowser_broadside(obj);
}
/* </func_80106E40_baby_bowser_broadside> */

/* <func_80106E70_baby_bowser_broadside> */
void func_80106E70_baby_bowser_broadside(omObjData* obj) {
    obj->model[0] = func_8000B108_main(0x2D0003, 0x10099);
    func_8001C954_main(obj->model[0]);
    obj->func = func_80106EC4_baby_bowser_broadside;
}
/* </func_80106E70_baby_bowser_broadside> */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80106EC4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107140_baby_bowser_broadside);

/* <func_80107600_baby_bowser_broadside> */
void func_80107600_baby_bowser_broadside(omObjData* obj) {
    func_8010A2C4_baby_bowser_broadside(BB_WORK(obj)->b.group);
    func_800E4E30_minigame(obj);
}
/* </func_80107600_baby_bowser_broadside> */

/* <func_80107630_baby_bowser_broadside> */
void func_80107630_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    Center.x = 0.0f;
    Center.y = 215.0f;
    Center.z = -144.0f;
    CRot.x = 322.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2410.0f;
    func_8010A158_baby_bowser_broadside(0, task);
}
/* </func_80107630_baby_bowser_broadside> */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_801076AC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107854_baby_bowser_broadside);

/* <func_80107A00_baby_bowser_broadside> */
void func_80107A00_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    if (task->state == 0) {
        task->unk1C = 0;
        task->unk1E = 0;
        task->state = 1;
    }
    if (++task->unk1C >= 16) {
        task->unk1C = 15;
        func_8004AB0C_main(15);
        func_8010A158_baby_bowser_broadside(BB_WORK(ctx->obj)->b.group, task);
    }
}
/* </func_80107A00_baby_bowser_broadside> */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107A80_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80107C64_baby_bowser_broadside);

/* <func_80107FE0_baby_bowser_broadside> */
void func_80107FE0_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    s16 i;

    if (task->state == 0) {
        if (++task->unk1C >= 41) {
            task->unk1C = 0;
            for (i = 0; i < 4; i++) {
                func_8010A0B4_baby_bowser_broadside(i + 3, 0xDFFF, &D_80110004_baby_bowser_broadside[i],
                                                    func_80109D2C_baby_bowser_broadside, 0);
            }
            task->state = 1;
        }
    } else if (D_8010FD76_baby_bowser_broadside == 0) {
        if (GMesStatGet() == 0) {
            D_8010FD76_baby_bowser_broadside = 1;
        }
    } else if (D_8010FD76_baby_bowser_broadside >= 2) {
        if (GMesStatGet() == 0) {
            D_8010FD76_baby_bowser_broadside = 3;
        }
        if (D_8010FD76_baby_bowser_broadside == 3) {
            if (++task->unk1C >= 15) {
                func_8010A0B4_baby_bowser_broadside(BB_WORK(ctx->obj)->b.group, 0, NULL,
                                                    func_801081A4_baby_bowser_broadside, 0);
                func_8010A158_baby_bowser_broadside(BB_WORK(ctx->obj)->b.group, task);
            }
        }
    } else {
        if (++task->unk1C == 15) {
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
            D_8010FD60_baby_bowser_broadside = 1;
        }
        if (GMesStatGet() != 0) {
            task->unk1C = 0;
            D_8010FD76_baby_bowser_broadside = 2;
        }
    }
}
/* </func_80107FE0_baby_bowser_broadside> */

/* <func_801081A4_baby_bowser_broadside> */
void func_801081A4_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
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
/* </func_801081A4_baby_bowser_broadside> */

/* <func_80108210_baby_bowser_broadside> */
void func_80108210_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    HmfModel* model;

    model = &HmfModelData[ctx->models[0]];
    if (D_80110008_baby_bowser_broadside->timer < 600.0f) {
        model->rot.y -= D_80110008_baby_bowser_broadside->speed;
        if (model->rot.y < 0.0f) {
            model->rot.y += 360.0f;
        } else if (model->rot.y >= 360.0f) {
            model->rot.y -= 360.0f;
        }
    }
    model = &HmfModelData[ctx->models[2]];
    model->rot.y += D_80110008_baby_bowser_broadside->speed;
    if (model->rot.y < 0.0f) {
        model->rot.y += 360.0f;
    } else if (model->rot.y >= 360.0f) {
        model->rot.y -= 360.0f;
    }
}
/* </func_80108210_baby_bowser_broadside> */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80108350_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80108614_baby_bowser_broadside);

/* <func_801087CC_baby_bowser_broadside> */
void func_801087CC_baby_bowser_broadside(s16 model) {
    HmfModelData[model].unk44 = 1.0f;
    HmfModelData[model].unk40 = 0.0f;
}
/* </func_801087CC_baby_bowser_broadside> */

/* <func_80108804_baby_bowser_broadside> */
void func_80108804_baby_bowser_broadside(f32 angle) {
    D_80110008_baby_bowser_broadside->unk58 = cosdf(angle);
    D_80110008_baby_bowser_broadside->unk5C = sindf(angle);
    D_80110008_baby_bowser_broadside->unk52 = 1;
    D_80110008_baby_bowser_broadside->unk18 = 0;
    D_80110008_baby_bowser_broadside->unk28 = 0.0f;
}
/* </func_80108804_baby_bowser_broadside> */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/165010", func_80108860_baby_bowser_broadside);

/* <func_80109058_baby_bowser_broadside> */
s16 func_80109058_baby_bowser_broadside(omObjData* obj, BbPlayer* player) {
    player->aimColl->pos.x = obj->trans.x;
    player->aimColl->pos.y = 500.0f;
    player->aimColl->pos.z = obj->trans.z;
    player->aimColl->vel.x = sindf(player->aim) * 20.0f * 5.0f * 8.0f;
    player->aimColl->vel.y = 0.0f;
    player->aimColl->vel.z = cosdf(player->aim) * 20.0f * 5.0f * 8.0f;
    func_8010E0B0_baby_bowser_broadside(player->aimColl);
    return player->aimColl->unk2A != 0;
}
/* </func_80109058_baby_bowser_broadside> */

/* <func_8010913C_baby_bowser_broadside> */
void func_8010913C_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    f32 cur;
    f32 target;
    BbPlayer* player = task->data;
    s16 ball;
    s32 motion;
    f32 sx;
    f32 sy;
    f32 angle;

    if (D_80110008_baby_bowser_broadside->flags & 2) {
        if (--player->cooldown < 0) {
            player->cooldown = 0;
        }
        if ((u16)D_800CDA7C_main[player->no] & 0x8000) {
            if (player->cooldown == 0 && player->held == 0) {
                player->held = 1;
                ball = func_80109970_baby_bowser_broadside(player);
                if (ball != -1) {
                    if (task->unk0C != 0) {
                        task->unk0C = 0;
                        func_80109EB0_baby_bowser_broadside(player, 40, 1);
                    } else {
                        task->unk0C = 1;
                        func_80109EB0_baby_bowser_broadside(player, 39, 1);
                    }
                    func_801087CC_baby_bowser_broadside(player->model);
                    func_80109EBC_baby_bowser_broadside(player, 38);
                    player->cooldown = 10;
                    player->fire.w |= ball + 1;
                }
            }
        } else {
            player->held = 0;
        }
        sx = D_800CBB6E_main[player->no];
        sy = D_800D20A1_main[player->no];
        if (sx == 0.0f && sy == 0.0f) {
            if (player->sePlaying != 0) {
                player->sePlaying = 0;
                HuAudFXStop(player->seNo);
            }
        } else {
            angle = atan2df(sy, sx) + 90.0f;
            if (angle >= 360.0f) {
                angle -= 360.0f;
            }
            cur = player->aim;
            target = angle;
            func_8010F6F8_baby_bowser_broadside(&cur, &target);
            if (!((cur - target > 0.0f ? cur - target : -(cur - target)) < 5.0f)) {
                if (cur - target > 0.0f) {
                    player->aim -= 2.0f;
                } else if (cur - target < 0.0f) {
                    player->aim += 2.0f;
                }
            }
        }
    }
}
/* </func_8010913C_baby_bowser_broadside> */

/* <func_80109434_baby_bowser_broadside> */
void func_80109434_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    f32 facing;
    f32 aim;
    BbPlayer* player = task->data;
    omObjData* obj = ctx->obj;
    f32 x;
    f32 z;

    if (!(D_80110008_baby_bowser_broadside->flags & 4)) {
        if (D_80110008_baby_bowser_broadside->timer < 600.0f) {
            player->angle -= D_80110008_baby_bowser_broadside->speed;
        }
        if (player->angle >= 360.0f) {
            player->angle -= 360.0f;
        } else if (player->angle < 0.0f) {
            player->angle += 360.0f;
        }
        x = sindf(player->angle);
        z = cosdf(player->angle);
        x *= 550.0f;
        z *= 550.0f;
        Hu3DModelPosSet(player->model, x, 400.0f, z);
        obj->trans.x = x;
        obj->trans.y = 455.0f;
        obj->trans.z = z;
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 2.5f, z);
        facing = player->angle + 180.0f;
        if (facing > 360.0f) {
            facing -= 360.0f;
        }
        if (player->aim >= 360.0f) {
            player->aim -= 360.0f;
        } else if (player->aim < 0.0f) {
            player->aim += 360.0f;
        }
        aim = player->aim;
        func_8010F6F8_baby_bowser_broadside(&facing, &aim);
        if (facing - aim > 30.0f) {
            player->aim = facing - 30.0f;
            if (player->sePlaying != 0) {
                player->sePlaying = 0;
                HuAudFXStop(player->seNo);
            }
        } else if (facing - aim < -30.0f) {
            player->aim = facing + 30.0f;
            if (player->sePlaying != 0) {
                player->sePlaying = 0;
                HuAudFXStop(player->seNo);
            }
        }
        Hu3DModelRotSet(player->model, 0.0f, player->aim, 0.0f);
        obj->rot.y = player->aim;
    }
}
/* </func_80109434_baby_bowser_broadside> */

/* <func_801096E8_baby_bowser_broadside> */
void func_801096E8_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    BbPlayer* player = task->data;
    BbBall* ball;
    omObjData* obj;
    s16 i;
    s16 fx;

    obj = ctx->obj;
    ball = player->balls;
    i = 0;
    if (player->fire.h.lo != 0) {
        i = player->fire.h.lo;
        func_801099D4_baby_bowser_broadside(obj, &player->balls[(s16)(i - 1)], player->aim, player->team);
        player->fire.w &= 0xFFFF0000;
        HuAudFXPlay(0x35A);
    }
    for (i = 0; i < 3; i++, ball++) {
        if (ball->active != 0) {
            ball->coll->vel.x = ball->vel.x;
            ball->coll->vel.y = ball->vel.y;
            ball->coll->vel.z = ball->vel.z;
            func_8010E0B0_baby_bowser_broadside(ball->coll);
            ball->time += 1.0f;
            ball->vel.y = ball->unk1C - ball->time * 2.45f;
            if (ball->coll->unk2A != 0) {
                func_801098F8_baby_bowser_broadside(ball);
            } else if (ball->coll->unk30 != 0) {
                HuAudFXPlay(0x35B);
                func_801098F8_baby_bowser_broadside(ball);
                fx = func_8010AADC_baby_bowser_broadside(ball->team + 2);
                if (fx != -1) {
                    func_8010AB80_baby_bowser_broadside(fx, ball->coll->pos.x, ball->coll->pos.y, ball->coll->pos.z,
                                                        0.0f, 0.0f, 0.0f, 1.0f, 0);
                }
                if (D_80110008_baby_bowser_broadside->flags & 2) {
                    D_80110000_baby_bowser_broadside[player->team].score++;
                }
                func_80108804_baby_bowser_broadside(ball->angle);
            }
            if (!(ball->coll->flags & 1)) {
                func_801098F8_baby_bowser_broadside(ball);
            }
        }
    }
}
/* </func_801096E8_baby_bowser_broadside> */

/* <func_801098F8_baby_bowser_broadside> */
void func_801098F8_baby_bowser_broadside(BbBall* ball) {
    func_8010AB80_baby_bowser_broadside(func_8010AADC_baby_bowser_broadside(ball->team), ball->coll->pos.x,
                                        ball->coll->pos.y, ball->coll->pos.z, 0.0f, 0.0f, 0.0f, 1.0f, 0);
    func_8001C258_main(ball->model, 4, 4);
    ball->active = 0;
}
/* </func_801098F8_baby_bowser_broadside> */

/* <func_80109970_baby_bowser_broadside> */
s16 func_80109970_baby_bowser_broadside(BbPlayer* player) {
    s16 i;

    for (i = 0; i < 3; i++) {
        if (player->balls[i].active == 0) {
            break;
        }
    }
    if (i == 3) {
        return -1;
    }
    return i;
}
/* </func_80109970_baby_bowser_broadside> */

/* <func_801099D4_baby_bowser_broadside> */
void func_801099D4_baby_bowser_broadside(omObjData* obj, BbBall* ball, f32 angle, s16 team) {
    u8 color[4];
    f32 s;
    f32 c;
    f32 dx;
    f32 dz;
    s16 fx;

    s = sindf(angle);
    c = cosdf(angle);
    dx = s * 100.0f;
    dz = c * 100.0f;
    Hu3DModelPosSet(ball->model, dx + obj->trans.x, 500.0f, dz + obj->trans.z);
    ball->vel.x = ball->vel0.x = s * 50.0f;
    ball->vel.y = sindf(22.5f) * 30.000002f;
    ball->vel.z = ball->vel0.z = c * 50.0f;
    ball->unk1C = ball->vel.y;
    ball->time = 0;
    ball->angle = angle;
    ball->active = 1;
    func_8001C258_main(ball->model, 4, 0);
    dx = s * 180.0f;
    dz = c * 180.0f;
    ball->team = team;
    fx = func_8010AFF4_baby_bowser_broadside(0);
    if (fx != -1) {
        if (team == 0) {
            color[0] = 0xFF;
            color[1] = 0xBF;
            color[2] = 0xBF;
            color[3] = 0xFF;
        } else {
            color[0] = 0xA5;
            color[1] = 0xCC;
            color[2] = 0xE5;
            color[3] = 0xFF;
        }
        func_8010B098_baby_bowser_broadside(fx, dx + obj->trans.x, 469.99997f, dz + obj->trans.z, color);
    }
    omVibrate(BB_WORK(obj)->b.player, 10, 0, 10);
}
/* </func_801099D4_baby_bowser_broadside> */

/* <func_80109BD8_baby_bowser_broadside> */
void func_80109BD8_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    BbPlayer* player = task->data;
    omObjData* obj = ctx->obj;
    f32 t;

    if (task->state == 0) {
        task->unk1C = 0;
        task->unk2C = obj->rot.y;
        task->unk30 = 0.0f;
        func_8010F6F8_baby_bowser_broadside(&task->unk2C, &task->unk30);
        func_80109EB0_baby_bowser_broadside(player, 2, 1);
        player->unk_0C = -1;
        task->state = 1;
    }
    t = task->unk1C / 20.0f;
    if (t > 1.0f) {
        t = 1.0f;
    }
    obj->rot.y = (task->unk30 - task->unk2C) * t + task->unk2C;
    if (++task->unk1C > 20.0f) {
        func_80109EB0_baby_bowser_broadside(player, 0, 1);
        obj->rot.y = 0.0f;
        task->unk1C = 20;
        if (D_8010FD60_baby_bowser_broadside != 0) {
            func_80109EB0_baby_bowser_broadside(player, 13, 1);
            func_8010A158_baby_bowser_broadside(BB_WORK(obj)->b.group, task);
        }
    }
}
/* </func_80109BD8_baby_bowser_broadside> */

/* <func_80109D2C_baby_bowser_broadside> */
void func_80109D2C_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    BbPlayer* player = task->data;
    omObjData* obj = ctx->obj;

    if (D_8010FD60_baby_bowser_broadside != 0) {
        func_80109EB0_baby_bowser_broadside(player, 14, 1);
        player->unk_0C = -1;
        func_8010A158_baby_bowser_broadside(BB_WORK(obj)->b.group, task);
    }
}
/* </func_80109D2C_baby_bowser_broadside> */

/* <func_80109D94_baby_bowser_broadside> */
void func_80109D94_baby_bowser_broadside(BbCtx* ctx, BbTask* task) {
    BbPlayer* player = task->data;
    omObjData* obj = ctx->obj;
    HmfModel* model = &HmfModelData[obj->model[0]];

    if (D_800CCF58_main[model->unk02].unk02 - 1 <= model->unk40) {
        player->unk08 = 1;
    }
    if (player->unk08 != 0) {
        func_800E5690_minigame(obj, player->unk0A);
        if (player->unk0A == 13) {
            func_80045ED0_main(D_800A178C_main[GwPlayer[obj->work[0]].chr][0] | 0x2F);
        }
        player->unk08 = 0;
        if (player->unk_0C != -1) {
            player->unk0A = player->unk_0C;
            player->unk_0C = -1;
        }
    }
}
/* </func_80109D94_baby_bowser_broadside> */

/* <func_80109EB0_baby_bowser_broadside> */
void func_80109EB0_baby_bowser_broadside(BbPlayer* player, s16 motion, s8 pending) {
    player->unk08 = pending;
    player->unk0A = motion;
}
/* </func_80109EB0_baby_bowser_broadside> */

void func_80109EBC_baby_bowser_broadside(unk_80109EBC *arg0, s16 arg1) {
    arg0->unk_0C = arg1;
}
