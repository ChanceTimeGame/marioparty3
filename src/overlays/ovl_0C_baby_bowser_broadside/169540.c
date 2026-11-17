#include "common.h"

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_80109ED0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_80109F64_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A0B4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A158_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A1B0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A264_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A2C4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A3C8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A598_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A738_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A7CC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A81C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A8C4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A9D4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010AADC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010AB80_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010ACF8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010AE60_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010AFF4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B098_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B198_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B328_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B360_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B3B4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B54C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010BCBC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010C8D4_baby_bowser_broadside);

// m1 bb3: collider system shared with tick_tock_hop/motor_rooter (system.c); copies of their helpers below
#include "ultra64.h"
#include "math.h"
#include "gcc/memory.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/util.h"
#include "mallocblock.h"

#define BB3_ABS(x) ((x) > 0 ? (x) : -(x))
#define BB3_M_ID(m, i, j) ((m)[(i) * 4 + (j)])
#define BB3_VECMagXZ(a) sqrtf(((a)->x * (a)->x) + ((a)->z * (a)->z))
#define BB3_COLLIDERS_MAX 12

f32 atan2df(f32, f32);
f32 sqrtf(f32);

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} BbRGBA;

typedef struct {
    /* 0x00 */ Vec normal;
    /* 0x0C */ f32 dist;
    /* 0x10 */ s8 axis; // dominant normal axis: 0 x, 1 y, 2 z
} BbPlane; // Size 0x14

// Collider attr bits: 1 disabled, 2 no height test, 4 recompute plane, 8 transform from model,
// 0x10 detect only (no push), 0x20 two-sided, 0x40 follows parent, 0x80 sets the mover's attr bit 1,
// 0x100 plane, 0x200 sphere, 0x400 cylinder, none of these: vertical prism.
typedef struct {
    /* 0x00 */ s32 attr;
    /* 0x04 */ s8 set;
    /* 0x08 */ f32 *posX;
    /* 0x0C */ f32 *posY;
    /* 0x10 */ f32 *posZ;
    /* 0x14 */ f32 *rotX;
    /* 0x18 */ f32 *rotY;
    /* 0x1C */ f32 *rotZ;
    /* 0x20 */ f32 transMtx[16];
    /* 0x60 */ Vec base[4];
    /* 0x90 */ Vec cur[4];
    /* 0xC0 */ s16 vertexCount;
    /* 0xC4 */ f32 height;
    /* 0xC8 */ BbPlane plane;
    /* 0xDC */ f32 radius;
    /* 0xE0 */ s16 parent;
} BbCollider; // Size 0xE4

typedef struct {
    /* 0x00 */ s32 attr;
    /* 0x04 */ s16 *colliders;
    /* 0x08 */ s16 count;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ f32 radius;
    /* 0x28 */ s16 model;
    /* 0x2A */ s16 hitPlane;
    /* 0x2C */ s16 hitPrism;
    /* 0x2E */ s16 hitSphere;
    /* 0x30 */ s16 hitCylinder;
} BbMover;

typedef struct {
    /* 0x00 */ char unk00[0x40];
    /* 0x40 */ void (*func)(void *, void *);
} BbFuncContext;

extern u8 D_800D2008_main;
extern const f64 D_8010FFE8_baby_bowser_broadside; // 32.0
extern const f64 D_8010FFF0_baby_bowser_broadside; // 0.5
extern BbCollider *D_80110020_baby_bowser_broadside;

void func_8010DE70_baby_bowser_broadside(void *groupCtx, void *ctx);
s16 func_8010E348_baby_bowser_broadside(BbCollider *c, BbMover *m);
s16 func_8010E538_baby_bowser_broadside(BbCollider *c, BbMover *m);
s16 func_8010E710_baby_bowser_broadside(BbCollider *c, BbMover *m);
s16 func_8010E9FC_baby_bowser_broadside(BbCollider *c, Vec *p);
f32 func_8010ED1C_baby_bowser_broadside(BbCollider *c, Vec *p);
s16 func_8010EDC0_baby_bowser_broadside(BbCollider *c, BbMover *m);
f32 func_8010F004_baby_bowser_broadside(BbMover *m, Vec *a, Vec *b);
void func_8010F3C4_baby_bowser_broadside(Vec *v, BbPlane *out);
void func_8010F878_baby_bowser_broadside(f32 *out);
void func_8010F900_baby_bowser_broadside(f32 *out, f32 x, f32 y, f32 z);
void func_8010F958_baby_bowser_broadside(f32 *out, f32 angle);
void func_8010F9C0_baby_bowser_broadside(f32 *out, f32 angle);
void func_8010FA28_baby_bowser_broadside(f32 *a, f32 *b, f32 *out);
void func_8010FB74_baby_bowser_broadside(f32 transX, f32 transY, f32 transZ, f32 rotX, f32 rotY, f32 rotZ, f32 *out);
void func_8010FC2C_baby_bowser_broadside(Vec *in, s16 n, f32 *mtx, Vec *out);
// end m1 bb3

