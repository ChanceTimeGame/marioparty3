#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// dinghies A: Dizzy Dinghies (players steer dinghies on a rippling sea)

typedef func_800E1BA8_minigame_ObjData MgWork;

/* omObjData::data of the sea (the framework's ground object, minigame mgcol.h GroundWork) */
typedef struct DdGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} DdGround; /* size 0xB4 */

// main
s32 func_8000B638_main(void);
void func_80021BE0_main(s32* arg0, s32 n);
void func_800142A0_main(s32);
void Hu3DAnimInit(s32);
void func_8001E65C_main(s16 mdl, f32 u, f32 v, s32 w, s32 h);
s16 func_8000B13C_main(s32 file);
void func_8001FB34_main(s16 arg0, u8 arg1);
void func_8001FBFC_main(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80017358_main(s16 arg0, char* arg1, s16 arg2, char* arg3);
u8 rand8(void);

extern s32 D_800A178C_main[][6];

/* D_800CB890_main: a float (far distance) then a s16 the dinghy model file and speed depend on (0..2) */
extern struct {
    f32 unk00;
    s16 unk04;
} D_800CB890_main;
extern u8 D_800CE20A_main;
extern u8 D_800D2008_main;
extern f32 D_800D5210_main;
extern u8 D_800D6A90_main;

// minigame
void func_800E1490_minigame(u16 arg0);
void func_800E1804_minigame(void);
void func_800E12EC_minigame(omObjData* obj, f32 arg1);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1334_minigame(omObjData* obj, f32 arg1);
void func_800E1340_minigame(omObjData* obj, f32 arg1);
void func_800E134C_minigame(omObjData* obj, f32 arg1);
void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E147C_minigame(omObjData* obj);
u16 func_800E6E9C_minigame(void);

extern f32 D_800EB73C_minigame;
extern f32 D_800EB77C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[]; /* minigame mgcol.h HitList */

extern s32 D_8010A020_dizzy_dinghies;
extern u16 D_8010A022_dizzy_dinghies;

// LOCAL

void func_80105CAC_dizzy_dinghies(omObjData* obj);
void func_80105D64_dizzy_dinghies(omObjData* obj);
f32 func_80105D90_dizzy_dinghies(f32 x, f32 z);
void func_80105EB4_dizzy_dinghies(omObjData* obj);
void func_80106494_dizzy_dinghies(omObjData* obj);
void func_8010655C_dizzy_dinghies(omObjData* obj);
void func_80106818_dizzy_dinghies(omObjData* obj);
void func_80106970_dizzy_dinghies(omObjData* obj);
void func_80106DF4_dizzy_dinghies(omObjData* obj);
void func_80107098_dizzy_dinghies(omObjData* obj);
void func_80107738_dizzy_dinghies(omObjData* obj, s32 player);
void func_801085F4_dizzy_dinghies(omObjData* obj);
void func_80107098_dizzy_dinghies(omObjData* obj);
void func_80107DE8_dizzy_dinghies(omObjData* obj);
void func_80109420_dizzy_dinghies(omObjData* obj);

extern s16 D_800EB934_minigame;

extern Vec D_80109740_dizzy_dinghies[]; /* start positions, one per board (D_801097EC) */
extern f32 D_80109768_dizzy_dinghies; /* start heading */
extern f32 D_80109770_dizzy_dinghies;
extern f32 D_80109774_dizzy_dinghies;
extern f32 D_80109778_dizzy_dinghies;
extern f32 D_80109780_dizzy_dinghies;
extern f32 D_80109784_dizzy_dinghies;
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
extern f32 D_801097E4_dizzy_dinghies;
extern s32 D_801097E8_dizzy_dinghies; /* looping sound handle (func_8004AC98_main), -1 none */
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
extern s32 D_80109D84_dizzy_dinghies[][3]; /* course object model files per board */
extern s32 D_80109DA8_dizzy_dinghies[][3]; /* their motion files */
extern char* D_80109DCC_dizzy_dinghies[]; /* head part name per character */
extern s8 D_80109DF8_dizzy_dinghies[4];
extern s16 D_80109DFC_dizzy_dinghies; /* shared models, -1 until loaded */
extern s16 D_80109DFE_dizzy_dinghies;
extern s16 D_80109E00_dizzy_dinghies;
extern char D_80109F50_dizzy_dinghies[];
extern u8 D_80109D40_dizzy_dinghies;
extern s8 D_80109D42_dizzy_dinghies;
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
    D_800CB890_main.unk00 = 12000.0f;
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

/* The sea and intro/outro controller (the minigame state from func_800E6F40_minigame). */
void func_80106DF4_dizzy_dinghies(omObjData* obj) {
    s32 t;
    s32 i;

    func_80105EB4_dizzy_dinghies(obj);
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        t = func_800E6E9C_minigame();
        switch (func_800E6F40_minigame()) {
        case 0:
            if (t == 5) {
                HuAudFXPlay(0x424);
                D_801097E8_dizzy_dinghies = func_8004AC98_main(D_8010A022_dizzy_dinghies + 0x428, 0);
            }
        case 1:
            func_8010655C_dizzy_dinghies(obj);
            break;
        case 2:
            if (t == 0) {
                HuAudFXPlay(0x427);
            }
            func_80106818_dizzy_dinghies(obj);
            break;
        case 3:
            if (t == 15.0) {
                func_8004AEF0_main((s16)D_801097E8_dizzy_dinghies, 30);
                D_801097E8_dizzy_dinghies = -1;
            }
            if (t == 1) {
                D_80109778_dizzy_dinghies -= 0.025f;
            }
            D_801097E0_dizzy_dinghies *= 0.95f;
            D_80109D42_dizzy_dinghies = 9;
        case 4:
            if (D_800EB934_minigame == 1) {
                if (D_801097D4_dizzy_dinghies == 0) {
                    HuAudSeqPlay(0x6B);
                } else if (D_80109D40_dizzy_dinghies == 1) {
                    HuAudSeqPlay(0x6A);
                } else {
                    HuAudSeqPlay(0x65);
                }
            }
            break;
        case 5:
            WipeCreateOut(0, 20);
            obj->func = func_80105D64_dizzy_dinghies;
            func_8004AB0C_main(30);
            break;
        }
        for (i = 0; i < D_800EC280_minigame; i++) {
            ((MgWork*)D_800EC598_minigame[i]->data)->unk60 = CRot.y;
        }
        if (D_800D530C_main == 1) {
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            obj->func = func_80105D64_dizzy_dinghies;
        }
        func_80106970_dizzy_dinghies(obj);
    }
}

