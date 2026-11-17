#include "common.h"

/* a story-scene actor: its object and the action its process runs every frame */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
} StoryActor; /* size = 0x18 */

extern StoryActor D_801158F0_mstory1[8];
extern Vec D_801159B0_mstory1[8]; /* actor positions */
extern s16 D_80115A10_mstory1; /* shadow model, linked by every actor */
extern s16 D_80115A14_mstory1[4];
extern s32 D_80115A1C_mstory1[3]; /* texture animations */
extern s16 D_80115A28_mstory1;
extern const Vec D_80114CB0_mstory1[8]; /* actor start positions */
extern const s32 D_80114D10_mstory1[8];
extern const s32 D_80114D30_mstory1[8];
extern const s32 D_80114D50_mstory1[8];
extern const s32 D_80114D70_mstory1[8];
extern const Vec D_80114E40_mstory1;
extern const Vec D_80114E4C_mstory1;
extern const Vec D_80114F00_mstory1;
extern const Vec D_80114F0C_mstory1;
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_80032FC0_main(s16, s32, s32);
s16 func_800329B4_main(void *);
void func_80106984_mstory1(void);
void func_801081D8_mstory1(omObjData *obj);
void func_801081E0_mstory1(void);
void func_801085F0_mstory1(void);
void func_80109140_mstory1(void);
void func_80109470_mstory1(void);
void func_801099F8_mstory1(void);
void func_80109C20_mstory1(void);
void func_80109C28_mstory1(omObjData *obj);
void func_80109DC0_mstory1(void);
void func_8010A424_mstory1(void);
void func_8010AA98_mstory1(void);
void func_8010B110_mstory1(void);
void func_8010B3B8_mstory1(void);
void func_8010B4E4_mstory1(void);
void func_8010BC68_mstory1(void);
#include "mallocblock.h"

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i runs
   from points[i] to points[i + 1] and covers [segs[i].start, segs[i].end] of the path's
   length (0..1). flags & 1: closed (the last segment returns to points[0]). Same as opboard's. */
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
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, s32);
s32 func_80050064_main(s32 write);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);

void func_80105FF4_mstory1(void);
void func_801068A0_mstory1(void);
void func_80106B30_mstory1(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106D80_mstory1(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106B14_mstory1(omObjData *obj, Vec *to, s32 frames);
void func_80106D64_mstory1(omObjData *obj, Vec *to, s32 frames);
void func_8010704C_mstory1(omObjData *obj, Vec *to, s32 frames);
s32 func_8010726C_mstory1(s16 model);

extern u32 D_80114A80_mstory1; /* main object state */
extern s32 D_80114A84_mstory1; /* 1: the scene was seen before, A skips it */
extern s8 D_80114A88_mstory1;
extern Vec D_80114A8C_mstory1; /* camera position */
extern Vec D_80114A98_mstory1; /* camera target */
extern Vec D_80114AA4_mstory1; /* camera up */
extern s32 D_80114AB0_mstory1;
extern s16 D_801158B0_mstory1; /* message window */
extern s16 D_801158B2_mstory1; /* background model */
extern s32 D_801158B4_mstory1; /* the controller that drives the story messages */
extern s16 D_801158B8_mstory1; /* background sprite */
extern s32 D_801158E4_mstory1;
extern s16 D_801158C0_mstory1[8]; /* the map sprite, then the seven board icons */
extern s16 D_801158D0_mstory1[8]; /* the star ring */
extern s16 D_801158E0_mstory1; /* the flash sprite */
extern const s32 D_80114C6C_mstory1[7]; /* board icon files */
extern const s16 D_80114C88_mstory1[7][2]; /* board icon positions */
void func_8000BBFC_main(u16 spriteId, s16 alpha);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BEAC_main(u16 spriteId, s32 r, s32 g, s32 b);


// the A-press test: retail andi/sltu, KMC folds it to srl/andi (masked 2)
#ifdef NON_MATCHING
void func_80105C90_mstory1(omObjData *obj) {
    u32 state = D_80114A80_mstory1;

    switch (state) {
    case 0:
        HuAudSeqPlay(0x26);
        state++;
        break;
    case 1:
        state += WipeStatGet() == 0;
        break;
    case 2:
        if (D_80114A84_mstory1 == 1) {
            state += (D_800D5558_main[D_801158B4_mstory1] & 0x1000) > 0;
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
    D_80114A80_mstory1 = state;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105C90_mstory1);
#endif

void func_80105D80_mstory1(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80114A88_mstory1 == 0) {
            WipeCreateOut(2, 0x14);
            HuAudSeqFadeOut(0x1E);
            D_80114A88_mstory1 = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            func_8005F524_main();
            func_80050064_main(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105E00_mstory1(void) {
    D_801158B8_mstory1 = InitEspriteSlot(func_8000B838_main(0x1D0012), 0, 0);
    func_8000BBD4_main(D_801158B8_mstory1, 0xA0, 0x78);
    func_8000BC48_main(D_801158B8_mstory1, 0x4000);
    D_801158B2_mstory1 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_801158B2_mstory1, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_801158B2_mstory1, 2, 0);
    func_8001C814_main(D_801158B2_mstory1, 1, 1);
}

void func_80105EC0_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, 4, 4);
    func_8000BB94_main(D_801158B8_mstory1);
}

void func_80105EF4_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, 4, 0);
    func_8000BB54_main(D_801158B8_mstory1);
}

void func_80105F28_mstory1(omObjData *obj) {
    D_800CE17C_main[0] = D_80114A8C_mstory1.x;
    D_800CE17C_main[1] = D_80114A8C_mstory1.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_80114A8C_mstory1, &D_80114A98_mstory1, &D_80114AA4_mstory1);
    Hu3DCamUpdateMtx(0);
}

