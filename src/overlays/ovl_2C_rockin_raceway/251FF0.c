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
    /* 0x00 */ char unk00[2];
    /* 0x02 */ u16 unk02;
    /* 0x04 */ char unk04[0x24];
    /* 0x28 */ f32 unk28; /* lap time, seconds */
    /* 0x2C */ char unk2C[2];
    /* 0x2E */ s16 unk2E; /* player */
    /* 0x30 */ char unk30[0x10];
    /* 0x40 */ f32 unk40; /* wheel angle */
    /* 0x44 */ char unk44[0x14];
    /* 0x58 */ Vec unk58; /* position */
    /* 0x64 */ char unk64[4];
    /* 0x68 */ f32 unk68; /* heading */
    /* 0x6C */ char unk6C[4];
} RrKart; /* size 0x70 */

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
    /* 0x02 */ s16 unk02; /* 0x4D000F */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06; /* 0x4D0010 */
    /* 0x08 */ s16 unk08; /* 0x4D0011 */
    /* 0x0A */ s16 unk0A; /* 0x4D0012 */
    /* 0x0C */ s16 unk0C[2]; /* 0x31, 0x32: best time digits */
    /* 0x10 */ s16 unk10; /* 0x4D0013 */
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
extern s16 D_80111B74_rockin_raceway;
/* per player HUD (D_80111B80): position and the five digit offsets */
typedef struct RrHud {
    /* 0x00 */ s16 unk00; /* player */
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06; /* x */
    /* 0x08 */ s16 unk08; /* y */
    /* 0x0A */ s16 unk0A[5]; /* digit x relative to unk06 */
} RrHud; /* size 0x14 */

extern s16 D_80111B6C_rockin_raceway[4]; /* sprite groups */
extern RrHud D_80111B80_rockin_raceway[4];
extern s16 D_80111330_rockin_raceway[4][2];
extern s32 D_801115B8_rockin_raceway[];
void func_8010A990_rockin_raceway(omObjData *obj);
extern RrKart *D_80111B30_rockin_raceway;
extern s32 D_80111AD0_rockin_raceway;
extern s32 D_80111AD8_rockin_raceway; /* game state */
extern s32 D_80111ADC_rockin_raceway;
void func_8010AAAC_rockin_raceway(s16 player, s16 value, u16 arg2);
extern u8 D_800D6A90_main;
f32 func_8010E840_rockin_raceway(f32 t, f32 a, f32 b, f32 c);
extern s16 D_80111B76_rockin_raceway[2]; /* best time sprite groups */
extern s16 D_80111B7A_rockin_raceway; /* new record pulse timer */
extern s16 D_80111340_rockin_raceway[8];
extern s32 D_80111B00_rockin_raceway[2 * 6]; /* best time digits, six per time */
extern s32 D_801115D8_rockin_raceway[6]; /* digit sprite members */
/* camera state (MP2 Looney Lumberjacks LLCamera) */
typedef struct RrCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} RrCamera; /* size 0x24 */

extern s32 fontcolor;
extern s32 D_800EBE24_minigame;
extern s32 D_801115F0_rockin_raceway; /* camera debug mode */
extern s32 D_801115F4_rockin_raceway; /* debug text x */
extern s32 D_801115F8_rockin_raceway; /* debug text y */
void func_8010C7CC_rockin_raceway(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
/* camera preset (D_80111350): center, rotation, zoom */
typedef struct RrCamPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} RrCamPreset;

extern RrCamPreset D_80111350_rockin_raceway;
extern omObjData *D_80111BD8_rockin_raceway;
extern s16 D_80111C28_rockin_raceway;
extern s16 D_80111C2A_rockin_raceway;
extern s16 D_80111C2C_rockin_raceway;
extern s16 D_80111C2E_rockin_raceway;
void func_8010C0D8_rockin_raceway(omObjData *obj);
void func_8010C5E0_rockin_raceway(s32 idx);
#define RR_WRAP(v)          \
    if ((v) >= 360.0) {     \
        (v) -= 360.0;       \
    } else if ((v) < 0.0) { \
        (v) += 360.0;       \
    }

extern RrCamera D_80111BE0_rockin_raceway[2]; /* [0] target, [1] start */
f32 func_8010E7C8_rockin_raceway(f32 t, f32 a, f32 b);
void func_8010D134_rockin_raceway(s32 idx);
/* a camera focus point (D_80111C4C, 16 of them) */
typedef struct RrFocus {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 weight;
} RrFocus; /* size 0x10 */

