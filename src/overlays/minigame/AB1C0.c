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

/* A probe sphere plus the actor's position (MP2 collision.h ColSphere). */
typedef struct ColSphere {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 r;
    /* 0x10 */ f32 x2;
    /* 0x14 */ f32 y2;
    /* 0x18 */ f32 z2;
} ColSphere;

/* Result list of func_80021C14_main (src/20A20.c HitList). */
typedef struct HitList {
    /* 0x00 */ u16** list;
    /* 0x04 */ u16 count;
    /* 0x06 */ u16 pos;
} HitList;

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

/* omObjData.data of a minigame player (MP2 collision.h MgWork, 0x15C bytes); only the fields this
   unit's B functions use are named, offsets from MP3's asm. */
typedef struct MgWork {
    /* 0x00 */ u8 unk_00[0x20]; /* per ground object flags: 1 ignore it, 8 hazard */
    /* 0x20 */ char unk_20[0x14];
    /* 0x34 */ f32 unk_34;  /* height */
    /* 0x38 */ f32 unk_38;  /* vertical speed; 1000.0f on the ground */
    /* 0x3C */ f32 unk_3C;  /* heading */
    /* 0x40 */ f32 unk_40;  /* speed */
    /* 0x44 */ char unk_44[4];
    /* 0x48 */ f32 unk_48;  /* radius */
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ u16 unk_50;  /* flags */
    /* 0x52 */ u8 unk_52;
    /* 0x53 */ s8 unk_53;   /* ground object index, -1 none */
    /* 0x54 */ s8 unk_54;
    /* 0x55 */ u8 unk_55;
    /* 0x56 */ u8 unk_56;
    /* 0x57 */ s8 unk_57;   /* controller port */
    /* 0x58 */ u8 unk_58;
    /* 0x59 */ s8 unk_59;   /* player */
    /* 0x5A */ char unk_5A[2];
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ char unk_68[4];
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ s32 unk_74[6]; /* packed (x << 16) | (y & 0xFFFF) stick samples */
    /* 0x8C */ f32 unk_8C;  /* ceiling height */
    /* 0x90 */ f32 unk_90;  /* ground velocity */
    /* 0x94 */ f32 unk_94;
    /* 0x98 */ f32 unk_98;
    /* 0x9C */ f32 unk_9C;  /* tilt x */
    /* 0xA0 */ f32 unk_A0;
    /* 0xA4 */ f32 unk_A4;  /* tilt z */
    /* 0xA8 */ char unk_A8[4];
    /* 0xAC */ f32 unk_AC;
    /* 0xB0 */ f32 unk_B0;
    /* 0xB4 */ f32 unk_B4;  /* speed factor */
    /* 0xB8 */ char unk_B8[4];
    /* 0xBC */ u16 unk_BC;  /* frames running, at most 200 */
    /* 0xBE */ u16 unk_BE;  /* hazard hit countdown */
    /* 0xC0 */ u16 unk_C0;  /* spin countdown */
    /* 0xC2 */ char unk_C2;
    /* 0xC3 */ s8 unk_C3;
    /* 0xC4 */ s8 unk_C4;
    /* 0xC5 */ s8 unk_C5;
    /* 0xC6 */ s16 unk_C6;  /* turn lean, -12..12 */
    /* 0xC8 */ void* unk_C8; /* held item, an omObjData* */
    /* 0xCC */ f32 unk_CC;
    /* 0xD0 */ u16 unk_D0;
    /* 0xD2 */ char unk_D2[8];
    /* 0xDA */ u16 unk_DA;
    /* 0xDC */ char unk_DC[0xC];
    /* 0xE8 */ void* unk_E8;
    /* 0xEC */ s32 (*unk_EC)(omObjData* obj, omObjData* actor); /* actor touch hook; 1 skips the default */
    /* 0xF0 */ u16 unk_F0;
    /* 0xF2 */ char unk_F2[0x12];
    /* 0x104 */ s32 (*unk_104[21])(); /* the minigame's override hooks; 1 = handled */
    /* 0x158 */ void* unk_158;
} MgWork;

