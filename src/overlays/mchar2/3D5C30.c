#include "common.h"
#include "game/object.h"
#include "game/hmfman.h"
#include "math.h"
#include "game/pause.h"

/* Character motion viewer 2 (ovl_57, a debug overlay; mchar's twin): characters 6 and 7 (two model
   sets), six motions picked with the C buttons, the camera on the first controller. */

extern u16 omdispinfo;
extern s16 D_800A1786_main;
extern s32 fontcolor;
void func_80045C2C_main(void);
void func_8004DEC8_main(s16 arg0);
void* DataReadTemp(s32 dirAndFile);
void DataCloseTemp(void* data);
f32 func_8002FC7C_main(D_800CCF58_main_Struct *anim, u8 flags, f32 time, f32 end, f32 speed);

void func_80105B7C_mchar2(omObjData *obj);
void func_80105C90_mchar2(omObjData *obj);
void func_80106428_mchar2(s16 set);
void func_80106630_mchar2(s16 motion);
void func_801067C4_mchar2(omObjData *obj);
void func_80106CA8_mchar2(void);
void func_80106D24_mchar2(omObjData *obj);
void func_80106D80_mchar2(omObjData *obj);

/* .bss */
extern char D_80106F48_mchar2[0x100];    /* print buffer */
extern Vec D_80107048_mchar2;            /* camera rotation (D_8010704C_mchar2: its y) */
extern u8 D_80106EC0_mchar2;            /* number of motions in D_80106DC4_mchar2 */
extern s32 D_80106EC8_mchar2[8][2];      /* each character's two models */
/* a character's pair of model files, or of motions (current, previous) */
typedef struct MCharPair {
    /* 0x00 */ s32 a;
    /* 0x04 */ s32 b;
} MCharPair;
extern MCharPair D_80106F08_mchar2[8];   /* each character's motion: current, previous */

/* .data (0x3D7040) */
u16 D_80106DB0_mchar2 = 0;             /* quit */
u8 D_80106DB2_mchar2 = 1;              /* show the text */
s16 D_80106DB4_mchar2[8] = { 2, 3, 7, 4, 5, 6, 8, 9 }; /* voice set per character */
/* the motions offered (0x8000: play once), ended by 0xFFFF */
u16 D_80106DC4_mchar2[8] = { 0, 1, 2, 3, 0x802F, 0x8036, 0xFFFF, 0 };
char *D_80106DD4_mchar2[6] = { "C000_000", "C000_001", "C000_003", "C000_004", "C000_400", "C000_407" };
s16 D_80106DEC_mchar2 = 0;             /* character */
s16 D_80106DEE_mchar2 = 0;             /* index into D_80106DC4_mchar2 */
s16 D_80106DF0_mchar2 = 1;             /* which of the two models */
s16 D_80106DF2_mchar2 = 0;
u8 D_80106DF4_mchar2 = 0;
u8 D_80106DF5_mchar2 = 0;              /* frames until the models are reloaded */
MCharPair D_80106DF8_mchar2[2] = { { 0x000800A2, 0x000800A0 }, { 0x00090003, 0x00090000 } };

void func_801059A0_mchar2(void) {
    s16 i;

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
    omAddObj(0x2710, 0, 0, -1, func_80106D24_mchar2);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, -100.0f, 100.0f, 100.0f);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    func_80106CA8_mchar2();
    omAddObj(0x7D0, 0xA, 0xA, -1, func_80105B7C_mchar2);
    omAddObj(0x7D0, 0, 0, -1, func_801067C4_mchar2);
    WipeCreateIn(0, 0x10);
    D_800CD280_main = 1;
    func_8001F38C_main(0xC0, 0xE0, 0xFF);
    for (i = 0; D_80106DC4_mchar2[i] != 0xFFFF; i++) {
    }
    D_80106EC0_mchar2 = i;
    func_80045C2C_main();
}

#ifdef NON_MATCHING
void func_80105B7C_mchar2(omObjData *obj) {
    s16 i;

    obj->model[0] = -1;
    for (i = 0; i < 8; i++) {
        D_80106F08_mchar2[i].b = -1;
        D_80106F08_mchar2[i].a = -1;
        D_80106EC8_mchar2[i][1] = -1;
        D_80106EC8_mchar2[i][0] = -1;
    }
    D_80106DF2_mchar2 = 0;
    func_80106428_mchar2(0);
    func_8001C258_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 4, 0);
    func_8001C814_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 2, 2);
    obj->func = func_80105C90_mchar2;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_80105B7C_mchar2);
#endif

