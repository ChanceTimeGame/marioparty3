#include "common.h"

/* Minigame player collision against the ground objects and their faces: MP2 src/1130.c
   func_80002040_2C40 .. func_800062F0_6EF0 (MP1 src/1130.c func_80000530 ..). Layouts re-derived
   from the MP3 asm. */

typedef struct ColVtx {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} ColVtx;

typedef struct ColTri {
    /* 0x0 */ s16 flags; /* bits 14-15: vertex count - 2, bits 8-13: surface type */
    /* 0x2 */ s16 v[3];
} ColTri;

/* main 20A20.c's polygon query list (func_80021C14_main / func_80022198_main) */
typedef struct HitList {
    /* 0x00 */ u16** list;
    /* 0x04 */ u16 count;
    /* 0x06 */ u16 pos;
} HitList;

typedef struct HitProbe {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 r;
} HitProbe;

typedef struct Vec4f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ f32 w; /* radius */
} Vec4f;

/* A HitProbe followed by a second position: func_800D7C14_minigame's probe and save locals, which
   retail reads as one block (host hazard: two separate locals). */
typedef struct ColSphere {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 r;
    /* 0x10 */ f32 x2;
    /* 0x14 */ f32 y2;
    /* 0x18 */ f32 z2;
} ColSphere;

/* omObjData::data of a ground / platform object (D_800EC1C0_minigame[]) */
typedef struct GroundWork {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;  /* surface id copied to MgWork.unk_56 */
    /* 0x05 */ char unk_05;
    /* 0x06 */ u16 unk_06; /* flags: 2 skip, 4 test the part list, 8/0x10/0x20/0x40 primitive
                              shapes, 0x50 needs func_800E30B8_minigame, 0x400 tilts the rider */
    /* 0x08 */ f32 unk_08; /* friction */
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10; /* conveyor factor applied to the floor normal */
    /* 0x14 */ f32 unk_14; /* top surface height */
    /* 0x18 */ char unk_18[0x80];
    /* 0x98 */ f32 unk_98; /* subtracted from unk_14 for a player's ceiling test */
    /* 0x9C */ f32 unk_9C; /* cylinder radius (shapes 0x20, 0x40) */
    /* 0xA0 */ f32 unk_A0; /* box min x (shape 8) */
    /* 0xA4 */ f32 unk_A4; /* box min z */
    /* 0xA8 */ f32 unk_A8; /* box max x */
    /* 0xAC */ f32 unk_AC; /* box max z */
} GroundWork; /* size unknown */

/* omObjData::data of a minigame player (MP2 MgWork; only the fields this unit reads are named) */
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

/* omObjData::data of an item actor (A96F0.c), 0xAC bytes */
typedef struct ColActorWork {
    /* 0x00 */ u8 unk_00[0x20];
    /* 0x20 */ char unk_20[4];
    /* 0x24 */ u8 unk_24;
    /* 0x25 */ char unk_25[0xF];
    /* 0x34 */ f32 unk_34;      /* height */
    /* 0x38 */ f32 unk_38;      /* vertical speed; 1000.0f on the ground */
    /* 0x3C */ f32 unk_3C;      /* heading (degrees) */
    /* 0x40 */ f32 unk_40;      /* speed */
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;      /* radius */
    /* 0x4C */ char unk_4C[4];
    /* 0x50 */ u16 unk_50;      /* flags */
    /* 0x52 */ u8 unk_52;       /* kind (7: hazard) */
    /* 0x53 */ s8 unk_53;
    /* 0x54 */ u8 unk_54;       /* active */
    /* 0x55 */ char unk_55[0x57];
} ColActorWork; /* size = 0xAC */

f32 func_800D8640_minigame(omObjData* g, MgWork* w, f32 y);
f32 func_800D8778_minigame(omObjData* g, MgWork* w, f32 h, f32 y, Vec* n);
f32 func_800D8818_minigame(f32 x, f32 y, f32 z, ColVtx* verts, ColTri* tri, Vec* dir, Vec* out);
f32 func_800D89CC_minigame(omObjData* obj, f32 x, f32 y, f32 z, Vec* n);
f32 func_800D9F10_minigame(omObjData* obj, f32 y);
s32 func_800D9F3C_minigame(Vec* pos, ColTri* tri, ColVtx* verts);
s32 func_800DA054_minigame(Vec4f* s, s16* tri, ColVtx* verts);
f32 func_800DA204_minigame(f32 x, f32 y, f32 z, ColVtx* a, ColVtx* b, Vec* n);
s32 func_800DA2E0_minigame(Vec* p, s16* idx, ColVtx* verts, Vec* n);
s32 func_800DA540_minigame(Vec* p, ColTri* tri, ColVtx* verts);
s32 func_800DA768_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800DB628_minigame(omObjData* obj);
s32 func_800DB704_minigame(s32 n, u16* idx, ColVtx* verts, HitProbe* probe);
s32 func_800DB724_minigame(s32 n, s16* idx, ColVtx* verts, HitProbe* probe);
s32 func_800DBCF4_minigame(s32 n, s16* idx, ColVtx* verts, HitProbe* probe);

void func_800DC354_minigame(omObjData* g, Vec4f* p, Vec* save);
void func_800DC7D8_minigame(omObjData* g, Vec4f* p);
void func_800DC8E4_minigame(omObjData* g, Vec4f* p, f32 h);

/* A96F0 */
void func_800D81C8_minigame(omObjData* obj, omObjData* actor);

/* AB1C0 (fork B) */
void func_800DCCB0_minigame(omObjData* g, Vec4f* p, Vec* save, f32 h);
s32 func_800DD530_minigame(omObjData* obj, Vec4f* p, f32 arg2);
void func_800DDB60_minigame(omObjData* obj, Vec* n);
void func_800DFCDC_minigame(f32 dx, f32 dz, f32 d);
void func_800E0430_minigame(f32 nx, f32 ny, f32 nz);
void func_800E048C_minigame(f32 x, f32 y, f32 z);
/* B3CE0, B63A0, B7600 */
void func_800E1A9C_minigame(MgWork* w, s32 state);
void func_800E2CA4_minigame(omObjData* obj, f32 arg1);
f32 func_800E2ED4_minigame(f32 x1, f32 z1, f32 x2, f32 z2);
void func_800E317C_minigame(omObjData* obj, f32 dx, f32 dz);
void func_800E34D8_minigame(omObjData* a, omObjData* b);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
void func_800E561C_minigame(omObjData* obj, u8 flags);
void func_800E1810_minigame(void);
void func_800E19FC_minigame(MgWork* w, s32 state);
void func_800E28BC_minigame(f32 (*l2w)[4], f32 (*w2l)[4], Vec* p, omObjData* g);
void func_800E2B58_minigame(f32 (*m)[4], Vec* v);
void func_800E2BD4_minigame(f32 (*m)[4], Vec* v);
void func_800E2C68_minigame(f32 (*m)[4], Vec* v);
s32 func_800E2F40_minigame(void* parts, Vec* p);
s32 func_800E30B8_minigame(Vec* p, GroundWork* gw);
void func_800E47D8_minigame(omObjData* obj, f32 y);
void func_800E4890_minigame(omObjData* obj, f32 x, f32 y, f32 z, f32 shadowY, Vec* n);
s32 func_800E5690_minigame(omObjData* obj, s32 motion);

