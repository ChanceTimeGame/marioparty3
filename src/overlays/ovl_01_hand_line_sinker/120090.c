#include "common.h"
// m4 hl: Hand, Line and Sinker: camera tween and the fishing line strip (MP1 Cast Aways' line code)
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "mallocblock.h"

/* A camera pose: Center, CRot, CZoom. */
typedef struct HlCamPose {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} HlCamPose; // Size 0x1C

/* The camera tween object's data (func_8010B5EC_hand_line_sinker). */
typedef struct HlCamTween {
    /* 0x00 */ HlCamPose *from;
    /* 0x04 */ HlCamPose *to;
    /* 0x08 */ u16 frames;
    /* 0x0A */ u16 left;
    /* 0x0C */ f32 t;
} HlCamTween; // Size 0x10

/* A fishing line: a model whose display list is rebuilt each frame (MP1 CastAwaysSpriteData). */
typedef struct HlLine {
    /* 0x00 */ s16 model;
    /* 0x02 */ u8 r;
    /* 0x03 */ u8 g;
    /* 0x04 */ u8 b;
    /* 0x08 */ Vtx *vtx[8]; /* per frame buffer, 0x200 bytes (32 vertices) */
    /* 0x28 */ Gfx *gfx[8]; /* per frame buffer, 0x400 bytes */
} HlLine; // Size 0x48

void *func_8000B638_main(void);
void osSyncPrintf(const char *fmt, ...);
extern u8 D_800D2008_main; /* frame buffer index */
extern Gfx *gMainGfxPos;
extern Vec Center;
extern Vec CRot;
extern f32 CZoom;

void func_8010B750_hand_line_sinker(omObjData *obj);

/* .bss */
extern HlLine *D_8010C180_hand_line_sinker;
extern Gfx *D_8010C184_hand_line_sinker;
extern HmfData **D_8010C188_hand_line_sinker;
extern HmfModel *D_8010C18C_hand_line_sinker;
extern omObjData *D_8010C190_hand_line_sinker;

void func_8010B5B0_hand_line_sinker(void) {
    func_8000B5F0_main(1);
    func_8000B638_main();
    gCameraList->fov[0] = 40.0f;
}

/* Starts a camera tween from one pose to another over frames (bit 15 set: driven by func_8010BA50). */
void func_8010B5EC_hand_line_sinker(HlCamPose *from, HlCamPose *to, s16 frames) {
    HlCamTween *tw;

    Center = from->center;
    CRot = from->rot;
    CZoom = from->zoom;
    D_8010C190_hand_line_sinker = omAddObj(0x28, 0, 0, -1, func_8010B750_hand_line_sinker);
    tw = HuMemAllocTag(sizeof(HlCamTween), 0x7918);
    D_8010C190_hand_line_sinker->data = tw;
    tw->from = from;
    tw->to = to;
    tw->left = frames;
    tw->frames = frames;
    tw->t = 0.0f;
    Center = from->center;
    CRot = from->rot;
    CZoom = from->zoom;
    D_8010C190_hand_line_sinker->work[0] = 1;
    D_8010C190_hand_line_sinker->work[1] = 0;
    D_8010C190_hand_line_sinker->work[2] = 0;
    if (frames >= 0) {
        D_8010C190_hand_line_sinker->work[3] = 1;
    } else {
        D_8010C190_hand_line_sinker->work[3] = 0;
    }
}

