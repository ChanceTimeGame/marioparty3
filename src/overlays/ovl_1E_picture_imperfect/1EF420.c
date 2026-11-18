#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

// pi A: Picture Imperfect (4 players, split screen: assemble a picture from its pieces)

typedef func_800E1BA8_minigame_ObjData MgWork;

/* The minigame control block (as All Fired Up's AfCtrl) */
typedef struct PiCtrl {
    /* 0x00 */ s8 unk00; /* row being filled: 0, 2, 3.., then 1; 10 done */
    /* 0x01 */ s8 unk01; /* row the player is on */
    /* 0x02 */ u8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ s8 unk07;
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
} PiCtrl; /* size 0x28 */

/* MgWork::unk158 of a player */
typedef struct PiPlayer {
    /* 0x00 */ s8 unk00; /* row being filled: 0, 2, 3.., then 1; 10 done */
    /* 0x01 */ s8 unk01; /* row the player is on */
    /* 0x02 */ u8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ s8 unk07;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14; /* bob angle */
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char unk1A[2];
} PiPlayer; /* size 0x1C */

// main
void func_8000B5F0_main(u8 arg0);
s32 func_8000B710_main(s32 arg0);
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004AD70_main(void);
void func_8000BC48_main(u16, s32);
void func_8000BB54_main(u16 arg0);
void func_8000BD50_main(u16 spriteId, s16 frame);
void func_8000BBFC_main(u16 spriteId, s16 alpha);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BEAC_main(u16 spriteId, s32 r, s32 g, s32 b);

extern s32 D_800A178C_main[][6];

extern u8 D_800CE20A_main;
extern u16 D_800A1906_main; /* music state flags */
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;

s16 func_8004AC98_main(s16, s16);
void func_8004AE00_main(s16 handle, s16 pan);
f32 sindf(f32);

extern s8 D_800CBB6E_main[];  /* CPU stick x */
extern s8 D_800D20A1_main[];  /* CPU stick y */
extern s16 D_800CDA7C_main[];
extern u16 D_800D5558_main[];

// minigame
void func_800DDD94_minigame(omObjData* obj);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
u16 func_800E6E9C_minigame(void);

extern f32 D_800EB748_minigame;
void func_800E1490_minigame(u16 arg0);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2);
void func_800E1804_minigame(void);
void func_800E1840_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[];

/* omObjData::data of the framework's ground object */
typedef struct PiGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[3];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ char unk0C[0xA8];
} PiGround; /* size 0xB4 */

// LOCAL
void func_80109AC4_picture_imperfect(omObjData* obj);
void func_801081E4_picture_imperfect(omObjData* obj);
void func_801083C0_picture_imperfect(s8 player);
void func_80108688_picture_imperfect(omObjData* obj);
void func_80108A64_picture_imperfect(PiPlayer* ex, s8 player);
void func_80108C20_picture_imperfect(PiPlayer* ex, s8 player);
void func_80109284_picture_imperfect(PiPlayer* ex, s8 player);
void func_80107820_picture_imperfect(omObjData* obj);
void func_80105BA8_picture_imperfect(void);
void func_80105E68_picture_imperfect(PiCtrl* ctrl);
void func_80105EF4_picture_imperfect(void);
void func_80106154_picture_imperfect(omObjData* obj);
void func_8010629C_picture_imperfect(omObjData* obj);
void func_80109608_picture_imperfect(omObjData* obj);

extern s16 D_80109FE0_picture_imperfect; /* looping sound handle, -1 none */
extern s16 D_80109FE2_picture_imperfect;
extern u8 D_80109FE4_picture_imperfect;  /* result state */
extern s16 D_80109FE8_picture_imperfect[4][2]; /* centre of each screen quarter */
extern s8 D_80109FF8_picture_imperfect[4]; /* players with the most pieces, -1 none */
extern s8 D_80109FFC_picture_imperfect[4][5]; /* column each player stopped each row at */
extern s32 D_8010A010_picture_imperfect;
extern s8 D_8010A014_picture_imperfect;
extern s16 D_8010A018_picture_imperfect[4][2]; /* sprite position of each screen quarter */
extern s8 D_8010A028_picture_imperfect;        /* next player to set up */
extern s32 D_8010A02C_picture_imperfect;       /* pieces placed */
extern u8 D_8010A030_picture_imperfect[4][5]; /* column order, one row per layout */
extern u32 D_8010A044_picture_imperfect;
extern s8 D_8010A048_picture_imperfect[5]; /* y offset of each row */
extern f32 D_8010A050_picture_imperfect;   /* title scale */
extern u8 D_8010A054_picture_imperfect; /* title: step */
extern u8 D_8010A055_picture_imperfect; /* title: alpha */
extern u8 D_8010A056_picture_imperfect; /* title: timer */       /* frame counter of the row scroll */

extern s8 D_8010A110_picture_imperfect;    /* number of winners */
extern s8 D_8010A111_picture_imperfect;    /* pieces whose score flash finished */
extern s8 D_8010A112_picture_imperfect[4]; /* score flash timer per player */
extern s8 D_8010A116_picture_imperfect[4]; /* score flash blink per player */
extern s16 D_8010A11A_picture_imperfect[4]; /* score display timer */
extern s16 D_8010A122_picture_imperfect; /* sprite file being loaded */
extern s16 D_8010A124_picture_imperfect; /* title sound handle */
extern PiCtrl D_8010A128_picture_imperfect;
extern u8 D_8010A140_picture_imperfect[4]; /* winners */
extern u8 D_8010A150_picture_imperfect; /* picture set: 2 - D_800CE20A_main */
extern u8 D_8010A151_picture_imperfect; /* column order layout, random */
extern s16 D_8010A152_picture_imperfect; /* frame sprite group (one variable for the four quarters) */
extern s16 D_8010A154_picture_imperfect; /* divider sprite group */
extern s16 D_8010A156_picture_imperfect;
extern s16 D_8010A158_picture_imperfect;
extern s16 D_8010A15A_picture_imperfect;
extern s16 D_8010A15C_picture_imperfect[4];
/* picture piece sprite slots, one table per row: [player][column] */
extern s16 D_8010A168_picture_imperfect[4][5];
extern s16 D_8010A190_picture_imperfect[4][5];
extern s16 D_8010A1B8_picture_imperfect[4][5];
extern s16 D_8010A1E0_picture_imperfect[4][5];
extern s16 D_8010A208_picture_imperfect[4][5];
extern s16 D_8010A230_picture_imperfect;
/* picture piece sprites of the set, one table per row */
extern s16 D_8010A232_picture_imperfect[5];
extern s16 D_8010A23C_picture_imperfect[5];
extern s16 D_8010A246_picture_imperfect[5];
extern s16 D_8010A250_picture_imperfect[5];
extern s16 D_8010A25A_picture_imperfect[5];
extern s16 D_8010A264_picture_imperfect;
extern s16 D_8010A266_picture_imperfect;
extern s16 D_8010A268_picture_imperfect;
extern s16 D_8010A26A_picture_imperfect;
extern s16 D_8010A26C_picture_imperfect;
extern s16 D_8010A26E_picture_imperfect[4];
extern s16 D_8010A276_picture_imperfect[4];
extern s16 D_8010A27E_picture_imperfect[4];
extern s16 D_8010A286_picture_imperfect[4];
extern s16 D_8010A28E_picture_imperfect[4];
extern s16 D_8010A296_picture_imperfect[4];
extern s16 D_8010A29E_picture_imperfect[4];
extern s16 D_8010A2A6_picture_imperfect;
extern s16 D_8010A2A8_picture_imperfect;
extern s16 D_8010A2AA_picture_imperfect;
extern s8 D_8010A2AC_picture_imperfect[5]; /* column shown in each row; the rows scroll at different speeds */

