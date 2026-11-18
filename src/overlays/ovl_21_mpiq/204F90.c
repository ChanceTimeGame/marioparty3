#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/data.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"

// m4 mq: M.P.I.Q. (quiz show: buzz in and answer)

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_80045C2C_main(void);
void func_8004AD70_main(void);
void func_8005F524_main(void);
void func_800557A0_main(void);
extern u16 D_800D530C_main;
extern Vec Center;
extern Vec CRot;
extern f32 CZoom;

// minigame
extern s32 D_800EBEB0_minigame[];
extern f32 D_800EB774_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBE24_minigame;

// LOCAL
void func_80105C60_mpiq(omObjData* obj);
void func_80105D60_mpiq(omObjData* obj);
void func_80105DA4_mpiq(omObjData* obj);
void func_80105DC0_mpiq(omObjData* obj);
void func_80105DDC_mpiq(omObjData* obj);
void func_80105DF8_mpiq(omObjData* obj);
void func_80105E14_mpiq(omObjData* obj, s32 player);
void func_80106B5C_mpiq(void);
void func_80106E98_mpiq(void);
void func_8010720C_mpiq(void);
void func_80107584_mpiq(void);
void func_80107D70_mpiq(void);
void func_80107F28_mpiq(void);
void func_80108178_mpiq(void);
void func_80108688_mpiq(void);
void func_80108A3C_mpiq(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z);
void func_80108B74_mpiq(void);
void func_80109414_mpiq(void);
void func_8010B0CC_mpiq(void);
void func_8010C5B8_mpiq(omObjData* obj);

extern D_80111B50_vine_with_me_Struct D_8010C680_mpiq;
extern s32 D_8010C9B4_mpiq; /* camera */
extern s8 D_8010C9B8_mpiq;
extern s16 D_8010C9BA_mpiq;
extern s16 D_8010C9C2_mpiq;
extern s32 D_8010C9D8_mpiq; /* winner, -1 none */
extern s32 D_8010C9F8_mpiq;
extern s32 D_8010C9FC_mpiq;
extern s16 D_8010CA00_mpiq;
extern s32 D_8010D020_mpiq;
typedef func_800E1BA8_minigame_ObjData MgWork;
void func_80012D0C_main(s16 camIndex, f32 dist, Vec2f* in, Vec2f* out);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
extern s32 D_800A178C_main[][6];
void func_8010651C_mpiq(omObjData* obj);
s16 func_80106658_mpiq(void);
extern f32 D_8010C6A8_mpiq[4]; /* player x on screen */
extern s32 D_8010C9C8_mpiq[4];
extern s32 D_8010C9E8_mpiq[4];
void func_800DDD94_minigame(omObjData* obj);
s16 func_8005B5EC_main(void* win);

/* CPU answer plan per player */
typedef struct MqCpu {
    /* 0x00 */ s32 unk00; /* buzz delay */
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08; /* answer button */
} MqCpu; // Size 0xC
extern MqCpu D_8010CA08_mpiq[4];
extern s16 D_8010CA38_mpiq[10]; /* right answer per question */
extern s16 D_8010CA4C_mpiq; /* question */
extern void* D_8010CA50_mpiq[10]; /* question messages */
void func_8000BC48_main(u16, u16);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BBFC_main(u16, u8);
void func_800E1490_minigame(u16 arg0);
extern omObjData* D_800EC1C0_minigame[];

/* The stage object's data (func_80106B5C_mpiq) */
typedef struct MqStage {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[3];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ char unk0C[0xA4];
    /* 0xB0 */ void* unkB0; /* 0x14-byte block (podiums) */
} MqStage; // Size 0xB4 on N64

