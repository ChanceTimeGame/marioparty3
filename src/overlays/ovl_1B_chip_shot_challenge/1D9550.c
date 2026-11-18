#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/hmfman.h"
#include "mallocblock.h"

// chip shot A: Chip Shot Challenge (4 players take turns chipping a golf ball at the hole; nearest wins)

typedef func_800E1BA8_minigame_ObjData MgWork;

typedef struct ColVtx {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} ColVtx;

typedef struct ColTri {
    /* 0x0 */ s16 flags;
    /* 0x2 */ s16 v[3];
} ColTri;

/* main 20A20.c's polygon query list (minigame mgcol.h HitList) */
typedef struct HitList {
    /* 0x00 */ u16** list;
    /* 0x04 */ u16 count;
    /* 0x06 */ u16 pos;
} HitList;

typedef struct HitProbe {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 r;
} HitProbe;

typedef struct Vec4f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ f32 w; /* radius */
} Vec4f;

/* omObjData::data of the ball: the framework's item actor (minigame mgcol.h ColActorWork) */
typedef struct CsBall {
    /* 0x00 */ u8 unk00[0x20];
    /* 0x20 */ char unk20[0x14];
    /* 0x34 */ f32 unk34; /* height */
    /* 0x38 */ f32 unk38; /* vertical speed; 1000.0f on the ground */
    /* 0x3C */ f32 unk3C; /* heading */
    /* 0x40 */ f32 unk40; /* speed */
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48; /* radius */
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ u16 unk50;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ s8 unk53; /* ground object index */
    /* 0x54 */ u8 unk54;
    /* 0x55 */ char unk55[3];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C; /* slope push x */
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64; /* slope push z */
    /* 0x68 */ char unk68[0xC];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 (*unk84[9])();
    /* 0xA8 */ void* unkA8;
} CsBall; /* size 0xAC */

/* The minigame control block (minigame B8A20.c MgCtrl; the header's D_80111B50_vine_with_me_Struct) */
typedef struct CsCtrl {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06; /* result message: winners - 1, 4 none */
    /* 0x07 */ u8 unk07;
    /* 0x08 */ f32 unk08[4];
    /* 0x18 */ u8 unk18[4]; /* winner player indices */
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
} CsCtrl;

/* The model file's face data (HmfData; minigame mgcol.h) */
typedef struct DealerHmfData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 unk1A; /* face group count */
} DealerHmfData;

/* One scattered polygon of the vertex-scatter effect (src/13F90.c HmfFxPart). */
typedef struct DealerFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec dir;
    /* 0x24 */ Vec vel;
} DealerFxPart; /* sizeof 0x30 */

/* A model's vertex-scatter effect (HmfModel.unkBC; src/13F90.c HmfFxWork). */
typedef struct DealerFxWork {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02; /* frame */
    /* 0x04 */ u16 unk04; /* flags: 4 finished */
    /* 0x06 */ char unk06[0x52];
    /* 0x58 */ DealerFxPart* parts;
} DealerFxWork;

// main
s32 func_8000B638_main(void);
void func_8000BC48_main(u16, u16);
void func_80013390_main(s16 model, s16 type, char* name, void (*hook)(s16));
s32 func_80017B6C_main(s16 arg0, s16 arg1, s16 arg2);
void func_80017D24_main(f32 (*mf)[4], f32 rx, f32 ry, f32 rz);
void func_8001EF6C_main(s16 arg0, s16 arg1, char* arg2);
f32 func_800202A8_main(f32 angle);
s32 func_800202FC_main(Vec* v);
void func_8002038C_main(ColVtx* a, ColVtx* b, ColVtx* c, Vec* n);
f32 func_800204F4_main(f32 x, f32 y, f32 z, ColVtx* verts, ColTri* tri);
void func_80021BE0_main(HitList* l, s32 n);
void func_80021C14_main(s16 mi, HitList* l, s32 (*cb)(s32, u16*, ColVtx*, HitProbe*), HitProbe* probe);
u16* func_80022198_main(HitList* l);
void func_8004B760_main(s32 prio, s32 sprId, void* draw, f32 fov, Vec* eye, Vec* at);
void func_80088800_main(f32 (*mf)[4], f32 x, f32 y, f32 z);
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
f64 fabs(f64);

