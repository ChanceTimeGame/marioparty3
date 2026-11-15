#include "common.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/process.h"
#include "game/util.h"
#include "game/data.h"
#include "variables.h"
#include "math.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/105D50.h"
#include "game/esprite.h"

typedef struct RbHooked {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} RbHooked; // sizeof 0x08 on N64

extern s16 D_80108F30_mgresultbattle[4];    /* coin icon sprite per figure */
extern s16 D_80108F38_mgresultbattle[4][3]; /* coin digit sprites per figure */
extern RbHooked D_80108F50_mgresultbattle[4];
extern RbHooked D_80108F7C_mgresultbattle;
extern RbHooked D_80108F84_mgresultbattle;
extern s8 D_80108F8C_mgresultbattle[4];

extern const Vec D_801089D0_mgresultbattle[4];
extern const s32 D_80108A00_mgresultbattle[4];
extern const f32 D_80108A10_mgresultbattle[4];

void func_80016B00_main(s16 model, s16 frame, char *name, f32 (*mtx)[4][4]);
void func_8000BD50_main(u16 spriteId, s16 frame);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_80106918_mgresultbattle(void);
void func_80107F94_mgresultbattle(void);
void func_80107F9C_mgresultbattle(omObjData *);
void func_8010829C_mgresultbattle(omObjData *);
void func_801082A4_mgresultbattle(void);
void func_801082C0_mgresultbattle(omObjData *);
void func_80108510_mgresultbattle(s16 idx, s16 x, s16 y);

// Creates the four placing plates (model by placing) in front of the figures; the hook keeps the
// figures on the plates' "chara" joints.
void func_80107D10_mgresultbattle(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x14, 8, 8, -1, NULL);
    D_80108F7C_mgresultbattle.obj = obj;
    obj->model[0] = func_8000B108_main(0x1B0005, 0x2B9);
    for (i = 0; i < 4; i++) {
        obj->model[i + 1] =
            func_8000B108_main(D_80108A00_mgresultbattle[GwPlayer[D_80108F8C_mgresultbattle[i]].bonusCoin], 0x16B9);
        func_8001C814_main(obj->model[i + 1], 2, 0);
        func_8001C814_main(obj->model[i + 1], 1, 1);
        func_8001C258_main(obj->model[i + 1], 4, 4);
        Hu3DModelPosSet(obj->model[i + 1], D_801089D0_mgresultbattle[i].x, D_801089D0_mgresultbattle[i].y,
                        D_801089D0_mgresultbattle[i].z);
        Hu3DModelRotSet(obj->model[i + 1], 0.0f, D_80108A10_mgresultbattle[i], 0.0f);
        func_8001C258_main(obj->model[i + 1], 4, 0);
        func_8001C6A8_main(obj->model[i + 1], D_800CCF58_main[HmfModelData[obj->model[i + 1]].unk02].unk02);
        func_8001C814_main(obj->model[i + 1], 1, 1);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = -5.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_80107F94_mgresultbattle);
    D_80108F7C_mgresultbattle.func = func_80107F9C_mgresultbattle;
    HuPrcSleep(2);
    while (1) {
        D_80108F7C_mgresultbattle.func(obj);
        HuPrcVSleep();
    }
}

void func_80107F94_mgresultbattle(void) {
}

/* Figure positions, left to right (shared with 4F3780 and 4F4980). */
const Vec D_801089D0_mgresultbattle[4] = {
    { -450.0f, 0.0f, 0.0f },
    { -150.0f, 0.0f, 0.0f },
    { 150.0f, 0.0f, 0.0f },
    { 450.0f, 0.0f, 0.0f },
};

/* Plate model per placing. */
const s32 D_80108A00_mgresultbattle[4] = { 0x1B0001, 0x1B0002, 0x1B0003, 0x1B0004 };

/* Plate y rotation per figure. */
const f32 D_80108A10_mgresultbattle[4] = { 10.0f, 2.0f, -2.0f, -10.0f };

void func_80107F9C_mgresultbattle(omObjData *obj) {
    f32 mtx[4][4];
    s32 i;

    for (i = 0; i < 4; i++) {
        func_80016B00_main(obj->model[i + 1], HmfModelData[obj->model[i + 1]].unk40, "chara", &mtx);
        Hu3DModelPosSet(D_80108F50_mgresultbattle[i].obj->model[1], mtx[3][0] + D_801089D0_mgresultbattle[i].x,
                        mtx[3][1] + D_801089D0_mgresultbattle[i].y, mtx[3][2] + D_801089D0_mgresultbattle[i].z);
    }
}

// Plays the plates' rise motion from its start.
void func_801080A0_mgresultbattle(void) {
    omObjData *obj = D_80108F7C_mgresultbattle.obj;
    s32 i;

    for (i = 0; i < 4; i++) {
        func_8001C258_main(obj->model[i + 1], 4, 0);
        func_8001C814_main(obj->model[i + 1], 1, 0);
        func_8001C6A8_main(obj->model[i + 1], 0.0f);
    }
}

