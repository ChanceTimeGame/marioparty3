#include "mgenter.h"

extern f32 D_800CE17C_main[];
extern f32 D_800D5210_main;
extern s16 D_80109B40_mgenter;  /* instruction card sprite file */
extern s16 D_80109B42_mgenter;  /* its esprite slot */
extern s16 D_80109B44_mgenter;  /* next image buffer */
extern u16 *D_80109B48_mgenter[3]; /* image buffers (0x6000 bytes each) */
extern void *D_80109B54_mgenter; /* the sprite's own image */
extern Vec D_80109B88_mgenter;  /* fixed camera target */
extern Vec D_80109BA4_mgenter;  /* fixed camera eye */

typedef struct MgEntEspr {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ s16 unk04; /* sprite group */
    /* 0x06 */ char unk06[0x1E];
} MgEntEspr; /* size 0x24 */
extern MgEntEspr *D_800CD1DC_main;

/* .data (0x46CBA0) */
f32 D_80109AB0_mgenter = 58.0f;
s8 D_80109AB4_mgenter = 0; /* 1: the fixed camera D_80109BA4_mgenter/D_80109B88_mgenter */

// masked 34: retail addresses Center through a base register and shares the D-pad move tails (one more $f register here)
/* debug camera on the second controller: C up/down zoom, L/R... the field of view, stick turns, the
   D-pad moves the target; Z with it goes faster; START prints the camera */