void func_801059A0_picture_imperfect(void) {
    omObjData* obj;
    s32 i;

    Hu3DAnimInit(0x20);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105EF4_picture_imperfect();
    D_8010A150_picture_imperfect = 2 - D_800CE20A_main;
    func_80105BA8_picture_imperfect();
    func_80105E68_picture_imperfect(&D_8010A128_picture_imperfect);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010A128_picture_imperfect);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    D_8010A151_picture_imperfect = rand8() >> 6;
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80106154_picture_imperfect), 0xA0);
    func_800E1490_minigame(D_800EBE28_minigame);
    obj = omAddObj(0, 1, 0, -1, func_80109608_picture_imperfect);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = obj;
    for (i = 0; i < 4; i++) {
        omSetStatBit(D_800EC598_minigame[i] = omAddObj(1, 4, 60, -1, func_8010629C_picture_imperfect), 0xA0);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, 0xA0);
    obj->work[0] = 4;
    WipeCreateIn(0xFF, 16);
}

/* Load the picture pieces of the set, and the shared sprites. */
void func_80105BA8_picture_imperfect(void) {
    s32 i;

    switch (D_8010A150_picture_imperfect) {
        case 0:
            D_8010A230_picture_imperfect = func_8000B838_main(0x3F0005);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[i] = func_8000B838_main((i + 0x0E) | 0x3F0000);
                D_8010A23C_picture_imperfect[i] = func_8000B838_main((i + 0x13) | 0x3F0000);
                D_8010A246_picture_imperfect[i] = func_8000B838_main((i + 0x18) | 0x3F0000);
                D_8010A250_picture_imperfect[i] = func_8000B838_main((i + 0x1D) | 0x3F0000);
                D_8010A25A_picture_imperfect[i] = func_8000B838_main((i + 0x22) | 0x3F0000);
            }
            break;
        case 1:
            D_8010A230_picture_imperfect = func_8000B838_main(0x3F0006);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[i] = func_8000B838_main((i + 0x27) | 0x3F0000);
                D_8010A23C_picture_imperfect[i] = func_8000B838_main((i + 0x2C) | 0x3F0000);
                D_8010A246_picture_imperfect[i] = func_8000B838_main((i + 0x31) | 0x3F0000);
                D_8010A250_picture_imperfect[i] = func_8000B838_main((i + 0x36) | 0x3F0000);
            }
            break;
        case 2:
        default:
            D_8010A230_picture_imperfect = func_8000B838_main(0x3F0007);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[i] = func_8000B838_main((i + 0x3B) | 0x3F0000);
                D_8010A23C_picture_imperfect[i] = func_8000B838_main((i + 0x40) | 0x3F0000);
                D_8010A246_picture_imperfect[i] = func_8000B838_main((i + 0x45) | 0x3F0000);
            }
            break;
    }
    D_8010A264_picture_imperfect = func_8000B838_main(0x40001C);
    D_8010A266_picture_imperfect = func_8000B838_main(0x40001B);
    D_8010A268_picture_imperfect = func_8000B838_main(0x40001D);
    D_8010A26A_picture_imperfect = func_8000B838_main(0x2E);
    D_8010A26C_picture_imperfect = func_8000B838_main(0x3E0019);
}

void func_80105E68_picture_imperfect(PiCtrl* ctrl) {
    s32 i;

    D_800EB932_minigame = 10;
    ctrl->unk00 = 0;
    ctrl->unk01 = 0;
    ctrl->unk02 = 1;
    ctrl->unk03 = 2;
    ctrl->unk04 = 0;
    ctrl->unk05 = 0;
    ctrl->unk06 = 9;
    ctrl->unk1C = -1;
    ctrl->unk1E = 1800;
    ctrl->unk20 = -1;
    ctrl->unk22 = 360;
    ctrl->unk24 = 162;
    for (i = 0; i < 4; i++) {
        ctrl->unk08[i] = 0;
        ctrl->unk18[i] = 0xFF;
    }
}

/* Four cameras, one screen quarter each. */
void func_80105EF4_picture_imperfect(void) {
    s32 i;

    func_8000B710_main(4);
    func_8000B5F0_main(4);
    for (i = 0; i < 4; i++) {
        CenterM[i].x = -200.0f;
        CenterM[i].y = 100.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = CRotM[i].y = CRotM[i].z = 0.0f;
        CZoomM[i] = 2100.0f;
        Hu3DCamSetPerspective(i, 30.0f, 80.0f, 8000.0f);
    }
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 120.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 240.0f, 511.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 120.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 240.0f, 511.0f);
    ScissorSet(2, 0.0f, 120.0f, 160.0f, 240.0f);
    ViewportSet(2, 640.0f, 480.0f, 511.0f, 320.0f, 720.0f, 511.0f);
    ScissorSet(3, 160.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(3, 640.0f, 480.0f, 511.0f, 960.0f, 720.0f, 511.0f);
}

void func_80106154_picture_imperfect(omObjData* obj) {
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        if (D_8010A014_picture_imperfect == 0 && D_800D530C_main == 1) {
            func_8004AD70_main();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                func_8004A950_main();
            }
            func_800E6F0C_minigame(5);
            D_8010A014_picture_imperfect = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 0x31;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (D_8010A010_picture_imperfect == 0) {
                    WipeCreateOut(0, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    func_80037258_main();
                    omOvlReturnEx(1);
                }
                D_8010A010_picture_imperfect++;
                break;
        }
    }
}