/* main */
s32 func_8000DC24_main(f32 tri[3][3], Vec* pos, f32 r, Vec* hit);  /* sphere against a triangle */
s32 func_8000E19C_main(f32 quad[4][3], Vec* pos, f32 r, Vec* hit); /* sphere against a quad */
s32 func_800202FC_main(Vec* v);                                     /* normalise */
void func_8002038C_main(ColVtx* a, ColVtx* b, ColVtx* c, Vec* n);  /* face normal */
f32 func_8002048C_main(f32 x, f32 z, ColVtx* a, ColVtx* b);
f32 func_800204F4_main(f32 x, f32 y, f32 z, ColVtx* verts, ColTri* tri); /* face height */
void func_80021C14_main(s16 mi, HitList* l, s32 (*cb)(s32, u16*, ColVtx*, HitProbe*), HitProbe* probe);
u16* func_80022198_main(HitList* l);
f64 fabs(f64);
f32 fabsf(f32);

extern u8 D_800EB734_minigame;  /* ground object tested first (the one stood on) */
extern s16 D_800EB736_minigame; /* contact count */
extern u8 D_800EB738_minigame;  /* ground object of the last floor found */
extern u8 D_800EB735_minigame;
extern f32 D_800EB744_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB770_minigame;
extern f32 D_800EB778_minigame;
extern f32 D_800EB77C_minigame;

extern Vec D_800EBDD0_minigame;          /* reference point for the face-side test */
extern u16 D_800EBE28_minigame;          /* ground object count */
extern f32 D_800EBE2C_minigame;          /* push x this frame */
extern f32 D_800EBE30_minigame[4][4];    /* ground object: world to local */
extern HitList D_800EBEB0_minigame;      /* face query */
extern Vec D_800EBEB8_minigame[];        /* contact points */
extern omObjData* D_800EBE70_minigame[]; /* item actors (ColActorWork) */
extern u16 D_800EC1B8_minigame;          /* their count */
extern omObjData* D_800EC1C0_minigame[]; /* ground objects */
extern f32 D_800EC240_minigame[4][4];    /* ground object: local to world */
extern u16 D_800EC280_minigame;          /* player count */
extern u16 D_800EC288_minigame;          /* actor touches while MgWork.unk_BE is set */
extern Vec D_800EC298_minigame[];        /* contact normals */
extern omObjData* D_800EC598_minigame[]; /* player objects */
extern f32 D_800EC5D8_minigame;          /* push z this frame */

f32 func_800D8640_minigame(omObjData* g, MgWork* w, f32 y) {
    GroundWork* gw = g->data;
    Vec v;
    f32 c;

    if (gw->unk_06 & 0x50) {
        c = gw->unk_14 - gw->unk_98;
        if ((c < y + w->unk_34) & (y < c)) {
            v.x = 0.0f;
            v.y = c;
            v.z = 0.0f;
            if (g->trans.x != v.x || g->trans.y != v.x || g->trans.z != v.x || g->rot.x != v.x ||
                g->rot.y != v.x || g->rot.z != v.x) {
                func_800E2C68_minigame(D_800EC240_minigame, &v);
            }
            w->unk_8C = v.y;
            w->unk_56 = gw->unk_04;
        }
    }
    return gw->unk_14;
}

/* A face height h under a player: a downward-facing face (n->y < 0) within the player's height
   is a ceiling instead (w->unk_8C), and the floor result is -65536.0f. */
f32 func_800D8778_minigame(omObjData* g, MgWork* w, f32 h, f32 y, Vec* n) {
    GroundWork* gw = g->data;
    Vec v;

    if ((h < y + w->unk_34) & (y < h)) {
        if (n->y < 0.0f) {
            v.x = 0.0f;
            v.y = h;
            v.z = 0.0f;
            w->unk_8C = h;
            w->unk_56 = gw->unk_04;
            return -65536.0f;
        }
    }
    return h;
}

f32 func_800D8818_minigame(f32 x, f32 y, f32 z, ColVtx* verts, ColTri* tri, Vec* dir, Vec* out) {
    Vec n;
    f32 vx, vy, vz;
    f32 dx, dy, dz;
    f32 t;
    f32 d;
    f32 nx, ny, nz;
    ColVtx* v = &verts[tri->v[0]];

    vx = v->x;
    vy = v->y;
    vz = v->z;
    dx = dir->x;
    dy = dir->y;
    dz = dir->z;
    func_8002038C_main(v, &verts[tri->v[1]], &verts[tri->v[2]], &n);
    nx = n.x;
    ny = n.y;
    nz = n.z;
    d = nx * dx + ny * dy + nz * dz;
    t = (nx * (vx - x) + ny * (vy - y) + nz * (vz - z)) / d;
    x += dx * t;
    out->x = x;
    y += dy * t;
    out->y = y;
    z += dz * t;
    out->z = z;
    return y;
}

/* Highest floor of the ground objects under a player at (x, y, z), skipping D_800EB734_minigame;
   n receives its normal. A downward face or a primitive's underside within the player's height
   is recorded as a ceiling (func_800D8640_minigame, func_800D8778_minigame). */
f32 func_800D89CC_minigame(omObjData* obj, f32 x, f32 y, f32 z, Vec* n) {
    Vec4f q;
    Vec a;
    Vec d;
    MgWork* w = obj->data;
    f32 best = -65536.0f;
    s16 i;
    omObjData* g;
    GroundWork* gw;
    f32 h;
    s16 mdl;
    ColVtx* verts;
    ColTri* tri;
    u8 moved;

    q.w = 10.0f;
    w->unk_53 = -1;
    for (i = 0; i < D_800EBE28_minigame; i++) {
        g = D_800EC1C0_minigame[i];
        gw = g->data;
        if (i == D_800EB734_minigame) {
            continue;
        }
        if (w->unk_00[i] & 1) {
            continue;
        }
        q.x = x;
        q.y = y;
        q.z = z;
        func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, (Vec*)&q, g);
        if ((gw->unk_06 & 4) && func_800E2F40_minigame(HmfModelData[*g->model].hmf->unk60, (Vec*)&q) == 0) {
            continue;
        }
        if (gw->unk_06 & 0x7A) {
            if ((gw->unk_06 & 0x50) && func_800E30B8_minigame((Vec*)&q, gw) == 0) {
                continue;
            }
            h = func_800D8640_minigame(g, w, q.y);
            if (g->trans.x != 0.0f || g->trans.y != 0.0f || g->trans.z != 0.0f || g->rot.x != 0.0f ||
                g->rot.y != 0.0f || g->rot.z != 0.0f) {
                q.y = h;
                func_800E2C68_minigame(D_800EC240_minigame, (Vec*)&q);
                if (best <= q.y && q.y < y + 150.0f) {
                    best = q.y;
                    w->unk_53 = D_800EB738_minigame = i;
                    if (n != NULL) {
                        n->z = n->x = 0.0f;
                        n->y = 1.0f;
                        func_800E2B58_minigame(D_800EC240_minigame, n);
                        func_800202FC_main(n);
                    }
                }
            } else if (best <= h && h < y + 150.0f) {
                best = h;
                D_800EB738_minigame = i;
                w->unk_53 = i;
                if (n != NULL) {
                    n->x = 0.0f;
                    n->y = 1.0f;
                    n->z = 0.0f;
                }
            }
        } else {
            mdl = *g->model;
            verts = HmfModelData[mdl].hmf->unk50;
            func_80021C14_main(mdl, &D_800EBEB0_minigame, func_800DB704_minigame, (HitProbe*)&q);
            goto next;
            do {
                moved = 0;
                if (g->trans.x != 0.0f || g->trans.y != 0.0f || g->trans.z != 0.0f || g->rot.x != 0.0f ||
                    g->rot.y != 0.0f || g->rot.z != 0.0f) {
                    a.x = x;
                    a.y = y + 101.23f;
                    a.z = z;
                    func_800E2BD4_minigame(D_800EBE30_minigame, &a);
                    d.x = a.x - q.x;
                    d.y = a.y - q.y;
                    d.z = a.z - q.z;
                    func_800202FC_main(&d);
                    func_800D8818_minigame(q.x, q.y, q.z, verts, tri, &d, (Vec*)&q);
                    func_800E2C68_minigame(D_800EC240_minigame, (Vec*)&q);
                    func_8002038C_main(&verts[tri->v[0]], &verts[tri->v[1]], &verts[tri->v[2]], &d);
                    func_800E2B58_minigame(D_800EC240_minigame, &d);
                    h = func_800D8778_minigame(g, w, q.y, y, &d);
                    moved = 1;
                } else {
                    h = func_800204F4_main(q.x, q.y, q.z, verts, tri);
                }
                if (best <= h && h < y + 150.0f) {
                    best = h;
                    D_800EB738_minigame = i;
                    w->unk_53 = i;
                    if (n != NULL) {
                        func_8002038C_main(&verts[tri->v[0]], &verts[tri->v[1]], &verts[tri->v[2]], n);
                        if (moved == 1) {
                            a.x = n->x;
                            a.y = n->y;
                            a.z = n->z;
                            func_800E2B58_minigame(D_800EC240_minigame, &a);
                            n->x = a.x;
                            n->y = a.y;
                            n->z = a.z;
                            func_800202FC_main(n);
                        }
                    }
                }
            next:;
            } while ((tri = (ColTri*)func_80022198_main(&D_800EBEB0_minigame)) != NULL);
        }
    }
    return best;
}

