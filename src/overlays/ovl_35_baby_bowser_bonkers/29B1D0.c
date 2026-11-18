#include "common.h"
// m3 bk: Baby Bowser Bonkers
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"

/* A camera key (D_8010BCB0, 2 x 0x24); the same layout as Log Jam's BkCamera. */
typedef struct BkCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} BkCamera; // Size 0x24

typedef struct BkBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} BkBytes;

typedef union BkPack {
    void *p;
    BkBytes b;
} BkPack;

#define BK_WRAP(v)             \
    if ((v) >= 360.0) {        \
        (v) -= 360.0;          \
    } else if ((v) < 0.0) {    \
        (v) += 360.0;          \
    }

extern u16 D_800D5558_main[];
extern u8 D_800D6A90_main;
extern s32 fontcolor;

extern s32 D_8010B890_baby_bowser_bonkers;
extern f32 D_8010B8EC_baby_bowser_bonkers;
extern f32 D_8010B8F0_baby_bowser_bonkers;
extern f32 D_8010B8F4_baby_bowser_bonkers;
extern s32 D_8010B938_baby_bowser_bonkers; /* debug camera mode */
extern s32 D_8010B93C_baby_bowser_bonkers; /* debug text x */
extern s32 D_8010B940_baby_bowser_bonkers; /* debug text y */
extern BkCamera D_8010BCB0_baby_bowser_bonkers[2];
extern s32 D_8010BCF8_baby_bowser_bonkers;
extern s32 D_8010BCFC_baby_bowser_bonkers;
extern s32 D_8010BD00_baby_bowser_bonkers;

void func_801062E8_baby_bowser_bonkers(omObjData* obj);
void func_8010A6D8_baby_bowser_bonkers(omObjData *obj);
void func_8010AB14_baby_bowser_bonkers(s32 idx);
void func_8010AD00_baby_bowser_bonkers(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
void func_8010AEF0_baby_bowser_bonkers(s32 idx);
f32 func_8010B044_baby_bowser_bonkers(f32 a, f32 b);
f32 func_8010B148_baby_bowser_bonkers(f32 target, f32 cur, f32 step);
f32 func_8010B308_baby_bowser_bonkers(f32 t, f32 a, f32 b);
f32 func_8010B320_baby_bowser_bonkers(f32 t, f32 a, f32 b);
void func_8010B380_baby_bowser_bonkers(omObjData *obj, u32 value);
void *func_8010B3AC_baby_bowser_bonkers(omObjData *obj);
void func_8001E65C_main(s16 mdl, f32 u, f32 v, s32 w, s32 h);
void func_8001F6BC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void func_8001F6F8_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
f32 fabsf(f32);
f64 fmod(f64, f64);
// end m3 bk

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801059A0_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80105BB0_baby_bowser_bonkers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", D_8010B950_baby_bowser_bonkers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", D_8010B95C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80105C0C_baby_bowser_bonkers);

