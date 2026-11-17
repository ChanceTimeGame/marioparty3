#include "common.h"

// story i1
#include "mallocblock.h"
/* a story-scene actor: its object and the action its process runs every frame (as mstory1's) */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
} StoryActor; /* size = 0x18 */

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i covers
   [segs[i].start, segs[i].end] of the path's length (0..1). flags & 1: closed. As mstory1's. */
typedef struct ObPathSeg {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
} ObPathSeg; /* size = 0x8 */

typedef struct ObPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 flags;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ Vec *points;
    /* 0x0C */ ObPathSeg *segs;
} ObPath; /* size = 0x10 */

typedef struct TexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} TexAnimSlot; /* size = 0xC */

extern TexAnimSlot *D_800D1714_main;
extern f32 D_800CE17C_main[];
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, s32);
s32 func_80050064_main(s32 write);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
void func_80032FC0_main(s16, s32, s32);
s16 func_800329B4_main(void *);

extern u32 D_80114730_mstory5; /* main object state */
extern s32 D_80114734_mstory5; /* 1: the scene was seen before, A skips it */
extern s8 D_80114738_mstory5;
extern Vec D_8011473C_mstory5; /* camera position */
extern Vec D_80114748_mstory5; /* camera target */
extern Vec D_80114754_mstory5; /* camera up */
extern s32 D_80114760_mstory5;
extern s16 D_801151B0_mstory5; /* message window */
extern s16 D_801151B2_mstory5; /* background model */
extern s32 D_801151B4_mstory5; /* the controller that drives the story messages */
extern s16 D_801151B8_mstory5; /* background sprite */
extern s32 D_801151E4_mstory5;
extern StoryActor D_801151F0_mstory5[];
extern s16 D_80115364_mstory5; /* shadow model, linked by every actor */
extern const Vec D_80114A88_mstory5;

void func_80106028_mstory5(void);
void func_801085D8_mstory5(omObjData *obj);
void func_80106B64_mstory5(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106DB4_mstory5(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106B48_mstory5(omObjData *obj, Vec *to, s32 frames);
void func_80106D98_mstory5(omObjData *obj, Vec *to, s32 frames);
void func_80107080_mstory5(omObjData *obj, Vec *to, s32 frames);
s32 func_801072A0_mstory5(s16 model);
void func_80107254_mstory5(s16 model);
void func_801068E4_mstory5(s16 model, s16 anim, s16 frame);
void func_8010E3F0_mstory5(omObjData *a, omObjData *b);
void func_80105BDC_mstory5(omObjData *obj);
void func_80105CCC_mstory5(omObjData *obj);
void func_80105E34_mstory5(void);
void func_80105F5C_mstory5(omObjData *obj);
void func_8010842C_mstory5(void);
void func_801100AC_mstory5(void);
extern s16 D_801151B6_mstory5; /* low half of D_801151B4_mstory5 */
extern s16 D_80115368_mstory5;
void func_801069B8_mstory5(void);
void func_801085E0_mstory5(void);
void func_801097B8_mstory5(void);
void func_8010ABE4_mstory5(void);
void func_8010AF44_mstory5(void);
void func_8010B77C_mstory5(void);
void func_8010C4B8_mstory5(void);
void func_8010C85C_mstory5(void);
void func_8010CBE8_mstory5(void);
void func_8010DB30_mstory5(void);
void func_8010DC78_mstory5(void);
void func_8010E558_mstory5(void);
void func_8010E5D0_mstory5(void);
void func_8010F2BC_mstory5(void);
extern Vec D_801152F8_mstory5[]; /* actor positions */
extern s16 D_80115382_mstory5[4];
extern const Vec D_80114900_mstory5[]; /* actor start positions */
extern const s32 D_8011496C_mstory5[8];
extern const s32 D_8011498C_mstory5[8];
extern const s32 D_801149AC_mstory5[8];
extern const s32 D_801149CC_mstory5[8];
extern const s32 D_801149EC_mstory5[8];
void func_80108A20_mstory5(void);
extern s32 D_80115370_mstory5[4]; /* texture animations */
extern s16 D_80115380_mstory5;
void func_80109B28_mstory5(void);
typedef struct StoryMapPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} StoryMapPos; /* size = 0x4 */
extern const s32 D_801148C4_mstory5[7]; /* chapter map node sprites */
extern const StoryMapPos D_801148E0_mstory5[8]; /* chapter map node positions */
extern s16 D_801151C0_mstory5[8]; /* [0] the chapter map, [1..7] its nodes */
extern s16 D_801151D0_mstory5[8]; /* sparkles around the current node */
extern s16 D_801151E0_mstory5; /* fade overlay */
void func_801068D4_mstory5(void);
void func_8000BBFC_main(u16 spriteId, s16 alpha);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BEAC_main(u16 spriteId, s32 r, s32 g, s32 b);
/* a model part looked up by name (func_8001D33C_main) */
typedef struct StoryHmfPart {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ Vec scale;
    /* 0x28 */ char unk28[0x18];
    /* 0x40 */ Vec scale2;
} StoryHmfPart;
void *func_8001D33C_main(s16, const char *);
void func_8001EF6C_main(s16 arg0, s16 arg1, const char *arg2);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);
void func_80105FDC_mstory5(void);
void func_80105FEC_mstory5(s32 arg0);
s32 func_801068C8_mstory5(void);
void func_80106A20_mstory5(void);
void func_80106A50_mstory5(void);
void func_80106A74_mstory5(s32 mess);
s32 func_80106B30_mstory5(s32 chr);
void func_80106FC8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80106FF4_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80109790_mstory5(omObjData *obj);
void func_80109E70_mstory5(omObjData *obj);
void func_80109F48_mstory5(omObjData *obj);
void func_8010A0A8_mstory5(omObjData *obj);
void func_8010B320_mstory5(omObjData *obj);
void func_8010B5DC_mstory5(omObjData *obj);
void func_8010B9D4_mstory5(omObjData *obj);
void func_8010C6A4_mstory5(omObjData *obj);
void func_8010CA04_mstory5(omObjData *obj);
void func_8010D484_mstory5(omObjData *obj);
void func_8010E538_mstory5(omObjData *obj);
void func_8010EA34_mstory5(omObjData *obj);
void func_8010F14C_mstory5(s32 arg0, s32 arg1);
void func_8010F240_mstory5(s32 arg0);
// end story i1

