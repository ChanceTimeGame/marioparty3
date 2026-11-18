#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// winners_wheel: Winner's Wheel (1 player: stop the wheel to win its prize)

/* omObjData::data of the wheel host (D_8010A498) */
typedef struct WwHost {
    /* 0x00 */ s32 unk00; /* flags */
    /* 0x04 */ s32 unk04;
} WwHost; /* size 8 */

/* omObjData::data of the wheel (D_8010A49C) */
typedef struct WwWheel {
    /* 0x00 */ s32 unk00; /* flags: 1 spinning, 2 speeding up, 4 slowing down */
    /* 0x04 */ f32 unk04; /* spin speed */
    /* 0x08 */ f32 unk08; /* scale */
    /* 0x0C */ f32 unk0C; /* x rotation */
    /* 0x10 */ f32 unk10; /* spin angle */
} WwWheel; /* size 0x14 */

/* omObjData::data of the player (D_8010A4B4) */
typedef struct WwPlayer {
    /* 0x00 */ s32 unk00; /* flags */
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C; /* scale */
    /* 0x10 */ f32 unk10; /* x */
    /* 0x14 */ f32 unk14; /* y */
    /* 0x18 */ f32 unk18; /* z */
} WwPlayer; /* size 0x1C */

/* omObjData::data of the prizes on the wheel (D_8010A4A0) */
typedef struct WwPrize {
    /* 0x00 */ f32 unk00[6]; /* x */
    /* 0x18 */ f32 unk18[6]; /* y */
    /* 0x30 */ f32 unk30[6]; /* z */
    /* 0x48 */ f32 unk48[6]; /* x rotation */
    /* 0x60 */ f32 unk60[6]; /* angle on the wheel */
    /* 0x78 */ f32 unk78[6]; /* scale */
    /* 0x90 */ f32 unk90;    /* y squash */
    /* 0x94 */ f32 unk94;    /* z squash */
} WwPrize; /* size 0x98 */

/* An entry of D_800CBB60_main (minigame BD210.c's MgSprModel) */
typedef struct WwSprModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x22];
} WwSprModel; /* size 0x24 */

/* omObjData::data of the two hosts (D_8010A4B8) */
typedef struct WwHostPair {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04; /* index */
} WwHostPair; /* size 8 */

/* omObjData::data of the 18 pegs round the wheel (D_8010A4C0) */
typedef struct WwPegs {
    /* 0x00 */ s32 unk00;     /* flags: 1 turning, 2 speeding up, 4 slowing down, 8 settle the slot */
    /* 0x04 */ f32 unk04[18]; /* angle, snapped to 20; [0] the ring's, [1] doubles as its previous value */
    /* 0x4C */ f32 unk4C[18]; /* angle; [0] the ring's continuous one */
    /* 0x94 */ f32 unk94;     /* speed */
    /* 0x98 */ f32 unk98;     /* angle that counts a click */
    /* 0x9C */ s32 unk9C;     /* clicks left */
    /* 0xA0 */ s32 unkA0;     /* 2: the empty slot was picked */
} WwPegs; /* size 0xA4 */

/* omObjData::data of the wheel's six rim lights (D_8010A4A4) */
typedef struct WwRim {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ f32 unk04[6];
    /* 0x1C */ f32 unk1C[6];
    /* 0x34 */ f32 unk34[6];
    /* 0x4C */ f32 unk4C[6]; /* angle */
} WwRim; /* size 0x64 */

/* omObjData::data of the won prize shown over the wheel (D_8010A4A8) */
typedef struct WwShow {
    /* 0x00 */ s32 unk00; /* flags: 1 bobbing, 2 sparkles */
    /* 0x04 */ f32 unk04; /* x */
    /* 0x08 */ f32 unk08; /* y */
    /* 0x0C */ f32 unk0C; /* z */
    /* 0x10 */ f32 unk10; /* bob angle */
    /* 0x14 */ f32 unk14; /* x rotation */
} WwShow; /* size 0x18 */

// main
void GMesPosSet(s16 mesId, f32 x, f32 y);
void func_8001473C_main(s16 index, u16 arg1); /* src/14EA0.c: (s16, s16) */
omObjData* func_80045ED0_main(u32 arg0);
extern WwSprModel* D_800CBB60_main;
extern u16 D_800A11D0_main[6];
extern u16 D_800A11DC_main[5]; /* CPU target odds, percent */
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z);
void func_80021BE0_main(s32* arg0, s32 n);
void func_8004B760_main(s32 prio, s32 sprId, void* draw, f32 fov, Vec* eye, Vec* at);
void func_8004BCE4_main(void* work);
void func_8004AD70_main(void);

typedef struct WwEsprite {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[0x1E];
} WwEsprite; /* size 0x24 */

extern WwEsprite* D_800CD1DC_main;
extern D_800CCF58_main_Struct* D_800CCF58_main;
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[];

// minigame
void func_800E6F0C_minigame(s8 arg0);
u16 func_800E6E9C_minigame(void);
extern s32 D_800EBEB0_minigame[];
extern s32 D_800EBE24_minigame;

// this overlay
void func_801059A0_winners_wheel(void);
void func_80105AB0_winners_wheel(void);
void func_80105BA8_winners_wheel(void);
void func_80105C5C_winners_wheel(omObjData* obj);
void func_80105E78_winners_wheel(s32 arg0);
void func_80105F18_winners_wheel(void);
void func_80105F60_winners_wheel(void);
void func_80105F94_winners_wheel(void);
void func_80105FB0_winners_wheel(omObjData* obj);
void func_80105FE4_winners_wheel(omObjData* obj);
void func_801063B0_winners_wheel(void);
void func_80106514_winners_wheel(omObjData* obj);
void func_80106718_winners_wheel(void);
void func_80106734_winners_wheel(void);
void func_80106750_winners_wheel(void);
void func_8010677C_winners_wheel(void);
void func_80106910_winners_wheel(void);
void func_80106D2C_winners_wheel(omObjData* obj);
void func_80106EB0_winners_wheel(s32 arg0);
void func_80106F54_winners_wheel(void);
void func_8010701C_winners_wheel(void);
void func_801070CC_winners_wheel(void);
void func_801075D4_winners_wheel(omObjData* obj);
void func_801077F4_winners_wheel(void);
void func_80107820_winners_wheel(void);
void func_801078D8_winners_wheel(void);
void func_80107B04_winners_wheel(omObjData* obj);
void func_80107B0C_winners_wheel(void);
void func_80107BE0_winners_wheel(void);
void func_80107CB4_winners_wheel(void);
void func_80107D50_winners_wheel(void);
void func_80107F4C_winners_wheel(omObjData* obj);
void func_8010842C_winners_wheel(void);
void func_80108458_winners_wheel(void);
void func_801089C8_winners_wheel(void);
void func_801089F4_winners_wheel(void);
void func_80108E80_winners_wheel(void);
void func_80108F04_winners_wheel(s32 arg0);
void func_80109050_winners_wheel(void);
void func_8010907C_winners_wheel(void);
void func_80109104_winners_wheel(void);
void func_80109130_winners_wheel(void);
void func_80109388_winners_wheel(void);
void func_80109454_winners_wheel(void);
void func_801095E4_winners_wheel(omObjData* obj);
void func_8010985C_winners_wheel(void);
void func_80109A18_winners_wheel(omObjData* obj);
void func_80109B90_winners_wheel(void);
void func_80109BAC_winners_wheel(void);
void func_80109BF0_winners_wheel(void);
void func_80109C1C_winners_wheel(void);
void func_80109D44_winners_wheel(void);
void func_80109E90_winners_wheel(omObjData* obj);
void func_80109F80_winners_wheel(void);
void func_80109FAC_winners_wheel(void);
void func_8010A190_winners_wheel(void);

