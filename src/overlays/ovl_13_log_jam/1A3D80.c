#include "common.h"
// m1 lj1: Log Jam (two teams of two)
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"

/* One player (D_8010E5B8_log_jam, 4 x 0x38). */
typedef struct LjPlayer {
    /* 0x00 */ s16 unk00; /* slot 0..3 */
    /* 0x02 */ s16 unk02; /* role in the team: 0 or 1 (1 carries the hook) */
    /* 0x04 */ s16 unk04; /* team */
    /* 0x06 */ s16 unk06; /* pending result motion: 0 win, 1 lose, -1 none */
    /* 0x08 */ s16 unk08; /* state */
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C; /* frame counter */
    /* 0x0E */ s16 unk0E; /* jump length */
    /* 0x10 */ f32 unk10; /* vertical speed */
    /* 0x14 */ s32 unk14; /* win voice file */
    /* 0x18 */ s16 unk18; /* GwPlayer index */
    /* 0x1A */ s16 unk1A; /* controller port */
    /* 0x1C */ s16 unk1C; /* character */
    /* 0x1E */ s16 unk1E; /* CPU */
    /* 0x20 */ s16 unk20; /* CPU difficulty */
    /* 0x22 */ s16 unk22; /* log held, -1 none */
    /* 0x24 */ s16 unk24; /* CPU: target, -1 none */
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28; /* CPU: frames since the last press */
    /* 0x2A */ s16 unk2A; /* CPU: frames to wait */
    /* 0x2C */ u16 unk2C; /* CPU: buttons to press */
    /* 0x2E */ s16 unk2E; /* CPU: misses in a row */
    /* 0x30 */ s16 unk30; /* CPU: 4 - difficulty */
    /* 0x32 */ s16 unk32; /* motion */
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char unk36[2];
} LjPlayer; // Size 0x38

/* One team (D_8010E5AC_log_jam, 2 x 0x48). */
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} LjRGBA;

/* One log (D_8010E5C4_log_jam, 32 x 0x78). */
typedef struct LjLog {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ s16 unk02[3]; /* models */
    /* 0x08 */ s16 unk08; /* active */
    /* 0x0A */ s16 unk0A; /* kind */
    /* 0x0C */ s16 unk0C; /* state */
    /* 0x0E */ s16 unk0E; /* state timer */
    /* 0x10 */ Vec unk10; /* position */
    /* 0x1C */ Vec unk1C; /* rotation */
    /* 0x28 */ Vec unk28; /* velocity */
    /* 0x34 */ s16 unk34; /* piece: 0 left half, 1 right half */
    /* 0x36 */ char unk36[0x1C];
    /* 0x52 */ s16 unk52; /* piece state */
    /* 0x54 */ f32 unk54; /* spin speed */
    /* 0x58 */ f32 unk58; /* wobble amplitude */
    /* 0x5C */ f32 unk5C; /* wobble decay */
    /* 0x60 */ f32 unk60; /* wobble phase */
    /* 0x64 */ f32 unk64; /* wobble speed */
    /* 0x68 */ f32 unk68; /* resting roll */
    /* 0x6C */ char unk6C[8];
    /* 0x74 */ void (*unk74)(struct LjLog*);
} LjLog; // Size 0x78

/* A cloud sprite (D_8010E5D4_log_jam, 5 x 0x24). */
typedef struct LjCloud {
    /* 0x00 */ s16 id; /* index */
    /* 0x02 */ s16 grp; /* sprite group */
    /* 0x04 */ s16 angle; /* wobble phase, degrees */
    /* 0x08 */ f32 scale; /* base scale */
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 sx; /* scale x */
    /* 0x18 */ f32 sy; /* scale y */
    /* 0x1C */ f32 speed; /* drift per frame */
    /* 0x20 */ s32 unk20;
} LjCloud; // Size 0x24

typedef struct LjTeam {
    /* 0x00 */ omObjData* unk00; /* player objects */
    /* 0x04 */ omObjData* unk04;
    /* 0x08 */ LjPlayer* unk08;
    /* 0x0C */ LjPlayer* unk0C;
    /* 0x10 */ s16 unk10; /* team index */
    /* 0x12 */ s16 unk12; /* score */
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ Vec unk24;
    /* 0x30 */ Vec unk30;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
} LjTeam; // Size 0x48


u8 func_8000B638_main(void);
void func_800E6F0C_minigame(s32);

void func_80105B9C_log_jam(omObjData* obj);
void func_80105C10_log_jam(omObjData* obj);
void func_801060C4_log_jam(omObjData* obj);
void func_801060E8_log_jam(omObjData* obj);
void func_80106190_log_jam(void);
void func_801065E8_log_jam(omObjData* obj);
void func_80106968_log_jam(omObjData* obj);
void func_80106FAC_log_jam(void);
void func_80108D50_log_jam(void);
s16 func_80108CE0_log_jam(s16 arg0);
void func_801091DC_log_jam(void);
void func_80109A00_log_jam(void);
void func_80109AD8_log_jam(void);
void func_80109B34_log_jam(void);
void func_8010A344_log_jam(void);
void func_8010A724_log_jam(void);
void func_8010ABA4_log_jam(void);
void func_8010B04C_log_jam(void);
void func_8010C55C_log_jam(omObjData* obj, u32 value);
void func_80107080_log_jam(omObjData* obj, LjTeam* team);
void func_80107C84_log_jam(omObjData* obj, LjTeam* team);
void func_8010A6FC_log_jam(s16 team, s16 score);
LjLog* func_8010910C_log_jam(s16 idx);
void func_8010925C_log_jam(s16 idx);
s32 func_8010A9D4_log_jam(Vec* pos, Vec* vel, Vec* scale, f32 speed, LjRGBA* color);
f32 func_8010C514_log_jam(f32 target, f32 cur, f32 step);
void func_80106F48_log_jam(omObjData* obj);
void func_8010C714_log_jam(omObjData* obj, s16 arg1, s16 arg2);
void func_8010C7F8_log_jam(omObjData* obj);
void func_8010C8B0_log_jam(omObjData* obj);
s16 func_80109A7C_log_jam(s16 kind, s16 part);
void func_8001EF6C_main(s16 arg0, s16 arg1, const char* arg2);
void func_80108840_log_jam(omObjData* obj, LjTeam* team);
void func_80108A80_log_jam(omObjData* obj, LjTeam* team);
s16 func_80108D1C_log_jam(f32 v, f32 g);
void func_80109140_log_jam(s16 idx, f32 x, f32 y, f32 z);
void func_80109190_log_jam(s16 idx, f32 x, f32 y, f32 z);
void func_8010C7D0_log_jam(omObjData* obj);
s32 func_8010AE58_log_jam(Vec* pos, Vec* vel, Vec* scale, f32 speed, LjRGBA* color);
omObjData* func_80045F1C_main(u32, s16, s16);
void func_800E4C88_minigame(omObjData* obj, s32 idx, f32 x, f32 y, f32 z, f32 a, f32 b);
void func_8010C6A4_log_jam(omObjData* obj, s16 arg1, s16 arg2);
void func_80109350_log_jam(s16 idx);
void* func_8010C588_log_jam(omObjData* obj);
void func_80108E54_log_jam(omObjData* obj);
void func_80109B8C_log_jam(omObjData* obj);
void func_8010A0B0_log_jam(omObjData* obj);
s16 func_80109044_log_jam(s16 kind, s16 part);
void func_801094E4_log_jam(LjLog* log);

extern s32 D_800A178C_main[][6];
extern u16 D_800D5558_main[];

extern omObjData* D_8010E590_log_jam;
extern s32 D_8010E594_log_jam;
extern s32 D_8010E598_log_jam;
extern s32 D_8010E59C_log_jam;
extern s32 D_8010E5A0_log_jam;
extern s32 D_8010E5A4_log_jam;
extern s32 D_8010E5A8_log_jam;
extern LjTeam* D_8010E5AC_log_jam;
extern omObjData* D_8010E5B0_log_jam[2]; /* team objects */
extern LjPlayer* D_8010E5B8_log_jam;
extern s16 D_8010E5BC_log_jam;
extern D_80111B50_vine_with_me_Struct D_8010E640_log_jam;
extern LjLog* D_8010E5C4_log_jam;
extern omObjData* D_8010E5C0_log_jam;
extern s16* D_8010E5C8_log_jam; /* log model templates, 3 kinds x 3 parts */
extern u8 D_800D6A90_main;
extern omObjData* D_800EC1C0_minigame[];
// end m1 lj1

// m1 lj2
/* lj2 names lj1's LjRGBA RGBA. */
typedef LjRGBA RGBA;

typedef struct LjEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ RGBA color;
    /* 0x08 */ f32 frame;
    /* 0x0C */ f32 speed;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec vel;
    /* 0x28 */ Vec scale;
} LjEffect; // Size 0x34

typedef struct LjCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} LjCamera; // Size 0x24

typedef struct LjBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} LjBytes;

typedef union LjPack {
    void *p;
    LjBytes b;
} LjPack;

typedef struct LjCounter {
    /* 0x00 */ s16 id;
    /* 0x02 */ s16 grp;
    /* 0x04 */ s16 timer;
    /* 0x06 */ s16 digit; /* member popping in */
    /* 0x08 */ s16 value;
    /* 0x0A */ s16 shown;
} LjCounter; // Size 0xC

typedef struct LjVec2 {
    f32 x;
    f32 y;
} LjVec2;

#define LJ_WRAP(v)             \
    if ((v) >= 360.0) {        \
        (v) -= 360.0;          \
    } else if ((v) < 0.0) {    \
        (v) += 360.0;          \
    }

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
extern s32 fontcolor;
extern s8 HmfPauseF;
extern s16 *D_8010E5CC_log_jam; // s16[0x20] sprite/file ids
extern LjCounter *D_8010E5D0_log_jam;
extern LjCloud *D_8010E5D4_log_jam;
extern omObjData *D_8010E5D8_log_jam;
extern LjEffect *D_8010E5DC_log_jam;
extern omObjData *D_8010E5E0_log_jam;
extern LjEffect *D_8010E5E4_log_jam;
extern LjCamera D_8010E5E8_log_jam[2];
extern s32 D_8010E630_log_jam;
extern s32 D_8010E634_log_jam;
extern s32 D_8010E638_log_jam;