/* the scene for each story step (GwPlayer[0].coin), and the flag set once it has been seen */
void (*const D_801148A0_mstory5[2])(void) = { func_801100AC_mstory5, func_8010842C_mstory5 };
const s32 D_801148A8_mstory5[2] = { 0x3A, 0x3C };

void func_801059A0_mstory5(void) {
    s16 step;

    func_800142A0_main(0x3C);
    omInitObjMan(0x1E, 0x1E);
    func_8005A6B0_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 35.0f, 80.0f, 8000.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    {
        omObjData *obj = omAddObj(0x7FDA, 0, 0, -1, func_80105F5C_mstory5);
        omSetStatBit(obj, 0xA0);
        func_80105F5C_mstory5(obj);
    }
    omAddObj(0, 0, 0, -1, func_80105BDC_mstory5);
    omAddObj(0, 0, 0, -1, func_80105CCC_mstory5);
    func_80105E34_mstory5();
    for (D_801151B4_mstory5 = 0; D_801151B4_mstory5 < 4; D_801151B4_mstory5++) {
        if (CheckControllerRead(D_801151B6_mstory5) != 0) {
            break;
        }
    }
    if (D_801151B4_mstory5 >= 4) {
        D_801151B4_mstory5 = 0;
    }
    step = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        step = 1;
    }
    D_801148A0_mstory5[step]();
    if (_CheckFlag(D_801148A8_mstory5[step]) != 0) {
        D_80114734_mstory5 = 1;
    } else {
        _SetFlag(D_801148A8_mstory5[step]);
    }
    WipeCreateIn(2, 0x10);
}

#ifdef NON_MATCHING
void func_80105BDC_mstory5(omObjData *obj) {
    u32 state = D_80114730_mstory5;

    switch (state) {
    case 0:
        HuAudSeqPlay(0x26);
        state++;
        break;
    case 1:
        state += WipeStatGet() == 0;
        break;
    case 2:
        if (D_80114734_mstory5 == 1) {
            state += (D_800D5558_main[D_801151B4_mstory5] & 0x1000) > 0;
        }
        break;
    case 3:
        WipeCreateOut(2, 0x14);
        HuAudSeqFadeOut(0x1E);
        state++;
        break;
    case 4:
        if (WipeStatGet() == 0) {
            func_8005F524_main();
            func_80050064_main(1);
            omOvlReturnEx(1);
        }
        break;
    }
    D_80114730_mstory5 = state;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80105BDC_mstory5);
#endif

void func_80105CCC_mstory5(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80114738_mstory5 == 0) {
            WipeCreateOut(2, 0x14);
            HuAudSeqFadeOut(0x1E);
            D_80114738_mstory5 = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            func_8005F524_main();
            func_80050064_main(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105D4C_mstory5(void) {
    func_8001C814_main(D_801151B2_mstory5, 4, 0);
    func_8001C814_main(D_801151B2_mstory5, 1, 0);
    func_8001C6A8_main(D_801151B2_mstory5, 0.0f);
    HuAudFXPlay(0x216);
}

void func_80105DA0_mstory5(void) {
    func_8001C814_main(D_801151B2_mstory5, 4, 4);
    func_8001C814_main(D_801151B2_mstory5, 1, 0);
    func_8001C6A8_main(D_801151B2_mstory5, D_800CCF58_main[HmfModelData[D_801151B2_mstory5].unk02].unk02);
}

void func_80105E34_mstory5(void) {
    D_801151B8_mstory5 = InitEspriteSlot(func_8000B838_main(0x1D0012), 0, 0);
    func_8000BBD4_main(D_801151B8_mstory5, 0xA0, 0x78);
    func_8000BC48_main(D_801151B8_mstory5, 0x4000);
    D_801151B2_mstory5 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_801151B2_mstory5, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_801151B2_mstory5, 2, 0);
    func_8001C814_main(D_801151B2_mstory5, 1, 1);
}

void func_80105EF4_mstory5(void) {
    func_8001C258_main(D_801151B2_mstory5, 4, 4);
    func_8000BB94_main(D_801151B8_mstory5);
}

void func_80105F28_mstory5(void) {
    func_8001C258_main(D_801151B2_mstory5, 4, 0);
    func_8000BB54_main(D_801151B8_mstory5);
}

void func_80105F5C_mstory5(omObjData *obj) {
    D_800CE17C_main[0] = D_8011473C_mstory5.x;
    D_800CE17C_main[1] = D_8011473C_mstory5.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_8011473C_mstory5, &D_80114748_mstory5, &D_80114754_mstory5);
    Hu3DCamUpdateMtx(0);
}

