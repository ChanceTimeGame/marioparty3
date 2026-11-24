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

// hh A: Hyper Hydrants (2 vs 2, split screen: each team pumps a hydrant to put out its fire)

typedef func_800E1BA8_minigame_ObjData MgWork;

#define HH_IABS(x) (((x) < 0) ? -(x) : (x))
#define HH_FABS(x) (((x) < 0.0f) ? -(x) : (x))
#define HH_ABS(x) (((x) > 0.0f) ? (x) : 0.0f - (x))

/* The minigame control block (as All Fired Up's AfCtrl) */
typedef struct HhCtrl {
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
} HhCtrl; /* size 0x28 */

/* MgWork::unk158 of a player */
typedef struct HhPlayer {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ s8 unk10; /* pump stroke: 0 idle, 1 down, 2 up */
    /* 0x11 */ char unk11;
    /* 0x12 */ u16 unk12; /* last pump button: 0x8000 A (down), 0x4000 B/Z (up) */
    /* 0x14 */ char unk14[4];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s8 unk1C;
    /* 0x1D */ char unk1D;
    /* 0x1E */ s16 unk1E;
} HhPlayer; /* size 0x20 */

/* omObjData::data of a water jet */
typedef struct HhJet {
    /* 0x00 */ s16 unk00; /* pressure, 5 .. 15 per pump level */
    /* 0x02 */ char unk02[2];
    /* 0x04 */ f32 unk04; /* heading, 120 .. 240 */
    /* 0x08 */ f32 unk08;
} HhJet; /* size 0xC */

/* HmfModel::hmf (only the face group count is read) */
typedef struct HhHmfData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 unk1A; /* face group count */
} HhHmfData;

/* A water drop of a jet's vertex-scatter effect (src/13F90.c HmfFxPart) */
typedef struct HhFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale; /* 0: hidden */
    /* 0x0C */ Vec pos;   /* y <= 0: a free slot */
    /* 0x18 */ Vec dir;
    /* 0x24 */ Vec vel;
} HhFxPart; /* size 0x30 */

/* HmfModel::unkBC of a water jet's model (src/13F90.c HmfFxWork), the work of its hook func_80108788 */
typedef struct HhFxWork {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02; /* frame */
    /* 0x04 */ u16 unk04; /* flags: 4 finished */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08; /* team (set by func_801078B8) */
    /* 0x0C */ char unk0C[0x4C];
    /* 0x58 */ HhFxPart* parts;
} HhFxWork;

/* omObjData::data of a fire */
typedef struct HhFire {
    /* 0x00 */ s8 unk00; /* index in the team */
    /* 0x01 */ s8 unk01; /* size class 1..3 */
    /* 0x02 */ s8 unk02; /* team */
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04; /* put out */
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ char unk07;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ f32 unk0C; /* shadow scale */
    /* 0x10 */ f32 unk10; /* radius; 0 when gone */
    /* 0x14 */ f32 unk14; /* bounce phase (drop-in) */
    /* 0x18 */ s8 unk18; /* frames hit in a row */
    /* 0x19 */ s8 unk19; /* hit this frame */
    /* 0x1A */ s8 unk1A;
    /* 0x1B */ char unk1B;
    /* 0x1C */ s16 unk1C; /* sound handle */
    /* 0x1E */ s16 unk1E;
} HhFire; /* size 0x20 */

/* omObjData::data of the iris object (the framework's ground block, as All Fired Up's AfGround) */
typedef struct HhGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[3];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ char unk0C[0xA8];
} HhGround; /* size 0xB4 */

// main
s32 func_8000B638_main(void);
void func_8000B710_main(s32);
void func_80021BE0_main(s32* arg0, s32 n);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004AD70_main(void);
void func_8000BD50_main(u16 id, s8 digit);
void func_80012B14_main(s16 camIndex, Vec* worldPos, Vec2f* outPos);
void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
void func_8001F6BC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void func_8001F6F8_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void func_8004AE00_main(s16 handle, s16 pan);
f32 HuSqrtf(f32 x);
s16 HmfAnimRead(HmfData* arg0, s32 arg1, char* arg2);

extern s32 D_800A178C_main[][6];
extern u16 D_800A1906_main; /* music state flags */
extern u16 D_800D530C_main;
extern u8 D_800D6A90_main;
extern s8 D_800CBB6E_main[];  /* CPU stick x */
extern s8 D_800D20A1_main[];  /* CPU stick y */
extern u16 D_800D5558_main[]; /* CPU buttons */
extern s16 D_800CDA7C_main[];

// minigame
void func_800DDD94_minigame(omObjData* obj);
void func_800E1328_minigame(omObjData* obj, f32 arg1);
void func_800E1490_minigame(u16 arg0);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E1804_minigame(void);
void func_800E1840_minigame(void);
void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2);
void func_800E4C88_minigame(omObjData* obj, u8 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s16 D_800EB934_minigame;
extern s32 D_800EBEB0_minigame[];

// LOCAL

void func_801059A0_hyper_hydrants(void);
void func_80105CB4_hyper_hydrants(HhCtrl* ctrl);
void func_80105D44_hyper_hydrants(omObjData* obj);
void func_80105D68_hyper_hydrants(s8 cam);
void func_80105EB0_hyper_hydrants(s8 cam);
void func_80105FC8_hyper_hydrants(void);
void func_801060F8_hyper_hydrants(omObjData* obj);
void func_80106238_hyper_hydrants(omObjData* obj);
void func_80106A50_hyper_hydrants(omObjData* obj);
void func_80107238_hyper_hydrants(omObjData* obj);
void func_801078B8_hyper_hydrants(omObjData* obj);
void func_80107A90_hyper_hydrants(omObjData* obj);
void func_801083A8_hyper_hydrants(s16 model, Vec* pos, HhJet* jet, s8 n);
void func_80108788_hyper_hydrants(s16 model);
void func_80108F34_hyper_hydrants(omObjData* obj);
void func_801091B0_hyper_hydrants(omObjData* obj);
void func_80109484_hyper_hydrants(omObjData* obj);
void func_80109588_hyper_hydrants(omObjData* obj);
void func_801099A0_hyper_hydrants(omObjData* obj);
void func_80109B30_hyper_hydrants(omObjData* obj);
void func_80109E44_hyper_hydrants(omObjData* obj);
void func_8010A2D4_hyper_hydrants(omObjData* obj);
void func_8010A458_hyper_hydrants(omObjData* obj);
void func_8010A68C_hyper_hydrants(omObjData* obj);
void func_8010AB34_hyper_hydrants(omObjData* obj);
void func_8010AE08_hyper_hydrants(omObjData* obj);
void func_8010B2FC_hyper_hydrants(omObjData* obj);
void func_8010B38C_hyper_hydrants(void);
void func_8010B658_hyper_hydrants(omObjData* obj);
void func_8010B8B0_hyper_hydrants(omObjData* obj);
s16 func_8010BC80_hyper_hydrants(s16 se, s16 side, s8 use3d, s16 player);
void func_8010BD14_hyper_hydrants(Vec* out, Vec* from, Vec* to);

extern Vec D_8010BDE0_hyper_hydrants;
extern Vec D_8010BDEC_hyper_hydrants;
extern Vec D_8010BDF8_hyper_hydrants;
extern Vec D_8010BE04_hyper_hydrants;
extern s8 D_8010BE10_hyper_hydrants[4]; /* fires lit per team (index into the layout row) */
extern s16 D_8010BE14_hyper_hydrants[2][2][2]; /* score digit positions, per team and digit */
extern f32 D_8010BE28_hyper_hydrants;
extern f32 D_8010BE2C_hyper_hydrants;
extern s8 D_8010BE24_hyper_hydrants;
extern s8 D_8010BE25_hyper_hydrants;
extern s8 D_8010BE34_hyper_hydrants;
extern s8 D_8010BE38_hyper_hydrants[3][16]; /* fire size class per layout, team slot */
extern s8 D_8010BE68_hyper_hydrants[2]; /* a fire came back this second, per team */
extern s8 D_8010BE6A_hyper_hydrants; /* iris: only clear, never redraw */
extern char D_8010BEF0_hyper_hydrants[]; /* "c201n_00_DEF" */
extern s8 D_8010BE35_hyper_hydrants;
extern s32 D_8010BE30_hyper_hydrants;

extern s8 D_8010BF40_hyper_hydrants;
extern s16 D_8010BF42_hyper_hydrants[2];
extern s8 D_8010BF46_hyper_hydrants;
extern s32 D_8010BF48_hyper_hydrants; /* drop-ins made; its low byte is D_8010BF4B */
extern s32 D_8010BF4C_hyper_hydrants;
extern s8 D_8010BF50_hyper_hydrants;
extern s16 D_8010BF52_hyper_hydrants;
extern s16 D_8010BF54_hyper_hydrants;
extern s16 D_8010BF56_hyper_hydrants;
extern s16 D_8010BF58_hyper_hydrants;
extern s16 D_8010BF88_hyper_hydrants;
extern s16 D_8010BF8A_hyper_hydrants[2]; /* iris mask sprite groups */
extern s16 D_8010BF8E_hyper_hydrants;    /* mask width */
extern u16 D_8010BF90_hyper_hydrants;    /* mask height */
extern u8* D_8010BF94_hyper_hydrants[2]; /* mask texels */
extern s32 D_8010BF9C_hyper_hydrants;    /* iris radius */ /* frames since the last pump, per team */
extern HhCtrl D_8010BF60_hyper_hydrants;
extern s8 D_8010BFA8_hyper_hydrants;
extern s8 D_8010BFA9_hyper_hydrants;
extern s32 D_8010BFA0_hyper_hydrants; /* screen x of the drop-in */
extern s32 D_8010BFA4_hyper_hydrants;
extern s8 D_8010BFAA_hyper_hydrants;
extern s8 D_8010BFAB_hyper_hydrants;
extern s8 D_8010BFAC_hyper_hydrants[2];
extern s8 D_8010BFAE_hyper_hydrants[2]; /* jet pressure per team */
extern Vec* D_8010BFB0_hyper_hydrants[2][6]; /* hose segment positions per team */
extern omObjData* D_8010BFE0_hyper_hydrants[2];
extern omObjData* D_8010BFE8_hyper_hydrants[2][5];
extern s8 D_8010C010_hyper_hydrants;
extern s16 D_8010C022_hyper_hydrants[2];
extern Vec D_8010C028_hyper_hydrants[2];
extern s16 D_8010C012_hyper_hydrants[2];
extern s16 D_8010C016_hyper_hydrants[2];
extern s16 D_8010C01A_hyper_hydrants[2][2]; /* hydrant end of the hose per team */


void func_801059A0_hyper_hydrants(void) {
    omObjData* obj;
    s32 i;
    s32 j;

    Hu3DAnimInit(0x20);
    func_80021BE0_main(D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105FC8_hyper_hydrants();
    func_80105CB4_hyper_hydrants(&D_8010BF60_hyper_hydrants);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010BF60_hyper_hydrants);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_80105D44_hyper_hydrants);
    omSetStatBit(obj, 0xA0);
    func_80105D44_hyper_hydrants(obj);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_801060F8_hyper_hydrants), 0xA0);
    for (i = 0; i < 2; i++) {
        D_8010BFE0_hyper_hydrants[i] = omAddObj(0, 2, 0, -1, func_80108F34_hyper_hydrants);
    }
    D_8010C010_hyper_hydrants = (rand8() * 3) >> 8;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 5; i++) {
            D_8010BFE8_hyper_hydrants[j][i] = omAddObj(0, 3, 0, -1, func_80109588_hyper_hydrants);
        }
    }
    for (i = 0; i < 2; i++) {
        omAddObj(1, 10, 0, -1, func_801078B8_hyper_hydrants);
    }
    omAddObj(1, 0, 0, -1, func_8010AE08_hyper_hydrants);
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 3, 5, -1, func_80106238_hyper_hydrants);
    }
    for (i = 0; i < 2; i++) {
        omAddObj(3, 6, 0, -1, func_8010A68C_hyper_hydrants);
    }
    omAddObj(3, 0, 0, -1, func_8010B658_hyper_hydrants);
    WipeCreateIn(0xFF, 16);
}