/* .bss (ovl_3B_bss) */
extern u8 D_8010A464_winners_wheel; /* state */
extern s16 D_8010A466_winners_wheel;
extern s32 D_8010A468_winners_wheel[6]; /* prize on each wheel slot (0x11: none) */
extern s32 D_8010A480_winners_wheel;    /* slot the wheel stopped on */
extern s32 D_8010A484_winners_wheel;
extern s32 D_8010A48C_winners_wheel;    /* the playing player */
extern s32 D_8010A490_winners_wheel;    /* CPU timer */
extern omObjData* D_8010A498_winners_wheel;
extern omObjData* D_8010A49C_winners_wheel;
extern omObjData* D_8010A4A0_winners_wheel;
extern omObjData* D_8010A4A4_winners_wheel;
extern omObjData* D_8010A4A8_winners_wheel;
extern s16 D_8010A488_winners_wheel;    /* sparkle effect */
extern s16 D_8010A48A_winners_wheel;    /* the spin-up sound */
extern s16 D_8010A48E_winners_wheel;    /* the player's port */
extern s16 D_8010A494_winners_wheel;    /* the wheel's sound */
extern s16 D_8010A4AC_winners_wheel[3]; /* player motions */
extern omObjData* D_8010A4B4_winners_wheel;
extern omObjData* D_8010A4B8_winners_wheel[2];
extern omObjData* D_8010A4C0_winners_wheel;

/* .data (0x8010A260-0x8010A2D0) */
/* The minigame control block (bowloons' BlCtrl; the header's D_80111B50_vine_with_me_Struct) */
typedef struct WwCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06; /* result message */
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
} WwCtrl;

WwCtrl D_8010A260_winners_wheel = {
    0, 3, 2, 0, 0, 0, 5, 0, { 0.0f, 0.0f, 0.0f, 0.0f }, { 0, 0, 0, 0 }, 240, 300, -1, 150, 150,
};
s16 D_8010A288_winners_wheel = 0;
s32 D_8010A28C_winners_wheel[8] = { 2, 3, 7, 4, 5, 6, 8, 9 }; /* character file directories */
s32 D_8010A2AC_winners_wheel[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };


void func_801059A0_winners_wheel(void) {
    omInitObjMan(30, 10);
    Hu3DAnimInit(16);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    func_8010A190_winners_wheel();
    func_8004A208_main();
    func_8001F38C_main(0, 0, 0);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010A260_winners_wheel);
    WipeCreateIn(0xFF, 16);
    func_80105AB0_winners_wheel();
    func_80105BA8_winners_wheel();
    func_801063B0_winners_wheel();
    func_80106910_winners_wheel();
    func_801070CC_winners_wheel();
    func_801078D8_winners_wheel();
    func_80107D50_winners_wheel();
    func_80109454_winners_wheel();
    func_80109D44_winners_wheel();
    D_8010A466_winners_wheel = 0;
    CZoom = 1800.0f;
    D_800EBE24_minigame = 0;
    D_8010A464_winners_wheel = 0;
    omAddObj(0x50, 0, 0, -1, func_80105FE4_winners_wheel);
    HuAudSeqPlay(0x44);
}

/* The background sprite. */
void func_80105AB0_winners_wheel(void) {
    Vec eye;
    Vec at;
    s16 sprId;

    sprId = InitEspriteSlot(func_8000B838_main(0x5C0006), 0, 1);
    func_8000BB94_main(sprId);
    eye.x = 0.0f;
    eye.y = 200.0f;
    eye.z = 2625.0f;
    at.x = -0.9f;
    at.y = -21.9f;
    at.z = -253.6f;
    func_8004B760_main(100, D_800CD1DC_main[sprId].unk04, func_8004BCE4_main, 11.1f, &eye, &at);
}

/* The wheel host. */
void func_80105BA8_winners_wheel(void) {
    omObjData* obj;
    WwHost* work;

    obj = omAddObj(10, 1, 0, -1, func_80105C5C_winners_wheel);
    D_8010A498_winners_wheel = obj;
    obj->data = work = HuMemAllocTag(sizeof(WwHost), 31000);
    obj->model[0] = func_8000B108_main(0x5C0000, 0x699);
    func_8001C814_main(obj->model[0], 1, 1);
    omSetTra(obj, -175.0f, -400.0f, 400.0f);
    obj->func = func_80105C5C_winners_wheel;
    work->unk00 = 0;
    work->unk04 = 0;
}

void func_80105C5C_winners_wheel(omObjData* obj) {
    WwHost* work = obj->data;

    if (work->unk00 & 1) {
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
            work->unk00 &= ~1;
            func_80105F18_winners_wheel();
        }
    }
    if ((work->unk00 & 2) && HmfModelData[obj->model[0]].unk40 <= 0.0f) {
        work->unk00 &= ~2;
        if (work->unk04 != 0) {
            func_80105F60_winners_wheel();
        }
    }
    if (work->unk00 & 4) {
        obj->trans.y -= 2.0f;
        if (obj->trans.y <= -400.0f) {
            work->unk00 &= ~4;
            func_8001C258_main(obj->model[0], 4, 4);
        }
    }
    if (work->unk00 & 8) {
        obj->trans.y += 4.0f;
        if (obj->trans.y >= -350.0f && obj->trans.y < -346.0f) {
            HuAudFXPlay(0x4CA);
        }
        if (obj->trans.y >= -200.0f) {
            obj->trans.y = -200.0f;
            work->unk00 &= ~8;
        }
    }
}

void func_80105E78_winners_wheel(s32 arg0) {
    WwHost* work = D_8010A498_winners_wheel->data;

    func_8001C814_main(D_8010A498_winners_wheel->model[0], 4, 0);
    func_8001C814_main(D_8010A498_winners_wheel->model[0], 1, 0);
    work->unk00 |= 1;
    work->unk04 = arg0;
    if (arg0 == 0) {
        func_80106718_winners_wheel();
        func_80108E80_winners_wheel();
    } else {
        func_80106734_winners_wheel();
        func_80108F04_winners_wheel(arg0);
    }
}

