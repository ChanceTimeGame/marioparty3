#include "common.h"
#include "overlays/minigame.h"

// dinghies A: Dizzy Dinghies (players steer dinghies on a rippling sea)

typedef func_800E1BA8_minigame_ObjData MgWork;

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_800142A0_main(s32);
void Hu3DAnimInit(s32);
void func_8001E65C_main(s16 mdl, f32 u, f32 v, s32 w, s32 h);

extern f32 D_800CB890_main;
extern u8 D_800CE20A_main;
extern u8 D_800D2008_main;
extern f32 D_800D5210_main;
extern u8 D_800D6A90_main;

// minigame
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
u16 func_800E6E9C_minigame(void);

extern f32 D_800EB73C_minigame;
extern f32 D_800EB77C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[]; /* minigame mgcol.h HitList */

// LOCAL

void func_80105CAC_dizzy_dinghies(omObjData* obj);
void func_80107098_dizzy_dinghies(omObjData* obj);
void func_80107DE8_dizzy_dinghies(omObjData* obj);
void func_80109420_dizzy_dinghies(omObjData* obj);

extern Vec D_80109740_dizzy_dinghies[]; /* start positions, one per board (D_801097EC) */
extern f32 D_801097B0_dizzy_dinghies;
extern f32 D_801097B4_dizzy_dinghies; /* wave 1 phase */
extern f32 D_801097B8_dizzy_dinghies; /* wave 1 period */
extern f32 D_801097BC_dizzy_dinghies; /* wave 1 wavelength */
extern f32 D_801097C0_dizzy_dinghies; /* wave 1 amplitude */
extern f32 D_801097C4_dizzy_dinghies; /* wave 2 phase */
extern f32 D_801097C8_dizzy_dinghies;
extern f32 D_801097CC_dizzy_dinghies;
extern f32 D_801097D0_dizzy_dinghies;
extern f32 D_801097D8_dizzy_dinghies;
extern f32 D_801097DC_dizzy_dinghies;
extern s32 D_801097D4_dizzy_dinghies;
extern f32 D_801097E0_dizzy_dinghies;
extern s32 D_801097EC_dizzy_dinghies;
/* Course objects per board (D_801097EC): position, rotation, kind (0..2; -1 ends the list) */
extern Vec D_801097F0_dizzy_dinghies[];
extern Vec D_801098BC_dizzy_dinghies[];
extern s8 D_80109988_dizzy_dinghies[];
extern Vec D_8010999C_dizzy_dinghies[];
extern Vec D_80109A80_dizzy_dinghies[];
extern s8 D_80109B64_dizzy_dinghies[];
extern Vec D_80109B78_dizzy_dinghies[];
extern Vec D_80109C50_dizzy_dinghies[];
extern s8 D_80109D28_dizzy_dinghies[];
extern D_80111B50_vine_with_me_Struct D_80109D3C_dizzy_dinghies;
extern f32 D_80109D70_dizzy_dinghies;
extern f32 D_80109D74_dizzy_dinghies;
extern f32 D_80109D78_dizzy_dinghies;
extern f32 D_80109D7C_dizzy_dinghies;
extern f32 D_80109D80_dizzy_dinghies;

void func_801059A0_dizzy_dinghies(void) {
    u8 cam;

    Hu3DAnimInit(50);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800E1804_minigame();
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 20.0f, 80.0f, 8000.0f);
    D_800D5210_main = 20000.0f;
    D_800CB890_main = 12000.0f;
    func_8001F38C_main(0, 0, 0x40);
    HmfLightMaxSet(2);
    HmfLightDirSet(1, -98.0f, 14.0f, 66.0f);
    HmfLightDirSet(2, -84.0f, 83.0f, 12.0f);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightColorSet(2, 0xE6, 0xE6, 0xE6);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 40, 0, -1, func_80107098_dizzy_dinghies);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 13, 0, -1, func_80107DE8_dizzy_dinghies);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    omSetStatBit(omAddObj(4, 0, 0, -1, func_80105CAC_dizzy_dinghies), 0xA0);
    omSetStatBit(omAddObj(100, 0, 0, -1, func_80109420_dizzy_dinghies), 0xA0);
    D_800EB73C_minigame = 10.0f;
    WipeCreateIn(0xFF, 16);
    func_800E5EA0_minigame(&D_80109D3C_dizzy_dinghies);
    D_800EB930_minigame = 0x32;
    D_800EB932_minigame = 0x48;
    D_801097EC_dizzy_dinghies = D_800CE20A_main;
}

