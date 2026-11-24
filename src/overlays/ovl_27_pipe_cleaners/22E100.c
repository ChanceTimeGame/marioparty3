#include "common.h"
// m2 pc: Pipe Cleaners (four players, each pulls the pipes' plungers as they rise)
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/wipe.h"
#include "mallocblock.h"

/* A sprite slot (D_8010A300_pipe_cleaners, 10 x 0x84; [0] and [1] used). */
typedef struct PcSprite {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 unk04[10];
    /* 0x18 */ s32 unk18[10];
    /* 0x40 */ s16 grp;
    /* 0x42 */ s16 spr;
    /* 0x44 */ Vec pos;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} PcSprite; // Size 0x84

/* One pipe (D_8010A968_pipe_cleaners, 4 players x 4 pipes, 0x1C each). */
typedef struct PcPipe {
    /* 0x00 */ s32 state; /* 0 down, 1 rising, 2 up, 3 lowering, 4 pulled */
    /* 0x04 */ s32 next;
    /* 0x08 */ omObjData *obj;
    /* 0x0C */ s32 kind; /* 0 short wait, 1 long wait, 2 all at once */
    /* 0x10 */ s32 init; /* the state's first frame has run */
    /* 0x14 */ s32 timer;
    /* 0x18 */ s32 pulled;
} PcPipe; // Size 0x1C

/* One player (D_8010AB30_pipe_cleaners, 4 x 0x38). */
typedef struct PcPlayer {
    /* 0x00 */ s32 state; /* 0 idle, 1..4 pulling pipe 1..4, 5 win, 6 lose, 7 hook flies off */
    /* 0x04 */ omObjData *obj;
    /* 0x08 */ s32 score;
    /* 0x0C */ s32 rank;
    /* 0x10 */ s32 hookState;
    /* 0x14 */ f32 hookRot;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ Vec hookPos;
    /* 0x28 */ s32 cpuAimChance;
    /* 0x2C */ s32 cpuPullChance;
    /* 0x30 */ s32 cpuWait;
    /* 0x34 */ s32 cpuTimer;
} PcPlayer; // Size 0x38

/* One score digit sprite (D_8010AC18_pipe_cleaners, 4 players x 4, 0x14 each). */
typedef struct PcDigit {
    /* 0x00 */ s32 spr; /* sprite id, an s16 */
    /* 0x04 */ s32 active;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 alpha;
    /* 0x10 */ s32 value;
} PcDigit; // Size 0x14

/* Main code's sprite-model table (HmfSprModelCreate). */
typedef struct PcSprModel {
    /* 0x00 */ u16 model;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ char unk04[0x20];
} PcSprModel; // Size 0x24

/* A player's start position (D_80109EF0_pipe_cleaners). */
typedef struct PcPos {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rotZ;
} PcPos; // Size 0x10

/* A pipe's position (D_80109F80_pipe_cleaners) and the side it rises toward. */
typedef struct PcPipePos {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rotZ;
    /* 0x10 */ s32 dir; /* -1 down from the top, 1 up from the bottom */
} PcPipePos; // Size 0x14

/* A player's score position on screen (D_8010A010_pipe_cleaners). */
typedef struct PcScorePos {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
} PcScorePos; // Size 0x8

/* A camera (D_8010A040_pipe_cleaners). */
typedef struct PcCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} PcCamera; // Size 0x2C

extern PcSprModel *D_800CBB60_main;
extern s32 D_800A178C_main[][6];
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u16 D_800D530C_main;
extern D_800CCF58_main_Struct *D_800CCF58_main;