void func_801062E8_baby_bowser_bonkers(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_8010630C_baby_bowser_bonkers(omObjData* obj) {
    if (D_8010B890_baby_bowser_bonkers != 0) {
        if (D_8010B890_baby_bowser_bonkers == 1) {
            obj->func = func_801062E8_baby_bowser_bonkers;
        }
        D_8010B890_baby_bowser_bonkers--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010B890_baby_bowser_bonkers = 0x10;
        WipeCreateOut(0, (s16)D_8010B890_baby_bowser_bonkers);
        HuAudSeqFadeOut((s16)D_8010B890_baby_bowser_bonkers);
        func_8004AB0C_main((s16)D_8010B890_baby_bowser_bonkers);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801063B4_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010660C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80106AA4_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80106CEC_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801075F4_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80107648_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80107678_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801076D8_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80107CD8_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80107D38_baby_bowser_bonkers);

void func_80107E54_baby_bowser_bonkers(omObjData* obj) {
    func_8001E65C_main(obj->model[0], sindf(D_8010B8EC_baby_bowser_bonkers) * 15.0f, -D_8010B8F0_baby_bowser_bonkers,
                       64, 64);
    func_8001F6BC_main(obj->model[0], (u8)(cosdf(D_8010B8F4_baby_bowser_bonkers) * 32.0f + 32.0f), 0, 0,
                       (u8)(cosdf(D_8010B8F4_baby_bowser_bonkers) * 32.0f + 32.0f));
    func_8001F6F8_main(obj->model[0], 64, 32, 32, 0);
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010B8EC_baby_bowser_bonkers += 0.5f;
        if (D_8010B8EC_baby_bowser_bonkers >= 360.0f) {
            D_8010B8EC_baby_bowser_bonkers -= 360.0f;
        }
        D_8010B8F0_baby_bowser_bonkers += 0.2f;
        if (D_8010B8F0_baby_bowser_bonkers >= 64.0f) {
            D_8010B8F0_baby_bowser_bonkers -= 64.0f;
        }
        D_8010B8F4_baby_bowser_bonkers += 2.4f;
        if (D_8010B8F4_baby_bowser_bonkers >= 360.0f) {
            D_8010B8F4_baby_bowser_bonkers -= 360.0f;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801080D0_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108160_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801081C0_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010831C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108454_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801089CC_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108A0C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108B84_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108D6C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108E90_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108F9C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109080_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010919C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801091D4_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109388_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801093D4_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010943C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010958C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801096D0_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109704_baby_bowser_bonkers);

u16 func_8010984C_baby_bowser_bonkers(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109890_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109990_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109BFC_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109E98_baby_bowser_bonkers);

void func_80109EB8_baby_bowser_bonkers(void) {
    HuCamera *cam;
    s32 i;

    Center.x = 0.0f;
    Center.y = -708.8f;
    Center.z = -781.8f;
    CRot.x = 318.38f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2938.0f;
    func_8010AB14_baby_bowser_bonkers(0);
    func_8010AB14_baby_bowser_bonkers(1);
    D_8010BCF8_baby_bowser_bonkers = D_8010BCFC_baby_bowser_bonkers = D_8010BD00_baby_bowser_bonkers = 0;
    omAddObj(0x1F, 0, 0, -1, func_8010A6D8_baby_bowser_bonkers);
    cam = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        cam->viewports[i].vp.vscale[0] = cam->viewports[0].vp.vscale[0];
        cam->viewports[i].vp.vscale[1] = cam->viewports[0].vp.vscale[1];
        cam->viewports[i].vp.vscale[2] = cam->viewports[0].vp.vscale[2];
        cam->viewports[i].vp.vtrans[0] = cam->viewports[0].vp.vtrans[0];
        cam->viewports[i].vp.vtrans[1] = cam->viewports[0].vp.vtrans[1];
        cam->viewports[i].vp.vtrans[2] = cam->viewports[0].vp.vtrans[2];
    }
}


void func_80109FE8_baby_bowser_bonkers(void) {
    BkCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_8010B938_baby_bowser_bonkers) {
        case 1:
            if ((u16)D_800CDA7C_main[0] & 0x8000) {
                speed = 8.0f;
            }
            if (D_800CDA7C_main[0] & 0x4000) {
                speed = 0.5f;
            }
            if (D_800D5558_main[0] & 0x1000) {
                Center.x = 0.0f;
                Center.y = 191.2f;
                Center.z = 0.2f;
                CRot.x = -14.5f;
                CRot.y = 0.0f;
                CRot.z = 0.0f;
                CZoom = 1069.0f;
            } else {
                c.rot.x = (f32)D_800D20A1_main[0] * 0.125 * speed;
                c.rot.y = (f32)D_800CBB6E_main[0] * 0.125 * speed;
                if (D_800CDA7C_main[0] & 0x200) {
                    c.center.x = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 0x100) {
                    c.center.x = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x800) {
                    c.center.z = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x400) {
                    c.center.z = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 8) {
                    c.center.y = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 4) {
                    c.center.y = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 1) {
                    c.zoom = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 2) {
                    c.zoom = -(2.0 * speed);
                }
                c.center.x += Center.x;
                c.center.y += Center.y;
                c.center.z += Center.z;
                c.rot.x += CRot.x;
                c.rot.y += CRot.y;
                c.rot.z += CRot.z;
                c.zoom += CZoom;
                func_8010AD00_baby_bowser_bonkers(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 104, D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
                D_8010B93C_baby_bowser_bonkers++;
            }
            if (D_800CDA7C_main[0] & 0x202) {
                D_8010B93C_baby_bowser_bonkers--;
            }
            if (D_800CDA7C_main[0] & 0x404) {
                D_8010B940_baby_bowser_bonkers++;
            }
            if (D_800CDA7C_main[0] & 0x808) {
                D_8010B940_baby_bowser_bonkers--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010B93C_baby_bowser_bonkers + 20, (u16)D_8010B940_baby_bowser_bonkers + 104, D_800D5218_main);
            break;
        case 3:
            D_8010B938_baby_bowser_bonkers = 0;
            break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_8010B938_baby_bowser_bonkers == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_8010B938_baby_bowser_bonkers++ >= 4) {
            D_8010B938_baby_bowser_bonkers = 0;
        }
    }
}

void func_8010A6D8_baby_bowser_bonkers(omObjData *obj) {
    f32 t;

    if (D_8010BCFC_baby_bowser_bonkers <= 0) {
        func_8010AEF0_baby_bowser_bonkers(0);
        D_8010BD00_baby_bowser_bonkers = 0;
        return;
    }
    if (D_8010BCF8_baby_bowser_bonkers == 0) {
        Center.x = D_8010BCB0_baby_bowser_bonkers[0].center.x;
        Center.y = D_8010BCB0_baby_bowser_bonkers[0].center.y;
        Center.z = D_8010BCB0_baby_bowser_bonkers[0].center.z;
        CRot.x = D_8010BCB0_baby_bowser_bonkers[0].rot.x;
        CRot.y = D_8010BCB0_baby_bowser_bonkers[0].rot.y;
        CRot.z = D_8010BCB0_baby_bowser_bonkers[0].rot.z;
        CZoom = D_8010BCB0_baby_bowser_bonkers[0].zoom;
        BK_WRAP(CRot.x);
        BK_WRAP(CRot.y);
        BK_WRAP(CRot.z);
        D_8010BCFC_baby_bowser_bonkers = 0;
    } else {
        t = (f32)D_8010BCF8_baby_bowser_bonkers / (f32)D_8010BCFC_baby_bowser_bonkers;
        Center.x = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].center.x, D_8010BCB0_baby_bowser_bonkers[1].center.x);
        Center.y = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].center.y, D_8010BCB0_baby_bowser_bonkers[1].center.y);
        Center.z = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].center.z, D_8010BCB0_baby_bowser_bonkers[1].center.z);
        CRot.x = func_8010B320_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].rot.x, D_8010BCB0_baby_bowser_bonkers[1].rot.x);
        CRot.y = func_8010B320_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].rot.y, D_8010BCB0_baby_bowser_bonkers[1].rot.y);
        CRot.z = func_8010B320_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].rot.z, D_8010BCB0_baby_bowser_bonkers[1].rot.z);
        CZoom = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].zoom, D_8010BCB0_baby_bowser_bonkers[1].zoom);
        BK_WRAP(CRot.x);
        BK_WRAP(CRot.y);
        BK_WRAP(CRot.z);
        if (D_8010BCF8_baby_bowser_bonkers > 0) {
            D_8010BCF8_baby_bowser_bonkers--;
        } else {
            D_8010BCF8_baby_bowser_bonkers++;
        }
    }
    D_8010BD00_baby_bowser_bonkers = 1;
    func_8010AEF0_baby_bowser_bonkers(0);
}