void func_80107114_mpiq(void);
extern f32 D_8010C9B0_mpiq;
extern s32 D_8010C9BC_mpiq; /* player answering */
extern s16 D_8010C9DC_mpiq[2];
extern s16 D_8010C9E0_mpiq;
extern s16 D_8010C9E2_mpiq;
extern omObjData* D_8010CA78_mpiq;
void func_80107168_mpiq(omObjData* obj);
void func_800E13CC_minigame(omObjData* obj, f32 arg1, f32 arg2, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_8010747C_mpiq(omObjData* obj);
void func_80107774_mpiq(omObjData* obj);

/* A player's buzzer lamp (func_80107584_mpiq, D_8010CAC0_mpiq) */
typedef struct MqLamp {
    /* 0x00 */ f32 unk00; /* position */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08; /* fall speed */
    /* 0x0C */ f32 unk0C; /* rest height */
    /* 0x10 */ s32 unk10; /* flags */
    /* 0x14 */ s32 unk14; /* timer */
    /* 0x18 */ s32 unk18; /* player */
    /* 0x1C */ f32 unk1C; /* flash scale */
    /* 0x20 */ s32 unk20; /* flash alpha */
    /* 0x24 */ s16 unk24;
} MqLamp; // Size 0x28

extern omObjData* D_8010CA80_mpiq[4]; /* podiums */
extern s32 D_8010CA90_mpiq[4]; /* podium flags: 1 rising */
extern s32 D_8010CAA0_mpiq[4]; /* podium level (correct answers) */
extern f32 D_8010CAB0_mpiq[3]; /* podium height per level */
extern omObjData* D_8010CAC0_mpiq[4]; /* lamps */
void func_800E12EC_minigame(omObjData* obj, f32 arg1);
void func_800E561C_minigame(omObjData* obj, u8 flags);
void func_800E58F8_minigame(omObjData* obj, s32 a, s32 b);
void func_80107E90_mpiq(f32 x, f32 y, f32 z);
s16 func_801089D0_mpiq(omObjData* a, omObjData* b);
void func_80107DE0_mpiq(omObjData* obj);
extern s16 D_8010C9BE_mpiq; /* pad of the player answering */
extern omObjData* D_8010CAD0_mpiq; /* buzz effect */
void func_8001C6A8_main(s32 arg0, f32 arg1);
void func_80107FC4_mpiq(omObjData* obj);
void func_80108494_mpiq(omObjData* obj);
extern omObjData* D_8010CAD4_mpiq; /* "correct" effect */

/* Effect object data (D_8010CAD4_mpiq) */
typedef struct MqFx {
    /* 0x00 */ s32 unk00; /* flags */
    /* 0x04 */ s32 unk04; /* use count */
} MqFx; // Size 8

/* A player's score column (D_8010CAD8_mpiq) */
typedef struct MqColumn {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ f32 unk08; /* x */
    /* 0x0C */ char unk0C[0xC];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C[3]; /* block heights */
    /* 0x28 */ f32 unk28[3]; /* block y scale */
    /* 0x34 */ char unk34[4];
    /* 0x38 */ s32 unk38; /* blocks filled */
    /* 0x3C */ s32 unk3C; /* flags */
    /* 0x40 */ s32 unk40; /* player */
} MqColumn; // Size 0x44

extern omObjData* D_8010CAD8_mpiq[4]; /* score columns */
void func_801087F8_mpiq(omObjData* obj);

/* The host (D_8010CA78_mpiq) */
typedef struct MqHost {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ f32 unk08; /* rot y */
    /* 0x0C */ s32 unk0C; /* flags: 1 motion, 2 turn back, 4 turn */
} MqHost; // Size 0x10
void func_80108D10_mpiq(void);
void func_80108E20_mpiq(omObjData* obj);
void func_80109018_mpiq(void);

/* The answer buttons popup (D_8010CAE8_mpiq) */
typedef struct MqButtons {
    /* 0x00 */ f32 unk00; /* screen position */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ s32 unk08; /* flags: 1 grow, 2 shrink, 4/8/0x10 show A/B/C */
    /* 0x0C */ f32 unk0C; /* scale */
} MqButtons; // Size 0x10

extern u16 D_8010C9C0_mpiq;
extern omObjData* D_8010CAE8_mpiq;
extern s16 D_8010CAEC_mpiq[3]; /* button sprites */
extern s16 D_8010CAF2_mpiq[3]; /* button sprite files */
// LOCALEND

void func_801059A0_mpiq(void) {
    omObjData* obj;

    omInitObjMan(0x28, 0x14);
    Hu3DAnimInit(0x10);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    func_80045C2C_main();
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_80108A3C_mpiq(2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 420.0f, 0.0f);
    omOutView(obj);
    func_8001F38C_main(0, 0, 0);
    func_800E5EA0_minigame(&D_8010C680_mpiq);
    WipeCreateIn(0xFF, 0x10);
    D_800EBE28_minigame = 0;
    D_800EC280_minigame = 0;
    func_800E18D8_minigame();
    D_800EB774_minigame = 1.0f;
    D_8010C9F8_mpiq = 0;
    D_8010D020_mpiq = 0x3A;
    func_800E19F0_minigame(1);
    func_8005A6B0_main();
    func_80106B5C_mpiq();
    func_8010720C_mpiq();
    D_8010CA00_mpiq = -1;
    omSetStatBit(omAddObj(0x5000, 0, 0, -1, func_8010C5B8_mpiq), 0xA0);
    omAddObj(4, 0xA, 0x3C, -1, func_80105DA4_mpiq);
    omAddObj(4, 0xA, 0x3C, -1, func_80105DC0_mpiq);
    omAddObj(4, 0xA, 0x3C, -1, func_80105DDC_mpiq);
    omAddObj(4, 0xA, 0x3C, -1, func_80105DF8_mpiq);
    D_8010C9C2_mpiq = 1;
    func_80108B74_mpiq();
    D_8010C9FC_mpiq = 0;
    func_80109414_mpiq();
    omAddPrcObj(func_8010B0CC_mpiq, 0x5000, 0x1000, 0);
    func_80108688_mpiq();
    func_80108178_mpiq();
    omAddPrcObj(func_80106E98_mpiq, 0x4700, 0x1000, 0);
    omAddObj(0x5000, 0, 0, -1, func_80105C60_mpiq);
    func_80107584_mpiq();
    func_80107D70_mpiq();
    func_80107F28_mpiq();
    D_8010C9B8_mpiq = 0;
    D_8010C9BA_mpiq = 0;
    D_800EBE24_minigame = 0;
    D_800EB930_minigame = 0x31;
    D_800EB932_minigame = 0x3C;
}

void func_80105C60_mpiq(omObjData* obj) {
    if (D_800D530C_main != 0) {
        func_8004AD70_main();
        HuAudSeqFadeOut(0x1E);
        WipeCreateOut(0, 0x14);
    }
    switch (((u8 (*)(omObjData*))(void*)func_800E6F40_minigame)(obj)) { /* retail passes obj */
    case 0:
    case 1:
    case 2:
    case 4:
        break;
    case 3:
        if (D_8010C9D8_mpiq != -1) {
            D_8010C680_mpiq.unk06 = 0;
            D_8010C680_mpiq.unk18 = ((u8*)&D_8010C9D8_mpiq)[3];
        } else {
            D_8010C680_mpiq.unk06 = 4;
        }
        break;
    case 5:
        if (D_8010C9D8_mpiq != -1) {
            GwPlayer[D_8010C9D8_mpiq].bonusCoin += 10;
        }
        WipeCreateOut(0, 0x14);
        obj->func = func_80105D60_mpiq;
        break;
    }
}

void func_80105D60_mpiq(omObjData* obj) {
    if (WipeStatGet() == 0) {
        func_8005F524_main();
        GMesClose();
        func_800557A0_main();
        omOvlReturnEx(1);
    }
}

void func_80105DA4_mpiq(omObjData* obj) {
    func_80105E14_mpiq(obj, 0);
}

void func_80105DC0_mpiq(omObjData* obj) {
    func_80105E14_mpiq(obj, 1);
}

void func_80105DDC_mpiq(omObjData* obj) {
    func_80105E14_mpiq(obj, 2);
}

void func_80105DF8_mpiq(omObjData* obj) {
    func_80105E14_mpiq(obj, 3);
}

#ifdef NON_MATCHING
/* A player (podium contestant): model, motions, position. */
void func_80105E14_mpiq(omObjData* obj, s32 player) {
    Vec2f in;
    Vec out; /* only x, y written */
    s32 mot0[8] = { 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B };
    s32 mot1[8] = { 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B };
    s32 mot2[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
    s32 mot3[8] = { 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37 };
    s32 mot4[8] = { 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F };
    s32 mot5[8] = { 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C };
    s32 mot6[8] = { 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D };
    s32 mot7[8] = { 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E };
    s32 mot8[8] = { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 };
    s32 mot9[8] = { 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A };
    s32 mot10[8] = { 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15 };
    s32 mot11[8] = { 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23 };
    MgWork* work;
    s32 chr;
    u32 dir;
    s32 file;

    D_800EC598_minigame[D_800EC280_minigame++] = obj;
    dir = D_800A178C_main[GwPlayer[player].chr][0];
    file = D_800A178C_main[GwPlayer[player].chr][1];
    func_800E1BA8_minigame(obj, dir, file, player, 0x20AB9, 0x20A99);
    work = obj->data;
    chr = GwPlayer[player].chr;
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, mot0[chr]), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, mot1[chr]), 1, 0x13);
    func_800E5A00_minigame(obj, 0x15, func_80017BB8_main(chr, mot2[chr]), 0, 0);
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, mot3[chr]), 1, 0x78);
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, mot4[chr]), 1, 0x78);
    func_800E5A00_minigame(obj, 0x26, func_80017BB8_main(chr, mot5[chr]), 0, 0);
    func_800E5A00_minigame(obj, 0x27, func_80017BB8_main(chr, mot6[chr]), 0, 0);
    func_800E5A00_minigame(obj, 0x28, func_80017BB8_main(chr, mot7[chr]), 0, 0);
    func_800E5A00_minigame(obj, 0x29, func_80017BB8_main(chr, mot8[chr]), 0, 0);
    func_800E5A00_minigame(obj, 0x2A, func_80017BB8_main(chr, mot9[chr]), 0, 0);
    func_800E5A00_minigame(obj, 0x2B, func_80017BB8_main(chr, mot10[chr]), 1, 0);
    func_800E5A00_minigame(obj, 0x21, func_80017BB8_main(chr, mot11[chr]), 1, 0);
    in.x = D_8010C6A8_mpiq[player];
    in.y = 180.0f;
    func_80012D0C_main(0, CZoom, &in, (Vec2f*)&out);
    omSetTra(obj, out.x, 0.0f, 0.0f);
    obj->trans.x = out.x;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->rot.y = 180.0f;
    func_800E149C_minigame(obj, 0, 1);
    func_800E149C_minigame(obj, 1, 2);
    func_800E149C_minigame(obj, 2, 2);
    func_800E149C_minigame(obj, 3, 2);
    func_800E149C_minigame(obj, 4, 2);
    func_800E5690_minigame(obj, 0);
    D_8010C9C8_mpiq[player] = 0;
    D_8010C9E8_mpiq[player] = 0;
    work->unk104[2] = (void*)func_80106658_mpiq;
    obj->func = func_8010651C_mpiq;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80105E14_mpiq);
