#include "common.h"

// story v1
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
void MBDBackKill(void);
void MBDBackClose(void);

extern u32 D_80111AC0_mstory4; /* main object state */
extern s32 D_80111AC4_mstory4; /* 1: a board background is open and is closed on exit */
extern s32 D_80111AC8_mstory4; /* 1: the scene was seen before, A skips it */
extern s8 D_80111ACC_mstory4;
extern Vec D_80111AD0_mstory4; /* camera position */
extern Vec D_80111ADC_mstory4; /* camera target */
extern Vec D_80111AE8_mstory4; /* camera up */
extern s32 D_80111AF4_mstory4; /* the story map has finished */
extern s16 D_80112120_mstory4; /* message window */
extern s16 D_80112122_mstory4; /* background model */
extern s32 D_80112124_mstory4; /* the controller that drives the story messages */
extern s16 D_80112126_mstory4; /* low half of D_80112124_mstory4 */
extern s16 D_80112128_mstory4; /* background sprite */
extern s32 D_801121B4_mstory4;
extern s32 D_801123B0_mstory4[4]; /* play order: player per slot */

extern void (*const D_80111C10_mstory4[2])(void);
extern const s32 D_80111C18_mstory4[2];

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
void func_8010B9FC_mstory4(void);
void func_80106C10_mstory4(void);
void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80106C78_mstory4(void);
void func_80106CA8_mstory4(void);
void func_80106CCC_mstory4(s32 mess);
void *func_8001D33C_main(s16, const char *);
void func_801060E8_mstory4(void);
void func_801060F8_mstory4(s32 arg0);
s32 func_80106B20_mstory4(void);
void func_8000BBFC_main(u16 spriteId, s16 alpha);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_8000BEAC_main(u16 spriteId, s32 r, s32 g, s32 b);
void func_8000BD94_main(u16, s32, s32);
void func_8000BDDC_main(u16, s32);
void func_80106000_mstory4(void);
void func_80106034_mstory4(void);
void func_80106B2C_mstory4(void);
extern s16 D_80112130_mstory4[8]; /* [0] the map sprite, [1 + i] chapter i's mark */
extern s16 D_80112140_mstory4[7][8]; /* the sparkles around each chapter mark */
extern s16 D_801121B0_mstory4; /* flash sprite */
extern const s32 D_80111C34_mstory4[7];
extern const s16 D_80111C50_mstory4[8][2];

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

