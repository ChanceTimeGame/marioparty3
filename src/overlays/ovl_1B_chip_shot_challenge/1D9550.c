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

/* omObjData::data of the course (the framework's ground object, minigame mgcol.h GroundWork) */
typedef struct CsGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} CsGround; /* size 0xB4 */

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
omObjData* func_80045ED0_main(u32 arg0);
s16 HmfAnimRead(HmfData* hmf, s32 dataNum, char* name);

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
MgWork* func_80108274_chip_shot_challenge(omObjData* obj, s32 player);
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
extern s32 D_8010A844_chip_shot_challenge;    /* turn; -1 before the first */
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

/* the course object: the round's state machine */
void func_8010646C_chip_shot_challenge(omObjData* obj) {
    s32 t;
    s32 i;
    s32 n;
    f32 best;
    f32 x;
    f32 s;
    omObjData* p;
    MgWork* w;
    s32 chr;
    s32 file;

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        t = func_800E6E9C_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                func_80105EB8_chip_shot_challenge(obj);
                break;
            case 1:
                Hu3DModelRotSet(obj->model[5], 0.0f, 0.0f, 0.0f);
                break;
            case 2:
                if (D_8010A844_chip_shot_challenge < 0) {
                    D_8010A844_chip_shot_challenge = 0;
                }
                D_8010AA8C_chip_shot_challenge.x = Center.x;
                D_8010AA8C_chip_shot_challenge.y = Center.y - 200.0f;
                D_8010AA8C_chip_shot_challenge.z = Center.z;
                func_800202FC_main(&D_8010AA8C_chip_shot_challenge);
                D_8010AA88_chip_shot_challenge = HuSqrtf(Center.x * Center.x + Center.y * Center.y + Center.z * Center.z) / 30.0f;
                break;
            case 3:
                if (t == 0) {
                    best = 10000.0f;
                    for (i = 0; i < 4; i++) {
                        if (D_8010A8F0_chip_shot_challenge[i] < best) {
                            best = D_8010A8F0_chip_shot_challenge[i];
                            D_8010A950_chip_shot_challenge = i;
                        }
                        if (D_8010A8F0_chip_shot_challenge[i] == 0.0f) {
                            D_8010A94C_chip_shot_challenge++;
                            D_8010A8E0_chip_shot_challenge[i] = 0;
                        }
                    }
                    if (D_8010A94C_chip_shot_challenge != 0) {
                        D_8010A900_chip_shot_challenge.unk06 = (s8)D_8010A94C_chip_shot_challenge - 1;
                        for (i = 0, n = 0; i < 4; i++) {
                            if (D_8010A8F0_chip_shot_challenge[i] == 0.0f) {
                                D_8010A900_chip_shot_challenge.unk18[n++] = i;
                            }
                        }
                    } else {
                        for (i = 0; i < 4; i++) {
                            if (i != D_8010A950_chip_shot_challenge && (s32)best == (s32)D_8010A8F0_chip_shot_challenge[i]) {
                                D_8010A950_chip_shot_challenge = -1;
                            }
                        }
                        if (D_8010A950_chip_shot_challenge == -1) {
                            D_8010A900_chip_shot_challenge.unk06 = 4;
                        } else {
                            D_8010A900_chip_shot_challenge.unk06 = 0;
                            D_8010A900_chip_shot_challenge.unk18[0] = (u8)D_8010A950_chip_shot_challenge;
                            D_8010A8E0_chip_shot_challenge[D_8010A950_chip_shot_challenge] = 0;
                            D_8010A94C_chip_shot_challenge++;
                        }
                    }
                }
                Center.x -= D_8010AA8C_chip_shot_challenge.x * D_8010AA88_chip_shot_challenge;
                Center.y -= D_8010AA8C_chip_shot_challenge.y * D_8010AA88_chip_shot_challenge;
                Center.z -= D_8010AA8C_chip_shot_challenge.z * D_8010AA88_chip_shot_challenge;
                CRot.y *= 0.9f;
                if (Center.z >= 0.0f) {
                    Center.x = 0.0f;
                    Center.y = 200.0f;
                    Center.z = 0.0f;
                    CRot.y = 0.0f;
                }
                break;
            case 4:
                if (D_800EB934_minigame[0] == 1) {
                    for (i = 0; i < 4; i++) {
                        p = D_800EC598_minigame[i];
                        if (D_8010A8E0_chip_shot_challenge[D_8010A928_chip_shot_challenge[i]] == 0) {
                            w = p->data;
                            func_800E5690_minigame(p, 5);
                            chr = GwPlayer[w->unk59].chr;
                            file = D_800A178C_main[chr][0];
                            func_80017954_main(p->model[0], 2, chr, p->model[4]);
                            func_80045ED0_main(file | 0x2F);
                            GwPlayer[w->unk59].bonusCoin += 10;
                        } else {
                            func_800E5690_minigame(p, 6);
                        }
                    }
                }
                break;
            case 5:
                WipeCreateOut(0, 20);
                obj->func = func_80105E8C_chip_shot_challenge;
                break;
        }
        func_800E3628_minigame(obj->model[4], &D_8010AAB0_chip_shot_challenge);
        for (i = 0; i < 5; i++) {
            x = sindf(D_8010A87C_chip_shot_challenge[i]) * D_8010A8A4_chip_shot_challenge[i];
            Hu3DModelPosSet(obj->model[7 + i], x, D_8010A890_chip_shot_challenge[i],
                            cosdf(D_8010A87C_chip_shot_challenge[i]) * D_8010A8A4_chip_shot_challenge[i] - 1000.0f);
            Hu3DModelRotSet(obj->model[7 + i], 0.0f, CRot.y, 0.0f);
            s = sindf(D_8010A8CC_chip_shot_challenge[i]) * 0.25f + 2.5f;
            Hu3DModelScaleSet(obj->model[7 + i], s, s, s);
            D_8010A8CC_chip_shot_challenge[i] = func_800202A8_main(D_8010A8B8_chip_shot_challenge[i] * 30.0f + D_8010A8CC_chip_shot_challenge[i]);
            D_8010A87C_chip_shot_challenge[i] = func_800202A8_main(D_8010A87C_chip_shot_challenge[i] + D_8010A8B8_chip_shot_challenge[i]);
            if (D_8010A87C_chip_shot_challenge[i] > 260.0f) {
                D_8010A87C_chip_shot_challenge[i] = 100.0f;
            }
        }
        for (i = 0; i < D_800EC280_minigame; i++) {
            ((MgWork*)D_800EC598_minigame[i]->data)->unk60 = CRot.y;
        }
        if (D_800D530C_main == 1) {
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            obj->func = func_80105E8C_chip_shot_challenge;
        }
    }
}

