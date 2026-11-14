#include "common.h"
#include "msetup.h"

#include "game/vibrator.h"

f32 func_80018ACC_main(f32 *y, f32 *x, f32 t);
extern f32 D_8011A998_msetup; /* D_8011A994_msetup.y */
extern f32 D_8011A99C_msetup; /* D_8011A994_msetup.z */


extern f32 D_800CB890_main;
extern f32 D_800CE17C_main[];
extern f32 D_800D5210_main;
extern Vec D_8011A920_msetup; /* fixed camera target */
extern Vec D_8011A92C_msetup; /* fixed camera eye */

extern process_func D_8011955C_msetup[];
extern s16 D_8011A950_msetup[];
extern s16 D_8011A9A0_msetup[];


void func_801059A0_msetup(void) {
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0x19);
    func_8005A6B0_main();
    func_8004A208_main();
    D_800CD280_main = 1;
    D_8011A940_msetup = 80.0f;
    D_8011A93C_msetup = 6000.0f;
    D_80119414_msetup = 58.0f;
    Hu3DCamSetPerspective(0, 58.0f, 80.0f, 6000.0f);
    D_8011A994_msetup.x = 0.0f;
    D_8011A994_msetup.y = 0.0f;
    D_8011A994_msetup.z = 0.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    D_801198C0_msetup = -1;
    omAddObj(0x2710, 0, 0, -1, func_80105C4C_msetup);
    HmfLightMaxSet(3);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightDirSet(2, 0.0f, 0.0f, 100.0f);
    HmfLightColorSet(3, 0xF0, 0xF0, 0xF0);
    HmfLightDirSet(3, 0.0f, 100.0f, 0.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_8001F38C_main(0x10, 0x10, 0xF0);
    omPrcSetStatBit(omAddPrcObj(func_80106320_msetup, 0x1100, 0x400, 0), 0xA0);
    D_8011A944_msetup = 0;
    func_80106DF8_msetup();
    D_8011A938_msetup = -1;
    switch (omovlevtno) {
        case 0:
            D_8011A938_msetup = 0;
            break;
        case 1:
            D_8011A938_msetup = 1;
            break;
        case 2:
            D_8011A938_msetup = 2;
            break;
        case 3:
            D_8011A938_msetup = 3;
            break;
        case 4:
            D_8011A938_msetup = 4;
            break;
        case 5:
            D_8011A938_msetup = 5;
            break;
        case 6:
            D_8011A938_msetup = 6;
            break;
        case 7:
            D_8011A938_msetup = 7;
            break;
        case 8:
            D_8011A938_msetup = 8;
            break;
    }
    if (D_8011A938_msetup < 0) {
        D_80119410_msetup = 1;
    } else {
        omAddPrcObj(D_8011955C_msetup[D_8011A938_msetup], 0x3F00, 0x1000, 0);
    }
    if (D_8011A938_msetup == 4) {
        WipeColorSet(0xFF, 0xFF, 0xFF);
    } else {
        WipeColorSet(0, 0, 0);
    }
    D_8011AA48_msetup = 0xB;
    D_8011A93A_msetup = 0x14;
}

