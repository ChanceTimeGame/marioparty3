#include "common.h"
// m7 sb: Stardust Battle
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfman.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "math.h"

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

/* A pooled particle effect (Log Jam's SbEffect). */
typedef struct SbEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ RGBA color;
    /* 0x08 */ f32 frame;
    /* 0x0C */ f32 speed;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec vel;
    /* 0x28 */ Vec scale;
} SbEffect; // Size 0x34

typedef struct SbCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} SbCamera; // Size 0x24

typedef struct SbBytes {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} SbBytes;

typedef union SbPack {
    void *p;
    SbBytes b;
} SbPack;

typedef struct SbB44 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04; /* mode */
    /* 0x06 */ s16 unk06; /* timer */
    /* 0x08 */ char unk08[0xC];
} SbB44; // Size 0x14

typedef f32 Matrix4f[4][4];

#define SB_HMF_VTXNUM(hmf) (*(s16 *)&(hmf)->unk16[2])

#define SB_ABS(x) ((x) < 0 ? -(x) : (x))

#define SB_WRAP(v)             \
    if ((v) >= 360.0) {        \
        (v) -= 360.0;          \
    } else if ((v) < 0.0) {    \
        (v) += 360.0;          \
    }

/* The one player (D_80114AC8_stardust_battle, 0x7C, allocated in func_80106D0C). */
typedef struct SbPlayer {
    /* 0x00 */ s16 unk00; /* slot */
    /* 0x02 */ char unk02[2];
    /* 0x04 */ s16 unk04; /* state, -1 none */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ char unk16[2];
    /* 0x18 */ s32 unk18; /* win voice file */
    /* 0x1C */ s32 unk1C; /* lose voice file */
    /* 0x20 */ s16 unk20; /* GwPlayer index */
    /* 0x22 */ s16 unk22; /* controller port */
    /* 0x24 */ s16 unk24; /* character */
    /* 0x26 */ s16 unk26; /* CPU */
    /* 0x28 */ s16 unk28; /* CPU difficulty */
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ Vec unk2C; /* start position */
    /* 0x38 */ s16 unk38; /* shadow model group saved */
    /* 0x3A */ s16 unk3A; /* hook state (0x3A..0x5A cleared at creation) */
    /* 0x3C */ s16 unk3C; /* hook timer */
    /* 0x3E */ char unk3E[0x1C];
    /* 0x5A */ char unk5A[0xC];
    /* 0x66 */ s16 unk66;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ void (*unk6C)(omObjData *); /* per-frame hooks */
    /* 0x70 */ void (*unk70)(omObjData *);
    /* 0x74 */ void (*unk74)(omObjData *);
    /* 0x78 */ void (*unk78)(omObjData *); /* hook exit */
} SbPlayer; // Size 0x7C

/* The boss (D_80114B1C_stardust_battle, 0x74; its object is D_80114B18_stardust_battle). */
typedef struct SbBoss {
    /* 0x00 */ s16 unk00; /* state timer */
    /* 0x02 */ s16 unk02; /* dust timer */
    /* 0x04 */ s16 unk04; /* state */
    /* 0x06 */ s16 unk06; /* hits left */
    /* 0x08 */ s16 unk08; /* last hit, -1 none */
    /* 0x0A */ s16 unk0A; /* can be hit */
    /* 0x0C */ s16 unk0C; /* phase */
    /* 0x0E */ s16 unk0E; /* next phase */
    /* 0x10 */ s16 unk10; /* frames before the next attack */
    /* 0x12 */ s16 unk12; /* shots fired */
    /* 0x14 */ s16 unk14; /* shot timer */
    /* 0x16 */ s16 unk16; /* defeat count */
    /* 0x18 */ f32 unk18; /* spin speed */
    /* 0x1C */ f32 unk1C; /* heading */
    /* 0x20 */ f32 unk20; /* knock-back angle */
    /* 0x24 */ s16 unk24; /* fall frames */
    /* 0x26 */ s16 unk26; /* move frames */
    /* 0x28 */ f32 unk28; /* knock-back x step */
    /* 0x2C */ f32 unk2C; /* fall step */
    /* 0x30 */ f32 unk30; /* knock-back z step */
    /* 0x34 */ Vec unk34; /* target */
    /* 0x40 */ Vec unk40; /* move start */
    /* 0x4C */ Vec unk4C; /* defeat position */
    /* 0x58 */ f32 unk58; /* speed */
    /* 0x5C */ f32 unk5C; /* trail x */
    /* 0x60 */ f32 unk60; /* trail z */
    /* 0x64 */ f32 unk64; /* trail heading */
    /* 0x68 */ f32 unk68; /* colour scale r, g, b */
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
} SbBoss; // Size 0x74

/* A camera pose in .data (center, rotation, zoom). */
typedef struct SbCamPose {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} SbCamPose; // Size 0x1C

typedef func_800E1BA8_minigame_ObjData MgWork;

/* A dust particle (SbStage::unk28, 64 x 0x3C). */
typedef struct SbDust {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01; /* index */
    /* 0x02 */ char unk02[0x3A];
} SbDust; // Size 0x3C

/* A group of stage-mesh vertices sharing one position (SbStage::unk24, 0x2C each). */
typedef struct SbVtxGroup {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 n; /* vertices */
    /* 0x08 */ s16 idx[8];
    /* 0x18 */ u8 unk18; /* beyond the rim */
    /* 0x19 */ char unk19[3];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
} SbVtxGroup; // Size 0x2C

/* The stage (D_80114B10_stardust_battle, 0x38): the star-field cylinder and its scroll. */
typedef struct SbStage {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02; /* material "stardast-cyl10" */
    /* 0x04 */ s16 unk04; /* material "stardast-cyl5_1" */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08; /* scroll u, v of the first */
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10; /* scroll u, v of the second */
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ SbVtxGroup *unk24; /* vertex groups */
    /* 0x28 */ SbDust *unk28; /* 64 dust particles */
    /* 0x2C */ s16 unk2C; /* material "comet-nagare" */
    /* 0x2E */ char unk2E[2];
    /* 0x30 */ void (*unk30)(omObjData *); /* per-frame hook */
    /* 0x34 */ void (*unk34)(omObjData *); /* mode exit hook */
} SbStage; // Size 0x38

/* A shot (SbShots::unk08, 32 x 0x10). */
typedef struct SbShot {
    /* 0x00 */ s16 unk00; /* active */
    /* 0x02 */ s16 unk02; /* special */
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
} SbShot; // Size 0x10

/* The boss's shots (D_80114B20_stardust_battle, 0xC). */
typedef struct SbShots {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02; /* capacity */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ SbShot *unk08;
} SbShots; // Size 0xC

/* One of the 16 defeat stars (D_80114B5C_stardust_battle, 16 x 0x28). */
typedef struct SbStar {
    /* 0x00 */ s16 unk00; /* shown */
    /* 0x02 */ s16 unk02; /* model */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10; /* angle */
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} SbStar; // Size 0x28

/* An item (SbItems::unk0C, 0x7C each). */
typedef struct SbItem {
    /* 0x00 */ s16 unk00; /* active */
    /* 0x02 */ s16 unk02[2]; /* item models */
    /* 0x06 */ s16 unk06[2]; /* reflection models */
    /* 0x0A */ s16 unk0A; /* shadow model */
    /* 0x0C */ s16 unk0C; /* glow model */
    /* 0x0E */ char unk0E[2];
    /* 0x10 */ s16 unk10; /* model shown */
    /* 0x12 */ s16 unk12; /* bounces */
    /* 0x14 */ s16 unk14; /* state timer */
    /* 0x16 */ s16 unk16; /* state */
    /* 0x18 */ s16 unk18; /* glow shown */
    /* 0x1A */ char unk1A[2];
    /* 0x1C */ Vec unk1C; /* previous position */
    /* 0x28 */ Vec unk28; /* position */
    /* 0x34 */ Vec unk34; /* rotation */
    /* 0x40 */ Vec unk40; /* velocity */
    /* 0x4C */ char unk4C[0xC];
    /* 0x58 */ Vec unk58; /* hook start position */
    /* 0x64 */ char unk64[4];
    /* 0x68 */ f32 unk68; /* glow alpha */
    /* 0x6C */ f32 unk6C; /* glow alpha set */
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
} SbItem; // Size 0x7C

/* The items (D_80114B2C_stardust_battle). */
typedef struct SbItems {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06; /* glow material */
    /* 0x08 */ s16 unk08; /* count */
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ SbItem *unk0C;
} SbItems;

// end m7 sb types

// protos begin
void func_801059A0_stardust_battle(void);
void func_80105D18_stardust_battle(omObjData *obj);
void func_80105DA0_stardust_battle(omObjData *obj);
void func_801065B4_stardust_battle(omObjData* obj);
void func_801065D8_stardust_battle(omObjData *obj);
void func_80106690_stardust_battle(omObjData *obj);
void func_80106A3C_stardust_battle(omObjData *obj);
void func_80106B60_stardust_battle(omObjData *obj);
void func_80106C30_stardust_battle(omObjData *obj);
void func_80106D0C_stardust_battle(void);
void func_80106EB0_stardust_battle(omObjData *obj);
void func_801073F4_stardust_battle(omObjData *obj);
void func_80107DCC_stardust_battle(omObjData *obj, s16 mode);
s16 func_80107E84_stardust_battle(s16 hmf);
void func_80107F34_stardust_battle(f32 step);
s16 func_80107FA4_stardust_battle(void);
s16 func_80107FE8_stardust_battle(void);
void func_80108074_stardust_battle(void);
void func_801080B0_stardust_battle(void);
void func_801080EC_stardust_battle(void);
void func_80108120_stardust_battle(omObjData *obj);
void func_801081FC_stardust_battle(omObjData *obj);
void func_801082C4_stardust_battle(omObjData *obj);
void func_80108404_stardust_battle(omObjData *obj);
void func_80108444_stardust_battle(void);
void func_8010844C_stardust_battle(void);
void func_80108454_stardust_battle(omObjData *obj);
void func_801084B0_stardust_battle(omObjData *obj);
void func_801086E8_stardust_battle(omObjData *obj);
void func_8010882C_stardust_battle(omObjData *obj);
void func_801089B4_stardust_battle(void);
void func_801089BC_stardust_battle(omObjData *obj);
void func_80108AC4_stardust_battle(omObjData *obj);
void func_80108B34_stardust_battle(void);
void func_80108C14_stardust_battle(omObjData *obj);
void func_80108D84_stardust_battle(omObjData *obj);
void func_80108EC4_stardust_battle(s16 mdl, f32 u, f32 v, s32 w, s32 h, s32 mat);
void func_80109128_stardust_battle(s16 mode);
s16 func_8010929C_stardust_battle(void);
void func_801092F0_stardust_battle(omObjData *obj);
void func_801093CC_stardust_battle(omObjData *obj);
void func_80109F94_stardust_battle(omObjData *obj);
void func_80109FE4_stardust_battle(omObjData *obj);
void func_8010A5A4_stardust_battle(omObjData *obj);
void func_8010A5E0_stardust_battle(omObjData *obj);
void func_8010A690_stardust_battle(omObjData *obj);
void func_8010AAC4_stardust_battle(omObjData *obj);
void func_8010BFE4_stardust_battle(f32 y, s16 frames);
void func_8010C06C_stardust_battle(void);
void func_8010C0C8_stardust_battle(void);
void func_8010C1F8_stardust_battle(s16 motion, s16 start, s16 end, u8 flags);
void func_8010C2CC_stardust_battle(f32 v);
f32 func_8010C32C_stardust_battle(void);
void func_8010C38C_stardust_battle(f32 v);
f32 func_8010C3EC_stardust_battle(void);
void func_8010C44C_stardust_battle(void);
void func_8010C498_stardust_battle(void);
s16 func_8010C508_stardust_battle(void);
void func_8010C538_stardust_battle(void);
SbItem *func_8010E300_stardust_battle(s16 idx);
void func_8010E46C_stardust_battle(s16 idx, f32 x, f32 y, f32 z);
void func_8010E4C8_stardust_battle(s16 idx, f32 x, f32 y, f32 z);
void func_8010ED7C_stardust_battle(void);
u16 func_8010EE38_stardust_battle(s32 dirAndFile);
void func_8010F580_stardust_battle(s16 idx);
void func_8010F5B0_stardust_battle(s16 idx);
void func_8010F5E0_stardust_battle(void);
void func_8010F73C_stardust_battle(omObjData *obj);
s32 func_8010F890_stardust_battle(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color);
void func_80110758_stardust_battle(f32 x, f32 y, f32 z, s32 n);
void func_80110780_stardust_battle(s16 n);
void func_801107C4_stardust_battle(s16 n);
void func_80110914_stardust_battle(void);
void func_801115F8_stardust_battle(s32 idx);
void func_801117E4_stardust_battle(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames);
void func_801119D4_stardust_battle(s32 idx);
f32 func_80111B28_stardust_battle(f32 a, f32 b);
f32 func_80111DF8_stardust_battle(f32 t, f32 a, f32 b);
f32 func_80111E10_stardust_battle(f32 t, f32 a, f32 b);
void func_80111E70_stardust_battle(f32 *a, f32 *b, f32 *out, f32 t);
f32 func_80111EB8_stardust_battle(f32 x, f32 z);
void func_80111F38_stardust_battle(Vec* dir, f32* angles);
void func_80111FC0_stardust_battle(omObjData *obj, u32 value);
void *func_80111FEC_stardust_battle(omObjData *obj);
void func_80112040_stardust_battle(s16 mdl, const char *part, Matrix4f *out);
s32 func_80112980_stardust_battle(HuSprite_Unk84_Struct *arg0, RGBA *arg1);
s32 func_80113568_stardust_battle(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2);
void func_8011376C_stardust_battle(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3);
s32 func_801138A0_stardust_battle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
s16 func_8010FCBC_stardust_battle(Vec *pos, Vec *rot, f32 scale, s16 kind);
// protos end

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
f32 fabsf(f32);