/* the course: models, the ground object, the hole placed at random */
void func_80106B84_chip_shot_challenge(omObjData* obj) {
    CsGround* gw;
    s32 tag = 0x2B9;
    f32 angle;
    f32 dist;
    Vec p;

    D_800EB73C_minigame = 20.0f;
    if (rand8() > 128) {
        obj->model[0] = func_8000B0A0_main(0x3C0000, tag);
    } else {
        obj->model[0] = func_8000B0A0_main(0x3C0001, tag);
    }
    obj->model[1] = func_8000B0A0_main(0x3C0002, tag);
    obj->model[2] = func_8000B0A0_main(0x3C0003, tag);
    obj->model[3] = func_8000B0A0_main(0x3C0004, tag);
    obj->model[4] = func_8000B0A0_main(0x3C0005, tag);
    obj->model[5] = func_8000B0A0_main(0x3C0009, tag);
    func_800E3584_minigame(obj->model[4]);
    D_8010AAD0_chip_shot_challenge = obj->model[6] = func_8000B0A0_main(0xA0089, tag);
    obj->model[7] = func_8000B0A0_main(0x210029, tag);
    obj->model[8] = Hu3DModelLink(obj->model[7]);
    obj->model[9] = Hu3DModelLink(obj->model[7]);
    obj->model[10] = Hu3DModelLink(obj->model[7]);
    obj->model[11] = Hu3DModelLink(obj->model[7]);
    Hu3DModelScaleSet(obj->model[7], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[8], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[9], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[10], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[11], 2.0f, 2.0f, 2.0f);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -1000.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->data = gw = HuMemAllocTag(sizeof(CsGround), 31000);
    memset(gw, 0, sizeof(CsGround));
    obj->func = func_8010646C_chip_shot_challenge;
    gw->unk03 = 1;
    func_800E147C_minigame(obj);
    func_800E1370_minigame(obj, 1, 0.0f);
    func_800E1304_minigame(obj, 0.1f);
    func_800E1310_minigame(obj, D_800EB73C_minigame);
    func_800E131C_minigame(obj, 25.0f);
    func_800E1468_minigame(obj);
    gw->unk04 = 0;
    omSetStatBit(obj, 0xA0);
    while (1) {
        angle = rand8() * 1.4117647f;
        if (angle > 10.0f && (!(angle > 170.0f) | !(angle < 190.0f)) && angle < 350.0f) {
            break;
        }
    }
    dist = rand8() * 1.5f;
    if (dist < 200.0f) {
        dist = 200.0f;
    }
    D_8010AAA4_chip_shot_challenge.x = sindf(angle) * dist;
    D_8010AAA4_chip_shot_challenge.y = 50.0f;
    D_8010AAA4_chip_shot_challenge.z = cosdf(angle) * dist + -1000.0f;
    p.x = D_8010AAA4_chip_shot_challenge.x;
    p.y = 50.0f;
    p.z = D_8010AAA4_chip_shot_challenge.z;
    D_8010AAA4_chip_shot_challenge.y = func_8010A04C_chip_shot_challenge(&p, &D_8010AAB0_chip_shot_challenge);
    Hu3DModelScaleSet(obj->model[4], 0.625f, 0.625f, 0.625f);
    Hu3DModelPosSet(obj->model[4], D_8010AAA4_chip_shot_challenge.x, D_8010AAA4_chip_shot_challenge.y + 5.0f,
                    D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(obj->model[5], D_8010AAA4_chip_shot_challenge.x, D_8010AAA4_chip_shot_challenge.y - 10.0f,
                    D_8010AAA4_chip_shot_challenge.z);
    func_80107048_chip_shot_challenge();
}


/* four confetti models, scattered by the vertex effect */
void func_80107048_chip_shot_challenge(void) {
    s32 files[4] = { 0x000B002B, 0x000B002C, 0x000B002D, 0x000B002E };
    s16 model;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = func_8000B108_main(files[i], 0xAA9);
        D_8010AAD8_chip_shot_challenge[i] = model;
        func_8003302C_main(HmfAnimRead(HmfModelData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x20000, 0x20000);
        func_8001C448_main(model);
        func_8001C954_main(model);
        func_8001C514_main(model);
        func_80013390_main(model, -1, NULL, func_801073D4_chip_shot_challenge);
    }
}

void func_801071A8_chip_shot_challenge(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (!((D_8010AAE8_chip_shot_challenge + i) & 3)) {
            func_80107238_chip_shot_challenge(D_8010AAD8_chip_shot_challenge[i]);
        }
    }
    D_8010AAE8_chip_shot_challenge++;
}

