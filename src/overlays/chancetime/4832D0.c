#include "common.h"

// event e2
/* Chance Time unit 4832D0: the two Chance Time hosts, the spinning blocks and the swap. */

/* Sprite-model slot (D_800CBB60_main entry; src/14EA0.c unk_800ECDE0). */
typedef struct ChanceSprModel {
    /* 0x00 */ s16 model;
    /* 0x02 */ char unk_02[0x22];
} ChanceSprModel; // sizeof 0x24

/* Texture-animation slot (D_800D1714_main entry; src/14EA0.c TexAnimSlot). */
typedef struct TexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} TexAnimSlot; // sizeof 0xC

typedef f32 ChanceMtx[4][4];

void func_8001EF6C_main(s16 arg0, s16 arg1, char *arg2);
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
void func_80014714_main(s16 index, u16 arg1);
void func_80016B00_main(s16 arg0, s16 arg1, char *arg2, ChanceMtx *arg3);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);

void func_80107A80_chancetime(omObjData *obj);
void func_80107A88_chancetime(omObjData *obj);
void func_80107A90_chancetime(void);
void func_80107A98_chancetime(omObjData *obj);
void func_80107B18_chancetime(omObjData *obj);
void func_80107C84_chancetime(omObjData *obj);
void func_80107D60_chancetime(omObjData *obj);
void func_80107E40_chancetime(omObjData *obj);
void func_80107F58_chancetime(omObjData *obj);
void func_801080EC_chancetime(omObjData *obj);
void func_8010827C_chancetime(omObjData *obj);
void func_80108414_chancetime(omObjData *obj);
void func_80108578_chancetime(omObjData *obj);
void func_80108738_chancetime(omObjData *obj);
void func_80108C08_chancetime(s16 arg0, s16 arg1, s16 arg2);
void func_80106B18_chancetime(void);

extern ChanceSprModel *D_800CBB60_main;
extern TexAnimSlot *D_800D1714_main;
extern char D_8010FC80_chancetime[]; // "c160n_0_DEF"
extern char D_8010FC8C_chancetime[]; // "item_hook"

extern s32 D_8010FB00_chancetime;
extern s32 D_8010FB04_chancetime;
extern s32 D_8010FB08_chancetime;
extern f32 D_8010FB64_chancetime;
extern s32 D_8010FB68_chancetime;
extern f32 D_8010FB6C_chancetime;
extern f32 D_8010FB70_chancetime;
extern f32 D_8010FB74_chancetime;
extern f32 D_8010FB78_chancetime;
extern f32 D_8010FB7C_chancetime;
extern s16 D_8010FE80_chancetime[2];
extern s32 D_8010FE84_chancetime[2];
extern s32 D_8010FE8C_chancetime;
/* The host object and its current state (D_801100D8 is .func). */
typedef struct ChanceHost {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} ChanceHost;

extern ChanceHost D_801100D4_chancetime;

