#include "common.h"
#include "option.h"

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80109504_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801096B8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801096E4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80109730_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80109908_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010998C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80109A0C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80109B7C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80109CB0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113B90_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113B9C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113BA8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113BB4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113BC0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113BCC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80109D04_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80109EF4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010A3E8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010A498_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010A66C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010A8DC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010A940_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113CB8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113CD0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010AF54_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010B654_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010B68C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010BACC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010BFA4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010C04C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010C224_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010C3E4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010D5B0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010E77C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010E7FC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010E8E0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010F138_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010F914_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010F94C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FA28_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FA7C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FB40_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113D78_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113D90_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113DA8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_8011421C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FC40_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FDF4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FE00_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FE10_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FE84_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FF0C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FF88_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8010FFDC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110018_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110170_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011019C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110230_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110244_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110260_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110298_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801102F0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110358_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801103C8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801103FC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110440_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011046C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801104A4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801104D4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110504_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110520_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011053C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110594_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801105C4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110614_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011064C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110680_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801106B4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801106E8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110754_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801107A0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011083C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801108C4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110974_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801109AC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801109D0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801109F4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110A5C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110AD0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110B38_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110B8C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110BD4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110C1C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110C5C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110C9C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110CE0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110D50_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110D94_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110DCC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110E30_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110ED0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110F58_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80110FC8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011102C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111058_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801110C0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011130C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111458_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801115C0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111768_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111834_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111900_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801119CC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111A10_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111AF4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111B58_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111B88_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111BF0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111C20_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111C50_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111D1C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111D58_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111D90_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111DAC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111E00_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111E3C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80111E74_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112028_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112044_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112060_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112084_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011239C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80114674_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80114680_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801123D8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112A44_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112B08_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112E14_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112EB8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112F48_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112FD8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80112FF4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113088_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801130CC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801130E8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113204_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113218_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011323C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113258_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113274_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113290_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801132AC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801132C8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801132E4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113300_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011331C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113338_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113368_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113384_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801133A0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801133BC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_801133EC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113408_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113424_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113440_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_8011345C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80113490_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_801146BC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_801146C8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_801146D4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_801146E0_option);