void func_8010B750_hand_line_sinker(omObjData *obj) {
    HlCamTween *tw = obj->data;
    HlCamPose *from;
    HlCamPose *to;
    u32 mode;

    if (D_8010C190_hand_line_sinker->work[1] != 0) {
        from = tw->from;
        to = tw->to;
        mode = D_8010C190_hand_line_sinker->work[3];
        if (mode == 1) {
            Center.x += (to->center.x - from->center.x) / tw->frames;
            Center.y += (to->center.y - from->center.y) / tw->frames;
            Center.z += (to->center.z - from->center.z) / tw->frames;
            CRot.x += (to->rot.x - from->rot.x) / tw->frames;
            CRot.y += (to->rot.y - from->rot.y) / tw->frames;
            CRot.z += (to->rot.z - from->rot.z) / tw->frames;
            CZoom += (to->zoom - from->zoom) / tw->frames;
            if (--tw->left == 0) {
                Center.x = to->center.x;
                Center.y = to->center.y;
                Center.z = to->center.z;
                CRot.x = to->rot.x;
                CRot.y = to->rot.y;
                CRot.z = to->rot.z;
                CZoom = to->zoom;
                obj->work[0] = 0;
                if (obj->work[2] != mode) {
                    obj->func = NULL;
                } else {
                    omDelObj(obj);
                    D_8010C190_hand_line_sinker = NULL;
                }
            }
        } else {
            Center.x = (to->center.x - from->center.x) * tw->t + from->center.x;
            Center.y = (to->center.y - from->center.y) * tw->t + from->center.y;
            Center.z = (to->center.z - from->center.z) * tw->t + from->center.z;
            CRot.x = (to->rot.x - from->rot.x) * tw->t + from->rot.x;
            CRot.y = (to->rot.y - from->rot.y) * tw->t + from->rot.y;
            CRot.z = (to->rot.z - from->rot.z) * tw->t + from->rot.z;
            CZoom = (to->zoom - from->zoom) * tw->t + from->zoom;
            if (obj->work[0] == 0) {
                if (obj->work[2] == 1) {
                    D_8010C190_hand_line_sinker = NULL;
                    omDelObj(obj);
                } else {
                    obj->func = NULL;
                }
            }
        }
    }
}

/* Sets the tween's position (0..1) when it is not stepping linearly. */
void func_8010BA50_hand_line_sinker(f32 t) {
    ((HlCamTween *)D_8010C190_hand_line_sinker->data)->t = t;
}

void func_8010BA64_hand_line_sinker(void) {
    omOvlReturnEx(1);
}

HlLine *func_8010BA80_hand_line_sinker(s8 r, s8 g, s8 b) {
    HlLine *line = HuMemAlloc(sizeof(HlLine));
    s16 i;

    line->model = func_8001A894_main(0x1080, NULL, 4);
    i = 0;
    if (D_800D1FF0_main != 0) {
        do {
            line->vtx[i] = HuMemAlloc(0x200);
            line->gfx[i] = HuMemAlloc(0x400);
            i++;
        } while (i < D_800D1FF0_main);
    }
    line->r = r;
    line->g = g;
    line->b = b;
    return line;
}

/* Draws the line through count points as a strip of 3D lines. */
void func_8010BB58_hand_line_sinker(HlLine *line, Vec *points, u16 count) {
    Vtx *vtx;
    Gfx *gfx;
    s16 i;

    if (line != NULL) {
        vtx = line->vtx[D_800D2008_main];
        gfx = line->gfx[D_800D2008_main];
        if (count < 2) {
            osSyncPrintf("Line Count err %d\n", count);
        }
        D_8010C180_hand_line_sinker = line;
        D_8010C18C_hand_line_sinker = &HmfModelData[line->model];
        D_8010C188_hand_line_sinker = &HmfModelData[line->model].hmf;
        D_8010C184_hand_line_sinker = gfx;
        HmfModelData[line->model].hmf->unk3C->unk00[0] = gfx;
        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gfx++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPVertex(gfx++, osVirtualToPhysical(vtx), count + 1, 0);
        vtx->v.ob[0] = points->x;
        vtx->v.ob[1] = points->y;
        vtx->v.ob[2] = points->z;
        vtx->v.cn[0] = line->r;
        vtx->v.cn[1] = line->g;
        vtx->v.cn[2] = line->b;
        vtx->v.tc[1] = 0;
        vtx->v.tc[0] = 0;
        vtx->v.cn[3] = 0xFF;
        vtx++;
        points++;
        for (i = 1; i < count; i++) {
            gSPLine3D(gfx++, i - 1, i, 0);
            vtx->v.ob[0] = points->x;
            vtx->v.ob[1] = points->y;
            vtx->v.ob[2] = points->z;
            vtx->v.cn[0] = line->r;
            vtx->v.cn[1] = line->g;
            vtx->v.cn[2] = line->b;
            vtx->v.tc[1] = 0;
            vtx->v.tc[0] = 0;
            vtx->v.cn[3] = 0xFF;
            vtx++;
            points++;
        }
        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        gSPEndDisplayList(gfx++);
    }
}

void func_8010BE6C_hand_line_sinker(HlLine *line) {
    s16 i = 0;

    func_8001ACDC_main(line->model);
    if (D_800D1FF0_main != 0) {
        do {
            func_80019C00_main(line->vtx[i]);
            func_80019C00_main(line->gfx[i]);
            i++;
        } while (i < D_800D1FF0_main);
    }
    func_80019C00_main(line);
}
