#ifndef _INST_H
#define _INST_H

#include "common.h"

/* inst (overlay 0x70, the minigame instruction screen): what its units share. */

/* A model part name list (D_8010D4C0_inst[type][0..1]): count names follow. Each list is
   defined with its own size through INST_HOOK_LIST(n). */
#define INST_HOOK_LIST(n) struct { s16 count; const char *names[n]; }
typedef struct InstHookList {
    /* 0x00 */ s16 count;
    /* 0x04 */ const char *names[1]; /* [count] */
} InstHookList;

/* Views of hmfman.c's HmfMotionObjM / HmfDataM / HmfPartM (func_8001D33C_main's result). */
typedef struct InstHmfPart {
    /* 0x00 */ char unk00[0x24];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[0x42];
} InstHmfPart; /* size 0x68 */
typedef struct InstHmfData {
    /* 0x00 */ char unk00[0x60];
    /* 0x60 */ InstHmfPart *parts;
} InstHmfData;
typedef struct InstMotionObj {
    /* 0x00 */ s16 count;
    /* 0x02 */ char unk02[0x4A];
    /* 0x4C */ f32 unk4C; /* x scale */
    /* 0x50 */ s16 *children; /* part index, or 0x8000 | motion object index */
    /* 0x54 */ InstHmfData *hmf;
    /* 0x58 */ char unk58[8];
    /* 0x60 */ f32 unk60; /* y scale */
    /* 0x64 */ char unk64[0x10];
    /* 0x74 */ f32 unk74; /* z scale */
} InstMotionObj;

extern s8 D_8010D400_inst[7];
extern s8 D_8010D404_inst;
extern s8 D_8010D405_inst;
extern s8 D_8010D406_inst;
extern s8 D_8010D407_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D409_inst;
extern s8 D_8010D40A_inst; /* minigame type */
extern s8 D_8010D40B_inst; /* minigame index */
extern f32 D_8010D414_inst; /* board tilt */
extern s32 D_8010D4A4_inst; /* instruction message */
extern s32 D_8010D508_inst;
extern f32 D_8010D50C_inst;
extern s32 D_8010D510_inst;
extern InstHookList *D_8010D4C0_inst[9][2];
extern void *D_8010DC10_inst;
extern void *D_8010DC14_inst;
extern void *D_8010DC18_inst;
/* The board object and its current page handler. */
typedef struct InstBoard {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} InstBoard;
extern InstBoard D_8010DDD8_inst;
extern InstBoard D_8010DDE0_inst; /* the host character */

/* The host character's texture animation. */
typedef struct InstAnim {
    /* 0x00 */ s32 anim;
    /* 0x04 */ s32 unk4;
} InstAnim;
extern InstAnim D_8010DC20_inst;
extern s16 D_8010DC22_inst; /* low half of D_8010DC20_inst.anim */
extern s16 D_8010DC28_inst;

typedef struct TexAnimSlot {
    /* 0x00 */ s16 unk_00; /* frame */
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} TexAnimSlot; /* 14EA0.c */
extern TexAnimSlot *D_800D1714_main;
void func_80032FC0_main(s16, u8, u8);
s16 func_800329B4_main(void *);
void func_80108A10_inst(omObjData *);
void func_8010872C_inst(omObjData *);
void func_80108A18_inst(s16, s16, s16);

u16 func_8000B0D4_main(s32, s32);
void *func_8001D33C_main(s16 model, const char *name);
void func_80107938_inst(omObjData *);
void func_801079CC_inst(omObjData *);
void func_80107A24_inst(omObjData *);
void func_80107BF8_inst(omObjData *);
void func_80107E18_inst(omObjData *);
void func_80107F98_inst(omObjData *);
void func_8010B124_inst(void);
s8 func_8010B10C_inst(void);
void func_80107EE0_inst(void);
void func_8010815C_inst(omObjData *);
void func_80108AF0_inst(s16, void *, void *, void *);

#endif
