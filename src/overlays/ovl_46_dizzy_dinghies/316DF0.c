#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"

// dinghies A: Dizzy Dinghies (players steer dinghies on a rippling sea)

typedef func_800E1BA8_minigame_ObjData MgWork;

typedef struct Vec4f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ f32 w; /* radius */
} Vec4f;

/* The minigame control block (minigame B8A20.c MgCtrl; the header's D_80111B50_vine_with_me_Struct) */
typedef struct DdCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04; /* 1: the goal was reached */
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ Vec unk28;
} DdCtrl; /* size 0x34 */

/* What func_8001D33C_main returns (a model's motion group or hit transform), as far as used here */
typedef struct DdPart {
    /* 0x00 */ char unk00[0x1C];
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ char unk28[0x18];
    /* 0x40 */ Vec unk40;
} DdPart;

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
void* func_8001D33C_main(s16 model, char* name);
f32 func_800202A8_main(f32 angle);
s32 func_800202FC_main(Vec* v);
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z);
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
void func_800E17D4_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800E2308_minigame(s16* x, s16* y);
s32 func_800DD530_minigame(omObjData* obj, Vec4f* p, f32 arg2);
f64 fabs(f64);
void func_800E6F0C_minigame(s8 arg0);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_800E9C20_minigame(s16 count, u16 len);
void func_800E9F40_minigame(s16 idx, s32 x, s32 y, s16 dir);
void func_800EA0FC_minigame(s16 idx, f32 min, f32 max);
void func_800EA2A8_minigame(s16 idx);
void func_800EA178_minigame(s16 idx, f32 value);

extern f32 D_800EBE2C_minigame;
extern f32 D_800EC5D8_minigame;
void func_800E147C_minigame(omObjData* obj);
u16 func_800E6E9C_minigame(void);

extern f32 D_800EB73C_minigame;
extern f32 D_800EB77C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[]; /* minigame mgcol.h HitList */

extern s32 D_80109E04_dizzy_dinghies; /* last splash slot */
extern s16 D_80109E08_dizzy_dinghies[20]; /* history for the running mean func_80108488 */
extern s32 D_80109E30_dizzy_dinghies;
extern s32 D_80109E34_dizzy_dinghies;
extern s32 D_80109E3C_dizzy_dinghies; /* rumble cooldown */
extern s32 D_80109E40_dizzy_dinghies;
extern Vec D_80109E44_dizzy_dinghies[][3]; /* three points of the goal plane per board */