extern s32 D_800A178C_main[][6];
extern s8 D_800CBB6E_main[];
extern s16 D_800CDA7C_main[];
extern s8 D_800D20A1_main[];
extern f32 D_800D51FC_main;
extern f32 D_800D5410_main;
extern u8 D_800D6A90_main;

// minigame
f32 func_800D8818_minigame(f32 x, f32 y, f32 z, ColVtx* verts, ColTri* tri, Vec* dir, Vec* out);
s32 func_800DB704_minigame(s32 n, u16* idx, ColVtx* verts, HitProbe* probe);
f32 func_800D74AC_minigame(omObjData* obj, Vec4f* p, Vec* n);
void func_800D7388_minigame(omObjData* obj, f32 x, f32 y, f32 z, f32 g, Vec* n);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2);
void func_800E1468_minigame(omObjData* obj);
void func_800E147C_minigame(omObjData* obj);
void func_800E1490_minigame(u16 arg0);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
void func_800E17D4_minigame(omObjData* obj, f32 x, f32 y, f32 z);
void func_800E1804_minigame(void);
void func_800E28BC_minigame(f32 (*l2w)[4], f32 (*w2l)[4], Vec* p, omObjData* g);
void func_800E2B58_minigame(f32 (*m)[4], Vec* v);
void func_800E2BD4_minigame(f32 (*m)[4], Vec* v);
void func_800E2C68_minigame(f32 (*m)[4], Vec* v);
f32 func_800E2ED4_minigame(f32 x1, f32 z1, f32 x2, f32 z2);
void func_800E3584_minigame(s16 mdl);
void func_800E3628_minigame(s16 mdl, Vec* n);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(s8 arg0);

extern f32 D_800EB720_minigame;
extern f32 D_800EB72C_minigame;
extern f32 D_800EB73C_minigame;
extern f32 D_800EB77C_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s16 D_800EB934_minigame[];
extern f32 D_800EBE2C_minigame;
extern f32 D_800EBE30_minigame[4][4];
extern HitList D_800EBEB0_minigame;
extern f32 D_800EC240_minigame[4][4];
extern f32 D_800EC5D8_minigame;

// LOCAL

void func_801059A0_chip_shot_challenge(void);
s32 func_80105DE0_chip_shot_challenge(s32 player);
void func_80105E8C_chip_shot_challenge(omObjData* obj);
void func_80105EB8_chip_shot_challenge(omObjData* obj);
void func_8010646C_chip_shot_challenge(omObjData* obj);
void func_80106B84_chip_shot_challenge(omObjData* obj);
void func_80107048_chip_shot_challenge(void);
void func_801071A8_chip_shot_challenge(void);
void func_80107238_chip_shot_challenge(s16 model);
void func_801073D4_chip_shot_challenge(s16 model);
void func_80107520_chip_shot_challenge(omObjData* obj);
void func_80107960_chip_shot_challenge(s16 dist);
void func_80107BB0_chip_shot_challenge(void);
void func_80107E94_chip_shot_challenge(void);
void func_8010802C_chip_shot_challenge(void);
void func_80108108_chip_shot_challenge(omObjData* obj);
MgWork* func_80108274_chip_shot_challenge(omObjData* obj, s8 player);
void func_801085C0_chip_shot_challenge(omObjData* obj);
void func_80108638_chip_shot_challenge(omObjData* obj);
void func_801086B4_chip_shot_challenge(omObjData* obj);
void func_80108730_chip_shot_challenge(omObjData* obj);
void func_801087AC_chip_shot_challenge(omObjData* obj);
void func_801091E8_chip_shot_challenge(omObjData* obj);
void func_801094D8_chip_shot_challenge(omObjData* obj);
f32 func_80109AD0_chip_shot_challenge(omObjData* obj, f32 x, f32 y, f32 z);
void func_80109B24_chip_shot_challenge(omObjData* obj, f32 x, f32 y, f32 z);
f32 func_80109DE0_chip_shot_challenge(omObjData* obj, Vec4f* p);
void func_80109EF0_chip_shot_challenge(omObjData* obj, f32 x, f32 y, f32 z, f32 g, Vec* n);
f32 func_8010A04C_chip_shot_challenge(Vec* p, Vec* n);
void func_8010A3DC_chip_shot_challenge(omObjData* obj, Vec* n);
void func_8010A454_chip_shot_challenge(omObjData* obj, s32* stickX, s32* stickY, s32* btn);

