#ifndef _OPENING_H_
#define _OPENING_H_

#include "common.h"

/* Overlay 0x7A `opening`: the title screen and the scripted opening demo. */

/* Sprite slot (opSpr*): D_80114EB0_opening[64]. */
typedef struct OpSpr {
    /* 0x00 */ s16 espId; /* esprite slot, -1 when free */
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ f32 scaleX;
    /* 0x10 */ f32 scaleY;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18; /* 0xFF at init */
} OpSpr; /* size = 0x1C */

/* Model slot (opModel*, opMotion*): D_80115630_opening[160]. */
typedef struct OpModel {
    /* 0x00 */ s16 model;  /* -1 when free */
    /* 0x02 */ s16 motion; /* -1 when free */
    /* 0x04 */ s32 pos[3]; /* retail keeps the position truncated to integers */
    /* 0x10 */ Vec scale;
    /* 0x1C */ Vec rot;
    /* 0x28 */ s32 unk28;
} OpModel; /* size = 0x2C */

/* Window slot: D_801171B8_opening[32]. */
typedef struct OpWin {
    /* 0x00 */ s16 id;     /* window id, -1 when free */
    /* 0x04 */ u32 mesBuf; /* heap copy of the message (address above 0x80000000), or 0 */
    /* 0x08 */ s32 type;   /* read by the kill path (3 = choice window); never written in this unit */
} OpWin; /* size = 0xC */

/* Screen shake (func_80110C04_opening): starts at D_80117338_opening. */
typedef struct OpShake {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ f32 power;
    /* 0x08 */ s32 time;
    /* 0x0C */ s32 maxTime;
    /* 0x10 */ s32 sign;
} OpShake; /* size = 0x14 */

/* Demo camera (func_80110FB0_opening): D_80117350_opening. */
typedef struct OpCamera {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec at;
    /* 0x18 */ Vec up;
    /* 0x24 */ omObjData *obj;
} OpCamera; /* size = 0x28 */

/* Effect object slot (opDemoObj*, opWipe*, opDemo*Eff*): D_80117388_opening[16].
   The work words are reused per effect; `wipe` is the opWipe* view. */
typedef struct OpDemoObj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ union {
        s32 i[14];
        f32 f[14];
        struct {
            /* 0x04 */ s32 time;
            /* 0x08 */ s32 maxTime;
            /* 0x0C */ u8 r, g, b, a;
            /* 0x10 */ s16 gfx; /* func_8001AC8C_main handle */
        } wipe;
    } w;
} OpDemoObj; /* size = 0x3C */

/* Controller-error sprite: D_80117750_opening. */
typedef struct OpContError {
    /* 0x00 */ s16 anim;
    /* 0x02 */ s16 esp;
} OpContError;

/* .data */
extern OvlEntrypoint D_80114B50_opening[];
extern Vec D_80114BB8_opening;   /* viewport scale */
extern Vec D_80114BC4_opening;   /* viewport translation */
extern RectF D_80114BD0_opening; /* scissor */
extern s32 D_80114BE0_opening;   /* random seed */
extern Gfx D_80114BE8_opening[]; /* wipe display list */
extern Vec D_80114C40_opening;   /* camera position */
extern Vec D_80114C4C_opening;   /* camera target */
extern Vec D_80114C58_opening;   /* camera up */
/* D_80114B70/B88/BA0/BAC (opDemoEvent only) and the .rodata tables D_80114CE4/D84/D90/D9C/DA8
   are left to the forks that decompile their users. */

