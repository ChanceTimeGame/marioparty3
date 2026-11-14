#include "common.h"
#include "option.h"
#include "mallocblock.h"
#include "game/vibrator.h"
#include "pad.h"

void func_801059A0_option(void) {
    ovlEventCall(D_801134B0_option, omovlevtno);
}

OP_FILE_END()

void func_801059D0_option(void) {
    Vec pos;
    Vec target;
    Vec up;

    omInitObjMan(0x40, 0x20);
    func_800142A0_main(0x20);
    func_8004A208_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    pos = D_801139E0_option;
    target = D_801139EC_option;
    up = D_801139F8_option;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 41.0f, 80.0f, 8000.0f);
    Hu3DCamSetPositionOrientation(0, &pos, &target, &up);
    func_80030030_main(1.0f);
    pfInit();
    func_8005A6B0_main();
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x80, 0x80, 0x80);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    HmfLightDirSet(1, 0.0f, 64.0f, 192.0f);
    D_800D2132_main = 0;
}

void func_80105C14_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C38_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C5C_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C80_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105CA4_option(void) {
    func_801059D0_option();
    func_80108AAC_option();
}

void func_80105CC8_option(void) {
    func_801059D0_option();
    func_80108AAC_option();
}

void func_80105CEC_option(void) {
    func_801059D0_option();
    func_80108AF0_option();
}

void func_80105D10_option(void) {
    D_801146F0_option.proc = NULL;
    D_801146F0_option.moveObj = NULL;
    D_801146F0_option.view = -1;
    D_801146F0_option.fov = 50.0f;
    D_801146F0_option.nearZ = 80.0f;
    D_801146F0_option.farZ = 4000.0f;
}

void func_80105D5C_option(f32 fov, f32 nearZ, f32 farZ) {
    D_801146F0_option.fov = fov;
    D_801146F0_option.nearZ = nearZ;
    D_801146F0_option.farZ = farZ;
}

void func_80105D74_option(void) {
    while (TRUE) {
        func_80012E54_main(0);
        HuPrcVSleep();
    }
}

void func_80105DA0_option(s16 view, f32 fov) {
    if (D_801146F0_option.proc != NULL) {
        func_80105E40_option();
    }
    func_80013320_main(view, 0);
    D_801146F0_option.view = view;
    D_801146F0_option.fov = fov;
    Hu3DCamSetPerspective(0, fov, D_801146F0_option.nearZ, D_801146F0_option.farZ);
    func_80012E54_main(0);
    D_801146F0_option.proc = omAddPrcObj(func_80105D74_option, 0x5000, 0x2000, 0);
}

void func_80105E40_option(void) {
    if (D_801146F0_option.proc != NULL) {
        omDelPrcObj(D_801146F0_option.proc);
    } else {
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    if (D_801146F0_option.view != -1) {
        func_80013350_main(0);
        D_801146F0_option.view = -1;
    }
    D_801146F0_option.proc = NULL;
}

void func_80105EB8_option(void) {
    while (TRUE) {
        Hu3DCamSetPositionOrientation(0, &D_801146F0_option.eye, &D_801146F0_option.at, &D_801146F0_option.up);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

void func_80105F08_option(f32 fov) {
    Vec eye;
    Vec at;
    Vec up;

    D_801146F0_option.fov = fov;
    if (D_801146F0_option.view != -1) {
        func_80105FF8_option(&eye, &at, &up);
        HuVecCopy3F(&D_801146F0_option.eye, &eye);
        HuVecCopy3F(&D_801146F0_option.at, &at);
        HuVecCopy3F(&D_801146F0_option.up, &up);
    }
    if (D_801146F0_option.proc != NULL) {
        func_80105E40_option();
    }
    Hu3DCamSetPositionOrientation(0, &D_801146F0_option.eye, &D_801146F0_option.at, &D_801146F0_option.up);
    Hu3DCamUpdateMtx(0);
    Hu3DCamSetPerspective(0, D_801146F0_option.fov, D_801146F0_option.nearZ, D_801146F0_option.farZ);
    D_801146F0_option.proc = omAddPrcObj(func_80105EB8_option, 0x5000, 0x2000, 0);
}

#ifdef NON_MATCHING
/* The followed model camera's eye and target, and an up vector square to the view direction
   (modesel func_80108AE0_modesel); the stored camera when none is followed. Waits forever while the
   model camera has no view. */
s32 func_80105FF8_option(Vec *eye, Vec *at, Vec *up) {
    HmfData *hmf;
    OpHmfCamView *view;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;
    f32 ux;
    f32 uy;
    f32 uz;
    f32 rz;

    if (D_801146F0_option.view == -1) {
        HuVecCopy3F(eye, &D_801146F0_option.eye);
        HuVecCopy3F(at, &D_801146F0_option.at);
        HuVecCopy3F(up, &D_801146F0_option.up);
        return 0;
    }
    hmf = HmfModelData[gCameraList->unk4].hmf;
    if (hmf == NULL || (view = *(OpHmfCamView **)&hmf->unkB8[4]) == NULL) {
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    eye->x = view->pos.x;
    eye->y = view->pos.y;
    eye->z = view->pos.z;
    at->x = view->at.x;
    at->y = view->at.y;
    at->z = view->at.z;
    rz = -90.0f;
    dx = at->x - eye->x;
    dy = at->y - eye->y;
    dz = at->z - eye->z;
    len = dx * dx + dy * dy + dz * dz;
    len = HuSqrtf(len);
    dx /= len;
    dy /= len;
    dz /= len;
    ux = dy * dz - dz * (dy + 1.0f);
    uy = dz * dx - dx * dz;
    uz = dx * (dy + 1.0f) - dy * dx;
    up->x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz))
          + uy * (dy * dx * (1.0f - cosdf(rz)) - dz * sindf(rz))
          + uz * (dz * dx * (1.0f - cosdf(rz)) + dy * sindf(rz));
    up->y = ux * (dy * dx * (1.0f - cosdf(rz)) + dz * sindf(rz))
          + uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz))
          + uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
    up->z = ux * (dz * dx * (1.0f - cosdf(rz)) - dy * sindf(rz))
          + uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz))
          + uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80105FF8_option);
#endif

/* Stores eye and target as the camera, with an up vector square to the view direction (also written
   to *up). */
void func_80106508_option(Vec *eye, Vec *at, Vec *up) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;
    f32 ux;
    f32 uy;
    f32 uz;
    f32 rz;

    rz = -90.0f;
    dx = at->x - eye->x;
    dy = at->y - eye->y;
    dz = at->z - eye->z;
    len = dx * dx + dy * dy + dz * dz;
    len = HuSqrtf(len);
    dx /= len;
    dy /= len;
    dz /= len;
    ux = dy * dz - dz * (dy + 1.0f);
    uy = dz * dx - dx * dz;
    uz = dx * (dy + 1.0f) - dy * dx;
    up->x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz))
          + uy * (dy * dx * (1.0f - cosdf(rz)) - dz * sindf(rz))
          + uz * (dz * dx * (1.0f - cosdf(rz)) + dy * sindf(rz));
    up->y = ux * (dy * dx * (1.0f - cosdf(rz)) + dz * sindf(rz))
          + uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz))
          + uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
    up->z = ux * (dz * dx * (1.0f - cosdf(rz)) - dy * sindf(rz))
          + uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz))
          + uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
    HuVecCopy3F(&D_801146F0_option.eye, eye);
    HuVecCopy3F(&D_801146F0_option.at, at);
    HuVecCopy3F(&D_801146F0_option.up, up);
}

/* Camera move, straight: eye and target both move linearly. */
void func_80106998_option(omObjData *obj) {
    Vec eye;
    Vec at;
    Vec up;
    Vec from;
    Vec to;
    f32 t;
    f32 u;

    t = (f32)D_801146F0_option.t / (f32)D_801146F0_option.len;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        u = 1.0f;
    } else {
        u = t;
    }
    HuVecCopy3F(&from, &D_801146F0_option.fromEye);
    HuVecCopy3F(&to, &D_801146F0_option.toEye);
    HuVecCopyXYZ(&eye, (to.x - from.x) * u + from.x, (to.y - from.y) * u + from.y, (to.z - from.z) * u + from.z);
    HuVecCopy3F(&from, &D_801146F0_option.fromAt);
    HuVecCopy3F(&to, &D_801146F0_option.toAt);
    HuVecCopyXYZ(&at, (to.x - from.x) * u + from.x, (to.y - from.y) * u + from.y, (to.z - from.z) * u + from.z);
    if (D_801146F0_option.t > D_801146F0_option.len) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.toEye, &D_801146F0_option.toAt, &up);
        D_801146F0_option.moveObj = NULL;
        return;
    }
    D_801146F0_option.t++;
    func_80106508_option(&eye, &at, &up);
}

void func_80106B78_option(void) {
    if (D_801146F0_option.moveObj != NULL) {
        omDelObj(D_801146F0_option.moveObj);
    }
    D_801146F0_option.moveObj = NULL;
}

omObjData *func_80106BAC_option(Vec *eye, Vec *at, s32 len) {
    omObjData *obj;

    func_80106B78_option();
    obj = omAddObj(6, 0, 0, -1, func_80106998_option);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_801146F0_option.moveObj = obj;
    D_801146F0_option.t = 0;
    D_801146F0_option.len = len;
    HuVecCopy3F(&D_801146F0_option.fromAt, &D_801146F0_option.at);
    HuVecCopy3F(&D_801146F0_option.fromEye, &D_801146F0_option.eye);
    HuVecCopyXYZ(&D_801146F0_option.toAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&D_801146F0_option.toEye, eye->x, eye->y, eye->z);
    return obj;
}

/* Camera move keeping the horizontal eye-to-target distance in step (linear). */
void func_80106C7C_option(omObjData *obj) {
    Vec eye;
    Vec at;
    Vec up;
    Vec fromEye;
    Vec toEye;
    Vec d;
    Vec fromAt;
    Vec toAt;
    Vec d0;
    Vec d1;
    f32 len0;
    f32 t;
    f32 u;
    f32 s;

    t = (f32)D_801146F0_option.t / (f32)D_801146F0_option.len;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        u = 1.0f;
    } else {
        u = t;
    }
    s = u;
    HuVecCopy3F(&fromEye, &D_801146F0_option.fromEye);
    HuVecCopy3F(&toEye, &D_801146F0_option.toEye);
    HuVecCopyXYZ(&eye, (toEye.x - fromEye.x) * s + fromEye.x, (toEye.y - fromEye.y) * s + fromEye.y, (toEye.z - fromEye.z) * s + fromEye.z);
    HuVecCopy3F(&fromAt, &D_801146F0_option.fromAt);
    HuVecCopy3F(&toAt, &D_801146F0_option.toAt);
    HuVecCopyXYZ(&at, (toAt.x - fromAt.x) * s + fromAt.x, (toAt.y - fromAt.y) * s + fromAt.y, (toAt.z - fromAt.z) * s + fromAt.z);
    HuVecCopyXYZ(&d0, fromAt.x - fromEye.x, 0.0f, fromAt.z - fromEye.z);
    HuVecCopyXYZ(&d1, toAt.x - toEye.x, 0.0f, toAt.z - toEye.z);
    len0 = HuVecGetLength3F(&d0);
    t = HuVecGetLength3F(&d1);
    HuVecCopyXYZ(&d, at.x - eye.x, 0.0f, at.z - eye.z);
    t = ((t - len0) * s + len0) / HuVecGetLength3F(&d);
    HuVecCopyXYZ(&at, t * d.x + eye.x, (toAt.y - fromAt.y) * s + fromAt.y, t * d.z + eye.z);
    if (D_801146F0_option.t > D_801146F0_option.len) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.toEye, &D_801146F0_option.toAt, &up);
        D_801146F0_option.moveObj = NULL;
        return;
    }
    D_801146F0_option.t++;
    func_80106508_option(&eye, &at, &up);
}

omObjData *func_80106F88_option(Vec *eye, Vec *at, s32 len) {
    omObjData *obj;

    func_80106B78_option();
    obj = omAddObj(6, 0, 0, -1, func_80106C7C_option);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_801146F0_option.moveObj = obj;
    D_801146F0_option.t = 0;
    D_801146F0_option.len = len;
    HuVecCopy3F(&D_801146F0_option.fromAt, &D_801146F0_option.at);
    HuVecCopy3F(&D_801146F0_option.fromEye, &D_801146F0_option.eye);
    HuVecCopyXYZ(&D_801146F0_option.toAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&D_801146F0_option.toEye, eye->x, eye->y, eye->z);
    return obj;
}

/* As func_80106C7C_option, eased (sine). */
void func_80107058_option(omObjData *obj) {
    Vec eye;
    Vec at;
    Vec up;
    Vec fromEye;
    Vec toEye;
    Vec d;
    Vec fromAt;
    Vec toAt;
    Vec d0;
    Vec d1;
    f32 len0;
    f32 t;
    f32 u;
    f32 s;

    t = (f32)D_801146F0_option.t / (f32)D_801146F0_option.len;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        u = 1.0f;
    } else {
        u = t;
    }
    u = sindf(u * 90.0f);
    HuVecCopy3F(&fromEye, &D_801146F0_option.fromEye);
    HuVecCopy3F(&toEye, &D_801146F0_option.toEye);
    HuVecCopyXYZ(&eye, (toEye.x - fromEye.x) * u + fromEye.x, (toEye.y - fromEye.y) * u + fromEye.y, (toEye.z - fromEye.z) * u + fromEye.z);
    HuVecCopy3F(&fromAt, &D_801146F0_option.fromAt);
    HuVecCopy3F(&toAt, &D_801146F0_option.toAt);
    HuVecCopyXYZ(&at, (toAt.x - fromAt.x) * u + fromAt.x, (toAt.y - fromAt.y) * u + fromAt.y, (toAt.z - fromAt.z) * u + fromAt.z);
    HuVecCopyXYZ(&d0, fromAt.x - fromEye.x, 0.0f, fromAt.z - fromEye.z);
    HuVecCopyXYZ(&d1, toAt.x - toEye.x, 0.0f, toAt.z - toEye.z);
    len0 = HuVecGetLength3F(&d0);
    t = HuVecGetLength3F(&d1);
    HuVecCopyXYZ(&d, at.x - eye.x, 0.0f, at.z - eye.z);
    t = ((t - len0) * u + len0) / HuVecGetLength3F(&d);
    HuVecCopyXYZ(&at, t * d.x + eye.x, (toAt.y - fromAt.y) * u + fromAt.y, t * d.z + eye.z);
    if (D_801146F0_option.t > D_801146F0_option.len) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.toEye, &D_801146F0_option.toAt, &up);
        D_801146F0_option.moveObj = NULL;
        return;
    }
    D_801146F0_option.t++;
    func_80106508_option(&eye, &at, &up);
}

omObjData *func_8010737C_option(Vec *eye, Vec *at, s32 len) {
    omObjData *obj;

    func_80106B78_option();
    obj = omAddObj(6, 0, 0, -1, func_80107058_option);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_801146F0_option.moveObj = obj;
    D_801146F0_option.t = 0;
    D_801146F0_option.len = len;
    HuVecCopy3F(&D_801146F0_option.fromAt, &D_801146F0_option.at);
    HuVecCopy3F(&D_801146F0_option.fromEye, &D_801146F0_option.eye);
    HuVecCopyXYZ(&D_801146F0_option.toAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&D_801146F0_option.toEye, eye->x, eye->y, eye->z);
    return obj;
}

/* Camera move turning the horizontal view direction round (D_80114764_option picks the way). */
void func_8010744C_option(omObjData *obj) {
    Vec eye;
    Vec at;
    Vec up;
    Vec fromEye;
    Vec toEye;
    Vec dir;
    Vec fromAt;
    Vec toAt;
    Vec d0;
    Vec d1;
    f32 len0;
    f32 t;
    f32 u;
    f32 s;

    t = (f32)D_801146F0_option.t / (f32)D_801146F0_option.len;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        u = 1.0f;
    } else {
        u = t;
    }
    HuVecCopy3F(&fromEye, &D_801146F0_option.fromEye);
    HuVecCopy3F(&toEye, &D_801146F0_option.toEye);
    HuVecCopyXYZ(&eye, (toEye.x - fromEye.x) * u + fromEye.x, (toEye.y - fromEye.y) * u + fromEye.y, (toEye.z - fromEye.z) * u + fromEye.z);
    HuVecCopy3F(&fromAt, &D_801146F0_option.fromAt);
    HuVecCopy3F(&toAt, &D_801146F0_option.toAt);
    HuVecCopyXYZ(&at, (toAt.x - fromAt.x) * u + fromAt.x, (toAt.y - fromAt.y) * u + fromAt.y, (toAt.z - fromAt.z) * u + fromAt.z);
    HuVecCopyXYZ(&d0, fromAt.x - fromEye.x, 0.0f, fromAt.z - fromEye.z);
    HuVecCopyXYZ(&d1, toAt.x - toEye.x, 0.0f, toAt.z - toEye.z);
    s = sindf(u * 90.0f);
    if (D_80114764_option != 0) {
        func_80107B80_option(&d0, &d1, s, &dir);
    } else {
        func_80107D64_option(&d0, &d1, s, &dir);
    }
    len0 = HuVecGetLength3F(&d0);
    t = (HuVecGetLength3F(&d1) - len0) * u + len0;
    HuVecCopyXYZ(&at, t * dir.x + eye.x, (toAt.y - fromAt.y) * u + fromAt.y, t * dir.z + eye.z);
    if (D_801146F0_option.t > D_801146F0_option.len) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.toEye, &D_801146F0_option.toAt, &up);
        D_801146F0_option.moveObj = NULL;
        return;
    }
    D_801146F0_option.t++;
    func_80106508_option(&eye, &at, &up);
}

omObjData *func_80107758_option(Vec *eye, Vec *at, s32 len) {
    omObjData *obj;

    obj = func_80106F88_option(eye, at, len);
    obj->func = func_8010744C_option;
    D_80114764_option = 1;
    return obj;
}

omObjData *func_8010778C_option(Vec *eye, Vec *at, s32 len) {
    omObjData *obj;

    obj = func_80106F88_option(eye, at, len);
    obj->func = func_8010744C_option;
    D_80114764_option = 0;
    return obj;
}

/* As func_8010744C_option, with the eye-to-target distance eased too. */
void func_801077BC_option(omObjData *obj) {
    Vec eye;
    Vec at;
    Vec up;
    Vec fromEye;
    Vec toEye;
    Vec dir;
    Vec fromAt;
    Vec toAt;
    Vec d0;
    Vec d1;
    f32 len0;
    f32 t;
    f32 u;
    f32 s;

    t = (f32)D_801146F0_option.t / (f32)D_801146F0_option.len;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        u = 1.0f;
    } else {
        u = t;
    }
    HuVecCopy3F(&fromEye, &D_801146F0_option.fromEye);
    HuVecCopy3F(&toEye, &D_801146F0_option.toEye);
    HuVecCopyXYZ(&eye, (toEye.x - fromEye.x) * u + fromEye.x, (toEye.y - fromEye.y) * u + fromEye.y, (toEye.z - fromEye.z) * u + fromEye.z);
    HuVecCopy3F(&fromAt, &D_801146F0_option.fromAt);
    HuVecCopy3F(&toAt, &D_801146F0_option.toAt);
    HuVecCopyXYZ(&at, (toAt.x - fromAt.x) * u + fromAt.x, (toAt.y - fromAt.y) * u + fromAt.y, (toAt.z - fromAt.z) * u + fromAt.z);
    HuVecCopyXYZ(&d0, fromAt.x - fromEye.x, 0.0f, fromAt.z - fromEye.z);
    HuVecCopyXYZ(&d1, toAt.x - toEye.x, 0.0f, toAt.z - toEye.z);
    s = sindf(u * 90.0f);
    if (D_80114764_option != 0) {
        func_80107B80_option(&d0, &d1, s, &dir);
    } else {
        func_80107D64_option(&d0, &d1, s, &dir);
    }
    len0 = HuVecGetLength3F(&d0);
    t = (HuVecGetLength3F(&d1) - len0) * s + len0;
    HuVecCopyXYZ(&at, t * dir.x + eye.x, (toAt.y - fromAt.y) * u + fromAt.y, t * dir.z + eye.z);
    if (D_801146F0_option.t > D_801146F0_option.len) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.toEye, &D_801146F0_option.toAt, &up);
        D_801146F0_option.moveObj = NULL;
        return;
    }
    D_801146F0_option.t++;
    func_80106508_option(&eye, &at, &up);
}

