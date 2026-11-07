#include "game/camera.h"
#include "mallocblock.h"
#include "include_asm.h"
#include "macros.h"
#include "types.h"

typedef struct Vec2f {
/* 0x00 */ f32 x;
/* 0x04 */ f32 y;
} Vec2f;

// EXTERN
f32 cosdf(f32);
f32 sindf(f32);
void func_8008A0D0_main(Mtx *);

/* The camera a model file may carry (hmfload.c's HmfData_UnkBC). */
typedef struct HmfCamAttach {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ Vec pos;
    /* 0x14 */ Vec at;
    /* 0x20 */ Vec up;
    /* 0x2C */ f32 unk2C;
} HmfCamAttach;

/* hmfload.c's HmfLoadData as far as its camera (pointer slots kept so the host layout agrees). */
typedef struct HmfCamData {
    /* 0x00 */ char unk00[0x2C];
    /* 0x2C */ void *unk2C[4];
    /* 0x3C */ void *unk3C;
    /* 0x40 */ void *unk40;
    /* 0x44 */ void *unk44[3];
    /* 0x50 */ void *unk50[5];
    /* 0x64 */ s16 unk64;
    /* 0x68 */ void *unk68;
    /* 0x6C */ char unk6C[0x14];
    /* 0x80 */ void *unk80[8];
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ f32 unkA4[3];
    /* 0xB0 */ void *unkB0[3];
    /* 0xBC */ HmfCamAttach *camAttach;
} HmfCamData;

extern HuCamera *gCameraList;
extern Vec D_800A0554_main;
extern Vec D_800A0590_main;
extern RectF D_800A05CC_main;
extern s16 D_800C9932_main;
extern HuCamMtxs *D_800D0444_main;
extern HuCamera *D_800D10F4_main;
extern u8 D_800D1FF0_main;
extern u8 D_800D2008_main;
extern s16 D_800D418E_main;

void Hu3DCamInit(u32 arg0) {
    s16 var_s3;
    s16 var_s2;

    D_800C9932_main = arg0;
    D_800D418E_main = 0;
    if (gCameraList != NULL) {
        HuMemFree(gCameraList);
    }
    gCameraList = HuMemAlloc(0xD20);
    for (var_s3 = 0; var_s3 < 6; var_s3++) {
        gCameraList[var_s3].fov[0] = 45.0f;
        gCameraList[var_s3].fov[1] = 80.0f;
        gCameraList[var_s3].fov[2] = 8000.0f;
        gCameraList[var_s3].unk2 = 0;
        gCameraList[var_s3].unk4 = -1;
        CameraViewportSet(var_s3, &D_800A0554_main, &D_800A0590_main);
        CameraScissorSet(var_s3, &D_800A05CC_main);
        gCameraList[var_s3].unkA0 = NULL;
        gCameraList[var_s3].unkA8 = NULL;
        gCameraList[var_s3].unkAC = NULL;
        for (var_s2 = 0; var_s2 < D_800D1FF0_main; var_s2++) {
            func_8008A0D0_main(&gCameraList[var_s3].mtxs[var_s2].perspMtx);
            func_8008A0D0_main(&gCameraList[var_s3].mtxs[var_s2].lookAtMtx);
        }
    }
    D_800D10F4_main = gCameraList;
    D_800D0444_main = gCameraList->mtxs;
}

void func_800123F4_main(void) {
    D_800D418E_main = D_800D2008_main;
}

void Hu3DCamSetPositionOrientation(s16 camIndex, Vec *pos, Vec *at, Vec *up) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->pos = *pos;
    camera->at = *at;
    camera->up = *up;
}

void Hu3DCamSetPerspective(s16 camIndex, f32 fov, f32 near, f32 far) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->fov[0] = fov;
    camera->fov[1] = near;
    camera->fov[2] = far;
    camera->perspNorm = 1;
}

void CameraScissorSet(s16 camIndex, RectF *arg1) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->screenLeft = arg1->x1;
    camera->screenTop = arg1->y1;
    camera->screenRight = arg1->x2;
    camera->screenBottom = arg1->y2;
}

void CameraViewportSet(s16 camIndex, Vec *arg1, Vec *arg2) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->screenScale = *arg1;
    camera->screenPos = *arg2;
}

void Hu3DCamUpdateMtx(s16 camIndex) {
    HuCamera *camera;
    HuCamMtxs *mtxs;

    camera = &gCameraList[camIndex];
    mtxs = &camera->mtxs[D_800D418E_main];

    guPerspective(&mtxs->perspMtx, &camera->perspNorm, camera->fov[0], (SCREEN_WIDTH / SCREEN_HEIGHT), camera->fov[1], camera->fov[2], 1.0f);
    guLookAt(&mtxs->lookAtMtx, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z, camera->up.x, camera->up.y, camera->up.z);
}

