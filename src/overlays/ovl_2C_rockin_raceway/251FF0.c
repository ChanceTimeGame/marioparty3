#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "game/hmfman.h"
#include "game/util.h"
#include "math.h"
#include "game/gamemes.h"
#include "game/audio.h"

// m1 rr: Rockin' Raceway (four karts race laps of a track; boost by tapping the buttons in rhythm)

/* One kart (D_80111B30, 4 of them, 0x70 each; the object keeps a pointer to it in work[]) */
typedef struct RrRacer {
    /* 0x00 */ u16 unk00; /* racer index */
    /* 0x02 */ u16 unk02; /* 0 driving, 1 spun out, 2 boosted */
    /* 0x04 */ s16 unk04; /* sound ids */
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A; /* player */
    /* 0x0C */ u16 unk0C; /* pad */
    /* 0x0E */ u16 unk0E; /* character */
    /* 0x10 */ u16 unk10; /* CPU */
    /* 0x12 */ u16 unk12; /* CPU difficulty */
    /* 0x14 */ u16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C; /* rank */
    /* 0x1E */ u16 unk1E; /* button expected next */
    /* 0x20 */ u16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ char unk2C[2];
    /* 0x2E */ u16 unk2E; /* lane */
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34; /* frame counter */
    /* 0x38 */ f32 unk38; /* speed */
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u16 unk4C; /* track node */
    /* 0x4E */ char unk4E[2];
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ Vec unk58; /* position */
    /* 0x64 */ Vec unk64; /* rotation */
} RrRacer; /* size 0x70 */

/* the four racing lines (D_80111B40), built by func_80109DA8 from D_801112A0 */
typedef struct RrPath {
    /* 0x00 */ s16 unk00; /* index */
    /* 0x02 */ u16 unk02; /* point count */
    /* 0x04 */ f32 unk04; /* lap length without the closing segment */
    /* 0x08 */ f32 unk08; /* length up to point D_801112C0[i] */
    /* 0x0C */ Vec *unk0C; /* points */
    /* 0x10 */ Vec *unk10; /* segment midpoints */
    /* 0x14 */ f32 *unk14; /* segment lengths */
    /* 0x18 */ f32 *unk18; /* length at each point (count + 1) */
    /* 0x1C */ Vec *unk1C; /* segment rotation */
    /* 0x20 */ u16 *unk20; /* per point: 1 or 2 placed at random */
} RrPath; /* size 0x24 */

/* A kart pose snapshot (D_80111B3C, [2][4]): a player's two trailing models */
typedef struct RrPose {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ Vec unk04;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ Vec unk1C;
} RrPose; /* size 0x28 */

typedef struct RrPoseSet {
    RrPose p[4];
} RrPoseSet; /* size 0xA0 */

/* An item box (D_80111B48, 8 of them) */
typedef struct RrItem {
    /* 0x00 */ u16 unk00; /* active */
    /* 0x02 */ s16 unk02; /* models */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ Vec unk0C; /* position */
    /* 0x18 */ Vec unk18; /* velocity */
} RrItem; /* size 0x24 */

/* Saved state of a smoke model (D_80111B50, 12 of them) */
typedef struct RrSmokeSave {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ Vec unk18;
    /* 0x24 */ Vec unk24;
} RrSmokeSave; /* size 0x30 */

/* A sprite effect (D_80111B5C, 16 of them) */
typedef struct RrEffect {
    /* 0x00 */ u16 unk00; /* active */
    /* 0x02 */ s16 unk02; /* model */
    /* 0x04 */ f32 unk04; /* frame */
    /* 0x08 */ f32 unk08; /* frame speed */
    /* 0x0C */ Vec unk0C; /* position */
    /* 0x18 */ Vec unk18; /* velocity */
    /* 0x24 */ Vec unk24; /* scale */
} RrEffect; /* size 0x30 */

/* 16 entries of D_80111B60 (and RRRecFrame.obj): an RrEffect and its model state, saved by func_801097A0 */
typedef struct RrMdlSave {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02; /* model unk40 */
    /* 0x04 */ s32 unk04; /* model unk18 */
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
    /* 0x28 */ Vec scale;
} RrMdlSave; /* size 0x34 */

/* the sprite files (D_80111B68) */
typedef struct RrSprFiles {
    /* 0x00 */ s16 unk00; /* 0x4D000E */
    /* 0x02 */ s16 unk02; /* 0x4D000F */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06; /* 0x4D0010 */
    /* 0x08 */ s16 unk08; /* 0x4D0011 */
    /* 0x0A */ s16 unk0A; /* 0x4D0012 */
    /* 0x0C */ s16 unk0C[2]; /* 0x31, 0x32: best time digits */
    /* 0x10 */ s16 unk10; /* 0x4D0013 */
} RrSprFiles;

/* A racer's standing while ranking */
typedef struct RrRank {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} RrRank; /* size 0x18 */

/* D_801112D0 is {s16, s16} node pairs per lane; the label sits on the second half, so this view is shifted by 2 */
typedef struct RrNodeView {
    /* 0x00 */ u16 unk00; /* D_801112D0[i].second */
    /* 0x02 */ u16 unk02; /* D_801112D0[i + 1].first */
} RrNodeView;

/* camera presets (D_80111350 to D_801113F8): center, rotation, zoom */
typedef struct RrCamPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} RrCamPreset;

/* Mirror of gamemes.c's GAMEMES (0x74), for the timer message position */
typedef struct RrGameMes {
    /* 0x00 */ char unk00[0x60];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ char unk68[0xC];
} RrGameMes; /* size 0x74 */

/* per player HUD (D_80111B80): position and the five digit offsets */
typedef struct RrHud {
    /* 0x00 */ s16 unk00; /* player */
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06; /* x */
    /* 0x08 */ s16 unk08; /* y */
    /* 0x0A */ s16 unk0A[5]; /* digit x relative to unk06 */
} RrHud; /* size 0x14 */

/* camera state (MP2 Looney Lumberjacks LLCamera) */
typedef struct RrCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} RrCamera; /* size 0x24 */

/* a camera focus point (D_80111C4C, 16 of them) */
typedef struct RrFocus {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 weight;
} RrFocus; /* size 0x10 */

typedef struct RRRecPlayer {
    /* 0x00 */ Vec trans;
    /* 0x0C */ Vec rot;
    /* 0x18 */ Vec scale;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
} RRRecPlayer; /* size 0x2C */

typedef struct RRRecModel {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
    /* 0x24 */ Vec scale;
} RRRecModel; /* size 0x30 */

/* One recorded frame of the race (30 kept in a ring). */
typedef struct RRRecFrame {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ s32 unk4[4];
    /* 0x014 */ RRRecPlayer player[4];
    /* 0x0C4 */ RRRecModel model[12];
    /* 0x304 */ RrMdlSave obj[16];
} RRRecFrame; /* size 0x644 */

/* A delayed sound effect (16 queued in D_80111BD0_rockin_raceway). */
typedef struct RRSe {
    /* 0x00 */ s16 fx;
    /* 0x02 */ s16 delay;
    /* 0x04 */ s16 kind;
    /* 0x06 */ s16 arg;
} RRSe;

/* Four vertices copied as one block (retail copies them byte-aligned). */
typedef struct RRQuad {
    u8 data[4 * sizeof(Vtx)];
} RRQuad;

typedef struct RRColor {
    u8 r, g, b, a;
} RRColor;

/* Pointers retail packs byte by byte into an object's work[]. */
typedef struct RRBytes {
    u32 a : 8;
    u32 b : 8;
    u32 c : 8;
    u32 d : 8;
} RRBytes;

typedef union RRPack {
    void* p;
    RRBytes b;
} RRPack;

/* func_8010C7CC with a camera preset */
#define RR_CAM(c, n) \
    func_8010C7CC_rockin_raceway((c).center.x, (c).center.y, (c).center.z, (c).rot.x, (c).rot.y, (c).rot.z, (c).zoom, n)

#define RR_WRAP(v)          \
    if ((v) >= 360.0) {     \
        (v) -= 360.0;       \
    } else if ((v) < 0.0) { \
        (v) += 360.0;       \
    }

// main
void Hu3DAnimInit(s32);
void func_800142A0_main(s32);
void func_8004A208_main(void);
void func_8004A950_main(void);
s32 func_8000B638_main(void);
u16 GWMgRecordGet(s16);
void func_80017D24_main(HuMtx4F m, f32, f32, f32);
void func_80088850_main(Mtx* m, f32 x, f32 y, f32 z);
void func_8008A070_main(HuMtx4F m);
s32 WipeStatGet(void);
s32 WipeCreateOut(s32, s32);
void* DataRead(s32 dirAndFile);
void DataClose(void*);
f64 fabs(f64); /* the GCC builtin (abs.d) */
f32 fabsf(f32);
f64 fmod(f64 x, f64 y);

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
extern s16 D_800D418E_main; /* the viewport being drawn */
extern u16 D_800D530C_main;
extern u16 D_800D5558_main[];
extern u8 D_800D6A90_main;
extern s32 D_800EBE24_minigame;
extern s32 fontcolor;
extern Vec CRot;
extern RrGameMes gMesData[];

// rockin_raceway .data (0x80110EE0, 0x860 bytes)

