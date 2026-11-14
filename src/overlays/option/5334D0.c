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

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80107B80_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80107D64_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113A20_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80107F50_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80108A68_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80108AAC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80108AF0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80108B34_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113A4C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113A50_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113A54_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", jtbl_80113A58_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113A80_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113A8C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113A98_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113AA4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113AB0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113ABC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113AC8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113AD4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113AE0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113AEC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113AF8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113B04_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113B10_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/5334D0", D_80113B1C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/5334D0", func_80108B58_option);

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