#endif

void func_8010651C_mpiq(omObjData* obj) {
    MgWork* work;
    f32 x;
    f32 z;

    work = obj->data;
    x = obj->trans.x;
    z = obj->trans.z;
    D_800CBB6E_main[work->unk57] = 0;
    D_800D20A1_main[work->unk57] = 0;
    if (D_8010C9E8_mpiq[work->unk59] & 1) {
        D_800CDA7C_main[work->unk57] = 0;
        D_800D5558_main[work->unk57] = 0;
    }
    if (D_8010C9C2_mpiq == 1 && !(GwPlayer[work->unk59].stat & 1)) {
        D_800CDA7C_main[work->unk57] &= 0x7FFF;
        D_800D5558_main[work->unk57] &= 0x7FFF;
    }
    func_800DDD94_minigame(obj);
    work->unk60 = 0;
    obj->trans.x = x;
    obj->trans.z = z;
}

s16 func_80106658_mpiq(void) {
    return D_8010C9C2_mpiq;
}

#ifdef NON_MATCHING
/* CPU plan for a question: buzz delay, answer time, and a right or wrong answer by difficulty. */
void func_80106664_mpiq(s32 player) {
    s16 buttons[3] = { 0x8000, 0x4000, 0x2000 };
    s32 range;
    void* win;
    s32 base;
    s32 offset;
    s32 mod;
    s32 add;
    s32 skill;
    s32 ans;

    skill = 0;
    win = func_800364DC_main(D_8010CA50_mpiq[D_8010CA4C_mpiq]);
    base = func_8005B5EC_main(win) * 5 - 0x28;
    add = 0;
    mod = 0;
    offset = 0;
    D_8010CA08_mpiq[player].unk08 = 0;
    range = 0;
    switch (GwPlayer[player].cpu_difficulty) {
    case 0:
        range = 0x3C;
        offset = 0x5A;
        mod = 2;
        add = 8;
        skill = 1;
        break;
    case 1:
        range = 0x4B;
        offset = 0x3C;
        mod = 6;
        add = 4;
        skill = 3;
        break;
    case 2:
        range = 0x5A;
        offset = 0x1E;
        mod = 8;
        add = 2;
        skill = 5;
        break;
    case 3:
        range = 0x69;
        offset = 0;
        mod = 9;
        add = 1;
        skill = 8;
        break;
    }
    D_8010CA08_mpiq[player].unk00 = base + offset + (rand8() % (range + 1) - (range >> 1));
    if (D_8010CA08_mpiq[player].unk00 < 0x1F) {
        D_8010CA08_mpiq[player].unk00 = 0x1E;
    }
    D_8010CA08_mpiq[player].unk04 = (rand8() % mod + add) * 10;
    if ((u8)(rand8() % 10) == 0 ? skill >= 2 : skill > 0) {
        D_8010CA08_mpiq[player].unk08 = buttons[D_8010CA38_mpiq[D_8010CA4C_mpiq]];
    } else {
        ans = (u8)(rand8() % 3);
        if (ans == D_8010CA38_mpiq[D_8010CA4C_mpiq]) {
            ans = (ans + 1) % 3;
        }
        D_8010CA08_mpiq[player].unk08 = buttons[ans];
    }
    func_800365E8_main(win);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80106664_mpiq);
