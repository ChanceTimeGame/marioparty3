#include "common.h"

// story f1
/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry): segment i runs
   from points[i] to points[i + 1] and covers [segs[i].start, segs[i].end] of the path's
   length (0..1). flags & 1: closed (the last segment returns to points[0]). Same as mstory1's. */
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

/* a chapter 2 actor: its object and the action its process runs every frame */
typedef struct StoryActor2 {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C; /* 1: walking (footstep sounds) */
    /* 0x10 */ s32 unk10; /* footstep sound */
} StoryActor2; /* size = 0x14 */

typedef struct StoryMotions {
    s32 v[8][3]; /* per character: three motion files of directory 0x1D */
} StoryMotions;

typedef struct StoryTargets {
    Vec v[6];
} StoryTargets;

typedef struct StoryRot4 {
    Vec v[4];
} StoryRot4;

typedef struct StoryPads {
    s16 v[4];
} StoryPads;

extern TexAnimSlot *D_800D1714_main;
extern f32 D_800CE17C_main[];
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, s32);
s32 func_80050064_main(s32 write);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
void func_800E989C_minigame(void);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BEAC_main(u16 spriteId, s32 arg1, s32 arg2, s32 arg3);
#include "mallocblock.h"

extern Vec D_8011B920_mstory2; /* camera position */
extern Vec D_8011B92C_mstory2; /* camera target */
extern Vec D_8011B938_mstory2; /* camera up */
extern s16 D_8011B944_mstory2; /* 1: the scene was seen before, A skips it */
extern s16 D_8011B946_mstory2; /* main object state */
extern s16 D_8011B948_mstory2; /* 1: leave to the minigame */
extern s32 D_8011B94C_mstory2;
extern void (*const D_8011BDE0_mstory2[5])(void);
extern const s32 D_8011BDF4_mstory2[5];
extern const StoryPads D_8011BE1C_mstory2;
extern const StoryPads D_8011BE24_mstory2;
extern const s32 D_8011BE2C_mstory2[7]; /* board icon sprites */
extern const s16 D_8011BE48_mstory2[7][2]; /* board icon positions */
extern s16 D_8011C640_mstory2; /* story step (GwPlayer[0].coin, at most 4) */
extern s16 D_8011C642_mstory2; /* the controller that drives the story messages */
extern s16 D_8011C644_mstory2; /* message window */
extern u16 D_8011C646_mstory2; /* background sprite */
extern s16 D_8011C648_mstory2; /* background model */
extern s16 D_8011C650_mstory2[8]; /* chapter map: [0] the map, [1..7] the board icons */
extern s16 D_8011C660_mstory2[8]; /* the stars around this chapter's icon */
extern s16 D_8011C670_mstory2; /* frame sprite */
extern s32 D_8011C674_mstory2; /* the chapter the map shows */
void func_80106D50_mstory2(void);
extern const StoryRot4 D_8011BEB0_mstory2;
extern StoryActor2 D_8011C680_mstory2[6];
extern s16 D_8011C75A_mstory2; /* shadow model */
extern s16 D_8011C75C_mstory2; /* the story character (GwStory.unk1) */
extern s16 D_8011C75E_mstory2; /* the partner character */
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_80105FBC_mstory2(void);
void func_801060A4_mstory2(void);
void func_801060D4_mstory2(void);
void func_801060F8_mstory2(s32 mess);
void func_8010614C_mstory2(s32 mess);
void func_801072AC_mstory2(s16 model);
void func_801076DC_mstory2(omObjData *a, omObjData *b);
void func_801088A4_mstory2(void);
void func_8010889C_mstory2(omObjData *obj);
void func_80108A3C_mstory2(void);
void func_80108AB0_mstory2(omObjData *unused);
void func_80108C40_mstory2(omObjData *obj);
void func_80109D04_mstory2(void);
void func_8010AC1C_mstory2(void);
void func_8010B7B8_mstory2(void);
void func_8010C038_mstory2(void);
void func_8010C1E4_mstory2(void);
void func_8010C398_mstory2(void);
void func_8010A5FC_mstory2(omObjData *obj);
void func_80106D58_mstory2(s16 model, s16 anim, s16 frame);
void func_801073A4_mstory2(omObjData *obj, f32 speed, s16 frames);
extern s16 D_8011C74A_mstory2[3]; /* actor 0's texture animations */
extern s16 D_8011C750_mstory2;
extern const StoryTargets D_8011BEE0_mstory2;
extern Vec D_8011B950_mstory2[]; /* paths: Vec lists ended by { 9999, 9999, 9999 } */
extern Vec D_8011B980_mstory2[];
extern Vec D_8011B9C8_mstory2;
extern Vec D_8011B9D4_mstory2;
extern Vec D_8011B9E0_mstory2;
extern Vec D_8011BA1C_mstory2;
extern Vec D_8011BA28_mstory2;
extern Vec D_8011BA34_mstory2;
extern s16 D_8011C740_mstory2[3]; /* actor 2's texture animations */
extern s16 D_8011C746_mstory2;
extern s16 D_8011C748_mstory2; /* 1 while actor 3 turns round */
void func_800138EC_main(s16 model, u16 mask, u16 flags);
ObPath *func_80107B90_mstory2(Vec *points, s16 flags);
void func_80107E94_mstory2(ObPath *path, f32 t, Vec *out);
void func_8010873C_mstory2(ObPath *path);
void func_80107824_mstory2(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106E2C_mstory2(omObjData *obj, Vec *to, s32 frames);
void func_80105EA4_mstory2(void);
void func_8010622C_mstory2(void);
void func_8010A298_mstory2(omObjData *obj);
void func_8010A3B4_mstory2(omObjData *obj);
void func_8010A784_mstory2(omObjData *obj);
void func_8010A9F0_mstory2(omObjData *obj);
void func_8010B110_mstory2(omObjData *obj);
void func_8010B200_mstory2(omObjData *obj);
void func_8010B46C_mstory2(omObjData *obj);
void func_8010B688_mstory2(omObjData *obj);
void func_8010B738_mstory2(omObjData *obj);
void func_8010BACC_mstory2(omObjData *obj);
void func_8010BD04_mstory2(omObjData *obj);
void func_8010BDC4_mstory2(omObjData *obj);
void func_8010C018_mstory2(omObjData *obj);
void func_8010C328_mstory2(omObjData *obj);
void func_8010C348_mstory2(omObjData *obj);
extern const StoryMotions D_8011BF28_mstory2;
extern char *D_8011BA40_mstory2[8]; /* per character: its model's texture name */
extern s32 D_800A178C_main[][6]; /* per character: [0] its file directory */
void func_80032FC0_main(s16, s32, s32);
s16 func_800329B4_main(void *);
void func_8010A290_mstory2(void);
extern s16 D_8011C756_mstory2;
extern s16 D_8011C758_mstory2;
extern s16 D_8011CA80_mstory2[4]; /* play order: player per slot */

void func_801059BC_mstory2(void);
void func_801059E4_mstory2(omObjData *obj);
void func_80105A64_mstory2(void);
void func_80105B44_mstory2(void);
void func_80105B60_mstory2(void);
void func_80105C1C_mstory2(void);
void func_80105DB4_mstory2(omObjData *obj);
void func_80105EC4_mstory2(omObjData *obj);
void func_80105F4C_mstory2(omObjData *obj);
void func_80105F94_mstory2(omObjData *obj);
void func_801063B0_mstory2(void);
void func_801064AC_mstory2(void);
void func_80106E48_mstory2(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_801070D8_mstory2(omObjData *obj, Vec *to, s32 frames);
s32 func_801072F8_mstory2(s16 model);
void func_8010876C_mstory2(void);
void func_8010D0EC_mstory2(void);
void func_80111D7C_mstory2(void);
void func_80116A3C_mstory2(void);
void func_8011AAE0_mstory2(void);
// end story f1

void func_801059A0_mstory2(void) {
    func_80105C1C_mstory2();
}

void func_801059BC_mstory2(void) {
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_801059E4_mstory2(omObjData *obj) {
    D_800CE17C_main[0] = D_8011B920_mstory2.x;
    D_800CE17C_main[1] = D_8011B920_mstory2.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_8011B920_mstory2, &D_8011B92C_mstory2, &D_8011B938_mstory2);
    Hu3DCamUpdateMtx(0);
}

void func_80105A64_mstory2(void) {
    omObjData *obj;

    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 35.0f, 80.0f, 8000.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_801059E4_mstory2);
    omSetStatBit(obj, 0xA0);
    func_801059E4_mstory2(obj);
}

void func_80105B44_mstory2(void) {
    func_8005A6B0_main();
}

void func_80105B60_mstory2(void) {
    s16 n = 0;
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayer[j].group) {
                D_8011CA80_mstory2[n++] = j;
            }
            if (n >= 4) {
                break;
            }
        }
        if (n >= 4) {
            break;
        }
    }
}

void func_80105C1C_mstory2(void) {
    func_800142A0_main(0x20);
    omInitObjMan(0x20, 0x20);
    func_801059BC_mstory2();
    func_80105A64_mstory2();
    func_80105B44_mstory2();
    func_80105B60_mstory2();
    D_8011C640_mstory2 = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 5) {
        D_8011C640_mstory2 = 4;
    }
    omAddObj(0, 0, 0, -1, func_80105DB4_mstory2);
    omAddObj(0, 0, 0, -1, func_80105F94_mstory2);
    func_801063B0_mstory2();
    if (D_8011C640_mstory2 != 0) {
        if (_CheckFlag(D_8011BDF4_mstory2[D_8011C640_mstory2]) != 0) {
            D_8011B944_mstory2 = 1;
        } else {
            _SetFlag(D_8011BDF4_mstory2[D_8011C640_mstory2]);
        }
    }
    for (D_8011C642_mstory2 = 0; D_8011C642_mstory2 < 4; D_8011C642_mstory2++) {
        if (CheckControllerRead(D_8011C642_mstory2) != 0) {
            break;
        }
    }
    if (D_8011C642_mstory2 >= 4) {
        D_8011C642_mstory2 = 0;
    }
    D_8011BDE0_mstory2[D_8011C640_mstory2]();
    WipeCreateIn(2, 0x10);
}

/* the scene for each story step (GwPlayer[0].coin, 0..4), and the flag set once it has been seen */
void (*const D_8011BDE0_mstory2[5])(void) = {
    func_8011AAE0_mstory2, func_8010876C_mstory2, func_8010D0EC_mstory2, func_80111D7C_mstory2, func_80116A3C_mstory2,
};
const s32 D_8011BDF4_mstory2[5] = { -1, 0x33, 0x35, 0x37, 0x39 };

