#include "common.h"
#include "game/camera.h"
#include "mallocblock.h"

extern f32 D_800CB890_main;
extern f32 D_800CCF98_main[];
extern f32 D_800CE17C_main[];
extern f32 D_800D04B8_main[][6];
extern f32 D_800D4198_main[];
extern f32 D_800D5210_main;
extern omObjData *D_800CE194_main;
extern s32 D_800D6AB8_main;

void func_8004CF00_main(omObjData *);

/* Camera-anchored 2D objects, a frame timer and the sound-fade object (MP2 src/7AA60.c). */

/* The work block of a camera-anchored 2D object (func_8004B7B0_main: one camera,
   func_8004B984_main: one per camera): a sprite drawn by `draw` at the screen position of a
   point on a plane, scaled with the camera distance. */
typedef struct CamSprWork {
    /* 0x00 */ s16 sprId;
    /* 0x04 */ f32 scaleX;     // baseScaleX * baseZoom / current distance
    /* 0x08 */ f32 scaleY;
    /* 0x0C */ f32 baseScaleX; // screenScale.x / 640
    /* 0x10 */ f32 baseScaleY; // screenScale.y / 480
    /* 0x14 */ f32 baseZoom;   // camera distance at creation
    /* 0x18 */ f32 offsetX;    // screen offset of the plane point since creation
    /* 0x1C */ f32 offsetY;
    /* 0x20 */ Vec planePos;   // where the view ray met the plane at creation
    /* 0x2C */ void (*draw)(struct CamSprWork*);
    /* 0x30 */ HuCamera* cam;
} CamSprWork; /* size 0x34 */

/* Per-slot sound fades (func_8004CF30_main / func_8004D094_main), one entry per sound slot. */
typedef struct SndFadeWork {
    /* 0x00 */ f32* vol;      // flag 1: fade out, then stop the slot
    /* 0x04 */ f32* volStep;
    /* 0x08 */ f32* vol2;     // flag 4 (with flag 2): fade to silence, keep playing
    /* 0x0C */ f32* vol2Step;
    /* 0x10 */ u8* flags;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ char unk2C[8];
    /* 0x34 */ s16 unk34;
} SndFadeWork; /* size 0x38 */

extern Gfx* gMainGfxPos;
extern Vec D_800D6A78_main;    /* plane normal for the one-camera object */
extern Vec D_800CD2A8_main[4]; /* plane normals, one per camera */
extern omObjData* D_800D6A40_main;
extern str800D5298 D_800D1398_main;
extern s16 D_800A1910_main; /* sound slot count (audio.c declares it s16[8]) */
extern u16 D_800D530C_main;

void func_80012B14_main(s16 camIndex, Vec* worldPos, Vec2f* outPos);
double fabs(double); /* the GCC builtin (abs.d) */

void func_8004B7B0_main(s32 prio, s16 sprId, void (*draw)(CamSprWork*), f32 fov, Vec* eye, Vec* at);
void func_8004B984_main(u8 count, s32 prio, u16* sprIds, void (*draw)(CamSprWork*), f32 fov, Vec* eye, Vec* at);
void func_8004BC00_main(void);
void func_8004BCE4_main(CamSprWork* work);
void func_8004C4C4_main(omObjData* obj);
void func_8004C76C_main(omObjData* obj);
void func_8004CB44_main(Vec* out, Vec* normal);
void func_8004CD04_main(Vec* eye, Vec* at, f32* zoom, Vec* rot, Vec* center);
void func_8004D094_main(omObjData* obj);

void omOutView(omObjData *object) {
    Vec pos, at, up;
    f32 rot_x = CRot.x;
    f32 rot_y = CRot.y;

    pos.x = Center.x + sindf(rot_y) * cosdf(rot_x) * CZoom;
    pos.y = Center.y + -sindf(rot_x) * CZoom;
    pos.z = Center.z + cosdf(rot_y) * cosdf(rot_x) * CZoom;
    at.x = Center.x;
    at.y = Center.y;
    at.z = Center.z;
    up.x = sindf(rot_y) * sindf(rot_x);
    up.y = cosdf(rot_x);
    up.z = cosdf(rot_y) * sindf(rot_x);
    D_800CE17C_main[0] = pos.x;
    D_800CE17C_main[1] = pos.z;
    D_800CE17C_main[-1] = CRot.y; // actually D_800CE178_main?
    D_800CE17C_main[2] = gCameraList->fov[0];
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
}

