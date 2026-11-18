#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

// at A: Awful Tower

typedef func_800E1BA8_minigame_ObjData MgWork;

/* omObjData::data of a ground object (the framework's stage piece) */
typedef struct AtGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} AtGround; /* size 0xB4 */

/* omObjData::data of a coin: the framework's item actor (as Treadmill Grill's TgGrill) */
typedef struct AtCoin {
    /* 0x00 */ u8 unk00[0x20];
    /* 0x20 */ char unk20[0x14];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ u16 unk50;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ s8 unk53;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 unk55; /* sprite model */
    /* 0x56 */ u16 unk56;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ char unk5C[0x1C];
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 (*unk84[9])();
    /* 0xA8 */ void* unkA8;
} AtCoin; /* size 0xAC */

/* One player's slot, by team (D_8010D308_awful_tower) */
typedef struct AtPlayer {
    /* 0x00 */ s8 unk00; /* character */
    /* 0x01 */ s8 unk01; /* player */
    /* 0x02 */ u8 unk02; /* group */
    /* 0x03 */ s8 unk03; /* pad */
    /* 0x04 */ s8 unk04; /* CPU difficulty, -1 human */
    /* 0x05 */ char unk05[3];
    /* 0x08 */ s32 unk08;
} AtPlayer; /* size 0xC */

/* The minigame control block (as Treadmill Grill's TgCtrl) */
typedef struct AtCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
} AtCtrl; /* size 0x28 */

/* Sprite-model slot: main's unk_800ECDE0 (src/14EA0.c) */
typedef struct AtSprModel {
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
    /* 0x20 */ u8* unk20;
} AtSprModel; /* size 0x24 */

typedef struct AtRect {
    s32 v[4];
} AtRect;

typedef struct AtTbl8 {
    s32 v[8];
} AtTbl8;

typedef struct AtTbl3 {
    s32 v[3];
} AtTbl3;

typedef struct AtF5 {
    f32 v[5];
} AtF5;

typedef struct AtByte4 {
    u8 v[4];
} AtByte4;

typedef struct AtChrTbl {
    u8 v[8];
} AtChrTbl;

typedef struct AtTbl16 {
    s32 v[2][8];
} AtTbl16;

// main
void func_80021BE0_main(s32* arg0, s32 n);
void func_800142A0_main(s32);
void func_8000B710_main(s32);
void func_80045010_main(const s16*, s32);
omObjData* func_80045ED0_main(u32 arg0);
u16 func_80014618_main(s16 index, u16 arg1);
s16 func_800329B4_main(void*);
void func_8001FB34_main(s16 arg0, u8 arg1);
void func_8001FBBC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_8001FBFC_main(s16 arg0, f32 arg1, f32 arg2, f32 arg3);

extern AtSprModel* D_800CBB60_main;
extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern Vec CRotM[];

// minigame
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E13CC_minigame(omObjData* obj, f32 arg1, f32 arg2, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E1468_minigame(omObjData* obj);
void func_800E1490_minigame(u16 arg0);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E1594_minigame(omObjData* obj, s32 arg1, s32 arg2, s32 arg3);
void func_800E17F4_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
extern s32 D_800EBEB0_minigame[];
extern omObjData* D_800EBE70_minigame[];

// LOCAL

extern s32 D_8010CB60_awful_tower[4]; /* team bits 1, 2, 4, 8 */
extern AtCtrl D_8010CB70_awful_tower;
extern s32 D_8010CB98_awful_tower[];
extern s16 D_8010CB9A_awful_tower; /* low half of D_8010CB98_awful_tower[0] */
extern AtRect D_8010CCC0_awful_tower;
extern AtRect D_8010CCD0_awful_tower;
extern const s16 D_8010CCE0_awful_tower[];
extern const AtTbl8 D_8010CD34_awful_tower;
extern const AtChrTbl D_8010CD2C_awful_tower;
extern const AtTbl16 D_8010CD54_awful_tower;
extern s16 D_8010D3EC_awful_tower[2];
extern Gfx* gMainGfxPos;
extern Gfx D_8010CBA0_awful_tower[];
extern const AtRect D_8010CE40_awful_tower;
extern const AtRect D_8010CE50_awful_tower;
extern const AtRect D_8010CE60_awful_tower;
extern const AtRect D_8010CE70_awful_tower;
extern const AtByte4 D_8010CE80_awful_tower;

/* main's esprite slot (src/esprite.c D_800CD1DC_main_Struct; no pointer fields) */
typedef struct AtEspr {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04; /* sprite group */
    /* 0x06 */ char unk06[0x1E];
} AtEspr; /* size 0x24 */
extern AtEspr* D_800CD1DC_main;
extern const AtRect D_8010CDC0_awful_tower;
extern const AtTbl3 D_8010CDD0_awful_tower;
extern const AtTbl3 D_8010CDDC_awful_tower;
extern const AtF5 D_8010CDE8_awful_tower;
extern const AtF5 D_8010CDFC_awful_tower;
extern const AtTbl3 D_8010CE10_awful_tower;
extern u16 D_8010D348_awful_tower[4][3];
extern s16 D_8010D3B8_awful_tower[4];
extern s16 D_8010D3D0_awful_tower[4];
extern u16 D_800D530C_main;

extern s16 D_8010D2CC_awful_tower[4];
extern AtPlayer D_8010D2D8_awful_tower[4];
extern AtPlayer* D_8010D308_awful_tower[4];
extern f32 D_8010D320_awful_tower[4];
extern u8 D_8010D330_awful_tower[4][5];
extern omObjData* D_8010D344_awful_tower;
extern omObjData* D_8010D360_awful_tower[4][3];
extern omObjData* D_8010D390_awful_tower[5];
extern omObjData* D_8010D3A8_awful_tower[4];
extern u8 D_8010D3CC_awful_tower[4];
extern u16 D_8010D3D8_awful_tower;
extern u32 D_8010D3DC_awful_tower;
extern s16 D_8010D3E4_awful_tower;
extern omObjData* D_8010D3E8_awful_tower;
extern s8 D_8010D3FC_awful_tower;
extern u8 D_8010D3FD_awful_tower;
extern u8 D_8010D3FE_awful_tower;

/* func_80108E8C_awful_tower's state: per team unless noted */
extern u32 D_8010CBE8_awful_tower;     /* frame counter (all teams) */
extern f32 D_8010CBEC_awful_tower[4];  /* player x, 32000 when out */
extern s8 D_8010CBFC_awful_tower[4];   /* floor stood on, 1-based; 0 the ground, -1 airborne */
extern s8 D_8010CC00_awful_tower[4];
extern s8 D_8010CC04_awful_tower[4];   /* floor ridden */
extern s8 D_8010CC08_awful_tower[4];
extern u8 D_8010CC0C_awful_tower[4];   /* flying enemy state */
extern u8 D_8010CC10_awful_tower[4];   /* flying enemy side/level */
extern u8 D_8010CC14_awful_tower[4];   /* drop timer */
extern f32 D_8010CC18_awful_tower[4];  /* hazard y, -1000 none */
extern u8 D_8010CC28_awful_tower[4];
extern f32 D_8010CC2C_awful_tower[4];
extern s8 D_8010CC3C_awful_tower[4];   /* CPU target floor, 1-based */
extern u8 D_8010CC40_awful_tower[4];   /* CPU jump timer */
extern u8 D_8010CC44_awful_tower;      /* finish hop step */
extern f32 D_8010CC48_awful_tower;     /* finish hop start x */
extern u8 D_8010CC4C_awful_tower[4];
extern f32 D_8010CC50_awful_tower[4];
extern f32 D_8010CC60_awful_tower[4];
extern u8 D_8010CC70_awful_tower[4];
extern s8 D_8010CC74_awful_tower[4];
extern s8 D_8010CC78_awful_tower[4];   /* CPU timing jitter */
extern s8 D_8010CC7C_awful_tower[];    /* CPU jump frame per floor */
extern s8 D_8010CC8F_awful_tower[];    /* CPU jump hold per target floor (1-based: label is one byte before its table) */
extern u8 D_8010CCA4_awful_tower[4];
extern f32 D_8010CCA8_awful_tower[];   /* hazard vx by side */
extern f32 D_8010CCB4_awful_tower[];   /* hazard vy by side */
extern f32 D_8010D0D0_awful_tower[16]; /* floor heights this frame */
extern f32 D_8010D110_awful_tower[16]; /* floor height change this frame */
extern f32 D_8010D150_awful_tower[4];  /* flying enemy x, y, vx, vy */
extern f32 D_8010D160_awful_tower[4];
extern f32 D_8010D170_awful_tower[4];
extern f32 D_8010D180_awful_tower[4];
extern f32 D_8010D190_awful_tower[4];  /* hazard x, vx, vy, rot, rot speed, armed */
extern f32 D_8010D1A0_awful_tower[4];
extern f32 D_8010D1B0_awful_tower[4];
extern f32 D_8010D1C0_awful_tower[4];
extern f32 D_8010D1D0_awful_tower[4];
extern f32 D_8010D1E0_awful_tower[4];
extern f32 D_8010D1F0_awful_tower[55]; /* cosine cache, -1 unset */
extern f32 D_800D54FC_main[][3];
extern s16 D_800CDA7C_main[];
extern u16 D_800D5558_main[4];
extern s16 D_800D1244_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern s16 D_800D056A_main[];
extern s16 D_800D1382_main[];
extern f32 D_800EB744_minigame;
extern f32 D_800EB760_minigame;

/* main's FxPool (src/D7A0.c) */
typedef struct FxPoolEntry {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 model;
    /* 0x04 */ Vec unk04;
} FxPoolEntry; /* size 0x10 */
typedef struct FxPool {
    /* 0x00 */ s16 count;
    /* 0x04 */ FxPoolEntry* entries;
} FxPool;
extern FxPool* D_800D6A00_main[8];

void func_800DDD94_minigame(omObjData* obj);
void func_800E4C88_minigame(omObjData* obj, s32 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
void func_800E19FC_minigame(MgWork* work, s32 state);
u16 func_800E4A80_minigame(omObjData* obj);
void func_80014850_main(s16 index);

void func_80106028_awful_tower(omObjData* obj);
void func_801061FC_awful_tower(omObjData* obj);
void func_80106A9C_awful_tower(omObjData* obj);
s32 func_80106C44_awful_tower(omObjData* player, omObjData* coin);
void func_80106CDC_awful_tower(omObjData* obj);
void func_80106E84_awful_tower(omObjData* obj);
void func_80106FDC_awful_tower(omObjData* obj);
void func_80107734_awful_tower(omObjData* obj);
void func_80107858_awful_tower(void);
void func_80108880_awful_tower(omObjData* obj, u32 arg1, s32 arg2, u16 arg3, f32 x, f32 y, f32 z);
void func_80108CCC_awful_tower(omObjData* obj);
void func_80108D3C_awful_tower(omObjData* obj);
void func_80108DAC_awful_tower(omObjData* obj);
void func_80108E1C_awful_tower(omObjData* obj);
void func_80108E8C_awful_tower(omObjData* obj);

void func_801059A0_awful_tower(void) {
    omObjData* obj;
    s32 i;
    s32 j;

    Hu3DAnimInit(50);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(100, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(4);
    func_8000B710_main(4);
    for (i = 0; i < 4; i++) {
        AtRect x0 = D_8010CCC0_awful_tower;
        AtRect x1 = D_8010CCD0_awful_tower;

        ScissorSet(i, x0.v[i], 0.0f, x1.v[i], 240.0f);
        ViewportSet(i, 640.0f, 480.0f, 511.0f, i * 272 + 236, 480.0f, 511.0f);
        Hu3DCamSetPerspective(i, 7.152669f, 8000.0f, 16000.0f);
        CenterM[i].x = 0.0f;
        CenterM[i].y = 650.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = 0.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CZoomM[i] = 12000.0f;
    }
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    HmfLightMaxSet(2);
    HmfLightDirSet(0, 0.0f, 80.0f, 130.0f);
    HmfLightColorSet(0, 0x80, 0x80, 0x90);
    HmfLightDirSet(1, 20.0f, 80.0f, 110.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xF0);
    omAddObj(0, 0, 0, -1, func_80106028_awful_tower);
    D_8010D3E8_awful_tower = omAddObj(4, 0x15, 0x15, -1, func_80106FDC_awful_tower);
    omSetStatBit(D_8010D3E8_awful_tower, 0xA0);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = D_8010D344_awful_tower =
        omAddObj(2, 0x15, 0x15, -1, func_80106A9C_awful_tower);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = D_8010D360_awful_tower[i][j] =
                omAddObj(2, 4, 4, -1, func_80106E84_awful_tower);
        }
    }
    for (i = 0; i < 5; i++) {
        D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = D_8010D390_awful_tower[i] =
            omAddObj(2, 4, 2, -1, func_80106CDC_awful_tower);
    }
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[0] =
        omAddObj(3, 0xC, 0x3C, -1, func_80108CCC_awful_tower);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[1] =
        omAddObj(3, 0xC, 0x3C, -1, func_80108D3C_awful_tower);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[2] =
        omAddObj(3, 0xC, 0x3C, -1, func_80108DAC_awful_tower);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[3] =
        omAddObj(3, 0xC, 0x3C, -1, func_80108E1C_awful_tower);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 4;
    omSetStatBit(obj, 0xA0);
    WipeCreateIn(0xFF, 30);
    func_80045010_main(D_8010CCE0_awful_tower, 1);
    D_8010CB70_awful_tower.unk01 = 0;
    D_8010CB70_awful_tower.unk1C = 60;
    D_8010CB70_awful_tower.unk1E = 1800;
    D_8010CB70_awful_tower.unk03 = 2;
    D_8010CB70_awful_tower.unk02 = 1;
    D_8010CB70_awful_tower.unk22 = 75;
    D_8010CB70_awful_tower.unk24 = 165;
    D_8010CB70_awful_tower.unk04 = 0;
    D_8010CB70_awful_tower.unk05 = 0;
    D_8010CB70_awful_tower.unk20 = -1;
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010CB70_awful_tower);
    for (i = 0; i < 4; i++) {
        D_8010D2CC_awful_tower[i] = func_8000D658_main(0x6A9, 4);
    }
}

