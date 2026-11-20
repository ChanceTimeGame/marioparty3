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

/* omObjData::data of the goal (D_8010ABCC_parasol_plummet, 0x14) */
typedef struct PaGoal {
    /* 0x00 */ f32 unk00; /* position */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C; /* angle */
    /* 0x10 */ s32 unk10; /* motion: 1 circling, 2 rising, 4 bobbing */
} PaGoal; // Size 0x14

/* omObjData::data of the timer (D_8010AC6C_parasol_plummet, 0x14) */
typedef struct PaTimer {
    /* 0x00 */ f32 unk00[2]; /* sprite y */
    /* 0x08 */ s16 unk08; /* sprite file */
    /* 0x0A */ s16 unk0A[2]; /* sprites */
    /* 0x0E */ char unk0E[6];
} PaTimer; // Size 0x14

/* omObjData::data of a rising bubble (func_801086F0_parasol_plummet, 0x1C) */
typedef struct PaBubble {
    /* 0x00 */ f32 unk00; /* screen position */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08; /* rise speed */
    /* 0x0C */ f32 unk0C; /* scale */
    /* 0x10 */ f32 unk10; /* scale wobble */
    /* 0x14 */ f32 unk14; /* wobble phase */
    /* 0x18 */ s32 unk18; /* sprite slot */
} PaBubble; // Size 0x1C

/* omObjData::data of the scrolling cliff walls (func_801089E0_parasol_plummet, 0x40) */
typedef struct PaWall {
    /* 0x00 */ f32 unk00[6]; /* sprite x */
    /* 0x18 */ f32 unk18[6]; /* sprite y */
    /* 0x30 */ char unk30[2];
    /* 0x32 */ s16 unk32[6]; /* sprites */
    /* 0x3E */ char unk3E[2];
} PaWall; // Size 0x40

/* omObjData::data of a Lakitu-style thrower on the cliff (D_8010AC80_parasol_plummet, 0x24) */
typedef struct PaFoe {
    /* 0x00 */ f32 unk00; /* screen position */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ char unk08[0x10];
    /* 0x18 */ s32 unk18; /* slot */
    /* 0x1C */ f32 unk1C; /* facing (rot y) */
    /* 0x20 */ u16 unk20; /* 1 active, 2 throwing */
    /* 0x22 */ s16 unk22;
} PaFoe; // Size 0x24

/* omObjData::data of an item (D_8010AB70_parasol_plummet) */
typedef struct PaItem {
    /* 0x00 */ f32 unk00; /* rotation speed */
    /* 0x04 */ s32 unk04; /* slot in D_8010ABB8_parasol_plummet */
    /* 0x08 */ f32 unk08; /* position */
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10; /* drift speed */
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18; /* rotation */
    /* 0x1C */ u16 unk1C; /* 1 live */
    /* 0x1E */ char unk1E[2];
    /* 0x20 */ f32 unk20; /* scale */
    /* 0x24 */ u8 unk24; /* 1 coin, 2 five coins, 3 hazard */
    /* 0x25 */ char unk25[3];
} PaItem; // Size 0x28

/* Main sprite-model slot (D_800CBB60_main; 14EA0.c's unk_800ECDE0, copied here as it is not in a header). */
typedef struct PaSprModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ s8 unk16;
    /* 0x17 */ s8 unk17;
    /* 0x18 */ s8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8* unk20; /* key-frame list */
} PaSprModel; /* size = 0x24 */

typedef struct PaS16x4 {
    s16 v[4];
} PaS16x4;

typedef struct PaS32x3 {
    s32 v[3];
} PaS32x3;

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
void func_8000BC48_main(u16, u16);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_80012D0C_main(s16 camIndex, f32 dist, Vec2f* in, Vec2f* out);
void func_8001C6A8_main(s32 arg0, f32 arg1);
void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);

extern s8 D_800CBB6E_main[]; /* stick x */
extern u16 D_800D530C_main;
extern PaSprModel* D_800CBB60_main;
u16 func_80014618_main(s16 index, u16 arg1);
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
f32 func_801079D8_parasol_plummet(omObjData* obj, s32 item);
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
void func_80107E6C_parasol_plummet(omObjData* obj);
void func_8010803C_parasol_plummet(void);
void func_80108178_parasol_plummet(omObjData* obj);
void func_801082CC_parasol_plummet(omObjData* obj);
void func_801083F8_parasol_plummet(void);
void func_8010856C_parasol_plummet(void);
void func_80108C1C_parasol_plummet(omObjData* obj);
void func_80108DD0_parasol_plummet(void);
void func_801086F0_parasol_plummet(s32 arg0);
void func_80108878_parasol_plummet(omObjData* obj);
void func_801089E0_parasol_plummet(omObjData* obj);
void func_80108F6C_parasol_plummet(void);
void func_80108FFC_parasol_plummet(void);
void func_801090A8_parasol_plummet(s32 arg0);
void func_801092B0_parasol_plummet(s32 arg0);
void func_801093D4_parasol_plummet(omObjData* obj);
void func_80109604_parasol_plummet(void);
s16 func_80109F7C_parasol_plummet(omObjData* obj, s32 arg1);
void func_801096BC_parasol_plummet(void);
void func_8010995C_parasol_plummet(s32 arg0);
void func_80109B38_parasol_plummet(s32 arg0);
void func_80109D74_parasol_plummet(omObjData* obj);
void func_8010A160_parasol_plummet(void);
void func_8010A484_parasol_plummet(void);
void func_8010A75C_parasol_plummet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z);