extern Vec D_80109F60_dizzy_dinghies[6]; /* splash positions */
extern f32 D_80109FA8_dizzy_dinghies[6]; /* splash speeds */
extern Vec D_80109FC0_dizzy_dinghies[6]; /* splash directions (x, z) */
extern f32 D_8010A008_dizzy_dinghies[6]; /* splash scales */
extern s32 D_8010A020_dizzy_dinghies;
extern Vec D_8010A028_dizzy_dinghies[20]; /* history for the running mean func_80108514 */
extern s32 D_8010A118_dizzy_dinghies; /* the pad's buttons, taken from the game this frame */
extern s32 D_8010A11C_dizzy_dinghies; /* the pad's stick x, taken likewise */
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
void func_80107E04_dizzy_dinghies(omObjData* obj, f32 scale);
s32 func_80108488_dizzy_dinghies(s32 player, s16 v);
void func_80108514_dizzy_dinghies(s32 player, f32 speed, Vec* out);
void func_80108E30_dizzy_dinghies(Vec* a, Vec* b, Vec* c, Vec* n);
void func_80108EC4_dizzy_dinghies(omObjData* obj, f32 x, f32 z);
void func_801090BC_dizzy_dinghies(omObjData* obj, f32 x, f32 z);
f32 func_80109238_dizzy_dinghies(omObjData* obj, f32 x, f32 y, f32 z);
void func_801095D4_dizzy_dinghies(omObjData* obj);
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
extern f32 D_8010977C_dizzy_dinghies;
extern Vec D_80109788_dizzy_dinghies; /* last move */
extern Vec D_80109794_dizzy_dinghies; /* position before the move */
extern Vec D_801097A0_dizzy_dinghies; /* push direction */
extern f32 D_801097AC_dizzy_dinghies; /* push strength */
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
extern DdCtrl D_80109D3C_dizzy_dinghies;
extern s32 D_80109D84_dizzy_dinghies[][3]; /* course object model files per board */
extern s32 D_80109DA8_dizzy_dinghies[][3]; /* their motion files */
extern char* D_80109DCC_dizzy_dinghies[]; /* head part name per character */
extern s8 D_80109DF8_dizzy_dinghies[4];
extern s16 D_80109DFC_dizzy_dinghies; /* shared models, -1 until loaded */
extern s16 D_80109DFE_dizzy_dinghies;
extern s16 D_80109E00_dizzy_dinghies;
extern char D_80109EF0_dizzy_dinghies[];
extern char D_80109F04_dizzy_dinghies[];
extern char D_80109F14_dizzy_dinghies[];
extern char D_80109F24_dizzy_dinghies[];
extern char D_80109F3C_dizzy_dinghies[];
extern char D_80109F50_dizzy_dinghies[];
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
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_80109D3C_dizzy_dinghies);
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
            D_80109D3C_dizzy_dinghies.unk06 = 9;
        case 4:
            if (D_800EB934_minigame == 1) {
                if (D_801097D4_dizzy_dinghies == 0) {
                    HuAudSeqPlay(0x6B);
                } else if (D_80109D3C_dizzy_dinghies.unk04 == 1) {
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

void func_80107DE8_dizzy_dinghies(omObjData* obj) {
    func_80107738_dizzy_dinghies(obj, 0);
}

/* Spawn a splash behind the dinghy and move the live ones (models 1..6; also 7..12 for the wide dinghy). */
void func_80107E04_dizzy_dinghies(omObjData* obj, f32 scale) {
    f32 heading;
    f32 rnd;
    f32 a;
    f32 ox;
    f32 oz;
    f32 ox2;
    f32 oz2;
    f32 s;
    s32 idx;
    s32 i;

    heading = ((MgWork*)obj->data)->unk3C;
    idx = D_80109E04_dizzy_dinghies + 1;
    if (idx == 6) {
        idx = 0;
    }
    D_80109E04_dizzy_dinghies = idx;
    D_8010A008_dizzy_dinghies[idx] = 1.0f;
    D_80109FA8_dizzy_dinghies[idx] = scale * 10.0f;
    rnd = (rand8() - 128) / 4;
    D_80109F60_dizzy_dinghies[idx].x = sindf(heading + 180.0f) * 150.0f + obj->trans.x + sindf(heading + 90.0f) + rnd;
    D_80109F60_dizzy_dinghies[idx].y = obj->trans.y;
    D_80109F60_dizzy_dinghies[idx].z = cosdf(heading + 180.0f) * 150.0f + obj->trans.z + sindf(heading + 90.0f) + rnd;
    rnd = (rand8() - 128) / 4;
    a = heading + 180.0f + rnd;
    D_80109FC0_dizzy_dinghies[idx].x = sindf(a);
    D_80109FC0_dizzy_dinghies[idx].z = cosdf(a);
    if (D_8010A020_dizzy_dinghies == 2) {
        for (i = 0; i < 6; i++) {
            if (D_80109FA8_dizzy_dinghies[i] > 0.0f) {
                ox = sindf(heading + 90.0f) * 60.0f;
                oz = cosdf(heading + 90.0f) * 60.0f;
                ox2 = sindf(heading + 90.0f) * -60.0f;
                oz2 = cosdf(heading + 90.0f) * -60.0f;
                D_80109F60_dizzy_dinghies[i].x += D_80109FC0_dizzy_dinghies[i].x * D_80109FA8_dizzy_dinghies[i] * scale;
                D_80109F60_dizzy_dinghies[i].y -= 20.0f;
                D_80109F60_dizzy_dinghies[i].z += D_80109FC0_dizzy_dinghies[i].z * D_80109FA8_dizzy_dinghies[i] * scale;
                s = scale * (D_8010A008_dizzy_dinghies[i] *= 1.3f);
                Hu3DModelPosSet(obj->model[i + 1], ox + D_80109F60_dizzy_dinghies[i].x, D_80109F60_dizzy_dinghies[i].y, oz + D_80109F60_dizzy_dinghies[i].z);
                Hu3DModelScaleSet(obj->model[i + 1], s, s, s);
                func_8001C258_main(obj->model[i + 1], 4, 0);
                Hu3DModelPosSet(obj->model[i + 7], ox2 + D_80109F60_dizzy_dinghies[i].x, D_80109F60_dizzy_dinghies[i].y, oz2 + D_80109F60_dizzy_dinghies[i].z);
                Hu3DModelScaleSet(obj->model[i + 7], s, s, s);
                func_8001C258_main(obj->model[i + 7], 4, 0);
            } else {
                func_8001C258_main(obj->model[i + 1], 4, 4);
                func_8001C258_main(obj->model[i + 7], 4, 4);
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            if (D_80109FA8_dizzy_dinghies[i] > 0.0f) {
                D_80109F60_dizzy_dinghies[i].x += D_80109FC0_dizzy_dinghies[i].x * D_80109FA8_dizzy_dinghies[i] * scale;
                D_80109F60_dizzy_dinghies[i].y -= 20.0f;
                D_80109F60_dizzy_dinghies[i].z += D_80109FC0_dizzy_dinghies[i].z * D_80109FA8_dizzy_dinghies[i] * scale;
                Hu3DModelPosSet(obj->model[i + 1], D_80109F60_dizzy_dinghies[i].x, D_80109F60_dizzy_dinghies[i].y, D_80109F60_dizzy_dinghies[i].z);
                s = scale * (D_8010A008_dizzy_dinghies[i] *= 1.3f);
                Hu3DModelScaleSet(obj->model[i + 1], s, s, s);
                func_8001C258_main(obj->model[i + 1], 4, 0);
            } else {
                func_8001C258_main(obj->model[i + 1], 4, 4);
            }
        }
    }
}


/* Mean of the last 20 values passed. */
s32 func_80108488_dizzy_dinghies(s32 player, s16 v) {
    s32 sum;
    u8 i;

    D_80109E08_dizzy_dinghies[D_80109E34_dizzy_dinghies] = v;
    D_80109E34_dizzy_dinghies++;
    if (D_80109E34_dizzy_dinghies >= 20) {
        D_80109E34_dizzy_dinghies = 0;
    }
    sum = 0;
    for (i = 0; i < 20; i++) {
        sum += D_80109E08_dizzy_dinghies[i];
    }
    return sum / 20;
}

/* Mean x and z of the last 20 values of D_80109788. */
void func_80108514_dizzy_dinghies(s32 player, f32 speed, Vec* out) {
    s32 i;

    out->x = out->y = out->z = 0.0f;
    D_8010A028_dizzy_dinghies[D_80109E30_dizzy_dinghies].x = D_80109788_dizzy_dinghies.x;
    D_8010A028_dizzy_dinghies[D_80109E30_dizzy_dinghies].z = D_80109788_dizzy_dinghies.z;
    D_80109E30_dizzy_dinghies++;
    if (D_80109E30_dizzy_dinghies >= 20) {
        D_80109E30_dizzy_dinghies = 0;
    }
    for (i = 0; i < 20; i++) {
        out->x += D_8010A028_dizzy_dinghies[i].x;
        out->z += D_8010A028_dizzy_dinghies[i].z;
    }
    out->x /= 20.0f;
    out->z /= 20.0f;
}

#ifdef NON_MATCHING
/* Differs only in f20/f22 allocation (speed and y). */
/* The player's dinghy: paddle with A, steer with the stick; the sea and pushes move it. */
void func_801085F4_dizzy_dinghies(omObjData* obj) {
    Vec vel;
    Vec mean;
    s16 sx;
    s16 sy;
    MgWork* work;
    DdPart* part;
    s32 mode;
    s32 player;
    s32 pad;
    f32 y;
    f32 speed;
    f32 x;
    f32 z;
    f32 h;
    f32 d;
    f32 mot;
    s32 ax;

    work = obj->data;
    D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
    player = work->unk59;
    pad = work->unk57;
    speed = work->unk40;
    D_80109794_dizzy_dinghies.x = x = obj->trans.x;
    D_80109794_dizzy_dinghies.y = y = obj->trans.y;
    D_80109794_dizzy_dinghies.z = z = obj->trans.z;
    D_8010A118_dizzy_dinghies = (u16)D_800CDA7C_main[pad];
    D_8010A11C_dizzy_dinghies = D_800CBB6E_main[pad];
    D_800CBB6E_main[pad] = 0;
    D_800CDA7C_main[pad] = 0;
    mode = func_800E6E8C_minigame();
    if (mode == 2) {
        sx = (u16)D_8010A11C_dizzy_dinghies;
        sy = 0;
        if (sx > 60) {
            sx = 60;
        }
        if (sy > 60) {
            sy = 60;
        }
        if (sx < -60) {
            sx = -60;
        }
        if (sy < -60) {
            sy = -60;
        }
        func_800E2308_minigame(&sx, &sy);
    } else {
        sy = 0;
        sx = 0;
        D_8010A118_dizzy_dinghies = 0;
        if (mode == 3) {
            if (work->unk3C > 180.0f) {
                work->unk3C += 2.0f;
                if (work->unk3C > 360.0f) {
                    work->unk3C = 0.0f;
                }
            } else {
                work->unk3C -= 2.0f;
                if (work->unk3C < 0.0f) {
                    work->unk3C = 0.0f;
                }
            }
        }
    }
    if (D_8010A118_dizzy_dinghies & 0x8000) {
        if (speed == 0.0f) {
            speed = 1.0f;
        }
        speed *= 1.08f;
        D_801097B0_dizzy_dinghies *= D_80109774_dizzy_dinghies;
    } else {
        speed *= D_80109778_dizzy_dinghies;
        D_801097B0_dizzy_dinghies *= 0.9f;
    }
    y = func_80108488_dizzy_dinghies(player, sx) / 15.0f;
    if (speed < 1.0f) {
        speed = 0.0f;
    }
    if (speed > D_80109770_dizzy_dinghies) {
        speed = D_80109770_dizzy_dinghies;
    }
    if (D_801097B0_dizzy_dinghies < 0.05f) {
        D_801097B0_dizzy_dinghies = 0.05f;
    }
    if (D_801097B0_dizzy_dinghies > 1.0f) {
        D_801097B0_dizzy_dinghies = 1.0f;
    }
    if (D_801097E8_dizzy_dinghies != -1) {
        HuAudFXPitchSet((s16)D_801097E8_dizzy_dinghies, (s16)(D_801097B0_dizzy_dinghies * 400.0f + -400.0f));
    }
    work->unk40 = speed;
    vel.x = sindf(work->unk3C) * (speed * D_801097B0_dizzy_dinghies);
    vel.y = 0.0f;
    vel.z = cosdf(work->unk3C) * (speed * D_801097B0_dizzy_dinghies);
    work->unk3C = func_800202A8_main(work->unk3C - y);
    func_80108514_dizzy_dinghies(player, speed, &mean);
    mean.x += vel.x;
    mean.z += vel.z;
    d = HuSqrtf(mean.x * mean.x + mean.z * mean.z);
    if (speed < d) {
        mean.x = (speed / d) * mean.x;
        mean.z = (speed / d) * mean.z;
    }
    x += D_801097A0_dizzy_dinghies.x * D_801097AC_dizzy_dinghies + mean.x;
    z += D_801097A0_dizzy_dinghies.z * D_801097AC_dizzy_dinghies + mean.z;
    h = func_80109238_dizzy_dinghies(obj, x, 0.0f, z);
    D_80109788_dizzy_dinghies.x = x - D_80109794_dizzy_dinghies.x;
    D_80109788_dizzy_dinghies.y = 0.0f;
    D_80109788_dizzy_dinghies.z = z - D_80109794_dizzy_dinghies.z;
    x += D_800EBE2C_minigame;
    z += D_800EC5D8_minigame;
    D_801097D8_dizzy_dinghies -= (obj->trans.x - x) * 32.0f / 1000.0f;
    D_801097DC_dizzy_dinghies += (obj->trans.z - z) * 32.0f / 1000.0f;
    func_80108EC4_dizzy_dinghies(obj, x, z);
    speed = work->unk40;
    func_80088910_main((f32(*)[4])HmfModelData[obj->model[0]].mtx, 0.0f, work->unk3C, 0.0f);
    func_800E17D4_minigame(obj, x, h - 40.0f, z);
    func_80107E04_dizzy_dinghies(obj, D_801097B0_dizzy_dinghies);
    if (D_801097AC_dizzy_dinghies != 0.0f) {
        D_801097AC_dizzy_dinghies *= 0.9f;
        if (D_801097AC_dizzy_dinghies < 1.0f) {
            D_801097AC_dizzy_dinghies = 0.0f;
        }
    }
    mot = HmfModelData[obj->model[0]].unk40;
    ax = sx;
    if (ax < 0) {
        ax = -ax;
    }
    if (ax < 10) {
        if (mot > 5.0f) {
            mot *= 0.9f;
            if (mot < 5.0f) {
                mot = 5.0f;
            }
        } else {
            mot *= 1.1f;
            if (mot > 5.0f) {
                mot = 5.0f;
            }
            if (mot < 1.0f) {
                mot = 1.0f;
            }
        }
    } else {
        mot -= sx / 100.0f;
    }
    if (mot < 0.0f) {
        mot = 0.0f;
    }
    if (mot > 10.0f) {
        mot = 10.0f;
    }
    func_8001C6A8_main(obj->model[0], mot);
    func_801095D4_dizzy_dinghies(obj);
    D_800CDA7C_main[pad] = (u16)D_8010A118_dizzy_dinghies;
    D_800CBB6E_main[pad] = (u8)D_8010A11C_dizzy_dinghies;
    part = func_8001D33C_main(obj->model[0], D_80109F50_dizzy_dinghies);
    if (part != (void*)-1) {
        part->unk1C.z = part->unk1C.y = part->unk1C.x = D_801097E4_dizzy_dinghies;
        part->unk40.z = part->unk40.y = part->unk40.x = D_801097E4_dizzy_dinghies;
    }
    func_800EA178_minigame(0, speed);
}

#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_801085F4_dizzy_dinghies);
#endif

/* Unit normal of the triangle a, b, c. */
void func_80108E30_dizzy_dinghies(Vec* a, Vec* b, Vec* c, Vec* n) {
    f32 ux;
    f32 uy;
    f32 uz;
    f32 vx;
    f32 vy;
    f32 vz;

    ux = b->x - a->x;
    uy = b->y - a->y;
    uz = b->z - a->z;
    vx = c->x - a->x;
    vy = c->y - a->y;
    vz = c->z - a->z;
    n->x = uy * vz - uz * vy;
    n->y = uz * vx - ux * vz;
    n->z = ux * vy - uy * vx;
    func_800202FC_main(n);
}

/* Tilt the dinghy (rot.x, rot.z) toward the sea's slope at (x, z), one degree a frame. */
void func_80108EC4_dizzy_dinghies(omObjData* obj, f32 x, f32 z) {
    Vec p0;
    Vec p1;
    Vec p2;
    Vec n;
    MgWork* work;

    p0.x = x;
    p0.y = func_80105D90_dizzy_dinghies(x, z);
    p0.z = z;
    p1.x = x + sindf(0.0f) * 10.0f;
    p1.z = z + cosdf(0.0f) * 10.0f;
    p1.y = func_80105D90_dizzy_dinghies(p1.x, p1.z);
    p2.x = x + sindf(90.0f) * 10.0f;
    p2.z = z + cosdf(90.0f) * 10.0f;
    p2.y = func_80105D90_dizzy_dinghies(p2.x, p2.z);
    func_80108E30_dizzy_dinghies(&p0, &p1, &p2, &n);
    n.y = 0.0f;
    func_800202FC_main(&n);
    work = obj->data;
    n.x *= 5.0f;
    n.z *= 20.0f;
    if (work->unk90 < n.x) {
        work->unk90 += 1.0f;
    } else if (work->unk90 > n.x) {
        work->unk90 -= 1.0f;
    }
    if (work->unk98 < n.z) {
        work->unk98 += 1.0f;
    } else if (work->unk98 > n.z) {
        work->unk98 -= 1.0f;
    }
    obj->rot.x = work->unk90;
    obj->rot.z = work->unk98;
}

/* After a collision push: undo it if larger than the radius; rumble the pad. */
void func_801090BC_dizzy_dinghies(omObjData* obj, f32 x, f32 z) {
    MgWork* work;
    f32 r;
    f32 d;

    work = obj->data;
    r = work->unk48;
    d = HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame);
    if (r < d || fabs(D_800EBE2C_minigame) > r || fabs(D_800EC5D8_minigame) > r) {
        D_800EBE2C_minigame = D_80109794_dizzy_dinghies.x - x;
        D_800EC5D8_minigame = D_80109794_dizzy_dinghies.z - z;
    }
    if (func_800E6E8C_minigame() == 2) {
        if (D_80109E3C_dizzy_dinghies == 0) {
            if (d > 0.0f) {
                if (d < r / 3.0f) {
                    omVibrate(work->unk59, 2, 3, 10);
                } else {
                    omVibrate(work->unk59, 10, 0, 10);
                }
                D_80109E3C_dizzy_dinghies = 10;
            }
        } else {
            D_80109E3C_dizzy_dinghies--;
        }
    }
}

/* Collide the dinghy moving to (x, y, z) with the course; a hit slows it and pushes it away. Returns the sea height. */
f32 func_80109238_dizzy_dinghies(omObjData* obj, f32 x, f32 y, f32 z) {
    Vec4f p;
    MgWork* work;
    f32 speed;
    f32 d;

    work = obj->data;
    speed = work->unk40;
    p.x = x + sindf(work->unk3C) * speed + D_800EBE2C_minigame;
    p.y = y;
    p.z = z + cosdf(work->unk3C) * speed + D_800EC5D8_minigame;
    p.w = work->unk48;
    work->unk54 = -1;
    work->unk53 = -1;
    p.x += D_800EBE2C_minigame;
    p.z += D_800EC5D8_minigame;
    func_800DD530_minigame(obj, &p, 0.0f);
    d = HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame);
    if (d != 0.0f) {
        if (d > D_80109770_dizzy_dinghies * 0.5f) {
            work->unk40 *= D_80109784_dizzy_dinghies;
        } else {
            work->unk40 *= D_80109780_dizzy_dinghies;
        }
        if (d > D_801097AC_dizzy_dinghies) {
            D_801097A0_dizzy_dinghies.x = D_800EBE2C_minigame;
            D_801097A0_dizzy_dinghies.y = 0.0f;
            D_801097A0_dizzy_dinghies.z = D_800EC5D8_minigame;
            func_800202FC_main(&D_801097A0_dizzy_dinghies);
            D_801097AC_dizzy_dinghies = 16.0f;
        }
    }
    func_801090BC_dizzy_dinghies(obj, x, z);
    return func_80105D90_dizzy_dinghies(p.x, p.z);
}

/* HUD: the speed meter and the player's face (one player). */
void func_80109420_dizzy_dinghies(omObjData* obj) {
    s32 pos[4];
    s16 frame;
    u16 spr;
    s32 i;
    void* data;

    pos[0] = 0x3E;
    pos[1] = 0x20;
    pos[2] = 0x2C;
    pos[3] = 0x1C;
    frame = func_8000B838_main(0x670008);
    func_8000B838_main(0x440014);
    func_8000B838_main(0x440015);
    data = DataRead(0x440013);
    func_80055810_main(data);
    DataClose(data);
    for (i = 0; i <= 0; i++) {
        spr = InitEspriteSlot(frame, 0, 1);
        func_8000BB54_main(spr);
        func_8000BBD4_main(spr, pos[0], pos[1]);
        func_8000BCC8_main(spr, 0xFFFF);
        func_8000BBFC_main(spr, 200);
        spr = InitEspriteSlot(func_8000B838_main((GwPlayer[i].chr + 8) | 0x210000), 0, 1);
        func_8000BB54_main(spr);
        func_8000BBD4_main(spr, pos[2] - 10, pos[3] + 4);
        func_8000BCC8_main(spr, 100);
        func_800E9C20_minigame(1, 5);
        func_800EA0FC_minigame(0, 0.0f, D_80109770_dizzy_dinghies);
        func_800E9F40_minigame(0, 0x2C, 0x1B, 0);
        func_800EA2A8_minigame(0);
    }
    obj->func = NULL;
}

/* Goal: the dinghy has crossed the board's goal plane within 1400 of its first point. */
void func_801095D4_dizzy_dinghies(omObjData* obj) {
    Vec n;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 hit;

    func_80108E30_dizzy_dinghies(&D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][0], &D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][1], &D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][2], &n);
    dx = obj->trans.x - D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][0].x;
    dy = obj->trans.y - D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][0].y;
    dz = obj->trans.z - D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][0].z;
    hit = 1;
    if (!(dx * n.x + dy * n.y + dz * n.z >= 0.0f)) {
        hit = 0;
    }
    if (HuSqrtf(dx * dx + dz * dz) > 1400.0f) {
        hit = 0;
    }
    if (hit == 1 && func_800E6E8C_minigame() == 2) {
        func_800E6F0C_minigame(3);
        D_801097D4_dizzy_dinghies = hit;
        D_80109E40_dizzy_dinghies = HuAudFXPlay(0x425);
    }
}

