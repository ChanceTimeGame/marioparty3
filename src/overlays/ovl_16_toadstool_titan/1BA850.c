#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// ts A: Toadstool Titan

typedef func_800E1BA8_minigame_ObjData MgWork;

/* A player's record (D_8010F528, pointed to by D_8010F568) */
typedef struct TtPlayer {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 player; /* GwPlayer index */
    /* 0x02 */ u8 group;
    /* 0x03 */ s8 pad;
    /* 0x04 */ s8 com; /* cpu difficulty, -1 human */
    /* 0x05 */ char unk05;
    /* 0x06 */ s16 unk6; /* func_80017790_main result */
    /* 0x08 */ s16 unk8; /* func_80017AD8_main result */
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ s32 unkC; /* win motion: (group << 16) | 0x2F or 0x30 */
} TtPlayer; /* size 0x10 */

/* omObjData::data of the panels and the stage (the framework's ground object) */
typedef struct TtGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ char unk05[0xAF];
} TtGround; /* size 0xB4 */

/* D_800D6A40_main's work: a copy of src/4BF40.c's SndFadeWork (main's real layout) */
typedef struct SndFadeWork {
    /* 0x00 */ f32* vol;
    /* 0x04 */ f32* volStep;
    /* 0x08 */ f32* vol2;
    /* 0x0C */ f32* vol2Step;
    /* 0x10 */ u8* flags;
    /* 0x14 */ s16 musFade[2];
    /* 0x18 */ s16 musFrames[2];
    /* 0x1C */ f32 musStep[2];
    /* 0x24 */ f32 musMaxVol[2];
    /* 0x2C */ f32 musVol[2];
    /* 0x34 */ s16 fadeInFrames;
} SndFadeWork; /* size 0x38 */

typedef struct { s32 v[6]; } TtTbl6;
typedef struct { s32 v[8]; } TtTbl8;
typedef struct { s32 v[16]; } TtTbl16;
typedef struct { f32 v[9]; } TtTbl9f;

/* .rodata */
extern const s16 D_8010EE80_toadstool_titan[];
extern const TtTbl8 D_8010EECC_toadstool_titan;
extern const TtTbl9f D_8010EF10_toadstool_titan; /* panel x */
extern const TtTbl9f D_8010EF34_toadstool_titan; /* panel z */
extern const TtTbl6 D_8010EF68_toadstool_titan;
extern const TtTbl8 D_8010F218_toadstool_titan;
extern const TtTbl16 D_8010F238_toadstool_titan;

/* .data */
extern u8 D_8010EDA0_toadstool_titan;
extern f32 D_8010EDA4_toadstool_titan; /* viewport rect */
extern f32 D_8010EDA8_toadstool_titan;
extern f32 D_8010EDAC_toadstool_titan;
extern f32 D_8010EDB0_toadstool_titan;
extern u8 D_8010EDB4_toadstool_titan[]; /* debris timers (14) */
extern u8 D_8010EDC4_toadstool_titan[]; /* panel timers (9) */
extern u8 D_8010EDCD_toadstool_titan;
extern s16 D_8010EDCE_toadstool_titan;
extern s16 D_8010EDD0_toadstool_titan;
extern f32 D_8010EDD4_toadstool_titan;
extern f32 D_8010EDD8_toadstool_titan;
extern f32 D_8010EDDC_toadstool_titan;
extern f32 D_8010EDE0_toadstool_titan;
extern u16 D_8010EDE4_toadstool_titan;
extern s16 D_8010EDE8_toadstool_titan[];
extern s32 D_8010EE38_toadstool_titan;
extern u8 D_8010EE3C_toadstool_titan; /* the crown holder is dashing */
extern u8 D_8010EE40_toadstool_titan[4]; /* CPU state */
extern s16 D_8010EE44_toadstool_titan[4]; /* CPU timer / target */
extern s16 D_8010EE4C_toadstool_titan[4]; /* CPU jump timer */
extern f32 D_8010EE54_toadstool_titan[4]; /* CPU aim offset x */
extern f32 D_8010EE64_toadstool_titan[4]; /* CPU aim offset z */

/* .bss */
extern f32 D_8010F3D0_toadstool_titan[14];
extern f32 D_8010F408_toadstool_titan[14];
extern f32 D_8010F440_toadstool_titan[14];
extern f32 D_8010F478_toadstool_titan[14];
extern f32 D_8010F4B0_toadstool_titan[14];
extern f32 D_8010F4E8_toadstool_titan[14];
extern f32 D_8010F520_toadstool_titan;
extern TtPlayer D_8010F528_toadstool_titan[4];
extern TtPlayer* D_8010F568_toadstool_titan[4];
extern u32 D_8010F580_toadstool_titan;
extern u8 D_8010F584_toadstool_titan;
extern s16 D_8010F586_toadstool_titan;
extern s16 D_8010F588_toadstool_titan[1];
extern s8 D_8010F58A_toadstool_titan;
extern f32 D_8010F58C_toadstool_titan;
extern D_80111B50_vine_with_me_Struct D_8010F590_toadstool_titan; /* the minigame control block */
extern f32 D_8010F5B8_toadstool_titan;
extern u16 D_8010F5BC_toadstool_titan;
extern Vec D_8010F5C0_toadstool_titan; /* camera target */
extern omObjData* D_8010F5D0_toadstool_titan[9];
extern u8 D_8010F5F4_toadstool_titan;
extern omObjData* D_8010F5F8_toadstool_titan;
extern s16 D_8010F5FC_toadstool_titan;
extern f32 D_8010F600_toadstool_titan;
extern f32 D_8010F604_toadstool_titan;
extern f32 D_8010F608_toadstool_titan;
extern s16 D_8010F60C_toadstool_titan[1];
extern s8 D_8010F60E_toadstool_titan;
extern f32 D_8010F610_toadstool_titan;
extern u8 D_8010F614_toadstool_titan[2]; /* music started, fanfare started */
extern u8 D_8010F616_toadstool_titan[4];
extern u32 D_8010F61C_toadstool_titan;
extern f32 D_8010F624_toadstool_titan; /* camera fov */
extern Vec D_8010F628_toadstool_titan; /* camera position */
extern u8 D_8010F620_toadstool_titan;
extern s16 D_8010F634_toadstool_titan[];
extern omObjData* D_8010F640_toadstool_titan[4];
extern u8 D_8010F650_toadstool_titan[9];
extern u8 D_8010F659_toadstool_titan[4];
extern u8 D_8010F65D_toadstool_titan[4];
extern f32 D_8010F664_toadstool_titan;
extern u8 D_8010F668_toadstool_titan[4];
extern u8 D_8010F66C_toadstool_titan;
extern f32 D_8010F670_toadstool_titan;

extern u8 D_800D6A90_main;
extern u8 D_800CD6A6_main;
extern s32 D_800EBEB0_minigame[];
extern s32 D_800A178C_main[][6];
extern omObjData* D_800D6A40_main;
extern f32 D_800CE17C_main[];
extern Gfx* gMainGfxPos;
extern Gfx D_8010EDF0_toadstool_titan[]; /* render state for the zoomed screen */
/* main's esprite slot (src/esprite.c D_800CD1DC_main_Struct; no pointer fields) */
typedef struct TtEspr {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04; /* sprite group */
    /* 0x06 */ char unk06[0x1E];
} TtEspr; /* size 0x24 */
extern TtEspr* D_800CD1DC_main;
extern f32 D_800D5210_main;
extern f32 D_800CB890_main;
extern s16 D_800D418E_main;
extern s16 D_800D037E_main;
extern s16 D_800CDA7C_main[];
extern u16 D_800D5558_main[4];
extern s16 D_800D1244_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern s16 D_800D056A_main[];
extern s16 D_800D1382_main[];
extern f32 D_800EB73C_minigame;
extern f32 D_800EB75C_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;