void func_80105DB4_mstory2(omObjData *obj) {
    s16 state = D_8011B946_mstory2;
    s16 seq;

    switch (state) {
    case 0:
        seq = 0x26;
        if (D_8011C640_mstory2 == 0) {
            seq = 0x2C;
        }
        state++;
        HuAudSeqPlay(seq);
        break;
    case 1:
        if (WipeStatGet() == 0) {
            state++;
        }
        break;
    case 2:
        if (D_8011C640_mstory2 != 0 && D_8011B944_mstory2 == 1) {
            if (D_800D5558_main[D_8011C642_mstory2] & 0x1000) {
                state++;
            }
        }
        break;
    case 4:
        D_8011B948_mstory2 = 1;
    case 3:
    default:
        obj->func = func_80105F4C_mstory2;
        break;
    }
    D_8011B946_mstory2 = state;
}

void func_80105EA4_mstory2(void) {
    D_8011B946_mstory2 = 3;
}

void func_80105EB4_mstory2(void) {
    D_8011B946_mstory2 = 4;
}

void func_80105EC4_mstory2(omObjData *obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        func_8005F524_main();
        if (D_8011B948_mstory2 == 0) {
            if (D_8011C640_mstory2 != 0) {
                func_80050064_main(1);
            }
            omOvlReturnEx(1);
        } else if (D_8011B948_mstory2 == 1) {
            func_800E989C_minigame();
        }
    }
}

void func_80105F4C_mstory2(omObjData *obj) {
    WipeCreateOut(2, 0x14);
    HuAudSeqFadeOut(0x1E);
    func_8004AB0C_main(0x1E);
    obj->func = func_80105EC4_mstory2;
}

void func_80105F94_mstory2(omObjData *obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80105F4C_mstory2;
    }
}

void func_80105FBC_mstory2(void) {
    StoryPads slots = D_8011BE1C_mstory2;
    StoryPads masks = D_8011BE24_mstory2;

    D_8011C644_mstory2 = func_80060880_main(0xA0, 0xC2, 0x14);
    slots.v[D_8011C642_mstory2] = -1;
    func_8005B63C_main(D_8011C644_mstory2, 2, 0);
    func_8005FE54_main(D_8011C644_mstory2, masks.v[D_8011C642_mstory2]);
    func_8005F744_main(slots.v[0], slots.v[1], slots.v[2], slots.v[3]);
}

void func_801060A4_mstory2(void) {
    func_8005D294_main(D_8011C644_mstory2);
    func_80060C14_main(D_8011C644_mstory2, 1);
}

void func_801060D4_mstory2(void) {
    func_80060EA8_main(D_8011C644_mstory2, 1);
}

void func_801060F8_mstory2(s32 mess) {
    func_8005B43C_main(D_8011C644_mstory2, mess, -1, -1);
    while (func_8005E0C0_main(D_8011C644_mstory2) != 0) {
        HuPrcVSleep();
    }
}

void func_8010614C_mstory2(s32 mess) {
    func_8005B43C_main(D_8011C644_mstory2, mess, -1, -1);
    func_8005B6BC_main(D_8011C644_mstory2, GwStory.unk1 + 0x1C00, 0);
    while (func_8005E0C0_main(D_8011C644_mstory2) != 0) {
        HuPrcVSleep();
    }
}

s16 func_801061BC_mstory2(void) {
    return func_8005E1D8_main(D_8011C644_mstory2, 0, 1);
}

void func_801061EC_mstory2(void) {
    func_8000BB54_main(D_8011C646_mstory2);
}

void func_8010620C_mstory2(void) {
    func_8000BB94_main(D_8011C646_mstory2);
}

void func_8010622C_mstory2(void) {
    HuAudFXPlay(0x216);
    func_8001C814_main(D_8011C648_mstory2, 4, 0);
    func_8001C814_main(D_8011C648_mstory2, 1, 0);
    func_8001C6A8_main(D_8011C648_mstory2, 0.0f);
    func_8001C92C_main(D_8011C648_mstory2, 2.0f);
}

void func_80106290_mstory2(void) {
    func_8001C814_main(D_8011C648_mstory2, 4, 4);
    func_8001C814_main(D_8011C648_mstory2, 1, 0);
    func_8001C6A8_main(D_8011C648_mstory2, HmfModelData[D_8011C648_mstory2].unk40);
}

void func_801062F4_mstory2(void) {
    s16 i = 0;

    HmfModelData[D_8011C648_mstory2].rot.y += -10.6f;
    do {
        HmfModelData[D_8011C648_mstory2].rot.x += 17.84f;
        HuPrcVSleep();
        i++;
    } while (i < 5);
}

void func_801063B0_mstory2(void) {
    D_8011C646_mstory2 = InitEspriteSlot(func_8000B838_main(0x1D0012), 0, 0);
    func_8000BBD4_main(D_8011C646_mstory2, 0xA0, 0x78);
    func_8000BC48_main(D_8011C646_mstory2, 0x4000);
    D_8011C648_mstory2 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_8011C648_mstory2, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_8011C648_mstory2, 2, 0);
    func_8001C814_main(D_8011C648_mstory2, 1, 1);
}

void func_80106470_mstory2(s32 arg0) {
    D_8011C674_mstory2 = arg0;
    D_8011B94C_mstory2 = 0;
    omAddPrcObj(func_801064AC_mstory2, 0x1000, 0x800, 0);
}

/* the chapter map: the board icons cleared so far, a ring of stars around this chapter's
   board, fades in and out of the frame sprite; sets D_8011B94C_mstory2 when done */
