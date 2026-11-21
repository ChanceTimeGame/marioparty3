#include "ultra64.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "include_asm.h"
#include "fridged_bridges.h"

/* omObjData::data of a player's camera follower (func_8010BE0C_fridged_bridges, 8) */
typedef struct FbCam {
    /* 0x00 */ u16 unk00; /* player */
    /* 0x04 */ omObjData *unk04; /* player object */
} FbCam; // Size 0x8

/* as main 20A20.c: the model data's root transform, at HmfData 0x68 (an N64-offset view, as in main) */
typedef struct HitXform {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec unk08;
    /* 0x14 */ Vec unk14;
    /* 0x20 */ Vec unk20; /* scale */
} HitXform;

typedef struct HmfHitData {
    /* 0x00 */ char unk00[0x68];
    /* 0x68 */ HitXform *xform;
} HmfHitData;

typedef f32 Matrix4f[4][4];

extern s32 D_800C9940_main;
extern s32 D_800D10F4_main;
extern s16 D_800D418E_main;
extern void *MTXBuf;
extern s16 MTXBufNum;
void func_80017C10_main(Mtx *, f32, f32, f32);
void func_80017CD0_main(Matrix4f, f32, f32, f32);
void func_80017D24_main(Matrix4f, f32, f32, f32);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
void guMtxCatF(float m[4][4], float n[4][4], float r[4][4]);

void *HuMemAllocTag(s32 size, s16 tag);
void func_8010BE88_fridged_bridges(omObjData *obj);

extern s16 D_8010CF48_fridged_bridges[4]; /* per player: camera bit */
void func_8010C178_fridged_bridges(omObjData *obj);

s32 D_8010D240_fridged_bridges[1] = { 0x45000C }; /* per effect type: model file */
omObjFunc D_8010D244_fridged_bridges[1] = { func_8010C178_fridged_bridges }; /* per effect type: object function */
u32 D_8010D248_fridged_bridges[1] = { 0x23 }; /* per effect type: lifetime */
extern s16 D_8010DA30_fridged_bridges[1][12]; /* effect models */
extern u16 D_8010DA48_fridged_bridges[1][12]; /* 1 = in use */
extern omObjData *D_8010DA88_fridged_bridges;
extern f32 D_800CCF98_main[];
extern f32 D_800D4198_main[];

void func_8010BDF0_fridged_bridges(void) {
    omOvlReturnEx(1);
}

/* Camera follower for a player */
void func_8010BE0C_fridged_bridges(omObjData *obj) {
    FbPlayer *work = obj->data;
    omObjData *cam;
    FbCam *cw;

    cam = omAddObj(0x32, 0, 0, -1, func_8010BE88_fridged_bridges);
    work->unk2C = cam;
    cw = HuMemAllocTag(sizeof(FbCam), 0x7918);
    cam->data = cw;
    cw->unk00 = work->unk02;
    cw->unk04 = obj;
    cam->work[0] = 0;
}

void func_8010BE88_fridged_bridges(omObjData *obj) {
    FbCam *cw = obj->data;

    if (obj->work[0] != 0) {
        CenterM[cw->unk00].x = cw->unk04->trans.x;
        CenterM[cw->unk00].z = cw->unk04->trans.z;
    }
}

/* Effect model pool */
void func_8010BEE8_fridged_bridges(void) {
    s32 i;
    s32 j;

    D_8010DA88_fridged_bridges = omAddObj(0x3C, 0, 0, -1, NULL);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 12; j++) {
            D_8010DA30_fridged_bridges[i][j] = func_8000B108_main(D_8010D240_fridged_bridges[i], 0x68D);
            D_8010DA48_fridged_bridges[i][j] = 0;
        }
    }
}