void func_80105CB4_hyper_hydrants(HhCtrl* ctrl) {
    s32 i;

    D_800EB932_minigame = 10;
    ctrl->unk00 = 0;
    ctrl->unk01 = 1;
    ctrl->unk02 = 1;
    ctrl->unk03 = 2;
    ctrl->unk04 = 0;
    ctrl->unk05 = 0;
    ctrl->unk06 = 9;
    ctrl->unk1C = 80;
    ctrl->unk1E = 900;
    ctrl->unk20 = -1;
    ctrl->unk22 = 75;
    ctrl->unk24 = 150;
    for (i = 0; i < 4; i++) {
        ctrl->unk08[i] = 0;
        ctrl->unk18[i] = 0xFF;
    }
}

void func_80105D44_hyper_hydrants(omObjData* obj) {
    func_80105EB0_hyper_hydrants(0);
    func_80105EB0_hyper_hydrants(1);
}

/* Camera `cam` (0 left team, 1 right team) during the intro: the target slides forward 2 units a frame. */
void func_80105D68_hyper_hydrants(s8 cam) {
    Vec pos;
    Vec at;
    Vec up;

    if (cam == 0) {
        pos.x = -850.0f;
    } else {
        pos.x = 850.0f;
    }
    pos.y = 1046.895f;
    pos.z = D_8010BE28_hyper_hydrants;
    if (cam == 0) {
        at.x = -850.0f;
    } else {
        at.x = 850.0f;
    }
    at.y = 0.0f;
    D_8010BE2C_hyper_hydrants += 2.0f;
    if (D_8010BE2C_hyper_hydrants > at.y) {
        D_8010BE2C_hyper_hydrants = at.y;
    }
    at.z = D_8010BE2C_hyper_hydrants;
    up.x = 0.0f;
    up.y = 1050.25f;
    up.z = 566.575f;
    Hu3DCamSetPositionOrientation(cam, &pos, &at, &up);
    Hu3DCamUpdateMtx(cam);
}

/* Camera `cam` at its start position. */
void func_80105EB0_hyper_hydrants(s8 cam) {
    Vec pos;
    Vec at;
    Vec up;

    if (cam == 0) {
        pos.x = -850.0f;
    } else {
        pos.x = 850.0f;
    }
    pos.y = 1046.895f;
    pos.z = 570.285f;
    if (cam == 0) {
        at.x = -850.0f;
    } else {
        at.x = 850.0f;
    }
    at.y = 0.0f;
    at.z = -375.0f;
    up.x = 0.0f;
    up.y = 1050.25f;
    up.z = 566.575f;
    Hu3DCamSetPositionOrientation(cam, &pos, &at, &up);
    Hu3DCamUpdateMtx(cam);
}

/* Two cameras, left and right halves of the screen. */
void func_80105FC8_hyper_hydrants(void) {
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 35.883f, 80.0f, 8000.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(1, 35.883f, 80.0f, 8000.0f);
}

void func_801060F8_hyper_hydrants(omObjData* obj) {
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        if (D_8010BE34_hyper_hydrants == 0 && D_800D530C_main == 1) {
            func_8004AD70_main();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                func_8004A950_main();
            }
            func_800E6F0C_minigame(5);
            D_8010BE34_hyper_hydrants = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 0x34;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (D_8010BE30_hyper_hydrants == 0) {
                    WipeCreateOut(0, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_8010BE30_hyper_hydrants++;
                break;
        }
    }
}

/* A player. Groups 0 and 2 aim the hose (D_8010BFAA/AB), 1 and 3 pump the hydrant (D_8010BFA8/A9); team = group >= 2.
   Model 2 is the hose or the hydrant. */
void func_80106238_hyper_hydrants(omObjData* obj) {
    s8 chr;
    u32 dir;
    s32 file;
    MgWork* pw;
    HhPlayer* ex;

    chr = GwPlayer[D_8010BE35_hyper_hydrants].chr;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][1];
    func_800E19F0_minigame(1);
    func_800E1BA8_minigame(obj, dir, file, D_8010BE35_hyper_hydrants, 0xAC9, 0xAD9);
    pw = obj->data;
    obj->rot.x = obj->rot.z = 0.0f;
    obj->scale.z = 1.0f;
    obj->scale.y = 1.0f;
    obj->scale.x = 1.0f;
    pw->unk158 = HuMemAllocTag(sizeof(HhPlayer), 0x7918);
    memset(obj->data, 0, sizeof(HhPlayer)); /* retail clears the start of MgWork, not the new block */
    ex = pw->unk158;
    ex->unk18 = 0;
    ex->unk1A = 0;
    ex->unk10 = 0;
    ex->unk12 = 0x4000;
    ex->unk1E = 0;
    ex->unk1C = 0;
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x14));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x7B));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x36));
    if (D_8010BE35_hyper_hydrants == 0) {
        D_8010BF40_hyper_hydrants = (u32)(rand8() * 5) >> 7;
    }
    switch (GwPlayer[pw->unk59].group) {
        case 0:
            obj->trans.x = D_8010BDE0_hyper_hydrants.x;
            obj->trans.y = D_8010BDE0_hyper_hydrants.y;
            obj->trans.z = D_8010BDE0_hyper_hydrants.z;
            D_8010BFAA_hyper_hydrants = pw->unk59;
            obj->rot.y = 180.0f;
            obj->model[2] = func_8000B108_main(0x2F0004, 0xA99);
            Hu3DModelRotSet(obj->model[2], obj->rot.x, obj->rot.y, obj->rot.z);
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 1, 2);
            Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z);
            func_8001C8A8_main(obj->model[0], 1);
            func_8001C8A8_main(obj->model[1], 1);
            func_8001C8A8_main(obj->model[2], 1);
            D_8010C022_hyper_hydrants[0] = func_8010BC80_hyper_hydrants(0x369, 0, 1, pw->unk59);
            func_8004AAD0_main(D_8010C022_hyper_hydrants[0], 0);
            break;
        case 1:
            obj->trans.x = D_8010BDEC_hyper_hydrants.x;
            obj->trans.y = D_8010BDEC_hyper_hydrants.y;
            obj->trans.z = D_8010BDEC_hyper_hydrants.z;
            D_8010BFA8_hyper_hydrants = pw->unk59;
            obj->rot.y = 0.0f;
            obj->model[2] = func_8000B108_main(0x2F0005, 0xA89);
            func_8001C258_main(obj->model[2], 0x10000, 0x10000);
            func_8001F6BC_main(obj->model[2], 0, 0, 0, 0);
            func_8001F6F8_main(obj->model[2], 0x10, 0x10, 0x10, 0);
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[1]].unk02, 0, 1, 2);
            if ((dir >> 16) == 6) {
                obj->trans.z -= 48.7f;
                Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z + 48.7f);
            } else {
                Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z);
            }
            func_8001C8A8_main(obj->model[0], 1);
            func_8001C8A8_main(obj->model[1], 1);
            func_8001C8A8_main(obj->model[2], 1);
            break;
        case 2:
            obj->trans.x = D_8010BDF8_hyper_hydrants.x;
            obj->trans.y = D_8010BDF8_hyper_hydrants.y;
            obj->trans.z = D_8010BDF8_hyper_hydrants.z;
            D_8010BFAB_hyper_hydrants = pw->unk59;
            obj->rot.y = 180.0f;
            obj->model[2] = func_8000B108_main(0x2F0006, 0xA99);
            Hu3DModelRotSet(obj->model[2], obj->rot.x, obj->rot.y, obj->rot.z);
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 1, 2);
            Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z);
            func_8001C8A8_main(obj->model[0], 2);
            func_8001C8A8_main(obj->model[1], 2);
            func_8001C8A8_main(obj->model[2], 2);
            D_8010C022_hyper_hydrants[1] = func_8010BC80_hyper_hydrants(0x369, 1, 1, pw->unk59);
            func_8004AAD0_main(D_8010C022_hyper_hydrants[1], 0);
            break;
        case 3:
            obj->trans.x = D_8010BE04_hyper_hydrants.x;
            obj->trans.y = D_8010BE04_hyper_hydrants.y;
            obj->trans.z = D_8010BE04_hyper_hydrants.z;
            D_8010BFA9_hyper_hydrants = pw->unk59;
            obj->rot.y = 0.0f;
            obj->model[2] = func_8000B108_main(0x2F0007, 0xA89);
            func_8001C258_main(obj->model[2], 0x10000, 0x10000);
            func_8001F6BC_main(obj->model[2], 0, 0, 0, 0);
            func_8001F6F8_main(obj->model[2], 0x10, 0x10, 0x10, 0);
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[1]].unk02, 0, 1, 2);
            if ((dir >> 16) == 6) {
                obj->trans.z -= 48.7f;
                Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z + 48.7f);
            } else {
                Hu3DModelPosSet(obj->model[2], obj->trans.x, 0.0f, obj->trans.z);
            }
            func_8001C8A8_main(obj->model[0], 2);
            func_8001C8A8_main(obj->model[1], 2);
            func_8001C8A8_main(obj->model[2], 2);
            break;
    }
    ex->unk00 = sindf(obj->rot.y - 40.0f);
    ex->unk04 = cosdf(obj->rot.y - 40.0f);
    ex->unk08 = sindf(obj->rot.y - 140.0f);
    ex->unk0C = cosdf(obj->rot.y - 140.0f);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C6A8_main(obj->model[2], 0.0f);
    obj->func = func_80106A50_hyper_hydrants;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    D_8010BE35_hyper_hydrants++;
}