void func_8000B5F0_main(u8 arg0);
s32 func_8000B710_main(s32 arg0);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BD50_main(u16 spriteId, s16 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
s16 func_800329B4_main(void *);
void func_8001EED8_main(s16 arg0, u8 arg1, s8 arg2);
omObjData *func_80045ED0_main(u32 arg0);
void func_80088800_main(HuMtx4F mf, f32 x, f32 y, f32 z);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_80032FC0_main(s16, u8, u8);
void func_80034048_main(s16, s16);
void func_80033354_main(s16);
s16 func_80032694_main(HmfData *, u16, s32, char *);
void func_80032FF8_main(s32, u8);
s32 func_80017BB8_main(s16, s16);
s16 func_8004AC98_main(s16, s16);
void func_8004AB0C_main(s32);
void func_8003F578_main(s16);
void func_8003F5C0_main(void);
void func_80045010_main(const s16 *, s32);

/* .rodata: the players' animation names (D_80109F60_pipe_cleaners) */
extern const char D_8010A134_pipe_cleaners[];
extern const char D_8010A140_pipe_cleaners[];
extern const char D_8010A14C_pipe_cleaners[];
extern const char D_8010A158_pipe_cleaners[];
extern const char D_8010A164_pipe_cleaners[];
extern const char D_8010A170_pipe_cleaners[];
extern const char D_8010A17C_pipe_cleaners[];
extern const char D_8010A188_pipe_cleaners[];

/* .data */
/* CPU by difficulty: 1 in n to aim, 1 in n to press, wait (x5 frames). */
s32 D_80109EC0_pipe_cleaners[4][3] = {
    { 20, 20, 5 },
    { 5, 3, 4 },
    { 2, 2, 2 },
    { 1, 2, 1 },
};
PcPos D_80109EF0_pipe_cleaners[4] = {
    { -135.0f, 270.0f, 45.0f, 180.0f },
    { 135.0f, 270.0f, 45.0f, 180.0f },
    { -135.0f, 50.0f, 45.0f, 0.0f },
    { 135.0f, 50.0f, 45.0f, 0.0f },
};
/* Per character: the three animation files (0 at the start, 1 win, 2 lose). */
u16 D_80109F30_pipe_cleaners[8][3] = {
    { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 },
    { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 }, { 0xA4, 0xA5, 0xA6 }, { 0x1A, 0x1C, 0x1D },
};
char *D_80109F60_pipe_cleaners[8] = {
    (char *)D_8010A188_pipe_cleaners, (char *)D_8010A17C_pipe_cleaners,
    (char *)D_8010A170_pipe_cleaners, (char *)D_8010A164_pipe_cleaners,
    (char *)D_8010A158_pipe_cleaners, (char *)D_8010A14C_pipe_cleaners,
    (char *)D_8010A140_pipe_cleaners, (char *)D_8010A134_pipe_cleaners,
};
PcPipePos D_80109F80_pipe_cleaners[4] = {
    { -135.0f, 320.0f, 45.0f, 180.0f, -1 },
    { 135.0f, 320.0f, 45.0f, 180.0f, -1 },
    { -135.0f, 0.0f, 45.0f, 0.0f, 1 },
    { 135.0f, 0.0f, 45.0f, 0.0f, 1 },
};
/* Pipe speed per frame of the rise/fall. */
f32 D_80109FD0_pipe_cleaners[16] = {
    5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f,
};
PcScorePos D_8010A010_pipe_cleaners[4] = {
    { 81, 40 },
    { 241, 40 },
    { 81, 160 },
    { 241, 160 },
};
s16 D_8010A030_pipe_cleaners = -1;
s32 D_8010A034_pipe_cleaners = 0;
s32 D_8010A038_pipe_cleaners = 0;
s32 D_8010A03C_pipe_cleaners = 0;
PcCamera D_8010A040_pipe_cleaners[4] = {
    { { 0.0f, 0.0f, 160.0f, 120.0f }, { 320.0f, 240.0f, 511.0f, 350.0f, 240.0f, 511.0f }, 15.0f },
    { { 160.0f, 0.0f, 320.0f, 120.0f }, { 320.0f, 240.0f, 511.0f, 930.0f, 240.0f, 511.0f }, 15.0f },
    { { 0.0f, 120.0f, 160.0f, 240.0f }, { 320.0f, 240.0f, 511.0f, 350.0f, 700.0f, 511.0f }, 15.0f },
    { { 160.0f, 120.0f, 320.0f, 240.0f }, { 320.0f, 240.0f, 511.0f, 930.0f, 700.0f, 511.0f }, 15.0f },
};
/* .rodata */
extern const s16 D_8010A2A8_pipe_cleaners[];
/* .bss */
extern void *D_8010A2B0_pipe_cleaners[4][3];
extern s16 D_8010A2E0_pipe_cleaners[8];
extern s32 D_8010A2F0_pipe_cleaners;
extern PcSprite D_8010A300_pipe_cleaners[10];
extern s32 D_8010A828_pipe_cleaners;
extern s32 D_8010A82C_pipe_cleaners;
extern s16 D_8010A830_pipe_cleaners[4];
extern s8 D_8010A838_pipe_cleaners[4][60];
extern s32 D_8010A928_pipe_cleaners[16];
extern PcPipe D_8010A968_pipe_cleaners[16];
extern omObjData *D_8010AB28_pipe_cleaners;
extern PcPlayer D_8010AB30_pipe_cleaners[4];
extern s32 D_8010AC10_pipe_cleaners;
extern s32 D_8010AC14_pipe_cleaners;
extern PcDigit D_8010AC18_pipe_cleaners[16];
extern s32 D_8010AD58_pipe_cleaners;

void func_80105A74_pipe_cleaners(void);
void func_80105B3C_pipe_cleaners(s32 player);
void func_80105BB4_pipe_cleaners(omObjData *obj);
void func_80105C50_pipe_cleaners(omObjData *obj);
void func_80105DE8_pipe_cleaners(omObjData *obj);
void func_80105DF0_pipe_cleaners(omObjData *obj);
void func_80105E94_pipe_cleaners(s32 player);
void func_80105EF8_pipe_cleaners(omObjData *obj);
void func_80105F00_pipe_cleaners(omObjData *obj);
void func_801060D4_pipe_cleaners(s32 pipe);
void func_801060FC_pipe_cleaners(omObjData *obj);
void func_80106204_pipe_cleaners(omObjData *obj);
void func_801063E8_pipe_cleaners(omObjData *obj, s32 pipe);
s32 func_80106540_pipe_cleaners(omObjData *obj, u32 mode);
void func_801066E4_pipe_cleaners(omObjData *obj);
void func_8010698C_pipe_cleaners(omObjData *obj, u8 anim);
void func_80106A70_pipe_cleaners(omObjData *obj, s32 motion);
void func_80106B18_pipe_cleaners(omObjData *obj, PcPlayer *player);
void func_80106BF8_pipe_cleaners(omObjData *obj, PcPlayer *player);
void func_80106CB4_pipe_cleaners(omObjData *obj, PcPlayer *player);
void func_80106CF4_pipe_cleaners(PcPlayer *player);
void func_80106DA4_pipe_cleaners(PcPlayer *player);
void func_80106E10_pipe_cleaners(omObjData *obj);
void func_80106FD8_pipe_cleaners(omObjData *obj, u16 chr, f32 frame, s32 state);
void func_80107114_pipe_cleaners(omObjData *obj);
void func_8010731C_pipe_cleaners(omObjData *obj);
void func_801073A4_pipe_cleaners(omObjData *obj);
void func_8010742C_pipe_cleaners(omObjData *obj);
void func_80107598_pipe_cleaners(omObjData *obj);
void func_80107B28_pipe_cleaners(omObjData *obj);
void func_80107C08_pipe_cleaners(omObjData *obj);
void func_80107D84_pipe_cleaners(omObjData *obj);
void func_80107E3C_pipe_cleaners(omObjData *obj);
void func_8010801C_pipe_cleaners(omObjData *obj);
void func_801080F4_pipe_cleaners(omObjData *obj);
void func_80108194_pipe_cleaners(omObjData *obj);
void func_80108428_pipe_cleaners(void);
void func_80108484_pipe_cleaners(void);
void func_80108708_pipe_cleaners(void);
void func_801088AC_pipe_cleaners(PcDigit *digit, s32 arg1);
void func_80108964_pipe_cleaners(PcDigit *digit, s32 arg1);
void func_80108A4C_pipe_cleaners(omObjData *obj);
void func_80108F18_pipe_cleaners(omObjData *obj);
void func_80109218_pipe_cleaners(void);
void func_801093A4_pipe_cleaners(void);
void func_801096C0_pipe_cleaners(void);
void func_80109784_pipe_cleaners(omObjData *obj);
void func_8010984C_pipe_cleaners(omObjData *obj);
void func_80109884_pipe_cleaners(omObjData *obj);
void func_801098DC_pipe_cleaners(omObjData *obj);
void func_80109B74_pipe_cleaners(omObjData *obj);
void func_80109BFC_pipe_cleaners(void);
void func_80109D70_pipe_cleaners(void);

void func_801059A0_pipe_cleaners(void) {
    func_80109D70_pipe_cleaners();
}

f32 func_801059BC_pipe_cleaners(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

u8 func_80105A3C_pipe_cleaners(s32 max) {
    return ((u32)(rand8() * max)) >> 8;
}

void func_80105A74_pipe_cleaners(void) {
    PcSprite *spr;
    u32 i;

    for (i = 0, spr = D_8010A300_pipe_cleaners; i < 10; i++, spr++) {
        spr->unk00 = 0;
        spr->unk04[0] = 0;
        spr->unk04[1] = 0;
        spr->unk04[2] = 0;
        spr->unk04[3] = 0;
        spr->unk04[4] = 0;
        spr->unk04[5] = 0;
        spr->unk04[6] = 0;
        spr->unk04[7] = 0;
        spr->unk04[8] = 0;
        spr->unk04[9] = 0;
        spr->unk18[0] = 0;
        spr->unk18[1] = 0;
        spr->unk18[2] = 0;
        spr->unk18[3] = 0;
        spr->unk18[4] = 0;
        spr->unk18[5] = 0;
        spr->unk18[6] = 0;
        spr->unk18[7] = 0;
        spr->unk18[8] = 0;
        spr->unk18[9] = 0;
        spr->grp = -1;
        spr->spr = -1;
        spr->pos.x = spr->pos.y = spr->pos.z = 0.0f;
        spr->unk50.x = spr->unk50.y = spr->unk50.z = 0.0f;
        spr->unk5C.x = spr->unk5C.y = spr->unk5C.z = 0.0f;
        spr->unk68 = 0.0f;
        spr->unk6C = 0.0f;
        spr->unk70 = 0.0f;
        spr->unk74 = 0.0f;
        spr->unk78.x = spr->unk78.y = spr->unk78.z = 0.0f;
    }
}

/* Clears a player's pad input (the CPU writes its own). */
void func_80105B3C_pipe_cleaners(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

#ifdef NON_MATCHING
void func_80105BB4_pipe_cleaners(omObjData *obj) {
    func_8000BBD4_main(D_8010A300_pipe_cleaners[0].spr, D_8010A300_pipe_cleaners[0].pos.x, D_8010A300_pipe_cleaners[0].pos.y);
    func_8000BBD4_main(D_8010A300_pipe_cleaners[1].spr, D_8010A300_pipe_cleaners[1].pos.x, D_8010A300_pipe_cleaners[1].pos.y);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80105BB4_pipe_cleaners);
#endif

#ifdef NON_MATCHING
void func_80105C50_pipe_cleaners(omObjData *obj) {
    s32 grp;

    D_8010A300_pipe_cleaners[1].pos.x = 160.0f;
    D_8010A300_pipe_cleaners[1].pos.y = 120.0f;
    grp = func_8000B838_main(0x48000C);
    D_8010A300_pipe_cleaners[1].grp = grp;
    D_8010A300_pipe_cleaners[1].spr = InitEspriteSlot(grp, 0, 0);
    func_8000BC48_main(D_8010A300_pipe_cleaners[1].spr, 0x5000);
    func_8000BBD4_main(D_8010A300_pipe_cleaners[1].spr, D_8010A300_pipe_cleaners[1].pos.x, D_8010A300_pipe_cleaners[1].pos.y);
    D_8010A300_pipe_cleaners[0].pos.x = 160.0f;
    D_8010A300_pipe_cleaners[0].pos.y = 120.0f;
    grp = func_8000B838_main(0x48000A);
    D_8010A300_pipe_cleaners[0].grp = grp;
    D_8010A300_pipe_cleaners[0].spr = InitEspriteSlot(grp, 0, 0);
    func_8000BC48_main(D_8010A300_pipe_cleaners[0].spr, 0x1000);
    func_8000BBD4_main(D_8010A300_pipe_cleaners[0].spr, D_8010A300_pipe_cleaners[0].pos.x, D_8010A300_pipe_cleaners[0].pos.y);
    obj->func = func_80105BB4_pipe_cleaners;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80105C50_pipe_cleaners);
#endif

void func_80105DB4_pipe_cleaners(void) {
    omAddObj(100, 1, 0, -1, func_80105C50_pipe_cleaners);
}

void func_80105DE8_pipe_cleaners(omObjData *obj) {
}

/* The stage and its shadow. */
void func_80105DF0_pipe_cleaners(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x480001, 0x299);
    obj->model[1] = func_8000B108_main(0x480002, 0x299);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->func = func_80105DE8_pipe_cleaners;
}

void func_80105E60_pipe_cleaners(void) {
    omAddObj(110, 2, 0, -1, func_80105DF0_pipe_cleaners);
}

void func_80105E94_pipe_cleaners(s32 player) {
    s16 model = D_8010A830_pipe_cleaners[player];

    func_8001C258_main(D_800CBB60_main[model].model, 4, 0);
    func_800146DC_main(model, 1, 0);
}

void func_80105EF8_pipe_cleaners(omObjData *obj) {
}

void func_80105F00_pipe_cleaners(omObjData *obj) {
    s16 *slot = &D_8010A830_pipe_cleaners[obj->work[0]];
    void *data;
    s16 anim;
    s32 model;

    data = DataRead(0xB);
    anim = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    model = HmfSprModelCreate((void *)-1, 0x2A4, 0x10);
    func_800147FC_main(model, 0xFF, 0xFF, 0xFF);
    func_800146DC_main(model, 1, 1);
    D_800CBB60_main[(s16)model].unk02 = anim;
    func_8001C258_main(D_800CBB60_main[(s16)model].model, 4, 4);
    Hu3DModelPosSet(D_800CBB60_main[(s16)model].model, -60.0f, 180.0f, 0.0f);
    Hu3DModelScaleSet(D_800CBB60_main[(s16)model].model, 3.0f, 3.0f, 3.0f);
    func_8001C814_main(D_800CBB60_main[(s16)model].model, 2, 2);
    func_8001C8A8_main(D_800CBB60_main[(s16)model].model, 1 << obj->work[0]);
    *slot = model;
    obj->func = func_80105EF8_pipe_cleaners;
}

void func_80106078_pipe_cleaners(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(500, 1, 0, -1, func_80105F00_pipe_cleaners)->work[0] = i;
    }
}

void func_801060D4_pipe_cleaners(s32 pipe) {
    s32 *state = &D_8010A928_pipe_cleaners[pipe];

    if (*state == 0) {
        *state = 1;
    }
}

void func_801060FC_pipe_cleaners(omObjData *obj) {
    s32 *state = &D_8010A928_pipe_cleaners[obj->work[0]];
    s16 model;

    if (*state != 0) {
        if (*state == 1) {
            func_8001C258_main(obj->model[0], 4, 0);
            func_8001C5B4_main(obj->model[0], D_8010AB28_pipe_cleaners->motion[0]);
            func_8001C814_main(obj->model[0], 2, 2);
            func_8001C6A8_main(obj->model[0], 0.0f);
            *state = 2;
            return;
        }
        model = obj->model[0];
        if (HmfModelData[model].unk40 == 0.0f) {
            func_8001C258_main(model, 4, 4);
            func_8001C814_main(obj->model[0], 1, 1);
            *state = 0;
        }
    }
}

void func_80106204_pipe_cleaners(omObjData *obj) {
    D_8010A928_pipe_cleaners[obj->work[0]] = 0;
    if (obj->work[0] == 0) {
        obj->model[0] = func_8000B108_main(0x480004, 0x299);
        D_8010AC14_pipe_cleaners = obj->model[0];
        func_8000B460_main(obj, 0, 0x480005);
        D_8010AB28_pipe_cleaners = obj;
    } else {
        obj->model[0] = Hu3DModelLink((s16)D_8010AC14_pipe_cleaners);
    }
    obj->trans.x = D_80109EF0_pipe_cleaners[obj->work[0] & 3].x;
    obj->trans.y = D_80109EF0_pipe_cleaners[obj->work[0] & 3].y;
    obj->trans.z = D_80109EF0_pipe_cleaners[obj->work[0] & 3].z;
    obj->rot.z = D_80109EF0_pipe_cleaners[obj->work[0] & 3].rotZ;
    func_8001C5B4_main(obj->model[0], D_8010AB28_pipe_cleaners->motion[0]);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C6A8_main(obj->model[0], 0.0f);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C8A8_main(obj->model[0], 1 << (obj->work[0] >> 2));
    obj->func = func_801060FC_pipe_cleaners;
}

void func_8010638C_pipe_cleaners(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(400, 1, 1, -1, func_80106204_pipe_cleaners)->work[0] = i;
    }
}

