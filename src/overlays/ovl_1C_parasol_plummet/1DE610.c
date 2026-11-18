#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"

// m2 pa: Parasol Plummet (4 players drift down on parasols and steer through the rings)

/* omObjData::data of a player (D_8010AB60_parasol_plummet, HuMemAllocTag 0x50) */
typedef struct PaPlayer {
    /* 0x00 */ f32 unk00; /* position */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C; /* roll (rot z) */
    /* 0x10 */ u8 unk10;
    /* 0x11 */ char unk11[3];
    /* 0x14 */ u32 unk14; /* flags: 1 frozen, 0x40 finished */
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24; /* player index */
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34; /* bump speed */
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ f32 unk48; /* target roll */
    /* 0x4C */ s32 unk4C; /* lane 0..3, then rank */
} PaPlayer; // Size 0x50

/* omObjData::data of an item (D_8010AB70_parasol_plummet) */
typedef struct PaItem {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04; /* slot in D_8010ABB8_parasol_plummet */
    /* 0x08 */ f32 unk08; /* position */
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ char unk10[0x14];
    /* 0x24 */ u8 unk24; /* 1 coin, 2 five coins, 3 hazard */
} PaItem;

typedef struct PaS32x8 {
    s32 v[8];
} PaS32x8;

typedef struct PaS32x56 {
    s32 v[8][7];
} PaS32x56;

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004AD70_main(void);
void func_8001E500_main(s16, char*, char*);
f64 fabs(f64);

extern s8 D_800CBB6E_main[]; /* stick x */
extern u16 D_800D530C_main;
extern Vec Center;
extern Vec CRot;
extern f32 CZoom;

// minigame
u16 func_800E6E9C_minigame(void);

extern s32 D_800EBEB0_minigame[];

// LOCAL
void func_80105B94_parasol_plummet(omObjData* obj);
void func_80105E94_parasol_plummet(omObjData* obj);
void func_80105EC0_parasol_plummet(s32 arg0);
void func_80106418_parasol_plummet(omObjData* obj);
void func_80106788_parasol_plummet(omObjData* obj);
void func_8010687C_parasol_plummet(omObjData* obj);
void func_8010693C_parasol_plummet(omObjData* obj);
void func_801069E4_parasol_plummet(omObjData* obj);
void func_80106AB4_parasol_plummet(omObjData* obj);
void func_80106CDC_parasol_plummet(omObjData* obj);
void func_80106DB0_parasol_plummet(omObjData* obj);
void func_80106E14_parasol_plummet(omObjData* obj);
void func_801071B4_parasol_plummet(omObjData* obj);
s16 func_801074CC_parasol_plummet(omObjData* obj);
u16 func_801076D4_parasol_plummet(omObjData* obj);
void func_80107A44_parasol_plummet(omObjData* obj);
void func_80107B5C_parasol_plummet(omObjData* obj);
void func_80107B78_parasol_plummet(omObjData* obj);
void func_80107C94_parasol_plummet(omObjData* obj);
void func_80107CD4_parasol_plummet(omObjData* obj);
void func_80107C30_parasol_plummet(omObjData* obj);
void func_80107D14_parasol_plummet(omObjData* obj);
void func_80107D30_parasol_plummet(void);
void func_80108178_parasol_plummet(omObjData* obj);
void func_8010856C_parasol_plummet(void);
void func_801089E0_parasol_plummet(omObjData* obj);
void func_80108F6C_parasol_plummet(void);
void func_80109604_parasol_plummet(void);
s16 func_80109F7C_parasol_plummet(omObjData* obj, s32 arg1);
void func_8010A160_parasol_plummet(void);
void func_8010A75C_parasol_plummet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z);

extern s32 D_8010AB50_parasol_plummet; /* camera */
extern u8 D_8010AB54_parasol_plummet;
extern omObjData* D_8010AB60_parasol_plummet[4]; /* players */
extern omObjData* D_8010AB70_parasol_plummet[18]; /* items */
extern u8 D_8010ABB8_parasol_plummet[20]; /* item slots in use */
extern omObjData* D_8010ABCC_parasol_plummet;
extern u16 D_8010ABD0_parasol_plummet;
extern f32 D_8010AC50_parasol_plummet[4]; /* lanes taken */
extern s16 D_8010AC64_parasol_plummet;
extern u8 D_8010AC66_parasol_plummet; /* minigame state */

