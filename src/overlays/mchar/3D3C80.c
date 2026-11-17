#include "common.h"
#include "game/object.h"
#include "game/hmfman.h"
#include "math.h"
#include "game/pause.h"

/* Character motion viewer (ovl_56, a debug overlay): the eight characters' two models, a motion picked
   from 160 with the C buttons, the camera on the first controller. */

extern u16 omdispinfo;
extern s16 D_800A1786_main;
extern s32 fontcolor;
void func_80045C2C_main(void);
void func_8004DEC8_main(s16 arg0);
void* DataReadTemp(s32 dirAndFile);
void DataCloseTemp(void* data);
f32 func_8002FC7C_main(D_800CCF58_main_Struct *anim, u8 flags, f32 time, f32 end, f32 speed);

void func_80105B38_mchar(omObjData *obj);
void func_80105C4C_mchar(omObjData *obj);
void func_8010654C_mchar(s16 set);
void func_80106764_mchar(s16 motion);
void func_80106898_mchar(omObjData *obj);
void func_80106D7C_mchar(void);
void func_80106DF8_mchar(omObjData *obj);
void func_80106E54_mchar(omObjData *obj);

/* .bss */
extern char D_80107950_mchar[0x100];    /* print buffer */
extern Vec D_80107A50_mchar;            /* camera rotation (D_80107A54_mchar: its y) */
extern s32 D_80107A60_mchar[8][2];      /* each character's two models */
/* a character's pair of model files, or of motions (current, previous) */
typedef struct MCharPair {
    /* 0x00 */ s32 a;
    /* 0x04 */ s32 b;
} MCharPair;
extern MCharPair D_80107AA0_mchar[8];   /* each character's motion: current, previous */

/* .data (0x3D5160) */
u16 D_80106E80_mchar = 0;              /* quit */
u8 D_80106E82_mchar = 1;               /* show the text */
s16 D_80106E84_mchar[8] = { 2, 3, 7, 4, 5, 6, 8, 9 }; /* voice set per character */
char *D_80106E94_mchar[160] = {
    "C000_000", "C000_001", "C000_003", "C000_004", "C000_005", "C000_006",
    "C000_009", "C000_010", "C000_011", "C000_012", "C000_013", "C000_020",
    "C000_022", "C000_023", "C000_024", "C000_028", "C000_029", "C000_030",
    "C000_036", "C000_039", "C000_047", "C000_048", "C000_049", "C000_050",
    "C000_068", "C000_072", "C000_078", "C000_101", "C000_113", "C000_114",
    "C000_115", "C000_116", "C000_117", "C000_118", "C000_121", "C000_122",
    "C000_123", "C000_172", "C000_178", "C000_227", "C000_228", "C000_243",
    "C000_277", "C000_288", "C000_308", "C000_322", "C000_323", "C000_400",
    "C000_401", "C000_402", "C000_403", "C000_404", "C000_405", "C000_406",
    "C000_407", "C000_408", "C000_409", "C000_410", "C000_411", "C000_413",
    "C000_414", "C000_415", "C000_416", "C000_417", "C000_418", "C000_419",
    "C000_420", "C000_421", "C000_422", "C000_423", "C000_424", "C000_426",
    "C000_427", "C000_428", "C000_429", "C000_430", "C000_431", "C000_432",
    "C000_437", "C000_438", "C000_439", "C000_440", "C000_441", "C000_442",
    "C000_445", "C000_446", "C000_447", "C000_448", "C000_449", "C000_450",
    "C000_451", "C000_453", "C000_455", "C000_456", "C000_458", "C000_459",
    "C000_460", "C000_461", "C000_462", "C000_463", "C000_464", "C000_465",
    "C000_466", "C000_467", "C000_468", "C000_469", "C000_470", "C000_471",
    "C000_472", "C000_473", "C000_474", "C000_476", "C000_477", "C000_478",
    "C000_479", "C000_480", "C000_481", "C000_482", "C000_483", "C000_484",
    "C000_485", "C000_486", "C000_487", "C000_488", "C000_489", "C000_490",
    "C000_491", "C000_492", "C000_493", "C000_494", "C000_495", "C000_496",
    "C000_497", "C000_498", "C000_499", "C000_500", "C000_501", "C000_502",
    "C000_504", "C000_505", "C000_506", "C000_507", "C000_508", "C000_509",
    "C000_510", "C000_511", "C000_512", "C000_513", "C000_514", "C000_515",
    "C000_516", "C000_517", "C000_518", "C000_519", "C000_520", "C000_521",
    "C000_522", "C000_523", "C000_524", "C000_100",
};
s16 D_80107114_mchar = 0;              /* character */
s16 D_80107116_mchar = 0;              /* motion */
s16 D_80107118_mchar = 0;              /* which of the two models */
s16 D_8010711A_mchar = 0;              /* model set, D_80107120_mchar[set..] */
u8 D_8010711C_mchar = 0;
u8 D_8010711D_mchar = 0;               /* frames until the models are reloaded */
MCharPair D_80107120_mchar[8] = {
    { 0x000200A2, 0x000200A1 }, { 0x000300A2, 0x000300A1 }, { 0x000700A2, 0x000700A1 }, { 0x000400A2, 0x000400A1 },
    { 0x000500A2, 0x000500A1 }, { 0x000600A2, 0x000600A1 }, { 0x000800A2, 0x000800A1 }, { 0x00090003, 0x00090001 },
};

