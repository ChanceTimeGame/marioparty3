#ifndef MGRESULTDEALER_H
#define MGRESULTDEALER_H

#include "common.h"
#include "game/object.h"
#include "game/hmfman.h"
#include "math.h"
#include "../ovl_81_name/ovl_81.h"

/* mgresultdealer: the Game Guy minigame results screen (ovl 0x72). The player's coin total is shown
   as Game Guy's hand drops a slot of coins (40 coin sprites and their sparkles) on the winner. */

typedef struct UnkOmData {
    omObjData *obj;
    void (*func)(omObjData *);
} UnkOmData;

/* Sprite-model slot (D_800CBB60_main entry; mgresultduel's DuelSprModel). */
typedef struct DealerSprModel {
    /* 0x00 */ s16 model;
    /* 0x02 */ u16 bank;
    /* 0x04 */ s16 step;
    /* 0x06 */ s16 anim;
    /* 0x08 */ s16 time;
    /* 0x0A */ char unk_0A[0x16];
    /* 0x20 */ u8 *unk_20;
} DealerSprModel; /* sizeof 0x24 */

typedef struct DealerSprAnim {
    /* 0x00 */ s16 stepCount;
    /* 0x02 */ s16 duration;
    /* 0x04 */ s16 *steps; /* stepCount pairs of s16 x4 */
} DealerSprAnim; /* sizeof 8 */

typedef struct DealerSprBank {
    /* 0x00 */ char unk_00[0x0C];
    /* 0x0C */ void *frames;
    /* 0x10 */ DealerSprAnim *anims;
    /* 0x14 */ u16 *palette;
} DealerSprBank; /* sizeof 0x18 */

/* One flying coin (or the sparkle where it lands). */
typedef struct DealerCoin {
    /* 0x00 */ u8 active;
    /* 0x02 */ u16 spr;
    /* 0x04 */ s32 time;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 z;
    /* 0x14 */ f32 vy;
} DealerCoin; /* sizeof 0x18 */

/* The model file's camera (hmfload.c HmfData_UnkBC, at HmfData +0xBC). */
typedef struct DealerHmfCam {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec eye;
    /* 0x14 */ Vec at;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 fov;
} DealerHmfCam;

typedef struct DealerHmfData {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 unk1A; /* face group count */
    /* 0x1C */ char unk1C[0xA0];
    /* 0xBC */ DealerHmfCam *cam;
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
    /* 0x58 */ DealerFxPart *parts;
} DealerFxWork;

extern DealerSprModel *D_800CBB60_main;
extern DealerSprBank *D_800D408C_main;
extern s32 D_800A178C_main[][6];

f32 atan2df(f32, f32);
s16 HmfAnimRead(HmfData *hmf, s32 dataNum, char *name);
void func_80013320_main(s16 modelIndex, s16 camIndex);
void func_80013390_main(s16 model, s16 type, char *name, void (*hook)(s16));
void func_80019828_main(s16, s32);
u16 func_80014618_main(s16 index, u16 arg1);
void func_80014714_main(s16 index, u16 arg1);
void func_8000BC48_main(u16, s32);