void omOutViewMulti(omObjData *object) {
    u8 i;

    for (i = 0; i < object->work[0]; i++) {
        Vec pos, at, up;
        f32 rot_x = CRotM[i].x;
        f32 rot_y = CRotM[i].y;

        pos.x = CenterM[i].x + sindf(rot_y) * cosdf(rot_x) * CZoomM[i];
        pos.y = CenterM[i].y + -sindf(rot_x) * CZoomM[i];
        pos.z = CenterM[i].z + cosdf(rot_y) * cosdf(rot_x) * CZoomM[i];
        at.x = CenterM[i].x;
        at.y = CenterM[i].y;
        at.z = CenterM[i].z;
        up.x = sindf(rot_y) * sindf(rot_x);
        up.y = cosdf(rot_x);
        up.z = cosdf(rot_y) * sindf(rot_x);
        D_800D04B8_main[i][1] = pos.x;
        D_800D04B8_main[i][2] = pos.z;
        D_800D04B8_main[i][0] = CRotM[i].y;
        D_800D04B8_main[i][3] = gCameraList[i].fov[0];
        D_800D04B8_main[i][4] = D_800CCF98_main[i];
        D_800D04B8_main[i][5] = D_800D4198_main[i];
        Hu3DCamSetPositionOrientation(i, &pos, &at, &up);
        Hu3DCamUpdateMtx(i);
    }
}

void func_8004B760_main(s32 prio, s32 sprId, void (*draw)(CamSprWork*), f32 fov, Vec* eye, Vec* at) {
    D_800D6A78_main.x = 0.0f;
    D_800D6A78_main.y = 1.0f;
    D_800D6A78_main.z = 0.0f;
    func_8004B7B0_main(prio, sprId, draw, fov, eye, at);
}

void func_8004B7B0_main(s32 prio, s16 sprId, void (*draw)(CamSprWork*), f32 fov, Vec* eye, Vec* at) {
    Mtx unused; /* retail's frame has 0x40 bytes of unused locals */
    omObjData* obj;
    CamSprWork* work;
    HuCamera* cam;

    obj = omAddObj(prio, 0, 0, -1, func_8004C4C4_main);
    omSetStatBit(obj, 0xA0);
    work = HuMemAllocTag(sizeof(CamSprWork), 0x7918);
    obj->data = work;
    work->draw = draw;
    work->sprId = sprId;
    func_8004CD04_main(eye, at, &CZoom, &CRot, &Center);
    Hu3DCamSetPerspective(0, fov, 80.0f, 8000.0f);
    cam = gCameraList;
    func_8004CB44_main(&work->planePos, &D_800D6A78_main);
    work->baseZoom = CZoom;
    work->baseScaleX = cam->screenScale.x / 640.0f;
    work->baseScaleY = cam->screenScale.y / 480.0f;
    work->scaleX = work->baseScaleX;
    work->scaleY = work->baseScaleY;
    work->cam = cam;
}

/* One camera-anchored 2D object per camera (count cameras), each plane the floor. */
void func_8004B904_main(s32 count, s32 prio, u16* sprIds, void (*draw)(CamSprWork*), f32 fov, Vec* eye, Vec* at) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800CD2A8_main[i].x = 0.0f;
        D_800CD2A8_main[i].y = 1.0f;
        D_800CD2A8_main[i].z = 0.0f;
    }
    func_8004B984_main(count, prio, sprIds, draw, fov, eye, at);
}

void func_8004B984_main(u8 count, s32 prio, u16* sprIds, void (*draw)(CamSprWork*), f32 fov, Vec* eye, Vec* at) {
    Mtx unused; /* retail's frame has 0x40 bytes of unused locals */
    omObjData* obj;
    CamSprWork* work;
    HuCamera* cam;
    s32 i;
    f32 near, far;

    obj = omAddObj(prio, 0, 0, -1, func_8004C76C_main);
    omSetStatBit(obj, 0xA0);
    obj->data = HuMemAllocTag(count * sizeof(CamSprWork), 0x7918);
    work = obj->data;
    func_8004CD04_main(eye, at, &CZoom, &CRot, &Center);
    near = 80.0f;
    far = 8000.0f;
    obj->work[0] = count;
    for (i = 0; i < count; i++, work++) {
        Hu3DCamSetPerspective(i, fov, near, far);
        work->draw = draw;
        work->sprId = sprIds[i];
        CZoomM[i] = CZoom;
        CRotM[i] = CRot;
        CenterM[i] = Center;
        cam = &gCameraList[i];
        func_8004CB44_main(&work->planePos, &D_800CD2A8_main[i]);
        work->baseZoom = CZoom;
        work->baseScaleX = cam->screenScale.x / 640.0f;
        work->baseScaleY = cam->screenScale.y / 480.0f;
        work->scaleX = work->baseScaleX;
        work->scaleY = work->baseScaleY;
        work->cam = cam;
    }
}