/* .data (0x8010DE90..0x8010E1D0). Inner labels the remaining asm uses are undefined_syms.txt aliases. */
Vec D_8010DE90_log_jam[4] = { /* D_8010DE98 = [0].z */
    { -233.0f, 0.0f, 70.0f }, { -131.0f, 0.0f, -5.0f }, { 131.0f, 0.0f, -5.0f }, { 233.0f, 0.0f, 70.0f },
};
Vec D_8010DEC0_log_jam[4] = { /* D_8010DEC8 = [0].z */
    { -170.0f, 0.0f, 40.0f }, { -128.0f, 0.0f, 20.0f }, { 128.0f, 0.0f, 20.0f }, { 170.0f, 0.0f, 40.0f },
};
Vec D_8010DEF0_log_jam[4] = { /* D_8010DEF8 = [0].z */
    { -70.0f, 0.0f, 200.0f }, { -190.0f, 0.0f, 250.0f }, { 190.0f, 0.0f, 250.0f }, { 70.0f, 0.0f, 200.0f },
};
f32 D_8010DF20_log_jam[4] = { 45.0f, 15.0f, -15.0f, -45.0f };
Vec D_8010DF30_log_jam[2] = { /* D_8010DF34 = [0].y, D_8010DF38 = [0].z */
    { -100.0f, 50.0f, 115.0f },
    { 100.0f, 50.0f, 115.0f },
};
RGBA D_8010DF48_log_jam = { 0xE9, 0xDD, 0xA1, 0x80 };
RGBA D_8010DF4C_log_jam = { 0xFF, 0xFF, 0xFF, 0xFF };
s32 D_8010DF50_log_jam[8] = { 0x200A5, 0x300A5, 0x700A5, 0x400A5, 0x500A5, 0x600A5, 0x800A5, 0x9001C };
s32 D_8010DF70_log_jam[8] = { 0x200A6, 0x300A6, 0x700A6, 0x400A6, 0x500A6, 0x600A6, 0x800A6, 0x9001D };
s32 D_8010DF90_log_jam = 0; /* D_8010DF92 = its low half */
s32 D_8010DF94_log_jam[4] = { 0, 1, 2, 3 };
s16 D_8010DFA4_log_jam[4][2][2] = { /* fallback teams */
    { { 0, 1 }, { 2, 3 } }, { { 3, 0 }, { 1, 2 } }, { { 2, 3 }, { 0, 1 } }, { { 1, 2 }, { 3, 0 } },
};
s16 D_8010DFC4_log_jam[4] = { 0, 1, 1, 0 };
s16 D_8010DFCC_log_jam[4] = { 0x12, 0x13, 0x15, 0x14 };
s32 D_8010DFD4_log_jam[8] = { 0x20000, 0x30000, 0x70000, 0x40000, 0x50000, 0x60000, 0x80000, 0x90000 }; /* D_8010DFE8 = [5] */
s32 D_8010DFF4_log_jam[4] = { 0x2F, 0x30, 0x36, 0x37 }; /* D_8010DFF6/D_8010DFFE = low halves of [0]/[2] */
s32 D_8010E004_log_jam[3] = { 3, 4, 5 };
f32 D_8010E010_log_jam[8] = { 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 250.0f, 200.0f, 200.0f };
s32 D_8010E030_log_jam[9] = { 0x340003, 0x340004, 0x340005, 0x340006, 0x340007, 0x340008, 0x340009, 0x34000A, 0x34000B };
LjVec2 D_8010E054_log_jam[5] = { /* cloud start positions; D_8010E058 = [0].y */
    { 120.0f, 30.0f }, { 360.0f, 45.0f }, { 0.0f, 52.0f }, { 240.0f, 60.0f }, { 480.0f, 75.0f },
};
f32 D_8010E07C_log_jam[5] = { 0.7f, 0.6f, 0.55f, 0.47f, 0.4f }; /* cloud scales */
s16 D_8010E090_log_jam[2] = { 38, 282 }; /* counter x */
s32 D_8010E094_log_jam = 0; /* debug camera mode */
s32 D_8010E098_log_jam = 0; /* debug text x; D_8010E09A = low half */
s32 D_8010E09C_log_jam = 0; /* debug text y; D_8010E09E = low half */