omObjData *func_80107AD4_option(Vec *eye, Vec *at, s32 len) {
    omObjData *obj;

    obj = func_80106F88_option(eye, at, len);
    obj->func = func_801077BC_option;
    D_80114764_option = 1;
    return obj;
}

omObjData *func_80107B08_option(Vec *eye, Vec *at, s32 len) {
    omObjData *obj;

    obj = func_80106F88_option(eye, at, len);
    obj->func = func_801077BC_option;
    D_80114764_option = 0;
    return obj;
}

f32 func_80107B38_option(f32 x0, f32 y0, f32 x1, f32 y1) {
    return -(atan2df(y1 - y0, x1 - x0) - 90.0f);
}

#ifdef NON_MATCHING
/* Turns the horizontal direction a towards b by the fraction t, the short way round (modesel
   func_801094F0_modesel); writes the unit direction to out. */
void func_80107B80_option(Vec *a, Vec *b, f32 t, Vec *out) {
    f32 end;
    f32 ang;
    f32 angA;
    f32 angB;

    angA = func_80107B38_option(0.0f, 0.0f, a->x, a->z);
    if (angA < 0.0f) {
        angA += 360.0f;
    }
    angB = func_80107B38_option(0.0f, 0.0f, b->x, b->z);
    if (angB < 0.0f) {
        angB += 360.0f;
    }
    if (-a->z * b->x + a->x * b->z > 0.0f) {
        end = angB;
        if (!(angB - angA < 0.0f)) {
            end = angB - 360.0f;
        }
        ang = (end - angA) * t + angA;
        if (ang < 0.0f) {
            ang += 360.0f;
        }
    } else {
        end = angB;
        if (!(angB - angA > 0.0f)) {
            end = angB + 360.0f;
        }
        ang = (end - angA) * t + angA;
        if (ang > 360.0f) {
            ang -= 360.0f;
        }
    }
    out->x = sindf(ang);
    out->y = 0.0f;
    out->z = cosdf(ang);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80107B80_option);
#endif

#ifdef NON_MATCHING
/* As func_80107B80_option, the long way round. */
void func_80107D64_option(Vec *a, Vec *b, f32 t, Vec *out) {
    f32 end;
    f32 ang;
    f32 angA;
    f32 angB;

    angA = func_80107B38_option(0.0f, 0.0f, a->x, a->z);
    if (angA < 0.0f) {
        angA += 360.0f;
    }
    angB = func_80107B38_option(0.0f, 0.0f, b->x, b->z);
    if (angB < 0.0f) {
        angB += 360.0f;
    }
    if (-a->z * b->x + a->x * b->z > 0.0f) {
        end = angB;
        if (!(angB - angA > 0.0f)) {
            end = angB + 360.0f;
        }
        ang = (end - angA) * t + angA;
        if (ang > 360.0f) {
            ang -= 360.0f;
        }
    } else {
        end = angB;
        if (!(angB - angA < 0.0f)) {
            end = angB - 360.0f;
        }
        ang = (end - angA) * t + angA;
        if (ang < 0.0f) {
            ang += 360.0f;
        }
    }
    out->x = sindf(ang);
    out->y = 0.0f;
    out->z = cosdf(ang);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80107D64_option);
#endif

OP_FILE_END()

/* The records board: ten windows, one per record (D_80113A08_option: the record numbers for
   GWMgRecordGet; D_80113A14_option: the unlock that names it, plus one), shown under a sprite
   (dataNum) at (x, y) until A or B is pressed. Times are frames: minutes, seconds and hundredths. */
void func_80107F50_option(s32 dataNum, s16 x, s16 y) {
    s16 win[10];
    u8 buf0[32];
    u8 buf1[32];
    u8 buf2[32];
    OpRecIds ids = D_80113A08_option;
    OpRecIds unlock = D_80113A14_option;
    s32 mes[10] = { 0x4501, 0x4502, 0x4503, 0x4504, 0x4505, 0x4506, 0x4507, 0x4508, 0x4509, 0x450A };
    s16 spr;
    s16 esp;
    s16 w;
    s16 rec;
    s16 i;
    s16 j;
    f32 scale;

    HuPrcSleep(3);
    spr = func_8000B838_main(dataNum);
    esp = InitEspriteSlot(spr, 0, 1);
    func_8000BBD4_main(esp, x, y);
    func_8000BCC8_main(esp, 0x8000);
    func_8000BE5C_main(esp, 0.0f, 0.0f);
    for (i = 0; i < 10; i++) {
        win[i] = func_80061188_main(-1, x - 104, y - 71 + i * 14, 213, 20, 0);
        func_8005BEE0_main(win[i], 0);
    }
    w = func_80061188_main(-1, 0, 0, 210, 14, 1);
    func_8005FBF8_main(w, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i < 11; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        func_8000BE5C_main(esp, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        rec = GWMgRecordGet(ids.id[i]);
        if (rec < 0) {
            rec = 0;
        }
        switch (ids.id[i]) {
            case 0:
                sprintf((char *)buf0, "%3d", rec);
                func_8005B6BC_main(win[i], (u32)buf0, 0);
                break;
            case 1:
            case 2:
            case 5:
            case 6:
            case 7:
                sprintf((char *)buf0, "%d", (s16)(rec / 3600));
                func_8005B6BC_main(win[i], (u32)buf0, 0);
                rec %= 3600;
                sprintf((char *)buf1, "%2d", (s16)(rec / 60));
                if (buf1[0] == ' ') {
                    buf1[0] = '0';
                }
                func_8005B6BC_main(win[i], (u32)buf1, 1);
                sprintf((char *)buf2, "%2d", (s16)((f32)(s16)(rec % 60) / 60.0f * 100.0f));
                if (buf2[0] == ' ') {
                    buf2[0] = '0';
                }
                func_8005B6BC_main(win[i], (u32)buf2, 2);
                break;
            case 4:
                sprintf((char *)buf0, "%3d", (s16)(rec / 100));
                rec %= 100;
                func_8005B6BC_main(win[i], (u32)buf0, 0);
                sprintf((char *)buf1, "%2d", rec);
                if (buf1[0] == ' ') {
                    buf1[0] = '0';
                }
                func_8005B6BC_main(win[i], (u32)buf1, 1);
                break;
            case 3:
            case 9:
                sprintf((char *)buf0, "%d", (s16)(rec / 1800));
                func_8005B6BC_main(win[i], (u32)buf0, 0);
                rec %= 1800;
                sprintf((char *)buf1, "%2d", (s16)(rec / 30));
                if (buf1[0] == ' ') {
                    buf1[0] = '0';
                }
                func_8005B6BC_main(win[i], (u32)buf1, 1);
                sprintf((char *)buf2, "%2d", (s16)((f32)(s16)(rec % 30) * (1.0f / 30.0f) * 99.0f));
                if (buf2[0] == ' ') {
                    buf2[0] = '0';
                }
                func_8005B6BC_main(win[i], (u32)buf2, 2);
                break;
            case 8:
                sprintf((char *)buf0, "%4d", rec);
                func_8005B6BC_main(win[i], (u32)buf0, 0);
                break;
        }
        func_8005FFA8_main(win[i]);
        rec = (s8)unlock.id[i] - 1; /* the unlock now */
        if (rec == 70 && _CheckFlag(0x2B)) {
            func_8005B43C_main(win[i], mes[i], -1, -1);
        } else if (rec >= 0 && GWMgUnlockCheck(rec)) {
            func_8005B43C_main(win[i], mes[i], -1, -1);
        } else if (rec == -1 && _CheckFlag(0x1E)) {
            func_8005B43C_main(win[i], mes[i], -1, -1);
        } else if (rec == -2 && _CheckFlag(0x1F)) {
            func_8005B43C_main(win[i], mes[i], -1, -1);
        } else {
            func_8005B43C_main(win[i], 0x4500, -1, -1);
        }
        func_8005BA90_main(w, x, y - 62 + i * 14);
        func_8005FFA8_main(w);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            func_8005BEE0_main(w, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
    }
    func_8005F364_main(w);
    do {
        HuPrcVSleep();
    } while (!(D_800D5558_main[0] & 0xC000));
    for (i = 0; i < 10; i++) {
        func_8005FE90_main(win[i]);
    }
    HuAudFXPlay(0x2E9);
    for (i = 1; i < 11; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        func_8000BE5C_main(esp, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        func_8005F364_main(win[i]);
    }
    func_8000C184_main(esp);
    HuSprKill(spr);
}

void func_80108A68_option(void) {
    func_80108B34_option();
    func_80112060_option();
    D_80114770_option = omAddPrcObj(func_80108B58_option, 0x5000, 0x2000, 0);
}

void func_80108AAC_option(void) {
    func_80108B34_option();
    func_80112060_option();
    D_80114770_option = omAddPrcObj(func_8010A66C_option, 0x5000, 0x2000, 0);
}

void func_80108AF0_option(void) {
    func_80108B34_option();
    func_80112060_option();
    D_80114770_option = omAddPrcObj(func_8010C224_option, 0x5000, 0x2000, 0);
}

void func_80108B34_option(void) {
    func_8010F94C_option();
    func_8010FDF4_option();
}

/* Camera points of the screen process (func_80108B58_option); D_80113A98_option is the up vector. */
const Vec D_80113A80_option = { 0.0f, 271.19f, 1191.11f };
const Vec D_80113A8C_option = { 0.0f, 228.72f, -550.0f };
const Vec D_80113A98_option = { 0.0f, 1.0f, 0.0f };
const Vec D_80113AA4_option = { 0.0f, 271.19f, 350.0f };
const Vec D_80113AB0_option = { -535.0f, 228.72f, -550.0f };
const Vec D_80113ABC_option = { 0.0f, 228.72f, 350.0f };
const Vec D_80113AC8_option = { -160.0f, 228.72f, 50.0f };
const Vec D_80113AD4_option = { 450.0f, 228.72f, 1191.11f };
const Vec D_80113AE0_option = { 535.0f, 228.72f, -550.0f };
const Vec D_80113AEC_option = { 160.0f, 228.72f, 50.0f };
const Vec D_80113AF8_option = { -450.0f, 228.72f, 1191.11f };
const Vec D_80113B04_option = { 0.0f, 410.0f, -550.0f };
const Vec D_80113B10_option = { 0.0f, 228.72f, 50.0f };
const Vec D_80113B1C_option = { 0.0f, 228.72f, 1191.11f };

/* The screen process: camera flight in for the entry (omovlevtno), the menu (func_80109504_option),
   camera flight out, then the next overlay. */
void func_80108B58_option(void) {
    Vec eye;
    Vec at;
    Vec up;
    Vec eye2_0;
    Vec at2_0;
    Vec eye0_1;
    Vec at0_1;
    Vec up0_1;
    Vec eye1_1;
    Vec at1_1;
    Vec eye2_1;
    Vec at2_1;
    Vec eye0_2;
    Vec at0_2;
    Vec up0_2;
    Vec eye1_2;
    Vec at1_2;
    Vec eye2_2;
    Vec at2_2;
    Vec eye0_3;
    Vec at0_3;
    Vec up0_3;
    Vec eye1_3;
    Vec at1_3;
    Vec eye2_3;
    Vec at2_3;
    Vec eye3_3;
    Vec at3_3;
    Vec eye0_D;
    Vec at0_D;
    s32 choice;
    s32 next;

    next = 1;
    func_8001F38C_main(0, 0x40, 0x40);
    func_80112084_option();
    func_8010FB40_option(0, 9);
    func_8010FB40_option(1, 10);
    switch (omovlevtno) {
        case 0:
            func_8004A5C4_main(7);
            WipeCreateIn(11, 16);
            eye = D_80113A80_option;
            at = D_80113A8C_option;
            up = D_80113A98_option;
            func_80106508_option(&eye, &at, &up);
            eye2_0 = D_80113AA4_option;
            at2_0 = D_80113A8C_option;
            func_8010737C_option(&eye2_0, &at2_0, 45);
            HuPrcSleep(45);
            break;
        case 1:
            func_8004A5C4_main(7);
            WipeColorSet(255, 255, 255);
            WipeCreateIn(11, 16);
            eye0_1 = D_80113AB0_option;
            at0_1 = D_80113ABC_option;
            up0_1 = D_80113A98_option;
            func_80106508_option(&eye0_1, &at0_1, &up0_1);
            eye1_1 = D_80113AC8_option;
            at1_1 = D_80113AD4_option;
            func_80107AD4_option(&eye1_1, &at1_1, 46);
            HuPrcSleep(46);
            eye2_1 = D_80113AA4_option;
            at2_1 = D_80113A8C_option;
            func_80107758_option(&eye2_1, &at2_1, 45);
            HuPrcSleep(45);
            break;
        case 2:
            func_8004A5C4_main(7);
            WipeColorSet(255, 255, 255);
            WipeCreateIn(11, 16);
            eye0_2 = D_80113AE0_option;
            at0_2 = D_80113ABC_option;
            up0_2 = D_80113A98_option;
            func_80106508_option(&eye0_2, &at0_2, &up0_2);
            eye1_2 = D_80113AEC_option;
            at1_2 = D_80113AF8_option;
            func_80107AD4_option(&eye1_2, &at1_2, 46);
            HuPrcSleep(46);
            eye2_2 = D_80113AA4_option;
            at2_2 = D_80113A8C_option;
            func_80107758_option(&eye2_2, &at2_2, 45);
            HuPrcSleep(45);
            break;
        case 3:
            WipeColorSet(255, 255, 255);
            WipeCreateIn(11, 16);
            eye0_3 = D_80113B04_option;
            at0_3 = D_80113ABC_option;
            up0_3 = D_80113A98_option;
            func_80106508_option(&eye0_3, &at0_3, &up0_3);
            eye1_3 = D_80113B10_option;
            at1_3 = D_80113ABC_option;
            func_80106F88_option(&eye1_3, &at1_3, 50);
            HuPrcSleep(50);
            eye2_3 = D_80113ABC_option;
            at2_3 = D_80113B1C_option;
            func_8010737C_option(&eye2_3, &at2_3, 25);
            HuPrcSleep(25);
            eye3_3 = D_80113ABC_option;
            at3_3 = D_80113A8C_option;
            func_80107758_option(&eye3_3, &at3_3, 35);
            HuPrcSleep(35);
            break;
        default:
            func_8004A5C4_main(7);
            WipeCreateIn(11, 16);
            eye0_D = D_80113A80_option;
            at0_D = D_80113A8C_option;
            func_80107758_option(&eye0_D, &at0_D, 45);
            HuPrcSleep(16);
            break;
    }
    choice = func_80109504_option();
    func_801133A0_option(0);
    switch (choice) {
        case 0:
            HuVecCopy3F(&eye, &D_801136F4_option);
            eye.y += 20.0f;
            HuVecCopy3F(&at, &D_80113700_option);
            at.y += 20.0f;
            HuAudFXPlay(0x2EB);
            func_801132AC_option(0, 0);
            func_801132E4_option(0, 0);
            func_80113300_option(0);
            func_80106F88_option(&eye, &at, 20);
            func_8010FFDC_option();
            WipeCreateOut(11, 20);
            HuPrcSleep(20);
            break;
        case 1:
            HuVecCopy3F(&eye, &D_8011370C_option);
            eye.z += 200.0f;
            HuVecCopy3F(&at, &D_80113718_option);
            func_80113338_option(9, 12, 0, 8, 0);
            HuAudFXPlay(0x2EB);
            func_8011331C_option(0, 6, 0);
            func_80113300_option(0);
            eye.z -= 200.0f;
            at.z -= 200.0f;
            func_80106F88_option(&eye, &at, 20);
            func_8010FFDC_option();
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 2:
            HuVecCopy3F(&eye, &D_80113724_option);
            eye.z += 200.0f;
            HuVecCopy3F(&at, &D_80113730_option);
            func_80113338_option(10, 11, 0, 8, 0);
            HuAudFXPlay(0x2EB);
            func_8011331C_option(0, 7, 0);
            func_801132E4_option(0, 0);
            func_80113300_option(0);
            eye.z -= 200.0f;
            at.z -= 200.0f;
            func_80106F88_option(&eye, &at, 20);
            func_8010FFDC_option();
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 3:
        case 4:
            HuVecCopy3F(&eye, &D_8011373C_option);
            HuVecCopy3F(&at, &D_80113748_option);
            func_80106F88_option(&eye, &at, 30);
            HuPrcSleep(20);
            func_80106B78_option();
            HuAudFXPlay(0x2E1);
            func_801132AC_option(1, 0);
            func_801132E4_option(1, 0);
            func_80113300_option(1);
            func_80106F88_option(&eye, &at, 20);
            func_8010FFDC_option();
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 9:
        default:
            choice = 9;
            break;
    }
    next = choice;
    func_8010FA28_option();
    func_8011239C_option();
    func_8005F524_main();
    omOvlKill();
    switch (next) {
        case 0:
            omOvlHisChg(0, 0x7B, 3, 0x91);
            omOvlCallEx(0x7B, 6, 0x91);
            break;
        case 1:
            omOvlGotoEx(0x7B, 4, 0x91);
            break;
        case 2:
            omOvlGotoEx(0x7B, 5, 0x91);
            break;
        case 3:
            omOvlReturnEx(1);
            omOvlHisChg(0, 0x77, 3, 0x91);
            break;
        case 9:
        default:
            omOvlReturnEx(1);
            break;
    }
    omDelPrcObj(D_80114770_option);
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_80109504_option(void) {
    Vec at;
    s32 x, y;
    s32 sel;
    s32 btn;
    s32 ret;

    sel = 0;
    if (func_800465E8_main() != 0) {
        func_800465F4_main(1);
        func_801133BC_option(0, 0x4E00);
        func_80113490_option(0);
        func_80113408_option(0, 0x4E02);
    } else {
        func_801133BC_option(0, 0x4E02);
    }
    func_80113384_option(0);
    func_8010A3E8_option(sel, 0);
    while (1) {
        btn = D_800D5558_main[0];
        btn |= func_801130E8_option(0);
        if (btn & 0x8000) {
            ret = func_80109D04_option(sel, btn);
            if (ret != -1) {
                sel = ret;
                break;
            }
        } else if (btn & 0xF00) {
            sel = func_80109EF4_option(sel, btn);
        } else if (btn & 0x4000) {
            func_801133A0_option(0);
            func_80113440_option(0);
            switch (sel) {
            case 2:
                goto move;
            case 0:
            case 1:
            move:
                HuVecCopy3F(&at, &D_80113514_option[0]);
                func_80107758_option(&D_80113514_option[-1], &at, 30);
                HuPrcSleep(30);
                break;
            case 3:
                break;
            }
            sel = 3;
            func_80109908_option(0.0f, 100.0f, 1275.0f, &x, &y);
            func_80112028_option(0, x, y);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E03);
            func_80113384_option(0);
        }
        HuPrcVSleep();
    }
    func_801133EC_option(0);
    return sel;
}

void func_801096B8_option(s32 arg0, s32 x, s32 y) {
    D_80114778_option.x = x;
    D_80114778_option.y = y;
    func_80112028_option(arg0, 160, y);
}

void func_801096E4_option(s32 arg0) {
    if (++D_80114778_option.unkC > 20) {
        D_80114778_option.unkC = 0;
    }
    D_80114778_option.unk8 = 0;
    func_80112028_option(arg0, D_80114778_option.x, D_80114778_option.y);
}

#ifdef NON_MATCHING
/* Matches except two FP registers swapped (dy <-> fov). */
void func_80109730_option(Vec *eye, Vec *at, Vec *up, f32 fov, Vec *pos, f32 *x, f32 *y) {
    f32 mtx[4][4];
    f32 dx, dy, dz;
    f32 vx, vy, vz;

    guLookAtF(mtx, eye->x, eye->y, eye->z, at->x, at->y, at->z, up->x, up->y, up->z);
    dx = pos->x;
    dy = pos->y;
    dz = pos->z;
    dx -= eye->x;
    dy -= eye->y;
    dz -= eye->z;
    vx = dx * mtx[0][0] + dy * mtx[1][0] + dz * mtx[2][0];
    vy = dx * mtx[0][1] + dy * mtx[1][1] + dz * mtx[2][1];
    vz = dx * mtx[0][2] + dy * mtx[1][2] + dz * mtx[2][2];
    fov /= 2.0f;
    dy = sindf(fov);
    dx = dy / cosdf(fov) * vz * 1.3333334f;
    dy = sindf(fov);
    dy = dy / cosdf(fov) * vz;
    *x = vx * (160.0f / -dx) + 160.0f;
    *y = vy * (120.0f / dy) + 120.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80109730_option);
#endif

void func_80109908_option(f32 x, f32 y, f32 z, s32 *outX, s32 *outY) {
    Vec pos;
    f32 sx, sy;
    HuCamera *cam = gCameraList;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80109730_option(&cam->pos, &cam->at, &cam->up, cam->fov[0], &pos, &sx, &sy);
    *outX = sx;
    *outY = sy;
}

void func_8010998C_option(Vec *eye, Vec *at, Vec *up, f32 x, f32 y, f32 z, s32 *outX, s32 *outY) {
    Vec pos;
    f32 sx, sy;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80109730_option(eye, at, up, gCameraList->fov[0], &pos, &sx, &sy);
    *outX = sx;
    *outY = sy;
}



void func_80109A0C_option(s32 arg0, Vec *from, Vec *to, s32 len) {
    f32 p0[2];
    f32 p1[2];
    s32 x, y;
    f32 t;
    s32 i;

    for (i = 0; i <= len; i++) {
        func_80109908_option(from->x, from->y, from->z, &x, &y);
        p0[0] = x;
        p0[1] = y;
        func_80109908_option(to->x, to->y, to->z, &x, &y);
        p1[0] = x;
        p1[1] = y;
        t = (1.0f / len) * i;
        func_80112028_option(arg0, t * (p1[0] - p0[0]) + p0[0], t * (p1[1] - p0[1]) + p0[1]);
        HuPrcVSleep();
    }
    func_80112028_option(arg0, p1[0], p1[1]);
}

void func_80109B7C_option(s32 arg0, s32 x0, s32 y0, s32 x1, s32 y1, s32 len) {
    f32 t;
    s32 i;

    for (i = 0; i <= len; i++) {
        t = (1.0f / len) * i;
        func_80112028_option(arg0, x0 + t * (x1 - x0), y0 + t * (y1 - y0));
        HuPrcVSleep();
    }
    func_80112028_option(arg0, x1, y1);
}

void func_80109CB0_option(s32 sel, s32 *x, s32 *y) {
    s32 xpos = 160;
    s32 ypos = 120;

    switch (sel) {
    case 0:
        xpos = 160;
        ypos = 80;
        break;
    case 1:
    case 2:
        xpos = 160;
        ypos = 130;
        break;
    case 3:
    case 4:
        xpos = 160;
        ypos = 110;
        break;
    case 5:
        break;
    }
    *x = xpos;
    *y = ypos;
}

s32 func_80109D04_option(s32 sel, s32 btn) {
    switch (sel) {
    case 0:
        func_801133A0_option(0);
        func_80113440_option(0);
        {
            Vec eye = { 0.0f, 430.0f, -150.0f };
            Vec at = { 0.0f, 430.0f, -550.0f };

            func_8010737C_option(&eye, &at, 30);
        }
        func_80113338_option(9, 11, 0, 8, 0);
        func_80113338_option(10, 12, 0, 8, 0);
        HuPrcSleep(30);
        break;
    case 1:
        func_801133A0_option(0);
        func_80113440_option(0);
        {
            Vec eye = { -535.0f, 128.72f, -150.0f };
            Vec at = { -535.0f, 78.72f, -550.0f };

            func_8010737C_option(&eye, &at, 20);
        }
        HuPrcSleep(20);
        break;
    case 2:
        func_801133A0_option(0);
        func_80113440_option(0);
        {
            Vec eye = { 535.0f, 128.72f, -150.0f };
            Vec at = { 535.0f, 78.72f, -550.0f };

            func_8010737C_option(&eye, &at, 20);
        }
        HuPrcSleep(20);
        break;
    case 3:
        func_801133A0_option(0);
        func_80113408_option(0, 0x4E04);
        if (func_8011345C_option(0) != 0) {
            func_80113408_option(0, 0x4E03);
            func_80113384_option(0);
            return -1;
        }
        sel = 3;
        break;
    case 9:
        break;
    }
    return sel;
}

s32 func_80109EF4_option(s32 sel, s32 btn) {
    Vec up = D_80113A98_option;
    s32 x0, y0, x1, y1;

    switch (sel) {
    case 0:
        if (btn & 0x200) {
            sel = 1;
            func_80107758_option(&D_801137CC_option[0], &D_801137CC_option[1], 7);
            func_80113368_option(0, &x0, &y0);
            func_8010998C_option(&D_801137CC_option[0], &D_801137CC_option[1], &up, D_8011376C_option[1].x, D_8011376C_option[1].y, D_8011376C_option[1].z, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 7);
            func_80113408_option(0, 0x4E01);
        } else if (btn & 0x100) {
            sel = 2;
            func_80107758_option(&D_801137E4_option[0], &D_801137E4_option[1], 7);
            func_80113368_option(0, &x0, &y0);
            func_8010998C_option(&D_801137E4_option[0], &D_801137E4_option[1], &up, D_8011376C_option[2].x, D_8011376C_option[2].y, D_8011376C_option[2].z, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 7);
            func_80113408_option(0, 0x4E01);
        }
        break;
    case 1:
        if (btn & 0x200) {
            sel = 3;
            func_80107758_option(&D_801137B4_option[0], &D_801137B4_option[1], 20);
            func_801133A0_option(0);
            func_80113440_option(0);
            HuPrcSleep(20);
            func_80109908_option(D_8011376C_option[3].x, D_8011376C_option[3].y, D_8011376C_option[3].z, &x0, &y0);
            func_80112028_option(0, x0, y0);
            func_80113258_option(0);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E03);
        } else if (btn & 0x100) {
            sel = 0;
            func_80107758_option(&D_8011379C_option[0], &D_8011379C_option[1], 7);
            func_80113368_option(0, &x0, &y0);
            func_8010998C_option(&D_8011379C_option[0], &D_8011379C_option[1], &up, D_8011376C_option[0].x, D_8011376C_option[0].y, D_8011376C_option[0].z, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 7);
            func_80113408_option(0, 0x4E02);
        }
        break;
    case 2:
        if (btn & 0x200) {
            sel = 0;
            func_80107758_option(&D_8011379C_option[0], &D_8011379C_option[1], 7);
            func_80113368_option(0, &x0, &y0);
            func_8010998C_option(&D_8011379C_option[0], &D_8011379C_option[1], &up, D_8011376C_option[0].x, D_8011376C_option[0].y, D_8011376C_option[0].z, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 7);
            func_80113408_option(0, 0x4E02);
        } else if (btn & 0x100) {
            sel = 3;
            func_80107758_option(&D_801137B4_option[0], &D_801137B4_option[1], 20);
            func_801133A0_option(0);
            func_80113440_option(0);
            HuPrcSleep(20);
            func_80109908_option(D_8011376C_option[3].x, D_8011376C_option[3].y, D_8011376C_option[3].z, &x0, &y0);
            func_80112028_option(0, x0, y0);
            func_80113258_option(0);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E03);
        }
        break;
    case 3:
        if (btn & 0x200) {
            sel = 2;
            func_80107758_option(&D_801137E4_option[0], &D_801137E4_option[1], 20);
            func_801133A0_option(0);
            func_80113440_option(0);
            func_8011323C_option(0);
            HuPrcSleep(20);
            func_80109908_option(D_8011376C_option[2].x, D_8011376C_option[2].y, D_8011376C_option[2].z, &x0, &y0);
            func_80112028_option(0, x0, y0);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E01);
        } else if (btn & 0x100) {
            sel = 1;
            func_80107758_option(&D_801137CC_option[0], &D_801137CC_option[1], 20);
            func_801133A0_option(0);
            func_80113440_option(0);
            func_8011323C_option(0);
            HuPrcSleep(20);
            func_80109908_option(D_8011376C_option[1].x, D_8011376C_option[1].y, D_8011376C_option[1].z, &x0, &y0);
            func_80112028_option(0, x0, y0);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E01);
        }
        break;
    case 4:
        break;
    }
    return sel;
}

