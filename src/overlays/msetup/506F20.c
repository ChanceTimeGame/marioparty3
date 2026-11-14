#include "common.h"
#include "msetup.h"
#include "mallocblock.h"

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010ACC0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010AF40_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B1F4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B388_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B4B8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B588_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B5D0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B82C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B858_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B8E0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B968_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B998_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B9B8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BA10_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BA3C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BA6C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BBF4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BC18_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BE8C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BEB0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BEF8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CAF0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CC70_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CD14_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CE8C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D060_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D094_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D0C8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D234_msetup);

// register allocation: retail copies arg0 to t3 and loads pad into a0 (masked 16, same blocks)
#ifdef NON_MATCHING
s16 func_8010D4DC_msetup(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 pad, s32 btn) {
    s16 x = -D_800CBB6E_main[pad];
    s16 y = D_800D20A1_main[pad];

    if (btn & 0x200) {
        if (x < 30) {
            x = 100;
        }
    } else if (btn & 0x100) {
        if (x > -30) {
            x = -100;
        }
    }
    if (btn & 0x800) {
        if (y < 30) {
            y = 100;
        }
    } else if (btn & 0x400) {
        if (y > -30) {
            y = -100;
        }
    }
    return func_8010D234_msetup(arg0, arg1, arg2, arg3, x, y);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D4DC_msetup);
#endif

s16 func_8010D5EC_msetup(s16 pad) {
    u16 btn = D_800CDA7C_main[pad];
    s8 y = D_800D20A1_main[pad];
    s8 x = D_800CBB6E_main[pad];

    if (x > 30) {
        btn |= 0x100;
    } else if (x < -30) {
        btn |= 0x200;
    }
    if (y > 30) {
        btn |= 0x800;
    } else if (y < -30) {
        btn |= 0x400;
    }
    return btn;
}

s32 func_8010D684_msetup(s16 pad, s16 *prev) {
    u16 old = *prev;
    s16 now = func_8010D5EC_msetup(pad);

    old &= now;
    old ^= now;
    *prev = now;
    return (s16)old;
}

