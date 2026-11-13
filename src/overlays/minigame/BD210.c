#include "common.h"

#include "game/hmfman.h"
#include "mallocblock.h"

/* A star-burst effect object (omObjData::data): two rings of ten sparkle sprites (MP1 src/6C470.c). */
typedef struct MgStarPart {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 radius;
    /* 0x10 */ f32 angle;
    /* 0x14 */ f32 scale;
    /* 0x18 */ s16 state;
    /* 0x1A */ s16 timer;
} MgStarPart; // Size 0x1C

typedef struct MgStarWork {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ void (*func4)(void);
    /* 0x008 */ void (*func8)(omObjData*);
    /* 0x00C */ void (*funcC)(omObjData*);
    /* 0x010 */ f32 unk10; /* target */
    /* 0x014 */ f32 unk14;
    /* 0x018 */ f32 unk18;
    /* 0x01C */ f32 unk1C; /* ground height for the shadow */
    /* 0x020 */ s32 unk20; /* state */
    /* 0x024 */ MgStarPart parts[10];
    /* 0x13C */ MgStarPart parts2[10];
    /* 0x254 */ s16 sprites[23];
    /* 0x282 */ u16 unk282;
    /* 0x284 */ u16 unk284;
    /* 0x286 */ u16 unk286;
    /* 0x288 */ u16 unk288;
    /* 0x28A */ u16 unk28A;
    /* 0x28C */ u16 unk28C;
    /* 0x28E */ u16 unk28E;
} MgStarWork; // Size 0x290

/* An entry of D_800CBB60_main (0x24 bytes; src/14EA0.c's unk_800ECDE0). */
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[0x22];
} MgSprModel;

extern MgSprModel* D_800CBB60_main;
extern s16 D_800EBE00_minigame[4]; /* models and sprites shared by every star burst */

u16 SprModelRead(s32 arg0, s32 arg1, s32 arg2);
s16 func_8000B0D4_main(s32, s32);
u16 func_80014618_main(s16 index, u16 arg1);
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
void func_80014714_main(s16 index, u16 arg1);
void func_80014794_main(s16 index, u8 arg1);
void func_800147FC_main(s16 index, u8 arg1, u8 arg2, u8 arg3);

void func_800EAA58_minigame(omObjData* obj);
void func_800EAE14_minigame(omObjData* obj);
s32 func_800EAE7C_minigame(omObjData* obj);
void func_800EB3CC_minigame(omObjData* obj);
void func_800EB5E4_minigame(omObjData* obj);

void func_800EA690_minigame(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800EBE00_minigame[i] = -1;
    }
}

omObjData* func_800EA6C4_minigame(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    omObjData* obj;
    MgStarWork* w;
    s16* mdl;
    s32 i;

    obj = omAddObj(arg0, 0x17, 0, -1, func_800EAA58_minigame);
    mdl = obj->model;
    for (i = 0; i < 0x17; i++) {
        *mdl++ = -1;
    }
    w = HuMemAllocTag(sizeof(*w), 0x7918);
    obj->data = w;
    memset(w, 0, sizeof(*w));
    w->unk282 = arg1;
    w->unk284 = arg2;
    w->unk286 = arg3;
    w->unk288 = arg4;
    w->unk28A = 0x18;
    w->unk28C = 0x78;
    w->unk28E = 1;
    w->unk20 = 0;
    w->func4 = NULL;
    w->func8 = func_800EB3CC_minigame;
    w->funcC = func_800EB5E4_minigame;
    return obj;
}

void func_800EA7D0_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
}

void func_800EA7E0_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    obj->rot.x = x;
    obj->rot.y = y;
    obj->rot.z = z;
}

/* Retail sets the glow model's position, not its scale, to 3 * y (as MP1). */
void func_800EA7F0_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    MgStarWork* w = obj->data;
    s16 mdl;
    f32 s;

    obj->scale.x = x;
    obj->scale.y = y;
    obj->scale.z = z;
    w->unk28C = y * 120.0f;
    w->unk28E = y;
    mdl = obj->model[2];
    if (mdl >= 0) {
        s = y * 3.0f;
        Hu3DModelPosSet(mdl, s, s, s);
    }
}

void func_800EA8F0_minigame(omObjData* obj, f32 arg1) {
    ((MgStarWork*)obj->data)->unk1C = arg1;
}

void func_800EA8FC_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    MgStarWork* w = obj->data;

    w->unk10 = x;
    w->unk14 = y;
    w->unk18 = z;
}

void func_800EA910_minigame(omObjData* obj, s32 arg1) {
    ((MgStarWork*)obj->data)->unk20 = arg1;
}

s32 func_800EA91C_minigame(omObjData* obj) {
    return ((MgStarWork*)obj->data)->unk20;
}

