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
    /* 0x0C */ char unk0C[0xA8];
} MqStage; // Size 0xB4

void func_80107114_mpiq(void);
extern f32 D_8010C9B0_mpiq;
extern s32 D_8010C9BC_mpiq; /* player answering */
extern s16 D_8010C9DC_mpiq[2];
extern s16 D_8010C9E0_mpiq;
extern s16 D_8010C9E2_mpiq;
extern omObjData* D_8010CA78_mpiq;
void func_80107168_mpiq(omObjData* obj);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010720C_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010747C_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107558_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107584_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107774_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107C18_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107C50_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107C74_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107D70_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107DE0_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107E90_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107F28_mpiq);

void func_80107FC4_mpiq(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107FCC_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010811C_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108178_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108494_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801085F4_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108688_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801087F8_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801089A4_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801089D0_mpiq);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108B74_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108D10_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108E20_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80109018_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80109414_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C8A8_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C8B4_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C8E4_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C904_mpiq);

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