void func_80105FDC_mstory5(void) {
    D_80114730_mstory5 = 3;
}

void func_80105FEC_mstory5(s32 arg0) {
    D_801151E4_mstory5 = arg0;
    D_80114760_mstory5 = 0;
    omAddPrcObj(func_80106028_mstory5, 0x1000, 0x800, 0);
}

// masked 2: the assembler adds a nop after each cosdf/sindf delay slot (retail has none; gcc filled the
// slot itself here, retail apparently did not)
#ifdef NON_MATCHING
/* the chapter map: the map and its 7 nodes, a ring of 8 sparkles around the current node, and a
   fading overlay; it fades in, lights the nodes cleared so far, flashes the current one, then
   fades out and sets D_80114760_mstory5 */
void func_80106028_mstory5(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 alpha;
    s32 i;
    s32 j;

    D_801151C0_mstory5[0] = InitEspriteSlot(func_8000B838_main(0x1D0001), 0, 0);
    func_8000BBD4_main(D_801151C0_mstory5[0], 0xA0, 0x78);
    func_8000BB94_main(D_801151C0_mstory5[0]);
    for (i = 0; i < 7; i++) {
        D_801151C0_mstory5[i + 1] = InitEspriteSlot(func_8000B838_main(D_801148C4_mstory5[i]), 0, 0);
        func_8000BBD4_main(D_801151C0_mstory5[i + 1], D_801148E0_mstory5[i].x + 0x30, D_801148E0_mstory5[i].y + 0x30);
        func_8000BC48_main(D_801151C0_mstory5[i + 1], 8);
        func_8000BB94_main(D_801151C0_mstory5[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        D_801151D0_mstory5[i] = InitEspriteSlot(func_80055810_main(data), 0, 1);
        x = D_801148E0_mstory5[D_801151E4_mstory5].x + 0x30;
        y = D_801148E0_mstory5[D_801151E4_mstory5].y + 0x30;
        angle = i * 45.0f;
        x += cosdf(angle) * 32.0f;
        y -= sindf(angle) * 32.0f;
        func_8000BBD4_main(D_801151D0_mstory5[i], x, y);
        func_8000BC48_main(D_801151D0_mstory5[i], 0x1000);
        func_8000BEAC_main(D_801151D0_mstory5[i], 0xFF, 0xFF, 0xC0);
        func_8000BC48_main(D_801151D0_mstory5[i], 8);
        func_8000BE5C_main(D_801151D0_mstory5[i], 1.5f, 1.5f);
        func_8000BBFC_main(D_801151D0_mstory5[i], 0xFF);
        func_8000BB94_main(D_801151D0_mstory5[i]);
    }
    HuMemMemoryFreePerm(data);
    D_801151E0_mstory5 = InitEspriteSlot(func_8000B838_main(0x1D0000), 0, 0);
    func_8000BBD4_main(D_801151E0_mstory5, 0xA0, 0x78);
    func_8000BE5C_main(D_801151E0_mstory5, 40.0f, 30.0f);
    func_8000BC48_main(D_801151E0_mstory5, 0);
    func_8000BB94_main(D_801151E0_mstory5);
    omPrcSetDestructor(0, func_801068D4_mstory5);
    func_8000BB54_main(D_801151E0_mstory5);
    func_8000BBFC_main(D_801151E0_mstory5, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801151E0_mstory5, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_801151E0_mstory5, 0x100);
    for (i = 0; i < D_801151E4_mstory5; i++) {
        func_8000BB54_main(D_801151C0_mstory5[i + 1]);
    }
    func_80105EF4_mstory5();
    func_8000BB54_main(D_801151C0_mstory5[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801151E0_mstory5, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_801151E0_mstory5);
    func_8000BBFC_main(D_801151C0_mstory5[D_801151E4_mstory5 + 1], 0);
    func_8000BB54_main(D_801151C0_mstory5[D_801151E4_mstory5 + 1]);
    for (alpha = 0.0f, j = 0; j < 20; j++) {
        alpha += 12.75f;
        func_8000BBFC_main(D_801151C0_mstory5[D_801151E4_mstory5 + 1], alpha);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_801151C0_mstory5[D_801151E4_mstory5 + 1], 0xFF);
    func_8000BE5C_main(D_801151C0_mstory5[D_801151E4_mstory5 + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        func_8000BD94_main(D_801151D0_mstory5[i], 0, 0);
        func_8000BDDC_main(D_801151D0_mstory5[i], 1);
        func_8000BB54_main(D_801151D0_mstory5[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        func_8000BB94_main(D_801151D0_mstory5[i]);
    }
    if (D_801151E4_mstory5 == 6) {
        HuPrcSleep(40);
        func_8000BB54_main(D_801151E0_mstory5);
        func_8000BBFC_main(D_801151E0_mstory5, 0);
        for (i = 0; i < 5; i++) {
            func_8000BBFC_main(D_801151E0_mstory5, i * 0.125f * 255.0f);
            HuPrcVSleep();
        }
        func_8000BBFC_main(D_801151E0_mstory5, 0x100);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            func_8000BBFC_main(D_801151E0_mstory5, 255.0f - i * 0.125f * 255.0f);
            HuPrcVSleep();
        }
        func_8000BB94_main(D_801151E0_mstory5);
        HuPrcSleep(80);
    } else {
        HuPrcSleep(60);
    }
    func_8000BB54_main(D_801151E0_mstory5);
    func_8000BBFC_main(D_801151E0_mstory5, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801151E0_mstory5, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_801151E0_mstory5, 0x100);
    func_8000BB94_main(D_801151C0_mstory5[D_801151E4_mstory5 + 1]);
    func_8000BB94_main(D_801151C0_mstory5[0]);
    func_80105F28_mstory5();
    HuPrcSleep(30);
    for (i = 0; i < D_801151E4_mstory5; i++) {
        func_8000BB94_main(D_801151C0_mstory5[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801151E0_mstory5, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_801151E0_mstory5);
    D_80114760_mstory5 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80106028_mstory5);
#endif

s32 func_801068C8_mstory5(void) {
    return D_80114760_mstory5;
}

void func_801068D4_mstory5(void) {
}

void func_801068DC_mstory5(void) {
}

void func_801068E4_mstory5(s16 model, s16 anim, s16 frame) {
    TexAnimSlot *slot;

    if (anim >= 0) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            slot = &D_800D1714_main[anim];
            slot->unk_00 = frame;
            slot->unk_04 = 0;
            slot->unk_0A = 0;
            slot->unk_06 = 0;
            slot->unk_02 = 0;
        }
    }
}

void func_801069B8_mstory5(void) {
    D_801151B0_mstory5 = func_80060880_main(0xA0, 0xC2, 0x14);
    func_8005FE54_main(D_801151B0_mstory5, 1 << D_801151B4_mstory5);
    func_8005B6BC_main(D_801151B0_mstory5, GwStory.unk1 + 0x1C00, 0);
}

void func_80106A20_mstory5(void) {
    func_8005D294_main(D_801151B0_mstory5);
    func_80060C14_main(D_801151B0_mstory5, 1);
}

void func_80106A50_mstory5(void) {
    func_80060EA8_main(D_801151B0_mstory5, 1);
}

void func_80106A74_mstory5(s32 mess) {
    func_8005B43C_main(D_801151B0_mstory5, mess, -1, -1);
    while (func_8005E0C0_main(D_801151B0_mstory5) != 0) {
        HuPrcVSleep();
    }
}

void func_80106AC8_mstory5(s32 mess) {
    func_8005B43C_main(D_801151B0_mstory5, mess, -1, -1);
}

void func_80106AF4_mstory5(void) {
    while (func_8005E0C0_main(D_801151B0_mstory5) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106B30_mstory5(s32 chr) {
    return (chr == GwStory.unk1) ? -1 : 0;
}

void func_80106B48_mstory5(omObjData *obj, Vec *to, s32 frames) {
    func_80106B64_mstory5(obj, to, frames, 1);
}

#ifdef NON_MATCHING
/* walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning
   it to face the way first when `turn` is set */
void func_80106B64_mstory5(omObjData *obj, Vec *to, s32 frames, s32 turn) {
    Vec start;
    Vec delta;
    Vec step;
    Vec pos;
    s16 model;
    f32 t;

    model = obj->model[1];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    delta.x = to->x - start.x;
    delta.y = to->y - start.y;
    delta.z = to->z - start.z;
    if (turn) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(delta.z, delta.x) - 90.0f), 0.0f);
    }
    step.x = delta.x / frames;
    step.y = delta.y / frames;
    step.z = delta.z / frames;
    for (t = 0.0f; t < frames; t += 1.0f) {
        pos.x = t * step.x + start.x;
        pos.y = t * step.y + start.y;
        pos.z = t * step.z + start.z;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], pos.x, -5.0f, pos.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, to->x, to->y, to->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], to->x, -5.0f, to->z);
    }
    HuPrcVSleep();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80106B64_mstory5);
#endif

void func_80106D98_mstory5(omObjData *obj, Vec *to, s32 frames) {
    func_80106DB4_mstory5(obj, to, frames, 1);
}

#ifdef NON_MATCHING
/* as func_80106B64_mstory5, but the second model follows in 3D */
void func_80106DB4_mstory5(omObjData *obj, Vec *to, s32 frames, s32 turn) {
    Vec start;
    Vec delta;
    Vec step;
    Vec pos;
    s16 model;
    f32 t;

    model = obj->model[1];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    delta.x = to->x - start.x;
    delta.y = to->y - start.y;
    delta.z = to->z - start.z;
    if (turn) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(delta.z, delta.x) - 90.0f), 0.0f);
    }
    step.x = delta.x / frames;
    step.y = delta.y / frames;
    step.z = delta.z / frames;
    for (t = 0.0f; t < frames; t += 1.0f) {
        pos.x = t * step.x + start.x;
        pos.y = t * step.y + start.y;
        pos.z = t * step.z + start.z;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, to->x, to->y, to->z);
    HuPrcVSleep();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80106DB4_mstory5);
