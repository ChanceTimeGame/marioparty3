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
    /* 0x03 */ u8 unk03; /* pad */
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

typedef struct AtPair {
    s16 unk00;
    s16 unk02;
} AtPair;

extern AtPair D_8010CB60_awful_tower[4];
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
extern const AtRect D_8010CDC0_awful_tower;
extern const AtTbl3 D_8010CDD0_awful_tower;
extern const AtTbl3 D_8010CDDC_awful_tower;
extern const AtF5 D_8010CDE8_awful_tower;
extern const AtF5 D_8010CDFC_awful_tower;
extern const AtTbl3 D_8010CE10_awful_tower;
extern u16 D_8010D348_awful_tower[4][3];
extern s16 D_8010D3B8_awful_tower[4];
extern u16 D_8010D3D0_awful_tower[4];
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
                                   D_8010CB60_awful_tower[D_8010D3FC_awful_tower].unk02);
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
            func_8001C8A8_main(obj->model[i + b.v[j]], D_8010CB60_awful_tower[i].unk02);
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
                func_8001C8A8_main(D_8010D360_awful_tower[i][j]->model[k + 1], D_8010CB60_awful_tower[i].unk02);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80107734_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE40_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE50_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE60_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE70_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE80_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80107858_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108880_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108CCC_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108D3C_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108DAC_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108E1C_awful_tower);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108E8C_awful_tower);

/* Sets a model's animation frame (unk98->unk08 holds an f32). */
void func_8010CB1C_awful_tower(s16 model, s16 frame) {
    HmfModel* m = &HmfModelData[model];

    *(f32*)&m->hmf->unk98->unk08 = frame;
}
