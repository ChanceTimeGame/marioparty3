#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "game/hmfman.h"
#include "game/util.h"
#include "math.h"
#include "game/gamemes.h"
#include "game/audio.h"

// m1 rr1: Rockin' Raceway (four karts race laps of a track; boost by tapping the buttons in rhythm)

/* One kart (D_80111B30, 4 of them, 0x70 each; the object keeps a pointer to it in work[]) */
typedef struct RrRacer {
    /* 0x00 */ u16 unk00; /* racer index */
    /* 0x02 */ u16 unk02; /* 0 driving, 1 spun out, 2 boosted */
    /* 0x04 */ s16 unk04; /* sound ids */
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A; /* player */
    /* 0x0C */ u16 unk0C; /* pad */
    /* 0x0E */ u16 unk0E; /* character */
    /* 0x10 */ u16 unk10; /* CPU */
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

typedef struct RrPoseSet {
    RrPose p[4];
} RrPoseSet; /* size 0xA0 */

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
void func_80017D24_main(HuMtx4F m, f32, f32, f32);
void func_8008A070_main(HuMtx4F m);
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
s32 func_8010A48C_rockin_raceway(u16 lane, u16 node);
s16 func_8010A4C0_rockin_raceway(s32 dirAndFile);
void func_8010A504_rockin_raceway(void);
void func_8010A5E4_rockin_raceway(s16 lane, s16 chr);
void func_8010B124_rockin_raceway(void);
void func_8010B774_rockin_raceway(void);
void func_8010CB5C_rockin_raceway(RrRacer* r, f32 arg1);
void func_8010D5B8_rockin_raceway(void);
void func_8010E2E4_rockin_raceway(void);
void func_8010E344_rockin_raceway(s32, s32, s32, s16);
f32 func_8010E504_rockin_raceway(f32, f32);
f32 func_8010E608_rockin_raceway(f32, f32, f32);
f32 func_8010E7C8_rockin_raceway(f32, f32, f32);
void func_8010EC0C_rockin_raceway(omObjData* obj, void* data);
void* func_8010EC38_rockin_raceway(omObjData* obj);
s16 func_8010EC8C_rockin_raceway(HuSprite_Unk84_Struct*, void*);
s16 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct*, u16, void*);
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
s32 func_80108760_rockin_raceway(Vec* pos, Vec* vel, s16 time);
void func_80108864_rockin_raceway(omObjData* obj);
s32 func_80108A80_rockin_raceway(Vec* pos);
void func_80108BAC_rockin_raceway(void);
void func_80108D84_rockin_raceway(void);
void func_80108ED4_rockin_raceway(omObjData* obj);
void func_80108F8C_rockin_raceway(f32 x, f32 y, f32 z);
void func_80109044_rockin_raceway(void);
void func_80109134_rockin_raceway(void);
void func_80109208_rockin_raceway(void);
void func_80109384_rockin_raceway(omObjData* obj);
s32 func_801094EC_rockin_raceway(Vec* pos, Vec* vel, Vec* scale, f32 speed);

extern s32 D_801112C0_rockin_raceway[]; /* last node per lane */
/* D_801112D0 is {s16, s16} node pairs per lane; the label sits on the second half, so this view is shifted by 2 */
typedef struct RrNodeView {
    /* 0x00 */ u16 unk00; /* D_801112D0[i].second */
    /* 0x02 */ u16 unk02; /* D_801112D0[i + 1].first */
} RrNodeView;
extern RrNodeView D_801112D2_rockin_raceway[];
extern f32 D_801112E0_rockin_raceway[];
extern f32 D_801112F0_rockin_raceway[];
extern f32 D_80111300_rockin_raceway[];
extern f32 D_80111304_rockin_raceway[];
extern s32 D_80111320_rockin_raceway[];
extern u8 D_801114D4_rockin_raceway[];
extern u32 D_80111558_rockin_raceway;
extern s32 D_8011155C_rockin_raceway;
extern s16 D_8011155E_rockin_raceway;
extern u16 D_80111562_rockin_raceway[][2];
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
extern RrPoseSet* D_80111B3C_rockin_raceway;
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

/* A camera preset: seven floats handed to func_8010C7CC */
typedef struct RrCam {
    /* 0x00 */ f32 v[7];
} RrCam; /* size 0x1C */

#define RR_CAM(c, n) func_8010C7CC_rockin_raceway((c).v[0], (c).v[1], (c).v[2], (c).v[3], (c).v[4], (c).v[5], (c).v[6], n)

/* Mirror of gamemes.c's GAMEMES (0x74), for the timer message position */
typedef struct RrGameMes {
    /* 0x00 */ char unk00[0x60];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ char unk68[0xC];
} RrGameMes; /* size 0x74 */
extern RrGameMes gMesData[];

f64 fabs(f64);
void func_80106A80_rockin_raceway(omObjData* obj);
void func_80109D00_rockin_raceway(s32* order);
void func_80109D54_rockin_raceway(s32* times);
void func_8010B2B8_rockin_raceway(void);
void func_8010B5DC_rockin_raceway(s32* times);
void func_8010C7CC_rockin_raceway(f32, f32, f32, f32, f32, f32, f32, s32 frames);
void func_8010C9BC_rockin_raceway(void);
void func_8010C9CC_rockin_raceway(void);
void func_8010CA1C_rockin_raceway(void);
void func_8010D104_rockin_raceway(void);
void func_8010D114_rockin_raceway(void);
void func_8010D600_rockin_raceway(void);
void func_8010D9C4_rockin_raceway(s32);
void func_8010E08C_rockin_raceway(s16);
void func_8010E39C_rockin_raceway(void);
void func_801097A0_rockin_raceway(void);
void func_801098D8_rockin_raceway(void);

extern RrCam D_8011136C_rockin_raceway;
extern RrCam D_80111388_rockin_raceway;
extern RrCam D_801113A4_rockin_raceway;
extern RrCam D_801113C0_rockin_raceway;
extern RrCam D_801113DC_rockin_raceway;
extern RrCam D_801113F8_rockin_raceway;
extern f32 D_80111410_rockin_raceway; /* D_801113F8.v[6] */
extern u16 D_80111AEA_rockin_raceway; /* low half of D_80111AE8 */
extern s32 D_80111AF0_rockin_raceway[4];
extern s16 D_80111B7A_rockin_raceway;
extern s16 D_80111C2C_rockin_raceway;
extern s16 D_80111C2E_rockin_raceway;

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


void func_80105CB0_rockin_raceway(omObjData* obj) {
    s32 times[2];
    omObjData* leadObj;
    omObjData* otherObj;
    RrRacer* lead;
    RrRacer* other;
    s32 i;
    s16 mes;
    f32 t;

    times[0] = 0;
    times[1] = 0;
    func_80106A80_rockin_raceway(obj);
    func_8010E39C_rockin_raceway();
    if (D_80111BD6_rockin_raceway >= 0) {
        if (--D_80111BD6_rockin_raceway == 0) {
            D_80111BD4_rockin_raceway = HuAudFXPlay(0x470);
            func_8004AAD0_main(D_80111BD4_rockin_raceway, 0x40);
            HuAudFXPitchSet(D_80111BD4_rockin_raceway, 0);
            D_80111BD6_rockin_raceway = -1;
        }
    }
    switch (D_80111AD8_rockin_raceway) {
        case 0:
            D_80111AD8_rockin_raceway = 1;
            D_80111ADC_rockin_raceway = 0;
            break;
        case 1:
            switch (D_80111ADC_rockin_raceway) {
                case 0:
                    HuAudFXPlay(0x46F);
                    RR_CAM(D_8011136C_rockin_raceway, 19);
                    D_80111C2E_rockin_raceway = 0;
                    D_80111ADC_rockin_raceway++;
                    break;
                case 2:
                    RR_CAM(D_80111388_rockin_raceway, 75);
                    D_80111C2E_rockin_raceway = 0;
                    D_80111ADC_rockin_raceway++;
                    break;
                case 4:
                    if (D_80111AD0_rockin_raceway >= 5) {
                        D_80111ADC_rockin_raceway++;
                    }
                    break;
                case 6:
                    RR_CAM(D_801113A4_rockin_raceway, 75);
                    D_80111C2E_rockin_raceway = 0;
                    D_80111AD0_rockin_raceway = 0;
                    D_80111ADC_rockin_raceway++;
                    break;
                case 8:
                    RR_CAM(D_801113C0_rockin_raceway, 45);
                    D_80111C2E_rockin_raceway = 2;
                    D_80111ADC_rockin_raceway++;
                    break;
                case 10:
                    if (D_80111AD0_rockin_raceway == 3) {
                    } else if (D_80111AD0_rockin_raceway >= 4) {
                        D_80111AD8_rockin_raceway = 2;
                        D_80111ADC_rockin_raceway = 0;
                    }
                    break;
                default:
                    if (D_80111ADC_rockin_raceway == 9 && D_80111AD0_rockin_raceway == 20) {
                        GMesCreate(3);
                        HuAudSeqPlay(0x2E);
                    }
                    if (D_80111C2C_rockin_raceway == 0) {
                        if (D_80111ADC_rockin_raceway == 3) {
                            HuAudSeqPlay(0x6D);
                        }
                        D_80111AD0_rockin_raceway = 0;
                        D_80111ADC_rockin_raceway++;
                    }
                    break;
            }
            break;
        case 2:
            if (D_80111AD0_rockin_raceway == 8) {
                HuAudFXPlay(0x46C);
            }
            if (D_80111AD0_rockin_raceway == 30) {
                D_80111AE0_rockin_raceway = 1;
            }
            if (D_80111AD0_rockin_raceway == 20) {
                func_8010C9BC_rockin_raceway();
                func_8010CA1C_rockin_raceway();
            }
            func_8010803C_rockin_raceway(D_80111AF0_rockin_raceway);
            if (D_80111AE0_rockin_raceway != 0) {
                times[0] = ++D_80111AE4_rockin_raceway;
                times[1] = D_80111AE8_rockin_raceway;
                func_8010B5DC_rockin_raceway(times);
                func_80109D00_rockin_raceway(D_80111AF0_rockin_raceway);
                func_80109D54_rockin_raceway(times);
                func_8010D600_rockin_raceway();
                D_80111AEC_rockin_raceway--;
            }
            if (D_80111AEC_rockin_raceway == 900) {
                mes = GMesCreate(0x1A, 30, 156, 56);
                gMesData[mes].unk60 = 156.0f;
                gMesData[mes].unk64 = 56.0f;
            } else if (D_80111AEC_rockin_raceway < 900) {
                func_8003F578_main((D_80111AEC_rockin_raceway + 29) / 30);
                if (D_80111AEC_rockin_raceway == 0) {
                    func_8003F5C0_main();
                }
            }
            if ((D_80111B34_rockin_raceway = func_80108464_rockin_raceway()) != -1 || D_80111AEC_rockin_raceway <= 0) {
                func_8010D104_rockin_raceway();
                func_8010C9CC_rockin_raceway();
                RR_CAM(D_801113DC_rockin_raceway, 10);
                D_80111C2E_rockin_raceway = 2;
                if (D_80111B34_rockin_raceway != -1) {
                    leadObj = D_800EC598_minigame[D_80111AF0_rockin_raceway[0]];
                    lead = func_8010EC38_rockin_raceway(leadObj);
                    for (i = 1; i < 4; i++) {
                        otherObj = D_800EC598_minigame[D_80111AF0_rockin_raceway[i]];
                        other = func_8010EC38_rockin_raceway(otherObj);
                        if (other->unk02 == 1) {
                            continue;
                        }
                        if (fabs(lead->unk48 - other->unk48) < 30.0) {
                            D_80111B38_rockin_raceway = 3;
                            break;
                        }
                        if (lead->unk48 - other->unk48 < 100.0) {
                            if (fabs(leadObj->trans.x - otherObj->trans.x) < 30.0) {
                                D_80111B38_rockin_raceway = 3;
                            } else {
                                D_80111B38_rockin_raceway = 1;
                            }
                            break;
                        }
                    }
                }
                for (i = 0; i < 4; i++) {
                    lead = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
                    if (lead->unk04 != -1) {
                        HuAudFXStop(lead->unk04);
                        lead->unk04 = -1;
                    }
                    if (lead->unk06 != -1) {
                        HuAudFXStop(lead->unk06);
                        lead->unk06 = -1;
                    }
                }
                GMesCreate(0xE);
                HuAudSeqFadeOut(120);
                D_80111AD8_rockin_raceway = 3;
                D_80111ADC_rockin_raceway = 0;
            }
            break;
        case 3:
            if (D_80111AD0_rockin_raceway == 3 && D_80111BD4_rockin_raceway != -1) {
                func_8004AAD0_main(D_80111BD4_rockin_raceway, 110);
                HuAudFXPitchSet(D_80111BD4_rockin_raceway, 200);
            }
            if (GMesStatGet() == 0) {
                D_80111AD8_rockin_raceway = 4;
                D_80111ADC_rockin_raceway = 0;
            }
            break;
        case 4:
            if (D_80111AD0_rockin_raceway >= 15) {
                if (D_80111B34_rockin_raceway != -1) {
                    GwPlayer[((RrRacer*)func_8010EC38_rockin_raceway(D_800EC598_minigame[D_80111B34_rockin_raceway]))->unk0A].bonusCoin += 10;
                    if (D_80111B38_rockin_raceway != 0) {
                        func_80109044_rockin_raceway();
                        func_801097A0_rockin_raceway();
                        func_8010E08C_rockin_raceway(D_80111B34_rockin_raceway);
                        D_80111AD8_rockin_raceway = 5;
                    } else {
                        D_80111AD8_rockin_raceway = 6;
                    }
                } else {
                    D_80111AD8_rockin_raceway = 6;
                }
                D_80111ADC_rockin_raceway = 0;
            }
            break;
        case 5:
            D_80111B3A_rockin_raceway = 1;
            if (D_80111ADC_rockin_raceway >= 1 && D_80111ADC_rockin_raceway <= 28) {
                if (D_80111AD0_rockin_raceway >= 4.5f) {
                    if (D_80111ADC_rockin_raceway == 10) {
                        func_80107E78_rockin_raceway(0, 9);
                    }
                    D_80111ADC_rockin_raceway++;
                    D_80111AD0_rockin_raceway = 0;
                }
            } else if (D_80111ADC_rockin_raceway < 33) {
                if (D_80111AD0_rockin_raceway >= 7.5f) {
                    D_80111ADC_rockin_raceway++;
                    D_80111AD0_rockin_raceway = 0;
                }
            } else if (D_80111AD0_rockin_raceway >= 30.0f) {
                D_80111ADC_rockin_raceway++;
                D_80111AD0_rockin_raceway = 0;
            }
            if (D_80111ADC_rockin_raceway < 30) {
                func_8010D9C4_rockin_raceway(D_80111ADC_rockin_raceway);
                if (D_80111BD4_rockin_raceway != -1) {
                    t = D_80111ADC_rockin_raceway / 30.0f;
                    func_8004AAD0_main(D_80111BD4_rockin_raceway, func_8010E7C8_rockin_raceway(t, 64.0f, 110.0f));
                    HuAudFXPitchSet(D_80111BD4_rockin_raceway, (s16)func_8010E7C8_rockin_raceway(t, 0.0f, 200.0f));
                }
                RR_CAM(D_801113F8_rockin_raceway, 1);
            } else if (D_80111ADC_rockin_raceway < 34) {
                if (D_80111BD4_rockin_raceway != -1) {
                    func_8004AAD0_main(D_80111BD4_rockin_raceway, 110);
                    HuAudFXPitchSet(D_80111BD4_rockin_raceway, 200);
                }
                func_8010D9C4_rockin_raceway(29);
                func_8010C7CC_rockin_raceway(65535.0f, 65535.0f, 65535.0f, 65535.0f, 65535.0f, 65535.0f,
                                             D_80111410_rockin_raceway - (D_80111ADC_rockin_raceway - 29) * 100, 1);
            } else {
                RR_CAM(D_801113DC_rockin_raceway, 1);
                func_80109134_rockin_raceway();
                func_801098D8_rockin_raceway();
                D_80111B3A_rockin_raceway = 0;
                D_80111AD8_rockin_raceway = 6;
                D_80111ADC_rockin_raceway = 0;
            }
            break;
        case 6:
            switch (D_80111ADC_rockin_raceway) {
                case 0:
                    if (D_80111AD0_rockin_raceway >= 15.0f || D_80111B38_rockin_raceway == 0) {
                        if (D_80111B34_rockin_raceway != -1 && D_80111AE4_rockin_raceway < D_80111AE8_rockin_raceway) {
                            D_80111AE8_rockin_raceway = D_80111AE4_rockin_raceway;
                            GWMgRecordSet(3, D_80111AEA_rockin_raceway);
                            GMesCreate(0x1B);
                            D_80111B7A_rockin_raceway = 15;
                            D_80111AD4_rockin_raceway = 99;
                            D_80111B36_rockin_raceway = 1;
                            D_80111ADC_rockin_raceway++;
                        } else {
                            D_80111ADC_rockin_raceway = 2;
                        }
                        times[0] = D_80111AE4_rockin_raceway;
                        times[1] = D_80111AE8_rockin_raceway;
                        func_8010B5DC_rockin_raceway(times);
                        D_80111AD0_rockin_raceway = 0;
                    }
                    break;
                case 1:
                    if (D_80111AD0_rockin_raceway >= 75.0f) {
                        D_80111ADC_rockin_raceway++;
                        D_80111AD0_rockin_raceway = 0;
                    }
                    break;
                case 2:
                    if (D_80111B34_rockin_raceway != -1) {
                        lead = func_8010EC38_rockin_raceway(D_800EC598_minigame[D_80111B34_rockin_raceway]);
                        GMesCreate(0x16, lead->unk0E);
                        if (D_80111B36_rockin_raceway == 0) {
                            HuAudSeqPlay(0x65);
                            D_80111AD4_rockin_raceway = 138;
                        } else {
                            HuAudSeqPlay(0x6A);
                        }
                        func_8004ACE0_main(0x28F, lead->unk0A);
                        func_8010C9BC_rockin_raceway();
                        func_8010D114_rockin_raceway();
                    } else {
                        if (D_80111B36_rockin_raceway == 0) {
                            HuAudSeqPlay(0x6C);
                            D_80111AD4_rockin_raceway = 144;
                        }
                        GMesCreate(0x20);
                    }
                    D_80111ADC_rockin_raceway++;
                    D_80111AD0_rockin_raceway = 0;
                    break;
                case 3:
                    if (GMesStatGet() == 0) {
                        D_80111ADC_rockin_raceway++;
                        D_80111AD0_rockin_raceway = 0;
                    }
                    break;
                case 4:
                    if (D_80111AD0_rockin_raceway >= 15) {
                        WipeCreateOut(0, 16);
                        HuAudSeqFadeOut(16);
                        func_8004AB0C_main(16);
                        D_80111AD0_rockin_raceway = 0;
                        D_80111ADC_rockin_raceway++;
                    }
                    break;
                default:
                    if (WipeStatGet() == 0) {
                        obj->func = func_80106A5C_rockin_raceway;
                    }
                    break;
            }
            break;
    }
    func_8010B2B8_rockin_raceway();
    D_80111ACC_rockin_raceway++;
    if (D_80111558_rockin_raceway == D_80111AD8_rockin_raceway) {
        D_80111AD0_rockin_raceway++;
    } else {
        D_80111AD0_rockin_raceway = 0;
        D_80111558_rockin_raceway = D_80111AD8_rockin_raceway;
    }
}

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