void func_8010600C_awful_tower(void) {
    func_80107858_awful_tower();
}

void func_80106028_awful_tower(omObjData* obj) {
    AtPlayer** p;
    s32 i;
    s32 group;

    D_8010D3D8_awful_tower = 0;
    D_8010D3E4_awful_tower = 0;
    D_8010D3DC_awful_tower = 0;
    D_8010D3FC_awful_tower = 5;
    D_8010D3FD_awful_tower = 0;
    D_8010D3FE_awful_tower = 0;
    D_8010D320_awful_tower[0] = 650.0f;
    D_8010D320_awful_tower[1] = 650.0f;
    D_8010D320_awful_tower[2] = 650.0f;
    D_8010D320_awful_tower[3] = 650.0f;
    for (i = 0; i < 4; i++) {
        D_8010D330_awful_tower[i][0] = D_8010D330_awful_tower[i][1] = D_8010D330_awful_tower[i][2] =
            D_8010D330_awful_tower[i][3] = D_8010D330_awful_tower[i][4] = 1;
        D_8010D308_awful_tower[i] = &D_8010D2D8_awful_tower[i];
        bzero(D_8010D308_awful_tower[i], sizeof(AtPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = D_8010D3CC_awful_tower[i] = GwPlayer[i].group;
        p = &D_8010D308_awful_tower[group & 0xFF];
        (*p)->unk01 = i;
        (*p)->unk03 = GwPlayer[i].pad;
        (*p)->unk00 = GwPlayer[i].chr;
        (*p)->unk02 = group;
        (*p)->unk04 = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    obj->func = func_801061FC_awful_tower;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CCE0_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CD2C_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CD34_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CD54_awful_tower);

/* The minigame's main control object: intro, play, winner, result and exit. */
void func_801061FC_awful_tower(omObjData* obj) {
    struct {
        AtChrTbl chr;
        AtTbl8 hi;
        AtTbl16 lo;
    } t;
    s32 c;
    s16 i;

    t.chr = D_8010CD2C_awful_tower;
    t.hi = D_8010CD34_awful_tower;
    t.lo = D_8010CD54_awful_tower;
    D_8010D3DC_awful_tower++;
    switch (D_8010D3E4_awful_tower) {
        case 0:
            if (D_8010D3DC_awful_tower == 51 && D_8010D3D8_awful_tower == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(51);
            }
            break;
        case 3:
            if (D_8010D3FE_awful_tower >= 20) {
                func_800E6F1C_minigame();
            }
            break;
    }
    func_800E6F40_minigame();
    switch (D_8010D3E4_awful_tower) {
        case 0:
            if (func_800E6E8C_minigame() == 1) {
                D_8010D3E4_awful_tower = 1;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 1:
            if (func_800E6E8C_minigame() == 2) {
                D_8010D3E4_awful_tower = 2;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 2:
            if (D_8010D3FC_awful_tower != 5 || func_800E6E8C_minigame() == 3) {
                if (D_8010D3FC_awful_tower == 5) {
                    D_8010D3E4_awful_tower = 6;
                    D_8010D3FC_awful_tower = 4;
                } else {
                    D_8010D3E4_awful_tower = 3;
                }
                D_8010D3DC_awful_tower = 0;
            }
            if (D_8010D3E4_awful_tower != 3) {
                break;
            }
        case 3:
            if (D_8010D3DC_awful_tower == 0) {
                D_8010CB70_awful_tower.unk22 = 210;
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                D_8010CB70_awful_tower.unk06 = 0;
                D_8010CB70_awful_tower.unk18[0] = D_8010D308_awful_tower[D_8010D3FC_awful_tower]->unk01;
                GwPlayer[D_8010D308_awful_tower[D_8010D3FC_awful_tower]->unk01].bonusCoin = 10;
            }
            if (D_8010D3DC_awful_tower == 2) {
                func_800E6F34_minigame(30);
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010D3E4_awful_tower = 4;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 6:
            if (D_8010D3DC_awful_tower == 1) {
                D_8010CB70_awful_tower.unk06 = 4;
                D_8010CB70_awful_tower.unk24 = 0x90;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010D3E4_awful_tower = 5;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 4:
            if (D_8010D3DC_awful_tower == 1) {
                c = D_8010D308_awful_tower[D_8010D3FC_awful_tower]->unk00;
                D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9] =
                    func_8000B108_main(D_800A178C_main[c][0] | D_800A178C_main[c][2], 0x4AD);
                D_8010D3EC_awful_tower[0] =
                    func_80017790_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 1, t.chr.v[c],
                                       (t.hi.v[c] << 16) | t.lo.v[0][c]);
                D_8010D3EC_awful_tower[1] = func_80017AD8_main((t.hi.v[c] << 16) | t.lo.v[1][c]);
                func_8001C514_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]);
                func_8001C8A8_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9],
                                   D_8010CB60_awful_tower[D_8010D3FC_awful_tower]);
                func_8001C258_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[0], 4, 4);
                func_8001C258_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 4, 0);
                func_8001C6A8_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9],
                                   HmfModelData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[0]].unk40);
                func_8001C814_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 2, 2);
                HmfModelData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]].pos.x =
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.x;
                HmfModelData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]].pos.y =
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.y;
                HmfModelData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]].pos.z =
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.z;
            }
            if (D_8010D3DC_awful_tower < 16) {
                Hu3DModelRotSet(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 0.0f,
                                D_8010D3DC_awful_tower / 15.0f * 90.0f + -90.0f, 0.0f);
            }
            if (D_8010D3DC_awful_tower == 30) {
                func_8001C5B4_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9],
                                   D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[10]);
                func_8001C814_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 2, 0);
                func_80017954_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 1,
                                   t.chr.v[D_8010D308_awful_tower[D_8010D3FC_awful_tower]->unk00],
                                   D_8010D3EC_awful_tower[1]);
                func_80045ED0_main(D_8010D308_awful_tower[D_8010D3FC_awful_tower]->unk08);
            }
        case 5:
            if (D_8010D3E4_awful_tower == 5 && D_8010D3DC_awful_tower == 1) {
                for (i = 0; i < 4; i++) {
                    func_800E5690_minigame(D_8010D3A8_awful_tower[i], 14);
                }
            }
            if (func_800E6E8C_minigame() == 5) {
                D_8010D3E4_awful_tower = 7;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 7:
            if (D_8010D3DC_awful_tower == 1) {
                WipeCreateOut(0, 20);
            } else if (D_8010D3DC_awful_tower >= 32) {
                D_8010D3D8_awful_tower = 1;
            }
            break;
    }
    if (D_8010D3D8_awful_tower != 0 || D_800D530C_main != 0) {
        if (D_800D530C_main != 0) {
            if (D_8010D3FD_awful_tower == 0) {
                WipeCreateOut(0, 20);
                HuAudSeqFadeOut(20);
                func_8004AB0C_main(20);
            }
            D_8010D3FD_awful_tower++;
            if (D_8010D3FD_awful_tower < 25) {
                return;
            }
        } else {
            HuAudSeqFadeOut(30);
        }
        omOvlReturnEx(1);
    }
}

