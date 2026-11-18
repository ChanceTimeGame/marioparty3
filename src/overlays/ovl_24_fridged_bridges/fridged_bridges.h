#ifndef FRIDGED_BRIDGES_H
#define FRIDGED_BRIDGES_H

#include "game/object.h"

/* omObjData::data of a player (func_8010648C_fridged_bridges, 0x6C) */
typedef struct FbPlayer {
    /* 0x00 */ u16 unk00; /* 0 frozen, 1 walking, 2 falling */
    /* 0x02 */ s16 unk02; /* player index */
    /* 0x04 */ u16 unk04; /* motion: 0 idle, 1 walk, 2 run */
    /* 0x06 */ s16 unk06; /* 1 = reached the goal */
    /* 0x08 */ f32 unk08; /* velocity x */
    /* 0x0C */ f32 unk0C; /* velocity z */
    /* 0x10 */ f32 unk10; /* stick x */
    /* 0x14 */ f32 unk14; /* stick z */
    /* 0x18 */ char unk18[4];
    /* 0x1C */ s16 unk1C; /* tile */
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u16 unk26; /* hooks used */
    /* 0x28 */ u16 unk28;
    /* 0x2A */ char unk2A[2];
    /* 0x2C */ omObjData *unk2C;
    /* 0x30 */ omObjData *unk30; /* splash fish object */
    /* 0x34 */ f32 unk34; /* fall velocity x */
    /* 0x38 */ f32 unk38; /* fall velocity y */
    /* 0x3C */ f32 unk3C; /* fall velocity z */
    /* 0x40 */ f32 unk40; /* float angle */
    /* 0x44 */ f32 unk44; /* hook scale */
    /* 0x48 */ u16 unk48; /* footstep sound timer */
    /* 0x4A */ u16 unk4A; /* slide sound timer */
    /* 0x4C */ f32 unk4C; /* CPU speed factor */
    /* 0x50 */ f32 unk50; /* splash scale */
    /* 0x54 */ u16 unk54; /* splash timer */
    /* 0x56 */ u16 unk56;
    /* 0x58 */ u16 unk58;
    /* 0x5A */ char unk5A[2];
    /* 0x5C */ f32 unk5C; /* last safe x */
    /* 0x60 */ f32 unk60; /* last safe y */
    /* 0x64 */ f32 unk64; /* last safe z */
    /* 0x68 */ s16 unk68; /* last safe tile */
    /* 0x6A */ u16 unk6A; /* CPU: frames until it turns back */
} FbPlayer; // Size 0x6C

typedef struct FbUV {
    /* 0x00 */ f32 u;
    /* 0x04 */ f32 v;
} FbUV;

/* main 20A20.c's draw-culling view (func_80020E94_main's first argument) */
typedef struct HitViewFan {
    /* 0x00 */ f32 angle;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 fov;
    /* 0x10 */ f32 len;
    /* 0x14 */ f32 back;
} HitViewFan;

/* D_8010DA90_fridged_bridges: per player, the view func_80020E94_main culls with, and its work area */
typedef struct FbView {
    /* 0x000 */ HitViewFan fan;
    /* 0x018 */ u8 unk18[0xC00];
} FbView; // Size 0xC18

extern FbView D_8010DA90_fridged_bridges[4];

#endif
