#include "common.h"
#include "mallocblock.h"

/* Model collision grids and the model matrix, from MP2 src/2E0D0.c (the same code as MP1
   src/29C90.c; MP1 names in the comments). */

typedef f32 Matrix4f[4][4];

typedef struct ColVtx {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} ColVtx;

typedef struct ColTri {
    /* 0x0 */ s16 flags;
    /* 0x2 */ s16 v[3];
} ColTri;

/* One cell of a collision grid: a run of polygons in the grid's polygon stream. */
typedef struct HitCell {
    /* 0x00 */ s32 offset;
    /* 0x04 */ s16 count;
} HitCell; /* size = 0x8 */

/* Collision grid built from a model's hit data (func_8001FF04_main). */
typedef struct HitGrid {
    /* 0x00 */ s32 w;
    /* 0x04 */ s32 h;
    /* 0x08 */ f32 cw;
    /* 0x0C */ f32 ch;
    /* 0x10 */ u16* polys;
    /* 0x14 */ s16* map0;
    /* 0x18 */ s16* map1;
    /* 0x1C */ s16* map2;
    /* 0x20 */ HitCell* cells;
} HitGrid; /* size = 0x24 */

/* Result list of func_80021C14_main (callers declare it as an s32). */
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

/* The model data's root transform (MP1 unk2C0C0Struct40, start). */
typedef struct HitXform {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec unk08;
    /* 0x14 */ Vec unk14;
    /* 0x20 */ Vec unk20; /* scale */
} HitXform;

/* HmfData as these functions read it: the transform at 0x68, inside HmfData's unk64[]. */
typedef struct HmfHitData {
    /* 0x00 */ char unk00[0x68];
    /* 0x68 */ HitXform* xform;
} HmfHitData;

/* Draw-culling view passed by the model draw callbacks (MP1 HitViewFan). */
typedef struct HitViewFan {
    /* 0x00 */ f32 angle;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 fov;
    /* 0x10 */ f32 len;
    /* 0x14 */ f32 back;
} HitViewFan;

/* MP1 HitViewCells: a square of cells around a point. */
typedef struct HitViewCells {
    /* 0x00 */ f32 angle;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 z;
    /* 0x0C */ s32 rx;
    /* 0x10 */ s32 rz;
} HitViewCells;

/* MP1 HitViewCircle: the cells whose centres lie within r of a point. */
typedef struct HitViewCircle {
    /* 0x00 */ f32 angle;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 r;
} HitViewCircle;

extern s16 D_800B19E0_main;
extern s16 D_800B19E2_main;
extern s16 D_800B19E4_main;
extern s16* D_800B19E8_main;
extern HitGrid* D_800D1104_main;
extern s32 D_800C9940_main;
extern s32 D_800D10F4_main;
extern s16 D_800D418E_main;
extern void* MTXBuf;
extern s16 MTXBufNum;

void func_80017CD0_main(Matrix4f, f32, f32, f32); /* MP1 MtxScale */
void func_80017D24_main(Matrix4f, f32, f32, f32); /* MP1 MtxRotate */
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f); /* MP1 MtxMult */
s32 func_800202FC_main(Vec*);
f32 func_80021F98_main(ColVtx*, s16, s16, s16, f32*, f32*);
s32 func_80021550_main(f32, f32, ColVtx*);
void func_80019668_main(HmfModel* arg0);
void func_80024DF0_main(HmfData*, s16, void*, Matrix4f); /* MP1 func_8002D2CC */
void guMtxCatF(float m[4][4], float n[4][4], float r[4][4]); /* guMtxCatF */
int abs(int);

#define CLAMP_S16(v) if ((v) > 0x7FFF) { (v) = 0x7FFF; } else if ((v) < -0x8000) { (v) = -0x8000; }

/* MP1 func_80029090 (src/29C90.c) */
void Hu3DAnimInit(s32 arg0) {
    s16 n = arg0; /* functions.us.h declares the parameter s32; MP1 has s16 n */
    s32 i;

    D_800B19E2_main = 0;
    D_800D1104_main = HuMemAllocTag(n * sizeof(HitGrid), 0x55F0);
    D_800B19E0_main = n;
    D_800B19E8_main = HuMemAllocTag(n * 2, 0x55F0);
    for (i = 0; i < n; i++) {
        D_800B19E8_main[i] = i + 1;
    }
    D_800B19E4_main = 0;
}