/* omObjData.data of a minigame item actor (MP2 collision.h ColActorWork); fields this unit uses. */
typedef struct ColActorWork {
    /* 0x00 */ char unk_00[0x48];
    /* 0x48 */ f32 unk_48;      /* radius */
    /* 0x4C */ char unk_4C[4];
    /* 0x50 */ u16 unk_50;      /* flags */
} ColActorWork; /* size 0x15C (MP2) */

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
void func_800DFCDC_minigame(f32 dx, f32 dz, f32 d);
void func_800E19FC_minigame(MgWork* w, s32 state);           /* B3CE0: set the motion state */
f32 func_800E2ED4_minigame(f32 ax, f32 az, f32 bx, f32 bz);  /* B3CE0: cos of the xz angle */
s32 func_800E5690_minigame(omObjData* obj, s32 motion);      /* B7600: set a motion */
void omVibrate(s16 player, s16 duration, s16 off, s16 on);
extern f32 D_800EB760_minigame;
f64 fabs(f64);
void func_80021C14_main(s16 mi, HitList* l, s32 (*cb)(), void* probe); /* src/20A20.c: faces near probe */
void func_800DC354_minigame(omObjData* obj, Vec4f* s, Vec4f* p); /* A: shape 8 (ignores p) */
void func_800DCCB0_minigame(omObjData* obj, Vec4f* s, Vec4f* p, f32 h);
void func_800DC7D8_minigame(omObjData* obj, Vec4f* s);         /* A: shape 0x20 */
void func_800DC8E4_minigame(omObjData* obj, Vec4f* s, f32 h);  /* A: shape 0x40 */
s32 func_800DB724_minigame();                                  /* A: face callbacks for func_80021C14_main */
s32 func_800DBCF4_minigame();
void func_800DD1F4_minigame(omObjData* obj, Vec* s, f32 arg2);
s32 func_800E1510_minigame(s8 surface);                        /* B3CE0 */
void func_800E28BC_minigame(f32 (*l2w)[4], f32 (*w2l)[4], Vec* p, omObjData* obj); /* B3CE0 */
void func_800E2B58_minigame(f32 (*m)[4], Vec* v);              /* B3CE0: rotate v */
s32 func_800E2FD8_minigame(HmfModelData_Unk64_Unk60_Struct* b, Vec* p, f32 r); /* B3CE0 */
void func_800146DC_main(s16 index, s32 arg1, s32 arg2);
void func_80014850_main(s16 index);
void func_800E1810_minigame(void);                              /* B3CE0 */
void func_800E2CA4_minigame(omObjData* obj, f32 speed);        /* B3CE0: throw the held item (speed unused) */
extern f32 D_800EB770_minigame;
s32 func_800DD530_minigame(omObjData* obj, Vec4f* p, f32 arg2);
void func_800E2DA4_minigame(omObjData* obj, omObjData* actor);  /* B3CE0: touch an item actor */
s32 func_800E4510_minigame(omObjData* obj, omObjData* other);   /* B63A0 */
void func_800E454C_minigame(omObjData* obj, omObjData* other, f32 dx, f32 dz, u16 i); /* B63A0: hit a player */
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b); /* B7600: effect */
extern u16 D_800EC1B8_minigame;          /* item actor count */
extern omObjData* D_800EBE70_minigame[]; /* item actors */
extern u16 D_800EC280_minigame;          /* player count */
extern omObjData* D_800EC598_minigame[]; /* players */
extern s32 fontcolor;
extern u8 D_800EB73B_minigame;          /* debug menu: homing camera */
extern f32 D_800EB73C_minigame;         /* movement tuning (debug menu rows 2-10) */
extern f32 D_800EB740_minigame;
extern f32 D_800EB744_minigame;         /* jump speed */
extern f32 D_800EB748_minigame;         /* gravity */
extern f32 D_800EB74C_minigame;
extern f32 D_800EB750_minigame;
extern f32 D_800EB754_minigame;         /* player radius */
extern f32 D_800EB758_minigame;         /* attack reach */
extern f32 D_800EB75C_minigame;
extern s8 D_800EB780_minigame;          /* debug menu row */
extern u16 D_800EC288_minigame;          /* touches while invulnerable */
f32 func_800202A8_main(f32 angle);
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z);
f32 func_800D9028_minigame(omObjData* obj, f32 x, f32 y, f32 z, f32 unused); /* A: ceiling height */
f32 func_800D972C_minigame(omObjData* obj, f32 rot, f32 x, f32 y, f32 z);    /* A: ground height, 65536.0f none */
f32 func_800DFD48_minigame(f32 speed);
void func_800DFD9C_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800E17D4_minigame(omObjData* obj, f32 x, f32 y, f32 z);     /* B3CE0: obj->trans */
void func_800E1A9C_minigame(MgWork* w, s32 arg1);                     /* B3CE0 */
s32 func_800E2250_minigame(omObjData* obj, s16 x, s16 y);             /* B3CE0: stick sample */
void func_800E2308_minigame(s16* x, s16* y);                          /* B3CE0: stick dead zone */
void func_800E23E0_minigame(omObjData* obj);                          /* B3CE0 */
s16 func_800E240C_minigame(s16 player, s16 limit, s8 x, s8 y);        /* B3CE0 */
void func_800E3820_minigame(omObjData* obj, MgWork* w);               /* B63A0 */
void func_800E38A4_minigame(omObjData* obj, MgWork* w);               /* B63A0 */
void func_800E39CC_minigame(omObjData* obj, MgWork* w, GroundWork* g, s16 x, s16 y); /* B63A0 */
void func_800E3AB8_minigame(omObjData* obj, MgWork* w);               /* B63A0 */
void func_800E3B98_minigame(omObjData* obj, MgWork* w, GroundWork* g, f32 x, f32 y, f32 z); /* B63A0 */
void func_800E3CA0_minigame(omObjData* obj, MgWork* w, GroundWork* g, f32 x, f32 y, f32 z); /* B63A0 */
void func_800E3D3C_minigame(omObjData* obj, MgWork* w);               /* B63A0 */
void func_800E3E24_minigame(omObjData* obj, f32 x, f32 y, f32 z);     /* B63A0 */
void func_800E3F44_minigame(omObjData* obj, s32 flags, f32 x, f32 y, f32 z); /* B63A0 */
void func_800E3FD8_minigame(omObjData* obj, f32 x, f32 y, f32 z);     /* B63A0 */
void func_800E4248_minigame(omObjData* obj, f32 x, f32 y, f32 z);     /* B63A0 */
s32 func_800E4A90_minigame(omObjData* obj);                           /* B7600: motion state flags */
void func_800E4E30_minigame(omObjData* obj);                          /* B7600 */
void func_800E5138_minigame(omObjData* obj);                          /* B7600 */
u8 func_800E6E8C_minigame(void);                                      /* B8A20 */
extern f32 D_800EB774_minigame;
extern u8 D_800EB734_minigame;          /* ground object the player stands on */
extern u16 D_800EBE28_minigame;         /* ground object count */
extern f32 D_800EBE30_minigame[4][4];   /* ground object: world to local */
extern HitList D_800EBEB0_minigame;
extern omObjData* D_800EC1C0_minigame[]; /* ground objects */
extern s8 D_800EC286_minigame;          /* surface id of the last object touched */
void func_800E2BD4_minigame(f32 (*m)[4], Vec* v); /* B3CE0: v = m * v (MP1 func_8000A464) */
extern f32 D_800EC240_minigame[4][4]; /* ground object: local to world */
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

/* Shape 0x10: the outside of a box (GroundWork.unk_A0..unk_AC, top unk_14, height unk_98): a corner
   (func_800DCA34_minigame) or the face the sphere is beyond adds a contact; then the actor is pushed
   out from each new contact, measured from p (MP2 func_800066BC_72BC measures from s). */
void func_800DCCB0_minigame(omObjData* obj, Vec4f* s, Vec4f* p, f32 h) {
    s32 i = D_800EB736_minigame;
    GroundWork* g = obj->data;
    f32 x = s->x;
    f32 z = s->z;
    f32 x0, z0, x1, z1;
    f32 cx, cz;

    if (s->y < h + g->unk_14 && g->unk_14 - g->unk_98 - h < s->y) {
        x0 = g->unk_A0 - s->w;
        z0 = g->unk_A4 - s->w;
        x1 = g->unk_A8 + s->w;
        z1 = g->unk_AC + s->w;
        if ((x0 <= x) & (x < x1)) {
            if ((z0 < z) & (z < z1)) {
                if (func_800DCA34_minigame(s, g) == 1) {
                    if (x0 <= x && x <= (cx = g->unk_A0)) {
                        if (g->unk_A4 <= s->z && s->z <= g->unk_AC) {
                            if (cx == s->x) {
                                cx += 1.0f;
                            }
                            func_800E048C_minigame(cx, s->y, s->z);
                            func_800E0430_minigame(-1.0f, 0.0f, 0.0f);
                            D_800EB736_minigame++;
                        }
                    } else if (x <= x1 && (cx = g->unk_A8) <= x) {
                        if (g->unk_A4 <= s->z && s->z <= g->unk_AC) {
                            if (cx == s->x) {
                                cx -= 1.0f;
                            }
                            func_800E048C_minigame(cx, s->y, s->z);
                            func_800E0430_minigame(1.0f, 0.0f, 0.0f);
                            D_800EB736_minigame++;
                        }
                    } else if (z0 <= z && z <= g->unk_A4) {
                        if (g->unk_A0 <= s->x && s->x <= g->unk_A8) {
                            cz = g->unk_A4;
                            if (cz == s->z) {
                                cz += 1.0f;
                            }
                            func_800E048C_minigame(s->x, s->y, cz);
                            func_800E0430_minigame(0.0f, 0.0f, -1.0f);
                            D_800EB736_minigame++;
                        }
                    } else if (z <= z1 && g->unk_AC <= z) {
                        if (g->unk_A0 <= s->x && s->x <= g->unk_A8) {
                            cz = g->unk_AC;
                            if (cz == s->z) {
                                cz -= 1.0f;
                            }
                            func_800E048C_minigame(s->x, s->y, cz);
                            func_800E0430_minigame(0.0f, 0.0f, 1.0f);
                            D_800EB736_minigame++;
                        }
                    }
                }
                for (; i < D_800EB736_minigame; i++) {
                    if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f ||
                        obj->rot.x != 0.0f || obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
                        func_800E2BD4_minigame(D_800EC240_minigame, &D_800EBEB8_minigame[i]);
                    }
                    x0 = D_800EBEB8_minigame[i].x - p->x;
                    z0 = D_800EBEB8_minigame[i].z - p->z;
                    func_800DFCDC_minigame(x0, z0, HuSqrtf(x0 * x0 + z0 * z0) - s->w);
                }
            }
        }
    }
}