void func_80106B28_rockin_raceway(void) {
    RrLane* track;
    omObjData* obj;
    RrRacer* r;
    s32 i;
    s32 j;
    u16 lane;

    D_80111B30_rockin_raceway = HuMemAllocTag(sizeof(RrRacer) * 4, 0x7918);
    D_80111B34_rockin_raceway = -1;
    D_80111B3A_rockin_raceway = 0;
    D_80111B3C_rockin_raceway = HuMemAllocTag(sizeof(RrPose) * 8, 0x7918);
    memset(D_80111B3C_rockin_raceway, 0, sizeof(RrPose) * 8);
    i = 0;
    r = D_80111B30_rockin_raceway;
    for (; i < 4; i++) {
        memset(r, 0, sizeof(RrRacer));
        r->unk00 = i;
        r->unk0A = D_80111562_rockin_raceway[i][0];
        r->unk0C = GwPlayer[r->unk0A].pad;
        r->unk0E = GwPlayer[r->unk0A].chr;
        if (GwPlayer[r->unk0A].stat & 1) {
            r->unk10 = 1;
        } else {
            r->unk10 = 0;
        }
        r->unk12 = GwPlayer[r->unk0A].cpu_difficulty;
        r->unk2E = GwPlayer[r->unk0A].group;
        for (j = 0; j < 4; j++) {
            if (D_80111570_rockin_raceway[r->unk2E] == -1) {
                D_80111570_rockin_raceway[r->unk2E] = r->unk2E;
                break;
            }
            lane = r->unk2E;
            r->unk2E = lane + 1;
            if (r->unk2E >= 4) {
                r->unk2E = lane - 3;
            }
        }
        track = &D_80111B40_rockin_raceway[r->unk2E];
        r->unk30 = track->unk08 - D_80111B44_rockin_raceway;
        if (r->unk30 < 0.0f) {
            r->unk30 = 0.0f;
        }
        func_8010A5E4_rockin_raceway(r->unk2E, r->unk0E);
        r++;
        obj = omAddObj(i + 0x10, 10, 60, -1, func_80106DC8_rockin_raceway);
        D_800EC598_minigame[D_800EC280_minigame] = obj;
        func_8010EC0C_rockin_raceway(obj, &D_80111B30_rockin_raceway[i]);
        D_800EC280_minigame++;
    }
}

void func_80106DC8_rockin_raceway(omObjData* obj) {
    RrRacer* r;
    s32 i;
    s32 level;
    s32 mdl;
    u16 chr;

    r = func_8010EC38_rockin_raceway(obj);
    obj->func = func_801071D8_rockin_raceway;
    chr = r->unk0E;
    obj->model[0] = func_8000B108_main(D_80111580_rockin_raceway[chr] | 0x4D0000, 0x299);
    obj->model[1] = func_8000B108_main(9, 0x299);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            obj->model[3] = func_8000B108_main(D_80111580_rockin_raceway[chr] | 0x4D0000, 0x28D);
            func_8001FA68_main(obj->model[3]);
            func_8001F9E4_main(obj->model[3], 0x40);
            func_8001C514_main(obj->model[3]);
        } else {
            obj->model[3 + i] = Hu3DModelLink(obj->model[3]);
        }
        func_8001C8E4_main(obj->model[3 + i], D_80111590_rockin_raceway[i % 3]);
    }
    switch (r->unk12) {
        case 0:
            level = 0;
            break;
        case 1:
            level = 1;
            break;
        case 2:
            level = 2;
            break;
        default:
            level = 3;
            break;
    }
    r->unk02 = 0;
    r->unk04 = -1;
    r->unk06 = -1;
    r->unk08 = 0;
    r->unk34 = 0;
    r->unk38 = 0.0f;
    r->unk24 = 0.0f;
    r->unk28 = 1.0f;
    r->unk1C = 0;
    r->unk1E = 0;
    r->unk20 = 0;
    r->unk14 = level * 200 + rand16() % 300 + 300;
    r->unk16 = rand16() % 1000;
    if (r->unk14 != 0) {
        r->unk16 %= r->unk14;
    }
    r->unk18 = 0;
    r->unk1A = 0;
    r->unk3C = r->unk40 = r->unk44 = r->unk48 = r->unk54 = 0.0f;
    r->unk58.x = r->unk58.y = r->unk58.z = 0.0f;
    r->unk64.x = r->unk64.y = r->unk64.z = 0.0f;
    r->unk44 = func_8010A258_rockin_raceway(r->unk2E, r->unk30, r->unk44, 0.0f, &r->unk4C, &r->unk50, &r->unk58, &r->unk64);
    obj->model[2] = mdl = func_8000B108_main(0x4D0009, 0x99);
    Hu3DModelPosSet((s16)mdl, r->unk58.x - 69.9999988079071045, r->unk58.y, r->unk58.z);
    func_8001C92C_main((s16)mdl, 0.0f);
    obj->trans.x = r->unk58.x;
    obj->trans.y = r->unk58.y;
    obj->trans.z = r->unk58.z;
    obj->rot.x = r->unk64.x;
    obj->rot.y = r->unk64.y;
    obj->rot.z = r->unk64.z;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
}

