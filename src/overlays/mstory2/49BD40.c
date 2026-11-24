#include "mstory2.h"


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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE1C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE24_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE2C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE48_mstory2);

Vec D_8011B920_mstory2 = { 14.0f, 193.0f, 1400.0f };
Vec D_8011B92C_mstory2 = { -25.0f, 0.0f, -650.0f };
Vec D_8011B938_mstory2 = { 0.0f, 1.0f, -0.0001f };
s16 D_8011B944_mstory2 = 0;
s16 D_8011B946_mstory2 = 0;
s16 D_8011B948_mstory2 = 0;
s32 D_8011B94C_mstory2 = 0;