#endif

void func_80106FC8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106B48_mstory5(obj, &to, frames);
}

void func_80106FF4_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106B64_mstory5(obj, &to, frames, turn);
}

void func_80107024_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106D98_mstory5(obj, &to, frames);
}

void func_80107050_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106DB4_mstory5(obj, &to, frames, turn);
}

void func_80107080_mstory5(omObjData *obj, Vec *to, s32 frames) {
    Vec start;
    Vec delta;
    Vec rot;
    s16 model;
    f32 t;
    f32 a;

    model = obj->model[1];
    start.x = HmfModelData[model].rot.x;
    start.y = HmfModelData[model].rot.y;
    start.z = HmfModelData[model].rot.z;
    delta.x = to->x - start.x;
    delta.y = to->y - start.y;
    delta.z = to->z - start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        a = 90.0f / frames * t;
        rot.x = sindf(a) * delta.x + start.x;
        rot.y = sindf(a) * delta.y + start.y;
        rot.z = sindf(a) * delta.z + start.z;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, to->x, to->y, to->z);
    HuPrcVSleep();
}

void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80107080_mstory5(obj, &to, frames);
}

void func_80107254_mstory5(s16 model) {
    HuPrcSleep(10);
    while (func_801072A0_mstory5(model) == 0) {
        HuPrcVSleep();
    }
}