/* The sea (ground object): its models, the course object models, and the ground setup. */
void func_80107098_dizzy_dinghies(omObjData* obj) {
    s16 mot;
    DdGround* gw;

    obj->model[0] = func_8000B0A0_main((D_801097EC_dizzy_dinghies + 3) | 0x670000, 0x4B9);
    obj->model[1] = func_8000B0A0_main(0x670006, 0x4A9);
    obj->model[2] = func_8000B0A0_main(0x670007, 0x8C9);
    obj->model[3] = func_8000B0A0_main(0xA0089, 0x8C9);
    obj->model[9] = func_8000B0A0_main(D_80109D84_dizzy_dinghies[D_801097EC_dizzy_dinghies][0], 0x4DD);
    obj->model[10] = Hu3DModelLink(obj->model[9]);
    obj->model[11] = Hu3DModelLink(obj->model[9]);
    obj->model[12] = Hu3DModelLink(obj->model[9]);
    mot = func_8000B13C_main(D_80109DA8_dizzy_dinghies[D_801097EC_dizzy_dinghies][0]);
    func_8001C5B4_main(obj->model[9], mot);
    func_8001C5B4_main(obj->model[10], mot);
    func_8001C5B4_main(obj->model[11], mot);
    func_8001C5B4_main(obj->model[12], mot);
    func_8001C814_main(obj->model[9], 2, 2);
    func_8001C814_main(obj->model[10], 2, 2);
    func_8001C814_main(obj->model[11], 2, 2);
    func_8001C814_main(obj->model[12], 2, 2);
    obj->model[19] = func_8000B0A0_main(D_80109D84_dizzy_dinghies[D_801097EC_dizzy_dinghies][1], 0x4DD);
    obj->model[20] = Hu3DModelLink(obj->model[19]);
    obj->model[21] = Hu3DModelLink(obj->model[19]);
    obj->model[22] = Hu3DModelLink(obj->model[19]);
    mot = func_8000B13C_main(D_80109DA8_dizzy_dinghies[D_801097EC_dizzy_dinghies][1]);
    func_8001C5B4_main(obj->model[19], mot);
    func_8001C5B4_main(obj->model[20], mot);
    func_8001C5B4_main(obj->model[21], mot);
    func_8001C5B4_main(obj->model[22], mot);
    func_8001C814_main(obj->model[19], 2, 2);
    func_8001C814_main(obj->model[20], 2, 2);
    func_8001C814_main(obj->model[21], 2, 2);
    func_8001C814_main(obj->model[22], 2, 2);
    obj->model[29] = func_8000B0A0_main(D_80109D84_dizzy_dinghies[D_801097EC_dizzy_dinghies][2], 0x4DD);
    obj->model[30] = Hu3DModelLink(obj->model[29]);
    obj->model[31] = Hu3DModelLink(obj->model[29]);
    obj->model[32] = Hu3DModelLink(obj->model[29]);
    mot = func_8000B13C_main(D_80109DA8_dizzy_dinghies[D_801097EC_dizzy_dinghies][2]);
    func_8001C5B4_main(obj->model[29], mot);
    func_8001C5B4_main(obj->model[30], mot);
    func_8001C5B4_main(obj->model[31], mot);
    func_8001C5B4_main(obj->model[32], mot);
    func_8001C814_main(obj->model[29], 2, 2);
    func_8001C814_main(obj->model[30], 2, 2);
    func_8001C814_main(obj->model[31], 2, 2);
    func_8001C814_main(obj->model[32], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(DdGround), 31000);
    memset(gw, 0, sizeof(DdGround));
    obj->func = func_80106DF4_dizzy_dinghies;
    gw->unk03 = 1;
    Center.x = -224.0f;
    Center.y = 300.0f;
    Center.z = 300.0f;
    CRot.x = 330.0f;
    CRot.y = 5.0f;
    CZoom = 4500.0f;
    func_800E147C_minigame(obj);
    func_800E1370_minigame(obj, 1, 0.0f);
    func_800E1304_minigame(obj, 0.2f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E131C_minigame(obj, 25.0f);
    gw->unk04 = 0;
    func_8001FB34_main(obj->model[1], 1);
    func_8001FBFC_main(obj->model[1], -66.0f, -99.0f, -9.0f);
    func_8001C2FC_main(obj->model[1], 0x20000, 0x20000);
    func_8001C448_main(obj->model[1]);
    func_8001C954_main(obj->model[1]);
    omSetStatBit(obj, 0xA0);
    Hu3DModelPosSet(obj->model[2], D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x + 500.0f, D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y + 500.0f, D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z);
    Hu3DModelPosSet(obj->model[3], D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x + 500.0f, D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y + 500.0f, D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[3], 2.0f, 2.0f, 2.0f);
    func_8001C814_main(obj->model[2], 1, 1);
    func_8001C814_main(obj->model[3], 2, 2);
}

/* The player: character and dinghy models, actor work, start position. */
void func_80107738_dizzy_dinghies(omObjData* obj, s32 player) {
    MgWork* work;
    s32 chrMdl;
    s32 file0;
    s32 file1;
    s32 kind;
    s32 attr;
    s32 i;

    attr = 0x6D9;
    for (i = 0; i < obj->mdlcnt; i++) {
        obj->model[i] = 0;
    }
    obj->data = HuMemAllocTag(sizeof(MgWork), 0x7918);
    memset(obj->data, 0, sizeof(MgWork));
    work = obj->data;
    file1 = D_800A178C_main[GwPlayer[(u16)player].chr][2];
    file0 = D_800A178C_main[GwPlayer[(u16)player].chr][0];
    chrMdl = func_8000B108_main(file0 | file1, attr | 4);
    kind = D_800CB890_main.unk04;
    D_8010A020_dizzy_dinghies = kind;
    obj->model[0] = func_8000B108_main(kind | 0x670000, attr);
    func_80017358_main(chrMdl, D_80109DCC_dizzy_dinghies[GwPlayer[(u16)player].chr], obj->model[0], D_80109F50_dizzy_dinghies);
    switch (kind) {
    case 0:
        D_80109770_dizzy_dinghies = 80.0f;
        D_80109774_dizzy_dinghies = 1.1f;
        D_80109778_dizzy_dinghies = 0.975f;
        D_80109780_dizzy_dinghies = 0.925f;
        D_80109784_dizzy_dinghies = 0.775f;
        break;
    case 1:
        D_80109770_dizzy_dinghies = 85.0f;
        D_80109774_dizzy_dinghies = 1.025f;
        D_80109778_dizzy_dinghies = 0.97f;
        D_80109780_dizzy_dinghies = 0.92f;
        D_80109784_dizzy_dinghies = 0.76f;
        break;
    case 2:
    default:
        D_80109770_dizzy_dinghies = 90.0f;
        D_80109774_dizzy_dinghies = 1.0125f;
        D_80109778_dizzy_dinghies = 0.96f;
        D_80109780_dizzy_dinghies = 0.9125f;
        D_80109784_dizzy_dinghies = 0.75f;
        break;
    }
    work->unk57 = GwPlayer[(u16)player].pad;
    obj->func = func_801085F4_dizzy_dinghies;
    work->unk52 = 0;
    work->unkB4 = 1.0f;
    work->unk8C = 65536.0f;
    work->unkD0 = 0xFFFF;
    work->unk4C = 0.5f;
    work->unkCC = 1.0f;
    work->unk60 = 0;
    func_800E1328_minigame(obj, 100.0f);
    func_800E1334_minigame(obj, 150.0f);
    func_800E1340_minigame(obj, 20.0f);
    func_800E134C_minigame(obj, 30.0f);
    func_800E12EC_minigame(obj, 1000.0f);
    work->unk9C = work->unkA0 = work->unkA4 = 0.0f;
    work->unk59 = player;
    work->unkC3 = -1;
    work->unkC4 = -1;
    work->unkB0 = 1.0f;
    work->unkAC = 1.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    for (i = 0; i < 6; i++) {
        if (i == 3 || i == 0) {
            if (D_80109DFC_dizzy_dinghies < 0) {
                obj->model[i + 1] = D_80109DFC_dizzy_dinghies = func_8000B108_main(0x440006, 0x889);
            } else {
                obj->model[i + 1] = Hu3DModelLink(D_80109DFC_dizzy_dinghies);
            }
        } else if (i == 4 || i == 1) {
            if (D_80109DFE_dizzy_dinghies < 0) {
                obj->model[i + 1] = D_80109DFE_dizzy_dinghies = func_8000B108_main(0x440007, 0x889);
            } else {
                obj->model[i + 1] = Hu3DModelLink(D_80109DFE_dizzy_dinghies);
            }
        } else {
            if (D_80109E00_dizzy_dinghies < 0) {
                obj->model[i + 1] = D_80109E00_dizzy_dinghies = func_8000B108_main(0x440008, 0x889);
            } else {
                obj->model[i + 1] = Hu3DModelLink(D_80109E00_dizzy_dinghies);
            }
        }
        func_8001C2FC_main(obj->model[i + 1], 0x70000000, 0x70000000);
    }
    if (kind == 2) {
        for (i = 0; i < 6; i++) {
            if (i == 3 || i == 0) {
                obj->model[i + 7] = Hu3DModelLink(D_80109DFC_dizzy_dinghies);
            } else if (i == 4 || i == 1) {
                obj->model[i + 7] = Hu3DModelLink(D_80109DFE_dizzy_dinghies);
            } else {
                obj->model[i + 7] = Hu3DModelLink(D_80109E00_dizzy_dinghies);
            }
            func_8001C2FC_main(obj->model[i + 7], 0x70000000, 0x70000000);
        }
    }
    work = obj->data;
    work->unk3C = D_80109768_dizzy_dinghies;
    func_800E149C_minigame(obj, 0, 2);
    do {
        i = rand8() & 3;
    } while (D_80109DF8_dizzy_dinghies[i] != -1);
    obj->trans.x = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x;
    obj->trans.y = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y;
    obj->trans.z = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z;
    Center.x = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x;
    Center.y = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y;
    Center.z = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z;
    func_8001C6A8_main(obj->model[0], 5.0f);
    func_8001C814_main(obj->model[0], 1, 1);
    switch (GwPlayer[(u16)player].chr) {
    case 2:
    case 6:
    case 7:
        D_801097E4_dizzy_dinghies = 3.0f;
        break;
    case 4:
        D_801097E4_dizzy_dinghies = 1.8f;
        break;
    }
}

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