void func_80105F18_winners_wheel(void) {
    WwHost* work = D_8010A498_winners_wheel->data;

    func_8001C814_main(D_8010A498_winners_wheel->model[0], 4, 4);
    work->unk00 |= 2;
}

void func_80105F60_winners_wheel(void) {
    WwHost* work = D_8010A498_winners_wheel->data;

    work->unk00 |= 4;
    HuAudFXPlay(0x4CA);
}

void func_80105F94_winners_wheel(void) {
    WwHost* work = D_8010A498_winners_wheel->data;

    work->unk00 |= 8;
}

void func_80105FB0_winners_wheel(omObjData* obj) {
    if (WipeStatGet() == 0) {
        func_8005F524_main();
        omOvlReturnEx(1);
    }
}

void func_80105FE4_winners_wheel(omObjData* obj) {
    /* retail passes obj to the argument-less func_800E6F40_minigame */
    u8 (*getStat)(omObjData*) = (void*)func_800E6F40_minigame;

    if (D_800D530C_main != 0) {
        func_8004AD70_main();
        HuAudSeqFadeOut(30);
        WipeCreateOut(0, 20);
    }
    switch (getStat(obj)) {
        case 0:
            if (func_800E6E9C_minigame() == 15) {
                func_8010842C_winners_wheel();
            }
            break;
        case 2:
            if (func_800E6E9C_minigame() == 0) {
                omAddPrcObj(func_80109388_winners_wheel, 0x50, 0, 0);
                D_8010A464_winners_wheel = 1;
            }
            if (D_8010A464_winners_wheel == 1) {
                if (!(GwPlayer[D_8010A48C_winners_wheel].stat & 1)) {
                    if (D_800D5558_main[GwPlayer[D_8010A48C_winners_wheel].pad] == 0x8000) {
                        goto stop;
                    }
                } else if (--D_8010A490_winners_wheel == 0) {
                stop:
                    func_80106EB0_winners_wheel(1);
                    D_8010A464_winners_wheel = 3;
                }
            }
            if (D_8010A464_winners_wheel == 2) {
                func_80106EB0_winners_wheel(2);
                D_8010A464_winners_wheel = 0;
            }
            break;
        case 3:
            if (func_800E6E9C_minigame() == 1) {
                func_80109050_winners_wheel();
                func_801077F4_winners_wheel();
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                    func_8010985C_winners_wheel();
                }
            }
            if (D_8010A464_winners_wheel == 4) {
                func_80106750_winners_wheel();
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] == 0x11) {
                    func_80109F80_winners_wheel();
                } else {
                    func_80109BF0_winners_wheel();
                    func_80109BAC_winners_wheel();
                }
                D_8010A464_winners_wheel = 0;
            }
            if (D_8010A464_winners_wheel == 5) {
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                    func_801089C8_winners_wheel();
                }
                D_8010A464_winners_wheel = 0;
            }
            if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                D_8010A260_winners_wheel.unk06 = 5;
            } else {
                D_8010A260_winners_wheel.unk06 = 7;
            }
            break;
        case 4:
            if (func_800E6E9C_minigame() == 1) {
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                    func_80106F54_winners_wheel();
                    func_80107BE0_winners_wheel();
                } else {
                    func_8010701C_winners_wheel();
                    func_80107CB4_winners_wheel();
                    HuAudFXPlay(0x4CF);
                }
            }
            break;
        case 5:
            if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
                GwPlayer[D_8010A48C_winners_wheel].bonusCoin = D_8010A468_winners_wheel[D_8010A480_winners_wheel];
            } else {
                GwPlayer[D_8010A48C_winners_wheel].bonusCoin = -1;
            }
            WipeCreateOut(0, 20);
            obj->func = func_80105FB0_winners_wheel;
            break;
    }
}

/* The wheel. */
void func_801063B0_winners_wheel(void) {
    omObjData* obj;
    WwWheel* work;

    obj = omAddObj(0xFF, 3, 0, -1, func_80106514_winners_wheel);
    obj->data = HuMemAllocTag(sizeof(WwWheel), 31000);
    D_8010A49C_winners_wheel = obj;
    work = obj->data;
    obj->model[0] = func_8000B108_main(0x5C0001, 0x6B9);
    obj->model[1] = func_8000B108_main(0x5C0002, 0x6B9);
    obj->model[2] = func_8000B108_main(0x5C0004, 0xA99);
    obj->func = func_80106514_winners_wheel;
    work->unk00 = 0;
    work->unk04 = 0.0f;
    work->unk0C = 0.0f;
    work->unk10 = 0.0f;
    work->unk08 = 0.93f;
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, work->unk08, work->unk08, 1.0f);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 10.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 180.0f, 180.0f);
    Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, 0.0f);
}

void func_80106514_winners_wheel(omObjData* obj) {
    WwWheel* work = obj->data;

    func_80088910_main((f32(*)[4])HmfModelData[obj->model[0]].mtx, 0.0f, 0.0f, -work->unk10);
    omSetRot(obj, work->unk0C, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[1], work->unk0C, 180.0f, 180.0f);
    Hu3DModelRotSet(obj->model[2], work->unk0C, 0.0f, 0.0f);
    omSetSca(obj, work->unk08, work->unk08, 1.0f);
    if (work->unk00 & 1) {
        work->unk10 += work->unk04;
        if (work->unk10 >= 360.0f) {
            work->unk10 -= 360.0f;
        }
    }
    if (work->unk00 & 2) {
        work->unk04 += 0.2f;
        if (work->unk04 >= 2.4f) {
            work->unk04 = 2.4f;
            work->unk00 &= ~2;
        }
    }
    if (work->unk00 & 4) {
        work->unk04 -= 0.2f;
        if (work->unk04 <= 0.0f) {
            work->unk04 = 0.2f;
        }
        if ((s32)work->unk10 % 20 == 0) {
            work->unk04 = 0.0f;
            work->unk00 &= ~4;
            work->unk00 &= ~1;
        }
    }
}

void func_80106718_winners_wheel(void) {
    WwWheel* work = D_8010A49C_winners_wheel->data;

    work->unk00 |= 3;
}

void func_80106734_winners_wheel(void) {
    WwWheel* work = D_8010A49C_winners_wheel->data;

    work->unk00 |= 5;
}

void func_80106750_winners_wheel(void) {
    omAddPrcObj(func_8010677C_winners_wheel, 0x50, 0, 0);
}

