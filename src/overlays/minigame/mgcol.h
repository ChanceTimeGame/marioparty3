#ifndef _MINIGAME_MGCOL_H
#define _MINIGAME_MGCOL_H

/* The minigame overlay's collision and actor structs (MP2 collision.h; offsets re-derived from the MP3
   asm), shared by A96F0.c (item actors) and AB1C0.c (player collision). MgWork is the same object as
   include/overlays/minigame.h's func_800E1BA8_minigame_ObjData (same layout, field for field); keep
   the two in step. */

#include "common.h"

/* Minigame player collision against the ground objects and their faces: MP2 src/1130.c
   func_80002040_2C40 .. func_800062F0_6EF0 (MP1 src/1130.c func_80000530 ..). Layouts re-derived
   from the MP3 asm. */

typedef struct ColVtx {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} ColVtx;

typedef struct ColTri {
    /* 0x0 */ s16 flags; /* bits 14-15: vertex count - 2, bits 8-13: surface type */
    /* 0x2 */ s16 v[3];
} ColTri;

/* main 20A20.c's polygon query list (func_80021C14_main / func_80022198_main) */
typedef struct HitList {
    /* 0x00 */ u16** list;
    /* 0x04 */ u16 count;
    /* 0x06 */ u16 pos;
} HitList;

typedef struct HitProbe {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 r;
} HitProbe;

typedef struct Vec4f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ f32 w; /* radius */
} Vec4f;

/* A HitProbe followed by a second position: func_800D7C14_minigame's probe and save locals, which
   retail reads as one block (host hazard: two separate locals). */
typedef struct ColSphere {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 r;
    /* 0x10 */ f32 x2;
    /* 0x14 */ f32 y2;
    /* 0x18 */ f32 z2;
} ColSphere;

/* omObjData::data of a ground / platform object (D_800EC1C0_minigame[]) */
typedef struct GroundWork {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;  /* surface id copied to MgWork.unk_56 */
    /* 0x05 */ char unk_05;
    /* 0x06 */ u16 unk_06; /* flags: 2 skip, 4 test the part list, 8/0x10/0x20/0x40 primitive
                              shapes, 0x50 needs func_800E30B8_minigame, 0x400 tilts the rider */
    /* 0x08 */ f32 unk_08; /* friction */
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10; /* conveyor factor applied to the floor normal */
    /* 0x14 */ f32 unk_14; /* top surface height */
    /* 0x18 */ char unk_18[0x80];
    /* 0x98 */ f32 unk_98; /* subtracted from unk_14 for a player's ceiling test */
    /* 0x9C */ f32 unk_9C; /* cylinder radius (shapes 0x20, 0x40) */
    /* 0xA0 */ f32 unk_A0; /* box min x (shape 8) */
    /* 0xA4 */ f32 unk_A4; /* box min z */
    /* 0xA8 */ f32 unk_A8; /* box max x */
    /* 0xAC */ f32 unk_AC; /* box max z */
} GroundWork; /* size unknown */

