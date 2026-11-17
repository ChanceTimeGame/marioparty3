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

// story i2
/* a story-scene actor: its object and the action its process runs every frame */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 flags; /* cues the scripts give each other */
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} StoryActor; /* size = 0x18 */

extern StoryActor D_801151F0_mstory5[9];
extern StoryActor D_801152C8_mstory5; /* actors 9 and 10 are objects of their own */
extern StoryActor D_801152E0_mstory5;
extern Vec D_801152F8_mstory5[9]; /* actor positions */
extern s16 D_80115364_mstory5; /* shadow model, linked by every actor */
extern s32 D_80115370_mstory5[4]; /* texture animations */
extern s16 D_80115380_mstory5;
extern s16 D_80115368_mstory5; /* a model actor 3 links */
extern s16 D_8011538A_mstory5[4]; /* actor 3's texture animations */
extern const Vec D_80114AA0_mstory5;
extern const Vec D_80114AB8_mstory5[2];
extern const Vec D_80114AD0_mstory5;
extern const Vec D_80114ADC_mstory5;
extern const Vec D_80114AE8_mstory5;
extern const Vec D_80114AF4_mstory5;
extern const Vec D_80114B00_mstory5;
extern const Vec D_80114B0C_mstory5;
extern const Vec D_80114B18_mstory5;
extern const Vec D_80114B24_mstory5;
void func_801068E4_mstory5(s16 model, s16 anim, s16 frame);
void func_80106A20_mstory5(void);
void func_80106A50_mstory5(void);
void func_80106A74_mstory5(s32 mes);
s32 func_80106B30_mstory5(s32 chr);
void func_80106B48_mstory5(omObjData *obj, Vec *pos, s32 time);
void func_80106FC8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 time);
void func_80107080_mstory5(omObjData *obj, Vec *rot, s32 time);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 time);
void func_80107254_mstory5(s16 model);
void func_80106B64_mstory5(omObjData *obj, Vec *pos, s32 time, s32 arg3);
void func_80106FF4_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 time, s32 arg5);
void func_8010CFE4_mstory5(void);
void func_8010D214_mstory5(void);
void func_8010E1A0_mstory5(omObjData *obj);
void func_8010E6B4_mstory5(omObjData *obj);
void func_8010E870_mstory5(omObjData *obj);
void func_8010EBCC_mstory5(omObjData *obj);
void func_8010EDFC_mstory5(omObjData *obj);
void func_8010F02C_mstory5(omObjData *obj);
void func_8010F0B8_mstory5(omObjData *obj);
void func_8010D594_mstory5(omObjData *obj);
void func_8010D7D8_mstory5(omObjData *obj);
void func_8010E648_mstory5(omObjData *obj);
void func_8010B6F8_mstory5(omObjData *obj);
void func_80109F48_mstory5(omObjData *obj);
void func_8010ABC4_mstory5(omObjData *obj);
extern s16 D_80114770_mstory5;
extern const Vec D_80114B54_mstory5;
extern const Vec D_80114B60_mstory5[5];
extern const Vec D_80114B9C_mstory5;
extern const Vec D_80114BA8_mstory5;
extern const Vec D_80114BB4_mstory5[2];
extern const Vec D_80114BCC_mstory5;
extern const Vec D_80114BD8_mstory5;
extern const Vec D_80114BE4_mstory5;
extern const Vec D_80114BF0_mstory5[2];
void func_80105D4C_mstory5(void);
void func_801074E8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 time, s32 arg5);
void func_8010F41C_mstory5(omObjData *obj);
void func_80108A28_mstory5(omObjData *obj);
void func_80109698_mstory5(omObjData *obj);
void func_8010975C_mstory5(omObjData *obj);
void func_8010D560_mstory5(omObjData *obj);
void func_8010DE84_mstory5(omObjData *obj);
void func_8010AE0C_mstory5(void);
void func_8010AE14_mstory5(omObjData *obj);
void func_8010E3F0_mstory5(omObjData *obj, omObjData *target);
void func_8010F14C_mstory5(s32 actor, s32 fx);
void func_8010F240_mstory5(s32 actor);
extern const Vec D_80114918_mstory5; /* actor 2's start position */
extern const Vec D_80114924_mstory5; /* actor 3's */
extern const Vec D_80114930_mstory5; /* actor 4's */
extern const Vec D_8011493C_mstory5; /* actor 5's */
extern const Vec D_80114948_mstory5; /* actor 6's */
void func_8010B318_mstory5(void);
void func_8010B9CC_mstory5(void);
void func_8010C69C_mstory5(void);
void func_8010CBE0_mstory5(void);
void func_8010D47C_mstory5(void);
void func_80017358_main(s16 arg0, char *arg1, s16 arg2, char *arg3);
extern const Vec D_80114954_mstory5; /* actor 7's start position */
extern s32 D_80114774_mstory5; /* 1 once actor 7 exists */
/* func_801085D8_mstory5 (the idle action) is defined above as void (void) */
#define STORY5_IDLE ((void (*)(omObjData *))func_801085D8_mstory5)

const Vec D_80114AAC_mstory5 = { 10.0f, 378.9f, 0.0f };

void func_80109B30_mstory5(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    D_801151F0_mstory5[0].func = func_80109698_mstory5;
    D_801151F0_mstory5[7].func = func_8010D560_mstory5;
    func_80107080_mstory5(obj, (Vec *)&D_80114AAC_mstory5, 30);
    func_80106B48_mstory5(obj, (Vec *)&D_80114B0C_mstory5, 20);
    HuPrcSleep(30);
    func_80107080_mstory5(obj, (Vec *)&D_80114ADC_mstory5, 10);
    func_80106B48_mstory5(obj, (Vec *)&D_80114B00_mstory5, 15);
    D_801151F0_mstory5[0].func = func_8010975C_mstory5;
    func_80107080_mstory5(obj, (Vec *)D_80114AB8_mstory5, 10);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115370_mstory5[1]);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A49 : 0x5B3D);
    func_80106A50_mstory5();
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115370_mstory5[0]);
    func_80107228_mstory5(D_801151F0_mstory5[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_80107080_mstory5(D_801151F0_mstory5[7].obj, (Vec *)&D_80114B18_mstory5, 10);
    func_80107080_mstory5(obj, (Vec *)&D_80114AD0_mstory5, 20);
    func_8001C624_main(D_801151F0_mstory5[7].obj->model[1], HmfModelData[D_801151F0_mstory5[7].obj->motion[1]].unk02, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4A : 0x5B3E);
    func_80106A50_mstory5();
    func_8001C624_main(D_801151F0_mstory5[7].obj->model[1], HmfModelData[D_801151F0_mstory5[7].obj->motion[0]].unk02, 0, 10, 2);
    func_80107080_mstory5(D_801151F0_mstory5[7].obj, (Vec *)&D_80114B24_mstory5, 10);
    D_801151F0_mstory5[8].func = func_8010DE84_mstory5;
    func_80107080_mstory5(obj, (Vec *)&D_80114AA0_mstory5, 20);
    func_8001C624_main(D_801151F0_mstory5[0].obj->model[1], HmfModelData[D_801151F0_mstory5[0].obj->motion[12]].unk02, 0, 10, 2);
    while (!(D_801151F0_mstory5[8].flags & 2)) {
        HuPrcVSleep();
    }
    D_801151F0_mstory5[0].func = func_80108A28_mstory5;
    HuPrcSleep(40);
    func_80107080_mstory5(obj, (Vec *)&D_80114AF4_mstory5, 50);
    func_80107080_mstory5(obj, (Vec *)&D_80114AE8_mstory5, 40);
    D_801151F0_mstory5[1].func = STORY5_IDLE;
}

/* actor 1 turns and leaves */
void func_80109E70_mstory5(omObjData *obj) {
    Vec pos;
    s16 model;

    model = obj->model[1];
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801151F0_mstory5[1].func = STORY5_IDLE;
}

/* actor 1 hops */
void func_80109F48_mstory5(omObjData *obj) {
    Vec pos;
    Vec start;
    s16 model;
    s32 i;

    model = obj->model[1];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    pos.y = HmfModelData[model].pos.y;
    i = 0;
    do {
        pos.x = HmfModelData[model].pos.x;
        pos.z = HmfModelData[model].pos.z;
        Hu3DModelPosSet(model, pos.x, sindf(i * 15.0f) * 80.0f + pos.y, pos.z);
        i++;
        HuPrcVSleep();
    } while (i < 12);
    Hu3DModelPosSet(model, start.x, start.y, start.z);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115370_mstory5[2]);
    D_801151F0_mstory5[1].func = STORY5_IDLE;
}

/* the scene's climax: actors 0, 1, 3 and 7 talk it out, then actor 7 is thrown */
void func_8010A0A8_mstory5(omObjData *obj) {
    omObjData *a3;
    omObjData *a7;
    omObjData *a1;
    omObjData *a0;

    a1 = D_801151F0_mstory5[1].obj;
    a3 = D_801151F0_mstory5[3].obj;
    a7 = D_801151F0_mstory5[7].obj;
    a0 = D_801151F0_mstory5[0].obj;
    while (!(D_801151F0_mstory5[3].flags & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(D_801151F0_mstory5[1].obj, (Vec *)&D_80114BE4_mstory5, 15, 0);
    D_801151F0_mstory5[3].func = STORY5_IDLE;
    func_80107080_mstory5(D_801151F0_mstory5[3].obj, (Vec *)&D_80114B9C_mstory5, 10);
    func_80106FF4_mstory5(a7, 0.0f, 200.0f, 150.0f, 15, 0);
    func_8001C624_main(D_801151F0_mstory5[0].obj->model[1], HmfModelData[D_801151F0_mstory5[0].obj->motion[0]].unk02, 0, 30, 2);
    func_8001C624_main(D_801151F0_mstory5[3].obj->model[1], HmfModelData[D_801151F0_mstory5[3].obj->motion[9]].unk02, 0, 30, 0);
    HuPrcSleep(10);
    func_8001C624_main(D_801151F0_mstory5[1].obj->model[1], HmfModelData[D_801151F0_mstory5[1].obj->motion[2]].unk02, 0, 30, 2);
    func_80107254_mstory5(D_801151F0_mstory5[3].obj->model[1]);
    func_8001C624_main(D_801151F0_mstory5[3].obj->model[1], HmfModelData[D_801151F0_mstory5[3].obj->motion[9]].unk02, 0, 30, 0);
    func_80107254_mstory5(D_801151F0_mstory5[3].obj->model[1]);
    func_8001C624_main(D_801151F0_mstory5[3].obj->model[1], HmfModelData[D_801151F0_mstory5[3].obj->motion[0]].unk02, 0, 30, 2);
    func_8001C624_main(D_801151F0_mstory5[1].obj->model[1], HmfModelData[D_801151F0_mstory5[1].obj->motion[0]].unk02, 0, 30, 2);
    D_801151F0_mstory5[1].func = STORY5_IDLE;
    func_80106B48_mstory5(D_801151F0_mstory5[1].obj, (Vec *)D_80114BF0_mstory5, 8);
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, (Vec *)D_80114B60_mstory5, 10);
    func_80107080_mstory5(D_801151F0_mstory5[3].obj, (Vec *)&D_80114B54_mstory5, 5);
    D_801151F0_mstory5[7].func = STORY5_IDLE;
    D_801151F0_mstory5[0].func = STORY5_IDLE;
    func_80107080_mstory5(D_801151F0_mstory5[7].obj, (Vec *)&D_80114BA8_mstory5, 5);
    func_80107080_mstory5(D_801151F0_mstory5[0].obj, (Vec *)D_80114BB4_mstory5, 5);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4E : 0x5B42);
    func_80106A50_mstory5();
    func_80106B48_mstory5(D_801151F0_mstory5[1].obj, (Vec *)&D_80114BE4_mstory5, 10);
    func_80107228_mstory5(D_801151F0_mstory5[7].obj, 15.0f, 20.0f, 0.0f, 5);
    func_8001C624_main(a7->model[1], HmfModelData[a7->motion[1]].unk02, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4F : 0x5B43);
    func_80106A50_mstory5();
    func_8001C624_main(a7->model[1], HmfModelData[a7->motion[0]].unk02, 0, 10, 2);
    HuAudFXPlay(0x27C);
    func_80107228_mstory5(a3, 0.0f, -110.0f, 0.0f, 5);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[4]].unk02, 0, 10, 0);
    func_80107254_mstory5(a3->model[1]);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[5]].unk02, 0, 10, 2);
    func_801068E4_mstory5(a1->model[1], D_80115380_mstory5, D_80115370_mstory5[3]);
    func_8010CFE4_mstory5();
    HuAudFXPlay(0x21C);
    func_8001C624_main(a7->model[1], HmfModelData[a7->motion[4]].unk02, 0, 10, 2);
    HuPrcSleep(20);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A50 : 0x5B44);
    func_80106A50_mstory5();
    func_80107228_mstory5(a7, 0.0f, 0.0f, 0.0f, 5);
    D_801151F0_mstory5[8].func = func_8010E1A0_mstory5;
    HuPrcSleep(50);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[12]].unk02, 0, 10, 0);
    func_80107254_mstory5(a3->model[1]);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[0]].unk02, 0, 10, 2);
    D_801152E0_mstory5.func = STORY5_IDLE;
    func_80107228_mstory5(a0, 0.0f, 150.0f, 0.0f, 10);
    func_801068E4_mstory5(a1->model[1], D_80115380_mstory5, D_80115370_mstory5[0]);
    func_8001C624_main(a0->model[1], HmfModelData[a0->motion[10]].unk02, 0, 10, 2);
    HuPrcSleep(100);
    func_80106B48_mstory5(D_801151F0_mstory5[1].obj, (Vec *)D_80114BF0_mstory5, 8);
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, (Vec *)D_80114B60_mstory5, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A51 : 0x5B45);
    func_80106A50_mstory5();
    func_8001C624_main(a0->model[1], HmfModelData[a0->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(D_801151F0_mstory5[3].obj->model[1], HmfModelData[D_801151F0_mstory5[3].obj->motion[1]].unk02, 0, 30, 2);
    D_801151F0_mstory5[3].func = func_8010E6B4_mstory5;
    D_801151F0_mstory5[7].func = func_8010E870_mstory5;
    HuPrcSleep(70);
    func_801068E4_mstory5(a1->model[1], D_80115380_mstory5, D_80115370_mstory5[1]);
    func_8001C624_main(a1->model[1], HmfModelData[a1->motion[1]].unk02, 0, 10, 2);
    D_801151F0_mstory5[1].func = func_8010ABC4_mstory5;
    func_80106FF4_mstory5(a1, 238.0f, 100.0f, 214.0f, 60, 0);
    D_801151F0_mstory5[1].func = STORY5_IDLE;
    D_801151F0_mstory5[8].flags |= 0x10;
    while (!(D_801151F0_mstory5[8].flags & 8)) {
        HuPrcVSleep();
    }
    func_80107228_mstory5(a1, 0.0f, -140.0f, 0.0f, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A52 : 0x5B46);
    func_80106A50_mstory5();
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, (Vec *)D_80114B60_mstory5, 10);
    HuPrcSleep(20);
    func_8010D214_mstory5();
    func_8001C624_main(a7->model[1], HmfModelData[a7->motion[0]].unk02, 0, 10, 2);
    D_80114770_mstory5 = 1;
    func_80106B48_mstory5(D_801151F0_mstory5[7].obj, (Vec *)&D_80114BCC_mstory5, 3);
    HuAudFXPlay(0x219);
    CharFXPlay(0x2AB, GwStory.unk1);
    func_8004AC5C_main(0x2B3, 1);
    D_801152E0_mstory5.func = func_8010EBCC_mstory5;
    D_801151F0_mstory5[3].func = func_8010EDFC_mstory5;
    D_80114770_mstory5 = 0;
    func_80106B64_mstory5(D_801151F0_mstory5[7].obj, (Vec *)&D_80114BD8_mstory5, 5, 0);
    D_801151F0_mstory5[1].func = func_80109F48_mstory5;
    HuPrcSleep(12);
    func_80107228_mstory5(D_801151F0_mstory5[1].obj, 0.0f, -135.0f, 0.0f, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A53 : 0x5B47);
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, (Vec *)D_80114B60_mstory5, 10);
    func_8010CFE4_mstory5();
    HuAudFXPlay(0x21C);
    func_80107228_mstory5(a7, 20.0f, 10.0f, 0.0f, 10);
    func_8001C624_main(a7->model[1], HmfModelData[a7->motion[4]].unk02, 0, 10, 2);
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A54 : 0x5B48);
    func_80106A50_mstory5();
    CharFXPlay(0x274, GwStory.unk1);
    func_8004AC5C_main(0x27C, 1);
    D_801152E0_mstory5.func = func_8010F02C_mstory5;
    D_801151F0_mstory5[3].func = func_8010F0B8_mstory5;
    HuPrcSleep(10);
    HuPrcSleep(40);
    D_801151F0_mstory5[1].flags |= 1;
    D_801152C8_mstory5.func = STORY5_IDLE;
}