/* The wheel tips over (30 frames, 6 degrees a frame) with its prizes, rim lights and the won prize. */
void func_8010677C_winners_wheel(void) {
    WwWheel* wheel = D_8010A49C_winners_wheel->data;
    WwPrize* prize = D_8010A4A0_winners_wheel->data;
    WwRim* rim = D_8010A4A4_winners_wheel->data;
    WwShow* show;
    s32 i;
    s32 j;

    for (i = 0; i < 30; i++) {
        wheel->unk0C += 6.0f;
        for (j = 0; j < 6; j++) {
            prize->unk48[j] += 6.0f;
            prize->unk90 = cosdf(i * 6.0f);
            prize->unk94 = cosdf(i * 6.0f);
        }
        for (j = 0; j < 6; j++) {
            rim->unk34[j] += 6.0f;
        }
        if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 0x11) {
            show = D_8010A4A8_winners_wheel->data;
            show->unk14 += 6.0f;
            show->unk08 = 2.0f * sindf(show->unk14 - 180.0f);
            show->unk0C = 2.0f * cosdf(show->unk14);
        }
        HuPrcVSleep();
    }
    D_8010A464_winners_wheel = 5;
    omDelPrcObj(NULL);
}

/* The player's character. */
void func_80106910_winners_wheel(void) {
    s32 sp18[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 sp38[8] = { 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0 };
    s32 sp58[8][4] = {
        { 0, 0x8C, 0x2F, 0x36 }, { 0, 0x8C, 0x2F, 0x36 }, { 0, 0x8C, 0x2F, 0x36 }, { 0, 0x8C, 0x2F, 0x36 },
        { 0, 0x8C, 0x2F, 0x36 }, { 0, 0x8C, 0x2F, 0x36 }, { 0, 0x8C, 0x2F, 0x36 }, { 0, 0x8C, 0x2F, 0x36 },
    };
    s32 spD8[8] = { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B };
    s32 spF8[8] = { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D };
    s32 sp118[8] = { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C };
    omObjData* obj;
    WwPlayer* work;
    s32 i;
    s16 chr;
    s32 dir;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            D_8010A48C_winners_wheel = i;
            break;
        }
    }
    obj = omAddObj(0x50, 5, 10, -1, func_80106D2C_winners_wheel);
    obj->data = HuMemAllocTag(sizeof(WwPlayer), 31000);
    D_8010A4B4_winners_wheel = obj;
    work = obj->data;
    work->unk04 = 0;
    work->unk00 = 0;
    work->unk08 = 0;
    work->unk0C = 0.93f;
    chr = GwPlayer[D_8010A48C_winners_wheel].chr;
    dir = D_8010A28C_winners_wheel[chr] << 16;
    obj->model[0] = func_8000B108_main(dir | sp38[chr], 0x6C9);
    work->unk10 = -170.0f;
    work->unk14 = -125.0f;
    work->unk18 = 230.0f;
    omSetTra(obj, work->unk10, work->unk14, work->unk18);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        func_8000B460_main(obj, i, func_80017BB8_main(chr, sp58[chr][i]));
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    D_8010A4AC_winners_wheel[0] = func_80017790_main(obj->model[0], 1, D_8010A2AC_winners_wheel[chr], dir | spD8[chr]);
    D_8010A4AC_winners_wheel[1] = func_80017AD8_main(dir | sp118[chr]);
    D_8010A4AC_winners_wheel[2] = func_80017AD8_main(dir | spF8[chr]);
    func_8001C514_main(obj->model[0]);
}

void func_80106D2C_winners_wheel(omObjData* obj) {
    WwPlayer* work = obj->data;

    omSetSca(obj, work->unk0C, work->unk0C, work->unk0C);
    omSetTra(obj, work->unk10, work->unk14, work->unk18);
    if (work->unk00 & 1) {
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
            func_8001C814_main(obj->model[0], 4, 4);
            if (work->unk08 != 0) {
                work->unk00 |= 2;
            }
            work->unk00 &= ~1;
        }
    }
    if (work->unk00 & 2) {
        if (HmfModelData[obj->model[0]].unk40 <= 0.0f) {
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
            work->unk00 &= ~2;
        }
    }
}

void func_80106EB0_winners_wheel(s32 arg0) {
    WwPlayer* work = D_8010A4B4_winners_wheel->data;

    work->unk00 |= 1;
    work->unk08 = arg0;
    func_8001C624_main(D_8010A4B4_winners_wheel->model[0], HmfModelData[D_8010A4B4_winners_wheel->motion[1]].unk02, 0, 10, 0);
    func_8001C814_main(D_8010A4B4_winners_wheel->model[0], 4, 0);
    HuAudFXPlay(0x4C9);
    func_80105E78_winners_wheel(arg0);
}

/* The player cheers: won a prize. */
void func_80106F54_winners_wheel(void) {
    u8 chr = GwPlayer[D_8010A48C_winners_wheel].chr;

    func_8001C624_main(D_8010A4B4_winners_wheel->model[0], HmfModelData[D_8010A4B4_winners_wheel->motion[2]].unk02, 0, 10, 0);
    func_80017954_main(D_8010A4B4_winners_wheel->model[0], 1, D_8010A2AC_winners_wheel[chr], D_8010A4AC_winners_wheel[1]);
    func_80045ED0_main((D_8010A28C_winners_wheel[chr] << 16) | 0x2F);
}

/* The player is let down: no prize. */
void func_8010701C_winners_wheel(void) {
    u8 chr = GwPlayer[D_8010A48C_winners_wheel].chr;

    func_8001C624_main(D_8010A4B4_winners_wheel->model[0], HmfModelData[D_8010A4B4_winners_wheel->motion[3]].unk02, 0, 10, 0);
    func_80017954_main(D_8010A4B4_winners_wheel->model[0], 1, D_8010A2AC_winners_wheel[chr], D_8010A4AC_winners_wheel[2]);
}