/* A player: pumpers run func_80107238; the hose player turns, its hydrant sound pitch follows the pump level. */
void func_80106A50_hyper_hydrants(omObjData* obj) {
    MgWork* pw;
    HhPlayer* ex;
    s16 team;
    s32 voice;

    switch (func_800E6E8C_minigame()) {
        case 0:
        case 1:
            func_8001C6A8_main(obj->model[2], HmfModelData[obj->model[0]].unk40);
            break;
        case 2:
            pw = obj->data;
            ex = pw->unk158;
            if (pw->unk59 == D_8010BFA8_hyper_hydrants || pw->unk59 == D_8010BFA9_hyper_hydrants) {
                func_80107238_hyper_hydrants(obj);
                break;
            }
            if (!(GwPlayer[pw->unk59].stat & 1)) {
                if (HH_IABS(D_800CBB6E_main[pw->unk57]) > 0 && obj->rot.y > 120.0f &&
                    obj->rot.y < 240.0f) {
                    func_8001C814_main(obj->model[0], 1, 2);
                } else {
                    func_8001C814_main(obj->model[0], 1, 1);
                }
            }
            ex->unk00 = sindf(obj->rot.y - 40.0f);
            ex->unk04 = cosdf(obj->rot.y - 40.0f);
            ex->unk08 = sindf(obj->rot.y - 140.0f);
            ex->unk0C = cosdf(obj->rot.y - 140.0f);
            switch (D_8010BFAC_hyper_hydrants[team = pw->unk59 != D_8010BFAA_hyper_hydrants]) {
                case 0:
                    func_8004AAD0_main(D_8010C022_hyper_hydrants[team], 0);
                    break;
                case 1:
                    func_8004AAD0_main(D_8010C022_hyper_hydrants[team], 0x54);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[team], -300);
                    break;
                case 2:
                    func_8004AAD0_main(D_8010C022_hyper_hydrants[team], 0x5B);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[team], -200);
                    break;
                case 3:
                    func_8004AAD0_main(D_8010C022_hyper_hydrants[team], 0x62);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[team], -100);
                    break;
                case 4:
                    func_8004AAD0_main(D_8010C022_hyper_hydrants[team], 0x70);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[team], 100);
                    break;
                case 5:
                    func_8004AAD0_main(D_8010C022_hyper_hydrants[team], 0x77);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[team], 200);
                    break;
                default:
                    func_8004AAD0_main(D_8010C022_hyper_hydrants[team], 0x7F);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[team], 300);
                    break;
            }
            break;
        case 3:
            pw = obj->data;
            if (func_800E6E9C_minigame() == 0) {
                HuAudFXStop(D_8010C022_hyper_hydrants[0]);
                HuAudFXStop(D_8010C022_hyper_hydrants[1]);
                HuAudFXPlay(0x36B);
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 30, 2);
                func_8001C258_main(obj->model[2], 4, 4);
                switch (GwPlayer[pw->unk59].group) {
                    case 0:
                    case 1:
                        if (D_8010BE24_hyper_hydrants > D_8010BE25_hyper_hydrants) {
                            D_8010BF60_hyper_hydrants.unk06 = 1;
                            if (D_8010BF60_hyper_hydrants.unk18[0] == 0xFF) {
                                D_8010BF60_hyper_hydrants.unk18[0] = pw->unk59;
                            } else {
                                D_8010BF60_hyper_hydrants.unk18[1] = pw->unk59;
                            }
                        } else if (D_8010BE24_hyper_hydrants == D_8010BE25_hyper_hydrants) {
                            D_8010BF60_hyper_hydrants.unk06 = 4;
                        }
                        break;
                    case 2:
                    case 3:
                        if (D_8010BE24_hyper_hydrants < D_8010BE25_hyper_hydrants) {
                            D_8010BF60_hyper_hydrants.unk06 = 1;
                            if (D_8010BF60_hyper_hydrants.unk18[0] == 0xFF) {
                                D_8010BF60_hyper_hydrants.unk18[0] = pw->unk59;
                            } else {
                                D_8010BF60_hyper_hydrants.unk18[1] = pw->unk59;
                            }
                        } else if (D_8010BE24_hyper_hydrants == D_8010BE25_hyper_hydrants) {
                            D_8010BF60_hyper_hydrants.unk06 = 4;
                        }
                        break;
                }
            }
            if (HH_ABS(obj->rot.y) > 20.0f) {
                obj->rot.y -= 20.0f;
            } else {
                obj->rot.y = 0.0f;
            }
            if (((u32)D_800A178C_main[GwPlayer[pw->unk59].chr][0] >> 16) == 6 &&
                (D_8010BFA8_hyper_hydrants == pw->unk59 || D_8010BFA9_hyper_hydrants == pw->unk59)) {
                obj->trans.z += 5.0f;
                if (obj->trans.z > 18.7f) {
                    obj->trans.z = 18.7f;
                }
                Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
            }
            break;
        case 4:
            if (D_800EB934_minigame != 0) {
                pw = obj->data;
                if (pw->unk59 == D_8010BF60_hyper_hydrants.unk18[0] || pw->unk59 == D_8010BF60_hyper_hydrants.unk18[1]) {
                    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[3]].unk02, 0, 30, 2);
                    switch (GwPlayer[pw->unk59].chr) {
                        case 0:
                        default:
                            voice = 2;
                            break;
                        case 1:
                            voice = 3;
                            break;
                        case 2:
                            voice = 7;
                            break;
                        case 3:
                            voice = 4;
                            break;
                        case 4:
                            voice = 5;
                            break;
                        case 5:
                            voice = 6;
                            break;
                        case 6:
                            voice = 8;
                            break;
                        case 7:
                            voice = 9;
                            break;
                    }
                    func_80045ED0_main((voice << 16) | 0x2F);
                    GwPlayer[pw->unk59].bonusCoin += 10;
                } else {
                    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[4]].unk02, 0, 30, 2);
                }
            } else if (HmfModelData[obj->model[0]].unk40 >= 118.0f) {
                func_8001C814_main(obj->model[0], 1, 1);
            }
            break;
        case 5:
            break;
    }
}

/* A hydrant pumper (groups 1 and 3): alternate A (handle down) and B/Z (handle up); CPUs pump by chance.
   The pump count sets the team's level (D_8010BFAC) every 31 frames. */
void func_80107238_hyper_hydrants(omObjData* obj) {
    u16 down;
    u16 up;
    MgWork* pw;
    HhPlayer* ex;
    f32 frame;
    f32 end;
    s16 team;
    s16 hit;
    s8 r;

    down = 0;
    pw = obj->data;
    ex = pw->unk158;
    frame = HmfModelData[obj->model[0]].unk40;
    end = D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02;
    team = GwPlayer[pw->unk59].group >= 2;
    up = 0;
    if (GwPlayer[pw->unk59].stat & 1) {
        if ((frame == end) | (frame == 0.0f)) {
            r = (u32)(rand8() * 25) >> 6;
            switch (GwPlayer[pw->unk59].cpu_difficulty) {
                case 3:
                    hit = 1;
                    break;
                case 2:
                    hit = r < 90;
                    break;
                case 1:
                default:
                    hit = r < 40;
                    break;
                case 0:
                    hit = r < 30;
                    break;
            }
            if (D_8010BFAC_hyper_hydrants[team] == 0) {
                D_8010BFAC_hyper_hydrants[team] = 1;
                hit = 1;
            }
        } else {
            hit = 0;
        }
        if (hit) {
            if (frame == end) {
                up = 1;
            } else if (frame == 0.0f) {
                down = 1;
            }
        }
    } else {
        down = D_800D5558_main[pw->unk57] >> 15;
        up = (D_800D5558_main[pw->unk57] & 0x6000) != 0;
    }
    if ((down != 0) & (up != 0)) {
        if (ex->unk12 == 0x8000) {
            down = 0;
        } else if (ex->unk12 == 0x4000) {
            up = 0;
        }
    } else if (down) {
        if (ex->unk12 == 0x8000) {
            down = 0;
        }
    } else if (up) {
        if (ex->unk12 == 0x4000) {
            up = 0;
        }
    }
    if (down) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[1]].unk02, frame, 1, 2);
        ex->unk10 = 1;
        func_8010BC80_hyper_hydrants(0x368, team, 1, pw->unk59);
        ex->unk12 = 0x8000;
    } else if (up) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[1]].unk02, frame, 1, 4);
        ex->unk10 = 2;
        func_8010BC80_hyper_hydrants(0x367, team, 1, pw->unk59);
        ex->unk12 = 0x4000;
    }
    if (ex->unk10 == 1) {
        if (ex->unk18 < 9) {
            ex->unk18++;
        }
        if (frame >= end - 2.0f) {
            func_8001C814_main(obj->model[0], 1, 1);
            func_8001C814_main(obj->model[2], 1, 1);
            frame = end;
            ex->unk10 = 0;
        }
        D_8010BF42_hyper_hydrants[team] = 0;
    } else if (ex->unk10 == 2) {
        end = 0.0f;
        if (frame == end) {
            func_8001C814_main(obj->model[0], 1, 1);
            func_8001C814_main(obj->model[2], 1, 1);
            frame = end;
            ex->unk10 = 0;
        } else {
            ex->unk1C = 0;
        }
        D_8010BF42_hyper_hydrants[team] = 0;
    } else {
        if (ex->unk18 == 0) {
            D_8010BFAC_hyper_hydrants[team] = 0;
        } else if (ex->unk18 < 2) {
            D_8010BFAC_hyper_hydrants[team] = 1;
        } else if (ex->unk18 < 3) {
            D_8010BFAC_hyper_hydrants[team] = 2;
        } else if (ex->unk18 < 4) {
            D_8010BFAC_hyper_hydrants[team] = 3;
        } else if (ex->unk18 < 6) {
            D_8010BFAC_hyper_hydrants[team] = 4;
        } else if (ex->unk18 < 8) {
            D_8010BFAC_hyper_hydrants[team] = 5;
        } else {
            D_8010BFAC_hyper_hydrants[team] = 6;
        }
        if (D_8010BF42_hyper_hydrants[team] >= 2 && ex->unk18 > 0) {
            ex->unk18--;
        }
        D_8010BF42_hyper_hydrants[team]++;
    }
    func_8001C6A8_main(obj->model[0], frame);
    func_8001C6A8_main(obj->model[2], frame);
    if (frame == 0.0f) {
        ex->unk1C ^= 1;
    } else {
        ex->unk1C = 0;
    }
    if (ex->unk1C) {
        func_8001F6BC_main(obj->model[2], 0x40, 0x40, 0x40, 0);
        func_8001F6F8_main(obj->model[2], 0, 0, 0, 0);
    } else {
        func_8001F6BC_main(obj->model[2], 0, 0, 0, 0);
        func_8001F6F8_main(obj->model[2], 0x10, 0x10, 0x10, 0);
    }
    if (ex->unk1A >= 31) {
        D_8010BFAC_hyper_hydrants[team] = ex->unk18;
        ex->unk1A = 0;
        ex->unk18 = 0;
    } else {
        ex->unk1A++;
    }
}