void func_8010ABC4_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[0].obj);
}

/* actor 2 */
void func_8010ABE4_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[2].obj = obj;
    D_801151F0_mstory5[2].flags = 0;
    D_801151F0_mstory5[2].unk0C = 0;
    if (func_80106B30_mstory5(0) == 0) {
        obj->model[1] = func_8000B108_main(0x200A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
        func_8000B460_main(obj, 0, 0x20000);
        func_8000B460_main(obj, 1, 0x1D003C);
        func_8000B460_main(obj, 2, 0x1D003D);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
        func_8000B460_main(obj, 0, 0x30000);
        func_8000B460_main(obj, 1, 0x1D0046);
        func_8000B460_main(obj, 2, 0x1D0047);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_801152F8_mstory5[2] = D_80114918_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5[2].x, D_801152F8_mstory5[2].y, D_801152F8_mstory5[2].z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5[2].x, -5.0f, D_801152F8_mstory5[2].z);
    omPrcSetDestructor(0, func_8010AE0C_mstory5);
    D_801151F0_mstory5[2].func = func_8010AE14_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[2].func(obj);
        HuPrcVSleep();
    }
}

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

const Vec D_80114C08_mstory5 = { 200.0f, 0.0f, 1200.0f };

/* actor 2's first action */
void func_8010AE14_mstory5(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106B30_mstory5(0) == 0) {
        CharFXPlay(0x26B, 0);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_801151F0_mstory5[1].func = func_80109B30_mstory5;
    HuPrcSleep(70);
    if (func_80106B30_mstory5(0) == 0) {
        CharFXPlay(0x286, 0);
    } else {
        CharFXPlay(0x286, 1);
    }
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    func_8010F14C_mstory5(2, 0x28);
    func_80106B48_mstory5(obj, (Vec *)&D_80114C08_mstory5, 0x28);
    func_8010F240_mstory5(2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801151F0_mstory5[2].func = STORY5_IDLE;
}

// masked 0 except an andi 0xFF per func_80017AD8_main call: it returns s16, functions.us.h says u8
// (~/repos/mp3-wt/s1A.header.patch)
#ifdef NON_MATCHING
/* actor 3: character 7's model */
void func_8010AF44_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 0x10, -1, NULL);
    D_801151F0_mstory5[3].obj = obj;
    D_801151F0_mstory5[3].flags = 0;
    D_801151F0_mstory5[3].unk0C = 0;
    obj->model[1] = func_8000B108_main(0x90000, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    obj->model[3] = Hu3DModelLink(D_80115368_mstory5);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, 0x90004);
    func_8000B460_main(obj, 1, func_80017BB8_main(7, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(7, 2));
    func_8000B460_main(obj, 3, 0x9000C);
    func_8000B460_main(obj, 4, 0x1D0079);
    func_8000B460_main(obj, 5, 0x1D007B);
    func_8000B460_main(obj, 6, 0x1D007C);
    func_8000B460_main(obj, 7, func_80017BB8_main(7, 0x7A));
    func_8000B460_main(obj, 8, 0x70003);
    func_8000B460_main(obj, 9, 0x1D0078);
    func_8000B460_main(obj, 10, func_80017BB8_main(7, 0x13));
    func_8000B460_main(obj, 11, func_80017BB8_main(7, 0x72));
    func_8000B460_main(obj, 12, func_80017BB8_main(7, 0x32));
    func_8000B460_main(obj, 13, func_80017BB8_main(7, 0x33));
    func_8000B460_main(obj, 14, func_80017BB8_main(7, 0x21));
    D_8011538A_mstory5[0] = func_80017790_main(obj->model[1], 2, 7, func_80017BB8_main(7, 0xA4));
    D_8011538A_mstory5[1] = func_80017AD8_main(func_80017BB8_main(7, 0xAA));
    D_8011538A_mstory5[2] = func_80017AD8_main(func_80017BB8_main(7, 0xA5));
    D_8011538A_mstory5[3] = func_80017AD8_main(func_80017BB8_main(7, 0xA6));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, 7, D_8011538A_mstory5[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_801152F8_mstory5[3] = D_80114924_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5[3].x, D_801152F8_mstory5[3].y, D_801152F8_mstory5[3].z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5[3].x, -5.0f, D_801152F8_mstory5[3].z);
    omPrcSetDestructor(0, func_8010B318_mstory5);
    D_801151F0_mstory5[3].func = STORY5_IDLE;
    while (TRUE) {
        D_801151F0_mstory5[3].func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010AF44_mstory5);
#endif

void func_8010B318_mstory5(void) {
}

/* actor 3's part of the scene */
void func_8010B320_mstory5(omObjData *obj) {
    s16 model;

    model = obj->model[1];
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80105D4C_mstory5();
    HuPrcSleep(15);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    while (!(D_801151F0_mstory5[1].flags & 2)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_8004AAD0_main(HuAudFXPlay(0x297), 0x5A);
    func_80107254_mstory5(model);
    D_801151F0_mstory5[3].flags |= 8;
    while (!(D_801151F0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    func_8010F14C_mstory5(3, 0x28);
    func_8004AAD0_main(D_801151F0_mstory5[3].unk14, 0x40);
    D_801152E0_mstory5.func = func_8010F41C_mstory5;
    func_801074E8_mstory5(obj, 150.0f, 0.0f, 384.0f, 180, 1);
    func_8010F240_mstory5(3);
    func_801068E4_mstory5(D_801151F0_mstory5[1].obj->model[1], D_80115380_mstory5, D_80115370_mstory5[0]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[10]].unk02, 0, 30, 2);
    D_801151F0_mstory5[3].flags |= 4;
    HuPrcSleep(60);
    func_801068E4_mstory5(D_801151F0_mstory5[1].obj->model[1], D_80115380_mstory5, D_80115370_mstory5[0]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
    D_801151F0_mstory5[3].flags |= 2;
    D_801151F0_mstory5[3].func = STORY5_IDLE;
}

/* actor 3 turns and leaves */
void func_8010B5DC_mstory5(omObjData *obj) {
    Vec pos;
    s16 model;

    model = obj->model[1];
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_8010F14C_mstory5(3, 0x1F);
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8010F240_mstory5(3);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801151F0_mstory5[3].func = STORY5_IDLE;
}

void func_8010B6F8_mstory5(omObjData *obj) {
    s16 model;

    model = obj->model[1];
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801151F0_mstory5[3].func = STORY5_IDLE;
}

/* actor 4 */
void func_8010B77C_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x10, 8, -1, NULL);
    D_801151F0_mstory5[4].obj = obj;
    D_801151F0_mstory5[4].flags = 0;
    D_801151F0_mstory5[4].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    obj->model[3] = func_8000B108_main(0x1D0027, 0x2B9);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0x1D0031);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C814_main(obj->model[3], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801152F8_mstory5[4] = D_80114930_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5[4].x, D_801152F8_mstory5[4].y, D_801152F8_mstory5[4].z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5[4].x, -5.0f, D_801152F8_mstory5[4].z);
    omPrcSetDestructor(0, func_8010B9CC_mstory5);
    D_801151F0_mstory5[4].func = STORY5_IDLE;
    while (TRUE) {
        D_801151F0_mstory5[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B9CC_mstory5(void) {
}

/* actor 4's scene: actor 3 knocks it flying (it spins away, shrinking), then the scene goes on */
void func_8010B9D4_mstory5(omObjData *obj) {
    Vec rot;
    Vec pos;
    Vec vel;
    omObjData *a3;
    omObjData *a7;
    omObjData *a0;
    omObjData *a1;
    s16 model;
    f32 scale;
    f32 shadow;
    f32 i;

    model = obj->model[1];
    a3 = D_801151F0_mstory5[3].obj;
    a7 = D_801151F0_mstory5[7].obj;
    a0 = D_801151F0_mstory5[0].obj;
    a1 = D_801151F0_mstory5[1].obj;
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8010D214_mstory5();
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A55 : 0x5B49);
    func_80106A50_mstory5();
    D_801151F0_mstory5[7].func = func_8010D594_mstory5;
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(40);
    func_80107228_mstory5(a3, 0.0f, -90.0f, 0.0f, 10);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[1]].unk02, 0, 10, 2);
    func_8010F14C_mstory5(3, 0x1F);
    func_80106FC8_mstory5(a3, HmfModelData[a3->model[1]].pos.x - 50.0f, HmfModelData[a3->model[1]].pos.y, HmfModelData[a3->model[1]].pos.z, 10);
    func_8010F240_mstory5(3);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[0]].unk02, 0, 10, 2);
    while (!(D_801151F0_mstory5[7].flags & 1)) {
        HuPrcVSleep();
    }
    func_80106FC8_mstory5(obj, 300.0f, 0.0f, 380.0f, 30);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115370_mstory5[2]);
    func_80107228_mstory5(a3, 0.0f, 90.0f, 0.0f, 10);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[7]].unk02, 0, 10, 0);
    HuAudFXPlay(0x2B3);
    func_80107254_mstory5(a3->model[1]);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[8]].unk02, 0, 10, 0);
    HuPrcSleep(3);
    func_8001C814_main(a3->model[1], 1, 1);
    HuPrcSleep(10);
    func_8001C814_main(a3->model[1], 1, 0);
    HuPrcSleep(6);
    HuAudFXPlay(0x21D);
    D_801152C8_mstory5.func = func_8010E648_mstory5;
    D_801151F0_mstory5[3].func = func_8010B6F8_mstory5;
    func_8001C6A8_main(a0->model[4], 0.0f);
    Hu3DModelPosSet(a0->model[4], 180.0f, 0.0f, 480.0f);
    func_8001C258_main(a0->model[4], 4, 0);
    D_801151F0_mstory5[1].func = func_80109F48_mstory5;
    func_8001C624_main(a7->model[1], HmfModelData[a7->motion[5]].unk02, 0, 10, 2);
    D_801151F0_mstory5[7].func = func_8010D7D8_mstory5;
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    rot.x = HmfModelData[model].rot.x;
    rot.y = HmfModelData[model].rot.y;
    rot.z = HmfModelData[model].rot.z;
    scale = 1.0f;
    shadow = 3.0f;
    vel.x = -111.666664f;
    vel.y = 66.666664f;
    vel.z = -100.0f;
    i = 0.0f;
    while (TRUE) {
        pos.x += vel.x;
        pos.y += vel.y;
        pos.z += vel.z;
        vel.x *= 0.85f;
        vel.y *= 0.85f;
        vel.z *= 0.85f;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        Hu3DModelPosSet(obj->model[2], pos.x, 0.0f, pos.z);
        rot.z += 2.25f;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        Hu3DModelScaleSet(model, scale, scale, scale);
        scale = vel.z / -100.0f;
        Hu3DModelScaleSet(obj->model[2], shadow, 1.0f, shadow);
        shadow -= 0.5f;
        if (shadow < 0.0f) {
            shadow = 0.0f;
        }
        if (i >= 20.0f) {
            break;
        }
        i += 1.0f;
        HuPrcVSleep();
    }
    func_8001C258_main(model, 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    Hu3DModelPosSet(obj->model[3], HmfModelData[model].pos.x, HmfModelData[model].pos.y, HmfModelData[model].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    HuAudFXPlay(0x21E);
    while (!(D_801151F0_mstory5[4].flags & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(35);
    D_801151F0_mstory5[7].flags |= 2;
    HuPrcSleep(50);
    func_80107228_mstory5(a3, 0.0f, 0.0f, 0.0f, 10);
    func_80017954_main(a3->model[1], 2, 7, D_8011538A_mstory5[2]);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[4]].unk02, 0, 10, 0);
    func_80107254_mstory5(a3->model[1]);
    HuAudFXPlay(0x27C);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[5]].unk02, 0, 10, 2);
    HuPrcSleep(20);
    func_80107228_mstory5(a3, 0.0f, -90.0f, 0.0f, 20);
    HuPrcSleep(10);
    func_80107228_mstory5(a1, 0.0f, -30.0f, 0.0f, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A58 : 0x5B4C);
    func_80106A50_mstory5();
    func_80107228_mstory5(a1, 0.0f, 0.0f, 0.0f, 10);
    HuPrcSleep(60);
    func_80107228_mstory5(a7, 0.0f, 20.0f, 0.0f, 10);
    func_8001C624_main(D_801151F0_mstory5[7].obj->model[1], HmfModelData[D_801151F0_mstory5[7].obj->motion[2]].unk02, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A59 : 0x5B4D);
    func_80106A50_mstory5();
    func_8001C624_main(a7->model[1], HmfModelData[a7->motion[5]].unk02, 0, 10, 2);
    func_80017954_main(a3->model[1], 2, 7, D_8011538A_mstory5[0]);
    func_80107228_mstory5(a3, 0.0f, 0.0f, 0.0f, 10);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[13]].unk02, 0, 10, 0);
    func_80107254_mstory5(a3->model[1]);
    func_8001C624_main(a3->model[1], HmfModelData[a3->motion[0]].unk02, 0, 10, 2);
    func_80107228_mstory5(a3, 0.0f, 90.0f, 0.0f, 10);
    D_801151F0_mstory5[4].flags |= 2;
    D_801151F0_mstory5[4].func = STORY5_IDLE;
}