void func_801059A0_mchar(void) {
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    if (omdispinfo != 0) {
        omdispinfo = 0;
        func_8004DEC8_main(D_800A1786_main);
        D_800A1786_main = -1;
    }
    omAddObj(0x2710, 0, 0, -1, func_80106DF8_mchar);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, -100.0f, 100.0f, 100.0f);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    func_80106D7C_mchar();
    omAddObj(0x7D0, 0xA, 0xA, -1, func_80105B38_mchar);
    omAddObj(0x7D0, 0, 0, -1, func_80106898_mchar);
    WipeCreateIn(0, 0x10);
    D_800CD280_main = 1;
    func_8001F38C_main(0xC0, 0xE0, 0xFF);
    func_80045C2C_main();
}

#ifdef NON_MATCHING
void func_80105B38_mchar(omObjData *obj) {
    s16 i;

    obj->model[0] = -1;
    for (i = 0; i < 8; i++) {
        D_80107AA0_mchar[i].b = -1;
        D_80107AA0_mchar[i].a = -1;
        D_80107A60_mchar[i][1] = -1;
        D_80107A60_mchar[i][0] = -1;
    }
    D_8010711A_mchar = 0;
    func_8010654C_mchar(0);
    func_8001C258_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
    func_8001C814_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
    obj->func = func_80105C4C_mchar;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mchar/3D3C80", func_80105B38_mchar);
#endif

/* per frame: C up/down pick the motion (and play the character's voice for it), R swaps the two models
   (keeping the motion time), D-pad left/right the character, pad 2 L/R step the motion, both C left and
   right quit; pad 2 START toggles the text */
void func_80105C4C_mchar(omObjData *obj) {
    HmfModel *src;
    HmfModel *dst;

    if (D_8010711D_mchar != 0) {
        D_8010711D_mchar--;
        if (D_8010711D_mchar == 0) {
            func_8010654C_mchar(D_8010711A_mchar);
            func_8001C258_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
            func_8001C814_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
        }
    }
    if ((u16)D_800D0590_main[0] & 0x8000) {
        if (++D_80107116_mchar >= 160) {
            D_80107116_mchar = 0;
        }
        func_80106764_mchar(D_80107116_mchar);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if ((u16)D_800D0590_main[0] & 0x4000) {
        if (--D_80107116_mchar < 0) {
            D_80107116_mchar = 159;
        }
        func_80106764_mchar(D_80107116_mchar);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if (D_800D5558_main[0] & 0x1000) {
        D_8010711C_mchar++;
    }
    if (D_800D5558_main[0] & 4) {
        func_8001C258_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 4);
        src = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        if (++D_80107118_mchar >= 2) {
            D_80107118_mchar = 0;
        }
        func_8001C258_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
        dst = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        dst->unk02 = src->unk02;
        dst->unk40 = src->unk40;
        dst->unk03 = src->unk03;
        dst->unk4C = src->unk4C;
        dst->unk05 = src->unk05;
        dst->unk04 = src->unk04;
    }
    if (D_800D5558_main[0] & 2) {
        func_8001C258_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 4);
        if (++D_80107114_mchar >= 8) {
            D_80107114_mchar = 0;
        }
        func_8001C258_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
        func_8001F304_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], D_80107AA0_mchar[D_80107114_mchar].a);
        func_8001C814_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if (D_800D5558_main[0] & 1) {
        func_8001C258_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 4);
        if (--D_80107114_mchar < 0) {
            D_80107114_mchar = 7;
        }
        func_8001C258_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
        func_8001F304_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], D_80107AA0_mchar[D_80107114_mchar].a);
        func_8001C814_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if ((u16)D_800D0590_main[1] & 0xC000) {
        src = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        if ((u16)D_800D0590_main[1] & 0x4000) {
            src->unk03 |= 4;
        }
        src->unk03 &= ~1;
        src->unk40 = func_8002FC7C_main(&D_800CCF58_main[src->unk02], src->unk03, src->unk40, src->unk48,
                                          2.0f * src->unk44);
        src->unk4C = func_8002FC7C_main(&D_800CCF58_main[src->unk04], src->unk05, src->unk4C, src->unk54,
                                          2.0f * src->unk50);
        src->unk03 = (src->unk03 & ~4) | 1;
    }
    if ((D_800CDA7C_main[0] & 0x30) == 0x30) {
        D_80106E80_mchar = 1;
    }
    if (D_800D5558_main[1] & 0x1000) {
        D_80106E82_mchar = D_80106E82_mchar == 0;
    }
    if (D_80106E82_mchar != 0) {
        src = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        fontcolor = 9;
        sprintf(D_80107950_mchar, "MOTIONNO.%3d <%s>", D_80107116_mchar, D_80106E94_mchar[D_80107116_mchar]);
        print8(0x18, 0xB6, D_80107950_mchar);
        sprintf(D_80107950_mchar, "CENTER:%3.3f,%3.3f,%3.3f", Center.x, Center.y, Center.z);
        print8(0x18, 0xBE, D_80107950_mchar);
        sprintf(D_80107950_mchar, "ROTATE:%3.3f,%3.3f,%3.3f", CRot.x, CRot.y, CRot.z);
        print8(0x18, 0xC6, D_80107950_mchar);
        sprintf(D_80107950_mchar, "ZOOM:  %3.3f", CZoom);
        print8(0x18, 0xCE, D_80107950_mchar);
        sprintf(D_80107950_mchar, "M_TIME:%d", (u16)src->unk40);
        print8(0x18, 0xD6, D_80107950_mchar);
    }
}