/* still asm */
void func_8010DF70_stardust_battle(s16);
void func_8001C5B4_main(s16, s16);
void func_8010A5A4_stardust_battle(omObjData *obj);
void func_8010A690_stardust_battle(omObjData *obj);
void func_800465A8_main(s16, f32, f32, f32);
void func_8010A204_stardust_battle(f32 x, f32 z, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void func_8010C5A8_stardust_battle(s32, s32);
s32 func_8010CA48_stardust_battle(s16);
void func_8010DE64_stardust_battle(s32, s32);
extern s16 D_80113E90_stardust_battle[];
extern s32 D_80113E98_stardust_battle[];
extern s16 D_80113EA8_stardust_battle[];
extern s16 D_80113EB0_stardust_battle[];
extern void (*D_80113E78_stardust_battle[3])(omObjData *);
extern void (*D_80113E84_stardust_battle[3])(omObjData *);
extern s32 D_80113E54_stardust_battle[3];
extern s32 D_80113E60_stardust_battle[3];
extern s32 D_80113E6C_stardust_battle[3];
void func_8001ED54_main(s16);
void func_800E1490_minigame(u16 arg0);
void func_800E1304_minigame(omObjData *obj, f32 arg1);
void func_800E1310_minigame(omObjData *obj, f32 arg1);
void func_800E131C_minigame(omObjData *obj, f32 arg1);
void func_800E1370_minigame(omObjData* obj, s32 flags, f32 arg2);
void func_8010A04C_stardust_battle(f32 x, f32 z, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void func_800E5798_minigame(omObjData *obj, u16 motion);
omObjData *func_80045F1C_main(u32, s16, s16);
extern f32 D_800EB748_minigame;
extern f32 D_800EB774_minigame;
void func_80108120_stardust_battle(omObjData *obj);
void func_801081FC_stardust_battle(omObjData *obj);
void func_801082C4_stardust_battle(omObjData *obj);
extern void (*D_80113E24_stardust_battle[3])(omObjData *);
extern void (*D_80113E30_stardust_battle[3])(omObjData *);
extern void (*D_80113E3C_stardust_battle[3])(omObjData *);
extern void (*D_80113E48_stardust_battle[3])(omObjData *);
extern omObjData *D_80114B18_stardust_battle;
void func_80107760_stardust_battle(omObjData *obj, s16 busy);
s16 func_8010E524_stardust_battle(omObjData *obj, s16 mode, Vec *dir);
void func_8010EA04_stardust_battle(omObjData *obj);
void func_800DDD94_minigame(omObjData* obj);
s32 func_800E4A90_minigame(omObjData* obj);
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern f32 D_800EB744_minigame;
extern f32 D_800EB770_minigame;
extern u8 D_800D6A90_main;
void func_80106EB0_stardust_battle(omObjData *obj);
void func_801073F4_stardust_battle(omObjData *obj);
void func_800E5978_minigame(omObjData* obj, u16 idx, s32 file, u16 flags, u16 speed);
void func_800E149C_minigame(omObjData* obj, u8 idx, u8 val);
extern s32 D_800A178C_main[][6];
extern Vec D_80113CB0_stardust_battle[];
extern s32 D_80113DEC_stardust_battle[4];
extern s32 D_80113DFC_stardust_battle[8];
extern s32 D_80113E1C_stardust_battle[2];
void func_80107F34_stardust_battle(f32);
void func_80106690_stardust_battle(omObjData *obj);
void func_80106A3C_stardust_battle(omObjData *obj);
void func_80106B60_stardust_battle(omObjData *obj);
void func_80106C30_stardust_battle(omObjData *obj);
void func_801065D8_stardust_battle(omObjData *obj);
void func_80106D0C_stardust_battle(void);
void func_80108074_stardust_battle(void);
void func_801080B0_stardust_battle(void);
void func_801080EC_stardust_battle(void);
void func_80108B34_stardust_battle(void);
void func_8010A74C_stardust_battle(void);
void func_80109B18_stardust_battle(omObjData *obj);

void func_8010CB34_stardust_battle(void);
void func_8010EE7C_stardust_battle(void);
void func_8010F400_stardust_battle(s32, s32);
void func_8010FA60_stardust_battle(void);
void func_801107E4_stardust_battle(void);
f32 func_80111C2C_stardust_battle(f32 target, f32 cur, f32 step);
s32 func_801138A0_stardust_battle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8010F73C_stardust_battle(omObjData *obj);

extern RGBA D_80113CF4_stardust_battle;
u16 GWMgRecordGet(s16 arg0);
u8 func_8000B638_main(void);
void func_800E6F0C_minigame(s32);
void func_8003F5C0_main(void);
extern const s16 D_80114100_stardust_battle[];
extern const s16 D_8011410C_stardust_battle[];
extern SbCamPose D_80113CF8_stardust_battle;
extern SbCamPose D_80113D14_stardust_battle;
extern SbCamPose D_80113D30_stardust_battle;
extern SbCamPose D_80113D68_stardust_battle;
extern s16 D_80113DBC_stardust_battle[];
extern s16 D_80113DC4_stardust_battle[];
extern s16 D_80113DCC_stardust_battle[];
extern void (*D_80113DDC_stardust_battle)(omObjData *);
extern s16 D_80113DE0_stardust_battle; /* intro sound */
extern s32 D_80113DE4_stardust_battle; /* fade-out timer */
extern u8 D_80113DE8_stardust_battle;
extern omObjData *D_80114A98_stardust_battle;
extern s32 D_80114A9C_stardust_battle;
extern s32 D_80114AA0_stardust_battle;
extern s32 D_80114AA4_stardust_battle; /* state timer */
extern s32 D_80114AA8_stardust_battle;
extern s32 D_80114AAC_stardust_battle;
extern s32 D_80114AB0_stardust_battle; /* game frames */
extern s32 D_80114AB4_stardust_battle; /* record */
extern u16 D_80114AB6_stardust_battle; /* low half of D_80114AB4 */
extern s32 D_80114AB8_stardust_battle; /* game state */
extern s32 D_80114ABC_stardust_battle;
extern s32 D_80114AC0_stardust_battle; /* record mode */
extern s32 D_80114AC4_stardust_battle;
extern SbPlayer *D_80114AC8_stardust_battle;
extern s16 D_80114ACC_stardust_battle;
extern s16 D_80114ACE_stardust_battle;
extern Matrix4f D_80114AD0_stardust_battle;
extern SbStage *D_80114B10_stardust_battle;
extern s16 D_80114B14_stardust_battle;
extern SbBoss *D_80114B1C_stardust_battle;
extern SbShots *D_80114B20_stardust_battle;
extern s32 D_80114B24_stardust_battle;
extern s16 *D_80114B28_stardust_battle;
extern SbItems *D_80114B2C_stardust_battle;
extern s16 D_80114B54_stardust_battle;
extern omObjData *D_80114B58_stardust_battle;
extern SbStar *D_80114B5C_stardust_battle; /* 16 */
extern s32 D_80114BB0_stardust_battle;
extern s32 D_80114BB4_stardust_battle;
extern D_80111B50_vine_with_me_Struct D_80114BB8_stardust_battle;
extern s32 D_80113F08_stardust_battle; /* debug camera mode */
extern s32 D_80113F0C_stardust_battle; /* debug text x */
extern s32 D_80113F10_stardust_battle; /* debug text y */
extern SbB44 *D_80114B44_stardust_battle;
extern SbCamera D_80114B60_stardust_battle[2];
extern s32 D_80114BA8_stardust_battle;
extern s32 D_80114BAC_stardust_battle;
extern s32 fontcolor;
extern s8 HmfPauseF;
extern Matrix4f *D_800D1358_main;
extern s16 *D_800D04B4_main;
extern s16 D_800CD1B0_main;
extern s16 D_800D138A_main;
extern Matrix4f D_800D5A00_main[];
void func_8008A070_main(Matrix4f);
void func_80017CD0_main(Matrix4f, f32, f32, f32);
void func_80017D24_main(Matrix4f, f32, f32, f32);
void func_80018044_main(Matrix4f, Matrix4f, Matrix4f);
f64 fabs(f64);
void func_8002DFF8_main(HmfData *, f32, D_800CCF58_main_Struct *, s32);
void func_8002EAC0_main(HmfData *, f32, f32);
s16 func_8002C834_main(HmfData *, const char *);
void func_80016C2C_main(HmfData *arg0, s16 arg1, s16 arg2);
f64 fmod(f64, f64);
extern Gfx D_80114020_stardust_battle[];
extern s16 *D_80114B30_stardust_battle; /* s16[0x20] sprite/file ids */
extern omObjData *D_80114B48_stardust_battle;
extern SbEffect *D_80114B4C_stardust_battle;

void func_801059A0_stardust_battle(void) {
    u8 cam;
    s32 level;

    Hu3DAnimInit(50);
    omInitObjMan(50, 10);
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
    D_80114AB0_stardust_battle = 0;
    D_80114AA4_stardust_battle = 0;
    D_80114AA0_stardust_battle = 0;
    D_80114AA8_stardust_battle = 0;
    D_80114AAC_stardust_battle = 0;
    D_80114AB8_stardust_battle = -1;
    D_80114ABC_stardust_battle = 0;
    D_80114AC0_stardust_battle = 0;
    D_80114B14_stardust_battle = 1;
    D_80114B24_stardust_battle = 9;
    D_80114B28_stardust_battle = D_80113DBC_stardust_battle;
    D_80114AC4_stardust_battle = 1;
    D_80114AC0_stardust_battle = _CheckFlag(0x1C);
    if (D_80114AC0_stardust_battle != 0) {
        D_80114AC0_stardust_battle = 1;
        D_80114AB4_stardust_battle = GWMgRecordGet(9);
        if (D_80114AB4_stardust_battle == 0) {
            D_80114AB4_stardust_battle = 4500;
        }
    }
    if (!(GwSystem.playMode & 4) || _CheckFlag(0x1C) != 0) {
        level = 2;
    } else {
        level = GwStory.unk2;
    }
    switch (level) {
    case 0:
        D_80114B24_stardust_battle = 3;
        D_80114B28_stardust_battle = D_80113DCC_stardust_battle;
        break;
    case 1:
        D_80114B24_stardust_battle = 6;
        D_80114B28_stardust_battle = D_80113DC4_stardust_battle;
        break;
    default:
        D_80114B24_stardust_battle = 9;
        D_80114B28_stardust_battle = D_80113DBC_stardust_battle;
        break;
    }
    D_80114ACC_stardust_battle = -1;
    D_80114ACE_stardust_battle = 0;
    D_80114B30_stardust_battle = HuMemAllocTag(0x40, 31000);
    D_80114AC8_stardust_battle = NULL;
    D_80114B10_stardust_battle = 0;
    D_80114B18_stardust_battle = 0;
    D_80114B1C_stardust_battle = NULL;
    D_80114B2C_stardust_battle = 0;
    D_80114B58_stardust_battle = 0;
    D_80114B5C_stardust_battle = 0;
    guMtxIdentF(D_80114AD0_stardust_battle);
    D_80114A98_stardust_battle = omAddObj(0x20, 0, 0, -1, func_80105D18_stardust_battle);
    memset(&D_80114BB8_stardust_battle, 0, 0x28);
    D_80114BB8_stardust_battle.unk01 = 4;
    func_800E5EA0_minigame(&D_80114BB8_stardust_battle);
    func_80045010_main(D_80114100_stardust_battle, 1);
    func_80045010_main(D_8011410C_stardust_battle, 1);
}

void func_80105D18_stardust_battle(omObjData *obj) {
    obj->func = func_80105DA0_stardust_battle;
    func_80108B34_stardust_battle();
    func_8010F5E0_stardust_battle();
    func_8010FA60_stardust_battle();
    func_80106D0C_stardust_battle();
    func_8010A74C_stardust_battle();
    func_8010CB34_stardust_battle();
    func_801107E4_stardust_battle();
    func_8010EE7C_stardust_battle();
    D_80114B54_stardust_battle = func_8000D658_main(0x1CA9, 10);
    if (_CheckFlag(0xA) != 0) {
        D_80114A9C_stardust_battle = 1;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114100_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_8011410C_stardust_battle);

void func_80105DA0_stardust_battle(omObjData *obj) {
    SbBoss *boss = D_80114B1C_stardust_battle;
    s32 left;

    switch (D_80114AB8_stardust_battle) {
    case -1:
        if (D_80114AA4_stardust_battle > 0) {
            D_80114BB4_stardust_battle = 0;
            func_801117E4_stardust_battle(D_80113CF8_stardust_battle.center.x, D_80113CF8_stardust_battle.center.y, D_80113CF8_stardust_battle.center.z, D_80113CF8_stardust_battle.rot.x, D_80113CF8_stardust_battle.rot.y, D_80113CF8_stardust_battle.rot.z, D_80113CF8_stardust_battle.zoom, 1);
            D_80113DE0_stardust_battle = HuAudFXPlay(0x50C);
            WipeCreateIn(0xFF, 0x10);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 0:
        if (WipeStatGet() == 0 && func_80107FA4_stardust_battle() != 0) {
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 1:
        if (func_80107FE8_stardust_battle() != 0) {
            D_80114BB4_stardust_battle = 0;
            func_801117E4_stardust_battle(D_80113D14_stardust_battle.center.x, D_80113D14_stardust_battle.center.y, D_80113D14_stardust_battle.center.z, D_80113D14_stardust_battle.rot.x, D_80113D14_stardust_battle.rot.y, D_80113D14_stardust_battle.rot.z, D_80113D14_stardust_battle.zoom, 37);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 2:
        if (D_80114BB0_stardust_battle == 0) {
            HuAudSeqPlay(0x41);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 3:
        if (D_80114AA4_stardust_battle >= 22.5) {
            D_80114BB4_stardust_battle = 3;
            func_801117E4_stardust_battle(D_80113D30_stardust_battle.center.x, D_80113D30_stardust_battle.center.y, D_80113D30_stardust_battle.center.z, D_80113D30_stardust_battle.rot.x, D_80113D30_stardust_battle.rot.y, D_80113D30_stardust_battle.rot.z, D_80113D30_stardust_battle.zoom, 15);
            func_80107E84_stardust_battle(0);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 4:
        if (D_80114BB0_stardust_battle == 0) {
            func_8010C1F8_stardust_battle(0, 0, 300, 0);
            HuAudFXPlay(0x511);
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 5:
        if (func_8010C3EC_stardust_battle() >= 60.0f && func_8010C32C_stardust_battle() == 1.0f) {
            func_8010C38C_stardust_battle(60.0f);
            func_8010C2CC_stardust_battle(0.0f);
        }
        if (D_80114AA4_stardust_battle == 43.0f) {
            func_8010BFE4_stardust_battle(450.0f, 30);
        }
        if (D_80114AA4_stardust_battle > 45.0f) {
            func_8010C1F8_stardust_battle(0, 60, 0, 4);
            func_8010C2CC_stardust_battle(2.0f);
            D_80114BB4_stardust_battle = 2;
            func_801117E4_stardust_battle(D_80113D68_stardust_battle.center.x, D_80113D68_stardust_battle.center.y, D_80113D68_stardust_battle.center.z, D_80113D68_stardust_battle.rot.x, D_80113D68_stardust_battle.rot.y, D_80113D68_stardust_battle.rot.z, D_80113D68_stardust_battle.zoom, 22);
            if (D_80113DE0_stardust_battle != -1) {
                func_8004AEF0_main(D_80113DE0_stardust_battle, 22);
                D_80113DE0_stardust_battle = -1;
            }
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 6:
        if (D_80114BB0_stardust_battle == 0) {
            GMesCreate(9);
            HuAudFXPlay(0xE);
            func_80108074_stardust_battle();
            D_80114AB8_stardust_battle++;
        }
        break;
    case 7:
        if (GMesStatGet() == 0) {
            func_8010F400_stardust_battle(0, D_80114AB0_stardust_battle);
            func_800E6F0C_minigame(2);
            D_80114AB8_stardust_battle++;
        }
        break;
    case 8:
        func_8010F400_stardust_battle(0, ++D_80114AB0_stardust_battle);
        if (D_80114AB0_stardust_battle == 4470) {
            func_8010F5B0_stardust_battle(0);
            func_8010F5B0_stardust_battle(1);
        } else if (D_80114AB0_stardust_battle == 4499) {
            GMesCreate(0x1A, 31, 0x9C, 0x20);
        } else if (D_80114AB0_stardust_battle >= 4500) {
            left = 5429 - D_80114AB0_stardust_battle;
            func_8003F578_main(left / 30);
        }
        if (D_80114AB0_stardust_battle >= 5400 || D_80114ACE_stardust_battle != 0 || boss->unk06 <= 0) {
            func_8003F5C0_main();
            GMesCreate(0x14);
            func_800E6F0C_minigame(3);
            func_8010C06C_stardust_battle();
            func_8010ED7C_stardust_battle();
            HuAudSeqFadeOut(120);
            func_801080EC_stardust_battle();
            if (boss->unk06 <= 0) {
                D_80114ACC_stardust_battle = 0;
                left = (5429 - D_80114AB0_stardust_battle) / 30;
                if (left >= 60) {
                    GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = 3;
                } else if (left >= 40) {
                    GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = 2;
                } else if (left >= 20) {
                    GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = 1;
                } else {
                    GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = 0;
                }
            } else {
                GwPlayer[D_80114AC8_stardust_battle->unk20].bonusCoin = -1;
            }
            D_80114AA4_stardust_battle = 0;
            D_80114AB8_stardust_battle++;
        }
        break;
    case 9:
        if (GMesStatGet() == 0 && (func_8010C508_stardust_battle() == 12 || (D_80114AC0_stardust_battle != 0 && D_80114ACC_stardust_battle >= 0 && D_80114AB0_stardust_battle < D_80114AB4_stardust_battle))) {
            func_800E6F0C_minigame(4);
            func_801080B0_stardust_battle();
            D_80114ABC_stardust_battle = 0;
            if (D_80114AC0_stardust_battle == 0 || D_80114ACC_stardust_battle < 0 || D_80114AB0_stardust_battle >= D_80114AB4_stardust_battle) {
                func_8010C0C8_stardust_battle();
            }
            if (D_80114AC0_stardust_battle != 0) {
                if (D_80114ACC_stardust_battle >= 0) {
                    D_80113DDC_stardust_battle = func_80106690_stardust_battle;
                } else {
                    D_80113DDC_stardust_battle = func_80106A3C_stardust_battle;
                }
            } else if (D_80114ACC_stardust_battle >= 0) {
                D_80113DDC_stardust_battle = func_80106B60_stardust_battle;
            } else {
                D_80113DDC_stardust_battle = func_80106C30_stardust_battle;
            }
            D_80114AB8_stardust_battle++;
            D_80114AA4_stardust_battle = 0;
        }
        break;
    case 10:
        if (D_80113DDC_stardust_battle != NULL) {
            D_80113DDC_stardust_battle(obj);
        }
        break;
    case 32:
    case 64:
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreateOut(11, 0x10);
        HuAudSeqFadeOut(0x10);
        func_8004AB0C_main(0x10);
        HuAudFXPlay(0x509);
        D_80114AB8_stardust_battle = 99;
        D_80114AA4_stardust_battle = 0;
        break;
    case 99:
        if (WipeStatGet() == 0) {
            obj->func = func_801065B4_stardust_battle;
        }
        break;
    }
    func_801065D8_stardust_battle(obj);
    D_80114AA0_stardust_battle++;
    D_80114AA4_stardust_battle++;
}

void func_801065B4_stardust_battle(omObjData* obj) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

void func_801065D8_stardust_battle(omObjData *obj) {
    if (D_80113DE4_stardust_battle != 0) {
        if (D_80113DE4_stardust_battle == 1) {
            obj->func = func_801065B4_stardust_battle;
        }
        D_80113DE4_stardust_battle--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_80113DE4_stardust_battle = 0x10;
        WipeColorSet(0, 0, 0);
        WipeCreateOut(0, (s16)D_80113DE4_stardust_battle);
        HuAudSeqFadeOut((s16)D_80113DE4_stardust_battle);
        func_8004AB0C_main((s16)D_80113DE4_stardust_battle);
    }
}

void func_80106690_stardust_battle(omObjData *obj) {
    switch (D_80114ABC_stardust_battle) {
    case 0:
        if (D_80114AB0_stardust_battle >= D_80114AB4_stardust_battle) {
            if (func_8010C508_stardust_battle() == 14) {
                func_8010C498_stardust_battle();
                D_80114ABC_stardust_battle = 16;
                D_80114AA4_stardust_battle = 0;
            }
        } else {
            D_80114ABC_stardust_battle = 2;
        }
        break;
    case 2:
        if (D_80113DE8_stardust_battle == 2) {
            if (func_8010C508_stardust_battle() == 12) {
                func_8010C0C8_stardust_battle();
                D_80113DE8_stardust_battle = 1;
            }
        } else if (D_80113DE8_stardust_battle == 1 && func_8010C508_stardust_battle() == 14) {
            func_8010C498_stardust_battle();
            D_80113DE8_stardust_battle = 0;
        }
        if (D_80114AA4_stardust_battle > 15.0f) {
            D_80114AB4_stardust_battle = D_80114AB0_stardust_battle;
            GWMgRecordSet(9, D_80114AB6_stardust_battle);
            func_8010F400_stardust_battle(0, D_80114AB0_stardust_battle);
            func_8010F400_stardust_battle(1, D_80114AB4_stardust_battle);
            func_8010F580_stardust_battle(1);
            GMesCreate(0x1B);
            D_80114AAC_stardust_battle = 99;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 3:
        if (D_80113DE8_stardust_battle == 2) {
            if (func_8010C508_stardust_battle() == 12) {
                func_8010C0C8_stardust_battle();
                D_80113DE8_stardust_battle = 1;
            }
        } else if (D_80113DE8_stardust_battle == 1 && func_8010C508_stardust_battle() == 14) {
            func_8010C498_stardust_battle();
            D_80113DE8_stardust_battle = 0;
        }
        if (GMesStatGet() == 0) {
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 4:
        if (D_80113DE8_stardust_battle == 2) {
            if (func_8010C508_stardust_battle() == 12) {
                func_8010C0C8_stardust_battle();
                D_80113DE8_stardust_battle = 1;
            }
        } else if (D_80113DE8_stardust_battle == 1 && func_8010C508_stardust_battle() == 14) {
            func_8010C498_stardust_battle();
            D_80113DE8_stardust_battle = 0;
        }
        if (D_80114AA4_stardust_battle >= 15) {
            HuAudSeqPlay(0x6A);
            D_80114AC8_stardust_battle->unk04 = 13;
            GMesCreate(0x16, D_80114AC8_stardust_battle->unk24);
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 5:
        if (GMesStatGet() == 0) {
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 16:
        if (D_80114AA4_stardust_battle > 60.0f) {
            D_80114AC8_stardust_battle->unk04 = 13;
            GMesCreate(0x16, D_80114AC8_stardust_battle->unk24);
            HuAudSeqPlay(0x65);
            D_80114AAC_stardust_battle = 98;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 17:
        if (GMesStatGet() == 0) {
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 6:
    case 18:
        if (D_80114AA4_stardust_battle >= 15) {
            D_80114AB8_stardust_battle = 32;
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    }
}

void func_80106A3C_stardust_battle(omObjData *obj) {
    switch (D_80114ABC_stardust_battle) {
    case 0:
        if (func_8010C508_stardust_battle() == 14) {
            D_80114AC8_stardust_battle->unk04 = 14;
            func_8010C44C_stardust_battle();
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 1:
        if (D_80114AA4_stardust_battle >= 15.0f) {
            GMesCreate(0x1D);
            HuAudSeqPlay(0x6B);
            D_80114AAC_stardust_battle = 132;
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 2:
        if (GMesStatGet() == 0) {
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 3:
        if (D_80114AA4_stardust_battle >= 15) {
            D_80114AB8_stardust_battle = 32;
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    }
}

void func_80106B60_stardust_battle(omObjData *obj) {
    switch (D_80114ABC_stardust_battle) {
    case 0:
        func_80107F34_stardust_battle(5.0f);
        if (func_8010C508_stardust_battle() == 14) {
            func_8010C498_stardust_battle();
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 1:
        func_80107F34_stardust_battle(5.0f);
        if (D_80114AA4_stardust_battle >= 150.0f) {
            D_80114AB8_stardust_battle = 64;
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    }
}

void func_80106C30_stardust_battle(omObjData *obj) {
    switch (D_80114ABC_stardust_battle) {
    case 0:
        D_80114AC8_stardust_battle->unk04 = 14;
        D_80114AA4_stardust_battle = 0;
        D_80114ABC_stardust_battle++;
        break;
    case 1:
        if (func_8010C508_stardust_battle() == 14) {
            func_8010C44C_stardust_battle();
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    case 2:
        if (D_80114AA4_stardust_battle >= 30.0f) {
            D_80114AB8_stardust_battle = 64;
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
        }
        break;
    }
}

void func_80106D0C_stardust_battle(void) {
    SbPlayer *pl;
    omObjData *obj;
    s16 i;

    pl = D_80114AC8_stardust_battle = HuMemAllocTag(sizeof(SbPlayer), 31000);
    func_800E19F0_minigame(0);
    func_800E18D8_minigame();
    for (i = 0; i < 4; i++) {
        if (GwPlayer[D_80113DEC_stardust_battle[i]].group == 0) {
            break;
        }
    }
    if (i >= 4) {
        i = 0;
    }
    pl->unk00 = i;
    pl->unk20 = D_80113DEC_stardust_battle[pl->unk00];
    obj = omAddObj(0x10, 11, 60, -1, func_80106EB0_stardust_battle);
    D_800EC598_minigame[D_800EC280_minigame] = obj;
    D_800EC280_minigame++;
    obj->trans.x = D_80113CB0_stardust_battle[pl->unk00].x;
    obj->trans.z = D_80113CB0_stardust_battle[pl->unk00].z;
    pl->unk2C.x = obj->trans.x;
    pl->unk2C.y = obj->trans.y;
    pl->unk2C.z = obj->trans.z;
    pl->unk6C = NULL;
    pl->unk70 = NULL;
    pl->unk74 = NULL;
    pl->unk78 = NULL;
    memset(&pl->unk3A, 0, 0x20);
    func_80111FC0_stardust_battle(obj, (u32)pl);
}

/* NON_MATCHING: scheduling only: retail puts the sll of the rand8() index after the lui/addiu of D_80113E1C */
#ifdef NON_MATCHING
void func_80106EB0_stardust_battle(omObjData *obj) {
    SbPlayer *pl = func_80111FEC_stardust_battle(obj);
    s16 chr;
    u32 dir;
    s32 *voice;
    s32 *chrfile;
    MgWork *work;
    u32 sub;
    s32 file;

    s16 idx = pl->unk20;

    pl->unk24 = chr = GwPlayer[idx].chr;
    pl->unk22 = GwPlayer[idx].pad;
    pl->unk26 = GwPlayer[idx].stat & 1;
    pl->unk28 = GwPlayer[idx].cpu_difficulty;
    dir = D_800A178C_main[chr][0];
    file = D_800A178C_main[chr][1];
    sub = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(obj, dir, file, idx, 0x699, 0x1699);
    work = obj->data;
    work->unk50 &= ~1;
    work->unkEC = NULL;
    obj->model[3] = func_8000B108_main(3, 0x1E8D);
    obj->model[4] = func_8000B108_main(4, 0x1E8D);
    obj->model[10] = -1;
    obj->model[9] = func_8000B108_main(dir | sub, 0x6BD);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(obj, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(obj, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(obj, 0x11, func_80017BB8_main(chr, 0xE), 1, 0xF);
    func_800E5A00_minigame(obj, 0x12, func_80017BB8_main(chr, 0xF), 2, 0);
    func_800E5A00_minigame(obj, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(obj, 0x14, func_80017BB8_main(chr, 0x1D), 0, 0);
    func_800E5A00_minigame(obj, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(obj, 0x20, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5A00_minigame(obj, 9, func_80017BB8_main(chr, 7), 1, 0x27);
    func_800E5978_minigame(obj, 0x21, func_80017BB8_main(chr, 0x23), 2, 0);
    func_800E5A00_minigame(obj, 0x22, func_80017BB8_main(chr, 0x24), 2, 0);
    if (chr != 5) {
        func_800E5A00_minigame(obj, 5, func_80017BB8_main(chr, 0x8E), 0, 0);
        func_800E5A00_minigame(obj, 0x26, func_80017BB8_main(chr, 0x12), 0, 0);
        func_800E5A00_minigame(obj, 0x27, func_80017BB8_main(chr, 0x1C), 0, 0);
    } else {
        func_800E5A00_minigame(obj, 5, 0xA015C, 0, 0);
        func_800E5A00_minigame(obj, 0x26, 0xA015B, 0, 0);
        func_800E5A00_minigame(obj, 0x27, 0xA015A, 0, 0);
    }
    func_800E5A00_minigame(obj, 0x28, func_80017BB8_main(chr, 0x6C), 0, 0);
    func_800E5A00_minigame(obj, 0x29, func_80017BB8_main(chr, 0x9B), 0, 0);
    voice = &D_80113E1C_stardust_battle[rand8() & 1];
    func_800E5A00_minigame(obj, 0xD, func_80017BB8_main(chr, (s16)*voice), 1, 0x78);
    chrfile = &D_80113DFC_stardust_battle[chr];
    pl->unk18 = *chrfile | *voice;
    func_800E5A00_minigame(obj, 0xE, func_80017BB8_main(chr, 0x39), 1, 0x3C);
    pl->unk1C = *chrfile | 0x39;
    func_800E5690_minigame(obj, 0);
    func_800E149C_minigame(obj, 0, 2);
    pl->unk0C = 0;
    pl->unk0E = 0;
    pl->unk04 = -1;
    pl->unk0A = 0;
    pl->unk08 = 0;
    pl->unk66 = -1;
    pl->unk68 = 0;
    pl->unk6A = 0;
    pl->unk10 = -1;
    pl->unk12 = 0;
    pl->unk14 = 0;
    func_80107E84_stardust_battle(1);
    obj->func = func_801073F4_stardust_battle;
    omSetStatBit(obj, 0xA0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106EB0_stardust_battle);
#endif

/* NON_MATCHING: register allocation, and retail sign-extends the two saved stick bytes (lbu/sll/sra) where mine keeps lb; they are only stored back as bytes */
#ifdef NON_MATCHING
void func_801073F4_stardust_battle(omObjData *obj) {
    SbPlayer *pl;
    MgWork *work;
    HmfModel *model;
    u16 btn;
    s32 sx;
    s32 sy;
    s32 busy;
    s16 hit;

    busy = 0;
    pl = func_80111FEC_stardust_battle(obj);
    work = obj->data;
    model = &HmfModelData[obj->model[0]];
    if (func_80049F98_main() + D_800D6A90_main != 0) {
        func_8001C258_main(obj->model[0], 4, 0);
        return;
    }
    if (pl->unk6C != NULL) {
        pl->unk6C(obj);
    }
    btn = D_800D5558_main[pl->unk22];
    sx = D_800CBB6E_main[pl->unk22];
    sy = D_800D20A1_main[pl->unk22];
    if (model->unk06 == obj->motion[0x27]) {
        D_800D5558_main[pl->unk22] = 0;
        D_800D20A1_main[pl->unk22] = 0;
        D_800CBB6E_main[pl->unk22] = 0;
    } else if (pl->unk66 != -1) {
        D_800D5558_main[pl->unk22] &= ~0x4000;
    }
    if (pl->unk70 != NULL) {
        pl->unk70(obj);
    }
    func_800DDD94_minigame(obj);
    if (func_800E4A90_minigame(obj) & 0x8C00) {
        busy = 1;
    }
    if (pl->unk74 != NULL) {
        pl->unk74(obj);
    }
    D_800D5558_main[pl->unk22] = btn;
    D_800CBB6E_main[pl->unk22] = sx;
    D_800D20A1_main[pl->unk22] = sy;
    func_80107760_stardust_battle(obj, busy);
    if (busy == 0 && pl->unk14 == 0 && func_800E6E8C_minigame() == 2) {
        hit = func_8010E524_stardust_battle(obj, 0, NULL);
        pl->unk10 = hit;
        if (hit != -1) {
            if (hit == 0xFF) {
                pl->unk14 = 90;
            } else {
                D_80114ACE_stardust_battle = 1;
            }
            work->unk40 = D_800EB770_minigame;
            work->unk38 = -(D_800EB744_minigame * 0.65f);
            func_800E5690_minigame(obj, 9);
        }
        func_8010EA04_stardust_battle(obj);
    }
    func_801092F0_stardust_battle(obj);
    if (func_8010929C_stardust_battle() == 1) {
        func_8001C258_main(obj->model[1], 4, 4);
    }
    pl->unk2C.x = obj->trans.x;
    pl->unk2C.y = obj->trans.y;
    pl->unk2C.z = obj->trans.z;
    if (pl->unk14 != 0) {
        if (pl->unk0A & 1) {
            func_8001C258_main(obj->model[0], 4, 4);
        } else {
            func_8001C258_main(obj->model[0], 4, 0);
        }
        if (--pl->unk14 == 0) {
            func_8001C258_main(obj->model[0], 4, 0);
        }
    }
    pl->unk0A++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801073F4_stardust_battle);
#endif

void func_8001EED8_main(s16 mdl, s16 motion, s32 arg2); /* hmfman.c defines (s16, u8, s8) */
void func_8002367C_main(Matrix4f src, Matrix4f dst);
void func_80112220_stardust_battle(omObjData *obj, const char *part, Matrix4f out);
s16 func_8010E03C_stardust_battle(omObjData *obj);
void func_8010E35C_stardust_battle(s16 idx);

/* NON_MATCHING: scheduling only: in the "no item yet" case retail loads HmfModelData into a0 before the model-index multiply, mine into v1 after it */
#ifdef NON_MATCHING
void func_80107760_stardust_battle(omObjData *obj, s16 busy) {
    Matrix4f mtx;
    SbPlayer *pl;
    MgWork *work;
    HmfModel *model;
    HmfModel *m;
    SbItem *item;
    f32 t;
    s16 frame;
    f32 x;
    f32 y;
    f32 z;

    pl = func_80111FEC_stardust_battle(obj);
    model = &HmfModelData[obj->model[0]];
    work = obj->data;
    if (func_800E6E8C_minigame() == 2 && busy == 0) {
        switch (pl->unk66) {
        case -1:
            if (work->unk5C == 0x40) {
                m = &HmfModelData[obj->model[0]];
                frame = m->unk40;
                if (m->unk04 == 0xFF) {
                    if (!(frame < 10.0f) && !(frame > 20.0f)) {
                        pl->unk66 = func_8010E03C_stardust_battle(obj);
                        if (pl->unk66 != -1) {
                            func_80112220_stardust_battle(obj, "item_hook", mtx);
                            pl->unk6A = 1;
                            pl->unk68 = 0;
                        }
                    }
                }
            }
            break;
        case -2:
            if (D_800CCF58_main[model->unk06].unk02 <= model->unk58) {
                HmfModelData[obj->model[0]].unk06 = 0xFF;
                pl->unk66 = -1;
            }
            break;
        default:
            func_80112220_stardust_battle(obj, "item_hook", mtx);
            if (pl->unk6A < 5) {
                t = pl->unk6A / 5.0f;
                if (t < 0.0f) {
                    t = 0.0f;
                } else if (t > 1.0f) {
                    t = 1.0f;
                }
                item = func_8010E300_stardust_battle(pl->unk66);
                if (item != NULL) {
                    x = func_80111DF8_stardust_battle(t, item->unk58.x, mtx[3][0]);
                    y = func_80111DF8_stardust_battle(t, item->unk58.y, mtx[3][1]);
                    z = func_80111DF8_stardust_battle(t, item->unk58.z, mtx[3][2]);
                    func_80111DF8_stardust_battle(t, 0.0f, work->unk3C);
                    func_8010E46C_stardust_battle(pl->unk66, x, y, z);
                    mtx[3][0] = mtx[3][1] = mtx[3][2] = 0.0f;
                    func_80111E70_stardust_battle((f32 *)D_80114AD0_stardust_battle, (f32 *)mtx,
                                                  HmfModelData[item->unk02[item->unk10]].mtx, t);
                    func_8010E4C8_stardust_battle(pl->unk66, 0.0f, 0.0f, 0.0f);
                } else {
                    func_8010E46C_stardust_battle(pl->unk66, mtx[3][0], mtx[3][1], mtx[3][2]);
                    func_8010E4C8_stardust_battle(pl->unk66, 0.0f, work->unk3C, 0.0f);
                    pl->unk6A = 5;
                }
                pl->unk6A++;
            } else {
                func_8010E46C_stardust_battle(pl->unk66, mtx[3][0], mtx[3][1], mtx[3][2]);
                item = func_8010E300_stardust_battle(pl->unk66);
                if (item != NULL) {
                    mtx[3][0] = mtx[3][1] = mtx[3][2] = 0.0f;
                    func_8002367C_main((f32(*)[4])HmfModelData[item->unk02[item->unk10]].mtx, mtx);
                    func_8010E4C8_stardust_battle(pl->unk66, 0.0f, 0.0f, 0.0f);
                } else {
                    func_8010E4C8_stardust_battle(pl->unk66, 0.0f, work->unk3C, 0.0f);
                }
            }
            if (pl->unk68 == 0 && model->unk06 != obj->motion[0x26]) {
                if (work->unk5C == 0x40) {
                    if ((s16)HmfModelData[obj->model[0]].unk40 < 28) {
                    } else {
                        func_8001EED8_main(obj->model[0], obj->motion[0x26], 0);
                        pl->unk68 = 1;
                    }
                } else {
                    func_8001EED8_main(obj->model[0], obj->motion[0x26], 0);
                    pl->unk68 = 1;
                }
            }
            if (model->unk06 == obj->motion[0x26] && (D_800D5558_main[pl->unk22] & 0x4000)) {
                if (work->unk5C != 0x40) {
                    func_8001EED8_main(obj->model[0], obj->motion[0x27], 0);
                    model->unk5C = 2.0f;
                }
            } else if (model->unk06 == obj->motion[0x27]
                       && D_800CCF58_main[model->unk06].unk02 * 0.5f <= model->unk58) {
                func_8010E4C8_stardust_battle(pl->unk66, 0.0f, work->unk3C, 0.0f);
                func_8010E35C_stardust_battle(pl->unk66);
                pl->unk66 = -2;
            }
            break;
        }
    } else {
        if (pl->unk66 >= 0) {
            item = func_8010E300_stardust_battle(pl->unk66);
            if (item != NULL) {
                Hu3DModelScaleSet(func_8000D550_main(D_80114B54_stardust_battle, item->unk28.x, item->unk28.y, item->unk28.z), 2.0f, 2.0f, 2.0f);
                func_8010DF70_stardust_battle(pl->unk66);
            }
            pl->unk66 = -1;
        }
        if (model->unk06 != 0xFF) {
            HmfModelData[obj->model[0]].unk06 = 0xFF;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107760_stardust_battle);
#endif

void func_80107DCC_stardust_battle(omObjData *obj, s16 mode) {
    SbPlayer *pl;

    if (obj != NULL) {
        pl = func_80111FEC_stardust_battle(obj);
        if (pl->unk78 != NULL) {
            pl->unk78(obj);
            pl->unk78 = NULL;
        }
        if (D_80113E24_stardust_battle[mode] != NULL) {
            D_80113E24_stardust_battle[mode](obj);
        }
        pl->unk70 = D_80113E30_stardust_battle[mode];
        pl->unk74 = D_80113E3C_stardust_battle[mode];
        pl->unk78 = D_80113E48_stardust_battle[mode];
    }
}

s16 func_80107E84_stardust_battle(s16 hmf) {
    omObjData *obj = D_800EC598_minigame[0];
    SbPlayer *pl = func_80111FEC_stardust_battle(obj);
    HmfModel *a = &HmfModelData[obj->model[0]];
    HmfModel *b = &HmfModelData[obj->model[9]];
    HmfData *tmp;

    if (pl->unk12 == hmf) {
        return hmf;
    }
    tmp = b->hmf;
    b->hmf = a->hmf;
    a->hmf = tmp;
    pl->unk12 = hmf;
    return hmf;
}

void func_80107F34_stardust_battle(f32 step) {
    MgWork *work = D_800EC598_minigame[0]->data;

    work->unk3C = func_80111C2C_stardust_battle(atan2df(D_80114B18_stardust_battle->trans.x - D_800EC598_minigame[0]->trans.x, D_80114B18_stardust_battle->trans.z - D_800EC598_minigame[0]->trans.z), work->unk3C, step);
}

s16 func_80107FA4_stardust_battle(void) {
    SbPlayer *pl;

    if (D_800EC280_minigame == 0) {
        return 0;
    }
    pl = func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
    pl->unk6C = func_80108120_stardust_battle;
    pl->unk3A = 0;
    return 1;
}

s16 func_80107FE8_stardust_battle(void) {
    SbPlayer *pl;

    if (D_800EC280_minigame != 0) {
        pl = func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
        if (pl->unk6C == func_80108120_stardust_battle && pl->unk3A >= 2 && !(pl->unk3C < 22.5f)) {
            return 1;
        }
    }
    return 0;
}

void func_80108074_stardust_battle(void) {
    if (D_800EC280_minigame != 0) {
        ((SbPlayer *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]))->unk6C = func_801081FC_stardust_battle;
    }
}

void func_801080B0_stardust_battle(void) {
    if (D_800EC280_minigame != 0) {
        ((SbPlayer *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]))->unk6C = func_801082C4_stardust_battle;
    }
}

void func_801080EC_stardust_battle(void) {
    if (D_800EC280_minigame != 0) {
        ((SbPlayer *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]))->unk6C = NULL;
    }
}

void func_80108120_stardust_battle(omObjData *obj) {
    SbPlayer *pl = func_80111FEC_stardust_battle(obj);

    switch (pl->unk3A) {
    case 0:
        func_800E5690_minigame(obj, 0x28);
        pl->unk3A++;
        break;
    case 1:
        if (func_800E4A90_minigame(obj) == 1) {
            func_800E5690_minigame(obj, 0x29);
            pl->unk3A++;
            pl->unk3C = 0;
        }
        break;
    case 2:
        pl->unk3C++;
        if (func_800E4A90_minigame(obj) == 1) {
            pl->unk6C = NULL;
            pl->unk3C = 0;
            pl->unk3A = 0;
        }
        break;
    }
}

void func_801081FC_stardust_battle(omObjData *obj) {
    f32 x = obj->trans.x;
    f32 z = obj->trans.z;

    if (x > 200.0) {
        x = 200.0f;
    } else if (x < -200.0) {
        x = -200.0f;
    }
    if (z > 300.0) {
        z = 300.0f;
    }
    func_801117E4_stardust_battle(x, 65535.0f, z, 65535.0f, 65535.0f, 65535.0f, 65535.0f, 1);
}

void func_801082C4_stardust_battle(omObjData *obj) {
    SbPlayer *pl = func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
    MgWork *work = obj->data;

    if (pl->unk04 != -1 && work->unk38 == 1000.0f && !(func_800E4A90_minigame(obj) & 0x8C00)) {
        if (pl->unk04 == 13) {
            if (func_80111B28_stardust_battle(0.0f, work->unk3C) < 5.0f) {
                work->unk3C = 0.0f;
            } else {
                work->unk3C = func_80111C2C_stardust_battle(0.0f, work->unk3C, 5.0f);
                return;
            }
        }
        HmfModelData[obj->model[0]].unk06 = 0xFF;
        func_800E5798_minigame(obj, pl->unk04);
        func_80045F1C_main(pl->unk04 == 13 ? pl->unk18 : pl->unk1C, -1, pl->unk20);
        pl->unk04 = -1;
    }
}

void func_80108404_stardust_battle(omObjData *obj) {
    D_800EB744_minigame = 1.47f;
    D_800EB748_minigame = 0.15f;
    D_800EB774_minigame = 1.7f;
}

void func_80108444_stardust_battle(void) {
}

void func_8010844C_stardust_battle(void) {
}

void func_80108454_stardust_battle(omObjData *obj) {
    SbPlayer *pl = func_80111FEC_stardust_battle(obj);

    D_800EB744_minigame = 1.029f;
    D_800EB748_minigame = 0.105000004f;
    D_800EB774_minigame = 1.19f;
    pl->unk0A = 0;
}

void func_801084B0_stardust_battle(omObjData *obj) {
    SbPlayer *pl = func_80111FEC_stardust_battle(obj);
    f32 x;
    f32 y;
    f32 len;
    s16 idx;

    idx = pl->unk22;
    x = D_800CBB6E_main[idx];
    y = D_800D20A1_main[idx];
    if (x > 60.0f) {
        x = 60.0f;
    } else if (x < -60.0f) {
        x = -60.0f;
    } else {
        x = D_800CBB6E_main[pl->unk22];
    }
    if (y > 60.0f) {
        y = 60.0f;
    } else if (y < -60.0f) {
        y = -60.0f;
    } else {
        y = D_800D20A1_main[pl->unk22];
    }
    if (fabs(x) < 8.0) {
        x = 0.0f;
    }
    if (fabs(y) < 8.0) {
        y = 0.0f;
    }
    len = sqrtf(x * x + y * y);
    if (len != 0.0f) {
        len = 1.0f / len;
    } else {
        len = 0.0f;
    }
    D_800CBB6E_main[pl->unk22] = x * len * 60.0f * 0.8f;
    D_800D20A1_main[pl->unk22] = y * len * 60.0f * 0.8f;
}

void func_801086E8_stardust_battle(omObjData *obj) {
    SbPlayer *pl = func_80111FEC_stardust_battle(obj);
    s32 v;
    s32 idx;

    if (obj->trans.y == 0.0f) {
        idx = pl->unk22;
        v = D_800CBB6E_main[idx];
        if (v < 0) {
            v = -v;
        }
        if (v < 17) {
            v = D_800D20A1_main[idx];
            if (v < 0) {
                v = -v;
            }
            if (v < 17) {
                goto still;
            }
        }
        pl->unk0C = 1;
    } else {
    still:
        pl->unk0C = 0;
    }
    if (pl->unk0C != 0) {
        pl->unk0E++;
    } else {
        pl->unk0E = 0;
    }
    if (D_80114B14_stardust_battle != 1) {
        if ((obj->trans.y != 0.0f || !(pl->unk2C.y > 0.0f)) && pl->unk0C != 0 && pl->unk0E == 20) {
            pl->unk0E = 0;
        }
        if (!(pl->unk0A & 0xF)) {
            func_8010A04C_stardust_battle(D_80114B18_stardust_battle->trans.x, D_80114B18_stardust_battle->trans.z, 37.5f, 7.5000005f, 0.0f, 0.0f);
        }
    }
}

void func_8010882C_stardust_battle(omObjData *obj) {
    SbPlayer *pl = func_80111FEC_stardust_battle(obj);
    HmfModel *body = &HmfModelData[obj->model[0]];
    HmfModel *shadow;
    f32 *mtx;

    D_800EB744_minigame = 1.47f;
    D_800EB748_minigame = 0.15f;
    D_800EB774_minigame = 1.7f;
    obj->model[10] = func_8000B108_main(D_800A178C_main[pl->unk24][0] | D_800A178C_main[pl->unk24][1], 0x689);
    func_8001ED54_main(obj->model[10]);
    func_8001C448_main(obj->model[10]);
    func_8001C514_main(obj->model[10]);
    shadow = &HmfModelData[obj->model[10]];
    pl->unk38 = shadow->unk02;
    shadow->unk02 = body->unk02;
    shadow->unk40 = body->unk40;
    shadow->unk44 = 0.0f;
    shadow->unk04 = body->unk04;
    shadow->unk4C = body->unk4C;
    shadow->unk50 = 0.0f;
    shadow->unk06 = body->unk06;
    shadow->unk58 = body->unk58;
    shadow->unk5C = 0.0f;
    shadow->unk0C = body->unk0C;
    shadow->unk0E = body->unk0E;
    mtx = shadow->mtx;
    guMtxIdentF((f32 (*)[4])mtx);
    func_80017CD0_main((f32 (*)[4])mtx, 1.0f, -1.0f, 1.0f);
}

void func_801089B4_stardust_battle(void) {
}

void func_801089BC_stardust_battle(omObjData *obj) {
    MgWork *work;
    HmfModel *body;
    HmfModel *shadow;

    if (obj->model[10] != -1) {
        func_80111FEC_stardust_battle(obj);
        work = obj->data;
        body = &HmfModelData[obj->model[0]];
        shadow = &HmfModelData[obj->model[10]];
        Hu3DModelPosSet(obj->model[10], obj->trans.x, -obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[10], obj->rot.x, work->unk3C, obj->rot.z);
    shadow->unk02 = body->unk02;
    shadow->unk40 = body->unk40;
    shadow->unk44 = 0.0f;
    shadow->unk04 = body->unk04;
    shadow->unk4C = body->unk4C;
    shadow->unk50 = 0.0f;
    shadow->unk06 = body->unk06;
    shadow->unk58 = body->unk58;
    shadow->unk5C = 0.0f;
    shadow->unk0C = body->unk0C;
    shadow->unk0E = body->unk0E;
    }
}

void func_80108AC4_stardust_battle(omObjData *obj) {
    SbPlayer *pl = func_80111FEC_stardust_battle(obj);
    HmfModel *shadow = &HmfModelData[obj->model[10]];

    shadow->unk02 = pl->unk38;
    shadow->unk04 = 0xFF;
    shadow->unk06 = 0xFF;
    func_8001ACDC_main(obj->model[10]);
    obj->model[10] = -1;
}

void func_80108B34_stardust_battle(void) {
    SbStage *st;
    omObjData *obj;

    D_80114B10_stardust_battle = st = HuMemAllocTag(sizeof(SbStage), 31000);
    memset(st, 0, sizeof(SbStage));
    st->unk00 = -1;
    st->unk20 = 0;
    st->unk24 = NULL;
    st->unk28 = NULL;
    st->unk30 = NULL;
    st->unk34 = NULL;
    obj = omAddObj(3, 8, 0, -1, func_80108C14_stardust_battle);
    D_800EC1C0_minigame[(u16)D_800EBE28_minigame] = obj;
    omSetStatBit(obj, 0xA0);
    func_80111FC0_stardust_battle(D_800EC1C0_minigame[(u16)D_800EBE28_minigame], (u32)st);
    D_800EBE28_minigame++;
    func_800E1490_minigame(0);
}

void func_80108C14_stardust_battle(omObjData *obj) {
    SbStage *st = func_80111FEC_stardust_battle(obj);
    MgWork *work;
    HmfData *hmf;

    obj->data = HuMemAllocTag(0xB4, 31000); /* the ground object's part of MgWork */
    work = obj->data;
    memset(work, 0, 0xB4);
    work->unk00[3] = 1;
    work->unk04 = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 1.0f);
    func_800E1310_minigame(obj, 10.0f);
    func_800E1370_minigame(obj, 2, 0.0f);
    func_80109128_stardust_battle(0);
    obj->model[2] = func_8000B108_main(0x62000A, 0x19);
    Hu3DModelScaleSet(obj->model[2], 1.75f, 1.5f, 1.5f);
    Hu3DModelPosSet(obj->model[2], 0.0f, -200.0f, 0.0f);
    func_8001C954_main(obj->model[2]);
    hmf = HmfModelData[obj->model[2]].hmf;
    st->unk02 = func_8002C834_main(hmf, "stardast-cyl10");
    st->unk04 = func_8002C834_main(hmf, "stardast-cyl5_1");
    st->unk18 = st->unk1C = st->unk10 = st->unk14 = st->unk08 = st->unk0C = 0.0f;
    obj->func = func_80108D84_stardust_battle;
}

void func_80108D84_stardust_battle(omObjData *obj) {
    SbStage *st = func_80111FEC_stardust_battle(obj);

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        st->unk0C += 2.0f;
        if (st->unk0C >= 64.0f) {
            st->unk0C -= 128.0f;
        }
        st->unk10 -= 0.25f;
        if (st->unk10 <= -32.0f) {
            st->unk10 += 64.0f;
        }
    }
    func_80108EC4_stardust_battle(obj->model[2], st->unk08, st->unk0C, 0x40, 0x40, st->unk02);
    func_80108EC4_stardust_battle(obj->model[2], st->unk10, st->unk14, 0x20, 0x20, st->unk04);
    if (st->unk30 != NULL) {
        st->unk30(obj);
    }
}

/* NON_MATCHING: scheduling only: retail loads hmf->unk60 before sign-extending the material index */
#ifdef NON_MATCHING
void func_80108EC4_stardust_battle(s16 mdl, f32 u, f32 v, s32 w, s32 h, s32 mat) {
    HmfData *hmf = HmfModelData[mdl].hmf;
    HmfModelData_Unk64_Unk60_Struct *m;
    Vtx *src;
    Vtx *dst;
    u16 su;
    u16 sv;
    u16 tw;
    u16 th;
    s16 n;
    s16 i;

    if (hmf != NULL) {
        m = &hmf->unk60[(s16)mat];
        n = m->unk2A;
        src = (Vtx *)hmf->unk40 + m->unk28;
        dst = &hmf->unk44[D_800D2008_main][m->unk28];
        tw = w << 5;
        th = h << 5;
        su = u * 32.0f;
        sv = v * 32.0f;
        if (u < 0.0f) {
            u = -u;
        }
        if (v < 0.0f) {
            v = -v;
        }
        if (u * 32.0f > tw) {
            su %= tw;
        }
        if (v * 32.0f > th) {
            sv %= th;
        }
        for (i = 0; i < n; i++) {
            dst->v.tc[0] = su + src->v.tc[0];
            dst->v.tc[1] = sv + src->v.tc[1];
            src++;
            dst++;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108EC4_stardust_battle);
#endif

void func_80109128_stardust_battle(s16 mode) {
    omObjData *obj;
    SbStage *st;
    u16 n = D_800EBE28_minigame;

    if (n != 0 && D_800EC280_minigame != 0) {
        obj = D_800EC1C0_minigame[n - 1];
        st = func_80111FEC_stardust_battle(obj);
        if (st->unk00 != mode) {
            func_80107DCC_stardust_battle(D_800EC598_minigame[0], mode);
            if (st->unk34 != NULL) {
                st->unk34(obj);
                st->unk34 = NULL;
            }
            st->unk00 = mode;
            st->unk30 = D_80113E78_stardust_battle[mode];
            st->unk34 = D_80113E84_stardust_battle[mode];
            if (obj->model[0] != -1) {
                func_8001ACDC_main(obj->model[0]);
            }
            if (obj->model[1] != -1) {
                func_8001ACDC_main(obj->model[1]);
            }
            obj->model[0] = func_8000B108_main(D_80113E60_stardust_battle[mode] | 0x620000, 0x699);
            obj->model[1] = func_8000B108_main(D_80113E54_stardust_battle[mode] | 0x620000, D_80113E6C_stardust_battle[mode] | 0x299);
            if (st->unk30 != NULL) {
                st->unk30(obj);
            }
        }
    }
}

s16 func_8010929C_stardust_battle(void) {
    if (*(u16 *)&D_800EBE28_minigame != 0 && D_800EC280_minigame != 0) {
        return ((SbStage *)func_80111FEC_stardust_battle(D_800EC1C0_minigame[(u16)D_800EBE28_minigame - 1]))->unk00;
    }
    return 0;
}

void func_801092F0_stardust_battle(omObjData *obj) {
    MgWork *work = obj->data;
    f32 d = obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z;
    f32 r = fabs(525.0 - work->unk48);

    if (r * r < d) {
        d = sqrtf(d);
        if (d != 0.0f) {
            d = r / d;
        } else {
            obj->trans.x = 0.0f;
            obj->trans.z = r;
            d = 1.0f;
        }
        obj->trans.x = d * obj->trans.x;
        obj->trans.z = d * obj->trans.z;
    }
}

void func_801093CC_stardust_battle(omObjData *obj) {
    SbStage *st = func_80111FEC_stardust_battle(obj);

    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 1.0f);
    func_800E1310_minigame(obj, 10.0f);
    st->unk30 = NULL;
}

void func_8001EFEC_main(s16 mdl, const char *name);

/* NON_MATCHING: scheduling only: retail loads HmfModelData into v1 after the model-index multiply, mine into a0 before it */
#ifdef NON_MATCHING

void func_80109424_stardust_battle(omObjData *obj) {
    SbStage *st;
    HmfData *hmf;
    SbVtxGroup *buf;
    Vtx *v;
    s32 i;
    s32 j;
    f32 r;
    f32 inv;
    f32 s;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 x;
    f32 a;

    st = func_80111FEC_stardust_battle(obj);
    hmf = HmfModelData[obj->model[1]].hmf;
    i = 0;
    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 1.5f);
    func_800E1310_minigame(obj, 8.0f);
    func_8001C954_main(obj->model[1]);
    func_8001EFEC_main(obj->model[1], "co_y02_DEF");
    hmf->unk60->unk50 |= 0x08000000;
    buf = HuMemAlloc(SB_HMF_VTXNUM(hmf) * sizeof(SbVtxGroup));
    memset(buf, 0, SB_HMF_VTXNUM(hmf) * sizeof(SbVtxGroup));
    v = hmf->unk40;
    st->unk20 = 0;
    for (; i < SB_HMF_VTXNUM(hmf); i++, v++) {
        for (j = 0; j < st->unk20; j++) {
            if (buf[j].x != v->v.ob[0]) {
                continue;
            }
            if (buf[j].y != v->v.ob[1]) {
                continue;
            }
            if (buf[j].z != v->v.ob[2]) {
                continue;
            }
            if (buf[j].n < 8) {
                buf[j].idx[buf[j].n] = i;
                buf[j].n++;
            } else {
                osSyncPrintf("VTX OVER %d \n", i);
            }
            break;
        }
        if (j < st->unk20) {
            continue;
        }
        buf[st->unk20].x = v->v.ob[0];
        buf[st->unk20].y = v->v.ob[1];
        buf[st->unk20].z = v->v.ob[2];
        buf[st->unk20].n = 1;
        buf[st->unk20].idx[0] = i;
        r = sqrtf(v->v.ob[0] * v->v.ob[0] + v->v.ob[2] * v->v.ob[2]);
        if (r != 0.0f) {
            inv = 1.0f / r;
        } else {
            inv = 0.0f;
        }
        r = r / 600.0;
        if (r >= 1.0f) {
            r = 1.0f;
        }
        s = sindf(r * 90.0f);
        nx = buf[st->unk20].x * inv * s * 128.0f;
        nz = buf[st->unk20].z * inv * s * 128.0f;
        ny = (1.0f - s) * 128.0f;
        r = sqrtf(nx * nx + ny * ny + nz * nz);
        if (r != 0.0f) {
            nx /= r;
            ny /= r;
            nz /= r;
        }
        buf[st->unk20].unk1C = 0.0f;
        buf[st->unk20].unk20 = 1.0f;
        buf[st->unk20].unk24 = 0.0f;
        buf[st->unk20].unk28 = 0.0f;
        if (sqrtf(buf[st->unk20].x * buf[st->unk20].x + buf[st->unk20].z * buf[st->unk20].z) > 525.0) {
            buf[st->unk20].unk18 = 1;
        } else {
            buf[st->unk20].unk18 = 0;
        }
        st->unk20++;
    }
    st->unk24 = HuMemAllocTag(st->unk20 * sizeof(SbVtxGroup), 31000);
    memcpy(st->unk24, buf, st->unk20 * sizeof(SbVtxGroup));
    HuMemFree(buf);
    func_80109FE4_stardust_battle(obj);
    a = 0.0f;
    for (i = 0; i < 8; i++) {
        x = (f32)(u8)(rand8() % 100) * 0.01 * 100.0;
        func_8010A04C_stardust_battle(x, (f32)(u8)(rand8() % 100) * 0.01 * 100.0, 31.25f, 7.5000005f, 1.0f, a);
        a += 120.00000476837158;
    }
    st->unk30 = func_80109B18_stardust_battle;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109424_stardust_battle);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109B18_stardust_battle);

void func_80109F94_stardust_battle(omObjData *obj) {
    SbStage *st = func_80111FEC_stardust_battle(obj);

    if (st->unk24 != NULL) {
        HuMemFree(st->unk24);
    }
    st->unk24 = NULL;
    func_8010A5A4_stardust_battle(obj);
}

void func_80109FE4_stardust_battle(omObjData *obj) {
    SbStage *st = func_80111FEC_stardust_battle(obj);
    SbDust *d;
    s32 i;

    if (st->unk28 == NULL) {
        d = st->unk28 = HuMemAllocTag(sizeof(SbDust) * 64, 31000);
        memset(d, 0, sizeof(SbDust) * 64);
        for (i = 0; i < 64; i++, d++) {
            d->unk01 = i;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A04C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A204_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A418_stardust_battle);

void func_8010A5A4_stardust_battle(omObjData *obj) {
    SbStage *st = func_80111FEC_stardust_battle(obj);

    if (st->unk28 != NULL) {
        HuMemFree(st->unk28);
    }
    st->unk28 = NULL;
}

void func_8010A5E0_stardust_battle(omObjData *obj) {
    SbStage *st = func_80111FEC_stardust_battle(obj);
    HmfData *hmf = HmfModelData[obj->model[0]].hmf;

    func_800E131C_minigame(obj, 20.0f);
    func_800E1304_minigame(obj, 0.1f);
    func_800E1310_minigame(obj, 5.0f);
    func_8001C954_main(obj->model[0]);
    st->unk2C = func_8002C834_main(hmf, "comet-nagare");
    st->unk30 = func_8010A690_stardust_battle;
}

void func_8010A690_stardust_battle(omObjData *obj) {
    SbStage *st = func_80111FEC_stardust_battle(obj);

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        st->unk1C += 2.0f;
        if (st->unk1C >= 64.0f) {
            st->unk1C -= 128.0f;
        }
    }
    func_80108EC4_stardust_battle(obj->model[0], st->unk18, st->unk1C, 0x40, 0x40, st->unk2C);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A74C_stardust_battle);

/* NON_MATCHING: register allocation (f20/f22 for the case-2 scale and the case-3 deltas), the trail-distance loads and one andi before func_80110758; ops, calls and fields equal */
#ifdef NON_MATCHING
void func_8010AAC4_stardust_battle(omObjData *obj) {
    SbBoss *boss = func_80111FEC_stardust_battle(obj);
    Vec dust;
    Vec hit;
    Vec pos;
    f32 k;
    f32 dz;
    f32 dx;
    f32 a;
    f32 r;
    u8 rnd;
    s32 n;
    s32 gap;
    s16 mode;

    if (boss->unk24 != 0) {
        obj->trans.y += boss->unk2C;
        boss->unk24--;
    }
    pos.x = obj->trans.x;
    pos.y = obj->trans.y;
    pos.z = obj->trans.z;
    (void)pos; /* retail stores the start position and never reads it */
    switch (boss->unk04) {
    case 0:
        if (func_800E6E8C_minigame() == 2) {
            boss->unk00 = 0;
            boss->unk04 = 1;
        }
        break;
    case 1:
        if (boss->unk00 > 30) {
            boss->unk00 = 0;
            if (D_80114AB0_stardust_battle < 5340) {
                boss->unk04 = 2;
            }
        }
        break;
    case 2:
        if (boss->unk00 > 30) {
            k = 1.0f - (boss->unk00 - 30) / 15.0f;
        } else {
            if (boss->unk00 == 1) {
                HuAudFXPlay(0x508);
            }
            k = 1.0f;
        }
        obj->rot.z = sindf(fmod(boss->unk00 * 25.0f, 360.0)) * k * 30.0f;
        if (boss->unk00 > 45.0f) {
            obj->rot.z = 0.0f;
            boss->unk00 = 0;
            boss->unk04 = 3;
        }
        break;
    case 3:
        if (boss->unk14 >= D_80113EA8_stardust_battle[boss->unk0C]) {
            if (boss->unk12 >= 10) {
                func_8010C5A8_stardust_battle(10, 10);
                boss->unk12 = 0;
            }
            func_8010DE64_stardust_battle(func_8010CA48_stardust_battle(boss->unk12), D_80113E98_stardust_battle[boss->unk0C]);
            HuAudFXPlay(0x50D);
            boss->unk14 = 0;
            boss->unk12++;
        }
        boss->unk14++;
        dx = boss->unk34.x - obj->trans.x;
        dz = boss->unk34.z - obj->trans.z;
        boss->unk1C = func_80111C2C_stardust_battle(atan2df(dx, dz), boss->unk1C, 15.0f);
        obj->trans.x += sindf(boss->unk1C) * boss->unk58;
        obj->trans.z += cosdf(boss->unk1C) * boss->unk58;
        if (dx * dx + dz * dz < 22500.0) {
            a = rand16() % 360;
            r = fmod((f32)rand16(), 400.0) + 100.0;
            boss->unk34.x = sindf(a) * r;
            boss->unk34.z = cosdf(a) * r;
        }
        if (boss->unk00 > 150.0f) {
            if (boss->unk58 > 0.0f) {
                boss->unk58 -= 0.999999977648258209;
                if (boss->unk58 <= 0.0f) {
                    boss->unk58 = 0.0f;
                    func_8010BFE4_stardust_battle(100.0f, 60);
                    boss->unk0A = 1;
                    boss->unk00 = 0;
                    boss->unk04 = 4;
                }
            }
        } else if (boss->unk58 < 15.0000005960464478) {
            boss->unk58 += 0.999999977648258209;
        }
        break;
    case 4:
        if (boss->unk00 >= 30) {
            boss->unk00 = 0;
            boss->unk04 = 5;
        }
        break;
    case 5:
        if (boss->unk24 == 0) {
            if (boss->unk00 >= boss->unk10) {
                func_8010BFE4_stardust_battle(450.0f, 60);
                boss->unk00 = 0;
                boss->unk04 = 6;
            }
        } else {
            boss->unk00 = 0;
        }
        break;
    case 6:
        if (boss->unk24 == 0) {
            a = rand16() % 360;
            r = fmod((f32)rand16(), 500.0);
            boss->unk34.x = sindf(a) * r;
            boss->unk34.z = cosdf(a) * r;
            boss->unk0A = 0;
            if (boss->unk06 <= D_80114B28_stardust_battle[boss->unk0C]) {
                boss->unk0E = boss->unk0C + 1;
            }
            boss->unk00 = 0;
            if (boss->unk0C != boss->unk0E && D_80114AC4_stardust_battle != 0 && D_80114AB0_stardust_battle < 5250) {
                HuAudFXPlay(0x50E);
                boss->unk04 = 8;
            } else if (D_80114AB0_stardust_battle < 5340) {
                boss->unk04 = 2;
            } else {
                boss->unk04 = 1;
            }
        }
        break;
    case 7:
        boss->unk0A = 0;
        k = 1.0f - boss->unk00 / 9.99f;
        obj->trans.x += boss->unk28;
        obj->trans.z += boss->unk30;
        obj->rot.z = -(sindf(boss->unk20) * k * 45.0f);
        obj->rot.x = cosdf(boss->unk20) * k * 45.0f;
        if (boss->unk00 & 1) {
            obj->trans.x = obj->trans.x + 50.0;
        } else {
            obj->trans.x = obj->trans.x - 50.0;
        }
        if (boss->unk00 >= 9.99f) {
            boss->unk0A = 0;
            k = boss->unk06 / 9.0f;
            boss->unk68 = func_80111DF8_stardust_battle(k, 1.0f, 0.0f);
            boss->unk70 = func_80111DF8_stardust_battle(k, 0.0f, 1.0f);
            obj->rot.z = obj->rot.x = 0.0f;
            boss->unk00 = 0;
            if (boss->unk06 != 0 && func_800E6E8C_minigame() == 2) {
                func_8010BFE4_stardust_battle(450.0f, 30);
                boss->unk04 = 6;
            } else {
                boss->unk04 = 12;
            }
        }
        break;
    case 8:
        if (boss->unk00 >= 15.0f) {
            if (boss->unk18 < 45.0f) {
                boss->unk18 += 5.0f;
            }
            obj->rot.y += boss->unk18;
            if (obj->rot.y > 360.0f) {
                obj->rot.y -= 360.0f;
            }
            if (boss->unk00 >= 45.0f) {
                WipeColorSet(0xFF, 0xFF, 0xFF);
                WipeCreateOut(11, 30);
                boss->unk00 = 0;
                boss->unk04 = 9;
                HuAudFXPlay(0x509);
            }
        }
        break;
    case 9:
        obj->rot.y += boss->unk18;
        if (obj->rot.y > 360.0f) {
            obj->rot.y -= 360.0f;
        }
        if (WipeStatGet() == 0) {
            func_80109128_stardust_battle(D_80113E90_stardust_battle[boss->unk0E]);
            boss->unk0C = boss->unk0E;
            obj->rot.y = 0.0f;
            boss->unk18 = 0.0f;
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateIn(11, 15);
            switch (boss->unk0C) {
            case 1:
                HuAudFXPlay(0x50F);
                break;
            case 2:
                HuAudFXPlay(0x510);
                break;
            }
            boss->unk00 = 0;
            boss->unk04 = 10;
        }
        break;
    case 10:
        if (WipeStatGet() == 0) {
            boss->unk00 = 0;
            boss->unk04 = 1;
        }
        break;
    case 11:
        boss->unk0A = 0;
        obj->rot.x = func_80111C2C_stardust_battle(0.0f, obj->rot.x, 10.0f);
        obj->rot.y = func_80111C2C_stardust_battle(0.0f, obj->rot.y, 10.0f);
        obj->rot.z = func_80111C2C_stardust_battle(0.0f, obj->rot.z, 10.0f);
        if (func_80111B28_stardust_battle(0.0f, obj->rot.x) < 10.0f && func_80111B28_stardust_battle(0.0f, obj->rot.y) < 10.0f && func_80111B28_stardust_battle(0.0f, obj->rot.z) < 10.0f) {
            obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
            boss->unk04 = 12;
        }
        break;
    case 13:
        boss->unk0A = 0;
        k = (f32)boss->unk00 / boss->unk26;
        if (k > 1.0f) {
            k = 1.0f;
        } else if (k < 0.0f) {
            k = 0.0f;
        }
        k = sindf(k * 90.0f);
        obj->trans.x = func_80111DF8_stardust_battle(k, boss->unk40.x, boss->unk34.x);
        obj->trans.y = func_80111DF8_stardust_battle(k, boss->unk40.y, boss->unk34.y);
        obj->trans.z = func_80111DF8_stardust_battle(k, boss->unk40.z, boss->unk34.z);
        if (boss->unk00 >= boss->unk26) {
            obj->trans.x = boss->unk34.x;
            obj->trans.y = boss->unk34.y;
            obj->trans.z = boss->unk34.z;
            boss->unk26 = 0;
            boss->unk00 = 0;
            boss->unk04 = 14;
        }
        break;
    case 12:
    case 14:
        boss->unk0A = 0;
        break;
    case 16:
        if (boss->unk00 < 30) {
            obj->rot.x = sindf(boss->unk00 / 30.0f * 90.0f) * 30.0f;
        } else if (boss->unk00 > 90.0f) {
            obj->rot.x = 30.0f - sindf((boss->unk00 - 90.0f) / 30.0f * 90.0f) * 30.0f;
            if (boss->unk00 > 120.0f) {
                obj->rot.x = 0.0f;
                boss->unk00 = 0;
                boss->unk04 = 0;
            }
        }
        break;
    case 17:
        if (boss->unk18 < 22.5f) {
            boss->unk18 = boss->unk18 + 5.0f;
        } else {
            boss->unk18 = 22.5f;
        }
        obj->rot.y += boss->unk18;
        if (obj->rot.y > 360.0f) {
            obj->rot.y -= 360.0f;
        }
        if (boss->unk00 & 1) {
            rnd = rand8();
            obj->trans.y = boss->unk4C.y + 5.00000007450580597 + (f32)(u8)(rnd % 100) * 0.01 * 5.00000007450580597;
            n = rnd / 100;
        } else {
            rnd = rand8();
            obj->trans.y = boss->unk4C.y - 5.00000007450580597 - (f32)(u8)(rnd % 100) * 0.01 * 5.00000007450580597;
            n = rnd / 100;
        }
        func_80110758_stardust_battle(boss->unk4C.x, boss->unk4C.y + 80.0000011920928955, boss->unk4C.z, n);
        if (boss->unk16 <= 16) {
            if ((u16)boss->unk16 < 4) {
                if (boss->unk00 >= D_80113EB0_stardust_battle[boss->unk16]) {
                    HuAudFXPlay(0x50A);
                    boss->unk16++;
                    boss->unk00 = 0;
                }
            } else if (boss->unk00 & 1) {
                HuAudFXPlay(0x50A);
                boss->unk16++;
            }
            if (boss->unk16 < 16) {
                func_80110780_stardust_battle(boss->unk16);
            } else {
                func_801107C4_stardust_battle(boss->unk16);
            }
        }
        if (!(boss->unk00 & 7)) {
            dust.x = boss->unk4C.x + 2.0 * ((0.5 - (f32)(u8)(rand8() % 100) * 0.01) * 100.0);
            dust.z = boss->unk4C.z + 2.0 * ((0.5 - (f32)(u8)(rand8() % 100) * 0.01) * 100.0);
            dust.y = boss->unk4C.y + (f32)(u8)(rand8() % 100) * 0.01 * 150.0;
            Hu3DModelScaleSet(func_8000D550_main(D_80114B54_stardust_battle, dust.x, dust.y, dust.z), 2.0f, 2.0f, 2.0f);
        }
        break;
    }
    if (boss->unk0A != 0) {
        boss->unk08 = func_8010E524_stardust_battle(obj, 1, &hit);
        if (boss->unk08 != -1) {
            if (boss->unk06 != 0) {
                boss->unk06--;
            }
            boss->unk10 -= 4;
            if (boss->unk10 < 15.0f) {
                boss->unk10 = 15;
            }
            boss->unk20 = atan2df(hit.x, hit.z);
            boss->unk28 = sindf(boss->unk20) * 100.0 * 0.100100100040435791;
            boss->unk30 = cosdf(boss->unk20) * 100.0 * 0.100100100040435791;
            boss->unk04 = 7;
            boss->unk00 = 0;
        }
    }
    func_800465A8_main(obj->model[0], boss->unk68, boss->unk6C, boss->unk70);
    dx = obj->trans.x - boss->unk5C;
    dz = obj->trans.z - boss->unk60;
    gap = 16;
    if (dx * dx + dz * dz > 100.000002980232267) {
        gap = 8;
        boss->unk64 = func_80111C2C_stardust_battle(atan2df(dx, dz), boss->unk64, 10.0f);
        boss->unk5C = boss->unk5C + sindf(boss->unk64) * 100.0 * 0.0666666701436042786;
        boss->unk60 = boss->unk60 + cosdf(boss->unk64) * 100.0 * 0.0666666701436042786;
    }
    mode = D_80114B14_stardust_battle;
    if (mode == 1 && func_8010929C_stardust_battle() == mode && boss->unk02 >= gap) {
        if (gap != 16) {
            func_8010A04C_stardust_battle(boss->unk5C, boss->unk60, 43.75f, 7.5000005f, 0.125f, 50.0f);
            boss->unk02 = 0;
        } else {
            func_8010A204_stardust_battle(boss->unk5C, boss->unk60, 43.75f, 7.5000005f, 0.125f, 50.0f);
            boss->unk02 = 0;
        }
    }
    if (func_8010929C_stardust_battle() != 1 && obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z < 275625.0) {
        k = 1.0 - obj->trans.y * 0.001;
        if (k < 0.2f) {
            k = 0.2f;
        }
        func_8001C258_main(obj->model[1], 4, 0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
        Hu3DModelScaleSet(obj->model[1], k * 1.5f, 1.0f, k * 1.5f);
    } else {
        func_8001C258_main(obj->model[1], 4, 4);
    }
    if (func_8010929C_stardust_battle() == 2) {
        func_8001C258_main(obj->model[2], 4, 0);
        Hu3DModelPosSet(obj->model[2], obj->trans.x, -obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[2], obj->rot.x, obj->rot.y, obj->rot.z);
        HmfModelData[obj->model[2]].unk02 = HmfModelData[obj->model[0]].unk02;
        HmfModelData[obj->model[2]].unk40 = HmfModelData[obj->model[0]].unk40;
    } else {
        func_8001C258_main(obj->model[2], 4, 4);
    }
    boss->unk00++;
    boss->unk02++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010AAC4_stardust_battle);
#endif

void func_8010BFE4_stardust_battle(f32 y, s16 frames) {
    SbBoss *boss;

    if (D_80114B18_stardust_battle != NULL) {
        boss = func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        if (frames > 0) {
            boss->unk24 = frames;
            boss->unk2C = (y - D_80114B18_stardust_battle->trans.y) / frames;
        }
    }
}

void func_8010C06C_stardust_battle(void) {
    SbBoss *boss;

    if (D_80114B18_stardust_battle != NULL) {
        boss = func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        boss->unk2C = 0.0f;
        boss->unk24 = 0;
        if (boss->unk04 != 7) {
            boss->unk28 = boss->unk30 = 0.0f;
            boss->unk04 = 11;
        }
    }
}

void func_8010C0C8_stardust_battle(void) {
    SbBoss *boss;
    f32 dx;
    f32 dy;
    f32 dz;

    if (D_80114B18_stardust_battle != NULL) {
        boss = func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        boss->unk40.x = D_80114B18_stardust_battle->trans.x;
        boss->unk40.y = D_80114B18_stardust_battle->trans.y;
        boss->unk40.z = D_80114B18_stardust_battle->trans.z;
        boss->unk34.x = Center.x;
        boss->unk34.y = 450.0f;
        boss->unk34.z = Center.z + 200.0;
        dx = boss->unk34.x - boss->unk40.x;
        dy = boss->unk34.y - boss->unk40.y;
        dz = boss->unk34.z - boss->unk40.z;
        boss->unk26 = sqrtf(dx * dx + dy * dy + dz * dz) / 15.0000005960464478;
        if (boss->unk26 == 0) {
            boss->unk26 = 1;
        }
        boss->unk24 = 0;
        boss->unk00 = 0;
        boss->unk04 = 13;
    }
}

void func_8010C1F8_stardust_battle(s16 motion, s16 start, s16 end, u8 flags) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &HmfModelData[obj->model[0]];
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        model->unk40 = start;
        model->unk48 = end;
        model->unk03 = flags;
    }
}

void func_8010C2CC_stardust_battle(f32 v) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &HmfModelData[obj->model[0]];
        model->unk44 = v;
    }
}

f32 func_8010C32C_stardust_battle(void) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj == NULL) {
        return 0.0f;
    }
    func_80111FEC_stardust_battle(obj);
    model = &HmfModelData[obj->model[0]];
    return model->unk44;
}

void func_8010C38C_stardust_battle(f32 v) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &HmfModelData[obj->model[0]];
        model->unk40 = v;
    }
}

f32 func_8010C3EC_stardust_battle(void) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj == NULL) {
        return 0.0f;
    }
    func_80111FEC_stardust_battle(obj);
    model = &HmfModelData[obj->model[0]];
    return model->unk40;
}

void func_8010C44C_stardust_battle(void) {
    SbBoss *boss;

    if (D_80114B18_stardust_battle != NULL) {
        boss = func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        boss->unk00 = 0;
        boss->unk04 = 15;
        func_8010C1F8_stardust_battle(1, 0, 0, 2);
    }
}

void func_8010C498_stardust_battle(void) {
    SbBoss *boss;

    if (D_80114B18_stardust_battle != NULL) {
        boss = func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        boss->unk18 = 0.0f;
        boss->unk00 = 0;
        boss->unk04 = 17;
        HuAudFXPlay(0x50B);
        boss->unk4C.x = D_80114B18_stardust_battle->trans.x;
        boss->unk4C.y = D_80114B18_stardust_battle->trans.y;
        boss->unk4C.z = D_80114B18_stardust_battle->trans.z;
    }
}

s16 func_8010C508_stardust_battle(void) {
    omObjData *obj = D_80114B18_stardust_battle;

    if (obj != NULL) {
        return ((SbBoss *)func_80111FEC_stardust_battle(obj))->unk04;
    }
    return 0;
}

void func_8010C538_stardust_battle(void) {
    SbShots *sh;

    D_80114B20_stardust_battle = sh = HuMemAllocTag(sizeof(SbShots), 31000);
    sh->unk08 = HuMemAllocTag(sizeof(SbShot) * 32, 31000);
    memset(sh->unk08, 0, sizeof(SbShot) * 32);
    sh->unk00 = 0;
    sh->unk02 = 32;
    sh->unk04 = 0;
    func_8010C5A8_stardust_battle(32, 0);
}

void func_8010C5A8_stardust_battle(s32 n, s32 m) {
    f32 angle[32];
    f32 dist[32];
    s32 order[32];
    SbShots *sh = D_80114B20_stardust_battle;
    SbShot *shot = sh->unk08;
    s32 i;
    s32 j;
    s32 a;
    s32 b;
    f32 ft;
    s32 it;

    memset(shot, 0, sizeof(SbShot) * 32);
    sh->unk00 = n;
    sh->unk04 = m;
    if (sh->unk00 == 0) {
        return;
    }
    for (i = 0; i < sh->unk00; i++) {
        angle[i] = 360.0f / sh->unk00 * i;
    }
    for (i = 0; i < sh->unk00 * 8; i++) {
        a = rand8() % sh->unk00;
        b = rand8() % sh->unk00;
        if (a != b) {
            ft = angle[b];
            angle[b] = angle[a];
            angle[a] = ft;
        }
    }
    for (i = 0; i < sh->unk00; i++) {
        dist[i] = 525.0 / sh->unk00 * i;
    }
    for (i = 0; i < sh->unk00 * 8; i++) {
        a = rand8() % sh->unk00;
        b = rand8() % sh->unk00;
        if (a != b) {
            ft = dist[b];
            dist[b] = dist[a];
            dist[a] = ft;
        }
    }
    for (i = 0; i < sh->unk00; i++) {
        order[i] = i;
    }
    for (i = 0; i < sh->unk00 * 8; i++) {
        a = rand8() % sh->unk00;
        b = rand8() % sh->unk00;
        if (a != b) {
            it = order[b];
            order[b] = order[a];
            order[a] = it;
        }
    }
    for (i = 0; i < 32; i++, shot++) {
        if (i >= sh->unk00) {
            shot->unk00 = 0;
        } else {
            for (j = 0; j < sh->unk04; j++) {
                if (i == order[j]) {
                    shot->unk02 = 1;
                    j = sh->unk04;
                }
            }
            shot->unk00 = 1;
            shot->x = sindf(angle[i]) * dist[i];
            shot->z = cosdf(angle[i]) * dist[i];
            shot->y = 0.0f;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CA48_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CB34_stardust_battle);

extern RGBA D_80113EC4_stardust_battle[];
void func_8001CAA4_main(s16 arg0, s16 arg1, f32 arg2);

/* NON_MATCHING: loop-invariant hoisting only: retail keeps 100.0 (the random-step scale) in s6/s7 and reloads 0.01 from the pool at each use; mine keeps 0.01 in s6/s7 and reloads 100.0 */
#ifdef NON_MATCHING
void func_8010CE5C_stardust_battle(void) {
    SbItems *items = D_80114B2C_stardust_battle;
    SbItem *item = items->unk0C;
    s32 stage = func_8010929C_stardust_battle();
    f32 floor;
    s32 i;
    s32 done;
    f32 s;
    Vec pos;
    Vec scale;

    floor = (stage == 1) ? 25.0f : 0.0f;
    for (i = 0; i < items->unk08; i++, item++) {
        if (item->unk00 == 0) {
            continue;
        }
        if (func_80049F98_main() + D_800D6A90_main != 0) {
            if (item->unk18 != 0) {
                func_8001CAA4_main(item->unk0C, items->unk06, item->unk68);
            }
            if (item->unk16 == 3) {
                func_8001C258_main(item->unk02[item->unk10], 4, 0);
            }
            continue;
        }
        item->unk1C.x = item->unk28.x;
        item->unk1C.y = item->unk28.y;
        item->unk1C.z = item->unk28.z;
        done = 0;
        switch (item->unk16) {
        case 0:
            item->unk28.x += item->unk40.x;
            item->unk28.y += item->unk40.y;
            item->unk28.z += item->unk40.z;
            s = sindf((item->unk14 & 7) * 51.42857f) * 0.2f;
            Hu3DModelScaleSet(item->unk0C, s + 0.75f, s + 0.75f, s + 0.75f);
            if (item->unk28.y <= floor) {
                s = fabsf((floor - item->unk28.y) / item->unk40.y);
                item->unk28.x -= s * item->unk40.x;
                item->unk28.z -= s * item->unk40.z;
                item->unk28.y = floor;
                pos.x = item->unk28.x;
                pos.y = item->unk28.y;
                pos.z = item->unk28.z + 50.0;
                scale.x = scale.y = scale.z = 1.2f;
                func_8010F890_stardust_battle(&pos, NULL, &scale, 1.0f, &D_80113EC4_stardust_battle[stage]);
                HuAudFXPlay(0x504);
                item->unk16 = 2;
                item->unk14 = 0;
            }
            break;
        case 1:
            s = sindf((item->unk14 & 7) * 51.42857f) * 0.2f;
            Hu3DModelScaleSet(item->unk0C, s + 1.0f, s + 1.0f, s + 1.0f);
            if (item->unk68 < 1.0f) {
                item->unk68 += 0.2f;
            }
            if (item->unk12 & 1) {
                item->unk28.x -= fabs(item->unk28.y - 0.0f);
                item->unk28.y = floor;
                if (item->unk12 < 2) {
                    item->unk16 = 2;
                    item->unk14 = 0;
                }
            } else {
                item->unk28.x += ((f32)(u8)(rand8() % 100) * 0.01 * 0.025f + 0.025f) * 100.0;
                item->unk28.y = floor + ((f32)(u8)(rand8() % 100) * 0.01 * 0.025f + 0.025f) * 100.0;
            }
            item->unk12--;
            break;
        case 2:
            if (item->unk14 >= 30) {
                func_8001C258_main(item->unk02[1], 4, 0);
                item->unk10 = 1;
                item->unk18 = 0;
                item->unk16 = 3;
                item->unk14 = 0;
                break;
            }
            s = 1.0f - item->unk14 * 0.033333335f;
            if (s < 0.0f) {
                s = 0.5f;
            } else {
                s = s * 0.5f + 0.5f;
            }
            s += sindf((item->unk14 & 7) * 51.42857f) * 0.2f;
            Hu3DModelScaleSet(item->unk0C, s, s, s);
            if (item->unk68 < 1.0f) {
                item->unk68 += 0.2f;
            }
            if (item->unk14 >= 15.0f) {
                if (item->unk14 & 1) {
                    func_8001C258_main(item->unk02[0], 4, 0);
                    item->unk10 = 0;
                } else {
                    func_8001C258_main(item->unk02[1], 4, 0);
                    item->unk10 = 1;
                }
            }
            break;
        case 3:
            if (item->unk14 >= 60.0f) {
                if (item->unk14 & 1) {
                    func_8001C258_main(item->unk02[item->unk10], 4, 4);
                } else {
                    func_8001C258_main(item->unk02[item->unk10], 4, 0);
                }
                if (item->unk14 >= 90.0f) {
                    func_8010DF70_stardust_battle(i);
                    done = 1;
                }
            }
            break;
        case 5:
            item->unk40.y -= 2.44995f;
            item->unk28.x += item->unk40.x;
            item->unk28.y += item->unk40.y;
            item->unk28.z += item->unk40.z;
            if ((item->unk28.y < floor && item->unk28.x * item->unk28.x + item->unk28.z * item->unk28.z < 330625.0)
                || (item->unk1C.x * item->unk1C.x + item->unk1C.z * item->unk1C.z < 330625.0
                    && item->unk28.x * item->unk28.x + item->unk28.z * item->unk28.z > 330625.0
                    && item->unk1C.y < 50.0 && item->unk28.y < 50.0)) {
                pos.x = item->unk28.x;
                pos.z = item->unk28.z;
                pos.y = 30.000002f;
                func_8010FCBC_stardust_battle(&pos, NULL, 1.0f, 1);
                func_8010FCBC_stardust_battle(&pos, NULL, 1.0f, 2);
                func_8010DF70_stardust_battle(i);
                done = 1;
            }
            break;
        }
        if (done == 0) {
            func_8001C258_main(item->unk02[(s16)(item->unk10 ^ 1)], 4, 4);
            func_8001C258_main(item->unk06[(s16)(item->unk10 ^ 1)], 4, 4);
            Hu3DModelPosSet(item->unk02[item->unk10], item->unk28.x, item->unk28.y, item->unk28.z);
            Hu3DModelRotSet(item->unk02[item->unk10], item->unk34.x, item->unk34.y, item->unk34.z);
            if (stage != 2 || item->unk28.y <= -50.0
                || item->unk28.x * item->unk28.x + item->unk28.z * item->unk28.z > 275625.0) {
                func_8001C258_main(item->unk06[item->unk10], 4, 4);
            } else {
                func_8001C258_main(item->unk06[item->unk10], 4, 0);
                Hu3DModelPosSet(item->unk06[item->unk10], item->unk28.x, -item->unk28.y, item->unk28.z);
                Hu3DModelRotSet(item->unk06[item->unk10], item->unk34.x, item->unk34.y, item->unk34.z);
            }
            if (item->unk18 != 0) {
                func_8001C258_main(item->unk0C, 4, 0);
                Hu3DModelPosSet(item->unk0C, item->unk28.x, item->unk28.y + 34.9999994039535522, item->unk28.z);
                item->unk78 += 20.0f;
                if (item->unk78 >= 360.0f) {
                    item->unk74 -= 360.0f;
                }
                Hu3DModelRotSet(item->unk0C, item->unk70 + 180.0f, item->unk74, 0.0f);
                func_8008A070_main((f32(*)[4])HmfModelData[item->unk0C].mtx);
                func_80017D24_main((f32(*)[4])HmfModelData[item->unk0C].mtx, 0.0f, item->unk78, 0.0f);
                if (item->unk68 > 1.0f) {
                    item->unk68 = 1.0f;
                } else if (item->unk68 < 0.0f) {
                    item->unk68 = 0.0f;
                }
                if (item->unk68 != item->unk6C) {
                    func_8001CAA4_main(item->unk0C, items->unk06, item->unk68);
                }
                item->unk6C = item->unk68;
            } else {
                func_8001C258_main(item->unk0C, 4, 4);
            }
            if (stage != 1 && item->unk28.x * item->unk28.x + item->unk28.z * item->unk28.z < 275625.0) {
                s = 1.0 - item->unk28.y * 0.001;
                if (s < 0.2f) {
                    s = 0.2f;
                }
                func_8001C258_main(item->unk0A, 4, 0);
                Hu3DModelPosSet(item->unk0A, item->unk28.x, 0.0f, item->unk28.z);
                Hu3DModelScaleSet(item->unk0A, s * 0.8f, 1.0f, s * 0.8f);
            } else {
                func_8001C258_main(item->unk0A, 4, 4);
            }
            if (item->unk28.y < -1000.0) {
                func_8010DF70_stardust_battle(i);
            }
            item->unk14++;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CE5C_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114528_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_8011452C_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114530_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", jtbl_80114538_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114550_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114558_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114560_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114568_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114570_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114578_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114580_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114588_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114590_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114598_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_801145A0_stardust_battle);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010DADC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010DE64_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010DF70_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E03C_stardust_battle);

SbItem *func_8010E300_stardust_battle(s16 idx) {
    SbItems *items = D_80114B2C_stardust_battle;
    SbItem *item;

    if (idx >= items->unk08) {
        return NULL;
    }
    item = &items->unk0C[idx];
    return (item->unk00 != 0) ? item : NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E35C_stardust_battle);

void func_8010E46C_stardust_battle(s16 idx, f32 x, f32 y, f32 z) {
    SbItem *item;

    if (idx < D_80114B2C_stardust_battle->unk08) {
        item = &D_80114B2C_stardust_battle->unk0C[idx];
        if (item->unk00 != 0) {
            item->unk28.x = x;
            item->unk28.y = y;
            item->unk28.z = z;
        }
    }
}

void func_8010E4C8_stardust_battle(s16 idx, f32 x, f32 y, f32 z) {
    SbItem *item;

    if (idx < D_80114B2C_stardust_battle->unk08) {
        item = &D_80114B2C_stardust_battle->unk0C[idx];
        if (item->unk00 != 0) {
            item->unk34.x = x;
            item->unk34.y = y;
            item->unk34.z = z;
        }
    }
}

s16 func_8010E524_stardust_battle(omObjData *obj, s16 mode, Vec *dir) {
    Vec pos;
    Vec rot;
    Vec vel;
    SbItems *items;
    SbItem *item;
    MgWork *work;
    s32 i;
    f32 r;
    f32 h;
    f32 rr;
    f32 d;
    f32 dx;
    f32 dy;
    f32 dz;

    if (D_80114B2C_stardust_battle == NULL || D_80114B18_stardust_battle == NULL) {
        return -1;
    }
    items = D_80114B2C_stardust_battle;
    item = items->unk0C;
    work = obj->data;
    if (mode == 0) {
        r = (work->unk48 + 50.0) * 0.7f;
        h = work->unk34;
    } else {
        r = 135.0f;
        h = 150.0f;
    }
    rr = r * r;
    for (i = 0; i < items->unk08; i++, item++) {
        if (item->unk00 == 0) {
            continue;
        }
        if (mode == 0) {
            if (item->unk16 == 3) {
                continue;
            }
            if (item->unk18 == 0) {
                continue;
            }
            dy = item->unk28.y - obj->trans.y;
        } else {
            if (item->unk18 != 0) {
                continue;
            }
            if (item->unk16 != 5) {
                continue;
            }
            dy = item->unk28.y + 34.9999994039535522 - obj->trans.y;
        }
        dx = item->unk28.x - obj->trans.x;
        dz = item->unk28.z - obj->trans.z;
        if (fabs(dx) > r) {
            continue;
        }
        if (fabs(dz) > r) {
            continue;
        }
        d = dx * dx + dz * dz;
        if (!(d < rr)) {
            continue;
        }
        if ((dy > -50.0) & (dy < h)) {
        if (mode == 0) {
            pos.x = (item->unk28.x + obj->trans.x) * 0.5f;
            pos.z = (item->unk28.z + obj->trans.z) * 0.5f;
            pos.y = (item->unk28.y + 50.0 + obj->trans.y + 100.0) * 0.5;
            func_8010FCBC_stardust_battle(&pos, NULL, 1.2f, 2);
            HuAudFXPlay(0x505);
        } else {
            pos.x = item->unk28.x;
            pos.y = item->unk28.y;
            pos.z = item->unk28.z;
            vel.x = item->unk40.x;
            vel.y = item->unk40.y;
            vel.z = item->unk40.z;
            func_80111F38_stardust_battle(&vel, &rot.x);
            rot.x -= 90.0f;
            func_8010FCBC_stardust_battle(&pos, &rot, 1.0f, 0);
            dir->x = item->unk40.x;
            dir->y = item->unk40.y;
            dir->z = item->unk40.z;
            HuAudFXPlay(0x506);
            func_8010DF70_stardust_battle(i);
        }
        return i;
        }
    }
    if (mode == 0) {
        dx = D_80114B18_stardust_battle->trans.x - obj->trans.x;
        dz = D_80114B18_stardust_battle->trans.z - obj->trans.z;
        dy = D_80114B18_stardust_battle->trans.y + 34.9999994039535522 - obj->trans.y;
        r = (work->unk48 + 85.000002384185791) * 0.7f;
        d = dx * dx + dz * dz;
        rr = r * r;
        if (d < rr && ((dy > -150.0) & (dy < h))) {
            pos.x = (D_80114B18_stardust_battle->trans.x + obj->trans.x) * 0.5f;
            pos.z = (D_80114B18_stardust_battle->trans.z + obj->trans.z) * 0.5f;
            pos.y = (D_80114B18_stardust_battle->trans.y + 100.0 + obj->trans.y + 100.0) * 0.5;
            rot.x = 90.0f;
            rot.y = atan2df(dx, dz);
            rot.z = 0.0f;
            func_8010FCBC_stardust_battle(&pos, &rot, 1.0f, 1);
            return 0xFF;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010EA04_stardust_battle);

/* NON_MATCHING: register allocation only: retail loads D_80114B2C into v0 and copies it to s2 in the delay slot */
#ifdef NON_MATCHING
void func_8010ED7C_stardust_battle(void) {
    SbItems *items;
    SbItem *item;
    s32 i;

    if ((items = D_80114B2C_stardust_battle) != NULL) {
        item = items->unk0C;
        for (i = 0; i < items->unk08; i++, item++) {
            if (item->unk00 != 0) {
                Hu3DModelScaleSet(func_8000D550_main(D_80114B54_stardust_battle, item->unk28.x, item->unk28.y, item->unk28.z), 2.0f, 2.0f, 2.0f);
                func_8010DF70_stardust_battle(i);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010ED7C_stardust_battle);
#endif

u16 func_8010EE38_stardust_battle(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 id = func_80055810_main(data);

    DataClose(data);
    return id;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010EE7C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F0E8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F400_stardust_battle);

void func_8010F580_stardust_battle(s16 idx) {
    D_80114B44_stardust_battle[idx].unk04 = 1;
    D_80114B44_stardust_battle[idx].unk06 = 0;
}

void func_8010F5B0_stardust_battle(s16 idx) {
    D_80114B44_stardust_battle[idx].unk04 = 2;
    D_80114B44_stardust_battle[idx].unk06 = 0;
}

void func_8010F5E0_stardust_battle(void) {
    HuSprite_Unk84_Struct *spr;
    SbEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_80114B30_stardust_battle[1] = func_8010EE38_stardust_battle(0xB));
    D_80114B48_stardust_battle = omAddObj(0x1E, 0, 0, -1, func_8010F73C_stardust_battle);
    D_80114B4C_stardust_battle = effect = HuMemAllocTag(sizeof(SbEffect) * 4, 0x7918);
    for (i = 0; i < 4; i++, effect++) {
        if (i == 0) {
            effect->model = func_80112980_stardust_battle(spr, &D_80113CF4_stardust_battle);
        } else {
            effect->model = func_80113568_stardust_battle(spr, D_80114B4C_stardust_battle->model, &D_80113CF4_stardust_battle);
        }
        effect->active = 0;
        *(u32 *)&effect->color = *(u32 *)&D_80113CF4_stardust_battle;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &HmfModelData[effect->model];
        model->unk40 = 0.0f;
    }
}

void func_8010F73C_stardust_battle(omObjData *obj) {
    HuSprite_Unk84_Struct *spr;
    SbEffect *effect;
    HmfModel *model;
    s32 i;

    i = 0;
    spr = func_80055194_main(D_80114B30_stardust_battle[1]);
    effect = D_80114B4C_stardust_battle;
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
                func_8011376C_stardust_battle(effect->model, spr, (s32)effect->frame, &effect->color);
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
    } while (i < 4);
}

s32 func_8010F890_stardust_battle(Vec *pos, Vec *vel, Vec *scale, f32 speed, RGBA *color) {
    HuSprite_Unk84_Struct *spr;
    SbEffect *effect;
    HmfModel *model;
    s32 i;

    spr = func_80055194_main(D_80114B30_stardust_battle[1]);
    for (i = 0, effect = D_80114B4C_stardust_battle; i < 4; i++, effect++) {
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
            func_8011376C_stardust_battle(effect->model, spr, 0, &effect->color);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FA60_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FBCC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FCBC_stardust_battle);

void func_80110364_stardust_battle(omObjData *obj);
s32 func_801122D0_stardust_battle(void);

void func_8010FE74_stardust_battle(void) {
    f32 angles[16];
    SbStar *star;
    omObjData *obj;
    s32 i;
    s32 a;
    s32 b;
    f32 tmp;
    s16 grp;

    star = D_80114B5C_stardust_battle = HuMemAllocTag(sizeof(SbStar) * 16, 31000);
    obj = D_80114B58_stardust_battle = omAddObj(30, 1, 0, -1, func_80110364_stardust_battle);
    for (i = 0; i < 16; i++) {
        angles[i] = i * 22.5f;
    }
    for (i = 0; i < 512; i++) {
        a = rand8() & 0xF;
        b = rand8() & 0xF;
        if (a != b) {
            tmp = angles[a];
            angles[a] = angles[b];
            angles[b] = tmp;
        }
    }
    for (i = 0; i < 16; i++, star++) {
        star->unk02 = func_801122D0_stardust_battle();
        func_8001C258_main(star->unk02, 4, 4);
        Hu3DModelScaleSet(star->unk02, (f32)(u8)(rand8() % 100) * 0.01 * 1.5 + 1.0 - 0.5, 1.0f, 1.0f);
        star->unk04 = (u8)(rand8() % 180);
        star->unk06 = (u8)(rand8() % 180);
        star->unk00 = 0;
        star->unk14 = 20.0f;
        star->unk18 = 20.0f;
        star->unk08 = (f32)(u8)(rand8() % 100) * 0.01 * 40.0 - 20.0;
        star->unk0C = (f32)(u8)(rand8() % 100) * 0.01 * 90.0 - 45.0;
        star->unk10 = angles[i] + ((f32)(u8)(rand8() % 100) * 0.01 * 10.0 - 5.0);
        star->unk1C = star->unk20 = star->unk24 = 0.0f;
    }
    obj->model[0] = func_8000B0A0_main(0x620009, 0x1839);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->scale.x = obj->scale.y = obj->scale.z = 10.0f;
    D_80114B30_stardust_battle[2] = func_8010EE38_stardust_battle(0x62000B);
    grp = HuSprGrpCreate(1, 0);
    obj->work[3] = grp;
    func_80055024_main(grp, 0, D_80114B30_stardust_battle[2], 0);
    func_800550F4_main(grp, 0, 0);
    func_80054FF8_main(grp, 0, 0);
    func_80054904_main(grp, 0, 160, 120);
    HuSprScaleSet(grp, 0, 4.0f, 4.0f);
    func_80055484_main(grp, 0, 0xFF, 0xFF, 0xFF, 0);
    HuSprAttrSet(grp, 0, 0x20009800);
    HuSprPriSet(grp, 0, 0xFFFF);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80110364_stardust_battle);

void func_80110758_stardust_battle(f32 x, f32 y, f32 z, s32 n) {
    if (D_80114B58_stardust_battle != NULL) {
        D_80114B58_stardust_battle->trans.x = x;
        D_80114B58_stardust_battle->trans.y = y;
        D_80114B58_stardust_battle->trans.z = z;
    }
}

void func_80110780_stardust_battle(s16 n) {
    SbStar *star = D_80114B5C_stardust_battle;
    s32 i;

    if (star != NULL) {
        for (i = 0; i < 16; i++, star++) {
            if (i < n) {
                star->unk00 = 1;
            } else {
                star->unk00 = 0;
            }
        }
    }
}

void func_801107C4_stardust_battle(s16 n) {
    if (D_80114B58_stardust_battle != NULL) {
        D_80114B58_stardust_battle->work[0] = 1;
        D_80114B58_stardust_battle->work[1] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801107E4_stardust_battle);

void func_80110914_stardust_battle(void) {
    SbCamera c = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed = 1.0f;

    switch (D_80113F08_stardust_battle) {
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
                func_801117E4_stardust_battle(c.center.x, c.center.y, c.center.z, c.rot.x, c.rot.y, c.rot.z, c.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 104, D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & 0x100) || (D_800CDA7C_main[0] & 1)) {
                D_80113F0C_stardust_battle++;
            }
            if (D_800CDA7C_main[0] & 0x202) {
                D_80113F0C_stardust_battle--;
            }
            if (D_800CDA7C_main[0] & 0x404) {
                D_80113F10_stardust_battle++;
            }
            if (D_800CDA7C_main[0] & 0x808) {
                D_80113F10_stardust_battle--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((u16)D_80113F0C_stardust_battle + 20, (u16)D_80113F10_stardust_battle + 104, D_800D5218_main);
            break;
        case 3:
            D_80113F08_stardust_battle = 0;
            break;
    }
    if (D_800D5558_main[0] & 0x10) {
        if (D_80113F08_stardust_battle == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_80113F08_stardust_battle++ >= 4) {
            D_80113F08_stardust_battle = 0;
        }
    }
}

extern f32 D_80113F14_stardust_battle[]; /* case-3 ease-in steps */

/* NON_MATCHING: register allocation only (masked 0): in case 4 retail forms sin * t in f0 and takes abs.s into f20, mine multiplies into f20 */
#ifdef NON_MATCHING
void func_80111004_stardust_battle(void) {
    f32 t = 0.0f;
    f32 s;

    if (D_80114BAC_stardust_battle <= 0) {
        func_801119D4_stardust_battle(0);
        D_80114BB0_stardust_battle = 0;
        return;
    }
    if (D_80114BA8_stardust_battle == 0) {
        Center.x = D_80114B60_stardust_battle[0].center.x;
        Center.y = D_80114B60_stardust_battle[0].center.y;
        Center.z = D_80114B60_stardust_battle[0].center.z;
        CRot.x = D_80114B60_stardust_battle[0].rot.x;
        CRot.y = D_80114B60_stardust_battle[0].rot.y;
        CRot.z = D_80114B60_stardust_battle[0].rot.z;
        CZoom = D_80114B60_stardust_battle[0].zoom;
        SB_WRAP(CRot.x);
        SB_WRAP(CRot.y);
        SB_WRAP(CRot.z);
        D_80114BAC_stardust_battle = 0;
    } else {
        switch (D_80114BB4_stardust_battle) {
        case 0:
            t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
            break;
        case 1:
            t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
            t = sindf(t * 90.0f);
            break;
        case 2:
            t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
            t = sindf(t * 90.0f);
            t = t * t;
            break;
        case 3:
            if (D_80114BA8_stardust_battle > 5) {
                t = (f32)(D_80114BA8_stardust_battle - 5) / (f32)(D_80114BAC_stardust_battle - 5);
                t = sindf(t * 90.0f);
                t = t * t;
            } else {
                t = D_80113F14_stardust_battle[5 - D_80114BA8_stardust_battle];
            }
            break;
        case 4:
            t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
            s = sindf(t * 90.0f);
            t = fabsf(sindf(s * 450.0f) * t);
            break;
        case 5:
            t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
            s = sindf(t * 90.0f);
            t = s + sindf(t * 720.0f) * 0.2f;
            break;
        }
        Center.x = func_80111DF8_stardust_battle(t, D_80114B60_stardust_battle[0].center.x, D_80114B60_stardust_battle[1].center.x);
        Center.y = func_80111DF8_stardust_battle(t, D_80114B60_stardust_battle[0].center.y, D_80114B60_stardust_battle[1].center.y);
        Center.z = func_80111DF8_stardust_battle(t, D_80114B60_stardust_battle[0].center.z, D_80114B60_stardust_battle[1].center.z);
        CRot.x = func_80111E10_stardust_battle(t, D_80114B60_stardust_battle[0].rot.x, D_80114B60_stardust_battle[1].rot.x);
        CRot.y = func_80111E10_stardust_battle(t, D_80114B60_stardust_battle[0].rot.y, D_80114B60_stardust_battle[1].rot.y);
        CRot.z = func_80111E10_stardust_battle(t, D_80114B60_stardust_battle[0].rot.z, D_80114B60_stardust_battle[1].rot.z);
        CZoom = func_80111DF8_stardust_battle(t, D_80114B60_stardust_battle[0].zoom, D_80114B60_stardust_battle[1].zoom);
        SB_WRAP(CRot.x);
        SB_WRAP(CRot.y);
        SB_WRAP(CRot.z);
        if (D_80114BA8_stardust_battle > 0) {
            D_80114BA8_stardust_battle--;
        } else {
            D_80114BA8_stardust_battle++;
        }
    }
    D_80114BB0_stardust_battle = 1;
    func_801119D4_stardust_battle(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111004_stardust_battle);
#endif

void func_801115F8_stardust_battle(s32 idx) {
    SB_WRAP(CRot.x);
    SB_WRAP(CRot.y);
    SB_WRAP(CRot.z);
    D_80114B60_stardust_battle[idx].center.x = Center.x;
    D_80114B60_stardust_battle[idx].center.y = Center.y;
    D_80114B60_stardust_battle[idx].center.z = Center.z;
    D_80114B60_stardust_battle[idx].rot.x = CRot.x;
    D_80114B60_stardust_battle[idx].rot.y = CRot.y;
    D_80114B60_stardust_battle[idx].rot.z = CRot.z;
    D_80114B60_stardust_battle[idx].zoom = CZoom;
    D_80114B60_stardust_battle[idx].unk1C = D_80114B60_stardust_battle[idx].unk20 = 0.0f;
}

void func_801117E4_stardust_battle(f32 cx, f32 cy, f32 cz, f32 rx, f32 ry, f32 rz, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_80114BA8_stardust_battle = frames - 1;
        D_80114BAC_stardust_battle = frames;
        if (cx != 65535.0f) {
            D_80114B60_stardust_battle[0].center.x = cx;
        } else {
            D_80114B60_stardust_battle[0].center.x = Center.x;
        }
        if (cy != 65535.0f) {
            D_80114B60_stardust_battle[0].center.y = cy;
        } else {
            D_80114B60_stardust_battle[0].center.y = Center.y;
        }
        if (cz != 65535.0f) {
            D_80114B60_stardust_battle[0].center.z = cz;
        } else {
            D_80114B60_stardust_battle[0].center.z = Center.z;
        }
        if (rx != 65535.0f) {
            D_80114B60_stardust_battle[0].rot.x = rx;
        } else {
            D_80114B60_stardust_battle[0].rot.x = CRot.x;
        }
        if (ry != 65535.0f) {
            D_80114B60_stardust_battle[0].rot.y = ry;
        } else {
            D_80114B60_stardust_battle[0].rot.y = CRot.y;
        }
        if (rz != 65535.0f) {
            D_80114B60_stardust_battle[0].rot.z = rz;
        } else {
            D_80114B60_stardust_battle[0].rot.z = CRot.z;
        }
        if (zoom != 65535.0f) {
            D_80114B60_stardust_battle[0].zoom = zoom;
        } else {
            D_80114B60_stardust_battle[0].zoom = CZoom;
        }
        func_801115F8_stardust_battle(1);
    }
}

void func_801119D4_stardust_battle(s32 idx) {
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

f32 func_80111B28_stardust_battle(f32 a, f32 b) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111C2C_stardust_battle);

f32 func_80111DF8_stardust_battle(f32 t, f32 a, f32 b) {
    return a + t * (b - a);
}

f32 func_80111E10_stardust_battle(f32 t, f32 a, f32 b) {
    return func_80111C2C_stardust_battle(b, a, fabsf(func_80111B28_stardust_battle(b, a) * t));
}

void func_80111E70_stardust_battle(f32 *a, f32 *b, f32 *out, f32 t) {
    s32 i;

    for (i = 0; i < 16; i++) {
        out[i] = a[i] + t * (b[i] - a[i]);
    }
}

f32 func_80111EB8_stardust_battle(f32 x, f32 z) {
    f32 a = atan2df(z, x);

    if (a < 0.0) {
        a += 360.0;
    } else if (a >= 360.0) {
        a -= 360.0;
    }
    return a;
}

void func_80111F38_stardust_battle(Vec* dir, f32* angles) {
    f32 h = sqrtf(dir->x * dir->x + dir->z * dir->z);

    *angles++ = func_80111EB8_stardust_battle(h, -dir->y);
    *angles++ = func_80111EB8_stardust_battle(dir->z, dir->x);
    *angles = 0.0f;
}

void func_80111FC0_stardust_battle(omObjData *obj, u32 value) {
    obj->work[0] = value >> 24;
    obj->work[1] = (value >> 16) & 0xFF;
    obj->work[2] = (value >> 8) & 0xFF;
    obj->work[3] = value & 0xFF;
}

void *func_80111FEC_stardust_battle(omObjData *obj) {
    SbPack u;

    u.b.a = obj->work[0];
    u.b.b = obj->work[1];
    u.b.c = obj->work[2];
    u.b.d = obj->work[3];
    return u.p;
}

void func_80112040_stardust_battle(s16 mdl, const char *part, Matrix4f *out) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80112220_stardust_battle);

/* HmfData::unk3C as this unit fills it: hmfman.h's HmfModelData_Unk64_Unk3C_Struct plus a third list at 0x18 */
typedef struct SbHmfDl {
    /* 0x00 */ Gfx *unk00[4];
    /* 0x10 */ Gfx *unk10;
    /* 0x14 */ Gfx *unk14;
    /* 0x18 */ Gfx *unk18;
} SbHmfDl; // Size 0x1C

extern Vtx_t D_80114060_stardust_battle[10];
void func_801127B8_stardust_battle(s16 mdl, s16 n, s16 buf);

s32 func_801122D0_stardust_battle(void) {
    HmfData *hmf;
    Gfx *buf;
    Gfx *gfx;
    Vtx_t *v;
    Vtx_t *src;
    s32 size;
    s32 idx;
    s32 i;
    s32 j;

    buf = gfx = HuMemAlloc(0x10000);
    idx = func_8001A894_main(0x1CC1, buf, 4);
    hmf = HmfModelData[idx].hmf;
    hmf->unk60->unk50 |= 0x01010000;
    HuMemFree(hmf->unk3C);
    hmf->unk3C = HuMemAllocTag(sizeof(SbHmfDl), D_800CDD6A_main);
    SB_HMF_VTXNUM(hmf) = 10;
    v = hmf->unk40 = HuMemAllocTag(sizeof(Vtx_t) * 10, hmf->unk0E);
    for (j = 0, src = D_80114060_stardust_battle; j < 10; j++, v++, src++) {
        *v = *src;
    }
    gSPDisplayList(gfx++, osVirtualToPhysical(D_80114020_stardust_battle));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, SHADE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - (u8 *)buf;
    ((SbHmfDl *)hmf->unk3C)->unk10 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buf, ((SbHmfDl *)hmf->unk3C)->unk10, size);
    HuMemFree(buf);
    buf = gfx = HuMemAlloc(0x10000);
    gSPVertex(gfx++, 0x01000000, 10, 0);
    gSP1Triangle(gfx++, 0, 1, 2, 0);
    gSP1Triangle(gfx++, 1, 3, 4, 0);
    gSP1Triangle(gfx++, 2, 1, 4, 0);
    gSP1Triangle(gfx++, 2, 4, 5, 0);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - (u8 *)buf;
    ((SbHmfDl *)hmf->unk3C)->unk14 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buf, ((SbHmfDl *)hmf->unk3C)->unk14, size);
    HuMemFree(buf);
    buf = gfx = HuMemAlloc(0x10000);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - (u8 *)buf;
    ((SbHmfDl *)hmf->unk3C)->unk18 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buf, ((SbHmfDl *)hmf->unk3C)->unk18, size);
    HuMemFree(buf);
    for (i = 0; i < D_800D1FF0_main; i++) {
        ((SbHmfDl *)hmf->unk3C)->unk00[i + 1] = HuMemAllocTag(0x100, hmf->unk0E);
        func_801127B8_stardust_battle(idx, 1, i);
    }
    ((SbHmfDl *)hmf->unk3C)->unk00[0] = ((SbHmfDl *)hmf->unk3C)->unk00[D_800D2008_main + 1];
    return idx;
}

void func_801127B8_stardust_battle(s16 mdl, s16 n, s16 buf) {
    HmfData *hmf;
    Gfx *gfx;
    s16 b;
    s16 i;

    if (buf != -1) {
        b = buf;
    } else {
        b = D_800D2008_main;
    }
    hmf = HmfModelData[mdl].hmf;
    gfx = (&((SbHmfDl *)hmf->unk3C)->unk00[1])[b];
    gDPPipeSync(gfx++);
    gSPDisplayList(gfx++, osVirtualToPhysical(((SbHmfDl *)hmf->unk3C)->unk10));
    for (i = 0; i < n; i++) {
        gSPSegment(gfx++, 0x01, osVirtualToPhysical((Vtx_t *)hmf->unk40 + i * 10));
        gSPDisplayList(gfx++, osVirtualToPhysical(((SbHmfDl *)hmf->unk3C)->unk14));
    }
    gSPDisplayList(gfx++, osVirtualToPhysical(((SbHmfDl *)hmf->unk3C)->unk18));
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    ((SbHmfDl *)hmf->unk3C)->unk00[0] = ((SbHmfDl *)hmf->unk3C)->unk00[b + 1];
}

s32 func_80112980_stardust_battle(HuSprite_Unk84_Struct *arg0, RGBA *arg1) {
    HmfData *temp_s4;
    Gfx *temp_v0_0;
    Gfx *temp_v0_2;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_s1;

    temp_v0_0 = temp_v0_2 = HuMemAlloc(0x10000);
    temp_v0 = func_8001A894_main(0x1CC1, temp_v0_0, 4);
    temp_s4 = HmfModelData[temp_v0].hmf;
    temp_s4->unk60->unk50 |= 0x01010000;
    HuMemFree(temp_s4->unk3C);
    temp_s4->unk3C = HuMemAllocTag(0x18, D_800CDD6A_main);
    func_801138A0_stardust_battle(arg0, temp_s4, 1.0f, 0, 0);
    gSPDisplayList(temp_v0_2++, osVirtualToPhysical(D_80114020_stardust_battle));
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

s32 func_80113568_stardust_battle(HuSprite_Unk84_Struct *arg0, u16 arg1, RGBA *arg2) {
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

void func_8011376C_stardust_battle(u16 modelId, HuSprite_Unk84_Struct *arg1, u16 arg2, RGBA *arg3) {
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

s32 func_801138A0_stardust_battle(HuSprite_Unk84_Struct *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
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