/* actor 5 */
void func_8010C4B8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[5].obj = obj;
    D_801151F0_mstory5[5].flags = 0;
    D_801151F0_mstory5[5].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0xA00F0);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801152F8_mstory5[5] = D_8011493C_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5[5].x, D_801152F8_mstory5[5].y, D_801152F8_mstory5[5].z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5[5].x, -5.0f, D_801152F8_mstory5[5].z);
    omPrcSetDestructor(0, func_8010C69C_mstory5);
    D_801151F0_mstory5[5].func = STORY5_IDLE;
    while (TRUE) {
        D_801151F0_mstory5[5].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C69C_mstory5(void) {
}

/* actor 5 walks in, then plays its motion 2 over and over once actor 0 gives cue 1 */
void func_8010C6A4_mstory5(omObjData *obj) {
    Vec pos;
    s16 model;

    model = obj->model[1];
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106FC8_mstory5(obj, 100.0f, pos.y, pos.z, 30);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 210.0f, 0.0f, 10);
    while (!(D_801151F0_mstory5[0].flags & 1)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
        func_80107254_mstory5(model);
    }
}

/* actor 6: a copy of actor 5's model */
void func_8010C85C_mstory5(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[6].obj = obj;
    D_801151F0_mstory5[6].flags = 0;
    D_801151F0_mstory5[6].unk0C = 0;
    src = D_801151F0_mstory5[5].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801152F8_mstory5[6] = D_80114948_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5[6].x, D_801152F8_mstory5[6].y, D_801152F8_mstory5[6].z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5[6].x, -5.0f, D_801152F8_mstory5[6].z);
    omPrcSetDestructor(0, func_8010CBE0_mstory5);
    D_801151F0_mstory5[6].func = STORY5_IDLE;
    while (TRUE) {
        D_801151F0_mstory5[6].func(obj);
        HuPrcVSleep();
    }
}

/* actor 6 (actor 5's motions) does the same from the other side */
void func_8010CA04_mstory5(omObjData *obj) {
    Vec pos;
    omObjData *src;
    s16 model;

    model = obj->model[1];
    src = D_801151F0_mstory5[5].obj;
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_80106FC8_mstory5(obj, -100.0f, pos.y, pos.z, 30);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 200.0f, 0.0f, 10);
    while (!(D_801151F0_mstory5[0].flags & 1)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        func_8001C624_main(model, HmfModelData[src->motion[2]].unk02, 0, 10, 2);
        func_80107254_mstory5(model);
    }
}

void func_8010CBE0_mstory5(void) {
}

/* actor 7: a big character with two pairs of eye parts hooked onto it */
void func_8010CBE8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 10, 8, -1, NULL);
    D_801151F0_mstory5[7].obj = obj;
    D_801151F0_mstory5[7].flags = 0;
    D_801151F0_mstory5[7].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA012E);
    func_8000B460_main(obj, 3, 0xA0127);
    func_8000B460_main(obj, 4, 0xA0126);
    func_8000B460_main(obj, 5, 0xA012A);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    obj->model[3] = func_8000B108_main(0x1D002E, 0x6B9);
    obj->model[4] = func_8000B108_main(0x1D002E, 0x6B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    obj->model[5] = func_8000B108_main(0xA0122, 0x2A9);
    func_8001C258_main(obj->model[5], 4, 4);
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[5]);
    func_80017358_main(obj->model[3], "c208nk0-r_eye", obj->model[5], "r_eye");
    func_80017358_main(obj->model[4], "c208nk0-r_eye", obj->model[5], "l_eye");
    obj->model[6] = func_8000B108_main(0x1D002F, 0x6B9);
    obj->model[7] = func_8000B108_main(0x1D002F, 0x6B9);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8001C258_main(obj->model[7], 4, 4);
    obj->model[8] = func_8000B108_main(0xA0122, 0x2A9);
    func_8001C258_main(obj->model[8], 4, 4);
    Hu3DModelScaleSet(obj->model[8], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[8]);
    func_80017358_main(obj->model[6], "c208nk1-r_eye", obj->model[8], "r_eye");
    func_80017358_main(obj->model[7], "c208nk1-r_eye", obj->model[8], "l_eye");
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_801152F8_mstory5[7] = D_80114954_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5[7].x, D_801152F8_mstory5[7].y, D_801152F8_mstory5[7].z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5[7].x, -5.0f, D_801152F8_mstory5[7].z);
    omPrcSetDestructor(0, func_8010D47C_mstory5);
    D_801151F0_mstory5[7].func = STORY5_IDLE;
    D_80114774_mstory5 = 1;
    while (TRUE) {
        D_801151F0_mstory5[7].func(obj);
        HuPrcVSleep();
    }
}

// story i3
/* a story-scene actor: its object and the action its process runs every frame */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10; /* looping sound effect */
    /* 0x14 */ s32 unk14; /* its handle */
} StoryActor; /* size = 0x18 */

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry), as mstory1's */
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

extern StoryActor D_801151F0_mstory5[9];
extern StoryActor D_801152C8_mstory5[2]; /* two more actors */
extern const Vec D_80114C44_mstory5;
extern const Vec D_80114C50_mstory5;
extern const Vec D_80114C5C_mstory5;
extern s16 D_80114770_mstory5;
extern s32 D_80114774_mstory5;
extern Vec D_80114778_mstory5[]; /* paths: Vec lists ended by { 9999, 9999, 9999 } */
extern Vec D_801147A8_mstory5[];
extern const s32 D_80114C78_mstory5[2];
extern const Vec D_80114960_mstory5;
extern Vec D_80115358_mstory5; /* actor 8 position */
extern s16 D_80115366_mstory5; /* effect model */
void func_800138EC_main(s16 model, u16 mask, u16 flags);
ObPath *func_80107850_mstory5(Vec *points, s16 flags);
void func_80107B54_mstory5(ObPath *path, f32 t, Vec *out);
void func_801083FC_mstory5(ObPath *path);
s32 func_80106B30_mstory5(s32 chr);
void func_80106FC8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80106FF4_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn);
void func_80107024_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107050_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn);
void func_80107080_mstory5(omObjData *obj, const Vec *to, s32 frames);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107254_mstory5(s16 model);
s32 func_801072A0_mstory5(s16 model);
void func_8010734C_mstory5(omObjData *obj, f32 speed, s16 frames);
void func_8010CFE4_mstory5(void);
void func_8010D230_mstory5(void);
void func_8010DE7C_mstory5(void);
extern Vec D_801147F0_mstory5[];
extern const Vec D_80114C84_mstory5;
void func_80106A20_mstory5(void);
void func_80106A50_mstory5(void);
void func_80106A74_mstory5(s32 mess);
void func_80106AC8_mstory5(s32 mess);
void func_80106AF4_mstory5(void);
void func_8010E3F0_mstory5(omObjData *a, omObjData *b);
void func_8010E8C0_mstory5(omObjData *obj);
void func_8010F14C_mstory5(u32 actor, s32 fx);
void func_8010F240_mstory5(u32 actor);
void *HuMemAllocTag(s32 size, s16 tag);
void HuMemFree(void *data);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
ObPath *func_8010F4D0_mstory5(Vec *points, s16 flags);
void func_8010F7D4_mstory5(ObPath *path, f32 t, Vec *out);
void func_8011007C_mstory5(ObPath *path);
/* the second scene's actors (func_801100AC_mstory5) */
extern StoryActor D_801153A0_mstory5[9];
extern Vec D_80115478_mstory5[8]; /* actor positions */
extern s16 D_801154D8_mstory5; /* shadow model, linked by every actor */
extern s16 D_801154DC_mstory5[4]; /* texture animations */
extern const Vec D_80114D20_mstory5[8]; /* actor start positions */
extern const s32 D_80114D80_mstory5[8];
extern const s32 D_80114DA0_mstory5[8];
extern const s32 D_80114DC0_mstory5[8];
extern const s32 D_80114DE0_mstory5[8];
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_801069B8_mstory5(void);
void func_80110208_mstory5(void);
void func_80110618_mstory5(void);
void func_801114E8_mstory5(void);
void func_80111DB8_mstory5(void);
void func_80112104_mstory5(void);
void func_8011275C_mstory5(void);
void func_80112F38_mstory5(void);
void func_80113470_mstory5(void);
void func_80113974_mstory5(void);
void func_80113D2C_mstory5(void);
void func_80113E58_mstory5(void);
void func_801145DC_mstory5(void);
typedef struct MsPart { /* a model part (func_8001D33C_main) */
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ char unk28[0x18];
    /* 0x40 */ Vec unk40;
} MsPart;
extern s16 D_801154DA_mstory5; /* the item effect model */
extern const Vec D_80114E00_mstory5;
extern const Vec D_80114E0C_mstory5;
extern const Vec D_80114E18_mstory5[2];
extern const Vec D_80114E30_mstory5;
extern const Vec D_80114E54_mstory5;
extern const Vec D_80114E60_mstory5;
extern const Vec D_80114E6C_mstory5;
extern const Vec D_80114E78_mstory5;
extern const Vec D_80114E84_mstory5;
extern const Vec D_80114E90_mstory5;
extern const char D_80114E9C_mstory5[]; /* "item_hook" */
extern const f64 D_80114EA8_mstory5; /* 0.8 */
extern const f64 D_80114EB0_mstory5; /* 1.0 */
void func_8001EF6C_main(s16 arg0, s16 arg1, const char *arg2);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);
void *func_8001D33C_main(s16, const char *);
void func_80105FEC_mstory5(s32 arg0);
s32 func_801068C8_mstory5(void);
void func_80106B64_mstory5(omObjData *obj, const Vec *to, s32 frames, s32 turn);
void func_80111B60_mstory5(omObjData *obj);
void func_80111C48_mstory5(omObjData *obj);
void func_8011299C_mstory5(omObjData *obj);
void func_80113B6C_mstory5(omObjData *obj);
void func_8011447C_mstory5(u32 actor, s32 fx);
void func_80114560_mstory5(u32 actor);
void func_8010E538_mstory5(omObjData *obj);
extern const Vec D_80114C90_mstory5;
extern const Vec D_80114C9C_mstory5;
extern const Vec D_80114CA8_mstory5;
extern s16 D_80115370_mstory5[]; /* texture animation numbers */
extern s16 D_80115372_mstory5;
extern s16 D_8011537A_mstory5;
extern s16 D_80115380_mstory5;
extern s16 D_80115384_mstory5;
extern s16 D_8011538A_mstory5;
void func_801068E4_mstory5(s16 model, s16 anim, s16 frame);
void func_80106B48_mstory5(omObjData *obj, const Vec *to, s32 frames);
void func_80017954_main(s16, s16, s16, s16);