void func_80107300_chancetime(void) {
    omObjData *obj;
    void *data;
    s32 anim;
    s32 spr;
    s8 i;

    obj = omAddObj(0x14, 10, 16, -1, NULL);
    D_801100D4_chancetime.obj = obj;
    obj->model[1] = func_8000B108_main(0xA0000, 0x2A9);
    Hu3DModelPosSet(obj->model[1], -200.0f, 0.0f, -50.0f);
    func_8001C8A8_main(obj->model[1], 2);
    obj->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], -200.0f, -5.0f, -50.0f);
    func_8001C8A8_main(obj->model[2], 2);
    data = DataRead(0xA002A);
    D_8010FE84_chancetime[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_8010FC80_chancetime);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8010FE84_chancetime[0], 1, 0);
    func_80032FF8_main((s16)D_8010FE84_chancetime[0], 0);
    D_8010FE8C_chancetime = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_8010FE84_chancetime[0], 0, D_8010FC80_chancetime);
    data = DataRead(0xA002B);
    D_8010FE84_chancetime[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    obj->model[3] = func_8000B108_main(0xA0000, 0x2A9);
    Hu3DModelPosSet(obj->model[3], 200.0f, 0.0f, -50.0f);
    func_8001C8A8_main(obj->model[3], 2);
    data = DataRead(0xA002A);
    anim = (s16)HmfAnimCreate(HmfModelData[obj->model[3]].hmf, data, 0, D_8010FC80_chancetime);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[3]);
    func_8001C514_main(obj->model[3]);
    func_80032FC0_main(anim, 1, 0);
    func_80032FF8_main(anim, 0);
    obj->model[4] = Hu3DModelLink(obj->model[2]);
    Hu3DModelPosSet(obj->model[4], 200.0f, -5.0f, -50.0f);
    func_8001C8A8_main(obj->model[4], 2);
    obj->model[5] = func_8000B108_main(0x1C0008, 0x2B9);
    func_8001C8A8_main(obj->model[5], 2);
    func_8001C258_main(obj->model[5], 0x4000, 0x4000);
    func_8001C814_main(obj->model[5], 2, 2);
    func_8001C258_main(obj->model[5], 4, 4);
    func_8001C814_main(obj->model[5], 1, 1);
    obj->model[6] = func_8000B108_main(0x1C0008, 0x2B9);
    func_8001C8A8_main(obj->model[6], 2);
    func_8001C258_main(obj->model[6], 0x4000, 0x4000);
    func_8001C814_main(obj->model[6], 2, 2);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8001C814_main(obj->model[6], 1, 1);
    for (i = 0; i < 2; i++) {
        data = DataRead(0xB);
        spr = HmfSprModelCreate(data, 0x6BD, 8);
        HuMemMemoryFreePerm(data);
        func_8001C258_main(D_800CBB60_main[(u16)spr].model, 4, 4);
        Hu3DModelPosSet(D_800CBB60_main[(u16)spr].model, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(D_800CBB60_main[(u16)spr].model, 3.0f, 3.0f, 3.0f);
        func_8001C814_main(D_800CBB60_main[(u16)spr].model, 2, 0);
        func_8001C2FC_main(D_800CBB60_main[(u16)spr].model, 0x70000000, 0x70000000);
        func_8001C8A8_main(D_800CBB60_main[(u16)spr].model, 2);
        obj->model[i + 7] = D_800CBB60_main[(u16)spr].model;
        D_8010FE80_chancetime[i] = spr;
    }
    func_8000B460_main(obj, 0, 0xA0001);
    func_8000B460_main(obj, 1, 0xA0006);
    func_8000B460_main(obj, 2, 0xA000F);
    func_8000B460_main(obj, 3, 0xA0010);
    func_8000B460_main(obj, 4, 0xA0011);
    func_8000B460_main(obj, 5, 0xA000C);
    func_8000B460_main(obj, 6, 0xA000D);
    func_8000B460_main(obj, 7, 0xA000E);
    func_8000B460_main(obj, 8, 0xA001C);
    func_8000B460_main(obj, 9, 0xA001D);
    func_8000B460_main(obj, 10, 0xA001E);
    func_8000B460_main(obj, 11, 0xA0016);
    func_8000B460_main(obj, 12, 0xA0018);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C5B4_main(obj->model[3], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 0);
    func_8001C814_main(obj->model[3], 2, 0);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[3], 0.0f, 0.0f, 0.0f);
    omPrcSetDestructor(0, func_80107A90_chancetime);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 30, 2);
    func_8001C624_main(obj->model[3], HmfModelData[obj->motion[5]].unk02, 0, 30, 2);
    D_801100D4_chancetime.func = func_80107A88_chancetime;
    while (TRUE) {
        D_801100D4_chancetime.func(obj);
        HuPrcVSleep();
    }
}

void func_80107A80_chancetime(omObjData *obj) {
}

void func_80107A88_chancetime(omObjData *obj) {
}

void func_80107A90_chancetime(void) {
}

void func_80107A98_chancetime(omObjData *obj) {
    func_8001C5B4_main(obj->model[1], obj->motion[2]);
    func_8001C814_main(obj->model[1], 2, 0);
    func_8001C5B4_main(obj->model[3], obj->motion[2]);
    func_8001C814_main(obj->model[3], 2, 0);
    D_801100D4_chancetime.func = func_80107B18_chancetime;
}

