#include "common.h"
#include "../ovl_81_name/ovl_81.h"

/* Overlay 0x7D `storyresult`: the story mode results screen. Same framework as msetup (501C00.c). */

/* Model definition table entry (0x28 stride; msetup's MsModelDef). */
typedef struct SrModelDef {
    /* 0x00 */ s32 unk0; /* func_8000B108_main arg0 */
    /* 0x04 */ s32 unk4; /* func_8000B108_main arg1 */
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA; /* func_8001C814_main arg2 */
    /* 0x0C */ s32 unkC; /* 0: none, 1: pos/rot, 2: pos*5 / rot */
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
} SrModelDef; /* size = 0x28 */

typedef struct SrModelSlot {
    /* 0x00 */ s16 model;
    /* 0x02 */ s16 unk2; /* HmfModelData[model].unk02 */
} SrModelSlot; /* size = 0x4 */

/* Camera key (msetup's MsCamKey). */
typedef struct SrCamKey {
    /* 0x00 */ Vec rot;    /* CRot */
    /* 0x0C */ Vec center; /* Center */
    /* 0x18 */ f32 zoom;   /* CZoom */
    /* 0x1C */ f32 fov;
    /* 0x20 */ f32 unk20;
} SrCamKey; /* size = 0x24 */

typedef void (*SrCamFunc)(s16, s16, s16);

void func_80105C30_storyresult(omObjData *obj);
void func_80105CF8_storyresult(omObjData *obj);
void func_80105DEC_storyresult(SrModelDef *def, s16 model);
void func_80105EA0_storyresult(SrModelDef *defs, SrModelSlot *slots, s32 count);
u32 func_80105F7C_storyresult(u32 seed);
u32 func_80106050_storyresult(void);
u32 func_80106078_storyresult(u32 max);
void func_80106190_storyresult(void);
void func_80106754_storyresult(void);
void func_80106780_storyresult(SrCamKey *keys, f32 speed, SrCamFunc func);
void func_80106C84_storyresult(void);
s16 func_80106E48_storyresult(void);
void func_80107204_storyresult(void);
void func_8010822C_storyresult(void);
void func_801083A4_storyresult(void);
void func_800E989C_minigame(void);
f32 func_80018ACC_main(f32 *y, f32 *x, f32 t);

extern u16 omovlstat;
extern f32 D_800CB890_main;
extern f32 D_800CE17C_main[];
extern f32 D_800D5210_main;
extern f32 D_8010A918_storyresult; /* current fov */
extern s8 D_8010A91C_storyresult;  /* fixed camera */
extern u32 D_8010A920_storyresult; /* random seed */
extern s16 D_8010ABE2_storyresult; /* exit mode */
extern Vec D_8010AC00_storyresult; /* fixed camera target */
extern Vec D_8010AC0C_storyresult; /* CRot copy; splat also labels .y/.z */
extern f32 D_8010AC10_storyresult;
extern f32 D_8010AC14_storyresult;
extern Vec D_8010AC18_storyresult; /* fixed camera eye */
extern f32 D_8010AC24_storyresult; /* near plane */
extern f32 D_8010AC2C_storyresult; /* far plane */
extern s16 D_8010AC30_storyresult; /* next overlay event */
extern s16 D_8010ABE0_storyresult; /* first controller (D_8010ABE8_storyresult.pad[0]) */

/* .bss 0x8010ABE8 (0x18): controller order; splat also labels D_8010ABEC/F0/F4/FA. */
typedef struct SrPadWork {
    /* 0x00 */ u8 pad[4];  /* connected controllers first, 0xFF-filled by the free ports */
    /* 0x04 */ u8 unk4[4];
    /* 0x08 */ u8 unk8[4];
    /* 0x0C */ u8 unkC[4];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;   /* connected controller count */
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
} SrPadWork; /* size = 0x18 */
extern SrPadWork D_8010ABE8_storyresult;
extern u8 D_8010A924_storyresult[]; /* per GwStory.unk0 (chapter): 0 party board, 1 duel board, 2 two-player game, other none */
extern s16 kakusiMasuItemHis[];
extern u8 D_800CE20A_main;
extern s16 D_800EBAF0_minigame;
s32 func_80050614_main(s32 write);
s16 func_80106FF0_storyresult(void);
void func_80107030_storyresult(void);
s16 func_801070D8_storyresult(void);
void func_80107140_storyresult(void);
void func_80107920_storyresult(void);
Process *func_8010818C_storyresult(s16 *res, s16 slot);
s16 func_8010A370_storyresult(s16 slot);
extern s16 D_8010AC32_storyresult; /* next overlay */