void func_8010A3E8_option(s32 sel, s32 arg1) {
    s32 i;
    s32 x, y;

    i = 0;
    switch (sel) {
    case 0:
        i = 0;
        break;
    case 1:
        i = 1;
        break;
    case 2:
        i = 2;
        break;
    case 3:
        i = 3;
        break;
    }
    func_80109908_option(D_8011376C_option[i].x, D_8011376C_option[i].y, D_8011376C_option[i].z, &x, &y);
    func_80112028_option(0, x, y);
}

s32 func_8010A498_option(void) {
    Vec eye;
    Vec at;
    s32 sel;
    s32 btn;
    s32 ret;

    sel = 0;
    func_80105F08_option(41.539f);
    func_801133BC_option(0, 0x4E05);
    func_80113490_option(0);
    func_80113408_option(0, 0x4E06);
    func_80113384_option(0);
    func_8010B654_option(0, 0);
    while (1) {
        btn = D_800D5558_main[0];
        btn |= func_801130E8_option(0);
        if (btn & 0x8000) {
            ret = func_8010AF54_option(sel, btn);
            if (ret != -1) {
                sel = ret;
                break;
            }
        } else if (btn & 0xF00) {
            sel = func_8010A940_option(sel, btn);
        } else if (btn & 0x4000) {
            func_801133A0_option(0);
            func_80113440_option(0);
            switch (sel) {
            case 0:
            case 1:
            case 2:
                sel = 4;
                HuVecCopy3F(&eye, &D_80113580_option[4][0]);
                HuVecCopy3F(&at, &D_80113580_option[4][1]);
                func_80107758_option(&eye, &at, 20);
                HuPrcSleep(20);
                break;
            case 3:
                sel = 5;
                HuVecCopy3F(&eye, &D_80113580_option[5][0]);
                HuVecCopy3F(&at, &D_80113580_option[5][1]);
                func_80107758_option(&eye, &at, 20);
                HuPrcSleep(20);
                break;
            case 4:
            case 5:
                break;
            }
            func_80113424_option(0);
            func_80113408_option(0, 0x4E0B);
            func_80113384_option(0);
        }
        func_8010B654_option(sel, btn);
        HuPrcVSleep();
    }
    func_801133EC_option(0);
    return sel;
}

#ifdef NON_MATCHING
/* Only difference: retail sets sel = 9 then copies it to mode in the default case (li s1,9; move s0,s1); this C gives li s0,9. */
void func_8010A66C_option(void) {
    Vec eye;
    Vec at;
    s32 sel;
    s32 mode;

    func_8001F38C_main(0, 64, 64);
    func_801123D8_option();
    HuAudSeqPlay(0x4A);
    WipeCreateIn(11, 16);
    HuPrcSleep(16);
    sel = func_8010A498_option();
    func_801133A0_option(0);
    switch (sel) {
    case 4:
        HuVecCopy3F(&eye, &D_801137FC_option);
        HuVecCopy3F(&at, &D_80113808_option);
        eye.z -= 200.0f;
        func_80106F88_option(&eye, &at, 20);
        HuPrcSleep(20);
        HuAudFXPlay(0x2EB);
        func_801132AC_option(1, 0);
        func_801132E4_option(1, 0);
        func_80113300_option(1);
        eye.z += 200.0f;
        func_80106F88_option(&eye, &at, 20);
        goto fade;
    case 5:
        HuVecCopy3F(&eye, &D_80113814_option);
        HuVecCopy3F(&at, &D_80113820_option);
        eye.z -= 200.0f;
        func_80106F88_option(&eye, &at, 20);
        HuPrcSleep(20);
        HuAudFXPlay(0x2EB);
        func_801132AC_option(1, 0);
        func_8011331C_option(1, 12, 0);
        func_801132E4_option(1, 0);
        func_80113300_option(1);
        eye.z += 200.0f;
        func_80106F88_option(&eye, &at, 20);
    case 0:
    case 1:
    case 2:
    case 3:
    fade:
        mode = sel;
        func_8010FFDC_option();
        WipeColorSet(255, 255, 255);
        WipeCreateOut(11, 20);
        HuAudSeqFadeOut(20);
        HuPrcSleep(20);
        break;
    case 9:
    default:
        sel = 9;
        mode = sel;
        break;
    }
    func_80112A44_option();
    func_8005F524_main();
    omOvlKill();
    switch (mode) {
    case 4:
        omOvlGotoEx(0x7B, 1, 0x91);
        break;
    case 5:
        omOvlGotoEx(0x7B, 2, 0x91);
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 9:
    default:
        omOvlReturnEx(1);
        break;
    }
    omDelPrcObj(D_80114770_option);
    while (1) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010A66C_option);
#endif

void func_8010A8DC_option(s32 sel, s32 *x, s32 *y) {
    s32 xpos = 160;
    s32 ypos = 120;

    switch (sel) {
    case 0:
        if (!(D_800D09A8_main & 1)) {
            xpos = 224;
            ypos = 56;
        } else {
            xpos = 184;
            ypos = 56;
        }
        break;
    case 1:
        xpos = 160;
        ypos = 130;
        break;
    case 2:
        xpos = 160;
        ypos = 130;
        break;
    case 3:
        xpos = 160;
        ypos = 130;
        break;
    case 4:
        xpos = 160;
        ypos = 130;
        break;
    case 5:
        xpos = 160;
        ypos = 130;
        break;
    case 6:
        break;
    }
    *x = xpos;
    *y = ypos;
}

s32 func_8010A940_option(s32 sel, s32 btn) {
    Vec eye;
    Vec at;
    s32 x0, y0, x1, y1;

    switch (sel) {
    case 0:
        if (btn & 0x200) {
            sel = 2;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 8);
            func_80113258_option(6);
            func_80113258_option(7);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 8);
            func_80113408_option(0, 0x4E0A);
        } else if (btn & 0x100) {
            sel = 3;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 8);
            func_80113258_option(6);
            func_80113258_option(7);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 8);
            func_80113408_option(0, 0x4E09);
        }
        break;
    case 1:
        break;
    case 2:
        if (btn & 0x200) {
            sel = 4;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 20);
            func_801133A0_option(0);
            func_80113440_option(0);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 20);
            HuPrcSleep(12);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E0B);
        } else if (btn & 0x100) {
            sel = 0;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 8);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 8);
            func_80113408_option(0, 0x4E06);
            func_8011323C_option(6);
            func_8011323C_option(7);
        }
        break;
    case 3:
        if (btn & 0x200) {
            sel = 0;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 8);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 8);
            func_80113408_option(0, 0x4E06);
            func_8011323C_option(6);
            func_8011323C_option(7);
        } else if (btn & 0x100) {
            sel = 5;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 20);
            func_801133A0_option(0);
            func_80113440_option(0);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 20);
            HuPrcSleep(12);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E0B);
        }
        break;
    case 4:
        if (btn & 0x200) {
            sel = 5;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 8);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 8);
            func_80113408_option(0, 0x4E0B);
        } else if (btn & 0x100) {
            sel = 2;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 20);
            func_801133A0_option(0);
            func_80113440_option(0);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 20);
            HuPrcSleep(12);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E0A);
        }
        break;
    case 5:
        if (btn & 0x200) {
            sel = 3;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 20);
            func_801133A0_option(0);
            func_80113440_option(0);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 20);
            HuPrcSleep(12);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E09);
        } else if (btn & 0x100) {
            sel = 4;
            HuVecCopy3F(&eye, &D_80113580_option[sel][0]);
            HuVecCopy3F(&at, &D_80113580_option[sel][1]);
            func_80107758_option(&eye, &at, 8);
            func_80113368_option(0, &x0, &y0);
            func_8010A8DC_option(sel, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 8);
            func_80113408_option(0, 0x4E0B);
        }
        break;
    }
    return sel;
}