extern omObjData *D_80111C30_rockin_raceway;
extern s16 D_80111C34_rockin_raceway; /* focus point count */
extern f32 D_80111C38_rockin_raceway[5]; /* focus centre x, y, z; [3] (D_80111C44) summed weight; [4] (D_80111C48) target zoom */
extern RrFocus *D_80111C4C_rockin_raceway;
void func_8010CE90_rockin_raceway(omObjData *obj);
void func_8010CADC_rockin_raceway(Vec *pos, f32 weight);
double fabs(double); /* the GCC builtin (abs.d) */
void func_8010D288_rockin_raceway(s32 cam, Vec *pos, Vec *out, f32 *screen);
f32 func_8010E608_rockin_raceway(f32 target, f32 cur, f32 step);
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

/* rr2 func_8010A48C_rockin_raceway */
u16 func_8010A48C_rockin_raceway(u16 idx, u16 pt) {
    RrPath *path = &D_80111B40_rockin_raceway[idx];

    return path->unk20[pt];
}
/* rr2 end func_8010A48C_rockin_raceway */

/* rr2 func_8010A4C0_rockin_raceway */
u16 func_8010A4C0_rockin_raceway(s32 file) {
    void *data;
    s16 spr;

    data = DataRead(file);
    spr = func_80055810_main(data);
    DataClose(data);
    return spr;
}
/* rr2 end func_8010A4C0_rockin_raceway */

/* rr2 func_8010A504_rockin_raceway */
void func_8010A504_rockin_raceway(void) {
    s32 grp;

    D_80111B68_rockin_raceway->unk02 = func_8010A4C0_rockin_raceway(0x4D000F);
    D_80111B68_rockin_raceway->unk0A = func_8010A4C0_rockin_raceway(0x4D0012);
    D_80111B68_rockin_raceway->unk10 = func_8010A4C0_rockin_raceway(0x4D0013);
    grp = HuSprGrpCreate(1, 0);
    D_80111B74_rockin_raceway = grp;
    func_80054904_main(grp, 0, 160, 60);
    func_80055024_main(grp, 0, D_80111B68_rockin_raceway->unk0A, 0);
    func_800550F4_main(grp, 0, 0);
    func_80054FF8_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x9000);
}
/* rr2 end func_8010A504_rockin_raceway */

/* rr2 func_8010A5E4_rockin_raceway */
void func_8010A5E4_rockin_raceway(s16 player, s16 kind) {
    s32 spr;
    s32 x;
    s32 y;
    s32 grp;
    s32 i;
    s32 off;


    spr = func_8010A4C0_rockin_raceway(D_801115B8_rockin_raceway[kind]);
    x = D_80111330_rockin_raceway[player][0];
    y = D_80111330_rockin_raceway[player][1];
    D_80111B6C_rockin_raceway[player] = grp = HuSprGrpCreate(7, 0);
    D_80111B80_rockin_raceway[player].unk00 = player;
    D_80111B80_rockin_raceway[player].unk08 = y;
    D_80111B80_rockin_raceway[player].unk04 = 0;
    D_80111B80_rockin_raceway[player].unk02 = 0;
    if (player & 1) {
        D_80111B80_rockin_raceway[player].unk06 = x - 4;
    } else {
        D_80111B80_rockin_raceway[player].unk06 = x + 46;
    }
    for (i = 0; i < 5; i++) {
        if (player & 1) {
            D_80111B80_rockin_raceway[player].unk0A[i] = x + (s16)(i * 8 - 20) - D_80111B80_rockin_raceway[player].unk06;
        } else {
            D_80111B80_rockin_raceway[player].unk0A[i] = x + (s16)(i * 8 + 30) - D_80111B80_rockin_raceway[player].unk06;
        }
    }
    for (i = 0; i < 7; i++) {
        if (i == 0) {
            if (player & 1) {
                func_80054904_main(grp, i, x - 42, y);
            } else {
                func_80054904_main(grp, i, x + 8, y);
            }
            func_80055024_main(grp, i, spr, 0);
        } else if (i == 6) {
            if (player & 1) {
                func_80054904_main(grp, i, x - 55, y);
            } else {
                func_80054904_main(grp, i, x - 5, y);
            }
            func_80055024_main(grp, i, D_80111B68_rockin_raceway->unk10, 0);
            func_80055484_main(grp, i, 0, 0, 0, 0xA0);
        } else {
            if (player & 1) {
                func_80054904_main(grp, i, x - 20, y);
            } else {
                func_80054904_main(grp, i, x + 30, y);
            }
            func_80055024_main(grp, i, D_80111B68_rockin_raceway->unk02, 0);
            x += 8;
        }
        func_800550F4_main(grp, i, 0);
        func_80054FF8_main(grp, i, 0);
        HuSprAttrSet(grp, i, 0x1000);
        if (i != 6) {
            HuSprPriSet(grp, i, -16 - i);
        } else {
            HuSprPriSet(grp, i, 0xFFFF);
        }
    }
    omSetStatBit(omAddObj(20, 0, 0, -1, func_8010A990_rockin_raceway), 0xA0);
}
/* rr2 end func_8010A5E4_rockin_raceway */

