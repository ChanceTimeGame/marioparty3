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
    /* 0x5A */ char unk_5A[0x5A];
    /* 0xB4 */ f32 unk_B4;  /* speed factor */
} MgWork; /* size 0x15C (MP2) */

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