#ifdef NON_MATCHING
/* Matches except s3/s4 swapped (ret and the hoisted constant 2). */
s32 func_8010AF54_option(s32 sel, s32 btn) {
    s32 no;
    s16 model;
    u8 *flag;
    s32 ret = -1;

    switch (sel) {
    case 0: {
        Vec cam[2] = { { 0.0f, 264.9f, 164.27f }, { 0.0f, 184.6f, -138.7f } };

        func_80113258_option(6);
        func_80113258_option(7);
        func_801133A0_option(0);
        func_80113440_option(0);
        func_80106F88_option(&cam[0], &cam[1], 8);
        HuPrcSleep(8);
        func_801133EC_option(0);
        flag = &D_800D09A8_main;
        do {
            if (!(*flag & 1)) {
                func_801133BC_option(0, 0x4E07);
                func_80113408_option(0, 0x4E07);
                no = func_8011345C_option(0);
                if (no == 0) {
                    func_801133A0_option(0);
                    HuPrcVSleep();
                    *flag |= 1;
                    func_80000F30_main(1);
                    RepeatVibrator(0, 5, 0, 5);
                    func_80050CFC_main();
                    func_80113440_option(0);
                    func_801133EC_option(0);
                    func_80113338_option(8, 11, 0, 8, 0);
                    func_801132C8_option(21, 1);
                    func_801132E4_option(21, 0);
                    func_80113300_option(8);
                    func_80113338_option(8, 10, 0, 8, 2);
                    func_801132C8_option(4, 7);
                    func_80113300_option(4);
                    func_8011331C_option(4, 17, 0);
                    func_801132E4_option(4, 40);
                    func_801132AC_option(4, 4);
                    HuAudFXPlay(0x2F5);
                    func_8011331C_option(5, 19, 0);
                    func_801132C8_option(5, 7);
                    func_801132E4_option(5, 0);
                    func_80113300_option(5);
                    func_8011331C_option(5, 20, 2);
                    func_801132AC_option(5, 2);
                }
            } else {
                func_801133BC_option(0, 0x4E08);
                func_80113408_option(0, 0x4E08);
                no = func_8011345C_option(0);
                if (no == 0) {
                    func_801133A0_option(0);
                    HuPrcVSleep();
                    *flag &= 0xFE;
                    func_80000F30_main(0);
                    RepeatVibrator(0, 5, 0, 5);
                    func_80050CFC_main();
                    func_801133EC_option(0);
                    func_80113338_option(8, 11, 0, 2, 0);
                    func_801132C8_option(21, 1);
                    func_801132E4_option(21, 0);
                    func_80113300_option(8);
                    func_80113338_option(8, 10, 0, 8, 2);
                    func_801132C8_option(5, 7);
                    func_80113300_option(5);
                    func_8011331C_option(5, 19, 0);
                    func_801132E4_option(5, 40);
                    func_801132AC_option(5, 4);
                    HuAudFXPlay(0x2F5);
                    func_8011331C_option(4, 17, 0);
                    func_801132C8_option(4, 7);
                    func_801132E4_option(4, 0);
                    func_80113300_option(4);
                    func_8011331C_option(4, 18, 2);
                    func_801132AC_option(4, 2);
                }
            }
            func_8010B654_option(sel, 0);
        } while (no == 0);
        func_80113408_option(0, 0x4E06);
        {
            Vec cam2[2] = { { 0.0f, 264.9f, 364.27f }, { 0.0f, 184.6f, 61.3f } };

            func_80113440_option(0);
            func_80106F88_option(&cam2[0], &cam2[1], 8);
        }
        HuPrcSleep(8);
        func_80113384_option(0);
        func_80113424_option(0);
        func_8011323C_option(6);
        func_8011323C_option(7);
        break;
    }
    case 1:
        break;
    case 2:
        func_801133A0_option(0);
        func_80106F88_option(&D_8011382C_option[0], &D_8011382C_option[1], 8);
        HuAudFXPlay(0x2EA);
        func_801132E4_option(2, 0);
        func_801132C8_option(2, 7);
        func_801132AC_option(2, 0);
        func_80113300_option(2);
        func_80113440_option(0);
        func_8004A9DC_main(0x60);
        func_8010E8E0_option();
        func_8004A9DC_main(0x7F);
        func_80106F88_option(&D_80113844_option[0], &D_80113844_option[1], 8);
        func_801132E4_option(2, 40);
        func_801132C8_option(2, 7);
        func_801132AC_option(2, 4);
        model = func_80113218_option(2);
        while (HmfModelData[model].unk40 != 0.0f) {
            HuPrcVSleep();
        }
        func_80113424_option(0);
        func_80113384_option(0);
        break;
    case 3:
        func_80113440_option(0);
        func_801133A0_option(0);
        func_80106F88_option(&D_8011385C_option[0], &D_8011385C_option[1], 8);
        HuAudFXPlay(0x2EA);
        func_801132E4_option(3, 0);
        func_801132C8_option(3, 7);
        func_801132AC_option(3, 0);
        func_80113300_option(3);
        func_8010F138_option();
        HuAudSeqPlay(0x4A);
        func_80106F88_option(&D_80113874_option[0], &D_80113874_option[1], 8);
        func_801132E4_option(3, 40);
        func_801132C8_option(3, 7);
        func_801132AC_option(3, 4);
        model = func_80113218_option(3);
        while (HmfModelData[model].unk40 != 0.0f) {
            HuPrcVSleep();
        }
        func_80113424_option(0);
        func_80113384_option(0);
        break;
    case 4:
    case 5:
        func_801133A0_option(0);
        func_80113408_option(0, 0x4E0C);
        if (func_8011345C_option(0) != 0) {
            func_80113408_option(0, 0x4E0B);
            func_80113384_option(0);
            return -1;
        }
    case 9:
    default:
        ret = sel;
        break;
    }
    return ret;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113CB8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113CD0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010AF54_option);
#endif

void func_8010B654_option(s32 sel, s32 btn) {
    s32 x, y;

    func_8010A8DC_option(sel, &x, &y);
    func_801096B8_option(0, x, y);
    func_801096E4_option(0);
}


s32 func_8010B68C_option(s32 sel, s32 btn) {
    Vec eye;
    Vec at;
    Vec up = D_80113A98_option;
    s32 x0, y0, x1, y1;

    switch (sel) {
    case 0:
        if (btn & 0x200) {
            sel = 1;
        } else if (btn & 0x100) {
            sel = 2;
        }
        break;
    case 1:
        if (btn & 0x200) {
            sel = 3;
            HuVecCopy3F(&eye, &D_80113694_option[0]);
            HuVecCopy3F(&at, &D_801136AC_option[1]);
            func_80107758_option(&eye, &at, 30);
            func_801133A0_option(0);
            func_80113440_option(0);
            HuPrcSleep(30);
            func_80109908_option(D_8011388C_option[2].x, D_8011388C_option[2].y, D_8011388C_option[2].z, &x0, &y0);
            func_80112028_option(0, x0, y0);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E12);
        } else if (btn & 0x100) {
            sel = 2;
            func_80107758_option(&D_80113694_option[0], &D_80113694_option[1], 7);
            func_80113368_option(0, &x0, &y0);
            func_8010998C_option(&D_80113694_option[0], &D_80113694_option[1], &up, D_8011388C_option[1].x, D_8011388C_option[1].y, D_8011388C_option[1].z, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 7);
            func_80113408_option(0, 0x4E0E);
        }
        break;
    case 2:
        if (btn & 0x200) {
            sel = 1;
            func_80107758_option(&D_8011367C_option[0], &D_8011367C_option[1], 7);
            func_80113368_option(0, &x0, &y0);
            func_8010998C_option(&D_8011367C_option[0], &D_8011367C_option[1], &up, D_8011388C_option[0].x, D_8011388C_option[0].y, D_8011388C_option[0].z, &x1, &y1);
            func_80109B7C_option(0, x0, y0, x1, y1, 7);
            func_80113408_option(0, 0x4E10);
        } else if (btn & 0x100) {
            sel = 3;
            HuVecCopy3F(&eye, &D_80113694_option[0]);
            HuVecCopy3F(&at, &D_801136AC_option[1]);
            func_80107758_option(&eye, &at, 30);
            func_801133A0_option(0);
            func_80113440_option(0);
            HuPrcSleep(30);
            func_80109908_option(D_8011388C_option[2].x, D_8011388C_option[2].y, D_8011388C_option[2].z, &x0, &y0);
            func_80112028_option(0, x0, y0);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E12);
        }
        break;
    case 3:
        if (btn & 0x200) {
            sel = 2;
            func_80107758_option(&D_80113694_option[0], &D_80113694_option[1], 30);
            func_801133A0_option(0);
            func_80113440_option(0);
            HuPrcSleep(30);
            func_80109908_option(D_8011388C_option[1].x, D_8011388C_option[1].y, D_8011388C_option[1].z, &x0, &y0);
            func_80112028_option(0, x0, y0);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E0E);
        } else if (btn & 0x100) {
            sel = 1;
            func_80107758_option(&D_8011367C_option[0], &D_8011367C_option[1], 30);
            func_801133A0_option(0);
            func_80113440_option(0);
            HuPrcSleep(30);
            func_80109908_option(D_8011388C_option[0].x, D_8011388C_option[0].y, D_8011388C_option[0].z, &x0, &y0);
            func_80112028_option(0, x0, y0);
            func_80113384_option(0);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E10);
        }
        break;
    case 4:
        break;
    }
    return sel;
}

s32 func_8010BACC_option(s32 sel, s32 btn) {
    Vec eye;
    Vec at;
    s32 ret = -1;
    s16 model;
    s32 no;

    switch (sel) {
    case 0:
        break;
    case 1:
        func_801133A0_option(0);
        HuAudFXPlay(0x2E6);
        func_80113338_option(8, 12, 0, 8, 2);
        func_801132E4_option(4, 0);
        func_801132C8_option(4, 7);
        func_80113300_option(4);
        func_80113408_option(0, 0x4E11);
        no = func_8011345C_option(0);
        if (no == 0) {
            HuVecCopyXYZ(&eye, -195.0f, 160.0f, -595.0f);
            HuVecCopyXYZ(&at, -195.0f, 160.0f, -680.0f);
            func_80106F88_option(&eye, &at, 20);
            func_80113440_option(0);
            HuPrcSleep(20);
            func_8010C3E4_option(0xE002E, 160, 120);
        } else if (no == 1) {
            HuVecCopyXYZ(&eye, -195.0f, 160.0f, -595.0f);
            HuVecCopyXYZ(&at, -195.0f, 160.0f, -680.0f);
            func_80106F88_option(&eye, &at, 20);
            func_80113440_option(0);
            HuPrcSleep(20);
            func_8010D5B0_option(0xE002E, 160, 120);
        }
        func_80113408_option(0, 0x4E10);
        func_80106F88_option(&D_8011367C_option[0], &D_8011367C_option[1], 30);
        func_80113338_option(8, 10, 0, 8, 2);
        func_801132C8_option(4, 7);
        func_801132AC_option(4, 4);
        HuPrcSleep(30);
        model = func_80113218_option(4);
        while (HmfModelData[model].unk40 != 0.0f) {
            HuPrcVSleep();
        }
        func_80113424_option(0);
        func_80113384_option(0);
        break;
    case 2:
        func_801133A0_option(0);
        HuAudFXPlay(0x2E6);
        func_80113338_option(9, 12, 0, 8, 2);
        func_801132E4_option(5, 0);
        func_801132C8_option(5, 7);
        func_80113300_option(5);
        func_80113408_option(0, 0x4E0F);
        if (func_8011345C_option(0) == 0) {
            HuVecCopyXYZ(&eye, 195.0f, 160.0f, -595.0f);
            HuVecCopyXYZ(&at, 195.0f, 160.0f, -665.0f);
            func_80106F88_option(&eye, &at, 20);
            func_80113440_option(0);
            HuPrcSleep(20);
            func_80107F50_option(0xE002D, 160, 120);
        }
        func_80113408_option(0, 0x4E0E);
        func_80106F88_option(&D_80113694_option[0], &D_80113694_option[1], 30);
        func_80113338_option(9, 11, 0, 8, 2);
        func_801132C8_option(5, 7);
        func_801132AC_option(5, 4);
        HuPrcSleep(30);
        model = func_80113218_option(5);
        while (HmfModelData[model].unk40 != 0.0f) {
            HuPrcVSleep();
        }
        func_80113424_option(0);
        func_80113384_option(0);
        break;
    case 3:
        func_801133A0_option(0);
        func_80113408_option(0, 0x4E13);
        if (func_8011345C_option(0) == 0) {
            ret = 3;
        } else {
            switch (sel) {
            case 0:
                break;
            case 1:
                func_80113408_option(0, 0x4E10);
                break;
            case 2:
                func_80113408_option(0, 0x4E0E);
                break;
            case 3:
                func_80113408_option(0, 0x4E12);
                break;
            }
            func_80113384_option(0);
            ret = -1;
        }
        break;
    case 9:
    default:
        ret = 4;
        break;
    }
    return ret;
}

void func_8010BFA4_option(s32 sel, s32 btn) {
    s32 x = 160;
    s32 y = 120;

    switch (sel) {
    case 0:
        break;
    case 1:
        func_80109908_option(D_8011388C_option[0].x, D_8011388C_option[0].y, D_8011388C_option[0].z, &x, &y);
        break;
    case 2:
        func_80109908_option(D_8011388C_option[1].x, D_8011388C_option[1].y, D_8011388C_option[1].z, &x, &y);
        break;
    case 3:
        func_80109908_option(D_8011388C_option[2].x, D_8011388C_option[2].y, D_8011388C_option[2].z, &x, &y);
        break;
    }
    func_801096B8_option(0, x, y);
    func_801096E4_option(0);
}

#ifdef NON_MATCHING
/* Matches except that this C hoists the constant -1 (the A-press result test) out of the loop into s5. */
s32 func_8010C04C_option(void) {
    s32 pos[2];
    Vec eye;
    Vec at;
    s32 sel;
    s32 btn;
    s32 ret;

    func_801133BC_option(0, 0x4E0D);
    func_80113490_option(0);
    func_80113408_option(0, 0x4E10);
    sel = 1;
    func_80107758_option(&D_8011367C_option[0], &D_8011367C_option[1], 20);
    HuPrcSleep(20);
    func_80109908_option(D_8011388C_option[0].x, D_8011388C_option[0].y, D_8011388C_option[0].z, &pos[0], &pos[1]);
    func_80112028_option(0, pos[0], pos[1]);
    func_80113384_option(0);
    func_8010BFA4_option(1, 0);
    while (1) {
        btn = D_800D5558_main[0];
        btn |= func_801130E8_option(0);
        if (btn & 0x8000) {
            ret = func_8010BACC_option(sel, btn);
            if (ret != -1) {
                sel = ret;
                break;
            }
        } else if (btn & 0xF00) {
            sel = func_8010B68C_option(sel, btn);
        } else if (btn & 0x4000) {
            func_801133A0_option(0);
            func_80113440_option(0);
            switch (sel) {
            case 0:
            case 1:
            case 2:
                HuVecCopy3F(&eye, &D_801136AC_option[0]);
                HuVecCopy3F(&at, &D_801136AC_option[1]);
                func_80107758_option(&eye, &at, 20);
                HuPrcSleep(20);
                sel = 3;
                break;
            default:
                sel = 3;
                break;
            }
            func_80113424_option(0);
            func_80113408_option(0, 0x4E12);
            func_80113384_option(0);
        }
        func_8010BFA4_option(sel, btn);
        HuPrcVSleep();
    }
    func_801133EC_option(0);
    return sel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010C04C_option);
#endif

void func_8010C224_option(void) {
    Vec eye;
    Vec at;
    s32 sel;
    s32 mode;

    func_8001F38C_main(0, 64, 64);
    func_80112B08_option();
    func_8004A9DC_main(0x60);
    WipeCreateIn(11, 16);
    HuPrcSleep(16);
    sel = func_8010C04C_option();
    func_801133A0_option(0);
    switch (sel) {
    case 3:
        HuVecCopy3F(&eye, &D_801138B0_option);
        eye.z -= 200.0f;
        eye.y -= 40.0f;
        HuVecCopy3F(&at, &D_801138BC_option);
        at.y -= 40.0f;
        HuAudFXPlay(0x2EB);
        func_801132E4_option(1, 0);
        func_801132C8_option(1, 7);
        func_80113300_option(1);
        eye.z += 200.0f;
        func_80106F88_option(&eye, &at, 20);
        mode = sel;
        func_8010FFDC_option();
        WipeColorSet(255, 255, 255);
        WipeCreateOut(11, 20);
        func_8004A9DC_main(0x7F);
        HuPrcSleep(20);
        break;
    case 9:
    default:
        sel = 9;
    case 0:
    case 1:
    case 2:
    case 4:
        mode = sel;
        break;
    }
    func_80112E14_option();
    func_8005F524_main();
    omOvlKill();
    switch (mode) {
    case 3:
        omOvlReturnEx(1);
        break;
    default:
        omOvlReturnEx(1);
        break;
    }
    omDelPrcObj(D_80114770_option);
    while (1) {
        HuPrcVSleep();
    }
}

#ifndef NON_MATCHING
INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113D78_option);
#endif

