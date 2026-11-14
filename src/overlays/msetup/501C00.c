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
            D_8011A9E0_msetup[i].state = 1;
        }
        while (D_8011A9E0_msetup[3].state != 0) {
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
            D_8011A9E0_msetup[i].state = 7;
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
            D_8011A9E0_msetup[i].state = 10;
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
        D_8011A9E0_msetup[i].state = 12;
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
        D_8011A9E0_msetup[i].state = 11;
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
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[2], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(MsSetupWork));
    D_8011A886_msetup[0] = -1;
    proc->user_data = &D_8011A886_msetup[-2];
    D_80119420_msetup = func_8010F2BC_msetup();
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(wait, 0, sizeof(wait));
    proc->user_data = wait;
    func_80106260_msetup((MsCamKey *)&D_80119580_msetup);
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
            D_8011A9E0_msetup[i].state = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9E0_msetup[i].state = 16;
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
            D_8011A9E0_msetup[i].state = 1;
        }
        while (D_8011A9E0_msetup[1].state != 0) {
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
            D_8011A9E0_msetup[i].state = 6;
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
        D_8011A9E0_msetup[i].state = 14;
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
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[1], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(MsSetupWork));
    D_8011A886_msetup[0] = -1;
    proc->user_data = &D_8011A886_msetup[-2];
    D_80119420_msetup = func_8010F2BC_msetup();
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(wait, 0, sizeof(wait));
    proc->user_data = wait;
    func_80106260_msetup((MsCamKey *)&D_80119580_msetup);
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
            D_8011A9E0_msetup[i].state = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < (s16)(u16)D_8011A880_msetup; i++) {
            D_8011A9E0_msetup[i].state = 16;
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
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[2], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(MsSetupWork));
    D_8011A886_msetup[0] = -1;
    proc->user_data = &D_8011A886_msetup[-2];
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(wait, 0, sizeof(wait));
    proc->user_data = wait;
    func_80106260_msetup((MsCamKey *)&D_80119580_msetup);
    func_8010BBF4_msetup(D_8011A880_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    wait[0] = 1;
    HuAudFXPlay(0x2DB);
    D_8011A9E0_msetup[0].state = 1;
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
        D_8011A9E0_msetup[j].state = 1;
    }
    for (i = 7; i != 0; i--) {
        HuPrcVSleep();
    }
    D_8011A9E0_msetup[0].state = 17;
    while (D_8011A9E0_msetup[D_8011A880_msetup - 1].state != 0) {
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
                D_8011A9E0_msetup[i].state = 16;
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

void func_80109868_msetup(void) {
    s16 sp10[2];
    Process *proc;
    s32 i;
    s32 loop;

    D_8011A880_msetup = 2;
    func_80108F74_msetup();
    D_8011AA30_msetup.board = GwSystem.current_board_index;
    D_8011AA30_msetup.turns = GwSystem.total_turns;
    D_8011AA30_msetup.unk17 = _CheckFlag(0x29);
    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011AA30_msetup.chr[i] = GwPlayer[i].chr;
        D_8011AA30_msetup.star[i] = GwPlayer[i].star;
        D_8011AA30_msetup.pad[i] = GwPlayer[i].pad;
        if (GwPlayer[i].stat & 1) {
            D_8011AA30_msetup.com[i] = GwPlayer[i].cpu_difficulty;
        } else {
            D_8011AA30_msetup.com[i] = 0xFF;
        }
    }
    D_8011AA30_msetup.unk10 = 1;
    D_8011AA30_msetup.unk11 = 1;
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[1], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, 6);
    D_8011A886_msetup[0] = -1;
    proc->user_data = D_8011A886_msetup - 2;
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(sp10, 0, 4);
    proc->user_data = sp10;
    func_80106260_msetup((MsCamKey *)&D_80119580_msetup);
    func_8010BBF4_msetup(D_8011A880_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    sp10[0] = 1;
    HuAudFXPlay(0x2DB);
    D_8011A9E0_msetup[0].state = 1;
    while (sp10[0] == 1) {
        HuPrcVSleep();
    }
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    func_8010B968_msetup(D_8011AA30_msetup.chr[0] + 0x1C00, 0);
    func_8010B82C_msetup(0x2900);
    func_8010B858_msetup();
    func_8010B82C_msetup(D_801194C0_msetup[D_8011AA30_msetup.board]);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x2907);
    func_8010B858_msetup();
    D_8011A882_msetup.state = 0xC;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    func_8010B82C_msetup(0x2908);
    func_8010B858_msetup();
    HuAudFXPlay(0x2DB);
    for (i = 1; i < D_8011A880_msetup; i++) {
        D_8011A9E0_msetup[i].state = 1;
    }
    for (i = 7; i != 0; i--) {
        HuPrcVSleep();
    }
    D_8011A9E0_msetup[0].state = 0x11;
    while (D_8011A9E0_msetup[D_8011A880_msetup - 1].state != 0) {
        HuPrcVSleep();
    }
    if (D_8011AA30_msetup.chr[1] != 1) {
        func_8010B82C_msetup(D_801194D8_msetup[D_8011AA30_msetup.chr[1]]);
    } else {
        func_8010B82C_msetup(D_801194F8_msetup[D_8011AA30_msetup.board]);
    }
    func_8010B858_msetup();
    func_8010B82C_msetup(0x2914);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x2915);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x2916);
    func_8010B858_msetup();
    func_8010B82C_msetup(D_8011AA30_msetup.unk17 != 0 ? 0x291A : 0x2919);
    func_8010B858_msetup();
    loop = TRUE;
    do {
        func_8010B82C_msetup(0x2917);
        if (func_8010B858_msetup() == 0) {
            func_8010B82C_msetup(0x2918);
            func_8010B858_msetup();
            HuAudFXPlay(0x2A6);
            D_8011A990_msetup = 0;
            for (i = 0; i < D_8011A880_msetup; i++) {
                D_8011A9E0_msetup[i].state = 0x10;
            }
            HuAudSeqFadeOut(0x186);
            D_80119412_msetup = 1;
            HuAudFXPlay(0x2DF);
            func_801068F4_msetup(D_801197BC_msetup, 22.0f, NULL);
            _ClearFlag(0);
            _ClearFlag(0x28);
            if (D_8011AA30_msetup.unk17 != 0) {
                _SetFlag(0x20);
            } else {
                _ClearFlag(0x20);
            }
            GwSystem.playMode = 6;
            D_8011A944_msetup = 3;
            D_8011AA4C_msetup[0] = 0x5A;
            D_8011A946_msetup = 0;
            omOvlHisChg(0, 0x7D, 0, 0x4090);
            omovlhisidx++;
            loop = FALSE;
        } else {
            func_8010B82C_msetup(0x1501);
            if (func_8010B858_msetup() == 0) {
                loop = FALSE;
                D_8011A990_msetup = 0;
                D_80119410_msetup = 0x4B;
                HuAudFXPlay(0x2EC);
                func_801068F4_msetup(D_801196C0_msetup, 25.0f, NULL);
            }
        }
    } while (loop);
    D_80119410_msetup = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s16 func_80109EA0_msetup(s16 arg0) {
    s16 ret;

    if (D_8011A886_msetup[0] >= 0) {
        func_8010B82C_msetup(0x4900);
        func_8010B858_msetup();
        func_8010B82C_msetup(0x4902);
        func_8010B858_msetup();
        ret = arg0 + 1;
    } else {
        ret = arg0 - 1;
    }
    return ret;
}

