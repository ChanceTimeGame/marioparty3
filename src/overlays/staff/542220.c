#include "common.h"
#include "../ovl_81_name/ovl_81.h"

typedef struct UnkStaff {
    char unk_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} UnkStaff;

typedef struct UnkStaff_1 {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ char unk_20[8];
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ char unk_2A[2];
} UnkStaff_1;

typedef struct UnkStaff_2 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} UnkStaff_2;

void func_8010C680_staff(s16 *, s32 *, f32 *, void *);
void func_8010C8F4_staff(UnkStaff_1 *);
void func_8010CD74_staff(UnkStaff_1 *);
void func_8010CFD4_staff(UnkStaff *);
extern f32 D_80110534_staff;
extern s8 D_80110538_staff;
extern Vec D_80111534_staff;
extern Vec D_80111540_staff;
extern f32 D_80111560_staff;
extern f32 D_80111564_staff;

// story j1
#include "mallocblock.h"

/* Model definition table entry (0x28 stride; storyresult's SrModelDef, msetup's MsModelDef). */
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

/* Camera key (storyresult's SrCamKey). */
typedef struct SrCamKey {
    /* 0x00 */ Vec rot;    /* CRot */
    /* 0x0C */ Vec center; /* Center */
    /* 0x18 */ f32 zoom;   /* CZoom */
    /* 0x1C */ f32 fov;
    /* 0x20 */ f32 unk20;
} SrCamKey; /* size = 0x24 */

typedef void (*SrCamFunc)(s16, s16, s16);

/* Spline path (mstory1's ObPath). */
typedef struct ObPathSeg {
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
} ObPathSeg; /* size = 0x8 */

typedef struct ObPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 flags;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ Vec *points;
    /* 0x0C */ ObPathSeg *segs;
} ObPath; /* size = 0x10 */

void func_80105DB8_staff(SrModelDef *def, s16 model);
void func_80105E6C_staff(SrModelDef *defs, SrModelSlot *slots, s32 count);
u32 func_80105F48_staff(u32 seed);
u32 func_8010601C_staff(void);
u32 func_80106044_staff(u32 max);
void func_8010609C_staff(SrCamKey *key);
void func_8010615C_staff(void);
void func_80106720_staff(void);
void func_8010674C_staff(SrCamKey *keys, f32 speed, SrCamFunc func);
ObPath *func_801085F0_staff(Vec *points, s16 flags);
void func_801088F4_staff(ObPath *path, f32 t, Vec *out);
void func_8010919C_staff(ObPath *path);
f32 func_80018ACC_main(f32 *p, f32 *times, f32 t);
extern f32 D_800CB890_main;
extern f32 D_800CE17C_main[];
extern f32 D_800D5210_main;
extern SrModelDef D_80110FF4_staff[];
extern u32 D_8011053C_staff; /* random seed */
extern Vec D_80111550_staff; /* CRot copy */

/* .bss 0x80111518 (0x18): controller order (storyresult's SrPadWork). */
typedef struct SrPadWork {
    /* 0x00 */ u8 pad[4];  /* connected controllers first, then the free ports */
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
extern SrPadWork D_80111518_staff;
extern s16 D_80111510_staff; /* first controller (D_80111518_staff.pad[0]) */
void func_80106C50_staff(void);
void func_801059A0_staff(void);
void func_80105BD4_staff(omObjData *obj);
void func_80105CB4_staff(omObjData *obj);
void func_80106E20_staff(void);
extern u16 D_80110530_staff;  /* exit delay */
extern s16 D_80111512_staff;  /* 1: entered from story mode (omovlevtno >= 6) */
extern u16 D_80111514_staff;  /* credits variant (omovlevtno, or GwStory.unk1) */
extern s16 D_80111516_staff;  /* next overlay */
extern s16 D_80111530_staff;  /* wipe type */
extern s16 D_80111532_staff;  /* next overlay event */
extern s16 D_8011154C_staff;  /* wipe duration */
extern s16 D_8011155C_staff;  /* exit mode */
/* gamemes.c's GAMEMES (mgenter's MgEntMes): a string drawn as one sprite per character. */
typedef struct StaffMes {
    /* 0x00 */ u8 mesNo;
    /* 0x01 */ u8 stat;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 strGId[16];
    /* 0x40 */ s16 strSprId[16];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} StaffMes; /* size 0x74 */
extern SrCamKey D_80110560_staff;
void func_80107508_staff(void);
void func_80107EB8_staff(void);
void func_80109264_staff(void);
void func_801095E4_staff(void);
void func_8010B514_staff(s16 arg0, s16 arg1);
void func_8010B794_staff(s16 arg0);
void func_8010BF84_staff(void);
void func_8010D1E8_staff(void);
void func_8010D998_staff(void);
UnkStaff_2 *func_8010DE50_staff(s32 file);
void func_8010DEE4_staff(UnkStaff_2 *obj, f32 x, f32 y, f32 z);
void func_8010DEF4_staff(UnkStaff_2 *obj, f32 x, f32 y, f32 z);
void func_8010DF04_staff(UnkStaff_2 *arg0, s16 arg1);
void func_8010DF0C_staff(UnkStaff_2 *obj, s32 mask, s32 bits);
s16 func_8010DF24_staff(UnkStaff_2 *arg0);
extern s32 D_80110540_staff[]; /* per credits variant (D_80111514_staff) */
void func_801073EC_staff(UnkStaff_2 *obj, s32 i);
/* Background star sprites: four layers (the 0x14 records of func_80107740_staff). */
typedef struct StaffStarPos {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} StaffStarPos; /* size = 0x8 */

typedef struct StaffStarLayer {
    /* 0x00 */ StaffStarPos *pos;
    /* 0x04 */ f32 *vel;   /* per star fall speed; func_80107B1C_staff sets it to t * speed */
    /* 0x08 */ f32 *speed;
    /* 0x0C */ s16 grp;
    /* 0x0E */ s16 sprite;
    /* 0x10 */ s16 count;
} StaffStarLayer; /* size = 0x14 */
extern s32 D_8011058C_staff[4]; /* star sprite files */
extern u8 D_8011059C_staff[4];  /* stars per layer */
extern u16 D_801105A0_staff[4]; /* sprite priorities */
extern f32 D_801105A8_staff[4]; /* base speeds */
StaffStarLayer *func_80107740_staff(void);
void func_80107A9C_staff(StaffStarLayer *layers);
void func_80107B1C_staff(StaffStarLayer *layers, f32 t);
void func_80107BA0_staff(StaffStarLayer *layers);
void func_80107DBC_staff(StaffStarLayer *layers);
/* func_80107EB8_staff's work block (one stack object at sp+0x10): the three end-credit names
   and the two shooting stars. */
typedef struct StaffNameWork {
    /* 0x00 */ s16 slot[4];      /* name esprite slots */
    /* 0x08 */ s16 spr[4];       /* name sprites */
    /* 0x10 */ s16 unk10[4];
    /* 0x18 */ s16 x[4];
    /* 0x20 */ f32 y[4];
    /* 0x30 */ s16 shootSlot[4]; /* shooting star esprite slots */
    /* 0x38 */ s16 shootSpr[4];
    /* 0x40 */ s16 timer[4];     /* frames to the next shooting star; < 0 while one falls */
} StaffNameWork; /* size = 0x48 */
typedef struct StaffXY {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} StaffXY;
extern s16 D_801105B8_staff[3];  /* name fall speeds */
extern u16 D_801105C0_staff[3];  /* func_8000BCC8_main arg */
extern StaffXY D_801105C8_staff[3]; /* name start positions */
extern s32 D_801105D4_staff[3];  /* name sprite files */
extern s32 D_801105E0_staff[2];  /* shooting star sprite files */
void func_8000BEAC_main(u16 spriteId, s32 arg1, s32 arg2, s32 arg3);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
extern s32 D_801105F0_staff[2]; /* func_80109264_staff model files */
extern Vec D_801105F8_staff[2]; /* their orbit centres */
extern f32 D_80110610_staff[2]; /* their end angles */
void func_801091CC_staff(Vec *out, Vec *center, f32 angle);
extern Vec D_80110618_staff[]; /* path points (ended by 9999s) */
extern Vec D_80110648_staff[];
/* Credit actors (func_80109D74_staff sets up three from a 0x18-byte definition table). */
typedef struct StaffSVec {
    s16 x;
    s16 y;
    s16 z;
} StaffSVec; /* size = 0x6 */

typedef struct StaffActor {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk0C[0x10];
    /* 0x1C */ s16 model;
    /* 0x1E */ s16 mot;
    /* 0x20 */ char unk20[2];
    /* 0x22 */ StaffSVec ofs;
    /* 0x28 */ s16 sub[4];   /* extra models of the types 4, 7, 8, 10 */
    /* 0x30 */ char unk30[2];
    /* 0x32 */ s16 anim;
    /* 0x34 */ s16 type;
    /* 0x36 */ s16 spread;   /* x offset of sub[0] (types 4, 8, 10) */
    /* 0x38 */ char unk38[2];
    /* 0x3A */ s16 flags;    /* 0: unused, 1: set up, 3: placed; |2 drawn this frame, |4 requested */
} StaffActor; /* size = 0x3C */

typedef struct StaffActorDef {
    /* 0x00 */ f32 scale;
    /* 0x04 */ s32 file;
    /* 0x08 */ s32 motFile;
    /* 0x0C */ StaffSVec ofs;
    /* 0x12 */ s16 type;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 anim;     /* 1-based index into D_80110674_staff, 0: none */
} StaffActorDef; /* size = 0x18 */

typedef struct StaffActorWork {
    /* 0x00 */ StaffActor *actors; /* three */
    /* 0x04 */ char unk04[4];
    /* 0x08 */ s16 cur;
} StaffActorWork;

typedef struct StaffAnimDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ char *name;
} StaffAnimDef; /* size = 0x8 */

extern s16 D_8011066C_staff[4];          /* type 7 sub-model x offsets */
extern StaffAnimDef D_80110674_staff[];
s16 func_8000B13C_main(s32 arg0);
void func_8010992C_staff(Process *proc, s16 model);
s16 func_8010998C_staff(Process *proc, s16 *model, s16 *mot, Vec *pos);
void func_80109D08_staff(Process *proc, s16 model, Vec *pos);
StaffActorDef *func_80109D74_staff(StaffActor *actor, StaffActorDef *def);
/* j1 decl end */

