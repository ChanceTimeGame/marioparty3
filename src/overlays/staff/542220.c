#include "common.h"
#include "mallocblock.h"
#include "../ovl_81_name/ovl_81.h"

typedef struct UnkStaff {
    /* 0x00 */ Vec pos; /* story j3 */
    /* 0x0C */ Vec rot; /* story j3 */
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

void func_80105E6C_staff(void *, s16 *, s32);
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

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801059A0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105BD4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105CB4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105DB8_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105E6C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80105F48_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010601C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106044_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010609C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010615C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106720_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010674C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106C50_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106E20_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801073EC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107508_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107740_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107A9C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107B1C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107BA0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107DBC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107EB8_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801085F0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801088F4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010919C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801091CC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109264_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801095E4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010992C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010998C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109D08_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109D74_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109F34_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010A848_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B1E0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B430_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B4B4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B514_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B794_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B8C0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B9BC_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BA30_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BE20_staff);

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

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BF84_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C680_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C8F4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CD74_staff);

// story j3: the staff credits' firework, a copy of duelresult's (45A700.c).

/* One scattered polygon of the effect (13F90.c's HmfFxPart). */
typedef struct StFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale; /* alpha/size; <= 0 is a free slot */
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec dir; /* x: delay in frames for the shape's particles */
    /* 0x24 */ Vec vel; /* shape particles: target offset; z > 0 marks them */
} StFxPart; /* size 0x30 */

/* HmfModel.unkBC for a vertex-scatter model (13F90.c's HmfFxWork). */
typedef struct StFxWork {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags; /* 2 done, 4 finished */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 dist;
    /* 0x0C */ char unk0C[0xC];
    /* 0x18 */ void (*hook)(s16);
    /* 0x1C */ char unk1C[0x3C];
    /* 0x58 */ StFxPart* parts;
} StFxWork;

/* HmfData as the effect reads it (13F90.c's HmfFxData). */
typedef struct StFxData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 count; /* face group (particle) count */
} StFxData;

#define ST_FXWORK(model) ((StFxWork*) HmfModelData[model].unkBC)
#define ST_FXDATA(model) ((StFxData*) HmfModelData[model].hmf)

// Work area allocated by func_8010DE50/func_8010FB28 and stored at the process's user_data
// (see Process.user_data).
typedef struct StFwWork {
    /* 0x00 */ s32 unk_00; /* sprite data id of the shape the firework draws */
    /* 0x04 */ s16 unk_04; /* flags: 1 waiting, 2 stop */
    /* 0x06 */ s16 unk_06; /* shape scale (StFxWork.dist) */
    /* 0x08 */ s16 unk_08; /* flight frames */
    /* 0x0A */ s16 unk_0A; /* flight frames, set by func_8010AC94 */
    /* 0x0C */ Vec unk_0C; /* flight start */
    /* 0x18 */ Vec unk_18; /* flight end */
    /* 0x24 */ Vec unk_24; /* current start */
    /* 0x30 */ Vec unk_30; /* current end */
    /* 0x3C */ Vec unk_3C; /* arc amplitude */
    /* 0x48 */ f32 unk_48; /* arc phase, 0 or 180 */
} StFwWork; // sizeof 0x4C

void func_8010DF34_staff(void);
void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
void func_800138EC_main(s16 model, u16 mask, u16 flags);
s16 func_80013928_main(s16 model);
void func_80013954_main(s16 model, s16 value);

void func_8010F04C_staff(s16 model, s32 dataId);
StFxPart* func_8010F3E4_staff(s16 model, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, u8 r, u8 g, u8 b);
void func_8010F4C4_staff(s16 model);
void func_8010F9D4_staff(s16 model);
void func_8010FB88_staff(void);

/* Rows of the matrix turning a vector by angle a about the unit axis (x, y, z), applied to
   (vx, vy, vz) (the camera roll in camera.c's func_80013220-style code). */
#define ST_ROT_X(x, y, z, a, vx, vy, vz)                                                         \
    ((vx) * ((x) * (x) + (1.0f - (x) * (x)) * cosdf(a)) +                                       \
     (vy) * ((x) * (y) * (1.0f - cosdf(a)) - (z) * sindf(a)) +                                  \
     (vz) * ((x) * (z) * (1.0f - cosdf(a)) + (y) * sindf(a)))
#define ST_ROT_Y(x, y, z, a, vx, vy, vz)                                                         \
    ((vx) * ((x) * (y) * (1.0f - cosdf(a)) + (z) * sindf(a)) +                                  \
     (vy) * ((y) * (y) + (1.0f - (y) * (y)) * cosdf(a)) +                                       \
     (vz) * ((y) * (z) * (1.0f - cosdf(a)) - (x) * sindf(a)))
#define ST_ROT_Z(x, y, z, a, vx, vy, vz)                                                         \
    ((vx) * ((x) * (z) * (1.0f - cosdf(a)) - (y) * sindf(a)) +                                  \
     (vy) * ((y) * (z) * (1.0f - cosdf(a)) + (x) * sindf(a)) +                                  \
     (vz) * ((z) * (z) + (1.0f - (z) * (z)) * cosdf(a)))

/* Spark colours (r, g, b, pad); defined in this unit's .data. */
extern u8 D_801111E0_staff[4][4];

/* story j3: one cast member of the credits' stage (func_8010CFD4). */
typedef struct StaffActorDef {
    /* 0x00 */ s32 model;    /* data id */
    /* 0x04 */ s32 link;     /* data id of the model linked to it */
    /* 0x08 */ s32 anim;     /* data id of its animation */
    /* 0x0C */ char* animName;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
} StaffActorDef; /* size 0x28 */

extern StaffActorDef D_80111094_staff[8];

/* story j3: the unit's .data types (definitions at the end of the file). */
typedef struct StaffCamKey {
    /* 0x00 */ Vec rot;    /* CRot */
    /* 0x0C */ Vec center; /* Center */
    /* 0x18 */ f32 zoom;   /* CZoom */
    /* 0x1C */ f32 fov;
    /* 0x20 */ s32 unk20[3]; /* not read by func_8010609C */
} StaffCamKey;

typedef struct StaffAnimDef {
    /* 0x00 */ s32 anim; /* data id */
    /* 0x04 */ char* name;
} StaffAnimDef;

/* One cast member of a credits scene (func_80109D74 reads three per scene). */
typedef struct StaffCastEntry {
    /* 0x00 */ f32 scale;
    /* 0x04 */ s32 model; /* data id */
    /* 0x08 */ s32 link;  /* data id, 0 for none */
    /* 0x0C */ s16 unk0C[3];
    /* 0x12 */ s16 unk12; /* -1 ends the table */
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 anim; /* 1-based index into D_80110674, 0 for none */
} StaffCastEntry; /* size 0x18 */

/* One command of a credits page (func_8010BF84): type -1 ends the page. */
typedef struct StaffCreditLine {
    /* 0x00 */ s8 type;
    /* 0x01 */ u8 arg;
    /* 0x02 */ u16 mes; /* message id */
} StaffCreditLine;

/* A stage model (func_80105E6C/func_80105DB8). */
typedef struct StaffModelDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ s32 attr;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
} StaffModelDef; /* size 0x28 */

extern StaffModelDef D_80110FF4_staff[4];

