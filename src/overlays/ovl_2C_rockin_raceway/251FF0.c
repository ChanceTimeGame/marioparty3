#include "common.h"

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801059A0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80105C24_rockin_raceway);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_80111740_rockin_raceway);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_8011174C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80105CB0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106A5C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106A80_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106B28_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106DC8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801071D8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010769C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107958_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107A38_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107BFC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107D04_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107E78_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010803C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108464_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108578_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108760_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108864_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108A80_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108BAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108D84_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108ED4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108F8C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109044_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109134_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109208_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109384_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801094EC_rockin_raceway);

// m1 rr2
#include "overlays/minigame.h"
#include "mallocblock.h"

/* a kart (rr1's functions own most of it) */
typedef struct RrKart {
    /* 0x00 */ char unk00[0x40];
    /* 0x40 */ f32 unk40; /* wheel angle */
    /* 0x44 */ char unk44[0x14];
    /* 0x58 */ Vec unk58; /* position */
    /* 0x64 */ char unk64[4];
    /* 0x68 */ f32 unk68; /* heading */
} RrKart;

/* 16 entries of D_80111B5C: a model and its animation state */
typedef struct RrMdlAnim {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02; /* model, -1 unused */
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ char unk0C[0x24];
} RrMdlAnim; /* size 0x30 */

/* 16 entries of D_80111B60: the RrMdlAnim and model state saved by func_801097A0 */
typedef struct RrMdlSave {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02; /* model unk40 */
    /* 0x04 */ s32 unk04; /* model unk18 */
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
    /* 0x28 */ Vec scale;
} RrMdlSave; /* size 0x34 */

extern RrMdlAnim *D_80111B5C_rockin_raceway;
extern RrMdlSave *D_80111B60_rockin_raceway;
extern s16 D_80111B64_rockin_raceway;

void func_801094EC_rockin_raceway(Vec *pos, Vec *vel, Vec *scale, f32 arg3);
void func_80109A04_rockin_raceway(omObjData *obj);
void func_80109CF8_rockin_raceway(void);
/* the sprite files (D_80111B68) */
typedef struct RrSprFiles {
    /* 0x00 */ s16 unk00; /* 0x4D000E */
    /* 0x02 */ char unk02[4];
    /* 0x06 */ s16 unk06; /* 0x4D0010 */
    /* 0x08 */ s16 unk08; /* 0x4D0011 */
} RrSprFiles;

extern RrSprFiles *D_80111B68_rockin_raceway;
extern s32 D_80111AE8_rockin_raceway;
extern Vtx D_801114D8_rockin_raceway[];
extern Vtx D_80111518_rockin_raceway[];
extern s32 D_8011159C_rockin_raceway[];
extern s32 D_801115AC_rockin_raceway[2]; /* inside D_8011159C's label: best times? */
extern s32 D_801115B4_rockin_raceway;

u16 func_8010A4C0_rockin_raceway(s32 file);
void func_8010B5DC_rockin_raceway(s32 *times);
s16 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct *spr, u16 model, s32 *arg2);
s16 func_8010FFB8_rockin_raceway(HuSprite_Unk84_Struct *spr, Vtx *vtx);
void func_80110C38_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *spr, s32 *arg2);
void func_80110D90_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *spr, s32 *times);
/* the four racing lines (D_80111B40), built by func_80109DA8 from D_801112A0 */
typedef struct RrPath {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ u16 unk02; /* point count */
    /* 0x04 */ f32 unk04; /* lap length without the closing segment */
    /* 0x08 */ f32 unk08; /* length up to point D_801112C0[i] */
    /* 0x0C */ Vec *unk0C; /* points */
    /* 0x10 */ Vec *unk10; /* segment midpoints */
    /* 0x14 */ f32 *unk14; /* segment lengths */
    /* 0x18 */ f32 *unk18; /* length at each point (count + 1) */
    /* 0x1C */ Vec *unk1C; /* segment rotation */
    /* 0x20 */ s16 *unk20; /* per point: 1 or 2 placed at random */
} RrPath; /* size 0x24 */

extern RrPath *D_80111B40_rockin_raceway;
extern f32 D_80111B44_rockin_raceway;
extern Vec *D_801112A0_rockin_raceway[4];
extern s32 D_801112B0_rockin_raceway[4]; /* label D_801112B2 + 2: the u16 load reads its low half */
extern s32 D_801112C0_rockin_raceway[4];