Gfx D_8010E0A0_log_jam[] = {
    gsSPSegment(0x00, 0x00000000),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPNoOp(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_8010E158_log_jam[] = {
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx D_8010E178_log_jam[] = {
    gsSPDisplayList(D_8010E158_log_jam),
    gsSPDisplayList(D_8010E0A0_log_jam),
    gsSPEndDisplayList(),
};

Gfx D_8010E190_log_jam[] = {
    gsDPPipeSync(),
    gsSPDisplayList(D_8010E178_log_jam),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

u16 func_8010A300_log_jam(s32 dirAndFile);
void func_8010A4C0_log_jam(omObjData *obj);
void func_8010A880_log_jam(omObjData *obj);
void func_8010AD04_log_jam(omObjData *obj);
s32 func_8010CB64_log_jam(HuSprite_Unk84_Struct *spr, RGBA *color);
s32 func_8010D74C_log_jam(HuSprite_Unk84_Struct *spr, u16 model, RGBA *color);
void func_8010B86C_log_jam(omObjData *obj);
void func_8010BCA8_log_jam(s32 idx);
void func_8010BE94_log_jam(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
void func_8010C084_log_jam(s32 idx);
f32 func_8010C1D8_log_jam(f32 a, f32 b);
f32 func_8010C2DC_log_jam(f32 target, f32 cur, f32 step);
f32 func_8010C49C_log_jam(f32 t, f32 a, f32 b);
f32 func_8010C4B4_log_jam(f32 t, f32 a, f32 b);
f32 fabsf(f32);
f64 fabs(f64);
f64 fmod(f64, f64);
s32 func_8010DA84_log_jam(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8010D950_log_jam(u16 model, HuSprite_Unk84_Struct *spr, u16 frame, RGBA *color);
void func_8010C5DC_log_jam(omObjData *obj, s16 slot, s16 frames);
void func_800E4BA4_minigame(u8 mdl);
typedef f32 Matrix4f[4][4];
extern Matrix4f *D_800D1358_main; /* matrix table being filled */
extern s16 *D_800D04B4_main;      /* per matrix: its motion object */
extern s16 D_800CD1B0_main;       /* matrices written */
extern s16 D_800D138A_main;       /* matrix stack depth */
extern Matrix4f D_800D5A00_main[]; /* matrix stack */
void func_8002DFF8_main(HmfData *, f32, D_800CCF58_main_Struct *, s32);
void func_8002EAC0_main(HmfData *, f32, f32);
s16 func_8002C834_main(HmfData *, const char *);
void func_8008A070_main(Matrix4f);
void func_80017CD0_main(Matrix4f, f32, f32, f32);
void func_80017D24_main(Matrix4f, f32, f32, f32);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
void func_80016C2C_main(HmfData *arg0, s16 arg1, s16 arg2);
void func_8010C8E0_log_jam(s16 mdl, const char *part, Matrix4f *out);
void func_8010CAC0_log_jam(omObjData *obj, const char *part, Matrix4f out);

// end m1 lj2

void func_801059A0_log_jam(void) {
    u8 cam;

    Hu3DAnimInit(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(0x10);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 4000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_8010E5A0_log_jam = 900;
    D_8010E59C_log_jam = 0;
    D_8010E598_log_jam = 0;
    D_8010E5A4_log_jam = -1;
    D_8010E5A8_log_jam = 0;
    D_8010E5BC_log_jam = -1;
    D_8010E5CC_log_jam = HuMemAllocTag(0x40, 31000);
    D_8010E590_log_jam = omAddObj(0x20, 0, 0, -1, func_80105B9C_log_jam);
    memset(&D_8010E640_log_jam, 0, 0x28);
    D_8010E640_log_jam.unk01 = 4;
    func_800E5EA0_minigame(&D_8010E640_log_jam);
}

void func_80105B9C_log_jam(omObjData* obj) {
    obj->func = func_80105C10_log_jam;
    func_80109B34_log_jam();
    func_8010A344_log_jam();
    func_8010A724_log_jam();
    func_8010ABA4_log_jam();
    func_80109A00_log_jam();
    func_80106190_log_jam();
    func_80108D50_log_jam();
    func_8010B04C_log_jam();
    if (_CheckFlag(0xA) != 0) {
        D_8010E594_log_jam = 1;
    }
}

void func_80105C10_log_jam(omObjData* obj) {
    LjTeam* t0;
    LjTeam* t1;

    switch (D_8010E5A4_log_jam) {
    case -1:
        if (D_8010E59C_log_jam >= 2) {
            WipeCreateIn(0xFF, 0x10);
            D_8010E5A4_log_jam = 0;
            D_8010E59C_log_jam = 0;
        }
        break;
    case 0:
        if (WipeStatGet() == 0) {
            GMesCreate(5);
            HuAudFXPlay(0xE);
            D_8010E5A4_log_jam++;
            D_8010E59C_log_jam = 0;
        }
        break;
    case 1:
        if (D_8010E59C_log_jam == 30) {
            HuAudSeqPlay(0x2E);
        }
        if (GMesStatGet() == 0) {
            GMesCreate(0x1A, (D_8010E5A0_log_jam + 29) / 30, 0x9C, 0x20);
            func_800E6F0C_minigame(2);
            D_8010E5A4_log_jam++;
        }
        break;
    case 2:
        func_8003F578_main((D_8010E5A0_log_jam-- + 28) / 30);
        if (D_8010E5A0_log_jam <= 0) {
            func_8003F5C0_main();
            GMesCreate(0x10);
            func_800E6F0C_minigame(3);
            HuAudSeqFadeOut(0x78);
            D_8010E5A0_log_jam = 0;
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    case 3:
        if (func_80108CE0_log_jam(0xE) != 0 && GMesStatGet() == 0) {
            func_800E6F0C_minigame(4);
            func_801091DC_log_jam();
            func_80106FAC_log_jam();
            func_80109AD8_log_jam();
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    case 4:
        if (func_80108CE0_log_jam(0x11) != 0) {
            t0 = func_8010C588_log_jam(D_8010E5B0_log_jam[0]);
            t1 = func_8010C588_log_jam(D_8010E5B0_log_jam[1]);
            if (t0->unk12 > t1->unk12) {
                GMesCreate(0x1E, t0->unk08->unk1C, t0->unk0C->unk1C);
                GwPlayer[t0->unk08->unk18].bonusCoin += 10;
                GwPlayer[t0->unk0C->unk18].bonusCoin += 10;
                t0->unk08->unk06 = t0->unk0C->unk06 = 0;
                t1->unk08->unk06 = t1->unk0C->unk06 = 1;
                HuAudSeqPlay(0x66);
                D_8010E5A8_log_jam = 0x8C;
            } else if (t0->unk12 < t1->unk12) {
                GMesCreate(0x1E, t1->unk08->unk1C, t1->unk0C->unk1C);
                GwPlayer[t1->unk08->unk18].bonusCoin += 10;
                GwPlayer[t1->unk0C->unk18].bonusCoin += 10;
                t0->unk08->unk06 = t0->unk0C->unk06 = 1;
                t1->unk08->unk06 = t1->unk0C->unk06 = 0;
                HuAudSeqPlay(0x66);
                D_8010E5A8_log_jam = 0x8C;
            } else {
                GMesCreate(0x20);
                t0->unk08->unk06 = t0->unk0C->unk06 = 1;
                t1->unk08->unk06 = t1->unk0C->unk06 = 1;
                HuAudSeqPlay(0x6C);
                D_8010E5A8_log_jam = 0x90;
            }
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    case 5:
        if (GMesStatGet() == 0) {
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    case 6:
        if (D_8010E59C_log_jam >= 16) {
            WipeCreateOut(0, 0x10);
            HuAudSeqFadeOut(0x10);
            func_8004AB0C_main(0x10);
            D_8010E59C_log_jam = 0;
            D_8010E5A4_log_jam++;
        }
        break;
    default:
        if (WipeStatGet() == 0) {
            obj->func = func_801060C4_log_jam;
        }
        break;
    }
    func_801060E8_log_jam(obj);
    D_8010E598_log_jam++;
    D_8010E59C_log_jam++;
}

void func_801060C4_log_jam(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_801060E8_log_jam(omObjData* obj) {
    if (D_8010DF90_log_jam != 0) {
        if (D_8010DF90_log_jam == 1) {
            obj->func = func_801060C4_log_jam;
        }
        D_8010DF90_log_jam--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010DF90_log_jam = 0x10;
        WipeCreateOut(0, (s16)D_8010DF90_log_jam);
        HuAudSeqFadeOut((s16)D_8010DF90_log_jam);
        func_8004AB0C_main((s16)D_8010DF90_log_jam);
    }
}

#ifdef NON_MATCHING
/* Differs: the group switch keeps one register copy fewer (retail moves the group into v1). */
void func_80106190_log_jam(void) {
    s32 grp[2][2];
    LjTeam* team;
    LjPlayer* pl;
    omObjData* o;
    s32 bad;
    s32 n0;
    s32 n1;
    s32 n2;
    s32 n3;
    s32 i;
    s32 j;
    s16 (*tbl)[2];
    s32 g;

    team = D_8010E5AC_log_jam = HuMemAllocTag(sizeof(LjTeam) * 2, 31000);
    memset(team, 0, sizeof(LjTeam) * 2);
    D_8010E5B8_log_jam = HuMemAllocTag(sizeof(LjPlayer) * 4, 31000);
    memset(D_8010E5B8_log_jam, 0, sizeof(LjPlayer) * 4);
    bad = 0;
    n3 = 0;
    n2 = 0;
    n1 = 0;
    n0 = 0;
    for (i = 0; i < 4; i++) {
        switch (g = GwPlayer[D_8010DF94_log_jam[i]].group) {
        case 0:
            if (n0 > 0) {
                bad = 1;
            } else {
                grp[0][1] = D_8010DF94_log_jam[i];
                n0++;
            }
            break;
        case 1:
            if (n1 > 0) {
                bad = 1;
            } else {
                grp[0][0] = D_8010DF94_log_jam[i];
                n1++;
            }
            break;
        case 2:
            if (n2 > 0) {
                bad = 1;
            } else {
                grp[1][0] = D_8010DF94_log_jam[i];
                n2++;
            }
            break;
        case 3:
            if (n3 > 0) {
                bad = 1;
            } else {
                grp[1][1] = D_8010DF94_log_jam[i];
                n3++;
            }
            break;
        default:
            bad = 1;
            break;
        }
        if (bad != 0) {
            break;
        }
    }
    if (bad != 0) {
        tbl = D_8010DFA4_log_jam[rand8() & 3];
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                grp[i][j] = tbl[i][j];
            }
        }
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    for (i = 0; i < 2; i++, team++) {
        team->unk10 = i;
        team->unk12 = 0;
        team->unk14 = 0;
        team->unk16 = -1;
        team->unk18 = -1;
        team->unk1A = 0;
        team->unk1C = -1;
        team->unk1E = 0;
        team->unk20 = 0;
        team->unk24.x = team->unk24.y = team->unk24.z = 0.0f;
        team->unk30.x = team->unk30.y = team->unk30.z = 0.0f;
        team->unk3C = 0.0f;
        team->unk40 = team->unk44 = 0.0f;
        D_8010E5B0_log_jam[i] = omAddObj(i + 0x10, 0, 0, -1, func_801065E8_log_jam);
        func_8010C55C_log_jam(D_8010E5B0_log_jam[i], (u32)team);
        for (j = 0; j < 2; j++) {
            pl = &D_8010E5B8_log_jam[i * 2 + j];
            pl->unk00 = i * 2 + j;
            pl->unk04 = i;
            pl->unk02 = D_8010DFC4_log_jam[pl->unk00];
            pl->unk18 = grp[i][j];
            o = D_800EC598_minigame[D_800EC280_minigame] = omAddObj(D_8010DFCC_log_jam[pl->unk00], 8, 11, -1, func_80106968_log_jam);
            D_800EC280_minigame++;
            o->trans.x = D_8010DE90_log_jam[pl->unk00].x;
            o->trans.z = D_8010DE90_log_jam[pl->unk00].z;
            o->rot.y = D_8010DF20_log_jam[pl->unk00];
            func_8010C55C_log_jam(o, (u32)pl);
            if (pl->unk02 == 0) {
                team->unk00 = o;
                team->unk08 = pl;
            } else {
                team->unk04 = o;
                team->unk0C = pl;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106190_log_jam);
#endif


const Vec D_8010E1F0_log_jam = { 0.7f, 0.7f, 0.7f }; /* effect scale */

void func_801065E8_log_jam(omObjData* obj) {
    Vec pos;
    Vec scale = D_8010E1F0_log_jam;
    LjTeam* team;
    LjLog* log;
    s16 done;

    done = 0;
    team = func_8010C588_log_jam(obj);
    func_80107080_log_jam(team->unk00, team);
    func_80107C84_log_jam(team->unk04, team);
    if (team->unk12 >= 30) {
        team->unk12 = 29;
    }
    func_8010A6FC_log_jam(team->unk10, team->unk12);
    if (func_800E6E8C_minigame() == 3 && team->unk16 != -1) {
        log = func_8010910C_log_jam(team->unk16);
        pos.x = log->unk10.x;
        pos.z = log->unk10.z;
        pos.y = log->unk10.y + 40.00000059604645;
        func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, &D_8010DF4C_log_jam);
        func_8010925C_log_jam(team->unk16);
        team->unk16 = team->unk18 = -1;
    }
    if (team->unk1C != -1) {
        team->unk30.x += team->unk40;
        team->unk30.y += team->unk44;
        team->unk24.y += team->unk3C;
        team->unk3C -= 1.6333001f;
        team->unk24.x = func_8010C514_log_jam(D_8010DF30_log_jam[(s16)(team->unk10 ^ 1)].x, team->unk24.x, 7.0f);
        team->unk24.z = func_8010C514_log_jam(D_8010DF30_log_jam[(s16)(team->unk10 ^ 1)].z, team->unk24.z, 7.0f);
        if (team->unk24.y < 184.0000033378601 && team->unk3C <= 0.0f) {
            done = 1;
            team->unk30.x = -225.0f;
            team->unk24.y = 184.0f;
        }
        Hu3DModelPosSet(team->unk1C, team->unk24.x, team->unk24.y, team->unk24.z);
        Hu3DModelRotSet(team->unk1C, 0.0f, team->unk30.y, 0.0f);
        if (team->unk20 >= 0) {
            pos.x = team->unk24.x;
            pos.z = team->unk24.z;
            pos.y = team->unk24.y - 50.0;
            func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, &D_8010DF4C_log_jam);
            func_8001C258_main(team->unk1C, 4, 4);
            done = 1;
        }
        func_8008A070_main((f32(*)[4])HmfModelData[team->unk1C].mtx);
        func_80017C10_main((Mtx*)HmfModelData[team->unk1C].mtx, 0.0f, -50.0f, 0.0f);
        func_80017D24_main((f32(*)[4])HmfModelData[team->unk1C].mtx, team->unk30.x, 0.0f, 0.0f);
        team->unk20++;
        if (done != 0) {
            team->unk1C = -1;
        }
    }
    team->unk1A++;
}

const char D_8010E218_log_jam[] = "item_hook"; /* hook attach point */

#ifdef NON_MATCHING
/* Differs: the character-table loads for func_800E1BA8_minigame and the voice pointer take other registers/slots. */
void func_80106968_log_jam(omObjData* obj) {
    LjPlayer* pl;
    s32* voice;
    s16 chr;
    s16 i;
    s16 gw;
    func_800E1BA8_minigame_ObjData* w;

    pl = func_8010C588_log_jam(obj);
    gw = pl->unk18;
    chr = GwPlayer[gw].chr;
    pl->unk1C = chr;
    pl->unk1A = GwPlayer[gw].pad;
    pl->unk1E = GwPlayer[gw].stat & 1;
    pl->unk20 = GwPlayer[gw].cpu_difficulty;
    func_800E1BA8_minigame(obj, D_800A178C_main[chr][0], D_800A178C_main[chr][2], gw, 0x6A9, 0x299);
    w = obj->data;
    w->unk50 &= ~1;
    w->unkEC = NULL;
    if (pl->unk02 == 1) {
        obj->model[2] = func_8000B108_main(0x340000, 0xB9);
        func_8001C258_main(obj->model[2], 0x4000, 0x4000);
        func_8001EF6C_main(obj->model[2], obj->model[0], D_8010E218_log_jam);
        for (i = 0; i < 3; i++) {
            obj->model[3 + i] = func_80109A7C_log_jam(i, 0);
            func_8001C258_main(obj->model[3 + i], 4, 4);
            func_8001C258_main(obj->model[3 + i], 0x4000, 0x4000);
            func_8001EF6C_main(obj->model[3 + i], obj->model[2], "m219-item-f");
        }
    } else {
        for (i = 0; i < 3; i++) {
            obj->model[3 + i] = func_80109A7C_log_jam(i, 0);
            func_8001C258_main(obj->model[3 + i], 4, 4);
            func_8001C258_main(obj->model[3 + i], 0x4000, 0x4000);
            func_8001EF6C_main(obj->model[3 + i], obj->model[0], D_8010E218_log_jam);
        }
    }
    obj->model[6] = func_8000B108_main(8, 0x68D);
    Hu3DModelScaleSet(obj->model[6], 0.5f, 0.5f, 0.5f);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 6), 1, 0x1B);
    if (pl->unk02 == 1) {
        func_800E5A00_minigame(obj, 3, func_80017BB8_main(chr, 0x74), 0, 0x14);
        func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x75), 0, 0xA);
        func_800E5A00_minigame(obj, 5, func_80017BB8_main(chr, 0x81), 0, 8);
        func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 0x76), 1, 0);
    } else {
        func_800E5A00_minigame(obj, 7, func_80017BB8_main(chr, 0x77), 0, 0x1E);
        func_800E5A00_minigame(obj, 8, func_80017BB8_main(chr, 0x78), 0, 0x28);
    }
    if (chr == 5) {
        func_800E5A00_minigame(obj, 9, func_80017BB8_main(5, 0x31), 1, 0x78);
        pl->unk14 = D_8010DFD4_log_jam[5] | 0x31;
    } else if (chr == 1 || chr == 6) {
        func_800E5A00_minigame(obj, 9, func_80017BB8_main(chr, (s16)D_8010DFF4_log_jam[0]), 1, 0x78);
        pl->unk14 = D_8010DFD4_log_jam[chr] | D_8010DFF4_log_jam[0];
    } else {
        voice = &D_8010DFF4_log_jam[rand8() & 1];
        func_800E5A00_minigame(obj, 9, func_80017BB8_main(chr, (s16)*voice), 1, 0x78);
        pl->unk14 = D_8010DFD4_log_jam[chr] | *voice;
    }
    func_800E5A00_minigame(obj, 10, func_80017BB8_main(chr, (s16)D_8010DFF4_log_jam[2]), 1, 0x78);
    pl->unk06 = -1;
    pl->unk0C = 0;
    pl->unk0A = 0;
    pl->unk22 = -1;
    pl->unk24 = -1;
    pl->unk26 = -1;
    pl->unk10 = 0.0f;
    pl->unk0E = 0;
    pl->unk28 = 0;
    pl->unk2A = 10;
    pl->unk2C = 0;
    pl->unk2E = 0;
    pl->unk30 = 4 - pl->unk20;
    if (pl->unk02 == 0) {
        pl->unk08 = 0;
        func_8010C5DC_log_jam(obj, 0, 5);
        pl->unk32 = 0;
    } else {
        pl->unk08 = 5;
        func_8010C714_log_jam(obj, 4, 7);
        pl->unk32 = 4;
    }
    pl->unk34 = 0;
    obj->func = func_80106F48_log_jam;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106968_log_jam);
#endif

void func_80106F48_log_jam(omObjData* obj) {
    LjPlayer* pl = func_8010C588_log_jam(obj);

    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    pl->unk0C++;
    func_8010C7F8_log_jam(obj);
    func_8010C8B0_log_jam(obj);
}

void func_80106FAC_log_jam(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            if (D_800EC598_minigame[i]->model[D_8010E004_log_jam[j]] != -1) {
                func_8001ACDC_main(D_800EC598_minigame[i]->model[D_8010E004_log_jam[j]]);
                D_800EC598_minigame[i]->model[D_8010E004_log_jam[j]] = -1;
            }
        }
    }
}

/* The player without the hook (role 0): take a log from the chute and pass it to the partner. */
void func_80107080_log_jam(omObjData* obj, LjTeam* team) {
    f32 mtx[4][4];
    Vec scale = D_8010E1F0_log_jam;
    Vec pos;
    LjPlayer* pl;
    HmfModel* hmf;
    LjPlayer* partner;
    f32 t;
    s32 sym;

    t = 0.0f;
    pl = func_8010C588_log_jam(obj);
    hmf = &HmfModelData[obj->model[0]];
    partner = team->unk0C;
    if (pl->unk1E != 0) {
        func_80108840_log_jam(obj, team);
    }
    if (func_800E6E8C_minigame() == 3 && pl->unk08 < 13) {
        pl->unk08 = 13;
        pl->unk0C = 0;
    }
    if (*(s32*)&pl->unk08 != 0x10000 && pl->unk08 < 13) {
        obj->rot.y = func_8010C2DC_log_jam(D_8010DF20_log_jam[pl->unk00], obj->rot.y, 10.0f);
    }
    switch (pl->unk08) {
    case 0:
        if (pl->unk0C >= 3.0f && func_800E6E8C_minigame() == 2) {
            func_8010C5DC_log_jam(obj, 7, 5);
            func_8004AC98_main(0x38A, pl->unk18);
            pl->unk08 = 1;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 1:
        if (pl->unk0A == 0) {
            t = pl->unk0C / 14.0f;
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > 1.0f) {
                t = 1.0f;
            }
            obj->rot.y = func_8010C4B4_log_jam(D_8010DF20_log_jam[pl->unk00], 0.0f, t);
            if (hmf->unk04 == 0xFF && hmf->unk40 >= 14.0f && hmf->unk02 == obj->motion[7]) {
                pl->unk24 = (u8)(rand8() % 3);
                func_8001C258_main(obj->model[3 + pl->unk24], 4, 0);
                pl->unk0A++;
                pl->unk0C = 0;
            }
        } else if (hmf->unk04 == 0xFF && hmf->unk40 >= 29.0f && hmf->unk02 == obj->motion[7]) {
            pl->unk08 = 2;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 2:
        if ((D_800D5558_main[pl->unk1A] & 0xE000) && team->unk16 == -1 && partner->unk22 == -1 &&
            (u16)(partner->unk08 - 6) < 2) {
            switch (D_800D5558_main[pl->unk1A]) {
            case 0x8000:
                sym = 0;
                break;
            case 0x4000:
                sym = 1;
                break;
            case 0x2000:
                sym = 2;
                break;
            default:
                sym = 3;
                break;
            }
            if (sym == pl->unk24) {
                func_8010C5DC_log_jam(obj, 8, 5);
                pl->unk08 = 3;
            } else {
                func_8010C714_log_jam(obj, 8, 0);
                hmf->unk40 = 0.0f;
                hmf->unk44 = 0.0f;
                omVibrate(pl->unk18, 2, 3, 10);
                pl->unk08 = 4;
            }
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 4:
        if (pl->unk0A == 0) {
            if ((hmf->unk40 += 2.0f) >= 10.0f) {
                pos.x = obj->trans.x;
                pos.y = obj->trans.y + D_8010E010_log_jam[pl->unk1C];
                pos.z = obj->trans.z;
                func_8010AE58_log_jam(&pos, NULL, NULL, 1.0f, NULL);
                pl->unk0A++;
            }
        } else if (!(pl->unk0A & 1)) {
            if ((hmf->unk40 += 2.0f) >= 6.0f) {
                pl->unk0A++;
            }
        } else if ((hmf->unk40 -= 2.0f) <= 0.0f) {
            if (pl->unk0A == 1 || pl->unk0A == 5 || pl->unk0A == 9) {
                pos.x = obj->trans.x;
                pos.y = obj->trans.y + D_8010E010_log_jam[pl->unk1C];
                pos.z = obj->trans.z;
                func_8010AE58_log_jam(&pos, NULL, NULL, 1.0f, NULL);
            }
            pl->unk0A++;
        }
        if (pl->unk0A >= 9) {
            func_8010C7D0_log_jam(obj);
            hmf->unk40 = 0.0f;
            pl->unk08 = 2;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 3:
        if (pl->unk0A == 0) {
            if (hmf->unk04 == 0xFF && hmf->unk02 == obj->motion[8]) {
                t = hmf->unk40 / 20.0f;
            }
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > 1.0f) {
                t = 1.0f;
            }
            obj->trans.x = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].x, D_8010DEC0_log_jam[pl->unk00].x);
            obj->trans.z = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].z, D_8010DEC0_log_jam[pl->unk00].z);
            if (hmf->unk04 == 0xFF && hmf->unk40 >= 19.0f && hmf->unk02 == obj->motion[8]) {
                func_8001C258_main(obj->model[3 + pl->unk24], 4, 4);
                pl->unk22 = func_80109044_log_jam(pl->unk24, 0);
                func_80109140_log_jam(pl->unk22, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y,
                                      D_8010DF30_log_jam[team->unk10].z);
                func_80109190_log_jam(pl->unk22, 0.0f, 0.0f, 0.0f);
                team->unk16 = pl->unk22;
                team->unk18 = pl->unk24;
                team->unk1A = 0;
                pl->unk22 = pl->unk24 = -1;
                omVibrate(pl->unk18, 10, 0, 10);
                pl->unk0A++;
                pl->unk0C = 0;
            }
        } else {
            if (hmf->unk04 == 0xFF && hmf->unk02 == obj->motion[8]) {
                t = (hmf->unk40 - 19.0f) / 20.0f;
            }
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > 1.0f) {
                t = 1.0f;
            }
            obj->trans.x = func_8010C49C_log_jam(t, D_8010DEC0_log_jam[pl->unk00].x, D_8010DE90_log_jam[pl->unk00].x);
            obj->trans.z = func_8010C49C_log_jam(t, D_8010DEC0_log_jam[pl->unk00].z, D_8010DE90_log_jam[pl->unk00].z);
            if (hmf->unk04 == 0xFF && hmf->unk40 >= 39.0f && hmf->unk02 == obj->motion[8]) {
                func_8010C5DC_log_jam(obj, 0, 5);
                pl->unk08 = 0;
                pl->unk0A = 0;
                pl->unk0C = 0;
            }
        }
        break;
    case 13:
        if (pl->unk24 != -1) {
            func_8001C258_main(obj->model[3 + pl->unk24], 4, 4);
            func_8010CAC0_log_jam(obj, D_8010E218_log_jam, mtx);
            func_8010A9D4_log_jam((Vec*)mtx[3], NULL, &scale, 1.0f, &D_8010DF4C_log_jam);
            pl->unk22 = pl->unk24 = -1;
        }
        func_8010C5DC_log_jam(obj, 0, 5);
        pl->unk08 = 14;
        /* fallthrough */
    case 14:
        obj->rot.y = func_8010C2DC_log_jam(0.0f, obj->rot.y, 10.0f);
        obj->trans.x = func_8010C514_log_jam(D_8010DE90_log_jam[pl->unk00].x, obj->trans.x, 10.0f);
        obj->trans.z = func_8010C514_log_jam(D_8010DE90_log_jam[pl->unk00].z, obj->trans.z, 10.0f);
        if (func_800E6E8C_minigame() == 4) {
            func_8010C5DC_log_jam(obj, 1, 5);
            pl->unk10 = 32.0f;
            pl->unk0E = func_80108D1C_log_jam(32.0f, 1.6333001f);
            pl->unk08 = 15;
            pl->unk0C = 0;
        }
        break;
    case 15:
        t = (f32)pl->unk0C / pl->unk0E;
        if (t > 1.0f) {
            t = 1.0f;
        } else if (t < 0.0f) {
            t = 0.0f;
        }
        if (pl->unk0C == 6) {
            func_8010C5DC_log_jam(obj, 2, 6);
        } else if (pl->unk0C == pl->unk0E - 10) {
            func_8010C5DC_log_jam(obj, 1, 7);
        }
        obj->trans.x = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].x, D_8010DEF0_log_jam[pl->unk00].x);
        obj->trans.z = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].z, D_8010DEF0_log_jam[pl->unk00].z);
        obj->trans.y += pl->unk10;
        pl->unk10 -= 1.6333001f;
        if (obj->trans.y <= 0.0f) {
            func_8010C5DC_log_jam(obj, 0, 5);
            obj->trans.y = 0.0f;
            pl->unk08 = 16;
            pl->unk0C = 0;
        }
        break;
    case 16:
        pl->unk08 = 17;
        pl->unk0C = 0;
        break;
    case 17:
        if (pl->unk06 != -1) {
            switch (pl->unk06) {
            case 0:
                func_8010C5DC_log_jam(obj, 9, 5);
                func_80017790_main(obj->model[0], 2, pl->unk1C, D_8010DF50_log_jam[pl->unk1C]);
                func_80045F1C_main(pl->unk14, -1, pl->unk18);
                break;
            case 1:
                func_8010C5DC_log_jam(obj, 10, 5);
                func_80017790_main(obj->model[0], 2, pl->unk1C, D_8010DF70_log_jam[pl->unk1C]);
                break;
            }
            pl->unk06 = -1;
        }
        break;
    }
}

