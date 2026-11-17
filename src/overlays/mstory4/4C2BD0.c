#include "common.h"

// story v1
/* a story-scene actor: its object and the action its process runs every frame */
typedef struct StoryActor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10; /* looping sound effect */
    /* 0x14 */ s32 unk14; /* its handle */
} StoryActor; /* size = 0x18 */

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

#include "mallocblock.h"

extern TexAnimSlot *D_800D1714_main;
extern f32 D_800CE17C_main[];
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, s32);
s32 func_80050064_main(s32 write);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
void MBDBackKill(void);
void MBDBackClose(void);

extern u32 D_80111AC0_mstory4; /* main object state */
extern s32 D_80111AC4_mstory4; /* 1: a board background is open and is closed on exit */
extern s32 D_80111AC8_mstory4; /* 1: the scene was seen before, A skips it */
extern s8 D_80111ACC_mstory4;
extern Vec D_80111AD0_mstory4; /* camera position */
extern Vec D_80111ADC_mstory4; /* camera target */
extern Vec D_80111AE8_mstory4; /* camera up */
extern s32 D_80111AF4_mstory4;
extern s16 D_80112120_mstory4; /* message window */
extern s16 D_80112122_mstory4; /* background model */
extern s32 D_80112124_mstory4; /* the controller that drives the story messages */
extern s16 D_80112126_mstory4; /* low half of D_80112124_mstory4 */
extern s16 D_80112128_mstory4; /* background sprite */
extern s32 D_801121B4_mstory4;
extern StoryActor D_801121C0_mstory4[];
extern s32 D_80112238_mstory4[4]; /* texture animations */
extern s16 D_80112248_mstory4;
extern s32 D_801123B0_mstory4[4]; /* play order: player per slot */

extern void (*const D_80111C10_mstory4[2])(void);
extern const s32 D_80111C18_mstory4[2];
extern const Vec D_80111DB8_mstory4;
extern const Vec D_80111DC4_mstory4;
extern const Vec D_80111E78_mstory4;
extern const Vec D_80111E84_mstory4;

void func_80105C90_mstory4(omObjData *obj);
void func_80105DA8_mstory4(omObjData *obj);
void func_80105F40_mstory4(void);
void func_80106068_mstory4(omObjData *obj);
void func_80106134_mstory4(void);
void func_80106DBC_mstory4(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106DA0_mstory4(omObjData *obj, Vec *to, s32 frames);
void func_80106FF0_mstory4(omObjData *obj, Vec *to, s32 frames);
void func_8010700C_mstory4(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_801072D8_mstory4(omObjData *obj, Vec *to, s32 frames);
s32 func_801074F8_mstory4(s16 model);
void func_801074AC_mstory4(s16 model);
void func_80106B3C_mstory4(s16 model, s16 anim, s16 frame);
void func_8010818C_mstory4(void);
void func_80108280_mstory4(omObjData *obj);
void func_8010B9FC_mstory4(void);
void func_80106C10_mstory4(void);
void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80108288_mstory4(void);
void func_801094DC_mstory4(void);
void func_80109B5C_mstory4(omObjData *obj);
void func_80109EA4_mstory4(void);
void func_8010A1C4_mstory4(void);
void func_8010A480_mstory4(void);
void func_8010A5AC_mstory4(void);
void func_8010ACF4_mstory4(void);
extern s16 D_8011228C_mstory4; /* shadow model, linked by every actor */
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_801086EC_mstory4(void);
extern Vec D_80112250_mstory4[]; /* actor positions */
extern s16 D_80112290_mstory4[4];
extern const Vec D_80111C70_mstory4[]; /* actor start positions */
extern const s32 D_80111CAC_mstory4[8];
extern const s32 D_80111CCC_mstory4[8];
extern const s32 D_80111CEC_mstory4[8];
extern const s32 D_80111D0C_mstory4[8];
void func_80109838_mstory4(void);
void func_80032FC0_main(s16, s32, s32);
s16 func_800329B4_main(void *);
void func_801093B0_mstory4(omObjData *obj);
void func_801086F4_mstory4(omObjData *obj);
void func_8010A44C_mstory4(omObjData *obj);
void func_8010A76C_mstory4(omObjData *obj);
void func_80106C78_mstory4(void);
void func_80106CA8_mstory4(void);
void func_80106CCC_mstory4(s32 mess);
extern const Vec D_80111DDC_mstory4;
extern const Vec D_80111DF4_mstory4;
extern const Vec D_80111E0C_mstory4;
extern const Vec D_80111E18_mstory4;
extern const Vec D_80111E24_mstory4;
extern const Vec D_80111E30_mstory4;
extern const Vec D_80111E3C_mstory4;
extern const Vec D_80111E48_mstory4;
extern const Vec D_80111E54_mstory4;
extern const Vec D_80111E60_mstory4;
void func_8010A05C_mstory4(void);
void func_8010A064_mstory4(omObjData *obj);
void func_80109840_mstory4(omObjData *obj);
void func_8010ABD0_mstory4(s32 actor, s32 fx);
void func_8010AC84_mstory4(s32 actor);
typedef struct MsPart { /* a model part (func_8001D33C_main) */
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ char unk28[0x18];
    /* 0x40 */ Vec unk40;
} MsPart;
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_8002FD8C_main(s16, s16, const char *, s16, s16);
void func_8002FDCC_main(s16, s16, const char *, s16, s16);
void *func_8001D33C_main(s16, const char *);
void func_801060E8_mstory4(void);
void func_801060F8_mstory4(s32 arg0);
s32 func_80106B20_mstory4(void);
void func_80109CCC_mstory4(omObjData *obj);
void func_80109E3C_mstory4(omObjData *obj);
void func_80109E68_mstory4(omObjData *obj);
extern s16 D_8011228E_mstory4;

void func_801059A0_mstory4(void) {
    s16 n = 0;
    s16 i;
    s16 j;
    s16 step;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            D_801123B0_mstory4[n] = j;
            n++;
            if (n >= 4) {
                break;
            }
        }
        if (n >= 4) {
            break;
        }
    }
    func_800142A0_main(0x3C);
    omInitObjMan(0x1E, 0x1E);
    func_8005A6B0_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 35.0f, 80.0f, 8000.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    {
        omObjData *obj = omAddObj(0x7FDA, 0, 0, -1, func_80106068_mstory4);
        omSetStatBit(obj, 0xA0);
        func_80106068_mstory4(obj);
    }
    omAddObj(0, 0, 0, -1, func_80105C90_mstory4);
    omAddObj(0, 0, 0, -1, func_80105DA8_mstory4);
    func_80105F40_mstory4();
    for (D_80112124_mstory4 = 0; D_80112124_mstory4 < 4; D_80112124_mstory4++) {
        if (CheckControllerRead(D_80112126_mstory4) != 0) {
            break;
        }
    }
    if (D_80112124_mstory4 >= 4) {
        D_80112124_mstory4 = 0;
    }
    step = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        step = 1;
    }
    D_80111C10_mstory4[step]();
    if (_CheckFlag(D_80111C18_mstory4[step]) != 0) {
        D_80111AC8_mstory4 = 1;
    } else {
        _SetFlag(D_80111C18_mstory4[step]);
    }
    WipeCreateIn(2, 0x10);
}

