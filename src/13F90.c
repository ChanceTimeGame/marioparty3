#include "common.h"
#include "mallocblock.h"

/* One scattered polygon of the effect (0x30 bytes, one per face group). */
typedef struct HmfFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 speed; /* func_80013D4C_main: random 0..1.5 */
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec dir; /* unit direction on a sphere */
    /* 0x24 */ Vec vel;
} HmfFxPart; /* size 0x30 */

/* A model's vertex-scatter effect (HmfModel.unkBC; hmfman.h's HmfModelData_UnkBC_Struct). */
typedef struct HmfFxWork {
    /* 0x00 */ s16 unk00; /* motion, -1 none */
    /* 0x02 */ s16 unk02; /* frame */
    /* 0x04 */ u16 unk04; /* flags: 1 loop, 4 finished, 8 recolour */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08; /* distance */
    /* 0x0C */ f32 unk0C; /* speed */
    /* 0x10 */ char unk10[8];
    /* 0x18 */ void (*unk18)(s16);
    /* 0x1C */ char unk1C[0xC];
    /* 0x28 */ Vec verts[4]; /* polygon template, relative to its centre */
    /* 0x58 */ HmfFxPart* parts;
} HmfFxWork; /* size 0x5C */

/* One face group of a model file (0x18 bytes): up to 4 vertex indices and the centre. */
typedef struct HmfFxGroup {
    /* 0x00 */ u8 count; /* bit 7: flag */
    /* 0x01 */ char unk01[3];
    /* 0x04 */ s16 vtx[4];
    /* 0x0C */ Vec center;
} HmfFxGroup; /* size 0x18 */

/* hmfman.h's HmfModelData_Unk64_Unk60_Struct (0x68 bytes) with its face-group range. */
typedef struct HmfFxObj {
    /* 0x00 */ char unk00[0x2C];
    /* 0x2C */ s16 firstGroup;
    /* 0x2E */ s16 groupCount;
    /* 0x30 */ char unk30[0x20];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ void* unk54;
    /* 0x58 */ char unk58[0x10];
} HmfFxObj; /* size 0x68 */

/* HmfData as the effect reads it (hmfload.c's HmfLoadData; pointer slots kept for the host). */
typedef struct HmfFxData {
    /* 0x00 */ char unk00[0xE];
    /* 0x0E */ s16 unk0E; /* memory tag - 1 */
    /* 0x10 */ char unk10[0xA];
    /* 0x1A */ s16 unk1A; /* face group count */
    /* 0x1C */ char unk1C[0x10];
    /* 0x2C */ void* unk2C[4];
    /* 0x3C */ void* unk3C;
    /* 0x40 */ Vtx* unk40; /* vertex positions */
    /* 0x44 */ Vtx* unk44[3]; /* vertex buffers, one per frame */
    /* 0x50 */ void* unk50[4];
    /* 0x60 */ HmfFxObj* unk60;
    /* 0x64 */ s16 unk64;
    /* 0x68 */ void* unk68;
    /* 0x6C */ char unk6C[0x14];
    /* 0x80 */ void* unk80[8];
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ f32 unkA4[3];
    /* 0xB0 */ HmfFxGroup* unkB0;
} HmfFxData;

extern HuCamera* gCameraList;
extern u8 D_800CD6A6_main;  /* camera being drawn */
extern u8 D_800D2008_main;  /* frame buffer index */
s32 func_80018F18_main(HuMtx4F a, HuMtx4F out);
s16 func_8002C834_main(void*, char*);
void func_80013D44_main(void);
void func_80013D4C_main(s16 model);
void func_80013FB4_main(s16 model);

#define FXWORK(model) ((HmfFxWork*) HmfModelData[model].unkBC)
#define FXDATA(model) ((HmfFxData*) HmfModelData[model].hmf)

// Masked 19 (374 vs 372): retail calls rand8 as if it returned int (no andi 0xff after the call;
// include/functions.h declares u8), so the shuffle's index arithmetic differs; a2/a3 swapped in
// the template loop. Logic checked against the asm.
#ifdef NON_MATCHING
/* Sets up the vertex-scatter effect on model: one particle per face group of motion name (all
   groups if NULL), the group's polygon as the template, directions spread over a sphere in a
   shuffled order. type 0/1/2 picks the update (none, burst, scatter); -1 uses hook. */
