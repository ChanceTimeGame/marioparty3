#include "common.h"
#include "msetup.h"
#include "mallocblock.h"

#include "game/vibrator.h"

extern u8 D_8011A949_msetup; /* low byte of D_8011A948_msetup (big-endian) */


/* omObjData::data of the func_80107428_msetup background object (HuMemAllocTag 0x88). */
typedef struct MsShaftWork {
    /* 0x00 */ f32 wallY[3];
    /* 0x0C */ f32 ringY[3];
    /* 0x18 */ f32 rotY;
    /* 0x1C */ Vec star[3];
    /* 0x40 */ Vec item[6];
} MsShaftWork; /* size = 0x88 */


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
                RepeatVibrator(D_8011AA30_msetup.pad[i], 5, 0, 5);
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

/* Resets the per-player setup (D_8011AA30_msetup .. D_8011AA47_msetup, one block): the pads
   plugged in go first, the other players take the free port numbers. */
void func_80106DF8_msetup(void) {
    s16 i;
    s16 j;
    s16 k;
    s16 n;

    for (i = 0; i < 4; i++) {
        D_8011AA30_msetup.pad[i] = 0xFF;
        D_8011AA34_msetup[i] = i;
        D_8011AA38_msetup[i] = 0xFF;
        D_8011AA3C_msetup[i] = 0;
    }
    for (i = 0, n = 0; i < 4; i++) {
        if (CheckControllerRead(i) != 0) {
            D_8011AA30_msetup.pad[n] = i;
            n++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_8011AA30_msetup.pad[i] == 0xFF) {
            for (k = 0; k < 4; k++) {
                for (j = 0; j < 4; j++) {
                    if (D_8011AA30_msetup.pad[j] == k) {
                        break;
                    }
                }
                if (j == 4) {
                    break;
                }
            }
            D_8011AA30_msetup.pad[i] = k;
        }
    }
    D_8011AA30_msetup.turns = 0;
    D_8011AA30_msetup.length = 0;
    D_8011AA30_msetup.unk13 = 0;
    D_8011AA30_msetup.unk14 = n;
    D_8011AA30_msetup.unk10 = 0;
    D_8011AA30_msetup.unk11 = 4;
    D_8011AA30_msetup.board = 0;
    D_8011AA30_msetup.unk17 = 0;
    D_8011A948_msetup = D_8011AA30_msetup.pad[0];
}

#ifdef NON_MATCHING
/* Only residue: hazard nops after cosdf()/sindf() (matches with W2DC_BLANKSTRIP). */
f32 func_80106FC0_msetup(Vec *pos, s32 mask, f32 radius) {
    f32 angle;
    u32 r;

    r = func_801061E0_msetup() & mask;
    pos->y -= r;
    r = func_801061E0_msetup() & 0x7FFFFFFF;
    if (D_8011AA4A_msetup != 0) {
        r = r % 120;
        r += 120;
    } else {
        r = r % 360;
    }
    angle = r;
    pos->x = radius * sindf(angle);
    pos->z = radius * cosdf(angle);
    return angle;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106FC0_msetup);
#endif

void func_801070FC_msetup(omObjData *obj) {
    MsShaftWork *work;
    s32 i;
    u16 model;
    f32 y;
    Vec *pos;

    work = obj->data;
    for (i = 0; i < 3; i++) {
        model = obj->model[i + 4];
        y = work->wallY[i];
        y += 100.0f;
        if (y >= 4000.0f) {
            y -= 12000.0f;
        }
        Hu3DModelPosSet(model, 0.0f, y, 0.0f);
        Hu3DModelRotSet(model, 0.0f, work->rotY, 0.0f);
        work->wallY[i] = y;
    }
    work->rotY += 2.0f;
    for (i = 0; i < 3; i++) {
        model = obj->model[i + 1];
        y = work->ringY[i];
        y += 60.0f;
        if (y >= 4000.0f) {
            y -= 12000.0f;
        }
        Hu3DModelPosSet(model, 0.0f, y, 0.0f);
        work->ringY[i] = y;
    }
    for (i = 0; i < 3; i++) {
        model = obj->model[i + 7];
        pos = &work->star[i];
        pos->y += 40.0f;
        if (pos->y > 1000.0f) {
            pos->y -= 12000.0f;
            func_80106FC0_msetup(pos, 0xFFF, 900.00006f);
        }
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    }
    for (i = 0; i < 6; i++) {
        model = obj->model[i + 10];
        pos = &work->item[i];
        pos->y += 75.0f;
        if (pos->y > 1000.0f) {
            pos->y -= 12000.0f;
            y = func_80106FC0_msetup(pos, 0xFFF, 906.00006f);
            Hu3DModelRotSet(model, 0.0f, y - 180.0f, 0.0f);
        }
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    }
}