/* loads the eight characters' two models from set `set` and their motion 0 */
#ifdef NON_MATCHING
void func_8010654C_mchar(s16 set) {
    s16 i;
    void *data;

    for (i = 0; i < 8; i++) {
        D_80107A60_mchar[i][0] = func_8000B108_main(D_80107120_mchar[i + set].a, 0x2AC);
        func_80017790_main(D_80107A60_mchar[i][0], 0, i, func_80017BB8_main(i, 0xA3));
        func_8001C514_main(D_80107A60_mchar[i][0]);
        D_80107A60_mchar[i][1] = func_8000B108_main(D_80107120_mchar[i + set].b, 0x2AC);
        func_80017790_main(D_80107A60_mchar[i][1], 1, i, func_80017BB8_main(i, 0xA4));
        func_8001C514_main(D_80107A60_mchar[i][1]);
        if (D_80107AA0_mchar[i].a != -1) {
            func_8002D4B8_main(D_80107AA0_mchar[i].a);
        }
        if (D_80107AA0_mchar[i].b != -1) {
            func_8002D4B8_main(D_80107AA0_mchar[i].b);
        }
        data = DataReadTemp(func_80017BB8_main(i, 0));
        D_80107AA0_mchar[i].a = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
        D_80107AA0_mchar[i].b = -1;
        func_8001F304_main(D_80107A60_mchar[i][0], D_80107AA0_mchar[i].a);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mchar/3D3C80", func_8010654C_mchar);
#endif

/* loads motion `motion` for every character (the previous one is kept until the next load) */
void func_80106764_mchar(s16 motion) {
    s16 i;
    void *data;

    for (i = 0; i < 8; i++) {
        if (D_80107AA0_mchar[i].b != -1) {
            func_8002D4B8_main(D_80107AA0_mchar[i].b);
        }
        D_80107AA0_mchar[i].b = D_80107AA0_mchar[i].a;
        data = DataReadTemp(func_80017BB8_main(i, motion));
        D_80107AA0_mchar[i].a = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
    }
    func_8001C624_main(D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], D_80107AA0_mchar[D_80107114_mchar].a, 0,
                       0xA, 2);
}

// masked 37: as mgenter func_80108A60_mgenter, retail addresses Center through a base register (one more $f register here)
/* debug camera on the first controller (as mgenter's func_80108A60_mgenter): L resets it, C up/down zoom,
   the stick turns, the D-pad moves the target; Z with it goes faster */
#ifdef NON_MATCHING
void func_80106898_mchar(omObjData *obj) {
    f32 rx;
    f32 ry;
    f32 spd;
    f32 dx;
    f32 dz;
    f32 inv;

    if (D_800CDA7C_main[0] & 0x1000) {
        func_80106D7C_mchar();
    }
    if (D_800CDA7C_main[0] & 0x20) {
        if (D_800CDA7C_main[0] & 0x2000) {
            CZoom += 30.0f;
        } else {
            CZoom += 10.0f;
        }
    }
    if ((D_800CDA7C_main[0] & 0x10) && CZoom - 10.0f != 0.0f) {
        if (D_800CDA7C_main[0] & 0x2000) {
            CZoom -= 30.0f;
        } else {
            CZoom -= 10.0f;
        }
    }
    rx = D_80107A50_mchar.x;
    ry = D_80107A50_mchar.y;
    if (D_800CDA7C_main[0] & 0x2000) {
        spd = 5.0f;
    } else {
        spd = 2.0f;
    }
    ry += (-D_800CBB6E_main[0] / 30) * spd;
    if (ry >= 360.0f) {
        ry -= 360.0f;
    } else if (ry < 0.0f) {
        ry += 360.0f;
    }
    D_80107A50_mchar.y = ry;
    rx += (s8)(D_800D20A1_main[0] / 30) * spd;
    if (rx >= 360.0f) {
        rx -= 360.0f;
    } else if (rx < 0.0f) {
        rx += 360.0f;
    }
    D_80107A50_mchar.x = rx;
    CRot.x = (s16)rx;
    CRot.y = (s16)D_80107A50_mchar.y;
    if (D_800CDA7C_main[0] & 0x2000) {
        spd = 10.0f;
    } else {
        spd = 2.0f;
    }
    if (D_800CDA7C_main[0] & 0x800) {
        dx = sindf(ry) * sindf(rx);
        spd = -spd;
        Center.x += dx * spd;
        Center.y += cosdf(rx) * spd;
        Center.z += cosdf(ry) * sindf(rx) * spd;
    } else if (D_800CDA7C_main[0] & 0x400) {
        dx = sindf(ry) * sindf(rx);
        Center.x += dx * spd;
        Center.y += cosdf(rx) * spd;
        Center.z += cosdf(ry) * sindf(rx) * spd;
    } else if (D_800CDA7C_main[0] & 0x200) {
        dz = gCameraList->pos.z - Center.z;
        dx = -(gCameraList->pos.x - Center.x);
        inv = 1.0f / HuSqrtf(dz * dz + dx * dx);
        Center.x += dz * inv * spd;
        Center.y += 0.0f;
        Center.z += dx * inv * spd;
    } else if (D_800CDA7C_main[0] & 0x100) {
        dz = -(gCameraList->pos.z - Center.z);
        dx = gCameraList->pos.x - Center.x;
        inv = 1.0f / HuSqrtf(dz * dz + dx * dx);
        Center.x += dz * inv * spd;
        Center.y += 0.0f;
        Center.z += dx * inv * spd;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mchar/3D3C80", func_80106898_mchar);
#endif

void func_80106D7C_mchar(void) {
    D_80107A50_mchar.x = D_80107A50_mchar.y = D_80107A50_mchar.z = 0.0f;
    CRot.x = CRot.y = CRot.z = 0.0f;
    CZoom = 400.0f;
    Center.x = Center.z = 0.0f;
    Center.y = 64.0f;
    gCameraList->fov[0] = 45.0f;
}

void func_80106DF8_mchar(omObjData *obj) {
    if (D_80106E80_mchar != 0 || D_800D530C_main != 0) {
        WipeCreateOut(0, 8);
        obj->func = func_80106E54_mchar;
        HuAudSeqFadeOut(0x3C);
    }
}

void func_80106E54_mchar(omObjData *obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}