/* A team's water jet (work[0] the team): its model follows the hose player; func_80108788 draws the stream. */
void func_801078B8_hyper_hydrants(omObjData* obj) {
    omObjData* player;
    HhJet* jet;

    obj->work[0] = D_8010BF46_hyper_hydrants;
    obj->func = func_80107A90_hyper_hydrants;
    obj->model[0] = func_8000B108_main(0x2F000B, 0x689);
    if (D_8010BF46_hyper_hydrants == 0) {
        player = D_800EC598_minigame[D_8010BFAA_hyper_hydrants];
        func_8001C8A8_main(obj->model[0], 1);
    } else {
        player = D_800EC598_minigame[D_8010BFAB_hyper_hydrants];
        func_8001C8A8_main(obj->model[0], 2);
    }
    obj->trans.x = player->trans.x;
    obj->trans.z = player->trans.z;
    obj->trans.y = 40.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, 40.0f, obj->trans.z);
    func_8001C2FC_main(obj->model[0], 0x20000, 0x20000);
    func_8001C448_main(obj->model[0]);
    func_8001C954_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_80013390_main(obj->model[0], -1, NULL, func_80108788_hyper_hydrants);
    jet = obj->data = HuMemAllocTag(sizeof(HhJet), 0x7918);
    memset(jet, 0, sizeof(HhJet));
    jet->unk00 = 5;
    jet->unk04 = 180.0f;
    jet->unk08 = 50.0f;
    ((HhFxWork*)HmfModelData[obj->model[0]].unkBC)->unk08 = D_8010BF46_hyper_hydrants;
    D_8010BF46_hyper_hydrants++;
}

// masked residue: $a0/$v1 for the pressure limit and the 110/55 jet distance multiply not duplicated into both arms (scheduling only); logic checked
#ifdef NON_MATCHING
/* A water jet while playing: the hose player (CPU: towards the nearest fire) turns it; A raises the pressure up
   to 15 per pump level of the team. */