/* the scene for each story step (GwPlayer[0].coin), and the flag set once it has been seen */
void (*const D_80111C10_mstory4[2])(void) = { func_8010818C_mstory4, func_8010B9FC_mstory4 };

const s32 D_80111C18_mstory4[2] = { 0x3E, 0x3F };

#ifdef NON_MATCHING
// the A-press test: retail andi/sltu, KMC folds it to srl/andi (masked 2), as mstory1's twin
void func_80105C90_mstory4(omObjData *obj) {
    u32 state = D_80111AC0_mstory4;

    switch (state) {
    case 0:
        HuAudSeqPlay(0x26);
        state++;
        break;
    case 1:
        state += WipeStatGet() == 0;
        break;
    case 2:
        if (D_80111AC8_mstory4 == 1) {
            state += (D_800D5558_main[D_80112124_mstory4] & 0x1000) != 0;
        }
        break;
    case 3:
        if (GwPlayer[0].coin == 0) {
            WipeCreateOut(2, 0x14);
        } else {
            WipeCreateOut(0xB, 0x14);
        }
        state++;
        break;
    case 4:
        if (WipeStatGet() == 0) {
            if (D_80111AC4_mstory4 == 1) {
                MBDBackKill();
                MBDBackClose();
            }
            func_8005F524_main();
            func_80050064_main(1);
            omOvlReturnEx(1);
        }
        break;
    }
    D_80111AC0_mstory4 = state;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80105C90_mstory4);
#endif