/* omObjData::data of a minigame player (MP2 MgWork; only the fields this unit reads are named) */
typedef struct MgWork {
    /* 0x00 */ u8 unk_00[0x20]; /* per ground object flags: 1 ignore it, 8 hazard */
    /* 0x20 */ char unk_20[0x14];
    /* 0x34 */ f32 unk_34;  /* height */
    /* 0x38 */ f32 unk_38;  /* vertical speed; 1000.0f on the ground */
    /* 0x3C */ f32 unk_3C;  /* heading */
    /* 0x40 */ f32 unk_40;  /* speed */
    /* 0x44 */ char unk_44[4];
    /* 0x48 */ f32 unk_48;  /* radius */
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ u16 unk_50;  /* flags */
    /* 0x52 */ u8 unk_52;
    /* 0x53 */ s8 unk_53;   /* ground object index, -1 none */
    /* 0x54 */ s8 unk_54;
    /* 0x55 */ u8 unk_55;
    /* 0x56 */ u8 unk_56;
    /* 0x57 */ s8 unk_57;   /* controller port */
    /* 0x58 */ u8 unk_58;
    /* 0x59 */ s8 unk_59;   /* player */
    /* 0x5A */ char unk_5A[2];
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ char unk_68[4];
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ s32 unk_74[6]; /* packed (x << 16) | (y & 0xFFFF) stick samples */
    /* 0x8C */ f32 unk_8C;  /* ceiling height */
    /* 0x90 */ f32 unk_90;  /* ground velocity */
    /* 0x94 */ f32 unk_94;
    /* 0x98 */ f32 unk_98;
    /* 0x9C */ f32 unk_9C;  /* tilt x */
    /* 0xA0 */ f32 unk_A0;
    /* 0xA4 */ f32 unk_A4;  /* tilt z */
    /* 0xA8 */ char unk_A8[4];
    /* 0xAC */ f32 unk_AC;
    /* 0xB0 */ f32 unk_B0;
    /* 0xB4 */ f32 unk_B4;  /* speed factor */
    /* 0xB8 */ char unk_B8[4];
    /* 0xBC */ u16 unk_BC;  /* frames running, at most 200 */
    /* 0xBE */ u16 unk_BE;  /* hazard hit countdown */
    /* 0xC0 */ u16 unk_C0;  /* spin countdown */
    /* 0xC2 */ char unk_C2;
    /* 0xC3 */ s8 unk_C3;
    /* 0xC4 */ s8 unk_C4;
    /* 0xC5 */ s8 unk_C5;
    /* 0xC6 */ s16 unk_C6;  /* turn lean, -12..12 */
    /* 0xC8 */ void* unk_C8; /* held item, an omObjData* */
    /* 0xCC */ f32 unk_CC;
    /* 0xD0 */ u16 unk_D0;
    /* 0xD2 */ char unk_D2[8];
    /* 0xDA */ u16 unk_DA;
    /* 0xDC */ char unk_DC[0xC];
    /* 0xE8 */ void* unk_E8;
    /* 0xEC */ s32 (*unk_EC)(omObjData* obj, omObjData* actor); /* actor touch hook; 1 skips the default */
    /* 0xF0 */ u16 unk_F0;
    /* 0xF2 */ char unk_F2[0x12];
    /* 0x104 */ s32 (*unk_104[21])(); /* the minigame's override hooks; 1 = handled */
    /* 0x158 */ void* unk_158;
} MgWork;

/* omObjData::data of an item actor, 0xAC bytes (func_800D83D8_minigame). unk_84[] are hooks; one
   returning 1 skips the default step. */
typedef struct ColActorWork {
    /* 0x00 */ u8 unk_00[0x20]; /* per ground object flags: 1 ignore it */
    /* 0x20 */ char unk_20[4];
    /* 0x24 */ u8 unk_24;       /* sprite / effect slot */
    /* 0x25 */ char unk_25[0xF];
    /* 0x34 */ f32 unk_34;      /* height */
    /* 0x38 */ f32 unk_38;      /* vertical speed; 1000.0f on the ground */
    /* 0x3C */ f32 unk_3C;      /* heading (degrees) */
    /* 0x40 */ f32 unk_40;      /* speed */
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;      /* radius */
    /* 0x4C */ char unk_4C[4];
    /* 0x50 */ u16 unk_50;      /* flags */
    /* 0x52 */ u8 unk_52;       /* kind (3-6: coin values, 7: hazard) */
    /* 0x53 */ s8 unk_53;       /* ground object index, -1 none */
    /* 0x54 */ u8 unk_54;       /* active */
    /* 0x55 */ char unk_55[3];
    /* 0x58 */ f32 unk_58;      /* ground velocity scale */
    /* 0x5C */ f32 unk_5C;      /* ground velocity */
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;      /* tilt x */
    /* 0x6C */ char unk_6C[4];
    /* 0x70 */ f32 unk_70;      /* tilt z */
    /* 0x74 */ char unk_74[4];
    /* 0x78 */ s32 unk_78;      /* age (frames) */
    /* 0x7C */ s32 unk_7C;      /* lifetime (frames) */
    /* 0x80 */ s32 unk_80;
    /* 0x84 */ s32 (*unk_84[9])();
    /* 0xA8 */ void* unk_A8;
} ColActorWork; /* size = 0xAC */

#endif