/* Camera: look at a point ahead of the player's dinghy. */
void func_80105CAC_dizzy_dinghies(omObjData* obj) {
    MgWork* work = D_800EC598_minigame[0]->data;
    f32 angle = work->unk3C;
    f32 dist = D_801097B0_dizzy_dinghies * 100.0f + D_801097E0_dizzy_dinghies + 2.0f * work->unk40;

    Center.x = D_800EC598_minigame[0]->trans.x + sindf(angle) * dist;
    Center.y = 0.0f;
    Center.z = D_800EC598_minigame[0]->trans.z + cosdf(angle) * dist;
}

void func_80105D64_dizzy_dinghies(omObjData* obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

/* Sea height at (x, z): the mean of two circular waves. */
f32 func_80105D90_dizzy_dinghies(f32 x, f32 z) {
    f32 h;
    f32 x2;
    f32 z2;

    h = sindf((D_801097B4_dizzy_dinghies / D_801097B8_dizzy_dinghies - HuSqrtf(x * x + z * z) / D_801097BC_dizzy_dinghies) * 6.283185307179586) * D_801097C0_dizzy_dinghies;
    x2 = x + 8000.0f;
    z2 = z + 5000.0f;
    return (h + sindf((D_801097C4_dizzy_dinghies / D_801097C8_dizzy_dinghies - HuSqrtf(x2 * x2 + z2 * z2) / D_801097CC_dizzy_dinghies) * 6.283185307179586) * D_801097D0_dizzy_dinghies) / 2.0f;
}

/* Sea model: move its vertices to the wave height and shade them (crests white, troughs blue). */
void func_80105EB4_dizzy_dinghies(omObjData* obj) {
    HmfData* hmf;
    Vtx* dst;
    Vtx* src;
    f32 px;
    f32 pz;
    f32 x;
    f32 z;
    f32 h;
    s32 i;

    px = D_800EC598_minigame[0]->trans.x;
    pz = D_800EC598_minigame[0]->trans.z;
    hmf = HmfModelData[obj->model[1]].hmf;
    dst = hmf->unk44[D_800D2008_main];
    src = hmf->unk40;
    for (i = 0; i < *(s16*)&hmf->unk16[2]; i++, dst++, src++) {
        x = src->v.ob[0] + px;
        z = src->v.ob[2] + pz;
        h = sindf((D_801097B4_dizzy_dinghies / D_801097B8_dizzy_dinghies - HuSqrtf(x * x + z * z) / D_801097BC_dizzy_dinghies) * 6.283185307179586) * D_801097C0_dizzy_dinghies;
        x = x + 8000.0f;
        z = z + 5000.0f;
        h = (h + sindf((D_801097C4_dizzy_dinghies / D_801097C8_dizzy_dinghies - HuSqrtf(x * x + z * z) / D_801097CC_dizzy_dinghies) * 6.283185307179586) * D_801097D0_dizzy_dinghies) / 2.0f;
        dst->v.ob[1] = h;
        if (h > 0.0) {
            h = 256.0f - h;
            dst->v.cn[0] = 0xAA;
            dst->v.cn[1] = 0xAA;
            dst->v.cn[2] = h;
        } else {
            h = 175.0f - h;
            if (h > 255.0f) {
                h = 255.0f;
            }
            dst->v.cn[0] = h;
            dst->v.cn[1] = h;
            dst->v.cn[2] = 0xFF;
        }
    }
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_801097B4_dizzy_dinghies += 0.11f;
        D_801097C4_dizzy_dinghies += 0.09f;
        Hu3DModelPosSet(obj->model[1], px, 0.0f, pz);
    }
    func_8001E65C_main(obj->model[1], D_801097D8_dizzy_dinghies, D_801097DC_dizzy_dinghies, 32, 32);
    if (D_800CDA7C_main[1] & 8) {
        D_801097B8_dizzy_dinghies += 0.001f;
    }
    if (D_800CDA7C_main[1] & 4) {
        D_801097B8_dizzy_dinghies -= 0.001f;
    }
    if (D_801097B8_dizzy_dinghies < 0.01f) {
        D_801097B8_dizzy_dinghies = 0.01f;
    }
    if (D_800CDA7C_main[1] & 1) {
        D_801097BC_dizzy_dinghies += 0.1f;
    }
    if (D_800CDA7C_main[1] & 2) {
        D_801097BC_dizzy_dinghies -= 0.1f;
    }
    if (D_800CDA7C_main[1] & 0x10) {
        D_801097C0_dizzy_dinghies -= 0.1f;
    }
    if (D_800CDA7C_main[1] & 0x20) {
        D_801097C0_dizzy_dinghies += 0.1f;
    }
    D_801097C8_dizzy_dinghies = D_801097B8_dizzy_dinghies - 0.3f;
    D_801097CC_dizzy_dinghies = D_801097BC_dizzy_dinghies - 5.0f;
    D_801097D0_dizzy_dinghies = D_801097C0_dizzy_dinghies - 20.0f;
}