void func_8010D4C0_baby_bowser_broadside(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2) {
    HmfModel *model = &HmfModelData[modelId];
    HmfData *temp_s2 = model->hmf;
    HmfModelData_Unk64_Unk3C_Struct *temp_v1 = temp_s2->unk3C;
    Gfx *temp_s0 = temp_v1->unk00[D_800D2008_main + 1];

    temp_v1->unk00[0] = temp_s0;
    gDPPipeSync(&temp_s0[0]);
    gSPSegment(&temp_s0[1], 0x02, osVirtualToPhysical(arg1->unk00[arg2].unk00));
    gSPDisplayList(&temp_s0[2], osVirtualToPhysical(temp_s2->unk3C->unk10));
    gDPPipeSync(&temp_s0[3]);
    gSPEndDisplayList(&temp_s0[4]);
}

void func_8010D590_baby_bowser_broadside(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, BbRGBA *arg3) {
    HmfModel *model = &HmfModelData[modelId];
    HmfData *temp_s3 = model->hmf;
    HmfModelData_Unk64_Unk3C_Struct *temp_v1 = temp_s3->unk3C;
    Gfx *temp_s0 = temp_v1->unk00[D_800D2008_main + 1];

    temp_v1->unk00[0] = temp_s0;
    gDPPipeSync(&temp_s0[0]);
    gSPSegment(&temp_s0[1], 0x02, osVirtualToPhysical(arg1->unk00[arg2].unk00));
    gSPDisplayList(&temp_s0[2], osVirtualToPhysical(temp_s3->unk3C->unk10));
    gDPSetPrimColor(&temp_s0[3], 0, 0, arg3->r, arg3->g, arg3->b, arg3->a);
    gDPPipeSync(&temp_s0[4]);
    gSPDisplayList(&temp_s0[5], osVirtualToPhysical(temp_s3->unk3C->unk14));
    gDPPipeSync(&temp_s0[6]);
    gSPEndDisplayList(&temp_s0[7]);
}

s16 func_8010D6C4_baby_bowser_broadside(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
    Vtx *temp_s7;
    Vtx *var_s1;
    Vtx_t *var_t0;
    Vtx_t *var_a3;
    s32 var_a2;
    s32 temp_s4;
    s32 temp_a1;
    s32 sp24;
    s32 temp_f2;
    s32 var_s0;
    s32 var_s2;
    s32 sp2C;
    s32 temp_lo;
    s32 temp_s3;
    s32 var_s0_2;
    s32 var_a2_2;

    if (arg0->unk1A >= 2) {
        var_a2 = 0x800;
    } else {
        var_a2 = 0x1000;
    }
    temp_s4 = arg0->unk00->unk04;
    temp_a1 = arg0->unk00->unk06;
    sp24 = (f64)(temp_s4 * 0x64) * arg2 / D_8010FFE8_baby_bowser_broadside;
    temp_f2 = (f64)(temp_a1 * 0x64) * arg2 / D_8010FFE8_baby_bowser_broadside;
    if ((arg0->unk18 & 0xFFF) == 4) {
        var_s0 = ((temp_s4 + 1) & 0xFFFE) * temp_a1 * 4;
    } else {
        var_s0 = temp_s4 * temp_a1 * arg0->unk18;
    }
    var_s0 = (var_s0 < 0) ? (var_s0 + 7) : var_s0;
    var_s0 >>= 3;
    var_s2 = var_s0 / var_a2;
    if (var_s2 <= 0) {
        var_s2 = 1;
    }
    sp2C = temp_a1 / var_s2;
    temp_lo = temp_f2 / var_s2;
    temp_s3 = var_s2 * 4;
    temp_s7 = var_s1 = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
    memset(temp_s7, 0, temp_s3 * sizeof(Vtx));
    for (var_s0_2 = 0; var_s0_2 < var_s2; var_s0_2++, var_s1 += 4) {
        var_s1[0].v.ob[0] = (s32)(sp24 * D_8010FFF0_baby_bowser_broadside);
        var_s1[0].v.ob[1] = (s32)(temp_f2 * D_8010FFF0_baby_bowser_broadside - temp_lo * var_s0_2);
        var_s1[0].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[0].v.tc[1] = 0;
        var_s1[1].v.ob[0] = (s32)(sp24 * D_8010FFF0_baby_bowser_broadside);
        var_s1[1].v.ob[1] = (s32)(temp_f2 * D_8010FFF0_baby_bowser_broadside - temp_lo * (var_s0_2 + 1));
        var_s1[1].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[1].v.tc[1] = (sp2C - 1) * 64;
        var_s1[2].v.ob[0] = (s32) - (sp24 * D_8010FFF0_baby_bowser_broadside);
        var_s1[2].v.ob[1] = (s32)(temp_f2 * D_8010FFF0_baby_bowser_broadside - temp_lo * var_s0_2);
        var_s1[2].v.tc[0] = 0;
        var_s1[2].v.tc[1] = 0;
        var_s1[3].v.ob[0] = (s32) - (sp24 * D_8010FFF0_baby_bowser_broadside);
        var_s1[3].v.ob[1] = (s32)(temp_f2 * D_8010FFF0_baby_bowser_broadside - temp_lo * (var_s0_2 + 1));
        var_s1[3].v.tc[0] = 0;
        var_s1[3].v.tc[1] = (sp2C - 1) * 64;
        for (var_a2_2 = 0; var_a2_2 < 4; var_a2_2++) {
            var_s1[var_a2_2].v.ob[0] += arg3;
            var_s1[var_a2_2].v.ob[1] += arg4;
            var_s1[var_a2_2].v.ob[2] = 0;
            var_s1[var_a2_2].v.flag = 0;
            var_s1[var_a2_2].v.cn[3] = 0xFF;
            var_s1[var_a2_2].v.cn[0] = var_s1[var_a2_2].v.cn[1] = var_s1[var_a2_2].v.cn[2] = 0;
        }
    }
    var_s1 = temp_s7;
    for (var_s0_2 = 0; var_s0_2 < D_800D1FF0_main; var_s0_2++) {
        arg1->unk44[var_s0_2] = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
        var_t0 = &arg1->unk44[var_s0_2]->v;
        var_a3 = &var_s1->v;
        for (var_a2_2 = 0; var_a2_2 < temp_s3; var_a2_2++) {
            *(var_t0++) = *(var_a3++);
        }
    }
    HuMemFree(temp_s7);
    return var_s2;
}