/* per frame: C up/down pick the motion (and play the character's voice for it), R swaps the two models
   (keeping the motion time), D-pad left/right the character, pad 2 L/R step the motion, both C left and
   right quit; pad 2 START toggles the text */
void func_80105C90_mchar2(omObjData *obj) {
    HmfModel *src;
    HmfModel *dst;

    if (D_80106DF5_mchar2 != 0) {
        D_80106DF5_mchar2--;
        if (D_80106DF5_mchar2 == 0) {
            func_80106428_mchar2(D_80106DF2_mchar2);
            func_8001C258_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 4, 0);
            func_8001C814_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 2, 2);
        }
    }
    if ((u16)D_800D0590_main[0] & 0x8000) {
        if (D_80106DC4_mchar2[++D_80106DEE_mchar2] == 0xFFFF) {
            D_80106DEE_mchar2 = 0;
        }
        func_80106630_mchar2(D_80106DC4_mchar2[D_80106DEE_mchar2]);
    }
    if ((u16)D_800D0590_main[0] & 0x4000) {
        if (--D_80106DEE_mchar2 < 0) {
            D_80106DEE_mchar2 = D_80106EC0_mchar2 - 1;
        }
        func_80106630_mchar2(D_80106DC4_mchar2[D_80106DEE_mchar2]);
    }
    if (D_800D5558_main[0] & 0x1000) {
        D_80106DF4_mchar2++;
    }
    if (D_800D5558_main[0] & 2) {
        func_8001C258_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 4, 4);
        if (++D_80106DEC_mchar2 >= 2) {
            D_80106DEC_mchar2 = 0;
        }
        func_8001C258_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 4, 0);
        func_8001F304_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], D_80106F08_mchar2[D_80106DEC_mchar2].a);
        func_8001C814_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 2, 2);
        func_80045ED0_main((D_80106DB4_mchar2[D_80106DEC_mchar2] << 16) | D_80106DEE_mchar2);
    }
    if (D_800D5558_main[0] & 1) {
        func_8001C258_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 4, 4);
        if (--D_80106DEC_mchar2 < 0) {
            D_80106DEC_mchar2 = 1;
        }
        func_8001C258_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 4, 0);
        func_8001F304_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], D_80106F08_mchar2[D_80106DEC_mchar2].a);
        func_8001C814_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 2, 2);
        func_80045ED0_main((D_80106DB4_mchar2[D_80106DEC_mchar2] << 16) | D_80106DEE_mchar2);
    }
    if ((u16)D_800D0590_main[1] & 0xC000) {
        src = &HmfModelData[D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2]];
        if ((u16)D_800D0590_main[1] & 0x4000) {
            src->unk03 |= 4;
        }
        src->unk03 &= ~1;
        src->unk40 = func_8002FC7C_main(&D_800CCF58_main[src->unk02], src->unk03, src->unk40, src->unk48,
                                          2.0f * src->unk44);
        if (src->unk04 != 0xFF) {
            src->unk4C = func_8002FC7C_main(&D_800CCF58_main[src->unk04], src->unk05, src->unk4C, src->unk54,
                                              2.0f * src->unk50);
        }
        src->unk03 = (src->unk03 & ~4) | 1;
    }
    if ((D_800CDA7C_main[0] & 0x30) == 0x30) {
        D_80106DB0_mchar2 = 1;
    }
    if (D_800D5558_main[1] & 0x1000) {
        D_80106DB2_mchar2 = D_80106DB2_mchar2 == 0;
    }
    if (D_80106DB2_mchar2 != 0) {
        src = &HmfModelData[D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2]];
        fontcolor = 9;
        sprintf(D_80106F48_mchar2, "MOTIONNO.%3d <%s>", D_80106DEE_mchar2, D_80106DD4_mchar2[D_80106DEE_mchar2]);
        print8(0x18, 0xB6, D_80106F48_mchar2);
        sprintf(D_80106F48_mchar2, "CENTER:%3.3f,%3.3f,%3.3f", Center.x, Center.y, Center.z);
        print8(0x18, 0xBE, D_80106F48_mchar2);
        sprintf(D_80106F48_mchar2, "ROTATE:%3.3f,%3.3f,%3.3f", CRot.x, CRot.y, CRot.z);
        print8(0x18, 0xC6, D_80106F48_mchar2);
        sprintf(D_80106F48_mchar2, "ZOOM:  %3.3f", CZoom);
        print8(0x18, 0xCE, D_80106F48_mchar2);
        sprintf(D_80106F48_mchar2, "M_TIME:%d", (u16)src->unk40);
        print8(0x18, 0xD6, D_80106F48_mchar2);
    }
}