/* The hook player (role 1): hook the log the partner passes, split it, throw the hook at the end. */
void func_80107C84_log_jam(omObjData* obj, LjTeam* team) {
    f32 mtx[4][4];
    Vec scale = D_8010E1F0_log_jam;
    LjPlayer* pl;
    HmfModel* hmf;
    LjPlayer* partner;
    f32 t;
    f32 frame;
    s32 target;

    pl = func_8010C588_log_jam(obj);
    hmf = &HmfModelData[obj->model[0]];
    partner = team->unk08;
    if (pl->unk1E != 0) {
        func_80108A80_log_jam(obj, team);
    }
    if (func_800E6E8C_minigame() == 3 && pl->unk08 < 13) {
        pl->unk08 = 13;
        pl->unk0C = 0;
    }
    switch (pl->unk08) {
    case 5:
        if (func_800E6E8C_minigame() == 2) {
            func_8010C5DC_log_jam(obj, 3, 7);
            pl->unk08 = 6;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 6:
        if (hmf->unk04 == 0xFF && hmf->unk40 >= 19.0f && hmf->unk02 == obj->motion[3]) {
            pl->unk08 = 7;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 7:
        if ((D_800D5558_main[pl->unk1A] & 0xE000) && *(s32*)&partner->unk08 != 0x30000) {
            if (D_800D5558_main[pl->unk1A] == 0x8000) {
                pl->unk26 = 0;
            } else if (D_800D5558_main[pl->unk1A] == 0x4000) {
                pl->unk26 = 1;
            } else if (D_800D5558_main[pl->unk1A] == 0x2000) {
                pl->unk26 = 2;
            } else {
                pl->unk26 = 3;
            }
            if (pl->unk22 == 32) {
                target = pl->unk24;
            } else {
                target = team->unk18;
            }
            func_8004AC98_main(0x38D, pl->unk18);
            if (target == -1 || target == pl->unk26) {
                func_8010C5DC_log_jam(obj, 4, 2);
                pl->unk08 = 8;
            } else {
                func_8010C5DC_log_jam(obj, 5, 2);
                pl->unk08 = 9;
            }
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 8:
        if (pl->unk22 == 32) {
            target = pl->unk24;
        } else {
            target = team->unk18;
        }
        frame = 9.0f;
        if (hmf->unk04 == 0xFF && hmf->unk40 >= frame && hmf->unk02 == obj->motion[4]) {
            if (target == -1) {
                func_8004AC98_main(0x38C, pl->unk18);
                pl->unk08 = 12;
                pl->unk0A = 0;
                pl->unk0C = 0;
                func_8010C5DC_log_jam(obj, 6, 5);
                func_800E4C88_minigame(obj, 6, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y,
                                       D_8010DF30_log_jam[team->unk10].z, 0.0f, 0.0f);
            } else {
                func_8004AC98_main(0x38B, pl->unk18);
                omVibrate(pl->unk18, 10, 0, 10);
                pl->unk08 = 10;
                pl->unk0A = 0;
                pl->unk0C = 0;
                if (team->unk16 != -1) {
                    pl->unk22 = team->unk16;
                    team->unk16 = team->unk18 = -1;
                    team->unk1A = 0;
                } else {
                    func_8001C258_main(obj->model[3 + pl->unk24], 4, 4);
                    pl->unk24 = pl->unk22 = -1;
                    pl->unk22 = func_80109044_log_jam(target, 0);
                    func_80109140_log_jam(pl->unk22, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y,
                                          D_8010DF30_log_jam[team->unk10].z);
                    func_80109190_log_jam(pl->unk22, 0.0f, 0.0f, 0.0f);
                }
                if (pl->unk22 != -1) {
                    func_80109350_log_jam(pl->unk22);
                    pl->unk22 = pl->unk24 = -1;
                }
                if (func_800E6E8C_minigame() == 2) {
                    team->unk12++;
                }
            }
        }
        break;
    case 9:
        if (hmf->unk04 == 0xFF && hmf->unk40 >= 8.0f && hmf->unk02 == obj->motion[5]) {
            func_8004AC98_main(0x38C, pl->unk18);
            pl->unk08 = 11;
            pl->unk0A = 0;
            pl->unk0C = 0;
            if (team->unk16 != -1) {
                pl->unk22 = 32;
                pl->unk24 = team->unk18;
                func_8001C258_main(obj->model[3 + pl->unk24], 4, 0);
                func_8010925C_log_jam(team->unk16);
                team->unk16 = team->unk18 = -1;
                team->unk1A = 0;
                func_800E4C88_minigame(obj, 6, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y + 50.0,
                                       D_8010DF30_log_jam[team->unk10].z, 0.0f, 0.0f);
            } else {
                func_800E4C88_minigame(obj, 6, D_8010DF30_log_jam[team->unk10].x, D_8010DF30_log_jam[team->unk10].y,
                                       D_8010DF30_log_jam[team->unk10].z, 0.0f, 0.0f);
            }
            omVibrate(pl->unk18, 2, 2, 20);
            func_8010C7D0_log_jam(obj);
        }
        break;
    case 10:
        if (pl->unk0C >= 9.0f) {
            pl->unk08 = 5;
            pl->unk0A = 0;
            pl->unk0C = 0;
            func_8010C5DC_log_jam(obj, 3, 5);
        }
        break;
    case 11:
        if (pl->unk0C >= 15.0f) {
            pl->unk08 = 6;
            pl->unk0A = 0;
            pl->unk0C = 0;
            func_8010C6A4_log_jam(obj, 3, 12);
        }
        break;
    case 12:
        if (pl->unk0C >= 90.0f) {
            func_8010C5DC_log_jam(obj, 3, 7);
            pl->unk08 = 5;
            pl->unk0A = 0;
            pl->unk0C = 0;
        }
        break;
    case 13:
        func_8010CAC0_log_jam(obj, D_8010E218_log_jam, mtx);
        team->unk1C = obj->model[2];
        if (team->unk1C != -1) {
            func_8008A070_main((f32(*)[4])HmfModelData[team->unk1C].mtx);
            func_80017C10_main((Mtx*)HmfModelData[team->unk1C].mtx, 0.0f, -50.0f, 0.0f);
            func_8001C258_main(team->unk1C, 0x4000, 0);
            team->unk20 = 0;
            team->unk24.x = mtx[3][0];
            team->unk24.z = mtx[3][2];
            team->unk24.y = mtx[3][1] + 50.0;
            team->unk3C = 30.000001907348633f;
            team->unk40 = (u8)(rand8() % 10) + 40;
            team->unk44 = 3 - (u8)(rand8() % 6);
        }
        if (pl->unk24 != -1) {
            func_8001C258_main(obj->model[3 + pl->unk24], 4, 4);
            func_8010A9D4_log_jam((Vec*)mtx[3], NULL, &scale, 1.0f, &D_8010DF4C_log_jam);
            pl->unk22 = pl->unk24 = -1;
        }
        func_8010C5DC_log_jam(obj, 0, 5);
        pl->unk08 = 14;
        /* fallthrough */
    case 14:
        obj->rot.y = func_8010C2DC_log_jam(0.0f, obj->rot.y, 10.0f);
        obj->trans.x = func_8010C514_log_jam(D_8010DE90_log_jam[pl->unk00].x, obj->trans.x, 10.0f);
        obj->trans.z = func_8010C514_log_jam(D_8010DE90_log_jam[pl->unk00].z, obj->trans.z, 10.0f);
        if (func_800E6E8C_minigame() == 4) {
            func_8010C5DC_log_jam(obj, 1, 5);
            pl->unk10 = 25.0f;
            pl->unk0E = func_80108D1C_log_jam(25.0f, 1.6333001f);
            pl->unk08 = 15;
            pl->unk0C = 0;
        }
        break;
    case 15:
        t = (f32)pl->unk0C / pl->unk0E;
        if (t > 1.0f) {
            t = 1.0f;
        } else if (t < 0.0f) {
            t = 0.0f;
        }
        if (pl->unk0C == 6) {
            func_8010C5DC_log_jam(obj, 2, 6);
        } else if (pl->unk0C == pl->unk0E - 6) {
            func_8010C5DC_log_jam(obj, 1, 6);
        }
        obj->trans.x = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].x, D_8010DEF0_log_jam[pl->unk00].x);
        obj->trans.z = func_8010C49C_log_jam(t, D_8010DE90_log_jam[pl->unk00].z, D_8010DEF0_log_jam[pl->unk00].z);
        obj->trans.y += pl->unk10;
        pl->unk10 -= 1.6333001f;
        if (obj->trans.y <= 0.0f) {
            func_8010C5DC_log_jam(obj, 0, 5);
            obj->trans.y = 0.0f;
            pl->unk08 = 16;
            pl->unk0C = 0;
        }
        break;
    case 16:
        pl->unk08 = 17;
        pl->unk0C = 0;
        break;
    case 17:
        if (pl->unk06 != -1) {
            switch (pl->unk06) {
            case 0:
                func_8010C5DC_log_jam(obj, 9, 5);
                func_80017790_main(obj->model[0], 2, pl->unk1C, D_8010DF50_log_jam[pl->unk1C]);
                func_80045F1C_main(pl->unk14, -1, pl->unk18);
                break;
            case 1:
                func_8010C5DC_log_jam(obj, 10, 5);
                func_80017790_main(obj->model[0], 2, pl->unk1C, D_8010DF70_log_jam[pl->unk1C]);
                break;
            }
            pl->unk06 = -1;
        }
        break;
    }
}

/* CPU input of the hook player (role 1). */
void func_80108840_log_jam(omObjData* obj, LjTeam* team) {
    LjPlayer* pl = func_8010C588_log_jam(obj);
    LjPlayer* partner = team->unk0C;

    D_800D5558_main[pl->unk1A] = 0;
    switch (pl->unk08) {
    case 1:
    case 3:
    case 4:
        pl->unk2C = 0;
        break;
    case 2:
        if (pl->unk2C != 0) {
            D_800D5558_main[pl->unk1A] |= pl->unk2C;
        } else if (pl->unk28 > pl->unk2A) {
            if ((u8)(rand8() % 100) < pl->unk20 * 13 + 50 || pl->unk2E >= pl->unk30 || partner->unk1E == 0) {
                switch (pl->unk24) {
                case 0:
                    pl->unk2C |= 0x8000;
                    break;
                case 1:
                    pl->unk2C |= 0x4000;
                    break;
                default:
                    pl->unk2C |= 0x2000;
                    break;
                }
                pl->unk2E = 0;
            } else {
                switch (pl->unk24) {
                case 0:
                    pl->unk2C |= 0x2000;
                    break;
                case 1:
                    pl->unk2C |= 0x8000;
                    break;
                default:
                    pl->unk2C |= 0x4000;
                    break;
                }
                pl->unk2E++;
            }
            pl->unk28 = 0;
            pl->unk2A = (u8)(rand8() % 3) + (6 - pl->unk20 * 2) * 2;
        }
        break;
    }
    pl->unk28++;
}

/* CPU input of the other player (role 0). */
void func_80108A80_log_jam(omObjData* obj, LjTeam* team) {
    LjPlayer* pl = func_8010C588_log_jam(obj);
    LjPlayer* partner = team->unk08;
    s16 target;

    D_800D5558_main[pl->unk1A] = 0;
    if (team->unk16 != -1) {
        target = team->unk18;
    } else {
        target = pl->unk24;
    }
    switch (pl->unk08) {
    case 7:
        if (pl->unk2C & 0xE000) {
            D_800D5558_main[pl->unk1A] |= pl->unk2C;
        } else if (pl->unk28 > pl->unk2A && target != -1) {
            if ((u8)(rand8() % 100) < pl->unk20 * 13 + 50 || pl->unk2E >= pl->unk30 || partner->unk1E == 0) {
                switch (target) {
                case 0:
                    pl->unk2C |= 0x8000;
                    break;
                case 1:
                    pl->unk2C |= 0x4000;
                    break;
                default:
                    pl->unk2C |= 0x2000;
                    break;
                }
                pl->unk2E = 0;
            } else {
                switch (target) {
                case 0:
                    pl->unk2C |= 0x2000;
                    break;
                case 1:
                    pl->unk2C |= 0x8000;
                    break;
                default:
                    pl->unk2C |= 0x4000;
                    break;
                }
                pl->unk2E++;
            }
            pl->unk28 = 0;
            pl->unk2A = (u8)(rand8() % 10) + 16 - pl->unk20 * 2;
        }
        break;
    case 8:
    case 9:
        pl->unk2C = 0;
        break;
    }
    pl->unk28++;
}

/* 1 when all four players are in this state. */
s16 func_80108CE0_log_jam(s16 state) {
    LjPlayer* pl;
    s32 i;

    for (i = 0, pl = D_8010E5B8_log_jam; i < 4; i++, pl++) {
        if (pl->unk08 != state) {
            return 0;
        }
    }
    return 1;
}

/* Frames a throw at speed v under gravity g stays above its start height. */
s16 func_80108D1C_log_jam(f32 v, f32 g) {
    f32 y = 0.0f;
    s16 n = 0;

    do {
        y += v;
        v -= g;
        n++;
    } while (y > 0.0f);
    return n;
}

void func_80108D50_log_jam(void) {
    LjLog* log;
    s32 i;

    log = D_8010E5C4_log_jam = HuMemAllocTag(sizeof(LjLog) * 32, 31000);
    for (i = 0; i < 32; i++, log++) {
        log->unk00 = i;
        log->unk02[0] = -1;
        log->unk02[1] = -1;
        log->unk02[2] = -1;
        log->unk08 = 0;
        log->unk0A = 0;
        log->unk0C = 0;
        log->unk0E = 0;
        log->unk10.x = log->unk10.y = log->unk10.z = 0.0f;
        log->unk1C.x = log->unk1C.y = log->unk1C.z = 0.0f;
        log->unk28.x = log->unk28.y = log->unk28.z = 0.0f;
        memset(&log->unk34, 0, 0x20);
        memset(&log->unk54, 0, 0x20);
        log->unk74 = NULL;
    }
    D_8010E5C0_log_jam = omAddObj(0x18, 0, 0, -1, func_80108E54_log_jam);
    omSetStatBit(D_8010E5C0_log_jam, 0xA0);
}

void func_80108E54_log_jam(omObjData* obj) {
    LjLog* log;
    s32 i;
    s32 j;

    for (i = 0, log = D_8010E5C4_log_jam; i < 32; i++, log++) {
        if (log->unk08 == 0) {
            continue;
        }
        switch (log->unk0C) {
        case 0:
            break;
        case 1:
            if ((log->unk0E & 1) || func_80049F98_main() + D_800D6A90_main != 0) {
                for (j = 0; j < 3; j++) {
                    if (log->unk02[j] != -1) {
                        func_8001C258_main(log->unk02[j], 4, 0);
                    }
                }
            } else {
                for (j = 0; j < 3; j++) {
                    if (log->unk02[j] != -1) {
                        func_8001C258_main(log->unk02[j], 4, 4);
                    }
                }
            }
            if (log->unk0E >= 30.0f) {
                log->unk0E = 0;
                log->unk0C++;
            }
            break;
        default:
            func_8010925C_log_jam(log->unk00);
            continue;
        }
        if (log->unk74 != NULL && func_80049F98_main() + D_800D6A90_main == 0) {
            log->unk74(log);
        }
        if (log->unk08 == 0) {
            continue;
        }
        if (log->unk02[0] != -1) {
            Hu3DModelPosSet(log->unk02[0], log->unk10.x, log->unk10.y, log->unk10.z);
            Hu3DModelRotSet(log->unk02[0], log->unk1C.x, log->unk1C.y, log->unk1C.z);
        }
        if (func_80049F98_main() + D_800D6A90_main == 0) {
            log->unk0E++;
        }
    }
}

/* Spawn a log of a kind; returns its index or -1. */
s16 func_80109044_log_jam(s16 kind, s16 part) {
    LjLog* log;
    s32 i;

    if (D_8010E5C4_log_jam == NULL) {
        return -1;
    }
    for (i = 0, log = D_8010E5C4_log_jam; i < 32; i++, log++) {
        if (log->unk08 == 0) {
            log->unk02[0] = func_80109A7C_log_jam(kind, part);
            if (log->unk02[0] != -1) {
                func_8001C258_main(log->unk02[0], 4, 0);
            }
            log->unk08 = 1;
            log->unk0A = kind;
            log->unk0C = 0;
            log->unk0E = 0;
            return i;
        }
    }
    return -1;
}

#ifdef NON_MATCHING
/* Differs: retail adds offset + base, this adds base + offset (operand order only). */
LjLog* func_8010910C_log_jam(s16 idx) {
    LjLog* logs = D_8010E5C4_log_jam;

    if (logs != NULL) {
        return &logs[idx];
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010910C_log_jam);
#endif

void func_80109140_log_jam(s16 idx, f32 x, f32 y, f32 z) {
    LjLog* log;

    if (D_8010E5C4_log_jam != NULL) {
        log = &D_8010E5C4_log_jam[idx];
        if (log->unk08 != 0) {
            log->unk10.x = x;
            log->unk10.y = y;
            log->unk10.z = z;
        }
    }
}

void func_80109190_log_jam(s16 idx, f32 x, f32 y, f32 z) {
    LjLog* log;

    if (D_8010E5C4_log_jam != NULL) {
        log = &D_8010E5C4_log_jam[idx];
        if (log->unk08 != 0) {
            log->unk1C.x = x;
            log->unk1C.y = y;
            log->unk1C.z = x; /* retail: z is ignored */
        }
    }
}

void func_801091DC_log_jam(void) {
    s32 i;
    LjLog* log;

    if (D_8010E5C4_log_jam != NULL) {
        for (i = 0, log = D_8010E5C4_log_jam; i < 32; i++, log++) {
            if (log->unk08 != 0) {
                func_8010925C_log_jam(i);
            }
        }
        HuMemFree(D_8010E5C4_log_jam);
        D_8010E5C4_log_jam = NULL;
        D_8010E5C0_log_jam->func = NULL;
    }
}

void func_8010925C_log_jam(s16 idx) {
    LjLog* log;
    s32 i;

    if (D_8010E5C4_log_jam != NULL) {
        log = &D_8010E5C4_log_jam[idx];
        if (log->unk08 != 0) {
            for (i = 0; i < 3; i++) {
                if (log->unk02[i] != -1) {
                    func_8001ACDC_main(log->unk02[i]);
                    log->unk02[i] = -1;
                }
            }
            log->unk08 = 0;
            log->unk0E = 0;
            log->unk0C = 0;
            log->unk0A = 0;
            log->unk10.x = log->unk10.y = log->unk10.z = 0.0f;
            log->unk1C.x = log->unk1C.y = log->unk1C.z = 0.0f;
            log->unk28.x = log->unk28.y = log->unk28.z = 0.0f;
            memset(&log->unk34, 0, 0x20);
            memset(&log->unk54, 0, 0x20);
            log->unk74 = NULL;
        }
    }
}

const Vec D_8010E2C0_log_jam = { 0.0f, 0.0f, 0.0f };
const Vec D_8010E2CC_log_jam = { 0.5f, 0.5f, 0.5f }; /* split effect scale */

#ifdef NON_MATCHING
/* Differs: register allocation of the log pointer and one delay slot. */
/* Split a log in two halves that fly apart. */
void func_80109350_log_jam(s16 idx) {
    Vec pos = D_8010E2C0_log_jam;
    Vec scale = D_8010E2CC_log_jam;
    LjLog* log;
    LjLog* half;
    f32 x;
    f32 y;
    f32 z;
    s32 kind;
    s16 n;
    s32 i;

    if (D_8010E5C4_log_jam == NULL) {
        return;
    }
    log = &D_8010E5C4_log_jam[idx];
    if (log->unk08 == 0) {
        return;
    }
    kind = log->unk0A;
    x = log->unk10.x;
    y = log->unk10.y;
    z = log->unk10.z;
    pos.x = x;
    pos.y = log->unk10.y;
    pos.z = log->unk10.z;
    func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, &D_8010DF48_log_jam);
    func_8010925C_log_jam(idx);
    for (i = 0; i < 2; i++) {
        n = func_80109044_log_jam(kind, i + 1);
        if (n != -1) {
            half = &D_8010E5C4_log_jam[n];
            half->unk10.x = x;
            half->unk10.y = y;
            half->unk10.z = z;
            half->unk34 = i;
            half->unk52 = 0;
            half->unk74 = func_801094E4_log_jam;
            half->unk74(half);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109350_log_jam);
#endif

#define LJ_RANDF() ((f32)(u8)(rand8() % 100) * 0.01)

/* Motion of a split half: fly out, land, then wobble to rest. */
void func_801094E4_log_jam(LjLog* log) {
    Vec pos = D_8010E2C0_log_jam;
    Vec scale = D_8010E2CC_log_jam;
    f32 f;

    switch (log->unk52) {
    case 0:
        if (log->unk34 == 0) {
            log->unk28.x = (LJ_RANDF() * 0.02 + 0.03f) * 100.0;
            log->unk54 = -(LJ_RANDF() * 0.75 + 4.0);
            log->unk68 = -90.0f;
        } else {
            log->unk28.x = -((LJ_RANDF() * 0.02 + 0.03f) * 100.0);
            log->unk54 = LJ_RANDF() * 0.75 + 4.0;
            log->unk68 = 90.0f;
        }
        log->unk28.y = LJ_RANDF() * 2.0 + 10.999999940395355;
        log->unk28.z = LJ_RANDF() * 1.2500000186264515 + 0.6250000093132257;
        log->unk52++;
        break;
    case 1:
        log->unk1C.z += log->unk54;
        log->unk28.y -= 1.6333001f;
        if (log->unk10.y <= 0.0f) {
            log->unk10.y = 0.0f;
            log->unk28.x = log->unk28.y = log->unk28.z = 0.0f;
            log->unk58 = 20.0f;
            log->unk5C = 1.0f;
            log->unk60 = 0.0f;
            log->unk64 = 55.0f;
            log->unk52++;
            pos.x = log->unk10.x;
            pos.y = log->unk10.y;
            pos.z = log->unk10.z;
            func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, &D_8010DF48_log_jam);
        }
        break;
    case 2:
        log->unk60 += log->unk64;
        if (log->unk60 >= 360.0f) {
            log->unk60 -= 360.0f;
        }
        f = log->unk58 - log->unk5C;
        if (f > 0.0f) {
            log->unk58 = f;
        } else {
            log->unk58 = 0.0f;
        }
        log->unk1C.z = sindf(log->unk60) * log->unk58 + log->unk68;
        if (log->unk0C == 0) {
            log->unk0C = 1;
        }
        break;
    }
    log->unk10.x += log->unk28.x;
    log->unk10.y += log->unk28.y;
    log->unk10.z += log->unk28.z;
}

void func_80109A00_log_jam(void) {
    s32 i;

    D_8010E5C8_log_jam = HuMemAllocTag(9 * sizeof(s16), 31000);
    for (i = 0; i < 9; i++) {
        D_8010E5C8_log_jam[i] = func_8000B108_main(D_8010E030_log_jam[i], 0xBD);
    }
}

s16 func_80109A7C_log_jam(s16 kind, s16 part) {
    s16* mdl = D_8010E5C8_log_jam;

    return (mdl != NULL) ? Hu3DModelLink(mdl[kind * 3 + part]) : -1;
}

void func_80109AD8_log_jam(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        func_8001ACDC_main(D_8010E5C8_log_jam[i]);
    }
    HuMemFree(D_8010E5C8_log_jam);
    D_8010E5C8_log_jam = NULL;
}

void func_80109B34_log_jam(void) {
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 0x10, 0, -1, func_80109B8C_log_jam);
}