omObjData *func_80107428_msetup(void) {
    omObjData *obj;
    MsShaftWork *work;
    s32 i;
    s16 base;
    u16 model;
    f32 y;
    f32 angle;
    Vec *pos;

    D_8011AA4A_msetup = 0;
    D_80119430_msetup = obj = omAddObj(0x17D0, 0x10, 0, -1, func_801070FC_msetup);
    if (obj == NULL) {
        return NULL;
    }
    obj->model[0] = -1;
    work = HuMemAllocTag(sizeof(MsShaftWork), 0x7918);
    memset(work, 0, sizeof(MsShaftWork));
    obj->data = work;
    for (y = 0.0f, base = -1, i = 0; i < 3; i++, y -= 4000.0f) {
        if (base < 0) {
            base = model = func_8000B108_main(0x140000, 0x2B9);
        } else {
            model = Hu3DModelLink(base);
        }
        obj->model[i + 4] = model;
        Hu3DModelPosSet(model, 0.0f, y, 0.0f);
        Hu3DModelScaleSet(model, 1.2f, 2.0f, 1.2f);
        work->wallY[i] = y;
    }
    work->rotY = 0.0f;
    for (y = work->rotY, base = -1, i = 0; i < 3; i++, y -= 4000.0f) {
        if (base < 0) {
            base = model = func_8000B108_main(0x140004, 0x299);
        } else {
            model = Hu3DModelLink(base);
        }
        obj->model[i + 1] = model;
        Hu3DModelPosSet(model, 0.0f, y, 0.0f);
        Hu3DModelScaleSet(model, 1.2f, 2.0f, 1.2f);
        work->ringY[i] = y;
    }
    for (base = -1, i = 0; i < 3; i++) {
        if (base < 0) {
            base = model = func_8000B108_main(0x140002, 0x299);
        } else {
            model = Hu3DModelLink(base);
        }
        obj->model[i + 7] = model;
        pos = &work->star[i];
        pos->y = 0.0f;
        func_80106FC0_msetup(pos, 0x1FFF, 900.00006f);
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    }
    for (base = -1, i = 0; i < 6; i++) {
        if (base < 0) {
            base = model = func_8000B108_main(0x140005, 0x299);
        } else {
            model = Hu3DModelLink(base);
        }
        obj->model[i + 10] = model;
        pos = &work->item[i];
        pos->y = 0.0f;
        angle = func_80106FC0_msetup(pos, 0x1FFF, 906.00006f);
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
        Hu3DModelRotSet(model, 0.0f, angle - 180.0f, 0.0f);
    }
    return obj;
}