void func_801060D0_storyresult(SrCamKey *key);
extern u16 D_8010A910_storyresult; /* exit delay */
extern s16 D_8010A912_storyresult;
extern s16 D_8010A914_storyresult;
extern SrCamKey D_8010AB9C_storyresult[];
extern s16 D_8010AC28_storyresult;
extern s16 D_8010AC2A_storyresult;

/*<func_801059A0_storyresult>*/
void func_801059A0_storyresult(void) {
    omInitObjMan(0x33, 0x19);
    switch (omovlevtno) {
    case 0:
        if (func_80106E48_storyresult() == 0) {
            return;
        }
        break;
    case 2:
        func_800E989C_minigame();
        return;
    }
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    func_8005A6B0_main();
    D_800CD280_main = 0;
    D_8010AC24_storyresult = 80.0f;
    D_8010AC2C_storyresult = 6000.0f;
    D_8010A918_storyresult = 58.0f;
    Hu3DCamSetPerspective(0, 58.0f, 80.0f, 6000.0f);
    D_8010AC0C_storyresult.x = 0.0f;
    D_8010AC0C_storyresult.y = 0.0f;
    D_8010AC0C_storyresult.z = 0.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    func_80106190_storyresult();
    omAddObj(0x2710, 0, 0, -1, func_80105C30_storyresult);
    HmfLightMaxSet(3);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightDirSet(2, 0.0f, 0.0f, 100.0f);
    HmfLightColorSet(3, 0xF0, 0xF0, 0xF0);
    HmfLightDirSet(3, 0.0f, 100.0f, 0.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_8001F38C_main(0x10, 0x10, 0xF0);
    omPrcSetStatBit(omAddPrcObj(func_80106754_storyresult, 0x1100, 0x400, 0), 0xA0);
    D_8010ABE2_storyresult = 0;
    func_80106C84_storyresult();
    switch (omovlevtno) {
    case 0:
        if (omovlstat & 0x4000) {
            omAddPrcObj(func_80107204_storyresult, 0x3F00, 0x1000, 0);
        }
        break;
    case 1:
        omAddPrcObj(func_8010822C_storyresult, 0x3F00, 0x1000, 0);
        break;
    case 2:
        break;
    case 3:
        omAddPrcObj(func_801083A4_storyresult, 0x3F00, 0x1000, 0);
        break;
    }
    WipeColorSet(0, 0, 0);
    D_8010AC2A_storyresult = 2;
    D_8010AC28_storyresult = 0x14;
}
/*</func_801059A0_storyresult>*/

/*<func_80105C30_storyresult>*/
void func_80105C30_storyresult(omObjData *obj) {
    if (D_8010A910_storyresult == 0) {
        if (D_800D530C_main != 0) {
            goto out;
        }
    } else {
        if (D_8010A910_storyresult != 1) {
            D_8010A910_storyresult--;
            return;
        }
    out:
        if (D_8010AC2A_storyresult >= 0) {
            WipeCreateOut(D_8010AC2A_storyresult, D_8010AC28_storyresult);
        }
        switch (D_8010A914_storyresult) {
        case 1:
            HuAudSeqFadeOut(0x1E);
            break;
        case 2:
            HuAudSeqFadeOut(0x51);
            break;
        }
        obj->func = func_80105CF8_storyresult;
    }
}
/*</func_80105C30_storyresult>*/

/*<func_80105CF8_storyresult>*/
void func_80105CF8_storyresult(omObjData *obj) {
    s32 stat;

    if (WipeStatGet() == 0) {
        if (D_8010A912_storyresult != 0) {
            MBDBackKill();
            MBDBackClose();
        }
        func_8005F524_main();
        stat = 0x14;
        switch (D_8010ABE2_storyresult) {
        case 0:
        default:
            omOvlReturnEx(1);
            break;
        case 2:
            omOvlCallEx(D_8010AC32_storyresult, D_8010AC30_storyresult, stat);
            break;
        case 1:
            omOvlGotoEx(D_8010AC32_storyresult, D_8010AC30_storyresult, stat);
            break;
        case 3:
            stat = 0x4090;
            omOvlGotoEx(D_8010AC32_storyresult, D_8010AC30_storyresult, stat);
            break;
        case 4:
            stat = 0x92;
            omOvlGotoEx(D_8010AC32_storyresult, D_8010AC30_storyresult, stat);
            break;
        }
    }
}
/*</func_80105CF8_storyresult>*/

/*<func_80105DEC_storyresult>*/
void func_80105DEC_storyresult(SrModelDef *def, s16 model) {
    switch ((u32)def->unkC) {
    case 1:
        Hu3DModelPosSet(model, def->pos.x, def->pos.y, def->pos.z);
        Hu3DModelRotSet(model, def->rot.x, def->rot.y, def->rot.z);
        break;
    case 0:
        break;
    case 2:
        Hu3DModelPosSet(model, def->pos.x * 5.0f, def->pos.y * 5.0f, def->pos.z * 5.0f);
        Hu3DModelRotSet(model, def->rot.x, def->rot.y, def->rot.z);
        break;
    }
}
/*</func_80105DEC_storyresult>*/

/*<func_80105EA0_storyresult>*/
void func_80105EA0_storyresult(SrModelDef *defs, SrModelSlot *slots, s32 count) {
    s16 i;
    u16 model;

    if (defs == NULL || slots == NULL) {
        return;
    }
    for (i = 0; i < count; defs++, i++, slots++) {
        model = func_8000B108_main(defs->unk0, defs->unk4);
        slots->model = model;
        func_80105DEC_storyresult(defs, model);
        slots->unk2 = HmfModelData[(s16)model].unk02;
        if (slots->unk2 >= 0) {
            func_8001C814_main(model, -1, defs->unkA);
        }
    }
}
/*</func_80105EA0_storyresult>*/

/*<func_80105F7C_storyresult>*/
u32 func_80105F7C_storyresult(u32 seed) {
    s32 hi, lo;

    if (seed == 0) {
        seed = rand8();
        seed = seed ^ osGetCount();
        seed ^= 0xD826BC89;
    }
    hi = seed / 0x1F31D;
    lo = seed - (hi * 0x1F31D);
    seed = hi * 0xB14;
    seed = seed - lo * 0x41A7;
    return seed;
}
/*</func_80105F7C_storyresult>*/

/*<func_80106050_storyresult>*/
u32 func_80106050_storyresult(void) {
    return D_8010A920_storyresult = func_80105F7C_storyresult(D_8010A920_storyresult);
}
/*</func_80106050_storyresult>*/

/*<func_80106078_storyresult>*/
u32 func_80106078_storyresult(u32 max) {
    return ((D_8010A920_storyresult = func_80105F7C_storyresult(D_8010A920_storyresult)) & 0x7FFFFFFF) % max;
}
/*</func_80106078_storyresult>*/

/*<func_801060D0_storyresult>*/
void func_801060D0_storyresult(SrCamKey *key) {
    f32 fov;

    CRot = key->rot;
    D_8010AC0C_storyresult = CRot;
    Center = key->center;
    CZoom = key->zoom;
    fov = key->fov;
    if (fov != D_8010A918_storyresult) {
        D_8010A918_storyresult = fov;
        Hu3DCamSetPerspective(0, fov, D_8010AC24_storyresult, D_8010AC2C_storyresult);
    }
}
/*</func_801060D0_storyresult>*/

/*<func_80106190_storyresult>*/
/* msetup func_80106320_msetup without its loop; the camera process func_80106754_storyresult calls it. */
#ifdef NON_MATCHING
/* Residue (masked 11): retail schedules the &Center load before the first mul.s, and f2/f12 swap in the distance sum (as msetup func_801068F4_msetup). */
void func_80106190_storyresult(void) {
    Vec pos;
    Vec at;
    Vec up;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 ux;
    f32 uy;
    f32 uz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;

    if (D_8010A91C_storyresult == 0) {
        rx = CRot.x;
        ry = CRot.y;
        rz = CRot.z;
        pos.x = sindf(ry) * cosdf(rx) * CZoom + Center.x;
        pos.y = -sindf(rx) * CZoom + Center.y;
        pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
        at.x = Center.x;
        at.y = Center.y;
        at.z = Center.z;
        ux = sindf(ry) * sindf(rx);
        uy = cosdf(rx);
        uz = cosdf(ry) * sindf(rx);
        dx = at.x - pos.x;
        dy = at.y - pos.y;
        dz = at.z - pos.z;
        len = HuSqrtf(dx * dx + dy * dy + dz * dz);
        dx /= len;
        dy /= len;
        dz /= len;
        up.x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz))
             + uy * (dx * dy * (1.0f - cosdf(rz)) - dz * sindf(rz))
             + uz * (dx * dz * (1.0f - cosdf(rz)) + dy * sindf(rz));
        up.y = ux * (dx * dy * (1.0f - cosdf(rz)) + dz * sindf(rz))
             + uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz))
             + uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
        up.z = ux * (dx * dz * (1.0f - cosdf(rz)) - dy * sindf(rz))
             + uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz))
             + uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
    } else {
        pos = D_8010AC18_storyresult;
        at = D_8010AC00_storyresult;
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
    }
    D_800CE17C_main[0] = pos.x;
    D_800CE17C_main[1] = pos.z;
    D_800CE17C_main[-1] = CRot.y;
    D_800CE17C_main[2] = gCameraList->fov[0];
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54DD10", func_80106190_storyresult);
#endif
/*</func_80106190_storyresult>*/