void func_80105FA8_mstory1(void) {
    D_80114A80_mstory1 = 3;
}

void func_80105FB8_mstory1(s32 arg0) {
    D_801158E4_mstory1 = arg0;
    D_80114AB0_mstory1 = 0;
    omAddPrcObj(func_80105FF4_mstory1, 0x1000, 0x800, 0);
}

/* the chapter-map scene: the board map with the seven board icons, a ring of eight stars
   that bursts around the current board's icon, and a flash; sets D_80114AB0_mstory1 when done */
void func_80105FF4_mstory1(void) {
    void *data;
    f32 x;
    f32 y;
    f32 a;
    f32 alpha;
    s32 i;
    s32 j;
    s32 wait;

    D_801158C0_mstory1[0] = InitEspriteSlot(func_8000B838_main(0x1D0001), 0, 0);
    func_8000BBD4_main(D_801158C0_mstory1[0], 0xA0, 0x78);
    func_8000BB94_main(D_801158C0_mstory1[0]);
    for (i = 0; i < 7; i++) {
        D_801158C0_mstory1[i + 1] = InitEspriteSlot(func_8000B838_main(D_80114C6C_mstory1[i]), 0, 0);
        func_8000BBD4_main(D_801158C0_mstory1[i + 1], D_80114C88_mstory1[i][0] + 0x30, D_80114C88_mstory1[i][1] + 0x30);
        func_8000BC48_main(D_801158C0_mstory1[i + 1], 8);
        func_8000BB94_main(D_801158C0_mstory1[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        D_801158D0_mstory1[i] = InitEspriteSlot(func_80055810_main(data), 0, 1);
        x = D_80114C88_mstory1[D_801158E4_mstory1][0] + 0x30;
        y = D_80114C88_mstory1[D_801158E4_mstory1][1] + 0x30;
        a = i * 45.0f;
        x += cosdf(a) * 32.0f;
        y -= sindf(a) * 32.0f;
        func_8000BBD4_main(D_801158D0_mstory1[i], x, y);
        func_8000BC48_main(D_801158D0_mstory1[i], 0x1000);
        func_8000BEAC_main(D_801158D0_mstory1[i], 0xFF, 0xFF, 0xC0);
        func_8000BC48_main(D_801158D0_mstory1[i], 8);
        func_8000BE5C_main(D_801158D0_mstory1[i], 1.5f, 1.5f);
        func_8000BBFC_main(D_801158D0_mstory1[i], 0xFF);
        func_8000BB94_main(D_801158D0_mstory1[i]);
    }
    HuMemMemoryFreePerm(data);
    D_801158E0_mstory1 = InitEspriteSlot(func_8000B838_main(0x1D0000), 0, 0);
    func_8000BBD4_main(D_801158E0_mstory1, 0xA0, 0x78);
    func_8000BE5C_main(D_801158E0_mstory1, 40.0f, 30.0f);
    func_8000BC48_main(D_801158E0_mstory1, 0);
    func_8000BB94_main(D_801158E0_mstory1);
    omPrcSetDestructor(0, func_801068A0_mstory1);
    func_8000BB54_main(D_801158E0_mstory1);
    func_8000BBFC_main(D_801158E0_mstory1, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801158E0_mstory1, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_801158E0_mstory1, 0x100);
    for (i = 0; i < D_801158E4_mstory1; i++) {
        func_8000BB54_main(D_801158C0_mstory1[i + 1]);
    }
    func_80105EC0_mstory1();
    func_8000BB54_main(D_801158C0_mstory1[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801158E0_mstory1, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_801158E0_mstory1);
    func_8000BBFC_main(D_801158C0_mstory1[D_801158E4_mstory1 + 1], 0);
    func_8000BB54_main(D_801158C0_mstory1[D_801158E4_mstory1 + 1]);
    for (alpha = 0.0f, j = 0; j < 20; j++) {
        alpha += 12.75f;
        func_8000BBFC_main(D_801158C0_mstory1[D_801158E4_mstory1 + 1], alpha);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_801158C0_mstory1[D_801158E4_mstory1 + 1], 0xFF);
    func_8000BE5C_main(D_801158C0_mstory1[D_801158E4_mstory1 + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        func_8000BD94_main(D_801158D0_mstory1[i], 0, 0);
        func_8000BDDC_main(D_801158D0_mstory1[i], 1);
        func_8000BB54_main(D_801158D0_mstory1[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        func_8000BB94_main(D_801158D0_mstory1[i]);
    }
    wait = 60;
    if (D_801158E4_mstory1 == 6) {
        HuPrcSleep(40);
        func_8000BB54_main(D_801158E0_mstory1);
        func_8000BBFC_main(D_801158E0_mstory1, 0);
        for (i = 0; i < 5; i++) {
            func_8000BBFC_main(D_801158E0_mstory1, i * 0.125f * 255.0f);
            HuPrcVSleep();
        }
        func_8000BBFC_main(D_801158E0_mstory1, 0x100);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            func_8000BBFC_main(D_801158E0_mstory1, 255.0f - i * 0.125f * 255.0f);
            HuPrcVSleep();
        }
        func_8000BB94_main(D_801158E0_mstory1);
        wait = 80;
    }
    HuPrcSleep(wait);
    func_8000BB54_main(D_801158E0_mstory1);
    func_8000BBFC_main(D_801158E0_mstory1, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801158E0_mstory1, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_801158E0_mstory1, 0x100);
    func_8000BB94_main(D_801158C0_mstory1[D_801158E4_mstory1 + 1]);
    func_8000BB94_main(D_801158C0_mstory1[0]);
    func_80105EF4_mstory1();
    HuPrcSleep(30);
    for (i = 0; i < D_801158E4_mstory1; i++) {
        func_8000BB94_main(D_801158C0_mstory1[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801158E0_mstory1, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_801158E0_mstory1);
    D_80114AB0_mstory1 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_80106894_mstory1(void) {
    return D_80114AB0_mstory1;
}

void func_801068A0_mstory1(void) {
}

void func_801068A8_mstory1(void) {
}

void func_801068B0_mstory1(s16 model, s16 anim, s16 frame) {
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

void func_80106984_mstory1(void) {
    D_801158B0_mstory1 = func_80060880_main(0xA0, 0xC2, 0x14);
    func_8005FE54_main(D_801158B0_mstory1, 1 << D_801158B4_mstory1);
    func_8005B6BC_main(D_801158B0_mstory1, GwStory.unk1 + 0x1C00, 0);
}

void func_801069EC_mstory1(void) {
    func_8005D294_main(D_801158B0_mstory1);
    func_80060C14_main(D_801158B0_mstory1, 1);
}

void func_80106A1C_mstory1(void) {
    func_80060EA8_main(D_801158B0_mstory1, 1);
}

void func_80106A40_mstory1(s32 mess) {
    func_8005B43C_main(D_801158B0_mstory1, mess, -1, -1);
    while (func_8005E0C0_main(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

void func_80106A94_mstory1(s32 mess) {
    func_8005B43C_main(D_801158B0_mstory1, mess, -1, -1);
}

void func_80106AC0_mstory1(void) {
    while (func_8005E0C0_main(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106AFC_mstory1(s32 chr) {
    return (chr == GwStory.unk1) ? -1 : 0;
}

void func_80106B14_mstory1(omObjData *obj, Vec *to, s32 frames) {
    func_80106B30_mstory1(obj, to, frames, 1);
}

// register allocation; retail converts frames separately for the divide (masked 10)
#ifdef NON_MATCHING
/* walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning
   it to face the way first when `turn` is set */
void func_80106B30_mstory1(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106B30_mstory1);
#endif

void func_80106D64_mstory1(omObjData *obj, Vec *to, s32 frames) {
    func_80106D80_mstory1(obj, to, frames, 1);
}

// register allocation; retail converts frames separately for the divide (masked 9)
#ifdef NON_MATCHING
/* as func_80106B30_mstory1, but the second model follows in 3D */
void func_80106D80_mstory1(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106D80_mstory1);
#endif

void func_80106F94_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106B14_mstory1(obj, &to, frames);
}

void func_80106FC0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106B30_mstory1(obj, &to, frames, turn);
}

void func_80106FF0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106D64_mstory1(obj, &to, frames);
}

void func_8010701C_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106D80_mstory1(obj, &to, frames, turn);
}

/* turns obj's model to the rotation `to` in `frames` frames, easing out */
void func_8010704C_mstory1(omObjData *obj, Vec *to, s32 frames) {
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

void func_801071F4_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_8010704C_mstory1(obj, &to, frames);
}

void func_80107220_mstory1(s16 model) {
    HuPrcSleep(10);
    while (func_8010726C_mstory1(model) == 0) {
        HuPrcVSleep();
    }
}

/* -1 once the model's motion has played to its end */
s32 func_8010726C_mstory1(s16 model) {
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

/* moves obj's model (and its shadow) `speed` units a frame the way it faces, for `frames` frames */
void func_80107318_mstory1(omObjData *obj, f32 speed, s16 frames) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C88_mstory1);