void func_80107B18_chancetime(omObjData *obj) {
    D_8010FB64_chancetime += 8.0f;
    Hu3DModelRotSet(obj->model[1], 0.0f, D_8010FB64_chancetime, 0.0f);
    Hu3DModelRotSet(obj->model[3], 0.0f, -D_8010FB64_chancetime, 0.0f);
    if (D_8010FB64_chancetime >= 45.0f) {
        D_8010FB64_chancetime = 45.0f;
        Hu3DModelRotSet(obj->model[1], 0.0f, 45.0f, 0.0f);
        Hu3DModelRotSet(obj->model[3], 0.0f, -D_8010FB64_chancetime, 0.0f);
        if (D_800CCF58_main[HmfModelData[obj->model[1]].unk02].unk02 <= HmfModelData[obj->model[1]].unk40) {
            D_801100D4_chancetime.func = func_80107C84_chancetime;
            D_8010FB64_chancetime = 0.0f;
        }
    }
}

void func_80107C84_chancetime(omObjData *obj) {
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[3]].unk02, 0, 30, 2);
    func_8001C814_main(obj->model[5], 1, 0);
    func_8001C624_main(obj->model[3], HmfModelData[obj->motion[3]].unk02, 0, 30, 2);
    func_8001C814_main(obj->model[6], 1, 0);
    D_801100D4_chancetime.func = func_80107D60_chancetime;
}

void func_80107D60_chancetime(omObjData *obj) {
    if (func_8001C7D0_main(obj->model[1]) >= 5.0f) {
        func_8001EF6C_main(obj->model[5], obj->model[1], D_8010FC8C_chancetime);
        func_8001C258_main(obj->model[5], 4, 0);
        func_8001C814_main(obj->model[5], 1, 0);
        func_8001EF6C_main(obj->model[6], obj->model[3], D_8010FC8C_chancetime);
        func_8001C258_main(obj->model[6], 4, 0);
        func_8001C814_main(obj->model[6], 1, 0);
        func_80108738_chancetime(obj);
        D_801100D4_chancetime.func = func_80107A80_chancetime;
    }
}

void func_80107E40_chancetime(omObjData *obj) {
    func_8001C814_main(obj->model[5], 1, 1);
    func_8001C814_main(obj->model[6], 1, 1);
    func_8001C6A8_main(obj->model[5], 0.0f);
    func_8001C6A8_main(obj->model[6], 0.0f);
    func_8001C814_main(obj->model[5], 2, 0);
    func_8001C814_main(obj->model[6], 2, 0);
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[2]].unk02, 0, 30, 0);
    func_8001C624_main(obj->model[3], HmfModelData[obj->motion[2]].unk02, 0, 30, 0);
    D_801100D4_chancetime.func = func_80107F58_chancetime;
}

void func_80107F58_chancetime(omObjData *obj) {
    f32 frame = func_8001C7D0_main(obj->model[1]);

    if (D_8010FB68_chancetime == 0) {
        if (frame >= 20.0f) {
        func_8001C258_main(obj->model[5], 0x4000, 0);
        func_8001C258_main(obj->model[5], 4, 4);
        func_8001C258_main(obj->model[6], 0x4000, 0);
        func_8001C258_main(obj->model[6], 4, 4);
        func_80108738_chancetime(obj);
        D_8010FB68_chancetime = 1;
        }
    }
    if (frame < 0.0f) {
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
        func_8001C624_main(obj->model[3], HmfModelData[obj->motion[1]].unk02, 0, 30, 2);
        D_8010FB68_chancetime = 0;
        func_80108C08_chancetime(obj->model[1], D_8010FE8C_chancetime, D_8010FE84_chancetime[1]);
        D_801100D4_chancetime.func = func_801080EC_chancetime;
    }
}