/* Animation names in .rodata (INCLUDE_RODATA). */
extern char D_8011133C_staff[], D_80111348_staff[], D_80111354_staff[], D_80111360_staff[], D_8011136C_staff[];
extern char D_80111378_staff[], D_80111384_staff[], D_80111390_staff[], D_8011139C_staff[], D_801113A8_staff[];
extern char D_801113B4_staff[], D_801113C0_staff[], D_801113CC_staff[], D_801113D8_staff[], D_801113E4_staff[];
extern char D_801113F0_staff[], D_80111430_staff[], D_8011143C_staff[], D_80111448_staff[], D_80111454_staff[];
extern char D_80111460_staff[], D_8011146C_staff[], D_80111478_staff[], D_80111484_staff[];
extern s16 D_80111510_staff; /* controller to rumble */
s32 func_8010601C_staff(void);
void func_8010D450_staff(s16 model, Vec* pos);
void RepeatVibrator(s16 contId, s16 onTime, s16 offTime, s16 duration);
void func_8010D580_staff(s16 model, s16 shadow, Vec* start);
s16 func_8000B13C_main(s32 file);
void func_8000BC48_main(u16 arg0, u16 arg1);
/* story j3: func_8010D998's locals, one frame object (retail indexes the sprite ids from it). */
typedef struct StaffDieScene {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk0C[0x14]; /* unused */
    /* 0x20 */ s16 sprIds[3];
} StaffDieScene;

extern Vec D_80110FDC_staff;       /* die drop start */
extern s32 D_80110FE8_staff[3];    /* sprite data ids */

// story j3: NON_MATCHING, masked 0, raw 7: i and ring swap s4/s5 (register allocation). Logic checked.
#ifdef NON_MATCHING
/* Creates the eight cast members of D_80111094 into actor[8]: model, animation, linked model, and
   for all but the first a shadow (one model, linked for the rest) at its feet. */
