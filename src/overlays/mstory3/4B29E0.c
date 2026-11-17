#include "common.h"

//@@hdr
// story u1
/* a story-scene actor: its object and the action its process runs every frame (mstory1's, 4 bytes shorter) */
typedef struct StoryActor3 {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
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

typedef struct S16Quad {
    s16 v[4];
} S16Quad;

extern TexAnimSlot *D_800D1714_main;
extern f32 D_800CE17C_main[];
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, s32);
s32 func_80050064_main(s32 write);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);

extern Vec D_80115260_mstory3; /* camera position */
extern Vec D_8011526C_mstory3; /* camera target */
extern Vec D_80115278_mstory3; /* camera up */
extern s16 D_80115284_mstory3; /* 1: the scene was seen before, A skips it */
extern s16 D_80115286_mstory3; /* main object state */
extern s32 D_80115288_mstory3;
extern void (*D_801154F0_mstory3[2])(void); /* the scene for each story step (GwPlayer[0].coin) */
extern s32 D_801154F8_mstory3[2]; /* and the flag set once it has been seen */
extern S16Quad D_80115500_mstory3;
extern S16Quad D_80115508_mstory3; /* message window controller masks */
extern s16 D_80115B90_mstory3; /* the controller that drives the story messages */
extern s16 D_80115B92_mstory3; /* message window */
extern s16 D_80115B94_mstory3; /* background sprite */
extern s16 D_80115B96_mstory3; /* background model */
extern s32 D_80115BBC_mstory3;
extern StoryActor3 D_80115BC0_mstory3[6];
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
void func_8010643C_mstory3(void);
void func_80106DE0_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80106DC4_mstory3(omObjData *obj, Vec *to, s32 frames);
void func_80107070_mstory3(omObjData *obj, Vec *to, s32 frames);
s32 func_80107290_mstory3(s16 model);
void func_801077BC_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80108CA8_mstory3(omObjData *obj);
void func_80108E28_mstory3(omObjData *obj);
void func_8010D5CC_mstory3(void);
void func_8010895C_mstory3(void);
// story u1 end
//@@end

//@@func_801059A0_mstory3
void func_801059A0_mstory3(void) {
    func_80105C1C_mstory3();
}
//@@end

//@@func_801059BC_mstory3
void func_801059BC_mstory3(void) {
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
}
//@@end

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801059E4_mstory3);

//@@func_80105A64_mstory3
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
//@@end

//@@func_80105B44_mstory3
void func_80105B44_mstory3(void) {
    func_8005A6B0_main();
}
//@@end

//@@func_80105B60_mstory3
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
//@@end

//@@func_80105C1C_mstory3
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
//@@end

//@@func_80105D98_mstory3
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
//@@end

//@@func_80105E8C_mstory3
void func_80105E8C_mstory3(void) {
    D_80115286_mstory3 = 3;
}
//@@end

//@@func_80105E9C_mstory3
void func_80105E9C_mstory3(omObjData *obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        func_8005F524_main();
        func_80050064_main(1);
        omOvlReturnEx(1);
    }
}
//@@end

//@@func_80105EE4_mstory3
void func_80105EE4_mstory3(omObjData *obj) {
    WipeCreateOut(2, 0x14);
    HuAudSeqFadeOut(0x1E);
    func_8004AB0C_main(0x1E);
    obj->func = func_80105E9C_mstory3;
}
//@@end

//@@func_80105F2C_mstory3
void func_80105F2C_mstory3(omObjData *obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80105EE4_mstory3;
    }
}
//@@end

//@@func_80105F54_mstory3
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
//@@end

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010603C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010606C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106090_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801060E4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106154_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106184_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801061A4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801061C4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106220_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106284_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106340_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106400_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010643C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106CDC_mstory3);

void func_80106CE8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106CF0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106DC4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106DE0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107014_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107040_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107070_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107218_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107244_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107290_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010733C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801074D8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107674_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801077BC_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107A18_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107D80_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108084_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010892C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010895C_mstory3);

void func_80108A94_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108A9C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108C34_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108CA8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108E28_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A23C_mstory3);

void func_8010A7C8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A7D0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A8EC_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010AB34_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010AB54_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010ACBC_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010AF28_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B154_mstory3);

void func_8010B634_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B63C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B72C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B998_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010BBB4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010BC34_mstory3);

void func_8010BF40_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010BF48_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C15C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C17C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C23C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C3F4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C490_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C4B0_mstory3);

void func_8010C654_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C65C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C7A0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C7C0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C810_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C870_mstory3);

void func_8010C9E0_mstory3(void) {
}