#endif

/* CPU input: buzz in when its delay runs out, then press its answer. */
void func_801069F8_mpiq(s32 player) {
    MgWork* work;

    work = D_800EC598_minigame[player]->data;
    if (!(D_8010C9E8_mpiq[player] & 1)) {
        if (D_8010C9C2_mpiq == 0 && D_8010CA08_mpiq[player].unk00 != 0) {
            D_8010CA08_mpiq[player].unk00--;
            if (D_8010CA08_mpiq[player].unk00 == 0) {
                D_800CDA7C_main[work->unk57] |= 0x8000;
                D_800D5558_main[work->unk57] |= 0x8000;
            }
        } else if (player == D_8010C9BC_mpiq && D_8010CA08_mpiq[player].unk04 != 0) {
            D_8010CA08_mpiq[player].unk04--;
            if (D_8010CA08_mpiq[player].unk04 == 0) {
                D_800CDA7C_main[work->unk57] |= D_8010CA08_mpiq[player].unk08;
                D_800D5558_main[work->unk57] |= D_8010CA08_mpiq[player].unk08;
            }
        }
    }
}

/* The stage: background and podium sprites. */
void func_80106B5C_mpiq(void) {
    omObjData* obj;
    MqStage* stage;
    u16 spr;

    obj = omAddObj(5, 2, 0, -1, NULL);
    obj->data = stage = HuMemAllocTag(sizeof(MqStage), 0x7918);
    obj->model[0] = 0;
    D_8010C9B0_mpiq = 1.0f;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
    memset(obj->data, 0, sizeof(MqStage));
    stage->unk03 = 1;
    stage->unk08 = 0.5f;
    stage->unk04 = 0;
    spr = InitEspriteSlot(func_8000B838_main(0x420000), 0, 1);
    func_8000BC48_main(spr, 0x4008);
    func_8000BBD4_main(spr, 0xA0, 0x78);
    func_8000BB54_main(spr);
    func_8000BE5C_main(spr, 1.0f, 1.0f);
    func_8000BCC8_main(spr, 0xFF);
    D_8010C9DC_mpiq[0] = InitEspriteSlot(func_8000B838_main(0x42000C), 0, 1);
    func_8000BC48_main(D_8010C9DC_mpiq[0], 0x4008);
    func_8000BBD4_main(D_8010C9DC_mpiq[0], 0x9E, 0x56);
    func_8000BB94_main(D_8010C9DC_mpiq[0]);
    func_8000BE5C_main(D_8010C9DC_mpiq[0], 1.0f, 1.0f);
    func_8000BCC8_main(D_8010C9DC_mpiq[0], 3);
    D_8010C9DC_mpiq[1] = InitEspriteSlot(func_8000B838_main(0x42000D), 0, 1);
    func_8000BC48_main(D_8010C9DC_mpiq[1], 0x4008);
    func_8000BBD4_main(D_8010C9DC_mpiq[1], 0x9E, 0x56);
    func_8000BB94_main(D_8010C9DC_mpiq[1]);
    func_8000BE5C_main(D_8010C9DC_mpiq[1], 1.0f, 1.0f);
    func_8000BCC8_main(D_8010C9DC_mpiq[1], 3);
    D_8010C9E0_mpiq = InitEspriteSlot(func_8000B838_main(0x420001), 0, 1);
    func_8000BC48_main(D_8010C9E0_mpiq, 0x4008);
    func_8000BBD4_main(D_8010C9E0_mpiq, 0xA0, -0x5A);
    func_8000BB54_main(D_8010C9E0_mpiq);
    func_8000BE5C_main(D_8010C9E0_mpiq, 1.0f, 1.0f);
    func_8000BCC8_main(D_8010C9E0_mpiq, 0xFE);
    D_8010C9E2_mpiq = InitEspriteSlot(func_8000B838_main(0x420002), 0, 1);
    func_8000BC48_main(D_8010C9E2_mpiq, 0x4008);
    func_8000BBD4_main(D_8010C9E2_mpiq, 0xA0, -0x5A);
    func_8000BB54_main(D_8010C9E2_mpiq);
    func_8000BE5C_main(D_8010C9E2_mpiq, 1.0f, 1.0f);
    func_8000BBFC_main(D_8010C9E2_mpiq, 0xE6);
    func_8000BCC8_main(D_8010C9E2_mpiq, 0xFF);
    func_80107114_mpiq();
    obj->func = NULL;
}

/* Title drop-in: the sign slides down with a bounce. */
void func_80106E98_mpiq(void) {
    Vec2f in;
    Vec out; /* only x, y written */
    s32 i;
    s32 dy;

    HuPrcSleep(0xF);
    HuAudFXPlay(0x413);
    for (i = 0; i < 0x1E; i++) {
        in.x = 260.0f;
        in.y = ((f32)i - 30.0f) * 4.0f;
        func_80012D0C_main(0, CZoom, &in, (Vec2f*)&out);
        D_8010CA78_mpiq->trans.y = out.y;
        dy = (0x1E - i) * 6;
        func_8000BBD4_main(D_8010C9E0_mpiq, 0xA0, 0x5A - dy);
        func_8000BBD4_main(D_8010C9E2_mpiq, 0x9E, 0x52 - dy);
        HuPrcVSleep();
    }
    func_8000BBD4_main(D_8010C9E0_mpiq, 0xA0, 0x54);
    func_8000BBD4_main(D_8010C9E2_mpiq, 0x9E, 0x4E);
    HuPrcVSleep();
    func_8000BBD4_main(D_8010C9E0_mpiq, 0xA0, 0x5E);
    func_8000BBD4_main(D_8010C9E2_mpiq, 0x9E, 0x58);
    HuPrcVSleep();
    func_8000BBD4_main(D_8010C9E0_mpiq, 0xA0, 0x58);
    func_8000BBD4_main(D_8010C9E2_mpiq, 0x9E, 0x52);
    HuPrcVSleep();
    func_8000BBD4_main(D_8010C9E0_mpiq, 0xA0, 0x5C);
    func_8000BBD4_main(D_8010C9E2_mpiq, 0x9E, 0x56);
    HuPrcVSleep();
    func_8000BBD4_main(D_8010C9E0_mpiq, 0xA0, 0x59);
    func_8000BBD4_main(D_8010C9E2_mpiq, 0x9E, 0x53);
    HuPrcVSleep();
    func_8000BBD4_main(D_8010C9E0_mpiq, 0xA0, 0x5B);
    func_8000BBD4_main(D_8010C9E2_mpiq, 0x9E, 0x55);
    HuPrcVSleep();
    func_8000BBD4_main(D_8010C9E0_mpiq, 0xA0, 0x5A);
    func_8000BBD4_main(D_8010C9E2_mpiq, 0x9E, 0x54);
    omDelPrcObj(NULL);
}

