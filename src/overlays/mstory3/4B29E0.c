#include "common.h"

// story u4: .data 0x80115260..0x801153B0 (the rodata after it, 801154F0..80115740, is asm/data/overlays/mstory3/4C2530.rodata.s)
extern const char D_80115668_mstory3[], D_80115674_mstory3[], D_80115680_mstory3[], D_8011568C_mstory3[];
extern const char D_80115698_mstory3[], D_801156A4_mstory3[], D_801156B0_mstory3[], D_801156BC_mstory3[];
Vec D_80115260_mstory3 = { 14.0f, 193.0f, 1400.0f };
Vec D_8011526C_mstory3 = { -25.0f, 0.0f, -650.0f };
Vec D_80115278_mstory3 = { 0.0f, 1.0f, -0.0001f };
s16 D_80115284_mstory3 = 0;
s16 D_80115286_mstory3 = 0;
s32 D_80115288_mstory3 = 0;
s32 D_8011528C_mstory3 = 0;
Vec D_80115290_mstory3[4] = { { 0.0f, 200.0f, 100.0f }, { -200.0f, 100.0f, -100.0f }, { -100.0f, 300.0f, 300.0f }, { 9999.0f, 9999.0f, 9999.0f } };
Vec D_801152C0_mstory3[6] = { { -100.0f, 300.0f, 300.0f }, { -200.0f, 400.0f, -100.0f }, { 0.0f, 200.0f, 100.0f }, { 9999.0f, 9999.0f, 9999.0f }, { 0.0f, 158.73f, 0.0f }, { 0.0f, 167.01f, 0.0f } };
Vec D_80115308_mstory3 = { 0.0f, 158.46f, 0.0f };
Vec D_80115314_mstory3 = { 0.0f, -70.43f, 0.0f };
Vec D_80115320_mstory3 = { 0.0f, -77.13f, 0.0f };
Vec D_8011532C_mstory3[4] = { { 0.0f, -135.0f, 0.0f }, { 0.0f, 162.4f, 0.0f }, { 0.0f, -147.34f, 0.0f }, { 0.0f, 306.61f, 0.0f } };
Vec D_8011535C_mstory3 = { 0.0f, 90.0f, 0.0f };
Vec D_80115368_mstory3 = { 0.0f, 50.19f, 0.0f };
Vec D_80115374_mstory3 = { 0.0f, 100.78f, 0.0f };
/* model names "c000l_0_DEF" .. "c005l_0_DEF", "c300l_0_DEF", "c301l_0_DEF" */
const char *D_80115380_mstory3[8] = {
    D_801156BC_mstory3, D_801156B0_mstory3, D_801156A4_mstory3, D_80115698_mstory3,
    D_8011568C_mstory3, D_80115680_mstory3, D_80115674_mstory3, D_80115668_mstory3,
};
const char *D_801153A0_mstory3[2] = { D_801156BC_mstory3, D_801156B0_mstory3 };
u32 D_801153A8_mstory3[2] = { 0 }; /* file end padding (the unit's data ends on a 16-byte boundary) */
// end story u4

// story u1
#include "mallocblock.h"

/* a story-scene actor: its object and the action its process runs every frame (mstory1's, 4 bytes shorter) */
typedef struct StoryActor3 {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 flags; /* scene progress bits other actors wait on */
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10; /* while unk0C is 1: the footstep sound */
} StoryActor3; /* size = 0x14 */

/* A path through points (Vec list ended by a { 9999, 9999, 9999 } entry); see mstory1's 48D950.c */
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

typedef struct VecQuad {
    Vec v[4];
} VecQuad;

typedef struct VecSix {
    Vec v[6];
} VecSix;

typedef struct S16Quad {
    s16 v[4];
} S16Quad;

typedef struct MsMotTbl3 { /* actor 0's motions 3, 4 and 8 by character */
    s32 mot[8][3];
} MsMotTbl3; /* size = 0x60 */

extern TexAnimSlot *D_800D1714_main;
extern f32 D_800CE17C_main[];
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, s32);
s32 func_80050064_main(s32 write);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);

extern s16 D_80115B90_mstory3; /* the controller that drives the story messages */
extern s16 D_80115B92_mstory3; /* message window */
extern s16 D_80115B94_mstory3; /* background sprite */
extern s16 D_80115B96_mstory3; /* background model */
extern s16 D_80115B98_mstory3[8]; /* [0] the map, [1 + i] stamp i */
extern s16 D_80115BA8_mstory3[8]; /* the sparkles around the new stamp */
extern s16 D_80115BB8_mstory3; /* the white flash */
extern s32 D_80115BBC_mstory3; /* the stamp this scene wins */
extern StoryActor3 D_80115BC0_mstory3[6];
extern s16 D_80115C80_mstory3[3]; /* texture animation frames */
extern s16 D_80115C86_mstory3;
extern s16 D_80115C88_mstory3;
extern s16 D_80115C9A_mstory3; /* shadow model */
extern s16 D_80115C9C_mstory3; /* the story character (GwStory.unk1) */
extern u8 D_80115C9D_mstory3; /* its low byte */
extern s16 D_80115C9E_mstory3; /* the other one */
extern u8 D_80115C9F_mstory3; /* its low byte */
extern s16 D_80115DC0_mstory3[4]; /* play order: player per slot */

void func_801059BC_mstory3(void);
void func_801059E4_mstory3(omObjData *obj);
void func_80105A64_mstory3(void);
void func_80105B44_mstory3(void);
void func_80105B60_mstory3(void);
void func_80105C1C_mstory3(void);
void func_80105D98_mstory3(omObjData *obj);
void func_80105E9C_mstory3(omObjData *obj);
void func_80105EE4_mstory3(omObjData *obj);
void func_80105F2C_mstory3(omObjData *obj);
void func_80106340_mstory3(void);
void func_80106184_mstory3(void);
void func_801061A4_mstory3(void);
void func_80106CE8_mstory3(void);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BEAC_main(u16 spriteId, s32 arg1, s32 arg2, s32 arg3);
void func_8010643C_mstory3(void);
void func_80106DE0_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106DC4_mstory3(omObjData *obj, Vec *to, s32 frames);
void func_80107070_mstory3(omObjData *obj, Vec *to, s32 frames);
void func_80107A18_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn);
ObPath *func_80107D80_mstory3(Vec *points, s16 flags);
void func_80108084_mstory3(ObPath *path, f32 t, Vec *out);
void func_8010892C_mstory3(ObPath *path);
s32 func_80107290_mstory3(s16 model);
void func_801077BC_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80108CA8_mstory3(omObjData *obj);
void func_80108E28_mstory3(omObjData *obj);
void func_8010D5CC_mstory3(void);
void func_8010895C_mstory3(void);
void func_80108A9C_mstory3(void);
void func_80108C34_mstory3(void);
void func_80108A94_mstory3(omObjData *obj);
void func_800138EC_main(s16 model, u16 mask, u16 flags);
void func_8000CFA4_main(s16, f32, f32, f32);
s16 func_8004AC98_main(s16, s16);
void func_8010A7D0_mstory3(omObjData *obj);
void func_8010A8EC_mstory3(omObjData *obj);
void func_8010ACBC_mstory3(omObjData *obj);
void func_8010AF28_mstory3(omObjData *obj);
void func_8010B63C_mstory3(omObjData *obj);
void func_8010B72C_mstory3(omObjData *obj);
void func_8010B998_mstory3(omObjData *obj);
void func_8010BBB4_mstory3(omObjData *obj);
void func_8010BF48_mstory3(omObjData *obj);
void func_8010C17C_mstory3(omObjData *obj);
void func_8010C23C_mstory3(omObjData *obj);
void func_8010C490_mstory3(omObjData *obj);
void func_8010C7A0_mstory3(omObjData *obj);
void func_8010C7C0_mstory3(omObjData *obj);
void func_8010C810_mstory3(omObjData *obj);
void func_8010A23C_mstory3(void);
void func_8010B154_mstory3(void);
void func_8010BC34_mstory3(void);
void func_8010C4B0_mstory3(void);
void func_8010C65C_mstory3(void);
void func_8010C870_mstory3(void);
// story u1 end