void func_8010629C_picture_imperfect(omObjData* obj) {
    MgWork* pw;
    PiPlayer* ex;
    s8 chr;
    s32 dir;
    s32 file;
    s16 mask;
    s32 i;

    chr = GwPlayer[D_8010A028_picture_imperfect].chr;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][1];
    func_800E19F0_minigame(1);
    func_800E1BA8_minigame(obj, dir, file, D_8010A028_picture_imperfect, 0x2A9, 0x2B9);
    pw = obj->data;
    pw->unk158 = HuMemAllocTag(sizeof(PiPlayer), 0x7918);
    memset(pw->unk158, 0, sizeof(PiPlayer));
    ex = pw->unk158;
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->trans.x = 0.0f;
    obj->trans.y = -8.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    ex->unk10 = 272.0f;
    obj->model[2] = func_8000B108_main(0x3F0000, 0x2B9);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, ex->unk10, obj->trans.z);
    Hu3DModelScaleSet(obj->model[2], 1.2f, 1.2f, 1.2f);
    obj->model[3] = func_8000B108_main(8, 0x88D);
    switch (D_8010A028_picture_imperfect) {
        case 0:
        default:
            mask = 1;
            break;
        case 1:
            mask = 2;
            break;
        case 2:
            mask = 4;
            break;
        case 3:
            mask = 8;
            break;
    }
    func_8001C8A8_main(obj->model[0], mask);
    func_8001C8A8_main(obj->model[1], mask);
    func_8001C8A8_main(obj->model[2], mask);
    func_8001C8A8_main(obj->model[3], mask);
    func_800E149C_minigame(obj, 0, 2);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, 0x36), 1, 0x78);
    func_800E5690_minigame(obj, 0);
    obj->func = func_80107820_picture_imperfect;
    ex->unk00 = 0;
    ex->unk01 = 0;
    ex->unk02 = 0;
    ex->unk08 = 0;
    ex->unk03 = 0;
    ex->unk04 = 0;
    ex->unk0A = 0xFF;
    ex->unk0C = 1.0f;
    ex->unk14 = 0;
    ex->unk05 = 0;
    ex->unk06 = 0;
    ex->unk07 = 0;
    ex->unk18 = (rand8() * 15 >> 7) + 30;

#define PI_PIECE(dst, src, col)                                                                            \
    dst[D_8010A028_picture_imperfect][col] = InitEspriteSlot(src[col], 0, 1);                              \
    func_8000BBD4_main(dst[D_8010A028_picture_imperfect][col],               \
                       D_8010A018_picture_imperfect[D_8010A028_picture_imperfect][0],                      \
                       D_8010A018_picture_imperfect[D_8010A028_picture_imperfect][1]);                     \
    func_8000BC48_main(dst[D_8010A028_picture_imperfect][col], 0x5000);      \
    func_8000BCC8_main(dst[D_8010A028_picture_imperfect][col], 0xFFF0);      \
    func_8000BB94_main(dst[D_8010A028_picture_imperfect][col])

#define PI_GROUP()                                                                                         \
    D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect] = HuSprGrpCreate(1, 0);                     \
    func_80055024_main(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0,                      \
                       D_8010A230_picture_imperfect, 0);                                                   \
    HuSprAttrReset(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0xFFFF);                 \
    HuSprAttrSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0x5000);                   \
    func_80054904_main(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0,                      \
                       D_8010A018_picture_imperfect[D_8010A028_picture_imperfect][0],                      \
                       D_8010A018_picture_imperfect[D_8010A028_picture_imperfect][1]);                     \
    HuSprPriSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0xFFFF)

#define PI_SPRITE(n, src)                                                                                  \
    n[D_8010A028_picture_imperfect] = InitEspriteSlot(src, 0, 1);            \
    func_8000BBD4_main(n[D_8010A028_picture_imperfect],                      \
                       D_8010A018_picture_imperfect[D_8010A028_picture_imperfect][0],                      \
                       D_8010A018_picture_imperfect[D_8010A028_picture_imperfect][1]);                     \
    func_8000BC48_main(n[D_8010A028_picture_imperfect], 0x1000);             \
    func_8000BCC8_main(n[D_8010A028_picture_imperfect], 0xF);                \
    func_8000BB94_main(n[D_8010A028_picture_imperfect])

    switch (D_8010A150_picture_imperfect) {
        case 0:
            PI_GROUP();
            for (i = 0; i < 5; i++) {
                PI_PIECE(D_8010A168_picture_imperfect, D_8010A232_picture_imperfect, i);
                PI_PIECE(D_8010A190_picture_imperfect, D_8010A23C_picture_imperfect, i);
                PI_PIECE(D_8010A1B8_picture_imperfect, D_8010A246_picture_imperfect, i);
                PI_PIECE(D_8010A1E0_picture_imperfect, D_8010A250_picture_imperfect, i);
                PI_PIECE(D_8010A208_picture_imperfect, D_8010A25A_picture_imperfect, i);
            }
            break;
        case 1:
            PI_GROUP();
            for (i = 0; i < 5; i++) {
                PI_PIECE(D_8010A168_picture_imperfect, D_8010A232_picture_imperfect, i);
                PI_PIECE(D_8010A190_picture_imperfect, D_8010A23C_picture_imperfect, i);
                PI_PIECE(D_8010A1B8_picture_imperfect, D_8010A246_picture_imperfect, i);
                PI_PIECE(D_8010A1E0_picture_imperfect, D_8010A250_picture_imperfect, i);
            }
            break;
        case 2:
        default:
            PI_GROUP();
            for (i = 0; i < 5; i++) {
                PI_PIECE(D_8010A168_picture_imperfect, D_8010A232_picture_imperfect, i);
                PI_PIECE(D_8010A190_picture_imperfect, D_8010A23C_picture_imperfect, i);
                PI_PIECE(D_8010A1B8_picture_imperfect, D_8010A246_picture_imperfect, i);
            }
            break;
    }
    PI_SPRITE(D_8010A26E_picture_imperfect, D_8010A264_picture_imperfect);
    PI_SPRITE(D_8010A276_picture_imperfect, D_8010A266_picture_imperfect);
    PI_SPRITE(D_8010A27E_picture_imperfect, D_8010A266_picture_imperfect);
    PI_SPRITE(D_8010A286_picture_imperfect, D_8010A268_picture_imperfect);
    PI_SPRITE(D_8010A28E_picture_imperfect, D_8010A26A_picture_imperfect);
    PI_SPRITE(D_8010A296_picture_imperfect, D_8010A26A_picture_imperfect);
    PI_SPRITE(D_8010A29E_picture_imperfect, D_8010A26C_picture_imperfect);
    D_8010A028_picture_imperfect++;
}