D_80111B50_vine_with_me_Struct D_8010A8A0_parasol_plummet = {
    0, 0, 1, 2, 0, 0, 9, { 0 }, 0, { 0 }, 0xB4, 0x384, -1, 0xD2, 0x3C,
};

s32 D_8010A8C8_parasol_plummet[] = { 2, 3, 7, 4, 5, 6, 8, 9, 0, 0 }; /* model directory by character */


void func_801059A0_parasol_plummet(void) {
    omObjData* obj;
    s32 i;

    omInitObjMan(0x28, 0xA);
    Hu3DAnimInit(0x10);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_8010A75C_parasol_plummet(2500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    omOutView(obj);
    func_8001F38C_main(0, 0, 0);
    func_800E5EA0_minigame(&D_8010A8A0_parasol_plummet);
    WipeCreateIn(0xFF, 0x10);
    for (i = 0; i < 4; i++) {
        D_8010AC50_parasol_plummet[i] = 0.0f;
    }
    for (i = 0; i < 4; i++) {
        D_8010AB60_parasol_plummet[i] = NULL;
        func_80105EC0_parasol_plummet(i);
    }
    func_80107D30_parasol_plummet();
    omAddObj(0x50, 0, 0, -1, func_80108178_parasol_plummet);
    omAddObj(0x50, 0, 0, -1, func_801089E0_parasol_plummet);
    omAddObj(0x50, 0, 0, -1, func_80105B94_parasol_plummet);
    omAddPrcObj(func_8010856C_parasol_plummet, 0x50, 0x2000, 0);
    func_80108F6C_parasol_plummet();
    func_80109604_parasol_plummet();
    D_8010AB54_parasol_plummet = 0;
    D_8010ABD0_parasol_plummet = 0;
    func_8010A160_parasol_plummet();
    D_8010AC64_parasol_plummet = func_8000D658_main(0x2A9, 4);
}

/* NON_MATCHING: only differs by retail passing obj to func_800E6F40_minigame (declared (void)); with that call it
   is identical. The main loop: framework state, the finish ranking by height and the exit. */
#ifdef NON_MATCHING
void func_80105B94_parasol_plummet(omObjData* obj) {
    s32 idx[4];
    f32 val[4];
    PaPlayer* p;
    s32 i;
    s32 j;
    omObjData** objs;

    if (D_800D530C_main != 0) {
        func_8004AD70_main();
        HuAudSeqFadeOut(0x1E);
        WipeCreateOut(0, 0x14);
    }
    D_8010AC66_parasol_plummet = func_800E6F40_minigame();
    switch (D_8010AC66_parasol_plummet) {
    case 0:
        if (func_800E6E9C_minigame() == 0x14) {
            HuAudFXPlay(0x3E5);
        }
        if (func_800E6E9C_minigame() == 0x96) {
            HuAudSeqPlay(0x33);
        }
        break;
    case 1:
        break;
    case 2:
        if (D_8010ABD0_parasol_plummet == 0) {
            for (i = 0; i < 4; i++) {
                p = D_8010AB60_parasol_plummet[i]->data;
                if (!(p->unk14 & 1)) {
                    p->unk14 |= 1;
                }
            }
            D_8010ABD0_parasol_plummet++;
        }
        break;
    case 3:
        p = D_8010AB60_parasol_plummet[0]->data;
        if (!(p->unk14 & 0x40)) {
            for (i = 0; i < 4; i++) {
                p = D_8010AB60_parasol_plummet[i]->data;
                val[i] = p->unk00;
                idx[i] = i;
            }
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (val[i] < val[j]) {
                        f32 tf = val[i];
                        s32 ti;

                        val[i] = val[j];
                        val[j] = tf;
                        ti = idx[i];
                        idx[i] = idx[j];
                        idx[j] = ti;
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                p = D_8010AB60_parasol_plummet[i]->data;
                p->unk4C = idx[i];
            }
        }
        for (i = 0; i < 4; i++) {
            p = D_8010AB60_parasol_plummet[i]->data;
            if (!(p->unk14 & 0x40)) {
                func_80107C30_parasol_plummet(D_8010AB60_parasol_plummet[i]);
                func_80107D14_parasol_plummet(D_8010AB60_parasol_plummet[i]);
                func_80107D14_parasol_plummet(D_8010AB60_parasol_plummet[i]);
                p->unk14 = (p->unk14 | 0x40) & ~1;
                func_8010687C_parasol_plummet(D_8010AB60_parasol_plummet[i]);
            }
        }
        D_8010A8A0_parasol_plummet.unk06 = 9;
        if (func_800E6E9C_minigame() == 0x87) {
            HuAudSeqPlay(0x66);
        }
        break;
    case 4:
        break;
    case 5:
        WipeCreateOut(0, 0x14);
        obj->func = func_80105E94_parasol_plummet;
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80105B94_parasol_plummet);
#endif

void func_80105E94_parasol_plummet(omObjData* obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

const PaS32x8 D_8010A908_parasol_plummet = { { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 } };
const PaS32x8 D_8010A928_parasol_plummet = { { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 } };
const PaS32x56 D_8010A948_parasol_plummet = { {
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
    { 0, 0x44, 0x45, 4, 0x46, 0x2F, 0x36 },
} };


void func_80105EC0_parasol_plummet(s32 arg0) {
    PaS32x8 unused = D_8010A908_parasol_plummet;
    PaS32x8 file = D_8010A928_parasol_plummet;
    PaS32x56 mot = D_8010A948_parasol_plummet;
    omObjData* obj;
    PaPlayer* p;
    s16 chr;
    s32 dir;
    s32 id;
    s32 lane;
    f32* taken;
    s32 i;

    obj = omAddObj(0x50, 5, 0xA, -1, func_80106418_parasol_plummet);
    obj->data = HuMemAllocTag(sizeof(PaPlayer), 0x7918);
    D_8010AB60_parasol_plummet[arg0] = obj;
    p = obj->data;
    p->unk00 = 0.0f;
    p->unk04 = 0.0f;
    p->unk08 = 0.0f;
    p->unk0C = 0;
    p->unk28 = 0;
    p->unk30 = 0;
    p->unk2C = 0;
    p->unk34 = 0;
    p->unk24 = arg0;
    p->unk10 = 1;
    p->unk38 = 0;
    p->unk3C = 0;
    p->unk40 = 0;
    p->unk18 = 0;
    p->unk44 = 0;
    p->unk48 = 0;
    p->unk14 = 0x20;
    chr = GwPlayer[arg0].chr;
    dir = D_8010A8C8_parasol_plummet[chr] << 16;
    id = file.v[chr];
    while (TRUE) {
        lane = rand8() & 3;
        taken = &D_8010AC50_parasol_plummet[lane];
        if (*taken == 0.0f) {
            p->unk4C = lane;
            *taken += 1.0f;
            break;
        }
    }
    obj->model[0] = func_8000B108_main(dir | id, 0x6D9);
    omSetTra(obj, p->unk00, p->unk04, p->unk08);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 7; i++) {
        func_8000B460_main(obj, i, func_80017BB8_main(chr, mot.v[chr][i]));
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    obj->model[1] = func_8000B108_main(0x3D0006, 0x6C9);
    Hu3DModelPosSet(obj->model[1], p->unk00, p->unk04, p->unk08);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8000B460_main(obj, 8, 0x3D0000);
    func_8001C5B4_main(obj->model[1], obj->motion[8]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8000B460_main(obj, 9, 0x3D0001);
    obj->model[2] = func_8000B108_main(0x3D0007, 0x6D9);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    func_8001C258_main(obj->model[2], 4, 4);
    switch (GwPlayer[arg0].chr) {
    case 1:
        func_8001E500_main(obj->model[1], "ma01_DEF", "ru_DEF");
        break;
    case 2:
        func_8001E500_main(obj->model[1], "ma01_DEF", "pi_DEF");
        break;
    case 3:
        func_8001E500_main(obj->model[1], "ma01_DEF", "yo_DEF");
        break;
    case 4:
        func_8001E500_main(obj->model[1], "ma01_DEF", "wa_DEF");
        break;
    case 5:
        func_8001E500_main(obj->model[1], "ma01_DEF", "do_DEF");
        break;
    case 6:
        func_8001E500_main(obj->model[1], "ma01_DEF", "waru_DEF");
        break;
    case 7:
        func_8001E500_main(obj->model[1], "ma01_DEF", "di_DEF");
        break;
    }
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
}

void func_80106418_parasol_plummet(omObjData* obj) {
    Vec2f screen;
    Vec pos;
    f32 lanes[4] = { -450.0f, -150.0f, 150.0f, 450.0f };
    PaPlayer* p;
    f32 dx;
    f32 dy;
    s32 y;

    p = obj->data;
    dx = -sindf(p->unk0C) * 80.0f;
    dy = cosdf(p->unk0C) * 80.0f;
    omSetTra(obj, p->unk00 - dx, p->unk04 - dy, p->unk08);
    omSetRot(obj, 0.0f, 0.0f, p->unk0C);
    Hu3DModelPosSet(obj->model[1], p->unk00 - dx, p->unk04 - dy, p->unk08);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, p->unk0C);
    func_80106AB4_parasol_plummet(obj);
    func_80107A44_parasol_plummet(obj);
    p->unk28 = 12.0f;
    if (p->unk14 & 0x16) {
        p->unk28 = -24.0f;
    }
    if (p->unk14 & 0x10) {
        p->unk28 += p->unk2C;
        p->unk2C -= 5.0f;
        if (p->unk2C == 0.0f) {
            p->unk14 &= ~0x10;
            p->unk00 = lanes[p->unk4C];
            func_8010687C_parasol_plummet(obj);
            func_8001C258_main(obj->model[1], 4, 0);
        }
    }
    if ((p->unk14 & 0x60) == 0x40) {
        p->unk28 += p->unk30;
        p->unk30 -= 2.0f;
        p->unk0C = 0.0f;
    }
    p->unk04 += p->unk28;
    pos.x = p->unk00;
    pos.y = p->unk04;
    pos.z = p->unk08;
    Hu3DCam3DToScreen(0, &pos, &screen);
    y = screen.y;
    if (y < 0x15) {
        func_8010687C_parasol_plummet(obj);
        func_80107C94_parasol_plummet(obj);
    }
    if (y >= 0xF0) {
        p->unk04 -= -24.0f;
        if (p->unk14 & 0x40) {
            if (p->unk04 <= ((PaPlayer*)D_8010ABCC_parasol_plummet->data)->unk04) {
                p->unk14 |= 0x20;
                p->unk14 &= ~4;
                p->unk14 &= ~0x80;
                p->unk14 &= ~2;
                p->unk14 &= ~1;
                p->unk18 = 0;
                p->unk0C = 0.0f;
                func_8001C258_main(obj->model[1], 4, 4);
            }
        } else if (!(p->unk14 & 2)) {
            func_80106788_parasol_plummet(obj);
        }
    }
    func_801071B4_parasol_plummet(obj);
    func_801069E4_parasol_plummet(obj);
    func_80107B78_parasol_plummet(obj);
    func_80106CDC_parasol_plummet(obj);
    func_80106E14_parasol_plummet(obj);
    func_80106DB0_parasol_plummet(obj);
    func_80107CD4_parasol_plummet(obj);
}

void func_80106788_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    if (!(p->unk14 & 0x20)) {
        func_8001C5B4_main(obj->model[0], obj->motion[1]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[8]].unk02, 0, 0xA, 2);
        func_8001C258_main(obj->model[1], 4, 0);
        p->unk10 = 1;
        p->unk14 &= ~4;
        if (func_800E6E8C_minigame() == 2) {
            func_8004AC5C_main(0x3E1, p->unk24);
        }
    }
}

void func_8010687C_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    if (!(p->unk14 & 0x20)) {
        func_8001C5B4_main(obj->model[0], obj->motion[2]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[9]].unk02, 0, 0xA, 2);
        p->unk10 = 0;
        p->unk48 = 0.0f;
        p->unk14 = (p->unk14 | 4) & ~8;
    }
}