void func_801071D8_rockin_raceway(omObjData* obj) {
    RrRacer* r;
    s32 i;
    HmfModel* src;
    HmfModel* dst;
    RrPose* pose;

    r = func_8010EC38_rockin_raceway(obj);
    if (D_80111B3A_rockin_raceway != 0) {
        for (i = 0; i < 2; i++) {
            if (D_80111B3C_rockin_raceway[i].p[r->unk0A].unk02 != 0) {
                func_8001C258_main(obj->model[3 + i], 4, 0);
            } else {
                func_8001C258_main(obj->model[3 + i], 4, 4);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            func_8001C258_main(obj->model[3 + i], 4, 4);
        }
    }
    for (i = 1; i >= 0; i--) {
        if (i != 0) {
            src = &HmfModelData[obj->model[2 + i]];
        } else {
            src = &HmfModelData[obj->model[0]];
        }
        dst = &HmfModelData[obj->model[3 + i]];
        dst->pos.x = src->pos.x;
        dst->pos.y = src->pos.y;
        dst->pos.z = src->pos.z;
        dst->rot.x = src->rot.x;
        dst->rot.y = src->rot.y;
        dst->rot.z = src->rot.z;
        dst->scale.x = src->scale.x;
        dst->scale.y = src->scale.y;
        dst->scale.z = src->scale.z;
    }
    switch (D_80111AD8_rockin_raceway) {
        case 2:
            func_8001C92C_main(obj->model[2], 1.0f);
            if (r->unk10 != 0) {
                func_8010769C_rockin_raceway(obj);
            }
            if (D_80111AE0_rockin_raceway == 0) {
                r->unk38 = 0.0f;
                r->unk24 = 0.0f;
                r->unk28 = 1.0f;
            }
            r->unk38 -= 0.009f;
            if (r->unk38 < 0.01f) {
                r->unk38 = 0.0f;
            }
            if (r->unk38 == 0.0f) {
                r->unk1E = 0xE000;
            } else {
                r->unk24 += 20.0f;
                if (r->unk24 >= 360.0f) {
                    r->unk24 -= 360.0f;
                    func_8004ACE0_main(!(r->unk08 & 1) ? 0x45A : 0x463, r->unk0A);
                    r->unk08++;
                }
            }
            switch (r->unk02) {
                case 0:
                case 2:
                    func_80107958_rockin_raceway(r);
                    if (D_80111AE0_rockin_raceway == 0) {
                        r->unk38 = 0.0f;
                        r->unk24 = 0.0f;
                        r->unk28 = 1.0f;
                    }
                    func_80107A38_rockin_raceway(r);
                    break;
                case 1:
                    func_80107BFC_rockin_raceway(r);
                    break;
            }
            func_8010CB5C_rockin_raceway(r, 0.03f);
            func_80107D04_rockin_raceway(obj);
            break;
        case 3:
        case 4:
        case 6:
            switch (r->unk02) {
                case 0:
                case 2:
                    r->unk38 = func_8010E7C8_rockin_raceway(0.1f, r->unk38, 0.65f);
                    func_80107A38_rockin_raceway(r);
                    r->unk24 += 20.0f;
                    if (r->unk24 >= 360.0f) {
                        r->unk24 -= 360.0f;
                    }
                    break;
                case 1:
                    if (r->unk00 == D_80111B34_rockin_raceway) {
                        r->unk02 = 0;
                        r->unk28 = 1.0f;
                        r->unk24 = 0.0f;
                        r->unk40 = 0.0f;
                    } else {
                        func_80107BFC_rockin_raceway(r);
                    }
                    break;
            }
            if (D_80111AD8_rockin_raceway == 6 && r->unk00 == D_80111B34_rockin_raceway) {
                func_8010CB5C_rockin_raceway(r, 0.1f);
            }
            func_80107D04_rockin_raceway(obj);
            break;
        case 5:
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], 0.6f, 0.6f, 0.6f);
    r->unk34++;
}

void func_8010769C_rockin_raceway(omObjData* obj) {
    RrRacer* r;
    s32 level;
    s32 press;

    press = 0;
    r = func_8010EC38_rockin_raceway(obj);
    switch (r->unk12) {
        case 0:
            level = 0;
            break;
        case 1:
            level = 1;
            break;
        case 2:
            level = 2;
            break;
        default:
            level = 3;
            break;
    }
    switch (func_8010A48C_rockin_raceway(r->unk2E, r->unk4C)) {
        case 1:
            if (r->unk28 >= 0.5f) {
                r->unk1A = 1;
            }
            break;
        case 2:
            r->unk1A = 1;
            break;
    }
    if (r->unk1A == 0) {
        if (r->unk16 < 0 && r->unk02 != 2) {
            if (++r->unk16 == 0) {
                r->unk16 = 0;
            } else {
                D_800D5558_main[r->unk0C] = 0;
                return;
            }
        } else {
            if (D_80111AD0_rockin_raceway > 60) {
                r->unk16 += (rand8() & 3) + 2;
            }
            if (r->unk16 >= r->unk14) {
                r->unk16 = -(rand16() % 30 + 30);
            }
        }
        if (r->unk38 < D_80111300_rockin_raceway[level * 2]) {
            r->unk1A = 1;
        } else if (r->unk02 == 2) {
            r->unk1A = 1;
        } else if (r->unk38 < D_80111304_rockin_raceway[level * 2] && !(rand8() & 0x3F)) {
            r->unk1A = 1;
        }
        if (r->unk1A == 0) {
            goto end;
        }
    }
    r->unk18++;
    if (r->unk18 > D_80111320_rockin_raceway[level]) {
        r->unk18 = 0;
        r->unk1A = 0;
        press = 1;
    }
end:
    if (press) {
        if (r->unk1E == 0x8000) {
            D_800D5558_main[r->unk0C] = 0x8000;
        } else {
            D_800D5558_main[r->unk0C] = 0x6000;
        }
    }
}

void func_80107958_rockin_raceway(RrRacer* r) {
    if (D_800D5558_main[r->unk0C] & r->unk1E) {
        r->unk38 += D_801112E0_rockin_raceway[r->unk1C] * 0.1f;
        if (r->unk38 >= 1.0f) {
            r->unk38 = 1.0f;
        }
        if (D_800D5558_main[r->unk0C] == 0x8000) {
            r->unk1E = 0x6000;
        } else {
            r->unk1E = 0x8000;
        }
        r->unk28 -= 0.05f;
        if (r->unk28 < 0.0f) {
            r->unk28 = 0.0f;
        }
    }
}

void func_80107A38_rockin_raceway(RrRacer* r) {
    if (r->unk28 <= 0.0f && D_80111AD8_rockin_raceway == 2) {
        r->unk02 = 1;
        func_8004AC98_main(0x458, r->unk0A);
        func_8004AC98_main(0x459, r->unk0A);
        func_8010E344_rockin_raceway(0x286, 3, 3, r->unk0A);
        if (D_80111AD8_rockin_raceway == 2) {
            omVibrate(r->unk0A, 2, 2, 20);
        }
    } else {
        r->unk28 += 0.008f;
        if (r->unk28 > 1.0f) {
            r->unk28 = 1.0f;
        }
    }
    if (r->unk02 == 2) {
        if (!(r->unk34 & 0x1F)) {
            func_80108F8C_rockin_raceway(r->unk58.x + 20.000000298023224, r->unk58.y + 139.9999976158142, r->unk58.z);
        }
        r->unk28 = 1.0f;
        if (--r->unk20 == 0) {
            if (D_80111AD8_rockin_raceway == 2) {
                if (r->unk04 != -1) {
                    HuAudFXStop(r->unk04);
                    r->unk04 = -1;
                }
                if (r->unk06 != -1) {
                    HuAudFXStop(r->unk06);
                    r->unk06 = -1;
                }
            }
            r->unk20 = 0;
            r->unk02 = 0;
        }
    }
}

void func_80107BFC_rockin_raceway(RrRacer* r) {
    r->unk38 = 0.0f;
    if (r->unk28 >= 0.975f) {
        r->unk40 = func_8010E608_rockin_raceway(r->unk38, r->unk40, 30.0f);
        if (func_8010E504_rockin_raceway(0.0f, r->unk40) < 0.5f) {
            r->unk24 = 0.0f;
            r->unk40 = 0.0f;
            r->unk02 = 0;
        }
    } else {
        r->unk40 += 30.0f;
        if (r->unk40 >= 360.0f) {
            r->unk40 -= 360.0f;
        }
        if (r->unk34 & 3) {
            func_801096A0_rockin_raceway(r);
        }
        r->unk28 += 0.025f;
    }
}

void func_80107D04_rockin_raceway(omObjData* obj) {
    HuMtx4F mtx;
    RrRacer* r;
    f32 speed;

    r = func_8010EC38_rockin_raceway(obj);
    speed = r->unk38 * D_801112F0_rockin_raceway[r->unk1C] * 3.0f;
    r->unk3C = sindf(r->unk24) * r->unk38 * 30.0f;
    r->unk44 = func_8010A258_rockin_raceway(r->unk2E, r->unk30, r->unk44, speed, &r->unk4C, &r->unk50, &r->unk58, &r->unk64);
    if (r->unk3C > 0.0f) {
        func_8008A070_main(mtx);
        func_80017D24_main(mtx, r->unk3C, 0.0f, 0.0f);
        func_80017C10_main((Mtx*)mtx, 0.0f, 0.0f, 47.0f);
        r->unk54 = mtx[3][2];
    } else {
        r->unk54 = 47.0f;
    }
    r->unk48 = r->unk44 + r->unk54;
    obj->trans.x = r->unk58.x;
    obj->trans.y = r->unk58.y;
    obj->trans.z = r->unk58.z;
    obj->rot.x = r->unk64.x + r->unk3C;
    obj->rot.y = r->unk64.y + r->unk40;
}

void func_80107E78_rockin_raceway(s32 slot, s16 arg1) {
    omObjData* obj;
    RrRacer* r;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = D_800EC598_minigame[i];
        r = func_8010EC38_rockin_raceway(obj);
        if (D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk02 == 0) {
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk02 = 1;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk00 = arg1;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk04.x = obj->trans.x;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk04.y = obj->trans.y;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk04.z = obj->trans.z;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk10.x = obj->rot.x;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk10.y = obj->rot.y;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk10.z = obj->rot.z;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk1C.x = obj->scale.x;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk1C.y = obj->scale.y;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk1C.z = obj->scale.z;
        }
    }
}

void func_8010803C_rockin_raceway(s32* order) {
    RrRank rank[4];
    RrRank tmp;
    RrRacer* r;
    s32 i;
    s32 j;
    s32 k;
    s32 swap;

    for (i = 0; i < 4; i++) {
        r = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        rank[i].unk00 = i;
        rank[i].unk04 = r->unk4C;
        rank[i].unk08 = r->unk2E;
        rank[i].unk0C = D_800EC598_minigame[i]->trans.x + r->unk54;
        rank[i].unk10 = r->unk50;
        rank[i].unk14 = r->unk48;
    }
    for (i = 0; i < 64; i++) {
        j = rand8() & 3;
        k = rand8() & 3;
        tmp = rank[j];
        rank[j] = rank[k];
        rank[k] = tmp;
    }
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            swap = 0;
            if (rank[i].unk04 >= D_801112C0_rockin_raceway[rank[i].unk08] - 1
                && rank[j].unk04 >= D_801112C0_rockin_raceway[rank[j].unk08] - 1
                && rank[i].unk0C < rank[j].unk0C) {
                swap = 1;
            } else if (rank[i].unk04 < rank[j].unk04) {
                swap = 1;
            } else if (rank[i].unk04 == rank[j].unk04 && rank[i].unk10 < rank[j].unk10) {
                swap = 1;
            }
            if (swap) {
                tmp = rank[i];
                rank[i] = rank[j];
                rank[j] = tmp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        r = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        for (j = 0; j < 4; j++) {
            if (rank[j].unk00 == i) {
                break;
            }
        }
        if (j >= 4) {
            j = 3;
        }
        r->unk1C = j;
    }
    for (i = 0; i < 4; i++) {
        order[i] = ((RrRacer*)func_8010EC38_rockin_raceway(D_800EC598_minigame[rank[i].unk00]))->unk0A;
    }
}

s32 func_80108464_rockin_raceway(void) {
    RrRacer* r;
    s32 i;

    for (i = 0; i < 4; i++) {
        r = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        if (r->unk4C >= D_801112C0_rockin_raceway[r->unk2E] - 1
            && D_800EC598_minigame[i]->trans.x + r->unk54 >= 340.00000953674316) {
            break;
        }
    }
    if (i < 4) {
        for (i = 0; i < 4; i++) {
            if (((RrRacer*)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]))->unk1C == 0) {
                return i;
            }
        }
    }
    return -1;
}

void func_80108578_rockin_raceway(void) {
    Vec rot;
    Vec pos;
    RrItem* item;
    RrRacer* r;
    s32 i;

    D_80111B48_rockin_raceway = item = HuMemAllocTag(sizeof(RrItem) * 8, 0x7918);
    for (i = 0; i < 8; i++, item++) {
        memset(item, 0, sizeof(RrItem));
        if (i == 0) {
            item->unk02 = func_8000B108_main(0x4D0007, 0x99);
            item->unk04 = func_8000B108_main(0x4D0008, 0x99);
        } else {
            item->unk02 = Hu3DModelLink(D_80111B48_rockin_raceway->unk02);
            item->unk04 = Hu3DModelLink(D_80111B48_rockin_raceway->unk04);
        }
        func_8001C258_main(item->unk02, 4, 4);
        func_8001C258_main(item->unk04, 4, 4);
        item->unk0A = 0;
        item->unk06 = 0;
        item->unk00 = 0;
        item->unk0C.x = item->unk0C.y = item->unk0C.z = 0.0f;
        item->unk18.x = item->unk18.y = item->unk18.z = 0.0f;
    }
    for (i = 0, r = D_80111B30_rockin_raceway; i < 4; i++, r++) {
        func_8010A258_rockin_raceway(r->unk2E, r->unk30, 1500.0f, 0.0f, NULL, NULL, &pos, &rot);
        func_80108760_rockin_raceway(&pos, NULL, 90);
        func_80108760_rockin_raceway(&D_80111B40_rockin_raceway[i].unk0C[D_801112D2_rockin_raceway[i].unk00], NULL, 30);
    }
    omSetStatBit(omAddObj(0x1E, 0, 0, -1, func_80108864_rockin_raceway), 0xA0);
}