/* .bss */
extern Process *D_80114EA0_opening;   /* title / demo main process */
extern s32 D_80114EA4_opening;        /* demo end flag (opDemoEnd*) */
extern OpSpr D_80114EB0_opening[64];
extern s16 D_801155B0_opening[64];    /* sprite animations (opAnim*) */
extern OpModel D_80115630_opening[160];
extern s16 D_801171B0_opening;        /* title background animation */
extern s16 D_801171B2_opening;        /* title background esprite */
extern OpWin D_801171B8_opening[32];
extern OpShake D_80117338_opening;
extern OpCamera D_80117350_opening;
extern Vec D_80117378_opening;
extern s32 D_80117384_opening;
extern OpDemoObj D_80117388_opening[16];
extern OpContError D_80117750_opening;

/* main and board-overlay functions without a shared prototype */
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BBFC_main(u16 spriteId, s16 arg1);
void func_8000BCC8_main(u16 spriteId, s32 arg1);
void func_8000BD94_main(u16 spriteId, s32 arg1, s32 arg2);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
void func_8000BE5C_main(u16 spriteId, f32 x, f32 y);
void func_80030030_main(f32);
s32 func_80050064_main(s32 write);
s32 func_800452A0_main(void *arg0, void *arg1);
void MBCameraOffsetSet(s16 arg0, s16 arg1);

