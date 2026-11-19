#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"

typedef struct BtStrip {
    /* 0x00 */ s16 sprite; /* index into D_8010FB98_bowser_toss */
    /* 0x02 */ s16 frame;
} BtStrip;

extern f32 D_8010F34C_bowser_toss;
extern BtStrip D_8010F350_bowser_toss[8];

extern s32 D_8010F3EC_bowser_toss; /* debug camera mode */
extern s32 D_8010F3F0_bowser_toss; /* debug camera index */
extern s32 D_8010F3F4_bowser_toss; /* debug text x; D_8010F3F6 = low half */
extern s32 D_8010F3F8_bowser_toss; /* debug text y; D_8010F3FA = low half */
extern s32 fontcolor;

extern s16 D_8010F378_bowser_toss[3][8][2];
extern s32 D_8010F3D8_bowser_toss[5];

/* Split a score counter's shown value into five digit sprites (sprite 7 is the leading digit). */
#define BT_DIGITS(sc, d, v, j)                                \
    v = (sc)->unk0C;                                             \
    for (j = 0; j < 5; j++) {                                    \
        d[j] = v / D_8010F3D8_bowser_toss[j];                    \
        v -= d[j] * D_8010F3D8_bowser_toss[j];                   \
        if (d[j] >= 10) {                                        \
            d[j] = 9;                                            \
        } else if (d[j] < 0) {                                   \
            d[j] = 0;                                            \
        }                                                        \
        if (j == 0) {                                            \
            if (d[0] > 0) {                                      \
                HuSprAttrReset((sc)->unk00, 7, 0x8000);          \
            }                                                    \
            func_80054FF8_main((sc)->unk00, 7, (s16)d[j]);       \
        } else {                                                 \
            func_80054FF8_main((sc)->unk00, j - 1, (s16)d[j]);   \
        }                                                        \
    }

#define BT_RANDF() ((f32)(u8)(rand8() % 100) * 0.01)

/* A dust puff where a Bowser lands. */
#define BT_DUST_VEL(bw, pos, vel, s, a, b)                                        \
    pos.x = ((bw)->unk30.x + 100.0f) - BT_RANDF() * 200.0;                         \
    pos.z = (bw)->unk30.z + BT_RANDF() * 200.0 * 0.5;                              \
    pos.y = 0.0f;                                                                  \
    a = -(BT_RANDF() * 90.0);                                                      \
    b = BT_RANDF() * 360.0;                                                        \
    s = BT_RANDF() * 5.000000074505806 + 5.000000074505806;                        \
    vel.x = sindf(b) * cosdf(a) * s;                                               \
    vel.y = -sindf(a) * s;                                                         \
    vel.z = cosdf(b) * cosdf(a) * s

#define BT_DUST(bw, p, pos, vel, scale, s, a, b) \
    BT_DUST_VEL(bw, pos, vel, s, a, b);          \
    func_8010A2D4_bowser_toss(&pos, &vel, &scale, 1.0f, (p)->unk00)





#define BT_WRAP(v)             \
    if ((v) >= 360.0) {        \
        (v) -= 360.0;          \
    } else if ((v) < 0.0) {    \
        (v) += 360.0;          \
    }

typedef struct RGBA {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

/* A sprite-sheet effect (D_8010FB94_bowser_toss, 32 x 0x30). */
typedef struct BtEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ f32 frame;
    /* 0x08 */ f32 speed;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ Vec scale;
} BtEffect; // Size 0x30

s32 func_8010DDFC_bowser_toss(HuSprite_Unk84_Struct* arg0, RGBA* arg1, u8 arg2);
void func_8010A17C_bowser_toss(omObjData* obj);
void func_8010A500_bowser_toss(omObjData* obj);
void func_8010A908_bowser_toss(omObjData* obj);

extern RGBA D_8010F150_bowser_toss;
extern Vec D_8010F278_bowser_toss[];
extern RGBA D_8010F320_bowser_toss;
extern Gfx D_8010F4F0_bowser_toss[];
extern omObjData* D_8010FB90_bowser_toss;
extern BtEffect* D_8010FB94_bowser_toss;


f32 func_8010D5DC_bowser_toss(f32 a, f32 b);
f32 func_8010D8A0_bowser_toss(f32 t, f32 a, f32 b);
f32 func_8010D8B8_bowser_toss(f32 t, f32 a, f32 b);
u16 func_8010AD54_bowser_toss(s32 dirAndFile);
s32 func_8010EA0C_bowser_toss(HuSprite_Unk84_Struct* arg0, u16 arg1, RGBA* arg2);
void func_8010EC10_bowser_toss(u16 modelId, HuSprite_Unk84_Struct* arg1, u16 arg2, RGBA* arg3);
s32 func_8010ED44_bowser_toss(HuSprite_Unk84_Struct* arg0, HmfData* arg1, f32 arg2, u16 arg3, u16 arg4);

// m7 bw: Bowser Toss (1 vs 1 x 2: spin and throw Bowser; two players on split screens)

/* A player's work (D_8010FB74_bowser_toss, 2 x 0x5C; packed into obj->work). */
typedef struct BtPlayer {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ s16 unk02; /* result motion: 0 win, 1 lose, -1 none */
    /* 0x04 */ f32 unk04; /* distance */
    /* 0x08 */ s32 unk08; /* frame counter */
    /* 0x0C */ s16 unk0C; /* state */
    /* 0x0E */ u16 unk0E; /* press counter */
    /* 0x10 */ s16 unk10; /* spin sound, -1 none */
    /* 0x12 */ char unk12[2];
    /* 0x14 */ s32 unk14; /* win voice file */
    /* 0x18 */ s16 unk18; /* GwPlayer index */
    /* 0x1A */ s16 unk1A; /* controller port */
    /* 0x1C */ s16 unk1C; /* character */
    /* 0x1E */ s16 unk1E; /* CPU */
    /* 0x20 */ s16 unk20; /* CPU difficulty */
    /* 0x22 */ char unk22[2];
    /* 0x24 */ f32 unk24; /* minimum angle */
    /* 0x28 */ f32 unk28; /* maximum angle */
    /* 0x2C */ f32 unk2C; /* angle range */
    /* 0x30 */ s16 unk30; /* motion blend frames */
    /* 0x32 */ s16 unk32;
    /* 0x34 */ f32 unk34; /* vertical speed */
    /* 0x38 */ f32 unk38; /* horizontal speed */
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ char unk3E[2];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ f32 unk44; /* spin speed */
    /* 0x48 */ f32 unk48; /* target angle */
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ char unk4E[2];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54; /* CPU: stick */
    /* 0x58 */ f32 unk58; /* CPU: release speed */
} BtPlayer; // Size 0x5C

typedef f32 Matrix4f[4][4];
/* Matrix bake record (src/14EA0.c's unk1EA70StructC). */
typedef struct unk1EA70StructC {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16* unk_04;
    /* 0x08 */ Matrix4f* unk_08;
} unk1EA70StructC; // sizeof 0xC

/* A thrown Bowser (D_8010FB8C_bowser_toss, 2 x 0x64). */
typedef struct BtBowser {
    /* 0x00 */ omObjData* unk00; /* thrower */
    /* 0x04 */ s16 unk04; /* models */
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A; /* state */
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[2];
    /* 0x28 */ f32 unk28; /* spin speed, 0..1 */
    /* 0x2C */ f32 unk2C; /* angle, 0..1 */
    /* 0x30 */ Vec unk30; /* position */
    /* 0x3C */ f32 unk3C; /* rotation x */
    /* 0x40 */ f32 unk40; /* rotation y */
    /* 0x44 */ f32 unk44; /* spin */
    /* 0x48 */ f32 unk48; /* horizontal speed */
    /* 0x4C */ f32 unk4C; /* vertical speed */
    /* 0x50 */ s32 unk50;
    /* 0x54 */ char unk54[8];
    /* 0x5C */ unk1EA70StructC* unk5C;
    /* 0x60 */ void* unk60;
} BtBowser; // Size 0x64

typedef struct BtBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} BtBytes;

typedef union BtPack {
    void* p;
    BtBytes b;
} BtPack;

f32 fabsf(f32);
f64 fabs(f64);
f64 fmod(f64, f64);
extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
omObjData* func_80045F1C_main(u32, s16, s16);
u16 GWMgRecordGet(s16 arg0);
s32 func_8000B710_main(s32 arg0);
void func_800E6F0C_minigame(s32);
void func_8001EED8_main(s16 arg0, s16 arg1, s16 arg2);
void func_8001EF6C_main(s16 arg0, s16 arg1, const char* arg2);
s32 func_800E2250_minigame(omObjData* obj, s16 x, s16 y);

void func_80105C80_bowser_toss(omObjData* obj);
void func_80105CEC_bowser_toss(omObjData* obj);
void func_8010649C_bowser_toss(omObjData* obj);
void func_801064C0_bowser_toss(omObjData* obj);
void func_80106568_bowser_toss(void);
void func_801067B0_bowser_toss(omObjData* obj);
void func_80106BC4_bowser_toss(omObjData* obj);
void func_80107E84_bowser_toss(omObjData* obj);
f32 func_801080D0_bowser_toss(f32 arg0, f32 arg1, f32 arg2);
s32 func_8010840C_bowser_toss(void);
s32 func_80108444_bowser_toss(void);
void func_8010847C_bowser_toss(omObjData* obj, s16 a, s16 b);
void func_801084DC_bowser_toss(void);
void func_8010858C_bowser_toss(s16 idx);
BtBowser* func_80108800_bowser_toss(s16 idx);
void func_8010882C_bowser_toss(omObjData* obj);
s32 func_80109F20_bowser_toss(void);
void func_8010A028_bowser_toss(void);
s32 func_8010A2D4_bowser_toss(Vec* pos, Vec* vel, Vec* scale, f32 speed, s16 player);
void func_8010A4A8_bowser_toss(void);
void func_8010AD98_bowser_toss(void);
void func_8010B41C_bowser_toss(void);
void func_8010C1A0_bowser_toss(s16 idx, s32 value);
s32 func_8010C23C_bowser_toss(void);
void func_8010C274_bowser_toss(void);
s32 func_8010C2A4_bowser_toss(void);
void func_8010C2DC_bowser_toss(void);
void func_8010D250_bowser_toss(s32 idx, f32 x, f32 y, f32 a, f32 b, f32 c, f32 d, f32 zoom, s32 frames);
f32 func_8010D6E0_bowser_toss(f32 target, f32 cur, f32 step);
void func_8010D960_bowser_toss(omObjData* obj, u32 value);
void* func_8010D98C_bowser_toss(omObjData* obj);
unk1EA70StructC* func_8010D9E0_bowser_toss(s16 model, s16 step, const char* part, s16 useOverlay, u16 frame);
void func_8010DDC4_bowser_toss(unk1EA70StructC* arg0);

extern s32 D_800A178C_main[][6];

extern s16 D_8010F530_bowser_toss[];
extern s16 D_8010F53C_bowser_toss[];
extern s32 D_8010F154_bowser_toss[];
extern s32 D_8010F174_bowser_toss[];
extern s32 D_8010F194_bowser_toss;
extern Vec D_8010F198_bowser_toss[];
extern s32 D_8010F1B0_bowser_toss[];
extern s32 D_8010F1C0_bowser_toss[];
extern f32 D_8010F1E0_bowser_toss[];
extern f32 D_8010F200_bowser_toss[];
extern s32 D_8010F220_bowser_toss[];
extern s32 D_8010F228_bowser_toss[];
extern f32 D_8010F230_bowser_toss[];
extern f32 D_8010F240_bowser_toss[];
extern f32 D_8010F250_bowser_toss[];
extern f32 D_8010F260_bowser_toss[];
extern f32 D_8010F270_bowser_toss[2];

extern omObjData* D_8010FB50_bowser_toss;
extern s32 D_8010FB54_bowser_toss;
extern s32 D_8010FB58_bowser_toss;
extern s32 D_8010FB5C_bowser_toss;
extern s32 D_8010FB60_bowser_toss;
extern u32 D_8010FB64_bowser_toss;
extern s32 D_8010FB68_bowser_toss;
extern s32 D_8010FB6C_bowser_toss;
extern s16 D_8010FB70_bowser_toss;
extern s16 D_8010FB72_bowser_toss;
extern BtPlayer* D_8010FB74_bowser_toss;
extern s16 D_8010FB78_bowser_toss;
extern s32 D_8010FB7C_bowser_toss;
extern s32 D_8010FB80_bowser_toss;
extern s32 D_8010FB84_bowser_toss;
extern omObjData* D_8010FB88_bowser_toss;
extern BtBowser* D_8010FB8C_bowser_toss;
extern s16* D_8010FB98_bowser_toss;
extern D_80111B50_vine_with_me_Struct D_8010FBB8_bowser_toss;

/* A score counter (D_8010FBA0_bowser_toss, 3 x 0x10). */
typedef struct BtScore {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02; /* timer */
    /* 0x04 */ s16 unk04; /* state */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s32 unk08; /* shown value */
    /* 0x0C */ s32 unk0C; /* target value */
} BtScore; // Size 0x10

void func_8008A070_main(Matrix4f);
void func_80017D24_main(Matrix4f, f32, f32, f32);
void func_80017CD0_main(Matrix4f, f32, f32, f32);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
void func_8002367C_main(Matrix4f, Matrix4f);
void func_80109DB8_bowser_toss(omObjData* obj, f32 rot, Matrix4f out);
void func_80109E4C_bowser_toss(BtBowser* bw, Matrix4f out, f32 frame);
s16 func_80109F68_bowser_toss(f32 x, f32 y, f32 vx, f32 vy);
void func_8010D918_bowser_toss(f32* a, f32* b, f32* out, f32 t);

extern BtScore* D_8010FBA0_bowser_toss;

/* A camera key: CenterM, CRotM, CZoomM of one screen. */
typedef struct BtCamKey {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} BtCamKey; // Size 0x24

/* One screen's camera move (D_8010FBA4_bowser_toss, 2 x 0x54): from key[0] to key[1]. */
typedef struct BtCam {
    /* 0x00 */ BtCamKey key[2];
    /* 0x48 */ s32 unk48; /* frames left */
    /* 0x4C */ s32 unk4C; /* frames */
    /* 0x50 */ s32 unk50;
} BtCam; // Size 0x54