void func_801080EC_chancetime(omObjData *obj) {
    s8 done;

    done = 0;
    if ((D_8010FB6C_chancetime += 8.0f) >= 45.0f) {
        D_8010FB6C_chancetime = 45.0f;
        done = 1;
    }
    Hu3DModelRotSet(obj->model[1], 0.0f, 45.0f - D_8010FB6C_chancetime, 0.0f);
    if ((D_8010FB70_chancetime += 8.0f) >= 135.0f) {
        D_8010FB70_chancetime = 135.0f;
        done++;
    }
    Hu3DModelRotSet(obj->model[3], 0.0f, D_8010FB70_chancetime + -45.0f, 0.0f);
    if (done >= 2) {
        func_8001C624_main(obj->model[3], HmfModelData[obj->motion[1]].unk02, 0, 30, 2);
        D_8010FB6C_chancetime = D_8010FB70_chancetime = 0.0f;
        D_801100D4_chancetime.func = func_8010827C_chancetime;
    }
}

void func_8010827C_chancetime(omObjData *obj) {
    s16 done = 0;

    if ((D_8010FB74_chancetime += 30.0f) >= 250.0f) {
        D_8010FB74_chancetime = 250.0f;
        done = 1;
    }
    Hu3DModelPosSet(obj->model[3], D_8010FB74_chancetime + 200.0f, 0.0f, -50.0f);
    Hu3DModelPosSet(obj->model[4], D_8010FB74_chancetime + 200.0f, -5.0f, -50.0f);
    if (done == 1) {
        D_8010FB74_chancetime = 0.0f;
        func_8001C258_main(obj->model[3], 4, 4);
        func_8001C258_main(obj->model[4], 4, 4);
        func_80106B18_chancetime();
        func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 30, 2);
        func_8001C624_main(obj->model[3], HmfModelData[obj->motion[5]].unk02, 0, 30, 2);
        D_801100D4_chancetime.func = func_80107A88_chancetime;
    }
}