/* CPU: press toward one pipe (0/1 right, 2/3 left; even B, odd A). */
void func_801063E8_pipe_cleaners(omObjData *obj, s32 pipe) {
    s32 dir = pipe & 3;

    if (dir == 0) {
        D_800D5558_main[GwPlayer[obj->work[0]].pad] = 0x4000;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = 60;
    } else if (dir == 1) {
        D_800D5558_main[GwPlayer[obj->work[0]].pad] = 0x8000;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = 60;
    } else if (dir == 2) {
        D_800D5558_main[GwPlayer[obj->work[0]].pad] = 0x4000;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = -60;
    } else if (dir == 3) {
        D_800D5558_main[GwPlayer[obj->work[0]].pad] = 0x8000;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = -60;
    }
}

/* CPU: choose a pipe of this player's four, or -1. */
// decomp-permuter
s32 func_80106540_pipe_cleaners(omObjData *obj, u32 mode)
{
  s32 wait[4];
  PcPipe *pipe;
  s32 idx;
  u32 i;
  for (i = 0; i < 4; i++)
  {
    wait[i] = -2;
  }

  for (i = 0; i < 4; i++)
  {
    idx = (obj->work[0] * 4) + i;
    pipe = &D_8010A968_pipe_cleaners[idx];
    switch (mode)
    {
      case 0:
        switch (pipe->state)
      {
        case 0:

        case 1:

        case 3:

        case 4:
          break;

        case 2:
          return idx;

      }

        break;

      case 1:
        switch (pipe->state)
      {
        case 0:

        case 3:

        case 4:
          break;

        case 1:

        case 2:
          return idx;

      }

        break;

      case 2:
        switch (pipe->state)
      {
        case 0:

        case 4:
          break;

        case 1:

        case 2:
          if (i)
        {
          wait[i] = -1;
          break;
        }
        else
        {
          wait[i] = -1;
          break;
        }

        case 3:
          wait[i] = pipe->timer;
          break;

      }

        break;

    }

  }

  if (mode == 2)
  {
    for (i = 0; i < 4; i++)
    {
      if (((u32) wait[i]) < 4)
      {
        return (obj->work[0] * 4) + i;
      }
    }

    for (i = 0; i < 4; i++)
    {
      if (wait[i] == (-1))
      {
        return (obj->work[0] * 4) + i;
      }
    }

  }
  return -1;
}

