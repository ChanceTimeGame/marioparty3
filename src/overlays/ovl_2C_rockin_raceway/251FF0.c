#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "game/hmfman.h"
#include "game/util.h"

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
void func_8010A5E4_rockin_raceway(s16 lane, s32 chr);
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
s32 func_80108760_rockin_raceway(Vec* pos, Vec* vel, s16 time);
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

#ifdef NON_MATCHING
void func_80106B28_rockin_raceway(void) {
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
        r->unk30 = D_80111B40_rockin_raceway[r->unk2E].unk08 - D_80111B44_rockin_raceway;
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106B28_rockin_raceway);
#endif

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