extern s32 D_8010AB50_parasol_plummet; /* camera */
extern u8 D_8010AB54_parasol_plummet; /* 1 = a thrower released its throw */
extern f32 D_8010AB58_parasol_plummet; /* throw height */
extern omObjData* D_8010AB60_parasol_plummet[4]; /* players */
extern omObjData* D_8010AB70_parasol_plummet[18]; /* items */
extern u8 D_8010ABB8_parasol_plummet[20]; /* item slots in use */
extern omObjData* D_8010ABCC_parasol_plummet;
extern u16 D_8010ABD0_parasol_plummet;
extern s16 D_8010ABD8_parasol_plummet[58]; /* item bag: 1 coin, 2 five coins, 3 hazard, -1 drawn */
extern f32 D_8010AC50_parasol_plummet[4]; /* lanes taken */
extern s16 D_8010AC64_parasol_plummet;
extern s32 D_8010AC60_parasol_plummet; /* thrower that threw */
extern f32 D_8010AC68_parasol_plummet; /* time */
extern omObjData* D_8010AC6C_parasol_plummet; /* timer */
extern f32 D_8010AC70_parasol_plummet; /* wall scroll speed */
extern u8 D_8010AC74_parasol_plummet;
extern u8 D_8010AC75_parasol_plummet[5]; /* thrower slots in use */
extern omObjData* D_8010AC80_parasol_plummet[5]; /* throwers */
extern f32 D_8010AC94_parasol_plummet; /* next thrower height */
extern f32 D_8010AC98_parasol_plummet;
extern s32 D_8010AC9C_parasol_plummet; /* next thrower side */
extern s16 D_8010ACA0_parasol_plummet[3]; /* item sprite models by kind */
extern s16 D_8010ACA8_parasol_plummet[12]; /* coin digit sprites, 3 per player */
extern s16 D_8010ACC0_parasol_plummet; /* digit sprite file */
extern s16 D_8010ACC2_parasol_plummet[4]; /* character icon files */
extern s16 D_8010ACCA_parasol_plummet[4]; /* character icon sprites */
extern s16 D_8010ACD2_parasol_plummet; /* coin icon file */
extern s16 D_8010ACD4_parasol_plummet[4]; /* coin icon sprites */
extern s16 D_8010ACDC_parasol_plummet; /* "x" file */
extern s16 D_8010ACDE_parasol_plummet[4]; /* "x" sprites */
extern s16 D_8010ACF0_parasol_plummet[5]; /* bubble sprites */
extern s16 D_8010ACFA_parasol_plummet; /* bubble sprite file */
extern u8 D_8010ACFC_parasol_plummet[5]; /* bubble slots in use */
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
            if (p->unk04 <= ((PaGoal*)D_8010ABCC_parasol_plummet->data)->unk04) {
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
// decomp-permuter
void func_80106CDC_parasol_plummet(omObjData *obj)
{
  PaPlayer *p = obj->data;
  int new_var;
  s32 btn;
  if (p->unk14 & 1)
  {
    if (GwPlayer[p->unk24].stat & 1)
    {
      btn = func_801076D4_parasol_plummet(obj) & 0x8000;
    }
    else
    {
      new_var = 0x8000;
      btn = D_800D5558_main[GwPlayer[p->unk24].pad] & new_var;
    }
    if (btn)
    {
      if (p->unk14 & 4)
      {
        func_80106788_parasol_plummet(obj);
      }
      else
      {
        func_8010687C_parasol_plummet(obj);
      }
    }
  }
}

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

void func_801071B4_parasol_plummet(omObjData* obj) {
    f32 offIn[4] = { -260.0f, -100.0f, 100.0f, 260.0f };
    f32 offOut[4] = { -210.0f, -70.0f, 70.0f, 210.0f };
    PaS32x8 unused = D_8010A928_parasol_plummet;
    PaPlayer* p;
    PaGoal* goal;
    s32 dir;

    p = obj->data;
    goal = D_8010ABCC_parasol_plummet->data;
    if (p->unk14 & 0x20) {
        if (D_8010AC66_parasol_plummet == 0) {
            p->unk00 = goal->unk00 + offIn[p->unk4C];
            p->unk04 = goal->unk04 + 300.0f;
            p->unk08 = goal->unk08 + 200.0f;
            if (fabs(p->unk00) <= 500.0 && fabs(p->unk08) <= 100.0) {
                p->unk08 = 0.0f;
                p->unk14 = (p->unk14 | 0x10) & ~0x20;
                p->unk2C = 130.0f;
                func_8001C5B4_main(obj->model[0], obj->motion[3]);
                func_8001C258_main(obj->model[4], 4, 0);
                Hu3DModelPosSet(obj->model[4], obj->trans.x, obj->trans.y, obj->trans.z);
            }
        } else {
            if (p->unk18 == 0) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C814_main(obj->model[0], 2, 2);
            }
            if (p->unk18 == 0x78) {
                dir = D_8010A8C8_parasol_plummet[GwPlayer[p->unk24].chr] << 16;
                if (GwPlayer[p->unk24].gameCoin != 0) {
                    func_8001C5B4_main(obj->model[0], obj->motion[5]);
                    func_80045ED0_main(dir | 0x2F);
                } else {
                    func_8001C5B4_main(obj->model[0], obj->motion[6]);
                }
            }
            p->unk00 = goal->unk00 + offOut[p->unk4C];
            p->unk04 = goal->unk04 + 300.0f;
            p->unk08 = goal->unk08 + 200.0f;
            p->unk18++;
        }
    }
}

/* NON_MATCHING: retail compiles the CPU difficulty switch as two separate rand8 tests (0..2 and 3; GCC merges
   these equivalent arms) and allocates s3/s4 the other way round. CPU steering: aim at the nearest item ahead. */
#ifdef NON_MATCHING
s16 func_801074CC_parasol_plummet(omObjData* obj) {
    f32 dist[18];
    s32 idx[18];
    PaPlayer* p;
    PaItem* item;
    s32 stick;
    s32 n;
    s32 i;
    s32 j;
    f32 d;

    stick = 0;
    n = 0;
    for (i = 0; i < 18; i++) {
        d = func_801079D8_parasol_plummet(obj, i);
        if (d != -1.0f) {
            dist[n] = d;
            idx[n] = i;
            n++;
        }
    }
    if (n == 0) {
        return 0;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n; j++) {
            if (dist[i] < dist[j]) {
                f32 tf = dist[i];
                s32 ti;

                dist[i] = dist[j];
                dist[j] = tf;
                ti = idx[i];
                idx[i] = idx[j];
                idx[j] = ti;
            }
        }
    }
    p = obj->data;
    switch (GwPlayer[p->unk24].cpu_difficulty) {
    case 0:
    case 1:
    case 2:
        if (rand8() == 0) {
            return 0;
        }
        break;
    case 3:
        if (rand8() == 0) {
            return 0;
        }
        break;
    default:
        return stick;
    }
    item = D_8010AB70_parasol_plummet[idx[0]]->data;
    if (p->unk00 < item->unk08) {
        stick = 0x46;
    }
    if (item->unk08 < p->unk00) {
        stick = -0x46;
    }
    return stick;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801074CC_parasol_plummet);
