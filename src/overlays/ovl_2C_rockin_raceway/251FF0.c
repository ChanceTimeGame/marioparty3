#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "game/hmfman.h"

// m1 rr1: Rockin' Raceway (four karts race laps of a track; boost by tapping the buttons in rhythm)

/* One kart (D_80111B30, 4 of them, 0x70 each; the object keeps a pointer to it in work[]) */
typedef struct RrRacer {
    /* 0x00 */ s16 unk00; /* racer index */
    /* 0x02 */ u16 unk02; /* 0 driving, 1 spun out, 2 boosted */
    /* 0x04 */ s16 unk04; /* sound ids */
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A; /* player */
    /* 0x0C */ s16 unk0C; /* pad */
    /* 0x0E */ s16 unk0E; /* character */
    /* 0x10 */ s16 unk10; /* CPU */
    /* 0x12 */ u16 unk12; /* CPU difficulty */
    /* 0x14 */ u16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C; /* rank */
    /* 0x1E */ u16 unk1E; /* button expected next */
    /* 0x20 */ u16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ char unk2C[2];
    /* 0x2E */ u16 unk2E; /* lane */
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34; /* frame counter */
    /* 0x38 */ f32 unk38; /* speed */
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u16 unk4C; /* track node */
    /* 0x4E */ char unk4E[2];
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ Vec unk58; /* position */
    /* 0x64 */ Vec unk64; /* rotation */
} RrRacer; /* size 0x70 */

/* A lane of the track (D_80111B40, 0x24 each) */
typedef struct RrLane {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ Vec* unk0C;
    /* 0x10 */ char unk10[0x10];
    /* 0x20 */ u16* unk20;
} RrLane; /* size 0x24 */

/* A kart pose snapshot (D_80111B3C, [2][4]) */
typedef struct RrPose {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ Vec unk04;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ Vec unk1C;
} RrPose; /* size 0x28 */

/* An item box (D_80111B48, 8 of them) */
typedef struct RrItem {
    /* 0x00 */ u16 unk00; /* active */
    /* 0x02 */ s16 unk02; /* models */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ Vec unk0C; /* position */
    /* 0x18 */ Vec unk18; /* velocity */
} RrItem; /* size 0x24 */

/* Saved state of a smoke model (D_80111B50, 12 of them) */
typedef struct RrSmokeSave {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ Vec unk18;
    /* 0x24 */ Vec unk24;
} RrSmokeSave; /* size 0x30 */

/* A sprite effect (D_80111B5C, 16 of them) */
typedef struct RrEffect {
    /* 0x00 */ u16 unk00; /* active */
    /* 0x02 */ s16 unk02; /* model */
    /* 0x04 */ f32 unk04; /* frame */
    /* 0x08 */ f32 unk08; /* frame speed */
    /* 0x0C */ Vec unk0C; /* position */
    /* 0x18 */ Vec unk18; /* velocity */
    /* 0x24 */ Vec unk24; /* scale */
} RrEffect; /* size 0x30 */

/* Shared work (D_80111B68) */
typedef struct RrWork {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ s16 unk04;
} RrWork;

/* A racer's standing while ranking */
typedef struct RrRank {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} RrRank; /* size 0x18 */

// main
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004A208_main(void);
void func_8004A950_main(void);
s32 func_8000B638_main(void);
u16 GWMgRecordGet(s16);
void func_80017D24_main(f32 (*m)[4], f32, f32, f32);
void func_8008A070_main(f32 (*m)[4]);
s32 WipeStatGet(void);
s32 WipeCreateOut(s32, s32);
void* DataRead(s32 dirAndFile);
void DataClose(void*);

extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;
extern u16 D_800D5558_main[];
extern Vec CRot;

// rockin_raceway (outside rr1's range)
void func_801096A0_rockin_raceway(RrRacer* r);
void func_801099AC_rockin_raceway(void);
void func_80109DA8_rockin_raceway(void);
f32 func_8010A258_rockin_raceway(s32 lane, f32 dist, f32 pos, f32 speed, u16* node, f32* arg5, Vec* outPos, Vec* outRot);
u16 func_8010A48C_rockin_raceway(u16 lane, u16 node);
s16 func_8010A4C0_rockin_raceway(s32 dirAndFile);
void func_8010A504_rockin_raceway(void);
void func_8010A5E4_rockin_raceway(s16 lane, s32 chr);
void func_8010B124_rockin_raceway(void);
void func_8010B774_rockin_raceway(void);
void func_8010CB5C_rockin_raceway(RrRacer* r, f32 arg1);
void func_8010D5B8_rockin_raceway(void);
void func_8010E2E4_rockin_raceway(void);
void func_8010E344_rockin_raceway(s32, s32, s32, s32);
f32 func_8010E504_rockin_raceway(f32, f32);
f32 func_8010E608_rockin_raceway(f32, f32, f32);
f32 func_8010E7C8_rockin_raceway(f32, f32, f32);
void func_8010EC0C_rockin_raceway(omObjData* obj, void* data);
void* func_8010EC38_rockin_raceway(omObjData* obj);
s16 func_8010EC8C_rockin_raceway(HuSprite_Unk84_Struct*, void*);
s16 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct*, s16, void*);
void func_8010FA78_rockin_raceway(u16, HuSprite_Unk84_Struct*, u16, void*);