void func_8010E8A0_rockin_raceway(f32 t, Vec *a, Vec *b, Vec *c, Vec *out);
void func_8010E994_rockin_raceway(f32 t, Vec *a, Vec *b, Vec *c, Vec *out);
void func_8010EB84_rockin_raceway(Vec *dir, Vec *rot);
f32 func_8010E7E0_rockin_raceway(f32 t, f32 a, f32 b);
// m1 rr2 end

/* rr2 func_801096A0_rockin_raceway */
void func_801096A0_rockin_raceway(RrKart *kart) {
    Vec pos;
    Vec vel;
    Vec scale;

    pos.x = kart->unk58.x;
    pos.z = kart->unk58.z;
    pos.y = kart->unk58.y + 200.0 * 0.1f;
    vel.x = -(sindf(kart->unk68 + kart->unk40) * 100.0 * 0.1f);
    vel.z = -(cosdf(kart->unk68 + kart->unk40) * 100.0 * 0.1f);
    vel.y = 1.0f;
    scale.x = scale.y = scale.z = 0.25f;
    func_801094EC_rockin_raceway(&pos, &vel, &scale, 1.0f);
}
/* rr2 end func_801096A0_rockin_raceway */

/* rr2 func_801097A0_rockin_raceway */
void func_801097A0_rockin_raceway(void) {
    RrMdlSave *save;
    RrMdlAnim *anim;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway == 0) {
        save = D_80111B60_rockin_raceway;
        anim = D_80111B5C_rockin_raceway;
        for (i = 0; i < 16; i++, anim++, save++) {
            if (anim->unk02 != -1) {
                model = &HmfModelData[anim->unk02];
                save->unk00 = anim->unk00;
                save->unk02 = model->unk40;
                save->unk04 = model->unk18;
                save->unk08 = anim->unk04;
                save->unk0C = anim->unk08;
                save->pos.x = model->pos.x;
                save->pos.y = model->pos.y;
                save->pos.z = model->pos.z;
                save->rot.x = model->rot.x;
                save->rot.y = model->rot.y;
                save->rot.z = model->rot.z;
                save->scale.x = model->scale.x;
                save->scale.y = model->scale.y;
                save->scale.z = model->scale.z;
                anim->unk00 = 0;
                model->unk18 |= 4;
                model->unk40 = 0.0f;
            }
        }
        D_80111B64_rockin_raceway = 1;
    }
}
/* rr2 end func_801097A0_rockin_raceway */

/* rr2 func_801098D8_rockin_raceway */
void func_801098D8_rockin_raceway(void) {
    RrMdlSave *save;
    RrMdlAnim *anim;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway != 0) {
        save = D_80111B60_rockin_raceway;
        anim = D_80111B5C_rockin_raceway;
        for (i = 0; i < 16; i++, anim++, save++) {
            if (anim->unk02 != -1) {
                model = &HmfModelData[anim->unk02];
                anim->unk00 = save->unk00;
                model->unk18 = save->unk04;
                anim->unk04 = save->unk08;
                anim->unk08 = save->unk0C;
                model->pos.x = save->pos.x;
                model->pos.y = save->pos.y;
                model->pos.z = save->pos.z;
                model->rot.x = save->rot.x;
                model->rot.y = save->rot.y;
                model->rot.z = save->rot.z;
                model->scale.x = save->scale.x;
                model->scale.y = save->scale.y;
                model->scale.z = save->scale.z;
            }
        }
        D_80111B64_rockin_raceway = 0;
    }
}
/* rr2 end func_801098D8_rockin_raceway */

/* rr2 func_801099AC_rockin_raceway */
void func_801099AC_rockin_raceway(void) {
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 24, 0, -1, func_80109A04_rockin_raceway);
}
/* rr2 end func_801099AC_rockin_raceway */