/* the four racing lines' points (D_801112A0) */
Vec D_80110EE0_rockin_raceway[20] = {
    { 704.785f, 0.0f, -699.55f }, { 201.485f, 0.0f, -705.05f }, { -294.435f, 0.0f, -705.05f },
    { -801.855f, 0.0f, -710.0f }, { -986.52f, 0.0f, -629.3f }, { -1153.55f, 0.0f, -519.15f },
    { -1278.255f, 0.0f, -365.4f }, { -1350.875f, 0.0f, -188.65f }, { -1376.325f, 0.0f, 1.4f },
    { -1353.34f, 0.0f, 186.6f }, { -1275.89f, 0.0f, 363.35f }, { -1152.43f, 0.0f, 513.45f },
    { -989.035f, 0.0f, 632.1f }, { -800.13f, 0.0f, 698.7f }, { -308.055f, 0.0f, 699.75f },
    { 299.445f, 0.0f, 699.75f }, { 787.435f, 0.0f, 704.75f }, { 980.315f, 0.0f, 633.85f },
    { 1143.355f, 0.0f, 515.55f }, { 1268.58f, 0.0f, 364.75f },
};
Vec D_80110FD0_rockin_raceway[20] = {
    { 698.385f, 0.0f, -607.55f }, { 202.65f, 0.0f, -613.3f }, { -292.17f, 0.0f, -624.85f },
    { -777.295f, 0.0f, -619.1f }, { -937.375f, 0.0f, -547.5f }, { -1076.53f, 0.0f, -442.5f },
    { -1183.765f, 0.0f, -312.4f }, { -1254.48f, 0.0f, -161.75f }, { -1275.04f, 0.0f, -6.5f },
    { -1249.91f, 0.0f, 162.4f }, { -1183.76f, 0.0f, 315.35f }, { -1081.105f, 0.0f, 445.45f },
    { -937.39f, 0.0f, 548.2f }, { -773.115f, 0.0f, 609.8f }, { -305.52f, 0.0f, 611.15f },
    { 301.515f, 0.0f, 616.5f }, { 765.37f, 0.0f, 610.85f }, { 932.645f, 0.0f, 550.75f },
    { 1069.645f, 0.0f, 447.45f }, { 1180.59f, 0.0f, 316.0f },
};
Vec D_801110C0_rockin_raceway[20] = {
    { 699.23f, 0.0f, -517.35f }, { 203.075f, 0.0f, -525.15f }, { -299.32f, 0.0f, -530.1f },
    { -748.01f, 0.0f, -515.15f }, { -882.0f, 0.0f, -463.1f }, { -1005.37f, 0.0f, -380.85f },
    { -1095.59f, 0.0f, -266.7f }, { -1148.435f, 0.0f, -138.95f }, { -1172.27f, 0.0f, 0.65f },
    { -1155.245f, 0.0f, 135.25f }, { -1095.645f, 0.0f, 268.1f }, { -1003.655f, 0.0f, 377.15f },
    { -886.2f, 0.0f, 465.7f }, { -748.21f, 0.0f, 520.25f }, { -297.04f, 0.0f, 523.75f },
    { 295.995f, 0.0f, 519.85f }, { 740.775f, 0.0f, 523.75f }, { 877.835f, 0.0f, 464.55f },
    { 992.225f, 0.0f, 376.9f }, { 1088.745f, 0.0f, 269.6f },
};
Vec D_801111B0_rockin_raceway[20] = {
    { 701.125f, 0.0f, -421.1f }, { 202.54f, 0.0f, -419.7f }, { -303.185f, 0.0f, -424.85f },
    { -716.595f, 0.0f, -419.3f }, { -833.05f, 0.0f, -380.45f }, { -931.415f, 0.0f, -309.8f },
    { -1004.03f, 0.0f, -220.2f }, { -1050.36f, 0.0f, -113.6f }, { -1067.345f, 0.0f, -0.8f },
    { -1051.89f, 0.0f, 113.5f }, { -1007.115f, 0.0f, 218.55f }, { -931.46f, 0.0f, 309.75f },
    { -835.715f, 0.0f, 377.7f }, { -719.915f, 0.0f, 428.7f }, { -303.6f, 0.0f, 429.95f },
    { 302.365f, 0.0f, 429.95f }, { 711.44f, 0.0f, 429.95f }, { 826.63f, 0.0f, 385.3f },
    { 925.47f, 0.0f, 314.3f }, { 1000.045f, 0.0f, 220.2f },
};
Vec* D_801112A0_rockin_raceway[4] = {
    D_80110EE0_rockin_raceway,
    D_80110FD0_rockin_raceway,
    D_801110C0_rockin_raceway,
    D_801111B0_rockin_raceway,
};
s32 D_801112B0_rockin_raceway[4] = { 20, 20, 20, 20 }; /* point count per line; label D_801112B2 = low halves */
s32 D_801112C0_rockin_raceway[4] = { 15, 15, 15, 15 }; /* last node per lane */
u16 D_801112D0_rockin_raceway[4][2] = { { 8, 14 }, { 8, 14 }, { 8, 14 }, { 8, 14 } }; /* D_801112D2 = D_801112D0 + 2 */
f32 D_801112E0_rockin_raceway[4] = { 1.0f, 1.1f, 1.2f, 1.4f };
f32 D_801112F0_rockin_raceway[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
/* CPU speed thresholds, a pair per difficulty */
f32 D_80111300_rockin_raceway[8] = { 0.6f, 0.7f, 0.7f, 0.8f, 0.8f, 0.9f, 0.9f, 0.99f };
s32 D_80111320_rockin_raceway[4] = { 5, 4, 3, 2 };
s16 D_80111330_rockin_raceway[4][2] = { { 30, 30 }, { 270, 30 }, { 30, 211 }, { 270, 211 } };
s16 D_80111340_rockin_raceway[8] = { 118, 130, 138, 150, 162, 172, 184, 196 };
RrCamPreset D_80111350_rockin_raceway = { { 0.0f, -288.8f, -65.0f }, { 326.0f, 0.0f, 0.0f }, 4278.0f };
RrCamPreset D_8011136C_rockin_raceway = { { 0.0f, 200.8f, -65.0f }, { 326.0f, 0.0f, 0.0f }, 4278.0f };
RrCamPreset D_80111388_rockin_raceway = { { 136.0f, -94.8f, -1001.8f }, { 341.0f, 305.5f, 0.0f }, 952.0f };
RrCamPreset D_801113A4_rockin_raceway = { { 1126.0f, -94.8f, -721.8f }, { 341.0f, 305.5f, 0.0f }, 952.0f };
RrCamPreset D_801113C0_rockin_raceway = { { 246.0f, 33.2f, -693.8f }, { 350.3f, 285.4f, 0.0f }, 1140.0f };
RrCamPreset D_801113DC_rockin_raceway = { { 0.0f, 200.8f, -65.0f }, { 326.0f, 0.0f, 0.0f }, 3278.0f };
RrCamPreset D_801113F8_rockin_raceway = { { 340.0f, -200.0f, 165.0f }, { 326.0f, 0.0f, 0.0f }, 1678.0f };
Vec D_80111414_rockin_raceway[4] = {
    { -384.5f, 56.6f, -88.4f }, { -387.95f, 39.8f, 85.75f }, { -129.3f, 56.6f, -88.4f },
    { -129.3f, 39.8f, 85.75f },
};
Vec D_80111444_rockin_raceway[12] = {
    { 58.4f, 58.75f, -92.85f }, { 126.8f, 58.75f, -92.85f }, { 222.3f, 58.75f, -92.85f },
    { 290.7f, 58.75f, -92.85f }, { 397.8f, 58.75f, -92.85f }, { 466.15f, 58.75f, -92.85f },
    { 58.4f, 43.75f, 82.0f }, { 126.8f, 43.75f, 82.0f }, { 222.3f, 43.75f, 82.0f },
    { 290.7f, 43.75f, 82.0f }, { 397.8f, 43.75f, 82.0f }, { 466.15f, 43.75f, 82.0f },
};
RRColor D_801114D4_rockin_raceway = { 0xE9, 0xDD, 0xA1, 0xFF };
Vtx D_801114D8_rockin_raceway[4] = {
    { { { 67, -67, 0 }, 0, { 1984, 0 }, { 0, 0, 0, 255 } } },
    { { { 67, 67, 0 }, 0, { 1984, 1984 }, { 0, 0, 0, 255 } } },
    { { { -65, -67, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
    { { { -67, 67, 0 }, 0, { 0, 1984 }, { 0, 0, 0, 255 } } },
};
Vtx D_80111518_rockin_raceway[4] = {
    { { { 29, -62, 0 }, 0, { 960, 0 }, { 0, 0, 0, 255 } } },
    { { { 29, 62, 0 }, 0, { 960, 1984 }, { 0, 0, 0, 255 } } },
    { { { -29, -62, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } } },
    { { { -29, 62, 0 }, 0, { 0, 1984 }, { 0, 0, 0, 255 } } },
};
u32 D_80111558_rockin_raceway = 0xFFFFFFFF;
s32 D_8011155C_rockin_raceway = 0; /* D_8011155E = low half */
s32 D_80111560_rockin_raceway[4] = { 0, 1, 2, 3 }; /* D_80111562 = D_80111560 + 2: the low halves */
s32 D_80111570_rockin_raceway[4] = { -1, -1, -1, -1 };
u16 D_80111580_rockin_raceway[8] = { 1, 2, 3, 4, 5, 6, 12, 13 };
u32 D_80111590_rockin_raceway[3] = { 0, 0x400, 0x800 };
s32 D_8011159C_rockin_raceway[4] = { -1, -1, -1, -1 };
s32 D_801115AC_rockin_raceway[2] = { 0, 0 };
RRColor D_801115B4_rockin_raceway = { 0xFF, 0xFF, 0xFF, 0xFF };
s32 D_801115B8_rockin_raceway[8] = { 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
s32 D_801115D8_rockin_raceway[6] = { 0, 1, 3, 4, 6, 7 };
s32 D_801115F0_rockin_raceway = 0;
s32 D_801115F4_rockin_raceway = 0;
s32 D_801115F8_rockin_raceway = 0;
s32 D_801115FC_rockin_raceway = -1;

Gfx D_80111600_rockin_raceway[] = {
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
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
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
Gfx D_801116B8_rockin_raceway[] = {
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
Gfx D_801116D8_rockin_raceway[] = {
    gsSPDisplayList(D_801116B8_rockin_raceway),
    gsSPDisplayList(D_80111600_rockin_raceway),
    gsSPEndDisplayList(),
};
Gfx D_801116F0_rockin_raceway[] = {
    gsDPPipeSync(),
    gsSPDisplayList(D_801116D8_rockin_raceway),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};
RRColor D_80111730_rockin_raceway = { 0xFF, 0xFF, 0xFF, 0xFF };
RRColor D_80111734_rockin_raceway = { 0xFF, 0xFF, 0xFF, 0xFF };

/* labels inside the objects above (undefined_syms.txt aliases) */
extern RrNodeView D_801112D2_rockin_raceway[]; /* D_801112D0 + 2 */
extern s16 D_8011155E_rockin_raceway; /* low half of D_8011155C */
extern u16 D_80111562_rockin_raceway[][2]; /* D_80111560 + 2 */

// rockin_raceway .bss
extern s32 D_80111AC0_rockin_raceway;
extern omObjData* D_80111AC4_rockin_raceway;
extern s32 D_80111AC8_rockin_raceway;
extern s32 D_80111ACC_rockin_raceway;
extern s32 D_80111AD0_rockin_raceway;
extern s32 D_80111AD4_rockin_raceway;
extern s32 D_80111AD8_rockin_raceway; /* race state */
extern s32 D_80111ADC_rockin_raceway;
extern s16 D_80111AE0_rockin_raceway;
extern s32 D_80111AE4_rockin_raceway;
extern s32 D_80111AE8_rockin_raceway;
extern u16 D_80111AEA_rockin_raceway; /* low half of D_80111AE8 */
extern s32 D_80111AEC_rockin_raceway;
extern s32 D_80111AF0_rockin_raceway[4];
extern s32 D_80111B00_rockin_raceway[2 * 6]; /* best time digits, six per time */
extern RrRacer* D_80111B30_rockin_raceway;
extern s16 D_80111B34_rockin_raceway;
extern s16 D_80111B36_rockin_raceway;
extern s16 D_80111B38_rockin_raceway;
extern s16 D_80111B3A_rockin_raceway;
extern RrPoseSet* D_80111B3C_rockin_raceway;
extern RrPath* D_80111B40_rockin_raceway;
extern f32 D_80111B44_rockin_raceway;
extern RrItem* D_80111B48_rockin_raceway;
extern omObjData* D_80111B4C_rockin_raceway;
extern RrSmokeSave* D_80111B50_rockin_raceway;
extern s16 D_80111B54_rockin_raceway;
extern omObjData* D_80111B58_rockin_raceway;
extern RrEffect* D_80111B5C_rockin_raceway;
extern RrMdlSave* D_80111B60_rockin_raceway;
extern s16 D_80111B64_rockin_raceway;
extern RrSprFiles* D_80111B68_rockin_raceway;
extern s16 D_80111B6C_rockin_raceway[4]; /* sprite groups */
extern s16 D_80111B74_rockin_raceway;
extern s16 D_80111B76_rockin_raceway[2]; /* best time sprite groups */
extern s16 D_80111B7A_rockin_raceway; /* new record pulse timer */
extern RrHud D_80111B80_rockin_raceway[4];
extern RRSe* D_80111BD0_rockin_raceway;
extern s16 D_80111BD4_rockin_raceway;
extern s16 D_80111BD6_rockin_raceway;
extern omObjData* D_80111BD8_rockin_raceway;
extern RrCamera D_80111BE0_rockin_raceway[2]; /* [0] target, [1] start */
extern s16 D_80111C28_rockin_raceway;
extern s16 D_80111C2A_rockin_raceway;
extern s16 D_80111C2C_rockin_raceway;
extern s16 D_80111C2E_rockin_raceway;
extern omObjData* D_80111C30_rockin_raceway;
extern s16 D_80111C34_rockin_raceway; /* focus point count */
extern f32 D_80111C38_rockin_raceway[5]; /* focus centre x, y, z; [3] (D_80111C44) summed weight; [4] (D_80111C48) target zoom */
extern RrFocus* D_80111C4C_rockin_raceway;
extern RRRecFrame* D_80111C50_rockin_raceway;
extern s32 D_80111C54_rockin_raceway;
extern s32 D_80111C58_rockin_raceway;

// rockin_raceway functions
void func_801059A0_rockin_raceway(void);
void func_80105C24_rockin_raceway(omObjData* obj);
void func_80105CB0_rockin_raceway(omObjData* obj);
void func_80106A5C_rockin_raceway(omObjData* obj);
void func_80106A80_rockin_raceway(omObjData* obj);
void func_80106B28_rockin_raceway(void);
void func_80106DC8_rockin_raceway(omObjData* obj);
void func_801071D8_rockin_raceway(omObjData* obj);
void func_8010769C_rockin_raceway(omObjData* obj);
void func_80107958_rockin_raceway(RrRacer* r);
void func_80107A38_rockin_raceway(RrRacer* r);
void func_80107BFC_rockin_raceway(RrRacer* r);
void func_80107D04_rockin_raceway(omObjData* obj);
void func_80107E78_rockin_raceway(s32 slot, s16 arg1);
void func_8010803C_rockin_raceway(s32* order);
s32 func_80108464_rockin_raceway(void);
void func_80108578_rockin_raceway(void);
s32 func_80108760_rockin_raceway(Vec* pos, Vec* vel, s16 time);
void func_80108864_rockin_raceway(omObjData* obj);
s32 func_80108A80_rockin_raceway(Vec* pos);
void func_80108BAC_rockin_raceway(void);
void func_80108D84_rockin_raceway(void);
void func_80108ED4_rockin_raceway(omObjData* obj);
void func_80108F8C_rockin_raceway(f32 x, f32 y, f32 z);
void func_80109044_rockin_raceway(void);
void func_80109134_rockin_raceway(void);
void func_80109208_rockin_raceway(void);
void func_80109384_rockin_raceway(omObjData* obj);
s32 func_801094EC_rockin_raceway(Vec* pos, Vec* vel, Vec* scale, f32 speed);
void func_80109CF8_rockin_raceway(void);
void func_801096A0_rockin_raceway(RrRacer* kart);
void func_801097A0_rockin_raceway(void);
void func_801098D8_rockin_raceway(void);
void func_801099AC_rockin_raceway(void);
void func_80109A04_rockin_raceway(omObjData *obj);
void func_80109D00_rockin_raceway(s32 *arg0);
void func_80109D54_rockin_raceway(s32 *times);
void func_80109DA8_rockin_raceway(void);
f32 func_8010A258_rockin_raceway(u16 idx, f32 dist, f32 base, f32 delta, u16 *seg, f32 *frac, Vec *pos, Vec *rot);
s32 func_8010A48C_rockin_raceway(u16 idx, u16 pt);
u16 func_8010A4C0_rockin_raceway(s32 file);
void func_8010A504_rockin_raceway(void);
void func_8010A5E4_rockin_raceway(s16 player, s16 kind);
void func_8010A990_rockin_raceway(omObjData *obj);
void func_8010AAAC_rockin_raceway(s16 player, s16 value, u16 mode);
void func_8010B124_rockin_raceway(void);
void func_8010B2B8_rockin_raceway(void);
void func_8010B5DC_rockin_raceway(s32 *times);
void func_8010B774_rockin_raceway(void);
void func_8010B89C_rockin_raceway(void);
void func_8010C0D8_rockin_raceway(omObjData *obj);
void func_8010C5E0_rockin_raceway(s32 idx);
void func_8010C7CC_rockin_raceway(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
void func_8010C9BC_rockin_raceway(void);
void func_8010C9CC_rockin_raceway(void);
void func_8010CA1C_rockin_raceway(void);
void func_8010CADC_rockin_raceway(Vec *pos, f32 weight);
void func_8010CB5C_rockin_raceway(RrRacer* kart, f32 weight);
void func_8010CC10_rockin_raceway(void);
void func_8010CE90_rockin_raceway(omObjData *obj);
void func_8010D104_rockin_raceway(void);
void func_8010D114_rockin_raceway(void);
void func_8010D134_rockin_raceway(s32 idx);
void func_8010D288_rockin_raceway(s32 cam, Vec* pos, f32* screen, f32* rel);
void func_8010D5B8_rockin_raceway(void);
void func_8010D600_rockin_raceway(void);
RRRecFrame* func_8010D944_rockin_raceway(s32 idx);
void func_8010D9C4_rockin_raceway(s32 frame);
void func_8010E08C_rockin_raceway(s32 idx);
void func_8010E2E4_rockin_raceway(void);
s32 func_8010E344_rockin_raceway(s16 fx, s16 delay, s16 kind, s16 arg);
void func_8010E39C_rockin_raceway(void);
f32 func_8010E504_rockin_raceway(f32 a, f32 b);
f32 func_8010E608_rockin_raceway(f32 target, f32 cur, f32 step);
f32 func_8010E7C8_rockin_raceway(f32 t, f32 a, f32 b);
f32 func_8010E7E0_rockin_raceway(f32 t, f32 a, f32 b);
f32 func_8010E840_rockin_raceway(f32 t, f32 a, f32 b, f32 c);
void func_8010E8A0_rockin_raceway(f32 t, Vec* a, Vec* b, Vec* c, Vec* out);
f32 func_8010E93C_rockin_raceway(f32 t, f32 a, f32 b, f32 c);
void func_8010E994_rockin_raceway(f32 t, Vec* a, Vec* b, Vec* c, Vec* out);
f32 func_8010EB04_rockin_raceway(f32 x, f32 z);
void func_8010EB84_rockin_raceway(Vec* dir, f32* angles);
void func_8010EC0C_rockin_raceway(omObjData* obj, void* p);
RrRacer* func_8010EC38_rockin_raceway(omObjData* obj);
s32 func_8010EC8C_rockin_raceway(HuSprite_Unk84_Struct* spr, RRColor* color);
s32 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct* spr, u16 model, RRColor* color);
void func_8010FA78_rockin_raceway(u16 model, HuSprite_Unk84_Struct* spr, u16 frame, RRColor* color);
s32 func_8010FBAC_rockin_raceway(HuSprite_Unk84_Struct* spr, HmfData* hmf, f32 scale, u16 x, u16 y);
s32 func_8010FFB8_rockin_raceway(HuSprite_Unk84_Struct* spr, Vtx* vtx);
void func_80110C38_rockin_raceway(s16* models, HuSprite_Unk84_Struct* spr, s32* players);
void func_80110D90_rockin_raceway(s16* models, HuSprite_Unk84_Struct* spr, s32* times /* unused */);


/* "ＳＴＡＲＴ" */
const s16 D_80111740_rockin_raceway[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000 };

/* "ＦＩＮＩＳＨ" */
const s16 D_8011174C_rockin_raceway[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000, 0x0000, 0x0000 };

void func_801059A0_rockin_raceway(void) {
    u8 cam;

    Hu3DAnimInit(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(0x40);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 67.0f, 16.0f, 98.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 1.0f, 50.0f, -108.0f);
    HmfLightMaxSet(2);
    func_8000B5F0_main(1);
    cam = func_8000B638_main();
    ScissorSet(cam, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(cam, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 6000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_80111ACC_rockin_raceway = 0;
    D_80111AD0_rockin_raceway = 0;
    D_80111AD4_rockin_raceway = 0;
    D_80111AD8_rockin_raceway = 0;
    D_80111ADC_rockin_raceway = 0;
    D_80111AE0_rockin_raceway = 0;
    D_80111BD4_rockin_raceway = -1;
    D_80111BD6_rockin_raceway = -1;
    D_80111B36_rockin_raceway = 0;
    D_80111B38_rockin_raceway = 0;
    D_80111AE4_rockin_raceway = 0;
    D_80111AEC_rockin_raceway = 5400;
    D_80111AE8_rockin_raceway = GWMgRecordGet(3);
    if (D_80111AE8_rockin_raceway == 0) {
        D_80111AE8_rockin_raceway = 9000;
    }
    D_80111BD8_rockin_raceway = 0;
    D_80111C30_rockin_raceway = 0;
    D_80111B68_rockin_raceway = HuMemAllocTag(0x40, 0x7918);
    D_80111AC4_rockin_raceway = omAddObj(0x20, 0, 0, -1, func_80105C24_rockin_raceway);
    func_80045010_main(D_80111740_rockin_raceway, 1);
    func_80045010_main(D_8011174C_rockin_raceway, 1);
}

void func_80105C24_rockin_raceway(omObjData* obj) {
    obj->func = func_80105CB0_rockin_raceway;
    func_80109DA8_rockin_raceway();
    func_801099AC_rockin_raceway();
    func_80108D84_rockin_raceway();
    func_80109208_rockin_raceway();
    func_8010A504_rockin_raceway();
    func_8010B124_rockin_raceway();
    func_80106B28_rockin_raceway();
    func_80108578_rockin_raceway();
    func_8010E2E4_rockin_raceway();
    func_8010B774_rockin_raceway();
    func_8010D5B8_rockin_raceway();
    if (_CheckFlag(0xA) != 0) {
        D_80111AC8_rockin_raceway = 1;
    }
}


void func_80105CB0_rockin_raceway(omObjData* obj) {
    s32 times[2];
    omObjData* leadObj;
    omObjData* otherObj;
    RrRacer* lead;
    RrRacer* other;
    s32 i;
    s16 mes;
    f32 t;

    times[0] = 0;
    times[1] = 0;
    func_80106A80_rockin_raceway(obj);
    func_8010E39C_rockin_raceway();
    if (D_80111BD6_rockin_raceway >= 0) {
        if (--D_80111BD6_rockin_raceway == 0) {
            D_80111BD4_rockin_raceway = HuAudFXPlay(0x470);
            func_8004AAD0_main(D_80111BD4_rockin_raceway, 0x40);
            HuAudFXPitchSet(D_80111BD4_rockin_raceway, 0);
            D_80111BD6_rockin_raceway = -1;
        }
    }
    switch (D_80111AD8_rockin_raceway) {
        case 0:
            D_80111AD8_rockin_raceway = 1;
            D_80111ADC_rockin_raceway = 0;
            break;
        case 1:
            switch (D_80111ADC_rockin_raceway) {
                case 0:
                    HuAudFXPlay(0x46F);
                    RR_CAM(D_8011136C_rockin_raceway, 19);
                    D_80111C2E_rockin_raceway = 0;
                    D_80111ADC_rockin_raceway++;
                    break;
                case 2:
                    RR_CAM(D_80111388_rockin_raceway, 75);
                    D_80111C2E_rockin_raceway = 0;
                    D_80111ADC_rockin_raceway++;
                    break;
                case 4:
                    if (D_80111AD0_rockin_raceway >= 5) {
                        D_80111ADC_rockin_raceway++;
                    }
                    break;
                case 6:
                    RR_CAM(D_801113A4_rockin_raceway, 75);
                    D_80111C2E_rockin_raceway = 0;
                    D_80111AD0_rockin_raceway = 0;
                    D_80111ADC_rockin_raceway++;
                    break;
                case 8:
                    RR_CAM(D_801113C0_rockin_raceway, 45);
                    D_80111C2E_rockin_raceway = 2;
                    D_80111ADC_rockin_raceway++;
                    break;
                case 10:
                    if (D_80111AD0_rockin_raceway == 3) {
                    } else if (D_80111AD0_rockin_raceway >= 4) {
                        D_80111AD8_rockin_raceway = 2;
                        D_80111ADC_rockin_raceway = 0;
                    }
                    break;
                default:
                    if (D_80111ADC_rockin_raceway == 9 && D_80111AD0_rockin_raceway == 20) {
                        GMesCreate(3);
                        HuAudSeqPlay(0x2E);
                    }
                    if (D_80111C2C_rockin_raceway == 0) {
                        if (D_80111ADC_rockin_raceway == 3) {
                            HuAudSeqPlay(0x6D);
                        }
                        D_80111AD0_rockin_raceway = 0;
                        D_80111ADC_rockin_raceway++;
                    }
                    break;
            }
            break;
        case 2:
            if (D_80111AD0_rockin_raceway == 8) {
                HuAudFXPlay(0x46C);
            }
            if (D_80111AD0_rockin_raceway == 30) {
                D_80111AE0_rockin_raceway = 1;
            }
            if (D_80111AD0_rockin_raceway == 20) {
                func_8010C9BC_rockin_raceway();
                func_8010CA1C_rockin_raceway();
            }
            func_8010803C_rockin_raceway(D_80111AF0_rockin_raceway);
            if (D_80111AE0_rockin_raceway != 0) {
                times[0] = ++D_80111AE4_rockin_raceway;
                times[1] = D_80111AE8_rockin_raceway;
                func_8010B5DC_rockin_raceway(times);
                func_80109D00_rockin_raceway(D_80111AF0_rockin_raceway);
                func_80109D54_rockin_raceway(times);
                func_8010D600_rockin_raceway();
                D_80111AEC_rockin_raceway--;
            }
            if (D_80111AEC_rockin_raceway == 900) {
                mes = GMesCreate(0x1A, 30, 156, 56);
                gMesData[mes].unk60 = 156.0f;
                gMesData[mes].unk64 = 56.0f;
            } else if (D_80111AEC_rockin_raceway < 900) {
                func_8003F578_main((D_80111AEC_rockin_raceway + 29) / 30);
                if (D_80111AEC_rockin_raceway == 0) {
                    func_8003F5C0_main();
                }
            }
            if ((D_80111B34_rockin_raceway = func_80108464_rockin_raceway()) != -1 || D_80111AEC_rockin_raceway <= 0) {
                func_8010D104_rockin_raceway();
                func_8010C9CC_rockin_raceway();
                RR_CAM(D_801113DC_rockin_raceway, 10);
                D_80111C2E_rockin_raceway = 2;
                if (D_80111B34_rockin_raceway != -1) {
                    leadObj = D_800EC598_minigame[D_80111AF0_rockin_raceway[0]];
                    lead = func_8010EC38_rockin_raceway(leadObj);
                    for (i = 1; i < 4; i++) {
                        otherObj = D_800EC598_minigame[D_80111AF0_rockin_raceway[i]];
                        other = func_8010EC38_rockin_raceway(otherObj);
                        if (other->unk02 == 1) {
                            continue;
                        }
                        if (fabs(lead->unk48 - other->unk48) < 30.0) {
                            D_80111B38_rockin_raceway = 3;
                            break;
                        }
                        if (lead->unk48 - other->unk48 < 100.0) {
                            if (fabs(leadObj->trans.x - otherObj->trans.x) < 30.0) {
                                D_80111B38_rockin_raceway = 3;
                            } else {
                                D_80111B38_rockin_raceway = 1;
                            }
                            break;
                        }
                    }
                }
                for (i = 0; i < 4; i++) {
                    lead = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
                    if (lead->unk04 != -1) {
                        HuAudFXStop(lead->unk04);
                        lead->unk04 = -1;
                    }
                    if (lead->unk06 != -1) {
                        HuAudFXStop(lead->unk06);
                        lead->unk06 = -1;
                    }
                }
                GMesCreate(0xE);
                HuAudSeqFadeOut(120);
                D_80111AD8_rockin_raceway = 3;
                D_80111ADC_rockin_raceway = 0;
            }
            break;
        case 3:
            if (D_80111AD0_rockin_raceway == 3 && D_80111BD4_rockin_raceway != -1) {
                func_8004AAD0_main(D_80111BD4_rockin_raceway, 110);
                HuAudFXPitchSet(D_80111BD4_rockin_raceway, 200);
            }
            if (GMesStatGet() == 0) {
                D_80111AD8_rockin_raceway = 4;
                D_80111ADC_rockin_raceway = 0;
            }
            break;
        case 4:
            if (D_80111AD0_rockin_raceway >= 15) {
                if (D_80111B34_rockin_raceway != -1) {
                    GwPlayer[((RrRacer*)func_8010EC38_rockin_raceway(D_800EC598_minigame[D_80111B34_rockin_raceway]))->unk0A].bonusCoin += 10;
                    if (D_80111B38_rockin_raceway != 0) {
                        func_80109044_rockin_raceway();
                        func_801097A0_rockin_raceway();
                        func_8010E08C_rockin_raceway(D_80111B34_rockin_raceway);
                        D_80111AD8_rockin_raceway = 5;
                    } else {
                        D_80111AD8_rockin_raceway = 6;
                    }
                } else {
                    D_80111AD8_rockin_raceway = 6;
                }
                D_80111ADC_rockin_raceway = 0;
            }
            break;
        case 5:
            D_80111B3A_rockin_raceway = 1;
            if (D_80111ADC_rockin_raceway >= 1 && D_80111ADC_rockin_raceway <= 28) {
                if (D_80111AD0_rockin_raceway >= 4.5f) {
                    if (D_80111ADC_rockin_raceway == 10) {
                        func_80107E78_rockin_raceway(0, 9);
                    }
                    D_80111ADC_rockin_raceway++;
                    D_80111AD0_rockin_raceway = 0;
                }
            } else if (D_80111ADC_rockin_raceway < 33) {
                if (D_80111AD0_rockin_raceway >= 7.5f) {
                    D_80111ADC_rockin_raceway++;
                    D_80111AD0_rockin_raceway = 0;
                }
            } else if (D_80111AD0_rockin_raceway >= 30.0f) {
                D_80111ADC_rockin_raceway++;
                D_80111AD0_rockin_raceway = 0;
            }
            if (D_80111ADC_rockin_raceway < 30) {
                func_8010D9C4_rockin_raceway(D_80111ADC_rockin_raceway);
                if (D_80111BD4_rockin_raceway != -1) {
                    t = D_80111ADC_rockin_raceway / 30.0f;
                    func_8004AAD0_main(D_80111BD4_rockin_raceway, func_8010E7C8_rockin_raceway(t, 64.0f, 110.0f));
                    HuAudFXPitchSet(D_80111BD4_rockin_raceway, (s16)func_8010E7C8_rockin_raceway(t, 0.0f, 200.0f));
                }
                RR_CAM(D_801113F8_rockin_raceway, 1);
            } else if (D_80111ADC_rockin_raceway < 34) {
                if (D_80111BD4_rockin_raceway != -1) {
                    func_8004AAD0_main(D_80111BD4_rockin_raceway, 110);
                    HuAudFXPitchSet(D_80111BD4_rockin_raceway, 200);
                }
                func_8010D9C4_rockin_raceway(29);
                func_8010C7CC_rockin_raceway(65535.0f, 65535.0f, 65535.0f, 65535.0f, 65535.0f, 65535.0f,
                                             D_801113F8_rockin_raceway.zoom - (D_80111ADC_rockin_raceway - 29) * 100, 1);
            } else {
                RR_CAM(D_801113DC_rockin_raceway, 1);
                func_80109134_rockin_raceway();
                func_801098D8_rockin_raceway();
                D_80111B3A_rockin_raceway = 0;
                D_80111AD8_rockin_raceway = 6;
                D_80111ADC_rockin_raceway = 0;
            }
            break;
        case 6:
            switch (D_80111ADC_rockin_raceway) {
                case 0:
                    if (D_80111AD0_rockin_raceway >= 15.0f || D_80111B38_rockin_raceway == 0) {
                        if (D_80111B34_rockin_raceway != -1 && D_80111AE4_rockin_raceway < D_80111AE8_rockin_raceway) {
                            D_80111AE8_rockin_raceway = D_80111AE4_rockin_raceway;
                            GWMgRecordSet(3, D_80111AEA_rockin_raceway);
                            GMesCreate(0x1B);
                            D_80111B7A_rockin_raceway = 15;
                            D_80111AD4_rockin_raceway = 99;
                            D_80111B36_rockin_raceway = 1;
                            D_80111ADC_rockin_raceway++;
                        } else {
                            D_80111ADC_rockin_raceway = 2;
                        }
                        times[0] = D_80111AE4_rockin_raceway;
                        times[1] = D_80111AE8_rockin_raceway;
                        func_8010B5DC_rockin_raceway(times);
                        D_80111AD0_rockin_raceway = 0;
                    }
                    break;
                case 1:
                    if (D_80111AD0_rockin_raceway >= 75.0f) {
                        D_80111ADC_rockin_raceway++;
                        D_80111AD0_rockin_raceway = 0;
                    }
                    break;
                case 2:
                    if (D_80111B34_rockin_raceway != -1) {
                        lead = func_8010EC38_rockin_raceway(D_800EC598_minigame[D_80111B34_rockin_raceway]);
                        GMesCreate(0x16, lead->unk0E);
                        if (D_80111B36_rockin_raceway == 0) {
                            HuAudSeqPlay(0x65);
                            D_80111AD4_rockin_raceway = 138;
                        } else {
                            HuAudSeqPlay(0x6A);
                        }
                        func_8004ACE0_main(0x28F, lead->unk0A);
                        func_8010C9BC_rockin_raceway();
                        func_8010D114_rockin_raceway();
                    } else {
                        if (D_80111B36_rockin_raceway == 0) {
                            HuAudSeqPlay(0x6C);
                            D_80111AD4_rockin_raceway = 144;
                        }
                        GMesCreate(0x20);
                    }
                    D_80111ADC_rockin_raceway++;
                    D_80111AD0_rockin_raceway = 0;
                    break;
                case 3:
                    if (GMesStatGet() == 0) {
                        D_80111ADC_rockin_raceway++;
                        D_80111AD0_rockin_raceway = 0;
                    }
                    break;
                case 4:
                    if (D_80111AD0_rockin_raceway >= 15) {
                        WipeCreateOut(0, 16);
                        HuAudSeqFadeOut(16);
                        func_8004AB0C_main(16);
                        D_80111AD0_rockin_raceway = 0;
                        D_80111ADC_rockin_raceway++;
                    }
                    break;
                default:
                    if (WipeStatGet() == 0) {
                        obj->func = func_80106A5C_rockin_raceway;
                    }
                    break;
            }
            break;
    }
    func_8010B2B8_rockin_raceway();
    D_80111ACC_rockin_raceway++;
    if (D_80111558_rockin_raceway == D_80111AD8_rockin_raceway) {
        D_80111AD0_rockin_raceway++;
    } else {
        D_80111AD0_rockin_raceway = 0;
        D_80111558_rockin_raceway = D_80111AD8_rockin_raceway;
    }
}

void func_80106A5C_rockin_raceway(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_80106A80_rockin_raceway(omObjData* obj) {
    s16* fade;

    if (D_8011155C_rockin_raceway != 0) {
        if (D_8011155C_rockin_raceway == 1) {
            obj->func = func_80106A5C_rockin_raceway;
        }
        D_8011155C_rockin_raceway--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8011155C_rockin_raceway = 16;
        fade = &D_8011155E_rockin_raceway;
        WipeCreateOut(0, *fade);
        HuAudSeqFadeOut(*fade);
        func_8004AB0C_main(*fade);
    }
}

void func_80106B28_rockin_raceway(void) {
    RrPath* track;
    omObjData* obj;
    RrRacer* r;
    s32 i;
    s32 j;
    u16 lane;

    D_80111B30_rockin_raceway = HuMemAllocTag(sizeof(RrRacer) * 4, 0x7918);
    D_80111B34_rockin_raceway = -1;
    D_80111B3A_rockin_raceway = 0;
    D_80111B3C_rockin_raceway = HuMemAllocTag(sizeof(RrPose) * 8, 0x7918);
    memset(D_80111B3C_rockin_raceway, 0, sizeof(RrPose) * 8);
    i = 0;
    r = D_80111B30_rockin_raceway;
    for (; i < 4; i++) {
        memset(r, 0, sizeof(RrRacer));
        r->unk00 = i;
        r->unk0A = D_80111562_rockin_raceway[i][0];
        r->unk0C = GwPlayer[r->unk0A].pad;
        r->unk0E = GwPlayer[r->unk0A].chr;
        if (GwPlayer[r->unk0A].stat & 1) {
            r->unk10 = 1;
        } else {
            r->unk10 = 0;
        }
        r->unk12 = GwPlayer[r->unk0A].cpu_difficulty;
        r->unk2E = GwPlayer[r->unk0A].group;
        for (j = 0; j < 4; j++) {
            if (D_80111570_rockin_raceway[r->unk2E] == -1) {
                D_80111570_rockin_raceway[r->unk2E] = r->unk2E;
                break;
            }
            lane = r->unk2E;
            r->unk2E = lane + 1;
            if (r->unk2E >= 4) {
                r->unk2E = lane - 3;
            }
        }
        track = &D_80111B40_rockin_raceway[r->unk2E];
        r->unk30 = track->unk08 - D_80111B44_rockin_raceway;
        if (r->unk30 < 0.0f) {
            r->unk30 = 0.0f;
        }
        func_8010A5E4_rockin_raceway(r->unk2E, r->unk0E);
        r++;
        obj = omAddObj(i + 0x10, 10, 60, -1, func_80106DC8_rockin_raceway);
        D_800EC598_minigame[D_800EC280_minigame] = obj;
        func_8010EC0C_rockin_raceway(obj, &D_80111B30_rockin_raceway[i]);
        D_800EC280_minigame++;
    }
}

void func_80106DC8_rockin_raceway(omObjData* obj) {
    RrRacer* r;
    s32 i;
    s32 level;
    s32 mdl;
    u16 chr;

    r = func_8010EC38_rockin_raceway(obj);
    obj->func = func_801071D8_rockin_raceway;
    chr = r->unk0E;
    obj->model[0] = func_8000B108_main(D_80111580_rockin_raceway[chr] | 0x4D0000, 0x299);
    obj->model[1] = func_8000B108_main(9, 0x299);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            obj->model[3] = func_8000B108_main(D_80111580_rockin_raceway[chr] | 0x4D0000, 0x28D);
            func_8001FA68_main(obj->model[3]);
            func_8001F9E4_main(obj->model[3], 0x40);
            func_8001C514_main(obj->model[3]);
        } else {
            obj->model[3 + i] = Hu3DModelLink(obj->model[3]);
        }
        func_8001C8E4_main(obj->model[3 + i], D_80111590_rockin_raceway[i % 3]);
    }
    switch (r->unk12) {
        case 0:
            level = 0;
            break;
        case 1:
            level = 1;
            break;
        case 2:
            level = 2;
            break;
        default:
            level = 3;
            break;
    }
    r->unk02 = 0;
    r->unk04 = -1;
    r->unk06 = -1;
    r->unk08 = 0;
    r->unk34 = 0;
    r->unk38 = 0.0f;
    r->unk24 = 0.0f;
    r->unk28 = 1.0f;
    r->unk1C = 0;
    r->unk1E = 0;
    r->unk20 = 0;
    r->unk14 = level * 200 + rand16() % 300 + 300;
    r->unk16 = rand16() % 1000;
    if (r->unk14 != 0) {
        r->unk16 %= r->unk14;
    }
    r->unk18 = 0;
    r->unk1A = 0;
    r->unk3C = r->unk40 = r->unk44 = r->unk48 = r->unk54 = 0.0f;
    r->unk58.x = r->unk58.y = r->unk58.z = 0.0f;
    r->unk64.x = r->unk64.y = r->unk64.z = 0.0f;
    r->unk44 = func_8010A258_rockin_raceway(r->unk2E, r->unk30, r->unk44, 0.0f, &r->unk4C, &r->unk50, &r->unk58, &r->unk64);
    obj->model[2] = mdl = func_8000B108_main(0x4D0009, 0x99);
    Hu3DModelPosSet((s16)mdl, r->unk58.x - 69.9999988079071045, r->unk58.y, r->unk58.z);
    func_8001C92C_main((s16)mdl, 0.0f);
    obj->trans.x = r->unk58.x;
    obj->trans.y = r->unk58.y;
    obj->trans.z = r->unk58.z;
    obj->rot.x = r->unk64.x;
    obj->rot.y = r->unk64.y;
    obj->rot.z = r->unk64.z;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
}

void func_801071D8_rockin_raceway(omObjData* obj) {
    RrRacer* r;
    s32 i;
    HmfModel* src;
    HmfModel* dst;
    RrPose* pose;

    r = func_8010EC38_rockin_raceway(obj);
    if (D_80111B3A_rockin_raceway != 0) {
        for (i = 0; i < 2; i++) {
            if (D_80111B3C_rockin_raceway[i].p[r->unk0A].unk02 != 0) {
                func_8001C258_main(obj->model[3 + i], 4, 0);
            } else {
                func_8001C258_main(obj->model[3 + i], 4, 4);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            func_8001C258_main(obj->model[3 + i], 4, 4);
        }
    }
    for (i = 1; i >= 0; i--) {
        if (i != 0) {
            src = &HmfModelData[obj->model[2 + i]];
        } else {
            src = &HmfModelData[obj->model[0]];
        }
        dst = &HmfModelData[obj->model[3 + i]];
        dst->pos.x = src->pos.x;
        dst->pos.y = src->pos.y;
        dst->pos.z = src->pos.z;
        dst->rot.x = src->rot.x;
        dst->rot.y = src->rot.y;
        dst->rot.z = src->rot.z;
        dst->scale.x = src->scale.x;
        dst->scale.y = src->scale.y;
        dst->scale.z = src->scale.z;
    }
    switch (D_80111AD8_rockin_raceway) {
        case 2:
            func_8001C92C_main(obj->model[2], 1.0f);
            if (r->unk10 != 0) {
                func_8010769C_rockin_raceway(obj);
            }
            if (D_80111AE0_rockin_raceway == 0) {
                r->unk38 = 0.0f;
                r->unk24 = 0.0f;
                r->unk28 = 1.0f;
            }
            r->unk38 -= 0.009f;
            if (r->unk38 < 0.01f) {
                r->unk38 = 0.0f;
            }
            if (r->unk38 == 0.0f) {
                r->unk1E = 0xE000;
            } else {
                r->unk24 += 20.0f;
                if (r->unk24 >= 360.0f) {
                    r->unk24 -= 360.0f;
                    func_8004ACE0_main(!(r->unk08 & 1) ? 0x45A : 0x463, r->unk0A);
                    r->unk08++;
                }
            }
            switch (r->unk02) {
                case 0:
                case 2:
                    func_80107958_rockin_raceway(r);
                    if (D_80111AE0_rockin_raceway == 0) {
                        r->unk38 = 0.0f;
                        r->unk24 = 0.0f;
                        r->unk28 = 1.0f;
                    }
                    func_80107A38_rockin_raceway(r);
                    break;
                case 1:
                    func_80107BFC_rockin_raceway(r);
                    break;
            }
            func_8010CB5C_rockin_raceway(r, 0.03f);
            func_80107D04_rockin_raceway(obj);
            break;
        case 3:
        case 4:
        case 6:
            switch (r->unk02) {
                case 0:
                case 2:
                    r->unk38 = func_8010E7C8_rockin_raceway(0.1f, r->unk38, 0.65f);
                    func_80107A38_rockin_raceway(r);
                    r->unk24 += 20.0f;
                    if (r->unk24 >= 360.0f) {
                        r->unk24 -= 360.0f;
                    }
                    break;
                case 1:
                    if (r->unk00 == D_80111B34_rockin_raceway) {
                        r->unk02 = 0;
                        r->unk28 = 1.0f;
                        r->unk24 = 0.0f;
                        r->unk40 = 0.0f;
                    } else {
                        func_80107BFC_rockin_raceway(r);
                    }
                    break;
            }
            if (D_80111AD8_rockin_raceway == 6 && r->unk00 == D_80111B34_rockin_raceway) {
                func_8010CB5C_rockin_raceway(r, 0.1f);
            }
            func_80107D04_rockin_raceway(obj);
            break;
        case 5:
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], 0.6f, 0.6f, 0.6f);
    r->unk34++;
}

void func_8010769C_rockin_raceway(omObjData* obj) {
    RrRacer* r;
    s32 level;
    s32 press;

    press = 0;
    r = func_8010EC38_rockin_raceway(obj);
    switch (r->unk12) {
        case 0:
            level = 0;
            break;
        case 1:
            level = 1;
            break;
        case 2:
            level = 2;
            break;
        default:
            level = 3;
            break;
    }
    switch (func_8010A48C_rockin_raceway(r->unk2E, r->unk4C)) {
        case 1:
            if (r->unk28 >= 0.5f) {
                r->unk1A = 1;
            }
            break;
        case 2:
            r->unk1A = 1;
            break;
    }
    if (r->unk1A == 0) {
        if (r->unk16 < 0 && r->unk02 != 2) {
            if (++r->unk16 == 0) {
                r->unk16 = 0;
            } else {
                D_800D5558_main[r->unk0C] = 0;
                return;
            }
        } else {
            if (D_80111AD0_rockin_raceway > 60) {
                r->unk16 += (rand8() & 3) + 2;
            }
            if (r->unk16 >= r->unk14) {
                r->unk16 = -(rand16() % 30 + 30);
            }
        }
        if (r->unk38 < D_80111300_rockin_raceway[level * 2]) {
            r->unk1A = 1;
        } else if (r->unk02 == 2) {
            r->unk1A = 1;
        } else if (r->unk38 < D_80111300_rockin_raceway[level * 2 + 1] && !(rand8() & 0x3F)) {
            r->unk1A = 1;
        }
        if (r->unk1A == 0) {
            goto end;
        }
    }
    r->unk18++;
    if (r->unk18 > D_80111320_rockin_raceway[level]) {
        r->unk18 = 0;
        r->unk1A = 0;
        press = 1;
    }
end:
    if (press) {
        if (r->unk1E == 0x8000) {
            D_800D5558_main[r->unk0C] = 0x8000;
        } else {
            D_800D5558_main[r->unk0C] = 0x6000;
        }
    }
}

void func_80107958_rockin_raceway(RrRacer* r) {
    if (D_800D5558_main[r->unk0C] & r->unk1E) {
        r->unk38 += D_801112E0_rockin_raceway[r->unk1C] * 0.1f;
        if (r->unk38 >= 1.0f) {
            r->unk38 = 1.0f;
        }
        if (D_800D5558_main[r->unk0C] == 0x8000) {
            r->unk1E = 0x6000;
        } else {
            r->unk1E = 0x8000;
        }
        r->unk28 -= 0.05f;
        if (r->unk28 < 0.0f) {
            r->unk28 = 0.0f;
        }
    }
}

void func_80107A38_rockin_raceway(RrRacer* r) {
    if (r->unk28 <= 0.0f && D_80111AD8_rockin_raceway == 2) {
        r->unk02 = 1;
        func_8004AC98_main(0x458, r->unk0A);
        func_8004AC98_main(0x459, r->unk0A);
        func_8010E344_rockin_raceway(0x286, 3, 3, r->unk0A);
        if (D_80111AD8_rockin_raceway == 2) {
            omVibrate(r->unk0A, 2, 2, 20);
        }
    } else {
        r->unk28 += 0.008f;
        if (r->unk28 > 1.0f) {
            r->unk28 = 1.0f;
        }
    }
    if (r->unk02 == 2) {
        if (!(r->unk34 & 0x1F)) {
            func_80108F8C_rockin_raceway(r->unk58.x + 20.000000298023224, r->unk58.y + 139.9999976158142, r->unk58.z);
        }
        r->unk28 = 1.0f;
        if (--r->unk20 == 0) {
            if (D_80111AD8_rockin_raceway == 2) {
                if (r->unk04 != -1) {
                    HuAudFXStop(r->unk04);
                    r->unk04 = -1;
                }
                if (r->unk06 != -1) {
                    HuAudFXStop(r->unk06);
                    r->unk06 = -1;
                }
            }
            r->unk20 = 0;
            r->unk02 = 0;
        }
    }
}

void func_80107BFC_rockin_raceway(RrRacer* r) {
    r->unk38 = 0.0f;
    if (r->unk28 >= 0.975f) {
        r->unk40 = func_8010E608_rockin_raceway(r->unk38, r->unk40, 30.0f);
        if (func_8010E504_rockin_raceway(0.0f, r->unk40) < 0.5f) {
            r->unk24 = 0.0f;
            r->unk40 = 0.0f;
            r->unk02 = 0;
        }
    } else {
        r->unk40 += 30.0f;
        if (r->unk40 >= 360.0f) {
            r->unk40 -= 360.0f;
        }
        if (r->unk34 & 3) {
            func_801096A0_rockin_raceway(r);
        }
        r->unk28 += 0.025f;
    }
}

void func_80107D04_rockin_raceway(omObjData* obj) {
    HuMtx4F mtx;
    RrRacer* r;
    f32 speed;

    r = func_8010EC38_rockin_raceway(obj);
    speed = r->unk38 * D_801112F0_rockin_raceway[r->unk1C] * 3.0f;
    r->unk3C = sindf(r->unk24) * r->unk38 * 30.0f;
    r->unk44 = func_8010A258_rockin_raceway(r->unk2E, r->unk30, r->unk44, speed, &r->unk4C, &r->unk50, &r->unk58, &r->unk64);
    if (r->unk3C > 0.0f) {
        func_8008A070_main(mtx);
        func_80017D24_main(mtx, r->unk3C, 0.0f, 0.0f);
        func_80017C10_main((Mtx*)mtx, 0.0f, 0.0f, 47.0f);
        r->unk54 = mtx[3][2];
    } else {
        r->unk54 = 47.0f;
    }
    r->unk48 = r->unk44 + r->unk54;
    obj->trans.x = r->unk58.x;
    obj->trans.y = r->unk58.y;
    obj->trans.z = r->unk58.z;
    obj->rot.x = r->unk64.x + r->unk3C;
    obj->rot.y = r->unk64.y + r->unk40;
}

void func_80107E78_rockin_raceway(s32 slot, s16 arg1) {
    omObjData* obj;
    RrRacer* r;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = D_800EC598_minigame[i];
        r = func_8010EC38_rockin_raceway(obj);
        if (D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk02 == 0) {
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk02 = 1;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk00 = arg1;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk04.x = obj->trans.x;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk04.y = obj->trans.y;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk04.z = obj->trans.z;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk10.x = obj->rot.x;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk10.y = obj->rot.y;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk10.z = obj->rot.z;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk1C.x = obj->scale.x;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk1C.y = obj->scale.y;
            D_80111B3C_rockin_raceway[slot].p[r->unk0A].unk1C.z = obj->scale.z;
        }
    }
}

void func_8010803C_rockin_raceway(s32* order) {
    RrRank rank[4];
    RrRank tmp;
    RrRacer* r;
    s32 i;
    s32 j;
    s32 k;
    s32 swap;

    for (i = 0; i < 4; i++) {
        r = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        rank[i].unk00 = i;
        rank[i].unk04 = r->unk4C;
        rank[i].unk08 = r->unk2E;
        rank[i].unk0C = D_800EC598_minigame[i]->trans.x + r->unk54;
        rank[i].unk10 = r->unk50;
        rank[i].unk14 = r->unk48;
    }
    for (i = 0; i < 64; i++) {
        j = rand8() & 3;
        k = rand8() & 3;
        tmp = rank[j];
        rank[j] = rank[k];
        rank[k] = tmp;
    }
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            swap = 0;
            if (rank[i].unk04 >= D_801112C0_rockin_raceway[rank[i].unk08] - 1
                && rank[j].unk04 >= D_801112C0_rockin_raceway[rank[j].unk08] - 1
                && rank[i].unk0C < rank[j].unk0C) {
                swap = 1;
            } else if (rank[i].unk04 < rank[j].unk04) {
                swap = 1;
            } else if (rank[i].unk04 == rank[j].unk04 && rank[i].unk10 < rank[j].unk10) {
                swap = 1;
            }
            if (swap) {
                tmp = rank[i];
                rank[i] = rank[j];
                rank[j] = tmp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        r = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        for (j = 0; j < 4; j++) {
            if (rank[j].unk00 == i) {
                break;
            }
        }
        if (j >= 4) {
            j = 3;
        }
        r->unk1C = j;
    }
    for (i = 0; i < 4; i++) {
        order[i] = ((RrRacer*)func_8010EC38_rockin_raceway(D_800EC598_minigame[rank[i].unk00]))->unk0A;
    }
}

s32 func_80108464_rockin_raceway(void) {
    RrRacer* r;
    s32 i;

    for (i = 0; i < 4; i++) {
        r = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        if (r->unk4C >= D_801112C0_rockin_raceway[r->unk2E] - 1
            && D_800EC598_minigame[i]->trans.x + r->unk54 >= 340.00000953674316) {
            break;
        }
    }
    if (i < 4) {
        for (i = 0; i < 4; i++) {
            if (((RrRacer*)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]))->unk1C == 0) {
                return i;
            }
        }
    }
    return -1;
}

void func_80108578_rockin_raceway(void) {
    Vec rot;
    Vec pos;
    RrItem* item;
    RrRacer* r;
    s32 i;

    D_80111B48_rockin_raceway = item = HuMemAllocTag(sizeof(RrItem) * 8, 0x7918);
    for (i = 0; i < 8; i++, item++) {
        memset(item, 0, sizeof(RrItem));
        if (i == 0) {
            item->unk02 = func_8000B108_main(0x4D0007, 0x99);
            item->unk04 = func_8000B108_main(0x4D0008, 0x99);
        } else {
            item->unk02 = Hu3DModelLink(D_80111B48_rockin_raceway->unk02);
            item->unk04 = Hu3DModelLink(D_80111B48_rockin_raceway->unk04);
        }
        func_8001C258_main(item->unk02, 4, 4);
        func_8001C258_main(item->unk04, 4, 4);
        item->unk0A = 0;
        item->unk06 = 0;
        item->unk00 = 0;
        item->unk0C.x = item->unk0C.y = item->unk0C.z = 0.0f;
        item->unk18.x = item->unk18.y = item->unk18.z = 0.0f;
    }
    for (i = 0, r = D_80111B30_rockin_raceway; i < 4; i++, r++) {
        func_8010A258_rockin_raceway(r->unk2E, r->unk30, 1500.0f, 0.0f, NULL, NULL, &pos, &rot);
        func_80108760_rockin_raceway(&pos, NULL, 90);
        func_80108760_rockin_raceway(&D_80111B40_rockin_raceway[i].unk0C[D_801112D2_rockin_raceway[i].unk00], NULL, 30);
    }
    omSetStatBit(omAddObj(0x1E, 0, 0, -1, func_80108864_rockin_raceway), 0xA0);
}

s32 func_80108760_rockin_raceway(Vec* pos, Vec* vel, s16 time) {
    RrItem* item;
    s32 i;

    for (i = 0, item = D_80111B48_rockin_raceway; i < 8; i++, item++) {
        if (item->unk00 == 0) {
            break;
        }
    }
    if (i >= 8) {
        return -1;
    }
    item->unk00 = 1;
    item->unk08 = time;
    item->unk0A = 0;
    if (pos != NULL) {
        item->unk0C.x = pos->x;
        item->unk0C.y = pos->y;
        item->unk0C.z = pos->z;
    } else {
        item->unk0C.x = item->unk0C.y = item->unk0C.z = 0.0f;
    }
    /* retail reads pos here, not vel (both callers pass NULL) */
    if (vel != NULL) {
        item->unk18.x = pos->x;
        item->unk18.y = pos->y;
        item->unk18.z = pos->z;
    } else {
        item->unk18.x = item->unk18.y = item->unk18.z = 0.0f;
    }
    Hu3DModelPosSet(item->unk02, item->unk0C.x, item->unk0C.y, item->unk0C.z);
    Hu3DModelPosSet(item->unk04, item->unk0C.x, item->unk0C.y, item->unk0C.z);
    return i;
}

void func_80108864_rockin_raceway(omObjData* obj) {
    RrItem* item;
    s32 i;
    s16 on;
    s16 off;

    if (func_80049F98_main() + D_800D6A90_main == 0 && D_80111AD8_rockin_raceway == 2) {
        func_80108BAC_rockin_raceway();
    }
    for (i = 0, item = D_80111B48_rockin_raceway; i < 8; i++, item++) {
        if (item->unk00 == 0) {
            continue;
        }
        if (func_80049F98_main() + D_800D6A90_main == 0 && D_80111AD8_rockin_raceway == 2) {
            if (++item->unk06 >= item->unk08) {
                item->unk06 = 0;
                item->unk0A ^= 1;
            }
        }
        if (item->unk0A & 1) {
            on = item->unk04;
            off = item->unk02;
        } else {
            on = item->unk02;
            off = item->unk04;
        }
        func_8001C258_main(on, 4, 0);
        func_8001C258_main(off, 4, 4);
        item->unk0C.x += item->unk18.x;
        item->unk0C.y += item->unk18.y;
        item->unk0C.z += item->unk18.z;
        Hu3DModelPosSet(on, item->unk0C.x, item->unk0C.y, item->unk0C.z);
        Hu3DModelPosSet(off, item->unk0C.x, item->unk0C.y, item->unk0C.z);
        Hu3DModelScaleSet(on, 1.0f, 1.0f, 1.0f);
        Hu3DModelScaleSet(off, 1.0f, 1.0f, 1.0f);
        if (D_80111AD8_rockin_raceway >= 3) {
            item->unk00 = 0;
            func_8001C258_main(on, 4, 4);
            func_8001C258_main(off, 4, 4);
        }
    }
}

s32 func_80108A80_rockin_raceway(Vec* pos) {
    RrItem* item;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;

    for (i = 0, item = D_80111B48_rockin_raceway; i < 8; i++, item++) {
        if (item->unk00 != 0) {
            dx = item->unk0C.x - pos->x;
            dy = item->unk0C.y - pos->y;
            dz = item->unk0C.z - pos->z;
            if (dx * dx + dy * dy + dz * dz < 3600.0002861023004) {
                func_8001C258_main(item->unk02, 4, 4);
                func_8001C258_main(item->unk04, 4, 4);
                item->unk00 = 0;
                if (D_80111BD4_rockin_raceway == -1 && D_80111BD6_rockin_raceway == -1 && item->unk08 == 30) {
                    D_80111BD6_rockin_raceway = 4;
                }
                break;
            }
        }
    }
    if (i < 8) {
        return item->unk0A;
    }
    return -1;
}

void func_80108BAC_rockin_raceway(void) {
    RrRacer* r;
    s32 i;

    for (i = 0; i < 4; i++) {
        r = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        switch (func_80108A80_rockin_raceway(&r->unk58)) {
            case 0:
                r->unk02 = 2;
                r->unk28 = 1.0f;
                r->unk20 = 300;
                r->unk34 |= 0xE;
                if (D_80111AD8_rockin_raceway == 2) {
                    omVibrate(r->unk0A, 10, 0, 10);
                }
                if (D_80111AD8_rockin_raceway == 2) {
                    if (r->unk04 != -1) {
                        HuAudFXStop(r->unk04);
                        r->unk04 = -1;
                    }
                    if (r->unk06 != -1) {
                        HuAudFXStop(r->unk06);
                        r->unk06 = -1;
                    }
                }
                r->unk04 = func_8004AC98_main(0x46D, r->unk0A);
                r->unk06 = func_8004AC98_main(0x46E, r->unk0A);
                break;
            case 1:
                r->unk02 = 1;
                r->unk28 = 0.0f;
                if (D_80111AD8_rockin_raceway == 2) {
                    if (r->unk04 != -1) {
                        HuAudFXStop(r->unk04);
                        r->unk04 = -1;
                    }
                    if (r->unk06 != -1) {
                        HuAudFXStop(r->unk06);
                        r->unk06 = -1;
                    }
                }
                func_8004AC98_main(0x458, r->unk0A);
                func_8004AC98_main(0x459, r->unk0A);
                func_8010E344_rockin_raceway(0x286, 3, 3, r->unk0A);
                if (D_80111AD8_rockin_raceway == 2) {
                    omVibrate(r->unk0A, 2, 2, 20);
                }
                break;
        }
    }
}

void func_80108D84_rockin_raceway(void) {
    omObjData* obj;
    HmfModel* mdl;
    s32 i;

    obj = omAddObj(0x1D, 13, 0, -1, func_80108ED4_rockin_raceway);
    D_80111B4C_rockin_raceway = obj;
    obj->model[0] = -1;
    for (i = 1; i < 13; i++) {
        obj->model[i] = func_8000B108_main(0x1001F, 0x899);
        func_8001C2FC_main(obj->model[i], 0x600, 0x400);
        Hu3DModelScaleSet(obj->model[i], 1.0f, 1.0f, 1.0f);
        mdl = &HmfModelData[obj->model[i]];
        mdl->unk40 = 0.0f;
        mdl->unk44 = 1.0f;
        func_8001C258_main(obj->model[i], 4, 4);
    }
    D_80111B50_rockin_raceway = HuMemAllocTag(sizeof(RrSmokeSave) * 12, 0x7918);
    memset(D_80111B50_rockin_raceway, 0, sizeof(RrSmokeSave) * 12);
    D_80111B54_rockin_raceway = 0;
}

void func_80108ED4_rockin_raceway(omObjData* obj) {
    HmfModel* mdl;
    s32 i;

    if (D_80111B54_rockin_raceway == 0) {
        for (i = 1; i < 13; i++) {
            if (obj->model[i] != -1) {
                mdl = &HmfModelData[obj->model[i]];
                if (!(mdl->unk18 & 4) && D_800CCF58_main[mdl->unk02].unk02 <= mdl->unk40) {
                    mdl->unk18 |= 4;
                    mdl->unk40 = 0.0f;
                }
            }
        }
    }
}

void func_80108F8C_rockin_raceway(f32 x, f32 y, f32 z) {
    omObjData* obj;
    HmfModel* mdl;
    s32 i;

    obj = D_80111B4C_rockin_raceway;
    for (i = 1; i < 13; i++) {
        if (obj->model[i] != -1) {
            mdl = &HmfModelData[obj->model[i]];
            if (mdl->unk18 & 4) {
                mdl->pos.x = x;
                mdl->pos.y = y;
                mdl->pos.z = z;
                mdl->rot.x = CRot.x;
                mdl->rot.y = CRot.y;
                mdl->rot.z = CRot.z;
                mdl->unk18 &= ~4;
                mdl->unk40 = 0.0f;
                mdl->unk44 = 1.5f;
                return;
            }
        }
    }
}

void func_80109044_rockin_raceway(void) {
    omObjData* obj;
    RrSmokeSave* save;
    HmfModel* mdl;
    s32 i;

    obj = D_80111B4C_rockin_raceway;
    save = D_80111B50_rockin_raceway;
    if (D_80111B54_rockin_raceway == 0) {
        for (i = 1; i < 13; i++, save++) {
            if (obj->model[i] != -1) {
                mdl = &HmfModelData[obj->model[i]];
                save->unk00 = mdl->unk18;
                save->unk04 = mdl->unk40;
                save->unk08 = mdl->unk44;
                save->unk0C.x = mdl->pos.x;
                save->unk0C.y = mdl->pos.y;
                save->unk0C.z = mdl->pos.z;
                save->unk18.x = mdl->rot.x;
                save->unk18.y = mdl->rot.y;
                save->unk18.z = mdl->rot.z;
                save->unk24.x = mdl->scale.x;
                save->unk24.y = mdl->scale.y;
                save->unk24.z = mdl->scale.z;
                mdl->unk18 |= 4;
                mdl->unk40 = mdl->unk44 = 0.0f;
            }
        }
        D_80111B54_rockin_raceway = 1;
    }
}

void func_80109134_rockin_raceway(void) {
    omObjData* obj;
    RrSmokeSave* save;
    HmfModel* mdl;
    s32 i;

    obj = D_80111B4C_rockin_raceway;
    save = D_80111B50_rockin_raceway;
    if (D_80111B54_rockin_raceway != 0) {
        for (i = 1; i < 13; i++, save++) {
            if (obj->model[i] != -1) {
                mdl = &HmfModelData[obj->model[i]];
                mdl->unk18 = save->unk00;
                mdl->unk40 = save->unk04;
                mdl->unk44 = save->unk08;
                mdl->pos.x = save->unk0C.x;
                mdl->pos.y = save->unk0C.y;
                mdl->pos.z = save->unk0C.z;
                mdl->rot.x = save->unk18.x;
                mdl->rot.y = save->unk18.y;
                mdl->rot.z = save->unk18.z;
                mdl->scale.x = save->unk24.x;
                mdl->scale.y = save->unk24.y;
                mdl->scale.z = save->unk24.z;
            }
        }
        D_80111B54_rockin_raceway = 0;
    }
}

void func_80109208_rockin_raceway(void) {
    HmfModel* mdl;
    HuSprite_Unk84_Struct* spr;
    RrEffect* fx;
    s32 i;

    D_80111B68_rockin_raceway->unk04 = func_8010A4C0_rockin_raceway(11);
    spr = func_80055194_main(D_80111B68_rockin_raceway->unk04);
    D_80111B58_rockin_raceway = omAddObj(0x1C, 0, 0, -1, func_80109384_rockin_raceway);
    D_80111B5C_rockin_raceway = fx = HuMemAllocTag(sizeof(RrEffect) * 16, 0x7918);
    for (i = 0; i < 16; i++, fx++) {
        if (i == 0) {
            fx->unk02 = func_8010EC8C_rockin_raceway(spr, &D_801114D4_rockin_raceway);
        } else {
            fx->unk02 = func_8010F874_rockin_raceway(spr, D_80111B5C_rockin_raceway->unk02, &D_801114D4_rockin_raceway);
        }
        fx->unk00 = 0;
        fx->unk04 = fx->unk08 = 0.0f;
        fx->unk0C.x = fx->unk0C.y = fx->unk0C.z = 0.0f;
        fx->unk18.x = fx->unk18.y = fx->unk18.z = 0.0f;
        fx->unk24.x = fx->unk24.y = fx->unk24.z = 0.0f;
        func_8001C258_main(fx->unk02, 4, 4);
        mdl = &HmfModelData[fx->unk02];
        mdl->unk40 = 0.0f;
    }
    D_80111B60_rockin_raceway = HuMemAllocTag(0x340, 0x7918);
    memset(D_80111B60_rockin_raceway, 0, 0x340);
    D_80111B64_rockin_raceway = 0;
}

void func_80109384_rockin_raceway(omObjData* obj) {
    HuSprite_Unk84_Struct* spr;
    RrEffect* fx;
    HmfModel* mdl;
    s32 i;

    if (D_80111B64_rockin_raceway == 0) {
        spr = func_80055194_main(D_80111B68_rockin_raceway->unk04);
        for (i = 0, fx = D_80111B5C_rockin_raceway; i < 16; i++, fx++) {
            if (fx->unk00 == 0) {
                continue;
            }
            mdl = &HmfModelData[fx->unk02];
            if (mdl->unk18 & 4) {
                continue;
            }
            fx->unk0C.x += fx->unk18.x;
            fx->unk0C.y += fx->unk18.y;
            fx->unk0C.z += fx->unk18.z;
            mdl->pos.x = fx->unk0C.x;
            mdl->pos.y = fx->unk0C.y;
            mdl->pos.z = fx->unk0C.z;
            mdl->scale.x = fx->unk24.x;
            mdl->scale.y = fx->unk24.y;
            mdl->scale.z = fx->unk24.z;
            func_8010FA78_rockin_raceway(fx->unk02, spr, (s32)fx->unk04, &D_801114D4_rockin_raceway);
            fx->unk04 += fx->unk08;
            if ((s32)fx->unk04 >= spr->unk10) {
                fx->unk00 = 0;
                fx->unk04 = 0.0f;
                mdl->unk18 |= 4;
            }
        }
    }
}

s32 func_801094EC_rockin_raceway(Vec* pos, Vec* vel, Vec* scale, f32 speed) {
    HuSprite_Unk84_Struct* spr;
    RrEffect* fx;
    HmfModel* mdl;
    s32 i;

    spr = func_80055194_main(D_80111B68_rockin_raceway->unk04);
    for (i = 0, fx = D_80111B5C_rockin_raceway; i < 16; i++, fx++) {
        if (fx->unk00 != 0) {
            continue;
        }
        fx->unk00 = 1;
        mdl = &HmfModelData[fx->unk02];
        if (pos != NULL) {
            fx->unk0C.x = pos->x;
            fx->unk0C.y = pos->y;
            fx->unk0C.z = pos->z;
        } else {
            fx->unk0C.x = fx->unk0C.y = fx->unk0C.z = 0.0f;
        }
        if (vel != NULL) {
            fx->unk18.x = vel->x;
            fx->unk18.y = vel->y;
            fx->unk18.z = vel->z;
        } else {
            fx->unk18.x = fx->unk18.y = fx->unk18.z = 0.0f;
        }
        if (scale != NULL) {
            fx->unk24.x = scale->x;
            fx->unk24.y = scale->y;
            fx->unk24.z = scale->z;
        } else {
            fx->unk24.x = fx->unk24.y = fx->unk24.z = 1.0f;
        }
        fx->unk08 = speed;
        fx->unk04 = 0.0f;
        func_8010FA78_rockin_raceway(fx->unk02, spr, 0, &D_801114D4_rockin_raceway);
        func_8001C258_main(fx->unk02, 4, 0);
        mdl->unk40 = 0.0f;
        mdl->pos.x = fx->unk0C.x;
        mdl->pos.y = fx->unk0C.y;
        mdl->pos.z = fx->unk0C.z;
        mdl->scale.x = fx->unk24.x;
        mdl->scale.y = fx->unk24.y;
        mdl->scale.z = fx->unk24.z;
        return i;
    }
    return -1;
}


void func_801096A0_rockin_raceway(RrRacer *kart) {
    Vec pos;
    Vec vel;
    Vec scale;

    pos.x = kart->unk58.x;
    pos.z = kart->unk58.z;
    pos.y = kart->unk58.y + 200.0 * 0.1f;
    vel.x = -(sindf(kart->unk64.y + kart->unk40) * 100.0 * 0.1f);
    vel.z = -(cosdf(kart->unk64.y + kart->unk40) * 100.0 * 0.1f);
    vel.y = 1.0f;
    scale.x = scale.y = scale.z = 0.25f;
    func_801094EC_rockin_raceway(&pos, &vel, &scale, 1.0f);
}

void func_801097A0_rockin_raceway(void) {
    RrMdlSave *save;
    RrEffect *anim;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway == 0) {
        save = D_80111B60_rockin_raceway;
        anim = D_80111B5C_rockin_raceway;
        for (i = 0; i < 16; i++, anim++, save++) {
            if (anim->unk02 != -1) {
                model = &HmfModelData[anim->unk02];
                save->unk00 = anim->unk00;
                save->unk02 = model->unk40;
                save->unk04 = model->unk18;
                save->unk08 = anim->unk04;
                save->unk0C = anim->unk08;
                save->pos.x = model->pos.x;
                save->pos.y = model->pos.y;
                save->pos.z = model->pos.z;
                save->rot.x = model->rot.x;
                save->rot.y = model->rot.y;
                save->rot.z = model->rot.z;
                save->scale.x = model->scale.x;
                save->scale.y = model->scale.y;
                save->scale.z = model->scale.z;
                anim->unk00 = 0;
                model->unk18 |= 4;
                model->unk40 = 0.0f;
            }
        }
        D_80111B64_rockin_raceway = 1;
    }
}

void func_801098D8_rockin_raceway(void) {
    RrMdlSave *save;
    RrEffect *anim;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway != 0) {
        save = D_80111B60_rockin_raceway;
        anim = D_80111B5C_rockin_raceway;
        for (i = 0; i < 16; i++, anim++, save++) {
            if (anim->unk02 != -1) {
                model = &HmfModelData[anim->unk02];
                anim->unk00 = save->unk00;
                model->unk18 = save->unk04;
                anim->unk04 = save->unk08;
                anim->unk08 = save->unk0C;
                model->pos.x = save->pos.x;
                model->pos.y = save->pos.y;
                model->pos.z = save->pos.z;
                model->rot.x = save->rot.x;
                model->rot.y = save->rot.y;
                model->rot.z = save->rot.z;
                model->scale.x = save->scale.x;
                model->scale.y = save->scale.y;
                model->scale.z = save->scale.z;
            }
        }
        D_80111B64_rockin_raceway = 0;
    }
}

void func_801099AC_rockin_raceway(void) {
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = omAddObj(1, 24, 0, -1, func_80109A04_rockin_raceway);
}

void func_80109A04_rockin_raceway(omObjData *obj) {
    s32 i;
    s16 grp;

    obj->func = (omObjFunc)func_80109CF8_rockin_raceway;
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->model[0] = func_8000B0A0_main(0x4D0000, 0x99);
    obj->model[1] = func_8000B0A0_main(0x4D000A, 0xB9);
    obj->model[2] = func_8000B0A0_main(0x4D000B, 0xB9);
    D_80111B68_rockin_raceway->unk06 = func_8010A4C0_rockin_raceway(0x4D0010);
    D_80111B68_rockin_raceway->unk08 = func_8010A4C0_rockin_raceway(0x4D0011);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            obj->model[3] = func_8010FFB8_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk06), D_801114D8_rockin_raceway);
        } else {
            obj->model[3 + i] = func_8010F874_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk06), obj->model[3], &D_801115B4_rockin_raceway);
        }
    }
    for (i = 0; i < 12; i++) {
        if (i == 0) {
            obj->model[7] = func_8010FFB8_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk08), D_80111518_rockin_raceway);
        } else {
            obj->model[7 + i] = func_8010F874_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway->unk08), obj->model[7], &D_801115B4_rockin_raceway);
        }
    }
    func_80110C38_rockin_raceway(&obj->model[3], func_80055194_main(D_80111B68_rockin_raceway->unk06), D_8011159C_rockin_raceway);
    D_801115AC_rockin_raceway[1] = D_80111AE8_rockin_raceway;
    func_8010B5DC_rockin_raceway(D_801115AC_rockin_raceway);
    func_80110D90_rockin_raceway(&obj->model[7], func_80055194_main(D_80111B68_rockin_raceway->unk08), D_801115AC_rockin_raceway);
    D_80111B68_rockin_raceway->unk00 = func_8010A4C0_rockin_raceway(0x4D000E);
    grp = HuSprGrpCreate(1, 0);
    func_80055024_main(grp, 0, D_80111B68_rockin_raceway->unk00, 0);
    HuSprAttrSet(grp, 0, 0x4000);
    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    func_80054904_main(grp, 0, 160, 120);
    HuSprPriSet(grp, 0, 0xFFFF);
    func_800550F4_main(grp, 0, 0);
    WipeCreateIn(0xFF, 16);
}

