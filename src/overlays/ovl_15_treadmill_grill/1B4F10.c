#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"

// tg A: Treadmill Grill

typedef func_800E1BA8_minigame_ObjData MgWork;

/* omObjData::data of the stage (the framework's ground object) */
typedef struct TgGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} TgGround; /* size 0xB4 */

/* omObjData::data of a grill hazard: the framework's item actor (minigame mgcol.h ColActorWork) */
typedef struct TgGrill {
    /* 0x00 */ u8 unk00[0x20];
    /* 0x20 */ char unk20[0x14];
    /* 0x34 */ f32 unk34; /* height */
    /* 0x38 */ f32 unk38; /* vertical speed */
    /* 0x3C */ f32 unk3C; /* heading */
    /* 0x40 */ f32 unk40; /* speed */
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48; /* radius */
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ u16 unk50;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ s8 unk53;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ char unk55;
    /* 0x56 */ u16 unk56; /* grill index */
    /* 0x58 */ char unk58[0x1C];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 (*unk84[9])();
    /* 0xA8 */ void* unkA8;
} TgGrill; /* size 0xAC */

/* The minigame control block (as All Fired Up's AfCtrl) */
typedef struct TgCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
} TgCtrl; /* size 0x28 */

// main
void Hu3DAnimInit(s32);
void func_80021BE0_main(s32* arg0, s32 arg1);
void func_800142A0_main(s32);
u8 func_8000B638_main(void);
s32 func_80017BB8_main(s16, s16);
s32 func_800202FC_main(Vec* v);
f32 func_800202A8_main(f32 angle);
void func_8001E65C_main(s16 mdl, f32 u, f32 v, s32 w, s32 h);
void* func_8001D33C_main(s16 model, char* name);
void func_80088910_main(f32 (*m)[4], f32 x, f32 y, f32 z); /* guRotateRPYF */
s16 func_80032694_main(HmfData* hmf, u16 anim, s32 arg2, char* name);
s16 HmfAnimRead(HmfData* hmf, s32 dataNum, char* name);
void func_8002FD8C_main(s16 arg0, s16 arg1, const char* arg2, s16 arg3, s16 arg4);

extern f32 D_800D51FC_main;
extern u8 D_800D2008_main; /* frame buffer index */
extern s8 D_800CBB6E_main[];  /* CPU stick x */
extern s16 D_800CDA7C_main[]; /* CPU buttons pressed */
extern s8 D_800D20A1_main[];  /* CPU stick y */
extern u16 D_800D5558_main[]; /* CPU buttons */
extern f32 D_800D5410_main;

extern s32 D_800A178C_main[][6];
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;
extern Vec Center;
extern Vec CRot;
extern f32 CZoom;

// minigame
void func_800E1490_minigame(u16 arg0);
extern f32 D_800EB744_minigame; /* jump speed */
extern f32 D_800EB748_minigame; /* gravity */
extern f32 D_800EB774_minigame; /* max fall speed */
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E3568_minigame(MgWork* work, s32 slot, void* hook);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E13CC_minigame(omObjData* obj, f32 arg1, f32 arg2, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E147C_minigame(omObjData* obj);
void func_800E17F4_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800E5798_minigame(omObjData* obj, s32 arg1);
f32 func_800E2ED4_minigame(f32 x0, f32 z0, f32 x1, f32 z1);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);
extern s16 D_800EB934_minigame;

extern f32 D_800EB73C_minigame;
extern s32 D_800EB77C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s32 D_800EBEB0_minigame[];
extern omObjData* D_800EBE70_minigame[];

// LOCAL

/* What func_8001D33C_main returns (a model's named object) */
typedef struct TgHmfObj {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk18[0x20];
    /* 0x38 */ f32 unk38;
} TgHmfObj;

/* One face group of a model file (src/13F90.c HmfFxGroup) */
typedef struct TgFaceGroup {
    /* 0x00 */ u8 count;
    /* 0x01 */ char unk01;
    /* 0x02 */ s8 unk02; /* 0x7F: an end cap of the belt */
    /* 0x03 */ char unk03;
    /* 0x04 */ s16 vtx[4];
    /* 0x0C */ Vec center;
} TgFaceGroup; /* size 0x18 */

/* HmfData as the belt code reads it (src/13F90.c HmfFxData; N64 offsets, pointer slots typed) */
typedef struct TgHmfData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 unk1A; /* face group count */
    /* 0x1C */ char unk1C[0x24];
    /* 0x40 */ Vtx* unk40;    /* vertex positions */
    /* 0x44 */ Vtx* unk44[3]; /* vertex buffers, one per frame */
    /* 0x50 */ char unk50[0x60];
    /* 0xB0 */ TgFaceGroup* unkB0;
} TgHmfData;

/* A wandering hazard's position (D_8010AFE0_treadmill_grill) */
typedef struct TgPos2 {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
} TgPos2; /* size 8 */

/* A CPU player's remembered stick (D_8010B2E0_treadmill_grill) */
typedef struct TgStick {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
} TgStick; /* size 8 */
void func_801065DC_treadmill_grill(omObjData* obj);
void func_801067A8_treadmill_grill(omObjData* obj);
void func_801084B4_treadmill_grill(omObjData* obj);
void func_801085D8_treadmill_grill(omObjData* obj);
void func_80108730_treadmill_grill(omObjData* obj);
void func_80108888_treadmill_grill(omObjData* obj);
void func_801089E0_treadmill_grill(void);
void func_80108DE0_treadmill_grill(omObjData* obj);
void func_80108FCC_treadmill_grill(omObjData* obj);
f32 func_801093E8_treadmill_grill(s32 i, omObjData* obj);
s32 func_8010AB9C_treadmill_grill(f32 z);
void func_8010980C_treadmill_grill(omObjData* obj);
void func_8010A548_treadmill_grill(void);
void func_8010A6A4_treadmill_grill(void);
void func_8010A754_treadmill_grill(omObjData* obj);
void func_8010A9AC_treadmill_grill(omObjData* obj);
void func_801093E0_treadmill_grill(omObjData* obj, s32 i);
void func_8010ACBC_treadmill_grill(omObjData* obj);

void func_80109108_treadmill_grill(omObjData* obj);

extern f32 D_8010B064_treadmill_grill[13]; /* grill object growth */
extern s32 D_8010B098_treadmill_grill[13]; /* grill object sound played */
void func_80106008_treadmill_grill(omObjData* obj);
void func_801062DC_treadmill_grill(omObjData* obj);
void func_80109FA8_treadmill_grill(omObjData* obj);
void func_80107238_treadmill_grill(omObjData* obj);
void func_80106DA0_treadmill_grill(omObjData* obj, u32 arg1, s32 arg2, u16 arg3, f32 x, f32 y, f32 z);
void func_80107454_treadmill_grill(omObjData* obj, f32* x, f32* y, f32* z);
void func_80108C64_treadmill_grill(omObjData* obj, f32 x, f32 y, f32 z);
void func_80107798_treadmill_grill(omObjData* obj);
s32 func_8010AA2C_treadmill_grill(f32 x, f32 z);
void func_8010AE6C_treadmill_grill(omObjData* obj);

extern s32 D_8010AF80_treadmill_grill; /* next free model in D_8010B310 */
extern u16 D_8010B310_treadmill_grill[16]; /* player models */
extern f32 D_8010AF8C_treadmill_grill[4]; /* belt widths */
extern Vec D_8010AFB0_treadmill_grill[4]; /* start positions; a taken one is zeroed */
extern Vec D_8010B000_treadmill_grill[4]; /* hazard positions */
extern s32 D_8010B030_treadmill_grill[3]; /* hazard inactive */
extern f32 D_8010B0E8_treadmill_grill[4]; /* CPU stick scale per difficulty */
extern s32 D_8010B0F8_treadmill_grill[4]; /* CPU state per player */
extern s32 D_8010B108_treadmill_grill[4]; /* CPU aggression per difficulty */
extern s32 D_8010B118_treadmill_grill[4]; /* CPU state timer per player */
extern TgStick D_8010B2E0_treadmill_grill[4];
extern TgPos2 D_8010AFE0_treadmill_grill[4]; /* hazard x/z */
extern f32 D_8010B1E0_treadmill_grill[4];    /* hazard heading */
extern f32 D_8010B1F0_treadmill_grill[4];    /* hazard turn speed */
extern f32 D_8010B200_treadmill_grill[4];    /* hazard speed */
extern s32 D_8010B210_treadmill_grill[4];    /* hazard wander timer */
extern f32 D_8010B1B4_treadmill_grill[];     /* treadmill belt speeds */
extern f32 D_8010B220_treadmill_grill;       /* shadow pulse angle */
extern f32 D_8010AF88_treadmill_grill;       /* belt width scale */
extern s32 D_8010B19C_treadmill_grill;       /* belt start: -1 not started */
extern f32 D_8010B1A4_treadmill_grill[4];    /* belt texture scroll */
extern s32 D_8010B1D4_treadmill_grill;
extern s32 D_8010B1D8_treadmill_grill;
extern s32 D_8010B1DC_treadmill_grill;
extern s32 D_8010B224_treadmill_grill[4];    /* belt sounds, -1 none */
extern f32 D_8010AF9C_treadmill_grill[4];    /* belt widths last frame */
extern f32 D_8010B17C_treadmill_grill[4];    /* belt speed step */
extern f32 D_8010B1C4_treadmill_grill[4];    /* belt speed step (applied) */
extern f32 D_8010B234_treadmill_grill[6];    /* belt target speeds */
extern s16 D_8010B24C_treadmill_grill[6];    /* belt sound pitches */
extern s32 D_8010B258_treadmill_grill;       /* belt stops */
extern f32 D_8010B25C_treadmill_grill;
extern f32 D_8010B260_treadmill_grill;
extern s32 D_8010B128_treadmill_grill[4][4]; /* landing puff timers per player */
extern f32 D_8010B168_treadmill_grill[4];    /* landing puff scales */
extern s32 D_8010B300_treadmill_grill; /* CPU input: buttons pressed */
extern s32 D_8010B304_treadmill_grill; /* CPU input: buttons */
extern s32 D_8010B308_treadmill_grill; /* CPU input: stick x */
extern s32 D_8010B30C_treadmill_grill; /* CPU input: stick y */
extern s16 D_8010B0D4_treadmill_grill;
extern s32 D_8010B0D8_treadmill_grill[4]; /* landings per player */ /* shared player part model, -1 until loaded */