/* CPU player input. */
// control flow (masked 52, 132 of 180): GCC cross-jumps the last else branch into the identical tail of
// the aim branch (random pipe, pull roll, timer); retail keeps both copies. Same calls and logic.
#ifdef NON_MATCHING
void func_801066E4_pipe_cleaners(omObjData *obj) {
    PcPlayer *player;
    s32 pipe;

    func_80105B3C_pipe_cleaners(obj->work[0]);
    player = &D_8010AB30_pipe_cleaners[obj->work[0]];
    if (player->state == 0) {
        if (player->cpuTimer != 0) {
            player->cpuTimer--;
        } else if (rand8() % player->cpuAimChance == 0) {
            pipe = func_80106540_pipe_cleaners(obj, (u8)((u32)rand8() % 3));
            if (pipe != -1) {
                if (rand8() % player->cpuPullChance != 0) {
                    pipe = (rand8() & 3) + obj->work[0] * 4;
                    if (rand8() % player->cpuPullChance != 0) {
                        func_801063E8_pipe_cleaners(obj, pipe);
                    }
                } else {
                    func_801063E8_pipe_cleaners(obj, pipe);
                }
                player->cpuTimer = (rand8() % player->cpuWait) * 5;
            }
        } else {
            pipe = (rand8() & 3) + obj->work[0] * 4;
            if (rand8() % player->cpuPullChance != 0) {
                func_801063E8_pipe_cleaners(obj, pipe);
            }
            player->cpuTimer = (rand8() % player->cpuWait) * 5;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801066E4_pipe_cleaners);
#endif

void func_8010698C_pipe_cleaners(omObjData *obj, u8 anim) {
    s8 chr = GwPlayer[obj->work[0]].chr;

    func_80033354_main(D_8010A2E0_pipe_cleaners[obj->work[0]]);
    D_8010A2E0_pipe_cleaners[obj->work[0]] = HmfAnimCreate(HmfModelData[obj->model[0]].hmf,
        D_8010A2B0_pipe_cleaners[obj->work[0]][anim], 0, D_80109F60_pipe_cleaners[chr]);
}

// decomp-permuter
void func_80106A70_pipe_cleaners(omObjData *obj, s32 motion)
{
  u8 new_var;
  s16 idx;
  if (motion == 0)
  {
    idx = obj->motion[0] & 0x3FFF;
    new_var = HmfModelData[idx].unk02;
    func_8001EED8_main(obj->model[0], new_var, 2);
    return;
  }
  func_8001C5B4_main(obj->model[0], obj->motion[motion]);
  HmfModelData[obj->model[0]].unk06 = 0xFF;
}

/* The hook flies up off the winner's head. */
void func_80106B18_pipe_cleaners(omObjData *obj, PcPlayer *player) {
    player->hookPos.x = -60.0f;
    player->hookPos.y = 150.0f;
    player->hookPos.z = 0.0f;
    player->hookRot = 0.0f;
    func_8001C258_main(player->obj->model[2], 0x4000, 0);
    Hu3DModelPosSet(obj->model[2], player->hookPos.x, player->hookPos.y, player->hookPos.z);
    Hu3DModelRotSet(obj->model[2], player->hookRot, 0.0f, 0.0f);
    func_80106A70_pipe_cleaners(player->obj, 7);
    func_8001C814_main(player->obj->model[0], 2, 2);
    func_8001C6A8_main(obj->model[0], 0.0f);
    player->state = 7;
    player->hookState = 1;
}

const char D_8010A134_pipe_cleaners[] = "c301l_0_DEF";
const char D_8010A140_pipe_cleaners[] = "c300l_0_DEF";
const char D_8010A14C_pipe_cleaners[] = "c005l_0_DEF";
const char D_8010A158_pipe_cleaners[] = "c004l_0_DEF";
const char D_8010A164_pipe_cleaners[] = "c003l_0_DEF";
const char D_8010A170_pipe_cleaners[] = "c002l_0_DEF";
const char D_8010A17C_pipe_cleaners[] = "c001l_0_DEF";
const char D_8010A188_pipe_cleaners[] = "c000l_0_DEF";

void func_80106BF8_pipe_cleaners(omObjData *obj, PcPlayer *player) {
    player->hookPos.y += 10.0;
    player->hookRot += 46.0;
    Hu3DModelPosSet(obj->model[2], player->hookPos.x, player->hookPos.y, player->hookPos.z);
    Hu3DModelRotSet(obj->model[2], player->hookRot, 0.0f, 0.0f);
    if (player->hookPos.y >= 240.0) {
        player->hookState = 2;
    }
}

void func_80106CB4_pipe_cleaners(omObjData *obj, PcPlayer *player) {
    func_8001C258_main(player->obj->model[2], 4, 4);
    player->hookState = 3;
}

/* Win: motion 5, voice, anim 1. */
void func_80106CF4_pipe_cleaners(PcPlayer *player) {
    omObjData *obj = player->obj;
    s32 dir = D_800A178C_main[GwPlayer[obj->work[0]].chr][0];

    func_80106A70_pipe_cleaners(obj, 5);
    func_8001C814_main(player->obj->model[0], 2, 2);
    func_8001C6A8_main(player->obj->model[0], 0.0f);
    player->state = 5;
    func_80045ED0_main(dir | 0x2F);
    func_8010698C_pipe_cleaners(player->obj, 1);
}

/* Lose: motion 6, anim 2. */
void func_80106DA4_pipe_cleaners(PcPlayer *player) {
    func_80106A70_pipe_cleaners(player->obj, 6);
    func_8001C814_main(player->obj->model[0], 2, 2);
    func_8001C6A8_main(player->obj->model[0], 0.0f);
    player->state = 6;
    func_8010698C_pipe_cleaners(player->obj, 2);
}

/* Idle: stick right/left with A/B pulls one of the four pipes. */
void func_80106E10_pipe_cleaners(omObjData *obj) {
    PcPlayer *player = &D_8010AB30_pipe_cleaners[obj->work[0]];

    if (D_800D20A1_main[GwPlayer[obj->work[0]].pad] > 50 && (D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x8000)) {
        func_80106A70_pipe_cleaners(obj, 1);
        player->state = 2;
    } else if (D_800D20A1_main[GwPlayer[obj->work[0]].pad] < -50 && (D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x8000)) {
        func_80106A70_pipe_cleaners(obj, 3);
        player->state = 4;
    } else if (D_800D20A1_main[GwPlayer[obj->work[0]].pad] > 50 && (D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x4000)) {
        func_80106A70_pipe_cleaners(obj, 2);
        player->state = 1;
    } else if (D_800D20A1_main[GwPlayer[obj->work[0]].pad] < -50 && (D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x4000)) {
        func_80106A70_pipe_cleaners(obj, 4);
        player->state = 3;
    }
    func_8001C814_main(obj->model[0], 2, 2);
    func_8001C6A8_main(obj->model[0], 0.0f);
}

/* Shadow scale follows the pull motion. */
// control flow (masked 5): retail repeats the obj->model load in the frame < 20 arm and jumps past the
// join's copy (tried: the call in both arms, the test inverted, one scale local)
#ifdef NON_MATCHING
void func_80106FD8_pipe_cleaners(omObjData *obj, u16 chr, f32 frame, s32 state) {
    f32 base = 1.0f;
    f32 div = 1.0f;
    f32 scale;

    if (state < 3) {
        div = 40.0f;
        base = 0.5f;
    } else {
        switch (chr) {
            case 0:
            case 2:
            case 7:
                div = 50.0f;
                base = 0.6f;
                break;
            case 1:
            case 4:
            case 6:
                div = 0.0f;
                base = 1.0f;
                break;
            case 3:
                div = 100.0f;
                base = 0.8f;
                break;
            case 5:
                if (state == 3) {
                    div = 0.0f;
                    base = 1.0f;
                } else {
                    div = 100.0f;
                    base = 0.8f;
                }
                break;
        }
    }
    if (div == 0.0f) {
        Hu3DModelScaleSet(obj->model[1], base, 1.0f, base);
    } else {
        if (frame < 20.0f) {
            scale = 20.0f - frame;
        } else {
            scale = frame - 20.0f;
        }
        Hu3DModelScaleSet(obj->model[1], base + scale / div, 1.0f, base + scale / div);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106FD8_pipe_cleaners);
#endif

/* Pulling: at frame 16 the pipe under the hook is pulled (a point). */
void func_80107114_pipe_cleaners(omObjData *obj) {
    PcPlayer *player = &D_8010AB30_pipe_cleaners[obj->work[0]];
    PcPipe *pipe = &D_8010A968_pipe_cleaners[player->state - 1 + obj->work[0] * 4];
    f32 frame = HmfModelData[obj->model[0]].unk40;

    if (frame == 16.0f) {
        if (pipe->state != 0 && pipe->state != 4) {
            pipe->next = 4;
            pipe->init = 0;
            func_801060D4_pipe_cleaners(player->state - 1 + obj->work[0] * 4);
            HuAudFXPlay(0x436);
            func_8004AC98_main(0x437, obj->work[0]);
            func_8001C814_main(obj->model[0], 4, 4);
            player->score++;
            if (!(GwPlayer[obj->work[0]].stat & 1)) {
                omVibrate(obj->work[0], 10, 0, 10);
            }
        }
    } else if (HmfModelData[obj->model[0]].unk40 == 0.0f) {
        func_80106A70_pipe_cleaners(obj, 0);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C6A8_main(obj->model[0], 0.0f);
        player->state = 0;
    }
    func_80106FD8_pipe_cleaners(obj, GwPlayer[obj->work[0]].chr, frame, player->state);
}

void func_8010731C_pipe_cleaners(omObjData *obj) {
    s16 model = obj->model[0];

    if (HmfModelData[model].unk40 == D_800CCF58_main[HmfModelData[model].unk02].unk02 - 2) {
        func_8001C814_main(model, 1, 1);
    }
}

void func_801073A4_pipe_cleaners(omObjData *obj) {
    s16 model = obj->model[0];

    if (HmfModelData[model].unk40 == D_800CCF58_main[HmfModelData[model].unk02].unk02 - 2) {
        func_8001C814_main(model, 1, 1);
    }
}

void func_8010742C_pipe_cleaners(omObjData *obj) {
    PcPlayer *player;

    if (GwPlayer[obj->work[0]].stat & 1) {
        func_801066E4_pipe_cleaners(obj);
    }
    if (D_8010A2F0_pipe_cleaners != 2) {
        func_80105B3C_pipe_cleaners(obj->work[0]);
    }
    player = &D_8010AB30_pipe_cleaners[obj->work[0]];
    switch (player->state) {
        case 0:
            func_80106E10_pipe_cleaners(obj);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            func_80107114_pipe_cleaners(obj);
            break;
        case 5:
            func_8010731C_pipe_cleaners(obj);
            break;
        case 6:
            func_801073A4_pipe_cleaners(obj);
            break;
    }
    if (D_8010A2F0_pipe_cleaners == 4) {
        switch (player->hookState) {
            case 0:
                func_80106B18_pipe_cleaners(obj, player);
                break;
            case 1:
                func_80106BF8_pipe_cleaners(obj, player);
                break;
            case 2:
                func_80106CB4_pipe_cleaners(obj, player);
                func_80105E94_pipe_cleaners(obj->work[0]);
                break;
        }
    }
}

void func_80107598_pipe_cleaners(omObjData *obj) {
    PcPlayer *player = &D_8010AB30_pipe_cleaners[obj->work[0]];
    u16 chr;
    s32 dir;
    s32 i;
    s32 diff;

    player->state = 0;
    player->obj = obj;
    player->score = 0;
    player->rank = 0;
    player->hookState = 0;
    player->hookRot = 0.0f;
    player->unk18 = 0;
    player->hookPos.x = player->hookPos.y = player->hookPos.z = 0.0f;
    chr = GwPlayer[obj->work[0]].chr;
    dir = D_800A178C_main[chr][0];
    obj->model[0] = func_8000B108_main(dir | D_800A178C_main[chr][2], 0x2A9);
    for (i = 0; i < 3; i++) {
        D_8010A2B0_pipe_cleaners[obj->work[0]][i] = DataRead(dir | D_80109F30_pipe_cleaners[chr][i]);
    }
    D_8010A2E0_pipe_cleaners[obj->work[0]] = HmfAnimCreate(HmfModelData[obj->model[0]].hmf,
        D_8010A2B0_pipe_cleaners[obj->work[0]][0], 0, D_80109F60_pipe_cleaners[chr]);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x18));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x68));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x69));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x6A));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x6B));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0));
    func_80106A70_pipe_cleaners(obj, 0);
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(*(HuMtx4F *)HmfModelData[obj->model[1]].mtx, 0.0f, 10.0f, 50.0f);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->model[2] = func_8000B108_main(0x480003, 0x299);
    func_8001C258_main(obj->model[2], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[2], obj->model[0], "item_hook");
    func_8001C8A8_main(obj->model[0], 1 << obj->work[0]);
    func_8001C8A8_main(obj->model[1], 1 << obj->work[0]);
    func_8001C8A8_main(obj->model[2], 1 << obj->work[0]);
    diff = GwPlayer[obj->work[0]].cpu_difficulty;
    player->cpuAimChance = D_80109EC0_pipe_cleaners[diff][0];
    player->cpuPullChance = D_80109EC0_pipe_cleaners[diff][1];
    player->cpuWait = D_80109EC0_pipe_cleaners[diff][2];
    player->cpuTimer = (rand8() % player->cpuWait) * 5;
    obj->func = func_8010742C_pipe_cleaners;
}

