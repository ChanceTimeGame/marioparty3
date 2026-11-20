#include "common.h"
// m1 sy1: Slot Synch (two teams of two; each team stops the reels of one slot machine)
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"

/* One player (D_8010DF60_slot_synch, 4 x 0x30). Log Jam's player block has the same shape. */
typedef struct SsPlayer {
    /* 0x00 */ s16 unk00; /* slot 0..3 (also the reel index) */
    /* 0x02 */ s16 unk02; /* team */
    /* 0x04 */ s16 unk04; /* pending result motion: 0 win, 1 lose, -1 none */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A; /* frame counter */
    /* 0x0C */ f32 unk0C; /* position */
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u32 unk18; /* win message (func_80045F1C_main) */
    /* 0x1C */ s16 unk1C; /* GwPlayer index */
    /* 0x1E */ s16 unk1E; /* controller port */
    /* 0x20 */ s16 unk20; /* character */
    /* 0x22 */ s16 unk22; /* CPU */
    /* 0x24 */ s16 unk24; /* CPU difficulty */
    /* 0x26 */ s16 unk26; /* CPU: last reel symbol seen */
    /* 0x28 */ s16 unk28; /* CPU: 1 = stop on a miss */
    /* 0x2A */ s16 unk2A; /* CPU: frames to wait */
    /* 0x2C */ s16 unk2C; /* CPU: target symbol, -1 none */
    /* 0x2E */ char unk2E[2];
} SsPlayer; // Size 0x30

/* One team (D_8010DF5C_slot_synch, 2 x 0x20). */
typedef struct SsTeam {
    /* 0x00 */ omObjData* unk00; /* player objects */
    /* 0x04 */ omObjData* unk04;
    /* 0x08 */ SsPlayer* unk08;
    /* 0x0C */ SsPlayer* unk0C;
    /* 0x10 */ s16 unk10; /* team index */
    /* 0x12 */ s16 unk12; /* state */
    /* 0x14 */ s16 unk14; /* state timer */
    /* 0x16 */ s16 unk16; /* score */
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A; /* result symbol, 4 = no match */
    /* 0x1C */ s16 unk1C; /* reels running */
    /* 0x1E */ s16 unk1E; /* CPU: symbol the team aims at */
} SsTeam; // Size 0x20

/* One reel (D_8010DF7C_slot_synch, 4 x 0x3C): reels 0-1 are team 0's machine, 2-3 team 1's. */
typedef struct SsReel {
    /* 0x00 */ s16 unk00; /* model */
    /* 0x02 */ u8 unk02; /* reel index */
    /* 0x03 */ u8 unk03; /* reel strip (D_8010D854_slot_synch row) */
    /* 0x04 */ s8 unk04; /* 0 left, 1 right */
    /* 0x05 */ u8 unk05; /* face in front, 0..3 */
    /* 0x06 */ u8 unk06; /* symbol in front */
    /* 0x07 */ char unk07;
    /* 0x08 */ s16 unk08; /* symbol to stop on, -1 any */
    /* 0x0A */ u16 unk0A; /* state timer */
    /* 0x0C */ s16 unk0C; /* state: 0 idle, 1 speeding up, 2 spinning, 3 dropping, 4/5 broken */
    /* 0x0E */ char unk0E[2];
    /* 0x10 */ f32 unk10; /* drop speed */
    /* 0x14 */ f32 unk14; /* spin speed */
    /* 0x18 */ f32 unk18; /* spin acceleration */
    /* 0x1C */ f32 unk1C; /* top spin speed */
    /* 0x20 */ s32 unk20; /* spin sound, -1 none */
    /* 0x24 */ Vec unk24; /* position */
    /* 0x30 */ Vec unk30; /* rotation */
} SsReel; // Size 0x3C

/* One row of machine-body vertices sharing a height (func_80108D3C_slot_synch). */
typedef struct SsRow {
    /* 0x00 */ u16 unk00[72]; /* vertex indices */
    /* 0x90 */ s16 unk90; /* height (Vtx ob[1]) */
    /* 0x92 */ s16 unk92; /* vertex count */
} SsRow; // Size 0x94

/* One machine body (D_8010DF80_slot_synch, 2 x 0x20): a bulge that runs up the cabinet. */
typedef struct SsBody {
    /* 0x00 */ s16 unk00; /* model */
    /* 0x02 */ s16 unk02; /* machine index */
    /* 0x04 */ s16 unk04; /* 1 = bulge moving */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08; /* bulge height */
    /* 0x0C */ f32 unk0C; /* bulge half-width */
    /* 0x10 */ f32 unk10; /* bulge strength */
    /* 0x14 */ f32 unk14; /* bulge speed */
    /* 0x18 */ s16 unk18; /* row count */
    /* 0x1A */ char unk1A[2];
    /* 0x1C */ SsRow* unk1C; /* rows, shared by both bodies */
} SsBody; // Size 0x20

/* One score sprite (D_8010DF70_slot_synch.unk08, up to 24 x 0x2C). */
typedef struct SsSpr {
    /* 0x00 */ s16 unk00; /* group member */
    /* 0x02 */ u16 unk02; /* priority */
    /* 0x04 */ u16 unk04; /* timer */
    /* 0x06 */ u8 unk06; /* graphic */
    /* 0x07 */ u8 unk07; /* team */
    /* 0x08 */ u8 unk08; /* state: 0 idle, 1 bouncing, 2 settling */
    /* 0x09 */ u8 unk09; /* position changed */
    /* 0x0A */ u8 unk0A; /* blink counter, 0x80 = rising */
    /* 0x0B */ u8 unk0B; /* start delay */
    /* 0x0C */ u16 unk0C; /* bounce duration */
    /* 0x0E */ char unk0E[2];
    /* 0x10 */ f32 unk10; /* bounce height */
    /* 0x14 */ Vec2f unk14; /* start position */
    /* 0x1C */ Vec2f unk1C; /* target position */
    /* 0x24 */ Vec2f unk24; /* position */
} SsSpr; // Size 0x2C

/* The score sprites' manager (D_8010DF70_slot_synch, 0xC). */
typedef struct SsSprMan {
    /* 0x00 */ omObjData* unk00;
    /* 0x04 */ s16 unk04; /* sprite group */
    /* 0x06 */ u16 unk06; /* sprite count */
    /* 0x08 */ SsSpr* unk08;
} SsSprMan;

/* A sprite position table entry (D_8010D938_slot_synch, D_8010D980_slot_synch). */
typedef struct SsSprPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05; /* graphic */
} SsSprPos;

/* The camera/ground object's data (func_80107794_slot_synch); Boulder Ball's BbGround. */
typedef struct SsGround {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} SsGround; // Size 0xB4

/* A symbol popping out of a machine (D_8010DF88_slot_synch, 5 x 0x58). */
typedef struct SsMot {
    /* 0x00 */ s16 unk00; /* idle motion (the model's own) */
    /* 0x02 */ s16 unk02; /* land motion */
    /* 0x04 */ s16 unk04; /* run motion */
} SsMot;

typedef struct SsPop {
    /* 0x00 */ u8 unk00; /* active */
    /* 0x01 */ u8 unk01; /* team */
    /* 0x02 */ u8 unk02; /* scored */
    /* 0x03 */ u8 unk03; /* no sparkle */
    /* 0x04 */ s16 unk04[4]; /* model per symbol */
    /* 0x0C */ SsMot unk0C[4];
    /* 0x24 */ s16 unk24; /* shadow model */
    /* 0x26 */ s16 unk26; /* symbol, 4 = none */
    /* 0x28 */ s16 unk28; /* state */
    /* 0x2A */ s16 unk2A; /* state timer */
    /* 0x2C */ f32 unk2C; /* vertical speed */
    /* 0x30 */ f32 unk30; /* run speed */
    /* 0x34 */ Vec unk34; /* position */
    /* 0x40 */ Vec unk40; /* rotation */
    /* 0x4C */ Vec unk4C; /* scale */
} SsPop; // Size 0x58

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

#define ABS(x) ((x) < 0 ? -(x) : (x))

/* HmfData's vertex count (0x18 lies inside the header's unk16 padding). */
#define SS_HMF_VTXNUM(hmf) (*(s16*)&(hmf)->unk16[2])

void func_80105B98_slot_synch(omObjData* obj);
void func_80105C08_slot_synch(omObjData* obj);
void func_80106080_slot_synch(omObjData* obj);
void func_801060A4_slot_synch(omObjData* obj);
void func_8010614C_slot_synch(void);
void func_80106560_slot_synch(omObjData* obj);
void func_80106878_slot_synch(omObjData* obj);
void func_80106E8C_slot_synch(omObjData* obj);
void func_80107108_slot_synch(omObjData* obj);
void func_801075D4_slot_synch(void);
void func_80109508_slot_synch(void);
s16 func_80106CF0_slot_synch(s16 team);
void func_8010A1D0_slot_synch(void);
void func_8010A39C_slot_synch(void);
void func_8010A480_slot_synch(s16 idx, s16 file0, s16 file1, s16 target);
void func_8010AAB8_slot_synch(void);
void func_8010AF38_slot_synch(void);
void func_8010C3FC_slot_synch(omObjData *obj, u32 value);
void *func_8010C428_slot_synch(omObjData *obj);
s16 func_80108A7C_slot_synch(s16 idx);
s16 func_80108AA8_slot_synch(s16 idx);
s16 func_80108C88_slot_synch(s16 idx, s16 face);
void func_801089F8_slot_synch(s16 idx);
void func_80108CD0_slot_synch(s16 idx);
void func_8010800C_slot_synch(u8 sym, u8 team);
s16 func_80109FA4_slot_synch(s16 player, s16 arg1);
s16 func_8010A178_slot_synch(s16 idx);
void func_8010AA9C_slot_synch(s16 idx, s16 target);
f32 func_8010C384_slot_synch(f32 t, f32 a, f32 b);
void func_80108428_slot_synch(omObjData* obj);
s16 func_80108848_slot_synch(s16 idx);
s32 func_8010AD68_slot_synch(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color);
f64 fabs(f64);
f32 fabsf(f32);
void func_801091D8_slot_synch(omObjData* obj);
void func_801092B8_slot_synch(SsBody* b);
void func_80107794_slot_synch(omObjData* obj);
void func_80107A80_slot_synch(omObjData* obj);
void func_80107A88_slot_synch(void);
s16 func_80107B00_slot_synch(f32 x, f32 y, u8 gfx, u8 team, u16 prio);
void func_80107BAC_slot_synch(void);
void func_80107D54_slot_synch(omObjData* obj);
void func_80108238_slot_synch(void);
void func_80108D3C_slot_synch(void);
void func_80109754_slot_synch(omObjData* obj);
s16 func_8010C47C_slot_synch(s32 dirAndFile);
f32 func_8010C1C4_slot_synch(f32 target, f32 cur, f32 step);
void func_80106CCC_slot_synch(s16 team, s16 add);
void func_80106D0C_slot_synch(s16 team, s16 kind);
s16 func_80108B74_slot_synch(s16 idx, s16 steps);
void func_80108D14_slot_synch(s16 idx, s16 sym);
u16 func_8010A2C4_slot_synch(s32 dirAndFile);
void func_8010A308_slot_synch(s16 grp, s16 member, f32 x, f32 y);
void func_800E1304_minigame(omObjData* obj, f32 arg1);
void func_800E1310_minigame(omObjData* obj, f32 arg1);
void func_800E131C_minigame(omObjData* obj, f32 arg1);
void func_800E139C_minigame(omObjData* obj, f32 arg1, f32 minX, f32 minZ, f32 maxX, f32 maxZ);
void func_800E1490_minigame(s32);
extern u8 D_800D2008_main;
extern u8 D_800D6A90_main;
void func_800DDD94_minigame(omObjData* obj);
omObjData* func_80045F1C_main(u32, s16, s16);
s32 func_80017BB8_main(s16, s16);
extern s16 D_800CDA7C_main[];
extern u16 D_800D5558_main[];