/* .rodata 0x801154F0..0x80115740: the unit's constant tables and local initializers, in order */
void (*const D_801154F0_mstory3[2])(void) = { func_8010D5CC_mstory3, func_8010895C_mstory3 }; /* the scene for each story step (GwPlayer[0].coin) */
const s32 D_801154F8_mstory3[2] = { 0x3D, 0x3B }; /* and the flag set once it has been seen */
const S16Quad D_80115500_mstory3 = { { 0, 0, 0, 0 } };
const S16Quad D_80115508_mstory3 = { { 1, 2, 4, 8 } }; /* message window controller masks */
const s32 D_80115510_mstory3[7] = { 0x1D000B, 0x1D000C, 0x1D000D, 0x1D000E, 0x1D000F, 0x1D0010, 0x1D0011 }; /* stamp sprite files */
const s16 D_8011552C_mstory3[7][2] = { { 57, 20 }, { 129, 36 }, { 200, 22 }, { 215, 91 }, { 150, 124 }, { 81, 105 }, { 12, 122 } }; /* stamp positions (x, y), less 0x30 */
const Vec D_80115548_mstory3 = { -120.0f, 0.0f, 480.0f };
const Vec D_80115554_mstory3 = { 608.1f, -85.8f, -1390.3f }; /* actor 1's start position */
const Vec D_80115560_mstory3 = { 238.0f, 100.0f, 214.0f }; /* actor 2's start position */
const Vec D_8011556C_mstory3 = { 0.0f, 200.0f, 150.0f }; /* actor 3's start position */
const Vec D_80115578_mstory3 = { 0.0f, 200.0f, 100.0f }; /* actor 4's start position */
const Vec D_80115584_mstory3 = { 0.0f, 0.0f, 0.0f };
const VecQuad D_80115590_mstory3 = { { { 20.0f, -20.0f, 0.0f }, { 0.0f, 225.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 300.0f, 0.0f } } }; /* the two turns of func_80108CA8_mstory3 */
const VecSix D_801155C0_mstory3 = { { { 150.0f, 0.0f, 384.0f }, { 0.0f, 200.0f, 300.0f }, { 0.0f, 200.0f, 150.0f }, { 300.0f, 25.0f, 400.0f }, { 300.0f, 125.0f, 400.0f }, { 238.0f, 100.0f, 214.0f } } }; /* func_80108E28_mstory3's walk targets */
const MsMotTbl3 D_80115608_mstory3 = { {
    { 0x40, 0x3E, 0x42 }, { 0x4B, 0x48, 0x4D }, { 0x54, 0x52, 0x56 }, { 0x5D, 0x5B, 0x5F },
    { 0x67, 0x65, 0x69 }, { 0x70, 0x6E, 0x72 }, { 0x4B, 0x48, 0x4D }, { 0x54, 0x52, 0x56 },
} };
const char D_80115668_mstory3[] = "c301l_0_DEF";
const char D_80115674_mstory3[] = "c300l_0_DEF";
const char D_80115680_mstory3[] = "c005l_0_DEF";
const char D_8011568C_mstory3[] = "c004l_0_DEF";
const char D_80115698_mstory3[] = "c003l_0_DEF";
const char D_801156A4_mstory3[] = "c002l_0_DEF";
const char D_801156B0_mstory3[] = "c001l_0_DEF";
const char D_801156BC_mstory3[] = "c000l_0_DEF";
const char D_801156C8_mstory3[] = "item_hook";
const Vec D_801156D4_mstory3 = { 0.0f, 180.0f, 0.0f };
const Vec D_801156E0_mstory3 = { 0.0f, 0.0f, 0.0f };
const Vec D_801156EC_mstory3 = { 0.0f, -180.0f, 0.0f };
const char D_801156F8_mstory3[] = "c204n_0_DEF";
const Vec D_80115704_mstory3 = { 0.0f, 167.0f, 0.0f };
const Vec D_80115710_mstory3 = { 0.0f, -135.0f, 0.0f };
const Vec D_8011571C_mstory3 = { 0.0f, -53.39f, 0.0f };
const Vec D_80115728_mstory3 = { 0.0f, -53.390015f, 0.0f };
const Vec D_80115734_mstory3 = { 0.0f, 0.0f, 0.0f };

void func_801059A0_mstory3(void) {
    func_80105C1C_mstory3();
}

void func_801059BC_mstory3(void) {
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_801059E4_mstory3(omObjData *obj) {
    D_800CE17C_main[0] = D_80115260_mstory3.x;
    D_800CE17C_main[1] = D_80115260_mstory3.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_80115260_mstory3, &D_8011526C_mstory3, &D_80115278_mstory3);
    Hu3DCamUpdateMtx(0);
}

void func_80105A64_mstory3(void) {
    omObjData *obj;

    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 35.0f, 80.0f, 8000.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_801059E4_mstory3);
    omSetStatBit(obj, 0xA0);
    func_801059E4_mstory3(obj);
}

void func_80105B44_mstory3(void) {
    func_8005A6B0_main();
}

void func_80105B60_mstory3(void) {
    s16 n = 0;
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayer[j].group) {
                D_80115DC0_mstory3[n++] = j;
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

void func_80105C1C_mstory3(void) {
    s16 step;

    func_800142A0_main(0x20);
    omInitObjMan(0x20, 0x20);
    func_801059BC_mstory3();
    func_80105A64_mstory3();
    func_80105B44_mstory3();
    func_80105B60_mstory3();
    step = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        step = 1;
    }
    omAddObj(0, 0, 0, -1, func_80105D98_mstory3);
    omAddObj(0, 0, 0, -1, func_80105F2C_mstory3);
    func_80106340_mstory3();
    if (_CheckFlag(D_801154F8_mstory3[step]) != 0) {
        D_80115284_mstory3 = 1;
    } else {
        _SetFlag(D_801154F8_mstory3[step]);
    }
    for (D_80115B90_mstory3 = 0; D_80115B90_mstory3 < 4; D_80115B90_mstory3++) {
        if (CheckControllerRead(D_80115B90_mstory3) != 0) {
            break;
        }
    }
    if (D_80115B90_mstory3 >= 4) {
        D_80115B90_mstory3 = 0;
    }
    D_801154F0_mstory3[step]();
    WipeCreateIn(2, 0x10);
}

void func_80105D98_mstory3(omObjData *obj) {
    s16 state = D_80115286_mstory3;

    switch (state) {
    case 0:
        HuAudSeqPlay(0x26);
        state++;
        break;
    case 1:
        if (WipeStatGet() == 0) {
            state++;
        }
        break;
    case 2:
        if (D_80115284_mstory3 == 1) {
            if (D_800D5558_main[D_80115B90_mstory3] & 0x1000) {
                state++;
            }
        }
        break;
    case 3:
        obj->func = func_80105EE4_mstory3;
        state++;
        break;
    default:
        obj->func = func_80105EE4_mstory3;
        break;
    }
    D_80115286_mstory3 = state;
}

void func_80105E8C_mstory3(void) {
    D_80115286_mstory3 = 3;
}

void func_80105E9C_mstory3(omObjData *obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        func_8005F524_main();
        func_80050064_main(1);
        omOvlReturnEx(1);
    }
}

void func_80105EE4_mstory3(omObjData *obj) {
    WipeCreateOut(2, 0x14);
    HuAudSeqFadeOut(0x1E);
    func_8004AB0C_main(0x1E);
    obj->func = func_80105E9C_mstory3;
}

void func_80105F2C_mstory3(omObjData *obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80105EE4_mstory3;
    }
}

/* opens the story message window, driven by controller D_80115B90_mstory3 */
void func_80105F54_mstory3(void) {
    S16Quad a = D_80115500_mstory3;
    S16Quad b = D_80115508_mstory3;

    D_80115B92_mstory3 = func_80060880_main(0xA0, 0xC2, 0x14);
    a.v[D_80115B90_mstory3] = -1;
    func_8005B63C_main(D_80115B92_mstory3, 2, 0);
    func_8005FE54_main(D_80115B92_mstory3, b.v[D_80115B90_mstory3]);
    func_8005F744_main(a.v[0], a.v[1], a.v[2], a.v[3]);
}

void func_8010603C_mstory3(void) {
    func_8005D294_main(D_80115B92_mstory3);
    func_80060C14_main(D_80115B92_mstory3, 1);
}

void func_8010606C_mstory3(void) {
    func_80060EA8_main(D_80115B92_mstory3, 1);
}