/* After the wall pushes: a fast player running into a wall bounces off it. */
void func_800DD1F4_minigame(omObjData* obj, Vec* s, f32 arg2) {
    MgWork* w;
    f32 speed;
    f32 sa, sb;
    f32 dx, dy, dz;
    f32 lim;
    s32 i;

    if (D_800EB736_minigame == 0) {
        return;
    }
    w = obj->data;
    if (w->unk_52 == 0) {
        sa = w->unk_40;
        sb = w->unk_B4;
        if (w->unk_50 & 6) {
            speed = sa * 0.6f * sb;
        } else {
            speed = sa * sb;
        }
    } else {
        speed = w->unk_40;
    }
    if (w->unk_38 != 1000.0f) {
        speed *= w->unk_4C;
    }
    for (i = 0; i < D_800EB736_minigame; i++) {
        dx = D_800EBEB8_minigame[i].x - s->x;
        dy = D_800EBEB8_minigame[i].y - s->y;
        dz = D_800EBEB8_minigame[i].z - s->z;
        HuSqrtf(dx * dx + dy * dy + dz * dz);
        if (func_800E2ED4_minigame(sindf(w->unk_3C) * speed + D_800EBE2C_minigame, cosdf(w->unk_3C) * speed + D_800EC5D8_minigame, dx, dz) > 0.9f &&
            w->unk_38 != 1000.0f && w->unk_40 > D_800EB764_minigame) {
            lim = w->unk_40;
            if (w->unk_50 & 6) {
                lim *= 0.6f;
            }
            lim *= w->unk_4C * w->unk_B4 * 0.98f;
            if (HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame) < lim) {
                if (w->unk_50 & 8) {
                    w->unk_40 = -D_800EB760_minigame;
                } else {
                    w->unk_40 = -D_800EB76C_minigame;
                }
                func_800E5690_minigame(obj, 0x1E);
                func_800E19FC_minigame(w, 7);
                omVibrate(w->unk_59, 5, 0, 5);
                return;
            }
        }
        if (arg2 != 0.0f) {
            w->unk_40 = arg2;
            func_800E19FC_minigame(w, 7);
            omVibrate(w->unk_59, 2, 3, 10);
            return;
        }
    }
}

/* Push the player's sphere out of every ground object: the one it stands on (D_800EB734_minigame, in
   world space) first, then the others in their local space. Returns the surface id of the last
   object touched (-1 none); func_800DD1F4_minigame then handles a wall hit. */
s32 func_800DD530_minigame(omObjData* obj, Vec4f* p, f32 arg2) {
    Vec4f s;
    ColSphere s2;
    MgWork* w = obj->data;
    omObjData* o;
    GroundWork* g;
    s16 prev;
    s16 i;

    s.x = p->x;
    s.y = w->unk_34 / 2.0f + p->y;
    s.z = p->z;
    s.w = p->w;
    D_800EC286_minigame = -1;
    D_800EB736_minigame = 0;
    prev = D_800EB736_minigame;
    if (!(w->unk_00[D_800EB734_minigame] & 1)) {
        o = D_800EC1C0_minigame[D_800EB734_minigame];
        g = o->data;
        if (g->unk_06 & 8) {
            s.x += D_800EBE2C_minigame;
            s.y += D_800EC5D8_minigame;
            func_800DC354_minigame(o, &s, &s);
        } else if (g->unk_06 & 0x10) {
            s.x += D_800EBE2C_minigame;
            s.y += D_800EC5D8_minigame;
            func_800DCCB0_minigame(o, &s, &s, w->unk_34 / 2.0f);
        } else if (g->unk_06 & 0x20) {
            s.x += D_800EBE2C_minigame;
            s.y += D_800EC5D8_minigame;
            func_800DC7D8_minigame(o, &s);
        } else if (g->unk_06 & 0x40) {
            s.x += D_800EBE2C_minigame;
            s.y += D_800EC5D8_minigame;
            func_800DC8E4_minigame(o, &s, w->unk_34 / 2.0f);
        } else if (!(g->unk_06 & 2)) {
            func_80021C14_main(*D_800EC1C0_minigame[D_800EB734_minigame]->model, &D_800EBEB0_minigame, func_800DB724_minigame, &s);
        }
        if (prev != D_800EB736_minigame) {
            D_800EC286_minigame = g->unk_04;
        }
    }
    for (i = 0; i < D_800EBE28_minigame; i++) {
        o = D_800EC1C0_minigame[i];
        g = o->data;
        if (i == D_800EB734_minigame || (g->unk_06 & 2) || (w->unk_00[i] & 1)) {
            continue;
        }
        prev = D_800EB736_minigame;
        s2.x = s2.x2 = p->x;
        s2.y = s2.y2 = w->unk_34 / 2.0f + p->y;
        s2.z = s2.z2 = p->z;
        s2.r = s.w = p->w;
        func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, (Vec*)&s2, o);
        if ((g->unk_06 & 4) && func_800E2FD8_minigame(HmfModelData[*o->model].hmf->unk60, (Vec*)&s2, w->unk_48) == 0) {
            continue;
        }
        if (g->unk_06 & 8) {
            s2.x += D_800EBE2C_minigame;
            s2.y += D_800EC5D8_minigame;
            func_800DC354_minigame(o, (Vec4f*)&s2, (Vec4f*)&s2.x2);
        } else if (g->unk_06 & 0x10) {
            s2.x += D_800EBE2C_minigame;
            s2.y += D_800EC5D8_minigame;
            func_800DCCB0_minigame(o, (Vec4f*)&s2, (Vec4f*)&s2.x2, w->unk_34 / 2.0f);
        } else if (g->unk_06 & 0x20) {
            s2.x += D_800EBE2C_minigame;
            s2.y += D_800EC5D8_minigame;
            func_800DC7D8_minigame(o, (Vec4f*)&s2);
        } else if (g->unk_06 & 0x40) {
            s2.x += D_800EBE2C_minigame;
            s2.y += D_800EC5D8_minigame;
            func_800DC8E4_minigame(o, (Vec4f*)&s2, w->unk_34 / 2.0f);
        } else {
            func_80021C14_main(*D_800EC1C0_minigame[i]->model, &D_800EBEB0_minigame, func_800DBCF4_minigame, &s2);
        }
        if (prev != D_800EB736_minigame) {
            D_800EC286_minigame = g->unk_04;
            func_800E2B58_minigame(D_800EC240_minigame, &D_800EC298_minigame[D_800EB736_minigame - 1]);
        }
    }
    s.x = p->x + D_800EBE2C_minigame;
    s.y = w->unk_34 / 2.0f + p->y;
    s.z = p->z + D_800EC5D8_minigame;
    s.w = p->w;
    if (func_800E1510_minigame(D_800EC286_minigame) == 1) {
        func_800DD1F4_minigame(obj, (Vec*)&s, arg2);
    }
    return D_800EC286_minigame;
}

/* Tilt the player toward the floor normal n; a slow player levels out. */
void func_800DDB60_minigame(omObjData* obj, Vec* n) {
    MgWork* w = obj->data;
    f32 rx, rz;
    f32 cx, cz;

    if (w->unk_40 > D_800EB764_minigame) {
        rx = -(atan2df(n->y, n->z) - 90.0f);
        rz = atan2df(n->y, n->x);
        cx = w->unk_9C;
        cz = w->unk_A4;
        rz -= 90.0f;
        if (cx < rx) {
            w->unk_9C += 4.0f;
            if (rx < w->unk_9C) {
                w->unk_9C = rx;
            }
        } else if (rx < cx) {
            w->unk_9C -= 4.0f;
            if (w->unk_9C < rx) {
                w->unk_9C = rx;
            }
        }
        if (cz < rz) {
            w->unk_A4 += 4.0f;
            if (rz < w->unk_A4) {
                w->unk_A4 = rz;
            }
        } else if (rz < cz) {
            w->unk_A4 -= 4.0f;
            if (w->unk_A4 < rz) {
                w->unk_A4 = rz;
            }
        }
    } else {
        if (fabs(w->unk_9C) > 2.0) {
            obj->rot.x = w->unk_9C = w->unk_9C * 0.3;
        }
        if (fabs(w->unk_A4) > 2.0) {
            obj->rot.z = w->unk_A4 = w->unk_A4 * 0.3;
        }
    }
    obj->rot.x = w->unk_9C;
    obj->rot.z = w->unk_A4;
}