void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16)) {
    HmfModel* m;
    HmfFxData* hmf;
    HmfFxWork* work;
    HmfFxPart* part;
    HmfFxGroup* group;
    Vtx* p;
    s16* order;
    s32 first;
    s32 count;
    s16 i;
    s16 j;
    s16 a;
    s16 b;
    s16 tmp;
    s16 k;
    s16 side;
    f32 yaw;
    f32 pitch;
    f32 s;

    m = &HmfModelData[model];
    hmf = (HmfFxData*) m->hmf;
    func_8001C258_main(model, 0x01000000, 0x01000000);
    work = HuMemAllocTag(sizeof(HmfFxWork), (u16) hmf->unk0E + 1);
    m->unkBC = (HmfModelData_UnkBC_Struct*) work;
    part = HuMemAllocTag(hmf->unk1A * sizeof(HmfFxPart), (u16) hmf->unk0E + 1);
    work->parts = part;
    if (type == -1) {
        work->unk18 = hook;
    }
    work->unk02 = 0;
    work->unk04 = 0;
    work->unk08 = work->unk0C = 0.0f;
    if (name != NULL) {
        work->unk00 = func_8002C834_main(FXDATA(model), name);
        first = hmf->unk60[work->unk00].firstGroup;
        count = hmf->unk60[work->unk00].groupCount;
    } else {
        work->unk00 = -1;
        first = 0;
        count = hmf->unk1A;
    }
    order = HuMemAlloc(hmf->unk1A * sizeof(s16));
    for (i = 0; i < count; i++) {
        order[i] = i;
    }
    for (i = 0; i < 200; i++) {
        a = (rand8() * hmf->unk1A) >> 8;
        b = (rand8() * hmf->unk1A) >> 8;
        tmp = order[a];
        order[a] = order[b];
        order[b] = tmp;
    }
    group = &hmf->unkB0[first];
    for (j = 0; j < group->count; j++) {
        p = &hmf->unk40[group->vtx[j]];
        work->verts[j].x = p->v.ob[0] - group->center.x;
        work->verts[j].y = p->v.ob[1] - group->center.y;
        work->verts[j].z = p->v.ob[2] - group->center.z;
    }
    if (type != -1) {
        switch (type) {
            case 0:
                work->unk18 = (void (*)(s16)) func_80013D44_main;
                break;
            case 1:
                work->unk18 = func_80013D4C_main;
                break;
            case 2:
                work->unk18 = func_80013FB4_main;
                break;
        }
        side = HuSqrtf(count);
        for (i = 0; i < count; i++) {
            part->speed = 1.0f;
            part->pos.x = part->pos.y = part->pos.z = 0.0f;
            k = order[i];
            yaw = (360.0f / side) * (k % side);
            s = sindf(yaw);
            pitch = (180.0f / side) * (k / side);
            part->vel.x = part->dir.x = s * sindf(pitch);
            part->vel.y = part->dir.y = cosdf(pitch);
            part->vel.z = part->dir.z = cosdf(yaw) * sindf(pitch);
            part->scale = 1.0f;
            part++;
        }
    } else {
        for (i = 0; i < count; i++) {
            part->pos.x = part->pos.y = part->pos.z = part->scale = part->dir.x = part->dir.y = part->dir.z = 0.0f;
            part++;
        }
    }
    HuMemFree(hmf->unk40);
    HuMemFree(order);
}

#else
INCLUDE_ASM("asm/nonmatchings/13F90", func_80013390_main);
#endif

void func_800138EC_main(s16 model, u16 mask, u16 flags) {
    FXWORK(model)->unk04 = (FXWORK(model)->unk04 & ~mask) | flags;
}

s16 func_80013928_main(s16 model) {
    return FXWORK(model)->unk04;
}

void func_80013954_main(s16 model, s16 value) {
    FXWORK(model)->unk02 = value;
}

s16 func_80013980_main(s16 model) {
    return FXWORK(model)->unk02;
}

/* Draw hook: places each face group's polygon at its particle, facing the camera. */
void func_800139AC_main(s16 model, s16 obj) {
    HuMtx4F view;
    HuMtx4F inv;
    Vec verts[4];
    HmfFxData* hmf;
    HmfFxWork* work;
    HuCamera* cam;
    HmfFxGroup* group;
    HmfFxPart* part;
    Vtx* vtxBuf;
    Vtx* vp;
    Vtx* vp2;
    Vec* v;
    s16* idx;
    s32 i;
    s32 j;
    s32 n;
    s32 first;
    s32 count;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    HmfModel* m;

    m = &HmfModelData[model];
    hmf = (HmfFxData*) m->hmf;
    work = (HmfFxWork*) m->unkBC;
    cam = &gCameraList[D_800CD6A6_main];
    guLookAtF(view, cam->pos.x, cam->pos.y, cam->pos.z, cam->at.x, cam->at.y, cam->at.z, cam->up.x, cam->up.y,
              cam->up.z);
    func_80018F18_main(view, inv);
    if (obj != -1) {
        first = hmf->unk60[obj].firstGroup;
        count = hmf->unk60[obj].groupCount;
    } else {
        first = 0;
        count = hmf->unk1A;
    }
    group = &hmf->unkB0[first];
    v = verts;
    for (j = 0; j < group->count; j++) {
        x = work->verts[j].x;
        y = work->verts[j].y;
        z = work->verts[j].z;
        v->x = x * inv[0][0] + y * inv[1][0] + z * inv[2][0];
        v->y = x * inv[0][1] + y * inv[1][1] + z * inv[2][1];
        v->z = x * inv[0][2] + y * inv[1][2] + z * inv[2][2];
        v++;
    }
    part = work->parts;
    vtxBuf = hmf->unk44[D_800D2008_main];
    if (work->unk04 & 8) {
        for (i = 0; i < count; i++) {
            n = group->count & 0x7F;
            idx = group->vtx;
            v = verts;
            scale = part->scale;
            for (j = 0; j < n; j++) {
                vp = &vtxBuf[*idx];
                vp->v.ob[0] = scale * v->x + part->pos.x;
                vp->v.ob[1] = scale * v->y + part->pos.y;
                vp->v.ob[2] = scale * v->z + part->pos.z;
                vp2 = &vtxBuf[*idx++];
                vp2->v.cn[0] = part->color[0];
                vp2->v.cn[1] = part->color[1];
                vp2->v.cn[2] = part->color[2];
                v++;
            }
            group++;
            part++;
        }
    } else {
        for (i = 0; i < count; i++) {
            n = group->count & 0x7F;
            idx = group->vtx;
            v = verts;
            scale = part->scale;
            for (j = 0; j < n; j++) {
                vp = &vtxBuf[*idx++];
                vp->v.ob[0] = scale * v->x + part->pos.x;
                vp->v.ob[1] = scale * v->y + part->pos.y;
                vp->v.ob[2] = scale * v->z + part->pos.z;
                v++;
            }
            group++;
            part++;
        }
    }
}