void func_80105DA8_mstory4(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80111ACC_mstory4 == 0) {
            if (GwPlayer[0].coin == 0) {
                WipeCreateOut(2, 0x14);
            } else {
                WipeCreateOut(0xB, 0x14);
            }
            D_80111ACC_mstory4 = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            func_8005F524_main();
            if (D_80111AC4_mstory4 == 1) {
                MBDBackKill();
                MBDBackClose();
            }
            func_80050064_main(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105E58_mstory4(void) {
    func_8001C814_main(D_80112122_mstory4, 4, 0);
    func_8001C814_main(D_80112122_mstory4, 1, 0);
    func_8001C6A8_main(D_80112122_mstory4, 0.0f);
    HuAudFXPlay(0x217);
}

void func_80105EAC_mstory4(void) {
    func_8001C814_main(D_80112122_mstory4, 4, 4);
    func_8001C814_main(D_80112122_mstory4, 1, 0);
    func_8001C6A8_main(D_80112122_mstory4, D_800CCF58_main[HmfModelData[D_80112122_mstory4].unk02].unk02);
}

void func_80105F40_mstory4(void) {
    D_80112128_mstory4 = InitEspriteSlot(func_8000B838_main(0x1D0012), 0, 0);
    func_8000BBD4_main(D_80112128_mstory4, 0xA0, 0x78);
    func_8000BC48_main(D_80112128_mstory4, 0x4000);
    D_80112122_mstory4 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_80112122_mstory4, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_80112122_mstory4, 2, 0);
    func_8001C814_main(D_80112122_mstory4, 1, 1);
}

void func_80106000_mstory4(void) {
    func_8001C258_main(D_80112122_mstory4, 4, 4);
    func_8000BB94_main(D_80112128_mstory4);
}

void func_80106034_mstory4(void) {
    func_8001C258_main(D_80112122_mstory4, 4, 0);
    func_8000BB54_main(D_80112128_mstory4);
}

void func_80106068_mstory4(omObjData *obj) {
    D_800CE17C_main[0] = D_80111AD0_mstory4.x;
    D_800CE17C_main[1] = D_80111AD0_mstory4.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_80111AD0_mstory4, &D_80111ADC_mstory4, &D_80111AE8_mstory4);
    Hu3DCamUpdateMtx(0);
}

void func_801060E8_mstory4(void) {
    D_80111AC0_mstory4 = 3;
}

void func_801060F8_mstory4(s32 arg0) {
    D_801121B4_mstory4 = arg0;
    D_80111AF4_mstory4 = 0;
    omAddPrcObj(func_80106134_mstory4, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80106134_mstory4);

s32 func_80106B20_mstory4(void) {
    return D_80111AF4_mstory4;
}

void func_80106B2C_mstory4(void) {
}

void func_80106B34_mstory4(void) {
}

void func_80106B3C_mstory4(s16 model, s16 anim, s16 frame) {
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

void func_80106C10_mstory4(void) {
    D_80112120_mstory4 = func_80060880_main(0xA0, 0xC2, 0x14);
    func_8005FE54_main(D_80112120_mstory4, 1 << D_80112124_mstory4);
    func_8005B6BC_main(D_80112120_mstory4, GwStory.unk1 + 0x1C00, 0);
}

void func_80106C78_mstory4(void) {
    func_8005D294_main(D_80112120_mstory4);
    func_80060C14_main(D_80112120_mstory4, 1);
}

void func_80106CA8_mstory4(void) {
    func_80060EA8_main(D_80112120_mstory4, 1);
}

void func_80106CCC_mstory4(s32 mess) {
    func_8005B43C_main(D_80112120_mstory4, mess, -1, -1);
    while (func_8005E0C0_main(D_80112120_mstory4) != 0) {
        HuPrcVSleep();
    }
}

void func_80106D20_mstory4(s32 mess) {
    func_8005B43C_main(D_80112120_mstory4, mess, -1, -1);
}

void func_80106D4C_mstory4(void) {
    while (func_8005E0C0_main(D_80112120_mstory4) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106D88_mstory4(s32 chr) {
    return (chr == GwStory.unk1) ? -1 : 0;
}

void func_80106DA0_mstory4(omObjData *obj, Vec *to, s32 frames) {
    func_80106DBC_mstory4(obj, to, frames, 1);
}

#ifdef NON_MATCHING
/* walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning
   it to face the way first when `turn` is set */
void func_80106DBC_mstory4(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80106DBC_mstory4);
#endif

void func_80106FF0_mstory4(omObjData *obj, Vec *to, s32 frames) {
    func_8010700C_mstory4(obj, to, frames, 1);
}

#ifdef NON_MATCHING
/* as func_80106DBC_mstory4, but the second model follows in 3D */
void func_8010700C_mstory4(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010700C_mstory4);
#endif

void func_80107220_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106DA0_mstory4(obj, &to, frames);
}

void func_8010724C_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106DBC_mstory4(obj, &to, frames, turn);
}

void func_8010727C_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106FF0_mstory4(obj, &to, frames);
}

void func_801072A8_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_8010700C_mstory4(obj, &to, frames, turn);
}

void func_801072D8_mstory4(omObjData *obj, Vec *to, s32 frames) {
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

void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_801072D8_mstory4(obj, &to, frames);
}

