#include "common.h"

// d7: matrix inverse and sphere-against-polygon hit tests (MP4 mapspace.c's
// PrecalcPntToTriangle / Hitcheck_Triangle_with_Sphere / Hitcheck_Quadrangle_with_Sphere).

f32 HuVecDot3F(Vec* a, Vec* b);
void HuVecCross(Vec* out, Vec* a, Vec* b);

/* Inverse of an affine matrix (rotation/scale rows 0-2, translation row 3). */
void func_8000D960_main(HuMtx4F src, HuMtx4F dst) {
    f32 ae, af, ah, ai;
    f32 bd, bf, bg, bi;
    f32 cd, ce, cg, ch;
    f32 dh, di, eg, ei, fg, fh;
    f32 inv;

    ae = src[0][0] * src[1][1];
    af = src[0][0] * src[1][2];
    ah = src[0][0] * src[2][1];
    ai = src[0][0] * src[2][2];
    bd = src[0][1] * src[1][0];
    bf = src[0][1] * src[1][2];
    bg = src[0][1] * src[2][0];
    bi = src[0][1] * src[2][2];
    cd = src[0][2] * src[1][0];
    ce = src[0][2] * src[1][1];
    cg = src[0][2] * src[2][0];
    ch = src[0][2] * src[2][1];
    dh = src[1][0] * src[2][1];
    di = src[1][0] * src[2][2];
    eg = src[1][1] * src[2][0];
    ei = src[1][1] * src[2][2];
    fg = src[1][2] * src[2][0];
    fh = src[1][2] * src[2][1];
    inv = 1.0f / ((bf - ce) * src[2][0] + (cd - af) * src[2][1] + (ae - bd) * src[2][2]);
    dst[0][0] = (-fh + ei) * inv;
    dst[0][1] = (ch - bi) * inv;
    dst[0][2] = (-ce + bf) * inv;
    dst[1][0] = (fg - di) * inv;
    dst[1][1] = (-cg + ai) * inv;
    dst[1][2] = (cd - af) * inv;
    dst[2][0] = (-eg + dh) * inv;
    dst[2][1] = (bg - ah) * inv;
    dst[2][2] = (-bd + ae) * inv;
    dst[3][0] = ((di - fg) * src[3][1] + (eg - dh) * src[3][2] + (fh - ei) * src[3][0]) * inv;
    dst[3][1] = ((bi - ch) * src[3][0] + (cg - ai) * src[3][1] + (ah - bg) * src[3][2]) * inv;
    dst[3][2] = ((ce - bf) * src[3][0] + (af - cd) * src[3][1] + (bd - ae) * src[3][2]) * inv;
    dst[0][3] = dst[1][3] = dst[2][3] = 0.0f;
    dst[3][3] = 1.0f;
}

/* Sphere (pos, r) against triangle tri: hit is the triangle's closest point; 1 if within r. */
s32 func_8000DC24_main(f32 tri[3][3], Vec* pos, f32 r, Vec* hit) {
    Vec org;
    Vec u;
    Vec v;
    Vec n;
    Vec p;
    Vec ofs;

    HuVecCopy3F(&org, (Vec*) tri[0]);
    HuVecSubtract(&u, (Vec*) tri[1], (Vec*) tri[0]);
    HuVecSubtract(&v, (Vec*) tri[2], (Vec*) tri[0]);
    HuVecCross(&n, &u, &v);
    HuVecSubtract(&p, pos, (Vec*) tri[0]);
    func_8000DD38_main(&org, &u, &v, &n, &p, &ofs);
    HuVecAdd(hit, &ofs, &org);
    if (HuVecDistance(hit, pos) > r) {
        return 0;
    } else {
        return 1;
    }
}

/* Closest point to p (relative to the triangle's origin) on the triangle spanned by u and v
   (normal n); org is unused. */