typedef struct BtRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} BtRect;

extern Matrix4f* D_800D1358_main;
extern s16* D_800D04B4_main;
extern s16 D_800CD1B0_main;
extern s16 D_800D138A_main;
extern Matrix4f D_800D5A00_main[];
void func_8002DFF8_main(HmfData*, f32, D_800CCF58_main_Struct*, s32);
s16 func_8002C834_main(HmfData*, const char*);
void func_80016C2C_main(HmfData* arg0, s16 arg1, s16 arg2);
void func_8010CDB8_bowser_toss(omObjData* obj);
void func_8010D080_bowser_toss(s32 side, s32 key);
void func_8010DB9C_bowser_toss(s16 model, s16 step, unk1EA70StructC* rec, s16 part, s16 useOverlay, s16 frame);

extern BtRect D_8010F33C_bowser_toss[];
extern s16 D_8010FB9C_bowser_toss[2];
extern BtCam* D_8010FBA4_bowser_toss;
extern Vec D_8010FBA8_bowser_toss;

void func_8010AF38_bowser_toss(s16 side, Vec* center, Vec* rot);

extern s16 D_8010F324_bowser_toss[2][5];
extern RGBA D_8010F338_bowser_toss;
void func_8010D43C_bowser_toss(s32 side);

void func_801059A0_bowser_toss(void) {
    omObjData* obj;
    s32 i;

    Hu3DAnimInit(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(0x10);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, 0xA0);
    obj->work[0] = 2;
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 121.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    for (i = 0; i < 2; i++) {
        Hu3DCamSetPerspective(i, 45.0f, 80.0f, 4000.0f);
    }
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_8010FB60_bowser_toss = 300;
    D_8010FB5C_bowser_toss = 0;
    D_8010FB58_bowser_toss = 0;
    D_8010FB64_bowser_toss = 0;
    D_8010FB68_bowser_toss = 0;
    D_8010FB6C_bowser_toss = 0;
    D_8010FB78_bowser_toss = -1;
    D_8010FB7C_bowser_toss = 0;
    D_8010FB70_bowser_toss = -1;
    D_8010FB84_bowser_toss = -1;
    D_8010FB80_bowser_toss = GWMgRecordGet(4);
    D_8010FB72_bowser_toss = 0;
    D_8010FB50_bowser_toss = omAddObj(0x40, 0, 0, -1, func_80105C80_bowser_toss);
    memset(&D_8010FBB8_bowser_toss, 0, 0x28);
    D_8010FBB8_bowser_toss.unk01 = 4;
    func_800E5EA0_minigame(&D_8010FBB8_bowser_toss);
    D_8010FB98_bowser_toss = HuMemAllocTag(0x20, 31000);
    memset(D_8010FB98_bowser_toss, 0, 0x20);
    func_80045010_main(D_8010F530_bowser_toss, 1);
    func_80045010_main(D_8010F53C_bowser_toss, 1);
}