s32 func_801072A0_mstory5(s16 model) {
    s32 done;
    f32 frame;

    frame = func_8001C7D0_main(model);
    done = 0;
    if (frame == -1.0f) {
        if (D_800CCF58_main[HmfModelData[model].unk02].unk02 <= HmfModelData[model].unk40) {
            done = -1;
        }
    }
    return done;
}

void func_8010734C_mstory5(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(HmfModelData[obj->model[1]].rot.y);
    dz = speed * cosdf(HmfModelData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        HmfModelData[obj->model[2]].pos.x = HmfModelData[obj->model[1]].pos.x += dx;
        HmfModelData[obj->model[2]].pos.z = HmfModelData[obj->model[1]].pos.z += dz;
        HuPrcVSleep();
    }
}

// masked 15: retail converts frames again for the loop test (its f20 holds the divisor, then t)
#ifdef NON_MATCHING
/* moves obj's model (and its shadow, 5 below it) towards (x, y, z) over `frames` frames: steady
   for 50 frames, then speeding up; it stops once x has reached the target's */
void func_801074E8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec start;
    Vec delta;
    Vec step;
    Vec pos;
    Vec accel;
    Vec to;
    s16 model;
    f32 t;
    f32 n;
    f32 sx;
    f32 sy;
    f32 sz;

    to.x = x;
    to.y = y;
    to.z = z;
    model = obj->model[1];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    delta.x = to.x - start.x;
    delta.y = to.y - start.y;
    delta.z = to.z - start.z;
    if (turn) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(delta.z, delta.x) - 90.0f), 0.0f);
    }
    n = frames;
    sx = delta.x / n;
    accel.x = sx / 90.0f;
    sy = delta.y / n;
    accel.y = sy / 90.0f;
    sz = delta.z / n;
    accel.z = sz / 90.0f;
    step.x = sx;
    step.y = sy;
    step.z = sz;
    pos.x = start.x;
    pos.y = start.y;
    pos.z = start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        if (t < 50.0f) {
            pos.x += step.x;
            pos.y += step.y;
            pos.z += step.z;
        } else {
            pos.x += step.x += accel.x;
            pos.y += step.y += accel.y;
            pos.z += step.z += accel.z;
        }
        if (pos.x <= to.x) {
            pos.x = to.x;
            pos.y = to.y;
            pos.z = to.z;
            Hu3DModelPosSet(model, to.x, to.y, to.z);
            if (obj->model[2] >= 0) {
                Hu3DModelPosSet(obj->model[2], pos.x, pos.y - 5.0f, pos.z);
            }
            break;
        }
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], pos.x, pos.y - 5.0f, pos.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, to.x, to.y, to.z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], to.x, to.y - 5.0f, to.z);
    }
    HuPrcVSleep();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801074E8_mstory5);
#endif

ObPath *func_80107850_mstory5(Vec *points, s16 flags) {
    ObPath *path;
    Vec *prev;
    Vec *cur;
    ObPathSeg *seg;
    f32 total;
    f32 pos;
    f32 len;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 n;
    s16 i;

    path = HuMemAllocTag(sizeof(ObPath), 0x7918);
    path->flags = flags;
    path->points = points;
    prev = points;
    cur = prev + 1;
    total = 0.0f;
    n = 0;
    while (cur->x != 9999.0f || cur->y != 9999.0f || cur->z != 9999.0f) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
        n++;
        cur++;
        prev++;
    }
    if (flags & 1) {
        dx = points->x - prev->x;
        dy = points->y - prev->y;
        dz = points->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    n++;
    path->count = n;
    seg = HuMemAllocTag(n * sizeof(ObPathSeg), 0x7918);
    path->segs = seg;
    prev = points;
    cur = prev + 1;
    pos = 0.0f;
    for (i = 0; i < n; i++, prev++, cur++, seg++) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        if ((flags & 1) && i == n - 1) {
            dx = points->x - prev->x;
            dy = points->y - prev->y;
            dz = points->z - prev->z;
        }
        len = HuSqrtf(dx * dx + dy * dy + dz * dz);
        seg->start = pos / total;
        seg->end = (pos + len) / total;
        if (seg->end > 1.0f) {
            seg->end = 1.0001f;
        }
        pos += len;
    }
    return path;
}