/* launch the first idle confetti piece */
void func_80107238_chip_shot_challenge(s16 model) {
    DealerFxPart* part;
    s16 count;
    s16 i;

    count = ((DealerHmfData*)HmfModelData[model].hmf)->unk1A;
    part = ((DealerFxWork*)HmfModelData[model].unkBC)->parts;
    for (i = 0; i < count; i++, part++) {
        if (part->pos.y <= 0.0f) {
            part->pos.x = (rand8() - 127.0f) * 2.0f;
            part->pos.y = D_8010AAA4_chip_shot_challenge.y + 700.0f;
            part->pos.z = ((rand8() * 125) >> 5) - 500;
            part->dir.x = (f32)((s32)((u32)(rand8() * 5) >> 7) - 5) / 2.0f;
            part->dir.y = 0.0f;
            part->dir.z = (f32)((s32)((u32)(rand8() * 5) >> 7) - 5) / 2.0f;
            part->scale = 5.0f;
            return;
        }
    }
}

/* the effect's update hook: the pieces fall until they reach the ground */
void func_801073D4_chip_shot_challenge(s16 model) {
    DealerHmfData* hmf;
    DealerFxWork* work;
    DealerFxPart* part;
    u16 count;
    s16 i;

    hmf = (DealerHmfData*)HmfModelData[model].hmf;
    work = (DealerFxWork*)HmfModelData[model].unkBC;
    count = hmf->unk1A;
    if (work->unk02 == 0) {
        work->unk04 &= ~4;
        part = work->parts;
        for (i = 0; i < (s16)count; i++, part++) {
            part->scale = part->vel.x = part->vel.y = part->vel.z = part->pos.x = part->pos.y = part->pos.z = 0.0f;
            part->speed = 1.0f;
        }
        work->unk02++;
    }
    part = work->parts;
    for (i = 0; i < (s16)count; i++, part++) {
        if (part->pos.y > 0.0f) {
            part->pos.x += part->dir.x;
            part->pos.y += part->dir.y - 15.0f;
            part->pos.z += part->dir.z;
        } else {
            part->scale = 0.0f;
        }
    }
}

