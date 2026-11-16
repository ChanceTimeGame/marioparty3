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
void func_80108EDC_chancetime(omObjData *obj);
void func_8010963C_chancetime(omObjData *obj);
void func_80109B70_chancetime(omObjData *obj);
void func_8010A0A4_chancetime(omObjData *obj);
void func_8010A5D8_chancetime(omObjData *obj);
void func_8010AA90_chancetime(omObjData *obj);
void func_8010B124_chancetime(omObjData *obj);
s32 func_8010B6F4_chancetime(s16 model);
void func_8010B7A0_chancetime(s16 model);
void func_8010B818_chancetime(omObjData *obj, Vec *to, s32 frames);
void func_8010B834_chancetime(omObjData *obj, Vec *to, s32 frames, s32 turn);
void func_8010BA68_chancetime(omObjData *obj, Vec *to, s32 frames);
void func_8010BC10_chancetime(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
f32 func_8010BC3C_chancetime(Vec *from, Vec *to);
void func_8010BC88_chancetime(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_8010BD40_chancetime(void);

extern ChanceSprModel *D_800CBB60_main;
extern TexAnimSlot *D_800D1714_main;
extern char D_8010FC80_chancetime[]; // "c160n_0_DEF"
extern char D_8010FC8C_chancetime[]; // "item_hook"

extern s32 D_8010FB00_chancetime;
extern s32 D_8010FB04_chancetime;
extern s32 D_8010FB08_chancetime;
extern Vec D_8010FB0C_chancetime;
extern Vec D_8010FB18_chancetime;
extern Vec D_8010FB24_chancetime;
extern Vec D_8010FB30_chancetime;
extern Vec D_8010FB3C_chancetime;
extern Vec D_8010FB48_chancetime;
extern Vec D_8010FB54_chancetime;
extern s32 D_8010FB60_chancetime;
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

/* The Chance Time hosts' objects: [0] second host, [1]..[4] its copies, [5].. (D_80110090..D_801100BC) */
extern ChanceHost D_80110088_chancetime[7];
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

/* The second host (D_80110088_chancetime): appears at D_8010FB0C_chancetime and runs its state. */
void func_80108CDC_chancetime(void) {
    omObjData *obj;
    omObjData *host;
    void *data;
    s32 anim;

    obj = omAddObj(0x14, 4, 0, -1, NULL);
    D_80110088_chancetime[0].obj = obj;
    host = D_801100D4_chancetime.obj;
    obj->model[1] = func_8000B108_main(0xA0000, 0x2A9);
    Hu3DModelPosSet(obj->model[1], D_8010FB0C_chancetime.x, D_8010FB0C_chancetime.y, D_8010FB0C_chancetime.z);
    func_8001C8A8_main(obj->model[1], 2);
    data = DataRead(0xA002A);
    anim = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, D_8010FC80_chancetime);
    HuMemMemoryFreePerm(data);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(anim, 1, 0);
    func_80032FF8_main(anim, 0);
    obj->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], D_8010FB0C_chancetime.x, D_8010FB0C_chancetime.y, D_8010FB0C_chancetime.z);
    func_8001C8A8_main(obj->model[2], 2);
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 30, 2);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80110088_chancetime[0].func = func_80108EDC_chancetime;
    while (TRUE) {
        D_80110088_chancetime[0].func(obj);
        HuPrcVSleep();
    }
}

/* NON_MATCHING: in the final hop loop retail keeps model*3 and model*192 in separate registers
 * for the landing test and reloads 0.0f each pass (4 instructions); logic matches. */