/* Render state for the objects' sprites. */
void func_8004BC00_main(void) {
    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetCombineLERP(gMainGfxPos++, TEXEL0, 0, TEXEL0_ALPHA, 0, TEXEL0, 0, PRIM_LOD_FRAC, 0, TEXEL0, 0,
                      TEXEL0_ALPHA, 0, TEXEL0, 0, PRIM_LOD_FRAC, 0);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
}

/* The objects' default sprite draw: an 8-bit CI sprite with a 256-colour palette, centred in the
   camera's viewport (scaled and offset by the object), loaded and drawn in horizontal strips of
   as many rows as fit in 2 KB of TMEM. */
void func_8004BCE4_main(CamSprWork* work) {
    HuSprite* spr;
    HuCamera* cam;
    u16 w, h, rows;
    s16 left, top, right, bottom;
    f32 halfW, halfH;
    f32 x0, y0, x1, y1;
    f32 step, next;
    s32 s;

    spr = HuSprGet(work->sprId, 0);
    w = spr->unk_84->unk14;
    h = spr->unk_84->unk16;
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gMainGfxPos++, spr->unk_84->unk0C);
    cam = work->cam;
    left = cam->screenLeft;
    top = cam->screenTop;
    right = cam->screenRight;
    bottom = cam->screenBottom;
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, left, top, right, bottom);
    halfW = (w / 2.0f) * work->scaleX;
    halfH = (h / 2.0f) * work->scaleY;
    x0 = (right - left) / 2.0f - halfW - work->offsetX + left;
    y0 = (bottom - top) / 2.0f - halfH - work->offsetY + top;
    x1 = (right - left) / 2.0f + halfW - work->offsetX + left;
    y1 = (bottom - top) / 2.0f + halfH - work->offsetY + top;
    rows = 0x800 / w - 1;
    x1 -= 1.0f;
    y1 -= 1.0f;
    step = (f32)fabs((f64)y1 - (f64)y0) / (u16)(h / rows);
    for (s = 0; s < h - 1; s += rows) {
        next = y0 + step;
        if (s + rows >= h - 1) {
            rows = h - s - 1;
        }
        if (top <= next) {
            if (y1 < next) {
                step = y1 - y0;
            }
            gDPLoadTextureTile(gMainGfxPos++, spr->unk_84->unk08, G_IM_FMT_CI, G_IM_SIZ_8b, w, h, 0, s, w,
                               s + rows, 0, 0, 0, 0, 0, 0, 0);
            gSPScisTextureRectangle(gMainGfxPos++, (s32)(x0 * 4.0f), (s32)(y0 * 4.0f), (s32)(x1 * 4.0f),
                                    (s32)((y0 + step) * 4.0f), G_TX_RENDERTILE, 0, s << 5,
                                    (s32)(1024.0f / work->scaleX), (s32)(1024.0f / work->scaleY));
        }
        y0 += step;
        if (bottom <= y0) {
            break;
        }
    }
}

/* Object function of func_8004B7B0_main: camera 0 from CRot/CZoom/Center (as omOutView), then
   the sprite's scale and screen offset, and its draw callback. */