/* the trajectory dots, the distance display and the hole-in-one/out-of-bounds signs */
void func_80107520_chip_shot_challenge(omObjData* obj) {
    void* data;
    s16 digits;
    s16 units;
    s16 group;
    s16 i;
    s32 x;

    D_800D51FC_main = D_800D5410_main = 0.0f;
    obj->model[1] = func_8000B0A0_main(0x3C0007, 0xAD9);
    obj->model[2] = func_8000B0A0_main(0x3C0007, 0xAD9);
    obj->model[3] = func_8000B0A0_main(0x3C0007, 0xAD9);
    obj->model[4] = func_8000B0A0_main(0x3C0007, 0xAD9);
    obj->model[5] = func_8000B0A0_main(0x3C0007, 0xAD9);
    obj->model[6] = func_8000B0A0_main(0x3C0007, 0xAD9);
    obj->model[7] = func_8000B0A0_main(0x3C0007, 0xAD9);
    obj->model[8] = func_8000B0A0_main(0x3C0007, 0xAD9);
    obj->model[9] = func_8000B0A0_main(0x3C0007, 0xAD9);
    obj->model[10] = func_8000B0A0_main(0x3C0007, 0xAD9);
    D_800D51FC_main = D_800D5410_main = 1.0f;
    obj->func = func_801091E8_chip_shot_challenge;
    data = DataRead(0x2D);
    digits = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x3C001F);
    units = func_80055810_main(data);
    DataClose(data);
    group = D_8010AAC0_chip_shot_challenge = HuSprGrpCreate(4, 5);
    func_80055024_main(group, 0, digits, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x8000);
    func_80054904_main(group, 0, 0x80, 0x64);
    HuSprPriSet(group, 0, 1);
    x = 15;
    for (i = 1; i < 4; i++) {
        HuSprPriSet(group, i, 1);
        func_80055024_main(group, i, digits, 0);
        func_80054904_main(group, i, x, 0);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, 0x8000);
        if (i == 1) {
            x += 20;
        } else {
            x += 15;
        }
        func_800554C4_main(group, i, 0);
    }
    HuSprAttrReset(group, 2, 0x8000);
    group = HuSprGrpCreate(2, 5);
    D_8010AAC4_chip_shot_challenge = group;
    func_80055024_main(group, 0, units, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x8000);
    func_80054904_main(group, 0, 0x9F, 0x64);
    HuSprPriSet(group, 0, 1);
    HuSprPriSet(group, 1, 1);
    func_80055024_main(group, 1, units, 0);
    func_80054904_main(group, 1, 0x23, 0);
    HuSprAttrReset(group, 1, 0xFFFF);
    HuSprAttrSet(group, 1, 0x8000);
    func_800554C4_main(group, 1, 0);
    HuSprAttrReset(group, 2, 0x8000);
    D_8010AACC_chip_shot_challenge = func_8000B0A0_main(0x3C001D, 0xAD9);
    D_8010AAC8_chip_shot_challenge = func_8000B0A0_main(0x3C001C, 0xAD9);
}