/*<func_80106754_storyresult>*/
void func_80106754_storyresult(void) {
    while (1) {
        func_80106190_storyresult();
        HuPrcVSleep();
    }
}
/*</func_80106754_storyresult>*/

/*<func_80106780_storyresult>*/
#ifdef NON_MATCHING
/* Residue: two hazard nops after cosdf() (W2DC_BLANKSTRIP) and f2/f12 swapped in the distance sum. */
void func_80106780_storyresult(SrCamKey *keys, f32 speed, SrCamFunc func) {
    f32 out[10];
    f32 y[4];
    f32 x[4];
    SrCamFunc fn;
    SrCamKey *cur;
    f32 *p0;
    f32 *p1;
    f32 *p2;
    f32 *p3;
    f32 *o;
    f32 total;
    f32 d;
    f32 px, py, pz;
    f32 dz, dy, dx;
    f32 lx, ly, lz;
    s16 i;
    s16 seg;
    s16 j;

    fn = func;
    lz = 0.0f;
    ly = 0.0f;
    lx = 0.0f;
    total = 0.0f;
    cur = keys;
    for (i = 0; cur->zoom != 0.0f; cur = &keys[++i]) {
        if (speed != 0.0f) {
            px = sindf(cur->rot.y) * cosdf(cur->rot.x) * cur->zoom + cur->center.x;
            py = -sindf(cur->rot.x) * cur->zoom + cur->center.y;
            pz = cosdf(cur->rot.y) * cosdf(cur->rot.x) * cur->zoom + cur->center.z;
            if (i > 0) {
                dx = lx - px;
                dy = ly - py;
                dz = lz - pz;
                d = dx * dx + dy * dy + dz * dz;
            d = HuSqrtf(d);
                if (d == 0.0f) {
                    d = speed * 10.0f;
                }
                total += d / speed;
                cur->unk20 = total;
            }
            lx = px;
            ly = py;
            lz = pz;
        } else {
            total = cur->unk20;
        }
    }
    total -= 10.0f;
    for (i = 10, seg = 1; i < total; i++) {
        if (i > keys[seg + 1].unk20) {
            seg++;
        }
        x[0] = keys[seg - 1].unk20;
        x[1] = keys[seg].unk20;
        x[2] = keys[seg + 1].unk20;
        x[3] = keys[seg + 2].unk20;
        p0 = &keys[seg - 1].rot.x;
        p1 = &keys[seg].rot.x;
        p2 = &keys[seg + 1].rot.x;
        p3 = &keys[seg + 2].rot.x;
        o = out;
        for (j = 0; j < 8; j++) {
            y[0] = *p0++;
            y[1] = *p1++;
            y[2] = *p2++;
            y[3] = *p3++;
            *o++ = func_80018ACC_main(y, x, i);
        }
        Center.x = out[3];
        Center.y = out[4];
        Center.z = out[5];
        D_8010AC0C_storyresult.x = CRot.x = out[0];
        D_8010AC10_storyresult = CRot.y = out[1];
        D_8010AC14_storyresult = CRot.z = out[2];
        CZoom = out[6];
        gCameraList->fov[0] = D_8010A918_storyresult = out[7];
        if (func != NULL) {
            fn((s16)total, seg, i);
        }
        HuPrcVSleep();
    }
    i = seg + 1;
    D_8010AC0C_storyresult.x = CRot.x = keys[i].rot.x;
    D_8010AC0C_storyresult.y = CRot.y = keys[i].rot.y;
    D_8010AC0C_storyresult.z = CRot.z = keys[i].rot.z;
    CZoom = keys[i].zoom;
    Center.x = keys[i].center.x;
    Center.y = keys[i].center.y;
    Center.z = keys[i].center.z;
    gCameraList->fov[0] = D_8010A918_storyresult = keys[i].fov;
    D_800CB99C_main = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54DD10", func_80106780_storyresult);
#endif
/*</func_80106780_storyresult>*/

/*<func_80106C84_storyresult>*/
void func_80106C84_storyresult(void) {
    s16 i;
    s16 n;
    s16 j;
    s16 k;

    for (i = 0; i < 4; i++) {
        D_8010ABE8_storyresult.pad[i] = 0xFF;
        D_8010ABE8_storyresult.unk4[i] = i;
        D_8010ABE8_storyresult.unk8[i] = 0xFF;
        D_8010ABE8_storyresult.unkC[i] = 0;
    }
    for (i = 0, n = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            D_8010ABE8_storyresult.pad[n] = i;
            n++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_8010ABE8_storyresult.pad[i] == 0xFF) {
            for (j = 0; j < 4; j++) {
                for (k = 0; k < 4; k++) {
                    if (D_8010ABE8_storyresult.pad[k] == j) {
                        break;
                    }
                }
                if (k == 4) {
                    break;
                }
            }
            D_8010ABE8_storyresult.pad[i] = j;
        }
    }
    D_8010ABE8_storyresult.unk12 = 0;
    D_8010ABE8_storyresult.unk16 = 0;
    D_8010ABE8_storyresult.unk13 = 0;
    D_8010ABE8_storyresult.unk14 = n;
    D_8010ABE8_storyresult.unk10 = 0;
    D_8010ABE8_storyresult.unk11 = 4;
    D_8010ABE8_storyresult.unk15 = 0;
    D_8010ABE0_storyresult = D_8010ABE8_storyresult.pad[0];
}
/*</func_80106C84_storyresult>*/