#ifdef NON_MATCHING
/* Records board: per-page counts and one record per character, paged with left/right until B. */
void func_8010C3E4_option(s32 dataNum, s16 x, s16 y) {
    OpRecSpr w;
    s32 mes[6] = { 0x5002, 0x5003, 0x5004, 0x5005, 0x5006, 0x5007 };
    char buf[8];
    s16 i;
    s16 j;
    s32 page;
    s32 sel;
    s16 boardData;
    s16 board;
    s16 iconData;
    s16 numData;
    s16 cursorWin;
    s32 tens;
    s32 ones;
    s32 count;
    s32 k;
    f32 bx;
    f32 by;
    f32 s;
    s32 btn;

    sel = 0;
    page = 0;
    HuPrcSleep(3);
    boardData = func_8000B838_main(dataNum);
    board = InitEspriteSlot(boardData, 0, 1);
    func_8000BBD4_main(board, x, y);
    func_8000BCC8_main(board, 0x8000);
    func_8000BE5C_main(board, 0.0f, 0.0f);
    iconData = func_8000B838_main(0x1F0004);
    for (i = 0; i < 8; i++) {
        w.icon[i] = InitEspriteSlot(iconData, 0, 1);
        func_8000BBD4_main(w.icon[i], x + i * 24 - 84, y + 12);
        func_8000BCC8_main(w.icon[i], 0x8000);
        func_8000BE5C_main(w.icon[i], 1.0f, 1.0f);
        func_8000BDDC_main(w.icon[i], 1);
        func_8000BD94_main(w.icon[i], (u16)D_801138C8_option[i], 0);
        func_8000BB94_main(w.icon[i]);
    }
    numData = func_8000B838_main(0x1F0007);
    for (i = 0; i < 8; i++) {
        w.digit[i].tens = InitEspriteSlot(numData, 0, 1);
        w.digit[i].ones = InitEspriteSlot(numData, 0, 1);
        func_8000BBD4_main(w.digit[i].tens, x + i * 24 - 96 + 8, y + 26);
        func_8000BBD4_main(w.digit[i].ones, x + i * 24 - 96 + 16, y + 26);
        func_8000BCC8_main(w.digit[i].tens, 0x8000);
        func_8000BCC8_main(w.digit[i].ones, 0x8000);
        func_8000BE5C_main(w.digit[i].tens, 1.0f, 1.0f);
        func_8000BE5C_main(w.digit[i].ones, 1.0f, 1.0f);
        func_8000BDDC_main(w.digit[i].tens, 1);
        func_8000BDDC_main(w.digit[i].ones, 1);
        tens = (u8)(OP_RECVAL(2, page)[D_801138C8_option[i]] / 10);
        if (tens >= 10) {
            tens = 9;
        }
        ones = (u8)(OP_RECVAL(2, page)[D_801138C8_option[i]] % 10);
        func_8000BD94_main(w.digit[i].tens, (u16)tens, 0);
        func_8000BD94_main(w.digit[i].ones, (u16)ones, 0);
        func_8000BB94_main(w.digit[i].tens);
        func_8000BB94_main(w.digit[i].ones);
    }
    cursorWin = func_80061188_main(-1, 0, 0, 210, 14, 1);
    func_8005FBF8_main(cursorWin, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i < 11; i++) {
        s = cosdf(i * 36.0f) * 0.5f + 0.5f;
        func_8000BE5C_main(board, s, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    bx = x - 104;
    by = y - 71;
    while (TRUE) {
        w.win[0] = func_80061188_main(-1, bx + D_801138EC_option[0].x, by + D_801138EC_option[0].y, D_801138EC_option[0].w, D_801138EC_option[0].h, 0);
        func_8005BEE0_main(w.win[0], 0);
        func_8005B43C_main(w.win[0], 0x5000, -1, -1);
        w.win[1] = func_80061188_main(-1, bx + D_801138EC_option[1].x, by + D_801138EC_option[1].y, D_801138EC_option[1].w, D_801138EC_option[1].h, 0);
        func_8005BEE0_main(w.win[1], 0);
        func_8005B43C_main(w.win[1], mes[page], -1, -1);
        k = 2;
        w.win[k] = func_80061188_main(-1, bx + D_801138EC_option[k].x, by + D_801138EC_option[k].y, D_801138EC_option[k].w, D_801138EC_option[k].h, 0);
        func_8005BEE0_main(w.win[k], 0);
        count = OP_RECCOUNT(2, page);
        if (count >= 100) {
            count = 99;
        }
        sprintf(buf, D_80113A50_option, count);
        func_8005B6BC_main(w.win[k], (u32)buf, 0);
        func_8005B43C_main(w.win[k], 0x500E, -1, -1);
        k++;
        w.win[k] = func_80061188_main(-1, bx + D_801138EC_option[k].x, by + D_801138EC_option[k].y, D_801138EC_option[k].w, D_801138EC_option[k].h, 0);
        func_8005BEE0_main(w.win[k], 0);
        func_8005B43C_main(w.win[k], 0x500F, -1, -1);
        k++;
        w.win[k] = func_80061188_main(-1, bx + D_801138EC_option[k].x, by + D_801138EC_option[k].y, D_801138EC_option[k].w, D_801138EC_option[k].h, 0);
        func_8005BEE0_main(w.win[k], 0);
        func_8005B43C_main(w.win[k], 0x5010, -1, -1);
        k++;
        w.win[k] = func_80061188_main(-1, bx + D_801138EC_option[k].x, by + D_801138EC_option[k].y, D_801138EC_option[k].w, D_801138EC_option[k].h, 0);
        func_8005BEE0_main(w.win[k], 0);
        func_8005B43C_main(w.win[k], 0x5011, -1, -1);
        k++;
        for (i = 0; i < 4; i++) {
            func_8005FFA8_main(w.win[i]);
            func_8005BA90_main(cursorWin, bx + 104.0f, by + D_801138EC_option[i].y + 9.0f);
            func_8005FFA8_main(cursorWin);
            HuAudFXPlay(0x2E8);
            for (j = 1; j < 4; j++) {
                func_8005BEE0_main(cursorWin, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        for (i = 0; i < 8; i++) {
            func_8000BB54_main(w.icon[i]);
        }
        func_8005FFA8_main(cursorWin);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            func_8005BA90_main(cursorWin, x, y + 10);
            func_8005BEE0_main(cursorWin, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        for (i = 0; i < 8; i++) {
            tens = (u8)(OP_RECVAL(2, page)[D_801138C8_option[i]] / 10);
            if (tens >= 10) {
                tens = 9;
            }
            ones = (u8)(OP_RECVAL(2, page)[D_801138C8_option[i]] % 10);
            func_8000BD94_main(w.digit[i].tens, (u16)tens, 0);
            func_8000BD94_main(w.digit[i].ones, (u16)ones, 0);
            func_8000BDDC_main(w.digit[i].tens, 1);
            func_8000BDDC_main(w.digit[i].ones, 1);
            if (tens != 0) {
                func_8000BB54_main(w.digit[i].tens);
            } else {
                func_8000BB94_main(w.digit[i].tens);
            }
            func_8000BB54_main(w.digit[i].ones);
        }
        func_8005FFA8_main(cursorWin);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            func_8005BA90_main(cursorWin, x, y + 25);
            func_8005BEE0_main(cursorWin, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        func_8005FE90_main(cursorWin);
        for (i = 4; i < k; i++) {
            func_8005FFA8_main(w.win[i]);
            func_8005BA90_main(cursorWin, bx + 104.0f, by + D_801138EC_option[i].y + 9.0f);
            func_8005FFA8_main(cursorWin);
            HuAudFXPlay(0x2E8);
            for (j = 1; j < 4; j++) {
                func_8005BEE0_main(cursorWin, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        do {
            HuPrcVSleep();
            btn = D_800D5558_main[0] | func_801130E8_option(0);
        } while (!(btn & 0x4300));
        if (btn & 0x4000) {
            break;
        }
        if (btn & 0x200) {
            sel--;
            if (sel < 0) {
                sel = 5;
            }
            if (!_CheckFlag(0x31) && sel == 5) {
                sel = 4;
            }
        }
        if (btn & 0x100) {
            sel++;
            if (sel >= 6) {
                sel = 0;
            }
            if (!_CheckFlag(0x31) && sel == 5) {
                sel = 0;
            }
        }
        page = sel;
        for (i = 0; i < 8; i++) {
            func_8000BB94_main(w.icon[i]);
            func_8000BB94_main(w.digit[i].tens);
            func_8000BB94_main(w.digit[i].ones);
        }
        for (i = 0; i < k; i++) {
            func_8005FE90_main(w.win[i]);
        }
        for (i = 0; i < k; i++) {
            func_8005F364_main(w.win[i]);
        }
        HuPrcSleep(3);
    }
    HuAudFXPlay(0x2E9);
    func_8005F364_main(cursorWin);
    for (i = 0; i < 8; i++) {
        func_8000BB94_main(w.icon[i]);
        func_8000BB94_main(w.digit[i].tens);
        func_8000BB94_main(w.digit[i].ones);
    }
    for (i = 0; i < k; i++) {
        func_8005FE90_main(w.win[i]);
    }
    for (i = 0; i < k; i++) {
        func_8005F364_main(w.win[i]);
    }
    HuPrcSleep(3);
    for (i = 1; i < 11; i++) {
        s = 1.0f - sindf(i * 9.0f);
        func_8000BE5C_main(board, s, s);
        HuPrcVSleep();
    }
    for (i = 0; i < 8; i++) {
        func_8000C184_main(w.icon[i]);
        func_8000C184_main(w.digit[i].tens);
        func_8000C184_main(w.digit[i].ones);
    }
    HuSprKill(iconData);
    HuSprKill(numData);
    func_8000C184_main(board);
    HuSprKill(boardData);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010C3E4_option);
#endif

#ifndef NON_MATCHING
INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113D90_option);
#endif

#ifdef NON_MATCHING
/* The second records board (func_8010C3E4_option with the table at GwCommon.unk_1D + 0x38). */
void func_8010D5B0_option(s32 dataNum, s16 x, s16 y) {
    OpRecSpr w;
    s32 mes[6] = { 0x5008, 0x5009, 0x500A, 0x500B, 0x500C, 0x500D };
    char buf[8];
    s16 i;
    s16 j;
    s32 page;
    s32 sel;
    s16 boardData;
    s16 board;
    s16 iconData;
    s16 numData;
    s16 cursorWin;
    s32 tens;
    s32 ones;
    s32 count;
    s32 k;
    f32 bx;
    f32 by;
    f32 s;
    s32 btn;

    sel = 0;
    page = 0;
    HuPrcSleep(3);
    boardData = func_8000B838_main(dataNum);
    board = InitEspriteSlot(boardData, 0, 1);
    func_8000BBD4_main(board, x, y);
    func_8000BCC8_main(board, 0x8000);
    func_8000BE5C_main(board, 0.0f, 0.0f);
    iconData = func_8000B838_main(0x1F0004);
    for (i = 0; i < 8; i++) {
        w.icon[i] = InitEspriteSlot(iconData, 0, 1);
        func_8000BBD4_main(w.icon[i], x + i * 24 - 84, y + 12);
        func_8000BCC8_main(w.icon[i], 0x8000);
        func_8000BE5C_main(w.icon[i], 1.0f, 1.0f);
        func_8000BDDC_main(w.icon[i], 1);
        func_8000BD94_main(w.icon[i], (u16)D_8011394C_option[i], 0);
        func_8000BB94_main(w.icon[i]);
    }
    numData = func_8000B838_main(0x1F0007);
    for (i = 0; i < 8; i++) {
        w.digit[i].tens = InitEspriteSlot(numData, 0, 1);
        w.digit[i].ones = InitEspriteSlot(numData, 0, 1);
        func_8000BBD4_main(w.digit[i].tens, x + i * 24 - 96 + 8, y + 26);
        func_8000BBD4_main(w.digit[i].ones, x + i * 24 - 96 + 16, y + 26);
        func_8000BCC8_main(w.digit[i].tens, 0x8000);
        func_8000BCC8_main(w.digit[i].ones, 0x8000);
        func_8000BE5C_main(w.digit[i].tens, 1.0f, 1.0f);
        func_8000BE5C_main(w.digit[i].ones, 1.0f, 1.0f);
        func_8000BDDC_main(w.digit[i].tens, 1);
        func_8000BDDC_main(w.digit[i].ones, 1);
        tens = (u8)(OP_RECVAL(0x38, page)[D_8011394C_option[i]] / 10);
        if (tens >= 10) {
            tens = 9;
        }
        ones = (u8)(OP_RECVAL(0x38, page)[D_8011394C_option[i]] % 10);
        func_8000BD94_main(w.digit[i].tens, (u16)tens, 0);
        func_8000BD94_main(w.digit[i].ones, (u16)ones, 0);
        func_8000BB94_main(w.digit[i].tens);
        func_8000BB94_main(w.digit[i].ones);
    }
    cursorWin = func_80061188_main(-1, 0, 0, 210, 14, 1);
    func_8005FBF8_main(cursorWin, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i < 11; i++) {
        s = cosdf(i * 36.0f) * 0.5f + 0.5f;
        func_8000BE5C_main(board, s, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    bx = x - 104;
    by = y - 71;
    while (TRUE) {
        w.win[0] = func_80061188_main(-1, bx + D_80113970_option[0].x, by + D_80113970_option[0].y, D_80113970_option[0].w, D_80113970_option[0].h, 0);
        func_8005BEE0_main(w.win[0], 0);
        func_8005B43C_main(w.win[0], 0x5001, -1, -1);
        w.win[1] = func_80061188_main(-1, bx + D_80113970_option[1].x, by + D_80113970_option[1].y, D_80113970_option[1].w, D_80113970_option[1].h, 0);
        func_8005BEE0_main(w.win[1], 0);
        func_8005B43C_main(w.win[1], mes[page], -1, -1);
        k = 2;
        w.win[k] = func_80061188_main(-1, bx + D_80113970_option[k].x, by + D_80113970_option[k].y, D_80113970_option[k].w, D_80113970_option[k].h, 0);
        func_8005BEE0_main(w.win[k], 0);
        count = OP_RECCOUNT(0x38, page);
        if (count >= 100) {
            count = 99;
        }
        sprintf(buf, D_80113A50_option, count);
        func_8005B6BC_main(w.win[k], (u32)buf, 0);
        func_8005B43C_main(w.win[k], 0x500E, -1, -1);
        k++;
        w.win[k] = func_80061188_main(-1, bx + D_80113970_option[k].x, by + D_80113970_option[k].y, D_80113970_option[k].w, D_80113970_option[k].h, 0);
        func_8005BEE0_main(w.win[k], 0);
        func_8005B43C_main(w.win[k], 0x500F, -1, -1);
        k++;
        w.win[k] = func_80061188_main(-1, bx + D_80113970_option[k].x, by + D_80113970_option[k].y, D_80113970_option[k].w, D_80113970_option[k].h, 0);
        func_8005BEE0_main(w.win[k], 0);
        func_8005B43C_main(w.win[k], 0x5010, -1, -1);
        k++;
        w.win[k] = func_80061188_main(-1, bx + D_80113970_option[k].x, by + D_80113970_option[k].y, D_80113970_option[k].w, D_80113970_option[k].h, 0);
        func_8005BEE0_main(w.win[k], 0);
        func_8005B43C_main(w.win[k], 0x5011, -1, -1);
        k++;
        for (i = 0; i < 4; i++) {
            func_8005FFA8_main(w.win[i]);
            func_8005BA90_main(cursorWin, bx + 104.0f, by + D_80113970_option[i].y + 9.0f);
            HuAudFXPlay(0x2E8);
            func_8005FFA8_main(cursorWin);
            for (j = 1; j < 4; j++) {
                func_8005BEE0_main(cursorWin, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        for (i = 0; i < 8; i++) {
            func_8000BB54_main(w.icon[i]);
        }
        func_8005FFA8_main(cursorWin);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            func_8005BA90_main(cursorWin, x, y + 10);
            func_8005BEE0_main(cursorWin, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        for (i = 0; i < 8; i++) {
            tens = (u8)(OP_RECVAL(0x38, page)[D_8011394C_option[i]] / 10);
            if (tens >= 10) {
                tens = 9;
            }
            ones = (u8)(OP_RECVAL(0x38, page)[D_8011394C_option[i]] % 10);
            func_8000BD94_main(w.digit[i].tens, (u16)tens, 0);
            func_8000BD94_main(w.digit[i].ones, (u16)ones, 0);
            func_8000BDDC_main(w.digit[i].tens, 1);
            func_8000BDDC_main(w.digit[i].ones, 1);
            if (tens != 0) {
                func_8000BB54_main(w.digit[i].tens);
            } else {
                func_8000BB94_main(w.digit[i].tens);
            }
            func_8000BB54_main(w.digit[i].ones);
        }
        HuAudFXPlay(0x2E8);
        func_8005FFA8_main(cursorWin);
        for (j = 1; j < 4; j++) {
            func_8005BA90_main(cursorWin, x, y + 25);
            func_8005BEE0_main(cursorWin, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        func_8005FE90_main(cursorWin);
        for (i = 4; i < k; i++) {
            func_8005FFA8_main(w.win[i]);
            func_8005BA90_main(cursorWin, bx + 104.0f, by + D_80113970_option[i].y + 9.0f);
            func_8005FFA8_main(cursorWin);
            HuAudFXPlay(0x2E8);
            for (j = 1; j < 4; j++) {
                func_8005BEE0_main(cursorWin, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        do {
            HuPrcVSleep();
            btn = D_800D5558_main[0] | func_801130E8_option(0);
        } while (!(btn & 0x4300));
        if (btn & 0x4000) {
            break;
        }
        if (btn & 0x200) {
            sel--;
            if (sel < 0) {
                sel = 5;
            }
            if (!_CheckFlag(0x31) && sel == 5) {
                sel = 4;
            }
        }
        if (btn & 0x100) {
            sel++;
            if (sel >= 6) {
                sel = 0;
            }
            if (!_CheckFlag(0x31) && sel == 5) {
                sel = 0;
            }
        }
        page = sel;
        for (i = 0; i < 8; i++) {
            func_8000BB94_main(w.icon[i]);
            func_8000BB94_main(w.digit[i].tens);
            func_8000BB94_main(w.digit[i].ones);
        }
        for (i = 0; i < k; i++) {
            func_8005FE90_main(w.win[i]);
        }
        for (i = 0; i < k; i++) {
            func_8005F364_main(w.win[i]);
        }
        HuPrcSleep(3);
    }
    HuAudFXPlay(0x2E9);
    func_8005F364_main(cursorWin);
    for (i = 0; i < 8; i++) {
        func_8000BB94_main(w.icon[i]);
        func_8000BB94_main(w.digit[i].tens);
        func_8000BB94_main(w.digit[i].ones);
    }
    for (i = 0; i < k; i++) {
        func_8005FE90_main(w.win[i]);
    }
    for (i = 0; i < k; i++) {
        func_8005F364_main(w.win[i]);
    }
    HuPrcSleep(3);
    for (i = 1; i < 11; i++) {
        s = 1.0f - sindf(i * 9.0f);
        func_8000BE5C_main(board, s, s);
        HuPrcVSleep();
    }
    for (i = 0; i < 8; i++) {
        func_8000C184_main(w.icon[i]);
        func_8000C184_main(w.digit[i].tens);
        func_8000C184_main(w.digit[i].ones);
    }
    HuSprKill(iconData);
    HuSprKill(numData);
    func_8000C184_main(board);
    HuSprKill(boardData);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010D5B0_option);
#endif

void func_8010E77C_option(s32 x, s32 y, s32 t) {
    func_80112028_option(1, (s32)(x + sindf(t * 18) * 4.0f) - 2, y);
}

void func_8010E7FC_option(s32 x0, s32 y0, s32 x1, s32 y1, s32 len) {
    f32 t;
    s32 i;

    i = 0;
    while (TRUE) {
        HuPrcVSleep();
        t = (f32)i / len;
        func_80112028_option(1, (x1 - x0) * t + x0, (y1 - y0) * t + y0);
        if (i == len) {
            break;
        }
        i++;
    }
}


/* Sound test: fifteen pages of nine sound effects (a word per message id, a halfword per effect). */
void func_8010E8E0_option(void) {
    s16 win[16]; /* [0..8] the entries, [10] the help window */
    OpSndPage pages[15] = {
        { 0x4C01, { { 0x4C10, 0x2B5 }, { 0x4C11, 0x263 }, { 0x4C14, 0x275 }, { 0x4C12, 0x290 }, { 0x4C13, 0x27E }, { 0x4C15, 0x26C }, { 0x4C16, 0x287 }, { 0x4C17, 0x2AC }, { -1, -1 } } },
        { 0x4C02, { { 0x4C10, 0x2B6 }, { 0x4C11, 0x264 }, { 0x4C14, 0x276 }, { 0x4C12, 0x291 }, { 0x4C13, 0x27F }, { 0x4C15, 0x26D }, { 0x4C16, 0x288 }, { 0x4C17, 0x2AD }, { -1, -1 } } },
        { 0x4C03, { { 0x4C10, 0x2B7 }, { 0x4C11, 0x265 }, { 0x4C14, 0x277 }, { 0x4C12, 0x292 }, { 0x4C13, 0x280 }, { 0x4C15, 0x26E }, { 0x4C16, 0x289 }, { 0x4C17, 0x2AE }, { -1, -1 } } },
        { 0x4C04, { { 0x4C10, 0x2B8 }, { 0x4C11, 0x266 }, { 0x4C14, 0x278 }, { 0x4C12, 0x293 }, { 0x4C13, 0x281 }, { 0x4C15, 0x26F }, { 0x4C16, 0x28A }, { 0x4C17, 0x2AF }, { -1, -1 } } },
        { 0x4C05, { { 0x4C10, 0x2B9 }, { 0x4C11, 0x267 }, { 0x4C14, 0x279 }, { 0x4C12, 0x294 }, { 0x4C13, 0x282 }, { 0x4C15, 0x270 }, { 0x4C16, 0x28B }, { 0x4C17, 0x2B0 }, { -1, -1 } } },
        { 0x4C06, { { 0x4C10, 0x2BA }, { 0x4C11, 0x268 }, { 0x4C14, 0x27A }, { 0x4C12, 0x295 }, { 0x4C13, 0x283 }, { 0x4C15, 0x271 }, { 0x4C16, 0x28C }, { 0x4C17, 0x2B1 }, { -1, -1 } } },
        { 0x4C07, { { 0x4C10, 0x2BC }, { 0x4C11, 0x26A }, { 0x4C14, 0x27C }, { 0x4C12, 0x297 }, { 0x4C13, 0x285 }, { 0x4C15, 0x273 }, { 0x4C16, 0x28E }, { 0x4C17, 0x2B3 }, { -1, -1 } } },
        { 0x4C08, { { 0x4C10, 0x2BB }, { 0x4C11, 0x269 }, { 0x4C14, 0x27B }, { 0x4C12, 0x296 }, { 0x4C13, 0x284 }, { 0x4C15, 0x272 }, { 0x4C16, 0x28D }, { 0x4C17, 0x2B2 }, { -1, -1 } } },
        { 0x4C09, { { 0x4C18, 0x2A6 }, { 0x4C19, 0x2A7 }, { 0x4C1A, 0x2A8 }, { 0x4C1B, 0x2A9 }, { 0x4C1C, 0x2AA }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x4C0A, { { 0x4C1D, 0x29B }, { 0x4C1E, 0x298 }, { 0x4C1F, 0x299 }, { 0x4C20, 0x29A }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x4C0B, { { 0x4C21, 0x29C }, { 0x4C22, 0x29D }, { 0x4C23, 0x29E }, { 0x4C24, 0x29F }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x4C0C, { { 0x4C25, 0x259 }, { 0x4C26, 0x25B }, { 0x4C27, 0x256 }, { 0x4C28, 0x257 }, { 0x4C29, 0x25D }, { 0x4C2A, 0x2A3 }, { 0x4C2B, 0x2A4 }, { 0x4C2C, 0x2A2 }, { -1, -1 } } },
        { 0x4C0D, { { 0x4C2D, 0x258 }, { 0x4C2E, 0x2A5 }, { 0x4C2F, 0x2A0 }, { 0x4C30, 0x2A1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x4C0E, { { 0x4C31, 0x251 }, { 0x4C32, 0x253 }, { 0x4C33, 0x252 }, { 0x4C34, 0x254 }, { 0x4C35, 0x255 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x4C0F, { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
    };
    s32 i;
    s32 page;
    s32 cur;
    s32 t;
    s32 unlocked;
    s32 prev;
    s16 titleWin;
    s32 fx;
    s32 btn;

    func_801132E4_option(2, 0);
    func_8011331C_option(2, 13, 0);
    func_801132C8_option(2, 7);
    cur = 0;
    page = 0;
    func_80112028_option(2, 90, 116);
    func_80113384_option(2);
    func_80112028_option(1, 30, 40);
    func_80113384_option(1);
    titleWin = func_80061188_main(-1, 24, 28, 120, 20, 0);
    func_8005BEE0_main(titleWin, 0);
    func_8005C154_main(titleWin, 192, 192, 192);
    func_8005FBF8_main(titleWin, 255, 255, 255);
    func_8005C060_main(titleWin, 0, 0, 0, 0);
    func_8005C02C_main(titleWin, 0);
    func_8005B43C_main(titleWin, pages[0].title, -1, -1);
    func_8005FFA8_main(titleWin);
    unlocked = FALSE;
    if (func_800E905C_minigame(0) >= 0) {
        unlocked = TRUE;
        pages[14].item[1].mes = 0x4C37;
        pages[14].item[1].fx = 0x2C7;
    }
    if (func_800E905C_minigame(1) >= 0) {
        unlocked = TRUE;
        pages[14].item[2].mes = 0x4C38;
        pages[14].item[2].fx = 0x2C8;
    }
    if (func_800E905C_minigame(2) >= 0) {
        unlocked = TRUE;
        pages[14].item[3].mes = 0x4C39;
        pages[14].item[3].fx = 0x2C9;
    }
    if (func_800E905C_minigame(3) >= 0) {
        unlocked = TRUE;
        pages[14].item[4].mes = 0x4C3A;
        pages[14].item[4].fx = 0x2CA;
    }
    if (func_800E905C_minigame(4) >= 0) {
        unlocked = TRUE;
        pages[14].item[5].mes = 0x4C3B;
        pages[14].item[5].fx = 0x2CB;
    }
    if (func_800E905C_minigame(5) >= 0) {
        unlocked = TRUE;
        pages[14].item[6].mes = 0x4C3C;
        pages[14].item[6].fx = 0x2CC;
    }
    if (unlocked) {
        pages[14].item[0].mes = 0x4C36;
        pages[14].item[0].fx = 0x240;
    }
    for (i = 0; i < 9; i++) {
        win[i] = func_80061188_main(-1, 36, (i + 1) * 14 + 28, 120, 20, 0);
        func_8005BEE0_main(win[i], 0);
        func_8005C154_main(win[i], 192, 192, 192);
        func_8005FBF8_main(win[i], 255, 255, 255);
        func_8005C060_main(win[i], 0, 0, 0, 0);
        func_8005C02C_main(win[i], 0);
        if (pages[page].item[i].mes != -1) {
            func_8005B43C_main(win[i], pages[page].item[i].mes, -1, -1);
        } else {
            func_8005D294_main(win[i]);
        }
        func_8005FFA8_main(win[i]);
    }
    win[10] = func_80061188_main(-1, 36, 176, 120, 44, 0);
    func_8005BEE0_main(win[10], 0);
    func_8005C154_main(win[10], 192, 192, 192);
    func_8005FBF8_main(win[10], 255, 255, 255);
    func_8005C060_main(win[10], 0, 0, 0, 0);
    func_8005C02C_main(win[10], 0);
    func_8005B43C_main(win[10], 0x5D00, -1, -1);
    t = 0;
    func_8005FFA8_main(win[10]);
    while (TRUE) {
        HuPrcVSleep();
        btn = (u16)D_800D1244_main[0];
        btn |= func_80113204_option(0);
        btn = (btn & ~0xC000) | (D_800D5558_main[0] & 0xC000);
        if (btn & 0x4000) {
            func_80033910_main(HmfModelData[func_80113218_option(2)].hmf);
            break;
        }
        if (btn & 0x8000) {
            if (pages[page].item[cur].fx != -1) {
                if (func_8010FE00_option() != 0) {
                    func_8010FE10_option();
                }
                fx = HuAudFXPlay(pages[page].item[cur].fx);
                func_80033970_main(HmfModelData[func_80113218_option(2)].hmf);
                func_8010FF0C_option(fx);
            } else {
                func_80113218_option(2);
            }
        } else if (btn & 0x300) {
            if (btn & 0x200) {
                page--;
            } else {
                page++;
            }
            if (page >= 15) {
                page = 0;
            }
            if (page < 0) {
                page = 14;
            }
            if (page == 14) {
                if (!unlocked) {
                    page = (btn & 0x200) ? 13 : 0;
                }
            }
            func_8005B43C_main(titleWin, pages[page].title, -1, -1);
            for (i = 0; i < 9; i++) {
                if (pages[page].item[i].mes != -1) {
                    func_8005B43C_main(win[i], pages[page].item[i].mes, -1, -1);
                } else {
                    func_8005D294_main(win[i]);
                }
            }
            while (TRUE) {
                if (pages[page].item[cur].fx != -1) {
                    break;
                }
                cur--;
                if (cur >= 9) {
                    cur = 0;
                }
                if (cur < 0) {
                    cur = 8;
                }
            }
        } else if (btn & 0xC00) {
            prev = cur;
            do {
                if (btn & 0x800) {
                    cur--;
                } else {
                    cur++;
                }
                if (cur >= 9) {
                    cur = 0;
                }
                if (cur < 0) {
                    cur = 8;
                }
            } while (pages[page].item[cur].fx == -1);
            func_8010E7FC_option(30, (prev + 1) * 14 + 40, 30, (cur + 1) * 14 + 40, 4);
        }
        t = (t < 11) ? t + 1 : 0;
        func_8010E77C_option(30, (cur + 1) * 14 + 40, t);
    }
    func_8005FE90_main(titleWin);
    func_8005F364_main(titleWin);
    for (i = 0; i < 9; i++) {
        func_8005FE90_main(win[i]);
    }
    for (i = 0; i < 9; i++) {
        func_8005F364_main(win[i]);
    }
    func_8005FE90_main(win[10]);
    func_8005F364_main(win[10]);
    HuAudFXPlay(0x2F9);
    func_8011331C_option(2, 15, 1);
    func_801132E4_option(2, 40);
    HuPrcSleep(3);
    func_801133A0_option(1);
    func_801133A0_option(2);
}

/* Music test: twelve pages of nine songs; some appear only once unlocked. */
void func_8010F138_option(void) {
    s16 win[16]; /* [0..8] the entries, [10] the help window */
    OpSndPage pages[12] = {
        { 0x5D01, { { 0x5D0F, 0x3 }, { 0x5D10, 0x9 }, { 0x5D11, 0xB }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x5D02, { { 0x5D12, 0x4 }, { 0x5D13, 0x7 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x5D03, { { 0x5D14, 0x8 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x5D04, { { 0x5D17, 0x18 }, { 0x5D18, 0x19 }, { 0x5D19, 0x1A }, { 0x5D1A, 0x1B }, { 0x5D1B, 0x1C }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x5D05, { { 0x5D1D, 0x1E }, { 0x5D1E, 0x1F }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x5D06, { { 0x5D20, 0xD }, { 0x5D21, 0x12 }, { 0x5D22, 0x17 }, { 0x5D23, 0x24 }, { 0x5D24, 0x13 }, { 0x5D25, 0xF }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x5D07, { { 0x5D26, 0x10 }, { 0x5D27, 0x3E }, { 0x5D28, 0x14 }, { 0x5D29, 0x15 }, { 0x5D2A, 0x16 }, { 0x5D2B, 0x46 }, { 0x5D2C, 0x47 }, { -1, -1 }, { -1, -1 } } },
        { 0x5D08, { { 0x5D2D, 0x2D }, { 0x5D2E, 0x2E }, { 0x5D2F, 0x2F }, { 0x5D30, 0x30 }, { 0x5D31, 0x31 }, { 0x5D32, 0x32 }, { 0x5D33, 0x33 }, { 0x5D34, 0x34 }, { -1, -1 } } },
        { 0x5D09, { { 0x5D35, 0x35 }, { 0x5D36, 0x36 }, { 0x5D37, 0x37 }, { 0x5D38, 0x38 }, { 0x5D39, 0x44 }, { 0x5D3A, 0x43 }, { 0x5D3B, 0x42 }, { -1, -1 }, { -1, -1 } } },
        { 0x5D0A, { { 0x5D3D, 0xA }, { 0x5D3E, 0x39 }, { 0x5D3F, 0x3A }, { 0x5D40, 0x3B }, { 0x5D41, 0x26 }, { 0x5D42, 0x21 }, { 0x5D43, 0x2C }, { -1, -1 }, { -1, -1 } } },
        { 0x5D0B, { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
        { 0x5D0C, { { 0x5D48, 0x3C }, { 0x5D49, 0x3D }, { 0x5D4A, 0x48 }, { 0x5D4B, 0x45 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } } },
    };
    s32 i;
    s32 page;
    s32 cur;
    s32 t;
    s32 prev;
    s16 titleWin;
    s32 btn;

    func_801132E4_option(3, 0);
    func_8011331C_option(3, 14, 0);
    func_801132C8_option(3, 7);
    cur = 0;
    page = 0;
    func_80112028_option(2, 230, 116);
    func_80113384_option(2);
    func_80112028_option(1, 170, 40);
    func_80113384_option(1);
    titleWin = func_80061188_main(-1, 164, 28, 120, 20, 0);
    func_8005BEE0_main(titleWin, 0);
    func_8005C154_main(titleWin, 192, 192, 192);
    func_8005FBF8_main(titleWin, 255, 255, 255);
    func_8005C060_main(titleWin, 0, 0, 0, 0);
    func_8005C02C_main(titleWin, 0);
    func_8005B43C_main(titleWin, 0x5D01, -1, -1);
    func_8005FFA8_main(titleWin);
    if (func_80110018_option() != 0) {
        pages[2].item[1].mes = 0x5D15;
        pages[2].item[1].fx = 0x4C;
    }
    if (_CheckFlag(0x1D) != 0) {
        pages[2].item[2].mes = 0x5D16;
        pages[2].item[2].fx = 0x4D;
    }
    if (_CheckFlag(0x31) != 0) {
        pages[3].item[5].mes = 0x5D1C;
        pages[3].item[5].fx = 0x1D;
    }
    if (_CheckFlag(0x30) != 0) {
        pages[4].item[2].mes = 0x5D1F;
        pages[4].item[2].fx = 0x20;
    }
    if (_CheckFlag(0x1E) != 0) {
        pages[8].item[7].mes = 0x5D3C;
        pages[8].item[7].fx = 0x41;
        pages[10].item[0].mes = 0x5D44;
        pages[10].item[0].fx = 0x28;
        pages[10].item[1].mes = 0x5D45;
        pages[10].item[1].fx = 0x29;
        pages[10].item[2].mes = 0x5D46;
        pages[10].item[2].fx = 0x2A;
        pages[10].item[3].mes = 0x5D47;
        pages[10].item[3].fx = 6;
    }
    for (i = 0; i < 9; i++) {
        win[i] = func_80061188_main(-1, 180, (i + 1) * 14 + 28, 118, 20, 0);
        func_8005BEE0_main(win[i], 0);
        func_8005C154_main(win[i], 192, 192, 192);
        func_8005FBF8_main(win[i], 255, 255, 255);
        func_8005C060_main(win[i], 0, 0, 0, 0);
        func_8005C02C_main(win[i], 0);
        if (pages[page].item[i].mes != -1) {
            func_8005B43C_main(win[i], pages[page].item[i].mes, -1, -1);
        } else {
            func_8005D294_main(win[i]);
        }
        func_8005FFA8_main(win[i]);
    }
    win[10] = func_80061188_main(-1, 176, 190, 120, 44, 0);
    func_8005BEE0_main(win[10], 0);
    func_8005C154_main(win[10], 192, 192, 192);
    func_8005FBF8_main(win[10], 255, 255, 255);
    func_8005C060_main(win[10], 0, 0, 0, 0);
    func_8005C02C_main(win[10], 0);
    func_8005B43C_main(win[10], 0x5D00, -1, -1);
    t = 0;
    func_8005FFA8_main(win[10]);
    while (TRUE) {
        HuPrcVSleep();
        btn = (u16)D_800D1244_main[0];
        btn |= func_80113204_option(0);
        btn = (btn & ~0xC000) | (D_800D5558_main[0] & 0xC000);
        if (btn & 0x4000) {
            func_80033910_main(HmfModelData[func_80113218_option(3)].hmf);
            break;
        }
        if (btn & 0x8000) {
            func_8004A950_main();
            if (pages[page].item[cur].fx != -1) {
                HuAudSeqPlay(pages[page].item[cur].fx);
            }
            func_80033970_main(HmfModelData[func_80113218_option(3)].hmf);
        } else if (btn & 0x300) {
            if (btn & 0x200) {
                page--;
            } else {
                page++;
            }
            if (page >= 12) {
                page = 0;
            }
            if (page < 0) {
                page = 11;
            }
            if (page == 10) {
                if (!_CheckFlag(0x1E)) {
                    page = (btn & 0x200) ? 9 : 11;
                }
            }
            func_8005B43C_main(titleWin, pages[page].title, -1, -1);
            for (i = 0; i < 9; i++) {
                if (pages[page].item[i].mes != -1) {
                    func_8005B43C_main(win[i], pages[page].item[i].mes, -1, -1);
                } else {
                    func_8005D294_main(win[i]);
                }
            }
            while (TRUE) {
                if (pages[page].item[cur].fx != -1) {
                    break;
                }
                cur--;
                if (cur >= 9) {
                    cur = 0;
                }
                if (cur < 0) {
                    cur = 8;
                }
            }
        } else if (btn & 0xC00) {
            prev = cur;
            do {
                if (btn & 0x800) {
                    cur--;
                } else {
                    cur++;
                }
                if (cur >= 9) {
                    cur = 0;
                }
                if (cur < 0) {
                    cur = 8;
                }
            } while (pages[page].item[cur].fx == -1);
            func_8010E7FC_option(170, (prev + 1) * 14 + 40, 170, (cur + 1) * 14 + 40, 4);
        }
        t = (t < 11) ? t + 1 : 0;
        func_8010E77C_option(170, (cur + 1) * 14 + 40, t);
    }
    func_8005FE90_main(titleWin);
    func_8005F364_main(titleWin);
    for (i = 0; i < 9; i++) {
        func_8005FE90_main(win[i]);
    }
    for (i = 0; i < 9; i++) {
        func_8005F364_main(win[i]);
    }
    func_8005FE90_main(win[10]);
    func_8005F364_main(win[10]);
    HuAudFXPlay(0x2F9);
    func_8011331C_option(3, 16, 1);
    func_801132E4_option(3, 40);
    HuPrcSleep(3);
    func_801133A0_option(1);
    func_801133A0_option(2);
}

f32 func_8010F914_option(f32 x, f32 z) {
    return -(atan2df(z, x) - 90.0f);
}

void func_8010F94C_option(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        HuVecCopyXYZ(&D_80114788_option[i].unk0, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&D_80114788_option[i].unkC, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&D_80114788_option[i].pos, 0.0f, 0.0f, 0.0f);
        D_80114788_option[i].obj = NULL;
    }
}

void func_8010FA28_option(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omDelObj(D_80114788_option[i].obj);
    }
}

void func_8010FA7C_option(omObjData *obj) {
    Vec eye;
    Vec at;
    Vec up;
    Vec pos;
    Vec dir;
    s32 model;

    model = D_80114788_option[obj->work[0]].model;
    func_80105FF8_option(&eye, &at, &up);
    func_80113274_option(model, &pos.x, &pos.y, &pos.z);
    HuVecCopyXYZ(&dir, eye.x - pos.x, eye.y - pos.y, eye.z - pos.z);
    func_80113290_option(model, 0.0f, func_8010F914_option(dir.x, dir.z), 0.0f);
}

void func_8010FB40_option(u32 no, s32 model) {
    f32 x;
    f32 y;
    f32 z;
    omObjData *obj;

    if (D_80114788_option[no].obj != NULL) {
        omDelObj(D_80114788_option[no].obj);
    }
    func_80113274_option(model, &x, &y, &z);
    HuVecCopyXYZ(&D_80114788_option[no].unkC, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&D_80114788_option[no].pos, x, y, z);
    D_80114788_option[no].model = model;
    obj = omAddObj(6, 0, 0, -1, func_8010FA7C_option);
    D_80114788_option[no].obj = obj;
    obj->work[0] = no;
}







u16 func_8010FC40_option(s32 val) {
    char buf[0x100];
    OpHmfCamView *view;

    HuPrcSleep(3);
    while (TRUE) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(buf, "\n%d\n", val);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            view = *(OpHmfCamView **)&HmfModelData[gCameraList->unk4].hmf->unkB8[4];
            sprintf(buf, "POS:%4.2f,%4.2f,%4.2f", view->pos.x, view->pos.y, view->pos.z);
            print8(16, 180, buf);
            sprintf(buf, "A T:%4.2f,%4.2f,%4.2f", view->at.x, view->at.y, view->at.z);
            print8(16, 190, buf);
            sprintf(buf, "U P:%4.2f,%4.2f,%4.2f", view->up.x, view->up.y, view->up.z);
            print8(16, 200, buf);
        } else {
            sprintf(buf, D_80113A4C_option, val);
            print8(16, 220, buf);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void func_8010FDF4_option(void) {
    D_801147E0_option.obj = NULL;
}

s32 func_8010FE00_option(void) {
    return D_801147E0_option.obj != NULL;
}

void func_8010FE10_option(void) {
    if (D_801147E0_option.obj != NULL) {
        func_80033910_main(HmfModelData[func_80113218_option(2)].hmf);
        HuAudFXStop((s16)D_801147E0_option.seNo);
        omDelObj(D_801147E0_option.obj);
        D_801147E0_option.obj = NULL;
    }
}

void func_8010FE84_option(omObjData *obj) {
    if (func_800078F8_main(D_801147E0_option.seNo) == 0) {
        func_80033910_main(HmfModelData[func_80113218_option(2)].hmf);
        HuAudFXStop((s16)D_801147E0_option.seNo);
        omDelObj(obj);
        D_801147E0_option.obj = NULL;
    }
}

omObjData *func_8010FF0C_option(s32 seNo) {
    if (D_801147E0_option.obj != NULL) {
        omDelObj(D_801147E0_option.obj);
    }
    D_801147E0_option.obj = omAddObj(6, 0, 0, -1, func_8010FE84_option);
    D_801147E0_option.seNo = seNo;
    func_800078F8_main(seNo);
    return D_801147E0_option.obj;
}

void func_8010FF88_option(void) {
    s32 *p;

    if (D_801147E8_option == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }
    p = &D_801147E8_option;
    *p = (*p >= 11) ? 0 : *p + 1;
}

void func_8010FFDC_option(void) {
    D_801147E8_option = 0;
    omAddObj(6, 0, 0, -1, (void (*)(omObjData *))func_8010FF88_option);
}

s32 func_80110018_option(void) {
    s16 count[9];
    s16 i;
    s16 type;

    for (i = 0; i < 9; i++) {
        count[i] = 0;
    }
    for (i = 0; i < 0x47; i++) {
        type = D_800A6D44_main[i].minigameType;
        if (D_800A6D40_main[i].unk0 == 0x70 || D_800A6D40_main[i].unk0 == -1) {
            continue;
        }
        if (i == 0x1B || i == 8) {
            continue;
        }
        if (i == 0x10) {
            continue;
        }
        if (type < 5 && GWMgUnlockCheck(i) != 0) {
            if (++count[type] >= 3) {
                return 1;
            }
        }
    }
    return 0;
}

OP_FILE_END()

void func_80110170_option(void) {
    func_8011019C_option();
    func_80110754_option();
    func_801119CC_option();
}

#ifdef NON_MATCHING
void func_8011019C_option(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_80114EF0_option[i] = -1;
        D_801147F0_option[i].espId = -1;
        D_801147F0_option[i].x = D_801147F0_option[i].y = 0;
        D_801147F0_option[i].scaleX = D_801147F0_option[i].scaleY = 0.0f;
        D_801147F0_option[i].unk14 = 0.0f;
        D_801147F0_option[i].unk18 = 0xFF;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011019C_option);
#endif

s16 func_80110230_option(s32 no) {
    return D_80114EF0_option[no];
}

s16 func_80110244_option(s32 no) {
    return D_801147F0_option[no].espId;
}

void func_80110260_option(s32 no, s32 dataNum) {
    D_80114EF0_option[no] = func_8000B838_main(dataNum);
}

void func_80110298_option(s32 no) {
    if (D_80114EF0_option[no] != -1) {
        HuSprKill(D_80114EF0_option[no]);
    }
    D_80114EF0_option[no] = -1;
}

void func_801102F0_option(s32 no, s16 animNo) {
    D_801147F0_option[no].espId = InitEspriteSlot(D_80114EF0_option[animNo], 0, 0);
    func_8011053C_option(no, 160, 120);
}

void func_80110358_option(s32 no) {
    if (D_801147F0_option[no].espId != -1) {
        func_8000C184_main(D_801147F0_option[no].espId);
    }
    D_801147F0_option[no].espId = -1;
}

void func_801103C8_option(s32 no, s32 dataNum) {
    func_80110260_option(no, dataNum);
    func_801102F0_option(no, no);
}

void func_801103FC_option(s32 no, s32 dataNum) {
    func_801103C8_option(no, dataNum);
    func_8000BC48_main(D_801147F0_option[no].espId, 0x4000);
}

void func_80110440_option(s32 no) {
    func_80110358_option(no);
    func_80110298_option(no);
}

void func_8011046C_option(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_80110440_option(i);
    }
}

void func_801104A4_option(s32 no) {
    func_8000BB54_main(D_801147F0_option[no].espId);
}

void func_801104D4_option(s32 no) {
    func_8000BB94_main(D_801147F0_option[no].espId);
}

void func_80110504_option(s32 no) {
    func_801104A4_option(no);
}

void func_80110520_option(s32 no) {
    func_801104D4_option(no);
}

void func_8011053C_option(s32 no, s32 x, s32 y) {
    D_801147F0_option[no].x = x;
    D_801147F0_option[no].y = y;
    func_8000BBD4_main(D_801147F0_option[no].espId, x, y);
}

void func_80110594_option(s32 no, s32 *x, s32 *y) {
    *x = D_801147F0_option[no].x;
    *y = D_801147F0_option[no].y;
}

void func_801105C4_option(s32 no, f32 x, f32 y) {
    D_801147F0_option[no].scaleX = x;
    D_801147F0_option[no].scaleY = y;
    func_8000BE5C_main(D_801147F0_option[no].espId, x, y);
}

void func_80110614_option(s32 no, u16 alpha) {
    func_8000BBFC_main(D_801147F0_option[no].espId, alpha);
}

void func_8011064C_option(s32 no, u16 attr) {
    func_8000BC48_main(D_801147F0_option[no].espId, attr);
}

void func_80110680_option(s32 no, u16 attr) {
    func_8000BC88_main(D_801147F0_option[no].espId, attr);
}

void func_801106B4_option(s32 no, u16 arg1) {
    func_8000BCC8_main(D_801147F0_option[no].espId, arg1);
}

void func_801106E8_option(s32 no, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_801147F0_option[no].espId, 1);
    func_8000BD94_main(D_801147F0_option[no].espId, arg1, arg2);
}

void func_80110754_option(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        D_80114F70_option[i].model = -1;
        D_80114F70_option[i].motion = -1;
    }
}

void func_801107A0_option(s32 no, s32 arg1, s32 dataNum) {
    s16 model = func_8000B108_main(arg1, dataNum);

    D_80114F70_option[no].model = model;
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
}

void func_8011083C_option(s32 no, s32 dataNum, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(dataNum);
    D_80114F70_option[no].motion = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void func_801108C4_option(s32 no) {
    if (D_80114F70_option[no].model != -1) {
        func_8001ACDC_main(D_80114F70_option[no].model);
        D_80114F70_option[no].model = -1;
    }
    if (D_80114F70_option[no].motion != -1) {
        func_8002D4B8_main(D_80114F70_option[no].motion);
        D_80114F70_option[no].motion = -1;
    }
}

void func_80110974_option(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        func_801108C4_option(i);
    }
}

s16 func_801109AC_option(s32 no) {
    return D_80114F70_option[no].model;
}

s16 func_801109D0_option(s32 no) {
    return D_80114F70_option[no].motion;
}

void func_801109F4_option(s32 no, f32 x, f32 y, f32 z) {
    D_80114F70_option[no].rot.x = x;
    D_80114F70_option[no].rot.y = y;
    D_80114F70_option[no].rot.z = z;
    Hu3DModelRotSet(D_80114F70_option[no].model, x, y, z);
}

void func_80110A5C_option(s32 no, f32 x, f32 y, f32 z) {
    D_80114F70_option[no].pos[0] = x;
    D_80114F70_option[no].pos[1] = y;
    D_80114F70_option[no].pos[2] = z;
    Hu3DModelPosSet(D_80114F70_option[no].model, x, y, z);
}

void func_80110AD0_option(s32 no, f32 x, f32 y, f32 z) {
    D_80114F70_option[no].scale.x = x;
    D_80114F70_option[no].scale.y = y;
    D_80114F70_option[no].scale.z = z;
    Hu3DModelScaleSet(D_80114F70_option[no].model, x, y, z);
}

void func_80110B38_option(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80114F70_option[no].pos[0];
    *y = D_80114F70_option[no].pos[1];
    *z = D_80114F70_option[no].pos[2];
}

void func_80110B8C_option(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80114F70_option[no].rot.x;
    *y = D_80114F70_option[no].rot.y;
    *z = D_80114F70_option[no].rot.z;
}

void func_80110BD4_option(s32 no, f32 *x, f32 *y, f32 *z) {
    *x = D_80114F70_option[no].scale.x;
    *y = D_80114F70_option[no].scale.y;
    *z = D_80114F70_option[no].scale.z;
}

void func_80110C1C_option(s32 no) {
    func_8001C258_main(D_80114F70_option[no].model, 4, 4);
}

void func_80110C5C_option(s32 no) {
    func_8001C258_main(D_80114F70_option[no].model, 4, 0);
}

void func_80110C9C_option(s32 no, s32 flag) {
    func_8001C814_main(D_80114F70_option[no].model, -1, flag);
}

void func_80110CE0_option(s32 no, s32 motNo, s16 arg2, s16 arg3, u16 arg4) {
    func_8001C624_main(D_80114F70_option[no].model, D_80114F70_option[motNo].motion, arg2, arg3, arg4);
}

void func_80110D50_option(s32 no, s32 arg1) {
    func_8001C814_main(D_80114F70_option[no].model, arg1, 0);
}

void func_80110D94_option(s32 no, f32 speed) {
    func_8001C92C_main(D_80114F70_option[no].model, speed);
}

void func_80110DCC_option(s32 no, u32 time) {
    func_8001C6A8_main(D_80114F70_option[no].model, time);
}

void func_80110E30_option(s32 no) {
    while (HmfModelData[D_80114F70_option[no].model].unk40 !=
           D_800CCF58_main[HmfModelData[D_80114F70_option[no].model].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 func_80110ED0_option(s32 no) {
    return HmfModelData[D_80114F70_option[no].model].unk40 ==
           D_800CCF58_main[HmfModelData[D_80114F70_option[no].model].unk02].unk02;
}

void func_80110F58_option(s32 no, s32 motNo, u16 flag) {
    s16 model = func_801109AC_option(no);
    s16 motion = func_801109D0_option(motNo);

    func_8001F304_main(model, motion);
    func_8001C814_main(model, -1, flag);
}

void func_80110FC8_option(s32 dataNum) {
    D_80115A70_option = func_8000B838_main(dataNum);
    D_80115A72_option = InitEspriteSlot(D_80115A70_option, 0, 0);
    func_8000BC48_main(D_80115A72_option, 0x4000);
    func_8000BBD4_main(D_80115A72_option, 160, 120);
}

void func_8011102C_option(void) {
    func_8000C184_main(D_80115A72_option);
    HuSprKill(D_80115A70_option);
}

u32 func_80111058_option(u32 mes) {
    u8 buf[0x100];
    s32 size;
    void *copy;
    u32 ret;

    if (mes <= 0x80000000) {
        ret = mes;
    } else {
        size = func_800452A0_main(buf, (void *)mes);
        copy = HuMemAlloc(size);
        bcopy(buf, copy, size);
        ret = (u32)copy;
    }
    return ret;
}

#ifdef NON_MATCHING
void func_801110C0_option(s32 no, u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 id;
    u32 buf;

    switch (type) {
        case 1:
            buf = func_80111058_option(mes);
            id = func_80111458_option(buf, x, y, w, h, type);
            break;
        case 2:
            buf = func_80111058_option(mes);
            id = func_801115C0_option(buf, x, y, w, h, type);
            break;
        case 3:
            buf = func_80111058_option(mes);
            id = func_80111768_option(buf, x, y, type);
            break;
        case 4:
            buf = func_80111058_option(mes);
            id = func_80111834_option(buf, x, y, type);
            break;
        case 5:
            buf = func_80111058_option(mes);
            id = func_80111900_option(buf, x, y, type);
            break;
        case 0:
        default:
            buf = func_80111058_option(mes);
            id = func_8011130C_option(buf, x, y, w, h, type);
            break;
    }
    if (buf > 0x80000000) {
        D_80115A78_option[no].mes = buf;
    }
    D_80115A78_option[no].id = id;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801110C0_option);
#endif

s16 func_8011130C_option(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 8);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0xFF);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C154_main(win, 0xC0, 0xC0, 0xC0);
    func_8005FBF8_main(win, 0, 0x40, 0x40);
    func_8005C02C_main(win, 7);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80111458_option(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 4);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_8005BEE0_main(win, 0xFF);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0xC0, 0xC0, 0xC0);
    func_8005FBF8_main(win, 0xFF, 0xFF, 0xFF);
    func_8005C02C_main(win, 1);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_801115C0_option(u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type) {
    s16 win = func_8005A968_main(x, y, w, h, 0, 8);

    func_8005B63C_main(win, -1, 0x11);
    func_8005BDFC_main(win, 0);
    func_80060144_main(win);
    func_8005BE30_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005C060_main(win, 5, 0, 0xB0, 0xC0);
    func_8005C060_main(win, 7, 0xFF, 0xFF, 0xFF);
    func_8005C060_main(win, 0, 0, 0, 0);
    func_8005C060_main(win, 3, 0, 0, 0);
    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005C154_main(win, 0xC0, 0xC0, 0);
    func_8005FBF8_main(win, 0xFF, 0xFF, 0xFF);
    func_8005C02C_main(win, 6);
    func_8005D294_main(win);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80111768_option(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 1);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80111834_option(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x14);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_80060C14_main(win, 0);
    func_8005FE54_main(win, 1);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

s16 func_80111900_option(u32 mes, s16 x, s16 y, s16 type) {
    s16 win = func_80060880_main(x, y, 0x13);

    func_8005C060_main(win, 2, 0xFF, 0x40, 0x40);
    func_8005C060_main(win, 4, 0x60, 0xFF, 0x40);
    func_8005C060_main(win, 6, 0xFF, 0xFF, 0x40);
    func_8005FE54_main(win, 1);
    func_80060C14_main(win, 0);
    func_8005B43C_main(win, mes, -1, -1);
    return win;
}

void func_801119CC_option(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_80115A78_option[i].id = -1;
        D_80115A78_option[i].mes = 0;
    }
}

void func_80111A10_option(s32 no) {
    if (D_80115A78_option[no].type == 3) {
        func_80060EA8_main(D_80115A78_option[no].id, 1);
        func_800610E0_main(D_80115A78_option[no].id);
    } else {
        func_8005FE90_main(D_80115A78_option[no].id);
        func_8005F364_main(D_80115A78_option[no].id);
        D_80115A78_option[no].id = -1;
    }
    if (D_80115A78_option[no].mes != 0) {
        func_80019C00_main((void *)D_80115A78_option[no].mes);
        D_80115A78_option[no].mes = 0;
    }
}

void func_80111AF4_option(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (D_80115A78_option[i].id != -1) {
            func_80111A10_option(i);
        }
    }
}

void func_80111B58_option(s32 no, f32 x, f32 y) {
    func_8005BB18_main(D_80115A78_option[no].id, x, y);
}

void func_80111B88_option(s32 no, f32 x, f32 y) {
    func_8005BA90_main(D_80115A78_option[no].id, x, y);
}

void func_80111BF0_option(s32 no) {
    func_8005FFA8_main(D_80115A78_option[no].id);
}

void func_80111C20_option(s32 no) {
    func_8005FE90_main(D_80115A78_option[no].id);
}

void func_80111C50_option(s32 arg0, u32 arg1) {
    u32 temp_v0;

    func_8005D294_main(D_80115A78_option[arg0].id);
    if (D_80115A78_option[arg0].mes != 0) {
        func_80019C00_main((void *)D_80115A78_option[arg0].mes);
        D_80115A78_option[arg0].mes = 0;
    }

    temp_v0 = func_80111058_option(arg1);
    // pointer check
    if (temp_v0 > 0x80000000U) {
        D_80115A78_option[arg0].mes = temp_v0;
    }
    func_8005B43C_main(D_80115A78_option[arg0].id, temp_v0, -1, -1);
}

void func_80111D1C_option(s32 no, s8 arg1, s32 arg2) {
    func_800601BC_main(D_80115A78_option[no].id, arg2, arg1);
}

s32 func_80111D58_option(s32 no, s16 arg1, s32 arg2) {
    return func_8005E1D8_main(D_80115A78_option[no].id, arg1, arg2);
}

s16 func_80111D90_option(s32 no) {
    return D_80115A78_option[no].id;
}

void func_80111DAC_option(s32 no) {
    while (func_8005E0C0_main(D_80115A78_option[no].id) != 0) {
        HuPrcVSleep();
    }
}

void func_80111E00_option(s32 btn) {
    do {
        HuPrcVSleep();
    } while (!(btn & D_800D5558_main[0]));
}

void func_80111E3C_option(s32 no, s16 arg1) {
    func_8005BE30_main(D_80115A78_option[no].id, arg1);
}

extern const char D_80114620_option[];
extern const char D_80114628_option[];
extern const char D_80114640_option[];
extern const char D_80114658_option[];
extern const char D_80114670_option[];

u16 func_80111E74_option(s32 val) {
    char buf[0x100];
    OpHmfCamView *view;

    HuPrcSleep(3);
    while (TRUE) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(buf, D_80114620_option, val);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            view = *(OpHmfCamView **)&HmfModelData[gCameraList->unk4].hmf->unkB8[4];
            sprintf(buf, D_80114628_option, view->pos.x, view->pos.y, view->pos.z);
            print8(16, 180, buf);
            sprintf(buf, D_80114640_option, view->at.x, view->at.y, view->at.z);
            print8(16, 190, buf);
            sprintf(buf, D_80114658_option, view->up.x, view->up.y, view->up.z);
            print8(16, 200, buf);
        } else {
            sprintf(buf, D_80114670_option, val);
            print8(16, 220, buf);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

/* func_80111E74_option's own strings: retail keeps them apart from func_8010FC40_option's identical ones */
const char D_80114620_option[] = "\n%d\n";
const char D_80114628_option[] = "POS:%4.2f,%4.2f,%4.2f";
const char D_80114640_option[] = "A T:%4.2f,%4.2f,%4.2f";
const char D_80114658_option[] = "U P:%4.2f,%4.2f,%4.2f";
const char D_80114670_option[] = "%d"; /* its own copy in retail: GCC would merge a literal with func_80107F50_option's */

void func_80112028_option(s32 no, s32 x, s32 y) {
    func_8011053C_option(no, x, y);
}

void func_80112044_option(s32 no, u16 alpha) {
    func_80110614_option(no, alpha);
}

void func_80112060_option(void) {
    func_80110170_option();
    func_80105D10_option();
}

void func_80112084_option(void) {
    s16 model;

    func_80112FF4_option(0, 0xE0004, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(1, 0xE0007, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(3, 0xE0009, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(4, 0xE000A, 0.0f, 0.0f, 0.0f);
    func_80110C9C_option(4, 2);
    func_80112FD8_option(6, 0xE0005, 1);
    func_80112FD8_option(7, 0xE0006, 1);
    func_80112EB8_option(9, 0xA0000, -385.0f, -6.25f, -500.0f);
    func_80110AD0_option(9, 0.75f, 0.75f, 0.75f);
    func_80110C9C_option(9, 2);
    func_80112EB8_option(10, 0xA0000, 385.0f, -6.25f, -500.0f);
    func_80110AD0_option(10, 0.75f, 0.75f, 0.75f);
    func_80110C9C_option(10, 2);
    func_80017790_main(func_80113218_option(9), 0, 10, 0xA002A);
    model = func_80113218_option(10);
    func_80017790_main(model, 0, 10, 0xA002A);
    func_80017A84_main(model, 0, 10, 1, 0);
    func_80112FD8_option(11, 0xA001D, 1);
    func_80112FD8_option(12, 0xA001E, 1);
    func_80112FD8_option(13, 0xA001D, 1);
    func_80112FD8_option(14, 0xA001E, 1);
    func_80112FD8_option(15, 0xA0001, 1);
    func_80112EB8_option(20, 9, -385.0f, 0.049999997f, -500.0f);
    func_80112EB8_option(21, 9, 385.0f, 0.049999997f, -500.0f);
    func_80105DA0_option(func_80113218_option(0), 68.0f);
    func_80105D5C_option(68.0f, 45.0f, 3200.0f);
    func_80105F08_option(68.0f);
    {
        Vec eye = { 0.0f, 271.19f, 841.11f };
        Vec at = { 0.0f, 228.72f, -550.0f };
        Vec curEye;
        Vec curAt;
        Vec up;

        func_80105FF8_option(&curEye, &curAt, &up);
        func_80106508_option(&eye, &at, &up);
    }
    func_80113088_option();
}

void func_8011239C_option(void) {
    func_801130CC_option();
    func_80105E40_option();
    func_80110974_option();
    func_8011046C_option();
    func_80111AF4_option();
}

void func_801123D8_option(void) {
    s16 model;
    void *data;

    func_80112FF4_option(0, 0xE000D, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(1, 0xE000E, 0.0f, 0.0f, 0.0f);
    func_80112F48_option(2, 0xE0010, -250.0f, 0.0f, -401.15002f);
    func_801109F4_option(2, 0.0f, 10.0f, 0.0f);
    model = func_80113218_option(2);
    data = DataRead(0xE0020);
    func_80032FC0_main(HmfAnimCreate(HmfModelData[model].hmf, data, 0, "oumu0_1_DEF"), 1, 0);
    DataClose(data);
    func_8001C448_main(model);
    func_80033910_main(HmfModelData[model].hmf);
    func_80112F48_option(3, 0xE0013, 250.0f, 0.0f, -401.15002f);
    func_801109F4_option(3, 0.0f, -11.0f, 0.0f);
    model = func_80113218_option(3);
    data = DataRead(0xE0021);
    func_80032FC0_main(HmfAnimCreate(HmfModelData[model].hmf, data, 0, "tranpet_DEF"), 1, 0);
    DataClose(data);
    data = DataRead(0xE0022);
    func_80032FC0_main(HmfAnimCreate(HmfModelData[model].hmf, data, 0, "doramu2_DEF"), 1, 0);
    DataClose(data);
    data = DataRead(0xE0023);
    func_80032FC0_main(HmfAnimCreate(HmfModelData[model].hmf, data, 0, "sinbaru_DEF"), 1, 0);
    DataClose(data);
    func_8001C448_main(model);
    func_80033910_main(HmfModelData[model].hmf);
    func_80112F48_option(4, 0xE0016, 0.0f, 0.0f, 0.0f);
    func_80112F48_option(5, 0xE0019, 0.0f, 0.0f, 0.0f);
    func_80112FD8_option(17, 0xE0017, 0);
    func_80112FD8_option(18, 0xE0018, 0);
    func_80112FD8_option(19, 0xE001A, 0);
    func_80112FD8_option(20, 0xE001B, 0);
    if (!(D_800D09A8_main & 1)) {
        func_8011331C_option(4, 18, 0);
        func_801132C8_option(4, 7);
        func_801132AC_option(4, 2);
        func_801132E4_option(5, 1);
        func_801132C8_option(5, 7);
        func_801132AC_option(5, 4);
    } else {
        func_8011331C_option(5, 20, 0);
        func_801132C8_option(5, 7);
        func_801132AC_option(5, 2);
        func_801132E4_option(4, 1);
        func_801132C8_option(4, 7);
        func_801132AC_option(4, 4);
    }
    func_80112F48_option(6, 0xE001C, 90.0f, 108.2f, -300.0f);
    func_80112F48_option(7, 0xE001C, -90.0f, 108.2f, -300.0f);
    func_80112EB8_option(8, 0xA00B0, 0.0f, 20.0f, -401.15002f);
    func_80110C9C_option(8, 2);
    func_80017790_main(func_80113218_option(8), 0, 13, 0xA00B7);
    func_80112EB8_option(9, 0xE001E, 0.0f, 0.0f, 0.0f);
    func_80110C9C_option(9, 2);
    func_80112EB8_option(21, 0xE001F, 0.0f, 22.25f, -310.7f);
    func_80110C9C_option(21, 1);
    func_80112FD8_option(10, 0xA00B1, 0);
    func_80110F58_option(8, 10, 2);
    func_80112FD8_option(11, 0xA00B2, 2);
    func_80112FD8_option(12, 0xE000F, 0);
    func_80112FD8_option(13, 0xE0011, 0);
    func_80112FD8_option(14, 0xE0014, 0);
    func_80112FD8_option(15, 0xE0012, 0);
    func_80112FD8_option(16, 0xE0015, 0);
    func_801103C8_option(1, 0x30);
    func_801106B4_option(1, 5);
    func_8011053C_option(1, 0xA0, 0x71);
    func_801104D4_option(1);
    func_801103C8_option(2, 0xE0024);
    func_801106B4_option(2, 0x2718);
    func_8011053C_option(2, 0xA0, 0x71);
    func_801104D4_option(2);
    func_80105DA0_option(func_80113218_option(0), 41.539f);
    func_80105F08_option(41.539f);
    {
        Vec eye = { 0.0f, 264.9f, 364.27f };
        Vec at = { 0.0f, 184.59999f, 61.300003f };
        Vec curEye;
        Vec curAt;
        Vec up;

        func_80105FF8_option(&curEye, &curAt, &up);
        func_80106508_option(&eye, &at, &up);
    }
    func_80113088_option();
}

void func_80112A44_option(void) {
    func_801130CC_option();
    func_80105E40_option();
    func_801108C4_option(0);
    func_801108C4_option(1);
    func_801108C4_option(2);
    func_801108C4_option(3);
    func_801108C4_option(4);
    func_801108C4_option(5);
    func_801108C4_option(6);
    func_801108C4_option(7);
    func_801108C4_option(8);
    func_801108C4_option(9);
    func_801108C4_option(10);
    func_801108C4_option(11);
    func_801108C4_option(12);
    func_801108C4_option(13);
    func_801108C4_option(14);
    func_801108C4_option(15);
    func_801108C4_option(16);
    func_80110974_option();
    func_8011046C_option();
    func_80111AF4_option();
}

void func_80112B08_option(void) {
    s16 model;

    func_80112EB8_option(0, 0xE0025, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(1, 0xE0026, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(2, 0xE0027, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(3, 0xE0028, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(4, 0xE0029, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(5, 0xE002A, 0.0f, 0.0f, 0.0f);
    func_80112FF4_option(6, 0xE002B, 0.0f, 0.0f, 0.0f);
    func_80110C1C_option(6);
    func_80112FF4_option(7, 0xE002C, 0.0f, 0.0f, 0.0f);
    func_80110C1C_option(7);
    func_80112EB8_option(8, 0xA008E, -74.9735f, 56.406998f, -735.0f);
    func_80110C9C_option(8, 2);
    func_80017790_main(func_80113218_option(8), 0, 9, 0xA00A3);
    func_80112EB8_option(9, 0xA00A2, 64.9735f, 60.8265f, -720.0f);
    func_80110C9C_option(9, 2);
    model = func_80113218_option(9);
    func_80017790_main(model, 0, 8, 0xA00A3);
    func_80017A84_main(model, 0, 8, 1, 0);
    func_80112FD8_option(10, 0xA009E, 1);
    func_80110F58_option(8, 10, 2);
    func_80112FD8_option(11, 0xA009F, 1);
    func_80110F58_option(9, 11, 2);
    func_80112FD8_option(12, 0xA008F, 1);
    func_80105DA0_option(func_80113218_option(6), 55.0f);
    func_80105D5C_option(50.0f, 12.0f, 4800.0f);
    func_80105F08_option(50.0f);
    {
        Vec eye = { 0.0f, 225.0f, 0.0f };
        Vec at = { 0.0f, 225.0f, -220.0f };
        Vec curEye;
        Vec curAt;
        Vec up;

        func_80105FF8_option(&curEye, &curAt, &up);
        func_80106508_option(&eye, &at, &up);
    }
    func_80113088_option();
}

void func_80112E14_option(void) {
    func_801130CC_option();
    func_80105E40_option();
    func_801108C4_option(0);
    func_801108C4_option(1);
    func_801108C4_option(2);
    func_801108C4_option(3);
    func_801108C4_option(4);
    func_801108C4_option(5);
    func_801108C4_option(6);
    func_801108C4_option(7);
    func_801108C4_option(8);
    func_801108C4_option(9);
    func_801108C4_option(10);
    func_801108C4_option(11);
    func_801108C4_option(12);
    func_80110974_option();
    func_8011046C_option();
    func_80111AF4_option();
}

void func_80112EB8_option(s32 no, s32 arg1, f32 x, f32 y, f32 z) {
    func_801107A0_option(no, arg1, 0x2A9);
    func_80110A5C_option(no, x, y, z);
    func_80110AD0_option(no, 1.0f, 1.0f, 1.0f);
    func_80110DCC_option(no, 0);
    func_80110C9C_option(no, 1);
}

void func_80112F48_option(s32 no, s32 arg1, f32 x, f32 y, f32 z) {
    func_801107A0_option(no, arg1, 0x6A9);
    func_80110A5C_option(no, x, y, z);
    func_80110AD0_option(no, 1.0f, 1.0f, 1.0f);
    func_80110DCC_option(no, 0);
    func_80110C9C_option(no, 1);
}

void func_80112FD8_option(s32 no, s32 dataNum, s32 arg2) {
    func_8011083C_option(no, dataNum, arg2);
}

void func_80112FF4_option(s32 no, s32 arg1, f32 x, f32 y, f32 z) {
    func_801107A0_option(no, arg1, 0x2002A9);
    func_80110A5C_option(no, x, y, z);
    func_80110AD0_option(no, 1.0f, 1.0f, 1.0f);
    func_80110DCC_option(no, 0);
    func_80110C9C_option(no, 1);
}

void func_80113088_option(void) {
    func_801103C8_option(0, 0x88);
    func_801106B4_option(0, 5);
    func_8011053C_option(0, 0xA0, 0x71);
    func_801104D4_option(0);
}

void func_801130CC_option(void) {
    func_80110440_option(0);
}

#ifdef NON_MATCHING
s32 func_801130E8_option(s32 pad) {
    s32 ax;
    s32 ay;
    s32 x;
    s32 y;

    x = D_800CBB6E_main[pad];
    y = D_800D20A1_main[pad];
    if (D_801139D0_option != 0) {
        if ((x == 0) & (y == 0)) {
            D_801139D0_option = 0;
            return 0;
        }
        return 0;
    }
    if ((x != 0) | (y != 0)) {
        ax = x;
        if (x < 0) {
            ax = -ax;
        }
        ay = y;
        if (y < 0) {
            ay = -ay;
        }
        if (ay < ax) {
            if (ay * 2 < ax) {
                D_801139D0_option = (x < 0) ? 0x200 : 0x100;
            } else if (y > 0) {
                D_801139D0_option = (x < 0) ? 0xA00 : 0x900;
            } else {
                D_801139D0_option = (x < 0) ? 0x600 : 0x500;
            }
        } else if (ax * 2 < ay) {
            D_801139D0_option = (y < 0) ? 0x400 : 0x800;
        } else if (y > 0) {
            D_801139D0_option = (x < 0) ? 0xA00 : 0x900;
        } else {
            D_801139D0_option = (x < 0) ? 0x600 : 0x500;
        }
    }
    return D_801139D0_option;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801130E8_option);
#endif

s32 func_80113204_option(s32 pad) {
    return (u16)D_800D0590_main[pad];
}

s16 func_80113218_option(s32 no) {
    return func_801109AC_option(no);
}

void func_8011323C_option(s32 no) {
    func_80110C5C_option(no);
}

void func_80113258_option(s32 no) {
    func_80110C1C_option(no);
}

void func_80113274_option(s32 no, f32 *x, f32 *y, f32 *z) {
    func_80110B38_option(no, x, y, z);
}

void func_80113290_option(s32 no, f32 x, f32 y, f32 z) {
    func_801109F4_option(no, x, y, z);
}

void func_801132AC_option(s32 no, s32 flag) {
    func_80110C9C_option(no, flag);
}

void func_801132C8_option(s32 no, s32 arg1) {
    func_80110D50_option(no, arg1);
}

void func_801132E4_option(s32 no, u32 time) {
    func_80110DCC_option(no, time);
}

void func_80113300_option(s32 no) {
    func_80110E30_option(no);
}

void func_8011331C_option(s32 no, s32 motNo, s32 flag) {
    func_80110F58_option(no, motNo, flag);
}

void func_80113338_option(s32 no, s32 motNo, s16 arg2, s16 arg3, u16 arg4) {
    func_80110CE0_option(no, motNo, arg2, arg3, arg4);
}

void func_80113368_option(s32 no, s32 *x, s32 *y) {
    func_80110594_option(no, x, y);
}

void func_80113384_option(s32 no) {
    func_80110504_option(no);
}

void func_801133A0_option(s32 no) {
    func_80110520_option(no);
}

void func_801133BC_option(s32 no, u32 mes) {
    func_801110C0_option(no, mes, 0xA0, 0xC2, 0, 0, 4);
}

void func_801133EC_option(s32 no) {
    func_80111A10_option(no);
}

void func_80113408_option(s32 no, u32 mes) {
    func_80111C50_option(no, mes);
}

void func_80113424_option(s32 no) {
    func_80111BF0_option(no);
}

void func_80113440_option(s32 no) {
    func_80111C20_option(no);
}

s32 func_8011345C_option(s32 no) {
    func_80111DAC_option(no);
    return func_80111D58_option(no, 0, 0);
}

void func_80113490_option(s32 no) {
    func_80111DAC_option(no);
}

/* .data (0x801134B0); each source file's data was 16-byte aligned (OP_DATA_FILE_END) */
OvlEntrypoint D_801134B0_option[] = {
    { 0, func_80105C14_option },
    { 1, func_80105C38_option },
    { 2, func_80105C5C_option },
    { 3, func_80105C80_option },
    { 4, func_80105CA4_option },
    { 5, func_80105CC8_option },
    { 6, func_80105CEC_option },
    { -1, NULL },
};
Vec D_801134F0_option[3] = {
    { 0.0f, 271.19f, 350.0f },
    { 0.0f, 228.72f, -550.0f },
    { 0.0f, 250.0f, 350.0f },
};
Vec D_80113514_option[9] = {
    { 0.0f, 228.72f, 1275.0f },
    { 0.0f, 271.19f, 350.0f },
    { 0.0f, 228.72f, -550.0f },
    { 0.0f, 271.19f, 350.0f },
    { -535.0f, 228.72f, -550.0f },
    { 0.0f, 271.19f, 350.0f },
    { 535.0f, 228.72f, -550.0f },
    { 0.0f, 250.0f, -400.0f },
    { 0.0f, 228.72f, 1275.0f },
};
Vec D_80113580_option[6][2] = {
    { { 0.0f, 264.9f, 364.27f }, { 0.0f, 184.59999f, 61.300003f } },
    { { 0.0f, 224.46501f, -293.5f }, { 0.0f, 123.75f, -61.300003f } },
    { { 0.0f, 224.46501f, 364.27f }, { -242.5f, 123.75f, -358.5f } },
    { { 0.0f, 224.46501f, 364.27f }, { 240.0f, 123.75f, -358.5f } },
    { { 0.0f, 224.46501f, -293.5f }, { -265.7f, 105.85f, 725.0f } },
    { { 0.0f, 224.46501f, -293.5f }, { 265.7f, 105.85f, 725.0f } },
};
Vec D_80113610_option[9] = {
    { 0.0f, 184.59999f, -61.300003f },
    { 0.0f, 184.59999f, -61.300003f },
    { 0.0f, 123.75f, -640.0f },
    { -242.5f, 201.0f, -358.5f },
    { 535.0f, 228.72f, -550.0f },
    { -265.7f, 105.85f, 725.0f },
    { 265.7f, 105.85f, 725.0f },
    { 0.0f, 225.0f, 0.0f },
    { 0.0f, 200.0f, -220.0f },
};
Vec D_8011367C_option[2] = {
    { 0.0f, 225.0f, 0.0f },
    { -75.0f, 200.0f, -680.0f },
};
Vec D_80113694_option[2] = {
    { 0.0f, 225.0f, 0.0f },
    { 75.0f, 200.0f, -680.0f },
};
Vec D_801136AC_option[2] = {
    { 0.0f, 225.0f, 0.0f },
    { 0.0f, 225.0f, 475.0f },
};
Vec D_801136C4_option[4] = {
    { 0.0f, 170.0f, -7.64f },
    { -195.0f, -165.0f, -220.0f },
    { 195.0f, 165.0f, -220.0f },
    { -50.0f, 0.0f, 475.0f },
};
Vec D_801136F4_option = { 0.0f, 410.0f, -450.0f };
Vec D_80113700_option = { 0.0f, 410.0f, -550.0f };
Vec D_8011370C_option = { -535.0f, 88.70001f, -450.0f };
Vec D_80113718_option = { -535.0f, 88.70001f, -550.0f };
Vec D_80113724_option = { 535.0f, 88.70001f, -450.0f };
Vec D_80113730_option = { 535.0f, 88.70001f, -550.0f };
Vec D_8011373C_option = { 0.0f, 128.70001f, 1175.0f };
Vec D_80113748_option = { 0.0f, 128.70001f, 1275.0f };
Vec D_80113754_option = { 0.0f, 93.70001f, -450.0f };
Vec D_80113760_option = { 0.0f, 93.70001f, -525.0f };
Vec D_8011376C_option[4] = {
    { 0.0f, 430.0f, -550.0f },
    { -535.0f, 100.0f, -550.0f },
    { 535.0f, 100.0f, -550.0f },
    { 0.0f, 100.0f, 1275.0f },
};
Vec D_8011379C_option[2] = {
    { 0.0f, 271.19f, 350.0f },
    { 0.0f, 228.72f, -550.0f },
};
Vec D_801137B4_option[2] = {
    { 0.0f, 250.0f, 350.0f },
    { 0.0f, 228.72f, 1275.0f },
};
Vec D_801137CC_option[2] = {
    { 0.0f, 228.72f, 350.0f },
    { -535.0f, 228.72f, -550.0f },
};
Vec D_801137E4_option[2] = {
    { 0.0f, 228.72f, 350.0f },
    { 535.0f, 228.72f, -550.0f },
};
Vec D_801137FC_option = { -265.7f, 105.85f, 625.0f };
Vec D_80113808_option = { -265.7f, 105.85f, 725.0f };
Vec D_80113814_option = { 265.7f, 105.85f, 625.0f };
Vec D_80113820_option = { 265.7f, 105.85f, 725.0f };
Vec D_8011382C_option[2] = {
    { -228.75f, 123.75f, 41.500015f },
    { -323.75f, 98.75f, -358.5f },
};
Vec D_80113844_option[2] = {
    { 0.0f, 224.46501f, 364.27f },
    { -242.5f, 123.75f, -358.5f },
};
Vec D_8011385C_option[2] = {
    { 228.75f, 123.75f, 41.500015f },
    { 323.75f, 98.75f, -358.5f },
};
Vec D_80113874_option[2] = {
    { 0.0f, 224.46501f, 364.27f },
    { 242.5f, 123.75f, -358.5f },
};
Vec D_8011388C_option[3] = {
    { -195.0f, 165.0f, -695.0f },
    { 195.0f, 165.0f, -695.0f },
    { -50.0f, 225.0f, 475.0f },
};
Vec D_801138B0_option = { 0.0f, 225.0f, 275.0f };
Vec D_801138BC_option = { 0.0f, 225.0f, 575.0f };
s32 D_801138C8_option[9] = { 0, 1, 2, 3, 4, 5, 7, 6, 8 };
OpRect D_801138EC_option[6] = {
    { 0.0f, 0.0f, 213.0f, 20.0f },
    { 0.0f, 19.0f, 213.0f, 20.0f },
    { 0.0f, 34.0f, 213.0f, 20.0f },
    { 0.0f, 53.0f, 213.0f, 20.0f },
    { 0.0f, 105.0f, 213.0f, 20.0f },
    { 0.0f, 120.0f, 213.0f, 20.0f },
};
s32 D_8011394C_option[9] = { 0, 1, 2, 3, 4, 5, 7, 6, 8 };
OpRect D_80113970_option[6] = {
    { 0.0f, 0.0f, 213.0f, 20.0f },
    { 0.0f, 19.0f, 213.0f, 20.0f },
    { 0.0f, 34.0f, 213.0f, 20.0f },
    { 0.0f, 53.0f, 213.0f, 20.0f },
    { 0.0f, 105.0f, 213.0f, 20.0f },
    { 0.0f, 120.0f, 213.0f, 20.0f },
};
s32 D_801139D0_option = 0;
OP_DATA_FILE_END()
Vec D_801139E0_option = { 0.0f, 0.0f, 100.0f };
Vec D_801139EC_option = { 0.0f, 0.0f, 0.0f };
Vec D_801139F8_option = { 0.0f, 1.0f, 0.0f };
s32 D_80113A04_option = 0; /* unreferenced */
OpRecIds D_80113A08_option = { { 0, 1, 2, 4, 3, 5, 6, 7, 9, 8 } };
OpRecIds D_80113A14_option = { { 0x0D, 0x10, 0x23, 0x34, 0x2C, 0x47, 0x47, 0x47, 0, 0xFF } };