void func_80106090_mstory3(s32 mess) {
    func_8005B43C_main(D_80115B92_mstory3, mess, -1, -1);
    while (func_8005E0C0_main(D_80115B92_mstory3) != 0) {
        HuPrcVSleep();
    }
}

void func_801060E4_mstory3(s32 mess) {
    func_8005B43C_main(D_80115B92_mstory3, mess, -1, -1);
    func_8005B6BC_main(D_80115B92_mstory3, GwStory.unk1 + 0x1C00, 0);
    while (func_8005E0C0_main(D_80115B92_mstory3) != 0) {
        HuPrcVSleep();
    }
}

s16 func_80106154_mstory3(void) {
    return func_8005E1D8_main(D_80115B92_mstory3, 0, 1);
}

void func_80106184_mstory3(void) {
    func_8000BB54_main(D_80115B94_mstory3);
}

void func_801061A4_mstory3(void) {
    func_8000BB94_main(D_80115B94_mstory3);
}

void func_801061C4_mstory3(void) {
    func_8001C814_main(D_80115B96_mstory3, 4, 0);
    func_8001C814_main(D_80115B96_mstory3, 1, 0);
    func_8001C6A8_main(D_80115B96_mstory3, 0.0f);
    func_8001C92C_main(D_80115B96_mstory3, 2.0f);
}

void func_80106220_mstory3(void) {
    func_8001C814_main(D_80115B96_mstory3, 4, 4);
    func_8001C814_main(D_80115B96_mstory3, 1, 0);
    func_8001C6A8_main(D_80115B96_mstory3, HmfModelData[D_80115B96_mstory3].unk40);
}

void func_80106284_mstory3(void) {
    s16 i = 0;

    HmfModelData[D_80115B96_mstory3].rot.y += -10.6f;
    do {
        HmfModelData[D_80115B96_mstory3].rot.x += 17.84f;
        HuPrcVSleep();
        i++;
    } while (i < 5);
}

void func_80106340_mstory3(void) {
    D_80115B94_mstory3 = InitEspriteSlot(func_8000B838_main(0x1D0012), 0, 0);
    func_8000BBD4_main(D_80115B94_mstory3, 0xA0, 0x78);
    func_8000BC48_main(D_80115B94_mstory3, 0x4000);
    D_80115B96_mstory3 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_80115B96_mstory3, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_80115B96_mstory3, 2, 0);
    func_8001C814_main(D_80115B96_mstory3, 1, 1);
}

void func_80106400_mstory3(s32 arg0) {
    D_80115BBC_mstory3 = arg0;
    D_80115288_mstory3 = 0;
    omAddPrcObj(func_8010643C_mstory3, 0x1000, 0x800, 0);
}

// masked 0 but for a nop KMC puts after each of the cosdf/sindf calls that retail does not have (2 instructions)
#ifdef NON_MATCHING
/* the stamp screen: the map with the stamps won so far, a flash, then stamp D_80115BBC_mstory3
   fades in inside a ring of sparkles (a second flash for the last one); sets D_80115288_mstory3 */
void func_8010643C_mstory3(void) {
    void *file;
    f32 x;
    f32 y;
    f32 alpha;
    s32 i;
    s32 j;

    D_80115B98_mstory3[0] = InitEspriteSlot(func_8000B838_main(0x1D0001), 0, 0);
    func_8000BBD4_main(D_80115B98_mstory3[0], 0xA0, 0x78);
    func_8000BB94_main(D_80115B98_mstory3[0]);
    for (i = 0; i < 7; i++) {
        D_80115B98_mstory3[i + 1] = InitEspriteSlot(func_8000B838_main(D_80115510_mstory3[i]), 0, 0);
        func_8000BBD4_main(D_80115B98_mstory3[i + 1], D_8011552C_mstory3[i][0] + 0x30,
                           D_8011552C_mstory3[i][1] + 0x30);
        func_8000BC48_main(D_80115B98_mstory3[i + 1], 8);
        func_8000BB94_main(D_80115B98_mstory3[i + 1]);
    }
    file = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        D_80115BA8_mstory3[i] = InitEspriteSlot(func_80055810_main(file), 0, 1);
        x = D_8011552C_mstory3[D_80115BBC_mstory3][0] + 0x30;
        y = D_8011552C_mstory3[D_80115BBC_mstory3][1] + 0x30;
        x += cosdf(i * 45.0f) * 32.0f;
        y -= sindf(i * 45.0f) * 32.0f;
        func_8000BBD4_main(D_80115BA8_mstory3[i], x, y);
        func_8000BC48_main(D_80115BA8_mstory3[i], 0x1000);
        func_8000BEAC_main(D_80115BA8_mstory3[i], 0xFF, 0xFF, 0xC0);
        func_8000BC48_main(D_80115BA8_mstory3[i], 8);
        func_8000BE5C_main(D_80115BA8_mstory3[i], 1.5f, 1.5f);
        func_8000BBFC_main(D_80115BA8_mstory3[i], 0xFF);
        func_8000BB94_main(D_80115BA8_mstory3[i]);
    }
    HuMemMemoryFreePerm(file);
    D_80115BB8_mstory3 = InitEspriteSlot(func_8000B838_main(0x1D0000), 0, 0);
    func_8000BBD4_main(D_80115BB8_mstory3, 0xA0, 0x78);
    func_8000BE5C_main(D_80115BB8_mstory3, 40.0f, 30.0f);
    func_8000BC48_main(D_80115BB8_mstory3, 0);
    func_8000BB94_main(D_80115BB8_mstory3);
    omPrcSetDestructor(0, func_80106CE8_mstory3);
    func_8000BB54_main(D_80115BB8_mstory3);
    func_8000BBFC_main(D_80115BB8_mstory3, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_80115BB8_mstory3, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_80115BB8_mstory3, 0x100);
    for (i = 0; i < D_80115BBC_mstory3; i++) {
        func_8000BB54_main(D_80115B98_mstory3[i + 1]);
    }
    func_801061A4_mstory3();
    func_8000BB54_main(D_80115B98_mstory3[0]);
    HuPrcSleep(0x1E);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_80115BB8_mstory3, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_80115BB8_mstory3);
    func_8000BBFC_main(D_80115B98_mstory3[D_80115BBC_mstory3 + 1], 0);
    func_8000BB54_main(D_80115B98_mstory3[D_80115BBC_mstory3 + 1]);
    for (j = 0, alpha = 0.0f; j < 20; j++) {
        alpha += 12.75f;
        func_8000BBFC_main(D_80115B98_mstory3[D_80115BBC_mstory3 + 1], alpha);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_80115B98_mstory3[D_80115BBC_mstory3 + 1], 0xFF);
    func_8000BE5C_main(D_80115B98_mstory3[D_80115BBC_mstory3 + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        func_8000BD94_main(D_80115BA8_mstory3[i], 0, 0);
        func_8000BDDC_main(D_80115BA8_mstory3[i], 1);
        func_8000BB54_main(D_80115BA8_mstory3[i]);
    }
    HuPrcSleep(0x14);
    for (i = 0; i < 8; i++) {
        func_8000BB94_main(D_80115BA8_mstory3[i]);
    }
    if (D_80115BBC_mstory3 == 6) {
        HuPrcSleep(0x28);
        func_8000BB54_main(D_80115BB8_mstory3);
        func_8000BBFC_main(D_80115BB8_mstory3, 0);
        for (i = 0; i < 5; i++) {
            func_8000BBFC_main(D_80115BB8_mstory3, i * 0.125f * 255.0f);
            HuPrcVSleep();
        }
        func_8000BBFC_main(D_80115BB8_mstory3, 0x100);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            func_8000BBFC_main(D_80115BB8_mstory3, 255.0f - i * 0.125f * 255.0f);
            HuPrcVSleep();
        }
        func_8000BB94_main(D_80115BB8_mstory3);
        HuPrcSleep(0x50);
    } else {
        HuPrcSleep(0x3C);
    }
    func_8000BB54_main(D_80115BB8_mstory3);
    func_8000BBFC_main(D_80115BB8_mstory3, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_80115BB8_mstory3, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_80115BB8_mstory3, 0x100);
    func_8000BB94_main(D_80115B98_mstory3[D_80115BBC_mstory3 + 1]);
    func_8000BB94_main(D_80115B98_mstory3[0]);
    func_80106184_mstory3();
    HuPrcSleep(0x1E);
    for (i = 0; i < D_80115BBC_mstory3; i++) {
        func_8000BB94_main(D_80115B98_mstory3[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_80115BB8_mstory3, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_80115BB8_mstory3);
    D_80115288_mstory3 = 1;
    while (1) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010643C_mstory3);
#endif

s32 func_80106CDC_mstory3(void) {
    return D_80115288_mstory3;
}

void func_80106CE8_mstory3(void) {
}

void func_80106CF0_mstory3(s16 model, s16 anim, s16 frame) {
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

void func_80106DC4_mstory3(omObjData *obj, Vec *to, s32 frames) {
    func_80106DE0_mstory3(obj, to, frames, 1);
}

// register allocation; retail converts frames separately for the divide (masked 8, as mstory1's func_80106B30)
#ifdef NON_MATCHING
/* walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning
   it to face the way first when `turn` is set */
void func_80106DE0_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106DE0_mstory3);
#endif

void func_80107014_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106DC4_mstory3(obj, &to, frames);
}