/* actor 7 swaps its model 1 for model 5, which takes model 1's place */
void func_8010CFE4_mstory5(void) {
    omObjData *obj = D_801151F0_mstory5[7].obj;
    s16 m[2];

    m[0] = obj->model[1];
    m[1] = obj->model[5];
    func_8001C258_main(m[0], 4, 4);
    func_8001C258_main(m[1], 4, 0);
    HmfModelData[m[1]].pos.x = HmfModelData[m[0]].pos.x;
    HmfModelData[m[1]].pos.y = HmfModelData[m[0]].pos.y;
    HmfModelData[m[1]].pos.z = HmfModelData[m[0]].pos.z;
    HmfModelData[m[1]].rot.x = HmfModelData[m[0]].rot.x;
    HmfModelData[m[1]].rot.y = HmfModelData[m[0]].rot.y;
    HmfModelData[m[1]].rot.z = HmfModelData[m[0]].rot.z;
    HmfModelData[m[1]].scale.x = HmfModelData[m[0]].scale.x;
    HmfModelData[m[1]].scale.y = HmfModelData[m[0]].scale.y;
    HmfModelData[m[1]].scale.z = HmfModelData[m[0]].scale.z;
    obj->model[1] = m[1];
    obj->model[5] = m[0];
}

void func_8010D214_mstory5(omObjData *obj) {
    func_8010CFE4_mstory5();
}

/* the same with model 8 */
void func_8010D230_mstory5(void) {
    omObjData *obj = D_801151F0_mstory5[7].obj;
    s16 m[2];

    m[0] = obj->model[1];
    m[1] = obj->model[8];
    func_8001C258_main(m[0], 4, 4);
    func_8001C258_main(m[1], 4, 0);
    HmfModelData[m[1]].pos.x = HmfModelData[m[0]].pos.x;
    HmfModelData[m[1]].pos.y = HmfModelData[m[0]].pos.y;
    HmfModelData[m[1]].pos.z = HmfModelData[m[0]].pos.z;
    HmfModelData[m[1]].rot.x = HmfModelData[m[0]].rot.x;
    HmfModelData[m[1]].rot.y = HmfModelData[m[0]].rot.y;
    HmfModelData[m[1]].rot.z = HmfModelData[m[0]].rot.z;
    HmfModelData[m[1]].scale.x = HmfModelData[m[0]].scale.x;
    HmfModelData[m[1]].scale.y = HmfModelData[m[0]].scale.y;
    HmfModelData[m[1]].scale.z = HmfModelData[m[0]].scale.z;
    obj->model[1] = m[1];
    obj->model[8] = m[0];
}

void func_8010D460_mstory5(omObjData *obj) {
    func_8010D230_mstory5();
}

void func_8010D47C_mstory5(void) {
}

/* actor 7 turns, walks 1000 units off along x and hides its models */
#ifdef NON_MATCHING
void func_8010D484_mstory5(omObjData *arg0) {
    omObjData *obj = D_801151F0_mstory5[7].obj;
    Vec pos;
    HmfModel *m;

    m = &HmfModelData[obj->model[1]];
    pos.x = m->pos.x;
    pos.y = m->pos.y;
    pos.z = m->pos.z;
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801152C8_mstory5[1].func = (void (*)(omObjData *))func_801085D8_mstory5;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D484_mstory5);
#endif

void func_8010D560_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114C44_mstory5, 20);
    D_801151F0_mstory5[7].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

