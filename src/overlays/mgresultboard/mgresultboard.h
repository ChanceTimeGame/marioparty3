#ifndef MGRESULTBOARD_H
#define MGRESULTBOARD_H

#include "common.h"

typedef struct PlayerResult {
    /* 0x00 */ s8 idx;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s8 unk_02;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s16 score;
    /* 0x06 */ s16 coin;
    /* 0x08 */ s16 gameCoin;
    /* 0x0A */ s16 bonusCoin;
} PlayerResult; // sizeof 0x0C

/* One player's animated result figure: two models (obj->model[mdlA + 1], obj->model[mdlB + 1])
   that swap when the playing motion ends. */
typedef struct ResultSlot {
    /* 0x00 */ s8 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} ResultSlot; // sizeof 0x0C

extern f32 D_8010AAF4_mgresultboard;
extern s32 D_8010AAF8_mgresultboard;
extern s32 D_8010ADB0_mgresultboard[8];
extern omObjData *D_8010AF98_mgresultboard;
extern omObjData *D_8010AFA0_mgresultboard;
extern omObjData *D_8010AFA8_mgresultboard;
extern void (*D_8010AFAC_mgresultboard)(omObjData *);
extern ResultSlot D_8010AFB0_mgresultboard[4];
extern omObjData *D_8010AFE0_mgresultboard;
extern ResultSlot D_8010AFE8_mgresultboard[4];
extern PlayerResult D_8010B018_mgresultboard[4];
extern PlayerResult D_8010B048_mgresultboard[4];

void func_80107D00_mgresultboard(void);
void func_801080C4_mgresultboard(void);
void func_80108150_mgresultboard(omObjData *);
void func_801081CC_mgresultboard(omObjData *);
void func_801081E8_mgresultboard(void);
s32 func_801081F0_mgresultboard(omObjData *, s8, s8, s8);
s32 func_80108250_mgresultboard(omObjData *, s8, s8, s8);
void func_80108330_mgresultboard(omObjData *);
s32 func_801092E0_mgresultboard(omObjData *, s8, s16);
s32 func_80109878_mgresultboard(omObjData *, s8, s16);
void func_80108700_mgresultboard(void);
void func_80108BBC_mgresultboard(omObjData *);
void func_80108BC4_mgresultboard(omObjData *);
void func_80108C60_mgresultboard(omObjData *);
void func_8010913C_mgresultboard(void);
void func_80109144_mgresultboard(void);
s32 func_80109A90_mgresultboard(omObjData *, s8, s16);
s32 func_8010A864_mgresultboard(omObjData *, s8, s8);

#endif