/* rr2 func_8010A990_rockin_raceway */
void func_8010A990_rockin_raceway(omObjData *obj) {
    RrKart *kart;
    s32 i;

    if (D_80111AD8_rockin_raceway == 5 && (D_80111ADC_rockin_raceway > 0 || D_80111AD0_rockin_raceway >= 2)) {
        HuSprAttrReset(D_80111B74_rockin_raceway, 0, 0x8000);
    } else {
        HuSprAttrSet(D_80111B74_rockin_raceway, 0, 0x8000);
    }
    if (D_80111AD8_rockin_raceway < 3) {
        for (i = 0, kart = D_80111B30_rockin_raceway; i < 4; i++, kart++) {
            func_8010AAAC_rockin_raceway(kart->unk2E, kart->unk28 * 100.0f, kart->unk02);
        }
    } else {
        for (i = 0; i < 4; i++) {
            func_8010AAAC_rockin_raceway(i, 0, 0xFFFF);
        }
    }
}
/* rr2 end func_8010A990_rockin_raceway */

/* rr2 func_8010AAAC_rockin_raceway */
void func_8010AAAC_rockin_raceway(s16 player, s16 value, u16 mode) {
    u16 grp;
    f32 scale;
    f32 x;
    s32 i;
    s32 j;

    grp = D_80111B6C_rockin_raceway[player];
    if (mode == 2) {
        if (D_80111B80_rockin_raceway[player].unk02++ > 30.0f) {
            D_80111B80_rockin_raceway[player].unk02 = 30;
        }
        scale = D_80111B80_rockin_raceway[player].unk02 / 30.0f;
        scale = func_8010E840_rockin_raceway(scale, 0.0f, 1.0f, 0.4f) + 1.0;
    } else {
        if (D_80111B80_rockin_raceway[player].unk02-- < 0) {
            D_80111B80_rockin_raceway[player].unk02 = 0;
        }
        scale = D_80111B80_rockin_raceway[player].unk02 / 30.0f;
        scale = scale * 0.4f + 1.0;
    }
    if (D_80111B80_rockin_raceway[player].unk02 != D_80111B80_rockin_raceway[player].unk04) {
        for (i = 0; i < 5; i++) {
            x = D_80111B80_rockin_raceway[player].unk06 + D_80111B80_rockin_raceway[player].unk0A[i] * scale;
            HuSprScaleSet(grp, i + 1, scale, scale);
            func_80054904_main(grp, i + 1, x, D_80111B80_rockin_raceway[player].unk08);
            if (mode == 2) {
                HuSprAttrSet(grp, i + 1, 0x838);
            } else {
                HuSprAttrReset(grp, i + 1, 0x838);
            }
        }
        D_80111B80_rockin_raceway[player].unk04 = D_80111B80_rockin_raceway[player].unk02;
    }
    switch (mode) {
    case 1:
        if ((D_80111AD0_rockin_raceway & 1) && func_80049F98_main() + D_800D6A90_main == 0) {
            HuSprAttrSet(grp, 0, 0x8000);
        } else {
            HuSprAttrReset(grp, 0, 0x8000);
        }
        break;
    case 2:
        HuSprAttrReset(grp, 0, 0x8000);
        if (!(D_80111AD0_rockin_raceway & 3)) {
            for (i = 0; i < 5; i++) {
                HuSprAttrReset(grp, i + 1, 0x8000);
                func_80054FF8_main(grp, i + 1, 1);
                func_80055458_main(grp, i + 1, 0x100);
            }
        } else {
            for (i = 0; i < 5; i++) {
                HuSprAttrReset(grp, i + 1, 0x8000);
                func_80054FF8_main(grp, i + 1, 0);
                func_80055458_main(grp, i + 1, 0x100);
            }
        }
        return;
    case 0xFFFF:
        for (i = 0; i < 7; i++) {
            HuSprAttrSet(grp, i, 0x8000);
        }
        return;
    default:
        HuSprAttrReset(grp, 0, 0x8000);
        break;
    }
    for (i = 0; i < 5; i++) {
        if (i * 20 < value) {
            j = i + 1;
            HuSprAttrReset(grp, j, 0x8000);
            if (value >= j * 20) {
                func_80055458_main(grp, j, 0x100);
                func_80054FF8_main(grp, j, 0);
            } else {
                func_80055458_main(grp, i + 1, (s16)(value % 20) * 0.05f * 256.0f);
                func_80054FF8_main(grp, i + 1, 0);
            }
        } else {
            HuSprAttrSet(grp, i + 1, 0x8000);
        }
    }
}
/* rr2 end func_8010AAAC_rockin_raceway */