/* show the ball's distance to the hole */
// masked 5, one instruction short: retail keeps dist and the thousands digit in two registers (s3, s1)
// where this C shares one; the digit arithmetic (dist - dist / 1000 * 1000, then / 100, / 10) is as retail
#ifdef NON_MATCHING
void func_80107960_chip_shot_challenge(s16 dist) {
    s16 q;
    s16 r;
    s16 u;

    q = dist / 1000;
    if (q != 0) {
        HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 0, 0x8000);
        func_80055140_main(D_8010AAC0_chip_shot_challenge, 0, q, 0);
        func_800550F4_main(D_8010AAC0_chip_shot_challenge, 0, 1);
    }
    r = dist - (s16)(dist / 1000) * 1000;
    HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 1, 0x8000);
    q = r / 100;
    func_80055140_main(D_8010AAC0_chip_shot_challenge, 1, q, 0);
    func_800550F4_main(D_8010AAC0_chip_shot_challenge, 1, 1);
    r -= q * 100;
    HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 2, 0x8000);
    q = r / 10;
    func_80055140_main(D_8010AAC0_chip_shot_challenge, 2, q, 0);
    func_800550F4_main(D_8010AAC0_chip_shot_challenge, 2, 1);
    u = r - q * 10;
    HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 3, 0x8000);
    func_80055140_main(D_8010AAC0_chip_shot_challenge, 3, u, 0);
    func_800550F4_main(D_8010AAC0_chip_shot_challenge, 3, 1);
    HuSprAttrReset(D_8010AAC4_chip_shot_challenge, 0, 0x8000);
    func_80054FF8_main(D_8010AAC4_chip_shot_challenge, 0, 1);
    HuSprAttrReset(D_8010AAC4_chip_shot_challenge, 1, 0x8000);
    func_80054FF8_main(D_8010AAC4_chip_shot_challenge, 1, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107960_chip_shot_challenge);
#endif