/* A player's step (MP1 func_80002C48): move along the heading, push out of walls, find the floor
   and the shadow under the new position. Retail never initialises normal (passed to
   func_800E4890_minigame when nothing was found) and adds the push to x/z twice when
   func_800DA768_minigame returns 2. Host hazard: the uninitialised normal. */
// retail compares floorY with -65536.0f after the model-floor loop and writes it back: a no-op it really executes
f32 func_800D9028_minigame(omObjData* obj, f32 x, f32 y, f32 z, f32 unused) {
    Vec4f probe;
    Vec n;
    Vec n2;
    MgWork* w;
    GroundWork* gw;
    Vec* normal;
    f32 speed;
    f32 sa, sb, sc;
    f32 nx, nz;
    f32 floorY, shadowY;
    f32 h;
    s16 mdl;
    ColVtx* verts;
    ColTri* tri;

    w = obj->data;
    w->unk_53 = w->unk_54 = -1;
    w->unk_8C = 65536.0f;
    sa = w->unk_40;
    sb = w->unk_4C;
    sc = w->unk_B4;
    if (w->unk_50 & 6) {
        speed = sa * 0.6f * sb;
    } else {
        speed = sa * sb;
    }
    speed *= sc;
    nx = x + sindf(w->unk_3C) * speed + D_800EBE2C_minigame;
    nz = z + cosdf(w->unk_3C) * speed + D_800EC5D8_minigame;
    shadowY = floorY = -65536.0f;
    if (func_800DA768_minigame(obj, nx, y, nz) != 2) {
        func_800DB628_minigame(obj);
        sa = w->unk_40;
        sb = w->unk_4C;
        sc = w->unk_B4;
        if (w->unk_50 & 6) {
            speed = sa * 0.6f * sb;
        } else {
            speed = sa * sb;
        }
        speed *= sc;
        nx = x + sindf(w->unk_3C) * speed;
        nz = z + cosdf(w->unk_3C) * speed;
        probe.x = nx;
        probe.y = y;
        probe.z = nz;
        probe.w = w->unk_48;
        func_800DD530_minigame(obj, &probe, 0);
        func_800DB628_minigame(obj);
        probe.x = nx + D_800EBE2C_minigame;
        probe.y = y;
        probe.z = nz + D_800EC5D8_minigame;
        if (!(w->unk_00[D_800EB734_minigame] & 1)) {
            gw = D_800EC1C0_minigame[D_800EB734_minigame]->data;
            if (gw->unk_06 & 0x7A) {
                if (func_800E30B8_minigame((Vec*)&probe, gw) == 1) {
                    h = gw->unk_14;
                    if (floorY < h && h < y + 150.0f) {
                        floorY = h;
                        D_800EB738_minigame = D_800EB734_minigame;
                        if (shadowY < floorY && shadowY < y + 35.0f) {
                            shadowY = floorY;
                            n.x = 0.0f;
                            n.y = 1.0f;
                            n.z = 0.0f;
                            normal = &n;
                        }
                    }
                }
            } else {
                mdl = *D_800EC1C0_minigame[D_800EB734_minigame]->model;
                verts = HmfModelData[mdl].hmf->unk50;
                func_80021C14_main(mdl, &D_800EBEB0_minigame, func_800DB704_minigame, (HitProbe*)&probe);
                for (tri = (ColTri*)func_80022198_main(&D_800EBEB0_minigame); tri != NULL; tri = (ColTri*)func_80022198_main(&D_800EBEB0_minigame)) {
                    h = func_800204F4_main(nx + D_800EBE2C_minigame, y, nz + D_800EC5D8_minigame, verts, tri);
                    if (floorY < h && h < y + 150.0f) {
                        floorY = h;
                        D_800EB738_minigame = D_800EB734_minigame;
                    }
                    if (shadowY < h && shadowY < y + 35.0f) {
                        shadowY = h;
                        func_8002038C_main(&verts[tri->v[0]], &verts[tri->v[1]], &verts[tri->v[2]], &n);
                        normal = &n;
                    }
                }
                if (floorY == -65536.0f) {
                    floorY = -65536.0f;
                }
            }
        }
        h = func_800D89CC_minigame(obj, nx + D_800EBE2C_minigame, y, nz + D_800EC5D8_minigame, &n2);
        if (floorY < h && h < y + 150.0f) {
            floorY = h;
        } else {
            w->unk_53 = -1;
        }
        if (shadowY < h && h < y + 150.0f) {
            shadowY = h;
            normal = &n2;
        }
        if (floorY == -65536.0f) {
            shadowY = -65536.0f;
            w->unk_4C = D_800EB778_minigame;
            if (w->unk_38 < 0.0f) {
                w->unk_38 = 0.0f;
            }
            w->unk_53 = -1;
            if (w->unk_8C != 65536.0f) {
                y = w->unk_8C - w->unk_34;
                func_800E47D8_minigame(obj, y);
            }
        } else if (y < floorY) {
            w->unk_53 = D_800EB738_minigame;
            y = func_800D9F10_minigame(obj, floorY);
            w->unk_38 = 1000.0f;
            w->unk_50 &= ~8;
            if (w->unk_00[(s8)D_800EB738_minigame] & 8) {
                func_800E1810_minigame();
            }
        } else {
            w->unk_53 = -1;
            if (w->unk_8C != 65536.0f) {
                y = w->unk_8C - w->unk_34;
                func_800E47D8_minigame(obj, y);
            }
        }
    } else {
        probe.x = nx + D_800EBE2C_minigame;
        probe.y = y;
        probe.z = nz + D_800EC5D8_minigame;
        probe.w = w->unk_48;
        func_800DD530_minigame(obj, &probe, 0);
    }
    if (obj->model[1] != 0) {
        func_800E4890_minigame(obj, nx, y, nz, shadowY, normal);
    }
    obj->rot.x = obj->rot.z = w->unk_9C = w->unk_A4 = w->unk_90 = w->unk_94 = w->unk_98 = 0.0f;
    return y;
}