void func_8010693C_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    if (!(p->unk14 & 0x40)) {
        p->unk40 = 0x1E;
        p->unk14 = (p->unk14 & ~1) | 2;
        func_8010687C_parasol_plummet(obj);
        func_8001C5B4_main(obj->model[0], obj->motion[4]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8004ACE0_main(0x286, p->unk24);
        HuAudFXPlay(0x3E6);
        omVibrate(p->unk24, 2, 2, 0x14);
    }
}

void func_801069E4_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    if (p->unk14 & 2) {
        if (!(p->unk14 & 0x40)) {
            p->unk0C += 30.0f;
            if (p->unk0C >= 360.0f) {
                p->unk0C -= 360.0f;
            }
            if (--p->unk40 == 0) {
                p->unk14 = (p->unk14 | 1) & ~2;
                func_8001C5B4_main(obj->model[0], obj->motion[1]);
                func_8001C814_main(obj->model[0], 2, 2);
                p->unk0C = 0.0f;
            }
        }
    }
}


void func_80106AB4_parasol_plummet(omObjData* obj) {
    Vec2f screen;
    Vec pos;
    PaPlayer* p;
    s16 stick;
    s32 a;
    s32 x;
    f32 speed;

    p = obj->data;
    p->unk48 = 0.0f;
    if (!(p->unk14 & 1)) {
        return;
    }
    if (!(p->unk14 & 4)) {
        if (GwPlayer[p->unk24].stat & 1) {
            stick = func_801074CC_parasol_plummet(obj);
        } else {
            stick = D_800CBB6E_main[GwPlayer[p->unk24].pad];
        }
        speed = (fabs((f32)stick) - 30.0) / 5.0;
        if (stick >= 0x1E) {
            p->unk00 = speed + p->unk00;
            p->unk48 = -30.0f;
            pos.x = p->unk00;
            pos.y = p->unk04;
            pos.z = p->unk08;
            Hu3DCam3DToScreen(0, &pos, &screen);
            x = screen.x;
            if (x >= 0x100) {
                p->unk00 = p->unk00 - speed;
            }
            p->unk14 &= ~8;
        }
        if (stick < -0x1D) {
            p->unk00 = p->unk00 - speed;
            p->unk48 = 30.0f;
            pos.x = p->unk00;
            pos.y = p->unk04;
            pos.z = p->unk08;
            Hu3DCam3DToScreen(0, &pos, &screen);
            x = screen.x;
            if (x < 0x41) {
                p->unk00 = speed + p->unk00;
            }
            p->unk14 &= ~8;
        }
        a = stick;
        if (a < 0) {
            a = -a;
        }
        if (a < 0x1E && !(p->unk14 & 2)) {
            p->unk48 = 0.0f;
        }
    }
}