void func_80107A48_pipe_cleaners(void) {
    u16 player = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                player = 0;
                break;
            case 1:
                player = 1;
                break;
            case 2:
                player = 2;
                break;
            case 3:
                player = 3;
                break;
        }
        omAddObj(300, 9, 60, -1, func_80107598_pipe_cleaners)->work[0] = player;
    }
}

/* Pipe state 0: down (hidden). */
void func_80107B28_pipe_cleaners(omObjData *obj) {
    PcPipePos *pos = &D_80109F80_pipe_cleaners[obj->work[0] & 3];
    PcPipe *pipe = &D_8010A968_pipe_cleaners[obj->work[0]];

    if (pipe->init == 0) {
        pipe->init = 1;
        obj->trans.x = pos->x;
        obj->trans.y = pos->y;
        obj->trans.z = pos->z;
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        func_8001C6A8_main(obj->model[0], 0.0f);
        func_8001C814_main(obj->model[0], 1, 1);
        Hu3DModelScaleSet(obj->model[0], 0.1f, 0.1f, 0.1f);
        func_80032FF8_main((s16)obj->work[1], 0);
    }
}

/* Pipe state 1: rising. */
void func_80107C08_pipe_cleaners(omObjData *obj) {
    PcPipe *pipe = &D_8010A968_pipe_cleaners[obj->work[0]];

    if (pipe->init == 0) {
        pipe->init = 1;
        pipe->timer = 0;
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C6A8_main(obj->model[0], 0.0f);
        Hu3DModelScaleSet(obj->model[0], 1.0f, 1.0f, 1.0f);
        func_80034048_main(obj->work[1], 0);
        func_80032FC0_main(obj->work[1], 1, 0);
    }
    obj->trans.y += D_80109FD0_pipe_cleaners[pipe->timer] * D_80109F80_pipe_cleaners[obj->work[0] & 3].dir;
    if (pipe->timer == 14) {
        func_8001C814_main(obj->model[0], 1, 1);
        switch (pipe->kind) {
            case 0:
            case 2:
                pipe->next = 2;
                break;
            case 1:
                pipe->next = 3;
                break;
        }
        pipe->init = 0;
    }
    pipe->timer++;
}

/* Pipe state 2: up, waiting. */
void func_80107D84_pipe_cleaners(omObjData *obj) {
    PcPipe *pipe = &D_8010A968_pipe_cleaners[obj->work[0]];
    s32 wait;

    if (pipe->init == 0) {
        pipe->init = 1;
        pipe->timer = 0;
        func_8001C814_main(obj->model[0], 1, 1);
        Hu3DModelScaleSet(obj->model[0], 1.0f, 1.0f, 1.0f);
    }
    wait = 119;
    if (pipe->kind == 0) {
        wait = 29;
    }
    if (pipe->timer == wait) {
        pipe->next = 3;
        pipe->init = 0;
    }
    pipe->timer++;
}