/* A player: play (CPU, piece drop, the bobbing marker), results, the finish. */
void func_80107820_picture_imperfect(omObjData* obj) {
    MgWork* pw = obj->data;
    PiPlayer* ex = pw->unk158;
    s8 i;
    s8 n;
    s8 pad;
    s16 se;
    s16 mus;
    s32 rows;
    s32 voice;
    PiPlayer* other;

    switch (func_800E6E8C_minigame()) {
        case 0:
            func_800DDD94_minigame(obj);
            break;
        case 2:
            pad = pw->unk57;
            D_800D20A1_main[pad] = 0;
            D_800CBB6E_main[pad] = 0;
            if (func_80049F98_main() + D_800D6A90_main != 0) {
                func_80108688_picture_imperfect(obj);
                break;
            }
            if (GwPlayer[pw->unk59].stat & 1) {
                func_801081E4_picture_imperfect(obj);
            }
            if (ex->unk05 == 0 && ex->unk06 == 0 && pw->unk38 != 1000.0f && 200.0f - pw->unk34 <= obj->trans.y) {
                se = func_8004AC98_main(0x3F3, pw->unk59);
                if (pw->unk59 & 1) {
                    func_8004AE00_main(se, 0x5C);
                } else {
                    func_8004AE00_main(se, 0x20);
                }
                omVibrate(pw->unk59, 2, 3, 10);
                func_800E4C88_minigame(obj, 3, obj->trans.x, ex->unk10 - 25.0f, obj->trans.z, 180.0f, 0);
                ex->unk14 = 0.0f;
                ex->unk05 = 1;
                D_8010A02C_picture_imperfect++;
                switch (D_8010A150_picture_imperfect) {
                    case 0:
                    default:
                        rows = 5;
                        break;
                    case 1:
                        rows = 4;
                        break;
                    case 2:
                        rows = 3;
                        break;
                }
                if (rows * 4 == D_8010A02C_picture_imperfect && D_80109FE0_picture_imperfect != -1) {
                    HuAudFXStop(D_80109FE0_picture_imperfect);
                    D_80109FE0_picture_imperfect = -1;
                    D_80109FE2_picture_imperfect = 0;
                }
            }
            if (ex->unk05 == 1) {
                if (ex->unk14 == 180.0f) {
                    ex->unk10 = 272.0f;
                    ex->unk14 = 0.0f;
                    ex->unk05 = 0;
                } else {
                    ex->unk14 += 20.0f;
                    ex->unk10 = sindf(ex->unk14) * 100.0f + 272.0f;
                }
                Hu3DModelPosSet(obj->model[2], obj->trans.x, ex->unk10, obj->trans.z);
            }
            if (ex->unk06 == 1 || ex->unk03 != 0) {
                D_800CDA7C_main[pw->unk57] &= 0x7FFF;
                D_800D5558_main[pw->unk57] &= 0x7FFF;
            }
            func_801083C0_picture_imperfect(pw->unk59);
            func_80108688_picture_imperfect(obj);
            func_80108C20_picture_imperfect(ex, pw->unk59);
            D_800EB748_minigame = 0.7f;
            func_800DDD94_minigame(obj);
            break;
        case 3:
            if (D_80109FE0_picture_imperfect != -1) {
                HuAudFXStop(D_80109FE0_picture_imperfect);
                D_80109FE0_picture_imperfect = -1;
                D_80109FE2_picture_imperfect = 0;
            }
            if (func_80049F98_main() + D_800D6A90_main != 0) {
                break;
            }
            if (ex->unk03 == 0) {
                func_80108A64_picture_imperfect(ex, pw->unk59);
            }
            switch (D_80109FE4_picture_imperfect) {
                case 1:
                    func_80109284_picture_imperfect(ex, pw->unk59);
                    break;
                case 2:
                    for (i = 0; i < 4; i++) {
                        if (obj != D_800EC598_minigame[i]) {
                            other = ((MgWork*)D_800EC598_minigame[i]->data)->unk158;
                            if (ex->unk04 < other->unk04) {
                                ex->unk07++;
                            }
                        }
                    }
                    n = 0;
                    if (pw->unk59 == 3) {
                        D_8010A110_picture_imperfect = 0;
                        for (i = 0; i < 4; i++) {
                            other = ((MgWork*)D_800EC598_minigame[i]->data)->unk158;
                            if (other->unk07 == 0) {
                                D_8010A110_picture_imperfect++;
                                D_80109FF8_picture_imperfect[n] = i;
                                n++;
                            }
                        }
                        D_80109FE4_picture_imperfect = 8;
                    }
                    break;
                case 8:
                    if (pw->unk59 == 3) {
                        if (D_8010A110_picture_imperfect == 1) {
                            D_8010A140_picture_imperfect[0] = D_80109FF8_picture_imperfect[0];
                        } else if (D_8010A110_picture_imperfect == 2) {
                            D_8010A140_picture_imperfect[0] = D_80109FF8_picture_imperfect[0];
                            D_8010A140_picture_imperfect[1] = D_80109FF8_picture_imperfect[1];
                        } else if (D_8010A110_picture_imperfect == 3) {
                            D_8010A140_picture_imperfect[0] = D_80109FF8_picture_imperfect[0];
                            D_8010A140_picture_imperfect[1] = D_80109FF8_picture_imperfect[1];
                            D_8010A140_picture_imperfect[2] = D_80109FF8_picture_imperfect[2];
                        } else {
                                if (ex->unk04 != 0) {
                                    D_8010A140_picture_imperfect[0] = D_80109FF8_picture_imperfect[0];
                                    D_8010A140_picture_imperfect[1] = D_80109FF8_picture_imperfect[1];
                                    D_8010A140_picture_imperfect[2] = D_80109FF8_picture_imperfect[2];
                                    D_8010A140_picture_imperfect[3] = D_80109FF8_picture_imperfect[3];
                                } else {
                                    D_80109FF8_picture_imperfect[0] = D_80109FF8_picture_imperfect[1] =
                                        D_80109FF8_picture_imperfect[2] = D_80109FF8_picture_imperfect[3] = -1;
                                }
                        }
                        D_80109FE4_picture_imperfect = 0x10;
                        if (pw->unk59 == 3) {
                            func_800E6F0C_minigame(4);
                        }
                    }
                    break;
            }
            func_800DDD94_minigame(obj);
            break;
        case 4:
            if (func_800E6E9C_minigame() == 12) {
                if (D_80109FE4_picture_imperfect == 0x10) {
                    if (pw->unk59 == D_80109FF8_picture_imperfect[0] || pw->unk59 == D_80109FF8_picture_imperfect[1]
                        || pw->unk59 == D_80109FF8_picture_imperfect[2]
                        || pw->unk59 == D_80109FF8_picture_imperfect[3]) {
                        func_800E5690_minigame(obj, 13);
                        switch (GwPlayer[pw->unk59].chr) {
                            case 0:
                            default:
                                voice = 2;
                                break;
                            case 1:
                                voice = 3;
                                break;
                            case 2:
                                voice = 7;
                                break;
                            case 3:
                                voice = 4;
                                break;
                            case 4:
                                voice = 5;
                                break;
                            case 5:
                                voice = 6;
                                break;
                            case 6:
                                voice = 8;
                                break;
                            case 7:
                                voice = 9;
                                break;
                        }
                        func_80045ED0_main((voice << 16) | 0x2F);
                        GwPlayer[pw->unk59].bonusCoin += 10;
                    } else {
                        func_800E5690_minigame(obj, 14);
                    }
                    func_800DDD94_minigame(obj);
                }
                if (pw->unk59 == 3) {
                    if (D_8010A110_picture_imperfect == 1) {
                            GMesCreate(0x16, GwPlayer[D_8010A140_picture_imperfect[0]].chr);
                            mus = 0x65;
                    } else if (D_8010A110_picture_imperfect == 2) {
                            GMesCreate(0x1E, GwPlayer[D_8010A140_picture_imperfect[0]].chr,
                                       GwPlayer[D_8010A140_picture_imperfect[1]].chr);
                            mus = 0x66;
                    } else if (D_8010A110_picture_imperfect == 3) {
                            GMesCreate(0x22, GwPlayer[D_8010A140_picture_imperfect[0]].chr,
                                       GwPlayer[D_8010A140_picture_imperfect[1]].chr,
                                       GwPlayer[D_8010A140_picture_imperfect[2]].chr);
                            mus = 0x66;
                    } else {
                            if (ex->unk04 != 0) {
                                GMesCreate(0x23, GwPlayer[D_8010A140_picture_imperfect[0]].chr,
                                           GwPlayer[D_8010A140_picture_imperfect[1]].chr,
                                           GwPlayer[D_8010A140_picture_imperfect[2]].chr,
                                           GwPlayer[D_8010A140_picture_imperfect[3]].chr);
                                mus = 0x66;
                            } else {
                                GMesCreate(0x20);
                                mus = 0x6C;
                            }
                    }
                    HuAudSeqPlay(mus);
                    D_8010A128_picture_imperfect.unk06 = 9;
                }
            } else {
                D_8010A128_picture_imperfect.unk06 = 9;
            }
            break;
    }
    func_8001C258_main(obj->model[1], 4, 4);
}