void func_80107040_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106DE0_mstory3(obj, &to, frames, turn);
}

void func_80107070_mstory3(omObjData *obj, Vec *to, s32 frames) {
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

void func_80107218_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80107070_mstory3(obj, &to, frames);
}

void func_80107244_mstory3(s16 model) {
    HuPrcSleep(10);
    while (func_80107290_mstory3(model) == 0) {
        HuPrcVSleep();
    }
}

s32 func_80107290_mstory3(s16 model) {
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

/* walks obj (and its shadow) forwards along its facing, speed per frame for frames frames */
void func_8010733C_mstory3(omObjData *obj, f32 speed, s16 frames) {
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

/* walks obj (and its shadow) backwards: as func_8010733C_mstory3 */
void func_801074D8_mstory3(omObjData *obj, f32 speed, s16 frames) {
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

void func_80107674_mstory3(omObjData *a, omObjData *b) {
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

// register allocation; retail converts frames separately for the divide and the loop (masked 10, as mstory1's func_80106D80)
#ifdef NON_MATCHING
/* as func_80106DE0_mstory3, but the second model follows 5 below the first */
void func_801077BC_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801077BC_mstory3);
#endif

// retail converts frames again for the loop test instead of reusing the divide's (masked 15: that, then shifted branches)
#ifdef NON_MATCHING
/* walks obj's model (and its shadow, 5 below) towards `to` in `frames` frames, speeding up after
   frame 50; stops early once it passes to->x on the way down in x */
void func_80107A18_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn) {
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
            pos.x += (step.x += accel.x);
            pos.y += (step.y += accel.y);
            pos.z += (step.z += accel.z);
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107A18_mstory3);
#endif

ObPath *func_80107D80_mstory3(Vec *points, s16 flags) {
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

// register allocation only (masked 0), as mstory1's func_801077C4
#ifdef NON_MATCHING
/* the point at t (0..1) along a path: a spline through the four points around the segment t
   falls in */
void func_80108084_mstory3(ObPath *path, f32 t, Vec *out) {
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
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108084_mstory3);
#endif

void func_8010892C_mstory3(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

/* story step 2: the cast, its processes and the sound process */
void func_8010895C_mstory3(void) {
    if ((D_80115C9C_mstory3 = GwStory.unk1) == 0) {
        D_80115C9E_mstory3 = 1;
    } else {
        D_80115C9E_mstory3 = 0;
    }
    func_80105F54_mstory3();
    D_80115C9A_mstory3 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010A23C_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B154_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010BC34_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C4B0_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C870_mstory3, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_80108C34_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C65C_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80108A9C_mstory3, 0x1001, 0x1000, 0);
    func_8001C258_main(D_80115C9A_mstory3, 4, 4);
}

void func_80108A94_mstory3(omObjData *obj) {
}

/* plays the footstep sounds of actors 0 and 1 when their motion loops (actor 1 panned by its depth) */
void func_80108A9C_mstory3(void) {
    s16 fx;
    s8 pan;
    f32 z;

    while (1) {
        if (D_80115BC0_mstory3[0].unk0C == 1
            && HmfModelData[D_80115BC0_mstory3[0].obj->model[1]].unk40 == 0.0f) {
            CharFXPlay(D_80115BC0_mstory3[0].unk10, D_80115C9D_mstory3);
        }
        if (D_80115BC0_mstory3[1].unk0C == 1
            && HmfModelData[D_80115BC0_mstory3[1].obj->model[1]].unk40 == 0.0f) {
            fx = CharFXPlay(D_80115BC0_mstory3[1].unk10, D_80115C9F_mstory3);
            z = HmfModelData[D_80115BC0_mstory3[1].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                pan = z / 15.0f + 127.0f;
            } else {
                pan = 0x7F;
            }
            func_8004AAD0_main(fx, pan);
        }
        HuPrcVSleep();
    }
}

/* actor 5's process: runs its action every frame */
void func_80108C34_mstory3(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_80115BC0_mstory3[5].obj = obj;
    D_80115BC0_mstory3[5].flags = 0;
    D_80115BC0_mstory3[5].func = func_80108CA8_mstory3;
    while (1) {
        D_80115BC0_mstory3[5].func(obj);
        HuPrcVSleep();
    }
}

/* actors 3 and 2 turn, talk, and turn back; then actor 5 moves on to func_80108E28_mstory3 */
void func_80108CA8_mstory3(omObjData *obj) {
    VecQuad rot = D_80115590_mstory3;
    s32 mess;

    HuPrcSleep(0x28);
    func_80107070_mstory3(D_80115BC0_mstory3[3].obj, &rot.v[0], 10);
    func_80107070_mstory3(D_80115BC0_mstory3[2].obj, &rot.v[1], 10);
    HuAudFXPlay(0x159);
    func_8001C624_main(D_80115BC0_mstory3[3].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[3].obj->motion[1]].unk02, 0, 10, 2);
    func_8010603C_mstory3();
    mess = 0x5B38;
    if (D_80115C9C_mstory3 != 0) {
        mess = 0x5A45;
    }
    func_80106090_mstory3(mess);
    func_8010606C_mstory3();
    func_8001C624_main(D_80115BC0_mstory3[3].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[3].obj->motion[0]].unk02, 0, 10, 2);
    func_80107070_mstory3(D_80115BC0_mstory3[3].obj, &rot.v[2], 10);
    func_80107070_mstory3(D_80115BC0_mstory3[2].obj, &rot.v[3], 10);
    D_80115BC0_mstory3[5].func = func_80108E28_mstory3;
}

/* actor 5's main scene: actor 4 flies in along a path, the cast reacts and talks (two rounds of it
   for the second story character), actor 4 flies off, the stars are handed over, then the scene ends */
void func_80108E28_mstory3(omObjData *obj) {
    Vec pos;
    ObPath *path[2];
    s16 n = 0;
    VecSix to = D_801155C0_mstory3;
    s16 i;
    f32 t;
    s32 mess;

    func_8001C258_main(D_80115BC0_mstory3[4].obj->model[1], 4, 0);
    func_8001C258_main(D_80115BC0_mstory3[4].obj->model[2], 4, 0);
    func_800138EC_main(D_80115BC0_mstory3[4].obj->model[2], 1, 1);
    HuAudFXPlay(0x215);
    path[0] = func_80107D80_mstory3(D_80115290_mstory3, 0);
    for (i = 0; i < 40.0f; i++) {
        if (i == 30) {
            func_8001C624_main(D_80115BC0_mstory3[0].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[0].obj->motion[9]].unk02, 0, 10, 2);
        }
        t = i * 0.025f;
        func_80108084_mstory3(path[0], t * t, &pos);
        Hu3DModelPosSet(D_80115BC0_mstory3[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115BC0_mstory3[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010892C_mstory3(path[0]);
    D_80115BC0_mstory3[0].func = func_8010A7D0_mstory3;
    while (1) {
        if (D_80115BC0_mstory3[0].flags == 1) {
            pos.x -= 0.19999999f;
            pos.y -= 2.0f;
            pos.z += 1.0f;
            Hu3DModelPosSet(D_80115BC0_mstory3[4].obj->model[1], pos.x, pos.y, pos.z);
            func_8000CFA4_main(D_80115BC0_mstory3[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
            if (n++ == 30.0f) {
                n = 0;
                break;
            }
        }
        HuPrcVSleep();
    }
    func_8004AAD0_main(CharFXPlay(0x2BD, D_80115C9F_mstory3), 0x50);
    HuPrcSleep(0x1E);
    func_8001C258_main(D_80115BC0_mstory3[1].obj->model[1], 4, 0);
    func_8001C258_main(D_80115BC0_mstory3[1].obj->model[2], 4, 0);
    func_801061C4_mstory3();
    HuPrcSleep(10);
    D_80115BC0_mstory3[0].func = func_8010A8EC_mstory3;
    D_80115BC0_mstory3[2].func = func_8010BF48_mstory3;
    while (1) {
        pos.x += 1.0f;
        pos.y += 10.0f;
        pos.z -= 5.0f;
        Hu3DModelPosSet(D_80115BC0_mstory3[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115BC0_mstory3[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        if (n++ == 6.0f) {
            break;
        }
        HuPrcVSleep();
    }
    D_801152C0_mstory3[0].x = pos.x;
    D_801152C0_mstory3[0].y = pos.y;
    D_801152C0_mstory3[0].z = pos.z;
    func_80107070_mstory3(D_80115BC0_mstory3[3].obj, &D_80115308_mstory3, 5);
    D_80115BC0_mstory3[3].func = func_8010C7A0_mstory3;
    while (1) {
        if (D_80115BC0_mstory3[2].flags == 5) {
            break;
        }
        HuPrcVSleep();
    }
    func_80107244_mstory3(D_80115BC0_mstory3[1].obj->model[1]);
    HuPrcSleep(0x1E);
    D_80115BC0_mstory3[1].unk0C = 1;
    D_80115BC0_mstory3[1].unk10 = 0x28;
    func_8001C92C_main(D_80115BC0_mstory3[0].obj->model[1], 0.25f);
    func_8001C624_main(D_80115BC0_mstory3[0].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[0].obj->motion[10]].unk02, 0, 10, 2);
    func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[1].obj->motion[2]].unk02, 0, 10, 2);
    func_80107A18_mstory3(D_80115BC0_mstory3[1].obj, &to.v[0], 0xB4, 1);
    D_80115BC0_mstory3[1].unk0C = 0;
    func_8001C624_main(D_80115BC0_mstory3[0].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[0].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C92C_main(D_80115BC0_mstory3[0].obj->model[1], 1.0f);
    func_80106CF0_mstory3(D_80115BC0_mstory3[2].obj->model[1], D_80115C86_mstory3, D_80115C80_mstory3[0]);
    func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[1].obj->motion[3]].unk02, 0, 10, 2);
    HuPrcSleep(0x3C);
    func_80106CF0_mstory3(D_80115BC0_mstory3[2].obj->model[1], D_80115C86_mstory3, D_80115C80_mstory3[0]);
    func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[1].obj->motion[0]].unk02, 0, 10, 2);
    func_80107070_mstory3(D_80115BC0_mstory3[1].obj, &D_80115314_mstory3, 10);
    if (D_80115C9C_mstory3 != 0) {
        func_80106DE0_mstory3(D_80115BC0_mstory3[2].obj, &to.v[3], 15, 0);
        func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                           HmfModelData[D_80115BC0_mstory3[1].obj->motion[1]].unk02, 0, 10, 2);
        func_80107070_mstory3(D_80115BC0_mstory3[1].obj, &D_8011535C_mstory3, 10);
        func_8001C624_main(D_80115BC0_mstory3[0].obj->model[1],
                           HmfModelData[D_80115BC0_mstory3[0].obj->motion[0]].unk02, 0, 10, 2);
        func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                           HmfModelData[D_80115BC0_mstory3[1].obj->motion[5]].unk02, 0, 10, 0);
        HuPrcSleep(10);
        func_8001C624_main(D_80115BC0_mstory3[2].obj->model[1],
                           HmfModelData[D_80115BC0_mstory3[2].obj->motion[2]].unk02, 0, 10, 2);
        func_80107244_mstory3(D_80115BC0_mstory3[1].obj->model[1]);
        func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                           HmfModelData[D_80115BC0_mstory3[1].obj->motion[5]].unk02, 0, 10, 0);
        func_80107244_mstory3(D_80115BC0_mstory3[1].obj->model[1]);
        func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                           HmfModelData[D_80115BC0_mstory3[1].obj->motion[0]].unk02, 0, 10, 2);
        func_8001C624_main(D_80115BC0_mstory3[2].obj->model[1],
                           HmfModelData[D_80115BC0_mstory3[2].obj->motion[0]].unk02, 0, 10, 2);
        D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
        func_80106DC4_mstory3(D_80115BC0_mstory3[2].obj, &to.v[4], 8);
        func_80107070_mstory3(D_80115BC0_mstory3[2].obj, &D_80115320_mstory3, 10);
        func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                           HmfModelData[D_80115BC0_mstory3[1].obj->motion[1]].unk02, 0, 10, 2);
        func_80107070_mstory3(D_80115BC0_mstory3[1].obj, &D_80115314_mstory3, 5);
        func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                           HmfModelData[D_80115BC0_mstory3[1].obj->motion[0]].unk02, 0, 10, 2);
        D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
        D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
        func_80107070_mstory3(D_80115BC0_mstory3[3].obj, &D_80115368_mstory3, 5);
        func_80107070_mstory3(D_80115BC0_mstory3[0].obj, &D_80115374_mstory3, 5);
        func_8010603C_mstory3();
        func_80106090_mstory3(0x5A46);
        func_8010606C_mstory3();
    } else {
        for (i = 0; i < 2; i++) {
            func_80106DE0_mstory3(D_80115BC0_mstory3[2].obj, &to.v[3], 15, 0);
            func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[1].obj->motion[1]].unk02, 0, 10, 2);
            func_80107070_mstory3(D_80115BC0_mstory3[1].obj, &D_8011535C_mstory3, 10);
            func_8001C624_main(D_80115BC0_mstory3[0].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[0].obj->motion[0]].unk02, 0, 10, 2);
            func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[1].obj->motion[5]].unk02, 0, 10, 0);
            HuPrcSleep(10);
            func_8001C624_main(D_80115BC0_mstory3[2].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[2].obj->motion[2]].unk02, 0, 10, 2);
            func_80107244_mstory3(D_80115BC0_mstory3[1].obj->model[1]);
            if (i == 0) {
                func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                                   HmfModelData[D_80115BC0_mstory3[1].obj->motion[5]].unk02, 0, 10, 0);
                func_80107244_mstory3(D_80115BC0_mstory3[1].obj->model[1]);
            }
            func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[1].obj->motion[0]].unk02, 0, 10, 2);
            func_8001C624_main(D_80115BC0_mstory3[2].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[2].obj->motion[0]].unk02, 0, 10, 2);
            D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
            func_80106DC4_mstory3(D_80115BC0_mstory3[2].obj, &to.v[4], 8);
            func_80107070_mstory3(D_80115BC0_mstory3[2].obj, &D_80115320_mstory3, 10);
            func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[1].obj->motion[1]].unk02, 0, 10, 2);
            func_80107070_mstory3(D_80115BC0_mstory3[1].obj, &D_80115314_mstory3, 5);
            func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[1].obj->motion[0]].unk02, 0, 10, 2);
            D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
            D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
            func_80107070_mstory3(D_80115BC0_mstory3[3].obj, &D_80115368_mstory3, 5);
            func_80107070_mstory3(D_80115BC0_mstory3[0].obj, &D_80115374_mstory3, 5);
            func_8010603C_mstory3();
            D_80115BC0_mstory3[1].func = func_8010BBB4_mstory3;
            func_80106090_mstory3(i + 0x5B39);
            func_8010606C_mstory3();
            func_8001C624_main(D_80115BC0_mstory3[0].obj->model[1],
                               HmfModelData[D_80115BC0_mstory3[0].obj->motion[8]].unk02, 0, 10, 0);
            func_80107244_mstory3(D_80115BC0_mstory3[0].obj->model[1]);
        }
        func_80107244_mstory3(D_80115BC0_mstory3[1].obj->model[1]);
    }
    func_8001C624_main(D_80115BC0_mstory3[0].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[0].obj->motion[0]].unk02, 0, 10, 2);
    func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[1].obj->motion[1]].unk02, 0, 10, 2);
    D_80115BC0_mstory3[1].func = func_8010B63C_mstory3;
    D_80115BC0_mstory3[2].func = func_8010C17C_mstory3;
    D_80115BC0_mstory3[3].func = func_8010C7C0_mstory3;
    path[1] = func_80107D80_mstory3(D_801152C0_mstory3, 0);
    for (i = 0; i < 50.0f; i++) {
        t = i * 0.02f;
        func_80108084_mstory3(path[1], t * t, &pos);
        Hu3DModelPosSet(D_80115BC0_mstory3[4].obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115BC0_mstory3[4].obj->model[2], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010892C_mstory3(path[1]);
    func_8001C258_main(D_80115BC0_mstory3[4].obj->model[1], 4, 4);
    func_8001C258_main(D_80115BC0_mstory3[4].obj->model[2], 4, 4);
    func_800138EC_main(D_80115BC0_mstory3[4].obj->model[2], 1, 0);
    HuPrcSleep(5);
    func_80106CF0_mstory3(D_80115BC0_mstory3[2].obj->model[1], D_80115C86_mstory3, D_80115C80_mstory3[2]);
    func_8001C624_main(D_80115BC0_mstory3[2].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[2].obj->motion[1]].unk02, 0, 10, 2);
    D_80115BC0_mstory3[2].func = func_8010C490_mstory3;
    HuPrcSleep(10);
    func_80106DC4_mstory3(D_80115BC0_mstory3[2].obj, &to.v[5], 0x3C);
    HuPrcSleep(0x1E);
    D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
    func_80107070_mstory3(D_80115BC0_mstory3[2].obj, &D_8011532C_mstory3[0], 10);
    func_8010603C_mstory3();
    mess = 0x5B3B;
    if (D_80115C9C_mstory3 == 0) {
        mess = 0x5A47;
    }
    func_80106090_mstory3(mess);
    func_8010606C_mstory3();
    HuPrcSleep(0x1E);
    D_80115C88_mstory3 = 1;
    to.v[2].y = to.v[1].y = HmfModelData[D_80115BC0_mstory3[3].obj->model[1]].pos.y;
    func_80106DC4_mstory3(D_80115BC0_mstory3[3].obj, &to.v[1], 3);
    HuAudFXPlay(0x217);
    D_80115BC0_mstory3[2].func = func_8010C23C_mstory3;
    D_80115BC0_mstory3[3].func = func_8010C810_mstory3;
    D_80115BC0_mstory3[0].func = func_8010ACBC_mstory3;
    D_80115BC0_mstory3[1].func = func_8010B72C_mstory3;
    func_8004AC98_main(D_80115C9C_mstory3 + 0x2AC, 0);
    func_8004AC98_main(D_80115C9E_mstory3 + 0x2AC, 1);
    D_80115C88_mstory3 = 0;
    func_80106DE0_mstory3(D_80115BC0_mstory3[3].obj, &to.v[2], 5, 0);
    while (1) {
        if (D_80115BC0_mstory3[2].flags == 1) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_8001C624_main(D_80115BC0_mstory3[3].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[3].obj->motion[1]].unk02, 0, 10, 2);
    func_8010603C_mstory3();
    mess = 0x5B3C;
    if (D_80115C9C_mstory3 != 0) {
        mess = 0x5A48;
    }
    func_80106090_mstory3(mess);
    func_8010606C_mstory3();
    func_8001C624_main(D_80115BC0_mstory3[3].obj->model[1],
                       HmfModelData[D_80115BC0_mstory3[3].obj->motion[0]].unk02, 0, 10, 2);
    D_80115BC0_mstory3[0].func = func_8010AF28_mstory3;
    D_80115BC0_mstory3[1].func = func_8010B998_mstory3;
    while (1) {
        if (D_80115BC0_mstory3[0].flags == 10 && D_80115BC0_mstory3[1].flags == D_80115BC0_mstory3[0].flags) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);
    func_80105E8C_mstory3();
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[4].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[1].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[5].func = func_80108A94_mstory3;
}

