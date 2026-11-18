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

void *HuMemAllocTag(s32 size, s16 tag);
void func_8010BE88_fridged_bridges(omObjData *obj);

extern s16 D_8010CF48_fridged_bridges[4]; /* per player: camera bit */
extern s32 D_8010D240_fridged_bridges[1]; /* per effect type: model file */
extern omObjFunc D_8010D244_fridged_bridges[1]; /* per effect type: object function */
extern u32 D_8010D248_fridged_bridges[1]; /* per effect type: lifetime */
extern s16 D_8010DA30_fridged_bridges[1][12]; /* effect models */
extern u16 D_8010DA48_fridged_bridges[1][12]; /* 1 = in use */
extern omObjData *D_8010DA88_fridged_bridges;

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010C1D8_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010C46C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010C738_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010CDE4_fridged_bridges);