/* 523FD0.c */
void func_801059A0_opening(void);
void opObjectInit(void);
void opTitleObjectSetup(void);
void func_80105C2C_opening(void);
void opDemoObjectSetup(void);
void opEventInit(void);
void opTitleCreate(void);
void opDemoCreate(void);
Process *opDemoEventCreate(void);
void opDemoMain(void);
Process *func_80105F68_opening(void);
void opTitleMain(void);
s32 opBtnStartCheck(void);
void opDemoEndReset(void);
void opDemoEndSet(s32 flag);
s32 opDemoEndGet(s32 unused); /* retail callers pass a mask it ignores */
void func_801061F0_opening(void);
void func_8010621C_opening(void);
s16 opAnimIdGet(s32 no);
s16 opEspIdGet(s32 no);
void opAnimCreate(s32 no, s32 dataNum);
void opAnimKill(s32 no);
void opEspCreate(s32 no, s16 animNo);
void opEspKill(s32 no);
void opSprCreate(s32 no, s32 dataNum);
void opSprBGCreate(s32 no, s32 dataNum);
void opSprKill(s32 no);
void opSprKillAll(void);
void opSprDispOn(s32 no);
void opSprDispOff(s32 no);
void opSprBGDispOn(s32 no);
void opSprBGDispOff(s32 no);
void opSprPosSet(s32 no, s32 x, s32 y);
void opSprPosGet(s32 no, s32 *x, s32 *y);
void opSprScaleSet(s32 no, f32 x, f32 y);
void opSprAlphaSet(s32 no, u16 alpha); /* B: callers narrow to u16 (opTitleSprMain) */
void opSprAttrSet(s32 no, u16 attr);
void opSprAttrReset(s32 no, u16 attr);
void func_80106734_opening(s32 no, u16 arg1);
void func_80106768_opening(s32 no, u16 arg1, u16 arg2);
void func_801067D4_opening(void);
void opModelCreate(s32 no, s32 arg1, s32 dataNum);
void opMotionCreate(s32 no, s32 dataNum, s16 arg2);
void opModelKill(s32 no);
void opModelKillAll(void);
s16 opModelIdGet(s32 no);
s16 opMotionIdGet(s32 no);
void opModelRotSet(s32 no, f32 x, f32 y, f32 z);
void opModelPosSet(s32 no, f32 x, f32 y, f32 z);
void opModelScaleSet(s32 no, f32 x, f32 y, f32 z);
void opModelPosGet(s32 no, f32 *x, f32 *y, f32 *z);
void opModelRotGet(s32 no, f32 *x, f32 *y, f32 *z);
void opModelScaleGet(s32 no, f32 *x, f32 *y, f32 *z);
void opModelDispOff(s32 no);
void opModelDispOn(s32 no);
void opMotionFlagSet(s32 no, s16 flag);
void opMotionShiftSet(s32 no, s32 motNo, s16 arg2, s16 arg3, s16 arg4);
void func_80106DD0_opening(s32 no, s16 arg1);
void opMotionSpeedSet(s32 no, f32 speed);
void opMotionTimeSet(s32 no, u32 time);
void opMotionEndWait(s32 no);
s32 opMotionEndCheck(s32 no);
void opMotionSet(s32 no, s32 motNo, s16 flag);
void func_80107048_opening(s32 dataNum);
void func_801070AC_opening(void);
u32 func_801070D8_opening(u32 mes);
void func_80107140_opening(s32 no, u32 mes, s16 x, s16 y, s16 w, s16 h, s16 type);
s16 func_8010738C_opening(u32 mes, s16 x, s16 y, s16 w, s16 h);
s16 func_801074D8_opening(u32 mes, s16 x, s16 y, s16 w, s16 h);
s16 func_80107640_opening(u32 mes, s16 x, s16 y, s16 w, s16 h);
s16 func_801077E8_opening(u32 mes, s16 x, s16 y);
s16 func_801078B4_opening(u32 mes, s16 x, s16 y);
s16 func_80107980_opening(u32 mes, s16 x, s16 y);
void func_80107A4C_opening(void);
void func_80107A90_opening(s32 no);
void func_80107B74_opening(void);
void func_80107BD8_opening(s32 no, f32 x, f32 y);
void func_80107C08_opening(s32 no, f32 x, f32 y);
void func_80107C70_opening(s32 no);
void func_80107CA0_opening(s32 no);
void func_80107CD0_opening(s32 no, u32 mes);
void func_80107D9C_opening(s32 no, s8 arg1, s32 arg2);
void func_80107DD8_opening(s32 no, s16 arg1, s32 arg2);
s16 func_80107E10_opening(s32 no);
void func_80107E2C_opening(s32 no);
void func_80107E80_opening(u16 btn);
u16 func_80107EF4_opening(s32 arg0);
void opDemoEventSetup(void);
void func_80108118_opening(void);
void opDemoEvent(void);
void opDemoEventKill(void);
void func_80110B90_opening(void);
void func_80110B9C_opening(void);
void func_80110C04_opening(omObjData *obj);
void func_80110D8C_opening(s32 time, f32 power);
void opDemoCharCreate(s32 no, s32 dataNum, f32 x, f32 y, f32 z);
void opDemoShadowCreate(s32 no, f32 x, f32 y, f32 z);
void opDemoModelKill(void);
void opDemoSprKill(void);
void func_80110F48_opening(void);
void func_80110FB0_opening(Vec *pos, Vec *at);
void func_80111028_opening(void);
void func_8011105C_opening(void);
void func_80111090_opening(omObjData *obj);
void func_801110AC_opening(f32 *posX, f32 *posY, f32 *posZ, f32 *atX, f32 *atY, f32 *atZ);
void func_801110F0_opening(f32 posX, f32 posY, f32 posZ, f32 atX, f32 atY, f32 atZ);
f32 func_80111164_opening(f32 x0, f32 z0, f32 x1, f32 z1);
f32 func_801111AC_opening(f32 from, f32 to, f32 step);
f32 func_8011124C_opening(f32 x0, f32 z0, f32 x1, f32 z1, f32 t);
f32 func_80111490_opening(f32 angle, f32 x, f32 z, f32 t);
void func_80111580_opening(void);
s16 func_801117D4_opening(s32 arg0, s32 arg1);
s16 func_80111984_opening(s32 arg0, s32 arg1);
u32 func_80111B34_opening(u32 seed);
void func_80111C08_opening(void);
u32 func_80111C30_opening(u32 max);
s32 func_80111C88_opening(s16 model, f32 x, f32 y, f32 z);
s32 func_80111DDC_opening(s16 model, f32 x, f32 y, f32 z, f32 scale);
void func_80111F58_opening(s16 model);
void func_80112120_opening(s16 model);
void opTitleSetup(void);
void opTitleSprMain(void);
void opTitleKill(void);
void func_80112944_opening(void);
void opDemoObjKillAll(void);
void opDemoObjKill(s32 no);
void opDemoObjCreate(s32 no, omObjFunc func);
void func_80112A74_opening(omObjData *obj);
void func_80112BA0_opening(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_80112C8C_opening(omObjData *obj);
void func_80112D30_opening(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void opDemoOutEffMain(omObjData *obj);
void opDemoOutEffCreate(s32 arg0, s32 arg1);
void opDemoGuideInEffMain(omObjData *obj);
void opDemoGuideInEffCreate(s32 arg0, s32 arg1);
void opDemoStarWaitMain(omObjData *obj);
void opDemoStarWaitCreate(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6);
void func_801134FC_opening(s32 arg0, Vec *arg1, Vec *arg2, f32 arg3, f32 arg4);
void func_8011361C_opening(omObjData *obj);
void func_8011373C_opening(omObjData *obj);
void func_801139B0_opening(s32 arg0, s32 arg1, Vec *arg2, Vec *arg3, char *arg4, char *arg5);
void func_80113AE8_opening(omObjData *obj);
void func_80113E8C_opening(omObjData *obj);
void func_80114150_opening(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4);
void func_80114250_opening(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void opWipeDraw(Gfx **gfx, s32 arg1, s32 arg2);
void opWipeColorSet(s32 no, u8 r, u8 g, u8 b, u8 a);
void opWipeInMain(omObjData *obj);
void opWipeOutMain(omObjData *obj);
void opWipeKill(s32 no);
void opWipeInCreate(s32 no, s32 time);
void opWipeOutCreate(s32 no, s32 time);
void opWipeWhiteInCreate(s32 time);
void opWipeWhiteOutCreate(s32 time);
void func_801149A4_opening(s32 arg0);
void opSleep(s32 time);
void opContErrorCreate(void);
void opContErrorDispOn(void);
void opContErrorDispOff(void);
void opContErrorKill(void);

/* B */
/* hmfman's vertex-scatter effect (HmfModel.unkBC, 13F90.c's HmfFxWork) as this overlay's hooks
   use it: one OpFxPart per face group. */
typedef struct OpFxPart {
    /* 0x00 */ u8 color[3];
    /* 0x04 */ f32 phase; /* 0..180 while live, >= 180 idle */
    /* 0x08 */ f32 scale;
    /* 0x0C */ Vec pos;
    /* 0x18 */ f32 angle;
    /* 0x1C */ f32 radiusStep;
    /* 0x20 */ f32 radius;
    /* 0x24 */ Vec vel; /* func_80111F58_opening: x = angle step, y/z = height/radius factors */
} OpFxPart; /* size 0x30 */

typedef struct OpFxWork {
    /* 0x00 */ s16 motion;
    /* 0x02 */ s16 frame;
    /* 0x04 */ u16 flags;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ void (*hook)(s16);
    /* 0x1C */ Vec center;
    /* 0x28 */ Vec verts[4];
    /* 0x58 */ OpFxPart *parts;
} OpFxWork; /* size 0x5C */

/* HmfData's face group count (hmfman.h does not name it). */
typedef struct OpFxHmf {
    /* 0x00 */ char unk00[0x1A];
    /* 0x1A */ s16 groupCount;
} OpFxHmf;

#define OP_FX_WORK(m) ((OpFxWork *)(m)->unkBC)
#define OP_FX_GROUPS(m) (((OpFxHmf *)(m)->hmf)->groupCount)

void func_80013390_main(s16 model, s16 type, char *name, void (*hook)(s16));
void func_8000BEAC_main(u16 spriteId, s32 r, s32 g, s32 b);

extern const Vec D_80114D84_opening; /* title camera position */
extern const Vec D_80114D90_opening; /* title camera target */

#endif