/* A player's step with the ground's conveyor push (MP1 func_80002C48): move along rot, push out of
   walls, land on the floor within 35 units or start falling (returns 65536.0f). */
f32 func_800D972C_minigame(omObjData* obj, f32 rot, f32 x, f32 y, f32 z) {
    Vec4f probe;
    Vec n;
    Vec n2;
    MgWork* w;
    GroundWork* gw;
    GroundWork* cur;
    ColVtx* verts;
    ColTri* tri;
    s16 mdl;
    Vec* normal;
    s32 ground;
    f32 speed;
    f32 sa, sb;
    f32 floorY, shadowY;
    f32 h;
    f32 nx, nz;

    ground = -1;
    w = obj->data;
    w->unk_54 = ground;
    w->unk_53 = ground;
    w->unk_8C = 65536.0f;
    normal = NULL;
    sa = w->unk_40;
    sb = w->unk_B4;
    if (w->unk_50 & 6) {
        speed = sa * 0.6f * sb;
    } else {
        speed = sa * sb;
    }
    if (fabs(w->unk_90) > 1.0) {
        D_800EBE2C_minigame += w->unk_90;
    }
    if (fabs(w->unk_98) > 1.0) {
        D_800EC5D8_minigame += w->unk_98;
    }
    nx = x + sindf(rot) * speed + D_800EBE2C_minigame;
    nz = z + cosdf(rot) * speed + D_800EC5D8_minigame;
    shadowY = floorY = -65536.0f;
    if (func_800DA768_minigame(obj, nx, y, nz) != 2) {
        func_800DB628_minigame(obj);
        sa = w->unk_40;
        sb = w->unk_B4;
        if (w->unk_50 & 6) {
            speed = sa * 0.6f * sb;
        } else {
            speed = sa * sb;
        }
        nx = x + sindf(rot) * speed;
        nz = z + cosdf(rot) * speed;
        probe.x = nx + D_800EBE2C_minigame;
        probe.y = y;
        probe.z = nz + D_800EC5D8_minigame;
        probe.w = w->unk_48;
        func_800DD530_minigame(obj, &probe, 0);
        func_800DB628_minigame(obj);
        probe.x = nx + D_800EBE2C_minigame;
        probe.y = y;
        probe.z = nz + D_800EC5D8_minigame;
        if (!(w->unk_00[D_800EB734_minigame] & 1)) {
            gw = D_800EC1C0_minigame[D_800EB734_minigame]->data;
            if (gw->unk_06 & 0x7A) {
                if (func_800E30B8_minigame((Vec*)&probe, gw) == 1) {
                    h = gw->unk_14;
                    if (floorY < h && h < y + 150.0f) {
                        floorY = h;
                        ground = D_800EB734_minigame;
                        if (shadowY < floorY && shadowY < y + 35.0f) {
                            shadowY = floorY;
                            n.x = 0.0f;
                            n.y = 1.0f;
                            n.z = 0.0f;
                            normal = &n;
                        }
                    }
                }
            } else {
                mdl = *D_800EC1C0_minigame[D_800EB734_minigame]->model;
                verts = HmfModelData[mdl].hmf->unk50;
                func_80021C14_main(mdl, &D_800EBEB0_minigame, func_800DB704_minigame, (HitProbe*)&probe);
                for (tri = (ColTri*)func_80022198_main(&D_800EBEB0_minigame); tri != NULL; tri = (ColTri*)func_80022198_main(&D_800EBEB0_minigame)) {
                    h = func_800204F4_main(nx, y, nz, verts, tri);
                    if (floorY < h) {
                        floorY = h;
                        ground = D_800EB734_minigame;
                    }
                    if (shadowY < h && shadowY < y + 35.0f) {
                        shadowY = h;
                        func_8002038C_main(&verts[tri->v[0]], &verts[tri->v[1]], &verts[tri->v[2]], &n);
                        normal = &n;
                    }
                }
                if (floorY == -65536.0f) {
                    floorY = -65536.0f;
                }
            }
        }
        h = func_800D89CC_minigame(obj, nx + D_800EBE2C_minigame, y, nz + D_800EC5D8_minigame, &n2);
        if (floorY < h && h < y + 35.0f) {
            ground = D_800EB738_minigame;
            floorY = h;
        } else {
            if (h < y + 150.0f && y + 35.0f < h) {
                floorY = 65536.0f;
            }
            w->unk_53 = -1;
        }
        if (shadowY < h && h < y + 35.0f) {
            shadowY = h;
            normal = &n2;
        }
        if (y - 35.0f < floorY && floorY < y + 35.0f) {
            if ((s8)ground != -1) {
                w->unk_53 = ground;
            }
            y = func_800D9F10_minigame(obj, floorY);
            if (w->unk_00[(s8)ground] & 8) {
                func_800E1810_minigame();
            }
            w->unk_38 = 1000.0f;
            if (w->unk_8C != 65536.0f) {
                func_800E47D8_minigame(obj, y);
            }
        } else {
            func_800E5690_minigame(obj, 6);
            w->unk_38 = D_800EB77C_minigame;
            w->unk_53 = -1;
            func_800E19FC_minigame(w, 13);
            return 65536.0f;
        }
    } else {
        probe.x = nx + D_800EBE2C_minigame;
        probe.y = y;
        probe.z = nz + D_800EC5D8_minigame;
        probe.w = w->unk_48;
        func_800DD530_minigame(obj, &probe, 0);
    }
    if (obj->model[1] != 0) {
        func_800E4890_minigame(obj, nx, y, nz, shadowY, normal);
    }
    if (w->unk_53 >= 0) {
        cur = D_800EC1C0_minigame[w->unk_53]->data;
        w->unk_90 = normal->x * cur->unk_10;
        w->unk_94 = normal->y;
        w->unk_98 = normal->z * cur->unk_10;
        if (cur->unk_06 & 0x400) {
            func_800DDB60_minigame(obj, normal);
        }
    } else {
        obj->rot.x = obj->rot.z = w->unk_9C = w->unk_A4 = w->unk_90 = w->unk_94 = w->unk_98 = 0.0f;
    }
    return y;
}

f32 func_800D9F10_minigame(omObjData* obj, f32 y) {
    u8* w = obj->data;
    f32 r = obj->trans.y;

    if (w[w[0x53]] & 2) {
        r = y;
    }
    return r;
}

s32 func_800D9F3C_minigame(Vec* pos, ColTri* tri, ColVtx* verts) {
    Vec n;
    ColVtx* v;
    f32 vx, vy, vz;
    f32 dx, dy, dz;
    s32 ret;

    func_8002038C_main(&verts[tri->v[0]], &verts[tri->v[1]], &verts[tri->v[2]], &n);
    v = &verts[tri->v[0]];
    vx = v->x;
    vy = v->y;
    vz = v->z;
    dx = vx - pos->x;
    dy = vy - pos->y;
    dz = vz - pos->z;
    ret = 1;
    if (dx * n.x + dy * n.y + dz * n.z < 0.0f) {
        ret = -1;
    }
    return ret;
}