void func_80107A90_hyper_hydrants(omObjData* obj) {
    s16 team;
    s8 p;
    omObjData* player;
    MgWork* pw;
    HhPlayer* ex;
    s8 port;
    HhJet* jet;
    s16 near;
    f32 far;
    s16 best;
    s16 i;
    f32 angle;
    f32 dist;
    s32 lim;
    Vec pos;

    if (func_800E6E8C_minigame() == 2) {
        if (obj->work[0] == 0) {
            team = 0;
            if (D_8010BFAC_hyper_hydrants[0] == 0) {
                return;
            }
            p = D_8010BFAA_hyper_hydrants;
        } else {
            team = 1;
            if (D_8010BFAC_hyper_hydrants[1] == 0) {
                return;
            }
            p = D_8010BFAB_hyper_hydrants;
        }
        player = D_800EC598_minigame[p];
        pw = player->data;
        ex = pw->unk158;
        port = pw->unk57;
        jet = obj->data;
        near = 0;
        if (GwPlayer[p].stat & 1) {
            far = -1000.0f;
            best = 4;
            for (i = 0; i < 5; i++) {
                if (far < D_8010BFE8_hyper_hydrants[team][i]->trans.z) {
                    far = D_8010BFE8_hyper_hydrants[team][i]->trans.z;
                    best = i;
                }
                if (D_8010BFE8_hyper_hydrants[team][i]->trans.z >= -250.0f) {
                    near++;
                }
            }
            angle = atan2df(D_8010BFE8_hyper_hydrants[team][best]->trans.x - D_800EC598_minigame[p]->trans.x,
                            D_8010BFE8_hyper_hydrants[team][best]->trans.z - D_800EC598_minigame[p]->trans.z);
            while (angle >= 360.0f) {
                angle -= 360.0f;
            }
            while (angle < 0.0f) {
                angle += 360.0f;
            }
            if (HH_FABS((s32)angle - jet->unk04) > 5.0f) {
                func_8001C814_main(D_800EC598_minigame[p]->model[0], 1, 2);
                switch (GwPlayer[p].cpu_difficulty) {
                    case 3:
                        if ((s32)angle < jet->unk04) {
                            jet->unk04 -= 4.0f;
                        } else {
                            jet->unk04 += 4.0f;
                        }
                        break;
                    case 2:
                        if ((rand8() >> 7) == 0) {
                            if ((s32)angle < jet->unk04) {
                                jet->unk04 -= 4.0f;
                            } else {
                                jet->unk04 += 4.0f;
                            }
                        }
                        break;
                    case 1:
                    default:
                        if (((rand8() * 3) >> 8) == 0) {
                            if ((s32)angle < jet->unk04) {
                                jet->unk04 -= 2.0f;
                            } else {
                                jet->unk04 += 2.0f;
                            }
                        }
                        break;
                    case 0:
                        if (((rand8() * 5) >> 8) == 0) {
                            if ((s32)angle < jet->unk04) {
                                jet->unk04 -= 1.0f;
                            } else {
                                jet->unk04 += 1.0f;
                            }
                        }
                        break;
                }
            } else {
                func_8001C814_main(D_800EC598_minigame[p]->model[0], 1, 1);
            }
            if (jet->unk04 > 240.0f) {
                jet->unk04 = 240.0f;
            }
            if (jet->unk04 < 120.0f) {
                jet->unk04 = 120.0f;
            }
            if (near >= 2) {
                D_800CDA7C_main[port] |= 0x8000;
            } else {
                D_800CDA7C_main[port] &= 0x7FFF;
            }
        } else if (HH_IABS(D_800CBB6E_main[port]) > 40) {
            if (D_800CBB6E_main[port] < 0) {
                jet->unk04 += 5.0f;
                if (jet->unk04 > 240.0f) {
                    jet->unk04 = 240.0f;
                }
            } else if (D_800CBB6E_main[port] > 0) {
                jet->unk04 -= 5.0f;
                if (jet->unk04 < 120.0f) {
                    jet->unk04 = 120.0f;
                }
            }
        } else if (HH_IABS(D_800CBB6E_main[port]) > 20) {
            if (D_800CBB6E_main[port] < 0) {
                jet->unk04 += 2.0f;
                if (jet->unk04 > 240.0f) {
                    jet->unk04 = 240.0f;
                }
            } else if (D_800CBB6E_main[port] > 0) {
                jet->unk04 -= 2.0f;
                if (jet->unk04 < 120.0f) {
                    jet->unk04 = 120.0f;
                }
            }
        }
        player->rot.y = jet->unk04;
        Hu3DModelRotSet(player->model[2], player->rot.x, player->rot.y, player->rot.z);
        if ((u16)D_800CDA7C_main[port] & 0x8000) {
            jet->unk00 += 3;
            lim = D_8010BFAC_hyper_hydrants[team] * 15;
            if (jet->unk00 > lim) {
                jet->unk00 = lim;
            }
        } else {
            jet->unk00 -= 3;
            if (jet->unk00 < 5) {
                jet->unk00 = 5;
            }
        }
        D_8010BFAE_hyper_hydrants[team] = jet->unk00;
        if (jet->unk00 > 50) {
            dist = 110.0f;
        } else {
            dist = 55.0f;
        }
        pos.x = ex->unk00 * dist + player->trans.x;
        pos.z = ex->unk04 * dist + player->trans.z;
        pos.y = 40.0f;
        func_801083A8_hyper_hydrants(obj->model[0], &pos, jet, jet->unk00 > 20 ? 28 : 10);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80107A90_hyper_hydrants);
#endif

// masked residue: retail converts -half after the spread's rand8() call (evaluation order; logic checked)
#ifdef NON_MATCHING
/* Emit up to `n` drops of a water jet from `pos`: a free particle (pos.y <= 0) gets a velocity aimed around the
   jet's heading, spread over its pressure in degrees. */
void func_801083A8_hyper_hydrants(s16 model, Vec* pos, HhJet* jet, s8 n) {
    HhFxWork* work;
    HhFxPart* part;
    s16 count;
    s16 half;
    s16 i;
    f32 heading;
    f32 speed;
    f32 t;
    Vec vel;

    work = (HhFxWork*)HmfModelData[model].unkBC;
    count = ((HhHmfData*)HmfModelData[model].hmf)->unk1A;
    half = jet->unk00 / 2;
    heading = jet->unk04 - half;
    speed = (s32)((u32)(rand8() * 5) >> 7) * 0.1f + jet->unk08;
    vel.x = sindf(heading + ((rand8() * jet->unk00) >> 8)) * speed;
    vel.y = sindf((f32)-half + ((rand8() * jet->unk00) >> 8)) * speed;
    vel.z = cosdf(heading + ((rand8() * jet->unk00) >> 8)) * speed;
    part = work->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->pos.y <= 0.0f) {
            part->vel = vel;
            t = (s32)((u32)(rand8() * 5) >> 7) * 0.1f;
            part->pos.x = t * vel.x + pos->x;
            part->pos.y = t * vel.y + pos->y;
            part->pos.z = t * vel.z + pos->z;
            if (jet->unk00 > 20) {
                part->scale = (u8)(rand8() & 7) + 2;
            } else {
                part->scale = (u8)(rand8() % 3) + 2;
            }
            if (--n == 0) {
                break;
            }
            speed = (s32)((u32)(rand8() * 5) >> 7) * 0.1f + jet->unk08;
            vel.x = sindf(heading + ((rand8() * jet->unk00) >> 8)) * speed;
            vel.y = sindf((f32)-half + ((rand8() * jet->unk00) >> 8)) * speed;
            vel.z = cosdf(heading + ((rand8() * jet->unk00) >> 8)) * speed;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801083A8_hyper_hydrants);
#endif

// masked residue: retail keeps 0.0f in $f12 for the drop resets and hoists the constant 1 (registers/scheduling; logic checked)
#ifdef NON_MATCHING
/* The water jet's update hook: drops fly and fall (damped by the pump level), and a drop crossing a fire marks
   it hit (and is used up while A is held). A fire hit for 15 frames (30 while A is held) goes out. */
void func_80108788_hyper_hydrants(s16 model) {
    HhFxWork* work;
    HhFxPart* part;
    omObjData* fire;
    HhFire* fd;
    s16 count;
    s16 i;
    s16 j;
    s32 team;
    s32 port;
    f32 minz;
    f32 z;
    f32 nz;
    f32 dx;
    f32 fz;
    s32 lim;
    s32 a;
    s32 b;

    work = (HhFxWork*)HmfModelData[model].unkBC;
    count = ((HhHmfData*)HmfModelData[model].hmf)->unk1A;
    team = work->unk08;
    if (work->unk02 == 0) {
        work->unk04 &= ~4;
        part = work->parts;
        for (i = 0; i < count; i++, part++) {
            part->pos.z = part->pos.y = part->pos.x = 0.0f;
            part->vel.z = part->vel.y = part->vel.x = 0.0f;
            part->scale = 0.0f;
            part->speed = 1.0f;
        }
        work->unk02++;
    }
    part = work->parts;
    if (team == 0) {
        port = ((MgWork*)D_800EC598_minigame[D_8010BFAA_hyper_hydrants]->data)->unk57;
    } else {
        port = ((MgWork*)D_800EC598_minigame[D_8010BFAB_hyper_hydrants]->data)->unk57;
    }
    minz = -500.0f;
    if ((u16)D_800CDA7C_main[port] & 0x8000) {
        minz = -250.0f;
    }
    for (i = 0; i < count; i++, part++) {
        if (part->pos.y > 0.0f) {
            if (part->pos.z < minz) {
                part->pos.y = part->scale = 0.0f;
            } else {
                z = part->pos.z;
                nz = z + part->vel.z;
                for (j = 0; j < 5; j++) {
                    fire = D_8010BFE8_hyper_hydrants[team][j];
                    fd = fire->data;
                    if (fd->unk10 == 0.0f) {
                        continue;
                    }
                    fz = fire->trans.z;
                    dx = HH_ABS(fire->trans.x - part->pos.x);
                    if (nz < z) {
                        a = nz < fz;
                        b = fz < z;
                    } else {
                        a = z < fz;
                        b = fz < nz;
                    }
                    if ((a & b) && dx < fd->unk10 * fire->scale.x) {
                        if (!((u16)D_800CDA7C_main[port] & 0x8000)) {
                            fd->unk19 = 1;
                        } else {
                            part->scale = 0.0f;
                            part->pos.y = 0.0f;
                            fd->unk19 = 1;
                        }
                        break;
                    }
                }
            }
            part->pos.x += part->vel.x;
            part->pos.y += part->vel.y - 1.0f;
            part->pos.z += part->vel.z;
            switch (D_8010BFAC_hyper_hydrants[team]) {
                case 0:
                    part->pos.y = part->scale = 0.0f;
                    part->vel.z = part->vel.y = part->vel.x = 0.0f;
                    break;
                case 1:
                    part->vel.x *= 0.6f;
                    part->vel.y *= 0.6f;
                    part->vel.z *= 0.6f;
                    if (D_8010BFAE_hyper_hydrants[team] >= 6) {
                        part->vel.y -= 75.0f;
                    } else {
                        part->vel.y -= 2.5f;
                    }
                    break;
                case 2:
                    part->vel.x *= 0.7f;
                    part->vel.y *= 0.7f;
                    part->vel.z *= 0.7f;
                    if (D_8010BFAE_hyper_hydrants[team] >= 6) {
                        part->vel.y -= 52.5f;
                    } else {
                        part->vel.y -= 1.75f;
                    }
                    break;
                case 3:
                    part->vel.x *= 0.8f;
                    part->vel.y *= 0.8f;
                    part->vel.z *= 0.8f;
                    if (D_8010BFAE_hyper_hydrants[team] >= 6) {
                        part->vel.y -= 45.0f;
                    } else {
                        part->vel.y -= 1.5f;
                    }
                    break;
                case 4:
                    part->vel.x *= 0.8f;
                    part->vel.y *= 0.8f;
                    part->vel.z *= 0.8f;
                    if (D_8010BFAE_hyper_hydrants[team] >= 6) {
                        part->vel.y -= 30.0f;
                    } else {
                        part->vel.y -= 1.0f;
                    }
                    break;
                case 5:
                    part->vel.x *= 0.9f;
                    part->vel.y *= 0.9f;
                    part->vel.z *= 0.9f;
                    if (D_8010BFAE_hyper_hydrants[team] >= 6) {
                        part->vel.y -= 15.0f;
                    } else {
                        part->vel.y -= 0.5f;
                    }
                    break;
                default:
                    part->vel.x *= 0.99f;
                    part->vel.y *= 0.99f;
                    part->vel.z *= 0.99f;
                    if (D_8010BFAE_hyper_hydrants[team] >= 6) {
                        part->vel.y -= 15.0f;
                    } else {
                        part->vel.y -= 0.5f;
                    }
                    break;
            }
        } else {
            part->scale = 0.0f;
        }
    }
    for (i = 0; i < 5; i++) {
        fire = D_8010BFE8_hyper_hydrants[team][i];
        fd = fire->data;
        if (fd->unk19 == 1) {
            if (D_8010BFAC_hyper_hydrants[team] > 0) {
                func_800E4C88_minigame(fire, 2, fire->trans.x, 100.0f, fire->trans.z + 50.0f, 0.0f, 0.0f);
                if (fd->unk18 == 1) {
                    fd->unk1A = 1;
                }
                fd->unk18++;
            }
            lim = 15;
            if ((u16)D_800CDA7C_main[port] & 0x8000) {
                lim = 30;
            }
            if (fd->unk04 == 0 && fd->unk18 >= lim) {
                fd->unk04 = 1;
                fd->unk18 = 0;
            }
            fd->unk19 = 0;
        } else {
            fd->unk18 = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80108788_hyper_hydrants);
#endif

// masked 6 (191/193): retail selects the camera with a branch (li 1/0) where this C gets sltu; tried ternary, if/else both orders, s32 cam (logic checked)
#ifdef NON_MATCHING
/* A team's burning building drop-in (work as HhFire): falls from 800 at the start, then bounces. */
void func_80108F34_hyper_hydrants(omObjData* obj) {
    HhFire* fd;
    s16 mdl;
    s16 cam;
    Vec pos;
    Vec2f scr;

    obj->func = func_801091B0_hyper_hydrants;
    fd = obj->data = HuMemAllocTag(sizeof(HhFire), 0x7918);
    memset(fd, 0, sizeof(HhFire));
    fd->unk00 = D_8010BF48_hyper_hydrants;
    fd->unk03 = 0;
    fd->unk14 = 0;
    if (fd->unk00 == 0) {
        obj->trans.x = -800.0f;
    } else {
        obj->trans.x = 800.0f;
    }
    obj->trans.y = 800.0f;
    obj->trans.z = -700.0f;
    obj->scale.z = 3.0f;
    obj->scale.y = 3.0f;
    obj->scale.x = 3.0f;
    pos.x = obj->trans.x;
    pos.y = obj->trans.y + 200.0f;
    pos.z = obj->trans.z;
    if (fd->unk00 != 0) {
        cam = 1;
    } else {
        cam = 0;
    }
    func_80012B14_main(cam, &pos, &scr);
    D_8010BFA0_hyper_hydrants = scr.x;
    D_8010BFA4_hyper_hydrants = scr.y;
    mdl = obj->model[0] = func_8000B108_main(0xA008A, 0x289);
    if (fd->unk00 == 0) {
        HmfAnimRead(HmfModelData[mdl].hmf, 0xA008C, D_8010BEF0_hyper_hydrants);
        func_8001C8A8_main(obj->model[0], 1);
    } else {
        func_80032694_main(HmfModelData[mdl].hmf, 0, 0, D_8010BEF0_hyper_hydrants);
        func_8001C8A8_main(obj->model[0], 2);
    }
    func_8001C448_main(mdl);
    func_8001C514_main(mdl);
    obj->model[1] = func_8000B108_main(0x2F0003, 0x99);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    fd->unk0C = 0.1f;
    Hu3DModelScaleSet(obj->model[1], 0.1f, 0.1f, 0.1f);
    D_8010BF48_hyper_hydrants++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80108F34_hyper_hydrants);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", D_8010BEF0_hyper_hydrants);

void func_801091B0_hyper_hydrants(omObjData* obj) {
    HhFire* fd;
    HhFire* other;
    Vec pos;
    Vec2f scr;

    fd = obj->data;
    switch (func_800E6E8C_minigame()) {
        case 0:
            if (fd->unk00 == 0) {
                pos.x = obj->trans.x + 50.0f;
                pos.y = obj->trans.y + 120.0f;
                pos.z = obj->trans.z;
                func_80012B14_main(0, &pos, &scr);
                D_8010BFA0_hyper_hydrants = scr.x;
                D_8010BFA4_hyper_hydrants = scr.y;
                if (fd->unk03 == 0) {
                    obj->trans.y -= 40.0f;
                    if (obj->trans.y < 0.0f) {
                        func_8010BC80_hyper_hydrants(0x366, 0, 1, 0);
                        fd->unk03 = 1;
                        omVibrate(0, 10, 0, 10);
                        omVibrate(1, 10, 0, 10);
                        omVibrate(2, 10, 0, 10);
                        omVibrate(3, 10, 0, 10);
                    }
                } else if (fd->unk03 == 1) {
                    func_80109484_hyper_hydrants(obj);
                }
                fd->unk0C += 0.5f;
                if (fd->unk0C > obj->scale.x / 2.0f) {
                    fd->unk0C = obj->scale.x / 2.0f;
                }
            } else {
                other = D_8010BFE0_hyper_hydrants[0]->data;
                obj->trans.y = D_8010BFE0_hyper_hydrants[0]->trans.y;
                fd->unk0C = other->unk0C;
                fd->unk03 = other->unk03;
                if (fd->unk03 == 0 && obj->trans.y < 0.0f) {
                    func_8010BC80_hyper_hydrants(0x366, 1, 1, 1);
                }
            }
            Hu3DModelScaleSet(obj->model[1], fd->unk0C, fd->unk0C, fd->unk0C);
            break;
        case 1:
            obj->trans.y = 0.0f;
            fd->unk03 = 0;
            break;
        case 2:
            func_80109484_hyper_hydrants(obj);
            break;
        case 3:
        case 4:
        case 5:
            obj->scale.x -= 0.4f;
            if (obj->scale.x < 0.0f) {
                obj->scale.x = 0.0f;
            }
            obj->scale.y = obj->scale.z = obj->scale.x;
            fd->unk0C = obj->scale.x / 2.0f;
            Hu3DModelScaleSet(obj->model[1], fd->unk0C, fd->unk0C, fd->unk0C);
            break;
    }
}

/* The drop-in's landing bounce: three half-sine hops of 50, then it rests. */
void func_80109484_hyper_hydrants(omObjData* obj) {
    HhFire* fd = obj->data;

    if (fd->unk03 == 1) {
        if (fd->unk14 < 1080.0f) {
            obj->trans.y = sindf(fd->unk14) * 50.0f + 0.0f;
            fd->unk14 += 45.0f;
            if ((s32)fd->unk14 % 180 == 0) {
                fd->unk14 += 180.0f;
            }
        } else {
            obj->trans.y = 0.0f;
            fd->unk14 = 0.0f;
            fd->unk03 = 2;
        }
    }
}

// decomp-permuter
void func_80109588_hyper_hydrants(omObjData *obj)
{
  HhFire *fd;
  s16 mdl;
  s16 new_var;
  obj->func = func_801099A0_hyper_hydrants;
  fd = (obj->data = HuMemAllocTag(sizeof(HhFire), 0x7918));
  memset(fd, 0, sizeof(HhFire));
  if (D_8010BF4C_hyper_hydrants < 5)
  {
    fd->unk02 = 0;
  }
  else
  {
    fd->unk02 = 1;
  }
  fd->unk00 = D_8010BF4C_hyper_hydrants % 5;
  fd->unk10 = 50.0f;
  fd->unk03 = rand8() >> 7;
  fd->unk04 = 0;
  fd->unk08 = (rand8() >> 5) * 15;
  fd->unk18 = 0;
  fd->unk19 = 0;
  fd->unk14 = 0;
  fd->unk05 = 0;
  fd->unk06 = 2;
  fd->unk0A = (rand8() >> 5) * 15;
  fd->unk1A = 0;
  fd->unk1E = 0;
  obj->trans.x = D_8010BFE0_hyper_hydrants[fd->unk02]->trans.x;
  obj->trans.z = D_8010BFE0_hyper_hydrants[fd->unk02]->trans.z;
  obj->trans.y = 0.0f;
  obj->rot.x = (obj->rot.y = (obj->rot.z = obj->trans.y));
  switch (D_8010BE38_hyper_hydrants[D_8010C010_hyper_hydrants][fd->unk00])
  {
    case 0:
      obj->scale.x = (obj->scale.y = (obj->scale.z = 1.0f));
      fd->unk0C = 0.5f;
      fd->unk01 = 1;
      break;

    case 1:
      obj->scale.x = (obj->scale.y = (obj->scale.z = 1.25f));
      fd->unk0C = 0.625f;
      fd->unk01 = 2;
      break;

    case 2:

    default:
      obj->scale.x = (obj->scale.y = (obj->scale.z = 1.5f));
      fd->unk0C = 0.75f;
      fd->unk01 = 3;
      break;

  }

  mdl = (obj->model[0] = func_8000B108_main(0x2F0002, 9));
  if (D_8010BF4C_hyper_hydrants == 0)
  {
    HmfAnimRead(HmfModelData[mdl].hmf, 0xA008C, D_8010BEF0_hyper_hydrants);
  }
  else
  {
    func_80032694_main(HmfModelData[mdl].hmf, 0, 0, D_8010BEF0_hyper_hydrants);
  }
  func_8001C448_main(mdl);
  func_8001C514_main(mdl);
  func_8001C258_main(new_var = obj->model[0], 4, 4);
  obj->model[1] = func_8000B108_main(0x2F0003, 0x99);
  Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
  Hu3DModelScaleSet(obj->model[1], fd->unk0C, fd->unk0C, fd->unk0C);
  func_8001C258_main(obj->model[1], 4, 4);
  obj->model[2] = func_8000B108_main(0x2F000C, 0xA59);
  Hu3DModelScaleSet(obj->model[2], 2.0f, 2.0f, 2.0f);
  if (fd->unk02 == 0)
  {
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C8A8_main(obj->model[1], 1);
    func_8001C8A8_main(obj->model[2], 1);
  }
  else
  {
    func_8001C8A8_main(obj->model[0], 2);
    func_8001C8A8_main(obj->model[1], 2);
    func_8001C8A8_main(obj->model[2], 2);
  }
  D_8010BF4C_hyper_hydrants++;
}

/* A fire: grows in, burns and moves while playing (func_80109E44), goes out when hit long enough. */
void func_801099A0_hyper_hydrants(omObjData* obj) {
    HhFire* fd = obj->data;

    switch (func_800E6E8C_minigame()) {
        case 0:
            func_80109B30_hyper_hydrants(obj);
            break;
        case 1:
            obj->trans.y = 0.0f;
            break;
        case 2:
            func_80109E44_hyper_hydrants(obj);
            if (fd->unk04 == 1) {
                func_8010A458_hyper_hydrants(obj);
            }
            if (fd->unk1A == 1) {
                if (fd->unk1E >= 2) {
                    fd->unk1E = 0;
                    fd->unk1A = 0;
                } else {
                    if (fd->unk1E == 0) {
                        fd->unk1C = func_8010BC80_hyper_hydrants(0x365, fd->unk02, 0, 0);
                    }
                    fd->unk1E++;
                }
            }
            break;
        case 3:
            obj->scale.x -= 0.1f;
            if (obj->scale.x < 0.0f) {
                obj->scale.x = 0.0f;
            }
            obj->scale.y = obj->scale.z = obj->scale.x;
            fd->unk0C = obj->scale.x / 2.0f;
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], fd->unk0C, fd->unk0C, fd->unk0C);
}

/* A fire's intro: after the drop-in lands it hops out of it (two arcs of 200) along its lane. */
void func_80109B30_hyper_hydrants(omObjData* obj) {
    HhFire* fd;
    s32 ph;

    fd = obj->data;
    ph = 0;
    if (!(D_8010BFE0_hyper_hydrants[fd->unk02]->trans.y > 0.0f)) {
        if (fd->unk14 == 0.0f) {
            func_8001C258_main(obj->model[0], 4, 0);
            func_8001C258_main(obj->model[1], 4, 0);
        } else if (fd->unk14 < 720.0f) {
            ph = (s32)fd->unk14 % 360;
            obj->trans.y = sindf(fd->unk14) * 200.0f;
        } else {
            obj->trans.y = 0.0f;
        }
        switch (fd->unk00) {
            case 0:
                obj->trans.z += 6.0f;
                if (fd->unk14 < 720.0f) {
                    fd->unk14 += 8.0f;
                    if (ph >= 180) {
                        fd->unk14 += 180.0f;
                    }
                }
                break;
            case 1:
                obj->trans.x -= 1.5f;
                obj->trans.z += 8.0f;
                if (fd->unk14 < 720.0f) {
                    fd->unk14 += 10.0f;
                    if (ph >= 180) {
                        fd->unk14 += 180.0f;
                    }
                }
                break;
            case 2:
                obj->trans.x += 1.5f;
                obj->trans.z += 8.0f;
                if (fd->unk14 < 720.0f) {
                    fd->unk14 += 10.0f;
                    if (ph >= 180) {
                        fd->unk14 += 180.0f;
                    }
                }
                break;
            case 3:
                obj->trans.x -= 1.5f;
                obj->trans.z += 5.0f;
                if (fd->unk14 < 720.0f) {
                    fd->unk14 += 6.0f;
                    if (ph >= 180) {
                        fd->unk14 += 180.0f;
                    }
                }
                break;
            default:
                obj->trans.x += 1.5f;
                obj->trans.z += 5.0f;
                if (fd->unk14 < 720.0f) {
                    fd->unk14 += 6.0f;
                    if (ph >= 180) {
                        fd->unk14 += 180.0f;
                    }
                }
                break;
        }
    }
}

/* A fire while playing: a put-out fire comes back from the building once a second; a live one grows to its size,
   wanders up and down the yard (z -500 .. -200) and side to side within its half of the screen. */
void func_80109E44_hyper_hydrants(omObjData* obj) {
    HhFire* fd;
    Vec pos;
    Vec2f scr;

    fd = obj->data;
    if (fd->unk01 == 0) {
        if (func_800E6E9C_minigame() % 60 == 0) {
            if (D_8010BE68_hyper_hydrants[fd->unk02] == 0) {
                func_8010A2D4_hyper_hydrants(obj);
                func_8010BC80_hyper_hydrants(0x365, fd->unk02, 0, 0);
                D_8010BE68_hyper_hydrants[fd->unk02] = 1;
                ((HhFire*)D_8010BFE0_hyper_hydrants[fd->unk02]->data)->unk03 = 1;
                goto move;
            }
        } else {
            D_8010BE68_hyper_hydrants[fd->unk02] = 0;
        }
        return;
    }
    if (fd->unk05 == 1) {
        obj->scale.x += 0.05f;
        switch (fd->unk01) {
            case 1:
                if (obj->scale.x > 1.0f) {
                    obj->scale.x = 1.0f;
                    fd->unk05 = 0;
                }
                break;
            case 2:
                if (obj->scale.x > 1.25f) {
                    obj->scale.x = 1.25f;
                    fd->unk05 = 0;
                }
                break;
            case 3:
                if (obj->scale.x > 1.5f) {
                    obj->scale.x = 1.5f;
                    fd->unk05 = 0;
                }
                break;
        }
        obj->scale.y = obj->scale.z = obj->scale.x;
        fd->unk0C = obj->scale.x / 2.0f;
    }
move:
    if (fd->unk06 == 2) {
        obj->trans.z += 2.0f;
        if (obj->trans.z > -500.0f) {
            fd->unk06 = 0;
        }
    } else if (fd->unk0A == 0) {
        fd->unk0A = (rand8() >> 5) * 15;
        if ((rand8() >> 7) == 0) {
            fd->unk06 ^= 1;
        }
    } else {
        fd->unk0A--;
        if (fd->unk06 == 0) {
            if (obj->trans.z > -200.0f) {
                fd->unk06 ^= 1;
            }
        } else if (fd->unk06 == 1) {
            if (obj->trans.z < -500.0f) {
                fd->unk06 ^= 1;
            }
        }
    }
    if (fd->unk06 == 0) {
        obj->trans.z += 3.0f;
    } else if (fd->unk06 == 1) {
        obj->trans.z -= 3.0f;
    }
    if (fd->unk08 == 0) {
        fd->unk03 ^= 1;
        fd->unk08 = (rand8() >> 5) * 15;
    } else {
        fd->unk08--;
        pos.x = obj->trans.x;
        pos.y = obj->trans.y;
        pos.z = obj->trans.z;
        if (fd->unk02 == 0) {
            Hu3DCam3DToScreen(0, &pos, &scr);
            if (fd->unk03 == 0 && scr.x < 119.0f) {
                fd->unk03 ^= 1;
            } else if (fd->unk03 == 1 && scr.x > 225.0f) {
                fd->unk03 ^= 1;
            }
        } else {
            Hu3DCam3DToScreen(1, &pos, &scr);
            if (fd->unk03 == 0 && scr.x < 95.0f) {
                fd->unk03 ^= 1;
            } else if (fd->unk03 == 1 && scr.x > 201.0f) {
                fd->unk03 ^= 1;
            }
        }
    }
    if (fd->unk03 != 0) {
        obj->trans.x += 4.0f;
    } else {
        obj->trans.x -= 4.0f;
    }
}

/* Bring a put-out fire back at the building with the next size from the layout table. */
void func_8010A2D4_hyper_hydrants(omObjData* obj) {
    HhFire* fd;
    s8 i;
    s8 size;

    fd = obj->data;
    i = D_8010BE10_hyper_hydrants[fd->unk02]++;
    if (i >= 16) {
        i %= 16;
    }
    size = D_8010BE38_hyper_hydrants[D_8010C010_hyper_hydrants][i];
    fd->unk10 = 50.0f;
    fd->unk18 = 0;
    fd->unk1A = 0;
    fd->unk05 = 1;
    fd->unk06 = 2;
    obj->trans.x = D_8010BFE0_hyper_hydrants[fd->unk02]->trans.x;
    obj->trans.z = D_8010BFE0_hyper_hydrants[fd->unk02]->trans.z;
    obj->trans.y = 0.0f;
    obj->scale.z = 0.1f;
    obj->scale.y = 0.1f;
    obj->scale.x = 0.1f;
    switch (size) {
        case 0:
            fd->unk0C = obj->scale.x / 2.0f;
            fd->unk01 = 1;
            break;
        case 1:
            fd->unk0C = obj->scale.x / 2.0f;
            fd->unk01 = 2;
            break;
        case 2:
        default:
            fd->unk0C = obj->scale.x / 2.0f;
            fd->unk01 = 3;
            break;
    }
}

/* A fire being put out shrinks a size class; at the smallest it goes out and the team scores. */
void func_8010A458_hyper_hydrants(omObjData* obj) {
    HhFire* fd = obj->data;

    switch (fd->unk01) {
        case 3:
            if (obj->scale.x <= 1.25f) {
                obj->scale.x = obj->scale.y = obj->scale.z = fd->unk0C = 1.25f;
                fd->unk04 = 0;
                fd->unk01--;
            } else {
                obj->scale.y = obj->scale.z = fd->unk0C = obj->scale.x = obj->scale.x - 0.05f;
            }
            break;
        case 2:
            if (obj->scale.x <= 1.0f) {
                obj->scale.x = obj->scale.y = obj->scale.z = fd->unk0C = 1.0f;
                fd->unk04 = 0;
                fd->unk01--;
            } else {
                obj->scale.y = obj->scale.z = fd->unk0C = obj->scale.x = obj->scale.x - 0.05f;
            }
            break;
        case 1:
            if (obj->scale.x <= 0.0f) {
                obj->trans.z = D_8010BFE0_hyper_hydrants[fd->unk02]->trans.z;
                obj->scale.x = obj->scale.y = obj->scale.z = fd->unk0C = fd->unk10 = 0.0f;
                fd->unk04 = 0;
                fd->unk01--;
                if (fd->unk02 == 0) {
                    D_8010BE24_hyper_hydrants++;
                    func_8010BC80_hyper_hydrants(0x364, fd->unk02, 1, D_8010BFAA_hyper_hydrants);
                } else {
                    D_8010BE25_hyper_hydrants++;
                    func_8010BC80_hyper_hydrants(0x364, fd->unk02, 1, D_8010BFAB_hyper_hydrants);
                }
                if (fd->unk02 == 0) {
                    omVibrate(D_8010BFA8_hyper_hydrants, 2, 3, 10);
                    omVibrate(D_8010BFAA_hyper_hydrants, 2, 3, 10);
                } else {
                    omVibrate(D_8010BFA9_hyper_hydrants, 2, 3, 10);
                    omVibrate(D_8010BFAB_hyper_hydrants, 2, 3, 10);
                }
            } else {
                obj->scale.y = obj->scale.z = fd->unk0C = obj->scale.x = obj->scale.x - 0.1f;
            }
            break;
    }
}

/* A team's hose (work[0] the team): 6 segments from the hydrant (by the pumper) to the hose player's nozzle. */
void func_8010A68C_hyper_hydrants(omObjData* obj) {
    s32 team;
    omObjData* p;
    HhPlayer* ex;
    f32 nx;
    f32 nz;
    Vec step;
    s32 i;
    s32 pl;

    obj->func = func_8010AB34_hyper_hydrants;
    team = 1;
    if (D_8010BF50_hyper_hydrants == 0) {
        obj->work[0] = 0;
        pl = D_8010BFA8_hyper_hydrants;
        team = 0;
    } else {
        obj->work[0] = team;
        pl = D_8010BFA9_hyper_hydrants;
    }
    p = D_800EC598_minigame[pl];
    D_8010C028_hyper_hydrants[team].x = (p->trans.x - 25.0f) - 18.75f;
    D_8010C028_hyper_hydrants[team].y = 37.5f;
    if (((u32)D_800A178C_main[GwPlayer[((MgWork*)p->data)->unk59].chr][0] >> 16) == 6) {
        D_8010C028_hyper_hydrants[team].z = p->trans.z + 50.0f + 18.75f + 48.7f;
    } else {
        D_8010C028_hyper_hydrants[team].z = p->trans.z + 50.0f + 18.75f;
    }
    obj->scale.z = 1.6f;
    obj->scale.y = 1.6f;
    obj->scale.x = 1.6f;
    if (obj->work[0] == 0) {
        pl = D_8010BFAA_hyper_hydrants;
    } else {
        pl = D_8010BFAB_hyper_hydrants;
    }
    p = D_800EC598_minigame[pl];
    ex = ((MgWork*)p->data)->unk158;
    nx = p->trans.x + ex->unk08 * 60.0f;
    nz = p->trans.z + ex->unk0C * 60.0f;
    step.x = HH_ABS(D_8010C028_hyper_hydrants[team].x - nx) / 5.0f;
    step.y = -8.5f;
    step.z = HH_ABS(D_8010C028_hyper_hydrants[team].z - nz) / 5.0f;
    for (i = 0; i < 6; i++) {
        obj->model[i] = func_8000B108_main(0x2F0008, 0x899);
        Hu3DModelScaleSet(obj->model[i], obj->scale.x, obj->scale.y, obj->scale.z);
        D_8010BFB0_hyper_hydrants[team][i] = HuMemAllocTag(0x1C, 0x7918);
        if (team == 0) {
            func_8001C8A8_main(obj->model[i], 1);
        } else {
            func_8001C8A8_main(obj->model[i], 2);
        }
        D_8010BFB0_hyper_hydrants[team][i]->x = nx + i * step.x;
        D_8010BFB0_hyper_hydrants[team][i]->y = i * step.y + 80.0f;
        D_8010BFB0_hyper_hydrants[team][i]->z = nz + i * step.z;
        if (i == 0) {
            obj->trans.x = D_8010BFB0_hyper_hydrants[team][i]->x;
            obj->trans.y = D_8010BFB0_hyper_hydrants[team][i]->y;
            obj->trans.z = D_8010BFB0_hyper_hydrants[team][i]->z;
        }
        Hu3DModelPosSet(obj->model[i], D_8010BFB0_hyper_hydrants[team][i]->x, D_8010BFB0_hyper_hydrants[team][i]->y,
                        D_8010BFB0_hyper_hydrants[team][i]->z);
    }
    D_8010BF50_hyper_hydrants++;
}

/* The hose follows its nozzle while playing and fades out at the end. */
void func_8010AB34_hyper_hydrants(omObjData* obj) {
    s32 team;
    omObjData* hose;
    HhPlayer* ex;
    f32 nx;
    f32 nz;
    Vec step;
    s32 i;
    s32 pl;

    switch (func_800E6E8C_minigame()) {
        case 2:
            team = 1;
            if (obj->work[0] == 0) {
                pl = D_8010BFAA_hyper_hydrants;
                team = 0;
            } else {
                pl = D_8010BFAB_hyper_hydrants;
            }
            hose = D_800EC598_minigame[pl];
            ex = ((MgWork*)hose->data)->unk158;
            nx = hose->trans.x + ex->unk08 * 60.0f;
            nz = hose->trans.z + ex->unk0C * 60.0f;
            step.x = HH_ABS(D_8010C028_hyper_hydrants[team].x - nx) / 5.0f;
            step.y = -8.5f;
            step.z = HH_ABS(D_8010C028_hyper_hydrants[team].z - nz) / 5.0f;
            for (i = 0; i < 6; i++) {
                D_8010BFB0_hyper_hydrants[team][i]->x = nx + i * step.x;
                D_8010BFB0_hyper_hydrants[team][i]->y = i * step.y + 80.0f;
                D_8010BFB0_hyper_hydrants[team][i]->z = nz + i * step.z;
                if (i == 0) {
                    obj->trans.x = D_8010BFB0_hyper_hydrants[team][i]->x;
                    obj->trans.y = D_8010BFB0_hyper_hydrants[team][i]->y;
                    obj->trans.z = D_8010BFB0_hyper_hydrants[team][i]->z;
                }
                Hu3DModelPosSet(obj->model[i], D_8010BFB0_hyper_hydrants[team][i]->x,
                                D_8010BFB0_hyper_hydrants[team][i]->y, D_8010BFB0_hyper_hydrants[team][i]->z);
            }
            break;
        case 0:
            break;
        case 1:
            break;
        case 3:
        case 4:
        case 5:
            for (i = 0; i < 6; i++) {
                func_8001C258_main(obj->model[i], 4, 4);
            }
            break;
    }
}

// decomp-permuter
void func_8010AE08_hyper_hydrants(omObjData *obj)
{
  HhGround *gw;
  HuSprite *spr[2];
  s32 i;
  u8 *a;
  u8 *b;
  f32 x;
  f32 y;
  f32 dx;
  float new_var;
  f32 dy;
  f32 d;
  obj->func = func_8010B2FC_hyper_hydrants;
  obj->trans.x = (obj->trans.y = (obj->trans.z = 0.0f));
  D_8010BF56_hyper_hydrants = func_8000B838_main(0x2F0009);
  D_8010BF58_hyper_hydrants = HuSprGrpCreate(1, 0);
  func_80055024_main(D_8010BF58_hyper_hydrants, 0, D_8010BF56_hyper_hydrants, 0);
  HuSprPriSet(D_8010BF58_hyper_hydrants, 0, 0x10);
  HuSprAttrReset(D_8010BF58_hyper_hydrants, 0, 0xFFFF);
  HuSprAttrSet(D_8010BF58_hyper_hydrants, 0, 0x1000);
  func_80054904_main(D_8010BF58_hyper_hydrants, 0, 160, 120);
  for (i = 0; i < 2; i++)
  {
    D_8010BF52_hyper_hydrants = func_8000B838_main(0x2F0000);
    D_8010BF88_hyper_hydrants = HuSprGrpCreate(1, 0);
    func_80055024_main(D_8010BF88_hyper_hydrants, 0, D_8010BF52_hyper_hydrants, 0);
    HuSprAttrReset(D_8010BF88_hyper_hydrants, 0, 0xFFFF);
    if (i == 0)
    {
      HuSprAttrSet(D_8010BF88_hyper_hydrants, 0, 0x5000);
      func_80054904_main(D_8010BF88_hyper_hydrants, 0, 80, 120);
    }
    else
    {
      HuSprAttrSet(D_8010BF88_hyper_hydrants, 0, 0x5001);
      func_80054904_main(D_8010BF88_hyper_hydrants, 0, 240, 120);
    }
  }

  gw = (obj->data = HuMemAllocTag(sizeof(HhGround), 0x7918));
  memset(gw, 0, sizeof(HhGround));
  gw->unk03 = 1;
  gw->unk04 = 0;
  gw->unk08 = 0.5f;
  func_800E1370_minigame(obj, 2, 0.0f);
  for (i = 0; i < 2; i++)
  {
    D_8010BF54_hyper_hydrants = func_8000B838_main(0x2F0001);
    D_8010BF8A_hyper_hydrants[i] = HuSprGrpCreate(1, 0);
    func_80055024_main(D_8010BF8A_hyper_hydrants[i], 0, D_8010BF54_hyper_hydrants, 0);
    HuSprPriSet(D_8010BF58_hyper_hydrants, 0, 0x20);
    HuSprAttrReset(D_8010BF8A_hyper_hydrants[i], 0, 0xFFFF);
    if (i == 0)
    {
      HuSprAttrSet(D_8010BF8A_hyper_hydrants[0], 0, 0x1000);
      func_80054904_main(D_8010BF8A_hyper_hydrants[0], 0, 80, 120);
    }
    else
    {
      HuSprAttrSet(D_8010BF8A_hyper_hydrants[i], 0, 0x1001);
      func_80054904_main(D_8010BF8A_hyper_hydrants[i], 0, 240, 120);
    }
    spr[i] = HuSprGet(D_8010BF8A_hyper_hydrants[i], 0);
    D_8010BF94_hyper_hydrants[i] = spr[i]->unk_84->unk00->unk00;
  }

  D_8010BF8E_hyper_hydrants = spr[0]->unk_84->unk14;
  D_8010BF90_hyper_hydrants = spr[0]->unk_84->unk16;
  D_8010BF9C_hyper_hydrants = 35;
  new_var = 0.13725491f;
  a = D_8010BF94_hyper_hydrants[0];
  b = D_8010BF94_hyper_hydrants[1];
  for (y = 0.0f; y < ((s16) D_8010BF90_hyper_hydrants); y += 1.0f)
  {
    for (x = 0.0f; x < D_8010BF8E_hyper_hydrants; x += 1.0f, a++, b++)
    {
      dx = x - D_8010BFA0_hyper_hydrants;
      dy = y - D_8010BFA4_hyper_hydrants;
      d = HuSqrtf((dx * dx) + (dy * dy));
      if (D_8010BF9C_hyper_hydrants < d)
      {
        *a = (*b = 0xFF);
      }
      else
      {
        *a = (*b = d / new_var);
      }
    }

  }

  func_80055458_main(D_8010BF8A_hyper_hydrants[0], 0, 240);
  func_80055458_main(D_8010BF8A_hyper_hydrants[1], 0, 240);
}

/* The iris opens by 3 a frame (to 240) once the drop-in has landed. */
void func_8010B2FC_hyper_hydrants(omObjData* obj) {
    if (func_800E6E8C_minigame() == 0) {
        if (D_8010BFE0_hyper_hydrants[0]->trans.y > 0.0f) {
            func_8010B38C_hyper_hydrants();
        } else if (D_8010BF9C_hyper_hydrants < 240) {
            D_8010BF9C_hyper_hydrants += 3;
            func_8010B38C_hyper_hydrants();
        } else {
            D_8010BF9C_hyper_hydrants = 240;
        }
    }
}

// masked 15 (213/211): retail loads the mask height once (lhu) at loop entry for both the bound and h, this C adds an lh there and a stack slot; tried the comma form and s32 h (logic checked)
#ifdef NON_MATCHING
/* Redraw the iris masks: clear inside 0.8 of the radius, a ramp to the radius, opaque beyond. */
void func_8010B38C_hyper_hydrants(void) {
    HhFire* big;
    f32 inner;
    f32 k;
    s32 ymax;
    u8* a;
    u8* b;
    s32 x;
    s32 y;
    f32 dx;
    f32 dy;
    f32 d;
    u8 v;
    u16 h;

    big = D_8010BFE0_hyper_hydrants[0]->data;
    if (big->unk03 == 2) {
        D_8010BE6A_hyper_hydrants = 1;
    }
    inner = D_8010BF9C_hyper_hydrants * 0.8f;
    k = (D_8010BF9C_hyper_hydrants * 0.2f) / 255.0f;
    ymax = D_8010BFA4_hyper_hydrants + D_8010BF9C_hyper_hydrants;
    a = D_8010BF94_hyper_hydrants[0];
    b = D_8010BF94_hyper_hydrants[1];
    for (y = 0; y < (s16)(h = D_8010BF90_hyper_hydrants); y++) {
        if (big->unk03 != 1 ? ymax < y : (s16)h / 2 < y) {
            break;
        }
        for (x = 0; x < D_8010BF8E_hyper_hydrants; x++, a++, b++) {
            if (D_8010BE6A_hyper_hydrants == 0 || *a != 0) {
                dx = x - D_8010BFA0_hyper_hydrants;
                dy = y - D_8010BFA4_hyper_hydrants;
                d = HuSqrtf(dx * dx + dy * dy);
                if (d <= inner) {
                    if (*a != 0) {
                        *a = *b = 0;
                    }
                } else if (D_8010BF9C_hyper_hydrants < d) {
                    if (~*a & 0xFF) {
                        *a = *b = 0xFF;
                    }
                } else {
                    v = (d - inner) / k;
                    if (v != *a) {
                        *a = *b = v;
                    }
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010B38C_hyper_hydrants);
#endif

/* The score display: a frame and a label per team, two digit sprites per team. */
void func_8010B658_hyper_hydrants(omObjData* obj) {
    s16 pos[2][2] = { { 35, 32 }, { 252, 32 } };
    s16 spr;
    s16 i;
    s16 j;

    spr = func_8000B838_main(0x2F000A);
    for (i = 0; i < 2; i++) {
        D_8010C012_hyper_hydrants[i] = InitEspriteSlot(spr, 0, 1);
        func_8000BBD4_main(D_8010C012_hyper_hydrants[i], pos[i][0], pos[i][1]);
        func_8000BB94_main(D_8010C012_hyper_hydrants[i]);
    }
    spr = func_8000B838_main(0x21001B);
    for (i = 0; i < 2; i++) {
        D_8010C016_hyper_hydrants[i] = InitEspriteSlot(spr, 0, 1);
        func_8000BBD4_main(D_8010C016_hyper_hydrants[i], pos[i][0] + 12, pos[i][1]);
        func_8000BB94_main(D_8010C016_hyper_hydrants[i]);
    }
    spr = func_8000B838_main(0x31);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            D_8010C01A_hyper_hydrants[i][j] = InitEspriteSlot(spr, 0, 1);
            func_8000BBD4_main(D_8010C01A_hyper_hydrants[i][j], D_8010BE14_hyper_hydrants[i][j][0],
                               D_8010BE14_hyper_hydrants[i][j][1]);
            func_8000BB94_main(D_8010C01A_hyper_hydrants[i][j]);
        }
    }
    obj->func = func_8010B8B0_hyper_hydrants;
}

/* Show each team's fires put out (one or two digits) while playing; hidden otherwise. */
void func_8010B8B0_hyper_hydrants(omObjData* obj) {
    s32 i;
    s32 j;

    switch (func_800E6E8C_minigame()) {
        case 2:
        case 3:
            if (D_8010BE24_hyper_hydrants < 10) {
                func_8000BB54_main(D_8010C01A_hyper_hydrants[0][0]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[0][0], D_8010BE24_hyper_hydrants % 10);
                func_8000BBD4_main(D_8010C01A_hyper_hydrants[0][0], D_8010BE14_hyper_hydrants[0][0][0],
                                   D_8010BE14_hyper_hydrants[0][0][1]);
                func_8000BB94_main(D_8010C01A_hyper_hydrants[0][1]);
            } else {
                func_8000BB54_main(D_8010C01A_hyper_hydrants[0][0]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[0][0], D_8010BE24_hyper_hydrants / 10);
                func_8000BBD4_main(D_8010C01A_hyper_hydrants[0][0], D_8010BE14_hyper_hydrants[0][0][0],
                                   D_8010BE14_hyper_hydrants[0][0][1]);
                func_8000BB54_main(D_8010C01A_hyper_hydrants[0][1]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[0][1], D_8010BE24_hyper_hydrants % 10);
                func_8000BBD4_main(D_8010C01A_hyper_hydrants[0][1], D_8010BE14_hyper_hydrants[0][1][0],
                                   D_8010BE14_hyper_hydrants[0][1][1]);
            }
            if (D_8010BE25_hyper_hydrants < 10) {
                func_8000BB54_main(D_8010C01A_hyper_hydrants[1][0]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[1][0], D_8010BE25_hyper_hydrants % 10);
                func_8000BBD4_main(D_8010C01A_hyper_hydrants[1][0], D_8010BE14_hyper_hydrants[1][0][0],
                                   D_8010BE14_hyper_hydrants[1][0][1]);
                func_8000BB94_main(D_8010C01A_hyper_hydrants[1][1]);
            } else {
                func_8000BB54_main(D_8010C01A_hyper_hydrants[1][0]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[1][0], D_8010BE25_hyper_hydrants / 10);
                func_8000BBD4_main(D_8010C01A_hyper_hydrants[1][0], D_8010BE14_hyper_hydrants[1][0][0],
                                   D_8010BE14_hyper_hydrants[1][0][1]);
                func_8000BB54_main(D_8010C01A_hyper_hydrants[1][1]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[1][1], D_8010BE25_hyper_hydrants % 10);
                func_8000BBD4_main(D_8010C01A_hyper_hydrants[1][1], D_8010BE14_hyper_hydrants[1][1][0],
                                   D_8010BE14_hyper_hydrants[1][1][1]);
            }
            for (i = 0; i < 2; i++) {
                func_8000BB54_main(D_8010C012_hyper_hydrants[i]);
                func_8000BB54_main(D_8010C016_hyper_hydrants[i]);
            }
            break;
        default:
            for (i = 0; i < 2; i++) {
                func_8000BB94_main(D_8010C012_hyper_hydrants[i]);
                func_8000BB94_main(D_8010C016_hyper_hydrants[i]);
                for (j = 0; j < 2; j++) {
                    func_8000BB94_main(D_8010C01A_hyper_hydrants[i][j]);
                }
            }
            break;
    }
}

/* Play sound `se` (positioned on `player` when `use3d`), panned to the left or right half. */
s16 func_8010BC80_hyper_hydrants(s16 se, s16 side, s8 use3d, s16 player) {
    s16 handle;

    if (use3d) {
        handle = func_8004AC98_main(se, player);
    } else {
        handle = HuAudFXPlay(se);
    }
    if (side == 0) {
        func_8004AE00_main(handle, 0x20);
    } else {
        func_8004AE00_main(handle, 0x60);
    }
    return handle;
}

/* out = the unit vector from `from` to `to` (zero when they coincide). */
void func_8010BD14_hyper_hydrants(Vec* out, Vec* from, Vec* to) {
    f32 len;

    out->x = to->x - from->x;
    out->y = to->y - from->y;
    out->z = to->z - from->z;
    len = out->x * out->x + out->y * out->y + out->z * out->z;
    len = HuSqrtf(len);
    if (len != 0.0f) {
        out->x /= len;
        out->y /= len;
        out->z /= len;
    } else {
        out->x = out->y = out->z = 0.0f;
    }
}