void func_8004C4C4_main(omObjData* obj) {
    Vec pos, at, up;
    Vec planePos;
    Vec2f scr0, scr1;
    CamSprWork* work = obj->data;
    f32 rot_x = CRot.x;
    f32 rot_y = CRot.y;
    f32 dist;

    pos.x = Center.x + sindf(rot_y) * cosdf(rot_x) * CZoom;
    pos.y = Center.y + -sindf(rot_x) * CZoom;
    pos.z = Center.z + cosdf(rot_y) * cosdf(rot_x) * CZoom;
    at.x = Center.x;
    at.y = Center.y;
    at.z = Center.z;
    up.x = sindf(rot_y) * sindf(rot_x);
    up.y = cosdf(rot_x);
    up.z = cosdf(rot_y) * sindf(rot_x);
    D_800CE17C_main[0] = pos.x;
    D_800CE17C_main[1] = pos.z;
    D_800CE17C_main[-1] = CRot.y;
    D_800CE17C_main[2] = gCameraList->fov[0];
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
    dist = HuSqrtf((Center.x - pos.x) * (Center.x - pos.x) +
                               (Center.y - pos.y) * (Center.y - pos.y) +
                               (Center.z - pos.z) * (Center.z - pos.z));
    work->scaleX = (work->baseZoom / dist) * work->baseScaleX;
    work->scaleY = (work->baseZoom / dist) * work->baseScaleY;
    func_8004CB44_main(&planePos, &D_800D6A78_main);
    func_80012B14_main(0, &planePos, &scr0);
    func_80012B14_main(0, &work->planePos, &scr1);
    work->offsetX = (scr0.x - scr1.x) * work->baseScaleX;
    work->offsetY = (scr0.y - scr1.y) * work->baseScaleY;
    if (work->draw != NULL) {
        func_8004BC00_main();
        work->draw(work);
        gSPEndDisplayList(gMainGfxPos++);
    }
}

/* Object function of func_8004B984_main: the same for each of its cameras (omOutViewMulti).
   Retail projects every camera's plane point through camera 0 (func_80012B14_main's first
   argument). */
void func_8004C76C_main(omObjData* obj) {
    Vec pos, at, up;
    Vec planePos;
    Vec2f scr0, scr1;
    CamSprWork* work = obj->data;
    s32 i;
    f32 rot_x, rot_y;
    f32 dist;

    func_8004BC00_main();
    for (i = 0; i < obj->work[0]; i++, work++) {
        rot_x = CRotM[i].x;
        rot_y = CRotM[i].y;
        pos.x = CenterM[i].x + sindf(rot_y) * cosdf(rot_x) * CZoomM[i];
        pos.y = CenterM[i].y + -sindf(rot_x) * CZoomM[i];
        pos.z = CenterM[i].z + cosdf(rot_y) * cosdf(rot_x) * CZoomM[i];
        at.x = CenterM[i].x;
        at.y = CenterM[i].y;
        at.z = CenterM[i].z;
        up.x = sindf(rot_y) * sindf(rot_x);
        up.y = cosdf(rot_x);
        up.z = cosdf(rot_y) * sindf(rot_x);
        D_800D04B8_main[i][1] = pos.x;
        D_800D04B8_main[i][2] = pos.z;
        D_800D04B8_main[i][0] = CRotM[i].y;
        D_800D04B8_main[i][3] = gCameraList[i].fov[0];
        D_800D04B8_main[i][4] = D_800CCF98_main[i];
        D_800D04B8_main[i][5] = D_800D4198_main[i];
        Hu3DCamSetPositionOrientation(i, &pos, &at, &up);
        Hu3DCamUpdateMtx(i);
        dist = HuSqrtf((CenterM[i].x - pos.x) * (CenterM[i].x - pos.x) +
                                   (CenterM[i].y - pos.y) * (CenterM[i].y - pos.y) +
                                   (CenterM[i].z - pos.z) * (CenterM[i].z - pos.z));
        work->scaleX = (work->baseZoom / dist) * work->baseScaleX;
        work->scaleY = (work->baseZoom / dist) * work->baseScaleY;
        func_8004CB44_main(&planePos, &D_800CD2A8_main[i]);
        func_80012B14_main(0, &planePos, &scr0);
        func_80012B14_main(0, &work->planePos, &scr1);
        work->offsetX = (scr0.x - scr1.x) * work->baseScaleX;
        work->offsetY = (scr0.y - scr1.y) * work->baseScaleY;
        if (work->draw != NULL) {
            work->draw(work);
            if (i != obj->work[0] - 1) {
                gDPPipeSync(gMainGfxPos++);
            }
        }
    }
    gSPEndDisplayList(gMainGfxPos++);
}

/* Where the camera's view ray (from the eye through Center) meets the plane through the origin
   with the given normal. */