void func_80013D44_main(void) {
}

/* Effect 1 (burst): the polygons fly out along their directions, slowing down, over 50 frames;
   flag 1 restarts it, flag 4 is set when it ends. */
void func_80013D4C_main(s16 model) {
    HmfFxData* hmf;
    HmfFxWork* work;
    HmfFxPart* part;
    s16 count;
    s16 i;
    f32 scale;
    f32 dist;
    f32 speed;

    hmf = FXDATA(model);
    work = FXWORK(model);
    if (work->unk00 == -1) {
        count = hmf->unk1A;
    } else {
        count = hmf->unk60[work->unk00].groupCount;
    }
    part = work->parts;
    if (work->unk02 >= 50) {
        if (!(work->unk04 & 1)) {
            return;
        }
        work->unk02 = 0;
    }
    scale = 2.0f * cosdf(work->unk02 * 1.8f);
    if (work->unk02 <= 0) {
        work->unk04 &= ~4;
        work->unk08 = 0.0f;
        work->unk0C = 10.0f;
        for (i = 0; i < count; i++) {
            part[i].speed = (rand8() & 0xF) * 0.1f;
        }
        scale = 0.0f;
    }
    dist = work->unk08;
    for (i = 0; i < count; i++) {
        speed = part->speed;
        part->pos.x = dist * part->dir.x * speed;
        part->pos.y = dist * part->dir.y * speed;
        part->pos.z = dist * part->dir.z * speed;
        part->scale = scale;
        part++;
    }
    work->unk08 += work->unk0C;
    work->unk0C *= 0.98;
    if (++work->unk02 >= 50) {
        work->unk04 |= 4;
    }
}

/* Effect 2 (scatter): the polygons are thrown out along their directions and fall, bouncing
   off the model's ground height, over 100 frames; flag 1 restarts it, flag 4 is set when it ends. */
void func_80013FB4_main(s16 model) {
    HmfFxData* hmf;
    HmfFxWork* work;
    HmfFxPart* part;
    s16 count;
    s16 i;
    f32 scale;
    f32 groundY;

    hmf = FXDATA(model);
    work = FXWORK(model);
    if (work->unk00 == -1) {
        count = hmf->unk1A;
    } else {
        count = hmf->unk60[work->unk00].groupCount;
    }
    if (work->unk02 >= 100) {
        if (!(work->unk04 & 1)) {
            return;
        }
        work->unk02 = 0;
    }
    scale = 2.0f * cosdf(work->unk02 * 0.9f);
    if (work->unk02 <= 0) {
        work->unk04 &= ~4;
        scale = 0.0f;
        part = work->parts;
        for (i = 0; i < count; i++) {
            part->pos.x = part->pos.y = part->pos.z = 0.0f;
            part->vel.x = part->dir.x * 10.0f;
            part->vel.y = part->dir.y * 10.0f;
            part->vel.z = part->dir.z * 10.0f;
            part++;
        }
    }
    part = work->parts;
    groundY = HmfModelData[model].pos.y;
    for (i = 0; i < count; i++) {
        part->pos.x += part->vel.x * part->speed;
        part->pos.y += part->vel.y * part->speed;
        part->pos.z += part->vel.z * part->speed;
        part->vel.y -= 0.1f;
        if (groundY + part->pos.y < 0.0f) {
            part->pos.y = -groundY;
            part->vel.x *= 0.9f;
            part->vel.y = -(part->vel.y * 0.3f);
            part->vel.z *= 0.9f;
        }
        part->vel.x *= 0.999f;
        part->vel.y *= 0.999f;
        part->vel.z *= 0.999f;
        part->scale = scale;
        part++;
    }
    if (++work->unk02 >= 100) {
        work->unk04 |= 4;
    }
}
