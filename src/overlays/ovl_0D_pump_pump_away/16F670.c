#include "common.h"
#include "overlays/minigame.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "mallocblock.h"

typedef func_800E1BA8_minigame_ObjData MgWork;

/* The vertex count of an HmfData (+0x18, inside its unk16 bytes). */
#define PP_HMF_VTXNUM(h) (*(s16 *)&(h)->unk16[2])

/* A colour as three words (sky gradient key colours, D_80110EB8_pump_pump_away). */
typedef struct PpRgb {
    /* 0x00 */ s32 r;
    /* 0x04 */ s32 g;
    /* 0x08 */ s32 b;
} PpRgb;

typedef struct PpTexSize {
    /* 0x00 */ u16 w;
    /* 0x02 */ u16 h;
} PpTexSize;

/* A team's state (D_80111978_pump_pump_away, 2 x 0x34). */
typedef struct PpTeam {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 phase;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 timer;
    /* 0x18 */ f32 dist;
    /* 0x1C */ f32 lastDist;
    /* 0x20 */ f32 speed;
    /* 0x24 */ s32 state;
    /* 0x28 */ omObjData *obj;
    /* 0x2C */ f32 wobble;
    /* 0x30 */ f32 drift;
} PpTeam; // Size 0x34

/* An entity slot (D_80111A30_pump_pump_away, 50 x 0x84; the layout of Coconut Conk's). */
typedef struct CcEnt {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 grp;
    /* 0x42 */ s16 spr;
    /* 0x44 */ Vec pos;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} CcEnt; // Size 0x84

/* The full-screen picture (D_80113530_pump_pump_away). */
typedef struct PpScreen {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 grp;
    /* 0x08 */ s32 draw;
    /* 0x0C */ HuSprite_Unk84_Struct *spr;
    /* 0x10 */ s32 alpha;
    /* 0x14 */ s32 timer;
} PpScreen;

/* A 2D overlay with up to eight values (D_80111758_pump_pump_away, D_8011178C_pump_pump_away). */
typedef struct PpHud {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 grp;
    /* 0x08 */ s32 draw;
    /* 0x0C */ HuSprite_Unk84_Struct *spr;
    /* 0x10 */ s32 val[8];
    /* 0x30 */ s32 alpha;
} PpHud; // Size 0x34

typedef struct PpPos16 {
    /* 0x00 */ u16 x;
    /* 0x02 */ u16 y;
} PpPos16;

/* A water splash slot (D_801117E0_pump_pump_away, 20 x 0x10). */
typedef struct PpSplash {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 alpha;
    /* 0x08 */ f32 vel;
    /* 0x0C */ omObjData *obj;
} PpSplash;

/* The water arc between a team's pump and its balloon (D_80113518_pump_pump_away). */
typedef struct PpArc {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 team;
    /* 0x08 */ f32 angle;
    /* 0x0C */ omObjData *obj;
} PpArc;

#define PP_WRAP(a) ((a) >= 360.0f ? (a) - 360.0f : (a) < 0.0f ? (a) + 360.0f : (a))

/* A player's pump state (D_80113570_pump_pump_away, 4 x 0x10). */
typedef struct PpPump {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 flag;
    /* 0x0C */ s32 player;
} PpPump;

/* A player (D_80113438_pump_pump_away, 4 x 0x38). */
typedef struct PpPlayer {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ omObjData *obj;
    /* 0x08 */ s32 state;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
} PpPlayer; // Size 0x38

/* A team's pump tank (D_801117C0_pump_pump_away, 2 x 0x10). */
typedef struct PpTank {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 level;
    /* 0x0C */ s32 count;
} PpTank;

/* A fading effect model's state (D_80113400_pump_pump_away, 3 x 8). */
typedef struct PpFx {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 alpha;
} PpFx;

/* The record display (D_801135B0_pump_pump_away). */
typedef struct PpRecord {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 spr;
    /* 0x06 */ s16 file;
    /* 0x08 */ s16 grp;
    /* 0x0A */ s16 win;
    /* 0x0C */ s32 digit[3];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u16 record;
    /* 0x20 */ s32 scale;
    /* 0x24 */ s32 dir;
} PpRecord; // Size 0x28

/* The record line on the course (D_801135D8_pump_pump_away). */
typedef struct PpRecLine {
    /* 0x00 */ s32 state;
    /* 0x04 */ u16 rec;
    /* 0x08 */ s32 flag;
} PpRecLine;

/* A distance marker (D_80113418_pump_pump_away, 2 x 0x10). */
typedef struct PpMarker {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 n;
    /* 0x08 */ f32 angle;
    /* 0x0C */ s32 stop;
} PpMarker;

typedef s32 (*PpDrawHookAdd)(s32, void (*)(Gfx **, s32, s32), u8);

extern s32 fontcolor;
extern s32 D_800A178C_main[][6];
extern s16 D_800CDA7C_main[];
extern s8 D_800CBB6E_main[];
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[4];
extern u8 D_800D6A90_main;
extern u8 D_800D2008_main;

extern Vec D_80110E70_pump_pump_away[];
extern Vec D_80110EA0_pump_pump_away[];
extern PpRgb D_80110EB8_pump_pump_away[];

extern f32 D_801116E0_pump_pump_away;
extern f32 D_801116E4_pump_pump_away;
extern s32 D_801116F4_pump_pump_away;
extern PpTeam D_80111978_pump_pump_away[2];
extern CcEnt D_80111A30_pump_pump_away[50];
extern PpScreen D_80113530_pump_pump_away;
extern PpArc D_80113518_pump_pump_away;
/* Fields of D_80113518_pump_pump_away under their own labels (retail addresses each directly). */
extern s32 D_8011351C_pump_pump_away; /* .team */
extern f32 D_80113520_pump_pump_away; /* .angle */
extern omObjData *D_80113524_pump_pump_away; /* .obj */
extern s16 D_80111108_pump_pump_away;
extern s16 D_8011110C_pump_pump_away;
extern s16 D_8011110E_pump_pump_away;
extern s32 D_80111110_pump_pump_away;
extern s16 D_8011110A_pump_pump_away;
extern PpFx D_80113400_pump_pump_away[3];
extern PpRecord D_801135B0_pump_pump_away;
extern PpRecLine D_801135D8_pump_pump_away;
/* Fields of D_801135B0_pump_pump_away and D_801135D8_pump_pump_away under their own labels (retail addresses each directly). */
extern s16 D_801135B4_pump_pump_away; /* D_801135B0_pump_pump_away.spr */
extern s16 D_801135B8_pump_pump_away; /* D_801135B0_pump_pump_away.grp */
extern u16 D_801135CC_pump_pump_away; /* D_801135B0_pump_pump_away.record */
extern u16 D_801135DC_pump_pump_away; /* D_801135D8_pump_pump_away.rec */
extern s32 D_801135E0_pump_pump_away; /* D_801135D8_pump_pump_away.flag */
extern PpMarker D_80113418_pump_pump_away[2];
extern s32 D_80111700_pump_pump_away;
extern s32 D_80111704_pump_pump_away;
extern s32 D_80111708_pump_pump_away;
extern Vec D_80111004_pump_pump_away[];
/* Fields of D_80113530_pump_pump_away under their own labels (retail addresses each directly). */
extern s32 D_80113534_pump_pump_away; /* .grp */
extern s32 D_80113538_pump_pump_away; /* .draw */
extern HuSprite_Unk84_Struct *D_8011353C_pump_pump_away; /* .spr */
extern s32 D_80113540_pump_pump_away; /* .alpha */
extern s32 D_80113544_pump_pump_away; /* .timer */
extern PpSplash D_801117E0_pump_pump_away[20];
extern PpTank D_801117C0_pump_pump_away[2];
extern PpHud D_80111758_pump_pump_away[2];
/* Fields of D_80111758_pump_pump_away[0] and [1] under their own labels (retail addresses each directly). */
extern s32 D_8011175C_pump_pump_away; /* [0].grp */
extern s32 D_80111760_pump_pump_away; /* [0].draw */
extern HuSprite_Unk84_Struct *D_80111764_pump_pump_away; /* [0].spr */
extern s32 D_80111790_pump_pump_away; /* [1].grp */
extern s32 D_80111794_pump_pump_away; /* [1].draw */
extern HuSprite_Unk84_Struct *D_80111798_pump_pump_away; /* [1].spr */
extern s32 D_80111788_pump_pump_away; /* D_80111758_pump_pump_away.alpha */
extern s32 D_801117BC_pump_pump_away; /* D_8011178C_pump_pump_away.alpha */
extern Vec D_80110FC4_pump_pump_away[];
extern PpPos16 D_80110FDC_pump_pump_away[];
extern PpPos16 D_80110FE4_pump_pump_away[];
extern Vec D_80110F6C_pump_pump_away[];
extern f32 D_80110F9C_pump_pump_away[];
extern s32 D_80113528_pump_pump_away;
extern s32 D_8011352C_pump_pump_away;
extern PpPlayer D_80113438_pump_pump_away[4];
extern PpPump D_80113570_pump_pump_away[4];
extern PpTexSize D_80113548_pump_pump_away[];
extern s32 D_801135E4_pump_pump_away;

void func_8001E888_main(s16 model, f32 u, f32 v, u16 w, u16 h, char *name, u8 arg6);
void func_80088800_main(f32 *mtx, f32 x, f32 y, f32 z);
void func_80034048_main(s16, s16);
void func_80032FC0_main(s16, u8, u8);
s16 func_80032694_main(HmfData *, u16, s32, char *);
void func_800335BC_main(char *arg0, void *arg1);
void func_8010749C_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2);
void func_8010775C_pump_pump_away(omObjData *obj);
void func_801078B4_pump_pump_away(void);
void func_80108560_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2);
void func_80108810_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2);
void func_80108B0C_pump_pump_away(omObjData *obj);
void func_8010A468_pump_pump_away(void);
void func_8010AF70_pump_pump_away(omObjData *obj);
s16 func_8000B5BC_main(s32);
void func_8001F974_main(s16, s16);
void func_8000BC48_main(u16, u16);
u16 GWMgRecordGet(s16 arg0);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
s32 func_8010CCBC_pump_pump_away(void);
void func_8010CDF4_pump_pump_away(omObjData *obj);
void func_8010CEE8_pump_pump_away(omObjData *obj);
omObjData *func_80045EF4_main(u32 arg0, s16 arg1);
void func_8004AE00_main(s16 handle, s16 pan);

void func_80110D28_pump_pump_away(void);
void func_801059A0_pump_pump_away(void);
Gfx **func_801059BC_pump_pump_away(Gfx **gfx);
Gfx **func_80105AA0_pump_pump_away(Gfx **gfx);
Gfx **func_80105B6C_pump_pump_away(Gfx **gfx, u8 alpha);
f32 func_80105B9C_pump_pump_away(f32 angle, f32 add);
u8 func_80105C1C_pump_pump_away(s32 max);
void func_80105C54_pump_pump_away(void);
void func_80105D1C_pump_pump_away(s32 player);
f32 func_80105D94_pump_pump_away(f32 x);
void func_80105EE4_pump_pump_away(Vec *from, Vec *to, Vec *out);
void func_80106260_pump_pump_away(u16 x, u16 y, char *str, u16 color);
void func_80106724_pump_pump_away(omObjData *obj);
void func_8010780C_pump_pump_away(omObjData *obj);
void func_8010682C_pump_pump_away(omObjData *obj);
void func_801078EC_pump_pump_away(omObjData *obj);
void func_801068C8_pump_pump_away(omObjData *obj);
void func_80107964_pump_pump_away(omObjData *obj);
void func_80107A8C_pump_pump_away(omObjData *obj);
void func_80108CFC_pump_pump_away(omObjData *obj);
void func_8010AD24_pump_pump_away(omObjData *obj);
void func_80109B80_pump_pump_away(omObjData *obj);
void func_8010A570_pump_pump_away(omObjData *obj);
void func_8010AE40_pump_pump_away(omObjData *obj);
void func_801069D0_pump_pump_away(omObjData *obj);
void func_80106A6C_pump_pump_away(omObjData *obj);
void func_8010ADA0_pump_pump_away(omObjData *obj);
void func_801082AC_pump_pump_away(omObjData *obj);
void func_8010BF14_pump_pump_away(omObjData *obj);
void func_8010BD80_pump_pump_away(omObjData *obj);
void func_8010C060_pump_pump_away(omObjData *obj);
void func_80107338_pump_pump_away(omObjData *obj);
void func_8010A390_pump_pump_away(omObjData *obj);
void func_8010D48C_pump_pump_away(omObjData *obj);
void func_8010C1C8_pump_pump_away(omObjData *obj);
void func_8010811C_pump_pump_away(omObjData *obj);
void func_8010D620_pump_pump_away(omObjData *obj);
void func_8010E6B8_pump_pump_away(omObjData *obj);
void func_8010E98C_pump_pump_away(omObjData *obj);
void func_8010654C_pump_pump_away(omObjData *obj);
void func_8010B630_pump_pump_away(omObjData *obj);
void func_80109D74_pump_pump_away(omObjData *obj);
void func_8010EBC4_pump_pump_away(omObjData *obj);
void func_80107EB8_pump_pump_away(omObjData *obj);
void func_8010A150_pump_pump_away(omObjData *obj);
void func_8010FCF8_pump_pump_away(omObjData *obj);
void func_8010FC64_pump_pump_away(omObjData *obj);
void func_80110034_pump_pump_away(omObjData *obj);
void func_8010921C_pump_pump_away(omObjData *obj);
void func_80110290_pump_pump_away(omObjData *obj);
void func_8010E0F4_pump_pump_away(omObjData *obj);
void func_80110260_pump_pump_away(omObjData *obj);
void func_8010C4D0_pump_pump_away(omObjData *obj);
void func_80110574_pump_pump_away(omObjData *obj);
void func_80109E98_pump_pump_away(omObjData *obj);
void func_801098E0_pump_pump_away(omObjData *obj);
void func_8010FEF8_pump_pump_away(omObjData *obj);
void func_8010D95C_pump_pump_away(omObjData *obj);
void func_8010B370_pump_pump_away(omObjData *obj);
void func_801104BC_pump_pump_away(omObjData *obj);
void func_8010BC14_pump_pump_away(omObjData *obj);
void func_8010FD94_pump_pump_away(omObjData *obj);
void func_8010FEB4_pump_pump_away(omObjData *obj);
void func_8010D1B8_pump_pump_away(omObjData *obj);
void func_8010F688_pump_pump_away(omObjData *obj);
void func_8011038C_pump_pump_away(omObjData *obj);
void func_8010FE6C_pump_pump_away(omObjData *obj);
void func_80108E74_pump_pump_away(omObjData *obj);
void func_80110458_pump_pump_away(omObjData *obj);
void func_80110B34_pump_pump_away(omObjData *obj);
void func_80109C30_pump_pump_away(omObjData *obj);
void func_8010AED4_pump_pump_away(omObjData *obj);
void func_8010C3E0_pump_pump_away(omObjData *obj);
void func_8010FA64_pump_pump_away(omObjData *obj);
void func_8010D6F4_pump_pump_away(omObjData *obj);
void func_8010FF70_pump_pump_away(omObjData *obj);
void func_8010F024_pump_pump_away(omObjData *obj);
void func_8010FD34_pump_pump_away(omObjData *obj);
void func_801102E4_pump_pump_away(omObjData *obj);
void func_80108FE0_pump_pump_away(omObjData *obj);
void func_8010628C_pump_pump_away(omObjData *obj);
void func_8010B274_pump_pump_away(omObjData *obj);
void func_8010A3F0_pump_pump_away(omObjData *obj);
void func_801094CC_pump_pump_away(omObjData *obj);
void func_8010B898_pump_pump_away(omObjData *obj);
void func_8010DC68_pump_pump_away(omObjData *obj);
void func_8010E45C_pump_pump_away(omObjData *obj);
void func_8010FF28_pump_pump_away(omObjData *obj);
void func_8010FA28_pump_pump_away(omObjData *obj);
void func_801103D8_pump_pump_away(omObjData *obj);
void func_8010FE2C_pump_pump_away(omObjData *obj);
void func_8010F268_pump_pump_away(omObjData *obj);
void func_801104F4_pump_pump_away(omObjData *obj);