// decomp-permuter
void func_80105C90_mstory4(omObjData *obj)
{
  u32 state = D_80111AC0_mstory4;
  int new_var;
  switch (state)
  {
    case 0:
      HuAudSeqPlay(0x26);
      state++;
      break;

    case 1:
      state += WipeStatGet() == 0;
      break;

    case 2:
      if (D_80111AC8_mstory4 == 1)
    {
      new_var = D_800D5558_main[D_80112124_mstory4] & 0x1000;
      state += new_var != 0;
    }
      break;

    case 3:
      if (GwPlayer[0].coin == 0)
    {
      WipeCreateOut(2, 0x14);
    }
    else
    {
      WipeCreateOut(0xB, 0x14);
    }
      state++;
      break;

    case 4:
      if (WipeStatGet() == 0)
    {
      if (D_80111AC4_mstory4 == 1)
      {
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

/* the chapter marks on the story map and where they sit; the last entry is padding */
const s32 D_80111C34_mstory4[7] = { 0x1D000B, 0x1D000C, 0x1D000D, 0x1D000E, 0x1D000F, 0x1D0010, 0x1D0011 };
const s16 D_80111C50_mstory4[8][2] = {
    { 0x39, 0x14 }, { 0x81, 0x24 }, { 0xC8, 0x16 }, { 0xD7, 0x5B },
    { 0x96, 0x7C }, { 0x51, 0x69 }, { 0x0C, 0x7A }, { 0, 0 },
};

#ifdef NON_MATCHING
// opcode-identical except: retail's cosdf/sindf delay slots were filled by the assembler (no nop after them; KMC GCC fills them itself, and as adds a nop), the sparkle loop's i/j registers swap, and one addu is scheduled differently
/* the story map: the chapters cleared so far appear, the new one (D_801121B4_mstory4)
   fades in and sparkles; chapter 6 flashes twice. Sets D_80111AF4_mstory4 when done. */
void func_80106134_mstory4(void) {
    void *data;
    s16 *sprite;
    f32 x;
    f32 y;
    f32 alpha;
    f32 angle;
    s32 j;
    s32 i;

    D_80112130_mstory4[0] = InitEspriteSlot(func_8000B838_main(0x1D0001), 0, 0);
    func_8000BBD4_main(D_80112130_mstory4[0], 0xA0, 0x78);
    func_8000BB94_main(D_80112130_mstory4[0]);
    for (i = 0; i < 7; i++) {
        D_80112130_mstory4[1 + i] = InitEspriteSlot(func_8000B838_main(D_80111C34_mstory4[i]), 0, 0);
        func_8000BBD4_main(D_80112130_mstory4[1 + i], D_80111C50_mstory4[i][0] + 0x30, D_80111C50_mstory4[i][1] + 0x30);
        func_8000BC48_main(D_80112130_mstory4[1 + i], 8);
        func_8000BB94_main(D_80112130_mstory4[1 + i]);
    }
    data = DataRead(0x1D0002);
    i = 0;
    j = 0;
    do {
        do {
            D_80112140_mstory4[i][j] = InitEspriteSlot(func_80055810_main(data), 0, 1);
            x = D_80111C50_mstory4[i][0] + 0x30;
            y = D_80111C50_mstory4[i][1] + 0x30;
            angle = j * 45.0f;
            x += cosdf(angle) * 32.0f;
            y -= sindf(angle) * 32.0f;
            func_8000BBD4_main(D_80112140_mstory4[i][j], x, y);
            func_8000BC48_main(D_80112140_mstory4[i][j], 0x1000);
            func_8000BEAC_main(D_80112140_mstory4[i][j], 0xFF, 0xFF, 0xC0);
            func_8000BC48_main(D_80112140_mstory4[i][j], 8);
            func_8000BE5C_main(D_80112140_mstory4[i][j], 1.5f, 1.5f);
            func_8000BBFC_main(D_80112140_mstory4[i][j], 0xFF);
            func_8000BB94_main(D_80112140_mstory4[i][j]);
            j++;
        } while (j < 8);
        i++;
        j = 0;
    } while (i < 7);
    HuMemMemoryFreePerm(data);
    D_801121B0_mstory4 = InitEspriteSlot(func_8000B838_main(0x1D0000), 0, 0);
    func_8000BBD4_main(D_801121B0_mstory4, 0xA0, 0x78);
    func_8000BE5C_main(D_801121B0_mstory4, 40.0f, 30.0f);
    func_8000BC48_main(D_801121B0_mstory4, 0);
    func_8000BB94_main(D_801121B0_mstory4);
    omPrcSetDestructor(0, func_80106B2C_mstory4);
    func_8000BB54_main(D_801121B0_mstory4);
    func_8000BBFC_main(D_801121B0_mstory4, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801121B0_mstory4, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_801121B0_mstory4, 0x100);
    for (i = 0; i < D_801121B4_mstory4; i++) {
        func_8000BB54_main(D_80112130_mstory4[1 + i]);
    }
    func_80106000_mstory4();
    func_8000BB54_main(D_80112130_mstory4[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801121B0_mstory4, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_801121B0_mstory4);
    func_8000BBFC_main(D_80112130_mstory4[1 + D_801121B4_mstory4], 0);
    func_8000BB54_main(D_80112130_mstory4[1 + D_801121B4_mstory4]);
    for (alpha = 0.0f, i = 0; i < 20; i++) {
        alpha += 12.75f;
        func_8000BBFC_main(D_80112130_mstory4[1 + D_801121B4_mstory4], alpha);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_80112130_mstory4[1 + D_801121B4_mstory4], 0xFF);
    func_8000BE5C_main(D_80112130_mstory4[1 + D_801121B4_mstory4], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (j = 0; j < 8; j++) {
        func_8000BD94_main(D_80112140_mstory4[D_801121B4_mstory4][j], 0, 0);
        func_8000BDDC_main(D_80112140_mstory4[D_801121B4_mstory4][j], 1);
        func_8000BB54_main(D_80112140_mstory4[D_801121B4_mstory4][j]);
    }
    HuPrcSleep(20);
    for (j = 0; j < 8; j++) {
        func_8000BB94_main(D_80112140_mstory4[D_801121B4_mstory4][j]);
    }
    HuPrcSleep(30);
    HuAudFXPlay(0x131);
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 8; j++) {
            sprite = &D_80112140_mstory4[i][j];
            func_8000BD94_main(*sprite, 0, 0);
            func_8000BDDC_main(*sprite, 1);
            func_8000BB54_main(*sprite);
        }
    }
    HuPrcSleep(20);
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 8; j++) {
            func_8000BB94_main(D_80112140_mstory4[i][j]);
        }
    }
    if (D_801121B4_mstory4 != 6) {
        HuPrcSleep(60);
    } else {
        HuPrcSleep(40);
        HuAudFXPlay(0x221);
        for (i = 0; i < 2; i++) {
            func_8000BB54_main(D_801121B0_mstory4);
            func_8000BBFC_main(D_801121B0_mstory4, 0);
            for (j = 0; j < 7; j++) {
                func_8000BBFC_main(D_801121B0_mstory4, j * 0.14285715f * 255.0f);
                HuPrcVSleep();
            }
            func_8000BBFC_main(D_801121B0_mstory4, 0x100);
            HuPrcSleep(3);
            for (j = 0; j < 7; j++) {
                func_8000BBFC_main(D_801121B0_mstory4, 255.0f - j * 0.14285715f * 255.0f);
                HuPrcVSleep();
            }
            func_8000BB94_main(D_801121B0_mstory4);
            HuPrcSleep(5);
        }
    }
    func_8000BB54_main(D_801121B0_mstory4);
    func_8000BBFC_main(D_801121B0_mstory4, 0);
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801121B0_mstory4, i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BBFC_main(D_801121B0_mstory4, 0x100);
    func_8000BB94_main(D_80112130_mstory4[1 + D_801121B4_mstory4]);
    func_8000BB94_main(D_80112130_mstory4[0]);
    func_80106034_mstory4();
    HuPrcSleep(30);
    for (i = 0; i < D_801121B4_mstory4; i++) {
        func_8000BB94_main(D_80112130_mstory4[1 + i]);
    }
    for (i = 0; i < 20; i++) {
        func_8000BBFC_main(D_801121B0_mstory4, 255.0f - i * 0.05f * 255.0f);
        HuPrcVSleep();
    }
    func_8000BB94_main(D_801121B0_mstory4);
    D_80111AF4_mstory4 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80106134_mstory4);
#endif

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
    t = frames;
    step.x = delta.x / t;
    step.y = delta.y / t;
    step.z = delta.z / t;
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

void func_80106FF0_mstory4(omObjData *obj, Vec *to, s32 frames) {
    func_8010700C_mstory4(obj, to, frames, 1);
}

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
    t = frames;
    step.x = delta.x / t;
    step.y = delta.y / t;
    step.z = delta.z / t;
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

/* .data */
u32 D_80111AC0_mstory4 = 0; /* main object state */
s32 D_80111AC4_mstory4 = 0;
s32 D_80111AC8_mstory4 = 0;
s8 D_80111ACC_mstory4 = 0;
Vec D_80111AD0_mstory4 = { 14.0f, 193.0f, 1400.0f }; /* camera position */
Vec D_80111ADC_mstory4 = { -25.0f, 0.0f, -650.0f }; /* camera target */
Vec D_80111AE8_mstory4 = { 0.0f, 1.0f, -0.0001f }; /* camera up */
s32 D_80111AF4_mstory4 = 0;