void func_80108414_chancetime(omObjData *obj) {
    Hu3DModelPosSet(obj->model[1], -200.0f, sindf(D_8010FB78_chancetime * 18.0f) * 50.0f, -50.0f);
    Hu3DModelPosSet(obj->model[3], 200.0f, sindf(D_8010FB78_chancetime * 18.0f) * 50.0f, -50.0f);
    D_8010FB78_chancetime += 1.0f;
    if (D_8010FB78_chancetime >= 10.0f) {
        D_8010FB78_chancetime = 0.0f;
        Hu3DModelPosSet(obj->model[1], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(obj->model[3], 200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(obj->model[2], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(obj->model[4], 200.0f, 0.0f, -50.0f);
        D_8010FB00_chancetime = 0;
        D_8010FB04_chancetime = 1;
        D_801100D4_chancetime.func = func_80107A80_chancetime;
    }
}

void func_80108578_chancetime(omObjData *obj) {
    Hu3DModelPosSet(obj->model[1], -200.0f, sindf(D_8010FB7C_chancetime * 36.0f) * 20.0f, -50.0f);
    Hu3DModelPosSet(obj->model[3], 200.0f, sindf(D_8010FB7C_chancetime * 36.0f) * 20.0f, -50.0f);
    D_8010FB7C_chancetime += 1.0f;
    if (D_8010FB7C_chancetime >= 5.0f) {
        D_8010FB7C_chancetime = 0.0f;
        Hu3DModelPosSet(obj->model[1], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(obj->model[3], 200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(obj->model[2], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(obj->model[4], 200.0f, 0.0f, -50.0f);
        D_8010FB00_chancetime = 0;
        D_8010FB04_chancetime = 1;
        D_801100D4_chancetime.func = func_80107A80_chancetime;
    }
}

void func_801086DC_chancetime(void) {
    D_801100D4_chancetime.func = func_80107A98_chancetime;
}

void func_801086F0_chancetime(void) {
    D_801100D4_chancetime.func = func_80107E40_chancetime;
}

void func_80108704_chancetime(void) {
    D_8010FB00_chancetime = 1;
    D_8010FB04_chancetime = 0;
    D_801100D4_chancetime.func = func_80108414_chancetime;
}

s32 func_8010872C_chancetime(void) {
    return D_8010FB04_chancetime;
}

/* NON_MATCHING: the f32->s16 frame argument of func_80016B00_main truncates through $f0/$f2
 * swapped (register allocation only); logic matches. */
#ifdef NON_MATCHING
void func_80108738_chancetime(omObjData *obj) {
    ChanceMtx mtx;
    Vec pos;
    f32 angle;
    s16 model;

    model = obj->model[1];
    func_80016B00_main(model, HmfModelData[model].unk40, D_8010FC8C_chancetime, &mtx);
    angle = -HmfModelData[obj->model[1]].rot.y;
    pos.x = cosdf(angle) * mtx[3][0] - sindf(angle) * mtx[3][2];
    pos.y = mtx[3][1];
    pos.z = sindf(angle) * mtx[3][0] + cosdf(angle) * mtx[3][2];
    Hu3DModelPosSet(obj->model[7], HmfModelData[obj->model[1]].pos.x + pos.x,
                    HmfModelData[obj->model[1]].pos.y + pos.y - 100.0f,
                    HmfModelData[obj->model[1]].pos.z + pos.z + 80.0f);
    func_8001C258_main(obj->model[7], 4, 0);
    func_8001C814_main(obj->model[7], 2, 0);
    func_8001C814_main(obj->model[7], 1, 0);
    func_80014714_main(D_8010FE80_chancetime[0], 0);
    model = obj->model[3];
    func_80016B00_main(model, HmfModelData[model].unk40, D_8010FC8C_chancetime, &mtx);
    angle = -HmfModelData[obj->model[3]].rot.y;
    pos.x = cosdf(angle) * mtx[3][0] - sindf(angle) * mtx[3][2];
    pos.y = mtx[3][1];
    pos.z = sindf(angle) * mtx[3][0] + cosdf(angle) * mtx[3][2];
    Hu3DModelPosSet(obj->model[8], HmfModelData[obj->model[3]].pos.x + pos.x,
                    HmfModelData[obj->model[3]].pos.y + pos.y - 100.0f,
                    HmfModelData[obj->model[3]].pos.z + pos.z + 80.0f);
    func_8001C258_main(obj->model[8], 4, 0);
    func_8001C814_main(obj->model[8], 2, 0);
    func_8001C814_main(obj->model[8], 1, 0);
    func_80014714_main(D_8010FE80_chancetime[1], 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108738_chancetime);
#endif

void func_80108A88_chancetime(void) {
    omObjData *obj = D_801100D4_chancetime.obj;

    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[5]].unk02, 0, 30, 2);
    func_8001C624_main(obj->model[3], HmfModelData[obj->motion[5]].unk02, 0, 30, 2);
    D_8010FB08_chancetime = 0;
    D_801100D4_chancetime.func = func_80107A88_chancetime;
}

void func_80108B50_chancetime(void) {
    omObjData *obj = D_801100D4_chancetime.obj;

    D_801100D4_chancetime.func = func_80107A80_chancetime;
    func_8001C624_main(obj->model[1], HmfModelData[obj->motion[4]].unk02, 0, 30, 2);
    func_8001C624_main(obj->model[3], HmfModelData[obj->motion[4]].unk02, 0, 30, 2);
}

/* Pauses (frame -1) or restarts at a frame the texture animation slot of a model. */
void func_80108C08_chancetime(s16 model, s16 slot, s16 frame) {
    TexAnimSlot *p;

    if (slot >= 0) {
        if (frame == -1) {
            func_80033910_main(HmfModelData[model].hmf);
            return;
        }
        func_80033970_main(HmfModelData[model].hmf);
        p = &D_800D1714_main[slot];
        p->unk_00 = frame;
        p->unk_04 = 0;
        p->unk_0A = 0;
        p->unk_06 = 0;
        p->unk_02 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108CDC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108EDC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_801094CC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010963C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80109A00_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80109B70_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80109F34_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010A0A4_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010A468_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010A5D8_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010A99C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010AA90_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B030_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B124_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B6F4_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B7A0_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B7EC_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B818_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B834_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BA68_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BC10_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BC3C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BC88_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BD40_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BF3C_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BF48_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/4832D0", D_8010FC80_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/4832D0", D_8010FC8C_chancetime);