extern u8 D_8010AF84_treadmill_grill[4]; /* player out */
extern TgCtrl D_8010B03C_treadmill_grill;
extern Vec D_8010B378_treadmill_grill[13]; /* grill positions along the path */
extern Vec D_8010B330_treadmill_grill[6];  /* grill path corners */
extern f32 D_8010AFAC_treadmill_grill;     /* grill path phase */
extern s32 D_8010B178_treadmill_grill;     /* grills created */

void func_801059A0_treadmill_grill(void) {
    u8 cam;

    Hu3DAnimInit(0x32);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(0x1E, 0);
    func_8004A208_main();
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 20.0f, 80.0f, 8000.0f);
    HmfLightDirSet(1, -35.0f, -114.0f, -3.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB77C_minigame = 0;
    func_800E19F0_minigame(0);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 1, 0, -1, func_801065DC_treadmill_grill);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 16, 0, -1, func_801067A8_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_801084B4_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_801085D8_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_80108730_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_80108888_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[(u16)D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    D_800EB73C_minigame = 10.0f;
    WipeCreateIn(0xFF, 16);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010B03C_treadmill_grill);
    D_800EB930_minigame = 0x35;
    D_800EB932_minigame = 0x14;
    HmfLightDirSet(1, 86.0f, 45.0f, 74.0f);
    func_801089E0_treadmill_grill();
}

void func_80106008_treadmill_grill(omObjData* obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80106034_treadmill_grill(omObjData* obj) {
    omObjData* o;
    f32 scale;
    s32 i;

    if (WipeStatGet() != 0) {
        return;
    }
    func_80109108_treadmill_grill(obj);
    for (i = 0; i < (u16)D_800EC1B8_minigame; i++) {
        o = D_800EBE70_minigame[i];
        o->trans.x = D_8010B378_treadmill_grill[i].x;
        o->trans.y = D_8010B378_treadmill_grill[i].y;
        o->trans.z = D_8010B378_treadmill_grill[i].z;
        o->rot.y = atan2df(-o->trans.x, -o->trans.z);
        scale = D_8010B064_treadmill_grill[i] += 0.125f;
        if (scale > 2.3f) {
            scale = 2.3f;
        }
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        o->scale.x = o->scale.y = o->scale.z = scale;
        if (scale > 1.0f && D_8010B098_treadmill_grill[i] == 0) {
            HuAudFXPlay(0x39F);
            D_8010B098_treadmill_grill[i]++;
        }
    }
}

void func_801061E8_treadmill_grill(omObjData* obj) {
    f32 scale;
    s32 i;

    for (i = 0; i < 3; i++) {
        scale = HmfModelData[obj->model[i + 10]].scale.x;
        scale -= 0.1f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelScaleSet(obj->model[i + 10], scale, scale, scale);
        Hu3DModelScaleSet(obj->model[i + 13], scale, scale, scale);
    }
}

void func_801062DC_treadmill_grill(omObjData* obj) {
    MgWork* work;
    omObjData* o;
    s32 last;
    s32 left;
    s32 i;

    last = 0;
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        left = 0;
        for (i = 0; i < D_800EC280_minigame; i++) {
            if (D_8010AF84_treadmill_grill[i] == 0) {
                left++;
                last = i;
            }
        }
        switch (func_800E6F40_minigame()) {
            case 0:
                if (func_800E6E9C_minigame() == 10) {
                    HuAudSeqPlay(0);
                }
                break;
            case 2:
                if (left < 2) {
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (left != 1) {
                    D_8010B03C_treadmill_grill.unk06 = 4;
                } else {
                    D_8010B03C_treadmill_grill.unk18[0] = last;
                    D_8010B03C_treadmill_grill.unk06 = 0;
                }
                break;
            case 4:
                if (D_800EB934_minigame == 1) {
                    if (D_8010B03C_treadmill_grill.unk06 == 4) {
                        for (i = 0; i < 4; i++) {
                            o = D_800EC598_minigame[i];
                            if (D_8010AF84_treadmill_grill[i] == 0) {
                                func_800E5798_minigame(o, 14);
                            }
                        }
                    } else {
                        o = D_800EC598_minigame[last];
                        func_800E5798_minigame(o, 13);
                        work = o->data;
                        GwPlayer[work->unk59].bonusCoin += 10;
                        func_80045ED0_main(D_800A178C_main[GwPlayer[work->unk59].chr][0] | 0x2F);
                    }
                }
                break;
            case 5:
                WipeCreateOut(0, 20);
                obj->func = func_80106008_treadmill_grill;
                break;
        }
        for (i = 0; i < D_800EC280_minigame; i++) {
            ((MgWork*)D_800EC598_minigame[i]->data)->unk60 = CRot.y;
        }
        if (D_800D530C_main == 1) {
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            obj->func = func_80106008_treadmill_grill;
        }
        Center.y = 150.0f;
        Center.z = -350.0f;
    }
}

void func_801065DC_treadmill_grill(omObjData* obj) {
    TgGround* gw;

    obj->model[0] = func_8000B0A0_main(0x360005, 0xA9);
    obj->trans.x = 100.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -1200.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(TgGround), 31000);
    memset(gw, 0, sizeof(TgGround));
    obj->func = func_801062DC_treadmill_grill;
    gw->unk03 = 1;
    CZoom = 3736.0f;
    CRot.x = 319.0f;
    CRot.y = 0.0f;
    Center.x = 0.0f;
    Center.y = 50.0f;
    Center.z = -350.0f;
    func_800E147C_minigame(obj);
    func_800E139C_minigame(obj, 0.0f, -1500.0f, -1500.0f, 1500.0f, 1500.0f);
    func_800E1304_minigame(obj, 0.2f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E131C_minigame(obj, 25.0f);
    gw->unk04 = 0;
    func_8001C2FC_main(obj->model[0], 0x20000, 0x20000);
    func_8001C448_main(obj->model[0]);
    func_8001C954_main(obj->model[0]);
    omSetStatBit(obj, 0xA0);
}

const char D_8010B288_treadmill_grill[] = "c201_000-eyes";

void func_801067A8_treadmill_grill(omObjData* obj) {
    TgGround* gw;

    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    obj->model[0] = func_8000B0A0_main(0x360000, 0xAA9);
    obj->model[1] = func_8000B0A0_main(0x360001, 0xAA9);
    obj->model[2] = func_8000B0A0_main(0x360000, 0xAA9);
    obj->model[3] = func_8000B0A0_main(0x360001, 0xAA9);
    obj->model[4] = func_8000B0A0_main(0x360002, 0xA99);
    obj->model[5] = func_8000B0A0_main(0x360003, 0xA99);
    obj->model[6] = func_8000B0A0_main(0x360003, 0xA99);
    obj->model[7] = func_8000B0A0_main(0x360004, 0xA99);
    obj->model[8] = func_8000B0A0_main(0x360004, 0xA99);
    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    obj->model[9] = func_8000B0A0_main(0x360006, 0x299);
    obj->model[10] = D_8010B310_treadmill_grill[D_8010AF80_treadmill_grill++];
    obj->model[11] = D_8010B310_treadmill_grill[D_8010AF80_treadmill_grill++];
    obj->model[12] = D_8010B310_treadmill_grill[D_8010AF80_treadmill_grill++];
    func_8001C2FC_main(obj->model[10], 0x70000000, 0);
    func_8001C2FC_main(obj->model[11], 0x70000000, 0);
    func_8001C2FC_main(obj->model[12], 0x70000000, 0);
    func_8002FD8C_main(obj->model[10], HmfModelData[obj->model[10]].unk02, D_8010B288_treadmill_grill, 0x4C, 0x46);
    func_8002FD8C_main(obj->model[11], HmfModelData[obj->model[11]].unk02, D_8010B288_treadmill_grill, 0x4C, 0x46);
    func_8002FD8C_main(obj->model[12], HmfModelData[obj->model[12]].unk02, D_8010B288_treadmill_grill, 0x4C, 0x46);
    obj->model[13] = func_8000B0A0_main(0x360007, 0xAC9);
    obj->model[14] = Hu3DModelLink(obj->model[13]);
    obj->model[15] = Hu3DModelLink(obj->model[13]);
    func_8001C2FC_main(obj->model[13], 0x80000000, 0x80000000);
    func_8001C2FC_main(obj->model[14], 0x80000000, 0x80000000);
    func_8001C2FC_main(obj->model[15], 0x80000000, 0x80000000);
    func_8001C448_main(obj->model[13]);
    func_8001C448_main(obj->model[14]);
    func_8001C448_main(obj->model[15]);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->rot.y = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(TgGround), 31000);
    memset(gw, 0, sizeof(TgGround));
    obj->func = func_80109FA8_treadmill_grill;
    gw->unk03 = 1;
    func_800E13CC_minigame(obj, 250.0f, 250.0f, -550.0f, -1050.0f, 550.0f, 150.0f);
    func_8001C2FC_main(obj->model[0], 0x20000, 0x20000);
    func_8001C448_main(obj->model[0]);
    func_8001C954_main(obj->model[0]);
    func_8001C2FC_main(obj->model[1], 0x20000, 0x20000);
    func_8001C448_main(obj->model[1]);
    func_8001C954_main(obj->model[1]);
    func_8001C2FC_main(obj->model[2], 0x20000, 0x20000);
    func_8001C448_main(obj->model[2]);
    func_8001C954_main(obj->model[2]);
    func_8001C2FC_main(obj->model[3], 0x20000, 0x20000);
    func_8001C448_main(obj->model[3]);
    func_8001C954_main(obj->model[3]);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, -300.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, -600.0f);
    Hu3DModelPosSet(obj->model[3], 0.0f, 0.0f, -900.0f);
    func_800E147C_minigame(obj);
    func_800E1304_minigame(obj, 0.3f);
    func_800E131C_minigame(obj, 15.0f);
    func_800E17F4_minigame(obj, 1.0f, 1.0f, 1.0f);
    gw->unk04 = 1;
    Hu3DModelPosSet(obj->model[4], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[5], 480.0f, 150.0f, 165.0f);
    Hu3DModelPosSet(obj->model[6], -480.0f, 150.0f, 165.0f);
    Hu3DModelPosSet(obj->model[7], 430.0f, 220.0f, 155.0f);
    Hu3DModelPosSet(obj->model[8], -430.0f, 220.0f, 155.0f);
    Hu3DModelPosSet(obj->model[9], 0.0f, 0.0f, -450.0f);
    Hu3DModelScaleSet(obj->model[9], 1.1f, 1.0f, 0.8f);
    omSetStatBit(obj, 0xA0);
    func_8010AE6C_treadmill_grill(obj);
}