void func_800DDD70_minigame(omObjData* obj) {
    D_800EBDD0_minigame.x = obj->trans.x;
    D_800EBDD0_minigame.y = obj->trans.y;
    D_800EBDD0_minigame.z = obj->trans.z;
}

/* A minigame player's step (MP2 func_80007790_8390, MP1 func_80005A28): stick and buttons, then one
   branch per motion state (func_800E4A90_minigame's flags), then the move along the heading. MP3
   reads the stick only when func_800E6E8C_minigame() is 2, and stops the turn sound only when
   unk_C5 > 0.
   register allocation (masked 0, raw 3): the cos * mag product in the 0x320 branch takes $f12
   instead of $f4, as in MP2 (raw 3) and MP1. Tried: a temp for the product (moves the residue to
   the rx * rx below), assigning it back to mag. */
#ifdef NON_MATCHING
void func_800DDD94_minigame(omObjData* obj) {
    s16 sx;
    s16 sy;
    f32 x;
    f32 y;
    f32 z;
    MgWork* w = obj->data;
    GroundWork* g;
    GroundWork* gr;
    omObjData* o;
    u8 port = w->unk_57;
    f32 mag = 0.0f;
    u16 mdl;
    f32 vy0;
    u16 btn;
    u16 trg;
    s32 flags;
    s32 ok;
    u16 anim;
    s32 r;
    s16 rx, ry;
    s16 r2;
    f32 dx, dy;
    f32 frame;
    f32 v;
    f32 ny;
    f32 vv1;
    f32 vv;
    f32 v1, ny1, v3, v5, frame5, frame2, frame6;
    omObjData* o7;
    f32 lim;
    f32 acc;
    f32 ang;
    f32 px;

    x = obj->trans.x;
    y = obj->trans.y;
    z = obj->trans.z;
    func_800DDD70_minigame(obj);
    mdl = obj->model[0];
    vy0 = w->unk_38;
    D_800EBE2C_minigame = D_800EC5D8_minigame = mag;
    D_800EC288_minigame = 0;
    *(s8*)&w->unk_55 = -1; /* s8 here (MP1 s8; collision.h u8) */
    D_800EC286_minigame = -1;
    if (w->unk_104[0] != 0) {
        ((void (*)(omObjData*))w->unk_104[0])(obj);
    }
    if (func_800E6E8C_minigame() == 2 && (s8)port >= 0 && !(w->unk_50 & 1)) {
        sx = D_800CBB6E_main[(s8)port];
        sy = D_800D20A1_main[(s8)port];
        if (sx > 60) {
            sx = 60;
        }
        if (sy > 60) {
            sy = 60;
        }
        if (sx < -60) {
            sx = -60;
        }
        if (sy < -60) {
            sy = -60;
        }
        func_800E2308_minigame(&sx, &sy);
        if (!(w->unk_50 & 6)) {
            trg = D_800D5558_main[(s8)port];
            btn = D_800CDA7C_main[(s8)port];
        } else {
            btn = 0;
            trg = 0;
        }
    } else {
        sx = sy = 0;
        btn = 0;
        trg = 0;
    }
    flags = func_800E4A90_minigame(obj);
    if (flags & 1) {
        ok = 1;
        if (w->unk_38 == 1000.0f) {
            if (func_800D972C_minigame(obj, w->unk_3C, x, y, z) != 65536.0f && (trg & 0x8000)) {
                func_800E3820_minigame(obj, w);
                ok = 0;
            }
        } else {
            v1 = w->unk_38;
            if (v1 > D_800EB774_minigame) {
                v1 = D_800EB774_minigame;
            }
            vv1 = v1 * v1;
            ny1 = y + vv1 * ((w->unk_38 >= 0.0f) ? -35.0f : 35.0f);
            w->unk_38 += D_800EB748_minigame;
            if (func_800E5690_minigame(obj, 6) == 1) {
                func_800E19FC_minigame(w, 3);
                ok = 0;
            }
            y = func_800D9028_minigame(obj, x, ny1, z, y);
            if (w->unk_38 == 1000.0f) {
                o = D_800EC1C0_minigame[w->unk_53];
                if (((GroundWork*)o->data)->unk_03 == 2) {
                    func_800DFD9C_minigame(obj, x, o->trans.y, z);
                }
            }
        }
        if (ok == 1) {
            func_800E5690_minigame(obj, 0);
        }
        w->unk_C6 = 0;
    } else if (flags & 0x100000) {
        w->unk_C0--;
        if (w->unk_C0 == 0) {
            func_800E5690_minigame(obj, 0x13);
        }
        if (w->unk_C0 - 52 < 0) {
            w->unk_40 = D_800EB770_minigame;
            obj->rot.y = 0.0f;
        } else {
            obj->rot.y = func_800202A8_main(w->unk_C0 * 45.0f);
            if (w->unk_40 < D_800EB770_minigame) {
                w->unk_40 += D_800EB740_minigame * 0.2f;
                if (D_800EB770_minigame <= w->unk_40) {
                    w->unk_40 = D_800EB770_minigame;
                }
            } else if (D_800EB770_minigame <= w->unk_40) {
                w->unk_40 += -D_800EB740_minigame * 0.2f;
                if (w->unk_40 <= D_800EB770_minigame) {
                    w->unk_40 = D_800EB770_minigame;
                }
            }
        }
        ny = func_800D972C_minigame(obj, w->unk_3C, x, y, z);
        if (ny != 65536.0f) {
            y = ny;
        }
    } else if (flags & 0x18C18) {
        if (flags & 0x10000) {
            if (trg & 0x8000) {
                func_800E3820_minigame(obj, w);
            }
        } else if (w->unk_40 == D_800EB770_minigame) {
            if (flags & 0x400) {
                func_800E5690_minigame(obj, 0x21);
            } else if (flags & 0x10) {
                func_800E5690_minigame(obj, 0x12);
            } else if (flags & 0x800) {
                func_800E5690_minigame(obj, 0x22);
            } else if (flags & 8) {
                func_800E5690_minigame(obj, 0x13);
            } else {
                func_800E5690_minigame(obj, 0);
            }
        } else if (w->unk_40 < D_800EB770_minigame) {
            w->unk_40 += D_800EB740_minigame * 2.0f;
            if (D_800EB770_minigame <= w->unk_40) {
                w->unk_40 = D_800EB770_minigame;
            }
        } else if (D_800EB770_minigame <= w->unk_40) {
            w->unk_40 += -D_800EB740_minigame * 2.0f;
            if (w->unk_40 <= D_800EB770_minigame) {
                w->unk_40 = D_800EB770_minigame;
            }
        }
        v3 = w->unk_38;
        if (v3 == 1000.0f) {
            if (flags & 0x10) {
                if (w->unk_40 > D_800EB760_minigame) {
                    w->unk_3C += -(f32)sx / D_800EB750_minigame;
                } else {
                    lim = (w->unk_40 <= D_800EB76C_minigame) ? D_800EB76C_minigame : w->unk_40;
                    w->unk_3C += -(sx / D_800EB750_minigame) * (lim / D_800EB760_minigame);
                }
            }
            goto ground;
        } else {
            if (v3 > D_800EB774_minigame) {
                v3 = D_800EB774_minigame;
            }
            vv = v3 * v3;
            ny = y + vv * ((w->unk_38 >= 0.0f) ? -35.0f : 35.0f);
            w->unk_38 += D_800EB748_minigame;
            y = func_800D9028_minigame(obj, x, ny, z, y);
            if (w->unk_38 != 1000.0f) {
            } else {
                o = D_800EC1C0_minigame[w->unk_53];
                if (((GroundWork*)o->data)->unk_03 == 2) {
                    func_800DFD9C_minigame(obj, x, o->trans.y, z);
                } else if (flags & 0x10) {
                    func_800E5690_minigame(obj, 0x12);
                } else if (flags & 8) {
                    func_800E5690_minigame(obj, 0x13);
                } else if (flags & 0xC00) {
                } else {
                    func_800E5690_minigame(obj, 0);
                }
            }
        }
        w->unk_C6 = 0;
    } else if (flags & 0x6000) {
        func_800E2250_minigame(obj, sx, sy);
        frame = func_8001C7D0_main(mdl);
        if (frame == -1.0f) {
            frame = HmfModelData[(s16)mdl].unk40;
        }
        if (flags & 0x4000) {
            w->unk_3C += 25.0f;
            if (frame >= 14.0f) {
                func_800E5690_minigame(obj, 1);
                w->unk_40 = D_800EB76C_minigame;
                func_800E19FC_minigame(w, 1);
            }
        } else if (frame >= 10.0f) {
            if (abs(sx) >= 9 || abs(sy) >= 9) {
                if (w->unk_40 < D_800EB76C_minigame) {
                    if (func_800E2ED4_minigame(sx, -sy, sindf(w->unk_3C), cosdf(w->unk_3C)) < 0.0f) {
                        func_800E5690_minigame(obj, 0x20);
                    }
                }
            }
            if (frame >= 15.0f && w->unk_40 < D_800EB76C_minigame) {
                if (abs(sx) >= 9 || abs(sy) >= 9) {
                    if (w->unk_40 < D_800EB76C_minigame) {
                        if (func_800E2ED4_minigame(sx, -sy, sindf(w->unk_3C), cosdf(w->unk_3C)) < 0.0f) {
                            func_800E5690_minigame(obj, 0x20);
                        } else {
                            func_800E5690_minigame(obj, 2);
                            w->unk_40 = D_800EB764_minigame;
                            func_800E19FC_minigame(w, 1);
                        }
                    }
                } else {
                    func_800E5690_minigame(obj, 0);
                }
            }
        }
        if (w->unk_53 >= 0) {
            acc = ((GroundWork*)D_800EC1C0_minigame[w->unk_53]->data)->unk_08;
        } else {
            acc = D_800EB740_minigame;
        }
        acc *= 2.0f;
        if (w->unk_40 < D_800EB770_minigame) {
            w->unk_40 = acc + w->unk_40;
            if (D_800EB770_minigame <= w->unk_40) {
                w->unk_40 = D_800EB770_minigame;
            }
        } else if (D_800EB770_minigame <= w->unk_40) {
            w->unk_40 = w->unk_40 - acc;
            if (w->unk_40 <= D_800EB770_minigame) {
                w->unk_40 = D_800EB770_minigame;
            }
        }
        ny = func_800D972C_minigame(obj, w->unk_3C, x, y, z);
        if (ny != 65536.0f) {
            y = ny;
            if (trg & 0x8000) {
                func_800E3820_minigame(obj, w);
            } else if (trg & 0x4000) {
                func_800E38A4_minigame(obj, w);
                func_800E23E0_minigame(obj);
            }
        }
        w->unk_C6 = 0;
    } else if (flags & 0x320) {
        frame2 = func_8001C7D0_main(mdl);
        if (frame2 == -1.0f) {
            frame2 = HmfModelData[(s16)mdl].unk40;
        }
        v = w->unk_38;
        if (!(flags & 0x300)) {
            if (((frame2 > 5.0f) & (frame2 < 7.0f)) && !(btn & 0x8000)) {
                if (!(w->unk_50 & 8) & (v < 0.0f)) {
                    w->unk_38 = -D_800EB744_minigame * 0.2f;
                }
            }
            if (abs(sx) >= 9 || abs(sy) >= 9) {
                D_800EBE2C_minigame = sx / D_800EB74C_minigame * w->unk_B4;
                D_800EC5D8_minigame = -(f32)sy / D_800EB74C_minigame * w->unk_B4;
                mag = HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame);
                ang = atan2df(D_800EBE2C_minigame, D_800EC5D8_minigame) + w->unk_60;
                D_800EBE2C_minigame = sindf(ang) * mag;
                D_800EC5D8_minigame = cosdf(ang) * mag;
                if (w->unk_50 & 8) {
                    D_800EBE2C_minigame *= 0.2f;
                    D_800EC5D8_minigame *= 0.2f;
                }
            }
            if (trg & 0x4000) {
                func_800E3D3C_minigame(obj, w);
            }
            if ((trg & 0x2000) && !(w->unk_50 & 8)) {
                func_800E3AB8_minigame(obj, w);
            }
            if (v > D_800EB774_minigame) {
                v = D_800EB774_minigame;
            }
            ny = y + v * v * ((w->unk_38 >= 0.0f) ? -35.0f : 35.0f);
            w->unk_38 += D_800EB748_minigame;
        } else {
            if (v > D_800EB774_minigame) {
                v = D_800EB774_minigame;
            }
            if (frame2 > 26.0f) {
                ny = y + v * v * ((w->unk_38 >= 0.0f) ? -35.0f : 35.0f);
                w->unk_38 += D_800EB748_minigame * 2.0f;
            } else if (flags & 0x100) {
                ny = y + v * v * ((w->unk_38 >= 0.0f) ? -35.0f : 35.0f);
                w->unk_38 += D_800EB748_minigame / 2.0f;
            } else {
                ny = y;
            }
            if (flags & 0x100) {
                func_800E3E24_minigame(obj, x, ny, z);
            }
        }
        y = func_800D9028_minigame(obj, x, ny, z, y);
        if (w->unk_38 != 1000.0f) {
        } else {
            o = D_800EC1C0_minigame[w->unk_53];
            g = o->data;
            if (g->unk_03 == 2) {
                func_800DFD9C_minigame(obj, x, o->trans.y, z);
            } else if (flags & 0x200) {
                if (!(w->unk_50 & 0x80) && w->unk_BE == 0) {
                    func_800E3B98_minigame(obj, w, g, x, y, z);
                } else {
                    func_800E3CA0_minigame(obj, w, g, x, y, z);
                }
            } else {
                func_800E39CC_minigame(obj, w, g, sx, sy);
            }
        }
        w->unk_C6 = 0;
    } else if (flags & 0xC0) {
        func_800E3F44_minigame(obj, flags, x, y, z);
        if (w->unk_38 == 1000.0f) {
            if (w->unk_40 < D_800EB770_minigame) {
                w->unk_40 += D_800EB740_minigame * 2.0f;
                if (D_800EB770_minigame < w->unk_40) {
                    w->unk_40 = D_800EB770_minigame;
                }
            } else if (D_800EB770_minigame < w->unk_40) {
                w->unk_40 += -D_800EB740_minigame * 2.0f;
                if (w->unk_40 < D_800EB770_minigame) {
                    w->unk_40 = D_800EB770_minigame;
                }
            }
        ground:
            ny = func_800D972C_minigame(obj, w->unk_3C, x, y, z);
            if (ny != 65536.0f) {
                y = ny;
            }
        } else {
            v5 = w->unk_38;
            if (v5 > D_800EB774_minigame) {
                v5 = D_800EB774_minigame;
            }
            frame5 = func_8001C7D0_main(mdl);
            if (frame5 == -1.0f) {
                frame5 = HmfModelData[(s16)mdl].unk40;
            }
            ny = y + v5 * v5 * ((w->unk_38 >= 0.0f) ? -35.0f : 35.0f);
            if (frame5 > 30.0f) {
                w->unk_38 += D_800EB748_minigame * 2.0f;
            } else {
                w->unk_38 += D_800EB748_minigame / 2.0f;
            }
            y = func_800D9028_minigame(obj, x, ny, z, y);
            if (w->unk_38 != 1000.0f) {
            } else {
                o = D_800EC1C0_minigame[w->unk_53];
                if (((GroundWork*)o->data)->unk_03 == 2) {
                    func_800DFD9C_minigame(obj, x, o->trans.y, z);
                } else if (abs(sx) < 8 && abs(sy) < 8) {
                    w->unk_40 = D_800EB770_minigame;
                    func_800E5690_minigame(obj, 0x15);
                    func_800E19FC_minigame(w, 4);
                } else {
                    func_800E5690_minigame(obj, 1);
                    w->unk_40 = D_800EB768_minigame;
                    func_800E19FC_minigame(w, 1);
                }
            }
        }
        w->unk_C6 = 0;
    } else if (flags & 6) {
        r = func_800E2250_minigame(obj, sx, sy);
        rx = r >> 16;
        ry = r;
        mag = HuSqrtf(rx * rx + ry * ry) / D_800EB75C_minigame;
        if (w->unk_53 >= 0) {
            gr = D_800EC1C0_minigame[w->unk_53]->data;
            if (gr->unk_0C != 0.0f) {
                w->unk_40 += mag / gr->unk_0C;
            } else {
                w->unk_40 += mag / D_800EB73C_minigame;
            }
            if (sx | sy) {
                w->unk_40 = w->unk_40 - gr->unk_08;
            } else {
                w->unk_40 = -gr->unk_08 * 3.0f + w->unk_40;
            }
        } else {
            w->unk_40 += mag / D_800EB73C_minigame;
            if (sx | sy) {
                w->unk_40 = w->unk_40 - D_800EB740_minigame;
            } else {
                w->unk_40 = -D_800EB740_minigame * 3.0f + w->unk_40;
            }
        }
        mag = func_800DFD48_minigame(mag);
        if (w->unk_40 > mag) {
            w->unk_40 = mag;
        }
        if (w->unk_40 < D_800EB770_minigame) {
            w->unk_40 = D_800EB770_minigame;
        }
        if (abs(rx) >= 9 || abs(ry) >= 9) {
            w->unk_3C = atan2df(rx, -ry) + w->unk_60;
        }
        ny = func_800D972C_minigame(obj, w->unk_3C, x, y, z);
        if (ny != 65536.0f) {
            y = ny;
            if (!(func_800E4A90_minigame(obj) & 0xC00)) {
                if (trg & 0x8000) {
                    func_800E3820_minigame(obj, w);
                } else if (trg & 0x4000) {
                    func_800E38A4_minigame(obj, w);
                } else if (dx = sx - rx, dy = sy - ry, HuSqrtf(dx * dx + dy * dy) > 65.0f) {
                    if (fabs(w->unk_40) >= D_800EB764_minigame) {
                        func_800E5690_minigame(obj, 0x11);
                        w->unk_40 = D_800EB768_minigame;
                        func_800E19FC_minigame(w, 2);
                        px = x + sindf(w->unk_3C) * 70.0f;
                        func_800E4C88_minigame(obj, 4, px, y, z + cosdf(w->unk_3C) * 70.0f, 0.0f, w->unk_3C + 180.0f);
                    }
                } else if (HuSqrtf(rx * rx + ry * ry) > 43.0f && abs(sx) < 8 && abs(sy) < 8) {
                    if (fabs(w->unk_40) >= D_800EB764_minigame) {
                        func_800E5690_minigame(obj, 0x11);
                        w->unk_40 = D_800EB768_minigame;
                        func_800E19FC_minigame(w, 2);
                        px = x + sindf(w->unk_3C) * 70.0f;
                        func_800E4C88_minigame(obj, 4, px, y, z + cosdf(w->unk_3C) * 70.0f, 0.0f, w->unk_3C + 180.0f);
                    }
                } else if (w->unk_40 == D_800EB770_minigame) {
                    w->unk_C6 = 0;
                    func_800E5690_minigame(obj, 0);
                    if (w->unk_C4 > 0) {
                        if (w->unk_C5 > 0) {
                            HuAudFXStop(w->unk_C5);
                        }
                        w->unk_C4 = -1;
                    }
                } else if (mag > D_800EB764_minigame) {
                    anim = 2;
                    r2 = func_800E240C_minigame(w->unk_59, 12, sx, sy);
                    if (r2 > 0) {
                        w->unk_C6++;
                        if (w->unk_C6 >= 0) {
                            if (w->unk_C6 >= 13) {
                                w->unk_C6 = 12;
                                anim = 4;
                            }
                        }
                    } else if (r2 < 0) {
                        w->unk_C6--;
                        if (w->unk_C6 < 0) {
                            if (w->unk_C6 < -12) {
                                w->unk_C6 = -12;
                                anim = 3;
                            }
                        }
                    } else {
                        w->unk_C6 = 0;
                    }
                    if (func_800E5690_minigame(obj, anim) == 1) {
                        func_800E1A9C_minigame(w, 1);
                    } else {
                        frame6 = func_8001C7D0_main(mdl);
                        if (frame6 == -1.0f) {
                            frame6 = HmfModelData[(s16)mdl].unk40;
                        }
                        if (frame6 == 0.0f) {
                            func_800E1A9C_minigame(w, 1);
                        }
                    }
                    if (w->unk_BC < 60) {
                        px = x - sindf(w->unk_3C) * 20.0f;
                        func_800E4C88_minigame(obj, 3, px, y, z - cosdf(w->unk_3C) * 20.0f, 0.0f, w->unk_3C);
                    }
                    w->unk_BC++;
                    if (w->unk_BC > 200) {
                        w->unk_BC = 200;
                    }
                    if (w->unk_90 > D_800EB768_minigame || w->unk_98 > D_800EB768_minigame) {
                        px = x - sindf(w->unk_3C) * 20.0f;
                        func_800E4C88_minigame(obj, 3, px, y, z - cosdf(w->unk_3C) * 20.0f, 0.0f, w->unk_3C);
                    }
                } else {
                    w->unk_C6 = 0;
                    if (func_800E5690_minigame(obj, 1) == 1) {
                        func_800E1A9C_minigame(w, 0);
                    } else {
                        frame6 = func_8001C7D0_main(mdl);
                        if (frame6 == -1.0f) {
                            frame6 = HmfModelData[(s16)mdl].unk40;
                        }
                        if (frame6 == 0.0f) {
                            func_800E1A9C_minigame(w, 0);
                        }
                    }
                    w->unk_BC = 0;
                }
            }
        }
    } else if (flags & 0x20000) {
        o7 = D_800EC1C0_minigame[w->unk_53];
        y -= 20.0f;
        if (y < o7->trans.y - 75.0f) {
            y = o7->trans.y - 75.0f;
        }
        if (w->unk_40 > D_800EB770_minigame) {
            w->unk_40 -= D_800EB740_minigame;
            if (w->unk_40 <= D_800EB770_minigame) {
                w->unk_40 = D_800EB770_minigame;
            }
        } else if (w->unk_40 < D_800EB770_minigame) {
            w->unk_40 += D_800EB740_minigame;
            if (D_800EB770_minigame <= w->unk_40) {
                w->unk_40 = D_800EB770_minigame;
            }
        }
        if (obj->model[2] != 0) {
            Hu3DModelPosSet(obj->model[2], x, o7->trans.y - 64.0f, z);
            Hu3DModelScaleSet(obj->model[2], 6.0f, 6.0f, 6.0f);
        }
    } else if (flags & 0xC0000) {
        if (flags & 0x40000) {
            func_800E3FD8_minigame(obj, x, y, z);
        } else {
            func_800E4248_minigame(obj, x, y, z);
        }
        if (w->unk_40 < D_800EB770_minigame) {
            w->unk_40 += D_800EB740_minigame * 2.0f;
            if (D_800EB770_minigame < w->unk_40) {
                w->unk_40 = D_800EB770_minigame;
            }
        } else if (D_800EB770_minigame < w->unk_40) {
            w->unk_40 += -D_800EB740_minigame * 2.0f;
            if (w->unk_40 < D_800EB770_minigame) {
                w->unk_40 = D_800EB770_minigame;
            }
        }
        ny = func_800D972C_minigame(obj, w->unk_3C, x, y, z);
        if (ny != 65536.0f) {
            y = ny;
        }
    } else if (flags & 0x1000) {
        w->unk_40 = D_800EB770_minigame;
    } else if (flags & 0x200000) {
        if (w->unk_104[20] != 0) {
            ((void (*)(omObjData*, f32*, f32*, f32*))w->unk_104[20])(obj, &x, &y, &z);
        }
    }
    mag = w->unk_40;
    if (w->unk_50 & 6) {
        mag *= 0.6f;
    }
    mag *= (vy0 != 1000.0f) ? w->unk_4C * w->unk_B4 : w->unk_B4;
    x += sindf(w->unk_3C) * mag + D_800EBE2C_minigame;
    z += cosdf(w->unk_3C) * mag + D_800EC5D8_minigame;
    func_80088910_main((f32 (*)[4])HmfModelData[obj->model[0]].mtx, 0.0f, w->unk_3C, 0.0f);
    func_800E17D4_minigame(obj, x, y, z);
    if (w->unk_104[1] != 0) {
        ((void (*)(omObjData*))w->unk_104[1])(obj);
    }
    func_800E4E30_minigame(obj);
    func_800E5138_minigame(obj);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDD94_minigame);