/* Stage setup: log chutes, the background, the score sprites and the clouds. */
void func_80109B8C_log_jam(omObjData* obj) {
    LjCloud* cloud;
    s16 mdl;
    s16 grp;
    s16 i;
    s16 j;

    obj->model[1] = mdl = func_8000B108_main(0x340001, 0xA9);
    Hu3DModelPosSet(mdl, -100.0f, 0.0f, 115.0f);
    obj->model[2] = mdl = Hu3DModelLink(mdl);
    Hu3DModelPosSet(mdl, 100.0f, 0.0f, 115.0f);
    obj->model[3] = mdl = func_8000B108_main(0x340002, 0x89);
    Hu3DModelPosSet(mdl, -230.0f, 0.0f, 195.0f);
    obj->model[4] = mdl = Hu3DModelLink(mdl);
    Hu3DModelPosSet(mdl, 230.0f, 0.0f, 195.0f);
    D_8010E5CC_log_jam[0] = func_8010A300_log_jam(0x34000C);
    grp = HuSprGrpCreate(3, 0);
    func_80055024_main(grp, 0, D_8010E5CC_log_jam[0], 0);
    func_80054904_main(grp, 0, 160, 120);
    func_800550F4_main(grp, 0, 0);
    func_80054FF8_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x4000580C);
    HuSprPriSet(grp, 0, 0xFF00);
    D_8010E5CC_log_jam[4] = func_8010A300_log_jam(0x340010);
    func_80055024_main(grp, 1, D_8010E5CC_log_jam[4], 0);
    func_80054904_main(grp, 1, 0, 40);
    func_800550F4_main(grp, 1, 0);
    func_80054FF8_main(grp, 1, 0);
    HuSprAttrSet(grp, 1, 0x4000580C);
    HuSprPriSet(grp, 1, 0xFF01);
    func_80055458_main(grp, 1, 200);
    D_8010E5CC_log_jam[1] = func_8010A300_log_jam(0x34000D);
    func_80055024_main(grp, 2, D_8010E5CC_log_jam[1], 0);
    func_80054904_main(grp, 2, 0, 0);
    func_800550F4_main(grp, 2, 0);
    func_80054FF8_main(grp, 2, 0);
    HuSprAttrSet(grp, 2, 0x403C);
    HuSprPriSet(grp, 2, 0xFFFF);
    D_8010E5CC_log_jam[2] = func_8010A300_log_jam(0x34000E);
    D_8010E5CC_log_jam[5] = func_8010A300_log_jam(0x340011);
    cloud = D_8010E5D4_log_jam = HuMemAllocTag(sizeof(LjCloud) * 5, 31000);
    for (i = 0; i < 5; i++, cloud++) {
        cloud->id = i;
        cloud->grp = HuSprGrpCreate(2, 0);
        cloud->angle = rand8() % 360;
        cloud->scale = D_8010E07C_log_jam[i];
        cloud->x = D_8010E054_log_jam[i].x;
        cloud->y = D_8010E054_log_jam[i].y;
        cloud->sx = cloud->sy = 1.0f;
        cloud->speed = -0.5f;
        cloud->unk20 = 0;
        for (j = 0; j < 2; j++) {
            if (j == 0) {
                func_80055024_main(cloud->grp, 0, D_8010E5CC_log_jam[2], 0);
            } else {
                func_80055024_main(cloud->grp, j, D_8010E5CC_log_jam[5], 0);
                func_80055458_main(cloud->grp, j, 190);
            }
            func_800550F4_main(cloud->grp, j, 0);
            func_80054FF8_main(cloud->grp, j, 0);
            HuSprAttrSet(cloud->grp, j, 0x2000583C);
            func_80054904_main(cloud->grp, j, cloud->x, cloud->y);
            HuSprScaleSet(cloud->grp, j, cloud->sx, cloud->sy);
            HuSprPriSet(cloud->grp, j, j + i * 2 - 0xF1);
        }
    }
    obj->func = func_8010A0B0_log_jam;
}