void func_80105C24_rockin_raceway(omObjData* obj);
void func_80105CB0_rockin_raceway(omObjData* obj);
void func_80106A5C_rockin_raceway(omObjData* obj);
void func_80106B28_rockin_raceway(void);
void func_80106DC8_rockin_raceway(omObjData* obj);
void func_801071D8_rockin_raceway(omObjData* obj);
void func_8010769C_rockin_raceway(omObjData* obj);
void func_80107958_rockin_raceway(RrRacer* r);
void func_80107A38_rockin_raceway(RrRacer* r);
void func_80107BFC_rockin_raceway(RrRacer* r);
void func_80107D04_rockin_raceway(omObjData* obj);
void func_80107E78_rockin_raceway(s32 slot, s16 arg1);
void func_8010803C_rockin_raceway(s32* order);
s32 func_80108464_rockin_raceway(void);
void func_80108578_rockin_raceway(void);
s16 func_80108760_rockin_raceway(Vec* pos, Vec* vel, s16 time);
void func_80108864_rockin_raceway(omObjData* obj);
u16 func_80108A80_rockin_raceway(Vec* pos);
void func_80108BAC_rockin_raceway(void);
void func_80108D84_rockin_raceway(void);
void func_80108ED4_rockin_raceway(omObjData* obj);
void func_80108F8C_rockin_raceway(f32 x, f32 y, f32 z);
void func_80109044_rockin_raceway(void);
void func_80109134_rockin_raceway(void);
void func_80109208_rockin_raceway(void);
void func_80109384_rockin_raceway(omObjData* obj);
s16 func_801094EC_rockin_raceway(Vec* pos, Vec* vel, Vec* scale, f32 speed);

extern s32 D_801112C0_rockin_raceway[]; /* last node per lane */
extern s16 D_801112D2_rockin_raceway[];
extern f32 D_801112E0_rockin_raceway[];
extern f32 D_801112F0_rockin_raceway[];
extern f32 D_80111300_rockin_raceway[];
extern f32 D_80111304_rockin_raceway[];
extern s32 D_80111320_rockin_raceway[];
extern u8 D_801114D4_rockin_raceway[];
extern u32 D_80111558_rockin_raceway;
extern s32 D_8011155C_rockin_raceway;
extern s16 D_8011155E_rockin_raceway;
extern u16 D_80111562_rockin_raceway[];
extern s32 D_80111570_rockin_raceway[];
extern u16 D_80111580_rockin_raceway[];
extern u32 D_80111590_rockin_raceway[];

extern omObjData* D_80111AC4_rockin_raceway;
extern s32 D_80111AC8_rockin_raceway;
extern s32 D_80111ACC_rockin_raceway;
extern s32 D_80111AD0_rockin_raceway;
extern s32 D_80111AD4_rockin_raceway;
extern s32 D_80111AD8_rockin_raceway; /* race state */
extern s32 D_80111ADC_rockin_raceway;
extern s16 D_80111AE0_rockin_raceway;
extern s32 D_80111AE4_rockin_raceway;
extern s32 D_80111AE8_rockin_raceway;
extern s32 D_80111AEC_rockin_raceway;
extern RrRacer* D_80111B30_rockin_raceway;
extern s16 D_80111B34_rockin_raceway;
extern s16 D_80111B36_rockin_raceway;
extern s16 D_80111B38_rockin_raceway;
extern s16 D_80111B3A_rockin_raceway;
extern RrPose* D_80111B3C_rockin_raceway;
extern RrLane* D_80111B40_rockin_raceway;
extern f32 D_80111B44_rockin_raceway;
extern RrItem* D_80111B48_rockin_raceway;
extern omObjData* D_80111B4C_rockin_raceway;
extern RrSmokeSave* D_80111B50_rockin_raceway;
extern s16 D_80111B54_rockin_raceway;
extern omObjData* D_80111B58_rockin_raceway;
extern RrEffect* D_80111B5C_rockin_raceway;
extern void* D_80111B60_rockin_raceway;
extern s16 D_80111B64_rockin_raceway;
extern RrWork* D_80111B68_rockin_raceway;
extern s16 D_80111BD4_rockin_raceway;
extern s16 D_80111BD6_rockin_raceway;
extern s32 D_80111BD8_rockin_raceway;
extern s32 D_80111C30_rockin_raceway;