extern s32 D_801116F8_pump_pump_away; /* advance the game phase on the next frame */
extern s32 D_801116FC_pump_pump_away; /* phase timer */
extern s32 D_80111118_pump_pump_away;
void func_8010DD24_pump_pump_away(omObjData *obj);
void func_8010FA20_pump_pump_away(omObjData *obj);
/* A camera (D_8011111C_pump_pump_away; River Raiders' and Curtain Call's layout). */
typedef struct PpCamera {
    /* 0x00 */ f32 scissor[4];
    /* 0x10 */ f32 viewport[6];
    /* 0x28 */ f32 fov;
} PpCamera; // Size 0x2C
extern PpCamera D_8011111C_pump_pump_away[1];
void func_80110BB8_pump_pump_away(void);
s32 func_8000B710_main(s32 arg0);
extern const s16 D_801116D8_pump_pump_away[];
/* Six-slot effect tables (D_80111710_pump_pump_away, D_801119E8_pump_pump_away; 6 x 0xC) and a four-slot one (D_801135E8_pump_pump_away, 4 x 0x10). */
typedef struct PpSlot12 {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ f32 angle;
} PpSlot12;
typedef struct PpSlot16 {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 dir;
    /* 0x0C */ f32 speed;
} PpSlot16;
extern PpSlot12 D_80111710_pump_pump_away[6];
extern PpSlot12 D_801119E8_pump_pump_away[6];
extern PpSlot16 D_801135E8_pump_pump_away[4];
extern s16 D_801116EA_pump_pump_away;
extern s16 D_801116EE_pump_pump_away;
extern s16 D_801116F0_pump_pump_away;
extern s16 D_801116F2_pump_pump_away;
s32 func_8010FAA8_pump_pump_away(void);
void func_8010FB70_pump_pump_away(omObjData *obj);
void func_801100F0_pump_pump_away(void);
void func_80110A78_pump_pump_away(void);
void func_8003F578_main(s16);
void func_8003F5C0_main(void);
void func_8010F900_pump_pump_away(omObjData *obj);
extern s32 D_8011199C_pump_pump_away; /* D_80111978_pump_pump_away[0].state */
/* Four-slot table (D_80111920_pump_pump_away, 4 x 0x14). */
typedef struct PpSlot20 {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 dir;
    /* 0x0C */ f32 speed;
    /* 0x10 */ f32 phase;
} PpSlot20;
extern PpSlot20 D_80111920_pump_pump_away[4];
extern s16 D_801116EC_pump_pump_away;
extern s32 D_801119E4_pump_pump_away;
void func_801109BC_pump_pump_away(void);
extern u16 D_80111114_pump_pump_away;
extern f32 D_80111990_pump_pump_away; /* D_80111978_pump_pump_away[0].dist */
extern f32 D_801119C4_pump_pump_away; /* D_80111978_pump_pump_away[1].dist */
extern f32 D_8011101C_pump_pump_away[]; /* start heights of the D_80111920_pump_pump_away models */
extern f32 D_8011102C_pump_pump_away[]; /* start heights of the D_801135E8_pump_pump_away models */
extern f32 D_8011103C_pump_pump_away[]; /* heights of the D_80111710_pump_pump_away models */
extern s32 D_80111970_pump_pump_away; /* next D_8011103C_pump_pump_away slot */
extern f32 D_8011109C_pump_pump_away[]; /* heights of the D_801119E8_pump_pump_away models */
extern s32 D_801133F8_pump_pump_away; /* next D_8011109C_pump_pump_away slot */
extern u8 D_801116E8_pump_pump_away; /* the marker motion bank */

/* .data */
Vec D_80110E70_pump_pump_away[4] = { { -295.0f, 10.0f, 600.0f }, { -135.0f, 10.0f, 600.0f }, { 135.0f, 10.0f, 600.0f }, { 295.0f, 10.0f, 600.0f } };
Vec D_80110EA0_pump_pump_away[2] = { { -215.0f, 200.0f, 0.0f }, { 215.0f, 200.0f, 0.0f } };
PpRgb D_80110EB8_pump_pump_away[15] = { { 200, 230, 255 }, { 20, 150, 255 }, { 135, 225, 255 }, { 65, 170, 250 }, { 20, 100, 220 }, { 10, 60, 170 }, { 10, 40, 130 }, { 10, 30, 110 }, { 15, 25, 100 }, { 15, 25, 90 }, { 15, 25, 90 }, { 15, 25, 90 }, { 15, 25, 90 }, { 15, 25, 90 }, { 15, 25, 90 } };
Vec D_80110F6C_pump_pump_away[4] = { { -295.0f, 10.0f, 600.0f }, { -135.0f, 10.0f, 600.0f }, { 135.0f, 10.0f, 600.0f }, { 295.0f, 10.0f, 600.0f } };
f32 D_80110F9C_pump_pump_away[10] = { 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f };
Vec D_80110FC4_pump_pump_away[2] = { { -215.0f, 0.0f, 0.0f }, { 215.0f, 0.0f, 0.0f } };
PpPos16 D_80110FDC_pump_pump_away[2] = { { 23, 208 }, { 238, 208 } };
PpPos16 D_80110FE4_pump_pump_away[8] = { { 29, 211 }, { 29, 211 }, { 38, 211 }, { 47, 211 }, { 244, 211 }, { 244, 211 }, { 253, 211 }, { 262, 211 } };
Vec D_80111004_pump_pump_away[2] = { { -215.0f, 0.0f, 0.0f }, { 215.0f, 0.0f, 0.0f } };
f32 D_8011101C_pump_pump_away[4] = { 1500.0f, 1750.0f, 2250.0f, 2500.0f };
f32 D_8011102C_pump_pump_away[4] = { 2750.0f, 3250.0f, 3500.0f, 3750.0f };
f32 D_8011103C_pump_pump_away[24] = { 4200.0f, 4400.0f, 4600.0f, 4800.0f, 5200.0f, 5400.0f, 5600.0f, 5800.0f, 6200.0f, 6400.0f, 6600.0f, 6800.0f, 7200.0f, 7400.0f, 7600.0f, 7800.0f, 8200.0f, 8400.0f, 8600.0f, 8800.0f, 9200.0f, 9400.0f, 9600.0f, 9800.0f };
f32 D_8011109C_pump_pump_away[27] = { 1250.0f, 1500.0f, 1750.0f, 2250.0f, 2500.0f, 2750.0f, 3250.0f, 3500.0f, 3750.0f, 4250.0f, 4500.0f, 4750.0f, 5250.0f, 5500.0f, 5750.0f, 6250.0f, 6500.0f, 6750.0f, 7250.0f, 7500.0f, 7750.0f, 8250.0f, 8500.0f, 8750.0f, 9250.0f, 9500.0f, 9750.0f };
s16 D_80111108_pump_pump_away = 0;
s16 D_8011110A_pump_pump_away = 0;
s16 D_8011110C_pump_pump_away = 18;
s16 D_8011110E_pump_pump_away = 0;
s32 D_80111110_pump_pump_away = 0;
u16 D_80111114_pump_pump_away = 0;
s32 D_80111118_pump_pump_away = 0;
PpCamera D_8011111C_pump_pump_away[1] = { { { 0.0f, 0.0f, 320.0f, 240.0f }, { 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f }, 20.0f } };


void func_801059A0_pump_pump_away(void) {
    func_80110D28_pump_pump_away();
}

Gfx **func_801059BC_pump_pump_away(Gfx **gfx) {
    u32 mode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *g = *gfx;

    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                  G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(g++, mode);
    gDPSetCombineMode(g++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetPrimColor(g++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(g++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    *gfx = g;
    return gfx;
}

Gfx **func_80105AA0_pump_pump_away(Gfx **gfx) {
    u32 mode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *g = *gfx;

    gDPPipeSync(g++);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gSPClearGeometryMode(g++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                  G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(g++, mode);
    gDPSetCombineMode(g++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetRenderMode(g++, IM_RD | CVG_DST_FULL | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                     GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    *gfx = g;
    return gfx;
}

Gfx **func_80105B6C_pump_pump_away(Gfx **gfx, u8 alpha) {
    Gfx *g;

    g = *gfx;
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, alpha);
    *gfx = g;
    return gfx;
}

f32 func_80105B9C_pump_pump_away(f32 angle, f32 add) {
    f32 ret = angle + add;

    while (ret >= 360.0f) {
        ret -= 360.0f;
    }
    while (ret < 0.0f) {
        ret += 360.0f;
    }
    return ret;
}

u8 func_80105C1C_pump_pump_away(s32 max) {
    return ((u32)(rand8() * max)) >> 8;
}

void func_80105C54_pump_pump_away(void) {
    CcEnt *ent;
    u32 i;

    for (i = 0, ent = D_80111A30_pump_pump_away; i < 50; i++, ent++) {
        ent->obj = NULL;
        ent->unk04 = 0;
        ent->unk06 = 0;
        ent->unk08 = 0;
        ent->unk0A = 0;
        ent->unk0C = 0;
        ent->unk0E = 0;
        ent->unk10 = 0;
        ent->unk12 = 0;
        ent->unk14 = 0;
        ent->unk16 = 0;
        ent->unk18 = 0;
        ent->unk1C = 0;
        ent->unk20 = 0;
        ent->unk24 = 0;
        ent->unk28 = 0;
        ent->unk2C = 0;
        ent->unk30 = 0;
        ent->unk34 = 0;
        ent->unk38 = 0;
        ent->unk3C = 0;
        ent->grp = -1;
        ent->spr = -1;
        ent->pos.x = ent->pos.y = ent->pos.z = 0.0f;
        ent->unk50.x = ent->unk50.y = ent->unk50.z = 0.0f;
        ent->unk5C.x = ent->unk5C.y = ent->unk5C.z = 0.0f;
        ent->unk68 = 0.0f;
        ent->unk6C = 0.0f;
        ent->unk70 = 0.0f;
        ent->unk74 = 0.0f;
        ent->unk78.x = ent->unk78.y = ent->unk78.z = 0.0f;
    }
}

void func_80105D1C_pump_pump_away(s32 player) {
    D_800CDA7C_main[GwPlayer[player].pad] = 0;
    D_800D5558_main[GwPlayer[player].pad] = 0;
    D_800CBB6E_main[GwPlayer[player].pad] = 0;
    D_800D20A1_main[GwPlayer[player].pad] = 0;
}

f32 func_80105D94_pump_pump_away(f32 x) {
    f32 a;
    f32 b;
    f32 sum;
    s32 sign;
    s32 i;

    sign = 1;
    if (x > 1.0f) {
        x = 1.0f / x;
    } else {
        sign = -1;
        if (x < -1.0f) {
            x = 1.0f / x;
        } else {
            sign = 0;
        }
    }
    sum = 0.0f;
    i = 6;
    do {
        a = (f32)(i * i) * x * x;
        b = (f32)(i * 2 + 1) + sum;
        i--;
        sum = a / b;
    } while (i > 0);
    if (sum != -1.0f) {
        if (sign > 0) {
            return 1.5707963267948966 - (x / (sum + 1.0f));
        }
        if (sign < 0) {
            return -1.5707963267948966 - (x / (sum + 1.0f));
        }
        return x / (sum + 1.0f);
    }
    return 0.0f;
}

void func_80105EE4_pump_pump_away(Vec *from, Vec *to, Vec *out) {
    Vec delta;
    Vec fromV;
    Vec toV;
    f32 horizontal;
    f32 pitch;
    f32 yaw;
    f32 y;
    f32 eps;
    s32 nearPositive;
    s32 nearNegative;

    fromV.x = from->x;
    fromV.y = from->y;
    fromV.z = from->z;
    toV.x = to->x;
    toV.y = to->y;
    toV.z = to->z;
    delta.x = toV.x - fromV.x;
    delta.y = toV.y - fromV.y;
    delta.z = toV.z - fromV.z;
    horizontal = HuSqrtf(delta.x * delta.x + delta.z * delta.z);
    nearPositive = horizontal <= 0.002f;
    nearNegative = horizontal >= -0.002f;
    if (nearPositive & nearNegative) {
        horizontal = 0.0f;
        y = delta.y;
        eps = 0.0001f;
        yaw = horizontal;
        if (!(y > eps) && y < eps) {
            pitch = horizontal;
        } else {
            pitch = 180.0f;
        }
    } else {
        if (delta.x != 0.0f && delta.z != 0.0f) {
            yaw = func_80105D94_pump_pump_away(delta.x / delta.z) * 57.29577951308232;
        } else if (delta.z == 0.0f) {
            if (delta.x >= 0.0f) {
                yaw = 90.0f;
            } else {
                yaw = 270.0f;
            }
        } else {
            yaw = 0.0f;
        }
        if (delta.z < 0.0f) {
            yaw -= 180.0f;
        }
        if (horizontal != 0.0f && delta.y != 0.0f) {
            pitch = func_80105D94_pump_pump_away(delta.y / horizontal) * 57.29577951308232;
        } else {
            pitch = 0.0f;
        }
        yaw = yaw >= 360.0f ? yaw - 360.0f : yaw < 0.0f ? yaw + 360.0f : yaw;
        pitch = pitch + 90.0f >= 360.0f ? pitch + 90.0f - 360.0f : pitch + 90.0f < 0.0f ? pitch + 90.0f + 360.0f : pitch + 90.0f;
    }
    nearPositive = pitch <= 0.002f;
    nearNegative = pitch >= -0.002f;
    if (nearPositive & nearNegative) {
        pitch = 0.0f;
    }
    horizontal = HuSqrtf(delta.y * delta.y + horizontal * horizontal);
    out->z = yaw;
    out->x = horizontal;
}

void func_80106260_pump_pump_away(u16 x, u16 y, char *str, u16 color) {
    fontcolor = color;
    print8(x, y, str);
}

#ifdef NON_MATCHING
void func_8010628C_pump_pump_away(omObjData *obj) {
    PpTeam *t;
    PpTeam *t1;
    f32 scale;
    s32 i;

    switch (D_801116F4_pump_pump_away) {
        case 4:
            t = D_80111978_pump_pump_away;
            t1 = &t[1];
            if (t->dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y -= t->speed;
            } else {
                obj->trans.y -= t1->speed;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (D_80113530_pump_pump_away.state >= 2) {
        case 7:
                obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            break;
    }
    for (i = 0; i < 2; i++) {
        scale = D_80111978_pump_pump_away[i].obj->trans.y - obj->trans.y - 200.0f;
        if ((scale > 1000.0f) | (scale < -100.0f)) {
            func_8001C258_main(obj->model[i + 1], 4, 4);
        } else {
            func_8001C258_main(obj->model[i + 1], 4, 0);
            scale = 3.0 - scale * 0.003;
            if (scale >= 3.0) {
                scale = 3.0f;
            }
        }
        Hu3DModelPosSet(obj->model[i + 1], D_80110EA0_pump_pump_away[i].x, obj->trans.y + 1.0, D_80110EA0_pump_pump_away[i].z + 0.0f);
        Hu3DModelScaleSet(obj->model[i + 1], scale, scale, scale);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010628C_pump_pump_away);
#endif

void func_8010654C_pump_pump_away(omObjData *obj) {
    s32 i;

    obj->model[0] = func_8000B108_main(0x2E0000, 0x289);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    for (i = 1; i < 3; i++) {
        obj->model[i] = func_8000B0A0_main(0, 0xC9);
        func_8001C2FC_main(obj->model[i], 0x80000000, 0);
        func_8001C448_main(obj->model[i]);
        func_8001C514_main(obj->model[i]);
        func_80088800_main(HmfModelData[obj->model[i]].mtx, 0.0f, 1.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[i], 3.0f, 3.0f, 3.0f);
        Hu3DModelPosSet(obj->model[i], D_80110EA0_pump_pump_away[i - 1].x, obj->trans.y + 1.0, D_80110EA0_pump_pump_away[i - 1].z + 0.0f);
    }
    obj->func = func_8010628C_pump_pump_away;
}

void func_801066F0_pump_pump_away(void) {
    omAddObj(200, 3, 0, -1, func_8010654C_pump_pump_away);
}

void func_80106724_pump_pump_away(omObjData *obj) {
    PpTeam *t;
    PpTeam *t1;

    switch (D_801116F4_pump_pump_away) {
        case 4:
            t = D_80111978_pump_pump_away;
            t1 = &t[1];
            if (t->dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y = obj->trans.y - t->speed * 0.9;
            } else {
                obj->trans.y = obj->trans.y - t1->speed * 0.9;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (D_80113530_pump_pump_away.state >= 2) {
        case 7:
                obj->trans.x = obj->trans.y = 0.0f;
                obj->trans.z = -1100.0f;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            break;
    }
}

void func_8010682C_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E0003, 0x289);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1100.0f;
    obj->func = func_80106724_pump_pump_away;
}

void func_80106894_pump_pump_away(void) {
    omAddObj(250, 1, 0, -1, func_8010682C_pump_pump_away);
}

void func_801068C8_pump_pump_away(omObjData *obj) {
    PpTeam *t;
    PpTeam *t1;

    switch (D_801116F4_pump_pump_away) {
        case 4:
            t = D_80111978_pump_pump_away;
            t1 = &t[1];
            if (t->dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y = obj->trans.y - t->speed * 0.8;
            } else {
                obj->trans.y = obj->trans.y - t1->speed * 0.8;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (D_80113530_pump_pump_away.state >= 2) {
        case 7:
                obj->trans.x = obj->trans.y = 0.0f;
                obj->trans.z = -1290.0f;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            break;
    }
}

void func_801069D0_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E0004, 0x289);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1290.0f;
    obj->func = func_801068C8_pump_pump_away;
}

void func_80106A38_pump_pump_away(void) {
    omAddObj(260, 1, 0, -1, func_801069D0_pump_pump_away);
}

#ifdef NON_MATCHING
void func_80106A6C_pump_pump_away(omObjData *obj) {
    HmfData *hmf = HmfModelData[obj->model[0]].hmf;
    Vtx *v = hmf->unk44[D_800D2008_main];
    PpTeam *t1;
    f32 dist;
    s32 step;
    u32 i;

    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
        case 2:
        case 3:
            for (i = 0; i < PP_HMF_VTXNUM(hmf); i++, v++) {
                if (i == 1 || i == 2) {
                    v->v.cn[0] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].r;
                    v->v.cn[1] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].g;
                    v->v.cn[2] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].b;
                } else {
                    v->v.cn[0] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].r;
                    v->v.cn[1] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].g;
                    v->v.cn[2] = D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].b;
                }
            }
            break;
        case 4:
            func_8001C258_main(obj->model[0], 4, 0);
            func_8001C258_main(obj->model[1], 4, 4);
            t1 = &D_80111978_pump_pump_away[1];
            if (D_80111978_pump_pump_away[1].dist < D_80111978_pump_pump_away[0].dist) {
                dist = D_80111978_pump_pump_away[0].dist;
            } else {
                dist = t1->dist;
            }
            step = dist * 0.01;
            D_801135E4_pump_pump_away = step * 0.01;
            if (func_80049F98_main() + D_800D6A90_main == 0) {
                if (D_80111978_pump_pump_away[0].dist - t1->dist > 0.0f) {
                    D_801116E0_pump_pump_away = D_80111978_pump_pump_away[0].dist * 1.25e-05;
                    D_801116E4_pump_pump_away = D_801116E4_pump_pump_away - D_80111978_pump_pump_away[0].speed * 0.08;
                } else {
                    D_801116E0_pump_pump_away = t1->dist * 1.25e-05;
                    D_801116E4_pump_pump_away = D_801116E4_pump_pump_away - t1->speed * 0.08;
                }
            }
            for (i = 0; i < PP_HMF_VTXNUM(hmf); i++, v++) {
                if (i == 1 || i == 2) {
                    v->v.cn[0] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].r -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].r - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].r) *
                              ((f32)((D_801135E4_pump_pump_away + 1) * 100 - step) * 0.01));
                    v->v.cn[1] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].g -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].g - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].g) *
                              ((f32)((D_801135E4_pump_pump_away + 1) * 100 - step) * 0.01));
                    v->v.cn[2] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].b -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].b - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away].b) *
                              ((f32)((D_801135E4_pump_pump_away + 1) * 100 - step) * 0.01));
                } else {
                    v->v.cn[0] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].r -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].r - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].r) *
                              ((f32)((D_801135E4_pump_pump_away + 2) * 100 - (dist + 10000.0f) * 0.01) * 0.01));
                    v->v.cn[1] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].g -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].g - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].g) *
                              ((f32)((D_801135E4_pump_pump_away + 2) * 100 - (dist + 10000.0f) * 0.01) * 0.01));
                    v->v.cn[2] = (f32)D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].b -
                        (f32)((f32)(D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 2].b - D_80110EB8_pump_pump_away[D_801135E4_pump_pump_away + 1].b) *
                              ((f32)((D_801135E4_pump_pump_away + 2) * 100 - (dist + 10000.0f) * 0.01) * 0.01));
                }
            }
        case 5:
            func_8001E888_main(obj->model[0], D_801116E4_pump_pump_away, D_801116E4_pump_pump_away, D_80113548_pump_pump_away[0].w, D_80113548_pump_pump_away[0].h,
                               "dammy_0-sky_b_2", 0);
            break;
        case 6:
            if (D_80113530_pump_pump_away.state >= 2) {
        case 7:
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 0);
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80106A6C_pump_pump_away);
#endif