s32 func_8000DD38_main(Vec* org, Vec* u, Vec* v, Vec* n, Vec* p, Vec* out) {
    Vec a;
    Vec b;
    Vec unused; /* retail's frame has a third, unreferenced Vec (0x30) */
    f32 inv;
    f32 s;
    f32 t;
    f32 d;

    HuVecCopyXYZ(&a, -p->x, -p->y, -p->z);
    inv = 1.0f / (-(u->z * v->y * n->x) + u->y * v->z * n->x + u->z * v->x * n->y - u->x * v->z * n->y
                  - u->y * v->x * n->z + u->x * v->y * n->z);
    s = (v->z * (n->y * a.x - n->x * a.y) + v->y * (n->x * a.z - n->z * a.x)
         + v->x * (n->z * a.y - n->y * a.z)) * inv;
    t = (u->z * (n->x * a.y - n->y * a.x) + u->y * (n->z * a.x - n->x * a.z)
         + u->x * (n->y * a.z - n->z * a.y)) * inv;
    if ((s > 0.0f) & (t > 0.0f) && s + t > 1.0f) {
        HuVecSubtract(&a, v, u);
        HuVecSubtract(&b, p, u);
        d = HuVecDot3F(&a, &b) / HuVecDot3F(&a, &a);
        if (d <= 0.0f) {
            HuVecCopy3F(out, u);
        } else if (d >= 1.0f) {
            HuVecCopy3F(out, v);
        } else {
            HuVecMulScalar(&b, d, &a);
            HuVecAdd(out, u, &b);
        }
    } else if (t < 0.0f) {
        d = HuVecDot3F(u, p) / HuVecDot3F(u, u);
        if (d <= 0.0f) {
            HuVecCopyXYZ(out, 0.0f, 0.0f, 0.0f);
        } else if (d >= 1.0f) {
            HuVecCopy3F(out, u);
        } else {
            HuVecMulScalar(out, d, u);
        }
    } else if (s < 0.0f) {
        d = HuVecDot3F(v, p) / HuVecDot3F(v, v);
        if (d <= 0.0f) {
            HuVecCopyXYZ(out, 0.0f, 0.0f, 0.0f);
        } else if (d >= 1.0f) {
            HuVecCopy3F(out, v);
        } else {
            HuVecMulScalar(out, d, v);
        }
    } else {
        HuVecCopyXYZ(out, s * u->x + t * v->x, s * u->y + t * v->y, s * u->z + t * v->z);
    }
    return 1;
}

/* Sphere (pos, r) against quad quad (triangles 0-1-2 and 0-2-3): hit is the closer triangle's
   closest point; 1 if within r. */
s32 func_8000E19C_main(f32 quad[4][3], Vec* pos, f32 r, Vec* hit) {
    Vec org;
    Vec u;
    Vec v;
    Vec w;
    Vec n;
    Vec p;
    Vec ofs;
    Vec hitA;
    Vec hitB;
    f32 dist;
    f32 distB;

    HuVecCopy3F(&org, (Vec*) quad[0]);
    HuVecSubtract(&u, (Vec*) quad[1], (Vec*) quad[0]);
    HuVecSubtract(&v, (Vec*) quad[2], (Vec*) quad[0]);
    HuVecSubtract(&w, (Vec*) quad[3], (Vec*) quad[0]);
    HuVecCross(&n, &u, &v);
    HuVecSubtract(&p, pos, (Vec*) quad[0]);
    func_8000DD38_main(&org, &u, &v, &n, &p, &ofs);
    HuVecAdd(&hitA, &ofs, &org);
    func_8000DD38_main(&org, &v, &w, &n, &p, &ofs);
    HuVecAdd(&hitB, &ofs, &org);
    dist = HuVecDistance(&hitA, pos);
    distB = HuVecDistance(&hitB, pos);
    if (dist < distB) {
        HuVecCopy3F(hit, &hitA);
    } else {
        dist = distB;
        HuVecCopy3F(hit, &hitB);
    }
    if (dist > r) {
        return 0;
    } else {
        return 1;
    }
}

/* out = the projection of b onto a. */
void func_8000E344_main(Vec* a, Vec* b, Vec* out) {
    HuVecMulScalar(out, HuVecDot3F(a, b) / HuVecDot3F(a, a), a);
}