/* Start a pooled effect (type 0: water splash) at (x, y, z) in a player's view */
omObjData *func_8010BFD0_fridged_bridges(u16 type, u16 player, f32 x, f32 y, f32 z) {
    omObjData *fx;
    s32 i;
    u16 model;

    for (i = 0; i < 12; i++) {
        if (D_8010DA48_fridged_bridges[type][i] == 0) {
            break;
        }
    }
    if (i == 12) {
        return NULL;
    }
    model = D_8010DA30_fridged_bridges[type][i];
    D_8010DA48_fridged_bridges[type][i] = 1;
    fx = omAddObj(0x3C, 1, 0, -1, D_8010D244_fridged_bridges[type]);
    fx->model[0] = model;
    func_8001C258_main(fx->model[0], 4, 0);
    func_8001C8A8_main(fx->model[0], D_8010CF48_fridged_bridges[player]);
    func_8001C6A8_main(fx->model[0], 0.0f);
    omSetTra(fx, x, y, z);
    omSetSca(fx, 2.0f, 1.0f, 2.0f);
    fx->work[0] = D_8010D248_fridged_bridges[type];
    fx->work[1] = i;
    return fx;
}

void func_8010C178_fridged_bridges(omObjData *obj) {
    if (--obj->work[0] == 0) {
        func_8001C258_main(obj->model[0], 4, 4);
        D_8010DA48_fridged_bridges[0][obj->work[1]] = 0;
        omDelObj(obj);
    }
}

/* Per-player camera: position from centre, rotation and zoom; culling view */
void func_8010C1D8_fridged_bridges(omObjData *obj) {
    Vec pos;
    Vec at;
    Vec up;
    f32 rx;
    f32 ry;
    u8 i;

    for (i = 0; i < obj->work[0]; i++) {
        rx = CRotM[i].x;
        ry = CRotM[i].y;
        pos.x = sindf(ry) * cosdf(rx) * CZoomM[i] + CenterM[i].x;
        pos.y = -sindf(rx) * CZoomM[i] + CenterM[i].y;
        pos.z = cosdf(ry) * cosdf(rx) * CZoomM[i] + CenterM[i].z;
        at.x = CenterM[i].x;
        at.y = CenterM[i].y;
        at.z = CenterM[i].z;
        up.x = sindf(ry) * sindf(rx);
        up.y = cosdf(rx);
        up.z = cosdf(ry) * sindf(rx);
        D_8010DA90_fridged_bridges[i].fan.x = pos.x;
        D_8010DA90_fridged_bridges[i].fan.z = pos.z;
        D_8010DA90_fridged_bridges[i].fan.angle = CRotM[i].y;
        D_8010DA90_fridged_bridges[i].fan.fov = gCameraList[i].fov[0];
        D_8010DA90_fridged_bridges[i].fan.len = D_800CCF98_main[i];
        D_8010DA90_fridged_bridges[i].fan.back = D_800D4198_main[i];
        Hu3DCamSetPositionOrientation(i, &pos, &at, &up);
        Hu3DCamUpdateMtx(i);
    }
}

/* Model matrix for the culled draw (main func_8002087C_main) */
void func_8010C46C_fridged_bridges(HmfModel *m, Matrix4f mtx) {
    Matrix4f tmp;
    HitXform *xf;

    D_800C9940_main = m->unk18;
    guMtxL2F(mtx, (Mtx *)((u8 *)D_800D10F4_main + D_800D418E_main * 0x80 + 0xF0));
    if (m->pos.x != 0.0f || m->pos.y != 0.0f || m->pos.z != 0.0f) {
        func_80017C10_main((Mtx *)mtx, m->pos.x, m->pos.y, m->pos.z);
    }
    if (m->rot.x != 0.0f || m->rot.y != 0.0f || m->rot.z != 0.0f) {
        func_80017D24_main(mtx, m->rot.x, m->rot.y, m->rot.z);
    }
    if (m->scale.x != 1.0f || m->scale.y != 1.0f || m->scale.z != 1.0f) {
        func_80017CD0_main(mtx, m->scale.x, m->scale.y, m->scale.z);
    }
    func_80018044_main((f32(*)[4])m->mtx, mtx, mtx);
    xf = ((HmfHitData *)m->hmf)->xform;
    guMtxIdentF(tmp);
    if (xf->unk08.x == 0.0f || xf->unk08.y == 0.0f || xf->unk08.z == 0.0f) {
        func_80017C10_main((Mtx *)tmp, xf->unk08.x, xf->unk08.y, xf->unk08.z);
    }
    if (xf->unk14.x == 0.0f || xf->unk14.y == 0.0f || xf->unk14.z == 0.0f) {
        func_80017D24_main(tmp, xf->unk14.x, xf->unk14.y, xf->unk14.z);
    }
    if (xf->unk20.x != 1.0f || xf->unk20.y != 1.0f || xf->unk20.z != 1.0f) {
        func_80017CD0_main(tmp, xf->unk20.x, xf->unk20.y, xf->unk20.z);
    }
    guMtxCatF(tmp, mtx, mtx);
    guMtxF2L(mtx, (Mtx *)((u8 *)MTXBuf + MTXBufNum * 0x40));
}