void func_80107338_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E0001, 0x289);
    obj->model[1] = func_8000B108_main(0x2E0002, 0x289);
    func_8001C2FC_main(obj->model[0], 0x20000, 0x20000);
    func_8001C448_main(obj->model[0]);
    func_8001C954_main(obj->model[0]);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C258_main(obj->model[1], 4, 0);
    func_800335BC_main("m213_back_DEF", D_80113548_pump_pump_away);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1300.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, -1300.0f);
    D_801116E0_pump_pump_away = 0.0f;
    D_801116E4_pump_pump_away = 0.0f;
    D_801135E4_pump_pump_away = 0;
    obj->func = func_80106A6C_pump_pump_away;
}

void func_8010745C_pump_pump_away(void) {
    omSetStatBit(omAddObj(100, 2, 0, -1, func_80107338_pump_pump_away), 0xA0);
}

#ifdef NON_MATCHING
void func_8010749C_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2) {
    PpScreen *s = &D_80113530_pump_pump_away;
    Gfx *g;
    s32 i;
    s32 j;

    if (s->state != -1) {
        if (D_80113540_pump_pump_away < 0xFF) {
            gfx = func_80105B6C_pump_pump_away(func_80105AA0_pump_pump_away(gfx), (u8)D_80113540_pump_pump_away);
        } else {
            gfx = func_801059BC_pump_pump_away(gfx);
        }
        g = *gfx;
        gDPSetTextureLUT(g++, G_TT_RGBA16);
        gDPLoadTLUT_pal16(g++, 0, s->spr->unk0C);
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                gDPLoadTextureTile_4b(g++, s->spr->unk08, G_IM_FMT_CI, 64, 48, 0, 0, 64, 48, 0,
                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                      G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 64 << 2, 48 << 2);
                gSPTextureRectangle(g++, (i * 64) << 2, (j * 48) << 2, ((i + 1) * 64) << 2, ((j + 1) * 48) << 2,
                                    G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            }
        }
        *gfx = g;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010749C_pump_pump_away);
#endif

void func_8010775C_pump_pump_away(omObjData *obj) {
    PpScreen *s = &D_80113530_pump_pump_away;

    if (s->state == -1) {
        return;
    }
    switch (s->state) {
        case 0:
            s->alpha = 0;
            break;
        case 1:
            s->alpha += 26;
            if (s->alpha >= 256) {
                s->alpha = 255;
                s->state = 2;
            }
            break;
        case 2:
            if (s->timer != 0) {
                s->timer--;
            } else {
                s->state = 3;
            }
            break;
        case 3:
            s->alpha -= 25;
            if (s->alpha < 30) {
                s->alpha = 0;
                s->state = 4;
            }
            break;
        case 4:
            s->alpha = 0;
            s->state = -1;
            break;
    }
}

void func_8010780C_pump_pump_away(omObjData *obj) {
    PpDrawHookAdd hookAdd = (PpDrawHookAdd)(void (*)(void))func_8001AC8C_main;

    D_80113534_pump_pump_away = func_8000B838_main(0x2E001E);
    D_8011353C_pump_pump_away = func_80055194_main((s16)D_80113534_pump_pump_away);
    D_80113538_pump_pump_away = hookAdd(0, func_8010749C_pump_pump_away, 6);
    func_8001C8A8_main((s16)D_80113538_pump_pump_away, 1);
    D_80113540_pump_pump_away = 0;
    D_80113530_pump_pump_away.state = -1;
    D_80113544_pump_pump_away = 30;
    obj->func = func_8010775C_pump_pump_away;
}

void func_801078B4_pump_pump_away(void) {
    omAddObj(950, 1, 0, -1, func_8010780C_pump_pump_away)->work[0] = 0;
}

void func_801078EC_pump_pump_away(omObjData *obj) {
    PpSplash *p;
    s32 i;

    for (i = 0; i < 20; i++) {
        p = &D_801117E0_pump_pump_away[i];
        if (p->state == 0) {
            p->state = 1;
            p->obj->trans.x = obj->trans.x;
            p->obj->trans.y = obj->trans.y + 50.0f;
            p->obj->trans.z = obj->trans.z + 50.0f;
            p->vel = 0;
            return;
        }
    }
}

void func_80107964_pump_pump_away(omObjData *obj) {
    PpPump *pump = &D_80113570_pump_pump_away[obj->work[0]];
    PpPlayer *pl = &D_80113438_pump_pump_away[pump->player];

    func_8001C6A8_main(obj->model[0], HmfModelData[pl->obj->model[0]].unk40);
    if (pl->unk18 != 0 && HmfModelData[obj->model[0]].unk40 <= 6.0f) {
        if (pump->timer != 0) {
            pump->timer--;
            return;
        }
        pump->flag ^= 1;
        pump->timer = 1;
        func_80034048_main((s16)obj->work[1], (s16)pump->flag);
    } else {
        pump->timer = 0;
        func_80034048_main((s16)obj->work[1], 0);
    }
}

void func_80107A8C_pump_pump_away(omObjData *obj) {
    PpPump *pump = &D_80113570_pump_pump_away[obj->work[0]];

    if (pump->state == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 2:
            func_80107964_pump_pump_away(obj);
            break;
        case 3:
            if (pump->state == 0) {
                func_801078EC_pump_pump_away(obj);
                pump->state = 1;
            }
            func_8001C258_main(obj->model[0], 4, 4);
            break;
        case 0:
        case 1:
        case 4:
            break;
    }
}

void func_80107B40_pump_pump_away(omObjData *obj) {
    void *data;
    PpPump *pump;
    s32 i;

    obj->model[0] = func_8000B108_main(0x2E0005, 0x2A9);
    func_8000B460_main(obj, 0, 0x2E0006);
    /* retail: players 0 and 1 fall through into the second team's animation set-up */
    switch (obj->work[0]) {
        case 0:
        case 1:
            if (obj->work[0] == 0) {
                data = DataRead(0x2E0007);
                obj->work[1] = D_8011352C_pump_pump_away = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "m213_p1_DEF");
                HuMemMemoryFreePerm(data);
            } else {
                obj->work[1] = func_80032694_main(HmfModelData[obj->model[0]].hmf, (u16)D_8011352C_pump_pump_away, 0, "m213_p1_DEF");
            }
        case 2:
        case 3:
            if (obj->work[0] == 2) {
                data = DataRead(0x2E0008);
                obj->work[1] = D_80113528_pump_pump_away = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "m213_p1_DEF");
                HuMemMemoryFreePerm(data);
            } else {
                obj->work[1] = func_80032694_main(HmfModelData[obj->model[0]].hmf, (u16)D_80113528_pump_pump_away, 0, "m213_p1_DEF");
            }
            break;
    }
    func_80034048_main((s16)obj->work[1], 0);
    func_80032FC0_main((s16)obj->work[1], 1, 1);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 1, 1);
    obj->trans.x = D_80110F6C_pump_pump_away[obj->work[0]].x;
    obj->trans.y = D_80110F6C_pump_pump_away[obj->work[0]].y;
    obj->trans.z = D_80110F6C_pump_pump_away[obj->work[0]].z;
    obj->func = func_80107A8C_pump_pump_away;
    pump = &D_80113570_pump_pump_away[obj->work[0]];
    pump->state = 0;
    pump->timer = 0;
    pump->flag = 0;
    for (i = 0; i < 4; i++) {
        if ((D_80113438_pump_pump_away + i)->obj->work[3] == obj->work[0]) {
            break;
        }
    }
    pump->player = i;
}