/* MP1 func_80029140 (src/29C90.c) */
s32 func_8001FED0_main(s16 idx) {
    return D_800D1104_main[idx].w == D_800D1104_main[idx].h;
}

/* MP1 func_80029174 (src/29C90.c): build a collision grid from a model's MAP1 chunk (big-endian
   bytes, read bytewise). */
s16 func_8001FF04_main(s16 mi) {
    s16 idx;
    u8* p;
    u32 size;
    HitGrid* g;
    HitCell* cell;
    u16 y;
    u16 x;
    u16* dst;
    u32 i;
    union {
        s32 i;
        f32 f;
    } u;

    if (D_800B19E2_main != D_800B19E0_main) {
        idx = D_800B19E4_main;
        D_800B19E4_main = D_800B19E8_main[idx];
        p = (u8*)HmfModelData[mi].hmf->unk38;
        size = ((p[4] << 24) | (p[5] << 16) | (p[6] << 8) | p[7]) - 0x10;
        g = &D_800D1104_main[idx];
        g->w = (p[8] << 8) | p[9];
        g->h = (p[10] << 8) | p[11];
        u.i = (p[16] << 24) | (p[17] << 16) | (p[18] << 8) | p[19];
        g->cw = u.f;
        u.i = (p[20] << 24) | (p[21] << 16) | (p[22] << 8) | p[23];
        g->ch = u.f;
        cell = g->cells = HuMemAllocTag((g->h << 3) * g->w, 0x55F0);
        p += 0x18;
        g->map0 = HuMemAllocTag((g->h << 1) * g->w, 0x55F0);
        g->map1 = HuMemAllocTag((g->h << 1) * g->w, 0x55F0);
        g->map2 = HuMemAllocTag((g->h << 1) * g->w, 0x55F0);
        for (y = 0; y < g->h; y++) {
            for (x = 0; x < g->w; x++) {
                g->map0[y * g->w + x] = (p[0] << 8) | p[1];
                g->map1[y * g->w + x] = (p[2] << 8) | p[3];
                g->map2[y * g->w + x] = (p[4] << 8) | p[5];
                cell->offset = (p[6] << 24) | (p[7] << 16) | (p[8] << 8) | p[9];
                cell->count = (p[10] << 8) | p[11];
                p += 0xC;
                cell++;
                size -= 0xC;
            }
        }
        dst = g->polys = HuMemAllocTag(size, 0x55F0);
        for (i = 0; i < size; i += 2) {
            *dst = (p[0] << 8) | p[1];
            dst++;
            p += 2;
        }
        D_800B19E2_main++;
        return idx;
    }
    return -1;
}