void func_8010A0B0_log_jam(omObjData *obj) {
    LjCloud *cloud;
    HuSprite *spr;
    f32 wave;
    s16 i;

    for (i = 0, cloud = D_8010E5D4_log_jam; i < 5; i++, cloud++) {
        wave = sindf(cloud->angle);
        cloud->x += cloud->speed * ((f32)(u8)(rand8() % 100) * 0.01 * 0.4f + 0.6f);
        cloud->sx = cloud->scale + 0.075f + wave * 0.075f;
        cloud->sy = cloud->scale + 0.075f - wave * 0.075f;
        if (cloud->x <= -64.0f) {
            cloud->x += 416.0f;
        } else if (cloud->x > 384.0f) {
            cloud->x -= 320.0f;
        }
        HuSprScaleSet(cloud->grp, 0, cloud->sx, cloud->sy);
        HuSprScaleSet(cloud->grp, 1, cloud->sx, cloud->sy);
        spr = HuSprGet(cloud->grp, 0);
        spr->unk_48 = cloud->x;
        spr->unk_4C = cloud->y;
        spr = HuSprGet(cloud->grp, 1);
        spr->unk_48 = cloud->x;
        spr->unk_4C = cloud->y;
        cloud->angle += (u8)(rand8() % 7) + 2;
        if (cloud->angle >= 360) {
            cloud->angle -= 360;
        }
    }
}