void func_80107E5C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(500, 1, 1, -1, func_80107B40_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_80107EB8_pump_pump_away(omObjData *obj) {
    PpPlayer *pl[2];
    PpTank *tank = &D_801117C0_pump_pump_away[obj->work[0]];
    PpTeam *team;
    s32 level;
    s32 i;
    s32 n;

    for (i = 0, n = 0; (i < 4) & (n < 2); i++) {
        pl[n] = &D_80113438_pump_pump_away[i];
        n += GwPlayer[pl[n]->obj->work[0]].group == obj->work[0];
    }
    switch (tank->state) {
        case 0:
            if (tank->count < pl[0]->unk10 + pl[1]->unk10) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                level = (pl[0]->unk10 + pl[1]->unk10 - tank->count) / 3;
                tank->count = pl[0]->unk10 + pl[1]->unk10;
                if (level >= 10) {
                    level = 9;
                }
                tank->level = level;
                func_8001C92C_main(obj->model[0], D_80110F9C_pump_pump_away[level]);
                func_8001C814_main(obj->model[0], 1, 0);
                tank->state = 1;
            } else {
                func_8001C6A8_main(obj->model[0], 0.0f);
            }
            break;
        case 1:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                tank->state = 0;
                team = &D_80111978_pump_pump_away[obj->work[0]];
                team->unk0C = 1;
                team->unk10 = tank->level;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107EB8_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_8010811C_pump_pump_away(omObjData *obj) {
    PpTank *tank = &D_801117C0_pump_pump_away[obj->work[0]];

    switch (tank->state) {
        case 2:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C258_main(obj->model[0], 4, 4);
                tank->state = 3;
            }
            break;
        case 3:
            break;
        default:
            if (HmfModelData[obj->model[0]].unk40 == 0.0f ||
                D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C5B4_main(obj->model[0], obj->motion[1]);
                func_8001C814_main(obj->model[0], 2, 0);
                tank->state = 2;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010811C_pump_pump_away);
#endif

void func_801082AC_pump_pump_away(omObjData *obj) {
    if (D_801117C0_pump_pump_away[obj->work[0]].unk00 == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C814_main(obj->model[0], 1, 1);
            break;
        case 2:
            func_80107EB8_pump_pump_away(obj);
            break;
        case 3:
            func_8010811C_pump_pump_away(obj);
            break;
        case 4:
            break;
    }
}

void func_80108358_pump_pump_away(omObjData *obj) {
    void *data;
    PpTank *tank;

    obj->model[0] = func_8000B108_main(0x2E0009, 0x289);
    func_8000B460_main(obj, 0, 0x2E000A);
    func_8000B460_main(obj, 1, 0x2E000B);
    if (obj->work[0] != 0) {
        data = DataRead(0x2E000C);
        obj->work[1] = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "m213_hose_r_DEF");
        func_80032FC0_main((s16)obj->work[1], 1, 1);
        HuMemMemoryFreePerm(data);
        func_8001C448_main(obj->model[0]);
        func_8001C514_main(obj->model[0]);
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    obj->trans.x = D_80110FC4_pump_pump_away[obj->work[0]].x;
    obj->trans.y = D_80110FC4_pump_pump_away[obj->work[0]].y;
    obj->trans.z = D_80110FC4_pump_pump_away[obj->work[0]].z;
    obj->func = func_801082AC_pump_pump_away;
    tank = &D_801117C0_pump_pump_away[obj->work[0]];
    tank->unk00 = 0;
    tank->state = 0;
    tank->level = 0;
    tank->count = 0;
}

void func_80108504_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(600, 1, 2, -1, func_80108358_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_80108560_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2) {
    PpHud *h = &D_80111758_pump_pump_away[0];
    Gfx *g;
    s32 i;

    if (h->state != -1) {
        if (D_80111788_pump_pump_away < 0xFF) {
            gfx = func_80105B6C_pump_pump_away(func_80105AA0_pump_pump_away(gfx), (u8)D_80111788_pump_pump_away);
        } else {
            gfx = func_801059BC_pump_pump_away(gfx);
        }
        g = *gfx;
        gDPSetTextureLUT(g++, G_TT_RGBA16);
        gDPLoadTLUT_pal16(g++, 0, h->spr->unk0C);
        for (i = 0; i < 2; i++) {
            gDPLoadTextureTile_4b(g++, h->spr->unk08, G_IM_FMT_CI, 64, 16, 0, 0, 64, 16, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 64 << 2, 16 << 2);
            gSPTextureRectangle(g++, D_80110FDC_pump_pump_away[i].x << 2, D_80110FDC_pump_pump_away[i].y << 2, (D_80110FDC_pump_pump_away[i].x + 64) << 2,
                                (D_80110FDC_pump_pump_away[i].y + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
        *gfx = g;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108560_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_80108810_pump_pump_away(Gfx **gfx, s32 arg1, s32 arg2) {
    PpHud *h = &D_80111758_pump_pump_away[1];
    Gfx *g;
    s32 i;

    if (h->state != -1) {
        if (D_801117BC_pump_pump_away < 0xFF) {
            gfx = func_80105B6C_pump_pump_away(func_80105AA0_pump_pump_away(gfx), (u8)D_801117BC_pump_pump_away);
        } else {
            gfx = func_801059BC_pump_pump_away(gfx);
        }
        g = *gfx;
        gDPSetTextureLUT(g++, G_TT_RGBA16);
        gDPLoadTLUT_pal16(g++, 0, h->spr->unk0C);
        for (i = 0; i < 8; i++) {
            if (i != 0 && i != 4) {
                gDPLoadTextureTile_4b(g++, h->spr->unk08, G_IM_FMT_CI, 8, 100, 0, h->val[i], 8, h->val[i] + 10, 0,
                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                      G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPSetTileSize(g++, G_TX_RENDERTILE, 0, 0, 8 << 2, 10 << 2);
                gSPTextureRectangle(g++, D_80110FE4_pump_pump_away[i].x << 2, D_80110FE4_pump_pump_away[i].y << 2, (D_80110FE4_pump_pump_away[i].x + 8) << 2,
                                    (D_80110FE4_pump_pump_away[i].y + 10) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            }
        }
        *gfx = g;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108810_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_80108B0C_pump_pump_away(omObjData *obj) {
    s32 digit[4];
    PpHud *h = &D_80111758_pump_pump_away[1];
    s32 n;
    s32 cur;
    s32 t;
    s32 i;

    for (t = 0; t < 2; t++) {
        n = (D_80111978_pump_pump_away + t)->dist / 10.0f;
        digit[0] = n / 10000;
        n -= digit[0] * 10000;
        digit[1] = n / 1000;
        n -= digit[1] * 1000;
        digit[2] = n / 100;
        n -= digit[2] * 100;
        digit[3] = n / 10;
        n -= digit[3] * 10;
        for (i = 0; i < 4; i++) {
            h->val[t * 4 + i] = 100 - digit[i] * 10;
            if (i == 3) {
                h->val[t * 4 + i] -= n;
            }
        }
        for (i = 3; i > 0; i--) {
            cur = h->val[t * 4 + i];
            if (cur < 11) {
                h->val[t * 4 + i - 1] = h->val[t * 4 + i - 1] - (10 - cur);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108B0C_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_80108CFC_pump_pump_away(omObjData *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if ((D_80111758_pump_pump_away + i)->state == -1) {
            return;
        }
    }
    func_80108B0C_pump_pump_away(obj);
    switch (obj->work[0]) {
        case 0:
            if (D_801116F4_pump_pump_away < 4) {
                for (i = 0; i < 2; i++) {
                    (D_80111758_pump_pump_away + i)->alpha = 0;
                }
            } else {
                obj->work[0] = 1;
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                (D_80111758_pump_pump_away + i)->alpha += 25;
                if ((D_80111758_pump_pump_away + i)->alpha >= 255) {
                    (D_80111758_pump_pump_away + i)->alpha = 255;
                    obj->work[0] = 2;
                }
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                (D_80111758_pump_pump_away + i)->alpha = 255;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108CFC_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_80108E74_pump_pump_away(omObjData *obj) {
    PpDrawHookAdd hookAdd0 = (PpDrawHookAdd)(void (*)(void))func_8001AC8C_main;
    PpDrawHookAdd hookAdd1 = (PpDrawHookAdd)(void (*)(void))func_8001AC8C_main;
    PpHud *h = D_80111758_pump_pump_away;
    s32 i;

    D_8011175C_pump_pump_away = func_8000B838_main(0x2E0015);
    D_80111764_pump_pump_away = func_80055194_main((s16)D_8011175C_pump_pump_away);
    D_80111760_pump_pump_away = hookAdd0(0, func_80108560_pump_pump_away, 2);
    func_8001C8A8_main((s16)D_80111760_pump_pump_away, 1);
    D_80111788_pump_pump_away = 0;
    h->state = 0;
    h++;
    D_80111790_pump_pump_away = func_8000B838_main(0x2E0016);
    D_80111798_pump_pump_away = func_80055194_main((s16)D_80111790_pump_pump_away);
    D_80111794_pump_pump_away = hookAdd1(0, func_80108810_pump_pump_away, 2);
    func_8001C8A8_main((s16)D_80111794_pump_pump_away, 1);
    D_801117BC_pump_pump_away = 0;
    h->state = 0;
    obj->func = func_80108CFC_pump_pump_away;
    for (i = 0; i < 8; i++) {
        h->val[i] = 100;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108E74_pump_pump_away);
#endif

void func_80108FA8_pump_pump_away(void) {
    omAddObj(900, 2, 0, -1, func_80108E74_pump_pump_away)->work[0] = 0;
}

void func_80108FE0_pump_pump_away(omObjData *obj) {
    PpFx *fx = &D_80113400_pump_pump_away[obj->work[0]];
    PpTeam *t;
    PpTeam *t1;

    switch (fx->state) {
        case 0:
            break;
        case 1:
            func_8001C5B4_main(obj->model[0], obj->motion[0]);
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C258_main(obj->model[0], 4, 0);
            fx->state = 3;
            break;
        case 2:
            func_8001C5B4_main(obj->model[1], obj->motion[1]);
            func_8001C6A8_main(obj->model[1], 0.0f);
            func_8001C92C_main(obj->model[1], 0.5f);
            func_8001C814_main(obj->model[1], 1, 0);
            func_8001C258_main(obj->model[1], 4, 0);
            fx->state = 4;
            break;
        case 3:
            t = D_80111978_pump_pump_away;
            t1 = &t[1];
            if (t->dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
                obj->trans.y -= t->speed;
            } else {
                obj->trans.y -= t1->speed;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            fx->alpha -= 8;
            if (fx->alpha > 0) {
                func_8001F9E4_main(obj->model[0], (u8)fx->alpha);
            } else {
                func_8001C814_main(obj->model[0], 1, 1);
                func_8001C258_main(obj->model[0], 4, 4);
                fx->alpha = 255;
                fx->state = 0;
            }
            break;
        case 4:
            fx->alpha -= 5;
            if (fx->alpha > 0) {
                func_8001F9E4_main(obj->model[1], (u8)fx->alpha);
            } else {
                func_8001C814_main(obj->model[1], 1, 1);
                func_8001C258_main(obj->model[1], 4, 4);
                fx->alpha = 255;
                fx->state = 0;
            }
            break;
    }
}

void func_8010921C_pump_pump_away(omObjData *obj) {
    if (D_80113400_pump_pump_away[obj->work[0]].state == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
            break;
        case 4:
        case 7:
            func_80108FE0_pump_pump_away(obj);
            break;
    }
}

void func_80109280_pump_pump_away(omObjData *obj) {
    PpFx *fx;

    obj->model[0] = func_8000B108_main(0x2E0017, 0x289);
    obj->model[1] = func_8000B108_main(0x2E0019, 0x289);
    func_8000B460_main(obj, 0, 0x2E0018);
    func_8000B460_main(obj, 1, 0x2E001A);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xFF);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C6A8_main(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001FA68_main(obj->model[1]);
    func_8001F9E4_main(obj->model[1], 0xFF);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C6A8_main(obj->model[1], 0.0f);
    func_8001C814_main(obj->model[1], 1, 1);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = D_80111004_pump_pump_away[obj->work[0]].x;
    obj->trans.y = D_80111004_pump_pump_away[obj->work[0]].y;
    obj->trans.z = D_80111004_pump_pump_away[obj->work[0]].z;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->func = func_8010921C_pump_pump_away;
    fx = &D_80113400_pump_pump_away[obj->work[0]];
    fx->state = 0;
    fx->alpha = 255;
}

void func_80109470_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(750, 1, 2, -1, func_80109280_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_801094CC_pump_pump_away(omObjData *obj) {
    PpTeam *t;
    PpArc *a;
    s32 mdl;
    s32 mot;
    s16 se;

    a = &D_80113518_pump_pump_away;
    t = &D_80111978_pump_pump_away[D_8011351C_pump_pump_away];
    switch (a->state) {
        case 0:
            break;
        case 1:
            mdl = obj->model[0];
            mot = obj->motion[0];
            goto start;
        case 2:
            mdl = obj->model[0];
            mot = obj->motion[1];
        start:
            func_8001C5B4_main(mdl, mot);
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C258_main(obj->model[0], 4, 0);
            obj->trans.x = t->obj->trans.x;
            obj->trans.y = t->obj->trans.y + 200.0f;
            obj->trans.z = t->obj->trans.z;
            a->state = 3;
            break;
        case 3:
            if (HmfModelData[obj->model[0]].unk40 >= 16.0f && D_8011110A_pump_pump_away == 0) {
                se = HuAudFXPlay(0x363);
                if (t->obj->work[0] != 0) {
                    func_8004AE00_main(se, 0x60);
                } else {
                    func_8004AE00_main(se, 0x20);
                }
                D_8011110A_pump_pump_away = 1;
            }
            obj->trans.y = t->obj->trans.y + 200.0f;
            if (t->state == 2) {
                a->state = 4;
                break;
            }
            if (D_80111108_pump_pump_away != 0) {
                if (a->angle <= 175.0f) {
                    a->angle = 175.0f;
                    D_80111108_pump_pump_away ^= 1;
                } else {
                    a->angle = PP_WRAP(a->angle - 0.5);
                }
            } else {
                if (a->angle >= 185.0f) {
                    a->angle = 185.0f;
                    D_80111108_pump_pump_away ^= 1;
                } else {
                    a->angle = PP_WRAP(a->angle + 0.5);
                }
            }
            obj->rot.z = PP_WRAP(a->angle + 180.0f);
            t->obj->trans.x = obj->trans.x - sindf(a->angle) * 200.0f;
            t->obj->trans.y = cosdf(a->angle) * 200.0f + obj->trans.y;
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801094CC_pump_pump_away);
#endif

void func_801098E0_pump_pump_away(omObjData *obj) {
    PpArc *a = &D_80113518_pump_pump_away;
    PpTeam *t = &D_80111978_pump_pump_away[D_8011351C_pump_pump_away];

    if (a->state == 4) {
        func_8001C5B4_main(obj->model[0], obj->motion[1]);
        func_8001C6A8_main(obj->model[0], 0.0f);
        func_8001C814_main(obj->model[0], 1, 0);
        func_8001C258_main(obj->model[0], 4, 0);
        obj->trans.x = t->obj->trans.x;
        obj->trans.y = t->obj->trans.y + 200.0f;
        obj->trans.z = t->obj->trans.z;
        a->state = 5;
    }
}

void func_801099D4_pump_pump_away(omObjData *obj) {
    PpArc *a = &D_80113518_pump_pump_away;

    if (a->state == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            if (a->state < 4) {
                func_801094CC_pump_pump_away(obj);
                break;
            }
        case 8:
            func_801098E0_pump_pump_away(obj);
            break;
    }
}

void func_80109A50_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E001B, 0x1689);
    func_8000B460_main(obj, 0, 0x2E001C);
    func_8000B460_main(obj, 1, 0x2E001D);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C6A8_main(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->func = func_801099D4_pump_pump_away;
    D_80113518_pump_pump_away.state = 0;
    D_8011351C_pump_pump_away = -1;
    D_80113520_pump_pump_away = 180.0f;
    D_80113524_pump_pump_away = obj;
}

void func_80109B48_pump_pump_away(void) {
    omAddObj(740, 1, 2, -1, func_80109A50_pump_pump_away)->work[0] = 0;
}

void func_80109B80_pump_pump_away(omObjData *obj) {
    PpSplash *p;
    PpTeam *t;
    s32 i;

    for (i = 0; i < 20; i++) {
        p = &D_801117E0_pump_pump_away[i];
        if (p->state == 0) {
            t = D_80111978_pump_pump_away + obj->work[0];
            p->state = 1;
            p->obj->trans.x = obj->trans.x;
            p->obj->trans.y = obj->trans.y - 200.0f;
            p->obj->trans.z = obj->trans.z;
            p->vel = t->speed * 0.6;
            return;
        }
    }
}

void func_80109C30_pump_pump_away(omObjData *obj) {
    PpSplash *p = &D_801117E0_pump_pump_away[obj->work[0]];

    if (p->state == -1) {
        return;
    }
    switch (p->state) {
        case -1:
            break;
        case 1:
            func_8001C258_main(obj->model[0], 4, 0);
            p->state = 2;
            break;
        case 2:
            p->alpha -= 25;
            if (p->alpha > 0) {
                func_8001F9E4_main(obj->model[0], (u8)p->alpha);
                obj->trans.y -= p->vel * p->vel;
                obj->scale.x += 0.1;
                obj->scale.y += 0.1;
                obj->scale.z += 0.1;
            } else {
                func_8001C258_main(obj->model[0], 4, 4);
                p->alpha = 0xFF;
                p->vel = 0.0f;
                p->state = 0;
                obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
            }
            break;
    }
}

void func_80109D74_pump_pump_away(omObjData *obj) {
    PpSplash *p;

    obj->model[0] = func_8000B108_main(0x2E0013, 0x289);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xFF);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->func = func_80109C30_pump_pump_away;
    p = &D_801117E0_pump_pump_away[obj->work[0]];
    p->state = 0;
    p->alpha = 0xFF;
    p->vel = 0.0f;
    p->obj = obj;
}

void func_80109E3C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 14; i++) {
        omAddObj(760, 1, 0, -1, func_80109D74_pump_pump_away)->work[0] = i;
    }
}

void func_80109E98_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];
    s16 se;

    switch (t->unk0C) {
        case 0:
            func_8001C6A8_main(obj->model[0], 0.0f);
            break;
        case 1:
            func_8001C5B4_main(obj->model[0], obj->motion[0]);
            func_8001C92C_main(obj->model[0], D_80110F9C_pump_pump_away[t->unk10]);
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C814_main(obj->model[0], 4, 0);
            t->unk0C = 2;
            se = HuAudFXPlay(0x362);
            if (obj->work[0] != 0) {
                func_8004AE00_main(se, 0x60);
            } else {
                func_8004AE00_main(se, 0x20);
            }
            break;
        case 2:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2);
                func_8001C92C_main(obj->model[0], D_80110F9C_pump_pump_away[t->unk10]);
                func_8001C814_main(obj->model[0], 4, 4);
                t->unk0C = 3;
            }
            break;
        case 3:
            if (HmfModelData[obj->model[0]].unk40 <= 2.0f) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                t->unk0C = 0;
            }
            break;
    }
}

void func_8010A150_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];

    switch (t->unk0C) {
        case 2:
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2);
                func_8001C92C_main(obj->model[0], D_80110F9C_pump_pump_away[t->unk10]);
                func_8001C814_main(obj->model[0], 4, 4);
                t->unk0C = 3;
            }
            break;
        case 3:
            if (HmfModelData[obj->model[0]].unk40 <= 2.0f) {
                func_8001C5B4_main(obj->model[0], obj->motion[0]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C814_main(obj->model[0], 4, 0);
                func_8001C814_main(obj->model[0], 1, 1);
                t->unk0C = 0;
            }
            break;
        default:
            func_8001C5B4_main(obj->model[0], obj->motion[0]);
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C814_main(obj->model[0], 1, 1);
            t->unk0C = 3;
            break;
    }
}

// decomp-permuter
void func_8010A390_pump_pump_away(omObjData *obj)
{
  PpTeam *new_var;
  u32 w = obj->work[0];
  new_var = &D_80111978_pump_pump_away[w];
  D_80113400_pump_pump_away[w].state = (new_var->unk00 = 1);
  if (obj->work[0] == 0)
  {
    HuAudFXPlay(0x35F);
  }
}

void func_8010A3F0_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];

    if (t->dist - t->lastDist > 300.0f) {
        func_80109B80_pump_pump_away(obj);
        t->lastDist = t->dist;
    }
}

void func_8010A468_pump_pump_away(void) {
    PpMarker *m;
    PpSlot20 *a;
    PpSlot16 *b;
    PpSlot12 *c;
    s32 i;

    for (i = 0; i < 2; i++) {
        m = &D_80113418_pump_pump_away[i];
        m->stop = 1;
    }
    D_801135E0_pump_pump_away = 1;
    for (i = 0; i < 4; i++) {
        a = &D_80111920_pump_pump_away[i];
        a->unk04 = 1;
    }
    for (i = 0; i < 4; i++) {
        b = &D_801135E8_pump_pump_away[i];
        b->unk04 = 1;
    }
    for (i = 0; i < 6; i++) {
        c = &D_80111710_pump_pump_away[i];
        c->unk04 = 1;
    }
    for (i = 0; i < 6; i++) {
        c = &D_801119E8_pump_pump_away[i];
        c->unk04 = 1;
    }
}

#ifdef NON_MATCHING
void func_8010A570_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];
    s32 rem;
    s16 se;

    switch (t->phase) {
        case 0:
            if (t->dist < 2000.0f) {
                t->speed += 0.2;
                t->dist = t->speed * t->speed + t->dist;
            } else {
                t->dist = t->speed * t->speed + t->dist;
                t->phase = 1;
                t->wobble = (u8)(rand8() % 7) * 15;
            }
            func_8010A3F0_pump_pump_away(obj);
            break;
        case 1:
            t->speed = 10.6f;
            t->dist = t->dist + 112.36001f;
            if (--t->timer <= 0) {
                t->timer = 0;
                if (D_80111978_pump_pump_away[obj->work[0] ^ 1].timer == 0) {
                    t->phase = 3;
                } else {
                    t->phase = 2;
                }
            } else if (t->timer < 20) {
                obj->trans.y -= t->drift;
            } else {
                /* retail: the wrap macro draws a new random number for each use */
                t->wobble = PP_WRAP((u8)(rand8() % 10) + t->wobble);
                obj->trans.y = obj->trans.y + sindf(t->wobble) * 3.0;
                t->drift = (obj->trans.y - 200.0f) * 0.05;
            }
            func_8010A3F0_pump_pump_away(obj);
            break;
        case 2:
            if (t->speed > 0.0f) {
                t->speed -= 0.4;
                t->dist = t->speed * t->speed + t->dist;
                if (t->speed <= 0.0f) {
                    t->dist = (f32)(101 - (s32)t->dist % 100) + t->dist;
                }
                func_8010A3F0_pump_pump_away(obj);
                break;
            }
            if (D_80111110_pump_pump_away == 0 && t->speed < -1.2) {
                se = HuAudFXPlay(0x360);
                if (obj->work[0] != 0) {
                    func_8004AE00_main(se, 0x60);
                } else {
                    func_8004AE00_main(se, 0x20);
                }
                D_80111110_pump_pump_away = 1;
            }
            if (obj->trans.y < -200.0f) {
                t->state = 1;
            }
            if (obj->trans.y <= -3000.0f) {
                obj->trans.y = -3000.0f;
            } else {
                obj->trans.y -= t->speed * t->speed;
                t->speed -= 0.2;
            }
            break;
        case 3:
            if (t->speed > 0.0f) {
                t->speed -= 0.3;
                t->dist = t->speed * t->speed + t->dist;
                if (t->speed <= 0.0f) {
                    rem = (s32)t->dist % 100;
                    t->dist = (f32)(101 - rem) + t->dist;
                    func_8010A468_pump_pump_away();
                }
                func_8010A3F0_pump_pump_away(obj);
                break;
            }
            t->phase = 10;
            break;
        case 10:
            if (obj->trans.y < 0.0f) {
                t->state = 1;
            }
            if (D_8011110C_pump_pump_away <= 0) {
                if (D_8011110E_pump_pump_away == 0) {
                    D_80113518_pump_pump_away.state = 1;
                    D_8011351C_pump_pump_away = obj->work[0];
                    obj->trans.y -= t->speed * t->speed;
                    t->speed = -2.0f;
                    D_8011110E_pump_pump_away = 1;
                } else {
                    obj->trans.y -= t->speed * t->speed;
                    obj->rot.z = PP_WRAP(D_80113518_pump_pump_away.angle + 180.0f);
                }
            } else {
                D_8011110C_pump_pump_away--;
                obj->trans.y -= t->speed * t->speed;
                t->speed -= 0.2;
            }
            break;
    }
    if (D_80113530_pump_pump_away.state >= 2) {
        obj->trans.y = 2000.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010A570_pump_pump_away);
#endif

void func_8010AD24_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];

    if (t->timer == 0 && t->dist == 0.0f) {
        t->unk00 = 99;
        t->state = 2;
        return;
    }
    func_8010A570_pump_pump_away(obj);
}

#ifdef NON_MATCHING
void func_8010ADA0_pump_pump_away(omObjData *obj) {
    PpTeam *t = D_80111978_pump_pump_away + (obj->work[0] ^ 1);

    if (D_801116F4_pump_pump_away < 6) {
        obj->trans.y -= t->speed;
        if (obj->trans.y < -2800.0f) {
            obj->trans.y = -2800.0f;
        }
    } else if (D_80113530_pump_pump_away.state >= 2) {
        obj->trans.y = 200.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010ADA0_pump_pump_away);
#endif

void func_8010AE40_pump_pump_away(omObjData *obj) {
    switch (D_80111978_pump_pump_away[obj->work[0]].unk00) {
        case 0:
            func_8010A390_pump_pump_away(obj);
            break;
        case 1:
            func_8010AD24_pump_pump_away(obj);
            break;
        case 99:
            func_8010ADA0_pump_pump_away(obj);
            break;
    }
}

void func_8010AED4_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];

    if (t->unk00 == 99) {
        obj->trans.y = 200.0f;
        return;
    }
    if (t->phase == 2) {
        obj->trans.y = 950.0f;
        t->unk08 = 20;
    } else if (t->phase == 10) {
        obj->trans.y = 1000.0f;
        obj->rot.z = 0.0f;
        t->unk08 = 10;
    }
}

#ifdef NON_MATCHING
void func_8010AF70_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];
    PpPlayer *pl;
    s16 se;
    s32 i;

    switch (t->unk08) {
        case 10:
            obj->trans.y = 1010.0f;
            t->unk08 = 11;
            break;
        case 11:
            obj->rot.z = PP_WRAP(D_80113518_pump_pump_away.angle + 180.0f);
            obj->trans.y -= 10.0f;
            if (obj->trans.y <= 200.0f) {
                obj->trans.y = 200.0f;
                t->state = 2;
                t->unk08 = 12;
            }
            break;
        case 20:
            obj->trans.y = 1000.0f;
            obj->rot.z = 180.0f;
            t->unk08 = 21;
            break;
        case 21:
            obj->trans.y -= 50.0f;
            if (obj->trans.y <= 250.0f) {
                D_80113400_pump_pump_away[obj->work[0]].state = 2;
                t->unk08 = 22;
                se = HuAudFXPlay(0x361);
                if (obj->work[0] != 0) {
                    func_8004AE00_main(se, 0x60);
                } else {
                    func_8004AE00_main(se, 0x20);
                }
                for (i = 0; i < 4; i++) {
                    pl = &D_80113438_pump_pump_away[i];
                    if (pl->unk00 == -1) {
                        continue;
                    }
                    if (pl->obj->work[1] == obj->work[0]) {
                        if (pl->unk20 == 0) {
                            omVibrate((s16)pl->obj->work[0], 2, 2, 20);
                        }
                    } else {
                        if (pl->unk20 == 0) {
                            omVibrate((s16)pl->obj->work[0], 10, 0, 10);
                        }
                    }
                }
            }
            break;
        case 22:
            obj->trans.y -= 50.0f;
            if (obj->trans.y <= 100.0f) {
                obj->trans.y = 100.0f;
                t->state = 2;
                t->unk08 = 23;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010AF70_pump_pump_away);
#endif

void func_8010B274_pump_pump_away(omObjData *obj) {
    PpTeam *t = &D_80111978_pump_pump_away[obj->work[0]];

    if (t->unk00 == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
            func_8001C6A8_main(obj->model[0], 0.0f);
            func_8001C814_main(obj->model[0], 1, 1);
            break;
        case 2:
            func_80109E98_pump_pump_away(obj);
            break;
        case 3:
            func_8010A150_pump_pump_away(obj);
            break;
        case 4:
        case 5:
        case 6:
            func_8010AE40_pump_pump_away(obj);
            break;
        case 7:
            if (t->unk08 == 0) {
                func_8010AED4_pump_pump_away(obj);
            } else {
                func_8010AF70_pump_pump_away(obj);
            }
            break;
    }
}

void func_8010B370_pump_pump_away(omObjData *obj) {
    void *data;
    PpTeam *t;

    obj->model[0] = func_8000B108_main(0x2E000D, 0x4022A9);
    obj->motion[0] = func_8000B5BC_main(0x2E000E);
    func_8001C954_main(obj->model[0]);
    func_8001F974_main(obj->model[0], obj->motion[0]);
    func_8001C514_main(obj->motion[0]);
    if (obj->work[0] != 0) {
        data = DataRead(0x2E000F);
        obj->work[1] = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "m213_roket_r00_DEF");
        func_80032FC0_main((s16)obj->work[1], 1, 1);
        HuMemMemoryFreePerm(data);
        data = DataRead(0x2E0010);
        obj->work[2] = (s16)HmfAnimCreate(HmfModelData[obj->model[0]].hmf, data, 0, "m213_roket_r01_DEF");
        func_80032FC0_main((s16)obj->work[2], 1, 1);
        HuMemMemoryFreePerm(data);
        func_8001C448_main(obj->model[0]);
        func_8001C514_main(obj->model[0]);
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 0);
    obj->trans.x = D_80110EA0_pump_pump_away[obj->work[0]].x;
    obj->trans.y = D_80110EA0_pump_pump_away[obj->work[0]].y;
    obj->trans.z = D_80110EA0_pump_pump_away[obj->work[0]].z;
    obj->func = func_8010B274_pump_pump_away;
    t = &D_80111978_pump_pump_away[obj->work[0]];
    t->unk00 = 0;
    t->phase = 0;
    t->unk08 = 0;
    t->unk0C = 0;
    t->unk10 = 0;
    t->timer = 0;
    t->dist = 0;
    t->lastDist = 0;
    t->speed = 0;
    t->state = 0;
    t->wobble = 0;
    t->obj = obj;
}

void func_8010B5D4_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(700, 1, 1, -1, func_8010B370_pump_pump_away)->work[0] = i;
    }
}

void func_8010B630_pump_pump_away(omObjData *obj) {
    PpPlayer *pl = &D_80113438_pump_pump_away[obj->work[0]];
    s32 fire = 0;
    s32 n;

    if (pl->unk34 > 0) {
        pl->unk34--;
    } else {
        fire = 1;
        pl->unk34 = rand8() % pl->unk30 + 5;
    }
    if (fire != 0) {
        if (pl->unk18 != 0) {
            D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x8000;
        } else {
            D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x4000;
        }
        return;
    }
    n = pl->unk30 * 0.5;
    if (rand8() % n == 0 && pl->unk14 == 0.0f) {
        if (pl->unk18 != 0) {
            D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x8000;
        } else {
            D_800D5558_main[GwPlayer[obj->work[0]].pad] |= 0x4000;
        }
        pl->unk34 = rand8() % pl->unk30 + 5;
    }
}

void func_8010B898_pump_pump_away(omObjData *obj) {
    PpPlayer *pl = &D_80113438_pump_pump_away[obj->work[0]];
    f32 frame = HmfModelData[obj->model[0]].unk40;
    s16 se;
    s32 btn;

    if (pl->unk18 != 0) {
        if (frame <= 2.0f) {
            if (pl->unk10 >= 6) {
                pl->unk10 = pl->unk10 * 0.97;
            }
            pl->unk14 = 0.0f;
        }
        pl->unk10 = (s32)pl->unk14 + pl->unk10;
        if (D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x8000) {
            se = func_8004AC98_main(0x35D, (s16)obj->work[0]);
            if (obj->work[1] != 0) {
                func_8004AE00_main(se, 0x60);
            } else {
                func_8004AE00_main(se, 0x20);
            }
            if (frame < 2.0f) {
                pl->unk14 = (pl->unk2C - frame) * 0.17;
            } else {
                pl->unk14 = (pl->unk2C - frame) * 0.01;
            }
            pl->unk18 = 0;
            pl->unk28 = 1;
            pl->unk2C = frame;
        }
    } else {
        if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= frame) {
            if (pl->unk10 >= 6) {
                pl->unk10 = pl->unk10 * 0.97;
            }
            pl->unk14 = 0.0f;
        }
        pl->unk10 = (s32)pl->unk14 + pl->unk10;
        btn = D_800D5558_main[GwPlayer[obj->work[0]].pad];
        if (btn & 0x4000) {
            goto pumpDown;
        }
        if (btn & 0x2000) {
        pumpDown:
            se = func_8004AC98_main(0x35E, (s16)obj->work[0]);
            if (obj->work[1] != 0) {
                func_8004AE00_main(se, 0x60);
            } else {
                func_8004AE00_main(se, 0x20);
            }
            if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= frame) {
                pl->unk14 = (frame - pl->unk2C) * 0.17;
            } else {
                pl->unk14 = (frame - pl->unk2C) * 0.01;
            }
            pl->unk18 = 1;
            pl->unk28 = 1;
            pl->unk2C = frame;
        }
    }
}