s32 func_800DA054_minigame(Vec4f* s, s16* tri, ColVtx* verts) {
    s32 side = -1;
    Vec n;
    ColVtx* v;
    f32 dx, dy, dz;
    f32 vx, vy, vz;
    f32 d;
    f32 t;

    if ((tri[0] & 0x3F00) <= 0x200) {
        return 0;
    }
    func_8002038C_main(&verts[tri[1]], &verts[tri[2]], &verts[tri[3]], &n);
    v = &verts[tri[1]];
    vx = v->x;
    vy = dx = v->y; // dx is reassigned below; the extra copy (decomp-permuter) reproduces retail's registers
    vz = v->z;
    dx = vx - s->x;
    dy = vy - s->y;
    dz = vz - s->z;
    d = dx * n.x + dy * n.y + dz * n.z;
    if (d >= 0.0f) {
        side = 1;
    }
    if (fabsf(d) > s->w) {
        return 0;
    }
    t = dx * n.x + dy * n.y + dz * n.z;
    s->x += t * n.x;
    s->y += t * n.y;
    s->z += t * n.z;
    return side;
}

f32 func_800DA204_minigame(f32 x, f32 y, f32 z, ColVtx* a, ColVtx* b, Vec* n) {
    f32 ax = a->x - x;
    f32 ay = a->y - y;
    f32 az = a->z - z;
    f32 bx = b->x - x;
    f32 by = b->y - y;
    f32 bz = b->z - z;

    return (ay * bz - az * by) * n->x + (az * bx - ax * bz) * n->y + (ax * by - ay * bx) * n->z;
}