/* .data */
extern s32 D_8010A820_chip_shot_challenge;    /* the ball is in flight */
extern s32 D_8010A824_chip_shot_challenge;    /* aiming: show the trajectory */
extern f32 D_8010A828_chip_shot_challenge;    /* aim heading */
extern f32 D_8010A82C_chip_shot_challenge;    /* aim power */
extern f32 D_8010A830_chip_shot_challenge;
extern f32 D_8010A834_chip_shot_challenge;    /* slope push */
extern f32 D_8010A838_chip_shot_challenge;    /* ball speed */
extern s32 D_8010A83C_chip_shot_challenge;    /* the ball is in the hole */
extern s32 D_8010A840_chip_shot_challenge;    /* frames since the ball stopped */
extern s16 D_8010A844_chip_shot_challenge;    /* turn */
extern s16 D_8010A846_chip_shot_challenge;
extern s32 D_8010A848_chip_shot_challenge;
extern s32 D_8010A84C_chip_shot_challenge[4][3]; /* player start positions */
extern f32 D_8010A87C_chip_shot_challenge[5];
extern f32 D_8010A890_chip_shot_challenge[5];
extern f32 D_8010A8A4_chip_shot_challenge[5];
extern f32 D_8010A8B8_chip_shot_challenge[5];
extern f32 D_8010A8CC_chip_shot_challenge[5];
extern s32 D_8010A8E0_chip_shot_challenge[4];  /* 0: the player won */
extern f32 D_8010A8F0_chip_shot_challenge[4];  /* each player's distance to the hole */
extern CsCtrl D_8010A900_chip_shot_challenge;
extern s32 D_8010A928_chip_shot_challenge[4];  /* player of each turn */
extern f32 D_8010A938_chip_shot_challenge;
extern f32 D_8010A93C_chip_shot_challenge;
extern f32 D_8010A940_chip_shot_challenge;
extern f32 D_8010A944_chip_shot_challenge;
extern s32 D_8010A948_chip_shot_challenge;
extern s32 D_8010A94C_chip_shot_challenge;     /* winner count */
extern s32 D_8010A950_chip_shot_challenge;     /* nearest player */
extern f32 D_8010A954_chip_shot_challenge;
extern s32 D_8010A958_chip_shot_challenge;
extern u8 D_8010A96C_chip_shot_challenge;
extern f32 D_8010A970_chip_shot_challenge;
extern f32 D_8010A974_chip_shot_challenge;
extern f32 D_8010A978_chip_shot_challenge;
extern f32 D_8010A97C_chip_shot_challenge;
extern s32 D_8010A980_chip_shot_challenge;
extern f32 D_8010A984_chip_shot_challenge[4];  /* CPU aim error: heading */
extern f32 D_8010A994_chip_shot_challenge[4];  /* CPU aim error: power */
extern f32 D_8010A9A4_chip_shot_challenge[4];  /* CPU aim error per difficulty */

/* .bss */
extern f32 D_8010AA60_chip_shot_challenge;
extern Vec D_8010AA64_chip_shot_challenge;
extern Vec D_8010AA70_chip_shot_challenge;
extern Vec D_8010AA7C_chip_shot_challenge;
extern f32 D_8010AA88_chip_shot_challenge;
extern Vec D_8010AA8C_chip_shot_challenge;
extern s32 D_8010AA98_chip_shot_challenge;
extern s32 D_8010AA9C_chip_shot_challenge;
extern s32 D_8010AAA0_chip_shot_challenge;     /* ground found under the ball */
extern Vec D_8010AAA4_chip_shot_challenge;     /* the hole */
extern Vec D_8010AAB0_chip_shot_challenge;     /* the ground normal at the hole */
extern f32 D_8010AABC_chip_shot_challenge;
extern s32 D_8010AAC0_chip_shot_challenge;     /* digit sprites */
extern s32 D_8010AAC4_chip_shot_challenge;     /* unit sprites */
extern s32 D_8010AAC8_chip_shot_challenge;
extern s32 D_8010AACC_chip_shot_challenge;
extern s32 D_8010AAD0_chip_shot_challenge;
extern s32 D_8010AAD8_chip_shot_challenge[4];  /* confetti models */
extern s16 D_8010AAE8_chip_shot_challenge;
extern omObjData* D_8010AAF0_chip_shot_challenge; /* the ball */