/* rr2 func_80109A04_rockin_raceway */
void func_80109A04_rockin_raceway(omObjData *obj) {
    s32 i;
    s16 grp;

    obj->func = (omObjFunc)func_80109CF8_rockin_raceway;
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->model[0] = func_8000B0A0_main(0x4D0000, 0x99);
    obj->model[1] = func_8000B0A0_main(0x4D000A, 0xB9);
    obj->model[2] = func_8000B0A0_main(0x4D000B, 0xB9);
    D_80111B68_rockin_raceway->unk06 = func_8010A4C0_rockin_raceway(0x4D0010);
    D_80111B68_rockin_raceway->unk08 = func_8010A4C0_rockin_raceway(0x4D0011);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            obj->model[3] = func_8010FFB8_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk06), D_801114D8_rockin_raceway);
        } else {
            obj->model[3 + i] = func_8010F874_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk06), obj->model[3], &D_801115B4_rockin_raceway);
        }
    }
    for (i = 0; i < 12; i++) {
        if (i == 0) {
            obj->model[7] = func_8010FFB8_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk08), D_80111518_rockin_raceway);
        } else {
            obj->model[7 + i] = func_8010F874_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk08), obj->model[7], &D_801115B4_rockin_raceway);
        }
    }
    func_80110C38_rockin_raceway(&obj->model[3], func_80055194_main(D_80111B68_rockin_raceway->unk06), D_8011159C_rockin_raceway);
    D_801115AC_rockin_raceway[1] = D_80111AE8_rockin_raceway;
    func_8010B5DC_rockin_raceway(D_801115AC_rockin_raceway);
    func_80110D90_rockin_raceway(&obj->model[7], func_80055194_main(D_80111B68_rockin_raceway->unk08), D_801115AC_rockin_raceway);
    D_80111B68_rockin_raceway->unk00 = func_8010A4C0_rockin_raceway(0x4D000E);
    grp = HuSprGrpCreate(1, 0);
    func_80055024_main(grp, 0, D_80111B68_rockin_raceway->unk00, 0);
    HuSprAttrSet(grp, 0, 0x4000);
    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    func_80054904_main(grp, 0, 160, 120);
    HuSprPriSet(grp, 0, 0xFFFF);
    func_800550F4_main(grp, 0, 0);
    WipeCreateIn(0xFF, 16);
}
/* rr2 end func_80109A04_rockin_raceway */

void func_80109CF8_rockin_raceway(void) {
}

/* rr2 func_80109D00_rockin_raceway */
void func_80109D00_rockin_raceway(s32 *arg0) {
    omObjData *obj = D_800EC1C0_minigame[0];

    func_80110C38_rockin_raceway(&obj->model[3], func_80055194_main(D_80111B68_rockin_raceway->unk06), arg0);
}
/* rr2 end func_80109D00_rockin_raceway */

/* rr2 func_80109D54_rockin_raceway */
void func_80109D54_rockin_raceway(s32 *times) {
    omObjData *obj = D_800EC1C0_minigame[0];

    func_80110D90_rockin_raceway(&obj->model[7], func_80055194_main(D_80111B68_rockin_raceway->unk08), times);
}
/* rr2 end func_80109D54_rockin_raceway */