typedef struct ColVtx {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} ColVtx;

/* main 20A20.c's collision grid (D_800D1104_main entries) */
typedef struct HitGrid {
    /* 0x00 */ s32 w;
    /* 0x04 */ s32 h;
    /* 0x08 */ f32 cw;
    /* 0x0C */ f32 ch;
    /* 0x10 */ u16 *polys;
    /* 0x14 */ s16 *map0;
    /* 0x18 */ s16 *map1;
    /* 0x1C */ s16 *map2;
    /* 0x20 */ void *cells;
} HitGrid; /* size = 0x24 */

#define CLAMP_S16(v) if ((v) > 0x7FFF) { (v) = 0x7FFF; } else if ((v) < -0x8000) { (v) = -0x8000; }

extern HitGrid *D_800D1104_main;
void func_80019668_main(HmfModel *arg0);
void func_80024DF0_main(HmfData *, s16, void *, Matrix4f);
s32 func_80021550_main(f32 x, f32 z, ColVtx *v);
void func_8010CDE4_fridged_bridges(u16 list, FbView *view, HmfData *hmf, u16 id);

/* NON_MATCHING: register allocation (masked 0, raw 68): view and model swap saved registers with
   the grid and loop counters, as in main func_80020E94_main (retail view s2, m s3, grid s5). */
#ifdef NON_MATCHING
/* Draw callback (func_80020E94_main with the cells' display lists gathered per grid layer into one
   list each, drawn once per layer) */