void func_8000B5F0_main(u8);
u8 func_8000B638_main(void);
void func_8004AD70_main(void);
void func_800E6F0C_minigame(s32);
void func_800E18D8_minigame(void);
void func_800E19F0_minigame(s8);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);

extern s32 D_800A178C_main[][6];

extern omObjData* D_8010DF40_slot_synch;
extern s32 D_8010DF44_slot_synch;
extern s32 D_8010DF48_slot_synch;
extern s32 D_8010DF4C_slot_synch;
extern s32 D_8010DF50_slot_synch;
extern s32 D_8010DF54_slot_synch;
extern s32 D_8010DF58_slot_synch;
extern SsTeam* D_8010DF5C_slot_synch;
extern SsPlayer* D_8010DF60_slot_synch;
extern s16 D_8010DF64_slot_synch;
extern u16 D_8010DF66_slot_synch[4]; /* sprite priorities */
extern SsSprMan D_8010DF70_slot_synch;
extern SsReel* D_8010DF7C_slot_synch;
extern SsBody* D_8010DF80_slot_synch;
extern omObjData* D_8010DF84_slot_synch;
extern SsPop* D_8010DF88_slot_synch;
extern s16* D_8010DF8C_slot_synch; /* sprite files, 0x20 */
extern D_80111B50_vine_with_me_Struct D_8010DFF8_slot_synch;
// end m1 sy1

// m1 sy2

typedef struct SsCounter {
    /* 0x00 */ s16 grp;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 unk6[2];
    /* 0x0A */ s16 value;
    /* 0x0C */ s16 target;
    /* 0x0E */ s16 timer;
} SsCounter; // Size 0x10

typedef struct SsEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ RGBA color;
    /* 0x08 */ f32 frame;
    /* 0x0C */ f32 speed;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec vel;
    /* 0x28 */ Vec scale;
} SsEffect; // Size 0x34

typedef struct SsCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} SsCamera; // Size 0x24

typedef struct SsBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} SsBytes;

typedef union SsPack {
    void *p;
    SsBytes b;
} SsPack;

#define SS_WRAP(v)             \
    if ((v) >= 360.0) {        \
        (v) -= 360.0;          \
    } else if ((v) < 0.0) {    \
        (v) += 360.0;          \
    }

extern s16 D_800CDD6A_main;
extern omObjData *D_8010DF94_slot_synch;
extern s32 fontcolor;
extern SsCamera D_8010DFA0_slot_synch[2];
extern s32 D_8010DFE8_slot_synch;
extern s32 D_8010DFEC_slot_synch;
extern s32 D_8010DFF0_slot_synch;
extern SsEffect *D_8010DF98_slot_synch;
extern SsCounter *D_8010DF90_slot_synch;

