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
    /* 0x00 */ u8 unk_00[0x20]; /* per ground object flags: 1 ignore it, 2 keep the height, 8 hazard */
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
    /* 0x56 */ u8 unk_56;   /* surface id of the ceiling (GroundWork.unk_04) */
    /* 0x57 */ char unk_57[0x35];
    /* 0x8C */ f32 unk_8C;  /* ceiling height, 65536.0f none */
    /* 0x90 */ f32 unk_90;  /* ground velocity */
    /* 0x94 */ f32 unk_94;
    /* 0x98 */ f32 unk_98;
    /* 0x9C */ f32 unk_9C;
    /* 0xA0 */ f32 unk_A0;
    /* 0xA4 */ f32 unk_A4;
    /* 0xA8 */ char unk_A8[0xC];
    /* 0xB4 */ f32 unk_B4;  /* speed factor */
} MgWork;

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

/* AB1C0 (fork B) */
void func_800DCCB0_minigame(omObjData* g, Vec4f* p, Vec* save, f32 h);
s32 func_800DD530_minigame(omObjData* obj, Vec4f* p, f32 arg2);
void func_800DDB60_minigame(omObjData* obj, Vec* n);
void func_800DFCDC_minigame(f32 dx, f32 dz, f32 d);
void func_800E0430_minigame(f32 nx, f32 ny, f32 nz);
void func_800E048C_minigame(f32 x, f32 y, f32 z);
/* B3CE0, B63A0, B7600 */
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
extern f32 D_800EB778_minigame;
extern f32 D_800EB77C_minigame;

extern Vec D_800EBDD0_minigame;          /* reference point for the face-side test */
extern u16 D_800EBE28_minigame;          /* ground object count */
extern f32 D_800EBE2C_minigame;          /* push x this frame */
extern f32 D_800EBE30_minigame[4][4];    /* ground object: world to local */
extern HitList D_800EBEB0_minigame;      /* face query */
extern Vec D_800EBEB8_minigame[];        /* contact points */
extern omObjData* D_800EC1C0_minigame[]; /* ground objects */
extern f32 D_800EC240_minigame[4][4];    /* ground object: local to world */
extern Vec D_800EC298_minigame[];        /* contact normals */
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

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA768_minigame);


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

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DCA34_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DCCB0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DD1F4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DD530_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDB60_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDD70_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDD94_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFCDC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFD48_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFD9C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFE44_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFF3C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800E0430_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800E048C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800E04C8_minigame);