/* hole in one: the sign bounces over the hole, confetti falls */
void func_80107BB0_chip_shot_challenge(void) {
    f32 x;
    f32 z;
    f32 y;
    f32 top;
    Vec d;

    x = d.x = D_8010AAF0_chip_shot_challenge->trans.x;
    d.y = D_8010AAF0_chip_shot_challenge->trans.y;
    z = d.z = D_8010AAF0_chip_shot_challenge->trans.z;
    func_800202FC_main(&d);
    if (D_8010A840_chip_shot_challenge < 31) {
        y = D_8010AAA4_chip_shot_challenge.y + 700.0f - D_8010A840_chip_shot_challenge * 10.0f;
        Center.y *= 1.02f;
        D_8010A954_chip_shot_challenge = -9.0f;
        if (D_8010A958_chip_shot_challenge != 0) {
            HuAudFXPlay(0x3DF);
            D_8010A958_chip_shot_challenge = 0;
        }
    } else {
        y = D_8010AAA4_chip_shot_challenge.y + 400.0f + sindf(D_8010A954_chip_shot_challenge) * 100.0f;
        D_8010A954_chip_shot_challenge -= 9.0f;
        Center.y *= 1.02f;
        D_8010A958_chip_shot_challenge = -1;
    }
    if (D_8010A840_chip_shot_challenge < 101) {
        func_801071A8_chip_shot_challenge();
    }
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[0], D_8010AAA4_chip_shot_challenge.x, D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[1], D_8010AAA4_chip_shot_challenge.x, D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[2], D_8010AAA4_chip_shot_challenge.x, D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[3], D_8010AAA4_chip_shot_challenge.x, D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    top = D_8010AAA4_chip_shot_challenge.y + 400.0f;
    if (top < Center.y) {
        Center.y = top;
    }
    Hu3DModelPosSet(D_8010AAD0_chip_shot_challenge, x, y, z);
    Hu3DModelPosSet(D_8010AAC8_chip_shot_challenge, x, y, z);
    Hu3DModelRotSet(D_8010AAD0_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AAC8_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    func_8001C258_main(D_8010AAC8_chip_shot_challenge, 4, 0);
    func_8001C258_main(D_8010AAD0_chip_shot_challenge, 4, 0);
}

/* the ball stopped: the sign rises beside it */
void func_80107E94_chip_shot_challenge(void) {
    f32 x;
    f32 z;
    f32 y;
    Vec d;

    x = d.x = D_8010AAF0_chip_shot_challenge->trans.x;
    d.y = D_8010AAF0_chip_shot_challenge->trans.y;
    z = d.z = D_8010AAF0_chip_shot_challenge->trans.z;
    func_800202FC_main(&d);
    if (D_8010A840_chip_shot_challenge == 1) {
        func_8004AC98_main(0x3DC, D_8010A844_chip_shot_challenge);
    }
    if (D_8010A840_chip_shot_challenge < 31) {
        y = D_8010A840_chip_shot_challenge * 10.0f + -200.0f;
    } else {
        y = 100.0f;
    }
    x += d.x * 200.0f;
    z += d.z * 200.0f;
    Hu3DModelPosSet(D_8010AAD0_chip_shot_challenge, x, y, z);
    Hu3DModelPosSet(D_8010AACC_chip_shot_challenge, x, y, z);
    Hu3DModelRotSet(D_8010AAD0_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AACC_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    func_8001C258_main(D_8010AACC_chip_shot_challenge, 4, 0);
    func_8001C258_main(D_8010AAD0_chip_shot_challenge, 4, 0);
}

/* hide the distance display and the signs */
void func_8010802C_chip_shot_challenge(void) {
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 0, 0x8000);
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 1, 0x8000);
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 2, 0x8000);
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 3, 0x8000);
    HuSprAttrSet(D_8010AAC4_chip_shot_challenge, 0, 0x8000);
    HuSprAttrSet(D_8010AAC4_chip_shot_challenge, 1, 0x8000);
    func_8001C258_main(D_8010AACC_chip_shot_challenge, 4, 4);
    func_8001C258_main(D_8010AAC8_chip_shot_challenge, 4, 4);
    if (func_800E6E8C_minigame() >= 2) {
        func_8001C258_main(D_8010AAD0_chip_shot_challenge, 4, 4);
    }
}

/* the ball: an item actor */
void func_80108108_chip_shot_challenge(omObjData* obj) {
    CsBall* w;
    s32 i;

    obj->data = HuMemAllocTag(sizeof(CsBall), 31000);
    memset(obj->data, 0, sizeof(CsBall));
    w = obj->data;
    obj->model[0] = func_8000B0A0_main(0x3C0008, 0xAB9);
    obj->model[1] = func_8000B0D4_main(9, 0xAB9);
    func_800E3584_minigame(obj->model[1]);
    w->unk44 = 0.3f;
    w->unk48 = 60.0f;
    w->unk34 = 50.0f;
    w->unk3C = 0.0f;
    w->unk78 = 0;
    w->unk52 = 7;
    w->unk7C = 0;
    w->unk50 = 0;
    w->unk40 = 0.0f;
    w->unk38 = 1000.0f;
    w->unk74 = 0.5f;
    w->unk54 = 1;
    for (i = 0; i < 9; i++) {
        w->unk84[i] = NULL;
    }
    func_800E149C_minigame(obj, 0, 2);
    obj->scale.x = obj->scale.y = obj->scale.z = 0.5f;
    Hu3DModelScaleSet(obj->model[1], 0.4f, 0.4f, 0.4f);
    obj->func = func_801094D8_chip_shot_challenge;
}