void func_80107114_mpiq(void) {
    omObjData* obj;
    f32* angle;

    obj = omAddObj(5, 0, 0, -1, func_80107168_mpiq);
    obj->data = angle = HuMemAllocTag(sizeof(f32), 0x7918);
    *angle = 0;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C718_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C738_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C758_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C778_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C798_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C7B8_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C7D8_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C7F8_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C818_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C838_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C858_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C878_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C898_mpiq);

#ifdef NON_MATCHING
/* Title sign pulse. */
void func_80107168_mpiq(omObjData* obj) {
    f32* angle;
    f32 scale;

    angle = obj->data;
    scale = sindf(*angle) * 0.02f + 1.02;
    func_8000BE5C_main(D_8010C9E0_mpiq, scale, scale);
    *angle += 5.0f;
    if (*angle >= 360.0f) {
        *angle -= 360.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107168_mpiq);
#endif

/* The four podiums. */
void func_8010720C_mpiq(void) {
    Vec2f in;
    Vec out; /* only x, y written */
    f32 heights[3] = { 47.0f, 94.0f, 141.0f };
    omObjData* obj;
    MqStage* stage;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(2, 2, 0, -1, func_8010747C_mpiq);
        obj->data = HuMemAllocTag(sizeof(MqStage), 0x7918);
        D_8010CA80_mpiq[i] = obj;
        stage = obj->data;
        stage->unkB0 = HuMemAllocTag(0x14, 0x7918);
        if (i == 0) {
            obj->model[0] = func_8000B0A0_main(0x42000E, 0x29D);
        } else {
            obj->model[0] = Hu3DModelLink(D_8010CA80_mpiq[0]->model[0]);
        }
        D_8010C9B0_mpiq = 1.0f;
        in.x = D_8010C6A8_mpiq[i];
        in.y = 180.0f;
        func_80012D0C_main(0, CZoom, &in, (Vec2f*)&out);
        omSetTra(obj, out.x, 0.0f, 0.0f);
        D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
        memset(obj->data, 0, sizeof(MqStage));
        stage->unk03 = 1;
        stage->unk08 = 0.5f;
        stage->unk04 = i + 1;
        func_800E13CC_minigame(obj, 0.0f, 100.0f, -100.0f, -100.0f, 100.0f, 100.0f);
        D_8010CA90_mpiq[i] = 0;
        D_8010CAA0_mpiq[i] = 0;
    }
    for (j = 0; j < 3; j++) {
        D_8010CAB0_mpiq[j] = heights[j];
    }
    obj->func = func_8010747C_mpiq;
}

/* A podium rising to its level. */
void func_8010747C_mpiq(omObjData* obj) {
    MqLamp* lamp;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (obj == D_8010CA80_mpiq[i]) {
            break;
        }
    }
    if (D_8010CA90_mpiq[i] & 1) {
        obj->trans.y += 4.7f;
        lamp = D_8010CAC0_mpiq[i]->data;
        lamp->unk04 += 4.7f;
        if (obj->trans.y >= D_8010CAB0_mpiq[D_8010CAA0_mpiq[i] - 1]) {
            obj->trans.y = D_8010CAB0_mpiq[D_8010CAA0_mpiq[i] - 1];
            lamp->unk0C = lamp->unk04;
            D_8010CA90_mpiq[i] &= ~1;
        }
    }
}

void func_80107558_mpiq(s32 player, s32 level) {
    D_8010CAA0_mpiq[player] = level;
    D_8010CA90_mpiq[player] |= 1;
}

/* The four buzzer lamps over the podiums. */
void func_80107584_mpiq(void) {
    Vec2f in;
    Vec out; /* only x, y written */
    omObjData* obj;
    MqLamp* lamp;
    s32 i;
    s32 attr;
    s32 attr2;

    attr = 0x699;
    attr2 = 0xA89;
    for (i = 0; i < 4; i++) {
        obj = omAddObj(0xA, 3, 0, -1, func_80107774_mpiq);
        D_8010CAC0_mpiq[i] = obj;
        lamp = obj->data = HuMemAllocTag(sizeof(MqLamp), 0x7918);
        if (i == 0) {
            obj->model[0] = func_8000B0A0_main(0x42000B, attr);
            obj->model[1] = func_8000B0A0_main(0x42000F, attr2 | 4);
            func_8001FA68_main(obj->model[1]);
            obj->model[2] = func_8000B108_main(0x5D0008, attr | 4);
        } else {
            obj->model[0] = Hu3DModelLink(D_8010CAC0_mpiq[0]->model[0]);
            obj->model[1] = Hu3DModelLink(D_8010CAC0_mpiq[0]->model[1]);
            obj->model[2] = Hu3DModelLink(D_8010CAC0_mpiq[0]->model[2]);
        }
        func_8001C814_main(obj->model[0], 1, 1);
        in.x = D_8010C6A8_mpiq[i];
        in.y = 52.0f;
        func_80012D0C_main(0, CZoom, &in, (Vec2f*)&out);
        omSetTra(obj, out.x, out.y, 0.0f);
        lamp->unk00 = out.x;
        lamp->unk04 = out.y;
        lamp->unk0C = out.y;
        lamp->unk10 = 0;
        lamp->unk08 = 0;
        lamp->unk18 = i;
        lamp->unk24 = 0;
        Hu3DModelPosSet(obj->model[1], lamp->unk00, lamp->unk04, 0.0f);
    }
}