// story u2
/* a chapter-3 scene actor (stride 0x14): its object and the step its process calls every frame */
typedef StoryActor3 MsActor3;

extern s16 D_80115C8A_mstory3[3]; /* actor 0's texture animations */
extern s16 D_80115C90_mstory3;
extern s16 D_80115C92_mstory3[3]; /* actor 1's texture animations */
extern s16 D_80115C98_mstory3;
extern s32 D_800A178C_main[][6];

void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);

void func_8010A7C8_mstory3(void);
void func_8010AB34_mstory3(omObjData *obj);
void func_8010C3F4_mstory3(omObjData *obj);
extern Vec D_80115C50_mstory3; /* actor 2's position */
extern Vec D_80115C5C_mstory3; /* actor 3's position */
void func_8010C654_mstory3(void);
extern Vec D_80115C68_mstory3; /* actor 4's position */
void func_8010C9E0_mstory3(void);
void func_8010BF40_mstory3(void);
void func_8010C15C_mstory3(omObjData *obj);
extern Vec D_80115C44_mstory3; /* actor 1's position */
void func_8010B634_mstory3(void);
void func_8010AB54_mstory3(omObjData *obj);

/* actor 0: the player's character */
void func_8010A23C_mstory3(void) {
    MsMotTbl3 tbl;
    omObjData *obj;
    void *data;

    tbl = D_80115608_mstory3;
    obj = omAddObj(10, 20, 20, -1, NULL);
    D_80115BC0_mstory3[0].obj = obj;
    D_80115BC0_mstory3[0].flags = 0;
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[0].unk0C = 0;
    D_80115BC0_mstory3[0].unk10 = 0x1F;
    obj->model[1] = func_8000B108_main(D_800A178C_main[D_80115C9C_mstory3][0] | D_800A178C_main[D_80115C9C_mstory3][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C9A_mstory3);
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(D_80115C9C_mstory3, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(D_80115C9C_mstory3, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(D_80115C9C_mstory3, 2));
    func_8000B460_main(obj, 3, tbl.mot[D_80115C9C_mstory3][0] | 0x1D0000);
    func_8000B460_main(obj, 4, tbl.mot[D_80115C9C_mstory3][1] | 0x1D0000);
    func_8000B460_main(obj, 5, func_80017BB8_main(D_80115C9C_mstory3, 0x72));
    func_8000B460_main(obj, 6, func_80017BB8_main(D_80115C9C_mstory3, 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(D_80115C9C_mstory3, 0x33));
    func_8000B460_main(obj, 8, tbl.mot[D_80115C9C_mstory3][2] | 0x1D0000);
    func_8000B460_main(obj, 9, func_80017BB8_main(D_80115C9C_mstory3, 0x9B));
    func_8000B460_main(obj, 10, func_80017BB8_main(D_80115C9C_mstory3, 0x9C));
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 162.4f, 0.0f);
    if (D_80115C9C_mstory3 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    data = DataRead(func_80017BB8_main(D_80115C9C_mstory3, 0xA4));
    D_80115C8A_mstory3[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, (char *)D_80115380_mstory3[D_80115C9C_mstory3]);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115C8A_mstory3[0], 1, 0);
    func_80032FF8_main(D_80115C8A_mstory3[0], 0);
    D_80115C90_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115C8A_mstory3[0], 0, (char *)D_80115380_mstory3[D_80115C9C_mstory3]);
    data = DataRead(func_80017BB8_main(D_80115C9C_mstory3, 0xA9));
    D_80115C8A_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115C90_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115C8A_mstory3[0], 0, (char *)D_80115380_mstory3[D_80115C9C_mstory3]);
    data = DataRead(func_80017BB8_main(D_80115C9C_mstory3, 0xAA));
    D_80115C8A_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106CF0_mstory3(obj->model[1], D_80115C90_mstory3, D_80115C8A_mstory3[0]);
    omPrcSetDestructor(0, func_8010A7C8_mstory3);
    while (1) {
        D_80115BC0_mstory3[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A7C8_mstory3(void) {
}

/* actor 0: takes out the item and plays motions 3 and 4 */
void func_8010A7D0_mstory3(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], obj->model[1], (char *)D_801156C8_mstory3);
    func_8001C258_main(obj->model[3], 4, 0);
    func_8001C624_main(model, HmfModelData[obj->motion[3]].unk02, 0, 10, 0);
    func_80107244_mstory3(model);
    func_8001C624_main(model, HmfModelData[obj->motion[4]].unk02, 0, 10, 0);
    func_80107244_mstory3(model);
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[0].flags = 1;
}

/* actor 0: plays motion 4 then 3 at double speed and puts the item away */
void func_8010A8EC_mstory3(omObjData *obj) {
    f32 frame;
    s16 model = obj->model[1];

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
    D_80115BC0_mstory3[0].func = func_8010AB34_mstory3;
}

void func_8010AB34_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[1].obj);
}