// masked 0: pw and ex swap $s3/$s4 (registers only); logic checked
#ifdef NON_MATCHING
/* CPU: wait a random time, then press A when the marker is on the row picked by difficulty. */
void func_801081E4_picture_imperfect(omObjData* obj) {
    s32 t2;
    s32 t1;
    s32 t0;
    u8 r;
    PiPlayer* ex;
    MgWork* pw;

    pw = obj->data;
    ex = pw->unk158;
    if (ex->unk18 != 0) {
        ex->unk18--;
        return;
    }
    switch (GwPlayer[pw->unk59].cpu_difficulty) {
        case 3:
            t2 = 9;
            t1 = 7;
            t0 = 5;
            break;
        case 2:
            t2 = 30;
            t1 = 10;
            t0 = 5;
            break;
        case 1:
        default:
            t2 = 75;
            t1 = 40;
            t0 = 20;
            break;
        case 0:
            t2 = 90;
            t1 = 70;
            t0 = 40;
            break;
    }
    r = (u32)(rand8() * 25) >> 6;
    if (r < t0) {
        if (ex->unk01 != 4) {
            return;
        }
    } else if (r < t1) {
        if (ex->unk01 != 3) {
            return;
        }
    } else if (r < t2) {
        if (ex->unk01 != 2) {
            return;
        }
    } else if (r < t1) { /* retail tests t1 again: row 1 is never picked */
        if (ex->unk01 != 1) {
            return;
        }
    } else if (ex->unk01 != 0) {
        return;
    }
    D_800D5558_main[pw->unk57] |= 0x8000;
    ex->unk18 = (rand8() * 15 >> 6) + 30;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_801081E4_picture_imperfect);
#endif