/* Camera: close in on the player when D_801097D4 is set. */
void func_80106494_dizzy_dinghies(omObjData* obj) {
    omObjData* player;

    if (D_801097D4_dizzy_dinghies == 1) {
        player = D_800EC598_minigame[0];
        Center.x -= (Center.x - player->trans.x) * 0.25f;
        Center.z -= (Center.z - player->trans.z) * 0.25f;
        Center.y -= (Center.y - player->trans.y) * 0.25f;
        CZoom *= 0.95f;
        if (CZoom < 2000.0f) {
            CZoom = 2000.0f;
        }
    }
}

#ifdef NON_MATCHING
/* Differs only by one nop after the sindf call (scheduling). */
void func_8010655C_dizzy_dinghies(omObjData* obj) {
    f32 x;
    f32 y;
    f32 z;
    s32 t;

    x = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x + 400.0f + D_80109D70_dizzy_dinghies;
    y = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y + 500.0f;
    z = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z;
    Hu3DModelPosSet(obj->model[3], x, y, z);
    x += cosdf(D_80109D74_dizzy_dinghies + 90.0f) * 77.65f;
    Hu3DModelPosSet(obj->model[2], x, y + sindf(D_80109D74_dizzy_dinghies + 90.0f) * 77.65f, z + 140.0f);
    Hu3DModelRotSet(obj->model[3], 0.0f, 0.0f, D_80109D74_dizzy_dinghies);
    Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, sindf(D_80109D78_dizzy_dinghies) * D_80109D7C_dizzy_dinghies);
    D_80109D70_dizzy_dinghies *= 0.9f;
    if (D_80109D70_dizzy_dinghies > -300.0f) {
        D_80109D78_dizzy_dinghies += 10.0f;
        D_80109D7C_dizzy_dinghies *= 0.98f;
        D_80109D74_dizzy_dinghies *= 0.8f;
    }
    t = func_800E6E9C_minigame();
    if (func_800E6E8C_minigame() == 0) {
        if (t == 60) {
            func_8001C814_main(obj->model[2], 1, 0);
        }
    } else if (t == 15.0 || t == 45.0) {
        HuAudFXPlay(0x426);
    }
}

#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_8010655C_dizzy_dinghies);
#endif

void func_80106818_dizzy_dinghies(omObjData* obj) {
    f32 x;
    f32 y;
    f32 z;

    if (D_80109D80_dizzy_dinghies < 2000.0f) {
        x = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x + 400.0f;
        y = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y + 500.0f + D_80109D80_dizzy_dinghies;
        z = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z;
        D_80109D80_dizzy_dinghies *= 1.15f;
        Hu3DModelPosSet(obj->model[3], x, y, z);
        Hu3DModelPosSet(obj->model[2], x, y + 77.65f, z + 140.0f);
        return;
    }
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
}

