#ifndef _OVL_MINIGAME_H
#define _OVL_MINIGAME_H

#include "ultra64.h"
#include "game/object.h"

/* A player's motion slot (MgWork::unkE8[slot]). */
typedef struct {
    /* 0x00 */ u16 unk00; /* flags: 1 loop, 2 not interruptible, 4 motion file */
    /* 0x02 */ u16 unk02; /* speed */
    /* 0x04 */ s16 unk04; /* passed on as MgMotionReq::unk06 */
    /* 0x06 */ char unk06[2];
    /* 0x08 */ s32 unk08; /* key func_800E5A98_minigame looks up */
} func_800E1BA8_minigame_UnkE8_ObjData; // Size 0xC

/* A pending motion request (MgWork::unkD8). */
typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u16 motion;
    /* 0x04 */ char unk04[2];
    /* 0x06 */ s16 unk06; /* < 0: none; else the 4th argument of func_80017954_main */
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 speed;
} MgMotionReq; // Size 0x10

typedef struct {
    /* 0x000 */ char unk00[4];
    /* 0x004 */ u8 unk04; /* id */
    /* 0x005 */ char unk05;
    /* 0x006 */ u16 unk06; /* flags */
    /* 0x008 */ f32 unk08;
    /* 0x00C */ f32 unk0C;
    /* 0x010 */ f32 unk10;
    /* 0x014 */ f32 unk14;
    /* 0x018 */ char unk18[0x1C];
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ f32 unk3C;
    /* 0x040 */ f32 unk40;
    /* 0x044 */ f32 unk44;
    /* 0x048 */ f32 unk48;
    /* 0x04C */ f32 unk4C;
    /* 0x050 */ u16 unk50;
    /* 0x052 */ s8 unk52;
    /* 0x053 */ s8 unk53;
    /* 0x054 */ s8 unk54;
    /* 0x055 */ u8 unk55;
    /* 0x056 */ u8 unk56;
    /* 0x057 */ s8 unk57;
    /* 0x058 */ u8 unk58;
    /* 0x059 */ s8 unk59;
    /* 0x05A */ u8 unk5A; /* model of the last motion (func_800E210C_minigame) */
    /* 0x05B */ u8 unk5B; /* that motion */
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ f32 unk60; /* heading offset added to the stick angle */
    /* 0x064 */ f32 unk64;
    /* 0x068 */ f32 unk68;
    /* 0x06C */ f32 unk6C;
    /* 0x070 */ f32 unk70;
    /* 0x074 */ s32 unk74[6];
    /* 0x08C */ f32 unk8C;
    /* 0x090 */ f32 unk90;
    /* 0x094 */ f32 unk94;
    /* 0x098 */ f32 unk98;
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ union {
        f32 f;     /* ground object: box maxX */
        u16 timer; /* player: squash timer */
    } unkA8;
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ f32 unkB0;
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8; /* end frame of the current motion */
    /* 0x0BC */ u16 unkBC;
    /* 0x0BE */ u16 unkBE;
    /* 0x0C0 */ u16 unkC0;
    /* 0x0C2 */ u8 unkC2; /* blink phase */
    /* 0x0C3 */ s8 unkC3;
    /* 0x0C4 */ s8 unkC4;
    /* 0x0C5 */ s8 unkC5;
    /* 0x0C6 */ s16 unkC6;
    /* 0x0C8 */ void* unkC8;
    /* 0x0CC */ f32 unkCC;
    /* 0x0D0 */ u16 unkD0; /* current motion step, 0xFFFF idle */
    /* 0x0D2 */ u16 unkD2; /* motion step count */
    /* 0x0D4 */ char unkD4[2];
    /* 0x0D6 */ u16 unkD6; /* request pending */
    /* 0x0D8 */ MgMotionReq unkD8;
    /* 0x0E8 */ func_800E1BA8_minigame_UnkE8_ObjData* unkE8;
    /* 0x0EC */ s32 (*unkEC)(omObjData*, omObjData*);
    /* 0x0F0 */ u16 unkF0;
    /* 0x0F2 */ s8 unkF2[0x12]; /* motion per slot (func_800E21B8_minigame) */
    /* 0x104 */ s32 (*unk104[21])(); /* minigame override hooks; 1 = handled */
    /* 0x158 */ void* unk158;
} func_800E1BA8_minigame_ObjData; // Size 0x15C

typedef struct {
    /* 0x00 */ char unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ char unk07[0x11];
    /* 0x18 */ s8 unk18;
    /* 0x19 */ char unk19[3];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
} D_80111B50_vine_with_me_Struct; // Size unknown (>= 0x26 and <= 0x28)

void func_800E18D8_minigame(void);
void func_800E19F0_minigame(s8);
void func_800E1BA8_minigame(omObjData*, u32, s32, u16, s32, s32);
void func_800E4E30_minigame(omObjData*);
s32 func_800E5690_minigame(omObjData*, u16);
void func_800E5A00_minigame(omObjData*, u16, s32, s32, u16);
void func_800E5EA0_minigame(D_80111B50_vine_with_me_Struct*);
u8 func_800E6E8C_minigame(void);
void func_800E6F1C_minigame(void);
void func_800E6F34_minigame(s32);
void func_800E6F40_minigame(void);

extern s16 D_800EBE28_minigame;
extern s16 D_800EC1B8_minigame;
extern omObjData* D_800EC1C0_minigame[];
extern u16 D_800EC280_minigame;
extern omObjData* D_800EC598_minigame[];

#endif