void func_8010AB14_baby_bowser_bonkers(s32 idx) {
    BK_WRAP(CRot.x);
    BK_WRAP(CRot.y);
    BK_WRAP(CRot.z);
    D_8010BCB0_baby_bowser_bonkers[idx].center.x = Center.x;
    D_8010BCB0_baby_bowser_bonkers[idx].center.y = Center.y;
    D_8010BCB0_baby_bowser_bonkers[idx].center.z = Center.z;
    D_8010BCB0_baby_bowser_bonkers[idx].rot.x = CRot.x;
    D_8010BCB0_baby_bowser_bonkers[idx].rot.y = CRot.y;
    D_8010BCB0_baby_bowser_bonkers[idx].rot.z = CRot.z;
    D_8010BCB0_baby_bowser_bonkers[idx].zoom = CZoom;
    D_8010BCB0_baby_bowser_bonkers[idx].unk1C = D_8010BCB0_baby_bowser_bonkers[idx].unk20 = 0.0f;
}

void func_8010AD00_baby_bowser_bonkers(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_8010BCF8_baby_bowser_bonkers = frames - 1;
        D_8010BCFC_baby_bowser_bonkers = frames;
        if (cx != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].center.x = cx;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].center.y = cy;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].center.z = cz;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].rot.x = rx;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].rot.y = ry;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].rot.z = rz;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_8010BCB0_baby_bowser_bonkers[0].zoom = zoom;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].zoom = CZoom;
        }
        func_8010AB14_baby_bowser_bonkers(1);
    }
}