void func_801059A0_staff(void) {
    u16 evt;

    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0x19);
    func_8005A6B0_main();
    func_8004A208_main();
    D_800CD280_main = 0;
    D_80111564_staff = 80.0f;
    D_80111560_staff = 6000.0f;
    D_80110534_staff = 58.0f;
    Hu3DCamSetPerspective(0, 58.0f, 80.0f, 6000.0f);
    D_80111550_staff.x = 0.0f;
    D_80111550_staff.y = 0.0f;
    D_80111550_staff.z = 0.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    func_8010615C_staff();
    omAddObj(0x2710, 0, 0, -1, func_80105BD4_staff);
    HmfLightMaxSet(3);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightDirSet(2, 0.0f, 0.0f, 100.0f);
    HmfLightColorSet(3, 0xF0, 0xF0, 0xF0);
    HmfLightDirSet(3, 0.0f, 100.0f, 0.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_8001F38C_main(0, 0, 0);
    omPrcSetStatBit(omAddPrcObj(func_80106720_staff, 0x1100, 0x400, 0), 0xA0);
    D_8011155C_staff = 0;
    func_80106C50_staff();
    D_80111514_staff = 0;
    D_80111512_staff = 0;
    evt = omovlevtno;
    if (evt < 6) {
        D_80111514_staff = evt;
    } else if (omovlevtno >= 6) {
        D_80111514_staff = GwStory.unk1;
        D_80111512_staff = 1;
    }
    omAddPrcObj(func_80106E20_staff, 0x3F00, 0x1000, 0);
    WipeColorSet(0, 0, 0);
    D_80111530_staff = 0xB;
    D_8011154C_staff = 0x14;
}

void func_80105BD4_staff(omObjData *obj) {
    if (D_80111512_staff == 0 && (D_800D5558_main[D_80111510_staff] & 0x1000)) {
        D_8011155C_staff = 0;
        D_80110530_staff = 1;
    }
    if (D_80110530_staff == 0) {
        if (D_800D530C_main != 0) {
            goto out;
        }
    } else {
        if (D_80110530_staff != 1) {
            D_80110530_staff--;
            return;
        }
    out:
        if (D_80111530_staff >= 0) {
            WipeCreateOut(D_80111530_staff, D_8011154C_staff);
        }
        HuAudSeqFadeOut(0xF);
        obj->func = func_80105CB4_staff;
    }
}

#ifdef NON_MATCHING
/* Instruction-identical to retail; only .rodata differs: retail pads this jump table with a zero word
   because the next file (text 0x80106E20, rodata 0x80111208) starts 8-aligned. */