#endif

/* NON_MATCHING: register allocation in the sort (f0/f2 swapped; masked 0). CPU parasol button: open or close to
   meet the nearest item's height, then wait a difficulty-dependent time. Retail reads idx[0] even when no item is
   live (n == 0): an uninitialised index into D_8010AB70_parasol_plummet. */
#ifdef NON_MATCHING
u16 func_801076D4_parasol_plummet(omObjData* obj) {
    f32 dist[18];
    s32 idx[18];
    PaPlayer* p;
    PaItem* item;
    s32 btn;
    s32 n;
    s32 i;
    s32 j;
    f32 d;
    f32 a;
    f32 b;

    p = obj->data;
    btn = 0;
    if (p->unk38 > 0) {
        p->unk38--;
    }
    if (p->unk38 == 0) {
        n = 0;
        for (i = 0; i < 18; i++) {
            d = func_801079D8_parasol_plummet(obj, i);
            if (d != -1.0f) {
                dist[n] = d;
                idx[n] = i;
                n++;
            }
        }
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n; j++) {
                if (dist[i] < dist[j]) {
                    f32 tf = dist[i];
                    s32 ti;

                    dist[i] = dist[j];
                    dist[j] = tf;
                    ti = idx[i];
                    idx[i] = idx[j];
                    idx[j] = ti;
                }
            }
        }
        p = obj->data;
        switch (GwPlayer[p->unk24].cpu_difficulty) {
        case 0:
            break;
        case 1:
            item = D_8010AB70_parasol_plummet[idx[0]]->data;
            if (p->unk04 > item->unk0C && !(p->unk14 & 4)) {
                btn = 0x8000;
            }
            if (p->unk04 < item->unk0C && (p->unk14 & 4)) {
                btn = 0x8000;
            }
            p->unk38 = (rand8() & 0x1F) + 0x20;
            break;
        case 2:
            item = D_8010AB70_parasol_plummet[idx[0]]->data;
            if (p->unk04 > item->unk0C && !(p->unk14 & 4)) {
                btn = 0x8000;
            }
            if (p->unk04 < item->unk0C && (p->unk14 & 4)) {
                btn = 0x8000;
            }
            p->unk38 = (rand8() & 0xF) + 0x10;
            break;
        case 3:
            item = D_8010AB70_parasol_plummet[idx[0]]->data;
            if (p->unk04 > item->unk0C && !(p->unk14 & 4)) {
                btn = 0x8000;
            }
            if (p->unk04 < item->unk0C && (p->unk14 & 4)) {
                btn = 0x8000;
            }
            p->unk38 = (rand8() & 7) + 8;
            break;
        }
        return btn;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801076D4_parasol_plummet);
#endif

f32 func_801079D8_parasol_plummet(omObjData* obj, s32 arg1) {
    PaPlayer* p;
    PaItem* item;
    f32 dist = -1.0f;
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;

    p = obj->data;
    x = p->unk00;
    y = p->unk04;
    if (D_8010ABB8_parasol_plummet[arg1] != 0) {
        item = D_8010AB70_parasol_plummet[arg1]->data;
        dx = item->unk08;
        dy = item->unk0C;
        dx -= x;
        dx *= dx;
        dy -= y;
        dy *= dy;
        dist = HuSqrtf(dx + dy);
    }
    return dist;
}

void func_80107A44_parasol_plummet(omObjData* obj) {
    Vec2f screen;
    Vec pos;
    PaPlayer* p;
    s32 x;

    p = obj->data;
    if (p->unk14 & 0x80) {
        p->unk00 += p->unk34;
        pos.x = p->unk00;
        pos.y = p->unk04;
        pos.z = p->unk08;
        Hu3DCam3DToScreen(0, &pos, &screen);
        x = screen.x;
        if (x >= 0x100) {
            p->unk00 -= p->unk34;
        }
        if (x < 0x41) {
            p->unk00 -= p->unk34;
        }
        p->unk18--;
        if (p->unk34 >= 0.0f) {
            p->unk34 -= 8.0f;
        } else {
            p->unk34 += 8.0f;
        }
        if (p->unk18 == 0) {
            p->unk14 = (p->unk14 & ~0x80) | 1;
            p->unk34 = 0.0f;
        }
    }
}

void func_80107B5C_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    p->unk14 |= 0x100;
    p->unk3C = 0x2D;
}

void func_80107B78_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    if (p->unk14 & 0x100) {
        if (!(p->unk14 & 0x40)) {
            if (--p->unk3C == 0) {
                func_80107C30_parasol_plummet(obj);
            }
            if (p->unk3C & 1) {
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 4);
            } else {
                func_8001C258_main(obj->model[0], 4, 0);
                func_8001C258_main(obj->model[1], 4, 0);
            }
        }
    }
}

void func_80107C30_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    func_8001C258_main(obj->model[0], 4, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    p->unk14 &= ~0x100;
}

void func_80107C94_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    if (!(p->unk14 & 2)) {
        if (!(p->unk14 & 0x200)) {
            if (p->unk14 & 1) {
                p->unk14 = (p->unk14 | 0x200) & ~1;
                p->unk44 = 0xA;
            }
        }
    }
}

void func_80107CD4_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    if (p->unk14 & 0x200) {
        if (--p->unk44 <= 0) {
            func_80107D14_parasol_plummet(obj);
        }
    }
}

void func_80107D14_parasol_plummet(omObjData* obj) {
    PaPlayer* p = obj->data;

    p->unk14 = (p->unk14 & ~0x200) | 1;
}

void func_80107D30_parasol_plummet(void) {
    omObjData* obj;
    PaGoal* g;

    omAddPrcObj(func_8010803C_parasol_plummet, 0x50, 0x2000, 0);
    obj = omAddObj(0x50, 1, 2, -1, func_80107E6C_parasol_plummet);
    obj->data = HuMemAllocTag(sizeof(PaGoal), 0x7918);
    D_8010ABCC_parasol_plummet = obj;
    g = obj->data;
    obj->model[0] = func_8000B108_main(0xA011A, 0x6D9);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    g->unk0C = 90.0f;
    g->unk00 = sindf(g->unk0C) * 3000.0f + 3000.0f;
    g->unk04 = cosdf(g->unk0C) * 2000.0f;
    g->unk08 = cosdf(g->unk0C) * 3000.0f;
    g->unk10 = 1;
}