/* Scroll the picture rows (player 0 drives it, player 3 advances the clock). */
void func_801083C0_picture_imperfect(s8 player) {
    if (player == 0) {
        if (D_8010A044_picture_imperfect % 10 == 9) {
            D_8010A2AC_picture_imperfect[0]++;
            if (D_8010A2AC_picture_imperfect[0] >= 5) {
                D_8010A2AC_picture_imperfect[0] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
        if ((D_8010A044_picture_imperfect & 7) == 7) {
            D_8010A2AC_picture_imperfect[2]++;
            if (D_8010A2AC_picture_imperfect[2] >= 5) {
                D_8010A2AC_picture_imperfect[2] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
        if (D_8010A044_picture_imperfect % 6 == 5) {
            D_8010A2AC_picture_imperfect[3]++;
            if (D_8010A2AC_picture_imperfect[3] >= 5) {
                D_8010A2AC_picture_imperfect[3] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
        if ((D_8010A044_picture_imperfect & 3) == 3) {
            D_8010A2AC_picture_imperfect[4]++;
            if (D_8010A2AC_picture_imperfect[4] >= 5) {
                D_8010A2AC_picture_imperfect[4] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
        if (D_8010A044_picture_imperfect % 2 == 1) {
            D_8010A2AC_picture_imperfect[1]++;
            if (D_8010A2AC_picture_imperfect[1] >= 5) {
                D_8010A2AC_picture_imperfect[1] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
    } else if (player == 3) {
        D_8010A044_picture_imperfect++;
    }
}

/* A player's current row: show the scrolling column, stop it on A (score by column), go to the next row. */
void func_80108688_picture_imperfect(omObjData* obj) {
    MgWork* pw = obj->data;
    PiPlayer* ex = pw->unk158;
    s8 player = pw->unk59;
    s16 (*tbl)[5];
    s32 period;
    s32 more;
    s8 i;

    switch (ex->unk00) {
        case 0:
            tbl = D_8010A168_picture_imperfect;
            switch (D_8010A150_picture_imperfect) {
                case 1:
                    period = 8;
                    break;
                case 2:
                    period = 6;
                    break;
                case 0:
                default:
                    period = 10;
                    break;
            }
            break;
        case 1:
            tbl = D_8010A190_picture_imperfect;
            period = 2;
            break;
        case 2:
            tbl = D_8010A1B8_picture_imperfect;
            switch (D_8010A150_picture_imperfect) {
                case 0:
                default:
                    period = 8;
                    break;
                case 1:
                    period = 6;
                    break;
                case 2:
                    period = 4;
                    break;
            }
            break;
        case 3:
            tbl = D_8010A1E0_picture_imperfect;
            period = (D_8010A150_picture_imperfect == 0) ? 6 : 4;
            break;
        case 4:
            tbl = D_8010A208_picture_imperfect;
            period = 4;
            break;
        default:
            if (pw->unk38 == 1000.0f) {
                ex->unk06 = 1;
            }
            return;
    }
    if (func_80049F98_main() + D_800D6A90_main != 0) {
        for (i = 0; i < 5; i++) {
            func_8000BB94_main(tbl[player][i]);
        }
        return;
    }
    ex->unk01 = D_8010A030_picture_imperfect[D_8010A151_picture_imperfect][D_8010A2AC_picture_imperfect[ex->unk00]];
    if (ex->unk08 == 0) {
        ex->unk08 = period;
    } else {
        ex->unk08--;
    }
    for (i = 0; i < 5; i++) {
        if (ex->unk01 == i) {
            func_8000BB54_main(tbl[player][ex->unk01]);
        } else {
            func_8000BB94_main(tbl[player][i]);
        }
    }
    if (D_800D5558_main[pw->unk57] & 0x8000) {
        ex->unk08 = period - 2;
        switch (ex->unk01) {
            case 0:
                ex->unk03 = 10;
                break;
            case 1:
                ex->unk03 = 7;
                break;
            case 2:
                ex->unk03 = 5;
                break;
            case 3:
                ex->unk03 = 3;
                break;
            case 4:
                ex->unk03 = 1;
                break;
        }
        ex->unk04 += ex->unk03;
        D_80109FFC_picture_imperfect[player][ex->unk00] = ex->unk01;
        ex->unk01 = rand8() * 5 >> 8;
        if (ex->unk00 == 0) {
            ex->unk00 = 2;
        } else if (ex->unk00 == 1) {
            ex->unk00 = 10;
        } else {
            ex->unk00++;
            switch (D_8010A150_picture_imperfect) {
                case 0:
                    more = ex->unk00 < 5;
                    break;
                case 1:
                    more = ex->unk00 < 4;
                    break;
                case 2:
                default:
                    more = ex->unk00 < 3;
                    break;
            }
            if (!more) {
                ex->unk00 = 1;
            }
        }
    }
}

/* Hide the sprites of the row the player is on. */
void func_80108A64_picture_imperfect(PiPlayer* ex, s8 player) {
    s32 i;

    switch (ex->unk00) {
        case 0:
            for (i = 0; i < 5; i++) {
                func_8000BB94_main(D_8010A168_picture_imperfect[player][i]);
            }
            break;
        case 1:
            for (i = 0; i < 5; i++) {
                func_8000BB94_main(D_8010A190_picture_imperfect[player][i]);
            }
            break;
        case 2:
            for (i = 0; i < 5; i++) {
                func_8000BB94_main(D_8010A1B8_picture_imperfect[player][i]);
            }
            break;
        case 3:
            for (i = 0; i < 5; i++) {
                func_8000BB94_main(D_8010A1E0_picture_imperfect[player][i]);
            }
            break;
        case 4:
            for (i = 0; i < 5; i++) {
                func_8000BB94_main(D_8010A208_picture_imperfect[player][i]);
            }
            break;
    }
}

/* The score of the last stopped piece: coloured by value, flashes, then grows and fades. */
void func_80108C20_picture_imperfect(PiPlayer* ex, s8 player) {
    u8 color[3];
    s32 row;
    s32 y;
    s32 rows;

    if (ex->unk03 != 0) {
        switch (ex->unk03) {
            case 1:
                if (D_8010A116_picture_imperfect[player] != 0) {
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0x80;
                } else {
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0xFF;
                }
                break;
            case 3:
                if (D_8010A116_picture_imperfect[player] != 0) {
                    color[0] = 0;
                    color[1] = 0x80;
                    color[2] = 0x80;
                } else {
                    color[0] = 0;
                    color[1] = 0xFF;
                    color[2] = 0xFF;
                }
                break;
            case 5:
                if (D_8010A116_picture_imperfect[player] != 0) {
                    color[0] = 0;
                    color[1] = 0x80;
                    color[2] = 0;
                } else {
                    color[0] = 0;
                    color[1] = 0xFF;
                    color[2] = 0;
                }
                break;
            case 7:
                if (D_8010A116_picture_imperfect[player] != 0) {
                    color[0] = 0x80;
                    color[1] = 0x40;
                    color[2] = 0;
                } else {
                    color[0] = 0xFF;
                    color[1] = 0x80;
                    color[2] = 0;
                }
                break;
            case 10:
                if (D_8010A116_picture_imperfect[player] != 0) {
                    color[0] = 0x80;
                    color[1] = 0;
                    color[2] = 0;
                } else {
                    color[0] = 0xFF;
                    color[1] = 0;
                    color[2] = 0;
                }
                break;
        }
        switch (D_8010A150_picture_imperfect) {
            case 0:
                row = ex->unk00 - 1;
                break;
            case 1:
                if (ex->unk00 == 1) {
                    row = 0;
                } else if (ex->unk00 == 2) {
                    row = 1;
                } else if (ex->unk00 == 3) {
                    row = 2;
                } else {
                    row = 4;
                }
                break;
            case 2:
            default:
                if (ex->unk00 == 1) {
                    row = 1;
                } else if (ex->unk00 == 2) {
                    row = 3;
                } else {
                    row = 4;
                }
                break;
        }
        y = D_80109FE8_picture_imperfect[player][1] + D_8010A048_picture_imperfect[row];
        func_8000BEAC_main(D_8010A26E_picture_imperfect[player], color[0], color[1], color[2]);
        func_8000BE5C_main(D_8010A26E_picture_imperfect[player], ex->unk0C, ex->unk0C);
        func_8000BBFC_main(D_8010A26E_picture_imperfect[player], ex->unk0A);
        func_8000BBD4_main(D_8010A26E_picture_imperfect[player], D_80109FE8_picture_imperfect[player][0] - 25, y);
        func_8000BB54_main(D_8010A26E_picture_imperfect[player]);
        if (ex->unk03 == 10) {
            func_8000BEAC_main(D_8010A276_picture_imperfect[player], color[0], color[1], color[2]);
            func_8000BE5C_main(D_8010A276_picture_imperfect[player], ex->unk0C, ex->unk0C);
            func_8000BBFC_main(D_8010A276_picture_imperfect[player], ex->unk0A);
            func_8000BD50_main(D_8010A276_picture_imperfect[player], ex->unk03 / 10);
            func_8000BBD4_main(D_8010A276_picture_imperfect[player], D_80109FE8_picture_imperfect[player][0] - 14, y);
            func_8000BB54_main(D_8010A276_picture_imperfect[player]);
        } else {
            func_8000BB94_main(D_8010A276_picture_imperfect[player]);
        }
        func_8000BEAC_main(D_8010A27E_picture_imperfect[player], color[0], color[1], color[2]);
        func_8000BE5C_main(D_8010A27E_picture_imperfect[player], ex->unk0C, ex->unk0C);
        func_8000BBFC_main(D_8010A27E_picture_imperfect[player], ex->unk0A);
        func_8000BD50_main(D_8010A27E_picture_imperfect[player], ex->unk03 % 10);
        func_8000BBD4_main(D_8010A27E_picture_imperfect[player], D_80109FE8_picture_imperfect[player][0] + 2, y);
        func_8000BB54_main(D_8010A27E_picture_imperfect[player]);
        func_8000BEAC_main(D_8010A286_picture_imperfect[player], color[0], color[1], color[2]);
        func_8000BE5C_main(D_8010A286_picture_imperfect[player], ex->unk0C, ex->unk0C);
        func_8000BBFC_main(D_8010A286_picture_imperfect[player], ex->unk0A);
        func_8000BBD4_main(D_8010A286_picture_imperfect[player], D_80109FE8_picture_imperfect[player][0] + 30, y);
        func_8000BB54_main(D_8010A286_picture_imperfect[player]);
        if (D_8010A112_picture_imperfect[player] >= 11) {
            ex->unk0C += 0.05f;
            ex->unk0A -= 10;
            D_8010A116_picture_imperfect[player] = 0;
        } else {
            D_8010A112_picture_imperfect[player]++;
            D_8010A116_picture_imperfect[player] ^= 1;
        }
        if (ex->unk0A <= 0) {
            ex->unk0C = 1.0f;
            ex->unk0A = 0xFF;
            ex->unk03 = 0;
            D_8010A112_picture_imperfect[player] = 0;
            D_8010A116_picture_imperfect[player] = 0;
            switch (D_8010A150_picture_imperfect) {
                case 0:
                default:
                    rows = 5;
                    break;
                case 1:
                    rows = 4;
                    break;
                case 2:
                    rows = 3;
                    break;
            }
            D_8010A111_picture_imperfect++;
            if (rows * 4 == D_8010A111_picture_imperfect) {
                func_800E6F0C_minigame(3);
            }
        }
    } else {
        func_8000BB94_main(D_8010A26E_picture_imperfect[player]);
        func_8000BB94_main(D_8010A276_picture_imperfect[player]);
        func_8000BB94_main(D_8010A27E_picture_imperfect[player]);
        func_8000BB94_main(D_8010A286_picture_imperfect[player]);
    }
}

/* Score display: digits roll for 30 frames, then show the score, hide at 90. */
void func_80109284_picture_imperfect(PiPlayer* ex, s8 player) {
    if (D_8010A11A_picture_imperfect[player] < 30) {
        if (D_8010A11A_picture_imperfect[player] == 0) {
            HuAudFXPlay(0x3EC);
        }
        func_8000BD50_main(D_8010A28E_picture_imperfect[player], (u32)(rand8() * 5) >> 7);
        func_8000BBD4_main(D_8010A28E_picture_imperfect[player], D_80109FE8_picture_imperfect[player][0] - 32,
                           D_80109FE8_picture_imperfect[player][1]);
        func_8000BB54_main(D_8010A28E_picture_imperfect[player]);
        func_8000BD50_main(D_8010A296_picture_imperfect[player], (u32)(rand8() * 5) >> 7);
        func_8000BBD4_main(D_8010A296_picture_imperfect[player], D_80109FE8_picture_imperfect[player][0] - 12,
                           D_80109FE8_picture_imperfect[player][1]);
        func_8000BB54_main(D_8010A296_picture_imperfect[player]);
        func_8000BBD4_main(D_8010A29E_picture_imperfect[player], D_80109FE8_picture_imperfect[player][0] + 20,
                           D_80109FE8_picture_imperfect[player][1] + 4);
        func_8000BB54_main(D_8010A29E_picture_imperfect[player]);
    } else if (D_8010A11A_picture_imperfect[player] == 30) {
        HuAudFXPlay(0x3ED);
        if (ex->unk04 >= 10) {
            func_8000BD50_main(D_8010A28E_picture_imperfect[player], ex->unk04 / 10);
            func_8000BBD4_main(D_8010A28E_picture_imperfect[player], D_80109FE8_picture_imperfect[player][0] - 32,
                               D_80109FE8_picture_imperfect[player][1]);
        } else {
            func_8000BB94_main(D_8010A28E_picture_imperfect[player]);
        }
        func_8000BD50_main(D_8010A296_picture_imperfect[player], ex->unk04 % 10);
        func_8000BBD4_main(D_8010A296_picture_imperfect[player], D_80109FE8_picture_imperfect[player][0] - 12,
                           D_80109FE8_picture_imperfect[player][1]);
    } else if (D_8010A11A_picture_imperfect[player] == 90) {
        func_8000BB94_main(D_8010A296_picture_imperfect[player]);
        func_8000BB94_main(D_8010A28E_picture_imperfect[player]);
        func_8000BB94_main(D_8010A29E_picture_imperfect[player]);
        if (player == 3) {
            D_80109FE4_picture_imperfect = 2;
        }
    }
    D_8010A11A_picture_imperfect[player]++;
}

/* The framework's ground object: frames of the four quarters, divider, title sprites, the piece counter. */
void func_80109608_picture_imperfect(omObjData* obj) {
    PiGround* gd;
    s32 i;
    s32 x;
    s32 y;

    obj->func = func_80109AC4_picture_imperfect;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            D_8010A122_picture_imperfect = func_8000B838_main(0x3F0002);
        }
        D_8010A152_picture_imperfect = HuSprGrpCreate(1, 0);
        func_80055024_main(D_8010A152_picture_imperfect, 0, D_8010A122_picture_imperfect, 0);
        HuSprAttrReset(D_8010A152_picture_imperfect, 0, 0xFFFF);
        HuSprAttrSet(D_8010A152_picture_imperfect, 0, 0x5000);
        func_80054904_main(D_8010A152_picture_imperfect, 0, D_80109FE8_picture_imperfect[i][0],
                           D_80109FE8_picture_imperfect[i][1]);
        HuSprPriSet(D_8010A152_picture_imperfect, 0, 0xFF);
    }
    D_8010A122_picture_imperfect = func_8000B838_main(0x3F0003);
    D_8010A154_picture_imperfect = HuSprGrpCreate(1, 0);
    func_80055024_main(D_8010A154_picture_imperfect, 0, D_8010A122_picture_imperfect, 0);
    HuSprAttrReset(D_8010A154_picture_imperfect, 0, 0xFFFF);
    HuSprAttrSet(D_8010A154_picture_imperfect, 0, 0x1000);
    func_80054904_main(D_8010A154_picture_imperfect, 0, 160, 120);
    HuSprPriSet(D_8010A154_picture_imperfect, 0, 0xF0);
    D_8010A122_picture_imperfect = func_8000B838_main(0x3F0001);
    D_8010A156_picture_imperfect = InitEspriteSlot(D_8010A122_picture_imperfect, 0, 1);
    func_8000BBD4_main(D_8010A156_picture_imperfect, 160, 120);
    func_8000BC48_main(D_8010A156_picture_imperfect, 0x1000);
    func_8000BCC8_main(D_8010A156_picture_imperfect, 0xF);
    func_8000BB54_main(D_8010A156_picture_imperfect);
    x = 128;
    y = 108;
    switch (D_8010A150_picture_imperfect) {
        case 0:
        default:
            D_8010A122_picture_imperfect = func_8000B838_main(0x3F0008);
            break;
        case 1:
            D_8010A122_picture_imperfect = func_8000B838_main(0x3F000A);
            break;
        case 2:
            D_8010A122_picture_imperfect = func_8000B838_main(0x3F000C);
            break;
    }
    D_8010A158_picture_imperfect = InitEspriteSlot(D_8010A122_picture_imperfect, 0, 1);
    func_8000BBD4_main(D_8010A158_picture_imperfect, x, y);
    func_8000BC48_main(D_8010A158_picture_imperfect, 0x1000);
    func_8000BCC8_main(D_8010A158_picture_imperfect, 0xF);
    func_8000BB54_main(D_8010A158_picture_imperfect);
    switch (D_8010A150_picture_imperfect) {
        case 0:
        default:
            D_8010A122_picture_imperfect = func_8000B838_main(0x3F0009);
            break;
        case 1:
            D_8010A122_picture_imperfect = func_8000B838_main(0x3F000B);
            break;
        case 2:
            D_8010A122_picture_imperfect = func_8000B838_main(0x3F000D);
            break;
    }
    D_8010A15A_picture_imperfect = InitEspriteSlot(D_8010A122_picture_imperfect, 0, 1);
    func_8000BBD4_main(D_8010A15A_picture_imperfect, x, y);
    func_8000BC48_main(D_8010A15A_picture_imperfect, 0x1000);
    func_8000BCC8_main(D_8010A15A_picture_imperfect, 0xF);
    func_8000BB54_main(D_8010A15A_picture_imperfect);
    D_8010A2A6_picture_imperfect = InitEspriteSlot(D_8010A26A_picture_imperfect, 0, 1);
    func_8000BBD4_main(D_8010A2A6_picture_imperfect, 225, 100);
    func_8000BC48_main(D_8010A2A6_picture_imperfect, 0x1000);
    func_8000BCC8_main(D_8010A2A6_picture_imperfect, 0xF);
    func_8000BB94_main(D_8010A2A6_picture_imperfect);
    D_8010A2A8_picture_imperfect = InitEspriteSlot(D_8010A26A_picture_imperfect, 0, 1);
    func_8000BBD4_main(D_8010A2A8_picture_imperfect, 245, 100);
    func_8000BC48_main(D_8010A2A8_picture_imperfect, 0x1000);
    func_8000BCC8_main(D_8010A2A8_picture_imperfect, 0xF);
    func_8000BB94_main(D_8010A2A8_picture_imperfect);
    D_8010A2AA_picture_imperfect = InitEspriteSlot(D_8010A26C_picture_imperfect, 0, 1);
    func_8000BBD4_main(D_8010A2AA_picture_imperfect, 277, 104);
    func_8000BC48_main(D_8010A2AA_picture_imperfect, 0x1000);
    func_8000BCC8_main(D_8010A2AA_picture_imperfect, 0xF);
    func_8000BB94_main(D_8010A2AA_picture_imperfect);
    obj->data = gd = HuMemAllocTag(sizeof(PiGround), 0x7918);
    memset(gd, 0, sizeof(PiGround));
    gd->unk03 = 1;
    gd->unk04 = 0;
    gd->unk08 = 0.5f;
    func_800E1370_minigame(obj, 2, -8.0f);
}

/* The ground object: the title intro (counter, fade, shrink to the corner), and the results title. */
void func_80109AC4_picture_imperfect(omObjData* obj) {
    f32 t;
    f32 u;
    s32 x;
    s32 y;

    if (func_800E6E8C_minigame() == 0) {
        switch (D_8010A150_picture_imperfect) {
            case 0:
            default:
                func_8000BD50_main(D_8010A2A6_picture_imperfect, 5);
                break;
            case 1:
                func_8000BD50_main(D_8010A2A6_picture_imperfect, 4);
                break;
            case 2:
                func_8000BD50_main(D_8010A2A6_picture_imperfect, 3);
                break;
        }
        func_8000BD50_main(D_8010A2A8_picture_imperfect, 0);
        if (func_800E6E9C_minigame() == 1) {
            func_8000BB54_main(D_8010A2A6_picture_imperfect);
            func_8000BB54_main(D_8010A2A8_picture_imperfect);
            func_8000BB54_main(D_8010A2AA_picture_imperfect);
        } else if (func_800E6E9C_minigame() >= 27) {
            switch (D_8010A054_picture_imperfect) {
                case 0:
                    if (D_8010A055_picture_imperfect == 0xFF) {
                        HuAudFXPlay(0x3F6);
                    }
                    func_8000BBFC_main(D_8010A15A_picture_imperfect, D_8010A055_picture_imperfect);
                    D_8010A055_picture_imperfect -= 5;
                    if (D_8010A055_picture_imperfect == 0) {
                        func_8000BB94_main(D_8010A2A6_picture_imperfect);
                        func_8000BB94_main(D_8010A2A8_picture_imperfect);
                        func_8000BB94_main(D_8010A2AA_picture_imperfect);
                        D_8010A054_picture_imperfect++;
                    }
                    break;
                case 1:
                    D_8010A050_picture_imperfect -= 0.04f;
                    t = D_8010A056_picture_imperfect / 50.0f;
                    u = 1.0f - t;
                    x = u * 128.0f + t * 160.0f;
                    y = u * 108.0f + t * 120.0f;
                    if (D_8010A056_picture_imperfect == 0) {
                        D_8010A124_picture_imperfect = HuAudFXPlay(0x3F5);
                    }
                    D_8010A056_picture_imperfect++;
                    if (D_8010A050_picture_imperfect > 0.02f) {
                        func_8000BE5C_main(D_8010A156_picture_imperfect, D_8010A050_picture_imperfect,
                                           D_8010A050_picture_imperfect);
                        func_8000BE5C_main(D_8010A158_picture_imperfect, D_8010A050_picture_imperfect,
                                           D_8010A050_picture_imperfect);
                        func_8000BBD4_main(D_8010A158_picture_imperfect, x, y);
                    } else {
                        D_8010A050_picture_imperfect = 0.0f;
                        D_8010A056_picture_imperfect = 0;
                        D_8010A054_picture_imperfect++;
                    }
                    break;
                case 2:
                    func_8000BB94_main(D_8010A156_picture_imperfect);
                    func_8000BB94_main(D_8010A158_picture_imperfect);
                    func_8000BB94_main(D_8010A15A_picture_imperfect);
                    if (D_8010A056_picture_imperfect >= 11) {
                        D_8010A054_picture_imperfect++;
                    } else {
                        D_8010A056_picture_imperfect++;
                    }
                    break;
                case 3:
                    D_8010A056_picture_imperfect = 0;
                    func_800E6F0C_minigame(1);
                    HuAudFXStop(D_8010A124_picture_imperfect);
                    break;
            }
        }
    } else if (func_800E6E8C_minigame() == 3) {
        if (GMesStatGet() == 0 && func_800E6E9C_minigame() >= 11) {
            D_8010A050_picture_imperfect += 0.04f;
            if (D_8010A050_picture_imperfect > 0.5f) {
                D_8010A050_picture_imperfect = 0.5f;
                if (D_80109FE4_picture_imperfect == 0) {
                    D_80109FE4_picture_imperfect = 1;
                }
            }
        }
        switch (D_80109FE4_picture_imperfect) {
            case 4:
            case 8:
            case 16:
                HuSprAttrSet(D_8010A154_picture_imperfect, 0, 0x5000);
                break;
            default:
                func_8000BE5C_main(D_8010A158_picture_imperfect, D_8010A050_picture_imperfect,
                                   D_8010A050_picture_imperfect);
                func_8000BBD4_main(D_8010A158_picture_imperfect, 160, 120);
                func_8000BB54_main(D_8010A158_picture_imperfect);
                func_8000BE5C_main(D_8010A15A_picture_imperfect, D_8010A050_picture_imperfect,
                                   D_8010A050_picture_imperfect);
                func_8000BBFC_main(D_8010A15A_picture_imperfect, 0xFF);
                func_8000BBD4_main(D_8010A15A_picture_imperfect, 160, 120);
                func_8000BB54_main(D_8010A15A_picture_imperfect);
                break;
        }
    }
}