// retail passes work->prio with lh (called unprototyped?), lhu here (masked 1); s7/s8 swapped
#ifdef NON_MATCHING
void func_8010D6D0_msetup(void) {
    MsSprWork *work;
    s16 *xy;
    s16 spr;
    s16 slot;
    s16 prevState;
    s16 shown;
    s16 startX;
    s16 startY;
    s16 dx;
    s16 dy;
    s16 prevIdx;
    s16 alpha;
    s16 step;
    s16 tx;
    s16 ty;
    s16 x;
    s16 y;
    s16 t;
    f32 s;

    work = HuPrcCurrentGet()->user_data;
    xy = &work->x;
    spr = func_8000B838_main(work->file);
    slot = InitEspriteSlot(spr, work->prio, 1);
    func_8000BCC8_main(slot, 1);
    x = tx = work->x;
    y = ty = work->y;
    func_8000BBD4_main(slot, x, y);
    func_8000BB94_main(slot);
    shown = 0;
    alpha = 0;
    step = 0;
    prevIdx = work->idx;
    t = 0;
    prevState = work->state;
    startX = x;
    startY = y;
    dy = 0;
    dx = 0;
    while (1) {
        if (prevState != work->state) {
            switch (work->state) {
            case 0:
                break;
            case 1:
                step = 0x40;
                if (shown == 0) {
                    alpha = 0;
                    func_8000BBFC_main(slot, 0);
                    func_8000BB54_main(slot);
                    shown = 1;
                }
                break;
            case 2:
                if (shown != 0) {
                    step = -0x40;
                }
                break;
            case -1:
                func_8000C184_main(slot);
                HuSprKill(spr);
                work->state = 100;
                while (1) {
                    HuPrcVSleep();
                }
            }
            prevState = work->state;
        }
        if (prevIdx != work->idx) {
            prevIdx = work->idx;
            if (work->pos != NULL) {
                xy[0] = work->pos[prevIdx][0];
                xy[1] = work->pos[prevIdx][1];
            }
        }
        if (tx != xy[0] || ty != xy[1]) {
            tx = xy[0];
            ty = xy[1];
            t = work->time;
            if (t != 0) {
                startX = x;
                startY = y;
                dx = tx - x;
                dy = ty - y;
            }
        }
        if (step != 0) {
            alpha += step;
            if (alpha >= 0x100) {
                alpha = 0xFF;
                step = 0;
            } else if (alpha < 0) {
                alpha = 0;
                step = 0;
                func_8000BB94_main(slot);
                shown = 0;
            }
            func_8000BBFC_main(slot, alpha);
        }
        if ((x != tx) | (y != ty)) {
            if (t == 0) {
                x = tx;
                y = ty;
            } else {
                t--;
                s = sindf((90.0f / work->time) * (work->time - t));
                x = startX + dx * s;
                y = startY + dy * s;
            }
            func_8000BBD4_main(slot, x, y);
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D6D0_msetup);
#endif

// register allocation only (masked 0): work/slot/y in s4/s3/s2
#ifdef NON_MATCHING
void func_8010DAC4_msetup(omObjData *obj) {
    MsArrowWork *work;
    s32 i;
    s16 slot;
    s16 x;
    s16 y;
    f32 s;

    work = obj->data;

    if (obj->work[0] != obj->work[3]) {
        switch (obj->work[0]) {
        case 0:
            break;
        case 1:
            obj->work[2] = 0;
            func_8000BB54_main(obj->model[0]);
            func_8000BB54_main(obj->model[1]);
            break;
        case 2:
            obj->work[2] = 0xFF;
            break;
        case 3:
            if (obj->work[3] == 4) {
                i = obj->work[2];
                func_8000BBD4_main(obj->model[i], work->pos[i][0], work->pos[i][1]);
            }
            obj->work[2] = 0;
            obj->work[1] = 5;
            work->angle = 360.0f;
            work->speed = -36.0f;
            break;
        case 4:
            if (obj->work[3] == 3) {
                i = obj->work[2];
                func_8000BBD4_main(obj->model[i], work->pos[i][0], work->pos[i][1]);
            }
            obj->work[2] = 1;
            obj->work[1] = 5;
            work->angle = 0.0f;
            work->speed = 36.0f;
            break;
        case 0xFF:
            func_8000C184_main(obj->model[0]);
            func_8000C184_main(obj->model[1]);
            HuSprKill(obj->model[2]);
            HuSprKill(obj->model[3]);
            obj->work[0] = 0;
            break;
        }
        obj->work[3] = obj->work[0];
    }
    switch (obj->work[3]) {
    case 0:
        break;
    case 1:
        i = obj->work[2] + obj->work[1];
        if (i >= 0x100) {
            i = 0xFF;
            obj->work[0] = 0;
        }
        obj->work[2] = i;
        func_8000BBFC_main(obj->model[0], i);
        func_8000BBFC_main(obj->model[1], i);
        break;
    case 2:
        i = obj->work[2] - obj->work[1];
        if (i < 0) {
            i = 0;
            func_8000BB94_main(obj->model[0]);
            func_8000BB94_main(obj->model[1]);
            obj->work[0] = 0;
        }
        obj->work[2] = i;
        func_8000BBFC_main(obj->model[0], i);
        func_8000BBFC_main(obj->model[1], i);
        break;
    case 3:
    case 4:
        i = obj->work[2];
        slot = obj->model[i];
        x = work->pos[i][0];
        y = work->pos[i][1];
        if (obj->work[1] == 0) {
            obj->work[0] = 0;
        } else {
            obj->work[1]--;
            work->angle += work->speed;
            s = sindf(work->angle) * 12.0f;
            x += s;
        }
        func_8000BBD4_main(slot, x, y);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010DAC4_msetup);
#endif

void func_8010DDD8_msetup(omObjData *obj) {
    func_8000C184_main(obj->model[0]);
    func_8000C184_main(obj->model[1]);
    HuSprKill(obj->model[2]);
    HuSprKill(obj->model[3]);
    HuMemFree(obj->data);
    omDelObj(obj);
}

omObjData *func_8010DE38_msetup(s32 x0, s32 x1, s32 y) {
    omObjData *obj;
    MsArrowWork *work;
    s16 spr;
    s16 slot;

    obj = omAddObj(0x17D0, 4, 0, -1, func_8010DAC4_msetup);
    if (obj == NULL) {
        return NULL;
    }
    omSetStatBit(obj, 0x100);
    work = HuMemAllocTag(sizeof(MsArrowWork), 0x7918);
    memset(work, 0, sizeof(MsArrowWork));
    obj->data = work;
    spr = func_8000B838_main(0x140012);
    slot = InitEspriteSlot(spr, 0, 1);
    obj->model[0] = slot;
    obj->model[2] = spr;
    func_8000BCC8_main(slot, 0x4800);
    func_8000BBD4_main(slot, x0, y);
    func_8000BB94_main(slot);
    work->pos[0][0] = x0;
    work->pos[0][1] = y;
    spr = func_8000B838_main(0x140013);
    slot = InitEspriteSlot(spr, 0, 1);
    obj->model[1] = slot;
    obj->model[3] = spr;
    func_8000BCC8_main(slot, 0x4800);
    func_8000BBD4_main(slot, x1, y);
    func_8000BB94_main(slot);
    work->pos[1][0] = x1;
    work->pos[1][1] = y;
    for (slot = 0; slot < 4; slot++) {
        obj->work[slot] = 0;
    }
    return obj;
}

s16 func_8010E00C_msetup(omObjData *obj, s16 count) {
    MsEmitWork *work;

    if (obj == NULL) {
        return 0;
    }
    work = obj->data;
    if (count >= 5) {
        count = 4;
    }
    work->count = count;
    return count;
}

void func_8010E044_msetup(omObjData *obj, s16 idx, s16 arg2, f32 x, f32 y, f32 z) {
    MsEmitWork *work;

    if (obj != NULL) {
        work = obj->data;
        if (idx < work->count) {
            work->pos[idx].x = x;
            work->pos[idx].y = y;
            work->pos[idx].z = z;
            work->range[idx] = arg2;
        }
    }
}

// retail loads model[0] straight into a0 and copies it to s1 (one instruction fewer); otherwise the same
#ifdef NON_MATCHING
void func_8010E09C_msetup(omObjData *obj) {
    MsEmitWork *work;
    Vec *pos;
    s32 model;
    s32 range;
    s32 i;
    f32 dx;
    f32 dz;
    s32 pad[2]; /* retail's frame is 8 bytes larger */

    model = obj->model[0];
    if (obj->work[1] != obj->work[2]) {
        func_8000CD00_main(model, D_80119AF4_msetup, D_80119AF8_msetup, D_80119AFC_msetup[0]);
        obj->work[2] = obj->work[1];
    }
    work = obj->data;
    switch (obj->work[0]) {
    case 0:
        break;
    case 1:
        for (i = 0; i < work->count; i++) {
            range = work->range[i];
            pos = &work->pos[i];
            dx = (rand8() * range / 256 - range / 2);
            dz = (rand8() * range / 256 - range / 2);
            func_8000CD74_main(model, dx + pos->x, pos->y, dz + pos->z);
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E09C_msetup);
#endif

omObjData *func_8010E21C_msetup(void) {
    omObjData *obj;
    MsEmitWork *work;
    MsFxWork *fx;
    s16 model;

    D_80119AF0_msetup = obj = omAddObj(0x17D0, 1, 0, -1, func_8010E09C_msetup);
    if (obj == NULL) {
        return NULL;
    } else {
        omSetStatBit(obj, 0x100);
        work = HuMemAllocTag(sizeof(MsEmitWork), 0x7918);
        memset(work, 0, sizeof(MsEmitWork));
        obj->data = work;
        model = func_8000CBA0_main(0x110012, 0x289);
        obj->model[0] = model;
        fx = MS_FX_WORK(model);
        fx->origin.x = fx->origin.y = fx->origin.z = 0.0f;
        fx->spread = 100.0f;
        obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
        obj->work[0] = 0;
        obj->work[1] = 0;
        obj->work[2] = 0xFF;
        obj->work[3] = 0;
        return obj;
    }
}

void func_8010E32C_msetup(MsLift *lifts, s32 count, f32 rotY, s32 link) {
    MsLift *lift;
    Vec *rot;
    s32 i;
    s16 model;
    s16 base;

    base = -1;
    for (i = 0; i < count; i++) {
        if ((base < 0) | (link == 0)) {
            model = base = func_8000B108_main(0x140003, 0x2A9);
        } else {
            model = Hu3DModelLink(base);
        }
        lifts[i].model = model;
        lifts[i].unk20 = 0;
        lift = &lifts[i];
        rot = &lift->rot;
        rot->x = rot->z = 0.0f;
        if (i != 0) {
            rot->y = rotY + 180.0f;
        } else {
            rot->y = rotY;
        }
        Hu3DModelRotSet(model, rot->x, rot->y, rot->z);
        lift->pos = D_80119B20_msetup;
        Hu3DModelPosSet(model, lift->pos.x, lift->pos.y, lift->pos.z);
        Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
        HuPrcVSleep();
    }
}


void func_8010E4BC_msetup(MsLift *lifts, s32 count, f32 rotY) {
    func_8010E32C_msetup(lifts, count, rotY, 1);
}

void func_8010E4D8_msetup(MsLift *lifts, s32 count) {
    s32 i;

    for (i = 0; i < count; i++, lifts++) {
        func_8001C514_main(lifts->model);
    }
}

void func_8010E52C_msetup(MsLift *lifts, MsLiftKey *keys, s16 count, s16 frames, s16 *models, u16 nmodels,
                         f32 scale0, f32 scale1) {
    Vec pos;
    MsLift *lift;
    MsLiftKey *key;
    Vec *rot;
    f32 dscale;
    f32 t;
    f32 ry;
    f32 scale;
    s32 i;
    s32 j;
    s32 k;
    s16 model;

    dscale = scale1 - scale0;
    for (i = 0; i < frames; i++) {
        t = (f32)i / frames;
        for (j = 0; j < count; j++) {
            if (lifts[j].unk20 & 1) {
                continue;
            }
            model = lifts[j].model;
            lift = &lifts[j];
            key = &keys[j];
            pos.x = (key->pos.x - lift->pos.x) * t;
            pos.y = (key->pos.y - lift->pos.y) * t;
            pos.z = (key->pos.z - lift->pos.z) * t;
            pos.x += lift->pos.x;
            pos.y += lift->pos.y;
            pos.z += lift->pos.z;
            rot = &lift->rot;
            if (lift->rot.y > 180.0f) {
                scale = lift->rot.y - 360.0f;
                ry = (key->rotY - scale) * t + scale;
            } else {
                ry = (keys[j].rotY - rot->y) * t + rot->y;
            }
            Hu3DModelRotSet(model, rot->x, ry, rot->z);
            Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        }
        scale = scale0 + t * dscale;
        if (models != NULL) {
            for (k = 0; k < (s16)nmodels; k++) {
                if (models[k] >= 0) {
                    Hu3DModelScaleSet(models[k], scale, scale, scale);
                }
            }
        }
        HuPrcVSleep();
    }
    for (j = 0; j < count; j++) {
        if (lifts[j].unk20 & 1) {
            continue;
        }
        model = lifts[j].model;
        lift = &lifts[j];
        lift->pos = keys[j].pos;
        lift->rot.y = keys[j].rotY;
        Hu3DModelPosSet(model, lift->pos.x, lift->pos.y, lift->pos.z);
        Hu3DModelRotSet(model, lift->rot.x, lift->rot.y, lift->rot.z);
    }
    if (models != NULL) {
        for (k = 0; k < (s16)nmodels; k++) {
            if (models[k] >= 0) {
                Hu3DModelScaleSet(models[k], scale1, scale1, scale1);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E8C8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010EB94_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F2BC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F2F4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F320_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F33C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F43C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F4E0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F87C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8011035C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80110954_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80111650_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6E4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6FC_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A708_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A714_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A720_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A72C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A738_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A744_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A74C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A754_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A75C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A764_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A76C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A774_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A77C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A784_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A78C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A794_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A79C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7A4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7AC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80112804_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80112E08_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80112F5C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801132C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801138F8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113DEC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113E20_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113E54_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113E88_msetup);

s32 func_80113ED4_msetup(MsSetupWork *arg0) {
#define MODE_PARTY 0
#define MODE_DUEL 1
#define FLAG_WALUIGIS_ISLAND 0x31
#define FLAG_BACKTRACK 0x30
    MsLift sp20[2];
    s16 unk_68;
    s32 *mainFSArray;
    s32 boardCountMaxCopy;
    f32 var_f20;
    void *temp_v0_4;
    omObjData *temp_s5;
    s16 prevBoardIndex;
    s16 backgroundEspriteSlot;
    s16 var_s6;
    s32 pad;
    s32 var_fp;
    s32 boardCountMax;
    s32 *boardDescriptionId;
    s16 curBoardIndex;
    s16 temp;
    s32 i;
    f32 tempFloat;

    boardDescriptionId = NULL;
    mainFSArray = NULL;
    curBoardIndex = D_8011AA45_msetup;
    arg0->unk4 = 0;
    backgroundEspriteSlot = -1;
    var_s6 = -1;
    boardCountMax = 6;
    var_fp = 70;
    tempFloat = 1.0f;

    switch (D_8011A938_msetup) { // current mode
        case MODE_PARTY:
            boardDescriptionId = D_80119EC4_msetup;
            mainFSArray = D_80119E94_msetup; // party mode board backgrounds
            tempFloat = 1.0f;
            var_fp = 74;
            boardCountMax = 5;
            if (_CheckFlag(FLAG_WALUIGIS_ISLAND) != 0) {
                boardCountMax = 6;
            }
            break;
        case MODE_DUEL:
            boardDescriptionId = D_80119EE0_msetup;
            mainFSArray = D_80119EAC_msetup; // duel mode board backgrounds
            var_fp = 74;
            boardCountMax = 5;
            if (_CheckFlag(FLAG_BACKTRACK) != 0) {
                boardCountMax = 6;
            }
            break;
    }

    func_8010B998_msetup();
    func_8010E4BC_msetup(sp20, 2, 0.0f);
    func_8010E4D8_msetup(sp20, 2);
    temp = sp20[0].model;
    temp_s5 = func_8010DE38_msetup(0x40, 0x100, 0x48);
    func_8010B82C_msetup(boardDescriptionId[6]);
    func_8010B858_msetup();
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(sp20, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    func_8001C258_main(sp20[1].model, 4, 4);

    for (var_f20 = 0.0f; var_f20 < 180.0f; var_f20 += (180.0f / 7.0f)) {
        Hu3DModelRotSet(temp, 0, var_f20, 0);
        HuPrcVSleep();
    }

    Hu3DModelRotSet(temp, 0, 180.0f, 0);
    temp_s5->work[0] = 1;
    temp_s5->work[1] = 36;

    for (var_f20 = 1.0f; var_f20 < 2.5f; var_f20 += (3.0f / 14.0f)) {
        Hu3DModelScaleSet(temp, var_f20, var_f20, var_f20);
        HuPrcVSleep();
    }

    Hu3DModelScaleSet(temp, 2.5f, 2.5f, 2.5f);
    prevBoardIndex = -1;
    pad = func_8010D684_msetup(D_8011A948_msetup, &unk_68);
    boardCountMaxCopy = boardCountMax;
    while (1) {
        pad = func_8010D684_msetup(D_8011A948_msetup, &unk_68);
        if (pad & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        if (pad & B_BUTTON) {
            HuAudFXPlay(4);
            curBoardIndex = -1;
            break;
        }
        if (pad & (U_JPAD | R_JPAD)) {
            curBoardIndex++;
            curBoardIndex = (boardCountMaxCopy <= curBoardIndex) ? 0 : curBoardIndex;
            HuAudFXPlay(1);
            temp_s5->work[0] = 4;
        } else {
            if (pad & (D_JPAD | L_JPAD)) {
                if (--curBoardIndex < 0) {
                    curBoardIndex = boardCountMax - 1;
                }
                HuAudFXPlay(1);
                temp_s5->work[0] = 3;
            }
        }
        // check if background image should update
        if (prevBoardIndex != curBoardIndex) {
            if (backgroundEspriteSlot >= 0) {
                for (i = 255; i > 0; i -= (255 / 5)) {
                    func_8000BBFC_main(backgroundEspriteSlot, i);
                    HuPrcVSleep();
                }
                func_8000C184_main(backgroundEspriteSlot);
                HuSprKill(var_s6);
            }
            temp_v0_4 = DataReadTemp(mainFSArray[curBoardIndex]);
            var_s6 = func_80055810_main(temp_v0_4);
            DataCloseTemp(temp_v0_4);
            backgroundEspriteSlot = InitEspriteSlot(var_s6, 0, 1);
            func_8000BC48_main(backgroundEspriteSlot, 0x1000);
            func_8000BCC8_main(backgroundEspriteSlot, 1);
            func_8000BBD4_main(backgroundEspriteSlot, 0xA0, var_fp);
            func_8000BE5C_main(backgroundEspriteSlot, tempFloat, tempFloat);
            for (i = 0; i < 255; i += (255 / 5)) {
                func_8000BBFC_main(backgroundEspriteSlot, i);
                HuPrcVSleep();
            }
            func_8000BBFC_main(backgroundEspriteSlot, 0xFF);
            prevBoardIndex = curBoardIndex;
            func_8010B82C_msetup(boardDescriptionId[curBoardIndex]);
        }
        HuPrcVSleep();
    }

    arg0->unk4 = curBoardIndex;
    if (curBoardIndex >= 0) {
        D_8011AA45_msetup = curBoardIndex;
    }

    temp_s5->work[0] = 2;
    temp_s5->work[1] = 17;

    for (i = 255; i > 0; i -= (255 / 5)) {
        func_8000BBFC_main(backgroundEspriteSlot, i);
        HuPrcVSleep();
    }

    func_8000BBFC_main(backgroundEspriteSlot, 0);

    for (var_f20 = 2.5f; var_f20 > 1.0f; var_f20 += -(3.0f / 14.0f)) {
        Hu3DModelScaleSet(temp, var_f20, var_f20, var_f20);
        HuPrcVSleep();
    }

    Hu3DModelScaleSet(temp, 1.0f, 1.0f, 1.0f);

    for (var_f20 = 180.0f; var_f20 < 360.0f; var_f20 += (180.0f / 7.0f)) {
        Hu3DModelRotSet(temp, 0, var_f20, 0);
        HuPrcVSleep();
    }

    Hu3DModelRotSet(temp, 0, 0.0f, 0);
    func_8001C258_main(sp20[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(sp20, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);

    if (curBoardIndex >= 0) {
        func_8010F320_msetup(D_80119420_msetup, 0, sp20[0].model, -1);
        func_8010F320_msetup(D_80119420_msetup, 2, backgroundEspriteSlot, var_s6);
        func_8001ACDC_main(sp20[1].model);
    } else {
        for (i = 0; i < 2; i++) {
            func_8001ACDC_main(sp20[i].model);
        }
        func_8000C184_main(backgroundEspriteSlot);
        HuSprKill(var_s6);
    }
    func_8010DDD8_msetup(temp_s5);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801145D0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80114AA0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801150A0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801152C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801157B8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115A9C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115E78_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7E0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7E8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7F8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A800_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115EE0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801167B8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80116FE0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117818_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117820_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117910_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117A3C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80118D48_msetup);