void func_801064AC_mstory2(void) {
    void *data;
    s32 i;
    s32 j;
    s32 wait;
    f32 x;
    f32 y;
    f32 a;
    f32 alpha;

    D_8011C650_mstory2[0] = InitEspriteSlot(func_8000B838_main(0x1D0001), 0, 0);
    func_8000BBD4_main(D_8011C650_mstory2[0], 0xA0, 0x78);
    func_8000BB94_main(D_8011C650_mstory2[0]);
    for (i = 0; i < 7; i++) {
        D_8011C650_mstory2[i + 1] = InitEspriteSlot(func_8000B838_main(D_8011BE2C_mstory2[i]), 0, 0);
        func_8000BBD4_main(D_8011C650_mstory2[i + 1], D_8011BE48_mstory2[i][0] + 0x30, D_8011BE48_mstory2[i][1] + 0x30);
        func_8000BC48_main(D_8011C650_mstory2[i + 1], 8);
        func_8000BB94_main(D_8011C650_mstory2[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        D_8011C660_mstory2[i] = InitEspriteSlot(func_80055810_main(data), 0, 1);
        x = D_8011BE48_mstory2[D_8011C674_mstory2][0] + 0x30;
        y = D_8011BE48_mstory2[D_8011C674_mstory2][1] + 0x30;
        a = i * 45.0f;
        x += cosdf(a) * 32.0f;
        y -= sindf(a) * 32.0f;
        func_8000BBD4_main(D_8011C660_mstory2[i], x, y);
        func_8000BC48_main(D_8011C660_mstory2[i], 0x1000);
        func_8000BEAC_main(D_8011C660_mstory2[i], 0xFF, 0xFF, 0xC0);
        func_8000BC48_main(D_8011C660_mstory2[i], 8);
        func_8000BE5C_main(D_8011C660_mstory2[i], 1.5f, 1.5f);
        func_8000BBFC_main(D_8011C660_mstory2[i], 0xFF);
        func_8000BB94_main(D_8011C660_mstory2[i]);
    }
    HuMemMemoryFreePerm(data);
    D_8011C670_mstory2 = InitEspriteSlot(func_8000B838_main(0x1D0000), 0, 0);
    func_8000BBD4_main(D_8011C670_mstory2, 0xA0, 0x78);
    func_8000BE5C_main(D_8011C670_mstory2, 40.0f, 30.0f);
    func_8000BC48_main(D_8011C670_mstory2, 0);
    func_8000BB94_main(D_8011C670_mstory2);
    omPrcSetDestructor(0, func_80106D50_mstory2);
    func_8000BB54_main(D_8011C670_mstory2);
    func_8000BBFC_main(D_8011C670_mstory2, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_8011C670_mstory2, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_8011C670_mstory2, 0x100);
    for (i = 0; i < D_8011C674_mstory2; i++) {
        func_8000BB54_main(D_8011C650_mstory2[i + 1]);
    }
    func_8010620C_mstory2();
    func_8000BB54_main(D_8011C650_mstory2[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_8011C670_mstory2, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_8011C670_mstory2);
    func_8000BBFC_main(D_8011C650_mstory2[D_8011C674_mstory2 + 1], 0);
    func_8000BB54_main(D_8011C650_mstory2[D_8011C674_mstory2 + 1]);
    for (alpha = 0.0f, j = 0; j < 20; j++) {
        alpha += 12.75f;
        func_8000BBFC_main(D_8011C650_mstory2[D_8011C674_mstory2 + 1], alpha);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_8011C650_mstory2[D_8011C674_mstory2 + 1], 0xFF);
    func_8000BE5C_main(D_8011C650_mstory2[D_8011C674_mstory2 + 1], 1.0f, 1.0f);
    for (i = 0; i < 8; i++) {
        func_8000BD94_main(D_8011C660_mstory2[i], 0, 0);
        func_8000BDDC_main(D_8011C660_mstory2[i], 1);
        func_8000BB54_main(D_8011C660_mstory2[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        func_8000BB94_main(D_8011C660_mstory2[i]);
    }
    wait = 60;
    if (D_8011C674_mstory2 == 6) {
        HuPrcSleep(40);
        func_8000BB54_main(D_8011C670_mstory2);
        func_8000BBFC_main(D_8011C670_mstory2, 0);
        for (i = 0; i < 5; i++) {
            func_8000BBFC_main(D_8011C670_mstory2, i * 0.125f * 255.0f);
            HuPrcVSleep();
        }
        func_8000BBFC_main(D_8011C670_mstory2, 0x100);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            func_8000BBFC_main(D_8011C670_mstory2, 255.0f - i * 0.125f * 255.0f);
            HuPrcVSleep();
        }
        func_8000BB94_main(D_8011C670_mstory2);
        wait = 80;
    }
    HuPrcSleep(wait);
    func_8000BB54_main(D_8011C670_mstory2);
    func_8000BBFC_main(D_8011C670_mstory2, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_8011C670_mstory2, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_8011C670_mstory2, 0x100);
    func_8000BB94_main(D_8011C650_mstory2[D_8011C674_mstory2 + 1]);
    func_8000BB94_main(D_8011C650_mstory2[0]);
    func_801061EC_mstory2();
    HuPrcSleep(30);
    for (i = 0; i < D_8011C674_mstory2; i++) {
        func_8000BB94_main(D_8011C650_mstory2[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_8011C670_mstory2, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_8011C670_mstory2);
    D_8011B94C_mstory2 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_80106D44_mstory2(void) {
    return D_8011B94C_mstory2;
}

void func_80106D50_mstory2(void) {
}

void func_80106D58_mstory2(s16 model, s16 anim, s16 frame) {
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

void func_80106E2C_mstory2(omObjData *obj, Vec *to, s32 frames) {
    func_80106E48_mstory2(obj, to, frames, 1);
}

#ifdef NON_MATCHING
/* walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning
   it to face the way first when `turn` is set */
void func_80106E48_mstory2(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80106E48_mstory2);
#endif

void func_8010707C_mstory2(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106E2C_mstory2(obj, &to, frames);
}

void func_801070A8_mstory2(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106E48_mstory2(obj, &to, frames, turn);
}

void func_801070D8_mstory2(omObjData *obj, Vec *to, s32 frames) {
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

void func_80107280_mstory2(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_801070D8_mstory2(obj, &to, frames);
}

void func_801072AC_mstory2(s16 model) {
    HuPrcSleep(10);
    while (func_801072F8_mstory2(model) == 0) {
        HuPrcVSleep();
    }
}

s32 func_801072F8_mstory2(s16 model) {
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

void func_801073A4_mstory2(omObjData *obj, f32 speed, s16 frames) {
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

void func_80107540_mstory2(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(HmfModelData[obj->model[1]].rot.y);
    dz = speed * cosdf(HmfModelData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        HmfModelData[obj->model[2]].pos.x = HmfModelData[obj->model[1]].pos.x -= dx;
        HmfModelData[obj->model[2]].pos.z = HmfModelData[obj->model[1]].pos.z -= dz;
        HuPrcVSleep();
    }
}

void func_801076DC_mstory2(omObjData *a, omObjData *b) {
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

// the frame count is converted once and kept (retail converts it again for the first loop test), as
// func_80106E48_mstory2: register/scheduling residue only
#ifdef NON_MATCHING
/* walks obj's model to `to` as func_80106E48_mstory2 does, but from frame 50 on the step grows
   by 1/90 of its first size every frame; it stops early once x has reached to->x */
void func_80107824_mstory2(omObjData *obj, Vec *to, s32 frames, s32 turn) {
    Vec start;
    Vec delta;
    Vec step;
    Vec pos;
    Vec accel;
    s16 model;
    f32 t;
    f32 sx;
    f32 sy;
    f32 sz;

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
    sx = delta.x / frames;
    accel.x = sx / 90.0f;
    sy = delta.y / frames;
    accel.y = sy / 90.0f;
    sz = delta.z / frames;
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
            pos.x = (step.x += accel.x) + pos.x;
            pos.y = (step.y += accel.y) + pos.y;
            pos.z = (step.z += accel.z) + pos.z;
        }
        if (pos.x <= to->x) {
            pos.x = to->x;
            pos.y = to->y;
            pos.z = to->z;
            Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
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
    Hu3DModelPosSet(model, to->x, to->y, to->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], to->x, to->y - 5.0f, to->z);
    }
    HuPrcVSleep();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80107824_mstory2);
#endif

ObPath *func_80107B90_mstory2(Vec *points, s16 flags) {
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
void func_80107E94_mstory2(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80107E94_mstory2);
#endif

void func_8010873C_mstory2(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

// register residue only: retail keeps the partner in v0, KMC picks a0 (masked 0)
#ifdef NON_MATCHING
/* story step 1 (chapter 2): the scene's processes */
void func_8010876C_mstory2(void) {
    s16 partner;

    D_8011C75C_mstory2 = GwStory.unk1;
    partner = 4;
    if (D_8011C75C_mstory2 == 4) {
        partner = 1;
    }
    D_8011C75E_mstory2 = partner;
    func_80105FBC_mstory2();
    D_8011C75A_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80109D04_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010AC1C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B7B8_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C038_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C398_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_80108A3C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C1E4_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_801088A4_mstory2, 0x1001, 0x1000, 0);
    func_8001C258_main(D_8011C75A_mstory2, 4, 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010876C_mstory2);
#endif

void func_8010889C_mstory2(omObjData *obj) {
}

/* footstep sounds of actors 0 and 1 (actor 1's panned by its depth) on their walk loop's frame 0 */
void func_801088A4_mstory2(void) {
    s16 se;
    s8 pan;

    while (TRUE) {
        if (D_8011C680_mstory2[0].unk0C == 1 && HmfModelData[D_8011C680_mstory2[0].obj->model[1]].unk40 == 0.0f) {
            CharFXPlay(D_8011C680_mstory2[0].unk10, D_8011C75C_mstory2);
        }
        if (D_8011C680_mstory2[1].unk0C == 1 && HmfModelData[D_8011C680_mstory2[1].obj->model[1]].unk40 == 0.0f) {
            se = CharFXPlay(D_8011C680_mstory2[1].unk10, D_8011C75E_mstory2);
            if (HmfModelData[D_8011C680_mstory2[1].obj->model[1]].pos.z <= 0.0f) {
                pan = HmfModelData[D_8011C680_mstory2[1].obj->model[1]].pos.z / 15.0f + 127.0f;
            } else {
                pan = 127;
            }
            func_8004AAD0_main(se, pan);
        }
        HuPrcVSleep();
    }
}

void func_80108A3C_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C680_mstory2[5].obj = obj;
    D_8011C680_mstory2[5].unk08 = 0;
    D_8011C680_mstory2[5].func = func_80108AB0_mstory2;
    while (TRUE) {
        D_8011C680_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

void func_80108AB0_mstory2(omObjData *unused) {
    StoryRot4 rot = D_8011BEB0_mstory2;

    HuPrcSleep(40);
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &rot.v[0], 10);
    func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &rot.v[1], 10);
    HuAudFXPlay(0x159);
    func_8001C624_main(D_8011C680_mstory2[3].obj->model[1], HmfModelData[D_8011C680_mstory2[3].obj->motion[1]].unk02, 0, 10, 2);
    func_801060A4_mstory2();
    if (D_8011C75C_mstory2 != 4) {
        func_8010614C_mstory2(0x5A0F);
    } else {
        func_801060F8_mstory2(0x5B00);
    }
    func_801060D4_mstory2();
    func_8001C624_main(D_8011C680_mstory2[3].obj->model[1], HmfModelData[D_8011C680_mstory2[3].obj->motion[0]].unk02, 0, 10, 2);
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &rot.v[2], 10);
    func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &rot.v[3], 10);
    D_8011C680_mstory2[5].func = func_80108C40_mstory2;
}

/* actor 5's main script for chapter 2: the hook item flies in and catches actor 0's model, the
   characters talk and walk, then the item flies off again and the scene ends */
void func_80108C40_mstory2(omObjData *unused) {
    s16 i = 0;
    Vec pos;
    ObPath *path[2];
    StoryTargets targets = D_8011BEE0_mstory2;
    s16 j;
    s16 k;
    f32 t;
    s32 wait;

    func_8001C258_main(D_8011C680_mstory2[4].obj->model[1], 4, 0);
    func_8001C258_main(D_8011C680_mstory2[4].obj->model[2], 4, 0);
    func_800138EC_main(D_8011C680_mstory2[4].obj->model[2], 1, 1);
    HuAudFXPlay(0x215);
    path[0] = func_80107B90_mstory2(D_8011B950_mstory2, 0);
    for (j = 0; j < 40.0f; j++) {
        if (j == 30) {
            func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[9]].unk02, 0, 10, 2);
        }
        t = j * 0.025f;
        func_80107E94_mstory2(path[0], t * t, &pos);
        Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010873C_mstory2(path[0]);
    D_8011C680_mstory2[0].func = func_8010A298_mstory2;
    while (TRUE) {
        if (D_8011C680_mstory2[0].unk08 == 1) {
            pos.x -= 0.19999999f;
            pos.y -= 2.0f;
            pos.z += 1.0f;
            Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
            func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
            if (i++ == 30.0f) {
                i = 0;
                break;
            }
        }
        HuPrcVSleep();
    }
    func_8004AAD0_main(CharFXPlay(0x2BD, D_8011C75E_mstory2), 0x50);
    if (D_8011C75C_mstory2 != 4) {
        func_801060A4_mstory2();
        func_801060F8_mstory2(0x5A11);
        func_801060D4_mstory2();
    } else {
        HuPrcSleep(30);
    }
    func_8001C258_main(D_8011C680_mstory2[1].obj->model[1], 4, 0);
    func_8001C258_main(D_8011C680_mstory2[1].obj->model[2], 4, 0);
    func_8010622C_mstory2();
    HuPrcSleep(10);
    D_8011C680_mstory2[0].func = func_8010A3B4_mstory2;
    D_8011C680_mstory2[2].func = func_8010BACC_mstory2;
    while (TRUE) {
        pos.x += 1.0f;
        pos.y += 10.0f;
        pos.z -= 5.0f;
        Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        if (i++ == 6.0f) {
            break;
        }
        HuPrcVSleep();
    }
    D_8011B980_mstory2[0].x = pos.x;
    D_8011B980_mstory2[0].y = pos.y;
    D_8011B980_mstory2[0].z = pos.z;
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &D_8011B9C8_mstory2, 5);
    D_8011C680_mstory2[3].func = func_8010C328_mstory2;
    while (TRUE) {
        if (D_8011C680_mstory2[2].unk08 == 5) {
            break;
        }
        HuPrcVSleep();
    }
    func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
    HuPrcSleep(30);
    D_8011C680_mstory2[1].unk0C = 1;
    D_8011C680_mstory2[1].unk10 = 0x28;
    func_8001C92C_main(D_8011C680_mstory2[0].obj->model[1], 0.25f);
    func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[10]].unk02, 0, 10, 2);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[2]].unk02, 0, 10, 2);
    func_80107824_mstory2(D_8011C680_mstory2[1].obj, &targets.v[0], 180, 1);
    D_8011C680_mstory2[1].unk0C = 0;
    func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C92C_main(D_8011C680_mstory2[0].obj->model[1], 1.0f);
    func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[3]].unk02, 0, 10, 2);
    HuPrcSleep(60);
    func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
    func_801070D8_mstory2(D_8011C680_mstory2[1].obj, &D_8011B9D4_mstory2, 5);
    if (D_8011C75C_mstory2 != 4) {
        D_8011C680_mstory2[1].func = func_8010B688_mstory2;
        func_801060A4_mstory2();
        func_801060F8_mstory2(0x5A12);
        func_801060D4_mstory2();
        func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
        D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    } else {
        for (j = 0; j < 2; j++) {
            func_80106E48_mstory2(D_8011C680_mstory2[2].obj, &targets.v[3], 15, 0);
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[1]].unk02, 0, 10, 2);
            func_801070D8_mstory2(D_8011C680_mstory2[1].obj, &D_8011BA1C_mstory2, 10);
            func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[5]].unk02, 0, 10, 0);
            HuPrcSleep(10);
            func_8001C624_main(D_8011C680_mstory2[2].obj->model[1], HmfModelData[D_8011C680_mstory2[2].obj->motion[2]].unk02, 0, 10, 2);
            func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
            if (j == 0) {
                func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[5]].unk02, 0, 10, 0);
                func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
            }
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
            func_8001C624_main(D_8011C680_mstory2[2].obj->model[1], HmfModelData[D_8011C680_mstory2[2].obj->motion[0]].unk02, 0, 10, 2);
            D_8011C680_mstory2[2].func = func_8010889C_mstory2;
            func_80106E2C_mstory2(D_8011C680_mstory2[2].obj, &targets.v[4], 8);
            func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &D_8011B9E0_mstory2, 10);
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[1]].unk02, 0, 10, 2);
            func_801070D8_mstory2(D_8011C680_mstory2[1].obj, &D_8011B9D4_mstory2, 5);
            func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
            D_8011C680_mstory2[3].func = func_8010889C_mstory2;
            D_8011C680_mstory2[0].func = func_8010889C_mstory2;
            func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &D_8011BA28_mstory2, 5);
            func_801070D8_mstory2(D_8011C680_mstory2[0].obj, &D_8011BA34_mstory2, 5);
            func_801060A4_mstory2();
            D_8011C680_mstory2[1].func = func_8010B738_mstory2;
            func_801060F8_mstory2(j + 0x5B01);
            func_801060D4_mstory2();
            func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[8]].unk02, 0, 10, 0);
            func_801072AC_mstory2(D_8011C680_mstory2[0].obj->model[1]);
        }
    }
    func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
    func_8001C624_main(D_8011C680_mstory2[0].obj->model[1], HmfModelData[D_8011C680_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
    D_8011C680_mstory2[1].func = func_8010B110_mstory2;
    D_8011C680_mstory2[2].func = func_8010BD04_mstory2;
    D_8011C680_mstory2[3].func = func_8010C348_mstory2;
    path[1] = func_80107B90_mstory2(D_8011B980_mstory2, 0);
    for (k = 0; k < 50.0f; k++) {
        t = k * 0.02f;
        func_80107E94_mstory2(path[1], t * t, &pos);
        Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010873C_mstory2(path[1]);
    func_8001C258_main(D_8011C680_mstory2[4].obj->model[1], 4, 4);
    func_8001C258_main(D_8011C680_mstory2[4].obj->model[2], 4, 4);
    func_800138EC_main(D_8011C680_mstory2[4].obj->model[2], 1, 0);
    HuPrcSleep(5);
    func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[2]);
    func_8001C624_main(D_8011C680_mstory2[2].obj->model[1], HmfModelData[D_8011C680_mstory2[2].obj->motion[1]].unk02, 0, 10, 2);
    if (D_8011C75C_mstory2 == 4) {
        D_8011C680_mstory2[2].func = func_8010C018_mstory2;
        HuPrcSleep(10);
        func_80106E2C_mstory2(D_8011C680_mstory2[2].obj, &targets.v[5], 60);
        wait = 30;
    } else {
        wait = 60;
    }
    HuPrcSleep(wait);
    D_8011C748_mstory2 = 1;
    targets.v[2].y = targets.v[1].y = HmfModelData[D_8011C680_mstory2[3].obj->model[1]].pos.y;
    func_80106E2C_mstory2(D_8011C680_mstory2[3].obj, &targets.v[1], 3);
    HuAudFXPlay(0x217);
    D_8011C680_mstory2[2].func = func_8010BDC4_mstory2;
    D_8011C680_mstory2[0].func = func_8010A784_mstory2;
    D_8011C680_mstory2[1].func = func_8010B200_mstory2;
    func_8004AC98_main(D_8011C75C_mstory2 + 0x2AC, 0);
    func_8004AC98_main(D_8011C75E_mstory2 + 0x2AC, 1);
    D_8011C748_mstory2 = 0;
    func_80106E48_mstory2(D_8011C680_mstory2[3].obj, &targets.v[2], 5, 0);
    while (TRUE) {
        if (D_8011C680_mstory2[2].unk08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_8001C624_main(D_8011C680_mstory2[3].obj->model[1], HmfModelData[D_8011C680_mstory2[3].obj->motion[1]].unk02, 0, 10, 2);
    func_801060A4_mstory2();
    func_801060F8_mstory2((D_8011C75C_mstory2 != 4) ? 0x5A13 : 0x5B03);
    func_801060D4_mstory2();
    func_8001C624_main(D_8011C680_mstory2[3].obj->model[1], HmfModelData[D_8011C680_mstory2[3].obj->motion[0]].unk02, 0, 10, 2);
    D_8011C680_mstory2[0].func = func_8010A9F0_mstory2;
    D_8011C680_mstory2[1].func = func_8010B46C_mstory2;
    while (TRUE) {
        if (D_8011C680_mstory2[0].unk08 == 10 && D_8011C680_mstory2[1].unk08 == D_8011C680_mstory2[0].unk08) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    func_80105EA4_mstory2();
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
    D_8011C680_mstory2[4].func = func_8010889C_mstory2;
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    D_8011C680_mstory2[5].func = func_8010889C_mstory2;
}

/* actor 0: the story character, with its hook item */
void func_80109D04_mstory2(void) {
    StoryMotions motions = D_8011BF28_mstory2;
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[0].obj = obj;
    D_8011C680_mstory2[0].unk08 = 0;
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].unk0C = 0;
    D_8011C680_mstory2[0].unk10 = 0x1F;
    obj->model[1] = func_8000B108_main(D_800A178C_main[D_8011C75C_mstory2][0] | D_800A178C_main[D_8011C75C_mstory2][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(D_8011C75C_mstory2, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(D_8011C75C_mstory2, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(D_8011C75C_mstory2, 2));
    func_8000B460_main(obj, 3, motions.v[D_8011C75C_mstory2][0] | 0x1D0000);
    func_8000B460_main(obj, 4, motions.v[D_8011C75C_mstory2][1] | 0x1D0000);
    func_8000B460_main(obj, 5, func_80017BB8_main(D_8011C75C_mstory2, 0x72));
    func_8000B460_main(obj, 6, func_80017BB8_main(D_8011C75C_mstory2, 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(D_8011C75C_mstory2, 0x33));
    func_8000B460_main(obj, 8, motions.v[D_8011C75C_mstory2][2] | 0x1D0000);
    func_8000B460_main(obj, 9, func_80017BB8_main(D_8011C75C_mstory2, 0x9B));
    func_8000B460_main(obj, 10, func_80017BB8_main(D_8011C75C_mstory2, 0x9C));
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 162.4f, 0.0f);
    if (D_8011C75C_mstory2 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    data = DataRead(func_80017BB8_main(D_8011C75C_mstory2, 0xA4));
    D_8011C74A_mstory2[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_8011BA40_mstory2[D_8011C75C_mstory2]);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C74A_mstory2[0], 1, 0);
    func_80032FF8_main(D_8011C74A_mstory2[0], 0);
    D_8011C750_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C74A_mstory2[0], 0, D_8011BA40_mstory2[D_8011C75C_mstory2]);
    data = DataRead(func_80017BB8_main(D_8011C75C_mstory2, 0xA9));
    D_8011C74A_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C750_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C74A_mstory2[0], 0, D_8011BA40_mstory2[D_8011C75C_mstory2]);
    data = DataRead(func_80017BB8_main(D_8011C75C_mstory2, 0xAA));
    D_8011C74A_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[0]);
    omPrcSetDestructor(0, func_8010A290_mstory2);
    while (TRUE) {
        D_8011C680_mstory2[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A290_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE1C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE24_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE2C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE48_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE74_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE80_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE8C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE98_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BEB0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BEE0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BF28_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BF88_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BF94_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFA0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFAC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFB8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFC4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFD0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFDC_mstory2);

void func_8010A298_mstory2(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], obj->model[1], "item_hook");
    func_8001C258_main(obj->model[3], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_801072AC_mstory2(model);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_801072AC_mstory2(model);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].unk08 = 1;
}

void func_8010A3B4_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    f32 frame;

    func_8001C5B4_main(model, obj->motion[4]);
    func_8001C814_main(model, 4, 4);
    func_8001C92C_main(model, 2.0f);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C5B4_main(model, obj->motion[3]);
    func_8001C814_main(model, 4, 4);
    func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
    do {
        frame = HmfModelData[model].unk40;
        HuPrcVSleep();
    } while (frame > 0.0f);
    func_8001C92C_main(model, 1.0f);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    D_8011C680_mstory2[0].func = func_8010A5FC_mstory2;
}

void func_8010A5FC_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010A61C_mstory2(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    D_8011C680_mstory2[0].unk0C = 1;
    D_8011C680_mstory2[0].unk10 = 0x1F;
    func_801073A4_mstory2(obj, 3.5f, 15);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[2]);
    func_80106D58_mstory2(D_8011C680_mstory2[1].obj->model[1], D_8011C758_mstory2, D_8011C756_mstory2);
    D_8011C680_mstory2[0].unk0C = 0;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 10, 2);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[4]].unk02, 0, 10, 2);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