void func_80106A9C_awful_tower(omObjData* obj) {
    AtGround* gw;

    obj->model[0] = -1;
    obj->model[0] = func_8000B0A0_main(0x460006, 0x499);
    func_8001C2FC_main(obj->model[0], 0x600, 0);
    func_8001FB34_main(obj->model[0], 1);
    func_8001FBBC_main(obj->model[0], 0xFF, 0xFF, 0xFF);
    func_8001FBFC_main(obj->model[0], 0.0f, 0.0f, 127.0f);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->trans.x = 1500.0f;
    obj->trans.y = -60.0f;
    obj->trans.z = 300.0f;
    omSetRot(obj, 90.0f, 0.0f, 0.0f);
    omSetSca(obj, 1000.0f, 1.0f, 1.0f);
    obj->data = gw = HuMemAllocTag(sizeof(AtGround), 31000);
    memset(gw, 0, sizeof(AtGround));
    gw->unk03 = 1;
    func_800E139C_minigame(obj, 0.0f, -670.0f, -380.0f, 670.0f, 250.0f);
    func_800E1304_minigame(obj, 1.0f);
    func_800E1310_minigame(obj, 6.0f);
    func_800E1468_minigame(obj);
    gw->unk04 = 0;
    obj->func = NULL;
}

s32 func_80106C44_awful_tower(omObjData* player, omObjData* coin) {
    AtCoin* cw = coin->data;

    GwPlayer[((MgWork*)player->data)->unk59].gameCoin++;
    HuAudFXPlay(9);
    cw->unk54 = 0;
    cw->unk78 = 0;
    func_8001C258_main(coin->model[0], 4, 4);
    func_8001C258_main(coin->model[1], 4, 4);
    return 1;
}

void func_80106CDC_awful_tower(omObjData* obj) {
    AtCoin* cw;
    s16 i;
    s32 pad[2]; /* retail's frame holds 8 unused bytes */

    obj->data = HuMemAllocTag(sizeof(AtCoin), 31000);
    memset(obj->data, 0, sizeof(AtCoin));
    cw = obj->data;
    if (D_8010CB98_awful_tower[0] == -1) {
        func_800E1594_minigame(obj, 0x210026, 0x41D, 8);
        D_8010CB98_awful_tower[0] = cw->unk55;
    } else {
        cw->unk55 = func_80014618_main(D_8010CB9A_awful_tower, 8);
        obj->model[0] = D_800CBB60_main[cw->unk55].unk00;
        func_8001C2FC_main(obj->model[0], 0x70000000, 0x70000000);
    }
    cw->unk44 = 0.0f;
    cw->unk48 = 40.0f;
    cw->unk34 = 50.0f;
    cw->unk3C = 0.0f;
    cw->unk78 = 0;
    cw->unk52 = 3;
    cw->unk7C = 2000;
    cw->unk50 = 0;
    cw->unk40 = 0.0f;
    cw->unk58 = 1.2f;
    cw->unk56 = 0;
    cw->unk54 = 1;
    for (i = 0; i < 9; i++) {
        cw->unk84[i] = NULL;
    }
    cw->unk84[8] = func_80106C44_awful_tower;
    func_800E17F4_minigame(obj, 3.0f, 3.0f, 3.0f);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->func = NULL;
}

void func_80106E84_awful_tower(omObjData* obj) {
    AtGround* gw;

    obj->model[0] = -1;
    obj->trans.x = obj->trans.y = obj->trans.z = 250.0f;
    obj->data = gw = HuMemAllocTag(sizeof(AtGround), 31000);
    memset(gw, 0, sizeof(AtGround));
    gw->unk03 = 1;
    func_800E13CC_minigame(obj, 50.0f, 100.0f, -50.0f, -50.0f, 50.0f, 50.0f);
    func_800E1304_minigame(obj, 1.0f);
    func_800E1310_minigame(obj, 6.0f);
    gw->unk04 = 0;
    obj->func = NULL;
}

s16 func_80106F58_awful_tower(s32 file, u16* spr) {
    void* data;
    s16 sprite;

    u16 idx;

    data = DataRead(file);
    sprite = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    *spr = idx = HmfSprModelCreate((void*)-1, 0x6B9, 0);
    D_800CBB60_main[idx].unk02 = sprite;
    return D_800CBB60_main[idx].unk00;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDC0_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDD0_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDDC_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDE8_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDFC_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE10_awful_tower);

#ifdef NON_MATCHING
/* Stage object setup: sprites, tower pieces, coins, blocks and the background. */
void func_80106FDC_awful_tower(omObjData* obj) {
    AtRect a = D_8010CDC0_awful_tower;
    s16 i;
    s16 j;
    s16 k;

    for (i = 0; i < 4; i++) {
        D_8010D3B8_awful_tower[i] = func_8000B838_main(a.v[i]);
        D_8010D3D0_awful_tower[i] =
            InitEspriteSlot(D_8010D3B8_awful_tower[i] = func_8000B838_main(a.v[i]), 0, 0);
        func_8000BB94_main(D_8010D3D0_awful_tower[i]);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 4; i++) {
            AtTbl3 b = D_8010CDD0_awful_tower;
            AtTbl3 c = D_8010CDDC_awful_tower;

            obj->model[i + b.v[j]] = func_80106F58_awful_tower(c.v[j] | 0x460000, &D_8010D348_awful_tower[i][j]);
            func_8001C258_main(obj->model[i + b.v[j]], 4, 4);
            func_8001C8A8_main(obj->model[i + b.v[j]], D_8010CB60_awful_tower[i]);
            if (j < 2) {
                Hu3DModelScaleSet(obj->model[i + b.v[j]], 6.0525f, 6.0525f, 6.0525f);
            } else {
                Hu3DModelScaleSet(obj->model[i + b.v[j]], 3.02625f, 3.02625f, 3.02625f);
            }
        }
    }
    for (i = 0; i < 5; i++) {
        AtF5 d = D_8010CDE8_awful_tower;
        AtF5 e = D_8010CDFC_awful_tower;
        AtCoin* cw = D_8010D390_awful_tower[i]->data;

        D_8010D390_awful_tower[i]->trans.x = d.v[i] * 150.0f;
        D_8010D390_awful_tower[i]->trans.y = e.v[i] * 100.0f + 50.0f;
        D_8010D390_awful_tower[i]->trans.z = 0.0f;
        cw->unk56 = i;
        func_8001C258_main(D_8010D390_awful_tower[i]->model[0], 4, 0);
    }
    for (i = 0; i < 3; i++) {
        AtTbl3 f = D_8010CE10_awful_tower;

        obj->model[i] = func_8000B108_main(f.v[i] | 0x460000, 0x4BD);
    }
    obj->model[20] = func_8000B108_main(0x460005, 0x4BD);
    func_8001C8A8_main(obj->model[20], 0);
    Hu3DModelScaleSet(obj->model[20], 0.666666f, 0.666666f, 0.666666f);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            ((AtGround*)D_8010D360_awful_tower[i][j]->data)->unk04 = j + i * 3 + 1;
            for (k = 0; k < 3; k++) {
                D_8010D360_awful_tower[i][j]->model[k + 1] = Hu3DModelLink(D_8010D3E8_awful_tower->model[j]);
                func_8001C258_main(D_8010D360_awful_tower[i][j]->model[k + 1], 4, 4);
                Hu3DModelScaleSet(D_8010D360_awful_tower[i][j]->model[k + 1], 0.666666f, 0.666666f, 0.666666f);
                func_8001C8A8_main(D_8010D360_awful_tower[i][j]->model[k + 1], D_8010CB60_awful_tower[i]);
            }
        }
    }
    obj->model[3] = func_8000B108_main(0xA011A, 0x4BD);
    func_8001C814_main(obj->model[3], 2, 2);
    Hu3DModelPosSet(obj->model[3], 0.0f, 4500.0f, 300.0f);
    Hu3DModelScaleSet(obj->model[3], 0.5f, 0.5f, 0.5f);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 3) {
            obj->model[i + 4] = func_8000B108_main(i == 3 ? 0x460001 : 0x460000, 0x4B9);
        } else {
            obj->model[i + 4] = Hu3DModelLink(obj->model[4]);
        }
        func_8001C8A8_main(obj->model[i + 4], 15);
        func_8001C814_main(obj->model[i + 4], 1, 1);
        Hu3DModelPosSet(obj->model[i + 4], 0.0f, i * 1120.0 - 9.0, -300.0f);
        Hu3DModelScaleSet(obj->model[i + 4], 0.75f, 0.75f, 0.75f);
    }
    obj->func = func_80107734_awful_tower;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80106FDC_awful_tower);
#endif

#ifdef NON_MATCHING
/* Stage object update: runs the players' logic and lowers the tower top in the winner scene. */
void func_80107734_awful_tower(omObjData* obj) {
    f32 t;

    func_80107858_awful_tower();
    if (D_8010D3E4_awful_tower == 3) {
        if (D_8010D3DC_awful_tower == 1) {
            func_8001C258_main(obj->model[3], 4, 0);
            func_8001C8A8_main(obj->model[3], D_8010CB60_awful_tower[D_8010D3FC_awful_tower]);
        }
        if (D_8010D3DC_awful_tower != 0 && D_8010D3DC_awful_tower < 46) {
            t = 1.0f - D_8010D3DC_awful_tower / 45.0f;
            t = t * t;
            Hu3DModelPosSet(obj->model[3], 0.0f, t * 700.0f + 4430.0, 300.0f);
        }
    }
    func_80049F98_main();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80107734_awful_tower);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE40_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE50_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE60_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE70_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE80_awful_tower);