void func_80105C88_mgresultdealer(omObjData *);
void func_801061C8_mgresultdealer(void);
void func_80106234_mgresultdealer(omObjData *);
void func_801062B4_mgresultdealer(void);
void func_8010630C_mgresultdealer(s16);
void func_801065D0_mgresultdealer(void);
void func_80106A50_mgresultdealer(omObjData *);
void func_80106B94_mgresultdealer(omObjData *);
void func_80106CC8_mgresultdealer(omObjData *);
void func_80106D94_mgresultdealer(void);
void func_80106D9C_mgresultdealer(void);
s8 func_80106EA0_mgresultdealer(void);
void func_80106EAC_mgresultdealer(void);
void func_80106EC0_mgresultdealer(omObjData *);
void func_80106EEC_mgresultdealer(void);
void func_8010705C_mgresultdealer(omObjData *);
void func_801070EC_mgresultdealer(s16);
void func_801072A8_mgresultdealer(s16);
void func_801073F4_mgresultdealer(void);
void func_80107448_mgresultdealer(void);
void func_801074A0_mgresultdealer(void);
void func_80107888_mgresultdealer(omObjData *);
void func_80107E3C_mgresultdealer(void);
void func_80107E44_mgresultdealer(s32);
s8 func_80108034_mgresultdealer(void);
void func_80108040_mgresultdealer(void);
void func_80108194_mgresultdealer(omObjData *);
void func_80108258_mgresultdealer(void);
void func_80108260_mgresultdealer(void);
s8 func_8010829C_mgresultdealer(void);
void func_801082A8_mgresultdealer(omObjData *);
void func_80108544_mgresultdealer(omObjData *);
void func_80108554_mgresultdealer(void);
void func_80108560_mgresultdealer(void);
void func_80108570_mgresultdealer(void);
void func_80108AEC_mgresultdealer(omObjData *);
void func_80108BD4_mgresultdealer(omObjData *);
void func_80109044_mgresultdealer(omObjData *);
void func_801090B4_mgresultdealer(void);
s32 func_801090E8_mgresultdealer(void);
s32 func_801090F4_mgresultdealer(void);
void func_80109100_mgresultdealer(omObjData *);
void func_801093A0_mgresultdealer(omObjData *);
s8 func_80109478_mgresultdealer(void);
void func_80109484_mgresultdealer(omObjData *);
void func_80109710_mgresultdealer(omObjData *);

/* .data (each defined at the end of the unit that owns it) */
extern s8 D_801098C0_mgresultdealer;  /* main state */
extern s32 D_801098CC_mgresultdealer; /* main state timer */
extern s8 D_801098D0_mgresultdealer;  /* quitting (START) */
extern s8 D_801098E0_mgresultdealer;  /* hand moving */
extern s8 D_801098E1_mgresultdealer;
extern s8 D_801098E2_mgresultdealer;  /* hand reached the bottom */
extern Vec D_801098E4_mgresultdealer; /* hand position */
extern Vec D_801098F0_mgresultdealer; /* hand rotation */
extern s32 D_801098FC_mgresultdealer[4]; /* confetti model files */
extern s16 D_8010990C_mgresultdealer; /* confetti frame counter */
extern const s32 D_801099A8_mgresultdealer[8];
extern s8 D_80109910_mgresultdealer;  /* coins falling */
extern s8 D_80109911_mgresultdealer;  /* all coins landed */
extern s32 D_80109914_mgresultdealer; /* frame */
extern s32 D_80109918_mgresultdealer; /* coins to drop (at most 999) */
extern s32 D_8010991C_mgresultdealer; /* coins dropped */
extern s32 D_80109920_mgresultdealer; /* coins shown (at most 50) */
extern s32 D_80109924_mgresultdealer; /* frames between drops */
extern s32 D_80109928_mgresultdealer; /* landing sound played */
extern s32 D_8010992C_mgresultdealer; /* rumble done */

/* .bss */
extern s16 D_801099F8_mgresultdealer[4]; /* confetti models */
extern f32 D_80109A60_mgresultdealer;    /* hand fall speed */
extern s16 D_80109A64_mgresultdealer[4]; /* player motions (D_80109A68/A6A: [2], [3]) */
extern UnkOmData D_8010A250_mgresultdealer; /* Game Guy, the hand and the slot */
extern s16 D_8010A258_mgresultdealer;     /* bonus coins (multiplier) */
extern s16 D_8010A264_mgresultdealer;     /* coins */
extern s8 D_8010A266_mgresultdealer[4];   /* players by group */
extern u16 D_80109A70_mgresultdealer[2]; /* sprite models of the coins [0] and their sparkles [1] */
extern DealerCoin D_80109A78_mgresultdealer[40]; /* coins */
extern DealerCoin D_80109E38_mgresultdealer[40]; /* sparkles */
extern UnkOmData D_8010A274_mgresultdealer; /* coins */

#endif