/* A buzzer lamp: drops onto its podium when buzzed, flashes, and is pressed by the answering player. */
void func_80107774_mpiq(omObjData* obj) {
    f32 bounce[12] = { 0.0f, 10.0f, 25.0f, 40.0f, 52.0f, 50.0f, 50.0f, 48.0f, 38.0f, 29.0f, 25.0f, 160.0f };
    MqLamp* lamp;
    s32 i;

    lamp = obj->data;
    obj->trans.y = lamp->unk04;
    if (lamp->unk10 & 1) {
        lamp->unk04 -= lamp->unk08;
        lamp->unk08 += 8.0f;
        if (lamp->unk04 <= D_8010CA80_mpiq[lamp->unk18]->trans.y + 30.0f) {
            lamp->unk04 = D_8010CA80_mpiq[lamp->unk18]->trans.y + 30.0f;
            lamp->unk10 = (lamp->unk10 & ~1) | 2;
            func_80107E90_mpiq(obj->trans.x, obj->trans.y - 50.0f, obj->trans.z);
        }
    }
    if (lamp->unk10 & 2) {
        lamp->unk04 += 16.0f;
        if (lamp->unk04 >= lamp->unk0C) {
            lamp->unk04 = lamp->unk0C;
            lamp->unk10 &= ~2;
        }
    }
    if (lamp->unk10 & 8) {
        func_8001C814_main(obj->model[0], 4, 4);
        lamp->unk10 &= ~8;
    }
    if (lamp->unk10 & 0x10) {
        if (--lamp->unk14 == 0xC) {
            func_8001C258_main(obj->model[0], 4, 4);
        }
        if (D_800CCF58_main[HmfModelData[obj->model[2]].unk02].unk02 <= HmfModelData[obj->model[2]].unk40) {
            func_8001C258_main(obj->model[2], 4, 4);
            lamp->unk10 &= ~0x10;
        }
    }
    if (lamp->unk10 & 0x20) {
        lamp->unk14--;
        Hu3DModelScaleSet(obj->model[1], lamp->unk1C, lamp->unk1C, lamp->unk1C);
        Hu3DModelPosSet(obj->model[1], lamp->unk00, lamp->unk04 + bounce[7 - lamp->unk14], 0.0f);
        func_8001F9E4_main(obj->model[1], lamp->unk20);
        lamp->unk1C += 0.2f;
        lamp->unk20 -= 0x23;
        if (lamp->unk14 == 0) {
            func_8001C258_main(obj->model[1], 4, 4);
            lamp->unk10 &= ~0x20;
        }
    }
    if (func_801089D0_mpiq(obj, D_800EC598_minigame[D_8010C9BC_mpiq]) != 0) {
        if (lamp->unk10 & 3) {
            if (lamp->unk24 == 0) {
                func_8004AC5C_main(0x411, D_8010C9BE_mpiq);
                lamp->unk24 = 1;
            }
            func_800E561C_minigame(D_800EC598_minigame[D_8010C9BC_mpiq], 1);
            omVibrate(D_8010C9BE_mpiq, 0x14, 0, 0x14);
        } else if (D_8010C9C2_mpiq == 0) {
            func_8001C814_main(obj->model[0], 4, 0);
            func_8001C814_main(obj->model[0], 1, 0);
            func_800E58F8_minigame(D_800EC598_minigame[D_8010C9BC_mpiq], 0x26, 0);
            D_8010C9C2_mpiq = 1;
            for (i = 0; i < 4; i++) {
                func_800E12EC_minigame(D_800EC598_minigame[i], 1000.0f);
            }
            lamp->unk10 |= 0x20;
            lamp->unk14 = 7;
            func_8001C258_main(obj->model[1], 4, 0);
            lamp->unk1C = 1.0f;
            lamp->unk20 = 0xFF;
        }
    } else {
        lamp->unk24 = 0;
    }
}

/* Drop player's lamp. */
void func_80107C18_mpiq(s32 player) {
    MqLamp* lamp = D_8010CAC0_mpiq[player]->data;

    lamp->unk10 |= 1;
    lamp->unk08 = 4.0f;
    lamp->unk18 = player;
}

void func_80107C50_mpiq(s32 player) {
    MqLamp* lamp = D_8010CAC0_mpiq[player]->data;

    lamp->unk10 |= 8;
}

void func_80107C74_mpiq(void) {
    f32 x;
    f32 y;
    f32 z;
    omObjData* obj;
    MqLamp* lamp;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = D_8010CAC0_mpiq[i];
        x = obj->trans.x;
        y = obj->trans.y;
        z = obj->trans.z + 200.0f;
        lamp = obj->data;
        lamp->unk10 |= 0x10;
        lamp->unk14 = 0xF;
        Hu3DModelPosSet(D_8010CAC0_mpiq[i]->model[2], x, y, z);
        Hu3DModelScaleSet(D_8010CAC0_mpiq[i]->model[2], 1.0f, 1.0f, 1.0f);
        func_8001C258_main(D_8010CAC0_mpiq[i]->model[2], 4, 0);
    }
}

void func_80107D70_mpiq(void) {
    omObjData* obj;
    s32* flags;

    obj = omAddObj(0xFF, 1, 0, -1, func_80107DE0_mpiq);
    D_8010CAD0_mpiq = obj;
    obj->data = flags = HuMemAllocTag(sizeof(s32), 0x7918);
    *flags = 0;
    obj->model[0] = func_8000B108_main(8, 0x69D);
}

void func_80107DE0_mpiq(omObjData* obj) {
    s32* flags;

    flags = obj->data;
    if (*flags & 1) {
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
            func_8001C258_main(obj->model[0], 4, 4);
            *flags &= ~1;
        }
    }
}

void func_80107E90_mpiq(f32 x, f32 y, f32 z) {
    ((MqFx*)D_8010CAD0_mpiq->data)->unk00 |= 1;
    func_8001C258_main(D_8010CAD0_mpiq->model[0], 4, 0);
    func_8001C6A8_main(D_8010CAD0_mpiq->model[0], 0.0f);
    omSetTra(D_8010CAD0_mpiq, x, y, z);
}