void func_8010AEF0_baby_bowser_bonkers(s32 idx) {
    HuCamera *cam = &gCameraList[idx];
    f32 rx = CRot.x;
    f32 ry = CRot.y;

    cam->pos.x = Center.x + sindf(ry) * cosdf(rx) * CZoom;
    cam->pos.y = -sindf(rx) * CZoom + Center.y;
    cam->pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
    cam->at.x = Center.x;
    cam->at.y = Center.y;
    cam->at.z = Center.z;
    cam->up.x = sindf(ry) * sindf(rx);
    cam->up.y = cosdf(rx);
    cam->up.z = cosdf(ry) * sindf(rx);
}

f32 func_8010B044_baby_bowser_bonkers(f32 a, f32 b) {
    f32 d;

    if (a >= 360.0f) {
        a -= 360.0f;
    } else if (a < 0.0f) {
        a += 360.0f;
    }
    if (b >= 360.0f) {
        b -= 360.0f;
    } else if (b < 0.0f) {
        b += 360.0f;
    }
    d = a - b;
    if (d <= -180.0f) {
        d += 360.0f;
    } else if (d >= 180.0f) {
        d -= 360.0f;
    }
    return d;
}

f32 func_8010B148_baby_bowser_bonkers(f32 target, f32 cur, f32 step) {
    f32 d;
    f32 v;
    f64 e;

    BK_WRAP(target);
    BK_WRAP(cur);
    d = fmod(target - cur + 360.0, 360.0);
    if (d < 180.0) {
        if (d <= step) {
            v = d;
        } else {
            v = step;
        }
    } else {
        e = 360.0 - d;
        if (e <= step) {
            v = -e;
        } else {
            v = -step;
        }
    }
    v += cur;
    BK_WRAP(v);
    return v;
}

f32 func_8010B308_baby_bowser_bonkers(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

f32 func_8010B320_baby_bowser_bonkers(f32 t, f32 a, f32 b) {
    return func_8010B148_baby_bowser_bonkers(b, a, fabsf(func_8010B044_baby_bowser_bonkers(b, a) * t));
}

void func_8010B380_baby_bowser_bonkers(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}

void *func_8010B3AC_baby_bowser_bonkers(omObjData *obj) {
    BkPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}