/* actors 0, 1 and 7 turn and slide left together for 20 frames */
void func_8010D594_mstory5(omObjData *arg0) {
    omObjData *objs[4];
    f32 dist[4];
    f32 speed[3];
    s32 frames = 20;
    s32 i;
    s32 j;

    dist[0] = 150.0f;
    dist[1] = 350.0f;
    dist[2] = 400.0f;
    speed[0] = dist[0] / frames;
    speed[1] = dist[1] / frames;
    speed[2] = dist[2] / frames;

    objs[0] = D_801151F0_mstory5[0].obj;
    objs[1] = D_801151F0_mstory5[1].obj;
    objs[2] = D_801151F0_mstory5[7].obj;
    objs[3] = D_801151F0_mstory5[3].obj;
    func_80107228_mstory5(objs[0], 0.0f, 90.0f, 0.0f, 10);
    func_80107228_mstory5(objs[1], 0.0f, 90.0f, 0.0f, 10);
    func_80107228_mstory5(objs[2], 0.0f, 90.0f, 0.0f, 10);
    func_8001C624_main(objs[0]->model[1], HmfModelData[objs[0]->motion[3]].unk02, 0, 10, 2);
    for (j = 0; j < frames; j++) {
        for (i = 0; i < 3; i++) {
            HmfModelData[objs[i]->model[1]].pos.x -= speed[i];
            HmfModelData[objs[i]->model[2]].pos.x -= speed[i];
        }
        HuPrcVSleep();
    }
    func_8001C624_main(objs[0]->model[1], HmfModelData[objs[0]->motion[0]].unk02, 0, 10, 2);
    D_801151F0_mstory5[7].unk08 |= 1;
    D_801151F0_mstory5[7].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

/* actors 0, 7 and 1 turn a quarter, wait for actor 7's flag 2, then turn back */
void func_8010D7D8_mstory5(omObjData *arg0) {
    omObjData *objs[3];
    Vec a;
    Vec b;
    s32 frames;
    s32 i;
    s32 j;

    a = D_80114C50_mstory5;
    b = D_80114C5C_mstory5;
    frames = 20;
    objs[0] = D_801151F0_mstory5[0].obj;
    objs[1] = D_801151F0_mstory5[7].obj;
    objs[2] = D_801151F0_mstory5[1].obj;
    func_8001C624_main(objs[0]->model[1], HmfModelData[objs[0]->motion[3]].unk02, 0, 10, 2);
    for (j = 0; j < frames; j++) {
        for (i = 0; i < 3; i++) {
            HmfModelData[objs[i]->model[1]].rot.y += 90.0f / frames;
        }
        HuPrcVSleep();
    }
    func_8001C624_main(objs[0]->model[1], HmfModelData[objs[0]->motion[0]].unk02, 0, 10, 2);
    while (!(D_801151F0_mstory5[7].unk08 & 2)) {
        HuPrcVSleep();
    }
    func_8001C624_main(objs[0]->model[1], HmfModelData[objs[0]->motion[3]].unk02, 0, 10, 2);
    frames = 20;
    for (j = 0; j < frames; j++) {
        for (i = 0; i < 3; i++) {
            HmfModelData[objs[i]->model[1]].rot.y -= (&a.x)[i] / frames;
            HmfModelData[objs[i]->model[1]].rot.x += (&b.x)[i] / frames;
        }
        HuPrcVSleep();
    }
    func_8001C624_main(objs[0]->model[1], HmfModelData[objs[0]->motion[0]].unk02, 0, 10, 2);
    D_801151F0_mstory5[7].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

void func_8010DADC_mstory5(omObjData *obj) {
    HuPrcSleep(60);
    func_80107228_mstory5(obj, 0.0f, 30.0f, 0.0f, 50);
    D_801151F0_mstory5[7].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

/* actor 7 bobs up and down (a process; never ends while D_80114774_mstory5 is set) */
#ifdef NON_MATCHING
void func_8010DB30_mstory5(void) {
    omObjData *obj;
    Vec pos;
    f32 t;
    f32 y;
    u16 model;
    HmfModel *m;
    s16 *mdl;

    t = 0.0f;
    if (D_80114774_mstory5 != 0) {
        obj = D_801151F0_mstory5[7].obj;
        pos.y = HmfModelData[obj->model[1]].pos.y;
        while (TRUE) {
            mdl = obj->model;
            model = mdl[1];
            m = &HmfModelData[mdl[1]];
            pos.x = m->pos.x;
            pos.z = m->pos.z;
            y = sindf(t) * 25.0f + 25.0f;
            t += 2.0f;
            t = (t >= 360.0f) ? t - 360.0f : t;
            if (D_80114770_mstory5 != 1) {
                Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
            }
            HuPrcVSleep();
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DB30_mstory5);
#endif

/* actor 8: two models, an effect model below it; runs its action every frame */
void func_8010DC78_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801151F0_mstory5[8].obj = obj;
    D_801151F0_mstory5[8].unk08 = 0;
    D_801151F0_mstory5[8].unk0C = 0;
    obj->model[1] = func_8000B108_main(D_80114C78_mstory5[0], 0x20299);
    obj->model[2] = func_8000B108_main(D_80114C78_mstory5[1], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C814_main(obj->model[2], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115358_mstory5 = D_80114960_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115358_mstory5.x, D_80115358_mstory5.y, D_80115358_mstory5.z);
    D_80115366_mstory5 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80115366_mstory5, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_80115366_mstory5, 60.0f);
    func_800138EC_main(D_80115366_mstory5, 1, 0);
    func_8001C258_main(D_80115366_mstory5, 4, 4);
    omPrcSetDestructor(0, func_8010DE7C_mstory5);
    D_801151F0_mstory5[8].func = (void (*)(omObjData *))func_801085D8_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[8].func(obj);
        HuPrcVSleep();
    }
}

void func_8010DE7C_mstory5(void) {
}

/* actor 8's flight: along the first path, then (after actor 7 reacts) spinning along the second */
void func_8010DE84_mstory5(omObjData *obj) {
    Vec pos;
    ObPath *path[2];
    omObjData *other;
    s32 i;
    f32 t;
    f32 rot;

    path[0] = func_80107850_mstory5(D_80114778_mstory5, 0);
    path[1] = func_80107850_mstory5(D_801147A8_mstory5, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_80115366_mstory5, 4, 0);
    func_800138EC_main(D_80115366_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    i = 0;
    do {
        t = i * 0.02f;
        func_80107B54_mstory5(path[0], t * t, &pos);
        i++;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 50);
    HuPrcSleep(40);
    other = D_801151F0_mstory5[7].obj;
    func_8001C624_main(other->model[1], HmfModelData[other->motion[3]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_801151F0_mstory5[8].unk08 |= 2;
    HuAudFXPlay(0x218);
    func_8001C624_main(other->model[1], HmfModelData[other->motion[0]].unk02, 0, 10, 2);
    rot = 0.0f;
    i = 0;
    do {
        t = i * (1.0f / 120.0f);
        func_80107B54_mstory5(path[1], t * t, &pos);
        rot -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        i++;
        Hu3DModelRotSet(obj->model[1], 0.0f, rot, 0.0f);
        func_8000CFA4_main(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 120);
    func_8001C258_main(obj->model[1], 4, 4);
    func_800138EC_main(D_80115366_mstory5, 1, 0);
    HuAudFXPlay(0x21A);
    func_801083FC_mstory5(path[0]);
    func_801083FC_mstory5(path[1]);
    D_801151F0_mstory5[8].unk08 = 1;
    D_801151F0_mstory5[8].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

/* actor 8 comes down its path, waits for flag 0x10, and goes back up */
void func_8010E1A0_mstory5(omObjData *obj) {
    Vec pos;
    ObPath *path;
    s32 i;
    f32 t;

    path = func_80107850_mstory5(D_801147F0_mstory5, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_800138EC_main(D_80115366_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    i = 0;
    do {
        t = i * 0.02f;
        func_80107B54_mstory5(path, t * t, &pos);
        pos.x += -100.0f;
        i++;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 50);
    while (!(D_801151F0_mstory5[8].unk08 & 0x10)) {
        HuPrcVSleep();
    }
    i = 0;
    do {
        t = 1.0f - i * 0.02f;
        func_80107B54_mstory5(path, t * t, &pos);
        pos.x += -100.0f;
        i++;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 50);
    func_8001C258_main(obj->model[2], 4, 4);
    func_800138EC_main(D_80115366_mstory5, 1, 0);
    func_801083FC_mstory5(path);
    D_801151F0_mstory5[8].unk08 = 8;
    D_801151F0_mstory5[8].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

/* turns a's model to face b's */
void func_8010E3F0_mstory5(omObjData *a, omObjData *b) {
    s16 models[2];
    Vec pos[2];
    Vec rot;
    Vec d;
    s32 i;

    models[0] = a->model[1];
    models[1] = b->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = HmfModelData[models[i]].pos.x;
        pos[i].y = HmfModelData[models[i]].pos.y;
        pos[i].z = HmfModelData[models[i]].pos.z;
    }
    rot.x = HmfModelData[models[0]].rot.x;
    rot.y = HmfModelData[models[0]].rot.y;
    rot.z = HmfModelData[models[0]].rot.z;
    d.x = pos[1].x - pos[0].x;
    d.y = pos[1].y - pos[0].y;
    d.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(d.z, d.x) - 90.0f);
    Hu3DModelRotSet(models[0], rot.x, rot.y, rot.z);
}

void func_8010E538_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[3].obj);
}

/* actor 9: an object with no models */
void func_8010E558_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_801152C8_mstory5[0].obj = obj;
    D_801152C8_mstory5[0].unk08 = 0;
    D_801152C8_mstory5[0].unk0C = 0;
    D_801152C8_mstory5[0].func = (void (*)(omObjData *))func_801085D8_mstory5;
    while (TRUE) {
        D_801152C8_mstory5[0].func(obj);
        HuPrcVSleep();
    }
}

/* actor 10: the same */
void func_8010E5D0_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_801152C8_mstory5[1].obj = obj;
    D_801152C8_mstory5[1].unk08 = 0;
    D_801152C8_mstory5[1].unk0C = 0;
    D_801152C8_mstory5[1].func = (void (*)(omObjData *))func_801085D8_mstory5;
    while (TRUE) {
        D_801152C8_mstory5[1].func(obj);
        HuPrcVSleep();
    }
}

/* a message (which one depends on func_80106B30_mstory5(0)); then flags actor 4 */
void func_8010E648_mstory5(omObjData *obj) {
    func_80106A20_mstory5();
    if (func_80106B30_mstory5(0) == 0) {
        func_80106AC8_mstory5(0x5A56);
    } else {
        func_80106AC8_mstory5(0x5B4A);
    }
    func_80106AF4_mstory5();
    func_80106A50_mstory5();
    D_801151F0_mstory5[4].unk08 |= 0x10;
    D_801152C8_mstory5[0].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

/* actor 3 turns to actor 0, plays motion 1 and walks off with its sound */
void func_8010E6B4_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[0].obj);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 30, 2);
    func_8010F14C_mstory5(3, 0x1F);
    func_8010734C_mstory5(obj, 4.5f, 15);
    func_8010F240_mstory5(3);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
    D_801151F0_mstory5[3].func = (void (*)(omObjData *))func_801085D8_mstory5;
    D_801152C8_mstory5[1].func = func_8010E8C0_mstory5;
}

/* lowers obj's model to y = 100 */
void func_8010E7B0_mstory5(omObjData *obj) {
    while (TRUE) {
        if (HmfModelData[obj->model[1]].pos.y > 100.0f) {
            HmfModelData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    HmfModelData[obj->model[1]].pos.y = 100.0f;
    D_801151F0_mstory5[1].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

void func_8010E870_mstory5(omObjData *obj) {
    Vec rot;

    rot = D_80114C84_mstory5;
    func_80107080_mstory5(obj, &rot, 10);
    D_801151F0_mstory5[7].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

/* actor 0 turns to actor 3 and walks to it; both play their reactions */
void func_8010E8C0_mstory5(omObjData *arg0) {
    omObjData *obj = D_801151F0_mstory5[0].obj;

    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[3].obj);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[3]].unk02, 0, 30, 2);
    func_8010F14C_mstory5(0, 0x1F);
    func_8010734C_mstory5(obj, 3.5f, 15);
    func_8010F240_mstory5(0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115384_mstory5);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[11]].unk02, 0, 30, 2);
    func_80017954_main(D_801151F0_mstory5[3].obj->model[1], 2, 7, D_8011538A_mstory5);
    func_8001C624_main(D_801151F0_mstory5[3].obj->model[1], HmfModelData[D_801151F0_mstory5[3].obj->motion[11]].unk02, 0, 30, 2);
    D_801152C8_mstory5[1].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

/* obj hops 13 frames, then turns */
void func_8010EA34_mstory5(omObjData *obj) {
    s16 model;
    Vec pos;
    Vec rot;
    s16 i;
    f32 y;

    i = 0;
    model = obj->model[1];
    rot = D_80114C90_mstory5;
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_801068E4_mstory5(model, D_80115380_mstory5, D_8011537A_mstory5);
    i = 0;
    do {
        y = sindf(i * 12.000001f) * 80.0f;
        HmfModelData[model].pos.y = y + pos.y;
        HuPrcVSleep();
        i++;
    } while (i < 13);
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &rot, 5);
    func_801068E4_mstory5(model, D_80115380_mstory5, D_80115372_mstory5);
    D_801151F0_mstory5[1].unk08 |= 2;
    D_801151F0_mstory5[1].func = func_8010E538_mstory5;
}

/* actor 0 brings out model 4 and steps toward the camera */
void func_8010EBCC_mstory5(omObjData *arg0) {
    Vec rot;
    Vec to;
    omObjData *obj;

    rot = D_80114C9C_mstory5;
    obj = D_801151F0_mstory5[0].obj;
    to.x = HmfModelData[obj->model[1]].pos.x - 5.0f;
    to.y = HmfModelData[obj->model[1]].pos.y;
    to.z = 500.0f;
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, HmfModelData[obj->model[1]].pos.z);
    func_8001C6A8_main(obj->model[4], 0.0f);
    func_8001C258_main(obj->model[4], 4, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115370_mstory5[12]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[4]].unk02, 0, 30, 0);
    func_80106B48_mstory5(obj, &to, 10);
    func_80107254_mstory5(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115370_mstory5[9]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
    func_80107080_mstory5(obj, &rot, 10);
    D_801152C8_mstory5[1].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

/* actor 3 brings out model 3 and steps toward the camera */
void func_8010EDFC_mstory5(omObjData *obj) {
    Vec rot;
    Vec to;
    Vec pos;

    rot = D_80114CA8_mstory5;
    pos.x = HmfModelData[obj->model[1]].pos.x + 5.0f;
    pos.y = HmfModelData[obj->model[1]].pos.y;
    pos.z = 500.0f;
    to = pos;
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, HmfModelData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    func_80017954_main(obj->model[1], 2, 7, D_80115370_mstory5[16]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[14]].unk02, 0, 30, 0);
    func_80106B48_mstory5(obj, &to, 10);
    func_80107254_mstory5(obj->model[1]);
    func_80017954_main(obj->model[1], 2, 7, D_80115370_mstory5[13]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
    func_80107080_mstory5(obj, &rot, 10);
    D_801151F0_mstory5[3].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

void func_8010F02C_mstory5(omObjData *arg0) {
    omObjData *obj = D_801151F0_mstory5[0].obj;

    func_80107228_mstory5(obj, 0.0f, 0.0f, 0.0f, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[8]].unk02, 0, 10, 0);
    D_801152C8_mstory5[1].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

void func_8010F0B8_mstory5(omObjData *arg0) {
    omObjData *obj = D_801151F0_mstory5[3].obj;

    func_80107228_mstory5(obj, 0.0f, 0.0f, 0.0f, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[13]].unk02, 0, 10, 0);
    D_801151F0_mstory5[3].func = (void (*)(omObjData *))func_801085D8_mstory5;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C44_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C50_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C5C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114CA8_mstory5);

/* starts actor's looping sound effect (replayed by func_8010F2BC_mstory5 each motion loop) */
void func_8010F14C_mstory5(u32 actor, s32 fx) {
    if (D_801151F0_mstory5[actor].unk0C == 0) {
        D_801151F0_mstory5[actor].unk0C = 1;
        D_801151F0_mstory5[actor].unk10 = fx;
        switch (actor) {
        case 0:
            D_801151F0_mstory5[actor].unk14 = CharFXPlay(fx, GwStory.unk1);
            break;
        case 2:
            if (func_80106B30_mstory5(0) == 0) {
                D_801151F0_mstory5[actor].unk14 = CharFXPlay(fx, 0);
            } else {
                D_801151F0_mstory5[actor].unk14 = CharFXPlay(fx, 1);
            }
            break;
        case 3:
            D_801151F0_mstory5[actor].unk14 = CharFXPlay(fx, 7);
            break;
        case 1:
        case 4:
        case 5:
        case 6:
            break;
        }
    }
}

void func_8010F240_mstory5(u32 actor) {
    if (D_801151F0_mstory5[actor].unk0C == 1) {
        D_801151F0_mstory5[actor].unk0C = 0;
        switch (actor) {
        case 0:
        case 2:
        case 3:
            HuAudFXStop((s16)D_801151F0_mstory5[actor].unk14);
            break;
        case 1:
        case 4:
        case 5:
        case 6:
            break;
        }
    }
}

/* replays each actor's looping sound effect when its motion starts over */
void func_8010F2BC_mstory5(void) {
    s32 i;
    s32 fx;

    while (TRUE) {
        for (i = 0; i < 9; i++) {
            if (D_801151F0_mstory5[i].unk0C == 1 && HmfModelData[D_801151F0_mstory5[i].obj->model[1]].unk40 == 0.0f) {
                fx = D_801151F0_mstory5[i].unk10;
                switch ((u32)i) {
                case 0:
                    D_801151F0_mstory5[i].unk14 = CharFXPlay(fx, GwStory.unk1);
                    break;
                case 2:
                    if (func_80106B30_mstory5(0) == 0) {
                        D_801151F0_mstory5[i].unk14 = CharFXPlay(fx, 0);
                    } else {
                        D_801151F0_mstory5[i].unk14 = CharFXPlay(fx, 1);
                    }
                    break;
                case 3:
                    D_801151F0_mstory5[i].unk14 = CharFXPlay(fx, 7);
                    break;
                case 1:
                case 4:
                case 5:
                case 6:
                    break;
                }
            }
        }
        HuPrcVSleep();
    }
}

/* while actor 3's sound plays, pans it across over 180 frames.
   Matches (masked 0), but retail pads .text to 16 after it with a nop: a source file ends here.
   The asm (which carries the nop) stays until the unit is split at func_8010F4D0_mstory5. */
#ifdef NON_MATCHING
void func_8010F41C_mstory5(omObjData *obj) {
    f32 pan;
    f32 step;
    s32 i;

    step = 0.35f;
    pan = 0.0f;
    if (D_801151F0_mstory5[3].unk0C == 1) {
        i = 0;
        do {
            func_8004AAD0_main(D_801151F0_mstory5[3].unk14, (s32)pan + 64);
            pan += step;
            HuPrcVSleep();
            i++;
        } while (i < 180);
        func_8004AAD0_main(D_801151F0_mstory5[3].unk14, 127);
    }
    D_801152C8_mstory5[1].func = (void (*)(omObjData *))func_801085D8_mstory5;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F41C_mstory5);
#endif

/* retail .rodata padding to 16 bytes after func_8010F2BC_mstory5's jump table: the source file ends here
   (the next one starts at func_8010F4D0_mstory5); drop it when the unit is split */
const s32 D_80114D14_mstory5[3] = { 0, 0, 0 };

ObPath *func_8010F4D0_mstory5(Vec *points, s16 flags) {
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
void func_8010F7D4_mstory5(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F7D4_mstory5);
#endif

void func_8011007C_mstory5(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* chapter 5, second scene: the actors' processes */
void func_801100AC_mstory5(void) {
    func_801069B8_mstory5();
    D_801154D8_mstory5 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80110208_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_801114E8_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80111DB8_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_8011275C_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112F38_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113470_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113974_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113D2C_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113E58_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_80112104_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_801145DC_mstory5, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_801154D8_mstory5, 4, 4);
}

void func_80110200_mstory5(void) {
}

// masked 0 when func_80017AD8_main returns s16 (functions.us.h says u8), as mstory1's func_801081E0
#ifdef NON_MATCHING
/* actor 0: the player's character */
void func_80110208_mstory5(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 6, 0x10, -1, NULL);
    D_801153A0_mstory5[0].obj = obj;
    D_801153A0_mstory5[0].unk08 = 0;
    D_801153A0_mstory5[0].unk0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x9C));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 5, D_80114D80_mstory5[chr]);
    func_8000B460_main(obj, 6, D_80114DA0_mstory5[chr]);
    func_8000B460_main(obj, 7, D_80114DC0_mstory5[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_80114DE0_mstory5[chr]);
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x9B));
    D_801154DC_mstory5[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_801154DC_mstory5[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_801154DC_mstory5[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_801154DC_mstory5[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_80115478_mstory5[0] = D_80114D20_mstory5[0];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[0].x, D_80115478_mstory5[0].y, D_80115478_mstory5[0].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[0].x, -5.0f, D_80115478_mstory5[0].z);
    Hu3DModelPosSet(obj->model[4], D_80115478_mstory5[0].x, D_80115478_mstory5[0].y, D_80115478_mstory5[0].z);
    omPrcSetDestructor(0, func_80110618_mstory5);
    D_801153A0_mstory5[0].func = (void (*)(omObjData *))func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[0].func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80110208_mstory5);
#endif

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

const Vec D_80114E3C_mstory5 = { 230.0f, 0.0f, 480.0f };
const Vec D_80114E48_mstory5 = { 680.0f, 0.0f, 480.0f };

/* actor 0 (the player): uses its item on actor 7, then the scene with actors 1, 3 and 6 */
void func_80110620_mstory5(omObjData *obj) {
    MsPart *part;
    s32 sfx;
    omObjData *other;
    s32 i;
    f32 scale;
    f32 frame;
    s16 model;

    HuPrcSleep(20);
    model = obj->model[1];
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 110.0f, 0.0f, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], model, D_80114E9C_mstory5);
    func_8001C258_main(obj->model[3], 4, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    while (!(D_801153A0_mstory5[7].unk08 & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_801153A0_mstory5[7].obj->model[1], 4, 4);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x45);
    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x46);
    func_8002FD8C_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x47);
    part = func_8001D33C_main(model, D_80114E9C_mstory5);
    i = 0;
    do {
        scale = sindf(i * 18.0f) * D_80114EA8_mstory5 + D_80114EB0_mstory5;
        part->unk1C.x = scale;
        part->unk1C.y = scale;
        part->unk1C.z = scale;
        part->unk40.x = scale;
        part->unk40.y = scale;
        part->unk40.z = scale;
        HuPrcVSleep();
        i++;
    } while (i < 10);
    func_8002FDCC_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x47);
    func_8002FDCC_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x46);
    func_8002FDCC_main(model, HmfModelData[model].unk02, D_80114E9C_mstory5, 0x1B, 0x45);
    func_80105FEC_mstory5(3);
    while (func_801068C8_mstory5() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3E : 0x5B31);
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
    func_80107080_mstory5(obj, &D_80114E00_mstory5, 10);
    HuAudSeqPlay(0x72);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[2]);
    func_80107254_mstory5(model);
    sfx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    other = D_801153A0_mstory5[6].obj;
    func_80107080_mstory5(other, &D_80114E90_mstory5, 3);
    func_80106B48_mstory5(other, &D_80114E60_mstory5, 5);
    func_80107080_mstory5(other, &D_80114E78_mstory5, 3);
    D_801153A0_mstory5[1].func = func_80111C48_mstory5;
    HuAudFXPlay(0x219);
    HuAudFXStop(sfx);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[3]);
    func_80107080_mstory5(other, &D_80114E84_mstory5, 3);
    func_80106B64_mstory5(other, &D_80114E6C_mstory5, 10, 0);
    func_80107254_mstory5(model);
    HuAudSeqPlay(0x26);
    func_80107080_mstory5(obj, &D_80114E0C_mstory5, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[0]);
    HuAudFXPlay(0x159);
    func_8001C624_main(D_801153A0_mstory5[6].obj->model[1], HmfModelData[D_801153A0_mstory5[6].obj->motion[1]].unk02, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3F : 0x5B32);
    func_80106A50_mstory5();
    func_8001C624_main(D_801153A0_mstory5[6].obj->model[1], HmfModelData[D_801153A0_mstory5[6].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(model, HmfModelData[obj->motion[8]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    D_801153A0_mstory5[3].func = func_8011299C_mstory5;
    D_801153A0_mstory5[6].func = func_80113B6C_mstory5;
    D_801153A0_mstory5[1].func = func_80111B60_mstory5;
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    func_8011447C_mstory5(0, 0x1F);
    func_80107080_mstory5(obj, &D_80114E18_mstory5[0], 20);
    func_80106B48_mstory5(obj, &D_80114E3C_mstory5, 20);
    func_80114560_mstory5(0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].unk08 & 2)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    func_8011447C_mstory5(0, 0x1F);
    func_80106B64_mstory5(obj, &D_80114E54_mstory5, 30, 0);
    func_80114560_mstory5(0);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    for (i = 0; i < 2; i++) {
        func_8001C624_main(model, HmfModelData[obj->motion[9]].unk02, 0, 5, 0);
        func_8001C92C_main(model, 5.0f);
        func_80107254_mstory5(model);
        func_8001C5B4_main(model, obj->motion[9]);
        func_8001C814_main(model, 4, 4);
        func_8001C814_main(model, 2, 0);
        func_8001C92C_main(model, 5.0f);
        func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
        while (HmfModelData[model].unk40 > 0.0f) {
            HuPrcVSleep();
        }
        func_8001C814_main(model, 4, 0);
    }
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8001C92C_main(model, 1.0f);
    while (!(D_801153A0_mstory5[3].unk08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80114E30_mstory5, 40);
    while (!(D_801153A0_mstory5[3].unk08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80114E18_mstory5[0], 15);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 2);
    func_8011447C_mstory5(0, 0x1F);
    func_80106B48_mstory5(obj, &D_80114E48_mstory5, 30);
    func_80114560_mstory5(0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[0].func = (void (*)(omObjData *))func_80110200_mstory5;
}

// story i4: structs, data and prototypes for func_801113BC_mstory5..func_801145DC_mstory5
/* a story-scene actor: its object and the action its process runs every frame */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 flags; /* cues the scripts give each other */
    /* 0x0C */ s32 sfxOn; /* a looping sound effect is playing */
    /* 0x10 */ s32 sfxId;
    /* 0x14 */ s32 sfxNo; /* its handle */
} StoryActor; /* size = 0x18 */

typedef struct StoryTexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} StoryTexAnimSlot; /* size = 0xC */

extern StoryTexAnimSlot *D_800D1714_main;
extern StoryActor D_801153A0_mstory5[8];
extern StoryActor D_80115460_mstory5; /* the effect object (func_80112104_mstory5) */
extern Vec D_80115478_mstory5[8]; /* actor positions */
extern s16 D_801154D8_mstory5; /* shadow model, linked by every actor */
extern s16 D_801154DA_mstory5; /* effect model */
extern s32 D_801154E4_mstory5[3]; /* texture animations */
extern s16 D_801154F0_mstory5;
/* a puff of the effect object (func_80112104_mstory5): time < 0 is idle; it grows and drifts for 40 frames */
typedef struct StoryPuff {
    /* 0x00 */ f32 time;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec vel;
} StoryPuff; /* size = 0x1C */
extern StoryPuff D_801154F8_mstory5[16];
extern s32 D_80114820_mstory5;

/* a sprite-model slot (D_800CBB60_main entry; src/14EA0.c unk_800ECDE0) */
typedef struct StorySprModel {
    /* 0x00 */ s16 model;
    /* 0x02 */ char unk_02[0x22];
} StorySprModel; /* size = 0x24 */
extern StorySprModel *D_800CBB60_main;
u16 func_80014618_main(s16 index, u16 arg1);
void func_80014794_main(s16 index, u8 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);
extern const Vec D_80114D20_mstory5[8]; /* actor start positions */

void func_80032FC0_main(s16, u8, u8);
void func_80032FF8_main(s32, u8);
s16 func_80032694_main(HmfData *, u16, s32, char *);
s16 func_800329B4_main(void *);
s32 HmfAnimCreate(HmfData *, void *, s32, char *);
void HuMemMemoryFreePerm(void *ptr);

void func_80105FDC_mstory5(void);
void func_801068E4_mstory5(s16 model, s16 anim, s16 frame);
void func_80106A20_mstory5(void);
void func_80106A50_mstory5(void);
void func_80106A74_mstory5(s32 mess);
s32 func_80106B30_mstory5(s32 chr);
void func_80106B48_mstory5(omObjData *obj, Vec *to, s32 frames);
void func_80106B64_mstory5(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80107080_mstory5(omObjData *obj, Vec *to, s32 frames);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107254_mstory5(s16 model);
/* func_80110200_mstory5 (the idle action) is defined void(void) above: cast where it is stored */
void func_80110620_mstory5(omObjData *obj);
void func_80111480_mstory5(omObjData *obj);
void func_80111818_mstory5(void);
void func_80111820_mstory5(omObjData *obj);
void func_80111FE0_mstory5(void);
void func_80111FE8_mstory5(omObjData *obj);
void func_80113CF8_mstory5(omObjData *obj);
void func_80114018_mstory5(omObjData *obj);
extern const Vec D_80114EB8_mstory5;
extern const Vec D_80114EC4_mstory5;
extern const Vec D_80114EDC_mstory5;
extern const Vec D_80114EF4_mstory5;
extern const Vec D_80114F0C_mstory5;
extern const Vec D_80114F18_mstory5;
extern const Vec D_80114F24_mstory5;
extern const Vec D_80114F30_mstory5;
extern const Vec D_80114F3C_mstory5;
extern const Vec D_80114F48_mstory5;
extern const Vec D_80114F60_mstory5;
extern const Vec D_80114F6C_mstory5;
extern const Vec D_80114F78_mstory5;
extern const Vec D_80114F84_mstory5;
extern const Vec D_80114F90_mstory5;
extern const Vec D_80114F9C_mstory5;
void func_801113BC_mstory5(omObjData *obj);
void func_80112514_mstory5(omObjData *obj);
void func_80113138_mstory5(omObjData *obj);
void func_80113618_mstory5(omObjData *obj);
void func_8011396C_mstory5(void);
void func_80112994_mstory5(void);
void func_80113130_mstory5(void);
void func_80113B64_mstory5(void);
void func_80114010_mstory5(void);
extern s32 D_80114824_mstory5; /* 1 once actor 6 exists: actor 6 bobs */
extern Vec D_80114828_mstory5[];
extern Vec D_80114858_mstory5[];
extern const s32 D_8011514C_mstory5[];
extern const Vec D_80115134_mstory5;
extern const Vec D_80114FC0_mstory5;
extern const Vec D_80114FD8_mstory5;
extern const Vec D_80114FE4_mstory5;
extern const Vec D_80114FF0_mstory5;
extern const Vec D_80115014_mstory5;
extern const Vec D_80115020_mstory5;
extern const Vec D_8011502C_mstory5;
extern const Vec D_80115038_mstory5;
extern const Vec D_80115050_mstory5;
extern const Vec D_80115068_mstory5;
extern const Vec D_80115074_mstory5;
extern const Vec D_80115080_mstory5;
extern const Vec D_80115098_mstory5;
extern const Vec D_801150B0_mstory5;
extern const Vec D_801150BC_mstory5;
extern const Vec D_801150E0_mstory5;
extern const Vec D_801150EC_mstory5;
extern const Vec D_801150F8_mstory5;
extern const Vec D_80115110_mstory5;
extern const Vec D_8011511C_mstory5;
extern const Vec D_80115128_mstory5;
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_800461B4_main(s16 arg0);
void func_8000CD00_main(s16, f32, f32, f32);
s16 func_8000CED8_main(s32, s32);
void func_8000CFA4_main(s16, f32, f32, f32);
void func_8000D018_main(s16, f32);

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i runs
   from points[i] to points[i + 1] and covers [segs[i].start, segs[i].end] of the path's
   length (0..1). flags & 1: closed. Same as mstory1's and opboard's. */
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

ObPath *func_8010F4D0_mstory5(Vec *points, s16 flags);
void func_8010F7D4_mstory5(ObPath *path, f32 t, Vec *out);
void func_8011007C_mstory5(ObPath *path);

// story i4: .data (0x80114730-0x801148A0); retail pads two file ends to 16 bytes
// (0x80114770 and 0x80114820 start new files).
u32 D_80114730_mstory5 = 0; /* main object state */
s32 D_80114734_mstory5 = 0;
s8 D_80114738_mstory5 = 0;
Vec D_8011473C_mstory5 = { 14.0f, 193.0f, 1400.0f }; /* camera position */
Vec D_80114748_mstory5 = { -25.0f, 0.0f, -650.0f }; /* camera target */
Vec D_80114754_mstory5 = { 0.0f, 1.0f, -0.0001f }; /* camera up */
s32 D_80114760_mstory5 = 0;
u8 D_80114764_mstory5[12] = { 0 }; /* file end padding */
s16 D_80114770_mstory5 = 0;
s32 D_80114774_mstory5 = 0;
/* paths: Vec lists ended by { 9999, 9999, 9999 } */
Vec D_80114778_mstory5[] = {
    { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f },
};
Vec D_801147A8_mstory5[] = {
    { -100.0f, 300.0f, 300.0f }, { -200.0f, 200.0f, 100.0f }, { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f },  { -50.0f, 120.0f, 450.0f },  { 9999.0f, 9999.0f, 9999.0f },
};
Vec D_801147F0_mstory5[] = {
    { 100.0f, 200.0f, 100.0f }, { -100.0f, 100.0f, -100.0f }, { 0.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f },
};
s32 D_80114820_mstory5 = 3;
s32 D_80114824_mstory5 = 0;
Vec D_80114828_mstory5[] = {
    { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f },
};
Vec D_80114858_mstory5[] = {
    { -100.0f, 300.0f, 300.0f }, { -200.0f, 200.0f, 100.0f }, { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f },  { -50.0f, 120.0f, 450.0f },  { 9999.0f, 9999.0f, 9999.0f },
};

void func_801113BC_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C624_main(model, HmfModelData[obj->motion[9]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    HuPrcSleep(80);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801153A0_mstory5[0].func = (void (*)(omObjData *))func_80110200_mstory5;
}

void func_80111480_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80114EB8_mstory5, 10);
    D_801153A0_mstory5[0].func = (void (*)(omObjData *))func_80110200_mstory5;
}

void func_801114B4_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80114EC4_mstory5, 10);
    D_801153A0_mstory5[0].func = (void (*)(omObjData *))func_80110200_mstory5;
}

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

