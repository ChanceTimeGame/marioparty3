#ifndef _ovl_80_F9DE0
#define _ovl_80_F9DE0

#include "common.h"
#include "game/board.h"

extern Object *D_801011FC_shared_board;

/* defined in F9DE0.c's .rodata, used by F5E80.c */
typedef struct SomeStruct {
    u8 unk_00[10];
} SomeStruct;

typedef struct SomeStruct2 {
    u16 unk_00[8];
} SomeStruct2;

extern const SomeStruct D_80102250_shared_board;
extern const SomeStruct2 D_8010225C_shared_board;

Object* MBKSuitCreate(void);
void MBKSuitKill(void);
void MBKSuitInit(void);
void MBKSuitClose(void);
void MBKSuitMotionSet(s16 arg0, s32 arg1);
void MBKSuitMotionShiftSet(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void func_800E648C_shared_board(void);
void MBKSuitMotionLoad(s32 arg0, s32 arg1);

#endif //_ovl_80_F9DE0