u16 func_8010A300_log_jam(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}

void func_8010A344_log_jam(void) {
    LjCounter *counter;
    s32 x;
    s32 i;
    s32 j;

    D_8010E5CC_log_jam[3] = func_8010A300_log_jam(0x34000F);
    counter = D_8010E5D0_log_jam = HuMemAllocTag(sizeof(LjCounter) * 2, 0x7918);
    for (i = 0; i < 2; i++, counter++) {
        x = D_8010E090_log_jam[i];
        memset(counter, 0, sizeof(LjCounter));
        counter->id = i;
        counter->grp = HuSprGrpCreate(10, 0);
        for (j = 0; j < 10; j++) {
            func_80055024_main(counter->grp, j, D_8010E5CC_log_jam[3], 0);
            func_800550F4_main(counter->grp, j, 0);
            func_80054FF8_main(counter->grp, j, 0);
            func_80055458_main(counter->grp, j, 0x100);
            HuSprAttrSet(counter->grp, j, 0x9000);
            func_80054904_main(counter->grp, j, x, 0x1C);
            if (i == 0) {
                x += 16;
            } else {
                x -= 16;
            }
        }
    }
    omAddObj(0x1E, 0, 0, -1, func_8010A4C0_log_jam);
}

void func_8010A4C0_log_jam(omObjData *obj) {
    LjCounter *counter;
    f32 t;
    s32 fives;
    s32 count;
    s32 i;
    s32 j;

    for (i = 0, counter = D_8010E5D0_log_jam; i < 2; i++, counter++) {
        fives = (s16)(counter->value / 5);
        count = fives + (s16)(counter->value % 5);
        if (counter->shown != counter->value) {
            for (j = 0; j < 10; j++) {
                func_80055458_main(counter->grp, j, 0x100);
                HuSprScaleSet(counter->grp, j, 1.0f, 1.0f);
            }
            counter->timer = 15;
            if (count != 0) {
                counter->digit = count - 1;
            }
        }
        if (counter->timer > 0) {
            if (counter->timer == 1) {
                t = 0.0f;
            } else {
                t = counter->timer / 15.0f;
            }
            func_80055458_main(counter->grp, counter->digit, (s32)((1.0f - t) * 256.0f));
            HuSprScaleSet(counter->grp, counter->digit, t + 1.0f, t + 1.0f);
            counter->timer--;
        }
        for (j = 0; j < 10; j++) {
            if (j < fives) {
                func_80054FF8_main(counter->grp, j, 1);
            } else {
                func_80054FF8_main(counter->grp, j, 0);
            }
            if (j < count) {
                HuSprAttrReset(counter->grp, j, 0x8000);
            } else {
                HuSprAttrSet(counter->grp, j, 0x8000);
            }
        }
        counter->shown = counter->value;
    }
}

void func_8010A6FC_log_jam(s16 idx, s16 value) {
    LjCounter *counter = &D_8010E5D0_log_jam[idx];

    counter->value = value;
}

void func_8010A724_log_jam(void) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010E5CC_log_jam[6] = func_8010A300_log_jam(0xB));
    D_8010E5D8_log_jam = omAddObj(0x1E, 0, 0, -1, func_8010A880_log_jam);
    D_8010E5DC_log_jam = effect = HuMemAllocTag(sizeof(LjEffect) * 8, 0x7918);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010CB64_log_jam(spr, &D_8010DF48_log_jam);
        } else {
            effect->model = func_8010D74C_log_jam(spr, D_8010E5DC_log_jam->model, &D_8010DF48_log_jam);
        }
        effect->active = 0;
        *(u32 *)&effect->color = *(u32 *)&D_8010DF48_log_jam;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &HmfModelData[effect->model];
        model->unk40 = 0.0f;
    }
}

void func_8010A880_log_jam(omObjData *obj) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    i = 0;
    spr = func_80055194_main(D_8010E5CC_log_jam[6]);
    effect = D_8010E5DC_log_jam;
    do {
        if (effect->active != 0) {
            model = &HmfModelData[effect->model];
            if (!(model->unk18 & 4)) {
                effect->pos.x += effect->vel.x;
                effect->pos.y += effect->vel.y;
                effect->pos.z += effect->vel.z;
                model->pos.x = effect->pos.x;
                model->pos.y = effect->pos.y;
                model->pos.z = effect->pos.z;
                model->scale.x = effect->scale.x;
                model->scale.y = effect->scale.y;
                model->scale.z = effect->scale.z;
                func_8010D950_log_jam(effect->model, spr, (s32)effect->frame, &effect->color);
                effect->frame += effect->speed;
                if ((s32)effect->frame >= (s32)spr->unk10) {
                    effect->active = 0;
                    effect->frame = 0.0f;
                    model->unk18 |= 4;
                }
            }
        }
        i++;
        effect++;
    } while (i < 8);
}

s32 func_8010A9D4_log_jam(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010E5CC_log_jam[6]);
    for (i = 0, effect = D_8010E5DC_log_jam; i < 8; i++, effect++) {
        if (effect->active == 0) {
            effect->active = 1;
            model = &HmfModelData[effect->model];
            if (pos != NULL) {
                effect->pos.x = pos->x;
                effect->pos.y = pos->y;
                effect->pos.z = pos->z;
            } else {
                effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
            }
            if (vel != NULL) {
                effect->vel.x = vel->x;
                effect->vel.y = vel->y;
                effect->vel.z = vel->z;
            } else {
                effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
            }
            if (scale != NULL) {
                effect->scale.x = scale->x;
                effect->scale.y = scale->y;
                effect->scale.z = scale->z;
            } else {
                effect->scale.x = effect->scale.y = effect->scale.z = 1.0f;
            }
            effect->color = *color;
            effect->speed = speed;
            effect->frame = 0.0f;
            func_8010D950_log_jam(effect->model, spr, 0, &effect->color);
            func_8001C258_main(effect->model, 4, 0);
            model->unk40 = 0.0f;
            model->pos.x = effect->pos.x;
            model->pos.y = effect->pos.y;
            model->pos.z = effect->pos.z;
            model->scale.x = effect->scale.x;
            model->scale.y = effect->scale.y;
            model->scale.z = effect->scale.z;
            return i;
        }
    }
    return -1;
}

void func_8010ABA4_log_jam(void) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010E5CC_log_jam[7] = func_8010A300_log_jam(0x340012));
    D_8010E5E0_log_jam = omAddObj(0x1E, 0, 0, -1, func_8010AD04_log_jam);
    D_8010E5E4_log_jam = effect = HuMemAllocTag(sizeof(LjEffect) * 8, 0x7918);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010CB64_log_jam(spr, &D_8010DF48_log_jam);
        } else {
            effect->model = func_8010D74C_log_jam(spr, D_8010E5E4_log_jam->model, &D_8010DF48_log_jam);
        }
        effect->active = 0;
        *(u32 *)&effect->color = *(u32 *)&D_8010DF48_log_jam;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &HmfModelData[effect->model];
        model->unk40 = 0.0f;
    }
}

void func_8010AD04_log_jam(omObjData *obj) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    i = 0;
    spr = func_80055194_main(D_8010E5CC_log_jam[7]);
    effect = D_8010E5E4_log_jam;
    do {
        if (effect->active != 0) {
            model = &HmfModelData[effect->model];
            if (!(model->unk18 & 4)) {
                effect->pos.x += effect->vel.x;
                effect->pos.y += effect->vel.y;
                effect->pos.z += effect->vel.z;
                model->pos.x = effect->pos.x;
                model->pos.y = effect->pos.y;
                model->pos.z = effect->pos.z;
                model->scale.x = effect->scale.x;
                model->scale.y = effect->scale.y;
                model->scale.z = effect->scale.z;
                func_8010D950_log_jam(effect->model, spr, (s32)effect->frame, &effect->color);
                effect->frame += effect->speed;
                if ((s32)effect->frame >= (s32)spr->unk10) {
                    effect->active = 0;
                    effect->frame = 0.0f;
                    model->unk18 |= 4;
                }
            }
        }
        i++;
        effect++;
    } while (i < 8);
}

s32 func_8010AE58_log_jam(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color) {
    HuSprite_Unk84_Struct *spr;
    LjEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010E5CC_log_jam[7]);
    for (i = 0, effect = D_8010E5E4_log_jam; i < 8; i++, effect++) {
        if (effect->active == 0) {
            effect->active = 1;
            model = &HmfModelData[effect->model];
            if (pos != NULL) {
                effect->pos.x = pos->x;
                effect->pos.y = pos->y;
                effect->pos.z = pos->z;
            } else {
                effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
            }
            if (vel != NULL) {
                effect->vel.x = vel->x;
                effect->vel.y = vel->y;
                effect->vel.z = vel->z;
            } else {
                effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
            }
            if (scale != NULL) {
                effect->scale.x = scale->x;
                effect->scale.y = scale->y;
                effect->scale.z = scale->z;
            } else {
                effect->scale.x = effect->scale.y = effect->scale.z = 1.0f;
            }
            if (color != NULL) {
                effect->color = *color;
            } else {
                memset(&effect->color, 0xFF, 4);
            }
            effect->speed = speed;
            effect->frame = 0.0f;
            func_8010D950_log_jam(effect->model, spr, 0, &effect->color);
            func_8001C258_main(effect->model, 4, 0);
            model->unk40 = 0.0f;
            model->pos.x = effect->pos.x;
            model->pos.y = effect->pos.y;
            model->pos.z = effect->pos.z;
            model->scale.x = effect->scale.x;
            model->scale.y = effect->scale.y;
            model->scale.z = effect->scale.z;
            return i;
        }
    }
    return -1;
}

void func_8010B04C_log_jam(void) {
    HuCamera *cam;
    s32 i;

    Center.x = 0.0f;
    Center.y = 126.8f;
    Center.z = -0.8f;
    CRot.x = 350.505f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 1062.0f;
    func_8010BCA8_log_jam(0);
    func_8010BCA8_log_jam(1);
    D_8010E630_log_jam = D_8010E634_log_jam = D_8010E638_log_jam = 0;
    omAddObj(0x1F, 0, 0, -1, func_8010B86C_log_jam);
    cam = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        cam->viewports[i].vp.vscale[0] = cam->viewports[0].vp.vscale[0];
        cam->viewports[i].vp.vscale[1] = cam->viewports[0].vp.vscale[1];
        cam->viewports[i].vp.vscale[2] = cam->viewports[0].vp.vscale[2];
        cam->viewports[i].vp.vtrans[0] = cam->viewports[0].vp.vtrans[0];
        cam->viewports[i].vp.vtrans[1] = cam->viewports[0].vp.vtrans[1];
        cam->viewports[i].vp.vtrans[2] = cam->viewports[0].vp.vtrans[2];
    }
}