void func_8010AB54_mstory3(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    D_80115BC0_mstory3[0].unk0C = 1;
    D_80115BC0_mstory3[0].unk10 = 0x1F;
    func_8010733C_mstory3(obj, 3.5f, 15);
    func_80106CF0_mstory3(obj->model[1], D_80115C90_mstory3, D_80115C8A_mstory3[2]);
    func_80106CF0_mstory3(D_80115BC0_mstory3[1].obj->model[1], D_80115C98_mstory3, D_80115C92_mstory3[2]);
    D_80115BC0_mstory3[0].unk0C = 0;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 10, 2);
    func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1], HmfModelData[D_80115BC0_mstory3[1].obj->motion[4]].unk02, 0, 10, 2);
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
}

/* actor 0: hops in place and turns to face the camera */
void func_8010ACBC_mstory3(omObjData *obj) {
    Vec rot;
    Vec pos;
    Vec tmp;

    rot = D_801156D4_mstory3;
    tmp.x = HmfModelData[obj->model[1]].pos.x - 5.0f;
    tmp.y = HmfModelData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    pos = tmp;
    func_80106CF0_mstory3(obj->model[1], D_80115C90_mstory3, D_80115C8A_mstory3[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, HmfModelData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[4], 4, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    func_80106DC4_mstory3(obj, &pos, 10);
    func_80107244_mstory3(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107070_mstory3(obj, &rot, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80106CF0_mstory3(obj->model[1], D_80115C90_mstory3, D_80115C8A_mstory3[0]);
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
}

/* actor 0: turns, waits for actor 1 and walks away */
void func_8010AF28_mstory3(omObjData *obj) {
    Vec rot;
    Vec pos;
    Vec tmp;

    rot = D_801156E0_mstory3;
    tmp.x = HmfModelData[obj->model[1]].pos.x;
    tmp.y = HmfModelData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    pos = tmp;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107070_mstory3(obj, &rot, 10);
    D_80115BC0_mstory3[2].func = func_8010C3F4_mstory3;
    func_8004AC98_main(D_80115C9C_mstory3 + 0x275, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[7]].unk02, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    D_80115BC0_mstory3[0].flags = 10;
    while (1) {
        if (D_80115BC0_mstory3[1].flags == 10) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115BC0_mstory3[0].unk0C = 1;
    D_80115BC0_mstory3[0].unk10 = 0x28;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_80106DC4_mstory3(obj, &pos, 60);
    D_80115BC0_mstory3[0].unk0C = 0;
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
}

/* NON_MATCHING: retail branches on i for the model file (bnez with the 0x300A0 load in the delay
   slot); KMC GCC turns every form tried into a negu/and/or select (masked 14, same count otherwise). */
#ifdef NON_MATCHING
/* actor 1: the partner, character 1 when the player is character 0, else character 0 */
void func_8010B154_mstory3(void) {
    s16 chrs[2] = { 0, 1 };
    s32 mots[2] = { 0x3B, 0x44 };
    omObjData *obj;
    void *data;
    s16 i;

    i = D_80115C9C_mstory3 == 0;
    obj = omAddObj(10, 20, 20, -1, NULL);
    D_80115BC0_mstory3[1].obj = obj;
    D_80115BC0_mstory3[1].flags = 0;
    D_80115BC0_mstory3[1].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[1].unk0C = 0;
    D_80115BC0_mstory3[1].unk10 = 0x1F;
    obj->model[1] = func_8000B108_main(i != 0 ? 0x300A0 : 0x200A0, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C9A_mstory3);
    obj->model[3] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chrs[i], 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chrs[i], 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chrs[i], 2));
    func_8000B460_main(obj, 3, func_80017BB8_main(chrs[i], 0x13));
    func_8000B460_main(obj, 4, func_80017BB8_main(chrs[i], 0x72));
    func_8000B460_main(obj, 5, mots[i] | 0x1D0000);
    func_8000B460_main(obj, 6, func_80017BB8_main(chrs[i], 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(chrs[i], 0x33));
    func_8000B460_main(obj, 8, func_80017BB8_main(chrs[i], 0x2F));
    if (D_80115C9C_mstory3 == 0) {
        func_8000B460_main(obj, 9, 0x1D0045);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_80115C44_mstory3 = D_80115554_mstory3;
    Hu3DModelPosSet(obj->model[1], D_80115C44_mstory3.x, D_80115C44_mstory3.y, D_80115C44_mstory3.z);
    Hu3DModelPosSet(obj->model[2], D_80115C44_mstory3.x, D_80115C44_mstory3.y - -5.0f, D_80115C44_mstory3.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, -14.48f, 0.0f);
    data = DataRead(func_80017BB8_main(chrs[i], 0xA4));
    D_80115C92_mstory3[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, (char *)D_801153A0_mstory3[i]);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115C92_mstory3[0], 1, 0);
    func_80032FF8_main(D_80115C92_mstory3[0], 0);
    D_80115C98_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115C92_mstory3[0], 0, (char *)D_801153A0_mstory3[i]);
    data = DataRead(func_80017BB8_main(chrs[i], 0xA9));
    D_80115C92_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115C98_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115C92_mstory3[0], 0, (char *)D_801153A0_mstory3[i]);
    data = DataRead(func_80017BB8_main(chrs[i], 0xAA));
    D_80115C92_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106CF0_mstory3(obj->model[1], D_80115C98_mstory3, D_80115C92_mstory3[0]);
    omPrcSetDestructor(0, func_8010B634_mstory3);
    while (1) {
        D_80115BC0_mstory3[1].func(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B154_mstory3);
#endif

void func_8010B634_mstory3(void) {
}

/* actor 1: a turn, then hands actor 0 its next step */
void func_8010B63C_mstory3(omObjData *obj) {
    D_80115BC0_mstory3[1].unk0C = 1;
    D_80115BC0_mstory3[1].unk10 = 0x1F;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_8010733C_mstory3(obj, 4.5f, 15);
    D_80115BC0_mstory3[1].unk0C = 0;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    D_80115BC0_mstory3[1].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[0].func = func_8010AB54_mstory3;
}

/* actor 1: hops in place and turns to face the camera */
void func_8010B72C_mstory3(omObjData *obj) {
    Vec rot;
    Vec pos;
    Vec tmp;

    rot = D_801156EC_mstory3;
    tmp.x = HmfModelData[obj->model[1]].pos.x + 5.0f;
    tmp.y = HmfModelData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    pos = tmp;
    func_80106CF0_mstory3(obj->model[1], D_80115C98_mstory3, D_80115C92_mstory3[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], HmfModelData[obj->model[1]].pos.x, HmfModelData[obj->model[1]].pos.y, HmfModelData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[6]].unk02, 0, 10, 0);
    func_80106DC4_mstory3(obj, &pos, 10);
    func_80107244_mstory3(obj->model[1]);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107070_mstory3(obj, &rot, 10);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 10, 2);
    func_80106CF0_mstory3(obj->model[1], D_80115C98_mstory3, D_80115C92_mstory3[0]);
    D_80115BC0_mstory3[1].func = func_80108A94_mstory3;
}

/* actor 1: turns, waits for actor 0 and walks away; ends with actor 0's step cleared */
void func_8010B998_mstory3(omObjData *obj) {
    Vec rot;
    Vec pos;
    Vec tmp;

    rot = D_801156E0_mstory3;
    tmp.x = HmfModelData[obj->model[1]].pos.x;
    tmp.y = HmfModelData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    pos = tmp;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[1]].unk02, 0, 10, 2);
    func_80107070_mstory3(obj, &rot, 10);
    func_8004AC98_main(D_80115C9E_mstory3 + 0x275, 1);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[7]].unk02, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    D_80115BC0_mstory3[1].flags = 10;
    while (1) {
        if (D_80115BC0_mstory3[0].flags == 10) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115BC0_mstory3[1].unk0C = 1;
    D_80115BC0_mstory3[1].unk10 = 0x28;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 10, 2);
    HuPrcSleep(10);
    func_80106DC4_mstory3(obj, &pos, 60);
    D_80115BC0_mstory3[1].unk0C = 0;
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
}