void func_8004CB44_main(Vec* out, Vec* normal) {
    Vec pos;
    f32 rot_x = CRot.x;
    f32 rot_y = CRot.y;
    f32 dist, dx, dy, dz, t;

    pos.x = Center.x + sindf(rot_y) * cosdf(rot_x) * CZoom;
    pos.y = Center.y + -sindf(rot_x) * CZoom;
    pos.z = Center.z + cosdf(rot_y) * cosdf(rot_x) * CZoom;
    dist = HuSqrtf((Center.x - pos.x) * (Center.x - pos.x) +
                               (Center.y - pos.y) * (Center.y - pos.y) +
                               (Center.z - pos.z) * (Center.z - pos.z));
    dx = (pos.x - Center.x) / dist;
    dy = (pos.y - Center.y) / dist;
    dz = (pos.z - Center.z) / dist;
    dist = dx * normal->x + dy * normal->y + dz * normal->z;
    t = (-pos.x * normal->x + -pos.y * normal->y + -pos.z * normal->z) / dist;
    out->x = dx * t + pos.x;
    out->y = dy * t + pos.y;
    out->z = dz * t + pos.z;
}

/* CZoom, CRot and Center for a camera at `eye` looking at `at`. */
void func_8004CD04_main(Vec* eye, Vec* at, f32* zoom, Vec* rot, Vec* center) {
    f32 mtx[4][4];
    f32 dx, dy, dz, ang, x, y;

    dx = eye->x - at->x;
    dy = eye->y - at->y;
    dz = eye->z - at->z;
    *zoom = HuSqrtf(dx * dx + dy * dy + dz * dz);
    ang = atan2df(dz, dx);
    rot->y = -(ang - 90.0f);
    ang = -ang;
    mtx[0][0] = mtx[2][2] = cosdf(ang);
    mtx[2][0] = -sindf(ang);
    mtx[0][2] = sindf(ang);
    mtx[1][1] = mtx[3][3] = 1.0f;
    mtx[1][0] = mtx[3][0] = mtx[0][1] = mtx[2][1] = mtx[3][1] = mtx[1][2] = mtx[3][2] = mtx[0][3] = mtx[1][3] =
        mtx[2][3] = 0.0f;
    x = dx * mtx[0][0] + dy * mtx[1][0] + dz * mtx[2][0];
    y = dx * mtx[0][1] + dy * mtx[1][1] + dz * mtx[2][1];
    rot->x = -atan2df(y, x);
    rot->z = 0.0f;
    center->x = at->x;
    center->y = at->y;
    center->z = at->z;
}
void func_8004CEA4_main() {
    D_800CE194_main = omAddObj(0x7FD8, 0, 0, -1, func_8004CF00_main);
    omSetStatBit(D_800CE194_main, 0xA0);
    D_800CE194_main->work[0] = D_800D6AB8_main;
}

void func_8004CF00_main(omObjData* obj) {
    s32* timer = (s32*)obj->work;

    if (*timer == 0) {
        D_800D530C_main = 1;
    } else {
        (*timer)--;
    }
}

/* Creates the sound-fade object: per-slot fade arrays sized by the configured sound slots. */
void func_8004CF30_main(void) {
    SndFadeWork* work;
    s32 i;

    D_800D6A40_main = omAddObj(0x7FD8, 0, 0, -1, func_8004D094_main);
    D_800D6A40_main->data = HuMemAllocTag(sizeof(SndFadeWork), 0x7918);
    work = D_800D6A40_main->data;
    func_80000EA8_main(&D_800D1398_main);
    D_800A1910_main = D_800D1398_main.unks4858[3];
    work->vol = HuMemAllocTag(D_800A1910_main * sizeof(f32), 0x7918);
    work->volStep = HuMemAllocTag(D_800A1910_main * sizeof(f32), 0x7918);
    work->vol2 = HuMemAllocTag(D_800A1910_main * sizeof(f32), 0x7918);
    work->vol2Step = HuMemAllocTag(D_800A1910_main * sizeof(f32), 0x7918);
    work->flags = HuMemAllocTag(D_800A1910_main, 0x7918);
    omSetStatBit(D_800D6A40_main, 0xA0);
    for (i = 0; i < D_800A1910_main; i++) {
        work->flags[i] = 0;
    }
    work->unk14 = 0;
    work->unk24 = -1.0f;
    work->unk1C = 0;
    work->unk18 = 0;
    work->unk16 = 0;
    work->unk28 = -1.0f;
    work->unk20 = 0;
    work->unk1A = 0;
    work->unk34 = -1;
}

INCLUDE_ASM("asm/nonmatchings/4BF40", func_8004D094_main);