/* rr2 func_8010B124_rockin_raceway */
void func_8010B124_rockin_raceway(void) {
    s32 grp;
    s32 i;
    s32 j;

    D_80111B68_rockin_raceway->unk0C[0] = func_8010A4C0_rockin_raceway(0x31);
    D_80111B68_rockin_raceway->unk0C[1] = func_8010A4C0_rockin_raceway(0x32);
    D_80111B7A_rockin_raceway = 0;
    for (i = 0; i < 2; i++) {
        D_80111B76_rockin_raceway[i] = grp = HuSprGrpCreate(8, 0);
        for (j = 0; j < 8; j++) {
            func_80054904_main(grp, j, D_80111340_rockin_raceway[j], i * 12 + 28);
            func_80055024_main(grp, j, D_80111B68_rockin_raceway->unk0C[i], 0);
            func_80054FF8_main(grp, j, 0);
            HuSprAttrSet(grp, j, 0x1000);
            func_800550F4_main(grp, j, 0);
        }
        func_80054FF8_main(grp, 2, 10);
        func_80054FF8_main(grp, 5, 11);
    }
}
/* rr2 end func_8010B124_rockin_raceway */

/* rr2 func_8010B2B8_rockin_raceway */
void func_8010B2B8_rockin_raceway(void) {
    f32 scale;
    u16 grp;
    s32 *digits;
    s32 i;
    s32 j;

    scale = 1.0f;
    if (D_80111AD8_rockin_raceway == 5) {
        for (i = 0; i < 2; i++) {
            grp = D_80111B76_rockin_raceway[i];
            for (j = 0; j < 8; j++) {
                HuSprAttrSet(grp, j, 0x8000);
            }
        }
        return;
    }
    digits = D_80111B00_rockin_raceway;
    for (i = 0; i < 2; i++) {
        grp = D_80111B76_rockin_raceway[i];
        for (j = 0; j < 8; j++) {
            HuSprAttrReset(grp, j, 0x8000);
        }
    }
    if (D_80111B7A_rockin_raceway != 0) {
        scale = sindf(D_80111B7A_rockin_raceway / 15.0f * 180.0f) + 1.0f;
        if (--D_80111B7A_rockin_raceway == 1) {
            scale = 1.0f;
        }
    }
    for (i = 0; i < 2; i++) {
        grp = D_80111B76_rockin_raceway[i];
        for (j = 0; j < 6; j++) {
            if (digits[i * 6 + j] >= 10) {
                digits[i * 6 + j] = 9;
            } else if (digits[i * 6 + j] < 0) {
                digits[i * 6 + j] = 0;
            }
            func_80054FF8_main(grp, D_801115D8_rockin_raceway[j], (s16)digits[i * 6 + j]);
        }
        if ((D_80111B7A_rockin_raceway != 0) & (i == 1)) {
            for (j = 0; j < 8; j++) {
                func_80054904_main(grp, j, (D_80111340_rockin_raceway[j] - 156) * scale + 156.0f, i * 12 + 28);
                HuSprScaleSet(grp, j, scale, scale);
            }
        }
    }
}
/* rr2 end func_8010B2B8_rockin_raceway */