void func_80012B14_main(s16 camIndex, Vec* worldPos, Vec2f* outPos);
void func_80021BE0_main(s32* arg0, s32 n);
u8 func_8000B638_main(void);
void func_80033910_main(HmfData*);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E13CC_minigame(omObjData* obj, f32 arg1, f32 arg2, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E1468_minigame(omObjData* obj);
void func_800E1490_minigame(u16 arg0);
omObjData* func_80045ED0_main(u32 arg0);
void func_80105E50_toadstool_titan(omObjData* obj);
void func_80106984_toadstool_titan(void);
void func_801060AC_toadstool_titan(omObjData* obj);
void func_801069DC_toadstool_titan(omObjData* obj);
void func_80106C98_toadstool_titan(omObjData* obj);
void func_80107360_toadstool_titan(omObjData* obj);
void func_8010B510_toadstool_titan(omObjData* obj);
void func_8010B658_toadstool_titan(omObjData* obj, u32 dir, s32 file, u16 idx, f32 x, f32 y, f32 z);
void func_8010B99C_toadstool_titan(omObjData* obj);
void func_8010BA80_toadstool_titan(omObjData* obj);
void func_8010BB64_toadstool_titan(omObjData* obj);
void func_8010BC48_toadstool_titan(omObjData* obj);
void func_8010BD2C_toadstool_titan(omObjData* obj);
void func_8002367C_main(f32 (*dst)[4], f32 (*src)[4]);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E5138_minigame(omObjData* obj);
void func_800DDD94_minigame(omObjData* obj);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
void func_8010AD8C_toadstool_titan(s16 x0, s16 y0, s16 x1, s16 y1);
void func_8010B4D4_toadstool_titan(s16 mdl, s16 frame);

#define TT_TICK() (func_80049F98_main() + D_800D6A90_main == 0)

void func_801059A0_toadstool_titan(void) {
    omObjData* o;
    s32 i;

    Hu3DAnimInit(50);
    func_80021BE0_main(D_800EBEB0_minigame, 64);
    func_800142A0_main(32);
    omInitObjMan(100, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(1);
    D_800CD6A6_main = func_8000B638_main();
    ScissorSet(D_800CD6A6_main, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(D_800CD6A6_main, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB73C_minigame = 15.0f;
    D_800EB760_minigame = 18.0f;
    D_800EB764_minigame = 13.5f;
    D_800EB768_minigame = 9.0f;
    D_800EB76C_minigame = 4.5f;
    func_800E19F0_minigame(1);
    HmfLightMaxSet(2);
    HmfLightDirSet(0, 0.0f, 73.0f, 95.0f);
    HmfLightColorSet(0, 0x80, 0x80, 0x80);
    HmfLightDirSet(1, 0.0f, 95.0f, 55.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 0.0f, 95.0f, 55.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    omAddObj(0, 0, 0, -1, func_80105E50_toadstool_titan);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = D_8010F5F8_toadstool_titan = o = omAddObj(4, 0x3A, 0x3A, -1, func_80106C98_toadstool_titan);
    omSetStatBit(o, 0xA0);
    for (i = 0; i < 9; i++) {
        D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = D_8010F5D0_toadstool_titan[i] = omAddObj(2, 2, 2, -1, func_801069DC_toadstool_titan);
    }
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[0] = omAddObj(3, 0xC, 0x3C, -1, func_8010B99C_toadstool_titan);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[1] = omAddObj(3, 0xC, 0x3C, -1, func_8010BA80_toadstool_titan);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[2] = omAddObj(3, 0xC, 0x3C, -1, func_8010BB64_toadstool_titan);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[3] = omAddObj(3, 0xC, 0x3C, -1, func_8010BC48_toadstool_titan);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, func_8010B510_toadstool_titan), 0xA0);
    WipeCreateIn(0xFF, 0x1E);
    func_80045010_main(D_8010EE80_toadstool_titan, 1);
    D_8010F590_toadstool_titan.unk01 = 0;
    D_8010F590_toadstool_titan.unk1C = 45;
    D_8010F590_toadstool_titan.unk1E = 1800;
    D_8010F590_toadstool_titan.unk03 = 2;
    D_8010F590_toadstool_titan.unk02 = 1;
    D_8010F590_toadstool_titan.unk22 = 60;
    D_8010F590_toadstool_titan.unk24 = 165;
    D_8010F590_toadstool_titan.unk04 = 0;
    D_8010F590_toadstool_titan.unk05 = 0;
    D_8010F590_toadstool_titan.unk20 = -1;
    func_800E5EA0_minigame(&D_8010F590_toadstool_titan);
}

void func_80105E48_toadstool_titan(void) {
}

void func_80105E50_toadstool_titan(omObjData* obj) {
    s32 i;
    s32 j;
    u8 n;

    D_8010F5BC_toadstool_titan = 0;
    D_8010F5FC_toadstool_titan = 0;
    D_8010F580_toadstool_titan = 0;
    D_8010F58A_toadstool_titan = 5;
    D_8010F584_toadstool_titan = 0;
    D_8010F586_toadstool_titan = 0;
    D_8010F61C_toadstool_titan = 0;
    D_8010F60E_toadstool_titan = -1;
    D_8010F616_toadstool_titan[0] = D_8010F616_toadstool_titan[1] = D_8010F616_toadstool_titan[2] = D_8010F616_toadstool_titan[3] = 0;
    D_8010F5F4_toadstool_titan = 0;
    D_8010F66C_toadstool_titan = 0;
    D_8010F614_toadstool_titan[0] = D_8010F614_toadstool_titan[1] = 0;
    D_8010F600_toadstool_titan = -1.0f;
    for (i = 0; i < 4; i++) {
        D_8010F568_toadstool_titan[i] = &D_8010F528_toadstool_titan[i];
        bzero(D_8010F568_toadstool_titan[i], sizeof(TtPlayer));
    }
    for (i = 0; i < 4; i++) {
        j = D_8010F65D_toadstool_titan[i] = GwPlayer[i].group;
        D_8010F568_toadstool_titan[j]->player = i;
        D_8010F568_toadstool_titan[j]->pad = GwPlayer[i].pad;
        D_8010F568_toadstool_titan[j]->chr = GwPlayer[i].chr;
        D_8010F568_toadstool_titan[j]->group = j;
        D_8010F568_toadstool_titan[j]->com = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
        n = D_8010F66C_toadstool_titan;
        D_8010F66C_toadstool_titan = (D_8010F568_toadstool_titan[j]->com == -1) ? n + 1 : n;
    }
    for (i = 0; i < 4; i++) {
        D_8010F668_toadstool_titan[i] = rand8() & 3;
        for (j = 0; j < i; j++) {
            if (D_8010F668_toadstool_titan[i] == D_8010F668_toadstool_titan[j]) {
                i--;
                break;
            }
        }
    }
    obj->func = func_801060AC_toadstool_titan;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EE80_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EECC_toadstool_titan);

void func_801060AC_toadstool_titan(omObjData* obj) {
    TtTbl8 mot;
    MgWork* w;
    s16 i;

    D_8010F580_toadstool_titan++;
    func_800E6F40_minigame();
    switch (D_8010F5FC_toadstool_titan) {
    case 0:
        if (func_800E6E8C_minigame() == 1) {
            D_8010F5FC_toadstool_titan = 1;
            D_8010F580_toadstool_titan = 0;
        }
        break;
    case 1:
        if (D_8010F580_toadstool_titan == 61 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
            HuAudSeqPlay(0x38);
            D_8010F614_toadstool_titan[0] = 1;
        }
        if (func_800E6E8C_minigame() == 2) {
            D_8010F5FC_toadstool_titan = 2;
            D_8010F580_toadstool_titan = 0;
        }
        break;
    case 2:
        if (D_8010F580_toadstool_titan == 1) {
            func_80106984_toadstool_titan();
        }
        if (D_8010F58A_toadstool_titan != 5 || func_800E6E8C_minigame() == 3) {
            if (D_8010F58A_toadstool_titan == 5) {
                D_8010F5FC_toadstool_titan = 6;
                D_8010F58A_toadstool_titan = 4;
                if (D_8010F586_toadstool_titan == 5) {
                    D_8010F61C_toadstool_titan = 150;
                }
            } else {
                D_8010F5FC_toadstool_titan = 3;
            }
            D_8010F580_toadstool_titan = 0;
        }
        if (D_8010F5FC_toadstool_titan != 3) {
            break;
        }
        /* fallthrough */
    case 3:
        if (D_8010F580_toadstool_titan == 0) {
            if (func_800E6E8C_minigame() != 3) {
                func_800E6F1C_minigame();
            }
            D_8010F590_toadstool_titan.unk06 = 0;
            D_8010F590_toadstool_titan.unk18 = D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->player;
            GwPlayer[D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->player].bonusCoin = 10;
            D_8010F614_toadstool_titan[0] = 0;
            if (D_8010F614_toadstool_titan[1] != 0 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A7C4_main(60);
                D_8010F614_toadstool_titan[1] = 0;
            }
        }
        if (D_8010F580_toadstool_titan == 2) {
            func_800E6F34_minigame(30);
            D_8010F590_toadstool_titan.unk22 = 60;
        }
        if (func_800E6E8C_minigame() == 4) {
            D_8010F5FC_toadstool_titan = 4;
            D_8010F580_toadstool_titan = 0;
        }
        break;
    case 6:
        if (D_8010F580_toadstool_titan == 1) {
            D_8010F590_toadstool_titan.unk06 = 4;
            D_8010F590_toadstool_titan.unk22 = 90;
            D_8010F590_toadstool_titan.unk24 = 144;
            D_8010F614_toadstool_titan[0] = 0;
            if (D_8010F614_toadstool_titan[1] != 0 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A7C4_main(60);
                D_8010F614_toadstool_titan[1] = 0;
            }
        }
        if (D_8010F580_toadstool_titan == 64 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
            func_8004A950_main();
        }
        if (D_8010F580_toadstool_titan == 67 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
            func_8004A72C_main(3);
        }
        if (func_800E6E8C_minigame() == 4) {
            D_8010F5FC_toadstool_titan = 5;
            D_8010F580_toadstool_titan = 0;
        }
        break;
    case 4:
        if (D_8010F580_toadstool_titan == 24 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
            func_8004A950_main();
        }
        if (D_8010F580_toadstool_titan == 27 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
            func_8004A72C_main(3);
        }
        if (D_8010F580_toadstool_titan == 29 && D_8010F586_toadstool_titan == 9) {
            mot = D_8010EECC_toadstool_titan;
            func_80017954_main(D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan]->model[0], 1,
                               mot.v[D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->chr],
                               D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->unk8);
            func_800E5A00_minigame(D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan], 0xD,
                                   func_80017BB8_main(D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->chr, (rand8() & 1) ? 0x2F : 0x30), 1, 0x78);
            func_80045ED0_main(D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->unkC);
            func_800035E8_main(D_800D037E_main);
        }
        if (D_8010F580_toadstool_titan == 30 && D_8010F586_toadstool_titan == 9) {
            func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan], 0xD);
        }
        /* fallthrough */
    case 5:
        if (D_8010F5FC_toadstool_titan == 5) {
            if (D_8010F580_toadstool_titan == 1) {
                for (i = 0; i < 4; i++) {
                    func_800E5A00_minigame(D_8010F640_toadstool_titan[i], 0xE, func_80017BB8_main(D_8010F568_toadstool_titan[i]->chr, 0x3A), 1, 0x78);
                }
                func_800035E8_main(D_800D037E_main);
            }
            if (D_8010F5FC_toadstool_titan == 5 && D_8010F580_toadstool_titan >= 2) {
                for (i = 0; i < 4; i++) {
                    w = D_8010F640_toadstool_titan[i]->data;
                    if (w->unk5C != 0x1000 && w->unk38 == 1000.0f) {
                        w->unk3C = 0.0f;
                        func_800E5690_minigame(D_8010F640_toadstool_titan[i], 0xE);
                    }
                }
            }
        }
        if (func_800E6E8C_minigame() == 5) {
            D_8010F5FC_toadstool_titan = 7;
            D_8010F580_toadstool_titan = 0;
        }
        break;
    case 7:
        if (D_8010F580_toadstool_titan == 1) {
            WipeCreateOut(0, 20);
        } else if (D_8010F580_toadstool_titan >= 32) {
            D_8010F5BC_toadstool_titan = 1;
        }
        break;
    }
    if (D_8010F5BC_toadstool_titan != 0 || D_800D530C_main != 0) {
        if (D_800D530C_main != 0) {
            if (D_8010F584_toadstool_titan == 0) {
                WipeCreateOut(0, 20);
                HuAudSeqFadeOut(20);
                func_8004A7C4_main(20);
                func_8004AB0C_main(20);
            }
            D_8010F584_toadstool_titan++;
            if (D_8010F584_toadstool_titan == 21 && D_800D6A40_main != NULL) {
                func_800035E8_main(D_800CDBC8_main);
                func_800035E8_main(D_800D037E_main);
            }
            if (D_8010F584_toadstool_titan == 23 && D_800D6A40_main != NULL && D_8010F600_toadstool_titan != -1.0f) {
                func_800036E8_main(D_800CDBC8_main, D_8010F600_toadstool_titan);
            }
            if (D_8010F584_toadstool_titan >= 25) {
                func_800035E8_main(D_800CDBC8_main);
                func_800035E8_main(D_800D037E_main);
                omOvlReturnEx(1);
            }
        } else {
            func_800035E8_main(D_800CDBC8_main);
            func_800035E8_main(D_800D037E_main);
            omOvlReturnEx(1);
        }
    }
}

void func_80106984_toadstool_titan(void) {
    SndFadeWork* w;
    f32 vol;

    if (D_800D6A40_main != NULL) {
        w = D_800D6A40_main->data;
        vol = func_800037C4_main(D_800CDBC8_main);
        w->musVol[0] = vol;
        w->musMaxVol[0] = vol;
        D_8010F600_toadstool_titan = vol;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF10_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF34_toadstool_titan);

void func_801069DC_toadstool_titan(omObjData* obj) {
    TtTbl9f xs = D_8010EF10_toadstool_titan;
    TtTbl9f zs = D_8010EF34_toadstool_titan;
    TtGround* gw;

    if (D_8010EDA0_toadstool_titan == 0) {
        obj->model[0] = func_8000B108_main(0x370000, 0xBD);
    } else {
        obj->model[0] = Hu3DModelLink(D_8010F5D0_toadstool_titan[0]->model[0]);
    }
    omSetTra(obj, xs.v[D_8010EDA0_toadstool_titan] * 1.11, 375.0f, zs.v[D_8010EDA0_toadstool_titan] * 1.11 + 20.0);
    omSetSca(obj, 0.6666667f, 0.6666667f, 0.6666667f);
    if (D_8010EDA0_toadstool_titan == 0) {
        obj->model[1] = func_8000B108_main(0x370001, 0xBD);
    } else {
        obj->model[1] = Hu3DModelLink(D_8010F5D0_toadstool_titan[0]->model[1]);
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], 0.6666667f, 0.6666667f, 0.6666667f);
    gw = obj->data = HuMemAllocTag(sizeof(TtGround), 0x7918);
    memset(gw, 0, sizeof(TtGround));
    gw->unk03 = 1;
    func_800E13CC_minigame(obj, 50.0f, 100.0f, -60.0f, -60.0f, 60.0f,
                           (D_8010EDA0_toadstool_titan == 4 || D_8010EDA0_toadstool_titan == 5) ? 120.0f : 60.0f);
    func_800E1304_minigame(obj, 1.0f);
    func_800E1310_minigame(obj, 6.0f);
    gw->unk04 = D_8010EDA0_toadstool_titan + 1;
    D_8010F650_toadstool_titan[D_8010EDA0_toadstool_titan] = 0;
    D_8010EDA0_toadstool_titan++;
    obj->func = NULL;
}

// register allocation: retail keeps 0.5f/0.875f in FPU registers and loads HmfModelData after the index; logic checked
#ifdef NON_MATCHING
void func_80106C98_toadstool_titan(omObjData* obj) {
    s32 sprs[1] = { 0x37000C };
    TtGround* gw;
    s16 i;

    obj->model[0] = -1;
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    gw = obj->data = HuMemAllocTag(sizeof(TtGround), 0x7918);
    memset(gw, 0, sizeof(TtGround));
    gw->unk03 = 1;
    func_800E139C_minigame(obj, 0.0f, -475.0f, -425.0f, 475.0f, 425.0f);
    func_800E1304_minigame(obj, 1.0f);
    func_800E1310_minigame(obj, 6.0f);
    func_800E1468_minigame(obj);
    gw->unk04 = 0;
    for (i = 0; i < 1; i++) {
        D_8010F60C_toadstool_titan[i] = func_8000B838_main(sprs[i]);
        D_8010F588_toadstool_titan[i] = InitEspriteSlot(D_8010F60C_toadstool_titan[i], 0, 0);
        func_8000BB94_main(D_8010F588_toadstool_titan[i]);
    }
    obj->model[1] = func_8000B108_main(0x370002, 0x4BD);
    Hu3DModelScaleSet(obj->model[1], 0.6666667f, 0.6666667f, 0.6666667f);
    Hu3DModelRotSet(obj->model[1], -23.0f, 0.0f, 0.0f);
    obj->model[3] = func_8000B108_main(0x370003, 0x404AD);
    func_8001FA68_main(obj->model[3]);
    for (i = 1; i < 5; i++) {
        obj->model[3 + i] = Hu3DModelLink(obj->model[3]);
    }
    obj->model[2] = func_8000B108_main(0x370003, 0x404AD);
    func_8001FA68_main(obj->model[2]);
    for (i = 0; i < 3; i++) {
        obj->model[26 + i] = func_8000B108_main(0x1001F, 0x8BD);
        Hu3DModelScaleSet(obj->model[26 + i], 2.5f, 2.5f, 2.5f);
        func_8001C2FC_main(obj->model[26 + i], 0x70000000, 0x70000000);
        (HmfModelData + obj->model[26 + i])->unk44 = 1.55f;
    }
    for (i = 0; i < 14; i++) {
        TtTbl6 tbl = D_8010EF68_toadstool_titan;

        if (i < 6) {
            obj->model[29 + i] = func_8000B108_main(tbl.v[(s16)(i % 6)] | 0x370000, 0x4BD);
        } else {
            obj->model[29 + i] = Hu3DModelLink(obj->model[29 + (s16)(i % 6)]);
        }
        func_8001C2FC_main(obj->model[29 + i], 0x70000000, 0x70000000);
        if (i == 0) {
            obj->model[43] = func_8000B108_main(9, 0xBD);
        } else {
            obj->model[43 + i] = Hu3DModelLink(obj->model[43]);
        }
        Hu3DModelScaleSet(obj->model[29 + i], 0.5, 0.5, 0.5);
        Hu3DModelScaleSet(obj->model[43 + i], 0.875, 0.875, 0.875);
    }
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            obj->model[8] = func_8000B108_main(0x37000A, 0x8BD);
        } else {
            obj->model[8 + i] = Hu3DModelLink(obj->model[8]);
        }
        Hu3DModelPosSet(obj->model[8 + i], D_8010F5D0_toadstool_titan[i]->trans.x, D_8010F5D0_toadstool_titan[i]->trans.y + 25.0f,
                        D_8010F5D0_toadstool_titan[i]->trans.z + 125.0f);
        Hu3DModelRotSet(obj->model[8 + i], -23.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[8 + i], 2.5f, 2.5f, 2.5f);
        obj->model[17 + i] = func_8000B108_main(0x37000B, 0x8BD);
        Hu3DModelPosSet(obj->model[17 + i], D_8010F5D0_toadstool_titan[i]->trans.x, D_8010F5D0_toadstool_titan[i]->trans.y - 100.0f,
                        D_8010F5D0_toadstool_titan[i]->trans.z);
        Hu3DModelRotSet(obj->model[17 + i], -23.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[17 + i], 0.75f, 0.75f, 0.75f);
    }
    obj->model[57] = func_8000B108_main(0x37000A, 0x8BD);
    Hu3DModelScaleSet(obj->model[57], 2.0f, 2.0f, 2.0f);
    obj->func = func_80107360_toadstool_titan;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_80106C98_toadstool_titan);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF68_toadstool_titan);