/* The prizes on the wheel: one empty slot, the rest from the board's prize list. */
void func_801070CC_winners_wheel(void) {
    s32 count[16];
    s32 frames[6] = { 30, 45, 60, 73, 85, 98 };
    omObjData* obj;
    WwPrize* work;
    s32 none;
    s32 i;
    s32 j;
    s32 k;
    s32 sum;
    s32 d;
    s32 kind;
    void* data;
    s16 id;

    obj = omAddObj(0xFF, 6, 0, -1, func_801075D4_winners_wheel);
    obj->data = HuMemAllocTag(sizeof(WwPrize), 31000);
    D_8010A4A0_winners_wheel = obj;
    work = obj->data;
    none = (u8)(rand8() % 6);
    D_8010A468_winners_wheel[none] = 0x11;
    data = DataRead(0x5C0007);
    k = HmfSprModelCreate(data, 0x699, 8);
    DataClose(data);
    obj->model[none] = D_800CBB60_main[(s16)k].unk00;
    work->unk60[none] = none * 60.0f + 30.0f;
    work->unk48[none] = 0.0f;
    work->unk00[none] = sindf(work->unk60[none]) * 70.0f;
    work->unk18[none] = cosdf(work->unk60[none]) * 70.0f;
    work->unk30[none] = 5.0f;
    work->unk78[none] = 1.395f;
    for (i = 0; i < 16; i++) {
        count[i] = 0;
    }
    for (j = 0, i = 0; i < 6; i++) {
        if (i != none) {
            kind = D_800A11D0_main[j++];
            count[kind]++;
            D_8010A468_winners_wheel[i] = kind;
            data = DataRead(0x21002C);
            id = HmfSprModelCreate(data, 0x699, 8);
            func_8001473C_main(id, kind);
            DataClose(data);
            obj->model[i] = D_800CBB60_main[id].unk00;
            work->unk60[i] = i * 60.0f + 30.0f;
            work->unk48[i] = 0.0f;
            work->unk00[i] = sindf(work->unk60[i]) * 70.0f;
            work->unk18[i] = cosdf(work->unk60[i]) * 70.0f;
            work->unk30[i] = 5.0f;
            work->unk78[i] = 1.395f;
        }
    }
    work->unk90 = 1.0f;
    work->unk94 = 1.0f;
    omSetTra(obj, work->unk00[0], work->unk18[0], work->unk30[0]);
    D_8010A480_winners_wheel = 0;
    D_8010A484_winners_wheel = 5;
    if (GwPlayer[D_8010A48C_winners_wheel].stat & 1) {
        kind = (u8)(rand8() % 100);
        for (k = 0, sum = 0; k < 5; k++) {
            if (sum <= kind && kind < sum + D_800A11DC_main[k]) {
                break;
            }
            sum += D_800A11DC_main[k];
        }
        if (k == 5) {
            k = 4;
        }
        /* skip the empty slot */
        if (k >= none) {
            k++;
        }
        d = (4 - GwPlayer[D_8010A48C_winners_wheel].cpu_difficulty) * 5;
        D_8010A490_winners_wheel = frames[k] + rand8() % (d * 2) - d;
    }
}

void func_801075D4_winners_wheel(omObjData* obj) {
    WwPrize* work = obj->data;
    WwWheel* wheel = D_8010A49C_winners_wheel->data;
    s32 i;

    for (i = 0; i < 6; i++) {
        work->unk00[i] = sindf(work->unk60[i] + wheel->unk10) * 70.0f * wheel->unk08;
        work->unk18[i] = cosdf(work->unk60[i] + wheel->unk10) * 70.0f * wheel->unk08 * work->unk90;
        work->unk30[i] = work->unk94 * 5.0f;
        func_80088910_main((f32(*)[4])HmfModelData[obj->model[i]].mtx, 0.0f, 0.0f, -work->unk60[i] - wheel->unk10);
        if (i == 0) {
            omSetTra(obj, work->unk00[0], work->unk18[0], work->unk30[0]);
            omSetRot(obj, work->unk48[0], 0.0f, 0.0f);
            omSetSca(obj, work->unk78[0], work->unk78[0], work->unk78[0]);
        } else {
            Hu3DModelPosSet(obj->model[i], work->unk00[i], work->unk18[i], work->unk30[i]);
            Hu3DModelScaleSet(obj->model[i], work->unk78[i], work->unk78[i], work->unk78[i]);
            Hu3DModelRotSet(obj->model[i], work->unk48[i], 0.0f, 0.0f);
        }
        if (work->unk30[i] <= 0.0f) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
}

void func_801077F4_winners_wheel(void) {
    omAddPrcObj(func_80107820_winners_wheel, 0x50, 0, 0);
}

/* The won prize pulses. */
void func_80107820_winners_wheel(void) {
    WwPrize* work = D_8010A4A0_winners_wheel->data;
    s32 i;

    for (i = 0; i < 60; i++) {
        work->unk78[D_8010A480_winners_wheel] = sindf(i * 36.0f) * 0.3f + 1.395f;
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

/* The two hosts beside the wheel. */
void func_801078D8_winners_wheel(void) {
    f32 pos[4][2];
    omObjData* obj;
    WwHostPair* work;
    s32 i;
    s32 attr;

    pos[0][0] = -300.0f;
    pos[0][1] = 300.0f;
    pos[1][0] = -62.5f;
    pos[1][1] = -12.5f;
    pos[2][0] = -275.0f;
    pos[2][1] = -275.0f;
    pos[3][0] = 30.0f;
    pos[3][1] = -30.0f;
    attr = 0x699;
    for (i = 0; i < 2; i++) {
        obj = omAddObj(0xFF, 1, 5, -1, func_80107B04_winners_wheel);
        D_8010A4B8_winners_wheel[i] = obj;
        obj->data = HuMemAllocTag(sizeof(WwHostPair), 31000);
        work = obj->data;
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0xA0147, attr);
        } else {
            obj->model[0] = Hu3DModelLink(D_8010A4B8_winners_wheel[0]->model[0]);
        }
        work->unk00 = 0;
        work->unk04 = i;
        omSetTra(obj, pos[0][i], pos[1][i], pos[2][i]);
        omSetRot(obj, 0.0f, pos[3][i], 0.0f);
        omSetSca(obj, 0.7f, 0.7f, 0.7f);
        func_8000B460_main(obj, 0, 0xA0148);
        func_8000B460_main(obj, 1, 0xA0149);
        func_8000B460_main(obj, 2, 0xA014A);
        func_8000B460_main(obj, 3, 0xA014B);
        func_8000B460_main(obj, 4, 0xA014C);
    }
}

void func_80107B04_winners_wheel(omObjData* obj) {
}

void func_80107B0C_winners_wheel(void) {
    func_8001C624_main(D_8010A4B8_winners_wheel[0]->model[0], HmfModelData[D_8010A4B8_winners_wheel[0]->motion[0]].unk02, 0, 10, 0);
    func_8001C624_main(D_8010A4B8_winners_wheel[1]->model[0], HmfModelData[D_8010A4B8_winners_wheel[1]->motion[0]].unk02, 0, 10, 0);
    func_8001C814_main(D_8010A4B8_winners_wheel[0]->model[0], 2, 2);
    func_8001C814_main(D_8010A4B8_winners_wheel[1]->model[0], 2, 2);
}

void func_80107BE0_winners_wheel(void) {
    func_8001C624_main(D_8010A4B8_winners_wheel[0]->model[0], HmfModelData[D_8010A4B8_winners_wheel[0]->motion[2]].unk02, 0, 10, 0);
    func_8001C624_main(D_8010A4B8_winners_wheel[1]->model[0], HmfModelData[D_8010A4B8_winners_wheel[1]->motion[2]].unk02, 0, 10, 0);
    func_8001C814_main(D_8010A4B8_winners_wheel[0]->model[0], 2, 2);
    func_8001C814_main(D_8010A4B8_winners_wheel[1]->model[0], 2, 2);
}

void func_80107CB4_winners_wheel(void) {
    func_8001C624_main(D_8010A4B8_winners_wheel[0]->model[0], HmfModelData[D_8010A4B8_winners_wheel[0]->motion[3]].unk02, 0, 10, 0);
    func_8001C624_main(D_8010A4B8_winners_wheel[1]->model[0], HmfModelData[D_8010A4B8_winners_wheel[1]->motion[3]].unk02, 0, 10, 0);
}

/* NON_MATCHING: retail passes the else branch's 0.0f arguments as integer zeros and keeps only the
   first branch's in a hoisted register (loop invariants differ; masked 10). Logic checked. */
#ifdef NON_MATCHING
/* The 18 pegs round the wheel. */
void func_80107D50_winners_wheel(void) {
    omObjData* obj;
    WwPegs* work;
    s32 i;
    s32 attr;

    obj = omAddObj(0xFF, 18, 0, -1, func_80107F4C_winners_wheel);
    obj->data = work = HuMemAllocTag(sizeof(WwPegs), 31000);
    D_8010A4C0_winners_wheel = obj;
    work->unk94 = 0.0f;
    work->unk00 = 0x20;
    work->unk9C = 0;
    work->unkA0 = 0;
    attr = 0x6BD;
    for (i = 0; i < 18; i++) {
        work->unk4C[i] = work->unk04[i] = i * 20.0f;
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x5C0005, attr);
            omSetTra(obj, sindf(work->unk04[0]) * -10.5f, cosdf(work->unk04[0]) * -10.5f, 0.0f);
            omSetRot(obj, 0.0f, 0.0f, -work->unk04[0]);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelPosSet(obj->model[i], sindf(work->unk04[i]) * -10.5f, cosdf(work->unk04[i]) * -10.5f, 0.0f);
            Hu3DModelRotSet(obj->model[i], 0.0f, 0.0f, -work->unk04[i]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80107D50_winners_wheel);
#endif

void func_80107F4C_winners_wheel(omObjData* obj) {
    WwPegs* work = obj->data;
    WwWheel* wheel = D_8010A49C_winners_wheel->data;
    f32 slow;
    f32 t;
    s32 i;

    for (i = 0; i < 18; i++) {
        if (i == 0) {
            omSetRot(obj, 0.0f, 0.0f, -work->unk04[0]);
        } else {
            Hu3DModelRotSet(obj->model[i], 0.0f, 0.0f, -work->unk04[i]);
        }
    }
    if (work->unk00 & 1) {
        work->unk4C[0] -= work->unk94;
        work->unk04[0] = (s32)((work->unk4C[0] + 0.5f) / 20.0f) * 20.0f;
        if (work->unk4C[0] <= 0.0f) {
            work->unk4C[0] += 360.0f;
        }
        t = work->unk04[0] + 10.0f;
        D_8010A480_winners_wheel = (s32)((360.0f - wheel->unk10 + t) / 60.0f) % 6;
    }
    if (work->unk00 & 8) {
        t = work->unk04[0] + 10.0f;
        D_8010A480_winners_wheel = (s32)((360.0f - wheel->unk10 + t) / 60.0f) % 6;
        D_8010A484_winners_wheel = 5 - D_8010A480_winners_wheel;
    }
    if (work->unk00 & 2) {
        work->unk94 += 0.29f;
        if (work->unk94 >= 20.0f) {
            work->unk94 = 20.0f;
            work->unk00 &= ~2;
        }
    }
    if (work->unk00 & 4) {
        if (work->unk04[1] != work->unk04[0]) {
            HuAudFXPlay(0x4C8);
        }
        slow = (work->unkA0 != 2) ? 1.0f : 2.0f;
        if (work->unk94 >= slow) {
            work->unk94 -= 0.02f;
            D_8010A288_winners_wheel -= 9;
            if (D_8010A288_winners_wheel < -900) {
                D_8010A288_winners_wheel = -900;
            }
            HuAudFXPitchSet(D_8010A494_winners_wheel, D_8010A288_winners_wheel);
        }
        if (work->unkA0 != 2) {
            if (work->unk04[0] == work->unk98 && work->unk04[1] != work->unk04[0]) {
                work->unk9C--;
            }
            if (work->unk9C == 0) {
                work->unk94 = 0.0f;
                work->unk00 &= ~4;
                work->unk00 &= ~1;
                HuAudFXStop(D_8010A494_winners_wheel);
                HuAudFXPlay(0x4CD);
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] == 0x11) {
                    omVibrate(D_8010A48E_winners_wheel, 10, 0, 10);
                } else {
                    omVibrate(D_8010A48E_winners_wheel, 2, 3, 10);
                }
                func_800E6F0C_minigame(3);
            }
        } else if (work->unk94 <= slow && D_8010A468_winners_wheel[D_8010A480_winners_wheel] == 0x11) {
            work->unk94 = 0.0f;
            work->unk00 &= ~4;
            work->unk00 &= ~1;
            omVibrate(D_8010A48E_winners_wheel, 10, 0, 10);
            func_800E6F0C_minigame(3);
            HuAudFXStop(D_8010A494_winners_wheel);
            HuAudFXPlay(0x4CD);
        }
        work->unk04[1] = work->unk04[0];
    }
}