void func_8010C738_fridged_bridges(FbView *view, HmfModel *m) {
    ColVtx tri[3];
    Matrix4f mtx;
    Matrix4f ident;
    f32 *fan;
    s16 gi;
    HitGrid *g;
    s32 t;
    s32 x;
    s32 z;
    s32 idx;
    s32 id;
    s32 i;
    f32 x0;
    f32 x1;
    f32 z0;
    f32 z1;
    f32 cw;
    f32 ch;

    fan = &view->fan.fov;
    m->hmf->unkD0 = (s32)m->unkB4;
    if (m->unkB4 != NULL) {
        func_80019668_main(m->unkB4);
    }
    gi = m->unk10;
    func_8010C46C_fridged_bridges(m, mtx);
    guMtxIdentF(ident);
    sindf(view->fan.angle);
    t = (D_800D1104_main[gi].w * D_800D1104_main[gi].cw) / 2.0f;
    cosdf(view->fan.angle);
    tri[0].y = tri[1].y = tri[2].y = 0;
    t = (D_800D1104_main[gi].w * D_800D1104_main[gi].cw) / 2.0f + view->fan.x + sindf(view->fan.angle) * fan[2];
    CLAMP_S16(t);
    tri[0].x = t;
    t = (D_800D1104_main[gi].h * D_800D1104_main[gi].ch) / 2.0f + view->fan.z + cosdf(view->fan.angle) * fan[2];
    CLAMP_S16(t);
    tri[0].z = t;
    t = tri[0].x - sindf(fan[0] / 2.0f + view->fan.angle) * fan[1];
    CLAMP_S16(t);
    tri[1].x = t;
    t = tri[0].z - cosdf(fan[0] / 2.0f + view->fan.angle) * fan[1];
    CLAMP_S16(t);
    tri[1].z = t;
    t = tri[0].x - sindf(view->fan.angle - fan[0] / 2.0f) * fan[1];
    CLAMP_S16(t);
    tri[2].x = t;
    t = tri[0].z - cosdf(view->fan.angle - fan[0] / 2.0f) * fan[1];
    CLAMP_S16(t);
    tri[2].z = t;
    g = &D_800D1104_main[gi];
    cw = g->cw;
    ch = g->ch;
    view->cnt[0] = view->cnt[1] = view->cnt[2] = 0;
    for (z = 0; z < D_800D1104_main[gi].h; z++) {
        z0 = z * ch + m->pos.z;
        z1 = z0 + ch;
        for (x = 0; x < g->w; x++) {
            idx = z * g->w + x;
            x0 = x * cw + m->pos.x;
            x1 = x0 + cw;
            id = g->map0[idx];
            if (id != -1 && (func_80021550_main(x0, z0, tri) == 1 || func_80021550_main(x1, z0, tri) == 1 ||
                             func_80021550_main(x0, z1, tri) == 1 || func_80021550_main(x1, z1, tri) == 1)) {
                func_8010CDE4_fridged_bridges(0, view, m->hmf, id);
            }
            id = g->map1[idx];
            if (id != -1 && (func_80021550_main(x0, z0, tri) == 1 || func_80021550_main(x1, z0, tri) == 1 ||
                             func_80021550_main(x0, z1, tri) == 1 || func_80021550_main(x1, z1, tri) == 1)) {
                func_8010CDE4_fridged_bridges(1, view, m->hmf, id);
            }
            id = g->map2[idx];
            if (id != -1 && (func_80021550_main(x0, z0, tri) == 1 || func_80021550_main(x1, z0, tri) == 1 ||
                             func_80021550_main(x0, z1, tri) == 1 || func_80021550_main(x1, z1, tri) == 1)) {
                func_8010CDE4_fridged_bridges(2, view, m->hmf, id);
            }
        }
    }
    for (i = 0; i < 3; i++) {
        if (view->cnt[i] != 0) {
            gSPEndDisplayList(&view->gfx[i][view->cnt[i]]);
            func_80024DF0_main(&view->hmf[i], 0, (u8 *)MTXBuf + MTXBufNum * 0x40, ident);
        }
    }
    MTXBufNum++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010C738_fridged_bridges);
#endif

/* NON_MATCHING (masked 5, raw 6): retail indexes the count as (view + list * 2)->0x18 in the second
   test; this C forms &view->cnt[list] first. Without the pointer GCC threads the first test's
   branch past the second (retail does not). Same loads, stores and branches otherwise. */
// H0: masked 5: retail addresses cnt as view + list*2 then 24(..); view->cnt[list] spelled out lets GCC thread the second test (masked 11), cnt = view->cnt gives masked 6.
#ifdef NON_MATCHING
/* Add the model data's display list id to grid layer list's display list. Retail adds a list only
   while the layer's list is empty, so each layer draws the first visible cell's list per frame. */
void func_8010CDE4_fridged_bridges(u16 list, FbView *view, HmfData *hmf, u16 id) {
    u16 *cnt;

    if (view->cnt[list] == 0) {
        view->hmf[list] = *hmf;
        ((Gfx **)view->hmf[list].unk3C)[0] = view->gfx[list];
        view->hmf[list].unk10 = 1;
    }
    cnt = &view->cnt[list];
    if (*cnt == 0) {
        gSPDisplayList(&view->gfx[list][*cnt], ((Gfx **)hmf->unk3C)[id]);
        (*cnt)++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010CDE4_fridged_bridges);
#endif