#endif



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

/* Motion 0x10 on a type-2 ground object; puts model[2] at (x, y, z). */
void func_800DFD9C_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    MgWork* w = obj->data;
    u8 slot;

    func_800E5690_minigame(obj, 0x10);
    slot = ((u8*)w->unk_20)[3]; /* 0x23, in MgWork.unk_20 padding: an effect slot */
    func_80014850_main(slot);
    func_800146DC_main(slot, 4, 4);
    Hu3DModelPosSet(obj->model[2], x, y, z);
    w->unk_40 = D_800EB770_minigame;
    func_800E1810_minigame();
}

/* Between motion frames 28 and 29 the held item is thrown. */
void func_800DFE44_minigame(omObjData* obj) {
    MgWork* w = obj->data;
    f32 frame = func_8001C7D0_main(obj->model[0]);
    s32 a, b;

    if (frame == -1.0f) {
        frame = HmfModelData[obj->model[0]].unk40;
    }
    a = !(frame >= 28.0f) ? 0 : 1;
    b = !(frame <= 29.0f) ? 0 : 1;
    if (a & b) {
        func_800E2CA4_minigame(obj, (w->unk_40 + D_800EB768_minigame) * w->unk_CC);
    }
}

/* A player's attack (motion frames 16-20) against the other players and the item actors, then a
   wall push for the attack point. */