void func_801114E8_mstory5(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[1].obj = obj;
    D_801153A0_mstory5[1].flags = 0;
    D_801153A0_mstory5[1].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80115478_mstory5[1] = D_80114D20_mstory5[1];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[1].x, D_80115478_mstory5[1].y, D_80115478_mstory5[1].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[1].x, -5.0f, D_80115478_mstory5[1].z);
    data = DataRead(0xA007E);
    D_801154E4_mstory5[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main((s16)D_801154E4_mstory5[0], 1, 0);
    func_80032FF8_main((s16)D_801154E4_mstory5[0], 0);
    D_801154F0_mstory5 = func_80032694_main(HmfModelData[obj->model[1]].hmf, (s16)D_801154E4_mstory5[0], 0, "c204n_0_DEF");
    D_801154E4_mstory5[0] = D_800D1714_main[D_801154E4_mstory5[0]].unk_00;
    data = DataRead(0xA0080);
    D_801154E4_mstory5[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_801154E4_mstory5[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, (s16)D_801154E4_mstory5[0]);
    omPrcSetDestructor(0, func_80111818_mstory5);
    D_801153A0_mstory5[1].func = (void (*)(omObjData *))func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80111818_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EDC_mstory5);

const Vec D_80114EE8_mstory5 = { 10.0f, 378.9f, 0.0f };

void func_80111820_mstory5(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    D_801153A0_mstory5[0].func = func_801113BC_mstory5;
    D_801153A0_mstory5[6].func = func_80113CF8_mstory5;
    func_80107080_mstory5(obj, (Vec *)&D_80114EE8_mstory5, 30);
    func_80106B48_mstory5(obj, (Vec *)&D_80114F48_mstory5, 20);
    HuPrcSleep(30);
    func_80107080_mstory5(obj, (Vec *)&D_80114F18_mstory5, 10);
    func_80106B48_mstory5(obj, (Vec *)&D_80114F3C_mstory5, 15);
    D_801153A0_mstory5[0].func = func_80111480_mstory5;
    func_80107080_mstory5(obj, (Vec *)&D_80114EF4_mstory5, 10);
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154E4_mstory5[1]);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3C : 0x5B2F);
    func_80106A50_mstory5();
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154E4_mstory5[0]);
    func_80107228_mstory5(D_801153A0_mstory5[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_80107080_mstory5(D_801153A0_mstory5[6].obj, (Vec *)&D_80114F60_mstory5, 10);
    func_80107080_mstory5(obj, (Vec *)&D_80114F0C_mstory5, 20);
    func_8001C624_main(D_801153A0_mstory5[6].obj->model[1], HmfModelData[D_801153A0_mstory5[6].obj->motion[1]].unk02, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3D : 0x5B30);
    func_80106A50_mstory5();
    func_8001C624_main(D_801153A0_mstory5[6].obj->model[1], HmfModelData[D_801153A0_mstory5[6].obj->motion[0]].unk02, 0, 10, 2);
    func_80107080_mstory5(D_801153A0_mstory5[6].obj, (Vec *)&D_80114F6C_mstory5, 10);
    D_801153A0_mstory5[7].func = func_80114018_mstory5;
    func_80107080_mstory5(obj, (Vec *)&D_80114EDC_mstory5, 20);
    func_8001C624_main(D_801153A0_mstory5[0].obj->model[1], HmfModelData[D_801153A0_mstory5[0].obj->motion[10]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[7].flags & 2)) {
        HuPrcVSleep();
    }
    D_801153A0_mstory5[0].func = func_80110620_mstory5;
    HuPrcSleep(40);
    func_80107080_mstory5(obj, (Vec *)&D_80114F30_mstory5, 50);
    func_80107080_mstory5(obj, (Vec *)&D_80114F24_mstory5, 40);
    D_801153A0_mstory5[1].func = (void (*)(omObjData *))func_80110200_mstory5;
}

void func_80111B60_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80114F9C_mstory5, 20);
    func_80106B48_mstory5(obj, (Vec *)&D_80114F78_mstory5, 20);
    while (!(D_801153A0_mstory5[3].flags & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(obj, (Vec *)&D_80114F90_mstory5, 30, 0);
    while (!(D_801153A0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    func_80106B48_mstory5(obj, (Vec *)&D_80114F84_mstory5, 30);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[1].func = (void (*)(omObjData *))func_80110200_mstory5;
}

void func_80111C48_mstory5(omObjData *obj) {
    Vec pos;
    Vec start;
    s16 model;
    s32 i;
    f32 y;

    model = obj->model[1];
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    pos.y = HmfModelData[model].pos.y;
    i = 0;
    do {
        pos.x = HmfModelData[model].pos.x;
        pos.z = HmfModelData[model].pos.z;
        y = sindf(i * 15.0f) * 80.0f;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        i++;
        HuPrcVSleep();
    } while (i < 12);
    Hu3DModelPosSet(model, start.x, y + start.y, start.z);
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, (s16)D_801154E4_mstory5[2]);
    D_801153A0_mstory5[1].func = (void (*)(omObjData *))func_80110200_mstory5;
}

void func_80111DB8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[2].obj = obj;
    D_801153A0_mstory5[2].flags = 0;
    D_801153A0_mstory5[2].sfxOn = 0;
    if (func_80106B30_mstory5(2) == 0) {
        obj->model[1] = func_8000B108_main(0x700A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
        func_8000B460_main(obj, 0, 0x70000);
        func_8000B460_main(obj, 1, 0x1D0050);
        func_8000B460_main(obj, 2, 0x1D0051);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
        func_8000B460_main(obj, 0, 0x30000);
        func_8000B460_main(obj, 1, 0x1D0046);
        func_8000B460_main(obj, 2, 0x1D0047);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80115478_mstory5[2] = D_80114D20_mstory5[2];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[2].x, D_80115478_mstory5[2].y, D_80115478_mstory5[2].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[2].x, -5.0f, D_80115478_mstory5[2].z);
    omPrcSetDestructor(0, func_80111FE0_mstory5);
    D_801153A0_mstory5[2].func = func_80111FE8_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[2].func(obj);
        HuPrcVSleep();
    }
}

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

const Vec D_80114FB4_mstory5 = { 200.0f, 0.0f, 1200.0f };

void func_80111FE8_mstory5(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106B30_mstory5(2) == 0) {
        CharFXPlay(0x26B, 2);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_801153A0_mstory5[1].func = func_80111820_mstory5;
    HuPrcSleep(70);
    if (func_80106B30_mstory5(2) == 0) {
        CharFXPlay(0x286, 2);
    } else {
        CharFXPlay(0x286, 1);
    }
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    func_80106B48_mstory5(obj, (Vec *)&D_80114FB4_mstory5, 40);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[2].func = (void (*)(omObjData *))func_80110200_mstory5;
}

/* the effect object: 16 puffs (NON_MATCHING: registers s1/s2 swapped, and retail reloads
   time after the += before comparing it with 40) */
#ifdef NON_MATCHING
void func_80112104_mstory5(void) {
    omObjData *obj;
    void *data;
    s32 i;
    s32 base;
    s16 model;
    f32 scale;

    obj = omAddObj(0x14, 0x14, 1, -1, NULL);
    D_80115460_mstory5.obj = obj;
    for (i = 0; i < 16; i++) {
        if (i == 0) {
            data = DataRead(0x1D0036);
            model = base = HmfSprModelCreate(data, 0xA89, 8);
            DataClose(data);
        } else {
            model = func_80014618_main(base, 8);
        }
        func_800147FC_main(model, 0xF0, 0x40, 8);
        func_80014794_main(model, 0x80);
        model = D_800CBB60_main[model].model;
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x70000000, 0x70000000);
        func_8001C814_main(model, 2, 2);
        func_8001C258_main(model, 4, 4);
        obj->model[i + 1] = model;
        D_801154F8_mstory5[i].time = -10.0f;
        D_801154F8_mstory5[i].pos.x = 0.0f;
        D_801154F8_mstory5[i].pos.y = 0.0f;
        D_801154F8_mstory5[i].pos.z = 0.0f;
        D_801154F8_mstory5[i].vel.x = 0.0f;
        D_801154F8_mstory5[i].vel.y = 0.0f;
        D_801154F8_mstory5[i].vel.z = 0.0f;
    }
    D_80115460_mstory5.func = (void (*)(omObjData *))func_80110200_mstory5;
    while (TRUE) {
        D_80115460_mstory5.func(obj);
        for (i = 0; i < 16; i++) {
            if (!(D_801154F8_mstory5[i].time < 0.0f)) {
                func_8001C258_main(obj->model[i + 1], 4, 0);
                scale = D_801154F8_mstory5[i].time / 40.0f * 3.0f + 1.0f;
                Hu3DModelScaleSet(obj->model[i + 1], scale, scale, scale);
                Hu3DModelPosSet(obj->model[i + 1], D_801154F8_mstory5[i].pos.x, D_801154F8_mstory5[i].pos.y, D_801154F8_mstory5[i].pos.z);
                D_801154F8_mstory5[i].pos.x += D_801154F8_mstory5[i].vel.x;
                D_801154F8_mstory5[i].pos.y += D_801154F8_mstory5[i].vel.y;
                D_801154F8_mstory5[i].pos.z += D_801154F8_mstory5[i].vel.z;
                D_801154F8_mstory5[i].time = D_801154F8_mstory5[i].time + 1.0f;
                if (D_801154F8_mstory5[i].time >= 40.0f) {
                    func_8001C258_main(obj->model[i + 1], 4, 4);
                    D_801154F8_mstory5[i].time = -10.0f;
                }
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112104_mstory5);
#endif

/* NON_MATCHING: only the HmfModelData load is scheduled differently */
#ifdef NON_MATCHING
/* the effect object's action: every third frame an idle puff starts 300 in front of actor 3
   and drifts away. Retail shows the puff's model from actor 3's object (obj is unused), not the
   effect object that owns the puffs; func_80112104_mstory5 shows the right one every frame anyway. */
void func_80112514_mstory5(omObjData *obj) {
    Vec pos;
    Vec rot;
    Vec off;
    omObjData *actor;
    HmfModel *model;
    s32 i;

    if (D_80114820_mstory5 >= 3) {
        D_80114820_mstory5 = 0;
        actor = D_801153A0_mstory5[3].obj;
        model = &HmfModelData[actor->model[1]];
        pos.x = model->pos.x;
        pos.y = model->pos.y;
        pos.z = model->pos.z;
        rot.x = model->rot.x;
        rot.y = model->rot.y;
        rot.z = model->rot.z;
        for (i = 0; i < 16; i++) {
            if (D_801154F8_mstory5[i].time < 0.0f) {
                off.x = 0.0f;
                off.y = 150.0f;
                off.z = 300.0f;
                D_801154F8_mstory5[i].pos.x = cosdf(rot.y) * off.x + pos.x - sindf(rot.y) * off.z;
                D_801154F8_mstory5[i].pos.y = pos.y + off.y;
                D_801154F8_mstory5[i].pos.z = sindf(rot.y) * off.x + pos.z + cosdf(rot.y) * off.z;
                D_801154F8_mstory5[i].vel.x = sindf(rot.y) * 5.0f;
                D_801154F8_mstory5[i].vel.y = cosdf(120.0f) * 5.0f;
                D_801154F8_mstory5[i].vel.z = cosdf(rot.y) * 5.0f;
                D_801154F8_mstory5[i].time = 0.0f;
                func_8001C258_main(actor->model[i + 1], 4, 0);
                break;
            }
        }
    }
    D_80114820_mstory5++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112514_mstory5);
#endif

void func_8011275C_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x10, 8, -1, NULL);
    D_801153A0_mstory5[3].obj = obj;
    D_801153A0_mstory5[3].flags = 0;
    D_801153A0_mstory5[3].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0xA003A);
    func_8000B460_main(obj, 4, 0xA003B);
    func_8000B460_main(obj, 5, 0x1D0031);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115478_mstory5[3] = D_80114D20_mstory5[3];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[3].x, D_80115478_mstory5[3].y, D_80115478_mstory5[3].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[3].x, -5.0f, D_80115478_mstory5[3].z);
    omPrcSetDestructor(0, func_80112994_mstory5);
    D_801153A0_mstory5[3].func = (void (*)(omObjData *))func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80112994_mstory5(void) {
}