/* .data (0x8010D7F0..0x8010DBA0). Inner labels the remaining asm uses are undefined_syms.txt aliases. */
Vec D_8010D7F0_slot_synch[4] = { /* D_8010D7F8 = [0].z */
    { -300.0f, 0.0f, 0.0f }, { -125.0f, 0.0f, -0.0f }, { 125.0f, 0.0f, -0.0f }, { 300.0f, 0.0f, 0.0f },
};
Vec D_8010D820_slot_synch[2] = { /* D_8010D824 = [0].y, D_8010D828 = [0].z */
    { -255.0f, 0.0f, -300.0f },
    { 255.0f, 0.0f, -300.0f },
};
s16 D_8010D838_slot_synch[2][2] = { { 70, 40 }, { 250, 40 } }; /* counter positions; D_8010D83A = [0][1] */
f32 D_8010D840_slot_synch[5] = { 0.0f, 90.0f, 180.0f, 270.0f, 0.0f };
u8 D_8010D854_slot_synch[2][4] = { { 0, 1, 2, 3 }, { 2, 3, 1, 0 } }; /* reel strips */
s16 D_8010D85C_slot_synch[4] = { 3, 1, 2, -1 };
RGBA D_8010D864_slot_synch = { 0xE9, 0xDD, 0xA1, 0x80 };
RGBA D_8010D868_slot_synch = { 0xFF, 0xFF, 0xFF, 0x80 };
RGBA D_8010D86C_slot_synch = { 0xFF, 0xFF, 0xFF, 0xFF };
s32 D_8010D870_slot_synch[8] = { 0x200A5, 0x300A5, 0x700A5, 0x400A5, 0x500A5, 0x600A5, 0x800A5, 0x9001C };
s32 D_8010D890_slot_synch[8] = { 0x200A6, 0x300A6, 0x700A6, 0x400A6, 0x500A6, 0x600A6, 0x800A6, 0x9001D };
s32 D_8010D8B0_slot_synch = 0; /* D_8010D8B2 = its low half */
s32 D_8010D8B4_slot_synch[4] = { 0, 1, 2, 3 };
s16 D_8010D8C4_slot_synch[4][2][2] = { { { 0, 1 }, { 2, 3 } }, { { 3, 0 }, { 1, 2 } }, { { 2, 3 }, { 0, 1 } }, { { 1, 2 }, { 3, 0 } } };
s16 D_8010D8E4_slot_synch[4] = { 0x12, 0x13, 0x15, 0x14 };
s32 D_8010D8EC_slot_synch[8] = { 0x20000, 0x30000, 0x70000, 0x40000, 0x50000, 0x60000, 0x80000, 0x90000 };
s32 D_8010D90C_slot_synch[4] = { 0x2F, 0x30, 0x36, 0x37 }; /* D_8010D910 = [1], D_8010D912/D_8010D916 = low halves of [1]/[2] */
u16 D_8010D91C_slot_synch[6] = { 0, 2, 1, 3, 0, 0 };
u16 D_8010D928_slot_synch[8] = { 3, 3, 3, 3, 2, 3, 3, 0 };
SsSprPos D_8010D938_slot_synch[12] = { /* D_8010D93A = [0].y, D_8010D93D = [0].unk05 */
    { 0x10, 0x5C, 0, 0 }, { 0x28, 0x5C, 0, 1 }, { 0x40, 0x5C, 0, 2 }, { 0x58, 0x5C, 0, 3 },
    { 0x1E, 0x6C, 0, 3 }, { 0x36, 0x6C, 0, 2 }, { 0x4E, 0x6C, 0, 1 }, { 0x66, 0x6C, 0, 0 },
    { 0x10, 0x7C, 0, 3 }, { 0x28, 0x7C, 0, 0 }, { 0x40, 0x7C, 0, 1 }, { 0x58, 0x7C, 0, 2 },
};
SsSprPos D_8010D980_slot_synch[12] = { /* D_8010D982 = [0].y, D_8010D985 = [0].unk05 */
    { 0x130, 0x5C, 0, 0 }, { 0x118, 0x5C, 0, 1 }, { 0x100, 0x5C, 0, 2 }, { 0xE8, 0x5C, 0, 3 },
    { 0x122, 0x6C, 0, 3 }, { 0x10A, 0x6C, 0, 2 }, { 0xF2, 0x6C, 0, 1 }, { 0xDA, 0x6C, 0, 0 },
    { 0x130, 0x7C, 0, 3 }, { 0x118, 0x7C, 0, 0 }, { 0x100, 0x7C, 0, 1 }, { 0xE8, 0x7C, 0, 2 },
};
s16 D_8010D9C8_slot_synch[4] = { 0, 1, 1, 0 }; /* reel strip per reel */
f32 D_8010D9D0_slot_synch[8] = { 150.0f, 150.0f, 150.0f, 150.0f, 150.0f, 180.0f, 150.0f, 150.0f };
s32 D_8010D9F0_slot_synch[4] = { 0xA0000, 0xA00A5, 0xA008E, 0xA00EE };
s32 D_8010DA00_slot_synch[4] = { 0xA0018, 0xA00B3, 0xA00A0, 0xA00FA };
s32 D_8010DA10_slot_synch[4] = { 0xA0002, 0xA00A9, 0xA0090, 0xA00F1 };
f32 D_8010DA20_slot_synch[4] = { 1.5f, 1.75f, 1.0f, 1.2f };
s32 D_8010DA30_slot_synch[4] = { 0x393, 0x391, 0x392, 0x394 }; /* D_8010DA32 = low half of [0] */
s32 D_8010DA40_slot_synch[8] = { 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
s32 D_8010DA60_slot_synch = 0; /* debug camera mode */
s32 D_8010DA64_slot_synch = 0; /* debug text x; D_8010DA66 = low half */
s32 D_8010DA68_slot_synch = 0; /* debug text y; D_8010DA6A = low half */
s32 D_8010DA6C_slot_synch = 0;

Gfx D_8010DA70_slot_synch[] = {
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

Gfx D_8010DB28_slot_synch[] = {
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx D_8010DB48_slot_synch[] = {
    gsSPDisplayList(D_8010DB28_slot_synch),
    gsSPDisplayList(D_8010DA70_slot_synch),
    gsSPEndDisplayList(),
};

Gfx D_8010DB60_slot_synch[] = {
    gsDPPipeSync(),
    gsSPDisplayList(D_8010DB48_slot_synch),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

void func_801094E0_slot_synch(s16 idx, f32 height, f32 speed);
void func_8010A7D0_slot_synch(omObjData *obj);
void func_8010AC14_slot_synch(omObjData *obj);
s32 func_8010C4C0_slot_synch(HuSprite_Unk84_Struct *arg0, RGBA *arg1);
s32 func_8010D0A8_slot_synch(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2);
void func_8010B754_slot_synch(omObjData *obj);
void func_8010BB90_slot_synch(s32 idx);
void func_8010BD7C_slot_synch(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
void func_8010BF6C_slot_synch(s32 idx);
f32 func_8010C0C0_slot_synch(f32 a, f32 b);
f32 func_8010C39C_slot_synch(f32 t, f32 a, f32 b);
f64 fmod(f64, f64);
s32 func_8010D3E0_slot_synch(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8010D2AC_slot_synch(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3);

// end m1 sy2


void func_801059A0_slot_synch(void) {
    u8 cam;

    Hu3DAnimInit(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(0x40);
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
    D_8010DF50_slot_synch = 900;
    D_8010DF4C_slot_synch = 0;
    D_8010DF48_slot_synch = 0;
    D_8010DF54_slot_synch = 0;
    D_8010DF58_slot_synch = 0;
    D_8010DF64_slot_synch = -1;
    D_8010DF8C_slot_synch = HuMemAllocTag(0x40, 31000);
    D_8010DF40_slot_synch = omAddObj(0x20, 0, 0, -1, func_80105B98_slot_synch);
    memset(&D_8010DFF8_slot_synch, 0, 0x28);
    D_8010DFF8_slot_synch.unk01 = 4;
    func_800E5EA0_minigame(&D_8010DFF8_slot_synch);
}

void func_80105B98_slot_synch(omObjData* obj) {
    obj->func = func_80105C08_slot_synch;
    func_8010A39C_slot_synch();
    func_80109508_slot_synch();
    func_801075D4_slot_synch();
    func_8010AAB8_slot_synch();
    func_8010614C_slot_synch();
    func_8010AF38_slot_synch();
    if (_CheckFlag(0xA) != 0) {
        D_8010DF44_slot_synch = 1;
    }
    WipeCreateIn(0xFF, 0x10);
}

void func_80105C08_slot_synch(omObjData* obj) {
    SsTeam* t0 = D_8010DF5C_slot_synch;
    SsTeam* t1 = t0 + 1;

    switch (D_8010DF54_slot_synch) {
    case 0:
        if (WipeStatGet() == 0) {
            GMesCreate(5);
            HuAudFXPlay(0xE);
            D_8010DF54_slot_synch++;
            D_8010DF4C_slot_synch = 0;
        }
        break;
    case 1:
        if (D_8010DF4C_slot_synch == 30) {
            HuAudSeqPlay(0x2E);
        }
        if (GMesStatGet() == 0) {
            GMesCreate(0x1A, (D_8010DF50_slot_synch + 29) / 30, 0x9C, 0x20);
            func_800E6F0C_minigame(2);
            D_8010DF54_slot_synch++;
        }
        break;
    case 2:
        func_8003F578_main((D_8010DF50_slot_synch-- + 28) / 30);
        if (D_8010DF50_slot_synch <= 0) {
            func_8004AD70_main();
            func_8003F5C0_main();
            GMesCreate(0x10);
            func_800E6F0C_minigame(3);
            HuAudSeqFadeOut(0x78);
            D_8010DF50_slot_synch = 0;
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    case 3:
        if (GMesStatGet() == 0 && func_80106CF0_slot_synch(0) == 0 && func_80106CF0_slot_synch(1) == 0) {
            func_800E6F0C_minigame(4);
            func_8010A1D0_slot_synch();
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    case 4:
        if (D_8010DF4C_slot_synch >= 15) {
            if (t0->unk16 > t1->unk16) {
                GMesCreate(0x1E, t0->unk08->unk20, t0->unk0C->unk20);
                GwPlayer[t0->unk08->unk1C].bonusCoin += 10;
                GwPlayer[t0->unk0C->unk1C].bonusCoin += 10;
                t0->unk08->unk04 = t0->unk0C->unk04 = 0;
                t1->unk08->unk04 = t1->unk0C->unk04 = 1;
                HuAudSeqPlay(0x66);
                D_8010DF58_slot_synch = 0x8C;
            } else if (t0->unk16 < t1->unk16) {
                GMesCreate(0x1E, t1->unk08->unk20, t1->unk0C->unk20);
                GwPlayer[t1->unk08->unk1C].bonusCoin += 10;
                GwPlayer[t1->unk0C->unk1C].bonusCoin += 10;
                t0->unk08->unk04 = t0->unk0C->unk04 = 1;
                t1->unk08->unk04 = t1->unk0C->unk04 = 0;
                HuAudSeqPlay(0x66);
                D_8010DF58_slot_synch = 0x8C;
            } else {
                GMesCreate(0x20);
                t0->unk08->unk04 = t0->unk0C->unk04 = 1;
                t1->unk08->unk04 = t1->unk0C->unk04 = 1;
                HuAudSeqPlay(0x6C);
                D_8010DF58_slot_synch = 0x90;
            }
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    case 5:
        if (GMesStatGet() == 0) {
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    case 6:
        if (D_8010DF4C_slot_synch >= 15) {
            WipeCreateOut(0, 0x10);
            HuAudSeqFadeOut(0x10);
            func_8004AB0C_main(0x10);
            D_8010DF4C_slot_synch = 0;
            D_8010DF54_slot_synch++;
        }
        break;
    default:
        if (WipeStatGet() == 0) {
            obj->func = func_80106080_slot_synch;
        }
        break;
    }
    func_801060A4_slot_synch(obj);
    D_8010DF48_slot_synch++;
    D_8010DF4C_slot_synch++;
}

void func_80106080_slot_synch(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_801060A4_slot_synch(omObjData* obj) {
    if (D_8010D8B0_slot_synch != 0) {
        if (D_8010D8B0_slot_synch == 1) {
            obj->func = func_80106080_slot_synch;
        }
        D_8010D8B0_slot_synch--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010D8B0_slot_synch = 0x10;
        WipeCreateOut(0, (s16)D_8010D8B0_slot_synch);
        HuAudSeqFadeOut((s16)D_8010D8B0_slot_synch);
        func_8004AB0C_main((s16)D_8010D8B0_slot_synch);
    }
}

#ifdef NON_MATCHING
void func_8010614C_slot_synch(void) {
    s32 grp[2][2];
    s32 g;
    SsTeam* team;
    SsPlayer* pl;
    omObjData* o;
    s32 bad;
    s32 n0;
    s32 n1;
    s32 i;
    s32 j;
    s32 tmp;
    s32 r;

    team = D_8010DF5C_slot_synch = HuMemAllocTag(sizeof(SsTeam) * 2, 31000);
    D_8010DF60_slot_synch = HuMemAllocTag(sizeof(SsPlayer) * 4, 31000);
    memset(D_8010DF60_slot_synch, 0, sizeof(SsPlayer) * 4);
    bad = 0;
    n1 = 0;
    n0 = 0;
    for (i = 0; i < 4; i++) {
        g = GwPlayer[D_8010D8B4_slot_synch[i]].group;
        switch (g) {
        case 0:
            if (n0 < 2) {
                grp[g][n0++] = D_8010D8B4_slot_synch[i];
            } else {
                bad = 1;
            }
            break;
        case 1:
            if (n1 < 2) {
                grp[g][n1++] = D_8010D8B4_slot_synch[i];
            } else {
                bad = 1;
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
        r = rand8() & 3;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                grp[i][j] = D_8010D8C4_slot_synch[r][i][j];
            }
        }
    } else {
        if (rand8() & 1) {
            tmp = grp[0][0];
            grp[0][0] = grp[0][1];
            grp[0][1] = tmp;
        }
        if (rand8() & 1) {
            tmp = grp[1][0];
            grp[1][0] = grp[1][1];
            grp[1][1] = tmp;
        }
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    for (i = 0; i < 2; i++, team++) {
        func_8010C3FC_slot_synch(omAddObj(i + 0x10, 0, 0, -1, func_80106878_slot_synch), (u32)team);
        team->unk10 = i;
        team->unk12 = 0;
        team->unk14 = 0;
        team->unk16 = 0;
        team->unk18 = -1;
        team->unk1A = -1;
        team->unk1C = 0;
        team->unk1E = -1;
        for (j = 0; j < 2; j++) {
            pl = &D_8010DF60_slot_synch[i * 2 + j];
            pl->unk00 = i * 2 + j;
            pl->unk02 = i;
            pl->unk1C = grp[i][j];
            o = D_800EC598_minigame[D_800EC280_minigame] = omAddObj(D_8010D8E4_slot_synch[pl->unk00], 9, 60, -1, func_80106560_slot_synch);
            D_800EC280_minigame++;
            o->trans.x = D_8010D7F0_slot_synch[pl->unk00].x;
            o->trans.z = D_8010D7F0_slot_synch[pl->unk00].z;
            if (j == 0) {
                team->unk00 = o;
                team->unk08 = pl;
            } else {
                team->unk04 = o;
                team->unk0C = pl;
            }
            func_8010C3FC_slot_synch(o, (u32)pl);
        }
        func_8010A480_slot_synch(i, GwPlayer[team->unk08->unk1C].chr, GwPlayer[team->unk0C->unk1C].chr, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010614C_slot_synch);
#endif

#ifdef NON_MATCHING
void func_80106560_slot_synch(omObjData* obj) {
    SsPlayer* pl;
    func_800E1BA8_minigame_ObjData* w;
    s32* msg;
    s16 chr;
    s16 idx;
    s32 dir;
    s32 r;
    s32 file;

    pl = func_8010C428_slot_synch(obj);
    idx = pl->unk1C;
    pl->unk20 = chr = GwPlayer[idx].chr;
    pl->unk1E = GwPlayer[idx].pad;
    pl->unk22 = GwPlayer[idx].stat & 1;
    pl->unk24 = GwPlayer[idx].cpu_difficulty;
    pl->unk26 = 0;
    pl->unk28 = 0;
    pl->unk2A = 0;
    pl->unk2C = -1;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(obj, dir, file, idx, 0x2A9, 0x299);
    w = obj->data;
    w->unk50 &= ~1;
    w->unkEC = NULL;
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 0x26, func_80017BB8_main(chr, 0x33), 1, 0x3C);
    func_800E5A00_minigame(obj, 0x27, func_80017BB8_main(chr, 0x3A), 1, 0x3C);
    if (chr != 5) {
        r = rand8() & 1;
        msg = &D_8010D90C_slot_synch[r];
        func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, *msg), 1, 0x78);
        pl->unk18 = D_8010D8EC_slot_synch[chr] | *msg;
    } else {
        func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, D_8010D90C_slot_synch[1]), 1, 0x78);
        pl->unk18 = D_8010D8EC_slot_synch[chr] | D_8010D90C_slot_synch[1];
    }
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, D_8010D90C_slot_synch[2]), 1, 0x78);
    func_800E5690_minigame(obj, 0);
    func_800E149C_minigame(obj, 0, 2);
    pl->unk04 = -1;
    pl->unk0A = 0;
    pl->unk08 = 0;
    pl->unk0C = pl->unk10 = pl->unk14 = 0.0f;
    obj->func = func_80106E8C_slot_synch;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106560_slot_synch);
#endif

void func_80106878_slot_synch(omObjData* obj) {
    SsTeam* t;
    SsReel* reel;
    func_800E1BA8_minigame_ObjData* w0;
    func_800E1BA8_minigame_ObjData* w1;
    s16 a;
    s16 b;

    t = func_8010C428_slot_synch(obj);
    switch (t->unk12) {
    case 0:
        if (func_800E6E8C_minigame() == 2) {
            func_801089F8_slot_synch(t->unk08->unk00);
            func_801089F8_slot_synch(t->unk0C->unk00);
            reel = &D_8010DF7C_slot_synch[t->unk08->unk00];
            if (reel->unk20 != -1) {
                HuAudFXStop((s16)reel->unk20);
                reel->unk20 = -1;
            }
            reel->unk20 = HuAudFXPlay(t->unk10 == 0 ? 0x38F : 0x395);
            t->unk14 = 0;
            t->unk12 = 1;
        } else if (func_800E6E8C_minigame() == 3 || func_800E6E8C_minigame() == 4) {
            func_80108CD0_slot_synch(t->unk08->unk00);
            func_80108CD0_slot_synch(t->unk0C->unk00);
        }
        break;
    case 1:
        if (func_800E6E8C_minigame() != 2) {
            t->unk1C = 0;
            t->unk14 = 0;
            t->unk12 = 0;
        }
        if (t->unk14 >= 30) {
            t->unk1C = 1;
            t->unk14 = 0;
            t->unk12 = 2;
        }
        break;
    case 2:
        if (func_80108A7C_slot_synch(t->unk08->unk00) != 0 && func_80108A7C_slot_synch(t->unk0C->unk00) != 0) {
            if (func_800E6E8C_minigame() == 2) {
                reel = &D_8010DF7C_slot_synch[t->unk08->unk00];
                if (reel->unk20 != -1) {
                    HuAudFXStop((s16)reel->unk20);
                    reel->unk20 = -1;
                }
            }
            t->unk1C = 0;
            a = func_80108AA8_slot_synch(t->unk08->unk00);
            b = func_80108AA8_slot_synch(t->unk0C->unk00);
            if (func_800E6E8C_minigame() == 3) {
                func_80108CD0_slot_synch(t->unk08->unk00);
                func_80108CD0_slot_synch(t->unk0C->unk00);
            }
            if (a == b) {
                t->unk1A = a;
            } else {
                t->unk1A = 4;
            }
            t->unk18 = func_80109FA4_slot_synch(t->unk10, t->unk1A);
            t->unk14 = 0;
            t->unk12 = 3;
        } else if (func_800E6E8C_minigame() != 2) {
            t->unk1C = 0;
            w0 = t->unk00->data;
            w1 = t->unk04->data;
            if (w0->unk38 == 1000.0f && w1->unk38 == 1000.0f) {
                if (func_800E6E8C_minigame() == 3) {
                    func_80108CD0_slot_synch(t->unk08->unk00);
                    func_80108CD0_slot_synch(t->unk0C->unk00);
                }
                t->unk14 = 0;
                t->unk12 = 0;
            }
        }
        break;
    case 3:
        if (func_8010A178_slot_synch(t->unk18) != 0) {
            if (t->unk1A != 4) {
                func_8010800C_slot_synch(t->unk1A, t->unk10);
            }
            if (t->unk1A != 3 && t->unk1A != 4) {
                func_800E5690_minigame(t->unk00, 0x26);
                func_800E5690_minigame(t->unk04, 0x26);
            } else {
                func_800E5690_minigame(t->unk00, 0x27);
                func_800E5690_minigame(t->unk04, 0x27);
            }
            t->unk14 = 0;
            t->unk12 = 4;
        }
        break;
    case 4:
        if (t->unk14 >= 30.0f) {
            func_800E5690_minigame(t->unk00, 0);
            func_800E5690_minigame(t->unk04, 0);
            t->unk14 = 0;
            t->unk12 = 0;
        }
        break;
    }
    t->unk14++;
    if (t->unk16 >= 100) {
        t->unk16 = 99;
    } else if (t->unk16 < 0) {
        t->unk16 = 0;
    }
    func_8010AA9C_slot_synch(t->unk10, t->unk16);
}

void func_80106CCC_slot_synch(s16 team, s16 add) {
    SsTeam* t = &D_8010DF5C_slot_synch[team];
    t->unk16 += add;
}

s16 func_80106CF0_slot_synch(s16 team) {
    SsTeam* t = &D_8010DF5C_slot_synch[team];
    return t->unk12;
}

void func_80106D0C_slot_synch(s16 team, s16 kind) {
    SsTeam* t = &D_8010DF5C_slot_synch[team];

    switch (kind) {
    case 1:
        omVibrate(t->unk08->unk1C, 5, 0, 5);
        omVibrate(t->unk0C->unk1C, 5, 0, 5);
        break;
    case 2:
        omVibrate(t->unk08->unk1C, 2, 3, 10);
        omVibrate(t->unk0C->unk1C, 2, 3, 10);
        break;
    case 3:
        omVibrate(t->unk08->unk1C, 10, 0, 10);
        omVibrate(t->unk0C->unk1C, 10, 0, 10);
        break;
    case 4:
        omVibrate(t->unk08->unk1C, 2, 2, 20);
        omVibrate(t->unk0C->unk1C, 2, 2, 20);
        break;
    case 5:
        omVibrate(t->unk08->unk1C, 20, 0, 20);
        omVibrate(t->unk0C->unk1C, 20, 0, 20);
        break;
    default:
        omVibrate(t->unk08->unk1C, 30, 0, 30);
        omVibrate(t->unk0C->unk1C, 30, 0, 30);
        break;
    }
}

#ifdef NON_MATCHING
void func_80106E8C_slot_synch(omObjData* obj) {
    SsPlayer* pl;
    SsTeam* t;
    u16 btn;
    u16 btn2;
    s8 sx;
    s8 sy;

    pl = func_8010C428_slot_synch(obj);
    t = &D_8010DF5C_slot_synch[pl->unk02];
    if (pl->unk22 != 0) {
        func_80107108_slot_synch(obj);
    }
    if (pl->unk04 != -1) {
        switch (pl->unk04) {
        case 0:
            func_800E5690_minigame(obj, 0xD);
            func_80017790_main(obj->model[0], 2, pl->unk20, D_8010D870_slot_synch[pl->unk20]);
            func_80045F1C_main(pl->unk18, -1, pl->unk1C);
            break;
        case 1:
            func_800E5690_minigame(obj, 0xE);
            func_80017790_main(obj->model[0], 2, pl->unk20, D_8010D890_slot_synch[pl->unk20]);
            break;
        }
        pl->unk04 = -1;
    }
    pl->unk0C = obj->trans.x;
    pl->unk10 = obj->trans.y;
    pl->unk14 = obj->trans.z;
    btn2 = 0;
    if ((t->unk1C == 0) | ((func_80108A7C_slot_synch(pl->unk00) == 0) ^ 1)) {
        btn = D_800CDA7C_main[pl->unk1E];
        btn2 = D_800D5558_main[pl->unk1E];
        D_800CDA7C_main[pl->unk1E] = 0;
        D_800D5558_main[pl->unk1E] = 0;
    } else {
        btn = 0;
    }
    sx = (u8)D_800CBB6E_main[pl->unk1E];
    sy = (u8)D_800D20A1_main[pl->unk1E];
    D_800CBB6E_main[pl->unk1E] = 0;
    D_800D20A1_main[pl->unk1E] = 0;
    func_800DDD94_minigame(obj);
    D_800CBB6E_main[pl->unk1E] = sx;
    D_800D20A1_main[pl->unk1E] = sy;
    if (t->unk1C == 0) {
        D_800CDA7C_main[pl->unk1E] = btn;
        D_800D5558_main[pl->unk1E] = btn2;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    pl->unk0A++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106E8C_slot_synch);
#endif

#ifdef NON_MATCHING
void func_80107108_slot_synch(omObjData* obj) {
    SsPlayer* pl;
    SsTeam* t;
    SsPlayer* mate;
    u16 steps;
    u16 sym;
    s16 a;
    s32 d;

    pl = func_8010C428_slot_synch(obj);
    t = &D_8010DF5C_slot_synch[pl->unk02];
    if (t->unk08 == pl) {
        mate = t->unk0C;
    } else {
        mate = t->unk08;
    }
    D_800CDA7C_main[pl->unk1E] = 0;
    D_800D5558_main[pl->unk1E] = 0;
    steps = D_8010D928_slot_synch[pl->unk20];
    switch (t->unk12) {
    case 0:
        if (pl->unk2C != -1) {
            return;
        }
        if (mate->unk22 == 0) {
            pl->unk2A = 150;
            pl->unk2C = D_8010D91C_slot_synch[(u8)(rand8() % 3)];
            return;
        }
        if ((u8)(rand8() % 100) < pl->unk24 * 15 + 60) {
            pl->unk28 = 0;
        } else {
            pl->unk28 = 1;
        }
        pl->unk2A = (u8)(rand8() % 30) + 75 - pl->unk24 * 12;
        if (t->unk1E == -1) {
            sym = D_8010D91C_slot_synch[(s16)((s16)((f32)(u8)(rand8() % 100) * (1.0f - pl->unk24 * 0.075f)) / 25)];
            pl->unk2C = sym;
            t->unk1E = sym;
        } else {
            pl->unk2C = t->unk1E;
            d = pl->unk2A - mate->unk2A;
            if (d < 0) {
                d = -d;
            }
            if (d < 9.0f) {
                if (mate->unk2A < pl->unk2A) {
                    pl->unk2A = pl->unk2A + 9.0f;
                } else {
                    pl->unk2A = pl->unk2A - 9.0f;
                }
            }
        }
        break;
    case 1:
        pl->unk0A = 0;
        break;
    case 2:
        if (func_80108A7C_slot_synch(pl->unk00) == 0) {
            func_80108AA8_slot_synch(pl->unk00);
            if (pl->unk2A < pl->unk0A) {
                if (pl->unk28 == 0) {
                    a = func_80108B74_slot_synch(pl->unk00, steps);
                    if (a == pl->unk2C) {
                        func_80108D14_slot_synch(pl->unk00, a);
                        D_800D5558_main[pl->unk1E] |= 0x8000;
                    }
                } else if (func_80108B74_slot_synch(pl->unk00, steps) != pl->unk2C) {
                    D_800D5558_main[pl->unk1E] |= 0x8000;
                }
            } else if (mate->unk22 == 0 && func_80108A7C_slot_synch(mate->unk00) != 0) {
                pl->unk0A = 0;
                if (func_80108B74_slot_synch(pl->unk00, steps) == func_80108AA8_slot_synch(mate->unk00)) {
                    func_80108D14_slot_synch(pl->unk00, func_80108AA8_slot_synch(mate->unk00));
                    D_800D5558_main[pl->unk1E] |= 0x8000;
                }
            }
        }
        pl->unk26 = func_80108AA8_slot_synch(pl->unk00);
        break;
    case 3:
        if (pl->unk2C != -1) {
            pl->unk28 = 0;
            pl->unk2A = 0;
            pl->unk2C = -1;
            t->unk1E = -1;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107108_slot_synch);
#endif

#ifdef NON_MATCHING
void func_801075D4_slot_synch(void) {
    omObjData* o;
    s16 i;
    s32 prio;

    prio = 0xFFFF;
    func_80107A88_slot_synch();
    func_80108238_slot_synch();
    func_80108D3C_slot_synch();
    D_8010DF66_slot_synch[0] = prio--;
    D_8010DF66_slot_synch[1] = prio--;
    for (i = 0; i < 12; i++, prio--) {
        func_80107B00_slot_synch(D_8010D938_slot_synch[i].x, D_8010D938_slot_synch[i].y, D_8010D938_slot_synch[i].unk05, 0, prio);
    }
    for (i = 0; i < 12; i++, prio--) {
        func_80107B00_slot_synch(D_8010D980_slot_synch[i].x, D_8010D980_slot_synch[i].y, D_8010D980_slot_synch[i].unk05, 1, prio);
    }
    D_8010DF66_slot_synch[2] = prio--;
    D_8010DF66_slot_synch[3] = prio;
    func_80107BAC_slot_synch();
    o = omAddObj(0x1D, 0x10, 0, -1, func_80107794_slot_synch);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame++] = o;
    func_800E1490_minigame(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801075D4_slot_synch);
#endif

void func_80107794_slot_synch(omObjData* obj) {
    SsGround* gw;
    s16 grp;

    obj->data = gw = HuMemAllocTag(sizeof(SsGround), 31000);
    memset(gw, 0, sizeof(SsGround));
    gw->unk03 = 1;
    gw->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 1.0f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E139C_minigame(obj, 0.0f, -2000.0f, -2000.0f, 2000.0f, 2000.0f);
    grp = HuSprGrpCreate(4, 0);
    D_8010DF8C_slot_synch[3] = func_8010A2C4_slot_synch(0x350007);
    func_80055024_main(grp, 0, D_8010DF8C_slot_synch[3], 0);
    func_80054904_main(grp, 0, 0, 0);
    func_800550F4_main(grp, 0, 0);
    func_80054FF8_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x580C);
    HuSprPriSet(grp, 0, D_8010DF66_slot_synch[0]);
    D_8010DF8C_slot_synch[8] = func_8010A2C4_slot_synch(0x350008);
    func_80055024_main(grp, 1, D_8010DF8C_slot_synch[8], 0);
    func_80054904_main(grp, 1, 0, 0x54);
    func_800550F4_main(grp, 1, 0);
    func_80054FF8_main(grp, 1, 0);
    HuSprAttrSet(grp, 1, 0x580C);
    HuSprPriSet(grp, 1, D_8010DF66_slot_synch[1]);
    D_8010DF8C_slot_synch[9] = func_8010A2C4_slot_synch(0x350009);
    func_80055024_main(grp, 2, D_8010DF8C_slot_synch[9], 0);
    func_80054904_main(grp, 2, 0xA0, 0);
    func_800550F4_main(grp, 2, 0);
    func_80054FF8_main(grp, 2, 0);
    HuSprAttrSet(grp, 2, 0x580C);
    HuSprPriSet(grp, 2, D_8010DF66_slot_synch[2]);
    D_8010DF8C_slot_synch[0] = func_8010A2C4_slot_synch(0x35000A);
    func_80055024_main(grp, 3, D_8010DF8C_slot_synch[0], 0);
    func_80054904_main(grp, 3, 0, 0x8A);
    func_800550F4_main(grp, 3, 0);
    func_80054FF8_main(grp, 3, 0);
    HuSprAttrSet(grp, 3, 0x580C);
    HuSprPriSet(grp, 3, D_8010DF66_slot_synch[3]);
    obj->func = func_80107A80_slot_synch;
}

void func_80107A80_slot_synch(omObjData* obj) {
}

void func_80107A88_slot_synch(void) {
    memset(&D_8010DF70_slot_synch, 0, sizeof(SsSprMan));
    D_8010DF70_slot_synch.unk06 = 0;
    D_8010DF70_slot_synch.unk08 = HuMemAllocTag(sizeof(SsSpr) * 24, 31000);
    memset(D_8010DF70_slot_synch.unk08, 0, sizeof(SsSpr) * 24);
    D_8010DF70_slot_synch.unk00 = omAddObj(0x1C, 0, 0, -1, NULL);
}

#ifdef NON_MATCHING
s16 func_80107B00_slot_synch(f32 x, f32 y, u8 gfx, u8 team, u16 prio) {
    SsSpr* spr;
    s16 idx;

    idx = -1;
    if (D_8010DF70_slot_synch.unk00->func == NULL) {
        idx = -1;
        if (D_8010DF70_slot_synch.unk06 < 24) {
            idx = D_8010DF70_slot_synch.unk06;
            spr = &D_8010DF70_slot_synch.unk08[idx];
            spr->unk00 = idx;
            spr->unk06 = gfx;
            spr->unk07 = team;
            spr->unk02 = prio;
            spr->unk24.x = x;
            spr->unk14.x = x;
            spr->unk1C.x = x;
            spr->unk24.y = y;
            spr->unk14.y = y;
            spr->unk1C.y = y;
            spr->unk08 = 0;
            spr->unk0A = 0;
            spr->unk09 = 0;
            spr->unk0B = 0;
            spr->unk0C = 0;
            spr->unk10 = 0;
            D_8010DF70_slot_synch.unk06++;
        }
    }
    return idx;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107B00_slot_synch);
#endif

void func_80107BAC_slot_synch(void) {
    s16 files[4];
    SsSpr* spr;
    s16 grp;
    s16 i;

    files[0] = D_8010DF8C_slot_synch[4] = func_8010A2C4_slot_synch(0x350003);
    files[1] = D_8010DF8C_slot_synch[5] = func_8010A2C4_slot_synch(0x350005);
    files[2] = D_8010DF8C_slot_synch[6] = func_8010A2C4_slot_synch(0x350004);
    files[3] = D_8010DF8C_slot_synch[7] = func_8010A2C4_slot_synch(0x350006);
    grp = D_8010DF70_slot_synch.unk04 = HuSprGrpCreate(D_8010DF70_slot_synch.unk06, 0);
    spr = D_8010DF70_slot_synch.unk08;
    for (i = 0; i < D_8010DF70_slot_synch.unk06; i++, spr++) {
        HuSprScaleSet(grp, spr->unk00, 0.75f, 0.75f);
        func_80055024_main(grp, spr->unk00, files[spr->unk06], 0);
        func_8010A308_slot_synch(grp, spr->unk00, spr->unk24.x, spr->unk24.y);
        func_800550F4_main(grp, spr->unk00, 0);
        func_80054FF8_main(grp, spr->unk00, 0);
        HuSprAttrSet(grp, spr->unk00, 0x4000580C);
        HuSprPriSet(grp, spr->unk00, spr->unk02);
    }
    D_8010DF70_slot_synch.unk00->func = func_80107D54_slot_synch;
}

void func_80107D54_slot_synch(omObjData* obj) {
    SsSpr* spr;
    f32 s;
    s16 i;

    spr = D_8010DF70_slot_synch.unk08;
    for (i = 0; i < D_8010DF70_slot_synch.unk06; i++, spr++) {
        spr->unk1C.x = spr->unk24.x;
        spr->unk1C.y = spr->unk24.y;
        switch (spr->unk08) {
        case 1:
            if (spr->unk0B != 0) {
                spr->unk0B--;
                spr->unk04 = 0;
            } else {
                if (spr->unk0A & 0x80) {
                    spr->unk0A++;
                    if ((spr->unk0A & 0x7F) >= 2) {
                        spr->unk0A = 2;
                    }
                } else {
                    spr->unk0A--;
                    if (!(spr->unk0A & 0x7F)) {
                        spr->unk0A = 0x80;
                    }
                }
                func_80054FF8_main(D_8010DF70_slot_synch.unk04, spr->unk00, (s16)(spr->unk0A & 2));
                s = sindf(spr->unk04 * 25);
                spr->unk24.x = spr->unk14.x;
                spr->unk24.y = spr->unk14.y - fabs(s) * spr->unk10;
                spr->unk09 = 1;
                if (spr->unk04 >= spr->unk0C) {
                    spr->unk04 = 0;
                    spr->unk08++;
                }
            }
            break;
        case 2:
            if (spr->unk24.y < spr->unk14.y - 1.0f) {
                if (spr->unk0A & 0x80) {
                    spr->unk0A++;
                    if ((spr->unk0A & 0x7F) >= 2) {
                        spr->unk0A = 2;
                    }
                } else {
                    spr->unk0A--;
                    if (!(spr->unk0A & 0x7F)) {
                        spr->unk0A = 0x80;
                    }
                }
                func_80054FF8_main(D_8010DF70_slot_synch.unk04, spr->unk00, (s16)(spr->unk0A & 2));
                spr->unk24.y += 1.0f;
            } else {
                func_80054FF8_main(D_8010DF70_slot_synch.unk04, spr->unk00, 0);
                spr->unk24.y = spr->unk14.y;
                spr->unk04 = 0;
                spr->unk08 = 0;
            }
            spr->unk09 = 1;
            break;
        }
        if (spr->unk09 != 0) {
            func_8010A308_slot_synch(D_8010DF70_slot_synch.unk04, spr->unk00, spr->unk24.x, spr->unk24.y);
            spr->unk09 = 0;
        }
        spr->unk04++;
    }
}

void func_8010800C_slot_synch(u8 sym, u8 team) {
    SsSpr* spr;
    s16 i;

    spr = D_8010DF70_slot_synch.unk08;
    for (i = 0; i < D_8010DF70_slot_synch.unk06; i++, spr++) {
        if (spr->unk06 == sym && spr->unk07 == team && spr->unk08 == 0) {
            spr->unk08 = 1;
            spr->unk04 = 0;
            spr->unk0A = 0x80;
            spr->unk0C = (f32)(u8)(rand8() % 100) * 0.01 * 30.0 + 30.0;
            spr->unk0B = rand8() % 22;
            spr->unk10 = (f32)(u8)(rand8() % 100) * 0.01 * 5.0 + 5.0;
        }
    }
}

void func_80108238_slot_synch(void) {
    SsReel* reel;
    s16 mdl1;
    s16 mdl0;
    s16 i;
    s32 m;

    mdl1 = -1;
    mdl0 = -1;
    reel = D_8010DF7C_slot_synch = HuMemAllocTag(sizeof(SsReel) * 4, 31000);
    memset(reel, 0, sizeof(SsReel) * 4);
    for (i = 0; i < 4; i++, reel++) {
        reel->unk03 = D_8010D9C8_slot_synch[i];
        if (reel->unk03 == 0) {
            m = mdl0;
            if (m == -1) {
                reel->unk00 = func_8000B108_main(0x350000, 0xB9);
                mdl0 = reel->unk00;
            } else {
                reel->unk00 = Hu3DModelLink(m);
            }
        } else {
            m = mdl1;
            if (m != -1) {
                reel->unk00 = Hu3DModelLink(m);
            } else {
                reel->unk00 = func_8000B108_main(0x350001, 0xB9);
                mdl1 = reel->unk00;
            }
        }
        reel->unk02 = i;
        reel->unk04 = i % 2;
        reel->unk0A = 0;
        reel->unk05 = 0;
        reel->unk06 = 0;
        reel->unk0C = 0;
        reel->unk10 = 0.0f;
        reel->unk08 = -1;
        reel->unk14 = 0.0f;
        reel->unk18 = 0.5f;
        reel->unk1C = 14.0f;
        reel->unk20 = -1;
        reel->unk24.x = D_8010D7F0_slot_synch[i].x;
        reel->unk24.z = D_8010D7F0_slot_synch[i].z;
        reel->unk24.y = 280.0f;
        reel->unk30.x = 0.0f;
        reel->unk30.y = reel->unk30.z = 0.0f;
    }
    omAddObj(0x1A, 0, 0, -1, func_80108428_slot_synch);
}

void func_80108428_slot_synch(omObjData* obj) {
    SsReel* reel;
    Vec pos;
    f32 a;
    s32 i;
    s32 j;

    reel = D_8010DF7C_slot_synch;
    i = 0;
    do {
        switch (reel->unk0C) {
        case 0:
        case 2:
        case 5:
            break;
        case 1:
            reel->unk14 += reel->unk18;
            if (reel->unk14 >= reel->unk1C) {
                reel->unk14 = reel->unk1C;
                reel->unk0C = 2;
                reel->unk0A = 0;
            }
            break;
        case 3:
            reel->unk24.y += reel->unk10;
            reel->unk10 -= 6.0;
            if (reel->unk24.y <= 280.0) {
                reel->unk24.y = 280.0f;
                reel->unk0A = 0;
                reel->unk0C = 0;
            }
            break;
        case 4:
            func_8001C258_main(reel->unk00, 4, 4);
            pos.x = reel->unk24.x;
            pos.y = reel->unk24.y;
            pos.z = reel->unk24.z;
            func_8010AD68_slot_synch(&pos, NULL, NULL, 1.0f, &D_8010D86C_slot_synch);
            reel->unk0C = 5;
            break;
        }
        a = reel->unk30.x + 45.0f;
        if (a > 360.0f) {
            a -= 360.0f;
        } else if (a < 0.0f) {
            a += 360.0f;
        }
        reel->unk05 = a / 90.0f;
        if (reel->unk05 >= 4) {
            reel->unk05 -= 4;
        }
        reel->unk06 = func_80108C88_slot_synch(reel->unk02, reel->unk05);
        reel->unk30.x += reel->unk14;
        if (reel->unk30.x >= 360.0f) {
            reel->unk30.x -= 360.0f;
        }
        if (func_80108848_slot_synch(reel->unk02) != -1 && (reel->unk0C == 1 || reel->unk0C == 2)) {
            func_8004AC98_main(0x38E, i);
            if (reel->unk08 == -1) {
                reel->unk14 = 0.0f;
                reel->unk30.x = D_8010D840_slot_synch[reel->unk05];
            } else {
                reel->unk14 = 0.0f;
                for (j = 0; j < 4; j++) {
                    reel->unk30.x = j * 90;
                    a = reel->unk30.x + 45.0f;
                    if (a > 360.0f) {
                        a -= 360.0f;
                    } else if (a < 0.0f) {
                        a += 360.0f;
                    }
                    reel->unk05 = a / 90.0f;
                    if (reel->unk05 >= 4) {
                        reel->unk05 -= 4;
                    }
                    reel->unk06 = func_80108C88_slot_synch(reel->unk02, reel->unk05);
                    if (reel->unk06 == reel->unk08) {
                        break;
                    }
                }
            }
            reel->unk24.y = 340.0f;
            reel->unk10 = 0.0f;
            reel->unk08 = -1;
            reel->unk0A = 0;
            reel->unk0C = 3;
        }
        i++;
        Hu3DModelPosSet(reel->unk00, reel->unk24.x, reel->unk24.y, reel->unk24.z);
        Hu3DModelRotSet(reel->unk00, reel->unk30.x, reel->unk30.y, reel->unk30.z);
        reel->unk0A++;
        reel++;
    } while (i < 4);
}

s16 func_80108848_slot_synch(s16 idx) {
    SsReel* reel;
    omObjData* o;
    func_800E1BA8_minigame_ObjData* w;
    SsPlayer* pl;
    f32 h;
    s32 i;

    reel = &D_8010DF7C_slot_synch[idx];
    for (i = 0; i < 4; i++) {
        o = D_800EC598_minigame[i];
        w = o->data;
        pl = func_8010C428_slot_synch(o);
        if (fabs(o->trans.x - reel->unk24.x) > 50.0 || fabs(o->trans.x - reel->unk24.x) > 50.0) {
            continue;
        }
        if (reel->unk0C == 1 || reel->unk0C == 2) {
            h = D_8010D9D0_slot_synch[pl->unk20];
        } else {
            h = D_8010D9D0_slot_synch[pl->unk20] + 50.0;
        }
        if (reel->unk24.y <= h + o->trans.y && h + pl->unk10 <= reel->unk24.y) {
            o->trans.y = reel->unk24.y - D_8010D9D0_slot_synch[pl->unk20] * 1.1;
            w->unk38 = 0.0f;
            return i;
        }
    }
    return -1;
}

// decomp-permuter
void func_801089F8_slot_synch(s16 idx)
{
  SsReel *reel = &D_8010DF7C_slot_synch[idx];
  float new_var;
  if (func_80108A7C_slot_synch(idx) != 0)
  {
    new_var = D_8010DF50_slot_synch / 900.0f;
    reel->unk1C = func_8010C384_slot_synch(new_var, 30.0f, 14.0f);
    reel->unk0C = 1;
    reel->unk0A = 0;
  }
}

s16 func_80108A7C_slot_synch(s16 idx) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    return reel->unk0C == 0;
}

#ifdef NON_MATCHING
s16 func_80108AA8_slot_synch(s16 idx) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    f32 a = reel->unk30.x + 45.0f;

    if (a > 360.0f) {
        a -= 360.0f;
    } else if (a < 0.0f) {
        a += 360.0f;
    }
    return func_80108C88_slot_synch(idx, a / 90.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108AA8_slot_synch);
#endif

#ifdef NON_MATCHING
s16 func_80108B74_slot_synch(s16 idx, s16 steps) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    f32 a = steps * reel->unk14 + reel->unk30.x + 45.0f;

    while (a > 360.0f) {
        a -= 360.0f;
    }
    while (a < 0.0f) {
        a += 360.0f;
    }
    return func_80108C88_slot_synch(idx, a / 90.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108B74_slot_synch);
#endif

s16 func_80108C88_slot_synch(s16 idx, s16 face) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    return D_8010D854_slot_synch[reel->unk03][face];
}

void func_80108CD0_slot_synch(s16 idx) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];

    if (reel->unk0C != 4 && reel->unk0C != 5) {
        reel->unk0C = 4;
        reel->unk0A = 0;
    }
}

void func_80108D14_slot_synch(s16 idx, s16 sym) {
    SsReel* reel = &D_8010DF7C_slot_synch[idx];
    reel->unk08 = sym;
}

void func_80108D3C_slot_synch(void) {
    s16 ys[256];
    SsBody* b;
    HmfData* hmf;
    Vtx* v;
    SsRow* row;
    s16 n;
    s16 i;
    s16 j;
    s16 k;
    s16 tmp;

    b = D_8010DF80_slot_synch = HuMemAllocTag(sizeof(SsBody) * 2, 31000);
    memset(b, 0, sizeof(SsBody) * 2);
    for (k = 0; k < 2; k++, b++) {
        b->unk00 = func_8000B108_main(0x350002, 0xB9);
        Hu3DModelPosSet(b->unk00, D_8010D820_slot_synch[k].x, D_8010D820_slot_synch[k].y, D_8010D820_slot_synch[k].z);
        Hu3DModelScaleSet(b->unk00, 1.0f, 0.85f, 1.0f);
        func_8001C954_main(b->unk00);
        hmf = HmfModelData[b->unk00].hmf;
        b->unk02 = k;
        b->unk04 = 0;
        b->unk08 = -75.0f;
        b->unk0C = 75.0f;
        b->unk10 = 0.75f;
        b->unk14 = 0.0f;
        if (k == 0) {
            v = hmf->unk40;
            n = 0;
            for (i = 0; i < SS_HMF_VTXNUM(hmf); i++, v++) {
                for (j = 0; j < n; j++) {
                    if (ys[j] == v->v.ob[1]) {
                        break;
                    }
                }
                if (j >= n) {
                    ys[j] = v->v.ob[1];
                    n++;
                }
                if (n >= 256) {
                    osSyncPrintf("VTX OVER!! \n");
                }
            }
            for (i = 0; i < n - 1; i++) {
                for (j = i + 1; j < n; j++) {
                    if (ys[i] < ys[j]) {
                        tmp = ys[i];
                        ys[i] = ys[j];
                        ys[j] = tmp;
                    }
                }
            }
            b->unk18 = n;
            row = b->unk1C = HuMemAllocTag(n * sizeof(SsRow), 31000);
            for (i = 0; i < b->unk18; i++, row++) {
                row->unk90 = ys[i];
                row->unk92 = 0;
            }
            v = hmf->unk40;
            for (i = 0; i < SS_HMF_VTXNUM(hmf); i++, v++) {
                for (j = 0; j < b->unk18; j++) {
                    row = &b->unk1C[j];
                    if (v->v.ob[1] == row->unk90) {
                        row->unk00[row->unk92] = i;
                        row->unk92++;
                        break;
                    }
                    if (row->unk92 >= 72) {
                        osSyncPrintf("VTX H OVER!! \n");
                    }
                }
            }
        } else {
            b->unk18 = D_8010DF80_slot_synch->unk18;
            b->unk1C = D_8010DF80_slot_synch->unk1C;
        }
    }
    omSetStatBit(omAddObj(0x1B, 0, 0, -1, func_801091D8_slot_synch), 0xA0);
}

void func_801091D8_slot_synch(omObjData* obj) {
    SsBody* b;
    s32 i;

    b = D_8010DF80_slot_synch;
    for (i = 0; i < 2; i++, b++) {
        if (func_80049F98_main() + D_800D6A90_main == 0 && b->unk04 == 1) {
            b->unk08 += b->unk14;
            if (b->unk08 >= 359.999990463256836 || b->unk08 <= -120.000004768371582) {
                b->unk14 = 0.0f;
                b->unk04 = 0;
            }
        }
        func_801092B8_slot_synch(b);
    }
}

void func_801092B8_slot_synch(SsBody* b) {
    SsRow* row;
    HmfData* hmf;
    Vtx* base;
    Vtx* cur;
    f32 d;
    f32 s;
    s32 i;
    s32 j;

    row = b->unk1C;
    hmf = HmfModelData[b->unk00].hmf;
    base = hmf->unk40;
    cur = hmf->unk44[D_800D2008_main];
    for (i = 0; i < b->unk18; i++, row++) {
        d = fabsf(b->unk08 - row->unk90 * 0.85f);
        if (b->unk0C < d) {
            s = 0.0f;
        } else {
            s = 1.0f - d / b->unk0C;
        }
        if (s >= 1.0f) {
            s = 1.0f;
        } else if (s <= 0.0f) {
            s = 0.0f;
        }
        if (s != 0.0f) {
            s = s * b->unk10 + 1.0f;
            for (j = 0; j < row->unk92; j++) {
                cur[row->unk00[j]].v.ob[0] = base[row->unk00[j]].v.ob[0] * s;
                cur[row->unk00[j]].v.ob[2] = base[row->unk00[j]].v.ob[2] * s;
            }
        } else {
            for (j = 0; j < row->unk92; j++) {
                cur[row->unk00[j]].v = base[row->unk00[j]].v;
            }
        }
    }
}

void func_801094E0_slot_synch(s16 idx, f32 height, f32 speed) {
    SsBody* b = &D_8010DF80_slot_synch[idx];

    b->unk04 = 1;
    b->unk08 = height;
    b->unk14 = speed;
}

void func_80109508_slot_synch(void) {
    SsPop* p;
    s32 i;
    s32 j;
    s32 mdl;

    p = D_8010DF88_slot_synch = HuMemAllocTag(sizeof(SsPop) * 5, 31000);
    memset(p, 0, sizeof(SsPop) * 5);
    for (i = 0; i < 5; i++, p++) {
        p->unk00 = 0;
        p->unk01 = 0;
        p->unk02 = 0;
        p->unk03 = 0;
        p->unk26 = 0;
        p->unk2A = 0;
        p->unk28 = 0;
        p->unk2C = 0.0f;
        p->unk30 = 0.0f;
        if (i == 0) {
            for (j = 0; j < 4; j++) {
                p->unk04[j] = func_8000B108_main(D_8010D9F0_slot_synch[j], 0x299);
                func_8001C258_main(p->unk04[j], 4, 4);
                p->unk0C[j].unk00 = HmfModelData[p->unk04[j]].unk02;
                p->unk0C[j].unk02 = func_8010C47C_slot_synch(D_8010DA00_slot_synch[j]);
                p->unk0C[j].unk04 = func_8010C47C_slot_synch(D_8010DA10_slot_synch[j]);
            }
            mdl = p->unk24 = func_8000B108_main(9, 0x99);
        } else {
            for (j = 0; j < 4; j++) {
                p->unk04[j] = Hu3DModelLink(D_8010DF88_slot_synch->unk04[j]);
                func_8001C258_main(p->unk04[j], 4, 4);
                p->unk0C[j].unk00 = D_8010DF88_slot_synch->unk0C[j].unk00;
                p->unk0C[j].unk02 = D_8010DF88_slot_synch->unk0C[j].unk02;
                p->unk0C[j].unk04 = D_8010DF88_slot_synch->unk0C[j].unk04;
            }
            mdl = p->unk24 = Hu3DModelLink(D_8010DF88_slot_synch->unk24);
        }
        func_8001C258_main(mdl, 4, 4);
    }
    D_8010DF84_slot_synch = omAddObj(0x19, 0, 6, -1, func_80109754_slot_synch);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DC78_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DC7C_slot_synch);

#ifdef NON_MATCHING
void func_80109754_slot_synch(omObjData* obj) {
    Vec pos;
    Vec vel;
    Vec scale;
    SsPop* p;
    HmfModel* m;
    f32 a;
    f32 s;
    s32 mdl;
    s32 i;
    s32 j;

    p = D_8010DF88_slot_synch;
    if (p == NULL) {
        return;
    }
    for (i = 0; i < 5; i++, p++) {
        if (p->unk00 == 0) {
            continue;
        }
        if (p->unk26 != 4) {
            mdl = p->unk04[p->unk26];
        } else {
            mdl = p->unk04[0];
        }
        m = &HmfModelData[mdl];
        switch (p->unk28) {
        case 0:
            p->unk34.y += 20.000000298023224;
            p->unk4C.x = p->unk4C.y = p->unk4C.z = p->unk34.y / 255.00000715255737;
            if (p->unk34.y >= 0.0f) {
                func_8001C258_main(mdl, 4, 0);
                func_8001C258_main(p->unk24, 4, 0);
            }
            if (p->unk03 == 0 && p->unk34.y > 204.00000876188287) {
                a = (f32)(u8)(rand8() % 100) * 0.01 * 360.0;
                for (j = 0; j < 4; j++) {
                    pos.x = p->unk34.x;
                    pos.y = p->unk34.y;
                    pos.z = p->unk34.z;
                    s = a + j * 90.0f;
                    vel.x = sindf(s) * 100.0 * 0.10000000149011612;
                    vel.z = cosdf(s) * 100.0 * 0.10000000149011612;
                    vel.y = 10.0f;
                    scale.x = scale.y = scale.z = 0.5f;
                    func_8010AD68_slot_synch(&pos, &vel, &scale, 1.0f, &D_8010D868_slot_synch);
                }
                HuAudFXPlay(0x390);
            }
            if (p->unk34.y >= 255.00000715255737) {
                func_8004AC98_main(D_8010DA30_slot_synch[p->unk26], p->unk01);
                func_80106D0C_slot_synch(p->unk01, p->unk26 == 3 ? 4 : 3);
                p->unk34.y = 255.0f;
                p->unk2C = 20.0f;
                p->unk2A = 0;
                p->unk28++;
            }
            break;
        case 1:
            if (m->unk44 == 0.0f && p->unk2C < 0.0f) {
                m->unk44 = 1.0f;
            }
            if (p->unk01 == 0) {
                p->unk34.x += 1.4999999664723873;
            } else {
                p->unk34.x -= 1.4999999664723873;
            }
            p->unk34.z += 10.000000149011612;
            p->unk34.y += p->unk2C;
            p->unk2C -= 1.6333001f;
            if (p->unk34.y <= 0.0f) {
                pos.x = p->unk34.x;
                pos.y = p->unk34.y;
                pos.z = p->unk34.z;
                func_8010AD68_slot_synch(&pos, NULL, NULL, 1.0f, &D_8010D864_slot_synch);
                func_8001C624_main(mdl, p->unk0C[p->unk26].unk02, 0, 5, 2);
                func_80106CCC_slot_synch(p->unk01, D_8010D85C_slot_synch[p->unk26]);
                p->unk02 = 1;
                p->unk34.y = 0.0f;
                p->unk2A = 0;
                p->unk28++;
            }
            break;
        case 2:
            if (p->unk2A >= 7.5f) {
                func_8001C624_main(mdl, p->unk0C[p->unk26].unk04, 0, 5, 2);
                m->unk44 = D_8010DA20_slot_synch[p->unk26];
                p->unk30 = 0.0f;
                p->unk2A = 0;
                p->unk28++;
            }
            break;
        case 3:
            p->unk30 += 3.5000000000000004;
            if (p->unk30 > 15.000000596046448) {
                p->unk30 = 15.000001f;
            }
            if (!(p->unk01 & 1)) {
                p->unk34.x -= p->unk30;
                p->unk40.y = func_8010C1C4_slot_synch(-90.0f, p->unk40.y, 15.0f);
            } else {
                p->unk34.x += p->unk30;
                p->unk40.y = func_8010C1C4_slot_synch(90.0f, p->unk40.y, 15.0f);
            }
            if (fabs(p->unk34.x) >= 600.0) {
                p->unk2A = 0;
                p->unk28 = 0x40;
            }
            break;
        case 0x10:
            p->unk34.y += 20.000000298023224;
            if (p->unk34.y >= 205.00000715255737) {
                pos.x = p->unk34.x;
                pos.y = p->unk34.y;
                pos.z = p->unk34.z;
                vel.z = vel.x = 0.0f;
                vel.y = 10.0f;
                func_8010AD68_slot_synch(&pos, &vel, NULL, 1.0f, &D_8010D86C_slot_synch);
                p->unk34.y = 255.0f;
                p->unk2C = 20.0f;
                func_80106D0C_slot_synch(p->unk01, 2);
                func_80106CCC_slot_synch(p->unk01, 0);
                p->unk02 = 1;
                p->unk2A = 0;
                p->unk28 = 0x40;
            }
            break;
        case 0x40:
            p->unk00 = 0;
            p->unk28 = 0;
            p->unk2A = 0;
            func_8001C258_main(mdl, 4, 4);
            break;
        }
        Hu3DModelPosSet(mdl, p->unk34.x, p->unk34.y, p->unk34.z);
        Hu3DModelRotSet(mdl, p->unk40.x, p->unk40.y, p->unk40.z);
        Hu3DModelScaleSet(mdl, p->unk4C.x, p->unk4C.y, p->unk4C.z);
        s = 1.0 - p->unk34.y / 765.0000214576721;
        if (s < 0.5f) {
            s = 0.5f;
        }
        Hu3DModelPosSet(p->unk24, p->unk34.x, 0.0f, p->unk34.z);
        Hu3DModelScaleSet(p->unk24, s, 1.0f, s);
        p->unk2A++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80109754_slot_synch);
#endif

s16 func_80109FA4_slot_synch(s16 player, s16 arg1) {
    SsPop *pop;
    s32 i;
    s16 model;

    if (D_8010DF88_slot_synch == NULL) {
        return -1;
    }
    pop = D_8010DF88_slot_synch;
    for (i = 0; i < 5; i++, pop++) {
        if (pop->unk00 == 0) {
            pop->unk00 = 1;
            pop->unk01 = player;
            pop->unk02 = 0;
            pop->unk03 = 0;
            pop->unk26 = arg1;
            pop->unk2A = 0;
            pop->unk2C = 0;
            pop->unk34.x = D_8010D820_slot_synch[pop->unk01].x;
            pop->unk34.z = D_8010D820_slot_synch[pop->unk01].z;
            pop->unk34.y = D_8010D820_slot_synch[pop->unk01].y - 20.0000002980232239;
            pop->unk40.x = pop->unk40.y = pop->unk40.z = 0.0f;
            pop->unk4C.x = pop->unk4C.y = pop->unk4C.z = 0.1f;
            if (pop->unk26 != 4) {
                pop->unk28 = 0;
                model = pop->unk04[pop->unk26];
                func_8001C258_main(model, 4, 4);
                HmfModelData[model].unk02 = pop->unk0C[pop->unk26].unk02;
                HmfModelData[model].unk40 = 0.0f;
                HmfModelData[model].unk44 = 0.0f;
                HmfModelData[model].unk03 &= ~2;
            } else {
                pop->unk28 = 0x10;
            }
            func_801094E0_slot_synch(pop->unk01, pop->unk34.y, 20.0f);
            return i;
        }
    }
    return -1;
}

s16 func_8010A178_slot_synch(s16 idx) {
    SsPop *pop;

    if (D_8010DF88_slot_synch == NULL) {
        return 1;
    }
    pop = &D_8010DF88_slot_synch[idx];
    if (pop->unk00 == 0 || pop->unk02 != 0) {
        return 1;
    }
    return 0;
}

void func_8010A1D0_slot_synch(void) {
    SsPop *pop = D_8010DF88_slot_synch;
    s32 i;
    s32 j;

    if (pop != NULL) {
        for (i = 0; i < 5; i++, pop++) {
            for (j = 0; j < 4; j++) {
                HmfModelData[pop->unk04[j]].unk02 = 0xFF;
                func_8001ACDC_main(pop->unk04[j]);
                func_8002D4B8_main(pop->unk0C[j].unk00);
                func_8002D4B8_main(pop->unk0C[j].unk02);
                func_8002D4B8_main(pop->unk0C[j].unk04);
            }
            func_8001ACDC_main(pop->unk24);
        }
        HuMemFree(D_8010DF88_slot_synch);
        D_8010DF88_slot_synch = NULL;
        D_8010DF84_slot_synch->func = NULL;
    }
}

u16 func_8010A2C4_slot_synch(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}

void func_8010A308_slot_synch(s16 grp, s16 member, f32 x, f32 y) {
    HuSprGrp *group = HuSprGrpData[grp];
    HuSprite *spr = HuSprGet(grp, member);

    if (spr->unk_48 != x || spr->unk_4C != y) {
        group->unk_0C = 1;
        spr->unk_48 = x;
        spr->unk_4C = y;
    }
}

void func_8010A39C_slot_synch(void) {
    SsCounter *counter;
    s32 i;

    D_8010DF8C_slot_synch[10] = func_8010A2C4_slot_synch(0x35000C);
    D_8010DF8C_slot_synch[11] = func_8010A2C4_slot_synch(0x35000B);
    D_8010DF8C_slot_synch[12] = func_8010A2C4_slot_synch(0x2D);
    counter = D_8010DF90_slot_synch = HuMemAllocTag(sizeof(SsCounter) * 2, 0x7918);
    for (i = 0; i < 2; i++, counter++) {
        counter->grp = -1;
        counter->x = D_8010D838_slot_synch[i][0];
        counter->y = D_8010D838_slot_synch[i][1];
        counter->unk6[0] = 0;
        counter->unk6[1] = 0;
        counter->value = 0;
        counter->target = 0;
        counter->timer = 0;
    }
    omAddObj(0x1E, 0, 0, -1, func_8010A7D0_slot_synch);
}

void func_8010A480_slot_synch(s16 idx, s16 file0, s16 file1, s16 target) {
    SsCounter *counter = &D_8010DF90_slot_synch[idx];
    s32 grp;
    s32 i;

    D_8010DF8C_slot_synch[idx * 2 + 13] = func_8010A2C4_slot_synch(D_8010DA40_slot_synch[file0]);
    D_8010DF8C_slot_synch[idx * 2 + 14] = func_8010A2C4_slot_synch(D_8010DA40_slot_synch[file1]);
    counter->grp = grp = HuSprGrpCreate(6, 0);
    counter->unk6[0] = -8;
    counter->unk6[1] = 8;
    counter->timer = 0;
    counter->target = 0;
    counter->value = 0;
    func_8010AA9C_slot_synch(idx, target);
    for (i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                HuSprAttrSet(grp, i, 0x8000);
            case 1:
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[12], 0);
                func_80054904_main(grp, i, counter->x + counter->unk6[i], counter->y);
                break;
            case 2:
                func_80054904_main(grp, i, counter->x - 26, counter->y - 9);
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[idx * 2 + 13], 0);
                break;
            case 3:
                func_80054904_main(grp, i, counter->x - 26, counter->y + 8);
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[idx * 2 + 14], 0);
                break;
            case 4:
                func_80054904_main(grp, i, counter->x + 27, counter->y);
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[11], 0);
                break;
            case 5:
                func_80054904_main(grp, i, counter->x, counter->y);
                HuSprScaleSet(grp, i, 1.0f, 1.0f);
                func_80055484_main(grp, i, 0, 0, 0xFF, 0xA0);
                func_80055024_main(grp, i, D_8010DF8C_slot_synch[10], 0);
                break;
        }
        func_800550F4_main(grp, i, 0);
        func_80054FF8_main(grp, i, 0);
        HuSprAttrSet(grp, i, 0x1000);
        HuSprPriSet(grp, i, i - 0x10);
    }
}

void func_8010A7D0_slot_synch(omObjData *obj) {
    SsCounter *counter = D_8010DF90_slot_synch;
    u16 digit[2];
    f32 scale;
    s32 i;

    for (i = 0; i < 2; i++, counter++) {
        digit[0] = counter->value / 10;
        digit[1] = counter->value - digit[0] * 10;
        if (digit[0] >= 10) {
            digit[0] = 9;
        }
        if (digit[1] >= 10) {
            digit[1] = 9;
        }
        func_80054FF8_main(counter->grp, 0, (s16)digit[0]);
        func_80054FF8_main(counter->grp, 1, (s16)digit[1]);
        if (counter->value != counter->target && counter->timer == 0) {
            counter->timer = 15;
            if (counter->value < counter->target) {
                counter->value++;
            } else {
                counter->value--;
            }
            HuSprAttrSet(counter->grp, 0, 0x838);
            HuSprAttrSet(counter->grp, 1, 0x838);
            if (counter->value >= 10) {
                HuSprAttrReset(counter->grp, 0, 0x8000);
            } else {
                HuSprAttrSet(counter->grp, 0, 0x8000);
            }
        }
        scale = sindf(counter->timer / 15.0f * 180.0f) * 0.5f + 1.0f;
        func_80054904_main(counter->grp, 0, counter->x + counter->unk6[0] * scale, counter->y);
        func_80054904_main(counter->grp, 1, counter->x + counter->unk6[1] * scale, counter->y);
        HuSprScaleSet(counter->grp, 0, scale, scale);
        HuSprScaleSet(counter->grp, 1, scale, scale);
        if (counter->timer != 0) {
            if (--counter->timer == 0) {
                HuSprAttrReset(counter->grp, 0, 0x838);
                HuSprAttrReset(counter->grp, 1, 0x838);
            }
        }
    }
}

void func_8010AA9C_slot_synch(s16 idx, s16 target) {
    SsCounter *counter;
    s32 offset = idx * sizeof(SsCounter);

    counter = (SsCounter *)((u8 *)D_8010DF90_slot_synch + offset);
    counter->target = target;
}

void func_8010AAB8_slot_synch(void) {
    HuSprite_Unk84_Struct *spr;
    SsEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010DF8C_slot_synch[1] = func_8010A2C4_slot_synch(0xB));
    D_8010DF94_slot_synch = omAddObj(0x1E, 0, 0, -1, func_8010AC14_slot_synch);
    D_8010DF98_slot_synch = effect = HuMemAllocTag(sizeof(SsEffect) * 8, 0x7918);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010C4C0_slot_synch(spr, &D_8010D868_slot_synch);
        } else {
            effect->model = func_8010D0A8_slot_synch(spr, D_8010DF98_slot_synch->model, &D_8010D868_slot_synch);
        }
        effect->active = 0;
        *(u32 *)&effect->color = *(u32 *)&D_8010D868_slot_synch;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &HmfModelData[effect->model];
        model->unk40 = 0.0f;
    }
}