void func_8010BC14_pump_pump_away(omObjData *obj) {
    PpPlayer *pl = &D_80113438_pump_pump_away[obj->work[0]];

    if (pl->unk28 != 0) {
        if (pl->unk18 != 0) {
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C814_main(obj->model[0], 4, 4);
        } else {
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C814_main(obj->model[0], 4, 0);
        }
        return;
    }
    if (pl->unk18 != 0) {
        if (HmfModelData[obj->model[0]].unk40 <= 2.0f) {
            func_8001C814_main(obj->model[0], 1, 1);
        }
    } else if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2 <= HmfModelData[obj->model[0]].unk40) {
        func_8001C814_main(obj->model[0], 1, 1);
    }
}

void func_8010BD80_pump_pump_away(omObjData *obj) {
    PpPlayer *pl = &D_80113438_pump_pump_away[obj->work[0]];

    switch (pl->state) {
        case 0:
            if (obj->rot.y >= 180.0f) {
                return;
            }
            if (obj->work[0] == 0 && D_80111708_pump_pump_away != 0) {
                D_80111708_pump_pump_away--;
            }
            if (D_80111708_pump_pump_away == 0) {
                func_8001C5B4_main(obj->model[0], obj->motion[3]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C814_main(obj->model[0], 2, 2);
                pl->state = 3;
            }
            break;
        case 3:
            obj->rot.y += 10.0f;
            if (obj->rot.y >= 180.0f) {
                obj->rot.y = 180.0f;
        case 1:
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 20, 2);
                pl->state = 0;
                pl->unk0C = 0;
            }
            break;
    }
}

void func_8010BF14_pump_pump_away(omObjData *obj) {
    PpPlayer *pl = &D_80113438_pump_pump_away[obj->work[0]];
    PpTeam *t;
    PpTeam *t1;

    if (D_80111978_pump_pump_away[obj->work[1]].unk00 == 99 && pl->unk0C == 0) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[4]].unk02, 0, 30, 2);
        pl->state = 4;
        pl->unk0C = 1;
    }
    t = D_80111978_pump_pump_away;
    t1 = &t[1];
    if (t->dist - D_80111978_pump_pump_away[1].dist > 0.0f) {
        obj->trans.y -= t->speed;
    } else {
        obj->trans.y -= t1->speed;
    }
    if (obj->trans.y < -3000.0f) {
        obj->trans.y = -3000.0f;
    }
}