void func_8010842C_winners_wheel(void) {
    omAddPrcObj(func_80108458_winners_wheel, 0x50, 0, 0);
}

/* The intro: the peg ring gathers, the hosts react, the pegs blink three times. */
void func_80108458_winners_wheel(void) {
    WwPegs* work = D_8010A4C0_winners_wheel->data;
    WwHost* host = D_8010A498_winners_wheel->data;
    s32 i;
    s32 j;

    work->unk00 = (work->unk00 | 8) & ~0x20;
    func_8001C258_main(D_8010A4C0_winners_wheel->model[0], 4, 0);
    func_8001C258_main(D_8010A4C0_winners_wheel->model[1], 4, 0);
    for (i = 0; i < 18; i++) {
        if (i == 0) {
            omSetTra(D_8010A4C0_winners_wheel, sindf(work->unk04[0]) * -10.5f, cosdf(work->unk04[0]) * -10.5f, 0.0f);
        } else {
            Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[i], sindf(work->unk04[i]) * -10.5f,
                            cosdf(work->unk04[i]) * -10.5f, 0.0f);
        }
    }
    for (i = 0; i < 18; i++) {
        if (i != 9) {
            work->unk04[0] = i * 20.0f;
            work->unk04[1] = 340.0f - work->unk04[0];
            omSetTra(D_8010A4C0_winners_wheel, sindf(work->unk04[0]) * -10.5f, cosdf(work->unk04[0]) * -10.5f, -1.0f);
            Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[1], sindf(work->unk04[1]) * -10.5f,
                            cosdf(work->unk04[1]) * -10.5f, -1.0f);
            HuAudFXPlay(0x4C8);
            HuPrcSleep(4);
        }
    }
    work->unk00 &= ~8;
    D_8010A484_winners_wheel = -1;
    func_8001C258_main(D_8010A4C0_winners_wheel->model[0], 4, 4);
    func_8001C258_main(D_8010A4C0_winners_wheel->model[1], 4, 4);
    work->unk00 |= 0x20;
    func_80109104_winners_wheel();
    while (CZoom < 2887.1f) {
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        func_8001C624_main(D_8010A4B8_winners_wheel[i]->model[0], HmfModelData[D_8010A4B8_winners_wheel[i]->motion[4]].unk02, 0, 10, 0);
        func_8001C814_main(D_8010A4B8_winners_wheel[i]->model[0], 2, 2);
    }
    func_80105F94_winners_wheel();
    for (i = 0; i < 18; i++) {
        work->unk04[i] = i * 20.0f;
        if (i == 0) {
            omSetTra(D_8010A4C0_winners_wheel, sindf(work->unk04[0]), cosdf(work->unk04[0]), 0.0f);
        } else {
            Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[i], sindf(work->unk04[i]), cosdf(work->unk04[i]), 0.0f);
        }
        func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 0);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 18; i++) {
            func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 0);
        }
        work->unk00 = (work->unk00 | 0x10) & ~0x20;
        HuPrcSleep(10);
        for (i = 0; i < 18; i++) {
            func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 4);
        }
        work->unk00 = (work->unk00 & ~0x10) | 0x20;
        HuPrcSleep(10);
    }
    while (host->unk00 & 8) {
        HuPrcVSleep();
    }
    func_80106EB0_winners_wheel(0);
    func_80107B0C_winners_wheel();
    work->unk00 &= ~0x20;
    omDelPrcObj(NULL);
}