/* a player: models, motions, the club */
MgWork* func_80108274_chip_shot_challenge(omObjData* obj, s32 player) {
    MgWork* w;
    s32 i;
    s32 chr;
    s32 f0;
    s32 f2;
    s32 tag;
    s32 c;

    c = GwPlayer[player].chr;
    f2 = D_800A178C_main[c][2];
    f0 = D_800A178C_main[c][0];
    tag = 0xAA9;
    chr = c;
    for (i = 0; i < obj->mdlcnt; i++) {
        obj->model[i] = 0;
    }
    obj->data = w = HuMemAllocTag(sizeof(MgWork), 31000);
    memset(w, 0, sizeof(MgWork));
    w->unkE8 = HuMemAllocTag(obj->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), 31000);
    obj->model[0] = func_8000B0A0_main(f0 | f2, tag);
    obj->model[1] = func_8000B0A0_main(9, tag);
    func_80017790_main(obj->model[0], 2, chr, func_80017B6C_main(chr, 2, 0));
    obj->model[4] = func_80017AD8_main(func_80017B6C_main(chr, 2, 1));
    func_800E5978_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5978_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5978_minigame(obj, 2, func_80017BB8_main(chr, 0x5E), 1, 0);
    func_800E5978_minigame(obj, 3, func_80017BB8_main(chr, 0x5F), 0, 0);
    func_800E5978_minigame(obj, 5, func_80017BB8_main(chr, 0x2F), 0, 0);
    func_800E5978_minigame(obj, 6, func_80017BB8_main(chr, 0x36), 0, 0);
    obj->model[2] = func_8000B0A0_main((chr + 10) | 0x3C0000, tag);
    obj->model[3] = func_8000B0A0_main((chr + 18) | 0x3C0000, 0x4AD);
    func_8001EF6C_main(obj->model[2], obj->model[0], "item_hook");
    func_8001C258_main(obj->model[2], 0x4000, 0x4000);
    func_8001FA68_main(obj->model[3]);
    func_8001F9E4_main(obj->model[3], 0x80);
    w->unk40 = 50.0f;
    obj->func = func_801087AC_chip_shot_challenge;
    w->unk50 = 0;
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    obj->rot.y = 90.0f;
    w->unk59 = player;
    w->unk57 = GwPlayer[player].pad;
    return w;
}

void func_801085C0_chip_shot_challenge(omObjData* obj) {
    MgWork* w = func_80108274_chip_shot_challenge(obj, D_8010A928_chip_shot_challenge[0]);

    obj->trans.x = -300.0f;
    obj->trans.z = 20.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    w->unk53 = 0;
}

void func_80108638_chip_shot_challenge(omObjData* obj) {
    MgWork* w = func_80108274_chip_shot_challenge(obj, D_8010A928_chip_shot_challenge[1]);

    obj->trans.x = -600.0f;
    obj->trans.z = 20.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    w->unk53 = 1;
}

void func_801086B4_chip_shot_challenge(omObjData* obj) {
    MgWork* w = func_80108274_chip_shot_challenge(obj, D_8010A928_chip_shot_challenge[2]);

    obj->trans.x = -900.0f;
    obj->trans.z = 20.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    w->unk53 = 2;
}

void func_80108730_chip_shot_challenge(omObjData* obj) {
    MgWork* w = func_80108274_chip_shot_challenge(obj, D_8010A928_chip_shot_challenge[3]);

    obj->trans.x = -1200.0f;
    obj->trans.z = 20.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    w->unk53 = 3;
}

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