/* "ＳＴＡＲＴ" */
const s16 D_80111740_rockin_raceway[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000 };

/* "ＦＩＮＩＳＨ" */
const s16 D_8011174C_rockin_raceway[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000, 0x0000, 0x0000 };

void func_801059A0_rockin_raceway(void) {
    u8 cam;

    Hu3DAnimInit(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(0x40);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 67.0f, 16.0f, 98.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 1.0f, 50.0f, -108.0f);
    HmfLightMaxSet(2);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 6000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_80111ACC_rockin_raceway = 0;
    D_80111AD0_rockin_raceway = 0;
    D_80111AD4_rockin_raceway = 0;
    D_80111AD8_rockin_raceway = 0;
    D_80111ADC_rockin_raceway = 0;
    D_80111AE0_rockin_raceway = 0;
    D_80111BD4_rockin_raceway = -1;
    D_80111BD6_rockin_raceway = -1;
    D_80111B36_rockin_raceway = 0;
    D_80111B38_rockin_raceway = 0;
    D_80111AE4_rockin_raceway = 0;
    D_80111AEC_rockin_raceway = 5400;
    D_80111AE8_rockin_raceway = GWMgRecordGet(3);
    if (D_80111AE8_rockin_raceway == 0) {
        D_80111AE8_rockin_raceway = 9000;
    }
    D_80111BD8_rockin_raceway = 0;
    D_80111C30_rockin_raceway = 0;
    D_80111B68_rockin_raceway = HuMemAllocTag(0x40, 0x7918);
    D_80111AC4_rockin_raceway = omAddObj(0x20, 0, 0, -1, func_80105C24_rockin_raceway);
    func_80045010_main(D_80111740_rockin_raceway, 1);
    func_80045010_main(D_8011174C_rockin_raceway, 1);
}

void func_80105C24_rockin_raceway(omObjData* obj) {
    obj->func = func_80105CB0_rockin_raceway;
    func_80109DA8_rockin_raceway();
    func_801099AC_rockin_raceway();
    func_80108D84_rockin_raceway();
    func_80109208_rockin_raceway();
    func_8010A504_rockin_raceway();
    func_8010B124_rockin_raceway();
    func_80106B28_rockin_raceway();
    func_80108578_rockin_raceway();
    func_8010E2E4_rockin_raceway();
    func_8010B774_rockin_raceway();
    func_8010D5B8_rockin_raceway();
    if (_CheckFlag(0xA) != 0) {
        D_80111AC8_rockin_raceway = 1;
    }
}


INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80105CB0_rockin_raceway);

void func_80106A5C_rockin_raceway(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_80106A80_rockin_raceway(omObjData* obj) {
    s16* fade;

    if (D_8011155C_rockin_raceway != 0) {
        if (D_8011155C_rockin_raceway == 1) {
            obj->func = func_80106A5C_rockin_raceway;
        }
        D_8011155C_rockin_raceway--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8011155C_rockin_raceway = 16;
        fade = &D_8011155E_rockin_raceway;
        WipeCreateOut(0, *fade);
        HuAudSeqFadeOut(*fade);
        func_8004AB0C_main(*fade);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106B28_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106DC8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801071D8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010769C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107958_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107A38_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107BFC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107D04_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107E78_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010803C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108464_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108578_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108760_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108864_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108A80_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108BAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108D84_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108ED4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108F8C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109044_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109134_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109208_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109384_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801094EC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801096A0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801097A0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801098D8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801099AC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109A04_rockin_raceway);

void func_80109CF8_rockin_raceway(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109D00_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109D54_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109DA8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A258_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A48C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A4C0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A504_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A5E4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A990_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010AAAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B124_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B2B8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B5DC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B774_rockin_raceway);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_80111838_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B89C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C0D8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C5E0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C7CC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C9BC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C9CC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CA1C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CADC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CB5C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CC10_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CE90_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D104_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D114_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D134_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D288_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D5B8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D600_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D944_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D9C4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E08C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E2E4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E344_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E39C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E504_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E608_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E7C8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E7E0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E840_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E8A0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E93C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E994_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EB04_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EB84_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EC0C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EC38_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EC8C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010F874_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FA78_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FBAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FFB8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80110C38_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80110D90_rockin_raceway);