// story f2
/* chapter 2's first scene (A): six actors, each run by a process that calls its current hook
   (Ms2Actor.func) once a frame; hooks are scene steps that hand the next step to other actors.
   (mstory1's MsActor, 0x14 bytes here.) */
typedef struct Ms2Actor {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *obj);
    /* 0x08 */ s32 flags; /* scene progress other actors wait on */
    /* 0x0C */ s32 sfxOn; /* 1: func_8010D224_mstory2 plays sfxId on the walk cycle */
    /* 0x10 */ s32 sfxId;
} Ms2Actor; /* size = 0x14 */

typedef struct Ms2PathSeg {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
} Ms2PathSeg; /* size = 0x8 */

/* a path through points ended by { 9999, 9999, 9999 } (mstory1's ObPath) */
typedef struct Ms2Path {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 flags;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ Vec *points;
    /* 0x0C */ Ms2PathSeg *segs;
} Ms2Path; /* size = 0x10 */

void func_80105FBC_mstory2(void);
void func_801060A4_mstory2(void);
void func_801060D4_mstory2(void);
void func_801060F8_mstory2(s32 mess);
void func_8010614C_mstory2(s32 mess);
void func_80106D58_mstory2(s16 model, s16 anim, s16 slot);
void func_80106E2C_mstory2(omObjData *obj, Vec *to, s32 frames);
void func_801070D8_mstory2(omObjData *obj, Vec *rot, s32 frames);
void func_801072AC_mstory2(s16 model);
void func_801073A4_mstory2(omObjData *obj, f32 speed, s16 frames);
void func_801076DC_mstory2(omObjData *obj, omObjData *target);
/* the idle hook (defined (void) above) */
#define MS2_IDLE ((void (*)(omObjData *))func_8010889C_mstory2)
void func_8010A61C_mstory2(omObjData *obj);
void func_8010B108_mstory2(void);
void func_8010BAC4_mstory2(void);
void func_8010BCE4_mstory2(omObjData *obj);
void func_8010BF7C_mstory2(omObjData *obj);
void func_8010C1DC_mstory2(void);
void func_8010C508_mstory2(void);
void func_8010D21C_mstory2(void);
Ms2Path *func_8010C510_mstory2(Vec *points, s16 flags);
void func_8010C814_mstory2(Ms2Path *path, f32 t, Vec *out);
void func_8010D0BC_mstory2(Ms2Path *path);
void func_8010D224_mstory2(void);
void func_8010D3BC_mstory2(void);
void func_8010D430_mstory2(omObjData *obj);
void func_8010D5C0_mstory2(omObjData *obj);
void func_8010E9E0_mstory2(void);
void func_8010EF6C_mstory2(void);
void func_8010F8F8_mstory2(void);
void func_801103E4_mstory2(void);
void func_80110C64_mstory2(void);
void func_80110E10_mstory2(void);
void func_80111024_mstory2(void);