void func_801089C8_winners_wheel(void) {
    omAddPrcObj(func_801089F4_winners_wheel, 0x50, 0, 0);
}

/* The peg ring's endless show after the win: eight pegs chase round, then all blink. */
void func_801089F4_winners_wheel(void) {
    WwPegs* work = D_8010A4C0_winners_wheel->data;
    s32 i;
    s32 j;
    f32 angle;

    for (i = 0; i < 18; i++) {
        if (i == 0) {
            omSetTra(D_8010A4C0_winners_wheel, sindf(work->unk04[0]), cosdf(work->unk04[0]), 0.0f);
        } else {
            Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[i], sindf(work->unk04[i]), cosdf(work->unk04[i]), 0.0f);
        }
    }
    while (TRUE) {
        func_8001C258_main(D_8010A4C0_winners_wheel->model[0], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[1], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[2], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[3], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[4], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[5], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[6], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[7], 4, 0);
        for (i = 0; i < 36; i++) {
            angle = i * 20.0f;
            work->unk04[0] = angle;
            work->unk04[1] = 340.0f - angle;
            work->unk04[2] = angle + 180.0f;
            work->unk04[3] = 160.0f - angle;
            work->unk04[4] = angle + 100.0f;
            work->unk04[5] = 80.0f - angle;
            work->unk04[6] = angle + 280.0f;
            work->unk04[7] = 260.0f - angle;
            omSetTra(D_8010A4C0_winners_wheel, sindf(work->unk04[0]), cosdf(work->unk04[0]), -1.0f);
            for (j = 1; j < 8; j++) {
                Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[j], sindf(work->unk04[j]), cosdf(work->unk04[j]), -1.0f);
            }
            HuPrcSleep(1);
        }
        for (i = 0; i < 18; i++) {
            work->unk04[i] = i * 20.0f;
            if (i == 0) {
                omSetTra(D_8010A4C0_winners_wheel, sindf(work->unk04[0]), cosdf(work->unk04[0]), 0.0f);
            } else {
                Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[i], sindf(work->unk04[i]), cosdf(work->unk04[i]), 0.0f);
            }
            func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 0);
        }
        for (j = 0; j < 8; j++) {
            for (i = 0; i < 18; i++) {
                func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 0);
            }
            HuPrcSleep(1);
            for (i = 0; i < 18; i++) {
                func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 4);
            }
            HuPrcSleep(1);
        }
    }
}

/* The peg ring starts turning. */
void func_80108E80_winners_wheel(void) {
    WwPegs* work = D_8010A4C0_winners_wheel->data;

    work->unk00 |= 3;
    work->unk04[0] = 340.0f;
    work->unk4C[0] = 340.0f;
    func_8001C258_main(D_8010A4C0_winners_wheel->model[0], 4, 0);
    omSetRot(D_8010A4C0_winners_wheel, 0.0f, 0.0f, work->unk04[0]);
    D_8010A48A_winners_wheel = HuAudFXPlay(0x4C7);
}

/* The peg ring slows down: it stops 0, 2 or 4 clicks past the current peg. */
void func_80108F04_winners_wheel(s32 arg0) {
    WwPegs* work = D_8010A4C0_winners_wheel->data;
    s32 r;
    f32 n;

    work->unk00 |= 4;
    work->unkA0 = arg0;
    r = (u8)(rand8() % 20);
    if (r < 3) {
        n = 4.0f;
    } else if (r < 6) {
        n = 8.0f;
    } else {
        n = 6.0f;
    }
    n -= 4.0f;
    work->unk98 = work->unk04[0] - n * 20.0f;
    work->unk9C = 2;
    if (n == 0.0f) {
        work->unk9C = 1;
    }
    if (work->unk98 < 0.0f) {
        work->unk98 += 360.0f;
    }
    work->unk94 = 4.0f;
    HuAudFXStop(D_8010A48A_winners_wheel);
    D_8010A494_winners_wheel = HuAudFXPlay(0x4CB);
}

void func_80109050_winners_wheel(void) {
    omAddPrcObj(func_8010907C_winners_wheel, 0x50, 0, 0);
}

/* The pointer peg blinks three times, then the result. */
void func_8010907C_winners_wheel(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_8001C258_main(D_8010A4C0_winners_wheel->model[0], 4, 0);
        HuPrcSleep(10);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[0], 4, 4);
        HuPrcSleep(10);
    }
    D_8010A464_winners_wheel = 4;
    omDelPrcObj(NULL);
}

void func_80109104_winners_wheel(void) {
    omAddPrcObj(func_80109130_winners_wheel, 0x50, 0, 0);
}

/* The camera pulls back while the wheel, its prizes and the player grow to full size. */
void func_80109130_winners_wheel(void) {
    WwWheel* wheel = D_8010A49C_winners_wheel->data;
    WwPrize* prize = D_8010A4A0_winners_wheel->data;
    WwPlayer* player = D_8010A4B4_winners_wheel->data;
    s32 i;
    s32 j;
    f32 t;
    f32 step = (1.0f - 0.93f) / 30.0f;

    for (i = 0; i < 30; i++) {
        CZoom += 36.2f;
        for (j = 0; j < 4; j++) {
            CZoomM[j] = CZoom;
        }
        wheel->unk08 = step + wheel->unk08;
        player->unk0C = step + player->unk0C;
        t = 30 - i;
        player->unk10 = t * 5.0f / 30.0f + -175.0f;
        player->unk14 = t * 0.0f / 30.0f + -125.0f;
        player->unk18 = t * -95.0f / 30.0f + 325.0f;
        for (j = 0; j < 6; j++) {
            prize->unk78[j] = wheel->unk08 * 1.5f;
        }
        HuPrcVSleep();
    }
    wheel->unk08 = 1.0f;
    player->unk0C = 1.0f;
    for (j = 0; j < 6; j++) {
        prize->unk78[j] = 1.5f;
    }
    CZoom = 2887.1f;
    player->unk10 = -175.0f;
    player->unk14 = -125.0f;
    player->unk18 = 325.0f;
    omDelPrcObj(NULL);
}