s32 func_80108760_rockin_raceway(Vec* pos, Vec* vel, s16 time) {
    RrItem* item;
    s32 i;

    for (i = 0, item = D_80111B48_rockin_raceway; i < 8; i++, item++) {
        if (item->unk00 == 0) {
            break;
        }
    }
    if (i >= 8) {
        return -1;
    }
    item->unk00 = 1;
    item->unk08 = time;
    item->unk0A = 0;
    if (pos != NULL) {
        item->unk0C.x = pos->x;
        item->unk0C.y = pos->y;
        item->unk0C.z = pos->z;
    } else {
        item->unk0C.x = item->unk0C.y = item->unk0C.z = 0.0f;
    }
    /* retail reads pos here, not vel (both callers pass NULL) */
    if (vel != NULL) {
        item->unk18.x = pos->x;
        item->unk18.y = pos->y;
        item->unk18.z = pos->z;
    } else {
        item->unk18.x = item->unk18.y = item->unk18.z = 0.0f;
    }
    Hu3DModelPosSet(item->unk02, item->unk0C.x, item->unk0C.y, item->unk0C.z);
    Hu3DModelPosSet(item->unk04, item->unk0C.x, item->unk0C.y, item->unk0C.z);
    return i;
}

void func_80108864_rockin_raceway(omObjData* obj) {
    RrItem* item;
    s32 i;
    s16 on;
    s16 off;

    if (func_80049F98_main() + D_800D6A90_main == 0 && D_80111AD8_rockin_raceway == 2) {
        func_80108BAC_rockin_raceway();
    }
    for (i = 0, item = D_80111B48_rockin_raceway; i < 8; i++, item++) {
        if (item->unk00 == 0) {
            continue;
        }
        if (func_80049F98_main() + D_800D6A90_main == 0 && D_80111AD8_rockin_raceway == 2) {
            if (++item->unk06 >= item->unk08) {
                item->unk06 = 0;
                item->unk0A ^= 1;
            }
        }
        if (item->unk0A & 1) {
            on = item->unk04;
            off = item->unk02;
        } else {
            on = item->unk02;
            off = item->unk04;
        }
        func_8001C258_main(on, 4, 0);
        func_8001C258_main(off, 4, 4);
        item->unk0C.x += item->unk18.x;
        item->unk0C.y += item->unk18.y;
        item->unk0C.z += item->unk18.z;
        Hu3DModelPosSet(on, item->unk0C.x, item->unk0C.y, item->unk0C.z);
        Hu3DModelPosSet(off, item->unk0C.x, item->unk0C.y, item->unk0C.z);
        Hu3DModelScaleSet(on, 1.0f, 1.0f, 1.0f);
        Hu3DModelScaleSet(off, 1.0f, 1.0f, 1.0f);
        if (D_80111AD8_rockin_raceway >= 3) {
            item->unk00 = 0;
            func_8001C258_main(on, 4, 4);
            func_8001C258_main(off, 4, 4);
        }
    }
}

s32 func_80108A80_rockin_raceway(Vec* pos) {
    RrItem* item;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;

    for (i = 0, item = D_80111B48_rockin_raceway; i < 8; i++, item++) {
        if (item->unk00 != 0) {
            dx = item->unk0C.x - pos->x;
            dy = item->unk0C.y - pos->y;
            dz = item->unk0C.z - pos->z;
            if (dx * dx + dy * dy + dz * dz < 3600.0002861023004) {
                func_8001C258_main(item->unk02, 4, 4);
                func_8001C258_main(item->unk04, 4, 4);
                item->unk00 = 0;
                if (D_80111BD4_rockin_raceway == -1 && D_80111BD6_rockin_raceway == -1 && item->unk08 == 30) {
                    D_80111BD6_rockin_raceway = 4;
                }
                break;
            }
        }
    }
    if (i < 8) {
        return item->unk0A;
    }
    return -1;
}

void func_80108BAC_rockin_raceway(void) {
    RrRacer* r;
    s32 i;

    for (i = 0; i < 4; i++) {
        r = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        switch (func_80108A80_rockin_raceway(&r->unk58)) {
            case 0:
                r->unk02 = 2;
                r->unk28 = 1.0f;
                r->unk20 = 300;
                r->unk34 |= 0xE;
                if (D_80111AD8_rockin_raceway == 2) {
                    omVibrate(r->unk0A, 10, 0, 10);
                }
                if (D_80111AD8_rockin_raceway == 2) {
                    if (r->unk04 != -1) {
                        HuAudFXStop(r->unk04);
                        r->unk04 = -1;
                    }
                    if (r->unk06 != -1) {
                        HuAudFXStop(r->unk06);
                        r->unk06 = -1;
                    }
                }
                r->unk04 = func_8004AC98_main(0x46D, r->unk0A);
                r->unk06 = func_8004AC98_main(0x46E, r->unk0A);
                break;
            case 1:
                r->unk02 = 1;
                r->unk28 = 0.0f;
                if (D_80111AD8_rockin_raceway == 2) {
                    if (r->unk04 != -1) {
                        HuAudFXStop(r->unk04);
                        r->unk04 = -1;
                    }
                    if (r->unk06 != -1) {
                        HuAudFXStop(r->unk06);
                        r->unk06 = -1;
                    }
                }
                func_8004AC98_main(0x458, r->unk0A);
                func_8004AC98_main(0x459, r->unk0A);
                func_8010E344_rockin_raceway(0x286, 3, 3, r->unk0A);
                if (D_80111AD8_rockin_raceway == 2) {
                    omVibrate(r->unk0A, 2, 2, 20);
                }
                break;
        }
    }
}

void func_80108D84_rockin_raceway(void) {
    omObjData* obj;
    HmfModel* mdl;
    s32 i;

    obj = omAddObj(0x1D, 13, 0, -1, func_80108ED4_rockin_raceway);
    D_80111B4C_rockin_raceway = obj;
    obj->model[0] = -1;
    for (i = 1; i < 13; i++) {
        obj->model[i] = func_8000B108_main(0x1001F, 0x899);
        func_8001C2FC_main(obj->model[i], 0x600, 0x400);
        Hu3DModelScaleSet(obj->model[i], 1.0f, 1.0f, 1.0f);
        mdl = &HmfModelData[obj->model[i]];
        mdl->unk40 = 0.0f;
        mdl->unk44 = 1.0f;
        func_8001C258_main(obj->model[i], 4, 4);
    }
    D_80111B50_rockin_raceway = HuMemAllocTag(sizeof(RrSmokeSave) * 12, 0x7918);
    memset(D_80111B50_rockin_raceway, 0, sizeof(RrSmokeSave) * 12);
    D_80111B54_rockin_raceway = 0;
}

void func_80108ED4_rockin_raceway(omObjData* obj) {
    HmfModel* mdl;
    s32 i;

    if (D_80111B54_rockin_raceway == 0) {
        for (i = 1; i < 13; i++) {
            if (obj->model[i] != -1) {
                mdl = &HmfModelData[obj->model[i]];
                if (!(mdl->unk18 & 4) && D_800CCF58_main[mdl->unk02].unk02 <= mdl->unk40) {
                    mdl->unk18 |= 4;
                    mdl->unk40 = 0.0f;
                }
            }
        }
    }
}

void func_80108F8C_rockin_raceway(f32 x, f32 y, f32 z) {
    omObjData* obj;
    HmfModel* mdl;
    s32 i;

    obj = D_80111B4C_rockin_raceway;
    for (i = 1; i < 13; i++) {
        if (obj->model[i] != -1) {
            mdl = &HmfModelData[obj->model[i]];
            if (mdl->unk18 & 4) {
                mdl->pos.x = x;
                mdl->pos.y = y;
                mdl->pos.z = z;
                mdl->rot.x = CRot.x;
                mdl->rot.y = CRot.y;
                mdl->rot.z = CRot.z;
                mdl->unk18 &= ~4;
                mdl->unk40 = 0.0f;
                mdl->unk44 = 1.5f;
                return;
            }
        }
    }
}

void func_80109044_rockin_raceway(void) {
    omObjData* obj;
    RrSmokeSave* save;
    HmfModel* mdl;
    s32 i;

    obj = D_80111B4C_rockin_raceway;
    save = D_80111B50_rockin_raceway;
    if (D_80111B54_rockin_raceway == 0) {
        for (i = 1; i < 13; i++, save++) {
            if (obj->model[i] != -1) {
                mdl = &HmfModelData[obj->model[i]];
                save->unk00 = mdl->unk18;
                save->unk04 = mdl->unk40;
                save->unk08 = mdl->unk44;
                save->unk0C.x = mdl->pos.x;
                save->unk0C.y = mdl->pos.y;
                save->unk0C.z = mdl->pos.z;
                save->unk18.x = mdl->rot.x;
                save->unk18.y = mdl->rot.y;
                save->unk18.z = mdl->rot.z;
                save->unk24.x = mdl->scale.x;
                save->unk24.y = mdl->scale.y;
                save->unk24.z = mdl->scale.z;
                mdl->unk18 |= 4;
                mdl->unk40 = mdl->unk44 = 0.0f;
            }
        }
        D_80111B54_rockin_raceway = 1;
    }
}

void func_80109134_rockin_raceway(void) {
    omObjData* obj;
    RrSmokeSave* save;
    HmfModel* mdl;
    s32 i;

    obj = D_80111B4C_rockin_raceway;
    save = D_80111B50_rockin_raceway;
    if (D_80111B54_rockin_raceway != 0) {
        for (i = 1; i < 13; i++, save++) {
            if (obj->model[i] != -1) {
                mdl = &HmfModelData[obj->model[i]];
                mdl->unk18 = save->unk00;
                mdl->unk40 = save->unk04;
                mdl->unk44 = save->unk08;
                mdl->pos.x = save->unk0C.x;
                mdl->pos.y = save->unk0C.y;
                mdl->pos.z = save->unk0C.z;
                mdl->rot.x = save->unk18.x;
                mdl->rot.y = save->unk18.y;
                mdl->rot.z = save->unk18.z;
                mdl->scale.x = save->unk24.x;
                mdl->scale.y = save->unk24.y;
                mdl->scale.z = save->unk24.z;
            }
        }
        D_80111B54_rockin_raceway = 0;
    }
}

void func_80109208_rockin_raceway(void) {
    HmfModel* mdl;
    HuSprite_Unk84_Struct* spr;
    RrEffect* fx;
    s32 i;

    D_80111B68_rockin_raceway->unk04 = func_8010A4C0_rockin_raceway(11);
    spr = func_80055194_main(D_80111B68_rockin_raceway->unk04);
    D_80111B58_rockin_raceway = omAddObj(0x1C, 0, 0, -1, func_80109384_rockin_raceway);
    D_80111B5C_rockin_raceway = fx = HuMemAllocTag(sizeof(RrEffect) * 16, 0x7918);
    for (i = 0; i < 16; i++, fx++) {
        if (i == 0) {
            fx->unk02 = func_8010EC8C_rockin_raceway(spr, D_801114D4_rockin_raceway);
        } else {
            fx->unk02 = func_8010F874_rockin_raceway(spr, D_80111B5C_rockin_raceway->unk02, D_801114D4_rockin_raceway);
        }
        fx->unk00 = 0;
        fx->unk04 = fx->unk08 = 0.0f;
        fx->unk0C.x = fx->unk0C.y = fx->unk0C.z = 0.0f;
        fx->unk18.x = fx->unk18.y = fx->unk18.z = 0.0f;
        fx->unk24.x = fx->unk24.y = fx->unk24.z = 0.0f;
        func_8001C258_main(fx->unk02, 4, 4);
        mdl = &HmfModelData[fx->unk02];
        mdl->unk40 = 0.0f;
    }
    D_80111B60_rockin_raceway = HuMemAllocTag(0x340, 0x7918);
    memset(D_80111B60_rockin_raceway, 0, 0x340);
    D_80111B64_rockin_raceway = 0;
}

void func_80109384_rockin_raceway(omObjData* obj) {
    HuSprite_Unk84_Struct* spr;
    RrEffect* fx;
    HmfModel* mdl;
    s32 i;

    if (D_80111B64_rockin_raceway == 0) {
        spr = func_80055194_main(D_80111B68_rockin_raceway->unk04);
        for (i = 0, fx = D_80111B5C_rockin_raceway; i < 16; i++, fx++) {
            if (fx->unk00 == 0) {
                continue;
            }
            mdl = &HmfModelData[fx->unk02];
            if (mdl->unk18 & 4) {
                continue;
            }
            fx->unk0C.x += fx->unk18.x;
            fx->unk0C.y += fx->unk18.y;
            fx->unk0C.z += fx->unk18.z;
            mdl->pos.x = fx->unk0C.x;
            mdl->pos.y = fx->unk0C.y;
            mdl->pos.z = fx->unk0C.z;
            mdl->scale.x = fx->unk24.x;
            mdl->scale.y = fx->unk24.y;
            mdl->scale.z = fx->unk24.z;
            func_8010FA78_rockin_raceway(fx->unk02, spr, (s32)fx->unk04, D_801114D4_rockin_raceway);
            fx->unk04 += fx->unk08;
            if ((s32)fx->unk04 >= spr->unk10) {
                fx->unk00 = 0;
                fx->unk04 = 0.0f;
                mdl->unk18 |= 4;
            }
        }
    }
}