#ifdef NON_MATCHING
void func_80108A60_mgenter(void) {
    f32 rx;
    f32 ry;
    f32 spd;
    f32 dx;
    f32 dz;
    f32 inv;

    if (D_800D5558_main[1] & 0x10) {
        osSyncPrintf("\t{\n\t{%4.1f,%4.1f,%4.1f},\n", CRot.x, CRot.y, CRot.z);
        osSyncPrintf("\t{%4.1f,%4.1f,%4.1f},\n", Center.x, Center.y, Center.z);
        osSyncPrintf("\t%4.1f,%4.1f\n\t},\n", CZoom, D_80109AB0_mgenter);
    }
    if (D_800CDA7C_main[1] & 8) {
        if (D_800CDA7C_main[1] & 0x2000) {
            CZoom += 30.0f;
        } else {
            CZoom += 10.0f;
        }
    }
    if ((D_800CDA7C_main[1] & 4) && CZoom - 10.0f != 0.0f) {
        if (D_800CDA7C_main[1] & 0x2000) {
            CZoom -= 30.0f;
        } else {
            CZoom -= 10.0f;
        }
    }
    if (D_800CDA7C_main[1] & 2) {
        D_80109AB0_mgenter += 1.0f;
    }
    if (D_800CDA7C_main[1] & 1) {
        D_80109AB0_mgenter -= 1.0f;
    }
    Hu3DCamSetPerspective(0, D_80109AB0_mgenter, D_80109B64_mgenter, D_80109B78_mgenter);
    rx = CRot.x;
    ry = CRot.y;
    if (D_800CDA7C_main[1] & 0x2000) {
        spd = 5.0f;
    } else {
        spd = 2.0f;
    }
    ry += (-D_800CBB6E_main[1] / 30) * spd;
    if (ry >= 360.0f) {
        ry -= 360.0f;
    } else if (ry < 0.0f) {
        ry += 360.0f;
    }
    CRot.y = ry;
    rx += (s8)(D_800D20A1_main[1] / 30) * spd;
    if (rx >= 360.0f) {
        rx -= 360.0f;
    } else if (rx < 0.0f) {
        rx += 360.0f;
    }
    CRot.x = rx;
    if (D_800CDA7C_main[1] & 0x2000) {
        spd = 10.0f;
    } else {
        spd = 2.0f;
    }
    if (D_800CDA7C_main[1] & 0x800) {
        dx = sindf(ry) * sindf(rx);
        spd = -spd;
        Center.x += dx * spd;
        Center.y += cosdf(rx) * spd;
        Center.z += cosdf(ry) * sindf(rx) * spd;
    } else if (D_800CDA7C_main[1] & 0x400) {
        dx = sindf(ry) * sindf(rx);
        Center.x += dx * spd;
        Center.y += cosdf(rx) * spd;
        Center.z += cosdf(ry) * sindf(rx) * spd;
    } else if (D_800CDA7C_main[1] & 0x200) {
        dz = gCameraList->pos.z - Center.z;
        dx = -(gCameraList->pos.x - Center.x);
        inv = 1.0f / HuSqrtf(dz * dz + dx * dx);
        Center.x += dz * inv * spd;
        Center.y += 0.0f;
        Center.z += dx * inv * spd;
    } else if (D_800CDA7C_main[1] & 0x100) {
        dz = -(gCameraList->pos.z - Center.z);
        dx = gCameraList->pos.x - Center.x;
        inv = 1.0f / HuSqrtf(dz * dz + dx * dx);
        Center.x += dz * inv * spd;
        Center.y += 0.0f;
        Center.z += dx * inv * spd;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/46BB50", func_80108A60_mgenter);
#endif

/* The camera process (msetup's func_80106320_msetup): the eye orbits Center at CZoom with rotation CRot,
   the up vector turned by CRot.z about the line of sight; or, while D_80109AB4_mgenter is set, the fixed
   eye and target with up +y. */
void func_80109020_mgenter(void) {
    Vec pos;
    Vec at;
    Vec up;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 ux;
    f32 uy;
    f32 uz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;

    while (1) {
        if (D_80109AB4_mgenter == 0) {
            rx = CRot.x;
            ry = CRot.y;
            rz = CRot.z;
            pos.x = sindf(ry) * cosdf(rx) * CZoom + Center.x;
            pos.y = -sindf(rx) * CZoom + Center.y;
            pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
            at.x = Center.x;
            at.y = Center.y;
            at.z = Center.z;
            ux = sindf(ry) * sindf(rx);
            uy = cosdf(rx);
            uz = cosdf(ry) * sindf(rx);
            dx = at.x - pos.x;
            dy = at.y - pos.y;
            dz = at.z - pos.z;
            len = HuSqrtf(dx * dx + dy * dy + dz * dz);
            dx /= len;
            dy /= len;
            dz /= len;
            up.x = ux * (dx * dx + (1.0f - dx * dx) * cosdf(rz))
                 + uy * (dx * dy * (1.0f - cosdf(rz)) - dz * sindf(rz))
                 + uz * (dx * dz * (1.0f - cosdf(rz)) + dy * sindf(rz));
            up.y = ux * (dx * dy * (1.0f - cosdf(rz)) + dz * sindf(rz))
                 + uy * (dy * dy + (1.0f - dy * dy) * cosdf(rz))
                 + uz * (dy * dz * (1.0f - cosdf(rz)) - dx * sindf(rz));
            up.z = ux * (dx * dz * (1.0f - cosdf(rz)) - dy * sindf(rz))
                 + uy * (dy * dz * (1.0f - cosdf(rz)) + dx * sindf(rz))
                 + uz * (dz * dz + (1.0f - dz * dz) * cosdf(rz));
        } else {
            pos = D_80109BA4_mgenter;
            at = D_80109B88_mgenter;
            up.x = 0.0f;
            up.y = 1.0f;
            up.z = 0.0f;
        }
        D_800CE17C_main[0] = pos.x;
        D_800CE17C_main[1] = pos.z;
        D_800CE17C_main[-1] = CRot.y;
        D_800CE17C_main[2] = gCameraList->fov[0];
        D_800CE17C_main[3] = D_800D5210_main;
        D_800CE17C_main[4] = D_800CB890_main.unk00;
        Hu3DCamSetPositionOrientation(0, &pos, &at, &up);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

/* the instruction card: one sprite whose image is swapped for a decoded HVQ picture */
s32 func_801095F4_mgenter(void) {
    s16 file;
    s16 slot;
    s16 i;

    D_80109B40_mgenter = file = func_8000B838_main(0x12000E);
    D_80109B42_mgenter = slot = InitEspriteSlot(file, 0, 1);
    for (i = 0; i < 3; i++) {
        D_80109B48_mgenter[i] = HuMemAllocTag(0x6000, 0x7918);
    }
    D_80109B54_mgenter = HuSprGet(D_800CD1DC_main[slot].unk04, 0)->unk_84->unk00->unk00;
    D_80109B44_mgenter = 0;
    func_8000BB94_main(slot);
    return slot;
}

/* decodes picture mes (and its MPS data, mes + 1) of directory 0x17 into the next buffer and shows it */
void func_801096EC_mgenter(s16 mes) {
    void *data;
    void *mps;
    u8 *work;

    data = DataRead(mes | 0x170000);
    mps = DataRead((mes + 1) | 0x170000);
    hvqMpsInit1(0xFF);
    hvqMpsDecodeStart1(mps);
    work = HuMemMemoryAllocPerm(0xC00);
    hvqMpsDecode1(data, D_80109B48_mgenter[D_80109B44_mgenter], 0x80, work);
    HuMemMemoryFreePerm(work);
    DataClose(data);
    DataClose(mps);
    HuSprGet(D_800CD1DC_main[D_80109B42_mgenter].unk04, 0)->unk_84->unk00->unk00 = D_80109B48_mgenter[D_80109B44_mgenter];
    if (++D_80109B44_mgenter >= 3) {
        D_80109B44_mgenter = 0;
    }
    func_8000BB54_main(D_80109B42_mgenter);
}

void func_80109820_mgenter(void) {
    s16 i;

    HuSprGet(D_800CD1DC_main[D_80109B42_mgenter].unk04, 0)->unk_84->unk00->unk00 = D_80109B54_mgenter;
    func_8000C184_main(D_80109B42_mgenter);
    HuSprKill(D_80109B40_mgenter);
    for (i = 0; i < 3; i++) {
        HuMemFree(D_80109B48_mgenter[i]);
    }
}

/* the D-pad as a stick: writes the controlling pad's stick (D_800CBB6E_main / D_800D20A1_main) at 50 */
void func_801098D8_mgenter(void) {
    f32 y;
    f32 x;
    f32 len;

    y = 0.0f;
    x = 0.0f;
    if (D_800CDA7C_main[D_80109B74_mgenter] & 0x200) {
        x = -1.0f;
    }
    if (D_800CDA7C_main[D_80109B74_mgenter] & 0x100) {
        x += 1.0f;
    }
    if (D_800CDA7C_main[D_80109B74_mgenter] & 0x800) {
        y += 1.0f;
    }
    if (D_800CDA7C_main[D_80109B74_mgenter] & 0x400) {
        y += -1.0f;
    }
    if (x == 0.0f && y == 0.0f) {
        return;
    }
    len = HuSqrtf(x * x + y * y);
    D_800CBB6E_main[D_80109B74_mgenter] = x / len * 50.0f;
    D_800D20A1_main[D_80109B74_mgenter] = y / len * 50.0f;
}