void func_800DFF3C_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    Vec4f v;
    MgWork* w = obj->data;
    MgWork* ow;
    ColActorWork* aw;
    omObjData* o;
    f32 frame;
    f32 rot;
    f32 len;
    f32 nx, ny, nz;
    f32 dx, dy, dz;
    f32 ang;
    u16 i;

    frame = func_8001C7D0_main(*obj->model);
    if (frame == -1.0f) {
        frame = HmfModelData[*obj->model].unk40;
    }
    if ((frame < 16.0f) | (frame > 20.0f)) {
        return;
    }
    if (w->unk_BE != 0) {
        D_800EC288_minigame++;
        return;
    }
    if (w->unk_50 & 0x400) {
        return;
    }
    len = w->unk_64 + w->unk_48;
    rot = w->unk_3C;
    nx = x + sindf(rot) * len;
    ny = y;
    nz = z + cosdf(rot) * len;
    w->unk_F0 = 1;
    for (i = 0; i < D_800EC280_minigame; i++) {
        o = D_800EC598_minigame[i];
        ow = o->data;
        if (!(ow->unk_5C & 0x8C00) && !(ow->unk_50 & 7) && ow->unk_BE == 0 && !(ow->unk_50 & 0x400)) {
            if (w == ow) {
                continue;
            }
            if (func_800E4510_minigame(obj, o) != 1) {
                continue;
            }
            dx = o->trans.x - nx;
            dy = o->trans.y - ny;
            dz = o->trans.z - nz;
            if (HuSqrtf(dx * dx + dy * dy + dz * dz) < ow->unk_48 + 30.0f) {
                func_800E454C_minigame(obj, o, dx, dz, i);
            }
        }
    }
    if (!(w->unk_50 & 0x17)) {
        for (i = 0; i < D_800EC1B8_minigame; i++) {
            o = D_800EBE70_minigame[i];
            aw = o->data;
            if (!(aw->unk_50 & 0x20)) {
                continue;
            }
            if (!(aw->unk_50 & 0x10)) {
                if (w->unk_BE != 0) {
                    D_800EC288_minigame++;
                } else {
                    dx = o->trans.x - nx;
                    dy = o->trans.y - ny;
                    dz = o->trans.z - nz;
                    len = HuSqrtf(dx * dx + dy * dy + dz * dz) - (aw->unk_48 + w->unk_48);
                    if (len < 0.0f && (w->unk_EC == NULL || w->unk_EC(obj, o) != 1)) {
                        func_800E2DA4_minigame(obj, o);
                    }
                }
            }
        }
    }
    v.x = sindf(rot) * w->unk_48 + obj->trans.x;
    v.y = ny;
    v.z = cosdf(rot) * w->unk_48 + obj->trans.z;
    v.w = w->unk_64;
    w->unk_55 = func_800DD530_minigame(obj, &v, -D_800EB760_minigame);
    if (D_800EB736_minigame != 0 && func_800E1510_minigame(D_800EC286_minigame) == 1) {
        ang = atan2df(D_800EBEB8_minigame[0].x - obj->trans.x, D_800EBEB8_minigame[0].z - obj->trans.z);
        func_800E4C88_minigame(obj, 6, nx, ny, nz, 0.0f, ang + 180.0f);
    }
    D_800EB736_minigame = 0;
    D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
}

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