// register allocation, stack layout and scheduling (frame 0x130, obj spilled); logic checked block by block
#ifdef NON_MATCHING
void func_80107360_toadstool_titan(omObjData* obj) {
    Vec2f sa;
    Vec2f sb;
    f32 cx;
    f32 cy;
    Vec a;
    Vec b;
    Vec c;
    f32 mf[4][4];
    s32 i;
    s32 j;
    s32 m;
    s32 cnt;
    s32 k;
    f64 d;
    s16 c2;
    u8 s;
    s32 n;
    f32 f;
    f32 g;
    f32 x;
    f32 y;
    f32 z;
    f32 zoom;
    f32 w;
    f32 h;
    f32 best;
    s8 bi;
    s8 q;
    u8 v;
    MgWork* mw;
    omObjData* p;
    omObjData* p2;
    HmfModel* hm;
    HuCamMtxs* cm;
    s16 k2;

    i = 0;
    if (D_8010F5FC_toadstool_titan == 4 && D_8010F580_toadstool_titan >= 30 && D_8010F580_toadstool_titan < 50) {
        p = D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan];
        b.x = p->trans.x;
        b.y = p->trans.y + 75.0f;
        b.z = p->trans.z;
        a = b;
        c.x = p->trans.x + 25.0f;
        c.y = p->trans.y + 75.0f;
        c.z = p->trans.z;
        b = c;
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        func_80012B14_main(0, &a, &sa);
        func_80012B14_main(0, &b, &sb);
        f = (sb.x - sa.x) * 12.0f;
        sb.x = f + sa.x;
        sa.x = sa.x - f;
        d = (sb.x - sa.x) * 0.75 * 0.5;
        sa.y = sa.y - d;
        sb.y = sb.y + d;
        f = 1.0f - (f32)(D_8010F580_toadstool_titan - 30) / 20.0f;
        f = 1.0f - f * f * f * f;
        g = 1.0f - f;
        sa.x = f * sa.x + g * 0.0f;
        sa.y = f * sa.y + g * 0.0f;
        sb.x = f * sb.x + g * 320.0f;
        sb.y = f * sb.y + g * 240.0f;
        zoom = 320.0f / (sb.x - sa.x);
        if (sa.x < 0.0f) {
            sb.x -= sa.x;
            sa.x -= sa.x;
        }
        if (sa.y < 0.0f) {
            sb.y -= sa.y;
            sa.y -= sa.y;
        }
        if (sb.x > 320.0f) {
            f = sb.x - 320.0f;
            sa.x -= f;
            sb.x -= f;
        }
        if (sb.y > 240.0f) {
            f = sb.y - 240.0f;
            sa.y -= f;
            sb.y -= f;
        }
        cx = (sa.x + sb.x) * 0.5;
        cy = (sa.y + sb.y) * 0.5;
        D_8010EDA4_toadstool_titan = (s32)((0.0f - cx) / (sa.x - cx) * (0.0f - cx) + cx);
        D_8010EDA8_toadstool_titan = (s32)((0.0f - cy) / (sa.y - cy) * (0.0f - cy) + cy);
        D_8010EDAC_toadstool_titan = (s32)((320.0f - cx) / (sb.x - cx) * (320.0f - cx) + cx);
        D_8010EDB0_toadstool_titan = (s32)((240.0f - cy) / (sb.y - cy) * (240.0f - cy) + cy);
        f = 0.0f;
        if (sa.x != 0.0f) {
            f = 0.0f - (sa.x - 0.0f) * zoom;
        }
        D_8010EDA4_toadstool_titan = f;
        f = 0.0f;
        if (sa.y != 0.0f) {
            f = 0.0f - (sa.y - 0.0f) * zoom;
        }
        D_8010EDA8_toadstool_titan = f;
        f = 320.0f;
        if (sb.x != 320.0f) {
            f = 320.0f - (sb.x - 320.0f) * zoom;
        }
        D_8010EDAC_toadstool_titan = f;
        f = 240.0f;
        if (sb.y != 240.0f) {
            f = 240.0f - (sb.y - 240.0f) * zoom;
        }
        D_8010EDB0_toadstool_titan = f;
        w = (s32)(zoom * 640.0f);
        h = (s32)(zoom * 480.0f);
        ViewportSet(0, w, h, 511.0f, (s32)((D_8010EDA4_toadstool_titan + D_8010EDAC_toadstool_titan) / 2.0 * 4.0),
                    (s32)((D_8010EDA8_toadstool_titan + D_8010EDB0_toadstool_titan) / 2.0 * 4.0), 511.0f);
    } else if (D_8010F5F4_toadstool_titan != 0 && D_8010F5F4_toadstool_titan < 13) {
        if (TT_TICK()) {
            f = D_8010F670_toadstool_titan + rand8() / 255.0 * 30.0 - 15.0;
        } else {
            f = D_8010F670_toadstool_titan;
        }
        d = sindf(f) * 0.5;
        if (!(D_8010F5F4_toadstool_titan & 1)) {
            d = d * D_8010F5F4_toadstool_titan;
        } else {
            d = d * -D_8010F5F4_toadstool_titan;
        }
        D_8010EDA4_toadstool_titan = (s16)d;
        D_8010EDAC_toadstool_titan = D_8010EDA4_toadstool_titan + 320.0f;
        d = cosdf(f) * 0.5;
        if (!(D_8010F5F4_toadstool_titan & 1)) {
            d = d * D_8010F5F4_toadstool_titan;
        } else {
            d = d * -D_8010F5F4_toadstool_titan;
        }
        D_8010EDA8_toadstool_titan = (s16)d;
        D_8010EDB0_toadstool_titan = D_8010EDA8_toadstool_titan + 240.0f;
        v = D_8010F5F4_toadstool_titan;
        if (TT_TICK()) {
            v--;
        }
        D_8010F5F4_toadstool_titan = v;
        ViewportSet(0, 640.0f, 480.0f, 511.0f, (s32)((D_8010EDA4_toadstool_titan + D_8010EDAC_toadstool_titan) / 2.0 * 4.0),
                    (s32)((D_8010EDA8_toadstool_titan + D_8010EDB0_toadstool_titan) / 2.0 * 4.0), 511.0f);
    } else if (D_8010F5F4_toadstool_titan == 13) {
        v = 13;
        if (TT_TICK()) {
            v = 12;
        }
        D_8010F5F4_toadstool_titan = v;
    }
    func_8010AD8C_toadstool_titan(D_8010EDA4_toadstool_titan, D_8010EDA8_toadstool_titan, D_8010EDAC_toadstool_titan, D_8010EDB0_toadstool_titan);
    if (!TT_TICK()) {
        return;
    }
    D_8010F61C_toadstool_titan++;
    switch (D_8010F586_toadstool_titan) {
    case 0:
        if (D_8010F61C_toadstool_titan >= 47) {
            D_8010F586_toadstool_titan = 7;
            D_8010F61C_toadstool_titan = 0;
            for (j = 0; j < 4; j++) {
                q = D_8010F568_toadstool_titan[j]->chr;
                D_8010F640_toadstool_titan[j]->model[6] = func_8000B108_main(5, 0x88D);
                D_8010F640_toadstool_titan[j]->model[7] = func_8000B108_main(8, 0x88D);
                D_8010F640_toadstool_titan[j]->model[8] = func_8000B108_main(7, 0x88D);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 1, func_80017BB8_main(q, 1), 1, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 0x12, func_80017BB8_main(q, 0xF), 2, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 2, func_80017BB8_main(q, 2), 1, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 0x11, func_80017BB8_main(q, 0xE), 1, 0xF);
                func_800E5978_minigame(D_8010F640_toadstool_titan[j], 0x1E, func_80017BB8_main(q, 0x20), 2, 0);
                func_800E5978_minigame(D_8010F640_toadstool_titan[j], 0x1F, func_80017BB8_main(q, 0x21), 2, 0);
                func_800E5978_minigame(D_8010F640_toadstool_titan[j], 0x20, func_80017BB8_main(q, 0x22), 0, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 5, func_80017BB8_main(q, 3), 0, 0);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 8, func_80017BB8_main(q, 6), 1, 0x1B);
                func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 0xC, func_80017BB8_main(q, 0x25), 1, 0x78);
            }
        }
        break;
    case 1:
    case 2:
        k = rand8() & 3;
        for (cnt = 0; cnt < 4; cnt++) {
            k = (k + 1) % 4;
            mw = D_8010F640_toadstool_titan[k]->data;
            if (D_8010F586_toadstool_titan == 1 && D_8010F61C_toadstool_titan < 4) {
                if ((u32)(mw->unk56 - 1) < 9 && D_8010F650_toadstool_titan[(s8)mw->unk56 - 1] == 2) {
                    s = rand8() % 9;
                    for (n = 0; n < 9; n++) {
                        m = (s + n) % 9;
                        if (D_8010F650_toadstool_titan[m] == 1) {
                            D_8010F650_toadstool_titan[(s8)mw->unk56 - 1] = 1;
                            D_8010F650_toadstool_titan[m] = 2;
                            break;
                        }
                    }
                }
            }
            if ((u32)(mw->unk56 - 1) < 9 && D_8010F650_toadstool_titan[(s8)mw->unk56 - 1] != 3) {
                s = (s8)mw->unk56 - 1;
                v = D_8010F650_toadstool_titan[s];
                if (v == 2) {
                    mw->unk38 += 0.5;
                    HmfModelData[D_8010F640_toadstool_titan[k]->model[0]].unk0E = HmfModelData[D_8010F640_toadstool_titan[k]->model[0]].unk0C;
                    D_8010F620_toadstool_titan = s;
                    for (j = 0; j < 9; j++) {
                        D_8010F650_toadstool_titan[j] = D_8010F650_toadstool_titan[j] != 0;
                    }
                    D_8010F650_toadstool_titan[s] = 3;
                    D_8010F586_toadstool_titan = 2;
                    D_8010F61C_toadstool_titan = 0;
                    D_8010F60E_toadstool_titan = k;
                } else if (v != 3) {
                    D_8010F650_toadstool_titan[s] = 0;
                    mw->unkC5 = func_8004AC98_main(0x3A5, mw->unk59);
                    mw->unkC4 = -1;
                    for (j = 0; j < 4; j++) {
                        func_800E149C_minigame(D_8010F640_toadstool_titan[j], s + 1, 1);
                    }
                    func_8001C258_main(D_8010F5D0_toadstool_titan[s]->model[0], 4, 4);
                    func_8001C258_main(D_8010F5D0_toadstool_titan[s]->model[1], 4, 4);
                    func_8001C258_main(D_8010F5F8_toadstool_titan->model[17 + s], 4, 0);
                    func_8010B4D4_toadstool_titan(D_8010F5F8_toadstool_titan->model[17 + s], 0);
                    D_8010EDC4_toadstool_titan[s] = 1;
                    for (n = 0, j = 0; n < 4 && j < 14; j++) {
                        if (D_8010EDB4_toadstool_titan[j] == 0) {
                            D_8010EDB4_toadstool_titan[j] = 1;
                            if (!(n & 1)) {
                                D_8010F3D0_toadstool_titan[j] = -25.0f;
                            } else {
                                D_8010F3D0_toadstool_titan[j] = 25.0f;
                            }
                            if (n / 2 == 0) {
                                D_8010F408_toadstool_titan[j] = -25.0f;
                            } else {
                                D_8010F408_toadstool_titan[j] = 25.0f;
                            }
                            D_8010F440_toadstool_titan[j] = rand8() / 255.0 * 50.0 - 25.0;
                            D_8010F478_toadstool_titan[j] = rand8() / 255.0 * 15.0;
                            D_8010F4B0_toadstool_titan[j] = 30.0 - rand8() / 255.0 * 10.0;
                            D_8010F4B0_toadstool_titan[j] = HuSqrtf(D_8010F478_toadstool_titan[j] * D_8010F478_toadstool_titan[j] + D_8010F4B0_toadstool_titan[j] * D_8010F4B0_toadstool_titan[j]);
                            D_8010F4E8_toadstool_titan[j] = rand8() / 255.0 * 20.0;
                            if (D_8010F3D0_toadstool_titan[j] < 0.0f) {
                                D_8010F478_toadstool_titan[j] = -D_8010F478_toadstool_titan[j];
                            }
                            if (D_8010F440_toadstool_titan[j] < 0.0f) {
                                D_8010F4E8_toadstool_titan[j] = -D_8010F4E8_toadstool_titan[j];
                            }
                            D_8010F3D0_toadstool_titan[j] += D_8010F5D0_toadstool_titan[s]->trans.x;
                            D_8010F408_toadstool_titan[j] += D_8010F5D0_toadstool_titan[s]->trans.y;
                            D_8010F440_toadstool_titan[j] += D_8010F5D0_toadstool_titan[s]->trans.z;
                            func_8001C258_main(obj->model[29 + j], 4, 0);
                            func_8001C258_main(obj->model[43 + j], 4, 0);
                            n++;
                        }
                    }
                }
            }
        }
        if (D_8010F586_toadstool_titan == 1) {
            break;
        }
        if (D_8010F61C_toadstool_titan >= 55) {
            D_8010F586_toadstool_titan = 3;
            D_8010F61C_toadstool_titan = 0;
            func_8001C258_main(D_8010F5F8_toadstool_titan->model[1], 4, 4);
            func_8001C258_main(D_8010F5F8_toadstool_titan->model[56], 4, 4);
            func_800036E8_main(D_800CDBC8_main, D_8010F600_toadstool_titan);
            break;
        }
        if (D_8010F61C_toadstool_titan == 35) {
            f = 0.0f;
            for (j = 0; j < 9; j++) {
                if (D_8010F650_toadstool_titan[j] != 0) {
                    f += 1.0f;
                    func_8001C258_main(D_8010F5F8_toadstool_titan->model[8 + j], 4, 0);
                    func_8010B4D4_toadstool_titan(D_8010F5F8_toadstool_titan->model[8 + j], 0);
                }
            }
            D_8010EDCD_toadstool_titan = 1;
            if (f > 0.0f) {
                HuAudFXPlay(0x3A9);
            }
        } else if (D_8010F61C_toadstool_titan == 42) {
            for (j = 0; j < 9; j++) {
                D_8010F650_toadstool_titan[j] = 0;
                for (m = 0; m < 4; m++) {
                    func_800E149C_minigame(D_8010F640_toadstool_titan[m], j + 1, 1);
                }
            }
        } else if (D_8010F61C_toadstool_titan == 45) {
            for (j = 0; j < 9; j++) {
                func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[0], 4, 4);
                func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[1], 4, 4);
            }
        }
        if (D_8010F61C_toadstool_titan < 7) {
            f = 2.0f * (f32)((D_8010F61C_toadstool_titan + 1) / 7.0) - 1.0f;
            f = -(f * f - 1.0f) * 25.0f + 375.0f;
            D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan]->trans.y = f;
            HmfModelData[D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan]->model[0]].pos.y = f;
        } else if (D_8010F61C_toadstool_titan >= 12 && D_8010F61C_toadstool_titan < 45) {
            if (D_8010F61C_toadstool_titan < 35) {
                f = (D_8010F61C_toadstool_titan - 12) / 23.0;
            } else {
                f = 1.0f;
            }
            func_8001C258_main(obj->model[1], 4, 0);
            p = D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan];
            Hu3DModelPosSet(obj->model[1], p->trans.x, f * 75.0f + p->trans.y + 12.5, p->trans.z - 25.0f);
            if (D_8010F61C_toadstool_titan == 12) {
                HuAudFXPlay(0x3A8);
                for (j = 0; j < 4; j++) {
                    mw = D_8010F640_toadstool_titan[k]->data;
                    mw->unkC4 = -1;
                    mw->unkC5 = -1;
                }
            }
        } else if (D_8010F61C_toadstool_titan >= 45) {
            best = 32767.0f;
            bi = -1;
            if (D_8010F61C_toadstool_titan == 45) {
                m = rand8() / 256.0 * 360.0;
                D_8010F610_toadstool_titan = HmfModelData[obj->model[1]].pos.x;
                D_8010F664_toadstool_titan = HmfModelData[obj->model[1]].pos.y;
                D_8010F604_toadstool_titan = HmfModelData[obj->model[1]].pos.z;
                f = m;
                D_8010F5B8_toadstool_titan = cosdf(f) * 7.0f;
                D_8010F608_toadstool_titan = -sindf(f) * 7.0f;
                D_8010F58C_toadstool_titan = 0.0f;
            }
            D_8010F610_toadstool_titan += D_8010F5B8_toadstool_titan;
            D_8010F664_toadstool_titan += D_8010F58C_toadstool_titan;
            D_8010F604_toadstool_titan += D_8010F608_toadstool_titan;
            D_8010F58C_toadstool_titan -= 3.0f;
            if (D_8010F664_toadstool_titan < 50.0f) {
                D_8010F664_toadstool_titan = 50.0f;
                D_8010F58C_toadstool_titan = 0.0f;
            }
            if (D_8010F610_toadstool_titan < -450.0f) {
                D_8010F610_toadstool_titan = -D_8010F610_toadstool_titan - 900.0f;
                D_8010F5B8_toadstool_titan = -D_8010F5B8_toadstool_titan;
            }
            if (D_8010F610_toadstool_titan > 450.0f) {
                D_8010F610_toadstool_titan = -D_8010F610_toadstool_titan + 900.0f;
                D_8010F5B8_toadstool_titan = -D_8010F5B8_toadstool_titan;
            }
            if (D_8010F604_toadstool_titan < -400.0f) {
                D_8010F604_toadstool_titan = -D_8010F604_toadstool_titan - 800.0f;
                D_8010F608_toadstool_titan = -D_8010F608_toadstool_titan;
            }
            if (D_8010F604_toadstool_titan > 400.0f) {
                D_8010F604_toadstool_titan = -D_8010F604_toadstool_titan + 800.0f;
                D_8010F608_toadstool_titan = -D_8010F608_toadstool_titan;
            }
            Hu3DModelPosSet(obj->model[1], D_8010F610_toadstool_titan, D_8010F664_toadstool_titan, D_8010F604_toadstool_titan);
            Hu3DModelPosSet(obj->model[56], D_8010F610_toadstool_titan, 0.0f, D_8010F604_toadstool_titan);
            func_8001C258_main(obj->model[56], 4, 0);
            for (q = 0; q < 4; q++) {
                p = D_8010F640_toadstool_titan[q];
                x = p->trans.x - D_8010F610_toadstool_titan;
                y = (p->trans.y + 75.0f - D_8010F664_toadstool_titan) / 1.75;
                z = p->trans.z - D_8010F604_toadstool_titan;
                f = HuSqrtf(x * x + y * y + z * z);
                if (f <= 100.0f && f < best) {
                    bi = q;
                    best = f;
                }
            }
            if (bi != -1) {
                D_8010F60E_toadstool_titan = bi;
                D_8010F61C_toadstool_titan = 54;
            } else {
                D_8010F61C_toadstool_titan = 46;
            }
            if (D_8010F5FC_toadstool_titan == 5 || D_8010F5FC_toadstool_titan == 6) {
                D_8010F586_toadstool_titan = 9;
                D_8010F61C_toadstool_titan = 0;
                func_8001C258_main(obj->model[1], 4, 4);
                func_8001C258_main(obj->model[56], 4, 4);
                func_8001C258_main(obj->model[57], 4, 0);
                Hu3DModelPosSet(obj->model[57], D_8010F610_toadstool_titan, D_8010F664_toadstool_titan, D_8010F604_toadstool_titan);
                func_8010B4D4_toadstool_titan(obj->model[57], 6);
            }
        }
        break;
    case 3:
        if ((D_8010F5FC_toadstool_titan == 5 || D_8010F5FC_toadstool_titan == 6) && D_8010F61C_toadstool_titan >= 2 && D_8010EDD0_toadstool_titan == 0) {
            D_8010F586_toadstool_titan = 9;
            D_8010F61C_toadstool_titan = 0;
            func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0);
            D_8010EDD0_toadstool_titan = 1;
        }
        if (D_8010F61C_toadstool_titan == 1) {
            D_8010EDCE_toadstool_titan = 1;
            if (D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A670_main(90);
                D_8010F614_toadstool_titan[0] = 0;
            }
            HuAudFXPlay(0x3AB);
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 1.0f, 1.0f, 1.0f);
            if (!(D_8010F5FC_toadstool_titan == 5 || D_8010F5FC_toadstool_titan == 6)) {
                func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0xC);
            }
            func_8001C8E4_main(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->model[0], 0x800);
            for (j = 0; j < 5; j++) {
                func_8001C8E4_main(D_8010F5F8_toadstool_titan->model[3 + j], 0x800);
            }
        } else if (D_8010F61C_toadstool_titan == 46) {
            func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0);
        } else if (D_8010F61C_toadstool_titan >= 55) {
            D_8010F586_toadstool_titan = 4;
            D_8010F61C_toadstool_titan = 0;
            for (j = 0; j < 5; j++) {
                func_8001C8E4_main(D_8010F5F8_toadstool_titan->model[3 + j], 0x400);
            }
        }
        break;
    case 4:
        if (D_8010F61C_toadstool_titan == 3) {
            mw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
            mw->unkC5 = func_8004AC98_main(0x3A7, mw->unk59);
            mw->unkC4 = -1;
            omVibrate(D_8010F568_toadstool_titan[D_8010F60E_toadstool_titan]->player, 10, 0, 10);
        }
        p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
        Hu3DModelScaleSet(p->model[1], p->scale.x, p->scale.y, p->scale.z);
        if (D_8010F61C_toadstool_titan < 24) {
            u8 tbl[8] = { 0, 0, 1, 0, 1, 1, 0, 1 };

            f = tbl[D_8010F61C_toadstool_titan & 7];
            if (D_8010F61C_toadstool_titan >= 12) {
                f = 2.0 - f * 0.5;
            } else {
                f = f * 0.5 + 1.0;
            }
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], f, f, f);
        } else {
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 2.0f, 2.0f, 2.0f);
        }
        if (D_8010F61C_toadstool_titan >= 35) {
            mw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
            if (D_8010F5FC_toadstool_titan == 2) {
                mw->unk50 |= 0x400;
            }
            D_8010F586_toadstool_titan = 5;
            D_8010F61C_toadstool_titan = (D_8010F5FC_toadstool_titan != 2) ? 150 : 0;
            func_8001C8E4_main(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->model[0], 0x400);
            if (D_8010F5FC_toadstool_titan == 2 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_80003A70_main(D_800CDBC8_main);
                func_8004A5C4_main(69);
                D_8010F614_toadstool_titan[1] = 1;
            }
        }
        break;
    case 5:
        omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 2.0f, 2.0f, 2.0f);
        if (D_8010F61C_toadstool_titan >= 150) {
            mw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
            mw->unk50 &= ~0x400;
            D_8010F586_toadstool_titan = 6;
            D_8010F61C_toadstool_titan = 0;
            if (D_8010F5FC_toadstool_titan == 2 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A7C4_main(40);
                D_8010F614_toadstool_titan[1] = 0;
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (D_8010F616_toadstool_titan[i] == 0 && D_8010F60E_toadstool_titan != i && D_8010F5FC_toadstool_titan == 2) {
                    p = D_8010F640_toadstool_titan[i];
                    p2 = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
                    x = p->trans.x - p2->trans.x;
                    y = (p->trans.y - p2->trans.y) * 0.5;
                    z = p->trans.z - p2->trans.z;
                    if (x * x + y * y + z * z < 22500.0f && p->trans.y < 270.0f) {
                        mw = p->data;
                        mw->unk50 |= 0x400;
                        mw->unkC5 = func_8004AC98_main(0x3A6, mw->unk59);
                        mw->unkC4 = -1;
                        omVibrate(D_8010F568_toadstool_titan[i]->player, 20, 0, 20);
                        D_8010F616_toadstool_titan[i] = 1;
                        D_8010F659_toadstool_titan[i] = !(D_8010F640_toadstool_titan[i]->trans.x < D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x);
                        if (D_8010F568_toadstool_titan[i]->com == -1) {
                            D_8010F66C_toadstool_titan--;
                        }
                        for (n = 0, j = 0; j < 4; j++) {
                            n += D_8010F616_toadstool_titan[j] != 0;
                        }
                        if (n == 3) {
                            D_8010F58A_toadstool_titan = D_8010F60E_toadstool_titan;
                            D_8010F61C_toadstool_titan = 120;
                        }
                    }
                }
            }
            i = 0;
        }
        break;
    case 6:
        if (D_8010F61C_toadstool_titan < 24) {
            u8 tbl[8] = { 0, 1, 0, 1, 0, 1, 0, 1 };

            f = tbl[D_8010F61C_toadstool_titan & 7];
            if (D_8010F61C_toadstool_titan >= 6) {
                f = 1.5 - f * 0.5;
            } else {
                f = f * 0.5 + 1.5;
            }
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], f, f, f);
            if (D_8010F61C_toadstool_titan == 1) {
                mw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
                mw->unkC5 = func_8004AC98_main(0x3A4, mw->unk59);
                mw->unkC4 = -1;
            }
        } else {
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 1.0f, 1.0f, 1.0f);
        }
        p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
        Hu3DModelScaleSet(p->model[1], p->scale.x, p->scale.y, p->scale.z);
        if (D_8010F61C_toadstool_titan == 13) {
            if (D_8010F5FC_toadstool_titan == 2) {
                D_8010F586_toadstool_titan = 7;
                D_8010F61C_toadstool_titan = 0;
            } else {
                D_8010F586_toadstool_titan = 9;
                D_8010F61C_toadstool_titan = 0;
                func_800E5A00_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0xD,
                                       func_80017BB8_main(D_8010F568_toadstool_titan[D_8010F60E_toadstool_titan]->chr, (s16)D_8010F568_toadstool_titan[i]->unkC), 1, 0x78);
            }
        }
        break;
    case 7:
        if (D_8010F61C_toadstool_titan == 1) {
            for (j = 0; j < 9; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[8 + j], 4, 0);
                func_8010B4D4_toadstool_titan(D_8010F5F8_toadstool_titan->model[8 + j], 0);
            }
            D_8010EDCD_toadstool_titan = 1;
            HuAudFXPlay(0x3A9);
            if (D_8010F5FC_toadstool_titan == 2 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0 && D_8010F614_toadstool_titan[0] == 0) {
                func_800035E8_main(D_800D037E_main);
                func_80003B70_main(D_800CDBC8_main, 0);
                func_8004A72C_main(35);
                D_8010F614_toadstool_titan[0] = 1;
            }
        }
        if (D_8010F61C_toadstool_titan == 10) {
            D_8010F586_toadstool_titan = 1;
            D_8010F61C_toadstool_titan = 0;
            for (j = 0; j < 9; j++) {
                D_8010F650_toadstool_titan[j] = 1;
                func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[0], 4, 0);
                func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[1], 4, 0);
                for (m = 0; m < 4; m++) {
                    func_800E149C_minigame(D_8010F640_toadstool_titan[m], j + 1, 2);
                }
            }
            s = rand8() % 9;
            do {
                v = rand8() % 9;
            } while (s == v);
            D_8010F650_toadstool_titan[v] = 2;
            D_8010F650_toadstool_titan[s] = 2;
        }
        break;
    case 9:
        if (D_8010F5FC_toadstool_titan >= 3 && D_8010F58A_toadstool_titan < 4 && D_8010F61C_toadstool_titan >= 7) {
            mw = D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan]->data;
            f = mw->unk3C;
            if (f < -10.0f) {
                mw->unk3C = f + 9.0f - f * 0.1;
            } else if (f > 10.0f) {
                mw->unk3C = f - 9.0f - f * 0.1;
            } else {
                mw->unk3C = 0.0f;
            }
        }
        break;
    }
    for (i = 0; i < 4; i++) {
        mw = D_8010F640_toadstool_titan[i]->data;
        mw->unk56 = 0;
        if (D_8010F616_toadstool_titan[i] != 0 && D_8010F616_toadstool_titan[i] < 60) {
            func_800E5690_minigame(D_8010F640_toadstool_titan[i], 0x12);
            HmfModelData[D_8010F640_toadstool_titan[i]->model[0]].unk40 = 0.0f;
            HmfModelData[D_8010F640_toadstool_titan[i]->model[0]].unk44 = 0.0f;
            func_800E4E30_minigame(D_8010F640_toadstool_titan[i]);
            HmfModelData[D_8010F640_toadstool_titan[i]->model[0]].unk0E = HmfModelData[D_8010F640_toadstool_titan[i]->model[0]].unk0C;
            func_800E5138_minigame(D_8010F640_toadstool_titan[i]);
            D_8010F640_toadstool_titan[i]->trans.x += sindf(D_8010F640_toadstool_titan[i]->rot.z) * -50.0f;
            D_8010F640_toadstool_titan[i]->trans.y += cosdf(D_8010F640_toadstool_titan[i]->rot.z) * 50.0f;
            D_8010F640_toadstool_titan[i]->rot.y += 33.0f;
            D_8010F640_toadstool_titan[i]->rot.z += 33.0f;
            D_8010F640_toadstool_titan[i]->rot.x = 0.0f;
            D_8010F640_toadstool_titan[i]->trans.x += D_8010F659_toadstool_titan[i] ? 30.0f : -30.0f;
            if (D_8010F616_toadstool_titan[i] < 14) {
                D_8010F640_toadstool_titan[i]->trans.y += (1.0 - D_8010F616_toadstool_titan[i] / 13.0) * 65.0 + 15.0;
            } else {
                D_8010F640_toadstool_titan[i]->trans.y += 15.0;
            }
            D_8010F640_toadstool_titan[i]->trans.x -= sindf(D_8010F640_toadstool_titan[i]->rot.z) * -50.0f;
            D_8010F640_toadstool_titan[i]->trans.y -= cosdf(D_8010F640_toadstool_titan[i]->rot.z) * 50.0f;
            D_8010F616_toadstool_titan[i]++;
            if (D_8010F616_toadstool_titan[i] == 15) {
                mw->unkC5 = func_8004ACE0_main(0x286, mw->unk59);
                mw->unkC4 = -1;
            }
        }
    }
    for (j = 0; j < 9; j++) {
        if (D_8010EDC4_toadstool_titan[j] != 0) {
            if (D_8010EDC4_toadstool_titan[j] >= 61) {
                D_8010EDC4_toadstool_titan[j] = 0;
                func_8001C258_main(obj->model[17 + j], 4, 4);
            } else {
                D_8010EDC4_toadstool_titan[j]++;
            }
        }
    }
    if (D_8010EDCD_toadstool_titan != 0) {
        if (D_8010EDCD_toadstool_titan >= 19) {
            D_8010EDCD_toadstool_titan = 0;
            for (j = 0; j < 9; j++) {
                func_8001C258_main(obj->model[8 + j], 4, 4);
            }
        } else {
            D_8010EDCD_toadstool_titan++;
        }
    }
    for (j = 0; j < 14; j++) {
        if (D_8010EDB4_toadstool_titan[j] != 0) {
            if (D_8010EDB4_toadstool_titan[j] >= 13) {
                D_8010EDB4_toadstool_titan[j] = 0;
                func_8001C258_main(obj->model[29 + j], 4, 4);
                func_8001C258_main(obj->model[43 + j], 4, 4);
            } else {
                D_8010EDB4_toadstool_titan[j]++;
                D_8010F4B0_toadstool_titan[j] -= 5.0f;
                D_8010F3D0_toadstool_titan[j] += D_8010F478_toadstool_titan[j];
                D_8010F408_toadstool_titan[j] += D_8010F4B0_toadstool_titan[j];
                D_8010F440_toadstool_titan[j] += D_8010F4E8_toadstool_titan[j];
                if (D_8010F408_toadstool_titan[j] < 0.0f) {
                    D_8010F408_toadstool_titan[j] = 0.0f;
                    D_8010F4B0_toadstool_titan[j] = -D_8010F4B0_toadstool_titan[j] * 0.3;
                }
                Hu3DModelPosSet(obj->model[29 + j], D_8010F3D0_toadstool_titan[j], D_8010F408_toadstool_titan[j], D_8010F440_toadstool_titan[j]);
                Hu3DModelPosSet(obj->model[43 + j], D_8010F3D0_toadstool_titan[j], 0.0f, D_8010F440_toadstool_titan[j]);
            }
        }
    }
    if (D_8010EDCE_toadstool_titan != 0 && D_8010EDD0_toadstool_titan == 0) {
        cm = &gCameraList->mtxs[D_800D418E_main];
        D_8010EDDC_toadstool_titan = 0.0f;
        D_8010EDD4_toadstool_titan = 0.0f;
        if (D_8010EDCE_toadstool_titan == 1) {
            func_8001F9E4_main(obj->model[3], 0xFF);
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[3 + j], 4, 0);
            }
        } else if (D_8010EDCE_toadstool_titan == 55) {
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[3 + j], 4, 4);
            }
        }
        if (D_8010EDCE_toadstool_titan >= 1 && D_8010EDCE_toadstool_titan < 55) {
            if (D_8010EDCE_toadstool_titan < 15) {
                f = 1.0 - D_8010EDCE_toadstool_titan / 15.0;
                D_8010EDD4_toadstool_titan = (1.0f - f * f * f) * 100.0f;
            } else {
                D_8010EDD4_toadstool_titan = 90.0f;
            }
            if (D_8010EDCE_toadstool_titan < 45) {
                D_8010EDD4_toadstool_titan += D_8010EDCE_toadstool_titan / 45.0 * 125.0;
            }
            if (D_8010EDCE_toadstool_titan >= 45 && D_8010EDCE_toadstool_titan < 56) {
                f = 1.0 - (D_8010EDCE_toadstool_titan - 45) / 10.0;
                D_8010EDD4_toadstool_titan = 215.0f - (f32)(1.0 - (f * f * 0.75 + f * 0.25)) * 180.0f;
            }
            if (D_8010EDCE_toadstool_titan < 55) {
                D_8010EDD8_toadstool_titan += (f32)(D_8010EDCE_toadstool_titan / 45.0) * 7.0f + 8.0f;
            }
            if (D_8010EDCE_toadstool_titan >= 45 && D_8010EDCE_toadstool_titan < 55) {
                f = 1.0 - (D_8010EDCE_toadstool_titan - 45) / 10.0;
                D_8010EDD8_toadstool_titan += (f32)(1.0 - (f * f * 0.75 + f * 0.25)) * 12.0f;
            }
        }
        if (D_8010EDCE_toadstool_titan == 55) {
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[2], 4, 0);
            }
        } else if (D_8010EDCE_toadstool_titan == 85) {
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[2], 4, 4);
            }
        }
        if (D_8010EDCE_toadstool_titan >= 55 && D_8010EDCE_toadstool_titan < 85) {
            f = 1.0 - (D_8010EDCE_toadstool_titan - 55) / 30.0;
            D_8010EDDC_toadstool_titan = 2.0 * (1.0f - (f32)(f * f * 0.75 + f * 0.25)) + 1.0;
            if (D_8010EDCE_toadstool_titan >= 75) {
                D_8010EDD8_toadstool_titan += 5.0f;
            } else {
                D_8010EDD8_toadstool_titan += (1.0 - (D_8010EDCE_toadstool_titan - 55) / 30.0) * 15.0;
            }
            D_8010EDE0_toadstool_titan = 1.0 - (D_8010EDCE_toadstool_titan - 55) / 30.0;
        }
        if (D_8010EDD4_toadstool_titan > 0.0f) {
            for (j = 0; j < 5; j++) {
                if (D_8010EDCE_toadstool_titan >= 45) {
                    f = (D_8010EDCE_toadstool_titan - 45) / 10.0;
                } else {
                    f = 0.0f;
                }
                g = 1.0f - f;
                p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
                hm = &HmfModelData[obj->model[1]];
                x = f * p->trans.x + g * hm->pos.x;
                y = (p->trans.y + 175.0f) * f + g * hm->pos.y;
                z = (p->trans.z + 85.0f) * f + g * hm->pos.z;
                guMtxL2F(mf, &cm->lookAtMtx);
                h = j * 72;
                func_80017C10_main((Mtx*)mf, cosdf(h + D_8010EDD8_toadstool_titan) * D_8010EDD4_toadstool_titan + x,
                                   sindf(h + D_8010EDD8_toadstool_titan) * D_8010EDD4_toadstool_titan + y, z);
                mf[0][0] = 0.45f;
                mf[0][1] = 0.0f;
                mf[0][2] = 0.0f;
                mf[1][0] = 0.0f;
                mf[1][1] = 0.45f;
                mf[1][2] = 0.0f;
                mf[2][0] = 0.0f;
                mf[2][1] = 0.0f;
                mf[2][2] = 0.45f;
                func_8002367C_main((f32(*)[4])HmfModelData[D_8010F5F8_toadstool_titan->model[3 + j]].mtx, mf);
            }
        }
        if (D_8010EDDC_toadstool_titan > 0.0f) {
            p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
            x = p->trans.x;
            y = p->trans.y + 175.0f;
            z = p->trans.z + 85.0f;
            guMtxL2F(mf, &cm->lookAtMtx);
            func_80017C10_main((Mtx*)mf, x, y, z);
            mf[0][0] = -sindf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mf[0][1] = cosdf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mf[0][2] = 0.0f;
            mf[1][0] = cosdf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mf[1][1] = sindf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mf[1][2] = 0.0f;
            mf[2][0] = 0.0f;
            mf[2][1] = 0.0f;
            mf[2][2] = D_8010EDDC_toadstool_titan;
            func_8002367C_main((f32(*)[4])HmfModelData[D_8010F5F8_toadstool_titan->model[2]].mtx, mf);
            func_8001F9E4_main(obj->model[2], (u32)(D_8010EDE0_toadstool_titan * 255.0f));
        }
        D_8010EDCE_toadstool_titan++;
        if (D_8010EDCE_toadstool_titan == 90) {
            D_8010EDCE_toadstool_titan = 0;
        }
    } else if (D_8010EDD0_toadstool_titan != 0) {
        f = 1.0 - D_8010EDD0_toadstool_titan / 20.0;
        func_8001F9E4_main(obj->model[3], (s32)(f * f * 255.0f));
        D_8010EDD0_toadstool_titan++;
        if (D_8010EDD0_toadstool_titan == 20) {
            D_8010EDD0_toadstool_titan = 0;
            D_8010EDCE_toadstool_titan = 0;
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[3 + j], 4, 4);
            }
        }
    }
    if (D_8010F586_toadstool_titan == 5) {
        c2 = (s16)(D_8010EDE4_toadstool_titan + 1) % 51;
        D_8010EDE4_toadstool_titan = c2;
        if (c2 % 17 == 0) {
            k2 = c2 / 17;
            D_8010EDE8_toadstool_titan[k2] = 0;
            func_8010B4D4_toadstool_titan(obj->model[26 + k2], 0);
            func_8001C258_main(obj->model[26 + k2], 4, 0);
            p = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
            Hu3DModelPosSet(obj->model[26 + k2], p->trans.x * 0.9, 300.0f, p->trans.z - 15.0f);
        }
    } else {
        D_8010EDE4_toadstool_titan = 0;
    }
    for (j = 0; j < 3; j++) {
        D_8010EDE8_toadstool_titan[j] = (D_8010EDE8_toadstool_titan[j] >= 55) ? D_8010EDE8_toadstool_titan[j] : D_8010EDE8_toadstool_titan[j] + 1;
        if (D_8010EDE8_toadstool_titan[j] >= 55) {
            D_8010EDE8_toadstool_titan[j] = 55;
            func_8001C258_main(obj->model[26 + j], 4, 4);
        }
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF80_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF88_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_80107360_toadstool_titan);
#endif