s32 func_801094EC_rockin_raceway(Vec* pos, Vec* vel, Vec* scale, f32 speed) {
    HuSprite_Unk84_Struct* spr;
    RrEffect* fx;
    HmfModel* mdl;
    s32 i;

    spr = func_80055194_main(D_80111B68_rockin_raceway->unk04);
    for (i = 0, fx = D_80111B5C_rockin_raceway; i < 16; i++, fx++) {
        if (fx->unk00 != 0) {
            continue;
        }
        fx->unk00 = 1;
        mdl = &HmfModelData[fx->unk02];
        if (pos != NULL) {
            fx->unk0C.x = pos->x;
            fx->unk0C.y = pos->y;
            fx->unk0C.z = pos->z;
        } else {
            fx->unk0C.x = fx->unk0C.y = fx->unk0C.z = 0.0f;
        }
        if (vel != NULL) {
            fx->unk18.x = vel->x;
            fx->unk18.y = vel->y;
            fx->unk18.z = vel->z;
        } else {
            fx->unk18.x = fx->unk18.y = fx->unk18.z = 0.0f;
        }
        if (scale != NULL) {
            fx->unk24.x = scale->x;
            fx->unk24.y = scale->y;
            fx->unk24.z = scale->z;
        } else {
            fx->unk24.x = fx->unk24.y = fx->unk24.z = 1.0f;
        }
        fx->unk08 = speed;
        fx->unk04 = 0.0f;
        func_8010FA78_rockin_raceway(fx->unk02, spr, 0, D_801114D4_rockin_raceway);
        func_8001C258_main(fx->unk02, 4, 0);
        mdl->unk40 = 0.0f;
        mdl->pos.x = fx->unk0C.x;
        mdl->pos.y = fx->unk0C.y;
        mdl->pos.z = fx->unk0C.z;
        mdl->scale.x = fx->unk24.x;
        mdl->scale.y = fx->unk24.y;
        mdl->scale.z = fx->unk24.z;
        return i;
    }
    return -1;
}

// m1 rr2
#include "overlays/minigame.h"
#include "mallocblock.h"

/* a kart (rr1's functions own most of it) */
typedef struct RrKart {
    /* 0x00 */ char unk00[2];
    /* 0x02 */ u16 unk02;
    /* 0x04 */ char unk04[0x24];
    /* 0x28 */ f32 unk28; /* lap time, seconds */
    /* 0x2C */ char unk2C[2];
    /* 0x2E */ s16 unk2E; /* player */
    /* 0x30 */ char unk30[0x10];
    /* 0x40 */ f32 unk40; /* wheel angle */
    /* 0x44 */ char unk44[0x14];
    /* 0x58 */ Vec unk58; /* position */
    /* 0x64 */ char unk64[4];
    /* 0x68 */ f32 unk68; /* heading */
    /* 0x6C */ char unk6C[4];
} RrKart; /* size 0x70 */

/* 16 entries of D_80111B5C: a model and its animation state */
typedef struct RrMdlAnim {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02; /* model, -1 unused */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ char unk0C[0x24];
} RrMdlAnim; /* size 0x30 */

/* 16 entries of D_80111B60: the RrMdlAnim and model state saved by func_801097A0 */
typedef struct RrMdlSave {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02; /* model unk40 */
    /* 0x04 */ s32 unk04; /* model unk18 */
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
    /* 0x28 */ Vec scale;
} RrMdlSave; /* size 0x34 */

extern RrMdlAnim *D_80111B5C_rockin_raceway;
extern RrMdlSave *D_80111B60_rockin_raceway;
extern s16 D_80111B64_rockin_raceway;

void func_801094EC_rockin_raceway(Vec *pos, Vec *vel, Vec *scale, f32 arg3);
void func_80109A04_rockin_raceway(omObjData *obj);
void func_80109CF8_rockin_raceway(void);
/* the sprite files (D_80111B68) */
typedef struct RrSprFiles {
    /* 0x00 */ s16 unk00; /* 0x4D000E */
    /* 0x02 */ s16 unk02; /* 0x4D000F */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06; /* 0x4D0010 */
    /* 0x08 */ s16 unk08; /* 0x4D0011 */
    /* 0x0A */ s16 unk0A; /* 0x4D0012 */
    /* 0x0C */ s16 unk0C[2]; /* 0x31, 0x32: best time digits */
    /* 0x10 */ s16 unk10; /* 0x4D0013 */
} RrSprFiles;

extern RrSprFiles *D_80111B68_rockin_raceway;
extern s32 D_80111AE8_rockin_raceway;
extern Vtx D_801114D8_rockin_raceway[];
extern Vtx D_80111518_rockin_raceway[];
extern s32 D_8011159C_rockin_raceway[];
extern s32 D_801115AC_rockin_raceway[2]; /* inside D_8011159C's label: best times? */
extern s32 D_801115B4_rockin_raceway;

u16 func_8010A4C0_rockin_raceway(s32 file);
void func_8010B5DC_rockin_raceway(s32 *times);
s16 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct *spr, u16 model, s32 *arg2);
s16 func_8010FFB8_rockin_raceway(HuSprite_Unk84_Struct *spr, Vtx *vtx);
void func_80110C38_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *spr, s32 *arg2);
void func_80110D90_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *spr, s32 *times);
/* the four racing lines (D_80111B40), built by func_80109DA8 from D_801112A0 */
typedef struct RrPath {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ u16 unk02; /* point count */
    /* 0x04 */ f32 unk04; /* lap length without the closing segment */
    /* 0x08 */ f32 unk08; /* length up to point D_801112C0[i] */
    /* 0x0C */ Vec *unk0C; /* points */
    /* 0x10 */ Vec *unk10; /* segment midpoints */
    /* 0x14 */ f32 *unk14; /* segment lengths */
    /* 0x18 */ f32 *unk18; /* length at each point (count + 1) */
    /* 0x1C */ Vec *unk1C; /* segment rotation */
    /* 0x20 */ s16 *unk20; /* per point: 1 or 2 placed at random */
} RrPath; /* size 0x24 */

extern RrPath *D_80111B40_rockin_raceway;
extern f32 D_80111B44_rockin_raceway;
extern Vec *D_801112A0_rockin_raceway[4];
extern s32 D_801112B0_rockin_raceway[4]; /* label D_801112B2 + 2: the u16 load reads its low half */
extern s32 D_801112C0_rockin_raceway[4];

void func_8010E8A0_rockin_raceway(f32 t, Vec *a, Vec *b, Vec *c, Vec *out);
void func_8010E994_rockin_raceway(f32 t, Vec *a, Vec *b, Vec *c, Vec *out);
void func_8010EB84_rockin_raceway(Vec *dir, Vec *rot);
f32 func_8010E7E0_rockin_raceway(f32 t, f32 a, f32 b);
extern s16 D_80111B74_rockin_raceway;
/* per player HUD (D_80111B80): position and the five digit offsets */
typedef struct RrHud {
    /* 0x00 */ s16 unk00; /* player */
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06; /* x */
    /* 0x08 */ s16 unk08; /* y */
    /* 0x0A */ s16 unk0A[5]; /* digit x relative to unk06 */
} RrHud; /* size 0x14 */

extern s16 D_80111B6C_rockin_raceway[4]; /* sprite groups */
extern RrHud D_80111B80_rockin_raceway[4];
extern s16 D_80111330_rockin_raceway[4][2];
extern s32 D_801115B8_rockin_raceway[];
void func_8010A990_rockin_raceway(omObjData *obj);
extern RrKart *D_80111B30_rockin_raceway;
extern s32 D_80111AD0_rockin_raceway;
extern s32 D_80111AD8_rockin_raceway; /* game state */
extern s32 D_80111ADC_rockin_raceway;
void func_8010AAAC_rockin_raceway(s16 player, s16 value, u16 arg2);
extern u8 D_800D6A90_main;
f32 func_8010E840_rockin_raceway(f32 t, f32 a, f32 b, f32 c);
extern s16 D_80111B76_rockin_raceway[2]; /* best time sprite groups */
extern s16 D_80111B7A_rockin_raceway; /* new record pulse timer */
extern s16 D_80111340_rockin_raceway[8];
extern s32 D_80111B00_rockin_raceway[2 * 6]; /* best time digits, six per time */
extern s32 D_801115D8_rockin_raceway[6]; /* digit sprite members */
/* camera state (MP2 Looney Lumberjacks LLCamera) */
typedef struct RrCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} RrCamera; /* size 0x24 */

extern s32 fontcolor;
extern s32 D_800EBE24_minigame;
extern s32 D_801115F0_rockin_raceway; /* camera debug mode */
extern s32 D_801115F4_rockin_raceway; /* debug text x */
extern s32 D_801115F8_rockin_raceway; /* debug text y */
void func_8010C7CC_rockin_raceway(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
/* camera preset (D_80111350): center, rotation, zoom */
typedef struct RrCamPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} RrCamPreset;

extern RrCamPreset D_80111350_rockin_raceway;
extern omObjData *D_80111BD8_rockin_raceway;
extern s16 D_80111C28_rockin_raceway;
extern s16 D_80111C2A_rockin_raceway;
extern s16 D_80111C2C_rockin_raceway;
extern s16 D_80111C2E_rockin_raceway;
void func_8010C0D8_rockin_raceway(omObjData *obj);
void func_8010C5E0_rockin_raceway(s32 idx);
#define RR_WRAP(v)          \
    if ((v) >= 360.0) {     \
        (v) -= 360.0;       \
    } else if ((v) < 0.0) { \
        (v) += 360.0;       \
    }

extern RrCamera D_80111BE0_rockin_raceway[2]; /* [0] target, [1] start */
f32 func_8010E7C8_rockin_raceway(f32 t, f32 a, f32 b);
void func_8010D134_rockin_raceway(s32 idx);
/* a camera focus point (D_80111C4C, 16 of them) */
typedef struct RrFocus {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 weight;
} RrFocus; /* size 0x10 */

extern omObjData *D_80111C30_rockin_raceway;
extern s16 D_80111C34_rockin_raceway; /* focus point count */
extern f32 D_80111C38_rockin_raceway[5]; /* focus centre x, y, z; [3] (D_80111C44) summed weight; [4] (D_80111C48) target zoom */
extern RrFocus *D_80111C4C_rockin_raceway;
void func_8010CE90_rockin_raceway(omObjData *obj);
void func_8010CADC_rockin_raceway(Vec *pos, f32 weight);
double fabs(double); /* the GCC builtin (abs.d) */
void func_8010D288_rockin_raceway(s32 cam, Vec *pos, Vec *out, f32 *screen);
f32 func_8010E608_rockin_raceway(f32 target, f32 cur, f32 step);
// m1 rr2 end

/* rr2 func_801096A0_rockin_raceway */
void func_801096A0_rockin_raceway(RrKart *kart) {
    Vec pos;
    Vec vel;
    Vec scale;

    pos.x = kart->unk58.x;
    pos.z = kart->unk58.z;
    pos.y = kart->unk58.y + 200.0 * 0.1f;
    vel.x = -(sindf(kart->unk68 + kart->unk40) * 100.0 * 0.1f);
    vel.z = -(cosdf(kart->unk68 + kart->unk40) * 100.0 * 0.1f);
    vel.y = 1.0f;
    scale.x = scale.y = scale.z = 0.25f;
    func_801094EC_rockin_raceway(&pos, &vel, &scale, 1.0f);
}
/* rr2 end func_801096A0_rockin_raceway */

/* rr2 func_801097A0_rockin_raceway */
void func_801097A0_rockin_raceway(void) {
    RrMdlSave *save;
    RrMdlAnim *anim;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway == 0) {
        save = D_80111B60_rockin_raceway;
        anim = D_80111B5C_rockin_raceway;
        for (i = 0; i < 16; i++, anim++, save++) {
            if (anim->unk02 != -1) {
                model = &HmfModelData[anim->unk02];
                save->unk00 = anim->unk00;
                save->unk02 = model->unk40;
                save->unk04 = model->unk18;
                save->unk08 = anim->unk04;
                save->unk0C = anim->unk08;
                save->pos.x = model->pos.x;
                save->pos.y = model->pos.y;
                save->pos.z = model->pos.z;
                save->rot.x = model->rot.x;
                save->rot.y = model->rot.y;
                save->rot.z = model->rot.z;
                save->scale.x = model->scale.x;
                save->scale.y = model->scale.y;
                save->scale.z = model->scale.z;
                anim->unk00 = 0;
                model->unk18 |= 4;
                model->unk40 = 0.0f;
            }
        }
        D_80111B64_rockin_raceway = 1;
    }
}
/* rr2 end func_801097A0_rockin_raceway */