/* rr2 func_8010B5DC_rockin_raceway */
#ifdef NON_MATCHING
void func_8010B5DC_rockin_raceway(s32 *times) {
    s32 parts[3];
    s32 *digit;
    s32 *digits;
    s32 i;

    digits = D_80111B00_rockin_raceway;
    for (i = 0; i < 2; i++) {
        parts[0] = times[i] / 1800;
        times[i] -= parts[0] * 1800;
        parts[1] = times[i] / 30;
        times[i] -= parts[1] * 30;
        parts[2] = times[i] / 30.0f * 99.0f;
        digit = &digits[i * 6];
        digit[0] = parts[0] / 10;
        digit[1] = parts[0] - digit[0] * 10;
        digit[2] = parts[1] / 10;
        digit[3] = parts[1] - digit[2] * 10;
        digit[4] = parts[2] / 10;
        digit[5] = parts[2] - digit[4] * 10;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B5DC_rockin_raceway);
#endif
/* rr2 end func_8010B5DC_rockin_raceway */

/* rr2 func_8010B774_rockin_raceway */
void func_8010B774_rockin_raceway(void) {
    HuCamera *cam;
    s32 i;

    Center.x = D_80111350_rockin_raceway.center.x;
    Center.y = D_80111350_rockin_raceway.center.y;
    Center.z = D_80111350_rockin_raceway.center.z;
    CRot.x = D_80111350_rockin_raceway.rot.x;
    CRot.y = D_80111350_rockin_raceway.rot.y;
    CRot.z = D_80111350_rockin_raceway.rot.z;
    CZoom = D_80111350_rockin_raceway.zoom;
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2E_rockin_raceway = 0;
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010C0D8_rockin_raceway);
    cam = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        cam->viewports[i].vp.vscale[0] = cam->viewports[0].vp.vscale[0];
        cam->viewports[i].vp.vscale[1] = cam->viewports[0].vp.vscale[1];
        cam->viewports[i].vp.vscale[2] = cam->viewports[0].vp.vscale[2];
        cam->viewports[i].vp.vtrans[0] = cam->viewports[0].vp.vtrans[0];
        cam->viewports[i].vp.vtrans[1] = cam->viewports[0].vp.vtrans[1];
        cam->viewports[i].vp.vtrans[2] = cam->viewports[0].vp.vtrans[2];
    }
}
/* rr2 end func_8010B774_rockin_raceway */

/* rr2 func_8010B89C_rockin_raceway */
void func_8010B89C_rockin_raceway(void) {
    RrCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_801115F0_rockin_raceway) {
    case 1:
        if ((u16)D_800CDA7C_main[0] & 0x8000) {
            speed = 8.0f;
        }
        if (D_800CDA7C_main[0] & 0x4000) {
            speed = 0.5f;
        }
        if (D_800D5558_main[0] & 0x1000) {
            Center.x = 0.0f;
            Center.y = 191.2f;
            Center.z = 0.2f;
            CRot.x = -14.5f;
            CRot.y = 0.0f;
            CRot.z = 0.0f;
            CZoom = 1069.0f;
        } else {
            c.rot.x = (f32)D_800D20A1_main[0] * 0.125 * speed;
            c.rot.y = (f32)D_800CBB6E_main[0] * 0.125 * speed;
            if (D_800CDA7C_main[0] & 0x200) {
                c.center.x = 2.0 * speed;
            }
            if (D_800CDA7C_main[0] & 0x100) {
                c.center.x = -(2.0 * speed);
            }
            if (D_800CDA7C_main[0] & 0x800) {
                c.center.z = -(2.0 * speed);
            }
            if (D_800CDA7C_main[0] & 0x400) {
                c.center.z = 2.0 * speed;
            }
            if (D_800CDA7C_main[0] & 8) {
                c.center.y = 2.0 * speed;
            }
            if (D_800CDA7C_main[0] & 4) {
                c.center.y = -(2.0 * speed);
            }
            if (D_800CDA7C_main[0] & 1) {
                c.zoom = 2.0 * speed;
            }
            if (D_800CDA7C_main[0] & 2) {
                c.zoom = -(2.0 * speed);
            }
            c.center.x += Center.x;
            c.center.y += Center.y;
            c.center.z += Center.z;
            c.rot.x += CRot.x;
            c.rot.y += CRot.y;
            c.rot.z += CRot.z;
            c.zoom += CZoom;
            func_8010C7CC_rockin_raceway(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
        }
        sprintf(D_800D5218_main, "CAMERA TEST_MODE");
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 80, D_800D5218_main);
        sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 88, D_800D5218_main);
        sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 96, D_800D5218_main);
        sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 104, D_800D5218_main);
        D_800EBE24_minigame = 0;
        break;
    case 2:
        if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
            D_801115F4_rockin_raceway++;
        }
        if (D_800CDA7C_main[0] & 0x202) {
            D_801115F4_rockin_raceway--;
        }
        if (D_800CDA7C_main[0] & 0x404) {
            D_801115F8_rockin_raceway++;
        }
        if (D_800CDA7C_main[0] & 0x808) {
            D_801115F8_rockin_raceway--;
        }
        fontcolor = 8;
        sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 80, D_800D5218_main);
        sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 88, D_800D5218_main);
        sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 96, D_800D5218_main);
        sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 104, D_800D5218_main);
        break;
    default:
        D_800EBE24_minigame = 1;
        break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_801115F0_rockin_raceway & 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (++D_801115F0_rockin_raceway >= 3) {
            D_801115F0_rockin_raceway = 0;
        }
    }
}
/* rr2 end func_8010B89C_rockin_raceway */