void func_80105CB4_staff(omObjData *obj) {
    s32 stat;

    if (WipeStatGet() == 0) {
        func_8005F524_main();
        stat = 0x14;
        switch (D_8011155C_staff) {
        case 0:
        default:
            if (D_80111512_staff != 0) {
                omovlhisidx = -1;
                omOvlCallEx(0x58, 0, 0x84);
                return;
            }
            omOvlReturnEx(1);
            break;
        case 2:
            omOvlCallEx(D_80111516_staff, D_80111532_staff, stat);
            break;
        case 1:
            omOvlGotoEx(D_80111516_staff, D_80111532_staff, stat);
            break;
        case 3:
            stat = 0x4090;
            omOvlGotoEx(D_80111516_staff, D_80111532_staff, stat);
            break;
        case 4:
            stat = 0x92;
            omOvlGotoEx(D_80111516_staff, D_80111532_staff, stat);
            break;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105CB4_staff);
#endif

void func_80105DB8_staff(SrModelDef *def, s16 model) {
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

void func_80105E6C_staff(SrModelDef *defs, SrModelSlot *slots, s32 count) {
    s16 i;
    u16 model;

    if (defs == NULL || slots == NULL) {
        return;
    }
    for (i = 0; i < count; defs++, i++, slots++) {
        model = func_8000B108_main(defs->unk0, defs->unk4);
        slots->model = model;
        func_80105DB8_staff(defs, model);
        slots->unk2 = HmfModelData[(s16)model].unk02;
        if (slots->unk2 >= 0) {
            func_8001C814_main(model, -1, defs->unkA);
        }
    }
}

u32 func_80105F48_staff(u32 seed) {
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

u32 func_8010601C_staff(void) {
    return D_8011053C_staff = func_80105F48_staff(D_8011053C_staff);
}

u32 func_80106044_staff(u32 max) {
    return ((D_8011053C_staff = func_80105F48_staff(D_8011053C_staff)) & 0x7FFFFFFF) % max;
}

void func_8010609C_staff(SrCamKey *key) {
    f32 fov;

    CRot = key->rot;
    D_80111550_staff = CRot;
    Center = key->center;
    CZoom = key->zoom;
    fov = key->fov;
    if (fov != D_80110534_staff) {
        D_80110534_staff = fov;
        Hu3DCamSetPerspective(0, fov, D_80111564_staff, D_80111560_staff);
    }
}

#ifdef NON_MATCHING
/* Residue (masked 11): retail schedules the &Center load before the first mul.s, and f2/f12 swap in the distance sum (as msetup func_801068F4_msetup). */
void func_8010615C_staff(void) {
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

    if (D_80110538_staff == 0) {
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
        pos = D_80111540_staff;
        at = D_80111534_staff;
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
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010615C_staff);
#endif

void func_80106720_staff(void) {
    while (1) {
        func_8010615C_staff();
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
/* Residue: two hazard nops after cosdf() (W2DC_BLANKSTRIP) and f2/f12 swapped in the distance sum. */
void func_8010674C_staff(SrCamKey *keys, f32 speed, SrCamFunc func) {
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
        D_80111550_staff.x = CRot.x = out[0];
        D_80111550_staff.y = CRot.y = out[1];
        D_80111550_staff.z = CRot.z = out[2];
        CZoom = out[6];
        gCameraList->fov[0] = D_80110534_staff = out[7];
        if (func != NULL) {
            fn((s16)total, seg, i);
        }
        HuPrcVSleep();
    }
    i = seg + 1;
    D_80111550_staff.x = CRot.x = keys[i].rot.x;
    D_80111550_staff.y = CRot.y = keys[i].rot.y;
    D_80111550_staff.z = CRot.z = keys[i].rot.z;
    CZoom = keys[i].zoom;
    Center.x = keys[i].center.x;
    Center.y = keys[i].center.y;
    Center.z = keys[i].center.z;
    gCameraList->fov[0] = D_80110534_staff = keys[i].fov;
    D_800CB99C_main = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010674C_staff);
#endif

#ifdef NON_MATCHING
/* Instruction-identical to retail; only the file-end padding differs: retail has a file boundary at
   0x80106E20 (three nops after this function), which the unit cannot express without a split. */
void func_80106C50_staff(void) {
    s16 i;
    s16 n;
    s16 j;
    s16 k;

    for (i = 0; i < 4; i++) {
        D_80111518_staff.pad[i] = 0xFF;
        D_80111518_staff.unk4[i] = i;
        D_80111518_staff.unk8[i] = 0xFF;
        D_80111518_staff.unkC[i] = 0;
    }
    for (i = 0, n = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            D_80111518_staff.pad[n] = i;
            n++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_80111518_staff.pad[i] == 0xFF) {
            for (j = 0; j < 4; j++) {
                for (k = 0; k < 4; k++) {
                    if (D_80111518_staff.pad[k] == j) {
                        break;
                    }
                }
                if (k == 4) {
                    break;
                }
            }
            D_80111518_staff.pad[i] = j;
        }
    }
    D_80111518_staff.unk12 = 0;
    D_80111518_staff.unk16 = 0;
    D_80111518_staff.unk13 = 0;
    D_80111518_staff.unk14 = n;
    D_80111518_staff.unk10 = 0;
    D_80111518_staff.unk11 = 4;
    D_80111518_staff.unk15 = 0;
    D_80111510_staff = D_80111518_staff.pad[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106C50_staff);
#endif

void func_80106E20_staff(void) {
    StaffMes mes;
    s16 names;
    s16 scene;
    s16 stat3;
    s16 stat4;
    s16 title;
    s16 stat6;
    s16 stat7;
    s16 group;
    s32 i;
    s16 n;
    s16 alpha;

    D_800CD280_main = 1;
    func_8010609C_staff(&D_80110560_staff);
    func_8010B514_staff(0, 6);
    func_8010B514_staff(1, 0xC);
    names = 0;
    omAddPrcObj(func_80107EB8_staff, 0x4200, 0x800, 0)->user_data = &names;
    scene = 0;
    omAddPrcObj(func_801095E4_staff, 0x4000, 0, 0)->user_data = &scene;
    stat3 = 0;
    omAddPrcObj(func_8010BF84_staff, 0x4000, 0, 0)->user_data = &stat3;
    stat4 = 0;
    omAddPrcObj(func_80109264_staff, 0x4000, 0, 0)->user_data = &stat4;
    title = 0;
    omAddPrcObj(func_80107508_staff, 0x1000, 0, 0)->user_data = &title;
    group = mes.strGId[func_8003A308_main((char *)&mes, "MARIO PARTY 3 STAFF", 0, -1, -1)];
    func_80054904_main(group, 0, 0xA0, 0x78);
    for (i = 1; i < 0x14; i++) {
        func_80055458_main(group, i, 0);
        HuSprAttrSet(group, i, 0x8000);
    }
    WipeCreateIn(D_80111530_staff, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudSeqPlay(6);
    title = 1;
    for (n = 0x1E; n != 0; n--) {
        HuPrcVSleep();
    }
    for (i = 1; i < 0x14; i++) {
        HuSprAttrReset(group, i, 0x8000);
    }
    for (alpha = 0x40; alpha <= 0x100; alpha += 0x40) {
        for (i = 1; i < 0x14; i++) {
            func_80055458_main(group, i, alpha);
        }
        HuPrcVSleep();
    }
    title = 2;
    for (n = 0xB4; n != 0; n--) {
        HuPrcVSleep();
    }
    for (alpha = 0xF0; alpha >= 0; alpha -= 0x10) {
        for (i = 1; i < 0x14; i++) {
            func_80055458_main(group, i, alpha);
        }
        HuPrcVSleep();
    }
    func_8003B128_main((char *)&mes);
    names = 2;
    HuPrcVSleep();
    stat4 = 1;
    do {
        HuPrcVSleep();
    } while (stat4 >= 0);
    scene = 1;
    names = 1;
    for (n = 0x78; n != 0; n--) {
        HuPrcVSleep();
    }
    stat3 = 1;
    do {
        HuPrcVSleep();
    } while (stat3 != 0);
    scene = 2;
    HuAudFXPlay(0x229);
    HuAudSeqFadeOut(0xF0);
    for (n = 0x4B; n != 0; n--) {
        HuPrcVSleep();
    }
    WipeColorSet(0, 0, 0);
    WipeCreateOut(0xB, 4);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8010B794_staff(0);
    func_8010B794_staff(1);
    scene = -1;
    names = -1;
    HuPrcSleep(2);
    stat6 = 1;
    omAddPrcObj(func_8010D1E8_staff, 0x4000, 0x1800, 0)->user_data = &stat6;
    while (stat6 != 0) {
        HuPrcVSleep();
    }
    HuAudSeqPlay(0x4E);
    WipeCreateIn(0xB, 4);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    for (n = 0xB4; n != 0; n--) {
        HuPrcVSleep();
    }
    HuAudSeqFadeOut(0x4A);
    WipeCreateOut(0xB, 0x18);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    stat6 = -1;
    stat7 = 1;
    omAddPrcObj(func_8010D998_staff, 0x4000, 0x1000, 0)->user_data = &stat7;
    while (stat7 != 0) {
        HuPrcVSleep();
    }
    WipeCreateIn(0xB, 0x18);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    stat7 = 1;
    HuAudFXPlay(0x22A);
    while (stat7 != 0) {
        HuPrcVSleep();
    }
    while (TRUE) {
        if ((D_800D5558_main[0] & 0xD000) || (D_800D5558_main[1] & 0xD000) || (D_800D5558_main[2] & 0xD000) ||
            (D_800D5558_main[3] & 0xD000)) {
            break;
        }
        HuPrcVSleep();
    }
    D_80110530_staff = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_801073EC_staff(UnkStaff_2 *obj, s32 i) {
    u32 r;
    s32 x;
    s32 y;

    r = func_8010601C_staff();
    x = (r & 0xFF) - 0x80;
    y = -0x1F4 - ((r >> 8) & 0xFF);
    func_8010DEF4_staff(obj, x, y, 0.0f);
    x = func_80106044_staff(0x64) + i * 0x1F4 - 0x226;
    y = (func_8010601C_staff() & 0x3F) + 0xDA;
    func_8010DEE4_staff(obj, x, y, (s32)(func_80106044_staff(0x1F4) - 0x320));
    func_8010DF04_staff(obj, func_80106044_staff(0x3C) + 0x1E);
}

#ifdef NON_MATCHING
/* masked 0; raw: v0/v1 swap in the table index. Retail also has a file boundary at 0x80107740
   (three nops after this function), which the unit cannot express without a split. */
void func_80107508_staff(void) {
    UnkStaff_2 *obj[3];
    s16 wait[3];
    s16 *stat;
    s32 i;
    u16 var;
    s16 idx;

    stat = HuPrcCurrentGet()->user_data;
    var = D_80111514_staff;
    idx = (var < 6) ? var : 0;
    for (i = 0; i < 3; i++) {
        obj[i] = func_8010DE50_staff(D_80110540_staff[idx]);
        func_801073EC_staff(obj[i], i);
        func_8010DF0C_staff(obj[i], 1, 1);
        wait[i] = 0;
    }
    while (*stat >= 0) {
        switch (*stat) {
        case 1:
            for (i = 0; i < 3; i++) {
                wait[i] = 1;
            }
            wait[0] = 1;
            break;
        case 2:
            for (i = 0; i < 3; i++) {
                func_8010DF0C_staff(obj[i], 4, 4);
            }
            *stat = -1;
            break;
        case 0:
            break;
        }
        if (*stat == 1) {
            for (i = 0; i < 3; i++) {
                if (wait[i] != 0) {
                    if (--wait[i] == 0) {
                        func_8010DF0C_staff(obj[i], 1, 0);
                    }
                } else if (func_8010DF24_staff(obj[i]) & 1) {
                    wait[i] = (rand8() & 0xF) + 1;
                }
            }
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107508_staff);
#endif

#ifdef NON_MATCHING
/* Register allocation (masked 20): retail keeps count in s3 and spills the vel pointer to the stack;
   this spills count instead. Logic checked against the asm. */
StaffStarLayer *func_80107740_staff(void) {
    StaffStarLayer *layers;
    StaffStarLayer *layer;
    StaffStarPos *pos;
    f32 *vel;
    f32 *speed;
    s16 i;
    s16 j;
    u8 count;
    s16 grp;
    s16 sprite;
    u16 pri;
    f32 base;
    u32 r;
    u8 red;
    u8 green;
    s32 x;
    s32 y;

    layers = HuMemAllocTag(4 * sizeof(StaffStarLayer), 0x7918);
    memset(layers, 0, 4 * sizeof(StaffStarLayer));
    for (i = 0, layer = layers; i < 4; i++, layer++) {
        count = D_8011059C_staff[i];
        pos = HuMemAllocTag(count * sizeof(StaffStarPos), 0x7918);
        vel = HuMemAllocTag(count * sizeof(f32), 0x7918);
        speed = HuMemAllocTag(count * sizeof(f32), 0x7918);
        grp = HuSprGrpCreate(count, 0);
        sprite = func_8000B838_main(D_8011058C_staff[i]);
        pri = D_801105A0_staff[i];
        layer->pos = pos;
        layer->grp = grp;
        layer->sprite = sprite;
        layer->vel = vel;
        layer->speed = speed;
        layer->count = count;
        base = D_801105A8_staff[i];
        for (j = 0; j < count; j++) {
            func_80055458_main(grp, j, 0x100);
            HuSprAttrReset(grp, j, 0xFFFF);
            HuSprAttrSet(grp, j, 0x5000);
            HuSprScaleSet(grp, j, 1.0f, 1.0f);
            func_800550F4_main(grp, j, 0);
            func_80055024_main(grp, j, sprite, 0);
            HuSprPriSet(grp, j, pri);
            r = func_8010601C_staff();
            red = r | 0xC0;
            r >>= 7;
            green = r | 0xC0;
            r >>= 7;
            func_80055420_main(grp, j, red, green, r | 0xC0);
            r = func_8010601C_staff() & 0x7FFFFFFF;
            x = r % 320;
            r >>= 6;
            y = r % 304 - 0x40;
            pos->x = x;
            pos->y = y;
            func_80054904_main(grp, j, x, y);
            *vel = 0.0f;
            r >>= 6;
            *speed = base + (base / 16.0f) * (f32)((s32)(r & 3) - 1);
            pos++;
            vel++;
            speed++;
        }
    }
    return layers;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107740_staff);
#endif

void func_80107A9C_staff(StaffStarLayer *layers) {
    StaffStarLayer *layer;
    s32 i;

    for (i = 0, layer = layers; i < 4; i++, layer++) {
        HuSprGrpKill(layer->grp);
        HuSprKill(layer->sprite);
        HuMemFree(layer->pos);
        HuMemFree(layer->vel);
        HuMemFree(layer->speed);
    }
    HuMemFree(layers);
}

void func_80107B1C_staff(StaffStarLayer *layers, f32 t) {
    StaffStarLayer *layer;
    f32 *vel;
    f32 *speed;
    s16 i;
    s16 j;
    s16 n;

    for (i = 0, layer = layers; i < 4; i++, layer++) {
        vel = layer->vel;
        speed = layer->speed;
        n = layer->count;
        for (j = 0; j < n; j++, vel++, speed++) {
            *vel = t * *speed;
        }
    }
}

#ifdef NON_MATCHING
/* masked 7: GCC hoists the first r % 160 multiply above the i == 0 branch (one extra nop). */
void func_80107BA0_staff(StaffStarLayer *layers) {
    StaffStarLayer *layer;
    StaffStarPos *pos;
    f32 *vel;
    s16 i;
    s16 j;
    s16 n;
    s16 grp;
    u32 r;
    u32 x;

    for (i = 0, layer = layers; i < 4; i++, layer++) {
        vel = layer->vel;
        grp = layer->grp;
        pos = layer->pos;
        n = layer->count;
        for (j = 0; j < n; j++, pos++, vel++) {
            pos->y += *vel;
            if (pos->y >= 240.0f) {
                r = func_8010601C_staff() & 0x7FFFFFFF;
                if (i == 0) {
                    x = r % 160;
                    r >>= 5;
                    x += r % 160;
                    pos->x = (s16)x;
                } else {
                    pos->x = r % 320;
                }
                r >>= 6;
                pos->y = -(s32)(r & 0x1F);
            }
            func_80054904_main(grp, j, pos->x, pos->y);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107BA0_staff);
#endif

void func_80107DBC_staff(StaffStarLayer *layers) {
    StaffStarLayer *layer;
    s16 i;
    s16 j;
    s16 n;
    s16 grp;
    u32 r;
    s16 t;
    s32 alpha;
    u32 m;

    r = 0;
    t = 0;
    for (i = 0, layer = layers; i < 4; i++, layer++) {
        grp = layer->grp;
        n = layer->count;
        for (j = 0; j < n; j++) {
            t -= 4;
            if (t < 0) {
                t = 0x1F;
                r = func_8010601C_staff();
            }
            m = r & 0xF;
            r >>= 4;
            alpha = 0x100;
            if (m == 0) {
                alpha = 0xB4;
            }
            func_80055458_main(grp, j, alpha);
        }
    }
}

#ifdef NON_MATCHING
/* Register allocation only (same instructions otherwise): retail keeps nameT in s7 and spills the
   layers pointer. Retail also has a file boundary at 0x801085F0 (one nop after this function). */
void func_80107EB8_staff(void) {
    StaffNameWork w;
    s16 pos[2][2];
    StaffStarLayer *layers;
    s16 active;
    s16 logoSpr;
    s16 logoSlot;
    s16 logoOn;
    s16 *stat;
    s16 prev;
    s16 namesOn;
    s16 left;
    s32 i;
    u16 slot;
    s32 x;
    f32 fade;
    f32 fadeSpd;
    f32 logoA;
    f32 logoSpd;
    f32 nameT;
    f32 nameSpd;

    stat = HuPrcCurrentGet()->user_data;
    layers = func_80107740_staff();
    for (i = 0; i < 2; i++) {
        w.shootSpr[i] = func_8000B838_main(D_801105E0_staff[i]);
        w.shootSlot[i] = InitEspriteSlot(w.shootSpr[i], 0, 0);
        func_8000BEAC_main(w.shootSlot[i], 0xFF, 0xFF, 0xFF);
        func_8000BC48_main(w.shootSlot[i], 0x4000);
        func_8000BB94_main(w.shootSlot[i]);
        w.timer[i] = (rand8() & 0x7F) + 0x78;
    }
    func_8000BEAC_main(w.shootSlot[1], 0xFF, 0xC8, 0xC8);
    logoSpr = func_8000B838_main(0x16001A);
    logoSlot = InitEspriteSlot(logoSpr, 0, 0);
    func_8000BC48_main(logoSlot, 0x4000);
    func_8000BBD4_main(logoSlot, 0xA0, 0x78);
    func_8000BCC8_main(logoSlot, 0xFFF0);
    logoOn = 1;
    for (i = 0; i < 3; i++) {
        w.spr[i] = func_8000B838_main(D_801105D4_staff[i]);
        w.slot[i] = slot = InitEspriteSlot(w.spr[i], 0, 0);
        func_8000BCC8_main(slot, D_801105C0_staff[i]);
        w.x[i] = D_801105C8_staff[i].x;
        w.y[i] = D_801105C8_staff[i].y;
        func_8000BBD4_main(slot, w.x[i], w.y[i]);
    }
    namesOn = 1;
    nameSpd = logoSpd = fadeSpd = 0.0f;
    active = 0;
    prev = *stat;
    while (prev >= 0) {
        if (prev != *stat) {
            switch (*stat) {
            case 1:
                active = 1;
                fadeSpd = 1.0f / 120.0f;
                fade = 0.0f;
                *stat = 0;
                if (logoOn) {
                    logoA = 256.0f;
                    logoSpd = -64.0f / 120.0f;
                }
                if (namesOn) {
                    nameSpd = 1.0f / 120.0f;
                    nameT = 0.0f;
                }
                break;
            case 2:
                for (i = 0; i < 3; i++) {
                    func_8000BC48_main(w.slot[i], 0x4000);
                }
                break;
            case -1:
                prev = -1;
                continue;
            case 0:
                break;
            }
            prev = *stat;
        }
        if (fadeSpd != 0.0f) {
            fade += fadeSpd;
            if (fade >= 1.0f) {
                fade = 1.0f;
                fadeSpd = 0.0f;
            } else if (fade <= 0.0f) {
                fade = 0.0f;
                fadeSpd = 0.0f;
                active = 0;
            }
            func_80107B1C_staff(layers, fade);
        }
        if (active) {
            func_80107BA0_staff(layers);
            for (i = 0; i < 2; i++) {
                if (--w.timer[i] == 0) {
                    func_8000BB54_main(w.shootSlot[i]);
                    x = func_80106044_staff(0xA0);
                    x += func_80106044_staff(0xA0);
                    pos[i][0] = x;
                    pos[i][1] = -0x80;
                    func_8000BBD4_main(w.shootSlot[i], pos[i][0], -0x80);
                } else if (w.timer[i] < 0) {
                    pos[i][1] += 8;
                    func_8000BBD4_main(w.shootSlot[i], pos[i][0], pos[i][1]);
                    if (pos[i][1] > 0xF0) {
                        func_8000BB94_main(w.shootSlot[i]);
                        w.timer[i] = (rand8() & 0x7F) + 1;
                    }
                }
            }
        }
        func_80107DBC_staff(layers);
        if (logoOn != 0) {
            if (logoSpd != 0.0f) {
                logoA += logoSpd;
                if (logoA <= 0.0f) {
                    logoA = 0.0f;
                    logoSpd = 0.0f;
                }
                func_8000BBFC_main(logoSlot, logoA);
                if (logoA == 0.0f) {
                    func_8000C184_main(logoSlot);
                    HuSprKill(logoSpr);
                    logoSlot = -1;
                    logoSpr = -1;
                    logoOn = 0;
                }
            }
        }
        if (namesOn != 0) {
            if (nameSpd != 0.0f) {
                nameT += nameSpd;
                left = 3;
                if (nameT >= 1.0f) {
                    nameT = 1.0f;
                }
                for (i = 0; i < 3; i++) {
                    if (w.y[i] < 304.0f) {
                        w.y[i] += nameT * D_801105B8_staff[i];
                        func_8000BBD4_main(w.slot[i], w.x[i], w.y[i]);
                    } else {
                        left--;
                        if (w.slot[i] >= 0) {
                            func_8000C184_main(w.slot[i]);
                            HuSprKill(w.spr[i]);
                            w.spr[i] = -1;
                            w.slot[i] = -1;
                        }
                    }
                }
                if (left == 0) {
                    namesOn = 0;
                }
            }
        }
        HuPrcVSleep();
    }
    func_80107A9C_staff(layers);
    for (i = 0; i < 2; i++) {
        func_8000C184_main(w.shootSlot[i]);
        HuSprKill(w.shootSpr[i]);
    }
    *stat = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107EB8_staff);
#endif

ObPath *func_801085F0_staff(Vec *points, s16 flags) {
    ObPath *path;
    Vec *prev;
    Vec *cur;
    ObPathSeg *seg;
    f32 total;
    f32 pos;
    f32 len;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 n;
    s16 i;

    path = HuMemAllocTag(sizeof(ObPath), 0x7918);
    path->flags = flags;
    path->points = points;
    prev = points;
    cur = prev + 1;
    total = 0.0f;
    n = 0;
    while (cur->x != 9999.0f || cur->y != 9999.0f || cur->z != 9999.0f) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
        n++;
        cur++;
        prev++;
    }
    if (flags & 1) {
        dx = points->x - prev->x;
        dy = points->y - prev->y;
        dz = points->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    n++;
    path->count = n;
    seg = HuMemAllocTag(n * sizeof(ObPathSeg), 0x7918);
    path->segs = seg;
    prev = points;
    cur = prev + 1;
    pos = 0.0f;
    for (i = 0; i < n; i++, prev++, cur++, seg++) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        if ((flags & 1) && i == n - 1) {
            dx = points->x - prev->x;
            dy = points->y - prev->y;
            dz = points->z - prev->z;
        }
        len = HuSqrtf(dx * dx + dy * dy + dz * dz);
        seg->start = pos / total;
        seg->end = (pos + len) / total;
        if (seg->end > 1.0f) {
            seg->end = 1.0001f;
        }
        pos += len;
    }
    return path;
}

#ifdef NON_MATCHING
/* the point at t (0..1) along a path: a spline through the four points around the segment t
   falls in */
void func_801088F4_staff(ObPath *path, f32 t, Vec *out) {
    f32 p[4];
    f32 times[4];
    ObPathSeg *segs;
    Vec *pts;
    s16 i;

    if (t >= 1.0f) {
        out->x = path->points[path->count - 1].x;
        out->y = path->points[path->count - 1].y;
        out->z = path->points[path->count - 1].z;
        return;
    }
    for (i = 0, segs = path->segs; i < path->count; i++, segs++) {
        if (t <= segs->start) {
            break;
        }
    }
    i--;
    i = (i < 0) ? 0 : i;
    if (i >= path->count - 1) {
        i--;
    }
    segs = path->segs;
    if (path->flags & 1) {
        times[0] = (i == 0) ? -(1.0f - segs[path->count - 1].start) : segs[i - 1].start;
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[path->count - 1].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[0].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[0].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[path->count - 1].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[0].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[0].z : pts[i + 2].z;
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = segs[i - 1].start;
        }
        times[1] = segs[i].start;
        times[2] = (i >= path->count - 1) ? segs[path->count - 1].end : segs[i + 1].start;
        times[3] = (i + 1 >= path->count - 1) ? segs[path->count - 1].end : segs[i + 2].start;
        pts = path->points;
        p[0] = (i == 0) ? pts[0].x : pts[i - 1].x;
        p[1] = pts[i].x;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].x : pts[i + 1].x;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].x : pts[i + 2].x;
        out->x = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].y : pts[i - 1].y;
        p[1] = pts[i].y;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].y : pts[i + 1].y;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].y : pts[i + 2].y;
        out->y = func_80018ACC_main(p, times, t);
        p[0] = (i == 0) ? pts[0].z : pts[i - 1].z;
        p[1] = pts[i].z;
        p[2] = (i >= path->count - 1) ? pts[path->count - 1].z : pts[i + 1].z;
        p[3] = (i + 1 >= path->count - 1) ? pts[path->count - 1].z : pts[i + 2].z;
    }
    out->z = func_80018ACC_main(p, times, t);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801088F4_staff);
#endif

void func_8010919C_staff(ObPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

void func_801091CC_staff(Vec *out, Vec *center, f32 angle) {
    f32 x;
    f32 y;

    x = cosdf(angle) * 1235.0f;
    y = sindf(angle) * 880.0f;
    x += center->x;
    y += center->y;
    out->x = x;
    out->y = y;
    out->z = center->z;
}

void func_80109264_staff(void) {
    f32 angle[2];
    f32 speed[2];
    Vec pos;
    s16 model[2];
    s16 *stat;
    s16 prev;
    s32 i;
    s16 m;
    f32 rz;

    rz = 0.0f;
    stat = HuPrcCurrentGet()->user_data;
    for (i = 0; i < 2; i++) {
        m = func_8000B108_main(D_801105F0_staff[i], 0x2A9);
        model[i] = m;
        func_8001C814_main(m, -1, 2);
        angle[i] = 270.0f;
        func_801091CC_staff(&pos, &D_801105F8_staff[i], 270.0f);
        Hu3DModelPosSet(m, pos.x, pos.y, pos.z);
    }
    func_800461B4_main(m);
    prev = 0;
    speed[0] = speed[1] = 0.0f;
    do {
        if (prev != *stat) {
            switch (*stat) {
            case 1:
                speed[1] = -3.0f;
                break;
            case 2:
                speed[0] = 3.0f;
                break;
            case 3:
                prev = -1;
                continue;
            case 0:
                break;
            }
            prev = *stat;
        }
        for (i = 0; i < 2; i++) {
            if (speed[i] != 0.0f) {
                angle[i] += speed[i];
                m = 0;
                if (speed[i] < 0.0f) {
                    if (angle[i] <= D_80110610_staff[i]) {
                        m = 1;
                    }
                } else if (angle[i] >= D_80110610_staff[i]) {
                    m++;
                }
                if (m) {
                    angle[i] = D_80110610_staff[i];
                    speed[i] = 0.0f;
                    (*stat)++;
                }
                func_801091CC_staff(&pos, &D_801105F8_staff[i], angle[i]);
                Hu3DModelPosSet(model[i], pos.x, pos.y, pos.z);
                switch (i) {
                case 0:
                    rz = angle[i];
                    break;
                case 1:
                    rz = angle[i] - 180.0f;
                    break;
                }
                Hu3DModelRotSet(model[i], 0.0f, 0.0f, rz);
            }
        }
        HuPrcVSleep();
    } while (prev >= 0);
    func_80046558_main(model[1]);
    func_8001ACDC_main(model[0]);
    func_8001ACDC_main(model[1]);
    HuPrcVSleep();
    *stat = -1;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
/* masked 0; raw: s1/s2 swap (prev and path) and f0/f2 in the cos term. */
void func_801095E4_staff(void) {
    Vec pos;
    ObPath *path;
    ObPath *next;
    s16 *stat;
    s16 model;
    s16 prev;
    s32 done;
    f32 angle;
    f32 angleSpd;
    f32 rot;
    f32 rotSpd;
    f32 rotEnd;

    prev = 0;
    stat = HuPrcCurrentGet()->user_data;
    model = func_8000B108_main(0xA015F, 0x2A9);
    func_8001C814_main(model, -1, 2);
    path = func_801085F0_staff(D_80110618_staff, 0);
    next = func_801085F0_staff(D_80110648_staff, 0);
    func_801088F4_staff(path, 0.0f, &pos);
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    rot = rotSpd = rotEnd = angleSpd = angle = 0.0f;
    do {
        if (prev != *stat) {
            switch (*stat) {
            case 1:
                if (path != NULL) {
                    angle = 180.0f;
                    angleSpd = 0.75f;
                    rotEnd = 8.0f;
                    rot = 0.0f;
                    rotSpd = 1.0f / 30.0f;
                }
                break;
            case 2:
                if (path == NULL && next != NULL) {
                    path = next;
                    angle = 180.0f;
                    angleSpd = 2.0f;
                    rotEnd = 0.0f;
                    rot = 8.0f;
                    rotSpd = -8.0f / 90.0f;
                    next = NULL;
                }
                break;
            case -1:
                prev = -1;
                continue;
            case 0:
                break;
            }
            prev = *stat;
        }
        if (angleSpd != 0.0f) {
            angle += angleSpd;
            done = 0;
            if (angle >= 360.0f) {
                angle = 0.0f;
                angleSpd = 0.0f;
                done = 1;
            }
            func_801088F4_staff(path, (cosdf(angle) + 1.0f) * 0.5f, &pos);
            Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
            if (done) {
                func_8010919C_staff(path);
                path = NULL;
                *stat = 0;
            }
        }
        if (rotSpd != 0.0f) {
            rot += rotSpd;
            done = 0;
            if (rotSpd < 0.0f) {
                if (rot <= rotEnd) {
                    done = 1;
                }
            } else if (rot >= rotEnd) {
                done++;
            }
            if (done) {
                rotSpd = 0.0f;
                rot = rotEnd;
            }
            Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        }
        HuPrcVSleep();
    } while (prev >= 0);
    func_8001ACDC_main(model);
    *stat = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801095E4_staff);
#endif

void func_8010992C_staff(Process *proc, s16 model) {
    StaffActor *actor;
    s32 i;

    actor = ((StaffActorWork *)proc->user_data)->actors;
    for (i = 0; i < 3; i++, actor++) {
        if (actor->flags == 3 && actor->model == model) {
            break;
        }
    }
    if (i < 3) {
        actor->flags |= 4;
    }
}

s16 func_8010998C_staff(Process *proc, s16 *model, s16 *mot, Vec *pos) {
    StaffActorWork *work;
    StaffActor *actor;
    f32 x;
    f32 y;
    f32 z;
    s16 cur;
    s32 i;
    s16 sub;

    work = proc->user_data;
    cur = work->cur;
    actor = &work->actors[cur];
    if (actor->flags == 0) {
        *model = -1;
        *mot = -1;
        return -1;
    }
    actor->flags |= 2;
    *model = actor->model;
    *mot = actor->mot;
    actor->pos = *pos;
    x = pos->x + actor->ofs.x;
    y = pos->y + actor->ofs.y;
    z = pos->z + actor->ofs.z;
    switch (actor->type) {
    case 4:
        Hu3DModelPosSet(actor->model, x - actor->spread, y, z);
        func_8001C258_main(actor->model, 4, 0);
        Hu3DModelPosSet(actor->sub[0], x + actor->spread, y, z);
        func_8001C258_main(actor->sub[0], 4, 0);
        break;
    case 7:
        Hu3DModelPosSet(actor->model, x, y, z);
        func_8001C258_main(actor->model, 4, 0);
        for (i = 0; i < 4; i++) {
            sub = actor->sub[i];
            Hu3DModelPosSet(sub, x + D_8011066C_staff[i], y, z);
            func_8001C258_main(sub, 4, 0);
        }
        break;
    case 8:
        Hu3DModelPosSet(actor->model, x - actor->spread, y, z);
        func_8001C258_main(actor->model, 4, 0);
        Hu3DModelPosSet(actor->sub[0], x + actor->spread, y, z);
        func_8001C258_main(actor->sub[0], 4, 0);
        break;
    case 10:
        Hu3DModelPosSet(actor->model, x - actor->spread, y, z);
        func_8001C258_main(actor->model, 4, 0);
        Hu3DModelPosSet(actor->sub[0], x + actor->spread, y, z);
        func_8001C258_main(actor->sub[0], 4, 0);
        break;
    case 0:
    default:
        Hu3DModelPosSet(actor->model, x, y, z);
        func_8001C258_main(actor->model, 4, 0);
        break;
    }
    if (++work->cur >= 3) {
        work->cur = 0;
    }
    return cur;
}

void func_80109D08_staff(Process *proc, s16 model, Vec *pos) {
    StaffActor *actor;
    s32 i;

    actor = ((StaffActorWork *)proc->user_data)->actors;
    for (i = 0; i < 3; i++, actor++) {
        if (actor->flags == 3 && actor->model == model) {
            break;
        }
    }
    if (i < 3) {
        actor->pos = *pos;
    }
}

StaffActorDef *func_80109D74_staff(StaffActor *actor, StaffActorDef *def) {
    void *data;
    s32 i;
    s16 anim;
    s16 model;
    s16 mot;

    for (i = 0; i < 3; i++, actor++, def++) {
        anim = 0;
        actor->flags = 1;
        actor->type = def->type;
        actor->ofs = def->ofs;
        model = func_8000B108_main(def->file, 0x2AD);
        func_8001C814_main(model, -1, 2);
        Hu3DModelScaleSet(model, def->scale, def->scale, def->scale);
        actor->anim = -1;
        if (def->anim != 0) {
            /* retail reuses the loop counter as the animation index */
            i = def->anim - 1;
            anim = 1;
            data = DataRead(D_80110674_staff[i].file);
            actor->anim = HmfAnimCreate(HmfModelData[model].hmf, data, 0, D_80110674_staff[i].name);
            HuMemMemoryFreePerm(data);
        }
        if (def->motFile != 0) {
            mot = func_8000B13C_main(def->motFile);
            func_8001C5B4_main(model, mot);
            func_8001C814_main(model, -1, 2);
        } else {
            mot = -1;
        }
        actor->model = model;
        actor->mot = mot;
        if (anim) {
            func_8001C448_main(model);
        }
        func_8001C514_main(model);
    }
    return def;
}

// story j2
#include "mallocblock.h"

typedef struct StaffTextGrp {
    /* 0x00 */ s16 grp;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 count;
} StaffTextGrp; // size 0x8: one line of sprite-letter text

extern s32 D_80110AA0_staff[]; // set 0 letter sprite files
extern s32 D_80110B0C_staff[]; // set 1 letter sprite files
extern s16 D_80111490_staff[27];
extern StaffTextGrp *D_801114C8_staff;
extern s16 D_801114D0_staff[28];
extern StaffTextGrp *D_80111508_staff;
extern u16 D_8011150C_staff;
extern u16 D_8011150E_staff;
void func_8005BF70_main(s16 winId, s32 alpha);
typedef struct StaffS16Vec {
    s16 x;
    s16 y;
    s16 z;
} StaffS16Vec;

typedef struct StaffScript {
    /* 0x00 */ f32 scale; // 0 ends the script
    /* 0x04 */ s32 file;
    /* 0x08 */ s32 file2; // optional attached model
    /* 0x0C */ StaffS16Vec unkC;
    /* 0x12 */ s16 type;
    /* 0x14 */ s16 param;
    /* 0x16 */ s16 anim; // 1-based index into D_80110674_staff
} StaffScript; // size 0x18

typedef struct StaffActor {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 model;
    /* 0x1E */ s16 model2;
    /* 0x20 */ s16 anim;
    /* 0x22 */ StaffS16Vec unk22;
    /* 0x28 */ s16 models[4];
    /* 0x30 */ s16 anim2;
    /* 0x32 */ s16 anim3;
    /* 0x34 */ s16 type;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 flags;
} StaffActor; // size 0x3C

typedef struct StaffAnimDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ char *name;
} StaffAnimDef;

extern StaffAnimDef D_80110674_staff[];
void func_80034048_main(s16, s16);
typedef struct StaffWork {
    /* 0x00 */ StaffActor *actors;
    /* 0x04 */ s16 state; // 1 ends the credits actors
    /* 0x06 */ char unk06[6];
} StaffWork; // size 0xC

extern StaffScript D_80110704_staff[];
StaffScript *func_80109D74_staff(StaffActor *actors, StaffScript *script);
void func_8010A848_staff(void);
typedef struct StaffMdl {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    /* 0x18 */ s16 model;
    /* 0x1A */ s16 model2;
    /* 0x1C */ s16 anim;
    /* 0x1E */ s16 model4; // < 0 when absent
} StaffMdl; // size 0x20: the file head's UnkStaff

typedef struct StaffFlyer {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 unk18; // angle
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 model;
    /* 0x2A */ s16 unk2A;
} StaffFlyer; // size 0x2C: the file head's UnkStaff_1 (its 0x18/0x1C are f32)

extern Vec D_80110FA0_staff[3];
u32 func_8010601C_staff(void);
typedef struct StaffLine {
    /* 0x00 */ Vec pos; // portrait model position
    /* 0x0C */ s16 x;
    /* 0x0E */ s16 y; // scrolls up one per frame
    /* 0x10 */ s16 line0; // set-0 text line (name)
    /* 0x12 */ s16 line1; // set-1 text line (title)
    /* 0x14 */ s16 esprite;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 model;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 type; // 0 free, 1 title, 2 sprite, 3 name, 4 name with portrait
} StaffLine; // size 0x20

typedef struct StaffCredit {
    /* 0x00 */ s8 type; // -1 ends this list
    /* 0x01 */ s8 delay;
    /* 0x02 */ u16 mes;
} StaffCredit;

extern s32 D_80110B80_staff[];
extern StaffCredit *D_80110F04_staff[]; // NULL-terminated
void func_8010992C_staff(Process *proc, s16 arg1);
void func_8010998C_staff(Process *proc, s16 *arg1, s16 *arg2, void *line);
void func_80109D08_staff(Process *proc, s16 arg1, void *line);
StaffScript *func_80109F34_staff(StaffActor *e, StaffScript *script);
void func_8010BA30_staff(s16 set, s16 idx, u32 mes, s16 x, s16 y);
// end story j2

#ifdef NON_MATCHING
// Register allocation: retail keeps attach in fp and spills sub; logic checked block by block.
StaffScript *func_80109F34_staff(StaffActor *e, StaffScript *script) {
    s32 attach;
    void *data;
    s32 i;
    s16 mdl;
    s16 m;
    s16 sub;

    e->flags = 0;
    switch (e->type) {
    case 7:
        for (i = 0; i < 4; i++) {
            func_8001ACDC_main(e->models[i]);
        }
        func_80033354_main(e->anim);
        func_80033354_main(e->anim2);
        break;
    case 4:
    case 8:
    case 10:
        func_8001ACDC_main(e->models[0]);
        break;
    case 12:
        func_80046558_main(e->model);
        break;
    }
    if (e->anim3 >= 0) {
        func_80033354_main(e->anim3);
    }
    if (e->model >= 0) {
        func_8001ACDC_main(e->model);
    }
    if (e->model2 >= 0) {
        func_8001ACDC_main(e->model2);
    }
    e->model2 = e->model = -1;
    HuPrcVSleep();
    if (script->scale == 0.0f) {
        return script;
    }
    e->type = script->type;
    attach = 0;
    data = DataRead(script->file);
    HuPrcVSleep();
    HuPrcVSleep();
    e->model = mdl = Hu3DModelCreate(data, 0x2AD);
    func_8001C814_main(mdl, -1, 2);
    Hu3DModelScaleSet(mdl, script->scale, script->scale, script->scale);
    e->unk22 = script->unkC;
    HuPrcVSleep();
    HuPrcVSleep();
    e->anim3 = -1;
    if (script->anim != 0) {
        i = script->anim - 1;
        attach = 1;
        data = DataRead(D_80110674_staff[i].file);
        HuPrcVSleep();
        HuPrcVSleep();
        e->anim3 = HmfAnimCreate(HmfModelData[mdl].hmf, data, 0, D_80110674_staff[i].name);
        HuMemMemoryFreePerm(data);
        HuPrcVSleep();
    }
    if (script->file2 != 0) {
        data = DataRead(script->file2);
        HuPrcVSleep();
        HuPrcVSleep();
        sub = Hu3DModelCreate(data, 0x1D);
        HuPrcVSleep();
        func_8001C5B4_main(mdl, sub);
        func_8001C814_main(mdl, -1, 2);
        e->model2 = sub;
    }
    switch (e->type) {
    case 1:
        e->unk36 = 0;
        e->rot.x = e->rot.y = e->rot.z = 0.0f;
        e->unk18 = 90.0f;
        Hu3DModelRotSet(mdl, 0.0f, 90.0f, 0.0f);
        break;
    case 2:
        e->unk36 = 0;
        e->unk38 = script->param;
        e->unk18 = 0.0f;
        e->rot.x = e->rot.y = e->rot.z = e->unk18;
        break;
    case 3:
        e->unk18 = 0.0f;
        e->unk36 = 30;
        e->rot.x = 0.0f;
        func_8001FA68_main(mdl);
        func_8001F9E4_main(mdl, 0xFF);
        break;
    case 4:
        e->unk36 = script->param;
        data = DataRead(0xA00C3);
        HuPrcVSleep();
        HuPrcVSleep();
        e->models[0] = m = Hu3DModelCreate(data, 0x2AD);
        Hu3DModelScaleSet(m, script->scale, script->scale, script->scale);
        func_8001C5B4_main(m, sub);
        func_8001C814_main(m, -1, 2);
        HuPrcVSleep();
        func_8001C514_main(m);
        HuPrcVSleep();
        break;
    case 5:
    case 11:
        e->unk18 = 0.0f;
        break;
    case 6:
        e->unk18 = e->rot.x = e->rot.y = e->rot.z = 0.0f;
        e->unk36 = e->unk38 = 0;
        break;
    case 7:
        data = DataRead(0xA008C);
        HuPrcVSleep();
        attach = 1;
        HuPrcVSleep();
        e->anim = HmfAnimCreate(HmfModelData[mdl].hmf, data, 0, "c201n_00_DEF");
        func_80034048_main(e->anim, 5);
        HuMemMemoryFreePerm(data);
        HuPrcVSleep();
        for (i = 0; i < 4; i++) {
            switch (i) {
            case 0:
                data = DataRead(script->file);
                HuPrcVSleep();
                HuPrcVSleep();
                m = Hu3DModelCreate(data, 0x2AD);
                HuPrcVSleep();
                data = DataRead(0xA008D);
                HuPrcVSleep();
                HuPrcVSleep();
                e->anim2 = HmfAnimCreate(HmfModelData[m].hmf, data, 0, "c201n_00_DEF");
                HuMemMemoryFreePerm(data);
                HuPrcVSleep();
                func_80034048_main(e->anim2, 8);
                func_8001C448_main(m);
                func_8001C514_main(m);
                break;
            case 1:
                data = DataRead(script->file);
                HuPrcVSleep();
                HuPrcVSleep();
                m = Hu3DModelCreate(data, 0x2AD);
                HuPrcVSleep();
                data = DataRead(0xA008D);
                HuPrcVSleep();
                HuPrcVSleep();
                e->anim3 = HmfAnimCreate(HmfModelData[m].hmf, data, 0, "c201n_00_DEF");
                HuMemMemoryFreePerm(data);
                HuPrcVSleep();
                func_8001C448_main(m);
                func_8001C514_main(m);
                break;
            case 2:
                m = Hu3DModelLink(e->models[1]);
                break;
            case 3:
                m = Hu3DModelLink(e->models[0]);
                break;
            }
            e->models[i] = m;
            func_8001C814_main(m, -1, 2);
            Hu3DModelScaleSet(m, script->scale, script->scale, script->scale);
            HuPrcVSleep();
        }
        HuPrcVSleep();
        HuPrcVSleep();
        break;
    case 8:
        e->models[0] = m = Hu3DModelLink(mdl);
        e->unk36 = script->param;
        func_8001C814_main(m, -1, 2);
        func_8001C6A8_main(m, D_800CCF58_main[HmfModelData[m].unk02].unk02 * 0.5f);
        Hu3DModelScaleSet(m, script->scale, script->scale, script->scale);
        Hu3DModelRotSet(mdl, -15.0f, 80.0f, 0.0f);
        Hu3DModelRotSet(m, -15.0f, -80.0f, 0.0f);
        break;
    case 10:
        e->models[0] = m = Hu3DModelLink(mdl);
        e->unk36 = script->param;
        func_8001C814_main(m, -1, 2);
        func_8001C6A8_main(m, D_800CCF58_main[HmfModelData[m].unk02].unk02 * 0.5f);
        Hu3DModelScaleSet(m, script->scale, script->scale, script->scale);
        Hu3DModelRotSet(mdl, 0.0f, -30.0f, 0.0f);
        Hu3DModelRotSet(m, 0.0f, 30.0f, 0.0f);
        break;
    case 12:
        func_800461B4_main(mdl);
        break;
    case 9:
        Hu3DModelRotSet(mdl, -30.0f, script->param, 0.0f);
        break;
    case 0:
    default:
        if (script->param != 0) {
            Hu3DModelRotSet(mdl, 0.0f, script->param, 0.0f);
        }
        break;
    }
    if (attach) {
        func_8001C448_main(mdl);
    }
    func_8001C514_main(mdl);
    e->flags = 1;
    HuPrcVSleep();
    return script + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109F34_staff);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010A848_staff);

void func_8010B1E0_staff(void) {
    StaffActor actors[3];
    StaffWork *w;
    Process *proc;
    StaffScript *script;
    StaffActor *a;
    s32 i;
    s16 cur;

    w = HuMemAllocTag(sizeof(StaffWork), 0x7918);
    memset(w, 0, sizeof(StaffWork));
    cur = 0;
    HuPrcCurrentGet()->user_data = w;
    proc = omAddPrcObj(func_8010A848_staff, 0x4000, 0x800, 0);
    proc->user_data = actors;
    w->actors = actors;
    script = func_80109D74_staff(actors, D_80110704_staff);
    while (cur >= 0) {
        if (cur != w->state) {
            switch (w->state) {
            default:
            case 0:
                cur = w->state;
                break;
            case 1:
                cur = -1;
                continue;
            }
        }
        for (a = actors, i = 0; i < 3; i++, a++) {
            if (a->flags != 0 && (a->flags & 4)) {
                script = func_80109F34_staff(a, script);
            }
        }
        HuPrcVSleep();
    }
    omDelPrcObj(proc);
    for (a = actors, i = 0; i < 3; i++, a++) {
        if (a->flags != 0) {
            a->flags = 0;
            switch (a->type) {
            case 7:
                for (i = 0; i < 4; i++) {
                    func_8001ACDC_main(a->models[i]);
                }
                func_80033354_main(a->anim);
                func_80033354_main(a->anim2);
                break;
            case 4:
            case 8:
            case 10:
                func_8001ACDC_main(a->models[0]);
                break;
            case 12:
                func_80046558_main(a->model);
                break;
            }
            if (a->anim3 >= 0) {
                func_80033354_main(a->anim3);
            }
            if (a->model >= 0) {
                func_8001ACDC_main(a->model);
            }
            if (a->model2 >= 0) {
                func_8001ACDC_main(a->model2);
            }
            a->model2 = a->model = -1;
        }
    }
    HuMemFree(w);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010B430_staff(s16 group, s16 member, s16 dx, s16 dy) {
    HuSprGrp *grp = HuSprGrpData[group];
    HuSprite *spr = grp->members[member];

    if ((dx != 0) | (dy != 0)) {
        grp->unk_0C = 1;
        spr->unk_48 = dx + spr->unk_48;
        spr->unk_4C = dy + spr->unk_4C;
    }
}

void func_8010B4B4_staff(s16 group, s16 member, s16 y) {
    f32 fy = y;
    HuSprGrp *grp = HuSprGrpData[group];
    HuSprite *spr = grp->members[member];

    if (spr->unk_4C != fy) {
        grp->unk_0C = 1;
        spr->unk_4C = fy;
    }
}

void func_8010B514_staff(s16 set, s16 count) {
    s16 *sprIds;
    s16 *id;
    s32 *files;
    s16 numSpr;
    s16 numMembers;
    s32 i;
    s32 j;
    StaffTextGrp *grps;
    StaffTextGrp *g;
    s16 grp;

    switch (set) {
    default:
    case 0:
        sprIds = D_80111490_staff;
        numMembers = 24;
        files = D_80110AA0_staff;
        numSpr = 27;
        break;
    case 1:
        numMembers = 28;
        sprIds = D_801114D0_staff;
        files = D_80110B0C_staff;
        numSpr = 28;
        break;
    }
    id = sprIds;
    for (i = 0; i < numSpr; i++) {
        *id++ = func_8000B838_main(*files++);
    }
    grps = HuMemAllocTag(count * sizeof(StaffTextGrp), 0x7918);
    g = grps;
    for (i = 0; i < count; i++, g++) {
        g->x = 160;
        g->y = 120;
        g->count = 0;
        g->grp = grp = HuSprGrpCreate(numMembers, 2);
        for (j = 0; j < numMembers; j++) {
            func_80055458_main(grp, j, 0x100);
            HuSprAttrReset(grp, j, 0xFFFF);
            HuSprAttrSet(grp, j, 0x9000);
            HuSprScaleSet(grp, j, 1.0f, 1.0f);
            func_800550F4_main(grp, j, 0);
            HuSprPriSet(grp, j, 400);
            func_80055420_main(grp, j, 0xFF, 0xFF, 0xFF);
            if (j != 0) {
                func_800554C4_main(grp, j, 0);
            } else {
                func_800554C4_main(grp, 0, -1);
            }
        }
    }
    switch (set) {
    default:
    case 0:
        D_801114C8_staff = grps;
        D_8011150C_staff = count;
        break;
    case 1:
        D_80111508_staff = grps;
        D_8011150E_staff = count;
        break;
    }
}

void func_8010B794_staff(s16 set) {
    StaffTextGrp *grps;
    s16 *sprIds;
    s16 count;
    s16 numSpr;
    StaffTextGrp *g;
    s32 i;

    switch (set) {
    default:
    case 0:
        grps = D_801114C8_staff;
        sprIds = D_80111490_staff;
        count = D_8011150C_staff;
        numSpr = 27;
        break;
    case 1:
        numSpr = 28;
        grps = D_80111508_staff;
        sprIds = D_801114D0_staff;
        count = D_8011150E_staff;
        break;
    }
    g = grps;
    if (grps != NULL) {
        for (i = 0; i < count; i++, g++) {
            HuSprGrpKill(g->grp);
        }
        HuMemFree(grps);
        for (i = 0; i < numSpr; i++, sprIds++) {
            HuSprKill(*sprIds);
        }
        switch (set) {
        default:
        case 0:
            D_801114C8_staff = NULL;
            break;
        case 1:
            D_80111508_staff = NULL;
            break;
        }
    }
}

void func_8010B8C0_staff(s16 set, s16 idx, s16 show) {
    StaffTextGrp *g;
    s16 n;
    s16 grp;
    s32 i;

    switch (set) {
    default:
    case 0:
        g = &D_801114C8_staff[idx];
        break;
    case 1:
        g = &D_80111508_staff[idx];
        break;
    }
    n = g->count;
    if (n != 0) {
        grp = g->grp;
        if (show != 0) {
            for (i = 0; i < n; i++) {
                HuSprAttrReset(grp, i, 0x8000);
            }
        } else {
            for (i = 0; i < n; i++) {
                HuSprAttrSet(grp, i, 0x8000);
            }
        }
    }
}

void func_8010B9BC_staff(s16 set, s16 idx, s16 x, s16 y) {
    StaffTextGrp *g;

    switch (set) {
    default:
    case 0:
        g = &D_801114C8_staff[idx];
        break;
    case 1:
        g = &D_80111508_staff[idx];
        break;
    }
    if (g->count != 0) {
        func_80054904_main(g->grp, 0, x, y);
    }
}

#ifdef NON_MATCHING
// Register allocation: retail keeps g in s8 and spills x, y and str; logic checked block by block.
void func_8010BA30_staff(s16 set, s16 idx, u32 mes, s16 x, s16 y) {
    s16 pos[24];
    StaffTextGrp *g;
    s16 *sprIds;
    s16 numMembers;
    s16 step;
    s16 width;
    s16 n;
    u8 c;
    s32 i;
    s16 ofs;
    u8 *str;
    u8 *buf;
    s16 grp;
    s16 extraI;

    switch (set) {
    default:
    case 0:
        g = &D_801114C8_staff[idx];
        sprIds = D_80111490_staff;
        numMembers = 24;
        extraI = -2;
        step = 10;
        break;
    case 1:
        g = &D_80111508_staff[idx];
        sprIds = D_801114D0_staff;
        numMembers = 28;
        extraI = 0;
        step = 10;
        break;
    }
    grp = g->grp;
    n = g->count;
    if (n != 0) {
        for (i = 0; i < n; i++) {
            HuSprAttrSet(grp, i, 0x8000);
        }
    }
    g->x = x;
    g->y = y;
    buf = NULL;
    if (mes > 0x80000000U) {
        str = (u8 *)mes;
    } else {
        str = buf = func_800364DC_main((void *)mes);
    }
    width = 0;
    for (n = 1; n < numMembers; str++) {
        c = *str;
        if (c == 0) {
            break;
        }
        if ((u32)(c - 'a') < 26) {
            c -= 0x20;
        }
        if ((c == 0x10) | (c == ' ')) {
            width += step;
        } else if (c == 0x1A) {
            width += step;
        } else if ((u8)(c - 'A') < 26) {
            c -= 'A';
            func_80055024_main(grp, n, sprIds[c], 0);
            if (n != 0) {
                func_800554C4_main(grp, n, 0);
            }
            pos[n] = width;
            width += step;
            if (c == 'I' - 'A') {
                width += extraI;
            }
            n++;
        } else if (c == '3') {
            func_80055024_main(grp, n, sprIds[26], 0);
            if (n != 0) {
                func_800554C4_main(grp, n, 0);
            }
            pos[n] = width;
            width += step;
            n++;
        } else if ((u8)(c - '[') < 2) {
            c -= 'A';
            func_80055024_main(grp, n, sprIds[c], 0);
            if (n != 0) {
                func_800554C4_main(grp, n, 0);
            }
            pos[n] = width;
            width += step;
            n++;
        }
    }
    if (width > step) {
        width -= step;
    }
    ofs = -(width >> 1);
    func_80054904_main(grp, 0, g->x, g->y);
    for (i = 1; i < n; i++) {
        func_80054904_main(grp, i, ofs + pos[i], 0);
        HuSprAttrReset(grp, i, 0x8000);
    }
    g->count = n;
    if (buf != NULL) {
        func_800365E8_main(buf);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BA30_staff);
#endif

void func_8010BE20_staff(s16 *wins, s16 count) {
    s32 i;
    s16 win;

    for (i = 0; i < count; i++) {
        *wins = win = func_8005A968_main(-120, -50, 240, 20, 0, 12);
        func_8005BCA4_main(win, 120, 10);
        func_8005BDFC_main(win, 0);
        func_8005BEE0_main(win, 0);
        func_8005C060_main(win, 2, 0xFF, 0, 0);
        func_8005C060_main(win, 4, 0, 0x90, 0);
        func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
        func_8005C060_main(win, 6, 0xFF, 0xAD, 0);
        func_8005C154_main(win, 0x40, 0x40, 0x40);
        func_8005FBF8_main(win, 0, 0, 0);
        func_8005C02C_main(win, 7);
        func_8005BF70_main(win, 0x100);
        func_8005FE90_main(win);
        wins++;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011133C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111348_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111354_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111360_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011136C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111378_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111384_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111390_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011139C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113A8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113B4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113C0_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113CC_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113D8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113E4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113F0_staff);

#ifdef NON_MATCHING
// Branch layout of the scroll switch and register choice differ; logic checked block by block.
void func_8010BF84_staff(void) {
    StaffLine lines[12];
    s16 models[16]; // only 3 used
    s16 spr[1];
    s16 slot[1];
    Process *proc;
    StaffWork *work;
    s16 *state;
    s16 mdlIdx;
    s16 nameIdx;
    StaffLine *l;
    s32 i;
    s16 base;
    s16 m;
    s16 cur;
    s16 titleIdx;
    s16 wait;
    StaffCredit *cred;
    s16 credIdx;
    s16 active;
    s16 done;
    s16 n;

    state = HuPrcCurrentGet()->user_data;
    proc = omAddPrcObj(func_8010B1E0_staff, 0x4000, 0x1000, 0);
    HuPrcVSleep();
    work = proc->user_data;
    for (l = lines, i = 0; i < 12; i++, l++) {
        l->type = 0;
        l->unk1C = l->model = l->esprite = l->line1 = l->line0 = l->unk18 = l->unk16 = -1;
    }
    base = -1;
    for (i = 0; i < 3; i++) {
        if (base < 0) {
            base = m = func_8000B108_main(0x160025, 0x2B9);
        } else {
            m = Hu3DModelLink(base);
        }
        models[i] = m;
        func_8001C258_main(m, 4, 4);
    }
    for (i = 0; i <= 0; i++) {
        spr[i] = func_8000B838_main(D_80110B80_staff[i]);
        slot[i] = InitEspriteSlot(spr[i], 0, 0);
        func_8000BB94_main(slot[i]);
    }
    mdlIdx = 0;
    nameIdx = 0;
    titleIdx = 0;
    cur = 0;
    do {
        if (cur != *state) {
            switch (*state) {
            case 0:
                break;
            case 1:
                wait = 1;
                cred = D_80110F04_staff[0];
                credIdx = 1;
                break;
            }
            cur = *state;
        }
        if (cur == 1) {
            if (credIdx >= 0 && --wait == 0) {
                if (cred->type == -1) {
                    cred = D_80110F04_staff[credIdx];
                    credIdx++;
                    if (cred == NULL) {
                        credIdx = -1;
                    }
                    wait += 127;
                } else {
                    for (l = lines, i = 0; i < 12; i++, l++) {
                        if (l->type == 0) {
                            break;
                        }
                    }
                    if (i < 12) {
                        l->x = 160;
                        l->y = 320;
                        l->pos.x = 0.0f;
                        l->pos.y = -480.0f;
                        l->pos.z = 380.0f;
                        l->type = cred->type;
                        switch (l->type) {
                        case 1:
                            func_8010BA30_staff(1, titleIdx, cred->mes, l->x, l->y);
                            l->line1 = titleIdx;
                            n = titleIdx + 1;
                            titleIdx = (n < 12) ? n : 0;
                            break;
                        case 4:
                            l->model = models[mdlIdx];
                            func_8001C258_main(l->model, 4, 0);
                            Hu3DModelPosSet(l->model, l->pos.x, l->pos.y, l->pos.z);
                            func_8010998C_staff(proc, &l->unk16, &l->unk18, l);
                            n = mdlIdx + 1;
                            mdlIdx = (n < 3) ? n : 0;
                            /* fallthrough */
                        case 3:
                            func_8010BA30_staff(0, nameIdx, cred->mes, l->x, l->y);
                            l->line0 = nameIdx;
                            n = nameIdx + 1;
                            nameIdx = (n < 6) ? n : 0;
                            wait += 22;
                            break;
                        case 2:
                            l->esprite = slot[cred->mes];
                            func_8000BB54_main(l->esprite);
                            break;
                        }
                        wait += cred->delay;
                        cred++;
                        if (l->type == 1 && cred->type >= 3) {
                            wait += 22;
                        }
                        wait += 30;
                    } else {
                        wait = 1;
                    }
                }
            }
            for (active = 0, l = lines, i = 0; i < 12; i++, l++) {
                if (l->type == 0) {
                    continue;
                }
                active++;
                l->y--;
                done = 0;
                if (l->type == 4) {
                    done = l->y < -63;
                } else if (l->y < -15) {
                    done++;
                }
                if (done) {
                    l->type = 0;
                    if (l->unk16 >= 0) {
                        func_8001C258_main(l->unk16, 4, 4);
                        func_8010992C_staff(proc, l->unk16);
                    }
                    l->unk18 = l->unk16 = -1;
                    if (l->line1 >= 0) {
                        func_8010B8C0_staff(1, l->line1, 0);
                        l->line1 = -1;
                    }
                    if (l->esprite >= 0) {
                        func_8000BB94_main(l->esprite);
                        l->esprite = -1;
                    }
                    if (l->line0 >= 0) {
                        func_8010B8C0_staff(0, l->line0, 0);
                        l->line0 = -1;
                    }
                    if (l->model >= 0) {
                        func_8001C258_main(l->model, 4, 4);
                        l->model = -1;
                    }
                    continue;
                }
                switch (l->type) {
                case 2:
                    func_8000BBD4_main(l->esprite, l->x, l->y);
                    break;
                case 1:
                    if (l->line1 >= 0) {
                        func_8010B9BC_staff(1, l->line1, l->x, l->y);
                    }
                    break;
                case 4:
                    l->pos.y = 288.0 - l->y * 2.4;
                    Hu3DModelPosSet(l->model, l->pos.x, l->pos.y, l->pos.z);
                    if (l->unk16 >= 0) {
                        func_80109D08_staff(proc, l->unk16, l);
                    }
                    /* fallthrough */
                case 3:
                    func_8010B9BC_staff(0, l->line0, l->x, l->y);
                    break;
                }
            }
            if ((active == 0) & (credIdx < 0)) {
                *state = -1;
            }
        }
        HuPrcVSleep();
    } while (cur >= 0);
    work->state = 1;
    for (i = 0; i < 3; i++) {
        func_8001ACDC_main(models[i]);
    }
    for (i = 0; i <= 0; i++) {
        func_8000C184_main(slot[i]);
        HuSprKill(spr[i]);
    }
    HuPrcVSleep();
    *state = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BF84_staff);
#endif

#ifdef NON_MATCHING
// masked 0; raw 2: retail copies the second parameter before the third.
void func_8010C680_staff(s16 *state, s32 *arg1, f32 *arg2, void *arg3) {
    StaffMdl *mdl = arg3;
    f32 *t = (f32 *)arg1;
    f32 *rotY = arg2;
    Vec pos;
    Vec *p;
    f32 d;

    pos = mdl->pos;
    p = &pos;
    switch (*state) {
    case 0:
        p->x += 6.266667f;
        if (p->x >= 260.0f) {
            (*state)++;
            *t = 0.0f;
        }
        break;
    case 1:
        *t += 12.0f;
        if (*t >= 180.0f) {
            *t = 180.0f;
            (*state)++;
        }
        d = cosdf(*t) * 6.266667f;
        p->x = d + p->x;
        d = 90.0f - *t;
        *rotY = d;
        break;
    case 2:
        p->x -= 6.266667f;
        if (p->x <= -680.0f) {
            (*state)++;
            *t = 0.0f;
        }
        break;
    case 3:
        *t += 12.0f;
        if (*t >= 180.0f) {
            *t = 180.0f;
            *state = 0;
        }
        d = cosdf(*t) * -6.266667f;
        p->x = d + p->x;
        d = *t + -90.0f;
        *rotY = d;
        break;
    }
    mdl->pos.x = p->x;
    Hu3DModelPosSet(mdl->model, p->x, p->y, p->z);
    Hu3DModelPosSet(mdl->model4, p->x, 0.0f, p->z);
    Hu3DModelRotSet(mdl->model, mdl->rot.x, *rotY - 8.0f, mdl->rot.z);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C680_staff);
#endif

void func_8010C8F4_staff(UnkStaff_1 *arg0) {
    Vec pos[3];
    StaffFlyer *flyers;
    StaffFlyer *f;
    Vec *p;
    s32 i;
    f32 a;
    f32 rot;
    f32 s;
    f32 c;

    f = (StaffFlyer *)arg0;
    flyers = f;
    for (p = pos, i = 0; i < 3; i++, f++, p++) {
        *p = f->pos;
        f->unk20 += 25.714285f;
        if (f->unk20 >= 180.0f) {
            f->unk20 -= 180.0f;
            a = (f32)(func_8010601C_staff() & 0x1F) - 15.0f;
            a += 20.0f;
            f->unk24 = a;
        }
        a = sindf(f->unk20) * f->unk24;
        p->y = a + p->y;
    }
    f = flyers;
    p = pos;
    switch (f->unk2A) {
    case 0:
        p->x += 6.266667f;
        if (p->x >= 260.0f) {
            f->unk2A++;
            f->unk18 = 0.0f;
        }
        break;
    case 1:
        f->unk18 += 12.0f;
        if (f->unk18 >= 180.0f) {
            f->unk18 = 180.0f;
            f->unk2A++;
        }
        s = cosdf(f->unk18) * 6.266667f;
        p->x = s + p->x;
        rot = f->unk18 + -90.0f;
        f->rot.y = rot;
        break;
    case 2:
        p->x -= 6.266667f;
        if (p->x <= -680.0f) {
            f->unk2A++;
            f->unk18 = 0.0f;
        }
        break;
    case 3:
        f->unk18 += 12.0f;
        if (f->unk18 >= 180.0f) {
            f->unk18 = 180.0f;
            f->unk2A = 0;
        }
        s = cosdf(f->unk18) * -6.266667f;
        p->x = s + p->x;
        rot = 90.0f - f->unk18;
        f->rot.y = rot;
        break;
    }
    f->pos.x = p->x;
    for (f = &flyers[1], p = &pos[1], i = 1; i < 3; i++, f++, p++) {
        a = f->unk18;
        switch (i) {
        case 1:
            a += 6.0f;
            rot = -90.0f;
            break;
        case 2:
            a -= 5.0f;
            rot = 90.0f;
            break;
        }
        if (a < 0.0f) {
            a += 360.0f;
        } else if (a >= 360.0f) {
            a -= 360.0f;
        }
        f->unk18 = a;
        s = sindf(a) * f->unk1C;
        c = cosdf(a) * f->unk1C;
        p->x = s + p->x;
        p->z = c + p->z;
        rot += a;
        if (rot < 0.0f) {
            rot += 360.0f;
        } else if (rot >= 360.0f) {
            rot -= 360.0f;
        }
        f->rot.y = rot;
    }
    for (f = flyers, p = pos, i = 0; i < 3; i++, f++, p++) {
        Hu3DModelPosSet(f->model, p->x, p->y, p->z);
        Hu3DModelRotSet(f->model, f->rot.x, f->rot.y, f->rot.z);
    }
}

void func_8010CD74_staff(UnkStaff_1 *arg0) {
    StaffFlyer *f;
    s16 base;
    s16 m;
    s32 i;

    base = -1;
    f = (StaffFlyer *)arg0;
    for (i = 0; i < 3; i++, f++) {
        if (base < 0) {
            base = m = Hu3DModelCreate(DataReadTemp(0xA015E), 0x2B9);
        } else {
            m = Hu3DModelLink(base);
        }
        f->model = m;
        func_8001C814_main(m, -1, 2);
        f->pos = D_80110FA0_staff[i];
        Hu3DModelPosSet(m, f->pos.x, f->pos.y, f->pos.z);
        f->rot.x = f->rot.y = f->rot.z = 0.0f;
        f->unk24 = 30.0f;
        switch (i) {
        case 0:
            Hu3DModelScaleSet(m, 0.8f, 0.8f, 0.8f);
            f->rot.y = -90.0f;
            Hu3DModelRotSet(m, 0.0f, -90.0f, 0.0f);
            f->unk1C = f->unk18 = f->unk20 = 0.0f;
            break;
        case 1:
            Hu3DModelScaleSet(m, 0.4f, 0.4f, 0.4f);
            f->unk20 = 60.0f;
            f->unk18 = 0.0f;
            f->unk1C = 50.0f;
            break;
        case 2:
            Hu3DModelScaleSet(m, 0.4f, 0.4f, 0.4f);
            f->unk20 = 120.0f;
            f->unk18 = 180.0f;
            f->unk1C = 80.0f;
            break;
        }
        f->unk2A = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CFD4_staff);

void func_8010D1E8_staff(void) {
    s16 sp10[3][2];
    UnkStaff sp20[8];
    UnkStaff_1 sp120[3];
    s16 sp1A8;
    s32 sp1AC;
    f32 sp1B0;
    s16 var_v0;
    s16 *temp_s2;
    s16 var_s0;
    s32 i;
    UnkStaff_1 *temp;
    UnkStaff *temp2;
    s16 *temp3;

    temp_s2 = HuPrcCurrentGet()->user_data;
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0x20);
    func_800E8180_name_81(1000.0f, 10000.0f);
    func_800E8110_name_81();
    D_80110538_staff = 1;
    D_80111540_staff.x = 350.0f;
    D_80111540_staff.y = 190.0f;
    D_80111540_staff.z = 3770.0f;
    D_80111534_staff.x = -1000.0f;
    D_80111534_staff.y = 130.0f;
    D_80111534_staff.z = 450.0f;
    D_80110534_staff = 40.0f;
    Hu3DCamSetPerspective(0, 40.0f, D_80111564_staff, D_80111560_staff);
    func_80105E6C_staff(D_80110FF4_staff, (SrModelSlot *)&sp10[0][0], 3);
    func_8010CFD4_staff(sp20);
    func_8010CD74_staff(sp120);
    *temp_s2 = 0;
    sp1A8 = 0;
    sp1B0 = 90.0f;
    sp1AC = 0;
    for (var_s0 = 0; var_s0 >= 0;) {
        if (var_s0 != *temp_s2) {
            if (*temp_s2 == -1) {
                var_s0 = -1;
            } else {
                var_s0 = *temp_s2;
                func_8010C8F4_staff(sp120);
                func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
                HuPrcVSleep();
            }
        } else {
            func_8010C8F4_staff(sp120);
            func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
            HuPrcVSleep();
        }
    }

    // TODO: fix typing of temp3 or sp10
    for (temp3 = sp10[0], i = 0; i < 3; i++, temp3 += 2) {
        func_8001ACDC_main(*temp3); //?
    }
    for (temp2 = sp20, i = 0; i < 8; i++, temp2++) {
        func_8001ACDC_main(temp2->unk_18);
        func_8001ACDC_main(temp2->unk_1A);
        func_80033354_main(temp2->unk_1C);
        if (temp2->unk_1E >= 0) {
            func_8001ACDC_main(temp2->unk_1E);
        }
    }

    for (temp = sp120, i = 0; i < 3; i++, temp++) {
        func_8001ACDC_main(temp->unk_28);
    }

    MBDBackKill();
    MBDBackClose();
    *temp_s2 = 0;
    while (1) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D450_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D580_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D998_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DE50_staff);

void func_8010DEDC_staff(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DEE4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DEF4_staff);

void func_8010DF04_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF0C_staff);

s16 func_8010DF24_staff(UnkStaff_2 *arg0) {
    return arg0->unk_04;
}

void func_8010DF2C_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF34_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F04C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F3E4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F4C4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F9D4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010FB28_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010FB88_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111430_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011143C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111448_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111454_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111460_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011146C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111478_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111484_staff);