s32 func_800DA2E0_minigame(Vec* p, s16* idx, ColVtx* verts, Vec* n) {
    f32 x = p->x;
    f32 y = p->y;
    f32 z = p->z;
    s32 cnt = ((u16)*idx >> 14) + 2;
    s32 i;
    s32 j;

    idx++;
    if (func_800DA204_minigame(x, y, z, &verts[idx[0]], &verts[idx[1]], n) > 0.0f) {
        for (i = 1; i < cnt; i++) {
            j = (i + 1) % cnt;
            if (func_800DA204_minigame(x, y, z, &verts[idx[i]], &verts[idx[j]], n) < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < cnt; i++) {
            j = (i + 1) % cnt;
            if (func_800DA204_minigame(x, y, z, &verts[idx[i]], &verts[idx[j]], n) > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}

s32 func_800DA540_minigame(Vec* p, ColTri* tri, ColVtx* verts) {
    f32 x, z;
    s32 cnt;
    s16* idx;
    s32 i;
    s32 j;

    idx = (s16*)tri;
    if (((u16)*idx & 0x3F00) > 0x200) {
        return 0;
    }
    x = p->x;
    z = p->z;
    cnt = ((u16)*idx >> 14) + 2;
    idx++;
    if (func_8002048C_main(x, z, &verts[idx[0]], &verts[idx[1]]) > 0.0f) {
        for (i = 1; i < cnt; i++) {
            j = (i + 1) % cnt;
            if (func_8002048C_main(x, z, &verts[idx[i]], &verts[idx[j]]) < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < cnt; i++) {
            j = (i + 1) % cnt;
            if (func_8002048C_main(x, z, &verts[idx[i]], &verts[idx[j]]) > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}

/* The player's step against the item actors (D_800EBE70_minigame: hazards, bouncing actors, coins)
   and the other players. Returns 2 when the player stomped or bumped another player, else 0. */
// register allocation (masked 0, raw 79): y and the radius swap s4/s5, and dy/dz and 0.0f swap
// $f22/$f26/$f30, as in MP2's func_80004168_4D68; declaration order made it worse
#ifdef NON_MATCHING
s32 func_800DA768_minigame(omObjData* obj, f32 x, f32 y, f32 z) {
    MgWork* w = obj->data;
    f32 radius = w->unk_48;
    f32 speed = w->unk_40;
    f32 py;
    omObjData* o;
    ColActorWork* ow;
    MgWork* ow2;
    f32 dx, dy, dz;
    f32 dist, flat;
    f32 dxx, dzz;
    f32 a;
    f32 dz2;
    u16 i;

    if (w->unk_50 & 6) {
        speed *= 0.6f;
    }
    speed *= (w->unk_38 != 1000.0f) ? w->unk_4C * w->unk_B4 : w->unk_B4;
    x += sindf(w->unk_3C) * speed;
    z += cosdf(w->unk_3C) * speed;
    w->unk_F0 = 0;

    for (i = 0; i < D_800EC1B8_minigame; i++) {
        o = D_800EBE70_minigame[i];
        ow = o->data;
        if (ow->unk_54 == 0) {
            continue;
        }
        dx = o->trans.x - (x + D_800EBE2C_minigame);
        dy = o->trans.y - y;
        dz = o->trans.z - (z + D_800EC5D8_minigame);
        flat = 100.0f;
        if (ow->unk_34 != 0.0f && o->trans.y <= y && y <= o->trans.y + ow->unk_34) {
            flat = HuSqrtf(dx * dx + dz * dz) - (radius + ow->unk_48);
        }
        dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (radius + ow->unk_48);
        if ((dist < 0.0f) | (flat < 0.0f)) {
            if (w->unk_EC != NULL && w->unk_EC(obj, o) == 1) {
                continue;
            }
            if (ow->unk_52 == 7) {
                if (w->unk_BE != 0) {
                    D_800EC288_minigame++;
                    continue;
                }
                if (w->unk_50 & 0x200) {
                    continue;
                }
                a = func_800E2ED4_minigame(sindf(w->unk_3C), cosdf(w->unk_3C), dx, dz);
                if (w->unk_50 & 0x10) {
                    func_800E2CA4_minigame(obj, D_800EB768_minigame);
                }
                if (a > 0.0f) {
                    func_800E5690_minigame(obj, 9);
                    w->unk_40 = -D_800EB760_minigame;
                } else {
                    func_800E5690_minigame(obj, 10);
                    w->unk_40 = D_800EB760_minigame;
                }
                w->unk_38 = -D_800EB744_minigame * 0.7f;
                w->unk_BE = 105;
                func_800E4C88_minigame(obj, 5, o->trans.x, y, o->trans.z, 0.0f, atan2df(dx, dz) + 180.0f);
                func_800E19FC_minigame(w, 8);
                omVibrate(w->unk_59, 20, 0, 20);
            } else if (ow->unk_50 & 0x20) {
                if (!(ow->unk_50 & 0x10)) {
                    dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (ow->unk_48 + w->unk_48);
                    if (dist < 0.0f) {
                        if (ow->unk_38 < 1000.0f) {
                            ow->unk_38 = -D_800EB744_minigame * 0.6f;
                            if (func_800E2ED4_minigame(sindf(ow->unk_3C), cosdf(ow->unk_3C), dx, dz) < 0.0f) {
                                ow->unk_40 = -D_800EB76C_minigame;
                            } else {
                                ow->unk_40 = D_800EB76C_minigame;
                            }
                        } else if (ow->unk_40 == D_800EB770_minigame) {
                            if (w->unk_38 != 1000.0f) {
                                func_800E317C_minigame(obj, dx, dz);
                                func_800E1A9C_minigame(w, 9);
                            } else {
                                if ((dx == 0.0f) & (dz == 0.0f)) {
                                    dx = sindf(w->unk_3C);
                                    dz = cosdf(w->unk_3C);
                                }
                                func_800DFCDC_minigame(dx, dz, dist);
                            }
                        } else {
                            ow->unk_40 = -ow->unk_40;
                        }
                    }
                }
            } else if (w->unk_BE != 0) {
                D_800EC288_minigame++;
            } else {
                func_800D81C8_minigame(obj, o);
            }
        }
    }

    py = y + w->unk_48;
    if (w->unk_50 & 0x400) {
        return 0;
    }
    for (i = 0; i < D_800EC280_minigame; i++) {
        o = D_800EC598_minigame[i];
        ow2 = o->data;
        if (w == ow2) {
            continue;
        }
        dx = o->trans.x - (x + D_800EBE2C_minigame);
        dy = (o->trans.y + ow2->unk_48) - py;
        dz2 = o->trans.z - (z + D_800EC5D8_minigame);
        if (ow2->unk_50 & 0x400) {
            continue;
        }
        dxx = dx * dx;
        dzz = dz2 * dz2;
        dist = HuSqrtf(dxx + dzz) - (w->unk_48 + ow2->unk_48) * 0.6f;
        flat = HuSqrtf(dxx + dy * dy + dzz) - (ow2->unk_48 + w->unk_48);
        if (((dist < 0.0f) | (flat < 0.0f)) && w->unk_38 != 1000.0f && !(w->unk_50 & 0x8000)) {
            if (py - (ow2->unk_34 + ow2->unk_48) <= o->trans.y && o->trans.y <= (py - w->unk_48) + w->unk_34) {
                if (!(ow2->unk_50 & 7) && w->unk_BE == 0 && ow2->unk_BE == 0) {
                    if (ow2->unk_38 != 1000.0f) {
                        if (w->unk_5C & 0x200) {
                            if (!(dist < 0.0f && dy < -w->unk_34 * 0.5f)) {
                                goto block_93;
                            }
                            func_800E4C88_minigame(obj, 7, x, py, z, 0.0f, 0.0f);
                            if (!(ow2->unk_50 & 0x200)) {
                                func_800E561C_minigame(o, 1);
                                func_800E5690_minigame(o, 0x1E);
                                if (ow2->unk_50 & 0x10) {
                                    func_800E2CA4_minigame(o, D_800EB76C_minigame);
                                }
                            }
                            ow2->unk_38 = w->unk_38;
                            goto block_104;
                        block_93:
                            if (D_800EB735_minigame != 1) {
                                goto block_78;
                            }
                            func_800E34D8_minigame(obj, o);
                            return 0;
                        }
                        if (!(dist < 0.0f && dy < -w->unk_34 * 0.2)) {
                            goto block_93;
                        }
                        if (!(ow2->unk_50 & 0x200)) {
                            func_800E4C88_minigame(obj, 6, x, py, z, -90.0f, 0.0f);
                            if (ow2->unk_50 & 0x10) {
                                func_800E2CA4_minigame(o, D_800EB76C_minigame);
                            }
                        }
                        if (ow2->unk_38 < 0.0f) {
                            ow2->unk_38 = 0.0f;
                        }
                    block_104:
                        ow2->unk_40 = D_800EB770_minigame;
                        func_800E317C_minigame(obj, dx, dz2);
                        func_800E1A9C_minigame(w, 9);
                        goto block_105;
                    block_78:
                        func_800DFCDC_minigame(dx, dz2, HuSqrtf(dx * dx + dz2 * dz2) - (ow2->unk_48 + w->unk_48));
                        return 0;
                    block_105:
                        omVibrate(w->unk_59, 2, 3, 10);
                        omVibrate(ow2->unk_59, 2, 3, 10);
                        return 2;
                    }
                    if ((dist < 0.0f) & (dy < 0.0f)) {
                        if (!(ow2->unk_50 & 0x200)) {
                            if (w->unk_5C & 0x200) {
                                func_800E561C_minigame(o, 1);
                                func_800E5690_minigame(o, 0);
                                func_800E4C88_minigame(obj, 7, x, py, z, 0.0f, 0.0f);
                            } else {
                                func_800E4C88_minigame(obj, 6, x, py, z, -90.0f, 0.0f);
                                func_800E561C_minigame(o, 2);
                            }
                            if (ow2->unk_50 & 0x10) {
                                func_800E2CA4_minigame(o, D_800EB76C_minigame);
                            }
                        }
                        func_800E317C_minigame(obj, dx, dz2);
                        func_800E1A9C_minigame(w, 9);
                        omVibrate(w->unk_59, 2, 3, 10);
                        omVibrate(ow2->unk_59, 20, 0, 20);
                        return 2;
                    }
                    func_800E317C_minigame(obj, dx, dz2);
                    w->unk_38 = -D_800EB744_minigame * 0.6f;
                    w->unk_40 = w->unk_40 * 0.5;
                    func_800E1A9C_minigame(w, 9);
                    omVibrate(w->unk_59, 2, 3, 10);
                    omVibrate(ow2->unk_59, 20, 0, 20);
                } else if (w->unk_38 != 1000.0f && ow2->unk_38 != 1000.0f) {
                    if (w->unk_BE != 0 || ow2->unk_BE != 0) {
                        if (D_800EB735_minigame == 1) {
                            func_800E34D8_minigame(obj, o);
                            omVibrate(w->unk_59, 2, 3, 10);
                            return 0;
                        }
                        func_800DFCDC_minigame(dx, dz2, flat);
                        return 0;
                    }
                } else {
                    if (w->unk_5C & 0x200) {
                        func_800E4C88_minigame(obj, 7, x, py, z, 0.0f, 0.0f);
                    } else {
                        func_800E4C88_minigame(obj, 6, x, py, z, -90.0f, 0.0f);
                    }
                    omVibrate(w->unk_59, 2, 3, 10);
                    func_800E317C_minigame(obj, dx, dz2);
                    func_800E1A9C_minigame(w, 9);
                }
            } else if (flat < 0.0f) {
                if (D_800EB735_minigame == 1) {
                    func_800E34D8_minigame(obj, o);
                } else {
                    func_800DFCDC_minigame(dx, dz2, flat);
                }
            }
        } else {
            flat = HuSqrtf(dx * dx + dy * dy + dz2 * dz2) - (ow2->unk_48 + w->unk_48);
            if (flat < 0.0f) {
                if (ow2->unk_38 != 1000.0f && w->unk_38 == 1000.0f) {
                    continue;
                }
                func_800DFCDC_minigame(dx, dz2, flat);
                w->unk_54 = i;
            }
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA768_minigame);
#endif


/* Clamp this frame's push: a push longer than the radius is replaced by one opposite the heading. */
void func_800DB628_minigame(omObjData* obj) {
    MgWork* w = obj->data;
    f32 r = w->unk_48;
    f32 rot;

    if (r < HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame) ||
        fabs(D_800EBE2C_minigame) > r || fabs(D_800EC5D8_minigame) > r) {
        rot = w->unk_3C;
        D_800EBE2C_minigame = -sindf(rot) * w->unk_40;
        D_800EC5D8_minigame = -cosdf(rot) * w->unk_40;
    }
}

s32 func_800DB704_minigame(s32 n, u16* idx, ColVtx* verts, HitProbe* p) {
    return func_800DA540_minigame((Vec*)p, (ColTri*)(idx - 1), verts);
}

/* Face filter for a face list in world space: push the sphere out of the face, recording the
   contact point and the face normal (MP1 func_80002080). */
s32 func_800DB724_minigame(s32 n, s16* idx, ColVtx* verts, HitProbe* probe) {
    ColSphere* s = (ColSphere*)probe;
    Vec4f sph;
    Vec pos;
    Vec hitPos;
    f32 quad[4][3];
    f32 tri3[3][3];
    Vec dir;
    s16* tri;
    s32 side;
    s32 hit;
    f32 pen, dz, dx;

    pos.x = sph.x = s->x + D_800EBE2C_minigame;
    pos.y = sph.y = s->y;
    pos.z = sph.z = s->z + D_800EC5D8_minigame;
    sph.w = s->r;
    tri = idx - 1;
    side = func_800DA054_minigame(&sph, tri, verts);
    if (side == 0) {
        return 0;
    }
    if (((u16)*tri >> 14) + 2 == 4) {
        quad[0][0] = verts[idx[0]].x;
        quad[0][1] = verts[idx[0]].y;
        quad[0][2] = verts[idx[0]].z;
        quad[1][0] = verts[idx[1]].x;
        quad[1][1] = verts[idx[1]].y;
        quad[1][2] = verts[idx[1]].z;
        quad[2][0] = verts[idx[2]].x;
        quad[2][1] = verts[idx[2]].y;
        quad[2][2] = verts[idx[2]].z;
        quad[3][0] = verts[idx[3]].x;
        quad[3][1] = verts[idx[3]].y;
        quad[3][2] = verts[idx[3]].z;
        hit = func_8000E19C_main(quad, (Vec*)&pos, sph.w, &hitPos);
    } else {
        tri3[0][0] = verts[idx[0]].x;
        tri3[0][1] = verts[idx[0]].y;
        tri3[0][2] = verts[idx[0]].z;
        tri3[1][0] = verts[idx[1]].x;
        tri3[1][1] = verts[idx[1]].y;
        tri3[1][2] = verts[idx[1]].z;
        tri3[2][0] = verts[idx[2]].x;
        tri3[2][1] = verts[idx[2]].y;
        tri3[2][2] = verts[idx[2]].z;
        hit = func_8000DC24_main(tri3, (Vec*)&pos, sph.w, &hitPos);
    }
    if (hit == 1) {
        func_800E048C_minigame(hitPos.x, hitPos.y, hitPos.z);
        func_8002038C_main(&verts[idx[0]], &verts[idx[1]], &verts[idx[2]], &D_800EC298_minigame[D_800EB736_minigame]);
        D_800EB736_minigame++;
        dx = hitPos.x - pos.x;
        dz = hitPos.z - pos.z;
        pen = sph.w - HuSqrtf(dx * dx + dz * dz);
        if (side > 0) {
            idx--;
            if (func_800D9F3C_minigame(&D_800EBDD0_minigame, (ColTri*)idx, verts) < 0) {
                dir.x = D_800EBDD0_minigame.x - pos.x;
                dir.y = D_800EBDD0_minigame.y - pos.y;
                dir.z = D_800EBDD0_minigame.z - pos.z;
                func_800202FC_main(&dir);
                if (func_800DA2E0_minigame(&pos, idx, verts, &dir) == hit) {
                    pen = HuSqrtf(dx * dx + dz * dz) + sph.w;
                }
            } else {
                pen = 0.0f;
            }
        }
        func_800DFCDC_minigame(-dx, -dz, pen);
    }
    return hit;
}

/* func_800DB724_minigame for a ground object's local face list: the hit is moved to world space with
   D_800EC240_minigame and the reference point to local space (MP1 func_8000261C). */
s32 func_800DBCF4_minigame(s32 n, s16* idx, ColVtx* verts, HitProbe* probe) {
    ColSphere* s = (ColSphere*)probe;
    Vec4f sph;
    Vec4f pos;
    Vec hitPos;
    f32 quad[4][3];
    f32 tri3[3][3];
    Vec dir;
    s16* tri;
    s32 side;
    s32 hit;
    f32 pen, dz, dx;

    pos.x = sph.x = s->x + D_800EBE2C_minigame;
    pos.y = sph.y = s->y;
    pos.z = sph.z = s->z + D_800EC5D8_minigame;
    sph.w = pos.w = s->r;
    tri = idx - 1;
    side = func_800DA054_minigame(&sph, tri, verts);
    if (side == 0) {
        return 0;
    }
    if (((u16)*tri >> 14) + 2 == 4) {
        quad[0][0] = verts[idx[0]].x;
        quad[0][1] = verts[idx[0]].y;
        quad[0][2] = verts[idx[0]].z;
        quad[1][0] = verts[idx[1]].x;
        quad[1][1] = verts[idx[1]].y;
        quad[1][2] = verts[idx[1]].z;
        quad[2][0] = verts[idx[2]].x;
        quad[2][1] = verts[idx[2]].y;
        quad[2][2] = verts[idx[2]].z;
        quad[3][0] = verts[idx[3]].x;
        quad[3][1] = verts[idx[3]].y;
        quad[3][2] = verts[idx[3]].z;
        hit = func_8000E19C_main(quad, (Vec*)&pos, sph.w, &hitPos);
    } else {
        tri3[0][0] = verts[idx[0]].x;
        tri3[0][1] = verts[idx[0]].y;
        tri3[0][2] = verts[idx[0]].z;
        tri3[1][0] = verts[idx[1]].x;
        tri3[1][1] = verts[idx[1]].y;
        tri3[1][2] = verts[idx[1]].z;
        tri3[2][0] = verts[idx[2]].x;
        tri3[2][1] = verts[idx[2]].y;
        tri3[2][2] = verts[idx[2]].z;
        hit = func_8000DC24_main(tri3, (Vec*)&pos, sph.w, &hitPos);
    }
    if (hit == 1) {
        pos.x = s->x2 + D_800EBE2C_minigame;
        pos.y = s->y2;
        pos.z = s->z2 + D_800EC5D8_minigame;
        func_800E2BD4_minigame(D_800EC240_minigame, &hitPos);
        func_800E048C_minigame(hitPos.x, hitPos.y, hitPos.z);
        func_8002038C_main(&verts[idx[0]], &verts[idx[1]], &verts[idx[2]], &D_800EC298_minigame[D_800EB736_minigame]);
        D_800EB736_minigame++;
        dx = hitPos.x - pos.x;
        dz = hitPos.z - pos.z;
        pen = sph.w - HuSqrtf(dx * dx + dz * dz);
        if (side > 0) {
            sph.x = D_800EBDD0_minigame.x;
            sph.y = D_800EBDD0_minigame.y;
            sph.z = D_800EBDD0_minigame.z;
            func_800E2BD4_minigame(D_800EBE30_minigame, (Vec*)&sph);
            idx--;
            if (func_800D9F3C_minigame((Vec*)&sph, (ColTri*)idx, verts) < 0) {
                dir.x = sph.x - pos.x;
                dir.y = sph.y - pos.y;
                dir.z = sph.z - pos.z;
                func_800202FC_main(&dir);
                if (func_800DA2E0_minigame((Vec*)&pos, idx, verts, &dir) == hit) {
                    pen = HuSqrtf(dx * dx + dz * dz) + sph.w;
                }
            } else {
                pen = 0.0f;
            }
        }
        if (pen >= 0.0f) {
            func_800DFCDC_minigame(-dx, -dz, pen);
        }
    }
    return hit;
}

/* Shape 8: the inside walls of a box (GroundWork.unk_A0..unk_AC); each wall the sphere reaches adds
   a contact (pushing harder when none did) and pushes it back in (MP1 func_80003460). */
/* save (the caller's unpushed probe position) is unused */
void func_800DC354_minigame(omObjData* obj, Vec4f* s, Vec* save) {
    s32 i = D_800EB736_minigame;
    GroundWork* g = obj->data;
    f32 x0 = g->unk_A0 + s->w;
    f32 z0 = g->unk_A4 + s->w;
    f32 x1 = g->unk_A8 - s->w;
    f32 z1 = g->unk_AC - s->w;
    f32 half;

    if (s->x <= x0) {
        func_800E048C_minigame(g->unk_A0, s->y, s->z);
        func_800E0430_minigame(1.0f, 0.0f, 0.0f);
        D_800EB736_minigame++;
    }
    if (x1 <= s->x) {
        func_800E048C_minigame(g->unk_A8, s->y, s->z);
        func_800E0430_minigame(-1.0f, 0.0f, 0.0f);
        D_800EB736_minigame++;
    }
    if (s->z <= z0) {
        func_800E048C_minigame(s->x, s->y, g->unk_A4);
        func_800E0430_minigame(0.0f, 0.0f, 1.0f);
        D_800EB736_minigame++;
    }
    if (z1 <= s->z) {
        func_800E048C_minigame(s->x, s->y, g->unk_AC);
        func_800E0430_minigame(0.0f, 0.0f, -1.0f);
        D_800EB736_minigame++;
    }
    if (i == D_800EB736_minigame) {
        half = s->w * 0.5f;
        if (s->x <= x0 - half) {
            func_800E048C_minigame(g->unk_A0, s->y, s->z);
            func_800E0430_minigame(1.0f, 0.0f, 0.0f);
            D_800EB736_minigame++;
        }
        if (x1 + half <= s->x) {
            func_800E048C_minigame(g->unk_A8, s->y, s->z);
            func_800E0430_minigame(-1.0f, 0.0f, 0.0f);
            D_800EB736_minigame++;
        }
        if (s->z <= z0 - half) {
            func_800E048C_minigame(s->x, s->y, g->unk_A4);
            func_800E0430_minigame(0.0f, 0.0f, 1.0f);
            D_800EB736_minigame++;
        }
        if (z1 + half <= s->z) {
            func_800E048C_minigame(s->x, s->y, g->unk_AC);
            func_800E0430_minigame(0.0f, 0.0f, -1.0f);
            D_800EB736_minigame++;
        }
    }
    for (; i < D_800EB736_minigame; i++) {
        x0 = D_800EBEB8_minigame[i].x - s->x;
        z0 = D_800EBEB8_minigame[i].z - s->z;
        func_800DFCDC_minigame(-x0, -z0, s->w - HuSqrtf(x0 * x0 + z0 * z0));
        if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f || obj->rot.x != 0.0f ||
            obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
            func_800E2BD4_minigame(D_800EC240_minigame, &D_800EBEB8_minigame[i]);
        }
    }
}

/* Shape 0x20: the inside wall of a cylinder (radius GroundWork.unk_9C) around the object. The
   contact point scales the probe by the unit direction (retail; not the radius). */
void func_800DC7D8_minigame(omObjData* obj, Vec4f* s) {
    GroundWork* g = obj->data;
    f32 x = s->x;
    f32 z = s->z;
    f32 d;
    Vec n;

    d = g->unk_9C - (HuSqrtf(x * x + z * z) + s->w);
    if (d <= 0.0f) {
        func_800DFCDC_minigame(x, z, d);
        n.x = x;
        n.y = 0.0f;
        n.z = z;
        func_800202FC_main(&n);
        func_800E048C_minigame(s->x * n.x, s->y, s->z * n.z);
        func_800E0430_minigame(-s->x, 0.0f, -s->z);
        D_800EB736_minigame++;
    }
}

/* Shape 0x40: the outside of a cylinder (radius GroundWork.unk_9C, top unk_14, height unk_98). */
void func_800DC8E4_minigame(omObjData* obj, Vec4f* s, f32 h) {
    GroundWork* g = obj->data;
    f32 x = s->x;
    f32 z = s->z;
    f32 d;
    Vec n;

    if (s->y < h + g->unk_14 && g->unk_14 - g->unk_98 - h < s->y) {
        d = HuSqrtf(x * x + z * z) - g->unk_9C;
        if (d >= 0.0f && d <= s->w) {
            func_800DFCDC_minigame(x, z, s->w - d);
            n.x = x;
            n.y = 0.0f;
            n.z = z;
            func_800202FC_main(&n);
            func_800E048C_minigame(-s->x * n.x, s->y, -s->z * n.z);
            func_800E0430_minigame(s->x, 0.0f, s->z);
            D_800EB736_minigame++;
        }
    }
}

/* minigame B: collision contacts and actor physics (MP2 src/1130.c func_80006440_7040 on, MP1
   src/1130.c func_8000396C on). */
s32 func_800202FC_main(Vec*); /* normalise */







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
void func_800DC7D8_minigame(omObjData* obj, Vec4f* s);         /* A: shape 0x20 */
void func_800DC8E4_minigame(omObjData* obj, Vec4f* s, f32 h);  /* A: shape 0x40 */
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
void func_800DCCB0_minigame(omObjData* obj, Vec4f* s, Vec* p, f32 h) {
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
            func_800DC354_minigame(o, &s, (Vec*)&s);
        } else if (g->unk_06 & 0x10) {
            s.x += D_800EBE2C_minigame;
            s.y += D_800EC5D8_minigame;
            func_800DCCB0_minigame(o, &s, (Vec*)&s, w->unk_34 / 2.0f);
        } else if (g->unk_06 & 0x20) {
            s.x += D_800EBE2C_minigame;
            s.y += D_800EC5D8_minigame;
            func_800DC7D8_minigame(o, &s);
        } else if (g->unk_06 & 0x40) {
            s.x += D_800EBE2C_minigame;
            s.y += D_800EC5D8_minigame;
            func_800DC8E4_minigame(o, &s, w->unk_34 / 2.0f);
        } else if (!(g->unk_06 & 2)) {
            func_80021C14_main(*D_800EC1C0_minigame[D_800EB734_minigame]->model, &D_800EBEB0_minigame, func_800DB724_minigame, (HitProbe*)&s);
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
            func_800DC354_minigame(o, (Vec4f*)&s2, (Vec*)&s2.x2);
        } else if (g->unk_06 & 0x10) {
            s2.x += D_800EBE2C_minigame;
            s2.y += D_800EC5D8_minigame;
            func_800DCCB0_minigame(o, (Vec4f*)&s2, (Vec*)&s2.x2, w->unk_34 / 2.0f);
        } else if (g->unk_06 & 0x20) {
            s2.x += D_800EBE2C_minigame;
            s2.y += D_800EC5D8_minigame;
            func_800DC7D8_minigame(o, (Vec4f*)&s2);
        } else if (g->unk_06 & 0x40) {
            s2.x += D_800EBE2C_minigame;
            s2.y += D_800EC5D8_minigame;
            func_800DC8E4_minigame(o, (Vec4f*)&s2, w->unk_34 / 2.0f);
        } else {
            func_80021C14_main(*D_800EC1C0_minigame[i]->model, &D_800EBEB0_minigame, func_800DBCF4_minigame, (HitProbe*)&s2);
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