void func_800138EC_main(s16 model, u16 mask, u16 flags);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);

extern char *D_8011BA60_mstory2[2]; /* .data: actor 1's animation names by model */
extern const Vec D_8011BE74_mstory2;
extern const Vec D_8011BE80_mstory2;
extern const Vec D_8011BE8C_mstory2;
extern const Vec D_8011BE98_mstory2;
extern const Vec D_8011BFF4_mstory2;
extern const Vec D_8011C000_mstory2;
extern const Vec D_8011C00C_mstory2;
extern const Vec D_8011C024_mstory2;
extern const Vec D_8011C030_mstory2;
extern const Vec D_8011C03C_mstory2[2];
typedef struct Ms2Rot4 {
    Vec v[4];
} Ms2Rot4;
extern const Ms2Rot4 D_8011C090_mstory2; /* actors 3 and 2's turns in func_8010D430_mstory2 */

extern Ms2Actor D_8011C680_mstory2[6]; /* scene A's actors */
extern Vec D_8011C704_mstory2; /* actor 1's start position */
extern Vec D_8011C710_mstory2; /* actor 2's */
extern Vec D_8011C71C_mstory2; /* actor 3's */
extern Vec D_8011C728_mstory2; /* actor 4's */
extern s16 D_8011C740_mstory2[3]; /* actor 2's texture animation slots */
extern s16 D_8011C746_mstory2; /* actor 2's texture animation */
extern s16 D_8011C748_mstory2; /* 1: actor 3 stops bobbing */
extern s16 D_8011C74A_mstory2[3]; /* actor 0's slots */
extern s16 D_8011C750_mstory2; /* actor 0's texture animation */
extern s16 D_8011C752_mstory2[3]; /* actor 1's slots */
extern s16 D_8011C758_mstory2; /* actor 1's texture animation */
extern s16 D_8011C75A_mstory2; /* the shadow model every actor links */
extern s16 D_8011C75C_mstory2; /* actor 0's character */
extern s16 D_8011C75E_mstory2; /* actor 1's character */