/* rr2 func_8010C0D8_rockin_raceway */
void func_8010C0D8_rockin_raceway(omObjData *obj) {
    f32 t;

    if (D_80111C2A_rockin_raceway <= 0) {
        func_8010D134_rockin_raceway(0);
        D_80111C2C_rockin_raceway = 0;
        return;
    }
    if (D_80111C28_rockin_raceway == 0) {
        Center.x = D_80111BE0_rockin_raceway[0].center.x;
        Center.y = D_80111BE0_rockin_raceway[0].center.y;
        Center.z = D_80111BE0_rockin_raceway[0].center.z;
        CRot.x = D_80111BE0_rockin_raceway[0].rot.x;
        CRot.y = D_80111BE0_rockin_raceway[0].rot.y;
        CRot.z = D_80111BE0_rockin_raceway[0].rot.z;
        CZoom = D_80111BE0_rockin_raceway[0].zoom;
        RR_WRAP(CRot.x);
        RR_WRAP(CRot.y);
        RR_WRAP(CRot.z);
        D_80111C2A_rockin_raceway = 0;
    } else {
        switch (D_80111C2E_rockin_raceway) {
        case 0:
            t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
            break;
        case 1:
            t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
            t = sindf(t * 90.0f);
            break;
        default:
            t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
            t = sindf(t * 90.0f);
            t = t * t;
            break;
        }
        Center.x = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.x, D_80111BE0_rockin_raceway[1].center.x);
        Center.y = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.y, D_80111BE0_rockin_raceway[1].center.y);
        Center.z = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.z, D_80111BE0_rockin_raceway[1].center.z);
        CRot.x = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.x, D_80111BE0_rockin_raceway[1].rot.x);
        CRot.y = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.y, D_80111BE0_rockin_raceway[1].rot.y);
        CRot.z = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.z, D_80111BE0_rockin_raceway[1].rot.z);
        CZoom = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].zoom, D_80111BE0_rockin_raceway[1].zoom);
        RR_WRAP(CRot.x);
        RR_WRAP(CRot.y);
        RR_WRAP(CRot.z);
        if (D_80111C28_rockin_raceway > 0) {
            D_80111C28_rockin_raceway--;
        } else {
            D_80111C28_rockin_raceway++;
        }
    }
    D_80111C2C_rockin_raceway = 1;
    func_8010D134_rockin_raceway(0);
}
/* rr2 end func_8010C0D8_rockin_raceway */

/* rr2 func_8010C5E0_rockin_raceway */
void func_8010C5E0_rockin_raceway(s32 idx) {
    RR_WRAP(CRot.x);
    RR_WRAP(CRot.y);
    RR_WRAP(CRot.z);
    D_80111BE0_rockin_raceway[idx].center.x = Center.x;
    D_80111BE0_rockin_raceway[idx].center.y = Center.y;
    D_80111BE0_rockin_raceway[idx].center.z = Center.z;
    D_80111BE0_rockin_raceway[idx].rot.x = CRot.x;
    D_80111BE0_rockin_raceway[idx].rot.y = CRot.y;
    D_80111BE0_rockin_raceway[idx].rot.z = CRot.z;
    D_80111BE0_rockin_raceway[idx].zoom = CZoom;
    D_80111BE0_rockin_raceway[idx].unk1C = D_80111BE0_rockin_raceway[idx].unk20 = 0.0f;
}
/* rr2 end func_8010C5E0_rockin_raceway */