void func_8010AD8C_toadstool_titan(s16 x0, s16 y0, s16 x1, s16 y1) {
    HuSprite* spr;
    HuSprite_Unk84_Unk00_Struct* cel;
    f32 sx;
    f32 sy;
    f32 ox;
    f32 oy;
    s32 dsdx;
    s32 dtdy;
    s32 row;
    s32 col;
    f32 ty;
    f32 tyb;
    f32 tx;
    f32 txr;
    s32 ulx;
    s32 uly;
    s32 lrx;
    s32 lry;

    sx = (x1 - x0) / 320.0;
    ox = x0;
    dsdx = 1.0 / sx * 1024.0;
    sy = (y1 - y0) / 240.0;
    oy = y0;
    dtdy = 1.0 / sy * 1024.0;
    gSPDisplayList(gMainGfxPos++, D_8010EDF0_toadstool_titan);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    spr = HuSprGet(D_800CD1DC_main[D_8010F588_toadstool_titan[0]].unk04, 0);
    cel = &spr->unk_84->unk00[spr->unk_90];
    gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
    for (row = 0; row < 6; row++) {
        ty = row * 40;
        tyb = ty + 40.0f + ((row == 5) ? -0.75 : 1.0);
        for (col = 0; col < 8; col++) {
            tx = col * 40;
            txr = tx + 40.0f + ((col < 7) ? 1.0f : 0.0f);
            ulx = (sx * tx + ox) * 4.0f;
            uly = (sy * ty + oy) * 4.0f;
            lrx = (sx * txr + ox) * 4.0f;
            lry = (sy * tyb + oy) * 4.0f;
            if (ulx > 1280 || uly > 960 || lrx < 0 || lry < 0) {
                continue;
            }
            gDPLoadTextureTile(gMainGfxPos++, cel->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, (s32)tx, (s32)ty, (s32)txr, (s32)tyb, 0,
                               G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPScisTextureRectangle(gMainGfxPos++, ulx, uly, lrx, lry, G_TX_RENDERTILE, tx * 32.0f, ty * 32.0f, dsdx, dtdy);
        }
    }
}

void func_8010B4D4_toadstool_titan(s16 mdl, s16 frame) {
    func_8001C6A8_main(mdl, frame);
}

void func_8010B510_toadstool_titan(omObjData* obj) {
    Vec up;

    if (D_8010EE38_toadstool_titan == 0) {
        D_8010EE38_toadstool_titan = 1;
        D_8010F628_toadstool_titan.x = 0.0f;
        D_8010F628_toadstool_titan.y = 868.0f;
        D_8010F628_toadstool_titan.z = 1561.0f;
        D_8010F5C0_toadstool_titan.x = 0.0f;
        D_8010F5C0_toadstool_titan.y = -100.0f;
        D_8010F5C0_toadstool_titan.z = -485.0f;
        D_8010F624_toadstool_titan = 32.5f;
    }
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    D_800CE17C_main[0] = D_8010F628_toadstool_titan.x;
    D_800CE17C_main[1] = D_8010F628_toadstool_titan.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = gCameraList->fov[0];
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPerspective(0, D_8010F624_toadstool_titan, 800.0f, 2750.0f);
    Hu3DCamSetPositionOrientation(0, &D_8010F628_toadstool_titan, &D_8010F5C0_toadstool_titan, &up);
    Hu3DCamUpdateMtx(0);
}

// register allocation and frame (retail 0xD0, two more saved registers, one base pointer into the tables); logic checked
#ifdef NON_MATCHING
void func_8010B658_toadstool_titan(omObjData* obj, u32 dir, s32 file, u16 idx, f32 x, f32 y, f32 z) {
    TtTbl8 grp = D_8010F218_toadstool_titan;
    TtTbl8 mot = D_8010EECC_toadstool_titan;
    TtTbl16 fil = D_8010F238_toadstool_titan;
    s32 chr;

    chr = D_8010F568_toadstool_titan[idx]->chr;
    func_800E18D8_minigame();
    func_800E1BA8_minigame(obj, dir, file, D_8010F568_toadstool_titan[idx]->player, 0x4A9, 0x99);
    omSetTra(obj, x, y, z);
    Hu3DModelPosSet(obj->model[1], x, 0.0f, z);
    ((MgWork*)obj->data)->unk59 = D_8010F568_toadstool_titan[idx]->player;
    D_8010F568_toadstool_titan[idx]->unkC = (rand8() & 1) ? 0x2F : 0x30;
    D_8010F568_toadstool_titan[idx]->unkC |= grp.v[(u16)chr] << 16;
    D_8010F568_toadstool_titan[idx]->unk6 = func_80017790_main(obj->model[0], 1, mot.v[(u16)chr], (grp.v[(u16)chr] << 16) | fil.v[(u16)chr]);
    D_8010F568_toadstool_titan[idx]->unk8 = func_80017AD8_main((grp.v[(u16)chr] << 16) | fil.v[(u16)chr + 8]);
    func_80033910_main(HmfModelData[obj->model[0]].hmf);
    func_8001C514_main(obj->model[0]);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5978_minigame(obj, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E149C_minigame(obj, 0, 2);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010B658_toadstool_titan);
#endif

void func_8010B99C_toadstool_titan(omObjData* obj) {
    s32 chr = D_8010F568_toadstool_titan[0]->chr;
    s32 file = D_800A178C_main[chr][3];
    u32 dir = D_800A178C_main[chr][0];

    func_8010B658_toadstool_titan(obj, dir, file, 0,
                                  (D_8010F668_toadstool_titan[0] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[0] & 1) ? -350.0f : 350.0f);
    obj->func = func_8010BD2C_toadstool_titan;
}

void func_8010BA80_toadstool_titan(omObjData* obj) {
    s32 chr = D_8010F568_toadstool_titan[1]->chr;
    s32 file = D_800A178C_main[chr][3];
    u32 dir = D_800A178C_main[chr][0];

    func_8010B658_toadstool_titan(obj, dir, file, 1,
                                  (D_8010F668_toadstool_titan[1] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[1] & 1) ? -350.0f : 350.0f);
    obj->func = func_8010BD2C_toadstool_titan;
}

void func_8010BB64_toadstool_titan(omObjData* obj) {
    s32 chr = D_8010F568_toadstool_titan[2]->chr;
    s32 file = D_800A178C_main[chr][3];
    u32 dir = D_800A178C_main[chr][0];

    func_8010B658_toadstool_titan(obj, dir, file, 2,
                                  (D_8010F668_toadstool_titan[2] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[2] & 1) ? -350.0f : 350.0f);
    obj->func = func_8010BD2C_toadstool_titan;
}

void func_8010BC48_toadstool_titan(omObjData* obj) {
    s32 chr = D_8010F568_toadstool_titan[3]->chr;
    s32 file = D_800A178C_main[chr][3];
    u32 dir = D_800A178C_main[chr][0];

    func_8010B658_toadstool_titan(obj, dir, file, 3,
                                  (D_8010F668_toadstool_titan[3] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[3] & 1) ? -350.0f : 350.0f);
    obj->func = func_8010BD2C_toadstool_titan;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F218_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F238_toadstool_titan);

#define TT_DEC(x) { s16 _v = (x); if (_v > 0) { _v--; } (x) = _v; }

// register allocation and stack layout (frame 0x178, more spills in retail); logic checked block by block
#ifdef NON_MATCHING
void func_8010BD2C_toadstool_titan(omObjData* obj) {
    u8 flags[4];
    MgWork* mw;
    TtPlayer* pl;
    omObjData* g;
    MgWork* gw;
    HmfModel* hm;
    s16* ptgt;
    s32 idx;
    s32 i;
    s32 bi;
    s32 sel;
    s32 a;
    s32 r;
    s32 b;
    f32 dx;
    f32 dz;
    f32 d;
    f32 best;
    f32 m;
    f32 ux;
    f32 uz;
    f32 cx;
    f32 cz;
    f32 sc;
    f32 w;
    f32 sn;
    f32 cs;
    f32 as;
    f32 ac;
    f32 sx;
    f32 sz;
    f32 lim;
    f32 hx;
    f32 t4;
    f32 t12;
    f32 ax;
    f32 az;
    f32 gx;
    f32 gz;
    f32 vx;
    f32 vz;
    f32 gvx;
    f32 gvz;
    f64 dr;
    f32* pf;
    s16 sv0;
    u16 sv1;
    s16 sv2;
    s8 sv3;
    s8 sv4;
    s16 sv5;
    s16 sv6;
    s32 sx8;
    s32 sy8;

    mw = obj->data;
    idx = D_8010F65D_toadstool_titan[mw->unk59];
    pl = D_8010F568_toadstool_titan[idx];
    if (idx == 0) {
        for (i = 0; i < 4; i++) {
            if (D_8010F640_toadstool_titan[i]->trans.y <= 0.0f) {
                flags[i] = 1;
            } else {
                flags[i] = (D_8010F616_toadstool_titan[i] != 0) * 2;
            }
        }
    }
    (void)flags; /* set, never read (retail) */
    sv0 = D_800CDA7C_main[pl->pad];
    sv1 = D_800D5558_main[pl->pad];
    sv2 = D_800D1244_main[pl->pad];
    sv3 = D_800CBB6E_main[pl->pad];
    sv4 = D_800D20A1_main[pl->pad];
    sv5 = D_800D056A_main[pl->pad];
    sv6 = D_800D1382_main[pl->pad];
    if (pl->com != -1) {
        s16 tbl[22][4] = {
            { 0, 0, 0, 0 },         { 300, 300, 200, 150 }, { 11, 9, 6, 3 },    { 6, 6, 6, 6 },
            { 11, 9, 5, 2 },        { 4, 4, 3, 1 },         { -30, -40, -40, -200 }, { 15, 20, 20, 100 },
            { 45, 35, 25, 25 },     { 1, 1, 1, 15 },        { 36, 46, 56, 66 }, { 1, 1, 1, 1 },
            { 20, 20, 15, 15 },     { 35, 25, 12, 8 },      { 0, 0, 6, 6 },     { 1, 8, 4, 5 },
            { 0, 24, 16, 32 },      { 1, 8, 24, 1 },        { 14, 9, 6, 0 },    { 6, 8, 5, 7 },
            { 0, 0, 0, 0 },         { 1, 1, 1, 1 },
        };

        D_800CDA7C_main[pl->pad] = 0;
        D_800D5558_main[pl->pad] = 0;
        D_800D1244_main[pl->pad] = 0;
        D_800CBB6E_main[pl->pad] = 0;
        D_800D20A1_main[pl->pad] = 0;
        D_800D056A_main[pl->pad] = 0;
        D_800D1382_main[pl->pad] = 0;
        if (D_8010F616_toadstool_titan[idx] != 0) {
            D_8010EE40_toadstool_titan[idx] = 13;
        }
        if (D_8010F586_toadstool_titan == 2 &&
            ((D_8010F60E_toadstool_titan == idx) ? D_8010F61C_toadstool_titan >= 10 : D_8010F61C_toadstool_titan >= 30)) {
            if (D_8010EE40_toadstool_titan[idx] != 0 && D_8010EE40_toadstool_titan[idx] < 4) {
                D_8010EE40_toadstool_titan[idx] = 10;
                D_8010EE44_toadstool_titan[idx] = 0;
            }
        }
        if (D_8010F586_toadstool_titan == 3 &&
            ((D_8010EE40_toadstool_titan[idx] != 0 && D_8010EE40_toadstool_titan[idx] < 4) ||
             (D_8010EE40_toadstool_titan[idx] >= 10 && D_8010EE40_toadstool_titan[idx] < 13))) {
            D_8010EE40_toadstool_titan[idx] = (D_8010F60E_toadstool_titan != idx) ? 7 : 4;
            D_8010EE44_toadstool_titan[idx] = 0;
        }
        if (D_8010F586_toadstool_titan == 7 &&
            ((D_8010EE40_toadstool_titan[idx] >= 4 && D_8010EE40_toadstool_titan[idx] < 7) ||
             (D_8010EE40_toadstool_titan[idx] >= 7 && D_8010EE40_toadstool_titan[idx] < 10))) {
            D_8010EE40_toadstool_titan[idx] = 1;
            D_8010EE44_toadstool_titan[idx] = tbl[12][pl->com] + rand8() % tbl[13][pl->com];
            D_8010EE4C_toadstool_titan[idx] = 0;
        }
        switch (D_8010EE40_toadstool_titan[idx]) {
        case 0:
            D_8010EE40_toadstool_titan[idx] = 1;
            D_8010EE44_toadstool_titan[idx] = 5;
            /* fallthrough */
        case 1:
            TT_DEC(D_8010EE44_toadstool_titan[idx]);
            if (D_8010EE44_toadstool_titan[idx] <= 0) {
                best = 16777216.0f;
                bi = -1;
                for (i = 0; i < 9; i++) {
                    if (D_8010F650_toadstool_titan[i] != 0) {
                        dx = obj->trans.x - D_8010F5D0_toadstool_titan[i]->trans.x;
                        dz = obj->trans.z - D_8010F5D0_toadstool_titan[i]->trans.z;
                        d = dx * dx + dz * dz + rand8() / 255.0 * tbl[1][pl->com] * tbl[1][pl->com];
                        if (d < best) {
                            best = d;
                            bi = i;
                        }
                    }
                }
                if (bi != -1) {
                    D_8010EE40_toadstool_titan[idx] = 2;
                    D_8010EE44_toadstool_titan[idx] = bi;
                    D_8010EE4C_toadstool_titan[idx] = 0;
                } else {
                    D_8010EE44_toadstool_titan[idx] = 1;
                }
            }
            break;
        case 2:
        case 3:
            g = D_8010F5D0_toadstool_titan[D_8010EE44_toadstool_titan[idx]];
            dx = g->trans.x - obj->trans.x;
            dz = g->trans.z - obj->trans.z;
            if (dx != 0.0f || dz != 0.0f) {
                d = HuSqrtf(dx * dx + dz * dz);
            } else {
                d = 16777216.0f;
            }
            D_800CBB6E_main[pl->pad] = dx / d * ((d > 33.0f) ? 1.0 : d / 33.0) * tbl[10][pl->com];
            D_800D20A1_main[pl->pad] = -(dz / d * ((d > 33.0f) ? 1.0 : d / 33.0) * tbl[10][pl->com]);
            if (obj->trans.y > 375.0f && mw->unk38 == 1000.0f) {
                D_800CBB6E_main[pl->pad] = 0;
                D_800D20A1_main[pl->pad] = 66;
            }
            if (D_8010EE40_toadstool_titan[idx] == 3 && D_8010EE4C_toadstool_titan[idx] == 0 && obj->trans.y <= 0.0f) {
                D_8010EE40_toadstool_titan[idx] = 2;
                D_8010EE4C_toadstool_titan[idx] = 0;
            } else if (D_8010EE40_toadstool_titan[idx] == 2 && D_8010EE4C_toadstool_titan[idx] == 0 && obj->trans.y <= 0.0f &&
                       (d < 50.0f || mw->unk54 != -1)) {
                sel = (d < 50.0f) ? 1 : (u8)(rand8() % 5) >> 1;
                switch (sel) {
                case 1:
                    D_8010EE40_toadstool_titan[idx] = 3;
                    D_800D5558_main[pl->pad] |= 0x8000;
                    D_8010EE4C_toadstool_titan[idx] = tbl[4][pl->com] + rand8() % tbl[5][pl->com];
                    break;
                case 2:
                    D_8010EE40_toadstool_titan[idx] = 1;
                    D_8010EE44_toadstool_titan[idx] = tbl[2][pl->com] + rand8() % tbl[3][pl->com];
                    break;
                }
            }
            if (D_8010EE40_toadstool_titan[idx] == 3) {
                D_800CDA7C_main[pl->pad] |= 0x8000;
            }
            TT_DEC(D_8010EE4C_toadstool_titan[idx]);
            if (D_8010F650_toadstool_titan[D_8010EE44_toadstool_titan[idx]] == 0) {
                D_8010EE40_toadstool_titan[idx] = 1;
                D_8010EE44_toadstool_titan[idx] = tbl[2][pl->com] + rand8() % tbl[3][pl->com];
            }
            break;
        case 4:
            TT_DEC(D_8010EE44_toadstool_titan[idx]);
            if (D_8010EE44_toadstool_titan[idx] > 0) {
                break;
            }
            if (((MgWork*)D_8010F640_toadstool_titan[idx]->data)->unk5C == 0x8000) {
                break;
            }
            best = 16777216.0f;
            bi = -1;
            for (i = 0; i < 4; i++) {
                if (i != idx && D_8010F616_toadstool_titan[i] == 0) {
                    dx = obj->trans.x - D_8010F640_toadstool_titan[i]->trans.x;
                    dz = obj->trans.z - D_8010F640_toadstool_titan[i]->trans.z;
                    d = dx * dx + dz * dz + (f32)tbl[6][pl->com] + (f32)(rand8() % tbl[7][pl->com]);
                    if (d < best) {
                        best = d;
                        bi = i;
                    }
                }
            }
            if (bi == -1) {
                D_8010EE44_toadstool_titan[idx] = 1;
                break;
            }
            D_8010EE40_toadstool_titan[idx] = 5;
            D_8010EE44_toadstool_titan[idx] = bi;
            if (tbl[14][pl->com] + rand8() % tbl[15][pl->com] >= 8) {
                if (D_8010F640_toadstool_titan[bi]->trans.x > 0.0f) {
                    dx = D_8010F640_toadstool_titan[bi]->trans.x - 350.0f;
                } else {
                    dx = -D_8010F640_toadstool_titan[bi]->trans.x - 350.0f;
                }
                if (D_8010F640_toadstool_titan[bi]->trans.z > 0.0f) {
                    dz = D_8010F640_toadstool_titan[bi]->trans.z - 350.0f;
                } else {
                    dz = -D_8010F640_toadstool_titan[bi]->trans.z - 350.0f;
                }
                if (dx * dx + dz * dz < 62500.0f) {
                    D_8010EE44_toadstool_titan[idx] += 4;
                    D_8010EE64_toadstool_titan[idx] = 0.0f;
                    D_8010EE54_toadstool_titan[idx] = 0.0f;
                    ax = D_8010F640_toadstool_titan[bi]->trans.x - obj->trans.x;
                    if (!(ax > 0.0f)) {
                        ax = -ax;
                    }
                    az = D_8010F640_toadstool_titan[bi]->trans.z - obj->trans.z;
                    if (!(az > 0.0f)) {
                        az = -(D_8010F640_toadstool_titan[bi]->trans.z - obj->trans.z);
                    }
                    if (ax < az) {
                        pf = &D_8010EE54_toadstool_titan[idx];
                        dr = rand8() / 255.0 * 200.0;
                        m = D_8010F640_toadstool_titan[bi]->trans.x;
                    } else {
                        pf = &D_8010EE64_toadstool_titan[idx];
                        dr = rand8() / 255.0 * 200.0;
                        m = D_8010F640_toadstool_titan[bi]->trans.z;
                    }
                    if (!(m < 0.0f)) {
                        dr = -dr;
                    }
                    *pf = dr;
                }
            }
            break;
        case 5:
        case 6:
            dx = D_8010F640_toadstool_titan[(s16)(D_8010EE44_toadstool_titan[idx] % 4)]->trans.x - obj->trans.x;
            dx += (D_8010EE44_toadstool_titan[idx] >= 4) ? D_8010EE54_toadstool_titan[idx] : 0.0f;
            dz = D_8010F640_toadstool_titan[(s16)(D_8010EE44_toadstool_titan[idx] % 4)]->trans.z - obj->trans.z;
            dz += (D_8010EE44_toadstool_titan[idx] >= 4) ? D_8010EE64_toadstool_titan[idx] : 0.0f;
            if (dx != 0.0f || dz != 0.0f) {
                d = HuSqrtf(dx * dx + dz * dz);
            } else {
                d = 16777216.0f;
            }
            D_800CBB6E_main[pl->pad] = (d > 33.0f) ? dx / d * 66.0f : dx / d * (2.0f * d);
            D_800D20A1_main[pl->pad] = -((d > 33.0f) ? dz / d * 66.0f : dz / d * (2.0f * d));
            if (D_8010EE40_toadstool_titan[idx] == 5 && D_8010EE4C_toadstool_titan[idx] <= 0 && D_8010EE3C_toadstool_titan != 0) {
                D_8010EE40_toadstool_titan[idx] = 6;
                D_8010EE4C_toadstool_titan[idx] = 0;
            }
            TT_DEC(D_8010EE4C_toadstool_titan[idx]);
            if (D_8010EE40_toadstool_titan[idx] == 6 && D_8010EE3C_toadstool_titan == 0) {
                D_8010EE40_toadstool_titan[idx] = 4;
                D_8010EE44_toadstool_titan[idx] = tbl[8][pl->com] + rand8() % tbl[9][pl->com];
            }
            break;
        case 7:
            TT_DEC(D_8010EE44_toadstool_titan[idx]);
            if (D_8010EE44_toadstool_titan[idx] <= 0) {
                D_8010EE40_toadstool_titan[idx] = 8;
                D_8010EE44_toadstool_titan[idx] = -1;
                D_8010EE4C_toadstool_titan[idx] = 0;
            }
            break;
        case 8:
        case 9:
            if (D_8010EE44_toadstool_titan[idx] == -1) {
                best = 100.0f;
                g = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
                dx = g->trans.x - obj->trans.x;
                dz = g->trans.z - obj->trans.z;
                if (dx != 0.0f || dz != 0.0f) {
                    d = 1.0f / HuSqrtf(dx * dx + dz * dz);
                } else {
                    d = 0.000001f;
                }
                ux = dx * d;
                uz = dz * d;
                bi = 0;
                ptgt = &D_8010EE44_toadstool_titan[idx];
                for (i = 0; i < 4; i++) {
                    cx = (i < 2) ? -400.0f : 400.0f;
                    dx = cx - obj->trans.x;
                    cz = ((i + 1) % 4 < 2) ? -350.0f : 350.0f;
                    dz = cz - obj->trans.z;
                    if (dx != 0.0f || dz != 0.0f) {
                        d = HuSqrtf(dx * dx + dz * dz);
                    } else {
                        d = 16777216.0f;
                    }
                    sc = ux * (dx / d) + uz * (dz / d) + 1.0f;
                    if (d == 16777216.0f) {
                        w = 10.0f;
                    } else if (d > 500.0f) {
                        w = 0.0f;
                    } else {
                        w = 1.0 - d / 500.0;
                    }
                    sc = sc * sc + w * w * 4.0f;
                    if (D_8010EE40_toadstool_titan[idx] == 9) {
                        gw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
                        sn = sindf(gw->unk3C);
                        cs = cosdf(gw->unk3C);
                        as = sn;
                        if (!(as > 0.0f)) {
                            as = -as;
                        }
                        sx = 1.0f;
                        if (sn < 0.0f) {
                            sx = -1.0f;
                        }
                        ac = cs;
                        if (!(ac > 0.0f)) {
                            ac = -ac;
                        }
                        sz = 1.0f;
                        if (cs < 0.0f) {
                            sz = -1.0f;
                        }
                        lim = 1000.0f;
                        if (ac < as) {
                            g = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
                            lim = (401.0f - sx * g->trans.x) / as * ac + sz * g->trans.z;
                        }
                        if (lim > 351.0f) {
                            g = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
                            t4 = sz * g->trans.z;
                            t12 = sx * g->trans.x;
                            hx = (351.0f - t4) / ac * as + t12;
                            if (hx > 401.0f) {
                                lim = (401.0f - t12) / as * ac + t4;
                                hx = 401.0f * sx;
                            } else {
                                lim = 351.0f;
                                hx = hx * sx;
                            }
                        } else {
                            hx = 401.0f * sx;
                        }
                        hx = hx - cx;
                        lim = lim * sz - cz;
                        if (hx != 0.0f || lim != 0.0f) {
                            d = HuSqrtf(hx * hx + lim * lim);
                        } else {
                            d = 0.0f;
                        }
                        if (d > 600.0f) {
                            sc = sc + 0.0;
                        } else {
                            sc = sc + (1.0 - d / 600.0) * 8.0;
                        }
                    }
                    if (D_8010EE40_toadstool_titan[idx] >= 8 && D_8010EE40_toadstool_titan[idx] < 10 && sc < best) {
                        bi = i;
                        best = sc;
                    }
                    if (best != 100.0f) {
                        *ptgt = bi;
                    }
                }
            }
            cx = (D_8010EE44_toadstool_titan[idx] < 2) ? -400.0f : 400.0f;
            dx = cx - obj->trans.x;
            cz = ((D_8010EE44_toadstool_titan[idx] + 1) % 4 < 2) ? -350.0f : 350.0f;
            dz = cz - obj->trans.z;
            if (dx != 0.0f || dz != 0.0f) {
                d = HuSqrtf(dx * dx + dz * dz);
            } else {
                d = 16777216.0f;
            }
            D_800CBB6E_main[pl->pad] = dx / d * ((d > 70.0f) ? 70.0f : (d > 35.0f) ? d : 0.0f);
            D_800D20A1_main[pl->pad] = -(dz / d * ((d > 70.0f) ? 70.0f : (d > 35.0f) ? d : 0.0f));
            if (D_8010EE3C_toadstool_titan != 0) {
                TT_DEC(D_8010EE4C_toadstool_titan[idx]);
                if (D_8010EE4C_toadstool_titan[idx] <= 0) {
                    D_8010EE40_toadstool_titan[idx] = 9;
                    D_8010EE44_toadstool_titan[idx] = -1;
                    a = tbl[19][pl->com];
                    r = rand8();
                    b = tbl[18][pl->com];
                    if (D_8010F66C_toadstool_titan == 0) {
                        D_8010EE4C_toadstool_titan[idx] = b + 5 + r % (a + 12);
                    } else {
                        D_8010EE4C_toadstool_titan[idx] = b + r % a;
                    }
                }
            } else {
                TT_DEC(D_8010EE4C_toadstool_titan[idx]);
                if (D_8010EE4C_toadstool_titan[idx] <= 0) {
                    D_8010EE40_toadstool_titan[idx] = 8;
                    D_8010EE44_toadstool_titan[idx] = -1;
                    D_8010EE4C_toadstool_titan[idx] = tbl[18][pl->com] + rand8() % tbl[19][pl->com];
                }
            }
            if (mw->unk38 != 1000.0f) {
                D_800CDA7C_main[pl->pad] |= 0x8000;
            } else if (D_8010F66C_toadstool_titan != 0 && tbl[16][pl->com] + rand8() % tbl[17][pl->com] >= 32) {
                ax = obj->trans.x;
                az = obj->trans.z;
                g = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan];
                gx = g->trans.x;
                gz = g->trans.z;
                gw = g->data;
                vx = sindf(mw->unk3C) * mw->unk40;
                vz = cosdf(mw->unk3C) * mw->unk40;
                gvx = sindf(gw->unk3C) * gw->unk40;
                gvz = cosdf(gw->unk3C) * gw->unk40;
                for (i = 0; i < 6;) {
                    dx = ax - gx;
                    dz = az - gz;
                    i++;
                    if (dx * dx + dz * dz < 22500.0f) {
                        D_800CDA7C_main[pl->pad] |= 0x8000;
                        D_800D5558_main[pl->pad] |= 0x8000;
                        D_800D1244_main[pl->pad] |= 0x8000;
                        break;
                    }
                    ax += vx;
                    az += vz;
                    gx += gvx;
                    gz += gvz;
                }
            }
            break;
        case 10:
            TT_DEC(D_8010EE44_toadstool_titan[idx]);
            if (D_8010EE44_toadstool_titan[idx] <= 0) {
                D_8010EE40_toadstool_titan[idx] = 11;
                D_8010EE44_toadstool_titan[idx] = 0;
                D_8010EE4C_toadstool_titan[idx] = 0;
            }
            break;
        case 11:
        case 12:
            hm = &HmfModelData[D_8010F5F8_toadstool_titan->model[1]];
            dx = hm->pos.x - obj->trans.x;
            dz = hm->pos.z - obj->trans.z;
            if (dx != 0.0f || dz != 0.0f) {
                d = HuSqrtf(dx * dx + dz * dz);
            } else {
                d = 16777216.0f;
            }
            D_800CBB6E_main[pl->pad] = dx / d * ((d > 33.0f) ? 1.0 : d / 33.0) * tbl[10][pl->com];
            D_800D20A1_main[pl->pad] = -(dz / d * ((d > 33.0f) ? 1.0 : d / 33.0) * tbl[10][pl->com]);
            if (D_8010EE40_toadstool_titan[idx] == 12 && D_8010EE4C_toadstool_titan[idx] == 0 && obj->trans.y <= 0.0f) {
                D_8010EE40_toadstool_titan[idx] = 11;
                D_8010EE4C_toadstool_titan[idx] = 0;
            } else if (D_8010EE40_toadstool_titan[idx] == 11 && D_8010EE4C_toadstool_titan[idx] == 0 && obj->trans.y <= 0.0f &&
                       pl->com > 0 && d < 50.0f && D_8010F61C_toadstool_titan >= 42) {
                sel = (d < 50.0f) ? 1 : (rand8() & 3) < 3;
                if (sel == 1) {
                    D_8010EE40_toadstool_titan[idx] = 12;
                    D_800D5558_main[pl->pad] |= 0x8000;
                    D_8010EE4C_toadstool_titan[idx] = tbl[4][pl->com] + rand8() % tbl[5][pl->com];
                }
            }
            if (D_8010EE40_toadstool_titan[idx] == 12) {
                D_800CDA7C_main[pl->pad] |= 0x8000;
            }
            TT_DEC(D_8010EE4C_toadstool_titan[idx]);
            break;
        }
        D_800D056A_main[pl->pad] = D_800CBB6E_main[pl->pad] * 2;
        D_800D1382_main[pl->pad] = D_800D20A1_main[pl->pad] * 2;
    }
    if (D_8010F586_toadstool_titan == 3 && D_8010F60E_toadstool_titan == idx) {
        D_800CDA7C_main[pl->pad] = 0;
        D_800D5558_main[pl->pad] = 0;
        D_800D1244_main[pl->pad] = 0;
        D_800CBB6E_main[pl->pad] = 0;
        D_800D20A1_main[pl->pad] = 0;
        D_800D056A_main[pl->pad] = 0;
        D_800D1382_main[pl->pad] = 0;
    }
    if (D_8010F586_toadstool_titan == 5 && D_8010F60E_toadstool_titan == idx) {
        D_800CDA7C_main[pl->pad] = 0;
        D_800D5558_main[pl->pad] = 0;
        D_800D1244_main[pl->pad] = 0;
    }
    if (D_8010F586_toadstool_titan == 5 && D_8010F60E_toadstool_titan == idx) {
        D_800EB73C_minigame = 30.0f;
        D_800EB75C_minigame = 1.6666666f;
        D_800EB760_minigame = 36.0f;
        D_800EB764_minigame = 27.0f;
        D_800EB768_minigame = 18.0f;
        D_800EB76C_minigame = 9.0f;
    }
    if (D_8010F586_toadstool_titan == 5 && D_8010F60E_toadstool_titan == idx) {
        if (D_8010EE3C_toadstool_titan == 0 && mw->unk40 > 9.0f) {
            D_8010EE3C_toadstool_titan = 1;
            sx8 = D_800CBB6E_main[pl->pad];
            sy8 = D_800D20A1_main[pl->pad];
            if (sx8 * sx8 + sy8 * sy8 >= 1601) {
                if (sx8 == 0) {
                    mw->unk3C = (sy8 >= 0) ? 180.0f : 0.0f;
                } else {
                    mw->unk3C = atan2df(D_800CBB6E_main[pl->pad], -D_800D20A1_main[pl->pad]);
                }
            }
            D_8010F520_toadstool_titan = mw->unk3C;
        }
        if (D_8010EE3C_toadstool_titan != 0) {
            D_800CBB6E_main[pl->pad] = sindf(D_8010F520_toadstool_titan) * 63.0f + (s8)(D_800CBB6E_main[pl->pad] / 6);
            D_800D20A1_main[pl->pad] = cosdf(D_8010F520_toadstool_titan) * -63.0f + (s8)(D_800D20A1_main[pl->pad] / 6);
            D_800D056A_main[pl->pad] = D_800CBB6E_main[pl->pad] * 2;
            D_800D1382_main[pl->pad] = D_800D20A1_main[pl->pad] * 2;
        }
    } else if (D_8010F586_toadstool_titan != 5) {
        D_8010EE3C_toadstool_titan = 0;
    }
    if ((D_8010F586_toadstool_titan == 3 || D_8010F586_toadstool_titan == 4 || D_8010F586_toadstool_titan == 6) && idx != D_8010F60E_toadstool_titan) {
        gw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
        gw->unkBE = 1;
        gw->unk50 |= 0x200;
    }
    if (D_8010F5FC_toadstool_titan >= 3 && mw->unk53 == -1) {
        D_800CBB6E_main[pl->pad] = rand8() % 40;
        D_800D20A1_main[pl->pad] = rand8() % 40;
        D_800D056A_main[pl->pad] = D_800CBB6E_main[pl->pad] * 2;
        D_800D1382_main[pl->pad] = D_800D20A1_main[pl->pad] * 2;
    }
    if ((mw->unk53 == 5 || mw->unk53 == 6) && obj->trans.z > 330.0f) {
        obj->trans.z = 330.0f;
    }
    if (obj->trans.y >= 425.0f && obj->trans.z > 345.0f) {
        obj->trans.z = 345.0f;
    }
    if ((D_8010F5FC_toadstool_titan != 0 || !(D_8010F580_toadstool_titan >= 46 && D_8010F580_toadstool_titan < 55)) &&
        ((D_8010F586_toadstool_titan != 4 && D_8010F586_toadstool_titan != 6) || D_8010F60E_toadstool_titan != idx) &&
        D_8010F616_toadstool_titan[idx] == 0) {
        func_800DDD94_minigame(obj);
        D_8010F634_toadstool_titan[idx] = -1;
    } else if (D_8010F634_toadstool_titan[idx] == -1 || HmfModelData[obj->model[0]].unk40 < D_8010F634_toadstool_titan[idx]) {
        D_8010F634_toadstool_titan[idx] = HmfModelData[obj->model[0]].unk40;
    } else {
        func_8001C6A8_main(obj->model[0], D_8010F634_toadstool_titan[idx]);
    }
    if (D_8010F5FC_toadstool_titan == 0 && (D_8010F580_toadstool_titan < 10 || idx != 0)) {
        HuAudFXStop(mw->unkC5);
    }
    if ((D_8010F586_toadstool_titan == 3 || D_8010F586_toadstool_titan == 4 || D_8010F586_toadstool_titan == 6) && idx != D_8010F60E_toadstool_titan) {
        gw = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
        gw->unkBE = 0;
        gw->unk50 &= ~0x200;
    }
    if (D_8010F5FC_toadstool_titan == 0 && D_8010F580_toadstool_titan < 10) {
        mw->unk38 = 0.0f;
    }
    if (D_8010F60E_toadstool_titan == idx && D_8010F586_toadstool_titan == 5) {
        omSetSca(obj, 2.0f, 2.0f, 2.0f);
        if (D_8010EE3C_toadstool_titan != 0) {
            m = mw->unk3C;
            if ((m > -145.0f && m < -35.0f && obj->trans.x <= -400.0f) ||
                (mw->unk3C > 35.0f && mw->unk3C < 145.0f && obj->trans.x >= 400.0f) ||
                ((mw->unk3C > 125.0f || mw->unk3C < -125.0f) && obj->trans.z <= -350.0f) ||
                (mw->unk3C > -55.0f && mw->unk3C < 55.0f && obj->trans.z >= 350.0f)) {
                obj->trans.x = (obj->trans.x <= -400.0f) ? -400.0f : (obj->trans.x >= 400.0f) ? 400.0f : obj->trans.x;
                obj->trans.z = (obj->trans.z <= -350.0f) ? -350.0f : (obj->trans.z >= 350.0f) ? 350.0f : obj->trans.z;
                mw->unk40 = -D_800EB768_minigame;
                func_800E5690_minigame(obj, 0x1E);
                omVibrate(mw->unk59, 20, 0, 20);
                for (i = 0; i < 4; i++) {
                    if (D_8010F616_toadstool_titan[i] == 0 && D_8010F568_toadstool_titan[i]->player != mw->unk59) {
                        omVibrate(D_8010F568_toadstool_titan[i]->player, 10, 0, 10);
                    }
                }
                D_8010EE3C_toadstool_titan = 0;
                D_8010F5F4_toadstool_titan = 13;
                D_8010F670_toadstool_titan = mw->unk3C;
                HuAudFXPlay(0x3AA);
            }
        }
    }
    D_800EB73C_minigame = 15.0f;
    D_800EB75C_minigame = 3.3333333f;
    D_800EB760_minigame = 18.0f;
    D_800EB764_minigame = 13.5f;
    D_800EB768_minigame = 9.0f;
    D_800EB76C_minigame = 4.5f;
    D_800CDA7C_main[pl->pad] = sv0;
    D_800D5558_main[pl->pad] = sv1;
    D_800D1244_main[pl->pad] = sv2;
    D_800CBB6E_main[pl->pad] = sv3;
    D_800D20A1_main[pl->pad] = sv4;
    D_800D056A_main[pl->pad] = sv5;
    D_800D1382_main[pl->pad] = sv6;
    if (D_8010F616_toadstool_titan[idx] >= 60) {
        func_8001C258_main(obj->model[0], 4, 4);
    }
    if (D_8010F616_toadstool_titan[idx] != 0) {
        func_8001C258_main(obj->model[1], 4, 4);
    }
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F278_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BD2C_toadstool_titan);
#endif