void *HuMemAllocTag(s32 size, s16 tag);
void HuMemFree(void *data);
extern s32 D_800A178C_main[][6];
extern char *D_8011BB60_mstory2[8]; /* .data: scene B actor 0's animation names by character */
/* scene B actor 0's motions 3, 4 and 8 by character */
typedef struct Ms2MotTbl {
    s32 m[8][3];
} Ms2MotTbl;
extern const Ms2MotTbl D_8011C108_mstory2;
extern s16 D_8011C82A_mstory2[3]; /* scene B actor 0's texture animation slots */
extern s16 D_8011C830_mstory2; /* its texture animation */
/* scene B's idle hook (defined (void) above) */
#define MS2B_IDLE ((void (*)(omObjData *))func_8010D21C_mstory2)
void func_80105EA4_mstory2(void);
void func_8010622C_mstory2(void);
void func_80106E48_mstory2(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80107824_mstory2(omObjData *obj, Vec *to, s32 frames, s32 arg3);
void func_8010EF74_mstory2(omObjData *obj);
void func_8010F090_mstory2(omObjData *obj);
void func_8010F460_mstory2(omObjData *obj);
void func_8010F6CC_mstory2(omObjData *obj);
void func_8010FDEC_mstory2(omObjData *obj);
void func_8010FEDC_mstory2(omObjData *obj);
void func_80110148_mstory2(omObjData *obj);
void func_80110364_mstory2(omObjData *obj);
void func_801106F8_mstory2(omObjData *obj);
void func_80110930_mstory2(omObjData *obj);
void func_801109F0_mstory2(omObjData *obj);
void func_80110C44_mstory2(omObjData *obj);
void func_80110F54_mstory2(omObjData *obj);
void func_80110F74_mstory2(omObjData *obj);
void func_80110FC4_mstory2(omObjData *obj);
extern Vec D_8011BA70_mstory2[]; /* .data: actor 4's flight in */
extern Vec D_8011BAA0_mstory2[]; /* .data: its flight out (point 0 is where it hovered) */
extern Vec D_8011BAE8_mstory2; /* .data: rotations */
extern Vec D_8011BAF4_mstory2;
extern Vec D_8011BB00_mstory2;
extern Vec D_8011BB0C_mstory2;
extern Vec D_8011BB3C_mstory2;
extern Vec D_8011BB48_mstory2;
extern Vec D_8011BB54_mstory2;
typedef struct Ms2Vec6 {
    Vec v[6];
} Ms2Vec6;
extern const Ms2Vec6 D_8011C0C0_mstory2; /* func_8010D5C0_mstory2's targets */
extern s16 D_8011C820_mstory2[3]; /* scene B actor 2's texture animation slots */
extern s16 D_8011C826_mstory2; /* its texture animation */
extern s16 D_8011C828_mstory2;
extern Ms2Actor D_8011C760_mstory2[6]; /* scene B's actors */
extern s16 D_8011C83A_mstory2; /* scene B's shadow model */
extern s16 D_8011C83C_mstory2; /* actor 0's character (the player's) */
extern s16 D_8011C83E_mstory2; /* actor 1's character */

/* actor 0 hops down: turns to face away, moves to z 500, then back to idle */
void func_8010A784_mstory2(omObjData *obj) {
    Vec rot = D_8011BFF4_mstory2;
    Vec pos = { HmfModelData[obj->model[1]].pos.x - 5.0f, HmfModelData[obj->model[1]].pos.y, 500.0f };

    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, HmfModelData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    func_80106E2C_mstory2(obj, &pos, 10);
    func_801072AC_mstory2(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801070D8_mstory2(obj, &rot, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[0]);
    D_8011C680_mstory2[0].func = MS2_IDLE;
}

void func_8010A9F0_mstory2(omObjData *obj) {
    Vec rot = D_8011C000_mstory2;
    Vec pos = { HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, 1200.0f };

    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801070D8_mstory2(obj, &rot, 10);
    D_8011C680_mstory2[2].func = func_8010BF7C_mstory2;
    func_8004AC98_main(D_8011C75C_mstory2 + 0x275, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[7]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[0].flags = 10;
    while (TRUE) {
        if (D_8011C680_mstory2[1].flags == 10) {
            break;
        }
        HuPrcVSleep();
    }
    D_8011C680_mstory2[0].sfxOn = 1;
    D_8011C680_mstory2[0].sfxId = 0x28;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &pos, 60);
    D_8011C680_mstory2[0].sfxOn = 0;
    D_8011C680_mstory2[0].func = MS2_IDLE;
}

/* actor 1: the partner (model by whether the player is character 4) */
void func_8010AC1C_mstory2(void) {
    s16 chrs[2] = { 4, 1 };
    s32 mots[2] = { 0x61, 0x44 };
    omObjData *obj;
    void *data;
    s16 idx;

    idx = D_8011C75C_mstory2 == 4;
    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[1].obj = obj;
    D_8011C680_mstory2[1].flags = 0;
    D_8011C680_mstory2[1].func = MS2_IDLE;
    D_8011C680_mstory2[1].sfxOn = 0;
    D_8011C680_mstory2[1].sfxId = 0x1F;
    obj->model[1] = func_8000B108_main(idx == 0 ? 0x500A0 : 0x300A0, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    obj->model[3] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chrs[idx], 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chrs[idx], 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chrs[idx], 2));
    func_8000B460_main(obj, 3, func_80017BB8_main(chrs[idx], 0x13));
    func_8000B460_main(obj, 4, func_80017BB8_main(chrs[idx], 0x72));
    func_8000B460_main(obj, 5, mots[idx] | 0x1D0000);
    func_8000B460_main(obj, 6, func_80017BB8_main(chrs[idx], 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(chrs[idx], 0x33));
    func_8000B460_main(obj, 8, func_80017BB8_main(chrs[idx], 0x2F));
    if (D_8011C75C_mstory2 == 4) {
        func_8000B460_main(obj, 9, 0x1D0045);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C704_mstory2 = D_8011BE74_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C704_mstory2.x, D_8011C704_mstory2.y, D_8011C704_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C704_mstory2.x, D_8011C704_mstory2.y - -5.0f, D_8011C704_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, -14.48f, 0.0f);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xA4));
    D_8011C752_mstory2[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_8011BA60_mstory2[idx]);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C752_mstory2[0], 1, 0);
    func_80032FF8_main(D_8011C752_mstory2[0], 0);
    D_8011C758_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C752_mstory2[0], 0, D_8011BA60_mstory2[idx]);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xA9));
    D_8011C752_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C758_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C752_mstory2[0], 0, D_8011BA60_mstory2[idx]);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xAA));
    D_8011C752_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[0]);
    omPrcSetDestructor(0, func_8010B108_mstory2);
    while (TRUE) {
        D_8011C680_mstory2[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B108_mstory2(void) {
}

void func_8010B110_mstory2(omObjData *obj) {
    D_8011C680_mstory2[1].sfxOn = 1;
    D_8011C680_mstory2[1].sfxId = 0x1F;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801073A4_mstory2(obj, 4.5f, 15);
    D_8011C680_mstory2[1].sfxOn = 0;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_8011C680_mstory2[1].func = MS2_IDLE;
    D_8011C680_mstory2[0].func = func_8010A61C_mstory2;
}

void func_8010B200_mstory2(omObjData *obj) {
    Vec rot = D_8011C00C_mstory2;
    Vec pos = { HmfModelData[obj->model[1]].pos.x + 5.0f, HmfModelData[obj->model[1]].pos.y, 500.0f };

    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, HmfModelData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    func_80106E2C_mstory2(obj, &pos, 10);
    func_801072AC_mstory2(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801070D8_mstory2(obj, &rot, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[0]);
    D_8011C680_mstory2[1].func = MS2_IDLE;
}

void func_8010B46C_mstory2(omObjData *obj) {
    Vec rot = D_8011C000_mstory2;
    Vec pos = { HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, 1200.0f };

    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_801070D8_mstory2(obj, &rot, 10);
    func_8004AC98_main(D_8011C75E_mstory2 + 0x275, 1);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[7]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[1].flags = 10;
    while (TRUE) {
        if (D_8011C680_mstory2[0].flags == 10) {
            break;
        }
        HuPrcVSleep();
    }
    D_8011C680_mstory2[1].sfxOn = 1;
    D_8011C680_mstory2[1].sfxId = 0x28;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &pos, 60);
    D_8011C680_mstory2[1].sfxOn = 0;
    D_8011C680_mstory2[0].func = MS2_IDLE;
}

void func_8010B688_mstory2(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
}

void func_8010B738_mstory2(omObjData *obj) {
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[9]].unk02, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[1].func = MS2_IDLE;
}

const Vec D_8011BFF4_mstory2 = { 0.0f, 180.0f, 0.0f };

const Vec D_8011C000_mstory2 = { 0.0f, 0.0f, 0.0f };

const Vec D_8011C00C_mstory2 = { 0.0f, -180.0f, 0.0f };

/* actor 2 (model 0xA0075, mstory1's actor 1) */
void func_8010B7B8_mstory2(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[2].obj = obj;
    D_8011C680_mstory2[2].flags = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C710_mstory2 = D_8011BE80_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C710_mstory2.x, D_8011C710_mstory2.y, D_8011C710_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C710_mstory2.x, -5.0f, D_8011C710_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    D_8011C740_mstory2[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C740_mstory2[0], 1, 0);
    func_80032FF8_main(D_8011C740_mstory2[0], 0);
    D_8011C746_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C740_mstory2[0], 0, "c204n_0_DEF");
    data = DataRead(0xA0083);
    D_8011C740_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C746_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C740_mstory2[0], 0, "c204n_0_DEF");
    data = DataRead(0xA0080);
    D_8011C740_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    omPrcSetDestructor(0, func_8010BAC4_mstory2);
    D_8011C680_mstory2[2].func = MS2_IDLE;
    while (TRUE) {
        D_8011C680_mstory2[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010BAC4_mstory2(void) {
}

/* actor 2 jumps (13 frames), turns, and actor 1 reacts */
void func_8010BACC_mstory2(omObjData *obj) {
    Vec pos;
    Vec rot;
    s16 model;
    f32 y;
    s16 i;

    model = obj->model[1];
    rot = D_8011C024_mstory2;
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        HmfModelData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_801070D8_mstory2(obj, &rot, 5);
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_8001C624_main(D_8011C680_mstory2[1].obj->model[1], HmfModelData[D_8011C680_mstory2[1].obj->motion[8]].unk02, 0, 10, 0);
    HuPrcSleep(D_8011C75C_mstory2 != 4 ? 30 : 35);
    func_8004AAD0_main(CharFXPlay(0x28F, D_8011C75E_mstory2), 0x60);
    D_8011C680_mstory2[2].func = func_8010BCE4_mstory2;
    D_8011C680_mstory2[2].flags = 5;
}

/* face actor 1 */
void func_8010BCE4_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

/* sink to y 100 */
void func_8010BD04_mstory2(omObjData *obj) {
    while (TRUE) {
        if (!(HmfModelData[obj->model[1]].pos.y > 100.0f)) {
            break;
        }
        HmfModelData[obj->model[1]].pos.y -= 2.0f;
        HuPrcVSleep();
    }
    HmfModelData[obj->model[1]].pos.y = 100.0f;
    D_8011C680_mstory2[2].func = MS2_IDLE;
}

void func_8010BDC4_mstory2(omObjData *obj) {
    Vec pos;
    Vec rot;
    s16 model;
    f32 y;
    s16 i;

    model = obj->model[1];
    rot = D_8011C030_mstory2;
    pos.x = HmfModelData[model].pos.x;
    pos.y = HmfModelData[model].pos.y;
    pos.z = HmfModelData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[1]);
    func_8001C624_main(D_8011C680_mstory2[2].obj->model[1], HmfModelData[D_8011C680_mstory2[2].obj->motion[0]].unk02, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        HmfModelData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    func_801070D8_mstory2(obj, &rot, 10);
    D_8011C680_mstory2[2].func = MS2_IDLE;
    D_8011C680_mstory2[2].flags = 1;
}

/* turn, then keep facing actor 0 */
void func_8010BF7C_mstory2(omObjData *obj) {
    Vec rot = D_8011C03C_mstory2[0];

    func_80106D58_mstory2(obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_801070D8_mstory2(obj, &rot, 10);
    while (TRUE) {
        func_801076DC_mstory2(D_8011C680_mstory2[2].obj, D_8011C680_mstory2[0].obj);
        HuPrcVSleep();
    }
}

/* face actor 0 */
void func_8010C018_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[0].obj);
}

/* actor 3 (model 0xA0122, twice the size) */
void func_8010C038_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[3].obj = obj;
    D_8011C680_mstory2[3].flags = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C71C_mstory2 = D_8011BE8C_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C71C_mstory2.x, D_8011C71C_mstory2.y, D_8011C71C_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C71C_mstory2.x, -5.0f, D_8011C71C_mstory2.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_8010C1DC_mstory2);
    D_8011C680_mstory2[3].func = MS2_IDLE;
    while (TRUE) {
        D_8011C680_mstory2[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C1DC_mstory2(void) {
}

/* NON_MATCHING: scheduling only; retail computes ofs + 25 before the wrap test (in its branch
   delay slot) and the mul right after the call */
#ifdef NON_MATCHING
/* actor 3 bobs 25 above its height until D_8011C748_mstory2 is 1 */
void func_8010C1E4_mstory2(void) {
    Vec pos;
    omObjData *obj;
    f32 angle;
    f32 ofs;

    angle = 0.0f;
    obj = D_8011C680_mstory2[3].obj;
    pos.y = HmfModelData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = HmfModelData[obj->model[1]].pos.x;
        pos.z = HmfModelData[obj->model[1]].pos.z;
        ofs = sindf(angle) * 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (D_8011C748_mstory2 != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + 25.0f + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010C1E4_mstory2);
#endif

/* face actor 1 */
void func_8010C328_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010C348_mstory2(omObjData *obj) {
    Vec rot = D_8011C000_mstory2;

    func_801070D8_mstory2(obj, &rot, 10);
    D_8011C680_mstory2[3].func = MS2_IDLE;
}

/* actor 4 (model 0x1D0003 and a second model 0xB0004) */
void func_8010C398_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011C680_mstory2[4].obj = obj;
    D_8011C680_mstory2[4].flags = 0;
    D_8011C680_mstory2[4].func = MS2_IDLE;
    obj->model[1] = func_8000B108_main(0x1D0003, 0x20299);
    obj->model[2] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C728_mstory2 = D_8011BE98_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C728_mstory2.x, D_8011C728_mstory2.y, D_8011C728_mstory2.z);
    func_8000CD00_main(obj->model[2], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[2], 60.0f);
    func_800138EC_main(obj->model[2], 1, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    omPrcSetDestructor(0, func_8010C508_mstory2);
    while (TRUE) {
        D_8011C680_mstory2[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C508_mstory2(void) {
}

/* build a path through points (mstory1's func_801074C0_mstory1) */
Ms2Path *func_8010C510_mstory2(Vec *points, s16 flags) {
    Ms2Path *path;
    Vec *prev;
    Vec *cur;
    Ms2PathSeg *seg;
    f32 total;
    f32 pos;
    f32 len;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 n;
    s16 i;

    path = HuMemAllocTag(sizeof(Ms2Path), 0x7918);
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
    seg = HuMemAllocTag(n * sizeof(Ms2PathSeg), 0x7918);
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

/* NON_MATCHING as mstory1's func_801077C4_mstory1 (same code) */
#ifdef NON_MATCHING
/* the point at t (0..1) along a path: a spline through the four points around the segment t
   falls in */
void func_8010C814_mstory2(Ms2Path *path, f32 t, Vec *out) {
    f32 p[4];
    f32 times[4];
    Ms2PathSeg *segs;
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010C814_mstory2);
#endif

void func_8010D0BC_mstory2(Ms2Path *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* chapter 2, scene B: the actors' processes */
void func_8010D0EC_mstory2(void) {
    s16 chr;

    chr = GwStory.unk1;
    D_8011C83C_mstory2 = chr;
    D_8011C83E_mstory2 = (chr == 3) ? 1 : 3;
    func_80105FBC_mstory2();
    D_8011C83A_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010E9E0_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010F8F8_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_801103E4_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80110C64_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80111024_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_8010D3BC_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80110E10_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010D224_mstory2, 0x1001, 0x1000, 0);
    func_8001C258_main(D_8011C83A_mstory2, 4, 4);
}

void func_8010D21C_mstory2(void) {
}

/* scene B's footsteps: actors 0 and 1 play their sfxId at frame 0 of the walk while sfxOn is 1
   (actor 1's panned by its depth) */
void func_8010D224_mstory2(void) {
    s16 fx;
    s32 pan;

    while (TRUE) {
        if (D_8011C760_mstory2[0].sfxOn == 1 && HmfModelData[D_8011C760_mstory2[0].obj->model[1]].unk40 == 0.0f) {
            CharFXPlay(D_8011C760_mstory2[0].sfxId, D_8011C83C_mstory2);
        }
        if (D_8011C760_mstory2[1].sfxOn == 1 && HmfModelData[D_8011C760_mstory2[1].obj->model[1]].unk40 == 0.0f) {
            fx = CharFXPlay(D_8011C760_mstory2[1].sfxId, D_8011C83E_mstory2);
            if (HmfModelData[D_8011C760_mstory2[1].obj->model[1]].pos.z <= 0.0f) {
                pan = HmfModelData[D_8011C760_mstory2[1].obj->model[1]].pos.z / 15.0f + 127.0f;
            } else {
                pan = 127;
            }
            func_8004AAD0_main(fx, pan);
        }
        HuPrcVSleep();
    }
}

/* actor 5: no model, only runs scene steps */
void func_8010D3BC_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_8011C760_mstory2[5].obj = obj;
    D_8011C760_mstory2[5].flags = 0;
    D_8011C760_mstory2[5].func = func_8010D430_mstory2;
    while (TRUE) {
        D_8011C760_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

/* actors 3 and 2 turn and talk (message 0x5A1F, or 0x5B0F for character 3), then turn back */
void func_8010D430_mstory2(omObjData *obj) {
    Ms2Rot4 rot = D_8011C090_mstory2;

    HuPrcSleep(40);
    func_801070D8_mstory2(D_8011C760_mstory2[3].obj, &rot.v[0], 10);
    func_801070D8_mstory2(D_8011C760_mstory2[2].obj, &rot.v[1], 10);
    HuAudFXPlay(0x159);
    func_8001C624_main(D_8011C760_mstory2[3].obj->model[1], HmfModelData[D_8011C760_mstory2[3].obj->motion[1]].unk02, 0, 10, 2);
    func_801060A4_mstory2();
    if (D_8011C83C_mstory2 != 3) {
        func_8010614C_mstory2(0x5A1F);
    } else {
        func_801060F8_mstory2(0x5B0F);
    }
    func_801060D4_mstory2();
    func_8001C624_main(D_8011C760_mstory2[3].obj->model[1], HmfModelData[D_8011C760_mstory2[3].obj->motion[0]].unk02, 0, 10, 2);
    func_801070D8_mstory2(D_8011C760_mstory2[3].obj, &rot.v[2], 10);
    func_801070D8_mstory2(D_8011C760_mstory2[2].obj, &rot.v[3], 10);
    D_8011C760_mstory2[5].func = func_8010D5C0_mstory2;
}

/* scene B, actor 5's main step: actor 4 flies in along a path, lands near actors 0 and 1, the
   talk (messages by character), then actor 4 flies off and everyone walks away */
void func_8010D5C0_mstory2(omObjData *obj) {
    Vec pos;
    Ms2Path *path[2];
    Ms2Vec6 to;
    f32 t;
    s16 i;
    s16 j;

    j = 0;
    to = D_8011C0C0_mstory2;
    func_8001C258_main(D_8011C760_mstory2[4].obj->model[1], 4, 0);
    func_8001C258_main(D_8011C760_mstory2[4].obj->model[2], 4, 0);
    func_800138EC_main(D_8011C760_mstory2[4].obj->model[2], 1, 1);
    HuAudFXPlay(0x215);
    path[0] = func_8010C510_mstory2(D_8011BA70_mstory2, 0);
    for (i = 0; i < 40.0f; i++) {
        if (i == 30) {
            func_8001C624_main(D_8011C760_mstory2[0].obj->model[1], HmfModelData[D_8011C760_mstory2[0].obj->motion[9]].unk02, 0, 10, 2);
        }
        t = i * 0.025f;
        func_8010C814_mstory2(path[0], t * t, &pos);
        Hu3DModelPosSet(D_8011C760_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011C760_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010D0BC_mstory2(path[0]);
    D_8011C760_mstory2[0].func = func_8010EF74_mstory2;
    while (TRUE) {
        if (D_8011C760_mstory2[0].flags == 1) {
            pos.x -= 0.19999999f;
            pos.y -= 2.0f;
            pos.z += 1.0f;
            Hu3DModelPosSet(D_8011C760_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
            func_8000CFA4_main(D_8011C760_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
            if (j++ == 30.0f) {
                j = 0;
                break;
            }
        }
        HuPrcVSleep();
    }
    func_8004AAD0_main(CharFXPlay(0x2BD, D_8011C83E_mstory2), 0x50);
    HuPrcSleep(30);
    func_8001C258_main(D_8011C760_mstory2[1].obj->model[1], 4, 0);
    func_8001C258_main(D_8011C760_mstory2[1].obj->model[2], 4, 0);
    func_8010622C_mstory2();
    HuPrcSleep(10);
    D_8011C760_mstory2[0].func = func_8010F090_mstory2;
    D_8011C760_mstory2[2].func = func_801106F8_mstory2;
    while (TRUE) {
        pos.x += 1.0f;
        pos.y += 10.0f;
        pos.z -= 5.0f;
        Hu3DModelPosSet(D_8011C760_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011C760_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        if (j++ == 6.0f) {
            break;
        }
        HuPrcVSleep();
    }
    D_8011BAA0_mstory2[0].x = pos.x;
    D_8011BAA0_mstory2[0].y = pos.y;
    D_8011BAA0_mstory2[0].z = pos.z;
    func_801070D8_mstory2(D_8011C760_mstory2[3].obj, &D_8011BAE8_mstory2, 5);
    D_8011C760_mstory2[3].func = func_80110F54_mstory2;
    while (TRUE) {
        if (D_8011C760_mstory2[2].flags == 5) {
            break;
        }
        HuPrcVSleep();
    }
    func_801072AC_mstory2(D_8011C760_mstory2[1].obj->model[1]);
    HuPrcSleep(30);
    D_8011C760_mstory2[1].sfxOn = 1;
    D_8011C760_mstory2[1].sfxId = 0x28;
    func_8001C92C_main(D_8011C760_mstory2[0].obj->model[1], 0.25f);
    func_8001C624_main(D_8011C760_mstory2[0].obj->model[1], HmfModelData[D_8011C760_mstory2[0].obj->motion[10]].unk02, 0, 10, 2);
    func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[2]].unk02, 0, 10, 2);
    func_80107824_mstory2(D_8011C760_mstory2[1].obj, &to.v[0], 180, 1);
    D_8011C760_mstory2[1].sfxOn = 0;
    func_8001C624_main(D_8011C760_mstory2[0].obj->model[1], HmfModelData[D_8011C760_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C92C_main(D_8011C760_mstory2[0].obj->model[1], 1.0f);
    func_80106D58_mstory2(D_8011C760_mstory2[2].obj->model[1], D_8011C826_mstory2, D_8011C820_mstory2[0]);
    func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[3]].unk02, 0, 10, 2);
    HuPrcSleep(60);
    func_80106D58_mstory2(D_8011C760_mstory2[2].obj->model[1], D_8011C826_mstory2, D_8011C820_mstory2[0]);
    func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
    func_801070D8_mstory2(D_8011C760_mstory2[1].obj, &D_8011BAF4_mstory2, 10);
    if (D_8011C83C_mstory2 != 3) {
        func_80106E48_mstory2(D_8011C760_mstory2[2].obj, &to.v[3], 15, 0);
        func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[1]].unk02, 0, 10, 2);
        func_801070D8_mstory2(D_8011C760_mstory2[1].obj, &D_8011BB3C_mstory2, 10);
        func_8001C624_main(D_8011C760_mstory2[0].obj->model[1], HmfModelData[D_8011C760_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
        func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[5]].unk02, 0, 10, 0);
        HuPrcSleep(10);
        func_8001C624_main(D_8011C760_mstory2[2].obj->model[1], HmfModelData[D_8011C760_mstory2[2].obj->motion[2]].unk02, 0, 10, 2);
        func_801072AC_mstory2(D_8011C760_mstory2[1].obj->model[1]);
        func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[5]].unk02, 0, 10, 0);
        func_801072AC_mstory2(D_8011C760_mstory2[1].obj->model[1]);
        func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
        func_8001C624_main(D_8011C760_mstory2[2].obj->model[1], HmfModelData[D_8011C760_mstory2[2].obj->motion[0]].unk02, 0, 10, 2);
        D_8011C760_mstory2[2].func = MS2B_IDLE;
        func_80106E2C_mstory2(D_8011C760_mstory2[2].obj, &to.v[4], 8);
        func_801070D8_mstory2(D_8011C760_mstory2[2].obj, &D_8011BB00_mstory2, 10);
        func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[1]].unk02, 0, 10, 2);
        func_801070D8_mstory2(D_8011C760_mstory2[1].obj, &D_8011BAF4_mstory2, 5);
        func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
        D_8011C760_mstory2[3].func = MS2B_IDLE;
        D_8011C760_mstory2[0].func = MS2B_IDLE;
        func_801070D8_mstory2(D_8011C760_mstory2[3].obj, &D_8011BB48_mstory2, 5);
        func_801070D8_mstory2(D_8011C760_mstory2[0].obj, &D_8011BB54_mstory2, 5);
        func_801060A4_mstory2();
        func_801060F8_mstory2(0x5A20);
        func_801060D4_mstory2();
    } else {
        for (i = 0; i < 2; i++) {
            func_80106E48_mstory2(D_8011C760_mstory2[2].obj, &to.v[3], 15, 0);
            func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[1]].unk02, 0, 10, 2);
            func_801070D8_mstory2(D_8011C760_mstory2[1].obj, &D_8011BB3C_mstory2, 10);
            func_8001C624_main(D_8011C760_mstory2[0].obj->model[1], HmfModelData[D_8011C760_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
            func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[5]].unk02, 0, 10, 0);
            HuPrcSleep(10);
            func_8001C624_main(D_8011C760_mstory2[2].obj->model[1], HmfModelData[D_8011C760_mstory2[2].obj->motion[2]].unk02, 0, 10, 2);
            func_801072AC_mstory2(D_8011C760_mstory2[1].obj->model[1]);
            if (i == 0) {
                func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[5]].unk02, 0, 10, 0);
                func_801072AC_mstory2(D_8011C760_mstory2[1].obj->model[1]);
            }
            func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
            func_8001C624_main(D_8011C760_mstory2[2].obj->model[1], HmfModelData[D_8011C760_mstory2[2].obj->motion[0]].unk02, 0, 10, 2);
            D_8011C760_mstory2[2].func = MS2B_IDLE;
            func_80106E2C_mstory2(D_8011C760_mstory2[2].obj, &to.v[4], 8);
            func_801070D8_mstory2(D_8011C760_mstory2[2].obj, &D_8011BB00_mstory2, 10);
            func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[1]].unk02, 0, 10, 2);
            func_801070D8_mstory2(D_8011C760_mstory2[1].obj, &D_8011BAF4_mstory2, 5);
            func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[0]].unk02, 0, 10, 2);
            D_8011C760_mstory2[3].func = MS2B_IDLE;
            D_8011C760_mstory2[0].func = MS2B_IDLE;
            func_801070D8_mstory2(D_8011C760_mstory2[3].obj, &D_8011BB48_mstory2, 5);
            func_801070D8_mstory2(D_8011C760_mstory2[0].obj, &D_8011BB54_mstory2, 5);
            func_801060A4_mstory2();
            D_8011C760_mstory2[1].func = func_80110364_mstory2;
            func_801060F8_mstory2(i + 0x5B10);
            func_801060D4_mstory2();
            func_8001C624_main(D_8011C760_mstory2[0].obj->model[1], HmfModelData[D_8011C760_mstory2[0].obj->motion[8]].unk02, 0, 10, 0);
            func_801072AC_mstory2(D_8011C760_mstory2[0].obj->model[1]);
        }
        func_801072AC_mstory2(D_8011C760_mstory2[1].obj->model[1]);
    }
    func_8001C624_main(D_8011C760_mstory2[0].obj->model[1], HmfModelData[D_8011C760_mstory2[0].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(D_8011C760_mstory2[1].obj->model[1], HmfModelData[D_8011C760_mstory2[1].obj->motion[1]].unk02, 0, 10, 2);
    D_8011C760_mstory2[1].func = func_8010FDEC_mstory2;
    D_8011C760_mstory2[2].func = func_80110930_mstory2;
    D_8011C760_mstory2[3].func = func_80110F74_mstory2;
    path[1] = func_8010C510_mstory2(D_8011BAA0_mstory2, 0);
    for (i = 0; i < 50.0f; i++) {
        t = i * 0.02f;
        func_8010C814_mstory2(path[1], t * t, &pos);
        Hu3DModelPosSet(D_8011C760_mstory2[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011C760_mstory2[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010D0BC_mstory2(path[1]);
    func_8001C258_main(D_8011C760_mstory2[4].obj->model[1], 4, 4);
    func_8001C258_main(D_8011C760_mstory2[4].obj->model[2], 4, 4);
    func_800138EC_main(D_8011C760_mstory2[4].obj->model[2], 1, 0);
    HuPrcSleep(5);
    func_80106D58_mstory2(D_8011C760_mstory2[2].obj->model[1], D_8011C826_mstory2, D_8011C820_mstory2[2]);
    func_8001C624_main(D_8011C760_mstory2[2].obj->model[1], HmfModelData[D_8011C760_mstory2[2].obj->motion[1]].unk02, 0, 10, 2);
    D_8011C760_mstory2[2].func = func_80110C44_mstory2;
    HuPrcSleep(10);
    func_80106E2C_mstory2(D_8011C760_mstory2[2].obj, &to.v[5], 60);
    HuPrcSleep(30);
    D_8011C760_mstory2[2].func = MS2B_IDLE;
    func_801070D8_mstory2(D_8011C760_mstory2[2].obj, &D_8011BB0C_mstory2, 10);
    func_801060A4_mstory2();
    func_801060F8_mstory2(D_8011C83C_mstory2 == 3 ? 0x5A21 : 0x5B12);
    func_801060D4_mstory2();
    HuPrcSleep(30);
    D_8011C828_mstory2 = 1;
    to.v[2].y = to.v[1].y = HmfModelData[D_8011C760_mstory2[3].obj->model[1]].pos.y;
    func_80106E2C_mstory2(D_8011C760_mstory2[3].obj, &to.v[1], 3);
    HuAudFXPlay(0x217);
    D_8011C760_mstory2[2].func = func_801109F0_mstory2;
    D_8011C760_mstory2[3].func = func_80110FC4_mstory2;
    D_8011C760_mstory2[0].func = func_8010F460_mstory2;
    D_8011C760_mstory2[1].func = func_8010FEDC_mstory2;
    func_8004AC98_main(D_8011C83C_mstory2 + 0x2AC, 0);
    func_8004AC98_main(D_8011C83E_mstory2 + 0x2AC, 1);
    D_8011C828_mstory2 = 0;
    func_80106E48_mstory2(D_8011C760_mstory2[3].obj, &to.v[2], 5, 0);
    while (TRUE) {
        if (D_8011C760_mstory2[2].flags == 1) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_8001C624_main(D_8011C760_mstory2[3].obj->model[1], HmfModelData[D_8011C760_mstory2[3].obj->motion[1]].unk02, 0, 10, 2);
    func_801060A4_mstory2();
    func_801060F8_mstory2(D_8011C83C_mstory2 != 3 ? 0x5A22 : 0x5B13);
    func_801060D4_mstory2();
    func_8001C624_main(D_8011C760_mstory2[3].obj->model[1], HmfModelData[D_8011C760_mstory2[3].obj->motion[0]].unk02, 0, 10, 2);
    D_8011C760_mstory2[0].func = func_8010F6CC_mstory2;
    D_8011C760_mstory2[1].func = func_80110148_mstory2;
    while (TRUE) {
        if (D_8011C760_mstory2[0].flags == 10 && D_8011C760_mstory2[1].flags == D_8011C760_mstory2[0].flags) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    func_80105EA4_mstory2();
    D_8011C760_mstory2[0].func = MS2B_IDLE;
    D_8011C760_mstory2[3].func = MS2B_IDLE;
    D_8011C760_mstory2[2].func = MS2B_IDLE;
    D_8011C760_mstory2[4].func = MS2B_IDLE;
    D_8011C760_mstory2[1].func = MS2B_IDLE;
    D_8011C760_mstory2[5].func = MS2B_IDLE;
}

/* scene B, actor 0: the player's character */
void func_8010E9E0_mstory2(void) {
    Ms2MotTbl mots = D_8011C108_mstory2;
    omObjData *obj;
    void *data;

    obj = omAddObj(10, 0x14, 0x14, -1, NULL);
    D_8011C760_mstory2[0].obj = obj;
    D_8011C760_mstory2[0].flags = 0;
    D_8011C760_mstory2[0].func = (void (*)(omObjData *))func_8010D21C_mstory2;
    D_8011C760_mstory2[0].sfxOn = 0;
    D_8011C760_mstory2[0].sfxId = 0x1F;
    obj->model[1] = func_8000B108_main(D_800A178C_main[D_8011C83C_mstory2][0] | D_800A178C_main[D_8011C83C_mstory2][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C83A_mstory2);
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(D_8011C83C_mstory2, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(D_8011C83C_mstory2, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(D_8011C83C_mstory2, 2));
    func_8000B460_main(obj, 3, mots.m[D_8011C83C_mstory2][0] | 0x1D0000);
    func_8000B460_main(obj, 4, mots.m[D_8011C83C_mstory2][1] | 0x1D0000);
    func_8000B460_main(obj, 5, func_80017BB8_main(D_8011C83C_mstory2, 0x72));
    func_8000B460_main(obj, 6, func_80017BB8_main(D_8011C83C_mstory2, 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(D_8011C83C_mstory2, 0x33));
    func_8000B460_main(obj, 8, mots.m[D_8011C83C_mstory2][2] | 0x1D0000);
    func_8000B460_main(obj, 9, func_80017BB8_main(D_8011C83C_mstory2, 0x9B));
    func_8000B460_main(obj, 10, func_80017BB8_main(D_8011C83C_mstory2, 0x9C));
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 162.4f, 0.0f);
    if (D_8011C83C_mstory2 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    data = DataRead(func_80017BB8_main(D_8011C83C_mstory2, 0xA4));
    D_8011C82A_mstory2[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_8011BB60_mstory2[D_8011C83C_mstory2]);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C82A_mstory2[0], 1, 0);
    func_80032FF8_main(D_8011C82A_mstory2[0], 0);
    D_8011C830_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C82A_mstory2[0], 0, D_8011BB60_mstory2[D_8011C83C_mstory2]);
    data = DataRead(func_80017BB8_main(D_8011C83C_mstory2, 0xA9));
    D_8011C82A_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C830_mstory2 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8011C82A_mstory2[0], 0, D_8011BB60_mstory2[D_8011C83C_mstory2]);
    data = DataRead(func_80017BB8_main(D_8011C83C_mstory2, 0xAA));
    D_8011C82A_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C830_mstory2, D_8011C82A_mstory2[0]);
    omPrcSetDestructor(0, func_8010EF6C_mstory2);
    while (TRUE) {
        D_8011C760_mstory2[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010EF6C_mstory2(void) {
}

const Vec D_8011C024_mstory2 = { 0.0f, 167.0f, 0.0f };

const Vec D_8011C030_mstory2 = { 0.0f, -135.0f, 0.0f };

const Vec D_8011C03C_mstory2[2] = { { 0.0f, -53.39f, 0.0f }, { -120.0f, 0.0f, 480.0f } };

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C054_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C060_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C06C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C078_mstory2);

/* { { 20, -20, 0 }, { 0, 225, 0 }, { 0, 0, 0 }, { 0, 300, 0 } }: kept as asm, since a C definition right
   after an INCLUDE_RODATA lands in .text (GCC still believes it is in .rodata) */
INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C090_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C0C0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C108_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C168_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C174_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C180_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C18C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C198_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1A4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1B0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1BC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010EF74_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F090_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F2D8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F2F8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F460_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F6CC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F8F8_mstory2);

void func_8010FDE4_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010FDEC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010FEDC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110148_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110364_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1D4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1E0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1EC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801103E4_mstory2);

void func_801106F0_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801106F8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110910_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110930_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801109F0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110BA8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110C44_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110C64_mstory2);

void func_80110E08_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110E10_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110F54_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110F74_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110FC4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111024_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111194_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801111A0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801114A4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111D4C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111D7C_mstory2);

void func_80111EAC_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111EB4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011204C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801120C0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80112250_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113670_mstory2);

void func_80113BFC_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C204_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C210_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C21C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C228_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C240_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C24C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C258_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C264_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C27C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C2AC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C2F4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C354_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C360_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C36C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C378_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C384_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C390_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C39C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3A8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113C04_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113D20_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113F68_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113F88_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801140F0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011435C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80114588_mstory2);

void func_80114A9C_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80114AA4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80114B94_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80114E00_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011501C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3C0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3CC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3D8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011509C_mstory2);

void func_801153A8_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801153B0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801155C8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801155E8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801156A8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115860_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801158FC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011591C_mstory2);

void func_80115AC0_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115AC8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115C0C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115C2C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115C7C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115CDC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115E4C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115E60_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116164_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116A0C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116A3C_mstory2);

void func_80116B6C_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116B74_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116D0C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116D80_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116F0C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011831C_mstory2);

void func_801188A8_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3F0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3FC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C408_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C414_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C42C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C438_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C444_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C450_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C468_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C498_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C4E0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C540_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C54C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C558_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C564_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C570_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C57C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C588_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C594_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801188B0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801189CC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80118C14_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80118C34_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80118D9C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119008_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119234_mstory2);

void func_80119720_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119728_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119818_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119A84_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119CA0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5AC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5B8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5C4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119D20_mstory2);

void func_8011A02C_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A034_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A24C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A26C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A32C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A4E4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A580_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A5A0_mstory2);

void func_8011A744_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A74C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A890_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A8B0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A900_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A960_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AAD0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AAE0_mstory2);

void func_8011AB7C_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AB84_mstory2);

void func_8011AC08_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AC10_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AD8C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B080_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5DC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5E8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5F4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C600_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C60C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C618_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B198_mstory2);

void func_8011B45C_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B464_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B64C_mstory2);

void func_8011B818_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B820_mstory2);