/* rr2 func_8010C7CC_rockin_raceway */
void func_8010C7CC_rockin_raceway(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_80111C28_rockin_raceway = frames - 1;
        D_80111C2A_rockin_raceway = frames;
        if (cx != 65535.0f) {
            D_80111BE0_rockin_raceway[0].center.x = cx;
        } else {
            D_80111BE0_rockin_raceway[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_80111BE0_rockin_raceway[0].center.y = cy;
        } else {
            D_80111BE0_rockin_raceway[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_80111BE0_rockin_raceway[0].center.z = cz;
        } else {
            D_80111BE0_rockin_raceway[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_80111BE0_rockin_raceway[0].rot.x = rx;
        } else {
            D_80111BE0_rockin_raceway[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_80111BE0_rockin_raceway[0].rot.y = ry;
        } else {
            D_80111BE0_rockin_raceway[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_80111BE0_rockin_raceway[0].rot.z = rz;
        } else {
            D_80111BE0_rockin_raceway[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_80111BE0_rockin_raceway[0].zoom = zoom;
        } else {
            D_80111BE0_rockin_raceway[0].zoom = CZoom;
        }
        func_8010C5E0_rockin_raceway(1);
    }
}
/* rr2 end func_8010C7CC_rockin_raceway */

/* rr2 func_8010C9BC_rockin_raceway */
void func_8010C9BC_rockin_raceway(void) {
    D_80111BD8_rockin_raceway->func = NULL;
}
/* rr2 end func_8010C9BC_rockin_raceway */

/* rr2 func_8010C9CC_rockin_raceway */
void func_8010C9CC_rockin_raceway(void) {
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway->func = func_8010C0D8_rockin_raceway;
}
/* rr2 end func_8010C9CC_rockin_raceway */

/* rr2 func_8010CA1C_rockin_raceway */
void func_8010CA1C_rockin_raceway(void) {
    HuCamera *cam;
    s32 i;

    D_80111C34_rockin_raceway = 0;
    D_80111C4C_rockin_raceway = HuMemAllocTag(16 * sizeof(RrFocus), 0x7918);
    D_80111C30_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010CE90_rockin_raceway);
    cam = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        cam->viewports[i].vp.vscale[0] = cam->viewports[0].vp.vscale[0];
        cam->viewports[i].vp.vscale[1] = cam->viewports[0].vp.vscale[1];
        cam->viewports[i].vp.vscale[2] = cam->viewports[0].vp.vscale[2];
        cam->viewports[i].vp.vtrans[0] = cam->viewports[0].vp.vtrans[0];
        cam->viewports[i].vp.vtrans[1] = cam->viewports[0].vp.vtrans[1];
        cam->viewports[i].vp.vtrans[2] = cam->viewports[0].vp.vtrans[2];
    }
}
/* rr2 end func_8010CA1C_rockin_raceway */

/* rr2 func_8010CADC_rockin_raceway */
#ifdef NON_MATCHING
void func_8010CADC_rockin_raceway(Vec *pos, f32 weight) {
    RrFocus *focus;

    if (D_80111C30_rockin_raceway != NULL && D_80111C34_rockin_raceway < 16) {
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].pos.x = pos->x;
        focus = &D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway];
        focus->pos.y = pos->y;
        focus->pos.z = pos->z;
        focus->weight = weight;
        D_80111C34_rockin_raceway++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CADC_rockin_raceway);
#endif
/* rr2 end func_8010CADC_rockin_raceway */

/* rr2 func_8010CB5C_rockin_raceway */
void func_8010CB5C_rockin_raceway(RrKart *kart, f32 weight) {
    Vec pos;

    pos.x = kart->unk58.x + 100.0;
    pos.y = kart->unk58.y + 100.0;
    pos.z = kart->unk58.z;
    func_8010CADC_rockin_raceway(&pos, weight);
    pos.x = kart->unk58.x - 100.0;
    pos.y = kart->unk58.y - 100.0;
    pos.z = kart->unk58.z;
    func_8010CADC_rockin_raceway(&pos, weight);
}
/* rr2 end func_8010CB5C_rockin_raceway */

/* rr2 func_8010CC10_rockin_raceway */
void func_8010CC10_rockin_raceway(void) {
    f32 max[3];
    f32 min[3];
    f32 *p;
    s32 i;
    s32 j;

    if (D_80111C34_rockin_raceway > 0) {
        for (i = 0; i < 4; i++) {
            D_80111C38_rockin_raceway[i] = 0.0f;
        }
        for (i = 0; i < D_80111C34_rockin_raceway; i++) {
            D_80111C38_rockin_raceway[3] += D_80111C4C_rockin_raceway[i].weight;
        }
        for (i = 0; i < 3; i++) {
            max[i] = ((f32 *)&D_80111C4C_rockin_raceway[0].pos)[i];
        }
        for (i = 0; i < 3; i++) {
            min[i] = ((f32 *)&D_80111C4C_rockin_raceway[0].pos)[i];
        }
        for (i = 1; i < D_80111C34_rockin_raceway; i++) {
            p = (f32 *)&D_80111C4C_rockin_raceway[i].pos;
            for (j = 0; j < 3; j++) {
                if (max[j] < p[j]) {
                    max[j] = p[j];
                }
            }
        }
        for (i = 1; i < D_80111C34_rockin_raceway; i++) {
            p = (f32 *)&D_80111C4C_rockin_raceway[i].pos;
            for (j = 0; j < 3; j++) {
                if (min[j] > p[j]) {
                    min[j] = p[j];
                }
            }
        }
        for (i = 0; i < 3; i++) {
            D_80111C38_rockin_raceway[i] = (max[i] + min[i]) * 0.5f;
        }
        if (D_80111C38_rockin_raceway[3] >= 1.0f) {
            D_80111C38_rockin_raceway[3] = 1.0f;
        }
    } else {
        D_80111C38_rockin_raceway[0] = Center.x;
        D_80111C38_rockin_raceway[1] = Center.y;
        D_80111C38_rockin_raceway[2] = Center.z;
        D_80111C38_rockin_raceway[3] = 0.0f;
    }
}
/* rr2 end func_8010CC10_rockin_raceway */

/* rr2 func_8010CE90_rockin_raceway */
void func_8010CE90_rockin_raceway(omObjData *obj) {
    f32 screen[2];
    f32 size;
    f32 scale;
    s32 i;

    size = 0.0f;
    func_8010CC10_rockin_raceway();
    Center.x = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3], Center.x, D_80111C38_rockin_raceway[0]);
    Center.y = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3], Center.y, D_80111C38_rockin_raceway[1]);
    Center.z = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3], Center.z, D_80111C38_rockin_raceway[2]);
    func_8010D134_rockin_raceway(0);
    for (i = 0; i < D_80111C34_rockin_raceway; i++) {
        func_8010D288_rockin_raceway(0, &D_80111C4C_rockin_raceway[i].pos, NULL, screen);
        if (fabs(screen[0]) > size) {
            size = fabs(screen[0]);
        }
        if (fabs(screen[1]) > size) {
            size = fabs(screen[1]);
        }
    }
    if (size != 0.0f) {
        scale = size / 0.8f;
    } else {
        scale = 1.0f;
    }
    D_80111C38_rockin_raceway[4] = scale * CZoom;
    if (D_80111AD8_rockin_raceway == 2) {
        if (D_80111C38_rockin_raceway[4] < 1500.0f) {
            D_80111C38_rockin_raceway[4] = 1500.0f;
        } else if (D_80111C38_rockin_raceway[4] >= 5000.0f) {
            D_80111C38_rockin_raceway[4] = 5000.0f;
        }
    } else {
        if (D_80111C38_rockin_raceway[4] < 1000.0f) {
            D_80111C38_rockin_raceway[4] = 1000.0f;
        } else if (D_80111C38_rockin_raceway[4] >= 5000.0f) {
            D_80111C38_rockin_raceway[4] = 5000.0f;
        }
    }
    CZoom = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3] * 0.5f, CZoom, D_80111C38_rockin_raceway[4]);
    CRot.x = func_8010E608_rockin_raceway(318.38f, CRot.x, 10.0f);
    CRot.y = func_8010E608_rockin_raceway(0.0f, CRot.y, 10.0f);
    D_80111C34_rockin_raceway = 0;
}
/* rr2 end func_8010CE90_rockin_raceway */