void func_8010DAE8_baby_bowser_broadside(void *groupCtx, BbFuncContext *ctx) {
    D_80110020_baby_bowser_broadside = HuMemAllocTag(BB3_COLLIDERS_MAX * sizeof(BbCollider), 31000);
    memset(D_80110020_baby_bowser_broadside, 0, BB3_COLLIDERS_MAX * sizeof(BbCollider));
    ctx->func = func_8010DE70_baby_bowser_broadside;
}

s16 func_8010DB38_baby_bowser_broadside(s16 modelId, Vec *base, s16 vertexCount, f32 radius, f32 height, u32 attr) {
    BbCollider *collider = D_80110020_baby_bowser_broadside;
    s16 i;

    for (i = 0; i < BB3_COLLIDERS_MAX; i++, collider++) {
        if (!collider->set) {
            if (modelId != -1) {
                HmfModel *model = &HmfModelData[modelId];

                collider->posX = &model->pos.x;
                collider->posY = &model->pos.y;
                collider->posZ = &model->pos.z;
                collider->rotX = &model->rot.x;
                collider->rotY = &model->rot.y;
                collider->rotZ = &model->rot.z;
            }
            memcpy(collider->base, base, vertexCount * sizeof(Vec));
            collider->radius = radius;
            collider->height = height;
            collider->vertexCount = vertexCount;
            if ((attr & 0x700) <= 0x100) {
                func_8010F3C4_baby_bowser_broadside(collider->base, &collider->plane);
            } else {
                attr &= ~4;
            }
            collider->attr = attr;
            collider->set = TRUE;
            break;
        }
    }
    return i;
}

s16 func_8010DC88_baby_bowser_broadside(s16 parentId, u32 attr) {
    BbCollider *collider = D_80110020_baby_bowser_broadside;
    BbCollider *parent = &D_80110020_baby_bowser_broadside[parentId];
    s16 i;

    for (i = 0; i < BB3_COLLIDERS_MAX; i++, collider++) {
        if (!collider->set) {
            collider->parent = parentId;
            collider->posX = parent->posX;
            collider->posY = parent->posY;
            collider->posZ = parent->posZ;
            collider->rotX = parent->rotX;
            collider->rotY = parent->rotY;
            collider->rotZ = parent->rotZ;
            memcpy(collider->base, parent->base, parent->vertexCount * sizeof(Vec));
            collider->radius = parent->radius;
            collider->height = parent->height;
            collider->vertexCount = parent->vertexCount;
            if ((attr & 0x700) <= 0x100) {
                collider->plane.normal = parent->plane.normal;
            } else {
                attr &= ~4;
            }
            collider->attr = attr | 0x40;
            collider->set = TRUE;
            break;
        }
    }
    return i;
}