void func_801059A0_chip_shot_challenge(void) {
    u8 cam;
    s16 sprId;
    s32 i;
    s32 rank;

    Hu3DAnimInit(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800E1804_minigame();
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 40.0f, 80.0f, 8000.0f);
    HmfLightDirSet(1, 32.0f, 99.0f, 59.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 12, 0, -1, func_80106B84_chip_shot_challenge);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 10, 10, -1, func_801085C0_chip_shot_challenge);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 10, 10, -1, func_80108638_chip_shot_challenge);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 10, 10, -1, func_801086B4_chip_shot_challenge);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 10, 10, -1, func_80108730_chip_shot_challenge);
    omAddObj(3, 25, 10, -1, func_80107520_chip_shot_challenge);
    D_8010AAF0_chip_shot_challenge = omAddObj(3, 10, 0, -1, func_80108108_chip_shot_challenge);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    sprId = InitEspriteSlot(func_8000B838_main(0x3C001E), 0, 1);
    func_8000BB54_main(sprId);
    func_8000BBD4_main(sprId, 160, 120);
    func_8000BC48_main(sprId, 0x4000);
    WipeCreateIn(0xFF, 16);
    func_800E5EA0_minigame((D_80111B50_vine_with_me_Struct*)&D_8010A900_chip_shot_challenge);
    D_800EB930_minigame = 0x2D;
    D_800EB932_minigame = 60;
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 0.0f;
    CRot.x = 350.0f;
    CRot.y = 0.0f;
    CZoom = 750.0f;
    for (i = 0; i < 4; i++) {
        rank = func_80105DE0_chip_shot_challenge(i);
        while (D_8010A928_chip_shot_challenge[rank] != -1) {
            rank++;
        }
        D_8010A928_chip_shot_challenge[rank] = i;
    }
}

/* the player's board rank (players ahead of them) */
s32 func_80105DE0_chip_shot_challenge(s32 player) {
    s32 score[4];
    s32 rank;
    s32 i;

    for (i = 0; i < 4; i++) {
        score[i] = GwPlayer[i].star * 1000 + GwPlayer[i].coin;
    }
    for (i = 0, rank = 0; i < 4; i++) {
        if (i != player) {
            rank += score[player] < score[i];
        }
    }
    return rank;
}

void func_80105E8C_chip_shot_challenge(omObjData* obj) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

