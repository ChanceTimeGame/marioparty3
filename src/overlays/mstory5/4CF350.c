#include "common.h"

#include "mallocblock.h"

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

extern s16 D_801151B0_mstory5; /* message window */
extern s16 D_801151B2_mstory5; /* background model */
extern s32 D_801151B4_mstory5; /* the controller that drives the story messages */
extern s16 D_801151B8_mstory5; /* background sprite */
extern s32 D_801151E4_mstory5;

void func_80106028_mstory5(void);
void func_80106B64_mstory5(omObjData *obj, const Vec *to, s32 frames, s32 turn);
void func_80106DB4_mstory5(omObjData *obj, const Vec *to, s32 frames, s32 turn);
s32 func_801072A0_mstory5(s16 model);
void func_80105BDC_mstory5(omObjData *obj);
void func_80105CCC_mstory5(omObjData *obj);
void func_80105E34_mstory5(void);
void func_80105F5C_mstory5(omObjData *obj);
void func_8010842C_mstory5(void);
void func_801100AC_mstory5(void);
extern s16 D_801151B6_mstory5; /* low half of D_801151B4_mstory5 */
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
void func_801074E8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 time, s32 arg5);
void HuMemMemoryFreePerm(void *ptr);

u32 D_80114730_mstory5 = 0; /* main object state */
s32 D_80114734_mstory5 = 0;
s8 D_80114738_mstory5 = 0;
Vec D_8011473C_mstory5 = { 14.0f, 193.0f, 1400.0f }; /* camera position */
Vec D_80114748_mstory5 = { -25.0f, 0.0f, -650.0f }; /* camera target */
Vec D_80114754_mstory5 = { 0.0f, 1.0f, -0.0001f }; /* camera up */
s32 D_80114760_mstory5 = 0;

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

// decomp-permuter
void func_80105BDC_mstory5(omObjData *obj)
{
  u32 state = D_80114730_mstory5;
  u16 new_var;
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
      if (D_80114734_mstory5 == 1)
    {
      state += ((new_var = D_800D5558_main[D_801151B4_mstory5]) & 0x1000) > 0;
    }
      break;

    case 3:
      WipeCreateOut(2, 0x14);
      HuAudSeqFadeOut(0x1E);
      state++;
      break;

    case 4:
      if (WipeStatGet() == 0)
    {
      func_8005F524_main();
      func_80050064_main(1);
      omOvlReturnEx(1);
    }
      break;

  }

  D_80114730_mstory5 = state;
}

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

void func_80106B48_mstory5(omObjData *obj, const Vec *to, s32 frames) {
    func_80106B64_mstory5(obj, to, frames, 1);
}

/* walks obj's model (and its shadow, kept on the ground) to `to` in `frames` frames, turning
   it to face the way first when `turn` is set */
void func_80106B64_mstory5(omObjData *obj, const Vec *to, s32 frames, s32 turn) {
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

void func_80106D98_mstory5(omObjData *obj, const Vec *to, s32 frames) {
    func_80106DB4_mstory5(obj, to, frames, 1);
}

/* as func_80106B64_mstory5, but the second model follows in 3D */
void func_80106DB4_mstory5(omObjData *obj, const Vec *to, s32 frames, s32 turn) {
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

void func_80107080_mstory5(omObjData *obj, const Vec *to, s32 frames) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148C4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148E0_mstory5);