#ifdef NON_MATCHING
void func_80108EDC_chancetime(omObjData *obj) {
    HmfModel *m;
    omObjData *host;
    f32 y;
    f32 vel;
    s32 i;
    s32 j;
    u16 model;

    model = obj->model[1];
    host = D_801100D4_chancetime.obj;
    HuPrcSleep(5);
    HuPrcSleep(2);
    y = HmfModelData[(s16)model].pos.y;
    for (j = 0; j < 3; j++) {
        func_8001C624_main(model, HmfModelData[host->motion[12]].unk02, 0, 10, 0);
        for (i = 0; i < 9; i++) {
            HmfModelData[(s16)model].pos.y = y + sindf(i * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[(s16)model].pos.y = y;
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(3);
    for (j = 0; j < 1; j++) {
        for (i = 0; i < 2; i++) {
            func_8001C624_main(model, HmfModelData[host->motion[5]].unk02, 0, 10, 0);
            func_8001C92C_main(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        func_8001C624_main(model, HmfModelData[host->motion[6]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
        func_8001C624_main(model, HmfModelData[host->motion[7]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    func_8001C624_main(model, HmfModelData[host->motion[8]].unk02, 0, 10, 0);
    HuPrcSleep(20);
    omAddPrcObj(func_8010BD40_chancetime, 0x1001, 0x2000, 0);
    HuPrcSleep(10);
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[12]].unk02, 0, 10, 0);
    /* retail also copies the model's position here into an unused Vec */
    vel = 20.0f;
    while (TRUE) {
        m = &HmfModelData[(s16)model];
        m->pos.y += vel;
        m->pos.z += 20.0f;
        if (m->pos.z >= -250.0f) {
            HmfModelData[obj->model[2]].pos.x = m->pos.x;
            HmfModelData[obj->model[2]].pos.y = 0.0f;
            HmfModelData[obj->model[2]].pos.z = m->pos.z;
            func_8001C258_main(obj->model[2], 4, 0);
        }
        if (HmfModelData[(s16)model].pos.y <= 0.0f) {
            break;
        }
        vel -= 3.0f;
        HuPrcVSleep();
    }
    m = &HmfModelData[(s16)model];
    m->pos.y = 0.0f;
    HmfModelData[obj->model[2]].pos.x = m->pos.x;
    HmfModelData[obj->model[2]].pos.y = 0.0f;
    HmfModelData[obj->model[2]].pos.z = m->pos.z;
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[1]].unk02, 0, 10, 2);
    func_8010BC88_chancetime(obj, 0.0f, 0.0f, 500.0f, 5);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80110088_chancetime[0].func = func_80107A80_chancetime;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_80108EDC_chancetime);
#endif

void func_801094CC_chancetime(void) {
    omObjData *obj;
    omObjData *host;
    omObjData *src;

    obj = omAddObj(0x14, 4, 0, -1, NULL);
    D_80110088_chancetime[1].obj = obj;
    host = D_801100D4_chancetime.obj;
    src = D_80110088_chancetime[0].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    Hu3DModelPosSet(obj->model[1], D_8010FB18_chancetime.x, D_8010FB18_chancetime.y, D_8010FB18_chancetime.z);
    func_8001C8A8_main(obj->model[1], 2);
    obj->model[2] = Hu3DModelLink(src->model[2]);
    Hu3DModelPosSet(obj->model[2], D_8010FB18_chancetime.x, D_8010FB18_chancetime.y, D_8010FB18_chancetime.z);
    func_8001C8A8_main(obj->model[2], 2);
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80110088_chancetime[1].func = func_8010963C_chancetime;
    while (TRUE) {
        D_80110088_chancetime[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010963C_chancetime(omObjData *obj) {
    omObjData *host;
    f32 y;
    s32 i;
    s32 j;
    s16 model;

    model = obj->model[1];
    host = D_801100D4_chancetime.obj;
    HuPrcSleep(5);
    HuPrcSleep(4);
    y = HmfModelData[model].pos.y;
    for (j = 0; j < 3; j++) {
        func_8001C624_main(model, HmfModelData[host->motion[12]].unk02, 0, 10, 0);
        for (i = 0; i < 9; i++) {
            HmfModelData[model].pos.y = y + sindf(i * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(1);
    for (j = 0; j < 1; j++) {
        for (i = 0; i < 2; i++) {
            func_8001C624_main(model, HmfModelData[host->motion[5]].unk02, 0, 10, 0);
            func_8001C92C_main(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        func_8001C624_main(model, HmfModelData[host->motion[6]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
        func_8001C624_main(model, HmfModelData[host->motion[7]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    func_8001C624_main(model, HmfModelData[host->motion[9]].unk02, 0, 10, 0);
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[host->motion[1]].unk02, 0, 10, 2);
    func_8010BC88_chancetime(obj, -400.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80110088_chancetime[1].func = func_80107A80_chancetime;
}

void func_80109A00_chancetime(void) {
    omObjData *obj;
    omObjData *host;
    omObjData *src;

    obj = omAddObj(0x14, 4, 0, -1, NULL);
    D_80110088_chancetime[2].obj = obj;
    host = D_801100D4_chancetime.obj;
    src = D_80110088_chancetime[0].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    Hu3DModelPosSet(obj->model[1], D_8010FB24_chancetime.x, D_8010FB24_chancetime.y, D_8010FB24_chancetime.z);
    func_8001C8A8_main(obj->model[1], 2);
    obj->model[2] = Hu3DModelLink(src->model[2]);
    Hu3DModelPosSet(obj->model[2], D_8010FB24_chancetime.x, D_8010FB24_chancetime.y, D_8010FB24_chancetime.z);
    func_8001C8A8_main(obj->model[2], 2);
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80110088_chancetime[2].func = func_80109B70_chancetime;
    while (TRUE) {
        D_80110088_chancetime[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80109B70_chancetime(omObjData *obj) {
    omObjData *host;
    f32 y;
    s32 i;
    s32 j;
    s16 model;

    model = obj->model[1];
    host = D_801100D4_chancetime.obj;
    HuPrcSleep(5);
    HuPrcSleep(1);
    y = HmfModelData[model].pos.y;
    for (j = 0; j < 3; j++) {
        func_8001C624_main(model, HmfModelData[host->motion[12]].unk02, 0, 10, 0);
        for (i = 0; i < 9; i++) {
            HmfModelData[model].pos.y = y + sindf(i * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(4);
    for (j = 0; j < 1; j++) {
        for (i = 0; i < 2; i++) {
            func_8001C624_main(model, HmfModelData[host->motion[5]].unk02, 0, 10, 0);
            func_8001C92C_main(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        func_8001C624_main(model, HmfModelData[host->motion[6]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
        func_8001C624_main(model, HmfModelData[host->motion[7]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    func_8001C624_main(model, HmfModelData[host->motion[9]].unk02, 0, 10, 0);
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[host->motion[1]].unk02, 0, 10, 2);
    func_8010BC88_chancetime(obj, -200.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80110088_chancetime[2].func = func_80107A80_chancetime;
}

void func_80109F34_chancetime(void) {
    omObjData *obj;
    omObjData *host;
    omObjData *src;

    obj = omAddObj(0x14, 4, 0, -1, NULL);
    D_80110088_chancetime[3].obj = obj;
    host = D_801100D4_chancetime.obj;
    src = D_80110088_chancetime[0].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    Hu3DModelPosSet(obj->model[1], D_8010FB30_chancetime.x, D_8010FB30_chancetime.y, D_8010FB30_chancetime.z);
    func_8001C8A8_main(obj->model[1], 2);
    obj->model[2] = Hu3DModelLink(src->model[2]);
    Hu3DModelPosSet(obj->model[2], D_8010FB30_chancetime.x, D_8010FB30_chancetime.y, D_8010FB30_chancetime.z);
    func_8001C8A8_main(obj->model[2], 2);
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80110088_chancetime[3].func = func_8010A0A4_chancetime;
    while (TRUE) {
        D_80110088_chancetime[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A0A4_chancetime(omObjData *obj) {
    omObjData *host;
    f32 y;
    s32 i;
    s32 j;
    s16 model;

    model = obj->model[1];
    host = D_801100D4_chancetime.obj;
    HuPrcSleep(5);
    HuPrcSleep(3);
    y = HmfModelData[model].pos.y;
    for (j = 0; j < 3; j++) {
        func_8001C624_main(model, HmfModelData[host->motion[12]].unk02, 0, 10, 0);
        for (i = 0; i < 9; i++) {
            HmfModelData[model].pos.y = y + sindf(i * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(2);
    for (j = 0; j < 1; j++) {
        for (i = 0; i < 2; i++) {
            func_8001C624_main(model, HmfModelData[host->motion[5]].unk02, 0, 10, 0);
            func_8001C92C_main(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        func_8001C624_main(model, HmfModelData[host->motion[6]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
        func_8001C624_main(model, HmfModelData[host->motion[7]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    func_8001C624_main(model, HmfModelData[host->motion[10]].unk02, 0, 10, 0);
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[host->motion[1]].unk02, 0, 10, 2);
    func_8010BC88_chancetime(obj, 200.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80110088_chancetime[3].func = func_80107A80_chancetime;
}

void func_8010A468_chancetime(void) {
    omObjData *obj;
    omObjData *host;
    omObjData *src;

    obj = omAddObj(0x14, 4, 0, -1, NULL);
    D_80110088_chancetime[4].obj = obj;
    host = D_801100D4_chancetime.obj;
    src = D_80110088_chancetime[0].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    Hu3DModelPosSet(obj->model[1], D_8010FB3C_chancetime.x, D_8010FB3C_chancetime.y, D_8010FB3C_chancetime.z);
    func_8001C8A8_main(obj->model[1], 2);
    obj->model[2] = Hu3DModelLink(src->model[2]);
    Hu3DModelPosSet(obj->model[2], D_8010FB3C_chancetime.x, D_8010FB3C_chancetime.y, D_8010FB3C_chancetime.z);
    func_8001C8A8_main(obj->model[2], 2);
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80110088_chancetime[4].func = func_8010A5D8_chancetime;
    while (TRUE) {
        D_80110088_chancetime[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A5D8_chancetime(omObjData *obj) {
    omObjData *host;
    f32 y;
    s32 i;
    s32 j;
    s16 model;

    model = obj->model[1];
    host = D_801100D4_chancetime.obj;
    HuPrcSleep(5);
    HuPrcSleep(4);
    y = HmfModelData[model].pos.y;
    for (j = 0; j < 3; j++) {
        func_8001C624_main(model, HmfModelData[host->motion[12]].unk02, 0, 10, 0);
        for (i = 0; i < 9; i++) {
            HmfModelData[model].pos.y = y + sindf(i * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(1);
    for (j = 0; j < 1; j++) {
        for (i = 0; i < 2; i++) {
            func_8001C624_main(model, HmfModelData[host->motion[5]].unk02, 0, 10, 0);
            func_8001C92C_main(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        func_8001C624_main(model, HmfModelData[host->motion[6]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
        func_8001C624_main(model, HmfModelData[host->motion[7]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    func_8001C624_main(model, HmfModelData[host->motion[10]].unk02, 0, 10, 0);
    HuPrcSleep(50);
    func_8001C624_main(model, HmfModelData[host->motion[1]].unk02, 0, 10, 2);
    func_8010BC88_chancetime(obj, 400.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80110088_chancetime[4].func = func_80107A80_chancetime;
}

void func_8010A99C_chancetime(void) {
    omObjData *host;
    omObjData *obj;

    host = D_801100D4_chancetime.obj;
    obj = omAddObj(0x14, 4, 0, -1, NULL);
    D_80110088_chancetime[5].obj = obj;
    obj->model[1] = host->model[1];
    obj->model[2] = host->model[2];
    Hu3DModelPosSet(obj->model[1], D_8010FB48_chancetime.x, D_8010FB48_chancetime.y, D_8010FB48_chancetime.z);
    Hu3DModelPosSet(obj->model[2], D_8010FB48_chancetime.x, D_8010FB48_chancetime.y, D_8010FB48_chancetime.z);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80110088_chancetime[5].func = func_8010AA90_chancetime;
    while (TRUE) {
        D_80110088_chancetime[5].func(obj);
        HuPrcVSleep();
    }
}

/* NON_MATCHING: as func_80108EDC_chancetime (retail also copies the position into an unused Vec
 * before the hop and splits the landing test's index); logic matches. */
#ifdef NON_MATCHING
void func_8010AA90_chancetime(omObjData *obj) {
    HmfModel *p;
    omObjData *host;
    f32 y;
    f32 vel;
    s32 i;
    s32 j;
    s16 model;

    model = D_801100D4_chancetime.obj->model[1];
    host = D_801100D4_chancetime.obj;
    HuPrcSleep(5);
    HuPrcSleep(3);
    y = HmfModelData[model].pos.y;
    for (j = 0; j < 3; j++) {
        func_8001C624_main(model, HmfModelData[host->motion[12]].unk02, 0, 10, 0);
        for (i = 0; i < 9; i++) {
            HmfModelData[model].pos.y = y + sindf(i * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(2);
    for (j = 0; j < 1; j++) {
        for (i = 0; i < 2; i++) {
            func_8001C624_main(model, HmfModelData[host->motion[5]].unk02, 0, 10, 0);
            func_8001C92C_main(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        func_8001C624_main(model, HmfModelData[host->motion[6]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
        func_8001C624_main(model, HmfModelData[host->motion[7]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    func_8001C624_main(model, HmfModelData[host->motion[9]].unk02, 0, 10, 0);
    HuPrcSleep(42);
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[12]].unk02, 0, 10, 0);
    vel = 20.0f;
    while (TRUE) {
        p = &HmfModelData[model];
        p->pos.y += vel;
        p->pos.z += 10.0f;
        if (p->pos.z >= -250.0f) {
            HmfModelData[obj->model[2]].pos.x = p->pos.x;
            HmfModelData[obj->model[2]].pos.y = 0.0f;
            HmfModelData[obj->model[2]].pos.z = p->pos.z;
            func_8001C258_main(obj->model[2], 4, 0);
        }
        if (HmfModelData[model].pos.y <= 0.0f) {
            break;
        }
        vel -= 2.0f;
        HuPrcVSleep();
    }
    p = &HmfModelData[model];
    p->pos.y = 0.0f;
    HmfModelData[obj->model[2]].pos.x = p->pos.x;
    HmfModelData[obj->model[2]].pos.y = 0.0f;
    HmfModelData[obj->model[2]].pos.z = p->pos.z;
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[5]].unk02, 0, 10, 2);
    D_8010FB60_chancetime = 1;
    D_80110088_chancetime[5].func = func_80107A80_chancetime;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010AA90_chancetime);
#endif

void func_8010B030_chancetime(void) {
    omObjData *host;
    omObjData *obj;

    host = D_801100D4_chancetime.obj;
    obj = omAddObj(0x14, 4, 0, -1, NULL);
    D_80110088_chancetime[6].obj = obj;
    obj->model[1] = host->model[3];
    obj->model[2] = host->model[4];
    Hu3DModelPosSet(obj->model[1], D_8010FB54_chancetime.x, D_8010FB54_chancetime.y, D_8010FB54_chancetime.z);
    Hu3DModelPosSet(obj->model[2], D_8010FB54_chancetime.x, D_8010FB54_chancetime.y, D_8010FB54_chancetime.z);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80110088_chancetime[6].func = func_8010B124_chancetime;
    while (TRUE) {
        D_80110088_chancetime[6].func(obj);
        HuPrcVSleep();
    }
}

/* NON_MATCHING: as func_80108EDC_chancetime (retail also copies the position into an unused Vec
 * before the hop and splits the landing test's index); logic matches. */
#ifdef NON_MATCHING
void func_8010B124_chancetime(omObjData *obj) {
    HmfModel *p;
    omObjData *host;
    f32 y;
    f32 vel;
    s32 i;
    s32 j;
    s16 model;

    model = D_801100D4_chancetime.obj->model[3];
    host = D_801100D4_chancetime.obj;
    HuPrcSleep(5);
    HuPrcSleep(4);
    y = HmfModelData[model].pos.y;
    for (j = 0; j < 3; j++) {
        func_8001C624_main(model, HmfModelData[host->motion[12]].unk02, 0, 10, 0);
        for (i = 0; i < 9; i++) {
            HmfModelData[model].pos.y = y + sindf(i * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    HmfModelData[model].pos.y = y;
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[0]].unk02, 0, 10, 2);
    HuPrcSleep(1);
    for (j = 0; j < 1; j++) {
        for (i = 0; i < 2; i++) {
            func_8001C624_main(model, HmfModelData[host->motion[5]].unk02, 0, 10, 0);
            func_8001C92C_main(model, 1.5f);
            func_8010B7A0_chancetime(model);
        }
        func_8001C624_main(model, HmfModelData[host->motion[6]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
        func_8001C624_main(model, HmfModelData[host->motion[7]].unk02, 0, 10, 0);
        func_8001C92C_main(model, 1.5f);
        func_8010B7A0_chancetime(model);
    }
    HuPrcSleep(1);
    func_8001C624_main(model, HmfModelData[host->motion[10]].unk02, 0, 10, 0);
    HuPrcSleep(42);
    func_8001C624_main(obj->model[1], HmfModelData[host->motion[12]].unk02, 0, 10, 0);
    vel = 20.0f;
    while (TRUE) {
        p = &HmfModelData[model];
        p->pos.y += vel;
        p->pos.z += 10.0f;
        if (p->pos.z >= -250.0f) {
            HmfModelData[obj->model[2]].pos.x = p->pos.x;
            HmfModelData[obj->model[2]].pos.y = 0.0f;
            HmfModelData[obj->model[2]].pos.z = p->pos.z;
            func_8001C258_main(obj->model[2], 4, 0);
        }
        if (HmfModelData[model].pos.y <= 0.0f) {
            break;
        }
        vel -= 3.0f;
        HuPrcVSleep();
    }
    p = &HmfModelData[model];
    p->pos.y = 0.0f;
    HmfModelData[obj->model[2]].pos.x = p->pos.x;
    HmfModelData[obj->model[2]].pos.y = 0.0f;
    HmfModelData[obj->model[2]].pos.z = p->pos.z;
    func_8001C624_main(model, HmfModelData[host->motion[1]].unk02, 0, 10, 2);
    func_8010BC88_chancetime(obj, 400.0f, 0.0f, 300.0f, 10);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_80110088_chancetime[6].func = func_80107A80_chancetime;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010B124_chancetime);
#endif

/* -1 once model's motion has stopped at its last frame, else 0. */
s32 func_8010B6F4_chancetime(s16 model) {
    f32 frame;
    s32 ret;

    frame = func_8001C7D0_main(model);
    ret = 0;
    if (frame == -1.0f) {
        if (D_800CCF58_main[HmfModelData[model].unk02].unk02 <= HmfModelData[model].unk40) {
            ret = -1;
        }
    }
    return ret;
}

void func_8010B7A0_chancetime(s16 model) {
    HuPrcSleep(15);
    while (func_8010B6F4_chancetime(model) == 0) {
        HuPrcVSleep();
    }
}

void func_8010B7EC_chancetime(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_8010B818_chancetime(obj, &to, frames);
}

void func_8010B818_chancetime(omObjData *obj, Vec *to, s32 frames) {
    func_8010B834_chancetime(obj, to, frames, 1);
}

/* Walks model[1] (and its shadow model[2], if any) in a straight line to `to` over `frames`
   frames, turning it to face the way first when `turn` is set. */
void func_8010B834_chancetime(omObjData *obj, Vec *to, s32 frames, s32 turn) {
    Vec from;
    Vec dist;
    Vec step;
    Vec pos;
    f32 t;
    s16 model;

    model = obj->model[1];
    from.x = HmfModelData[model].pos.x;
    from.y = HmfModelData[model].pos.y;
    from.z = HmfModelData[model].pos.z;
    dist.x = to->x - from.x;
    dist.y = to->y - from.y;
    dist.z = to->z - from.z;
    if (turn) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(dist.z, dist.x) - 90.0f), 0.0f);
    }
    t = frames;
    step.x = dist.x / t;
    step.y = dist.y / t;
    step.z = dist.z / t;
    for (t = 0.0f; t < frames; t += 1.0f) {
        pos.x = t * step.x + from.x;
        pos.y = t * step.y + from.y;
        pos.z = t * step.z + from.z;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], pos.x, 0.0f, pos.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, to->x, to->y, to->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], to->x, 0.0f, to->z);
    }
    HuPrcVSleep();
}

/* Eases model[1]'s rotation to `to` over `frames` frames (sine ease-out). */
void func_8010BA68_chancetime(omObjData *obj, Vec *to, s32 frames) {
    Vec from;
    Vec dist;
    Vec rot;
    f32 t;
    f32 angle;
    s16 model;

    model = obj->model[1];
    from.x = HmfModelData[model].rot.x;
    from.y = HmfModelData[model].rot.y;
    from.z = HmfModelData[model].rot.z;
    dist.x = to->x - from.x;
    dist.y = to->y - from.y;
    dist.z = to->z - from.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        angle = 90.0f / frames * t;
        rot.x = sindf(angle) * dist.x + from.x;
        rot.y = sindf(angle) * dist.y + from.y;
        rot.z = sindf(angle) * dist.z + from.z;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, to->x, to->y, to->z);
    HuPrcVSleep();
}

void func_8010BC10_chancetime(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec to;

    to.x = x;
    to.y = y;
    to.z = z;
    func_8010BA68_chancetime(obj, &to, frames);
}

/* Facing angle (degrees, model rot.y) from `from` toward `to`. */
f32 func_8010BC3C_chancetime(Vec *from, Vec *to) {
    Vec d;

    d.x = to->x - from->x;
    d.z = to->z - from->z;
    return -(atan2df(d.z, d.x) - 90.0f);
}

/* Turns model[1] toward (x, y, z) over 10 frames, then walks there over `frames` frames. */
void func_8010BC88_chancetime(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec from;
    Vec to;
    s16 model;

    model = obj->model[1];
    from.x = HmfModelData[model].pos.x;
    from.y = HmfModelData[model].pos.y;
    from.z = HmfModelData[model].pos.z;
    to.x = x;
    to.y = y;
    to.z = z;
    func_8010BC10_chancetime(obj, 0.0f, func_8010BC3C_chancetime(&from, &to), 0.0f, 10);
    func_8010B818_chancetime(obj, &to, frames);
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/4832D0", func_8010BD40_chancetime);

s32 func_8010BF3C_chancetime(void) {
    return D_8010FB60_chancetime;
}

void func_8010BF48_chancetime(void) {
    omObjData *obj = D_801100D4_chancetime.obj;

    func_8010BC10_chancetime(obj, 0.0f, 45.0f, 0.0f, 10);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/4832D0", D_8010FC80_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/4832D0", D_8010FC8C_chancetime);