void func_8010C060_pump_pump_away(omObjData *obj) {
    PpPlayer *pl = &D_80113438_pump_pump_away[obj->work[0]];
    s16 se;

    switch (pl->state) {
        case 0:
            obj->trans.y = D_80110E70_pump_pump_away[0].y;
            if (D_80111978_pump_pump_away[obj->work[1]].state == 2) {
                func_8001C5B4_main(obj->model[0], obj->motion[6]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C814_main(obj->model[0], 2, 0);
                func_8001C814_main(obj->model[0], 1, 0);
                pl->state = 6;
                se = func_8004ACE0_main(0x286, (s16)obj->work[0]);
                if (obj->work[1] != 0) {
                    func_8004AE00_main(se, 0x60);
                } else {
                    func_8004AE00_main(se, 0x20);
                }
            }
            break;
        case 4:
            if (obj->work[1] == 0) {
                obj->trans.y = D_80110E70_pump_pump_away[0].y;
            } else {
                obj->trans.y = D_80110E70_pump_pump_away[obj->work[1]].y;
            }
            break;
    }
}

void func_8010C1C8_pump_pump_away(omObjData *obj) {
    PpPlayer *pl = &D_80113438_pump_pump_away[obj->work[0]];
    f32 rot;

    obj->trans.y = D_80110E70_pump_pump_away[0].y;
    switch (pl->state) {
        case 0:
            if (pl->unk0C != 9) {
                func_8001C5B4_main(obj->model[0], obj->motion[3]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C814_main(obj->model[0], 2, 2);
                pl->state = 3;
            }
            break;
        case 3:
            obj->rot.y = PP_WRAP(obj->rot.y + 10.0f);
            rot = PP_WRAP(obj->rot.y + 180.0f);
            if (rot >= 180.0f) {
                obj->rot.y = 0.0f;
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 20, 2);
                pl->state = 0;
                pl->unk0C = 9;
            }
            break;
    }
}

void func_8010C3E0_pump_pump_away(omObjData *obj) {
    PpPlayer *pl = &D_80113438_pump_pump_away[obj->work[0]];
    s32 chr = D_800A178C_main[GwPlayer[obj->work[0]].chr][0];

    if (pl->state == 0) {
        func_8001C5B4_main(obj->model[0], obj->motion[5]);
        func_8001C6A8_main(obj->model[0], 0.0f);
        func_8001C814_main(obj->model[0], 1, 0);
        func_8001C814_main(obj->model[0], 2, 0);
        pl->state = 5;
        if (obj->work[0] != 0) {
            func_80045EF4_main(chr | 0x2F, 0x60);
        } else {
            func_80045EF4_main(chr | 0x2F, 0x20);
        }
    }
}

void func_8010C4D0_pump_pump_away(omObjData *obj) {
    PpPlayer *pl = &D_80113438_pump_pump_away[obj->work[0]];

    if (pl->unk00 == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
            func_80105D1C_pump_pump_away(obj->work[0]);
            if (pl->unk0C == 0) {
                func_8001C5B4_main(obj->model[0], obj->motion[1]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C814_main(obj->model[0], 1, 1);
                pl->state = 1;
                pl->unk0C = 0;
            }
            break;
        case 2:
            if (pl->unk20 != 0) {
                func_80105D1C_pump_pump_away(obj->work[0]);
                func_8010B630_pump_pump_away(obj);
            }
            func_8010B898_pump_pump_away(obj);
            func_8010BC14_pump_pump_away(obj);
            break;
        case 3:
            func_80105D1C_pump_pump_away(obj->work[0]);
            func_8010BD80_pump_pump_away(obj);
            if (GwPlayer[obj->work[0]].chr == 4) {
                obj->rot.x = 0.0f;
            }
            break;
        case 4:
        case 5:
            func_80105D1C_pump_pump_away(obj->work[0]);
            func_8010BF14_pump_pump_away(obj);
            break;
        case 6:
            if (D_80113530_pump_pump_away.state >= 2) {
        case 7:
                func_8010C060_pump_pump_away(obj);
            }
            break;
        case 8:
        case 9:
            func_8010C1C8_pump_pump_away(obj);
            break;
        case 10:
            func_8010C3E0_pump_pump_away(obj);
            break;
    }
    if (obj->work[2] != 0) {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 12.0f, obj->trans.z + 30.0f);
    } else {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y + 2.0, obj->trans.z + 30.0f);
    }
}

void func_8010C6E4_pump_pump_away(omObjData *obj) {
    u16 chr = GwPlayer[obj->work[0]].chr;
    PpPlayer *pl;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][1], 0x2B9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 20));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 19));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 47));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 55));
    func_8001C5B4_main(obj->model[0], obj->motion[1]);
    func_8001C814_main(obj->model[0], 2, 2);
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(HmfModelData[obj->model[1]].mtx, 0.0f, 5.0f, 0.0f);
    if (obj->work[1] == 0) {
        obj->trans.x = D_80110E70_pump_pump_away[D_80111700_pump_pump_away].x;
        obj->trans.y = D_80110E70_pump_pump_away[obj->work[1] + D_80111700_pump_pump_away].y;
        obj->trans.z = D_80110E70_pump_pump_away[obj->work[1] + D_80111700_pump_pump_away].z;
        obj->work[3] = obj->work[1] + D_80111700_pump_pump_away;
        D_80111700_pump_pump_away++;
    } else {
        obj->trans.x = D_80110E70_pump_pump_away[obj->work[1] + D_80111704_pump_pump_away + 1].x;
        obj->trans.y = D_80110E70_pump_pump_away[obj->work[1] + D_80111704_pump_pump_away + 1].y;
        obj->trans.z = D_80110E70_pump_pump_away[obj->work[1] + D_80111704_pump_pump_away + 1].z;
        obj->work[3] = obj->work[1] + D_80111704_pump_pump_away + 1;
        D_80111704_pump_pump_away++;
    }
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y + 2.0, obj->trans.z + 30.0f);
    switch (chr) {
        case 0:
            obj->trans.z -= 10.0f;
        case 2:
        case 7:
            obj->trans.z -= 20.0f;
            break;
        case 3:
            obj->trans.z -= 10.0f;
            break;
        case 4:
            obj->trans.z -= 20.0f;
            obj->rot.x = 350.0f;
            break;
        case 5:
            obj->trans.z -= 45.0f;
            break;
    }
    obj->func = func_8010C4D0_pump_pump_away;
    pl = &D_80113438_pump_pump_away[obj->work[0]];
    pl->unk00 = 0;
    pl->obj = obj;
    pl->state = 1;
    pl->unk0C = 0;
    pl->unk18 = 1;
    pl->unk10 = 0;
    pl->unk14 = 0;
    pl->unk1C = 0;
    pl->unk20 = GwPlayer[obj->work[0]].stat & 1;
    pl->unk24 = GwPlayer[obj->work[0]].cpu_difficulty;
    pl->unk28 = 0;
    pl->unk2C = 0;
    pl->unk34 = (u8)(rand8() % 5);
    switch (pl->unk24) {
        case 0:
            pl->unk30 = 20;
            break;
        case 1:
            pl->unk30 = 15;
            break;
        case 2:
            pl->unk30 = 10;
            break;
        default:
            pl->unk30 = 5;
            break;
    }
}

void func_8010CBF0_pump_pump_away(void) {
    omObjData *obj;
    s32 i;
    s32 player;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(300, 9, 60, -1, func_8010C6E4_pump_pump_away);
        switch (i) {
            case 1:
                player = 1;
                break;
            case 2:
                player = 2;
                break;
            case 3:
                player = 3;
                break;
            case 0:
            default:
                player = 0;
                break;
        }
        obj->work[0] = player;
        obj->work[1] = GwPlayer[player].group;
    }
}

// masked 6: retail shares the second branch's "return 0" and call blocks with the first; tried an
// if/else with one shared return 0 (masked 11) and a (u16) on either compare operand (masked 19).
#ifdef NON_MATCHING
s32 func_8010CCBC_pump_pump_away(void) {
    PpTeam *t = D_80111978_pump_pump_away;
    PpRecord *r = &D_801135B0_pump_pump_away;
    PpTeam *t1 = &t[1];
    u32 dist;

    if (t->dist > D_80111978_pump_pump_away[1].dist) {
        dist = (u16)(t->dist * 0.01);
        if (dist <= r->record) {
            return 0;
        }
        GWMgRecordSet(0, dist);
        return 1;
    }
    dist = t1->dist * 0.01;
    if ((u16)dist > r->record) {
        GWMgRecordSet(0, dist);
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010CCBC_pump_pump_away);
#endif

void func_8010CDF4_pump_pump_away(omObjData *obj) {
    PpRecord *r = &D_801135B0_pump_pump_away;
    s32 rec;

    if (D_801116F4_pump_pump_away < 9) {
        rec = (u16)GWMgRecordGet(0);
        D_801135CC_pump_pump_away = rec;
    } else {
        rec = (u16)GWMgRecordGet(0);
    }
    r->digit[0] = rec / 100;
    rec %= 100;
    if (r->digit[0] == 0) {
        r->digit[0] = -1;
    }
    r->digit[1] = rec / 10;
    rec %= 10;
    if (r->digit[1] == 0 && r->digit[0] == -1) {
        r->digit[1] = r->digit[0];
    }
    r->digit[2] = rec;
    r->unk18 = 12;
}

void func_8010CEE8_pump_pump_away(omObjData *obj) {
    PpRecord *r = &D_801135B0_pump_pump_away;
    s32 i;

    if (D_801116F4_pump_pump_away == 9 && func_8010CCBC_pump_pump_away() != 0) {
        func_8010CDF4_pump_pump_away(obj);
        if (r->dir == 0) {
            if (r->scale >= 13) {
                r->dir = 1;
            } else {
                r->scale += 2;
            }
        } else if (r->scale > 0) {
            r->scale -= 2;
        }
                HuSprScaleSet(r->grp, 0, r->scale / 12.0f + 1.0f, r->scale / 12.0f + 1.0f);
        func_80054904_main(r->grp, 0, r->scale / 4 + 32, r->scale / 4 + 22);
        func_80055024_main(r->grp, 0, r->spr, 0);
        func_800550F4_main(r->grp, 0, 0);
        func_80054FF8_main(r->grp, 0, (s16)r->digit[0]);
        HuSprAttrSet(r->grp, 0, 0x1000);
        HuSprAttrSet(r->grp, 0, 0);
        for (i = 1; i < 3; i++) {
            s16 j = i;
                        HuSprScaleSet(r->grp, j, r->scale / 12.0f + 1.0f, r->scale / 12.0f + 1.0f);
            func_80054904_main(r->grp, j, i * 12, 0);
            func_80055024_main(r->grp, j, r->spr, 0);
            func_800550F4_main(r->grp, j, 0);
            func_80054FF8_main(r->grp, j, (s16)r->digit[i]);
            HuSprAttrSet(r->grp, j, 0x1000);
            HuSprAttrSet(r->grp, j, 0);
        }
                func_8000BE5C_main(r->win, r->scale / 12.0f + 1.0f, r->scale / 12.0f + 1.0f);
        func_8000BBD4_main(r->win, r->scale * 4 + 78, r->scale / 4 + 22);
    }
}

#ifdef NON_MATCHING
void func_8010D1B8_pump_pump_away(omObjData *obj) {
    PpRecord *r = &D_801135B0_pump_pump_away;
    s32 i;

    func_8010CDF4_pump_pump_away(obj);
    D_801135B4_pump_pump_away = func_8000B838_main(0x32);
    D_801135B8_pump_pump_away = HuSprGrpCreate(4, 5);
    func_80054904_main(D_801135B8_pump_pump_away, 0, 32, 22);
    func_80055024_main(D_801135B8_pump_pump_away, 0, D_801135B4_pump_pump_away, 0);
    func_800550F4_main(D_801135B8_pump_pump_away, 0, 0);
    func_80054FF8_main(D_801135B8_pump_pump_away, 0, (s16)D_801135B0_pump_pump_away.digit[0]);
    HuSprAttrSet(D_801135B8_pump_pump_away, 0, 0x1000);
    HuSprAttrSet(D_801135B8_pump_pump_away, 0, 0);
    for (i = 1; i < 3; i++) {
        func_800554C4_main(r->grp, i, 0);
        func_80055024_main(r->grp, i, r->spr, 0);
        if (r->digit[i] != -1) {
            func_80054904_main(r->grp, i, i * 12, 0);
            func_80055024_main(r->grp, i, r->spr, 0);
            func_800550F4_main(r->grp, i, 0);
            func_80054FF8_main(r->grp, i, (s16)r->digit[i]);
            HuSprAttrSet(r->grp, i, 0x1000);
            HuSprAttrSet(r->grp, i, 0);
        } else {
            func_80054904_main(r->grp, i, i * 12, 0);
            func_80055024_main(r->grp, i, r->spr, 0);
            func_800550F4_main(r->grp, i, 0);
            func_80054FF8_main(r->grp, i, 0);
            HuSprAttrSet(r->grp, i, 0x1000);
            HuSprAttrSet(r->grp, i, 0x8000);
        }
    }
    r->file = func_8000B838_main(0x2E0023);
    r->win = InitEspriteSlot(r->file, 0, 0);
    func_8000BC48_main(r->win, 0x1000);
    func_8000BBD4_main(r->win, 78, 22);
    func_8000BB54_main(r->win);
    r->scale = 0;
    r->dir = 0;
    obj->func = func_8010CEE8_pump_pump_away;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D1B8_pump_pump_away);
#endif

void func_8010D458_pump_pump_away(void) {
    omAddObj(765, 1, 0, -1, func_8010D1B8_pump_pump_away);
}

// masked 11: retail converts dist to double in each arm (bc1tl with the cvt in its delay slot);
// tried an f64 dist (masked 11, j-shaped) and dist = t->dist before the test (masked 9, other regs).
#ifdef NON_MATCHING
void func_8010D48C_pump_pump_away(omObjData *obj) {
    PpRecLine *rl = &D_801135D8_pump_pump_away;
    PpTeam *t = D_80111978_pump_pump_away;
    PpTeam *t1 = &t[1];
    f32 dist;

    if (rl->state == -1) {
        return;
    }
    if (D_801135E0_pump_pump_away == 0) {
        if (t->dist > D_80111978_pump_pump_away[1].dist) {
            dist = t->dist;
        } else {
            dist = t1->dist;
        }
        if (rl->rec * 10 - dist * 0.1 + 400.0 < 2000.0) {
            func_8001C258_main(obj->model[0], 4, 0);
            obj->trans.y = rl->rec * 10 - dist * 0.1 + 350.0;
            if (obj->trans.y < -1000.0f) {
                func_8001C258_main(obj->model[0], 4, 4);
                rl->flag = 1;
            }
        }
    }
    if (D_80113530_pump_pump_away.state >= 2 && rl->state < 10) {
        func_8001C258_main(obj->model[0], 4, 4);
        rl->state = 10;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D48C_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_8010D620_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E001F, 0x1689);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 1000.0f;
    obj->trans.z = 550.0f;
    obj->func = func_8010D48C_pump_pump_away;
    D_801135D8_pump_pump_away.state = 0;
    D_801135DC_pump_pump_away = D_801135B0_pump_pump_away.record;
    D_801135E0_pump_pump_away = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D620_pump_pump_away);
#endif

void func_8010D6C0_pump_pump_away(void) {
    omAddObj(770, 1, 0, -1, func_8010D620_pump_pump_away);
}

#ifdef NON_MATCHING
void func_8010D6F4_pump_pump_away(omObjData *obj) {
    PpMarker *m = &D_80113418_pump_pump_away[obj->work[0]];
    PpTeam *t = D_80111978_pump_pump_away;
    PpTeam *t1 = &t[1];
    f32 dist;
    s32 n;
    s32 i;

    if (m->stop == 0) {
        if (t[1].dist < D_80111978_pump_pump_away[0].dist) {
            dist = D_80111978_pump_pump_away[0].dist;
        } else {
            dist = t1->dist;
        }
        i = dist * 0.01;
        switch (m->state) {
            case 0:
                n = i * 0.01 + 1.0;
                m->n = n;
                obj->trans.y = n * 1000 - dist * 0.1 + 480.0;
                m->state = 1;
                break;
            case 1:
                obj->trans.y = m->n * 1000 - dist * 0.1 + 480.0;
                if (obj->trans.y < -1000.0f) {
                    m->state = 0;
                }
                break;
        }
    }
    func_80034048_main((s16)obj->work[1], (s16)m->n);
    func_80034048_main((s16)obj->work[2], 0);
    func_80034048_main((s16)obj->work[3], 0);
    m->angle = PP_WRAP(m->angle + 6.0f);
    obj->trans.y = obj->trans.y + (f64)sindf(m->angle);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D6F4_pump_pump_away);
#endif

#ifdef NON_MATCHING
void func_8010D95C_pump_pump_away(omObjData *obj) {
    PpMarker *m = &D_80113418_pump_pump_away[obj->work[0]];
    PpTeam *t = D_80111978_pump_pump_away;
    PpTeam *t1 = &t[1];
    f32 dist;
    s32 n;
    s32 i;

    if (m->stop == 0) {
        if (t[1].dist < D_80111978_pump_pump_away[0].dist) {
            dist = D_80111978_pump_pump_away[0].dist;
        } else {
            dist = t1->dist;
        }
        i = dist * 0.01;
        switch (m->state) {
            case 0:
                n = i * 0.01 + 2.0;
                m->n = n;
                obj->trans.y = n * 1000 - dist * 0.1 + 480.0;
                m->state = 2;
                break;
            case 1:
                n = i * 0.01 + 1.0;
                m->n = n;
                obj->trans.y = n * 1000 - dist * 0.1 + 480.0;
                m->state = 2;
                break;
            case 2:
                obj->trans.y = m->n * 1000 - dist * 0.1 + 480.0;
                if (obj->trans.y < -1000.0f) {
                    m->state = 1;
                }
                break;
        }
    }
    func_80034048_main((s16)obj->work[1], (s16)m->n);
    func_80034048_main((s16)obj->work[2], 0);
    func_80034048_main((s16)obj->work[3], 0);
    m->angle = PP_WRAP(m->angle + 6.0f);
    obj->trans.y = obj->trans.y + (f64)sindf(m->angle);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D95C_pump_pump_away);
#endif

void func_8010DC68_pump_pump_away(omObjData *obj) {
    u32 n = obj->work[0];
    PpMarker *m = &D_80113418_pump_pump_away[n];

    if (m->state != -1) {
        if (n == 0) {
            func_8010D6F4_pump_pump_away(obj);
        } else {
            func_8010D95C_pump_pump_away(obj);
        }
        if (D_80113530_pump_pump_away.state >= 2 && m->state < 10) {
            func_8001C258_main(obj->model[0], 4, 4);
            func_8001C258_main(obj->model[1], 4, 4);
            m->state = 10;
        }
    }
}

void func_8010DD24_pump_pump_away(omObjData *obj) {
    void *data;
    PpMarker *m;
    s32 i;

    if (obj->work[0] == 0) {
        D_801116EA_pump_pump_away = obj->model[0] = func_8000B108_main(0xA0089, 0x289);
        obj->model[1] = func_8000B108_main(0x2E0020, 0x289);
        data = DataRead(0x2E0021);
        obj->work[1] = D_801116E8_pump_pump_away = HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "m213_plart2_DEF");
        obj->work[2] = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_801116E8_pump_pump_away, 0, "m213_plart1_DEF");
        obj->work[3] = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_801116E8_pump_pump_away, 0, "m213_plart0_DEF");
        HuMemMemoryFreePerm(data);
    } else {
        obj->model[0] = Hu3DModelLink(D_801116EA_pump_pump_away);
        obj->model[1] = func_8000B108_main(0x2E0020, 0x289);
        obj->work[1] = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_801116E8_pump_pump_away, 0, "m213_plart2_DEF");
        obj->work[2] = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_801116E8_pump_pump_away, 0, "m213_plart1_DEF");
        obj->work[3] = func_80032694_main(HmfModelData[obj->model[1]].hmf, D_801116E8_pump_pump_away, 0, "m213_plart0_DEF");
    }
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    for (i = 1; i < 4; i++) {
        func_80034048_main(obj->work[i], 0);
        func_80032FC0_main(obj->work[i], 1, 1);
    }
    func_8001C814_main(obj->model[0], 2, 2);
    obj->trans.x = 43.5f;
    obj->trans.y = 1000.0f;
    obj->trans.z = -17.5f;
    obj->rot.y = 345.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, obj->rot.y, 0.0f);
    obj->func = func_8010DC68_pump_pump_away;
    m = &D_80113418_pump_pump_away[obj->work[0]];
    m->state = 0;
    m->n = 0;
    m->angle = 0;
    m->stop = 0;
}