/* MP1 func_80029518 (src/29C90.c) */
f32 func_800202A8_main(f32 angle) {
    if (angle >= 360.0f) {
        angle -= 360.0f;
    } else if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

/* MP1 func_8002956C (src/29C90.c) */
s32 func_800202FC_main(Vec* v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 z = v->z;
    f32 len = HuSqrtf(x * x + y * y + z * z);
    s32 ret = 0;

    if (len != 0.0f) {
        v->x /= len;
        v->y /= len;
        v->z /= len;
        ret = 1;
    }
    return ret;
}

/* MP1 func_800295FC (src/29C90.c) */
void func_8002038C_main(ColVtx* a, ColVtx* b, ColVtx* c, Vec* n) {
    f32 abx = (f32)b->x - (f32)a->x;
    f32 aby = (f32)b->y - (f32)a->y;
    f32 abz = (f32)b->z - (f32)a->z;
    f32 acx = (f32)c->x - (f32)a->x;
    f32 acy = (f32)c->y - (f32)a->y;
    f32 acz = (f32)c->z - (f32)a->z;

    n->x = aby * acz - abz * acy;
    n->y = abz * acx - abx * acz;
    n->z = abx * acy - aby * acx;
    func_800202FC_main(n);
}

/* MP1 func_800296FC (src/29C90.c) */
f32 func_8002048C_main(f32 x, f32 z, ColVtx* a, ColVtx* b) {
    f32 ax = a->x - x;
    f32 az = a->z - z;
    f32 bx = b->x - x;
    f32 bz = b->z - z;

    return -(az * bx - ax * bz);
}

/* MP1 func_80029764 (src/29C90.c) */
f32 func_800204F4_main(f32 x, f32 y, f32 z, ColVtx* verts, ColTri* tri) {
    Vec n;
    Vec p;
    f32 nx;
    f32 ny;
    f32 nz;
    ColVtx* v = &verts[tri->v[0]];

    p.x = v->x;
    p.y = v->y;
    p.z = v->z;
    func_8002038C_main(&verts[tri->v[0]], &verts[tri->v[1]], &verts[tri->v[2]], &n);
    nx = n.x;
    ny = n.y;
    nz = n.z;
    return y + (nx * (p.x - x) + ny * (p.y - y) + nz * (p.z - z)) / ny;
}

/* MP1 func_80029874 (src/29C90.c) */
s32 func_80020604_main(f32 x, f32 z, s16* poly, ColVtx* verts) {
    Vec n;
    s32 cnt;
    s32 i;
    s32 j;

    func_8002038C_main(&verts[poly[1]], &verts[poly[2]], &verts[poly[3]], &n);
    if (n.y == 0.0f) {
        return 0;
    }
    cnt = ((u16)poly[0] >> 14) + 2;
    poly++;
    if (func_8002048C_main(x, z, &verts[poly[0]], &verts[poly[1]]) > 0.0f) {
        for (i = 1; i < cnt; i++) {
            j = (i + 1) % cnt;
            if (func_8002048C_main(x, z, &verts[poly[i]], &verts[poly[j]]) < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < cnt; i++) {
            j = (i + 1) % cnt;
            if (func_8002048C_main(x, z, &verts[poly[i]], &verts[poly[j]]) > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}

/* MP1 (same; MP3 adds 0xF0, not 0xF8) func_80029AEC (src/29C90.c) */
void func_8002087C_main(HmfModel* m, Matrix4f mtx) {
    Matrix4f tmp;
    HitXform* xf;

    D_800C9940_main = m->unk18;
    guMtxL2F(mtx, (Mtx*)((u8*)D_800D10F4_main + D_800D418E_main * 0x80 + 0xF0));
    if (m->pos.x != 0.0f || m->pos.y != 0.0f || m->pos.z != 0.0f) {
        func_80017C10_main((Mtx*)mtx, m->pos.x, m->pos.y, m->pos.z);
    }
    if (m->rot.x != 0.0f || m->rot.y != 0.0f || m->rot.z != 0.0f) {
        func_80017D24_main(mtx, m->rot.x, m->rot.y, m->rot.z);
    }
    if (m->scale.x != 1.0f || m->scale.y != 1.0f || m->scale.z != 1.0f) {
        func_80017CD0_main(mtx, m->scale.x, m->scale.y, m->scale.z);
    }
    func_80018044_main((f32(*)[4])m->mtx, mtx, mtx);
    xf = ((HmfHitData*)m->hmf)->xform;
    guMtxIdentF(tmp);
    if (xf->unk08.x == 0.0f || xf->unk08.y == 0.0f || xf->unk08.z == 0.0f) {
        func_80017C10_main((Mtx*)tmp, xf->unk08.x, xf->unk08.y, xf->unk08.z);
    }
    if (xf->unk14.x == 0.0f || xf->unk14.y == 0.0f || xf->unk14.z == 0.0f) {
        func_80017D24_main(tmp, xf->unk14.x, xf->unk14.y, xf->unk14.z);
    }
    if (xf->unk20.x != 1.0f || xf->unk20.y != 1.0f || xf->unk20.z != 1.0f) {
        func_80017CD0_main(tmp, xf->unk20.x, xf->unk20.y, xf->unk20.z);
    }
    guMtxCatF(tmp, mtx, mtx);
    guMtxF2L(mtx, (Mtx*)((u8*)MTXBuf + MTXBufNum * 0x40));
}

/* MP1 func_80029DB8 (src/29C90.c): draw a square of grid cells around the view point (permuter
   output in MP2). */
void func_80020B48_main(HitViewCells *view, HmfModel *m)
{
  Matrix4f mtx;
  Matrix4f ident;
  s32 *rp;
  s32 x0;
  s32 x1;
  s32 z0;
  s32 z1;
  s32 x;
  s32 z;
  s32 idx;
  s16 id;
  s16 gi;
  m->hmf->unkD0 = (s32)m->unkB4;
  rp = &view->rx;
  if (m->unkB4 != 0)
  {
    func_80019668_main(m->unkB4);
  }
  gi = m->unk10;
  func_8002087C_main(m, mtx);
  guMtxIdentF(ident);
  x = abs((((((D_800D1104_main[gi].w * D_800D1104_main[gi].cw) / 2.0f) + view->x) + m->pos.x) - ((2.0f * sindf(view->angle)) * D_800D1104_main[gi].cw)) / D_800D1104_main[gi].cw);
  z = abs((((((D_800D1104_main[gi].h * D_800D1104_main[gi].ch) / 2.0f) + view->z) + m->pos.z) - ((2.0f * cosdf(view->angle)) * D_800D1104_main[gi].ch)) / D_800D1104_main[gi].ch);
  x0 = x - rp[0];
  x1 = (x + rp[0]) + 1;
  z0 = z - rp[1];
  z1 = (z + rp[1]) + 1;
  if (x0 < 0)
  {
    x0 = 0;
  }
  if (z0 < 0)
  {
    z0 = 0;
  }
  if (D_800D1104_main[gi].w < x1)
  {
    x1 = D_800D1104_main[gi].w;
  }
  if (D_800D1104_main[gi].h < z1)
  {
    z1 = D_800D1104_main[gi].h;
  }
  for (z = z0; z < z1; z++)
  {
    for (x = x0; x < x1; x++)
    {
      idx = (z * D_800D1104_main[gi].w) + x;
      id = D_800D1104_main[gi].map0[idx];
      if (id != (-1))
      {
        func_80024DF0_main(m->hmf, id, ((u8 *) MTXBuf) + (MTXBufNum * 0x40), mtx);
      }
      id = D_800D1104_main[gi].map1[idx];
      if (id != (-1))
      {
        func_80024DF0_main(m->hmf, id, ((u8 *) MTXBuf) + (MTXBufNum * 0x40), mtx);
      }
      id = D_800D1104_main[gi].map2[idx];
      if (id != (-1))
      {
 do { func_80024DF0_main(m->hmf, id, ((u8 *) MTXBuf) + (MTXBufNum * 0x40), mtx); } while (0);
      }
    }

  }

  MTXBufNum++;
}

/* NON_MATCHING: register allocation (masked 0, raw 45): view and model swap saved registers, as in
   MP1 (retail m s1, view s2, fan s3). Setting fan first fixed the fan[2] load; declaration order did
   not move the rest. */
#ifdef NON_MATCHING
/* MP1 func_8002A0E4 (src/29C90.c, NON_MATCHING there): draw the grid cells inside the view fan.
   MP2 first hands the model's lights to its data. */
void func_80020E94_main(HitViewFan* view, HmfModel* m) {
    ColVtx tri[3];
    Matrix4f mtx;
    Matrix4f ident;
    f32* fan;
    s16 gi;
    s32 t;
    s32 x;
    s32 z;
    s32 idx;
    s32 id;
    f32 x0;
    f32 x1;
    f32 z0;
    f32 z1;

    fan = &view->fov;
    m->hmf->unkD0 = (s32)m->unkB4;
    if (m->unkB4 != NULL) {
        func_80019668_main(m->unkB4);
    }
    gi = m->unk10;
    func_8002087C_main(m, mtx);
    guMtxIdentF(ident);
    sindf(view->angle);
    t = (D_800D1104_main[gi].w * D_800D1104_main[gi].cw) / 2.0f;
    cosdf(view->angle);
    tri[0].y = tri[1].y = tri[2].y = 0;
    t = (D_800D1104_main[gi].w * D_800D1104_main[gi].cw) / 2.0f + view->x + sindf(view->angle) * fan[2];
    CLAMP_S16(t);
    tri[0].x = t;
    t = (D_800D1104_main[gi].h * D_800D1104_main[gi].ch) / 2.0f + view->z + cosdf(view->angle) * fan[2];
    CLAMP_S16(t);
    tri[0].z = t;
    t = tri[0].x - sindf(fan[0] / 2.0f + view->angle) * fan[1];
    CLAMP_S16(t);
    tri[1].x = t;
    t = tri[0].z - cosdf(fan[0] / 2.0f + view->angle) * fan[1];
    CLAMP_S16(t);
    tri[1].z = t;
    t = tri[0].x - sindf(view->angle - fan[0] / 2.0f) * fan[1];
    CLAMP_S16(t);
    tri[2].x = t;
    t = tri[0].z - cosdf(view->angle - fan[0] / 2.0f) * fan[1];
    CLAMP_S16(t);
    tri[2].z = t;
    for (z = 0; z < D_800D1104_main[gi].h; z++) {
        z0 = z * D_800D1104_main[gi].ch + m->pos.z;
        z1 = z0 + D_800D1104_main[gi].ch;
        for (x = 0; x < D_800D1104_main[gi].w; x++) {
            idx = z * D_800D1104_main[gi].w + x;
            x0 = x * D_800D1104_main[gi].cw + m->pos.x;
            x1 = x0 + D_800D1104_main[gi].cw;
            id = D_800D1104_main[gi].map0[idx];
            if (id != -1 && (func_80021550_main(x0, z0, tri) == 1 || func_80021550_main(x1, z0, tri) == 1 ||
                             func_80021550_main(x0, z1, tri) == 1 || func_80021550_main(x1, z1, tri) == 1)) {
                func_80024DF0_main(m->hmf, id, (u8*)MTXBuf + MTXBufNum * 0x40, ident);
            }
            id = D_800D1104_main[gi].map1[idx];
            if (id != -1 && (func_80021550_main(x0, z0, tri) == 1 || func_80021550_main(x1, z0, tri) == 1 ||
                             func_80021550_main(x0, z1, tri) == 1 || func_80021550_main(x1, z1, tri) == 1)) {
                func_80024DF0_main(m->hmf, id, (u8*)MTXBuf + MTXBufNum * 0x40, mtx);
            }
            id = D_800D1104_main[gi].map2[idx];
            if (id != -1 && (func_80021550_main(x0, z0, tri) == 1 || func_80021550_main(x1, z0, tri) == 1 ||
                             func_80021550_main(x0, z1, tri) == 1 || func_80021550_main(x1, z1, tri) == 1)) {
                func_80024DF0_main(m->hmf, id, (u8*)MTXBuf + MTXBufNum * 0x40, mtx);
            }
        }
    }
    MTXBufNum++;
}
#else
INCLUDE_ASM("asm/nonmatchings/20A20", func_80020E94_main);
#endif

/* MP1 func_8002A784 (src/29C90.c) */
s32 func_80021550_main(f32 x, f32 z, ColVtx* v) {
    s32 i;
    s32 j;
    f32 f;

    if (func_8002048C_main(x, z, &v[0], &v[1]) > 0.0f) {
        for (i = 1; i < 3; i++) {
            j = (i + 1) % 3;
            f = func_8002048C_main(x, z, &v[i], &v[j]);
            if (f == 0.0f) {
                return 1;
            }
            if (f < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < 3; i++) {
            j = (i + 1) % 3;
            f = func_8002048C_main(x, z, &v[i], &v[j]);
            if (f == 0.0f) {
                return 1;
            }
            if (f > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}

/* MP1 func_8002A92C (src/29C90.c): draw the grid cells whose centres lie within r of the view point.
   MP2 first hands the model's lights to its data. */
void func_800216F8_main(HitViewCircle* view, HmfModel* m) {
    Matrix4f mtx;
    Matrix4f ident;
    f32* rp;
    s16 gi;
    s32 x0;
    s32 x1;
    s32 z0;
    s32 z1;
    s32 x;
    s32 z;
    s32 idx;
    unsigned int id;
    f32 dx;
    f32 dz;

    rp = &view->r;
    m->hmf->unkD0 = (s32)m->unkB4;
    if (m->unkB4 != NULL) {
        func_80019668_main(m->unkB4);
    }
    gi = m->unk10;
    func_8002087C_main(m, mtx);
    guMtxIdentF(ident);
    x0 = ((view->x - *rp) + ((D_800D1104_main[gi].w * D_800D1104_main[gi].cw) / 2.0f)) / D_800D1104_main[gi].cw;
    x1 = ((view->x + *rp) + ((D_800D1104_main[gi].w * D_800D1104_main[gi].cw) / 2.0f)) / D_800D1104_main[gi].cw;
    z0 = ((view->z - *rp) + ((D_800D1104_main[gi].h * D_800D1104_main[gi].ch) / 2.0f)) / D_800D1104_main[gi].ch;
    z1 = ((view->z + *rp) + ((D_800D1104_main[gi].h * D_800D1104_main[gi].ch) / 2.0f)) / D_800D1104_main[gi].ch;
    if (x0 < 0) {
        x0 = 0;
    }
    if (z0 < 0) {
        z0 = 0;
    }
    if (D_800D1104_main[gi].w < x1) {
        x1 = D_800D1104_main[gi].w;
    }
    if (D_800D1104_main[gi].h < z1) {
        z1 = D_800D1104_main[gi].h;
    }
    for (z = z0; z < z1; z++) {
        dz = (((z * D_800D1104_main[gi].ch) + m->pos.z) + (D_800D1104_main[gi].ch / 2.0f)) -
             (((D_800D1104_main[gi].h * D_800D1104_main[gi].ch) / 2.0f) + view->z);
        for (x = x0; x < x1; x++) {
            dx = (((x * D_800D1104_main[gi].cw) + m->pos.x) + (D_800D1104_main[gi].cw / 2.0f)) -
                 (((D_800D1104_main[gi].w * D_800D1104_main[gi].cw) / 2.0f) + view->x);
            if (HuSqrtf((dx * dx) + (dz * dz)) < *rp) {
                idx = (z * D_800D1104_main[gi].w) + x;
                id = D_800D1104_main[gi].map0[idx];
                if (id != -1) {
                    func_80024DF0_main(m->hmf, id, (u8*)MTXBuf + MTXBufNum * 0x40, mtx);
                }
                id = D_800D1104_main[gi].map1[idx];
                if (id != -1) {
                    func_80024DF0_main(m->hmf, id, (u8*)MTXBuf + MTXBufNum * 0x40, mtx);
                }
                id = D_800D1104_main[gi].map2[idx];
                if (id != -1) {
                    func_80024DF0_main(m->hmf, id, (u8*)MTXBuf + MTXBufNum * 0x40, mtx);
                }
            }
        }
    }
    MTXBufNum++;
}

/* MP1 func_8002AD04 (src/29C90.c) */
void func_80021AF4_main(void) {
    HuMemFreeAllWithTag(0x55F0);
    D_800B19E0_main = 0;
    D_800B19E2_main = 0;
}

/* MP1 func_8002AD30 (src/29C90.c) */
void func_80021B20_main(s16 idx) {
    HitGrid* g;

    if (D_800B19E2_main != 0) {
        g = &D_800D1104_main[idx];
        HuMemFree(g->cells);
        HuMemFree(g->map0);
        HuMemFree(g->map1);
        HuMemFree(g->map2);
        HuMemFree(g->polys);
        D_800B19E2_main--;
        D_800B19E8_main[idx] = D_800B19E4_main;
        D_800B19E4_main = idx;
    }
}

/* MP1 func_8002ADF0 (src/29C90.c) */
void func_80021BE0_main(s32* arg0, s32 n) {
    ((HitList*)arg0)->list = HuMemAllocTag((u16)n * sizeof(u16*), 0x55F0);
}

/* MP1 func_8002AE24 (NON_MATCHING there): collect the polygons near the probe that cb accepts
   (permuter output in MP2). */
void func_80021C14_main(s16 mi, HitList *l, s32 (*cb)(s32, u16 *, ColVtx *, HitProbe *), HitProbe *probe)
{
  s32 x0;
  s32 z1;
  HmfData *mdl;
  HmfModel *m;
  HitGrid *g;
  HitCell *cell;
  u16 **out;
  u16 *p;
  s32 x1;
  s32 z0;
  s32 x;
  s32 z;
  char new_var;
  s32 i;
  l->pos = 0;
  l->count = 0;
  mdl = (HmfModelData + mi)->hmf;
  m = HmfModelData + mi;
  g = &D_800D1104_main[m->unk10];
  x = (((g->w * g->cw) / 2.0f) + probe->x) / g->cw;
  z = (((g->h * g->ch) / 2.0f) + probe->z) / g->ch;
  x0 = x - 1;
  x1 = x + 2;
  z0 = z - 1;
  z1 = z + 2;
  if (x0 < 0)
  {
    x0 = 0;
  }
  if (z0 < 0)
  {
    z0 = 0;
  }
  if (g->w < x1)
  {
    x1 = g->w;
  }
  if (g->h < z1)
  {
    z1 = g->h;
  }
  out = l->list;
  for (z = z0; z < z1; z++)
  {
    for (x = x0; x < x1; x++)
    {
      cell = &g->cells[(z * g->w) + x];
      if (cell->count != 0)
      {
        p = &g->polys[cell->offset];
        for (i = 0; i < cell->count; i++)
        {
          new_var = ((*p) >> 14) + 2;
          if (cb(new_var, p + 1, mdl->unk50, probe) != 0)
          {
            *(out++) = p;
            l->count++;
          }
          p += ((*p) >> 14) + 3;
        }

      }
    }

  }

}

/* MP1 func_8002B074 (src/29C90.c) */
s32 func_80021E64_main(u16 n, s16* idx, ColVtx* verts, HitProbe* probe) {
    f32 cx;
    f32 cz;
    f32 r;

    if (n == 4) {
        r = func_80021F98_main(verts, idx[0], idx[2], idx[3], &cx, &cz) + probe->r;
        cx -= probe->x;
        cz -= probe->z;
        if (cx * cx + cz * cz < r * r) {
            return 1;
        }
    }
    r = func_80021F98_main(verts, idx[0], idx[1], idx[2], &cx, &cz) + probe->r;
    cx -= probe->x;
    cz -= probe->z;
    return cx * cx + cz * cz < r * r;
}

/* MP1 func_8002B1A8 (src/29C90.c) */
f32 func_80021F98_main(ColVtx* verts, s16 a, s16 b, s16 c, f32* cx, f32* cz) {
    f32 dx;
    f32 dz;
    f32 ex;
    f32 ez;

    *cx = (verts[a].x + verts[b].x + verts[c].x) / 3;
    *cz = (verts[a].z + verts[b].z + verts[c].z) / 3;
    dx = verts[a].x - *cx;
    dz = verts[a].z - *cz;
    ex = verts[b].x - *cx;
    ez = verts[b].z - *cz;
    if (dx * dx + dz * dz < ex * ex + ez * ez) {
        dx = ex;
        dz = ez;
    }
    ex = verts[c].x - *cx;
    ez = verts[c].z - *cz;
    if (dx * dx + dz * dz < ex * ex + ez * ez) {
        dx = ex;
        dz = ez;
    }
    return HuSqrtf(dx * dx + dz * dz);
}

/* MP1 func_8002B3A8 (src/29C90.c) */
u16* func_80022198_main(HitList* l) {
    if (l->pos != l->count) {
        return l->list[l->pos++];
    }
    return NULL;
}

/* MP1 func_8002B3DC (src/29C90.c) */
void func_800221CC_main(HitList* l, s32 off, u16 mode) {
    s32 t;

    switch (mode) {
        case 0:
            if (off >= 0 && off + l->pos < l->count) {
                l->pos = off;
            }
            break;
        case 1:
            if (off + l->pos >= 0 && off + l->pos < l->count) {
                l->pos += off;
            }
            break;
        case 2:
            if (off <= 0 && off + l->pos >= 0) {
                t = off + 0xFFFF; /* == off - 1 as a u16 */
                l->pos = l->count + t;
            }
            break;
    }
}

/* MP1 func_8002B498 (src/29C90.c) */
void func_80022288_main(HitList* l) {
    HuMemFree(l->list);
}