void func_80109CF8_rockin_raceway(void) {
}

void func_80109D00_rockin_raceway(s32 *arg0) {
    omObjData *obj = D_800EC1C0_minigame[0];

    func_80110C38_rockin_raceway(&obj->model[3], func_80055194_main(D_80111B68_rockin_raceway->unk06), arg0);
}

void func_80109D54_rockin_raceway(s32 *times) {
    omObjData *obj = D_800EC1C0_minigame[0];

    func_80110D90_rockin_raceway(&obj->model[7], func_80055194_main(D_80111B68_rockin_raceway->unk08), times);
}

void func_80109DA8_rockin_raceway(void) {
    Vec rot;
    RrPath *path;
    s32 i;
    s32 j;
    s32 next;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 len;

    D_80111B40_rockin_raceway = HuMemAllocTag(sizeof(RrPath) * 4, 0x7918);
    for (i = 0, path = D_80111B40_rockin_raceway; i < 4; i++, path++) {
        path->unk00 = i;
        path->unk04 = path->unk08 = 0.0f;
        path->unk0C = D_801112A0_rockin_raceway[i];
        path->unk02 = D_801112B0_rockin_raceway[i];
        path->unk0C[D_801112C0_rockin_raceway[i]].x = 340.0f;
        path->unk10 = HuMemAllocTag(path->unk02 * sizeof(Vec), 0x7918);
        path->unk14 = HuMemAllocTag(path->unk02 * sizeof(f32), 0x7918);
        path->unk18 = HuMemAllocTag((path->unk02 + 1) * sizeof(f32), 0x7918);
        path->unk1C = HuMemAllocTag(path->unk02 * sizeof(Vec), 0x7918);
        path->unk20 = HuMemAllocTag(path->unk02 * sizeof(u16), 0x7918);
        memset(path->unk20, 0, 4);
        for (j = 0; j < 5; j++) {
            next = (rand8() & 0xFF) % D_801112C0_rockin_raceway[i];
            path->unk20[next] = 1;
        }
        for (j = 0; j < 3; j++) {
            next = (rand8() & 0xFF) % D_801112C0_rockin_raceway[i];
            path->unk20[next] = 2;
        }
        len = 0.0f;
        for (j = 0; j < path->unk02; j++) {
            next = (j + 1) % path->unk02;
            dx = path->unk0C[next].x - path->unk0C[j].x;
            dy = path->unk0C[next].y - path->unk0C[j].y;
            dz = path->unk0C[next].z - path->unk0C[j].z;
            path->unk14[j] = sqrtf(dx * dx + dy * dy + dz * dz);
            path->unk18[j] = len;
            len += path->unk14[j];
            if (j < D_801112C0_rockin_raceway[i]) {
                path->unk08 = len;
            }
            path->unk10[j].x = path->unk0C[j].x + dx * 0.5f;
            path->unk10[j].y = path->unk0C[j].y + dy * 0.5f;
            path->unk10[j].z = path->unk0C[j].z + dz * 0.5f;
            func_8010E994_rockin_raceway(0.0f, &path->unk0C[j], &path->unk10[j], &path->unk0C[next], &rot);
            func_8010EB84_rockin_raceway(&rot, (f32*)&path->unk1C[j]);
        }
        path->unk18[j] = len;
        path->unk04 = len - path->unk14[j - 1];
    }
    D_80111B44_rockin_raceway = D_80111B40_rockin_raceway[0].unk08;
    for (i = 1, path = &D_80111B40_rockin_raceway[1]; i < 4; i++, path++) {
        if (D_80111B44_rockin_raceway > path->unk08) {
            D_80111B44_rockin_raceway = path->unk08;
        }
    }
}