void func_80012640_main(s16 camIndex, Gfx **dispList) {
    HuCamMtxs *camMtx;
    HuCamera *camera;

    camera = &gCameraList[camIndex];
    camMtx = &camera->mtxs[D_800D418E_main];
    camera->viewports[D_800D418E_main].vp.vscale[0] = (s16)camera->screenScale.x;
    camera->viewports[D_800D418E_main].vp.vscale[1] = (s16)camera->screenScale.y;
    camera->viewports[D_800D418E_main].vp.vscale[2] = (s16)camera->screenScale.z;
    camera->viewports[D_800D418E_main].vp.vtrans[0] = (s16)camera->screenPos.x;
    camera->viewports[D_800D418E_main].vp.vtrans[1] = (s16)camera->screenPos.y;
    camera->viewports[D_800D418E_main].vp.vtrans[2] = (s16)camera->screenPos.z;

    gSPViewport((*dispList)++, &camera->viewports[D_800D418E_main].vp);
    gSPPerspNormalize((*dispList)++, camera->perspNorm);
    gSPMatrix((*dispList)++, osVirtualToPhysical(&camMtx->perspMtx), G_MTX_PROJECTION | G_MTX_LOAD);
    gSPMatrix((*dispList)++, OS_PHYSICAL_TO_K0(&camMtx->lookAtMtx), G_MTX_LOAD);
}

void func_800127C4_main(s16 camIndex, Gfx **dispList) {
    HuCamera *camera = &gCameraList[camIndex];
    gDPSetScissor((*dispList)++, G_SC_NON_INTERLACE, camera->screenLeft, camera->screenTop, camera->screenRight, camera->screenBottom);
}

void func_80012888_main(s16 camIndex, void (*arg1)(void *, struct HmfModel *), void *arg2) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->unkA0 = arg1;
    camera->unkA4 = arg2;
}

void func_800128BC_main(s16 camIndex, void (*arg1)(s32)) {
    gCameraList[camIndex].unkA8 = arg1;
}

void func_800128EC_main(s16 camIndex, void (*arg1)(s32)) {
    gCameraList[camIndex].unkAC = arg1;
}

void Hu3DCam3DToScreen(s16 camIndex, Vec *worldPos, Vec2f *outPos) {
    f32 x;
    f32 y;
    f32 z;
    f32 projectedX;
    f32 projectedY;
    f32 projectedZ;
    HuCamera *camera;
    HuMtx4F viewMtx;

    camera = &gCameraList[camIndex];
    guLookAtF(
        viewMtx,
        camera->pos.x,
        camera->pos.y,
        camera->pos.z,
        camera->at.x,
        camera->at.y,
        camera->at.z,
        camera->up.x,
        camera->up.y,
        camera->up.z);

    x = worldPos->x;
    y = worldPos->y;
    z = worldPos->z;
    x -= camera->pos.x;
    y -= camera->pos.y;
    z -= camera->pos.z;
    projectedX = ((x * viewMtx[0][0]) + (y * viewMtx[1][0])) + (z * viewMtx[2][0]);
    projectedY = ((x * viewMtx[0][1]) + (y * viewMtx[1][1])) + (z * viewMtx[2][1]);
    projectedZ = ((x * viewMtx[0][2]) + (y * viewMtx[1][2])) + (z * viewMtx[2][2]);
    x = sindf(camera->fov[0] / 2.0f) / cosdf(camera->fov[0] / 2.0f) * projectedZ * ASPECT_RATIO;
    y = (sindf(camera->fov[0] / 2.0f) / cosdf(camera->fov[0] / 2.0f)) * projectedZ;
    outPos->x = (projectedX * (SCREEN_WIDTH_CENTER / (-x))) + SCREEN_WIDTH_CENTER;
    outPos->y = ((projectedY * (SCREEN_HEIGHT_CENTER / y)) + SCREEN_HEIGHT_CENTER);
}