void func_8010AC14_slot_synch(omObjData *obj) {
    HuSprite_Unk84_Struct *spr;
    SsEffect *effect;
    HmfModel *model;
    s32 i;

    i = 0;
    spr = func_80055194_main(D_8010DF8C_slot_synch[1]);
    effect = D_8010DF98_slot_synch;
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
                func_8010D2AC_slot_synch(effect->model, spr, (s32)effect->frame, &effect->color);
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

s32 func_8010AD68_slot_synch(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color) {
    HuSprite_Unk84_Struct *spr;
    SsEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_8010DF8C_slot_synch[1]);
    for (i = 0, effect = D_8010DF98_slot_synch; i < 8; i++, effect++) {
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
            func_8010D2AC_slot_synch(effect->model, spr, 0, &effect->color);
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

void func_8010AF38_slot_synch(void) {
    HuCamera *cam;
    s32 i;

    Center.x = 0.0f;
    Center.y = 184.8f;
    Center.z = -708.8f;
    CRot.x = 354.505f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2000.0f;
    func_8010BB90_slot_synch(0);
    func_8010BB90_slot_synch(1);
    D_8010DFE8_slot_synch = D_8010DFEC_slot_synch = D_8010DFF0_slot_synch = 0;
    omAddObj(0x1F, 0, 0, -1, func_8010B754_slot_synch);
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

void func_8010B064_slot_synch(void) {
    SsCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_8010DA60_slot_synch) {
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
                func_8010BD7C_slot_synch(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 104, D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
                D_8010DA64_slot_synch++;
            }
            if (D_800CDA7C_main[0] & 0x202) {
                D_8010DA64_slot_synch--;
            }
            if (D_800CDA7C_main[0] & 0x404) {
                D_8010DA68_slot_synch++;
            }
            if (D_800CDA7C_main[0] & 0x808) {
                D_8010DA68_slot_synch--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_8010DA64_slot_synch + 20, (u16)D_8010DA68_slot_synch + 104, D_800D5218_main);
            break;
        case 3:
            D_8010DA60_slot_synch = 0;
            break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_8010DA60_slot_synch == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_8010DA60_slot_synch++ >= 4) {
            D_8010DA60_slot_synch = 0;
        }
    }
}

void func_8010B754_slot_synch(omObjData *obj) {
    f32 t;

    if (D_8010DFEC_slot_synch <= 0) {
        func_8010BF6C_slot_synch(0);
        D_8010DFF0_slot_synch = 0;
        return;
    }
    if (D_8010DFE8_slot_synch == 0) {
        Center.x = D_8010DFA0_slot_synch[0].center.x;
        Center.y = D_8010DFA0_slot_synch[0].center.y;
        Center.z = D_8010DFA0_slot_synch[0].center.z;
        CRot.x = D_8010DFA0_slot_synch[0].rot.x;
        CRot.y = D_8010DFA0_slot_synch[0].rot.y;
        CRot.z = D_8010DFA0_slot_synch[0].rot.z;
        CZoom = D_8010DFA0_slot_synch[0].zoom;
        SS_WRAP(CRot.x);
        SS_WRAP(CRot.y);
        SS_WRAP(CRot.z);
        D_8010DFEC_slot_synch = 0;
    } else {
        t = (f32)D_8010DFE8_slot_synch / (f32)D_8010DFEC_slot_synch;
        Center.x = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].center.x, D_8010DFA0_slot_synch[1].center.x);
        Center.y = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].center.y, D_8010DFA0_slot_synch[1].center.y);
        Center.z = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].center.z, D_8010DFA0_slot_synch[1].center.z);
        CRot.x = func_8010C39C_slot_synch(t, D_8010DFA0_slot_synch[0].rot.x, D_8010DFA0_slot_synch[1].rot.x);
        CRot.y = func_8010C39C_slot_synch(t, D_8010DFA0_slot_synch[0].rot.y, D_8010DFA0_slot_synch[1].rot.y);
        CRot.z = func_8010C39C_slot_synch(t, D_8010DFA0_slot_synch[0].rot.z, D_8010DFA0_slot_synch[1].rot.z);
        CZoom = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].zoom, D_8010DFA0_slot_synch[1].zoom);
        SS_WRAP(CRot.x);
        SS_WRAP(CRot.y);
        SS_WRAP(CRot.z);
        if (D_8010DFE8_slot_synch > 0) {
            D_8010DFE8_slot_synch--;
        } else {
            D_8010DFE8_slot_synch++;
        }
    }
    D_8010DFF0_slot_synch = 1;
    func_8010BF6C_slot_synch(0);
}

