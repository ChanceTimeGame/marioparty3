#include "common.h"

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D8640_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D8778_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D8818_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D89CC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D9028_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D972C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D9F10_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D9F3C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA054_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA204_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA2E0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA540_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA768_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DB628_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DB704_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DB724_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DBCF4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DC354_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DC7D8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DC8E4_minigame);

/* minigame B: collision contacts and actor physics (MP2 src/1130.c func_80006440_7040 on, MP1
   src/1130.c func_8000396C on). */
s32 func_800202FC_main(Vec*); /* normalise */

/* A probe sphere (MP2 collision.h Vec4f). */
typedef struct Vec4f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ f32 w; /* radius */
} Vec4f;

/* omObjData.data of a ground / platform object (MP2 collision.h GroundWork; offsets checked
   against MP3's asm). */
typedef struct GroundWork {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;  /* surface id */
    /* 0x05 */ char unk_05;
    /* 0x06 */ u16 unk_06; /* flags: 2 skip, 4 test the part list, 8/0x10/0x20/0x40 shapes */
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14; /* top surface height */
    /* 0x18 */ char unk_18[0x80];
    /* 0x98 */ f32 unk_98; /* height */
    /* 0x9C */ f32 unk_9C; /* cylinder radius */
    /* 0xA0 */ f32 unk_A0; /* box min x */
    /* 0xA4 */ f32 unk_A4; /* box min z */
    /* 0xA8 */ f32 unk_A8; /* box max x */
    /* 0xAC */ f32 unk_AC; /* box max z */
} GroundWork; /* size unknown */

extern s16 D_800EB736_minigame;     /* contact count (MP2 D_800BF796_C0396) */
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern Vec D_800EBDD0_minigame;     /* the actor's position at the start of its step */
extern f32 D_800EBE2C_minigame;     /* push x this frame */
extern f32 D_800EC5D8_minigame;     /* push z this frame */
extern Vec D_800EBEB8_minigame[];   /* contact points */
extern Vec D_800EC298_minigame[];   /* contact normals */

void func_800E0430_minigame(f32 x, f32 y, f32 z);
void func_800E048C_minigame(f32 x, f32 y, f32 z);

/* Box corners: a probe beyond a corner of the box (GroundWork.unk_A0..unk_AC) touching it adds the
   corner as a contact and returns 0; otherwise 1. */
s32 func_800DCA34_minigame(Vec4f* s, GroundWork* g) {
    f32 x = s->x;
    f32 y = s->y;
    f32 z = s->z;
    f32 dx, dz;

    if (x <= g->unk_A0) {
        dx = g->unk_A0 - x;
        dz = g->unk_A4;
        if (z <= dz) {
            dz -= z;
            if (HuSqrtf(dx * dx + dz * dz) - s->w < 0.0f) {
                func_800E048C_minigame(g->unk_A0, y, g->unk_A4);
                func_800E0430_minigame(x - g->unk_A0, 0.0f, z - g->unk_A4);
                D_800EB736_minigame++;
                return 0;
            }
        } else if ((dz = g->unk_AC) <= z) {
            dz -= z;
            if (HuSqrtf(dx * dx + dz * dz) - s->w < 0.0f) {
                func_800E048C_minigame(g->unk_A0, y, g->unk_AC);
                func_800E0430_minigame(x - g->unk_A0, 0.0f, z - g->unk_AC);
                D_800EB736_minigame++;
                return 0;
            }
        }
    } else if (s->x >= g->unk_A8) {
        dx = g->unk_A8 - x;
        dz = g->unk_A4;
        if (z <= dz) {
            dz -= z;
            if (HuSqrtf(dx * dx + dz * dz) - s->w < 0.0f) {
                func_800E048C_minigame(g->unk_A8, y, g->unk_A4);
                func_800E0430_minigame(x - g->unk_A8, 0.0f, z - g->unk_A4);
                D_800EB736_minigame++;
                return 0;
            }
        } else if ((dz = g->unk_AC) <= z) {
            dz -= z;
            if (HuSqrtf(dx * dx + dz * dz) - s->w < 0.0f) {
                func_800E048C_minigame(g->unk_A8, y, g->unk_AC);
                func_800E0430_minigame(x - g->unk_A8, 0.0f, z - g->unk_AC);
                D_800EB736_minigame++;
                return 0;
            }
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DCCB0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DD1F4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DD530_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDB60_minigame);

void func_800DDD70_minigame(omObjData* obj) {
    D_800EBDD0_minigame.x = obj->trans.x;
    D_800EBDD0_minigame.y = obj->trans.y;
    D_800EBDD0_minigame.z = obj->trans.z;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDD94_minigame);

/* Push the actor by d along (dx, 0, dz), normalised. */
void func_800DFCDC_minigame(f32 dx, f32 dz, f32 d) {
    Vec v;

    v.x = dx;
    v.y = 0.0f;
    v.z = dz;
    func_800202FC_main(&v);
    D_800EBE2C_minigame += d * v.x;
    D_800EC5D8_minigame += d * v.z;
}

f32 func_800DFD48_minigame(f32 arg0) {
    if (arg0 < D_800EB76C_minigame)
        return D_800EB76C_minigame;

    if (!(arg0 < D_800EB768_minigame)) {
        if (!(arg0 < D_800EB764_minigame)) {
            return arg0;
        } else {
            return D_800EB764_minigame;
        }
    } else {
        return D_800EB768_minigame;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFD9C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFE44_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFF3C_minigame);

/* Records contact normal number D_800EB736_minigame, normalised. */
void func_800E0430_minigame(f32 x, f32 y, f32 z) {
    s16 i = D_800EB736_minigame;

    D_800EC298_minigame[i].x = x;
    D_800EC298_minigame[i].y = y;
    D_800EC298_minigame[i].z = z;
    func_800202FC_main(&D_800EC298_minigame[i]);
}

/* Records contact point number D_800EB736_minigame. */
void func_800E048C_minigame(f32 x, f32 y, f32 z) {
    s16 i = D_800EB736_minigame;

    D_800EBEB8_minigame[i].x = x;
    D_800EBEB8_minigame[i].y = y;
    D_800EBEB8_minigame[i].z = z;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800E04C8_minigame);