/* loads characters 6 and 7's two models and their motion 0 (set is unused) */
#ifdef NON_MATCHING
void func_80106428_mchar2(s16 set) {
    s16 i;
    s16 chr;
    void *data;

    for (i = 0; i < 2; i++) {
        D_80106EC8_mchar2[i][0] = func_8000B108_main(D_80106DF8_mchar2[i].a, 0x2AC);
        chr = i + 6;
        func_80017790_main(D_80106EC8_mchar2[i][0], 0, chr, func_80017BB8_main(chr, 0xA3));
        func_8001C514_main(D_80106EC8_mchar2[i][0]);
        D_80106EC8_mchar2[i][1] = func_8000B108_main(D_80106DF8_mchar2[i].b, 0x2AC);
        func_80017790_main(D_80106EC8_mchar2[i][1], 1, chr, func_80017BB8_main(chr, 0xA4));
        func_8001C514_main(D_80106EC8_mchar2[i][1]);
        if (D_80106F08_mchar2[i].a != -1) {
            func_8002D4B8_main(D_80106F08_mchar2[i].a);
        }
        if (D_80106F08_mchar2[i].b != -1) {
            func_8002D4B8_main(D_80106F08_mchar2[i].b);
        }
        data = DataReadTemp(func_80017BB8_main(i + 6, 0));
        D_80106F08_mchar2[i].a = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
        D_80106F08_mchar2[i].b = -1;
        func_8001F304_main(D_80106EC8_mchar2[i][0], D_80106F08_mchar2[i].a);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_80106428_mchar2);
#endif

/* loads motion `motion` (0x8000: play once) for both characters (the previous one is kept until the next load) */
void func_80106630_mchar2(s16 motion) {
    s16 i;
    void *data;

    for (i = 0; i < 2; i++) {
        if (D_80106F08_mchar2[i].b != -1) {
            func_8002D4B8_main(D_80106F08_mchar2[i].b);
        }
        D_80106F08_mchar2[i].b = D_80106F08_mchar2[i].a;
        data = DataReadTemp(func_80017BB8_main(i + 6, motion & 0x7FFF));
        D_80106F08_mchar2[i].a = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
    }
    if (motion & 0x8000) {
        func_8001C624_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], D_80106F08_mchar2[D_80106DEC_mchar2].a, 0,
                           0xA, 0);
    } else {
        func_8001C624_main(D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], D_80106F08_mchar2[D_80106DEC_mchar2].a, 0,
                           0xA, 2);
    }
}

// masked 37: as mgenter func_80108A60_mgenter, retail addresses Center through a base register (one more $f register here)
/* debug camera on the first controller (as mgenter's func_80108A60_mgenter): L resets it, C up/down zoom,
   the stick turns, the D-pad moves the target; Z with it goes faster */
#ifdef NON_MATCHING
void func_801067C4_mchar2(omObjData *obj) {
    f32 rx;
    f32 ry;
    f32 spd;
    f32 dx;
    f32 dz;
    f32 inv;

    if (D_800CDA7C_main[0] & 0x1000) {
        func_80106CA8_mchar2();
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
    rx = D_80107048_mchar2.x;
    ry = D_80107048_mchar2.y;
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
    D_80107048_mchar2.y = ry;
    rx += (s8)(D_800D20A1_main[0] / 30) * spd;
    if (rx >= 360.0f) {
        rx -= 360.0f;
    } else if (rx < 0.0f) {
        rx += 360.0f;
    }
    D_80107048_mchar2.x = rx;
    CRot.x = (s16)rx;
    CRot.y = (s16)D_80107048_mchar2.y;
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
INCLUDE_ASM("asm/nonmatchings/overlays/mchar2/3D5C30", func_801067C4_mchar2);
#endif

void func_80106CA8_mchar2(void) {
    D_80107048_mchar2.x = D_80107048_mchar2.y = D_80107048_mchar2.z = 0.0f;
    CRot.x = CRot.y = CRot.z = 0.0f;
    CZoom = 400.0f;
    Center.x = Center.z = 0.0f;
    Center.y = 64.0f;
    gCameraList->fov[0] = 45.0f;
}

void func_80106D24_mchar2(omObjData *obj) {
    if (D_80106DB0_mchar2 != 0 || D_800D530C_main != 0) {
        WipeCreateOut(0, 8);
        obj->func = func_80106D80_mchar2;
        HuAudSeqFadeOut(0x3C);
    }
}

void func_80106D80_mchar2(omObjData *obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}