#ifdef NON_MATCHING
/* Draws the four players' tower backgrounds as textured strips; the winner's view zooms out. */
void func_80107858_awful_tower(void) {
    AtRect order = D_8010CE40_awful_tower;
    AtRect x0 = D_8010CCC0_awful_tower;
    AtRect x1 = D_8010CCD0_awful_tower;
    AtRect ofs = D_8010CE50_awful_tower;
    AtRect w0 = D_8010CE60_awful_tower;
    AtRect w1 = D_8010CE70_awful_tower;
    AtRect ofs2 = D_8010CE60_awful_tower;
    AtByte4 seq = D_8010CE80_awful_tower;
    AtRect sx0 = D_8010CCC0_awful_tower;
    AtRect sx1 = D_8010CCD0_awful_tower;
    f32 zoom;
    f32 a;
    f32 b;
    f32 scale;
    s32 zx0;
    s32 zx1;
    s16 i;
    s16 n;
    s16 j;
    HuSprite* spr;
    HuSprite_Unk84_Unk00_Struct* cel;
    s32 row;
    s32 end;
    s32 top;
    s32 bottom;
    s32 base;
    s32 ulx;
    s32 lrx;
    s32 uly;
    s32 lry;
    s32 ts;
    s32 dsdx;
    f64 f;
    u8 k;

    zoom = 0.0f;
    if (D_8010D3FC_awful_tower < 4) {
        for (i = 0, n = 0; i < 4; i++) {
            if (D_8010D3FC_awful_tower == i) {
                if (D_8010D3E4_awful_tower == 4 && D_8010D3DC_awful_tower < 30) {
                    zoom = 1.0f - D_8010D3DC_awful_tower / 29.0f;
                    zoom = (1.0f - zoom + 1.0f - zoom * zoom * zoom) * 0.5;
                } else if (D_8010D3E4_awful_tower == 7 || (D_8010D3E4_awful_tower == 4 && D_8010D3DC_awful_tower >= 30)) {
                    zoom = 1.0f;
                }
            } else {
                seq.v[n++] = i;
            }
        }
        seq.v[n] = D_8010D3FC_awful_tower;
    }
    if (zoom > 0.0f) {
        a = 1.0f - zoom;
        b = 1.0f - a;
        scale = ((a * 160.0f + b * 320.0f) - (a * 93.0f + b * 0.0f)) / (a * 67.0f + b * 113.0f);
        zx0 = sx0.v[D_8010D3FC_awful_tower] = x0.v[D_8010D3FC_awful_tower] * a + w0.v[D_8010D3FC_awful_tower] * b;
        zx1 = sx1.v[D_8010D3FC_awful_tower] = x1.v[D_8010D3FC_awful_tower] * a + w1.v[D_8010D3FC_awful_tower] * b;
        ScissorSet(D_8010D3FC_awful_tower, zx0, 0.0f, zx1, 240.0f);
        ViewportSet(D_8010D3FC_awful_tower, scale * 320.0f * 2.0f, scale * 240.0f * 2.0f, 511.0f,
                    ((D_8010D3FC_awful_tower * 68 + 59) * a + b * 160.0f) * 4.0f, 480.0f, 511.0f);
        CenterM[D_8010D3FC_awful_tower].y = a * D_8010D320_awful_tower[D_8010D3FC_awful_tower] + b * 4605.0f;
        for (i = 0; i < 4; i++) {
            if (D_8010D3FC_awful_tower != i) {
                if (i < D_8010D3FC_awful_tower) {
                    sx0.v[i] = MIN(zx0, sx0.v[i]);
                    sx1.v[i] = MIN(zx0, sx1.v[i]);
                } else {
                    sx0.v[i] = MAX(zx1, sx0.v[i]);
                    sx1.v[i] = MAX(zx1, sx1.v[i]);
                }
            }
        }
    }
    gSPDisplayList(gMainGfxPos++, D_8010CBA0_awful_tower);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    for (i = 3; i >= 0; i--) {
        spr = HuSprGet(D_800CD1DC_main[D_8010D3D0_awful_tower[order.v[i]]].unk04, 0);
        cel = &spr->unk_84->unk00[spr->unk_90];
        for (j = 0; j < 9; j++) {
            row = j * 16;
            end = (row + 17 <= 130) ? row + 17 : 130;
            if (i != 0) {
                gDPLoadTextureTile(gMainGfxPos++, (u8*)cel->unk00 + row * 114, G_IM_FMT_CI, G_IM_SIZ_8b, 114, 0, 0, 0,
                                   114, end - row, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                   G_TX_NOLOD);
                gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
            } else {
                gDPLoadTextureTile_4b(gMainGfxPos++, (u8*)cel->unk00 + row * 57, G_IM_FMT_CI, 114, 0, 0, 0, 114,
                                      end - row, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                      G_TX_NOLOD);
                gDPLoadTLUT_pal16(gMainGfxPos++, 0, spr->unk_84->unk0C);
            }
            top = row + i * 131;
            bottom = end + (i * 131 + 2);
            for (n = 0; n < 4; n++) {
                k = seq.v[n];
                if (zoom > 0.0f) {
                    if (sx0.v[k] == sx1.v[k]) {
                        continue;
                    }
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, sx0.v[k], 0,
                                  (k == D_8010D3FC_awful_tower) ? sx1.v[k] - 1 : sx1.v[k], 240);
                }
                if (k == D_8010D3FC_awful_tower) {
                    a = 1.0f - zoom;
                    b = 1.0f - a;
                } else {
                    a = 1.0f;
                    b = 0.0f;
                }
                base = (D_8010D320_awful_tower[k] - 650.0f) / 3850.0 * -284.0 + 284.0;
                ulx = (x0.v[k] * a + w0.v[k] * b) * 4.0f;
                lrx = (x1.v[k] * a + w1.v[k] * b) * 4.0f;
                f = a + b * (320.0 / 113.0);
                uly = ((top - base - 120) * f + 120.0) * 4.0;
                lry = ((bottom - base - 120) * f + 120.0) * 4.0 - 1.0;
                if (ulx > 1280 || lrx < 0) {
                    continue;
                }
                if (uly > 960 || lry < 0) {
                    continue;
                }
                ts = (ofs.v[k] * a + ofs2.v[k] * b) * 32.0;
                dsdx = (a * 67.0f + b * 113.0f) / ((a * 160.0f + b * 320.0f) - (a * 93.0f + b * 0.0f)) * 1024.0;
                gSPScisTextureRectangle(gMainGfxPos++, ulx, uly, lrx, lry, G_TX_RENDERTILE, ts, 0, dsdx, dsdx);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        ScissorSet(i, sx0.v[i], 0.0f, sx1.v[i], 240.0f);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80107858_awful_tower);
#endif

#ifdef NON_MATCHING
/* Sets up one player's object: models, motions and the team's tower. */
void func_80108880_awful_tower(omObjData* obj, u32 arg1, s32 arg2, u16 idx, f32 x, f32 y, f32 z) {
    AtTbl8 tbl = D_8010CD34_awful_tower;
    MgWork* w;
    AtPlayer* p;
    s32 chr;
    s32* pair;
    s32 i;

    chr = (s8)D_8010D308_awful_tower[idx]->unk00;
    func_800E18D8_minigame();
    func_800E1BA8_minigame(obj, arg1, arg2, D_8010D308_awful_tower[idx]->unk01, 0x4B9, 0x49D);
    pair = &D_8010CB60_awful_tower[idx];
    func_8001C8A8_main(obj->model[0], *pair);
    w = obj->data;
    w->unk59 = D_8010D308_awful_tower[idx]->unk01;
    w->unk50 |= 0x400;
    w->unk4C = 1.0f;
    w->unkB4 = 1.0f;
    obj->model[6] = func_8000B108_main(5, 0x80D);
    func_8001C8A8_main(obj->model[6], *pair);
    func_8001C8A8_main(obj->model[9], *pair);
    p = D_8010D308_awful_tower[idx];
    p->unk08 = (rand8() & 1) ? 0x2F : 0x30;
    obj->model[10] = func_8000B108_main(func_80017BB8_main(chr, (s16)D_8010D308_awful_tower[idx]->unk08), 0x4B9 | 4);
    D_8010D308_awful_tower[idx]->unk08 |= tbl.v[(u16)chr] << 16;
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(obj, 17, func_80017BB8_main(chr, 14), 1, 15);
    func_800E5978_minigame(obj, 21, func_80017BB8_main(chr, 31), 0, 0);
    func_800E5978_minigame(obj, 30, func_80017BB8_main(chr, 32), 2, 0);
    func_800E5978_minigame(obj, 31, func_80017BB8_main(chr, 33), 2, 0);
    func_800E5978_minigame(obj, 32, func_80017BB8_main(chr, 34), 0, 0);
    func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, 58), 1, 120);
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, z);
    i = 0;
    while (i++ < 12) {
        func_800E149C_minigame(obj, i, 1);
    }
    func_800E149C_minigame(obj, 0, 2);
    func_800E149C_minigame(obj, idx * 3 + 1, 2);
    func_800E149C_minigame(obj, idx * 3 + 2, 2);
    func_800E149C_minigame(obj, idx * 3 + 3, 2);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108880_awful_tower);
#endif

#ifdef NON_MATCHING
/* Player 0 object setup. */
void func_80108CCC_awful_tower(omObjData* obj) {
    s32 chr = D_8010D308_awful_tower[0]->unk00;

    func_80108880_awful_tower(obj, D_800A178C_main[chr][0], D_800A1790_main[chr][0], 0, 0.0f, 0.0f, 0.0f);
    obj->func = func_80108E8C_awful_tower;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108CCC_awful_tower);
#endif

#ifdef NON_MATCHING
/* Player 1 object setup. */
void func_80108D3C_awful_tower(omObjData* obj) {
    s32 chr = D_8010D308_awful_tower[1]->unk00;

    func_80108880_awful_tower(obj, D_800A178C_main[chr][0], D_800A1790_main[chr][0], 1, 0.0f, 0.0f, 0.0f);
    obj->func = func_80108E8C_awful_tower;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108D3C_awful_tower);