s16 func_801077E0_msetup(s32 arg0) {
    D_8011A882_msetup.state = 1;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_80107840_msetup(s32 arg0) {
    s32 i;

    D_8011A882_msetup.state = 2;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] != -1) {
        D_8011A990_msetup = 0;
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        func_8010BBF4_msetup(D_8011A880_msetup);
        for (i = 4; i != 0; i--) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x2DB);
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9F0_msetup[i].unk2 = 1;
        }
        while (D_8011AA2E_msetup != 0) {
            HuPrcVSleep();
        }
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_80107964_msetup(s32 arg0) {
    s32 i;

    if (D_8011AA41_msetup != 0) {
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9F0_msetup[i].unk2 = 7;
        }
        D_8011A882_msetup.state = 3;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
    } else {
        D_8011A990_msetup = 1;
    }
    if (D_8011A886_msetup[0] == -1) {
        HuAudFXPlay(0x2E4);
        func_8010BE8C_msetup(D_8011A880_msetup);
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_80107A58_msetup(s32 arg0) {
    s32 i;

    if (D_8011A886_msetup[0] < 0) {
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9F0_msetup[i].unk2 = 10;
        }
    }
    D_8011A882_msetup.state = 6;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] == 0) {
        D_8011A886_msetup[-2] = 4;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
        if (D_8011A886_msetup[0] < 0) {
            return arg0;
        }
        arg0++;
    } else {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011AA3C_msetup[i] = 0;
        }
        if (D_8011A886_msetup[0] < 0) {
            arg0--;
        } else {
            arg0++;
        }
    }
    return arg0;
}

s16 func_80107B8C_msetup(s32 arg0) {
    s32 i;

    for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
        D_8011A9F0_msetup[i].unk2 = 12;
    }
    D_8011A990_msetup = 2;
    HuPrcVSleep();
    func_8010B9B8_msetup(0x4000, 0x4000);
    D_8011A882_msetup.state = 8;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] < 0) {
        func_8010F2F4_msetup(D_80119420_msetup, 0xFF);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 1);
    }
    D_8011A990_msetup = 1;
    HuPrcVSleep();
    func_8010B9B8_msetup(0x4000, 0x4000);
    for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
        D_8011A9F0_msetup[i].unk2 = 11;
    }
    HuPrcVSleep();
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_80107CF4_msetup(s32 arg0) {
    D_8011A882_msetup.state = 5;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 3);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 4);
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_80107D84_msetup(s32 arg0) {
    s32 i;

    D_8011A882_msetup.state = 13;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] == 0) {
        D_8011AA47_msetup = 0;
    } else {
        D_8011AA47_msetup = 1;
    }
    if (D_8011A886_msetup[0] == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 6);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_80107E48_msetup(s32 arg0) {
    D_8011A882_msetup.state = 7;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] == 0) {
        D_8011AA43_msetup = 1;
    } else {
        D_8011AA43_msetup = 0;
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_80107ECC_msetup(s32 arg0) {
    D_8011A886_msetup[0] = 0;
    func_8010B82C_msetup(0x152D);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x152F);
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
        arg0 = -2;
    } else {
        func_8010B82C_msetup(0x152E);
        if (func_8010B858_msetup() == 0) {
            func_8010F2F4_msetup(D_80119420_msetup, 9);
            HuAudFXPlay(0x2E4);
            func_8010BE8C_msetup(D_8011A880_msetup);
            arg0 = 0;
        } else {
            D_8011A886_msetup[0] = -1;
            arg0--;
        }
    }
    return arg0;
}

void func_80107F88_msetup(s16 arg0, s16 arg1, s16 arg2) {
    if (arg2 == 0x31) {
        HuAudSeqPlay(9);
    }
}


extern s16 (*D_80119434_msetup[])(s32);
extern s16 (*D_80119458_msetup[])(s32);
extern MsCamKey D_80119580_msetup;
extern MsCamKey D_801195A0_msetup[];
extern MsCamKey D_801196C0_msetup[];
extern MsCamKey D_801197BC_msetup[];