/* actor 1 plays motion 9 while the caller's model finishes its motion */
void func_8010BBB4_mstory3(omObjData *obj) {
    func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1], HmfModelData[D_80115BC0_mstory3[1].obj->motion[9]].unk02, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    D_80115BC0_mstory3[1].func = func_80108A94_mstory3;
}

/* actor 2: model file 0xA0075 (the model chapter 1 gives its actor 1) */
void func_8010BC34_mstory3(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(10, 20, 20, -1, NULL);
    D_80115BC0_mstory3[2].obj = obj;
    D_80115BC0_mstory3[2].flags = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C9A_mstory3);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_80115C50_mstory3 = D_80115560_mstory3;
    Hu3DModelPosSet(obj->model[1], D_80115C50_mstory3.x, D_80115C50_mstory3.y, D_80115C50_mstory3.z);
    Hu3DModelPosSet(obj->model[2], D_80115C50_mstory3.x, -5.0f, D_80115C50_mstory3.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    D_80115C80_mstory3[0] = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, (char *)D_801156F8_mstory3);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115C80_mstory3[0], 1, 0);
    func_80032FF8_main(D_80115C80_mstory3[0], 0);
    D_80115C86_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115C80_mstory3[0], 0, (char *)D_801156F8_mstory3);
    data = DataRead(0xA0083);
    D_80115C80_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115C86_mstory3 = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_80115C80_mstory3[0], 0, (char *)D_801156F8_mstory3);
    data = DataRead(0xA0080);
    D_80115C80_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106CF0_mstory3(obj->model[1], D_80115C86_mstory3, D_80115C80_mstory3[0]);
    omPrcSetDestructor(0, func_8010BF40_mstory3);
    D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
    while (1) {
        D_80115BC0_mstory3[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010BF40_mstory3(void) {
}

/* actor 2 bobs up and down, turns, and actor 1 reacts with motion 8 and a voice */
void func_8010BF48_mstory3(omObjData *obj) {
    Vec start;
    Vec rot;
    f32 y;
    s16 i;
    s16 model = obj->model[1];

    rot = D_80115704_mstory3;
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    i = 0;
    func_80106CF0_mstory3(model, D_80115C86_mstory3, D_80115C80_mstory3[1]);
    do {
        y = sindf(i * 12.000001f) * 80.0f;
        HmfModelData[model].pos.y = y + start.y;
        HuPrcVSleep();
        i++;
    } while (i < 13);
    HuPrcSleep(10);
    func_80107070_mstory3(obj, &rot, 5);
    func_80106CF0_mstory3(model, D_80115C86_mstory3, D_80115C80_mstory3[0]);
    func_8001C624_main(D_80115BC0_mstory3[1].obj->model[1], HmfModelData[D_80115BC0_mstory3[1].obj->motion[8]].unk02, 0, 10, 0);
    HuPrcSleep(D_80115C9C_mstory3 != 0 ? 30 : 35);
    func_8004AAD0_main(CharFXPlay(0x28F, D_80115C9F_mstory3), 0x60);
    D_80115BC0_mstory3[2].func = func_8010C15C_mstory3;
    D_80115BC0_mstory3[2].flags = 5;
}

void func_8010C15C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[1].obj);
}

