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
extern s32 D_8010D240_fridged_bridges[1]; /* per effect type: model file */
extern omObjFunc D_8010D244_fridged_bridges[1]; /* per effect type: object function */
extern u32 D_8010D248_fridged_bridges[1]; /* per effect type: lifetime */
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010C738_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010CDE4_fridged_bridges);