#ifdef NON_MATCHING
/* the point at t (0..1) along a path: a spline through the four points around the segment t
   falls in */
void func_80107B54_mstory5(ObPath *path, f32 t, Vec *out) {
    f32 p[4];
    f32 times[4];
    ObPathSeg *segs;
    Vec *pts;
    s16 i;

    if (t >= 1.0f) {
        out->x = path->points[path->count - 1].x;
        out->y = path->points[path->count - 1].y;
        out->z = path->points[path->count - 1].z;
        return;
    }
    for (i = 0, segs = path->segs; i < path->count; i++, segs++) {
        if (t <= segs->start) {
            break;
        }
    }
    i--;
    i = (i < 0) ? 0 : i;
    if (i >= path->count - 1) {
        i--;
    }
    segs = path->segs;
    if (path->flags & 1) {
        times[0] = (i == 0) ? -(1.0f - segs[path->count - 1].start) : segs[i - 1].start;
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[path->count - 1].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[0].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[0].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[0].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].z : pts[i + 2].z;
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = segs[i - 1].start;
        }
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[0].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].z : pts[i + 2].z;
    }
    out->z = func_80018ACC_main(p, times, t);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80107B54_mstory5);
#endif

void func_801083FC_mstory5(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* story step 1's scene: shadow models, then every actor's and the script's processes */
void func_8010842C_mstory5(void) {
    func_801069B8_mstory5();
    D_80115364_mstory5 = func_8000B108_main(9, 0x2B9);
    D_80115368_mstory5 = func_8000B108_main(0x83, 0x2B9);
    omAddPrcObj(func_801085E0_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_801097B8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010ABE4_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010AF44_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010B77C_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010C4B8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010C85C_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010CBE8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010E558_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010E5D0_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010DC78_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_8010DB30_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010F2BC_mstory5, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115364_mstory5, 4, 4);
    func_8001C258_main(D_80115368_mstory5, 4, 4);
}

void func_801085D8_mstory5(omObjData *obj) {
}

// masked 0 when func_80017AD8_main returns s16 (functions.us.h says u8: an andi 0xFF per call; s1A.header.patch)
#ifdef NON_MATCHING
/* actor 0: the player's character */
void func_801085E0_mstory5(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 6, 0x10, -1, NULL);
    D_801151F0_mstory5[0].obj = obj;
    D_801151F0_mstory5[0].unk08 = 0;
    D_801151F0_mstory5[0].unk0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->model[4] = Hu3DModelLink(D_80115368_mstory5);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x9C));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 5, D_8011496C_mstory5[chr]);
    func_8000B460_main(obj, 6, D_8011498C_mstory5[chr]);
    func_8000B460_main(obj, 7, D_801149AC_mstory5[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_801149CC_mstory5[chr]);
    func_8000B460_main(obj, 10, D_801149EC_mstory5[chr]);
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 0x72));
    func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x9B));
    D_80115382_mstory5[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80115382_mstory5[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80115382_mstory5[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80115382_mstory5[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115382_mstory5[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_801152F8_mstory5[0] = D_80114900_mstory5[0];
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5[0].x, D_801152F8_mstory5[0].y, D_801152F8_mstory5[0].z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5[0].x, -5.0f, D_801152F8_mstory5[0].z);
    Hu3DModelPosSet(obj->model[4], D_801152F8_mstory5[0].x, D_801152F8_mstory5[0].y, D_801152F8_mstory5[0].z);
    omPrcSetDestructor(0, func_80108A20_mstory5);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[0].func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801085E0_mstory5);
#endif

void func_80108A20_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148C4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114900_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011490C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114918_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114924_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114930_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011493C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114948_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114954_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114960_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011496C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011498C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801149AC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801149CC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801149EC_mstory5);

// masked 49: CharFXPlay's s16 prototype (retail truncates its result at the assignment), and the
// stores to actors 1/7/10 and the wait for actor 1 (retail does not copy that loop test to the top)
#ifdef NON_MATCHING
/* the scene's camera-side positions and the hook part of the player's model */
const Vec D_80114A0C_mstory5 = { 0.0f, 0.0f, 0.0f };
const Vec D_80114A18_mstory5 = { 0.0f, 180.0f, 0.0f };
const Vec D_80114A24_mstory5 = { -100.0f, 0.0f, 350.0f };
const Vec D_80114A30_mstory5 = { -100.0f, 0.0f, 150.0f };
const Vec D_80114A3C_mstory5 = { 0.0f, 20.0f, 0.0f };
const Vec D_80114A48_mstory5 = { 0.0f, 0.0f, 0.0f };
const Vec D_80114A54_mstory5[2] = { { 0.0f, -26.565f, 0.0f }, { 0.0f, 45.0f, 0.0f } };
const char D_80114A6C_mstory5[] = "item_hook";

/* actor 0's script: hooks the item, the chapter map, then the exchange with actors 7, 1, 3, 4 and
   the exit; at the end it returns to idle and ends the scene */
void func_80108A28_mstory5(omObjData *obj) {
    StoryHmfPart *part;
    omObjData *obj7;
    omObjData *obj1;
    s16 model;
    s16 se;
    f32 frame;
    f32 scale;
    Vec pos;
    s32 i;

    HuPrcSleep(20);
    obj7 = D_801151F0_mstory5[7].obj;
    obj1 = D_801151F0_mstory5[1].obj;
    model = obj->model[1];
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 110.0f, 0.0f, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], model, D_80114A6C_mstory5);
    func_8001C258_main(obj->model[3], 4, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    while (!(D_801151F0_mstory5[8].unk08 & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_801151F0_mstory5[8].obj->model[1], 4, 4);
    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114A6C_mstory5, 0x1B, 0x45);
    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114A6C_mstory5, 0x1B, 0x46);
    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114A6C_mstory5, 0x1B, 0x47);
    part = func_8001D33C_main(model, D_80114A6C_mstory5);
    for (i = 0; i < 10; i++) {
        scale = sindf(i * 18.0f) * 0.8 + 1.0;
        part->scale.x = scale;
        part->scale.y = scale;
        part->scale.z = scale;
        part->scale2.x = scale;
        part->scale2.y = scale;
        part->scale2.z = scale;
        HuPrcVSleep();
    }
    func_8002FDCC_main(model, HmfModelData[model].unk02, D_80114A6C_mstory5, 0x1B, 0x47);
    func_8002FDCC_main(model, HmfModelData[model].unk02, D_80114A6C_mstory5, 0x1B, 0x46);
    func_8002FDCC_main(model, HmfModelData[model].unk02, D_80114A6C_mstory5, 0x1B, 0x45);
    func_80105FEC_mstory5(4);
    while (func_801068C8_mstory5() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80106A20_mstory5();
    func_80106A74_mstory5((func_80106B30_mstory5(0) == 0) ? 0x5A4B : 0x5B3F);
    func_80106A50_mstory5();
    func_8001C5B4_main(model, obj->motion[5]);
    func_8001C814_main(model, 4, 4);
    func_8001C92C_main(model, 2.0f);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C5B4_main(model, obj->motion[6]);
    func_8001C814_main(model, 4, 4);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C92C_main(model, 1.0f);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    HuAudSeqFadeOut(20);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_80107080_mstory5(obj, (Vec *)&D_80114A0C_mstory5, 10);
    HuAudSeqPlay(0x72);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80017954_main(model, 2, GwStory.unk1, D_80115382_mstory5[2]);
    func_80107254_mstory5(model);
    se = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    func_80107080_mstory5(obj7, (Vec *)&D_80114A54_mstory5[0], 3);
    func_80106B48_mstory5(obj7, (Vec *)&D_80114A24_mstory5, 5);
    func_80107080_mstory5(obj7, (Vec *)&D_80114A3C_mstory5, 3);
    D_801151F0_mstory5[1].func = func_80109F48_mstory5;
    HuAudFXPlay(0x219);
    HuAudFXStop(se);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_80017954_main(model, 2, GwStory.unk1, D_80115382_mstory5[3]);
    func_80107080_mstory5(obj7, (Vec *)&D_80114A48_mstory5, 3);
    func_80106B64_mstory5(obj7, (Vec *)&D_80114A30_mstory5, 10, 0);
    func_80107254_mstory5(model);
    func_80107080_mstory5(obj, (Vec *)&D_80114A18_mstory5, 10);
    HuAudSeqPlay(0x26);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80017954_main(model, 2, GwStory.unk1, D_80115382_mstory5[0]);
    HuAudFXPlay(0x159);
    func_8001C624_main(D_801151F0_mstory5[7].obj->model[1], HmfModelData[D_801151F0_mstory5[7].obj->motion[1]].unk02, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5((func_80106B30_mstory5(0) == 0) ? 0x5A4C : 0x5B40);
    func_80106A50_mstory5();
    func_8001C624_main(D_801151F0_mstory5[7].obj->model[1], HmfModelData[D_801151F0_mstory5[7].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(model, HmfModelData[obj->motion[8]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801151F0_mstory5[3].func = func_8010B320_mstory5;
    func_80107228_mstory5(D_801151F0_mstory5[7].obj, 0.0f, 158.46f, 0.0f, 5);
    D_801151F0_mstory5[1].func = func_8010EA34_mstory5;
    D_801151F0_mstory5[7].func = func_8010E538_mstory5;
    D_801151F0_mstory5[10].func = func_80109790_mstory5;
    func_80106FF4_mstory5(obj1, 238.0f, 100.0f, 214.0f, 10, 0);
    while (!(D_801151F0_mstory5[3].unk08 & 8)) {
        HuPrcVSleep();
    }
    func_80106A20_mstory5();
    func_80106A74_mstory5((func_80106B30_mstory5(0) == 0) ? 0x5A4D : 0x5B41);
    func_80106A50_mstory5();
    D_801151F0_mstory5[3].unk08 |= 1;
    while (!(D_801151F0_mstory5[3].unk08 & 4)) {
        HuPrcVSleep();
    }
    D_801151F0_mstory5[9].func = func_8010A0A8_mstory5;
    while (TRUE) {
        if (D_801151F0_mstory5[1].unk08 & 1) {
            break;
        }
        HuPrcVSleep();
    }
    D_801151F0_mstory5[4].func = func_8010B9D4_mstory5;
    while (!(D_801151F0_mstory5[4].unk08 & 2)) {
        HuPrcVSleep();
    }
    D_801151F0_mstory5[10].func = func_8010D484_mstory5;
    D_801151F0_mstory5[1].func = func_80109E70_mstory5;
    D_801151F0_mstory5[3].func = func_8010B5DC_mstory5;
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_8010F14C_mstory5(0, 0x1F);
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8010F240_mstory5(0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801151F0_mstory5[5].func = func_8010C6A4_mstory5;
    D_801151F0_mstory5[6].func = func_8010CA04_mstory5;
    HuPrcSleep(30);
    HuPrcSleep(40);
    HuAudFXPlay(0x2A0);
    func_80106A20_mstory5();
    func_80106A74_mstory5((func_80106B30_mstory5(0) == 0) ? 0x5A57 : 0x5B4B);
    func_80106A50_mstory5();
    HuPrcSleep(30);
    D_801151F0_mstory5[0].unk08 |= 1;
    HuPrcSleep(50);
    func_80105FDC_mstory5();
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A0C_mstory5);
INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A18_mstory5);
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80108A28_mstory5);
INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A3C_mstory5);
INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A48_mstory5);
INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A54_mstory5);
INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A6C_mstory5);
INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A78_mstory5);
INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A80_mstory5);
#endif