void func_80105C80_bowser_toss(omObjData* obj) {
    obj->func = func_80105CEC_bowser_toss;
    func_8010AD98_bowser_toss();
    func_8010B41C_bowser_toss();
    func_8010A028_bowser_toss();
    func_8010A4A8_bowser_toss();
    func_801084DC_bowser_toss();
    func_80106568_bowser_toss();
    func_8010C2DC_bowser_toss();
    if (_CheckFlag(0xA) != 0) {
        D_8010FB54_bowser_toss = 1;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F530_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F53C_bowser_toss);

void func_80105CEC_bowser_toss(omObjData* obj) {
    BtPlayer* p0;
    BtPlayer* p1;
    omObjData* wobj;
    BtBowser* bw;
    s32 s0;
    s32 s1;
    f32 x;
    f32 y;
    f32 z;

    switch (D_8010FB64_bowser_toss) {
    case 0:
        if (D_8010FB5C_bowser_toss == 2) {
            WipeCreateIn(0xFF, 0x10);
        }
        if (D_8010FB68_bowser_toss > 0) {
            D_8010FB68_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 1:
        GMesCreate(6);
        HuAudFXPlay(0xE);
        HuAudSeqPlay(0x30);
        D_8010FB68_bowser_toss = 0;
        D_8010FB64_bowser_toss++;
        break;
    case 2:
        if (GMesStatGet() == 0) {
            GMesCreate(0x1A, (D_8010FB60_bowser_toss + 29) / 30, 0x9C, 0x20);
            func_800E6F0C_minigame(2);
            D_8010FB64_bowser_toss++;
        }
        break;
    case 3:
        func_8003F578_main((D_8010FB60_bowser_toss-- + 28) / 30);
        if (D_8010FB60_bowser_toss <= 0) {
            p0 = func_8010D98C_bowser_toss(D_800EC598_minigame[0]);
            p1 = func_8010D98C_bowser_toss(D_800EC598_minigame[1]);
            p0->unk0C = 3;
            p1->unk0C = 3;
            func_8003F5C0_main();
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 4:
        if ((s16)func_80109F20_bowser_toss() != 0 && (s16)func_8010840C_bowser_toss() != 0) {
            GMesCreate(0x11);
            func_800E6F0C_minigame(3);
            HuAudSeqFadeOut(0x78);
            func_8010847C_bowser_toss(D_800EC598_minigame[0], 0, 0xA);
            func_8010847C_bowser_toss(D_800EC598_minigame[1], 0, 0xA);
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 5:
        if (GMesStatGet() == 0) {
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 6:
        if (D_8010FB5C_bowser_toss >= 15) {
            p0 = func_8010D98C_bowser_toss(D_800EC598_minigame[0]);
            p1 = func_8010D98C_bowser_toss(D_800EC598_minigame[1]);
            s0 = p0->unk04;
            s1 = p1->unk04;
            if (p0->unk04 == 0.0f && p1->unk04 == 0.0f) {
                D_8010FB78_bowser_toss = -1;
                D_8010FB7C_bowser_toss = -1;
                p0->unk02 = p1->unk02 = 1;
            } else if (s0 == s1) {
                if (rand8() & 1) {
                    s0 = s1 + 1;
                    p0->unk04 += 1.0f;
                } else {
                    s1++;
                    p1->unk04 += 1.0f;
                }
            }
            if (s0 > s1) {
                D_8010FB78_bowser_toss = p0->unk00;
                GwPlayer[p0->unk18].bonusCoin += 10;
                p0->unk02 = 0;
                p1->unk02 = 1;
                D_8010FB7C_bowser_toss = s0;
            } else if (s0 < s1) {
                D_8010FB78_bowser_toss = p1->unk00;
                GwPlayer[p1->unk18].bonusCoin += 10;
                p0->unk02 = 1;
                p1->unk02 = 0;
                D_8010FB7C_bowser_toss = s1;
            }
            func_8010C1A0_bowser_toss(p0->unk00, s0);
            func_8010C1A0_bowser_toss(p1->unk00, s1);
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 7:
        if ((s16)func_8010C23C_bowser_toss() != 0) {
            if (D_8010FB70_bowser_toss != -1) {
                HuAudFXPlay(0x4AC);
                D_8010FB70_bowser_toss = -1;
            }
            func_8010C274_bowser_toss();
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 8:
        if ((s16)func_80108444_bowser_toss() != 0 && (s16)func_8010C2A4_bowser_toss() != 0) {
            if (D_8010FB78_bowser_toss == -1) {
                GMesCreate(0x20);
                HuAudSeqPlay(0x6C);
                D_8010FB68_bowser_toss = 0x90;
                func_800E6F0C_minigame(4);
                D_8010FB64_bowser_toss = 11;
            } else {
                if (D_8010FB78_bowser_toss != 0) {
                    D_8010FB78_bowser_toss = 1;
                }
                if (D_8010FB80_bowser_toss < D_8010FB7C_bowser_toss) {
                    D_8010FB80_bowser_toss = D_8010FB7C_bowser_toss;
                    func_8010C1A0_bowser_toss(2, D_8010FB7C_bowser_toss);
                    GWMgRecordSet(4, (u16)D_8010FB80_bowser_toss);
                    GMesCreate(0x1B);
                    D_8010FB72_bowser_toss = 1;
                    D_8010FB68_bowser_toss = 99;
                    D_8010FB64_bowser_toss = 9;
                } else {
                    HuAudSeqPlay(0x67);
                    D_8010FB68_bowser_toss = 0x8C;
                    D_8010FB64_bowser_toss = 10;
                }
                wobj = D_800EC598_minigame[D_8010FB78_bowser_toss];
                bw = &D_8010FB8C_bowser_toss[D_8010FB78_bowser_toss];
                func_8010D98C_bowser_toss(wobj);
                x = wobj->trans.x * 0.5f + bw->unk30.x * 0.5f;
                if (wobj->trans.x != 0.0f) {
                    y = wobj->trans.y * 0.5f + 100.0;
                } else {
                    y = wobj->trans.y * 0.5f + 150.0;
                }
                z = CZoom * 0.5f;
                if (D_8010FB78_bowser_toss == 1) {
                    y -= 15.000000596046448;
                }
                func_8010D250_bowser_toss(D_8010FB78_bowser_toss, x, y, 65535.0f, 65535.0f, 65535.0f, 65535.0f,
                                          z, 30);
                func_800E6F0C_minigame(4);
            }
            D_8010FB5C_bowser_toss = 0;
        }
        break;
    case 9:
        if (D_8010FB5C_bowser_toss >= 75.0f) {
            D_8010FB64_bowser_toss = 10;
            D_8010FB5C_bowser_toss = 0;
        }
        break;
    case 10:
        GMesCreate(0x16, ((BtPlayer*)func_8010D98C_bowser_toss(D_800EC598_minigame[D_8010FB78_bowser_toss]))->unk1C);
        if (D_8010FB72_bowser_toss != 0) {
            HuAudSeqPlay(0x6A);
        }
        D_8010FB5C_bowser_toss = 0;
        D_8010FB64_bowser_toss++;
        break;
    case 11:
        if (GMesStatGet() == 0) {
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    case 12:
        if (D_8010FB5C_bowser_toss >= 15) {
            WipeCreateOut(0, 0x10);
            HuAudSeqFadeOut(0x10);
            func_8004AB0C_main(0x10);
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
        }
        break;
    default:
        if (WipeStatGet() == 0) {
            obj->func = func_8010649C_bowser_toss;
        }
        break;
    }
    func_801064C0_bowser_toss(obj);
    D_8010FB58_bowser_toss++;
    D_8010FB5C_bowser_toss++;
}

void func_8010649C_bowser_toss(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_801064C0_bowser_toss(omObjData* obj) {
    if (D_8010F194_bowser_toss != 0) {
        if (D_8010F194_bowser_toss == 1) {
            obj->func = func_8010649C_bowser_toss;
        }
        D_8010F194_bowser_toss--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010F194_bowser_toss = 0x10;
        WipeCreateOut(0, (s16)D_8010F194_bowser_toss);
        HuAudSeqFadeOut((s16)D_8010F194_bowser_toss);
        func_8004AB0C_main((s16)D_8010F194_bowser_toss);
    }
}

void func_80106568_bowser_toss(void) {
    s32 picked[2] = { -1, -1 };
    BtPlayer* p;
    s32 i;
    s32 j;
    s32 k;
    s32 found;
    s32 min;

    p = D_8010FB74_bowser_toss = HuMemAllocTag(sizeof(BtPlayer) * 2, 31000);
    memset(p, 0, sizeof(BtPlayer) * 2);
    for (i = 0; i < 2; i++) {
        for (j = 0, min = 99; j < 4; j++) {
            found = 0;
            for (k = 0; k < i; k++) {
                if (picked[k] == D_8010F1B0_bowser_toss[j]) {
                    found = 1;
                }
            }
            if (!found) {
                if (GwPlayer[D_8010F1B0_bowser_toss[j]].group < min) {
                    min = GwPlayer[D_8010F1B0_bowser_toss[j]].group;
                    D_8010FB74_bowser_toss[i].unk18 = D_8010F1B0_bowser_toss[j];
                }
            }
        }
        picked[i] = D_8010FB74_bowser_toss[i].unk18;
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    for (i = 0; i < 2; i++, p++) {
        p->unk00 = i;
        D_800EC598_minigame[D_800EC280_minigame] = omAddObj(i + 0x10, 11, 60, -1, func_801067B0_bowser_toss);
        D_800EC598_minigame[D_800EC280_minigame]->trans.x = D_8010F198_bowser_toss[i].x;
        D_800EC598_minigame[D_800EC280_minigame]->trans.y = D_8010F198_bowser_toss[i].y;
        D_800EC598_minigame[D_800EC280_minigame]->trans.z = D_8010F198_bowser_toss[i].z;
        D_800EC598_minigame[D_800EC280_minigame]->rot.y = 90.0f;
        func_8010D960_bowser_toss(D_800EC598_minigame[D_800EC280_minigame], (u32)p);
        D_800EC280_minigame++;
    }
}

/* NON_MATCHING: only the voice-table index shift is scheduled one instruction earlier (as in Bonkers). */
#ifdef NON_MATCHING
void func_801067B0_bowser_toss(omObjData* obj) {
    func_800E1BA8_minigame_ObjData* w;
    BtPlayer* p;
    s32* voice;
    u32 file0;
    s32 file1;
    u32 file2;
    s16 gw;
    s16 chr;
    f32 z;

    p = func_8010D98C_bowser_toss(obj);
    gw = p->unk18;
    chr = GwPlayer[gw].chr;
    p->unk1C = chr;
    p->unk1A = GwPlayer[gw].pad;
    p->unk1E = GwPlayer[gw].stat & 1;
    p->unk20 = GwPlayer[gw].cpu_difficulty;
    file0 = D_800A178C_main[chr][0];
    file1 = D_800A178C_main[chr][1];
    file2 = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(obj, file0, file1, gw, 0x289, 0x299);
    w = obj->data;
    w->unk50 &= ~1;
    w->unkEC = NULL;
    obj->model[3] = func_8000B108_main(3, 0x68D);
    obj->model[4] = func_8000B108_main(4, 0x68D);
    obj->model[10] = func_8000B108_main(file0 | file2, 0x2AD);
    func_8001C8A8_main(obj->model[0], 1 << p->unk00);
    func_8001C8A8_main(obj->model[1], 1 << p->unk00);
    func_8001C8A8_main(obj->model[10], 1 << p->unk00);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 3, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x6D), 1, 0);
    func_800E5A00_minigame(obj, 5, func_80017BB8_main(chr, 0x64), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 0x65), 1, 0x1E);
    voice = &D_8010F220_bowser_toss[rand8() & 1];
    func_800E5A00_minigame(obj, 7, func_80017BB8_main(chr, (s16)*voice), 1, 0x78);
    p->unk14 = D_8010F1C0_bowser_toss[chr] | *voice;
    func_800E5A00_minigame(obj, 8, func_80017BB8_main(chr, (s16)D_8010F228_bowser_toss[rand8() & 1]), 1, 0x78);
    func_800E5690_minigame(obj, 5);
    HmfModelData[obj->model[0]].unk02 = obj->motion[5];
    func_8001EED8_main(obj->model[0], obj->motion[6], 1);
    HmfModelData[obj->model[0]].unk5C = 0.0f;
    HmfModelData[obj->model[0]].unk58 = 0.0f;
    p->unk24 = D_8010F1E0_bowser_toss[chr];
    p->unk28 = D_8010F200_bowser_toss[chr];
    p->unk2C = p->unk28 - p->unk24;
    p->unk30 = p->unk32 = 0;
    p->unk3C = 1;
    p->unk40 = 0;
    p->unk44 = 0;
    p->unk04 = 0;
    p->unk34 = p->unk38 = z = p->unk04;
    p->unk0E = 0;
    p->unk02 = -1;
    p->unk08 = 0;
    p->unk50 = 0;
    p->unk48 = z;
    p->unk0C = 0;
    p->unk10 = -1;
    p->unk4C = 0;
    func_8010858C_bowser_toss(p->unk00);
    func_80108800_bowser_toss(p->unk00);
    obj->func = func_80106BC4_bowser_toss;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801067B0_bowser_toss);
#endif


/* NON_MATCHING: register allocation in the spin-target and pitch arithmetic; retail reloads p->unk10 for the
 * HuAudFXPitchSet argument where this keeps the tested value. */
#ifdef NON_MATCHING
void func_80106BC4_bowser_toss(omObjData* obj) {
    Vec pos = { 0.0f, 0.0f, 0.0f };
    Vec vel = { 0.0f, 0.0f, 0.0f };
    Vec scale = { 0.0f, 0.0f, 0.0f };
    BtPlayer* p;
    BtBowser* bw;
    func_800E1BA8_minigame_ObjData* w;
    HmfModel* model;
    f32 sx;
    f32 sy;
    f32 t;
    f32 d;
    f32 tgt;
    f32 ang;
    s32 ret;

    p = func_8010D98C_bowser_toss(obj);
    bw = func_80108800_bowser_toss(p->unk00);
    w = obj->data;
    model = &HmfModelData[obj->model[0]];
    switch (func_800E6E8C_minigame()) {
    case 0:
        if (p->unk0C == 0) {
            if (p->unk08 >= 30.0f) {
                p->unk08 = 0;
                p->unk0C = 1;
            }
        } else if (D_8010FB74_bowser_toss[0].unk0C > 0 && D_8010FB74_bowser_toss[1].unk0C > 0 &&
                   D_8010FB68_bowser_toss <= 0) {
            D_8010FB68_bowser_toss++;
        }
        break;
    case 2:
        if (p->unk1E != 0) {
            func_80107E84_bowser_toss(obj);
        }
        switch (p->unk0C) {
        case 1:
            if (D_800D5558_main[p->unk1A] & 0x8000) {
                if (func_800E5690_minigame(obj, 4) != 0) {
                    p->unk30 = 10;
                    p->unk32 = 1;
                    p->unk44 += 0.5f;
                    if (p->unk44 >= 45.0f) {
                        p->unk44 = 45.0f;
                    } else if (p->unk44 < 3.0f) {
                        p->unk44 = 3.0f;
                    }
                    p->unk4C = 1;
                    model->unk5C = 0.0f;
                    p->unk0C = 2;
                    p->unk10 = func_8004AC5C_main(0x4A6, p->unk00);
                } else {
                    p->unk44 = 0.0f;
                }
            }
            break;
        case 2:
            sx = fabs(D_800CBB6E_main[p->unk1A]);
            if (fabs(sx) < 8.0) {
                sx = 0.0f;
            } else if (sx > 60.0f) {
                sx = 60.0f;
            } else if (sx < -60.0f) {
                sx = -60.0f;
            }
            if (sx >= 8.0f) {
                sx -= 8.0f;
            }
            sy = fabs(D_800D20A1_main[p->unk1A]);
            if (fabs(sy) < 8.0) {
                sy = 0.0f;
            } else if (sy > 60.0f) {
                sy = 60.0f;
            } else if (sy < -60.0f) {
                sy = -60.0f;
            }
            if (sy >= 8.0f) {
                sy -= 8.0f;
            }
            ret = func_800E2250_minigame(obj, sx, sy);
            sx = ret >> 16;
            sy = ret & 0xFFFF;
            t = sqrtf(sx * sx + sy * sy) / 52.0f;
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > 1.0f) {
                t = 1.0f;
            }
            p->unk48 = tgt = t * p->unk2C + p->unk24;
            if (model->unk04 == 0xFF) {
                d = model->unk58 - tgt;
                if (fabs(d) < 1.75) {
                    model->unk58 = tgt;
                } else if (d < 0.0f) {
                    model->unk58 += 1.75f;
                } else {
                    model->unk58 -= 1.75f;
                }
            } else {
                model->unk58 = 0.0f;
            }
            p->unk44 -= 0.075f;
            t = 2.0 * (1.0 - bw->unk28);
            if (t < 1.0f) {
                t = 1.0f;
            } else if (t > 2.0f) {
                t = 2.0f;
            }
            t *= 0.5f;
            if (D_800D5558_main[p->unk1A] & 0x8000) {
                p->unk44 += t;
                if (!(++p->unk0E & 1)) {
                    pos.x = obj->trans.x;
                    pos.y = obj->trans.y + 20.0;
                    pos.z = obj->trans.z;
                    vel.x = sindf(obj->rot.y) * 20.0 * 0.20000000298023224;
                    vel.z = cosdf(obj->rot.y) * 20.0 * 0.20000000298023224;
                    vel.y = 0.0f;
                    scale.x = scale.y = scale.z = 0.5f;
                    func_8010A2D4_bowser_toss(&pos, &vel, &scale, 1.0f, p->unk00);
                }
            }
            if (p->unk44 >= 45.0f) {
                p->unk44 = 45.0f;
            } else if (p->unk44 < 3.0f) {
                p->unk44 = 3.0f;
            }
            model->unk44 = p->unk44 * 10.0f / 45.0f;
            if (p->unk44 >= 0.5f && model->unk44 < 0.3f) {
                model->unk44 = 0.3f;
            }
            if (model->unk44 >= 1.0f) {
                model->unk44 = 1.0f;
            }
            obj->rot.y += p->unk44;
            if (obj->rot.y >= 360.0f) {
                obj->rot.y -= 360.0f;
            }
            bw->unk28 = p->unk44 / 45.0f;
            if (bw->unk28 >= 1.0f) {
                bw->unk28 = 1.0f;
            } else if (bw->unk28 < 0.0f) {
                bw->unk28 = 0.0f;
            }
            if (p->unk10 != -1) {
                HuAudFXPitchSet(p->unk10, (s16)((f32)((1.0 - bw->unk28) * -3600.0) +
                                                (((ang = obj->rot.y) <= 180.0f) ? ang - 90.0f : -(ang - 270.0f)) *
                                                    0.011111111f * 400.0f));
            }
            bw->unk2C = (model->unk58 - p->unk24) / p->unk2C;
            if (bw->unk2C >= 1.0f) {
                bw->unk2C = 1.0f;
            } else if (bw->unk2C < 0.0f) {
                bw->unk2C = 0.0f;
            }
            break;
        case 3:
            if (p->unk4C != 0) {
                if (p->unk48 < p->unk24) {
                    p->unk48 = p->unk24;
                }
                if (model->unk04 == 0xFF) {
                    d = model->unk58 - p->unk48;
                    if (fabs(d) < 1.75) {
                        model->unk58 = p->unk48;
                    } else if (d < 0.0f) {
                        model->unk58 += 1.75f;
                    } else {
                        model->unk58 -= 1.75f;
                    }
                } else {
                    model->unk58 = 0.0f;
                }
                model->unk44 = p->unk44 * 10.0f / 45.0f;
                if (p->unk44 >= 0.5f && model->unk44 < 0.3f) {
                    model->unk44 = 0.3f;
                }
                if (model->unk44 >= 1.0f) {
                    model->unk44 = 1.0f;
                }
                bw->unk28 = p->unk44 / 45.0f;
                if (bw->unk28 >= 1.0f) {
                    bw->unk28 = 1.0f;
                } else if (bw->unk28 < 0.0f) {
                    bw->unk28 = 0.0f;
                }
                bw->unk2C = (model->unk58 - p->unk24) / p->unk2C;
                if (bw->unk2C >= 1.0f) {
                    bw->unk2C = 1.0f;
                } else if (bw->unk2C < 0.0f) {
                    bw->unk2C = 0.0f;
                }
                if (p->unk44 >= 45.0f) {
                    p->unk44 = 45.0f;
                } else if (p->unk44 < 3.0f) {
                    p->unk44 = 3.0f;
                }
                if (p->unk10 != -1) {
                    HuAudFXPitchSet(p->unk10, (s16)((f32)((1.0 - bw->unk28) * -3600.0) +
                                                    (((ang = obj->rot.y) <= 180.0f) ? ang - 90.0f : -(ang - 270.0f)) *
                                                        0.011111111f * 400.0f));
                }
                obj->rot.y += p->unk44;
                if (obj->rot.y >= 720.0f) {
                    obj->rot.y -= 720.0f;
                }
                if (obj->rot.y >= 450.0f) {
                    bw->unk0A = 1;
                    bw->unk0C = model->unk58;
                    if (p->unk10 != -1) {
                        HuAudFXStop(p->unk10);
                    }
                    p->unk10 = -1;
                    func_8004AC98_main(p->unk1C + 0xB0, p->unk00);
                    func_800E5690_minigame(obj, 0);
                    HmfModelData[obj->model[0]].unk06 = 0xFF;
                    p->unk3C = 0;
                    p->unk0C = 4;
                }
            } else {
                p->unk0C = 4;
            }
            break;
        case 4:
            if (p->unk3C != 0) {
                p->unk0C = 5;
                p->unk08 = 0;
                break;
            }
            obj->rot.y += p->unk44;
            if (obj->rot.y >= 360.0f) {
                obj->rot.y -= 360.0f;
            }
            if (p->unk44 != 0.0f) {
                p->unk44 *= 0.9f;
            }
            if (p->unk44 <= 0.1f) {
                p->unk44 = 0.0f;
                p->unk0C = 5;
                p->unk08 = 0;
            }
            break;
        case 5:
            break;
        }
        break;
    case 3:
        switch (p->unk0C) {
        case 5:
            p->unk0C = (D_8010FB78_bowser_toss == p->unk00) ? 6 : 9;
        case 6:
            if (p->unk04 < 400.0) {
                p->unk0C = 9;
            } else if (p->unk04 < 800.0) {
                func_800E5690_minigame(obj, 3);
                p->unk34 = 19.0f;
                p->unk0C = 7;
                func_8004AC98_main(p->unk1C + 0x3B, p->unk00);
                p->unk38 = ((f32)((p->unk04 - 400.0) / 400.0) + 1.0) * 9.000000357627869;
            } else {
                obj->trans.x = bw->unk30.x - 500.0;
                obj->trans.y = 700.0f;
                func_800E5690_minigame(obj, 3);
                p->unk34 = 0.0f;
                p->unk0C = 8;
                func_8004AC98_main(p->unk1C + 0xB9, p->unk00);
            }
            break;
        case 7:
            obj->trans.x += p->unk38;
            obj->trans.y += p->unk34;
            p->unk34 -= 1.79663f;
            obj->rot.y = func_8010D6E0_bowser_toss(90.0f, obj->rot.y, 10.0f);
            if (obj->trans.y <= 0.0f) {
                func_800E5690_minigame(obj, 0);
                func_8004AC98_main(p->unk1C + 0x32, p->unk00);
                obj->trans.y = 0.0f;
                p->unk0C = 9;
            }
            break;
        case 8:
            obj->trans.x += 9.000000357627869;
            obj->trans.y += p->unk34;
            p->unk34 -= 1.79663f;
            obj->rot.y = func_8010D6E0_bowser_toss(90.0f, obj->rot.y, 10.0f);
            if (obj->trans.y <= 0.0f) {
                func_800E5690_minigame(obj, 0);
                func_8004AC98_main(p->unk1C + 0x32, p->unk00);
                if (D_8010FB84_bowser_toss == -1) {
                    D_8010FB84_bowser_toss = HuAudFXPlay(0x4AA);
                }
                obj->trans.y = 0.0f;
                p->unk0C = 9;
            }
            break;
        case 9:
            if (p->unk3C != 0) {
                func_800E5690_minigame(obj, 0);
                HmfModelData[obj->model[0]].unk06 = 0xFF;
                bw->unk0A = 3;
                p->unk3C = 0;
            }
            obj->rot.y = func_8010D6E0_bowser_toss(0.0f, obj->rot.y, 10.0f);
            if (obj->rot.y < 1.0f || obj->rot.y >= 359.0f) {
                p->unk0C = 10;
            }
            break;
        case 10:
            break;
        }
        break;
    case 4:
        switch (p->unk02) {
        case 0:
            if (func_800E5690_minigame(obj, 7) != 0) {
                func_80017790_main(obj->model[0], 2, p->unk1C, D_8010F154_bowser_toss[p->unk1C]);
                func_80045F1C_main(p->unk14, -1, p->unk00);
                p->unk02 = -1;
            }
            break;
        case 1:
            if (func_800E5690_minigame(obj, 8) != 0) {
                func_80017790_main(obj->model[0], 2, p->unk1C, D_8010F174_bowser_toss[p->unk1C]);
                p->unk02 = -1;
            }
            break;
        }
        break;
    }
    func_800E4E30_minigame(obj);
    if (*(s32*)&p->unk30 != 0 && w->unkD6 == 0) {
        model = &HmfModelData[obj->model[0]];
        if (p->unk30 != 0) {
            model->unk0C = p->unk30;
        }
        if (p->unk30 == 1) {
            model->unk0E = p->unk30;
        }
        if (p->unk32 != 0) {
            model->unk44 = 0.0f;
            model->unk50 = 0.0f;
        }
        p->unk30 = p->unk32 = 0;
    }
    p->unk08++;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F5A0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80106BC4_bowser_toss);
#endif

/* NON_MATCHING: retail computes the pad index shift before the first store. */
#ifdef NON_MATCHING
void func_80107E84_bowser_toss(omObjData* obj) {
    BtPlayer* p;
    s16 pad;
    f32 t;
    u8 r;

    p = func_8010D98C_bowser_toss(obj);
    func_80108800_bowser_toss(p->unk00);
    pad = p->unk1A;
    D_800D20A1_main[pad] = 0;
    D_800D5558_main[pad] = 0;
    D_800CDA7C_main[pad] = 0;
    switch (p->unk0C) {
    case 1:
        p->unk54 = D_8010F230_bowser_toss[p->unk20] +
                   D_8010F240_bowser_toss[p->unk20] * ((0.5 - (f32)(u8)(rand8() % 100) * 0.01) * 2.0);
        r = rand8();
        p->unk58 = func_801080D0_bowser_toss(p->unk54,
                                             D_8010F260_bowser_toss[p->unk20] + (f32)(u8)(r % 100) * 0.01 * 1500.0,
                                             D_8010F250_bowser_toss[p->unk20]);
        D_800D5558_main[p->unk1A] |= 0x8000;
        break;
    case 2:
        D_800D20A1_main[p->unk1A] = p->unk54 * 60.0f;
        t = p->unk44 / 45.0f;
        if ((p->unk08 & 1) && t < p->unk58) {
            D_800D5558_main[p->unk1A] |= 0x8000;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80107E84_bowser_toss);
#endif

f32 func_801080D0_bowser_toss(f32 arg0, f32 arg1, f32 arg2) {
    f32 pos[2];
    f32 vel[2];
    f32 ang;
    f32 s;

    ang = 360.0f - arg0 * 85.0f;
    for (s = 0.5f; s < 1.0f; s += 0.01f) {
        pos[0] = D_8010F270_bowser_toss[0];
        pos[1] = D_8010F270_bowser_toss[1];
        vel[0] = fabs(cosdf(ang)) * s * 75.99999904632568;
        vel[1] = fabs(sindf(ang)) * s * 75.99999904632568;
        while (pos[1] > 0.0f) {
            pos[0] += vel[0];
            pos[1] += vel[1];
            vel[1] -= 0.65332f;
            if (vel[1] < -250.0) {
                vel[1] = -250.0f;
            }
        }
        if (arg1 <= pos[0]) {
            return s;
        }
    }
    for (s = 0.5f; s > 0.1f; s -= 0.01f) {
        pos[0] = D_8010F270_bowser_toss[0];
        pos[1] = D_8010F270_bowser_toss[1];
        vel[0] = fabs(cosdf(ang)) * s * 75.99999904632568;
        vel[1] = fabs(sindf(ang)) * s * 75.99999904632568;
        while (pos[1] > 0.0f) {
            pos[0] += vel[0];
            pos[1] += vel[1];
            vel[1] -= 0.65332f;
            if (vel[1] < -250.0) {
                vel[1] = -250.0f;
            }
        }
        if (arg1 <= pos[0]) {
            return s;
        }
    }
    return arg2;
}

s32 func_8010840C_bowser_toss(void) {
    BtPlayer* p;
    s32 i;

    for (i = 0, p = D_8010FB74_bowser_toss; i < 2; i++, p++) {
        if (p->unk0C != 5) {
            return 0;
        }
    }
    return 1;
}

s32 func_80108444_bowser_toss(void) {
    BtPlayer* p;
    s32 i;

    for (i = 0, p = D_8010FB74_bowser_toss; i < 2; i++, p++) {
        if (p->unk0C != 10) {
            return 0;
        }
    }
    return 1;
}

void func_8010847C_bowser_toss(omObjData* obj, s16 a, s16 b) {
    HmfModel* ma = &HmfModelData[obj->model[a]];
    HmfModel* mb = &HmfModelData[obj->model[b]];
    HmfData* tmp = ma->hmf;

    ma->hmf = mb->hmf;
    mb->hmf = tmp;
}

void func_801084DC_bowser_toss(void) {
    BtBowser* bw;
    s32 i;

    bw = D_8010FB8C_bowser_toss = HuMemAllocTag(sizeof(BtBowser) * 2, 31000);
    memset(bw, 0, sizeof(BtBowser) * 2);
    for (i = 0; i < 2; i++, bw++) {
        bw->unk00 = NULL;
        bw->unk5C = NULL;
        bw->unk10 = 0.0f;
        bw->unk14 = 120.0f;
        bw->unk18 = 0.0f;
        bw->unk1C = 0.0f;
        bw->unk20 = -1;
        bw->unk22 = 0;
        bw->unk24 = 0;
    }
    D_8010FB88_bowser_toss = omAddObj(0x14, 0, 0, -1, func_8010882C_bowser_toss);
}

/* NON_MATCHING: register allocation of the model id sign extension before Hu3DModelScaleSet. */
#ifdef NON_MATCHING
void func_8010858C_bowser_toss(s16 idx) {
    BtBowser* bw = &D_8010FB8C_bowser_toss[idx];
    HmfModel* model;
    u8 mtn;
    u8 mtn2;
    s32 size;
    s16 mask;
    u16 m;
    D_800CCF58_main_Struct* anim;

    bw->unk00 = D_800EC598_minigame[idx];
    bw->unk0A = 0;
    func_8010D98C_bowser_toss(bw->unk00);
    model = &HmfModelData[bw->unk00->model[0]];
    mtn = model->unk02;
    mtn2 = model->unk06;
    model->unk02 = bw->unk00->motion[4];
    model->unk06 = bw->unk00->motion[6];
    bw->unk5C = func_8010D9E0_bowser_toss(bw->unk00->model[0], 1, "item_hook", 1, 0);
    model->unk02 = mtn;
    model->unk06 = mtn2;
    anim = &D_800CCF58_main[bw->unk00->motion[6]];
    size = (s16)(anim->unk02 + 1) << 6;
    bw->unk60 = HuMemAllocTag(size, 31000);
    memset(bw->unk60, 0, size);
    memcpy(bw->unk60, bw->unk5C->unk_08, size);
    func_8010DDC4_bowser_toss(bw->unk5C);
    bw->unk5C = NULL;
    if (idx == 0) {
        bw->unk04 = func_8000B108_main(0x550000, 0x299);
        bw->unk06 = func_8000B108_main(0x550005, 0x29D);
        bw->unk08 = m = func_8000B108_main(0, 0x299);
    } else {
        bw->unk04 = Hu3DModelLink(D_8010FB8C_bowser_toss[0].unk04);
        bw->unk06 = Hu3DModelLink(D_8010FB8C_bowser_toss[0].unk06);
        bw->unk08 = m = Hu3DModelLink(D_8010FB8C_bowser_toss[0].unk08);
    }
    Hu3DModelScaleSet(m, 1.3f, 1.3f, 1.3f);
    func_8001C258_main(bw->unk04, 0x4000, 0x4000);
    func_8001EF6C_main(bw->unk04, bw->unk00->model[0], "item_hook");
    mask = 1 << idx;
    func_8001C8A8_main(bw->unk04, mask);
    func_8001C8A8_main(bw->unk06, mask);
    func_8001C8A8_main(bw->unk08, mask);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010858C_bowser_toss);
#endif

BtBowser* func_80108800_bowser_toss(s16 idx) {
    return &D_8010FB8C_bowser_toss[idx];
}

/* The two thrown Bowsers: held, spun, flying, landing, sliding to rest. */
/* NON_MATCHING: case 8 schedules the bw->unk30.x load before the 100.0f constant (retail after); otherwise identical. */
#ifdef NON_MATCHING
void func_8010882C_bowser_toss(omObjData* obj) {
    Matrix4f m0;
    Matrix4f m1;
    Matrix4f m2;
    Vec pos;
    Vec vel;
    Vec scale;
    BtBowser* bw;
    BtPlayer* p;
    HmfModel* model;
    s32 i;
    s32 j;
    s32 n;
    f32 a;
    f32 b;
    f32 s;
    f32 t;
    f32 g;

    i = 0;
    bw = D_8010FB8C_bowser_toss;
    do {
        p = func_8010D98C_bowser_toss(bw->unk00);
        model = &HmfModelData[bw->unk00->model[0]];
        obj->trans.x = bw->unk00->trans.x;
        obj->trans.y = bw->unk00->trans.y;
        obj->trans.z = bw->unk00->trans.z;
        obj->rot.x = bw->unk00->rot.x;
        obj->rot.y = bw->unk00->rot.y;
        obj->rot.z = bw->unk00->rot.z;
        obj->scale.x = bw->unk00->scale.x;
        obj->scale.y = bw->unk00->scale.y;
        obj->scale.z = bw->unk00->scale.z;
        switch (bw->unk0A) {
        case 0:
            if (bw->unk60 != NULL) {
                func_80109DB8_bowser_toss(obj, obj->rot.y, m0);
                func_80109E4C_bowser_toss(bw, m2, model->unk58);
                if (model->unk06 != 0xFF) {
                    func_80018044_main(m2, m0, m1);
                } else {
                    func_8002367C_main(m1, m0);
                }
                func_80017C10_main((Mtx*)m1, 0.0f, 0.0f, 150.0f);
                bw->unk30.x = m1[3][0];
                bw->unk30.z = m1[3][2];
            }
            break;
        case 1:
            func_8001C258_main(bw->unk04, 0x4000, 0);
            func_80109DB8_bowser_toss(obj, 90.0f, m0);
            func_80109E4C_bowser_toss(bw, m2, model->unk58);
            func_80018044_main(m2, m0, m1);
            func_80017C10_main((Mtx*)m1, 0.0f, 0.0f, 150.0f);
            bw->unk30.x = m1[3][0];
            bw->unk30.y = m1[3][1];
            bw->unk30.z = m1[3][2];
            bw->unk3C = 360.0f - bw->unk2C * 85.0f;
            bw->unk40 = 90.0f;
            bw->unk44 = 0.0f;
            func_8001C258_main(bw->unk04, 4, 4);
            func_8001C258_main(bw->unk06, 4, 0);
            bw->unk48 = fabs(cosdf(bw->unk3C)) * bw->unk28 * 75.99999904632568;
            bw->unk4C = fabs(sindf(bw->unk3C)) * bw->unk28 * 75.99999904632568;
            bw->unk50 = 0;
            bw->unk30.x += bw->unk48;
            bw->unk30.y += bw->unk4C;
            bw->unk22 = 0;
            bw->unk24 = func_80109F68_bowser_toss(bw->unk30.x, bw->unk30.y, bw->unk48, bw->unk4C);
            bw->unk20 = func_8004AC5C_main(0x4A7, p->unk00);
            if (bw->unk20 != -1) {
                HuAudFXPitchSet(bw->unk20, bw->unk22);
            }
            bw->unk0A = 2;
            bw->unk0C = 0;
            break;
        case 2:
            bw->unk30.x += bw->unk48;
            bw->unk30.y += bw->unk4C;
            bw->unk4C -= 0.65332f;
            if (bw->unk4C < -250.0) {
                bw->unk4C = -250.0f;
            }
            if (bw->unk0C < 20) {
                t = bw->unk0C / 20.0f;
                CenterM[i].x = func_8010D8A0_bowser_toss(t, Center.x, bw->unk30.x);
                CenterM[i].y = func_8010D8A0_bowser_toss(t, Center.y, bw->unk30.y);
            } else {
                CenterM[i].x = bw->unk30.x;
                CenterM[i].y = bw->unk30.y;
            }
            if (CenterM[i].x < Center.x) {
                CenterM[i].x = Center.x;
            }
            if (p->unk00 == 0) {
                if (CenterM[i].y < Center.y) {
                    CenterM[i].y = Center.y;
                }
            } else if (CenterM[i].y < D_8010FBA8_bowser_toss.y) {
                CenterM[i].y = D_8010FBA8_bowser_toss.y;
            }
            bw->unk3C = atan2df(-bw->unk4C, bw->unk48);
            bw->unk44 += bw->unk28 * 10.0f;
            if (bw->unk44 >= 360.0f) {
                bw->unk44 -= 360.0f;
            }
            g = -(fabs(bw->unk4C) / 250.0 * 100.0);
            if (bw->unk30.y <= g + 10.0) {
                bw->unk30.y = g + 10.0;
                bw->unk0E = 0;
                bw->unk0C = 0;
                p->unk04 = bw->unk30.x;
                scale.x = scale.y = scale.z = 1.0f;
                n = fabs(bw->unk4C) / 250.0 * 8.0 + 8.0;
                for (j = 0; j < n; j++) {
                    BT_DUST(bw, p, pos, vel, scale, s, a, b);
                }
                if (bw->unk20 != -1) {
                    HuAudFXStop(bw->unk20);
                }
                bw->unk20 = -1;
                func_8004AC5C_main(0x4A8, p->unk00);
                omVibrate(p->unk18, 20, 0, 20);
                if (bw->unk28 < 0.4f) {
                    bw->unk0A = 7;
                } else {
                    if (fabs(bw->unk48) < 2.0 * fabs(bw->unk4C)) {
                        bw->unk18 = 50.0f;
                    } else {
                        bw->unk18 = bw->unk28 / 0.4f * 50.0;
                    }
                    bw->unk1C = CenterM[i].y;
                    bw->unk0A = 6;
                }
            } else {
                if (bw->unk4C > 0.0f) {
                    bw->unk22 += 10;
                } else {
                    bw->unk22 -= 10;
                }
                if (bw->unk22 > 1200) {
                    bw->unk22 = 1200;
                } else if (bw->unk22 < 0) {
                    bw->unk22 = 0;
                }
                if (bw->unk20 != -1) {
                    HuAudFXPitchSet(bw->unk20, bw->unk22);
                }
            }
            break;
        case 3:
            func_8001C258_main(bw->unk04, 0x4000, 0);
            func_80109DB8_bowser_toss(obj, 90.0f, m0);
            func_80109E4C_bowser_toss(bw, m2, 0.0f);
            func_80018044_main(m2, m0, m1);
            func_80017C10_main((Mtx*)m1, 0.0f, 0.0f, 150.0f);
            bw->unk30.x = m1[3][0];
            bw->unk30.y = m1[3][1];
            bw->unk30.z = m1[3][2];
            bw->unk3C = 45.0f;
            bw->unk40 = 90.0f;
            bw->unk44 = 0.0f;
            func_8001C258_main(bw->unk04, 4, 4);
            func_8001C258_main(bw->unk06, 4, 0);
            bw->unk4C = 0.0f;
            bw->unk0A = 4;
            /* fallthrough */
        case 4:
            bw->unk4C -= 1.95996f;
            if (bw->unk4C < -250.0) {
                bw->unk4C = -250.0f;
            }
            bw->unk30.y += bw->unk4C;
            g = -(fabs(bw->unk4C) / 250.0 * 100.0);
            if (bw->unk30.y <= g + 10.0) {
                bw->unk30.y = g + 10.0;
                scale.x = scale.y = scale.z = 1.0f;
                for (j = 0; j < 5; j++) {
                    BT_DUST(bw, p, pos, vel, scale, s, a, b);
                }
                func_8004AC5C_main(0x4A8, p->unk00);
                bw->unk0A = 9;
            }
            break;
        case 5:
            bw->unk3C = func_8010D6E0_bowser_toss(0.0f, bw->unk3C, 5.0f);
            if (bw->unk3C <= 0.0f) {
                bw->unk0A = 9;
                bw->unk0C = 0;
            }
            break;
        case 6:
            bw->unk0A = 8;
            bw->unk0C = 0;
            break;
        case 7:
            bw->unk48 *= 0.8f;
            bw->unk30.x += bw->unk48;
            CenterM[i].x = bw->unk30.x;
            CenterM[i].y = bw->unk30.y;
            if (CenterM[i].x < Center.x) {
                CenterM[i].x = Center.x;
            }
            if (p->unk00 == 0) {
                if (CenterM[i].y < Center.y) {
                    CenterM[i].y = Center.y;
                }
            } else if (CenterM[i].y < D_8010FBA8_bowser_toss.y) {
                CenterM[i].y = D_8010FBA8_bowser_toss.y;
            }
            pos.x = bw->unk30.x;
            pos.y = 0.0f;
            pos.z = bw->unk30.z;
            a = BT_RANDF() * 180.0;
            b = BT_RANDF() * 360.0;
            s = BT_RANDF() * 7.000000029802322 + 7.000000029802322;
            vel.x = sindf(b) * cosdf(a) * s;
            vel.y = -sindf(a) * s;
            vel.z = cosdf(b) * cosdf(a) * s;
            scale.x = scale.y = scale.z = 1.0f;
            func_8010A2D4_bowser_toss(&pos, &vel, &scale, 1.0f, p->unk00);
            if (bw->unk48 <= 10.0) {
                bw->unk0A = 9;
                bw->unk0C = 0;
            }
            break;
        case 8:
            BT_DUST_VEL(bw, pos, vel, s, a, b);
            scale.x = scale.y = scale.z = 1.0f;
            func_8010A2D4_bowser_toss(&pos, &vel, &scale, 1.0f, p->unk00);
            if (bw->unk0C >= 6.0f) {
                bw->unk0A = 9;
                bw->unk0C = 0;
            }
            break;
        case 9:
            break;
        }
        if (bw->unk18 >= 0.1f) {
            CenterM[i].y = bw->unk18 * 0.5f + bw->unk1C + sindf(bw->unk10) * bw->unk18;
            bw->unk10 += bw->unk14;
            if (bw->unk10 >= 360.0f) {
                bw->unk10 -= 360.0f;
            }
            bw->unk18 -= 7.500000298023224;
        }
        Hu3DModelPosSet(bw->unk04, bw->unk30.x, bw->unk30.y, bw->unk30.z);
        Hu3DModelRotSet(bw->unk04, bw->unk3C, bw->unk40, 0.0f);
        func_8008A070_main((f32(*)[4])HmfModelData[bw->unk04].mtx);
        func_80017D24_main((f32(*)[4])HmfModelData[bw->unk04].mtx, 0.0f, 0.0f, bw->unk44);
        Hu3DModelPosSet(bw->unk06, bw->unk30.x, bw->unk30.y, bw->unk30.z);
        Hu3DModelRotSet(bw->unk06, bw->unk3C, bw->unk40, 0.0f);
        func_8008A070_main((f32(*)[4])HmfModelData[bw->unk06].mtx);
        func_80017D24_main((f32(*)[4])HmfModelData[bw->unk06].mtx, 0.0f, 0.0f, bw->unk44);
        Hu3DModelPosSet(bw->unk08, bw->unk30.x, 0.0f, bw->unk30.z);
        i++;
        bw->unk0C++;
        bw++;
    } while (i < 2);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010882C_bowser_toss);
#endif

void func_80109DB8_bowser_toss(omObjData* obj, f32 rot, Matrix4f out) {
    fmod(rot + obj->rot.y, 360.0);
    func_8008A070_main(out);
    func_80017C10_main((Mtx*)out, obj->trans.x, obj->trans.y, obj->trans.z);
    func_80017D24_main(out, obj->rot.x, rot, obj->rot.z);
    func_80017CD0_main(out, obj->scale.x, obj->scale.y, obj->scale.z);
}

/* NON_MATCHING: register allocation of the second key-frame index. */
#ifdef NON_MATCHING
void func_80109E4C_bowser_toss(BtBowser* bw, Matrix4f out, f32 frame) {
    s16 b;
    s16 a;
    f32 f;

    if ((s16)frame >= 29) {
        b = 29;
        f = 0.0f;
        a = 29;
    } else {
        b = 0;
        if ((s16)frame <= 0) {
            f = 0.0f;
            a = 0;
        } else {
            a = frame;
            f = frame - a;
            b = a + 1;
        }
    }
    func_8010D918_bowser_toss((f32*)((Matrix4f*)bw->unk60 + a), (f32*)((Matrix4f*)bw->unk60 + b), (f32*)out, f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80109E4C_bowser_toss);
#endif

s32 func_80109F20_bowser_toss(void) {
    BtBowser* bw;
    s32 i;

    for (i = 0, bw = D_8010FB8C_bowser_toss; i < 2; i++, bw++) {
        if ((bw->unk0A == 0) | (bw->unk0A == 9)) {
            continue;
        }
        return 0;
    }
    return 1;
}

/* NON_MATCHING: retail converts y to double before the ground-height add (scheduling only). */
#ifdef NON_MATCHING
s16 func_80109F68_bowser_toss(f32 x, f32 y, f32 vx, f32 vy) {
    s16 n = 0;

    if (y > 10.0) {
        do {
            y += vy;
            vy -= 1.95996f;
            if (vy < -250.0) {
                vy = -250.0f;
            }
            n++;
        } while ((f32)-(fabs(vy) / 250.0 * 100.0) + 10.0 < y);
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80109F68_bowser_toss);
#endif

void func_8010A028_bowser_toss(void) {
    HuSprite_Unk84_Struct* spr;
    BtEffect* fx;
    HmfModel* mdl;
    s32 i;

    spr = func_80055194_main(D_8010FB98_bowser_toss[5] = func_8010AD54_bowser_toss(0xB));
    D_8010FB90_bowser_toss = omAddObj(0x1E, 0, 0, -1, func_8010A17C_bowser_toss);
    D_8010FB94_bowser_toss = fx = HuMemAllocTag(sizeof(BtEffect) * 32, 31000);
    for (i = 0; i < 32; i++, fx++) {
        if (i == 0) {
            fx->model = func_8010DDFC_bowser_toss(spr, &D_8010F150_bowser_toss, 0);
        } else {
            fx->model = func_8010EA0C_bowser_toss(spr, D_8010FB94_bowser_toss->model, &D_8010F150_bowser_toss);
        }
        fx->active = 0;
        fx->frame = fx->speed = 0.0f;
        fx->pos.x = fx->pos.y = fx->pos.z = 0.0f;
        fx->vel.x = fx->vel.y = fx->vel.z = 0.0f;
        fx->scale.x = fx->scale.y = fx->scale.z = 0.0f;
        func_8001C258_main(fx->model, 4, 4);
        mdl = &HmfModelData[fx->model];
        mdl->unk40 = 0.0f;
    }
}

void func_8010A17C_bowser_toss(omObjData* obj) {
    HuSprite_Unk84_Struct* spr;
    BtEffect* fx;
    HmfModel* mdl;
    s32 i;

    spr = func_80055194_main(D_8010FB98_bowser_toss[5]);
    for (i = 0, fx = D_8010FB94_bowser_toss; i < 32; i++, fx++) {
        if (fx->active == 0) {
            continue;
        }
        mdl = &HmfModelData[fx->model];
        if (mdl->unk18 & 4) {
            continue;
        }
        fx->pos.x += fx->vel.x;
        fx->pos.y += fx->vel.y;
        fx->pos.z += fx->vel.z;
        mdl->pos.x = fx->pos.x;
        mdl->pos.y = fx->pos.y;
        mdl->pos.z = fx->pos.z;
        mdl->scale.x = fx->scale.x;
        mdl->scale.y = fx->scale.y;
        mdl->scale.z = fx->scale.z;
        func_8010EC10_bowser_toss(fx->model, spr, (s32)fx->frame, &D_8010F150_bowser_toss);
        fx->frame += fx->speed;
        if ((s32)fx->frame >= spr->unk10) {
            fx->active = 0;
            fx->frame = 0.0f;
            mdl->unk18 |= 4;
        }
    }
}

s32 func_8010A2D4_bowser_toss(Vec* pos, Vec* vel, Vec* scale, f32 speed, s16 player) {
    HuSprite_Unk84_Struct* spr;
    BtEffect* fx;
    HmfModel* mdl;
    s32 i;

    spr = func_80055194_main(D_8010FB98_bowser_toss[5]);
    for (i = 0, fx = D_8010FB94_bowser_toss; i < 32; i++, fx++) {
        if (fx->active != 0) {
            continue;
        }
        fx->active = 1;
        mdl = &HmfModelData[fx->model];
        if (pos != NULL) {
            fx->pos.x = pos->x;
            fx->pos.y = pos->y;
            fx->pos.z = pos->z;
        } else {
            fx->pos.x = fx->pos.y = fx->pos.z = 0.0f;
        }
        if (vel != NULL) {
            fx->vel.x = vel->x;
            fx->vel.y = vel->y;
            fx->vel.z = vel->z;
        } else {
            fx->vel.x = fx->vel.y = fx->vel.z = 0.0f;
        }
        if (scale != NULL) {
            fx->scale.x = scale->x;
            fx->scale.y = scale->y;
            fx->scale.z = scale->z;
        } else {
            fx->scale.x = fx->scale.y = fx->scale.z = 1.0f;
        }
        fx->speed = speed;
        fx->frame = 0.0f;
        func_8010EC10_bowser_toss(fx->model, spr, 0, &D_8010F150_bowser_toss);
        func_8001C258_main(fx->model, 4, 0);
        func_8001C8A8_main(fx->model, 1 << player);
        mdl->unk40 = 0.0f;
        mdl->pos.x = fx->pos.x;
        mdl->pos.y = fx->pos.y;
        mdl->pos.z = fx->pos.z;
        mdl->scale.x = fx->scale.x;
        mdl->scale.y = fx->scale.y;
        mdl->scale.z = fx->scale.z;
        return i;
    }
    return -1;
}

void func_8010A4A8_bowser_toss(void) {
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(0x20, 0x1C, 0, -1, func_8010A500_bowser_toss);
}

void func_8010A500_bowser_toss(omObjData* obj) {
    HuSprite_Unk84_Struct* spr;
    s32 side;
    s32 base;
    s32 k;
    s32 i;
    s16 grp;

    D_8010FB98_bowser_toss[0] = func_8010AD54_bowser_toss(0x550006);
    spr = func_80055194_main(D_8010FB98_bowser_toss[0]);
    for (side = 0; side < 2; side++) {
        base = side * 14;
        k = 0;
        if (side == 0) {
            obj->model[base + k] = func_8000B108_main(0x550001, 0xB9);
        } else {
            obj->model[base + k] = Hu3DModelLink(obj->model[0]);
        }
        k++;
        if (side == 0) {
            obj->model[base + k] = func_8000B108_main(0x550003, 0xB9);
            obj->model[base + k + 1] = func_8000B108_main(0x550004, 0xB9);
        } else {
            obj->model[base + k] = Hu3DModelLink(obj->model[k]);
            obj->model[base + k + 1] = Hu3DModelLink(obj->model[k + 1]);
        }
        for (i = 2; i < 5; i++) {
            obj->model[base + k + i] = Hu3DModelLink(obj->model[k + (i & 1)]);
        }
        k += 5;
        if (side == 0) {
            obj->model[base + k] = func_8000B108_main(0x550002, 0x99);
        } else {
            obj->model[base + k] = Hu3DModelLink(obj->model[k]);
        }
        for (i = 1; i < 4; i++) {
            obj->model[base + k + i] = Hu3DModelLink(obj->model[base + k]);
        }
        k += 4;
        if (side == 0) {
            obj->model[base + k] = func_8010DDFC_bowser_toss(spr, &D_8010F320_bowser_toss, 0);
        } else {
            obj->model[base + k] = func_8010EA0C_bowser_toss(spr, obj->model[k], &D_8010F320_bowser_toss);
        }
        for (i = 1; i < 4; i++) {
            obj->model[base + k + i] = func_8010EA0C_bowser_toss(spr, obj->model[k], &D_8010F320_bowser_toss);
        }
        for (i = base; i < base + 14; i++) {
            Hu3DModelPosSet(obj->model[i], D_8010F278_bowser_toss[i - base].x, D_8010F278_bowser_toss[i - base].y,
                            D_8010F278_bowser_toss[i - base].z);
            func_8001C8A8_main(obj->model[i], 1 << side);
        }
    }
    D_8010FB98_bowser_toss[4] = func_8010AD54_bowser_toss(0x55000A);
    grp = HuSprGrpCreate(1, 0);
    func_80055024_main(grp, 0, D_8010FB98_bowser_toss[4], 0);
    func_80054904_main(grp, 0, 0xA0, 0x78);
    func_800550F4_main(grp, 0, 0);
    func_80054FF8_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x1000);
    obj->func = func_8010A908_bowser_toss;
}

/* NON_MATCHING: retail keeps only 500.0 and 0.0f in registers and reloads the other double constants per use;
 * its frame spills the row index (it re-indexes D_8010F324 in the else arm). Same calls, stores and values. */
#ifdef NON_MATCHING
void func_8010A908_bowser_toss(omObjData* obj) {
    HuSprite_Unk84_Struct* spr;
    s16* row;
    s32 side;
    s32 base;
    s32 n;
    s32 m;
    s32 f;
    s32 j;

    spr = func_80055194_main(D_8010FB98_bowser_toss[0]);
    for (side = 0; side < 2; side++) {
        base = side * 14;
        n = (CenterM[side].x - 955.6950378417969) / 704.5024871826172 - 2.0;
        if (n < 0) {
            n = 0;
        }
        if (n >= 2) {
            func_8001C258_main(obj->model[base], 4, 4);
        } else {
            func_8001C258_main(obj->model[base], 4, 0);
        }
        row = D_8010F324_bowser_toss[n & 1];
        for (j = 0; j < 5; j++) {
            if (CenterM[side].x == Center.x) {
                func_8001C258_main(obj->model[base + 1 + row[j]], 4, 4);
            } else {
                func_8001C258_main(obj->model[base + 1 + row[j]], 4, 0);
                Hu3DModelPosSet(obj->model[base + 1 + row[j]], (s16)(n + j) * 704.5024871826172 + 955.6950378417969,
                                0.0f, 0.0f);
            }
        }
        m = CenterM[side].x / 500.0 - 1.0;
        if (m <= 0) {
            m = 1;
        }
        for (j = 0; j < 4; j++) {
            Hu3DModelPosSet(obj->model[base + 6 + j], (f32)(m + j) * 500.0, 0.0f, 0.0f);
        }
        for (j = 0; j < 4; j++) {
            f = m + j - 1;
            Hu3DModelPosSet(obj->model[base + 10 + j], (f32)(m + j) * 500.0, 75.0f, -300.0f);
            if (f >= 20) {
                f = 19;
                func_8001C258_main(obj->model[base + 10 + j], 4, 4);
            } else {
                if (f < 0) {
                    f = 0;
                }
                func_8001C258_main(obj->model[base + 10 + j], 4, 0);
            }
            func_8010EC10_bowser_toss(obj->model[base + 10 + j], spr, f, &D_8010F338_bowser_toss);
        }
        func_8010AF38_bowser_toss(side, &CenterM[side], &CRotM[side]);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A908_bowser_toss);
#endif

u16 func_8010AD54_bowser_toss(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}

/* NON_MATCHING: retail sign-extends the new sprite group before storing it (one instruction moved). */
#ifdef NON_MATCHING
void func_8010AD98_bowser_toss(void) {
    s32 i;
    s32 j;
    s16 grp;

    D_8010FB98_bowser_toss[1] = func_8010AD54_bowser_toss(0x550007);
    D_8010FB98_bowser_toss[2] = func_8010AD54_bowser_toss(0x550008);
    D_8010FB98_bowser_toss[3] = func_8010AD54_bowser_toss(0x550009);
    for (i = 0; i < 2; i++) {
        grp = HuSprGrpCreate(4, 0);
        D_8010FB9C_bowser_toss[i] = grp;
        for (j = 0; j < 4; j++) {
            func_80055024_main(grp, j, D_8010FB98_bowser_toss[1], 0);
            func_80054904_main(grp, j, D_8010F33C_bowser_toss[i].x, D_8010F33C_bowser_toss[i].y);
            func_800550F4_main(grp, j, 0);
            func_80054FF8_main(grp, j, 0);
            HuSprAttrSet(grp, j, 0x483C);
            func_800555E8_main(grp, j, D_8010F33C_bowser_toss[i].x, D_8010F33C_bowser_toss[i].y,
                               D_8010F33C_bowser_toss[i].w, D_8010F33C_bowser_toss[i].h);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010AD98_bowser_toss);
#endif

/* Scroll one screen's 2 x 2 background tiles to follow its camera. */
void func_8010AF38_bowser_toss(s16 side, Vec* center, Vec* rot) {
    s16 grp;
    f32 x;
    f32 y;
    f32 fy;
    f32 sx;
    f32 sy;
    s16 row;
    BtStrip* e;

    grp = D_8010FB9C_bowser_toss[side];
    x = (center->x - Center.x) / D_8010F34C_bowser_toss;
    y = (center->y - Center.y) / D_8010F34C_bowser_toss;
    if (x == 0.0f) {
        HuSprAttrSet(grp, 1, 0x8000);
        HuSprAttrSet(grp, 3, 0x8000);
    } else {
        HuSprAttrReset(grp, 1, 0x8000);
        HuSprAttrReset(grp, 3, 0x8000);
    }
    if (y == 0.0f) {
        HuSprAttrSet(grp, 2, 0x8000);
        HuSprAttrSet(grp, 3, 0x8000);
    } else {
        HuSprAttrReset(grp, 2, 0x8000);
        HuSprAttrReset(grp, 3, 0x8000);
    }
    row = y / 120.0f;
    if (side == 0) {
        x = -fmod(x, 320.0);
        fy = fmod(y, 120.0);
    } else {
        x = -fmod(x, 320.0);
        fy = fmod(y, 120.0) + 120.0;
    }
    if (center->x >= 0.0f) {
        sx = 1.0f;
    } else {
        sx = -1.0f;
    }
    if (center->y >= 0.0f) {
        sy = 1.0f;
    } else {
        sy = -1.0f;
    }
    if (row >= 8) {
        row = 7;
    } else if (row < 0) {
        row = 0;
    }
    e = &D_8010F350_bowser_toss[row];
    func_80054904_main(grp, 0, x, fy);
    func_80055024_main(grp, 0, D_8010FB98_bowser_toss[e->sprite], e->frame);
    func_80054FF8_main(grp, 0, e->frame);
    func_80054904_main(grp, 1, x + sx * 320.0f, fy);
    func_80055024_main(grp, 1, D_8010FB98_bowser_toss[e->sprite], e->frame);
    func_80054FF8_main(grp, 1, e->frame);
    if (sy >= 0.0f) {
        row++;
    } else {
        row--;
    }
    if (row >= 8) {
        row = 7;
    } else if (row < 0) {
        row = 0;
    }
    e = &D_8010F350_bowser_toss[row];
    func_80054904_main(grp, 2, x, fy - sy * 120.0f);
    func_80055024_main(grp, 2, D_8010FB98_bowser_toss[e->sprite], e->frame);
    func_80054FF8_main(grp, 2, e->frame);
    func_80054904_main(grp, 3, x + sx * 320.0f, fy - sy * 120.0f);
    func_80055024_main(grp, 3, D_8010FB98_bowser_toss[e->sprite], e->frame);
    func_80054FF8_main(grp, 3, e->frame);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010B41C_bowser_toss);

/* The three score counters: fade in, count up, pop, slide away. */
/* NON_MATCHING: float registers t/sum swapped (f20/f22), and retail converts the state-19 loop counter to s16 once
 * for both calls; same calls, stores and values. */
#ifdef NON_MATCHING
void func_8010B7AC_bowser_toss(void) {
    s32 d[5];
    BtScore* sc;
    BtScore* other;
    s32 i;
    s32 j;
    s32 v;
    s32 done;
    s32 y;
    f32 t;
    f32 sum;
    f32 f;

    i = 0;
    sc = D_8010FBA0_bowser_toss;
    do {
        done = 0;
        switch (sc->unk04) {
        case 1:
            func_80054904_main(sc->unk00, 6, D_8010F378_bowser_toss[i][6][0], D_8010F378_bowser_toss[i][6][1]);
            func_80055458_main(sc->unk00, 6, 0);
            HuSprAttrReset(sc->unk00, 6, 0x8000);
            sc->unk04 = 2;
            sc->unk02 = 0;
            break;
        case 2:
            t = sc->unk02 / 15.0f;
            func_80055458_main(sc->unk00, 6, t * 256.0f);
            if (sc->unk02 >= 15.0f) {
                func_80055458_main(sc->unk00, 6, 0x100);
                sc->unk04 = 31;
                sc->unk02 = 0;
            }
            break;
        case 3:
            for (j = 0; j < 6; j++) {
                func_80054904_main(sc->unk00, j, D_8010F378_bowser_toss[i][j][0], D_8010F378_bowser_toss[i][j][1]);
                HuSprAttrReset(sc->unk00, j, 0x8000);
            }
            func_80054904_main(sc->unk00, 7, D_8010F378_bowser_toss[i][7][0], D_8010F378_bowser_toss[i][7][1]);
            func_80054FF8_main(sc->unk00, 4, 1);
            func_80054FF8_main(sc->unk00, 5, 0);
            sc->unk04 = 4;
            sc->unk02 = 0;
            break;
        case 4:
            sc->unk0C += 333;
            if (sc->unk08 < sc->unk0C) {
                sc->unk0C = sc->unk08;
                done = 1;
            }
            BT_DIGITS(sc, d, v, j);
            if (done) {
                if (D_8010FB70_bowser_toss != -1) {
                    if (i == 0) {
                        other = &D_8010FBA0_bowser_toss[1];
                    } else {
                        other = &D_8010FBA0_bowser_toss[0];
                    }
                    if (other->unk04 != 3 && other->unk04 != 4) {
                        HuAudFXPlay(0x4AC);
                        D_8010FB70_bowser_toss = -1;
                    }
                }
                sc->unk04 = 5;
                sc->unk02 = 0;
            }
            break;
        case 5:
            if (sc->unk02 >= 15.0f) {
                sc->unk04 = 31;
                sc->unk02 = 0;
            }
            break;
        case 16:
            for (j = 0; j < 6; j++) {
                func_80054904_main(sc->unk00, j, D_8010F378_bowser_toss[i][j][0], D_8010F378_bowser_toss[i][j][1]);
                HuSprAttrReset(sc->unk00, j, 0x8000);
            }
            func_80054904_main(sc->unk00, 7, D_8010F378_bowser_toss[i][7][0], D_8010F378_bowser_toss[i][7][1]);
            func_80054FF8_main(sc->unk00, 4, 1);
            func_80054FF8_main(sc->unk00, 5, 0);
            BT_DIGITS(sc, d, v, j);
            sc->unk04 = 64;
            sc->unk02 = 0;
            break;
        case 18:
            BT_DIGITS(sc, d, v, j);
            sc->unk04 = 19;
            sc->unk02 = 0;
            /* fallthrough */
        case 19:
            sum = 0.0f;
            for (j = 0; j < 6; j++) {
                sum += D_8010F378_bowser_toss[i][j][0];
            }
            sum = (sum + D_8010F378_bowser_toss[i][7][0]) / 7.0f;
            t = sc->unk02 / 15.0f;
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > 1.0f) {
                t = 1.0f;
            }
            t = sindf(t * 180.0f);
            func_80054904_main(sc->unk00, 7, sum + (D_8010F378_bowser_toss[i][7][0] - sum) * (t + 1.0f),
                               D_8010F378_bowser_toss[i][7][1]);
            f = t * 1.2f + 1.2;
            /* Retail passes the loop counter (6) here, not the leading digit's 7. */
            HuSprScaleSet(sc->unk00, j, f, f);
            for (j = 0; j < 6; j++) {
                func_80054904_main(sc->unk00, j, sum + (D_8010F378_bowser_toss[i][j][0] - sum) * (t + 1.0f),
                                   D_8010F378_bowser_toss[i][j][1]);
                if (j < 4) {
                    f = t * 1.2f + 1.2;
                } else {
                    f = t + 1.0;
                }
                HuSprScaleSet(sc->unk00, j, f, f);
            }
            if (sc->unk02 >= 15.0f) {
                sc->unk04 = 64;
                sc->unk02 = 0;
            }
            break;
        case 32:
            t = sc->unk02 / 15.0f;
            sum = func_8010D8A0_bowser_toss(t, 0.0f, 81.0f);
            y = func_8010D8A0_bowser_toss(t, 0.0f, -35.0f);
            for (j = 0; j < 8; j++) {
                func_80054904_main(sc->unk00, j, (s32)sum + D_8010F378_bowser_toss[i][j][0],
                                   y + D_8010F378_bowser_toss[i][j][1]);
            }
            if (sc->unk02 >= 15.0f) {
                sc->unk04 = 64;
                sc->unk02 = 0;
            }
            break;
        case 64:
            break;
        }
        sc->unk02++;
        i++;
        sc++;
    } while (i < 3);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010B7AC_bowser_toss);
#endif

void func_8010C1A0_bowser_toss(s16 idx, s32 value) {
    BtScore* s = &D_8010FBA0_bowser_toss[idx];

    if (value == 0) {
        s->unk04 = 1;
    } else if (idx < 2) {
        s->unk04 = 3;
        s->unk02 = 0;
        s->unk08 = value;
        s->unk0C = 0;
        if (D_8010FB70_bowser_toss == -1) {
            D_8010FB70_bowser_toss = HuAudFXPlay(0x4AB);
        }
    } else {
        s->unk04 = 18;
        s->unk02 = 0;
        s->unk08 = s->unk0C = value;
    }
}

s32 func_8010C23C_bowser_toss(void) {
    BtScore* s;
    s32 i;

    for (i = 0, s = D_8010FBA0_bowser_toss; i < 2; i++, s++) {
        if (s->unk04 < 31) {
            return 0;
        }
    }
    return 1;
}

void func_8010C274_bowser_toss(void) {
    BtScore* s;
    s32 i;

    for (i = 0, s = D_8010FBA0_bowser_toss; i < 2; i++, s++) {
        s->unk04 = 32;
        s->unk02 = 0;
    }
}

s32 func_8010C2A4_bowser_toss(void) {
    BtScore* s;
    s32 i;

    for (i = 0, s = D_8010FBA0_bowser_toss; i < 2; i++, s++) {
        if (s->unk04 < 64) {
            return 0;
        }
    }
    return 1;
}

void func_8010C2DC_bowser_toss(void) {
    BtCam* cam;
    HuCamera* c;
    s32 i;
    s32 j;

    D_8010FBA4_bowser_toss = HuMemAllocTag(sizeof(BtCam) * 2, 31000);
    memset(D_8010FBA4_bowser_toss, 0, sizeof(BtCam) * 2);
    Center.x = 0.0f;
    Center.y = 212.0f;
    Center.z = 0.0f;
    CRot.x = 1.01f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 1222.0f;
    D_8010FBA8_bowser_toss.x = 0.0f;
    D_8010FBA8_bowser_toss.y = 162.0f;
    D_8010FBA8_bowser_toss.z = 0.0f;
    for (i = 0, cam = D_8010FBA4_bowser_toss; i < 2; i++, cam++) {
        CenterM[i].x = Center.x;
        CenterM[i].y = Center.y;
        CenterM[i].z = Center.z;
        CRotM[i].x = CRot.x;
        CRotM[i].y = CRot.y;
        CRotM[i].z = CRot.z;
        CZoomM[i] = CZoom;
        func_8010D080_bowser_toss(i, 0);
        func_8010D080_bowser_toss(i, 1);
        cam->unk48 = cam->unk4C = cam->unk50 = 0;
        c = &gCameraList[i];
        for (j = 0; j < D_800D1FF0_main; j++) {
            c->viewports[j].vp.vscale[0] = c->screenScale.x;
            c->viewports[j].vp.vscale[1] = c->screenScale.y;
            c->viewports[j].vp.vscale[2] = c->screenScale.z;
            c->viewports[j].vp.vtrans[0] = c->screenPos.x;
            c->viewports[j].vp.vtrans[1] = c->screenPos.y;
            c->viewports[j].vp.vtrans[2] = c->screenPos.z;
        }
    }
    omAddObj(0x1F, 0, 0, -1, func_8010CDB8_bowser_toss);
}


/* Debug camera test mode (Log Jam's func_8010B17C with one camera per screen). */
/* NON_MATCHING: retail loads the camera index into v1 and copies it to s4 in a branch delay slot; otherwise identical. */
#ifdef NON_MATCHING
void func_8010C570_bowser_toss(void) {
    BtCamKey c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;
    s32 cam = -1;
    Vec* center;
    Vec* rot;
    s32 i;

    switch (D_8010F3EC_bowser_toss) {
        case 1:
            if ((u16)D_800CDA7C_main[0] & 0x8000) {
                speed = 8.0f;
            }
            if (D_800CDA7C_main[0] & 0x4000) {
                speed = 0.5f;
            }
            if (D_800D5558_main[0] & 0x1000) {
                CenterM[D_8010F3F0_bowser_toss].x = Center.x;
                CenterM[D_8010F3F0_bowser_toss].y = Center.y;
                CenterM[D_8010F3F0_bowser_toss].z = Center.z;
                CRotM[D_8010F3F0_bowser_toss].x = CRot.x;
                CRotM[D_8010F3F0_bowser_toss].y = CRot.y;
                CRotM[D_8010F3F0_bowser_toss].z = CRot.z;
                CZoomM[D_8010F3F0_bowser_toss] = CZoom;
            } else {
                c.rot.x = (f32)D_800D20A1_main[0] * 0.125 * speed;
                c.rot.y = (f32)D_800CBB6E_main[0] * 0.125 * speed;
                if (D_800CDA7C_main[0] & 0x200) {
                    c.center.x = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 0x100) {
                    c.center.x = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x800) {
                    c.center.z = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 0x400) {
                    c.center.z = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 8) {
                    c.center.y = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 4) {
                    c.center.y = -(2.0 * speed);
                }
                if (D_800CDA7C_main[0] & 1) {
                    c.zoom = 2.0 * speed;
                }
                if (D_800CDA7C_main[0] & 2) {
                    c.zoom = -(2.0 * speed);
                }
                c.center.x += CenterM[D_8010F3F0_bowser_toss].x;
                c.center.y += CenterM[D_8010F3F0_bowser_toss].y;
                c.center.z += CenterM[D_8010F3F0_bowser_toss].z;
                c.rot.x += CRotM[D_8010F3F0_bowser_toss].x;
                c.rot.y += CRotM[D_8010F3F0_bowser_toss].y;
                c.rot.z += CRotM[D_8010F3F0_bowser_toss].z;
                c.zoom += CZoomM[D_8010F3F0_bowser_toss];
                func_8010D250_bowser_toss(D_8010F3F0_bowser_toss, c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y,
                                          c.rot.z, c.zoom, 1);
            }
            cam = D_8010F3F0_bowser_toss;
            fontcolor = 15;
            if (D_800D5558_main[0] & 0x10) {
                if ((D_8010F3F0_bowser_toss = cam + 1) >= 2) {
                    D_8010F3F0_bowser_toss = 0;
                    D_8010F3EC_bowser_toss++;
                }
                D_800D5558_main[0] &= ~0x10;
            }
            break;
        case 2:
            if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
                D_8010F3F4_bowser_toss++;
            }
            if (D_800CDA7C_main[0] & 0x202) {
                D_8010F3F4_bowser_toss--;
            }
            if (D_800CDA7C_main[0] & 0x404) {
                D_8010F3F8_bowser_toss++;
            }
            if (D_800CDA7C_main[0] & 0x808) {
                D_8010F3F8_bowser_toss--;
            }
            fontcolor = 8;
            cam = 1;
            break;
        case 3:
            D_8010F3EC_bowser_toss = 0;
            break;
    }
    if (cam != -1) {
        center = &CenterM[cam];
        rot = &CRotM[cam];
        sprintf(D_800D5218_main, "CAMERA TEST_MODE CAM_%d ", cam);
        print8((u16)D_8010F3F4_bowser_toss + 20, (u16)D_8010F3F8_bowser_toss + 80, D_800D5218_main);
        sprintf(D_800D5218_main, " CENTER X>%3.2f Y>%3.2f Z>%3.2f ", center->x, center->y, center->z);
        print8((u16)D_8010F3F4_bowser_toss + 20, (u16)D_8010F3F8_bowser_toss + 88, D_800D5218_main);
        sprintf(D_800D5218_main, " ROT    X>%3.2f Y>%3.2f Z>%3.2f ", rot->x, rot->y, rot->z);
        print8((u16)D_8010F3F4_bowser_toss + 20, (u16)D_8010F3F8_bowser_toss + 96, D_800D5218_main);
        sprintf(D_800D5218_main, " ZOOM   %3.2f ", CZoomM[cam]);
        print8((u16)D_8010F3F4_bowser_toss + 20, (u16)D_8010F3F8_bowser_toss + 104, D_800D5218_main);
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_8010F3EC_bowser_toss == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            for (i = 0; i < 2; i++) {
                center = &CenterM[i];
                rot = &CRotM[i];
                osSyncPrintf("CAMERA_NO %d \n", i);
                osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", center->x, center->y, center->z);
                osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", rot->x, rot->y, rot->z);
                /* Retail prints the shared CZoom here, not CZoomM[i]. */
                osSyncPrintf(" ZOOM   %3.3f \n", CZoom);
            }
            osSyncPrintf(" \n");
        }
        if (D_8010F3EC_bowser_toss++ >= 4) {
            D_8010F3EC_bowser_toss = 0;
        }
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F998_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C570_bowser_toss);
#endif

void func_8010CDB8_bowser_toss(omObjData* obj) {
    BtCam* cam;
    Vec* center;
    Vec* rot;
    f32 t;
    s32 i;

    for (i = 0, cam = D_8010FBA4_bowser_toss; i < 2; i++, cam++) {
        center = &CenterM[i];
        rot = &CRotM[i];
        if (cam->unk4C <= 0) {
            func_8010D43C_bowser_toss(i);
            cam->unk50 = 0;
        } else {
            if (cam->unk48 == 0) {
                center->x = cam->key[0].center.x;
                center->y = cam->key[0].center.y;
                center->z = cam->key[0].center.z;
                rot->x = cam->key[0].rot.x;
                rot->y = cam->key[0].rot.y;
                rot->z = cam->key[0].rot.z;
                CZoomM[i] = cam->key[0].zoom;
                cam->unk4C = 0;
            } else {
                t = 1.0f - (f32)cam->unk48 / (f32)cam->unk4C;
                center->x = func_8010D8A0_bowser_toss(t, cam->key[1].center.x, cam->key[0].center.x);
                center->y = func_8010D8A0_bowser_toss(t, cam->key[1].center.y, cam->key[0].center.y);
                center->z = func_8010D8A0_bowser_toss(t, cam->key[1].center.z, cam->key[0].center.z);
                rot->x = func_8010D8B8_bowser_toss(t, cam->key[1].rot.x, cam->key[0].rot.x);
                rot->y = func_8010D8B8_bowser_toss(t, cam->key[1].rot.y, cam->key[0].rot.y);
                rot->z = func_8010D8B8_bowser_toss(t, cam->key[1].rot.z, cam->key[0].rot.z);
                CZoomM[i] = func_8010D8A0_bowser_toss(t, cam->key[1].zoom, cam->key[0].zoom);
                if (cam->unk48 > 0) {
                    cam->unk48--;
                } else {
                    cam->unk48++;
                }
            }
            BT_WRAP(rot->x);
            BT_WRAP(rot->y);
            BT_WRAP(rot->z);
            cam->unk50 = 1;
            func_8010D43C_bowser_toss(i);
        }
    }
}

void func_8010D080_bowser_toss(s32 side, s32 key) {
    BtCam* cam = &D_8010FBA4_bowser_toss[side];
    Vec* center = &CenterM[side];
    Vec* rot = &CRotM[side];
    BtCamKey* k;

    BT_WRAP(rot->x);
    BT_WRAP(rot->y);
    BT_WRAP(rot->z);
    k = &cam->key[key];
    k->center.x = center->x;
    k->center.y = center->y;
    k->center.z = center->z;
    k->rot.x = rot->x;
    k->rot.y = rot->y;
    k->rot.z = rot->z;
    k->zoom = CZoomM[side];
    k->unk1C = k->unk20 = 0.0f;
}

void func_8010D250_bowser_toss(s32 side, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    BtCam* cam = &D_8010FBA4_bowser_toss[side];
    Vec* center = &CenterM[side];
    Vec* rot = &CRotM[side];

    if (frames > 0) {
        cam->unk48 = frames - 1;
        cam->unk4C = frames;
        if (x != 65535.0f) {
            cam->key[0].center.x = x;
        } else {
            cam->key[0].center.x = center->x;
        }
        if (y != 65535.0f) {
            cam->key[0].center.y = y;
        } else {
            cam->key[0].center.y = center->y;
        }
        if (z != 65535.0f) {
            cam->key[0].center.z = z;
        } else {
            cam->key[0].center.z = center->z;
        }
        if (rx != 65535.0f) {
            cam->key[0].rot.x = rx;
        } else {
            cam->key[0].rot.x = rot->x;
        }
        if (ry != 65535.0f) {
            cam->key[0].rot.y = ry;
        } else {
            cam->key[0].rot.y = rot->y;
        }
        if (rz != 65535.0f) {
            cam->key[0].rot.z = rz;
        } else {
            cam->key[0].rot.z = rot->z;
        }
        if (zoom != 65535.0f) {
            cam->key[0].zoom = zoom;
        } else {
            cam->key[0].zoom = CZoomM[side];
        }
        func_8010D080_bowser_toss(side, 1);
    }
}

void func_8010D43C_bowser_toss(s32 side) {
    HuCamera* cam = &gCameraList[side];
    f32 rx = CRotM[side].x;
    f32 ry = CRotM[side].y;

    cam->pos.x = sindf(ry) * cosdf(rx) * CZoomM[side] + CenterM[side].x;
    cam->pos.y = -sindf(rx) * CZoomM[side] + CenterM[side].y;
    cam->pos.z = cosdf(ry) * cosdf(rx) * CZoomM[side] + CenterM[side].z;
    cam->at.x = CenterM[side].x;
    cam->at.y = CenterM[side].y;
    cam->at.z = CenterM[side].z;
    cam->up.x = sindf(ry) * sindf(rx);
    cam->up.y = cosdf(rx);
    cam->up.z = cosdf(ry) * sindf(rx);
}

f32 func_8010D5DC_bowser_toss(f32 a, f32 b) {
    f32 d;

    if (a >= 360.0f) {
        a -= 360.0f;
    } else if (a < 0.0f) {
        a += 360.0f;
    }
    if (b >= 360.0f) {
        b -= 360.0f;
    } else if (b < 0.0f) {
        b += 360.0f;
    }
    d = a - b;
    if (d <= -180.0f) {
        d += 360.0f;
    } else if (d >= 180.0f) {
        d -= 360.0f;
    }
    return d;
}

f32 func_8010D6E0_bowser_toss(f32 target, f32 cur, f32 step) {
    f32 d;
    f32 v;
    f64 e;

    BT_WRAP(target);
    BT_WRAP(cur);
    d = fmod(target - cur + 360.0, 360.0);
    if (d < 180.0) {
        if (d <= step) {
            v = d;
        } else {
            v = step;
        }
    } else {
        e = 360.0 - d;
        if (e <= step) {
            v = -e;
        } else {
            v = -step;
        }
    }
    v += cur;
    BT_WRAP(v);
    return v;
}

f32 func_8010D8A0_bowser_toss(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

f32 func_8010D8B8_bowser_toss(f32 t, f32 a, f32 b) {
    return func_8010D6E0_bowser_toss(b, a, fabsf(func_8010D5DC_bowser_toss(b, a) * t));
}

/* NON_MATCHING: masked 0; register allocation of the two source addresses. */
#ifdef NON_MATCHING
void func_8010D918_bowser_toss(f32* a, f32* b, f32* out, f32 t) {
    s32 i;

    for (i = 0; i < 16; i++) {
        out[i] = t * (b[i] - a[i]) + a[i];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D918_bowser_toss);
#endif

void func_8010D960_bowser_toss(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}

void *func_8010D98C_bowser_toss(omObjData *obj) {
    BtPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}

unk1EA70StructC* func_8010D9E0_bowser_toss(s16 model, s16 step, const char* part, s16 useOverlay, u16 frame) {
    D_800CCF58_main_Struct* anim;
    HmfData* hmf;
    unk1EA70StructC* rec;
    s16 idx;

    if (useOverlay) {
        anim = &D_800CCF58_main[HmfModelData[model].unk06];
    } else {
        anim = &D_800CCF58_main[HmfModelData[model].unk02];
    }
    hmf = HmfModelData[model].hmf;
    idx = func_8002C834_main(hmf, part);
    rec = HuMemAlloc(sizeof(unk1EA70StructC));
    rec->unk_08 = HuMemAlloc((anim->unk02 + step) / step * sizeof(Matrix4f));
    rec->unk_04 = HuMemAlloc(*(s16*)hmf->unk16 * sizeof(s16)); /* HmfData +0x16: part count (hmfman.h pads it) */
    rec->unk_00 = anim->unk02;
    rec->unk_02 = step;
    func_8010DB9C_bowser_toss(model, step, rec, idx, useOverlay, frame);
    return rec;
}

void func_8010DB9C_bowser_toss(s16 model, s16 step, unk1EA70StructC* rec, s16 part, s16 useOverlay, s16 frame) {
    HmfData* hmf = HmfModelData[model].hmf;
    D_800CCF58_main_Struct* base = &D_800CCF58_main[HmfModelData[model].unk02];
    D_800CCF58_main_Struct* over = &D_800CCF58_main[HmfModelData[model].unk06];
    s16 i;

    D_800D1358_main = rec->unk_08;
    D_800D04B4_main = rec->unk_04;
    D_800CD1B0_main = 0;
    guMtxIdentF(D_800D5A00_main[0]);
    if (useOverlay) {
        for (i = 0; i < over->unk02; i += step) {
            func_8002DFF8_main(hmf, frame, base, 1);
            func_8002DFF8_main(hmf, i, over, 0);
            D_800D138A_main = 0;
            func_80016C2C_main(hmf, 0, part);
        }
    } else {
        for (i = 0; i < base->unk02; i += step) {
            func_8002DFF8_main(hmf, i, base, 1);
            func_8002DFF8_main(hmf, frame, over, 0);
            D_800D138A_main = 0;
            func_80016C2C_main(hmf, 0, part);
        }
    }
}

void func_8010DDC4_bowser_toss(unk1EA70StructC* arg0) {
    HuMemFree(arg0->unk_08);
    HuMemFree(arg0->unk_04);
    HuMemFree(arg0);
}

s32 func_8010DDFC_bowser_toss(HuSprite_Unk84_Struct *arg0, RGBA *arg1, u8 arg2) {
    HmfData *temp_s4;
    Gfx *temp_v0_0;
    Gfx *temp_v0_2;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_s1;

    temp_v0_0 = temp_v0_2 = HuMemAlloc(0x10000);
    temp_v0 = func_8001A894_main(0x8C1, temp_v0_0, 4);
    temp_s4 = HmfModelData[temp_v0].hmf;
    temp_s4->unk60->unk50 |= 0x01010000;
    HuMemFree(temp_s4->unk3C);
    temp_s4->unk3C = HuMemAllocTag(0x18, D_800CDD6A_main);
    func_8010ED44_bowser_toss(arg0, temp_s4, 1.0f, 0, 0);
    gSPDisplayList(temp_v0_2++, osVirtualToPhysical(D_8010F4F0_bowser_toss));
    gDPPipeSync(temp_v0_2++);
    gDPSetCycleType(temp_v0_2++, G_CYC_1CYCLE);
    gDPPipeSync(temp_v0_2++);
    gSPClearGeometryMode(temp_v0_2++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(temp_v0_2++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(temp_v0_2++, G_CD_NOISE);
    gDPSetTexturePersp(temp_v0_2++, G_TP_NONE);
    gDPSetTextureFilter(temp_v0_2++, G_TF_BILERP);
    gDPSetTextureConvert(temp_v0_2++, G_TC_FILT);
    gDPSetAlphaDither(temp_v0_2++, G_AD_PATTERN);
    gDPSetAlphaCompare(temp_v0_2++, G_AC_NONE);
    gDPSetBlendColor(temp_v0_2++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(temp_v0_2++);
    if (arg2) {
        gDPSetRenderMode(temp_v0_2++, G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2);
    } else {
        gDPSetRenderMode(temp_v0_2++, G_RM_ZB_CLD_SURF, G_RM_NOOP2);
    }
    if (arg0->unk18 & 0x8000) {
        gDPSetCombineLERP(temp_v0_2++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(temp_v0_2++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(temp_v0_2++);
    gSPEndDisplayList(temp_v0_2++);
    temp_s0 = (u32)temp_v0_2 - (u32)temp_v0_0;
    temp_s4->unk3C->unk10 = HuMemAllocTag(temp_s0, temp_s4->unk0E);
    bcopy(temp_v0_0, temp_s4->unk3C->unk10, temp_s0);
    HuMemFree(temp_v0_0);
    temp_v0_0 = temp_v0_2 = HuMemAlloc(0x10000);
    gSPTexture(temp_v0_2++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(temp_v0_2++, G_TP_PERSP);
    if (arg0->unk1A >= 2) {
        gDPSetTextureLUT(temp_v0_2++, G_TT_RGBA16);
        if (arg0->unk18 == 4) {
            gDPLoadTLUT_pal16(temp_v0_2++, 0, arg0->unk0C);
        } else {
            gDPLoadTLUT_pal256(temp_v0_2++, arg0->unk0C);
        }
        gDPPipeSync(temp_v0_2++);
        var_a2 = 2;
    } else {
        gDPSetTextureLUT(temp_v0_2++, G_TT_NONE);
        gDPPipeSync(temp_v0_2++);
        var_a2 = (arg0->unk18 & 0x8000) ? 4 : 0;
    }
    switch (arg0->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(temp_v0_2++, 0x02000000, var_a2,
                                   arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(temp_v0_2++, 0x02000000, var_a2, G_IM_SIZ_8b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(temp_v0_2++, 0x02000000, var_a2, G_IM_SIZ_16b,
                                arg0->unk00->unk04, arg0->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(temp_v0_2++);
    gSPSegment(temp_v0_2++, 0x01, osVirtualToPhysical(temp_s4->unk44[0]));
    gSPVertex(temp_v0_2++, 0x01000000, 4, 0);
    gSP2Triangles(temp_v0_2++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(temp_v0_2++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(temp_v0_2++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(temp_v0_2++);
    gSPEndDisplayList(temp_v0_2++);
    temp_s0 = (u32)temp_v0_2 - (u32)temp_v0_0;
    temp_s4->unk3C->unk14 = HuMemAllocTag(temp_s0, temp_s4->unk0E);
    bcopy(temp_v0_0, temp_s4->unk3C->unk14, temp_s0);
    HuMemFree(temp_v0_0);
    for (var_s1 = 0; var_s1 < D_800D1FF0_main; var_s1++) {
        temp_v0_2 = temp_s4->unk3C->unk00[var_s1 + 1] = HuMemAllocTag(0x100, temp_s4->unk0E);
        gDPPipeSync(temp_v0_2++);
        gSPSegment(temp_v0_2++, 0x02, osVirtualToPhysical(arg0->unk00->unk00));
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s4->unk3C->unk10));
        gDPSetPrimColor(temp_v0_2++, 0, 0, arg1->r, arg1->g, arg1->b, arg1->a);
        gDPPipeSync(temp_v0_2++);
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s4->unk3C->unk14));
        gDPPipeSync(temp_v0_2++);
        gSPEndDisplayList(temp_v0_2++);
    }
    temp_s4->unk3C->unk00[0] = temp_s4->unk3C->unk00[D_800D2008_main + 1];
    return temp_v0;
}

s32 func_8010EA0C_bowser_toss(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2) {
    HmfModel *model = &HmfModelData[arg1];
    HmfData *src = model->hmf;
    HmfData *temp_s1;
    Gfx *temp_v0_2;
    s32 temp_v0;
    s32 var_s2;

    temp_v0 = func_8001A894_main(model->unk18, NULL, 4);
    temp_s1 = HmfModelData[temp_v0].hmf;
    temp_s1->unk60->unk50 = src->unk60->unk50;
    HuMemFree(temp_s1->unk3C);
    temp_s1->unk3C = HuMemAllocTag(0x18, D_800CDD6A_main);
    temp_s1->unk3C->unk10 = src->unk3C->unk10;
    temp_s1->unk3C->unk14 = src->unk3C->unk14;
    for (var_s2 = 0; var_s2 < D_800D1FF0_main; var_s2++) {
        temp_v0_2 = temp_s1->unk3C->unk00[var_s2 + 1] = HuMemAllocTag(0x100, temp_s1->unk0E);
        gDPPipeSync(temp_v0_2++);
        gSPSegment(temp_v0_2++, 0x02, osVirtualToPhysical(arg0->unk00->unk00));
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s1->unk3C->unk10));
        gDPSetPrimColor(temp_v0_2++, 0, 0, arg2->r, arg2->g, arg2->b, arg2->a);
        gDPPipeSync(temp_v0_2++);
        gSPDisplayList(temp_v0_2++, osVirtualToPhysical(temp_s1->unk3C->unk14));
        gDPPipeSync(temp_v0_2++);
        gSPEndDisplayList(temp_v0_2++);
    }
    temp_s1->unk3C->unk00[0] = temp_s1->unk3C->unk00[D_800D2008_main + 1];
    return temp_v0;
}

void func_8010EC10_bowser_toss(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3) {
    HmfModel *model = &HmfModelData[modelId];
    HmfData *temp_s3 = model->hmf;
    HmfModelData_Unk64_Unk3C_Struct *temp_v1 = temp_s3->unk3C;
    Gfx *temp_s0 = temp_v1->unk00[D_800D2008_main + 1];

    temp_v1->unk00[0] = temp_s0;
    gDPPipeSync(&temp_s0[0]);
    gSPSegment(&temp_s0[1], 0x02, osVirtualToPhysical(arg1->unk00[arg2].unk00));
    gSPDisplayList(&temp_s0[2], osVirtualToPhysical(temp_s3->unk3C->unk10));
    gDPSetPrimColor(&temp_s0[3], 0, 0, arg3->r, arg3->g, arg3->b, arg3->a);
    gDPPipeSync(&temp_s0[4]);
    gSPDisplayList(&temp_s0[5], osVirtualToPhysical(temp_s3->unk3C->unk14));
    gDPPipeSync(&temp_s0[6]);
    gSPEndDisplayList(&temp_s0[7]);
}

s32 func_8010ED44_bowser_toss(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
    Vtx *temp_s7;
    Vtx *var_s1;
    Vtx_t *var_t0;
    Vtx_t *var_a3;
    s32 var_a2;
    s32 temp_s4;
    s32 temp_a1;
    s32 sp24;
    s32 temp_f2;
    s32 var_s0;
    s32 var_s2;
    s32 sp2C;
    s32 temp_lo;
    s32 temp_s3;
    s32 var_s0_2;
    s32 var_a2_2;

    if (arg0->unk1A >= 2) {
        var_a2 = 0x800;
    } else {
        var_a2 = 0x1000;
    }
    temp_s4 = arg0->unk00->unk04;
    temp_a1 = arg0->unk00->unk06;
    sp24 = temp_s4 * 100.0 * arg2 / 32.0;
    temp_f2 = temp_a1 * 100.0 * arg2 / 32.0;
    if ((arg0->unk18 & 0xFFF) == 4) {
        var_s0 = ((temp_s4 + 1) & 0xFFFE) * temp_a1 * 4;
    } else {
        var_s0 = temp_s4 * temp_a1 * arg0->unk18;
    }
    var_s0 = (var_s0 < 0) ? (var_s0 + 7) : var_s0;
    var_s0 >>= 3;
    var_s2 = var_s0 / var_a2;
    if (var_s2 <= 0) {
        var_s2 = 1;
    }
    sp2C = temp_a1 / var_s2;
    temp_lo = temp_f2 / var_s2;
    temp_s3 = var_s2 * 4;
    temp_s7 = var_s1 = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
    memset(temp_s7, 0, temp_s3 * sizeof(Vtx));
    for (var_s0_2 = 0; var_s0_2 < var_s2; var_s0_2++, var_s1 += 4) {
        var_s1[0].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[0].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[0].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[0].v.tc[1] = 0;
        var_s1[1].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[1].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[1].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[1].v.tc[1] = (sp2C - 1) * 64;
        var_s1[2].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[2].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[2].v.tc[0] = 0;
        var_s1[2].v.tc[1] = 0;
        var_s1[3].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[3].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[3].v.tc[0] = 0;
        var_s1[3].v.tc[1] = (sp2C - 1) * 64;
        for (var_a2_2 = 0; var_a2_2 < 4; var_a2_2++) {
            var_s1[var_a2_2].v.ob[0] += arg3;
            var_s1[var_a2_2].v.ob[1] += arg4;
            var_s1[var_a2_2].v.ob[2] = 0;
            var_s1[var_a2_2].v.flag = 0;
            var_s1[var_a2_2].v.cn[3] = 0xFF;
            var_s1[var_a2_2].v.cn[0] = var_s1[var_a2_2].v.cn[1] = var_s1[var_a2_2].v.cn[2] = 0;
        }
    }
    var_s1 = temp_s7;
    for (var_s0_2 = 0; var_s0_2 < D_800D1FF0_main; var_s0_2++) {
        arg1->unk44[var_s0_2] = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
        var_t0 = &arg1->unk44[var_s0_2]->v;
        var_a3 = &var_s1->v;
        for (var_a2_2 = 0; var_a2_2 < temp_s3; var_a2_2++) {
            *(var_t0++) = *(var_a3++);
        }
    }
    HuMemFree(temp_s7);
    return var_s2;
}