/* rr2 func_801098D8_rockin_raceway */
void func_801098D8_rockin_raceway(void) {
    RrMdlSave *save;
    RrMdlAnim *anim;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway != 0) {
        save = D_80111B60_rockin_raceway;
        anim = D_80111B5C_rockin_raceway;
        for (i = 0; i < 16; i++, anim++, save++) {
            if (anim->unk02 != -1) {
                model = &HmfModelData[anim->unk02];
                anim->unk00 = save->unk00;
                model->unk18 = save->unk04;
                anim->unk04 = save->unk08;
                anim->unk08 = save->unk0C;
                model->pos.x = save->pos.x;
                model->pos.y = save->pos.y;
                model->pos.z = save->pos.z;
                model->rot.x = save->rot.x;
                model->rot.y = save->rot.y;
                model->rot.z = save->rot.z;
                model->scale.x = save->scale.x;
                model->scale.y = save->scale.y;
                model->scale.z = save->scale.z;
            }
        }
        D_80111B64_rockin_raceway = 0;
    }
}
/* rr2 end func_801098D8_rockin_raceway */

/* rr2 func_801099AC_rockin_raceway */
void func_801099AC_rockin_raceway(void) {
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 24, 0, -1, func_80109A04_rockin_raceway);
}
/* rr2 end func_801099AC_rockin_raceway */

/* rr2 func_80109A04_rockin_raceway */
void func_80109A04_rockin_raceway(omObjData *obj) {
    s32 i;
    s16 grp;

    obj->func = (omObjFunc)func_80109CF8_rockin_raceway;
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->model[0] = func_8000B0A0_main(0x4D0000, 0x99);
    obj->model[1] = func_8000B0A0_main(0x4D000A, 0xB9);
    obj->model[2] = func_8000B0A0_main(0x4D000B, 0xB9);
    D_80111B68_rockin_raceway->unk06 = func_8010A4C0_rockin_raceway(0x4D0010);
    D_80111B68_rockin_raceway->unk08 = func_8010A4C0_rockin_raceway(0x4D0011);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            obj->model[3] = func_8010FFB8_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk06), D_801114D8_rockin_raceway);
        } else {
            obj->model[3 + i] = func_8010F874_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk06), obj->model[3], &D_801115B4_rockin_raceway);
        }
    }
    for (i = 0; i < 12; i++) {
        if (i == 0) {
            obj->model[7] = func_8010FFB8_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk08), D_80111518_rockin_raceway);
        } else {
            obj->model[7 + i] = func_8010F874_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk08), obj->model[7], &D_801115B4_rockin_raceway);
        }
    }
    func_80110C38_rockin_raceway(&obj->model[3], func_80055194_main(D_80111B68_rockin_raceway->unk06), D_8011159C_rockin_raceway);
    D_801115AC_rockin_raceway[1] = D_80111AE8_rockin_raceway;
    func_8010B5DC_rockin_raceway(D_801115AC_rockin_raceway);
    func_80110D90_rockin_raceway(&obj->model[7], func_80055194_main(D_80111B68_rockin_raceway->unk08), D_801115AC_rockin_raceway);
    D_80111B68_rockin_raceway->unk00 = func_8010A4C0_rockin_raceway(0x4D000E);
    grp = HuSprGrpCreate(1, 0);
    func_80055024_main(grp, 0, D_80111B68_rockin_raceway->unk00, 0);
    HuSprAttrSet(grp, 0, 0x4000);
    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    func_80054904_main(grp, 0, 160, 120);
    HuSprPriSet(grp, 0, 0xFFFF);
    func_800550F4_main(grp, 0, 0);
    WipeCreateIn(0xFF, 16);
}
/* rr2 end func_80109A04_rockin_raceway */

void func_80109CF8_rockin_raceway(void) {
}

/* rr2 func_80109D00_rockin_raceway */
void func_80109D00_rockin_raceway(s32 *arg0) {
    omObjData *obj = D_800EC1C0_minigame[0];

    func_80110C38_rockin_raceway(&obj->model[3], func_80055194_main(D_80111B68_rockin_raceway->unk06), arg0);
}
/* rr2 end func_80109D00_rockin_raceway */

/* rr2 func_80109D54_rockin_raceway */
void func_80109D54_rockin_raceway(s32 *times) {
    omObjData *obj = D_800EC1C0_minigame[0];

    func_80110D90_rockin_raceway(&obj->model[7], func_80055194_main(D_80111B68_rockin_raceway->unk08), times);
}
/* rr2 end func_80109D54_rockin_raceway */

/* rr2 func_80109DA8_rockin_raceway */
void func_80109DA8_rockin_raceway(void) {
    Vec rot;
    RrPath *path;
    s32 i;
    s32 j;
    s32 next;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;

    D_80111B40_rockin_raceway = HuMemAllocTag(sizeof(RrPath) * 4, 0x7918);
    for (i = 0, path = D_80111B40_rockin_raceway; i < 4; i++, path++) {
        path->unk00 = i;
        path->unk04 = path->unk08 = 0.0f;
        path->unk0C = D_801112A0_rockin_raceway[i];
        path->unk02 = D_801112B0_rockin_raceway[i];
        path->unk0C[D_801112C0_rockin_raceway[i]].x = 340.0f;
        path->unk10 = HuMemAllocTag(path->unk02 * sizeof(Vec), 0x7918);
        path->unk14 = HuMemAllocTag(path->unk02 * sizeof(f32), 0x7918);
        path->unk18 = HuMemAllocTag((path->unk02 + 1) * sizeof(f32), 0x7918);
        path->unk1C = HuMemAllocTag(path->unk02 * sizeof(Vec), 0x7918);
        path->unk20 = HuMemAllocTag(path->unk02 * sizeof(s16), 0x7918);
        memset(path->unk20, 0, 4);
        for (j = 0; j < 5; j++) {
            next = (rand8() & 0xFF) % D_801112C0_rockin_raceway[i];
            path->unk20[next] = 1;
        }
        for (j = 0; j < 3; j++) {
            next = (rand8() & 0xFF) % D_801112C0_rockin_raceway[i];
            path->unk20[next] = 2;
        }
        len = 0.0f;
        for (j = 0; j < path->unk02; j++) {
            next = (j + 1) % path->unk02;
            dx = path->unk0C[next].x - path->unk0C[j].x;
            dy = path->unk0C[next].y - path->unk0C[j].y;
            dz = path->unk0C[next].z - path->unk0C[j].z;
            path->unk14[j] = sqrtf(dx * dx + dy * dy + dz * dz);
            path->unk18[j] = len;
            len += path->unk14[j];
            if (j < D_801112C0_rockin_raceway[i]) {
                path->unk08 = len;
            }
            path->unk10[j].x = path->unk0C[j].x + dx * 0.5f;
            path->unk10[j].y = path->unk0C[j].y + dy * 0.5f;
            path->unk10[j].z = path->unk0C[j].z + dz * 0.5f;
            func_8010E994_rockin_raceway(0.0f, &path->unk0C[j], &path->unk10[j], &path->unk0C[next], &rot);
            func_8010EB84_rockin_raceway(&rot, &path->unk1C[j]);
        }
        path->unk18[j] = len;
        path->unk04 = len - path->unk14[j - 1];
    }
    D_80111B44_rockin_raceway = D_80111B40_rockin_raceway[0].unk08;
    for (i = 1, path = &D_80111B40_rockin_raceway[1]; i < 4; i++, path++) {
        if (D_80111B44_rockin_raceway > path->unk08) {
            D_80111B44_rockin_raceway = path->unk08;
        }
    }
}
/* rr2 end func_80109DA8_rockin_raceway */

#ifdef NON_MATCHING
/* rr2 func_8010A258_rockin_raceway */
f32 func_8010A258_rockin_raceway(u16 idx, f32 dist, f32 base, f32 delta, s16 *seg, f32 *frac, Vec *pos, Vec *rot) {
    RrPath *path = &D_80111B40_rockin_raceway[idx];
    f32 start;
    f32 d;
    f32 rem;
    f32 t;
    s32 i;

    s32 next;
    s32 cur;

    start = base + delta;
    if (path->unk04 <= start) {
        start = path->unk04;
    } else if (start <= 0.0f) {
        start = 0.0f;
    }
    d = start + dist;
    if (path->unk04 <= d) {
        d = path->unk04;
    } else if (d <= 0.0f) {
        d = 0.0f;
    }
    rem = d;
    for (i = 0; i < path->unk02; i++) {
        if (d <= path->unk18[i + 1]) {
            break;
        }
        rem = d - path->unk18[i + 1];
    }
    if (path->unk02 - 1 < i) {
        i = path->unk02 - 1;
    }
    if (seg != NULL) {
        *seg = i;
    }
    if (rem != 0.0f && path->unk14[i] != 0.0f) {
        t = rem / path->unk14[i];
    } else {
        t = 0.0f;
    }
    if (frac != NULL) {
        *frac = t;
    }
    cur = i;
    next = 0;
    if (i < path->unk02 - 1) {
        next = i + 1;
    }

    func_8010E8A0_rockin_raceway(t, &path->unk0C[cur], &path->unk10[cur], &path->unk0C[next], pos);
    rot->x = func_8010E7E0_rockin_raceway(t, path->unk1C[cur].x, path->unk1C[next].x);
    rot->y = func_8010E7E0_rockin_raceway(t, path->unk1C[cur].y, path->unk1C[next].y);
    return start;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A258_rockin_raceway);
#endif
/* rr2 end func_8010A258_rockin_raceway */

/* rr2 func_8010A48C_rockin_raceway */
u16 func_8010A48C_rockin_raceway(u16 idx, u16 pt) {
    RrPath *path = &D_80111B40_rockin_raceway[idx];

    return path->unk20[pt];
}
/* rr2 end func_8010A48C_rockin_raceway */

/* rr2 func_8010A4C0_rockin_raceway */
u16 func_8010A4C0_rockin_raceway(s32 file) {
    void *data;
    s16 spr;

    data = DataRead(file);
    spr = func_80055810_main(data);
    DataClose(data);
    return spr;
}
/* rr2 end func_8010A4C0_rockin_raceway */

/* rr2 func_8010A504_rockin_raceway */
void func_8010A504_rockin_raceway(void) {
    s32 grp;

    D_80111B68_rockin_raceway->unk02 = func_8010A4C0_rockin_raceway(0x4D000F);
    D_80111B68_rockin_raceway->unk0A = func_8010A4C0_rockin_raceway(0x4D0012);
    D_80111B68_rockin_raceway->unk10 = func_8010A4C0_rockin_raceway(0x4D0013);
    grp = HuSprGrpCreate(1, 0);
    D_80111B74_rockin_raceway = grp;
    func_80054904_main(grp, 0, 160, 60);
    func_80055024_main(grp, 0, D_80111B68_rockin_raceway->unk0A, 0);
    func_800550F4_main(grp, 0, 0);
    func_80054FF8_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x9000);
}
/* rr2 end func_8010A504_rockin_raceway */

/* rr2 func_8010A5E4_rockin_raceway */
void func_8010A5E4_rockin_raceway(s16 player, s16 kind) {
    s32 spr;
    s32 x;
    s32 y;
    s32 grp;
    s32 i;
    s32 off;


    spr = func_8010A4C0_rockin_raceway(D_801115B8_rockin_raceway[kind]);
    x = D_80111330_rockin_raceway[player][0];
    y = D_80111330_rockin_raceway[player][1];
    D_80111B6C_rockin_raceway[player] = grp = HuSprGrpCreate(7, 0);
    D_80111B80_rockin_raceway[player].unk00 = player;
    D_80111B80_rockin_raceway[player].unk08 = y;
    D_80111B80_rockin_raceway[player].unk04 = 0;
    D_80111B80_rockin_raceway[player].unk02 = 0;
    if (player & 1) {
        D_80111B80_rockin_raceway[player].unk06 = x - 4;
    } else {
        D_80111B80_rockin_raceway[player].unk06 = x + 46;
    }
    for (i = 0; i < 5; i++) {
        if (player & 1) {
            D_80111B80_rockin_raceway[player].unk0A[i] = x + (s16)(i * 8 - 20) - D_80111B80_rockin_raceway[player].unk06;
        } else {
            D_80111B80_rockin_raceway[player].unk0A[i] = x + (s16)(i * 8 + 30) - D_80111B80_rockin_raceway[player].unk06;
        }
    }
    for (i = 0; i < 7; i++) {
        if (i == 0) {
            if (player & 1) {
                func_80054904_main(grp, i, x - 42, y);
            } else {
                func_80054904_main(grp, i, x + 8, y);
            }
            func_80055024_main(grp, i, spr, 0);
        } else if (i == 6) {
            if (player & 1) {
                func_80054904_main(grp, i, x - 55, y);
            } else {
                func_80054904_main(grp, i, x - 5, y);
            }
            func_80055024_main(grp, i, D_80111B68_rockin_raceway->unk10, 0);
            func_80055484_main(grp, i, 0, 0, 0, 0xA0);
        } else {
            if (player & 1) {
                func_80054904_main(grp, i, x - 20, y);
            } else {
                func_80054904_main(grp, i, x + 30, y);
            }
            func_80055024_main(grp, i, D_80111B68_rockin_raceway->unk02, 0);
            x += 8;
        }
        func_800550F4_main(grp, i, 0);
        func_80054FF8_main(grp, i, 0);
        HuSprAttrSet(grp, i, 0x1000);
        if (i != 6) {
            HuSprPriSet(grp, i, -16 - i);
        } else {
            HuSprPriSet(grp, i, 0xFFFF);
        }
    }
    omSetStatBit(omAddObj(20, 0, 0, -1, func_8010A990_rockin_raceway), 0xA0);
}
/* rr2 end func_8010A5E4_rockin_raceway */