/* NON_MATCHING: register allocation in the pad index (masked 0). Button 0x8000 (A) toggles the parasol. */
#ifdef NON_MATCHING
void func_80106CDC_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;
    s32 btn;

    if (p->unk14 & 1) {
        if (GwPlayer[p->unk24].stat & 1) {
            btn = func_801076D4_parasol_plummet(obj) & 0x8000;
        } else {
            btn = D_800D5558_main[GwPlayer[p->unk24].pad] & 0x8000;
        }
        if (btn) {
            if (p->unk14 & 4) {
                func_80106788_parasol_plummet(obj);
            } else {
                func_8010687C_parasol_plummet(obj);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106CDC_parasol_plummet);
#endif

void func_80106DB0_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    if (p->unk0C > p->unk48) {
        p->unk0C -= 10.0f;
    }
    if (p->unk0C < p->unk48) {
        p->unk0C += 10.0f;
    }
}

void func_80106E14_parasol_plummet(omObjData* obj) {
    Vec2f screen;
    Vec pos;
    PaPlayer* p;
    PaPlayer* q;
    PaItem* item;
    s16 hit;
    f32 off;
    f32 dx;
    f32 dy;
    s32 x;

    p = obj->data;
    hit = func_80109F7C_parasol_plummet(obj, 0);
    if (p->unk14 & 2) {
        return;
    }
    if (p->unk14 & 0x100) {
        return;
    }
    if (p->unk14 & 0x20) {
        return;
    }
    if (p->unk14 & 0x80) {
        return;
    }
    if (hit != -1) {
        if (hit & 0x10) {
            q = D_8010AB60_parasol_plummet[hit & 0xF]->data;
            if (p->unk14 & 4) {
                off = 0.0f;
                while (TRUE) {
                    dx = (p->unk00 - q->unk00) + off;
                    dy = p->unk04 - q->unk04;
                    if (HuSqrtf(dx * dx + dy * dy) >= 150.0f) {
                        break;
                    }
                    pos.x = off + p->unk00;
                    pos.y = p->unk04;
                    pos.z = p->unk08;
                    Hu3DCam3DToScreen(0, &pos, &screen);
                    x = screen.x;
                    if (dx >= 0.0f) {
                        if (x > 0x100) {
                            off = (q->unk00 - p->unk00) - 1.0f;
                        } else {
                            off += 1.0f;
                        }
                    } else if (x < 0x40) {
                        off = (q->unk00 - p->unk00) + 1.0f;
                    } else {
                        off -= 1.0f;
                    }
                }
                p->unk00 = off + p->unk00;
            } else if (!(q->unk14 & 4) && !(p->unk14 & 0x80)) {
                p->unk14 = (p->unk14 | 0x80) & ~1;
                p->unk18 = 5;
                p->unk34 = 48.0f;
                dx = p->unk00 - q->unk00;
                omVibrate(p->unk24, 0xA, 0, 0xA);
                if (dx < 0.0f) {
                    p->unk34 = -p->unk34;
                }
                q->unk14 = (q->unk14 | 0x80) & ~1;
                q->unk18 = 5;
                omVibrate(q->unk24, 0xA, 0, 0xA);
                q->unk34 = -p->unk34;
            }
        } else {
            item = D_8010AB70_parasol_plummet[hit]->data;
            switch (item->unk24) {
            case 1:
                HuAudFXPlay(9);
                GwPlayer[p->unk24].gameCoin += 1;
                func_8001C258_main(D_8010AB70_parasol_plummet[hit]->model[0], 4, 4);
                func_8000D550_main(D_8010AC64_parasol_plummet, item->unk08, item->unk0C, 0.0f);
                D_8010ABB8_parasol_plummet[item->unk04] = 0;
                break;
            case 2:
                HuAudFXPlay(0x15);
                GwPlayer[p->unk24].gameCoin += 5;
                func_8001C258_main(D_8010AB70_parasol_plummet[hit]->model[0], 4, 4);
                func_8000D550_main(D_8010AC64_parasol_plummet, item->unk08, item->unk0C, 0.0f);
                D_8010ABB8_parasol_plummet[item->unk04] = 0;
                break;
            case 3:
                func_8010693C_parasol_plummet(obj);
                func_80107B5C_parasol_plummet(obj);
                break;
            }
        }
    }
}

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const f32 D_8010AAB0_parasol_plummet[] = { -260.0f, -100.0f, 100.0f, 260.0f };
const f32 D_8010AAC0_parasol_plummet[] = { -210.0f, -70.0f, 70.0f, 210.0f };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801071B4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801074CC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801076D4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801079D8_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107A44_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107B5C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107B78_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107C30_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107C94_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107CD4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107D14_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107D30_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107E6C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010803C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108178_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801082CC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801083F8_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010856C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801086F0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108878_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const s32 D_8010AAE0_parasol_plummet[] = { 0, 1, 1 };
const s32 D_8010AAEC_parasol_plummet[] = { 360, 600, 840 };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801089E0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108C1C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108DD0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108F6C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108FFC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801090A8_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801092B0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801093D4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109604_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801096BC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010995C_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const f32 D_8010AAF8_parasol_plummet[] = { 3.0f, 3.0f, 3.0f };
const u8 D_8010AB04_parasol_plummet[] = { 1, 2, 3 };
const s16 D_8010AB08_parasol_plummet[] = { 0x21, 0x26, 0x21, 0x27, 0x3D, 4 };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109B38_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109D74_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109F7C_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const s16 D_8010AB14_parasol_plummet[] = { 0x20, 0xE0, 0x20, 0xE0 };
const s16 D_8010AB1C_parasol_plummet[] = { 0x18, 0x18, 0xD8, 0xD8 };
const s32 D_8010AB24_parasol_plummet[] = { 8, 9, 10, 11, 12, 13, 14, 15 };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A160_parasol_plummet);

__asm__(".section .rodata"); // TEMP: rodata of asm functions
const s16 D_8010AB44_parasol_plummet[] = { 0x20, 0xEC, 0x20, 0xEC };

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A484_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A75C_parasol_plummet);