#ifdef NON_MATCHING
f32 func_8010A258_rockin_raceway(u16 idx, f32 dist, f32 base, f32 delta, u16 *seg, f32 *frac, Vec *pos, Vec *rot) {
    RrPath *path = &D_80111B40_rockin_raceway[idx];
    f32 start;
    f32 d;
    f32 rem;
    f32 t;
    s32 i;

    s32 next;
    s32 cur;

    start = base + delta;
    if (path->unk04 <= start) {
        start = path->unk04;
    } else if (start <= 0.0f) {
        start = 0.0f;
    }
    d = start + dist;
    if (path->unk04 <= d) {
        d = path->unk04;
    } else if (d <= 0.0f) {
        d = 0.0f;
    }
    rem = d;
    for (i = 0; i < path->unk02; i++) {
        if (d <= path->unk18[i + 1]) {
            break;
        }
        rem = d - path->unk18[i + 1];
    }
    if (path->unk02 - 1 < i) {
        i = path->unk02 - 1;
    }
    if (seg != NULL) {
        *seg = i;
    }
    if (rem != 0.0f && path->unk14[i] != 0.0f) {
        t = rem / path->unk14[i];
    } else {
        t = 0.0f;
    }
    if (frac != NULL) {
        *frac = t;
    }
    cur = i;
    next = 0;
    if (i < path->unk02 - 1) {
        next = i + 1;
    }

    func_8010E8A0_rockin_raceway(t, &path->unk0C[cur], &path->unk10[cur], &path->unk0C[next], pos);
    rot->x = func_8010E7E0_rockin_raceway(t, path->unk1C[cur].x, path->unk1C[next].x);
    rot->y = func_8010E7E0_rockin_raceway(t, path->unk1C[cur].y, path->unk1C[next].y);
    return start;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A258_rockin_raceway);