void func_80012B14_main(s16 camIndex, Vec *worldPos, Vec *outPos) {
    f32 x;
    f32 y;
    f32 z;
    f32 projectedX;
    f32 projectedY;
    f32 projectedZ;
    HuCamera *camera;
    HuMtx4F viewMtx;
    f32 f2;
    f32 f4;

    camera = &gCameraList[camIndex];
    guLookAtF(
        viewMtx,
        camera->pos.x,
        camera->pos.y,
        camera->pos.z,
        camera->at.x,
        camera->at.y,
        camera->at.z,
        camera->up.x,
        camera->up.y,
        camera->up.z);

    x = worldPos->x;
    y = worldPos->y;
    z = worldPos->z;
    x -= camera->pos.x;
    y -= camera->pos.y;
    z -= camera->pos.z;
    projectedX = ((x * viewMtx[0][0]) + (y * viewMtx[1][0])) + (z * viewMtx[2][0]);
    projectedY = ((x * viewMtx[0][1]) + (y * viewMtx[1][1])) + (z * viewMtx[2][1]);
    projectedZ = ((x * viewMtx[0][2]) + (y * viewMtx[1][2])) + (z * viewMtx[2][2]);
    x = sindf(camera->fov[0] / 2.0f) / cosdf(camera->fov[0] / 2.0f) * projectedZ * (camera->screenScale.x / camera->screenScale.y);
    y = (sindf(camera->fov[0] / 2.0f) / cosdf(camera->fov[0] / 2.0f)) * projectedZ;
    f2 = camera->screenPos.x / 4.0f;
    outPos->x = (projectedX * (f2 / (-x))) + f2;
    f4 = camera->screenPos.y / 4.0f;
    outPos->y = ((projectedY * (f4 / y)) + f4);
}

/* The camera-space point at depth dist under the screen point in (MP2 func_80020BC4_217C4). */
void func_80012D0C_main(s16 camIndex, f32 dist, Vec2f *in, Vec2f *out) {
    HuMtx4F viewMtx;
    f32 h;
    f32 w;
    f32 ux;
    f32 uy;
    HuCamera *camera;

    camera = &gCameraList[camIndex];
    guLookAtF(
        viewMtx,
        camera->pos.x,
        camera->pos.y,
        camera->pos.z,
        camera->at.x,
        camera->at.y,
        camera->at.z,
        camera->up.x,
        camera->up.y,
        camera->up.z);
    h = sindf(camera->fov[0] / 2.0f) / cosdf(camera->fov[0] / 2.0f) * dist;
    w = h * (4.0f / 3.0f);
    ux = in->x / 320.0f;
    uy = (240.0f - in->y) / 240.0f;
    out->x = 2.0f * w * ux - w;
    out->y = 2.0f * h * uy - h;
}

/* Points camera camIndex along the camera of the model it follows (gCameraList[].unk4): position
   and target from the model's file, up vector perpendicular to the view direction (the direction's
   cross product with itself plus world up, rotated -90 degrees about the direction). */
void func_80012E54_main(s16 camIndex) {
    HmfCamData *hmf;
    HmfCamAttach *cam;
    f32 x;
    f32 y;
    f32 z;
    f32 len;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 angle;
    HuCamera *camera;

    camera = &gCameraList[camIndex];
    hmf = (HmfCamData *) HmfModelData[camera->unk4].hmf;
    if (hmf == NULL) {
        return;
    }
    cam = hmf->camAttach;
    if (cam == NULL) {
        return;
    }
    angle = -90.0f;
    x = cam->at.x - cam->pos.x;
    y = cam->at.y - cam->pos.y;
    z = cam->at.z - cam->pos.z;
    len = x * x + y * y + z * z;
    len = HuSqrtf(len);
    x /= len;
    y /= len;
    z /= len;
    vx = y * z - z * (y + 1.0f);
    vy = z * x - x * z;
    vz = x * (y + 1.0f) - y * x;
    cam->up.x = vx * (x * x + (1.0f - x * x) * cosdf(angle)) +
                vy * (y * x * (1.0f - cosdf(angle)) - z * sindf(angle)) +
                vz * (z * x * (1.0f - cosdf(angle)) + y * sindf(angle));
    cam->up.y = vx * (y * x * (1.0f - cosdf(angle)) + z * sindf(angle)) +
                vy * (y * y + (1.0f - y * y) * cosdf(angle)) +
                vz * (y * z * (1.0f - cosdf(angle)) - x * sindf(angle));
    cam->up.z = vx * (z * x * (1.0f - cosdf(angle)) - y * sindf(angle)) +
                vy * (y * z * (1.0f - cosdf(angle)) + x * sindf(angle)) +
                vz * (z * z + (1.0f - z * z) * cosdf(angle));
    Hu3DCamSetPositionOrientation(camIndex, &cam->pos, &cam->at, &cam->up);
    Hu3DCamUpdateMtx(camIndex);
}

void func_80013320_main(s16 modelIndex, s16 camIndex) {
    gCameraList[camIndex].unk4 = modelIndex;
}

void func_80013350_main(s16 camIndex) {
    gCameraList[camIndex].unk4 = -1;
}