#endif

#ifdef NON_MATCHING
/* Player 2 object setup. */
void func_80108DAC_awful_tower(omObjData* obj) {
    s32 chr = D_8010D308_awful_tower[2]->unk00;

    func_80108880_awful_tower(obj, D_800A178C_main[chr][0], D_800A1790_main[chr][0], 2, 0.0f, 0.0f, 0.0f);
    obj->func = func_80108E8C_awful_tower;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108DAC_awful_tower);
#endif

#ifdef NON_MATCHING
/* Player 3 object setup. */
void func_80108E1C_awful_tower(omObjData* obj) {
    s32 chr = D_8010D308_awful_tower[3]->unk00;

    func_80108880_awful_tower(obj, D_800A178C_main[chr][0], D_800A1790_main[chr][0], 3, 0.0f, 0.0f, 0.0f);
    obj->func = func_80108E8C_awful_tower;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108E1C_awful_tower);
#endif

#ifndef NON_MATCHING /* func_80108E8C_awful_tower's local tables */
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CEE0_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CEF0_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF30_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF40_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF48_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF64_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF68_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF74_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF7C_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF88_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF8C_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF90_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF94_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CFDC_awful_tower);
#endif

#ifdef NON_MATCHING
#define AT_ABS(x) ((x) > 0 ? (x) : -(x))

/* Player object: per-frame update of one team's climber. Animates the tower floors (team 0), picks the nearest
   floors for the team's three ground objects, drives the CPU (fake pad input), the team's falling hazard, coins,
   the camera height and the finish. */