void func_8010BB90_slot_synch(s32 idx) {
    SS_WRAP(CRot.x);
    SS_WRAP(CRot.y);
    SS_WRAP(CRot.z);
    D_8010DFA0_slot_synch[idx].center.x = Center.x;
    D_8010DFA0_slot_synch[idx].center.y = Center.y;
    D_8010DFA0_slot_synch[idx].center.z = Center.z;
    D_8010DFA0_slot_synch[idx].rot.x = CRot.x;
    D_8010DFA0_slot_synch[idx].rot.y = CRot.y;
    D_8010DFA0_slot_synch[idx].rot.z = CRot.z;
    D_8010DFA0_slot_synch[idx].zoom = CZoom;
    D_8010DFA0_slot_synch[idx].unk1C = D_8010DFA0_slot_synch[idx].unk20 = 0.0f;
}

void func_8010BD7C_slot_synch(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_8010DFE8_slot_synch = frames - 1;
        D_8010DFEC_slot_synch = frames;
        if (cx != 65535.0f) {
            D_8010DFA0_slot_synch[0].center.x = cx;
        } else {
            D_8010DFA0_slot_synch[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_8010DFA0_slot_synch[0].center.y = cy;
        } else {
            D_8010DFA0_slot_synch[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_8010DFA0_slot_synch[0].center.z = cz;
        } else {
            D_8010DFA0_slot_synch[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_8010DFA0_slot_synch[0].rot.x = rx;
        } else {
            D_8010DFA0_slot_synch[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_8010DFA0_slot_synch[0].rot.y = ry;
        } else {
            D_8010DFA0_slot_synch[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_8010DFA0_slot_synch[0].rot.z = rz;
        } else {
            D_8010DFA0_slot_synch[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_8010DFA0_slot_synch[0].zoom = zoom;
        } else {
            D_8010DFA0_slot_synch[0].zoom = CZoom;
        }
        func_8010BB90_slot_synch(1);
    }
}

void func_8010BF6C_slot_synch(s32 idx) {
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

f32 func_8010C0C0_slot_synch(f32 a, f32 b) {
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

f32 func_8010C1C4_slot_synch(f32 target, f32 cur, f32 step) {
    f32 d;
    f32 v;
    f64 e;

    SS_WRAP(target);
    SS_WRAP(cur);
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
    SS_WRAP(v);
    return v;
}

f32 func_8010C384_slot_synch(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

f32 func_8010C39C_slot_synch(f32 t, f32 a, f32 b) {
    return func_8010C1C4_slot_synch(b, a, fabsf(func_8010C0C0_slot_synch(b, a) * t));
}

void func_8010C3FC_slot_synch(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}

void *func_8010C428_slot_synch(omObjData *obj) {
    SsPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}

s16 func_8010C47C_slot_synch(s32 dirAndFile) {
    s16 id = func_8001F1FC_main(DataRead(dirAndFile), 0x18);

    if (id >= 0) {
        return id;
    }
    return -1;
}

s32 func_8010C4C0_slot_synch(HuSprite_Unk84_Struct *arg0, RGBA *arg1) {
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
    func_8010D3E0_slot_synch(arg0, temp_s4, 1.0f, 0, 0);
    gSPDisplayList(temp_v0_2++, osVirtualToPhysical(D_8010DB60_slot_synch));
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
    gDPSetRenderMode(temp_v0_2++, G_RM_ZB_CLD_SURF, G_RM_NOOP2);
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

s32 func_8010D0A8_slot_synch(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2) {
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

void func_8010D2AC_slot_synch(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3) {
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

s32 func_8010D3E0_slot_synch(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
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