#endif

s32 func_8010A48C_rockin_raceway(u16 idx, u16 pt) {
    RrPath *path = &D_80111B40_rockin_raceway[idx];

    return path->unk20[pt];
}

u16 func_8010A4C0_rockin_raceway(s32 file) {
    void *data;
    s16 spr;

    data = DataRead(file);
    spr = func_80055810_main(data);
    DataClose(data);
    return spr;
}

void func_8010A504_rockin_raceway(void) {
    s32 grp;

    D_80111B68_rockin_raceway->unk02 = func_8010A4C0_rockin_raceway(0x4D000F);
    D_80111B68_rockin_raceway->unk0A = func_8010A4C0_rockin_raceway(0x4D0012);
    D_80111B68_rockin_raceway->unk10 = func_8010A4C0_rockin_raceway(0x4D0013);
    grp = HuSprGrpCreate(1, 0);
    D_80111B74_rockin_raceway = grp;
    func_80054904_main(grp, 0, 160, 60);
    func_80055024_main(grp, 0, D_80111B68_rockin_raceway->unk0A, 0);
    func_800550F4_main(grp, 0, 0);
    func_80054FF8_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x9000);
}

void func_8010A5E4_rockin_raceway(s16 player, s16 kind) {
    s32 spr;
    s32 x;
    s32 y;
    s32 grp;
    s32 i;
    s32 off;


    spr = func_8010A4C0_rockin_raceway(D_801115B8_rockin_raceway[kind]);
    x = D_80111330_rockin_raceway[player][0];
    y = D_80111330_rockin_raceway[player][1];
    D_80111B6C_rockin_raceway[player] = grp = HuSprGrpCreate(7, 0);
    D_80111B80_rockin_raceway[player].unk00 = player;
    D_80111B80_rockin_raceway[player].unk08 = y;
    D_80111B80_rockin_raceway[player].unk04 = 0;
    D_80111B80_rockin_raceway[player].unk02 = 0;
    if (player & 1) {
        D_80111B80_rockin_raceway[player].unk06 = x - 4;
    } else {
        D_80111B80_rockin_raceway[player].unk06 = x + 46;
    }
    for (i = 0; i < 5; i++) {
        if (player & 1) {
            D_80111B80_rockin_raceway[player].unk0A[i] = x + (s16)(i * 8 - 20) - D_80111B80_rockin_raceway[player].unk06;
        } else {
            D_80111B80_rockin_raceway[player].unk0A[i] = x + (s16)(i * 8 + 30) - D_80111B80_rockin_raceway[player].unk06;
        }
    }
    for (i = 0; i < 7; i++) {
        if (i == 0) {
            if (player & 1) {
                func_80054904_main(grp, i, x - 42, y);
            } else {
                func_80054904_main(grp, i, x + 8, y);
            }
            func_80055024_main(grp, i, spr, 0);
        } else if (i == 6) {
            if (player & 1) {
                func_80054904_main(grp, i, x - 55, y);
            } else {
                func_80054904_main(grp, i, x - 5, y);
            }
            func_80055024_main(grp, i, D_80111B68_rockin_raceway->unk10, 0);
            func_80055484_main(grp, i, 0, 0, 0, 0xA0);
        } else {
            if (player & 1) {
                func_80054904_main(grp, i, x - 20, y);
            } else {
                func_80054904_main(grp, i, x + 30, y);
            }
            func_80055024_main(grp, i, D_80111B68_rockin_raceway->unk02, 0);
            x += 8;
        }
        func_800550F4_main(grp, i, 0);
        func_80054FF8_main(grp, i, 0);
        HuSprAttrSet(grp, i, 0x1000);
        if (i != 6) {
            HuSprPriSet(grp, i, -16 - i);
        } else {
            HuSprPriSet(grp, i, 0xFFFF);
        }
    }
    omSetStatBit(omAddObj(20, 0, 0, -1, func_8010A990_rockin_raceway), 0xA0);
}