/* rr2 func_8010A990_rockin_raceway */
void func_8010A990_rockin_raceway(omObjData *obj) {
    RrKart *kart;
    s32 i;

    if (D_80111AD8_rockin_raceway == 5 && (D_80111ADC_rockin_raceway > 0 || D_80111AD0_rockin_raceway >= 2)) {
        HuSprAttrReset(D_80111B74_rockin_raceway, 0, 0x8000);
    } else {
        HuSprAttrSet(D_80111B74_rockin_raceway, 0, 0x8000);
    }
    if (D_80111AD8_rockin_raceway < 3) {
        for (i = 0, kart = D_80111B30_rockin_raceway; i < 4; i++, kart++) {
            func_8010AAAC_rockin_raceway(kart->unk2E, kart->unk28 * 100.0f, kart->unk02);
        }
    } else {
        for (i = 0; i < 4; i++) {
            func_8010AAAC_rockin_raceway(i, 0, 0xFFFF);
        }
    }
}
/* rr2 end func_8010A990_rockin_raceway */

/* rr2 func_8010AAAC_rockin_raceway */
void func_8010AAAC_rockin_raceway(s16 player, s16 value, u16 mode) {
    u16 grp;
    f32 scale;
    f32 x;
    s32 i;
    s32 j;

    grp = D_80111B6C_rockin_raceway[player];
    if (mode == 2) {
        if (D_80111B80_rockin_raceway[player].unk02++ > 30.0f) {
            D_80111B80_rockin_raceway[player].unk02 = 30;
        }
        scale = D_80111B80_rockin_raceway[player].unk02 / 30.0f;
        scale = func_8010E840_rockin_raceway(scale, 0.0f, 1.0f, 0.4f) + 1.0;
    } else {
        if (D_80111B80_rockin_raceway[player].unk02-- < 0) {
            D_80111B80_rockin_raceway[player].unk02 = 0;
        }
        scale = D_80111B80_rockin_raceway[player].unk02 / 30.0f;
        scale = scale * 0.4f + 1.0;
    }
    if (D_80111B80_rockin_raceway[player].unk02 != D_80111B80_rockin_raceway[player].unk04) {
        for (i = 0; i < 5; i++) {
            x = D_80111B80_rockin_raceway[player].unk06 + D_80111B80_rockin_raceway[player].unk0A[i] * scale;
            HuSprScaleSet(grp, i + 1, scale, scale);
            func_80054904_main(grp, i + 1, x, D_80111B80_rockin_raceway[player].unk08);
            if (mode == 2) {
                HuSprAttrSet(grp, i + 1, 0x838);
            } else {
                HuSprAttrReset(grp, i + 1, 0x838);
            }
        }
        D_80111B80_rockin_raceway[player].unk04 = D_80111B80_rockin_raceway[player].unk02;
    }
    switch (mode) {
    case 1:
        if ((D_80111AD0_rockin_raceway & 1) && func_80049F98_main() + D_800D6A90_main == 0) {
            HuSprAttrSet(grp, 0, 0x8000);
        } else {
            HuSprAttrReset(grp, 0, 0x8000);
        }
        break;
    case 2:
        HuSprAttrReset(grp, 0, 0x8000);
        if (!(D_80111AD0_rockin_raceway & 3)) {
            for (i = 0; i < 5; i++) {
                HuSprAttrReset(grp, i + 1, 0x8000);
                func_80054FF8_main(grp, i + 1, 1);
                func_80055458_main(grp, i + 1, 0x100);
            }
        } else {
            for (i = 0; i < 5; i++) {
                HuSprAttrReset(grp, i + 1, 0x8000);
                func_80054FF8_main(grp, i + 1, 0);
                func_80055458_main(grp, i + 1, 0x100);
            }
        }
        return;
    case 0xFFFF:
        for (i = 0; i < 7; i++) {
            HuSprAttrSet(grp, i, 0x8000);
        }
        return;
    default:
        HuSprAttrReset(grp, 0, 0x8000);
        break;
    }
    for (i = 0; i < 5; i++) {
        if (i * 20 < value) {
            j = i + 1;
            HuSprAttrReset(grp, j, 0x8000);
            if (value >= j * 20) {
                func_80055458_main(grp, j, 0x100);
                func_80054FF8_main(grp, j, 0);
            } else {
                func_80055458_main(grp, i + 1, (s16)(value % 20) * 0.05f * 256.0f);
                func_80054FF8_main(grp, i + 1, 0);
            }
        } else {
            HuSprAttrSet(grp, i + 1, 0x8000);
        }
    }
}
/* rr2 end func_8010AAAC_rockin_raceway */

/* rr2 func_8010B124_rockin_raceway */
void func_8010B124_rockin_raceway(void) {
    s32 grp;
    s32 i;
    s32 j;

    D_80111B68_rockin_raceway->unk0C[0] = func_8010A4C0_rockin_raceway(0x31);
    D_80111B68_rockin_raceway->unk0C[1] = func_8010A4C0_rockin_raceway(0x32);
    D_80111B7A_rockin_raceway = 0;
    for (i = 0; i < 2; i++) {
        D_80111B76_rockin_raceway[i] = grp = HuSprGrpCreate(8, 0);
        for (j = 0; j < 8; j++) {
            func_80054904_main(grp, j, D_80111340_rockin_raceway[j], i * 12 + 28);
            func_80055024_main(grp, j, D_80111B68_rockin_raceway->unk0C[i], 0);
            func_80054FF8_main(grp, j, 0);
            HuSprAttrSet(grp, j, 0x1000);
            func_800550F4_main(grp, j, 0);
        }
        func_80054FF8_main(grp, 2, 10);
        func_80054FF8_main(grp, 5, 11);
    }
}
/* rr2 end func_8010B124_rockin_raceway */

/* rr2 func_8010B2B8_rockin_raceway */
void func_8010B2B8_rockin_raceway(void) {
    f32 scale;
    u16 grp;
    s32 *digits;
    s32 i;
    s32 j;

    scale = 1.0f;
    if (D_80111AD8_rockin_raceway == 5) {
        for (i = 0; i < 2; i++) {
            grp = D_80111B76_rockin_raceway[i];
            for (j = 0; j < 8; j++) {
                HuSprAttrSet(grp, j, 0x8000);
            }
        }
        return;
    }
    digits = D_80111B00_rockin_raceway;
    for (i = 0; i < 2; i++) {
        grp = D_80111B76_rockin_raceway[i];
        for (j = 0; j < 8; j++) {
            HuSprAttrReset(grp, j, 0x8000);
        }
    }
    if (D_80111B7A_rockin_raceway != 0) {
        scale = sindf(D_80111B7A_rockin_raceway / 15.0f * 180.0f) + 1.0f;
        if (--D_80111B7A_rockin_raceway == 1) {
            scale = 1.0f;
        }
    }
    for (i = 0; i < 2; i++) {
        grp = D_80111B76_rockin_raceway[i];
        for (j = 0; j < 6; j++) {
            if (digits[i * 6 + j] >= 10) {
                digits[i * 6 + j] = 9;
            } else if (digits[i * 6 + j] < 0) {
                digits[i * 6 + j] = 0;
            }
            func_80054FF8_main(grp, D_801115D8_rockin_raceway[j], (s16)digits[i * 6 + j]);
        }
        if ((D_80111B7A_rockin_raceway != 0) & (i == 1)) {
            for (j = 0; j < 8; j++) {
                func_80054904_main(grp, j, (D_80111340_rockin_raceway[j] - 156) * scale + 156.0f, i * 12 + 28);
                HuSprScaleSet(grp, j, scale, scale);
            }
        }
    }
}
/* rr2 end func_8010B2B8_rockin_raceway */

/* rr2 func_8010B5DC_rockin_raceway */
#ifdef NON_MATCHING
void func_8010B5DC_rockin_raceway(s32 *times) {
    s32 parts[3];
    s32 *digit;
    s32 *digits;
    s32 i;

    digits = D_80111B00_rockin_raceway;
    for (i = 0; i < 2; i++) {
        parts[0] = times[i] / 1800;
        times[i] -= parts[0] * 1800;
        parts[1] = times[i] / 30;
        times[i] -= parts[1] * 30;
        parts[2] = times[i] / 30.0f * 99.0f;
        digit = &digits[i * 6];
        digit[0] = parts[0] / 10;
        digit[1] = parts[0] - digit[0] * 10;
        digit[2] = parts[1] / 10;
        digit[3] = parts[1] - digit[2] * 10;
        digit[4] = parts[2] / 10;
        digit[5] = parts[2] - digit[4] * 10;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B5DC_rockin_raceway);
#endif
/* rr2 end func_8010B5DC_rockin_raceway */

/* rr2 func_8010B774_rockin_raceway */
void func_8010B774_rockin_raceway(void) {
    HuCamera *cam;
    s32 i;

    Center.x = D_80111350_rockin_raceway.center.x;
    Center.y = D_80111350_rockin_raceway.center.y;
    Center.z = D_80111350_rockin_raceway.center.z;
    CRot.x = D_80111350_rockin_raceway.rot.x;
    CRot.y = D_80111350_rockin_raceway.rot.y;
    CRot.z = D_80111350_rockin_raceway.rot.z;
    CZoom = D_80111350_rockin_raceway.zoom;
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2E_rockin_raceway = 0;
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010C0D8_rockin_raceway);
    cam = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        cam->viewports[i].vp.vscale[0] = cam->viewports[0].vp.vscale[0];
        cam->viewports[i].vp.vscale[1] = cam->viewports[0].vp.vscale[1];
        cam->viewports[i].vp.vscale[2] = cam->viewports[0].vp.vscale[2];
        cam->viewports[i].vp.vtrans[0] = cam->viewports[0].vp.vtrans[0];
        cam->viewports[i].vp.vtrans[1] = cam->viewports[0].vp.vtrans[1];
        cam->viewports[i].vp.vtrans[2] = cam->viewports[0].vp.vtrans[2];
    }
}
/* rr2 end func_8010B774_rockin_raceway */

/* rr2 func_8010B89C_rockin_raceway */
void func_8010B89C_rockin_raceway(void) {
    RrCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_801115F0_rockin_raceway) {
    case 1:
        if ((u16)D_800CDA7C_main[0] & 0x8000) {
            speed = 8.0f;
        }
        if (D_800CDA7C_main[0] & 0x4000) {
            speed = 0.5f;
        }
        if (D_800D5558_main[0] & 0x1000) {
            Center.x = 0.0f;
            Center.y = 191.2f;
            Center.z = 0.2f;
            CRot.x = -14.5f;
            CRot.y = 0.0f;
            CRot.z = 0.0f;
            CZoom = 1069.0f;
        } else {
            c.rot.x = (f32)D_800D20A1_main[0] * 0.125 * speed;
            c.rot.y = (f32)D_800CBB6E_main[0] * 0.125 * speed;
            if (D_800CDA7C_main[0] & 0x200) {
                c.center.x = 2.0 * speed;
            }
            if (D_800CDA7C_main[0] & 0x100) {
                c.center.x = -(2.0 * speed);
            }
            if (D_800CDA7C_main[0] & 0x800) {
                c.center.z = -(2.0 * speed);
            }
            if (D_800CDA7C_main[0] & 0x400) {
                c.center.z = 2.0 * speed;
            }
            if (D_800CDA7C_main[0] & 8) {
                c.center.y = 2.0 * speed;
            }
            if (D_800CDA7C_main[0] & 4) {
                c.center.y = -(2.0 * speed);
            }
            if (D_800CDA7C_main[0] & 1) {
                c.zoom = 2.0 * speed;
            }
            if (D_800CDA7C_main[0] & 2) {
                c.zoom = -(2.0 * speed);
            }
            c.center.x += Center.x;
            c.center.y += Center.y;
            c.center.z += Center.z;
            c.rot.x += CRot.x;
            c.rot.y += CRot.y;
            c.rot.z += CRot.z;
            c.zoom += CZoom;
            func_8010C7CC_rockin_raceway(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
        }
        sprintf(D_800D5218_main, "CAMERA TEST_MODE");
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 80, D_800D5218_main);
        sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 88, D_800D5218_main);
        sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 96, D_800D5218_main);
        sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 104, D_800D5218_main);
        D_800EBE24_minigame = 0;
        break;
    case 2:
        if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
            D_801115F4_rockin_raceway++;
        }
        if (D_800CDA7C_main[0] & 0x202) {
            D_801115F4_rockin_raceway--;
        }
        if (D_800CDA7C_main[0] & 0x404) {
            D_801115F8_rockin_raceway++;
        }
        if (D_800CDA7C_main[0] & 0x808) {
            D_801115F8_rockin_raceway--;
        }
        fontcolor = 8;
        sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 80, D_800D5218_main);
        sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 88, D_800D5218_main);
        sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 96, D_800D5218_main);
        sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 104, D_800D5218_main);
        break;
    default:
        D_800EBE24_minigame = 1;
        break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_801115F0_rockin_raceway & 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (++D_801115F0_rockin_raceway >= 3) {
            D_801115F0_rockin_raceway = 0;
        }
    }
}
/* rr2 end func_8010B89C_rockin_raceway */