void func_80109698_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C624_main(model, HmfModelData[obj->motion[9]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    HuPrcSleep(80);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

void func_8010975C_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80114A88_mstory5, 10);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

void func_80109790_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(D_801151F0_mstory5[0].obj, D_801151F0_mstory5[3].obj);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A88_mstory5);

/* actor 1 */
void func_801097B8_mstory5(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[1].obj = obj;
    D_801151F0_mstory5[1].unk08 = 0;
    D_801151F0_mstory5[1].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_801152F8_mstory5[1] = D_80114900_mstory5[1];
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5[1].x, D_801152F8_mstory5[1].y, D_801152F8_mstory5[1].z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5[1].x, -5.0f, D_801152F8_mstory5[1].z);
    data = DataRead(0xA007E);
    D_80115370_mstory5[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main((s16)D_80115370_mstory5[0], 1, 0);
    func_80032FF8_main((s16)D_80115370_mstory5[0], 0);
    D_80115380_mstory5 = func_80032694_main(HmfModelData[obj->model[1]].hmf, (s16)D_80115370_mstory5[0], 0, "c204n_0_DEF");
    D_80115370_mstory5[0] = D_800D1714_main[D_80115370_mstory5[0]].unk_00;
    data = DataRead(0xA0080);
    D_80115370_mstory5[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80115370_mstory5[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0085);
    D_80115370_mstory5[3] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, (s16)D_80115370_mstory5[0]);
    omPrcSetDestructor(0, func_80109B28_mstory5);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80109B28_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AA0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109B30_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109E70_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109F48_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010A0A8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010ABC4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010ABE4_mstory5);