void func_80106DA0_treadmill_grill(omObjData* obj, u32 arg1, s32 arg2, u16 arg3, f32 x, f32 y, f32 z) {
    MgWork* work;
    s32 chr;
    s32 i;
    s32 attr = 0xA99;

    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    func_800E1BA8_minigame(obj, arg1, arg2, arg3, attr, attr);
    work = obj->data;
    chr = GwPlayer[work->unk59].chr;
    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    obj->model[3] = func_8000B108_main(3, 0x89D);
    obj->model[4] = func_8000B108_main(4, 0x89D);
    obj->model[6] = func_8000B108_main(5, 0x89D);
    obj->model[5] = func_8000B108_main(6, 0x89D);
    obj->model[7] = func_8000B108_main(8, 0x89D);
    obj->model[8] = func_8000B108_main(7, 0x89D);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 5, func_80017BB8_main(chr, 3), 0, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(obj, 8, func_80017BB8_main(chr, 6), 1, 27);
    func_800E5A00_minigame(obj, 17, func_80017BB8_main(chr, 0xE), 1, 15);
    func_800E5A00_minigame(obj, 32, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5A00_minigame(obj, 18, func_80017BB8_main(chr, 0xF), 2, 0);
    func_800E5A00_minigame(obj, 21, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 3, func_80017BB8_main(chr, 0x1D), 1, 0);
    func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(obj, 30, func_80017BB8_main(chr, 0x20), 2, 0);
    func_800E5A00_minigame(obj, 31, func_80017BB8_main(chr, 0x21), 2, 0);
    func_800E5978_minigame(obj, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
    func_800E5978_minigame(obj, 14, func_80017BB8_main(chr, 0x36), 1, 120);
    func_800E5978_minigame(obj, 38, func_80017BB8_main(chr, 0x1A), 1, 0);
    for (i = 10; i < 14; i++) {
        if (D_8010B0D4_treadmill_grill < 0) {
            obj->model[i] = D_8010B0D4_treadmill_grill = func_8000B108_main(0x10014, 0x89D);
        } else {
            obj->model[i] = Hu3DModelLink(D_8010B0D4_treadmill_grill);
        }
    }
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
    work = obj->data;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_800E149C_minigame(obj, 0, 2);
    func_800E149C_minigame(obj, 1, 2);
    func_800E3568_minigame(work, 0, func_80107798_treadmill_grill);
    func_800E3568_minigame(work, 1, func_80107238_treadmill_grill);
    func_800E3568_minigame(work, 20, func_80107454_treadmill_grill);
}

s32 func_80107230_treadmill_grill(void) {
    return 1;
}

// masked 0: retail ORs the two flags into a temporary, this C into hit (raw 1)
#ifdef NON_MATCHING
void func_80107238_treadmill_grill(omObjData* obj) {
    MgWork* work = obj->data;
    s32 player = work->unk59;
    s32 hit = 0;
    f32 dx, dy, dz;
    s32 i;

    if (D_8010AF84_treadmill_grill[player] == 0) {
        for (i = 0; i < 3; i++) {
            dx = obj->trans.x - D_8010B000_treadmill_grill[i].x;
            dy = obj->trans.y - D_8010B000_treadmill_grill[i].y;
            dz = obj->trans.z - D_8010B000_treadmill_grill[i].z;
            if (HuSqrtf(dx * dx + dy * dy + dz * dz) < work->unk48 + 40.0f) {
                hit = 1;
                break;
            }
        }
        hit = (work->unk53 == 0) | hit;
        if (hit) {
            D_8010AF84_treadmill_grill[player] = 1;
            func_800E5798_minigame(obj, 38);
            work->unk50 |= 0x400;
            work->unk38 = -D_800EB744_minigame;
            func_8001C258_main(obj->model[1], 4, 4);
            func_8004AC98_main(0x39D, work->unk59);
            func_8004ACE0_main(0x286, work->unk59);
            omVibrate(work->unk59, 2, 2, 20);
        }
    }
    if (GwPlayer[work->unk59].stat & 1) {
        D_800D5558_main[work->unk57] = D_8010B304_treadmill_grill;
        D_800CDA7C_main[work->unk57] = D_8010B300_treadmill_grill;
        D_800CBB6E_main[work->unk57] = D_8010B308_treadmill_grill;
        D_800D20A1_main[work->unk57] = D_8010B30C_treadmill_grill;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107238_treadmill_grill);
#endif

void func_80107454_treadmill_grill(omObjData* obj, f32* x, f32* y, f32* z) {
    MgWork* work = obj->data;
    omObjData* ground = D_800EC1C0_minigame[1];
    MgWork* gw;
    f32 vy;
    s16 se;

    if (HuSqrtf(*x * *x + *z * *z) > 2000.0f) {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[10], 4, 4);
        func_8001C258_main(obj->model[11], 4, 4);
        func_8001C258_main(obj->model[12], 4, 4);
        func_8001C258_main(obj->model[13], 4, 4);
        return;
    }
    gw = ground->data;
    work->unk3C = atan2df(*x - ground->trans.x, *z - ground->trans.z);
    work->unk40 = 25.0f;
    vy = work->unk38;
    if (vy > D_800EB774_minigame) {
        vy = D_800EB774_minigame;
    }
    *y += vy * vy * ((work->unk38 >= 0.0f) ? -35.0f : 35.0f);
    if (*x > gw->unkA0 && *x < gw->unkA8.f && *z > gw->unkA4 && *z < gw->unkA8.f) {
        if (*y <= gw->unk14) {
            work->unk38 = -D_800EB744_minigame;
            *y = gw->unk14;
            switch (D_8010B0D8_treadmill_grill[work->unk59]) {
                case 0:
                    se = 0x39E;
                    break;
                case 1:
                    se = 0x3A0;
                    break;
                case 2:
                    se = 0x3A1;
                    break;
                case 3:
                    se = 0x3A2;
                    break;
                case 4:
                default:
                    se = 0x3A3;
                    break;
            }
            func_8004AC98_main(se, work->unk59);
            D_8010B0D8_treadmill_grill[work->unk59]++;
        }
    } else if (*y <= 0.0f) {
        work->unk38 = -D_800EB744_minigame;
        *y = 0.0f;
        switch (D_8010B0D8_treadmill_grill[work->unk59]) {
            case 0:
                se = 0x39E;
                break;
            case 1:
                se = 0x3A0;
                break;
            case 2:
                se = 0x3A1;
                break;
            case 3:
                se = 0x3A2;
                break;
            case 4:
            default:
                se = 0x3A3;
                break;
        }
        func_8004AC98_main(se, work->unk59);
        D_8010B0D8_treadmill_grill[work->unk59]++;
    }
    work->unk38 += D_800EB748_minigame * 0.6f;
    func_80108C64_treadmill_grill(obj, *x, *y, *z);
}

/* CPU control hook (slot 0). Logic checked against the asm (branch counts equal; n64nmcmp FIELDS differ only by
   label offset). 31 instructions long: retail keeps bestAng in s5 and re-materialises the -1.0f / 10.0f resets in
   the escape loop, this C hoists them into s6/s7 and so spills the player index (18 extra stack reloads). */
#ifdef NON_MATCHING
void func_80107798_treadmill_grill(omObjData* obj) {
    Vec v;
    omObjData* ground;
    MgWork* gw;
    omObjData* o;
    MgWork* work;
    s32 diff;
    s32 player;
    s32 pad;
    f32 margin;
    f32 x, z;
    f32 px, pz;
    f32 minX, maxX, minZ, maxZ;
    f32 dx, dy, dz;
    f32 d, best, best2;
    f32 r;
    f32 ang, bestAng, angHit, far, farHit;
    s32 dir;
    s32 hz, near;
    s32 i;

    work = obj->data;
    player = work->unk59;
    pad = work->unk57;
    if (func_800E6E8C_minigame() == 3) {
        work->unk3C *= 0.8f;
    }
    if (!(GwPlayer[work->unk59].stat & 1)) {
        return;
    }
    D_8010B304_treadmill_grill = D_800D5558_main[pad];
    D_8010B300_treadmill_grill = (u16)D_800CDA7C_main[pad];
    D_8010B308_treadmill_grill = D_800CBB6E_main[pad];
    D_8010B30C_treadmill_grill = D_800D20A1_main[pad];
    D_800CBB6E_main[pad] = D_800D20A1_main[pad] = 0;
    D_800D5558_main[pad] = 0;
    D_800CDA7C_main[pad] = 0;
    if (D_8010AF84_treadmill_grill[player] == 1) {
        return;
    }
    ground = D_800EC1C0_minigame[1];
    gw = ground->data;
    diff = GwPlayer[work->unk59].cpu_difficulty;
    func_8010AA2C_treadmill_grill(obj->trans.x, obj->trans.z);
    D_800CBB6E_main[pad] = D_800D20A1_main[pad] = 0;
    D_800D5558_main[pad] = 0;
    margin = D_8010AF8C_treadmill_grill[0] / 3.0f;
    if (D_8010B0F8_treadmill_grill[player] == 0x20 && work->unk38 != 1000.0f) {
        D_800CBB6E_main[pad] = D_8010B2E0_treadmill_grill[player].x;
        D_800D20A1_main[pad] = D_8010B2E0_treadmill_grill[player].y;
        D_800CDA7C_main[pad] |= 0x8000;
        for (i = 0; i < 4; i++) {
            if (D_8010AF84_treadmill_grill[i] != 1) {
                if (i != player) {
                    o = D_800EC598_minigame[i];
                    dx = o->trans.x - obj->trans.x;
                    dz = o->trans.z - obj->trans.z;
                    if (HuSqrtf(dx * dx + dz * dz) < 2.0f * work->unk48) {
                        D_800D5558_main[pad] |= 0x2000;
                    }
                }
            }
        }
        return;
    }
    D_8010B118_treadmill_grill[player]++;
    x = obj->trans.x;
    z = obj->trans.z;
    if (D_8010B0F8_treadmill_grill[player] == 4) {
        minX = ground->trans.x + gw->unkA0 + margin;
        maxX = ground->trans.x + gw->unkA8.f - margin;
        minZ = ground->trans.z + gw->unkA4 + 200.0f;
        maxZ = ground->trans.z + gw->unkAC - 200.0f;
    } else if (D_8010B0F8_treadmill_grill[player] == 8) {
        minX = ground->trans.x + gw->unkA0 + margin;
        maxX = ground->trans.x + gw->unkA8.f - margin;
        minZ = ground->trans.z + gw->unkA4 + 300.0f;
        maxZ = ground->trans.z + gw->unkAC - 300.0;
    } else {
        minX = ground->trans.x + gw->unkA0 + 200.0f;
        maxX = ground->trans.x + gw->unkA8.f - 200.0f;
        minZ = ground->trans.z + gw->unkA4 + 200.0f;
        maxZ = ground->trans.z + gw->unkAC - 200.0f;
    }
    dir = 0;
    if (x < minX) {
        D_8010B2E0_treadmill_grill[player].x = D_800CBB6E_main[pad] = D_8010B0E8_treadmill_grill[diff] * 60.0f;
        dir = 4;
    } else if (x > maxX) {
        D_8010B2E0_treadmill_grill[player].x = D_800CBB6E_main[pad] = D_8010B0E8_treadmill_grill[diff] * -60.0f;
        dir = 4;
    }
    if (z < minZ) {
        D_8010B2E0_treadmill_grill[player].y = D_800D20A1_main[pad] = D_8010B0E8_treadmill_grill[diff] * -60.0f;
        dir = 8;
    } else if (z > maxZ) {
        D_8010B2E0_treadmill_grill[player].y = D_800D20A1_main[pad] = D_8010B0E8_treadmill_grill[diff] * 60.0f;
        dir = 8;
    }
    if (dir != 0) {
        D_8010B0F8_treadmill_grill[player] = dir;
        if (D_8010B118_treadmill_grill[player] > 60 && rand8() <= D_8010B108_treadmill_grill[diff] / 4.0f) {
            D_800D5558_main[pad] |= 0x8000;
            D_8010B0F8_treadmill_grill[player] = 0x20;
            D_8010B118_treadmill_grill[player] = 0;
        }
        return;
    }
    best = 2000.0f;
    hz = -1;
    for (i = 0; i < 3; i++) {
        if (D_8010B030_treadmill_grill[i] == 0) {
            dx = obj->trans.x - D_8010B000_treadmill_grill[i].x;
            dy = obj->trans.y - D_8010B000_treadmill_grill[i].y;
            dz = obj->trans.z - D_8010B000_treadmill_grill[i].z;
            d = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (d < best) {
                best = d;
                hz = i;
            }
        }
    }
    if (best < work->unk48 + 40.0f + 200.0f) {
        bestAng = -1.0f;
        angHit = -1.0f;
        far = 10.0f;
        farHit = 10.0f;
        ang = 0.0f;
        do {
            px = sindf(ang) * (work->unk48 + 40.0f + 200.0f) + obj->trans.x;
            pz = cosdf(ang) * (work->unk48 + 40.0f + 200.0f) + obj->trans.z;
            if (func_8010AA2C_treadmill_grill(px, pz) != -1) {
                for (i = 0; i < 3; i++) {
                    dx = px - D_8010B000_treadmill_grill[i].x;
                    dz = pz - D_8010B000_treadmill_grill[i].z;
                    d = HuSqrtf(dx * dx + dz * dz);
                    if (d < work->unk48 + 40.0f + 200.0f) {
                        angHit = -1.0f;
                        farHit = 10.0f;
                        break;
                    }
                    if (d > farHit) {
                        farHit = d;
                        angHit = ang;
                    }
                }
                if (farHit > far) {
                    far = farHit;
                    bestAng = angHit;
                }
            }
            ang += 60.0f;
        } while (ang < 360.0f);
        if (bestAng > 0.0f) {
            v.x = sindf(bestAng);
            v.z = cosdf(bestAng);
        } else {
            v.x = obj->trans.x - D_8010B000_treadmill_grill[hz].x;
            v.y = obj->trans.y - D_8010B000_treadmill_grill[hz].y;
            v.z = obj->trans.z - D_8010B000_treadmill_grill[hz].z;
            func_800202FC_main(&v);
        }
        D_800CBB6E_main[pad] = v.x * 60.0f * D_8010B0E8_treadmill_grill[diff];
        D_800D20A1_main[pad] = -v.z * 60.0f * D_8010B0E8_treadmill_grill[diff];
        D_8010B0F8_treadmill_grill[player] = 2;
        return;
    }
    near = -1;
    best2 = 2000.0f;
    if (D_8010B108_treadmill_grill[diff] >= rand8()) {
        for (i = 0; i < 4; i++) {
            if (D_8010AF84_treadmill_grill[i] != 1) {
                if (i != player) {
                    o = D_800EC598_minigame[i];
                    dx = obj->trans.x - o->trans.x;
                    dy = obj->trans.y - o->trans.y;
                    dz = obj->trans.z - o->trans.z;
                    d = HuSqrtf(dx * dx + dy * dy + dz * dz);
                    if (d < best2) {
                        best2 = d;
                        near = i;
                    }
                    if (d < 2.0f * work->unk48 + 80.0f
                        && (ang = work->unk3C, func_800E2ED4_minigame(dx, dz, sindf(ang), cosdf(ang)) < -0.8f)) {
                        D_800D5558_main[pad] = 0x4000;
                        D_8010B0F8_treadmill_grill[player] = 0x10;
                        break;
                    }
                }
            }
        }
        if (near != -1 && D_800D5558_main[pad] == 0) {
            o = D_800EC598_minigame[near];
            v.x = obj->trans.x - o->trans.x;
            v.y = 0.0f;
            v.z = obj->trans.z - o->trans.z;
            func_800202FC_main(&v);
            D_800CBB6E_main[pad] = -v.x * 60.0f * D_8010B0E8_treadmill_grill[diff];
            D_800D20A1_main[pad] = v.z * 60.0f * D_8010B0E8_treadmill_grill[diff];
            D_8010B0F8_treadmill_grill[player] = 0x10;
        }
    }
    switch (D_8010B0F8_treadmill_grill[player]) {
        case 4:
        case 8:
            if (D_8010B118_treadmill_grill[player] > 60 && rand8() <= D_8010B108_treadmill_grill[diff] / 4.0f) {
                D_800D5558_main[pad] |= 0x8000;
                D_8010B0F8_treadmill_grill[player] = 0x20;
                D_8010B118_treadmill_grill[player] = 0;
            }
            break;
        default:
            D_8010B2E0_treadmill_grill[player].x = 0;
            D_8010B2E0_treadmill_grill[player].y = 0;
            break;
    }
    D_8010B118_treadmill_grill[player]++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107798_treadmill_grill);
#endif

/* Player objects 0..3. Masked 12 each: retail loads the two D_800A178C_main arguments before it stores the
   stack arguments; this C loads them after (no other difference). */
#ifdef NON_MATCHING
void func_801084B4_treadmill_grill(omObjData* obj) {
    MgWork* work;
    s32 i;
    s32 chr;

    chr = GwPlayer[0].chr;
    func_80106DA0_treadmill_grill(obj, D_800A178C_main[chr][0], D_800A178C_main[chr][1], 0, 0.0f, 250.0f, -500.0f);
    work = obj->data;
    i = rand8() & 3;
    obj->trans.x = D_8010AFB0_treadmill_grill[i].x;
    obj->trans.y = D_8010AFB0_treadmill_grill[i].y;
    obj->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    work->unk3C = i * 90.0f + 135.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801084B4_treadmill_grill);
#endif

#ifdef NON_MATCHING
void func_801085D8_treadmill_grill(omObjData* obj) {
    MgWork* work;
    s32 i;
    s32 chr;

    chr = GwPlayer[1].chr;
    func_80106DA0_treadmill_grill(obj, D_800A178C_main[chr][0], D_800A178C_main[chr][1], 1, 0.0f, 250.0f, -300.0f);
    work = obj->data;
    do {
        i = rand8() & 3;
    } while (D_8010AFB0_treadmill_grill[i].x == 0.0f);
    obj->trans.x = D_8010AFB0_treadmill_grill[i].x;
    obj->trans.y = D_8010AFB0_treadmill_grill[i].y;
    obj->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    work->unk3C = i * 90.0f + 135.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801085D8_treadmill_grill);
#endif

#ifdef NON_MATCHING
void func_80108730_treadmill_grill(omObjData* obj) {
    MgWork* work;
    s32 i;
    s32 chr;

    chr = GwPlayer[2].chr;
    func_80106DA0_treadmill_grill(obj, D_800A178C_main[chr][0], D_800A178C_main[chr][1], 2, 0.0f, 250.0f, -300.0f);
    work = obj->data;
    do {
        i = rand8() & 3;
    } while (D_8010AFB0_treadmill_grill[i].x == 0.0f);
    obj->trans.x = D_8010AFB0_treadmill_grill[i].x;
    obj->trans.y = D_8010AFB0_treadmill_grill[i].y;
    obj->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    work->unk3C = i * 90.0f + 135.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108730_treadmill_grill);
#endif

#ifdef NON_MATCHING
void func_80108888_treadmill_grill(omObjData* obj) {
    MgWork* work;
    s32 i;
    s32 chr;

    chr = GwPlayer[3].chr;
    func_80106DA0_treadmill_grill(obj, D_800A178C_main[chr][0], D_800A178C_main[chr][1], 3, 0.0f, 250.0f, -300.0f);
    work = obj->data;
    do {
        i = rand8() & 3;
    } while (D_8010AFB0_treadmill_grill[i].x == 0.0f);
    obj->trans.x = D_8010AFB0_treadmill_grill[i].x;
    obj->trans.y = D_8010AFB0_treadmill_grill[i].y;
    obj->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    work->unk3C = i * 90.0f + 135.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108888_treadmill_grill);
#endif

/* Loads the 16 player-skin models (D_8010B310). Masked 4: retail keeps the model number unextended in a
   second register for the store; logic checked. */
#ifdef NON_MATCHING
void func_801089E0_treadmill_grill(void) {
    void* data;
    s16 anim;
    u16 mdl;
    s32 i;

    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    data = DataRead(0xA008A);
    anim = HmfAnimRead(HmfModelData[(s16)(D_8010B310_treadmill_grill[0] = Hu3DModelCreate(data, 0xAC1))].hmf, 0xA008C,
                       "c201n_00_DEF");
    func_8001C448_main(D_8010B310_treadmill_grill[0]);
    func_8001C514_main(D_8010B310_treadmill_grill[0]);
    for (i = 1; i < 3; i++) {
        mdl = Hu3DModelCreate(data, 0xAC1);
        func_80032694_main(HmfModelData[(s16)mdl].hmf, anim, 0, "c201n_00_DEF");
        func_8001C448_main(mdl);
        func_8001C514_main(mdl);
        D_8010B310_treadmill_grill[i] = mdl;
    }
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA008A);
    anim = HmfAnimRead(HmfModelData[(s16)(D_8010B310_treadmill_grill[i] = Hu3DModelCreate(data, 0xAC1))].hmf, 0xA008D,
                       "c201n_00_DEF");
    func_8001C448_main(D_8010B310_treadmill_grill[i]);
    func_8001C514_main(D_8010B310_treadmill_grill[i]);
    for (i++; i < 16; i++) {
        mdl = Hu3DModelCreate(data, 0xAC1);
        func_80032694_main(HmfModelData[(s16)mdl].hmf, anim, 0, "c201n_00_DEF");
        func_8001C448_main(mdl);
        func_8001C514_main(mdl);
        D_8010B310_treadmill_grill[i] = mdl;
    }
    HuMemMemoryFreePerm(data);
    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801089E0_treadmill_grill);
#endif

/* Landing puffs (All Fired Up func_80108958 twin). Masked 3: retail sets i = 0 after the row load; logic checked. */
#ifdef NON_MATCHING
void func_80108C64_treadmill_grill(omObjData* obj, f32 x, f32 y, f32 z) {
    s32* timer;
    s32 i;
    f32 sc;

    timer = D_8010B128_treadmill_grill[((MgWork*)obj->data)->unk59];
    for (i = 0; i < 4; i++) {
        if (timer[i] >= 0) {
            if (timer[i] == 0) {
                Hu3DModelPosSet(obj->model[i + 10], x, y + 30.0f, z);
                func_8001C258_main(obj->model[i + 10], 4, 0);
            }
            if (timer[i] < 8) {
                sc = D_8010B168_treadmill_grill[timer[i] / 2];
                Hu3DModelScaleSet(obj->model[i + 10], sc, sc, 1.0f);
            }
            if (timer[i] >= 8) {
                timer[i] = -1;
            }
        }
        timer[i]++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80108C64_treadmill_grill);
#endif

void func_80108DE0_treadmill_grill(omObjData* obj) {
    TgGrill* g;
    s32 i;

    obj->data = HuMemAllocTag(sizeof(TgGrill), 31000);
    memset(obj->data, 0, sizeof(TgGrill));
    g = obj->data;
    obj->model[1] = 0;
    obj->model[0] = D_8010B310_treadmill_grill[D_8010AF80_treadmill_grill++];
    obj->func = func_80108FCC_treadmill_grill;
    g->unk44 = 0.3f;
    g->unk48 = 60.0f;
    g->unk34 = 150.0f;
    g->unk3C = 0.0f;
    g->unk78 = 0;
    g->unk52 = 3;
    g->unk7C = 0;
    g->unk50 = 0x20;
    g->unk40 = 0.0f;
    g->unk74 = 0.8f;
    g->unk54 = 1;
    for (i = 0; i < 9; i++) {
        g->unk84[i] = NULL;
    }
    g->unk56 = D_8010B178_treadmill_grill;
    func_800E149C_minigame(obj, 0, 2);
    func_800E149C_minigame(obj, 1, 2);
    obj->trans.x = sindf(D_8010B178_treadmill_grill * 36.0f) * 450.0f;
    obj->trans.y = 500.0f;
    obj->trans.z = cosdf(D_8010B178_treadmill_grill * 36.0f) * 450.0f + -512.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.0f;
    D_8010B178_treadmill_grill++;
}

void func_80108FCC_treadmill_grill(omObjData* obj) {
    omObjData* ground = D_800EC1C0_minigame[1];
    TgGrill* g = obj->data;
    f32 sc;

    if (func_800E6E8C_minigame() == 2) {
        obj->trans.x = D_8010B378_treadmill_grill[g->unk56].x;
        obj->trans.y = D_8010B378_treadmill_grill[g->unk56].y;
        obj->trans.z = D_8010B378_treadmill_grill[g->unk56].z;
        obj->rot.y = atan2df(ground->trans.x - obj->trans.x, ground->trans.z - obj->trans.z);
        sc = sindf(D_8010AFAC_treadmill_grill * 5.0f + g->unk56 * 30) * 0.3f + 2.2f;
        obj->scale.x = obj->scale.y = obj->scale.z = sc;
    }
}

/* Grill path: corners round the treadmill, then grill positions spaced along it. Masked 0 (raw 6): retail
   divides into the spacing register from a temporary, this C ties the numerator to it. */
#ifdef NON_MATCHING
void func_80109108_treadmill_grill(omObjData* obj) {
    Vec dir;
    f32 step;
    f32 len;
    f32 t;
    f32 x0;
    f32 w;
    s32 n = 0;
    s32 i;

    step = (2.0f * (D_8010AF8C_treadmill_grill[0] + 600.0f) + 2000.0f) / (f32)((u16)D_800EC1B8_minigame - 1);
    D_8010B330_treadmill_grill[0].x = x0 = sindf(D_8010AFAC_treadmill_grill) * (step / 2.0f) + obj->trans.x + 0.0f;
    D_8010B330_treadmill_grill[0].y = 50.0f;
    D_8010B330_treadmill_grill[0].z = 350.0f;
    w = D_8010AF8C_treadmill_grill[0] / 2.0f;
    D_8010B330_treadmill_grill[1].x = w + obj->trans.x + 180.0f;
    D_8010B330_treadmill_grill[1].y = 50.0f;
    D_8010B330_treadmill_grill[1].z = 350.0f;
    D_8010B330_treadmill_grill[2].x = w + obj->trans.x + 180.0f;
    D_8010B330_treadmill_grill[2].y = 50.0f;
    D_8010B330_treadmill_grill[2].z = -1150.0f;
    D_8010B330_treadmill_grill[3].x = obj->trans.x - w - 180.0f;
    D_8010B330_treadmill_grill[3].y = 50.0f;
    D_8010B330_treadmill_grill[3].z = -1150.0f;
    D_8010B330_treadmill_grill[4].x = obj->trans.x - w - 180.0f;
    D_8010B330_treadmill_grill[4].y = 50.0f;
    D_8010B330_treadmill_grill[4].z = 350.0f;
    D_8010B330_treadmill_grill[5].x = x0;
    D_8010B330_treadmill_grill[5].y = 50.0f;
    D_8010B330_treadmill_grill[5].z = 350.0f;
    t = 0.0f;
    for (i = 0; i < 5; i++) {
        dir.x = D_8010B330_treadmill_grill[i + 1].x - D_8010B330_treadmill_grill[i].x;
        dir.y = D_8010B330_treadmill_grill[i + 1].y - D_8010B330_treadmill_grill[i].y;
        dir.z = D_8010B330_treadmill_grill[i + 1].z - D_8010B330_treadmill_grill[i].z;
        len = HuSqrtf(dir.x * dir.x + dir.z * dir.z);
        func_800202FC_main(&dir);
        do {
            D_8010B378_treadmill_grill[n].x = t * dir.x + D_8010B330_treadmill_grill[i].x;
            D_8010B378_treadmill_grill[n].y = t * dir.y + D_8010B330_treadmill_grill[i].y;
            D_8010B378_treadmill_grill[n].z = t * dir.z + D_8010B330_treadmill_grill[i].z;
            t += step;
            n++;
        } while (t < len);
        t -= len;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80109108_treadmill_grill);
#endif

void func_801093E0_treadmill_grill(omObjData* obj, s32 i) {
}

/* Moves wandering hazard i; returns its heading. One instruction long: the assembler puts a nop after the
   cosdf call that retail lacks (everything else matches). */
#ifdef NON_MATCHING
f32 func_801093E8_treadmill_grill(s32 i, omObjData* obj) {
    f32 a;
    f32 sp;

    if (D_8010AFE0_treadmill_grill[i].z < 0.0f && D_8010AFE0_treadmill_grill[i].z > -900.0f) {
        if (D_8010B210_treadmill_grill[i] == 0) {
            D_8010B1F0_treadmill_grill[i] = rand8() / 100.0f;
            D_8010B200_treadmill_grill[i] = rand8() / 100.0f + 1.0f;
            D_8010B210_treadmill_grill[i] = (rand8() >> 3) + 90;
        }
        if (D_8010B1F0_treadmill_grill[i] > 0.0f) {
            D_8010B1F0_treadmill_grill[i] -= 0.05f;
        }
        D_8010B210_treadmill_grill[i]--;
    } else if (D_8010AFE0_treadmill_grill[i].z >= 0.0f) {
        if (D_8010B1E0_treadmill_grill[i] > 210.0f) {
            D_8010B1F0_treadmill_grill[i] = -2.0f;
            D_8010B200_treadmill_grill[i] -= 0.2f;
            if (D_8010B200_treadmill_grill[i] < 0.0f) {
                D_8010B200_treadmill_grill[i] = 0.0f;
            }
        } else if (D_8010B1E0_treadmill_grill[i] < 150.0f) {
            D_8010B1F0_treadmill_grill[i] = 2.0f;
            D_8010B200_treadmill_grill[i] -= 0.2f;
            if (D_8010B200_treadmill_grill[i] < 0.0f) {
                D_8010B200_treadmill_grill[i] = 0.0f;
            }
        } else {
            D_8010B1F0_treadmill_grill[i] = 0.0f;
            D_8010B200_treadmill_grill[i] = 2.0f;
        }
    } else if (D_8010AFE0_treadmill_grill[i].z <= -900.0f) {
        if (D_8010B1E0_treadmill_grill[i] < 330.0f && D_8010B1E0_treadmill_grill[i] > 180.0f) {
            D_8010B1F0_treadmill_grill[i] = 2.0f;
            D_8010B200_treadmill_grill[i] -= 0.2f;
            if (D_8010B200_treadmill_grill[i] < 0.0f) {
                D_8010B200_treadmill_grill[i] = 0.0f;
            }
        } else if (D_8010B1E0_treadmill_grill[i] > 30.0f && D_8010B1E0_treadmill_grill[i] < 180.0f) {
            D_8010B1F0_treadmill_grill[i] = -2.0f;
            D_8010B200_treadmill_grill[i] -= 0.2f;
            if (D_8010B200_treadmill_grill[i] < 0.0f) {
                D_8010B200_treadmill_grill[i] = 0.0f;
            }
        } else {
            D_8010B1F0_treadmill_grill[i] = 0.0f;
            D_8010B200_treadmill_grill[i] = 2.0f;
        }
    }
    D_8010B1E0_treadmill_grill[i] += D_8010B1F0_treadmill_grill[i];
    a = D_8010B1E0_treadmill_grill[i] = func_800202A8_main(D_8010B1E0_treadmill_grill[i]);
    sp = D_8010B200_treadmill_grill[i];
    D_8010AFE0_treadmill_grill[i].x += sindf(a) * sp;
    D_8010AFE0_treadmill_grill[i].z += cosdf(a) * sp;
    return a;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801093E8_treadmill_grill);
#endif

/* Moves the three grill-riding hazards along the belt loop (D_8010AFE0[i].x is the distance along it) and
   places their models. Logic checked block by block; retail keeps obj and 50.0f in other registers (masked ~114). */
#ifdef NON_MATCHING
void func_8010980C_treadmill_grill(omObjData* obj) {
    TgHmfObj* part;
    f32 heading;
    f32 len;
    f32 p;
    f32 e;
    f32 y, ox, rz, sc;
    f32 sc2;
    s16 mdl;
    s32 i;

    if (func_800E6E8C_minigame() == 2 && func_800E6E9C_minigame() < 150) {
        return;
    }
    for (i = 0; i < 3; i++) {
        heading = func_801093E8_treadmill_grill(i, obj);
        len = D_8010AF8C_treadmill_grill[i] + 100.0f + 200.0f + 200.0f;
        p = D_8010AFE0_treadmill_grill[i].x -=
            D_8010B1B4_treadmill_grill[func_8010AB9C_treadmill_grill(D_8010AFE0_treadmill_grill[i].z)] * 3.125f;
        if (p > len) {
            D_8010AFE0_treadmill_grill[i].x = p - len;
        }
        if (D_8010AFE0_treadmill_grill[i].x < 0.0f) {
            D_8010AFE0_treadmill_grill[i].x = len + D_8010AFE0_treadmill_grill[i].x;
        }
        if (D_8010AFE0_treadmill_grill[i].x < 100.0f) {
            goto off;
        }
        if (D_8010AFE0_treadmill_grill[i].x <= 200.0f) {
            y = D_8010AFE0_treadmill_grill[i].x;
            ox = -(D_8010AF8C_treadmill_grill[i] + 100.0f) / 2.0f;
            rz = 90.0f;
            sc = (y - 100.0f) / 100.0f;
            D_8010B030_treadmill_grill[i] = 1;
        } else if (D_8010AFE0_treadmill_grill[i].x <= 250.0f) {
            rz = 90.0f - (D_8010AFE0_treadmill_grill[i].x - 200.0f) / 50.0f * 90.0f;
            y = 250.0f - sindf(rz) * 50.0f;
            ox = -(D_8010AF8C_treadmill_grill[i] / 2.0f) + sindf(-rz) * 50.0f;
            sc = (D_8010AFE0_treadmill_grill[i].x - 200.0f) / 100.0f + 1.0f;
            D_8010B030_treadmill_grill[i] = 0;
        } else if (D_8010AFE0_treadmill_grill[i].x < D_8010AF8C_treadmill_grill[i] + 250.0f) {
            ox = -(D_8010AF8C_treadmill_grill[i] + 100.0f) / 2.0f + D_8010AFE0_treadmill_grill[i].x - 250.0f;
            y = 250.0f;
            rz = 0.0f;
            sc = 1.5f;
            D_8010B030_treadmill_grill[i] = 0;
        } else if (D_8010AFE0_treadmill_grill[i].x < (e = D_8010AF8C_treadmill_grill[i] + 250.0f) + 50.0f) {
            rz = -((D_8010AFE0_treadmill_grill[i].x - e) / 50.0f) * 90.0f;
            y = sindf(rz) * 50.0f + 250.0f;
            ox = D_8010AF8C_treadmill_grill[i] / 2.0f + sindf(-rz) * 50.0f;
            sc = (D_8010AF8C_treadmill_grill[i] + 250.0f + 50.0f - D_8010AFE0_treadmill_grill[i].x) / 100.0f + 1.0f;
            D_8010B030_treadmill_grill[i] = 0;
        } else if (D_8010AFE0_treadmill_grill[i].x < (e = D_8010AF8C_treadmill_grill[i] + 250.0f + 50.0f + 100.0f)) {
            y = e - D_8010AFE0_treadmill_grill[i].x + 100.0f;
            ox = (D_8010AF8C_treadmill_grill[i] + 100.0f) / 2.0f;
            rz = -90.0f;
            sc = (e - D_8010AFE0_treadmill_grill[i].x) / 100.0f;
            D_8010B030_treadmill_grill[i] = 1;
        } else {
        off:
            y = 0.0f;
            ox = 0.0f;
            rz = 0.0f;
            sc = 1.0f;
            D_8010B030_treadmill_grill[i] = 1;
        }
        if (y != 0.0f) {
            mdl = obj->model[i + 10];
            func_8001C258_main(mdl, 4, 0);
            Hu3DModelPosSet(mdl, ox + obj->trans.x, y, D_8010AFE0_treadmill_grill[i].z);
            Hu3DModelRotSet(mdl, CRot.x, 0.0f, 0.0f);
            Hu3DModelScaleSet(mdl, sc, sc, sc);
            func_80088910_main((f32(*)[4])HmfModelData[mdl].mtx, 0.0f, 0.0f, rz);
            part = func_8001D33C_main(mdl, (char*)D_8010B288_treadmill_grill);
            part->unk38 = heading;
            part->unk14 = heading;
            D_8010B220_treadmill_grill += 5.0f;
            D_8010B220_treadmill_grill = func_800202A8_main(D_8010B220_treadmill_grill);
            sc2 = sc * 0.5f + sindf(D_8010B220_treadmill_grill) * 0.3f;
            mdl = obj->model[i + 13];
            func_8001C258_main(mdl, 4, 0);
            Hu3DModelPosSet(mdl, ox + obj->trans.x, y - 3.0f, D_8010AFE0_treadmill_grill[i].z);
            Hu3DModelScaleSet(mdl, sc2, sc2, sc2);
            func_80088910_main((f32(*)[4])HmfModelData[mdl].mtx, 0.0f, 0.0f, rz);
        } else {
            func_8001C258_main(obj->model[i + 10], 4, 4);
            func_8001C258_main(obj->model[i + 13], 4, 4);
        }
        D_8010B000_treadmill_grill[i].x = ox + obj->trans.x;
        D_8010B000_treadmill_grill[i].y = y;
        D_8010B000_treadmill_grill[i].z = D_8010AFE0_treadmill_grill[i].z;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010980C_treadmill_grill);
#endif

void func_80109FA8_treadmill_grill(omObjData* obj) {
    MgWork* work;
    omObjData* o;
    s32 lane;
    s32 i;

    func_8001E65C_main(obj->model[0], D_8010B1A4_treadmill_grill[0], 0.0f, 0x20, 0x40);
    func_8001E65C_main(obj->model[1], D_8010B1A4_treadmill_grill[1], 0.0f, 0x20, 0x40);
    func_8001E65C_main(obj->model[2], D_8010B1A4_treadmill_grill[2], 0.0f, 0x20, 0x40);
    func_8001E65C_main(obj->model[3], D_8010B1A4_treadmill_grill[3], 0.0f, 0x20, 0x40);
    func_8010ACBC_treadmill_grill(obj);
    if (func_80049F98_main() + D_800D6A90_main != 0) {
        return;
    }
    if (func_800E6E8C_minigame() == 0) {
        func_80106034_treadmill_grill(obj);
    } else if (func_800E6E8C_minigame() == 2) {
        Hu3DModelRotSet(obj->model[5], 0.0f, 0.0f, D_8010B1A4_treadmill_grill[0] * 1.2f);
        Hu3DModelRotSet(obj->model[6], 0.0f, 0.0f, D_8010B1A4_treadmill_grill[0] * 1.2f);
        D_8010B1A4_treadmill_grill[0] += D_8010B1B4_treadmill_grill[0];
        D_8010B1A4_treadmill_grill[1] += D_8010B1B4_treadmill_grill[1];
        D_8010B1A4_treadmill_grill[2] += D_8010B1B4_treadmill_grill[2];
        D_8010B1A4_treadmill_grill[3] += D_8010B1B4_treadmill_grill[3];
        func_8010980C_treadmill_grill(obj);
        if (D_8010B19C_treadmill_grill == -1) {
            func_8010A548_treadmill_grill();
            D_8010B19C_treadmill_grill = 0;
            D_8010B224_treadmill_grill[0] = HuAudFXPlay(0x397);
            D_8010B224_treadmill_grill[1] = HuAudFXPlay(0x398);
            D_8010B224_treadmill_grill[2] = HuAudFXPlay(0x399);
            D_8010B224_treadmill_grill[3] = HuAudFXPlay(0x39A);
        }
        if (D_8010B19C_treadmill_grill == 0) {
            if (D_8010B1D8_treadmill_grill != 0) {
                func_8010A9AC_treadmill_grill(obj);
                D_8010B1D8_treadmill_grill--;
            }
        } else {
            D_8010B19C_treadmill_grill--;
            if (D_8010B1D8_treadmill_grill != 0) {
                func_8010A9AC_treadmill_grill(obj);
                D_8010B1D8_treadmill_grill--;
            } else {
                func_8010A754_treadmill_grill(obj);
            }
        }
        if (D_8010B19C_treadmill_grill == 0) {
            if (++D_8010B1D4_treadmill_grill == 90) {
                func_8010A548_treadmill_grill();
            }
            if (++D_8010B1DC_treadmill_grill == 300) {
                func_8010A6A4_treadmill_grill();
                for (i = 0; i < 4; i++) {
                    work = D_800EC598_minigame[i]->data;
                    if (D_8010AF84_treadmill_grill[i] == 0) {
                        omVibrate(work->unk59, 20, 0, 20);
                    }
                }
            }
        }
        for (i = 0; i < D_800EC280_minigame; i++) {
            o = D_800EC598_minigame[i];
            work = o->data;
            if (D_8010AF84_treadmill_grill[i] == 0 && work->unk53 == 1) {
                lane = func_8010AA2C_treadmill_grill(o->trans.x, o->trans.z);
                if (lane != -1) {
                    if (lane >= -1) {
                        if (lane < 4) {
                            o->trans.x -= D_8010B1B4_treadmill_grill[lane] * 3.125f;
                        }
                    }
                }
            }
        }
        D_8010AFAC_treadmill_grill = func_800202A8_main(D_8010AFAC_treadmill_grill + 3.0f);
        func_80109108_treadmill_grill(obj);
    } else if (func_800E6E8C_minigame() == 3) {
        if (D_8010B224_treadmill_grill[0] != -1) {
            HuAudFXStop((s16)D_8010B224_treadmill_grill[0]);
            D_8010B224_treadmill_grill[0] = -1;
        }
        if (D_8010B224_treadmill_grill[1] != -1) {
            HuAudFXStop((s16)D_8010B224_treadmill_grill[1]);
            D_8010B224_treadmill_grill[1] = -1;
        }
        if (D_8010B224_treadmill_grill[2] != -1) {
            HuAudFXStop((s16)D_8010B224_treadmill_grill[2]);
            D_8010B224_treadmill_grill[2] = -1;
        }
        if (D_8010B224_treadmill_grill[3] != -1) {
            HuAudFXStop((s16)D_8010B224_treadmill_grill[3]);
            D_8010B224_treadmill_grill[3] = -1;
        }
        func_801061E8_treadmill_grill(obj);
    }
    D_8010AF88_treadmill_grill = D_8010AF8C_treadmill_grill[0] / 1100.0f;
    Hu3DModelScaleSet(obj->model[4], D_8010AF88_treadmill_grill, 1.0f, 1.0f);
    Hu3DModelPosSet(obj->model[9], 0.0f, 0.0f, -450.0f);
    Hu3DModelScaleSet(obj->model[9], D_8010AF88_treadmill_grill + 0.1f, 1.0f, 0.8f);
}

void func_8010A548_treadmill_grill(void) {
    f32* spd;
    f32 target;
    s32 r;
    s32 i;

    HuAudFXPlay(0x39C);
    for (i = 0; i < 4; i++) {
        spd = &D_8010B1B4_treadmill_grill[i];
        do {
            r = (u8)(rand8() % 6);
            target = D_8010B234_treadmill_grill[r];
        } while (*spd == target * 0.5f);
        D_8010B17C_treadmill_grill[i] = (target - D_8010B1B4_treadmill_grill[i]) / 20.0f;
        D_8010B1C4_treadmill_grill[i] = (target - D_8010B1B4_treadmill_grill[i]) / 20.0f;
        if (D_8010B224_treadmill_grill[i] >= 0) {
            HuAudFXPitchSet((s16)D_8010B224_treadmill_grill[i], D_8010B24C_treadmill_grill[r]);
        }
    }
    D_8010B1D8_treadmill_grill = 20;
    D_8010B1D4_treadmill_grill = 0;
}

void func_8010A6A4_treadmill_grill(void) {
    s32 i;

    if (D_8010B258_treadmill_grill++ < 2) {
        D_8010B19C_treadmill_grill = 50;
        D_8010B1DC_treadmill_grill = 0;
        for (i = 0; i < 4; i++) {
            D_8010B17C_treadmill_grill[i] = -D_8010B1B4_treadmill_grill[i] / 20.0f;
            D_8010B1C4_treadmill_grill[i] = -D_8010B1B4_treadmill_grill[i] / 20.0f;
        }
        D_8010B1D8_treadmill_grill = 20;
        D_8010B1D4_treadmill_grill = 0;
    }
}

void func_8010A754_treadmill_grill(omObjData* obj) {
    f32 minX, maxX;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8010AF9C_treadmill_grill[i] = D_8010AF8C_treadmill_grill[i];
        D_8010AF8C_treadmill_grill[i] -= 10.0f;
    }
    func_8010AE6C_treadmill_grill(obj);
    if (D_8010B19C_treadmill_grill == 0) {
        func_8010A548_treadmill_grill();
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, -300.0f);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, -600.0f);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, -900.0f);
    D_8010B25C_treadmill_grill += 5.5f;
    D_8010B260_treadmill_grill -= 5.5f;
    Hu3DModelPosSet(obj->model[4], obj->trans.x, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[5], obj->trans.x + D_8010B25C_treadmill_grill, 150.0f, 165.0f);
    Hu3DModelPosSet(obj->model[6], obj->trans.x + D_8010B260_treadmill_grill, 150.0f, 165.0f);
    Hu3DModelPosSet(obj->model[7], obj->trans.x + D_8010B25C_treadmill_grill + 50.0f, 220.0f, 155.0f);
    Hu3DModelPosSet(obj->model[8], obj->trans.x + D_8010B260_treadmill_grill - 50.0f, 220.0f, 155.0f);
    minX = -D_8010AF8C_treadmill_grill[0] / 2.0f;
    maxX = D_8010AF8C_treadmill_grill[0] / 2.0f + 50.0f;
    func_800E13CC_minigame(obj, 250.0f, 250.0f, minX - 50.0f, -1050.0f, maxX, 150.0f);
}

void func_8010A9AC_treadmill_grill(omObjData* obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_801093E0_treadmill_grill(obj, i);
        D_8010B1B4_treadmill_grill[i] += D_8010B1C4_treadmill_grill[i];
    }
}