/* Party Mode setup process: the menu steps of D_80119434_msetup, then the Star Lift ride. */
void func_80107FB4_msetup(void) {
    Process *proc;
    s16 wait[2];
    s16 step;
    s32 i;

    D_8011A880_msetup = 4;
    _ClearFlag(0);
    Hu3DModelPosSet(func_8000B108_main(D_8011942C_msetup, 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(MsSetupWork));
    D_8011A886_msetup[0] = -1;
    proc->user_data = &D_8011A886_msetup[-2];
    D_80119420_msetup = func_8010F2BC_msetup();
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(wait, 0, sizeof(wait));
    proc->user_data = wait;
    func_80106260_msetup(&D_80119580_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    wait[0] = 1;
    do {
        HuPrcVSleep();
    } while (wait[0] == 1);
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    if (_CheckFlag(0x1A) == 0) {
        _SetFlag(0x1A);
        func_8010B82C_msetup(0x1500);
        func_8010B858_msetup();
    }
    func_8010B82C_msetup(0x1502);
    func_8010B858_msetup();
    step = 0;
    do {
        step = D_80119434_msetup[step](step);
    } while (step >= 0);
    func_8010F2F4_msetup(D_80119420_msetup, 8);
    D_8011A990_msetup = 0;
    if (step < -1) {
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9F0_msetup[i].unk2 = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9F0_msetup[i].unk2 = 16;
        }
        HuAudSeqFadeOut(0x186);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(D_801197BC_msetup, 22.0f, NULL);
        GwSystem.current_board_index = D_8011AA30_msetup.board;
        GwSystem.total_turns = D_8011AA30_msetup.turns;
        GwSystem.current_game_length = D_8011AA30_msetup.length;
        for (i = 0; i < D_8011A880_msetup; i++) {
            GwPlayer[i].chr = D_8011AA34_msetup[i];
            GwPlayer[i].star = D_8011AA3C_msetup[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = D_8011AA30_msetup.pad[i];
            if (D_8011AA38_msetup[i] < 4) {
                GwPlayer[i].cpu_difficulty = D_8011AA38_msetup[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        if (D_8011AA43_msetup != 0) {
            _SetFlag(0x1B);
        } else {
            _ClearFlag(0x1B);
        }
        if (D_8011AA47_msetup != 0) {
            _SetFlag(0x20);
        } else {
            _ClearFlag(0x20);
        }
        D_8011A944_msetup = 4;
        D_8011AA4C_msetup[0] = 0x47;
        D_8011A946_msetup = 0;
    } else {
        D_80119410_msetup = 0x4B;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(D_801196C0_msetup, 25.0f, NULL);
    }
    func_8010F2F4_msetup(D_80119420_msetup, 0xFF);
    D_80119410_msetup = 1;
    while (1) {
        HuPrcVSleep();
    }
}

s16 func_80108464_msetup(s32 arg0) {
    D_8011A882_msetup.state = 9;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_801084C4_msetup(s32 arg0) {
    s32 i;

    D_8011A882_msetup.state = 2;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] != -1) {
        D_8011A990_msetup = 0;
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        func_8010BBF4_msetup(D_8011A880_msetup);
        HuAudFXPlay(0x2DB);
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9F0_msetup[i].unk2 = 1;
        }
        while (D_8011A9F0_msetup[1].unk2 != 0) {
            HuPrcVSleep();
        }
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_801085D4_msetup(s32 arg0) {
    s32 i;

    if (D_8011AA41_msetup != 0) {
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9F0_msetup[i].unk2 = 6;
        }
        D_8011A882_msetup.state = 3;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
    } else {
        D_8011A990_msetup = 1;
    }
    if (D_8011A886_msetup[0] == -1) {
        HuAudFXPlay(0x2E4);
        func_8010BE8C_msetup(D_8011A880_msetup);
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_801086C8_msetup(s32 arg0) {
    s32 i;

    for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
        D_8011A9F0_msetup[i].unk2 = 14;
    }
    D_8011A882_msetup.state = 11;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] == 0) {
        D_8011A886_msetup[-2] = 10;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
        if (D_8011A886_msetup[0] < 0) {
            return arg0;
        }
        arg0++;
    } else {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011AA3C_msetup[i] = 5;
        }
        if (D_8011A886_msetup[0] < 0) {
            arg0--;
        } else {
            arg0++;
        }
    }
    return arg0;
}

s16 func_801087F4_msetup(s32 arg0) {
    s32 i;

    D_8011A882_msetup.state = 8;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] < 0) {
        func_8010F2F4_msetup(D_80119420_msetup, 0xFF);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 1);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_801088A8_msetup(s32 arg0) {
    D_8011A882_msetup.state = 5;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 3);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 4);
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_80108938_msetup(s32 arg0) {
    s32 i;

    D_8011A882_msetup.state = 13;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    if (D_8011A886_msetup[0] == 0) {
        D_8011AA47_msetup = 0;
    } else {
        D_8011AA47_msetup = 1;
    }
    if (D_8011A886_msetup[0] == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 6);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_801089FC_msetup(s32 arg0) {
    D_8011A886_msetup[0] = 0;
    func_8010B82C_msetup(0x241B);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x241D);
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
        arg0 = -2;
    } else {
        func_8010B82C_msetup(0x241C);
        if (func_8010B858_msetup() == 0) {
            func_8010F2F4_msetup(D_80119420_msetup, 9);
            HuAudFXPlay(0x2E4);
            func_8010BE8C_msetup(D_8011A880_msetup);
            arg0 = 0;
        } else {
            D_8011A886_msetup[0] = -1;
            arg0--;
        }
    }
    return arg0;
}