Vec D_80109740_dizzy_dinghies[3] = {
    { 4500.0f, 0.0f, 7300.0f },
    { 6500.0f, 0.0f, 2300.0f },
    { 5500.0f, 0.0f, 6300.0f }
}; /* start positions per board */
f32 D_80109764_dizzy_dinghies = 180.0f;
f32 D_80109768_dizzy_dinghies = 180.0f; /* start heading */
f32 D_8010976C_dizzy_dinghies = 0.0f;
f32 D_80109770_dizzy_dinghies = 80.0f; /* top speed */
f32 D_80109774_dizzy_dinghies = 1.1f;
f32 D_80109778_dizzy_dinghies = 0.975f;
f32 D_8010977C_dizzy_dinghies = 0.925f;
f32 D_80109780_dizzy_dinghies = 0.925f;
f32 D_80109784_dizzy_dinghies = 0.775f;
Vec D_80109788_dizzy_dinghies = { 0.0f, 0.0f, 0.0f };
Vec D_80109794_dizzy_dinghies = { 0.0f, 0.0f, 0.0f };
Vec D_801097A0_dizzy_dinghies = { 0.0f, 0.0f, 0.0f };
f32 D_801097AC_dizzy_dinghies = 0.0f;
f32 D_801097B0_dizzy_dinghies = 0.1f;
f32 D_801097B4_dizzy_dinghies = 0.0f;
f32 D_801097B8_dizzy_dinghies = 0.2f;
f32 D_801097BC_dizzy_dinghies = 50.0f;
f32 D_801097C0_dizzy_dinghies = 55.0f;
f32 D_801097C4_dizzy_dinghies = 0.0f;
f32 D_801097C8_dizzy_dinghies = 0.13f;
f32 D_801097CC_dizzy_dinghies = 40.0f;
f32 D_801097D0_dizzy_dinghies = 40.0f;
s32 D_801097D4_dizzy_dinghies = 0;
f32 D_801097D8_dizzy_dinghies = 0.0f; /* sea texture scroll */
f32 D_801097DC_dizzy_dinghies = 0.0f;
f32 D_801097E0_dizzy_dinghies = 300.0f;
f32 D_801097E4_dizzy_dinghies = 2.0f;
s32 D_801097E8_dizzy_dinghies = -1;
s32 D_801097EC_dizzy_dinghies = 0; /* board */
Vec D_801097F0_dizzy_dinghies[17] = {
    { 3800.0f, 112.5f, 7200.0f },
    { 5200.0f, 112.5f, 7200.0f },
    { 5200.0f, 112.5f, 4600.0f },
    { 3700.0f, 112.5f, 2700.0f },
    { 4600.0f, 112.5f, -900.0f },
    { 3500.0f, 112.5f, -2800.0f },
    { 5900.0f, 112.5f, -7100.0f },
    { 1600.0f, 112.5f, -8400.0f },
    { -1100.0f, 112.5f, -9100.0f },
    { -3400.0f, 112.5f, -8400.0f },
    { -5200.0f, 112.5f, -9400.0f },
    { -4500.0f, 112.5f, -3600.0f },
    { -3600.0f, 112.5f, -1300.0f },
    { -4700.0f, 112.5f, 600.0f },
    { -3700.0f, 112.5f, 3100.0f },
    { -5200.0f, 112.5f, 7300.0f },
    { -3800.0f, 112.5f, 7200.0f }
};
Vec D_801098BC_dizzy_dinghies[17] = {
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 225.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f }
};
s8 D_80109988_dizzy_dinghies[20] = { 0, 0, 1, 2, 1, 1, 0, 1, 2, 1, 0, 1, 2, 1, 2, 0, 0, -1, 0, 0 };
Vec D_8010999C_dizzy_dinghies[19] = {
    { 5800.0f, 112.5f, 2100.0f },
    { 7200.0f, 112.5f, 2100.0f },
    { 5700.0f, 112.5f, -1000.0f },
    { 7200.0f, 112.5f, -3500.0f },
    { 6600.0f, 112.5f, -7000.0f },
    { 1900.0f, 112.5f, -6200.0f },
    { 4500.0f, 112.5f, -5700.0f },
    { 3200.0f, 112.5f, -900.0f },
    { 1500.0f, 112.5f, 3700.0f },
    { 200.0f, 112.5f, 0.0f },
    { 900.0f, 112.5f, -2100.0f },
    { 1300.0f, 112.5f, -7400.0f },
    { -2700.0f, 112.5f, -9200.0f },
    { -5400.0f, 112.5f, -7900.0f },
    { -3300.0f, 112.5f, -4200.0f },
    { -3500.0f, 112.5f, -2000.0f },
    { -1900.0f, 112.5f, 300.0f },
    { -3200.0f, 112.5f, 5300.0f },
    { -1800.0f, 112.5f, 5200.0f }
};
Vec D_80109A80_dizzy_dinghies[19] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 180.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
};
s8 D_80109B64_dizzy_dinghies[20] = { 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 2, 1, 0, 2, 0, 1, 0, 0, -1 };
Vec D_80109B78_dizzy_dinghies[18] = {
    { 4600.0f, -150.0f, 6200.0f },
    { 6400.0f, -150.0f, 6200.0f },
    { 5300.0f, -150.0f, 1000.0f },
    { 7200.0f, 0.0f, -4000.0f },
    { 3000.0f, -150.0f, -6800.0f },
    { 2100.0f, -150.0f, -1700.0f },
    { 2600.0f, -150.0f, 2300.0f },
    { 2100.0f, 0.0f, 7200.0f },
    { -300.0f, -150.0f, 8200.0f },
    { -2800.0f, -150.0f, 8000.0f },
    { -3600.0f, -150.0f, 4600.0f },
    { -4600.0f, 0.0f, 200.0f },
    { -800.0f, 0.0f, -3800.0f },
    { -1500.0f, -150.0f, -7000.0f },
    { -6200.0f, -150.0f, -3600.0f },
    { -5400.0f, -150.0f, -200.0f },
    { -7500.0f, -150.0f, 3900.0f },
    { -5500.0f, -150.0f, 3900.0f }
};
Vec D_80109C50_dizzy_dinghies[18] = {
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { -40.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { -40.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { -40.0f, 45.0f, 0.0f },
    { -40.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f }
};
s8 D_80109D28_dizzy_dinghies[20] = { 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, -1, 0 };
DdCtrl D_80109D3C_dizzy_dinghies = {
    0, 7, 1, 1, 0, 0, 0, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    75, 65535, 5400, 90, 135, 0,
    { 101.0f, -51.0f, 38.0f },
};
f32 D_80109D70_dizzy_dinghies = -2000.0f;
f32 D_80109D74_dizzy_dinghies = -20.0f;
f32 D_80109D78_dizzy_dinghies = -90.0f;
f32 D_80109D7C_dizzy_dinghies = 20.0f;
f32 D_80109D80_dizzy_dinghies = 5.0f;
s32 D_80109D84_dizzy_dinghies[3][3] = {
    { 0xA0000, 0xA008E, 0xA00A5 },
    { 0xA00C3, 0xA00E7, 0xA00CE },
    { 0xA0086, 0xA0059, 0xA0154 }
};
s32 D_80109DA8_dizzy_dinghies[3][3] = {
    { 0xA0017, 0xA0095, 0xA00B2 },
    { 0xA00BC, 0xA00ED, 0xA00D0 },
    { 0xA0088, 0xA005A, 0xA0154 }
};
char* D_80109DCC_dizzy_dinghies[11] = {
    D_80109F50_dizzy_dinghies,
    D_80109F3C_dizzy_dinghies,
    D_80109F24_dizzy_dinghies,
    D_80109F14_dizzy_dinghies,
    D_80109F04_dizzy_dinghies,
    D_80109EF0_dizzy_dinghies,
    D_80109F3C_dizzy_dinghies,
    D_80109F24_dizzy_dinghies,
    D_80109F50_dizzy_dinghies,
    D_80109F50_dizzy_dinghies,
    D_80109F50_dizzy_dinghies
};
s8 D_80109DF8_dizzy_dinghies[4] = { -1, -1, -1, -1 };
s16 D_80109DFC_dizzy_dinghies = -1;
s16 D_80109DFE_dizzy_dinghies = -1;
s16 D_80109E00_dizzy_dinghies = -1;
s32 D_80109E04_dizzy_dinghies = 0;
s16 D_80109E08_dizzy_dinghies[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
s32 D_80109E30_dizzy_dinghies = 0;
s32 D_80109E34_dizzy_dinghies = 0;
f32 D_80109E38_dizzy_dinghies = 1.0f;
s32 D_80109E3C_dizzy_dinghies = 0;
s32 D_80109E40_dizzy_dinghies = -1;
Vec D_80109E44_dizzy_dinghies[3][3] = {
    { { -4000.0f, 100.0f, 7000.0f }, { -5000.0f, 100.0f, 7000.0f }, { 0.0f, -500.0f, 7000.0f } },
    { { -2000.0f, 100.0f, 5000.0f }, { -3000.0f, 100.0f, 5000.0f }, { 0.0f, -500.0f, 5000.0f } },
    { { -5800.0f, 100.0f, 4000.0f }, { -7200.0f, 100.0f, 4000.0f }, { 0.0f, -500.0f, 4000.0f } }
};

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109EF0_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F04_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F14_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F24_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F3C_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F50_dizzy_dinghies);