/* Belt lane under (x, z): 0..3, -1 off the belts. */
s32 func_8010AA2C_treadmill_grill(f32 x, f32 z) {
    s32 lane = -1;

    if (x <= 550.0f && x >= -550.0f) {
        if (z <= 150.0f && z > -150.0f) {
            lane = 0;
        } else if (z <= -150.0f && z > -450.0f) {
            lane = 1;
        } else if (z <= -450.0f && z > -750.0f) {
            lane = 2;
        } else {
            lane = 3;
        }
    }
    return lane;
}

/* Belt lane at z: 0..3. */
s32 func_8010AB9C_treadmill_grill(f32 z) {
    if (z <= 150.0f && z > -150.0f) {
        return 0;
    }
    if (z <= -150.0f && z > -450.0f) {
        return 1;
    }
    if (z <= -450.0f && z > -750.0f) {
        return 2;
    }
    return 3;
}

/* Stretches the belt models' vertices to the current belt widths (end caps move to +-width / 2). */
void func_8010ACBC_treadmill_grill(omObjData* obj) {
    TgHmfData* hmf;
    TgFaceGroup* g;
    Vtx* dst;
    Vtx* src;
    f32 r;
    s32 i, j, k;

    for (i = 0; i < 4; i++) {
        hmf = (TgHmfData*)HmfModelData[obj->model[i]].hmf;
        r = D_8010AF8C_treadmill_grill[i] / 1000.0f;
        for (j = 0; j < hmf->unk1A; j++) {
            g = &hmf->unkB0[j];
            if (g->unk02 == 0x7F) {
                for (k = 0; k < g->count; k++) {
                    dst = &hmf->unk44[D_800D2008_main][g->vtx[k]];
                    src = &hmf->unk40[g->vtx[k]];
                    if (src->v.ob[0] > 0) {
                        dst->v.ob[0] = D_8010AF8C_treadmill_grill[i] * 0.5f;
                    } else {
                        dst->v.ob[0] = -D_8010AF8C_treadmill_grill[i] * 0.5f;
                    }
                }
            } else {
                for (k = 0; k < g->count; k++) {
                    dst = &hmf->unk44[D_800D2008_main][g->vtx[k]];
                    src = &hmf->unk40[g->vtx[k]];
                    dst->v.ob[0] = src->v.ob[0] * r;
                }
            }
        }
    }
}

/* Rescales the belt texture coordinates after a width change. */
void func_8010AE6C_treadmill_grill(omObjData* obj) {
    TgHmfData* hmf;
    TgFaceGroup* g;
    Vtx* p;
    f32 r;
    s32 i, j, k;

    for (i = 0; i < 4; i++) {
        hmf = (TgHmfData*)HmfModelData[obj->model[i]].hmf;
        r = D_8010AF8C_treadmill_grill[i] / D_8010AF9C_treadmill_grill[i];
        for (j = 0; j < hmf->unk1A; j++) {
            g = &hmf->unkB0[j];
            for (k = 0; k < g->count; k++) {
                p = &hmf->unk40[g->vtx[k]];
                p->v.tc[0] = p->v.tc[0] * r;
            }
        }
    }
}