/* actor 3's script: it drives the scene, cueing actors 4-6 through its flags */
void func_8011299C_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A40 : 0x5B33);
    func_80106A50_mstory5();
    D_801153A0_mstory5[4].func = func_80113138_mstory5;
    D_801153A0_mstory5[5].func = func_80113618_mstory5;
    D_801153A0_mstory5[3].flags |= 2;
    func_80106B48_mstory5(obj, (Vec *)&D_80114FC0_mstory5, 40);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuAudFXPlay(0x29C);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A41 : 0x5B34);
    func_80106A50_mstory5();
    D_801153A0_mstory5[3].flags |= 8;
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80106B48_mstory5(D_801153A0_mstory5[1].obj, (Vec *)&D_8011502C_mstory5, 10);
    HuAudFXPlay(0x2A8);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A42 : 0x5B35);
    func_80106A50_mstory5();
    func_8001C624_main(model, HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801153A0_mstory5[3].flags |= 0x10;
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107080_mstory5(obj, (Vec *)&D_80114FF0_mstory5, 10);
    func_80106B64_mstory5(obj, (Vec *)&D_80114FD8_mstory5, 40, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801153A0_mstory5[3].flags |= 1;
    func_80107080_mstory5(obj, (Vec *)&D_80115020_mstory5, 90);
    HuPrcSleep(60);
    func_80107080_mstory5(obj, (Vec *)&D_80115014_mstory5, 20);
    D_801153A0_mstory5[3].flags |= 4;
    HuPrcSleep(20);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106B48_mstory5(obj, (Vec *)&D_80114FE4_mstory5, 30);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80107080_mstory5(obj, (Vec *)&D_80114FF0_mstory5, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    HuPrcSleep(30);
    HuAudFXPlay(0x21B);
    D_80115460_mstory5.func = func_80112514_mstory5;
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_80115460_mstory5.func = (void (*)(omObjData *))func_80110200_mstory5;
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(40);
    HuAudFXPlay(0x29E);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A44 : 0x5B37);
    func_80106A50_mstory5();
    D_801153A0_mstory5[3].flags |= 0x20;
    HuPrcSleep(50);
    func_80105FDC_mstory5();
    D_801153A0_mstory5[3].func = (void (*)(omObjData *))func_80110200_mstory5;
}

void func_80112F38_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[4].obj = obj;
    D_801153A0_mstory5[4].flags = 0;
    D_801153A0_mstory5[4].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0xA00F0);
    func_8000B460_main(obj, 3, 0x1D0037);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115478_mstory5[4] = D_80114D20_mstory5[4];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[4].x, D_80115478_mstory5[4].y, D_80115478_mstory5[4].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[4].x, -5.0f, D_80115478_mstory5[4].z);
    omPrcSetDestructor(0, func_80113130_mstory5);
    D_801153A0_mstory5[4].func = (void (*)(omObjData *))func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[4].func(obj);
        HuPrcVSleep();
    }
}