#ifdef NON_MATCHING
// battleres A: masked 0, raw 13 (s0/s1 swapped between i and the icon sprite file).
// Creates the coin icon and three digit sprites per figure and runs the sprite hook.
void func_80108130_mgresultbattle(void) {
    omObjData *obj;
    s32 i;
    s32 j;
    s16 icon;
    s16 digit;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_80108F84_mgresultbattle.obj = obj;
    icon = func_8000B838_main(0x1B0006);
    for (i = 0; i < 4; i++) {
        D_80108F30_mgresultbattle[i] = InitEspriteSlot(icon, 0, 0);
        func_8000BB94_main(D_80108F30_mgresultbattle[i]);
    }
    digit = func_8000B838_main(0x1B0007);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_80108F38_mgresultbattle[i][j] = InitEspriteSlot(digit, 0, 0);
            func_8000BB94_main(D_80108F38_mgresultbattle[i][j]);
        }
    }
    omPrcSetDestructor(0, func_801082A4_mgresultbattle);
    D_80108F84_mgresultbattle.func = func_8010829C_mgresultbattle;
    while (1) {
        D_80108F84_mgresultbattle.func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_80108130_mgresultbattle);
#endif

void func_8010829C_mgresultbattle(omObjData *obj) {
}

void func_801082A4_mgresultbattle(void) {
}

void func_801082AC_mgresultbattle(void) {
    D_80108F84_mgresultbattle.func = func_801082C0_mgresultbattle;
}

// Sprite hook: puts each coin icon over its figure's head, then shows the coin counts and plays the
// win/lose motions.
void func_801082C0_mgresultbattle(omObjData *obj) {
    Vec pos;
    Vec2f screen;
    Vec2f at[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        pos.x = HmfModelData[D_80108F50_mgresultbattle[i].obj->model[1]].pos.x;
        pos.y = HmfModelData[D_80108F50_mgresultbattle[i].obj->model[1]].pos.y;
        pos.z = HmfModelData[D_80108F50_mgresultbattle[i].obj->model[1]].pos.z;
        Hu3DCam3DToScreen(0, &pos, &screen);
        func_8000BBD4_main(D_80108F30_mgresultbattle[i], screen.x, (s32)screen.y - 0x30);
        func_8000BB54_main(D_80108F30_mgresultbattle[i]);
        func_8000BE5C_main(D_80108F30_mgresultbattle[i], 0.0f, 0.0f);
        at[i] = screen;
    }
    for (i = 0; i < 20; i++) {
        sindf(i * 4.5f);
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        func_8000BE5C_main(D_80108F30_mgresultbattle[i], 1.0f, 1.0f);
        func_80108510_mgresultbattle(i, at[i].x, (s32)at[i].y - 0x30);
    }
    func_80106918_mgresultbattle();
    HuPrcSleep(50);
    D_80108F84_mgresultbattle.func = func_8010829C_mgresultbattle;
}

// Shows a figure's coin count (two digits under 10, three otherwise; digit 11 is the blank/icon cell).
void func_80108510_mgresultbattle(s16 idx, s16 x, s16 y) {
    s32 coin = (s16)GwPlayer[D_80108F8C_mgresultbattle[idx]].gameCoin;

    if (coin < 10) {
        func_8000BB54_main(D_80108F38_mgresultbattle[idx][0]);
        func_8000BB54_main(D_80108F38_mgresultbattle[idx][1]);
        func_8000BBD4_main(D_80108F38_mgresultbattle[idx][0], x - 6, y - 0x12);
        func_8000BBD4_main(D_80108F38_mgresultbattle[idx][1], x + 4, y - 0x12);
        func_8000BD50_main(D_80108F38_mgresultbattle[idx][0], 11);
        func_8000BD50_main(D_80108F38_mgresultbattle[idx][1], coin % 10);
    } else {
        func_8000BB54_main(D_80108F38_mgresultbattle[idx][0]);
        func_8000BB54_main(D_80108F38_mgresultbattle[idx][1]);
        func_8000BB54_main(D_80108F38_mgresultbattle[idx][2]);
        func_8000BBD4_main(D_80108F38_mgresultbattle[idx][0], x - 11, y - 0x12);
        func_8000BBD4_main(D_80108F38_mgresultbattle[idx][1], x - 1, y - 0x12);
        func_8000BBD4_main(D_80108F38_mgresultbattle[idx][2], x + 9, y - 0x12);
        if (coin < 100) {
            func_8000BD50_main(D_80108F38_mgresultbattle[idx][0], 11);
        } else {
            func_8000BD50_main(D_80108F38_mgresultbattle[idx][0], (coin / 100) % 10);
        }
        func_8000BD50_main(D_80108F38_mgresultbattle[idx][1], (coin / 10) % 10);
        func_8000BD50_main(D_80108F38_mgresultbattle[idx][2], coin % 10);
    }
}

void func_80108858_mgresultbattle(s16 idx) {
    func_8000BB94_main(D_80108F30_mgresultbattle[idx]);
    func_8000BB94_main(D_80108F38_mgresultbattle[idx][0]);
    func_8000BB94_main(D_80108F38_mgresultbattle[idx][1]);
    func_8000BB94_main(D_80108F38_mgresultbattle[idx][2]);
}