/* Pipe state 3: lowering. */
void func_80107E3C_pipe_cleaners(omObjData *obj) {
    PcPipe *pipe = &D_8010A968_pipe_cleaners[obj->work[0]];
    s32 done;

    if (pipe->init == 0) {
        pipe->init = 1;
        pipe->timer = 0;
        if (pipe->pulled == 0) {
            func_8001C5B4_main(obj->model[0], obj->motion[0]);
            func_8001C814_main(obj->model[0], 4, 4);
            func_8001C6A8_main(obj->model[0], 30.0f);
            Hu3DModelScaleSet(obj->model[0], 1.0f, 1.0f, 1.0f);
            func_80032FF8_main((s16)obj->work[1], 1);
        }
    }
    obj->trans.y -= D_80109FD0_pipe_cleaners[pipe->timer] * D_80109F80_pipe_cleaners[obj->work[0] & 3].dir;
    done = 0;
    if (D_80109F80_pipe_cleaners[obj->work[0] & 3].dir == -1) {
        if (D_80109F80_pipe_cleaners[obj->work[0] & 3].y <= obj->trans.y) {
            done = 1;
        }
    } else if (obj->trans.y <= D_80109F80_pipe_cleaners[obj->work[0] & 3].y) {
        done = 1;
    }
    if (pipe->timer >= 14 || done) {
        func_8001C814_main(obj->model[0], 1, 1);
        Hu3DModelScaleSet(obj->model[0], 0.1f, 0.1f, 0.1f);
        pipe->next = 0;
        pipe->init = 0;
        pipe->pulled = 0;
    }
    pipe->timer++;
}

/* Pipe state 4: pulled. */
void func_8010801C_pipe_cleaners(omObjData *obj) {
    PcPipe *pipe = &D_8010A968_pipe_cleaners[obj->work[0]];

    if (pipe->init == 0) {
        pipe->init = 1;
        pipe->timer = 0;
        func_8001C5B4_main(obj->model[0], obj->motion[1]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C6A8_main(obj->model[0], 0.0f);
        Hu3DModelScaleSet(obj->model[0], 1.0f, 1.0f, 1.0f);
        func_80032FF8_main((s16)obj->work[1], 2);
        pipe->next = 3;
        pipe->init = 0;
        pipe->pulled = 1;
    }
    pipe->timer++;
}

void func_801080F4_pipe_cleaners(omObjData *obj) {
    PcPipe *pipe = &D_8010A968_pipe_cleaners[obj->work[0]];

    switch (pipe->state = pipe->next) {
        case 0:
            func_80107B28_pipe_cleaners(obj);
            break;
        case 1:
            func_80107C08_pipe_cleaners(obj);
            break;
        case 2:
            func_80107D84_pipe_cleaners(obj);
            break;
        case 3:
            func_80107E3C_pipe_cleaners(obj);
            break;
        case 4:
            func_8010801C_pipe_cleaners(obj);
            break;
    }
}

void func_80108194_pipe_cleaners(omObjData *obj) {
    PcPipe *pipe = &D_8010A968_pipe_cleaners[obj->work[0]];
    void *data;
    s16 anim;

    obj->model[0] = func_8000B108_main(0x480006, 0x289);
    func_8000B460_main(obj, 0, 0x480007);
    func_8000B460_main(obj, 1, 0x480008);
    if (obj->work[0] == 0) {
        data = DataRead(0x480009);
        anim = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "s239_001_DEF");
        D_8010A828_pipe_cleaners = anim;
        obj->work[1] = anim;
        HuMemMemoryFreePerm(data);
    } else {
        obj->work[1] = func_80032694_main(HmfModelData[obj->model[0]].hmf, D_8010A828_pipe_cleaners, 0, "s239_001_DEF");
    }
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_80034048_main(obj->work[1], 0);
    func_80032FC0_main(obj->work[1], 1, 1);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 1, 1);
    pipe->obj = obj;
    pipe->state = 0;
    pipe->next = 0;
    pipe->timer = 0;
    pipe->init = 0;
    pipe->kind = 0;
    pipe->pulled = 0;
    obj->trans.x = D_80109F80_pipe_cleaners[obj->work[0] & 3].x;
    obj->trans.y = D_80109F80_pipe_cleaners[obj->work[0] & 3].y;
    obj->trans.z = D_80109F80_pipe_cleaners[obj->work[0] & 3].z;
    obj->rot.z = D_80109F80_pipe_cleaners[obj->work[0] & 3].rotZ;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 1 << (obj->work[0] >> 2));
    obj->func = func_801080F4_pipe_cleaners;
}

void func_80108428_pipe_cleaners(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(200, 1, 2, -1, func_80108194_pipe_cleaners)->work[0] = i;
    }
}

/* Builds each player's pipe schedule: 60 slots, two per step, -1 empty;
   a value is the pipe (0..3), +4 for a long wait. */
// decomp-permuter
void func_80108484_pipe_cleaners(void)
{
  s32 step[26];
  u32 i;
  int new_var;
  u32 j;
  s32 longStep;
  s32 slot;
  s32 extra;
  s8 *sched;
  s32 pipe;
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 60; j++)
    {
      D_8010A838_pipe_cleaners[i][j] = -1;
    }

  }

  longStep = 0;
  for (j = 0; j < 26; j++)
  {
    step[j] = -1;
  }

  for (i = 0; i < 4; i++)
  {
    extra = ((u8) (rand8() % 22)) + 3;
    sched = D_8010A838_pipe_cleaners[i];
    for (j = 0; j < 25; j++)
    {
      step[j] = rand8() & 3;
      if ((j & 1) && (step[j] == step[j - 1]))
      {
        j--;
        continue;
      }
      if ((j & 3) == 0)
      {
        longStep = j;
        new_var = 1;
        longStep = (((u8) (rand8() % 3)) + new_var) + longStep;
      }
      if (j == longStep)
      {
        step[j] += 4;
      }
      slot = (j * 2) + (rand8() & 1);
      sched[slot] = step[j];
      if (j == extra)
      {
        do
        {
          pipe = rand8() & 3;
        }
        while (((pipe == (sched + slot)[-1]) || (pipe == (sched + slot)[-2])) || (pipe == (sched + slot)[-3]));
        if (slot & 1)
        {
          D_8010A838_pipe_cleaners[i][slot - 1] = pipe;
        }
        else
        {
          D_8010A838_pipe_cleaners[i][slot + 1] = pipe;
        }
      }
    }

  }

}

/* Raises the pipes the schedule names, every 15 frames.
 * NON_MATCHING (H1): masked 4 at 115/115, register residue only: retail copies step into $a1
 * (move a1,v0) and computes slot in the bne delay slot; which lands in $a0. */