/* Duel Mode setup process: as func_80107FB4_msetup with two players and D_80119458_msetup. */
void func_80108AB8_msetup(void) {
    Process *proc;
    s16 wait[2];
    s16 step;
    s32 i;

    D_8011A880_msetup = 2;
    _ClearFlag(0);
    Hu3DModelPosSet(func_8000B108_main(D_80119428_msetup, 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(MsSetupWork));
    D_8011A886_msetup[0] = -1;
    proc->user_data = &D_8011A886_msetup[-2];
    D_80119420_msetup = func_8010F2BC_msetup();
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(wait, 0, sizeof(wait));
    proc->user_data = wait;
    func_80106260_msetup(&D_80119580_msetup);
    HuPrcVSleep();
    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011AA3C_msetup[i] = 5;
    }
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    wait[0] = 1;
    do {
        HuPrcVSleep();
    } while (wait[0] == 1);
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    if (_CheckFlag(0x19) == 0) {
        _SetFlag(0x19);
        func_8010B82C_msetup(0x2400);
        func_8010B858_msetup();
    }
    func_8010B82C_msetup(0x2402);
    func_8010B858_msetup();
    step = 0;
    do {
        step = D_80119458_msetup[step](step);
    } while (step >= 0);
    func_8010F2F4_msetup(D_80119420_msetup, 8);
    D_8011A990_msetup = 0;
    if (step < -1) {
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9F0_msetup[i].unk2 = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9F0_msetup[i].unk2 = 16;
        }
        HuAudSeqFadeOut(0x186);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(D_801197BC_msetup, 22.0f, NULL);
        GwSystem.current_board_index = D_8011AA30_msetup.board;
        GwSystem.total_turns = D_8011AA30_msetup.turns;
        for (i = 0; i < D_8011A880_msetup; i++) {
            GwPlayer[i].chr = D_8011AA34_msetup[i];
            GwPlayer[i].star = D_8011AA3C_msetup[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = D_8011AA30_msetup.pad[i];
            if (D_8011AA38_msetup[i] < 4) {
                GwPlayer[i].cpu_difficulty = D_8011AA38_msetup[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        if (D_8011AA47_msetup != 0) {
            _SetFlag(0x20);
        } else {
            _ClearFlag(0x20);
        }
        D_8011A944_msetup = 3;
        D_8011AA4C_msetup[0] = 0x5A;
        D_8011A946_msetup = 0;
    } else {
        D_80119410_msetup = 0x4B;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(D_801196C0_msetup, 25.0f, NULL);
    }
    func_8010F2F4_msetup(D_80119420_msetup, 0xFF);
    D_80119410_msetup = 1;
    while (1) {
        HuPrcVSleep();
    }
}

/* Story Mode: the board, turns and four players from GwStory (chapter unk0, character unk1,
   COM level unk2); the other two or three characters are shuffled. */
#ifdef NON_MATCHING
/* Residue: register allocation (board copy, the rest[] loop registers, the n < 4 entry test). */
void func_80108F74_msetup(void) {
    u8 rest[4];
    s32 i;
    s32 j;
    s32 n;
    s32 rival;
    s32 star;
    s32 board;
    u8 t;
    u32 r;

    GwSystem.current_board_index = D_80119478_msetup[GwStory.unk0];
    GwSystem.current_game_length = 0;
    board = D_80119488_msetup[GwStory.unk0];
    star = 0;
    if (board == 1) {
        GwSystem.total_turns = 20;
        star = 5;
    } else {
        GwSystem.total_turns = 15;
    }
    GwPlayer[0].chr = GwStory.unk1;
    GwPlayer[0].star = star;
    GwPlayer[0].pad = D_8011A949_msetup;
    GwPlayer[0].cpu_difficulty = 1;
    GwPlayer[0].stat = 0;
    GwPlayer[0].coin = 0;
    rival = D_80119498_msetup[GwStory.unk0];
    if ((u8)rival == GwStory.unk1) {
        rival = 1;
    }
    n = 0;
    if (board == 1) {
        GwPlayer[1].chr = rival;
        GwPlayer[1].star = star;
        GwPlayer[1].pad = D_8011AA30_msetup.pad[1];
        GwPlayer[1].cpu_difficulty = GwStory.unk2;
        GwPlayer[1].stat = 1;
        GwPlayer[1].coin = 0;
        return;
    }
    for (i = 0; n < 4; i++) {
        if ((u8)i != GwStory.unk1 && (u8)i != (u8)rival) {
            rest[n] = i;
            n++;
        }
    }
    for (n = 0x60; n != 0; n--) {
        r = func_801061E0_msetup();
        t = rest[r & 3];
        rest[r & 3] = rest[(r >> 2) & 3];
        rest[(r >> 2) & 3] = t;
    }
    j = 1;
    if (GwStory.unk0 >= 11) {
        GwPlayer[j].chr = rival;
        GwPlayer[j].star = star;
        GwPlayer[j].pad = D_8011AA30_msetup.pad[j];
        GwPlayer[j].cpu_difficulty = GwStory.unk2;
        GwPlayer[j].stat = 1;
        GwPlayer[j].coin = 0;
        j = 2;
    }
    for (n = 0; j < 4; j++, n++) {
        GwPlayer[j].chr = rest[n];
        GwPlayer[j].star = star;
        GwPlayer[j].pad = D_8011AA30_msetup.pad[j];
        GwPlayer[j].cpu_difficulty = GwStory.unk2;
        GwPlayer[j].stat = 1;
        GwPlayer[j].coin = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108F74_msetup);
#endif

/* Story Mode setup process: players from func_80108F74_msetup, the intro messages, then the
   start or cancel choice. */
void func_80109218_msetup(void) {
    Process *proc;
    s16 wait[2];
    s32 i;
    s32 j;
    s32 loop;

    D_8011A880_msetup = 4;
    func_80108F74_msetup();
    D_8011AA30_msetup.board = GwSystem.current_board_index;
    D_8011AA30_msetup.turns = GwSystem.total_turns;
    D_8011AA30_msetup.unk17 = _CheckFlag(0x29);
    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011AA34_msetup[i] = GwPlayer[i].chr;
        D_8011AA3C_msetup[i] = GwPlayer[i].star;
        D_8011AA30_msetup.pad[i] = GwPlayer[i].pad;
        if (GwPlayer[i].stat & 1) {
            D_8011AA38_msetup[i] = GwPlayer[i].cpu_difficulty;
        } else {
            D_8011AA38_msetup[i] = 0xFF;
        }
    }
    D_8011AA30_msetup.unk10 = 1;
    D_8011AA30_msetup.unk11 = 3;
    Hu3DModelPosSet(func_8000B108_main(D_8011942C_msetup, 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(MsSetupWork));
    D_8011A886_msetup[0] = -1;
    proc->user_data = &D_8011A886_msetup[-2];
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(wait, 0, sizeof(wait));
    proc->user_data = wait;
    func_80106260_msetup(&D_80119580_msetup);
    func_8010BBF4_msetup(D_8011A880_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    wait[0] = 1;
    HuAudFXPlay(0x2DB);
    D_8011A9F0_msetup[0].unk2 = 1;
    while (wait[0] == 1) {
        HuPrcVSleep();
    }
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    func_8010B998_msetup();
    func_8010B968_msetup(D_8011AA30_msetup.chr[0] + 0x1C00, 0);
    func_8010B82C_msetup(0x1A00);
    func_8010B858_msetup();
    func_8010B82C_msetup(D_801194A8_msetup[D_8011AA30_msetup.board]);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x1A07);
    func_8010B858_msetup();
    func_8010B998_msetup();
    D_8011A990_msetup = 2;
    D_8011A882_msetup.state = 12;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    D_8011A990_msetup = 1;
    j = 1;
    HuPrcVSleep();
    func_8010B9B8_msetup(0x4000, 0x4000);
    func_8010B82C_msetup(0x1A08);
    func_8010B858_msetup();
    D_8011A990_msetup = 0;
    HuAudFXPlay(0x2DB);
    for (; j < (s16)(u16)D_8011A880_msetup; j++) {
        D_8011A9F0_msetup[j].unk2 = 1;
    }
    for (i = 7; i != 0; i--) {
        HuPrcVSleep();
    }
    D_8011A9F0_msetup[0].unk2 = 17;
    while (D_8011A9F0_msetup[D_8011A880_msetup - 1].unk2 != 0) {
        HuPrcVSleep();
    }
    D_8011A990_msetup = 1;
    func_8010B82C_msetup(0x1A09);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x1A0A);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x1A0B);
    func_8010B858_msetup();
    func_8010B82C_msetup(D_8011AA47_msetup != 0 ? 0x1A10 : 0x1A0F);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x1A0C);
    func_8010B858_msetup();
    loop = 1;
    do {
        func_8010B82C_msetup(0x1A0D);
        if (func_8010B858_msetup() == 0) {
            func_8010B82C_msetup(0x1A0E);
            func_8010B858_msetup();
            HuAudFXPlay(0x2A6);
            D_8011A990_msetup = 0;
            for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
                D_8011A9F0_msetup[i].unk2 = 16;
            }
            HuAudSeqFadeOut(0x186);
            D_80119412_msetup = 1;
            HuAudFXPlay(0x2DF);
            func_801068F4_msetup(D_801197BC_msetup, 22.0f, NULL);
            _ClearFlag(0);
            _ClearFlag(0x28);
            _SetFlag(0x1B);
            if (D_8011AA47_msetup != 0) {
                _SetFlag(0x20);
            } else {
                _ClearFlag(0x20);
            }
            GwSystem.playMode = 5;
            D_8011A944_msetup = 4;
            D_8011AA4C_msetup[0] = 0x47;
            D_8011A946_msetup = 0;
            omOvlHisChg(0, 0x7D, 0, 0x4090);
            omovlhisidx++;
            loop = 0;
        } else {
            func_8010B82C_msetup(0x1501);
            if (func_8010B858_msetup() == 0) {
                loop = 0;
                D_8011A990_msetup = 0;
                D_80119410_msetup = 0x4B;
                HuAudFXPlay(0x2EC);
                func_801068F4_msetup(D_801196C0_msetup, 25.0f, NULL);
            }
        }
    } while (loop != 0);
    D_80119410_msetup = 1;
    while (1) {
        HuPrcVSleep();
    }
}

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