void func_8010B17C_log_jam(void) {
    LjCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_8010E094_log_jam) {
        case 1:
            if ((u16)D_800CDA7C_main[0] & 0x8000) {
                speed = 8.0f;
            }
            if (D_800CDA7C_main[0] & 0x4000) {
                speed = 0.5f;
            }
            if (D_800D5558_main[0] & 0x1000) {
                Center.x = 0.0f;
                Center.y = 191.2f;
                Center.z = 0.2f;
                CRot.x = -14.5f;
                CRot.y = 0.0f;
                CRot.z = 0.0f;
                CZoom = 1069.0f;
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
                c.center.x += Center.x;
                c.center.y += Center.y;
                c.center.z += Center.z;
                c.rot.x += CRot.x;
                c.rot.y += CRot.y;
                c.rot.z += CRot.z;
                c.zoom += CZoom;
                func_8010BE94_log_jam(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 104, D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
                D_8010E098_log_jam++;
            }
            if (D_800CDA7C_main[0] & 0x202) {
                D_8010E098_log_jam--;
            }
            if (D_800CDA7C_main[0] & 0x404) {
                D_8010E09C_log_jam++;
            }
            if (D_800CDA7C_main[0] & 0x808) {
                D_8010E09C_log_jam--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010E098_log_jam + 20, (u16)D_8010E09C_log_jam + 104, D_800D5218_main);
            break;
        case 3:
            D_8010E094_log_jam = 0;
            break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_8010E094_log_jam == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_8010E094_log_jam++ >= 4) {
            D_8010E094_log_jam = 0;
        }
    }
}

void func_8010B86C_log_jam(omObjData *obj) {
    f32 t;

    if (D_8010E634_log_jam <= 0) {
        func_8010C084_log_jam(0);
        D_8010E638_log_jam = 0;
        return;
    }
    if (D_8010E630_log_jam == 0) {
        Center.x = D_8010E5E8_log_jam[0].center.x;
        Center.y = D_8010E5E8_log_jam[0].center.y;
        Center.z = D_8010E5E8_log_jam[0].center.z;
        CRot.x = D_8010E5E8_log_jam[0].rot.x;
        CRot.y = D_8010E5E8_log_jam[0].rot.y;
        CRot.z = D_8010E5E8_log_jam[0].rot.z;
        CZoom = D_8010E5E8_log_jam[0].zoom;
        LJ_WRAP(CRot.x);
        LJ_WRAP(CRot.y);
        LJ_WRAP(CRot.z);
        D_8010E634_log_jam = 0;
    } else {
        t = (f32)D_8010E630_log_jam / (f32)D_8010E634_log_jam;
        Center.x = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].center.x, D_8010E5E8_log_jam[1].center.x);
        Center.y = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].center.y, D_8010E5E8_log_jam[1].center.y);
        Center.z = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].center.z, D_8010E5E8_log_jam[1].center.z);
        CRot.x = func_8010C4B4_log_jam(t, D_8010E5E8_log_jam[0].rot.x, D_8010E5E8_log_jam[1].rot.x);
        CRot.y = func_8010C4B4_log_jam(t, D_8010E5E8_log_jam[0].rot.y, D_8010E5E8_log_jam[1].rot.y);
        CRot.z = func_8010C4B4_log_jam(t, D_8010E5E8_log_jam[0].rot.z, D_8010E5E8_log_jam[1].rot.z);
        CZoom = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].zoom, D_8010E5E8_log_jam[1].zoom);
        LJ_WRAP(CRot.x);
        LJ_WRAP(CRot.y);
        LJ_WRAP(CRot.z);
        if (D_8010E630_log_jam > 0) {
            D_8010E630_log_jam--;
        } else {
            D_8010E630_log_jam++;
        }
    }
    D_8010E638_log_jam = 1;
    func_8010C084_log_jam(0);
}

void func_8010BCA8_log_jam(s32 idx) {
    LJ_WRAP(CRot.x);
    LJ_WRAP(CRot.y);
    LJ_WRAP(CRot.z);
    D_8010E5E8_log_jam[idx].center.x = Center.x;
    D_8010E5E8_log_jam[idx].center.y = Center.y;
    D_8010E5E8_log_jam[idx].center.z = Center.z;
    D_8010E5E8_log_jam[idx].rot.x = CRot.x;
    D_8010E5E8_log_jam[idx].rot.y = CRot.y;
    D_8010E5E8_log_jam[idx].rot.z = CRot.z;
    D_8010E5E8_log_jam[idx].zoom = CZoom;
    D_8010E5E8_log_jam[idx].unk1C = D_8010E5E8_log_jam[idx].unk20 = 0.0f;
}

void func_8010BE94_log_jam(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_8010E630_log_jam = frames - 1;
        D_8010E634_log_jam = frames;
        if (cx != 65535.0f) {
            D_8010E5E8_log_jam[0].center.x = cx;
        } else {
            D_8010E5E8_log_jam[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_8010E5E8_log_jam[0].center.y = cy;
        } else {
            D_8010E5E8_log_jam[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_8010E5E8_log_jam[0].center.z = cz;
        } else {
            D_8010E5E8_log_jam[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_8010E5E8_log_jam[0].rot.x = rx;
        } else {
            D_8010E5E8_log_jam[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_8010E5E8_log_jam[0].rot.y = ry;
        } else {
            D_8010E5E8_log_jam[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_8010E5E8_log_jam[0].rot.z = rz;
        } else {
            D_8010E5E8_log_jam[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_8010E5E8_log_jam[0].zoom = zoom;
        } else {
            D_8010E5E8_log_jam[0].zoom = CZoom;
        }
        func_8010BCA8_log_jam(1);
    }
}

void func_8010C084_log_jam(s32 idx) {
    HuCamera *cam = &gCameraList[idx];
    f32 rx = CRot.x;
    f32 ry = CRot.y;

    cam->pos.x = Center.x + sindf(ry) * cosdf(rx) * CZoom;
    cam->pos.y = -sindf(rx) * CZoom + Center.y;
    cam->pos.z = cosdf(ry) * cosdf(rx) * CZoom + Center.z;
    cam->at.x = Center.x;
    cam->at.y = Center.y;
    cam->at.z = Center.z;
    cam->up.x = sindf(ry) * sindf(rx);
    cam->up.y = cosdf(rx);
    cam->up.z = cosdf(ry) * sindf(rx);
}

f32 func_8010C1D8_log_jam(f32 a, f32 b) {
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

f32 func_8010C2DC_log_jam(f32 target, f32 cur, f32 step) {
    f32 d;
    f32 v;
    f64 e;

    LJ_WRAP(target);
    LJ_WRAP(cur);
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
    LJ_WRAP(v);
    return v;
}

f32 func_8010C49C_log_jam(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

f32 func_8010C4B4_log_jam(f32 t, f32 a, f32 b) {
    return func_8010C2DC_log_jam(b, a, fabsf(func_8010C1D8_log_jam(b, a) * t));
}

f32 func_8010C514_log_jam(f32 target, f32 cur, f32 step) {
    if (fabs(target - cur) < step) {
        return target;
    }
    if (target < cur) {
        step = -step;
    }
    return cur + step;
}

void func_8010C55C_log_jam(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}

void *func_8010C588_log_jam(omObjData *obj) {
    LjPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}

void func_8010C5DC_log_jam(omObjData *obj, s16 slot, s16 frames) {
    HmfModel *model = &HmfModelData[obj->model[0]];
    func_800E1BA8_minigame_UnkE8_ObjData *mtn;

    func_8001C624_main(obj->model[0], obj->motion[slot], 0, frames, 0);
    mtn = &((func_800E1BA8_minigame_ObjData *)obj->data)->unkE8[slot];
    if (mtn->unk00 & 1) {
        model->unk05 = 2;
    } else {
        model->unk05 = 0;
    }
    model->unk54 = mtn->unk02;
}

void func_8010C6A4_log_jam(omObjData *obj, s16 slot, s16 frame) {
    HmfModel *model = &HmfModelData[obj->model[0]];

    func_8010C5DC_log_jam(obj, slot, 5);
    model->unk4C = frame;
}

void func_8010C714_log_jam(omObjData *obj, s16 slot, s16 frame) {
    HmfModel *model = &HmfModelData[obj->model[0]];
    func_800E1BA8_minigame_UnkE8_ObjData *mtn;

    model->unk02 = obj->motion[slot];
    model->unk48 = model->unk40 = model->unk44 = 1.0f;
    model->unk04 = 0xFF;
    model->unk40 = frame;
    mtn = &((func_800E1BA8_minigame_ObjData *)obj->data)->unkE8[slot];
    if (mtn->unk00 & 1) {
        model->unk03 = 2;
    } else {
        model->unk03 = 0;
    }
    model->unk48 = mtn->unk02;
}

void func_8010C7D0_log_jam(omObjData *obj) {
    HmfModel *model = &HmfModelData[obj->model[0]];

    model->unk44 = 0.0f;
}

void func_8010C7F8_log_jam(omObjData *obj) {
    f32 frame = 0.0f;
    HmfModel *model = &HmfModelData[obj->model[0]];

    if (model->unk04 != 0xFF) {
        if (HmfPauseF == 0) {
            frame = model->unk0E + 2;
        }
        if (model->unk0C <= frame) {
            model->unk02 = model->unk04;
            model->unk40 = model->unk4C;
            model->unk03 = model->unk05;
            model->unk48 = model->unk54;
            model->unk04 = 0xFF;
            model->unk44 = 1.0f;
        }
    }
}

void func_8010C8B0_log_jam(omObjData *obj) {
    if (obj->model[6] != -1) {
        func_800E4BA4_minigame(obj->model[6]);
    }
}

void func_8010C8E0_log_jam(s16 mdl, const char *part, Matrix4f *out) {
    HmfModel *model = &HmfModelData[mdl];
    HmfData *hmf = model->hmf;
    s16 idx = func_8002C834_main(hmf, part);
    D_800CCF58_main_Struct *anim = &D_800CCF58_main[HmfModelData[mdl].unk02];
    s16 parts[4]; /* retail's frame leaves 8 bytes here, as in func_80016B00_main */

    D_800D1358_main = out;
    D_800D04B4_main = parts;
    D_800CD1B0_main = 0;
    if (model->unk06 != 0xFF) {
        hmf->unk94 = (HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->unk06];
        hmf->unkAC = model->unk58;
    } else {
        hmf->unk94 = NULL;
    }
    if (model->unk04 != 0xFF && model->unk0C != 0) {
        hmf->unk90 = (HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->unk04];
        hmf->unkA4 = model->unk4C;
        hmf->unkA8 = (f32)model->unk0E / (f32)model->unk0C;
    } else {
        hmf->unk90 = NULL;
    }
    guMtxIdentF(D_800D5A00_main[0]);
    func_8002DFF8_main(hmf, model->unk40, anim, 1);
    if (hmf->unk90 != NULL) {
        func_8002EAC0_main(hmf, hmf->unkA4, hmf->unkA8);
    }
    if (hmf->unk94 != NULL) {
        func_8002DFF8_main(hmf, hmf->unkAC, (D_800CCF58_main_Struct *)hmf->unk94, 0);
    }
    D_800D138A_main = 0;
    func_80016C2C_main(hmf, 0, idx);
    if (D_800CD1B0_main >= 2) {
        osSyncPrintf("Mtx Made Over\n");
    }
}

void func_8010CAC0_log_jam(omObjData *obj, const char *part, Matrix4f out) {
    Matrix4f m;
    Matrix4f partMtx;

    func_8008A070_main(m);
    func_80017C10_main((Mtx *)m, obj->trans.x, obj->trans.y, obj->trans.z);
    func_80017D24_main(m, obj->rot.x, obj->rot.y, obj->rot.z);
    func_80017CD0_main(m, obj->scale.x, obj->scale.y, obj->scale.z);
    func_8010C8E0_log_jam(obj->model[0], part, &partMtx);
    func_80018044_main(partMtx, m, out);
}

s32 func_8010CB64_log_jam(HuSprite_Unk84_Struct *arg0, RGBA *arg1) {
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
    func_8010DA84_log_jam(arg0, temp_s4, 1.0f, 0, 0);
    gSPDisplayList(temp_v0_2++, osVirtualToPhysical(D_8010E190_log_jam));
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
    gDPSetRenderMode(temp_v0_2++, G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2);
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

s32 func_8010D74C_log_jam(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2) {
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

void func_8010D950_log_jam(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3) {
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

s32 func_8010DA84_log_jam(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
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