/* rr2 func_8010D104_rockin_raceway */
void func_8010D104_rockin_raceway(void) {
    D_80111C30_rockin_raceway->func = NULL;
}
/* rr2 end func_8010D104_rockin_raceway */

/* rr2 func_8010D114_rockin_raceway */
void func_8010D114_rockin_raceway(void) {
    D_80111C34_rockin_raceway = 0;
    D_80111C30_rockin_raceway->func = func_8010CE90_rockin_raceway;
}
/* rr2 end func_8010D114_rockin_raceway */

/* rr2 func_8010D134_rockin_raceway */
#ifdef NON_MATCHING
void func_8010D134_rockin_raceway(s32 idx) {
    HuCamera *cam;
    f32 rx;
    f32 ry;

    cam = &gCameraList[idx];
    rx = CRot.x;
    ry = CRot.y;
    cam->pos.x = Center.x + sindf(ry) * cosdf(rx) * CZoom;
    cam->pos.y = -sindf(rx) * CZoom + Center.y;
    cam->pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
    cam->at.x = Center.x;
    cam->at.y = Center.y;
    cam->at.z = Center.z;
    cam->up.x = sindf(ry) * sindf(rx);
    cam->up.y = cosdf(rx);
    cam->up.z = cosdf(ry) * sindf(rx);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D134_rockin_raceway);
#endif
/* rr2 end func_8010D134_rockin_raceway */

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