void func_8010CFD4_staff(UnkStaff* actors) {
    s32 i;
    s16 ring;
    StaffActorDef* def;
    UnkStaff* actor;
    s16 model;
    s16 link;
    s16 shadow;
    void* anim;

    def = D_80111094_staff;
    actor = actors;
    ring = -1;
    for (i = 0; i < 8; i++, actor++, def++) {
        model = Hu3DModelCreate(DataReadTemp(def->model), 0x2A9);
        actor->unk_18 = model;
        anim = DataReadTemp(def->anim);
        actor->unk_1C = HmfAnimCreate(HmfModelData[model].hmf, anim, 0, def->animName);
        HuMemMemoryFreePerm(anim);
        func_8001C448_main(model);
        func_8001C514_main(model);
        link = Hu3DModelCreate(DataReadTemp(def->link), 0x1D);
        actor->unk_1A = link;
        func_8001C5B4_main(model, link);
        func_8001C814_main(model, -1, 2);
        Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
        actor->pos = def->pos;
        Hu3DModelPosSet(model, actor->pos.x, actor->pos.y, actor->pos.z);
        actor->rot = def->rot;
        Hu3DModelRotSet(model, def->rot.x, def->rot.y, def->rot.z);
        actor->unk_1E = -1;
        if (i != 0) {
            if (ring < 0) {
                shadow = ring = Hu3DModelCreate(DataReadTemp(9), 0x299);
            } else {
                shadow = Hu3DModelLink(ring);
            }
            actor->unk_1E = shadow;
            Hu3DModelPosSet(shadow, actor->pos.x, 0.0f, actor->pos.z);
            Hu3DModelScaleSet(shadow, 1.2f, 1.2f, 1.2f);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CFD4_staff);
#endif

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
    func_80105E6C_staff(D_80110FF4_staff, &sp10[0][0], 3);
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

// story j3: NON_MATCHING, masked 0, raw 11: FPU registers of the two double products. Logic checked.
#ifdef NON_MATCHING
/* Places shadow model under an actor at pos: offset by its height pos->y, shrinking with it, and
   hidden from 80 units up. */
void func_8010D450_staff(s16 model, Vec* pos) {
    f32 height;
    f32 scale;
    f32 dx;
    f32 dz;

    height = pos->y;
    scale = 400.0f - height;
    if (scale < 0.0f) {
        scale = 0.0f;
    }
    scale *= 0.0015f;
    Hu3DModelScaleSet(model, scale, scale, scale);
    dx = height * (f64) 0.2f;
    dz = height * (f64) 0.3464f;
    Hu3DModelPosSet(model, dx + pos->x, 0.0f, dz + pos->z);
    if (height >= 80.0f) {
        func_8001C258_main(model, 4, 4);
    } else {
        func_8001C258_main(model, 4, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D450_staff);
#endif

// story j3: NON_MATCHING, masked 0, raw 23: the two int temporaries swap s0/s1. Logic checked.
#ifdef NON_MATCHING
/* Drops actor model from pos as a tumbling die: it rolls 10 degrees a frame (about x, or about y
   tipped -90 on z, by the low bits of func_8010601C), bounces twice with a rumble, rolls on to the
   next quarter turn, then wobbles to rest. shadow follows it (func_8010D450). */
void func_8010D580_staff(s16 model, s16 shadow, Vec* start) {
    Vec pos;
    f32 rx;
    f32 ry;
    f32 rz;
    f32* roll;
    f32 angle;
    f32 vel;
    f32 rem;
    s32 face;
    s32 n;
    s32 i;

    rz = 0.0f;
    ry = 0.0f;
    rx = 0.0f;
    face = func_8010601C_staff();
    n = face & 0xF;
    if (n >= 10) {
        rz = -90.0f;
        roll = &ry;
    } else {
        roll = &rx;
    }
    n = (face >> 4) & 3;
    n *= 90;
    angle = n;
    vel = 0.0f;
    n = 0;
    pos = *start;
    do {
        angle -= 10.0f;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        vel += 2.0f;
        pos.y -= vel;
        if (pos.y <= 0.0f) {
            pos.y = 0.0f;
            vel = vel * -0.5;
            RepeatVibrator(D_80111510_staff, 5, 0, 5);
            n++;
        }
        pos.z -= 8.0f;
        Hu3DModelPosSet(model, pos.x, pos.y + 22.0f, pos.z);
        *roll = angle;
        Hu3DModelRotSet(model, rx, ry, rz);
        func_8010D450_staff(shadow, &pos);
        HuPrcVSleep();
    } while (n < 2);
    n = angle;
    rem = n % 90;
    if (rem >= 10.0f) {
        i = (s32) rem / 10;
        vel = pos.y / i;
        for (; i != 0; i--) {
            angle -= 10.0f;
            pos.y -= vel;
            pos.z -= 8.0f;
            Hu3DModelPosSet(model, pos.x, pos.y + 22.0f, pos.z);
            *roll = angle;
            Hu3DModelRotSet(model, rx, ry, rz);
            func_8010D450_staff(shadow, &pos);
            HuPrcVSleep();
        }
    }
    pos.y = 0.0f;
    Hu3DModelPosSet(model, pos.x, 22.0f, pos.z);
    *roll -= 8.0f;
    Hu3DModelRotSet(model, rx, ry, rz);
    HuPrcVSleep();
    *roll += 12.0f;
    Hu3DModelRotSet(model, rx, ry, rz);
    HuPrcVSleep();
    *roll -= 4.0f;
    Hu3DModelRotSet(model, rx, ry, rz);
    HuPrcVSleep();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D580_staff);
#endif

// story j3: NON_MATCHING, masked 12 (356 vs 357): retail keeps sp+0x10 in a register to index the sprite
// ids (one addiu more); the rest is register allocation. Logic checked.
#ifdef NON_MATCHING
/* Process of the credits' closing die scene: a backdrop sprite, the die model with its link and
   shadow, and three sprites below. Each time *user_data becomes 1 the die drops in
   (func_8010D580), the sprites fade in, and *user_data returns to 0. Never returns. */
void func_8010D998_staff(void) {
    StaffDieScene scene;
    s16* state;
    u16 backdrop;
    s16 link;
    s16 model;
    s16 shadow;
    s16 grp;
    s16 cur;
    s16 x;
    s16 alpha;
    s32 step;
    s32 i;

    state = HuPrcCurrentGet()->user_data;
    HmfLightDirSet(1, -21.0f, 235.0f, 181.0f);
    backdrop = InitEspriteSlot(func_8000B838_main(0x160024), 0, 0);
    func_8000BC48_main(backdrop, 0x4000);
    func_8000BBD4_main(backdrop, 160, 120);
    func_8000BCC8_main(backdrop, 0xFFF0);
    D_80110538_staff = 1;
    D_80111540_staff.x = -300.578f;
    D_80111540_staff.y = 542.5f;
    D_80111540_staff.z = 595.0f;
    D_80111534_staff.x = 10.3905f;
    D_80111534_staff.y = 0.0f;
    D_80111534_staff.z = 48.0235f;
    D_80110534_staff = 32.0f;
    Hu3DCamSetPerspective(0, 32.0f, D_80111564_staff, D_80111560_staff);
    link = func_8000B13C_main(0xA007D);
    model = func_8000B108_main(0xA0075, 0x2A9);
    func_8001C514_main(model);
    Hu3DModelScaleSet(model, 0.6f, 0.6f, 0.6f);
    HuPrcVSleep();
    func_8001C5B4_main(model, link);
    func_8001C814_main(model, 2, 2);
    shadow = func_8000B108_main(9, 0x299);
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(shadow, 4, 0);
    scene.pos = D_80110FDC_staff;
    Hu3DModelPosSet(model, scene.pos.x, scene.pos.y + 22.0f, scene.pos.z);
    func_8010D450_staff(shadow, &scene.pos);
    for (i = 0; i < 3; i++) {
        scene.sprIds[i] = func_8000B838_main(D_80110FE8_staff[i]);
    }
    grp = HuSprGrpCreate(3, 0);
    for (x = 268, i = 0; i < 3; i++, x += 12) {
        func_80055458_main(grp, i, 0);
        HuSprAttrReset(grp, i, 0xFFFF);
        HuSprAttrSet(grp, i, 0x9000);
        HuSprScaleSet(grp, i, 1.0f, 1.0f);
        func_80055024_main(grp, i, scene.sprIds[i], 0);
        func_800550F4_main(grp, i, 0);
        HuSprPriSet(grp, i, 400);
        func_80054904_main(grp, i, x, 214);
    }
    *state = 0;
    cur = 0;
    while (TRUE) {
        if (cur != *state) {
            if (*state == 1) {
                func_8001C258_main(model, 4, 0);
                func_8001C258_main(shadow, 4, 0);
            }
            cur = *state;
        }
        if (cur == 1) {
            func_8010D580_staff(model, shadow, &scene.pos);
            for (i = 0; i < 3; i++) {
                HuSprAttrReset(grp, i, 0x8000);
                func_80055458_main(grp, i, 0);
            }
            alpha = 0;
            step = 2;
            do {
                alpha += step;
                if (alpha >= 256) {
                    alpha = 256;
                    step = 0;
                }
                for (i = 0; i < 3; i++) {
                    func_80055458_main(grp, i, alpha);
                }
                HuPrcVSleep();
            } while (step != 0);
            *state = 0;
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D998_staff);
#endif

StFwWork* func_8010DE50_staff(s32 arg0) {
    Process* process;
    StFwWork* work;

    process = omAddPrcObj(func_8010DF34_staff, 0x3F00, 0x2000, 0);
    work = HuMemAllocTag(sizeof(StFwWork), 0x7918);
    process->user_data = work;
    work->unk_06 = 60;
    work->unk_0A = 60;
    work->unk_0C.x = 0.0f;
    work->unk_0C.y = 500.0f;
    work->unk_0C.z = 0.0f;
    work->unk_18.x = 0.0f;
    work->unk_18.y = 0.0f;
    work->unk_18.z = 0.0f;
    work->unk_00 = arg0;
    work->unk_04 = 0;
    return work;
}

void func_8010DEDC_staff(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

void func_8010DEE4_staff(StFwWork* arg0, f32 x, f32 y, f32 z) {
    arg0->unk_0C.x = x;
    arg0->unk_0C.y = y;
    arg0->unk_0C.z = z;
}

void func_8010DEF4_staff(StFwWork* arg0, f32 x, f32 y, f32 z) {
    arg0->unk_18.x = x;
    arg0->unk_18.y = y;
    arg0->unk_18.z = z;
}

void func_8010DF04_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

void func_8010DF0C_staff(StFwWork* arg0, s32 mask, s32 value) {
    arg0->unk_04 = value | (arg0->unk_04 & ~mask);
}

s16 func_8010DF24_staff(UnkStaff_2 *arg0) {
    return arg0->unk_04;
}

void func_8010DF2C_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

// story j3: NON_MATCHING, masked 380 (1245 vs 1191), duelresult's func_8010ACC4 with a different
// wait and an exit: retail computes the spark arguments in a different order and keeps work in s4
// (spilled here). Call sequence and flow match staff's asm; logic checked.
#ifdef NON_MATCHING
/* The firework: a rocket flies from work->unk_18 to work->unk_0C along a wobbling arc, trailing
   sparks, then bursts into the shape of sprite data work->unk_00. After each burst it sets
   work->unk_04 bit 0 (unless bit 1 is set) and waits until the bit is cleared; bit 2 kills both
   models, frees work and ends the process. */
void func_8010DF34_staff(void) {
    Vec pos;
    Vec prev;
    s16 head;
    s16 t;
    s16 spin;
    StFxWork* fx;
    s16 model;
    StFwWork* work;
    HmfData* hmf;
    HmfModelData_Unk64_Unk60_Struct* obj;
    HmfModelData_Unk64_Unk60_Unk54_Struct* face;
    s16 i;
    s16 j;
    s16 count;
    f32 roll;
    f32 r;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 sc;
    f32 ease;
    f32 wave;

    roll = 0.0f;
    work = HuPrcCurrentGet()->user_data;
    spin = 0;
    model = func_8000B108_main(0xB0034, 0x2A8);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    hmf = HmfModelData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        obj = &hmf->unk60[j];
        count = obj->unk22;
        face = obj->unk54;
        for (i = 0; i < count; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_8010F4C4_staff);
    func_800138EC_main(model, 8, 8);
    fx = ST_FXWORK(model);
    func_8001C258_main(model, 4, 4);
    head = func_8000B108_main(0xB0035, 0x2B9);
    func_8001C258_main(head, 4, 4);
    Hu3DModelScaleSet(head, 2.0f, 2.0f, 2.0f);
    func_8001C92C_main(head, 2.0f);
    while (!(work->unk_04 & 4)) {
        if (work->unk_04 & 1) {
            HuPrcVSleep();
            continue;
        }
        work->unk_04 &= ~1;
        work->unk_30 = work->unk_18;
        work->unk_24 = work->unk_0C;
        work->unk_08 = work->unk_0A;
        r = rand8() * 2 + 400;
        work->unk_3C.x = r - r / 2.0f;
        r = rand8() * 2 + 200;
        work->unk_3C.y = r - r / 2.0f;
        r = rand8() * 2 + 200;
        work->unk_3C.z = r - r / 2.0f;
        work->unk_48 = (rand8() & 1) ? 180.0f : 0.0f;
        fx->dist = work->unk_06;
        prev = pos = work->unk_30;
        HuAudFXPlay(0x16F);
        func_8001C258_main(model, 4, 0);
        func_80013954_main(model, 0);
        fx->hook = func_8010F9D4_staff;
        func_800138EC_main(model, 2, 0);
        for (t = 0; t <= work->unk_08; t++) {
            HuPrcVSleep();
            prev = pos;
            dx = work->unk_24.x - work->unk_30.x;
            dy = work->unk_24.y - work->unk_30.y;
            dz = work->unk_24.z - work->unk_30.z;
            ease = sindf(90.0f / work->unk_08 * t);
            wave = sindf(180.0f / work->unk_08 * t + work->unk_48);
            pos.x = ease * dx + work->unk_30.x + wave * work->unk_3C.x;
            pos.y = ease * dy + work->unk_30.y + wave * work->unk_3C.y;
            pos.z = ease * dz + work->unk_30.z + wave * work->unk_3C.z;
            spin += 5;
            if (spin > 360) {
                spin -= 360;
            }
            roll += 20.0f;
            if (roll > 360.0f) {
                roll -= 360.0f;
            }
            dx = prev.x - pos.x;
            dy = prev.y - pos.y;
            dz = prev.z - pos.z;
            len = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (len != 0.0f) {
                dx /= len;
                dy /= len;
                dz /= len;
                for (i = 0; i < 2; i++) {
                    rx = dx * (((s32) (rand8() * 15) >> 7) * 0.01f + 1.0f);
                    ry = dy * (((s32) (rand8() * 15) >> 7) * 0.01f + 1.0f);
                    rz = dz * (((s32) (rand8() * 15) >> 7) * 0.01f + 1.0f);
                    sc = len * ((s32) ((u32) (rand8() * 25) >> 7) * 0.01f);
                    rx *= sc;
                    ry *= sc;
                    rz *= sc;
                    func_8010F3E4_staff(model, rx + pos.x, ry + pos.y, rz + pos.z, rx, ry, rz, 0xFF, 0xFF, 0xC0);
                }
                func_8010F3E4_staff(model, pos.x, pos.y, pos.z,
                                         (dx * 0.5f + ST_ROT_X(dx, dy, dz, roll, 0.0f, 1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         (dy * 0.5f + ST_ROT_Y(dx, dy, dz, roll, 0.0f, 1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         (dz * 0.5f + ST_ROT_Z(dx, dy, dz, roll, 0.0f, 1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         0xFF, 0x20, 0x20);
                func_8010F3E4_staff(model, pos.x, pos.y, pos.z,
                                         (dx * 0.5f + ST_ROT_X(dx, dy, dz, roll, 0.0f, -1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         (dy * 0.5f + ST_ROT_Y(dx, dy, dz, roll, 0.0f, -1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         (dz * 0.5f + ST_ROT_Z(dx, dy, dz, roll, 0.0f, -1.0f, 0.0f) * 0.5f) * len / 2.0f,
                                         0xFF, 0x40, 0x00);
            }
        }
        HuPrcSleep(15);
        func_8001C258_main(model, 4, 4);
        func_8001C6A8_main(head, 0.0f);
        func_8001C258_main(head, 4, 0);
        Hu3DModelPosSet(head, pos.x, pos.y, pos.z);
        HuPrcVSleep();
        HuAudFXPlay(0x170);
        func_8010F04C_staff(model, work->unk_00);
        fx->hook = func_8010F4C4_staff;
        func_80013954_main(model, 0);
        func_8001C258_main(model, 4, 0);
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        func_800138EC_main(model, 2, 0);
        while (!(func_80013928_main(model) & 2)) {
            HuPrcVSleep();
        }
        func_8001C258_main(head, 4, 4);
        func_8001C258_main(model, 4, 4);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        if (!(work->unk_04 & 2)) {
            work->unk_04 |= 1;
        }
        HuPrcVSleep();
    }
    func_8001ACDC_main(model);
    func_8001ACDC_main(head);
    HuMemFree(work);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF34_staff);
#endif

// story j3 (from duelresult): masked 3: retail stores scale in rand8's delay slot with 3.0f still hoisted; only
// the source order that hoists it (scale before vel.z) fills the slot with vel.z. Logic checked.
#ifdef NON_MATCHING
/* Lays model's particles out on the white (0xFFFF) texels of sprite data dataId: each one's target
   offset (vel) is its texel's position from the centre, 12 units per texel; spare particles are
   cleared. */
void func_8010F04C_staff(s16 model, s32 dataId) {
    s16 sprId;
    s16 grp;
    s16 total;
    StFxWork* fx;
    HuSprite* spr;
    StFxPart* part;
    u16* pix;
    s16 w;
    s16 h;
    s16 x;
    s16 y;
    s16 i;
    s16 n;
    s16 white;

    sprId = func_8000B838_main(dataId);
    grp = HuSprGrpCreate(1, 0);
    func_80055024_main(grp, 0, sprId, 0);
    spr = HuSprGet(grp, 0);
    pix = spr->unk_84->unk00->unk00;
    w = spr->unk_84->unk00->unk04;
    h = spr->unk_84->unk00->unk06;
    white = 0;
    for (i = 0; i < w * h; i++) {
        if (*pix++ == 0xFFFF) {
            white++;
        }
    }
    pix = spr->unk_84->unk00->unk00;
    fx = ST_FXWORK(model);
    total = ST_FXDATA(model)->count;
    part = fx->parts;
    y = 0;
    n = 0;
    for (; y < h; y++) {
        for (x = 0; x < w; x++) {
            if (*pix++ == 0xFFFF && n < total) {
                part = &fx->parts[n];
                part->dir.x = rand8() & 0xF;
                part->vel.x = (x - w / 2) * 12;
                part->vel.y = (h / 2 - y) * 12;
                part->scale = 3.0f;
                part->vel.z = 1.0f;
                part->speed = (s32) ((u32) (rand8() * 5) >> 7) * 0.1f + 3.0f;
                n++;
                part++;
            }
        }
    }
    for (i = 0; i < total - n; i++, part++) {
        part->scale = part->vel.z = part->pos.x = part->pos.y = part->pos.z = 0.0f;
    }
    HuSprGrpKill(grp);
    HuSprKill(sprId);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F04C_staff);
#endif

/* Starts a particle at pos with velocity vel and colour (r, g, b) in the first free slot of model's
   effect; returns the slot (one past the last if none is free). */
StFxPart* func_8010F3E4_staff(s16 model, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, u8 r, u8 g, u8 b) {
    StFxPart* part;
    s16 i;
    s16 count;

    count = ST_FXDATA(model)->count;
    part = ST_FXWORK(model)->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->scale <= 0.0f) {
            part->pos.x = x;
            part->pos.y = y;
            part->pos.z = z;
            part->vel.x = vx;
            part->vel.y = vy;
            part->vel.z = vz;
            part->color[0] = r;
            part->color[1] = g;
            part->color[2] = b;
            part->scale = 2.0f;
            break;
        }
    }
    return part;
}

/* Effect hook of the burst: the particles fly out to the shape (vel), twinkle, then fall. */
void func_8010F4C4_staff(s16 model) {
    StFxData* data;
    StFxWork* fx;
    StFxPart* part;
    StFxPart* src;
    StFxPart* dst;
    s16 count;
    s16 i;
    s16 j;
    s16 n;
    f32 t;
    u8 r;
    u8 g;
    u8 b;

    data = ST_FXDATA(model);
    fx = ST_FXWORK(model);
    count = data->count;
    if (fx->frame == 0) {
        fx->flags &= ~4;
        part = fx->parts;
        for (i = 0; i < count; i++, part++) {
            if (part->vel.z > 0.0f) {
                part->scale = 1.0f;
            }
        }
    }
    part = fx->parts;
    r = rand8() | 0x80;
    g = rand8() | 0x80;
    b = rand8() | 0x80;
    if (fx->frame <= fx->dist) {
        if (fx->frame > 20) {
            for (j = 0; j < 2; j++) {
                src = &fx->parts[(rand8() * count) >> 8];
                if (src->vel.z > 0.0f) {
                    dst = &fx->parts[(rand8() * count) >> 8];
                    if (dst->vel.z <= 0.0f) {
                        dst->pos.x = src->pos.x;
                        dst->pos.y = src->pos.y;
                        dst->pos.z = src->pos.z;
                        dst->scale = 1.0f;
                    }
                }
            }
        }
        for (i = 0; i < count; i++, part++) {
            if (part->scale > 0.0f) {
                part->color[0] = r;
                part->color[1] = g;
                part->color[2] = b;
                if (part->vel.z > 0.0f) {
                    t = fx->frame * part->speed;
                    if (t > 90.0f) {
                        t = 90.0f;
                    }
                    part->pos.x = sindf(t) * part->vel.x;
                    part->pos.y = sindf(t) * part->vel.y;
                    part->pos.z = 0.0f;
                    part->scale = ((fx->frame + i) & 1) * 0.5f + 1.0f;
                } else {
                    part->pos.y -= 10.0f;
                    part->scale -= 0.04f;
                }
            } else {
                part->scale = 0.0f;
            }
        }
    } else {
        for (i = 0, n = 0; i < count; i++, part++) {
            if (part->scale > 0.0f) {
                part->color[0] = r;
                part->color[1] = g;
                part->color[2] = b;
                if (part->vel.z > 0.0f) {
                    if (part->dir.x <= 0.0f) {
                        part->pos.y -= part->speed * 5.0f;
                        part->scale -= 0.02f;
                        if (part->scale < 0.0f) {
                            part->scale = 0.0f;
                        }
                    } else {
                        part->dir.x -= 1.0f;
                        part->scale = ((fx->frame + i) & 1) * 0.5f + 1.0f;
                    }
                } else {
                    part->pos.y -= 10.0f;
                    part->scale -= 0.04f;
                }
            } else {
                part->scale = 0.0f;
                n++;
            }
        }
        if (n >= i) {
            fx->flags |= 2;
            return;
        }
    }
    fx->frame++;
}

/* Effect hook of the rising rocket: the trail particles move, sink and fade. */
void func_8010F9D4_staff(s16 model) {
    StFxData* data;
    StFxWork* fx;
    StFxPart* part;
    s16 count;
    s16 i;

    data = ST_FXDATA(model);
    fx = ST_FXWORK(model);
    count = data->count;
    if (fx->frame == 0) {
        fx->flags &= ~4;
        part = fx->parts;
        for (i = 0; i < count; i++, part++) {
            part->scale = part->pos.x = part->pos.y = part->pos.z = 0.0f;
        }
        fx->frame++;
    }
    part = fx->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->scale > 0.0f) {
            part->pos.x += part->vel.x;
            part->pos.y += part->vel.y;
            part->pos.z += part->vel.z;
            part->pos.y -= 5.0f;
            part->scale -= 0.05f;
        } else {
            part->scale = 0.0f;
        }
    }
}

StFwWork* func_8010FB28_staff(void) {
    Process* process;
    StFwWork* work;

    process = omAddPrcObj(func_8010FB88_staff, 0x3F00, 0x2000, 0);
    work = HuMemAllocTag(sizeof(StFwWork), 0x7918);
    process->user_data = work;
    work->unk_18.x = 0.0f;
    work->unk_18.y = 100.0f;
    work->unk_18.z = 0.0f;
    return work;
}

// story j3 (from duelresult): NON_MATCHING, masked 17 (670 vs 669): four extra nops after calls, the colour index
// (retail re-masks it with 0xFF and addresses splat's split labels D_8010D6C1/D_8010D6C2; this
// indexes the one table). Logic checked.
#ifdef NON_MATCHING
/* Two sparklers circling work->unk_18 (150 units out, opposite each other), each leaving sparks
   behind it in a spiral around its direction of travel. Never returns. */
void func_8010FB88_staff(void) {
    s16 angle[2];
    Vec cur[2];
    Vec prev[2];
    f32 roll[2];
    f32 tilt[2];
    StFwWork* work;
    HmfData* hmf;
    HmfModelData_Unk64_Unk60_Struct* obj;
    HmfModelData_Unk64_Unk60_Unk54_Struct* face;
    StFxWork* fx;
    s16 model;
    s16 i;
    s16 j;
    s16 count;
    f32 x;
    f32 y;
    f32 z;
    f32 a;
    f32 len;
    f32 ux;
    f32 uy;
    f32 uz;
    u8 k;

    work = HuPrcCurrentGet()->user_data;
    model = func_8000B108_main(0xB0034, 0x6A8);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    hmf = HmfModelData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        obj = &hmf->unk60[j];
        count = obj->unk22;
        face = obj->unk54;
        for (i = 0; i < count; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_8010F4C4_staff);
    func_800138EC_main(model, 8, 8);
    fx = ST_FXWORK(model);
    func_8001C258_main(model, 4, 4);
    func_8001C258_main(model, 4, 0);
    func_80013954_main(model, 0);
    fx->hook = func_8010F9D4_staff;
    func_800138EC_main(model, 2, 0);
    work->unk_30 = work->unk_18;
    cur[0].x = sindf(0.0f) * 150.0f + work->unk_30.x;
    cur[0].y = work->unk_30.y;
    cur[0].z = cosdf(0.0f) * 150.0f + work->unk_30.z;
    prev[0] = cur[0];
    tilt[0] = roll[0] = 0.0f;
    angle[0] = 0;
    cur[1].x = sindf(180.0f) * 150.0f + work->unk_30.x;
    cur[1].y = work->unk_30.y;
    cur[1].z = cosdf(180.0f) * 150.0f + work->unk_30.z;
    prev[1] = cur[1];
    tilt[1] = roll[1] = 180.0f;
    angle[1] = 180;
    while (TRUE) {
        HuPrcVSleep();
        for (i = 0; i < 2; i++) {
            prev[i] = cur[i];
            x = sindf(angle[i]) * 150.0f;
            z = cosdf(angle[i]) * 150.0f;
            a = sindf(tilt[i]) * 10.0f;
            cur[i].x = x * cosdf(a) + work->unk_30.x;
            cur[i].y = x * -sindf(a) + work->unk_30.y;
            cur[i].z = z + work->unk_30.z;
            angle[i] += 5;
            if (angle[i] > 360) {
                angle[i] -= 360;
            }
            roll[i] += 20.0f;
            if (roll[i] > 360.0f) {
                roll[i] -= 360.0f;
            }
            tilt[i] += 1.0f;
            if (tilt[i] > 360.0f) {
                tilt[i] -= 360.0f;
            }
            x = prev[i].x - cur[i].x;
            y = prev[i].y - cur[i].y;
            z = prev[i].z - cur[i].z;
            len = HuSqrtf(x * x + y * y + z * z);
            if (len != 0.0f) {
                x /= len;
                y /= len;
                z /= len;
                a = roll[i];
                /* (0, 1, 0) turned by a about the direction of travel */
                ux = x * y * (1.0f - cosdf(a)) - z * sindf(a);
                uy = y * y + (1.0f - y * y) * cosdf(a);
                uz = y * z * (1.0f - cosdf(a)) + x * sindf(a);
                ux = (x * 0.7f + ux * 0.3f) * len * 0.7f;
                uy = (y * 0.7f + uy * 0.3f) * len * 0.7f;
                uz = (z * 0.7f + uz * 0.3f) * len * 0.7f;
                k = rand8() & 3;
                func_8010F3E4_staff(model, cur[i].x, cur[i].y, cur[i].z, ux, uy, uz,
                                         D_801111E0_staff[k][0], D_801111E0_staff[k][1],
                                         D_801111E0_staff[k][2])->scale = 1.0f;
                ux = -(x * y * (1.0f - cosdf(a)) - z * sindf(a));
                uy = -(y * y + (1.0f - y * y) * cosdf(a));
                uz = -(y * z * (1.0f - cosdf(a)) + x * sindf(a));
                ux = (x * 0.7f + ux * 0.3f) * len * 0.7f;
                uy = (y * 0.7f + uy * 0.3f) * len * 0.7f;
                uz = (z * 0.7f + uz * 0.3f) * len * 0.7f;
                k = rand8() & 3;
                func_8010F3E4_staff(model, cur[i].x, cur[i].y, cur[i].z, ux, uy, uz,
                                         D_801111E0_staff[k][0], D_801111E0_staff[k][1],
                                         D_801111E0_staff[k][2])->scale = 1.0f;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010FB88_staff);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111430_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011143C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111448_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111454_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111460_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011146C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111478_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111484_staff);

/* .data (story j3) */
s16 D_80110530_staff[2] = { 0, 0 };
f32 D_80110534_staff = 58.0f; /* camera field of view */
s8 D_80110538_staff = 0;
s32 D_8011053C_staff = 0;
s32 D_80110540_staff[8] = {
    0xB003E, 0xB003F, 0xB0040, 0xB0041,
    0xB0042, 0xB0043, 0xB0044, 0xB0045,
};
StaffCamKey D_80110560_staff = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1390.0f, 32.0f, { -56, -1, -923766519 } };
s32 D_8011058C_staff[4] = { 0x16001E, 0x16001F, 0x160020, 0x160021 };
u8 D_8011059C_staff[4] = { 0x06, 0x08, 0x10, 0x20 };
u16 D_801105A0_staff[4] = { 0xF000, 0xF001, 0xF002, 0xF003 };
f32 D_801105A8_staff[4] = { 6.0f, 4.0f, 2.0f, 1.0f };
s16 D_801105B8_staff[4] = { 2, 6, 6, 0 };
s16 D_801105C0_staff[4] = { 402, 400, 400, 0 };
s16 D_801105C8_staff[3][2] = { { 160, 175 }, { 38, 185 }, { 286, 194 } }; /* D_801105CA_staff is [0][1] (undefined_syms.txt) */
s32 D_801105D4_staff[3] = { 0x16001B, 0x16001C, 0x16001D };
s32 D_801105E0_staff[4] = { 0x160022, 0x160023, 0, 0 };
s32 D_801105F0_staff[2] = { 0xA0075, 0xA0122 };
Vec D_801105F8_staff[2] = { { -755.0f, 580.0f, 0.0f }, { 755.0f, 580.0f, 0.0f } };
f32 D_80110610_staff[2] = { 360.0f, 180.0f };
Vec D_80110618_staff[4] = {
    { 0.0f, 70.0f, 546.0f },
    { 0.0f, 200.0f, 315.0f },
    { -402.0f, 296.0f, -37.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec D_80110648_staff[3] = { { -402.0f, 296.0f, -37.0f }, { 48.0f, 4.0f, 1298.0f }, { 9999.0f, 9999.0f, 9999.0f } };
s16 D_8011066C_staff[4] = { -160, -80, 80, 160 };
/* D_80110678_staff is [0].name (undefined_syms.txt) */
StaffAnimDef D_80110674_staff[18] = {
    { 0x200A4, D_801113F0_staff }, { 0x300A4, D_801113E4_staff }, { 0x700AB, D_801113D8_staff },
    { 0x400A4, D_801113CC_staff }, { 0x500A9, D_801113C0_staff }, { 0x600A4, D_801113B4_staff },
    { 0x90027, D_801113A8_staff }, { 0x800A4, D_8011139C_staff }, { 0xA0046, D_80111390_staff },
    { 0xA0100, D_80111384_staff }, { 0xA00A3, D_80111378_staff }, { 0xA00B7, D_8011136C_staff },
    { 0xA002B, D_80111360_staff }, { 0xA00E5, D_80111354_staff }, { 0xA00A3, D_80111378_staff },
    { 0xA00B7, D_8011136C_staff }, { 0xA002B, D_80111348_staff }, { 0xA007E, D_8011133C_staff },
};
StaffCastEntry D_80110704_staff[38] = {
    { 0.8f, 0x200A0, 0x2009D, { 0, 0, 0 }, 0, 0, 1 }, { 0.8f, 0x300A0, 0x3009D, { 0, 0, 0 }, 0, 0, 2 },
    { 0.8f, 0x700A0, 0x7009D, { 0, 0, 0 }, 0, 0, 3 }, { 0.8f, 0x400A0, 0x4009D, { 0, 0, 0 }, 0, 0, 4 },
    { 0.8f, 0x500A0, 0x5009D, { -26, 2, 0 }, 0, 0, 5 }, { 0.8f, 0x600A0, 0x6009D, { 30, 0, 0 }, 0, 0, 6 },
    { 0.8f, 0x90001, 0x90019, { 28, 0, 0 }, 0, 0, 7 }, { 0.8f, 0x16004B, 0x8009D, { 0, 0, 0 }, 0, 0, 8 },
    { 0.6f, 0xA002E, 0xA0040, { 0, 30, 0 }, 0, 0, 9 }, { 0.8f, 0xA00EE, 0xA00F4, { 0, -2, 0 }, 0, 0, 10 },
    { 0.8f, 0xA008E, 0xA00A1, { 0, 0, 0 }, 0, 0, 11 }, { 0.8f, 0xA00A5, 0, { 0, 32, 0 }, 1, 0, 12 },
    { 0.8f, 0xA0000, 0xA000A, { 0, -45, -80 }, 0, 0, 13 }, { 0.55f, 0xA00C4, 0xA00CB, { 0, 100, 0 }, 3, 0, 0 },
    { 0.9f, 0xA00BA, 0xA00C3, { 0, 30, 0 }, 4, 160, 0 }, { 0.8f, 0xA00CE, 0xA00D8, { 0, 0, 0 }, 0, 0, 0 },
    { 0.8f, 0xA0136, 0xA0138, { 0, 30, 0 }, 1, 0, 0 }, { 0.5f, 0xA010D, 0xA0116, { 0, 30, 0 }, 0, -15, 0 },
    { 0.5f, 0xA00D9, 0xA00DD, { 0, 30, 0 }, 1, 0, 0 }, { 0.8f, 0xA00E7, 0, { 0, 35, 0 }, 2, 140, 0 },
    { 1.2f, 0xA013F, 0xA0141, { 0, 30, 0 }, 0, 0, 0 }, { 0.6f, 0xA011B, 0xA011D, { 0, 30, 0 }, 0, 0, 0 },
    { 0.8f, 0xA0089, 0, { 0, 110, 0 }, 5, 0, 0 }, { 0.8f, 0xA00A2, 0xA0090, { 0, 30, 0 }, 1, 0, 15 },
    { 0.8f, 0xA00B0, 0xA00B1, { 0, 30, 0 }, 0, 0, 16 }, { 0.8f, 0xA0028, 0xA0019, { 0, 30, 0 }, 0, 0, 17 },
    { 0.8f, 0xA0063, 0xA006C, { 0, 30, 0 }, 0, 0, 0 }, { 0.6f, 0xA0086, 0xA0088, { 0, 10, -80 }, 1, 0, 0 },
    { 0.4f, 0xA0154, 0, { 0, 30, -40 }, 8, 140, 0 }, { 0.8f, 0xA014D, 0xA0153, { 0, 0, 0 }, 0, 0, 0 },
    { 0.8f, 0xA0156, 0, { 0, -25, -50 }, 6, 0, 0 }, { 0.8f, 0xA008B, 0, { 0, 30, 0 }, 7, 0, 0 },
    { 0.75f, 0xA0117, 0, { 0, 30, -20 }, 10, 165, 0 }, { 0.38f, 0x1301F4, 0, { 0, 116, 0 }, 11, 0, 0 },
    { 0.5f, 0x1301F5, 0, { 0, 45, 0 }, 0, 0, 0 }, { 0.95f, 0xA0122, 0xA0128, { 0, 138, 0 }, 12, 0, 0 },
    { 0.8f, 0xA0075, 0x1D0084, { 0, 30, 0 }, 0, 0, 18 }, { 0.0f, 0, 0, { 0, 0, 0 }, -1, 0, 0 },
};
s32 D_80110A94_staff[3] = { 0, 0, 0 }; /* zero padding to 0x80110AA0 (16-byte aligned: likely a file boundary in .data) */
s32 D_80110AA0_staff[27] = {
    0x160000, 0x160001, 0x160002, 0x160003, 0x160004, 0x160005,
    0x160006, 0x160007, 0x160008, 0x160009, 0x16000A, 0x16000B,
    0x16000C, 0x16000D, 0x16000E, 0x16000F, 0x160010, 0x160011,
    0x160012, 0x160013, 0x160014, 0x160015, 0x160016, 0x160017,
    0x160018, 0x160019, 0x16004A,
};
s32 D_80110B0C_staff[29] = {
    0x160026, 0x160027, 0x160028, 0x160029, 0x16002A, 0x16002B,
    0x16002C, 0x16002D, 0x16002E, 0x16002F, 0x160030, 0x160031,
    0x160032, 0x160033, 0x160034, 0x160035, 0x160036, 0x160037,
    0x160038, 0x160039, 0x16003A, 0x16003B, 0x16003C, 0x16003D,
    0x16003E, 0x16003F, 0x160041, 0x160040, 0,
};
s32 D_80110B80_staff = 0x160042;
StaffCreditLine D_80110B84_staff[3] = {
    { 4, 0x00, 0x6400 }, { 1, 0x00, 0x4B00 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110B90_staff[3] = {
    { 4, 0x00, 0x6401 }, { 1, 0x00, 0x4B01 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110B9C_staff[3] = {
    { 4, 0x00, 0x6402 }, { 1, 0x00, 0x4B02 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110BA8_staff[13] = {
    { 4, 0x00, 0x6403 }, { 3, 0x00, 0x6425 }, { 1, 0x00, 0x4B02 }, { 3, 0x00, 0x6426 },
    { 1, 0x00, 0x4B03 }, { 1, 0x0F, 0x4B04 }, { 1, 0x00, 0x4B05 }, { 1, 0x0F, 0x4B06 },
    { 1, 0x00, 0x4B07 }, { 1, 0x00, 0x4B08 }, { 3, 0x00, 0x6427 }, { 1, 0x00, 0x4B01 },
    { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110BDC_staff[4] = {
    { 4, 0x00, 0x6404 }, { 1, 0x00, 0x4B09 }, { 1, 0x00, 0x4B0A }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110BEC_staff[3] = {
    { 4, 0x00, 0x6405 }, { 1, 0x00, 0x4B0B }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110BF8_staff[8] = {
    { 4, 0x00, 0x6406 }, { 3, 0x00, 0x6425 }, { 1, 0x00, 0x4B0C }, { 3, 0x00, 0x6426 },
    { 1, 0x00, 0x4B0D }, { 3, 0x00, 0x6427 }, { 1, 0x00, 0x4B0E }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110C18_staff[21] = {
    { 4, 0x00, 0x6407 }, { 3, 0x00, 0x6425 }, { 1, 0x00, 0x4B0F }, { 3, 0x00, 0x6426 },
    { 1, 0x00, 0x4B10 }, { 1, 0x00, 0x4B11 }, { 1, 0x00, 0x4B12 }, { 1, 0x00, 0x4B13 },
    { 1, 0x0F, 0x4B14 }, { 1, 0x00, 0x4B15 }, { 1, 0x00, 0x4B16 }, { 1, 0x00, 0x4B17 },
    { 1, 0x00, 0x4B18 }, { 1, 0x0F, 0x4B19 }, { 1, 0x00, 0x4B1A }, { 1, 0x00, 0x4B1B },
    { 1, 0x00, 0x4B1C }, { 3, 0x00, 0x6427 }, { 1, 0x00, 0x4B1D }, { 1, 0x00, 0x4B1E },
    { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110C6C_staff[3] = {
    { 4, 0x00, 0x6408 }, { 1, 0x00, 0x4B1F }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110C78_staff[3] = {
    { 4, 0x00, 0x6409 }, { 1, 0x00, 0x4B20 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110C84_staff[8] = {
    { 4, 0x00, 0x640A }, { 3, 0x00, 0x6425 }, { 1, 0x00, 0x4B21 }, { 3, 0x00, 0x6426 },
    { 1, 0x00, 0x4B22 }, { 3, 0x00, 0x6427 }, { 1, 0x00, 0x4B23 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110CA4_staff[9] = {
    { 4, 0x00, 0x640B }, { 3, 0x00, 0x6425 }, { 1, 0x00, 0x4B24 }, { 3, 0x00, 0x6426 },
    { 1, 0x00, 0x4B25 }, { 3, 0x00, 0x6427 }, { 1, 0x00, 0x4B26 }, { 1, 0x00, 0x4B27 },
    { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110CC8_staff[3] = {
    { 4, 0x00, 0x640C }, { 1, 0x00, 0x4B28 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110CD4_staff[10] = {
    { 4, 0x00, 0x640D }, { 3, 0x00, 0x6428 }, { 1, 0x00, 0x4B29 }, { 3, 0x00, 0x6425 },
    { 1, 0x00, 0x4B2A }, { 3, 0x00, 0x6426 }, { 1, 0x00, 0x4B2B }, { 3, 0x00, 0x6427 },
    { 1, 0x00, 0x4B2C }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110CFC_staff[22] = {
    { 4, 0x00, 0x640E }, { 3, 0x00, 0x6428 }, { 1, 0x00, 0x4B2D }, { 1, 0x00, 0x4B2E },
    { 3, 0x00, 0x6425 }, { 1, 0x00, 0x4B2F }, { 3, 0x00, 0x6426 }, { 1, 0x00, 0x4B30 },
    { 1, 0x00, 0x4B31 }, { 1, 0x0F, 0x4B32 }, { 1, 0x00, 0x4B33 }, { 1, 0x00, 0x4B34 },
    { 1, 0x00, 0x4B35 }, { 1, 0x00, 0x4B36 }, { 1, 0x0F, 0x4B37 }, { 1, 0x00, 0x4B38 },
    { 1, 0x00, 0x4B39 }, { 1, 0x00, 0x4B3A }, { 3, 0x00, 0x6427 }, { 1, 0x00, 0x4B3B },
    { 1, 0x00, 0x4B3C }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110D54_staff[6] = {
    { 4, 0x00, 0x640F }, { 1, 0x00, 0x4B3D }, { 1, 0x00, 0x4B3E }, { 1, 0x00, 0x4B3F },
    { 1, 0x00, 0x4B40 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110D6C_staff[4] = {
    { 4, 0x00, 0x6410 }, { 1, 0x00, 0x4B41 }, { 1, 0x00, 0x4B42 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110D7C_staff[3] = {
    { 4, 0x00, 0x6411 }, { 1, 0x00, 0x4B43 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110D88_staff[3] = {
    { 4, 0x00, 0x6412 }, { 1, 0x00, 0x4B44 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110D94_staff[3] = {
    { 4, 0x00, 0x6413 }, { 1, 0x00, 0x4B45 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110DA0_staff[4] = {
    { 4, 0x00, 0x6414 }, { 1, 0x00, 0x4B46 }, { 1, 0x00, 0x4B4A }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110DB0_staff[3] = {
    { 4, 0x00, 0x6415 }, { 1, 0x00, 0x4B47 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110DBC_staff[4] = {
    { 4, 0x00, 0x6416 }, { 1, 0x00, 0x4B48 }, { 1, 0x00, 0x4B4B }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110DCC_staff[3] = {
    { 4, 0x00, 0x6417 }, { 1, 0x00, 0x4B49 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110DD8_staff[3] = {
    { 4, 0x00, 0x6418 }, { 1, 0x00, 0x4B4C }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110DE4_staff[6] = {
    { 4, 0x00, 0x6419 }, { 1, 0x16, 0x4B4D }, { 2, 0x0F, 0x0 }, { 1, 0x00, 0x4B4E },
    { 1, 0x00, 0x4B4F }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110DFC_staff[4] = {
    { 4, 0x00, 0x641A }, { 1, 0x00, 0x4B50 }, { 1, 0x00, 0x4B51 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110E0C_staff[3] = {
    { 4, 0x00, 0x641B }, { 1, 0x00, 0x4B52 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110E18_staff[3] = {
    { 4, 0x00, 0x641C }, { 1, 0x00, 0x4B53 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110E24_staff[3] = {
    { 4, 0x00, 0x641D }, { 1, 0x00, 0x4B54 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110E30_staff[15] = {
    { 4, 0x00, 0x641E }, { 3, 0x00, 0x642B }, { 1, 0x00, 0x4B6C }, { 1, 0x00, 0x4B6D },
    { 3, 0x00, 0x642C }, { 1, 0x00, 0x4B6E }, { 1, 0x00, 0x4B6F }, { 3, 0x00, 0x642D },
    { 1, 0x00, 0x4B70 }, { 1, 0x00, 0x4B71 }, { 3, 0x00, 0x642E }, { 1, 0x00, 0x4B72 },
    { 1, 0x00, 0x4B73 }, { 1, 0x00, 0x4B74 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110E6C_staff[18] = {
    { 4, 0x00, 0x641F }, { 1, 0x00, 0x4B56 }, { 1, 0x00, 0x4B57 }, { 1, 0x0F, 0x4B58 },
    { 1, 0x0F, 0x4B59 }, { 1, 0x0F, 0x4B5A }, { 1, 0x00, 0x4B6A }, { 1, 0x0F, 0x4B6B },
    { 1, 0x00, 0x4B5B }, { 1, 0x0F, 0x4B5C }, { 1, 0x0F, 0x4B5D }, { 1, 0x0F, 0x4B5E },
    { 1, 0x0F, 0x4B75 }, { 1, 0x00, 0x4B76 }, { 1, 0x0F, 0x4B5F }, { 1, 0x0F, 0x4B60 },
    { 1, 0x00, 0x4B61 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110EB4_staff[4] = {
    { 4, 0x00, 0x6420 }, { 1, 0x00, 0x4B62 }, { 1, 0x00, 0x4B0A }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110EC4_staff[4] = {
    { 4, 0x00, 0x6421 }, { 1, 0x00, 0x4B63 }, { 1, 0x00, 0x4B64 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110ED4_staff[4] = {
    { 4, 0x00, 0x6422 }, { 1, 0x00, 0x4B41 }, { 1, 0x00, 0x4B65 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110EE4_staff[4] = {
    { 4, 0x00, 0x6423 }, { 1, 0x00, 0x4B66 }, { 1, 0x00, 0x4B67 }, { -1, 0x00, 0x0 },
};
StaffCreditLine D_80110EF4_staff[4] = {
    { 4, 0x00, 0x6424 }, { 1, 0x00, 0x4B68 }, { 1, 0x1E, 0x4B69 }, { -1, 0x00, 0x0 },
};
/* the credits pages, NULL-terminated */
StaffCreditLine* D_80110F04_staff[39] = {
    D_80110B84_staff, D_80110B90_staff, D_80110B9C_staff, D_80110BA8_staff,
    D_80110BDC_staff, D_80110BEC_staff, D_80110BF8_staff, D_80110C18_staff,
    D_80110C6C_staff, D_80110C78_staff, D_80110C84_staff, D_80110CA4_staff,
    D_80110CC8_staff, D_80110CD4_staff, D_80110CFC_staff, D_80110D54_staff,
    D_80110D6C_staff, D_80110D7C_staff, D_80110D88_staff, D_80110D94_staff,
    D_80110DA0_staff, D_80110DB0_staff, D_80110DBC_staff, D_80110DCC_staff,
    D_80110DD8_staff, D_80110DE4_staff, D_80110DFC_staff, D_80110E0C_staff,
    D_80110E18_staff, D_80110E24_staff, D_80110E30_staff, D_80110E6C_staff,
    D_80110EB4_staff, D_80110EC4_staff, D_80110ED4_staff, D_80110EE4_staff,
    D_80110EF4_staff, NULL, NULL,
};
Vec D_80110FA0_staff[5] = {
    { -77.0f, 202.0f, 1762.0f },
    { -135.0f, 170.0f, 2500.0f },
    { -135.0f, 140.0f, 2500.0f },
    { 115.0f, 400.0f, -115.0f },
    { 52.0f, 0.0f, 135.0f },
};
Vec D_80110FDC_staff = { 52.0f, 340.0f, 400.0f };
s32 D_80110FE8_staff[3] = { 0x160004, 0x16000D, 0x160003 };
StaffModelDef D_80110FF4_staff[4] = {
    { 0xF0004, 697, 0, 0, 1, { -41.0f, 0.0f, 2893.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xF0003, 697, 0, 0, 1, { 96.0f, 0.0f, 3072.0f }, { 0.0f, -30.0f, 0.0f } },
    { 0xF0005, 697, 0, 0, 1, { -59.0f, 45.0f, 2907.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xA015E, 697, 0, 2, 1, { -77.0f, 202.0f, 1216.0f }, { 0.0f, 0.0f, 0.0f } },
};
StaffActorDef D_80111094_staff[8] = {
    { 0x200A1, 0xF000B, 0x200A4, D_80111484_staff, { 100.0f, -14.0f, 3072.0f }, { 0.0f, -30.0f, 0.0f } },
    { 0x300A1, 0x160043, 0x300AB, D_80111478_staff, { 205.0f, 0.0f, 2869.0f }, { 0.0f, 46.0f, 0.0f } },
    { 0x700A1, 0x160044, 0x700AB, D_8011146C_staff, { 299.0f, 0.0f, 2950.0f }, { 0.0f, -122.0f, 0.0f } },
    { 0x400A1, 0x160045, 0x400A3, D_80111460_staff, { -150.0f, 0.0f, 1762.0f }, { 0.0f, 83.0f, 0.0f } },
    { 0x500A1, 0x160046, 0x500AA, D_80111454_staff, { -626.0f, 0.0f, 2245.0f }, { 0.0f, 79.0f, 0.0f } },
    { 0x600A1, 0x160047, 0x600A4, D_80111448_staff, { -203.0f, 0.0f, 3066.0f }, { 0.0f, 39.0f, 0.0f } },
    { 0x800A1, 0x160048, 0x800AA, D_8011143C_staff, { -346.0f, 0.0f, 2356.0f }, { 0.0f, -103.0f, -8.0f } },
    { 0x90001, 0x160049, 0x9001A, D_80111430_staff, { -133.0f, 0.0f, 2460.0f }, { 0.0f, 0.0f, 0.0f } },
};
s32 D_801111D4_staff[3] = { 0, 0, 0 }; /* zero padding to 0x801111E0 (16-byte aligned: likely a file boundary in .data) */
/* firework spark colours (r, g, b, pad); D_801111E1/E2 alias [0][1]/[0][2] */
u8 D_801111E0_staff[4][4] = {
    { 0x00, 0xFF, 0xFF, 0x00 },
    { 0xFF, 0xA0, 0x28, 0x00 },
    { 0xFF, 0xFF, 0x00, 0x00 },
    { 0x00, 0xFF, 0x00, 0x00 },
};