void func_800EA928_minigame(omObjData* obj, u16 mode) {
    s16 mdl = obj->model[0];
    MgStarPart* p;
    s16 i;

    if (mdl >= 0) {
        switch (mode) {
        case 0:
            func_8001C6A8_main(mdl, 0.0f);
            break;
        case 4:
            p = ((MgStarWork*)obj->data)->parts;
            for (i = 10; i != 0; i--) {
                p->state = 0;
                p++;
            }
            p = ((MgStarWork*)obj->data)->parts2;
            for (i = 10; i != 0; i--) {
                p->state = 0;
                p++;
            }
            break;
        }
        func_8001C258_main(mdl, 4, mode);
        func_8001C258_main(obj->model[1], 4, mode);
        for (i = 2; i < 0x17; i++) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
}

void func_800EAA58_minigame(omObjData* obj) {
    MgStarWork* w = obj->data;
    u16 idx;
    s16 sprite;
    s32 i;
    s16 j;
    s16 k;

    if (D_800EBE00_minigame[0] < 0) {
        idx = func_8000B108_main(0x1C, w->unk282);
        D_800EBE00_minigame[0] = idx;
    } else {
        idx = Hu3DModelLink(D_800EBE00_minigame[0]);
    }
    obj->model[0] = idx;
    func_8001C814_main(idx, 1, 1);
    if (D_800EBE00_minigame[1] < 0) {
        idx = func_8000B0D4_main(w->unk288 == 0 ? 1 : 9, w->unk284);
        D_800EBE00_minigame[1] = idx;
    } else {
        idx = Hu3DModelLink(D_800EBE00_minigame[1]);
    }
    obj->model[1] = idx;
    if (D_800EBE00_minigame[2] < 0) {
        sprite = SprModelRead(0xC, w->unk286 | 4, 8);
        D_800EBE00_minigame[2] = sprite;
    } else {
        sprite = func_80014618_main(D_800EBE00_minigame[2], 8);
    }
    w->sprites[2] = sprite;
    idx = D_800CBB60_main[sprite].unk00;
    obj->model[2] = idx;
    func_8001C258_main(idx, 4, 4);
    func_80014794_main(sprite, 0xC0);
    func_800147FC_main(sprite, 0xFF, 0xFF, 0xBE);
    func_8001C2FC_main(idx, 0x70000000, 0x70000000);
    func_800146DC_main(sprite, 4, 0);
    Hu3DModelScaleSet(idx, w->unk28E * 3.0f, w->unk28E * 3.0f, w->unk28E * 3.0f);
    for (j = 3, k = 13, i = 0; i < 10; i++, j++, k++) {
        if (D_800EBE00_minigame[3] < 0) {
            sprite = SprModelRead(0xA, w->unk286, 8);
            D_800EBE00_minigame[3] = sprite;
        } else {
            sprite = func_80014618_main(D_800EBE00_minigame[3], 8);
        }
        w->sprites[j] = sprite;
        idx = D_800CBB60_main[sprite].unk00;
        obj->model[j] = idx;
        func_8001C2FC_main(idx, 0x70000000, 0x70000000);
        Hu3DModelScaleSet(idx, 2.0f, 2.0f, 2.0f);
        func_8001C258_main(idx, 4, 4);
        sprite = func_80014618_main(D_800EBE00_minigame[3], 8);
        w->sprites[k] = sprite;
        idx = D_800CBB60_main[sprite].unk00;
        obj->model[k] = idx;
        func_8001C2FC_main(idx, 0x70000000, 0x70000000);
        Hu3DModelScaleSet(idx, 2.0f, 2.0f, 2.0f);
        func_8001C258_main(idx, 4, 4);
        func_80014794_main(sprite, i * 15 + 0x60);
    }
    obj->func = func_800EAE14_minigame;
}

void func_800EAE14_minigame(omObjData* obj) {
    MgStarWork* w = obj->data;

    if (w->func4 != NULL) {
        w->func4();
    }
    if (w->func8 != NULL) {
        w->func8(obj);
    }
    if (w->funcC != NULL) {
        w->funcC(obj);
    }
}

// NON_MATCHING: register choice and scheduling (masked 6), as MP1 func_8006C058: f2/f6 for the
// spilled grow/shrink step, and the obj->model load is scheduled before the multiplies.
#ifdef NON_MATCHING
/* Moves the sparkles; the number still active. */
s32 func_800EAE7C_minigame(omObjData* obj) {
    MgStarWork* w = obj->data;
    MgStarPart* p;
    s32 count;
    f32 grow;
    f32 shrink;
    f32 maxScale;
    f32 ang;
    f32 c;
    f32 s;
    f32 x;
    f32 y;
    f32 z;
    f32 sc;
    f32 t;
    s32 i;
    s16 mdl;

    count = 0;
    grow = 4.0f / w->unk28A;
    shrink = -1.6f / w->unk28A;
    maxScale = 2.0f * w->unk28E;
    ang = CRot.y + 90.0f;
    p = w->parts;
    if (ang > 360.0f) {
        ang -= 360.0f;
    }
    c = sindf(ang);
    s = cosdf(ang);
    for (i = 3; i < 23; p++, i++) {
        if (i == 13) {
            p = w->parts2;
        }
        if (p->state == 0) {
            continue;
        }
        mdl = obj->model[i];
        count++;
        switch (p->state) {
            case 1:
                if (p->timer != 0) {
                    p->timer--;
                    break;
                }
                p->state = 2;
                p->timer = w->unk28A;
                Hu3DModelScaleSet(mdl, p->scale, p->scale, p->scale);
                y = sindf(p->angle) * p->radius;
                x = y * c;
                z = y * s;
                y = cosdf(p->angle) * p->radius;
                x += p->x;
                y += p->y;
                z += p->z;
                Hu3DModelPosSet(mdl, x, y, z);
                func_8001C258_main(mdl, 4, 0);
                if (i == 3) {
                    func_8001C258_main(obj->model[2], 4, 0);
                    Hu3DModelPosSet(obj->model[2], x + c * 10.0f, y - 10.0f, z + s * 10.0f);
                    func_800146DC_main(w->sprites[2], 4, 4);
                }
                break;
            case 2:
                if (p->timer != 0 && p->scale < maxScale) {
                    sc = grow + p->scale;
                    goto update;
                }
                p->state = 3;
                break;
            case 3:
                if (p->timer != 0) {
                    sc = shrink + p->scale;
            update:
                p->scale = sc;
                Hu3DModelScaleSet(mdl, sc, sc, sc);
                x = w->unk10 - p->x;
                y = w->unk14 - p->y;
                z = w->unk18 - p->z;
                t = p->timer;
                x /= t;
                y /= t;
                z /= t;
                p->x = x + p->x;
                p->y = y + p->y;
                p->z = z + p->z;
                y = sindf(p->angle) * p->radius;
                x = y * c;
                z = y * s;
                y = cosdf(p->angle) * p->radius;
                x += p->x;
                y += p->y;
                z += p->z;
                Hu3DModelPosSet(mdl, x, y, z);
                if (i == 3) {
                    Hu3DModelPosSet(obj->model[2], x + c * 10.0f, y - 10.0f, z + s * 10.0f);
                    func_80014714_main(w->sprites[2], p->timer % 8);
                }
                p->radius -= p->radius / p->timer;
                p->angle += 450.0f / w->unk28A;
                if (p->angle > 360.0f) {
                    p->angle -= 360.0f;
                } else if (p->angle < 0.0f) {
                    p->angle += 360.0f;
                }
                p->timer--;
                } else {
                    p->state = 0;
                    func_8001C258_main(mdl, 4, 4);
                    if (i < 13) {
                        HuAudFXPlay(0);
                    }
                }
                break;
        }
    }
    return count;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BD210", func_800EAE7C_minigame);
#endif

/* State machine: 1 starts the burst motion, 2 waits for its end and launches the sparkles,
   3 runs them until none is left. */
void func_800EB3CC_minigame(omObjData* obj) {
    MgStarWork* w = obj->data;
    MgStarPart* p;
    s16 mdl;
    s32 i;
    s32 t;
    f32 cur;

    if (w->unk20 > 0) {
        mdl = obj->model[0];
        switch (w->unk20) {
            case 1:
                func_8001C814_main(mdl, 1, 0);
                w->unk20 = 2;
                HuAudFXPlay(0);
                break;
            case 2:
                cur = HmfModelData[mdl].unk40;
                if (D_800CCF58_main[HmfModelData[mdl].unk02].unk02 <= cur) {
                    w->unk20 = 3;
                    p = w->parts;
                    t = 0;
                    for (i = 0; i < 10; i++, p++) {
                        p->timer = t;
                        t += 2;
                        p->radius = w->unk28C;
                        p->angle = 180.0f;
                        p->scale = w->unk28E;
                        p->state = 1;
                        p->x = obj->trans.x;
                        p->y = obj->trans.y + p->radius;
                        p->z = obj->trans.z;
                    }
                    p = w->parts2;
                    t--;
                    for (i = 0; i < 10; i++, p++) {
                        p->timer = t;
                        t++;
                        p->radius = w->unk28C;
                        p->angle = 180.0f;
                        p->scale = w->unk28E;
                        p->state = 1;
                        p->x = obj->trans.x;
                        p->y = obj->trans.y + p->radius;
                        p->z = obj->trans.z;
                    }
                }
                break;
            case 3:
                if (func_800EAE7C_minigame(obj) == 0) {
                    w->unk20 = 0;
                }
                break;
        }
    }
}

/* The shadow (model 1): on the ground below, shrinking with the height. */
void func_800EB5E4_minigame(omObjData* obj) {
    MgStarWork* w = obj->data;
    s16 mdl = obj->model[1];
    f32 d;
    f32 s;

    Hu3DModelPosSet(mdl, obj->trans.x, w->unk1C, obj->trans.z);
    d = obj->trans.y - w->unk1C - obj->scale.y * 50.0f;
    if (!w->unk288) {
        s = obj->scale.y * 0.58f;
    } else {
        s = obj->scale.y * 1.2f;
    }
    if (d < 0.0f) {
        d = s;
    } else {
        d = s - (d * 0.002f);
        if (d < 0.00001f) {
            d = 0.00001f;
        }
    }
    Hu3DModelScaleSet(mdl, d, d, d);
    Hu3DModelRotSet(mdl, obj->rot.x, obj->rot.y, obj->rot.z);
}