/* actor 2 sinks to height 100 */
void func_8010C17C_mstory3(omObjData *obj) {
    while (1) {
        if (!(HmfModelData[obj->model[1]].pos.y > 100.0f)) {
            break;
        }
        HmfModelData[obj->model[1]].pos.y -= 2.0f;
        HuPrcVSleep();
    }
    HmfModelData[obj->model[1]].pos.y = 100.0f;
    D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
}

/* actor 2 bobs up and down and turns */
void func_8010C23C_mstory3(omObjData *obj) {
    Vec start;
    Vec rot;
    f32 y;
    s16 i;
    s16 model = obj->model[1];

    rot = D_80115710_mstory3;
    start.x = HmfModelData[model].pos.x;
    start.y = HmfModelData[model].pos.y;
    start.z = HmfModelData[model].pos.z;
    i = 0;
    func_80106CF0_mstory3(model, D_80115C86_mstory3, D_80115C80_mstory3[1]);
    func_8001C624_main(D_80115BC0_mstory3[2].obj->model[1], HmfModelData[D_80115BC0_mstory3[2].obj->motion[0]].unk02, 0, 10, 2);
    do {
        y = sindf(i * 12.000001f) * 80.0f;
        HmfModelData[model].pos.y = y + start.y;
        HuPrcVSleep();
        i++;
    } while (i < 15);
    HuPrcSleep(15);
    func_80107070_mstory3(obj, &rot, 10);
    D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[2].flags = 1;
}

/* actor 2 turns, then keeps facing actor 0 */
void func_8010C3F4_mstory3(omObjData *obj) {
    Vec rot;

    rot = D_8011571C_mstory3;
    func_80106CF0_mstory3(obj->model[1], D_80115C86_mstory3, D_80115C80_mstory3[0]);
    func_80107070_mstory3(obj, &rot, 10);
    while (1) {
        func_80107674_mstory3(D_80115BC0_mstory3[2].obj, D_80115BC0_mstory3[0].obj);
        HuPrcVSleep();
    }
}

void func_8010C490_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[0].obj);
}

/* actor 3: model file 0xA0122, at double size */
void func_8010C4B0_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(10, 20, 20, -1, NULL);
    D_80115BC0_mstory3[3].obj = obj;
    D_80115BC0_mstory3[3].flags = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C9A_mstory3);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_80115C5C_mstory3 = D_8011556C_mstory3;
    Hu3DModelPosSet(obj->model[1], D_80115C5C_mstory3.x, D_80115C5C_mstory3.y, D_80115C5C_mstory3.z);
    Hu3DModelPosSet(obj->model[2], D_80115C5C_mstory3.x, -5.0f, D_80115C5C_mstory3.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_8010C654_mstory3);
    D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
    while (1) {
        D_80115BC0_mstory3[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C654_mstory3(void) {
}

/* NON_MATCHING: masked 0 except one nop the assembler puts after sindf's jal (delay slot
   mov.s $f12) where retail has none; mstory1's func_8010FAF8 has the same residue. */
#ifdef NON_MATCHING
/* process: actor 3 floats up and down (paused while D_80115C88_mstory3 is 1) */
void func_8010C65C_mstory3(void) {
    Vec pos;
    omObjData *obj;
    f32 angle;
    f32 y;

    angle = 0.0f;
    obj = D_80115BC0_mstory3[3].obj;
    pos.y = HmfModelData[obj->model[1]].pos.y;
    while (1) {
        pos.x = HmfModelData[obj->model[1]].pos.x;
        pos.z = HmfModelData[obj->model[1]].pos.z;
        y = sindf(angle) * 25.0f + 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (D_80115C88_mstory3 != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, y + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C65C_mstory3);
#endif

void func_8010C7A0_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[1].obj);
}

/* actor 3 turns */
void func_8010C7C0_mstory3(omObjData *obj) {
    Vec rot;

    rot = D_801156E0_mstory3;
    func_80107070_mstory3(obj, &rot, 10);
    D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
}

/* actor 2 turns; clears actor 3's step */
void func_8010C810_mstory3(omObjData *obj) {
    Vec rot;

    rot = D_80115728_mstory3;
    func_80107070_mstory3(D_80115BC0_mstory3[2].obj, &rot, 10);
    D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
}

/* actor 4: model file 0x1D0007, with model[2] from func_8000CED8_main (chapter 1 calls it a shadow) */
void func_8010C870_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(10, 20, 20, -1, NULL);
    D_80115BC0_mstory3[4].obj = obj;
    D_80115BC0_mstory3[4].flags = 0;
    D_80115BC0_mstory3[4].func = func_80108A94_mstory3;
    obj->model[1] = func_8000B108_main(0x1D0007, 0x20299);
    obj->model[2] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    D_80115C68_mstory3 = D_80115578_mstory3;
    Hu3DModelPosSet(obj->model[1], D_80115C68_mstory3.x, D_80115C68_mstory3.y, D_80115C68_mstory3.z);
    func_8000CD00_main(obj->model[2], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[2], 60.0f);
    func_800138EC_main(obj->model[2], 1, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    omPrcSetDestructor(0, func_8010C9E0_mstory3);
    while (1) {
        D_80115BC0_mstory3[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C9E0_mstory3(void) {
}