/* rr2 func_80109DA8_rockin_raceway */
void func_80109DA8_rockin_raceway(void) {
    Vec rot;
    RrPath *path;
    s32 i;
    s32 j;
    s32 next;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;

    D_80111B40_rockin_raceway = HuMemAllocTag(sizeof(RrPath) * 4, 0x7918);
    for (i = 0, path = D_80111B40_rockin_raceway; i < 4; i++, path++) {
        path->unk00 = i;
        path->unk04 = path->unk08 = 0.0f;
        path->unk0C = D_801112A0_rockin_raceway[i];
        path->unk02 = D_801112B0_rockin_raceway[i];
        path->unk0C[D_801112C0_rockin_raceway[i]].x = 340.0f;
        path->unk10 = HuMemAllocTag(path->unk02 * sizeof(Vec), 0x7918);
        path->unk14 = HuMemAllocTag(path->unk02 * sizeof(f32), 0x7918);
        path->unk18 = HuMemAllocTag((path->unk02 + 1) * sizeof(f32), 0x7918);
        path->unk1C = HuMemAllocTag(path->unk02 * sizeof(Vec), 0x7918);
        path->unk20 = HuMemAllocTag(path->unk02 * sizeof(s16), 0x7918);
        memset(path->unk20, 0, 4);
        for (j = 0; j < 5; j++) {
            next = (rand8() & 0xFF) % D_801112C0_rockin_raceway[i];
            path->unk20[next] = 1;
        }
        for (j = 0; j < 3; j++) {
            next = (rand8() & 0xFF) % D_801112C0_rockin_raceway[i];
            path->unk20[next] = 2;
        }
        len = 0.0f;
        for (j = 0; j < path->unk02; j++) {
            next = (j + 1) % path->unk02;
            dx = path->unk0C[next].x - path->unk0C[j].x;
            dy = path->unk0C[next].y - path->unk0C[j].y;
            dz = path->unk0C[next].z - path->unk0C[j].z;
            path->unk14[j] = sqrtf(dx * dx + dy * dy + dz * dz);
            path->unk18[j] = len;
            len += path->unk14[j];
            if (j < D_801112C0_rockin_raceway[i]) {
                path->unk08 = len;
            }
            path->unk10[j].x = path->unk0C[j].x + dx * 0.5f;
            path->unk10[j].y = path->unk0C[j].y + dy * 0.5f;
            path->unk10[j].z = path->unk0C[j].z + dz * 0.5f;
            func_8010E994_rockin_raceway(0.0f, &path->unk0C[j], &path->unk10[j], &path->unk0C[next], &rot);
            func_8010EB84_rockin_raceway(&rot, &path->unk1C[j]);
        }
        path->unk18[j] = len;
        path->unk04 = len - path->unk14[j - 1];
    }
    D_80111B44_rockin_raceway = D_80111B40_rockin_raceway[0].unk08;
    for (i = 1, path = &D_80111B40_rockin_raceway[1]; i < 4; i++, path++) {
        if (D_80111B44_rockin_raceway > path->unk08) {
            D_80111B44_rockin_raceway = path->unk08;
        }
    }
}
/* rr2 end func_80109DA8_rockin_raceway */

#ifdef NON_MATCHING
/* rr2 func_8010A258_rockin_raceway */
f32 func_8010A258_rockin_raceway(u16 idx, f32 dist, f32 base, f32 delta, s16 *seg, f32 *frac, Vec *pos, Vec *rot) {
    RrPath *path = &D_80111B40_rockin_raceway[idx];
    f32 start;
    f32 d;
    f32 rem;
    f32 t;
    s32 i;

    s32 next;
    s32 cur;

    start = base + delta;
    if (path->unk04 <= start) {
        start = path->unk04;
    } else if (start <= 0.0f) {
        start = 0.0f;
    }
    d = start + dist;
    if (path->unk04 <= d) {
        d = path->unk04;
    } else if (d <= 0.0f) {
        d = 0.0f;
    }
    rem = d;
    for (i = 0; i < path->unk02; i++) {
        if (d <= path->unk18[i + 1]) {
            break;
        }
        rem = d - path->unk18[i + 1];
    }
    if (path->unk02 - 1 < i) {
        i = path->unk02 - 1;
    }
    if (seg != NULL) {
        *seg = i;
    }
    if (rem != 0.0f && path->unk14[i] != 0.0f) {
        t = rem / path->unk14[i];
    } else {
        t = 0.0f;
    }
    if (frac != NULL) {
        *frac = t;
    }
    cur = i;
    next = 0;
    if (i < path->unk02 - 1) {
        next = i + 1;
    }

    func_8010E8A0_rockin_raceway(t, &path->unk0C[cur], &path->unk10[cur], &path->unk0C[next], pos);
    rot->x = func_8010E7E0_rockin_raceway(t, path->unk1C[cur].x, path->unk1C[next].x);
    rot->y = func_8010E7E0_rockin_raceway(t, path->unk1C[cur].y, path->unk1C[next].y);
    return start;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A258_rockin_raceway);
#endif
/* rr2 end func_8010A258_rockin_raceway */

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A48C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A4C0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A504_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A5E4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A990_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010AAAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B124_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B2B8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B5DC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B774_rockin_raceway);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_80111838_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B89C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C0D8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C5E0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C7CC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C9BC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C9CC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CA1C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CADC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CB5C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CC10_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CE90_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D104_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D114_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D134_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D288_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D5B8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D600_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D944_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D9C4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E08C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E2E4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E344_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E39C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E504_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E608_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E7C8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E7E0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E840_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E8A0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E93C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E994_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EB04_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EB84_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EC0C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EC38_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EC8C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010F874_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FA78_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FBAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FFB8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80110C38_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80110D90_rockin_raceway);