void func_8010A990_rockin_raceway(omObjData *obj) {
    RrRacer *kart;
    s32 i;

    if (D_80111AD8_rockin_raceway == 5 && (D_80111ADC_rockin_raceway > 0 || D_80111AD0_rockin_raceway >= 2)) {
        HuSprAttrReset(D_80111B74_rockin_raceway, 0, 0x8000);
    } else {
        HuSprAttrSet(D_80111B74_rockin_raceway, 0, 0x8000);
    }
    if (D_80111AD8_rockin_raceway < 3) {
        for (i = 0, kart = D_80111B30_rockin_raceway; i < 4; i++, kart++) {
            func_8010AAAC_rockin_raceway(kart->unk2E, kart->unk28 * 100.0f, kart->unk02);
        }
    } else {
        for (i = 0; i < 4; i++) {
            func_8010AAAC_rockin_raceway(i, 0, 0xFFFF);
        }
    }
}

void func_8010AAAC_rockin_raceway(s16 player, s16 value, u16 mode) {
    u16 grp;
    f32 scale;
    f32 x;
    s32 i;
    s32 j;

    grp = D_80111B6C_rockin_raceway[player];
    if (mode == 2) {
        if (D_80111B80_rockin_raceway[player].unk02++ > 30.0f) {
            D_80111B80_rockin_raceway[player].unk02 = 30;
        }
        scale = D_80111B80_rockin_raceway[player].unk02 / 30.0f;
        scale = func_8010E840_rockin_raceway(scale, 0.0f, 1.0f, 0.4f) + 1.0;
    } else {
        if (D_80111B80_rockin_raceway[player].unk02-- < 0) {
            D_80111B80_rockin_raceway[player].unk02 = 0;
        }
        scale = D_80111B80_rockin_raceway[player].unk02 / 30.0f;
        scale = scale * 0.4f + 1.0;
    }
    if (D_80111B80_rockin_raceway[player].unk02 != D_80111B80_rockin_raceway[player].unk04) {
        for (i = 0; i < 5; i++) {
            x = D_80111B80_rockin_raceway[player].unk06 + D_80111B80_rockin_raceway[player].unk0A[i] * scale;
            HuSprScaleSet(grp, i + 1, scale, scale);
            func_80054904_main(grp, i + 1, x, D_80111B80_rockin_raceway[player].unk08);
            if (mode == 2) {
                HuSprAttrSet(grp, i + 1, 0x838);
            } else {
                HuSprAttrReset(grp, i + 1, 0x838);
            }
        }
        D_80111B80_rockin_raceway[player].unk04 = D_80111B80_rockin_raceway[player].unk02;
    }
    switch (mode) {
    case 1:
        if ((D_80111AD0_rockin_raceway & 1) && func_80049F98_main() + D_800D6A90_main == 0) {
            HuSprAttrSet(grp, 0, 0x8000);
        } else {
            HuSprAttrReset(grp, 0, 0x8000);
        }
        break;
    case 2:
        HuSprAttrReset(grp, 0, 0x8000);
        if (!(D_80111AD0_rockin_raceway & 3)) {
            for (i = 0; i < 5; i++) {
                HuSprAttrReset(grp, i + 1, 0x8000);
                func_80054FF8_main(grp, i + 1, 1);
                func_80055458_main(grp, i + 1, 0x100);
            }
        } else {
            for (i = 0; i < 5; i++) {
                HuSprAttrReset(grp, i + 1, 0x8000);
                func_80054FF8_main(grp, i + 1, 0);
                func_80055458_main(grp, i + 1, 0x100);
            }
        }
        return;
    case 0xFFFF:
        for (i = 0; i < 7; i++) {
            HuSprAttrSet(grp, i, 0x8000);
        }
        return;
    default:
        HuSprAttrReset(grp, 0, 0x8000);
        break;
    }
    for (i = 0; i < 5; i++) {
        if (i * 20 < value) {
            j = i + 1;
            HuSprAttrReset(grp, j, 0x8000);
            if (value >= j * 20) {
                func_80055458_main(grp, j, 0x100);
                func_80054FF8_main(grp, j, 0);
            } else {
                func_80055458_main(grp, i + 1, (s16)(value % 20) * 0.05f * 256.0f);
                func_80054FF8_main(grp, i + 1, 0);
            }
        } else {
            HuSprAttrSet(grp, i + 1, 0x8000);
        }
    }
}

void func_8010B124_rockin_raceway(void) {
    s32 grp;
    s32 i;
    s32 j;

    D_80111B68_rockin_raceway->unk0C[0] = func_8010A4C0_rockin_raceway(0x31);
    D_80111B68_rockin_raceway->unk0C[1] = func_8010A4C0_rockin_raceway(0x32);
    D_80111B7A_rockin_raceway = 0;
    for (i = 0; i < 2; i++) {
        D_80111B76_rockin_raceway[i] = grp = HuSprGrpCreate(8, 0);
        for (j = 0; j < 8; j++) {
            func_80054904_main(grp, j, D_80111340_rockin_raceway[j], i * 12 + 28);
            func_80055024_main(grp, j, D_80111B68_rockin_raceway->unk0C[i], 0);
            func_80054FF8_main(grp, j, 0);
            HuSprAttrSet(grp, j, 0x1000);
            func_800550F4_main(grp, j, 0);
        }
        func_80054FF8_main(grp, 2, 10);
        func_80054FF8_main(grp, 5, 11);
    }
}

void func_8010B2B8_rockin_raceway(void) {
    f32 scale;
    u16 grp;
    s32 *digits;
    s32 i;
    s32 j;

    scale = 1.0f;
    if (D_80111AD8_rockin_raceway == 5) {
        for (i = 0; i < 2; i++) {
            grp = D_80111B76_rockin_raceway[i];
            for (j = 0; j < 8; j++) {
                HuSprAttrSet(grp, j, 0x8000);
            }
        }
        return;
    }
    digits = D_80111B00_rockin_raceway;
    for (i = 0; i < 2; i++) {
        grp = D_80111B76_rockin_raceway[i];
        for (j = 0; j < 8; j++) {
            HuSprAttrReset(grp, j, 0x8000);
        }
    }
    if (D_80111B7A_rockin_raceway != 0) {
        scale = sindf(D_80111B7A_rockin_raceway / 15.0f * 180.0f) + 1.0f;
        if (--D_80111B7A_rockin_raceway == 1) {
            scale = 1.0f;
        }
    }
    for (i = 0; i < 2; i++) {
        grp = D_80111B76_rockin_raceway[i];
        for (j = 0; j < 6; j++) {
            if (digits[i * 6 + j] >= 10) {
                digits[i * 6 + j] = 9;
            } else if (digits[i * 6 + j] < 0) {
                digits[i * 6 + j] = 0;
            }
            func_80054FF8_main(grp, D_801115D8_rockin_raceway[j], (s16)digits[i * 6 + j]);
        }
        if ((D_80111B7A_rockin_raceway != 0) & (i == 1)) {
            for (j = 0; j < 8; j++) {
                func_80054904_main(grp, j, (D_80111340_rockin_raceway[j] - 156) * scale + 156.0f, i * 12 + 28);
                HuSprScaleSet(grp, j, scale, scale);
            }
        }
    }
}

#ifdef NON_MATCHING
void func_8010B5DC_rockin_raceway(s32 *times) {
    s32 parts[3];
    s32 *digit;
    s32 *digits;
    s32 i;

    digits = D_80111B00_rockin_raceway;
    for (i = 0; i < 2; i++) {
        parts[0] = times[i] / 1800;
        times[i] -= parts[0] * 1800;
        parts[1] = times[i] / 30;
        times[i] -= parts[1] * 30;
        parts[2] = times[i] / 30.0f * 99.0f;
        digit = &digits[i * 6];
        digit[0] = parts[0] / 10;
        digit[1] = parts[0] - digit[0] * 10;
        digit[2] = parts[1] / 10;
        digit[3] = parts[1] - digit[2] * 10;
        digit[4] = parts[2] / 10;
        digit[5] = parts[2] - digit[4] * 10;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B5DC_rockin_raceway);
#endif

void func_8010B774_rockin_raceway(void) {
    HuCamera *cam;
    s32 i;

    Center.x = D_80111350_rockin_raceway.center.x;
    Center.y = D_80111350_rockin_raceway.center.y;
    Center.z = D_80111350_rockin_raceway.center.z;
    CRot.x = D_80111350_rockin_raceway.rot.x;
    CRot.y = D_80111350_rockin_raceway.rot.y;
    CRot.z = D_80111350_rockin_raceway.rot.z;
    CZoom = D_80111350_rockin_raceway.zoom;
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2E_rockin_raceway = 0;
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010C0D8_rockin_raceway);
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

void func_8010B89C_rockin_raceway(void) {
    RrCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_801115F0_rockin_raceway) {
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
            func_8010C7CC_rockin_raceway(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
        }
        sprintf(D_800D5218_main, "CAMERA TEST_MODE");
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 80, D_800D5218_main);
        sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 88, D_800D5218_main);
        sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 96, D_800D5218_main);
        sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 104, D_800D5218_main);
        D_800EBE24_minigame = 0;
        break;
    case 2:
        if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
            D_801115F4_rockin_raceway++;
        }
        if (D_800CDA7C_main[0] & 0x202) {
            D_801115F4_rockin_raceway--;
        }
        if (D_800CDA7C_main[0] & 0x404) {
            D_801115F8_rockin_raceway++;
        }
        if (D_800CDA7C_main[0] & 0x808) {
            D_801115F8_rockin_raceway--;
        }
        fontcolor = 8;
        sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 80, D_800D5218_main);
        sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 88, D_800D5218_main);
        sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 96, D_800D5218_main);
        sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
        print8((u16)D_801115F4_rockin_raceway + 20, (u16)D_801115F8_rockin_raceway + 104, D_800D5218_main);
        break;
    default:
        D_800EBE24_minigame = 1;
        break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_801115F0_rockin_raceway & 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (++D_801115F0_rockin_raceway >= 3) {
            D_801115F0_rockin_raceway = 0;
        }
    }
}

void func_8010C0D8_rockin_raceway(omObjData *obj) {
    f32 t;

    if (D_80111C2A_rockin_raceway <= 0) {
        func_8010D134_rockin_raceway(0);
        D_80111C2C_rockin_raceway = 0;
        return;
    }
    if (D_80111C28_rockin_raceway == 0) {
        Center.x = D_80111BE0_rockin_raceway[0].center.x;
        Center.y = D_80111BE0_rockin_raceway[0].center.y;
        Center.z = D_80111BE0_rockin_raceway[0].center.z;
        CRot.x = D_80111BE0_rockin_raceway[0].rot.x;
        CRot.y = D_80111BE0_rockin_raceway[0].rot.y;
        CRot.z = D_80111BE0_rockin_raceway[0].rot.z;
        CZoom = D_80111BE0_rockin_raceway[0].zoom;
        RR_WRAP(CRot.x);
        RR_WRAP(CRot.y);
        RR_WRAP(CRot.z);
        D_80111C2A_rockin_raceway = 0;
    } else {
        switch (D_80111C2E_rockin_raceway) {
        case 0:
            t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
            break;
        case 1:
            t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
            t = sindf(t * 90.0f);
            break;
        default:
            t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
            t = sindf(t * 90.0f);
            t = t * t;
            break;
        }
        Center.x = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.x, D_80111BE0_rockin_raceway[1].center.x);
        Center.y = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.y, D_80111BE0_rockin_raceway[1].center.y);
        Center.z = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.z, D_80111BE0_rockin_raceway[1].center.z);
        CRot.x = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.x, D_80111BE0_rockin_raceway[1].rot.x);
        CRot.y = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.y, D_80111BE0_rockin_raceway[1].rot.y);
        CRot.z = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.z, D_80111BE0_rockin_raceway[1].rot.z);
        CZoom = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].zoom, D_80111BE0_rockin_raceway[1].zoom);
        RR_WRAP(CRot.x);
        RR_WRAP(CRot.y);
        RR_WRAP(CRot.z);
        if (D_80111C28_rockin_raceway > 0) {
            D_80111C28_rockin_raceway--;
        } else {
            D_80111C28_rockin_raceway++;
        }
    }
    D_80111C2C_rockin_raceway = 1;
    func_8010D134_rockin_raceway(0);
}

void func_8010C5E0_rockin_raceway(s32 idx) {
    RR_WRAP(CRot.x);
    RR_WRAP(CRot.y);
    RR_WRAP(CRot.z);
    D_80111BE0_rockin_raceway[idx].center.x = Center.x;
    D_80111BE0_rockin_raceway[idx].center.y = Center.y;
    D_80111BE0_rockin_raceway[idx].center.z = Center.z;
    D_80111BE0_rockin_raceway[idx].rot.x = CRot.x;
    D_80111BE0_rockin_raceway[idx].rot.y = CRot.y;
    D_80111BE0_rockin_raceway[idx].rot.z = CRot.z;
    D_80111BE0_rockin_raceway[idx].zoom = CZoom;
    D_80111BE0_rockin_raceway[idx].unk1C = D_80111BE0_rockin_raceway[idx].unk20 = 0.0f;
}