#ifdef NON_MATCHING
/* D_8011AA48_msetup: retail stores it and reloads it (lh) before the >= 0 test; this keeps the register. */
void func_80105C4C_msetup(omObjData *obj) {
    s32 i;
    s32 wipe;

    if (D_80119412_msetup != 0) {
        D_80119419_msetup--;
        if (D_80119419_msetup == 0) {
            for (i = 0; i < D_8011AA40_msetup; i++) {
                RepeatVibrator(D_8011AA30_msetup[i], 5, 0, 5);
            }
            D_80119419_msetup = 10;
        }
    }
    if (D_80119410_msetup == 0) {
        if (D_800D530C_main != 0) {
            goto out;
        }
    } else {
        if (D_80119410_msetup != 1) {
            D_80119410_msetup--;
            return;
        }
    out:
        wipe = 2;
        if (D_8011A938_msetup == 4) {
            WipeColorSet(0xFF, 0xFF, 0xFF);
            wipe = 0xB;
        }
        D_8011AA48_msetup = wipe;
        if (D_8011AA48_msetup >= 0) {
            WipeCreateOut(D_8011AA48_msetup, D_8011A93A_msetup);
        }
        if (D_8011A944_msetup == 0) {
            HuAudSeqFadeOut(0xF);
        }
        obj->func = func_80105DB4_msetup;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80105C4C_msetup);
#endif

void func_80105DB4_msetup(omObjData *obj) {
    s32 stat;

    if (WipeStatGet() == 0) {
        func_8005F524_main();
        func_8010ACB0_msetup();
        stat = 0x14;
        switch (D_8011A944_msetup) {
            case 0:
            default:
                omOvlReturnEx(1);
                break;
            case 2:
                omOvlCallEx(D_8011AA4C_msetup[0], D_8011A946_msetup, stat);
                break;
            case 1:
                omOvlGotoEx(D_8011AA4C_msetup[0], D_8011A946_msetup, stat);
                break;
            case 3:
                stat = 0x4090;
                omOvlGotoEx(D_8011AA4C_msetup[0], D_8011A946_msetup, stat);
                break;
            case 4:
                stat = 0x92;
                omOvlGotoEx(D_8011AA4C_msetup[0], D_8011A946_msetup, stat);
                break;
        }
    }
}

void func_80105E90_msetup(MsModelDef *def) {
    s16 i;
    u16 model;
    s16 slot;

    for (i = 0; def->unk0 != -1; i++, def++) {
        model = func_8000B108_main(def->unk0, def->unk4);
        D_8011A950_msetup[i] = model;
        func_80105F7C_msetup(def, model);
        D_8011A9A0_msetup[i] = slot = HmfModelData[(s16)model].unk02;
        if (slot != -1) {
            func_8001C814_main(model, -1, def->unkA);
        }
    }
}

void func_80105F7C_msetup(MsModelDef *def, s16 model) {
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

void func_80106030_msetup(MsModelDef *defs, MsModelSlot *slots, s32 count) {
    s16 i;
    u16 model;

    if (defs == NULL || slots == NULL) {
        return;
    }
    for (i = 0; i < count; defs++, i++, slots++) {
        model = func_8000B108_main(defs->unk0, defs->unk4);
        slots->model = model;
        func_80105F7C_msetup(defs, model);
        slots->unk2 = HmfModelData[(s16)model].unk02;
        if (slots->unk2 >= 0) {
            func_8001C814_main(model, -1, defs->unkA);
        }
    }
}

u32 func_8010610C_msetup(u32 seed) {
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

u32 func_801061E0_msetup(void) {
    return D_8011941C_msetup = func_8010610C_msetup(D_8011941C_msetup);
}

u32 func_80106208_msetup(u32 max) {
    return ((D_8011941C_msetup = func_8010610C_msetup(D_8011941C_msetup)) & 0x7FFFFFFF) % max;
}

void func_80106260_msetup(MsCamKey *key) {
    f32 fov;

    CRot = key->rot;
    D_8011A994_msetup = CRot;
    Center = key->center;
    CZoom = key->zoom;
    fov = key->fov;
    if (fov != D_80119414_msetup) {
        D_80119414_msetup = fov;
        Hu3DCamSetPerspective(0, fov, D_8011A940_msetup, D_8011A93C_msetup);
    }
}

/* The camera process (MP3 main's omOutView plus a roll; MP2 MinigameParkSetup's
   func_80111D8C): the eye orbits Center at CZoom with rotation CRot, the up vector turned by
   CRot.z about the line of sight; or, while D_80119418_msetup is set, the fixed eye and target
   D_8011A92C/D_8011A920 with up +y. */
#ifdef NON_MATCHING
/* Only residue: two hazard nops before the mul.s after cosdf(); matches with 501C00.c in W2DC_BLANKSTRIP (tested). */
void func_80106320_msetup(void) {
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

    while (1) {
        if (D_80119418_msetup == 0) {
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
            pos = D_8011A92C_msetup;
            at = D_8011A920_msetup;
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
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106320_msetup);
#endif

/* Flies the camera along a path of keys (ended by zoom 0) at speed units per frame (MP2
   name_4E's func_8010BCB8): each key's arrival time goes in unk20 (speed 0: the table's own
   times), then every frame takes a spline through four keys for each of the eight values. */
#ifdef NON_MATCHING
/* Residue: two hazard nops after cosdf() (W2DC_BLANKSTRIP) and f2/f12 swapped in the distance sum. */
void func_801068F4_msetup(MsCamKey *keys, f32 speed, MsCamFunc func) {
    f32 out[10];
    f32 y[4];
    f32 x[4];
    MsCamFunc fn;
    MsCamKey *cur;
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
        D_8011A994_msetup.x = CRot.x = out[0];
        D_8011A998_msetup = CRot.y = out[1];
        D_8011A99C_msetup = CRot.z = out[2];
        CZoom = out[6];
        gCameraList->fov[0] = D_80119414_msetup = out[7];
        if (func != NULL) {
            fn((s16)total, seg, i);
        }
        HuPrcVSleep();
    }
    i = seg + 1;
    D_8011A994_msetup.x = CRot.x = keys[i].rot.x;
    D_8011A994_msetup.y = CRot.y = keys[i].rot.y;
    D_8011A994_msetup.z = CRot.z = keys[i].rot.z;
    CZoom = keys[i].zoom;
    Center.x = keys[i].center.x;
    Center.y = keys[i].center.y;
    Center.z = keys[i].center.z;
    gCameraList->fov[0] = D_80119414_msetup = keys[i].fov;
    D_800CB99C_main = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801068F4_msetup);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106DF8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106FC0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801070FC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107428_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801077E0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107840_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107964_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107A58_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107B8C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107CF4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107D84_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107E48_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107ECC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107F88_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107FB4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108464_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801084C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801085D4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801086C8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801087F4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801088A8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108938_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801089FC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108AB8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108F74_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109218_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109868_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109EA0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109F04_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109F7C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A10C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A204_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A2B0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A35C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A780_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A7A0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A7EC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010AC78_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010AC94_msetup);

void func_8010ACB0_msetup(void) {
}