/* Course objects: show at most five of each kind within 2500 of the camera target (models 9.., 19.., 29..). */
void func_80106970_dizzy_dinghies(omObjData* obj) {
    s32 kind;
    f32 px;
    f32 py;
    f32 pz;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 dx;
    f32 dz;
    f32 scale;
    s32 n0;
    s32 n1;
    s32 n2;
    s32 i;

    n2 = 0;
    n1 = 0;
    n0 = 0;
    for (i = 0; i < 30; i++) {
        func_8001C258_main(obj->model[i + 9], 4, 4);
    }
    i = 0;
    while (1) {
        switch (D_801097EC_dizzy_dinghies) {
        case 0:
            kind = D_80109988_dizzy_dinghies[i];
            px = D_801097F0_dizzy_dinghies[i].x;
            py = D_801097F0_dizzy_dinghies[i].y;
            pz = D_801097F0_dizzy_dinghies[i].z;
            rx = D_801098BC_dizzy_dinghies[i].x;
            ry = D_801098BC_dizzy_dinghies[i].y;
            rz = D_801098BC_dizzy_dinghies[i].z;
            break;
        case 1:
            kind = D_80109B64_dizzy_dinghies[i];
            px = D_8010999C_dizzy_dinghies[i].x;
            py = D_8010999C_dizzy_dinghies[i].y;
            pz = D_8010999C_dizzy_dinghies[i].z;
            rx = D_80109A80_dizzy_dinghies[i].x;
            ry = D_80109A80_dizzy_dinghies[i].y;
            rz = D_80109A80_dizzy_dinghies[i].z;
            break;
        case 2:
            kind = D_80109D28_dizzy_dinghies[i];
            px = D_80109B78_dizzy_dinghies[i].x;
            py = D_80109B78_dizzy_dinghies[i].y;
            pz = D_80109B78_dizzy_dinghies[i].z;
            rx = D_80109C50_dizzy_dinghies[i].x;
            ry = D_80109C50_dizzy_dinghies[i].y;
            rz = D_80109C50_dizzy_dinghies[i].z;
            break;
        }
        if (kind == -1) {
            break;
        }
        dx = Center.x - px;
        dz = Center.z - pz;
        if (HuSqrtf(dx * dx + dz * dz) < 2500.0f) {
            switch (kind) {
            case 0:
                if (n0 < 5) {
                    Hu3DModelPosSet(obj->model[n0 + 9], px, py, pz);
                    Hu3DModelRotSet(obj->model[n0 + 9], rx, ry, rz);
                    Hu3DModelScaleSet(obj->model[n0 + 9], 1.5f, 1.5f, 1.5f);
                    func_8001C258_main(obj->model[n0 + 9], 4, 0);
                    n0++;
                }
                break;
            case 1:
                if (n1 < 5) {
                    Hu3DModelPosSet(obj->model[n1 + 19], px, py, pz);
                    Hu3DModelRotSet(obj->model[n1 + 19], rx, ry, rz);
                    Hu3DModelScaleSet(obj->model[n1 + 19], 1.5f, 1.5f, 1.5f);
                    func_8001C258_main(obj->model[n1 + 19], 4, 0);
                    n1++;
                }
                break;
            case 2:
                if (n2 < 5) {
                    if (D_801097EC_dizzy_dinghies == 1) {
                        scale = 0.8f;
                    } else {
                        scale = 1.5f;
                    }
                    Hu3DModelPosSet(obj->model[n2 + 29], px, py, pz);
                    Hu3DModelRotSet(obj->model[n2 + 29], rx, ry, rz);
                    Hu3DModelScaleSet(obj->model[n2 + 29], scale, scale, scale);
                    func_8001C258_main(obj->model[n2 + 29], 4, 0);
                    n2++;
                }
                break;
            }
        }
        i++;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80106DF4_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80107098_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80107738_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80107DE8_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80107E04_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80108488_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80108514_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_801085F4_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80108E30_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80108EC4_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_801090BC_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80109238_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80109420_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_801095D4_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109EF0_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F04_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F14_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F24_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F3C_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F50_dizzy_dinghies);