/* Movement tuning debug menu for port 0 (MP2 func_80009E48_AA48): C buttons turn and zoom the
   camera, L/R pick a row (only row 0 is reachable), A/B toggle the homing camera or step the
   selected value. Retail bug: w is only set by the loops in rows 9 and 10, so the homing camera
   writes through an unset pointer (host hazard). */
void func_800E04C8_minigame(omObjData* obj, s32 port) {
    MgWork* w;
    s32 i;
    f32 cy;

    if (port != 0) {
        return;
    }
    if (D_800CDA7C_main[port] & 0x10) {
        CZoom -= 20.0f;
    }
    if (D_800CDA7C_main[port] & 0x20) {
        CZoom += 20.0f;
    }
    if (D_800CDA7C_main[port] & 8) {
        CRot.x += 0.3f;
    }
    if (D_800CDA7C_main[port] & 4) {
        CRot.x -= 0.3f;
    }
    if (D_800CDA7C_main[port] & 1) {
        CRot.y += 1.0f;
    }
    if (D_800CDA7C_main[port] & 2) {
        CRot.y -= 1.0f;
    }
    if (D_800D5558_main[port] & 0x800) {
        D_800EB780_minigame--;
    } else if (D_800D5558_main[port] & 0x400) {
        D_800EB780_minigame++;
    }
    if (D_800EB780_minigame < 0) {
        D_800EB780_minigame = 0;
    }
    if (D_800EB780_minigame > 0) {
        D_800EB780_minigame = 0;
    }
    switch (D_800EB780_minigame) {
        case 0:
            if (D_800D5558_main[port] & 0x300) {
                if (D_800EB73B_minigame != 0) {
                    D_800EB73B_minigame = 0;
                } else {
                    D_800EB73B_minigame = 1;
                }
            }
            break;
        case 2:
            if (D_800CDA7C_main[port] & 0x100) {
                D_800EB73C_minigame += 0.1f;
            }
            if (D_800CDA7C_main[port] & 0x200) {
                D_800EB73C_minigame -= 0.1f;
            }
            if (D_800EB73C_minigame > 50.0f) {
                D_800EB73C_minigame = 50.0f;
            }
            if (D_800EB73C_minigame < 1.0f) {
                D_800EB73C_minigame = 1.0f;
            }
            break;
        case 3:
            if (D_800CDA7C_main[port] & 0x100) {
                D_800EB740_minigame += 0.001f;
            }
            if (D_800CDA7C_main[port] & 0x200) {
                D_800EB740_minigame -= 0.001f;
            }
            if (D_800EB740_minigame > 0.999f) {
                D_800EB740_minigame = 0.999f;
            }
            if (D_800EB740_minigame < 0.001f) {
                D_800EB740_minigame = 0.001f;
            }
            break;
        case 4:
            if (D_800CDA7C_main[port] & 0x100) {
                D_800EB744_minigame += 0.01f;
            }
            if (D_800CDA7C_main[port] & 0x200) {
                D_800EB744_minigame -= 0.01f;
            }
            if (D_800EB744_minigame > 2.0f) {
                D_800EB744_minigame = 2.0f;
            }
            if (D_800EB744_minigame < 0.7f) {
                D_800EB744_minigame = 0.7f;
            }
            break;
        case 5:
            if (D_800CDA7C_main[port] & 0x100) {
                D_800EB748_minigame += 0.001f;
            }
            if (D_800CDA7C_main[port] & 0x200) {
                D_800EB748_minigame -= 0.001f;
            }
            if (D_800EB748_minigame > 0.2f) {
                D_800EB748_minigame = 0.2f;
            }
            if (D_800EB748_minigame < 0.01f) {
                D_800EB748_minigame = 0.01f;
            }
            break;
        case 6:
            if (D_800CDA7C_main[port] & 0x100) {
                D_800EB74C_minigame += 0.1f;
            }
            if (D_800CDA7C_main[port] & 0x200) {
                D_800EB74C_minigame -= 0.1f;
            }
            if (D_800EB74C_minigame > 30.0f) {
                D_800EB74C_minigame = 30.0f;
            }
            if (D_800EB74C_minigame < 0.0f) {
                D_800EB74C_minigame = 0.0f;
            }
            break;
        case 7:
            if (D_800CDA7C_main[port] & 0x100) {
                D_800EB750_minigame += 0.1f;
            }
            if (D_800CDA7C_main[port] & 0x200) {
                D_800EB750_minigame -= 0.1f;
            }
            if (D_800EB750_minigame > 100.0f) {
                D_800EB750_minigame = 100.0f;
            }
            if (D_800EB750_minigame < 20.0f) {
                D_800EB750_minigame = 20.0f;
            }
            break;
        case 8:
            if (D_800CDA7C_main[port] & 0x100) {
                D_800EB760_minigame += 0.1f;
            }
            if (D_800CDA7C_main[port] & 0x200) {
                D_800EB760_minigame -= 0.1f;
            }
            if (D_800EB760_minigame > 30.0f) {
                D_800EB760_minigame = 30.0f;
            }
            if (D_800EB760_minigame < 10.0f) {
                D_800EB760_minigame = 10.0f;
            }
            D_800EB76C_minigame = D_800EB760_minigame / 4.0f;
            D_800EB768_minigame = D_800EB760_minigame / 2.0f;
            D_800EB764_minigame = D_800EB76C_minigame * 3.0f;
            D_800EB75C_minigame = 60.0f / D_800EB760_minigame;
            break;
        case 9:
            if (D_800CDA7C_main[port] & 0x100) {
                D_800EB754_minigame += 0.1f;
            }
            if (D_800CDA7C_main[port] & 0x200) {
                D_800EB754_minigame -= 0.1f;
            }
            if (D_800EB754_minigame > 100.0f) {
                D_800EB754_minigame = 100.0f;
            }
            if (D_800EB754_minigame < 40.0f) {
                D_800EB754_minigame = 40.0f;
            }
            for (i = 0; i < D_800EC280_minigame; i++) {
                w = D_800EC598_minigame[i]->data;
                w->unk_48 = D_800EB754_minigame;
            }
            break;
        case 10:
            if (D_800CDA7C_main[port] & 0x100) {
                D_800EB758_minigame += 0.1f;
            }
            if (D_800CDA7C_main[port] & 0x200) {
                D_800EB758_minigame -= 0.1f;
            }
            if (D_800EB758_minigame > 100.0f) {
                D_800EB758_minigame = 100.0f;
            }
            if (D_800EB758_minigame < 10.0f) {
                D_800EB758_minigame = 40.0f;
            }
            for (i = 0; i < D_800EC280_minigame; i++) {
                w = D_800EC598_minigame[i]->data;
                w->unk_64 = D_800EB758_minigame;
            }
            break;
    }
    fontcolor = 15;
    sprintf(D_800D5218_main, "*");
    print8(16, (D_800EB780_minigame + 2) * 8, D_800D5218_main);
    sprintf(D_800D5218_main, "CAMERA :[%s]", D_800EB73B_minigame ? "HOMING" : "LOCK");
    print8(24, 16, D_800D5218_main);
    if (D_800EB73B_minigame != 0) {
        cy = HmfModelData[obj->model[1]].pos.y;
        if (cy != Center.y) {
            cy = Center.y + (cy - Center.y) / 20.0f;
        }
        Center.x = HmfModelData[obj->model[1]].pos.x;
        Center.y = cy;
        Center.z = HmfModelData[obj->model[1]].pos.z;
        w->unk_60 = CRot.y;
    }
}