/* rr2 func_8010C0D8_rockin_raceway */
void func_8010C0D8_rockin_raceway(omObjData *obj) {
    f32 t;

    if (D_80111C2A_rockin_raceway <= 0) {
        func_8010D134_rockin_raceway(0);
        D_80111C2C_rockin_raceway = 0;
        return;
    }
    if (D_80111C28_rockin_raceway == 0) {
        Center.x = D_80111BE0_rockin_raceway[0].center.x;
        Center.y = D_80111BE0_rockin_raceway[0].center.y;
        Center.z = D_80111BE0_rockin_raceway[0].center.z;
        CRot.x = D_80111BE0_rockin_raceway[0].rot.x;
        CRot.y = D_80111BE0_rockin_raceway[0].rot.y;
        CRot.z = D_80111BE0_rockin_raceway[0].rot.z;
        CZoom = D_80111BE0_rockin_raceway[0].zoom;
        RR_WRAP(CRot.x);
        RR_WRAP(CRot.y);
        RR_WRAP(CRot.z);
        D_80111C2A_rockin_raceway = 0;
    } else {
        switch (D_80111C2E_rockin_raceway) {
        case 0:
            t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
            break;
        case 1:
            t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
            t = sindf(t * 90.0f);
            break;
        default:
            t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
            t = sindf(t * 90.0f);
            t = t * t;
            break;
        }
        Center.x = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.x, D_80111BE0_rockin_raceway[1].center.x);
        Center.y = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.y, D_80111BE0_rockin_raceway[1].center.y);
        Center.z = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.z, D_80111BE0_rockin_raceway[1].center.z);
        CRot.x = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.x, D_80111BE0_rockin_raceway[1].rot.x);
        CRot.y = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.y, D_80111BE0_rockin_raceway[1].rot.y);
        CRot.z = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.z, D_80111BE0_rockin_raceway[1].rot.z);
        CZoom = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].zoom, D_80111BE0_rockin_raceway[1].zoom);
        RR_WRAP(CRot.x);
        RR_WRAP(CRot.y);
        RR_WRAP(CRot.z);
        if (D_80111C28_rockin_raceway > 0) {
            D_80111C28_rockin_raceway--;
        } else {
            D_80111C28_rockin_raceway++;
        }
    }
    D_80111C2C_rockin_raceway = 1;
    func_8010D134_rockin_raceway(0);
}
/* rr2 end func_8010C0D8_rockin_raceway */

/* rr2 func_8010C5E0_rockin_raceway */
void func_8010C5E0_rockin_raceway(s32 idx) {
    RR_WRAP(CRot.x);
    RR_WRAP(CRot.y);
    RR_WRAP(CRot.z);
    D_80111BE0_rockin_raceway[idx].center.x = Center.x;
    D_80111BE0_rockin_raceway[idx].center.y = Center.y;
    D_80111BE0_rockin_raceway[idx].center.z = Center.z;
    D_80111BE0_rockin_raceway[idx].rot.x = CRot.x;
    D_80111BE0_rockin_raceway[idx].rot.y = CRot.y;
    D_80111BE0_rockin_raceway[idx].rot.z = CRot.z;
    D_80111BE0_rockin_raceway[idx].zoom = CZoom;
    D_80111BE0_rockin_raceway[idx].unk1C = D_80111BE0_rockin_raceway[idx].unk20 = 0.0f;
}
/* rr2 end func_8010C5E0_rockin_raceway */

/* rr2 func_8010C7CC_rockin_raceway */
void func_8010C7CC_rockin_raceway(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_80111C28_rockin_raceway = frames - 1;
        D_80111C2A_rockin_raceway = frames;
        if (cx != 65535.0f) {
            D_80111BE0_rockin_raceway[0].center.x = cx;
        } else {
            D_80111BE0_rockin_raceway[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_80111BE0_rockin_raceway[0].center.y = cy;
        } else {
            D_80111BE0_rockin_raceway[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_80111BE0_rockin_raceway[0].center.z = cz;
        } else {
            D_80111BE0_rockin_raceway[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_80111BE0_rockin_raceway[0].rot.x = rx;
        } else {
            D_80111BE0_rockin_raceway[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_80111BE0_rockin_raceway[0].rot.y = ry;
        } else {
            D_80111BE0_rockin_raceway[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_80111BE0_rockin_raceway[0].rot.z = rz;
        } else {
            D_80111BE0_rockin_raceway[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_80111BE0_rockin_raceway[0].zoom = zoom;
        } else {
            D_80111BE0_rockin_raceway[0].zoom = CZoom;
        }
        func_8010C5E0_rockin_raceway(1);
    }
}
/* rr2 end func_8010C7CC_rockin_raceway */

/* rr2 func_8010C9BC_rockin_raceway */
void func_8010C9BC_rockin_raceway(void) {
    D_80111BD8_rockin_raceway->func = NULL;
}
/* rr2 end func_8010C9BC_rockin_raceway */

/* rr2 func_8010C9CC_rockin_raceway */
void func_8010C9CC_rockin_raceway(void) {
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway->func = func_8010C0D8_rockin_raceway;
}
/* rr2 end func_8010C9CC_rockin_raceway */

/* rr2 func_8010CA1C_rockin_raceway */
void func_8010CA1C_rockin_raceway(void) {
    HuCamera *cam;
    s32 i;

    D_80111C34_rockin_raceway = 0;
    D_80111C4C_rockin_raceway = HuMemAllocTag(16 * sizeof(RrFocus), 0x7918);
    D_80111C30_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010CE90_rockin_raceway);
    cam = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        cam->viewports[i].vp.vscale[0] = cam->viewports[0].vp.vscale[0];
        cam->viewports[i].vp.vscale[1] = cam->viewports[0].vp.vscale[1];
        cam->viewports[i].vp.vscale[2] = cam->viewports[0].vp.vscale[2];
        cam->viewports[i].vp.vtrans[0] = cam->viewports[0].vp.vtrans[0];
        cam->viewports[i].vp.vtrans[1] = cam->viewports[0].vp.vtrans[1];
        cam->viewports[i].vp.vtrans[2] = cam->viewports[0].vp.vtrans[2];
    }
}
/* rr2 end func_8010CA1C_rockin_raceway */

/* rr2 func_8010CADC_rockin_raceway */
#ifdef NON_MATCHING
void func_8010CADC_rockin_raceway(Vec *pos, f32 weight) {
    RrFocus *focus;

    if (D_80111C30_rockin_raceway != NULL && D_80111C34_rockin_raceway < 16) {
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].pos.x = pos->x;
        focus = &D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway];
        focus->pos.y = pos->y;
        focus->pos.z = pos->z;
        focus->weight = weight;
        D_80111C34_rockin_raceway++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CADC_rockin_raceway);
#endif
/* rr2 end func_8010CADC_rockin_raceway */

/* rr2 func_8010CB5C_rockin_raceway */
void func_8010CB5C_rockin_raceway(RrKart *kart, f32 weight) {
    Vec pos;

    pos.x = kart->unk58.x + 100.0;
    pos.y = kart->unk58.y + 100.0;
    pos.z = kart->unk58.z;
    func_8010CADC_rockin_raceway(&pos, weight);
    pos.x = kart->unk58.x - 100.0;
    pos.y = kart->unk58.y - 100.0;
    pos.z = kart->unk58.z;
    func_8010CADC_rockin_raceway(&pos, weight);
}
/* rr2 end func_8010CB5C_rockin_raceway */

/* rr2 func_8010CC10_rockin_raceway */
void func_8010CC10_rockin_raceway(void) {
    f32 max[3];
    f32 min[3];
    f32 *p;
    s32 i;
    s32 j;

    if (D_80111C34_rockin_raceway > 0) {
        for (i = 0; i < 4; i++) {
            D_80111C38_rockin_raceway[i] = 0.0f;
        }
        for (i = 0; i < D_80111C34_rockin_raceway; i++) {
            D_80111C38_rockin_raceway[3] += D_80111C4C_rockin_raceway[i].weight;
        }
        for (i = 0; i < 3; i++) {
            max[i] = ((f32 *)&D_80111C4C_rockin_raceway[0].pos)[i];
        }
        for (i = 0; i < 3; i++) {
            min[i] = ((f32 *)&D_80111C4C_rockin_raceway[0].pos)[i];
        }
        for (i = 1; i < D_80111C34_rockin_raceway; i++) {
            p = (f32 *)&D_80111C4C_rockin_raceway[i].pos;
            for (j = 0; j < 3; j++) {
                if (max[j] < p[j]) {
                    max[j] = p[j];
                }
            }
        }
        for (i = 1; i < D_80111C34_rockin_raceway; i++) {
            p = (f32 *)&D_80111C4C_rockin_raceway[i].pos;
            for (j = 0; j < 3; j++) {
                if (min[j] > p[j]) {
                    min[j] = p[j];
                }
            }
        }
        for (i = 0; i < 3; i++) {
            D_80111C38_rockin_raceway[i] = (max[i] + min[i]) * 0.5f;
        }
        if (D_80111C38_rockin_raceway[3] >= 1.0f) {
            D_80111C38_rockin_raceway[3] = 1.0f;
        }
    } else {
        D_80111C38_rockin_raceway[0] = Center.x;
        D_80111C38_rockin_raceway[1] = Center.y;
        D_80111C38_rockin_raceway[2] = Center.z;
        D_80111C38_rockin_raceway[3] = 0.0f;
    }
}
/* rr2 end func_8010CC10_rockin_raceway */

/* rr2 func_8010CE90_rockin_raceway */
void func_8010CE90_rockin_raceway(omObjData *obj) {
    f32 screen[2];
    f32 size;
    f32 scale;
    s32 i;

    size = 0.0f;
    func_8010CC10_rockin_raceway();
    Center.x = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3], Center.x, D_80111C38_rockin_raceway[0]);
    Center.y = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3], Center.y, D_80111C38_rockin_raceway[1]);
    Center.z = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3], Center.z, D_80111C38_rockin_raceway[2]);
    func_8010D134_rockin_raceway(0);
    for (i = 0; i < D_80111C34_rockin_raceway; i++) {
        func_8010D288_rockin_raceway(0, &D_80111C4C_rockin_raceway[i].pos, NULL, screen);
        if (fabs(screen[0]) > size) {
            size = fabs(screen[0]);
        }
        if (fabs(screen[1]) > size) {
            size = fabs(screen[1]);
        }
    }
    if (size != 0.0f) {
        scale = size / 0.8f;
    } else {
        scale = 1.0f;
    }
    D_80111C38_rockin_raceway[4] = scale * CZoom;
    if (D_80111AD8_rockin_raceway == 2) {
        if (D_80111C38_rockin_raceway[4] < 1500.0f) {
            D_80111C38_rockin_raceway[4] = 1500.0f;
        } else if (D_80111C38_rockin_raceway[4] >= 5000.0f) {
            D_80111C38_rockin_raceway[4] = 5000.0f;
        }
    } else {
        if (D_80111C38_rockin_raceway[4] < 1000.0f) {
            D_80111C38_rockin_raceway[4] = 1000.0f;
        } else if (D_80111C38_rockin_raceway[4] >= 5000.0f) {
            D_80111C38_rockin_raceway[4] = 5000.0f;
        }
    }
    CZoom = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3] * 0.5f, CZoom, D_80111C38_rockin_raceway[4]);
    CRot.x = func_8010E608_rockin_raceway(318.38f, CRot.x, 10.0f);
    CRot.y = func_8010E608_rockin_raceway(0.0f, CRot.y, 10.0f);
    D_80111C34_rockin_raceway = 0;
}
/* rr2 end func_8010CE90_rockin_raceway */

/* rr2 func_8010D104_rockin_raceway */
void func_8010D104_rockin_raceway(void) {
    D_80111C30_rockin_raceway->func = NULL;
}
/* rr2 end func_8010D104_rockin_raceway */

/* rr2 func_8010D114_rockin_raceway */
void func_8010D114_rockin_raceway(void) {
    D_80111C34_rockin_raceway = 0;
    D_80111C30_rockin_raceway->func = func_8010CE90_rockin_raceway;
}
/* rr2 end func_8010D114_rockin_raceway */

/* rr2 func_8010D134_rockin_raceway */
#ifdef NON_MATCHING
void func_8010D134_rockin_raceway(s32 idx) {
    HuCamera *cam;
    f32 rx;
    f32 ry;

    cam = &gCameraList[idx];
    rx = CRot.x;
    ry = CRot.y;
    cam->pos.x = Center.x + sindf(ry) * cosdf(rx) * CZoom;
    cam->pos.y = -sindf(rx) * CZoom + Center.y;
    cam->pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
    cam->at.x = Center.x;
    cam->at.y = Center.y;
    cam->at.z = Center.z;
    cam->up.x = sindf(ry) * sindf(rx);
    cam->up.y = cosdf(rx);
    cam->up.z = cosdf(ry) * sindf(rx);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D134_rockin_raceway);
#endif
/* rr2 end func_8010D134_rockin_raceway */

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