void func_80107F28_mpiq(void) {
    omObjData* obj;
    MqFx* fx;

    obj = omAddObj(0xFF, 1, 0, -1, func_80107FC4_mpiq);
    D_8010CAD4_mpiq = obj;
    obj->data = fx = HuMemAllocTag(sizeof(MqFx), 0x7918);
    fx->unk00 = 0;
    obj->model[0] = func_8000B108_main(0x230009, 0x69D);
    Hu3DModelScaleSet(obj->model[0], 1.5f, 1.5f, 1.5f);
    fx->unk04 = 0;
}

void func_80107FC4_mpiq(omObjData* obj) {
}

#ifdef NON_MATCHING
/* Show the effect over a player's head (height by character). */
void func_80107FCC_mpiq(s32 player) {
    f32 heights[8] = { 100.0f, 110.0f, 100.0f, 110.0f, 100.0f, 120.0f, 110.0f, 100.0f };
    omObjData* obj;
    MqFx* fx;
    f32 x;
    f32 y;
    f32 z;

    obj = D_800EC598_minigame[player];
    x = obj->trans.x;
    y = obj->trans.y + heights[GwPlayer[player].chr];
    z = obj->trans.z;
    fx = D_8010CAD4_mpiq->data;
    fx->unk00 |= 1;
    if (fx->unk04 == 0) {
        func_8001C258_main(D_8010CAD4_mpiq->model[0], 4, 0);
        func_8001C6A8_main(D_8010CAD4_mpiq->model[0], 0.0f);
        func_8001C814_main(D_8010CAD4_mpiq->model[0], 2, 2);
    }
    omSetTra(D_8010CAD4_mpiq, x, y, z);
    fx->unk04++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107FCC_mpiq);
#endif

void func_8010811C_mpiq(void) {
    MqFx* fx = D_8010CAD4_mpiq->data;

    if (--fx->unk04 == 0) {
        func_8001C258_main(D_8010CAD4_mpiq->model[0], 4, 4);
        fx->unk00 &= ~1;
    }
}

#ifdef NON_MATCHING
/* The four score columns (three blocks each). */
void func_80108178_mpiq(void) {
    Vec2f in;
    Vec out; /* only x, y written */
    omObjData* obj;
    MqColumn* col;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(2, 5, 0, -1, func_80108494_mpiq);
        D_8010CAD8_mpiq[i] = obj;
        col = obj->data = HuMemAllocTag(sizeof(MqColumn), 0x7918);
        omSetSca(obj, 2.0f, 3.0f, 2.0f);
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x42000A, 0x6B9);
            obj->model[1] = func_8000B108_main(0x420007, 0x6BD);
            obj->model[2] = func_8000B108_main(0x420008, 0x6BD);
            obj->model[3] = func_8000B108_main(0x420009, 0x6BD);
            obj->model[4] = func_8000B108_main(0x420006, 0x6B9);
        } else {
            obj->model[0] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[0]);
            obj->model[1] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[1]);
            obj->model[2] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[2]);
            obj->model[3] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[3]);
            obj->model[4] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[4]);
        }
        col->unk38 = 0;
        col->unk3C = 0;
        in.x = D_8010C6A8_mpiq[i];
        in.y = 180.0f;
        func_80012D0C_main(0, CZoom, &in, (Vec2f*)&out);
        omSetTra(obj, out.x, -144.0f, 0.0f);
        omSetSca(obj, 2.0f, 4.0f, 2.0f);
        col->unk08 = out.x;
        col->unk18 = 0.0f;
        Hu3DModelPosSet(obj->model[4], out.x, col->unk18, col->unk18);
        Hu3DModelScaleSet(obj->model[4], 2.0f, 1.0f, 2.0f);
        for (j = 0; j < 3; j++) {
            Hu3DModelScaleSet(obj->model[j + 1], 2.0f, 2.0f, 2.0f);
            col->unk1C[j] = j * 50.0f - 44.0f;
            Hu3DModelPosSet(obj->model[j + 1], out.x, col->unk1C[j], 0.0f);
            col->unk28[j] = 0.0f;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108178_mpiq);
#endif

/* A score column: grows the next block while its podium rises. */
void func_80108494_mpiq(omObjData* obj) {
    MqColumn* col;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (obj == D_8010CAD8_mpiq[i]) {
            break;
        }
    }
    col = obj->data;
    for (i = 0; i < 3; i++) {
        HmfModelData[obj->model[i + 1]].scale.y = col->unk28[i];
    }
    if (col->unk3C & 1) {
        col->unk28[col->unk38] += 0.2f;
        HmfModelData[obj->model[4]].pos.y = D_8010CA80_mpiq[D_8010C9BC_mpiq]->trans.y;
        if (col->unk28[col->unk38] >= 2.0f) {
            col->unk28[col->unk38] = 2.0f;
        }
        if (!(D_8010CA90_mpiq[col->unk40] & 1)) {
            col->unk38++;
            col->unk3C &= ~1;
        }
    }
}

/* Start growing player's next block. */
void func_801085F4_mpiq(s32 player) {
    MqColumn* col = D_8010CAD8_mpiq[player]->data;

    col->unk3C |= 1;
    col->unk40 = player;
    func_8001C258_main(D_8010CAD8_mpiq[player]->model[col->unk38 + 1], 4, 0);
    func_8004AC5C_main(0x410, player);
    omVibrate(player, 0xA, 0, 0xA);
}

void func_80108688_mpiq(void) {
    Vec out; /* only x, y written */
    Vec2f in;
    omObjData* obj;
    MqHost* host;

    obj = omAddObj(0xA, 1, 1, -1, func_801087F8_mpiq);
    obj->data = HuMemAllocTag(sizeof(MqHost), 0x7918);
    D_8010CA78_mpiq = obj;
    host = obj->data;
    obj->model[0] = func_8000B108_main(0xA005D, 0x6D9);
    func_8001C814_main(obj->model[0], 2, 2);
    in.x = 260.0f;
    in.y = -120.0f;
    func_80012D0C_main(0, CZoom, &in, (Vec2f*)&out);
    omSetTra(obj, out.x, out.y, 200.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.1f, 1.1f, 1.1f);
    func_8000B460_main(obj, 0, 0xA005F);
    func_8000B460_main(obj, 1, 0xA0060);
    func_8000B460_main(obj, 2, 0xA0061);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    host->unk08 = 0;
}