void func_80113130_mstory5(void) {
}

/* actor 4's script: cued by actor 3's flags (8, 0x10, 1, 4, 0x20), then loops motion 2 */
void func_80113138_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B48_mstory5(obj, (Vec *)&D_80115038_mstory5, 40);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].flags & 8)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].flags & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, (Vec *)&D_80115074_mstory5, 40);
    while (!(D_801153A0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_80107080_mstory5(obj, (Vec *)&D_80115068_mstory5, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80106B48_mstory5(obj, (Vec *)&D_80115050_mstory5, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(40);
    func_80107080_mstory5(obj, (Vec *)&D_80115074_mstory5, 10);
    while (!(D_801153A0_mstory5[3].flags & 4)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, (Vec *)&D_80115068_mstory5, 30);
    while (!(D_801153A0_mstory5[3].flags & 0x20)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
        func_80107254_mstory5(model);
    }
}

void func_80113470_mstory5(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[5].obj = obj;
    D_801153A0_mstory5[5].flags = 0;
    D_801153A0_mstory5[5].sfxOn = 0;
    src = D_801153A0_mstory5[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115478_mstory5[5] = D_80114D20_mstory5[5];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[5].x, D_80115478_mstory5[5].y, D_80115478_mstory5[5].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[5].x, -5.0f, D_80115478_mstory5[5].z);
    omPrcSetDestructor(0, func_8011396C_mstory5);
    D_801153A0_mstory5[5].func = (void (*)(omObjData *))func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[5].func(obj);
        HuPrcVSleep();
    }
}

/* actor 5's script (a copy of actor 4: it plays actor 4's motions on its linked model) */
void func_80113618_mstory5(omObjData *obj) {
    omObjData *src = D_801153A0_mstory5[4].obj;
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B48_mstory5(obj, (Vec *)&D_80115080_mstory5, 40);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].flags & 8)) {
        HuPrcVSleep();
    }
    func_8001C624_main(model, HmfModelData[src->motion[3]].unk02, 0, 10, 0);
    func_80107254_mstory5(model);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].flags & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, (Vec *)&D_801150BC_mstory5, 40);
    while (!(D_801153A0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_80107080_mstory5(obj, (Vec *)&D_801150B0_mstory5, 10);
    func_8001C624_main(model, HmfModelData[src->motion[1]].unk02, 0, 10, 2);
    func_80106B48_mstory5(obj, (Vec *)&D_80115098_mstory5, 10);
    func_8001C624_main(model, HmfModelData[src->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(40);
    func_80107080_mstory5(obj, (Vec *)&D_801150BC_mstory5, 10);
    while (!(D_801153A0_mstory5[3].flags & 4)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, (Vec *)&D_801150B0_mstory5, 30);
    while (!(D_801153A0_mstory5[3].flags & 0x20)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        func_8001C624_main(model, HmfModelData[src->motion[2]].unk02, 0, 10, 0);
        func_80107254_mstory5(model);
    }
}

void func_8011396C_mstory5(void) {
}

void func_80113974_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[6].obj = obj;
    D_801153A0_mstory5[6].flags = 0;
    D_801153A0_mstory5[6].sfxOn = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_80115478_mstory5[6] = D_80114D20_mstory5[6];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[6].x, D_80115478_mstory5[6].y, D_80115478_mstory5[6].z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5[6].x, -5.0f, D_80115478_mstory5[6].z);
    omPrcSetDestructor(0, func_80113B64_mstory5);
    D_801153A0_mstory5[6].func = (void (*)(omObjData *))func_80110200_mstory5;
    D_80114824_mstory5 = 1;
    while (TRUE) {
        D_801153A0_mstory5[6].func(obj);
        HuPrcVSleep();
    }
}

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

const Vec D_801150C8_mstory5 = { 250.0f, 0.0f, 150.0f };
const Vec D_801150D4_mstory5 = { 800.0f, 0.0f, 350.0f };

void func_80113B6C_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_801150F8_mstory5, 20);
    func_80106B48_mstory5(obj, (Vec *)&D_801150C8_mstory5, 20);
    while (!(D_801153A0_mstory5[3].flags & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(obj, (Vec *)&D_801150E0_mstory5, 30, 0);
    while (!(D_801153A0_mstory5[3].flags & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, (Vec *)&D_80115128_mstory5, 40);
    while (!(D_801153A0_mstory5[3].flags & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, (Vec *)&D_801150F8_mstory5, 15);
    func_80106B64_mstory5(obj, (Vec *)&D_801150EC_mstory5, 5, 0);
    func_80107080_mstory5(obj, (Vec *)&D_80115110_mstory5, 10);
    func_80107080_mstory5(obj, (Vec *)&D_8011511C_mstory5, 10);
    func_80106B64_mstory5(obj, (Vec *)&D_801150D4_mstory5, 20, 0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[6].func = (void (*)(omObjData *))func_80110200_mstory5;
}

void func_80113CF8_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, (Vec *)&D_80115134_mstory5, 20);
    D_801153A0_mstory5[6].func = (void (*)(omObjData *))func_80110200_mstory5;
}

/* actor 6 bobs up and down */
/* actor 6 bobs up and down (NON_MATCHING, as mstory1's twin: one extra delay-slot nop) */
#ifdef NON_MATCHING
void func_80113D2C_mstory5(void) {
    Vec pos;
    s16 model;
    f32 t;
    f32 y;

    t = 0.0f;
    if (D_80114824_mstory5 != 0) {
        model = D_801153A0_mstory5[6].obj->model[1];
        pos.y = HmfModelData[model].pos.y;
        while (TRUE) {
            pos.x = HmfModelData[model].pos.x;
            pos.z = HmfModelData[model].pos.z;
            y = sindf(t) * 25.0f + 25.0f;
            t += 2.0f;
            t = (t >= 360.0f) ? t - 360.0f : t;
            Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
            HuPrcVSleep();
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113D2C_mstory5);
#endif

void func_80113E58_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801153A0_mstory5[7].obj = obj;
    D_801153A0_mstory5[7].flags = 0;
    D_801153A0_mstory5[7].sfxOn = 0;
    obj->model[1] = func_8000B108_main(D_8011514C_mstory5[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115478_mstory5[7] = D_80114D20_mstory5[7];
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5[7].x, D_80115478_mstory5[7].y, D_80115478_mstory5[7].z);
    D_801154DA_mstory5 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_801154DA_mstory5, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_801154DA_mstory5, 60.0f);
    func_800138EC_main(D_801154DA_mstory5, 1, 0);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    omPrcSetDestructor(0, func_80114010_mstory5);
    D_801153A0_mstory5[7].func = (void (*)(omObjData *))func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[7].func(obj);
        HuPrcVSleep();
    }
}

void func_80114010_mstory5(void) {
}

void func_80114018_mstory5(omObjData *obj) {
    Vec pos;
    ObPath *path[2];
    omObjData *other;
    s32 i;
    f32 t;
    f32 rot;

    path[0] = func_8010F4D0_mstory5(D_80114828_mstory5, 0);
    path[1] = func_8010F4D0_mstory5(D_80114858_mstory5, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_801154DA_mstory5, 4, 0);
    func_800138EC_main(D_801154DA_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    i = 0;
    do {
        t = i * 0.02f;
        func_8010F7D4_mstory5(path[0], t * t, &pos);
        i++;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_801154DA_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 50);
    HuPrcSleep(40);
    other = D_801153A0_mstory5[6].obj;
    func_8001C624_main(other->model[1], HmfModelData[other->motion[2]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    D_801153A0_mstory5[7].flags |= 2;
    HuAudFXPlay(0x218);
    func_8001C624_main(other->model[1], HmfModelData[other->motion[0]].unk02, 0, 10, 2);
    rot = 0.0f;
    i = 0;
    do {
        t = i * (1.0f / 120.0f);
        func_8010F7D4_mstory5(path[1], t * t, &pos);
        rot -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        i++;
        Hu3DModelRotSet(obj->model[1], 0.0f, rot, 0.0f);
        func_8000CFA4_main(D_801154DA_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    } while (i < 120);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    HuAudFXPlay(0x21A);
    func_8011007C_mstory5(path[0]);
    func_8011007C_mstory5(path[1]);
    D_801153A0_mstory5[7].flags = 1;
    D_801153A0_mstory5[7].func = (void (*)(omObjData *))func_80110200_mstory5;
}

void func_80114334_mstory5(omObjData *a, omObjData *b) {
    s16 models[2];
    Vec pos[2];
    Vec rot;
    Vec d;
    s32 i;

    models[0] = a->model[1];
    models[1] = b->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = HmfModelData[models[i]].pos.x;
        pos[i].y = HmfModelData[models[i]].pos.y;
        pos[i].z = HmfModelData[models[i]].pos.z;
    }
    rot.x = HmfModelData[models[0]].rot.x;
    rot.y = HmfModelData[models[0]].rot.y;
    rot.z = HmfModelData[models[0]].rot.z;
    d.x = pos[1].x - pos[0].x;
    d.y = pos[1].y - pos[0].y;
    d.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(d.z, d.x) - 90.0f);
    Hu3DModelRotSet(models[0], rot.x, rot.y, rot.z);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150EC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150F8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115110_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011511C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115128_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115134_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011514C_mstory5);

void func_8011447C_mstory5(u32 actor, s32 fx) {

    if (D_801153A0_mstory5[actor].sfxOn == 0) {
        D_801153A0_mstory5[actor].sfxOn = 1;
        D_801153A0_mstory5[actor].sfxId = fx;
        switch (actor) {
        case 0:
            D_801153A0_mstory5[actor].sfxNo = CharFXPlay(fx, GwStory.unk1);
            break;
        case 2:
            if (func_80106B30_mstory5(2) == 0) {
                D_801153A0_mstory5[actor].sfxNo = CharFXPlay(fx, 2);
            } else {
                D_801153A0_mstory5[actor].sfxNo = CharFXPlay(fx, 1);
            }
            break;
        case 1:
        case 3:
        case 4:
        case 5:
            break;
        }
    }
}

void func_80114560_mstory5(u32 actor) {
    if (D_801153A0_mstory5[actor].sfxOn == 1) {
        D_801153A0_mstory5[actor].sfxOn = 0;
        switch (actor) {
        case 0:
        case 2:
            HuAudFXStop((s16)D_801153A0_mstory5[actor].sfxNo);
            break;
        case 1:
        case 3:
        case 4:
        case 5:
            break;
        }
    }
}

void func_801145DC_mstory5(void) {
    s32 i;
    s32 fx;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (D_801153A0_mstory5[i].sfxOn == 1 && HmfModelData[D_801153A0_mstory5[i].obj->model[1]].unk40 == 0.0f) {
                fx = D_801153A0_mstory5[i].sfxId;
                switch ((u32)i) {
                case 0:
                    D_801153A0_mstory5[i].sfxNo = CharFXPlay(fx, GwStory.unk1);
                    break;
                case 2:
                    if (func_80106B30_mstory5(2) == 0) {
                        D_801153A0_mstory5[i].sfxNo = CharFXPlay(fx, 2);
                    } else {
                        D_801153A0_mstory5[i].sfxNo = CharFXPlay(fx, 1);
                    }
                    break;
                case 1:
                case 3:
                case 4:
                case 5:
                    break;
                }
            }
        }
        HuPrcVSleep();
    }
}