void func_8010DDDC_baby_bowser_broadside(s16 colliderId, Vec *base, f32 height) {
    if (colliderId < BB3_COLLIDERS_MAX && D_80110020_baby_bowser_broadside[colliderId].set) {
        BbCollider *collider = &D_80110020_baby_bowser_broadside[colliderId];

        memcpy(collider->base, base, collider->vertexCount * sizeof(Vec));
        collider->height = height;
        func_8010F3C4_baby_bowser_broadside(collider->base, &collider->plane);
    }
}

#ifdef NON_MATCHING
void func_8010DE70_baby_bowser_broadside(void *groupCtx, void *ctx) {
    BbCollider *collider = D_80110020_baby_bowser_broadside;
    s16 i;

    if (collider == NULL) {
        return;
    }
    for (i = 0; i < BB3_COLLIDERS_MAX; i++, collider++) {
        if (!collider->set) {
            continue;
        }
        if (collider->attr & 1) {
            continue;
        }
        if (!(collider->attr & 0x40)) {
            if (collider->attr & 8) {
                func_8010FB74_baby_bowser_broadside(*collider->posX, *collider->posY, *collider->posZ, *collider->rotX,
                                                    *collider->rotY, *collider->rotZ, collider->transMtx);
            } else {
                func_8010F878_baby_bowser_broadside(collider->transMtx);
            }
            func_8010FC2C_baby_bowser_broadside(collider->base, collider->vertexCount, collider->transMtx, collider->cur);
            if (collider->attr & 4) {
                func_8010F3C4_baby_bowser_broadside(collider->cur, &collider->plane);
            }
        } else {
            memcpy(collider->cur, D_80110020_baby_bowser_broadside[collider->parent].cur, collider->vertexCount * sizeof(Vec));
            if (collider->attr & 4) {
                collider->plane = D_80110020_baby_bowser_broadside[collider->parent].plane;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DE70_baby_bowser_broadside);
#endif

void func_8010E018_baby_bowser_broadside(BbMover *mover, s16 maxColliders, f32 radius, s16 modelId) {
    if (mover != NULL) {
        mover->count = maxColliders + 1;
        mover->colliders = HuMemAllocTag(mover->count * sizeof(s16), 31000);
        memset(mover->colliders, -1, mover->count * sizeof(s16));
        mover->pos.x = mover->pos.y = mover->pos.z = 0.0f;
        mover->vel.x = mover->vel.y = mover->vel.z = 0.0f;
        mover->radius = radius;
        mover->model = modelId;
    }
}

void func_8010E0B0_baby_bowser_broadside(BbMover *mover) {
    BbCollider *collider;
    s16 i;

    if (D_80110020_baby_bowser_broadside == NULL) {
        return;
    }
    mover->hitCylinder = 0;
    mover->hitPlane = 0;
    mover->hitPrism = 0;
    mover->hitSphere = 0;
    mover->attr &= ~1;
    if (mover->model != -1) {
        mover->pos.x = HmfModelData[mover->model].pos.x;
        mover->pos.y = HmfModelData[mover->model].pos.y;
        mover->pos.z = HmfModelData[mover->model].pos.z;
    }
    for (i = 1; i < mover->count; i++) {
        if (mover->colliders[i] == -1) {
            continue;
        }
        collider = &D_80110020_baby_bowser_broadside[mover->colliders[i]];
        if (collider->attr & 1) {
            continue;
        }
        if (collider->attr & 0x400) {
            if (func_8010E348_baby_bowser_broadside(collider, mover)) {
                if (!(collider->attr & 0x80)) {
                    mover->hitCylinder = i;
                } else {
                    mover->attr |= 1;
                }
            }
        } else if (collider->attr & 0x200) {
            if (func_8010E538_baby_bowser_broadside(collider, mover)) {
                if (!(collider->attr & 0x80)) {
                    mover->hitSphere = i;
                } else {
                    mover->attr |= 1;
                }
            }
        } else if (collider->attr & 0x100) {
            if (func_8010E710_baby_bowser_broadside(collider, mover)) {
                mover->hitPlane = i;
            }
        } else {
            if (func_8010EDC0_baby_bowser_broadside(collider, mover)) {
                if (collider->attr & 0x80) {
                    mover->attr |= 1;
                } else {
                    mover->hitPrism = i;
                }
            }
        }
    }
    mover->pos.x += mover->vel.x;
    mover->pos.y += mover->vel.y;
    mover->pos.z += mover->vel.z;
    if (mover->model != -1) {
        HmfModelData[mover->model].pos.x = mover->pos.x;
        HmfModelData[mover->model].pos.y = mover->pos.y;
        HmfModelData[mover->model].pos.z = mover->pos.z;
    }
}

s16 func_8010E348_baby_bowser_broadside(BbCollider *c, BbMover *m) {
    f32 range[2];
    Vec pos;
    Vec vel;
    Vec next;
    Vec d;
    f32 half;
    f32 dist;

    pos.x = m->pos.x;
    pos.y = m->pos.y;
    pos.z = m->pos.z;
    vel.x = m->vel.x;
    vel.y = m->vel.y;
    vel.z = m->vel.z;
    next.x = pos.x + vel.x;
    next.y = pos.y + vel.y;
    next.z = pos.z + vel.z;
    half = m->radius * 0.5f;
    range[0] = c->cur[0].y - half;
    range[1] = c->cur[0].y + c->height + half;
    if (!(next.y < range[0])) {
        if (range[1] < next.y) {
            return 0;
        }
        d.x = c->cur[0].x - next.x;
        d.z = c->cur[0].z - next.z;
        dist = HuSqrtf(d.x * d.x + d.z * d.z);
        if (!(dist <= m->radius + c->radius)) {
            return 0;
        }
        if (c->attr & 0x10) {
            return 1;
        }
        if (dist != 0.0f) {
            d.x /= dist;
            d.x *= m->radius + c->radius;
            d.z /= dist;
            d.z *= m->radius + c->radius;
        }
        next.x = c->cur[0].x - d.x;
        next.z = c->cur[0].z - d.z;
    } else {
        return 0;
    }
    vel.x = next.x - pos.x;
    vel.z = next.z - pos.z;
    m->vel.x = vel.x;
    m->vel.y = vel.y;
    m->vel.z = vel.z;
    return 1;
}

s16 func_8010E538_baby_bowser_broadside(BbCollider *c, BbMover *m) {
    Vec pos;
    Vec vel;
    Vec next;
    Vec d;
    f32 dist;

    pos.x = m->pos.x;
    pos.y = m->pos.y;
    pos.z = m->pos.z;
    vel.x = m->vel.x;
    vel.y = m->vel.y;
    vel.z = m->vel.z;
    next.x = pos.x + vel.x;
    next.y = pos.y + vel.y;
    next.z = pos.z + vel.z;
    d.x = c->cur[0].x - next.x;
    d.y = c->cur[0].y - next.y;
    d.z = c->cur[0].z - next.z;
    dist = HuSqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
    if (!(dist <= m->radius + c->radius)) {
        return 0;
    }
    if (!(c->attr & 0x10)) {
        if (dist != 0.0f) {
            d.x /= dist;
            d.x *= m->radius + c->radius;
            d.y /= dist;
            d.y *= m->radius + c->radius;
            d.z /= dist;
            d.z *= m->radius + c->radius;
        }
        next.x = c->cur[0].x - d.x;
        next.y = c->cur[0].y - d.y;
        next.z = c->cur[0].z - d.z;
    } else {
        return 1;
    }
    vel.x = next.x - pos.x;
    vel.y = next.y - pos.y;
    vel.z = next.z - pos.z;
    m->vel.x = vel.x;
    m->vel.y = vel.y;
    m->vel.z = vel.z;
    return 1;
}

#ifdef NON_MATCHING
s16 func_8010E710_baby_bowser_broadside(BbCollider *c, BbMover *m) {
    Vec n;
    Vec pos;
    Vec vel;
    Vec next;
    Vec proj;
    f32 d;
    f32 dist;
    s16 hit;

    n.x = c->plane.normal.x;
    n.y = c->plane.normal.y;
    n.z = c->plane.normal.z;
    d = -c->plane.dist;
    pos.x = m->pos.x;
    pos.y = m->pos.y;
    pos.z = m->pos.z;
    vel.x = m->vel.x;
    vel.y = m->vel.y;
    vel.z = m->vel.z;
    if (!(c->attr & 0x20) && n.x * pos.x + n.y * pos.y + n.z * pos.z + d < 0.0f) {
        return 0;
    }
    next.x = pos.x + vel.x;
    next.y = pos.y + vel.y;
    next.z = pos.z + vel.z;
    if (!(c->attr & 0x20)) {
        dist = func_8010ED1C_baby_bowser_broadside(c, &next);
        if (n.x * next.x + n.y * next.y + n.z * next.z + d > 0.0f) {
            if (m->radius <= BB3_ABS(dist)) {
                return 0;
            }
        }
    } else {
        dist = func_8010ED1C_baby_bowser_broadside(c, &next);
        if (m->radius <= BB3_ABS(dist)) {
            return 0;
        }
    }
    proj.x = -n.x * dist + next.x;
    proj.y = -n.y * dist + next.y;
    proj.z = -n.z * dist + next.z;
    hit = func_8010E9FC_baby_bowser_broadside(c, &proj);
    if (hit) {
        if (!(c->attr & 0x10)) {
            next.x = n.x * m->radius * 1.01f + proj.x;
            next.y = n.y * m->radius * 1.01f + proj.y;
            next.z = n.z * m->radius * 1.01f + proj.z;
            vel.x = next.x - pos.x;
            vel.y = next.y - pos.y;
            vel.z = next.z - pos.z;
            m->vel.x = vel.x;
            m->vel.y = vel.y;
            m->vel.z = vel.z;
        }
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E710_baby_bowser_broadside);
#endif

#ifdef NON_MATCHING
s16 func_8010E9FC_baby_bowser_broadside(BbCollider *c, Vec *p) {
    Vec e;
    Vec q;
    Vec *a;
    Vec *b;
    s16 i;

    switch (c->plane.axis) {
    case 0:
        for (i = 0; i < c->vertexCount; i++) {
            a = &c->cur[i];
            b = &c->cur[(i + 1 == c->vertexCount) ? 0 : i + 1];
            e.y = b->y - a->y;
            e.z = b->z - a->z;
            q.y = p->y - a->y;
            q.z = p->z - a->z;
            if ((e.y * q.z - e.z * q.y) * c->plane.normal.x < 0.0f) {
                return 0;
            }
        }
        break;
    case 1:
        for (i = 0; i < c->vertexCount; i++) {
            a = &c->cur[i];
            b = &c->cur[(i + 1 == c->vertexCount) ? 0 : i + 1];
            e.x = b->x - a->x;
            e.z = b->z - a->z;
            q.x = p->x - a->x;
            q.z = p->z - a->z;
            if ((e.z * q.x - e.x * q.z) * c->plane.normal.y < 0.0f) {
                return 0;
            }
        }
        // fallthrough (retail: missing break, the y-dominant case also runs the z test)
    case 2:
        for (i = 0; i < c->vertexCount; i++) {
            a = &c->cur[i];
            b = &c->cur[(i + 1 == c->vertexCount) ? 0 : i + 1];
            e.x = b->x - a->x;
            e.y = b->y - a->y;
            q.x = p->x - a->x;
            q.y = p->y - a->y;
            if ((e.x * q.y - e.y * q.x) * c->plane.normal.z < 0.0f) {
                return 0;
            }
        }
        break;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E9FC_baby_bowser_broadside);
#endif

f32 func_8010ED1C_baby_bowser_broadside(BbCollider *c, Vec *p) {
    Vec n;
    f32 x = p->x;
    f32 y = p->y;
    f32 z = p->z;

    n.x = c->plane.normal.x;
    n.y = c->plane.normal.y;
    n.z = c->plane.normal.z;
    return (x * n.x + y * n.y + z * n.z - c->plane.dist) / HuSqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
}

#ifdef NON_MATCHING
s16 func_8010EDC0_baby_bowser_broadside(BbCollider *c, BbMover *m) {
    f32 side;
    s16 i;

    if (!(c->attr & 2) && c->height < m->pos.y) {
        return 0;
    }
    side = func_8010F004_baby_bowser_broadside(m, &c->cur[0], &c->cur[1]);
    if (side == 0.0f) {
        return 0;
    }
    if (side > 0.0f) {
        for (i = 1; i < c->vertexCount; i++) {
            side = func_8010F004_baby_bowser_broadside(m, &c->cur[i], &c->cur[(i + 1 == c->vertexCount) ? 0 : i + 1]);
            if (side == 0.0f) {
                return 1;
            }
            if (side < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < c->vertexCount; i++) {
            side = func_8010F004_baby_bowser_broadside(m, &c->cur[i], &c->cur[(i + 1 == c->vertexCount) ? 0 : i + 1]);
            if (side == 0.0f) {
                return 1;
            }
            if (side > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010EDC0_baby_bowser_broadside);
#endif

f32 func_8010F004_baby_bowser_broadside(BbMover *m, Vec *a, Vec *b) {
    Vec modelPos;
    Vec ma;
    Vec mb;

    modelPos.x = m->pos.x;
    modelPos.z = m->pos.z;
    ma.x = a->x - modelPos.x;
    ma.z = a->z - modelPos.z;
    mb.x = b->x - modelPos.x;
    mb.z = b->z - modelPos.z;
    return ma.z * mb.x - ma.x * mb.z;
}

u8 func_8010F060_baby_bowser_broadside(f32 *out, u8 *timer, f32 start, f32 end, f32 duration) {
    f32 t = *timer / duration;

    *out = start + (end - start) * t;
    if (++(*timer) > duration) {
        *timer = 0;
        *out = end;
        return TRUE;
    }
    return FALSE;
}

f32 func_8010F0D8_baby_bowser_broadside(f32 t, f32 p0, f32 p1, f32 p2) {
    if (t > 1.0f) {
        t = 1.0f;
    }
    return (1.0f - t) * (1.0f - t) * p0 + 2.0f * (1.0f - t) * t * p1 + t * t * p2;
}

// Fisher-Yates shuffle on [0, n-1].
void func_8010F144_baby_bowser_broadside(s16 *out, s16 n) {
    s16 temp;
    s16 i;

    for (i = 0; i < n; i++) {
        out[i] = i;
    }
    for (i = n - 1; i >= 0; i--) {
        s16 rand = rand16() % (i + 1);

        temp = out[i];
        out[i] = out[rand];
        out[rand] = temp;
    }
}

void func_8010F250_baby_bowser_broadside(omObjData *object) {
    HmfModel *model = &HmfModelData[object->model[0]];

    object->scale.x = model->scale.x;
    object->scale.y = model->scale.y;
    object->scale.z = model->scale.z;
    object->trans.x = model->pos.x;
    object->trans.y = model->pos.y;
    object->trans.z = model->pos.z;
    if (model->rot.x >= 360.0f) {
        model->rot.x -= 360.0f;
    }
    if (model->rot.x < 0.0f) {
        model->rot.x += 360.0f;
    }
    if (model->rot.y >= 360.0f) {
        model->rot.y -= 360.0f;
    }
    if (model->rot.y < 0.0f) {
        model->rot.y += 360.0f;
    }
    if (model->rot.z >= 360.0f) {
        model->rot.z -= 360.0f;
    }
    if (model->rot.z < 0.0f) {
        model->rot.z += 360.0f;
    }
    object->rot.x = model->rot.x;
    object->rot.y = model->rot.y;
    object->rot.z = model->rot.z;
}

// Plane through v[0..2]: unit normal, distance, dominant axis.
void func_8010F3C4_baby_bowser_broadside(Vec *v, BbPlane *out) {
    f32 n[3];
    f32 e1x, e1y, e1z;
    f32 e2x, e2y, e2z;
    f32 len;
    s16 max;
    s16 i;

    e1x = v[1].x - v[0].x;
    e1y = v[1].y - v[0].y;
    e1z = v[1].z - v[0].z;
    e2x = v[2].x - v[0].x;
    e2y = v[2].y - v[0].y;
    e2z = v[2].z - v[0].z;
    n[0] = e1y * e2z - e1z * e2y;
    n[1] = e1z * e2x - e1x * e2z;
    n[2] = e1x * e2y - e1y * e2x;
    len = HuSqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
    if (len != 0.0f) {
        n[0] /= len;
        n[1] /= len;
        n[2] /= len;
    }
    out->dist = n[0] * v[0].x + n[1] * v[0].y + n[2] * v[0].z;
    max = 0;
    for (i = 1; i < 3; i++) {
        if (BB3_ABS(n[max]) < BB3_ABS(n[i])) {
            max = i;
        }
    }
    out->normal.x = n[0];
    out->normal.y = n[1];
    out->normal.z = n[2];
    out->axis = max;
}

void func_8010F5C8_baby_bowser_broadside(Vec from, Vec to, f32 *out) {
    Vec direction;
    f32 fullRot = 360.0f;
    f32 pitch;
    f32 yaw;

    direction.x = to.x - from.x;
    direction.y = to.y - from.y;
    direction.z = to.z - from.z;
    pitch = atan2df(direction.y, BB3_VECMagXZ(&direction));
    if (pitch < 0.0f) {
        pitch += fullRot;
    } else if (pitch >= fullRot) {
        pitch -= fullRot;
    }
    *(out++) = pitch;
    yaw = atan2df(direction.x, direction.z);
    if (yaw < 0.0f) {
        yaw += fullRot;
    } else if (yaw >= fullRot) {
        yaw -= fullRot;
    }
    *(out++) = yaw;
}

void func_8010F6F8_baby_bowser_broadside(f32 *a, f32 *b) {
    f32 diff;

    while (*b < 0.0f) {
        *b += 360.0f;
    }
    while (*b >= 360.0f) {
        *b -= 360.0f;
    }
    while (*a < 0.0f) {
        *a += 360.0f;
    }
    while (*a >= 360.0f) {
        *a -= 360.0f;
    }
    diff = BB3_ABS(*b - *a);
    if (diff > 180.0f) {
        if (*a < *b) {
            *b -= 360.0f;
        } else {
            *a -= 360.0f;
        }
    }
}

void func_8010F878_baby_bowser_broadside(f32 *out) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            BB3_M_ID(out, i, j) = 0.0f;
        }
        BB3_M_ID(out, i, i) = 1.0f;
    }
}

void func_8010F900_baby_bowser_broadside(f32 *out, f32 x, f32 y, f32 z) {
    func_8010F878_baby_bowser_broadside(out);
    BB3_M_ID(out, 3, 0) = x;
    BB3_M_ID(out, 3, 1) = y;
    BB3_M_ID(out, 3, 2) = z;
}

void func_8010F958_baby_bowser_broadside(f32 *out, f32 angle) {
    func_8010F878_baby_bowser_broadside(out);
    BB3_M_ID(out, 1, 1) = cosdf(angle);
    BB3_M_ID(out, 1, 2) = sindf(angle);
    BB3_M_ID(out, 2, 1) = -sindf(angle);
    BB3_M_ID(out, 2, 2) = cosdf(angle);
}

void func_8010F9C0_baby_bowser_broadside(f32 *out, f32 angle) {
    func_8010F878_baby_bowser_broadside(out);
    BB3_M_ID(out, 0, 0) = cosdf(angle);
    BB3_M_ID(out, 0, 2) = -sindf(angle);
    BB3_M_ID(out, 2, 0) = sindf(angle);
    BB3_M_ID(out, 2, 2) = cosdf(angle);
}

void func_8010FA28_baby_bowser_broadside(f32 *a, f32 *b, f32 *out) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            BB3_M_ID(out, i, j) = BB3_M_ID(a, i, 0) * BB3_M_ID(b, 0, j) + BB3_M_ID(a, i, 1) * BB3_M_ID(b, 1, j) +
                                  BB3_M_ID(a, i, 2) * BB3_M_ID(b, 2, j) + BB3_M_ID(a, i, 3) * BB3_M_ID(b, 3, j);
        }
    }
}

void func_8010FADC_baby_bowser_broadside(f32 *arg0, f32 *out) {
    *(out++) = BB3_M_ID(arg0, 3, 0) * BB3_M_ID(arg0, 0, 0) + BB3_M_ID(arg0, 3, 1) * BB3_M_ID(arg0, 1, 0) + BB3_M_ID(arg0, 3, 2) * BB3_M_ID(arg0, 2, 0);
    *(out++) = BB3_M_ID(arg0, 3, 0) * BB3_M_ID(arg0, 0, 1) + BB3_M_ID(arg0, 3, 1) * BB3_M_ID(arg0, 1, 1) + BB3_M_ID(arg0, 3, 2) * BB3_M_ID(arg0, 2, 1);
    *(out++) = BB3_M_ID(arg0, 3, 0) * BB3_M_ID(arg0, 0, 2) + BB3_M_ID(arg0, 3, 1) * BB3_M_ID(arg0, 1, 2) + BB3_M_ID(arg0, 3, 2) * BB3_M_ID(arg0, 2, 2);
}

void func_8010FB74_baby_bowser_broadside(f32 transX, f32 transY, f32 transZ, f32 rotX, f32 rotY, f32 rotZ, f32 *out) {
    f32 translationMtx[16];
    f32 rotXMtx[16];
    f32 rotYMtx[16];
    f32 rotMtx[16];

    func_8010F900_baby_bowser_broadside(translationMtx, transX, transY, transZ);
    func_8010F958_baby_bowser_broadside(rotXMtx, rotX);
    func_8010F9C0_baby_bowser_broadside(rotYMtx, rotY);
    func_8010FA28_baby_bowser_broadside(rotXMtx, rotYMtx, rotMtx);
    func_8010FA28_baby_bowser_broadside(rotMtx, translationMtx, out);
}

void func_8010FC2C_baby_bowser_broadside(Vec *in, s16 n, f32 *mtx, Vec *out) {
    s16 i;

    for (i = 0; i < n; i++) {
        out[i].x = (BB3_M_ID(mtx, 3, 0) + in[i].x) * BB3_M_ID(mtx, 0, 0) + (BB3_M_ID(mtx, 3, 1) + in[i].y) * BB3_M_ID(mtx, 1, 0) + (BB3_M_ID(mtx, 3, 2) + in[i].z) * BB3_M_ID(mtx, 2, 0);
        out[i].y = (BB3_M_ID(mtx, 3, 0) + in[i].x) * BB3_M_ID(mtx, 0, 1) + (BB3_M_ID(mtx, 3, 1) + in[i].y) * BB3_M_ID(mtx, 1, 1) + (BB3_M_ID(mtx, 3, 2) + in[i].z) * BB3_M_ID(mtx, 2, 1);
        out[i].z = (BB3_M_ID(mtx, 3, 0) + in[i].x) * BB3_M_ID(mtx, 0, 2) + (BB3_M_ID(mtx, 3, 1) + in[i].y) * BB3_M_ID(mtx, 1, 2) + (BB3_M_ID(mtx, 3, 2) + in[i].z) * BB3_M_ID(mtx, 2, 2);
    }
}