/* The 10-second timer: on time up the player stops the wheel. */
void func_80109388_winners_wheel(void) {
    s32 sec = 10;
    s32 t = 30;

    GMesPosSet(GMesCreate(0x1A, 10, 160, 28), 160.0f, 28.0f);
    do {
        if (--t == 0) {
            t = 30;
            sec--;
        }
        func_8003F578_main(sec);
        HuPrcVSleep();
        if (D_8010A464_winners_wheel == 3) {
            break;
        }
    } while (sec > 0);
    func_8003F5C0_main();
    if (D_8010A464_winners_wheel != 3) {
        D_8010A464_winners_wheel = 2;
    }
    omDelPrcObj(NULL);
}

/* The wheel's six rim lights. */
void func_80109454_winners_wheel(void) {
    omObjData* obj;
    WwRim* work;
    WwWheel* wheel;
    s32 i;
    s32 attr = 0x63D;

    obj = omAddObj(0xFF, 6, 0, -1, func_801095E4_winners_wheel);
    D_8010A4A4_winners_wheel = obj;
    obj->data = HuMemAllocTag(sizeof(WwRim), 31000);
    work = obj->data;
    wheel = D_8010A49C_winners_wheel->data;
    work->unk00 = 0;
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x5C0003, attr);
            omSetTra(obj, 0.0f, 0.0f, 6.0f);
            omSetSca(obj, wheel->unk08, wheel->unk08, 1.0f);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelPosSet(obj->model[i], 0.0f, 0.0f, 6.0f);
            Hu3DModelScaleSet(obj->model[i], wheel->unk08, wheel->unk08, 1.0f);
        }
        work->unk04[i] = 0.0f;
        work->unk1C[i] = 0.0f;
        work->unk34[i] = 0.0f;
        work->unk4C[i] = i * 60.0f;
    }
}

/* The rim lights follow the wheel; the stopped slot's (and the slot opposite) or all stay lit. */
void func_801095E4_winners_wheel(omObjData* obj) {
    WwRim* work = obj->data;
    WwWheel* wheel = D_8010A49C_winners_wheel->data;
    WwPegs* pegs = D_8010A4C0_winners_wheel->data;
    s32 i;

    for (i = 0; i < 6; i++) {
        func_80088910_main((f32(*)[4])HmfModelData[obj->model[i]].mtx, 0.0f, 0.0f, -work->unk4C[i]);
        if (i == 0) {
            omSetRot(obj, work->unk34[0], 0.0f, 0.0f);
            omSetSca(obj, wheel->unk08, wheel->unk08, 1.0f);
        } else {
            Hu3DModelRotSet(obj->model[i], work->unk34[i], 0.0f, 0.0f);
            Hu3DModelScaleSet(obj->model[i], wheel->unk08, wheel->unk08, 1.0f);
        }
        if (work->unk34[i] >= 90.0f) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
    for (i = 0; i < 6; i++) {
        func_8001C258_main(obj->model[i], 4, 0);
    }
    if (pegs->unk00 & 0x20) {
        D_8010A484_winners_wheel = -1;
        D_8010A480_winners_wheel = -1;
    }
    for (i = 0; i < 6; i++) {
        work->unk4C[i] = i * 60.0f + wheel->unk10;
        if (i == D_8010A480_winners_wheel || i == D_8010A484_winners_wheel || (pegs->unk00 & 0x10)) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
}

/* The won prize, shown over the wheel. */
void func_8010985C_winners_wheel(void) {
    s32 files[16] = {
        0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C,
    };
    omObjData* obj;
    WwShow* work;
    void* data;
    s32 file;
    s32 id;

    obj = omAddObj(0xFE, 1, 0, -1, func_80109A18_winners_wheel);
    obj->data = HuMemAllocTag(sizeof(WwShow), 31000);
    D_8010A4A8_winners_wheel = obj;
    work = obj->data;
    /* retail compares the slot, not its prize, with 0x11: never equal (only called for a prize) */
    if (D_8010A480_winners_wheel == 0x11) {
        file = 0x5C0007;
    } else {
        file = 0x210000;
        file |= files[D_8010A468_winners_wheel[D_8010A480_winners_wheel]];
    }
    data = DataRead(file);
    id = HmfSprModelCreate(data, 0x69D, 8);
    DataClose(data);
    obj->model[0] = D_800CBB60_main[(s16)id].unk00;
    work->unk04 = 0.0f;
    work->unk08 = 0.0f;
    work->unk0C = 2.0f;
    work->unk10 = 0.0f;
    work->unk14 = 180.0f;
    work->unk00 = 0;
    omSetTra(obj, work->unk04, work->unk08, work->unk0C);
    omSetSca(obj, 2.2f, 2.2f, 1.0f);
    func_8001C258_main(obj->model[0], 4, 4);
}

void func_80109A18_winners_wheel(omObjData* obj) {
    WwShow* work = obj->data;

    omSetTra(obj, work->unk04, work->unk08, work->unk0C);
    omSetRot(obj, work->unk14, 0.0f, 0.0f);
    if (work->unk00 & 1) {
        work->unk10 += 5.0f;
        if (work->unk10 >= 360.0f) {
            work->unk10 -= 360.0f;
        }
        work->unk08 = sindf(work->unk10) * 10.0f + 90.0f;
    }
    if (work->unk14 >= 270.0f) {
        func_8001C258_main(obj->model[0], 4, 0);
    }
    if (work->unk14 == 270.0f) {
        omVibrate(D_8010A48E_winners_wheel, 2, 2, 20);
        HuAudFXPlay(0x10);
    }
    if (work->unk00 & 2) {
        func_8000CFA4_main(D_8010A488_winners_wheel, work->unk04, work->unk08, work->unk0C - 2.0f);
    }
}

void func_80109B90_winners_wheel(void) {
    WwShow* work = D_8010A4A8_winners_wheel->data;

    work->unk00 |= 1;
}

void func_80109BAC_winners_wheel(void) {
    WwShow* work;

    D_8010A488_winners_wheel = func_8000CED8_main(0xB0004, 0x6A9);
    work = D_8010A4A8_winners_wheel->data;
    work->unk00 |= 2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109BF0_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109C1C_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109D44_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109E90_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109F80_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_80109FAC_winners_wheel);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3B_winners_wheel/2CF3B0", func_8010A190_winners_wheel);