/*<func_80106E48_storyresult>*/
/* Whether the story results run (0: go to overlay 0x75 instead). */
s16 func_80106E48_storyresult(void) {
    s16 ret;
    u16 who;
    s16 i;

    ret = 0;
    switch (D_8010A924_storyresult[GwStory.unk0]) {
    case 0:
        who = kakusiMasuItemHis[0];
    check:
        if (who < 6) {
            if (GwStory.unk1 == GwPlayer[(s16)who].chr) {
                ret++;
            }
        }
        break;
    case 1:
        if (kakusiMasuItemHis[2] != 0) {
            break;
        }
        who = kakusiMasuItemHis[0];
        goto check;
    case 2:
        for (i = 0; i < 2; i++) {
            if (GwPlayer[i].chr == GwStory.unk1) {
                break;
            }
        }
        if (i < 2 && GwPlayer[i].bonusCoin >= 0) {
            ret++;
        }
        break;
    default:
        ret++;
        break;
    }
    if (ret == 0) {
        D_8010ABE2_storyresult = 1;
        D_8010AC32_storyresult = 0x75;
        D_8010AC30_storyresult = 0;
        D_800CE20A_main = 0xF;
        omOvlGotoEx(0x75, 0, 0x14);
    }
    return ret;
}
/*</func_80106E48_storyresult>*/