void func_801074AC_mstory4(s16 model) {
    HuPrcSleep(10);
    while (func_801074F8_mstory4(model) == 0) {
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
// matches; kept as asm only for the file-boundary padding after it (801075B0 starts a 16-byte aligned file, ROM 0x4C47E0)
s32 func_801074F8_mstory4(s16 model) {
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801074F8_mstory4);
#endif

ObPath *func_801075B0_mstory4(Vec *points, s16 flags) {
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
void func_801078B4_mstory4(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801078B4_mstory4);
#endif

void func_8010815C_mstory4(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* story step 0 of chapter 4: the scene's actor processes */
void func_8010818C_mstory4(void) {
    func_80106C10_mstory4();
    D_8011228C_mstory4 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80108288_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_801094DC_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109EA4_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A1C4_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A480_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A5AC_mstory4, 0x384, 0x800, 0);
    omAddPrcObj(func_8010ACF4_mstory4, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_8011228C_mstory4, 4, 4);
}

void func_80108280_mstory4(omObjData *obj) {
}

#ifdef NON_MATCHING
// masked 0 when func_80017AD8_main returns s16 (functions.us.h says u8: an andi 0xFF per call; as mstory1's twin, s1A.header.patch)
void func_80108288_mstory4(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(0x14, 6, 0x10, -1, NULL);
    D_801121C0_mstory4[0].obj = obj;
    D_801121C0_mstory4[0].unk08 = 0;
    D_801121C0_mstory4[0].unk0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
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
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x30));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 6, D_80111CAC_mstory4[chr]);
    func_8000B460_main(obj, 7, D_80111CCC_mstory4[chr]);
    func_8000B460_main(obj, 8, D_80111CEC_mstory4[chr]);
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 10, D_80111D0C_mstory4[chr]);
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 0x2C));
    func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x7A));
    func_8000B460_main(obj, 13, func_80017BB8_main(chr, 0x9B));
    D_80112290_mstory4[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80112290_mstory4[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80112290_mstory4[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80112290_mstory4[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_80112250_mstory4[0] = D_80111C70_mstory4[0];
    Hu3DModelPosSet(obj->model[1], D_80112250_mstory4[0].x, D_80112250_mstory4[0].y, D_80112250_mstory4[0].z);
    Hu3DModelPosSet(obj->model[2], D_80112250_mstory4[0].x, -5.0f, D_80112250_mstory4[0].z);
    Hu3DModelPosSet(obj->model[4], D_80112250_mstory4[0].x, D_80112250_mstory4[0].y, D_80112250_mstory4[0].z);
    omPrcSetDestructor(0, func_801086EC_mstory4);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[0].func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80108288_mstory4);
#endif

void func_801086EC_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C34_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C50_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C70_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C7C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C88_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C94_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CA0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CAC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CCC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CEC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D0C_mstory4);

const Vec D_80111D2C_mstory4 = { 0.0f, 0.0f, 0.0f };
const Vec D_80111D38_mstory4 = { 0.0f, 180.0f, 0.0f };
const Vec D_80111D44_mstory4 = { 0.0f, 90.0f, 0.0f }; /* unused */
const Vec D_80111D50_mstory4 = { 0.0f, -90.0f, 0.0f }; /* unused */
const Vec D_80111D5C_mstory4 = { -100.0f, 0.0f, 350.0f };
const Vec D_80111D68_mstory4 = { -100.0f, 0.0f, 150.0f };
const Vec D_80111D74_mstory4 = { 0.0f, 20.0f, 0.0f };
const Vec D_80111D80_mstory4 = { 0.0f, 0.0f, 0.0f };
const Vec D_80111D8C_mstory4 = { 0.0f, -26.565f, 0.0f };

/* actor 0's scene: the item hook, then the talk with actors 1 and 3 */
void func_801086F4_mstory4(omObjData *obj) {
    MsPart *part;
    omObjData *actor1;
    omObjData *actor3;
    s32 i;
    f32 scale;
    f32 frame;
    s16 model;

    HuPrcSleep(20);
    actor1 = D_801121C0_mstory4[1].obj;
    actor3 = D_801121C0_mstory4[3].obj;
    model = obj->model[1];
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107480_mstory4(obj, 0.0f, 110.0f, 0.0f, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[7]].unk02, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], model, "item_hook");
    func_8001C258_main(obj->model[3], 4, 0);
    func_801074AC_mstory4(model);
    func_8001C624_main(model, HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    func_801074AC_mstory4(model);
    while (!(D_801121C0_mstory4[4].unk08 & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_801121C0_mstory4[4].obj->model[1], 4, 4);
    func_8001C258_main(D_8011228E_mstory4, 4, 4);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x45);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x46);
    func_8002FD8C_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x47);
    part = func_8001D33C_main(model, "item_hook");
    i = 0;
    do {
        scale = sindf(i * 18.0f) * 0.8 + 1.0;
        part->unk1C.x = scale;
        part->unk1C.y = scale;
        part->unk1C.z = scale;
        part->unk40.x = scale;
        part->unk40.y = scale;
        part->unk40.z = scale;
        HuPrcVSleep();
        i++;
    } while (i < 10);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x47);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x46);
    func_8002FDCC_main(model, HmfModelData[model].unk02, "item_hook", 0x1B, 0x45);
    func_801060F8_mstory4(6);
    while (func_80106B20_mstory4() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A72);
    func_80106CA8_mstory4();
    func_80106B3C_mstory4(actor1->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[3]);
    D_801121C0_mstory4[1].func = func_80109CCC_mstory4;
    HuPrcSleep(12);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A73);
    func_80106CA8_mstory4();
    func_8001C5B4_main(model, obj->motion[6]);
    func_8001C814_main(model, 4, 4);
    func_8001C92C_main(model, 2.0f);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C5B4_main(model, obj->motion[7]);
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
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_801072D8_mstory4(obj, (Vec *)&D_80111D2C_mstory4, 10);
    HuAudSeqPlay(0x72);
    func_8001C624_main(model, HmfModelData[obj->motion[2]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[2]);
    func_801074AC_mstory4(model);
    CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    HuPrcSleep(60);
    func_801072D8_mstory4(actor3, (Vec *)&D_80111D8C_mstory4, 3);
    func_80106DA0_mstory4(actor3, (Vec *)&D_80111D5C_mstory4, 5);
    func_801072D8_mstory4(actor3, (Vec *)&D_80111D74_mstory4, 3);
    D_801121C0_mstory4[1].func = func_80109B5C_mstory4;
    HuAudFXPlay(0x219);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[3]);
    func_801072D8_mstory4(actor3, (Vec *)&D_80111D80_mstory4, 3);
    func_80106DBC_mstory4(actor3, (Vec *)&D_80111D68_mstory4, 10, 0);
    func_80107480_mstory4(actor1, 0.0f, 225.0f, 0.0f, 10);
    func_801074AC_mstory4(model);
    HuAudSeqPlay(0x26);
    func_801072D8_mstory4(obj, (Vec *)&D_80111D38_mstory4, 10);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    HuAudFXPlay(0x159);
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[2]].unk02, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A74);
    func_80106CA8_mstory4();
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[obj->motion[11]].unk02, 0, 10, 2);
    func_80106B3C_mstory4(actor1->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[0]);
    func_80107480_mstory4(actor1, 0.0f, 225.0f, 0.0f, 10);
    HuPrcSleep(50);
    func_80107480_mstory4(actor3, 30.0f, -20.0f, 0.0f, 10);
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[1]].unk02, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A76);
    func_80106CA8_mstory4();
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[0]].unk02, 0, 10, 2);
    func_80107480_mstory4(actor3, 0.0f, 0.0f, 0.0f, 5);
    HuPrcSleep(50);
    HuAudSeqPlay(0x29);
    HuAudFXPlay(0x159);
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[3]].unk02, 0, 10, 0);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A77);
    func_80106CA8_mstory4();
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[0]].unk02, 0, 10, 2);
    D_801121C0_mstory4[1].func = func_80109E3C_mstory4;
    func_8001C624_main(model, HmfModelData[obj->motion[12]].unk02, 0, 10, 0);
    func_801074AC_mstory4(model);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[2]].unk02, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A78);
    func_80106CA8_mstory4();
    func_8001C624_main(actor3->model[1], HmfModelData[actor3->motion[3]].unk02, 0, 10, 0);
    func_80107480_mstory4(actor3, 0.0f, 0.0f, 0.0f, 10);
    func_80106B3C_mstory4(actor1->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[3]);
    D_801121C0_mstory4[1].func = func_80109E68_mstory4;
    func_80107480_mstory4(obj, 0.0f, 0.0f, 0.0f, 10);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[1]);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(30);
    func_801060E8_mstory4();
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_801093B0_mstory4(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C624_main(model, HmfModelData[obj->motion[10]].unk02, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(80);
    func_8001C624_main(model, HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_80109474_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, (Vec *)&D_80111DB8_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_801094A8_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, (Vec *)&D_80111DC4_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DC4_mstory4);

/* actor 1 */
void func_801094DC_mstory4(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801121C0_mstory4[1].obj = obj;
    D_801121C0_mstory4[1].unk08 = 0;
    D_801121C0_mstory4[1].unk0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80112250_mstory4[1] = D_80111C70_mstory4[1];
    Hu3DModelPosSet(obj->model[1], D_80112250_mstory4[1].x, D_80112250_mstory4[1].y, D_80112250_mstory4[1].z);
    Hu3DModelPosSet(obj->model[2], D_80112250_mstory4[1].x, -5.0f, D_80112250_mstory4[1].z);
    data = DataRead(0xA007E);
    D_80112238_mstory4[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main((s16)D_80112238_mstory4[0], 1, 0);
    func_80032FF8_main((s16)D_80112238_mstory4[0], 0);
    D_80112248_mstory4 = func_80032694_main(HmfModelData[obj->model[1]].hmf, (s16)D_80112238_mstory4[0], 0, "c204n_0_DEF");
    D_80112238_mstory4[0] = D_800D1714_main[D_80112238_mstory4[0]].unk_00;
    data = DataRead(0xA0080);
    D_80112238_mstory4[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80112238_mstory4[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0084);
    D_80112238_mstory4[3] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[0]);
    omPrcSetDestructor(0, func_80109838_mstory4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80109838_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DDC_mstory4);

const Vec D_80111DE8_mstory4 = { 10.0f, 378.9f, 0.0f };

/* actor 1's scene: actor 3 talks, then actor 4 runs its action */
void func_80109840_mstory4(omObjData *obj) {
    D_801121C0_mstory4[0].func = func_801093B0_mstory4;
    D_801121C0_mstory4[3].func = func_8010A44C_mstory4;
    func_801072D8_mstory4(obj, (Vec *)&D_80111DE8_mstory4, 30);
    func_80106DA0_mstory4(obj, (Vec *)&D_80111E48_mstory4, 20);
    HuPrcSleep(30);
    func_801072D8_mstory4(obj, (Vec *)&D_80111E18_mstory4, 10);
    func_80106DA0_mstory4(obj, (Vec *)&D_80111E3C_mstory4, 15);
    func_80107480_mstory4(D_801121C0_mstory4[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_801072D8_mstory4(obj, (Vec *)&D_80111DF4_mstory4, 15);
    HuPrcSleep(20);
    func_801072D8_mstory4(obj, (Vec *)&D_80111E0C_mstory4, 10);
    func_801072D8_mstory4(D_801121C0_mstory4[3].obj, (Vec *)&D_80111E54_mstory4, 10);
    func_8001C624_main(D_801121C0_mstory4[3].obj->model[1], HmfModelData[D_801121C0_mstory4[3].obj->motion[1]].unk02, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A71);
    func_80106CA8_mstory4();
    func_8001C624_main(D_801121C0_mstory4[3].obj->model[1], HmfModelData[D_801121C0_mstory4[3].obj->motion[0]].unk02, 0, 10, 2);
    func_801072D8_mstory4(D_801121C0_mstory4[3].obj, (Vec *)&D_80111E60_mstory4, 10);
    D_801121C0_mstory4[4].func = func_8010A76C_mstory4;
    func_801072D8_mstory4(obj, (Vec *)&D_80111DDC_mstory4, 20);
    func_8001C624_main(D_801121C0_mstory4[0].obj->model[1], HmfModelData[D_801121C0_mstory4[0].obj->motion[13]].unk02, 0, 10, 2);
    while (!(D_801121C0_mstory4[4].unk08 & 2)) {
        HuPrcVSleep();
    }
    D_801121C0_mstory4[0].func = func_801086F4_mstory4;
    HuPrcSleep(40);
    func_801072D8_mstory4(obj, (Vec *)&D_80111E30_mstory4, 50);
    func_801072D8_mstory4(obj, (Vec *)&D_80111E24_mstory4, 40);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109AE0_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, (Vec *)&D_80111E84_mstory4, 10);
    func_80106DA0_mstory4(obj, (Vec *)&D_80111E78_mstory4, 50);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109B5C_mstory4(omObjData *obj) {
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
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[2]);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109CCC_mstory4(omObjData *obj) {
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
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[3]);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109E3C_mstory4(omObjData *obj) {
    HuPrcSleep(5);
    D_801121C0_mstory4[1].func = func_80109B5C_mstory4;
}

void func_80109E68_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 0.0f, 0.0f, 10);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

/* actor 2 */
void func_80109EA4_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801121C0_mstory4[2].obj = obj;
    D_801121C0_mstory4[2].unk08 = 0;
    D_801121C0_mstory4[2].unk0C = 0;
    obj->model[1] = func_8000B108_main(0x800A0, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    func_8000B460_main(obj, 0, 0x80000);
    func_8000B460_main(obj, 1, 0x1D0076);
    func_8000B460_main(obj, 2, 0x1D0077);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80112250_mstory4[2] = D_80111C70_mstory4[2];
    Hu3DModelPosSet(obj->model[1], D_80112250_mstory4[2].x, D_80112250_mstory4[2].y, D_80112250_mstory4[2].z);
    Hu3DModelPosSet(obj->model[2], D_80112250_mstory4[2].x, -5.0f, D_80112250_mstory4[2].z);
    omPrcSetDestructor(0, func_8010A05C_mstory4);
    D_801121C0_mstory4[2].func = func_8010A064_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A05C_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DF4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E0C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E18_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E24_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E30_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E3C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E48_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E54_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E60_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E78_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E84_mstory4);

const Vec D_80111E9C_mstory4 = { 200.0f, 0.0f, 1200.0f };
const Vec D_80111EA8_mstory4 = { 166.66666f, 0.0f, 150.0f }; /* unused */

/* actor 2: actor 1 talks, then actor 2 walks off */
void func_8010A064_mstory4(omObjData *obj) {
    HuPrcSleep(10);
    CharFXPlay(0x26B, 6);
    HuPrcSleep(30);
    func_80106B3C_mstory4(D_801121C0_mstory4[1].obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[1]);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A70);
    func_80106CA8_mstory4();
    func_80106B3C_mstory4(D_801121C0_mstory4[1].obj->model[1], D_80112248_mstory4, (s16)D_80112238_mstory4[0]);
    D_801121C0_mstory4[1].func = func_80109840_mstory4;
    CharFXPlay(0x286, 6);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    func_8010ABD0_mstory4(2, 0x28);
    func_80106DA0_mstory4(obj, (Vec *)&D_80111E9C_mstory4, 0x28);
    func_8010AC84_mstory4(2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801121C0_mstory4[2].func = func_80108280_mstory4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A1C4_mstory4);

void func_8010A3C8_mstory4(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A3D0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A44C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A480_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A5AC_mstory4);

void func_8010A764_mstory4(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A76C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010AA88_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010ABD0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010AC84_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010ACF4_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010AE20_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010B124_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010B9CC_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010B9FC_mstory4);

void func_8010BAF0_mstory4(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010BAF8_mstory4);

void func_8010BF3C_mstory4(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010BF44_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C080_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111ECC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111EE4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F08_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F10_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F1C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F28_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F34_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F54_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C0BC_mstory4);

void func_8010C54C_mstory4(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C554_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C590_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C7F8_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C8D0_mstory4);

void func_8010CAE8_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F80_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010CAF0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010CD40_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010CE90_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010CFE0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010D128_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F98_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FA8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FC8_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010D1A0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010E5C4_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010E7C0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EA34_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EC38_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EDA0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EE3C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EF00_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EF28_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EF50_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EF80_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F010_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F0A0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F0E0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F12C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F178_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FF8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80112008_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F1F4_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F588_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F660_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F910_mstory4);

void func_8000BB94_main(u16);           /* extern */
void func_8000BD94_main(u16, s32, s32); /* extern */
void func_8000BDDC_main(u16, s32);      /* extern */
void func_8000C184_main(u16);
void func_80017954_main(s16, s16, s16, s16);;
void Hu3DModelRotSet(s16, f32, f32, f32);                           /* extern */
void func_800E4F50_name_81(Addr *);                           /* extern */
void MBDBackCreate(s32, s32);                                       /* extern */
void func_80106C78_mstory4(void);                            /* extern */
void func_80106CA8_mstory4(void);                            /* extern */
void func_80106CCC_mstory4(s32);                             /* extern */
void func_8010724C_mstory4(omObjData *, f32, f32, f32, s32, s32); /* extern */
void func_80107480_mstory4(omObjData *, f32, f32, f32, s32);     /* extern */
void func_801074AC_mstory4(s16);                             /* extern */
void func_8010E5C4_mstory4(void *, f32, f32, f32, s32, s32); /* extern */
void func_8010EF28_mstory4(s32);                             /* extern */
void func_8010F0A0_mstory4(void);                            /* extern */
void func_8010F12C_mstory4(void);                            /* extern */
void func_80110270_mstory4(void);                            /* extern */
void func_80110DB0_mstory4(f32, f32, f32, s16);              /* extern */
void func_801118F8_mstory4(s32, s32);                        /* extern */
void func_8011196C_mstory4(s32);                             /* extern */
extern Addr D_128CC60;

extern s32 D_80111AC4_mstory4;
extern Vec D_80111AD0_mstory4;
extern Vec D_80111ADC_mstory4;
extern s32 D_80111B8C_mstory4;

typedef struct UnkModel {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ char unk_04[0x14];
    /* 0x18 */ omObjData *obj2;
} UnkModel; // sizeof 0x14

typedef struct Unk {
    s16 unk_00;
    char unk_02[6];
} Unk; // sizeof 0x8

extern Unk D_80112088_mstory4[6];
extern UnkModel D_801122A0_mstory4;

extern s16 D_80112330_mstory4;
extern s16 D_80112378_mstory4[];
extern s16 D_801123A4_mstory4;

#ifdef NON_MATCHING
void func_8010FC98_mstory4(void) {
    omObjData *temp_s5;
    omObjData *temp_s7;
    s32 temp_s4;
    s32 var_a3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0;
    u16 temp_fp;
    u16 *temp_s0;
    s32 i, j;

    temp_s5 = D_801122A0_mstory4.obj;
    temp_s7 = D_801122A0_mstory4.obj2;
    temp_fp = temp_s5->model[1];
    Hu3DCamSetPerspective(0, 40.0f, 80.0f, 8000.0f);

    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 190.0f;
    D_80111AD0_mstory4.z = 3770.0f;

    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = 130.0f;
    D_80111ADC_mstory4.z = 450.0f;

    D_80111AC4_mstory4 = 1;
    var_s3 = 0;
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackCreate(0x20, 0);
    func_8010EF28_mstory4(7);
    for (i = 0; i < 6; i++) {
        // if (D_80112088_mstory4[i].unk_00 > 0) {
        for (j = 0, temp_s4 = D_80112088_mstory4[i].unk_00; j < temp_s4; var_s3++, j++) {
            func_8000BD94_main(D_80112378_mstory4[var_s3], 0, 0);
            func_8000BDDC_main(D_80112378_mstory4[var_s3], 1);
            func_8000BB94_main(D_80112378_mstory4[var_s3]);
            func_8000C184_main(D_80112378_mstory4[var_s3]);
        }
        // }
    }

    HuSprKill(D_801123A4_mstory4);
    func_8010F12C_mstory4();
    func_8001C5B4_main(temp_s5->model[1], temp_s5->motion[13]);
    func_8001C814_main(temp_s5->model[1], 2, 2);
    Hu3DModelPosSet(temp_s5->model[1], 0.0f, 0.0f, 2220.0f);
    Hu3DModelPosSet(temp_s5->model[2], 0.0f, -5.0f, 2220.0f);
    Hu3DModelRotSet(temp_s5->model[1], 0, 0, 0);
    Hu3DModelScaleSet(temp_s5->model[1], 1.5f, 1.5f, 1.5f);
    Hu3DModelScaleSet(temp_s5->model[2], 1.5f, 1.5f, 1.5f);
    HuPrcVSleep();
    func_8010F0A0_mstory4();
    HuPrcSleep(30);
    func_8001C258_main(temp_s7->model[6], 4, 0);
    Hu3DModelPosSet(temp_s7->model[6], 0.0f, 1000.0f, 2120.0f);
    Hu3DModelRotSet(temp_s7->model[6], 0, 0, 0);
    Hu3DModelScaleSet(temp_s7->model[6], 1.5f, 1.5f, 1.5f);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2120.0f, 0x3C, 0);
    D_80111B8C_mstory4 = 0;
    HuPrcSleep(20);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[0]].unk02, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 180.0f, 0.0f, 8);
    HuPrcSleep(20);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7E);
    func_80106CA8_mstory4();
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[4]].unk02, 0, 0xA, 0);
    func_801074AC_mstory4(temp_fp);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[0]].unk02, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 0.0f, 0.0f, 0xA);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[11]].unk02, 0, 0xA, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_8010724C_mstory4(temp_s5, 0.0f, 0.0f, 2930.0f, 0x28, 0);
    func_8011196C_mstory4(0);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[0]].unk02, 0, 0xA, 2);
    HuPrcSleep(20);
    CharFXPlay(0x2C6, GwStory.unk1);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[2]].unk02, 0, 0xA, 0);
    func_80017954_main(temp_fp, 2, GwStory.unk1, D_80112330_mstory4);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2500.0f, 0x14, 0);
    func_801074AC_mstory4(temp_fp);
    func_8001C624_main(temp_fp, HmfModelData[temp_s5->motion[3]].unk02, 0, 0xA, 2);
    func_80110270_mstory4();
    HuPrcVSleep();
    for (i = 0; i < 4; i++) {
        func_80110DB0_mstory4(0.0f, 400.0f, 2500.0f, i << 3);
        HuPrcSleep(2);
    }
}

#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010FC98_mstory4);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110270_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110394_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110460_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110494_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801104D4_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110500_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110528_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110724_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110888_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801108FC_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801109EC_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110B4C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110BB4_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110D5C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110DB0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110E3C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80111430_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80111740_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801118F8_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8011196C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801119C0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80112088_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_8011208C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_801120B8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_801120D4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_801120F4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80112114_mstory4);