s16 func_80109F04_msetup(s16 arg0) {
    s16 ret;

    if (D_8011A886_msetup[0] >= 0) {
        func_8010B968_msetup(D_8011AA30_msetup.chr[0] + 0x1C00, 0);
        func_8010B82C_msetup(0x4A00);
        func_8010B858_msetup();
        func_8010B82C_msetup(0x4A02);
        func_8010B858_msetup();
        ret = arg0 + 1;
    } else {
        ret = arg0 - 1;
    }
    return ret;
}

s16 func_80109F7C_msetup(s32 arg0) {
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
        func_8010BA6C_msetup(1, D_8011A880_msetup);
        for (i = 4; i != 0; i--) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x2DB);
        for (i = 1; i < D_8011A880_msetup; i++) {
            D_8011A9E0_msetup[i].state = 1;
        }
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        D_8011A9E0_msetup[0].state = 0x11;
        while (D_8011A9E0_msetup[D_8011A880_msetup - 1].state != 0) {
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

s16 func_8010A10C_msetup(s32 arg0) {
    s16 ret;
    s32 i;

    if (D_8011AA30_msetup.unk11 != 0) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9E0_msetup[i].state = 7;
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
        func_8010BC18_msetup(1, D_8011A880_msetup);
    }
    if (D_8011A886_msetup[0] < 0) {
        arg0--;
    } else {
        arg0++;
    }
    return arg0;
}

s16 func_8010A204_msetup(s32 arg0) {
    D_8011A886_msetup[0] = 0;
    func_8010B82C_msetup(0x4919);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x491B);
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
        arg0 = -2;
    } else {
        func_8010B82C_msetup(0x491A);
        if (func_8010B858_msetup() == 0) {
            HuAudFXPlay(0x2E4);
            func_8010BE8C_msetup(D_8011A880_msetup);
            arg0 = 1;
        } else {
            D_8011A886_msetup[0] = -1;
            arg0--;
        }
    }
    return arg0;
}

s16 func_8010A2B0_msetup(s32 arg0) {
    D_8011A886_msetup[0] = 0;
    func_8010B82C_msetup(0x4919);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x491B);
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
        arg0 = -2;
    } else {
        func_8010B82C_msetup(0x491A);
        if (func_8010B858_msetup() == 0) {
            HuAudFXPlay(0x2E4);
            func_8010BC18_msetup(1, D_8011A880_msetup);
            arg0 = 1;
        } else {
            D_8011A886_msetup[0] = -1;
            arg0--;
        }
    }
    return arg0;
}