void func_80107E6C_parasol_plummet(omObjData* obj) {
    PaGoal* g = obj->data;

    omSetTra(obj, g->unk00, g->unk04, g->unk08);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    if (g->unk10 & 1) {
        g->unk00 = sindf(g->unk0C) * 3000.0f + 3000.0f;
        g->unk04 = cosdf(g->unk0C) * 1000.0f - 500.0f;
        g->unk08 = cosdf(g->unk0C) * 3000.0f;
        g->unk0C += 2.5f;
        if (g->unk0C >= 360.0f) {
            g->unk0C -= 360.0f;
        }
    }
    if (g->unk10 & 2) {
        g->unk04 = sindf(g->unk0C) * 1000.0f + -300.0f;
        g->unk08 += 8.0f;
    }
    if (g->unk10 & 4) {
        g->unk04 = sindf(g->unk0C) * 100.0f + -300.0f;
        g->unk0C += 3.0f;
        if (g->unk0C >= 360.0f) {
            g->unk0C -= 360.0f;
        }
    }
}

void func_8010803C_parasol_plummet(void) {
    omObjData* obj = D_8010ABCC_parasol_plummet;
    PaGoal* g = obj->data;
    s32 i;

    g->unk10 |= 1;
    HuPrcSleep(0x78);
    func_8001C814_main(obj->model[0], 4, 4);
    g->unk10 &= ~1;
    while (D_8010AC66_parasol_plummet != 3) {
        HuPrcVSleep();
    }
    func_8001C814_main(obj->model[0], 4, 0);
    g->unk00 = 0.0f;
    g->unk04 = -2000.0f;
    g->unk08 = 0.0f;
    g->unk0C = 0.0f;
    g->unk10 |= 2;
    g->unk0C = 270.0f;
    for (i = 0; i < 0x5A; i++) {
        g->unk0C += 1.0f;
        HuPrcVSleep();
    }
    g->unk10 = (g->unk10 & ~2) | 4;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80108178_parasol_plummet(omObjData* obj) {
    PaTimer* t;
    s32 i;

    obj->data = HuMemAllocTag(sizeof(PaTimer), 0x7918);
    D_8010AC6C_parasol_plummet = obj;
    t = obj->data;
    t->unk00[0] = 120.0f;
    t->unk00[1] = 359.0f;
    t->unk08 = func_8000B838_main(0x3D0002);
    for (i = 0; i < 2; i++) {
        t->unk0A[i] = InitEspriteSlot(t->unk08, 0, 1);
        func_8000BC48_main(t->unk0A[i], 0x4008);
        func_8000BBD4_main(t->unk0A[i], 0xA0, t->unk00[i]);
        func_8000BB54_main(t->unk0A[i]);
        func_8000BE5C_main(t->unk0A[i], 1.0f, 1.0f);
        func_8000BCC8_main(t->unk0A[i], 0xFF);
    }
    D_8010AC68_parasol_plummet = 0;
    omAddPrcObj(func_801083F8_parasol_plummet, 0x50, 0x2000, 0);
    obj->func = func_801082CC_parasol_plummet;
}

void func_801082CC_parasol_plummet(omObjData* obj) {
    PaTimer* t = obj->data;
    s32 i;
    s32 y;

    for (i = 0; i < 2; i++) {
        y = t->unk00[i];
        func_8000BBD4_main(t->unk0A[i], 0xA0, y);
        t->unk00[i] += D_8010AC68_parasol_plummet;
        if (D_8010AC68_parasol_plummet < 0.0f && t->unk00[i] <= -120.0f) {
            t->unk00[i] += 478.0f;
        }
        if (D_8010AC68_parasol_plummet > 0.0f && t->unk00[i] >= 360.0f) {
            t->unk00[i] -= 478.0f;
        }
    }
}

void func_801083F8_parasol_plummet(void) {
    s32 i;

    D_8010AC68_parasol_plummet = 0.0f;
    HuPrcSleep(0x5A);
    for (i = 0; i < 0xB; i++) {
        D_8010AC68_parasol_plummet = (i * -5.0f) / 10.0f;
        HuPrcVSleep();
    }
    while (D_8010AC66_parasol_plummet != 3) {
        HuPrcVSleep();
    }
    for (i = 0; i < 0x1F; i++) {
        D_8010AC68_parasol_plummet = ((30.0f - i) * -5.0f) / 30.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(0xF);
    D_8010AC68_parasol_plummet = -2.5f;
    HuPrcSleep(0x32);
    D_8010AC68_parasol_plummet = 0.0f;
    HuPrcSleep(0x1E);
    for (i = 0; i < 0xB; i++) {
        D_8010AC68_parasol_plummet = (i * 5.0f) / 10.0f;
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010856C_parasol_plummet(void) {
    s32 i;

    D_8010ACFA_parasol_plummet = func_8000B838_main(0x210028);
    for (i = 0; i < 5; i++) {
        D_8010ACFC_parasol_plummet[i] = 0;
        D_8010ACF0_parasol_plummet[i] = InitEspriteSlot(D_8010ACFA_parasol_plummet, 0, 1);
        func_8000BC48_main(D_8010ACF0_parasol_plummet[i], 0x4008);
        func_8000BB94_main(D_8010ACF0_parasol_plummet[i]);
        func_8000BE5C_main(D_8010ACF0_parasol_plummet[i], 1.0f, 1.0f);
        func_8000BBD4_main(D_8010ACF0_parasol_plummet[i], 0xA0, 0x12C);
        func_8000BCC8_main(D_8010ACF0_parasol_plummet[i], 0x32);
    }
    while (TRUE) {
        if ((u8)(rand8() % 50) == 0 && D_8010AC68_parasol_plummet == -5.0f) {
            for (i = 0; i < 5; i++) {
                if (D_8010ACFC_parasol_plummet[i] == 0) {
                    func_801086F0_parasol_plummet(i);
                    break;
                }
            }
        }
        HuPrcVSleep();
    }
}

void func_801086F0_parasol_plummet(s32 arg0) {
    omObjData* obj;
    PaBubble* b;
    s32 x;
    s32 y;

    obj = omAddObj(0xA, 0, 0, -1, func_80108878_parasol_plummet);
    b = HuMemAllocTag(sizeof(PaBubble), 0x7918);
    obj->data = b;
    rand8();
    b->unk08 = -6.0f;
    b->unk00 = ((rand8() * 2) % 240) + 0x28;
    b->unk04 = 280.0f;
    b->unk18 = arg0;
    b->unk14 = 0.0f;
    rand8();
    b->unk0C = 1.0f;
    b->unk10 = ((rand8() & 1) + 1) / 10.0f;
    x = b->unk00;
    y = b->unk04;
    func_8000BBD4_main(D_8010ACF0_parasol_plummet[b->unk18], x, y);
    func_8000BB54_main(D_8010ACF0_parasol_plummet[arg0]);
    D_8010ACFC_parasol_plummet[arg0] = 1;
}

void func_80108878_parasol_plummet(omObjData* obj) {
    PaBubble* b = obj->data;
    f32 scale;
    s32 x;
    s32 y;

    x = b->unk00;
    y = b->unk04;
    func_8000BBD4_main(D_8010ACF0_parasol_plummet[b->unk18], x, y);
    b->unk04 = (-5.0f - D_8010AC68_parasol_plummet) + b->unk08 + b->unk04;
    b->unk14 += 10.0f;
    if (b->unk14 >= 360.0f) {
        b->unk14 -= 360.0f;
    }
    scale = sindf(b->unk14) * b->unk10 + b->unk0C;
    func_8000BE5C_main(D_8010ACF0_parasol_plummet[b->unk18], scale, scale);
    if (b->unk04 <= -40.0f) {
        func_8000BB94_main(D_8010ACF0_parasol_plummet[b->unk18]);
        D_8010ACFC_parasol_plummet[b->unk18] = 0;
        omDelObj(obj);
    }
}

const PaS32x3 D_8010AAE0_parasol_plummet = { { 0, 1, 1 } };
const PaS32x3 D_8010AAEC_parasol_plummet = { { 360, 600, 840 } };

/* NON_MATCHING: register allocation (s2/s3 swapped; masked 0). The scrolling cliff walls. */
// decomp-permuter
void func_801089E0_parasol_plummet(omObjData *obj)
{
  PaS32x3 kind = D_8010AAE0_parasol_plummet;
  s32 x;
  s32 xs[2] = {0x18, 0x128};
  PaS32x3 ys = D_8010AAEC_parasol_plummet;
  s32 file[2];
  s32 y;
  s32 i;
  PaWall *w;
  obj->data = HuMemAllocTag(sizeof(PaWall), 0x7918);
  w = obj->data;
  file[0] = func_8000B838_main(0x3D0005);
  file[1] = func_8000B838_main(0x3D0003);
  for (i = 0; i < 6; i++)
  {
    w->unk32[i] = (x = InitEspriteSlot(file[kind.v[i % 3]], 0, 1));
    w->unk00[i] = xs[i / 3];
    w->unk18[i] = ys.v[i % 3];
    x = w->unk00[i];
    y = w->unk18[i];
    func_8000BC48_main(w->unk32[i], 0x4008);
    if (i >= 3)
    {
      func_8000BC48_main(w->unk32[i], 1);
    }
    func_8000BBD4_main(w->unk32[i], x, y);
    func_8000BB54_main(w->unk32[i]);
    func_8000BE5C_main(w->unk32[i], 1.0f, 1.0f);
    func_8000BCC8_main(w->unk32[i], 0x1E);
  }

  func_8000BC88_main(w->unk32[3], 0x4000);
  D_8010AC74_parasol_plummet = 0;
  D_8010AC70_parasol_plummet = 0.0f;
  omAddPrcObj(func_80108DD0_parasol_plummet, 0x50, 0x2000, 0);
  obj->func = func_80108C1C_parasol_plummet;
}

void func_80108C1C_parasol_plummet(omObjData* obj) {
    PaWall* w = obj->data;
    s32 i;
    s32 x;
    s32 y;

    for (i = 0; i < 6; i++) {
        x = w->unk00[i];
        y = w->unk18[i];
        func_8000BBD4_main(w->unk32[i], x, y);
        w->unk18[i] += D_8010AC70_parasol_plummet;
        if (D_8010AC70_parasol_plummet < 0.0f && w->unk18[i] <= -120.0f) {
            if (i % 3 == 0) {
                func_8000BB94_main(w->unk32[i]);
            }
            w->unk18[i] += 480.0f;
        }
        if (D_8010AC70_parasol_plummet > 0.0f && w->unk18[i] >= 360.0f) {
            w->unk18[i] -= 480.0f;
        }
    }
    if (((PaGoal*)D_8010ABCC_parasol_plummet->data)->unk08 >= 0.0f) {
        func_8000BC48_main(w->unk32[3], 0x4000);
    }
}

void func_80108DD0_parasol_plummet(void) {
    s32 i;

    D_8010AC70_parasol_plummet = 0.0f;
    HuPrcSleep(0x1E);
    D_8010AC70_parasol_plummet = -4.0f;
    HuPrcSleep(0x1E);
    D_8010AC70_parasol_plummet = 0.0f;
    HuPrcSleep(0x1E);
    for (i = 0; i < 0xA; i++) {
        D_8010AC70_parasol_plummet = (i * -8.0f) / 10.0f;
        HuPrcVSleep();
    }
    while (D_8010AC66_parasol_plummet != 3) {
        HuPrcVSleep();
    }
    for (i = 0; i < 0x1F; i++) {
        D_8010AC70_parasol_plummet = ((30.0f - i) * -8.0f) / 30.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(0xF);
    D_8010AC70_parasol_plummet = -4.0f;
    HuPrcSleep(0x32);
    D_8010AC70_parasol_plummet = 0.0f;
    HuPrcSleep(0x1E);
    for (i = 0; i < 0xB; i++) {
        D_8010AC70_parasol_plummet = (i * 8.0f) / 10.0f;
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80108F6C_parasol_plummet(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        D_8010AC75_parasol_plummet[i] = 0;
        func_801092B0_parasol_plummet(i);
    }
    D_8010AC94_parasol_plummet = 341.0f;
    D_8010AC98_parasol_plummet = 6.0f;
    omAddPrcObj(func_80108FFC_parasol_plummet, 0x50, 0x2000, 0);
    D_8010AC9C_parasol_plummet = rand8() & 1;
}

void func_80108FFC_parasol_plummet(void) {
    s32 i;
    s32 j;

    HuPrcSleep(0x10E);
    for (i = 0; i < 0x1D; i++) {
        for (j = 0; j < 5; j++) {
            if (D_8010AC75_parasol_plummet[j] == 0) {
                func_801090A8_parasol_plummet(j);
                break;
            }
        }
        HuPrcSleep(0x1E);
    }
    while (D_8010AC66_parasol_plummet != 4) {
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_801090A8_parasol_plummet(s32 arg0) {
    Vec2f screen;
    Vec pos;
    f32 x;
    f32 y;
    omObjData* obj;
    PaFoe* f;

    obj = D_8010AC80_parasol_plummet[arg0];
    f = obj->data;
    if (D_8010AC9C_parasol_plummet != 0) {
        f->unk1C = 90.0f;
        f->unk00 = 30.0f;
    } else {
        f->unk1C = 270.0f;
        f->unk00 = 290.0f;
    }
    D_8010AC9C_parasol_plummet = (D_8010AC9C_parasol_plummet + 1) & 1;
    f->unk04 = D_8010AC94_parasol_plummet;
    D_8010AC94_parasol_plummet -= 43.2f;
    if (D_8010AC94_parasol_plummet <= 281.0f) {
        D_8010AC94_parasol_plummet += 60.0f;
    }
    screen.x = f->unk00;
    screen.y = f->unk04;
    func_80012D0C_main(0, CZoom, &screen, (Vec2f*)&pos);
    x = pos.x;
    y = pos.y;
    f->unk20 |= 1;
    func_8001C258_main(obj->model[0], 4, 0);
    D_8010AC75_parasol_plummet[arg0] = 1;
    f->unk18 = arg0;
    f->unk22 = D_8010AC98_parasol_plummet;
    D_8010AC98_parasol_plummet -= 1.0f;
    if (D_8010AC98_parasol_plummet <= 0.0f) {
        D_8010AC98_parasol_plummet = 5.0f;
    }
    omSetTra(obj, x, y, 0.0f);
    omSetRot(obj, 0.0f, f->unk1C, 0.0f);
}

void func_801092B0_parasol_plummet(s32 arg0) {
    omObjData* obj;
    PaFoe* f;

    obj = omAddObj(0xA, 1, 2, -1, func_801093D4_parasol_plummet);
    f = HuMemAllocTag(sizeof(PaFoe), 0x7918);
    obj->data = f;
    obj->model[0] = func_8000B108_main(0xA0117, 0x6DD);
    func_8000B460_main(obj, 0, 0xA0118);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    func_8000B460_main(obj, 1, 0xA0119);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    D_8010AC80_parasol_plummet[arg0] = obj;
    f->unk20 = 0;
    f->unk18 = arg0;
}

void func_801093D4_parasol_plummet(omObjData* obj) {
    Vec2f screen;
    Vec pos;
    f32 x;
    f32 y;
    PaFoe* f;
    f32 frame;

    if (D_8010AC66_parasol_plummet == 4) {
        omDelObj(obj);
        return;
    }
    f = obj->data;
    if (f->unk20 != 0) {
        screen.x = f->unk00;
        screen.y = f->unk04;
        func_80012D0C_main(0, CZoom, &screen, (Vec2f*)&pos);
        x = pos.x;
        y = pos.y;
        if (f->unk20 & 2) {
            D_8010AB58_parasol_plummet = y + 70.0f;
        }
        omSetTra(obj, x, y, 0.0f);
        f->unk04 += D_8010AC70_parasol_plummet;
        f->unk22--;
        if (f->unk04 <= 250.0f) {
            if (!(f->unk20 & 2)) {
                func_8001C5B4_main(obj->model[0], obj->motion[1]);
                func_8001C6A8_main(obj->model[0], 30.0f);
                f->unk20 |= 2;
            }
        }
        if (f->unk20 & 2) {
            frame = HmfModelData[obj->model[0]].unk40;
            if ((frame >= 37.0f) & (frame < 39.0f)) {
                D_8010AB54_parasol_plummet |= 1;
                D_8010AC60_parasol_plummet = f->unk18;
            }
        }
        if (f->unk04 <= 20.0f) {
            func_8001C258_main(obj->model[0], 4, 4);
            D_8010AC75_parasol_plummet[f->unk18] = 0;
            f->unk20 = 0;
        }
    }
}

void func_80109604_parasol_plummet(void) {
    s32 i;

    for (i = 0; i < 18; i++) {
        D_8010ABB8_parasol_plummet[i] = 0;
        func_80109B38_parasol_plummet(i);
    }
    omAddPrcObj(func_801096BC_parasol_plummet, 0x50, 0x2000, 0);
    for (i = 0; i < 58; i++) {
        if (i < 8) {
            D_8010ABD8_parasol_plummet[i] = 3;
        } else if (i < 53) {
            D_8010ABD8_parasol_plummet[i] = 1;
        } else {
            D_8010ABD8_parasol_plummet[i] = 2;
        }
    }
}

/* NON_MATCHING: register allocation and block order (masked 40, one instruction short). After a thrower throws,
   draw two items from the bag (at most one five-coin bag and one hazard per throw) into free item slots
   (0-5 coins, 6-11 five coins, 12-17 hazards); give up after 1000 tries. */
#ifdef NON_MATCHING
void func_801096BC_parasol_plummet(void) {
    s32 got[2];
    s32 n;
    s32 done;
    s32 tries;
    s32 r;
    s32 j;

    while (D_8010AC66_parasol_plummet != 4) {
        if (D_8010AB54_parasol_plummet & 1) {
            for (n = 0; n < 2; n++) {
                done = 0;
                tries = 0;
                do {
                    r = (u8)(rand8() % 58);
                    switch (D_8010ABD8_parasol_plummet[r]) {
                    case 1:
                        for (j = 0; j < 6; j++) {
                            if (D_8010ABB8_parasol_plummet[j] == 0) {
                                goto spawn;
                            }
                        }
                        break;
                    case 2:
                        for (j = 0; j < n; j++) {
                            if (got[j] == 2) {
                                break;
                            }
                        }
                        if (j == n) {
                            for (j = 6; j < 12; j++) {
                                if (D_8010ABB8_parasol_plummet[j] == 0) {
                                    goto spawn;
                                }
                            }
                        }
                        break;
                    spawn:
                        done++;
                        func_8010995C_parasol_plummet(j);
                        got[n] = D_8010ABD8_parasol_plummet[r];
                        D_8010ABD8_parasol_plummet[r] = -1;
                        break;
                    case 3:
                        for (j = 0; j < n; j++) {
                            if (got[j] == 3) {
                                break;
                            }
                        }
                        if (j == n) {
                            for (j = 12; j < 18; j++) {
                                if (D_8010ABB8_parasol_plummet[j] == 0) {
                                    goto spawn;
                                }
                            }
                        }
                        break;
                    }
                    tries++;
                    done += (tries == 1000);
                } while (done == 0);
                HuPrcSleep(3);
            }
            D_8010AB54_parasol_plummet &= ~1;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801096BC_parasol_plummet);
#endif

void func_8010995C_parasol_plummet(s32 arg0) {
    Vec2f screen;
    Vec pos;
    omObjData* obj;
    PaItem* item;
    PaFoe* f;
    f32 x;
    f32 y;

    obj = D_8010AB70_parasol_plummet[arg0];
    item = obj->data;
    item->unk1C |= 1;
    func_8001C258_main(obj->model[0], 4, 0);
    D_8010ABB8_parasol_plummet[arg0] = 1;
    item->unk04 = arg0;
    f = D_8010AC80_parasol_plummet[D_8010AC60_parasol_plummet]->data;
    screen.x = f->unk00;
    screen.y = f->unk04;
    func_80012D0C_main(0, CZoom, &screen, (Vec2f*)&pos);
    x = pos.x;
    y = pos.y;
    if (x >= 0.0f) {
        item->unk08 = x - 100.0f;
    } else {
        item->unk08 = x + 100.0f;
    }
    item->unk0C = y + 70.0f;
    item->unk18 = 0.0f;
    item->unk10 = (u8)(rand8() % 5) + 5;
    item->unk00 = -20.0f;
    if (item->unk08 > 0.0f) {
        item->unk10 = -item->unk10;
        item->unk00 = -item->unk00;
    }
    item->unk14 = (u8)(rand8() % 3) + 0x2D;
}

void func_80109B38_parasol_plummet(s32 arg0) {
    f32 scale[3] = { 3.0f, 3.0f, 3.0f };
    u8 type[3] = { 1, 2, 3 };
    s32 file[3] = { 0x210026, 0x210027, 0x3D0004 };
    omObjData* obj;
    PaItem* item;
    void* data;
    s32 kind;
    s16 m;
    f32 s;

    obj = omAddObj(0xB, 1, 0, -1, func_80109D74_parasol_plummet);
    obj->data = HuMemAllocTag(sizeof(PaItem), 0x7918);
    item = obj->data;
    kind = arg0 / 6;
    item->unk24 = type[kind];
    if (arg0 == kind * 6) {
        data = DataRead(file[kind]);
        m = HmfSprModelCreate(data, 0x6DD, 8);
        DataClose(data);
        D_8010ACA0_parasol_plummet[kind] = m;
    } else {
        m = func_80014618_main(D_8010ACA0_parasol_plummet[arg0 / 6], 8);
    }
    obj->model[0] = D_800CBB60_main[m].unk00;
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    item->unk20 = s = scale[arg0 / 6];
    omSetSca(obj, s, s, s);
    D_8010AB70_parasol_plummet[arg0] = obj;
    item->unk1C = 0;
}

void func_80109D74_parasol_plummet(omObjData* obj) {
    Vec2f screen;
    Vec pos;
    PaItem* item;

    item = obj->data;
    if (item->unk1C & 1) {
        if (D_8010AC66_parasol_plummet == 4) {
            omDelObj(obj);
            return;
        }
        omSetTra(obj, item->unk08, item->unk0C, 0.0f);
        omSetRot(obj, 0.0f, 0.0f, item->unk18);
        item->unk08 += item->unk10;
        item->unk0C += item->unk14;
        item->unk14 -= 1.0f;
        if (item->unk14 < -20.0f) {
            item->unk14 = -20.0f;
        }
        if (item->unk24 == 3) {
            item->unk18 += item->unk00;
            if (item->unk18 >= 360.0f) {
                item->unk18 -= 360.0f;
            }
            if (item->unk18 < 0.0f) {
                item->unk18 += 360.0f;
            }
        }
        pos.x = item->unk08;
        pos.y = item->unk0C;
        pos.z = 0.0f;
        Hu3DCam3DToScreen(0, &pos, &screen);
        if ((s32)screen.y >= 0xF0) {
            func_8001C258_main(obj->model[0], 4, 4);
            D_8010ABB8_parasol_plummet[item->unk04] = 0;
            item->unk1C &= ~1;
        }
        if (D_8010AC66_parasol_plummet != 1 && D_8010AC66_parasol_plummet != 2) {
            func_8001C258_main(obj->model[0], 4, 4);
            D_8010ABB8_parasol_plummet[item->unk04] = 0;
            item->unk08 = -10000.0f;
            item->unk0C = -10000.0f;
        }
    }
}

/* NON_MATCHING: retail rematerialises the 0.0f offsets at each use where this hoists them into f24 (masked 19,
   one instruction long). Nearest player (0x10 | index) within 100, or (players only) nearest live item within 80;
   -1 for none. */
#ifdef NON_MATCHING
s16 func_80109F7C_parasol_plummet(omObjData* obj, s32 arg1) {
    PaPlayer* p;
    PaItem* item;
    omObjData* other;
    f32 best;
    s32 hit;
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;
    f32 d;
    s32 i;

    best = 100.0f;
    hit = -1;
    if (arg1 == 0) {
        p = obj->data;
        x = p->unk00 - 0.0f;
        y = (p->unk04 - 0.0f) + 0.0f;
    } else {
        item = obj->data;
        x = item->unk08;
        y = item->unk0C;
    }
    for (i = 0; i < 4; i++) {
        other = D_8010AB60_parasol_plummet[i];
        if (other != obj) {
            p = other->data;
            dx = p->unk00 - 0.0f;
            dy = p->unk04 - 0.0f;
            dx -= x;
            dx *= dx;
            dy -= y;
            dy *= dy;
            d = HuSqrtf(dx + dy);
            if (d < best) {
                hit = i | 0x10;
                best = d;
            }
        }
    }
    if (arg1 == 0) {
        for (i = 0; i < 18; i++) {
            if (D_8010ABB8_parasol_plummet[i] == 1) {
                other = D_8010AB70_parasol_plummet[i];
                if (other != obj) {
                    item = other->data;
                    dx = item->unk08;
                    dy = item->unk0C;
                    dx -= x;
                    dx *= dx;
                    dy -= y;
                    dy *= dy;
                    d = HuSqrtf(dx + dy);
                    if ((d < best) & (d < 80.0f)) {
                        hit = i;
                        best = d;
                    }
                }
            }
        }
    }
    return hit;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109F7C_parasol_plummet);
#endif

const PaS16x4 D_8010AB14_parasol_plummet = { { 0x20, 0xE0, 0x20, 0xE0 } }; /* coin counter x */
const PaS16x4 D_8010AB1C_parasol_plummet = { { 0x18, 0x18, 0xD8, 0xD8 } }; /* coin counter y */

const PaS32x8 D_8010AB24_parasol_plummet = { { 8, 9, 10, 11, 12, 13, 14, 15 } }; /* character icon by character */
const PaS16x4 D_8010AB44_parasol_plummet = { { 0x20, 0xEC, 0x20, 0xEC } }; /* coin counter x (process) */

/* NON_MATCHING: register allocation and the digit x (this hoists x + 0x20 out of the loop; masked 3). Creates
   the coin counter sprites and starts their process. */
#ifdef NON_MATCHING
void func_8010A160_parasol_plummet(void) {
    PaS16x4 xs = D_8010AB14_parasol_plummet;
    PaS16x4 ys = D_8010AB1C_parasol_plummet;
    PaS32x8 icon = D_8010AB24_parasol_plummet;
    s16 i;
    s16 j;
    u16 x;
    u16 y;

    D_8010ACC0_parasol_plummet = func_8000B838_main(0x31);
    D_8010ACDC_parasol_plummet = func_8000B838_main(0x21001B);
    D_8010ACD2_parasol_plummet = func_8000B838_main(0x21001A);
    for (i = 0; i < 4; i++) {
        x = xs.v[i];
        y = ys.v[i];
        D_8010ACC2_parasol_plummet[i] = func_8000B838_main(icon.v[GwPlayer[i].chr] | 0x210000);
        D_8010ACCA_parasol_plummet[i] = InitEspriteSlot(D_8010ACC2_parasol_plummet[i], 0, 1);
        func_8000BBD4_main(D_8010ACCA_parasol_plummet[i], x, y);
        D_8010ACD4_parasol_plummet[i] = InitEspriteSlot(D_8010ACD2_parasol_plummet, 0, 1);
        func_8000BBD4_main(D_8010ACD4_parasol_plummet[i], x + 0x10, y);
        D_8010ACDE_parasol_plummet[i] = InitEspriteSlot(D_8010ACDC_parasol_plummet, 0, 1);
        func_8000BBD4_main(D_8010ACDE_parasol_plummet[i], x + 0x20, y);
        for (j = 0; j < 3; j++) {
            D_8010ACA8_parasol_plummet[i * 3 + j] = InitEspriteSlot(D_8010ACC0_parasol_plummet, 0, 1);
            func_8000BCC8_main(D_8010ACA8_parasol_plummet[i * 3 + j], 0xA);
            func_8000BC48_main(D_8010ACA8_parasol_plummet[i * 3 + j], 0x1000);
            func_8000BBD4_main(D_8010ACA8_parasol_plummet[i * 3 + j], x + (j * 0xC + 0x20), y);
        }
    }
    omPrcSetStatBit(omAddPrcObj(func_8010A484_parasol_plummet, 0, 0, 0), 0x80);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A160_parasol_plummet);
#endif

/* NON_MATCHING: register allocation (retail keeps y in a stack slot; frame 16 bytes smaller; masked 77). The coin
   counters: icon, coin, "x" and three digits per player, leading zeros hidden, "x" hidden from 100 coins. */
#ifdef NON_MATCHING
void func_8010A484_parasol_plummet(void) {
    PaS16x4 xs = D_8010AB44_parasol_plummet;
    PaS16x4 ys = D_8010AB1C_parasol_plummet;
    s32 i;
    s32 j;
    s16 x;
    s32 y;
    s16 coins;
    s16 rem;
    s32 div;
    s32 digit;
    s32 small;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            x = xs.v[i];
            y = ys.v[i];
            func_8000BBD4_main(D_8010ACCA_parasol_plummet[i], x, y);
            func_8000BBD4_main(D_8010ACD4_parasol_plummet[i], x + 0x10, y);
            func_8000BBD4_main(D_8010ACDE_parasol_plummet[i], x + 0x20, y);
            div = 100;
            coins = GwPlayer[i].gameCoin;
            rem = coins;
            small = coins < 100;
            for (j = 0; j < 3; j++) {
                func_8000BBD4_main(D_8010ACA8_parasol_plummet[i * 3 + j], x + (j * 0xC + 0x20), y);
                digit = rem / div;
                rem %= div;
                func_8000BB54_main(D_8010ACA8_parasol_plummet[i * 3 + j]);
                if ((div == 100) & small) {
                    func_8000BB94_main(D_8010ACA8_parasol_plummet[i * 3 + j]);
                }
                if ((div == 10) & (coins < 10)) {
                    func_8000BB94_main(D_8010ACA8_parasol_plummet[i * 3 + j]);
                }
                if (!small) {
                    func_8000BB94_main(D_8010ACDE_parasol_plummet[i]);
                }
                func_8000BDDC_main(D_8010ACA8_parasol_plummet[i * 3 + j], 1);
                func_8000BD94_main(D_8010ACA8_parasol_plummet[i * 3 + j], digit, 0);
                div /= 10;
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A484_parasol_plummet);
#endif

void func_8010A75C_parasol_plummet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 x, f32 y, f32 z) {
    func_8000B5F0_main(1);
    D_8010AB50_parasol_plummet = func_8000B638_main();
    ScissorSet(D_8010AB50_parasol_plummet, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(D_8010AB50_parasol_plummet, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = x;
    Center.y = y;
    Center.z = z;
    Hu3DCamSetPerspective(D_8010AB50_parasol_plummet, 30.0f, 80.0f, 8000.0f);
}