void func_80108E8C_awful_tower(omObjData* obj) {
    MgWork* w = obj->data;
    s16 team = D_8010D3CC_awful_tower[w->unk59];
    u8 ctrlSave = 0xFF;
    u8 lane[16] = { 0, 2, 1, 1, 0, 0, 2, 1, 2, 2, 1, 0, 1, 2, 2, 0 };
    f32 floorY[16] = { 45.0f,   250.0f,  615.0f,  950.0f,  1100.0f, 1350.0f, 1600.0f, 1800.0f,
                       2150.0f, 2450.0f, 2850.0f, 3150.0f, 3400.0f, 3700.0f, 3950.0f, 4500.0f };
    u8 column[16] = { 0, 1, 2, 1, 0, 1, 2, 0, 1, 0, 1, 2, 1, 0, 2, 1 };
    u8 near7[7] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    f32 near7d[7] = { 32000.0f, 32000.0f, 32000.0f, 32000.0f, 32000.0f, 32000.0f, 32000.0f };
    u8 near3[3] = { 0xFF, 0xFF, 0xFF };
    f32 near3d[3] = { 32000.0f, 32000.0f, 32000.0f };
    u8 coinNear[5];
    omObjData** grounds;
    MgWork* w2;
    AtPlayer* p;
    HmfModel* m;
    s32 padNo;
    s16 padBtn;
    u16 padTrg;
    s16 pad1244;
    s8 padX;
    s8 padY;
    s16 pad056A;
    s16 pad1382;
    s32 i;
    s32 j;
    s32 k;
    f32 d;
    f32 dx;
    f32 dy;
    f32 tx;
    f32 ty;
    f32 vx;
    f32 vy;
    f32 wob;
    s32 floor;
    u8 n;
    u8 cpuRate;
    s32 frame;
    s32 best;
    s32 sel;
    s32 r;
    s32 bits;
    u8* state;

    p = D_8010D308_awful_tower[team];
    if (D_8010D3E4_awful_tower == 5 && D_8010D3DC_awful_tower == 1) {
        D_8010CC00_awful_tower[team] = D_8010CBFC_awful_tower[team];
        w->unk3C = 0.0f;
    }

    /* Team 0 moves the tower's floors: each lane swings with its own period and amplitude. */
    if (team == 0) {
        s16 period[3] = { 60, 60, 60 };
        f32 phase[3];
        f32 amp[3] = { 150.0f, 200.0f, 300.0f };

        if (D_8010CBE8_awful_tower == 40) {
            for (i = 0; i < 15; i++) {
                D_8010D110_awful_tower[i] = 0.0f;
            }
            for (i = 0; i < 55; i++) {
                D_8010D1F0_awful_tower[i] = -1.0f;
            }
        }
        for (i = 0; i < 3; i++) {
            phase[i] = ((D_8010CBE8_awful_tower % period[i] < period[i] / 2
                             ? D_8010CBE8_awful_tower % period[i]
                             : period[i] - D_8010CBE8_awful_tower % period[i]) * 2.0) / period[i] * amp[i];
        }
        for (i = 0; i < 15; i++) {
            D_8010D0D0_awful_tower[i] =
                floorY[i] + (!(i & 1) ? phase[lane[i]] : amp[lane[i]] - phase[lane[i]]);
            D_8010D110_awful_tower[i] += D_8010D0D0_awful_tower[i];
        }
    }

    /* The pad is saved here and restored at the end: the CPU writes fake input into it. */
    padNo = p->unk03;
    padBtn = D_800CDA7C_main[padNo];
    padTrg = D_800D5558_main[padNo];
    pad1244 = D_800D1244_main[padNo];
    padX = D_800CBB6E_main[padNo];
    padY = D_800D20A1_main[padNo];
    pad056A = D_800D056A_main[padNo];
    pad1382 = D_800D1382_main[padNo];
    D_800D1382_main[padNo] = 0;
    D_800D20A1_main[padNo] = 0;

    /* Ride the floor the player stands on. */
    if (D_8010CC04_awful_tower[team] != 0 && D_8010D110_awful_tower[D_8010CC04_awful_tower[team]] < 0.0f) {
        obj->trans.y += D_8010D110_awful_tower[D_8010CC04_awful_tower[team]];
        D_8010CC28_awful_tower[team] = D_8010CC04_awful_tower[team];
        if (w->unk38 < 0.0) {
            w->unk38 = 0.25f;
        }
    }
    if (D_8010CC28_awful_tower[team] != 0 && D_8010CC70_awful_tower[team] == 0 &&
        obj->trans.y + 155.0f >= D_8010D0D0_awful_tower[D_8010CC28_awful_tower[team]] - 50.0f) {
        obj->trans.y = D_8010D0D0_awful_tower[D_8010CC28_awful_tower[team]] + -155.0f - 50.0f;
    }

    /* The seven floors nearest the team's camera height, nearest first. */
    for (i = 0; i < 15; i++) {
        d = AT_ABS(D_8010D0D0_awful_tower[i] - D_8010D320_awful_tower[team]);
        for (j = 0; j < 7; j++) {
            if (d < near7d[j]) {
                for (k = 5; k >= j; k--) {
                    near7[k + 1] = near7[k];
                    near7d[k + 1] = near7d[k];
                }
                near7[j] = i;
                near7d[j] = d;
                break;
            }
        }
    }
    /* Of those, the three nearest the player: they get the team's ground objects. */
    for (i = 0; i < 7; i++) {
        d = AT_ABS(D_8010D0D0_awful_tower[near7[i]] - (obj->trans.y + 75.0));
        for (j = 0; j < 3; j++) {
            if (d < near3d[j]) {
                for (k = 2; k >= j; k--) {
                    near3[k + 1] = near3[k];
                    near3d[k + 1] = near3d[k];
                }
                near3[j] = near7[i];
                near3d[j] = d;
                break;
            }
        }
    }
    grounds = D_8010D360_awful_tower[team];
    for (i = 0; i < 3; i++) {
        omSetTra(grounds[i], column[near3[i]] * 150 - 150, D_8010D0D0_awful_tower[near3[i]], 0.0f);
        if (near3[i] == 0) {
            func_800E13CC_minigame(grounds[i], 50.0f, 300.0f, -150.0f, -50.0f, 50.0f, 50.0f);
        } else {
            func_800E13CC_minigame(grounds[i], 50.0f, 100.0f, -50.0f, -50.0f, 50.0f, 50.0f);
        }
        for (j = 0; j < 3; j++) {
            func_8001C258_main(grounds[i]->model[j + 1], 4, 4);
        }
        if (team == 0) {
            func_8001C258_main(D_8010D3E8_awful_tower->model[20], 4, 4);
            func_8001C8A8_main(D_8010D3E8_awful_tower->model[20], 0);
        }
    }

    /* Show the seven nearest floors' models, at most three per lane; the top floor has its own model. */
    {
        u8 used[3] = { 0, 0, 0 };

        for (i = 0; i < 7; i++) {
            floor = near7[i];
            k = lane[floor];
            if (used[k] < 3) {
                if (floor == 14) {
                    Hu3DModelPosSet(D_8010D3E8_awful_tower->model[20], column[14] * 150 - 150,
                                    D_8010D0D0_awful_tower[14], 0.0f);
                    func_8001C258_main(D_8010D3E8_awful_tower->model[20], 4, 0);
                    HmfModelData[D_8010D3E8_awful_tower->model[20]].unk01 |= D_8010CB60_awful_tower[team];
                } else {
                    Hu3DModelPosSet(D_8010D360_awful_tower[team][k]->model[used[k] + 1], column[floor] * 150 - 150,
                                    D_8010D0D0_awful_tower[floor], 0.0f);
                    func_8001C258_main(D_8010D360_awful_tower[team][k]->model[used[k] + 1], 4, 0);
                }
                used[k]++;
            }
        }
    }

    /* The team's falling hazard. */
    if (D_8010CC18_awful_tower[team] > -1000.0f) {
        D_8010D1B0_awful_tower[team] -= 4.0f;
        D_8010D190_awful_tower[team] += D_8010D1A0_awful_tower[team];
        D_8010CC18_awful_tower[team] += D_8010D1B0_awful_tower[team];
        D_8010D1C0_awful_tower[team] += D_8010D1D0_awful_tower[team];
        Hu3DModelPosSet(D_8010D3E8_awful_tower->model[16 + team], D_8010D190_awful_tower[team],
                        D_8010CC18_awful_tower[team], 0.0f);
        Hu3DModelRotSet(D_8010D3E8_awful_tower->model[16 + team], 0.0f, 0.0f, D_8010D1C0_awful_tower[team]);
        dx = D_8010D190_awful_tower[team] - obj->trans.x;
        dy = (D_8010CC18_awful_tower[team] - obj->trans.y - 75.0f) / 2.0;
        if (D_8010D1E0_awful_tower[team] != 0.0f && (D_8010D3E4_awful_tower == 2 || D_8010D3E4_awful_tower == 6) &&
            dx * dx + dy * dy < 3600.0f) {
            w2 = obj->data;
            w2->unk3C = (obj->trans.y > 3500.0f) ? 90.0f : -90.0f;
            func_800E5690_minigame(obj, 30);
            if (w2->unk38 == 1000.0f) {
                w2->unk40 = -D_800EB760_minigame;
            } else {
                w2->unk40 = -D_800EB760_minigame;
                w2->unk38 = -D_800EB744_minigame * 0.6f;
            }
            func_800E4C88_minigame(obj, 6, (D_8010D190_awful_tower[team] + obj->trans.x) / 2.0,
                                   (D_8010CC18_awful_tower[team] + obj->trans.y + 75.0f) / 2.0, 0.0f, 0.0f, 180.0f);
            func_8004ACE0_main(0x286, w2->unk59);
            func_800E19FC_minigame(w2, 8);
            omVibrate(w2->unk59, 2, 2, 20);
            D_8010D1E0_awful_tower[team] = 0.0f;
        }
    }
    m = &HmfModelData[obj->model[6]];
    if (m->unk40 >= 10.0f) {
        m->unk40 = 0.0f;
        func_8001C258_main(obj->model[6], 4, 4);
    }

    /* CPU players (and the leader's last jump in the finish) drive the pad themselves. */
    if (p->unk04 != -1 ||
        (D_8010D3FC_awful_tower == team && D_8010D3E4_awful_tower == 3 && D_8010D3DC_awful_tower >= 50)) {
        u8 cpuJump[4] = { 8, 9, 12, 14 };
        u8 cpuJitter[4] = { 18, 11, 6, 4 };

        cpuRate = (p->unk04 != -1) ? cpuJump[p->unk04] : 16;
        if (D_8010CBE8_awful_tower % 60 == 0) {
            D_8010CC78_awful_tower[team] = (p->unk04 != -1) ? (rand8() % cpuJitter[p->unk04]) - (cpuJitter[p->unk04] >> 1)
                                                            : 0;
        }
        D_800CDA7C_main[p->unk03] = 0;
        D_800D5558_main[p->unk03] = 0;
        D_800D1244_main[p->unk03] = 0;
        D_800CBB6E_main[p->unk03] = 0;
        D_800D20A1_main[p->unk03] = 0;
        D_800D056A_main[p->unk03] = 0;
        D_800D1382_main[p->unk03] = 0;
        if (D_8010CC40_awful_tower[team] != 0 && D_8010CBFC_awful_tower[team] != -1 &&
            D_8010CBFC_awful_tower[team] != D_8010CC3C_awful_tower[team] - 1 &&
            D_8010CBFC_awful_tower[team] != D_8010CC3C_awful_tower[team]) {
            D_8010CC40_awful_tower[team] = 0;
        }
        if (D_8010D3E4_awful_tower == 2) {
            if (D_8010CBE8_awful_tower % 60 == D_8010CC7C_awful_tower[D_8010CBFC_awful_tower[team]] +
                                                   (D_8010CC78_awful_tower[team] + ((D_8010CBFC_awful_tower[team] & 1) ? 20 : 50))) {
                if ((D_8010CC40_awful_tower[team] == 0 || D_8010CBFC_awful_tower[team] == D_8010CC3C_awful_tower[team]) &&
                    D_8010CBFC_awful_tower[team] != -1) {
                    n = D_8010CCA4_awful_tower[team];
                    D_8010CCA4_awful_tower[team] = (n >= 5) ? n : n + 1;
                }
            }
            if (D_8010D3E4_awful_tower == 2 && ((rand8() & 0xF) < cpuRate || D_8010CCA4_awful_tower[team] >= 5)) {
                if (D_8010CBE8_awful_tower % 60 == D_8010CC7C_awful_tower[D_8010CBFC_awful_tower[team]] +
                                                   (D_8010CC78_awful_tower[team] + ((D_8010CBFC_awful_tower[team] & 1) ? 20 : 50))) {
                    if ((D_8010CC40_awful_tower[team] == 0 ||
                         D_8010CBFC_awful_tower[team] == D_8010CC3C_awful_tower[team]) &&
                        D_8010CBFC_awful_tower[team] != -1) {
                        D_8010CC40_awful_tower[team] = 1;
                        D_8010CC3C_awful_tower[team] = D_8010CBFC_awful_tower[team] + 1;
                        D_8010CCA4_awful_tower[team] = 0;
                    }
                }
            }
        }
        if (D_8010D3E4_awful_tower == 3 && D_8010D3FC_awful_tower == team &&
                   D_8010CBE8_awful_tower % 60 == 27 && D_8010D3DC_awful_tower >= 40 &&
                   (D_8010CC40_awful_tower[D_8010D3FC_awful_tower] == 0 ||
                    D_8010CBFC_awful_tower[D_8010D3FC_awful_tower] == D_8010CC3C_awful_tower[D_8010D3FC_awful_tower]) &&
                   D_8010CBFC_awful_tower[team] == 15) {
            D_8010CC40_awful_tower[team] = 1;
            D_8010CC3C_awful_tower[team] = D_8010CBFC_awful_tower[team] + 1;
            D_8010CC44_awful_tower = 1;
            D_8010CC48_awful_tower = obj->trans.x;
        }
        /* A jump in progress: press A on its first frame, hold it after. */
        if (D_8010CC40_awful_tower[team] == D_8010CC8F_awful_tower[D_8010CC3C_awful_tower[team]] + 3) {
            D_800CDA7C_main[p->unk03] |= 0x8000;
            D_800D5558_main[p->unk03] = 0x8000;
        } else if (D_8010CC8F_awful_tower[D_8010CC3C_awful_tower[team]] + 3 < D_8010CC40_awful_tower[team]) {
            D_800CDA7C_main[p->unk03] |= 0x8000;
        }
        /* Steer toward the target floor's column. */
        if (D_8010CC40_awful_tower[team] != 0) {
            dx = (column[D_8010CC3C_awful_tower[team] - 1] * 150 - 150) * 1.125 - obj->trans.x;
            padNo = p->unk03;
            if (dx > 30.0f) {
                D_800CBB6E_main[padNo] = 60;
            } else if (dx > 15.0f) {
                D_800CBB6E_main[padNo] = dx / 7.5 - 1.0;
            } else if (dx < -30.0f) {
                D_800CBB6E_main[padNo] = -60;
            } else if (dx < -15.0f) {
                D_800CBB6E_main[padNo] = dx / 7.5 + 1.0;
            } else {
                D_800CBB6E_main[padNo] = 0;
            }
            D_800D056A_main[p->unk03] = D_800CBB6E_main[p->unk03] * 2;
            D_8010CC40_awful_tower[team]++;
            D_8010CC40_awful_tower[team] %= 60;
            if (D_800CBB6E_main[p->unk03] == 0 && D_8010CBFC_awful_tower[team] == D_8010CC3C_awful_tower[team]) {
                D_8010CC40_awful_tower[team] = 0;
            }
        }
        if (D_8010CBFC_awful_tower[team] == 0) {
            if (obj->trans.x < -40.0f) {
                D_8010CC40_awful_tower[team] = 0;
                D_800CBB6E_main[p->unk03] = 60;
                D_800D056A_main[p->unk03] = D_800CBB6E_main[p->unk03] * 2;
            }
            if (D_8010CBFC_awful_tower[team] == 0 && obj->trans.x > 20.0f) {
                D_8010CC40_awful_tower[team] = 0;
                D_800CBB6E_main[p->unk03] = -60;
                D_800D056A_main[p->unk03] = D_800CBB6E_main[p->unk03] * 2;
            }
        }
        if (D_8010D3E4_awful_tower == 3 && D_8010D3FC_awful_tower == team) {
            ctrlSave = D_8010CB70_awful_tower.unk00;
            D_8010CB70_awful_tower.unk00 = 2;
            w->unk4C = 0.5f;
            w->unkB4 = 1.5f;
        }
    }
    /* The leader reaches the top: the top floor becomes the team's third ground. */
    if (D_8010D3FC_awful_tower == team && ((D_8010D3E4_awful_tower >= 4 && obj->trans.y >= 4550.0f) ||
                                           (D_8010D3E4_awful_tower == 3 && D_8010D3DC_awful_tower >= 30))) {
        omSetTra(D_8010D360_awful_tower[D_8010D3FC_awful_tower][2], 0.0f, 4500.0f, 0.0f);
        near3[2] = 15;
        near3d[2] = 4500.0f;
    }
    if (D_8010CBFC_awful_tower[team] == 15 && (D_8010D3E4_awful_tower != 3 || D_8010D3DC_awful_tower < 30)) {
        D_800CBB6E_main[p->unk03] = 0;
        D_800D056A_main[p->unk03] = 0;
        D_800CDA7C_main[p->unk03] &= 0x7FFF;
        D_800D5558_main[p->unk03] &= 0x7FFF;
        D_800D1244_main[p->unk03] &= 0x7FFF;
    }
    /* Pushed off a ground's side: hold the stick toward it until the player lets go. */
    if (D_8010CC74_awful_tower[team] != 0) {
        if (D_8010CC74_awful_tower[team] ==
            (D_800CBB6E_main[p->unk03] < 0 ? -1 : D_800CBB6E_main[p->unk03] > 0 ? 1 : 0)) {
            D_8010CC74_awful_tower[team] = 0;
            D_800CBB6E_main[p->unk03] = 0;
            D_800D056A_main[p->unk03] = 0;
        }
    }

    /* Coins near the player are collectable if the team has not taken them. */
    for (i = 0; i < 5; i++) {
        AtCoin* cw = D_8010D390_awful_tower[i]->data;

        coinNear[i] = AT_ABS(D_8010D390_awful_tower[i]->trans.y - (obj->trans.y + 160.0)) < 200.0;
        cw->unk54 = D_8010D330_awful_tower[team][i] != 0 && coinNear[i] != 0;
        cw->unk48 = (w->unk38 != 1000.0f) ? 59.0f : 40.0f;
        if (i == 0 && obj->trans.x > 55.0f && obj->trans.y > 1275.0f && obj->trans.y < 1425.0f &&
            w->unk38 >= 1.0f && w->unk38 < 1000.0f) {
            cw->unk48 = 90.0f;
        }
        if (i == 2 && obj->trans.x > 55.0f && obj->trans.y > 2300.0f && obj->trans.y < 2450.0f &&
            w->unk38 >= 1.0f && w->unk38 < 1000.0f) {
            cw->unk48 = 90.0f;
        }
        if (i == 3 && obj->trans.x < -55.0f && obj->trans.y > 3300.0f && obj->trans.y < 3500.0f &&
            w->unk38 >= 1.0f && w->unk38 < 1000.0f) {
            cw->unk48 = 90.0f;
        }
    }
    if (D_8010CC28_awful_tower[team] != 0) {
        D_800CDA7C_main[p->unk03] &= 0x7FFF;
    }
    if (D_8010D3FC_awful_tower >= 4 ||
        (D_8010D3E4_awful_tower != 7 && (D_8010D3E4_awful_tower != 4 || D_8010D3DC_awful_tower < 30))) {
        func_800DDD94_minigame(obj);
    }
    /* Finish: the leader's victory hop. */
    if (D_8010D3E4_awful_tower == 3) {
        if (D_8010CC44_awful_tower >= 12) {
            HuAudFXStop(w->unkC5);
        }
        if (D_8010D3E4_awful_tower == 3 && team == D_8010D3FC_awful_tower && D_8010CC44_awful_tower != 0) {
            f32 finish[18] = { 1.0f,      1.0f,      1.0f,      0.909788f, 0.819576f, 0.729364f, 0.639153f, 0.548941f, 0.458729f,
                               0.368517f, 0.278305f, 0.188094f, 0.097882f, 0.00767f,  0.005113f, 0.002557f, 0.0f,      0.0f };

            obj->trans.x = D_8010CC48_awful_tower * finish[D_8010CC44_awful_tower - 1];
            D_8010CC44_awful_tower = (D_8010CC44_awful_tower != 18) ? D_8010CC44_awful_tower + 1 : 0;
        }
    }
    if (ctrlSave != 0xFF) {
        D_8010CB70_awful_tower.unk00 = ctrlSave;
    }
    func_8001C258_main(obj->model[1], 4, 4);

    /* Pushed against a ground's side. */
    for (i = 0; i < 3; i++) {
        if (w->unk38 != 1000.0f &&
            AT_ABS(obj->trans.x - D_8010D360_awful_tower[team][i]->trans.x) < 110.0f &&
            AT_ABS(obj->trans.y + 75.0f - D_8010D360_awful_tower[team][i]->trans.y) < 125.0f) {
            j = (w->unk3C >= 0.0f && w->unk3C < 180.0f) ? 1 : 0;
            k = (D_8010D360_awful_tower[team][i]->trans.x < obj->trans.x) ? 1 : 0;
            if (j == k) {
                D_8010CC74_awful_tower[team] = j * 2 - 1;
            }
        }
    }

    /* Coins: taken (burst), out of range (2) or back in range (1). Team 3 recolours them for everyone. */
    for (i = 0; i < 5; i++) {
        omObjData* coin = D_8010D390_awful_tower[i];

        if (D_8010D330_awful_tower[team][i] != 0 && coinNear[i] != 0 && ((AtCoin*)coin->data)->unk54 == 0) {
            FxPoolEntry* fx = D_800D6A00_main[D_8010D2CC_awful_tower[team]]->entries;

            func_8000D550_main(D_8010D2CC_awful_tower[team], coin->trans.x, coin->trans.y, coin->trans.z);
            func_8001C8A8_main(fx->model, D_8010CB60_awful_tower[team]);
            D_8010D330_awful_tower[team][i] = 0;
        } else if (D_8010D330_awful_tower[team][i] != 0 &&
                   AT_ABS(D_8010D390_awful_tower[i]->trans.y - D_8010D320_awful_tower[team]) > 900.0f) {
            D_8010D330_awful_tower[team][i] = 2;
        } else if (D_8010D330_awful_tower[team][i] == 2) {
            D_8010D330_awful_tower[team][i] = 1;
        }
        if (team == 3) {
            bits = (D_8010D330_awful_tower[0][i] == 1) ? D_8010CB60_awful_tower[0] : 0;
            if (D_8010D330_awful_tower[1][i] == 1) {
                bits |= D_8010CB60_awful_tower[1];
            }
            if (D_8010D330_awful_tower[2][i] == 1) {
                bits |= D_8010CB60_awful_tower[2];
            }
            if (D_8010D330_awful_tower[3][i] == 1) {
                bits |= D_8010CB60_awful_tower[3];
            }
            func_8001C258_main(D_8010D390_awful_tower[i]->model[0], 4, 0);
            func_8001C8A8_main(D_8010D390_awful_tower[i]->model[0], bits);
        }
    }
    if (D_8010CC00_awful_tower[team] > 0 && func_800E4A80_minigame(obj) == 14) {
        obj->trans.y = D_8010D0D0_awful_tower[D_8010CC00_awful_tower[team] - 1] + 50.0f;
    }

    /* Landing: which floor the player stands on (unk53/unk56 are ground slots, 1-based). */
    w2 = obj->data;
    if (w2->unk38 != 1000.0f && (u8)(w2->unk56 + 1) >= 2 && D_8010CC08_awful_tower[team] == -1) {
        func_8004AC98_main(p->unk00 + 0xCB, w2->unk59);
    }
    D_8010CC08_awful_tower[team] = ((s8)w2->unk56 != 0) ? (s8)w2->unk56 - 1 : -1;
    D_8010CC04_awful_tower[team] = ((u8)(w2->unk56 + 1) >= 2) ? near3[((s8)w2->unk56 - 1) % 3] : 0;
    if ((s8)w2->unk56 >= 0 && w2->unk53 >= 0 && D_8010CC04_awful_tower[team] == near3[(w2->unk53 - 1) % 3] &&
        D_8010CC04_awful_tower[team] < 15) {
        D_8010CC04_awful_tower[team]++;
        D_8010CC70_awful_tower[team] = 1;
    } else {
        D_8010CC70_awful_tower[team] = 0;
    }
    if (w2->unk38 == 1000.0f) {
        D_8010CC28_awful_tower[team] = 0;
    }
    w2->unk56 = -1;
    D_8010CBFC_awful_tower[team] = -1;
    if (w2->unk53 >= 0) {
        D_8010CBFC_awful_tower[team] = (w2->unk53 != 0) ? near3[(w2->unk53 - 1) % 3] + 1 : 0;
        if (D_8010CBFC_awful_tower[team] == 16) {
            D_8010D3FE_awful_tower = (D_8010D3FE_awful_tower >= 255) ? D_8010D3FE_awful_tower : D_8010D3FE_awful_tower + 1;
        }
        floor = (w2->unk53 != 0) ? near3[(w2->unk53 - 1) % 3] : 0;
        if (D_8010D3E4_awful_tower == 2 && (D_8010CC0C_awful_tower[team] == 0 || D_8010CC0C_awful_tower[team] == 3) &&
            floor % 5 == D_8010D3E4_awful_tower) {
            if (D_8010CC0C_awful_tower[team] == 0) {
                D_8010D150_awful_tower[team] = 0.0f;
                D_8010D170_awful_tower[team] = 0.0f;
                D_8010D180_awful_tower[team] = -20.0f;
                D_8010D160_awful_tower[team] = D_8010D320_awful_tower[team] + 900.0f;
                func_8001C258_main(D_8010D3E8_awful_tower->model[8 + team], 4, 0);
            }
            D_8010CC0C_awful_tower[team] = 1;
            D_8010CC10_awful_tower[team] = floor / 5;
            Hu3DModelScaleSet(D_8010D3E8_awful_tower->model[8 + team],
                              (D_8010CC10_awful_tower[team] != 3) ? -6.0525f : 6.0525f, 6.0525f, 6.0525f);
            Hu3DModelScaleSet(D_8010D3E8_awful_tower->model[12 + team],
                              (D_8010CC10_awful_tower[team] != 3) ? -6.0525f : 6.0525f, 6.0525f, 6.0525f);
        }
        if (D_8010CC0C_awful_tower[team] == 2 && (floor % 5 == 0 || floor % 5 == 4)) {
            D_8010CC0C_awful_tower[team] = 3;
        }
    }
    if (obj->trans.x <= -50.0f && obj->trans.y < 15.0f) {
        obj->trans.x = -40.0f;
    }
    if (w2->unk38 != 1000.0) {
        w2->unk4C = (w2->unk38 < -0.05) ? 0.5f : 1.0f;
        w2->unkB4 = (w2->unk38 < -0.05) ? 1.5f : 1.0f;
        D_8010CBEC_awful_tower[team] = obj->trans.x;
    } else {
        w2->unk4C = 1.0f;
        w2->unkB4 = 1.0f;
        D_8010CBEC_awful_tower[team] = 32000.0f;
    }

    /* The team's flying enemy: flies in beside the floor, drops its hazard, flies off. */
    if (D_8010CC0C_awful_tower[team] != 0) {
        f32 hazardY[3] = { 1550.0f, 2650.0f, 3850.0f };

        ty = 0.0f;
        tx = 0.0f;
        switch (D_8010CC0C_awful_tower[team]) {
            case 1:
                tx = (D_8010CC10_awful_tower[team] != 3) ? 100.0f : -100.0f;
                ty = hazardY[D_8010CC10_awful_tower[team]];
                if (D_8010D3E4_awful_tower != 2) {
                    D_8010CC0C_awful_tower[team] = 3;
                } else if (D_8010D160_awful_tower[team] <= ty + 100.0f) {
                    D_8010CC0C_awful_tower[team] = 2;
                } else {
                    break;
                }
                /* fallthrough */
            case 2:
                tx = (D_8010CC10_awful_tower[team] != 3) ? 100.0f : -100.0f;
                ty = hazardY[D_8010CC10_awful_tower[team]];
                frame = ((D_8010CC10_awful_tower[team] == 0) ? 33 : (D_8010CC10_awful_tower[team] == 1) ? 10 : 41) -
                        D_8010CC4C_awful_tower[team];
                if (frame < 0) {
                    frame += 60;
                }
                if (D_8010CBE8_awful_tower % 60 == frame && D_8010CC14_awful_tower[team] == 0) {
                    D_8010CC14_awful_tower[team] = 1;
                    D_8010CC4C_awful_tower[team] =
                        (D_8010CC4C_awful_tower[team] >= 30) ? D_8010CC4C_awful_tower[team] : D_8010CC4C_awful_tower[team] + 5;
                    func_80014850_main(D_8010D348_awful_tower[team][1]);
                    func_8001C258_main(D_8010D3E8_awful_tower->model[8 + team], 4, 4);
                }
                if (D_8010D3E4_awful_tower != 2) {
                    D_8010CC0C_awful_tower[team] = 3;
                }
                /* fallthrough */
            case 3:
                if (D_8010D320_awful_tower[team] + 900.0f <= D_8010D160_awful_tower[team] ||
                    D_8010D150_awful_tower[team] >= 700.0f || D_8010D150_awful_tower[team] <= -700.0f) {
                    D_8010CC14_awful_tower[team] = 0;
                    D_8010CC0C_awful_tower[team] = 0;
                    D_8010CC4C_awful_tower[team] = 0;
                    func_8001C258_main(D_8010D3E8_awful_tower->model[8 + team], 4, 4);
                    func_8001C258_main(D_8010D3E8_awful_tower->model[12 + team], 4, 4);
                } else if (D_8010CC0C_awful_tower[team] == 3) {
                    tx = (D_8010CC10_awful_tower[team] == 2) ? -1000.0f : 1000.0f;
                    ty = D_8010D320_awful_tower[team] + 1200.0f;
                }
                break;
        }
        /* Retail tests the array's address here (always true). */
        state = D_8010CC0C_awful_tower;
        if (state != NULL) {
            wob = D_8010D1F0_awful_tower[D_8010CBE8_awful_tower % 55];
            vx = (tx - D_8010D150_awful_tower[team]) / 8.0f;
            vx = (vx < -22.0f) ? -22.0f : (vx > 22.0f) ? 22.0f : vx;
            vy = (ty - D_8010D160_awful_tower[team]) / 12.0f;
            vy = (vy < -27.0f) ? -27.0f : (vy > 27.0f) ? 27.0f : vy;
            D_8010D170_awful_tower[team] =
                (vx < D_8010D170_awful_tower[team])
                    ? ((D_8010D170_awful_tower[team] - 2.5 < vx) ? vx : D_8010D170_awful_tower[team] - 2.5)
                    : ((vx < D_8010D170_awful_tower[team] + 2.5) ? vx : D_8010D170_awful_tower[team] + 2.5);
            D_8010D180_awful_tower[team] =
                (vy < D_8010D180_awful_tower[team])
                    ? ((D_8010D180_awful_tower[team] - 2.5 < vy) ? vy : D_8010D180_awful_tower[team] - 2.5)
                    : ((vy < D_8010D180_awful_tower[team] + 2.5) ? vy : D_8010D180_awful_tower[team] + 2.5);
            D_8010D150_awful_tower[team] += D_8010D170_awful_tower[team];
            D_8010D160_awful_tower[team] += D_8010D180_awful_tower[team];
            if (wob == -1.0f) {
                wob = D_8010D1F0_awful_tower[D_8010CBE8_awful_tower % 55] =
                    cosdf(D_8010CBE8_awful_tower % 55 / 55.0 * 360.0);
            }
            wob *= 15.0f;
            Hu3DModelPosSet(D_8010D3E8_awful_tower->model[8 + team], D_8010D150_awful_tower[team],
                            wob + D_8010D160_awful_tower[team], 0.0f);
            Hu3DModelPosSet(D_8010D3E8_awful_tower->model[12 + team], D_8010D150_awful_tower[team],
                            wob + D_8010D160_awful_tower[team], 0.0f);
            if (D_8010CC14_awful_tower[team] != 0) {
                if (D_8010CC14_awful_tower[team] == 12) {
                    D_8010CC14_awful_tower[team] = 0;
                    func_80014850_main(D_8010D348_awful_tower[team][0]);
                    func_8001C258_main(D_8010D3E8_awful_tower->model[12 + team], 4, 4);
                } else {
                    D_8010CC14_awful_tower[team]++;
                    if (D_8010CC14_awful_tower[team] == 8 && D_8010CC18_awful_tower[team] <= -1000.0f) {
                        D_8010D1E0_awful_tower[team] = 1.0f;
                        D_8010D190_awful_tower[team] = D_8010D150_awful_tower[team];
                        D_8010CC18_awful_tower[team] = D_8010D160_awful_tower[team];
                        D_8010D1A0_awful_tower[team] = D_8010CCA8_awful_tower[D_8010CC10_awful_tower[team]];
                        D_8010D1B0_awful_tower[team] = D_8010CCB4_awful_tower[D_8010CC10_awful_tower[team]];
                        D_8010D1C0_awful_tower[team] = 0.0f;
                        D_8010D1D0_awful_tower[team] = (D_8010CC10_awful_tower[team] != 3) ? 23.0f : -23.0f;
                        func_8001C258_main(D_8010D3E8_awful_tower->model[16 + team], 4, 0);
                        Hu3DModelPosSet(D_8010D3E8_awful_tower->model[16 + team], D_8010D190_awful_tower[team],
                                        D_8010CC18_awful_tower[team], 0.0f);
                        Hu3DModelRotSet(D_8010D3E8_awful_tower->model[16 + team], 0.0f, 0.0f,
                                        D_8010D1C0_awful_tower[team]);
                    }
                }
            }
        }
    }

    /* Standing on a floor near the middle: snap back across x = 0 jitter. */
    if (D_8010CC04_awful_tower[team] != 0) {
        if (obj->trans.x < 5.0f && obj->trans.x > 0.0f && obj->trans.x - D_8010CC60_awful_tower[team] < -20.0f &&
            D_8010CC60_awful_tower[team] - D_8010CC50_awful_tower[team] > 10.0f) {
            obj->trans.x = D_8010CC60_awful_tower[team];
        }
        if (obj->trans.x > -5.0f && obj->trans.x < 0.0f && obj->trans.x - D_8010CC60_awful_tower[team] > 20.0f &&
            D_8010CC60_awful_tower[team] - D_8010CC50_awful_tower[team] < -10.0f) {
            obj->trans.x = D_8010CC60_awful_tower[team];
        }
    }
    D_8010CC50_awful_tower[team] = D_8010CC60_awful_tower[team];
    D_8010CC60_awful_tower[team] = obj->trans.x;
    obj->trans.x = (obj->trans.x < -175.0f) ? -175.0f : (obj->trans.x > 175.0f) ? 175.0f : obj->trans.x;

    /* The team's camera height follows the player. */
    if (D_8010D320_awful_tower[team] < obj->trans.y) {
        D_8010D320_awful_tower[team] = obj->trans.y;
    }
    if (obj->trans.y < D_8010D320_awful_tower[team] - 300.0f) {
        D_8010D320_awful_tower[team] = obj->trans.y + 300.0f;
    }
    if (D_8010D320_awful_tower[team] < 650.0f) {
        D_8010D320_awful_tower[team] = 650.0f;
    }
    obj->trans.z = 0.0f;
    if (D_8010D3E4_awful_tower == 0 && D_8010D3DC_awful_tower <= 90) {
        if (D_8010D3DC_awful_tower <= 75) {
            D_8010D320_awful_tower[team] = (1.0f - (f32)D_8010D3DC_awful_tower / 75.0f) * 3625.0f + 1025.0f;
        }
        if (D_8010D3DC_awful_tower > 75) {
            d = 1.0f - (f32)(D_8010D3DC_awful_tower - 75) / 15.0f;
            D_8010D320_awful_tower[team] = d * 375.0f * d + 650.0f;
        }
    }
    if (D_8010CC18_awful_tower[team] > -1000.0f && (D_8010CC18_awful_tower[team] < D_8010D320_awful_tower[team] - 850.0f ||
                                                    D_8010D320_awful_tower[team] + 850.0f < D_8010CC18_awful_tower[team])) {
        D_8010CC18_awful_tower[team] = -1000.0f;
        func_8001C258_main(D_8010D3E8_awful_tower->model[16 + team], 4, 4);
    }
    D_800D54FC_main[team][0] = D_8010D320_awful_tower[team];

    D_800CDA7C_main[p->unk03] = padBtn;
    D_800D5558_main[p->unk03] = padTrg;
    D_800D1244_main[p->unk03] = pad1244;
    D_800CBB6E_main[p->unk03] = padX;
    D_800D20A1_main[p->unk03] = padY;
    D_800D056A_main[p->unk03] = pad056A;
    D_800D1382_main[p->unk03] = pad1382;

    /* Team 3 runs last: advance the frame and pick the finish leader. */
    if (team == 3) {
        D_8010CBE8_awful_tower++;
        for (i = 0; i < 15; i++) {
            D_8010D110_awful_tower[i] = -D_8010D0D0_awful_tower[i];
        }
        if (D_8010D3FC_awful_tower == 5) {
            best = -1;
            sel = -1;
            for (i = 0; i < 4; i++) {
                if (D_8010CBFC_awful_tower[i] == 15 && D_8010CC2C_awful_tower[i] <= D_8010D3A8_awful_tower[i]->trans.x) {
                    r = rand8();
                    if (best < r) {
                        sel = i;
                        best = r;
                    }
                }
            }
            if (sel >= 0) {
                D_8010D3FC_awful_tower = sel;
                if (D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.x < 105.0) {
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.x = 105.0f;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (D_8010CBFC_awful_tower[i] == 15) {
                D_8010CC2C_awful_tower[i] = D_8010D3A8_awful_tower[i]->trans.x;
            } else {
                D_8010CC2C_awful_tower[i] = 1000.0f;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108E8C_awful_tower);
#endif

/* Sets a model's animation frame (unk98->unk08 holds an f32). */
void func_8010CB1C_awful_tower(s16 model, s16 frame) {
    HmfModel* m = &HmfModelData[model];

    *(f32*)&m->hmf->unk98->unk08 = frame;
}