/* the intro: the flag flies in from the side and drops into the hole */
void func_80105EB8_chip_shot_challenge(omObjData* obj) {
    s32 t;
    f32 sq;

    t = func_800E6E9C_minigame();
    if (t == 1) {
        HuAudFXPlay(0x3E0);
    }
    if (t < 5) {
        Center.x = D_8010AAA4_chip_shot_challenge.x;
        Center.y = D_8010AAA4_chip_shot_challenge.y + 200.0f;
        Center.z = D_8010AAA4_chip_shot_challenge.z;
        D_8010AA70_chip_shot_challenge.x = D_8010AAA4_chip_shot_challenge.x + 1000.0f;
        D_8010AA70_chip_shot_challenge.y = D_8010AAA4_chip_shot_challenge.y + 300.0f;
        D_8010AA70_chip_shot_challenge.z = D_8010AAA4_chip_shot_challenge.z;
        Hu3DModelPosSet(obj->model[5], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
    } else if (t < 35) {
        func_8001C258_main(obj->model[6], 4, 0);
        func_8001C258_main(obj->model[4], 4, 0);
        Hu3DModelPosSet(obj->model[6], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
        Hu3DModelPosSet(obj->model[5], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
        D_8010AA70_chip_shot_challenge.x -= 33.333332f;
        D_8010AA70_chip_shot_challenge.y -= 3.3333333f;
        D_8010AA70_chip_shot_challenge.z += 0.0f;
        if (t < 21) {
            D_8010A938_chip_shot_challenge = D_8010AA70_chip_shot_challenge.y;
            D_8010AA7C_chip_shot_challenge.x -= 66.666664f;
            D_8010A940_chip_shot_challenge = 30.0f;
        } else {
            D_8010AA7C_chip_shot_challenge.x = D_8010AA70_chip_shot_challenge.x;
            D_8010AA7C_chip_shot_challenge.y = D_8010AA70_chip_shot_challenge.y;
            D_8010AA7C_chip_shot_challenge.z = D_8010AA70_chip_shot_challenge.z;
        }
    } else if (t < 65) {
        Hu3DModelPosSet(obj->model[6], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
        D_8010AA64_chip_shot_challenge.x = D_8010AAA4_chip_shot_challenge.x;
        D_8010AA64_chip_shot_challenge.y = D_8010AAA4_chip_shot_challenge.y;
        D_8010AA64_chip_shot_challenge.z = D_8010AAA4_chip_shot_challenge.z;
        func_800202FC_main(&D_8010AA64_chip_shot_challenge);
        D_8010AA60_chip_shot_challenge =
            HuSqrtf(D_8010AAA4_chip_shot_challenge.x * D_8010AAA4_chip_shot_challenge.x +
                    D_8010AAA4_chip_shot_challenge.y * D_8010AAA4_chip_shot_challenge.y +
                    D_8010AAA4_chip_shot_challenge.z * D_8010AAA4_chip_shot_challenge.z) /
            30.0f;
        D_8010AA70_chip_shot_challenge.x -= 33.333332f;
        D_8010AA70_chip_shot_challenge.y += 3.3333333f;
        D_8010AA70_chip_shot_challenge.z += 0.0f;
        D_8010AA7C_chip_shot_challenge.x -= 66.666664f;
        if (D_8010AA7C_chip_shot_challenge.x < D_8010AAA4_chip_shot_challenge.x) {
            D_8010AA7C_chip_shot_challenge.x = D_8010AAA4_chip_shot_challenge.x;
            if (D_8010A948_chip_shot_challenge != 0) {
                func_8004AC98_main(0x3DE, 0);
                D_8010A948_chip_shot_challenge = 0;
            }
        }
    } else {
        func_8001C258_main(obj->model[6], 4, 4);
        Center.x -= D_8010AA64_chip_shot_challenge.x * D_8010AA60_chip_shot_challenge;
        Center.y -= D_8010AA64_chip_shot_challenge.y * D_8010AA60_chip_shot_challenge;
        Center.z -= D_8010AA64_chip_shot_challenge.z * D_8010AA60_chip_shot_challenge;
    }
    if (D_8010A938_chip_shot_challenge > -1000.0f) {
        sq = D_8010A944_chip_shot_challenge * D_8010A944_chip_shot_challenge;
        if (D_8010A944_chip_shot_challenge >= 0.0f) {
            D_8010A938_chip_shot_challenge = sq * -37.5f + D_8010A938_chip_shot_challenge;
        } else {
            D_8010A938_chip_shot_challenge = sq * 37.5f + D_8010A938_chip_shot_challenge;
        }
        D_8010A944_chip_shot_challenge += D_800EB72C_minigame;
        if (D_8010A944_chip_shot_challenge > 1.2f) {
            D_8010A944_chip_shot_challenge = 1.2f;
        }
        if (D_8010A938_chip_shot_challenge < 0.0f) {
            D_8010A938_chip_shot_challenge = 0.0f;
        }
        if (D_8010A938_chip_shot_challenge == 0.0f) {
            D_8010A940_chip_shot_challenge *= 0.9f;
            D_8010A93C_chip_shot_challenge += 50.0f;
        }
        D_8010AA7C_chip_shot_challenge.y = D_8010A938_chip_shot_challenge;
        Hu3DModelRotSet(obj->model[5], 0.0f, 0.0f, sindf(D_8010A93C_chip_shot_challenge) * D_8010A940_chip_shot_challenge);
        Hu3DModelPosSet(obj->model[5], D_8010AA7C_chip_shot_challenge.x,
                        D_8010AAA4_chip_shot_challenge.y + D_8010AA7C_chip_shot_challenge.y,
                        D_8010AA7C_chip_shot_challenge.z);
    } else {
        Hu3DModelPosSet(obj->model[6], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
        Hu3DModelRotSet(obj->model[5], 0.0f, 0.0f, 30.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010646C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80106B84_chip_shot_challenge);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010A9D8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107048_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801071A8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107238_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801073D4_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107520_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107960_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107BB0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107E94_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010802C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108108_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108274_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801085C0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108638_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801086B4_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108730_chip_shot_challenge);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010AA00_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801087AC_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801091E8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801094D8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109AD0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109B24_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109DE0_chip_shot_challenge);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010AA2C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109EF0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010A04C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010A3DC_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010A454_chip_shot_challenge);