#ifdef NON_MATCHING
void func_80108708_pipe_cleaners(void) {
    s32 i;
    s32 j;
    s32 value;
    s32 step;
    PcPipe *pipe;
    s32 slot;
    s32 which;

    if (D_8010AC10_pipe_cleaners < 900) {
        if (D_8010AC10_pipe_cleaners >= 89) {
            if (D_8010AC10_pipe_cleaners == 89) {
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 4; j++) {
                        pipe = &D_8010A968_pipe_cleaners[i * 4 + j];
                        pipe->kind = 2;
                        pipe->next = 1;
                        pipe->init = 0;
                    }
                }
                return;
            }
            step = D_8010AC10_pipe_cleaners / 15;
            slot = 59 - step;
            if (step * 15 == D_8010AC10_pipe_cleaners - 14) {
                for (i = 0; i < 4; i++) {
                    value = D_8010A838_pipe_cleaners[i][slot];
                    if (value != -1) {
                        which = value & 3;
                        value /= 4;
                        pipe = &D_8010A968_pipe_cleaners[i * 4 + which];
                        if (pipe->state != 0) {
                            for (j = 0; j < 4; j++) {
                                pipe = &D_8010A968_pipe_cleaners[i * 4 + j];
                                if (pipe->state == 0) {
                                    break;
                                }
                            }
                        }
                        if (pipe->state == 0) {
                            if (value == 0) {
                                pipe->kind = 0;
                            } else {
                                pipe->kind = 1;
                            }
                            pipe->next = 1;
                            pipe->init = 0;
                        }
                    }
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108708_pipe_cleaners);
#endif

void func_801088AC_pipe_cleaners(PcDigit *digit, s32 arg1) {
    if (arg1 != 0) {
        if (digit->scale < 1.0f) {
            digit->scale += 0.1;
            if (digit->scale >= 1.0f) {
                digit->scale = 1.0f;
            }
        } else {
            digit->scale = 1.0f;
        }
    } else {
        if (digit->scale < 1.0f) {
            digit->scale += 0.1;
            if (digit->scale >= 1.0f) {
                digit->scale = 1.0f;
            }
        } else {
            digit->scale = 1.0f;
        }
    }
    func_8000BE5C_main(digit->spr, digit->scale, digit->scale);
}

void func_80108964_pipe_cleaners(PcDigit *digit, s32 arg1) {
    if (arg1 != 0) {
        digit->scale -= 0.1;
    } else {
        digit->scale -= 0.1;
    }
    if (digit->scale <= 0.1) {
        digit->scale = 0.1f;
    }
    func_8000BE5C_main(digit->spr, digit->scale, digit->scale);
    if (digit->alpha > 20.0f) {
        digit->alpha = digit->alpha - 25.5;
    } else {
        digit->alpha = 1.0f;
    }
    func_8000BBFC_main(digit->spr, digit->alpha);
}

/* Score display: grows in, rolls random digits, shows the score, fades. */
#ifdef NON_MATCHING
void func_80108A4C_pipe_cleaners(omObjData *obj) {
    PcPlayer *player;
    PcDigit *digit;
    s32 i;

    if (D_8010A2F0_pipe_cleaners != 5) {
        for (i = 0; i < 16; i++) {
            digit = &D_8010AC18_pipe_cleaners[i];
            func_8000BB94_main(digit->spr);
            digit->active = 0;
        }
        D_8010AD58_pipe_cleaners = 16;
        D_8010A82C_pipe_cleaners = 0;
        return;
    }
    for (i = 0; i < 16; i++) {
        digit = &D_8010AC18_pipe_cleaners[i];
        if (digit->active == 0) {
            digit->active = 1;
            digit->scale = 0.0f;
            digit->alpha = 255.0f;
            digit->value = 0;
        }
    }
    if (D_8010AD58_pipe_cleaners > 0) {
        D_8010AD58_pipe_cleaners--;
        if (D_8010A82C_pipe_cleaners == 2 && D_8010A030_pipe_cleaners == -1) {
            D_8010A030_pipe_cleaners = HuAudFXPlay(0x3EC);
        }
    } else {
        switch (++D_8010A82C_pipe_cleaners) {
            case 1:
                D_8010AD58_pipe_cleaners = 15;
                break;
            case 2:
                if (D_8010A030_pipe_cleaners == -1) {
                    D_8010A030_pipe_cleaners = HuAudFXPlay(0x3EC);
                }
                D_8010AD58_pipe_cleaners = 60;
                break;
            case 3:
                HuAudFXPlay(0x3ED);
                D_8010AD58_pipe_cleaners = 30;
                break;
            case 4:
                D_8010AD58_pipe_cleaners = 16;
                break;
        }
    }
    for (i = 0; i < 4; i++) {
        player = &D_8010AB30_pipe_cleaners[i];
        digit = &D_8010AC18_pipe_cleaners[i * 4];
        func_8000BB54_main(digit->spr);
        switch (D_8010A82C_pipe_cleaners) {
            case 0:
                func_801088AC_pipe_cleaners(digit, 1);
                break;
            case 4:
                func_80108964_pipe_cleaners(digit, 1);
                break;
        }
        digit = &D_8010AC18_pipe_cleaners[i * 4 + 1];
        func_8000BB54_main(digit->spr);
        switch (D_8010A82C_pipe_cleaners) {
            case 0:
                func_801088AC_pipe_cleaners(digit, 0);
                break;
            case 4:
                func_80108964_pipe_cleaners(digit, 0);
                break;
        }
        digit = &D_8010AC18_pipe_cleaners[i * 4 + 2];
        func_8000BD50_main(digit->spr, digit->value / 10);
        func_8000BB54_main(digit->spr);
        switch (D_8010A82C_pipe_cleaners) {
            case 0:
                func_801088AC_pipe_cleaners(digit, 0);
                break;
            case 2:
                digit->value = (u8)(rand8() % 100);
                break;
            case 3:
                digit->value = player->score;
                break;
            case 4:
                func_80108964_pipe_cleaners(digit, 0);
                break;
        }
        digit = &D_8010AC18_pipe_cleaners[i * 4 + 3];
        func_8000BD50_main(digit->spr, digit->value % 10);
        func_8000BB54_main(digit->spr);
        switch (D_8010A82C_pipe_cleaners) {
            case 0:
                func_801088AC_pipe_cleaners(digit, 0);
                break;
            case 2:
                digit->value = (u8)(rand8() % 100);
                break;
            case 3:
                digit->value = player->score;
                break;
            case 4:
                func_80108964_pipe_cleaners(digit, 0);
                break;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108A4C_pipe_cleaners);
#endif

void func_80108F18_pipe_cleaners(omObjData *obj) {
    s32 grp0;
    s32 grp1;
    s32 grp2;
    s32 i;
    PcDigit *digit;

    grp0 = func_8000B838_main(0x48000B);
    grp1 = func_8000B838_main(0x21001B);
    grp2 = func_8000B838_main(0x2E);
    for (i = 0; i < 4; i++) {
        digit = &D_8010AC18_pipe_cleaners[i * 4];
        digit->spr = InitEspriteSlot(grp0, 0, 0);
        func_8000BC48_main(digit->spr, 0x1000);
        func_8000BE5C_main(digit->spr, 1.0f, 1.0f);
        func_8000BBD4_main(digit->spr, (s16)D_8010A010_pipe_cleaners[i].x - 30, D_8010A010_pipe_cleaners[i].y);
        func_8000BB94_main(digit->spr);
        digit = &D_8010AC18_pipe_cleaners[i * 4 + 1];
        digit->spr = InitEspriteSlot(grp1, 0, 0);
        func_8000BC48_main(digit->spr, 0x1000);
        func_8000BE5C_main(digit->spr, 2.0f, 2.0f);
        func_8000BBD4_main(digit->spr, D_8010A010_pipe_cleaners[i].x, D_8010A010_pipe_cleaners[i].y);
        func_8000BB94_main(digit->spr);
        digit = &D_8010AC18_pipe_cleaners[i * 4 + 2];
        digit->spr = InitEspriteSlot(grp2, 0, 0);
        func_8000BC48_main(digit->spr, 0x1000);
        func_8000BE5C_main(digit->spr, 1.0f, 1.0f);
        func_8000BBD4_main(digit->spr, (s16)D_8010A010_pipe_cleaners[i].x + 20, D_8010A010_pipe_cleaners[i].y);
        func_8000BB94_main(digit->spr);
        digit = &D_8010AC18_pipe_cleaners[i * 4 + 3];
        digit->spr = InitEspriteSlot(grp2, 0, 0);
        func_8000BC48_main(digit->spr, 0x1000);
        func_8000BE5C_main(digit->spr, 1.0f, 1.0f);
        func_8000BBD4_main(digit->spr, (s16)D_8010A010_pipe_cleaners[i].x + 40, D_8010A010_pipe_cleaners[i].y);
        func_8000BB94_main(digit->spr);
    }
    obj->func = func_80108A4C_pipe_cleaners;
}

void func_801091E4_pipe_cleaners(void) {
    omAddObj(600, 1, 0, -1, func_80108F18_pipe_cleaners);
}

/* Ranks the players by score (0 = most). */
void func_80109218_pipe_cleaners(void) {
    s16 i;
    s16 j;
    u16 scores[4];
    u16 temp;
    u16 done;
    PcPlayer *player;

    for (j = 0; j < 4; j++) {
        scores[j] = D_8010AB30_pipe_cleaners[j].score;
    }
    for (i = 0; i < 3; i++) {
        for (j = 3; j > i; j--) {
            if (scores[j] > scores[j - 1]) {
                temp = scores[j];
                scores[j] = scores[j - 1];
                scores[j - 1] = temp;
            }
        }
    }
    done = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            player = &D_8010AB30_pipe_cleaners[j];
            if (!((done >> j) & 1) && player->score == scores[i]) {
                player->rank = i;
                done |= 1 << j;
            }
        }
    }
}

/* Results: winners (rank 0) get 10 coins; a tie of all four at 0 is a draw. */
void func_801093A4_pipe_cleaners(void) {
    s32 chars[4];
    PcPlayer *player;
    s32 i;
    u32 count;

    for (i = 0; i < 4; i++) {
        chars[i] = 0;
    }
    for (i = 1; i < 4; i++) {
        if (D_8010AB30_pipe_cleaners[i].score != D_8010AB30_pipe_cleaners[0].score) {
            break;
        }
    }
    count = 0;
    if (i == 4) {
        count = 4;
        if (D_8010AB30_pipe_cleaners[0].score == 0) {
            count = 0;
            for (i = 0; i < 4; i++) {
                player = &D_8010AB30_pipe_cleaners[i];
                func_80106DA4_pipe_cleaners(player);
                GwPlayer[player->obj->work[0]].bonusCoin = 0;
            }
        } else {
            for (i = 0; i < 4; i++) {
                player = &D_8010AB30_pipe_cleaners[i];
                chars[i] = GwPlayer[player->obj->work[0]].chr;
                func_80106CF4_pipe_cleaners(player);
                GwPlayer[player->obj->work[0]].bonusCoin = 10;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            player = &D_8010AB30_pipe_cleaners[i];
            if (D_8010AB30_pipe_cleaners[i].rank == 0) {
                chars[count] = GwPlayer[player->obj->work[0]].chr;
                count++;
                func_80106CF4_pipe_cleaners(player);
                GwPlayer[player->obj->work[0]].bonusCoin = 10;
            } else {
                func_80106DA4_pipe_cleaners(player);
                GwPlayer[player->obj->work[0]].bonusCoin = 0;
            }
        }
    }
    switch (count) {
        case 0:
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
            break;
        case 1:
            GMesCreate(0x16, chars[0]);
            HuAudSeqPlay(0x65);
            break;
        case 2:
            GMesCreate(0x1E, chars[0], chars[1]);
            HuAudSeqPlay(0x66);
            break;
        case 3:
            GMesCreate(0x22, chars[0], chars[1], chars[2]);
            HuAudSeqPlay(0x66);
            break;
        case 4:
            GMesCreate(0x23, chars[0], chars[1], chars[2], chars[3]);
            HuAudSeqPlay(0x66);
            break;
    }
}

void func_801096C0_pipe_cleaners(void) {
    u32 i;

    if (D_8010A034_pipe_cleaners == 0) {
        D_8010A034_pipe_cleaners = 1;
        for (i = 0; i < 4; i++) {
            CZoomM[i] = 1500.0f;
            CRotM[i].x = 357.631f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = 160.0f;
            CenterM[i].z = -30.0f;
        }
    }
}

void func_80109784_pipe_cleaners(omObjData *obj) {
    u8 i;
    u8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            DataClose(D_8010A2B0_pipe_cleaners[i][j]);
        }
        func_80033354_main(D_8010A2E0_pipe_cleaners[i]);
    }
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010984C_pipe_cleaners(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_80109784_pipe_cleaners;
    }
}

void func_80109884_pipe_cleaners(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010984C_pipe_cleaners;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_801098DC_pipe_cleaners(omObjData *obj) {
    switch (D_8010A2F0_pipe_cleaners) {
        case 0:
            GMesCreate(3);
            D_8010A2F0_pipe_cleaners = 1;
            break;
        case 1:
            if (++D_8010A038_pipe_cleaners == 13) {
                HuAudSeqPlay(0x36);
            }
            if (GMesStatGet() == 0 || (GMesStatGet() & 2)) {
                D_8010A2F0_pipe_cleaners = 2;
                GMesCreate(0x1A, 30, 160, 28);
                D_8010AC10_pipe_cleaners = 901;
            }
            break;
        case 2:
            func_80108708_pipe_cleaners();
            if (D_8010AC10_pipe_cleaners > 0) {
                D_8010AC10_pipe_cleaners--;
                func_8003F578_main((D_8010AC10_pipe_cleaners + 29) / 30);
            } else {
                func_8003F5C0_main();
                D_8010AC10_pipe_cleaners = 15;
                D_8010A2F0_pipe_cleaners = 3;
            }
            break;
        case 3:
            if (--D_8010AC10_pipe_cleaners == 0) {
                GMesCreate(0xE);
                HuAudSeqFadeOut(120);
                D_8010A2F0_pipe_cleaners = 4;
            }
            break;
        case 4:
            if (GMesStatGet() == 0) {
                func_80109218_pipe_cleaners();
                D_8010AC10_pipe_cleaners = 135;
                D_8010A2F0_pipe_cleaners = 5;
            }
            break;
        case 5:
            if (--D_8010AC10_pipe_cleaners == 0) {
                D_8010AC10_pipe_cleaners = 1;
                D_8010A2F0_pipe_cleaners = 6;
            }
            break;
        case 6:
            if (--D_8010AC10_pipe_cleaners == 0) {
                func_801093A4_pipe_cleaners();
                D_8010A2F0_pipe_cleaners = 7;
            }
            break;
        case 7:
            if (D_8010A03C_pipe_cleaners == 0) {
                if (GMesStatGet() & 2) {
                    D_8010A03C_pipe_cleaners = 1;
                    D_8010AC10_pipe_cleaners = 20;
                }
            } else if (--D_8010AC10_pipe_cleaners <= 0) {
                WipeCreateOut(0, 20);
                obj->func = func_8010984C_pipe_cleaners;
            }
            break;
    }
    func_801096C0_pipe_cleaners();
}

void func_80109B74_pipe_cleaners(omObjData *obj) {
    WipeCreateIn(0xFF, 16);
    func_80105DB4_pipe_cleaners();
    func_80105E60_pipe_cleaners();
    func_80108428_pipe_cleaners();
    func_8010638C_pipe_cleaners();
    func_80107A48_pipe_cleaners();
    func_80108484_pipe_cleaners();
    func_801091E4_pipe_cleaners();
    func_80106078_pipe_cleaners();
    D_8010A2F0_pipe_cleaners = 0;
    obj->func = func_801098DC_pipe_cleaners;
}

void func_80109BF4_pipe_cleaners(void) {
}

void func_80109BFC_pipe_cleaners(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 4;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(4);
    func_8000B710_main(4);
    for (i = 0; i < 4; i++) {
        ScissorSet(i, D_8010A040_pipe_cleaners[i].scissor[0], D_8010A040_pipe_cleaners[i].scissor[1],
                   D_8010A040_pipe_cleaners[i].scissor[2], D_8010A040_pipe_cleaners[i].scissor[3]);
        ViewportSet(i, D_8010A040_pipe_cleaners[i].viewport[0], D_8010A040_pipe_cleaners[i].viewport[1],
                    D_8010A040_pipe_cleaners[i].viewport[2], D_8010A040_pipe_cleaners[i].viewport[3],
                    D_8010A040_pipe_cleaners[i].viewport[4], D_8010A040_pipe_cleaners[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8010A040_pipe_cleaners[i].fov, 80.0f, 8000.0f);
    }
}

void func_80109D70_pipe_cleaners(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(60, 0);
    func_8004A208_main();
    func_80109BFC_pipe_cleaners();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010A2A8_pipe_cleaners, 0);
    func_80045010_main(D_8010A2A8_pipe_cleaners, 1);
    omAddObj(1000, 0, 0, -1, func_80109B74_pipe_cleaners);
    omAddObj(1000, 0, 0, -1, func_80109884_pipe_cleaners);
    func_80105A74_pipe_cleaners();
}

/* Shift-JIS fullwidth "ABC", passed to func_80045010_main. */
const s16 D_8010A2A8_pipe_cleaners[] = { 0x8260, 0x8261, 0x8262, 0 };