void func_8010A35C_msetup(MsMenuFunc *menu) {
    s16 sp10[2];
    Process *proc;
    s16 state;
    s32 i;

    D_8011A880_msetup = 4;
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[0], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    proc = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, 6);
    D_8011A886_msetup[0] = -1;
    proc->user_data = D_8011A886_msetup - 2;
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(sp10, 0, 4);
    proc->user_data = sp10;
    if (D_8011A938_msetup == 6) {
        func_8010BA6C_msetup(0, 1);
    }
    func_80106260_msetup((MsCamKey *)&D_80119580_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    D_8011A886_msetup[0] = 0;
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    if (D_8011A938_msetup == 6) {
        HuAudFXPlay(0x2DB);
        D_8011A9E0_msetup[0].state = 1;
    }
    sp10[0] = 1;
    do {
        HuPrcVSleep();
    } while (sp10[0] == 1);
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    state = 0;
    do {
        state = menu[state](state);
    } while (state >= 0);
    D_8011A990_msetup = 0;
    if (state < -1) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9E0_msetup[i].state = 0xC;
        }
        HuPrcVSleep();
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9E0_msetup[i].state = 0x10;
        }
        HuAudSeqFadeOut(0x186);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(D_801197BC_msetup, 22.0f, NULL);
        for (i = 0; i < D_8011A880_msetup; i++) {
            GwPlayer[i].chr = D_8011AA30_msetup.chr[i];
            GwPlayer[i].star = D_8011AA30_msetup.star[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = D_8011AA30_msetup.pad[i];
            if (D_8011AA30_msetup.com[i] < 4) {
                GwPlayer[i].cpu_difficulty = D_8011AA30_msetup.com[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        D_8011A944_msetup = 1;
        D_8011AA4C_msetup[0] = 0x69;
        D_8011A946_msetup = 0;
    } else {
        D_80119410_msetup = 0x4B;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(D_801196C0_msetup, 25.0f, NULL);
    }
    D_80119410_msetup = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010A780_msetup(void) {
    func_8010A35C_msetup(D_80119510_msetup);
}

void func_8010A7A0_msetup(void) {
        D_8011AA30_msetup.unk10 = 1;
    D_8011AA30_msetup.unk11 = 3;
    D_8011AA30_msetup.chr[0] = GwStory.unk1;
    D_8011AA30_msetup.com[0] = 0xFF;
    func_8010A35C_msetup(D_80119524_msetup);
}

void func_8010A7EC_msetup(s16 mode) {
    s16 sp10[2];
    Process *proc;
    s32 *mes;
    s32 i;
    s8 star;

    switch (mode) {
    case 0:
    default:
        D_8011A880_msetup = 4;
        D_8011AA30_msetup.unk10 = 1;
        D_8011AA30_msetup.unk11 = 3;
        D_8011AA30_msetup.chr[0] = 3;
        D_8011AA30_msetup.chr[1] = 2;
        D_8011AA30_msetup.chr[2] = 0;
        D_8011AA30_msetup.chr[3] = 4;
        mes = D_80119534_msetup;
        i = 2;
        break;
    case 1:
        D_8011A880_msetup = 2;
        D_8011AA30_msetup.unk10 = 1;
        D_8011AA30_msetup.unk11 = 1;
        D_8011AA30_msetup.chr[0] = 0;
        D_8011AA30_msetup.chr[1] = 1;
        mes = D_80119548_msetup;
        i = 1;
        break;
    }
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[i], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    func_8010E21C_msetup();
    proc = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(sp10, 0, 4);
    proc->user_data = sp10;
    func_80106260_msetup((MsCamKey *)&D_80119580_msetup);
    func_8010BBF4_msetup(D_8011A880_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 0x10);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    sp10[0] = 1;
    HuAudFXPlay(0x2DB);
    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011A9E0_msetup[i].state = 1;
    }
    while (sp10[0] == 1) {
        HuPrcVSleep();
    }
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    func_8010B998_msetup();
    for (i = 0; i < 4; i++) {
        func_8010B82C_msetup(mes[i]);
        func_8010B858_msetup();
        if (func_8010BA3C_msetup() & 0x4000) {
            func_8010B82C_msetup(mes[4]);
            if (func_8010B858_msetup() == 0) {
                break;
            }
        }
    }
    if (i < 4) {
        D_8011A990_msetup = 0;
        D_80119410_msetup = 0x4B;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(D_801196C0_msetup, 25.0f, NULL);
    } else {
        HuAudFXPlay(0x2A6);
        D_8011A990_msetup = 0;
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9E0_msetup[i].state = 0x10;
        }
        HuAudSeqFadeOut(0x186);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(D_801197BC_msetup, 22.0f, NULL);
        _ClearFlag(0);
        GwSystem.current_board_index = 6;
        GwSystem.total_turns = 20;
        GwSystem.current_game_length = 0;
        switch (mode) {
        case 0:
        default:
            D_8011A944_msetup = 4;
            D_8011AA4C_msetup[0] = 0x47;
            D_8011A946_msetup = 0;
            star = 0;
            break;
        case 1:
            D_8011A944_msetup = 3;
            D_8011AA4C_msetup[0] = 0x5A;
            D_8011A946_msetup = 0;
            star = 5;
            break;
        }
        for (i = 0; i < D_8011A880_msetup; i++) {
            GwPlayer[i].chr = D_8011AA30_msetup.chr[i];
            GwPlayer[i].star = star;
            GwPlayer[i].pad = D_8011A948_msetup;
            GwPlayer[i].cpu_difficulty = 1;
            GwPlayer[i].stat = 1;
            GwPlayer[i].coin = 0;
        }
    }
    D_80119410_msetup = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010AC78_msetup(void) {
    func_8010A7EC_msetup(0);
}

void func_8010AC94_msetup(void) {
    func_8010A7EC_msetup(1);
}

void func_8010ACB0_msetup(void) {
}

/* .data (0x80119410, 0x1170 bytes): the overlay's initialised data, in address order. */
extern char D_8011A6E4_msetup[], D_8011A6F0_msetup[], D_8011A6FC_msetup[], D_8011A708_msetup[];
extern char D_8011A714_msetup[], D_8011A720_msetup[], D_8011A72C_msetup[], D_8011A738_msetup[];
extern char D_8011A744_msetup[], D_8011A74C_msetup[], D_8011A754_msetup[], D_8011A75C_msetup[];
extern char D_8011A764_msetup[], D_8011A76C_msetup[], D_8011A774_msetup[], D_8011A77C_msetup[];
extern char D_8011A784_msetup[], D_8011A78C_msetup[], D_8011A794_msetup[], D_8011A79C_msetup[];
extern char D_8011A7A4_msetup[], D_8011A7AC_msetup[];

u16 D_80119410_msetup = 0x0;
s16 D_80119412_msetup = 0;
f32 D_80119414_msetup = 58.0f;
s8 D_80119418_msetup = 0;
u8 D_80119419_msetup = 10;
s32 D_8011941C_msetup = 0x0;
Process * D_80119420_msetup = NULL;
s32 D_80119424_msetup[3] = {
    0x140001, 0x14000C, 0x14000D,
};
omObjData * D_80119430_msetup = NULL;
s16 (*D_80119434_msetup[9])(s32) = {
    func_801077E0_msetup, func_80107840_msetup, func_80107964_msetup, func_80107A58_msetup,
    func_80107B8C_msetup, func_80107CF4_msetup, func_80107D84_msetup, func_80107E48_msetup,
    func_80107ECC_msetup,
};
s16 (*D_80119458_msetup[8])(s32) = {
    func_80108464_msetup, func_801084C4_msetup, func_801085D4_msetup, func_801086C8_msetup,
    func_801087F4_msetup, func_801088A8_msetup, func_80108938_msetup, func_801089FC_msetup,
};
u8 D_80119478_msetup[16] = {
    0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5, 0, 0,
};
u8 D_80119488_msetup[16] = {
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 2, 2, 0, 0,
};
u8 D_80119498_msetup[16] = {
    4, 4, 3, 3, 5, 5, 2, 2, 0, 0, 7, 6, 6, 0, 0, 0,
};
s32 D_801194A8_msetup[6] = {
    0x1A01, 0x1A02, 0x1A03, 0x1A04, 0x1A05, 0x1A06,
};
s32 D_801194C0_msetup[6] = {
    0x2901, 0x2902, 0x2903, 0x2904, 0x2905, 0x2906,
};
s32 D_801194D8_msetup[8] = {
    0x290D, 0x290F, 0x290C, 0x290A, 0x2909, 0x290B, 0x290E, 0x290E,
};
s32 D_801194F8_msetup[6] = {
    0x290F, 0x2910, 0x2911, 0x2912, 0x2913, 0x2913,
};
MsMenuFunc D_80119510_msetup[5] = {
    (MsMenuFunc)func_80109EA0_msetup, func_801077E0_msetup, func_80107840_msetup, func_80107964_msetup,
    func_8010A204_msetup,
};
MsMenuFunc D_80119524_msetup[4] = {
    (MsMenuFunc)func_80109F04_msetup, func_80109F7C_msetup, func_8010A10C_msetup, func_8010A2B0_msetup,
};
s32 D_80119534_msetup[5] = {
    0x1701, 0x1702, 0x1703, 0x1704, 0x1705,
};
s32 D_80119548_msetup[5] = {
    0x2601, 0x2602, 0x2603, 0x2604, 0x2605,
};
process_func D_8011955C_msetup[9] = {
    func_80107FB4_msetup, func_80108AB8_msetup, func_80109218_msetup, func_80109868_msetup,
    func_80118D48_msetup, func_8010A780_msetup, func_8010A7A0_msetup, func_8010AC78_msetup,
    func_8010AC94_msetup,
};
MsCamView D_80119580_msetup = { { 270.0f, 0.0f, 0.0f }, { 0.0f, 200.0f, 0.0f }, 130.0f, 50.0f };
MsCamKey D_801195A0_msetup[8] = {
    { { 270.0f, 0.0f, 0.0f }, { 0.0f, 164.5f, 70.0f }, 130.0f, 50.0f, 1.0f },
    { { 270.0f, 0.0f, 0.0f }, { 0.0f, 164.5f, 70.0f }, 130.0f, 50.0f, 0.0f },
    { { 270.0f, 0.0f, 0.0f }, { 0.0f, 164.5f, 70.0f }, 450.0f, 50.0f, 0.0f },
    { { 270.0f, 0.0f, 0.0f }, { 0.0f, 164.5f, 70.0f }, 1000.0f, 50.0f, 0.0f },
    { { 270.0f, 0.0f, 0.0f }, { 0.0f, 166.5f, 70.0f }, 700.0f, 50.0f, 0.0f },
    { { 352.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 70.0f }, 560.0f, 50.0f, 0.0f },
    { { 352.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 70.0f }, 560.0f, 50.0f, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f },
};
MsCamKey D_801196C0_msetup[7] = {
    { { -8.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 70.0f }, 560.0f, 50.0f, 0.0f },
    { { -8.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 70.0f }, 560.0f, 50.0f, 0.0f },
    { { 68.0f, 0.0f, 0.0f }, { 0.0f, 166.5f, 70.0f }, 560.0f, 50.0f, 1.0f },
    { { 90.0f, 0.0f, 0.0f }, { 0.0f, 164.5f, 70.0f }, 810.0f, 50.0f, 0.0f },
    { { 90.0f, 0.0f, 0.0f }, { 0.0f, 164.5f, 70.0f }, 1960.0f, 150.0f, 0.0f },
    { { 90.0f, 0.0f, 0.0f }, { 0.0f, 164.5f, 70.0f }, 1960.0f, 150.0f, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f },
};
MsCamKey D_801197BC_msetup[7] = {
    { { 352.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 70.0f }, 560.0f, 50.0f, 0.0f },
    { { 352.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 70.0f }, 560.0f, 50.0f, 0.0f },
    { { 270.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 50.0f }, 560.0f, 50.0f, 1.0f },
    { { 270.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 50.0f }, 560.0f, 50.0f, 1.0f },
    { { 270.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 50.0f }, 1800.0f, 156.0f, 1.0f },
    { { 270.0f, 0.0f, 0.0f }, { 0.0f, 169.5f, 50.0f }, 1800.0f, 156.0f, 1.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f },
};
MSETUP_DATA_FILE_END()
s16 D_801198C0_msetup = -1;
MsModelDef D_801198C4_msetup[4] = {
    { 0xA0075, 685, 0, 2, 1, { 184.0f, 0.0f, 77.0f }, { 0.0f, -30.0f, 0.0f } },
    { 0xA0077, 8, 0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xA0078, 8, 0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x9, 669, 0, 0, 1, { 184.0f, 0.0f, 77.0f }, { 0.0f, 0.0f, 0.0f } },
};
s32 D_80119964_msetup[8] = {
    0x200A1, 0x300A2, 0x700A2, 0x400A2, 0x500A1, 0x600A1, 0x800A1, 0x90003,
};
u8 D_80119984_msetup[8] = {
    1, 0, 0, 0, 1, 1, 1, 0,
};
s32 D_8011998C_msetup[8] = {
    0x20025, 0x30025, 0x70025, 0x40025, 0x50025, 0x60025, 0x80025, 0x70025,
};
s32 D_801199AC_msetup[16] = {
    0x20033, 0x30033, 0x70033, 0x40033, 0x50033, 0x60033, 0x80033, 0x9000B, 0x20072, 0x30072,
    0x70072, 0x40072, 0x50072, 0x60072, 0x80072, 0x70072,
};
s32 D_801199EC_msetup[8] = {
    0x2004E, 0x3004E, 0x7004E, 0x4004E, 0x5004E, 0x6004E, 0x8004E, 0x90013,
};
Vec D_80119A0C_msetup[4] = {
    { -272.0f, 0.0f, -16.0f }, { -136.0f, 0.0f, -16.0f }, { 0.0f, 0.0f, -16.0f },
    { 136.0f, 0.0f, -16.0f },
};
Vec D_80119A3C_msetup[2] = {
    { -184.0f, 0.0f, -16.0f }, { 88.0f, 0.0f, -16.0f },
};
f32 D_80119A54_msetup[4] = {
    22.0f, 12.0f, 0.0f, -12.0f,
};
f32 D_80119A64_msetup[2] = {
    16.0f, -5.0f,
};
s16 D_80119A6C_msetup[8] = {
    5, 5, 0, 0, 0, 5, 5, 5,
};
s32 D_80119A7C_msetup[4] = {
    0x14001D, 0x14001E, 0x14001F, 0x140020,
};
s32 D_80119A8C_msetup[10] = {
    0x140025, 0x140026, 0x140027, 0x140028, 0x140029, 0x14002A, 0x14002B, 0x14002C, 0x14002D,
    0x14002E,
};
s32 D_80119AB4_msetup[5] = {
    0x14002F, 0x140030, 0x140031, 0x140032, 0x140033,
};
u8 D_80119AC8_msetup[4] = {
    255, 255, 255, 0,
};
u16 D_80119ACC_msetup[2] = {
    0x4C, 0x0,
};
s32 D_80119AD0_msetup[8] = {
    0x140043, 0x140044, 0x140045, 0x140046, 0x140047, 0x0, 0x0, 0x0,
};
omObjData * D_80119AF0_msetup = NULL;
f32 D_80119AF4_msetup = 5.0f;
f32 D_80119AF8_msetup = 20.0f;
f32 D_80119AFC_msetup[4] = {
    10.0f, 8.0f, 40.0f, 20.0f,
};
f32 D_80119B0C_msetup[5] = {
    1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
};
Vec D_80119B20_msetup = { 0.0f, -265.0f, -467.0f };
s32 D_80119B2C_msetup[2] = {
    0x11000E, 0x30,
};
s32 D_80119B34_msetup[4] = {
    0x1504, 0x1505, 0x1506, 0x1507,
};
s32 D_80119B44_msetup[7] = {
    0x140035, 0x1300D3, 0x1300D2, 0x1300D4, 0x1300CF, 0x1300CF, 0x1300CF,
};
s16 D_80119B60_msetup[8][2] = {
    { 136, 144 }, { 81, 136 }, { 81, 149 }, { 81, 162 }, { 91, 136 }, { 91, 149 }, { 91, 162 },
    { 53, 148 },
};
s16 D_80119B80_msetup[4][2] = { { 136, 144 }, { 136, 144 }, { 136, 144 }, { 136, 144 } }; /* unreferenced */
s16 D_80119B90_msetup[2][4] = {
    { 94, 119, 152, 62 }, { 108, 104, 120, 31 },
};
s32 D_80119BA0_msetup[8] = {
    0x140036, 0x140037, 0x140038, 0x14003C, 0x14003A, 0x140039, 0x14003B, 0x14003D,
};
s32 D_80119BC0_msetup[4] = { 0x14003E, 0x14003F, 0x140040, 0x140041 }; /* unreferenced */
s32 D_80119BD0_msetup[8] = {
    0x241E, 0x241F, 0x2420, 0x2424, 0x2422, 0x2421, 0x2423, 0x2425,
};
s32 D_80119BF0_msetup[8] = {
    0x2426, 0x2427, 0x2428, 0x242C, 0x242A, 0x2429, 0x242B, 0x242D,
};
u8 D_80119C10_msetup[8][3] = {
    { 1, 2, 1 }, { 2, 1, 2 }, { 1, 1, 1 }, { 2, 2, 5 }, { 2, 1, 3 }, { 1, 1, 3 }, { 0, 4, 3 },
    { 3, 1, 5 },
};
MsLiftKey D_80119C28_msetup[2] = {
    { { 350.0f, 300.0f, -467.0f }, 0.0f }, { { -350.0f, 300.0f, -467.0f }, 0.0f },
};
MsLiftKey D_80119C48_msetup[2] = {
    { { 0.0f, 300.0f, -467.0f }, 90.0f }, { { 0.0f, 300.0f, -467.0f }, 270.0f },
};
u8 D_80119C68_msetup[8] = {
    0, 1, 2, 7, 3, 4, 5, 6,
};
s32 D_80119C70_msetup[8] = {
    0x140014, 0x140015, 0x140016, 0x14001B, 0x140017, 0x140018, 0x140019, 0x14001A,
};
char *D_80119C90_msetup[8] = { /* unreferenced; follows D_80119C70_msetup */
    D_8011A738_msetup, D_8011A72C_msetup, D_8011A720_msetup, D_8011A714_msetup,
    D_8011A708_msetup, D_8011A6FC_msetup, D_8011A6F0_msetup, D_8011A6E4_msetup,
};
s16 D_80119CB0_msetup[8] = {
    693, 694, 695, 700, 696, 697, 698, 699,
};
s32 D_80119CC0_msetup[8] = {
    0x150C, 0x150D, 0x150E, 0x1512, 0x150F, 0x1510, 0x1511, 0x1513,
};
s32 D_80119CE0_msetup[8] = {
    0x2407, 0x2408, 0x2409, 0x240D, 0x240A, 0x240B, 0x240C, 0x240E,
};
s32 D_80119D00_msetup[8] = {
    0x490C, 0x490D, 0x490E, 0x4912, 0x490F, 0x4910, 0x4911, 0x4913,
};
s32 D_80119D20_msetup[8] = {
    0x4A06, 0x4A07, 0x4A08, 0x4A0C, 0x4A09, 0x4A0A, 0x4A0B, 0x4A0D,
};
s16 D_80119D40_msetup[8][2] = { /* unreferenced */
    { 0x70, 0x35 }, { 0x91, 0x35 }, { 0xB2, 0x35 }, { 0xD3, 0x35 },
    { 0x70, 0x55 }, { 0x91, 0x55 }, { 0xB2, 0x55 }, { 0xD3, 0x55 },
};
s32 D_80119D60_msetup[2] = { 0x140006, 0x14000B }; /* unreferenced */
char * D_80119D68_msetup[8] = {
    D_8011A77C_msetup, D_8011A774_msetup, D_8011A76C_msetup, D_8011A764_msetup, D_8011A75C_msetup,
    D_8011A754_msetup, D_8011A74C_msetup, D_8011A744_msetup,
};
s32 D_80119D88_msetup[8] = {
    0x130036, 0x130037, 0x130038, 0x13003D, 0x130039, 0x13003A, 0x13003B, 0x13003C,
};
s32 D_80119DA8_msetup[4] = {
    0x1508, 0x150B, 0x150A, 0x1509,
};
s32 D_80119DB8_msetup[4] = {
    0x1508, 0x2406, 0x2406, 0x2406,
};
MsLiftKey D_80119DC8_msetup[2] = {
    { { 350.0f, 300.0f, -467.0f }, 0.0f }, { { -350.0f, 300.0f, -467.0f }, 0.0f },
};
s16 D_80119DE8_msetup[2][2] = {
    { 98, 50 }, { 98, 84 },
};
s16 D_80119DF0_msetup[3][2] = {
    { 108, 64 }, { 165, 64 }, { 222, 64 },
};
s16 D_80119DFC_msetup[4][2] = {
    { 98, 64 }, { 143, 64 }, { 188, 64 }, { 233, 64 },
};
s16 (*D_80119E0C_msetup[3])[2] = { D_80119DE8_msetup, D_80119DF0_msetup, D_80119DFC_msetup };
s32 D_80119E18_msetup[2] = {
    0x1515, 0x1516,
};
char * D_80119E20_msetup[6] = {
    D_8011A7AC_msetup, D_8011A7A4_msetup, D_8011A79C_msetup, D_8011A794_msetup, D_8011A78C_msetup,
    D_8011A784_msetup,
};
s32 D_80119E38_msetup[6] = {
    0x140059, 0x14005A, 0x14005B, 0x14005C, 0x140057, 0x140058,
};
u16 D_80119E50_msetup[2] = {
    0x4, 0x0,
};
u16 D_80119E54_msetup[2] = {
    0x5, 0x3,
};
s32 D_80119E58_msetup[3] = {
    0x1519, 0x151A, 0x151B,
};
s32 D_80119E64_msetup[3] = {
    0x152A, 0x152B, 0x152C,
};
s32 D_80119E70_msetup[3] = {
    0x2410, 0x2411, 0x2412,
};
s32 D_80119E7C_msetup[3] = {
    0x2431, 0x2432, 0x2433,
};
s32 D_80119E88_msetup[3] = {
    0x1530, 0x1531, 0x1532,
};
s32 D_80119E94_msetup[6] = {
    0x140048, 0x140049, 0x14004A, 0x14004B, 0x14004C, 0x14004D,
};
s32 D_80119EAC_msetup[6] = {
    0x140051, 0x140052, 0x140053, 0x140054, 0x140055, 0x140056,
};
s32 D_80119EC4_msetup[7] = {
    0x151E, 0x151F, 0x1520, 0x1521, 0x1522, 0x1523, 0x151D,
};
s32 D_80119EE0_msetup[7] = {
    0x2415, 0x2416, 0x2417, 0x2418, 0x2419, 0x241A, 0x2414,
};
s32 D_80119EFC_msetup[6] = {
    0x1A11, 0x1A12, 0x1A13, 0x1A14, 0x1A15, 0x1A16,
};
s32 D_80119F14_msetup[6] = {
    0x291B, 0x291C, 0x291D, 0x291E, 0x291F, 0x2920,
};
u8 D_80119F2C_msetup[16] = { /* unreferenced */
    0xFF, 0x01, 0x03, 0xFF, 0x02, 0x01, 0x02, 0xFF, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};
s32 D_80119F3C_msetup[4] = {
    0x1525, 0x1526, 0x1527, 0x1528,
};
f32 D_80119F4C_msetup[5] = {
    288.0f, 216.0f, 144.0f, 72.0f, 0.0f,
};
f32 D_80119F60_msetup[3] = {
    288.0f, 72.0f, 0.0f,
};
/* game rules values (turns etc.); splat labels D_80119F6D/D_80119F78/D_80119F79 inside it */
s16 D_80119F6C_msetup[16] = { 20, 35, 50, -1, -1, 0, 10, 15, 20, 25, 30, 35, 40, 45, 50, 0 };
s32 D_80119F8C_msetup[2] = {
    0x242F, 0x2430,
};
MsLiftKey D_80119F94_msetup[2] = {
    { { -144.0f, 300.0f, -467.0f }, 180.0f }, { { 144.0f, 300.0f, -467.0f }, 180.0f },
};
MsLiftKey D_80119FB4_msetup[2] = {
    { { 0.0f, 300.0f, -467.0f }, 270.0f }, { { 0.0f, 300.0f, -467.0f }, 90.0f },
};
s32 D_80119FD4_msetup[2] = {
    0x2404, 0x2405,
};
s32 D_80119FDC_msetup[2] = {
    0x14004E, 0x14004F,
};
s16 D_80119FE4_msetup[5] = {
    1, 2, 3, 4, 5,
};
MsStateFunc D_80119FF0_msetup[14] = {
    func_80117818_msetup, func_8010F87C_msetup, func_80111650_msetup, func_801132C4_msetup,
    func_80114AA0_msetup, func_80115EE0_msetup, (MsStateFunc)func_80113DEC_msetup, (MsStateFunc)func_80113E20_msetup,
    func_80113ED4_msetup, func_801167B8_msetup, func_80116FE0_msetup, (MsStateFunc)func_80113E54_msetup,
    func_801145D0_msetup, (MsStateFunc)func_80113E88_msetup,
};
Vec D_8011A028_msetup[4] = {
    { 0.0f, 270.0f, -377.0f }, { 190.0f, 300.0f, -467.0f }, { 0.0f, 330.0f, -557.0f },
    { -190.0f, 300.0f, -467.0f },
};
s16 D_8011A058_msetup[4][4] = {
    { 0, 1, 2, 3 }, { 3, 0, 1, 2 }, { 2, 3, 0, 1 }, { 1, 2, 3, 0 },
};
s16 D_8011A078_msetup[4][4] = {
    { 0, 1, 3, 2 }, { 3, 0, 1, 2 }, { 1, 3, 0, 2 }, { 3, 0, 1, 2 },
};
s32 D_8011A098_msetup[4] = {
    0x14000E, 0x14000F, 0x140010, 0x140011,
};
f32 D_8011A0A8_msetup[4] = {
    180.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_8011A0B8_msetup[6] = {
    1.0f, 2.0f, 3.0f, 4.0f, 0.0f, 0.0f,
};
s16 D_8011A0D0_msetup[6] = {
    693, 694, 695, 696, 697, 698,
};
Vec D_8011A0DC_msetup[4] = {
    { -1000.0f, 700.0f, -700.0f }, { -85.0f, -8.0f, 2.0f }, { -341.0f, 133.0f, -534.0f },
    { -410.0f, -50.0f, -534.0f },
};
Vec D_8011A10C_msetup[4] = {
    { 1100.0f, 510.0f, -745.0f }, { 82.0f, 13.0f, 6.0f }, { 357.0f, -31.0f, -366.0f },
    { 370.0f, -65.0f, -366.0f },
};
Vec D_8011A13C_msetup[4] = {
    { 0.0f, 700.0f, 2.0f }, { 0.0f, -8.0f, 2.0f }, { 0.0f, 700.0f, 2.0f },
    { 0.0f, 205.0f, -534.0f },
};
Vec * D_8011A16C_msetup[3] = {
    D_8011A0DC_msetup, D_8011A10C_msetup, D_8011A13C_msetup,
};
MsStorySpr D_8011A178_msetup[10] = {
    { 0x140065, { 129.0f, -84.0f, 0.0f } }, { 0x140065, { 126.0f, 85.0f, 0.0f } },
    { 0x140065, { -127.0f, 93.0f, 0.0f } }, { 0x140065, { -139.0f, -73.0f, 0.0f } },
    { 0x140066, { 142.0f, 0.0f, 0.0f } }, { 0x140066, { 46.0f, 106.0f, 0.0f } },
    { 0x140066, { -39.0f, 111.0f, 0.0f } }, { 0x140066, { -143.0f, 4.0f, 0.0f } },
    { 0x140066, { -62.0f, -92.0f, 0.0f } }, { 0x140066, { 27.0f, -95.0f, 0.0f } },
};
MsStorySpr D_8011A218_msetup[10] = {
    { 0x140065, { 81.0f, -99.0f, 0.0f } }, { 0x140065, { 79.0f, 104.0f, 0.0f } },
    { 0x140065, { -88.0f, 106.0f, 0.0f } }, { 0x140065, { -84.0f, -108.0f, 0.0f } },
    { 0x140066, { 94.0f, -36.0f, 0.0f } }, { 0x140066, { 114.0f, 41.0f, 0.0f } },
    { 0x140066, { 0.0f, 111.0f, 0.0f } }, { 0x140066, { -92.0f, 16.0f, 0.0f } },
    { 0x140066, { -115.0f, -42.0f, 0.0f } }, { 0x140066, { 6.0f, -122.0f, 0.0f } },
};
MsStorySpr D_8011A2B8_msetup[11] = {
    { 0x140064, { 0.0f, 0.0f, 0.0f } }, { 0x140065, { 129.0f, -84.0f, 0.0f } },
    { 0x140065, { 126.0f, 85.0f, 0.0f } }, { 0x140065, { -127.0f, 93.0f, 0.0f } },
    { 0x140065, { -139.0f, -73.0f, 0.0f } }, { 0x140066, { 142.0f, 0.0f, 0.0f } },
    { 0x140066, { 46.0f, 106.0f, 0.0f } }, { 0x140066, { -39.0f, 111.0f, 0.0f } },
    { 0x140066, { -143.0f, 4.0f, 0.0f } }, { 0x140066, { -62.0f, -92.0f, 0.0f } },
    { 0x140066, { 27.0f, -95.0f, 0.0f } },
};
Vec D_8011A368_msetup[3] = {
    { -30.0f, 190.0f, 0.0f }, { 30.0f, 170.0f, 0.0f }, { -30.0f, 190.0f, 0.0f },
};
Vec D_8011A38C_msetup[3] = {
    { 20.0f, 25.0f, 0.0f }, { 20.0f, 335.0f, 0.0f }, { 20.0f, 25.0f, 0.0f },
};
u8 D_8011A3B0_msetup[8] = {
    0, 1, 2, 3, 4, 5, 0, 0,
};
MsStorySpr D_8011A3B8_msetup[7] = {
    { 0x14005D, { 0.0f, 0.0f, 0.0f } }, { 0x140014, { -102.0f, 50.0f, 0.0f } },
    { 0x140015, { 0.0f, 50.0f, 0.0f } }, { 0x140016, { 105.0f, 50.0f, 0.0f } },
    { 0x140017, { -102.0f, -55.0f, 0.0f } }, { 0x140018, { 0.0f, -55.0f, 0.0f } },
    { 0x140019, { 105.0f, -55.0f, 0.0f } },
};
MsStorySpr D_8011A428_msetup[5] = {
    { 0x14005E, { 0.0f, 0.0f, 0.0f } }, { 0x14005F, { 0.0f, 95.0f, 0.0f } },
    { 0x140060, { 0.0f, 33.0f, 0.0f } }, { 0x140061, { 0.0f, -30.0f, 0.0f } },
    { 0x140062, { 0.0f, -93.0f, 0.0f } },
};
MsStorySpr D_8011A478_msetup[5] = {
    { 0x14005E, { 0.0f, 0.0f, 0.0f } }, { 0x14005F, { 0.0f, 95.0f, 0.0f } },
    { 0x140060, { 0.0f, 33.0f, 0.0f } }, { 0x140061, { 0.0f, -30.0f, 0.0f } },
    { 0x140063, { 0.0f, -93.0f, 0.0f } },
};
MsStorySpr D_8011A4C8_msetup[4] = {
    { 0x14006A, { -90.0f, 0.0f, 0.0f } }, { 0x14006B, { 90.0f, 0.0f, 0.0f } },
    { 0x140069, { -90.0f, 0.0f, 0.0f } }, { 0x140069, { 90.0f, 0.0f, 0.0f } },
};
s32 D_8011A508_msetup[3] = {
    0x11000E, 0x30, 0x11000E,
};
s16 D_8011A514_msetup[6][2] = {
    { 90, 95 }, { 130, 95 }, { 170, 95 }, { 90, 135 }, { 130, 135 }, { 170, 135 },
};
s16 D_8011A52C_msetup[4][2] = {
    { 146, 77 }, { 146, 102 }, { 146, 127 }, { 146, 152 },
};
s16 D_8011A53C_msetup[2][2] = {
    { 124, 100 }, { 194, 100 },
};
s16 (*D_8011A544_msetup[3])[2] = { D_8011A514_msetup, D_8011A52C_msetup, D_8011A53C_msetup };
u8 D_8011A550_msetup[4] = {
    0, 1, 0, 0,
};
MsCamKey D_8011A554_msetup = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 650.0f, 50.0f, 0.0f };
s32 D_8011A578_msetup[2] = { 0, 0 }; /* unreferenced */