void func_8010C7CC_rockin_raceway(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_80111C28_rockin_raceway = frames - 1;
        D_80111C2A_rockin_raceway = frames;
        if (cx != 65535.0f) {
            D_80111BE0_rockin_raceway[0].center.x = cx;
        } else {
            D_80111BE0_rockin_raceway[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_80111BE0_rockin_raceway[0].center.y = cy;
        } else {
            D_80111BE0_rockin_raceway[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_80111BE0_rockin_raceway[0].center.z = cz;
        } else {
            D_80111BE0_rockin_raceway[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_80111BE0_rockin_raceway[0].rot.x = rx;
        } else {
            D_80111BE0_rockin_raceway[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_80111BE0_rockin_raceway[0].rot.y = ry;
        } else {
            D_80111BE0_rockin_raceway[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_80111BE0_rockin_raceway[0].rot.z = rz;
        } else {
            D_80111BE0_rockin_raceway[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_80111BE0_rockin_raceway[0].zoom = zoom;
        } else {
            D_80111BE0_rockin_raceway[0].zoom = CZoom;
        }
        func_8010C5E0_rockin_raceway(1);
    }
}

void func_8010C9BC_rockin_raceway(void) {
    D_80111BD8_rockin_raceway->func = NULL;
}

void func_8010C9CC_rockin_raceway(void) {
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway->func = func_8010C0D8_rockin_raceway;
}

void func_8010CA1C_rockin_raceway(void) {
    HuCamera *cam;
    s32 i;

    D_80111C34_rockin_raceway = 0;
    D_80111C4C_rockin_raceway = HuMemAllocTag(16 * sizeof(RrFocus), 0x7918);
    D_80111C30_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010CE90_rockin_raceway);
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

#ifdef NON_MATCHING
void func_8010CADC_rockin_raceway(Vec *pos, f32 weight) {
    RrFocus *focus;

    if (D_80111C30_rockin_raceway != NULL && D_80111C34_rockin_raceway < 16) {
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].pos.x = pos->x;
        focus = &D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway];
        focus->pos.y = pos->y;
        focus->pos.z = pos->z;
        focus->weight = weight;
        D_80111C34_rockin_raceway++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CADC_rockin_raceway);
#endif

void func_8010CB5C_rockin_raceway(RrRacer *kart, f32 weight) {
    Vec pos;

    pos.x = kart->unk58.x + 100.0;
    pos.y = kart->unk58.y + 100.0;
    pos.z = kart->unk58.z;
    func_8010CADC_rockin_raceway(&pos, weight);
    pos.x = kart->unk58.x - 100.0;
    pos.y = kart->unk58.y - 100.0;
    pos.z = kart->unk58.z;
    func_8010CADC_rockin_raceway(&pos, weight);
}

void func_8010CC10_rockin_raceway(void) {
    f32 max[3];
    f32 min[3];
    f32 *p;
    s32 i;
    s32 j;

    if (D_80111C34_rockin_raceway > 0) {
        for (i = 0; i < 4; i++) {
            D_80111C38_rockin_raceway[i] = 0.0f;
        }
        for (i = 0; i < D_80111C34_rockin_raceway; i++) {
            D_80111C38_rockin_raceway[3] += D_80111C4C_rockin_raceway[i].weight;
        }
        for (i = 0; i < 3; i++) {
            max[i] = ((f32 *)&D_80111C4C_rockin_raceway[0].pos)[i];
        }
        for (i = 0; i < 3; i++) {
            min[i] = ((f32 *)&D_80111C4C_rockin_raceway[0].pos)[i];
        }
        for (i = 1; i < D_80111C34_rockin_raceway; i++) {
            p = (f32 *)&D_80111C4C_rockin_raceway[i].pos;
            for (j = 0; j < 3; j++) {
                if (max[j] < p[j]) {
                    max[j] = p[j];
                }
            }
        }
        for (i = 1; i < D_80111C34_rockin_raceway; i++) {
            p = (f32 *)&D_80111C4C_rockin_raceway[i].pos;
            for (j = 0; j < 3; j++) {
                if (min[j] > p[j]) {
                    min[j] = p[j];
                }
            }
        }
        for (i = 0; i < 3; i++) {
            D_80111C38_rockin_raceway[i] = (max[i] + min[i]) * 0.5f;
        }
        if (D_80111C38_rockin_raceway[3] >= 1.0f) {
            D_80111C38_rockin_raceway[3] = 1.0f;
        }
    } else {
        D_80111C38_rockin_raceway[0] = Center.x;
        D_80111C38_rockin_raceway[1] = Center.y;
        D_80111C38_rockin_raceway[2] = Center.z;
        D_80111C38_rockin_raceway[3] = 0.0f;
    }
}

void func_8010CE90_rockin_raceway(omObjData *obj) {
    f32 screen[2];
    f32 size;
    f32 scale;
    s32 i;

    size = 0.0f;
    func_8010CC10_rockin_raceway();
    Center.x = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3], Center.x, D_80111C38_rockin_raceway[0]);
    Center.y = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3], Center.y, D_80111C38_rockin_raceway[1]);
    Center.z = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3], Center.z, D_80111C38_rockin_raceway[2]);
    func_8010D134_rockin_raceway(0);
    for (i = 0; i < D_80111C34_rockin_raceway; i++) {
        func_8010D288_rockin_raceway(0, &D_80111C4C_rockin_raceway[i].pos, NULL, screen);
        if (fabs(screen[0]) > size) {
            size = fabs(screen[0]);
        }
        if (fabs(screen[1]) > size) {
            size = fabs(screen[1]);
        }
    }
    if (size != 0.0f) {
        scale = size / 0.8f;
    } else {
        scale = 1.0f;
    }
    D_80111C38_rockin_raceway[4] = scale * CZoom;
    if (D_80111AD8_rockin_raceway == 2) {
        if (D_80111C38_rockin_raceway[4] < 1500.0f) {
            D_80111C38_rockin_raceway[4] = 1500.0f;
        } else if (D_80111C38_rockin_raceway[4] >= 5000.0f) {
            D_80111C38_rockin_raceway[4] = 5000.0f;
        }
    } else {
        if (D_80111C38_rockin_raceway[4] < 1000.0f) {
            D_80111C38_rockin_raceway[4] = 1000.0f;
        } else if (D_80111C38_rockin_raceway[4] >= 5000.0f) {
            D_80111C38_rockin_raceway[4] = 5000.0f;
        }
    }
    CZoom = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway[3] * 0.5f, CZoom, D_80111C38_rockin_raceway[4]);
    CRot.x = func_8010E608_rockin_raceway(318.38f, CRot.x, 10.0f);
    CRot.y = func_8010E608_rockin_raceway(0.0f, CRot.y, 10.0f);
    D_80111C34_rockin_raceway = 0;
}

void func_8010D104_rockin_raceway(void) {
    D_80111C30_rockin_raceway->func = NULL;
}

void func_8010D114_rockin_raceway(void) {
    D_80111C34_rockin_raceway = 0;
    D_80111C30_rockin_raceway->func = func_8010CE90_rockin_raceway;
}

#ifdef NON_MATCHING
void func_8010D134_rockin_raceway(s32 idx) {
    HuCamera *cam;
    f32 rx;
    f32 ry;

    cam = &gCameraList[idx];
    rx = CRot.x;
    ry = CRot.y;
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D134_rockin_raceway);
#endif