void func_8010AE0C_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AB8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AD0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114ADC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AE8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AF4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B00_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B24_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B54_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BA8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BB4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BCC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BD8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BE4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BF0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010AE14_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010AF44_mstory5);

void func_8010B318_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B320_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B5DC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B6F8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B77C_mstory5);

void func_8010B9CC_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B9D4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010C4B8_mstory5);

void func_8010C69C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010C6A4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010C85C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CA04_mstory5);

void func_8010CBE0_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CBE8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CFE4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D214_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D230_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D460_mstory5);

void func_8010D47C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D484_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D560_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D594_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D7D8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DADC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DB30_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DC78_mstory5);

void func_8010DE7C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DE84_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E1A0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E3F0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E538_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E558_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E5D0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E648_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E6B4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E7B0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E870_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E8C0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010EA34_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010EBCC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010EDFC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F02C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F0B8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C44_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C50_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C5C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114CA8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F14C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F240_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F2BC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F41C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F4D0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F7D4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011007C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801100AC_mstory5);

void func_80110200_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80110208_mstory5);

void func_80110618_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D20_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D2C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D38_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D44_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D50_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D5C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D68_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D74_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D80_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114DA0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114DC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114DE0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E00_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E30_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80110620_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801113BC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111480_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801114B4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E54_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EA8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EB0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EB8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EC4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801114E8_mstory5);

void func_80111818_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EDC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111820_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111B60_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111C48_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111DB8_mstory5);

void func_80111FE0_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EF4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F24_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F30_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F3C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F48_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F9C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111FE8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112104_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112514_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011275C_mstory5);

void func_80112994_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011299C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112F38_mstory5);

void func_80113130_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113138_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113470_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113618_mstory5);

void func_8011396C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113974_mstory5);

void func_80113B64_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FD8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FE4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FF0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115014_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115020_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011502C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115038_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115050_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115068_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115074_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115080_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115098_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150B0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150BC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113B6C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113CF8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113D2C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113E58_mstory5);

void func_80114010_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80114018_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80114334_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150EC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150F8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115110_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011511C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115128_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115134_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011514C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011447C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80114560_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801145DC_mstory5);