void func_801087F8_mpiq(omObjData* obj) {
    MqHost* host;

    host = obj->data;
    omSetRot(obj, 0.0f, host->unk08, 0.0f);
    if (host->unk0C & 1) {
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 0xA, 0);
            func_8001C814_main(obj->model[0], 2, 2);
            host->unk0C &= ~1;
        }
    }
    if (host->unk0C & 4) {
        host->unk08 -= 12.0f;
        if (host->unk08 <= -120.0f) {
            host->unk08 = -120.0f;
            host->unk0C &= ~4;
        }
    }
    if (host->unk0C & 2) {
        host->unk08 += 12.0f;
        if (host->unk08 >= 0.0f) {
            host->unk08 = 0.0f;
            host->unk0C &= ~2;
        }
    }
}

void func_801089A4_mpiq(s32 turn) {
    MqHost* host = D_8010CA78_mpiq->data;
    s32 flags;

    flags = host->unk0C & ~2;
    flags &= ~4;
    host->unk0C = turn | flags;
}

#ifdef NON_MATCHING
/* 1 if a and b are within 150 units (x, y). */
s16 func_801089D0_mpiq(omObjData* a, omObjData* b) {
    f32 ax;
    f32 ay;
    f32 dx;
    f32 dy;
    s32 near;

    near = 0;
    ax = a->trans.x;
    ay = a->trans.y;
    dx = b->trans.x - ax;
    dy = b->trans.y - ay;
    if (HuSqrtf(dx * dx + dy * dy) < 150.0f) {
        near = 1;
    }
    return near;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801089D0_mpiq);
#endif

void func_80108A3C_mpiq(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z) {
    func_8000B5F0_main(1);
    D_8010C9B4_mpiq = func_8000B638_main();
    ScissorSet(D_8010C9B4_mpiq, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(D_8010C9B4_mpiq, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = x;
    Center.y = y;
    Center.z = z;
    Hu3DCamSetPerspective(D_8010C9B4_mpiq, 30.0f, 80.0f, 8000.0f);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C8E4_mpiq);

void func_80108B74_mpiq(void) {
    s32 files[3] = { 3, 4, 5 };
    omObjData* obj;
    MqButtons* btn;
    s32 i;

    obj = omAddObj(0xA, 0, 0, -1, func_80108E20_mpiq);
    obj->data = btn = HuMemAllocTag(sizeof(MqButtons), 0x7918);
    D_8010CAE8_mpiq = obj;
    btn->unk08 = 0;
    btn->unk0C = 0;
    btn->unk00 = 0;
    btn->unk04 = 0;
    for (i = 0; i < 3; i++) {
        D_8010CAF2_mpiq[i] = func_8000B838_main(files[i] | 0x420000);
        D_8010CAEC_mpiq[i] = InitEspriteSlot(D_8010CAF2_mpiq[i], 0, 1);
        func_8000BC48_main(D_8010CAEC_mpiq[i], 8);
        func_8000BBD4_main(D_8010CAEC_mpiq[i], 0xA0, 0x78);
        func_8000BB54_main(D_8010CAEC_mpiq[i]);
        func_8000BE5C_main(D_8010CAEC_mpiq[i], 1.0f, 1.0f);
        func_8000BCC8_main(D_8010CAEC_mpiq[i], 0xFF);
    }
    omAddPrcObj(func_80109018_mpiq, 0x4800, 0, 0);
    omAddPrcObj(func_80108D10_mpiq, 0x5100, 0, 0);
}

/* Input process: mask the answer buttons of humans, drive the CPUs. */
void func_80108D10_mpiq(void) {
    s32 i;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].stat & 1) {
                D_800CDA7C_main[GwPlayer[i].pad] &= 0x1FFF;
                D_800D5558_main[GwPlayer[i].pad] &= 0x1FFF;
            }
            if (func_800E6E8C_minigame() == 2 && (GwPlayer[i].stat & 1)) {
                func_801069F8_mpiq(i);
            }
        }
        HuPrcVSleep();
    }
}

void func_80108E20_mpiq(omObjData* obj) {
    MqButtons* btn;
    s32 i;

    btn = obj->data;
    if (btn->unk08 & 4) {
        func_8000BB54_main(D_8010CAEC_mpiq[0]);
    } else {
        func_8000BB94_main(D_8010CAEC_mpiq[0]);
    }
    if (btn->unk08 & 8) {
        func_8000BB54_main(D_8010CAEC_mpiq[1]);
    } else {
        func_8000BB94_main(D_8010CAEC_mpiq[1]);
    }
    if (btn->unk08 & 0x10) {
        func_8000BB54_main(D_8010CAEC_mpiq[2]);
    } else {
        func_8000BB94_main(D_8010CAEC_mpiq[2]);
    }
    for (i = 0; i < 3; i++) {
        func_8000BBD4_main(D_8010CAEC_mpiq[i], btn->unk00, btn->unk04);
        func_8000BE5C_main(D_8010CAEC_mpiq[i], btn->unk0C, btn->unk0C);
    }
    if (btn->unk08 & 1) {
        btn->unk0C += 0.2f;
        if (btn->unk0C >= 1.0f) {
            btn->unk0C = 1.0f;
            btn->unk08 &= ~1;
        }
    }
    if (btn->unk08 & 2) {
        btn->unk0C -= 0.2f;
        if (btn->unk0C <= 0.2f) {
            btn->unk0C = 0.2f;
            btn->unk08 &= ~0x1E;
            D_8010C9C0_mpiq &= ~0x20;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80109018_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80109414_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801096C0_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010A010_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010A184_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010AB44_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010AEDC_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010AFAC_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010B0CC_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010B900_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010BA64_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010BB74_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C964_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010BD1C_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010C2F0_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010C4C0_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010C504_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010C558_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010C5B8_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010C624_mpiq);