/* Projects pos through camera cam: screen position and depth into screen, viewport-relative into rel. */
#ifdef NON_MATCHING
/* raw residue: sz and sn swap f22/f24 (one extra nop) */
void func_8010D288_rockin_raceway(s32 cam, Vec* pos, f32* screen, f32* rel) {
    Mtx look;
    Mtx mtx;
    HuCamera* c;
    Mtx* m;
    f32 sx, sy, sz;
    f32 sn;
    f32 dist;
    f32 x, y;

    c = &gCameraList[cam];
    m = &mtx;
    guLookAt(&look, c->pos.x, c->pos.y, c->pos.z, c->at.x, c->at.y, c->at.z, c->up.x, c->up.y, c->up.z);
    func_80088850_main(m, pos->x, pos->y, pos->z);
    guMtxCatL(m, &look, m);
    sx = (s32)((((u16*)&mtx)[12] << 16) | ((u16*)&mtx)[28]) >> 16;
    sy = (s32)((((u16*)&mtx)[13] << 16) | ((u16*)&mtx)[29]) >> 16;
    sz = (s32)((((u16*)&mtx)[14] << 16) | ((u16*)&mtx)[30]) >> 16;
    sn = sindf(gCameraList[cam].fov[0] / 2.0);
    dist = fabsf(sz * sn / cosdf(gCameraList[cam].fov[0] / 2.0));
    if (dist != 0.0) {
        x = c->viewports[D_800D418E_main].vp.vscale[0] / 4.0 * sx / dist / 1.3333333730697632;
        y = c->viewports[D_800D418E_main].vp.vscale[1] / 4.0 * -sy / dist;
        if (screen != NULL) {
            screen[0] = (s16)(x + c->viewports[D_800D418E_main].vp.vtrans[0] * 0.25f);
            screen[1] = (s16)(y + c->viewports[D_800D418E_main].vp.vtrans[1] * 0.25f);
            screen[2] = dist;
        }
        if (rel != NULL) {
            rel[0] = x / 160.0f;
            rel[1] = y / 120.0f;
        }
    } else {
        screen[0] = screen[1] = screen[2] = 0.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D288_rockin_raceway);
#endif

void func_8010D5B8_rockin_raceway(void) {
    D_80111C50_rockin_raceway = HuMemAllocTag(sizeof(RRRecFrame) * 30, 0x7918);
    memset(D_80111C50_rockin_raceway, 0, sizeof(RRRecFrame) * 30);
    D_80111C54_rockin_raceway = 0;
    D_80111C58_rockin_raceway = 0;
}

/* Records this frame of the race into the ring. */
void func_8010D600_rockin_raceway(void) {
    RRRecFrame* rec = &D_80111C50_rockin_raceway[D_80111C58_rockin_raceway];
    RrRacer* work;
    RRRecPlayer* p;
    RRRecModel* m;
    RrMdlSave* o;
    RrEffect* src;
    HmfModel* model;
    s16 id;
    s32 i;

    rec->unk0 = D_80111AE4_rockin_raceway;
    for (i = 0; i < 4; i++) {
        rec->unk4[i] = D_80111AF0_rockin_raceway[i];
    }
    for (i = 0; i < 4; i++) {
        work = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        p = &rec->player[i];
        p->trans.x = D_800EC598_minigame[i]->trans.x;
        p->trans.y = D_800EC598_minigame[i]->trans.y;
        p->trans.z = D_800EC598_minigame[i]->trans.z;
        p->rot.x = D_800EC598_minigame[i]->rot.x;
        p->rot.y = D_800EC598_minigame[i]->rot.y;
        p->rot.z = D_800EC598_minigame[i]->rot.z;
        p->scale.x = D_800EC598_minigame[i]->scale.x;
        p->scale.y = D_800EC598_minigame[i]->scale.y;
        p->scale.z = D_800EC598_minigame[i]->scale.z;
        p->unk24 = work->unk38;
        p->unk28 = work->unk24;
    }
    m = rec->model;
    for (i = 1; i < 13; i++, m++) {
        id = D_80111B4C_rockin_raceway->model[i];
        if (id != -1) {
            model = &HmfModelData[id];
            m->unk0 = model->unk18;
            m->unk4 = model->unk40;
            m->unk8 = 0;
            m->pos.x = model->pos.x;
            m->pos.y = model->pos.y;
            m->pos.z = model->pos.z;
            m->rot.x = model->rot.x;
            m->rot.y = model->rot.y;
            m->rot.z = model->rot.z;
            m->scale.x = model->scale.x;
            m->scale.y = model->scale.y;
            m->scale.z = model->scale.z;
        }
    }
    o = rec->obj;
    src = D_80111B5C_rockin_raceway;
    for (i = 0; i < 16; i++, o++, src++) {
        id = src->unk02;
        if (id != -1) {
            model = &HmfModelData[id];
            o->unk00 = src->unk00;
            o->unk02 = model->unk40;
            o->unk04 = model->unk18;
            o->unk08 = src->unk04;
            o->unk0C = src->unk08;
            o->pos.x = model->pos.x;
            o->pos.y = model->pos.y;
            o->pos.z = model->pos.z;
            o->rot.x = model->rot.x;
            o->rot.y = model->rot.y;
            o->rot.z = model->rot.z;
            o->scale.x = model->scale.x;
            o->scale.y = model->scale.y;
            o->scale.z = model->scale.z;
        }
    }
    D_80111C54_rockin_raceway++;
    D_80111C58_rockin_raceway++;
    if (D_80111C58_rockin_raceway >= 30) {
        D_80111C58_rockin_raceway -= 30;
    }
}

/* The recorded frame idx frames back from the oldest, NULL if not recorded. */
RRRecFrame* func_8010D944_rockin_raceway(s32 idx) {
    if ((idx >= D_80111C54_rockin_raceway) | (idx >= 30)) {
        return NULL;
    }
    if (D_80111C54_rockin_raceway >= 30) {
        idx += D_80111C58_rockin_raceway;
    }
    if (idx >= 30) {
        idx -= 30;
    }
    return &D_80111C50_rockin_raceway[idx];
}

#ifdef NON_MATCHING
/* Plays recorded frame `frame` back, blending from the frame before over 4.5 ticks. */
void func_8010D9C4_rockin_raceway(s32 frame) {
    s32 key[2];
    RRRecFrame* rec;
    RRRecFrame* prevRec;
    RRRecPlayer* cur;
    RRRecPlayer* prev;
    omObjData* obj;
    HmfModel* model;
    RrPose* trail;
    RRRecModel* m;
    RRRecModel* pm;
    RrMdlSave* o;
    RrMdlSave* po;
    RrEffect* src;
    f32 t;
    s32 i;
    s32 j;
    s16 id;

    if (D_801115FC_rockin_raceway != frame) {
        D_801115FC_rockin_raceway = frame;
        D_80111AC0_rockin_raceway = 0;
    } else {
        D_80111AC0_rockin_raceway++;
    }
    t = D_80111AC0_rockin_raceway / 4.5f;
    if (t >= 1.0f) {
        t = 1.0f;
    } else if (t <= 0.0f) {
        t = 0.0f;
    }
    rec = func_8010D944_rockin_raceway(frame);
    key[0] = rec->unk0;
    key[1] = D_80111AE8_rockin_raceway;
    func_8010B5DC_rockin_raceway(key);
    func_80109D00_rockin_raceway(rec->unk4);
    func_80109D54_rockin_raceway(key);
    for (i = 0; i < 4; i++) {
        cur = &rec->player[i];
        obj = D_800EC598_minigame[i];
        prev = cur;
        if (frame - 1 >= 0) {
            prev = &func_8010D944_rockin_raceway(frame - 1)->player[i];
        }
        obj->trans.x = func_8010E7C8_rockin_raceway(t, prev->trans.x, cur->trans.x);
        obj->trans.y = func_8010E7C8_rockin_raceway(t, prev->trans.y, cur->trans.y);
        obj->trans.z = func_8010E7C8_rockin_raceway(t, prev->trans.z, cur->trans.z);
        obj->rot.x = func_8010E7E0_rockin_raceway(t, prev->rot.x, cur->rot.x);
        obj->rot.y = func_8010E7E0_rockin_raceway(t, prev->rot.y, cur->rot.y);
        obj->rot.z = func_8010E7E0_rockin_raceway(t, prev->rot.z, cur->rot.z);
        obj->scale.x = func_8010E7C8_rockin_raceway(t, prev->scale.x, cur->scale.x);
        obj->scale.y = func_8010E7C8_rockin_raceway(t, prev->scale.y, cur->scale.y);
        obj->scale.z = func_8010E7C8_rockin_raceway(t, prev->scale.z, cur->scale.z);
    }
    if (D_80111B3A_rockin_raceway != 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 2; j++) {
                cur = &rec->player[i];
                if (frame - 1 - j >= 0) {
                    cur = &func_8010D944_rockin_raceway(frame - 2 - j)->player[i];
                }
                if (frame - 2 - j >= 0) {
                    prev = &func_8010D944_rockin_raceway(frame - 3 - j)->player[i];
                } else {
                    prev = cur;
                }
                model = &HmfModelData[D_800EC598_minigame[i]->model[j + 3]];
                trail = &D_80111B3C_rockin_raceway[j].p[i];
                if (trail->unk02 != 0) {
                    if (trail->unk00 != 0) {
                        model->pos.x = trail->unk04.x;
                        model->pos.y = trail->unk04.y;
                        model->pos.z = trail->unk04.z;
                        model->rot.x = trail->unk10.x;
                        model->rot.y = trail->unk10.y;
                        model->rot.z = trail->unk10.z;
                        model->scale.x = trail->unk1C.x;
                        model->scale.y = trail->unk1C.y;
                        model->scale.z = trail->unk1C.z;
                        trail->unk00--;
                    } else {
                        model->pos.x = func_8010E7C8_rockin_raceway(t, prev->trans.x, cur->trans.x);
                        model->pos.y = func_8010E7C8_rockin_raceway(t, prev->trans.y, cur->trans.y);
                        model->pos.z = func_8010E7C8_rockin_raceway(t, prev->trans.z, cur->trans.z);
                        model->rot.x = func_8010E7E0_rockin_raceway(t, prev->rot.x, cur->rot.x);
                        model->rot.y = func_8010E7E0_rockin_raceway(t, prev->rot.y, cur->rot.y);
                        model->rot.z = func_8010E7E0_rockin_raceway(t, prev->rot.z, cur->rot.z);
                        model->scale.x = func_8010E7C8_rockin_raceway(t, prev->scale.x, cur->scale.x);
                        model->scale.y = func_8010E7C8_rockin_raceway(t, prev->scale.y, cur->scale.y);
                        model->scale.z = func_8010E7C8_rockin_raceway(t, prev->scale.z, cur->scale.z);
                    }
                }
            }
        }
    }
    prevRec = rec;
    if (frame - 1 >= 0) {
        prevRec = func_8010D944_rockin_raceway(frame - 1);
    }
    m = rec->model;
    pm = prevRec->model;
    for (i = 1; i < 13; i++, m++, pm++) {
        id = D_80111B4C_rockin_raceway->model[i];
        if (id != -1) {
            model = &HmfModelData[id];
            model->unk18 = m->unk0;
            model->unk40 = func_8010E7C8_rockin_raceway(t, pm->unk4, m->unk4);
            model->unk44 = 0.0f;
            model->pos.x = m->pos.x;
            model->pos.y = m->pos.y;
            model->pos.z = m->pos.z;
            model->rot.x = m->rot.x;
            model->rot.y = m->rot.y;
            model->rot.z = m->rot.z;
            model->scale.x = m->scale.x;
            model->scale.y = m->scale.y;
            model->scale.z = m->scale.z;
        }
    }
    o = rec->obj;
    po = prevRec->obj;
    src = D_80111B5C_rockin_raceway;
    for (i = 0; i < 16; i++, src++, o++, po++) {
        id = src->unk02;
        if (id != -1) {
            model = &HmfModelData[id];
            src->unk00 = o->unk00;
            model->unk18 = o->unk04;
            src->unk04 = o->unk08;
            src->unk08 = o->unk0C;
            func_8010FA78_rockin_raceway(src->unk02, func_80055194_main(D_80111B68_rockin_raceway->unk04), src->unk04,
                                         &D_801114D4_rockin_raceway);
            if (po->unk00 != 0) {
                model->pos.x = func_8010E7C8_rockin_raceway(t, po->pos.x, o->pos.x);
                model->pos.y = func_8010E7C8_rockin_raceway(t, po->pos.y, o->pos.y);
                model->pos.z = func_8010E7C8_rockin_raceway(t, po->pos.z, o->pos.z);
            } else {
                model->pos.x = o->pos.x;
                model->pos.y = o->pos.y;
                model->pos.z = o->pos.z;
            }
            model->rot.x = o->rot.x;
            model->rot.y = o->rot.y;
            model->rot.z = o->rot.z;
            model->scale.x = o->scale.x;
            model->scale.y = o->scale.y;
            model->scale.z = o->scale.z;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D9C4_rockin_raceway);
#endif

/* Shifts every recorded player sideways (player `idx` across the track) and swings the recorded heading. */
void func_8010E08C_rockin_raceway(s32 idx) {
    RRRecPlayer* p;
    RrRacer* work;
    s32 i;
    s32 j;
    s32 turn;

    for (j = 0; j < 30; j++) {
        for (i = 0; i < 4; i++) {
            p = &func_8010D944_rockin_raceway(j)->player[i];
            if (i == idx) {
                p->trans.x = (f32)(p->trans.x - 20.000000298023224) + j / 30.0f * 40.00000059604645;
            } else {
                p->trans.x = p->trans.x - 20.000000298023224;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        work = func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        if (idx == i) {
            work->unk44 = work->unk44 + 20.000000298023224;
        } else {
            work->unk44 = work->unk44 - 20.000000298023224;
        }
    }
    p = &func_8010D944_rockin_raceway(29)->player[idx];
    turn = 90.0f - p->unk28;
    for (j = 0; j < 30; j++) {
        p = &func_8010D944_rockin_raceway(j)->player[idx];
        p->unk28 += turn;
        if (p->unk28 > 360.0f) {
            p->unk28 -= 360.0f;
        } else if (p->unk28 < 0.0f) {
            p->unk28 += 360.0f;
        }
        p->rot.x = sindf(p->unk28) * p->unk24 * 30.0f;
    }
}

void func_8010E2E4_rockin_raceway(void) {
    RRSe* se;
    s32 i;

    se = D_80111BD0_rockin_raceway = HuMemAllocTag(sizeof(RRSe) * 16, 0x7918);
    memset(se, 0, sizeof(RRSe) * 16);
    for (i = 0; i < 16; i++, se++) {
        se->fx = -1;
    }
}

/* Queues sound fx to play after delay ticks; returns its slot, -1 if all 16 are busy. */
s32 func_8010E344_rockin_raceway(s16 fx, s16 delay, s16 kind, s16 arg) {
    RRSe* se = D_80111BD0_rockin_raceway;
    s32 i;

    for (i = 0; i < 16; i++, se++) {
        if (se->fx == -1) {
            break;
        }
    }
    if (i >= 16) {
        return -1;
    }
    se->fx = fx;
    se->delay = delay;
    se->kind = kind;
    se->arg = arg;
    return i;
}

void func_8010E39C_rockin_raceway(void) {
    RRSe* se = D_80111BD0_rockin_raceway;
    s32 i;

    for (i = 0; i < 16; i++, se++) {
        if (se->fx != -1) {
            if (se->delay <= 0) {
                switch (se->kind) {
                    case 0:
                        HuAudFXPlay(se->fx);
                        break;
                    case 1:
                        func_8004AC98_main(se->fx, se->arg);
                        break;
                    case 2:
                        CharFXPlay(se->fx, GwPlayer[(s16)(se->arg % 4)].chr);
                        break;
                    default:
                        func_8004AC98_main(GwPlayer[(s16)(se->arg % 4)].chr + se->fx + 1, se->arg);
                        break;
                }
                se->fx = -1;
            }
            se->delay--;
        }
    }
}

/* Signed difference a - b of two angles, in (-180, 180]. */
f32 func_8010E504_rockin_raceway(f32 a, f32 b) {
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
    a -= b;
    if (a <= -180.0f) {
        a += 360.0f;
    } else if (a >= 180.0f) {
        a -= 360.0f;
    }
    return a;
}

/* Turns angle cur toward target by at most step degrees. */
f32 func_8010E608_rockin_raceway(f32 target, f32 cur, f32 step) {
    f32 d;
    f32 v;
    f64 e;

    RR_WRAP(target);
    RR_WRAP(cur);
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
    RR_WRAP(v);
    return v;
}

f32 func_8010E7C8_rockin_raceway(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

#ifdef NON_MATCHING
/* Angle lerp from a toward b. */
f32 func_8010E7E0_rockin_raceway(f32 t, f32 a, f32 b) {
    return func_8010E608_rockin_raceway(b, a, fabsf(func_8010E504_rockin_raceway(b, a) * t));
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E7E0_rockin_raceway);
#endif

/* Quadratic Bezier. */
f32 func_8010E840_rockin_raceway(f32 t, f32 a, f32 b, f32 c) {
    f32 u = 1.0 - t;

    return u * u * a + 2.0 * (u * t * b) + t * t * c;
}

void func_8010E8A0_rockin_raceway(f32 t, Vec* a, Vec* b, Vec* c, Vec* out) {
    f32* pa = (f32*)a;
    f32* pb = (f32*)b;
    f32* pc = (f32*)c;
    f32* po = (f32*)out;
    s32 i;

    for (i = 0; i < 3; i++) {
        *po++ = func_8010E840_rockin_raceway(t, *pa++, *pb++, *pc++);
    }
}

/* Quadratic Bezier derivative. */
f32 func_8010E93C_rockin_raceway(f32 t, f32 a, f32 b, f32 c) {
    return 2.0 * ((t - 1.0) * a + (1.0 - 2.0 * t) * b + t * c);
}

/* Unit tangent of the quadratic Bezier at t (0,0,1 if degenerate). */
void func_8010E994_rockin_raceway(f32 t, Vec* a, Vec* b, Vec* c, Vec* out) {
    f32 d[3];
    f32* pa = (f32*)a;
    f32* pb = (f32*)b;
    f32* pc = (f32*)c;
    f32* po = (f32*)out;
    f32 len;
    s32 i;

    for (i = 0; i < 3; i++) {
        d[i] = func_8010E93C_rockin_raceway(t, *pa++, *pb++, *pc++);
    }
    len = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    if (len != 0.0f) {
        for (i = 0; i < 3; i++) {
            *po++ = (f32)(1.0 / len) * d[i];
        }
        return;
    }
    *po++ = 0.0f;
    *po++ = 0.0f;
    *po = 1.0f;
}

/* atan2 in degrees, wrapped to [0, 360). */
f32 func_8010EB04_rockin_raceway(f32 x, f32 z) {
    f32 a = atan2df(z, x);

    if (a < 0.0) {
        a += 360.0;
    } else if (a >= 360.0) {
        a -= 360.0;
    }
    return a;
}

/* Pitch and yaw of direction dir. */
void func_8010EB84_rockin_raceway(Vec* dir, f32* angles) {
    f32 h = sqrtf(dir->x * dir->x + dir->z * dir->z);

    *angles++ = func_8010EB04_rockin_raceway(h, -dir->y);
    *angles++ = func_8010EB04_rockin_raceway(dir->z, dir->x);
    *angles = 0.0f;
}

void func_8010EC0C_rockin_raceway(omObjData* obj, void* p) {
    obj->work[0] = (u32)p >> 24;
    obj->work[1] = ((u32)p >> 16) & 0xFF;
    obj->work[2] = ((u32)p >> 8) & 0xFF;
    obj->work[3] = (u32)p & 0xFF;
}

RrRacer* func_8010EC38_rockin_raceway(omObjData* obj) {
    RRPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}

/* Builds a camera-facing sprite model from spr (model 0x18C1), tinted color; returns the model. */
s32 func_8010EC8C_rockin_raceway(HuSprite_Unk84_Struct* spr, RRColor* color) {
    HmfData* hmf;
    Gfx* buf;
    Gfx* gfx;
    s32 size;
    s32 idx;
    s32 fmt;
    s32 i;

    buf = gfx = HuMemAlloc(0x10000);
    idx = func_8001A894_main(0x18C1, buf, 4);
    hmf = HmfModelData[idx].hmf;
    hmf->unk60->unk50 |= 0x71010000;
    HuMemFree(hmf->unk3C);
    hmf->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    func_8010FBAC_rockin_raceway(spr, hmf, 1.0f, 0, 0);
    gSPDisplayList(gfx++, osVirtualToPhysical(D_801116F0_rockin_raceway));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (spr->unk18 & 0x8000) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)buf;
    hmf->unk3C->unk10 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buf, hmf->unk3C->unk10, size);
    HuMemFree(buf);
    buf = gfx = HuMemAlloc(0x10000);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (spr->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (spr->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, spr->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, spr->unk0C);
        }
        gDPPipeSync(gfx++);
        fmt = 2;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        fmt = (spr->unk18 & 0x8000) ? 4 : 0;
    }
    switch (spr->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, fmt, spr->unk00->unk04, spr->unk00->unk06, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, fmt, G_IM_SIZ_8b, spr->unk00->unk04, spr->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, fmt, G_IM_SIZ_16b, spr->unk00->unk04, spr->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 0x01, osVirtualToPhysical(hmf->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)buf;
    hmf->unk3C->unk14 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buf, hmf->unk3C->unk14, size);
    HuMemFree(buf);
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = hmf->unk3C->unk00[i + 1] = HuMemAllocTag(0x100, hmf->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 0x02, osVirtualToPhysical(spr->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, color->a);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    hmf->unk3C->unk00[0] = hmf->unk3C->unk00[D_800D2008_main + 1];
    return idx;
}

/* Clones model's hmf as a new model with its own per-buffer display lists (segment 2 = spr's first frame,
   prim color = color); returns the new model. */
s32 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct* spr, u16 model, RRColor* color) {
    HmfModel* m;
    HmfData* src;
    HmfData* dst;
    Gfx* gfx;
    s32 id;
    s32 i;

    m = &HmfModelData[model];
    src = m->hmf;
    id = func_8001A894_main(m->unk18, NULL, 4);
    dst = HmfModelData[id].hmf;
    dst->unk60->unk50 = src->unk60->unk50;
    HuMemFree(dst->unk3C);
    dst->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    dst->unk3C->unk10 = src->unk3C->unk10;
    dst->unk3C->unk14 = src->unk3C->unk14;
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = dst->unk3C->unk00[i + 1] = HuMemAllocTag(0x100, dst->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 0x02, osVirtualToPhysical(spr->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(dst->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, color->a);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(dst->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    dst->unk3C->unk00[0] = dst->unk3C->unk00[D_800D2008_main + 1];
    return id;
}

/* Points model's display list at frame `frame` of spr, tinted color. */
void func_8010FA78_rockin_raceway(u16 model, HuSprite_Unk84_Struct* spr, u16 frame, RRColor* color) {
    HmfModel* m;
    HmfData* hmf;
    Gfx* gfx;

    m = &HmfModelData[model];
    hmf = m->hmf;
    gfx = hmf->unk3C->unk00[D_800D2008_main + 1];
    hmf->unk3C->unk00[0] = gfx;
    gDPPipeSync(&gfx[0]);
    gSPSegment(&gfx[1], 0x02, osVirtualToPhysical(spr->unk00[frame].unk00));
    gSPDisplayList(&gfx[2], osVirtualToPhysical(hmf->unk3C->unk10));
    gDPSetPrimColor(&gfx[3], 0, 0, color->r, color->g, color->b, color->a);
    gDPPipeSync(&gfx[4]);
    gSPDisplayList(&gfx[5], osVirtualToPhysical(hmf->unk3C->unk14));
    gDPPipeSync(&gfx[6]);
    gSPEndDisplayList(&gfx[7]);
}

/* Builds the sprite's vertex quads (split into TMEM-sized bands), one copy per buffer in hmf->unk44; returns the band count. */
s32 func_8010FBAC_rockin_raceway(HuSprite_Unk84_Struct* spr, HmfData* hmf, f32 scale, u16 x, u16 y) {
    Vtx* buf;
    Vtx* v;
    Vtx_t* to;
    Vtx_t* from;
    s32 tmem;
    s32 w;
    s32 h;
    s32 sw;
    s32 sh;
    s32 size;
    s32 count;
    s32 qh;
    s32 qsh;
    s32 n;
    s32 i;
    s32 j;

    if (spr->unk1A >= 2) {
        tmem = 0x800;
    } else {
        tmem = 0x1000;
    }
    w = spr->unk00->unk04;
    h = spr->unk00->unk06;
    sw = w * 100.0 * scale / 32.0;
    sh = h * 100.0 * scale / 32.0;
    if ((spr->unk18 & 0xFFF) == 4) {
        size = ((w + 1) & 0xFFFE) * h * 4;
    } else {
        size = w * h * spr->unk18;
    }
    size = (size < 0) ? (size + 7) : size;
    size >>= 3;
    count = size / tmem;
    if (count <= 0) {
        count = 1;
    }
    qh = h / count;
    qsh = sh / count;
    n = count * 4;
    buf = v = HuMemAllocTag(n * sizeof(Vtx), hmf->unk0E);
    memset(buf, 0, n * sizeof(Vtx));
    for (i = 0; i < count; i++, v += 4) {
        v[0].v.ob[0] = (s32)(sw * 0.5);
        v[0].v.ob[1] = (s32)(sh * 0.5 - qsh * i);
        v[0].v.tc[0] = (w - 1) * 64;
        v[0].v.tc[1] = 0;
        v[1].v.ob[0] = (s32)(sw * 0.5);
        v[1].v.ob[1] = (s32)(sh * 0.5 - qsh * (i + 1));
        v[1].v.tc[0] = (w - 1) * 64;
        v[1].v.tc[1] = (qh - 1) * 64;
        v[2].v.ob[0] = (s32) - (sw * 0.5);
        v[2].v.ob[1] = (s32)(sh * 0.5 - qsh * i);
        v[2].v.tc[0] = 0;
        v[2].v.tc[1] = 0;
        v[3].v.ob[0] = (s32) - (sw * 0.5);
        v[3].v.ob[1] = (s32)(sh * 0.5 - qsh * (i + 1));
        v[3].v.tc[0] = 0;
        v[3].v.tc[1] = (qh - 1) * 64;
        for (j = 0; j < 4; j++) {
            v[j].v.ob[0] += x;
            v[j].v.ob[1] += y;
            v[j].v.ob[2] = 0;
            v[j].v.flag = 0;
            v[j].v.cn[3] = 0xFF;
            v[j].v.cn[0] = v[j].v.cn[1] = v[j].v.cn[2] = 0;
        }
    }
    v = buf;
    for (i = 0; i < D_800D1FF0_main; i++) {
        hmf->unk44[i] = HuMemAllocTag(n * sizeof(Vtx), hmf->unk0E);
        to = (Vtx_t*)hmf->unk44[i];
        from = &v->v;
        for (j = 0; j < n; j++) {
            *(to++) = *(from++);
        }
    }
    HuMemFree(buf);
    return count;
}

/* Builds a sprite model from spr on the four vertices vtx (model 0x4C1); returns the model. */
s32 func_8010FFB8_rockin_raceway(HuSprite_Unk84_Struct* spr, Vtx* vtx) {
    HmfData* hmf;
    Gfx* buf;
    Gfx* gfx;
    s32 size;
    s32 idx;
    s32 fmt;
    s32 i;

    buf = gfx = HuMemAlloc(0x10000);
    idx = func_8001A894_main(0x4C1, buf, 4);
    hmf = HmfModelData[idx].hmf;
    hmf->unk60->unk50 |= 0x01000000;
    HuMemFree(hmf->unk3C);
    hmf->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    for (i = 0; i < D_800D1FF0_main; i++) {
        hmf->unk44[i] = HuMemAllocTag(sizeof(RRQuad), hmf->unk0E);
        *(RRQuad*)hmf->unk44[i] = *(RRQuad*)vtx;
    }
    gSPDisplayList(gfx++, osVirtualToPhysical(D_801116F0_rockin_raceway));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (spr->unk18 & 0x8000) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gSPSegment(gfx++, 0x01, osVirtualToPhysical(hmf->unk44[0]));
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)buf;
    hmf->unk3C->unk10 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buf, hmf->unk3C->unk10, size);
    HuMemFree(buf);
    buf = gfx = HuMemAlloc(0x10000);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (spr->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (spr->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, spr->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, spr->unk0C);
        }
        gDPPipeSync(gfx++);
        fmt = 2;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        fmt = (spr->unk18 & 0x8000) ? 4 : 0;
    }
    switch (spr->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, fmt, spr->unk00->unk04, spr->unk00->unk06, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, fmt, G_IM_SIZ_8b, spr->unk00->unk04, spr->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, fmt, G_IM_SIZ_16b, spr->unk00->unk04, spr->unk00->unk06, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)buf;
    hmf->unk3C->unk14 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buf, hmf->unk3C->unk14, size);
    HuMemFree(buf);
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = hmf->unk3C->unk00[i + 1] = HuMemAllocTag(0x200, hmf->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 0x02, osVirtualToPhysical(spr->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    hmf->unk3C->unk00[0] = hmf->unk3C->unk00[D_800D2008_main + 1];
    return idx;
}

/* Shows each player's character (frame = character, 8 = none) on the four podium models. */
void func_80110C38_rockin_raceway(s16* models, HuSprite_Unk84_Struct* spr, s32* players) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (players[i] < 0) {
            func_8010FA78_rockin_raceway(models[i], spr, 8, &D_80111730_rockin_raceway);
        } else {
            if (players[i] >= 4) {
                players[i] = 0;
            }
            func_8010FA78_rockin_raceway(models[i], spr, GwPlayer[players[i]].chr, &D_80111730_rockin_raceway);
        }
        Hu3DModelPosSet(models[i], D_80111414_rockin_raceway[i].x, D_80111414_rockin_raceway[i].y + 40.00000059604645,
                        D_80111414_rockin_raceway[i].z);
        Hu3DModelRotSet(models[i], 95.72f, 0.0f, 0.0f);
    }
}

#ifdef NON_MATCHING
/* retail hoists the 40.0 double into f22 before the loop (frame 8 bytes larger); otherwise identical */
/* Shows the twelve digit models (frames 0-9, clamped). */
void func_80110D90_rockin_raceway(s16* models, HuSprite_Unk84_Struct* spr, s32* times /* unused */) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (D_80111B00_rockin_raceway[i] >= 9) {
            D_80111B00_rockin_raceway[i] = 9;
        } else if (D_80111B00_rockin_raceway[i] < 0) {
            D_80111B00_rockin_raceway[i] = 0;
        }
        func_8010FA78_rockin_raceway(models[i], spr, D_80111B00_rockin_raceway[i], &D_80111734_rockin_raceway);
        Hu3DModelPosSet(models[i], D_80111444_rockin_raceway[i].x, D_80111444_rockin_raceway[i].y + 40.00000059604645,
                        D_80111444_rockin_raceway[i].z);
        Hu3DModelRotSet(models[i], 95.72f, 0.0f, 0.0f);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80110D90_rockin_raceway);
#endif