void func_8010E098_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(780, 2, 1, -1, func_8010DD24_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_8010E0F4_pump_pump_away(omObjData *obj) {
    PpSlot20 *p = &D_80111920_pump_pump_away[obj->work[0]];
    PpTeam *t = D_80111978_pump_pump_away;
    PpTeam *t1 = &t[1];
    f32 dist;

    if (p->unk04 == 0) {
        if (t[1].dist < D_80111978_pump_pump_away[0].dist) {
            dist = D_80111978_pump_pump_away[0].dist;
        } else {
            dist = t1->dist;
        }
        if (D_8011101C_pump_pump_away[obj->work[0]] - dist * 0.1 + 400.0 < 1000.0) {
            func_8001C258_main(obj->model[0], 4, 0);
            obj->trans.y = D_8011101C_pump_pump_away[obj->work[0]] - dist * 0.1 + 400.0;
            if (obj->trans.y < -1000.0f) {
                func_8001C258_main(obj->model[0], 4, 4);
                p->unk04 = 1;
            }
        }
    }
    obj->rot.y = p->dir * 180 + 90;
    if (p->dir == 0) {
        obj->trans.x = obj->trans.x + p->speed;
    } else {
        obj->trans.x = obj->trans.x - p->speed;
    }
    if ((obj->trans.x < 0.0f ? -obj->trans.x : obj->trans.x) >= 700.0f) {
        if (p->dir == 0) {
            obj->trans.x = 700.0f;
        } else {
            obj->trans.x = -700.0f;
        }
        p->dir ^= 1;
        p->speed = (u8)(rand8() % 6) + 4;
    }
    p->phase = PP_WRAP(p->phase + 6.0f);
    obj->trans.y = obj->trans.y + 2.0 * sindf(p->phase);
    if (D_80113530_pump_pump_away.state >= 2 && p->state < 10) {
        func_8001C258_main(obj->model[0], 4, 4);
        p->state = 10;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E0F4_pump_pump_away);
#endif

void func_8010E45C_pump_pump_away(omObjData *obj) {
    PpSlot20 *p;

    if (D_801116EC_pump_pump_away == 0) {
        D_801116EC_pump_pump_away = obj->model[0] = func_8000B108_main(0x2E0011, 0x299);
    } else {
        obj->model[0] = Hu3DModelLink(D_801116EC_pump_pump_away);
    }
    func_8001C814_main(obj->model[0], 2, 2);
    func_8001C258_main(obj->model[0], 4, 4);
    if (rand8() & 1) {
        obj->trans.x = (u8)(rand8() % 10) * 50;
    } else {
        obj->trans.x = -((u8)(rand8() % 10) * 50);
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = -150.0f;
    obj->func = func_8010E0F4_pump_pump_away;
    p = &D_80111920_pump_pump_away[obj->work[0]];
    p->state = 0;
    p->unk04 = 0;
    p->dir = rand8() & 1;
    p->speed = (u8)(rand8() % 6) + 4;
    p->phase = rand8();
}

void func_8010E65C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(761, 1, 1, -1, func_8010E45C_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_8010E6B8_pump_pump_away(omObjData *obj) {
    PpSlot16 *p = &D_801135E8_pump_pump_away[obj->work[0]];
    PpTeam *t = D_80111978_pump_pump_away;
    PpTeam *t1 = &t[1];
    f32 dist;

    if (p->state != -1) {
        if (p->unk04 == 0) {
            if (t[1].dist < D_80111978_pump_pump_away[0].dist) {
                dist = D_80111978_pump_pump_away[0].dist;
            } else {
                dist = t1->dist;
            }
            if (D_8011102C_pump_pump_away[obj->work[0]] - dist * 0.1 + 400.0 < 1000.0) {
                func_8001C258_main(obj->model[0], 4, 0);
                obj->trans.y = D_8011102C_pump_pump_away[obj->work[0]] - dist * 0.1 + 400.0;
                if (obj->trans.y < -1000.0f) {
                    func_8001C258_main(obj->model[0], 4, 4);
                    p->unk04 = 1;
                }
            }
        }
        obj->rot.y = p->dir * 180 + 90;
        if (p->dir == 0) {
            obj->trans.x = obj->trans.x + p->speed;
        } else {
            obj->trans.x = obj->trans.x - p->speed;
        }
        if ((obj->trans.x < 0.0f ? -obj->trans.x : obj->trans.x) >= 700.0f) {
            if (p->dir == 0) {
                obj->trans.x = 700.0f;
            } else {
                obj->trans.x = -700.0f;
            }
            p->speed = (u8)(rand8() % 10) + 10;
            p->dir ^= 1;
        }
        if (D_80113530_pump_pump_away.state >= 2 && p->state < 10) {
            func_8001C258_main(obj->model[0], 4, 4);
            p->state = 10;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E6B8_pump_pump_away);
#endif

void func_8010E98C_pump_pump_away(omObjData *obj) {
    PpSlot16 *p;

    if (D_801116EE_pump_pump_away == 0) {
        D_801116EE_pump_pump_away = obj->model[0] = func_8000B108_main(0xA0062, 0x299);
    } else {
        obj->model[0] = Hu3DModelLink(D_801116EE_pump_pump_away);
    }
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    if (rand8() & 1) {
        obj->trans.x = (u8)(rand8() % 10) * 50;
    } else {
        obj->trans.x = -((u8)(rand8() % 10) * 50);
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = -150.0f;
    obj->func = func_8010E6B8_pump_pump_away;
    p = &D_801135E8_pump_pump_away[obj->work[0]];
    p->state = 0;
    p->unk04 = 0;
    p->dir = rand8() & 1;
    p->speed = (u8)(rand8() % 5) + 10;
}

void func_8010EB68_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(762, 1, 0, -1, func_8010E98C_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_8010EBC4_pump_pump_away(omObjData *obj) {
    PpSlot12 *p = &D_80111710_pump_pump_away[obj->work[0]];
    PpTeam *t = D_80111978_pump_pump_away;
    PpTeam *t1 = &t[1];
    f32 dist;

    if (p->state != -1) {
        if (p->unk04 == 0) {
            if (t[1].dist < D_80111978_pump_pump_away[0].dist) {
                dist = D_80111978_pump_pump_away[0].dist;
            } else {
                dist = t1->dist;
            }
            switch (p->state) {
                case 0:
                    if (D_8011103C_pump_pump_away[D_80111970_pump_pump_away] - dist * 0.1 + 400.0 < 1000.0) {
                        func_8001C258_main(obj->model[0], 4, 0);
                        /* Retail adds the scroll here; case 1 corrects the height on the next frame. */
                        obj->trans.y = D_8011103C_pump_pump_away[obj->work[0]] + dist * 0.1 + 400.0;
                        p->state = 1;
                        obj->work[1] = D_80111970_pump_pump_away;
                        D_80111970_pump_pump_away++;
                    }
                    break;
                case 1:
                    obj->trans.y = D_8011103C_pump_pump_away[obj->work[1]] - dist * 0.1 + 400.0;
                    if (obj->trans.y < -500.0f) {
                        func_8001C258_main(obj->model[0], 4, 4);
                        if (obj->work[0] & 1) {
                            obj->trans.x = rand16() % 501 + 100;
                        } else {
                            obj->trans.x = -(rand16() % 501) - 100;
                        }
                        p->state = 0;
                    }
                    break;
            }
        }
        p->angle = PP_WRAP(p->angle + 3.0f);
        obj->rot.z = PP_WRAP(sindf(p->angle) * 15.0f + 0.0f);
        if (D_80113530_pump_pump_away.state >= 2 && p->state < 10) {
            func_8001C258_main(obj->model[0], 4, 4);
            p->state = 10;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010EBC4_pump_pump_away);
#endif

void func_8010F024_pump_pump_away(omObjData *obj) {
    PpSlot12 *p;

    if (D_801116F0_pump_pump_away == 0) {
        D_801116F0_pump_pump_away = obj->model[0] = func_8000B108_main(0x2E0022, 0x289);
    } else {
        obj->model[0] = Hu3DModelLink(D_801116F0_pump_pump_away);
    }
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    if (obj->work[0] & 1) {
        obj->trans.x = rand16() % 501 + 100;
    } else {
        obj->trans.x = -(rand16() % 501) - 100;
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = -150.0f;
    obj->func = func_8010EBC4_pump_pump_away;
    p = &D_80111710_pump_pump_away[obj->work[0]];
    p->state = 0;
    p->unk04 = 0;
    p->angle = rand8();
}

void func_8010F20C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        omAddObj(762, 1, 0, -1, func_8010F024_pump_pump_away)->work[0] = i;
    }
}

#ifdef NON_MATCHING
void func_8010F268_pump_pump_away(omObjData *obj) {
    PpSlot12 *p = &D_801119E8_pump_pump_away[obj->work[0]];
    PpTeam *t = D_80111978_pump_pump_away;
    PpTeam *t1 = &t[1];
    f32 dist;
    s32 n;

    if (p->state != -1) {
        if (t[1].dist < D_80111978_pump_pump_away[0].dist) {
            dist = D_80111978_pump_pump_away[0].dist;
        } else {
            dist = t1->dist;
        }
        n = dist * 0.01;
        if (p->unk04 == 0) {
            switch (p->state) {
                case 0:
                    if (D_8011109C_pump_pump_away[D_801133F8_pump_pump_away] - dist * 0.1 + 400.0 < 1000.0) {
                        func_8001C258_main(obj->model[0], 4, 0);
                        /* Retail adds the scroll here; case 1 corrects the height on the next frame. */
                        obj->trans.y = D_8011109C_pump_pump_away[obj->work[0]] + dist * 0.1 + 400.0;
                        p->state = 1;
                        obj->work[1] = D_801133F8_pump_pump_away;
                        D_801133F8_pump_pump_away++;
                    }
                    break;
                case 1:
                    obj->trans.y = D_8011109C_pump_pump_away[obj->work[1]] - dist * 0.1 + 400.0;
                    if (obj->trans.y < -1000.0f) {
                        func_8001C258_main(obj->model[0], 4, 4);
                        if (obj->work[0] & 1) {
                            obj->trans.x = rand16() % 301 + 100;
                        } else {
                            obj->trans.x = -(rand16() % 301) - 100;
                        }
                        obj->trans.z = (rand8() & 1) ? -500.0f : 500.0f;
                        p->state = 0;
                    }
                    break;
            }
        }
        p->angle = PP_WRAP(p->angle + 6.0f);
        obj->scale.y = obj->scale.z = obj->scale.x = sindf(p->angle) * 0.03 + 0.5;
        if ((D_80113530_pump_pump_away.state >= 2 && p->state < 10) || (n >= 351 && p->state == 0)) {
            func_8001C258_main(obj->model[0], 4, 4);
            p->state = 10;
            p->unk04 = 1;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F268_pump_pump_away);
#endif

void func_8010F688_pump_pump_away(omObjData *obj) {
    PpSlot12 *p;

    if (D_801116F2_pump_pump_away == 0) {
        D_801116F2_pump_pump_away = obj->model[0] = func_8000B108_main(0x230005, 0x299);
    } else {
        obj->model[0] = Hu3DModelLink(D_801116F2_pump_pump_away);
    }
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    if (obj->work[0] & 1) {
        obj->trans.x = rand16() % 301 + 100;
    } else {
        obj->trans.x = -(rand16() % 301) - 100;
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = (rand8() & 1) ? -500.0f : 500.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.5f;
    obj->func = func_8010F268_pump_pump_away;
    p = &D_801119E8_pump_pump_away[obj->work[0]];
    p->state = 0;
    p->unk04 = 0;
    p->angle = rand8();
}

void func_8010F8A4_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        omAddObj(763, 1, 0, -1, func_8010F688_pump_pump_away)->work[0] = i;
    }
}

void func_8010F900_pump_pump_away(omObjData *obj) {
    Vec from;
    Vec to;
    Vec out;
    u32 i;

    if (D_80111114_pump_pump_away == 0) {
        D_80111114_pump_pump_away = 1;
        to.x = 650.0f;
        to.y = 0;
        to.z = 2600.0f;
        from.x = 65.0f;
        from.y = 0;
        from.z = -500.0f;
        func_80105EE4_pump_pump_away(&from, &to, &out);
        for (i = 0; i < 1; i++) {
            CZoomM[i] = out.x;
            CRotM[i].x = 360.0f - out.z;
            CRotM[i].y = 0;
            CRotM[i].z = 0;
            CenterM[i].x = 0.0f;
            CenterM[i].y = from.x;
            CenterM[i].z = from.z;
        }
    }
}

void func_8010FA20_pump_pump_away(omObjData *obj) {
}

void func_8010FA28_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away > 0) {
        D_801116FC_pump_pump_away--;
        return;
    }
    D_801116F8_pump_pump_away = 1;
    obj->func = func_8010FA20_pump_pump_away;
}

void func_8010FA64_pump_pump_away(omObjData *obj) {
    if (GMesStatGet() & 2) {
        D_801116FC_pump_pump_away = 0x14;
        obj->func = func_8010FA28_pump_pump_away;
    }
}

s32 func_8010FAA8_pump_pump_away(void) {
    PpTeam *t = D_80111978_pump_pump_away;
    PpRecord *r = &D_801135B0_pump_pump_away;
    PpTeam *t1 = &t[1];
    u32 n;

    if (t->dist > D_80111978_pump_pump_away[1].dist) {
        n = (u16)(t->dist * 0.01);
    } else {
        n = (u16)(t1->dist * 0.01);
    }
    return n > r->record;
}

void func_8010FB70_pump_pump_away(omObjData *obj) {
    u8 chr[2];
    PpPlayer *p;
    s32 team;
    s32 i;
    s32 n;

    team = 1;
    if (D_80111990_pump_pump_away > D_801119C4_pump_pump_away) {
        team = 0;
    }
    for (i = 0, n = 0; i < 4; i++) {
        p = &D_80113438_pump_pump_away[i];
        if (p->obj->work[1] == team) {
            chr[n++] = GwPlayer[p->obj->work[0]].chr;
            GwPlayer[p->obj->work[0]].bonusCoin = 10;
        }
    }
    GMesCreate(0x1E, chr[0], chr[1]);
    HuAudSeqPlay(func_8010FAA8_pump_pump_away() == 0 ? 0x66 : 0x6A);
}

void func_8010FC64_pump_pump_away(omObjData *obj) {
    PpTeam *t = D_80111978_pump_pump_away;
    PpTeam *t1 = &t[1];

    if (D_801116FC_pump_pump_away > 0) {
        D_801116FC_pump_pump_away--;
        return;
    }
    if (t->dist == t1->dist) {
        GMesCreate(0x20);
        HuAudSeqPlay(0x6C);
        D_801116FC_pump_pump_away = 0x90;
    } else {
        func_8010FB70_pump_pump_away(obj);
    }
    obj->func = func_8010FA64_pump_pump_away;
}

void func_8010FCF8_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away > 0) {
        D_801116FC_pump_pump_away--;
        return;
    }
    D_801116F8_pump_pump_away = 1;
    obj->func = func_8010FC64_pump_pump_away;
}

void func_8010FD34_pump_pump_away(omObjData *obj) {
    if (GMesStatGet() == 0) {
        if (D_801116FC_pump_pump_away > 0) {
            D_801116FC_pump_pump_away -= 1;
            return;
        }
        D_801116F8_pump_pump_away = 1;
        obj->func = func_8010FC64_pump_pump_away;
    }
}

void func_8010FD94_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away > 0) {
        D_801116FC_pump_pump_away -= 1;
        return;
    }
    if (func_8010FAA8_pump_pump_away() != 0) {
        GMesCreate(0x1B);
        D_801116F8_pump_pump_away = 1;
        D_801116FC_pump_pump_away = 0xF;
        obj->func = func_8010FD34_pump_pump_away;
        return;
    }
    D_801116FC_pump_pump_away = 0;
    D_801116F8_pump_pump_away = 2;
    obj->func = func_8010FC64_pump_pump_away;
}

void func_8010FE2C_pump_pump_away(omObjData *obj) {
    if (GMesStatGet() == 0) {
        D_801116FC_pump_pump_away = 0xF;
        obj->func = func_8010FD94_pump_pump_away;
    }
}

void func_8010FE6C_pump_pump_away(omObjData *obj) {
    GMesCreate(0x10);
    D_801116FC_pump_pump_away = 0x4B;
    HuAudSeqFadeOut(0x78);
    obj->func = func_8010FE2C_pump_pump_away;
}

void func_8010FEB4_pump_pump_away(omObjData *obj) {
    PpTeam *t = D_80111978_pump_pump_away;

    if (t->state == 2 && D_80111978_pump_pump_away[1].state == 2) {
        D_801116F8_pump_pump_away = 1;
        obj->func = func_8010FE6C_pump_pump_away;
    }
}

void func_8010FEF8_pump_pump_away(omObjData *obj) {
    if (D_80113530_pump_pump_away.state == -1) {
        D_801116F8_pump_pump_away = 1;
        obj->func = func_8010FEB4_pump_pump_away;
    }
}

void func_8010FF28_pump_pump_away(omObjData *obj) {
    PpTeam *t = D_80111978_pump_pump_away;

    if (t->state != 0 && D_80111978_pump_pump_away[1].state != 0) {
        D_80113530_pump_pump_away.state = 1;
        D_801116F8_pump_pump_away = 1;
        obj->func = func_8010FEF8_pump_pump_away;
    }
}

void func_8010FF70_pump_pump_away(omObjData *obj) {
    PpTeam *t = D_80111978_pump_pump_away;
    PpTeam *t1 = &t[1];

    if (D_801116FC_pump_pump_away != 0) {
        D_801116FC_pump_pump_away--;
        return;
    }
    if (t->timer == 0 && t1->timer == 0) {
        if (t->dist == 0.0f && t1->dist == 0.0f) {
            D_801116F8_pump_pump_away = 4;
            obj->func = func_8010FE6C_pump_pump_away;
            return;
        }
        if (t->phase == 10 || t1->phase == 10) {
            D_801116F8_pump_pump_away = 1;
            obj->func = func_8010FF28_pump_pump_away;
        }
    }
}

void func_80110034_pump_pump_away(omObjData *obj) {
    PpPlayer *p;
    s32 i;

    D_801116FC_pump_pump_away = 45;
    D_801116F8_pump_pump_away = 1;
    obj->func = func_8010FF70_pump_pump_away;
    if (D_801119E4_pump_pump_away != 0) {
        for (i = 0; i < 4; i++) {
            p = &D_80113438_pump_pump_away[i];
            if (p->unk00 != -1 && p->unk20 == 0) {
                omVibrate(p->obj->work[0], 2, 2, 20);
            }
        }
    }
}

// masked 15: the loop's sum and the two zero stores take other registers/bases (retail: beqzl with
// t1's store in the slot); chained and D_80111978_pump_pump_away[n] spellings of the stores do not help.
#ifdef NON_MATCHING
void func_801100F0_pump_pump_away(void) {
    PpPlayer *p;
    PpTeam *t;
    PpTeam *t1;
    s32 i;

    for (i = 0; i < 4; i++) {
        p = &D_80113438_pump_pump_away[i];
        t = &D_80111978_pump_pump_away[p->obj->work[1]];
        t->timer += p->unk10;
    }
    t = D_80111978_pump_pump_away;
    t1 = &t[1];
    if (t->timer == D_80111978_pump_pump_away[1].timer) {
        if (t->timer == 0) {
            t1->timer = 0;
            t->timer = 0;
        } else if (rand8() & 1) {
            t->timer += 40;
        } else {
            t1->timer += 40;
        }
    } else if ((t->timer - t1->timer >= 0 ? t->timer - t1->timer : t1->timer - t->timer) < 40) {
        if (t1->timer < t->timer) {
            t->timer = t1->timer + 40;
        } else {
            t1->timer = t->timer + 40;
        }
    }
    if (t->timer != 0 && t1->timer != 0) {
        D_801119E4_pump_pump_away = 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801100F0_pump_pump_away);
#endif

void func_80110260_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away != 0) {
        D_801116FC_pump_pump_away -= 1;
        return;
    }
    obj->func = func_80110034_pump_pump_away;
}

void func_80110290_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away != 0) {
        D_801116FC_pump_pump_away -= 1;
        return;
    }
    D_801116FC_pump_pump_away = 0;
    func_801100F0_pump_pump_away();
    obj->func = func_80110260_pump_pump_away;
}

void func_801102E4_pump_pump_away(omObjData *obj) {
    s32 temp_v1;
    temp_v1 = D_801116FC_pump_pump_away;
    if (temp_v1 != 0) {
        D_801116FC_pump_pump_away = temp_v1 - 1;
        func_8003F578_main((s16) ((temp_v1 + 0x1C) / 30));
        return;
    }
    func_8003F5C0_main();
    D_801116FC_pump_pump_away = 0x5A;
    obj->func = func_80110290_pump_pump_away;
    D_801116F8_pump_pump_away = 1;
    D_800D6A58_main = 1;
}

void func_8011038C_pump_pump_away(omObjData *obj) {
    GMesCreate(0x1A, 10, 160, 28);
    D_801116FC_pump_pump_away = 301;
    obj->func = func_801102E4_pump_pump_away;
}

void func_801103D8_pump_pump_away(omObjData *obj) {
    if (++D_80111118_pump_pump_away == 33) {
        HuAudSeqPlay(46);
    }
    if (GMesStatGet() == 0 || GMesStatGet() & 2) {
        obj->func = func_8011038C_pump_pump_away;
        D_801116F8_pump_pump_away = 1;
    }
}

void func_80110458_pump_pump_away(omObjData *obj) {
    GMesCreate(5);
    obj->func = func_801103D8_pump_pump_away;
    D_801116F8_pump_pump_away = 1;
}

void func_80110498_pump_pump_away(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_801104BC_pump_pump_away(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_80110498_pump_pump_away;
    }
}

void func_801104F4_pump_pump_away(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_801104BC_pump_pump_away;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8011054C_pump_pump_away(void) {
    D_801116F4_pump_pump_away += D_801116F8_pump_pump_away;
    D_801116F8_pump_pump_away = 0;
}

void func_80110574_pump_pump_away(omObjData *obj) {
    func_8011054C_pump_pump_away();
    switch (D_801116F4_pump_pump_away) {
        case 0:
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
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            WipeCreateOut(0, 20);
            obj->func = func_801104BC_pump_pump_away;
            break;
    }
}

void func_801105D8_pump_pump_away(void) {
    PpPlayer *p;
    s32 i;

    for (i = 0; i < 4; i++) {
        p = &D_80113438_pump_pump_away[i];
        p->unk00 = -1;
        p->obj = NULL;
        p->state = 0;
        p->unk0C = 0;
        p->unk10 = 0;
        p->unk14 = 0.0f;
        p->unk1C = 0;
        p->unk20 = 0;
        p->unk24 = 0;
        p->unk30 = 0;
    }
}

void func_80110638_pump_pump_away(void) {
    PpPump *p;
    s32 i;

    for (i = 0; i < 2; i++) {
        p = &D_80113570_pump_pump_away[i];
        p->state = -1;
    }
}

void func_8011066C_pump_pump_away(void) {
    PpTank *p;
    s32 i;

    for (i = 0; i < 2; i++) {
        p = &D_801117C0_pump_pump_away[i];
        p->unk00 = -1;
        p->state = 0;
        p->level = 0;
        p->count = 0;
    }
}

void func_801106AC_pump_pump_away(void) {
    PpTeam *t;
    s32 i;

    for (i = 0; i < 2; i++) {
        t = &D_80111978_pump_pump_away[i];
        t->unk00 = -1;
        t->phase = 0;
        t->unk08 = 0;
        t->unk0C = 0;
        t->unk10 = 0;
        t->timer = 0;
        t->dist = 0.0f;
        t->lastDist = 0.0f;
        t->speed = 0.0f;
        t->state = 0;
        t->wobble = 0.0f;
    }
}

void func_80110718_pump_pump_away(void) {
    PpHud *h;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        h = &D_80111758_pump_pump_away[i];
        h->state = -1;
        h->grp = 0;
        h->spr = NULL;
        h->draw = 0;
        h->alpha = 0;
        for (j = 0; j < 8; j++) {
            h->val[j] = 0;
        }
    }
}

void func_8011078C_pump_pump_away(void) {
    PpFx *p;
    s32 i;

    for (i = 0; i < 2; i++) {
        p = &D_80113400_pump_pump_away[i];
        p->state = -1;
        p->alpha = 0;
    }
}

void func_801107C4_pump_pump_away(void) {
    D_80113518_pump_pump_away.state = -1;
    D_8011351C_pump_pump_away = -1;
    D_80113520_pump_pump_away = 0.0f;
}

void func_801107E4_pump_pump_away(void) {
    PpSplash *p;
    s32 i;

    for (i = 0; i < 0x14; i++) {
        p = &D_801117E0_pump_pump_away[i];
        p->state = -1;
        p->alpha = 0;
        p->vel = 0.0f;
        p->obj = NULL;
    }
}

void func_80110824_pump_pump_away(void) {
    PpMarker *p;
    s32 i;

    for (i = 0; i < 2; i++) {
        p = &D_80113418_pump_pump_away[i];
        p->state = -1;
        p->n = 0;
        p->angle = 0.0f;
        p->stop = 0;
    }
    D_801116EA_pump_pump_away = 0;
}

void func_80110868_pump_pump_away(void) {
    D_801135D8_pump_pump_away.state = -1;
    D_801135DC_pump_pump_away = 0;
    D_801135E0_pump_pump_away = 0;
}

void func_80110888_pump_pump_away(void) {
    PpSlot20 *p;
    s32 i;

    for (i = 0; i < 4; i++) {
        p = &D_80111920_pump_pump_away[i];
        p->state = -1;
        p->unk04 = 0;
        p->dir = 0;
        p->speed = 0;
        p->phase = 0;
    }
    D_801116EC_pump_pump_away = 0;
}

void func_801108D8_pump_pump_away(void) {
    PpSlot16 *p;
    s32 i;

    for (i = 0; i < 4; i++) {
        p = &D_801135E8_pump_pump_away[i];
        p->state = -1;
        p->unk04 = 0;
        p->dir = 0;
        p->speed = 0;
    }
    D_801116EE_pump_pump_away = 0;
}

void func_8011091C_pump_pump_away(void) {
    PpSlot12 *p;
    s32 i;

    for (i = 0; i < 6; i++) {
        p = &D_80111710_pump_pump_away[i];
        p->state = -1;
        p->unk04 = 0;
        p->angle = 1.0f;
    }
    D_801116F0_pump_pump_away = 0;
}

void func_8011096C_pump_pump_away(void) {
    PpSlot12 *p;
    s32 i;

    for (i = 0; i < 6; i++) {
        p = &D_801119E8_pump_pump_away[i];
        p->state = -1;
        p->unk04 = 0;
        p->angle = 1.0f;
    }
    D_801116F2_pump_pump_away = 0;
}

void func_801109BC_pump_pump_away(void) {
    D_801116F4_pump_pump_away = 0;
    D_801116F8_pump_pump_away = 0;
    D_801116FC_pump_pump_away = 0;
    D_80111700_pump_pump_away = 0;
    D_80111704_pump_pump_away = 0;
    D_80111708_pump_pump_away = 30;
    D_801119E4_pump_pump_away = 0;
    func_801105D8_pump_pump_away();
    func_80110638_pump_pump_away();
    func_8011066C_pump_pump_away();
    func_801106AC_pump_pump_away();
    func_80110718_pump_pump_away();
    func_8011078C_pump_pump_away();
    func_801107C4_pump_pump_away();
    func_801107E4_pump_pump_away();
    func_80110824_pump_pump_away();
    func_80110868_pump_pump_away();
    func_80110888_pump_pump_away();
    func_801108D8_pump_pump_away();
    func_8011091C_pump_pump_away();
    func_8011096C_pump_pump_away();
}

void func_80110A78_pump_pump_away(void) {
    func_801109BC_pump_pump_away();
    func_8010745C_pump_pump_away();
    func_801066F0_pump_pump_away();
    func_80106894_pump_pump_away();
    func_80106A38_pump_pump_away();
    func_8010CBF0_pump_pump_away();
    func_80107E5C_pump_pump_away();
    func_80108504_pump_pump_away();
    func_8010B5D4_pump_pump_away();
    func_80109B48_pump_pump_away();
    func_80109470_pump_pump_away();
    func_80109E3C_pump_pump_away();
    func_80108FA8_pump_pump_away();
    func_8010D458_pump_pump_away();
    func_8010D6C0_pump_pump_away();
    func_8010E098_pump_pump_away();
    func_8010E65C_pump_pump_away();
    func_8010EB68_pump_pump_away();
    func_8010F20C_pump_pump_away();
    func_8010F8A4_pump_pump_away();
    func_801078B4_pump_pump_away();
}

void func_80110B34_pump_pump_away(omObjData *obj) {
    func_80110A78_pump_pump_away();
    WipeCreateIn(0xFF, 0x10);
    obj->func = func_80110574_pump_pump_away;
    omAddObj(0x32, 0, 0, -1, func_8010F900_pump_pump_away);
    omAddObj(0x320, 0, 0, -1, func_80110458_pump_pump_away);
}

void func_80110BB0_pump_pump_away(void) {
}

void func_80110BB8_pump_pump_away(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8011111C_pump_pump_away[i].scissor[0], D_8011111C_pump_pump_away[i].scissor[1],
                   D_8011111C_pump_pump_away[i].scissor[2], D_8011111C_pump_pump_away[i].scissor[3]);
        ViewportSet(i, D_8011111C_pump_pump_away[i].viewport[0], D_8011111C_pump_pump_away[i].viewport[1],
                    D_8011111C_pump_pump_away[i].viewport[2], D_8011111C_pump_pump_away[i].viewport[3],
                    D_8011111C_pump_pump_away[i].viewport[4], D_8011111C_pump_pump_away[i].viewport[5]);
        Hu3DCamSetPerspective(i, D_8011111C_pump_pump_away[i].fov, 80.0f, 8000.0f);
    }
}

void func_80110D28_pump_pump_away(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(100);
    omInitObjMan(100, 0);
    func_8004A208_main();
    func_80110BB8_pump_pump_away();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_801116D8_pump_pump_away, 0);
    func_80045010_main(D_801116D8_pump_pump_away, 1);
    omAddObj(1000, 0, 0, -1, func_80110B34_pump_pump_away);
    omAddObj(1000, 0, 0, -1, func_801104F4_pump_pump_away);
    func_80105C54_pump_pump_away();
}

const s16 D_801116D8_pump_pump_away[] = { 0x8260, 0x8261, 0x8262, 0 }; /* Shift-JIS fullwidth "ABC" */
