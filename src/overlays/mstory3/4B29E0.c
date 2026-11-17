#include "common.h"

//@@hdr
// story u1
#include "mallocblock.h"

/* a story-scene actor: its object and the action its process runs every frame (mstory1's, 4 bytes shorter) */
typedef struct StoryActor3 {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk08;
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
extern s16 D_80115B98_mstory3[8]; /* [0] the map, [1 + i] stamp i */
extern s16 D_80115BA8_mstory3[8]; /* the sparkles around the new stamp */
extern s16 D_80115BB8_mstory3; /* the white flash */
extern s32 D_80115BBC_mstory3; /* the stamp this scene wins */
extern s32 D_80115510_mstory3[7]; /* stamp sprite files */
extern s16 D_8011552C_mstory3[7][2]; /* stamp positions (x, y), less 0x30 */
extern VecQuad D_80115590_mstory3; /* the two turns of func_80108CA8_mstory3 */
extern StoryActor3 D_80115BC0_mstory3[6];
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
s32 func_80107290_mstory3(s16 model);
void func_801077BC_mstory3(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_80108CA8_mstory3(omObjData *obj);
void func_80108E28_mstory3(omObjData *obj);
void func_8010D5CC_mstory3(void);
void func_8010895C_mstory3(void);
void func_80108A9C_mstory3(void);
void func_80108C34_mstory3(void);
void func_8010A23C_mstory3(void);
void func_8010B154_mstory3(void);
void func_8010BC34_mstory3(void);
void func_8010C4B0_mstory3(void);
void func_8010C65C_mstory3(void);
void func_8010C870_mstory3(void);
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

//@@func_801059E4_mstory3
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
//@@end

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

//@@func_8010603C_mstory3
void func_8010603C_mstory3(void) {
    func_8005D294_main(D_80115B92_mstory3);
    func_80060C14_main(D_80115B92_mstory3, 1);
}
//@@end

//@@func_8010606C_mstory3
void func_8010606C_mstory3(void) {
    func_80060EA8_main(D_80115B92_mstory3, 1);
}
//@@end

//@@func_80106090_mstory3
void func_80106090_mstory3(s32 mess) {
    func_8005B43C_main(D_80115B92_mstory3, mess, -1, -1);
    while (func_8005E0C0_main(D_80115B92_mstory3) != 0) {
        HuPrcVSleep();
    }
}
//@@end

//@@func_801060E4_mstory3
void func_801060E4_mstory3(s32 mess) {
    func_8005B43C_main(D_80115B92_mstory3, mess, -1, -1);
    func_8005B6BC_main(D_80115B92_mstory3, GwStory.unk1 + 0x1C00, 0);
    while (func_8005E0C0_main(D_80115B92_mstory3) != 0) {
        HuPrcVSleep();
    }
}
//@@end

//@@func_80106154_mstory3
s16 func_80106154_mstory3(void) {
    return func_8005E1D8_main(D_80115B92_mstory3, 0, 1);
}
//@@end

//@@func_80106184_mstory3
void func_80106184_mstory3(void) {
    func_8000BB54_main(D_80115B94_mstory3);
}
//@@end

//@@func_801061A4_mstory3
void func_801061A4_mstory3(void) {
    func_8000BB94_main(D_80115B94_mstory3);
}
//@@end

//@@func_801061C4_mstory3
void func_801061C4_mstory3(void) {
    func_8001C814_main(D_80115B96_mstory3, 4, 0);
    func_8001C814_main(D_80115B96_mstory3, 1, 0);
    func_8001C6A8_main(D_80115B96_mstory3, 0.0f);
    func_8001C92C_main(D_80115B96_mstory3, 2.0f);
}
//@@end

//@@func_80106220_mstory3
void func_80106220_mstory3(void) {
    func_8001C814_main(D_80115B96_mstory3, 4, 4);
    func_8001C814_main(D_80115B96_mstory3, 1, 0);
    func_8001C6A8_main(D_80115B96_mstory3, HmfModelData[D_80115B96_mstory3].unk40);
}
//@@end

//@@func_80106284_mstory3
void func_80106284_mstory3(void) {
    s16 i = 0;

    HmfModelData[D_80115B96_mstory3].rot.y += -10.6f;
    do {
        HmfModelData[D_80115B96_mstory3].rot.x += 17.84f;
        HuPrcVSleep();
        i++;
    } while (i < 5);
}
//@@end

//@@func_80106340_mstory3
void func_80106340_mstory3(void) {
    D_80115B94_mstory3 = InitEspriteSlot(func_8000B838_main(0x1D0012), 0, 0);
    func_8000BBD4_main(D_80115B94_mstory3, 0xA0, 0x78);
    func_8000BC48_main(D_80115B94_mstory3, 0x4000);
    D_80115B96_mstory3 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_80115B96_mstory3, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_80115B96_mstory3, 2, 0);
    func_8001C814_main(D_80115B96_mstory3, 1, 1);
}
//@@end

//@@func_80106400_mstory3
void func_80106400_mstory3(s32 arg0) {
    D_80115BBC_mstory3 = arg0;
    D_80115288_mstory3 = 0;
    omAddPrcObj(func_8010643C_mstory3, 0x1000, 0x800, 0);
}
//@@end

//@@func_8010643C_mstory3
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
//@@end

//@@func_80106CDC_mstory3
s32 func_80106CDC_mstory3(void) {
    return D_80115288_mstory3;
}
//@@end

void func_80106CE8_mstory3(void) {
}

//@@func_80106CF0_mstory3
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
//@@end

//@@func_80106DC4_mstory3
void func_80106DC4_mstory3(omObjData *obj, Vec *to, s32 frames) {
    func_80106DE0_mstory3(obj, to, frames, 1);
}
//@@end

//@@func_80106DE0_mstory3
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
//@@end

//@@func_80107014_mstory3
void func_80107014_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106DC4_mstory3(obj, &to, frames);
}
//@@end

//@@func_80107040_mstory3
void func_80107040_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 turn) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80106DE0_mstory3(obj, &to, frames, turn);
}
//@@end

//@@func_80107070_mstory3
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
//@@end

//@@func_80107218_mstory3
void func_80107218_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_80107070_mstory3(obj, &to, frames);
}
//@@end

//@@func_80107244_mstory3
void func_80107244_mstory3(s16 model) {
    HuPrcSleep(10);
    while (func_80107290_mstory3(model) == 0) {
        HuPrcVSleep();
    }
}
//@@end

//@@func_80107290_mstory3
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
//@@end

//@@func_8010733C_mstory3
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
//@@end

//@@func_801074D8_mstory3
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
//@@end

//@@func_80107674_mstory3
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
//@@end

//@@func_801077BC_mstory3
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
//@@end

//@@func_80107A18_mstory3
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
//@@end

//@@func_80107D80_mstory3
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
//@@end

//@@func_80108084_mstory3
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
//@@end

//@@func_8010892C_mstory3
void func_8010892C_mstory3(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}
//@@end

//@@func_8010895C_mstory3
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
//@@end

void func_80108A94_mstory3(void) {
}

//@@func_80108A9C_mstory3
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
//@@end

//@@func_80108C34_mstory3
/* actor 5's process: runs its action every frame */
void func_80108C34_mstory3(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_80115BC0_mstory3[5].obj = obj;
    D_80115BC0_mstory3[5].unk08 = 0;
    D_80115BC0_mstory3[5].func = func_80108CA8_mstory3;
    while (1) {
        D_80115BC0_mstory3[5].func(obj);
        HuPrcVSleep();
    }
}
//@@end

//@@func_80108CA8_mstory3
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
//@@end

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
